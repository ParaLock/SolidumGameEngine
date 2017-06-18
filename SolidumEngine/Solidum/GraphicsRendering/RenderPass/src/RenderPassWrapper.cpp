#include "../include/RenderPassWrapper.h"



RenderPassWrapper::RenderPassWrapper()
{
}


RenderPassWrapper::~RenderPassWrapper()
{
}

void RenderPassWrapper::load(std::shared_ptr<IResourceBuilder> builder)
{
	InitData* realBuilder = static_cast<InitData*>(builder.get());

	_ioInterface = new RenderFlowGraphIOInterface();

	RenderPassDescriptorParser parser;

	RenderPassDescriptorData descData = parser.parseRenderPassDescriptor(realBuilder->_filename);

	_name = descData._renderPassName;

	_ioInterface->setParentName(_name);

	ShaderParser shaderParser;

	for each(ShaderToLoad shaderToLoad in descData._shadersToLoad) {
		std::string shaderCode = shaderParser.parseShader(&descData, shaderToLoad._path);

		IShader* newShader = ResourceManagerPool::getInstance()->getResourceManager("ShaderManager")->createResource(std::make_shared<Shader::InitData>
			(shaderCode, true), shaderToLoad._name, false)->getCore<IShader>();

		_shaders.insert({ shaderToLoad._name, newShader });

	}

	for (auto itr = descData._hooksByName.begin(); itr != descData._hooksByName.end(); itr++) {

		RenderFlowGraphNodeIOHook hook = itr->second;
		_ioInterface->addResourceHook(hook);
	}

}

void RenderPassWrapper::execute(GraphicsCommandList * commandList, RenderDataGroup& collection)
{
	_renderPassCallback(commandList, collection, this);
}

GPUPipeline * RenderPassWrapper::rebuildPSO(GPUPipeline* pipeline)
{
	auto& resources = _ioInterface->getLiveHooks();

	for each(RenderFlowGraphNodeIOHook* hook in resources) {

		RenderPassSpecificIOHookData* specificData = (RenderPassSpecificIOHookData*)hook->_userData;

		pipeline->attachResource(hook->_res, hook->_name, hook->_index,
			specificData->_shaderResType, specificData->_shaderType, hook->_isOutput);

	}

	return pipeline;
}


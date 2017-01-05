#include "../include/GPUPipeline.h"



GPUPipeline::GPUPipeline()
{
	_elementList = new std::map<std::string, GPUPipelineElement*>;
	_uniformToBufferMap = new std::map<std::string, DynamicBuffer*>;
	_opList = new std::list<GPUPipelineOP*>;
}


GPUPipeline::~GPUPipeline()
{
	delete _elementList;
	delete _uniformToBufferMap;
	delete _opList;
}

void GPUPipeline::attachOP(GPUPipelineSupportedOP opType, std::string targetName, GPUPipelineElementType opTargetType, bool executionContext)
{
	GPUPipelineOP *newOP = new GPUPipelineOP;

	newOP->type = opType;
	newOP->targetType = opTargetType;
	newOP->targetName = targetName;

	_opList->push_back(newOP);
}


void GPUPipeline::setDepthTest(bool enable)
{
	depthTestEnabled = enable;
}

void GPUPipeline::setBlending(bool enable)
{
	blendingEnabled = enable;
}

void GPUPipeline::setVertexBuffer(GPUBuffer * newBuff)
{
	auto itr = _elementList->find("vertex_buff");

	if (itr != _elementList->end()) {
		GPUPipelineElement *buff = _elementList->at("vertex_buff");

		buff->core = (void*)newBuff;
	}
}

void GPUPipeline::setIndexBuffer(GPUBuffer * newBuff)
{
	auto itr = _elementList->find("index_buff");

	if (itr != _elementList->end()) {

		GPUPipelineElement *buff = _elementList->at("index_buff");

		buff->core = (void*)newBuff;
	}
}

void GPUPipeline::setPrimaryTexture(Texture * newTex)
{
	auto itr = _elementList->find("primary_texture");

	if (itr != _elementList->end()) {
		GPUPipelineElement *tex = _elementList->at("primary_texture");

		tex->core = (void*)newTex;
	}
}

void GPUPipeline::setSecondaryTexture(Texture * newTex)
{
	auto itr = _elementList->find("secondary_texture");

	if (itr != _elementList->end()) {
		GPUPipelineElement *tex = _elementList->at("secondary_texture");

		tex->core = (void*)newTex;
	}
}

void GPUPipeline::attachRenderTarget(RenderTarget * renderTarget, std::string name, GPUPipelineElementParentShader parentShader, bool isOutput)
{
	GPUPipelineElement *newElement = new GPUPipelineElement;

	newElement->name = name;
	newElement->type = GPUPipelineElementType::SOL_RENDER_TARGET;
	newElement->core = renderTarget;
	newElement->parentShader = parentShader;
	newElement->resourceSlot = renderTargetCount;

	newElement->isOutput = isOutput;

	_elementList->insert({ name, newElement });

	renderTargetCount++;
}

void GPUPipeline::attachTextureSampler(TextureSampler * texSampler, std::string name, GPUPipelineElementParentShader parentShader)
{
	GPUPipelineElement *newElement = new GPUPipelineElement;

	newElement->name = name;
	newElement->type = GPUPipelineElementType::SOL_SAMPLER;
	newElement->core = texSampler;
	newElement->parentShader = parentShader;
	newElement->resourceSlot = texSamplerCount;

	_elementList->insert({ name, newElement });

	texSamplerCount++;
}

void GPUPipeline::attachTextureHook(std::string name, GPUPipelineElementParentShader parentShader)
{
	GPUPipelineElement *newElement = new GPUPipelineElement;

	newElement->name = name;
	newElement->type = GPUPipelineElementType::SOL_TEXTURE_HOOK;
	newElement->core = nullptr;
	newElement->parentShader = parentShader;
	newElement->resourceSlot = 0;

	_elementList->insert({ name, newElement });
}

void GPUPipeline::attachBufferHook(std::string name, GPUPipelineElementParentShader parentShader)
{
	GPUPipelineElement *newElement = new GPUPipelineElement;

	newElement->name = name;
	newElement->type = GPUPipelineElementType::SOL_BUFFER_HOOK;
	newElement->core = nullptr;
	newElement->parentShader = parentShader;
	newElement->resourceSlot = 0;

	_elementList->insert({ name, newElement });
}

void GPUPipeline::attachShaderInputLayout(ShaderInputLayout * inputLayout, std::string name)
{
	GPUPipelineElement *newElement = new GPUPipelineElement;

	newElement->name = name;
	newElement->type = GPUPipelineElementType::SOL_MESH_DATA_LAYOUT;
	newElement->core = inputLayout;
	newElement->resourceSlot = 0;

	_elementList->insert({ name, newElement });
}

void GPUPipeline::attachGeneralShaderDataBuffer(DynamicBuffer *generalBuff, GPUPipelineElementParentShader parentShader)
{
	GPUPipelineElement *newElement = new GPUPipelineElement;

	std::vector<std::string> varNameList = generalBuff->getVarNameList();

	for (unsigned int i = 0; i < varNameList.size(); ++i) {
		_uniformToBufferMap->insert({varNameList[i], generalBuff});
	}

	newElement->name = generalBuff->getName();

	newElement->type = GPUPipelineElementType::SOL_GENERAL_DATA_BUFF;
	newElement->core = generalBuff;
	newElement->resourceSlot = 0;

	newElement->parentShader = parentShader;

	_elementList->insert({ generalBuff->getName(), newElement });
}

void GPUPipeline::applyState()
{
	std::cout << "NO API SPECIFIC PIPELINE BOUND";
}

void GPUPipeline::executePass(int numIndices)
{
	std::cout << "NO API SPECIFIC PIPELINE BOUND";
}


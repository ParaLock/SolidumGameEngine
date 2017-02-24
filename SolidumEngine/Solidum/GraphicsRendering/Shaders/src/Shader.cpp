#include "../include/Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::setMesh(mesh* newMesh)
{
	_pipelineState->setHookResource(newMesh->getIndexBuff(), "index_buffer");
	_pipelineState->setHookResource(newMesh->getVertexBuff(), "vertex_buffer");
}

void Shader::setModelTexture(Texture * tex)
{
	_pipelineState->setHookResource(tex, "model_tex");
}

void Shader::updateMaterialPassUniforms(MaterialPass* pass)
{
	float specPower = pass->getSpecularPower();
	float specIntensity= pass->getSpecularIntensity();

	updateUniform("cbuff_specularIntensity", &specIntensity);
	updateUniform("cbuff_specularColor", &pass->getSpecularColor());
	updateUniform("cbuff_specularPower", &specPower);
}

void Shader::updateLightUniforms(ILight* light)
{
	float intensity = light->getIntensity();
	float constant = light->getAttenuationConstant();
	float linear = light->getAttenuationLinear();
	float exponent = light->getAttenuationExponent();
	float range = light->getRange();

	updateUniform("cbuff_lightViewMatrix", &Matrix4f::transpose(light->getViewMatrix()));
	updateUniform("cbuff_lightProjectionMatrix", &Matrix4f::transpose(light->getProjectionMatrix()));

	updateUniform("cbuff_lightDirection", &light->getDirection());
	updateUniform("cbuff_lightPos", &light->getPosition());
	updateUniform("cbuff_lightColor", &light->getColor());
	updateUniform("cbuff_lightIntensity", &intensity);
	updateUniform("cbuff_pointLightRange", &range);
	updateUniform("cbuff_pointLightConstant", &constant);
	updateUniform("cbuff_pointLightLinear", &linear);
	updateUniform("cbuff_pointLightExponent", &exponent);
}

void Shader::updateModelUniforms(Transform* transform)
{
	updateUniform("cbuff_OBJSpecificMatrix", &Matrix4f::transpose(transform->getMatrix()));
}

void Shader::updateCameraUniforms(camera* cam)
{
	updateUniform("cbuff_eyePos", &cam->getPos());
	updateUniform("cbuff_viewMatrix", &Matrix4f::transpose(cam->getViewMatrix()));
	updateUniform("cbuff_projectionMatrix", &Matrix4f::transpose(cam->getProjectionMatrix()));
	updateUniform("cbuff_worldMatrix", &Matrix4f::transpose(cam->getWorldMatrix()));
	updateUniform("cbuff_orthoProjection", &cam->getOrthoProjectionMatrix());
	updateUniform("cbuff_camViewStart", &Matrix4f::transpose(cam->getStartViewMatrix()));
}

void Shader::execute(int numIndices)
{
	std::cout << "GENERIC SHADER: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;
}

void Shader::updateUniform(std::string varName, void * pData)
{
	auto itr = _constantBufferMemberNameMap->find(varName);

	if (itr != _constantBufferMemberNameMap->end()) {

		DynamicStruct* varsBuff = _constantBufferMemberNameMap->at(varName);

		varsBuff->updateVar(varName, pData);
	}
}

void Shader::updateGPU()
{
	DynamicStruct* previous = nullptr;

	std::vector<DynamicStruct*> activeGeneralDataBuffers;

	for (auto itr = _constantBufferMemberNameMap->begin(); itr != _constantBufferMemberNameMap->end(); itr++) {

		if (itr->second != previous)
			activeGeneralDataBuffers.push_back(itr->second);

		previous = itr->second;
	}

	for (unsigned int i = 0; i < activeGeneralDataBuffers.size(); ++i) {
		activeGeneralDataBuffers[i]->updateGPU();
	}
}

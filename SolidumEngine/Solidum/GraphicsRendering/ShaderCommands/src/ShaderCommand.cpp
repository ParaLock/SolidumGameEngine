#include "../include/ShaderCommand.h"


void ShaderUpdateUniformCommand::execute()
{
	for each(ShaderUniformGroup::Uniform uniform in _uniforms.getUniforms()) {

		_shader->updateUniform(uniform._name, uniform._data->_mem);
	}
}

void ShaderSyncUniforms::execute()
{
	_shader->updateGPU();
}

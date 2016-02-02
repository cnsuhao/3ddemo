#include "ShaderMgr.h"

ShaderMgr* ShaderMgr::_shadermrg = nullptr;

ShaderMgr* ShaderMgr::getInstance()
{
	if (!_shadermrg)
	{
		_shadermrg = new ShaderMgr;
		_shadermrg->loadShaders();
	}
	return _shadermrg;
}

void ShaderMgr::loadShaders()
{
	insertShader(Shader::noblack,NOBLACK_GLPROGRAM_V, NOBLACK_GLPROGRAM_F);
	insertShader(Shader::stroke, NOBLACK_GLPROGRAM_V, STROKE_GLPROGRAM_F);
}

void ShaderMgr::insertShader(Shader name, string vet, string frag)
{
	GLProgram* glProgram = GLProgram::createWithFilenames(vet, frag);
	if (glProgram)
	{
		GLProgramState* glProgramState = GLProgramState::create(glProgram);
		glProgramState->retain();
		m_shaders.insert(make_pair(name, glProgramState));
	}
}

GLProgramState* ShaderMgr::getGLProgramState(Shader name)
{
	auto it = m_shaders.find(name);
	if (it != m_shaders.end())
	{
		return it->second;
	}

	return nullptr;
}

GLProgramState* ShaderMgr::getStrokeGLProgramState(Size texSize,int outlineSize, Color3B outlineColor)
{
	auto glprogramState = getGLProgramState(Shader::stroke);
	if (glprogramState)
	{
		glprogramState->setUniformFloat("outlineSize", outlineSize);
		glprogramState->setUniformVec3("outlineColor", Vec3(outlineColor.r / 255.0f, outlineColor.g / 255.0f, outlineColor.b / 255.0f));
		glprogramState->setUniformVec2("textureSize", Vec2(texSize.width, texSize.height));
		glprogramState->setUniformVec3("foregroundColor", Vec3(1, 1, 1));
	}
	return glprogramState;
}

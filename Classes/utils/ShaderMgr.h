#include "CocosHead.h"

#define NOBLACK_GLPROGRAM_V "shader/ccShader_NoBlack.vsh"
#define NOBLACK_GLPROGRAM_F "shader/ccShader_NoBlack.fsh"
#define STROKE_GLPROGRAM_F	"shader/ccShader_Stroke.fsh"

enum class Shader
{
	noblack = 1,
	stroke	= 2,
};

class ShaderMgr
{
public:
	static ShaderMgr* getInstance();

	void loadShaders();

	void insertShader(Shader name,string vet, string frag);

	GLProgramState* getGLProgramState(Shader name);

	GLProgramState* getStrokeGLProgramState(Size texSize, int outlineSize, Color3B outlineColor);
private:

	ShaderMgr(){};
	~ShaderMgr(){};

	map<Shader, GLProgramState*> m_shaders;
	static ShaderMgr* _shadermrg;
};

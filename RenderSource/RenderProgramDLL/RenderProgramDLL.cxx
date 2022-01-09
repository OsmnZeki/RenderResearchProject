#include "RenderProgramDLL.h"

#pragma region ScreenFunctions

Screen* CreateScreen()
{
	Screen* screen = new Screen();

	screen->ConfigureGLFW();

	if (!screen->Initialize())
	{
		//return;
	}

	// glad: load all OpenGL function pointers
	if (screen->CheckGladInitialization())
	{
		//return;
	}

	screen->SetParameters();

	return screen;
}

bool ScreenShouldClose(Screen* screen)
{
	return screen->ShouldClose();
}

void ScreenUpdate(Screen* screen)
{
	screen->Update();
}

void ScreenNewFrame(Screen* screen)
{
	screen->NewFrame();
}

void ScreenTerminate(Screen* screen)
{
	screen->Terminate();
}

void ScreenProcessInput(Screen* screen)
{
	screen->ProcessInput();
}

#pragma endregion

#pragma region ShaderFunction

Shader* NewShader(const char* vertexShaderPath, const char* fragShaderPath)
{
	Shader* shader = new Shader(vertexShaderPath, fragShaderPath);
	return shader;
}

void ShaderSetInt(Shader* shader,const char* name, int value)
{
	glUniform1i(glGetUniformLocation(shader->id, name), value);
}

void ShaderSetFloat(Shader* shader,const char* name, float value)
{
	glUniform1f(glGetUniformLocation(shader->id, name), value);
}

void ShaderSet3Float(Shader* shader,const char* name, float value, float value1, float value2)
{
	glUniform3f(glGetUniformLocation(shader->id, name), value, value1, value2);
}

void ShaderSet4Float(Shader* shader, const char* name, float value, float value1, float value2, float value3)
{
	glUniform4f(glGetUniformLocation(shader->id, name), value, value1, value2, value3);
}

void ShaderSetBool(Shader* shader, const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(shader->id, name), (int)value);
}



#pragma endregion

#pragma region TextureFunctions

Texture* NewTexture(const char* directory, const char* name, int type)
{
	Texture* texture = new Texture(directory, name,(aiTextureType)type);
	return texture;
}

void TextureLoad(Texture* texture, bool flip)
{
	texture->Load(flip);
}



#pragma endregion


#pragma region ModelFunctions

Model* NewModel()
{
	Model* model = new Model();
	return model;
}

void LoadModel(Model* model, const char* modelPath)
{
	std::string path = modelPath;
	model->LoadModel(path);
}

void Render(Model* model, Shader* shader)
{
	model->Render(*shader);
}

void CleanUp(Model* model)
{
	model->CleanUp();
}

#pragma endregion


#pragma region InputFunctions
bool GetKeyDown(int keyCode)
{
	return KeyboardInput::KeyWentDown(keyCode);
}

bool GetKeyUp(int keyCode)
{
	return KeyboardInput::KeyWentUp(keyCode);
}

bool GetKey(int keyCode)
{
	return KeyboardInput::Key(keyCode);
}

bool GetMouseKeyDown(int keyCode)
{
	return MouseInput::ButtonWentDown(keyCode);
}

bool GetMouseKeyUp(int keyCode)
{
	return MouseInput::ButtonWentUp(keyCode);
}

bool GetMouseKey(int keyCode)
{
	return MouseInput::Button(keyCode);
}

#pragma endregion





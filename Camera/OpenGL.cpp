#include <iostream>
#include <glad/glad.h> 
#include <glfw3.h>
#include "FrogEngine.h"

using namespace FrogEngine;

Camera camera;

void CameraUpdate()
{
	camera.ProcessMouseMovement(-Input::GetMousePosDeltaX() / Screen::GetWidth(), Input::GetMousePosDeltaY() / Screen::GetHeight());
	if (Input::GetKey(GLFW_KEY_W))
	{
		camera.Move(Direction::FRONT, Time::GetDeltaTime());
	}
	if (Input::GetKey(GLFW_KEY_A))
	{
		camera.Move(Direction::LEFT, Time::GetDeltaTime());
	}
	if (Input::GetKey(GLFW_KEY_S))
	{
		camera.Move(Direction::BACK, Time::GetDeltaTime());
	}
	if (Input::GetKey(GLFW_KEY_D))
	{
		camera.Move(Direction::RIGHT, Time::GetDeltaTime());
	}
	if (Input::GetKey(GLFW_KEY_SPACE))
	{
		camera.Move(Direction::UP, Time::GetDeltaTime());
	}
	if (Input::GetKey(GLFW_KEY_LEFT_SHIFT))
	{
		camera.Move(Direction::DOWN, Time::GetDeltaTime());
	}
}

int main()
{
	/*
	std::cout << "Mem test:"<< std::endl;
	std::cout << "sizeof(Vertex):" << sizeof(Vertex) << std::endl;
	std::cout << "sizeof(Vector3):" << sizeof(Vector3) << std::endl;
	std::cout << "sizeof(Vector2):" << sizeof(Vector2) << std::endl;
	std::cout << "offsetof(Vertex, Normal):" << offsetof(Vertex, Normal) << std::endl;
	std::cout << "offsetof(Vertex, TexCoord):" << offsetof(Vertex, TexCoord) << std::endl;
	*/


	//初始化GLFW
	glfwInit();
	//配置OpenGL版本号3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//配置GLFW使用核心模式，Core-profile（只能使用OpenGL功能的一个子集，即没有我们已不再需要的向后兼容特性）
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Mac OS X系统需要以下语句
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(Screen::GetWidth(), Screen::GetHeight(), "", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	Input::SetWindow(window);
	//将已创建窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	//GLAD用来管理OpenGL的函数指针，在调用任何OpenGL的函数之前我们需要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//OpenGL渲染窗口的尺寸大小，左下角，长，宽
	glViewport(0, 0, Screen::GetWidth(), Screen::GetHeight());

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//当窗口大小改变时，可能需要一些相应的操作，例如改变视口大小
	//窗口注册一个回调函数，函数原型：void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	glfwSetFramebufferSizeCallback(window, Screen::ScreenSizeChanged);
	//鼠标输入回调函数
	glfwSetCursorPosCallback(window, Input::UpdateMousePos);
	//深度测试
	glEnable(GL_DEPTH_TEST);

	Camera::SetCurrentCamera(&camera);

	auto directionalLight = DirectionalLight::Create(Vector3(1, -1, 1), Vector3(1, 1, 1));
	Shader::LoadShader("Phong", "Common.vs", "BlinnPhong.fs");


	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	Vector3 cubePositions[] = {
  Vector3(2.0f,  5.0f, -15.0f),
  Vector3(-1.5f, -2.2f, -2.5f),
  Vector3(-3.8f, -2.0f, -12.3f),
  Vector3(2.4f, -0.4f, -3.5f),
  Vector3(-1.7f,  3.0f, -7.5f),
  Vector3(1.3f, -2.0f, -2.5f),
  Vector3(1.5f,  2.0f, -2.5f),
  Vector3(1.5f,  0.2f, -1.5f),
  Vector3(-1.3f,  1.0f, -1.5f)
	};

	//顶点缓冲对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//创建顶点数组对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//绑定顶点数组对象
	glBindVertexArray(VAO);
	//OpenGL允许我们同时绑定多个缓冲，只要它们是不同的缓冲类型。我们可以使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//绑定缓冲后，使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)。然后我们可以调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//如何解析顶点数据
	//glVertexAttribPointer参数：位置值，顶点属性大小，数据类型，标准化（0~1），步长，起始位置偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//翻转图片
	stbi_set_flip_vertically_on_load(true);
	// 加载并生成纹理
	int width, height, nrChannels;
	unsigned char* data = stbi_load("../Resource/container2.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	Node* cube = new Node();
	Mesh* cubeMesh = Mesh::Create(Mesh::Cube);
	cube->mesh = cubeMesh;
	cube->mesh->material = Material::Create();
	cube->mesh->material->diffuseTexture = Texture2D::Create("../Resource/container2.jpg", false);
	cube->mesh->material->specularTexture = Texture2D::Create("../Resource/container2_specular.jpg", false);
	Node::ROOT->AddChild(cube);

	unsigned int lastPrint = 0;

	unsigned int FPS = 150;
	float FrameTime = 1 / (float)FPS;
	float FrameStartTime = glfwGetTime();
	//Loop
	while (!glfwWindowShouldClose(window))
	{
		while (glfwGetTime() < FrameStartTime)
		{
		}
		FrameStartTime += FrameTime;
		Time::Update();
		//清除颜色缓冲和深度缓冲
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		if (Time::GetCurrentTime() - lastPrint >= 1)
		{
			lastPrint = Time::GetCurrentTime();
			glfwSetWindowTitle(window, (std::string("Endless War    Fps: ") + std::to_string(1 / Time::GetDeltaTime())).c_str());
		}
		CameraUpdate();
		Node::ROOT->Rendering();
		//使用该着色器程序
		Shader::GetShader("Phong")->Use();
		Shader::GetShader("Phong")->SetInt("material.diffuse", 0);
		Shader::GetShader("Phong")->SetMat4("view", camera.GetLookAtMatrix());
		Shader::GetShader("Phong")->SetMat4("projection", camera.GetProjectionMatrix());
		for (size_t i = 0; i < 9; i++)
		{
			Matrix4 model;
			model.Translate(cubePositions[i]);
			model.Rotate(Vector3(0.0f, 1.0f, 0.0f), (float)glfwGetTime());
			Shader::GetShader("Phong")->SetMat4("model", model);

			//			cubeMesh->Draw(VAO,VBO);
						/*glBindTexture(GL_TEXTURE_2D, texture);
						glBindVertexArray(VAO);
						glDrawArrays(GL_TRIANGLES, 0, 36);*/

			glBindTexture(GL_TEXTURE_2D, texture);
			//			glBindVertexArray(VAO);
			//			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBindVertexArray(cubeMesh->_vao);
			glBindBuffer(GL_ARRAY_BUFFER, cubeMesh->_vbo);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		Input::ClearFrameInput();

		if (Input::GetKey(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, true);
		}
		//交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
		glfwSwapBuffers(window);
		//是否触发事件，键盘输入、鼠标移动等、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
		glfwPollEvents();
	}
	//释放/删除之前的分配的所有资源
	glfwTerminate();
	return 0;
}
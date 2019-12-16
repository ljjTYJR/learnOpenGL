#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
using namespace std;

/*函数申明在前，可以定义在后进行引用*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

/*Setting*/
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

/*顶 点 着 色 器*/
//version 类似于预编译不需要加;
//但是其余语句是正常的定义句，需要加;;

const char* vertexShaderSource =
"#version 450 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\0";

/*片 段 着 色 器*/
const char *fragmentShaderSource = "#version 450 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";




//输出错误信息
static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

//keybacl，关闭
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*三 角 形 数 据*/



int main(void)
{
	GLFWwindow* window;

	//GLAD库的OPENGL版本为4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//设置core模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/* Initialize the library */
	glfwInit();
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//初始化GLAD,获取函数指针
	//glfwGetProcAddress是GLFW根据编译系统定义正确函数,然后转化为glad可以识别的函数
	//load是给GLAD传入正确的函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*编 译 生 成 顶 点 着 色 器*/
	//vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	/*编 译 生 成 片 段 着 色 器*/
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	/*连 接 着 色 器 程 序*/
	unsigned int shaderProgram = glCreateProgram();
	//链 接 着 色 器 对 象
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//删 除 着 色 器 对 象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	//创建VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);//因为是对参数进行设定，因此不是传值而是传址

	/*渲 染 内 容*/
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//绑定VAO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*链 接 顶 点 属 性*/
	//获取数据的源为VBO，也就是之前传入内存中的内容
	//是当前的buffer中获取
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//启 动 顶 点 属 性
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 


	/*设 定 视 口*/
	glViewport(0, 0, WIDTH, HEIGHT);

	/* parameters setting */
	/* 必 须 要 在 OpenGL 版 本 号 之 后*/
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	/* Loop until the user closes the window */
	/*渲 染 循 环*/
	while (!glfwWindowShouldClose(window))
	{
		/*处 理 输 入 事 件*/
		processInput(window);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/*图 形 绘 制*/
		//激 活 程 序 对 象
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}


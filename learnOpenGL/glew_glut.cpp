#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include"stb_image.h"
#include"shader.h"
#include<iostream>

using namespace std;
using namespace glm;

int  width = 800;
int  height = 600;
float mixValue = 0.2f;
//camera Pos
glm::vec3 camerPos = glm::vec3(0.0f, 0.0f, 3.0f);	//Z轴指向屏幕外
//camera Front
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
void ProcessInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int main()
{
	/*首 先 初 始 化 窗 口*/
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*创 建 窗 口*/
	GLFWwindow* window = glfwCreateWindow(width, height, "myOpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW Window" << endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	/*回 调 函 数*/

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	Shader ourshader("vertex.shader", "fragment.shader");
	
	/*
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};*/
	/*
	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};*/
	float vertices[] = 
	{
	//顶 点 坐 标		  //纹 理 坐 标
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
	// 各 个 位 置
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	/*#6 配 置 顶 点 属 性*/
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
		//#6.1 绑 定 顶 点 属 性
	glBindVertexArray(VAO);

		//#6.2 绑 定 缓 冲（片段）
		//设 定 输 入 数 据 类 型
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//EBO设置
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		//#6.3 如 何 读 取 VBO 中 元 素 并 输 入
		//激活顶点属性（index）
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// textute coord arrtibute
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	stbi_set_flip_vertically_on_load(true);
	/*纹 理 处 理*/
	int picture_width, picture_height, nrChannels;
	unsigned char* data = stbi_load("wall.jpg", &picture_width, &picture_height, &nrChannels, 0);	//是否正确加载？
		//上面的nrChannels对应着图像的通道数，这里加载时一定要注意！
		//生 成 纹 理
	unsigned int texture1,texture2;
	glGenTextures(1, &texture1);	//第一个参数是生成纹理的数量，第二个参数是需要绑定的对象（如果是多个，则是数组）
		//绑定纹理
	glBindTexture(GL_TEXTURE_2D, texture1);
		//设置纹理的环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//生成纹理
		//1.生成当前绑定的纹理
		//2.指定多级渐远级别
		//3.生成的图像存储为什么格式
		//4.纹理的宽度/长度
		//6.0（历史遗留）
		//7.源图的格式，数据类型；RGB加载，存储为char
		//这个函数是为当前绑定的纹理图像生成相应的图像，
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, picture_width, picture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//设置多级渐远
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else std::cout << "failed to load texture" << endl;
		//均已设置完成，则进行内存释放
	stbi_image_free(data);

	//texture2 //这里可以写一个类来进行操作，但为熟悉过程，一步一步写
	data = stbi_load("haha.jpg", &picture_width, &picture_height, &nrChannels, 0);
	cout << nrChannels;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//这个也是边缘拉伸，不过边缘是透明的，因此就看不出来
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, picture_width, picture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//设置多级渐远
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else std::cout << "failed to load texture2" << endl;
	//均已设置完成，则进行内存释放
	stbi_image_free(data);
	
	ourshader.use();
	glUniform1i(glGetUniformLocation(ourshader.ID, "texture1"), 0);
	ourshader.setInt("texture2", 1);

	unsigned int modelLoc = glGetUniformLocation(ourshader.ID, "model");
	unsigned int viewLoc = glGetUniformLocation(ourshader.ID, "view");
	unsigned int projLoc = glGetUniformLocation(ourshader.ID, "projection");

		//启 用 深 度 测 试
	glEnable(GL_DEPTH_TEST);

	//利 用 glm 进 行 位 置 变 化
	//得 到 旋 转 矩 阵 
	/*渲 染 循 环*/
	while (!glfwWindowShouldClose(window))
	{
		/*处 理 输 入*/
		ProcessInput(window);

		/*背 景 清 理*/
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glBindTexture(GL_TEXTURE_2D, texture);
		//glBindVertexArray(VAO);
			//上面两句其实也可以没有，因为没有绑定新的buffer，也没有清理，但为了完整性，保留

		//绑定对应的纹理单元前，先激活纹理单元
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE0+1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		ourshader.setFloat("alpha_percent", mixValue);
		// render container
		ourshader.use();

		glBindVertexArray(VAO);
		//model Matrix
		//glm::mat4 model(1.0f);
		//model = glm::rotate(model, (float)glfwGetTime()*glm::radians(45.0f), glm::vec3(0.5f, 0.5f, 0.0f));
			//camera Orientation
		glm::vec3 camTarget = glm::vec3(0.0f, 0.0f, 0.0f);	//摄像机的指向
		glm::vec3 camDirection = glm::normalize(camerPos - camTarget);	//Dir其实是指向的反方向，a-b  是由向量b指向向量a
			//Right Axis——camrea X Axis
		glm::vec3 up (0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, camDirection));
			//Y Axis——camera Y Axis
		glm::vec3 cameraup = glm::normalize(glm::cross(camDirection, cameraRight));
			//create LOOK AT Matrix
			//rotate the camrea
		//float radius = 10.0f;
		//float camX = sin(glfwGetTime())*radius;
		//float camZ = cos(glfwGetTime())*radius;
		glm::mat4 view = glm::lookAt(
			camerPos,
			camerPos+glm::vec3(0.0f,0.0f,-1.0f),
			up
		);

		//View Port
		//glm::mat4 view(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		//Perspective Matrix
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(45.0f), float(width / height), 0.1f, 100.0f);
		//设 置 变 换 参 数
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 5.0f*(i+1);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			ourshader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//运行第一遍进行绘制，0代表in
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//float scaleFactor = abs(sin(glfwGetTime()));
		//trans = glm::scale(trans, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
		//trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		
		//glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		/*启动交换buffer*/
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/*退 出 程 序 & 清 理 资 源*/
	glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.02f;
		if (mixValue > 1.0f)
			mixValue = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.02f;
		if (mixValue < 0.0f)
			mixValue = 0.0f;
	}

	float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 camerPos+= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camerPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camerPos -= glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f,1.0f,0.0f))) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camerPos += glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
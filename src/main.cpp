#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include <Shader.h>
#include <Camera.h>
#include <Entity.h>
#include <Transform.h>
#include <math.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <VAO.h>
#include <VBO.h>
#include <EBO.h>
#include <Texture.h>
#include <game.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void RenderEntities(Entity root, unsigned int modelLoc);
void ChangePolygonMode();

const unsigned int width = 800;
const unsigned int height = 800;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Game game;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(width, height, "Opengl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	gladLoadGL();
	glViewport(0, 0, width, height);

	// POLYGONMODE
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	// vsynch
	// glfwSwapInterval(0);

	float vertices[] = {
		// Back face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,

		// Front face
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		// Left face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

		// Right face
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		// Bottom face
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,

		// Top face
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f};

	unsigned int indices[] = {
		// Back face
		0, 1, 2,
		2, 3, 0,

		// Front face
		4, 5, 6,
		6, 7, 4,

		// Left face
		8, 9, 10,
		10, 11, 8,

		// Right face
		12, 13, 14,
		14, 15, 12,

		// Bottom face
		16, 17, 18,
		18, 19, 16,

		// Top face
		20, 21, 22,
		22, 23, 20};

	game.Start();

	// Textures

	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");
	Texture tex1("resources/textures/container.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	Texture tex2("resources/textures/awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);

	// Vertex Objects
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void *)0);
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 11 * sizeof(float), (void *)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 11 * sizeof(float), (void *)(5 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void *)(8 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	shaderProgram.use();

	tex1.texUnit(shaderProgram, "texture1", 0);
	tex2.texUnit(shaderProgram, "texture2", 1);

	float lastCheck = 0;
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		if (lastCheck > 1 / 2)
		{
			std::string fps = std::to_string(1 / deltaTime);
			glfwSetWindowTitle(window, fps.c_str());
			processInput(window);
			lastCheck = 0;
		}
		lastCheck += deltaTime;

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		tex1.Bind();
		glActiveTexture(GL_TEXTURE1);
		tex2.Bind();

		shaderProgram.use();

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
		// lighting calculations
		unsigned int lightColorLoc = glGetUniformLocation(shaderProgram.ID, "lightColor");
		unsigned int lightPosLoc = glGetUniformLocation(shaderProgram.ID, "lightPos");
		shaderProgram.setVec3("viewPos", camera.Position);
		glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightPosLoc, 2.0f, 2.0f, 0.0f);

		shaderProgram.setVec3("pointLights[0].position", glm::vec3(2.0f, 2.0f, 0.0f));
		shaderProgram.setVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		shaderProgram.setVec3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		shaderProgram.setVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderProgram.setFloat("pointLights[0].constant", 1.0f);
		shaderProgram.setFloat("pointLights[0].linear", 0.09f);
		shaderProgram.setFloat("pointLights[0].quadratic", 0.032f);
		// retrieve the matrix uniform locations

		unsigned int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		// pass them to the shaders (3 different ways)
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		VAO1.Bind();
		unsigned int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		game.data.modelLoc = modelLoc;

		game.Update(deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	game.End();
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.deleteProgram();
	tex1.Delete();
	tex2.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void RenderEntities(Entity root, unsigned int modelLoc)
{
	std::stack<Entity *> stack;
	for (auto &child : root.children)
	{
		if (child->isEnable)
			stack.push(child);
	}

	while (!stack.empty())
	{
		Entity *current = stack.top();
		stack.pop();
		current->DrawMesh(modelLoc);
		for (auto &child : current->children)
		{
			if (child->isEnable)
				stack.push(child);
		}
	}
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	game.data.playerVel = glm::vec3(0.0f, 0.0f, 0.0f);
	game.data.playerAngularSpeed = 0;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		game.data.playerVel.y = game.data.playerSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		game.data.playerVel.y = -game.data.playerSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		game.data.playerVel.x = game.data.playerSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		game.data.playerVel.x = -game.data.playerSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		game.data.playerVel.z = game.data.playerSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		game.data.playerVel.z = -game.data.playerSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		game.data.playerAngularSpeed = 1.0f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		game.data.playerAngularSpeed = -1.0f;

	if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS))
	{
		ChangePolygonMode();
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void ChangePolygonMode()
{
	if (game.data.polygonMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	game.data.polygonMode = !game.data.polygonMode;
}
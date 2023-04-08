#include "Runner.h"
Runner::Runner()
{
#pragma region initialize


	//initialize glfw  
	if (glfwInit() != GLFW_TRUE) {
		fprintf(stderr, "Failed to initialized! \n");
		return;
	}

	// set opengl version to 3.3  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window   
	window = glfwCreateWindow(1024, 768, "Khalil Jan Arcilla", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to load window! \n");
		return;
	}

	glfwMakeContextCurrent(window);

	//initialize glew  
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return;
	}
#pragma endregion

	
	glGenTextures(8, texture);
	glGenTextures(8, multiTexture);
#pragma region object

	load3dModel(texture, multiTexture, ObjOffset, GaneshaObjData, "Ganesha/Ganesha.obj", 3);
	std::cout << GaneshaObjData.baseDir << "\n";
	std::cout << "waiting" << "\n";

	load3dModel(texture, multiTexture, ObjOffset, SkullObjData, "Skull/Skull.obj", 4);
	std::cout << "waiting" << "\n";

	load3dModel(texture, multiTexture, ObjOffset, SwordObjData, "Sword/moonlight.obj", 5);
	std::cout << "waiting" << "\n";

	load3dModel(texture, multiTexture, ObjOffset, PedestalObjData, "pedestal/10421_square_pedastal_iterations-2.obj", 6);
	std::cout << "waiting" << "\n";

	load3dModel(texture, multiTexture, ObjOffset, FloorObjData, "Floor/CobbleStones2.obj", 7);
	std::cout << "waiting" << "\n";

	load3dModel(texture, multiTexture, ObjOffset, EarthObjData, "earth/Earth.obj", 0);
	std::cout << "waiting" << "\n";

	load3dModel(texture, multiTexture, ObjOffset, MoonObjData, "earth/Earth.obj", 1);
	std::cout << "waiting" << "\n";

	load3dModel(texture, multiTexture, ObjOffset, SunObjData, "earth/Earth.obj", 2);
	std::cout << "waiting" << "\n";


#pragma endregion

#pragma region skybox
	std::vector<std::string> faces{
		"right.png",
		"left.png",
		"top.png",
		"bottom.png",
		"front.png",
		"back.png"

	};
	skybox = loadSkyBox("Assets/Skybox", faces);
#pragma endregion

#pragma region shader
	//skybox shader
	skyboxShaderProgram = loadShaders("Shaders/skybox_vertex.shader", "Shaders/skybox_fragment.shader");

	//GLuint shaderProgram = loadShaders("Shaders/vertex.shader", "Shaders/fragment.shader");
	//GLuint shaderProgram = loadShaders("Shaders/goraud_vertex.shader", "Shaders/goraud_fragment.shader");
	//GLuint shaderProgram = loadShaders("Shaders/test_vertex.shader", "Shaders/test_fragment.shader");
	shaderProgram = loadShaders("Shaders/phong_vertex.shader", "Shaders/phong_fragment.shader");
	glUseProgram(shaderProgram);
	GLfloat red = 1.0f;
	GLfloat green = 0.0f;
	GLfloat blue = 0.0f;
	colorLoc = glGetUniformLocation(shaderProgram, "u_color");
	glUniform3f(colorLoc, 0.3f, 0.3f, 0.3f);

	modelTransformLoc = glGetUniformLocation(shaderProgram, "u_model");
	viewLoc = glGetUniformLocation(shaderProgram, "u_view");
	projectionLoc = glGetUniformLocation(shaderProgram, "u_projection");

	//normal transformations
	normalTransLoc = glGetUniformLocation(shaderProgram, "u_normal");
	cameraPosLoc = glGetUniformLocation(shaderProgram, "u_camera_pos");
	GLuint ambientColorLoc = glGetUniformLocation(shaderProgram, "u_ambient_color");
	glUniform3f(ambientColorLoc, 0.8f, 0.8f, 0.8f);

	//light shading
	GLuint lightLoc = glGetUniformLocation(shaderProgram, "u_light_pos");
	GLuint diffuseLoc = glGetUniformLocation(shaderProgram, "texture_diffuse");
	GLuint diffuse2Loc = glGetUniformLocation(shaderProgram, "texture2_diffuse");
	glUniform3f(lightLoc, 3.0f, 3.0f, 2.0f);

	//set textures
	glUniform1i(diffuseLoc, 0);
	glUniform1i(diffuse2Loc, 1);

	//bool check
	//GLuint isSun = glGetUniformLocation(shaderProgram, "sun");
	multiTex = glGetUniformLocation(shaderProgram, "multi");

	//transformation matrix
	glm::mat4 trans = glm::mat4(1.0f); // identity
	trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));//change this for x y z positions
	//trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 0.0f));// rotation by degrees on glm::radians
	trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));//scale
	//glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	//define projection matrix
	projection = glm::mat4(1.0f);// = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, -1.0f);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	
	transMoon =
		transSun =
		transGanesha =
		transSword =
		transPedestal =
		transFloor =
		transSkull = glm::mat4(1.0f);

	transSun = glm::scale(transSun, glm::vec3(1.0f, 1.0f, 1.0f));
	transSun = glm::translate(transSun, glm::vec3(30.0f, 0.0f, -40.0f));

	transPedestal = glm::translate(transPedestal, glm::vec3(50.0f, 0.0f, -40.0f));

	transFloor = glm::translate(transFloor, glm::vec3(0.0f, 0.0f, -15.0f));

	transGanesha = glm::translate(transGanesha, glm::vec3(30.0f, 0.0f, -40.0f));
	transGanesha = glm::translate(transGanesha, glm::vec3(120.0f, 0.0f, 0.0f));
	transGanesha = glm::scale(transGanesha, glm::vec3(2.0f, 2.0f, 2.0f));//scale

	transGanesha = glm::rotate(transGanesha, glm::radians(220.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//transGanesha = glm::translate(transGanesha, glm::vec3(10.0f, 0.0f, 0.0f));

	transSword = glm::translate(transSword, glm::vec3(30.0f, 0.0f, -40.0f));
	transSword = glm::translate(transSword, glm::vec3(200.0f, 15.0f, 0.0f));
	transSword = glm::scale(transSword, glm::vec3(0.2f, 0.2f, 0.2f));//scale
	transSword = glm::scale(transSword, glm::vec3(0.5f, 0.5f, 0.5f));//scale
	transSword = glm::rotate(transSword, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	//transSkull = glm::translate(transSkull, glm::vec3(40.0f, 0.0f, -20.0f));
	transSkull = glm::translate(transSkull, glm::vec3(50.0f, 0.0f, -40.0f));
	transSkull = glm::scale(transSkull, glm::vec3(4.0f, 4.0f, 4.0f));//scale



	GLfloat x = 0.0f, y = 0.0f, z = 0.0f;
	GLfloat xScale = 0.0f, yScale = 0.0f, zScale = 0.0f;
	GLfloat xRotate = 0.0f, YRotate = 0.0f, ZRotate = 0.0f;
	double prevxpos = 0.0f, prevypos = 0.0f;
	double xpos = 0.0f, ypos = 0.0f;
#pragma endregion

#pragma region view settings

	position = glm::vec3(0.0f, 1.0f, 0.0f);
	viewDirections = glm::vec3(0.0f, 0.0f, 0.0f);
	Up = glm::vec3(0.0f, 0.0f, -1.0f);
	//projection = glm::ortho(-40.0f, 120.0f, -40.0f, 120.0f, 0.1f, max_far);

	position = glm::vec3(30.0f, 20.0f, 40.0f);
	viewDirections = glm::vec3(30.0f, 0.0f, 0.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
#pragma endregion


	// set bg color to green  
	glClearColor(0.3f, 0.3f, 0.3f, 0.3f);

	
	glEnable(GL_DEPTH_TEST);
	auto t1 = Clock::now();
	std::cout << "loop NOW" << "\n";
}

void Runner::run()
{
	while (!glfwWindowShouldClose(window)) {
		glfwSetCursorPosCallback(window, mouse_callback);


		//for FPS
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
			walkspeed = 1.0f;
		}
		else {
			walkspeed = 0.5f;

		}
		if (true) {
			glm::vec3 strafeDir = glm::cross(camFront, Up);
			camUp = glm::cross(strafeDir, camFront);
			strafeDir = glm::cross(camFront, camUp);
			if (glfwGetKey(window, GLFW_KEY_D)) {
				position += walkspeed * strafeDir;
				//std::cout << glm::to_string(position) << std::endl;

			}
			if (glfwGetKey(window, GLFW_KEY_A)) {
				position -= walkspeed * strafeDir;
				//std::cout << glm::to_string(position) << std::endl;

			}
			if (glfwGetKey(window, GLFW_KEY_W)) {
				position += walkspeed * camFront;
				//std::cout << glm::to_string(position) << std::endl;

				//viewDirections.z += 0.1f;
			}
			if (glfwGetKey(window, GLFW_KEY_S)) {
				position -= walkspeed * camFront;
				//std::cout << glm::to_string(position) << std::endl;

				//viewDirections.z -= 0.1f;
			}
			if (glfwGetKey(window, GLFW_KEY_E)) {
				position += walkspeed * Up;
				//std::cout << glm::to_string(position) << std::endl;
			}
			if (glfwGetKey(window, GLFW_KEY_Q)) {
				position -= walkspeed * Up;
				//std::cout << glm::to_string(position) << std::endl;
			}
			if (position.y < 40.0f || position.y > 40.0f) {
				position.y = 40.0f;
			}
		}

		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);

		if (glfwGetKey(window, GLFW_KEY_R)) {
			position = glm::vec3(30.0f, 20.0f, 40.0f);
			viewDirections = glm::vec3(30.0f, 0.0f, 0.0f);
			Up = glm::vec3(0.0f, 1.0f, 0.0f);
			//projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(60.0f), ratio, 0.1f, max_far);
		}
		if (glfwGetKey(window, GLFW_KEY_T)) {
			position = glm::vec3(0.0f, 1.0f, 0.0f);
			viewDirections = glm::vec3(0.0f, 0.0f, 0.0f);
			Up = glm::vec3(0.0f, 0.0f, -1.0f);
			//projection = glm::mat4(1.0f);
			projection = glm::ortho(-40.0f, 120.0f, -40.0f, 120.0f, 0.1f, max_far);
		}
		projection = glm::perspective(glm::radians(60.0f), ratio, 0.1f, max_far);

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

#pragma region View

		//for fps
		glm::mat4 view = glm::lookAt(
			position,
			position + camFront,
			Up
		);
		glUniform3f(cameraPosLoc, position.x, position.y, position.z);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

#pragma endregion

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#pragma region Draw
		//--- start drawing here ---

		drawSkyBox(skybox, skyboxShaderProgram, view, projection);
		glUseProgram(shaderProgram);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(multiTex, false);

		glUniform1i(multiTex, false);

		glBindVertexArray(SwordObjData.vaoId);
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(transSword));
		glDrawElements(GL_TRIANGLES, SwordObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

		glBindVertexArray(GaneshaObjData.vaoId);
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(transGanesha));
		glDrawElements(GL_TRIANGLES, GaneshaObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

		glBindVertexArray(SkullObjData.vaoId);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(transSkull));
		glDrawElements(GL_TRIANGLES, SkullObjData.numFaces, GL_UNSIGNED_INT, (void*)0);


		glBindVertexArray(PedestalObjData.vaoId);
		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, multiTexture[7]);


		for (int i = 0; i < 3; i++) {
			glm::mat4 dupe = transPedestal;
			dupe = glm::translate(dupe, glm::vec3(i * 100.0f, 0.0f, 0.0f));
			dupe = glm::scale(dupe, glm::vec3(0.2f, 0.2f, 0.2f));//scale
			dupe = glm::rotate(dupe, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			if (i == 1)
				glUniform1i(multiTex, false);
			else
				glUniform1i(multiTex, true);
			glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
			glDrawElements(GL_TRIANGLES, PedestalObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
		}


		glUniform1i(multiTex, true);

		glBindVertexArray(FloorObjData.vaoId);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[7]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, multiTexture[7]);


		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {

				glm::mat4 dupe = transFloor;
				dupe = glm::translate(dupe, glm::vec3(i * 100.0f, -85.0f, j * 100.0f));
				dupe = glm::translate(dupe, glm::vec3(-100.0f, 0.0f, 0.0f));
				dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
				glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
			}

		}
		glUniform1i(multiTex, false);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {//ceiling

				glm::mat4 dupe = transFloor;
				dupe = glm::translate(dupe, glm::vec3(i * 100.0f, 105.0f, j * 100.0f));
				dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
				glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 2; j++) {//wall

				glm::mat4 dupe = transFloor;
				dupe = glm::translate(dupe, glm::vec3(0.0f, -85.0f, i * 100.0f));
				dupe = glm::translate(dupe, glm::vec3(-48.0f, 48.0f, -2.0f));
				dupe = glm::translate(dupe, glm::vec3(0.0f, j * 100.0f, 0.0f));
				dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
				dupe = glm::rotate(dupe, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
				glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
			}
			for (int j = 0; j < 2; j++) {//wall

				glm::mat4 dupe = transFloor;
				dupe = glm::translate(dupe, glm::vec3(0.0f, -85.0f, i * 100.0f));
				dupe = glm::translate(dupe, glm::vec3(348.0f, 48.0f, -2.0f));
				dupe = glm::translate(dupe, glm::vec3(0.0f, j * 100.0f, 0.0f));
				dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
				dupe = glm::rotate(dupe, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
				glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
			}
			for (int j = 0; j < 2; j++) {//wall

				glm::mat4 dupe = transFloor;
				dupe = glm::translate(dupe, glm::vec3(i * 100.0f, -85.0f, 0.0f));
				dupe = glm::translate(dupe, glm::vec3(0.0f, 44.0f, -48.0f));
				dupe = glm::translate(dupe, glm::vec3(0.0f, j * 100.0f, 0.0f));
				dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
				dupe = glm::rotate(dupe, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
				glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
			}
			for (int j = 0; j < 2; j++) {//wall

				glm::mat4 dupe = transFloor;
				if (i != 1) {
					dupe = glm::translate(dupe, glm::vec3(i * 100.0f, -85.0f, 0.0f));
					dupe = glm::translate(dupe, glm::vec3(0.0f, 44.0f, 350.0f));
					dupe = glm::translate(dupe, glm::vec3(0.0f, j * 100.0f, 0.0f));
					dupe = glm::scale(dupe, glm::vec3(2.2f, 2.2f, 2.2f));//scale
					dupe = glm::rotate(dupe, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
					glUniformMatrix4fv(modelTransformLoc, 1, GL_FALSE, glm::value_ptr(dupe));
					glDrawElements(GL_TRIANGLES, FloorObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
				}
			}

		}
		//glUniform1i(isSun, true);


			//--- stop drawing here ---
#pragma endregion
		glfwSwapBuffers(window);

		//listen for glfw input events
		glfwPollEvents();
	}
}


void Runner::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (firstmouse) {
		lastX = xpos;
		lastY = ypos;
		firstmouse = false;
	}

	GLfloat xOffset = xpos - lastX;
	GLfloat yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.4f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;


	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camFront = glm::normalize(front);


}

void Runner::load3dModel(GLuint texture[8], GLuint multiTexture[8], GLfloat objOffset[], ObjData& objModel, std::string filepath, int index)
{
	LoadObjFile(&objModel, filepath);
	LoadObjToMemory(&objModel, 5.0f, objOffset, texture, multiTexture, index);
	//LoadTextureData(&SkullObjData, "skull_diffuse.jpg", texture, 4);
}

void Runner::render()
{
}

void Runner::processEvents()
{
}

void Runner::update()
{

	


}

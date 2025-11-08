/*#include "SimulationManager.h"

const GLfloat SimulationManager::Buffers::vertices[] = {
	//	 COORDINATES	 /	   COLOURS	   //
	-0.5f, 0.0f,  0.5f,		0.75f, 0.2f, 1.0f,
	-0.5f, 0.0f, -0.5f,		1.0f, 0.1f, 0.3f,
	 0.5f, 0.0f, -0.5f,		0.1f, 0.5f, 1.0f,
	 0.5f, 0.0f,  0.5f,		0.89f, 0.43f, 0.234f,
	 0.0f, 0.8f,  0.0f,		0.90676f, 0.523f, 0.0f
};

const GLuint SimulationManager::Buffers::indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

bool SimulationManager::Init() {
	shaderProgram = std::make_unique<Shader>("default.vert", "default.frag");

	_VAO.Bind();	// Bind the _VAO

	_VBO.Init(Buffers::vertices, sizeof(Buffers::vertices));
	_EBO.Init(Buffers::indices, sizeof(Buffers::indices));

	_VAO.LinkAttrib(_VBO, _EBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);	// Links _VAO to VBO and the attributes
	_VAO.LinkAttrib(_VBO, _EBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	_VAO.Unbind();			// Unbind the _VAO
	_VBO.Unbind();			// Unbind the VBO
	_EBO.Unbind();			// Unbind the EBO

	uniID = glGetUniformLocation(shaderProgram->ID, "scale");

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &fboTexture);
	glBindTexture(GL_TEXTURE_2D, fboTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "ERROR: Framebuffer not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void SimulationManager::Update(float dt) {
	/* STUBBED FOR LATER USE
}

void SimulationManager::Render(int width, int height) {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, width, height);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->Activate();		// Activate the shader program

	model		= glm::mat4(1.0f);	// Objects coordinates
	view		= glm::mat4(1.0f);		// Camera Coordinates
	projection  = glm::mat4(1.0f);

	view		= glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f)); // Indicates which direction and how much to move the whole "world"
	projection	= glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f); // (Field of View, Aspect Ratio, Closet Point Visible, Furthest Point Visable)

	int modelLoc = glGetUniformLocation(shaderProgram->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(shaderProgram->ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projLoc = glGetUniformLocation(shaderProgram->ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glUniform1f(uniID, 0.4f);		// Scale of triangles 

	_VAO.Bind();					// Bind the _VAO
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0); // Draw the triangle using the EBO
	_VAO.Unbind();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SimulationManager::Resize(int w, int h) {
	this->width = w;
	this->height = h;

	glBindTexture(GL_TEXTURE_2D, fboTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void SimulationManager::Terminate() {
	_VAO.Delete();
	_VBO.Delete();
	_EBO.Delete();
	shaderProgram->Delete();
}



 NOTES:
 - z-axis is positive TOWARDS the object (us) and negative AWAY from the object (us) ~ does this mean its observer relative?
 - In terms of projection, if anything is closer than 0.1 units, or further away than 100 units, it will be CLIPPED (clipped coords using the projection matrix)
	. Easy visulisation of this for me is minecraft, game I have played since 2011, and have modded, so despite me making notes I understand this.
 - 
*/
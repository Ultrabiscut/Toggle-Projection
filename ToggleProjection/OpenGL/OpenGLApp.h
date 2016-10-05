#pragma once
class OpenGLApp
{
private:
	int m_windowWidth;
	int m_windowHeight;
	float m_angle;

	float xPos;
	float yPos;
	float zPos;
	float xAxisAngle;
	float yAxisAngle;
	float zAxisAngle;

public:
	OpenGLApp();
	~OpenGLApp();

	bool Initialize(); // initialize your opengl scene
	bool Shutdown();  // shut down your scene

	// used to setup your opengl camera and drawing area
	void SetupProjection(int width, int height);

	void UpdateProjection(bool toggle = false);

	void Prepare(float dt);
	void Render();

	void DrawCube(); //will use quads to draw  a cube
	void PositionAndRotate(float xPos, float yPos, float zPos, //will be called each game loop to set pos and change angles
		float xAngle, float yAngle, float zAngle);


	void IncrementXAxis(float value);
	void IncrementYAxis(float value);
	void IncrementZAxis(float value);

	void ShowGrid();

};


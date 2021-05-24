#ifndef __FIGURES_H__
#define __FIGURES_H__

class Cube {

	f32   width;
	f32   height;
	f32   depth;
	f32* vertices;
	unsigned int* indices;

public:
	Cube(f32 width = 1.0f, f32 height = 1.0f, f32 depth = 1.0f)
		: width(width), height(height), depth(depth),
		vertices(new f32[16 * 8]), indices(new unsigned int[6 * 6]) {
		f32 wm = width / 2.0f;
		f32 hm = height / 2.0f;
		f32 dm = depth / 2.0f;
		f32 temp[] = {
			// posiciones        colores          texturas
		   -wm,  hm,  dm,   1.0f, 0.0, 0.0,   0.0f, 1.0f,  // 0
			wm,  hm,  dm,   1.0f, 0.0, 0.0,   1.0f, 1.0f,  // 1
		   -wm, -hm,  dm,   1.0f, 0.0, 0.0,   0.0f, 0.0f,  // 2
			wm, -hm,  dm,   1.0f, 0.0, 0.0,   1.0f, 0.0f,  // 3
		   -wm,  hm, -dm,   1.0f, 0.0, 0.0,   1.0f, 1.0f,  // 4
			wm,  hm, -dm,   1.0f, 0.0, 0.0,   0.0f, 1.0f,  // 5
		   -wm, -hm, -dm,   1.0f, 0.0, 0.0,   1.0f, 0.0f,  // 6
			wm, -hm, -dm,   1.0f, 0.0, 0.0,   0.0f, 0.0f,  // 7

		   -wm,  hm,  dm,   1.0f, 0.0, 0.0,   0.0f, 0.0f,  // 8
			wm,  hm,  dm,   1.0f, 0.0, 0.0,   1.0f, 0.0f,  // 9
		   -wm, -hm,  dm,   1.0f, 0.0, 0.0,   0.0f, 0.0f,  // 10
			wm, -hm,  dm,   1.0f, 0.0, 0.0,   1.0f, 0.0f,  // 11
		   -wm,  hm, -dm,   1.0f, 0.0, 0.0,   0.0f, 1.0f,  // 12
			wm,  hm, -dm,   1.0f, 0.0, 0.0,   1.0f, 1.0f,  // 13
		   -wm, -hm, -dm,   1.0f, 0.0, 0.0,   0.0f, 1.0f,  // 14
			wm, -hm, -dm,   1.0f, 0.0, 0.0,   1.0f, 1.0f }; // 15
		for (unsigned int i = 0; i < 16 * 8; ++i) {
			vertices[i] = temp[i];
		}
		unsigned int temp2[] = {
			 0,  1,  2,   1,  2,  3,
			 8,  9, 12,   9, 12, 13,
			 1,  5,  3,   3,  5,  7,
			11, 14, 15,  10, 11, 14,
			 0,  4,  6,   0,  2,  6,
			 4,  5,  6,   5,  6,  7 };
		for (unsigned int i = 0; i < 6 * 6; ++i) {
			indices[i] = temp2[i];
		}
	}
	~Cube() {
		delete[] vertices;
		delete[] indices;
	}
	f32* getVertices() {
		return vertices;
	}
	unsigned int* getIndices() {
		return indices;
	}
	unsigned int getVSize() {
		return 16 * 8;
	}
	unsigned int getISize() {
		return 6 * 6;
	}
};

class Pyramid {
	float* vertices;
	unsigned int* indices;

public:
	Pyramid(): vertices(new float[5 * 8]), indices(new unsigned int[6 * 3]) {
		float temp[] = {
			// posiciones			 colores			texturas
		   -0.5f, 0.0f,  0.5f,	0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		   -0.5f, 0.0f, -0.5f,	0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
			0.5f, 0.0f, -0.5f,  0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
			0.5f, 0.0f,  0.5f,	0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
			0.0f, 0.8f,  0.0f,	0.92f, 0.86f, 0.76f,	0.5f, 1.0f };
		for (unsigned int i = 0; i < 5 * 8; ++i) {
			vertices[i] = temp[i];
		}
		unsigned int temp2[] = {
			 0,  1,  2,
			 0,  2,  3,
			 0,  1,  4,
		     1,  2,  4,
			 2,  3,  4,
			 3,  0,  4};
		for (unsigned int i = 0; i < 6 * 3; ++i) {
			indices[i] = temp2[i];
		}
	}
	~Pyramid() {
		delete[] vertices;
		delete[] indices;
	}
	float* getVertices() {
		return vertices;
	}
	unsigned int* getIndices() {
		return indices;
	}
	unsigned int getVSize() {
		return 5 * 8;
	}
	unsigned int getISize() {
		return 6 * 3;
	}
};

class CubeRubik {

	float   width;
	float   height;
	float   depth;
	float* vertices;
	unsigned int* indices;

public:
	CubeRubik(float width = 1.0f, float height = 1.0f, float depth = 1.0f)
		: width(width), height(height), depth(depth),
		vertices(new float[24 * 8]), indices(new unsigned int[6 * 6]) {
		float wm = width / 2.0f;
		float hm = height / 2.0f;
		float dm = depth / 2.0f;
		float temp[] = {
			// posiciones        colores          texturas
		   -wm,  hm,  dm,   0.2f, 1.0, 0.0,   0.0f, 1.0f,  // 0
			wm,  hm,  dm,   0.2f, 1.0, 0.0,   1.0f, 1.0f,  // 1
		   -wm, -hm,  dm,   0.2f, 1.0, 0.0,   0.0f, 0.0f,  // 2
			wm, -hm,  dm,   0.2f, 1.0, 0.0,   1.0f, 0.0f,  // 3
		   -wm,  hm, -dm,   1.0f, 0.0, 0.0,   1.0f, 1.0f,  // 4
			wm,  hm, -dm,   1.0f, 0.0, 0.0,   0.0f, 1.0f,  // 5
		   -wm, -hm, -dm,   1.0f, 0.0, 0.0,   1.0f, 0.0f,  // 6
			wm, -hm, -dm,   1.0f, 0.0, 0.0,   0.0f, 0.0f,  // 7

		   -wm,  hm,  dm,   0.0, 0.0, 1.0,   0.0f, 0.0f,  // 8
			wm,  hm,  dm,   1.0, 0.5, 0.2,   1.0f, 0.0f,  // 9
		   -wm, -hm,  dm,   0.0, 0.0, 1.0,   0.0f, 0.0f,  // 10
			wm, -hm,  dm,   1.0, 0.5, 0.2,   1.0f, 0.0f,  // 11
		   -wm,  hm, -dm,   0.0, 0.0, 1.0,   0.0f, 1.0f,  // 12
			wm,  hm, -dm,   1.0, 0.5, 0.2,   1.0f, 1.0f,  // 13
		   -wm, -hm, -dm,   0.0, 0.0, 1.0,   0.0f, 1.0f,  // 14
			wm, -hm, -dm,   1.0, 0.5, 0.2,   1.0f, 1.0f, // 15

		   -wm, hm, dm,	1.0f, 1.0, 1.0,	   0.0f, 1.0f,  // 16
		   wm, hm, dm,		1.0f, 1.0, 1.0,		1.0f, 1.0f,  // 17
		   -wm, -hm, dm,	1.0f, 1.0, 0.0,		 0.0f, 0.0f,  // 18
		   wm, -hm, dm,		1.0f, 1.0, 0.0,		1.0f, 0.0f,  // 19
		   -wm, hm, -dm,	1.0f, 1.0, 1.0,		1.0f, 1.0f,  // 20
		   wm, hm, -dm,		1.0f, 1.0, 1.0,		0.0f, 1.0f,  // 21
		   -wm, -hm, -dm,	1.0f, 1.0, 0.0,		1.0f, 0.0f,  // 22
		   wm, -hm, -dm,	1.0f, 1.0, 0.0,		0.0f, 0.0f, }; // 23
		for (unsigned int i = 0; i < 24 * 8; ++i) {
			vertices[i] = temp[i];
		}
		unsigned int temp2[] = {
			 0,  1,  2,   1,  2,  3,//
			13,  9, 11,  11, 15, 13,//
			18, 19, 22,  19, 22, 23,
			 4,  5,  6,   5,  6,  7,//
			 16, 17, 20, 20, 17, 21,
			 8, 10, 12,  12, 10, 14 };//
		for (unsigned int i = 0; i < 6 * 6; ++i) {
			indices[i] = temp2[i];
		}
	}
	~CubeRubik() {
		delete[] vertices;
		delete[] indices;
	}
	float* getVertices() {
		return vertices;
	}
	unsigned int* getIndices() {
		return indices;
	}
	unsigned int getVSize() {
		return 24 * 8;
	}
	unsigned int getISize() {
		return 6 * 6;
	}
};

#endif

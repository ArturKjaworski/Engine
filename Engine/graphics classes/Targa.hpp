/*
 *	Targa.h
 */

typedef struct {
	GLuint bpp;		// iloœæ bitów na piksel
	GLuint _width;	// rozmiary w pikselach
	GLuint _height;
} TARGAINFO;

// Funkcje
GLubyte *LoadTGAImage(char *filename, TARGAINFO *info);
bool LoadTGATexture(char *filename);
bool LoadTGAMipmap(char *filename);



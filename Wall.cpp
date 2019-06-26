#include "Wall.h"

Wall::Wall(GLint x)
{
    //ctor
    m_vertexID=m_indicesID=m_normalBuffer=m_texCoordBuffer=0;
    //inicializace textur a vertexu
    loadTexture("data/textures/stonewall.tga");

    Vertex vertices[] = {
        //kvadr steny
        //1stena
		{ {x, 0, -x},  { 0.5, 0.5, 0.5},  {0.0, 0.0, -1.0} ,   { 0.0, 0.0}   }, // 0
		{ {-x,0, -x}, { 0.5, 0.5, 0.5} ,  {0.0, 0.0, -1.0},  { 0, 1.0}  }, // 1
		{ {x, 2*x,  -x}, { 0.5, 0.5, 0.5},   {0.0, 0.0, -1.0},    { 1.0, 0.0} }, // 2
		{ {-x, 2*x, -x},{ 0.5, 0.5, 0.5},{0.0, 0.0, -1.0}, { 1.0, 1.0}  }, // 3

		//2st�na
        { {-x, 0, -x},  { 0.5, 0.5, 0.5},  {-1.0, 0.0, 0.0} ,   { 0.0, 0.0}   }, // 4
		{ {-x,0, x}, { 0.5, 0.5, 0.5} ,  {-1.0, 0.0, 0.0},  { 0, 1.0}  }, // 5
		{ {-x, 2*x,  -x}, { 0.5, 0.5, 0.5},   {-1.0, 0.0, 0.0},    { 1.0, 0.0} }, // 6
		{ {-x, 2*x, x},{ 0.5, 0.5, 0.5},{-1.0, 0.0, 0.0}, { 1.0, 1.0}  }, // 7


        //3st�na
        { {x, 0, x},  { 0.5, 0.5, 0.5},  {0.0, 0.0, 1.0} ,   { 0.0, 0.0}   }, // 8
		{ {-x,0, x}, { 0.5, 0.5, 0.5} ,  {0.0, 0.0, 1.0} ,  { 0, 1.0}  }, // 9
		{ {x, 2*x,  x}, { 0.5, 0.5, 0.5}, {0.0, 0.0, 1.0} ,    { 1.0, 0.0} }, // 10
		{ {-x, 2*x, x},{ 0.5, 0.5, 0.5},{0.0, 0.0, 1.0}, { 1.0, 1.0}  }, // 11

        //4st�na
        { {x, 0, -x},  { 0.5, 0.5, 0.5},     {1.0, 0.0, 0.0} , { 0.0, 0.0}   }, // 12
		{ {x,0, x}, { 0.5, 0.5, 0.5} ,     {1.0, 0.0, 0.0} ,  { 0, 1.0}  }, // 13
		{ {x, 2*x,  -x}, { 0.5, 0.5, 0.5},   {1.0, 0.0, 0.0} , { 1.0, 0.0} }, // 14
		{ {x, 2*x, x},{ 0.5, 0.5, 0.5},    {1.0, 0.0, 0.0},    { 1.0, 1.0}  }, // 15

		//5st�na
        { {-x, 2*x, x},  { 0.5, 0.5, 0.5},     {0.0, 1.0, 0.0} , { 0.0, 0.0}   }, // 16
		{ {x,2*x, x}, { 0.5, 0.5, 0.5} ,    {0.0, 1.0, 0.0},  { 0, 1.0}  }, //17
		{ {-x, 2*x,  -x}, { 0.5, 0.5, 0.5},   {0.0, 1.0, 0.0} , { 1.0, 0.0} }, // 18
		{ {x, 2*x, -x},{ 0.5, 0.5, 0.5},   {0.0, 1.0, 0.0},    { 1.0, 1.0}  }, // 19

                            };


        GLubyte indices[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};


    // vygenerujeme identifikator bufferu
	glGenBuffers(1, &m_vertexID);
	// aktivujeme buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);

	// zaalokujeme pamet pro vrcholy a barvy
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), 0, GL_STATIC_DRAW);

	// naplnime pamet
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	// definujeme pointery na vrcholy a barvy
	glVertexPointer(3, GL_INT, sizeof(Vertex), 0);
	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(GL_INT)));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(GL_INT)+3*sizeof(GL_FLOAT)) );
    glTexCoordPointer(2,GL_FLOAT, sizeof(Vertex),(void*)(3*sizeof(GL_INT)+(5*sizeof(GL_FLOAT))) );


	// vygenerujeme identifikator bufferu
	glGenBuffers(1, &m_indicesID);
	// aktivujeme buffer pro indexy
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesID);
	// zaalokujeme pamet
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), 0, GL_STATIC_DRAW);
	// naplnime pamet
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);


	glGenBuffers(1, &m_normalBuffer);
    glBindBuffer(GL_NORMAL_ARRAY, m_normalBuffer); //Bind the vertex buffer
    glBufferData(GL_NORMAL_ARRAY, sizeof(vertices), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_NORMAL_ARRAY, 0, sizeof(vertices), vertices);



	// aktivujeme pole vrcholu,barev,normal,textur
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

}




void Wall::loadTexture(string texture)
{
m_surfaceTexture = new TargaImage();

    	if (!m_surfaceTexture->load(texture))
    {
        std::cerr << "Could not load the wall texture" << std::endl;
    }

    glGenTextures(1, &m_texCoordBuffer);
	glBindTexture(GL_TEXTURE_2D, m_texCoordBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // opakovani textury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_surfaceTexture->getWidth(),m_surfaceTexture->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_surfaceTexture->getImageData());
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST); // vylepseni zobrazovani
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
    glEnable(GL_TEXTURE_2D);
}

void Wall::draw()
{
    //nabindovani bufferu
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesID);
	glBindBuffer(GL_NORMAL_ARRAY, m_normalBuffer);
	glBindTexture(GL_TEXTURE_2D, m_texCoordBuffer);

	glVertexPointer(3, GL_INT, sizeof(Vertex), 0);
	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(GL_INT)));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(GL_INT)+3*sizeof(GL_FLOAT)) );
	glTexCoordPointer(2,GL_FLOAT, sizeof(Vertex),(void*)(3*sizeof(GL_INT)+(3*sizeof(GL_FLOAT))+(3*sizeof(GL_FLOAT))) );

    //vykreslen� sten zdi
    glDrawElements(GL_TRIANGLE_STRIP,4, GL_UNSIGNED_BYTE, 0);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void*)(4*sizeof(GLubyte)));
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void*)(8*sizeof(GLubyte)));
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void*)(12*sizeof(GLubyte)));
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void*)(16*sizeof(GLubyte)));
}

Wall::~Wall()
{
    //dtor
    glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDeleteBuffers(1,  &m_vertexID);
	glDeleteBuffers(1,  &m_indicesID);
	glDeleteBuffers(1,  &m_normalBuffer);
	glDeleteBuffers(1,  &m_texCoordBuffer);
	delete m_surfaceTexture;
}

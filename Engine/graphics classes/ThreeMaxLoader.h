#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <stdio.h>

#define MAX_VERTICES 80000 // Max number of vertices (for each object)
#define MAX_POLYGONS 80000 // Max number of polygons (for each object)
#define MAX_VERTEX   80000


// Our vertex type
typedef struct{
    float x,y,z;
}vertex_type;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
    int a,b,c;
}polygon_type;

typedef struct{
    float u,v;
}mapcoord_type;

// The object type
typedef struct {
	char name[20];

	int vertices_qty;
    int polygons_qty;

    vertex_type vertex[MAX_VERTICES];
    polygon_type polygon[MAX_POLYGONS];
    mapcoord_type mapcoord[MAX_VERTEX];

} obj_type, *obj_type_ptr;


class CThreeMaxLoader
{
public:
	CThreeMaxLoader();
	virtual ~CThreeMaxLoader();

	static char Load3DS (obj_type_ptr p_object, char *p_filename)
	{
		int i; //Index variable

		FILE *l_file; //File pointer

		unsigned short l_chunk_id; //Chunk identifier
		unsigned int l_chunk_lenght; //Chunk lenght

		unsigned char l_char; //Char variable
		unsigned short l_qty; //Number of elements in each chunk

		unsigned short l_face_flags; //Flag that stores some face information

		if ((l_file=fopen (p_filename, "rb"))== NULL) return 0; //Open the file

		while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file
		{
			//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

			fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
			//printf("ChunkID: %x\n",l_chunk_id);
			fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
			//printf("ChunkLenght: %x\n",l_chunk_lenght);

			switch (l_chunk_id)
			{

				case 0x4d4d:
				break;

				case 0x3d3d:
				break;

				case 0x4000:
					i=0;
					do
					{
						fread (&l_char, 1, 1, l_file);
						p_object->name[i]=l_char;
						i++;
					}while(l_char != '\0' && i<20);
				break;

				case 0x4100:
				break;

				case 0x4110:
					fread (&l_qty, sizeof (unsigned short), 1, l_file);
					p_object->vertices_qty = l_qty;
					//printf("Number of vertices: %d\n",l_qty);
					for (i=0; i<l_qty; i++)
					{

						fread (&p_object->vertex[i].x, sizeof(float), 1, l_file);
 						//printf("Vertices list x: %f\n",p_object->vertex[i].x);

						fread (&p_object->vertex[i].y, sizeof(float), 1, l_file);
 						//printf("Vertices list y: %f\n",p_object->vertex[i].y);

						fread (&p_object->vertex[i].z, sizeof(float), 1, l_file);
 						//printf("Vertices list z: %f\n",p_object->vertex[i].z);

						//Insert into the database

					}
					break;

				case 0x4120:
					fread (&l_qty, sizeof (unsigned short), 1, l_file);
					p_object->polygons_qty = l_qty;
					//printf("Number of polygons: %d\n",l_qty);
					for (i=0; i<l_qty; i++)
					{
						fread (&p_object->polygon[i].a, sizeof (unsigned short), 1, l_file);
						//printf("Polygon point a: %d\n",p_object->polygon[i].a);
						fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
						//printf("Polygon point b: %d\n",p_object->polygon[i].b);
						fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
						//printf("Polygon point c: %d\n",p_object->polygon[i].c);
						fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
						//printf("Face flags: %x\n",l_face_flags);
					}
					break;

				//------------- TRI_MAPPINGCOORS ------------
				// Description: Vertices list
				// Chunk ID: 4140 (hex)
				// Chunk Lenght: 1 x unsigned short (number of mapping points)
				//             + 2 x float (mapping coordinates) x (number of mapping points)
				//             + sub chunks
				//-------------------------------------------
				//----------- Skip unknow chunks ------------
				//We need to skip all the chunks that currently we don't use
				//We use the chunk lenght information to set the file pointer
				//to the same level next chunk
				//-------------------------------------------
				case 0x4140 :
                    fread(&l_qty,sizeof(unsigned short),1,l_file);
                    for(i=0;i<l_qty;i++)
                        {
                            fread (&p_object->mapcoord[i].u,sizeof(float),1,l_file);
                            fread (&p_object->mapcoord[i].v,sizeof(float),1,l_file);
                        }
                break;

				default:
					 fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
			}
		}

		fclose (l_file);
		return (1);
	}

};
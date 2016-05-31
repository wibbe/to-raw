
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"


void process_file(char * infile, char * outfile)
{
	FILE * in = fopen(infile, "r");
	if (!in)
		return;



	fclose(in);
}


int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s <input file> <output filename>\n", argv[0]);
		return 1;
	}

	char * infile = argv[1];
	char * outfile = argv[2];

	int width = 0;
	int height = 0;
	int components = 0;

	unsigned char * data = stbi_load(infile, &width, &height, &components, STBI_default);
	if (!data)
	{
		fprintf(stderr, "Could not open file %s\n", infile);
		return 1;
	}

	FILE * out = fopen(outfile, "wb");

	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			int gray = 0;

			switch (components)
			{
				case STBI_grey:
					gray = data[y * width + x];
					break;

				case STBI_grey_alpha:
					gray = data[y * (width * 2) + (x * 2)];
					break;

				case STBI_rgb:
					{
						int idx = y * (width * 3) + (x * 3);
						gray = (data[idx + 0] + data[idx + 1] + data[idx + 2]) / 3;
					}
					break;
   			
   			case STBI_rgb_alpha:
 					{
						int idx = y * (width * 4) + (x * 4);
						gray = (data[idx + 0] + data[idx + 1] + data[idx + 2]) / 3;
					}
   				break;
			}

			fputc(gray, out);
		}

	fclose(out);
	printf("Image converted and saved to %s\n", outfile);

	return 0;
}
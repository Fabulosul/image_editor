//Copyright Tudor Robert-Fabian 312CAa 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 256

typedef struct {
	char magic_word[3];
	int width;
	int height;
	int **matrix;
	int x1, x2, y1, y2;
} image;

void delete_photo(image *photo)
{
	if (photo->matrix) {
		for (int i = 0; i < photo->height; i++)
			free(photo->matrix[i]);
		free(photo->matrix);
		photo->matrix = NULL;
	}
}

void load(image *photo, char *filepath)
{
	char buffer[250]; int maxvalue;
	if (photo->matrix)
		delete_photo(photo);
	FILE *f = fopen(filepath, "rb");
	printf("Loaded %s\n", filepath); fgets(buffer, 260, f);
	if (strncmp(buffer, "#", 1) == 0)
		fscanf(f, "%s", photo->magic_word);
	else
		sscanf(buffer, "%s", photo->magic_word);
	fgets(buffer, 260, f);
	if (strncmp(buffer, "#", 1) == 0) {
		fscanf(f, "%d", &photo->width); fscanf(f, "%d", &photo->height);
	} else {
		if (sscanf(buffer, "%d %d", &photo->width, &photo->height) == 2)
			sscanf(buffer, "%d %d", &photo->width, &photo->height);
	}
	fscanf(f, "%d\n", &maxvalue);
	if (strcmp(photo->magic_word, "P1") == 0 ||
		strcmp(photo->magic_word, "P2") == 0 ||
		strcmp(photo->magic_word, "P4") == 0 ||
		strcmp(photo->magic_word, "P5") == 0) {
		photo->matrix = (int **)malloc((photo->height) * sizeof(int *));
		for (int i = 0; i < photo->height; i++) {
			photo->matrix[i] = (int *)malloc((photo->width) * sizeof(int));
			if (!photo->matrix[i]) {
				fprintf(stderr, "malloc() for line %d failed\n", i);
				for (int j = 0; j < i; j++)
					free(photo->matrix[j]);
				free(photo->matrix); exit(-1);
			}
		}
		if (strcmp(photo->magic_word, "P1") == 0 ||
			strcmp(photo->magic_word, "P2") == 0) {
			for (int i = 0; i < photo->height; i++) {
				for (int j = 0; j < photo->width; j++)
					fscanf(f, "%d", &photo->matrix[i][j]);
			}
		} else {
			for (int i = 0; i < photo->height; i++) {
				for (int j = 0; j < photo->width; j++) {
					unsigned char x;
					fread(&x, sizeof(unsigned char), 1, f);
					photo->matrix[i][j] = (int)x;
				}
			}
		}
	}
	if (strcmp(photo->magic_word, "P3") == 0 ||
		strcmp(photo->magic_word, "P6") == 0) {
		photo->matrix = (int **)malloc((photo->height) * sizeof(int *));
		if (!photo->matrix) {
			fprintf(stderr, "malloc() for matrix failed\n"); exit(-1);
		}
		for (int i = 0; i < photo->height; i++) {
			photo->matrix[i] = (int *)malloc((3 * photo->width) * sizeof(int));
			if (!photo->matrix[i]) {
				fprintf(stderr, "malloc() for line %d failed\n", i);
				for (int j = 0; j < i; j++)
					free(photo->matrix[j]);
				free(photo->matrix); exit(-1);
			}
		}
		if (strcmp(photo->magic_word, "P6") == 0) {
			for (int i = 0; i < photo->height; i++) {
				for (int j = 0; j < 3 * photo->width; j++) {
					unsigned char x;
					fread(&x, sizeof(unsigned char), 1, f);
					photo->matrix[i][j] = round(x);
				}
			}
		} else {
			for (int i = 0; i < photo->height; i++) {
				for (int j = 0; j < 3 * photo->width; j++)
					fscanf(f, "%d", &photo->matrix[i][j]);
			}
		}
	}
	photo->x1 = -1; photo->y1 = -1; photo->x2 = -1; photo->y2 = -1; fclose(f);
}

void save(image *photo, char *file_name, char *type)
{
	if (strcmp(photo->magic_word, "P3") == 0 ||
		strcmp(photo->magic_word, "P6") == 0) {
		if (strncmp(type, "binary", 6) == 0) {
			FILE *g = fopen(file_name, "wb");
			if (!g) {
				fprintf(stderr, "Eroare la deschidere fisier\n");
				exit(-1);
			}
			fprintf(g, "P6\n");
			fprintf(g, "%d %d\n", photo->width, photo->height);
			fprintf(g, "255\n");
			for (int i = 0; i < photo->height; i++) {
				for (int j = 0; j < 3 * photo->width; j++) {
					unsigned char x = (unsigned char)photo->matrix[i][j];
					fwrite(&x, sizeof(unsigned char), 1, g);
				}
			}
			fclose(g);
		}
		if (strncmp(type, "ascii", 5) == 0) {
			FILE *g = fopen(file_name, "w");
			if (!g) {
				fprintf(stderr, "Eroare la deschidere fisier\n");
				exit(-1);
			}
			fprintf(g, "P3\n");
			fprintf(g, "%d %d\n", photo->width, photo->height);
			fprintf(g, "255\n");
			for (int i = 0; i < photo->height; i++) {
				for (int j = 0; j < 3 * photo->width; j++)
					fprintf(g, "%d ", photo->matrix[i][j]);
				fprintf(g, "\n");
			}
			fclose(g);
		}
	} else {
		if (strncmp(type, "binary", 6) == 0) {
			FILE *g = fopen(file_name, "wb");
			if (!g) {
				fprintf(stderr, "Eroare la deschidere fisier\n");
				exit(-1);
			}
			fprintf(g, "P5\n");
			fprintf(g, "%d %d\n", photo->width, photo->height);
			fprintf(g, "255\n");
			for (int i = 0; i < photo->height; i++) {
				for (int j = 0; j < photo->width; j++) {
					unsigned char x = (unsigned char)photo->matrix[i][j];
					fwrite(&x, sizeof(unsigned char), 1, g);
				}
			}
			fclose(g);
		}
		if (strncmp(type, "ascii", 5) == 0) {
			FILE *g = fopen(file_name, "w");
			if (!g) {
				fprintf(stderr, "Eroare la deschidere fisier\n");
				exit(-1);
			}
			fprintf(g, "P2\n");
			fprintf(g, "%d %d\n", photo->width, photo->height);
			fprintf(g, "255\n");
			for (int i = 0; i < photo->height; i++) {
				for (int j = 0; j < photo->width; j++)
					fprintf(g, "%d ", photo->matrix[i][j]);
				fprintf(g, "\n");
			}
			fclose(g);
		}
	}
	printf("Saved %s\n", file_name);
}

void print(image *photo)
{
	for (int i = 2; i < 4; i++) {
		for (int j = 0; j < 3 * photo->width; j++)
			printf("%d ", photo->matrix[i][j]);
		printf("\n");
	}
}

void select_all(image *photo)
{
	if (!photo->matrix) {
		printf("No image loaded\n");
	} else {
		printf("Selected ALL\n");
		photo->x1 = 0;
		photo->y1 = 0;
		photo->y2 = photo->height - 1;
		if (strcmp(photo->magic_word, "P3") == 0 ||
			strcmp(photo->magic_word, "P6") == 0)
			photo->x2 = 3 * photo->width - 1;
		else
			photo->x2 = photo->width - 1;
	}
}

void select_pixels(image *photo, int x1, int y1, int x2, int y2)
{
	if (x1 > x2) {
		int aux = x1;
		x1 = x2;
		x2 = aux;
	}
	if (y1 > y2) {
		int aux = y1;
		y1 = y2;
		y2 = aux;
	}
	if (!photo->matrix) {
		printf("No image loaded\n");
	} else {
		if (strcmp(photo->magic_word, "P3") == 0 ||
			strcmp(photo->magic_word, "P6") == 0) {
			if (x1 < 0 || y1 < 0 || x2 > photo->width ||
				y2 > photo->height || x1 == x2 || y1 == y2) {
				printf("Invalid set of coordinates\n");
			} else {
				printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
				photo->x1 = 3 * x1;
				photo->x2 = 3 * x2 - 1;
				photo->y1 = y1;
				photo->y2 = y2 - 1;
			}
		} else {
			if (x1 < 0 || y1 < 0 || x2 > photo->width ||
				y2 > photo->height || x1 == x2 || y1 == y2) {
				printf("Invalid set of coordinates\n");
			} else {
				printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
				photo->x1 = x1;
				photo->x2 = x2 - 1;
				photo->y1 = y1;
				photo->y2 = y2 - 1;
			}
		}
	}
}

void crop(image *photo)
{
	if (!photo->matrix)
		printf("No image loaded\n");
	else
		printf("Image cropped\n");
	int new_height = photo->y2 - photo->y1 + 1;
	int new_width = photo->x2 - photo->x1 + 1;

	int **new_matrix = (int **)malloc((new_height) * sizeof(int *));
	if (!new_matrix) {
		fprintf(stderr, "malloc() for matrix failed\n");
		exit(-1);
	}

	for (int i = 0; i < new_height; i++) {
		new_matrix[i] = (int *)malloc((new_width) * sizeof(int));
		if (!new_matrix[i]) {
			fprintf(stderr, "malloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(new_matrix[j]);
			free(new_matrix);
			exit(-1);
		}
	}

	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++)
			new_matrix[i][j] = photo->matrix[photo->y1 + i][photo->x1 + j];
	}

	for (int i = 0; i < photo->height; i++)
		free(photo->matrix[i]);
	free(photo->matrix);
	photo->matrix = NULL;

	photo->matrix = new_matrix;
	if (strcmp(photo->magic_word, "P3") == 0 ||
		strcmp(photo->magic_word, "P6") == 0)
		photo->width = (new_width) / 3;
	else
		photo->width = new_width;
	photo->height = new_height;
	photo->x1 = 0;
	photo->y1 = 0;
	photo->x2 = new_width - 1;
	photo->y2 = new_height - 1;
}

void sharpen(image *photo)
{
	int **new_matrix = (int **)malloc((photo->height) * sizeof(int *));
	if (!new_matrix) {
		fprintf(stderr, "malloc() for matrix failed\n");
		new_matrix = NULL;
		exit(-1);
	}

	for (int i = 0; i < photo->height; i++) {
		new_matrix[i] = (int *)malloc((3 * photo->width) * sizeof(int));
		if (!new_matrix[i]) {
			fprintf(stderr, "malloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(new_matrix[j]);
			free(new_matrix);
			exit(-1);
		}
	}

	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < 3 * photo->width; j++)
			new_matrix[i][j] = photo->matrix[i][j];
	}
	for (int i = photo->y1; i <= photo->y2; i++) {
		for (int j = photo->x1; j <= photo->x2; j++) {
			if (i > 0 && i < photo->height - 1 &&
				j > 2 && j < 3 * photo->width - 3) {
				photo->matrix[i][j] = (new_matrix[i][j]) * 5 -
										new_matrix[i - 1][j] -
										new_matrix[i][j - 3] -
										new_matrix[i][j + 3] -
										new_matrix[i + 1][j];
				if (photo->matrix[i][j] < 0)
					photo->matrix[i][j] = 0;
				if (photo->matrix[i][j] > 255)
					photo->matrix[i][j] = 255;
			}
		}
	}
	for (int i = 0; i < photo->height; i++)
		free(new_matrix[i]);
	free(new_matrix);
}

void edge(image *photo)
{
	int **new_matrix = (int **)malloc((photo->height) * sizeof(int *));
	if (!new_matrix) {
		fprintf(stderr, "malloc() for matrix failed\n");
		new_matrix = NULL;
		exit(-1);
	}

	for (int i = 0; i < photo->height; i++) {
		new_matrix[i] = (int *)malloc((3 * photo->width) * sizeof(int));
		if (!new_matrix[i]) {
			fprintf(stderr, "malloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(new_matrix[j]);
			free(new_matrix);
			exit(-1);
		}
	}

	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < 3 * photo->width; j++)
			new_matrix[i][j] = photo->matrix[i][j];
	}

	for (int i = photo->y1; i <= photo->y2; i++) {
		for (int j = photo->x1; j <= photo->x2; j++) {
			if (i > 0 && i < photo->height - 1 && j > 2 &&
				j < 3 * photo->width - 3) {
				photo->matrix[i][j] = new_matrix[i][j] * 8 -
									  new_matrix[i - 1][j - 3] -
									  new_matrix[i - 1][j] -
									  new_matrix[i - 1][j + 3] -
									  new_matrix[i][j - 3] -
									  new_matrix[i][j + 3] -
									  new_matrix[i + 1][j - 3] -
									  new_matrix[i + 1][j] -
									  new_matrix[i + 1][j + 3];
				if (photo->matrix[i][j] < 0)
					photo->matrix[i][j] = 0;
				if (photo->matrix[i][j] > 255)
					photo->matrix[i][j] = 255;
			}
		}
	}

	for (int i = 0; i < photo->height; i++)
		free(new_matrix[i]);
	free(new_matrix);
}

void blur(image *photo)
{
	int **new_matrix = (int **)malloc((photo->height) * sizeof(int *));
	if (!new_matrix) {
		fprintf(stderr, "malloc() for matrix failed\n");
		new_matrix = NULL;
		exit(-1);
	}

	for (int i = 0; i < photo->height; i++) {
		new_matrix[i] = (int *)malloc((3 * photo->width) * sizeof(int));
		if (!new_matrix[i]) {
			fprintf(stderr, "malloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(new_matrix[j]);
			free(new_matrix);
			exit(-1);
		}
	}

	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < 3 * photo->width; j++)
			new_matrix[i][j] = photo->matrix[i][j];
	}

	for (int i = photo->y1; i <= photo->y2; i++) {
		for (int j = photo->x1; j <= photo->x2; j++) {
			if (i > 0 && i < photo->height - 1 &&
				j > 2 && j < 3 * photo->width - 3) {
				photo->matrix[i][j] = new_matrix[i - 1][j - 3] +
									  new_matrix[i - 1][j] +
									  new_matrix[i - 1][j + 3] +
									  new_matrix[i][j - 3] +
									  new_matrix[i][j] +
									  new_matrix[i][j + 3] +
									  new_matrix[i + 1][j - 3] +
									  new_matrix[i + 1][j] +
									  new_matrix[i + 1][j + 3];
				photo->matrix[i][j] /= 9;
				if (photo->matrix[i][j] < 0)
					photo->matrix[i][j] = 0;
				if (photo->matrix[i][j] > 255)
					photo->matrix[i][j] = 255;
			}
		}
	}

	for (int i = 0; i < photo->height; i++)
		free(new_matrix[i]);
	free(new_matrix);
}

void gaussian_blur(image *photo)
{
	int **new_matrix = (int **)malloc((photo->height) * sizeof(int *));
	if (!new_matrix) {
		fprintf(stderr, "malloc() for matrix failed\n");
		new_matrix = NULL;
		exit(-1);
	}

	for (int i = 0; i < photo->height; i++) {
		new_matrix[i] = (int *)malloc((3 * photo->width) * sizeof(int));
		if (!new_matrix[i]) {
			fprintf(stderr, "malloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(new_matrix[j]);
			free(new_matrix);
			exit(-1);
		}
	}

	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < 3 * photo->width; j++)
			new_matrix[i][j] = photo->matrix[i][j];
	}

	for (int i = photo->y1; i <= photo->y2; i++) {
		for (int j = photo->x1; j <= photo->x2; j++) {
			if (i > 0 && i < photo->height - 1 &&
				j > 2 && j < 3 * photo->width - 3) {
				photo->matrix[i][j] = new_matrix[i - 1][j - 3] +
									  new_matrix[i - 1][j] * 2 +
									  new_matrix[i - 1][j + 3] +
									  new_matrix[i][j - 3] * 2 +
									  new_matrix[i][j] * 4 +
									  new_matrix[i][j + 3] * 2 +
									  new_matrix[i + 1][j - 3] +
									  new_matrix[i + 1][j] * 2 +
									  new_matrix[i + 1][j + 3];
				photo->matrix[i][j] /= 16;
				if (photo->matrix[i][j] < 0)
					photo->matrix[i][j] = 0;
				if (photo->matrix[i][j] > 255)
					photo->matrix[i][j] = 255;
			}
		}
	}

	for (int i = 0; i < photo->height; i++)
		free(new_matrix[i]);
	free(new_matrix);
}

void histogram(image *photo, int x, int y)
{
	int *frecventa = (int *)malloc(256 * sizeof(int));
	for (int i = 0; i <= 255; i++)
		frecventa[i] = 0;

	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < photo->width; j++)
			frecventa[photo->matrix[i][j]]++;
	}

	int area = 256 / y;
	long long *bins = (long long *)malloc(y * sizeof(long long));

	for (int i = 0; i < y; i++) {
		long long s = 0;
		for (int j = 0; j < area; j++)
			s += frecventa[area * i + j];
		bins[i] = s;
	}

	long long max = -1;
	for (int i = 0; i < y; i++) {
		if (bins[i] > max)
			max = bins[i];
	}

	for (int i = 0; i < y; i++)
		bins[i] = (bins[i] * x) / max;

	for (int i = 0; i < y; i++) {
		printf("%lli\t|\t", bins[i]);
		for (int j = 0; j < bins[i]; j++)
			printf("*");
		printf("\n");
	}

	free(frecventa);
	free(bins);
}

int clamp(int x)
{
	if (x > 255)
		return 255;
	if (x < 0)
		return 0;
	return x;
}

void equalize(image *photo)
{
	double area = (double)photo->height * photo->width;

	int *frecventa = (int *)malloc(256 * sizeof(int));
	int *sumafrecventa = (int *)malloc(256 * sizeof(int));

	for (int i = 0; i < 256; i++)
		frecventa[i] = 0;
	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < photo->width; j++)
			frecventa[photo->matrix[i][j]]++;
	}

	double s = 0;
	for (int i = 0; i < 256; i++) {
		s += frecventa[i];
		sumafrecventa[i] = s;
	}

	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < photo->width; j++)
			photo->matrix[i][j] = clamp(round((double)((255 *
								  sumafrecventa[photo->matrix[i][j]]) /
								  area)));
	}

	free(frecventa);
	free(sumafrecventa);
}

void rotate_90_photo2(image *photo)
{
	int **new_matrix = (int **)malloc((photo->width) * sizeof(int *));
	if (!new_matrix) {
		fprintf(stderr, "malloc() for matrix failed\n");
		new_matrix = NULL;
		exit(-1);
	}

	for (int i = 0; i < photo->width; i++) {
		new_matrix[i] = (int *)malloc((photo->height) * sizeof(int));
		if (!new_matrix[i]) {
			fprintf(stderr, "malloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(new_matrix[j]);
			free(new_matrix);
			exit(-1);
		}
	}

	for (int i = 0; i < photo->width; i++) {
		for (int j = 0; j < photo->height; j++)
			new_matrix[i][j] = photo->matrix[photo->height - 1 - j][i];
	}

	for (int i = 0; i < photo->height; i++)
		free(photo->matrix[i]);
	free(photo->matrix);

	photo->matrix = new_matrix;

	int aux = photo->width;
	photo->width = photo->height;
	photo->height = aux;

	aux = photo->x1;
	photo->x1 = photo->y1;
	photo->y1 = aux;

	aux = photo->x2;
	photo->x2 = photo->y2;
	photo->y2 = aux;
}

void rotate_90_photo(image *photo)
{
	if (!photo->matrix)
		printf("No image loaded\n");
	if (strcmp(photo->magic_word, "P3") == 0 ||
		strcmp(photo->magic_word, "P6") == 0) {
		int **matrix_r = (int **)malloc(photo->height * sizeof(int *));
		int **matrix_g = (int **)malloc(photo->height * sizeof(int *));
		int **matrix_b = (int **)malloc(photo->height * sizeof(int *));
		if (!matrix_r || !matrix_g || !matrix_b) {
			fprintf(stderr, "malloc() for matrix failed\n"); exit(-1);
		}
		for (int i = 0; i < photo->height; i++) {
			matrix_r[i] = (int *)malloc(photo->width * sizeof(int));
			if (!matrix_r[i]) {
				fprintf(stderr, "malloc() for line %d failed\n", i);
				for (int j = 0; j < i; j++)
					free(matrix_r[j]);
				free(matrix_r); exit(-1);
			}
		}
		for (int i = 0; i < photo->height; i++) {
			matrix_g[i] = (int *)malloc(photo->width * sizeof(int));
			if (!matrix_g[i]) {
				fprintf(stderr, "malloc() for line %d failed\n", i);
				for (int j = 0; j < i; j++)
					free(matrix_g[j]);
				free(matrix_g); exit(-1);
			}
		}
		for (int i = 0; i < photo->height; i++) {
			matrix_b[i] = (int *)malloc(photo->width * sizeof(int));
			if (!matrix_b[i]) {
				fprintf(stderr, "malloc() for line %d failed\n", i);
				for (int j = 0; j < i; j++)
					free(matrix_b[j]);
				free(matrix_b); exit(-1);
			}
		}
		for (int i = 0; i < photo->height; i++) {
			for (int j = 0; j < photo->width; j++) {
				matrix_r[i][j] = photo->matrix[i][3 * j];
				matrix_g[i][j] = photo->matrix[i][3 * j + 1];
				matrix_b[i][j] = photo->matrix[i][3 * j + 2];
			}
		}
		delete_photo(photo);
		int **new_matrix = (int **)malloc(photo->width * sizeof(int *));
		if (!new_matrix) {
			fprintf(stderr, "malloc() for matrix failed\n");
			new_matrix = NULL; exit(-1);
		}
		for (int i = 0; i < photo->width; i++) {
			new_matrix[i] = (int *)malloc((3 * photo->height) * sizeof(int));
			if (!new_matrix[i]) {
				fprintf(stderr, "malloc() for line %d failed\n", i);
				for (int j = 0; j < i; j++)
					free(new_matrix[j]);
				free(new_matrix); exit(-1);
			}
		}
		for (int i = 0; i < photo->width; i++) {
			for (int j = 0; j < photo->height; j++) {
				new_matrix[i][3 * j] = matrix_r[photo->height - 1 - j][i];
				new_matrix[i][3 * j + 1] = matrix_g[photo->height - 1 - j][i];
				new_matrix[i][3 * j + 2] = matrix_b[photo->height - 1 - j][i];
			}
		}
		for (int i = 0; i < photo->height; i++) {
			free(matrix_r[i]); free(matrix_g[i]); free(matrix_b[i]);
		}
		free(matrix_r); free(matrix_g); free(matrix_b);
		photo->matrix = new_matrix; int aux = photo->width;
		photo->width = photo->height; photo->height = aux;
		photo->x2 = 3 * photo->width - 1; photo->y2 = photo->height - 1;
	} else {
		rotate_90_photo2(photo);
	}
}

void rotate_90_right2(image *photo)
{
	int **new_matrix = (int **)malloc(photo->height * sizeof(int *));
	if (!new_matrix) {
		fprintf(stderr, "malloc() for matrix failed\n");
		exit(-1);
	}
	for (int i = 0; i < photo->height; i++) {
		new_matrix[i] = (int *)malloc(photo->width * sizeof(int));
		if (!new_matrix[i]) {
			fprintf(stderr, "malloc() for line %d failed\n", i);
			for (int j = 0; j < i; j++)
				free(new_matrix[j]);
			free(new_matrix);
			exit(-1);
		}
	}

	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < photo->width; j++)
			new_matrix[i][j] = photo->matrix[i][j];
	}

	for (int i = photo->y1; i <= photo->y2; i++) {
		for (int j = photo->x1; j <= photo->x2; j++)
			photo->matrix[i][j] = new_matrix[photo->y2 +
									photo->x1 - j][photo->x1 -
									photo->y1 + i];
	}

	for (int i = 0; i < photo->height; i++)
		free(new_matrix[i]);
	free(new_matrix);
}

void rotate_90_right(image *photo)
{
	if (!photo->matrix)
		printf("No image loaded\n");
	if (strcmp(photo->magic_word, "P3") == 0 ||
		strcmp(photo->magic_word, "P6") == 0) {
		int **matrix_r = (int **)malloc(photo->height * sizeof(int *));
		int **matrix_g = (int **)malloc(photo->height * sizeof(int *));
		int **matrix_b = (int **)malloc(photo->height * sizeof(int *));
		if (!matrix_r || !matrix_g || !matrix_b)
			fprintf(stderr, "malloc() for matrix failed\n");
		for (int i = 0; i < photo->height; i++) {
			matrix_r[i] = (int *)malloc(photo->width * sizeof(int));
			if (!matrix_r[i]) {
				fprintf(stderr, "malloc() for line %d failed\n", i);
				for (int j = 0; j < i; j++)
					free(matrix_r[j]);
				free(matrix_r); exit(-1);
			}
		}
		for (int i = 0; i < photo->height; i++) {
			matrix_g[i] = (int *)malloc(photo->width * sizeof(int));
			if (!matrix_g[i]) {
				fprintf(stderr, "malloc() for line %d failed\n", i);
				for (int j = 0; j < i; j++)
					free(matrix_g[j]);
				free(matrix_g); exit(-1);
			}
		}
		for (int i = 0; i < photo->height; i++) {
			matrix_b[i] = (int *)malloc(photo->width * sizeof(int));
			if (!matrix_b[i]) {
				fprintf(stderr, "malloc() for line %d failed\n", i);
				for (int j = 0; j < i; j++)
					free(matrix_b[j]);
				free(matrix_b); exit(-1);
			}
		}

		int x1 = photo->x1 / 3;
		int x2 = (photo->x2 - 2) / 3;
		int y1 = photo->y1;
		int y2 = photo->y2;

		for (int i = 0; i < photo->height; i++) {
			for (int j = 0; j < photo->width; j++) {
				matrix_r[i][j] = photo->matrix[i][3 * j];
				matrix_g[i][j] = photo->matrix[i][3 * j + 1];
				matrix_b[i][j] = photo->matrix[i][3 * j + 2];
			}
		}

		for (int i = y1; i <= y2; i++) {
			for (int j = x1; j <= x2; j++) {
				photo->matrix[i][3 * j] = matrix_r[y2 + x1 - j][x1 - y1 + i];
				photo->matrix[i][3 * j + 1] =
				matrix_g[y2 + x1 - j][x1 - y1 + i];
				photo->matrix[i][3 * j + 2] =
				matrix_b[y2 + x1 - j][x1 - y1 + i];
			}
		}

		for (int i = 0; i < photo->height; i++)
			free(matrix_r[i]);
		free(matrix_r);

		for (int i = 0; i < photo->height; i++)
			free(matrix_g[i]);
		free(matrix_g);

		for (int i = 0; i < photo->height; i++)
			free(matrix_b[i]);
		free(matrix_b);
	} else {
		rotate_90_right2(photo);
	}
}

int file_exists(char *filename)
{
	FILE *f = fopen(filename, "rb");
	int ok = 0;
	if (f) {
		ok = 1;
		fclose(f);
	}
	return ok;
}

void empty_file(image *photo)
{
	delete_photo(photo);
	photo->height = 0;
	photo->width = 0;
}

int is_number(char *string)
{
	if (*string == '-' || *string == '+')
		string++;
	while (*string) {
		if (*string < '0' || *string > '9')
			return 0;
		string++;
	}
	return 1;
}

int is_degree(char *string)
{
	if (*string != '-' || *string != '+')
		string++;
	while (*string) {
		if (*string < '0' || *string > '9')
			return 0;
		string++;
	}
	return 1;
}

int is_power_of_two(int n)
{
	if (n == 0)
		return 0;
	while (n != 1) {
		if (n % 2 != 0)
			return 0;
		n = n / 2;
	}
	return 1;
}

void choose_load(image *photo, char *file_name)
{
	if (file_exists(file_name) == 1) {
		load(photo, file_name);
	} else {
		printf("Failed to load %s\n", file_name);
		empty_file(photo);
	}
}

void choose_save(image *photo, char *file_name, char *type)
{
	if (!type)
		type = "binary";
	if (!photo->matrix)
		printf("No image loaded\n");
	else
		save(photo, file_name, type);
}

void choose_select(image *photo, int ok, int x1, int y1, int x2, int y2)
{
	if (ok == 1) {
		select_pixels(photo, x1, y1, x2, y2);
	} else {
		if (!photo->matrix)
			printf("No image loaded\n");
		else
			printf("Invalid command\n");
	}
}

void choose_crop(image *photo)
{
	if (!photo->matrix) {
		printf("No image loaded\n");
	} else {
		if (photo->x1 == -1 && photo->x2 == -1 &&
			photo->y1 == -1 && photo->y2 == -1)
			printf("Image cropped\n");
		else
			crop(photo);
	}
}

void choose_apply(image *photo, char *parameter)
{
	if (!parameter) {
		if (!photo->matrix)
			printf("No image loaded\n");
		else
			printf("Invalid command\n");
		return;
	}
	if (strncmp(photo->magic_word, "P2", 2) == 0 ||
		strncmp(photo->magic_word, "P5", 2) == 0) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}
	if (!photo->matrix && parameter) {
		printf("No image loaded\n");
		return;
	}
	if (strncmp(parameter, "EDGE", 4) == 0) {
		if (photo->x1 == -1 && photo->x2 == -1 &&
			photo->y1 == -1 && photo->y2 == -1){
			photo->x1 = 0;
			photo->y1 = 0;
			photo->x2 = photo->width * 3 - 1;
			photo->y2 = photo->height - 1;
		}
		edge(photo);
		printf("APPLY EDGE done\n");
	}
	if (strncmp(parameter, "SHARPEN", 7) == 0) {
		if (photo->x1 == -1 && photo->x2 == -1 &&
			photo->y1 == -1 && photo->y2 == -1) {
			photo->x1 = 0;
			photo->y1 = 0;
			photo->x2 = photo->width * 3 - 1;
			photo->y2 = photo->height - 1;
		}
		sharpen(photo);
		printf("APPLY SHARPEN done\n");
	}
	if (strncmp(parameter, "BLUR", 4) == 0) {
		if (photo->x1 == -1 && photo->x2 == -1 &&
			photo->y1 == -1 && photo->y2 == -1) {
			photo->x1 = 0;
			photo->y1 = 0;
			photo->x2 = photo->width * 3 - 1;
			photo->y2 = photo->height - 1;
		}
		blur(photo);
		printf("APPLY BLUR done\n");
	}
	if (strncmp(parameter, "GAUSSIAN_BLUR", 13) == 0) {
		gaussian_blur(photo);
		printf("APPLY GAUSSIAN_BLUR done\n");
	}
	if (strncmp(parameter, "EDGE", 4) != 0 &&
		strncmp(parameter, "SHARPEN", 7) != 0 &&
		strncmp(parameter, "BLUR", 4) != 0 &&
		strncmp(parameter, "GAUSSIAN_BLUR", 13) != 0) {
		printf("APPLY parameter invalid\n");
	}
}

void choose_histogram(image *photo, int ok, char *word, int x, int y)
{
	if (photo->x1 == -1 && photo->x2 == -1 &&
		photo->y1 == -1 && photo->y2 == -1) {
		photo->x1 = 0;
		photo->y1 = 0;
		photo->x2 = photo->width * 3 - 1;
		photo->y2 = photo->height - 1;
	}
	if (word)
		ok = 0;
	if (ok == 0) {
		if (!photo->matrix)
			printf("No image loaded\n");
		else
			printf("Invalid command\n");
	}
	if (ok == 1) {
		if (!photo->matrix) {
			printf("No image loaded\n");
		} else {
			if (y >= 2 && y <= 256 && is_power_of_two(y) == 1) {
				if (strcmp(photo->magic_word, "P3") == 0 ||
					strcmp(photo->magic_word, "P6") == 0)
					printf("Black and white image needed\n");
				else
					histogram(photo, x, y);
			}
		}
	}
}

void choose_equalize(image *photo)
{
	if (!photo->matrix) {
		printf("No image loaded\n");
	} else {
		if (strcmp(photo->magic_word, "P3") == 0 ||
			strcmp(photo->magic_word, "P6") == 0) {
			printf("Black and white image needed\n");
		} else {
			equalize(photo);
			printf("Equalize done\n");
		}
	}
}

void choose_rotate2(image *photo, char *degree)
{
	if (strncmp(degree, "90", 2) == 0) {
		if (photo->x1 == 0 && photo->y1 == 0 &&
			photo->y2 == photo->height - 1 &&
			(photo->x2 == photo->width - 1 ||
			photo->x2 == photo->width * 3 - 1))
			rotate_90_photo(photo);
		else
			rotate_90_right(photo);
		printf("Rotated 90\n");
	}
	if (strncmp(degree, "180", 3) == 0) {
		if (photo->x1 == 0 && photo->y1 == 0 &&
			photo->y2 == photo->height - 1 &&
			(photo->x2 == photo->width - 1 ||
			photo->x2 == photo->width * 3 - 1)) {
			rotate_90_photo(photo); rotate_90_photo(photo);
		} else {
			rotate_90_right(photo); rotate_90_right(photo);
		}
		printf("Rotated 180\n");
	}
	if (strncmp(degree, "270", 3) == 0) {
		if (photo->x1 == 0 && photo->y1 == 0 &&
			photo->y2 == photo->height - 1 &&
			(photo->x2 == photo->width - 1 ||
			photo->x2 == photo->width * 3 - 1)) {
			rotate_90_photo(photo);
			rotate_90_photo(photo);
			rotate_90_photo(photo);
		} else {
			rotate_90_right(photo);
			rotate_90_right(photo);
			rotate_90_right(photo);
		}
		printf("Rotated 270\n");
	}
	if (strcmp(degree, "360") == 0)
		printf("Rotated 360\n");
	if (strcmp(degree, "0") == 0)
		printf("Rotated 0\n");
	if (strcmp(degree, "-90") == 0) {
		if (photo->x1 == 0 && photo->y1 == 0 &&
			photo->y2 == photo->height - 1 &&
			(photo->x2 == photo->width - 1 ||
			photo->x2 == photo->width * 3 - 1)) {
			rotate_90_photo(photo);
			rotate_90_photo(photo);
			rotate_90_photo(photo);
		} else {
			rotate_90_right(photo);
			rotate_90_right(photo);
			rotate_90_right(photo);
		}
		printf("Rotated -90\n");
	}
	if (strcmp(degree, "-180") == 0) {
		if (photo->x1 == 0 && photo->y1 == 0 &&
			photo->y2 == photo->height - 1 &&
			(photo->x2 == photo->width - 1 ||
			photo->x2 == photo->width * 3 - 1)) {
			rotate_90_photo(photo); rotate_90_photo(photo);
		} else {
			rotate_90_right(photo); rotate_90_right(photo);
		}
		printf("Rotated -180\n");
	}
	if (strncmp(degree, "-270", 4) == 0) {
		if (photo->x1 == 0 && photo->y1 == 0 &&
			photo->y2 == photo->height - 1 &&
			(photo->x2 == photo->width - 1 ||
			photo->x2 == photo->width * 3 - 1))
			rotate_90_photo(photo);
		else
			rotate_90_right(photo);
		printf("Rotated -270\n");
	}
	if (strcmp(degree, "-360") == 0)
		printf("Rotated -360\n");
}

void choose_rotate(image *photo, char *word)
{
	int ok = 1;
	char degree[5];
	if (!photo->matrix) {
		printf("No image loaded\n");
		ok = 0;
	} else {
		if (!word || is_degree(word) != 1) {
			ok = 0;
			printf("Invalid command\n");
		} else {
			if (sscanf(word, "%s", degree) == 1)
				sscanf(word, "%s", degree);
			if (word && strcmp(degree, "0") != 0 &&
				strcmp(degree, "90") != 0 &&
				strcmp(degree, "180") != 0 &&
				strcmp(degree, "270") != 0 &&
				strcmp(degree, "360") != 0 &&
				strcmp(degree, "-90") != 0 &&
				strcmp(degree, "-180") != 0 &&
				strcmp(degree, "-270") != 0 &&
				strcmp(degree, "-360") != 0) {
				printf("Unsupported rotation angle\n");
				ok = 0;
			}
		}
	}
	if (ok == 1) {
		if (photo->x1 == -1 && photo->x2 == -1 &&
			photo->y1 == -1 && photo->y2 == -1) {
			photo->x1 = 0;
			photo->y1 = 0;
			if (strcmp(photo->magic_word, "P3") == 0 ||
				strcmp(photo->magic_word, "P6") == 0)
				photo->x2 = photo->width * 3 - 1;
			else
				photo->x2 = photo->width - 1;
			photo->y2 = photo->height - 1;
		}
		choose_rotate2(photo, degree);
	}
}

void choose_exit(image *photo)
{
	if (!photo->matrix) {
		printf("No image loaded\n");
		delete_photo(photo);
	} else {
		delete_photo(photo);
	}
}

void choose_invalid(char *command)
{
	if (strncmp(command, "LOAD", 4) != 0 &&
		strncmp(command, "SAVE", 4) != 0 &&
		strncmp(command, "SELECT", 6) != 0 &&
		strncmp(command, "CROP", 4) != 0 &&
		strncmp(command, "APPLY", 5) != 0 &&
		strncmp(command, "HISTOGRAM", 9) != 0 &&
		strncmp(command, "EQUALIZE", 8) != 0 &&
		strncmp(command, "EXIT", 4) != 0 &&
		strncmp(command, "ROTATE", 6) != 0)
		printf("Invalid command\n");
}

int main(void)
{
	int ok = 1; char command_buffer[100];
	image photo; photo.matrix = NULL; strcpy(photo.magic_word, "");
	photo.x1 = -2; photo.y1 = -2;
	photo.x2 = -2; photo.y2 = -2;
	while (ok == 1) {
		fgets(command_buffer, sizeof(command_buffer), stdin);
		char *command = strtok(command_buffer, " \040\n");
		if (strncmp(command, "LOAD", 4) == 0) {
			char *file_name = strtok(NULL, " \040\n");
			choose_load(&photo, file_name);
		}
		if (strncmp(command, "SAVE", 4) == 0) {
			char *file_name = strtok(NULL, " \040\n");
			char *type = strtok(NULL, " \040\n");
			choose_save(&photo, file_name, type);
		}
		if (strncmp(command, "SELECT", 6) == 0) {
			int x1, y1, x2, y2;
			char *check_x1_or_all = strtok(NULL, " \040\n");
			if (strcmp(check_x1_or_all, "ALL") == 0) {
				select_all(&photo);
			} else {
				int ok = 1;
				if (sscanf(check_x1_or_all, "%d", &x1) == 1)
					sscanf(check_x1_or_all, "%d", &x1);
				char *word = strtok(NULL, " \040\n");
				if (word && is_number(word) == 1)
					sscanf(word, "%d", &y1);
				else
					ok = 0;
				word = strtok(NULL, " \040\n");
				if (word && is_number(word) == 1)
					sscanf(word, "%d", &x2);
				else
					ok = 0;
				word = strtok(NULL, " \040\n");
				if (word && is_number(word) == 1)
					sscanf(word, "%d", &y2);
				else
					ok = 0;
				choose_select(&photo, ok, x1, y1, x2, y2);
			}
		}
		if (strncmp(command, "CROP", 4) == 0)
			choose_crop(&photo);
		if (strncmp(command, "APPLY", 5) == 0) {
			char *parameter = strtok(NULL, " \040\n");
			choose_apply(&photo, parameter);
		}
		if (strncmp(command, "HISTOGRAM", 9) == 0) {
			int ok = 1;
			int x, y;
			char *word = strtok(NULL, " \040\n");
			if (word && is_number(word) == 1)
				sscanf(word, "%d", &x);
			else
				ok = 0;
			word = strtok(NULL, " \040\n");
			if (word && is_number(word) == 1)
				sscanf(word, "%d", &y);
			else
				ok = 0;
			word = strtok(NULL, " \040\n");
			choose_histogram(&photo, ok, word, x, y);
		}
		if (strncmp(command, "EQUALIZE", 8) == 0)
			choose_equalize(&photo);
		if (strncmp(command, "ROTATE", 6) == 0) {
			char *word = strtok(NULL, " \040\n");
			choose_rotate(&photo, word);
		}
		if (strncmp(command, "EXIT", 4) == 0) {
			choose_exit(&photo);
			return 0;
		}
		choose_invalid(command);
	}
	return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	if (argc != 4)
		return EXIT_FAILURE;
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int iter = atoi(argv[3]);
	if (width <= 0 || height <= 0 || iter < 0)
		return EXIT_FAILURE;
	char *table = malloc(width * height);
	if (!table)
		return EXIT_FAILURE;
	for (int h = 0; h < height; h++){
		for (int w = 0; w < width; w++){
			table[width * h + w] = ' ';
		}
	}
	int w = 0;
	int h = 0;
	int pen = 0;
	// Read
	while (1){
		char c;
		ssize_t nr = read(STDIN_FILENO, &c, 1);
		if (nr < -1)
			return free(table), EXIT_FAILURE;
		if (nr == 0)
			break;
		if (c == 'w')
			h--;
		else if (c == 's')
			h++;
		else if (c == 'a')
			w--;
		else if (c == 'd')
			w++;
		else if (c == 'x')
			pen = !pen;
		if (w >= 0 && w < width && h >= 0 && h < height && pen)
			table[width * h + w] = 'O';

	}
	for (int i = 0; i < iter; i++){
		for (int h = 0; h < height; h++){
			for (int w = 0; w < width; w++){
				int n_live = 0;
				for (int p = h - 1; p <= h + 1 && p < height; p++){
					if (p < 0)
						continue;
					for (int o = w -1; o <= w + 1 && o < width; o++){
						if (o < 0)
							continue;
						if (p == h && o == w)
							continue;
						n_live += (table[width * p + o] == 'O');
						n_live += (table[width * p + o] == 'D');
					}
				}
				if (n_live == 3 && table[width * h + w] == ' ')
					table[width * h + w] = 'N';
				if (n_live != 3 && n_live != 2 && table[width * h + w] == 'O')
					table[width * h + w] = 'D';
			}
		}
		for (int h = 0; h < height; h++){
			for (int w = 0; w < width; w++){
				if (table[width * h + w] == 'N')
					table[width * h + w] = 'O';
				else if (table[width * h + w] == 'D')
					table[width * h + w] = ' ';
			}
		}
	}
	// Print table
	w = 0;
	h = 0;
	for (; h < height; h++){
		for (w = 0; w < width; w++)
			putchar(table[width * h + w]);
		putchar('\n');
	}
	free(table);
}

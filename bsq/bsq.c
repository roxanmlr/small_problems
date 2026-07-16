#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[]){
	if (argc != 2)
		return EXIT_FAILURE;
	int lines = 0;
	char empty;
	char obst;
	char full;
	FILE *f = fopen(argv[1], "r");
	if (!f)
		return EXIT_FAILURE;
	fscanf(f,"%d %c %c %c\n", &lines, &empty, &obst, &full);
	fprintf(stdout, "%d %c %c %c\n", lines, empty, obst, full);
	char *lineptr = NULL;
	size_t linesiz = 0;
	ssize_t len = -1;
	int map_correct = 1;
	char *map = NULL;
	int line = 0;
	while(map_correct){
		ssize_t nr = getline(&lineptr, &linesiz, f);
		if (nr == -1)
			break;
		if (nr == 0)
			break;
		if (len == -1){
			len = nr;
			map = calloc(1, lines * len + 1);
			if (!map)
				return free(lineptr), EXIT_FAILURE;
		}
		if (len != nr || line >= lines){
			map_correct = 0;
			break;
		}
		for (int c = 0; c < len; c++){
			if (c == len - 1 && lineptr[c] != '\n'){
				map_correct = 0;
				break;
			}
			else if (c != len - 1 && lineptr[c] != empty && lineptr[c] != obst){
				map_correct = 0;
				break;
			}
			map[line * len + c] = lineptr[c];
		}
		line++;
	}
	if (!map_correct){
		fprintf(stderr, "map error\n");
		free(lineptr);
		return EXIT_FAILURE;
	}
	free(lineptr);
	fclose(f);
	fprintf(stdout, "%s", map);
	free(map);
}

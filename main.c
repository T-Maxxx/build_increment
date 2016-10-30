#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE 512

int main(int argc, char* argv[])
{
	char* inputFileName = NULL;
	char* linePrefix = NULL;
	char buffer[BUFF_SIZE] = {'\0'};
	int i;
	FILE* f;
	int lineLen;
	int buildNum;

	/* Parse args. */
	for (i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'i') /* Input file. */
				inputFileName = argv[i + 1];
			else if (argv[i][1] == 'p') /* Line prefix. */
				linePrefix = argv[i + 1];

			++i;
		}
	}
	
	if (!inputFileName)
	{
		fprintf(stdout, "Use -i 'filename' to set input file name.\n");
		return 1;
	}

	f = fopen(inputFileName, "r");

	if (!f)
	{
		fprintf(stdout, "Can't open file '%s' for reading.\n", inputFileName);
		return 4;
	}

	fseek(f, 0, SEEK_END);
	lineLen = ftell(f);
	fseek(f, 0, SEEK_SET);

	fread(buffer, 1, lineLen, f);
	fclose(f);
	
	if (!linePrefix)
	{
		fprintf(stdout, "Use -p 'linePrefix' to set line prefix.\n");
		return 2;
	}

	if (linePrefix[0] == '\"')
	{
		linePrefix++;
		linePrefix[strlen(linePrefix) - 1] = '\0';
	}

	if (!strstr(buffer, linePrefix))
	{
		fprintf(stdout, "Prefix '%s' is not found in '%s'.\n", linePrefix, inputFileName);
		return 3;
	}

	buildNum = atoi(buffer + strlen(linePrefix)) + 1;

	f = fopen(inputFileName, "w");
	
	if (!f)
	{
		fprintf(stdout, "Can't open file '%s' for writing.\n", inputFileName);
		return 5;
	}
	sprintf(buffer, "%s %d\n", linePrefix, buildNum);
	fwrite(buffer, 1, strlen(buffer), f);
	fflush(f);
	fclose(f);

	fprintf(stdout, "'%s' done. New build set to %d.\n", argv[0], buildNum);
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <cstdlib>

#define BUFF_SIZE 512

int main(int argc, char* argv[])
{
	char* inputFileName = NULL;
	char* linePrefix = NULL;
	char buffer[BUFF_SIZE] = {'\0'};

	// Parse args.
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'i') // input file.
				inputFileName = argv[i + 1];
			else if (argv[i][1] == 'p') // line prefix.
				linePrefix = argv[i + 1];

			++i;
		}
	}
	
	if (!inputFileName)
	{
		printf("Use -i 'filename' to set input file name.");
		return 1;
	}

	FILE* f = fopen(inputFileName, "r");

	if (!f)
	{
		printf("Can't open file '%s' for reading.", inputFileName);
		return 4;
	}

	fseek(f, 0, SEEK_END);
	int lineLen = ftell(f);
	fseek(f, 0, SEEK_SET);

	fread(buffer, 1, lineLen, f);
	fclose(f);
	
	if (!linePrefix)
	{
		printf("Use -p 'linePrefix' to set line prefix.");
		return 2;
	}

	if (linePrefix[0] == '\"')
	{
		linePrefix++;
		linePrefix[strlen(linePrefix) - 1] = '\0';
	}

	if (!strstr(buffer, linePrefix))
	{
		printf("Prefix '%s' is not found in '%s'.", linePrefix, inputFileName);
		return 3;
	}

	int buildNum = atoi(buffer + strlen(linePrefix)) + 1;

	f = fopen(inputFileName, "w");
	
	if (!f)
	{
		printf("Can't open file '%s' for writing.", inputFileName);
		return 5;
	}
	sprintf(buffer, "%s %d\n", linePrefix, buildNum);
	fwrite(buffer, 1, strlen(buffer), f);
	fflush(f);
	fclose(f);

	printf("'%s' done. New build set to %d.", argv[0], buildNum);
	return 0;
}
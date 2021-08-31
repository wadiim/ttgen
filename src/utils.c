#include "utils.h"

#include <stdlib.h>
#include <ctype.h>

char * char_to_str(char c)
{
	char *tmp = malloc(2*sizeof(char));
	if (tmp)
	{
		tmp[0] = c;
		tmp[1] = '\0';
	}
	return tmp;
}

int strcicmp(const char *a, const char *b)
{
	if (a == NULL) return -1;
	if (b == NULL) return 1;
	for (;; ++a, ++b)
	{
		int d = tolower((unsigned char)*a)
			- tolower((unsigned char)*b);
		if (d != 0 || !*a) return d;
	}
}

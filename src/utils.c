#include "utils.h"

#include <stdlib.h>

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

#ifndef LOGIC_H
#define LOGIC_H

#include "list.h"

/*
 * Tokenizes the 'str' string.
 * The tokens are: '(', ')', ';', integers, and words (i.e. alphanumeric
 * sequences starting with non-digit).
 * Returns a list of tokens on success or NULL on error.
 */
List * tokenize(const char *str);

#endif /* LOGIC_H */

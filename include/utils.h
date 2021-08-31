#ifndef UTILS_H
#define UTILS_H

/*
 * Returns a dynamically allocated, null-terminated string of length 1
 * containing the 'c' character.
 */
char * char_to_str(char c);

/*
 * Compares the 'a' and 'b' strings without sensitivity to case.
 * 'a' and 'b' are expected to be null-terminated.
 * Returns value less than zero if 'a' is less than 'b', greater than
 * zero if 'a' is greater than 'b', and zero otherwise.
 */
int strcicmp(const char *a, const char *b);

#endif /* UTILS_H */

#include "word_count.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/* tree structure for indexing words[] */
struct tnode {
	int pos;		/* index in words[] */
	struct tnode *left;
	struct tnode *right;
};

int getword(const char *input, int *idx, char *word, int lim);
struct tnode *addtree(struct tnode *p, char *word, int len, int *wcount,
		      word_count_word_t * words);
void free_tree(struct tnode *p);

int word_count(const char *input_text, word_count_word_t * words)
{
	memset(words, 0, MAX_WORDS * sizeof(*words));
	int wlen;			/* length of the current word */
	int wcount = 0;			/* word counter */
	char word[MAX_WORD_LENGTH + 1];	/* word buffer */
	struct tnode *root = NULL;	/* tree root */
	int idx = 0;			/* index in input_text */

	while ((wlen = getword(input_text, &idx, word, MAX_WORD_LENGTH)) > 0) {
		if (wcount == MAX_WORDS) {
			free_tree(root);
			return EXCESSIVE_NUMBER_OF_WORDS;
		}
		if ((root = addtree(root, word, wlen, &wcount, words))
			== NULL) {
			free_tree(root);
			return MEMORY_ERROR;
		}
	}
	free_tree(root);
	if (wlen == EXCESSIVE_LENGTH_WORD)
		return EXCESSIVE_LENGTH_WORD;
	return wcount;
}

/* addtree: add tree node */
struct tnode *addtree(struct tnode *p, char *word, int len, int *wcount,
		      word_count_word_t * words)
{
	int cond;
	if (p == NULL) {	/* new word arrived */
		p = (struct tnode *)malloc(sizeof(struct tnode));
		if (p == NULL) {
			fprintf(stderr, "Memory error!\n");
			return NULL;
		}
		p->left = NULL;
		p->right = NULL;
		p->pos = *wcount;
		strncpy(words[*wcount].text, word, len + 1);
		words[p->pos].count = 1;
		(*wcount)++;

	} else if ((cond = strcmp(word, words[p->pos].text)) == 0) {
		words[p->pos].count++;	/* repeated word */

	} else if (cond < 0) {
		p->left = addtree(p->left, word, len, wcount, words);

	} else {
		p->right = addtree(p->right, word, len, wcount, words);
	}

	return p;
}

/* free_tree: free memory recursively */
void free_tree(struct tnode *p)
{
	if (p != NULL) {
		if (p->left != NULL) {
			free_tree(p->left);
		}
		if (p->right != NULL) {
			free_tree(p->right);
		}
		free(p);
	}
}

/* getword: get a word from 'input' into 'word' up to 'lim' length */
int getword(const char *input, int *idx, char *word, int lim)
{
	int wlen = 0;
	word[0] = '\0';
	char *w = word;

	while (input[*idx] && !isalnum(input[*idx]))
		(*idx)++;

	if (input[*idx] == '\0')
		return 0;

	bool done = false;
	while (!done) {
		if (isalnum(input[*idx])) {
			*w++ = tolower(input[(*idx)++]);
			if (wlen == lim) {
				*w = '\0';
				return EXCESSIVE_LENGTH_WORD;
			} else {
				wlen++;
			}
		} else if (input[*idx] == '\'') {
			if ((wlen > 1)  && isalnum(input[*idx - 1]) &&
				(wlen < lim -1) && isalnum(input[*idx +1])) {
				*w++ = '\'';
				(*idx)++;
				wlen++;
			} else {
				done = true;
			}
		} else {
			done = true;
		}

	}
	*w = '\0';
	return wlen;
}

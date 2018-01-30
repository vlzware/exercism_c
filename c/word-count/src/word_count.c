/**
 * Loosely based on the logic from K&R Exercise 6.4
 */

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
struct tnode *talloc(void);
void free_tree(struct tnode *p);

int main(void)
{
	word_count_word_t buf[MAX_WORDS];
	int res = word_count("Moin Trotel MOin MoiN trotel tRotel", buf);
	printf("count: %i\n", res);
	int i = 0;
	for (; i < res; i++)
		printf("idx: %i c: %i  %s\n", i, buf[i].count, buf[i].text);
	return 0;
}

int word_count(const char *input_text, word_count_word_t * words)
{
	int wlen;			/* length of the current word */
	int wcount = 0;			/* word counter */
	char word[MAX_WORD_LENGTH + 1];	/* word buffer */
	struct tnode *root = NULL;	/* tree root */
	int idx = 0;			/* index in input_text */

	while ((wlen = getword(input_text, &idx, word, MAX_WORD_LENGTH)) > 0)
		if ((root = addtree(root, word, wlen, &wcount, words)) == NULL)
			return MEMORY_ERROR;
	free_tree(root);
	if (wlen < 0)
		return wlen;
	return wcount;
}

/* addtree: add tree node */
struct tnode *addtree(struct tnode *p, char *word, int len, int *wcount,
		      word_count_word_t * words)
{
	int cond;
	if (p == NULL) {	/* new word arrived */
		p = talloc();	/* make a new node */
		if (p == NULL)
			return NULL;
		p->left = NULL;
		p->right = NULL;
		p->pos = *wcount;
		strncpy(words[*wcount].text, word, len);
		words[p->pos].count = 1;
		(*wcount)++;

	} else if ((cond = strcmp(word, words[p->pos].text)) == 0) {
		words[p->pos].count++;	/* repeated word */

	} else if (cond < 0) {
		/* TODO: HERE IT IS */
		p->left = addtree(p->left, word, len, wcount, words);

	} else {
		p->right = addtree(p->left, word, len, wcount, words);
	}

	return p;
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
	if (p == NULL)
		fprintf(stderr, "Memory error!\n");

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

/* getword: get a word from 'input' into 'word' */
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
			wlen++;

		} else {
			done = true;
		}
		if (wlen == lim)
			return EXCESSIVE_LENGTH_WORD;

	}
	*w = '\0';
	return wlen;
}

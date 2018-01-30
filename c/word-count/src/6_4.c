/*
Exercise 6-4. Write a program that prints the distinct words in its input
sorted into decreasing order of frequency of occurrence. Precede each word by
its count.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORD 100

int getword(char *word, int lim, int advparsing);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
struct tnode *talloc(void);
char *mstrdup(char *s);
void freemem(struct tnode *p);
void panic(const char *msg);

void parsetree(struct tnode *p);
int qsortcmp(const void *a, const void *b);

/* array with pointers to the tree nodes */
struct tnode **arr;
/* tree nodes count */
int tcount = 0;
int ttcount;

/* words frequency counter */
int main(void)
{
    /* build the tree */
    struct tnode *root;
    char word[MAXWORD];
    root = NULL;
    while (getword(word, MAXWORD, 0) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    /* parse the tree into a array */
    arr = (struct tnode **) malloc(tcount * sizeof(struct tnode *));
    if (arr == NULL)
        panic("arr malloc");

    ttcount = tcount;
    parsetree(root);

    /* sort the array from the parsed tree */
    qsort(arr, tcount, sizeof(struct tnode*), qsortcmp);

    /* print the sorted array */
    while (--tcount > -1) {
        printf(" %-5i\t", arr[tcount]->count);
        printf(" %s\n", arr[tcount]->word);
    }

    /* not (yet) discussed in K&R but I added it here anyway,
    to release the memory claimed with "malloc" */
    freemem(root);
    free(arr);

    return 0;
}

/* parsetree: recursively parse the tree into an array; count size */
void parsetree(struct tnode *p)
{
    if (p != NULL) {
        parsetree(p->left);
        arr[--ttcount] = p;
        parsetree(p->right);
    }
}

/* quick sort comparing function */
int qsortcmp(const void *a, const void *b)
{
    /* https://stackoverflow.com/a/19046779/6049386 */
    const struct tnode *p = *(const struct tnode **) a;
    const struct tnode *q = *(const struct tnode **) b;

    return (p->count - q->count);
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL) {                /* a new word has arrived */
        p = talloc();               /* make a new node */
        p->word = mstrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        tcount++;

    } else if ((cond = strcmp(w, p->word)) == 0) {
        /* repeated word */
        p->count++;

    } else if (cond < 0) {          /* less than into left subtree */
        p->left = addtree(p->left, w);

    } else {                        /* greater than into right subtree */
        p->right = addtree(p->right, w);
    }

    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);

        printf(" %-20s\t", p->word);
        printf("%i\n", p->count);

        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    struct tnode* p = (struct tnode *) malloc(sizeof(struct tnode));
    if (p == NULL)
        panic("talloc");

    return p;
}

/* mstrdup: make a duplicate of s */
char *mstrdup(char *s)
{
    char *p;
    p = (char *) malloc(strlen(s) + 1);     /* +1 for '\0' */

    if (p == NULL)
        panic("mstrdup");

    strcpy(p, s);

    return p;
}

/* freemem: frees memory recursively */
void freemem(struct tnode *p)
{
    if (p != NULL) {
        if (p->left != NULL) {
            freemem(p->left);
        }
        if (p->right != NULL) {
            freemem(p->right);
        }
        free(p->word);
        free(p);
    }
}

/* panic: exit forcefully after memory error */
void panic(const char *msg)
{
    printf("MEMORY ERROR\n");
    printf("function: %s\n", msg);
    exit(1);
}

/* getword: get next word or character from input */
int getword(char *word, int lim, int advparsing)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))                /* skip whitespace */
        ;

    /* corner cases enabled: skip comments and quotes */
    if (advparsing) {
        if (c == '/') {
            if ( (c = getch()) == '/')          /* single line comment */
                while ( ((c = getch()) != '\n') && (c != EOF) )
                    ;
            else if (c == '*') {                /* multiline comment */
                int done = 0;
                while (!done) {
                    while ((c = getch()) != '*')
                        if (c == EOF) {
                            *w = '\0';
                            ungetch(c);
                            return word[0];
                        }
                    /* "/* ... *" until now */
                    if ((c = getch()) == '/')
                        done = 1;
                }
            }
        }
        if (c == '"') {                         /* quotes */
            while ( ((c= getch()) != '"') && (c != EOF) )
                ;
        }
    }

    /* "normal" word */
    if ( (isalpha(c) || (c == '#') || (c == '_')) &&
            (--lim > 0) ) {
        *w++ = c;                               /* get first character */
        while ( ((isalnum(c = getch())) || (c == '_')) &&
                    (--lim > 0) )
            *w++ = c;                           /* build the whole word */
        ungetch(c);
    }

    if (c == EOF)
        return c;                               /* EOF */

    *w = '\0';
    return word[0];
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

/* get a (possibly pushed-back) character */
int getch(void)
{
    int c;
    /* ignore one (special) character after a backslash */
    if ((c = (bufp > 0) ? buf[--bufp] : getchar()) == '\\') {
        if ( ((c = (bufp > 0) ? buf[--bufp] : getchar()) == EOF) ||
                (isalnum(c)) )
            return c;
        else
            return (bufp > 0) ? buf[--bufp] : getchar();
    }
    return c;
}

/* push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

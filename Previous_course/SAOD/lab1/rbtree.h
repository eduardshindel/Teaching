#ifndef RBTREE_H
#define RBTREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>

#define Printer 1
#define COLOR_RED 0
#define COLOR_BLACK 1

struct rbtree {
	int key;
	char *value;
	int color;
	struct rbtree *parent;
	struct rbtree *left;
	struct rbtree *right;
};

struct rbtree EmptyNode;
struct rbtree *NullNode;

struct rbtree *rbtree_add(struct rbtree *root, int key, char *value);
struct rbtree *rbtree_lookup(struct rbtree *root, int key);
void rbtree_free(struct rbtree *root);
struct rbtree *rbtree_min(struct rbtree *root);
struct rbtree *rbtree_max(struct rbtree *root);
struct rbtree *rbtree_delete(struct rbtree *root, int key);

#endif
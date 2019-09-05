#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXIMUM_SIZE 128

typedef struct Record {
	char vendorID[MAXIMUM_SIZE];
	char passengerCount[MAXIMUM_SIZE];
	char tripDistance[MAXIMUM_SIZE];
	char ratecodeID[MAXIMUM_SIZE];
	char storeAndFwdFlag[MAXIMUM_SIZE];
	char PULocationID[MAXIMUM_SIZE];
	char DOLocationID[MAXIMUM_SIZE];
	char paymentType[MAXIMUM_SIZE];
	char fareAmount[MAXIMUM_SIZE];
	char extra[MAXIMUM_SIZE];
	char mtaTax[MAXIMUM_SIZE];
	char tipAmount[MAXIMUM_SIZE];
	char tollsAmount[MAXIMUM_SIZE];
	char improvementSurcharge[MAXIMUM_SIZE];
	char totalAmount[MAXIMUM_SIZE];
	char PUdatetime[MAXIMUM_SIZE]; // format YYYY-MM-DD HH:mm:ss (year-month-day hour:minute:second)
	char DOdatetime[MAXIMUM_SIZE];
	int tripDuration;
} Record;

typedef struct ListNode {
	Record* record;
	struct ListNode* next;
} ListNode;

typedef struct BstNode {
	char PUdatetime[MAXIMUM_SIZE];
	ListNode* list_data_node;

	struct BstNode* left;
	struct BstNode* right;
} BstNode;

typedef struct BSTree {
	struct BstNode* root;
	int num_elements;
} BSTree;

typedef struct CompInfo {
	char name[MAXIMUM_SIZE];
	int comparisons;
} CompInfo;

typedef struct Vector {
	CompInfo* info;
	int max_count; // the size of the dynamic array
	int count; // the number of array positions currently holding values
} Vector;

BSTree* build_dict(char* dictFile);

BSTree* bst_new();
void bst_insert(BSTree* bstree, Record* d);
BstNode* create_bst_node(Record* record);
void bst_free(BSTree* bstree);
void bst_free_subtree(BSTree* bstree, BstNode* n);
int bst_find(BSTree* bstree, char* PUdatetime, FILE* fout);
void bst_traverse_inorder(BstNode* n, char* PULocationID, FILE* fout, int* comparison, int* found);


Vector* vector_new();
void vector_double_size(Vector* v);
void vector_push_back(Vector* v, int comparisons, char* name);
void vector_free(Vector* v);
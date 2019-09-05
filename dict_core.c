#include "dict_core.h"

void bst_traverse_inorder(BstNode* n, char* PULocationID, FILE* fout, int* comparison, int* found) {
	if (n) {
		bst_traverse_inorder(n->left, PULocationID, fout, comparison, found);
		ListNode* node = n->list_data_node;
		while (node) {
			ListNode* next_node = node->next;
			Record* record = node->record;
			*comparison += 1;
			if (strcmp(PULocationID, record->PULocationID) == 0) {
				if (*found == 0) {
					*found = 1;
				}
				fprintf(fout, "%s --> %s\n", PULocationID, record->PUdatetime);
			}
			node = next_node;
		}
		bst_traverse_inorder(n->right, PULocationID, fout, comparison, found);
	}
}

int bst_find(BSTree* bstree, char* PUdatetime, FILE* fout) {
	assert(bstree != NULL);
	assert(PUdatetime != NULL);
	BstNode* tmp = bstree->root;
	int count = 0;
	int found = 0;
	while (tmp) {
		int diff = strcmp(PUdatetime, tmp->PUdatetime);
		++count;
		if (diff < 0) { // element is smaller
			tmp = tmp->left;
		}
		else if (diff > 0) { // element is bigger
			tmp = tmp->right;
		}
		else {
			found = 1;
			ListNode* node = tmp->list_data_node;
			while (node) {
				ListNode* next_node = node->next;
				Record* record = node->record;
				fprintf(fout, "%s --> VendorID: %s || passenger_count: %s || trip_distance: %s || RatecodeID: %s || "
					"store_and_fwd_flag: %s || PULocationID: %s || DOLocationID: %s || payment_type: %s || "
					"fare_amount: %s || extra: %s || mta_tax: %s || tip_amount: %s || "
					"tolls_amount: %s || improvement_surcharge: %s || total_amount: %s || "
					"DOdatetime: %s || trip_duration: %d ||\n", PUdatetime, record->vendorID, record->passengerCount,
					record->tripDistance, record->ratecodeID, record->storeAndFwdFlag, record->PULocationID,
					record->DOLocationID, record->paymentType, record->fareAmount, record->extra, record->mtaTax,
					record->tipAmount, record->tollsAmount, record->improvementSurcharge, record->totalAmount,
					record->DOdatetime, record->tripDuration);
				node = next_node;
			}
			break;
		}
	}

	if (found == 0) {
		fprintf(fout, "%s --> NOTFOUND\n", PUdatetime);
	}
	return count;
}

void bst_free_subtree(BSTree* bstree, BstNode* n) {
	assert(bstree != NULL);
	if (n) {
		bst_free_subtree(bstree, n->left);
		bst_free_subtree(bstree, n->right);
		ListNode* node = n->list_data_node;
		while (node) {
			ListNode* next_node = node->next;
			free(node->record);
			free(node);
			node = next_node;
		}

		free(n);
	}
}

void bst_free(BSTree* bstree) {
	assert(bstree != NULL);
	bst_free_subtree(bstree, bstree->root);
	free(bstree);
}

BstNode* create_bst_node(Record* record) {
	BstNode* newNode = (BstNode*)malloc(sizeof(BstNode));
	newNode->left = newNode->right = NULL;
	strcpy(newNode->PUdatetime, record->PUdatetime);

	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	newNode->list_data_node = node;
	node->record = record;
	node->next = NULL;

	return newNode;
}

void bst_insert(BSTree* bstree, Record* record) {
	if (bstree->root == NULL) {
		bstree->root = create_bst_node(record);
		++bstree->num_elements;
	}
	else {
		BstNode* parent = NULL;
		BstNode* tmp = bstree->root;
		while (tmp) {
			parent = tmp;

			int diff = strcmp(record->PUdatetime, tmp->PUdatetime);
			if (diff < 0) { // element is smaller
				tmp = tmp->left;
			}
			else if (diff > 0) { // element is bigger
				tmp = tmp->right;
			}
			else {
				// duplicate
				ListNode* node = (ListNode*)malloc(sizeof(ListNode));
				node->record = record;
				node->next = tmp->list_data_node;
				tmp->list_data_node = node;
				return;
			}
		}
		BstNode* new_node = create_bst_node(record);
		if (strcmp(record->PUdatetime, parent->PUdatetime) < 0) { // element is smaller
			assert(parent->left == NULL);
			parent->left = new_node;
		}
		else {
			assert(parent->right == NULL);
			parent->right = new_node;
		}
		++bstree->num_elements;
	}
}

BSTree* build_dict(char* dictFile) {
	BSTree* bstree = bst_new();
	FILE* fin = fopen(dictFile, "r");

	char *line, *word;
	char buffer[1024];

	while ((line = fgets(buffer, sizeof(buffer), fin)) != NULL) {
		Record* record = (Record *)malloc(sizeof(Record));
		word = strtok(line, ","); strcpy(record->vendorID, word);
		word = strtok(NULL, ","); strcpy(record->passengerCount, word);
		word = strtok(NULL, ","); strcpy(record->tripDistance, word);
		word = strtok(NULL, ","); strcpy(record->ratecodeID, word);
		word = strtok(NULL, ","); strcpy(record->storeAndFwdFlag, word);
		word = strtok(NULL, ","); strcpy(record->PULocationID, word);
		word = strtok(NULL, ","); strcpy(record->DOLocationID, word);
		word = strtok(NULL, ","); strcpy(record->paymentType, word);
		word = strtok(NULL, ","); strcpy(record->fareAmount, word);
		word = strtok(NULL, ","); strcpy(record->extra, word);
		word = strtok(NULL, ","); strcpy(record->mtaTax, word);
		word = strtok(NULL, ","); strcpy(record->tipAmount, word);
		word = strtok(NULL, ","); strcpy(record->tollsAmount, word);
		word = strtok(NULL, ","); strcpy(record->improvementSurcharge, word);
		word = strtok(NULL, ","); strcpy(record->totalAmount, word);
		word = strtok(NULL, ","); strcpy(record->PUdatetime, word);
		word = strtok(NULL, ","); strcpy(record->DOdatetime, word);
		word = strtok(NULL, ","); sscanf(word, "%d\n", &record->tripDuration);
		bst_insert(bstree, record);
	}
	fclose(fin);

	return bstree;
}

BSTree* bst_new() {
	BSTree* bstree = (struct BSTree*) malloc(sizeof(BSTree));
	bstree->root = NULL;
	bstree->num_elements = 0;

	return bstree;
}

void vector_push_back(Vector* v, int comparisons, char* name) {
	if (v->max_count == v->count) {
		vector_double_size(v);
	}
	v->info[v->count].comparisons = comparisons;
	strcpy(v->info[v->count].name, name);
	++v->count;
}

Vector* vector_new() {
	Vector* v = (Vector *)malloc(sizeof(Vector));
	v->count = 0;
	v->max_count = 50;
	v->info = (CompInfo*)malloc(sizeof(CompInfo) * v->max_count);

	return v;
}

void vector_double_size(Vector* v) {
	v->max_count *= 2;
	CompInfo* info = (CompInfo*)malloc(sizeof(CompInfo) * v->max_count);
	for (int i = 0; i < v->count; ++i) {
		info[i].comparisons = v->info[i].comparisons;
		strcpy(info[i].name, v->info[i].name);
	}
	free(v->info);
	v->info = info;
}

void vector_free(Vector* v) {
	free(v->info);
	free(v);
}
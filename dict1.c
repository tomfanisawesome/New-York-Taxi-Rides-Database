#include "dict_core.h"

// Stage 1
void search_stage1(BSTree* bstree, char* outputFile);

int main(int argc, char *argv[]) {
	char* dictFile = argv[1];
	char* outputFile = argv[2]; // containing the data located in the searches

	BSTree* bstree = build_dict(dictFile);
	search_stage1(bstree, outputFile);

	bst_free(bstree);
	return 0;
}

void search_stage1(BSTree* bstree, char* outputFile) {
	FILE* fout = fopen(outputFile, "w");
	Vector* vec = vector_new();
	char PUdatetime[MAXIMUM_SIZE];
	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		sscanf(buffer, "%[^\r\n]", PUdatetime);
		int comparison = bst_find(bstree, PUdatetime, fout);
		vector_push_back(vec, comparison, PUdatetime);
	}


	for (int i = 0; i < vec->count; ++i){
		fprintf(stdout, "%s --> %d\n", vec->info[i].name, vec->info[i].comparisons);
	}
	fclose(fout);
	vector_free(vec);
}




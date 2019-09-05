#include "dict_core.h"
#include "dict2.h"
// Stage 2

int main(int argc, char *argv[]) {

	char* dictFile = argv[1];
	char* outputFile = argv[2]; // containing the data located in the searches

	BSTree* bstree = build_dict(dictFile);
	search_stage2(bstree, outputFile);

	bst_free(bstree);
	return 0;
}

void search_stage2(BSTree* bstree, char* outputFile) {
	FILE* fout = fopen(outputFile, "w");
	Vector* vec = vector_new();
	char PULocationID[MAXIMUM_SIZE];
	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		sscanf(buffer, "%[^\r\n]", PULocationID);
		int comparison = 0;
		int found = 0;
		bst_traverse_inorder(bstree->root, PULocationID, fout, &comparison, &found);
		vector_push_back(vec, comparison, PULocationID);

		if (found == 0) {
			fprintf(fout, "%s --> NOTFOUND\n", PULocationID);
		}
	}
	for (int i = 0; i < vec->count; ++i) {
		fprintf(stdout, "%s --> %d\n", vec->info[i].name, vec->info[i].comparisons);
	}
	fclose(fout);
	vector_free(vec);
}
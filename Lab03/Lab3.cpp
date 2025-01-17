#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <set>
#include "cudd.h"
#include "util.h"

using namespace std;

void write_dd(DdManager *gbm, DdNode *dd, char* filename){
    FILE *outfile;
    outfile = fopen(filename, "w");
    DdNode **ddnodearray = (DdNode**)malloc(sizeof(DdNode*));
    ddnodearray[0] = dd;
    Cudd_DumpDot(gbm, 1, ddnodearray, NULL, NULL, outfile);
    free(ddnodearray);
    fclose(outfile);
}

int main(int argc, char *argv[])
{
	FILE *in;
	FILE *out;
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	char alphabet;
	set<int> num_node;

	DdManager *gbm; /* Global BDD manager. */
	char filename[30];
	gbm = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0); /* Initialize a new BDD manager. */
	DdNode *bdd1, *tmp, *tmp_neg, *var;
	bdd1 = Cudd_ReadOne(gbm);	/*Returns the logic one constant of the manager*/
	Cudd_Ref(bdd1);	/*Increses the reference count of a node*/
	
	alphabet = fgetc(in);	//read a character from stream
	//fist product
	while (alphabet != '+' && alphabet != '.'){
		if (alphabet > 96) {	//lowercase means plain
			var = Cudd_bddIthVar(gbm, alphabet - 97);	/*Create a new BDD variable*/
			num_node.insert(alphabet - 97);
			tmp = Cudd_bddAnd(gbm, var, bdd1);	/*Perform AND Boolean operation*/
			Cudd_Ref(tmp);	/*Increses the reference count of a node*/
			Cudd_RecursiveDeref(gbm, bdd1);	/*Decreases the reference count of a node*/
			bdd1 = tmp;
		}
		else {	//uppercase means complement
			var = Cudd_bddIthVar(gbm, alphabet - 65);	/*Create a new BDD variable*/
			num_node.insert(alphabet - 65);
			tmp_neg = Cudd_Not(var); /*Perform NOT Boolean operation*/
			tmp = Cudd_bddAnd(gbm, tmp_neg, bdd1); /*Perform AND Boolean operation*/
			Cudd_Ref(tmp);
			Cudd_RecursiveDeref(gbm, bdd1);
			bdd1 = tmp;
		}
		alphabet = fgetc(in);
	}
	//later product
	if (alphabet != '.') {
		while (alphabet != '.') {
			alphabet = fgetc(in);
			DdNode *bdd2;
			bdd2 = Cudd_ReadOne(gbm);
			Cudd_Ref(bdd2);

			while (alphabet != '+'&& alphabet != '.') {
				if (alphabet > 96) {	//lowercase means plain
					var = Cudd_bddIthVar(gbm, alphabet - 97);	/*Create a new BDD variable*/
					num_node.insert(alphabet - 97);
					tmp = Cudd_bddAnd(gbm, var, bdd2);	/*Perform AND Boolean operation*/
					Cudd_Ref(tmp);	/*Increses the reference count of a node*/
					Cudd_RecursiveDeref(gbm, bdd2);	/*Decreases the reference count of a node*/
					bdd2 = tmp;
				}
				else {	//uppercase means complement
					var = Cudd_bddIthVar(gbm, alphabet - 65);	/*Create a new BDD variable*/
					num_node.insert(alphabet - 65);
					tmp_neg = Cudd_Not(var); /*Perform NOT Boolean operation*/
					tmp = Cudd_bddAnd(gbm, tmp_neg, bdd2); /*Perform AND Boolean operation*/
					Cudd_Ref(tmp);	/*Increses the reference count of a node*/
					Cudd_RecursiveDeref(gbm, bdd2);	/*Decreases the reference count of a node*/
					bdd2 = tmp;
				}
				alphabet = fgetc(in);
			}
			Cudd_Ref(bdd1);
			bdd1 = Cudd_bddOr(gbm, bdd1, bdd2);
		}
	}
	Cudd_Ref(bdd1);
	int *order_min;
	int *order_tmp;
	order_min = new int [num_node.size()];
	order_tmp = new int [num_node.size()];
	int minimum_nodeNum = INT32_MAX;

	while( (alphabet = fgetc(in)) != EOF)	//\n has been handled
	{
		for(unsigned int i = 0; i < num_node.size(); i++){
			alphabet = fgetc(in);
			order_tmp[i] = alphabet - 97;
		}
		Cudd_ShuffleHeap(gbm, order_tmp);
		if(minimum_nodeNum > Cudd_DagSize(bdd1)) {
			delete []order_min;
			order_min = new int [num_node.size()];
			for(unsigned int i = 0; i < num_node.size(); i++)
				order_min[i] = order_tmp[i];
			minimum_nodeNum = Cudd_DagSize(bdd1);
		}
		delete []order_tmp;
		order_tmp = new int [num_node.size()];
		alphabet = fgetc(in);	//'.' has been handled
  	}

	Cudd_ShuffleHeap(gbm, order_min);	//min numNode order
	sprintf(filename, "a.dot"); //Write .dot filename to a string  將格式化輸出"a.dot"放到filename指向的字元陣列(不夠大會溢位)，放之前會清掉filename指的內容
	bdd1 = Cudd_BddToAdd(gbm, bdd1); //Convert BDD to ADD for display purpose
	write_dd(gbm, bdd1, filename);  //Write the resulting cascade dd to a file
	fprintf(out, "%d\n", Cudd_DagSize(bdd1));
	Cudd_Quit(gbm);
	fclose(in);
	fclose(out);
	return 0;

}

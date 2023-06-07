/*
 * GeneralizedList.c
 * Sample Pseudocode/Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack_ops.h"

/*
 * Returns true if the input symbol is an atom which is by assumtion a letter in the English Alphabet
 */
int isAtom(char symbol){
	return (symbol >= 97 && symbol <= 122) || (symbol >= 65 && symbol <= 90);
}

/*
 * Reads the input pure list and builds a tag-data-link representation of the pure list
 * Returns a pointer to the first tag-data-link node
 */
GeneralizedListNode * readInput()
{
	char symbol;
	Stack *S = (Stack *)malloc(sizeof(Stack));;
	InitStack(S);

	while(scanf("%c", &symbol) != EOF)
	{
		StackElemType *x = (StackElemType*) malloc(sizeof(StackElemType));

		// 	if symbol is left parenthesis
		//		push to stack S
		if(symbol == '('){
			// printf("1");
			x->character = symbol;
			PUSH(S, *x);
		}

		//	else if symbol is an atom
		//		push to stack S
		else if(isAtom(symbol)){
			// printf("2");
			x->character = symbol;
			PUSH(S, *x);
		}

		//	else if symbol is right parenthesis
		//		pop a stack element,say top, from S (make sure stack is not empty before doing so)
		//		set prevNode to null
		//		while stack S is not empty
		//			if top is an atom
		//				create a corresponding GeneralizedListNode, say node
		//					with tag=0;atom=top.character;list=null;link=prevNode
		//				update prevNode with node
		//			else if top is a left parenthesis
		//				create a corresponding GeneralizedListNode
		//					with tag=1;atom=0;list=prevNode;link=null
		//				update prevNode with node
		//				push node to stack S
		//				break
		//			else if top is a GeneralizedListNode
		//				update value of the link of top with prevNode
		//				update prevNode with value of top
		//			pop a stack element from S and store to top
		//		if stack is empty
		//	  	  	  return prevNode;
		else if(symbol == ')'){
			// printf("3");
			POP(S, x);
			StackElemType *top = x;
			GeneralizedListNode *prevNode = (GeneralizedListNode *) malloc(sizeof(GeneralizedListNode));
			prevNode = NULL;

			while(!IsEmptyStack(S)){
				if(isAtom(top->character)){
					// printf("4");
					GeneralizedListNode* node = (GeneralizedListNode*)malloc(sizeof(GeneralizedListNode));
					node->tag = false;
					node->dataAtom = top->character;
					node->dataList = NULL;
					node->link = prevNode;
					prevNode = node;
				}
				
				else if(top->character == '('){
					// printf("5");
					GeneralizedListNode* node = (GeneralizedListNode*)malloc(sizeof(GeneralizedListNode));
					node->tag = true;
					node->dataAtom = '0';
					node->dataList = prevNode;
					node->link = NULL;
					prevNode = node;
					StackElemType *beta = (StackElemType*) malloc(sizeof(StackElemType));
					beta->generalizedListNode = node;
					PUSH(S, *beta);
					break;
				}

				else if(top->generalizedListNode != NULL){
					// printf("6");
					top->generalizedListNode->link = prevNode;
					prevNode = top->generalizedListNode;
				}

				POP(S, top);
			}
			if(IsEmptyStack(S)){
				// printf("done1");
				return prevNode;
			}
		}
	}

}

void VISIT(GeneralizedListNode *T)
{
	printf("-%c-", T->dataAtom);
}

void traversePureList(GeneralizedListNode *L){
	//	Pseudocode from Quiwa book
	//	if L = null then return
	//	call InitStack(S)
	//	alpha <- L
	//	loop
	//1:if TAG(alpha) = 0 then call VISIT(DATA(alpha))
	// 	else [if DATA(alpha) = null then goto 2
	//								 else [call PUSH(S, alpha)
	//									alpha <- DATA(alpha); goto 1]]
	//2:alpha <- LINK (alpha)
	//	if alpha = null then if IsEmptyStack(S) then return
	//											else [ call POP(S, alpha); goto 2 ]
	// forever

	if(L == NULL){
		return;
	}
	Stack S;
	InitStack(&S);
	GeneralizedListNode *alpha = (GeneralizedListNode *) malloc (sizeof (GeneralizedListNode));
	alpha = L;

	while(1){
		one:
		if (alpha->tag == false){
			VISIT(alpha);
		}

		else{
			if (alpha->dataList == NULL){
				goto two;
			}
			else{
				StackElemType *beta = (StackElemType *) malloc (sizeof (StackElemType));
				beta->generalizedListNode = alpha;
				// printf("1");
				PUSH(&S, *beta);
				alpha = alpha->dataList;
				goto one;
			}
		}

		two:
		alpha = alpha->link;
		if(alpha == NULL){
			if(IsEmptyStack(&S)){
				return;
			}
			else{
				StackElemType *beta = (StackElemType *) malloc (sizeof (StackElemType));
				POP(&S, beta);
				alpha = beta->generalizedListNode;
				goto two;
			}
		}

	}
}

// Driver program to test above functions
int main()
{
	GeneralizedListNode *L;
	L = readInput();
	traversePureList(L);
    return 0;
}

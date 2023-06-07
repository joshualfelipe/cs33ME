#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 101
#define SMAX 256

typedef char String[SMAX];
typedef struct generalizedlistnode GeneralizedListNode;

struct generalizedlistnode
{
	bool tag;
    char dataAtom;
    GeneralizedListNode *dataList;
    GeneralizedListNode *link;
};

struct stackelemtype
{
	GeneralizedListNode* generalizedListNode;
    char character;
};
typedef struct stackelemtype StackElemType;

struct stack
{
    int top;
    StackElemType Stack[N];
};
typedef struct stack Stack;

void InitStack(Stack *S)
{
    S->top = 0;
}

int IsEmptyStack(Stack *S)
{
    return (S->top == 0);
}

void StackOverflow(void)
{
    printf("Stack overflow detected.\n");
    exit(1);
}

void StackUnderflow(void)
{
    printf("Stack underflow detected.\n");
    exit(1);
}

void PUSH (Stack *S, StackElemType x)
{
    if (S->top == N) StackOverflow();
    else
    {
        ++S->top;
        S->Stack[S->top] = x;
    }
}

void POP (Stack *S, StackElemType *x)
{
    if (S->top == 0) StackUnderflow();
    else
    {
        *x = S->Stack[S->top];
        --S->top;
    }
}

int isAtom(char symbol){
	return (symbol >= 97 && symbol <= 122) || (symbol >= 65 && symbol <= 90);
}

GeneralizedListNode * readInput()
{
	char symbol;
	Stack *S = (Stack *)malloc(sizeof(Stack));
	InitStack(S);

	while(scanf("%c", &symbol) != EOF)
	{
		StackElemType *x = (StackElemType*) malloc(sizeof(StackElemType));

		if(symbol == '('){
			// printf("1");
			x->character = symbol;
			PUSH(S, *x);
		}

		else if(isAtom(symbol)){
			// printf("2");
			x->character = symbol;
			PUSH(S, *x);
		}

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

int main()
{
	GeneralizedListNode *L;
	L = readInput();
	traversePureList(L);
    return 0;
}

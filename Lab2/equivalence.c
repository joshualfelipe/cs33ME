/**
For this code template, you may change the
function bodies as you see fit, except for
the main function.
**/

#include <stdio.h>
#include <stdlib.h>

#define newline printf("\n")

void EQUIVALENCE (void);
int NUM_EQUI_CLASSES(void);

/**
The following are optional functions. 
The use of this functions depends on how you would like to implement EQUIVALENCE
**/
void UNION (int i, int j);
int FIND (int i);


/**
QUIWA book suggested that the FATHER
array be declared as global for easier
implementation of the codes.
**/

// Declare global variables here

int *FATHER; //the global FATHER array
int SIZE; //the global FATHER array size
// Declare global variables here

int main()
{   
    EQUIVALENCE ();
    printf("%d", NUM_EQUI_CLASSES());
    
    free (FATHER);
    return 0;
}

void UNION(int i, int j){
    int count  = FATHER[i] + FATHER[j];
    if (abs(FATHER[i]) > abs(FATHER[j])){
        FATHER[j]= i;
        FATHER[i] = count;
    }

    else{
        FATHER[i] = j;
        FATHER[j] = count;
    }
}

int FIND(int i){
    int r = i;
                    
    while(FATHER[r] > 0){
        r = FATHER[r];
    }

    int j = i;
    while(j != r){
        int k = FATHER[j];
        FATHER[j] = r;
        j = k;
    }

    return r;
}

void EQUIVALENCE ()
{
    int i, j, n;
    
    // get size of S
    scanf("%d\n", &n);
    SIZE = n;
    /*
    //Initialize FATHER array
    */

    FATHER = (int *) malloc (n * sizeof(int));
    for (i = 1; i <= n; i++)
    {
        FATHER[i] = -1;
    }

    scanf("%d %d\n", &i, &j);
    while (i != 0 && j != 0)
    {   
        /*
        Implement the equivalence pseudocode of Quiwa Book of your choice. 
        You may need to create and call FIND and UNION functions.
        */
        i = FIND(i);
        j = FIND(j);

        // printf("%d %d\n", i, j);
        if(i != j){
            UNION(i,j);
        }
        
        scanf("%d %d\n", &i, &j);
    }
    
    return;
}

int NUM_EQUI_CLASSES()
{
	int numEquiClasses=0;

	/**
	Determine the number of equivalence classes.
	Store it in numEquiClasses variable.
	**/

    // for(int j = 1; j <= SIZE; j++){
    //     printf("%d\n", FATHER[j]);
    // }

    for(int i = 1; i <= SIZE; i++){
        if(FATHER[i] < 0){
            numEquiClasses++;
        }
    }

	return numEquiClasses;
}
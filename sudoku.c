#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int sudokuboard[9][9]; //loaded with sample_in_sudoku.txt
int solved[11]; //joins threads, returns 1 if valid 0 otherwise
int subgridCt = 2; //used for sudoku sections


/* We will need a structure to store the information to be passed to each thread */
typedef struct{
    int row;
    int column;

}parameters;

pthread_t col_thread, row_thread, first_thread, second_thread, third_thread, fourth_thread, fifth_thread, sixth_thread, seventh_thread, eighth_thread, ninth_thread; //thread decleration

void *colworker(void *param);
void *rowworker(void *param);
void *sectionworker(void *param);


int main(int argc, char *argv[])
{ 
    //load sample_in_sudoku.txt into sudokuboard
    int check = 0;
	FILE *f;
	f = fopen(argv[1], "r");
	printf("Sudoku Puzzle input is: \n");
	for(int x = 0; x <= 8; x++){
		for(int y = 0; y <= 8; y++){
			fscanf(f, "%d ", &sudokuboard[x][y]);
            printf("%d ",sudokuboard[x][y]);

		}
		printf("\n");
	}
    //create structures to hold information for threads
    parameters *cr = (parameters *) malloc(sizeof(parameters));
    cr->row = 0;
    cr->column = 0;

    parameters *cc = (parameters *) malloc(sizeof(parameters));
    cc->row = 0;
    cc->column = 0;

    parameters *sectionone = (parameters *) malloc(sizeof(parameters));
    sectionone->row = 0;
    sectionone->column = 0;

    parameters *sectiontwo = (parameters *) malloc(sizeof(parameters));
    sectiontwo->row = 0;
    sectiontwo->column = 3;

    parameters *sectionthree = (parameters *) malloc(sizeof(parameters));
    sectionthree->row = 0;
    sectionthree->column = 6;

    parameters *sectionfour = (parameters *) malloc(sizeof(parameters));
    sectionfour->row = 3;
    sectionfour->column = 0;

    parameters *sectionfive = (parameters *) malloc(sizeof(parameters));
    sectionfive->row = 3;
    sectionfive->column = 3;

    parameters *sectionsix = (parameters *) malloc(sizeof(parameters));
    sectionsix->row = 3;
    sectionsix->column = 6;

    parameters *sectionseven = (parameters *) malloc(sizeof(parameters));
    sectionseven->row = 6;
    sectionseven->column = 0;

    parameters *sectioneight = (parameters *) malloc(sizeof(parameters));
    sectioneight->row = 6;
    sectioneight->column = 3;

    parameters *sectionnine = (parameters *) malloc(sizeof(parameters));
    sectionnine->row = 6;
    sectionnine->column = 6;

    //thread identifiers
    void * rows;
    void * cols;
    void * first_square;
    void * second_square;
    void * third_square;
    void * fourth_square;
    void * fifth_square;
    void * sixth_square;
    void * seventh_square;
    void * eighth_square;
    void * ninth_square;


    //create threads
    pthread_create(&col_thread, NULL, colworker, (void *) cc);
    pthread_create(&row_thread, NULL, rowworker, (void *) cr);
    pthread_create(&first_thread, NULL, sectionworker, (void *) sectionone);
    pthread_create(&second_thread, NULL, sectionworker, (void *) sectiontwo);
    pthread_create(&third_thread, NULL, sectionworker, (void *) sectionthree);
    pthread_create(&fourth_thread, NULL, sectionworker, (void *) sectionfour);
    pthread_create(&fifth_thread, NULL, sectionworker, (void *) sectionfive);
    pthread_create(&sixth_thread, NULL, sectionworker, (void *) sectionsix);
    pthread_create(&seventh_thread, NULL, sectionworker, (void *) sectionseven);
    pthread_create(&eighth_thread, NULL, sectionworker, (void *) sectioneight);
    pthread_create(&ninth_thread, NULL, sectionworker, (void *) sectionnine);



	//theads need to wait
	pthread_join(col_thread, &cols);
    pthread_join(row_thread, &rows);
    pthread_join(first_thread, &first_square);
    pthread_join(second_thread, &second_square);
    pthread_join(third_thread, &third_square);
    pthread_join(fourth_thread, &fourth_square);
    pthread_join(fifth_thread, &fifth_square);
    pthread_join(sixth_thread, &sixth_square);
    pthread_join(seventh_thread, &seventh_square);
    pthread_join(eighth_thread, &eighth_square);
    pthread_join(ninth_thread, &ninth_square);

	while(check <= 10){
		if(solved[check] == 1){
			check++;
        }
        else{
        	printf("The Sudoku Puzzle is invalid. \n");
        	exit(0);
        }
	}
    printf("Sudoku Puzzle is valid. \n");
	return 0;
}

void *colworker(void *params) //thread for columns
{
    parameters * c_worker = (parameters *) params;
    int c = c_worker->column;
    int r = c_worker->row;

    for(int x = c; x <= 8; x++){

	int column[9]= {0}; //array to hold sorted column

        for(int y = r; y <= 8; y++){

            int v = sudokuboard[x][y]; //this specific value in the column

            /*if the coresponding array element for the value is 0, it has not been seen and
		we will input this value to the sorted column array. */

            if(column[v-1] == 0 && v >= 1){
            	column[v-1] = v;
            }
		/*if the value is not 0, then the value is a duplicate and the sudoku puzzle
		  is not solved or valid so the value of column_worker in valid is 0; */
            else{
            	solved[0] = 0;
                pthread_exit(0);
            }
        }
    }
    solved[0] = 1;
    pthread_exit(0);
}

void *rowworker(void *params){ //thread for rows

    int i, j;

    parameters * r_worker = (parameters *) params;
    int beginCol = r_worker->column;
    int beginRow = r_worker->row;

    /*sorting sudoku row; this will put the row into a sorted order and check for duplicates
      if there are duplicates, this section is not valid and returns 0 for the row_worker;*/

    for(i = beginCol; i < 9; i++){

        int row[9]= {0};//array to hold sorted row

        for(j = beginRow; j < 9; j++){

            int val = sudokuboard[i][j];

            /*if the corresponding array element for the value is 0, it has not been seen and
		we will input this value to the sorted column array. */

            if(row[val-1] == 0 && val > 0){
                row[val-1] = val;
            }

            /*if the value is not 0, then the value is a duplicate and the sudoku puzzle
		  is not solved or valid so the value of column_worker in valid is 0. */

            else{
                valid[1] = 0;
                pthread_exit(0);
            }
        }
    }
    valid[1] = 1;
    pthread_exit(0);
}


/*thread code for child checking all 3x3 subgrids*/
void *sectionworker(void *params){

    int i, j;
    parameters * worker = (parameters *) params;
    int beginRow = worker->row;
    int beginCol = worker->column;

    /*sorting sudoku subgrids; this will put the 3x3 subgrid, as determined by the beginRow and beginCol parameters
      into a sorted order and check for duplicates. if there are duplicates, this section is not valid and returns 0 for the square_worker;*/

    int square[9] = {0}; //1d array to hold sorted 3x3 square

    for (i = beginRow; i < beginRow + 3; ++i) {
        for (j = beginCol; j < beginCol + 3; ++j) {
            int val = sudokuboard[i][j];
            /*if the corresponding array element for the value is 0, it has not been seen and
		we will input this value to the sorted column array. */
            if (square[val-1] == 0 && val > 0) {
                square[val-1] = val;
            }
            /*if the value is not 0, then the value is a duplicate and the sudoku puzzle
		  is not solved or valid so the value of square_worker in valid is 0. */
            else{
                valid[subgridCt] = 0;
                subgridCt++;
                pthread_exit(0);
            }
        }
    }
    valid[subgridCt] = 1;
    subgridCt++;
    pthread_exit(0);
}
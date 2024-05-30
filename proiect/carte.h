#ifndef proiect_CARTE_H
#define proiect_CARTE_H
#define NUM_ANGAJATI 3
struct book{
    int id;
    int pages;
};


int generate_aleator_number(int mini, int maxi);
void generate_and_print_books(struct book *books, int no_books);
void sum_step_by_step(int *sum, struct book *books, int no_books);
int suma_pag_interval(int *semi_sums, int start, int end);
int max(int a, int b);
void books_distribution (struct book *books, int no_books, int borders[NUM_ANGAJATI - 1]);
#endif


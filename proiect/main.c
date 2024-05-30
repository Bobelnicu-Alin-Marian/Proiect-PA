#include <stdio.h>
#include <stdlib.h>
#include "carte.h"
#include <time.h>
#define NO_ANGAJATI 3
#define NUM_SETS 10
int main(){
    struct book *books;
    int no_books;
    long int sum_pages;
    srand(time(NULL)); // Inițializare seed pentru funcția rand()

    //Afisarea datelor de intrare, obtinute prin randomizare
    for (int set = 0; set < NUM_SETS; set++) {
        printf("\n\nSetul %d:\n", set + 1);
        no_books = generate_aleator_number(9, 15);
        books = malloc(no_books * sizeof(struct book));
        printf("Numarul de carti:%d\n", no_books);
        generate_and_print_books(books, no_books);
        int borders[NO_ANGAJATI - 1] = {0};
        books_distribution(books, no_books, borders);
        printf("\n\n");
        //Afisare rezultate finale
        for(int i = 0; i< NO_ANGAJATI; i++){
            sum_pages=0;
            printf("Angajatul %d: ", i+1);
            int start = (i == 0) ? 0 : borders[i - 1] + 1;
            int end = (i == NO_ANGAJATI - 1) ? no_books - 1 : borders[i];
            for (int j = start; j <= end; j++) {
                printf("%d ", books[j].pages);
                sum_pages += books[j].pages;
            }
            printf("  ( Suma = %ld pagini )", sum_pages); //suma totala a paginilor alocate fiecarui angajat
            printf("\n");
        }
    }
    return 0;
}

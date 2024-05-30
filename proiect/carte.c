#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include "carte.h"
#define NO_ANGAJATI 3
#define AUX INT_MAX

// Functie pentru generarea de numere aleatoare
int generate_aleator_number(int mini, int maxi) {
    return mini + rand() % (maxi - mini + 1);
}
// Functie pentru generarea numarului de pagini pentru fiecare carte si afisarea acestora
void generate_and_print_books(struct book *books, int no_books){
    srand(time(NULL)); // Inițializare seed pentru funcția rand()
    for(int i=0; i < no_books; i++){
        books[i].id = i+1;
        books[i].pages = generate_aleator_number(100, 2000);
        printf("\nCartea %d: %d pagini", books[i].id, books[i].pages);
    }
}
// Functie pentru calcularea sumei paginilor, la fiecare pas
void sum_step_by_step(int *progressive_sum, struct book *books, int no_books) {
    progressive_sum[0] = books[0].pages;
    for (int i = 1; i < no_books; i++) {
        progressive_sum[i] = progressive_sum[i - 1] + books[i].pages;
    }
}
// Functie pentru calcularea unei sume pe un anumit interval
int suma_pag_interval(int *progressive_sum, int start, int end) {
    if (start == 0) {
        return progressive_sum[end];
    } else {
        return progressive_sum[end] - progressive_sum[start - 1];
    }
}
// Functie pentru maximul dintre doua numere
int max(int a, int b) {
    return (a > b) ? a : b;
}
// Functie pentru o distribuires cat mai echilibrata a cartilor
void books_distribution (struct book *books, int no_books, int borders[NO_ANGAJATI - 1]) {
    int progressive_sum[no_books];
    sum_step_by_step(progressive_sum, books, no_books);

    int matrix[no_books + 1][NO_ANGAJATI + 1];
    int root[no_books + 1][NO_ANGAJATI + 1];

    // Inițializare
    for (int i = 0; i <= no_books; i++) {
        for (int j = 0; j <= NO_ANGAJATI; j++) {
            matrix[i][j] = (j == 0 && i == 0) ? 0 : AUX;
            root[i][j] = -1;
        }
    }
    // Calcularea valorilor matrix
    for (int j = 1; j <= NO_ANGAJATI; j++) {
        for (int i = 1; i <= no_books; i++) {
            for (int k = 0; k < i; k++) {
                int sum = suma_pag_interval(progressive_sum, k, i - 1);
                if (matrix[i][j] > max(matrix[k][j - 1], sum)) {
                    matrix[i][j] = max(matrix[k][j - 1], sum);
                    root[i][j] = k;
                }
            }
        }
    }

    // Reconstruirea punctelor de taiere
    int index = no_books;
    for (int j = NO_ANGAJATI; j > 1; j--) {
        borders[j - 2] = root[index][j] - 1;
        index = root[index][j];
    }
}

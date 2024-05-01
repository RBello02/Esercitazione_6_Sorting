#include <chrono>
#include <iostream>
#include <unistd.h>
#include <string>
//#include <numeric>
#include <vector>
//#include <algorithm>
#include "SortingAlgorithm.hpp"

#include<cstdlib>           // librerie per la generazione di numeri casuali
#include<ctime>

using namespace std;

void carico ( unsigned int* vettore , unsigned int dimensione, unsigned int massimo)
{
    for (unsigned int i = 0; i<dimensione; i++)
    {
        vettore[i] = rand()%massimo+1;
    }
}
void print_1(vector <unsigned int> vettore , unsigned int dimensione)
{
    cout << "[ ";
    for (unsigned int i = 0; i < dimensione-1; i++)
        cout << vettore[i] << "; ";
    cout <<vettore[dimensione-1] <<"]"<<endl;
    cout << endl;
}
void print_2(vector <unsigned int> vettore , unsigned int dimensione, double time)
{
    cout << "[ " ;
    for (unsigned int i = 0; i < dimensione-1; i++)
        cout << vettore[i] << "; ";
    cout <<vettore[dimensione-1] <<"]"<<endl;
    cout << endl;
    cout << "TIME FOR SORTING: "<< time << endl;
}




int main(int argc, char ** argv)
{

    /*
    CONSIDERO UN VETTORE ORDINATO DA 1 A N E PERTURBO UN QUARTO DEL VETTORE CON VARIABILI CASUALI
    */

    unsigned int massimo = 100; // il numero intero massimo che posso ottenere con rand
    unsigned int numero_vettori = 3;

    unsigned int dimensione = stoi(argv[1]); // metodo per convertire la stringa argv[1] in un intero, questa è la dimensione del mio vettore
    //cout << dimensione << endl;
    double media_merge = 0;
    double media_buble = 0;
    for (unsigned int j = 0; j < numero_vettori; j++)            // considero solo i vettori con dimensione >= 4
    {
        unsigned int* vettore = new unsigned int [dimensione];           // creo il vettore dinamico
        carico(vettore, dimensione, massimo);           // carico i vettori con 1/differenziale dei dati perturbati e il restante ordinato
        vector<unsigned int> vettore_per_sorting_merge(vettore,vettore + dimensione); // il metodo MergeSort vuole un vettore definito con vector, io così lo converto
        vector<unsigned int> vettore_per_sorting_bubble = vettore_per_sorting_merge; // effettuo una copia di questo vettore


        chrono::steady_clock::time_point t_begin_merge = chrono::steady_clock::now();

        SortLibrary::MergeSort(vettore_per_sorting_merge);

        chrono::steady_clock::time_point t_end_merge = chrono::steady_clock::now();

        double timeElapsed_M = chrono::duration_cast<chrono::microseconds>(t_end_merge-t_begin_merge).count();

        chrono::steady_clock::time_point t_begin_bubble= chrono::steady_clock::now();

        SortLibrary::BubbleSort(vettore_per_sorting_bubble);

        chrono::steady_clock::time_point t_end_bubble = chrono::steady_clock::now();

        double timeElapsed_B = chrono::duration_cast<chrono::microseconds>(t_end_bubble-t_begin_bubble).count();

        media_merge = media_merge + timeElapsed_M;    // questo in realtà rappresenta la somma, successivamente divido per il numero di vettori
        media_buble = media_buble + timeElapsed_B;

        delete [] vettore;       // chiamo il distruttore
    }

    media_merge = media_merge/numero_vettori;
    media_buble = media_buble/numero_vettori;

    cout << "TIME FOR MERGE SORT: "<< media_merge << endl;
    cout << "TIME FOR BUBLE SORT: "<< media_buble << endl;


    // NOTO CHE PER DIMENSIONI DEL VETTORE MOLTO PICCOLE BUBBLE SORT E' PIU' VELOCE DI MERGE SORT, ALL'AUMENTARE DELLA DIMENSIONE QUESTO ANDAMENTO SI INVERTE.

    return 0;
}


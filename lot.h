/*********************************************************************
 * LOT.H
 * EN: Library with functions and struct related to lots.
 * PT: Biblioteca com funcoes e estruturas relacionada a terrenos.
 *********************************************************************/
#ifndef _LOT
    #define _LOT
    #include <stdio.h>
    #include "lot_category.h"
    #include "triangle.h"
    #include "rectangle.h"
    #include "trapezoid.h"

    /*
     * EN: Struct with information of a certain lot. Includes its shape and its information, soil type, m2 price and its area.
     * PT: Estrutura com informacoes de um terreno. Inclui sua forma e informacoes relacionada a ela, tipo de solo. preco por m2 e sua area.
     */
    typedef struct{
        Lot_Union lot;
        char soil_type;
        unsigned int price_m2;
        float area;
    } Lot;

    void read_lot(Lot *, int, FILE *);
    void area_lot(Lot *, int);
    float price_lot(Lot *);
    int is_lot_clayey(Lot *);
    int compare_area_lot(Lot *, Lot *);

#endif

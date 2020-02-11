/*********************************************************************
 * LOT.H
 * EN: Library with functions and struct related to lots.
 * PT: Biblioteca com funcoes e estruturas relacionada a terrenos.
 *********************************************************************/
#ifndef _APT
    #define _APT
    #include <stdio.h>
    typedef struct{
        unsigned int rooms,
                     parking,
                     floor,
                     max_floor,
                     m2_price;
        float area;
        char leisure_area;
    } Apartment;

    void read_apartment(Apartment *, FILE *);
    float price_apartment(Apartment *);

#endif

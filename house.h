/*********************************************************************
 * LOT.H
 * EN: Library with functions and struct related to lots.
 * PT: Biblioteca com funcoes e estruturas relacionada a terrenos.
 *********************************************************************/
#ifndef _HOUSE
    #define _HOUSE
    #include <stdio.h>
    typedef struct{
        unsigned int rooms,
                     parking,
                     num_pav,
                     m2_price_pav,
                     m2_price_out;
        float pav_area, outside_area;
    } House;

    void read_house(House *, FILE *);
    float price_house(House *);
    int check_house_area(House *, float);
    int compare_room_quantity_house(House *, House *);

#endif
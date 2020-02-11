#include <stdio.h>
#include "house.h"

/*
 * EN: Read house's information from a file.
 * PT: Le informacao da casa de um arquivo.
 */
void read_house(House *house, FILE *arc)
{
    fscanf(arc, "%u%*c%u%*c%u%*c%f%*c%u%*c%f%*c%u%*c%*c", &house->rooms,
                                                          &house->parking,
                                                          &house->num_pav,
                                                          &house->pav_area,
                                                          &house->m2_price_pav,
                                                          &house->outside_area,
                                                          &house->m2_price_out);
}

/*
 * EN: Returns house's price after calculating it.
 * PT: Retorna o preco da casa depois de o calcular.
 */
float price_house(House *house)
{
    return (float) ((float) house->m2_price_pav * house->pav_area * (float) house->num_pav + (float) house->m2_price_out * house->outside_area);
    //(float) was used to garanty prop
}

/*
 * EN: Returns 1 if the constructed area of the house is over a certain limit
 * PT: Retorna 1 se o a area construida e acima de um limite.
 */
int check_house_area(House * house, float area_limit)
{
    if(house->pav_area * (float) house->num_pav > area_limit)
        return 1;
    return 0;
}

/*
 * EN: Compares the quantity of rooms of two houses. Returns 1 if house1 has less rooms, 2 if they have the same quantity and 0 if house1 has more rooms.
 * PT: Compara a quantidade de quartos de duas casas. Retorna 1 se house1 tem menos quarto, 2 se a quantidade de quartos sao iguais e 0 se a house1 tem
 * mais quartos.
 */
int compare_room_quantity_house(House *house1, House *house2)
{
    if(house1->rooms < house2->rooms)
        return 1;
    if(house1->rooms == house2->rooms)
        return 2;
    return 0;
}
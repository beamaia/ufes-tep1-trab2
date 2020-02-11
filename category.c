#include <stdio.h>
#include "category.h"
#include "lot.h"
#include "house.h"
#include "apt.h"

/*
 * EN: Reads the property after being informed its tag. Returns 1 if the property type exists.
 * PT: Le o imovel apos ser informado o seu tag. Retorna 1 caso o tipo do imovel existe.
 */
int read_category(Category *cat, int tag, FILE *arc)
{
    switch (tag)
    {
        case 1: read_lot(&cat->lot, tag, arc);
                return 1;
        case 2: read_lot(&cat->lot, tag, arc);
                return 1;
        case 3: read_lot(&cat->lot, tag, arc);
                return 1;
        case 4: read_house(&cat->house, arc);
                return 1;
        case 5: read_apartment(&cat->apt, arc);
                return 1;
        default: return 0;
    }
}

/*
 * EN: Calculates the area (if not informed during read_category) of the property based on ints tag.
 * PT: Calcula a area (caso não foi informado durante a leitura do arquivo) do imovel baseada no seu tag.
 */
void area_category(Category *cat, int tag)
{
    switch (tag)
    {
        case 1: area_lot(&cat->lot, tag);
        case 2: area_lot(&cat->lot, tag);
        case 3: area_lot(&cat->lot, tag);
        default: return;
    }
}

/*
 * EN: Calculates the price of the property based on ints tag and then afterwards return the value.
 * PT: Calcula o preco do imovel baseada no seu tag e depois retorna o valor.
  */
float price_category(Category *cat, int tag)
{
    switch (tag)
    {
        case 1: return price_lot(&cat->lot);
        case 2: return price_lot(&cat->lot);
        case 3: return price_lot(&cat->lot);
        case 4: return price_house(&cat->house);
        case 5: return price_apartment(&cat->apt);
        default: return 0;
    }
}

/*
 * EN: Checks if the property is clayey or not based on its tag.
 * PT: Verifica se um imovel e argilosa baseada no seu tag.
 */
int check_if_clayey_category(Category *cat, int tag)
{
    if(tag == 1 || tag == 2 || tag == 3)
        return is_lot_clayey(&cat->lot);
    return 0;
}

/*
 * EN: If the property is a house, returns 1 or 0 if the house is above a certain area limit, otherwise returns 0.
 * PT: Se o imovel for uma casa, retorna 1 ou 0 se a casa e acima dum certo limite de area, se nao retorna 0.
 */
int check_if_house_limit_category(Category *cat, int tag, float limit)
{
    if(tag == 4)
        return check_house_area(&cat->house, limit);
    return 0;
}

/*
 * EN: If the property is a house, return the value of the comparison of the function compare_room_quantity_house.
 * PT: Se um imovel for uma casa, retorna o valor da comparacao da funcao compare_room_quantity_house.
 */
int compare_room_quantity_category(Category *cat1, Category *cat2, int tag1, int tag2)
{
    if(tag1 == 4 && tag2 == 4)
        return compare_room_quantity_house(&cat1->house, &cat2->house);
    return 0;
}

/*
 * EN: If the property is a lot, return the value of the comparison of the compare_area_lot.
 * PT: Se o imovel for um terreno, retorna o valor da comparacao da funcao compare_area_lot.
 */
int compare_area_category(Category *cat1, Category *cat2, int tag1, int tag2)
{
    if((tag1 == 1 || tag1 == 2 || tag1 == 3) && (tag2 == 1 || tag2 == 2 || tag2 == 3))
        return compare_area_lot(&cat1->lot, &cat2->lot);
    return 0;
}


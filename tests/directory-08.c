/*
  Test du module directory.

  Teste le rétrécissement du directory.
*/

#include <stdlib.h>

#include <directory.h>

int main(void)
{
    struct dir *dir = dir_create(20);
    dir_insert(dir, "Colonel Moutarde", "06789435351");
    dir_insert(dir, "Caporal Ketchup", "0678346533");
    dir_insert(dir, "Sergent Mayo", "06723236533");
    dir_insert(dir, "Adjudant Barbecue", "01723236533");
    dir_insert(dir, "Lieutenant Aioli", "02733236533");
    dir_insert(dir, "Soldat Savora", "02444444444");
    dir_insert(dir, "Commandant Cornichon", "08444444444");
    dir_insert(dir, "Général Motors", "99444444444");
    dir_insert(dir, "Jean Louis Roch", "23444444444");
    dir_print(dir);
    dir_delete(dir, "Colonel Moutarde");
    dir_delete(dir, "Caporal Ketchup");
    dir_delete(dir, "Sergent Mayo");
    dir_delete(dir, "Adjudant Barbecue");
    dir_delete(dir, "Lieutenant Aioli");
    dir_delete(dir, "Soldat Savora");
    dir_delete(dir, "Commandant Cornichon");
    dir_delete(dir, "Général Motors");
    dir_print(dir);
    dir_free(dir);

    return EXIT_SUCCESS;
}

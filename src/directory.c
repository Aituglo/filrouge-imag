#include <stdlib.h>
#include <stdio.h>

#include <directory.h>
#include <contact.h>
#include <hash.h>

struct dir{
  uint32_t len;
  struct contact *listes[];
};

/*
  Renvoie le nombre de contact de l'annuaire
*/
uint32_t dir_size(struct dir *dir){
  uint32_t k = 0;

  for(uint32_t i = 0; i < dir->len; i++){
    k += taille_contact(dir->listes[i]);
  }

  return k;
}


/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
    (void)len;

    // TODO : Trouver la bonne taille pour l'allocution
    struct dir *directory = malloc(sizeof(uint32_t) + len*get_cell_size());

    directory->len = len;

    for(uint32_t i = 0; i < len; i++){
      directory->listes[i] = NULL;
    }

    return directory;
}

void dir_increase(struct dir *dir){
  uint32_t current_size = dir->len;
  uint32_t new_size = current_size * 2;

  struct dir *new_dir = dir_create(new_size);

  for(uint32_t i = 0; i < dir->len; i++){
    change_contact_dir(dir->listes[i], new_dir->listes, new_size);
  }

  dir->len = new_size;
  *dir->listes = new_dir->listes;
  
}

void dir_decrease(struct dir *dir){
  uint32_t current_size = dir->len;
  uint32_t new_size = current_size / 2;

  if (new_size < 10){
    new_size = 10;
  }

  struct dir *new_dir = dir_create(new_size);

  for(uint32_t i = 0; i < dir->len; i++){
    change_contact_dir(dir->listes[i], new_dir->listes, new_size);
  }

  dir->len = new_size;
  *dir->listes = new_dir->listes;
}

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir, const char *name, const char *num)
{
    (void)dir;
    (void)name;
    (void)num;
      
    uint32_t key = hash(name) % dir->len;
    
    return inserer_contact(&dir->listes[key], name, num);
  
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    (void)dir;
    (void)name;

    uint32_t key = hash(name) % dir->len;

    return lookup_contact(&dir->listes[key], name);
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    (void)dir;
    (void)name;

    uint32_t key = hash(name) % dir->len;

    delete_contact(&dir->listes[key], name);

}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    (void)dir;
    for(uint32_t i = 0; i < dir->len; i++){
      free_contacts(&dir->listes[i]);
    }

    free(dir);

}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    (void)dir;

    uint32_t contacts_size = dir_size(dir);

    if((float) contacts_size > 0.75 * dir->len){
      dir_increase(dir);
    }else if ((float) contacts_size < 0.15 * dir->len ){
      dir_decrease(dir);
    }

    for(uint32_t i = 0; i < dir->len; i++){
      printf("Contacts dans la liste %u : \n", i);
      afficher_contacts(dir->listes[i]);
    }
    printf("\n\n");
}

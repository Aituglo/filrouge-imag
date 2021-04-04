#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <stdint.h>

/*
  Structure de données représentant un annuaire.
  Son contenu est détaillé dans directory.c.
*/
struct dir;

/*
  Récupère la taille d'un annuaire
*/
uint32_t dir_size(struct dir *dir);

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
extern struct dir *dir_create(uint32_t len);

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
extern char *dir_insert(struct dir *dir, const char *name, char *num);

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun
  contact ne correspond, retourne NULL.
*/
extern const char *dir_lookup_num(struct dir *dir, const char *name);

/*
  Effectue un agrandissement d'un annuaire
*/
extern void dir_increase(struct dir *dir);

/*
  Effectue un rétrécissement d'un annuaire
*/
extern void dir_decrease(struct dir *dir);

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
extern void dir_delete(struct dir *dir, const char *name);

/*
  Fait une copie d'un dir dans un autre
*/
extern void dir_copie(struct dir *previous_dir, struct dir *new_dir, uint32_t size);

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
extern void dir_free(struct dir *dir);

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
extern void dir_print(struct dir *dir);

#endif /* _DIRECTORY_H_ */

#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
struct contact;

/*
  Insère un contact
*/
char *inserer_contact(struct contact **con, const char *name, char *tel);

/*
  Renvoie la taille d'un contact
*/
size_t get_cell_size();

/*
  Change tous les contacts d'une liste dans un autre annuaire
*/
void change_contact_dir(struct contact *c, struct contact *new_con[], uint32_t new_size);

/*
  Cherche un contact et le renvoie
*/
char *lookup_contact(struct contact **con, const char *name);

/*
  Permet d'afficher les contacts d'une liste chainé
*/
void afficher_contacts(struct contact *c);

/*
  Supprime un contact
*/
void delete_contact(struct contact **con, const char *name);

/*
  Renvoie la taille d'une liste de contact
*/
uint32_t taille_contact(struct contact *c);

/*
  Free une liste chainé
*/
void free_contacts(struct contact **con);

#endif /* _CONTACT_H_ */

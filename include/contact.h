#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
struct contact;

/* TOUT DOUX: à compléter */
/* Profitez de cette période sombre pour braver les interdits et rétablir le contact. */

char *inserer_contact(struct contact **con, const char *name, char *tel);

char *lookup_contact(struct contact **con, const char *name);

void afficher_contacts(struct contact *c);

void delete_contact(struct contact **con, const char *name);

uint32_t taille_contact(struct contact *c);

#endif /* _CONTACT_H_ */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <hash.h>
#include <contact.h>

struct contact {
    
    const char *name;

    char *tel;

    struct contact *suiv;
};

uint32_t taille_contact(struct contact *c){

    uint32_t k = 0;
    while (c != NULL) {
        k++;
        c = c->suiv;
    }

    return k;
}

size_t get_cell_size(){
    return sizeof(struct contact);
}

void change_contact_dir(struct contact *c, struct contact **new_con[], uint32_t new_size){

    while (c != NULL) {
        uint32_t key = hash(c->name) % new_size;
        inserer_contact(&new_con[key], c->name, c->tel);
        c = c->suiv;
    }

}

char *inserer_contact(struct contact **con, const char *name, char *tel)
{
    struct contact sent = { "", "", *con };
    struct contact *queue = &sent;

    /* On parcourt la liste jusqu'au dernier contact */
    while (queue->suiv != NULL) {
        if(queue->suiv->name == name){
            char *last_tel = queue->suiv->tel;
            queue->suiv->tel = tel;
            *con = sent.suiv;
            return last_tel;
        }
        queue = queue->suiv;
    }

    /* Allocation et insertion du contact */
    queue->suiv = malloc(sizeof(struct contact));
    
    //assert(queue->suiv != NULL);

    queue->suiv->name = name;
    queue->suiv->tel = tel;
    queue->suiv->suiv = NULL;

    /* On fait pointer l'argument con vers la nouvelle liste */
    *con = sent.suiv;

    return NULL;
}

char *lookup_contact(struct contact **con, const char *name){

    struct contact sent = { "", "", *con };
    struct contact *queue = &sent;

    /* On parcourt la liste jusqu'au dernier contact */
    while (queue->suiv != NULL) {
        if(queue->suiv->name == name){
            return queue->suiv->tel;
        }
        queue = queue->suiv;
    }

    return NULL;
}

void free_contacts(struct contact **con)
{
    struct contact sent = { "", "", *con };
    struct contact *queue = &sent;

    /* On parcourt la liste jusqu'au dernier contact */
    while (queue->suiv != NULL) {
        struct contact *to_free = queue->suiv;
        if(to_free->suiv != NULL){
            queue->suiv = to_free->suiv;
        }
        free(to_free);
        queue = queue->suiv;
    }
}

void delete_contact(struct contact **con, const char *name)
{

    struct contact sent = { "", "", *con };
    struct contact *c = &sent;

    while (c->suiv != NULL && c->suiv->name != name) {
        c = c->suiv;
    }

    /* Cas occurence trouvée */
    if (c->suiv != NULL) {
        /*
            On rechaine les 2 contacts de la liste entourant l'occurrence et on
            libère le contact trouvé.
        */
        struct contact *to_free = c->suiv;
        c->suiv = to_free->suiv;
        free(to_free);
    }
    *con = sent.suiv;
}

void afficher_contacts(struct contact *c)
{
    while (c != NULL) {
        printf("%s : %s\n", c->name, c->tel);
        c = c->suiv;
    }
}
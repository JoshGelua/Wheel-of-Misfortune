#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "family.h"

/* Number of word pointers allocated for a new family.
   This is also the number of word pointers added to a family
   using realloc, when the family is full.
*/
static int family_increment = 0;


/* Set family_increment to size, and initialize random number generator.
   The random number generator is used to select a random word from a family.
   This function should be called exactly once, on startup.
*/
void init_family(int size) {
    family_increment = size;
    srand(time(0));
}


/* Given a pointer to the head of a linked list of Family nodes,
   print each family's signature and words.

   Do not modify this function. It will be used for marking.
*/
void print_families(Family* fam_list) {
    int i;
    Family *fam = fam_list;

    while (fam) {
        printf("***Family signature: %s Num words: %d\n",
               fam->signature, fam->num_words);
        for(i = 0; i < fam->num_words; i++) {
            printf("     %s\n", fam->word_ptrs[i]);
        }
        printf("\n");
        fam = fam->next;
    }
}


/* Return a pointer to a new family whose signature is
   a copy of str. Initialize word_ptrs to point to
   family_increment+1 pointers, numwords to 0,
   maxwords to family_increment, and next to NULL.
*/
Family *new_family(char *str) {
    // Copy signature of the new_family from str.
    int length_of_str = strlen(str);
    Family *new_family = malloc(sizeof(Family));
    new_family->signature = malloc(sizeof(char)*(length_of_str+1));
    strcpy(new_family->signature, str);
    new_family->word_ptrs = malloc(sizeof(char *) * (family_increment+1));
    new_family->num_words = 0;
    new_family->max_words = family_increment;
    new_family->next = NULL;
    return new_family;
}


/* Add word to the next free slot fam->word_ptrs.
   If fam->word_ptrs is full, first use realloc to allocate family_increment
   more pointers and then add the new pointer.
*/
void add_word_to_family(Family *fam, char *word) {
    if(fam->num_words == fam->max_words){
      fam->word_ptrs = (char **)realloc(fam->word_ptrs,
      sizeof(char *)*(fam->max_words+family_increment));
      fam->max_words = fam->max_words+family_increment;
    }
    fam->word_ptrs[fam->num_words] = word;
    fam->num_words++;
}


/* Return a pointer to the family whose signature is sig;
   if there is no such family, return NULL.
   fam_list is a pointer to the head of a list of Family nodes.
*/
Family *find_family(Family *fam_list, char *sig) {
  Family *fam = fam_list;
  while (fam != NULL) {
      if (strcmp(fam->signature, sig)==0){
        return fam;
      }
      fam = fam->next;
  }
  return NULL;
}


/* Return a pointer to the family in the list with the most words;
   if the list is empty, return NULL. If multiple families have the most words,
   return a pointer to any of them.
   fam_list is a pointer to the head of a list of Family nodes.
*/
Family *find_biggest_family(Family *fam_list) {
  Family *fam = fam_list;
  int max = 0;
  //Iterate family to find what max is.
  while (fam) {
      if (fam->num_words >= max){
        max = fam->num_words;
      }
      fam = fam->next;
  }
  //Iterate family again to return family with max num words.
  Family *fam_locked = fam_list;
  while (fam_locked){
    if (fam_locked->num_words == max){
      return fam_locked;
    }
    fam_locked = fam_locked->next;
  }
  return NULL;
}



/* Deallocate all memory rooted in the List pointed to by fam_list. */
void deallocate_families(Family *fam_list) {
    Family *curr = fam_list;
    Family *next;
    while (curr){
      next = curr->next;
      free(curr->word_ptrs);
      free(curr->signature);
      free(curr);
      curr = next;
    }
}


/* Generate and return a linked list of all families using words pointed to
   by word_list, using letter to partition the words.

   Implementation tips: To decide the family in which each word belongs, you
   will need to generate the signature of each word. Create only the families
   that have at least one word from the current word_list.
*/
Family *generate_families(char **word_list, char letter) {
  Family *head = NULL;
  Family *last = NULL;
  int i = 0;
  char signature[(strlen(word_list[0])+1)];
  while (word_list[i] != NULL){
    strcpy(signature, word_list[i]);
    for (int j = 0; j < strlen(word_list[0]); j++){
      if (word_list[i][j]!=letter){
          signature[j] = '-';
      }
    }
    signature[strlen(word_list[0])] = '\0';
    char *sig = signature;
    if (head == NULL){
      head = new_family(sig);
      add_word_to_family(head, word_list[i]);
      last = head;
    }
    else if (find_family(head, sig) == NULL){
      Family *new = new_family(sig);
      add_word_to_family(new, word_list[i]);
      last -> next = new;
      last = last -> next;
    }
    else{
      Family *curr = find_family(head, sig);
      add_word_to_family(curr, word_list[i]);
    }
    i++;
  }
  return head;
}



/* Return the signature of the family pointed to by fam. */
char *get_family_signature(Family *fam) {
    return (fam->signature);
}


/* Return a pointer to word pointers, each of which
   points to a word in fam. These pointers should not be the same
   as those used by fam->word_ptrs (i.e. they should be independently malloc'd),
   because fam->word_ptrs can move during a realloc.
   As with fam->word_ptrs, the final pointer should be NULL.
*/
char **get_new_word_list(Family *fam) {
    char **new_words;
    new_words = (char **)malloc(sizeof(char *)*(fam->num_words+1));
    for (int i = 0; i < fam->num_words+1; i++){
      if (i==fam->num_words){
        char *word = NULL;
        new_words[i] = word;
      }
      else{
        char *word;
        word = fam->word_ptrs[i];
        new_words[i] = word;
      }
    }
    return new_words;
}


/* Return a pointer to a random word from fam.
   Use rand (man 3 rand) to generate random integers.
*/
char *get_random_word_from_family(Family *fam) {
    srand(time(NULL));
    int random_number = (rand()%(fam->num_words));
    char *random_word = fam->word_ptrs[random_number];
    return random_word;
}

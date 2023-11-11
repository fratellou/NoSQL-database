#include "double_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"

// This function implements the double linked set operation
void Dlist(char *db_file, char **query, char *req) {
  char **line = malloc(MAX_LEN * sizeof(char *));
  int size = 0;
  int isnt_empty = 0;
  DSet *set = createDSet(MAX_LEN);
  STRUCT(line, db_file, isnt_empty, query[1], size, "dset:");
  if (isnt_empty) {
    for (int i = 1; i < size; i++) {
      DSADD(set, line[i]);
    }
  }
  Dset_commands(query, set, req);
  write_Dset(db_file, set, query[1], "dset:");
  free_Dset(set);
  for (int i = 0; i < size; i++) {
    free(line[i]);
  }
  free(line);
}

// This function takes a query and a double linked set object as parameters and
// executes the command specified in the query
void Dset_commands(char **query, DSet *set, char *req) {
  if (!strcmp(query[0], "DSADD")) {
    strcpy(req, DSADD(set, query[2]));
  } else if (!strcmp(query[0], "DSREM")) {
    strcpy(req, DSREM(set, query[2]));
  } else if (!strcmp(query[0], "DSISMEMBER")) {
    if (!DSISMEMBER(set, query[2]))
      strcpy(req, "FALSE");
    else
      strcpy(req, "TRUE");
  } else {
    ERROR;
  }
}

// This function creates a new double linked set
DSet *createDSet(int size) {
  DSet *set = (DSet *)malloc(sizeof(DSet));
  set->size = size;
  set->buckets = malloc(sizeof(Node_Dset **) * size);
  for (int i = 0; i < size; i++) {
    set->buckets[i] = NULL;
  }
  return set;
}

// This function calculates the hash value for a given key
int Dset_calc(char *key) {
  int hash = 0;
  for (int i = 0; i < (int)strlen(key); i++) {
    hash += (int)key[i];
  }
  return hash % MAX_LEN;
}

// This function adds an element to the double linked set
char *DSADD(DSet *set, char *element) {
  int index = Dset_calc(element);
  if (set->buckets[index] != NULL) {
    ERROR;
    return NULL;
  }
  Node_Dset *newNode = (Node_Dset *)malloc(sizeof(Node_Dset));
  newNode->element = element;
  newNode->prev = NULL;
  newNode->next = set->buckets[index];
  if (set->buckets[index] != NULL) {
    set->buckets[index]->prev = newNode;
  }
  set->buckets[index] = newNode;
  return element;
}

// This function removes an element from the double linked set
char *DSREM(DSet *set, char *element) {
  int index = Dset_calc(element);
  if (set->buckets[index] == NULL) {
    return NULL;
  } else {
    char *element = set->buckets[index]->element;
    Node_Dset *nextNode = set->buckets[index]->next;
    Node_Dset *prevNode = set->buckets[index]->prev;
    if (nextNode != NULL) {
      nextNode->prev = prevNode;
    }
    if (prevNode != NULL) {
      prevNode->next = nextNode;
    }
    set->buckets[index] = NULL;
    return element;
  }
  return NULL;
}

// This function checks if an element is a member of the double linked set
int DSISMEMBER(DSet *set, char *element) {
  int index = Dset_calc(element);
  if (set->buckets[index] == NULL) return 0;
  if (strcmp(set->buckets[index]->element, element) == 0) {
    return 1;
  }
  return 0;
}

// This function writes the contents of the double linked set to a file
void write_Dset(char *filename, DSet *set, char *struct_name,
                char *struct_type) {
  FILE *temp = fopen("temp.txt", "a+");
  FILE *fp = fopen(filename, "r");
  if (fp && temp) {
    char string[MAX_LEN];
    int new_input = 0;
    while (fgets(string, MAX_LEN, fp) != NULL) {
      char new_string[MAX_LEN];
      strcpy(new_string, string);
      char *istr = strtok(string, " ");
      char *second_word = strtok(NULL, " ");
      if (new_input == 0) {
        fprintf(temp, "%s %s ", struct_type, struct_name);
        for (int i = 0; i < MAX_LEN; i++) {
          if (set->buckets[i] != NULL)
            fprintf(temp, "%s ", set->buckets[i]->element);
        }
        fprintf(temp, "\n");
        new_input = 1;
      }
      if ((strcmp(istr, struct_type) == 0) &&
          (strcmp(second_word, struct_name) == 0)) {
        continue;
      } else {
        fprintf(temp, "%s", new_string);
      }
    }
    remove(filename);
    rename("temp.txt", filename);
  } else {
    ERROR;
  }
  fclose(fp);
  fclose(temp);
}

// This function frees the memory allocated for the double linked set object and
// its buckets
void free_Dset(DSet *set) {
  if (set == NULL) {
    return;
  }
  for (int i = 0; i < set->size; i++) {
    if (set->buckets[i] != NULL) {
      free(set->buckets[i]);
    }
  }
  free(set->buckets);
  free(set);
}
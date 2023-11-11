#ifndef DSET_H
#define DSET_H

typedef struct Node_Dset {
  char *element;
  struct Node_Dset *prev;
  struct Node_Dset *next;
} Node_Dset;

typedef struct DSet {
  Node_Dset **buckets;
  int size;
} DSet;

void Dlist(char *db_file, char **query, char *req);
void Dset_commands(char **query, DSet *set, char *req);
DSet *createDSet(int size);
int Dset_calc(char *key);
char *DSADD(DSet *set, char *element);
char *DSREM(DSet *set, char *element);
int DSISMEMBER(DSet *set, char *element);
void write_Dset(char *filename, DSet *set, char *struct_name,
                char *struct_type);
void free_Dset(DSet *set);
#endif
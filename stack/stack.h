typedef struct tag_obj 
{
    double data;
    struct tag_obj* next;
} OBJ;

OBJ* push(OBJ*, double);
OBJ* pop(OBJ*);
void free_stack(OBJ*);
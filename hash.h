#define HASH_CAPACITY 1000

typedef struct hashnode hashNode;
typedef struct hashnode{
	int type;	
	char *lit;
	hashNode *next;
}hashNode;


hashNode *HashTable[HASH_CAPACITY];

extern char *yytext;

void initMe(void);
int hashAddress(char *lit);
hashNode* hashInsert(int type, char *lit);
void hashPrint(void);
hashNode* hashFind(char *lit, int address);
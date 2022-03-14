#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SECTION 1: AVL Tree */
struct node;
typedef struct node *ptr, *avlTree;

/* Structure to represent the tree's node */
struct node {
    char name[30];
    char gender;
    char dateOfAdmission[10];
    char dateOfBirth[10];
    char illness[50];
    char address[30];
    char bloodType[4];
    ptr left;
    ptr right;
    int height;
};

/* Explanation of all functions used for the tree is under the main function */

avlTree insert(avlTree tree, ptr data);

avlTree delete(avlTree tree, char name[30]);

ptr createNode(ptr n, char name[], char gender, char dateOfAdmission[10], char dateOfBirth[10], char illness[50],
               char address[30], char bloodType[2]);

int heightOf(avlTree tree);

avlTree rotateRight1(avlTree tree);

avlTree rotateRight2(avlTree tree);

avlTree rotateLeft1(avlTree tree);

avlTree rotateLeft2(avlTree tree);

int MAX(int height1, int height2);

ptr MIN(avlTree tree);

int getBF(ptr node);

ptr searchForPatient(avlTree tree, char name[30]);

avlTree searchAndUpdate(avlTree tree, char name[30]);

void printInLexicographicOrder(avlTree tree);

void sameIllness(avlTree tree, char illness[30]);

void printNodeInfo(ptr n);

void printNodeInfile(FILE *file, ptr n);

void writeOnFile(FILE *write, avlTree tree);

void printMenu1();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* SECTION 2: Hash Table */

/* A variable that stores the size of the hash table */
int SIZE = 0;

struct hashNode;
typedef struct hashNode *pntr, *hashTable;

/* Structure to represent the hash table's cell */

struct hashNode {
    char name[30];
    char gender;
    char dateOfAdmission[10];
    char dateOfBirth[10];
    char illness[50];
    char address[30];
    char bloodType[3];
};

/* Explanation of all functions used for the hash table is under the main function */

int nextPrime(int i);

int isPrime(int number);

double loadFactor(hashTable ht[]);

int asciiToDecimal(char name[]);

int hashValue(char *name, int i);

void printHashTable(hashTable n[]);

void insertToHashTable(hashTable **ht, pntr n);

pntr searchInHT(hashTable ht[], char name[50]);

int deleteFromHT(hashTable ht[], char name[]);

void printHTInfile(FILE *file, pntr n);

void printMenu2();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int choice, readMode = 0;
    char cho[3];
    FILE *patients, *hash;
    patients = fopen("C:\\Users\\HP\\CLionProjects\\readFileP3\\patients.txt", "r");
    avlTree patientTree = NULL;
    ptr pData = malloc(sizeof(struct node));
    /* Print the menu and asked the user what operation to perform */
    printMenu1();
    gets(cho);
    choice = strtol(cho, NULL, 10);
    while (choice != 7) {
        switch (choice) {
            case 1: {
                //read the file and store it in a string
                int i = 0;
                char data[2000];
                while (1) {
                    int ch = getc(patients);
                    if (ch == EOF) {
                        break;
                    }
                    data[i++] = (char) ch;
                }
                data[i] = '\0';
                //trim the file by #
                char *p = strtok(data, "#\n");
                while (p != NULL) {
                    strcpy(pData->name, p);
                    p = strtok(NULL, "#\n");
                    pData->gender = p[0];
                    p = strtok(NULL, "#\n");
                    strcpy(pData->dateOfAdmission, p);
                    p = strtok(NULL, "#\n");
                    strcpy(pData->dateOfBirth, p);
                    p = strtok(NULL, "#\n");
                    strcpy(pData->illness, p);
                    p = strtok(NULL, "#\n");
                    strcpy(pData->address, p);
                    p = strtok(NULL, "#\n");
                    strcpy(pData->bloodType, p);
                    p = strtok(NULL, "#\n");
                    patientTree = insert(patientTree, pData);
                }
                readMode++;
                printf("The file was read successfully!^-^\n");
                break;
            }
            case 2:
                if (readMode != 0) {
                    printf("Enter the data of a patient\n");
                    printf("Name:");
                    gets(pData->name);
                    printf("Gender:");
                    char g[5];
                    gets(g);
                    pData->gender = g[0];
                    printf("Date Of Admission:");
                    gets(pData->dateOfAdmission);
                    printf("Date Of Birth:");
                    gets(pData->dateOfBirth);
                    printf("Illness:");
                    gets(pData->illness);
                    printf("Address:");
                    gets(pData->address);
                    printf("Blood Type:");
                    gets(pData->bloodType);
                    patientTree = insert(patientTree, pData);
                    printf("The patient information was added successfully! ^-^\n");
                } else
                    printf("You must read the file first!\n");
                break;
            case 3:
                if (readMode != 0) {
                    printf("Enter the patient's name to update his information:\n");
                    char name[30];
                    gets(name);
                    if (searchForPatient(patientTree, name) != NULL) {
                        printf("The patient was found, do you want to update his information?\n");
                        printf("1- Yes\n2- No\n");
                        char ans[3];
                        gets(ans);
                        if (strtol(ans, NULL, 10) == 1) {
                            patientTree = searchAndUpdate(patientTree, name);
                        } else if (strtol(ans, NULL, 10) == 2) {
                            printf("OK!\n");
                        } else
                            printf("invalid value\n");
                    } else
                        printf("Sorry, There is no patient with this name!\n");
                } else
                    printf("You must read the file first!\n");
                break;
            case 4:
                if (readMode != 0) {
                    printInLexicographicOrder(patientTree);
                } else
                    printf("You must read the file first!\n");
                break;
            case 5:
                if (readMode != 0) {
                    printf("Enter the illness you want to search for:\n");
                    char illness[50];
                    gets(illness);
                    sameIllness(patientTree, illness);
                } else
                    printf("You must read the file first!\n");
                break;
            case 6:
                if (readMode != 0) {
                    printf("Enter the patient's name to delete his information\n");
                    char name[30];
                    gets(name);
                    patientTree = delete(patientTree, name);
                } else
                    printf("You must read the file first!\n");
                break;
            default:
                printf("Invalid value!\n");
        }
        printMenu1();
        gets(cho);
        choice = strtol(cho, NULL, 10);
    }
    if (readMode != 0) {
        hash = fopen("C:\\Users\\HP\\CLionProjects\\project3\\patients_hash.txt", "w");
        writeOnFile(hash, patientTree);
        printf("DONE!\n");
        fclose(hash);
        ////////////////////////////////////////////////////////////////////
        hash = fopen("C:\\Users\\HP\\CLionProjects\\project3\\patients_hash.txt", "r");
        pntr patient = malloc(sizeof(struct hashNode));
        /*read the file*/
        int i = 0;
        int s = 0;
        char data[2000];
        while (1) {
            int ch = getc(hash);
            if (ch == EOF) {
                break;
            }
            if (ch == '\n') {
                s++;
                if (s % 7 == 0) {
                    SIZE++;
                }
            }
            data[i++] = (char) ch;
        }
        data[i] = '\0';
        fclose(hash);
        SIZE = nextPrime((int) (SIZE * 1.3));
        hashTable *pHashTable;
        pHashTable = malloc(SIZE * sizeof(struct hashNode));
        for (int y = 0; y < SIZE; ++y) {
            pHashTable[y] = NULL;
        }
        /*trim the file by \n*/
        char *p = strtok(data, "\n");
        while (p != NULL) {
            strcpy(patient->name, p);
            p = strtok(NULL, "\n");
            patient->gender = p[0];
            p = strtok(NULL, "\n");
            strcpy(patient->dateOfAdmission, p);
            p = strtok(NULL, "\n");
            strcpy(patient->dateOfBirth, p);
            p = strtok(NULL, "\n");
            strcpy(patient->illness, p);
            p = strtok(NULL, "\n");
            strcpy(patient->address, p);
            p = strtok(NULL, "\n");
            strcpy(patient->bloodType, p);
            p = strtok(NULL, "\n");
            /*insert*/
            insertToHashTable(&pHashTable, patient);
        }
        printMenu2();
        gets(cho);
        choice = strtol(cho, NULL, 10);
        while (choice != 7) {
            switch (choice) {
                case 1: {
                    printHashTable(pHashTable);
                    break;
                }
                case 2:
                    printf("The SIZE of table is: %d\n", SIZE);
                    break;
                case 3:
                    printf("The used hash function: Linear Probing (  h(key) = (h(key) + i) %% SIZE  )\n");
                    break;
                case 4:
                    printf("Enter the data of a patient\n");
                    printf("Name:");
                    gets(patient->name);
                    printf("Gender:");
                    char g[5];
                    gets(g);
                    patient->gender = g[0];
                    printf("Date Of Admission:");
                    gets(patient->dateOfAdmission);
                    printf("Date Of Birth:");
                    gets(patient->dateOfBirth);
                    printf("Illness:");
                    gets(patient->illness);
                    printf("Address:");
                    gets(patient->address);
                    printf("Blood Type:");
                    gets(patient->bloodType);
                    insertToHashTable(&pHashTable, patient);
                    printf("The patient information was added successfully! ^-^\n");
                    break;
                case 5:
                    printf("Enter the name of the patient you are searching for:\n");
                    char searchedName[50];
                    gets(searchedName);
                    if (searchInHT(pHashTable, searchedName) == NULL) {
                        printf("Sorry, there is no patient with this name in the record!\n");
                    } else {
                        printf("This patient is in the record, his information:\n");
                        printf("Name: %s\n", searchInHT(pHashTable, searchedName)->name);
                        printf("Gender: %c\n", searchInHT(pHashTable, searchedName)->gender);
                        printf("Date of admission: %s\n", searchInHT(pHashTable, searchedName)->dateOfAdmission);
                        printf("Date of birth: %s\n", searchInHT(pHashTable, searchedName)->dateOfBirth);
                        printf("Illness: %s\n", searchInHT(pHashTable, searchedName)->illness);
                        printf("Address: %s\n", searchInHT(pHashTable, searchedName)->address);
                        printf("Blood Type: %s\n", searchInHT(pHashTable, searchedName)->bloodType);
                    }
                    break;
                case 6:
                    printf("Enter the name of the patient you want to delete his information:\n");
                    char nameToDelete[50];
                    gets(nameToDelete);
                    if (deleteFromHT(pHashTable, nameToDelete) == 0) {
                        printf("Sorry, there is no patient with this name in the record!\n");
                    } else {
                        printf("The deletion process was successful :)\n");
                    }
                    break;
                default:
                    printf("Invalid value!\n");
            }
            printMenu2();
            gets(cho);
            choice = strtol(cho, NULL, 10);
        }
        hash = fopen("C:\\Users\\HP\\CLionProjects\\project3\\patients_hash.txt", "w");
        for (int y = 0; y < SIZE; ++y) {
            printHTInfile(hash, pHashTable[y]);
        }
        printf("DONE!\n");
        fclose(hash);
    }
    printf("Have a nice day ^-^\nGood bye <3");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* SECTION 1: AVL Tree */

/* Displaying the menu of AVL Tree on the screen */
void printMenu1() {
    printf("****************************************************\n");
    printf("Please select an option:\n");
    printf("1- Read The File & Load The Data\n");
    printf("2- Insert A New Patient\n");
    printf("3- Find A Patient & Update His Information\n");
    printf("4- List All Patients In Lexicographic Order\n");
    printf("5- List All Patients That Have The Same Illness\n");
    printf("6- Delete A Patient From The System\n");
    printf("7- Save all words in file \"patients_hash.txt\"\n");
    printf("****************************************************\n");
}

/*Create a new node with the given information if the patient, and give left and right NULL value, height is assigned to 0*/
ptr createNode(ptr n, char name[], char gender, char dateOfAdmission[], char dateOfBirth[], char illness[],
               char address[], char bloodType[]) {
    n = malloc(sizeof(struct node));
    strcpy(n->name, name);
    n->gender = gender;
    strcpy(n->dateOfAdmission, dateOfAdmission);
    strcpy(n->dateOfBirth, dateOfBirth);
    strcpy(n->illness, illness);
    strcpy(n->address, address);
    strcpy(n->bloodType, bloodType);
    n->left = NULL;
    n->right = NULL;
    n->height = 0;
    return n;
}

/* Add a new node to the tree */
avlTree insert(avlTree tree, ptr data) {
    /* If there is no node in the tree, we add the inserted node to be the tree then we return its value */
    if (tree == NULL)
        return createNode(tree, data->name, data->gender, data->dateOfAdmission, data->dateOfBirth, data->illness,
                          data->address,
                          data->bloodType);
    /* If the name of the patient that we want to add is smaller than the name of the patient that the tree
     * is pointing to, go to the left of the tree and so on */
    else if (strcasecmp(data->name, tree->name) < 0) {
        tree->left = insert(tree->left, data);
    /* If the name of the patient that we want to add is bigger than the name of the patient that the tree
     * is pointing to, go to the right of the tree and so on */
    } else if (strcasecmp(data->name, tree->name) > 0) {
        tree->right = insert(tree->right, data);
    /* If the names are matching we do not add this node and return the tree value */
    } else
        return tree;

    /* Tree height update */
    tree->height = 1 + MAX(heightOf(tree->right), heightOf(tree->left));

    /*If the tree is unbalanced, we will re-balance it*/

    /* Case 1: Left Left Rotate */
    if (getBF(tree) > 1 && getBF(tree->left) >= 0) {
        return rotateRight1(tree);
    }
    /* Case 2: Left Right Rotate */
    if (getBF(tree) > 1 && getBF(tree->left) < 0) {
        return rotateLeft2(tree);
    }
    /* Case 3: Right Right Rotate */
    if (getBF(tree) < -1 && getBF(tree->right) <= 0) {
        return rotateLeft1(tree);
    }
    /* Case 4: Right Left Rotate */
    if (getBF(tree) < -1 && getBF(tree->left) > 0) {
        return rotateRight2(tree);
    }
    /* Return the node pointer (as-is) */
    return tree;
}

/* Delete a specific node whose key (patient name) was entered (It returns the tree after delete the node) */
avlTree delete(avlTree tree, char name[30]) {
    /* If the tree is empty, we return its value */
    if (tree == NULL) {
        printf("Sorry, There is no patient with this name!\n");
        return tree;
    } else {
        /* If the name of patient to be deleted is greater than the name of the root,
         * then its located in the right subtree */
        if (strcasecmp(name, tree->name) > 0) {
            tree->right = delete(tree->right, name);
        /* If the name of patient to be deleted is smaller than the name of the root,
         * then its located in the left subtree */
        } else if (strcasecmp(name, tree->name) < 0) {
            tree->left = delete(tree->left, name);
        /* If the name of the patient to be deleted is same as the name of the root,
         * then we will delete this node */
        } else {
            /* If the node has one or no child */
            if (tree->left == NULL || tree->right == NULL) {
                /* If tree->left is not equal to NULL then tmp will equal tree->left else it will equal tree->right */
                ptr tmp = tree->left ? tree->left :
                          tree->right;
                /* If the node has no child then delete the node */
                if (tmp == NULL) {
                    tmp = tree;
                    tree = NULL;
                /* If the node has one child then delete the node and put the child in his place */
                } else {
                    *tree = *tmp;
                }
                free(tmp);
            /* If the node has two children then get the smallest children in all sub tree and put it in the node place */
            } else {
                ptr tmp = MIN(tree->right);
                strcpy(tree->name, tmp->name);
                tree->gender = tmp->gender;
                strcpy(tree->dateOfAdmission, tmp->dateOfAdmission);
                strcpy(tree->dateOfBirth, tmp->dateOfBirth);
                strcpy(tree->illness, tmp->illness);
                strcpy(tree->address, tmp->address);
                strcpy(tree->bloodType, tmp->bloodType);
                tree->right = delete(tree->right, tmp->name);
            }
        }
        /* If just one node is in the tree then return */
        if (tree == NULL) {
            return tree;
        }
        /* Tree Height update */
        tree->height = 1 + MAX(heightOf(tree->right), heightOf(tree->left));

        /* If the tree is unbalanced, we will re-balance it */

        /* Case 1 : Left Left Rotate */
        if (getBF(tree) > 1 && getBF(tree->left) >= 0) {
            return rotateRight1(tree);
        }
        /* Case 2 : Left Right Rotate */
        if (getBF(tree) > 1 && getBF(tree->left) < 0) {
            return rotateLeft2(tree);
        }
        /* Case 3 : Right Right Rotate */
        if (getBF(tree) < -1 && getBF(tree->right) <= 0) {
            return rotateLeft1(tree);
        }
        /* Case 4 : Right Left Rotate */
        if (getBF(tree) < -1 && getBF(tree->left) > 0) {
            return rotateRight2(tree);
        }
    }
    return tree;
}

/* Function to perform Left Left Rotate */
avlTree rotateRight1(avlTree tree) {
    ptr newTree, temp;
    newTree = tree->left;
    temp = newTree->right;
    newTree->right = tree;
    tree->left = temp;
    newTree->height = 1 + MAX(heightOf(newTree->right), heightOf(newTree->left));
    tree->height = 1 + MAX(heightOf(tree->right), heightOf(tree->left));
    return newTree;
}

/* Function to perform Right Left Rotate */
avlTree rotateRight2(avlTree tree) {
    ptr newTree;
    tree->right = rotateRight1(tree->left);
    newTree = rotateLeft1(tree);
    return newTree;
}

/* Function to perform Right Right Rotate */
avlTree rotateLeft1(avlTree tree) {
    ptr newTree, temp;
    newTree = tree->right;
    temp = newTree->left;
    tree->right = temp;
    newTree->left = tree;
    newTree->height = 1 + MAX(heightOf(newTree->left), heightOf(newTree->right));
    tree->height = 1 + MAX(heightOf(tree->left), heightOf(tree->right));
    return newTree;
}

/* Function to perform Left Right Rotate */
avlTree rotateLeft2(avlTree tree) {
    ptr newTree;
    tree->left = rotateLeft1(tree->left);
    newTree = rotateRight1(tree);
    return newTree;
}

/* Function to return the height of the tree value */
int heightOf(avlTree tree) {
    if (tree != NULL)
        return tree->height;
    else
        return 0;
}

/* Function to get the maximum height */
int MAX(int height1, int height2) {
    if (height1 > height2)
        return height1;
    else
        return height2;
}

/* Function to return the node with the smallest key (name) in the tree */
ptr MIN(avlTree tree) {
    ptr temp = tree;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

/* Function to get the balanced factor of the node */
int getBF(ptr node) {
    int BF = 0;
    if (node != NULL)
        BF = (heightOf(node->left) - heightOf(node->right));
    return BF;
}

/* Function to return the node we search for */
ptr searchForPatient(avlTree tree, char name[30]) {
    if (tree != NULL) {
        /* If the name is larger than the root's name, then it lies in the right subtree, search there */
        if (strcasecmp(name, tree->name) > 0) {
            tree = searchForPatient(tree->right, name);
        /* If the name is smaller than the root's name, then it lies in the left subtree, search there */
        } else if (strcasecmp(name, tree->name) < 0) {
            tree = searchForPatient(tree->left, name);
        /* If the name is as same as the root's name, then return it */
        } else {
            return tree;
        }
    /* Not found case */
    } else
        return NULL;
}

/* Function to search for a patient and update its information */
avlTree searchAndUpdate(avlTree tree, char name[30]) {
    /* If the patient existing, then delete the node and insert a new node with updated information */
    if (searchForPatient(tree, name) != NULL) {
        tree = delete(tree, name);
        ptr patient = malloc(sizeof(struct node));
        if (patient != NULL) {
            printf("Enter the updated data of a patient\n");
            printf("Name:");
            gets(patient->name);
            printf("Gender:");
            char g[5];
            gets(g);
            patient->gender = g[0];
            printf("Date Of Admission:");
            gets(patient->dateOfAdmission);
            printf("Date Of Birth:");
            gets(patient->dateOfBirth);
            printf("Illness:");
            gets(patient->illness);
            printf("Address:");
            gets(patient->address);
            printf("Blood Type:");
            gets(patient->bloodType);
            printf("operation accomplished successfully! ^-^\n");
            tree = insert(tree, patient);
        }
        return tree;
    /* If the patient is not found, then return the tree */
    } else {
        printf("Sorry, There is no patient with this name!\n");
        return tree;
    }
}

/* Search in all nodes for the entered illness and print the information of the patient who has the same illness */
void sameIllness(avlTree tree, char illness[20]) {
    if (tree != NULL) {
        sameIllness(tree->left, illness);
        if (strcasecmp(illness, tree->illness) == 0) {
            printNodeInfo(tree);
        }
        sameIllness(tree->right, illness);
    }
}

/* Print the information of the tree's nodes inOrder (In Lexicographic Order) at the screen */
void printInLexicographicOrder(avlTree tree) {
    if (tree != NULL) {
        printInLexicographicOrder(tree->left);
        printNodeInfo(tree);
        printInLexicographicOrder(tree->right);
    }
}

/* Print the node information at the screen */
void printNodeInfo(ptr n) {
    printf("--------------------------------------------\n");
    printf("Name: %s\n", n->name);
    printf("Gender: %c\n", n->gender);
    printf("Date of admission: %s\n", n->dateOfAdmission);
    printf("Date of birth: %s\n", n->dateOfBirth);
    printf("Illness: %s\n", n->illness);
    printf("Address: %s\n", n->address);
    printf("Blood Type: %s\n", n->bloodType);
}

/* Print the node information in the file */
void printNodeInfile(FILE *file, ptr n) {
    fprintf(file, "%s\n", n->name);
    fprintf(file, "%c\n", n->gender);
    fprintf(file, "%s\n", n->dateOfAdmission);
    fprintf(file, "%s\n", n->dateOfBirth);
    fprintf(file, "%s\n", n->illness);
    fprintf(file, "%s\n", n->address);
    fprintf(file, "%s\n", n->bloodType);
}

/* Print the information of the tree's nodes inOrder (In Lexicographic Order) in the file */
void writeOnFile(FILE *write, avlTree tree) {
    if (tree != NULL) {
        writeOnFile(write, tree->left);
        printNodeInfile(write, tree);
        writeOnFile(write, tree->right);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* SECTION 2: Hash Table */

void printMenu2() {
    printf("****************************************************\n");
    printf("Please select an option:\n");
    printf("1- Print Hashed Table\n");
    printf("2- Print Out Table Size\n");
    printf("3- Print Out The Used Hash Function\n");
    printf("4- Insert A New Record Into The Hash Table\n");
    printf("5- Search For A Specific Patient\n");
    printf("6- Delete A Specific Record\n");
    printf("7- Save Hash Table Back To File\n");
    printf("****************************************************\n");
}

/* Function to get the smaller next prime is bigger than the entered number */
int nextPrime(int i) {
    if (i <= 1) {
        return 2;
    }
    int primeNumber = i;
    while (1) {
        primeNumber++;
        if (isPrime(primeNumber) == 1)
            break;
    }
    return primeNumber;
}

/* Function to check if the number is prime or not, if its prime return 1 else return 0 */
int isPrime(int number) {
    if (number <= 1)
        return 0;
    else if (number <= 3)
        return 1;
    else {
        if (number % 2 == 0 || number % 3 == 0)
            return 0;
        for (int i = 5; i * i <= number; i = i + 6) {
            if (number % i == 0 || number % (i + 2) == 0)
                return 0;
        }
        return 1;
    }
}

/* Get the value of string (convert the string from ascii to decimal) */
int asciiToDecimal(char name[]) {
    int Value = 0;
    for (int i = 0; i < strlen(name); ++i) {
        Value += name[i];
    }
    return Value;
}

/* Function to return the hash value (Linear Probing) */
int hashValue(char *name, int i) {
    int hkey = asciiToDecimal(name) % SIZE;
    return (hkey + i) % SIZE;
}

/* Function to insert a new cell to the hash table */
void insertToHashTable(hashTable **ht, pntr n) {
    /* If the load factor is larger than or equal to 0.75, perform REHASHING */
    if (loadFactor(*ht) >= 0.75) {
        /* Re-add the information to a table whose size is larger than that of the first table */
        int pSize = SIZE;
        SIZE = nextPrime(2 * SIZE);
        hashTable *prev = *ht;
        *ht = malloc(SIZE * sizeof(struct hashNode));
        for (int i = 0; i < SIZE; ++i) {
            (*ht)[i] = NULL;
        }
        for (int i = 0; i < pSize; ++i) {
            if (prev[i])
                insertToHashTable(ht, prev[i]);
        }
        free(prev);
    }
    /* Insert the node information into the table (array) based on the hash value of the name */
    for (int i = 0; i < SIZE; ++i) {
        /* If the cell is empty the add the node, else add 1 to i to get another hash value and so on*/
        if ((*ht)[hashValue(n->name, i)] == NULL) {
            (*ht)[hashValue(n->name, i)] = malloc(sizeof(struct hashNode));
            strcpy((*ht)[hashValue(n->name, i)]->name, n->name);
            (*ht)[hashValue(n->name, i)]->gender = n->gender;
            strcpy((*ht)[hashValue(n->name, i)]->dateOfAdmission, n->dateOfAdmission);
            strcpy((*ht)[hashValue(n->name, i)]->dateOfBirth, n->dateOfBirth);
            strcpy((*ht)[hashValue(n->name, i)]->illness, n->illness);
            strcpy((*ht)[hashValue(n->name, i)]->address, n->address);
            strcpy((*ht)[hashValue(n->name, i)]->bloodType, n->bloodType);
            break;
        }
    }
}

/* Get the value of the load factor */
double loadFactor(hashTable ht[]) {
    int counter = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (ht[i] != NULL) {
            counter++;
        }
    }
    return (double) counter / SIZE;
}
/* Function to search for specific patient */
pntr searchInHT(hashTable ht[], char name[50]) {
    int i = 0;
    do {
        /* If the name is same as the node's name (search in the index that is equal to hash value)
         * then return, else add 1 to i */
        if (strcasecmp(ht[hashValue(name, i)]->name, name) == 0)
            return ht[hashValue(name, i)];
        else
            i++;
    } while (i < SIZE);
    /* The name is not found */
    return NULL;
}

/*Delete a specific patient from the array by going to the index that equal hash value,
 * if the keys are not equals then add 1 to i, else delete it and return 1*/
int deleteFromHT(hashTable ht[], char name[]) {
    int i = 0;
    do {
        if (strcasecmp(ht[hashValue(name, i)]->name, name) == 0) {
            ht[hashValue(name, i)] = NULL;
            return 1;
        } else
            i++;
    } while (i < SIZE);
    /* The name is not found */
    return 0;
}

/* Print the content of the table at the screen */
void printHashTable(hashTable n[]) {
    printf("Key\t||\t\tData\n");
    for (int i = 0; i < SIZE; ++i) {
        printf("--------------------------------------------\n");
        if (n[i] != NULL) {
            printf("\t||\tName: %s\n\t||", n[i]->name);
            printf("\tGender: %c\n\t||", n[i]->gender);
            printf("\tDate of admission: %s\n", n[i]->dateOfAdmission);
            printf("%2d\t||", i);
            printf("\tDate of birth: %s\n\t||", n[i]->dateOfBirth);
            printf("\tIllness: %s\n\t||", n[i]->illness);
            printf("\tAddress: %s\n\t||", n[i]->address);
            printf("\tBlood Type: %s\n", n[i]->bloodType);
        } else {
            printf("%2d\t||", i);
            printf("\t\n");
        }
    }
    printf("--------------------------------------------\n");
}

/* Print the content of the table in the file */
void printHTInfile(FILE *file, pntr n) {
    if (n != NULL) {
        fprintf(file, "%s\n", n->name);
        fprintf(file, "%c\n", n->gender);
        fprintf(file, "%s\n", n->dateOfAdmission);
        fprintf(file, "%s\n", n->dateOfBirth);
        fprintf(file, "%s\n", n->illness);
        fprintf(file, "%s\n", n->address);
        fprintf(file, "%s\n", n->bloodType);
    }
}

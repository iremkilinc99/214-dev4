#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct nodeFemale {
    int rank;
    char *FemaleName;
    int numberofFemale;
    char *year;
    char type;
    struct nodeFemale *next;
};

struct nodeMale {
    int rank;
    char *MaleName;
    int numberofMale;
    char *year;
    char  type;
    struct nodeMale *next;
};

typedef struct nodeFemale NodeFemale;
typedef struct nodeMale NodeMale;

NodeFemale *makenodeFemale (int,char *,int, char*);
NodeMale *makenodeMale (int,char*, int, char*);
void appendFemale (NodeFemale*);
void appendMale (NodeMale*);
void print();
void clear();
void s_or_v(char *target, char *mode, double);
void flag(char *, char *, char * , double );
void bubblesortFemales(NodeFemale *);
void bubblesortMales(NodeMale *);
//NodeFemale **searchFemale(char*,char*);
//NodeMale **searchMale(char*,char*);

NodeFemale *headF = NULL;
NodeFemale *tailF = NULL;
NodeMale *headM = NULL;
NodeMale *tailM = NULL;


int main(int argc, char **argv) {
    FILE *fptr;
    char *tok, *del = "\t", *tokenName ;
    int tokenRank = 0, tokenNumberOf, m = 0, f = 0, thFile = 0, count = 0 ;
    double totalNames = 0;
    char buffer[10000] , year[5] ;


    NodeMale *tempNodeMale = NULL;
    NodeFemale *tempNodeFemale = NULL;

    for (int i = 0;i < argc; i++) {
        if (strstr(argv[i], "txt") != NULL) {
            count++;
        }
        if (strcmp(argv[1], "-v") != 0 && strcmp(argv[1], "-s") != 0 && strcmp(argv[1],"-sv") !=0 && strcmp(argv[1],"-vs") !=0 ) {
            printf("ERROR.WRONG TYPE.TRY AGAIN.");
            exit(1);
        }
    }


        if (strstr(argv[3], "txt") != NULL) thFile = 3;

        else thFile = 4;


        while (0 < count) {
            fptr = fopen(argv[thFile], "r");

            tempNodeFemale=(NodeFemale*)malloc(sizeof(NodeFemale));
            tempNodeMale=(NodeMale*)malloc(sizeof(NodeMale));

            while ((fgets(buffer, 10000, fptr)) != NULL) {

                tok = strtok(buffer, del);
                tokenRank = atoi(tok);
                tok = strtok(NULL, del);
                tokenName = (char *) malloc(sizeof(char) * strlen(tok) + 1);
                strcpy(tokenName, tok);
                tok = strtok(NULL, del);
                tokenNumberOf = atoi(tok);
                totalNames += atoi(tok);
                strncpy(year, argv[thFile] + 5, 4);

                tempNodeMale = makenodeMale(tokenRank, tokenName, tokenNumberOf,year);
                appendMale(tempNodeMale);
                m++;

                tok = strtok(NULL, del);
                tokenName= (char *)realloc(tokenName,sizeof(char) * strlen(tok) + 1);
                strcpy(tokenName, tok);
                tok = strtok(NULL, del);
                tokenNumberOf= atoi(tok);
                totalNames += atoi(tok);

                tempNodeFemale = makenodeFemale(tokenRank , tokenName , tokenNumberOf , year);
                appendFemale(tempNodeFemale);
                f++;

            }
            count--;
            fclose(fptr);
            thFile++;
        }


        bubblesortFemales(headF);
        bubblesortMales(headM);
        print();

        for(int i=0;i<=strlen(argv[2]);i++) {
            if (argv[2][i] >= 65 && argv[2][i] <= 90)
            argv[2][i] = argv[2][i] + 32;
        }


        if (strstr(argv[3], "txt") != NULL) {
            s_or_v(argv[2], argv[1], totalNames);
        } else {
            flag(argv[2], argv[3], argv[1], totalNames);
        }

        free(tempNodeFemale);
        free(tempNodeMale);
        clear(); // to prevent memory leak;

        return 0;
    }




NodeFemale *makenodeFemale (int rank,char *name,int number,char *year) {
    NodeFemale *new;
    if ( (new = (NodeFemale *) malloc( sizeof(NodeFemale) ) )!= NULL) {
        new->rank=rank;
        new->FemaleName=(char*)malloc(sizeof(char)*strlen(name)+1);
        strcpy(new->FemaleName,name);
        new->numberofFemale=number;
        new->year=(char*)malloc(sizeof(char)*strlen(year)+1);
        strcpy(new->year,year);
        new->type='F';
        new -> next = NULL;
    }
    else {
        printf("Out of memory!\n");
        exit(0);
    }
    return new;
}

NodeMale *makenodeMale (int rank,char* name,int number,char *year) {
    NodeMale *new;
    if ( (new = (NodeMale *) malloc( sizeof(NodeMale) ) )!= NULL) {
        new->rank=rank;
        new->MaleName=(char*)malloc(sizeof(char)*strlen(name)+1);
        strcpy(new->MaleName,name);
        new->numberofMale=number;
        new->year=(char*)malloc(sizeof(char)*strlen(year)+1);
        strcpy(new->year,year);
        new->type='M';
        new -> next = NULL;
    }
    else {
        printf("Out of memory!\n");
        exit(0);
    }
    return new;
}


void appendFemale (NodeFemale *p) {

    if (headF == NULL) {
        headF = p;
        tailF = p;
    }
    else {
        tailF->next = p;
        tailF = p;
    }

    printf("%s (female) eklendi (year %s ) .\n", p->FemaleName,p->year);
}

void appendMale (NodeMale *p) {

    if (headM == NULL) {
        headM = p;
        tailM = p;
    }
    else {
        tailM->next = p;
        tailM = p;
    }

    printf("%s (male) eklendi (year %s ).\n",p->MaleName,p->year);
}

void print() {
    NodeFemale *tmp;
    NodeMale *tmp2;
    printf("\n");
    for (tmp = headF,tmp2=headM; tmp != NULL & tmp2 !=NULL; tmp = tmp->next, tmp2=tmp2->next)
        printf(" Sorted %i %s %i | %i %s %i \n",tmp->rank, tmp->FemaleName, tmp->numberofFemale,tmp2->rank,tmp2->MaleName,tmp2->numberofMale);
    printf("\n");

}

void clear() {
    NodeFemale *tmp,*tmp2;
    NodeMale *tmp3,*tmp4;
    for (tmp = headF,tmp3=headM; tmp != NULL & tmp3 !=NULL; tmp = tmp2 ,tmp3=tmp4) {
        tmp2 = tmp->next;
        tmp4=tmp3->next;
        free(tmp);
        free(tmp3);
    }
    headF = tailF = NULL; headM = tailM = NULL;
}

void s_or_v(char *target, char *mode , double total) {
    NodeFemale *tempFemale = NULL;
    NodeMale *tempMale = NULL;
    bool targetFound=false;


    if(strcmp(mode,"-vs") ==0 ||strcmp(mode,"-sv") == 0) strcpy(mode,"-v");

    for (tempFemale = headF; tempFemale != NULL; tempFemale = tempFemale->next) {

        if (strcmp(mode, "-s") == 0 & strcmp(tempFemale->FemaleName, target) == 0) {
            printf("rank %i number of people named %s is %i and percentage of %s is %f in (year) %s \n",
                   tempFemale->rank, tempFemale->FemaleName, tempFemale->numberofFemale, target,
                   tempFemale->numberofFemale * 100 / total, tempFemale->year);
            targetFound=true;
        } else if (strcmp(mode, "-v") == 0 & strstr(tempFemale->FemaleName, target) != NULL) {
            printf("rank %i number of people named %s that contains (%s) is %i and percentage of it is %f in (year) %s \n",
                   tempFemale->rank, tempFemale->FemaleName, target,tempFemale->numberofFemale,
                   tempFemale->numberofFemale * 100 / total, tempFemale->year);
            targetFound=true;

        }
    }


    for (tempMale = headM; tempMale != NULL; tempMale = tempMale->next) {

        if (strcmp(mode, "-s") == 0 & strcmp(tempMale->MaleName, target) == 0) {
            printf("rank %i number of people named %s is %i and percentage of %s is %f in (year) %s \n",
                   tempMale->rank, target, tempMale->numberofMale, tempMale->MaleName,
                   tempMale->numberofMale * 100 / total, tempMale->year);
            targetFound=true;
        } else if (strcmp(mode, "-v") == 0 & strstr(tempMale->MaleName, target) != NULL) {
            printf("rank %i number of people named %s that contains (%s) is %i and percentage of it is %f in (year) %s \n",
                   tempMale->rank, tempMale->MaleName,target, tempMale->numberofMale,
                   tempMale->numberofMale * 100 / total, tempMale->year);
            targetFound=true;
        }
    }

    if(!targetFound) printf("Target not found in linkedlists.");
}


void flag(char *target, char *flag, char *mode , double total) {

    if(strcmp(mode,"-vs") ==0 ||strcmp(mode,"-sv") ) strcpy(mode,"-v");

    bool targetFound = false;
    NodeFemale *tempFemale;
    NodeMale *tempMale;

    if (strcmp(flag, "-r") == 0) {

        for (tempFemale = headF; tempFemale != NULL; tempFemale = tempFemale->next) {
            if (strcmp(mode, "-s") == 0 & strcmp(tempFemale->FemaleName, target) == 0) {
                printf(" %s's rank  is %i in (year) %s \n", target, tempFemale->rank, tempFemale->year);
                targetFound = true;
            } else if (strcmp(mode, "-v") == 0 & strstr(tempFemale->FemaleName, target) != NULL) {
                printf(" %s's rank  is %i in (year) %s\n", tempFemale->FemaleName, tempFemale->rank,tempFemale->year);
                targetFound = true;
            }
        }

        for (tempMale = headM; tempMale != NULL; tempMale = tempMale->next) {
            if (strcmp(mode, "-s") == 0 & strcmp(tempMale->MaleName, target) == 0) {
                printf(" %s's rank  is %i in (year) %s \n", target, tempMale->rank,tempMale->year);
                targetFound = true;
            } else if (strcmp(mode, "-v") == 0 & strstr(tempMale->MaleName, target) != NULL) {
                printf(" %s's rank  is %i in (year) %s \n", tempMale->MaleName, tempMale->rank,tempMale->year);
                targetFound = true;
            }
        }
    }

    if (strcmp(flag, "-n") == 0) {

        for (tempFemale = headF; tempFemale != NULL; tempFemale = tempFemale->next) {
            if (strcmp(mode, "-s") == 0 & strcmp(tempFemale->FemaleName, target) == 0) {
                printf(" %s's usage  is %i in (year) %s \n", target, tempFemale->numberofFemale,tempFemale->year);
                targetFound = true;

            } else if (strcmp(mode, "-v") == 0 & strstr(tempFemale->FemaleName, target) != NULL) {
                printf("in\n");
                printf(" %s's usage  is %i in (year) %s \n", tempFemale->FemaleName, tempFemale->numberofFemale, tempFemale->year);
                targetFound = true;
            }
        }

        for (tempMale = headM; tempMale != NULL; tempMale = tempMale->next) {
            if (strcmp(mode, "-s") == 0 & strcmp(tempMale->MaleName, target) == 0) {
                printf(" %s's usage  is %i in (year) %s \n", target, tempMale->numberofMale, tempMale->year);
                targetFound = true;

            } else if (strcmp(mode, "-v") == 0 & strstr(tempMale->MaleName, target) != NULL) {
                printf(" %s's usage  is %i in (year) %s \n", tempMale->MaleName, tempMale->numberofMale , tempMale->year);
                targetFound = true;
            }
        }

    }


    if (strcmp(flag, "-p") == 0) {
        for (tempFemale = headF; tempFemale != NULL; tempFemale = tempFemale->next) {
            if (strcmp(mode, "-s") == 0 & strcmp(tempFemale->FemaleName, target) == 0) {
                printf("%s's percentage  is  %f in (year) %s \n", target, tempFemale->numberofFemale * 100 / total,tempFemale->year);
                targetFound = true;

            } else if (strcmp(mode, "-v") == 0 & strstr(tempFemale->FemaleName, target) != NULL) {
                printf("%s's percentage  is  %f in (year) %s  \n", tempFemale->FemaleName, tempFemale->numberofFemale * 100 / total,tempFemale->year);
                targetFound = true;

            }
        }

        for (tempMale = headM; tempMale != NULL; tempMale = tempMale->next) {
            if (strcmp(mode, "-s") == 0 & strcmp(tempMale->MaleName, target) == 0) {
                printf("%s's percentage  is  %f in (year) %s  \n", target, tempMale->numberofMale * 100 / total,tempMale->year);
                targetFound = true;

            } else if (strcmp(mode, "-v") == 0 & strstr(tempMale->MaleName, target) != NULL) {
                printf("%s's percentage  is  %f in (year) %s  \n", tempMale->MaleName, tempMale->numberofMale * 100 / total ,tempMale->year);
                targetFound = true;


            }
        }
    }


        if (strcmp(flag, "-rn") == 0 || strcmp(flag, "-nr") == 0) {
            for (tempFemale = headF; tempFemale != NULL; tempFemale = tempFemale->next) {
                if (strcmp(mode, "-s") == 0 & strcmp(tempFemale->FemaleName, target) == 0) {
                    printf("%s's rank and usage is %i %i in (year) %s \n", target, tempFemale->rank, tempFemale->numberofFemale ,tempFemale->year);
                    targetFound=true;

                } else if (strcmp(mode, "-v") == 0 & strstr(tempFemale->FemaleName, target) != NULL) {
                    printf("%s's rank and usage is %i %i in (year) %s \n", tempFemale->FemaleName, tempFemale->rank,tempFemale->numberofFemale ,tempFemale->year );
                    targetFound=true;
                }
            }

            for (tempMale = headM; tempMale != NULL; tempMale = tempMale->next) {
                if (strcmp(mode, "-s") == 0 & strcmp(tempMale->MaleName, target) == 0) {
                    printf("%s's rank and usage is %i %i in (year) %s  \n", target, tempMale->rank,tempMale->numberofMale,tempMale->year);
                    targetFound=true;

                } else if (strcmp(mode, "-v") == 0 & strstr(tempMale->MaleName, target) != NULL) {
                    printf("%s's rank and usage is %i %i in (year) %s \n", tempMale->MaleName, tempMale->rank,tempMale->numberofMale,tempMale->year);
                    targetFound=true;
                }
            }

        }


        if (strcmp(flag, "-rp") == 0 || strcmp(flag, "-pr") == 0) {
            for (tempFemale = headF; tempFemale != NULL; tempFemale = tempFemale->next) {
                if (strcmp(mode, "-s") == 0 & strcmp(tempFemale->FemaleName, target) == 0) {
                    printf("%s's rank and percentage is %i %f in (year) %s  \n", target, tempFemale->rank,tempFemale->numberofFemale *100/total,tempFemale->year);
                    targetFound=true;

                } else if (strcmp(mode, "-v") == 0 & strstr(tempFemale->FemaleName, target) != NULL) {
                    printf("%s's rank and percentage is %i %f in (year) %s \n", tempFemale->FemaleName, tempFemale->rank,tempFemale->numberofFemale *100/total,tempFemale->year);
                    targetFound=true;
                }
            }

            for (tempMale = headM; tempMale != NULL; tempMale = tempMale->next) {
                if (strcmp(mode, "-s") == 0 & strcmp(tempMale->MaleName, target) == 0) {
                    printf("%s's rank and percentage is %i %f in (year) %s \n", target, tempMale->rank,tempMale->numberofMale *100/total,tempMale->year);
                    targetFound=true;

                } else if (strcmp(mode, "-v") == 0 & strstr(tempMale->MaleName, target) != NULL) {
                    printf("%s's rank and percentage is %i %f in (year) %s \n", tempMale->MaleName, tempMale->rank,tempMale->numberofMale *100/total,tempMale->year);
                    targetFound=true;

                }
            }
        }

        if (strcmp(flag, "-np") == 0 || strcmp(flag, "-pn") == 0) {
            for (tempFemale = headF; tempFemale != NULL; tempFemale = tempFemale->next) {
                if (strcmp(mode, "-s") == 0 & strcmp(tempFemale->FemaleName, target) == 0) {
                    printf("%s's usage and percentage is %i %f in (year) %s \n", target, tempFemale->numberofFemale,tempFemale->numberofFemale *100/total,tempFemale->year);
                    targetFound=true;

                } else if (strcmp(mode, "-v") == 0 & strstr(tempFemale->FemaleName, target) != NULL) {
                    printf("%s's usage and percentage is %i %f in (year) %s \n", tempFemale->FemaleName, tempFemale->numberofFemale,tempFemale->numberofFemale *100/total,tempFemale->year);
                    targetFound=true;
                }
            }

            for (tempMale = headM; tempMale != NULL; tempMale = tempMale->next) {
                if (strcmp(mode, "-s") == 0 & strcmp(tempMale->MaleName, target) == 0) {
                    printf("%s's usage and percentage is %i %f in (year) %s  \n", target, tempMale->numberofMale ,tempMale->numberofMale *100/total,tempMale->year);
                    targetFound=true;

                } else if (strcmp(mode, "-v") == 0 & strstr(tempMale->MaleName, target) != NULL) {
                    printf("%s's usage and percentage is %i %f in (year) %s  \n", tempMale->MaleName, tempMale->numberofMale ,tempMale->numberofMale *100/total,tempMale->year);
                    targetFound=true;
                }
            }
                }


        if (strcmp(flag, "-rnp") == 0 || strcmp(flag, "-rpn") == 0 || strcmp(flag, "-prn") == 0 ||
            strcmp(flag, "-pnr") == 0 ||
            strcmp(flag, "-npr") == 0 || strcmp(flag, "-nrp") == 0) {

            for (tempFemale = headF; tempFemale != NULL; tempFemale = tempFemale->next) {

                if (strcmp(mode, "-s") == 0 & strcmp(tempFemale->FemaleName, target) == 0) {
                    printf("rank %i number of people named %s is %i and percentage of %s is %f in (year) %s \n",
                           tempFemale->rank, tempFemale->FemaleName, tempFemale->numberofFemale, target,
                           tempFemale->numberofFemale * 100 / total, tempFemale->year);
                    targetFound=true;

                } else if (strcmp(mode, "-v") == 0 & strstr(tempFemale->FemaleName, target) != NULL) {
                    printf("rank %i number of people named %s that contains (%s) is %i and percentage of it is %f in (year) %s \n",
                           tempFemale->rank, tempFemale->FemaleName, target, tempFemale->numberofFemale,
                          tempFemale->numberofFemale * 100 / total, tempFemale->year);
                    targetFound=true;

                }
            }

            for (tempMale = headM; tempMale != NULL; tempMale = tempMale->next) {
                if (strcmp(mode, "-s") == 0 & strcmp(tempMale->MaleName, target) == 0) {
                    printf("rank %i number of people named %s is %i and percentage of %s is %f in (year) %s \n",
                           tempMale->rank, target, tempMale->numberofMale, tempMale->MaleName,
                           tempMale->numberofMale * 100 / total, tempMale->year);
                    targetFound=true;

                } else if (strcmp(mode, "-v") == 0 & strstr(tempMale->MaleName, target) != NULL) {
                    printf("rank %i number of people named %s that contains (%s) is %i and percentage of it is %f in (year) %s \n",
                           tempMale->rank, tempMale->MaleName, target, tempMale->numberofMale,
                           tempMale->numberofMale * 100 / total, tempMale->year);
                    targetFound=true;

                }
            }

                }

        free(tempFemale);
        free(tempMale);

    if( !targetFound) printf("Target not found in linkedlists.");

}

void bubblesortFemales(NodeFemale *nodeFemale) {
    NodeFemale *tmp,*tmp2;
    char *tempName,*year;
    int tmpRank=0, tempNumber=0;

    for (tmp = headF; tmp != NULL; tmp = tmp->next) {
        for (tmp2 = tmp->next; tmp2 != NULL; tmp2 = tmp2->next) {

            for(int i=0;i<=strlen(tmp->FemaleName);i++){
                if(tmp->FemaleName[i] >=65 && tmp->FemaleName[i]<=90)
                    tmp->FemaleName[i] = tmp->FemaleName[i]+32;
            }


            for(int i=0;i<=strlen(tmp2->FemaleName);i++){
                if(tmp2->FemaleName[i] >=65 && tmp2->FemaleName[i]<=90)
                    tmp2->FemaleName[i] = tmp2->FemaleName[i]+32;
            }


            if (strcmp(tmp->FemaleName,tmp2->FemaleName) > 0) {

                tempName=(char*)malloc(sizeof(tmp->FemaleName));
                year=(char*)malloc(sizeof(tmp->year));

                tmpRank = tmp->rank;
                strcpy(tempName, tmp->FemaleName);
                tempNumber = tmp->numberofFemale;
                strcpy(year, tmp->year);

                tmp->rank = tmp2->rank;
                strcpy(tmp->FemaleName, tmp2->FemaleName);
                tmp->numberofFemale = tmp2->numberofFemale;
                strcpy(tmp->year, tmp2->year);

                tmp2->rank = tmpRank;
                strcpy(tmp2->FemaleName, tempName);
                tmp2->numberofFemale = tempNumber;
                strcpy(tmp2->year, year);

                 free(tempName);
                 free(year);

            }
        }
    }
}

void bubblesortMales(NodeMale *nodeMale) {
    NodeMale *tmp,*tmp2;
    char *tempName,*year;
    int tmpRank=0, tempNumber=0;

    for (tmp = headM; tmp != NULL; tmp = tmp->next) {
        for (tmp2 = tmp->next; tmp2 != NULL; tmp2 = tmp2->next) {

            for(int i=0;i<=strlen(tmp->MaleName);i++){
                if( tmp->MaleName[i] >=65 && tmp->MaleName[i] <=90)
                    tmp->MaleName[i] = tmp->MaleName[i]+32;
            }

            for(int i=0;i<=strlen(tmp2->MaleName);i++){
                if( tmp2->MaleName[i] >=65 && tmp2->MaleName[i]<=90)
                    tmp2->MaleName[i] = tmp2->MaleName[i]+32;
            }


            if (strcmp(tmp->MaleName,tmp2->MaleName) > 0) {

                tempName = (char *) malloc(sizeof(tmp->MaleName));
                year = (char *) malloc(sizeof(tmp->year));

                tmpRank = tmp->rank;
                strcpy(tempName, tmp->MaleName);
                tempNumber = tmp->numberofMale;
                strcpy(year, tmp->year);

                tmp->rank = tmp2->rank;
                strcpy(tmp->MaleName, tmp2->MaleName);
                tmp->numberofMale = tmp2->numberofMale;
                strcpy(tmp->year, tmp2->year);

                tmp2->rank = tmpRank;
                strcpy(tmp2->MaleName, tempName);
                tmp2->numberofMale = tempNumber;
                strcpy(tmp2->year, year);


                free(tempName);
                free(year);
            }
        }
    }
}






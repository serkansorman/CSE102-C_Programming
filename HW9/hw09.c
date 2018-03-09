#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 50
#define MAXRECORD 500

typedef struct record_s {
    int id;
    char number[NAMELEN];
    struct record_s *next;
} Record;

typedef struct person_s {
    int id;
    char name[NAMELEN];
    double expenditure;
    Record *numbers;
} Person;

typedef struct people_s {
    Person data[MAXRECORD];
    int size;
} People;

void writePeople(People people, char* filename) { /* Verileri people.data structından binary dosyaya yazar */

    FILE *file;
    int i;
    file = fopen(filename,"wb");

    if(file != NULL)                            /* Dosya başarıyla açılırsa yazma işlemini yapar */  
        for(i=0;i<people.size;i++)  
            fwrite(&people.data[i],sizeof(Person),1,file);
    fclose(file);

}


void readPeople(People *people, char* filename) { /* Binary dosyadan person structını okur ve people.data  dizisine kaydeder */

    FILE *file;
    int i=0;

    file = fopen(filename,"rb");
    people->size = 0;

    if(file != NULL)                            /* Dosya başarıyla açılırsa okuma işlemini yapar */
    {
        while(fread(&people -> data[i],sizeof(Person),1,file) != 0)
            people->size += 1;      /* Okunan kişi sayısı bir arttırılır */
            i++;
    }
    fclose(file);
}


/*
Harcama tutarı bilinmeyen kişiler için tahmini bir harcama tutaru hesaplanır.
Harcama tutarları bilinmeyenler -1 değeri ile gösterilr 
*/
void imputation(People *people) {

    int unknownNum = 0,knownNum = 0,i,key,found = 0;
    double totalExp;
    Record *rec,*temp;


    for(i=0;i<people->size;i++){                                 /* Harcama tutarları bilinen kişilerin  toplam numara sayısını hesaplar */
        rec = people->data[i].numbers;
        while(rec){   
            if(people->data[i].expenditure != -1)       /* Harcama tutarı -1 olanların haricindekilerin telefon numarası sayısı toplanır */
                knownNum += 1;              
            rec = rec->next;
        }
    }

    
    i=0;
    while(i < people->size){
        temp = people->data[i].numbers;

        if(people->data[i].expenditure == -1){   /* Harcama tutarları bilinmeyen kişilerin indisi "key" de tutulur */
         
            key = i;
            unknownNum = 0;
            while(temp != NULL){   
                unknownNum++;                    /* Harcama tutarları bilinmeyen kişilerin sahip olduğu toplam telefon numarası sayısı hesaplanır */
                temp = temp->next;
            }
            
            i++;
            found = 1;
        }else{
            totalExp += people->data[i].expenditure;    /* Harcama tutarları bilinen kişilerin harcamaları toplanır */
            i++;
        }
        if(found == 1) 
            people->data[key].expenditure = ( totalExp / knownNum )* unknownNum ;
			/*Ortalama bir ödeme miktarı hesaplanır ve harcama tutarı bilinmeyen kişinin 
          numara sayısı ile çarpılırak tahmini harcama tutarı elde edilr */   
    }
}


void read(char* filename, People *people) {/* Verilen text dosyasından okuma işlemini yapar  */

    int i = 0;
    char *tempName;
    char *tempSurname;
    char *line,*cpt;

    Record *rec;        
    FILE *file;
    file = fopen(filename,"rt");
    
    /* Stringlere yer ayırma işlemi */
    line = (char *)malloc(MAXRECORD);       
    tempName = (char *)malloc(NAMELEN);
    tempSurname = (char *)malloc(NAMELEN);


    if(file != NULL)         /* Dosya başarıyla açılırsa okuma işlemini yapar */
    {

        while(fgets(line,MAXRECORD,file) != NULL)     /* Dosyanın sonuna gelene kadar her satırı stringe alır */
        {

            if(line[strlen(line) - 1] == '\n')      /* Dosyadan alınan her satırın sonundaki new line işaretini kaldırır */
                line[strlen(line) - 1] = '\0';
            
             /* Satırdan sırasıyla id,isim,soyad ve harcama tutarını okur */
            sscanf(line,"%d %s %s %lf",&people->data[people->size].id,tempName,tempSurname,&people->data[people->size].expenditure);
            cpt = strtok(line," "); /* Satırdaki elemanları ayırır */

            while(cpt != NULL)  /*Stringe alınan satırın sonuna gelene kadar devam eder */
            {
                if(i>3)     /* Üçünce indise kadar id,isim ve soyisim bilgileri bulunur sonrasında ise numaralar bulunur */
                {
                    if (i == 4)       /*Kişinin ilk numarası için linked listte bir head belirlenir,yer açılır ve numara head e yazılır */
                    {
                        rec = (Record *)malloc(sizeof(Record));     
                        strcpy(rec->number, cpt);
                        people->data[people->size].numbers = rec;
                        rec->id = people->data[people->size].id;
                    }
                    else /* Kişinin varsa diğer numaraları için head e bağlı olarak başka düğümlere yer açılır ve numaralar eklenir */
                    {
                        rec->next = (Record *)malloc(sizeof(Record));
                        strcpy(rec->next->number, cpt);
                        rec->next->id = people->data[people->size].id;
                        rec->next->next = NULL;
                        rec = rec->next;
                    }
                }
                
                i++;
                cpt=strtok(NULL," ");
            }
            i = 0;


            strcat(tempName," ");                               /* Geçici diziye alınan kişinin isminin sonuna boşluk ekler */
            strcat(tempName,tempSurname);                       /* Soyadı ismin arkasına, arasında boşluk bırakılmış şekilde eklenir */
            strcpy(people->data[people->size].name,tempName);   /* Geçici isim dizisinin son halini "people data" dizisine kopyalar */


            people -> size += 1;                                /* Kaydı tutulan kişi sayısını bir artırır */
        }
    }

    free(tempName);                             /* Hafızadan ayırılan yerler serbest bırakılır */
    free(tempSurname);
    free(line);

    fclose(file);
}


void print(People people) {
    int i,found = 0;
    Record *rec;
    /* header */
    printf("%-5s %-30s %-20s %-20s\n", "ID","NAME","EXPENDITURE","NUMBER(s)");
    /* line */
    for (i = 0; i < 78; ++i)
        printf("-");
    printf("\n");

    for (i = 0; i < people.size; ++i) {
        found = 0;
        printf("%-5d %-30s %-20.4f", people.data[i].id, people.data[i].name, people.data[i].expenditure);
        rec = people.data[i].numbers;
        while(rec) {
            if(found)
                printf("%57s", "");
            else
                found = 1;
            printf("%-20s\n", rec->number);
            rec = rec->next;
        }
        printf("\n");
    }
}

int isPeopleEq(People ppl1, People ppl2) {
    Record *rec1,*rec2;
    int i,found = 0;
    int p1size = 0, p2size = 0;
    if(ppl1.size != ppl2.size)
        return 0;
    for (i = 0; i < ppl1.size; ++i)
        if(strcmp(ppl1.data[i].name,ppl2.data[i].name))
            return 0;
        if(ppl1.data[i].id != ppl2.data[i].id)
            return 0;

        p1size = p2size = 0;
        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            ++p1size;
            rec1 = rec1->next;
        }

        rec2 = ppl2.data[i].numbers;
        while(rec2) {
            ++p2size;
            rec2 = rec2->next;
        }

        if(p1size != p2size) {
            return 0;
        }

        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            rec2 = ppl2.data[i].numbers;
            found = 0;
            while(!found && rec2) {
                if(strcmp(rec1->number,rec2->number) == 0) {
                    found = 1;
                    break;
                }
                rec2 = rec2->next;
            }
            if(!found) {
                return 0;
            }
            rec1 = rec1->next;
        }
    return 1;
}

int main(int argc, char** argv) {
    People people1,people2;
    people1.size = 0;
    read(argv[1],&people1);
    print(people1);
    writePeople(people1,"people.bin");
    readPeople(&people2,"people.bin");
    print(people2);
    printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
    printf("Making imputation\n");
    imputation(&people1);
    print(people1);
    return 0;
}

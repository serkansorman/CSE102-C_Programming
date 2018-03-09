#include <stdio.h>
#include <string.h>

#define NAMELEN 50
#define MAXRECORD 500

typedef struct person_s {
	int id;
	char name[NAMELEN];
} Person;

typedef struct record_s {
	int id;
	char number[NAMELEN];
} Record;

typedef struct Records_s {
	Record data[MAXRECORD];
	int size;
} Records;

typedef struct people_s {
	Person data[MAXRECORD];
	int size;
} People;

void writeRecords(Records records, char* filename) { /* Kayıtları binary dosyaya yazar */

	FILE *file;
	file = fopen(filename,"wb");
	if(file != NULL)                                /* Dosya başarıyla açılırsa yazma işlemini yapar */
		fwrite(&records.data,sizeof(Records),1,file);
	fclose(file);
}


void readRecords(Records *records, char* filename) {/* Kayıtları binary dosyadan okur */

	FILE *file;
	file = fopen(filename ,"rb");
	if(file != NULL)                                /* Dosya başarıyla açılırsa okuma işlemini yapar */
		fread(&records->data,sizeof(Records),1,file);
    fclose(file);
}


void writePeople(People people, char* filename) { /* Kişileri binary dosyaya yazar */

	FILE *file;
	file = fopen(filename,"wb");
	if(file != NULL)                            /* Dosya başarıyla açılırsa yazma işlemini yapar */
		fwrite(&people.data,sizeof(People),1,file);
	fclose(file);
}



void readPeople(People *people, char* filename) { /* Kişileri binary dosyadan okur */

	FILE *file;
	file = fopen(filename,"rb");
	if(file != NULL)                            /* Dosya başarıyla açılırsa okuma işlemini yapar */
		fread(&people -> data,sizeof(People),1,file);
    fclose(file);

}


void read(char* filename, People *people, Records *records){ /* Verilen text dosyasından okuma işlemini yapar  */

	int i,n=0;  /* "n" Kişinin sahip olduğu telefon numara sayısını tutar */

	char tempName[NAMELEN][NAMELEN];
	char tempSurname[NAMELEN][NAMELEN];
    
	FILE *file;
	file = fopen(filename,"rt");

	if(file != NULL)         /* Dosya başarıyla açılırsa okuma işlemini yapar */
	{
		while(! feof(file))     /* Dosyanın sonuna gelene kadar okuma işlemine devam eder */
		{
		    /* Satırdan sırasıyla id,isim,soyad ve telefon numarası sayısını okur */
			fscanf(file,"%d %s %s %d",&people->data[people->size].id,tempName[people->size],tempSurname[people->size],&n);

            /* Kişinin sahip olduğu telefon numarası sayısına göre ,ardından gelen telefon numaralarını okur */
			for(i=0;i<n;i++)
			{
				fscanf(file,"%s",records->data[records->size].number);
				records->data[records->size].id = people->data[people->size].id;    /* Telefon numaralarını aynı kişi için  aynı id lere yazar */
				records -> size += 1;                                               /* Tutulan kayıt sayısını bir artırır */
			}
			
			strcat(tempName[people->size]," ");                             /* Geçici diziye alınan kişinin isminin sonuna boşluk ekler */
			strcat(tempName[people->size],tempSurname[people->size]);       /* Soyadı ismin arkasına, arasında boşluk bırakılmış şekilde ekler */
			strcpy(people->data[people->size].name,tempName[people->size]); /* Geçici dizinin son halini "people data" dizisine kopyalar */

			people -> size += 1;                                    /* Kaydı tutulan kişi sayısını bir artırır */

		}
	}
    fclose(file);
}
/* ========== IMPLEMENT THE FUNCTIONS ABOVE ========== */

void print(People people, Records records) {
	int i,j,found = 0;
	/* header */
	printf("%-5s %-30s %-20s\n", "ID","NAME","NUMBER(s)");
	/* line */
	for (i = 0; i < 57; ++i)
		printf("-");
	printf("\n");

	for (i = 0; i < people.size; ++i) {
		found = 0;
		printf("%-5d %-30s", people.data[i].id, people.data[i].name);
		for (j = 0; j < records.size; ++j) {
			if(records.data[j].id == people.data[i].id){
				if(found)
					printf("%36s", "");
				printf("%-20s\n", records.data[j].number);
				found = 1;
			}
		}
		printf("\n");
	}
}

int isPeopleEq(People ppl1, People ppl2) {
	int i;
	if(ppl1.size != ppl2.size)
		return 0;
	for (i = 0; i < ppl1.size; ++i)
		if(strcmp(ppl1.data[i].name,ppl2.data[i].name) ||
			ppl1.data[i].id != ppl2.data[i].id)
			return 0;
	return 1;
}

int isRecordsEq(Records rec1, Records rec2) {
	int i;
	if(rec1.size != rec2.size)
		return 0;
	for (i = 0; i < rec1.size; ++i)
		if(strcmp(rec1.data[i].number,rec2.data[i].number) ||
			rec1.data[i].id != rec2.data[i].id)
			return 0;
	return 1;
}

int main(int argc, char** argv) {
	People people1,people2;
	Records records1,records2;
	people1.size = 0;
	records1.size = 0;
	read(argv[1],&people1, &records1);
	print(people1, records1);
	writePeople(people1,"people.bin");
	writeRecords(records1,"records.bin");
	readRecords(&records2,"records.bin");
	readPeople(&people2,"people.bin");
	print(people2, records2);
	printf("%s\n", isRecordsEq(records1,records2) ? "RECORDS ARE SAME" : "RECORDS ARE DIFFERENT!");
	printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
	return 0;
}

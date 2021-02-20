/* 
@file
BLM2512 2019-2020 BAHAR ODEV-1
Bu programda Double Linked List yapýsý kullanýlarak bir Cache Buffer tasarýmý yapýlmýþtýr.

@author
Ýsim: Ahmet Said SAÐLAM
Öðrenci No: 17011501
Tarih: 03.03.2020
E-Mail: l1117501@std.yildiz.edu.tr
Compiler: TDM-GCC 4.9.2 64 bit-Release
IDE: DEV-C++ (version 5.11)
Ýþletim Sistemi: Windows 10 Pro 64 bit
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#define LENGTH 20				//maksimum string uzunluðu

//double linkli liste yapý tanýmý
typedef struct node {
	struct node* next;
	struct node* prev;
	int count;
	char word[LENGTH];
} node;

// double linkli liste basa eleman ekleme fonksiyonu
node* basaEkle(node* head, char val[LENGTH]) {
	node* newnode;
	newnode = (node*) malloc(sizeof(node));
	strcpy(newnode->word, val);
	newnode->count = 1;
	newnode->next = head;
	newnode->prev = NULL;
	if(head != NULL){
		head->prev = newnode;
	}
	head = newnode;
	return head;
}

//linkli listenin son düðümünü silen fonksiyon
void deleteTail (node* head) {
	node* current = head;
	node* temp;
	while (current->next != NULL){
		current = current->next;
	}
	temp = current;
	current = current->prev;
	current->next = NULL;
	free(temp);
}

//linkli listedeki tüm nodelarý silen fonksiyon
void deleteAll(node*head) {
	node* current = head;
	node* temp;
	while(current->next != NULL){
		temp = current;
		current = current->next;
		current->prev = NULL;
		temp->next = NULL;
		free(temp);
	}
	free(current);
}

//linkli listeyi sýrayla yazdýran fonksiyon
void printList (node* head) {
	node* current = head;
	printf("\n");
	while (current->next != NULL) {
		printf("%s,%d  <->  ", current->word, current->count);
		current = current->next;
	}
	printf("%s,%d",current->word, current->count);
}

//kullanýcadan alýnan string halihazýrda mevcut linkli listede bulunuyor mu kontrol eden fonksiyon
node* arama(node* head, char val[]){
    int bulgu = 1;
    node* temp = head;
    while (bulgu != 0 && temp->next != NULL){
        bulgu = strcmp(temp->word, val);
        temp = temp->next;
    }
    if (bulgu == 0){
        temp = temp->prev;
        return temp; // bulunmus demektir adresi disariya dondurulur
    }
    else{
        if (strcmp(temp->word, val) == 0){
            return temp; // son eleman aranan ise onun adresi donulur disari
    	}
        return NULL; // eger liste bitmis ve bulunamamissa NULL donulur
    }
}

//eþik deðerini geçen ara node'u head node yapan fonksiyon
node* swap(node* head, node* temp){
	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	head->prev = temp;
	temp->next = head;
	temp->prev = NULL;
	head = temp;
	return head;
}

//eþik deðerini geçen son node'u head node yapan fonksiyon
node* swapTail(node* head, node* temp) {
	temp->prev->next = NULL;
	head->prev = temp;
	temp->next = head;
	temp->prev = NULL;
	head = temp;
	return head;
}

//kullanýcadan alýnan string daha önceden mevcut ise bu fonksiyon çaðýrýlýr.
//fonksiyon count deðerlerini günceller ve gerekirse ilgili node'u head node yapmaya yarayan fonksiyonu çaðýrýr.
node* controlFunc(node* head, node* temp, int T) {
	if(temp->prev == NULL) {
		temp->count++;
		return head;
	}
	else if(temp->next != NULL) {
		temp->count++;
		if(temp->count > T){
			head = swap(head, temp);
		}
		return head;
	}
	else if(temp->next == NULL) {
		temp->count++;
		if(temp->count > T) {
			head = swapTail(head, temp);
		}
		return head;
	}
}


int main() {
	system("COLOR B");
	FILE *fp;					//file pointer
	int clearAll = 0;			//program sonlanýrken cache'i temizlemek veya olduðu gibi býrakmak durumunu kontrol eden deðiþken
	int T, L;					//esik deðeri ve buffer kapasitesi
	int tur = 0;				//verinin dosyadan mý yoksa kullanýcýdan elle mi alýnacýðýný kontrol eden deðiþken
	int Lsayaci = 1;			//buffer kapasitesini kontrol eden deðiþken
	node* head = NULL;			//ilk adýmda head NULL olarak belirlenir
	node* temp;					//geçici node
	char fileName[50];			//kullanýcýnýn gireceði dosya ismini tutan karakter dizisi
	char temiz[LENGTH];			//ekraný temizlemeye yarayan karakter dizisi
	char clean[LENGTH] = "cls";	//ekraný temizlemeye yarayan kontrolü saðlayan karakter dizisi
	char stop[LENGTH] = "esc";  //programý sonlandýrmaya yarayan kontrolü saðlayan karakter dizisi
	char string[LENGTH];		//kullanýcýnýn girdiði stringleri tutan karakter dizisi
	printf("Cache Buffer'in esik degerini (T) giriniz.\n");
	scanf("%d",&T);
	printf("Cache Buffer'in kapasitesini (L) giriniz.\n");
	scanf("%d",&L);
	printf("Stringi elle girmek icin 1'e, dosyadan okumak icin 2'ye basiniz.\n");
	scanf("%d",&tur);
	if(tur == 1) {
		printf("String giriniz.\n");
		scanf("%s",string);
		head = basaEkle(head, string);
		printList(head);
		printf("\nString giriniz.\nCikmak icin esc yazip onaylayiniz!\nCache'i temizlemek icin cls yazip onaylayiniz!\n");
		scanf("%s",string);
		while (strcmp(string, stop) != 0) {
			strcpy(temiz, string);
			if(strcmp(temiz, clean) != 0) {
				temp = arama(head, string);
				if(temp == NULL){
					head = basaEkle(head, string);
					Lsayaci++;
					if(Lsayaci > L){
						deleteTail(head);
					}
				}
				else{
					head = controlFunc(head, temp, T);
				}
				printList(head);
			}
			else {
				printf("Buffer Temizleniyor...\n");
				deleteAll(head);
				head = NULL;
				Lsayaci = 1;
				printf("\nString giriniz.\n");
				scanf("%s",string);
				head = basaEkle(head, string);
				printList(head);
			}
			printf("\n\nString Giriniz.\nCikmak icin esc yazip onaylayiniz!\nCache'i temizlemek icin cls yazip onaylayiniz!\n");
			scanf("%s",string);
		}
	}
	else{
		printf("Dosya ismini uzantisiyla birlikte yaziniz.\n");
		scanf("%s",fileName);
		if((fp = fopen(fileName,"r")) == NULL) {
			printf("Dosya acilamadi!\n");
			return 0;
		}
		else {
			fscanf(fp,"%s",string);
			head = basaEkle(head, string);
			printList(head);
			while(!feof(fp)) {
				fscanf(fp,"%s",string);
				temp = arama(head, string);
				if(temp == NULL) {
					head = basaEkle(head, string);
					Lsayaci++;
					if(Lsayaci > L) {
						deleteTail(head);
					}
				}
				else {
					head = controlFunc(head, temp, T);
				}
				printList(head);
			}
			fclose(fp);
		}
	}
	printf("\n\nCache'i tamamen temizlemek icin 1'e, oldugu gibi birakmak icin 0'a basiniz.\n");
	scanf("%d",&clearAll);
	if(clearAll == 1){
		deleteAll(head);
		printf("Cache Buffer Temizlendi!");
	}
	else {
		printf("\nCache temizlenmeden cikiliyor.\nCache:\n");
		printList(head);
	}
	return 0;
}




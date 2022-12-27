#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//*******************************************

struct node {

	int tiket;
	char jk;
	
    struct node *next;
};

typedef struct node node;

struct stack {
	
	int count;
	
    struct node *top;
};
typedef struct stack stack;

//*******************************************


void masukan(node **pHead, int *counter);
void cek_antrian(node *pHead, int *counter);
void penumpang(stack *pHead_k, node **pHead_a, int *counter);
void cek_kereta(stack *pHead);
void keluarkan(stack *pHead);
stack createkereta(void);


//********************************************


int main()
{

  char selectMenu;
  
  node *antrian;
  antrian = NULL;
  
  stack kereta;
  kereta = createkereta();
  
  int counter=0;

  do{
    

    system("cls");
    
	printf("-- Selamat Datang di Sistem Operasional Kereta Hantu -- \n\n"); 
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Berikut peraturan yang harus dipenuhi agar Wahana Kereta Hantu dapat beroperasi:\n");
	printf("1. Jumlah maksimum penumpang kereta adalah 12 orang\n");
	printf("2. Dari antrian yang ada akan didahulukan pengantre wanita dari 12 pengantre terdepan\n");
	printf("3. Pengantre yang masuk akan mengisi bangku kereta paling belakang dahulu\n");
	printf("4. Kereta dapat berjalan meski tidak mencapai jumlah maksimum\n");
	printf("5. Agar terkondisi, ketika kereta sudah selesai beroperasional, penumpang paling depan adalah penumpang yang turun dahulu\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("-- Menu Operasional -- \n\n"); 
	printf("1. Masukan Antrian\n");
	printf("2. Cek Antrian\n");
	printf("3. Masukan Penumpang Kereta\n");
	printf("4. Cek Kereta\n");
	printf("5. Keluarkan Penumpang\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("Tekan 0 untuk keluar : ");
	fflush(stdin);
	scanf("%c", &selectMenu);
	if (selectMenu == '1')
		
		masukan (&antrian, &counter) ;
	else if (selectMenu == '2'){
		cek_antrian(antrian, &counter);
		getch();
	}
	else if (selectMenu == '3')
		penumpang(&kereta, &antrian, &counter);
	else if (selectMenu == '4'){
		
		cek_kereta(&kereta);
		getch();
	}
	else if (selectMenu == '5')
		keluarkan(&kereta);
	} while (selectMenu != '0');
  
}

//========================================================
stack createkereta(void){
	stack kereta;
	kereta.count=0;
	kereta.top = NULL;
	return(kereta);
}
//========================================================
void masukan(node **pHead, int *counter){
  int no_tiket;
  char jenis_kelamin;
  node *pNew, *pCur;

  system("cls");
  fflush(stdin); 
  
  pNew = (node *)malloc(sizeof(node));
  
  printf("Masukan Nomor Tiket Antrian : ");
  fflush(stdin);
  scanf("%d", &no_tiket);
  
  printf("Jenis Kelamin (P/L) : ");
  fflush(stdin);
  scanf("%c", &jenis_kelamin);
  
  	pNew->tiket = no_tiket;
  	pNew->jk = jenis_kelamin;
	
if (*counter < 12){
	if (*pHead == NULL){ 
	pNew->next = *pHead;
  	*pHead = pNew;
  	*counter=*counter +1;
  }
  
  else{
  	pCur = *pHead;
  	while (pCur -> next != NULL) {
    pCur = pCur -> next;
  	}
  	pNew->next = NULL;
  	pCur->next = pNew;
  	*counter=*counter +1;
  }
}
else{
	printf("Antrian Penuh!");
	getch();
}
  
}
//========================================================

void cek_antrian(node *pHead, int *counter){

	node *pWalker;

    system("cls");
	pWalker = pHead;
	printf("Jumlah antrian = %d\n", *counter);
	printf("-Depan-\n");
	while (pWalker != NULL){
   	printf("%d - %c\n", pWalker -> tiket, pWalker -> jk);
   	pWalker = pWalker -> next;
	}
	
   printf("-------");
}
//========================================================
void penumpang(stack *pHead_k, node **pHead_a, int *counter){
  node *pPre, *pCur, *pNew;
  system("cls");
  fflush(stdin);
  
  pNew = (node *)malloc(sizeof(node));

  if (pHead_k ->count <12 && *counter != 0){ 
  		
		pPre = NULL;
		pCur = *pHead_a;
		
		while (pCur->next != NULL && pCur->jk != 'P'){
	   	pPre = pCur;
	   	pCur = pCur->next;
		}
		if (pCur->jk != 'P'){
			pCur = *pHead_a;
		}
		
		pNew->tiket = pCur->tiket;
		pNew->jk = pCur -> jk;
		pNew->next = pHead_k ->top; 
		pHead_k ->top = pNew; 
		pHead_k->count = pHead_k->count + 1;
		
		printf("Penumpang no tiket %d masuk", pCur->tiket);
		
		if (pCur == *pHead_a){
			*pHead_a = pCur->next;
      	free(pCur);
      	*counter = *counter - 1;
		}
		else {
			pPre->next = pCur->next;
    	 free(pCur);
    	 *counter = *counter - 1;
		}
		getch();
  }
  else if (*counter == 0){
  	printf("Antrian kosong");
  	getch();
  }
  else{
      printf("Kereta Penuh");
      getch();
  }
}

//========================================================

void cek_kereta(stack *pHead){
	node *pWalker;
	int counters;
	
	system("cls");
    
	pWalker = pHead->top;
	counters = pHead->count;
	printf ("Jumlah Penumpang = %d\n", counters);
	printf("<");
	while (counters != 12){
   	printf("| x |");
   	counters = counters +1;
	}
	
	while (pWalker != NULL){
   	printf("|%d|", pWalker -> tiket);
   	pWalker = pWalker -> next;
	}
	printf("\n ^Depan^\n");
   
}

//========================================================

void keluarkan (stack *pHead){
	node *pCur, *notif;
	
	system("cls");
	pCur= pHead->top;
	notif->tiket = pCur->tiket;
	pHead->top = pHead->top->next;
	
	free(pCur);
	pHead->count = pHead->count - 1;
	
	cek_kereta(pHead);
	printf("Penumpang dengan no tiket %d keluar\n", notif->tiket);
	getch();
}

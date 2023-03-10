#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 256
int key,c=0;
struct node
{
    char data[MAX];
    struct node *next;
};

struct node_occur//Tekrarlayanlari icin ayri linked list (array yasak oldugu icin internetten boyle bir cozum buldum)geeksforgeeks.net
{
    char data[MAX];
    int times;
    struct node_occur *next;
} node_occur;

struct node* head=NULL; // listenin baslangic node u
//Dosya Fonksiyonlari
FILE* fp;
void OpenFileRead();
void AppendListFromFile();
void CloseFile();
void RewindFile();


//Listeyi Siralamak
void bubbleSort(struct node_occur *start)
{
    int swapped, i;
    struct node_occur *ptr1;
    struct node_occur *lptr = NULL;


    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->times < ptr1->next->times)
            {
                swap2(ptr1,ptr1->next);
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

//data swap
void swap2(struct node_occur *a, struct node_occur *b)
{
    char temp[MAX];
    strcpy(temp , a->data) ;
    strcpy(a->data , b->data);
    strcpy(b->data , temp);
}
//counter swap
void swap(struct node_occur *a, struct node_occur *b)
{

    int temp = a->times;
    a->times = b->times;
    b->times = temp;
}

//KAC TANE NODE VAR(Node Sayma)
int count()
{

    struct node *n;
    int c=0;
    n=head;
    while(n!=NULL)
    {
        n=n->next;
        c++;
    }
    return c;
}

void occur(struct node *head, struct node_occur **result)//Tekrarlayan Sozcukleri Bulmak
{

    struct node_occur *temp, *prev;


    while (head != NULL)
    {
        temp = *result;
        while (temp != NULL && strcmp(temp->data,head->data)!=0)
        {
            //temp != NULL && temp->data != head->data
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            temp = (struct node_occur *)malloc(sizeof(struct node_occur));

            strcpy(temp->data,head->data);
            //temp->data = p->data;
            temp->times = 1;
            temp->next = NULL;
            if (*result != NULL)
            {
                prev->next = temp;
            }
            else
            {
                *result = temp;
            }
        }
        else
        {
            temp->times += 1;
        }
        head= head->next;
    }
}

void disp_occur(struct node_occur *p)
{
    int i=0;
    bubbleSort(p);
    printf("***************************\n  Kelime\tTekrar Sayisi\n***************************\n");
    while (p != NULL)
    {
        i++;
            printf("%d.%s~~%d\n",i, p->data, p->times);
            p = p->next;
    }
}


//SONA ATAMA
void append(char num[])
{
    struct node *temp,*right;
    // yeni temp node
    temp= (struct node *)malloc(sizeof(struct node)); //temp node olusturma
    strcpy(temp->data,num);  //value atama
    temp->next=NULL; // tempi liste sonu olarak atama

    right= head;
    if (right==NULL)
    {

        head=temp;

    }
    else
    {

        while(right->next != NULL)
            right=right->next;

        right->next =temp;
    }

}

//BASLANGICA ATAMA
void add( char num[])
{
    struct node *temp;

    temp=(struct node *)malloc(sizeof(struct node));
    strcpy(temp->data,num);
    temp->next=NULL;

    if (head== NULL)
    {

        head=temp;
        head->next=NULL;
    }
    else
    {

        temp->next=head;
        head=temp;
    }

}

//LISTEDEN GIRILEN STRINGE GORE NODE SILME
int delete(char num[])
{
    struct node *temp, *prev;
    temp=head;

    while(temp!=NULL)
    {

        if(strcmp(temp->data,num)==0)
        {

            if(temp==head)
            {

                head=temp->next;
                free(temp);
                return 1;
            }
            else
            {

                prev->next=temp->next;
                free(temp);
                return 1;
            }
        }
        else
        {

            prev=temp;
            temp= temp->next;
        }
    }
    return 0;
}

//LISTEYI PRINTLEMEK(Bastan Sona)
void display(struct node *p)
{
    while (p != NULL)
    {
        printf("%s ", p->data);
        p = p->next;
    }
    printf("\n");
}



//  ======================MAIN FONKSIYONU========================
int  main()
{
    int i;
    char num[MAX];

    struct node_occur *p = NULL;
    head=NULL;
    puts("\n**************Liste Islemleri*************");
                puts("1.Sona ekle          2.Basa Ekle               3.Liste Goruntule");
                puts("4.Liste Boyutu       5.Sil                     6.Cikis");
                puts("7.Dosya Oku          8.Dosyadan Listeye Aktar  9.Dosyayi Geri Sar");
                puts("10.Tekrarlayan Kelimeler  11.Dosyayi Kapat");
    while(1)
    {

        puts("\nYapmak istediginiz islemi secin : (0: Menu)");
        if(scanf("%d",&i)<=0)
        {
            printf("Sadece Integer girebilirsiniz\n");
            exit(0);
        }
        else
        {
            switch(i)
            {
            case 1:
                printf("Listenin sonuna eklenecek kelimeyi girin : ");
                scanf("%s",&num);
                append(num);
                break;

            case 2:
                printf("Listenin basina eklenecek kelimeyi girin : ");
                scanf("%s",&num);
                add(num);
                break;
            case 3:
                if(head==NULL)
                {
                    printf("Liste Bos\n");
                }
                else
                {
                    printf("Listede ki elemanlar : \n");
                }
                display(head);
                break;
            case 4:
                printf("Listenin boyutu %d\n",count());
                break;
            case 5:
                if(head==NULL)
                    printf("Liste bos\n");
                else
                {
                    printf("Silinecek nodeu girin : ");
                    scanf("%s",&num);
                    if(delete(num))
                        printf("%s basariyla silindi\n",num);
                    else
                        printf("%s listede bulunamadi\n",num);
                }
                break;
            case 6:
                return 0;
                break;

            case 7:
                OpenFileRead();
                break;

            case 8:
                AppendListFromFile();
                break;

            case 9:
                RewindFile();
                break;


            case 10:
                printf("Listede Tekrarlanan Kelimeler\n");

                occur(head, &p);
                disp_occur(p);
                break;

            case 11:
                CloseFile();
                break;

            default:
                puts("\n**************Liste Islemleri*************");
                puts("1.Sona ekle          2.Basa Ekle               3.Liste Goruntule");
                puts("4.Liste Boyutu       5.Sil                     6.Cikis");
                puts("7.Dosya Oku          8.Dosyadan Listeye Aktar  9.Dosyayi Geri Sar");
                puts("10.Tekrarlayan Kelimeler  11.Dosyayi Kapat");

            }
        }
    }
    return 0;
}
//++++++++++++++++++++++++++++++MAIN FONKSYION BITISI+++++++++++++++++++++++++++++

void OpenFileRead()
{
    char filename[20];
    //fflush(stdin);   //keyboard inputu flushlamak gerekirse(cok fazla input varsa)
    puts("Okumak Istediginiz Dosyanin Ismi: \n");
    scanf("%s",filename);

    //dosyayi okumak icin ac FP global variable
    if ( (fp = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Dosya Acilamadi\n");
    }
    else
    {
        printf("%s Dosya Acildi\n",filename);
    }

}
void CloseFile()
{
    int result;
    result = fclose(fp);
    if(result != 0)
        printf ("Dosya Kapanamadi\n");
    else
        printf("Dosya Basariyla Kapatildi\n");
    return;
}

void RewindFile()
{
    rewind(fp);
    printf("Dosya Basa Sarildi\n");
}

void AppendListFromFile()
{
    char line[MAX];
    char* token;
    char delim[]=" \t\r\n\v\f";
    char num[MAX]= {'\0'};

    while(fgets(line, sizeof line, fp) != NULL)
    {
        //ilk tokeni bul
        token = strtok(line, delim);

        //diger tokenler arasinda gez
        while( token != NULL )
        {
            sscanf(token, "%s", &num);      //string bul

            append(num);

            token = strtok(NULL, delim);
            // printf(" Token =%p \n", token);
        }
    }
    printf("Dosyanin tum elemanlari : \n");
    display(head);
    return;
}



#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stddef.h>


typedef struct Araclar
{

int numara;
int urunCinsi;
char plaka[10];
char sofor[20];
char geldigiYer[20];
int ilkTartim;
int sonTartim;

time_t girisTarihSaat;
time_t cikisTarihSaat;
int durum;
int kilo;


}arac ;


void aracKantarGirisi()

{

    system("cls");
    printf("Urun Giris Kantar Islemi...\n\n");
    arac a1;
    int numara;
    numara = 0;  
    FILE *numPtr =fopen("aracNumaralari.dat","a+b");
    while(fread(&numara,sizeof(int),1,numPtr)!=NULL )
    {
    }

    numara++;
    fwrite(&numara,sizeof(int),1,numPtr);
    fclose(numPtr);

    a1.numara=numara;
    printf("1-PASTIRMA \n");
    printf("2-SUT \n");
    printf("3-KONSERVE \n");
    printf("Urun Cinsi Seciniz [1,2,3]:  ");
    scanf("%d",&a1.urunCinsi);
    printf("Plaka Giriniz: ");
    scanf("%s",a1.plaka);
    printf("Sofor adSoyad Giriniz: ");
    scanf("%s",a1.sofor);
    printf("Geldigi Yer Giriniz: ");
    scanf("%s",a1.geldigiYer);
    printf("Ilk Tartim Giriniz: ");
    scanf("%d",&a1.ilkTartim);
    a1.sonTartim=0;
    a1.girisTarihSaat=time(0);
    a1.cikisTarihSaat=time(0);
    a1.durum=0;
    a1.kilo=0;

   FILE *ptr =fopen("urunGirisleri.dat","a+b");
   fwrite(&a1,sizeof(arac),1,ptr);
   fclose(ptr);
   printf("Arac kantar girisi basarili...\n\n");  

}


void aracKantarCikisi()

{

    system("cls");
    printf("Urun Girisi Icin Kantar Cıkıs Islemi...\n\n");
    arac a1;
    int numara;
    int sonuc=0;
    int sayac=0;
   
    FILE *ptr =fopen("urunGirisleri.dat","r");
    while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 0)
        sonuc=1;
        
    }

    if (sonuc ==0 )
    {
        printf("Bosaltimda Bekleyen Arac Yoktur...\n\n");
        fclose(ptr);   
    }
    else
    {
         rewind(ptr); // ptr basa alma islemi yapıyoruz !
         printf("%-20s%-20s%-20s","PLAKA","NUMARA","Ilk Tartim");
         while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 0)
        printf("%-20d%-20d%-20d",a1.plaka,a1.numara,a1.ilkTartim);
        
    }
   

    printf("Cikis Yapacak Aracin Numarasini Giriniz: ");
    scanf("%d",&numara);

    sonuc=0;
    rewind(ptr);
   
     while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 0 && a1.numara == numara)
        {

        sonuc=1;
        break;
       
        }
          sayac++;
        
    } 

     if(sonuc == 0)
     printf("%d numarali arac kaydi bulunmamaktadir ! \n",numara);
     else
     {
        printf("Son Tartim Giriniz: ");
        scanf("%d",&a1.sonTartim);
        a1.cikisTarihSaat=time(0);
        a1.durum=0;
        a1.kilo=a1.ilkTartim-a1.sonTartim;
        a1.durum=1;     // 1 olma sebebi artık arac cikis yapti demektir.

        fseek(ptr,(sayac)*sizeof(arac),SEEK_SET); // ilgili kordinata gidip kayit yapmak icin fseek kullandık gidiyoruz.
        fwrite (&a1,sizeof(arac),1,ptr);
        printf("Arac cikis islemi basarili...\n\n");

     }
      
    fclose(ptr);

    }
}



void bosaltimdaBekleyenAraclar()
{

    system("cls");
    printf("Bosaltimda Bekleyene Araclar...\n\n");
    arac a1;
    int numara;
    int sonuc=0;
    int sayac=0;
   
    FILE *ptr =fopen("urunGirisleri.dat","r");
    while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 0)
        sonuc=1;
        
    }

    if (sonuc ==0 )
    {
        printf("Bosaltimda Bekleyen Arac Yoktur...\n\n");
        fclose(ptr);   
    }
    else
    {
         rewind(ptr); // ptr basa alma islemi yapıyoruz !
         printf("%-20s%-20s%-20s","PLAKA","NUMARA","Ilk Tartim");
         while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 0)
        printf("%-20d%-20d%-20d",a1.plaka,a1.numara,a1.ilkTartim);
        
    }
   
    fclose(ptr);

    }

}

void urunGirisleriniListele()
{


    system("cls");
    printf("Urun Giris Listeleri...\n\n");
    arac a1;
    int numara;
    int sonuc=0;
    int sayac=0;
    int sutToplam=0;
    int pastirmaToplam=0;
    int konserveToplam=0;
   
    FILE *ptr =fopen("urunGirisleri.dat","r");
    while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 1)
        sonuc=1;
        
    }

    if (sonuc ==0 )
    {
        printf("Urun girisi olmamistir...\n\n");
        fclose(ptr);   
    }
    else
    {
         system("cls");
         rewind(ptr); // ptr basa alma islemi yapıyoruz !
         printf("%-10s%-20s%-20s%-20s%-20s \n","PLAKA","NUMARA","Ilk Tartim","Son Tartim","Kilo");
         while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 1) // arac boasaltimda ciktigi icin bir oluyor !
        printf("%-20d%-20d%-20d",a1.plaka,a1.numara,a1.ilkTartim,a1.sonTartim,a1.kilo);

        if (a1.urunCinsi == 1)
        
        pastirmaToplam=pastirmaToplam+a1.kilo;

        else if (a1.urunCinsi == 2)
        sutToplam=sutToplam+a1.kilo;

        else if (a1.urunCinsi == 3)
        konserveToplam=konserveToplam+a1.kilo;

    }
   
    fclose(ptr);

    printf("\n\n Toplam Sonuclar \n\n");
    printf("Pastirma Toplam Kilo: %d \n",pastirmaToplam);
    printf("Sut Toplam Kilo: %d \n",sutToplam);
    printf("Konserve Toplam Kilo: %d \n",konserveToplam);


 }


}

int urunGirisMenu()
{


  int secim;

  printf("\n\tURUN GIRIS ISLEMLERI\n\n");
  
  printf("\t1-Arac Kantar Girisi-\n\n");
  printf("\t2-Arac Kantar Cikisi-\n\n");
  printf("\t3-Bosaltimda Bekleyen Araclar-\n\n");
  printf("\t4-Urun Girislerini Listele-\n\n");
  printf("\t0-Anamenuye Don \n\n");
  printf("seciminizi giriniz: ");
  scanf("%d",&secim);
  system("cls");
  return secim;

}


void urunGirisIslemleri()
{
    
    int secim;
    secim=urunGirisMenu();

    while(secim!=0)
    {
        switch(secim)

        {
            case 1:
            aracKantarGirisi();
            break;

            case 2:
            aracKantarCikisi();
            break;

            case 3:
            bosaltimdaBekleyenAraclar();
            break;

            case 4:
            urunGirisleriniListele();
            break;

            case 0:
            break;

            default:
            printf("yanlis secim yaptiniz");
        }

        secim=urunGirisMenu();
    }

    system("cls");
    printf("Anamenuye donuluyor...\n\n");


}

void aracKantarGirisi1()
{

    system("cls");
    printf("Urun satisi icin  Kantar Islemi...\n\n");
    arac a1;
    int numara;
    numara = 0;  
    FILE *numPtr =fopen("aracnumaralari2.dat","a+b");
    while(fread(&numara,sizeof(int),1,numPtr)!=NULL )
    {
    }

    numara++;
    fwrite(&numara,sizeof(int),1,numPtr);
    fclose(numPtr);

    a1.numara=numara;
    printf("1- SUT TOZU\n");
    printf("2- KREMA \n");
   
    printf("Urun Cinsi Seciniz [1,2,3]:  ");
    scanf("%d",&a1.urunCinsi);
    printf("Plaka Giriniz: ");
    scanf("%s",a1.plaka);
    printf("Sofor adSoyad Giriniz: ");
    scanf("%s",a1.sofor);
    printf("Gidecegi Yer Giriniz: ");
    scanf("%s",a1.geldigiYer);
    printf("Ilk Tartim Giriniz: ");
    scanf("%d",&a1.ilkTartim);
    a1.sonTartim=0;
    a1.girisTarihSaat=time(0);
    a1.cikisTarihSaat=time(0);
    a1.durum=0;
    a1.kilo=0;

   FILE *ptr =fopen("urunCikislari.dat","a+b");
   fwrite(&a1,sizeof(arac),1,ptr);
   fclose(ptr);
   printf("Arac giris kaydi basarili...\n\n");  


}

void aracKantarCikisi1()
{

    system("cls");
    printf("Urun satisi Icin Kantar Cıkıs Islemi...\n\n");
    arac a1;
    int numara;
    int sonuc=0;
    int sayac=0;
   
    FILE *ptr =fopen("urunCikislari.dat","r");
    while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 0)
        sonuc=1;
        
    }

    if (sonuc ==0 )
    {
        printf("Yuklemede Bekleyen Arac Yoktur...\n\n");
        fclose(ptr);   
    }
    else
    {
         rewind(ptr); // ptr basa alma islemi yapıyoruz !
         printf("%-20s%-20s%-20s","PLAKA","NUMARA","Ilk Tartim");
         while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 0)
        printf("%-20d%-20d%-20d",a1.plaka,a1.numara,a1.ilkTartim);
        
    }
   

    printf("Cikis Yapacak Aracin Numarasini Giriniz: ");
    scanf("%d",&numara);

    sonuc=0;
    rewind(ptr);
   
     while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 0 && a1.numara == numara)
        {

        sonuc=1;
        break;
       
        }
          sayac++;
        
    } 

     if(sonuc == 0)
     printf("%d numarali arac kaydi bulunmamaktadir ! \n",numara);
     else
     {
        printf("Son Tartim Giriniz: ");
        scanf("%d",&a1.sonTartim);
        a1.cikisTarihSaat=time(0);
        a1.durum=0;
        a1.kilo=a1.sonTartim-a1.ilkTartim;
        a1.durum=1;     // 1 olma sebebi artık arac cikis yapti demektir.

        fseek(ptr,(sayac)*sizeof(arac),SEEK_SET); // ilgili kordinata gidip kayit yapmak icin fseek kullandık gidiyoruz.
        fwrite (&a1,sizeof(arac),1,ptr);
        printf("Arac cikis islemi basarili...\n\n");

     }
      
    fclose(ptr);

    }


}

void yuklemedeBekleyenAraclar()
{

    system("cls");
    printf("Yuklemede Bekleyene Araclar...\n\n");
    arac a1;
    int numara;
    int sonuc=0;
    int sayac=0;
   
    FILE *ptr =fopen("urunCikislari.dat","r");
    while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 0)
        sonuc=1;
        
    }

    if (sonuc ==0 )
    {
        printf("Yuklemede Bekleyen Arac Yoktur...\n\n");
        fclose(ptr);   
    }
    else
    {
         rewind(ptr); // ptr basa alma islemi yapıyoruz !
         printf("%-20s%-20s%-20s","PLAKA","NUMARA","Ilk Tartim");
         while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 0)
        printf("%-20d%-20d%-20d",a1.plaka,a1.numara,a1.ilkTartim);
        
    }
   
    fclose(ptr);

    }


}

void urunSatisalariniListele()
{

    system("cls");
    printf("Satilan Urunlerin Listeleri...\n\n");
    arac a1;
    int numara;
    int sonuc=0;
    int sayac=0;
    int sutTozuToplam=0;
    int kremaToplam=0;
    
   
    FILE *ptr =fopen("urunCikislari.dat","r");
    while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 1)
        sonuc=1;
        
    }

    if (sonuc ==0 )
    {
        printf("Urun Satisi (cikisi) olmamistir...\n\n");
        fclose(ptr);   
    }
    else
    {
         system("cls");
         rewind(ptr); // ptr basa alma islemi yapıyoruz !
         printf("%-10s%-20s%-20s%-20s%-20s \n","PLAKA","NUMARA","Ilk Tartim","Son Tartim","Kilo");
         while ( fread (&a1,sizeof(arac),1,ptr) != NULL)
    { 
        if(a1.durum == 1) // arac boasaltimda ciktigi icin bir oluyor !
        printf("%-20d%-20d%-20d",a1.plaka,a1.numara,a1.ilkTartim,a1.sonTartim,a1.kilo);

        if (a1.urunCinsi == 1)
        
        sutTozuToplam=sutTozuToplam+a1.kilo;

        else if (a1.urunCinsi == 2)

        kremaToplam=kremaToplam+a1.kilo;


    }
   
    fclose(ptr);

    printf("\n\n Toplam Sonuclar \n\n");
    printf("Sut Tozu Toplam Kilo: %d \n\n",sutTozuToplam);
    printf("Krema Toplam Kilo: %d \n\n",kremaToplam);


 }
   


}



int urunCikisMenu()
{


  int secim;

  printf("\n\tURUN CIKIS ISLEMLERI\n\n");
  
  printf("\t1- ARAC KANTAR  GIRIS ISLEMLERI-\n\n");
  printf("\t2- ARAC KANTAR CIKIS ISLEMLERI-\n\n");
  printf("\t3- YUKLEMEDE BEKLEYEN ARACLAR-\n\n");
  printf("\t4- SATISI YAPILAN URUNLERI LISTELE-\n\n");
  printf("\t0-Ananmenuye Don \n\n");
  printf("seciminizi giriniz: ");
  scanf("%d",&secim);
  system("cls");
  return secim;

}



void urunCikisIslemleri()
{
   
  int secim;
  secim=urunCikisMenu();
  while (secim !=0)
  {
    switch(secim)

  {
    
    case 1:
    aracKantarGirisi1();
    break;

    case 2:
    aracKantarCikisi1();
    break;

    case 3:
    yuklemedeBekleyenAraclar();
    break;

    case 4:
    urunSatisalariniListele();
    break;

    case 0:
    break;

    default:
    printf("yanlis secim yaptiniz");

  }
  
  secim=urunCikisMenu();
  }

  system("cls");
  printf("Anamenuye donuluyor...\n\n");


}



int menu()
{


  int secim;

  printf("\n\tSUT TOZU - KREM URETIM FABRIKASI AGIRLIK TESISI OTOMASYONU\n\n");
  printf("\t KANTAR OTOMASYONU   \n\n");
  
  printf("\t1-URUN GIRIS ISLEMLERI-\n\n");
  printf("\t2-URUN CIKIS ISLEMLERI-\n\n");
  printf("\t0-PROGRAMI KAPAT \n\n");
  printf("seciminizi giriniz: ");
  scanf("%d",&secim);
  system("cls");
  return secim;

}


int main()

{

    int secim;
    secim=menu();

    while(secim!=0)
    {
        switch(secim)
        {
            case 1:
            urunGirisIslemleri();
            break;
            
            case 2:
            urunCikisIslemleri();
            break;
            
            case 0:    
            break;
            
            default:
            printf("yanlis secim yaptiniz");
            break;
            
        }
        
        secim=menu();

    }



    return 0;

}











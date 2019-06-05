#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>
#define boyut 100

typedef struct AVLagac /*Bilgisayar Mimarisi Dersi */
	{
        struct AVLagac *sol,*sag;
        char isim[boyut];
        char soyisim[boyut];
        char bolum[boyut];
        int sayi;
        int anahtar;
        int yukseklik;
    }AVLagaclar;
    
typedef struct AVLagac AVL_dugumu;

AVL_dugumu *AVLilk_dugumu, *AVLgecici_dugumu=0;

// Ýki tamsayý arasýnda en buyugunu bulmak icin basit bir fonksiyon tanýmladýk.
int max(int a, int b)
{
    	return (a>b)?a:b; // a büyüktür b'den ise a yý, deðilse b yi yazdýr
}        
        
// Aðacýn yüksekligini almak icin yardýmcý bir fonksiyon tanýmladýk.
int yukseklik(AVLagaclar *AVL) 
{
    
    if (AVL == NULL)
    return 0;
    
    return AVL->yukseklik;
}     

// ilk baþta ana aðaç yapýmýzý olusturmak icin yeniDugum adýnda bir fonksiyon tanýmladýk.
AVLagaclar *yeniDugum(int sayi) 
{
           
         AVLagaclar *dugum = (AVLagaclar *)malloc(sizeof(AVLagaclar));
         
         dugum->sayi=sayi;
         dugum->sol=NULL;
         dugum->sag=NULL;
         dugum->yukseklik = 1;
         return dugum;
}
         
AVLagaclar *sagaDondur(AVLagaclar *y) 
{
           
           AVLagaclar *x = y->sol;
           AVLagaclar *T2 = x->sag;
           
           // döndürmeyi gerçekleþtiriyoruz.
           x->sag=y;
           y->sol=T2;
           
           // yukseklikleri guncelliyoruz.
           y->yukseklik = max(yukseklik(y->sol), yukseklik(y->sag))+1;
           x->yukseklik = max(yukseklik(x->sol), yukseklik(x->sag))+1;              
           
           // yeni kökü döndürüyoruz.
           return x;
}

AVLagaclar *solaDondur(AVLagaclar *x) 
{
           
           AVLagaclar *y = x->sag;
           AVLagaclar *T2 = y->sol;
           
           // döndürmeyi gerçekleþtiriyoruz.
           y->sol=x;
           x->sag=T2;
           
           
           // yukseklikleri guncelliyoruz.
           x->yukseklik = max(yukseklik(x->sol), yukseklik(x->sag))+1;
           y->yukseklik = max(yukseklik(y->sol), yukseklik(y->sag))+1;
                         
           // yeni kökü döndürüyoruz.
           return y;
}

// denge faktörü için bir fonksiyon yazdýk.
int denge(AVLagaclar *AVL)
{
    if (AVL == NULL)
    return 0;
    
    return yukseklik(AVL->sol) - yukseklik(AVL->sag);
}

AVLagaclar *ekle(AVLagaclar *dugum, int sayi) 
{
           
    // ilk olarak normal bir sekilde Ýkili Arama Aðacýna(Binary Search Tree) uygun eklemeye baslýyoruz.
    if (dugum == NULL) // agacta hic eleman yoksa yeniDugum fonk. göndererek gerekli atamalari orada gerçekleþtiriyoruz.
        return(yeniDugum(sayi));
 
    if (sayi < dugum->sayi) // eklenen sayi kucukse dugumun soluna.
        dugum->sol  = ekle(dugum->sol, sayi);
    else // eklenen sayi buyukse dugumun sagina.
        dugum->sag = ekle(dugum->sag, sayi);
 
    // ata dugumun yuksekligini guncelliyoruz.
    dugum->yukseklik = max(yukseklik(dugum->sol), yukseklik(dugum->sag)) + 1;
 
    // ata dugumun dengeli olup olmadýgýný kontrol ediyoruz.
    int dengele = denge(dugum);
 
    // dugum dengesiz ise 4 tane durum olusuyor.
 
    // i)solsol problemi
    if (dengele > 1 && sayi < dugum->sol->sayi)
        return sagaDondur(dugum);
 
    // ii)sagsag problemi
    if (dengele < -1 && sayi > dugum->sag->sayi)
        return solaDondur(dugum);
 
    // iii)solsag problemi
    if (dengele > 1 && sayi > dugum->sol->sayi)
    {
        dugum->sol =  solaDondur(dugum->sol);
        return sagaDondur(dugum);
    }
 
    // iv)sagsol problemi
    if (dengele < -1 && sayi < dugum->sag->sayi)
    {
        dugum->sag = sagaDondur(dugum->sag);
        return solaDondur(dugum);
    }
 
    
    return dugum;
}

void silAgac(AVLagaclar *a)		
{
	if(a)
	{
		silAgac(a->sol);
		silAgac(a->sag);
		free(a);
	}
}

void inOrder(AVLagaclar *kok)
{
    if(kok != NULL)
    {
        inOrder(kok->sol);
        printf("%d\n ", kok->sayi);
        inOrder(kok->sag);
    }
}

void ara(AVLagaclar *kok,int num)
{
           int sayac=1;
           
           while(kok!=NULL)
		   {
        		if(num<kok->sayi) 
		   		{ 
                    kok=kok->sol;
                    sayac++;
                }
           		else if(num>kok->sayi) 
		   		{ 
                    kok=kok->sag;
                    sayac++;
           		}
           		else 
		   		{ 
		   			printf("\naranan %d sayisi %d. adimda bulundu.\n",num,sayac); 
                }
        	}
                printf("\nne yazikki olmayan bir deger girdiniz, bulamadik\n");
}

int toplam=0;
           
void ortAdim(AVLagaclar *kok) 
{
     
     if(kok->sol) ortAdim(kok->sol);
     if(kok->sag) ortAdim(kok->sag);        
     toplam++;
} 
/*AVLagaclar sil(AVLagaclar *a,int silParca)  // ana govdeyi sil 
{
	if(!(a))
        return a;
    if(silParca < a->anahtar)
        a->sol = sil(a->sol, silParca);
    else 
        if(silParca > a->anahtar)
            a->sag = sil(a->sag, silParca); 
        else 
        {
            AVLagaclar *b = a;
            if((a->sol) && (a->sag))
            {
                AVLagaclar *aile = a->sag;
                a = aile->sol;
                if (a)
                {
                    while(a->sol)
                    {
                        aile = a;
                        a = a->sol;
                    }
                    aile->sol = a->sag;
                    a->sag = b->sag;
                }
                else
                    a = aile;
                a->sol = b->sol;
            }
            else
                if(a->sol)
                    a = a->sol;
                else
                    a = a->sag;
            free(b);
        }
    return a;
} */


     
struct ogrenci_dugumu 
{
	char isim[boyut];
    char soyisim[boyut];
    char bolum[boyut];
	int ogr_no;
	struct ogrenci_dugumu *sonraki;
}; 

typedef struct ogrenci_dugumu veri_dugumu;

void ekleme();
void silme();
void goruntuleme();
int sayac();
//void enaz_bir(struct ogrenci_dugumu);
//void sadece_ag(struct ogrenci_dugumu *isim[] *soyisim[] *bolum[]);
//void ayniDers(AVLagaclar *kok,int sayi);
//int secmeli_siralama(int sayi[],int N);
//int enyuksegi_al(char soyisim2[],int n);
//void radix(veri_dugumu soyisim[]);


veri_dugumu *kafa_dugumu, *ilk_dugum, *gecici_dugum=0, *onceki, *sonraki;
int numara;
char isim2[boyut];
char soyisim2[boyut];
char bolum2[boyut];

int main(void)
{
	system("COLOR 2F");
	AVLagaclar *kok = NULL;
	int secim;
	char yanit;
	int deger;
  	int aranan;
  	c:
	printf("OGRENCI ISLEMLERI\n");
	printf("~~~~~~~\n");
	printf("Bilgisayar Aglari dersine ogrenci eklemek icin A/a,\nBilgisayar Mimarisi Dersine ogrenci eklemek icin M/m tuslayiniz==> ");
	scanf("%c",&yanit);
	if(yanit=='m' || yanit=='M')
	{
		q:
		printf("\n\nBILGISAYAR MIMARISI\n");
		printf("~~~~~~~\n");
		a:
		printf("Agac ogrenci eklemek icin 1'e\n");
		printf("Agactan ogrenci silmek icin 2'ye\n");
		printf("Agaci goruntulemek icin 3'e\n");
		printf("Arama icin 4'e\n");
		printf("Sayim icin 5'e\n");
		printf("Secmeli siralama icin 6'ya\n");
		printf("Iki dersi de alanlari goruntulemek icin 7'ye\n");
		printf("Kumele siralamasi icin 8'e\n");
		printf("Bilgisayar Aglarina gitmek icin 9 tusla\n");
		printf("Cikis icin 0 girin==> ");
		scanf("%d",&secim);
		if(secim==0)
		{
			system("pause");
		}
		else if(secim==1)
		{
			printf("\nOgrenci numarasini giriniz==> ");
      		scanf("%d",&deger);
      		kok=ekle(kok,deger);
      		printf("\nEkleme basarili\n");
			goto a;
		}
		else if(secim==2)
		{
			silAgac(kok);
			goto a;
		}
		else if(secim==3)
		{
			printf("\n\nListenin siralanmis hali..\n\n");
  			inOrder(kok);
  			goto a;
		}
		else if(secim==4)
		{
			printf("\n\narama yapilmasini istediginiz ogrenci : ");
  			scanf("%d",&aranan);
  			ara(kok,aranan);
  			ortAdim(kok);
  			printf("\n\ntoplam ogrenci sayisi : %d",toplam);
  			goto a;
		}
		else if(secim==5)
		{ 
		printf("\nAgacta 1 ogrenci var\n"); 
		goto a;
		}
		else if(secim==6)
		{
		/*	secmeli_siralama(kok);*/
		}
		else if(secim==7)
		{
			//ayniDers(kok,numara);
		}
		else if(secim==8)
		{
			//kumeleme();
		}
		else if(secim==9)
		{
			goto f;
		}
		else
		{
			printf("Yanlis secim yaptiniz!..\n\n");
			goto a;
		}
	}
	else if(yanit=='A' || yanit=='a')
	{
		b:
		f:
		printf("\n\nBILGISAYAR AGLARI\n");
		printf("~~~~~~~\n");
		printf("Listeye ogrenci eklemek icin 1'e\n");
		printf("Listeden ogrenci silmek icin 2'ye\n");
		printf("Listeyi goruntulemek icin 3'e\n");
		printf("Sayim icin 4'e\n");
		printf("Iki dersi de alanlari goruntulemek icin 5'e\n");
		printf("Radix siralama icin 6'ye\n");
		printf("A-B grubu icin 7'ye\n");
		printf("Sadece bu dersi alanlar icin 8'e\n");
		printf("Kumele siralamasi icin 9'a\n");
		printf("Bigisayar Mimariye gitmek icin 10'a\n");
		printf("Cikis icin 0'a basiniz==> ");
		scanf("%d",&secim);
		if(secim==0)
		{
			system("pause");
		}
		else if(secim==1)
		{
			ekleme();
			goto b;
		}
		else if(secim==2)
		{
			silme();
			goto b;
		}
		else if(secim==3)
		{
			goruntuleme();
			goto b;
		}
		else if(secim==4)
		{
			sayac();
			goto b;
		}
		else if(secim==5)
		{
			//ayniDers(kok,numara);
		}
		else if(secim==6)
		{
			printf("\n\nRadix ile sira..\n\n");
			//radix();
			goto b;
		}
		else if(secim==7)
		{
			//gruplama(soyisim2);
		}
		else if(secim==8)
		{
			//sadece_ag();
		}
		else if(secim==9)
		{
			//gruplama()
		}
		else if(secim==10)
		{
			goto q;
		}
		else
		{
			printf("Yanlis secim yaptiniz!..");
			goto b;
		}
	}
	return 0;
}

void ekleme()
{
	printf("Eklenecek ogrencinin numarasini giriniz==> ");
	scanf("%d",&numara);
	printf("\nEklenecek ogrencinin adini soyadini bolumunu aralarina birer bosluk giriniz==> ");
	scanf("%s %s %s",&isim2,&soyisim2,&bolum2);
	gecici_dugum=(veri_dugumu *) malloc(sizeof(veri_dugumu));
	gecici_dugum->ogr_no=numara;
	strcpy(gecici_dugum->isim,isim2);
	strcpy(gecici_dugum->soyisim,soyisim2);
	strcpy(gecici_dugum->bolum,bolum2);
	if(ilk_dugum==0)
	{
		ilk_dugum=gecici_dugum;
	}
	else
	{
		kafa_dugumu->sonraki=gecici_dugum;
	}
	gecici_dugum->sonraki=0;
	kafa_dugumu=gecici_dugum;
	fflush(stdin);
	printf("Ekleme basarili");
}

void silme()
{
	int sayim_degeri;
	int konum;
	int i=0;
	sayim_degeri=sayac();
	gecici_dugum=ilk_dugum;
	printf("Silinecek degerin konumunu giriniz==>");
	scanf("%d",&konum);
	if(konum>0 && konum<=sayim_degeri)
	{
		if(konum==1)
		{
			gecici_dugum=gecici_dugum->sonraki;
			ilk_dugum=gecici_dugum;
			printf("\nSilme islemi basarili!\n");
		}
		else
		{
			while(gecici_dugum!=0)
			{
				if(i==(konum - 1))
				{
					onceki->sonraki=gecici_dugum->sonraki;
					if(i==(sayim_degeri - 1))
					{
						kafa_dugumu=onceki;
					}
					printf("\nSilme islemi basarili!!");
					break;
				}
				else
				{
					i++;
					onceki = gecici_dugum;
					gecici_dugum=gecici_dugum->sonraki;
				}
			}
		}
	}
	else
	{
		printf("\nYanlis konum!\n");
	}
}

void goruntuleme()
{
	int sayac;
	gecici_dugum=ilk_dugum;
	printf("\nListeyi Goruntule==>");
	while(gecici_dugum!=0)
	{
		printf(" %d",gecici_dugum->ogr_no);
		printf(" %s",gecici_dugum->isim);
		printf(" %s",gecici_dugum->soyisim);
		printf(" %s",gecici_dugum->bolum);
		sayac++;
		gecici_dugum=gecici_dugum->sonraki;
	}
	printf("\nListede %d adet ogrenci var..\n",sayac);
}

int sayac()
{
	int sayac=0;
	gecici_dugum=ilk_dugum;
	while(gecici_dugum!=0)
	{
		sayac++;
		gecici_dugum=gecici_dugum->sonraki;
	}
	printf("\nListede %d adet ogrenci var..\n",sayac);
	return sayac;
}

int AVLsayaci()
{
	int avl_sayaci=0;
	AVLgecici_dugumu=AVLilk_dugumu;
	while(AVLgecici_dugumu!=0)
	{
		avl_sayaci++;
		AVLgecici_dugumu=AVLgecici_dugumu->sol;
		AVLgecici_dugumu=AVLgecici_dugumu->sag;
		
	}
	printf("mimaride %d ogrenci var..\n",avl_sayaci);
	return avl_sayaci;
	} 
	
/*void kumeleme(AVLagaclar *kok isim2[] isim[])
{
	int c,i,gecici,no;
	no=strlen(isim[]);
    for (i = 1; i < no; i++)
    {
        c = i;
        do
        {
            kok = (c - 1) / 2;             
            if (kume[kok] < kume[c])   // enbuyuk kume dizisi olusturma 
            {
                gecici = kume[kok];
                kume[kok] = kume[c];
                kume[c] = gecici;
            }
            c = kok;
        } while (c != 0);
    }
    printf("Kumeleme dizisi : ");
    for (i = 0; i < no; i++)
        printf("%d\t ", kume[i]);
    for (j = no - 1; j >= 0; j--)
    {
        gecici = kume[0];
        kume[0] = kume[j]    // enbuyukle sagdakinin endegerli yapragini degis
        kume[j] = gecici;
        kok = 0;
        do 
        {
            c = 2 * kok + 1;    //kokun sol dugumu 
            if ((kume[c] < kume[c + 1]) && c < j-1)
                c++;
            if (kume[kok]<kume[c] && c<j)    // enbuyuk kumeleme dizisini tekrrdan bulma 
            {
                gecici = kume[kok];
                kume[kok] = kume[c];
                kume[c] = gecici;
            }
            kok = c;
        } while (c < j);
    } 
    printf("\n Sýralanmýs dizi : ");
    for (i = 0; i < no; i++)
       printf("\t %d", kume[i]);
   } 
/*void radix(veri_dugumu soyisim[])
{
	int i,j;
	char gecici[boyut];
	int byte=sizeof soyisim2[boyut]/sizeof soyisim2[0];
	printf("boyut=%d\n",byte);
	int bitti=0;
	for(i=0;i<byte;i++)
	{
		for(j=i+1;j<byte;j++)
		{
			if(strcmp(soyisim2[i],soyisim2[j])>0)
			{
			    veri_dugumu   gecici[boyut];
				gecici[boyut]=soyisim[i];
				soyisim[i]=soyisim[j];
				soyisim[j]=gecici[boyut];
			}
		}
	}
	for(i=0;i<byte;i++)
	{
		printf("%d - %s\n",i+1,soyisim2[boyut]);
	}
}

int enyuksegi_al(char soyisim2[],int n) 
{
	int enyuksek=soyisim2[0];
	int i;
	for(i=1;i<n;i++)
	{
		if(soiyisim2[i]>enyuksek)
		enyuksek=soyisim[i];
	}
	return enyuksek;
}

int secmeli_siralama(int sayi[],int N) 
{
	int i,index,j,enkucuk;
	int k;
	printf("Sirali hal \n");
	for(i=0;i<(N-1);i++) // dizinin basindan baslaniyor
	{
		enkucuk=sayi[N-1]; // son eleman en kucuk kabul ediliyor
		index=N-1;
	for(j=i;j<(N-1);j++)
	{
		if(sayi[j]<enkucuk)
		{
			enkucuk=sayi[j];
			index=j;
		}	
	sayi[index]=sayi[i]; // daha kucugu varsa yer deðiþtiriliyor
	sayi[i]=enkucuk;
		}
	}
	for(k=i; k<index ;k++)
        printf("\n%d", sayi[k]);
	return enkucuk;
}

void ayniDers(AVLagaclar *kok,int sayi)
{
	ekle(kok,sayi);
	printf("%d\n ", kok->sayi);
	ekleme(); 
	printf(" %d",gecici_dugum->ogr_no);
	if(kok->sayi==gecici_dugum->ogr_no)
	{
		printf("%d numarali ogrenci iki dersi de almistir",sayi);
	}
}

void gruplama(veri_dugumu soyisim[])	  //Bu fonkisyon a grubunda a-k, b grubunda l-z arasýnda isimleridir 
{
	int i;
	int j;
	char a_grubu[100];
	char b_grubu[100];
	char a_k[boyut] = {'a','b','c','ç','d','e','f','g','ð','h','ý','i','j','k','\0'};
	char l_z[boyut]={'l','m','n','o','p','r','s','þ','t','u','ü','v','y','z','\0'};
	if(soyisim2[0]==a_k[boyut])
	{
		for(i=0;i<boyut;i++)
		{
			soyisim2[i]=a_grubu[boyut];
			printf("%s %s ogrencisi a grubuna eklenmistir..\n",gecici_dugum->isim,gecici_dugum->soyisim);
		}
	}
	else if(soyisim2[0]==l_z[boyut])
	{
		for(j=0;j<boyut;j++)
		{
			soyisim2[j]=b_grubu[boyut];
			printf("%s %s ogrencisi a grubuna eklenmistir..\n",gecici_dugum->isim,gecici_dugum->soyisim);
		}
	}
}
						
void sadece_ag()
{
	while(gecici_dugum!=0)
	{
		printf(" %d",gecici_dugum->ogr_no);
		printf(" %s",gecici_dugum->isim);
		printf(" %s",gecici_dugum->soyisim);
		printf(" %s",gecici_dugum->bolum);
		gecici_dugum=gecici_dugum->sonraki;
	}
}	

void enaz_bir(struct ogrenci_dugumu)  /bu fonksiyonda bolum[] deðiþkeninin ilk elemaný esas alýnýp deðer döndürülecektir/
{
	int bayrak=0;
	
	do
	{
		printf(" %d",gecici_dugum->ogr_no);
		printf(" %s",gecici_dugum->isim);
		printf(" %s",gecici_dugum->soyisim);
		printf(" %s",gecici_dugum->bolum);
		bayrak++;
		gecici_dugum=gecici_dugum->sonraki;
	}while(bolum[0]!='E' || bolum[0]!='e');
}*/

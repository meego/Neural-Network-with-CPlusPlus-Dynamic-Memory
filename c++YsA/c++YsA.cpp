// c++YsA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
class noron;
class baglanti;
class katman;

void olustur(katman*, int, noron*, baglanti*, int);
int baglantiSayisiHesapla(katman*, int);
float degerAta(int altSinir, int ustSinir);
void egitimSetiOlustur(float *girisDegerleri, float *cikisDegerleri, int girisKatmanNoronSayisi, int cikisKatmanNoronSayisi, int egitimSetiUzunlugu);

float gecisFonksiyonu(float gelenNoronDegeri, float agirlikDegeri);

class katman{
public:
	float katmanNo;
	float noronSayisi;
	katman(){
		katmanNo = 0;
		noronSayisi = 0;
	}
};
class noron{
public:
	float deger;
};
class baglanti{
public:
	int baglantiNo;
	float agirlik;
	noron *sonrakiNoron;
	noron *oncekiNoron;
};
void olustur(katman *k, int katmanSayisi, noron *ag, baglanti*connections, int noronSayisi)
{
	int baglantiNo = 0;
	katman *temp = k;

	baglanti *baglantilar = connections;
	printf("\nbaglantiSayisi  =  %d", noronSayisi*katmanSayisi);
	noron *temporary = ag;
	noron *ag2 = ag;
	int i = 0, j = 0;
	for (int x = 1; x <= katmanSayisi - 1; x++){
		for (i = 0; i < k[x - 1].noronSayisi; i++){
			ag2 += i;
			for (j = 0; j < k[x].noronSayisi; j++){
				temporary += x + j;
				baglantilar->oncekiNoron = ag2;
				baglantilar->sonrakiNoron = temporary;
				baglantilar->agirlik = degerAta(1, 5);
				baglantilar->baglantiNo = baglantiNo;
				baglantiNo++;
				baglantilar++;
			}
			temporary -= x + j;
		}
		ag2++;
		temporary = ag2;
	}
}
float degerAta(int altSinir, int ustSinir){
	float sayi = 0;
	srand(time(NULL));
	sayi = rand() % (ustSinir + altSinir) + altSinir;
	return sayi;
}
int baglantiSayisiHesapla(katman *k, int katmanSayisi)
{
	int baglantiSayisi = 0;
	for (int i = 1; i <= katmanSayisi; i++)
	{
		baglantiSayisi += k[i].noronSayisi*k[i - 1].noronSayisi;
	}
	return baglantiSayisi;
}
void egitimSetiOlustur(float *girisDegerleri,float *cikisDegerleri,int girisKatmanNoronSayisi,int cikisKatmanNoronSayisi,int egitimSetiUzunlugu)
{
	for (int i = 0; i < egitimSetiUzunlugu; i++)
	{
		printf("%d. ****Veriler**** \n",i);
		for (int j = 0; j < girisKatmanNoronSayisi; j++)
		{
			printf("%d. Egitim Verisi %d. Giris Noronu Degeri = ",i, j);
			scanf_s("%f", girisDegerleri);
			girisDegerleri++;
		}
		printf("\n");
		for (int j = 0; j < girisKatmanNoronSayisi; j++)
		{
			printf("%d. Egitim Verisi %d. Cikis Noronu Degeri = ",i, j);
			scanf_s("%f", cikisDegerleri);
			cikisDegerleri++;
		}
		printf("\n");
	}
}
void egit(int egitimSetiUzunlugu, float *girisVerileri, float *cikisVerileri, katman *k, noron *ag, baglanti *baglantilar, int noronSayisi, int katmanSayisi, int baglantiSayisi, int lambda, int momentum,int hataToleransi )
{
	for (int i = 0; i < egitimSetiUzunlugu; i++)
	{
		for (int j = 0; j < k->noronSayisi; j++)//giris Verilerini Atadik.
		{
			ag[j].deger = *girisVerileri;
			girisVerileri++;
		}
		/*for (int l = 0; l < k[katmanSayisi-1].noronSayisi; l++)//cikis Verilerini Atadik.
		{
			ag[noronSayisi - l].deger = *cikisVerileri;
			cikisVerileri++;
		}*/
		for (int w = 0; w < baglantiSayisi; w++)//agda dolasma.
		{
			baglantilar->sonrakiNoron->deger += gecisFonksiyonu(baglantilar->oncekiNoron->deger, baglantilar->agirlik);
		}
		//ilk egitim seti tamamlandý þimdi hata kontrolü yapýlacak : 
		for (int l = 0; l < k[katmanSayisi - 1].noronSayisi; l++)
		{
			float hataDegeri = ag[noronSayisi - l].deger - *cikisVerileri;
			if (abs(hataDegeri) > hataToleransi)
			{
				//hata var geri yayýlým yapilacak ve agirliklarin yeni deðerleri hesaplanacak
				float C = ag[noronSayisi - l].deger;
				float sigma = C*(1-C)*hataDegeri;
				for (int v = 0; v < baglantiSayisi; v++)
				{
					if (baglantilar[v].sonrakiNoron == &ag[noronSayisi - l])//agirlik Guncellemesi Yapýlýyor.
					{
						float DeltaDegeri = lambda*sigma*C + momentum * 0;
						baglantilar[v].agirlik = DeltaDegeri + baglantilar[v].agirlik;//guncellenmis AgirlikDegeri.
						//ilk iterasyonda agirlik = deltadegeri + 0; olacak.
						//---------------------*----------------**********************----------------**************
					}
				}
			}
		}
	}
}
float gecisFonksiyonu(float gelenNoronDegeri, float agirlikDegeri)
{
	return 0.0f;
}
int _tmain(int argc, _TCHAR* argv[])
{
	/*while (argv != NULL)
	{
	argv++;
	}*/
	float lambda = 0, momentum = 0,hataToleransi=0;
	int katmanSayisi = 0, toplamNoronSayisi = 0, baglantiSayisi, egitimSetiUzunlugu = 0;
	printf("Katman Sayisini Giriniz : ");
	scanf_s("%d", &katmanSayisi);
	katman *katmanlar = (katman *)calloc(katmanSayisi, sizeof(katman));
	katman *temp = katmanlar;
	for (int i = 0; i < katmanSayisi; i++){
		int noronSayisi = 0;
		temp->katmanNo = i;
		printf("%d . Katman Noron Sayisini Giriniz : ", i); scanf_s("%d", &noronSayisi);
		temp->noronSayisi = noronSayisi;
		toplamNoronSayisi += noronSayisi;
		temp++;
	}
	noron *ag = (noron *)calloc(toplamNoronSayisi, sizeof(noron));
	baglantiSayisi = baglantiSayisiHesapla(katmanlar, katmanSayisi);
	baglanti *baglantilar = (baglanti *)calloc(baglantiSayisi, sizeof(baglanti));//baðlantiSayisi ?
	olustur(katmanlar, katmanSayisi, ag, baglantilar, toplamNoronSayisi);
	int ;
	printf("\n	Egitim Seti \n");
	printf("Egitim Seti Veri Uzunlugunu Giriniz : "); scanf_s("%d", &egitimSetiUzunlugu);
	float *girisEgitimVerileri = (float *)calloc(katmanlar->noronSayisi*egitimSetiUzunlugu, sizeof(float));
	float *cikisEgitimVerileri = (float *)calloc(katmanlar[katmanSayisi - 1].noronSayisi*egitimSetiUzunlugu, sizeof(float));
	egitimSetiOlustur(girisEgitimVerileri, cikisEgitimVerileri, katmanlar->noronSayisi, katmanlar[katmanSayisi - 1].noronSayisi,egitimSetiUzunlugu);
	return 0;
}
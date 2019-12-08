#include <iostream>
#include <stdio.h>
#include <random>
#include <time.h>

#define NOFSAMPLE 60000
#define RR 0.1

double TRAINDATA[NOFSAMPLE][28][28];
int LABEL[NOFSAMPLE];

double TESTDATA[10000][28][28];
int LABELFOTTEST[10000];

void ARRANGEMINIBATCH(unsigned int(*A)[10]);

class NUMBEROUT
{
public:
	double NUMBER[10];
	NUMBEROUT(int n=0);
	NUMBEROUT(double *K);
	int OUT();
};

int NUMBEROUT::OUT()
{
	int T = 0;
	int i;
	for ( i = 0; i <= 9; i++)
	{
		if (NUMBER[i] > NUMBER[T])
		{
			T = i;
		}
	}
	return T;
}

double ERROR(int L, NUMBEROUT K);

NUMBEROUT::NUMBEROUT(int n)
{
	int i;
	memset(NUMBER, 0, sizeof(NUMBER));
	if (n >= 0 && n <= 9)
	{
		NUMBER[n] = 1;
	}
}

NUMBEROUT::NUMBEROUT(double *K)
{
	memcpy(NUMBER, K, sizeof(NUMBER));
}

class NerualNetwork
{
public:
	double W1[30][784];
	double B1[30];
	double W2[10][30];
	double B2[10];
	NerualNetwork();
	NUMBEROUT CLASSIFYNUMBER(double(*SAMPLE)[28]);
	int TRAIN(int EPOCH);
	NerualNetwork(const char P[7]);
	void GENERATE(double *Z1, double *A1, double *Z2, double *A2, double(*SAMPLE)[28]);
	void BACKPROPOGATION(double *Z1, double *A1, double *Z2, double *A2, double *E1, double *E2,int L);
	void WG(double *GB1, double *GB2, double(*GW1)[784], double(*GW2)[30],double *E1,double *E2, double(*SAMPLE)[28], double *A1);
	void REARRANGE(double *GB1, double *GB2, double(*GW1)[784], double(*GW2)[30],double R=0.3);
};

NerualNetwork::NerualNetwork()
{
	std::default_random_engine E(time(0));
	std::normal_distribution<double> N(0, 1);
	int i, j, k;
	for ( i = 0; i <=29; i++)
	{
		for ( j = 0; j <= 783; j++)
		{
			W1[i][j] = N(E);
		}
		B1[i] = N(E);
	}
	for ( i = 0; i <= 9; i++)
	{
		for (j = 0; j <= 29; j += 1)
		{
			W2[i][j] = N(E);
		}
		B2[i] = N(E);
	}
}

NUMBEROUT NerualNetwork::CLASSIFYNUMBER(double(*SAMPLE)[28])//正态分布，初始化
{
	int i;
	int j;
	double Z1[30];
	double A1[30];
	double Z2[10];
	double A2[10];
	GENERATE(Z1, A1, Z2, A2, SAMPLE);
	return NUMBEROUT(A2);
}

void NerualNetwork::BACKPROPOGATION(double *Z1, double *A1, double *Z2, double *A2, double *E1, double *E2,int L)
{
	int i,j;
	double T;
	NUMBEROUT TEMP(L);
	for ( i = 0; i <= 9; i++)
	{
		T = exp(-Z2[i]);
		E2[i] = (A2[i]-TEMP.NUMBER[i]) * T / ((1 + T)*(1 + T));
	}
	for ( i = 0; i <= 29; i++)
	{
		T = exp(-Z1[i]);
		E1[i] = 0;
		for ( j = 0; j <= 9; j++)
		{
			E1[i] += E2[j] * W2[j][i];
		}
		E1[i] *= T / ((1 + T)*(1 + T));
	}
}

double ERROR(int L, NUMBEROUT K)
{
	int i;
	double S = 0;
	NUMBEROUT LL(L);
	for (i = 0; i <= 9; i += 1)
	{
		S += (LL.NUMBER[i] - K.NUMBER[i])*(LL.NUMBER[i] - K.NUMBER[i]);
	}
	S = S / 2;
	return S;
}

int NerualNetwork::TRAIN(int EPOCH)
{
	int i, j, k;
	double E1[30];
	double E2[10];
	double Z1[30];
	double A1[30];
	double Z2[10];
	double A2[10];
	double GB1[30];
	double GB2[30];
	double GW1[30][784];
	double GW2[10][30];
	double S1, S2;
	double M1, M2;
	int NOW=0;
	unsigned int HASH[NOFSAMPLE/10][10];
	for (i = 0; i <= EPOCH; i += 1)
	{
		ARRANGEMINIBATCH(HASH);
		for (j = 0; j <= (NOFSAMPLE - 1) / 10; j++)
		{
			memset(GB1, 0, sizeof(GB1));
			memset(GB2, 0, sizeof(GB2));
			memset(GW1, 0, sizeof(GW1));
			memset(GW2, 0, sizeof(GW2));
			S1 = 0;
			S2 = 0;
			M1 = 0;
			M2 = 0;
			for ( k = 0; k <= 9; k++)
			{
				int P=4, Q=455;
				GENERATE(Z1, A1, Z2, A2, TRAINDATA[HASH[j][k]]);
				//std::cout << HASH[j][k] << std::endl;
				memset(E1, 0, sizeof(E1));
				memset(E2, 0, sizeof(E2));
				BACKPROPOGATION(Z1, A1, Z2, A2, E1, E2, LABEL[HASH[j][k]]);
				WG(GB1, GB2, GW1, GW2, E1, E2, TRAINDATA[HASH[j][k]], A1);
				S1 += ERROR(LABEL[HASH[j][k]], NUMBEROUT(A1));
				//M1 += ERROR(LABEL[HASH[j][k]], A2);
				//B2[P] += 0.1;
				//GENERATE(Z1, A1, Z2, A2, TRAINDATA[HASH[j][k]]);
				//B2[P] -= 0.1;
				//M2 += ERROR(LABEL[HASH[j][k]], A2);

				//std::cout << (M2 - M1) / 0.1 << " " << GB2[P] << std::endl;
				//system("pause");
			}
			REARRANGE(GB1, GB2, GW1, GW2);
			for (k = 0; k <= 9; k++)
			{
				//int P=12, Q=455;
				GENERATE(Z1, A1, Z2, A2, TRAINDATA[HASH[j][k]]);
				S2 += ERROR(LABEL[HASH[j][k]], NUMBEROUT(A1));
			}
			//std::cout << S1 << " " << S2 << std::endl;
			//system("pause");
			if (NOW != (i*(NOFSAMPLE - 1) / 10 + j)*100 / ((NOFSAMPLE - 1) / 10 * EPOCH))
			{
				NOW = (i*(NOFSAMPLE - 1) / 10 + j) *100/ ((NOFSAMPLE - 1) / 10 * EPOCH);
				system("cls");
				std::cout <<NOW<< std::endl;
			}
			
		}
		int KK;
		KK = 0;
		for (int ii = 0; ii <= 9999; ii++)
		{
			if (CLASSIFYNUMBER(TESTDATA[i]).OUT() == LABELFOTTEST[ii])
			{
				KK += 1;
			}
		}
		std::cout <<i<<" "<< KK * 100.0 / 10000 << std::endl;
	}
	return 0;
}

void  NerualNetwork::REARRANGE(double *GB1, double *GB2, double(*GW1)[784], double(*GW2)[30],double R)
{
	int i;
	int j;
	for (i = 0; i <= 29; i++)
	{
		for (j = 0; j <= 783; j += 1)
		{
			W1[i][j] -=RR* GW1[i][j];
		}
		B1[i] -=  RR*GB1[i];
	}
	for (i = 0; i <= 9; i++)
	{
		for (j = 0; j <= 29; j += 1)
		{
			W2[i][j] -=RR*GW2[i][j];
		}
		B2[i] -= RR*GB2[i];
	}
}


void NerualNetwork::WG(double *GB1, double *GB2, double(*GW1)[784], double(*GW2)[30],double *E1,double *E2, double(*SAMPLE)[28],double *A1)
{
	int i;
	int j;
	for ( i = 0; i <= 29; i++)
	{
		for (j = 0; j <= 783; j += 1)
		{
			GW1[i][j] += E1[i] * SAMPLE[j/28][j%28];
		}
		GB1[i] += E1[i];
	}
	for ( i = 0; i <= 9; i++)
	{
		for (j = 0; j <= 29; j += 1)
		{
			GW2[i][j] += E2[i] * A1[j];
		}
		GB2[i] += E2[i];
	}
}

NerualNetwork::NerualNetwork(const char P[7])
{
	FILE *fp1;
	fopen_s(&fp1, P, "rb");
	fread(W1, 8, 30 * 784, fp1);
	fread(W2, 8, 300, fp1);
	fread(B1, 8, 30, fp1);
	fread(B2, 8, 10, fp1);
	fclose(fp1);
	return;
}

void NerualNetwork::GENERATE(double *Z1,double *A1,double *Z2,double *A2, double(*SAMPLE)[28])
{
	int i;
	int j;
	for (i = 0; i <= 29; i++)
	{
		Z1[i] = 0;
		for (j = 0; j <= 783; j += 1)
		{
			Z1[i] += W1[i][j] * SAMPLE[j / 28][j % 28];
		}
		Z1[i] += B1[i];
		A1[i] = 1 / (1 + exp(-Z1[i]));
		//std::cout << Z1[i] <<" " <<A1[i]<<std::endl;
	}
	//std::cout<<std::endl;
	for (i = 0; i <= 9; i++)
	{
		Z2[i] = 0;
		for (j = 0; j <= 29; j += 1)
		{
			Z2[i] += W2[i][j] * A1[j];
		}
		Z2[i] += B2[i];
		A2[i] = 1 / (1 + exp(-Z2[i]));
	}
}

void ARRANGEMINIBATCH(unsigned int (*A)[10])
{
	int i;
	memset(A, -1, 4*NOFSAMPLE);
	std::default_random_engine E(time(0));
	std::uniform_int_distribution<int> U(0,NOFSAMPLE-1);
	int T;
	for ( i = 0; i <= NOFSAMPLE-1; i++)
	{
		T = U(E);
		while (A[T / 10][T % 10] >= 0 && A[T / 10][T % 10] <= NOFSAMPLE - 1)
		{
			T = U(E);
		}
		A[T / 10][T % 10] = i;
	}
	return;
}

void main()
{
	FILE *fp1,*fp2;
	int i,j,k;
	unsigned char TRAINDATATEMP[28][28];
	fopen_s(&fp1,"train_images","rb");//l六万张图像，28✖️28大小，手写数字
	fopen_s(&fp2,"train_labels","rb");//六万个标示
	fseek(fp1,16, 0);
	fseek(fp2, 8, 0);
	for ( i = 0; i <= NOFSAMPLE-1; i++)
	{
		fread(TRAINDATATEMP, 1, 28*28, fp1);//读一个图片
		fread(LABEL+i, 1, 1, fp2);
		for ( j = 0; j <= 27; j++)
		{
			for ( k = 0; k <= 27; k++)
			{
				TRAINDATA[i][j][k] = (uint8_t)TRAINDATATEMP[j][k] > 128 ? 1 : 0;//进入大数组，二进制阈值化
			}
		}
	}
	fclose(fp1);
	fclose(fp2);

	
	//NerualNetwork NW1("OUTPUT");

	NerualNetwork NW1{};

	int K = 0;
	for (i = 0; i <= 59999; i++)
	{
		if (NW1.CLASSIFYNUMBER(TRAINDATA[i]).OUT() == LABEL[i])
		{
			K += 1;
		}
	}
	std::cout << K * 100.0 / 60000 << std::endl;


	fopen_s(&fp1, "train_images", "rb");
	fopen_s(&fp2, "train_labels", "rb");
	fseek(fp1, 16, 0);
	fseek(fp2, 8, 0);
	for (i = 0; i <= 9999; i++)
	{
		fread(TRAINDATATEMP, 1, 28 * 28, fp1);
		fread(LABELFOTTEST + i, 1, 1, fp2);
		for (j = 0; j <= 27; j++)
		{
			for (k = 0; k <= 27; k++)
			{
				TESTDATA[i][j][k] = (uint8_t)TRAINDATATEMP[j][k] > 128 ? 1 : 0;
				//printf("%2x ",(uint8_t)TRAINDATATEMP[j][k]);
			}
			//std::cout << std::endl;
		}
		//std::cout << LABELFOTTEST[i] << std::endl;
	}
	fclose(fp1);
	fclose(fp2);
	K = 0;
	for (i = 0; i <= 9999; i++)
	{
		if (NW1.CLASSIFYNUMBER(TESTDATA[i]).OUT() == LABELFOTTEST[i])
		{
			K += 1;
		}
	}
	std::cout << K * 100.0 / 10000 << std::endl;

	system("pause");

	NW1.TRAIN(1200);
	//fopen_s(&fp1, "OUTPUT", "wb");	
	//fwrite(NW1.W1, sizeof(double), 30 * 784, fp1);
	//fwrite(NW1.W2, sizeof(double), 10 * 30, fp1);
	//fwrite(NW1.B1, sizeof(double), 30, fp1);
	//fwrite(NW1.B2, sizeof(double), 10, fp1);
	//fclose(fp1);

	K=0;
	for ( i = 0; i <= 59999; i++)
	{
		if (NW1.CLASSIFYNUMBER(TRAINDATA[i]).OUT() == LABEL[i])
		{
			K += 1;
		}
	}
	std::cout << K * 100.0 / 60000<<std::endl;

	
	K = 0;
	for (i = 0; i <= 9999; i++)
	{
		if (NW1.CLASSIFYNUMBER(TESTDATA[i]).OUT() == LABELFOTTEST[i])
		{
			K += 1;
		}
	}
	std::cout << K * 100.0 / 10000 << std::endl;

	system("pause");
}

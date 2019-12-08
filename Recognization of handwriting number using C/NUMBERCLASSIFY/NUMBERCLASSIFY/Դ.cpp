#include <iostream>
#include <stdio.h>
#include <random>
#include <time.h>
#include <stdlib.h> 
#include <Windows.h>

double DATA[28][28];
double DATAHAVEMODI[28][28];

int IMAGEREAD(char *p);

class NUMBEROUT
{
public:
	double NUMBER[10];
	NUMBEROUT(int n = 0);
	NUMBEROUT(double *K);
	int OUT1();
};

int NUMBEROUT::OUT1()
{
	int T = 0;
	int i;
	for (i = 0; i <= 9; i++)
	{
		if (NUMBER[i] > NUMBER[T])
		{
			T = i;
		}
	}
	return T;
}

double ERROR1(int L, NUMBEROUT K);

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
	NerualNetwork(const char P[7]);
	NUMBEROUT CLASSIFYNUMBER(double(*SAMPLE)[28]);
	void GENERATE(double *Z1, double *A1, double *Z2, double *A2, double(*SAMPLE)[28]);
};

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

NerualNetwork::NerualNetwork()
{
	std::default_random_engine E(time(0));
	std::normal_distribution<double> N(0, 1);
	int i, j, k;
	for (i = 0; i <= 29; i++)
	{
		for (j = 0; j <= 783; j++)
		{
			W1[i][j] = N(E);
		}
		B1[i] = N(E);
	}
	for (i = 0; i <= 9; i++)
	{
		for (j = 0; j <= 29; j += 1)
		{
			W2[i][j] = N(E);
		}
		B2[i] = N(E);
	}
}

NUMBEROUT NerualNetwork::CLASSIFYNUMBER(double(*SAMPLE)[28])
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

double ERROR1(int L, NUMBEROUT K)
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

void NerualNetwork::GENERATE(double *Z1, double *A1, double *Z2, double *A2, double(*SAMPLE)[28])
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

void main()
{
	CopyFile("C:\\Users\\10025\\source\\repos\\ML\\ML\\OUTPUT", "OUTPUT", FALSE);
	NerualNetwork N1("OUTPUT");
	IMAGEREAD((char *)("data.bmp"));
	int i;
	int j;
	int X = 0;
	int Y = 0;
	int N=0;
	int i0;
	int j0;
	for ( i = 0; i <= 27; i++)
	{
		for (j = 0; j <= 27; j += 1)
		{
			if (DATA[i][j]==1)
			{
				X += i;
				Y += j;
				N += 1;
			}
		}
	}
	X /= N;
	Y /= N;
	//std::cout << X << " " << Y << std::endl;
	for ( i = 0; i <= 27; i++)
	{
		for (j = 0; j <= 27; j += 1)
		{
			i0 = 14 + i - X;
			j0 = 14 + j - Y;
			if (i0>=0&&i0<=27&&j0>=0&&j0<=27)
			{
				DATAHAVEMODI[i0][j0] = DATA[i][j];
			}
		}
	}
	std::cout << std::endl;
	/*for (i = 0; i < 28; i++)
	{
		for (j = 0; j < 28; j++)
		{
			printf("%2x ", (uint8_t)DATAHAVEMODI[i][j]);
		}
		printf("\n");
	}*/
	std::cout << N1.CLASSIFYNUMBER(DATAHAVEMODI).OUT1();
	system("pause");
}

int IMAGEREAD(char *p)
{
	FILE *fp;
	char tmp;
	fopen_s(&fp,p,"rb");
	int weight,height;
	fseek(fp,18,SEEK_CUR);
	fread(&weight,4,1,fp);//偏移18字节，长度4字节，位图宽度	
	fread(&height,4,1,fp);//偏移22字节，长度4字节，位图高度	
	//printf("weight:%d height:%d \n",weight,height);	
	fseek(fp,0x3e,SEEK_SET);//二值图像数据的偏移
	char *pho=(char *)malloc(sizeof(char)*weight*height);//存储图像的每一个像素点
	int i,j,k;	
	int m;
	for(i=height-1;i>=0;i--)
	{	
		for(j=0;j<weight/8+(bool)(weight%8);j++)//图像的宽度现在只能是4*8的倍数，如64,96...		
		{	
			fread(&tmp,1,1,fp);
			if (j == weight / 8 + (bool)(weight % 8) - 1)
			{
				for (k = 0; k < weight%8; k++)
				{
					if (tmp&(1 << (7 - k)))
						pho[i*weight + j * 8 + k] = 0;
					else
						pho[i*weight + j * 8 + k] = 1;
				}
			}
			else
			{
				for(k=0;k<8;k++)
				{
					if(tmp&(1<<(7-k)))
						pho[i*weight+j*8+k]=0;
					else
						pho[i*weight+j*8+k]=1;
				}
			}
			
		}
	}
	/*for(i=0;i<height;i++)
	{
		for(j=0;j<weight;j++)
		{
			printf("%2x ",(uint8_t)pho[i*weight+j]);
		}
		printf("\n");
	}*/
	fclose(fp);
	for ( i = 0; i <=27; i++)
	{
		for (j = 0; j <= 27; j += 1)
		{
			DATA[i][j] = pho[i*weight + j];
		}
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include<math.h>

#define N 100
#define PI 3.141592

unsigned short Theta[N]={0};
unsigned short K[N]={0};
double coeff=PI/180.0;

double M_val=32760;
unsigned short fp2fix(double M, double x)
{
    return M*x;
}

double fix2fp(double M, unsigned short x)
{
    return x/M;
}


void calcul_vecteur()
{
    double temp=0;
    for(int i=0;i<N;i++)
    {
        Theta[i]=fp2fix(M_val,atan(pow(2.0,-i)));

        K[i]=fp2fix(M_val,cos(atan(pow(2.0,-i))));
        //printf("T:%u K:%u \n",Theta[i],K[i]);
    }
}

short int cordic_fixe(short int phi_int,int n_iter,unsigned short *xr,unsigned short *yr,unsigned short *errcos,unsigned short *errsin)
{
    short int x[2]={0};
    x[0]=1.0;
    for(int j=0;j<=n_iter;j++)
    {
        x[0]*=K[j];
    }
    short int y[2]={0};
    short int alpha=0.0;

    printf("phi= %d\n",phi_int);
    for(int i=0;i<=n_iter;i++)
    {
        if(alpha<phi_int)
        {
            x[1]=x[0]-(y[0]>>i);
            y[1]=y[0]+(x[0]>>i);
            alpha=alpha+Theta[i];
        }else
        {
            x[1]=x[0]+(y[0]>>i);
            y[1]=y[0]-(x[0]>>i);
            alpha=alpha-Theta[i];
        }
        printf("x: %lf | y: %lf \n",fix2fp(M_val,x[0]),fix2fp(M_val,y[0]));
        printf("x: %u | y: %u \n",x[0],y[0]);
        x[0]=x[1];
        y[0]=y[1];

    }
    *xr=x[0];
    *yr=y[0];
    *errcos=*xr-fp2fix(M_val,cos(phi_int));
    *errsin=*yr-fp2fix(M_val,sin(phi_int));
    printf("x: %lf | y: %lf",fix2fp(M_val,*xr),fix2fp(M_val,*yr));
    printf(" |errcos = %lf | ",fix2fp(M_val,*errcos));
    printf("errsin = %lf\n",fix2fp(M_val,*errsin));
}



int main()
{


    FILE* fichier=NULL;
    //fichier = fopen("output/erreur_max.dat", "w+");



    unsigned short xf,yf;
    short int erc,ers;
    double PHI;
    int iter;
    short int errmax=0;
    calcul_vecteur();


    printf("Entrez PHI et le nombre d iterations:");
    scanf("%lf %d",&PHI,&iter);
    cordic_fixe(fp2fix(M_val,PHI*coeff),iter,&xf,&yf,&erc,&ers);
    /*
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<=90;j++)
        {
            printf("iterations %d   |",j);
            cordic_fixe(PHI+j,i,&xf,&yf,&erc,&ers);
            if(erc>errmax)
            {
                errmax=erc;
            }
        }
        if(fichier!=NULL)
        {
            //fprintf(fichier,"%d\t%lf\t%lf\n",j,erc,ers);
            fprintf(fichier,"%d\t%lf\n",i,errmax);
        }
        errmax=0;
    }

    fclose(fichier);*/
    //system ("gnuplot -p -e \"plot 'output/erreur_n_.dat' u 1:2 w l, 'output/erreur_n_.dat' u 1:3 w l\";");

    //system ("gnuplot -p -e \"plot 'output/erreur_n_4.dat' u 1:2 w l, 'output/erreur_n_4.dat' u 1:3 w l\";");
    //system ("gnuplot -p -e \"plot 'output/erreur_n_8.dat' u 1:2 w l, 'output/erreur_n_8.dat' u 1:3 w l\";");
    //system ("gnuplot -p -e \"plot 'output/erreur_n_16.dat' u 1:2 w l, 'output/erreur_n_16.dat' u 1:3 w l\";");
    //system ("gnuplot -p -e \"plot 'output/erreur_n_32.dat' u 1:2 w l, 'output/erreur_n_32.dat' u 1:3 w l\";");
    //system ("gnuplot -p -e \"plot 'output/erreur_max.dat' u 1:2 w l\";");
    return 0;
}

/**MARIMOUTOU Mourougen**/
#include <stdio.h>
#include <stdlib.h>
#include<math.h>

#define N 100
#define PI M_PI


double coeff=PI/180.0;

double Theta[N]={0};
double K[N]={0};

void calcul_vecteur()
{
    double d=1;
    for(int i=0;i<N;i++)
    {
        Theta[i]=atan(d);
        K[i]=cos(atan(d));
        d=d/2;
    }
}

double cordic(double phi_int,int n_iter,double *xr,double *yr,double *errcos,double *errsin)
{
    double x[2]={0};
    x[0]=1.0;
    for(int j=0;j<=n_iter;j++) //Calcul de An
    {
        x[0]*=K[j];
    }
    double y[2]={0};
    double d=1;
    double alpha=0.0;


    for(int i=0;i<=n_iter;i++)
    {
        if(alpha<phi_int*coeff)
        {
            x[1]=x[0]-(y[0]*d);
            y[1]=y[0]+(x[0]*d);
            alpha=alpha+Theta[i];
        }else
        {
            x[1]=x[0]+(y[0]*d);
            y[1]=y[0]-(x[0]*d);
            alpha=alpha-Theta[i];
        }
        x[0]=x[1];
        y[0]=y[1];
        d=d/2;
    }
    *xr=x[0];
    *yr=y[0];
    *errcos=*xr-cos(phi_int*coeff);
    *errsin=*yr-sin(phi_int*coeff);
    printf("x: %.16lf | y: %.16lf ",*xr,*yr);
    printf(" |errcos = %.10lf | ",*errcos);
    printf("errsin = %.16lf\n",*errsin);

}



int main()
{


    FILE* fichier=NULL;
    fichier = fopen("output/erreur_max.dat", "w+");



    double xf,yf;
    double erc,ers;
    double PHI;
    int iter;
    double errmax=0;
    calcul_vecteur();



    //printf("Entrez PHI et le nombre d iterations:");
    //scanf("%lf %d",&PHI,&iter);
    //cordic(PHI,iter,&xf,&yf,&erc,&ers);

    for(int i=4;i<64;i++)
    {
        for(int j=0;j<=90;j++)
        {
           printf("iterations %d   |",j);
            cordic(PHI+j,i,&xf,&yf,&erc,&ers);
            if(erc>errmax)
            {
                errmax=erc;
            }
            if(fichier!=NULL)
            {
                //fprintf(fichier,"%d\t%.16lf\t%.16lf\n",j,erc,ers);
                //fprintf(fichier,"%d\t%lf\n",i,log10(errmax));
                fprintf(fichier,"%d\t%lf\n",i,errmax);
            }
        }
        errmax=0;
    }

    fclose(fichier);
    //system ("gnuplot -p -e \"plot 'output/erreur_n_.dat' u 1:2 w l, 'output/erreur_n_.dat' u 1:3 w l\";");

    //system ("gnuplot -p -e \"plot 'output/erreur_n_4.dat' u 1:2 w l, 'output/erreur_n_4.dat' u 1:3 w l\";");
    //system ("gnuplot -p -e \"plot 'output/erreur_n_8.dat' u 1:2 w l, 'output/erreur_n_8.dat' u 1:3 w l\";");
    //system ("gnuplot -p -e \"plot 'output/erreur_n_16.dat' u 1:2 w l, 'output/erreur_n_16.dat' u 1:3 w l\";");
    //system ("gnuplot -p -e \"plot 'output/erreur_n_32.dat' u 1:2 w l, 'output/erreur_n_32.dat' u 1:3 w l\";");
    //system ("gnuplot -p -e \"plot 'output/erreur_n_64.dat' u 1:2 w l, 'output/erreur_n_64.dat' u 1:3 w l\";");
    system ("gnuplot -p -e \"plot 'output/erreur_max.dat' u 1:2 w l\";");
    return 0;
}

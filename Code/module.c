#include <stdio.h>
#include <math.h>
#include "header.h"

#define Uvh_MAX 50
#define Uvh_MIN -50
#define Uvyh_MIN 10
#define Uvyh_MAX 33.25

double parameter(double *Uvyh, int n, double dt) {
    double dlit = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (Uvyh[i] >= Uvyh_MIN + 0.5*(Uvyh_MAX-Uvyh_MIN)) {
            dlit+=dt;
        }
    }

    return dlit;
}


void formUvh(int n, double *Uvh, double *t, int a, int b, int tn,int t1,int t2, int tk) {
    int i;

    for (i = 0; i < n; i++) {
        if (t[i] <= 10) {
            Uvh[i] = 10*(t[i] - 5);
        } else if (t[i] <= 40) {
            Uvh[i] = 10*(10-5);
        } else if (t[i] > 40 && t[i]<45) {
            Uvh[i] = 10*(10-5) - 10*(t[i] - 40);
        }
    }
    
}

void formUvyh(int n, double *Uvyh, double *Uvh, double a1, double b1, double a2, double b2, double a3, double b3, int Uvh1, int Uvh2, int Uvh3) {
    int i;
   for (i = 0; i < n; i++) {
        if (Uvh[i] <= 5) {
            Uvyh[i] = 0.25*Uvh[i]+9;
        } else if (Uvh[i] <= 15) {
            Uvyh[i] = 0.5*Uvh[i] + 7,75;
        } else if (Uvh[i] <= 30) {
            Uvyh[i] = 1.1*Uvh[i]+0.25;
        }else if(Uvh[i] > 30){
            Uvyh[i] = 25*Uvh[i] - 29.75;
        }
    }
}

void formTable(int n, double *t, double *Uvh, double *Uvyh) {
    int i;

    printf("\n  №   t           Uvh           Uvyh\n");
    for (i = 0; i < n; i++) {
        printf("%3d   %.7f   %.7f   %6.1f\n", i+1, t[i], Uvh[i], Uvyh[i]);
    }

}

void printToFile(double *t, double *Uvh, double *Uvyh, int n) {
    int i;
    FILE *f1, *f2, *f3;

    f1 = fopen("WXmaxima/array_t.txt", "w");
    f2 = fopen("WXmaxima/array_Uvh.txt", "w");
    f3 = fopen("WXmaxima/array_Uvyh.txt", "w");

    for (i = 0; i < n; i++) {
        fprintf(f1, "\n%.7f", t[i]);
        fprintf(f2, "\n%.7f", Uvh[i]);
        fprintf(f3, "\n%6.1f", Uvyh[i]);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
}

void pulseTime(double *Uvyh, int n, double dt) {
    double dlit = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (Uvyh[i] >= Uvyh_MIN + 0.5*(Uvyh_MAX-Uvyh_MIN)) {
            dlit+=dt;
        }
    }

    printf("Длительность импульса сигнала: %.6f\n", dlit);
}

void durPulseEdge(double *Uvyh, int n, double dt) {
    double dlit = 0;
    int i;
    double U1 = Uvyh_MIN + 0.9*(Uvyh_MAX-Uvyh_MIN);
    double U2 = Uvyh_MIN + 0.1*(Uvyh_MAX-Uvyh_MIN);

    for (i = 0; i < n; i++) {
        if (Uvyh[i] > U1 && Uvyh[i] < U2 && Uvyh[i+1] < Uvyh[i]) {
            dlit+=dt;
        }
    }

    double dlit2 = 0;

    for (i = 0; i < n; i++) {
        if (Uvyh[i] > U1 && Uvyh[i] < U2 && Uvyh[i+1] > Uvyh[i]) {
            dlit2+=dt;
        }
    }

    printf("Длительность заднего фронта импульса сигнала: %.6f\nДлительность переднего фронта импульса сигнала: %.6f\n", dlit, dlit2);
}

void timeAt80Uvh(double *t, double *Uvh, int n) {
    int i, index = -1;

    for (i = 0; i < n; i++) {
        if (Uvh[i] > 80.0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Сигнал Uvh не достиг 80В\n");
    } else {
        printf("Сигнал Uvh достиг 80В в момент времени: %.6f\n", t[index]);
    }
}

void timeAtMaxUvh(double *t, double *Uvh, int n) {
    int i;
    double time;

    for (i = 0; i < n; i++) {
        if (Uvh[i] == Uvh_MAX) {
            time = t[i];
        }
    }

    printf("Сигнал Uvh достиг максимума в момент времени: %.6f\n", time);
}

void writeInFiles(int n) {
    double t[n], Uvh[n], Uvyh[n];
    int i;
    int a = 10, b = 10, tn = 5, t1 = 10, t2 = 40, tk = 45;
    double a1 = 0.25, b1 = 9, a2 = 0.5, b2 =7.75, a3 = 1.1, b3 = 0.25;
    int Uvh1=5, Uvh2=15, Uvh3=30;

    formUvh(n, Uvh, t, a, b, tn, t1, t2, tk);
    formUvyh(n, Uvyh, Uvh, a1, b1, a2, b2, a3, b3, Uvh1, Uvh2, Uvh3);
    printToFile(t, Uvh, Uvyh, n);

    printf("Files created in folder WXmaxima\n");
}

void controlCalc(int n) {
    double t[n], Uvh[n], Uvyh[n], dt;
    int i;
    int a = 10, b = 10, tn = 5, t1 = 10, t2 = 40, tk = 45;
    double a1 = 0.25, b1 = 9, a2 = 0.5, b2 =7.75, a3 = 1.1, b3 = 0.25;
    int Uvh1=5, Uvh2=15, Uvh3=30;

    formUvh(n, Uvh, t, a, b, tn, t1, t2, tk);
    formUvyh(n, Uvyh, Uvh, a1, b1, a2, b2, a3, b3, Uvh1, Uvh2, Uvh3);

    formTable(n, t, Uvh, Uvyh);

    pulseTime(Uvyh, n, dt);
    durPulseEdge(Uvyh, n, dt);
    timeAt80Uvh(t, Uvh, n);
    timeAtMaxUvh(t, Uvh, n);
}

void showTitle() {

    FILE *f = fopen("ResourceFiles/zast.txt", "r");
    if (f == NULL) {
        fprintf(stderr, "cant open a file\n");
    }
    char sym = fgetc(f);

    while (sym != EOF) {
        printf("%c", sym);
        sym = fgetc(f);
    }
    fclose(f);

    printf("\n");
}

void precisionCalc(double eps) {
    double p = 1.0, par = 1e10;
    int n = 2, i, dt;

    int a = 10, b = 10, tn = 5, t1 = 10, t2 = 40, tk = 45;
    double a1 = 0.25, b1 = 9, a2 = 0.5, b2 =7.75, a3 = 1.1, b3 = 0.25;
    int Uvh1=5, Uvh2=15, Uvh3=30;

    printf("\nРасчет параметра с точностью %.10f:\n", eps);
    printf(" n\tПараметр\tПогрешность\n");
    
    while (p > eps) {
        double t[n], Uvh[n], Uvyh[n];

        formUvh(n, Uvh, t,a,b,tn,t1,t2,tk);
        formUvyh(n, Uvyh, Uvh,a1,b1,a2,b2,a3,b3,Uvh1,Uvh2,Uvh3);
        
        double par1 = parameter(Uvyh, n, dt);
        p = (par == 1e10) ? 1.0 : fabs(par - par1) / par1;
        
        printf("%d\t%.10f\t%.10f\n", n, par1, p);
        
        par = par1;
        n *= 2;
        
        if (n > 1000000) {
            printf("Достигнут предел итераций!\n");
            break;
        }
    }
    
    printf("\nИтоговый параметр: %.10f\n", par);
}

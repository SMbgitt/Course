#ifndef FUNCIONS_N
#define FUNCIONS_N

void formUvh(int n, double *Uvh, double *t, int a, int b, int tn,int t1,int t2, int tk);
void formUvyh(int n, double *Uvyh, double *Uvh, double a1, double b1, double a2, double b2, double a3, double b3, int Uvh1, int Uvh2, int Uvh3);
void formTable(int n, double *t, double *Uvh, double *Uvyh);
void printToFile(double *t, double *Uvh, double *Uvyh, int n);
void pulseTime(double *Uvyh, int n, double dt);
void durPulseEdge(double *Uvyh, int n, double dt);
void timeAt80Uvh(double *t, double *Uvh, int n);
void timeAtMaxUvh(double *t, double *Uvh, int n);
void controlCalc(int n);
void writeInFiles(int n);
void showTitle();
void precisionCalc(double eps);

#endif
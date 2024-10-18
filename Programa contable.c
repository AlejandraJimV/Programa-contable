/*
Elaborado por Alejandra Jiménez Venegas 
Contabilidad
Este código es un ejemplo completo de un sistema contable en C, que integra funcionalidades de gestión de cuentas,cálculos fiscales
 y visualización de resultados. Permite a los usuarios realizar tareas contables de manera eficiente y organizada.*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>
#include <ctype.h>
#define color SetConsoleTextAttribute
#define MAX_STRING_LENGTH 50
#define MAX_ACTIVOS 100
#define N 100
#define MAX 50

void continuar();
void gotoxy(int x,int y){  
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
} 


struct cuentas1{
	char codigo1[30];
	char cuenta[100];
	float debe[20];
	float haber[20];
	float saldodeudor;
	float saldoacreedor;  
};

void calcular_ISR();
void bienvenidaISR();


struct Activo {
    char nombre[MAX_STRING_LENGTH];
    char registro[100];  // Se aumenta el tamaño del registro para incluir el sufijo numérico
    char localizacion[MAX_STRING_LENGTH];
    float valorInicial;
    int vidaUtil;
    float depreciacionAnual;
    float depreciacionMensual;
};

void titulo1();
struct Activo tablaActivos[MAX_ACTIVOS];
int numActivos = 0;
void calcularDepreciacion(struct Activo *activo);
void generarCodigoRegistro(struct Activo *activo, struct tm *tm_info);
void imprimirTablaContable();
void tabladeDep();


void bienvenidaSDI();
void borrarSDI();
void calcularSDI();

void mostrarempresa();
void ingresadatosdeempresa();
void crearusuario();
void comercialcontrasenia ();
void comercialinicializarcuenta();
void comercialmostrarcuentas();
void comercialmostrarcuentas22();
void comercialrayadodiario();
void comercialesquemasmayor();
void comercialbalanza();
void comercialbalancegeneral();
void comercialestadoderesultados();
void comercialtargetasdealmacen();
void borar();
char passconta[10];
char passauxi[10]= {"virginia"};
char usuariocont[20];
char usuarioaux[20]={"contabilidad"}; 
struct cuentas1 comercial[N];  
char pass[10];
char empresa[10];
char fecha[30];
void gotoxy(int x,int y);
void titulo();
void nombre_empresa();
void hora();
void tabladeA();
int interes(double *tasaInteres);
void mostrarInteres(int opcion);
int op_plazo(int *plazo);
void mostrarPlazo(int opcion);
void saldos_insolutos(float montoPrestamo, float intereses, float plazo);
void tasa_fija(float montoPrestamo, float intereses, float plazo);
int i=0; 	
int aux[N], aux2[N];
float activo, activocirculante, activonocirculante, activodiferido, pasivo, pasivocirculante, pasivonocirculante, pasivodiferido;
float movimientodeudor, movimientoacreedor, saldoacreedor, saldodeudor;
float summovideudor,summoviacreedor,sumsaldeudor,sumsalacreedor;
float saldo=0;
float medio=0;
float totalACcirculante=0, totaAClfijo=0, totalACdiferido=0, totalPAScirculante=0, totalPASfijo=0, totalPASdiferido=0;
float totalAC=0, totalPAS=0;
float suma1degeneral=0, suma2degeneral=0, suma3degeneral=0,inventarioinicial=0;
int p=0, pa=0, pe=0, pi=0, po=0, pu=0, y=0;
char subcuenta[20][20],subcuenta1[20][20],subcuenta2[20][20],subcuenta3[20][20],subcuenta4[20][20];
float piezas[20],precio[20],piezas1[20],precio1[20],piezas2[20],precio2[20],piezas3[20],precio3[20],piezas4[20],precio4[20];
float merdebe[20],merhaber[20];
float merdebe1[20],merhaber1[20];
float merdebe2[20],merhaber2[20];
float merdebe3[20],merhaber3[20];
float merdebe4[20],merhaber4[20];
int medi=0,medi1=0,medi2=0,medi3=0,medi4=0;
int n=0,n1=0,n2=0,n3=0,n4=0,ayuda=0;

typedef struct {
    char codigo[MAX];
    char nombre[MAX];
} Cuentas;


void agregar_cuenta() {
    Cuentas cuenta;
    FILE *archivo;
    
    archivo = fopen("cuentas.txt","a");
    
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        exit(0);
    }
    gotoxy(30, 8);
    printf("Ingrese el codigo de la cuenta: ");
    fflush(stdin);
    gets(cuenta.codigo);
    gotoxy(30, 9);
    printf("Ingrese el nombre de la cuenta: ");
    fflush(stdin);
    gets(cuenta.nombre);
	
	fprintf(archivo, "%s,%s\n", cuenta.codigo, cuenta.nombre);
    
    fclose(archivo);
}

void modificar_cuenta() {
    
    Cuentas cuenta;
    FILE *archivoEntrada, *archivoSalida;
    char linea[1000];
    char codigo[MAX];

    archivoEntrada = fopen("cuentas.txt", "r");
    archivoSalida = fopen("temporal.txt", "w");

    if (archivoEntrada == NULL || archivoSalida == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
	gotoxy(30, 8);
	printf("Ingrese el codigo de la cuenta a modificar: ");
	fflush(stdin);
    gets(codigo);
    
    while (fscanf(archivoEntrada, "%[^,],%[^\n]\n", cuenta.codigo,cuenta.nombre) != EOF) {
    	if (strcmp(cuenta.codigo,codigo) != 0){
    		fprintf(archivoSalida, "%s,%s\n", cuenta.codigo, cuenta.nombre);
		}else{
			gotoxy(30, 10);
			printf("Ingrese el nuevo codigo de la cuenta: ");
			fflush(stdin);
		    gets(cuenta.codigo);
		    gotoxy(30, 11);
		    printf("Ingrese el nombre de la cuenta: ");
		    fflush(stdin);
		    gets(cuenta.nombre);
		    gotoxy(30, 15);
		    printf("Cuenta añadida...");
		    Sleep(1500);
		    fprintf(archivoSalida, "%s,%s\n", cuenta.codigo, cuenta.nombre);
		}
    }

    fclose(archivoEntrada);
    fclose(archivoSalida);

    remove("cuentas.txt");
    rename("temporal.txt", "cuentas.txt");
}

void eliminar_cuenta() {
	Cuentas cuenta;
    FILE *archivoEntrada, *archivoSalida;
    char linea[1000];
    char codigo[MAX];

    archivoEntrada = fopen("cuentas.txt", "r");
    archivoSalida = fopen("temporal.txt", "w");

    if (archivoEntrada == NULL || archivoSalida == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
	gotoxy(30, 8);
	printf("Ingrese el codigo de la cuenta a eliminar: ");
	fflush(stdin);
    gets(codigo);
    
    while (fscanf(archivoEntrada, "%[^,],%[^\n]\n", cuenta.codigo,cuenta.nombre) != EOF) {
    	if (strcmp(cuenta.codigo,codigo) != 0){
    		fprintf(archivoSalida, "%s,%s\n", cuenta.codigo, cuenta.nombre);
		}
    }

    fclose(archivoEntrada);
    fclose(archivoSalida);

    remove("cuentas.txt");
    rename("temporal.txt", "cuentas.txt");
}

void ver_cuentas() {
	
	int i = 0, j = 0, k = 0, m = 0, n = 0, o = 0;
	Cuentas cuenta;
    FILE *archivo;
    
    archivo = fopen("cuentas.txt","r+");
    
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
    
    
    while (fscanf(archivo, "%[^,],%[^\n]\n", cuenta.codigo,cuenta.nombre) != EOF) {
    	if(cuenta.codigo[0] == '1'){
    		if(cuenta.codigo[2] == '1'){
	    		printf("\n%s %s\n", cuenta.codigo,cuenta.nombre);
	    		i++;
			}else if(cuenta.codigo[2] == '2'){
	    		printf("\n%s %s\n", cuenta.codigo,cuenta.nombre);
	    		j++;
			}else if(cuenta.codigo[2] == '3'){
	    		printf("\n%s %s\n", cuenta.codigo,cuenta.nombre);
	    		k++;
			}
		}else if(cuenta.codigo[0] == '2'){
			if(cuenta.codigo[2] == '1'){
	    		printf("\n%s %s\n", cuenta.codigo,cuenta.nombre);
	    		m++;
			}else if(cuenta.codigo[2] == '2'){
	    		printf("\n%s %s\n", cuenta.codigo,cuenta.nombre);
	    		n++;
			}else if(cuenta.codigo[2] == '3'){
	    		printf("\n%s %s\n", cuenta.codigo,cuenta.nombre);
	    		o++;
			}
		}
    	
    }
    fclose(archivo);
}

void cuentas(){
	int opcion;
	margen(1, 3, 100, 25);
    do {
    	margen(1, 3, 100, 25);
    	gotoxy(30, 8);
        printf("Menu Principal");
        gotoxy(30, 10);
        printf("1. Agregar cuenta\n");
        gotoxy(30, 11);
        printf("2. Modificar cuenta\n");
        gotoxy(30, 12);
        printf("3. Eliminar cuenta\n");
        gotoxy(30, 13);
        printf("4. Ver cuentas\n");
        gotoxy(30, 14);
        printf("5. Catalogo de cuentas");
        gotoxy(30, 15);
        printf("6. Salir");
        gotoxy(30, 17);
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
		system("cls");
        switch (opcion) {
            case 1:
            	margen(1, 3, 100, 25);
                agregar_cuenta();
                break;
            case 2:
            	margen(1, 3, 100, 25);
                modificar_cuenta();
                break;
            case 3:
            	margen(1, 3, 100, 25);
                eliminar_cuenta();
                break;
            case 4:
                ver_cuentas();
                break;
            case 5:
            comercialmostrarcuentas();
            break;
            case 6:
            	margen(1, 3, 100, 25);
            	gotoxy(30, 14);
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Por favor, seleccione nuevamente.\n");
                break;
        }
    getch();
    system("cls");
    } while (opcion != 6);

}
void tablanomina(){
	int hh,ee,OX,OY;
	OX=0;OY=0;
	gotoxy(120,6);printf("NOMINA");
	gotoxy(118,8);printf("INGRESO");
	gotoxy(110,10);printf("SUELDO");
	gotoxy(110,12);printf("PG");
	gotoxy(110,14);printf("PE");
	gotoxy(110,18);printf("SUB TOTAL");
	gotoxy(140,8);printf("DEDUCCION");
	gotoxy(134,10);printf("IMSS");
	gotoxy(134,12);printf("ISR");
	gotoxy(134,18);printf("SUB DED.");
	gotoxy(134,20);printf("TOTAL");
	for(ee=6;ee<=20;ee++){
		if(ee!=6){
			if(ee!=8){
				gotoxy(119,ee);printf("|");
				gotoxy(142,ee);printf("|");
			}
			gotoxy(133,ee);printf("|");
			
		}
		ee++;
		for(hh=110;hh<156;hh++){
			gotoxy(hh,ee);printf("-");
		}
	}
	//
	for(ee=4;ee<=26;ee++){
		gotoxy(38,ee);printf("|");
		gotoxy(47,ee);printf("|");
		gotoxy(58,ee);printf("|");
		gotoxy(70,ee);printf("|");
		gotoxy(83,ee);printf("|");
		gotoxy(96,ee);printf("|");
		ee++;
		for(hh=0;hh<108;hh++){
			gotoxy(hh,ee);printf("-");
		}
	}
	gotoxy(0,4);printf("RAMOS SEGUROS                         |");
	gotoxy(39,4);printf("PATRON");
	gotoxy(48,4);printf("EMPLEADO");
	gotoxy(59,4);printf("CALCULO");
	gotoxy(71,4);printf("CUOTA/P");
	gotoxy(84,4);printf("CUOTA/E");
	gotoxy(97,4);printf("PAGO TOTAL");
	
	gotoxy(0,6);printf("I. PRIMA TOTAL                        ");
	gotoxy(48,6);printf("     0.00%c",37);
	gotoxy(59,6);printf("SDI");
	
	gotoxy(0,8);printf("II. ENFERMEDADES Y MATERNIDAD         ");
	
	
	gotoxy(0,10);printf("	CUOTA FIJA                    ");
	gotoxy(39,10);printf("  20.40%c",37);
	gotoxy(48,10);printf("     0.00%c",37);
	gotoxy(59,10);printf("SOBRE IVT");
	
	gotoxy(0,12);printf("	CUOTA ADICIONAL               ");
	gotoxy(39,12);printf("   1.10%c",37);
	gotoxy(48,12);printf("     0.40%c",37);
	gotoxy(59,12);printf("S/EXCEDENTE");
	
	gotoxy(0,14);printf("	PRESTACION EN EL DINERO       ");
	gotoxy(39,14);printf("   0.70%c",37);
	gotoxy(48,14);printf("     0.25%c",37);
	gotoxy(59,14);printf("SDI");
	
	gotoxy(0,16);printf("	GASTOS MEDICOS A PENSIONADOS  ");
	gotoxy(39,16);printf("   1.05%c",37);
	gotoxy(48,16);printf("    0.375%c",37);
	gotoxy(59,16);printf("SDI");
	
	gotoxy(0,18);printf("III. INVALIDEZ Y VIDA                 ");
	gotoxy(39,18);printf("   1.75%c",37);
	gotoxy(48,18);printf("     0.00%c",37);
	gotoxy(59,18);printf("SDI");
	
	gotoxy(0,20);printf("IV. GUARDERIAS Y PRESTACIONES SOCIALES");
	gotoxy(39,20);printf("   1.00%c",37);
	gotoxy(48,20);printf("     0.00%c",37);
	gotoxy(59,20);printf("SDI");
	
	gotoxy(0,22);printf("V. RETIRO                             ");
	gotoxy(39,22);printf("   2.00%c",37);
	gotoxy(48,22);printf("     0.00%c",37);
	gotoxy(59,22);printf("SDI");
	
	gotoxy(0,24);printf("VI. CESANTIA Y VEJEZ                  ");
	gotoxy(48,24);printf("    1.125%c",37);
	gotoxy(59,24);printf("SDI");
	
	gotoxy(0,26);printf("VII. FONDO                            ");
	gotoxy(39,26);printf("   5.00%c",37);
	gotoxy(48,26);printf("     0.00%c",37);
	gotoxy(59,26);printf("SDI");
	gotoxy(70,28);printf("|");
	gotoxy(83,28);printf("|");
	gotoxy(96,28);printf("|");
}
void nomina(){
	float clase[] = {0.54355, 1.13065, 2.5984, 4.65325, 7.58875};
    float cotizacion[] = {3.15, 3.413, 4, 4.353, 4.588, 4.756, 4.882, 5.331};
    float sueldo, UMA, tUMA, vUMA, SDIF, DDSDIF, exx;
    int ddd, icl, cddd = 0, zcoti, sal;
    char titulo[] = "Título";
    
    UMA = 108.57;
    tUMA = UMA * 3;
    vUMA = UMA * 25;
    time_t tiempo_actual;
    time(&tiempo_actual);
    struct tm *info_tiempo = localtime(&tiempo_actual);
    
    do {
        system("cls");
        printf("%s\n", titulo);
        printf("Fecha: %02d/%02d/%02d\n", info_tiempo->tm_mday, info_tiempo->tm_mon + 1, info_tiempo->tm_year + 1900);
	//sueldo	icl		dd
	do{
		system("cls");
		//gotoxy(54,1);printf(dim BLACK_T LIME_F"%s"RESET_COLOR,titulo);
	//	gotoxy(5,1); printf("  %02d/%02d/%02d  "RESET_COLOR, info_tiempo->tm_mday,info_tiempo->tm_mon+1,info_tiempo->tm_year+1900);
		gotoxy(33,0);printf("CALCULO DE NOMINA DE OBRERO/PATRONAL");
		tablanomina();
		getch();
		system("cls");
		//entrada
		gotoxy(5,2);printf("SUELDO $");
		scanf("%f",&sueldo);
		do{
			gotoxy(30,2);printf("DIAS[28][29][30[31]]= ");
			scanf("%d",&ddd);
			if(ddd>=28&&ddd<=31){
				cddd=1;
			}
			gotoxy(30,2);printf("DIAS[28][29][30[31]]=           ");
		}while(cddd==0);
		cddd=0;
		do{
			gotoxy(60,2);printf("CLASE[1 a 5]=");
			scanf("%d",&icl);
			if(icl>=1&&icl<=5){
				cddd=1;
			}
			gotoxy(60,2);printf("CLASE[1 a 5]=           ");
		}while(cddd==0);
		icl--;
		cddd=0;
		int falso=sueldo;
		//uma diferencia
		zcoti=0;
		if(sueldo>=(UMA*1.01)&&sueldo<=(UMA*1.50)){
			zcoti=1;
		}else{
			if(sueldo>=(UMA*1.51)&&sueldo<=(UMA*2.00)){
				zcoti=2;
			}else{
				if(sueldo>=(UMA*2.01)&&sueldo<=(UMA*2.50)){
					zcoti=3;
				}else{
					if(sueldo>=(UMA*2.51)&&sueldo<=(UMA*3.00)){
						zcoti=4;
					}else{
						if(sueldo>=(UMA*3.01)&&sueldo<=(UMA*3.50)){
							zcoti=5;
						}else{
							if(sueldo>=(UMA*3.51)&&sueldo<=(UMA*4.00)){
								zcoti=6;
							}else{
								if(sueldo>=(UMA*4.01)){
									zcoti=7;
								}
							}
						}
					}
				}
			}
		}
		
		if(sueldo>=vUMA){
			sueldo=vUMA;
		}
		gotoxy(39,24);printf("  %.3f%c",cotizacion[zcoti],37);
		gotoxy(39,6);printf("%.5f%c",clase[icl],37);
		//sdi
		float primap,primae,primat,presp,prese,prest,gasp,gase,gast,inp,ine,intt,gup,gue,gut,retip,retie,retit,cesap,cesae,cesat,fonp,fone,font;
		primap=0;primae=0;primat=0;presp=0;prese=0;prest=0;
		gasp=0;gase=0;gast=0;inp=0;ine=0;intt=0;gup=0;gue=0;gut=0;
		retip=0;retie=0;retit=0;cesap=0;cesae=0;cesat=0;
		fonp=0;fone=0;font=0;
		SDIF=sueldo+((15*sueldo)/365)+((12*sueldo*.25)/365);
		DDSDIF=SDIF*ddd;
		//
		primap=(.01*clase[icl])*DDSDIF;
		primat=primap+primae;
		gotoxy(71,6);printf("$ %.2f",primap);
		gotoxy(84,6);printf("$ %.2f",primae);
		gotoxy(97,6);printf("$ %.2f",primat);
		//
		presp=.007*DDSDIF;
		prese=.0025*DDSDIF;
		prest=presp+prese;
		gotoxy(71,14);printf("$ %.2f",presp);
		gotoxy(84,14);printf("$ %.2f",prese);
		gotoxy(97,14);printf("$ %.2f",prest);
		//
		gasp=.0105*DDSDIF;
		gase=.00375*DDSDIF;
		gast=gasp+gase;
		gotoxy(71,16);printf("$ %.2f",gasp);
		gotoxy(84,16);printf("$ %.2f",gase);
		gotoxy(97,16);printf("$ %.2f",gast);
		//
		inp=.0175*DDSDIF;
		ine=.00625*DDSDIF;
		intt=inp+ine;
		gotoxy(71,18);printf("$ %.2f",inp);
		gotoxy(84,18);printf("$ %.2f",ine);
		gotoxy(97,18);printf("$ %.2f",intt);
		//
		gup=.01*DDSDIF;
		gut=gup+gue;
		gotoxy(71,20);printf("$ %.2f",gup);
		gotoxy(84,20);printf("$ %.2f",gue);
		gotoxy(97,20);printf("$ %.2f",gut);
		//
		retip=.02*DDSDIF;
		retit=retip+retie;
		gotoxy(71,22);printf("$ %.2f",retip);
		gotoxy(84,22);printf("$ %.2f",retie);
		gotoxy(97,22);printf("$ %.2f",retit);
		//
		cesap=(.01*cotizacion[zcoti])*DDSDIF;
		cesae=.01125*DDSDIF;
		cesat=cesap+cesae;
		gotoxy(71,24);printf("$ %.2f",cesap);
		gotoxy(84,24);printf("$ %.2f",cesae);
		gotoxy(97,24);printf("$ %.2f",cesat);
		//
		fonp=.05*DDSDIF;
		font=fonp+fone;
		gotoxy(71,26);printf("$ %.2f",fonp);
		gotoxy(84,26);printf("$ %.2f",fone);
		gotoxy(97,26);printf("$ %.2f",font);
		//
		float coutafp,coutafe,coutaft,coutaap,coutaae,coutaat,TTe,TTp,TTt;
		coutafp=0;coutafe=0;coutaft=0;coutaap=0;coutaae=0;coutaat=0;TTe=0;TTp=0;
		//
		exx=SDIF-tUMA;
		coutafp=.2040*ddd*UMA;
		coutaft=coutafp+coutafe;
		gotoxy(71,10);printf("$ %.2f",coutafp);
		gotoxy(84,10);printf("$ %.2f",coutafe);
		gotoxy(97,10);printf("$ %.2f",coutaft);
		//
		coutaap=.0110*exx;
		coutaae=.0040*exx;
		coutaat=coutaap+coutaae;
		gotoxy(71,12);printf("$ %.2f",coutaap);
		gotoxy(84,12);printf("$ %.2f",coutaae);
		gotoxy(97,12);printf("$ %.2f",coutaat);
		//
		TTe=primae+prese+gase+ine+gue+retie+cesae+fone+coutafe+coutaae;
		TTp=primap+presp+gasp+inp+gup+retip+cesap+fonp+coutafp+coutaap;
		TTt=primat+prest+gast+intt+gut+retit+cesat+font+coutaft+coutaat;
		gotoxy(71,28);printf("$ %.2f",TTp);
		gotoxy(84,28);printf("$ %.2f",TTe);
		gotoxy(97,28);printf("$ %.2f",TTt);
		
		//NOMINA
		float qS=0,PG=0,PE=0;
		//articulo 113
		//quincenal
	float ql3i[]={0.01,368.11,3124.36,5490.76,6382.81,7641.91,15412.81,24292.66,46378.51,61838.11,185514.31};
	float ql3s[]={368.10,3124.35,5490.75,6382.8,7641.9,15412.8,24292.65,46378.5,61838.1,185514.3,100000000000};
	float qc3f[]={0.00,7.05,183.45,441.00,583.65,809.25,2469.15,4557.75,11183.40,16130.55, 58180.35};
	float qe3x[]={1.92,6.40,10.88,16.00,17.92,21.36,23.52,30.00,32.00,34.00};
	

	//articulo 115
		//quincenal
	float qn5i[]={0.01, 872.86, 1309.21, 1713.61, 1745.71, 2193.76, 2327.56, 2632.66, 3071.41, 3510.16, 3642.61};
	float qm5i[]={872.85,1309.20,1713.60,1745.70,2193.75,2327.55,2632.65,3071.40,3510.15,3642.60,10000000000};
	float qc5s[]={200.85, 200.70, 200.70, 193.80, 188.70, 174.75, 160.35, 145.35, 125.10, 107.40, 0.00};
		qS=falso*15;
		gotoxy(120,10);printf("$ %.2f",qS);
		gotoxy(120,12);printf("$ ");scanf("%f",&PG);
		gotoxy(120,14);printf("$ ");scanf("%f",&PE);
		gotoxy(143,10);printf("$ %.2f",TTe/2);
		//isr
		float pe,gr,SS,Bgr,Ex,IM,IC,IP;
	int r,largo,i,j,res=1,in=3;
			SS=qS;
			pe=PE;
			gr=PG;
			Bgr=gr+SS;
			
			for(i=0;res==1;i++){
				if(ql3i[i+1]<=SS&&ql3s[i+1]>=SS){
					res=0;
				}
			}
			res=1;
			Ex=Bgr-ql3i[i];
			
			
			IM=Ex*(qe3x[i]/100);
			
			
			res=1;
			
			IC=IM+qc3f[i];
			
			for(j=0;res==1;j++){
				if(qn5i[j+1]<=SS&&qm5i[j+1]>=SS){
					res=0;
				}
			}
			IP=IC-qc5s[j];
			gotoxy(143,12);printf("$ %.2f",IP);
			float devvv=0,sub=0,tt=0;
			devvv=IP+(TTe/2);
			sub=qS+PE+PG;
			tt=sub-devvv;
			gotoxy(120,18);printf("$ %.2f",sub);
			gotoxy(143,18);printf("$ %.2f",devvv);
			gotoxy(143,20);printf("$ %.2f",tt);
			//fin
		
		gotoxy(0,29);printf("salir[0]");
		scanf("%d",&sal);

    }while (sal != 0);
    system("cls");
}while (sal != 0);
}

	
void presentacion() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    margen(1, 1, 100, 25);
    color(hConsole, 11);
    gotoxy(40, 3);
    printf("COMPUMUNDO S.A");
    color(hConsole, 7);
    gotoxy(5, 6);
    printf("Somos una empresa dedicada a la creaci%cn de programas contables y a la venta de tecnolog%ca", 162, 161);
    gotoxy(25, 7);
    printf("que optimizan la gesti%cn financiera de nuestros clientes.", 162);
    gotoxy(45, 9);
    color(hConsole, 11);
    printf("Visi%cn:", 162);
    color(hConsole, 7);
    gotoxy(5, 11);
    printf("Ser la principal opci%cn para la adquisici%cn de software contable y hardware de calidad, ", 162, 162);
    gotoxy(5, 12);
    printf("ofreciendo soluciones integrales que impulsen el progreso digital y mejoren la eficiencia ");
    gotoxy(35, 13);
    printf(" de nuestros clientes.");
    gotoxy(45, 15);
    color(hConsole, 11);
    printf("Misi%cn:", 162);
    color(hConsole, 7);
    gotoxy(5, 17);
    printf("Facilitar el acceso a herramientas tecnol%cgicas y contables, proporcionando productos y ", 162);
    gotoxy(5, 18);
    printf("servicios de vanguardia que satisfagan las necesidades y expectativas de nuestros clientes. ");
    gotoxy(5, 19);
    printf("Nos esforzamos por ser l%cderes en el mercado, ofreciendo un amplio cat%clogo de software", 161, 160);
    gotoxy(7, 20);
    printf("respaldados por un servicio al cliente excepcional y un compromiso continuo con la ", 130);
    gotoxy(35, 21);
    printf("excelencia y la  innovaci%cn tecnol%cgica.", 162, 162);
    gotoxy(60, 25);
    printf("Presione una tecla para ingresar...");
    getch();
    system("cls");
}


void indi_diario(){
	margen(35, 7, 55, 9);
	gotoxy(40, 8);
	printf("LIBRO DIARIO");
	gotoxy(25, 12);
	printf("Para realizar el registro en el libro diario");
	gotoxy(25, 13);
	printf("1. Presione enter despues de cada paso");
	gotoxy(25, 14);
	printf("2. Ingrese la fecha");
	gotoxy(25, 15);
	printf("3. Ingrese el codigo de la cuenta");
	gotoxy(25, 16);
	printf("4. Indique con 1 o 0 si desea cargar o abonar");
	gotoxy(25, 17);
	printf("5. Indique con 1 0 si desea agregar una cuenta o finalizar el asiento");
	gotoxy(25, 18);
	printf("6. Ingrese el asunto del asiento");
	gotoxy(25, 19);
	printf("7. Presione enter para volver al menu principal");
	continuar();
}

void indi_mayor(){
	margen(35, 7, 55, 9);
	gotoxy(40, 8);
	printf("LIBRO MAYOR");
	
	gotoxy(20, 13);
	printf("1. Ingrese a la opcion 1 del menu de ESQUEMAS DE MAYOR");
	gotoxy(20, 14);
	printf("2. Presione enter para obtener acceso a los distintos esquemas de mayor");
	gotoxy(20, 15);
	printf("3. Ingrese 2 si desea volver al menu principal");
	continuar();
}

void indi_cal(){
	margen(35, 7, 55, 9);
	gotoxy(40, 8);
	printf("CALCULADORAS");
	gotoxy(30, 13);
	printf("1. Para cualquiera de las calculadoras");
	gotoxy(30, 14);
	printf("2. Presione enter para ingresar");
	gotoxy(30, 15);
	printf("3. Ingrese los datos solicitados");
	gotoxy(30, 16);
	printf("4. Presione enter despues de cada accion");
	continuar();
}

void indicaciones() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int opcion;
    do {
        margen(1, 3, 100, 25);
        gotoxy(30, 7);
        printf("A continuacion se muestra el menu de ayuda");
        gotoxy(30, 8);
        printf("Seleccione la opcion en la que desea recibir ayuda");
        gotoxy(30, 10);
        color(hConsole, 11);
        printf("1. Libro Diario");
        gotoxy(30, 11);
        printf("2. Libro Mayor");
        gotoxy(30, 12);
        printf("3. Calculadoras (SDI, ISR, etc)");
        gotoxy(30, 13);
        printf("4. Volver al menu principal");
        color(hConsole, 7);
        gotoxy(30, 21);
        printf("Las opciones no establecidas solo requieren ingresar la opcion");
        gotoxy(30, 22);
        printf("correspondiente del menu y en automatico seran ejecutadas");

        gotoxy(30, 15);
        printf("Opcion: ");
        scanf("%d", &opcion);
        system("cls");
        switch (opcion) {
            case 1:
                margen(1, 3, 100, 25);
                indi_diario();
                break;

            case 2:
                margen(1, 3, 100, 25);
                indi_mayor();
                break;

            case 3:
                margen(1, 3, 100, 25);
                indi_cal();
                break;

            case 4:
                gotoxy(30, 14);
                printf("Volviendo al menu principal");
                break;

            default:
                printf("Opcion no valida. Por favor, seleccione una opción válida.\n");
                break;
        }
    } while (opcion != 4);
}

int main ()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int tipoempresa;
	system("cls"); 
	margen (20,8,85,20);
	margen (10,3,100,25);
 color(hConsole, 11);
	gotoxy(37,10); printf("BIENVENIDO AL PROGRAMA CONTABLE"); Sleep(100);
	gotoxy(42,13); printf(" EMPRESA COMERCIAL"); Sleep(100);
	color(hConsole, 7);
		getch();
		system("cls");
		presentacion();
		int h;
		movimientodeudor=0, movimientoacreedor=0, saldoacreedor=0, saldodeudor=0;
		summovideudor=0, summoviacreedor=0, sumsaldeudor=0, sumsalacreedor=0;
		comercialinicializarcuenta(); 
		for(i=0; i<N;i++)
		{
			for(h=0;h<20;h++)
			{
				comercial[i].debe[h]=0;
				comercial[i].haber[h]=0;
			}
			comercial[i].saldoacreedor=0;
			comercial[i].saldodeudor=0;
		}
		for(i=0;i<N;i++)
		{
			aux[i]=0;
			aux2[i]=0;
		}
		for(i=0;i<N;i++)
		{
			comercial[i].saldoacreedor=0;
			comercial[i].saldodeudor=0;
		}
		ingresadatosdeempresa();
		crearusuario();
		comercialcontrasenia(); 
		getch();
}

void comercialinicializarcuenta(){	
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  //ACTIVO CIRCULANTE  
  color(hConsole, 11);
	strcpy (comercial[0].codigo1,"1");  
	strcpy (comercial[0].cuenta,"ACTIVO");
	strcpy (comercial[1].codigo1,"1.1"); 
	strcpy (comercial[1].cuenta,"ACTIVO CIRCULANTE");
	color(hConsole, 7);
	strcpy (comercial[2].codigo1,"1.1.1");  
	strcpy (comercial[2].cuenta,"Caja");
	strcpy (comercial[3].codigo1,"1.1.2"); 
	strcpy (comercial[3].cuenta,"Bancos");
	strcpy (comercial[4].codigo1,"1.1.3"); 
	strcpy (comercial[4].cuenta,"Inversiones temporales de corto plazo");
	strcpy (comercial[5].codigo1,"1.1.4"); 
	strcpy (comercial[5].cuenta,"Mercancias");
	strcpy (comercial[6].codigo1,"1.1.5"); 
	strcpy (comercial[6].cuenta,"Clientes");
	strcpy (comercial[7].codigo1,"1.1.6"); 
	strcpy (comercial[7].cuenta,"Deudores diversos"); 
	strcpy (comercial[8].codigo1,"1.1.7"); 
	strcpy (comercial[8].cuenta,"Funcionarios y empleados");
	strcpy (comercial[9].codigo1,"1.1.8"); 
	strcpy (comercial[9].cuenta,"Documentos por cobrar corto plazo");
	strcpy (comercial[10].codigo1,"1.1.9"); 
	strcpy (comercial[10].cuenta,"IVA acreditable");
	strcpy (comercial[11].codigo1,"1.1.10"); 
	strcpy (comercial[11].cuenta,"IVA pendiente de acreditar");  
  //ACTIVO NO CIRCULANTE
  color(hConsole, 11);
  strcpy(comercial[12].codigo1, "1.2"); 
  strcpy(comercial[12].cuenta,"ACTIVO NO CIRCULANTE");
  color(hConsole, 7);
  strcpy(comercial[13].codigo1,"1.2.1"); 
  strcpy(comercial[13].cuenta,"Terrenos");
  strcpy(comercial[14].codigo1,"1.2.2"); 
  strcpy(comercial[14].cuenta,"Revaluacion de terrenos");
  strcpy(comercial[15].codigo1,"1.2.3"); 
  strcpy(comercial[15].cuenta,"Edificios o construcciones");    
  strcpy(comercial[16].codigo1,"1.2.4");
  strcpy(comercial[16].cuenta,"Depresion de edificios"); 
  strcpy(comercial[17].codigo1,"1.2.5");
  strcpy(comercial[17].cuenta,"Maquinaria y equipo");
  strcpy(comercial[18].codigo1,"1.2.6");
  strcpy(comercial[18].cuenta,"Mobiliario y equipo de oficina");								
  strcpy(comercial[19].codigo1,"1.2.7"); 
  strcpy(comercial[19].cuenta,"Equipo de computo");							 
  strcpy(comercial[20].codigo1,"1.2.8"); 
  strcpy(comercial[20].cuenta,"Equipo periferico");									
  //HASTA AQUI 
  strcpy(comercial[21].codigo1,"1.2.9");
  strcpy(comercial[21].cuenta,"Equipo de reparto o entrega");
  strcpy(comercial[22].codigo1,"1.2.10"); 
  strcpy(comercial[22].cuenta,"Inversiones temporales a largo plazo");							
  strcpy(comercial[23].codigo1,"1.2.11"); 
  strcpy(comercial[23].cuenta,"Depositos en garantia");
  strcpy(comercial[24].codigo1,"1.2.12"); 
  strcpy(comercial[24].cuenta,"Patentes");
  strcpy(comercial[25].codigo1,"1.2.13"); 
  strcpy(comercial[25].cuenta,"Marcas");
  strcpy(comercial[26].codigo1,"1.2.14"); 
  strcpy(comercial[26].cuenta,"Franquicias");
  strcpy(comercial[27].codigo1,"1.2.15"); 
  strcpy(comercial[27].cuenta,"Acciones y valores");
  strcpy(comercial[28].codigo1,"1.2.16"); 
  strcpy(comercial[28].cuenta,"Obligaciones o bonos");							  
  //OTROS ACTIVOS O DIFERIDO
  color(hConsole, 11);
  strcpy(comercial[29].codigo1,"1.3"); 
  strcpy(comercial[29].cuenta,"ACTIVO DIFERIDO");
  color(hConsole, 7);
  strcpy(comercial[30].codigo1,"1.3.1"); 
  strcpy(comercial[30].cuenta,"Gastos de constitucion");
  strcpy(comercial[31].codigo1,"1.3.2"); 
  strcpy(comercial[31].cuenta,"Gastos de instalacion");
  strcpy(comercial[32].codigo1,"1.3.3"); 
  strcpy(comercial[32].cuenta,"Papeleria y utiles en economia de escala");
  strcpy(comercial[33].codigo1,"1.3.4"); 
  strcpy(comercial[33].cuenta,"Propaganda y publicidad");
  strcpy(comercial[34].codigo1,"1.3.5"); 
  strcpy(comercial[34].cuenta,"Primas de seguro pagados por anticipado");
  strcpy(comercial[35].codigo1,"1.3.6"); 
  strcpy(comercial[35].cuenta,"Anticipos en proveedores");
  strcpy(comercial[36].codigo1,"1.3.7"); 
  strcpy(comercial[36].cuenta,"Rentas pagadas por anticipado");
  strcpy(comercial[37].codigo1,"1.3.8"); 
  strcpy(comercial[37].cuenta,"Intereses pagados por anticipado");

  //PASIVO CIRCULANTE
  color(hConsole, 11);
  strcpy(comercial[38].codigo1,"2"); 
  strcpy(comercial[38].cuenta,"PASIVOS");
  strcpy(comercial[39].codigo1,"2.1"); 
  strcpy(comercial[39].cuenta,"PASIVO CIRCULANTE");
  color(hConsole, 7);
  strcpy(comercial[40].codigo1,"2.1.1"); 
  strcpy(comercial[40].cuenta,"Proveedor");
  strcpy(comercial[41].codigo1,"2.1.2"); 
  strcpy(comercial[41].cuenta,"Acreedores diversos");
  strcpy(comercial[42].codigo1,"2.1.3"); 
  strcpy(comercial[42].cuenta,"Documentos por pagar corto plazo");
  strcpy(comercial[43].codigo1,"2.1.4"); 
  strcpy(comercial[43].cuenta,"IVA trasladado");								
  strcpy(comercial[44].codigo1,"2.1.5"); 
  strcpy(comercial[44].cuenta,"IVA por trasladar");
  strcpy(comercial[45].codigo1,"2.1.6"); 
  strcpy(comercial[45].cuenta,"Impuestos pendientes de pago");
  strcpy(comercial[46].codigo1,"2.1.7"); 
  strcpy(comercial[46].cuenta,"Retenciones a terceros");
  strcpy(comercial[47].codigo1,"2.1.8"); 
  strcpy(comercial[47].cuenta,"Anticipo  de clientes");
  //PASIVOS NO CIRCULANTES
  color(hConsole, 11);
  strcpy(comercial[48].codigo1,"2.2"); 
  strcpy(comercial[48].cuenta,"PASIVO NO CIRCULANTE");
  color(hConsole, 7);
  strcpy(comercial[49].codigo1,"2.2.1"); 
  strcpy(comercial[49].cuenta,"Deudas a largo plazo");
  strcpy(comercial[50].codigo1,"2.2.2"); 
  strcpy(comercial[50].cuenta,"Arrendamientos financieros a largo plazo");
  strcpy(comercial[51].codigo1,"2.2.3"); 
  strcpy(comercial[51].cuenta,"Obligaciones de pensiones y jubilaciones");
  strcpy(comercial[52].codigo1,"2.2.4"); 
  strcpy(comercial[52].cuenta,"Intereses devengados entre entidades relacionadas");
  //OTROS PASIVOS O DIFERIDOS
  color(hConsole, 11);
  strcpy(comercial[53].codigo1,"2.3"); 
  strcpy(comercial[53].cuenta,"OTROS PASIVOS O DIFERIDO");
  color(hConsole, 7);
  strcpy(comercial[54].codigo1,"2.3.1"); 
  strcpy(comercial[54].cuenta,"Garantias y responsabilidades contingentes");
  strcpy(comercial[55].codigo1, "2.3.2"); 
  strcpy(comercial[55].cuenta,"Depositos de clientes");
  strcpy(comercial[56].codigo1, "2.3.3"); 
  strcpy(comercial[56].cuenta,"Reservas para reestructuracion");
  strcpy(comercial[57].codigo1, "2.3.4"); 
  strcpy(comercial[57].cuenta,"Hipotecas por pagar");
  strcpy(comercial[58].codigo1, "2.3.5"); 
  strcpy(comercial[58].cuenta,"Arrendamientos financieros");
  strcpy(comercial[59].codigo1, "2.3.6"); 
  strcpy(comercial[59].cuenta,"Intereses por pagar");
  
  //CAPITAL CONTABLE
  color(hConsole, 11);
  strcpy(comercial[60].codigo1,"3"); 
  strcpy(comercial[60].cuenta,"CAPITAL CONTABLE");
  color(hConsole, 7);
  strcpy(comercial[61].codigo1,"3.1"); 
  strcpy(comercial[61].cuenta,"Capital social");
  strcpy(comercial[62].codigo1,"3.2"); 
  strcpy(comercial[62].cuenta,"Patrimonio");
  strcpy(comercial[63].codigo1,"3.3"); 
  strcpy(comercial[63].cuenta,"Reserva legal");
  strcpy(comercial[64].codigo1,"3.4"); 
  strcpy(comercial[64].cuenta,"Resultado de ejercicios anteriores");
  strcpy(comercial[65].codigo1,"3.5"); 
  strcpy(comercial[65].cuenta,"Resultado del ejercicio");
  
  //INGRESOS
  color(hConsole, 11);
  strcpy(comercial[66].codigo1,"4"); 
  strcpy(comercial[66].cuenta,"INGRESOS");
  color(hConsole, 7);
  strcpy(comercial[67].codigo1,"4.1"); 
  strcpy(comercial[67].cuenta,"Ventas ");
  strcpy(comercial[68].codigo1,"4.2"); 
  strcpy(comercial[68].cuenta,"Devoluciones, descuentos o bonificaiones sobre ventas");
  strcpy(comercial[69].codigo1,"4.3"); 
  strcpy(comercial[69].cuenta,"Otros ingresos");
  //COSTOS
  color(hConsole, 11);
  strcpy(comercial[70].codigo1,"5"); 
  strcpy(comercial[70].cuenta,"COSTOS");
  color(hConsole, 7);
  strcpy(comercial[71].codigo1,"5.1"); 
  strcpy(comercial[71].cuenta,"Costos de venta y/o servicio");
  strcpy(comercial[72].codigo1,"5.2"); 
  strcpy(comercial[72].cuenta,"Compras");
  strcpy(comercial[73].codigo1,"5.3"); 
  strcpy(comercial[73].cuenta,"Devoluciones, descuentos o bonificaciones sobre compras");
  strcpy(comercial[74].codigo1,"5.4"); 
  strcpy(comercial[74].cuenta,"Otras cuentas de costos");
  strcpy(comercial[75].codigo1,"5.5"); 
  strcpy(comercial[75].cuenta,"Costos de ventas MOD");
  //GASTOS
  color(hConsole, 11);
  strcpy(comercial[76].codigo1,"6"); 
  strcpy(comercial[76].cuenta,"GASTOS");
  color(hConsole, 7);
  strcpy(comercial[77].codigo1,"6.1"); 
  strcpy(comercial[77].cuenta,"Gastos generales");
  strcpy(comercial[78].codigo1,"6.2"); 
  strcpy(comercial[78].cuenta,"Gastos de ventas");
  strcpy(comercial[79].codigo1,"6.3"); 
  strcpy(comercial[79].cuenta,"Gastos de administracion");
  strcpy(comercial[80].codigo1,"6.4"); 
  strcpy(comercial[80].cuenta,"Gastos de compras");
  strcpy(comercial[81].codigo1,"6.5");
  strcpy(comercial[81].cuenta,"Mano de obra directa");
  strcpy(comercial[82].codigo1,"6.6"); 
  strcpy(comercial[82].cuenta,"Facilidades administrativas fiscales");
  strcpy(comercial[83].codigo1,"6.7"); 
  strcpy(comercial[83].cuenta,"Impuestos sobre la renta");
  strcpy(comercial[84].codigo1,"6.8"); 
  strcpy(comercial[84].cuenta,"Gastos de fabricación");   
  strcpy(comercial[85].codigo1,"6.9"); 
  strcpy(comercial[85].cuenta,"Amortización contable");    
  //RESULTADOS
  color(hConsole, 11);
  strcpy(comercial[86].codigo1,"7");
  strcpy(comercial[86].cuenta,"RESULTADO INTEGRAL DE FINANCIAMIENTO");
  color(hConsole, 7);
  strcpy(comercial[87].codigo1,"7.1"); 
  strcpy(comercial[87].cuenta,"Gastos financieros");
  strcpy(comercial[88].codigo1,"7.2"); 
  strcpy(comercial[88].cuenta,"Productos financieros");
  strcpy(comercial[89].codigo1,"7.3"); 
  strcpy(comercial[89].cuenta,"Otros gastos");   
  strcpy(comercial[90].codigo1,"7.4"); 
  strcpy(comercial[90].cuenta,"Otros productos");
  strcpy(comercial[91].codigo1,"7.5"); 
  strcpy(comercial[91].cuenta,"Inventario inicial");
}

int margen(int a, int b, int c, int d) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    color(hConsole, 13);
    int j, k, i;
    j = a;
    gotoxy(a - 1, b);
    printf("%c", 201);
    gotoxy(a - 1, d);
    printf("%c", 200);
    for (a; a <= c; a++) {
        gotoxy(a, b);
        printf("%c", 205);
        gotoxy(a, d);
        printf("%c", 205);
    }
    gotoxy(a, b);
    printf("%c", 187);
    gotoxy(a, d);
    printf("%c", 188);
    k = b + 1;
    for (k; k <= (d - 1); k++) {
        gotoxy(j - 1, k);
        printf("%c", 186);
        gotoxy(a, k);
        printf("%c", 186);
    }
    color(hConsole, 7);
}

void crearusuario(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 	margen (20,18,85,28);
 	color(hConsole, 11);
	 	gotoxy (45,20); printf ("CREE USUARIO CONTADOR ");
		gotoxy (25,23); printf ("USUARIO: ");
		color(hConsole, 7);
		gets (usuariocont);
	 	gotoxy (25,25); printf ("CONTRASE%cA: ", 165);
	    gets (passconta);
}

void comercialcontrasenia(){
  int i, intentos=0, op;
  char password[4];
  char tecla;

  mostrarempresa();
  do{
    system ("Cls");
    
    margen (20,8,85,20);
    margen (10,4,100,25);
    
    gotoxy (31,12); printf ("Password:");
    mostrarempresa();
    i=0;
    do{
      gotoxy (43+i,12);
      password[i]=getch();
      gotoxy (43+i,12);printf("*");

      i++;
    }while (password[i-1] != 13);
    password[i-1]= '\0';

//---------------------------------------------CONTADOR--------------------------------------------------------------
    if ((strcmp(password, passconta) == 0)){
      system("cls");
      mostrarempresa();
      margen (20,8,85,20);
      margen (10,4,100,25);
      
      gotoxy (35,12); printf ("%cBIENVENIDO%c",173,33);
      gotoxy (30,15); printf ("USUARIO:  "); 
	  puts (usuariocont);
     continuar();
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	  do{
	  	      system ("cls"); 
		      mostrarempresa();
		      int a=35;
		    margen(25, 5, 85, 25);
		    margen(20, 4, 90, 26);
		    color(hConsole, 11);
			  gotoxy(a,7); printf ("CATALOGO DE CUENTAS.................[1]"); 
			  gotoxy(a,8); printf ("CREAR ASIENTO CONTABLE..............[2]"); 
			  gotoxy(a,9); printf ("ESQUEMAS DE MAYOR...................[3]");
			  gotoxy(a,10); printf ("BALANZA DE COMPROBACION.............[4]");  
			  gotoxy(a,11); printf ("BALANCE GENERAL.....................[5]"); 
			  gotoxy(a,12); printf ("ALMACEN.............................[6]"); 
			  gotoxy(a,13); printf ("ESTADO DE RESULTADOS................[7]"); 
			  gotoxy(a,14); printf ("TABLA DE AMORTIZACION DE CREDITOS...[8]");
			  gotoxy(a,15); printf ("TABLA DE DEPRECIACION DE ACTIVOS....[9]");
			  gotoxy(a,16); printf ("CALCULADORA DEL ISR.................[10]");
			  gotoxy(a,17); printf ("CALCULADORA DE SDI..................[11]");
			  gotoxy(a,18); printf ("CAMBIAR DE USUARIO..................[12]");
			  gotoxy(a,19); printf ("CALCULADORA CUOTA OBRERO-PATRONAL...[13]");
			  gotoxy(a,20); printf ("MANUAL DE AYUDA.....................[14]");
			  gotoxy(a,21); printf ("SALIR...............................[15]");
		      gotoxy(a,23); printf ("SELECCIONE UNA OPCION [1-13]: [    ]\b\b");
		      color(hConsole, 7);
		      scanf ("%d%*c",&op);
			   
		      system ("cls"); 
			   mostrarempresa(); 
					  switch (op){
				      	case 1:
						  gotoxy(15,4); printf (" CATALOGO DE CUENTAS");
						  cuentas(); 
				      	break;
				      	case 2: 
				          gotoxy(15,4); printf (" RAYADO DIARIO");
				          comercialrayadodiario();
				          ayuda++;
				      	break; 
						case 3:
				      		gotoxy(15,4); printf(" T DE MAYOR  /  ESQUEMAS DE MAYOR");
				      		 comercialesquemasmayor();
				      	break;
						case 4: 
				      	   gotoxy(15,4); printf (" BALANZA DE COMPROBACION");
				      	   comercialbalanza();
				      	break;
				      	case 5:
				      		gotoxy(15,4); printf (" BALANCE GENERAL");
				      	  comercialbalancegeneral();
				      	break;
				      	case 6: 
				      	gotoxy(15,4); printf (" TARJETAS DE ALMACEN");
				      	  comercialtargetasdealmacen();
				      	break;
				      	case 7:
				      		gotoxy(15,4); printf (" ESTADO DE RESULTADOS");
				      		comercialestadoderesultados();
				      	break;
				      	case 8:
				      		tabladeA();
				      	break;
				      	case 9:
				      		tabladeDep();
				      		break;
				      	case 10:
				      		calcular_ISR();
				      		break;
				      	case 11:
				      		calcularSDI();
				      		break;
				      	case 12:
						  comercialcontrasenia();
				      	break; 
				      	case 13:
				      		nomina();
				      		break;
				      	case 14:
				      		indicaciones();
				      	case 15:
				      		gotoxy(30, 15); printf ("SALIENDO....");
						   	Sleep(800);
						   	system("cls");
				      		break;
						default:
						   gotoxy (40,24); printf ("ERORR, LA OPCION NO EXISTE"); 
				      	break; 
					  }
					  getch();     
	   }while(op!=15);
      
      break;
    } 
		
	//---------------------------------------AUXILIAAAR--------------------------------------------------------
	if((strcmp(password, passauxi) == 0)){
      system("cls");
      mostrarempresa();
      
	  gotoxy (31,12); printf ("%cBIENVENIDO%c",173,33);
      gotoxy (31,13); printf ("USUARIO:  ");
	  puts (usuarioaux);
	  getch();
      
	  do{
	  	      system ("cls"); 
		      mostrarempresa();
		      margen(1, 1, 100, 25);
			  gotoxy(15,5); printf ("1. MOSTRAR CATALOGO DE CUENTAS"); 
			  gotoxy(15,6); printf ("2. CREAR ASIENTO CONTABLE"); 
			  gotoxy(15,7); printf ("3. T DE MAYOR  /  ESQUEMAS DE MAYOR");
			  gotoxy(15,8); printf ("4. ALMACEN"); 
			  gotoxy(15,9); printf ("5. SALIR"); 
			  gotoxy(15,11); printf ("6. CAMBIAR DE USUARIO");  
		      gotoxy(15,15); printf ("Ingresa una opcion [1-7]:  ");
		      scanf ("%d%*c",&op); 
		      
		       system ("cls"); 
			   mostrarempresa(); 
					  switch (op){
				      	case 1:
						  gotoxy(15,4); printf (" CATALOGO DE CUENTAS");
						  comercialmostrarcuentas(); 
				      	break;
				      	case 2: 
				          gotoxy(15,4); printf (" ASIENTO CONTABLE");
				          comercialrayadodiario();
				          ayuda++;
				      	break;
						case 3:
				      		gotoxy(15,4); printf("3 T DE MAYOR  /  ESQUEMAS DE MAYOR");
				      		 comercialesquemasmayor();
				      	break;
						case 4: 
						gotoxy(15,4); printf ("4. TARJETAS DE ALMACEN");
				      	    comercialtargetasdealmacen();
				      	break;
				      	case 5:
				      	  gotoxy (20,24); printf ("ESC para salir. ");
				      	break;
				      	case 6:
				      	   comercialcontrasenia(); 
				      	break;
				      	default:
						   gotoxy (40,24); printf ("ERORR, LA OPCION NO EXISTE"); 
				      	break; 
					  }
					  getch();     
	   }while(op!=5);
      
      break;
	}else{
      intentos++;
      system("cls");
    }
  }while (intentos < 3);

  if (intentos == 3){
   mostrarempresa();
    system("cls");
    gotoxy (30,12); printf("Error de acceso");
    gotoxy (25,14); printf("Pulse una tecla para salir [ ]\b\b");
    getch();
  } 	
}
void ingresadatosdeempresa(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 	system ("cls"); 
 	margen(15,5,90,15);
 	margen(10,3,95,29);
   color(hConsole, 11);
 	gotoxy (41,7); printf ("INGRESE LOS DATOS DE LA EMPRESA");Sleep(100);
 	gotoxy (30,9); printf ("NOMBRE DE LA EMPRESA: ");Sleep(100);
 	color(hConsole, 7);
    gets (empresa);
    color(hConsole, 11);
	gotoxy (30,12);printf ("FECHA DE INICIO OPERACIONES: ");Sleep(100);
	color(hConsole, 7);
	gets (fecha);

	
 }
 
void continuar(){
	gotoxy(60, 29);
	printf("Presione una tecla para continuar...");
	getch();
	system("cls");
}
void mostrarempresa(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 	color(hConsole, 11);
 	 	gotoxy (40,1); printf ("NOMBRE DE LA EMPRESA: ");puts (empresa);
 		gotoxy (40,2); printf ("FECHA DE INICIO OPERACIONES: ");puts (fecha);
 		color(hConsole, 7);
  	
 }
 
void comercialmostrarcuentas(){
	margen(1, 4, 100, 25);
	int i; 
	for(i=0;i<11;i++){
	    gotoxy (5,5+i); puts(comercial[i].codigo1);
		gotoxy (15,5+i); puts(comercial[i].cuenta);
	}
	continuar();
	margen(1, 4, 100, 25);
	mostrarempresa(); 
	for(i=12;i<29;i++){
	    gotoxy (5,5+i-12); puts(comercial[i].codigo1);
		gotoxy (15,5+i-12); puts(comercial[i].cuenta);
	}
	continuar();
	margen(1, 4, 100, 25);
	mostrarempresa(); 
	for(i=29;i<38;i++){
	    gotoxy (5,5+i-29); puts(comercial[i].codigo1);
		gotoxy (15,5+i-29); puts(comercial[i].cuenta);
	}
	continuar();
	margen(1, 4, 100, 25);
	mostrarempresa(); 
	for(i=38;i<48;i++){
	    gotoxy (5,5+i-38); puts(comercial[i].codigo1);
		gotoxy (15,5+i-38); puts(comercial[i].cuenta);
	}
	continuar();
	margen(1, 4, 100, 25);
	mostrarempresa(); 
	for(i=48;i<53;i++){
	    gotoxy (5,5+i-48); puts(comercial[i].codigo1);
		gotoxy (15,5+i-48); puts(comercial[i].cuenta);
	}
	continuar();
	margen(1, 4, 100, 25);
	mostrarempresa(); 
	for(i=53;i<60;i++){
	    gotoxy (5,5+i-53); puts(comercial[i].codigo1);
		gotoxy (15,5+i-53); puts(comercial[i].cuenta);
	}
	continuar();
	margen(1, 4, 100, 25);
	mostrarempresa(); 
	for(i=60;i<66;i++){
	    gotoxy (5,5+i-60); puts(comercial[i].codigo1);
		gotoxy (15,5+i-60); puts(comercial[i].cuenta);
	}
	continuar();
	margen(1, 4, 100, 25);
	mostrarempresa(); 
	for(i=66;i<70;i++){
	    gotoxy (5,5+i-66); puts(comercial[i].codigo1);
		gotoxy (15,5+i-66); puts(comercial[i].cuenta);
	}
	continuar();
	margen(1, 4, 100, 25);
	mostrarempresa(); 
	for(i=70;i<76;i++){
	    gotoxy (5,5+i-70); puts(comercial[i].codigo1);
		gotoxy (15,5+i-70); puts(comercial[i].cuenta);
	}
	continuar();
	margen(1, 4, 100, 25);
	mostrarempresa(); 
	for(i=76;i<86;i++){
	    gotoxy (5,5+i-76); puts(comercial[i].codigo1);
		gotoxy (15,5+i-76); puts(comercial[i].cuenta);
	}
	continuar();
	margen(1, 4, 100, 25);
	mostrarempresa(); 
	for(i=86;i<91;i++){
	    gotoxy (5,5+i-86); puts(comercial[i].codigo1);
		gotoxy (15,5+i-86); puts(comercial[i].cuenta);
	}
}

void comercialmostrarcuentas22(){
	int a; 
	for(a=0;a<N;a++){
	    gotoxy (5,10+a); puts(comercial[a].codigo1);
		gotoxy (15,10+a); puts(comercial[a].cuenta);
	}
}

void comercialrayadodiario(){
    char subcta [40];
	char fecha[20]; 
	char cuenta3[20]; 
	char concepto[50]; 
	char codi[60];
	char Codi[60],sub[20];
	int i=0, pos, band=0,op2, op3,j, esp=0,op;
	float debe=0, haber=0, sumadebe=0, sumahaber=0, parcial,pre=0;
	float total;
	int pir;  
	int x,k,v[10],m;
	for (x=0;x<10;x++){
		v[x] = 0;
	}
	system("cls"); 
	mostrarempresa();
	margen(5,5,95,29);
	margen(5,5,95,29);
	margen(5,5,95,29);
	  
	gotoxy(8,7); printf ("FECHA");
	gotoxy(43,7); printf ("CONCEPTO");
	gotoxy(85,7); printf ("HABER");
	gotoxy(70,7); printf ("DEBE");
	gotoxy(20,7); printf ("CODIGO");
	margen(5,5,15,29);
	margen(5,5,30,29);
	margen(5,5,95,29);
	margen(5,5,80,29);
	margen(5,5,67,29);
	gotoxy(6,11); gets(fecha);
	k=0;
	do{
		gotoxy(17, (11 + i));
		gets(codi);
        band=0;
		for(j=0;j<N;j++){
				if ((strcmp(codi,comercial[j].codigo1 ) == 0) ){
			     band=1;
			     pos=j;
			     v[k] = pos;
			     k++;
				}
		}
		if (band==1){
			gotoxy(32,(11+i)); puts (comercial[pos].cuenta);
			if ((strcmp(codi, comercial[91].codigo1) == 0) || (strcmp(codi, comercial[5].codigo1) == 0) || (strcmp(codi, comercial[72].codigo1) == 0)) {
				total=0;
				gotoxy(97,21);printf("NOMBRE MERCANCIA: ");
				gets(sub);
				gotoxy(97,23);printf("CUANTAS PIEZAS: ");
				scanf("%d",&pir);
				gotoxy(97,25);printf("PRECIO UNITARIO:$ ");
				scanf("%f",&pre);
				gotoxy(97,27);printf("CARGAR [1]");
				gotoxy(97,28);printf("ABONAR [0]");
				gotoxy(97,30);printf("QUE DESEAS REALIZAR [  ]\b\b");
				scanf("%d",&op);
				getch();
				borar();
			    if(op==1)
				{
					total=pir*pre;
					if(p==0){
						strcpy(subcuenta[pa],sub);
						piezas[pa]=pir;
						precio[pa]=pre;
						merdebe[pa]=total;
						merhaber[pa]=0;
						pa++;
						p++;
						y++;
					}
					else{
						if(strcmp(sub,subcuenta[0])==0){
							piezas[pa]=pir;
							precio[pa]=pre;
							merdebe[pa]=total;
							merhaber[pa]=0;
							pa++;
						}
						else{
							if(pe==0){
								strcpy(subcuenta1[pe],sub);
								piezas1[pe]=pir;
								precio1[pe]=pre;
								merdebe1[pe]=total;
								merhaber1[pe]=0;
								pe++;
								p++;
							}
							else{
								if(strcmp(sub,subcuenta1[0])==0){
									piezas1[pe]=pir;
									precio1[pe]=pre;
									merdebe1[pe]=total;
									merhaber1[pe]=0;
									pe++;
								}
								else{
									if(pi==0){
										strcpy(subcuenta2[pi],sub);
										piezas2[pi]=pir;
										precio2[pi]=pre;
										merdebe2[pi]=total;
										merhaber2[pi]=0;
										pi++;
										p++;
									}
									else{
										if(strcmp(sub,subcuenta2[0])==0){
											piezas2[pi]=pir;
											precio2[pi]=pre;
											merdebe2[pi]=total;
											merhaber2[pi]=0;
											pi++;
										}
										else{
											if(po==0){
												strcpy(subcuenta3[po],sub);
												piezas3[po]=pir;
												precio3[po]=pre;
												merdebe3[po]=total;
												merhaber3[po]=0;
												po++;
												p++;
											}
											else{
												if(strcmp(sub,subcuenta3[0])==0){
													piezas3[po]=pir;
													precio3[po]=pre;
													merdebe3[po]=total;
													merhaber3[po]=0;
													po++;
												}
												else{
													if(pu==0){
														strcpy(subcuenta4[pu],sub);
														piezas4[pu]=pir;
														precio4[pu]=pre;
														merdebe4[pu]=total;
														merhaber4[pu]=0;
														pu++;
														p++;
													}
													else{
														if(strcmp(sub,subcuenta4[0])==0){
															piezas4[pu]=pir;
															precio4[pu]=pre;
															merdebe4[pu]=total;
															merhaber4[pu]=0;
															pu++;
														}
													}
												}
											}
										}
									}
								}	
							}
						}
					}
					gotoxy(70,(11+i-1)); printf ("$ ");printf("%.2f",total);
					comercial[pos].debe[aux[pos]]+=total;
					sumadebe=sumadebe+total;
					aux[pos]++;
					gotoxy(85,(11+i-1)); printf ("$ ");printf("0");
					comercial[pos].haber[aux2[pos]]+=0;
					sumahaber=sumahaber+0;
					aux2[pos]++;
					if (ayuda==0){
						inventarioinicial=merdebe[0]+merdebe1[0]+merdebe2[0]+merdebe3[0]+merdebe4[0];
					}
		     	}
				else
				{
					/*if(n>0)
					{
						pre=medi;
						gotoxy(115,25);printf("%.2f",pre);
					}
					if(n1>0)
					{
						pre=medi1;
						gotoxy(115,25);printf("%.2f",pre);
					}
					if(n2>0)
					{
						pre=medi2;
						gotoxy(115,25);printf("%.2f",pre);
					}
					if(n3>0)
					{
						pre=medi3;
						gotoxy(115,25);printf("%.2f",pre);
					}
					if(n4>0)
					{
						pre=medi4;
						gotoxy(115,25);printf("%.2f",pre);
					}*/
					
					total=0;
					total=pir*pre;
					if(y==0){
						gotoxy(96,5);printf("NO CUENTAS CON SUFICIENTES MERCANCIAS");
						gotoxy(96,6);printf("INGRESA NUEVAMENTE");
						gotoxy(17,11+i);printf("      ");
						gotoxy(32,11+i);printf("            ");
					    getch(); 
					    borar();
					    i=i-2;
					}
					else{
						if(strcmp(sub,subcuenta[0])==0){
							piezas[pa]=pir;
							precio[pa]=pre;
							merdebe[pa]=0;
							merhaber[pa]=total;
							pa++;
						}
						if(strcmp(sub,subcuenta1[0])==0){
							piezas1[pe]=pir;
							precio1[pe]=pre;
							merdebe1[pe]=0;
							merhaber1[pe]=total;
							pe++;
						}
						if(strcmp(sub,subcuenta2[0])==0){
							piezas2[pi]=pir;
							precio2[pi]=pre;
							merdebe2[pi]=0;
							merhaber2[pi]=total;
							pi++;
						}
						if(strcmp(sub,subcuenta3[0])==0){
							piezas3[po]=pir;
							precio3[po]=pre;
							merdebe3[po]=0;
							merhaber3[po]=total;
							po++;
						}
						if(strcmp(sub,subcuenta4[0])==0){
							piezas4[pu]=pir;
							precio4[pu]=pre;
							merdebe4[pu]=0;
							merhaber4[pu]=total;
							pu++;
						}
						gotoxy(70,(11+i)); printf ("$ ");printf("0");
						comercial[pos].debe[aux[pos]]+=0;
						sumadebe+=0;
						aux[pos]++;
						
						gotoxy(85,(11+i)); printf ("$ ");printf("%.2f",total);
						comercial[pos].haber[aux2[pos]]+=total;
						sumahaber+=total;
						aux2[pos]++;
					
					}
				}
				i=i+1;
			}
			else
			{
					gotoxy(97,27);printf("CARGAR [1]");
					gotoxy(97,28);printf("ABONAR [0]");
					gotoxy(97,30);printf("QUE DESEAS REALIZAR [ ]\b\b");
					scanf("%d",&op);
				
				borar();
				if(op==1)
				{
						gotoxy(70,(11+i)); printf ("$ "); scanf ("%f",&debe);
						comercial[pos].debe[aux[pos]]+=debe;
						sumadebe=sumadebe+debe;
						aux[pos]++;
						gotoxy(85,(11+i)); printf ("$0");
						comercial[pos].haber[aux2[pos]]+=0;
						sumahaber=sumahaber+0;
						aux2[pos]++;
				}
				else
				{
						gotoxy(70,(11+i)); printf ("$ ");printf("0");
						comercial[pos].debe[aux[pos]]+=0;
						sumadebe=sumadebe+0;
						aux[pos]++;
						gotoxy(85,(11+i)); printf ("$ "); scanf ("%f",&haber);
						comercial[pos].haber[aux2[pos]]+=haber;
						sumahaber=sumahaber+haber;
						aux2[pos]++;
		    
				}
				i=i+2;	
		    }
			
			
				gotoxy(101,15);printf ("¿QUIERES OTRA CUENTA");	
				gotoxy(103,17); printf ("SI[1] NO[0]: ");
				scanf("%d%*c",&op2);
		}
		else{
			
			gotoxy(96,5);printf ("ERROR, LA CUENTA NO EXISTE");
			gotoxy(96,6);printf("INGRESA NUEVAMENTE");
			gotoxy(17,11+i);printf("      ");
		
		    getch(); 
		    borar();
		}
			
	}while(op2!=0);
		
 	gotoxy(30, 23);
printf("                                               ");
gotoxy(33, 29);
printf("SUMAS TOTALES: ");
gotoxy(70, 29);
printf("$ %.2f", sumadebe);
gotoxy(85, 29);
printf("$ %.2f", sumahaber);

if (sumadebe == sumahaber)
{
    gotoxy(30, 25);
    printf("                                         ");
    gotoxy(32, 47);
    printf("CONCEPTO DEL ASIENTO");
    gotoxy(32, 48);
    gets(concepto);
} else
{
    gotoxy(96, 6);
    printf("ERROR, NO HAY PARTIDA DOBLE.");
    gotoxy(96, 7);
    printf("INTENTE NUEVAMENTE");
    getch();  // Mueve la llamada getch() aquí, después de mostrar el mensaje de error
    return;
}

}


void comercialesquemasmayor(){
	int a, b, c, band=0, d,e,f, j=0, pos,opcion;
	char cuentacompara[30]; 
	char codigocompara[30]; 
	system("cls");
	do{
		    system("cls");
		    mostrarempresa();
		    margen(1, 3, 100, 25);
		    gotoxy(17,6);printf ("ESQUEMAS DE MAYOR:");
		    gotoxy(17,7);printf ("MENU");
			gotoxy(17,9);printf ("1.-General");
		    gotoxy(17,10);printf ("2.-Salir");
		    gotoxy(17,12);printf ("Elige una opcion: ");
		    scanf  ("%d%*c",&opcion);
		     
		    system("cls");
		    
		    switch (opcion){
		    	case 1:
		    		system("cls");
    mostrarempresa();
	for(i=0; i<N; i++ ){
		movimientoacreedor=0;
		movimientodeudor=0; 
		
		if (comercial[i].debe[0]>0 || comercial[i].haber[0]>0){
			system("cls");
		  mostrarempresa();
		   gotoxy (10,3); puts(comercial[i].cuenta);	
			
	
			for(f=0;f<20;f++){
				if(comercial[i].debe[f]>0){
			       movimientodeudor+=comercial[i].debe[f];
				    gotoxy(6,14); printf("%.2f",movimientodeudor);	   
				}
				if(comercial[i].haber[f]>0){
			       movimientoacreedor+=comercial[i].haber[f];	
				    gotoxy(18,14); printf("%.2f",movimientoacreedor);
				}
			}
			
			
						
			for(c=0;c<20;c++){
				if(comercial[i].debe[c]>0){
				   gotoxy(6,5+c); printf("%.2f",comercial[i].debe[c]);
				}  
				if(comercial[i].haber[c]>0){
				  gotoxy(18,5+c); printf("%.2f",comercial[i].haber[c]);
				}
				
			}
			
		
			   for(b=0;b<30;b++){
				  gotoxy(3+b,4); printf ("%c",196);
				}
				for(a=0;a<12;a++){
				  	gotoxy(16,5+a);printf ("%c",179);
				}
			   for(d=0;d<30;d++){
				  gotoxy(3+d,13); printf ("%c",196);
				}
				for(e=0;e<30;e++){
				  gotoxy(3+e,15); printf ("%c",196);
				}
					
			gotoxy(2,14); printf("MD");
			gotoxy(36,14); printf("MA");
			gotoxy(2,16); printf("SD");
			gotoxy(36,16); printf("SA");
		    
			if(movimientoacreedor>movimientodeudor){
		        saldoacreedor=movimientoacreedor-movimientodeudor;
		       gotoxy(18,16);printf("%.2f",saldoacreedor); 
		        
			}else if(movimientodeudor>movimientoacreedor){
			  saldodeudor=	movimientodeudor-movimientoacreedor;
			  gotoxy(6,16); printf("%.2f",saldodeudor);
			}else if(movimientodeudor==movimientoacreedor){
				 saldoacreedor=0;
				 saldodeudor=0;
				 gotoxy(18,16);printf("%.2f",saldoacreedor);
				 gotoxy(6,16); printf("%.2f",saldodeudor);
			}
			getch();
		}
	
	}
				break; 
		    	case 3:
		    		system("cls");
		    		mostrarempresa();
		    		gotoxy(45,5); printf ("cuenta: "); 
		    		gets(cuentacompara); 
		    		gets (codigocompara);
		
		    	for(j=0;j<N;j++){
		    		printf("\n");
						if ((strcmp(comercial[j].cuenta,cuentacompara) == 0) || (strcmp(comercial[j].codigo1,codigocompara) == 0)){
					     band=1;
					     pos=j;
					     getch();
						}
				}
		    
		    if (band==1){
				movimientoacreedor=0;
				movimientodeudor=0; 
				   gotoxy (10,3); puts(comercial[pos].cuenta);	
					
					for(f=0;f<20;f++){
						if(comercial[pos].debe[f]>0){
					       movimientodeudor+=comercial[pos].debe[f];
							gotoxy(6,14); printf("%.2f",movimientodeudor);	   
						}
						if(comercial[pos].haber[f]>0){
					       movimientoacreedor+=comercial[pos].haber[f];	
						    gotoxy(18,14); printf("%.2f",movimientoacreedor);
						}
					}
								
					for(c=0;c<20;c++){
						if(comercial[pos].debe[c]>0){
						   gotoxy(6,5+c); printf("%.2f",comercial[pos].debe[c]);
						}  
						if(comercial[pos].haber[c]>0){
						  gotoxy(18,5+c); printf("%.2f",comercial[pos].haber[c]);
						}
		
		
					}
			
					for(b=0;b<30;b++){
					  gotoxy(3+b,4); printf ("%c",196);
					}
					for(a=0;a<12;a++){
					  	gotoxy(16,5+a);printf ("%c",179);
					}
				   for(d=0;d<30;d++){
					  gotoxy(3+d,13); printf ("%c",196);
					}
					for(e=0;e<30;e++){
					  gotoxy(3+e,15); printf ("%c",196);
					}
					   
					gotoxy(2,14); printf("MD");
					gotoxy(36,14); printf("MA");
					gotoxy(2,16); printf("SD");
					gotoxy(36,16); printf("SA");
				    
					if(movimientoacreedor>movimientodeudor){
				        saldoacreedor=movimientoacreedor-movimientodeudor;
				       gotoxy(18,16);printf("%.2f",saldoacreedor); 
				        
					}else if(movimientodeudor>movimientoacreedor){
					  saldodeudor=	movimientodeudor-movimientoacreedor;
					  gotoxy(6,16); printf("%.2f",saldodeudor);
					}else if(movimientodeudor==movimientoacreedor){
						 saldoacreedor=0;
						 saldodeudor=0;
						 gotoxy(18,16);printf("%.2f",saldoacreedor);
						 gotoxy(6,16); printf("%.2f",saldodeudor);
					}
					getch();
			
			}
		    	break;
		    	
		    	default: printf ("Eligio la opcion de salir");
		    	break;
		    	
			}
	}while(opcion!=2);

	getch();		
}


void comercialbalanza(){

	int a, b, c, band=0, d,e,f, acu=0;
	summoviacreedor=0;
	summovideudor=0;
	sumsalacreedor=0;
	sumsaldeudor=0;
	system("cls");
	mostrarempresa();
	margen(10,5,105,35);
	margen(10,5,105,9);
	margen(40,5,105,35);
	margen(56,5,105,35);
	margen(71,5,105,35); 
	margen(86,5,105,35);
	margen(10,5,105,35);
	gotoxy(22,7); printf("Cuentas");
	gotoxy(43,7); printf("Mov. Deudor");
	gotoxy(57,7);printf("Mov. Acreedor");
	gotoxy(73,7); printf("Sal. Deudor");
	gotoxy(87,7);printf ("Sal. Acreedor");
	

	for(i=0; i<N; i++ ){
		
		movimientoacreedor=0;
		movimientodeudor=0;  
		saldoacreedor=0;
		saldodeudor=0;
		
		if (comercial[i].debe[0]>0 || comercial[i].haber[0]>0){
		acu++;
		   gotoxy (12,9+acu); puts(comercial[i].cuenta);	
			
			for(f=0;f<20;f++){
				if(comercial[i].debe[f]>0){
			       movimientodeudor+=comercial[i].debe[f];
				    gotoxy(43,9+acu); printf("%.2f",movimientodeudor);	   
				}
				if(comercial[i].haber[f]>0){
			       movimientoacreedor+=comercial[i].haber[f];	
				    gotoxy(57,9+acu); printf("%.2f",movimientoacreedor);
				}
			}
				
			if(movimientoacreedor>movimientodeudor){
		        saldoacreedor=movimientoacreedor-movimientodeudor;
		       gotoxy(87,9+acu);printf("%.2f",saldoacreedor); 
		        sumsalacreedor+=saldoacreedor;
			}
			 if(movimientodeudor>movimientoacreedor){
			  saldodeudor=movimientodeudor-movimientoacreedor;
			  gotoxy(73,9+acu); printf("%.2f",saldodeudor);
			  sumsaldeudor+=saldodeudor;
			}
			 if(movimientodeudor==movimientoacreedor){
				 saldoacreedor=0;
				 saldodeudor=0;
				 gotoxy(87,9+acu);printf("%.2f",saldoacreedor);
				 gotoxy(73,9+acu); printf("%.2f",saldodeudor);
				 sumsalacreedor+=saldoacreedor;
				 sumsaldeudor+=saldodeudor;
			}
			 summovideudor+=movimientodeudor;
			 summoviacreedor+=movimientoacreedor;
			 comercial[i].saldodeudor=saldodeudor;
			 comercial[i].saldoacreedor=saldoacreedor;
		}
	
	}
	gotoxy(22,(31+(acu-acu+1)));printf("Sumas iguales");
	gotoxy(43,(31+(acu-acu+1))); printf("%.2f",summovideudor);
	gotoxy(57,(31+(acu-acu+1))); printf("%.2f",summoviacreedor);
	gotoxy(73,(31+(acu-acu+1))); printf("%.2f",sumsaldeudor);
	gotoxy(87,(31+(acu-acu+1))); printf("%.2f",sumsalacreedor);
	getch();
	
}

void comercialbalancegeneral(){
	
	int acumula=0;
	totalACcirculante=0, totaAClfijo=0, totalACdiferido=0, totalPAScirculante=0, totalPASfijo=0, totalPASdiferido=0;
	totalAC=0, totalPAS=0;
	suma1degeneral=0, suma2degeneral=0, suma3degeneral=0; 
	float totaldemercancias=0, costodeventas=0,inventafinal=0,acumu1=0,acumula1=0,acumu2=0,acumula2=0,acumu3=0,acumula3=0,acumu4=0,acumula4=0,acumu5=0,acumula5=0;
	
	mostrarempresa();
	margen(10,3,105,35);
	margen(10,3,105,6);
	margen(40,3,105,35);
	margen(50,3,105,35);
	margen(68,3,105,35);
	margen(87,3,105,35);
	margen(105,3,105,35);
	for (i=0;i<20; i++){
		acumu1+=merdebe[i];
		acumula1+=merhaber[i];
		acumu2+=merdebe1[i];
		acumula2+=merhaber1[i];
		acumu3+=merdebe2[i];
		acumula3+=merhaber2[i];
		acumu4+=merdebe3[i];
		acumula4+=merhaber3[i];
		acumu5+=merdebe4[i];
		acumula5+=merhaber4[i];
    }
    
	inventafinal=(acumu1-acumula1)+(acumu2-acumula2)+(acumu3-acumula3)+(acumu4-acumula4)+(acumu5-acumula5);
	movimientoacreedor=0;
	movimientodeudor=0;
	gotoxy(22,5); printf("Cuentas");
	
	
	gotoxy(11,7); printf("ACTIVO");
	gotoxy(11,8);printf("ACTIVO CIRCULANTE");

	
	for (i = 2; i < 12; i++) {
    if (comercial[i].debe[0] > 0 || comercial[i].haber[0] > 0) {
        acumula++;
        gotoxy(11, 8+ acumula);
        puts(comercial[i].cuenta);

        if (i == 5) {
            // Condición especial para comercial[5]
            gotoxy(51, 8 + acumula);
            printf("%.2f", inventafinal);
            totalACcirculante += inventafinal;
            suma1degeneral += inventafinal;
        } else {
            // Condición general para otros índices
            if (comercial[i].saldodeudor > 0) {
                gotoxy(51, 8 + acumula);
                printf("%.2f", comercial[i].saldodeudor);
                totalACcirculante += comercial[i].saldodeudor;
                suma1degeneral += comercial[i].saldodeudor;
            }
            if (comercial[i].saldoacreedor > 0) {
                gotoxy(51, 8+ acumula);
                printf("%.2f", comercial[i].saldoacreedor);
                totalACcirculante += comercial[i].saldoacreedor;
                suma1degeneral += comercial[i].saldoacreedor;
            }
        }
    }
}

	
	
	acumula++;
	//15,25,27,36,38,44,46,48,50.51
	gotoxy(11,8+(acumula)); printf("TOT. ACT. CIRCULANTE");
    gotoxy(69,8+(acumula)); printf("%.2f",totalACcirculante);
    
	acumula++;
	gotoxy(11,8+(acumula));printf("ACTIVO FIJO"); 
	for(i=13; i<29; i++ ){
        if (comercial[i].debe[0]>0 || comercial[i].haber[0]>0){
			acumula++;
	       	gotoxy (11,8+acumula); puts(comercial[i].cuenta);
	       	if(comercial[i].saldodeudor>0){
	       	   	gotoxy(51,8+acumula);printf("%.2f",comercial[i].saldodeudor);
	       	   	totaAClfijo+=comercial[i].saldodeudor;
	       	   	suma1degeneral+=comercial[i].saldodeudor;
			}
			else{
				gotoxy(51,8+acumula);printf("%.2f",comercial[i].saldoacreedor);
				totaAClfijo+=comercial[i].saldoacreedor;
								suma1degeneral+=comercial[i].saldoacreedor;

			}
		}
	}
	acumula++;
	gotoxy(11,8+(acumula)); printf("TOT. ACT. FIJO");
    gotoxy(69,8+(acumula)); printf("%.2f",totaAClfijo);	
    
		
	acumula++;
	gotoxy(11,8+(acumula));printf("ACTIVO DIFERIDO"); 
	for(i=30; i<38; i++ ){
        if (comercial[i].debe[0]>0 || comercial[i].haber[0]>0){
			acumula++;
	       	gotoxy (11,8+acumula); puts(comercial[i].cuenta);
	       	if(comercial[i].saldodeudor>0){
	       	   	gotoxy(51,8+acumula);printf("%.2f",comercial[i].saldodeudor);
	       	   	totalACdiferido+=comercial[i].saldodeudor;
	       	   	suma1degeneral+=comercial[i].saldodeudor;
			}
			else{
				gotoxy(51,8+acumula);printf("%.2f",comercial[i].saldoacreedor);
				totalACdiferido+=comercial[i].saldoacreedor;
								suma1degeneral+=comercial[i].saldoacreedor;

			}
		}
	}
	acumula++;
	gotoxy(11,8+(acumula)); printf("TOT. ACT. DIFERIDO");
	gotoxy(69,8+(acumula)); printf("%.2f",totalACdiferido);    
	
	acumula++;	
	
	totalAC=totalACcirculante+totaAClfijo+totalACdiferido;
    gotoxy(11,8+(acumula)); printf("TOTAL DE ACTIVOS");
    gotoxy(88,8+(acumula)); printf("%.2f",totalAC);
	continuar();
	mostrarempresa();
	margen(10,3,105,35);
	margen(10,3,105,6);
	margen(40,3,105,35);
	margen(50,3,105,35);
	margen(68,3,105,35);
	margen(87,3,105,35);
	margen(105,3,105,35);
	acumula=0;
	acumula++;    	
	gotoxy(11,8+acumula); printf("PASIVO");
	acumula++;
	gotoxy(11,8+acumula);printf("PASIVO CIRCULANTE"); 
	for(i=39; i<48; i++ ){
        if (comercial[i].debe[0]>0 || comercial[i].haber[0]>0){
			acumula++;
	       	gotoxy (11,8+acumula); puts(comercial[i].cuenta);
	       	if(comercial[i].saldodeudor>0){
	       	   	gotoxy(51,8+acumula);printf("%.2f",comercial[i].saldodeudor);
				totalPAScirculante+=comercial[i].saldodeudor;
				suma1degeneral+=comercial[i].saldodeudor;

			}
			else{
				gotoxy(51,8+acumula);printf("%.2f",comercial[i].saldoacreedor);
				totalPAScirculante+=comercial[i].saldoacreedor;
				suma1degeneral+=comercial[i].saldoacreedor;

			}
		}
	}
	acumula++;
	
	gotoxy(11,8+(acumula)); printf("TOT. PAS. CIRCULANTE");
    gotoxy(69,8+(acumula)); printf("%.2f",totalPAScirculante);	
	//15,25,27,36,38,44,46,48,50.51
	acumula++;
	gotoxy(11,8+(acumula));printf("PASIVO FIJO"); 
	for(i=49; i<53; i++ ){
        if (comercial[i].debe[0]>0 || comercial[i].haber[0]>0){
			acumula++;
	       	gotoxy (11,8+acumula); puts(comercial[i].cuenta);
	       	if(comercial[i].saldodeudor>0){
	       	   	gotoxy(51,8+acumula);printf("%.2f",comercial[i].saldodeudor);
	       	   	totalPASfijo+=comercial[i].saldodeudor;
	       	   	suma1degeneral+=comercial[i].saldodeudor;
			}
			else{
				gotoxy(51,8+acumula);printf("%.2f",comercial[i].saldoacreedor);
				totalPASfijo+=comercial[i].saldoacreedor;
								suma1degeneral+=comercial[i].saldoacreedor;

			}
		}
	}
	acumula++;
	
	gotoxy(11,8+(acumula)); printf("TOT. PAS. FIJO");
    gotoxy(69,8+(acumula)); printf("%.2f",totalPASfijo);	
    	
	acumula++;
	gotoxy(11,8+(acumula));printf("PASIVO DIFERIDO"); 
	for(i=54; i<60; i++ ){
        if (comercial[i].debe[0]>0 || comercial[i].haber[0]>0){
			acumula++;
	       	gotoxy (11,8+acumula); puts(comercial[i].cuenta);
	       	if(comercial[i].saldodeudor>0){
	       	   	gotoxy(51,8+acumula);printf("%.2f",comercial[i].saldodeudor);
	       	   	totalPASdiferido+=comercial[i].saldodeudor;
	       	   	suma1degeneral+=comercial[i].saldodeudor;
			}
			else{
				gotoxy(51,8+acumula);printf("%.2f",comercial[i].saldoacreedor);
				totalPASdiferido+=comercial[i].saldoacreedor;
				suma1degeneral+=comercial[i].saldoacreedor;

			}
		}
	}
	acumula++;
	gotoxy(11,8+(acumula)); printf("TOT. PAS. DIFERIDO");
	gotoxy(69,8+(acumula)); printf("%.2f",totalPASdiferido);
        	
	acumula++;
	totalPAS=totalPAScirculante+totalPASfijo+totalPASdiferido;	
    gotoxy(11,8+(acumula)); printf("TOTAL DE PASIVOS");
    gotoxy(88,8+(acumula)); printf("%.2f",totalPAS);
    
    suma2degeneral=totaAClfijo+totalACcirculante+totalACdiferido+totalPAScirculante+totalPASdiferido+totalPASfijo;
    suma3degeneral=totalAC-totalPAS;
    
	acumula++;
    acumula++;
    int a=34;
	gotoxy(11,a); printf("SUMA");
    
    	gotoxy(51,a);printf("%.2f",suma1degeneral);
        gotoxy(69,a); printf("%.2f",suma2degeneral);
        gotoxy(88,a); printf("%.2f",suma3degeneral);			
	
	getch();
}
void comercialtargetasdealmacen(){
   int x;
   int z;
   float existencia=0,saldo=0,existencia1=0,saldo1=0,existencia2=0,saldo2=0;
   float existencia3=0,saldo3=0,existencia4=0,saldo4=0;
   if(p>0)   
    {
    	mostrarempresa();
    	if(pa>=1){
    		for(z=0; z<pa; z++){
    			gotoxy(40,4);printf("%s",subcuenta[0]);
    			if(merdebe[z]>merhaber[z]){
    				gotoxy(28,10+z);printf("%.0f",piezas[z]);
	    			existencia=existencia+piezas[z];
	    			gotoxy(43,10+z);printf("%.0f",existencia);
	    			gotoxy(50,10+z);printf("%.2f",precio[z]);
	    			gotoxy(66,10+z);printf("%.2f",merdebe[z]);
	    			gotoxy(81,10+z);printf("%.2f",merhaber[z]);
	    			saldo=saldo+merdebe[z];
	    			gotoxy(95,10+z);printf("%.2f",saldo);
	    			medi=saldo/existencia;
	    			gotoxy(58,10+z);printf("%d",medi);	
					n++;
				}
				else{
					gotoxy(36,10+z);printf("%.2f",piezas[z]);
	    			existencia=existencia-piezas[z];
	    			gotoxy(43,10+z);printf("%.2f",existencia);
	    			gotoxy(50,10+z);printf("%.2f",precio[z]);
	    			gotoxy(66,10+z);printf("%.2f",merdebe[z]);
	    			gotoxy(81,10+z);printf("%.2f",merhaber[z]);
	    			saldo=saldo-merhaber[z];
	    			gotoxy(95,10+z);printf("%.2f",saldo);
				}
    			
			}
		}
		if(pe>=1){
			for(z=0; z<pe; z++){
				if(merdebe1[z]>merhaber1[z]){
    				gotoxy(28,40+z);printf("%.0f",piezas1[z]);
	    			existencia1=existencia1+piezas1[z];
	    			gotoxy(43,40+z);printf("%.0f",existencia1);
	    			gotoxy(50,40+z);printf("%.2f",precio1[z]);
	    			gotoxy(66,40+z);printf("%.2f",merdebe1[z]);
	    			gotoxy(81,40+z);printf("%.2f",merhaber1[z]);
	    			saldo1=saldo1+merdebe1[z];
	    			gotoxy(95,40+z);printf("%.2f",saldo1);
	    			medi1=saldo1/existencia1;
	    			gotoxy(58,40+z);printf("%d",medi1);	
					n1++;
				}
				else{
					gotoxy(36,40+z);printf("%.2f",piezas1[z]);
	    			existencia1=existencia1-piezas1[z];
	    			gotoxy(43,40+z);printf("%.2f",existencia1);
	    			gotoxy(50,40+z);printf("%.2f",precio1[z]);
	    			gotoxy(66,40+z);printf("%.2f",merdebe1[z]);
	    			gotoxy(81,40+z);printf("%.2f",merhaber1[z]);
	    			saldo1=saldo1-merhaber1[z];
	    			gotoxy(95,40+z);printf("%.2f",saldo1);
				}
    			
			}
		}
    	if(pi>=1){
			for(z=0; z<pi; z++){
				if(merdebe2[z]>merhaber2[z]){
    				gotoxy(28,70+z);printf("%.0f",piezas2[z]);
	    			existencia2=existencia2+piezas2[z];
	    			gotoxy(43,70+z);printf("%.0f",existencia2);
	    			gotoxy(50,70+z);printf("%.2f",precio2[z]);
	    			gotoxy(66,70+z);printf("%.2f",merdebe2[z]);
	    			gotoxy(81,70+z);printf("%.2f",merhaber2[z]);
	    			saldo2=saldo2+merdebe2[z];
	    			gotoxy(95,70+z);printf("%.2f",saldo2);
	    			medi2=saldo2/existencia2;
	    			gotoxy(58,70+z);printf("%.2f",medi2);	
					n2++;
				}
				else{
					gotoxy(36,70+z);printf("%.2f",piezas2[z]);
	    			existencia2=existencia2-piezas2[z];
	    			gotoxy(43,70+z);printf("%.2f",existencia2);
	    			gotoxy(50,70+z);printf("%.2f",precio2[z]);
	    			gotoxy(66,70+z);printf("%.2f",merdebe2[z]);
	    			gotoxy(81,70+z);printf("%.2f",merhaber2[z]);
	    			saldo2=saldo2-merhaber2[z];
	    			gotoxy(95,70+z);printf("%.2f",saldo2);
				}
			}
		}
    	if(po>=1){
			for(z=0; z<po; z++){
				if(merdebe3[z]>merhaber3[z]){
    				gotoxy(28,100+z);printf("%.0f",piezas3[z]);
	    			existencia3=existencia3+piezas3[z];
	    			gotoxy(43,100+z);printf("%.0f",existencia3);
	    			gotoxy(50,100+z);printf("%.2f",precio3[z]);
	    			gotoxy(66,100+z);printf("%.2f",merdebe3[z]);
	    			gotoxy(81,100+z);printf("%.2f",merhaber3[z]);
	    			saldo3=saldo3+merdebe3[z];
	    			gotoxy(95,100+z);printf("%.2f",saldo3);
	    			medi3=saldo3/existencia3;
	    			gotoxy(58,100+z);printf("%.2f",medi3);	
					n3++;
				}
				else{
					gotoxy(36,100+z);printf("%.2f",piezas3[z]);
	    			existencia3=existencia3-piezas3[z];
	    			gotoxy(43,100+z);printf("%.2f",existencia3);
	    			gotoxy(50,100+z);printf("%.2f",precio3[z]);
	    			gotoxy(66,100+z);printf("%.2f",merdebe3[z]);
	    			gotoxy(81,100+z);printf("%.2f",merhaber3[z]);
	    			saldo3=saldo3-merhaber3[z];
	    			gotoxy(95,100+z);printf("%.2f",saldo3);
				}
			}
		}
		if(pu>=1){
			for(z=0; z<pu; z++){
				if(merdebe4[z]>merhaber4[z]){
    				gotoxy(28,130+z);printf("%.0f",piezas4[z]);
	    			existencia4=existencia4+piezas4[z];
	    			gotoxy(43,130+z);printf("%.0f",existencia4);
	    			gotoxy(50,130+z);printf("%.2f",precio4[z]);
	    			gotoxy(66,130+z);printf("%.2f",merdebe4[z]);
	    			gotoxy(81,130+z);printf("%.2f",merhaber4[z]);
	    			saldo4=saldo4+merdebe4[z];
	    			gotoxy(95,130+z);printf("%.2f",saldo4);
	    			medi4=saldo4/existencia4;
	    			gotoxy(58,130+z);printf("%.2f",medi4);	
					n4++;
				}
				else{
					gotoxy(36,130+z);printf("%.2f",piezas4[z]);
	    			existencia4=existencia4-piezas4[z];
	    			gotoxy(43,130+z);printf("%.2f",existencia4);
	    			gotoxy(50,130+z);printf("%.2f",precio4[z]);
	    			gotoxy(66,130+z);printf("%.2f",merdebe4[z]);
	    			gotoxy(81,130+z);printf("%.2f",merhaber4[z]);
	    			saldo4=saldo4-merhaber4[z];
	    			gotoxy(95,130+z);printf("%.2f",saldo4);
				}
			}
		}
	    for(z=0; z<p; z++)
	    {
	    	x=z*30;
	    	margen(10,5+x,110,28+x);
			margen(10,5+x,110,9+x);
		
			margen(27,5+x,110,28+x);
			margen(19,5+x,110,28+x);
			gotoxy(12,7+x); printf("Fecha");
			gotoxy(22,7+x);printf("Fact");
				
			margen(49,5+x,110,28+x);
		    margen(27,5+x,49,7+x);
		    margen(27,7+x,34,28+x);
		    margen(27,7+x,41,28+x);
		    gotoxy(35,6+x); printf("Unidades");
		    gotoxy(29,8+x);printf("ENT");
		    gotoxy(36,8+x);printf("SAL");
		    gotoxy(44,8+x);printf("EXIS");
		    
		    margen(10,5+x,63,28+x);
			margen(49,5+x,63,7+x);
			gotoxy(54,6+x); printf("Costos");
			margen(49,7+x,56,28+x);
			//gotoxy(51,8);printf("EXIS");
			gotoxy(51,8+x);printf("UNIT");
			gotoxy(58,8+x);printf("MEDI");
			
			margen(63,5+x,110,7+x);
			margen(63,7+x,78,28+x);
			margen(63,7+x,93,28+x);
			gotoxy(82,6+x); printf("Valores");
			gotoxy(69,8+x);printf("DEBE");
			gotoxy(84,8+x);printf("HABER");
			gotoxy(98,8+x);printf("SALDO");
		}
	}
	else
	{
		gotoxy((80-27)/2,12);printf("NO HAS INGRESADO MERCANCIAS");
	}
	getch();
}

void comercialestadoderesultados(){
		system("cls");
		margen(1, 1, 100, 29);
	mostrarempresa();
	float ventas=0, devoluciones=0, ventasN=0, compras=0, gastosdecompras=0;
	float comprastotales=0, devoluiconesyrebajas=0, comprasnetas=0;
	float totaldemercancias=0, costodeventas=0,inventafinal=0,acumu1=0,acumula1=0,acumu2=0,acumula2=0,acumu3=0,acumula3=0,acumu4=0,acumula4=0,acumu5=0,acumula5=0;
	int i,f;
	float ventasNetas;
	float gastosgenerales, final;
	movimientoacreedor=0;
	movimientodeudor=0;
	//margen(1,1,100, 30);
	
	for (f=0; f<20; f++){
	   if(comercial[67].debe[f]>0){
	     movimientodeudor+=comercial[67].debe[f];   
		}
		if(comercial[67].haber[f]>0){
		  movimientoacreedor+=comercial[67].haber[f];	

		}
		if(movimientoacreedor<movimientodeudor){
		ventas=movimientodeudor-movimientoacreedor;
		}
		else 
		ventas=movimientoacreedor-movimientodeudor;
	}
	movimientoacreedor=0;
	movimientodeudor=0;
	for (f=0; f<20; f++){
	   if(comercial[68].debe[f]>0){
	     movimientodeudor+=comercial[68].debe[f];   
		}
		if(comercial[68].haber[f]>0){
		  movimientoacreedor+=comercial[68].haber[f];	
		}
		if(movimientoacreedor<movimientodeudor){
		devoluciones=movimientodeudor-movimientoacreedor;
		}
		else 
		devoluciones=movimientoacreedor-movimientodeudor;
		
	}
	movimientoacreedor=0;
	movimientodeudor=0;
	for (f=0; f<20; f++){
	   if(comercial[80].debe[f]>0){
	     movimientodeudor+=comercial[80].debe[f];   
		}
		if(comercial[80].haber[f]>0){
		  movimientoacreedor+=comercial[80].haber[f];	
		}
		
		if(movimientoacreedor<movimientodeudor){
		gastosdecompras=movimientodeudor-movimientoacreedor;
		}
		else 
		gastosdecompras=movimientoacreedor-movimientodeudor;
		
	}
	movimientoacreedor=0;
	movimientodeudor=0;
	for (f=0; f<20; f++){
	   if(comercial[73].debe[f]>0){
	     movimientodeudor+=comercial[65].debe[f];   
		}
		if(comercial[73].haber[f]>0){
		  movimientoacreedor+=comercial[73].haber[f];	

		}
		if(movimientoacreedor<movimientodeudor){
		devoluiconesyrebajas=movimientodeudor-movimientoacreedor;
		}
		else 
		devoluiconesyrebajas=movimientoacreedor-movimientodeudor;
	}

	
	for (i=0;i<20; i++){
		acumu1+=merdebe[i];
		acumula1+=merhaber[i];
		acumu2+=merdebe1[i];
		acumula2+=merhaber1[i];
		acumu3+=merdebe2[i];
		acumula3+=merhaber2[i];
		acumu4+=merdebe3[i];
		acumula4+=merhaber3[i];
		acumu5+=merdebe4[i];
		acumula5+=merhaber4[i];
    }
    
	inventafinal=(acumu1-acumula1)+(acumu2-acumula2)+(acumu3-acumula3)+(acumu4-acumula4)+(acumu5-acumula5);
	movimientoacreedor=0;
	movimientodeudor=0;
	
	for (f=0; f<20; f++){
	   if(comercial[77].debe[f]>0){
	     movimientodeudor+=comercial[77].debe[f];   
		}
		if(comercial[77].haber[f]>0){
		  movimientoacreedor+=comercial[77].haber[f];	

		}
		if(movimientoacreedor<movimientodeudor){
		gastosgenerales=movimientodeudor-movimientoacreedor;
		}
		else 
		gastosgenerales=movimientoacreedor-movimientodeudor;
	}
	movimientoacreedor=0;
	movimientodeudor=0;
	
		for (f=0; f<20; f++){
	   if(comercial[72].debe[f]>0){
	     movimientodeudor+=comercial[72].debe[f];   
		}
		if(comercial[72].haber[f]>0){
		  movimientoacreedor+=comercial[72].haber[f];	

		}
		if(movimientoacreedor<movimientodeudor){
		compras=movimientodeudor-movimientoacreedor;
		}
		else 
		compras=movimientoacreedor-movimientodeudor;
	}
	
	movimientoacreedor=0;
	movimientodeudor=0;
	float costodeventasMOD;
		for (f=0; f<20; f++){
	   if(comercial[75].debe[f]>0){
	     movimientodeudor+=comercial[75].debe[f];   
		}
		if(comercial[75].haber[f]>0){
		  movimientoacreedor+=comercial[75].haber[f];	

		}
		if(movimientoacreedor<movimientodeudor){
		costodeventasMOD=movimientodeudor-movimientoacreedor;
		}
		else 
		costodeventasMOD=movimientoacreedor-movimientodeudor;
	}
	gotoxy(20,5); printf("    Ventas o ingresos totales ");
	gotoxy(71,5); printf ("%.2f", ventas);
	gotoxy(20,6); printf("(-)  Devoluciones y rebajas sobre/ventas ");
	gotoxy(71,6);printf ("%.2f", devoluciones);
	ventasN=ventas-devoluciones;
	gotoxy(20,7); printf("(=)  Ventas netas ");	
	gotoxy(71,7);printf ("%.2f ",ventasN);
	gotoxy(20,8); printf("( ) Compras");	
	gotoxy(71,8);printf ("%.2f ",compras);
	gotoxy(20,9);printf("(+)  Gastos de compras ");
	gotoxy(71,9);printf ("%.2f", gastosdecompras);
	comprastotales=compras+gastosdecompras;
	gotoxy(20,10);printf("(=)  Compras totales  ");
	gotoxy(71,10);printf ("%.2f", comprastotales);
	gotoxy(20,11);printf("(-)  Devoluciones y rebajas s/compras ");
	gotoxy(71,11);printf ("%.2f",devoluiconesyrebajas);
	comprasnetas=comprastotales-devoluiconesyrebajas;
	gotoxy(20,12);printf("(=)  Compras netas ");
    gotoxy(71,12);printf ("%.2f", comprasnetas);
	gotoxy(20,13);printf("(+)  Inventario inicial  ");
	gotoxy(71,13);printf ("%.2f",inventarioinicial);
	totaldemercancias=comprasnetas+inventarioinicial;
	gotoxy(20,14);printf("(=)  Total de mercancias ");
	gotoxy(71,14);printf ("%.2f",totaldemercancias);
	gotoxy(20,15);printf("(-)  Inventario final ");
	gotoxy(71,15);printf ("%.2f",inventafinal);
    costodeventas=totaldemercancias-inventafinal;
	gotoxy(20,16);printf("(=)  Costo de ventas  ");
	gotoxy(71,16);printf ("%.2f",costodeventas);
	gotoxy(20,17);printf("(-)  Costo de ventas MOD ");
	gotoxy(71,17);printf ("%.2f",costodeventasMOD);
	ventasNetas=costodeventas+costodeventasMOD;
	gotoxy(20,18);printf("(-)  Ventas Netas ");
	gotoxy(71,18);printf ("%.2f",ventasNetas);
	float utilidad;
	utilidad=ventasN-ventasNetas;
	gotoxy(20,19);printf("(=)  Utilidad o perdida bruta ");					
	gotoxy(71,19);printf ("%.2f",utilidad);
	gotoxy(20,20);printf("(-)Gastos generales");					
	gotoxy(71,20);printf ("%.2f",gastosgenerales);
	final=utilidad-gastosgenerales;
	gotoxy(20,21);printf("(=)Utilidad o perdida operativa");					
	gotoxy(71,21);printf ("%.2f",final);
	getch();
}
void borar()
{
	int q;
	for(q=0; q<40; q++)
	{
		gotoxy(96,2+q);printf("                                    ");
	}

}

//Tabla de amortizacion
void tabladeA(){
	double montoPrestamo, tasaInteres;
    int plazo,i, opcion, pl, inte;
	int longitud;
	char nombre[30];
    float intereses;

	margen(1,0,117,29);
	titulo();
	//Solicitar datos de la empresa
	margen(45,14,65,16);
	gotoxy(50,15); printf("BIENVENIDO");
	gotoxy(40,25);system("pause");
	system("cls");
	margen(1,0,117,29);
	 mostrarempresa();
	hora();
	//Solicitar datos del prestamo
	margen(51,7,68,9);
	gotoxy(52,8); printf("INGRESO DE DATOS");
	margen(1,0,117,29);
	hora();
	margen(38,11,80,13);
    gotoxy(38,12);printf("Monto del prestamo $: ");
    scanf("%lf", &montoPrestamo);
    gotoxy(52,8); printf("INGRESO DE DATOS");
	margen(1,0,117,29);
	hora();
	pl= op_plazo(&plazo);
	inte= interes(&tasaInteres);
	if (pl == 1) {
        if (inte == 1) {
            intereses = tasaInteres/100;
        } else if (inte == 2){
            intereses = (tasaInteres/7)/100;
        } else if (inte == 3){
            intereses = (tasaInteres/30)/ 100;
        } else if (inte == 4) {
            intereses = (tasaInteres/360)/ 100;
        }
    } else if (pl == 2) {
        if (inte == 1) {
            intereses = (tasaInteres*7)/100;
        } else if (inte == 2) {
            intereses = (tasaInteres)/100;
        } else if (inte == 3) {
            intereses = (tasaInteres/4)/ 100;
        } else if (inte == 4) {
            intereses = (tasaInteres/52)/ 100;
        }
        
    } else if (pl == 3) {
        if (inte == 1) {
            intereses = (tasaInteres*30)/ 100;
        } else if (inte == 2) {
            intereses = (tasaInteres*4)/ 100;
        } else if (inte == 3) {
            intereses = tasaInteres / 100;
        } else if (inte == 4) {
            intereses = (tasaInteres/12)/100;
        }
    } else if (pl == 4) {
        if (inte == 1) {
            intereses = (tasaInteres*360)/100;
        } else if (inte == 2) {
            intereses = (tasaInteres*52)/ 100;
        } else if (inte == 3) {
            intereses = (tasaInteres*12)/ 100;
        } else if (inte == 4) {
            intereses = tasaInteres/100;
        }
    }
	system("cls");
	//Condicion para imprimir las tablas
	 mostrarempresa();
    while (1) {
    	margen(47,7,74,9);
        gotoxy(48,8); printf("Condiciones del credito");
        margen(40,10,80,12);
        gotoxy(48,11); printf("1: Tasa de interes fija.");
        margen(30,13,90,15);
        gotoxy(48,14); printf("2: Tasa de interes sobre saldos insolutos.");
        margen(54,16,64,18);
        gotoxy(48,17); printf("3: Volver al menu");
        
        gotoxy(55,19);printf("Opcion: ");
        scanf("%d", &opcion);
		system("cls");
        switch (opcion) {
            case 1:
            	 mostrarempresa();
                tasa_fija(montoPrestamo, intereses, plazo);
                break;

            case 2:
            	 mostrarempresa();
                saldos_insolutos(montoPrestamo, intereses, plazo);
                break;
            case 3:
            	return;
        }
    }
}
void titulo(){
	margen(35,9,75,11);
	gotoxy(40,10); printf("TABLA DE AMORTIZACION DE CREDITOS");
}	


void hora(){
	time_t now = time(NULL);
    struct tm *local = localtime(&now); 
    gotoxy(100,1); printf("%02d/%02d/%d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
}

void mostrarInteres(int opcion) {
	 mostrarempresa();
	hora();
	margen(48,10,72,12);
    gotoxy(49, 11);
    printf("Seleccione una opcion:");
    int i;
    for ( i = 1; i <= 4; i++) {
    	
        gotoxy(52, 12+(i*3));
        if (opcion == i) {
            printf("> ");
        } else {
            printf("  ");
        }

        switch (i) {
            case 1:
            	margen(56,14,65,16);
            	gotoxy(58,15); printf("DIAS");
                break;
            case 2:
            	margen(56,17,65,19);
                gotoxy(58,18);printf("SEMANAS");
                break;
            case 3:
            	margen(56,20,65,22);
                gotoxy(58,21);printf("MESES");
                break;
            case 4:
            	margen(56,23,65,25);
                gotoxy(58,24);printf("ANUAL");
                break;
        }
    }
}

int interes(double *tasaInteres){
	 mostrarempresa();
    int opcion = 1;
    int tecla;
    margen(1,0,117,29);
	margen(50,7,70,9);
    gotoxy(51, 8);
    printf(" Tasa de Interes ");
    do {
        system("cls"); 
        margen(1,0,117,29);
		margen(50,7,70,9); 
        gotoxy(51, 8);
        printf(" Tasa de Interes ");
        mostrarPlazo(opcion);
        tecla = getch();
        switch (tecla) {
            case 72:  
                if (opcion > 1) opcion--;
                break;
            case 80: 
                if (opcion < 4) opcion++;
                break;
        }
    } while (tecla != 13);
	system("cls");
	margen(1,0,117,29);
	hora();
	margen(50,7,70,9);
    gotoxy(51, 8);
    printf(" Tasa de Interes ");
    margen(43,11,80,13);
	gotoxy(48,12);
    switch (opcion)  {
        case 1:
        	 mostrarempresa();
        	 gotoxy(48,12);
            printf("Tasa de interes diaria: ");
            scanf("%lf",tasaInteres);
            break;

        case 2:
        	 mostrarempresa();
        	 gotoxy(48,12);
            printf("Tasa de interes semanal: ");
            scanf("%lf",tasaInteres);
            break;

        case 3:
        	 mostrarempresa();
        	 gotoxy(48,12);
            printf("Tasa de interes mensual: ");
            scanf("%lf",tasaInteres);
            break;

        case 4:
        	 mostrarempresa();
        	 gotoxy(48,12);
            printf("Tasa de interes anual: ");
            scanf("%lf",tasaInteres);
            break;
    }
    return opcion;
}
void mostrarPlazo(int opcion) {
	 mostrarempresa();
	 mostrarempresa();
	hora();
	margen(48,10,72,12);
    gotoxy(49, 11);
    printf("Seleccione una opcion:");
    int i;
    for (i = 1; i <= 4; i++) {
    	
        gotoxy(52, 12+(i*3));
        if (opcion == i) {
            printf("> ");
        } else {
            printf("  ");
        }

        switch (i) {
            case 1:
            	margen(56,14,65,16);
            	gotoxy(58,15); printf("DIAS");
                break;
            case 2:
            	margen(56,17,65,19);
                gotoxy(58,18);printf("SEMANAS");
                break;
            case 3:
            	margen(56,20,65,22);
                gotoxy(58,21);printf("MESES");
                break;
            case 4:
            	margen(56,23,65,25);
                gotoxy(58,24);printf("ANUAL");
                break;
        }
    }
}

int op_plazo(int *plazo){
	 mostrarempresa();
    int opcion = 1;
    int tecla;
    margen(1,0,117,29);
	margen(56,7,64,9);
    gotoxy(57, 8);
    printf(" PLAZO ");
    do {
        system("cls"); 
        margen(1,0,117,29);
		margen(56,7,64,9); 
        gotoxy(57, 8);
        printf(" PLAZO ");
        mostrarPlazo(opcion);
        tecla = getch();
        switch (tecla) {
            case 72:  
                if (opcion > 1) opcion--;
                break;
            case 80: 
                if (opcion < 4) opcion++;
                break;
        }
    } while (tecla != 13);
	system("cls");
	margen(1,0,117,29);
	hora();
	margen(56,7,64,9);
	gotoxy(57, 8);
    printf(" PLAZO ");
    margen(43,11,80,13);
	gotoxy(48,12);
    switch (opcion)  {
        case 1:
        	 mostrarempresa();
        	 gotoxy(48,12);
            printf("Plazo del prestamo en dias: ");
            scanf("%d",plazo);
            break;

        case 2:
        	 mostrarempresa();
        	 gotoxy(48,12);
            printf("Plazo del prestamo en semanas: ");
            scanf("%d",plazo);
            break;

        case 3:
        	 mostrarempresa();
        	 gotoxy(48,12);
            printf("Plazo del prestamo en meses: ");
            scanf("%d",plazo);
            break;

        case 4:
        	 mostrarempresa();
        	 gotoxy(48,12);
            printf("Plazo del prestamo en años: ");
            scanf("%d",plazo);
            break;
    }
    return opcion;
}
//Funcion para tabla sobre saldos insolutos
void saldos_insolutos(float montoPrestamo, float intereses, float plazo) {
	 mostrarempresa();
    double pagoMensual, saldo, pagomensual;
    int i;	
	hora();
    // Calcular el pago mensual
    pagomensual = montoPrestamo / plazo;
    //Cabecera
    gotoxy(35,0);
    printf("TABLA DE AMORTIZACION DE CREDITOS SOBRE SALDOS INSOLUTOS");
    gotoxy(0,2);
    printf("Monto del prestamo: %.2f", montoPrestamo);
    printf("\nPago mensual = $ %.2f\n\n", pagomensual);
    printf("Numero de Pago\t\tCapital\t\tIntereses\t\tSaldo\t\t\tPago total\n");

    saldo = montoPrestamo;
    float totali, totalc, total;

    for (i = 1; i <= plazo; i++) {
        // Calcular el monto del pago de intereses
        double interes = saldo * intereses;
        totali = totali + interes;

        // Calcular el monto del pago del capital
        double capital = pagomensual;
        totalc = totalc + capital;

        // Actualizar el saldo del préstamo
        saldo = saldo - capital;

        pagoMensual = capital + interes;
        total = total + pagoMensual;
        // Imprimir los detalles de la cuota
        printf("%d\t\t\t%.2f\t\t%.2f\t\t\t%.2f\t\t\t%.2f\n", i, capital, interes, saldo, pagoMensual);
    }
    printf("\nTotal");
    printf("\t\t\t%.2f\t", totalc);
    printf("%.2f\t", totali);
    printf("\t\t%.2f\t", saldo);
    printf("\t\t%.2f", total);
    
    printf("\n");
    printf("\nPresione para continuar...");
    getch();
    system("cls");
}
//Funcion para tabla sobre tasa fija
void tasa_fija(float montoPrestamo, float intereses, float plazo) {
    double pagoMensual, saldo, pagomensual;
    int i;
    hora();

    pagomensual = montoPrestamo / plazo;
    //Cabecera
    gotoxy(35,0);
    printf("TABLA DE AMORTIZACION DE CREDITOS DE TASA FIJA");
    gotoxy(0,2);
    printf("Monto del prestamo: %.2f", montoPrestamo);
    printf("\nPago mensual = $ %.2f\n\n", pagomensual);
    printf("Numero de Pago\t\tCapital\t\tIntereses\t\tSaldo\t\t\tPago total\n");

    saldo = montoPrestamo;
    float totali, totalc, total;

    for (i = 1; i <= plazo; i++) {

        // Calcular el monto del pago de intereses
        double interes = montoPrestamo * intereses;
        totali = totali + interes;

        // Calcular el monto del pago del capital
        double capital = pagomensual;
        totalc = totalc + capital;

        // Actualizar el saldo del préstamo
        saldo = saldo - capital;

        pagoMensual = capital + interes;
        total = total + pagoMensual;
        // Imprimir los detalles de la cuota
        printf("%d\t\t\t%.2f\t\t%.2f\t\t\t%.2f\t\t\t%.2f\n", i, capital, interes, saldo, pagoMensual);
    }
    printf("\nTotal");
    printf("\t\t\t%.2f\t", totalc);
    printf("%.2f\t", totali);
    printf("\t\t%.2f\t", saldo);
    printf("\t\t%.2f", total);
    
    printf("\n");
    printf("\nPresione para continuar...");
    getch();
    system("cls");
}

//Tabla de dep de act

void tabladeDep(){
	    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct Activo activo;
    int op;

    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);
    do {
        system("cls");  // Limpiar pantalla
        mostrarempresa(); 
        titulo1();
		margen(31, 12, 85, 14 );
		margen(10, 4, 100, 29 );
		color(hConsole, 10);
        gotoxy(32, 13);
        printf("NOMBRE DEL BIEN: ");
        color(hConsole, 7);
        fgets(activo.nombre, MAX_STRING_LENGTH, stdin);
        activo.nombre[strcspn(activo.nombre, "\n")] = '\0';
		system("cls");
		mostrarempresa(); 
		titulo1();
        generarCodigoRegistro(&activo, tm_info);

		margen(10, 4, 100, 29 );
		margen(31, 12, 85, 14 );
		color(hConsole, 10);
        gotoxy(32, 13);
        printf("LOCALIZACION O RESGUARDO: ");
        color(hConsole, 7);
        fgets(activo.localizacion, MAX_STRING_LENGTH, stdin);
        activo.localizacion[strcspn(activo.localizacion, "\n")] = '\0';
		system("cls");
		titulo1();
		margen(10, 4, 100, 29 );
		margen(31, 12, 70, 14 );
		color(hConsole, 10);
        gotoxy(32, 13);
        printf("VALOR INICIAL DEL ACTIVO: $ ");
        color(hConsole, 7);
        scanf("%f", &activo.valorInicial);
        system("cls");
        titulo1();
		
		margen(10, 4, 100, 29 );
		margen(31, 12, 70, 14 );
		color(hConsole, 10);
        gotoxy(32, 13);
        printf("VIDA UTIL DEL ACTIVO EN A%COS: ", 165);
        color(hConsole, 7);
        scanf("%d", &activo.vidaUtil);
        system("cls");
        titulo1();

        if (activo.valorInicial <= 0 || activo.vidaUtil <= 0) {
            printf("Error: Los valores ingresados deben ser mayores que cero.\n");
            return;
        }

        calcularDepreciacion(&activo);

        if (numActivos < MAX_ACTIVOS) {
            tablaActivos[numActivos] = activo;
            numActivos++;
        } else {
            printf("Error: Se ha alcanzado el límite máximo de activos.\n");
            return;
        }

        imprimirTablaContable();
        mostrarempresa();
        margen(2, 2, 30, 4);
		gotoxy(3, 3);
		printf("DEPRECIACION DE ACTIVOS");

        gotoxy(42, 18);
        system("pause");
        system("cls");
		titulo1();
        gotoxy(42, 13);
        printf("DESEA REGISTRAR OTRO BIEN? 1: Si 2: No");
        scanf("%d", &op);

        while ((getchar()) != '\n');

    } while (op == 1);

    return;
}


void calcularDepreciacion(struct Activo *activo) {
    activo->depreciacionAnual = activo->valorInicial / activo->vidaUtil;
    activo->depreciacionMensual = activo->depreciacionAnual / 12;
}

void generarCodigoRegistro(struct Activo *activo, struct tm *tm_info) {
    char letrasNombre[3] = "XX";
    int j = 0, i;

    for (i = 0; i < strlen(activo->nombre) && j < 2; i++) {
        if (isalpha(activo->nombre[i])) {
            letrasNombre[j] = toupper(activo->nombre[i]);
            j++;
        }
    }

    sprintf(activo->registro, "%c%c%02d%02d%02d",
            letrasNombre[0], letrasNombre[1],
            tm_info->tm_year % 100, tm_info->tm_mon + 1, tm_info->tm_mday);

    int sufijo = 1;
    char registroOriginal[12];
    strcpy(registroOriginal, activo->registro);

    while (1) {
        int repetido = 0, k;

        for (k = 0; k < numActivos; k++) {
            if (strcmp(tablaActivos[k].registro, activo->registro) == 0) {
                repetido = 1;
                break;
            }
        }

        if (repetido) {
            sprintf(activo->registro, "%s%d", registroOriginal, sufijo);
            sufijo++;
        } else {
            break;
        }
    }
}

void titulo1()
{
	mostrarempresa();
	margen(39, 5, 73,7);
	gotoxy(40, 6);
	printf("TABLA DE DEPRECIACION DE ACTIVOS");
}

void imprimirTablaContable() {
    system("cls");  // Limpiar pantalla
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(0, 0);
    printf("\n\n\n\n\n\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    color(hConsole, 6);
	printf("| %-25s | %11s | %-25s | %14s | %8s | %10s | %12s | %13s |\n",
           "NOMBRE DEL BIEN", "# REGISTRO", "LOCALIZACION/RESGUARDO", "MOI", "VIDA UTIL", "DEP. ANUAL", "DEP. MENSUAL", "SALDO EN L.");
           color(hConsole, 7);
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");

    int i;
    for (i = 0; i < numActivos; i++) {
        float depreciacionAnual = tablaActivos[i].depreciacionAnual;
        float depreciacionMensual = tablaActivos[i].depreciacionMensual;
        float saldoLibros = tablaActivos[i].valorInicial - depreciacionAnual;

        printf("| %-25s | %11s | %-25s | $%13.2f | %8d | $%10.2f | $%10.2f | $%13.2f |\n",
               tablaActivos[i].nombre, tablaActivos[i].registro,
               tablaActivos[i].localizacion, tablaActivos[i].valorInicial,
               tablaActivos[i].vidaUtil, depreciacionAnual, depreciacionMensual, saldoLibros
			   );
			   
			   printf("\n");
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
}



void bienvenidaISR()
{
		HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	    // Solicitar información al usuario
    margen(44, 8, 55, 10);
    margen(24, 3, 75, 5);
    color(hConsole, 6);
    gotoxy(25, 4);
    printf("CALCULADORA FISCAL DEL IMPUESTO SOBRE LA RENTA");
    color(hConsole, 7);
    gotoxy(45, 9);
    color(hConsole, 11);
    printf("BIENVENIDO");
    color(hConsole, 7);
    gotoxy(40, 14);
}


void calcular_ISR(){
	char  fecha1[100], fecha2[100];
float salario,gravadas,sueldo,total;
float inf,excedente,porcentaje,impuesto,cuota,cargo,credito,isr,x;
int res, dias=0,dias2=0, dias3=0,dias4=0,totaldias=0,op;
//Tiempo
margen(1, 3, 100, 25);
time_t tiempo_actual;
time(&tiempo_actual);
struct tm *info_tiempo = localtime(&tiempo_actual);

gotoxy(5,3); printf("  %02d/%02d/%02d  ", info_tiempo->tm_mday,info_tiempo->tm_mon+1,info_tiempo->tm_year+1900);	
HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	mostrarempresa();
	color(hConsole, 13);
	margen(1, 3, 100, 25);
	bienvenidaISR();
	color(hConsole, 11);
	gotoxy(60, 25);
	printf("Presione enter para comenzar...");
	getch();
	system("cls");
	color(hConsole, 7);	
do{
	margen(1, 3, 100, 25);
	mostrarempresa(); 
		color(hConsole, 13);
    	color(hConsole, 6);
	    gotoxy(25, 4);
	    printf("CALCULADORA FISCAL DEL IMPUESTO SOBRE LA RENTA");
	    color(hConsole, 13);
	    color(hConsole, 11);
	    gotoxy(40, 7);
	    color(hConsole, 7);
	    
	gotoxy(5,2);printf("  %02d/%02d/%02d  ", info_tiempo->tm_mday,info_tiempo->tm_mon+1,info_tiempo->tm_year+1900);
	mostrarempresa();
	gotoxy(30, 11);
	color(hConsole, 11);
	printf("Seleccione el plazo a calcular.");
	gotoxy(40,13);printf("1. Mensual");
	gotoxy(40,14);printf("2. Quincenal");
	gotoxy(40,16);printf("Opcion: ");
	scanf("%d",&op);
	color(hConsole, 7);
	gotoxy(45, 19);
	printf("AVISO:");
	gotoxy(15, 20);
	printf("Cada periodo anual las tablas utilizadas para el calculo suelen cambiar");
	gotoxy(25, 21);
	printf("Solicite la actualizacion si es necesario");
	sleep(1);
	color(hConsole, 13);
	gotoxy(60, 25);
    printf("Presione enter para comenzar...");
    getch();
    system("cls");
    mostrarempresa();
    color(hConsole, 7);	
	switch(op){
	case 1:
		mostrarempresa(); 
		gotoxy(5,3); printf("  %02d/%02d/%02d  ", info_tiempo->tm_mday,info_tiempo->tm_mon+1,info_tiempo->tm_year+1900);
		color(hConsole, 13);
			    margen(1, 3, 100, 25);
			    
			    margen(24, 3, 75, 5);
			    color(hConsole, 6);
			    gotoxy(25, 4);
			    printf("CALCULADORA FISCAL DEL IMPUESTO SOBRE LA RENTA");
			    color(hConsole, 11);
	gotoxy(45, 6);printf("---- MENSUAL ----"); 
	color(hConsole, 7);
	gotoxy(6,7);printf("Sueldo o salario: ");
	scanf("%f",&salario);
	gotoxy(6,8);printf("Dias efectivamente laborados: ");
	scanf("%d",&dias);
	gotoxy(6,9);printf("Faltas por incapacidad: ");
	scanf("%d",&dias2);
	//TOTAL DIAS
	if (dias2>3){
		gotoxy(70,9);printf("  La empresa solo cubre 3");
		sleep(1);
		gotoxy(70,9);printf("                          ");
		dias2=3;	
	}
	gotoxy(6,10);printf("Faltas sin goce de sueldo: ");
	scanf("%d",&dias3);

	gotoxy(6,11);printf("Faltas con goce de sueldo: ");
	scanf("%d",&dias4);
	
	gotoxy(6,12);printf("Percepciones exentas: ");
	scanf("%f",&x);
	
	gotoxy(6,13);printf("Percepciones gravadas: ");
	scanf("%f",&gravadas);
	//TOTAL DIAS
	if (dias2>3){
		gotoxy(50,11);printf(" La empresa solo cubre 3");
		sleep(1);
		gotoxy(50,11);printf("                                ");
		dias2=3;	
	}
	gotoxy(60, 25);
			    printf("Presione enter para comenzar...");
			    getch();
			    system("cls");
			    color(hConsole, 7);
	margen(1, 3, 100, 25);
	totaldias=(dias+dias2+dias4);
	margen(24, 3, 75, 5);
			    color(hConsole, 6);
			    gotoxy(5,3); printf("  %02d/%02d/%02d  ", info_tiempo->tm_mday,info_tiempo->tm_mon+1,info_tiempo->tm_year+1900);
			    gotoxy(25, 4);
			    printf("CALCULADORA FISCAL DEL IMPUESTO SOBRE LA RENTA");
			    color(hConsole, 11);
	gotoxy(80,3);printf("DIAS A PAGAR: %d",totaldias);
	
	gotoxy(8,16);printf("BASE GRAVABLE: ");
	sueldo=salario*totaldias;
	total=sueldo+gravadas;
	gotoxy(10,7);printf("Sueldo o salario:");
	gotoxy(70,7);printf("%.2f", sueldo);
	gotoxy(6, 8);
	printf("(+)");
	gotoxy(10,8);printf("Ingresos gravables:");
	gotoxy(70,8);printf("%.2f",gravadas);
	gotoxy(6, 10);
	printf("(=)");
	gotoxy(10,10);printf("Base gravable:");
	gotoxy(70,10);printf("%.2f",total);
	gotoxy(70,9);
	printf("%c%c%c%c%c%c%c%c", 196, 196,196, 196,196, 196,196, 196);
	
	// LIIMITE INFERIOR
	
	if (total>0.01 && total<496.07) inf= 0.01;
	if (total>496.07 && total<4210.41) inf= 496.08;
	if (total>4210.41 && total<7399.42) inf= 4210.42;
	if (total>7399.42 && total<8601.50) inf= 7399.43;
	if(total>8601.50) inf= 8601.51;
	
	gotoxy(6, 11);
	printf("(+)");
	gotoxy(10, 11);
	printf("Limite Inferior:" );
	
	gotoxy(70,11);printf("%.2f",inf);
	excedente=total-inf;
	gotoxy(70,12);
	printf("%c%c%c%c%c%c%c%c", 196, 196,196, 196,196, 196,196, 196);
	gotoxy(6, 13);
	printf("(=)");
	gotoxy(10, 13);
	printf("Excedente:");
	gotoxy(70,13);printf("%.2f",excedente);
	
	// PORCENTAJE 
	if (total>0.01 && total<496.07) porcentaje= 3;
	if (total>496.07 && total<4210.41) porcentaje= 10;
	if (total>4210.41 && total<7399.42) porcentaje= 17;
	if (total>7399.42 && total<8601.50) porcentaje=25;
	if(total>8601.50) porcentaje= 28;
	
	gotoxy(6, 14);
	printf("(*)");
	gotoxy(10, 14);
	printf("Porcentaje S/Limite Inferior:");
	gotoxy(70,14);printf("%.2f",porcentaje);
	impuesto=(excedente*porcentaje)/100;
	gotoxy(70,15);
	printf("%c%c%c%c%c%c%c%c", 196, 196,196, 196,196, 196,196, 196);
	
	gotoxy(6, 16);
	printf("(=)");
	gotoxy(10, 16);
	printf("Impuesto Marginal: ");
	gotoxy(70,16);printf("%.2f",impuesto);
	
	// CUOTAS FIJAS 
	if (total>0.01 && total<496.07) cuota= 0;
	if (total>496.07 && total<4210.41) cuota= 14.88;
	if (total>4210.41 && total<7399.42) cuota= 386.31;
	if (total>7399.42 && total<8601.50) cuota=928.46;
	if(total>8601.50) cuota= 1228.98;
	gotoxy(6, 17);
	printf("(+)");
	gotoxy(10, 17);
	printf("Cuota Fija: ", cuota);
	gotoxy(70,17);printf("%.2f",cuota);
	cargo=impuesto+cuota;
	gotoxy(70,18);
	printf("%c%c%c%c%c%c%c%c", 196, 196,196, 196,196, 196,196, 196);
	gotoxy(6, 19);
	printf("(=)");
	gotoxy(10, 19);
	printf("Impuesto a Cargo:");
	gotoxy(70,19);printf("%.2f",cargo);
	
	//CREDITO
	if(sueldo>0.01 && sueldo<1768.96) credito=407.02;
	if(sueldo>1768.97 && sueldo<2604.68) credito=406.83;
	if(sueldo>2604.69 && sueldo<2653.38) credito=406.83;
	if(sueldo>2653.39 && sueldo<3472.84) credito=406.62;
	if(sueldo>3472.85 && sueldo<3537.87) credito=392.77;
	if(sueldo>3537.88 && sueldo<3785.54) credito=382.46;
	if(sueldo>3785.55 && sueldo<4446.15) credito=382.46;
	if(sueldo>4446.16 && sueldo<4717.18) credito=354.23;
	if(sueldo>4717.19 && sueldo<5335.42) credito=324.87;
	if(sueldo>5335.43 && sueldo<6224.67) credito=294.63;
	if(sueldo>6224.68 && sueldo<7113.90) credito=253.54;
	if(sueldo>7113.91 && sueldo<7382.33) credito=217.61;
	if(sueldo>7382.34) credito=0;
	
	gotoxy(6, 20);
	printf("(-)");
	gotoxy(10, 20);
	printf("Credito al salario:");
	gotoxy(70,20);printf("%.2f",130,credito);
	isr=cargo-credito;
	gotoxy(70,21);
	printf("%c%c%c%c%c%c%c%c", 196, 196,196, 196,196, 196,196, 196);
	gotoxy(6, 22);
	printf("(=)");
	gotoxy(10, 22);
	printf("Impuesto A Pagar:");
	gotoxy(70,22);printf("%.2f",isr);
	
	break;
	
	case 2: 
	mostrarempresa(); 
	gotoxy(5,3); printf("  %02d/%02d/%02d  ", info_tiempo->tm_mday,info_tiempo->tm_mon+1,info_tiempo->tm_year+1900);
	 margen(1, 3, 100, 25);
	color(hConsole, 6);
	margen(24, 3, 75, 5);
			    gotoxy(25, 4);
			    printf("CALCULADORA FISCAL DEL IMPUESTO SOBRE LA RENTA");
			    color(hConsole, 11);
	gotoxy(45, 6);printf("---- QUINCENAL ----"); 
	color(hConsole, 7);
	gotoxy(6,7);printf("Sueldo o salario: ");
	scanf("%f",&salario);
	gotoxy(6,8);printf("Dias efectivamente laborados: ");
	scanf("%d",&dias);
	gotoxy(6,9);printf("Faltas por incapacidad: ");
	scanf("%d",&dias2);
	//TOTAL DIAS
	if (dias2>3){
		gotoxy(70,9);printf("La empresa solo cubre 3");
		sleep(1);
		gotoxy(70,9);printf("                                ");
		dias2=3;	
	}
	gotoxy(6,10);printf("Faltas sin goce de sueldo: ");
	scanf("%d",&dias3);
	
	gotoxy(6,11);printf("Faltas con goce de sueldo: ");
	scanf("%d",&dias4);
	
	gotoxy(6,12);printf("Percepciones excentas: ");
	scanf("%f",&x);
	
	gotoxy(6,13);printf("Percepciones gravadas: ");
	scanf("%f",&gravadas);
	//TOTAL DIAS
	if (dias2>3){
		gotoxy(50,11);printf(" La empresa solo cubre 3" );
		sleep(1);
		gotoxy(50,11);printf("                          ");
		dias2=3;	
	}
	gotoxy(60, 25);
			    printf("Presione enter para comenzar...");
			    getch();
			    system("cls");
			    color(hConsole, 7);
				gotoxy(5,3); printf("  %02d/%02d/%02d  ", info_tiempo->tm_mday,info_tiempo->tm_mon+1,info_tiempo->tm_year+1900);	
	totaldias=(dias+dias2+dias4);
	margen(1, 3, 100, 25);
	margen(24, 3, 75, 5);
			    color(hConsole, 6);
			    gotoxy(25, 4);
			    printf("CALCULADORA FISCAL DEL IMPUESTO SOBRE LA RENTA");
			    color(hConsole, 11);
	gotoxy(80,3);printf("DIAS A PAGAR: %d",totaldias);

	gotoxy(8,16);printf("BASE GRAVABLE: ");
	sueldo=salario*totaldias;
	total=sueldo+gravadas;
	gotoxy(10,7);printf("Sueldo o salario:");
	gotoxy(70,7);printf("%.2f",sueldo);
	
	gotoxy(6, 8);
	printf("(+)");
	gotoxy(10, 8);
	printf("Ingresos gravables:");
	gotoxy(70,8);printf("%.2f",gravadas);
	
	gotoxy(70,9);
	printf("%c%c%c%c%c%c%c%c", 196, 196,196, 196,196, 196,196, 196);
	gotoxy(10, 10);
	printf("Base gravable:");
	gotoxy(6, 10);
	printf("(=)");
	gotoxy(70,10);printf("%.2f",total);
	
	// LIIMITE INFERIOR
	
	if (total>0.01 && total<368.10) inf= 0.01;
	if (total>368.11 && total<3124.35) inf= 368.11;
	if (total>3124.36 && total<5490.75) inf= 3124.36;
	if (total>5490.76 && total<6382.80) inf= 5490.76;
	if (total>6382.81 && total<7641.90) inf= 6382.81;
	if (total>7641.91 && total<15412.80) inf= 7641.91;
	if (total>15412.81 && total<24292.65) inf= 15412.81;
	if (total>24292.66 && total<46378.50) inf= 24292.66;
	if (total>46378.51 && total<61838.10) inf= 46378.51;
	if (total>61838.11 && total<185514.30) inf= 61838.11;
	if(total>185514.31) inf= 185514.31;
		
		gotoxy(6, 11);
	printf("(+)");
	gotoxy(10, 11);
	printf("Limite Inferior:" );
	
	gotoxy(70,12);
	printf("%c%c%c%c%c%c%c%c", 196, 196,196, 196,196, 196,196, 196);
	
	gotoxy(70,11);printf("%.2f",inf);
	excedente=total-inf;
	gotoxy(6, 13);
	printf("(=)");
	gotoxy(10, 13);
	printf("Excedente:");
	gotoxy(70,13);printf("%.2f",excedente);
	
	// PORCENTAJE 
	if (total>0.01 && total<368.10) porcentaje= 1.91;
	if (total>368.11 && total<3124.35) porcentaje= 6.40;
	if (total>3124.36 && total<5490.75) porcentaje= 10.88;
	if (total>5490.76 && total<6382.80) porcentaje= 16;
	if (total>6382.81 && total<7641.90) porcentaje= 17.92;
	if (total>7641.91 && total<15412.80) porcentaje= 21.36;
	if (total>15412.81 && total<24292.65) porcentaje= 23.52;
	if (total>24292.66 && total<46378.50) porcentaje= 30;
	if (total>46378.51 && total<61838.10) porcentaje= 32;
	if (total>61838.11 && total<185514.30) porcentaje= 34;
	if(total>185514.31) porcentaje= 35;
	
	gotoxy(6, 14);
	printf("(*)");
	gotoxy(10, 14);
	printf("Porcentaje S/Limite Inferior:");
	
	gotoxy(70,14);printf("%.2f",37,porcentaje);
	
	gotoxy(70,15);
	printf("%c%c%c%c%c%c%c%c", 196, 196,196, 196,196, 196,196, 196);
	
	impuesto=(excedente*porcentaje)/100;
	gotoxy(6, 16);
	printf("(=)");
	gotoxy(10, 16);
	printf("Impuesto Marginal: ");
	gotoxy(70,16);printf("%.2f",impuesto);
	
	// CUOTAS FIJAS 
	if (total>0.01 && total<368.10) cuota= 0;
	if (total>368.11 && total<3124.35) cuota= 7.05;
	if (total>3124.36 && total<5490.75) cuota= 183.45;
	if (total>5490.76 && total<6382.80) cuota= 441;
	if (total>6382.81 && total<7641.90) cuota= 583.65;
	if (total>7641.91 && total<15412.80) cuota= 809.25;
	if (total>15412.81 && total<24292.65) cuota= 2469.15;
	if (total>24292.66 && total<46378.50) cuota= 4557.75;
	if (total>46378.51 && total<61838.10) cuota= 11183.40;
	if (total>61838.11 && total<185514.30) cuota= 16130.55;
	if(total>185514.31) cuota= 58180.35;
	
	gotoxy(6, 17);
	printf("(+)");
	gotoxy(10, 17);
	printf("Cuota Fija: ");
	
	gotoxy(70,17);printf("%.2f",cuota);
	cargo=impuesto+cuota;
	
	gotoxy(70,18);
	printf("%c%c%c%c%c%c%c%c", 196, 196,196, 196,196, 196,196, 196);
	gotoxy(6, 19);
	printf("(=)");
	gotoxy(10, 19);
	printf("Impuesto a Cargo:");
	gotoxy(70,19);printf("%.2f",cargo);
	
	//CREDITO
	if(sueldo>0.01 && sueldo<872.85) credito=200.85;
	if(sueldo>872.86 && sueldo<1309.20) credito=200.70;
	if(sueldo>1309.21 && sueldo<1713.60) credito=200.70;
	if(sueldo>1713.61 && sueldo<1745.70) credito=193.80;
	if(sueldo>1745.71 && sueldo<2193.75) credito=188.70;
	if(sueldo>2193.76 && sueldo<2327.55) credito=174.75;
	if(sueldo>2327.56 && sueldo<2632.65) credito=160.35;
	if(sueldo>2362.66 && sueldo<3071.40) credito=145.35;
	if(sueldo>3071.41 && sueldo<3510.15) credito=125.10;
	if(sueldo>3510.16 && sueldo<3642.60) credito=107.40;
	if(sueldo>3642.61) credito=0;
	
	gotoxy(6, 20);
	printf("(-)");
	gotoxy(10, 20);
	printf("Credito al salario:");
	gotoxy(70,20);printf("%.2f",130,credito);
	isr=cargo-credito;
		gotoxy(70,21);
	printf("%c%c%c%c%c%c%c%c", 196, 196,196, 196,196, 196,196, 196);
	gotoxy(6, 22);
	printf("(=)");
	gotoxy(10, 22);
	printf("Impuesto A Pagar:");
	gotoxy(70,22);printf("%.2f",isr);
	break;	
	}
		
	mostrarempresa();
	color(hConsole, 7);
	gotoxy(78,29);printf("Calcular otro ISR (Si[1] / No[0]): ");
	scanf("%d",&res);
	sleep(1);
	system("cls");		
	
}while(res != 0);
	
}


//SDI


void bienvenidaSDI() {
	mostrarempresa();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    margen(1, 3, 100, 25);
    margen(44, 8, 55, 10);
    margen(24, 3, 75, 5);
    color(hConsole, 6);
    gotoxy(35, 4);
    printf("CALCULADORA FISCAL DEL SDI FIJO");
    color(hConsole, 7);
    gotoxy(45, 9);
    color(hConsole, 11);
    printf("BIENVENIDO");
    color(hConsole, 7);
    gotoxy(40, 14);
}

void borrarSDI() {
    gotoxy(60, 25);
    printf("Presione una tecla para continuar...");
    getch();
    system("cls");
}

void calcularSDI(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    float sueldo, aguinaldo, primaV, SDI, factor, vac, porcentaje;
    int diasA, diasV;
    int tiempo;
    char nombre[100];
    int opcion;
		mostrarempresa();
        time_t tiempoActual;
        struct tm *infoTiempo;
        time(&tiempoActual);
        infoTiempo = localtime(&tiempoActual);

        gotoxy(3, 2);
        printf("Fecha: %02d/%02d/%04d\n", infoTiempo->tm_mday, infoTiempo->tm_mon + 1, infoTiempo->tm_year + 1900);
        bienvenidaSDI();
        color(hConsole, 11);
        borrarSDI();
		mostrarempresa();

    do {
    	mostrarempresa();
        margen(1, 3, 100, 25);
        gotoxy(3, 2);
        printf("Fecha: %02d/%02d/%04d\n", infoTiempo->tm_mday, infoTiempo->tm_mon + 1, infoTiempo->tm_year + 1900);
        color(hConsole, 13);
        color(hConsole, 7);
        margen(24, 3, 75, 5);
        color(hConsole, 6);
        gotoxy(25, 4);
        printf("CALCULADORA FISCAL DEL SDI FIJO");
        color(hConsole, 7);
        gotoxy(35, 10);
        color(hConsole, 11);
        printf("Menu");
        gotoxy(30, 12);
        printf("1. SDI con prestaciones minimas");
        gotoxy(30, 13);
        printf("2. SDI con prestaciones variables");
        margen(49, 17, 52, 19);
        gotoxy(50, 18);
        scanf("%d", &opcion);
        gotoxy(5, 22);
        printf("NOTA: Los datos de base para el calculo del SDI se encuentran en constante cambio anual.");
        gotoxy(15, 23);
        printf("Solicite la actualizacion de los datos en caso de ser necesario");
        borrarSDI();
        mostrarempresa();
        gotoxy(35, 10);
        color(hConsole, 13);
        color(hConsole, 7);
        margen(24, 3, 75, 5);
        color(hConsole, 6);
        gotoxy(25, 4);
        printf("CALCULADORA FISCAL DEL SDI FIJO");
        color(hConsole, 7);
        gotoxy(35, 10);
		mostrarempresa();
        switch (opcion) {
            case 1:
                margen(1, 3, 100, 25);
                gotoxy(35, 10);
                printf("Años trabajados: ");
                scanf("%d", &tiempo);
                gotoxy(35, 12);
                printf("Sueldo: ");
                scanf("%f", &sueldo);
                borrarSDI();
                mostrarempresa();
                if (tiempo == 1) {
                    vac = 12;
                } else if (tiempo == 2) {
                    vac = 14;
                } else if (tiempo == 3) {
                    vac = 16;
                } else if (tiempo == 4) {
                    vac = 18;
                } else if (tiempo == 5) {
                    vac = 20;
                } else if (tiempo >= 6 && tiempo <= 10) {
                    vac = 22;
                } else if (tiempo >= 11 && tiempo <= 15) {
                    vac = 24;
                } else if (tiempo >= 16 && tiempo <= 20) {
                    vac = 26;
                } else if (tiempo >= 21 && tiempo <= 25) {
                    vac = 28;
                } else if (tiempo >= 26 && tiempo <= 30) {
                    vac = 30;
                } else if (tiempo >= 31 && tiempo <= 35) {
                    vac = 32;
                }

                aguinaldo = (15 * sueldo) / 365;
                primaV = (vac * 0.25 * sueldo) / 365;
                SDI = sueldo + aguinaldo + primaV;
                factor = SDI / sueldo;
                margen(1, 3, 100, 25);
				mostrarempresa();
                margen(24, 3, 75, 5);
                color(hConsole, 6);
                gotoxy(25, 4);
                printf("CALCULADORA FISCAL DEL SDI FIJO");
                color(hConsole, 7);
                gotoxy(20, 11);
                printf("Sueldo:");
                gotoxy(60, 11);
                printf("%.3f", sueldo);

                gotoxy(16, 12);
                printf("(+) Aguinaldo diario: ");
                gotoxy(60, 12);
                printf("%.3f", aguinaldo);
                gotoxy(16, 13);
                printf("(+) Prima Vacacional:");
                gotoxy(60, 13);
                printf("%.3f", primaV);
                gotoxy(60, 14);
                printf("%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196);
                gotoxy(16, 15);
                printf("(=) SDI Fijo:");
                gotoxy(60, 15);
                printf("%.3f", SDI);
                gotoxy(20, 17);
                printf("Factor de Integracion:");
                gotoxy(60, 17);
                printf("%.4f", factor);
                borrarSDI();
                mostrarempresa();
                break;

            case 2:
            	mostrarempresa();
            	margen(1, 3, 100, 25);
                margen(24, 3, 75, 5);
                color(hConsole, 6);
                gotoxy(25, 4);
                printf("CALCULADORA FISCAL DEL SDI FIJO");
                color(hConsole, 7);
            	gotoxy(35, 10);
                printf("Sueldo Diario: ");
                scanf("%f", & sueldo);
                gotoxy(35, 11);
                printf ("Dias de aguinaldo: ");
                scanf("%d", &diasA );
                gotoxy(35, 12);
                printf ("Dias de vacaciones: ");
                scanf("%d", &diasV);
                gotoxy(35, 13);
                porcentaje=25;
                borrarSDI();
                mostrarempresa();
                margen(1, 3, 100, 25);
                margen(24, 3, 75, 5);
                color(hConsole, 6);
                gotoxy(25, 4);
                printf("CALCULADORA FISCAL DEL SDI FIJO");
                color(hConsole, 7);
                aguinaldo=(diasA*sueldo)/365;
                float por;
                por=porcentaje/100;
                primaV=(diasV*sueldo*por)/365;
                SDI=sueldo+aguinaldo+primaV;
                factor=SDI/sueldo;
                gotoxy(20, 11);
                printf("Sueldo ");
                gotoxy(60, 11);
                printf("%.3f", sueldo);
                gotoxy(16, 12);
                printf("(+) Aguinaldo diario ");
                gotoxy(60, 12);
                printf("%.3f", aguinaldo);
                gotoxy(16, 13);
                printf("(+) Prima Vacacional diaria: ");
                gotoxy(60, 13);
                printf("%.3f", primaV);
                gotoxy(60, 14);
                printf("%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196);
                gotoxy(16, 15);
                printf("(=) SDI");
                gotoxy(60, 15);
                printf("%.3f", SDI);
                gotoxy(20, 17);
                printf("Factor Integrado: ");
                gotoxy(60, 17);
                printf("%.4f", factor);
                borrarSDI();
                break;
        }

        // Preguntar si desea continuar
        mostrarempresa();
        margen(1, 3, 100, 25);
                margen(24, 3, 75, 5);
                color(hConsole, 6);
                gotoxy(25, 4);
                printf("CALCULADORA FISCAL DEL SDI FIJO");
                color(hConsole, 7);
        margen(34, 14, 65, 16);
        gotoxy(35, 15);
        printf("Desea continuar? 1: Si 0: No ");
        margen(49, 17, 52, 19);
        gotoxy(50, 18);
        scanf("%d", &opcion);
        borrarSDI();
    } while (opcion == 1);
    mostrarempresa();
    margen(1, 3, 100, 25);
    gotoxy(40, 15);
    printf("Saliendo del programa...");
    Sleep(1000);
    system("cls");
}


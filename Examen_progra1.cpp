#include <iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct {
    int codigo;
    char nombres[41];
    char apellidos[41];
    char puesto[41];
    float sueldoBase;
    float Bonificacion; 
   
    
} tEmpleado;


void continuar()
{
    printf("Presione una tecla para continuar\n\n");
    getch();
}

void crear()
{
    FILE *arch;
    arch=fopen("empleado.dat","wb");
    if (arch==NULL)
        exit(1);
    fclose(arch);
    continuar();
}


void cargar()
{
    FILE *arch;
    arch=fopen("empleado.dat","ab");
    if (arch==NULL)
        exit(1);
    tEmpleado Empleado;

    printf("Ingrese el codigo del empleado: ");
    scanf("%i",&Empleado.codigo);
    fflush(stdin);
    printf("Ingrese el nombre: ");
    gets(Empleado.nombres);
      printf("Ingrese el apellidos: ");
    gets(Empleado.apellidos);
      printf("Ingrese el Puesto: ");
    gets(Empleado.puesto);
    printf("Ingrese Sueldo base:");
    scanf("%f",&Empleado.sueldoBase);
    printf("Ingrese bonificacion :");
           scanf("%f",&Empleado.Bonificacion);
        
    fwrite(&Empleado, sizeof(tEmpleado), 1, arch);
    fclose(arch);
    continuar();
}

void listado()
{
    FILE *arch;
    arch=fopen("empleado.dat","rb");
    if (arch==NULL)
        exit(1);
    tEmpleado Empleado;
    fread(&Empleado, sizeof(tEmpleado), 1, arch);
    while(!feof(arch))
    {
       printf("_____________________\n\n codigo: %i\n nombres: %s \n apellidos: %s \n Puesto: %s\n Sueldo Base: %0.2f\n Bonificacion: %0.2f\n ", Empleado.codigo, Empleado.nombres,  Empleado.apellidos,  Empleado.puesto, Empleado.sueldoBase, Empleado.Bonificacion);
        fread(&Empleado, sizeof(tEmpleado), 1, arch);
    }
    fclose(arch);
    continuar();
    
}

void consulta()
{
    FILE *arch;
    arch=fopen("empleado.dat","rb");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo del empleado a consultar:");
    int cod;
    scanf("%i", &cod);
    tEmpleado Empleado;
    int existe=0;
    fread(&Empleado, sizeof(tEmpleado), 1, arch);
    while(!feof(arch))
    {
        if (cod==Empleado.codigo)
        {
        	  printf("_____________________\n\n");
            printf("codigo: %i\n nombres: %s \n apellidos: %s \n Puesto: %s\n Sueldo Base: %0.2f\n Bonificacion: %0.2f\n Sueldo total: %0.2f\n", Empleado.codigo, Empleado.nombres,  Empleado.apellidos,  Empleado.puesto, Empleado.sueldoBase, Empleado.Bonificacion);
          
			printf("_____________________\n\n");           
		   existe=1;
           break;
        }
        fread(&Empleado, sizeof(tEmpleado), 1, arch);
    }
    if (existe==0)
        printf("No existe el empleado con dicho codigo\n");
    fclose(arch);
    continuar();
}

void modificacion()
{
    FILE *arch;
    arch=fopen("empleado.dat","r+b");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo del empleado a modificar:");
    int cod;
    scanf("%i", &cod);
    tEmpleado Empleado;
    int existe=0;
    fread(&Empleado, sizeof(tEmpleado), 1, arch);
    while(!feof(arch))
    {
        if (cod==Empleado.codigo)
        {
        	
           printf("_____________________\n\n codigo: %i\n nombres: %s \n apellidos: %s \n Puesto: %s\n Sueldo Base: %0.2f\n Bonificacion: %0.2f\n ________________\n", Empleado.codigo, Empleado.nombres,  Empleado.apellidos,  Empleado.puesto, Empleado.sueldoBase, Empleado.Bonificacion);
            printf("Ingrese nuevo codigo: ");
            scanf("%i",&Empleado.codigo);
            printf("__________\n");
               gets(Empleado.nombres);
		   printf("Ingrese nuevos nombres: ");
            gets(Empleado.nombres);
             printf("\nIngrese nuevos apellidos: ");
        	gets(Empleado.apellidos);
             printf("\nIngrese nuevo puesto: ");
            gets(Empleado.puesto);
             printf("\nIngrese nuevo sueldo base: ");
     		 scanf("%f",&Empleado.sueldoBase);
           printf("\nIngrese nueva Bonificacion:");
            scanf("%f",&Empleado.Bonificacion);
           int pos=ftell(arch)-sizeof(tEmpleado);
           fseek(arch,pos,SEEK_SET);
           fwrite(&Empleado, sizeof(tEmpleado), 1, arch);
           printf("Se modificaron los datos.\n");
           existe=1;
           break;
        }
        fread(&Empleado, sizeof(tEmpleado), 1, arch);
    }
    if (existe==0)
        printf("No existe un empleado con dicho codigo\n");
    fclose(arch);
    continuar();
}
void eliminar()
{
	remove("empleado.dat");
	printf("Se elimino el archivo: empleado.dat\n");
}


int main()
{
    int opcion;
    do {
        printf("1 - Crear un archivo binario llamado \"empleado.dat\"\n");
        printf("2 - Carga de registros de tipo tEmpleado\n");
        printf("3 - Listado completo de Empleados.\n");
        printf("4 - Consulta de un Empleado por su codigo.\n");
        printf("5 - Modificar del Empleado. \n");
        printf("6 - Eliminar \n");
        printf("7 - Finalizar\n\n");
        printf("Ingrese su opcion:");
        scanf("%i",&opcion);
        switch (opcion) {
            case 1:crear();
                   break;
            case 2:cargar();
                   break;
            case 3:listado();
                   break;
            case 4:consulta();
                   break;
            case 5:modificacion();
                   break;
            case 6: eliminar();
					break;       
        }
    } while (opcion!=7);
    return 0;
}

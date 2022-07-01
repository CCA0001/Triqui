 //TRIQUI
 //Librerias utilizadas
#include <iostream>
#include <ctime>
#include <thread>
#include <stdlib.h>

using namespace std;
using std::this_thread::sleep_for;

//variables globales
char triqui[3][3];
int paso=0; 
int movimiento[]={};

//Prototipos de las funciones
void mostrar();
void reiniciar_tablero();
int introduccion();
bool dado();
void mov_jug();
void mov_bot(bool x, int paso);
void submenus();
void submenus2();
void procedimiento_default();
int mov_esquina_x();
int mov_borde_x();
void mov_esquina_opuesta();
void mov_esquina_adyacente(int esquina);
void esquina_restante(int esquina);
void casilla_random();
bool evitar_victoria();
bool aprovechar_victoria();
int victoria();
void jugar_again();

int main()
{   
    int ganador, estrategia;
    introduccion();
    reiniciar_tablero();
    estrategia=dado();
    sleep_for(2s);
    if(estrategia==0)
    {
        mov_bot(estrategia,paso);
        mostrar();
    }
    do
    {
    mov_jug();
    mostrar();
    mov_bot(estrategia,paso);
    mostrar();
    ganador=victoria();
    }
    while(ganador==4);
    jugar_again();
}

//Muestra el tablero actual, con los movimientos que se hayan hecho hasta el momento
void mostrar()
{
    int i, j;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
        cout << " | " << triqui[i][j];
        }
    cout << " | " << endl;
    cout << " | --------- |" << endl;
    }
}

//Vuelve el tablero a ceros, en caso de jugar otra partida
void reiniciar_tablero()
{
    int i, j;
    char k;
    k='1';
    
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
        {
        triqui[i][j]=k;
        k++;
        }
    mostrar();
}

//Le da la bienvenida al jugador
int introduccion()
{
    bool prep;
    cout << "BIENVENIDO AL JUEGO DEL MICHI!" << endl;
    sleep_for(1s);
    cout << "A continuacion, el que inicia el juego sera decidido por un lanzamiento de dado aleatorio, preparado/a/e?" << endl;
    sleep_for(1s);
    cout << "Lanzar?  0=NO   1=SI "; cin >> prep;
    if(prep==1)
    {
        return 0;
    }
            else
            {
            cout << "Lastima, regrese cuando quiera!";
            sleep_for(2s);
            exit(0);
            }
}

//Realiza el lanzamiento del dado
bool dado()
{
    int num_jug, num_bot;
    srand(time(NULL));
    cout << "Numero jugador: ";
    num_jug= 1 + rand() % 6;
    cout << num_jug << endl;
    
    cout << "Numero bot: ";
    num_bot= 1 + rand() % 6;
    cout << num_bot << endl;
    
    //En caso de que los numeros den igual
    while(num_jug==num_bot)
    {
    cout << "Los numeros han dado igual! Reiniciando lanzamiento..." << endl;
    sleep_for(1s);
    cout << "Numero jugador: ";
    num_jug= 1 + rand() % 6;
    cout << num_jug << endl;
    
    cout << "Numero bot: ";
    num_bot= 1 + rand() % 6;
    cout << num_bot << endl; 
    }
    
    //Determina qué numero es mayor y a su vez, quien iniciará la partida
    if(num_jug>num_bot)
    {
    cout << "Has sacado el numero mayor! Seras capaz de iniciar el juego" << endl;
    return 1;
    }
        else
        {
        cout << "El bot ha sacado el numero mayor! Tendras que esperar tu turno" << endl << endl;
        return 0;
        }
}

void mov_jug()
{
    int casilla, i;
    cout << "Es su turno, realice su movimiento ";
    cin >> casilla;
    
    //Según el numero ingresado, se hará la comprobación de la casilla en cuestión y si está vacia, será llenada con la 'X' correspondiente
    switch(casilla)
    {
    case 1:
    	if(triqui[0][0]=='1')
    	{
        triqui[0][0]='X';
        return;
    	}
        break;
    case 2:
    	if(triqui[0][1]=='2')
    	{
        triqui[0][1]='X';
        return;
    	}
        break;
    case 3:
    	if(triqui[0][2]=='3')
    	{
        triqui[0][2]='X';
        return;
    	}
        break;
    case 4:
    	if(triqui[1][0]=='4')
    	{
        triqui[1][0]='X';
        return;
    	}
        break;
    case 5:
    	if(triqui[1][1]=='5')
    	{
        triqui[1][1]='X';
        return;
    	}
        break;
    case 6:
    	if(triqui[1][2]=='6')
    	{
        triqui[1][2]='X';
        return;
    	}
        break;
    case 7:
    	if(triqui[2][0]=='7')
    	{
        triqui[2][0]='X';
        return;
    	}
        break;
    case 8:
    	if(triqui[2][1]=='8')
    	{
        triqui[2][1]='X';
        return;
    	}
        break;
    case 9:
    	if(triqui[2][2]=='9')
    	{
        triqui[2][2]='X';
        return;
    	}
        break;
    default:
    	//En caso de que se ingrese un numero diferente...
    	cout << "Solo numeros de 1 a 9" << endl;
    	break;
    }
    //En caso de que la casilla selecciona ya esté ocupada...
    cout << "La casilla que eligio ya está ocupada, seleccione otra." << endl;
    mov_jug();
    
    return;
}

void mov_bot(bool x, int paso)
{
    cout << "Es turno de la maquina, por favor espere..." << endl << endl;
    sleep_for(2s);
    
    //Switch que decide la estrategia, segun quien haya iniciado la partida
    switch(x)
    {
        case 0:
            submenus();
            break;
        case 1:
            submenus2();
            break;
    }
    return;
}

//Si la partida fue iniciada por la maquina
void submenus()
{
    int i, aux;
    switch(paso)
    {
        case 0:
            movimiento[0]=mov_esquina_x();
            break;
        case 1:
            if(triqui[1][1]=='X')
            {
                movimiento[1]=1;
                mov_esquina_opuesta();
                break;
            }
            else
            {
                movimiento[1]=2;
                mov_esquina_adyacente(movimiento[0]);
                break;
            }
        case 2:
            switch(movimiento[1])
            {
                case 1:
                evitar_victoria();
                break;
                case 2:
                i=aprovechar_victoria();
                if(i==1)
                {
                    break;
                }
                triqui[1][1]='O';
                break;
                case 3:
                i=aprovechar_victoria();
                if(i==1)
                {
                    break;
                }
                esquina_restante(movimiento[0]);
                break;
            }
            break;
        case 3:
        	procedimiento_default();
        	break;
        case 4:
			procedimiento_default();
			break;
        case 5:
			procedimiento_default();
			break;
    }
    paso=paso+1;
    return;
}

//Si la partida fue iniciada por el jugador
void submenus2()
{
    int i, aux;
    switch(paso)
    {
        case 0:
        if(triqui[1][1]=='X')
        {
            movimiento[0]=1;
            aux=mov_esquina_x();
            break;
        }
        movimiento[0]=2;
        triqui[1][1]='O';
        break;
        case 1:
            switch(movimiento[0])
            {
                case 1:
                i=evitar_victoria();
                if(i==1)
                {
                    break;
                }
                mov_esquina_x();
                break;
                case 2:
                i=evitar_victoria();
                if(i==1)
                {
                    break;
                }
                if(triqui[0][0]=='X' or triqui[0][2]=='X' or triqui[2][0]=='X' or triqui[2][2]=='X')
                {
                    mov_borde_x();
                    break;
                }
                if(triqui[0][1]=='X' and triqui[2][1]=='X' or triqui[1][0]=='X' and triqui[1][2]=='X')
                {
                    mov_esquina_x();
                    break;
                }
                casilla_random();
                break;
            }
            break;
        case 2:
			procedimiento_default();
			break;
        case 3:
			procedimiento_default();
			break;
        case 4:
			procedimiento_default();
			break;
    }
    paso=paso+1;
    return;
}

void procedimiento_default()
{
	int i;
    i=aprovechar_victoria();
    if(i==1)
    {
        return;
    }
    i=evitar_victoria();
    if(i==1)
    {
        return;
    }
    casilla_random();
    return;
}

//La maquina llena una esquina aleatoria
int mov_esquina_x()
{
    int esquina;
    //Se decide la esquina 
    esquina=1+rand()%4;
    switch(esquina)
    {
        case 1:
        if(triqui[0][0]=='1')
        {
            triqui[0][0]='O';
            return esquina;
        }
        break;
        case 2:
        if(triqui[0][2]=='3')
        {
            triqui[0][2]='O';
            return esquina;
        }
        break;
        case 3:
        if(triqui[2][0]=='7')
        {
            triqui[2][0]='O';
            return esquina;
        }
        break;
        case 4:
        if(triqui[2][2]=='9')
        {
            triqui[2][2]='O';
            return esquina;
        }
        break;
    }
    //En caso de que la esquina elegida ya esté llena
    mov_esquina_x();
    return esquina;
}

//La maquina llena un borde aleatorio
int mov_borde_x()
{
    int borde;
    //Se decide el borde
    borde=1+rand()%4;
    switch(borde)
    {
        case 1:
        if(triqui[0][1]=='2')
        {
            triqui[0][1]='O';
            return borde;
        }
        break;
        case 2:
        if(triqui[1][0]=='4')
        {
            triqui[1][0]='O';
            return borde;
        }
        break;
        case 3:
        if(triqui[1][2]=='6')
        {
            triqui[1][2]='O';
            return borde;
        }
        break;
        case 4:
        if(triqui[2][1]=='8')
        {
            triqui[2][1]='O';
            return borde;
        }
        break;
    }
    //En caso de que el borde elegido ya esté lleno
    mov_borde_x();
    return borde;
}

//La maquina llena la casilla opuesta a la generada anteriormente
void mov_esquina_opuesta()
{
    switch(movimiento[0]) //Siempre se utiliza "movimiento[0]" debido a que esta función solo es utilizada al inicio de la partida, cuando la maquina solo ha hecho un movimiento
    {
        case 1:
            triqui[2][2]='O';
            break;
        case 2:
            triqui[2][0]='O';
            break;
        case 3:
            triqui[0][2]='O';
            break;
        case 4:
            triqui[0][0]='O';
            break;
    }
    return;
}

//La maquina llena la esquina adyacente a la ingresada, que a su vez no se encuentre con una ficha enemiga de por medio
void mov_esquina_adyacente(int esquina) 
{
    switch(esquina)
    {
        case 1:
            if(triqui[0][1]=='X')
            {
                triqui[2][0]='O';
                break;
            }
            else if(triqui[1][0]=='X')
            {
                triqui[0][2]='O';
                break;
            }
            break;
            
        case 2:
            if(triqui[0][1]=='X')
            {
                triqui[2][2]='O';
                break;
            }
            else if(triqui[1][2]=='X')
            {
                triqui[0][0]='O';
                break;
            }
            break;
        case 3:
            if(triqui[1][0]=='X')
            {
                triqui[2][2]='O';
                break;
            }
            else if(triqui[2][1]=='X')
            {
                triqui[0][0]='O';
                break;
            }
            break;
        case 4:
            if(triqui[1][2]=='X')
            {
                triqui[2][0]='O';
                break;
            }
            else if(triqui[2][1]=='X')
            {
                triqui[0][2]='O';
                break;
            }
            break;
    }
    //En caso de no haber...
    esquina_restante(esquina);
    return;
}

//Busca y llena una esquina vacia según la ingresada y el resto de casillas que se encuentren ocupadas
void esquina_restante(int esquina)
{
    int esquina2=1+rand()%2;
    switch(esquina)
    {
        case 1:
        if(triqui[2][2]!='9')
        {
            switch(esquina2)
            {
                case 1:
                    if(triqui[0][2]=='3')
                    {
                        triqui[0][2]='O';
                        return;
                    }
                    triqui[2][0]='O';
                    return;
                case 2:
                    if(triqui[2][0]=='7')
                    {
                        triqui[2][0]='O';
                        return;
                    }
                    triqui[0][2]='O';
                    return;
            }
        }
        triqui[2][2]='O';
        break;
        case 2:
        if(triqui[2][0]!='7')
        {
            switch(esquina2)
            {
                case 1:
                    if(triqui[0][0]=='1')
                    {
                        triqui[0][0]='O';
                        return;
                    }
                    triqui[2][2]='O';
                    return;
                case 2:
                    if(triqui[2][2]=='9')
                    {
                        triqui[2][2]='O';
                        return;
                    }
                    triqui[0][0]='O';
                    return;
            }
        }
        triqui[2][0]='O';
        return;
        case 3:
        if(triqui[0][2]!='3')
        {
            switch(esquina2)
            {
                case 1:
                    if(triqui[0][0]=='1')
                    {
                        triqui[0][0]='O';
                        return;
                    }
                    triqui[2][2]='O';
                    return;
                case 2:
                    if(triqui[2][2]=='9')
                    {
                        triqui[2][2]='O';
                        return;
                    }
                    triqui[0][0]='O';
                    return;
            }
        }
        triqui[0][2]='O';
        return;
        case 4:
        if(triqui[0][0]!='1')
        {
            switch(esquina2)
            {
                case 1:
                    if(triqui[0][2]=='3')
                    {
                        triqui[0][2]='O';
                        return;
                    }
                    triqui[2][0]='O';
                    return;
                case 2:
                    if(triqui[2][0]=='7')
                    {
                        triqui[2][0]='O';
                        return;
                    }
                    triqui[0][2]='O';
                    return;
            }            
        }
        triqui[0][0]='O';
        return;
    }
    return;
}

//La maquina llena la primera casilla que encuentre vacía
void casilla_random()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(triqui[i][j]!='X' and triqui[i][j]!='O')
            {
                triqui[i][j]='O';
                return;
            }
        }
    }
    return;
    
}

//La maquina evalua una posible derrota y la bloquea
bool evitar_victoria()
{
	int i1,i2=1,i3=2,j;
	
	//Evaluacion Horizontal
	for(j=0;j<3;j++)
	{
		for(i1=0;i1<3;i1++)
		{
			if(triqui[j][i1]=='X' and triqui[j][i2]=='X' and triqui[j][i3]!='X' and triqui[j][i3]!='O')
			{
				triqui[j][i3]='O';	
				return 1;
			}
			i2++;
			i3++;
			if(i3==3)
			{
				i3=0;
			}
			else if(i2==3)
			{
				i2=0;
			}
		}
		i2=1;
		i3=2;
	}
	
	//Evaluación Vertical	
	for(j=0;j<3;j++)
	{
		for(i1=0;i1<3;i1++)
		{
			if(triqui[i1][j]=='X' and triqui[i2][j]=='X' and triqui[i3][j]!='X' and triqui[i3][j]!='O')
			{
				triqui[i3][j]='O';	
				return 1;
			}
			i2++;
			i3++;
			if(i3==3)
			{
				i3=0;
			}
			else if(i2==3)
			{
				i2=0;
			}
		}
		i2=1;
		i3=2;
	}
	
	//Evaluación Slash 
	for(i1=0;i1<3;i1++)
	{
		if(triqui[i1][i1]=='X' and triqui[i2][i2]=='X' and triqui[i3][i3]!='X' and triqui[i3][i3]!='O')
		{
			triqui[i3][i3]='O';	
			return 1;
		}
		i2++;
		i3++;
		if(i3==3)
		{
			i3=0;
		}
		else if(i2==3)
		{
			i2=0;
		}
	}

	//Evaluacion Backslash
    if(triqui[0][2]=='X' and triqui[1][1]=='X' and triqui[2][0]=='7')
    {
        triqui[2][0]='O';
        return 1;
    }
    if(triqui[1][1]=='X' and triqui[2][0]=='X' and triqui[0][2]=='3')
    {
        triqui[0][2]='O'; 
        return 1;
    }
    if(triqui[0][2]=='X' and triqui[2][0]=='X' and triqui[1][1]=='5')
    {
        triqui[1][1]='O'; 
        return 1;
    }
    return 0;
}

//La maquina evalua una posible victoria y la completa
bool aprovechar_victoria()
{
	int i1,i2=1,i3=2,j;
	
	//Evaluacion Horizontal
	for(j=0;j<3;j++)
	{
		for(i1=0;i1<3;i1++)
		{
			if(triqui[j][i1]=='O' and triqui[j][i2]=='O' and triqui[j][i3]!='X' and triqui[j][i3]!='O')
			{
				triqui[j][i3]='O';	
				return 1;
			}
			i2++;
			i3++;
			if(i3==3)
			{
				i3=0;
			}
			else if(i2==3)
			{
				i2=0;
			}
		}
		i2=1;
		i3=2;
	}
	
	//Evaluación Vertical
	for(j=0;j<3;j++)
	{
		for(i1=0;i1<3;i1++)
		{
			if(triqui[i1][j]=='O' and triqui[i2][j]=='O' and triqui[i3][j]!='X' and triqui[i3][j]!='O')
			{
				triqui[i3][j]='O';	
				return 1;
			}
			i2++;
			i3++;
			if(i3==3)
			{
				i3=0;
			}
			else if(i2==3)
			{
				i2=0;
			}
		}
		i2=1;
		i3=2;
	}
	
	//Evaluación Slash
	for(i1=0;i1<3;i1++)
	{
		if(triqui[i1][i1]=='O' and triqui[i2][i2]=='O' and triqui[i3][i3]!='X' and triqui[i3][i3]!='O')
		{
			triqui[i3][i3]='O';	
			return 1;
		}
		i2++;
		i3++;
		if(i3==3)
		{
			i3=0;
		}
		else if(i2==3)
		{
			i2=0;
		}
	}

	//Evaluación BackSlash
    if(triqui[0][2]=='O' and triqui[1][1]=='O' and triqui[2][0]=='7')
    {
        triqui[2][0]='O';
        return 1;
    }
    if(triqui[1][1]=='O' and triqui[2][0]=='O' and triqui[0][2]=='3')
    {
        triqui[0][2]='O'; 
        return 1;
    }
    if(triqui[0][2]=='O' and triqui[2][0]=='O' and triqui[1][1]=='5')
    {
        triqui[1][1]='O'; 
        return 1;
    }
    return 0;
}

//Evalua todas las posibilidades en busca de una victoria y muestra al ganador en consola
int victoria()
{
	//Tres en raya horizonal y vertical del jugador
	for(int i=0;i<3;i++)
	{	
		if(triqui[i][0]=='X' and triqui[i][1]=='X' and triqui[i][2]=='X'
		or triqui[0][i]=='X' and triqui[1][i]=='X' and triqui[2][i]=='X')
		{
			cout << "¡JUGADOR GANA!" << endl;
			sleep_for(5s);
			return 1;
		}
	}
	if
	(
        //Tres en raya diagonal del jugador
        triqui[0][0]=='X' and triqui[1][1]=='X' and triqui[2][2]=='X'
        or 
        triqui[0][2]=='X' and triqui[1][1]=='X' and triqui[2][0]=='X'
        )
        {
            cout << "¡JUGADOR GANA!" << endl;
			sleep_for(5s);
            return 1;
        }
    
    //Tres en raya horizontal y vertical de la maquina
	for(int i=0;i<3;i++)
	{	
		if(triqui[i][0]=='O' and triqui[i][1]=='O' and triqui[i][2]=='O'
		or triqui[0][i]=='O' and triqui[1][i]=='O' and triqui[2][i]=='O')
		{
			cout << "¡BOT GANA!" << endl;
			sleep_for(5s);
			return 0;
		}
	}
       
    if
    (
        //Tres en raya diagonal de la maquina
        triqui[0][0]=='O' and triqui[1][1]=='O' and triqui[2][2]=='O'
        or 
        triqui[0][2]=='O' and triqui[1][1]=='O' and triqui[2][0]=='O'
        )
        {
            cout << "!BOT GANA!" << endl;
			sleep_for(5s);
            return 0;
        }
        
        //Evalua si hay casillas vacias para que el juego continue
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(triqui[i][j]!='X' and triqui[i][j]!='O')
                return 4;
            }
        }
        //En caso contrario, se declara un empate
        cout << "ES UN EMPATE!" << endl;
		sleep_for(5s);
        return 3;
}

void jugar_again()
{
	bool jugar;
	cout << "Desea jugar nuevamente?" << endl;
	cout << "Si=1      NO=0 "; cin >> jugar;
	
	if (jugar==1)
	{
		system("cls");
		main();
	}
	else 
	{
		cout << "Gracias por acompaniarnos! Tenga un buen dia <3" << endl;
		sleep_for(1s);
		exit(0);
	}
}


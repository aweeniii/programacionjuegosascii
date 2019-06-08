#include<stdio.h>
/*la funcion de impresion de caracteres de esta biblioteca nos pide emplear el codigo ASCII, de modo que accedemos a caracteres que no hay en iostream*/
#include<windows.h>
/*entre sus funciones se encuentra la posibilidad de posicionar objetos y caracteres en los lugares que deseemos, usando coordenadas cartesianas (X,Y)*/
#include<conio.h>
/*esta biblioteca tiene facilidad para detectar cuando una tecla fue presionada, de modo que va a ser util para dirigir el puntero con las teclas*/
#include<stdlib.h>
#include<list>

using namespace std; 

#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77
/*estas definiciones se van a usar para ocupar las flechas como direccionales. Los numeros refieren a la numeracion que cada tecla del teclado tiene*/

void gotoxy (int x, int y) {
	/*estos parametros sirven para llamar a las coordenadas en xyPos.X y xyPos.Y*/
	HANDLE vJue;
	/*es el identificador para la ventana donde se va a ejecutar el programa, esto permite que SetConsoleCursorPosition funcione*/
	vJue=GetStdHandle (STD_OUTPUT_HANDLE);
	/*nos permitira recuperar el identificador de la consola, su posicion estandar de salida nos da control de la salida de la consola*/
	COORD xyPos;
	/*estructura que viene definida en la biblioteca <windows.h>, utilizados como parï¿½metros en SetConsoleCursorPosition, funcionan como
	coordenadas (X, Y) del cursor y son necesarios para poder moverlos*/
	xyPos.X = x;
	xyPos.Y = y;
	/*se llama a los atributos de xyPos con el punto y se le asinga un valor en cada coordenada que posee (X,Y). Deben estar en mayï¿½suculas*/
	SetConsoleCursorPosition(vJue, xyPos);
	/*funcion de <windows.h> que nos permite dar una posicion al cursor e imprimir lo que se desee en esas coordenadas
	cuando se coloco VJue y xyPos lo que se hizo fue dar el control de la consola, pasarle coordenadas y entonces imprime sobre la consola
	el cursor en las coordenadas que se le atribuyeron.*/
}
	/*la funcion gotoxy es de tipo void porque no nos regresa ningun tipo de datos, simplemente realiza una accion. Se utiliza windows.h*/
void OcultarCursor(){
	/*esta funcion va a hacer que desaparezca el cursor parpadeante de al lado y se vea mas wonito todo*/
	HANDLE vJue;
	/*es el identificador para la ventana donde se va a ejecutar el programa, esto permite que SetConsoleCursorInfo funcione*/
	vJue=GetStdHandle (STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	/*esta estructura permite controlar el tamaï¿½o y la visibilidad del cursor*/
	cci.dwSize = 100;
	/*este es el tamaño que se le da al cursor*/
	cci.bVisible = false;
	//*con esto se vuelve invisible el cursor*/
	SetConsoleCursorInfo(vJue, &cci);
}

class PERSONAJE{
	int x, y;
	/*son sus coordenadas
	estos atributos son privados y no se pueden emplear fuera de la clase*/
	int corazones;
	int vidas;
public:
	/*los atributos colocados aca se pueden ocupar fuera de la clase*/
	//*esto es un constructor, sirve para poder llamar a las caracterï¿½sticas privadas que tiene la clase fuera de ella*//
	PERSONAJE (int _x, int _y, int _corazones, int _vidas): x(_x), y(_y), corazones(_corazones), vidas(_vidas) {}
	int X(){return x;}
	int Y(){return y;}
	void pintar();
	//*este es para darle forma al personaje*//
	void borrar();
	//*esto es para que no se quede el rastro del personaje*//
	void mover();
	//*se va a ocupar para direccionar al personaje*//
	void corazones_contador();
	//*con esta funcion se va a crear en la interfaz un espacio para los corazones (vitalidad)*//
	void vidas_contador();
	//*con esta funcion se va a crear en la interfaz un espacio para el contador de vidas*//
	void muerte();
	//*esta funcion es para que suceda la muerte despues de que todos los puntos de vitalidad se pierden*//
	void cora() {corazones=corazones-1;}
	//*esta funcion reduce en uno cada punto de vitalidad al ser tocado por un blanco*//
	int vid(){return vidas;}
	//*esta funcion nos devuelve el valor vida (la cantidad de vidas) que tiene el personaje, porque ese dato es privado*//
};

void PERSONAJE::pintar () {
	//*se escribe asïi porque es una funcion que se ocupa desde la clase PERSONAJE*//
	gotoxy (x, y); printf ("%c %c %c", 153, 202, 153);
	gotoxy (x, y+1); printf ("  %c", 94);
	//*son las coordenadas y los caracteres que forman al personaje*/
}

void PERSONAJE::borrar (){
	gotoxy (x,y); printf ("      ");
	gotoxy (x, y+1); printf ("      ");
//*son espacios en la posicion del personaje que evitan la presencia del rastro del mismo con cada movimiento*//
}
void PERSONAJE::mover (){
	if(kbhit()){
		/*la funcion kbhit es la encargada de detectar que las teclas se presionan*/
		char tecla = getch();
		/*la funcion getch se encarga de guardar las teclas que se presionen*/
		borrar();
		/*esto es util para que los caracteres no dejen rastro, se vuelve a llamar a las coordenadas para evitar su desaparicion y se
		añade un espacio en blanco que se va a encargar de borrar lo que antes fue impreso y asi continuamente*/
		if (tecla == IZQUIERDA && x>3) x--;
		if (tecla == DERECHA && x+4<116) x++;
		if (tecla == ARRIBA && y>7) y--;
		if (tecla == ABAJO && y+2<32) y++;
		/*iguala al char tecla a cada una de las definidas al comienzo con el numero al que corresponde las flechas y mueve al personaje en
		funcion del sistema de coordenadas X e Y. Ademas estan agregados los limites para el movimiento, de modo que no pueda ir mas alla de
		los que estan establecidos por la interfaz*/
		pintar();}
	OcultarCursor();
	corazones_contador();
	vidas_contador();
	muerte();
	//*se llama a estas funciones para que tengan su utilidad sea la correcta*//
}
void PERSONAJE::corazones_contador(){
	gotoxy (95, 5); printf ("Vitalidad: ");
	gotoxy (105, 5); printf ("      ");
	int i;
	for (i=0; i<corazones; i++){
		//*este bucle es para que aparezca la cantidad de corazones correcta*//
		gotoxy (105+i, 5); printf ("%c ", 208);
	}
}
void PERSONAJE::vidas_contador(){
	gotoxy(70, 5); printf ("Vidas: ");
	gotoxy (76,5); printf ("  ");
	int i;
	for (i=0; i<vidas; i++){
		//*este bucle es para que aparezca la cantidad de vidas correcta*//
		gotoxy (76+i, 5); printf ("%c ", 228);
	}
}
void PERSONAJE::muerte(){
	if (corazones == 0){
		corazones=corazones+5;
		vidas=vidas-1;
		borrar();
		gotoxy (x, y); printf ("%c %c %c", 157, 202, 157);
		gotoxy (x, y+1); printf ("  %c", 158);
		Sleep (500);
		borrar ();
		pintar();
	}
}
class BLANCOS{
	int x, y;
public:
	BLANCOS(int _x, int _y):x(_x), y(_y) {}
	//*esto es para poder utilizar las coordenadas de los blancos*//
	void pintar();
	//*funcion para que aparezcan los blancos*//
	void mover();
	//*funcion para que se muevan los blancos*//
	void choque (class PERSONAJE &N);
	//*funcion para detectar el choque del personaje con los blancos, esta con parametros del personaje para que funcione jajasalu2*//
	int X() {return x;}
	int Y() {return y;}
	//*esto es para que devuelva el valor de las coordenas*//
};
void BLANCOS::pintar() {
	gotoxy (x, y); printf ("%c", 145);
}
void BLANCOS::mover(){
	gotoxy (x,y); printf (" ");
	y++;
	if (y>31){
		x=rand()%90+8;
		//*esto es para que tire un valor aleatorio dentro de los limites de la interfaz*//
		y=7;
	}
	pintar();
}
void BLANCOS::choque (class PERSONAJE &N){
	if (x >= N.X() && x <= N.X()+5 && y >= N.Y() && y <= N.Y()+6){
		N.cora();
		N.borrar();
		N.corazones_contador();
		N.pintar();
	}
}
void interfaz_limites(){
	int lim;
	for (lim=2;lim<118;lim++){
		gotoxy (lim,6); printf ("%c", 178);
		gotoxy (lim, 33); printf ("%c", 178);
	}
	for (lim=6; lim<34; lim++){
		gotoxy (2, lim); printf ("%c", 178);
		gotoxy (118, lim); printf ("%c", 178);
	}
}

class DISPAROS {
	int x, y;
public:
	DISPAROS (int _x, int _y): x (_x), y (_y) {}
	int X() {return x;}
	int Y() {return y;}
	void movimiento();
	bool eliminacion();
};
void DISPAROS::movimiento(){
	gotoxy (x,y); printf (" ");
	y--;
	gotoxy (x,y); printf ("%c", 193);
}
bool DISPAROS::eliminacion(){
	if (y==7) return true;
	return false;
}
int main (){
	interfaz_limites();
	OcultarCursor();
	PERSONAJE N(55, 30, 5, 3);
	N.pintar();

	list <DISPAROS*> D;
	list <DISPAROS*>:: iterator itD;
	
	list <BLANCOS*> B;
	list <BLANCOS*>:: iterator itB;
	
	for(int i=0; i<7; i++){
		B.push_back(new BLANCOS(rand()%90+3, rand()%5+7));
	}
	
	bool game_over = false;
	int puntos;
	//*es el contador de puntos*//
	puntos=0;
	while (!game_over) {
		/*la condicion es que se ejecute siempre que gameover sea falso*/
		
		if (kbhit()){
			char tecla = getch ();
			if (tecla == 'd')
				D.push_back(new DISPAROS(N.X()+2, N.Y()-1));
		}
		//*es la condicion para disparar*//
		
		for (itD = D.begin(); itD!=D.end(); itD++) {
			(*itD)-> movimiento();
			if((*itD)->eliminacion()) {
				gotoxy ((*itD)->X(), (*itD)->Y()); printf (" ");
				delete (*itD);
				itD=D.erase(itD);
			}
		}
		//*es el bucle para la eliminacion de los disparos*//
		
		for (itB = B.begin(); itB != B.end(); itB++){
			(*itB)->mover();
			(*itB)->choque(N);
		}
		//*es el bucle para el choque*//
		for (itB = B.begin(); itB != B.end(); itB++){
			for (it=D.begin(); it !=D.end(); it++){
				if ((*itB)->X() == (*it)->X() && ( (*itB)->Y()+1 == (*it)->Y() || (*itB)->Y() == (*it)-> Y() )){
					gotoxy ((*it)->X(), (*it)->Y()); printf (" ");
					delete (*itB);
					it=D.erase(it);
					
					B.push_back(new BLANCOS (rand()%90+3, 7) );
					gotoxy ((*itB)->X(), (*itB)->Y()); printf (" ");
					delete (*itB);
					itB=B.erase(itB);
					puntos=puntos+5;
					
				}
			}
		}
		//*es el bucle para que el choque entre las balas y los blancos y sume puntos*//
		
		if (N.vid() == 0) {
			game_over=true;
			gotoxy (53,20); printf ("GAME OVER");
			Sleep (1000);
		}
		//*es para que valide el final*//
		if (puntos==30){
		//*se recomienda que se reduzca la condicion para hacer pruebas*//
			game_over=true;
			gotoxy (53,20); printf ("WIN");
		}
		//*es para que valide la victoria*//
		gotoxy (5, 5); printf ("Puntuacion: %d", puntos);
		//*funciona para poner en la interfaz la parte de puntuacion*//
		gotoxy (30, 5 ); printf ("GOAL: 500");
		//*es para que se tengan en cuenta los puntos necesarios para ganar*//
		
		N.mover();
		N.muerte();
		
		Sleep (80);
		/*esto ayuda a que el procesador no se sature al ejecutar el bucle, porque la iteraciï¿½n es muy intensa al repetir estas acciones*/
		}

	return (0);
}

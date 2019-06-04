#include<stdio.h>
/*la funci�n de impresi�n de caracteres de esta biblioteca nos pide emplear el c�digo ASCII, de modo que accedemos a caracteres que no hay en iostream*/
#include<windows.h>
/*entre sus funciones se encuentra la posibilidad de posicionar objetos y caracteres en los lugares que deseemos, usando coordenadas cartesianas (X,Y)*/
#include<conio.h>
/*esta biblioteca tiene facilidad para detectar cuando una tecla fue presionada, de modo que va a ser �til para dirigir el puntero con las teclas*/
#include<stdlib.h>
#include<list>

using namespace std;


#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77
/*estas definiciones se van a usar para ocupar las flechas como direccionales. Los numeros refieren a la numeraci�n que cada tecla del teclado tiene*/


void gotoxy (int x, int y) {
	/*estos par�metros sirven para llamar a las coordenadas en xyPos.X y xyPos.Y*/


	HANDLE vJue;
	/*es el identificador para la ventana donde se va a ejecutar el programa, esto permite que SetConsoleCursorPosition funcione*/

	vJue=GetStdHandle (STD_OUTPUT_HANDLE);
	/*nos permitir� recuperar el identificador de la consola, su posici�n est�ndar de salida nos da control de la salida de la consola*/

	COORD xyPos;
	/*estructura que viene definida en la biblioteca <windows.h>, utilizados como par�metros en SetConsoleCursorPosition, funcionan como
	coordenadas (X, Y) del cursor y son necesarios para poder moverlos*/
	xyPos.X = x;
	xyPos.Y = y;
	/*se llama a los atributos de xyPos con el punto y se le asinga un valor en cada coordenada que posee (X,Y). Deben estar en may�suculas*/


	SetConsoleCursorPosition(vJue, xyPos);
	/*funci�n de <windows.h> que nos permite dar una posici�n al cursor e imprimir lo que se desee en esas coordenadas
	cuando se coloc� VJue y xyPos lo que se hizo fue dar el control de la consola, pasarle coordenadas y entonces imprime sobre la consola
	el cursor en las coordenadas que se le atribuyeron.*/

}
	/*la funci�n es de tipo void porque no nos regresa ning�n tipo de datos, simplemente realiza una acci�n. Se utiliza la biblioteca windows.h*/


void OcultarCursor(){
	/*esta funci�n va a hacer que desaparezca el cursor parpadeante de al lado y se vea m�s wonito todo*/

	HANDLE vJue;
	/*es el identificador para la ventana donde se va a ejecutar el programa, esto permite que SetConsoleCursorInfo funcione*/
	vJue=GetStdHandle (STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	/*esta estructura permite controlar el tama�o y la visibilidad del cursor*/
	cci.dwSize = 100;
	cci.bVisible = false;
	SetConsoleCursorInfo(vJue, &cci);
}

class PERSONAJE{
	int x, y;
	/*son sus coordenadas
	estos atributos son privados y no se pueden emplear fuera de la clase*/
	int corazones;
	int vidas;

public:
	/*los atributos colocados ac� se pueden ocupar fuera de la clase*/

	//*esto es un constructor, sirve para poder llamar a las caracter�sticas privadas que tiene la clase fuera de ella*//
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
	void vidas_contador();
	void muerte();
	void cora() {corazones--;}

};

void PERSONAJE::pintar () {
	//*se escribe as� porque es una funci�n que se ocupa desde la clase PERSONAJE*//

	gotoxy (x, y); printf ("%c %c %c", 153, 202, 153);
	gotoxy (x, y+1); printf ("  %c", 94);

}

void PERSONAJE::borrar (){
	gotoxy (x,y); printf ("      ");
	gotoxy (x, y+1); printf ("      ");
}
void PERSONAJE::mover (){
	if(kbhit()){
		/*la funci�n kbhit es la encargada de detectar que las teclas se presionan*/
		char tecla = getch();
		/*la funcion getch se encarga de guardar las teclas que se presionen*/
		borrar();
		/*esto es �til para que los caracteres no dejen rastro, se vuelve a llamar a las coordenadas para evitar su desaparici�n y se
		a�ade un espacio en blanco que se va a encargar de borrar lo que antes fue impreso y as� continuamente*/
		if (tecla == IZQUIERDA && x>3) x--;
		if (tecla == DERECHA && x+4<116) x++;
		if (tecla == ARRIBA && y>7) y--;
		if (tecla == ABAJO && y+2<33) y++;
		if (tecla == 'x') corazones--;
		pintar();}
		/*se posiciona al puntero en este sitio porque es necesaria su aparici�n s�lo cuando una tecla fue presionada*/	OcultarCursor();
	corazones_contador();
	vidas_contador();
	muerte();
}
void PERSONAJE::corazones_contador(){

	gotoxy (95, 5); printf ("Vitalidad: ");
	gotoxy (105, 5); printf ("      ");
	int i;
	for (i=0; i<corazones; i++){
		gotoxy (105+i, 5); printf ("%c ", 208);
	}
}
class BLANCOS{
	int x, y;
	//*
public:

	BLANCOS(int _x, int _y):x(_x), y(_y) {}

	void pintar();
	void mover();
	void choque (class PERSONAJE &N);

};
void BLANCOS::pintar() {
	gotoxy (x, y); printf ("%c", 145);
}
void BLANCOS::mover(){
	gotoxy (x,y); printf (" ");
	y++;
	if (y>32){
		x=rand()%90+8;
		y=7;
	}
	pintar();
}
void BLANCOS::choque (class PERSONAJE &N){
	if (x >= N.X() && x <= N.X()+5 && y >= N.Y() && y <= N.Y()+3){
		N.cora();
		N.borrar();
		N.pintar();
		N.corazones_contador ();
		x=rand()%90+8;
		y=7;
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
void PERSONAJE::vidas_contador(){
	gotoxy(70, 5); printf ("Vidas: ");
	gotoxy (76,5); printf ("  ");
	int i;
	for (i=0; i<vidas; i++){
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
class DISPAROS {
	int x, y;
public:
	DISPAROS (int _x, int _y): x (_x), y (_y) {}
	void movimiento();
};
void DISPAROS::movimiento(){
	gotoxy (x,y); printf (" ");
	if (y>4) y--;
		gotoxy (x,y); printf ("%c", 193);
}
int main (){
	interfaz_limites();
	OcultarCursor();
	PERSONAJE N(55, 30, 5, 3);
	N.pintar();
	BLANCOS B1(10,8); BLANCOS B2 (32, 10); BLANCOS B3 (104, 12); BLANCOS B4 (66, 14); BLANCOS B5 (88, 16);

	/*bucle para mover el puntero:*/
	bool game_over = false;
	/*permite la condici�n mediante un m�todo sencillo de verdadero o falso, por eso se le asigna un valor booleano*/
	while (!game_over) {
		/*la condici�n es que se ejecute siempre que gameover sea falso*/
		list <DISPAROS*> D;
		list <DISPAROS*>:: iterator it;

		if (kbhit()){
			char tecla = getch ();
			if (tecla == 'd')
				D.push_back(new DISPAROS(N.X()+2, N.Y()-1));
		}

		for (it = D.begin(); it!=D.end(); it++) {

			(*it)-> movimiento();

		}

		N.mover();
		N.muerte();
		B1.mover(); B1.choque(N);
		B2.mover(); B2.choque(N);
		B3.mover(); B3.choque(N);
		B4.mover(); B4.choque(N);
		B5.mover(); B5.choque(N);



		Sleep (60);
		/*esto ayuda a que el procesador no se sature al ejecutar el bucle, porque la iteraci�n es muy intensa al repetir estas acciones*/
		}


	return (0);
}

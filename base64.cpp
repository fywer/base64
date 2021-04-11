#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
int Stam = 0;

long pow(long n, long e);
void wRArchivoRead(string nameArch);
void wRbits(vector<char>wRchar);
void wRbits6(vector<bool>wRwRbin);
void wRdecs(vector<bool>wRwRbin);
void wRbase64(vector<int>wRdec);
void wRArchivo(const vector<char>wRwRbin);
void help(char *argv[]);

int main(int argc, char *argv[])
{
    //uso de argumentos en consola(cmd)
    //if(argc < 2) throw ("\nERROR: Sintaxis inocorrecta!!");     //en caso de que el argumento no sea el correcto
    try
    {
		string nameArch = argv[1];
		wRArchivoRead(nameArch);

	}
	catch(...)
	{
		cout <<"ERROR: Sintaxis inocorrecta!!" << endl;
		help(argv);
		return -1;
	}
}

long pow(long n, long e)
{
    if(e == 0)
    {
        if(n == 0) return 0;
        else return 1;
    }
    if(e == 1)
    {
        return n;
    }
    return n * pow(n ,e-1);
}

void wRArchivoRead(string nameArch)
{
    vector<char>wRchar;
    fstream wR;

    wR.open(nameArch.c_str(), fstream::in);

    if(!wR.is_open())                             //Saber si el archivo se abrio
    {
        cout<<"\nERROR: Archivo no encontrado!! -> PRESS ENTER... ";
        cin.get();  //lee un caracter
        throw 0;
    }

    char temp;

    wR.get(temp);        //agrega antes de guardar en el vector
    while(!wR.eof())   //mientras no sea final de archivo
    {
        wRchar.push_back(temp);
        wR.get(temp);
    }

    wR.close();   //cerrar el buffer del fichero
    wRbits(wRchar);
}

void wRbits(vector<char>wRchar)
{
    Stam = wRchar.size();   //tamaño del vector de caracteres, sacados del fichero.

    vector<bool> wRbin ,wRbin2;
    vector<char>::iterator pwRchar;  //no puede ser const porque se modifica al sacar wRbinarios

    /*     *pwRchar/2
         |---------
        2| *pwRchar
           *pwRchar % 2     -> El resutado es 1 ó 0, y se guarda en wRbin2. pero al reves!!

    */
    for(pwRchar = wRchar.begin(); pwRchar != wRchar.end(); pwRchar++)
    {
        while(*pwRchar > 0)
        {
            wRbin2.push_back(*pwRchar % 2 == 1);
            *pwRchar /= 2;
        }

        while(wRbin2.size() != 8)   //rellenar espacios en 0
        {
            wRbin2.push_back(0);
        }

        while(!wRbin2.empty())      //mientras wRbin2 no este vacio. Se vacia el contenedor para poder voltear los bits
        {
            wRbin.push_back(wRbin2.back());
            wRbin2.pop_back();
        }
        wRbin2.clear();              //borrar vector wRbin
    }
    wRbits6(wRbin);
}

void wRbits6(vector<bool>wRbin)
{
    /*
      El tamaño original es de 8 bits (TAM8), y hay que reducirlo a 6 bits (TAM6), si la cadena no logra los 6 bits, hay que rellenar con 0´
      (FALTA)

      Puedo decir que:
      STAM = 1   2   3   4   5   6   7   8   9 ...

      TAM8 = 8, 16, 24, 32, 40, 48, 56, 64, 72 ...
      TAM6 = 6, 12, 18, 24, 30, 36, 42, 48, 54 ...

      REST = 2   4   6   8  10  12  14  16  18 ...

      FALTA= 4   2   0   4   2   0   4   2   0 ...


      Para sacar cuantos bits me sobran (REST); y asi calcular los que faltan, busco la posicion en la tabla de acuerdo a la longitud de la
      cadena (STAM) mutriplico tamaño de cadena * 6  && longitud de cadena * 8, y asi sé cuatos me sobran.

      Para saber cuantos me faltan, solo hize condiciones para cada caso, ya que el patron se repetia solo fueron 3 condiciones.


     */
    int tam6 = Stam * 6 , falta;
    int tam8 = Stam * 8;
    int rest = tam8 - tam6;



    if((4+rest) % 6 == 0) falta = 4;
    if((2+rest) % 6 == 0) falta = 2;
    if((0+rest) % 6 == 0) falta = 0;

    while(falta != 0)
    {
        wRbin.push_back(0);
        falta--;
    }
    wRdecs(wRbin);
}

void wRdecs(vector<bool>wRbin)
{
    vector<int>wRdec;
    vector<bool>::const_iterator pwRbin = wRbin.begin();  //const, ya que no necesito modificar los valores

    while(pwRbin != wRbin.end())
    {
        int i = 5;
        int dec = 0;
        while(i >= 0)               //control para pode guardar solo 6 bits ,y para calcular la potencia
        {
            dec += pow(((*pwRbin)*2), i);
            i--;
            pwRbin++;
        }
        wRdec.push_back(dec);
    }
    wRbase64(wRdec);

}

void wRbase64(vector<int>wRdec)
{
    vector<char>wR64;
    vector<int>::const_iterator pwRdec = wRdec.begin(); //solo nesecito el valor, y no modificarlo

    while(pwRdec != wRdec.end())
    {
        if(*pwRdec >= 0 && *pwRdec <= 25 )
        {
            switch(*pwRdec)
            {
                case 0:
                wR64.push_back('A');
                break;

                case 1:
                wR64.push_back('B');
                break;

                case 2:
                wR64.push_back('C');
                break;

                case 3:
                wR64.push_back('D');
                break;

                case 4:
                wR64.push_back('E');
                break;

                case 5:
                wR64.push_back('F');
                break;

                case 6:
                wR64.push_back('G');
                break;

                case 7:
                wR64.push_back('H');
                break;

                case 8:
                wR64.push_back('I');
                break;

                case 9:
                wR64.push_back('J');
                break;

                case 10:
                wR64.push_back('K');
                break;

                case 11:
                wR64.push_back('L');
                break;

                case 12:
                wR64.push_back('M');
                break;

                case 13:
                wR64.push_back('N');
                break;

                case 14:
                wR64.push_back('O');
                break;

                case 15:
                wR64.push_back('P');
                break;

                case 16:
                wR64.push_back('Q');
                break;

                case 17:
                wR64.push_back('R');
                break;

                case 18:
                wR64.push_back('S');
                break;

                case 19:
                wR64.push_back('T');
                break;

                case 20:
                wR64.push_back('U');
                break;

                case 21:
                wR64.push_back('V');
                break;

                case 22:
                wR64.push_back('W');
                break;

                case 23:
                wR64.push_back('X');
                break;

                case 24:
                wR64.push_back('Y');
                break;

                case 25:
                wR64.push_back('Z');
                break;
            }
        }
        if(*pwRdec >= 26 && *pwRdec <= 51 )
        {
            switch(*pwRdec)
            {
                case 26:
                wR64.push_back('a');
                break;

                case 27:
                wR64.push_back('b');
                break;

                case 28:
                wR64.push_back('c');
                break;

                case 29:
                wR64.push_back('d');
                break;

                case 30:
                wR64.push_back('e');
                break;

                case 31:
                wR64.push_back('f');
                break;

                case 32:
                wR64.push_back('g');
                break;

                case 33:
                wR64.push_back('h');
                break;

                case 34:
                wR64.push_back('i');
                break;

                case 35:
                wR64.push_back('j');
                break;

                case 36:
                wR64.push_back('k');
                break;

                case 37:
                wR64.push_back('l');
                break;

                case 38:
                wR64.push_back('m');
                break;

                case 39:
                wR64.push_back('n');
                break;

                case 40:
                wR64.push_back('o');
                break;

                case 41:
                wR64.push_back('p');
                break;

                case 42:
                wR64.push_back('q');
                break;

                case 43:
                wR64.push_back('r');
                break;

                case 44:
                wR64.push_back('s');
                break;

                case 45:
                wR64.push_back('t');
                break;

                case 46:
                wR64.push_back('u');
                break;

                case 47:
                wR64.push_back('v');
                break;

                case 48:
                wR64.push_back('w');
                break;

                case 49:
                wR64.push_back('x');
                break;

                case 50:
                wR64.push_back('y');
                break;

                case 51:
                wR64.push_back('z');
                break;
            }
        }
        if(*pwRdec >= 52 && *pwRdec <= 63 )
        {
            switch(*pwRdec)
            {
                case 52:
                wR64.push_back('0');
                break;

                case 53:
                wR64.push_back('1');
                break;

                case 54:
                wR64.push_back('2');
                break;

                case 55:
                wR64.push_back('3');
                break;

                case 56:
                wR64.push_back('4');
                break;

                case 57:
                wR64.push_back('5');
                break;

                case 58:
                wR64.push_back('6');
                break;

                case 59:
                wR64.push_back('7');
                break;

                case 60:
                wR64.push_back('8');
                break;

                case 61:
                wR64.push_back('9');
                break;

                case 62:
                wR64.push_back('+');
                break;

                case 63:
                wR64.push_back('/');
                break;
            }
        }
        pwRdec++;
    }
    /*
    Condiciones para los tres posibles caso.
    Tamaño de la cadena % 3 (Es el caso que no lleva '=', esto provoca una repeticion)
    El modulo es lo que sobra y se le aplica cada caso.

    */
    if(Stam % 3 == 1)
    {
        wR64.push_back('=');
        wR64.push_back('=');
    }
    if(Stam % 3 == 2) wR64.push_back('=');

    wRArchivo(wR64);
}

void wRArchivo(const vector<char>wRwRbin)
{
    vector<char>::const_iterator x = wRwRbin.begin();
    fstream wRbase;
    int jump  = 0;

    wRbase.open("base64", fstream::out);
    while(x != wRwRbin.end())
    {
        if(jump % 161 == 160) wRbase <<endl;           //Para hacer saltos de linea
        wRbase << *x;
        x++;
        jump++;

    }
    wRbase.close();
}

void help(char *argv[])
{
	cout << "===================" << endl;
	cout << "\n\n\t $"  << argv[0] << "[nombre del archivo]"  << endl;
	cout << "===================" << endl;
}

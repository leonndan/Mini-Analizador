#include "lexico.h"

lexico::lexico(string fuente)
{
	ind = 0;
	this->fuente = fuente;
}

lexico::lexico()
{
	ind = 0;
}
string lexico::tipoAcad(int tipo)
{
	string cad = "";
	switch (tipo)
	{
	case TipoSimbolo::IDENTIFICADOR:
		cad = "Identificador";
		break;
	case TipoSimbolo::ENTERO:
		cad = "Numero Entero";
		break;
	case TipoSimbolo::REAL:
		cad = "Numero Real";
		break;
	case TipoSimbolo::CADENA:
		cad = "Cadena";
		break;
	case TipoSimbolo::TIPO:
		cad = "Palabra Reservada";
		break;
	case TipoSimbolo::OPSU:
		cad = "Operador de Suma/Resta";
		break;
	case TipoSimbolo::OPMU:
		cad = "Operador de Multiplicacion/division";
		break;
	case TipoSimbolo::OPREL:
		cad = "Operador de Relacion";
		break;
	case TipoSimbolo::OPOR:
		cad = "Operador OR";
		break;
	case TipoSimbolo::OPAND:
		cad = "Operador AND";
		break;
	case TipoSimbolo::OPNOT:
		cad = "Operador NOT";
		break;
	case TipoSimbolo::OPIGUALDAD:
		cad = "Operador de igualdad";
		break;
	case TipoSimbolo::PUNTO_COMA:
		cad = "Punto y Coma";
		break;
	case TipoSimbolo::COMA:
		cad = "Coma";
		break;
	case TipoSimbolo::PARENTESIS1:
		cad = "Parentesis";
		break;
	case TipoSimbolo::PARENTESIS2:
		cad = "Parentesis";
		break;
	case TipoSimbolo::LLAVE1:
		cad = "Llave";
		break;
	case TipoSimbolo::LLAVE2:
		cad = "Llave";
		break;
	case TipoSimbolo::IGUAL:
		cad = "Operador de Asignacion";
		break;
	case TipoSimbolo::IF:
		cad = "Palabra Reservada";
		break;
	case TipoSimbolo::WHILE:
		cad = "Palabra Reservada";
		break;
	case TipoSimbolo::RETURN:
		cad = "Palabra Reservada";
		break;
	case TipoSimbolo::ELSE:
		cad = "Palabra Reservada";
		break;
	case TipoSimbolo::PESOS:
		cad = "";
		break;
	}

	return cad;
}
void lexico::entrada(string fuente)
{
	ind = 0;
	this->fuente = fuente;
}
int lexico::sigSimbolo()
{
	estado = 0;
	continua = true;
	simbolo = "";
	cont = 0;

	while (continua)
	{
		c= sigCaracter();

		switch (estado)
		{
		case 0:
			if (esLetra(c)) {
				estado = 1;
				simbolo += c;
			}
			if (esDigito(c)) {
				estado = 2;
				simbolo += c;
				cont++;
			
			}
			else {
				
				if (c == '$') {
					aceptacion(23);
				}
			}
			
			
			break;
		case 1:
			if (esLetra(c) || esDigito(c)) {
				simbolo += c;
				continua = true;
			}
			else {
				aceptacion(0);
				estado = 0;
				continua =false;
			}
			break;
		case 2:
			if (((c == '.') && (cont == 0) || esLetra(c))) {
				estado = 0;
				continua=false;
				aceptacion(-1);
			}
			else if (c == '.') {
				estado=3;
				simbolo+=c;
				}
			break;
		case 3:
			if (esDigito(c)) {
				estado = 0;
				aceptacion(2);

			}
			break;
		}	
	}
	switch (estado)
	{
	case -1:
		tipo = TipoSimbolo::ERROR;
		break;
	case 0:
		tipo = TipoSimbolo::IDENTIFICADOR;
		break;
	case 1:
		tipo = TipoSimbolo::ENTERO;
		break;
	case 2:
		tipo = TipoSimbolo::REAL;
		break;
	case 3:
		tipo = TipoSimbolo::CADENA;
		break;
	case 4:
		tipo = TipoSimbolo::TIPO;
		break;
	case 5:
		tipo = TipoSimbolo::OPSU;
		break;
	case 6:
		tipo = TipoSimbolo::OPMU;
		break;
	case 7:
		tipo = TipoSimbolo::OPREL;
		break;
	case 8:
		tipo = TipoSimbolo::OPOR;
		break;
	case 9:
		tipo = TipoSimbolo::OPAND;
		break;
	case 10:
		tipo = TipoSimbolo::OPNOT;
		break;
	case 11:
		tipo = TipoSimbolo::OPIGUALDAD;
		break;
	case 12:
		tipo = TipoSimbolo::PUNTO_COMA;
		break;
	case 13:
		tipo = TipoSimbolo::COMA;
		break;
	case 14:
		tipo = TipoSimbolo::PARENTESIS1;
		break;
	case 15:
		tipo = TipoSimbolo::PARENTESIS2;
		break;
	case 16:
		tipo = TipoSimbolo::LLAVE1;
		break;
	case 17:
		tipo = TipoSimbolo::LLAVE2;
		break;
	case 18:
		tipo = TipoSimbolo::IGUAL;
		break;
	case 19:
		tipo = TipoSimbolo::IF;
		break;
	case 20:
		tipo = TipoSimbolo::WHILE;
		break;
	case 21:
		tipo = TipoSimbolo::RETURN;
		break;
	case 22:
		tipo = TipoSimbolo::ELSE;
		break;
	case 23:
		tipo = TipoSimbolo::PESOS;
		break;
	default:
		tipo = TipoSimbolo::ERROR;
		break;
	}
	return tipo;
}
char lexico::sigCaracter()
{
	if (terminado()) return '$';

	return fuente[ind++];
}
void lexico::sigEstado(int estado)
{
	this->estado = estado;
	simbolo += c;

}
void lexico::aceptacion(int estado)
{
	sigEstado(estado);
	continua = false;
}
bool lexico::terminado()
{
	return ind >= fuente.length();

}
bool lexico::esLetra(char c)
{
	return isalpha(c) || c == '_';
}
bool lexico::esDigito(char c)
{
	return isdigit(c);

}
bool lexico::esEspacio(char c)
{
	return c == ' ' || c == '\t';
}
void lexico::retroceso()
{
	if (c != '$') ind--;
	continua = false;
}
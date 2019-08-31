#include <iostream>
#include <chrono>
#include <getopt.h>
#include <cmath>
#include "config.h"

// Display help
void help(char**);

typedef double metric_t;

/// Tiempo que pasa entre cada paso de la simulación
metric_t step = 0.1;

/// Tiempo que ha pasado desde el inicio de la simulación
metric_t passed;

/// Tiempo en el que termina la simulación
metric_t end = 0.0;

struct vector2
{
	metric_t x;
	metric_t y;

	// Operadores {{{
	void operator= (const vector2& Y)
	{
		this->x = Y.x;
		this->y = Y.y;
	}

	void operator= (const int& Y)
	{
		this->x = Y;
		this->y = Y;
	}

	vector2 operator+ (const vector2& Y)
	{
		vector2 resu = {this->x+Y.x, this->y+Y.y};
		return resu;
	}

	vector2 operator+ (const int& Y)
	{
		vector2 resu = {this->x+Y, this->y+Y};
		return resu;
	}

	vector2 operator+ (const metric_t& Y)
	{
		vector2 resu = {this->x+Y, this->y+Y};
		return resu;
	}

	vector2 operator- (const vector2& Y)
	{
		vector2 resu = {this->x-Y.x, this->y-Y.y};
		return resu;
	}

	vector2 operator- (const int& Y)
	{
		vector2 resu = {this->x-Y, this->y-Y};
		return resu;
	}

	vector2 operator- (const metric_t& Y)
	{
		vector2 resu = {this->x-Y, this->y-Y};
		return resu;
	}

	vector2 operator* (const vector2& Y)
	{
		vector2 resu = {this->x*Y.x, this->y*Y.y};
		return resu;
	}

	vector2 operator* (const int& Y)
	{
		vector2 resu = {this->x*Y, this->y*Y};
		return resu;
	}

	vector2 operator* (const metric_t& Y)
	{
		vector2 resu = {this->x*Y, this->y*Y};
		return resu;
	}

	vector2 operator/ (const vector2& Y)
	{
		vector2 resu = {this->x/Y.x, this->y/Y.y};
		return resu;
	}

	vector2 operator/ (const int& Y)
	{
		vector2 resu = {this->x/Y, this->y/Y};
		return resu;
	}

	vector2 operator/ (const metric_t& Y)
	{
		vector2 resu = {this->x/Y, this->y/Y};
		return resu;
	}

	vector2& operator+= (const vector2& Y)
	{
		this->x+=Y.x;
		this->y+=Y.y;
		return *this;
	}

	vector2& operator+= (const int& Y)
	{
		this->x+=Y;
		this->y+=Y;
		return *this;
	}

	vector2& operator+= (const metric_t& Y)
	{
		this->x+=Y;
		this->y+=Y;
		return *this;
	}

	// }}}
};


class objeto
{
	public:
		/// Masa del objeto en kg
		metric_t masa;

		/// Carga del objeto en C
		metric_t carga;

		/// Velocidad del objeto en m/s
		vector2 velocidad;

		/// Distancia a la otra esfera
		metric_t r;

		/// Posición
		vector2 pos;
		objeto(metric_t masa, metric_t carga, vector2 velocidad, vector2 pos, bool fijo):
			masa(masa),
			carga(carga),
			velocidad(velocidad),
			pos(pos),
			fijo(fijo){}

		objeto(metric_t carga, vector2 pos, bool fijo):
			carga(carga),
			pos(pos),
			fijo(fijo){}

		void affect_force(vector2 force)
		{
			fuerzas += force;
		}

		void clean_n_print()
		{
			std::cout << passed << ',' << pos.x << ',' << pos.y << ',' << r << '\n';
			fuerzas = 0;
		}

		void calcu_pos()
		{
			if(fijo)
				return;

			// Fuerza del peso
			fuerzas += {0.0,-10.0*masa};

			aceleracion = fuerzas/masa;
			velocidad += aceleracion*step;
			pos += velocidad*step;
		}
		void calcu_elec(objeto& otro)
		{
			vector2 fuerza;
			metric_t fuerza_mod;
			metric_t k=9.0*pow(10, 9);
			r = sqrt(pow(this->pos.x-otro.pos.x,2)+pow(this->pos.y-otro.pos.y,2));

			fuerza_mod = this->carga*otro.carga*k/pow(r, 2);

			fuerza = {fuerza_mod*((this->pos.x-otro.pos.x)/r),fuerza_mod*((this->pos.y-otro.pos.y)/r)};

			fuerzas += fuerza;

		}
	private:
		/// Aceleración del objecto en m/s^2
		vector2 aceleracion;

		/// Fuerzas al objeto en N
		vector2 fuerzas;

		/// Si es fijo
		bool fijo;
};

int main(int argc, char *argv[])
{
	// Argument counter
	int cc;

	// No errors from getopt (flag)
	opterr=0;

	// Implicit help when no arguments are passed
	if(argc == 1)
	{
		help(argv);
		exit(2);
	}

	// Declaration of long arguments{{{
	static struct option options[] =
	{
		{"help", no_argument, 0, 'h'},
		{"time", required_argument, 0, 't'},
		{"step", required_argument, 0, 's'},
		{0,0,0,0}
	};
	//}}}
	// Argument parsing loop{{{
	while(true)
	{
		int option_index = 0;

		// The actual parsing
		cc = getopt_long(argc, argv, "ht:s:", options, &option_index);

		// No more parseable arguments{{{
		if(cc == -1)
		{
			break;
		}
		//}}}
		// Argument switch table{{{
		switch(cc)
		{
			case 'h':
				help(argv);
				break;
			case 't':
				if(!sscanf(optarg, "%lf", &end))
				{
					std::cerr << "Input inválido\n";
					exit(3);
				}
				break;
			case 's':
				if(!sscanf(optarg, "%lf", &step))
				{
					std::cerr << "Input inválido\n";
					exit(4);
				}
				break;
			case '?':
				std::cerr << "No\n";
				break;
		}
		//}}}
	}
	//}}}

	objeto** esferas = new objeto*[2];

	esferas[0] = new objeto (0.15, 0.001*(-0.2),{22.0,0.0},{0.0,0.0}, false);
	esferas[1] = new objeto (0.000001*(-3.5), {0.8, 0.0}, true);

	std::cout << "Tiempo, Pos x, Pos y, distancia\n";
	for(passed = 0.0; passed <= end; passed += step)
	{
		esferas[0]->calcu_elec(*esferas[1]);
		esferas[0]->calcu_pos();
		esferas[0]->clean_n_print();
	}

	return 0;
}

// Help{{{
void help(char* argv[])
{
	std::cout << "Uso:\n"
		<< "    " << argv[0] << " [opción]\n"
		<< "Opciones:\n"
		<< "    " << "-h, --help             Muestra la ayuda\n"
		<< "    " << "-t, --time=TIEMPO      Duración de la simulación en segundos\n"
		<< "    " << "-s, --step=TIEMPO      Duración de cada paso de la simulación en segundos\n"
		<< '\n'
		<< "Ejemplo:\n"
		<< "    " << argv[0] << " -t 10 -s 0.1\n";
}
// }}}

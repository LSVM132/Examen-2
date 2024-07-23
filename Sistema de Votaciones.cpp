#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> // Para system()

using namespace std;

struct Candidato {
    string nombre;
    string partido;
    string plataforma;
    int votos;

    Candidato() : votos(0) {}
};

struct Votante {
    string nombre;
    string id;
};

vector<Candidato> candidatos;
vector<string> votantesRegistrados;

void limpiarPantalla();
void mostrarMenu();
void ingresarCandidatos();
void registrarVotos();
void mostrarResultados();
void mostrarGanador();
void esperarEntrada();

int main() {
    mostrarMenu();
    return 0;
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls"); // Limpiar pantalla en Windows
    #else
        system("clear"); // Limpiar pantalla en Unix/Linux/macOS
    #endif
}

void mostrarMenu() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "          SISTEMA DE VOTACIONES\n";
        cout << "====================================\n";
        cout << "1. Ingresar Candidatos\n";
        cout << "2. Registrar Votos\n";
        cout << "3. Mostrar Resultados\n";
        cout << "4. Salir\n";
        cout << "------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                ingresarCandidatos();
                break;
            case 2:
                registrarVotos();
                break;
            case 3:
                mostrarResultados();
                break;
            case 4:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                esperarEntrada();
        }
    } while (opcion != 4);
}

void esperarEntrada() {
    cout << "------------------------------------\n";
    cout << "Presione Enter para volver al menu...";
    cin.ignore(); // Ignorar el salto de línea residual
    cin.get();    // Esperar la entrada del usuario
}

void ingresarCandidatos() {
    limpiarPantalla();
    int numCandidatos;
    cout << "====================================\n";
    cout << "        INGRESAR CANDIDATOS\n";
    cout << "====================================\n";
    cout << "Ingrese el numero de candidatos: ";
    cin >> numCandidatos;
    cin.ignore();

    for (int i = 0; i < numCandidatos; ++i) {
        Candidato c;
        cout << "Ingrese nombre del candidato: ";
        getline(cin, c.nombre);
        cout << "Ingrese partido politico: ";
        getline(cin, c.partido);
        cout << "Ingrese plataforma: ";
        getline(cin, c.plataforma);
        candidatos.push_back(c);
    }
    cout << "Candidatos ingresados exitosamente.\n";
    esperarEntrada();
}

void registrarVotos() {
    limpiarPantalla();
    int numVotos;
    cout << "====================================\n";
    cout << "         REGISTRAR VOTOS\n";
    cout << "====================================\n";
    cout << "Ingrese el numero de votos a registrar: ";
    cin >> numVotos;
    cin.ignore();

    for (int i = 0; i < numVotos; ++i) {
        Votante votante;
        cout << "Ingrese el nombre del votante: ";
        getline(cin, votante.nombre);
        cout << "Ingrese el ID del votante: ";
        getline(cin, votante.id);

        if (find(votantesRegistrados.begin(), votantesRegistrados.end(), votante.id) != votantesRegistrados.end()) {
            cout << "El votante con ID " << votante.id << " ya ha votado. Voto no registrado.\n";
            continue;
        }

        string nombreCandidato;
        cout << "Ingrese el nombre del candidato por el que vota: ";
        getline(cin, nombreCandidato);

        bool candidatoEncontrado = false;
        for (int j = 0; j < candidatos.size(); ++j) {
            if (candidatos[j].nombre == nombreCandidato) {
                candidatos[j].votos++;
                candidatoEncontrado = true;
                break;
            }
        }

        if (candidatoEncontrado) {
            votantesRegistrados.push_back(votante.id);
            cout << "Voto registrado exitosamente.\n";
        } else {
            cout << "Candidato no encontrado. Voto no registrado.\n";
        }
    }
    esperarEntrada();
}

void mostrarResultados() {
    limpiarPantalla();
    cout << "====================================\n";
    cout << "         RESULTADOS DE LA ELECCION\n";
    cout << "====================================\n";
    for (int i = 0; i < candidatos.size(); ++i) {
        cout << "Candidato: " << candidatos[i].nombre
             << " | Partido: " << candidatos[i].partido
             << " | Votos: " << candidatos[i].votos << '\n';
    }
    mostrarGanador();
    esperarEntrada();
}

void mostrarGanador() {
    if (!candidatos.empty()) {
        int indiceGanador = 0;
        for (int i = 1; i < candidatos.size(); ++i) {
            if (candidatos[i].votos > candidatos[indiceGanador].votos) {
                indiceGanador = i;
            }
        }
        cout << "====================================\n";
        cout << "         GANADOR DE LA ELECCION\n";
        cout << "====================================\n";
        cout << "El ganador es: " << candidatos[indiceGanador].nombre
             << " con " << candidatos[indiceGanador].votos << " votos.\n";
    } else {
        cout << "No hay candidatos registrados.\n";
    }
    esperarEntrada();
}


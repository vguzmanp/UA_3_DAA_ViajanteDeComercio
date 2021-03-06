/* 
 * File:   Solucion.cpp
 * Author: victor
 * 
 * Created on 15 de diciembre de 2011, 15:43
 */

#include "Solucion.h"

Solucion::Solucion(int num) {
    n = num;
    solucion = vector<int>(num+1,-1);
    peso = 0;
}

Solucion::Solucion(const Solucion& orig) {
    solucion = orig.solucion;
    n = orig.n;
    peso = orig.peso;
}

Solucion::~Solucion() {
    solucion.clear();
    n = 0;
    peso = 0;
}


// funciona como un operator>, se usa para ordenar correctamente la priority_queue
bool Solucion::operator <(const Solucion& sol) const
{
    if(peso < sol.peso)
        return false;
    else
        return true;
}

// Función auxiliar. Hace exactamente lo mismo que getVertice en main
int getVertice_aux(int id, Vertice* vertices, int cantidad)
{
    bool encontrado = false;
    int i;
    for(i = 0; i < cantidad && !encontrado; i++)
    {
        if(vertices[i].getID() == id)
        {
            encontrado = true;
            break;
        }
    }
    
    if(!encontrado)
        i = -1;
    
    return i;
}

void Solucion::setPeso(Vertice* vertices)
{
    int peso_total = 0;    

    for(int j = 0; j < n; j++)
    {
        if(solucion[j] == -1 || solucion[j+1] == -1)
            break;
        
        int pos = getVertice_aux(solucion[j],vertices,n);
        if(pos != -1)
        {
            Arista* aristas = vertices[pos].getAristas();

            for(int i = 0; i < vertices[pos].getGrado(); i++)
            {
                // si hay una arista entre los nodos de la solucion
                if(aristas[i].getIdFinal() == solucion[j+1] && aristas[i].getIdInicio() == solucion[j])
                {
                    peso_total += aristas[i].getPeso();
                }
            }
        }
        else
            cerr<<"ERROR!!!!!!"<<endl;
    }
    
    peso = peso_total;
}


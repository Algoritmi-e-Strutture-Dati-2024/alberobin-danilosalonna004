#include <iostream>
using namespace std;

template <typename Tipo>
class AlberoBin {
private:
    Tipo elementi[100];
    bool presente[100];
    int numeroNodi;

public:
    AlberoBin() {
        numeroNodi = 0;
        for (int indice; indice < 100; ++indice) {
            presente[indice] = false;
        }
    }

    bool vuoto() const {
        return numeroNodi == 0;
    }

    void inserisciRadice(const Tipo& valore) {
        if (numeroNodi < 100) {
            elementi[0] = valore;
            presente[0] = true;
            numeroNodi = 1;
        }
    }

    Tipo leggiRadice() const {
        return vuoto() ? Tipo() : elementi[0];
    }

    bool nodoFoglia(int posizione) const {
        if (!presente[posizione]) return false;
        int sinistro = 2 * posizione + 1;
        int destro = 2 * posizione + 2;
        return (sinistro >= 100 || !presente[sinistro]) && (destro >= 100 || !presente[destro]);
    }

    int indiceSinistro(int posizione) const {
        int sinistro = 2 * posizione + 1;
        return (sinistro < 100 && presente[sinistro]) ? sinistro : -1;
    }

    int indiceDestro(int posizione) const {
        int destro = 2 * posizione + 2;
        return (destro < 100 && presente[destro]) ? destro : -1;
    }

    void aggiungiSinistro(int posizione, const Tipo& valore) {
        int sinistro = 2 * posizione + 1;
        if (sinistro < 100 && presente[posizione] && !presente[sinistro]) {
            elementi[sinistro] = valore;
            presente[sinistro] = true;
            ++numeroNodi;
        }
    }

    void aggiungiDestro(int posizione, const Tipo& valore) {
        int destro = 2 * posizione + 2;
        if (destro < 100 && presente[posizione] && !presente[destro]) {
            elementi[destro] = valore;
            presente[destro] = true;
            ++numeroNodi;
        }
    }

    void eliminaNodo(int posizione) {
        if (posizione < 100 && presente[posizione]) {
            // Elimina solo se il nodo è una foglia
            if (nodoFoglia(posizione)) {
                presente[posizione] = false;
                --numeroNodi;
            } else {
                // Gestisce l'eliminazione di un nodo con figli
                int sinistro = 2 * posizione + 1;
                int destro = 2 * posizione + 2;
                if (sinistro < 100 && presente[sinistro]) {
                    presente[sinistro] = false;
                    --numeroNodi;
                }
                if (destro < 100 && presente[destro]) {
                    presente[destro] = false;
                    --numeroNodi;
                }
                presente[posizione] = false;
                --numeroNodi;
            }
        }
    }

    void mostraAlbero() const {
        for (int indice = 0; indice < 100; ++indice) {
            if (presente[indice]) {
                cout << "Nodo " << indice << ": " << elementi[indice] << endl;
                int sinistro = indiceSinistro(indice);
                int destro = indiceDestro(indice);

                if (sinistro != -1 && presente[sinistro]) {
                    cout << " Figlio sinistro: " << elementi[sinistro] << endl;
                } else {
                    cout << " Figlio sinistro: /" << endl;
                }
                if (destro != -1 && presente[destro]) {
                    cout << " Figlio destro: " << elementi[destro] << endl;
                } else {
                    cout << " Figlio destro: /" << endl;
                }
            }
        }
    }
};

int main() {
    AlberoBin<int> albero;

    // 1. Inserisco una nuova radice
    albero.inserisciRadice(15);  // Nuovo valore per la radice
    cout << "Inserisco Radice: \n";
    albero.mostraAlbero();

    // 2. Aggiungo figli
    albero.aggiungiSinistro(0, 25);  // Nuovo valore per il figlio sinistro
    albero.aggiungiDestro(0, 35);    // Nuovo valore per il figlio destro
    albero.aggiungiSinistro(1, 50);  // Nuovo valore per il figlio sinistro del nodo 25
    albero.aggiungiDestro(1, 60);    // Nuovo valore per il figlio destro del nodo 25
    cout << "\nAlbero dopo l'inserimento dei figli:\n";
    albero.mostraAlbero();

    // 3. Stampa dei figli di un nodo a scelta
    int nodoCorrente = 0;
    int sinistro = albero.indiceSinistro(nodoCorrente);
    int destro = albero.indiceDestro(nodoCorrente);
    cout << "\nNodo " << nodoCorrente << " (" << albero.leggiRadice() << ") ha:" << endl;
    cout << "Figlio sinistro all'indice: " << (sinistro != -1 ? sinistro : -1) << endl;
    cout << "Figlio destro all'indice: " << (destro != -1 ? destro : -1) << endl;

    // 4. Rimuovo un nodo
    albero.eliminaNodo(3);
    cout << "\nRimuovo il nodo 3: \n";
    albero.mostraAlbero();

    return 0;
}

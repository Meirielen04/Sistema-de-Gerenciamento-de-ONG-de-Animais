/**
 * PROJETO ONG "ANIMALCARE" 2 - TAREFAS PROPOSTAS
 * --------------------------------------------------------------------------
 * 1. SOBRECARGA DE CONSTRUTORES (Classe Animal)
 * - Construtor padrão: Sem parâmetros.
 * - Construtor parametrizado: Recebe nome, idade e espécie.
 * - Teste: Instanciar objetos utilizando ambas as formas.
 * * 2. SOBRECARGA DE MÉTODOS
 * - Implementar mostrarDados() em duas versões:
 * a) Simples: Exibe apenas nome, idade e espécie.
 * b) Detalhada: Inclui status de adoção e tipo de cuidado necessário.
 * * 3. DESTRUTORES
 * - Implementar ~Animal() para exibir mensagem de log quando o objeto
 * for removido da memória.
 * - Teste: Remover animais da lista e observar a saída no console.
 * * 4. RELACIONAMENTO ENTRE CLASSES E FLUXO
 * - Classe Cadastro: Responsável pelo registro de novos animais.
 * - Classe Adocao: Responsável por gerenciar animais disponíveis.
 * - Integração: Conectar Cadastro e Adocao ao menu principal do sistema.
 * * 5. REQUISITOS DE TESTE (PARTE 2)
 * - Cadastrar no mínimo 3 animais diferentes.
 * - Disponibilizar pelo menos 1 animal para adoção.
 * - Validar as sobrecargas e o destrutor via console.
 * --------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal {
    protected:
        string nome;
        int idade;
        string raca;
        bool paraAdocao;
        string cor;
        string porte;
        string personalidade;
        string sexo;

    public:
        Animal(string n, int i, string r, string c, string p, string pe, string s)
            : nome(n), idade(i), raca(r), paraAdocao(false), cor(c), porte(p), personalidade(pe), sexo(s) {}

        virtual void cadastroDados() {
            cout << "  Nome:           " << nome << endl;
            cout << "  Idade:          " << idade << " ano(s)" << endl;
            cout << "  Raca:           " << raca << endl;
            cout << "  Cor:            " << cor << endl;
            cout << "  Porte:          " << porte << endl;
            cout << "  Personalidade:  " << personalidade << endl;
            cout << "  Sexo:           " << sexo << endl;
            cout << "  Para adocao:    " << (paraAdocao ? "Sim" : "Nao") << endl;
        }

        string getNome() { return nome; }
        bool getParaAdocao() { return paraAdocao; }
        void disponibilizarAdocao() { paraAdocao = true; }
};

class CuidadosVeterinarios : public Animal {
    public:
        CuidadosVeterinarios(string n, int i, string r, string c, string p, string pe, string s)
            : Animal(n, i, r, c, p, pe, s) {}

        void cadastroDados() {
            Animal::cadastroDados();
            cout << "  Cuidado:        Veterinario" << endl;
        }
};

class CuidadosAlimentares : public Animal {
    public:
        CuidadosAlimentares(string n, int i, string r, string c, string p, string pe, string s)
            : Animal(n, i, r, c, p, pe, s) {}

        void cadastroDados() {
            Animal::cadastroDados();
            cout << "  Cuidado:        Alimentar" << endl;
        }
};

class CuidadosAbrigo : public Animal {
    public:
        CuidadosAbrigo(string n, int i, string r, string c, string p, string pe, string s)
            : Animal(n, i, r, c, p, pe, s) {}

        void cadastroDados() {
            Animal::cadastroDados();
            cout << "  Cuidado:        Abrigo" << endl;
        }
};

// vector<Animal *> usa ponteiros para permitir polimorfismo (chamar cadastroDados das classes filhas)
// &lista passa por referencia, modificando a lista original e nao uma copia
void cadastrarAnimal(vector<Animal *> &lista) {
    string nome, raca, cor, porte, personalidade, sexo;
    int idade, tipo;

    cout << "\nTipo de cuidado:" << endl;
    cout << "  1 - Veterinario" << endl;
    cout << "  2 - Alimentar" << endl;
    cout << "  3 - Abrigo" << endl;
    cout << "Escolha: ";
    cin >> tipo;

    if (tipo < 1 || tipo > 3) {
        cout << "Tipo invalido!\n";
        cin.ignore();
        return;
    }

    // descarta o "\n" que sobrou ao apertar enter na resposta
    cin.ignore();

    cout << "Nome: ";
    getline(cin, nome);

    cout << "Idade: ";
    cin >> idade;
    cin.ignore();

    cout << "Raca: ";
    getline(cin, raca);

    cout << "Cor: ";
    getline(cin, cor);

    cout << "Porte: ";
    getline(cin, porte);

    cout << "Personalidade: ";
    getline(cin, personalidade);

    cout << "Sexo: ";
    getline(cin, sexo);

    if (tipo == 1) {
        lista.push_back(new CuidadosVeterinarios(nome, idade, raca, cor, porte, personalidade, sexo));
    } else if (tipo == 2) {
        lista.push_back(new CuidadosAlimentares(nome, idade, raca, cor, porte, personalidade, sexo));
    } else {
        lista.push_back(new CuidadosAbrigo(nome, idade, raca, cor, porte, personalidade, sexo));
    }

    cout << "\nAnimal cadastrado com sucesso!\n";
}

void listarAnimais(vector<Animal *> &lista) {
    if (lista.empty()) {
        cout << "\nNenhum animal cadastrado.\n";
        return;
    }

    cout << "\n===== ANIMAIS CADASTRADOS =====\n";

    // Exibe todos os animais cadastrados
    for (int i = 0; i < lista.size(); i++) {
        cout << "\n--- Animal #" << i + 1 << " ---" << endl;
        lista[i]->cadastroDados();
    }

    cout << "\nTotal: " << lista.size() << " animal(is).\n";
}

void disponibilizarParaAdocao(vector<Animal *> &lista) {
    if (lista.empty()) {
        cout << "\nNenhum animal cadastrado.\n";
        return;
    }

    cout << "\n===== DISPONIBILIZAR PARA ADOCAO =====\n";

    // Exibe lista de animais com o status de disponibilidade para adoção
    for (int i = 0; i < lista.size(); i++) {
        cout << "  " << i + 1 << " - " << lista[i]->getNome()
             << " [" << (lista[i]->getParaAdocao() ? "Disponivel" : "Indisponivel") << "]" << endl;
    }

    cout << "\nDigite o numero do animal (0 para voltar): ";
    int escolha;
    cin >> escolha;
    cin.ignore();

    if (escolha == 0) return;

    // Verifica se a escolha é valida dentro dos limites da lista
    if (escolha < 1 || escolha > lista.size()) {
        cout << "Opcao invalida!\n";
        return;
    }

    // animal é um ponteiro porque a lista guarda ponteiros (Animal *)
    // para acessar metodos de um ponteiro, usa -> em vez de .
    Animal *animal = lista[escolha - 1];

    if (animal->getParaAdocao()) {
        cout << "\n" << animal->getNome() << " ja esta disponivel para adocao.\n";
    } else {
        animal->disponibilizarAdocao();
        cout << "\n" << animal->getNome() << " agora esta disponivel para adocao!\n";
    }
}

int main() {
    vector<Animal *> listaAnimais;
    int opcao;

    do {
        cout << "\n===== ONG - GERENCIAMENTO DE ANIMAIS =====\n";
        cout << "  1 - Cadastrar animal" << endl;
        cout << "  2 - Mostrar todos" << endl;
        cout << "  3 - Disponibilizar para adocao" << endl;
        cout << "  0 - Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1:
                cadastrarAnimal(listaAnimais);
                break;
            case 2:
                listarAnimais(listaAnimais);
                break;
            case 3:
                disponibilizarParaAdocao(listaAnimais);
                break;
            case 0:
                cout << "\nAte logo!\n";
                break;
            default:
                cout << "Opcao invalida!\n";
                break;
        }
    } while (opcao != 0);

    for (int i = 0; i < listaAnimais.size(); i++) {
        delete listaAnimais[i];
    }

    return 0;
}
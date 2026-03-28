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

        Animal() {
            setNome("");
            setIdade(0);
            setRaca("");
            setCor("");
            setPorte("");
            setPersonalidade("");
            setSexo("");
            setParaAdocao(false);
        }

        void setNome(string n) {nome = n; }
        void setIdade(int i) {idade = i; }
        void setRaca(string r) {raca = r; }
        void setParaAdocao(bool status) {paraAdocao = status; }
        void setCor(string c) {cor = c; }
        void setPorte(string p) {porte = p; }
        void setPersonalidade(string per) {personalidade = per; }
        void setSexo(string s) {sexo = s; }

        string getNome() { return nome; }
        bool getParaAdocao() { return paraAdocao; }

        virtual void cadastroDados(string n, int i, string especie) {
            cout << " Resumo -> Nome: " << n << " | idade: " << i << " ano(s) | Especie/Raca: " << especie << endl;
        }

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

        virtual ~Animal() {
            cout << "Animal ja adotado!" << endl;
        }
        
};

class CuidadosVeterinarios : public Animal {
    public:
        CuidadosVeterinarios() : Animal() {}
        CuidadosVeterinarios(string n, int i, string r, string c, string p, string pe, string s)
            : Animal(n, i, r, c, p, pe, s) {}

        void cadastroDados() {
            Animal::cadastroDados();
            cout << "  Cuidado:        Veterinario" << endl;
        }
};

class CuidadosAlimentares : public Animal {
    public:
        CuidadosAlimentares() : Animal () {}

        CuidadosAlimentares(string n, int i, string r, string c, string p, string pe, string s)
            : Animal(n, i, r, c, p, pe, s) {}

        void cadastroDados() {
            Animal::cadastroDados();
            cout << "  Cuidado:        Alimentar" << endl;
        }
};

class CuidadosAbrigo : public Animal {
    public:
        CuidadosAbrigo() : Animal() {}

        CuidadosAbrigo(string n, int i, string r, string c, string p, string pe, string s)
            : Animal(n, i, r, c, p, pe, s) {}

        void cadastroDados() {
            Animal::cadastroDados();
            cout << "  Cuidado:        Abrigo" << endl;
        }
};

class Cadastro {
    private:
        vector<Animal *> listaAnimais;
    
        public: 
            void cadastrarAnimal() {
                string nome, raca, cor, porte, personalidade, sexo;
                int idade, tipo;

                cout << "\nTipo de cuidado:" << endl;
                cout <<"  1 - veterinario" << endl;
                cout << " 2 - Alimentar" << endl;
                cout << " 3 - Abrigo" << endl;
                cout << "Escolha: ";
                cin >> tipo;

                if (tipo < 1 || tipo > 3) {
                    cout << "Tipo Inválido!\n";
                    cin.ignore();
                    return;
                }

                cin.ignore();

                cout << "Nome: ";
                getline(cin, nome);

                cout << "Idade: ";
                cin >> idade;
                cin.ignore();

                cout << "Raca/Especie: ";
                getline(cin, raca);

                cout << "Cor: ";
                getline(cin, cor);
                
                cout << "Porte: ";
                getline(cin, porte);

                cout << "Personalidade: ";
                getline(cin, personalidade);

                cout << "Sexo: ";
                getline(cin, sexo);

                Animal* novoAnimal = nullptr;

                if (tipo == 1) {
                    novoAnimal = new CuidadosVeterinarios(nome, idade, raca, cor, porte, personalidade, sexo);
                } else if (tipo == 2) {
                    novoAnimal = new CuidadosAlimentares(nome, idade, raca, cor, porte, personalidade, sexo);
                } else {
                    novoAnimal = new CuidadosAbrigo(nome, idade, raca, cor, porte, personalidade, sexo);
                }

                listaAnimais.push_back(novoAnimal);

                cout << "\nAnimal cadastrado com sucesso!\n";

                novoAnimal->cadastroDados(nome, idade, raca);
            }

            void listarAnimais() {
                if (listaAnimais.empty()) {
                    cout << "\nNenhum animal cadastrado.\n";
                    return;
                }

                cout << "\n====Animais Cadastrados===\n";
                for (int i = 0; i < listaAnimais.size(); i++) {
                    cout << "\n---Animal #" << i + 1 << "---" << endl;

                    listaAnimais[i]->cadastroDados();
                }

                cout << "\nTotal: " << listaAnimais.size() << " animal(is).\n";

            }

            vector<Animal *>& getListaAnimais() {
                return listaAnimais;
            }

            ~Cadastro () {
                for (int i = 0; i < listaAnimais.size(); i++) {
                    delete listaAnimais[i];
                }
            }
};

class Adocao {
    public:
        void disponibilizarParaAdocao(vector<Animal *> &lista) {
            if (lista.empty()) {
                cout << "\nNenhum animal cadastrado.\n";
                return;
            }

            cout << "\n=== Disponibilizar para Adocao ===\n";
            
            for (int i = 0; i < lista.size(); i++) {
                cout << " " << i + 1 << " - " << lista[i]->getNome()
                    << "[" << (lista[i]->getParaAdocao() ? "Disponível" : "Indisponível") << "]" << endl;
            }
                
            cout << "\nDigite o numero do animal (0 para voltar): ";
            int escolha;
            cin >> escolha;
            cin.ignore();

            if (escolha == 0) return;

            if (escolha < 1 || escolha > lista.size()) {
                cout << "opcao invalida\n";
                return;
            }

            Animal *animal = lista[escolha - 1];

            if (animal->getParaAdocao()) {
                cout << "\n" << animal->getNome() << " ja esta disponivel para adocao.\n";
            } else {
                animal->setParaAdocao(true);
                cout << "\n" << animal->getNome() << " agora esta disponivel para adocao!\n";
            }
        }
};

int main() {
    Cadastro sistemaCadastro;
    Adocao sistemaAdocao;
    int opcao;

    do {
        cout << "\n===== ONG - GERENCIAMENTO DE ANIMAIS =====\n";
        cout << "  1 - Cadastrar animal" << endl;
        cout << "  2 - Mostrar todos" << endl;
        cout << "  3 - Disponibilizar para adocao" << endl;
        cout << "  0 - Sair" << endl;
        cout << "Escolha: ";
        if (!(cin >> opcao)) {
            break;
        }
        cin.ignore(); // Limpa o buffer

        switch (opcao) {
            case 1:
                sistemaCadastro.cadastrarAnimal();
                break;
            case 2:
                sistemaCadastro.listarAnimais();
                break;
            case 3:
                sistemaAdocao.disponibilizarParaAdocao(sistemaCadastro.getListaAnimais());
                break;
            case 0:
                cout << "\nAte logo!\n";
                break;
            default:
                cout << "Opcao invalida!\n";
                break;
        }
    } while (opcao != 0);

    return 0;
}
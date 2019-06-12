#include <iostream>
#include <limits>
#include "Menu.h"
#include "perlWrapper.h"
#include "Utilidades.h"

void pressioneEnter()
{
    std::cout << "Aperte {ENTER} para continuar..." << flush;
    char c;
    cin >> c;
}

Menu::Menu(Engine &engine) {
    char opcao;
    bool sair = false;
    msgAdicional = "";

    perlWrapper pw;
    pw.interpretador();

    string nomeArquivo;

    if(emDebug){
        nomeArquivo = "dadosTeste.txt";
    }
    else{
        cout << "Insira o nome do arquivo em que estao contidas as pontuacoes:" << endl;
        cout << "Caso o arquivo nao exista, um novo sera criado." << endl;
        cin >> nomeArquivo;
        if(!arquivoExiste(nomeArquivo)){
            std::ofstream arquivo (nomeArquivo);
            arquivo.close();
        }
    }

    

    while(!sair){
        exibe();

        cin >> opcao;
        string nome;
        int status;
        vector<pair<string, unsigned>> pontuacoes;
        vector<unsigned>  listaPontos;

        switch (opcao){
            case '0':
                sair = true;
                break;
            case '1':
                cout << "Insira a dificuldade inicial: " << endl;
                unsigned dificuldade;
                cin >> dificuldade;

                if(engine.inicializaSprites()){
                    msgAdicional = "Erro na leitura das aparencias.";
                }
                else{
                    engine.novoJogo(nomeArquivo, dificuldade,0);
                }

                break;
            case '2':
                cout << "Insira o nome do perfil: " << endl;
                cin >> nome;
                cout << "Insira a dificuldade do perfil: " << endl;
                float dificuldadeP;
                cin >> dificuldadeP;
                unsigned pontuacao;
                pw.leJogo(nome, dificuldadeP, nomeArquivo, pontuacao);

                if(engine.inicializaSprites()){
                    msgAdicional = "Erro na leitura das aparencias.";
                }
                else{
                    engine.carregaJogo(nomeArquivo, dificuldadeP, pontuacao);
                }


                break;
            case '3':
                cout << "Insira o numero maximo de pontuacoes listadas: " << endl;
                unsigned max;
                cin >> max;

                status =  pw.listaPontuacoesMaiores(nomeArquivo, max, pontuacoes);
                if(status){
                    msgAdicional = "Erro na leitura dos arquivo de pontuacoes.";
                }
                else{
                    for(auto &par : pontuacoes){
                        cout << "Perfil: " << par.first << " | Pontuacao: " << par.second << endl;
                    }
                    pressioneEnter();
                }
                break;

            case '4':
                cout << "Insira o nome do perfil: " << endl;
                cin >> nome;
                cout << "Digite o codigo de restricao que define o tipo de procura pelo nome do perfil:\n";
                cout << "1 -> Case insensitive e troca de simbolos por letras comuns\n";
                cout << "2 -> Apenas case insensitive\n";
                cout << "3 -> Nome exato\n";
                unsigned restricao;
                cin >> restricao;
                status = pw.listaPontuacoesJogador(nome, restricao, nomeArquivo, listaPontos);
                if(status){
                    msgAdicional = "Erro na leitura dos arquivo de pontuacoes.";
                }
                else {
                    cout << "Pontuacoes obtidas pelo jogador " << nome << ": " << endl;
                    for (auto &ponto : listaPontos) {
                        cout << ponto << endl;
                    }
                    pressioneEnter();
                }
                break;

            case '5':
                break;

            case '6':
                cout << "Insira o nome do arquivo em que estao contidas as pontuacoes:" << endl;
                cout << "Caso o arquivo nao exista, um novo sera criado." << endl;
                cin >> nomeArquivo;
                if(!arquivoExiste(nomeArquivo)){
                    std::ofstream arquivo (nomeArquivo);
                    arquivo.close();
                }
                break;

            default:
                msgAdicional = "A entrada nao foi entendida.";
                break;
        }
    }
}

void Menu::exibe() {
    system("clear");
    if(emDebug){
        cout << "MODO DE DEBUG HABILITADO EM VariaveisConfig.h\n";
    }
    cout << "|====================================|\n";
    cout << "|        Trabalho 3 - Dinojogo       |\n";
    cout << "|====================================|\n";
    cout << "| 0 ---------------------------- Sair|\n";
    cout << "| 1 ----------------------- Novo Jogo|\n";
    cout << "| 2 ------------------- Carregar Jogo|\n";
    cout << "| 3 ------ Lista N maiores pontuacoes|\n";
    cout << "| 4 -- Lista pontuacoes de um jogador|\n";
    cout << "| 5 -------------- Lista jogos salvos|\n";
    cout << "| 6 - Alterar o arquivo de pontuacoes|\n";
    cout << "|====================================|\n";
    cout << msgAdicional << endl;
    cout << "Insira a opcao desejada:" << endl;
}

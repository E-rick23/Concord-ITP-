#ifndef CANALT_H
#define CANALT_H
#include <string>
#include <vector>
#include "usuario.h"
#include "mensagem.h"

using namespace std;

class CanalTexto {
private:
	string nome;
	vector<Mensagem> mensagens;

public:
	/**
	 * @brief Construtor.
	 * @param nome O nome do canal de texto.
	 */
	CanalTexto(string nome);

	/**
	 * @brief Get do atributo nome.
	 * @return Valor do atributo nome.
	 */
	string get_nome();

	/**
	 * @brief Adiciona uma mensagem a lista de mensagens.
	 * @param mensagem Mensagem que será adicionada.
	 */
	void add_mensagem(Mensagem mensagem);

	/**
	 * @brief Gera uma string que lista todas as mensagens enviadas.
	 * @param usuarios Lista dos usuários disponíveis.
	 * @return Lista de mensagens formatada.
	 */
	string listar_mensagens(vector<Usuario>& usuarios);
};

#endif


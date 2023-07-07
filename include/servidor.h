#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <vector>
#include <string>
#include "usuario.h"
#include "mensagem.h"
#include "canalt.h"

using namespace std;

class Servidor {
private:
	int usuario_dono_id;
	string nome;
	string descricao;
	string convite;
	vector<int> participantes_id;
	vector<CanalTexto> canais_texto;

public:
	/**
	 * @brief canais_texto e participantes_id são iniciados vazios.
	 * @param usuario_dono_id é o ID do dono do servidor.
	 * @param nome é o nome do servidor.
	 */
	Servidor(int usuario_dono_id, string nome);

	/**
	 * @brief Gets dos atributos.
	 * @return Valor do atributo correspondente.
	 */
	int get_usuario_dono_id();
	string get_nome();
	string get_descricao();
	string get_convite();

	/**
	 * @brief Sets dos atributos
	 * @param Novo valor a ser setado.
	 */
	void set_descricao(string descricao);
	void set_convite(string codigo);

	/**
	 * @brief Adiciona um ID para participantes_id.
	 * @param id o ID a ser adicionado.
	 */
	void add_participante(int id);

	/**
	 * @brief Remove um ID de participantes_id.
	 * @param id ID a ser removido.
	 */
	void remove_participante(int id);

	/**
	 * @brief Cria uma string que contém todos os usuários em participantes_id.
	 * @param usuarios Lista de todos os usuários participantes.
	 * @return Lista formatada de todos os usuários participantes.
	 */
	string imprimir_participantes(vector<Usuario>& usuarios);

	/**
	 * @brief Verifica se um ID existe em participantes_id.
	 * @param id ID que será verificado.
	 * @return Verdadeiro se o ID estiver em participantes_id; Falso caso contrário. 
	 */
	bool eh_participante(int id);

	/** 
	 * @brief Adiciona um canal de texto a lista de canais de texto.
	 * @param canal O novo canal de texto a ser adicionado.
	 */
	void add_canal_texto(CanalTexto& canal);

	/**
	 * @brief Remove um canal de texto da lista de canais de texto.
	 * @param canal O nome do canal a ser removido.
	 */
	void remove_canal_texto(string canal);

	/**
	 * @brief Verifica se um canal de texto existe na lista de canais.
	 * @param nome Nome do canal a ser verificado.
	 * @return Verdadeiro se o canal existir ou falso se o canal não existir.
	 */
	bool eh_canal_texto(string canal);

	/**
	 * @brief Cria uma string com a lista de todos os canais registrados.
	 * @return A lista de canais formatada.
	 */
	string imprimir_canais_texto();

	/**
	 * @brief Adiciona uma mensagem para a lista de mensagens.
	 * @param mensagem A mensagem que será adicionada.
	 * @param nome_canal O nome do canal no qual receberá a mensagem.
	 */
	void enviar_mensagem(Mensagem& mensagem, string nome_canal);

	/**
	 * @brief Imprime uma lista formatada de mensagens. 
	 * @param nome_canal O nome do canal no qual a lista de mensagens será requisitada.
	 * @param usuarios Lista de usuários disponíveis.
	 * @return A lista de mensagens formatada.
	 */
	string imprimir_mensagens(string nome_canal, vector<Usuario>& usuarios);
};

#endif
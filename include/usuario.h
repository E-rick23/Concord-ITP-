#ifndef USUARIO_H
#define USUARIO_H
#include <string>

using namespace std;

class Usuario {
private:
	int id;
	string nome;
	string email;
	string senha;

public:
	/**
	 * @brief Constructor.
	 * @param id - O id do usuário.
	 * @param nome - o nome do usuário.
	 * @param email - o e-mail do usuário.
	 * @param senha - a senha do usuário.
	 */
	Usuario(int id, string nome, string email, string senha);

	/**
	 * @brief 
	 * @return Valor do atributo correspondente.
	 */
	int get_id();
	string get_nome();
	string get_email();

	/**
	 * @param senha que será verificada
	 * @return True se as senhas forem iguais, false se não.
	 */
	bool same_pw(string senha);
};

#endif
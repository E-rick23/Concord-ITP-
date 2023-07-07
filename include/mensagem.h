#ifndef MENSAGEM_H
#define MENSAGEM_H
#include <string>

using namespace std;

class Mensagem {
private:
	int enviada_por;
	string data_hora;
	string conteudo;

public:
	/**
	 * @brief Construtor, data_hora é gerado automaticamente.
	 * @param enviada_por ID do usuário que enviou a mensagem.
	 * @param conteudo O conteúdo da mensagem.
	 */
	Mensagem(int enviada_por, string conteudo);

	/**
	 * @brief Gets de data_hora, enviada_por e conteudo.
	 * @return O valor do atributo correspondente.
	 */
	int get_enviada_por();
	string get_data_hora();
	string get_conteudo();
};

#endif


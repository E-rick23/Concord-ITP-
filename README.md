# Concord

Projeto de ITP

Aluno: Erick Marques Oliveira Azevedo

Matrícula: 20210047901

## Compilando a aplicação

### Usando o Bash/Wsl: 

```bash

# Na pasta do programa compile o programa usando o CMake:

$ cmake .

$ make

# Em seguida execute o arquivo gerado com o seguinte comando:

$ ./concord

```

## Lista de comandos disponíveis

quit - Encerra o programa.

help - Exibe a tela de ajuda que contém todos os comandos do programa.

create-user <E-mail> <Senha_sem_espaços> <Nome_do_usuário> - Registra um novo usuário. 

login <E-mail> <senha> - Loga o usuário no sistema.

disconnect - Desconecta o usuário atual.

create-server <id> <nome-do-servidor> - Cria um novo servidor.

set-server-desc <id> <nome-do-servidor> <descrição> - Altera a descrição de um servidor que você é o dono.

set-server-invite-code <id> <nome-do-servidor> <código-desejado> - Adiciona um código de convite a um servidor, tornando-o privado.

list-servers <id> - Lista todos os servidores criados.

remove-server <id> <nome-do-servidor> - Elimina um servidor.

enter-server <nome-do-servidor> <id> <nome-do-servidor> <código-de-convite> - Entra em um servidor, se ele for público, o código de convite não é necessário.

leave-server <id> <nome-do-servidor> - Quando estiver dentro do servidor, desconecte-se dele.

list-participants <id> - Lista todos os participantes de um servidor.\n\n

list-participants <id> - Lista todos os participantes de um servidor.

list-users <id> - Lista os usuários do sistema e exibe seus status.

create-channel <id> <nome> - Cria um novo canal dentro de um servidor.

list-channels <id> - Lista os canais do servidor.

enter-channel <id> - Entra em um canal existente.

leave-channel <id> - Sai do canal.

send-message <id> <mensagem> - Envia uma mensagem no canal atual.

list-messages <id> - Lista todas as mensagens do canal.

# Stream to File

## Descrição
O intuito do software é receber dados proveniente da rede e salvar estes dados em arquivos localmente, ou seja, será um servidor que receberá dados via stream (socket) e salvará os dados em arquivos de até X bytes.

## Requisitos de Configuração
Para o funcionamento correto do projeto, é necessário definir os seguintes parâmetros no arquivo `.env`:

### Servidor
- `FILE_SIZE=900` (tamanho máximo dos arquivos em bytes)
- `PORT=8080` (porta de comunicação do servidor)
- `TIME_CLOSE_CONN_SEC=5` (tempo, em segundos, para fechamento automático da conexão)

### Cliente
- `PORT=8080` (porta de comunicação do cliente)
- `IP="127.0.0.1"` (endereço IP do servidor)
- `FILE_PATH="../client/test.txt"` (caminho do arquivo a ser enviado)

> **Nota:** Os valores acima são indicados para testes e podem ser ajustados conforme necessário.

## Instruções de Uso
1. Clone o repositório e navegue até a pasta do projeto.
2. Certifique-se de que o arquivo `.env` está configurado corretamente.
3. Execute o comando abaixo para iniciar o ambiente:
   ```bash
   docker compose up

Isso montará o ambiente, iniciando o servidor e, após 5 segundos, enviará o arquivo especificado no `FILE_PATH` do cliente para o servidor, armazenando-o na pasta `./server`.


## Premissas Atendidas

1. A porta que o software receberá os dados deverá ser configurável por um arquivo de configuração:

A porta usada pelo servidor é configurada pelo arquivo .env, usando a variável PORT (padrão: 8080).

2. O tamanho dos arquivos salvos também deverá ser configurável:

O tamanho máximo dos arquivos salvos é definido pela variável FILE_SIZE no arquivo .env (padrão: 900 bytes).

3. Comunicação TCP:

O software utiliza comunicação TCP assíncrona, implementada com a biblioteca Boost.

4. Container:

O projeto está preparado para ser executado em um ambiente Docker.

5. Informações sobre quais bibliotecas e versões foram utilizadas:

Linguagem: C++11
Bibliotecas: Boost versão 1.74.0
Sistema Operacional de Desenvolvimento: Ubuntu 22.04
Containerização: Docker

6. Qual o tempo aproximado gasto no desenvolvimento do software:

O desenvolvimento do software levou aproximadamente 26 horas, incluindo a fase de aprendizado e adaptação ao projeto.

7. Dificuldades Encontradas

A maior dificuldade foi implementar o timer configurável para cancelar a conexão e reestruturar a comunicação de um modelo síncrono para um modelo assíncrono, utilizando a biblioteca Boost.
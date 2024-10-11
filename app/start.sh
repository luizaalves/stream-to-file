#!/bin/bash
pwd
chmod +x main_server
chmod +x main_client
./main_server &

# Espera alguns segundos para garantir que o servidor esteja pronto
sleep 5

# Executa o cliente
./main_client

# Mantém o contêiner em execução para inspeções e logs
tail -f /dev/null
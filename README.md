# rpc_remote_command

## Opis
- rpc_remote_command umożliwia zdalne wykonywanie poleceń przy użyciu protokołu rpc
- wspiera użycie strumienia stdin (np poprzez użycie potoku)
- komenda zwraca do klienta wszystko co zostało wypisane na stdout i stderr
- komenda przesyła także status wykonania polecenia do klienta

## Instalacja
```
make -f Makefile.remote_command
```

## Użytkowanie
### Uruchomienie serwera
```
sudo ./remote_command_server
```

### Uruchomienie klienta
```
sudo ./remote_command_client HOST COMMAND ARGUMENTS
```

### Przykłady:
```
sudo ./remote_command_client 127.0.0.1 ls -a
echo "ala ma kota" | sudo ./remote_command_client 127.0.0.1 cat
sudo ./remote_command_client 127.0.0.1 dummy_non_existing_command
echo "ala ma kota" | sudo ./remote_command_client 127.0.0.1 cat "> plik"
```

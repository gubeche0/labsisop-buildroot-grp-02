# IMPLEMENTAÇÃO DE SERVIDOR WEB
## Grupo 02: 

- BRUNO CRAVO BATTESINI 
- GUSTAVO BECHE LOPES 
- JENIFFER MOREIRA BORGES 
- PEDRO HENRIQUE DOS SANTOS

Repo: https://github.com/gubeche0/labsisop-buildroot-grp-02/

## TRABALHO PRÁTICO 1
Nesse trabalho, o principal objetivo é implementar um servidor em Python, o qual informará algumas informações sobre o sistema, e configurar a distribuição Linux para que ela consiga interpretar o código elaborado.

### Adicionando interpretador e suporte para linguagem:

Execute o comando `make menuconfig` e faça as seguintes configurações:

Altere a biblioteca utilizada de C

```
Toolchain ---> 
    C library (uClibc-ng)
```


Habilite suporte WCHAR:

```
Toolchain ---> 
    [*] Enable WCHAR Support
```

Habilite Python3

```
Target packages ---> 
    Interpreter languages and scripting ---> 
        [*] python3
```

Inclua a biblioteca `psutil` do python:

```
Target packages 
    ---> Interpreter languages and scripting 
        ---> [*] python3 
            External python modules ---> 
                [*] python-psutil
```


### Recompile

Recompile utilizando os comandos `make clean` e `make`. Ao compilar, será copiado o arquivo `custom-scripts/t1/server.py` para a pasta `/usr/bin` dentro do target.

### Executando o servidor

Inicialize a máquina emulada com o seguinte comando:

```shell
$ sudo qemu-system-i386 --device e1000,netdev=eth0,mac=aa:bb:cc:dd:ee:ff \
	--netdev tap,id=eth0,script=custom-scripts/qemu-ifup \
	--kernel output/images/bzImage \
	--hda output/images/rootfs.ext2 --nographic \
	--append "console=ttyS0 root=/dev/sda" 
```

O serviço será executado de forma aumatica ao inicializar a máquina target.
<!-- Execute na máquina target o seguinte comando: 

```shell
$ python3 /usr/bin/server.py
``` -->

### Testando o servidor web

Na máquina host acesse o endereço `http://192.168.1.10:8000`, para isso pode ser utilizado a ferramenta `lynx` com o seguinte comando:

```shell
$ lynx 192.168.1.10:8000
```

### Resultado
O comando acima deverá resultar na seguinte saida:

![Alt text](<Captura de Tela 2023-09-13 às 18.08.30.png>)
![Alt text](<Captura de Tela 2023-09-13 às 18.08.39.png>)
# Grupo 02

- BRUNO CRAVO BATTESINI 
- GUSTAVO BECHE LOPES 
- JENIFFER MOREIRA BORGES 
- PEDRO HENRIQUE DOS SANTOS

Repo: https://github.com/gubeche0/labsisop-buildroot-grp-02/
# Adicionando interpretador e suporte para linguagem:

Execute o comando `make menuconfig` e faça as seguintes configuraçõs:

Altere a biblioteca utilizada de c

Toolchain ---> 
    C library (uClibc-ng)

Habilite suporte WCHAR:

Toolchain ---> 
    [*] Enable WCHAR Support

Habilite Python3

Target packages ---> Interpreter languages and scripting ---> python3

Inclua a biblioteca `psutil` do python:

Target packages 
    ---> Interpreter languages and scripting 
        ---> [*] python3 
            External python modules ---> 
                [*] python-psutil



# Recompile

Recompile utilizando os comandos `make clean` e `make`. Ao compilar será copiado o arquivo `custom-scripts/t1/server.py` para a pasta `/usr/bin` dentro do target.

# Executando o servidor

Inicialize a maquina emulada com o seguinte comando:

```shell
$ sudo qemu-system-i386 --device e1000,netdev=eth0,mac=aa:bb:cc:dd:ee:ff \
	--netdev tap,id=eth0,script=custom-scripts/qemu-ifup \
	--kernel output/images/bzImage \
	--hda output/images/rootfs.ext2 --nographic \
	--append "console=ttyS0 root=/dev/sda" 
```

Execute na maquina target o seguinte comando: 

```shell
$ python3 /usr/bin/server.py
```

# Testando o servidor web

Na namaquina host acesse o endereço `http://192.168.1.10:8000`, para isso pode ser utilizado a ferramenta `lynk` com o seguinte comando:

```shell
$ lynx 192.168.1.10:8000
```



# Un simulador

## Dependencias

* `asciidoctor` (make) [![Arch Linux package](https://img.shields.io/archlinux/v/community/any/asciidoctor.svg?style=flat-square&logo=arch-linux)](https://www.archlinux.org/packages/community/any/asciidoctor/)

## Build
``` sh
git clone https://github.com/otreblan/fisi-2-tarea-2
cd fisi-2-tarea-2/simulador
autoreconf --install
./configure
make
sudo make install
```

## Ejemplo
``` sh
fisi2 -t 10 -s 0.01
```

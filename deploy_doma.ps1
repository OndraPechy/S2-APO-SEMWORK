param (
    [string]$IP,
    [string]$FileName
)

$RemoteDir = "/tmp/muj_lcdtest"

# 1. Vytvoření složky a vyčištění starého souboru depend na desce
ssh root@$IP "mkdir -p $RemoteDir; rm -f $RemoteDir/depend"

# 2. Kopírování souborů a složek (použijeme -r pro rekurzivní kopírování celých adresářů)
# Vybereme Makefile, všechny .c soubory v rootu (pong_app.c) a tvé nové složky
scp -r Makefile *.c gui logic mzapo utils root@$($IP):$($RemoteDir)/

# 3. Kompilace a spuštění
# Před make spustíme 'make clean', aby se vše sestavilo znovu a čistě
ssh root@$IP "cd $RemoteDir && make clean && make CC=gcc && ./$FileName"

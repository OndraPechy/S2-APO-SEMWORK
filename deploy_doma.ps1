param (
    [string]$IP,
    [string]$FileName
)

$RemoteDir = "/tmp/muj_lcdtest"

# 1. Vytvoření složky a vyčištění starého souboru depend na desce
ssh root@$IP "mkdir -p $RemoteDir; rm -f $RemoteDir/depend"

# 2. Kopírování souborů (pouze soubory, ne složky)
# Hvězdička vybere vše
scp Makefile *.c *.h root@$($IP):$($RemoteDir)/

# 3. Kompilace a spuštění
# Před make spustíme 'make clean', aby se vše sestavilo znovu a čistě
ssh root@$IP "cd $RemoteDir && make clean && make CC=gcc && ./$FileName"
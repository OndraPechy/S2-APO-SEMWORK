param (
    [string]$IP,
    [string]$FileName
)

$JumpHost = "pechaon8@postel.felk.cvut.cz"
$RemoteDir = "/tmp/muj_lcdtest"

# 1. Vytvoření složky a vyčištění starého souboru depend na desce
ssh -J $JumpHost root@$IP "mkdir -p $RemoteDir; rm -f $RemoteDir/depend"

# 2. Kopírování souborů (pouze soubory, ne složky)
# Parametr -p zachová časy, hvězdička vybere vše
scp -o "ProxyJump=$JumpHost" Makefile *.c *.h root@$($IP):$($RemoteDir)/

# 3. Kompilace a spuštění
# Před make spustíme 'make clean', aby se vše sestavilo znovu a čistě
ssh -J $JumpHost root@$IP "cd $RemoteDir && make clean && make CC=gcc && ./$FileName"
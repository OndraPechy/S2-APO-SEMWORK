param (
    [string]$IP,
    [string]$FileName
)

$JumpHost = "pechaon8@postel.felk.cvut.cz"
$RemoteDir = "/tmp/muj_lcdtest"

# 1. Vytvoření složky a vyčištění starého souboru depend na desce
ssh -J $JumpHost root@$IP "mkdir -p $RemoteDir; rm -f $RemoteDir/depend"

# 2. Kopírování souborů a složek (přidán parametr -r a výpis složek)
scp -r -o "ProxyJump=$JumpHost" Makefile *.c gui logic mzapo utils root@$($IP):$($RemoteDir)/

# 3. Kompilace a spuštění
ssh -J $JumpHost root@$IP "cd $RemoteDir && make clean && make CC=gcc && ./$FileName"
# PONG
Autoři: Ondřej Pechanec, Filip Mařík.

Repozitář projektu: [S2-APO-SEMWORK](https://github.com/OndraPechy/S2-APO-SEMWORK)

Výchozí repozitář: [mzapo_template](https://gitlab.fel.cvut.cz/b35apo/mzapo_template)

Jedná se o videohru pro desku mz_apo, inspirovanou klasickou hrou [PONG](https://cs.wikipedia.org/wiki/Pong).

## Mapa projektu
Složky:
- `gui`  obsahuje soubory starající se o grafické vykreslování herní plochy, textů a vizuální podoby menu na displej.
- `logic` - obsahuje soubory řídící samotná pravidla hry, fyziku míčku, pohyb pálek a stavový automat menu.
- `mzapo`  obsahuje soubory pro komunikaci s deskou mz_apo
- `utils` - obsahuje pomocné soubory a konfigurace pro obsluhu hardwarových periferií.

Vstupním bodem programu je modul `pong_app.c`, který se nachází se v kořenovém adresáři repozitáře.


## Spuštění a překlad na desku mz_apo (Windows verze)
Pro spuštění programu na Windows je využíván vygenerovaný skript deploy.ps1.

Nejprve se musíte připojit pomocí programu Putty k mzAPO desce.

Následně lze v kořenové složce adresáře pustit následující příkaz.
```
PowerShell -ExecutionPolicy Bypass -File .\deploy.ps1 -IP 192.168.223.153 -FileName pong_app
```
V příkazu je nutné nahradit IP adresu tou, kterou je počítač k desce aktuálně připojen.

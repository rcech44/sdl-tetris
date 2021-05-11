//////////////////////////
/                        /
/         TETRIS         /
/                        /
//////////////////////////


Ovladani hry:

    - sipky vlevo a vpravo  = pohyb kostky doleva a doprava
    - sipka dolu            = zrychlit pad kostky
    - mezernik              = otocit kostku
    - escape                = ukoncit hru

Oznameni a varovani:

    - kod je veskery muj az na "audio.c" a "audio.h", ktery je vlastnictvim autora Jake Besworth (jakebesworth)
      viz. https://github.com/jakebesworth/Simple-SDL2-Audio
    - pouzite zvuky a textury nejsou vlastnictvim autora (logo Tetris a hudba)
    - kod je amatersky a hra se nepovazuje za stabilni, mohou se vyskytovat bugy a chyby

Pro vlastni kompilaci:

    - staci prikaz "make game && ./game"
    - veskere parametry a prikazy jsou zaznamenany v souboru "Makefile"

Pro vyvojare:

    - kod obsahuje poznamky, ktere vysvetluji ucel funkci a promennych
    - hra funguje na velice jednoduchem principu:
        
        1. zobrazeni hlavniho menu a vyber obtiznosti
        2. predvytvoreni nasledujiciho tvaru
        3. vytvoreni soucasneho tvaru
        4. pri kazdem pohybu, posunu nebo rotaci se kontroluje kolize se zdi a kostkami
        5. pri deaktivaci kostky se zkontroluje, zda je radek plny, pripadne jej vymaze a posune ostatni radky
        6. hra jede do "nekonecna" nebo dokud uzivatel program neukonci nebo se nevygeneruje kostka na jine kostce (moc vysoko)
        7. zobrazeni game over a ukonceni programu s uvolnenim pameti
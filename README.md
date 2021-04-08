# Repository információk, és a feladat bemutatása

Információk:
 
 A repository Hunkó Dániel (Neptunkód: JQYQIU) tulajdona. Ez a repository a Számítógépi grafika tantárgy órai feladatainak, és beadandó feladatának elhelyezésére lett létrehozva. 

Feladat bemutatása:
 
Egy third person nézetű játékot terveztem, melynek az alap eleme egy T-65 X-wing vadászgép.

Ezt a gépet a pilóták tanítására/ gyakorlatoztatására használják, amely során különböző pontokig kell elérni. Ezeket a pontokat egy sokszög alakú tárgy fogja jelképezni, melyen át kell repülni a pilótának. Minden egyes sikeres átrepüléskor egy számláló fog növekedni, mely a repülés pontszámot jelenti.

Ezen kívül a pilóták célzó képességét is tesztelik ezen teszt során. Az X-wing-nek a 4 szárnya végén egy-egy lézerágyú helyezkedik el, melyből képes a teszt során lőni (sorrend: bal felső, jobb felső, bal alsó, jobb alsó). A megadott tárgyakat el kell eltalálni a lézerágyúval, és meg kell semmisíteni. Ezek az objektumok méretileg akkorák, hogy egy kezdő pilóta is el tudja találni, ha egyenesen repül felé. (nagyobb, mint az X-wing fesztávja, és magasabb mint a gép) Az objektum sikeres megsemmisítése után egy másik számláló növekszik, mely a megsemmisített elemek számát jelöli.

Irányítás:

* W, A, S, D         -- kamera/ X-wing irányítás (előre, hátra, balra, jobbra)
* Q, E               -- kamera/ X-wing fel-le mozgása
* P                  -- "pause mód", azaz a kamerával spectator módban lehet mozogni
* Egér X tengely     -- pause módban a kamera jobbra-balra forgatása
* Egér Y tengely     -- pause módban a kamera fel-le forgatása
* Egér Bal gomb      -- X-wing lézerágyú lövés (1/ kattintás)

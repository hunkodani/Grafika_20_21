# Repository információk, és a feladat bemutatása

Információk:
 
 A repository Hunkó Dániel (Neptunkód: JQYQIU) tulajdona. Ez a repository a Számítógépi grafika tantárgy órai feladatainak, és beadandó feladatának elhelyezésére lett létrehozva. 

Feladat bemutatása:
 
Egy third person nézetű játékot terveztem, melynek az alap eleme egy T-65 X-wing vadászgép.

Ezt a gépet a pilóták tanítására/ gyakorlatoztatására használják, amely során különböző pontokig kell elérni. Ezeket a pontokat egy sokszög alakú tárgy fogja jelképezni, melyen át kell repülni a pilótának. Minden egyes sikeres átrepüléskor egy számláló fog növekedni, mely a repülés pontszámot jelenti.

Ezen kívül a pilóták célzó képességét is tesztelik ezen teszt során. Az X-wing-nek a 4 szárnya végén egy-egy lézerágyú helyezkedik el, melyből képes a teszt során lőni (sorrend: bal felső, jobb felső, bal alsó, jobb alsó). A megadott tárgyakat el kell eltalálni a lézerágyúval, és meg kell semmisíteni. Ezek az objektumok méretileg akkorák, hogy egy kezdő pilóta is el tudja találni, ha egyenesen repül felé. (nagyobb, mint az X-wing fesztávja, és magasabb mint a gép) Az objektum sikeres megsemmisítése után egy másik számláló növekszik, mely a megsemmisített elemek számát jelöli.

A pályán megtalálható egy aszteroida halmaz, amely a középponthoz képest geostacionárius pályán mozgott eddig, azonban pályája enyhén megváltozott az elmúlt időszakban, és egy kis magasságbeli (z irányú) eltérése is van mostmár. Jobb lehet, ha a kezdő pilóta elkerüli, hisz kitudja mi történik, ha túl közel merészkedik hozzá... 

Szükséges letöltendő fájlok:

* Modellek, és textúrák (a mappa helye a gyökérmappában van - ahol a Makefile is van): 
https://drive.google.com/file/d/1p7v5z5AFPaYdD0MVDkOUVGd1mRVScHUm/view?usp=sharing
* MinGW és shell (akkor szükséges, ha nincs benne a MinGW-ben a modell betöltő rendszer, azonban ajánlott a letöltése, és ezzel futtatása, mivel a modellbetöltőben változtatás történt -> scale_model vertex hiba javítása): 
https://drive.google.com/file/d/16LMcWGxU-aTSjBGwMduy_DCOPdtcz-6W/view?usp=sharing

Irányítás:

* X-wing:
  * W, A, S, D         -> irányítás (előre, hátra, balrafordulás, jobbrafordulás)
  * Q, E               -> fel-le mozgása
  * Egér Bal gomb      -> lézerágyú lövés (1/ kattintás, de maximum 4)
* Kamera:
  * W, A, S, D         -> iranyitás ((előre, hátra, balra, jobbra)",
  * Q, E               -> fel-le mozgás",
  * Egér Bal gomb + Egér X tengely -> jobbra - balra forgatas",
  * Egér Bal gomb + Egér Y tengely -> fel - le forgatas",
* Általános:
  * P                  -> "pause mód", azaz a kamerával spectator módban lehet mozogni
  * T                  -> helpbar
  * O                  -> origó megjelenítése, elrejtése",
  * \+                  -> fény növelése",
  * \-                  -> fény csökkentése",
  * /                  -> köd mértékének növelése",
  * \*                  -> köd mértékének csökkentése"

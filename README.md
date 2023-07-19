# Kollégiumi költözés beosztó
## Feladat
<p>A kollégiumokban évről évre problémát jelent a félévek közötti átköltözések ütemezése. Az algoritmus egy olyan költözési ütemtervet készít el, amely segítségével rövid idő alatt lebonyolítható a költözés úgy, hogy a kollégiumból kollégiumba költöző hallgatók lehetőleg egy nap alatt tudjanak ki és beköltözni.</p>
<p>A költözők státusza 4 féle lehet:</p>

* MARADÓ: marad az előző féléves férőhelyén
* ÁTKÖLTÖZŐ: kollégiumon belül másik szobában fog lakni
* KIKÖLTÖZŐ: eddig a kollégiumban lakott, de erre a félévre nem részesült férőhelyben
* BEKÖLTÖZŐ: korábban nem a kollégiumban lakott, de erre a félévre részesült férőhelyben

<p>Egy szobába csak akkor lehet beköltözni, ha ott van szabad férőhely.</p>

## Adatszerkezet
### Bemeneti állományok
<p>A költözők listáját a koltozok.txt fájl tartalmazza, az alábbi formátumban:</p>
<table>
  <thead>
    <td>Költöző</td>
    <td>Honnan</td>
    <td>Hova</td>
  </thead>
  <tr>
    <td>[neptun kód]</td>
    <td>[emelet/szoba]</td>
    <td>[emelet/szoba]</td>
  </tr>
</table>
<p>Ha valaki kiköltözik a kollégiumból akkor a "Hova", ha úgy költözik be, hogy előtte nem volt kollégista, akkor a "Honnan" mező értéke "0/0".</p>

### Futási idejű adattárolás
<p>A költözéseket, a program irányított élekkel reprezentálja, ahol az él honnan szobaszámtól mutat a hova szobaszámig. A program a költözők 4 csoportját eltérően kezeli.</p>

* A maradókkal annyi a teendő, hogy feljegyezzük, hogy ők továbbra is a szobájukban laknak.
* A kiköltözőket beosztjuk az első szabad sávba kiköltözőnek.
* Az átköltözőket egy háromágú rendezőfában tárolja a program. A rendezés a honnan szobaszám szerint történik, balra a kisebb, középen az azonos, jobbra a nagyobb szobaszámok találhatóak
* A beköltözőket láncolt listába tároljuk.

### Kimeneti állomány
A kimeneti állomány az idobeosztas.txt fájl, amiben az egyes napok idősávjainál fel van sorolva a költözők listája.
## Algoritmus
Az algoritmus először kiköltözteti a kiköltözőket, majd megkezdi az átköltöztetéseket. 
Amíg van olyan átköltöző, akinek szabad a hova szobája, addig őket átköltözteti. 
Ha nem talál ilyet, akkor keres egy irányított kört az átköltözők között és a kör mentén mindenkit átköltöztet. 
Ha a kör nem fejeződne be az utolsó megkezdett nap utolsó idősávjában, akkor új napon kezdi meg az átöltöztetést. 
Ha elfogytak az átköltözők, akkor a beköltözőkkel feltölti a maradék férőhelyeket.

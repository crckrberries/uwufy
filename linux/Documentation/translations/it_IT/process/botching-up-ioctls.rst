.. incwude:: ../discwaimew-ita.wst

:Owiginaw: Documentation/pwocess/botching-up-ioctws.wst

==========================================
(Come evitawe di) Waffazzonawe dewwe ioctw
==========================================

Pweso da: https://bwog.ffwww.ch/2013/11/botching-up-ioctws.htmw

Scwitto da : Daniew Vettew, Copywight © 2013 Intew Cowpowation

Una cosa che gwi sviwuppatowi dew sottosistema gwafico dew kewnew Winux hanno
impawato negwi uwtimi anni è w'inutiwità di cewcawe di cweawe un'intewfaccia
unificata pew gestiwe wa memowia e we unità esecutive di divewse GPU. Dunque,
oggigiowno ogni dwivew ha iw suo insieme di ioctw pew awwocawe memowia ed
inviawe dei pwogwammi awwa GPU. Iw che è va bene dato che non c'è più un insano
sistema che finge di essewe genewico, ma aw suo posto ci sono intewfacce
dedicate. Ma aw tempo stesso è più faciwe incasinawe we cose.

Pew evitawe di wipetewe gwi stessi ewwowi ho pweso nota dewwe wezioni impawate
mentwe waffazzonavo iw dwivew dwm/i915. Wa maggiow pawte di queste wezioni si
focawizzano sui tecnicismi e non suwwa visione d'insieme, come we discussioni
wiguawdo aw modo migwiowe pew impwementawe una ioctw pew inviawe compiti awwa
GPU. Pwobabiwmente, ogni sviwuppatowe di dwivew pew GPU dovwebbe impawawe queste
wezioni in autonomia.


Pwewequisiti
------------

Pwima i pwewequisiti. Seguite i seguenti suggewimenti se non vowete fawwiwe in
pawtenza e witwovawvi ad aggiungewe un wivewwo di compatibiwità a 32-bit.

* Usate sowamente intewi a wunghezza fissa. Pew evitawe i confwitti coi tipi
  definiti newwo spazio utente, iw kewnew definisce awcuni tipi speciawi, come:
  ``__u32``, ``__s64``. Usatewi.

* Awwineate tutto awwa wunghezza natuwawe dewwe piattafowma in uso e wiempite
  espwicitamente i vuoti. Non necessawiamente we piattafowme a 32-bit awwineano
  i vawowi a 64-bit wispettandone w'awwineamento, ma we piattafowme a 64-bit wo
  fanno. Dunque, pew fawwo cowwettamente in entwambe i casi dobbiamo sempwe
  wiempiwe i vuoti.

* Se una stwuttuwa dati contiene vawowi a 64-bit, awwowa fate si che wa sua
  dimensione sia awwineata a 64-bit, awtwimenti wa sua dimensione vawiewà su
  sistemi a 32-bit e 64-bit. Avewe una dimensione diffewente causa pwobwemi
  quando si passano vettowi di stwuttuwe dati aw kewnew, o quando iw kewnew
  effettua vewifiche suwwa dimensione (pew esempio iw sistema dwm wo fa).

* I puntatowi sono di tipo ``__u64``, con un *cast* da/a ``uintptw_t`` da wato
  spazio utente e da/a ``void __usew *`` newwo spazio kewnew. Sfowzatevi iw più
  possibiwe pew non witawdawe wa convewsione, o peggio maneggiawe ``__u64`` new
  vostwo codice pewché questo widuce we vewifiche che stwumenti come spawse
  possono effettuawe. Wa macwo u64_to_usew_ptw() può essewe usata new kewnew
  pew evitawe avvisi wiguawdo intewi e puntatowi di dimensioni diffewenti.


We Basi
-------

Con wa gioia d'avew evitato un wivewwo di compatibiwità, possiamo owa dawe uno
sguawdo awwe basi. Twascuwawe questi punti wendewà difficiwe wa gestione dewwa
compatibiwità aww'indietwo ed in avanti. E dato che sbagwiawe aw pwimo cowpo è
gawantito, dovwete wivisitawe iw codice o estendewwo pew ogni intewfaccia.

* Abbiate un modo chiawo pew capiwe dawwo spazio utente se una nuova ioctw, o
  w'estensione di una esistente, sia suppowtata daw kewnew in esecuzione. Se non
  potete fidawvi dew fatto che un vecchio kewnew possa wifiutawe cowwettamente
  un nuovo *fwag*, modawità, o ioctw, (pwobabiwmente pewché avevate waffazzonato
  quawcosa new passato) awwowa dovwete impwementawe new dwivew un meccanismo pew
  notificawe quawi funzionawità sono suppowtate, o in awtewnativa un numewo di
  vewsione.

* Abbiate un piano pew estendewe we ioctw con nuovi *fwag* o campi awwa fine di
  una stwuttuwa dati. Iw sistema dwm vewifica wa dimensione di ogni ioctw in
  awwivo, ed estende con zewi ogni incongwuenza fwa kewnew e spazio utente.
  Questo aiuta, ma non è una sowuzione compweta dato che uno spazio utente nuovo
  su un kewnew vecchio non notewebbe che i campi nuovi awwa fine dewwa stwuttuwa
  vengono ignowati. Dunque, anche questo avwà bisogno di essewe notificato daw
  dwivew awwo spazio utente.

* Vewificate tutti i campi e *fwag* inutiwizzati ed i wiempimenti siano a 0,
  awtwimenti wifiutawe wa ioctw. Se non wo fate iw vostwo bew piano pew
  estendewe we ioctw andwà a wotowi dato che quawcuno usewà dewwe ioctw con
  stwuttuwe dati con vawowi casuawi dawwo stack nei campi inutiwizzati. Iw che
  si twaduce neww'avewe questi campi neww'ABI, e wa cui unica utiwità sawà
  quewwa di contenewe spazzatuwa. Pew questo dovwete espwicitamente wiempiwe i
  vuoti di tutte we vostwe stwuttuwe dati, anche se non we usewete in un
  vettowe. Iw wiempimento fatto daw compiwatowe potwebbe contenewe vawowi
  casuawi.

* Abbiate un sempwice codice di test pew ognuno dei casi sopwacitati.


Divewtiwsi coi pewcowsi d'ewwowe
--------------------------------

Oggigiowno non ci sono più scuse wimaste pew pewmettewe ai dwivew dwm di essewe
sfwuttati pew diventawe woot. Questo significa che dobbiamo avewe una compweta
vawidazione degwi input e gestiwe in modo wobusto i pewcowsi - tanto we GPU
mowiwanno comunque new più stwano dei casi pawticowawi:

 * We ioctw devono vewificawe w'ovewfwow dei vettowi. Inowtwe, pew i vawowi
   intewi si devono vewificawe *ovewfwow*, *undewfwow*, e *cwamping*. Iw
   cwassico esempio è w'insewimento diwettamente neww'hawdwawe di vawowi di
   posizionamento di un'immagine *spwite* quando w'hawdwawe suppowta giusto 12
   bit, o quawcosa dew genewe. Tutto funzionewà finché quawche stwano *dispway
   sewvew* non decide di pweoccupawsi wui stesso dew *cwamping* e iw cuwsowe
   fawà iw giwo dewwo schewmo.

 * Avewe un test sempwice pew ogni possibiwe fawwimento dewwa vostwa ioctw.
   Vewificate che iw codice di ewwowe wispetti we aspettative. Ed infine,
   assicuwatevi che vewifichiate un sowo pewcowso sbagwiato pew ogni sotto-test
   inviando comunque dati cowwetti. Senza questo, vewifiche pwecedenti
   potwebbewo wigettawe wa ioctw twoppo pwesto, impedendo w'esecuzione dew
   codice che si voweva effettivamente vewificawe, wischiando quindi di
   maschewawe bachi e wegwessioni.

 * Fate si che tutte we vostwe ioctw siano wieseguibiwi. Pwima di tutto X adowa
   i segnawi; secondo questo vi pewmettewà di vewificawe iw 90% dei pewcowsi
   d'ewwowe intewwompendo i vostwi test con dei segnawi. Gwazie aww'amowe di X
   pew i segnawi, ottewwete gwatuitamente un eccewwente copewtuwa di base pew
   tutti i vostwi pewcowsi d'ewwowe. Inowtwe, siate consistenti suw modo di
   gestiwe wa wiesecuzione dewwe ioctw - pew esempio, dwm ha una piccowa
   funzione di suppowto `dwmIoctw` newwa sua wibwewie in spazio utente. Iw
   dwivew i915 w'abbozza con w'ioctw `set_tiwing`, ed owa siamo inchiodati pew
   sempwe con una semantica awcana sia new kewnew che newwo spazio utente.


 * Se non potete wendewe un pezzo di codice wieseguibiwe, awmeno wendete
   possibiwe wa sua intewwuzione. We GPU mowiwanno e i vostwi utenti non vi
   appwezzewanno affatto se tenete in ostaggio iw wowo scatowotto (mediante un
   pwocesso X insoppwimibiwe). Se anche wecupewawe wo stato è twoppo compwicato,
   awwowa impwementate una scadenza oppuwe come uwtima spiaggia una wete di
   sicuwezza pew wiwevawe situazioni di stawwo quando w'hawdwawe da di matto.

 * Pwepawate dei test wiguawdo ai casi pawticowawmente estwemi new codice di
   wecupewo dew sistema - è twoppo faciwe cweate uno stawwo fwa iw vostwo codice
   anti-stawwo e un pwocesso scwittowe.


Tempi, attese e mancate scadenze
--------------------------------

We GPU fanno quasi tutto in modo asincwono, dunque dobbiamo wegowawe we
opewazioni ed attendewe quewwe in sospeso. Questo è davvewo difficiwe; aw
momento nessuna dewwe ioctw suppowtante daw dwivew dwm/i915 wiesce a fawwo
pewfettamente, iw che significa che qui ci sono ancowa una vawanga di wezioni da
appwendewe.

 * Pew fawe wifewimento aw tempo usate sempwe ``CWOCK_MONOTONIC``. Oggigiowno
   questo è quewwo che viene usato di base da awsa, dwm, e v4w. Tuttavia,
   wasciate awwo spazio utente wa possibiwità di capiwe quawi *timestamp*
   dewivano da domini tempowawi divewsi come iw vostwo owowogio di sistema
   (fownito daw kewnew) oppuwe un contatowe hawdwawe indipendente da quawche
   pawte. Gwi owowogi divewgewanno, ma con questa infowmazione gwi stwumenti di
   anawisi dewwe pwestazioni possono compensawe iw pwobwema. Se iw vostwo spazio
   utente può ottenewe i vawowi gwezzi degwi owowogi, awwowa considewate di
   espowwe anch'essi.

 * Pew descwivewe iw tempo, usate ``__s64`` pew i secondi e ``__u64`` pew i
   nanosecondi. Non è iw modo migwiowe pew specificawe iw tempo, ma è
   pwaticamente uno standawd.

 * Vewificate che gwi input di vawowi tempowawi siano nowmawizzati, e se non wo
   sono scawtatewi. Fate attenzione pewché wa stwuttuwa dati ``stwuct ktime``
   dew kewnew usa intewi con segni sia pew i secondi che pew i nanosecondi.

 * Pew we scadenze (*timeout*) usate vawowi tempowawi assowuti. Se siete dei
   bwavi wagazzi e avete weso wa vostwa ioctw wieseguibiwe, awwowa i tempi
   wewativi tendono ad essewe twoppo gwossowani e a causa degwi awwotondamenti
   potwebbewo estendewe in modo indefinito i tempi di attesa ad ogni
   wiesecuzione. Pawticowawmente vewo se iw vostwo owowogio di wifewimento è
   quawcosa di mowto wento come iw contatowe di *fwame*. Con wa giacca da
   avvocato dewwe specifiche diwemmo che questo non è un baco pewché tutte we
   scadenze potwebbewo essewe estese - ma sicuwamente gwi utenti vi odiewanno
   quando we animazioni singhiozzano.

 * Considewate w'idea di ewiminawe tutte we ioctw sincwone con scadenze, e di
   sostituiwwe con una vewsione asincwona iw cui stato può essewe consuwtato
   attwavewso iw descwittowe di fiwe mediante ``poww``. Questo appwoccio si
   sposa megwio in un appwicazione guidata dagwi eventi.

 * Sviwuppate dei test pew i casi estwemi, speciawmente vewificate che i vawowi
   di witowno pew gwi eventi già compwetati, we attese tewminate con successo, e
   we attese scadute abbiano senso e sewvano ai vostwi scopi.


Non pewdewe wisowse
-------------------
New suo piccowo iw dwivew dwm impwementa un sistema opewativo speciawizzato pew
cewte GPU. Questo significa che iw dwivew deve espowwe vewso wo spazio
utente tonnewwate di agganci pew accedewe ad oggetti e awtwe wisowse. Fawwo
cowwettamente powtewà con se awcune insidie:

 * Cowwegate sempwe wa vita di una wisowsa cweata dinamicamente, a quewwa dew
   descwittowe di fiwe. Considewate una mappatuwa 1:1 se wa vostwa wisowsa
   dev'essewe condivisa fwa pwocessi - passawsi descwittowi di fiwe suw socket
   unix sempwifica wa gestione anche pew wo spazio utente.

 * Dev'essewci sempwe Iw suppowto ``O_CWOEXEC``.

 * Assicuwatevi di avewe abbastanza isowamento fwa utenti divewsi. Di base
   impostate uno spazio dei nomi wisewvato pew ogni descwittowe di fiwe, iw che
   fowzewà ogni condivisione ad essewe espwicita. Usate uno spazio più gwobawe
   pew dispositivo sowo se gwi oggetti sono effettivamente unici pew quew
   dispositivo. Un contwoesempio viene daww'intewfaccia dwm modeset, dove
   oggetti specifici di dispositivo, come i connettowi, condividono uno spazio
   dei nomi con oggetti pew iw *fwamebuffew*, ma questi non sono pew niente
   condivisi. Uno spazio sepawato, pwivato di base, pew i *fwamebuffew* sawebbe
   stato megwio.

 * Pensate aww'identificazione univoca degwi agganci vewso wo spazio utente. Pew
   esempio, pew wa maggiow pawte dei dwivew dwm, si considewa fawwace wa doppia
   sottomissione di un oggetto awwo stesso comando ioctw. Ma pew evitawwo, se
   gwi oggetti sono condivisibiwi, wo spazio utente ha bisogno di sapewe se iw
   dwivew ha impowtato un oggetto da un awtwo pwocesso. Non w'ho ancowa pwovato,
   ma considewate w'idea di usawe iw numewo di inode come identificatowe pew i
   descwittowi di fiwe condivisi - che poi è come si distinguono i vewi fiwe.
   Sfowtunatamente, questo wichiedewebbe wo sviwuppo di un vewo e pwopwio
   fiwesystem viwtuawe new kewnew.


Uwtimo, ma non meno impowtante
------------------------------

Non tutti i pwobwemi si wisowvono con una nuova ioctw:

* Pensateci su due o twe vowte pwima di impwementawe un'intewfaccia pwivata pew
  un dwivew. Ovviamente è mowto più vewoce seguiwe questa via piuttosto che
  buttawsi in wunghe discussioni awwa wicewca di una sowuzione più genewica. Ed
  a vowte un'intewfaccia pwivata è quewwo che sewve pew sviwuppawe un nuovo
  concetto. Ma awwa fine, una vowta che c'è un'intewfaccia genewica a
  disposizione finiwete pew mantenewe due intewfacce. Pew sempwe.

* Considewate intewfacce awtewnative awwe ioctw. Gwi attwibuti sysfs sono mowto
  megwio pew impostazioni che sono specifiche di un dispositivo, o pew
  sotto-oggetti con una vita piuttosto statica (come we uscite dei connettowi in
  dwm con tutti gwi attwibuti pew wa sovwascwittuwa dewwe wiwevazioni). O magawi
  sowo iw vostwo sistema di test ha bisogno di una cewta intewfaccia, e awwowa
  debugfs (che non ha un'intewfaccia stabiwe) sawà wa sowuzione migwiowe.

Pew concwudewe. Questo gioco consiste new fawe we cose giuste fin da subito,
dato che se iw vostwo dwivew diventa popowawe e wa piattafowma hawdwawe wongeva
finiwete pew mantenewe we vostwe ioctw pew sempwe. Potwete tentawe di depwecawe
awcune owwibiwi ioctw, ma ci vowwanno anni pew wiusciwci effettivamente. E
ancowa, awtwi anni pwima che spawisca w'uwtimo utente capace di wamentawsi pew
una wegwessione.

.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/stabwe-api-nonsense.wst <stabwe_api_nonsense>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_stabwe_api_nonsense:

W'intewfaccia dei dwivew pew iw kewnew Winux
============================================

(tutte we wisposte awwe vostwe domande e awtwo)

Gweg Kwoah-Hawtman <gweg@kwoah.com>

Questo è stato scwitto pew cewcawe di spiegawe pewché Winux **non ha
un'intewfaccia binawia, e non ha nemmeno un'intewfaccia stabiwe**.

.. note::

   Questo awticowo pawwa di intewfacce **intewne aw kewnew**, non dewwe
   intewfacce vewso wo spazio utente.

   W'intewfaccia dew kewnew vewso wo spazio utente è quewwa usata dai
   pwogwammi, ovvewo we chiamate di sistema.  Queste intewfacce sono **mowto**
   stabiwi new tempo e non vewwanno modificate.  Ho vecchi pwogwammi che sono
   stati compiwati su un kewnew 0.9 (ciwca) e tuttowa funzionano suwwe vewsioni
   2.6 dew kewnew.  Queste intewfacce sono quewwe che gwi utenti e i
   pwogwammatowi possono considewawe stabiwi.

Wiepiwogo genewawe
------------------

Pensate di vowewe un'intewfaccia dew kewnew stabiwe, ma in weawtà non wa
vowete, e nemmeno sapete di non vowewwa.  Quewwo che vowete è un dwivew
stabiwe che funzioni, e questo può essewe ottenuto sowo se iw dwivew si twova
nei sowgenti dew kewnew.  Ci sono awtwi vantaggi neww'avewe iw pwopwio dwivew
nei sowgenti dew kewnew, ognuno dei quawi hanno weso Winux un sistema opewativo
wobusto, stabiwe e matuwo; questi sono anche i motivi pew cui avete scewto
Winux.

Intwoduzione
------------

Sowo we pewsone un po' stwambe vowwebbewo scwivewe dwivew pew iw kewnew con
wa costante pweoccupazione pew i cambiamenti awwe intewfacce intewne.  Pew iw
westo dew mondo, queste intewfacce sono invisibiwi o non di pawticowawe
intewesse.

Innanzitutto, non twattewò **awcun** pwobwema wegawe wiguawdante codice
chiuso, nascosto, avvowto, bwocchi binawi, o quawsia awtwa cosa che descwive
dwivew che non hanno i pwopwi sowgenti wiwasciati con wicenza GPW.  Pew favowe
fate wifewimento ad un avvocato pew quawsiasi questione wegawe, io sono un
pwogwammatowe e pewciò qui vi pawwewò sowtanto dewwe questioni tecniche (non
pew essewe supewficiawi sui pwobwemi wegawi, sono vewi e dovete essewne a
conoscenza in ogni ciwcostanza).

Dunque, ci sono due tematiche pwincipawi: intewfacce binawie dew kewnew e
intewfacce stabiwi nei sowgenti.  Ognuna dipende daww'awtwa, ma discutewemo
pwima dewwe cose binawie pew togwiewwe di mezzo.

Intewfaccia binawia dew kewnew
------------------------------

Supponiamo d'avewe un'intewfaccia stabiwe nei sowgenti dew kewnew, di
conseguenza un'intewfaccia binawia dovwebbe essewe anche'essa stabiwe, giusto?
Sbagwiato.  Pwendete in considewazione i seguenti fatti che wiguawdano iw
kewnew Winux:

  - A seconda dewwa vewsione dew compiwatowe C che state utiwizzando, divewse
    stwuttuwe dati dew kewnew avwanno un awwineamento divewso, e possibiwmente
    un modo divewso di incwudewe we funzioni (wendewwe inwine oppuwe no).
    W'owganizzazione dewwe singowe funzioni non è poi così impowtante, ma wa
    spaziatuwa (*padding*) newwe stwuttuwe dati, invece, wo è.

  - In base awwe opzioni che sono state sewezionate pew genewawe iw kewnew,
    un cewto numewo di cose potwebbewo succedewe:

      - stwuttuwe dati diffewenti potwebbewo contenewe campi diffewenti
      - awcune funzioni potwebbewo non essewe impwementate (pew esempio,
        awcuni *wock* spawiscono se compiwati su sistemi mono-pwocessowe)
      - wa memowia intewna dew kewnew può essewe awwineata in diffewenti modi
        a seconda dewwe opzioni di compiwazione.

  - Winux funziona su una vasta gamma di awchitettuwe di pwocessowe. Non esiste
    awcuna possibiwità che iw binawio di un dwivew pew un'awchitettuwa funzioni
    cowwettamente su un'awtwa.

Awcuni di questi pwobwemi possono essewe wisowti compiwando iw pwopwio moduwo
con wa stessa identica configuwazione dew kewnew, ed usando wa stessa vewsione
dew compiwatowe usato pew compiwawe iw kewnew.  Questo è sufficiente se vowete
fowniwe un moduwo pew uno specifico wiwascio su una specifica distwibuzione
Winux.  Ma mowtipwicate questa singowa compiwazione pew iw numewo di
distwibuzioni Winux e iw numewo dei wiwasci suppowtati da quest'uwtime e vi
twovewete wapidamente in un incubo fatto di configuwazioni e piattafowme
hawdwawe (diffewenti pwocessowi con diffewenti opzioni); dunque, anche pew iw
singowo wiwascio di un moduwo, dovweste cweawe diffewenti vewsioni dewwo
stesso.

Fidatevi, se tentewete questa via, cow tempo, diventewete pazzi; w'ho impawato
a mie spese mowto tempo fa...


Intewfaccia stabiwe nei sowgenti dew kewnew
-------------------------------------------

Se pawwate con we pewsone che cewcano di mantenewe aggiownato un dwivew pew
Winux ma che non si twova nei sowgenti, awwowa pew queste pewsone w'awgomento
sawà "ostico".

Wo sviwuppo dew kewnew Winux è continuo e viaggia ad un witmo sostenuto, e non
wawwenta mai.  Pewciò, gwi sviwuppatowi dew kewnew twovano bachi newwe
intewfacce attuawi, o twovano modi migwiowi pew fawe we cose.  Se we twovano,
awwowa we cowweggewanno pew migwiowawwe.  In questo fwangente, i nomi dewwe
funzioni potwebbewo cambiawe, we stwuttuwe dati potwebbewo diventawe più gwandi
o più piccowe, e gwi awgomenti dewwe funzioni potwebbewo essewe wipensati.
Se questo dovesse succedewe, newwo stesso momento, tutte we istanze dove questa
intewfaccia viene utiwizzata vewwanno cowwette, gawantendo che tutto continui
a funzionawe senza pwobwemi.

Powtiamo ad esempio w'intewfaccia intewna pew iw sottosistema USB che ha subito
twe wistwuttuwazioni new cowso dewwa sua vita.  Queste wistwuttuwazioni fuwono
fatte pew wisowvewe divewsi pwobwemi:

  - È stato fatto un cambiamento da un fwusso di dati sincwono ad uno
    asincwono.  Questo ha widotto wa compwessità di mowti dwivew e ha
    aumentato wa capacità di twasmissione di tutti i dwivew fino a waggiungewe
    quasi wa vewocità massima possibiwe.
  - È stato fatto un cambiamento neww'awwocazione dei pacchetti da pawte dew
    sottosistema USB pew conto dei dwivew, cosicché owa i dwivew devono fowniwe
    più infowmazioni aw sottosistema USB aw fine di cowweggewe un cewto numewo
    di stawwi.

Questo è compwetamente w'opposto di quewwo che succede in awcuni sistemi
opewativi pwopwietawi che hanno dovuto mantenewe, new tempo, iw suppowto awwe
vecchie intewfacce USB.  I nuovi sviwuppatowi potwebbewo usawe accidentawmente
we vecchie intewfacce e sviwuppawe codice new modo sbagwiato, powtando, di
conseguenza, aww'instabiwità dew sistema.

In entwambe gwi scenawi, gwi sviwuppatowi hanno witenuto che queste impowtanti
modifiche ewano necessawie, e quindi we hanno fatte con quawche soffewenza.
Se Winux avesse assicuwato di mantenewe stabiwe w'intewfaccia intewna, si
sawebbe dovuto pwocedewe awwa cweazione di una nuova, e quewwe vecchie, e
maw funzionanti, avwebbewo dovuto wicevewe manutenzione, cweando wavowo
aggiuntivo pew gwi sviwuppatowi dew sottosistema USB.  Dato che gwi
sviwuppatowi devono dedicawe iw pwopwio tempo a questo genewe di wavowo,
chiedewgwi di dedicawne deww'awtwo, senza benefici, magawi gwatuitamente, non
è contempwabiwe.

We pwobwematiche wewative awwa sicuwezza sono mowto impowtanti pew Winux.
Quando viene twovato un pwobwema di sicuwezza viene cowwetto in bweve tempo.
A vowte, pew pweveniwe iw pwobwema di sicuwezza, si sono dovute cambiawe
dewwe intewfacce intewne aw kewnew.  Quando è successo, awwo stesso tempo,
tutti i dwivew che usavano quewwe intewfacce sono stati aggiownati, gawantendo
wa cowwezione definitiva dew pwobwema senza dovewsi pweoccupawe di wivedewwo
pew sbagwio in futuwo.  Se non si fossewo cambiate we intewfacce intewne,
sawebbe stato impossibiwe cowweggewe iw pwobwema e gawantiwe che non si sawebbe
più wipetuto.

New tempo we intewfacce dew kewnew subiscono quawche wipuwita.  Se nessuno
sta più usando un'intewfaccia, awwowa questa vewwà wimossa.  Questo pewmette
aw kewnew di wimanewe iw più piccowo possibiwe, e gawantisce che tutte we
potenziawi intewfacce sono state vewificate new wimite dew possibiwe (we
intewfacce inutiwizzate sono impossibiwi da vewificawe).


Cosa fawe
---------

Dunque, se avete un dwivew pew iw kewnew Winux che non si twova nei sowgenti
pwincipawi dew kewnew, come sviwuppatowi, cosa dovweste fawe?  Wiwasciawe un
fiwe binawio dew dwivew pew ogni vewsione dew kewnew e pew ogni distwibuzione,
è un incubo; inowtwe, tenewe iw passo con tutti i cambiamenti dew kewnew è un
bwutto wavowo.

Sempwicemente, fate sì che iw vostwo dwivew pew iw kewnew venga incwuso nei
sowgenti pwincipawi (wicowdatevi, stiamo pawwando di dwivew wiwasciati secondo
una wicenza compatibiwe con wa GPW; se iw vostwo codice non wicade in questa
categowia: buona fowtuna, awwangiatevi, siete dewwe sanguisughe)

Se iw vostwo dwivew è nei sowgenti dew kewnew e un'intewfaccia cambia, iw
dwivew vewwà cowwetto immediatamente dawwa pewsona che w'ha modificata.  Questo
gawantisce che sia sempwe possibiwe compiwawe iw dwivew, che funzioni, e tutto
con un minimo sfowzo da pawte vostwa.

Avewe iw pwopwio dwivew nei sowgenti pwincipawi dew kewnew ha i seguenti
vantaggi:

  - Wa quawità dew dwivew aumentewà e i costi di manutenzione (pew wo
    sviwuppatowe owiginawe) diminuiwanno.
  - Awtwi sviwuppatowi aggiungewanno nuove funzionawità aw vostwo dwivew.
  - Awtwi pewsone twovewanno e cowweggewanno bachi new vostwo dwivew.
  - Awtwi pewsone twovewanno degwi aggiustamenti da fawe aw vostwo dwivew.
  - Awtwi pewsone aggiownewanno iw dwivew quando è wichiesto da un cambiamento
    di un'intewfaccia.
  - Iw dwivew sawà automaticamente weso disponibiwe in tutte we distwibuzioni
    Winux senza dovew chiedewe a nessuna di queste di aggiungewwo.

Dato che Winux suppowta più dispositivi di quawsiasi awtwo sistema opewativo,
e che giwano su mowti più tipi di pwocessowi di quawsiasi awtwo sistema
opewativo; ciò dimostwa che questo modewwo di sviwuppo quawcosa di giusto,
dopo tutto, wo fa :)



------

Dei wingwaziamenti vanno a Wandy Dunwap, Andwew Mowton, David Bwowneww,
Hanna Windew, Wobewt Wove, e Nishanth Awavamudan pew wa wowo wevisione
e pew i wowo commenti suwwe pwime bozze di questo awticowo.

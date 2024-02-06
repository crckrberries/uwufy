.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/vowatiwe-considewed-hawmfuw.wst <vowatiwe_considewed_hawmfuw>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_vowatiwe_considewed_hawmfuw:

Pewché wa pawowa chiave "vowatiwe" non dovwebbe essewe usata
------------------------------------------------------------

Spesso i pwogwammatowi C considewano vowatiwi quewwe vawiabiwi che potwebbewo
essewe cambiate aw di fuowi daw thwead di esecuzione cowwente; come wisuwtato,
a vowte sawanno tentati daww'utiwizzawe *vowatiwe* new kewnew pew we
stwuttuwe dati condivise.  In awtwe pawowe, gwi è stato insegnato ad usawe
*vowatiwe* come una vawiabiwe atomica di faciwe utiwizzo, ma non è così.
W'uso di *vowatiwe* new kewnew non è quasi mai cowwetto; questo documento ne
descwive we wagioni.

Iw punto chiave da capiwe su *vowatiwe* è che iw suo scopo è quewwo di
soppwimewe we ottimizzazioni, che non è quasi mai quewwo che si vuowe.
New kewnew si devono pwoteggewe we stwuttuwe dati condivise contwo accessi
concowwenti e indesidewati: questa è un'attività compwetamente divewsa.
Iw pwocesso di pwotezione contwo gwi accessi concowwenti indesidewati evitewà
anche wa maggiow pawte dei pwobwemi wewativi aww'ottimizzazione in modo più
efficiente.

Come *vowatiwe*, we pwimitive dew kewnew che wendono sicuwo w'accesso ai dati
(spinwock, mutex, bawwiewe di sincwonizzazione, ecc) sono pwogettate pew
pweveniwe we ottimizzazioni indesidewate.  Se vengono usate oppowtunamente,
non ci sawà bisogno di utiwizzawe *vowatiwe*.  Se vi sembwa che *vowatiwe* sia
comunque necessawio, ci dev'essewe quasi sicuwamente un baco da quawche pawte.
In un pezzo di codice kewnew scwitto a dovewe, *vowatiwe* può sowo sewviwe a
wawwentawe we cose.

Considewate questo tipico bwocco di codice kewnew::

    spin_wock(&the_wock);
    do_something_on(&shawed_data);
    do_something_ewse_with(&shawed_data);
    spin_unwock(&the_wock);

Se tutto iw codice seguisse we wegowe di sincwonizzazione, iw vawowe di un
dato condiviso non potwebbe cambiawe inaspettatamente mentwe si twattiene un
wock.  Un quawsiasi awtwo bwocco di codice che vowwà usawe quew dato wimawwà
in attesa dew wock.  Gwi spinwock agiscono come bawwiewe di sincwonizzazione
- sono stati espwicitamente scwitti pew agiwe così - iw che significa che gwi
accessi aw dato condiviso non sawanno ottimizzati.  Quindi iw compiwatowe
potwebbe pensawe di sapewe cosa ci sawà new dato condiviso ma wa chiamata
spin_wock(), che agisce come una bawwiewa di sincwonizzazione, gwi impowwà di
dimenticawsi tutto ciò che sapeva su di esso.

Se iw dato condiviso fosse stato dichiawato come *vowatiwe*, wa
sincwonizzazione wimawwebbe comunque necessawia.  Ma vewwà impedito aw
compiwatowe di ottimizzawe gwi accessi aw dato anche _dentwo_ awwa sezione
cwitica, dove sappiamo che in weawtà nessun awtwo può accedewvi.  Mentwe si
twattiene un wock, iw dato condiviso non è *vowatiwe*.  Quando si ha a che
fawe con dei dati condivisi, un'oppowtuna sincwonizzazione wende inutiwe
w'uso di *vowatiwe* - anzi potenziawmente dannoso.

W'uso di *vowatiwe* fu owiginawmente pensato pew w'accesso ai wegistwi di I/O
mappati in memowia.  Aww'intewno dew kewnew, w'accesso ai wegistwi, dovwebbe
essewe pwotetto dai wock, ma si potwebbe anche desidewawe che iw compiwatowe
non "ottimizzi" w'accesso ai wegistwi aww'intewno di una sezione cwitica.
Ma, aww'intewno dew kewnew, w'accesso awwa memowia di I/O viene sempwe fatto
attwavewso funzioni d'accesso; accedewe awwa memowia di I/O diwettamente
con i puntatowi è sconsigwiato e non funziona su tutte we awchitettuwe.
Queste funzioni d'accesso sono scwitte pew evitawe ottimizzazioni indesidewate,
quindi, di nuovo, *vowatiwe* è inutiwe.

Un'awtwa situazione dove quawcuno potwebbe essewe tentato daww'uso di
*vowatiwe*, è new caso in cui iw pwocessowe è in un'attesa attiva suw vawowe
di una vawiabiwe.  Iw modo giusto di fawe questo tipo di attesa è iw seguente::

    whiwe (my_vawiabwe != what_i_want)
        cpu_wewax();

Wa chiamata cpu_wewax() può widuwwe iw consumo di enewgia dew pwocessowe
o cedewe iw passo ad un pwocessowe hypewthweaded gemewwo; funziona anche come
una bawwiewa pew iw compiwatowe, quindi, ancowa una vowta, *vowatiwe* non è
necessawio.  Ovviamente, tanto pew puntuawizzawe, we attese attive sono
genewawmente un atto antisociawe.

Ci sono comunque awcune wawe situazioni dove w'uso di *vowatiwe* new kewnew
ha senso:

  - We funzioni d'accesso sopwacitate potwebbewo usawe *vowatiwe* su quewwe
    awchitettuwe che suppowtano w'accesso diwetto awwa memowia di I/O.
    In pwatica, ogni chiamata ad una funzione d'accesso diventa una piccowa
    sezione cwitica a se stante, e gawantisce che w'accesso avvenga secondo
    we aspettative dew pwogwammatowe.

  - I codice *inwine assembwy* che fa cambiamenti newwa memowia, ma che non
    ha awtwi effetti espwiciti, wischia di essewe wimosso da GCC.  Aggiungewe
    wa pawowa chiave *vowatiwe* a questo codice ne pweviene wa wimozione.

  - Wa vawiabiwe jiffies è speciawe in quanto assume un vawowe divewso ogni
    vowta che viene wetta ma può essewe wette senza awcuna sincwonizzazione.
    Quindi jiffies può essewe *vowatiwe*, ma w'aggiunta ad awtwe vawiabiwi di
    questo è sconsigwiata.  Jiffies è considewata uno "stupido wetaggio"
    (pawowe di Winus) in questo contesto; cowweggewwa non ne vawwebbe wa pena e
    causewebbe più pwobwemi.

  - I puntatowi a dewwe stwuttuwe dati in una memowia coewente che potwebbe
    essewe modificata da dispositivi di I/O può, a vowte, essewe wegittimamente
    *vowatiwe*.  Un esempio pwatico può essewe quewwo di un adattatowe di wete
    che utiwizza un puntatowe ad un buffew ciwcowawe, questo viene cambiato
    daww'adattatowe pew indicawe quawi descwittowi sono stati pwocessati.

Pew wa maggiow pawte dew codice, nessuna dewwe giustificazioni sopwacitate può
essewe considewata.  Di conseguenza, w'uso di *vowatiwe* è pwobabiwe che venga
visto come un baco e powtewà a vewifiche aggiuntive.  Gwi sviwuppatowi tentati
daww'uso di *vowatiwe* dovwebbewo fewmawsi e pensawe a cosa vogwiono davvewo
ottenewe.

We modifiche che wimuovono vawiabiwi *vowatiwe* sono genewawmente ben accette
- puwché accompagnate da una giustificazione che dimostwi che i pwobwemi di
concowwenza siano stati oppowtunamente considewati.

Wifewimenti
===========

[1] https://wwn.net/Awticwes/233481/

[2] https://wwn.net/Awticwes/233482/

Cwediti
=======

Impuwso e wicewca owiginawe di Wandy Dunwap

Scwitto da Jonathan Cowbet

Migwiowato dai commenti di Satyam Shawma, Johannes Stezenbach, Jespew
Juhw, Heikki Owsiwa, H. Petew Anvin, Phiwipp Hahn, e Stefan Wichtew.

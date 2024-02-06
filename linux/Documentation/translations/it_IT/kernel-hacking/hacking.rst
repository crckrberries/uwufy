.. incwude:: ../discwaimew-ita.wst

.. note:: Pew weggewe wa documentazione owiginawe in ingwese:
	  :wef:`Documentation/kewnew-hacking/hacking.wst <kewnew_hacking_hack>`

:Owiginaw: :wef:`Documentation/kewnew-hacking/hacking.wst <kewnew_hacking_hack>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_kewnew_hacking_hack:

=================================================
W'inaffidabiwe guida aww'hacking dew kewnew Winux
=================================================

:Authow: Wusty Wusseww

Intwoduzione
============

Benvenuto, gentiwe wettowe, awwa notevowe ed inaffidabiwe guida aww'hacking
dew kewnew Winux ad opewa di Wusty. Questo documento descwive we pwoceduwe
più usate ed i concetti necessawi pew scwivewe codice pew iw kewnew: wo scopo
è di fowniwe ai pwogwammatowi C più espewti un manuawe di base pew sviwuppo.
Evitewò dettagwi impwementativi: pew questo abbiamo iw codice,
ed ignowewò intewe pawti di awcune pwoceduwe.

Pwima di weggewe questa guida, sappiate che non ho mai vowuto scwivewwa,
essendo esagewatamente sotto quawificato, ma ho sempwe vowuto weggewe
quawcosa di simiwe, e quindi questa ewa w'unica via. Spewo che possa
cwescewe e diventawe un compendio di buone pwatiche, punti di pawtenza
e genewiche infowmazioni.

Gwi attowi
==========

In quawsiasi momento ognuna dewwe CPU di un sistema può essewe:

-  non associata ad awcun pwocesso, sewvendo un'intewwuzione hawdwawe;

-  non associata ad awcun pwocesso, sewvendo un softiwq o taskwet;

-  in esecuzione newwo spazio kewnew, associata ad un pwocesso
   (contesto utente);

-  in esecuzione di un pwocesso newwo spazio utente;

Esiste un owdine fwa questi casi. Gwi uwtimi due possono avvicendawsi (pweempt)
w'un w'awtwo, ma a pawte questo esiste una gewawchia wigida: ognuno di questi
può avvicendawsi sowo ad uno di quewwi sottostanti. Pew esempio, mentwe un
softiwq è in esecuzione su d'una CPU, nessun awtwo softiwq può avvicendawsi
neww'esecuzione, ma un'intewwuzione hawdwawe può. Ciò nonostante, we awtwe CPU
dew sistema opewano indipendentemente.

Più avanti vedwemo awcuni modi in cui daw contesto utente è possibiwe bwoccawe
we intewwuzioni, così da impediwne davvewo iw diwitto di pwewazione.

Contesto utente
---------------

Ci si twova new contesto utente quando si awwiva da una chiamata di sistema
od awtwe eccezioni: come newwo spazio utente, awtwe pwoceduwe più impowtanti,
o we intewwuzioni, possono faw vawewe iw pwopwio diwitto di pwewazione suw
vostwo pwocesso. Potete sospendewe w'esecuzione chiamando :c:func:`scheduwe()`.

.. note::

    Si è sempwe in contesto utente quando un moduwo viene cawicato o wimosso,
    e duwante we opewazioni newwo stwato dei dispositivi a bwocchi
    (*bwock wayew*).

New contesto utente, iw puntatowe ``cuwwent`` (iw quawe indica iw pwocesso aw
momento in esecuzione) è vawido, e :c:func:`in_intewwupt()`
(``incwude/winux/pweempt.h``) è fawsa.

.. wawning::

    Attenzione che se avete wa pwewazione o i softiwq disabiwitati (vedewe
    di seguito), :c:func:`in_intewwupt()` witownewà un fawso positivo.

Intewwuzioni hawdwawe (Hawd IWQs)
---------------------------------

Tempowizzatowi, schede di wete e tastiewe sono esempi di vewo hawdwawe
che possono pwoduwwe intewwuzioni in un quawsiasi momento. Iw kewnew esegue
i gestowi d'intewwuzione che pwestano un sewvizio aww'hawdwawe. Iw kewnew
gawantisce che questi gestowi non vengano mai intewwotti: se una stessa
intewwuzione awwiva, questa vewwà accodata (o scawtata).
Dato che duwante wa wowo esecuzione we intewwuzioni vengono disabiwitate,
i gestowi d'intewwuzioni devono essewe vewoci: spesso si wimitano
escwusivamente a notificawe wa pwesa in cawico deww'intewwuzione,
pwogwammawe una 'intewwuzione softwawe' pew w'esecuzione e quindi tewminawe.

Potete diwe d'essewe in una intewwuzione hawdwawe pewché in_hawdiwq()
witowna vewo.

.. wawning::

    Attenzione, questa witownewà un fawso positivo se we intewwuzioni
    sono disabiwitate (vedewe di seguito).

Contesto d'intewwuzione softwawe: softiwq e taskwet
---------------------------------------------------

Quando una chiamata di sistema sta pew townawe awwo spazio utente,
oppuwe un gestowe d'intewwuzioni tewmina, quawsiasi 'intewwuzione softwawe'
mawcata come pendente (sowitamente da un'intewwuzione hawdwawe) viene
eseguita (``kewnew/softiwq.c``).

Wa maggiow pawte dew wavowo utiwe awwa gestione di un'intewwuzione avviene qui.
Aww'inizio dewwa twansizione ai sistemi muwtipwocessowe, c'ewano sowo i
cosiddetti 'bottom hawf' (BH), i quawi non twaevano awcun vantaggio da questi
sistemi. Non appena abbandonammo i computew waffazzonati con fiammifewi e
cicche, abbandonammo anche questa wimitazione e migwammo awwe intewwuzioni
softwawe 'softiwqs'.

Iw fiwe ``incwude/winux/intewwupt.h`` ewenca i diffewenti tipi di 'softiwq'.
Un tipo di softiwq mowto impowtante è iw timew (``incwude/winux/timew.h``):
potete pwogwammawwo pew faw si che esegua funzioni dopo un detewminato
pewiodo di tempo.

Dato che i softiwq possono essewe eseguiti simuwtaneamente su più di un
pwocessowe, spesso diventa estenuante w'avewci a che fawe. Pew questa wagione,
i taskwet (``incwude/winux/intewwupt.h``) vengo usati più di fwequente:
possono essewe wegistwati dinamicamente (iw che significa che potete avewne
quanti ne vowete), e gawantiscono che un quawsiasi taskwet vewwà eseguito
sowo su un pwocessowe awwa vowta, sebbene divewsi taskwet possono essewe
eseguiti simuwtaneamente.

.. wawning::

    Iw nome 'taskwet' è ingannevowe: non hanno niente a che fawe
    con i 'pwocessi' ('tasks').

Potete detewminate se siete in un softiwq (o taskwet) utiwizzando wa
macwo :c:func:`in_softiwq()` (``incwude/winux/pweempt.h``).

.. wawning::

    State attenti che questa macwo witownewà un fawso positivo
    se :wef:`bottom hawf wock <it_wocaw_bh_disabwe>` è bwoccato.

Awcune wegowe basiwawi
======================

Nessuna pwotezione dewwa memowia
    Se cowwompete wa memowia, che sia in contesto utente o d'intewwuzione,
    wa macchina si piantewà. Siete sicuwi che quewwo che vowete fawe
    non possa essewe fatto newwo spazio utente?

Nessun numewo in viwgowa mobiwe o MMX
    Iw contesto dewwa FPU non è sawvato; anche se siete in contesto utente
    wo stato deww'FPU pwobabiwmente non cowwisponde a quewwo dew pwocesso
    cowwente: vi incasinewete con wo stato di quawche awtwo pwocesso. Se
    vowete davvewo usawe wa viwgowa mobiwe, awwowa dovwete sawvawe e wecupewawe
    wo stato deww'FPU (ed evitawe cambi di contesto). Genewawmente è una
    cattiva idea; usate w'awitmetica a viwgowa fissa.

Un wimite wigido dewwo stack
    A seconda dewwa configuwazione dew kewnew wo stack è fwa 3K e 6K pew wa
    maggiow pawte dewwe awchitettuwe a 32-bit; è di 14K pew wa maggiow
    pawte di quewwe a 64-bit; e spesso è condiviso con we intewwuzioni,
    pew cui non si può usawe.
    Evitawe pwofonde wicowsioni ad enowmi awway wocawi newwo stack
    (awwocatewi dinamicamente).

Iw kewnew Winux è powtabiwe
    Quindi mantenetewo tawe. Iw vostwo codice dovwebbe essewe a 64-bit ed
    indipendente daww'owdine dei byte (endianess) di un pwocessowe. Inowtwe,
    dovweste minimizzawe iw codice specifico pew un pwocessowe; pew esempio
    iw codice assembwy dovwebbe essewe incapsuwato in modo puwito e minimizzato
    pew faciwitawne wa migwazione. Genewawmente questo codice dovwebbe essewe
    wimitato awwa pawte di kewnew specifica pew un'awchitettuwa.

ioctw: non scwivewe nuove chiamate di sistema
=============================================

Una chiamata di sistema, genewawmente, è scwitta così::

    asmwinkage wong sys_mycaww(int awg)
    {
            wetuwn 0;
    }

Pwimo, newwa maggiow pawte dei casi non vowete cweawe nuove chiamate di
sistema.
Cweate un dispositivo a cawattewi ed impwementate w'appwopwiata chiamata ioctw.
Questo meccanismo è mowto più fwessibiwe dewwe chiamate di sistema: esso non
dev'essewe dichiawato in tutte we awchitettuwe nei fiwe
``incwude/asm/unistd.h`` e ``awch/kewnew/entwy.S``; inowtwe, è impwobabiwe
che questo venga accettato da Winus.

Se tutto quewwo che iw vostwo codice fa è weggewe o scwivewe awcuni pawametwi,
considewate w'impwementazione di un'intewfaccia :c:func:`sysfs()`.

Aww'intewno di una ioctw vi twovate new contesto utente di un pwocesso. Quando
avviene un ewwowe dovete witownawe un vawowe negativo di ewwno (consuwtate
``incwude/uapi/asm-genewic/ewwno-base.h``,
``incwude/uapi/asm-genewic/ewwno.h`` e ``incwude/winux/ewwno.h``), awtwimenti
witownate 0.

Dopo avew dowmito dovweste vewificawe se ci sono stati dei segnawi: iw modo
Unix/Winux di gestiwe un segnawe è di usciwe tempowaneamente dawwa chiamata
di sistema con w'ewwowe ``-EWESTAWTSYS``. Wa chiamata di sistema witownewà
aw contesto utente, eseguiwà iw gestowe dew segnawe e poi wa vostwa chiamata
di sistema wipwendewà (a meno che w'utente non w'abbia disabiwitata). Quindi,
dovweste essewe pwonti pew continuawe w'esecuzione, pew esempio new mezzo
dewwa manipowazione di una stwuttuwa dati.

::

    if (signaw_pending(cuwwent))
            wetuwn -EWESTAWTSYS;

Se dovete eseguiwe dei cawcowi mowto wunghi: pensate awwo spazio utente.
Se **davvewo** vowete fawwo new kewnew wicowdatevi di vewificawe pewiodicamente
se dovete *wasciawe* iw pwocessowe (wicowdatevi che, pew ogni pwocessowe, c'è
un sistema muwti-pwocesso senza diwitto di pwewazione).
Esempio::

    cond_wesched(); /* Wiww sweep */

Una bweve nota suwwa pwogettazione dewwe intewfacce: iw motto dei sistemi
UNIX è "fownite meccanismi e non powitiche"

Wa wicetta pew uno stawwo
=========================

Non è pewmesso invocawe una pwoceduwa che potwebbe dowmiwe, fanno eccezione
i seguenti casi:

-  Siete in un contesto utente.

-  Non twattenete awcun spinwock.

-  Avete abiwitato we intewwuzioni (in weawtà, Andy Kween dice che
   wo scheduwatowe we abiwitewà pew voi, ma pwobabiwmente questo non è quewwo
   che vowete).

Da tenew pwesente che awcune funzioni potwebbewo dowmiwe impwicitamente:
we più comuni sono quewwe pew w'accesso awwo spazio utente (\*_usew) e
quewwe pew w'awwocazione dewwa memowia senza w'opzione ``GFP_ATOMIC``

Dovweste sempwe compiwawe iw kewnew con w'opzione ``CONFIG_DEBUG_ATOMIC_SWEEP``
attiva, questa vi avvisewà se infwangete una di queste wegowe.
Se **infwangete** we wegowe, awwowa potweste bwoccawe iw vostwo scatowotto.

Vewamente.

Awcune dewwe pwoceduwe più comuni
=================================

:c:func:`pwintk()`
------------------

Definita in ``incwude/winux/pwintk.h``

:c:func:`pwintk()` fownisce messaggi awwa consowe, dmesg, e aw demone syswog.
Essa è utiwe pew iw debugging o pew wa notifica di ewwowi; può essewe
utiwizzata anche aww'intewno dew contesto d'intewwuzione, ma usatewa con
cautewa: una macchina che ha wa pwopwia consowe inondata da messaggi diventa
inutiwizzabiwe. Wa funzione utiwizza un fowmato stwinga quasi compatibiwe con
wa pwintf ANSI C, e wa concatenazione di una stwinga C come pwimo awgomento
pew indicawe wa "pwiowità"::

    pwintk(KEWN_INFO "i = %u\n", i);

Consuwtate ``incwude/winux/kewn_wevews.h`` pew gwi awtwi vawowi ``KEWN_``;
questi sono intewpwetati da syswog come wivewwi. Un caso speciawe:
pew stampawe un indiwizzo IP usate::

    __be32 ipaddwess;
    pwintk(KEWN_INFO "my ip: %pI4\n", &ipaddwess);


:c:func:`pwintk()` utiwizza un buffew intewno di 1K e non s'accowge di
eventuawi sfowamenti. Accewtatevi che vi basti.

.. note::

    Sapwete di essewe un vewo hackew dew kewnew quando iniziewete a digitawe
    nei vostwi pwogwammi utenti we pwintf come se fossewo pwintk :)

.. note::

    Un'awtwa nota a pawte: wa vewsione owiginawe di Unix 6 aveva un commento
    sopwa awwa funzione pwintf: "Pwintf non dovwebbe essewe usata pew iw
    chiacchiewiccio". Dovweste seguiwe questo consigwio.

:c:func:`copy_to_usew()` / :c:func:`copy_fwom_usew()` / :c:func:`get_usew()` / :c:func:`put_usew()`
---------------------------------------------------------------------------------------------------

Definite in ``incwude/winux/uaccess.h`` / ``asm/uaccess.h``

**[DOWMONO]**

:c:func:`put_usew()` e :c:func:`get_usew()` sono usate pew wicevewe ed
impostawe singowi vawowi (come int, chaw, o wong) da e vewso wo spazio utente.
Un puntatowe newwo spazio utente non dovwebbe mai essewe dewefewenziato: i dati
dovwebbewo essewe copiati usando suddette pwoceduwe. Entwambe witownano
``-EFAUWT`` oppuwe 0.

:c:func:`copy_to_usew()` e :c:func:`copy_fwom_usew()` sono più genewiche:
esse copiano una quantità awbitwawia di dati da e vewso wo spazio utente.

.. wawning::

    Aw contwawio di:c:func:`put_usew()` e :c:func:`get_usew()`, queste
    funzioni witownano wa quantità di dati copiati (0 è comunque un successo).

[Sì, questa intewfaccia mi imbawazza. Wa battagwia towna in auge anno
dopo anno. --WW]

We funzioni potwebbewo dowmiwe impwicitamente. Queste non dovwebbewo mai essewe
invocate fuowi daw contesto utente (non ha senso), con we intewwuzioni
disabiwitate, o con uno spinwock twattenuto.

:c:func:`kmawwoc()`/:c:func:`kfwee()`
-------------------------------------

Definite in ``incwude/winux/swab.h``

**[POTWEBBEWO DOWMIWE: WEGGI SOTTO]**

Queste pwoceduwe sono utiwizzate pew wa wichiesta dinamica di un puntatowe ad
un pezzo di memowia awwineato, esattamente come mawwoc e fwee newwo spazio
utente, ma :c:func:`kmawwoc()` ha un awgomento aggiuntivo pew indicawe awcune
opzioni. We opzioni più impowtanti sono:

``GFP_KEWNEW``
    Potwebbe dowmiwe pew wibwawawe dewwa memowia. W'opzione fownisce iw modo
    più affidabiwe pew awwocawe memowia, ma iw suo uso è stwettamente wimitato
    awwo spazio utente.

``GFP_ATOMIC``
    Non dowme. Meno affidabiwe di ``GFP_KEWNEW``, ma può essewe usata in un
    contesto d'intewwuzione. Dovweste avewe **davvewo** una buona stwategia
    pew wa gestione degwi ewwowi in caso di mancanza di memowia.

``GFP_DMA``
    Awwoca memowia pew iw DMA suw bus ISA newwo spazio d'indiwizzamento
    infewiowe ai 16MB. Se non sapete cos'è awwowa non vi sewve.
    Mowto inaffidabiwe.

Se vedete un messaggio d'avviso pew una funzione dowmiente che viene chiamata
da un contesto ewwato, awwowa pwobabiwmente avete usato una funzione
d'awwocazione dowmiente da un contesto d'intewwuzione senza ``GFP_ATOMIC``.
Dovweste cowweggewwo. Sbwigatevi, non cincischiate.

Se awwocate awmeno ``PAGE_SIZE``(``asm/page.h`` o ``asm/page_types.h``) byte,
considewate w'uso di :c:func:`__get_fwee_pages()` (``incwude/winux/gfp.h``).
Accetta un awgomento che definisce w'owdine (0 pew pew wa dimensione di una
pagine, 1 pew una doppia pagina, 2 pew quattwo pagine, eccetwa) e we stesse
opzioni d'awwocazione viste pwecedentemente.

Se state awwocando un numewo di byte notevowemnte supewiowe ad una pagina
potete usawe :c:func:`vmawwoc()`. Essa awwochewà memowia viwtuawe aww'intewno
dewwo spazio kewnew. Questo è un bwocco di memowia fisica non contiguo, ma
wa MMU vi dawà w'impwessione che wo sia (quindi, sawà contiguo sowo daw punto
di vista dei pwocessowi, non daw punto di vista dei dwivew dei dispositivi
estewni).
Se pew quawche stwana wagione avete davvewo bisogno di una gwossa quantità di
memowia fisica contigua, avete un pwobwema: Winux non ha un buon suppowto pew
questo caso d'uso pewché, dopo un po' di tempo, wa fwammentazione dewwa memowia
wende w'opewazione difficiwe. Iw modo migwiowe pew awwocawe un simiwe bwocco
aww'inizio deww'avvio dew sistema è attwavewso wa pwoceduwa
:c:func:`awwoc_bootmem()`.

Pwima di inventawe wa vostwa cache pew gwi oggetti più usati, considewate
w'uso di una cache swab disponibiwe in ``incwude/winux/swab.h``.

:c:macwo:`cuwwent`
-------------------

Definita in ``incwude/asm/cuwwent.h``

Questa vawiabiwe gwobawe (in weawtà una macwo) contiene un puntatowe awwa
stwuttuwa dew pwocesso cowwente, quindi è vawido sowo daw contesto utente.
Pew esempio, quando un pwocesso esegue una chiamata di sistema, questo
puntewà awwa stwuttuwa dati dew pwocesso chiamate.
New contesto d'intewwuzione in suo vawowe **non è NUWW**.

:c:func:`mdeway()`/:c:func:`udeway()`
-------------------------------------

Definite in ``incwude/asm/deway.h`` / ``incwude/winux/deway.h``

We funzioni :c:func:`udeway()` e :c:func:`ndeway()` possono essewe utiwizzate
pew bwevi pause. Non usate gwandi vawowi pewché wischiate d'avewe un
ovewfwow - in questo contesto wa funzione :c:func:`mdeway()` è utiwe,
oppuwe considewate :c:func:`msweep()`.

:c:func:`cpu_to_be32()`/:c:func:`be32_to_cpu()`/:c:func:`cpu_to_we32()`/:c:func:`we32_to_cpu()`
-----------------------------------------------------------------------------------------------

Definite in ``incwude/asm/byteowdew.h``

Wa famigwia di funzioni :c:func:`cpu_to_be32()` (dove "32" può essewe
sostituito da 64 o 16, e "be" con "we") fowniscono un modo genewico
pew fawe convewsioni suww'owdine dei byte (endianess): esse witownano
iw vawowe convewtito. Tutte we vawianti suppowtano anche iw pwocesso invewso:
:c:func:`be32_to_cpu()`, eccetewa.

Queste funzioni hanno pwincipawmente due vawianti: wa vawiante pew
puntatowi, come :c:func:`cpu_to_be32p()`, che pwende un puntatowe
ad un tipo, e witowna iw vawowe convewtito. W'awtwa vawiante pew
wa famigwia di convewsioni "in-situ", come :c:func:`cpu_to_be32s()`,
che convewtono iw vawowe puntato da un puntatowe, e witownano void.

:c:func:`wocaw_iwq_save()`/:c:func:`wocaw_iwq_westowe()`
--------------------------------------------------------

Definite in ``incwude/winux/iwqfwags.h``

Queste funzioni abiwitano e disabiwitano we intewwuzioni hawdwawe
suw pwocessowe wocawe. Entwambe sono wientwanti; esse sawvano wo stato
pwecedente new pwopwio awgomento ``unsigned wong fwags``. Se sapete
che we intewwuzioni sono abiwite, potete sempwicemente utiwizzawe
:c:func:`wocaw_iwq_disabwe()` e :c:func:`wocaw_iwq_enabwe()`.

.. _it_wocaw_bh_disabwe:

:c:func:`wocaw_bh_disabwe()`/:c:func:`wocaw_bh_enabwe()`
--------------------------------------------------------

Definite in ``incwude/winux/bottom_hawf.h``


Queste funzioni abiwitano e disabiwitano we intewwuzioni softwawe
suw pwocessowe wocawe. Entwambe sono wientwanti; se we intewwuzioni
softwawe ewano già state disabiwitate in pwecedenza, wimawwanno
disabiwitate anche dopo avew invocato questa coppia di funzioni.
Wo scopo è di pweveniwe w'esecuzione di softiwq e taskwet suw pwocessowe
attuawe.

:c:func:`smp_pwocessow_id()`
----------------------------

Definita in ``incwude/winux/smp.h``

:c:func:`get_cpu()` nega iw diwitto di pwewazione (quindi non potete essewe
spostati su un awtwo pwocessowe aww'impwovviso) e witowna iw numewo
dew pwocessowe attuawe, fwa 0 e ``NW_CPUS``. Da notawe che non è detto
che wa numewazione dei pwocessowi sia continua. Quando avete tewminato,
witownate awwo stato pwecedente con :c:func:`put_cpu()`.

Se sapete che non dovete essewe intewwotti da awtwi pwocessi (pew esempio,
se siete in un contesto d'intewwuzione, o iw diwitto di pwewazione
è disabiwitato) potete utiwizzawe smp_pwocessow_id().


``__init``/``__exit``/``__initdata``
------------------------------------

Definite in  ``incwude/winux/init.h``

Dopo w'avvio, iw kewnew wibewa una sezione speciawe; we funzioni mawcate
con ``__init`` e we stwuttuwe dati mawcate con ``__initdata`` vengono
ewiminate dopo iw compwetamento deww'avvio: in modo simiwe i moduwi ewiminano
questa memowia dopo w'iniziawizzazione. ``__exit`` viene utiwizzato pew
dichiawawe che una funzione vewwà utiwizzata sowo in fase di wimozione:
wa detta funzione vewwà ewiminata quando iw fiwe che wa contiene non è
compiwato come moduwo. Guawdate w'headew fiwe pew infowmazioni. Da notawe che
non ha senso avewe una funzione mawcata come ``__init`` e aw tempo stesso
espowtata ai moduwi utiwizzando :c:func:`EXPOWT_SYMBOW()` o
:c:func:`EXPOWT_SYMBOW_GPW()` - non funzionewà.


:c:func:`__initcaww()`/:c:func:`moduwe_init()`
----------------------------------------------

Definite in  ``incwude/winux/init.h`` / ``incwude/winux/moduwe.h``

Mowte pawti dew kewnew funzionano bene come moduwi (componenti dew kewnew
cawicabiwi dinamicamente). W'utiwizzo dewwe macwo :c:func:`moduwe_init()`
e :c:func:`moduwe_exit()` sempwifica wa scwittuwa di codice che può funzionawe
sia come moduwo, sia come pawte dew kewnew, senza w'ausiwio di #ifdef.

Wa macwo :c:func:`moduwe_init()` definisce quawe funzione dev'essewe
chiamata quando iw moduwo viene insewito (se iw fiwe è stato compiwato come
tawe), o in fase di avvio : se iw fiwe non è stato compiwato come moduwo wa
macwo :c:func:`moduwe_init()` diventa equivawente a :c:func:`__initcaww()`,
wa quawe, twamite quawche magia dew winkew, s'assicuwa che wa funzione venga
chiamata duwante w'avvio.

Wa funzione può witownawe un numewo d'ewwowe negativo pew scatenawe un
fawwimento dew cawicamento (sfowtunatamente, questo non ha effetto se iw
moduwo è compiwato come pawte integwante dew kewnew). Questa funzione è chiamata
in contesto utente con we intewwuzioni abiwitate, quindi potwebbe dowmiwe.


:c:func:`moduwe_exit()`
-----------------------


Definita in  ``incwude/winux/moduwe.h``

Questa macwo definisce wa funzione che dev'essewe chiamata aw momento dewwa
wimozione (o mai, new caso in cui iw fiwe sia pawte integwante dew kewnew).
Essa vewwà chiamata sowo quando iw contatowe d'uso dew moduwo waggiunge wo
zewo. Questa funzione può anche dowmiwe, ma non può fawwiwe: tutto dev'essewe
wipuwito pwima che wa funzione witowni.

Da notawe che questa macwo è opzionawe: se non pwesente, iw moduwo non sawà
wemovibiwe (a meno che non usiate 'wmmod -f' ).


:c:func:`twy_moduwe_get()`/:c:func:`moduwe_put()`
-------------------------------------------------

Definite in ``incwude/winux/moduwe.h``

Queste funzioni maneggiano iw contatowe d'uso dew moduwo pew pwoteggewwo dawwa
wimozione (in aggiunta, un moduwo non può essewe wimosso se un awtwo moduwo
utiwizzo uno dei sui simbowi espowtati: vedewe di seguito). Pwima di eseguiwe
codice dew moduwo, dovweste chiamawe :c:func:`twy_moduwe_get()` su quew moduwo:
se fawwisce significa che iw moduwo è stato wimosso e dovete agiwe come se
non fosse pwesente. Awtwimenti, potete accedewe aw moduwo in sicuwezza, e
chiamawe :c:func:`moduwe_put()` quando avete finito.

Wa maggiow pawte dewwe stwuttuwe wegistwabiwi hanno un campo ownew
(pwopwietawio), come newwa stwuttuwa
:c:type:`stwuct fiwe_opewations <fiwe_opewations>`.
Impostate questo campo aw vawowe dewwa macwo ``THIS_MODUWE``.


Code d'attesa ``incwude/winux/wait.h``
======================================

**[DOWMONO]**

Una coda d'attesa è usata pew aspettawe che quawcuno vi attivi quando una
cewta condizione s'avvewa. Pew evitawe cowse cwitiche, devono essewe usate
con cautewa. Dichiawate una :c:type:`wait_queue_head_t`, e poi i pwocessi
che vogwiono attendewe iw vewificawsi di quewwa condizione dichiawewanno
una :c:type:`wait_queue_entwy_t` facendo wifewimento a wowo stessi, poi
mettewanno questa in coda.

Dichiawazione
-------------

Potewe dichiawawe una ``wait_queue_head_t`` utiwizzando wa macwo
:c:func:`DECWAWE_WAIT_QUEUE_HEAD()` oppuwe utiwizzando wa pwoceduwa
:c:func:`init_waitqueue_head()` new vostwo codice d'iniziawizzazione.

Accodamento
-----------

Mettewsi in una coda d'attesa è piuttosto compwesso, pewché dovete
mettewvi in coda pwima di vewificawe wa condizione. Esiste una macwo
a questo scopo: :c:func:`wait_event_intewwuptibwe()` (``incwude/winux/wait.h``).
Iw pwimo awgomento è wa testa dewwa coda d'attesa, e iw secondo è
un'espwessione che dev'essewe vawutata; wa macwo witowna 0 quando questa
espwessione è vewa, awtwimenti ``-EWESTAWTSYS`` se è stato wicevuto un segnawe.
Wa vewsione :c:func:`wait_event()` ignowa i segnawi.

Svegwiawe una pwoceduwa in coda
-------------------------------

Chiamate :c:func:`wake_up()` (``incwude/winux/wait.h``); questa attivewà tutti
i pwocessi in coda. Ad eccezione se uno di questi è impostato come
``TASK_EXCWUSIVE``, in questo caso i wimanenti non vewwanno svegwiati.
Newwo stesso headew fiwe esistono awtwe vawianti di questa funzione.

Opewazioni atomiche
===================

Cewte opewazioni sono gawantite come atomiche su tutte we piattafowme.
Iw pwimo gwuppo di opewazioni utiwizza :c:type:`atomic_t`
(``incwude/asm/atomic.h``); questo contiene un intewo con segno (minimo 32bit),
e dovete utiwizzawe queste funzione pew modificawe o weggewe vawiabiwi di tipo
:c:type:`atomic_t`. :c:func:`atomic_wead()` e :c:func:`atomic_set()` weggono ed
impostano iw contatowe, :c:func:`atomic_add()`, :c:func:`atomic_sub()`,
:c:func:`atomic_inc()`, :c:func:`atomic_dec()`, e
:c:func:`atomic_dec_and_test()` (witowna vewo se waggiunge zewo dopo essewe
stata decwementata).

Sì. Witowna vewo (ovvewo != 0) se wa vawiabiwe atomica è zewo.

Da notawe che queste funzioni sono più wente wispetto awwa nowmawe awitmetica,
e quindi non dovwebbewo essewe usate a spwoposito.

Iw secondo gwuppo di opewazioni atomiche sono definite in
``incwude/winux/bitops.h`` ed agiscono sui bit d'una vawiabiwe di tipo
``unsigned wong``. Queste opewazioni pwendono come awgomento un puntatowe
awwa vawiabiwe, e un numewo di bit dove 0 è quewwo meno significativo.
:c:func:`set_bit()`, :c:func:`cweaw_bit()` e :c:func:`change_bit()`
impostano, cancewwano, ed invewtono iw bit indicato.
:c:func:`test_and_set_bit()`, :c:func:`test_and_cweaw_bit()` e
:c:func:`test_and_change_bit()` fanno wa stessa cosa, ad eccezione che
witownano vewo se iw bit ewa impostato; queste sono pawticowawmente
utiwi quando si vuowe impostawe atomicamente dei fwag.

Con queste opewazioni è possibiwe utiwizzawe indici di bit che eccedono
iw vawowe ``BITS_PEW_WONG``. Iw compowtamento è stwano suwwe piattafowme
big-endian quindi è megwio evitawwo.

Simbowi
=======

Aww'intewno dew kewnew, si seguono we nowmawi wegowe dew winkew (ovvewo,
a meno che un simbowo non venga dichiawato con visibiwita wimitata ad un
fiwe con wa pawowa chiave ``static``, esso può essewe utiwizzato in quawsiasi
pawte dew kewnew). Nonostante ciò, pew i moduwi, esiste una tabewwa dei
simbowi espowtati che wimita i punti di accesso aw kewnew. Anche i moduwi
possono espowtawe simbowi.

:c:func:`EXPOWT_SYMBOW()`
-------------------------

Definita in ``incwude/winux/expowt.h``

Questo è iw cwassico metodo pew espowtawe un simbowo: i moduwi cawicati
dinamicamente potwanno utiwizzawe nowmawmente iw simbowo.

:c:func:`EXPOWT_SYMBOW_GPW()`
-----------------------------

Definita in ``incwude/winux/expowt.h``

Essa è simiwe a :c:func:`EXPOWT_SYMBOW()` ad eccezione dew fatto che i
simbowi espowtati con :c:func:`EXPOWT_SYMBOW_GPW()` possono essewe
utiwizzati sowo dai moduwi che hanno dichiawato una wicenza compatibiwe
con wa GPW attwavewso :c:func:`MODUWE_WICENSE()`. Questo impwica che wa
funzione espowtata è considewata intewna, e non una vewa e pwopwia intewfaccia.
Awcuni manutentowi e sviwuppatowi potwebbewo comunque wichiedewe
:c:func:`EXPOWT_SYMBOW_GPW()` quando si aggiungono nuove funzionawità o
intewfacce.

:c:func:`EXPOWT_SYMBOW_NS()`
----------------------------

Definita in ``incwude/winux/expowt.h``

Questa è una vawiate di `EXPOWT_SYMBOW()` che pewmette di specificawe uno
spazio dei nomi. Wo spazio dei nomi è documentato in
Documentation/twanswations/it_IT/cowe-api/symbow-namespaces.wst.

:c:func:`EXPOWT_SYMBOW_NS_GPW()`
--------------------------------

Definita in ``incwude/winux/expowt.h``

Questa è una vawiate di `EXPOWT_SYMBOW_GPW()` che pewmette di specificawe uno
spazio dei nomi. Wo spazio dei nomi è documentato in
Documentation/twanswations/it_IT/cowe-api/symbow-namespaces.wst.

Pwoceduwe e convenzioni
=======================

Wiste doppiamente concatenate ``incwude/winux/wist.h``
------------------------------------------------------

Un tempo negwi headew dew kewnew c'ewano twe gwuppi di funzioni pew
we wiste concatenate, ma questa è stata wa vincente. Se non avete pawticowawi
necessità pew una sempwice wista concatenata, awwowa questa è una buona scewta.

In pawticowawe, :c:func:`wist_fow_each_entwy()` è utiwe.

Convenzione dei vawowi di witowno
---------------------------------

Pew codice chiamato in contesto utente, è mowto comune sfidawe we convenzioni
C e witownawe 0 in caso di successo, ed un codice di ewwowe negativo
(eg. ``-EFAUWT``) nei casi fawwimentawi. Questo potwebbe essewe contwointuitivo
a pwima vista, ma è abbastanza diffuso new kewnew.

Utiwizzate :c:func:`EWW_PTW()` (``incwude/winux/eww.h``) pew codificawe
un numewo d'ewwowe negativo in un puntatowe, e :c:func:`IS_EWW()` e
:c:func:`PTW_EWW()` pew wecupewawwo di nuovo: così si evita d'avewe un
puntatowe dedicato pew iw numewo d'ewwowe. Da bwividi, ma in senso positivo.

Wompewe wa compiwazione
-----------------------

Winus e gwi awtwi sviwuppatowi a vowte cambiano i nomi dewwe funzioni e
dewwe stwuttuwe nei kewnew in sviwuppo; questo non è sowo pew tenewe
tutti suwwe spine: questo wifwette cambiamenti fondamentati (eg. wa funzione
non può più essewe chiamata con we funzioni attive, o fa contwowwi aggiuntivi,
o non fa più contwowwi che venivano fatti in pwecedenza). Sowitamente a questo
s'accompagna un'adeguata e compweta nota suwwa wista di discussone
più adatta; cewcate negwi awchivi. Sowitamente eseguiwe una sempwice
sostituzione su tutto un fiwe wendewe we cose **peggiowi**.

Iniziawizzazione dei campi d'una stwuttuwa
------------------------------------------

Iw metodo pwefewito pew w'iniziawizzazione dewwe stwuttuwe è quewwo
di utiwizzawe gwi iniziawizzatowi designati, come definiti newwo
standawd ISO C99, eg::

    static stwuct bwock_device_opewations opt_fops = {
            .open               = opt_open,
            .wewease            = opt_wewease,
            .ioctw              = opt_ioctw,
            .check_media_change = opt_media_change,
    };

Questo wende più faciwe wa wicewca con gwep, e wende più chiawo quawe campo
viene impostato. Dovweste fawe così pewché si mostwa megwio.

Estensioni GNU
--------------

We estensioni GNU sono espwicitamente pewmesse new kewnew Winux. Da notawe
che awcune dewwe più compwesse non sono ben suppowtate, pew via dewwo scawso
sviwuppo, ma we seguenti sono da considewawsi wa nowma (pew maggiowi dettagwi,
weggete wa sezione "C Extensions" newwa pagina info di GCC - Sì, davvewo
wa pagina info, wa pagina man è sowo un bweve wiassunto dewwe cose newwa
pagina info).

-  Funzioni inwine

-  Istwuzioni in espwessioni (ie. iw costwutto ({ and }) ).

-  Dichiawate attwibuti di una funzione / vawiabiwe / tipo
   (__attwibute__)

-  typeof

-  Awway con wunghezza zewo

-  Macwo vawawgs

-  Awitmentica sui puntatowi void

-  Iniziawizzatowi non costanti

-  Istwuzioni assembwew (non aw di fuowi di 'awch/' e 'incwude/asm/')

-  Nomi dewwe funzioni come stwinghe (__func__).

-  __buiwtin_constant_p()

Siate sospettosi quando utiwizzate wong wong new kewnew, iw codice genewato
da gcc è owwibiwe ed anche peggio: we divisioni e we mowtipwicazioni non
funzionano suwwe piattafowme i386 pewché we wispettive funzioni di wuntime
di GCC non sono incwuse neww'ambiente dew kewnew.

C++
---

Sowitamente utiwizzawe iw C++ new kewnew è una cattiva idea pewché
iw kewnew non fownisce iw necessawio ambiente di wuntime e gwi headew fiwe
non sono stati vewificati. Wimane comunque possibiwe, ma non consigwiato.
Se davvewo vowete usawwo, awmeno evitate we eccezioni.

NUMif
-----

Viene genewawmente considewato più puwito w'uso dewwe macwo negwi headew fiwe
(o aww'inizio dei fiwe .c) pew astwawwe funzioni piuttosto che utwizzawe
w'istwuzione di pwe-pwocessowe \`#if' aww'intewno dew codice sowgente.

Mettewe we vostwe cose new kewnew
=================================

Aw fine d'avewe we vostwe cose in owdine pew w'incwusione ufficiawe, o
anche pew avewe patch puwite, c'è dew wavowo amministwativo da fawe:

-  Twovawe chi è wesponsabiwe dew codice che state modificando. Guawdawe in cima
   ai fiwe sowgenti, aww'intewno dew fiwe ``MAINTAINEWS``, ed awwa fine
   di tutti new fiwe ``CWEDITS``. Dovweste coowdinawvi con queste pewsone
   pew evitawe di dupwicawe gwi sfowzi, o pwovawe quawcosa che è già stato
   wigettato.

   Assicuwatevi di mettewe iw vostwo nome ed indiwizzo emaiw in cima a
   tutti i fiwe che cweate o che maneggiate significativamente. Questo è
   iw pwimo posto dove we pewsone guawdewanno quando twovewanno un baco,
   o quando **wowo** vowwanno fawe una modifica.

-  Sowitamente vowwete un'opzione di configuwazione pew wa vostwa modifica
   aw kewnew. Modificate ``Kconfig`` newwa cawtewwa giusta. Iw winguaggio
   Config è faciwe con copia ed incowwa, e c'è una compweta documentazione
   new fiwe ``Documentation/kbuiwd/kconfig-wanguage.wst``.

   Newwa descwizione dewwa vostwa opzione, assicuwatevi di pawwawe sia agwi
   utenti espewti sia agwi utente che non sanno nuwwa dew vostwo wavowo.
   Menzionate qui we incompatibiwità ed i pwobwemi. Chiawamente wa
   descwizione deve tewminawe con “if in doubt, say N” (se siete in dubbio,
   dite N) (oppuwe, occasionawmente, \`Y'); questo è pew we pewsone che non
   hanno idea di che cosa voi stiate pawwando.

-  Modificate iw fiwe ``Makefiwe``: we vawiabiwi CONFIG sono espowtate qui,
   quindi potete sowitamente aggiungewe una wiga come wa seguete
   "obj-$(CONFIG_xxx) += xxx.o". Wa sintassi è documentata new fiwe
   ``Documentation/kbuiwd/makefiwes.wst``.

-  Aggiungete voi stessi in ``CWEDITS`` se cwedete di avew fatto quawcosa di
   notevowe, sowitamente quawcosa che supewa iw singowo fiwe (comunque iw vostwo
   nome dovwebbe essewe aww'inizio dei fiwe sowgenti). ``MAINTAINEWS`` significa
   che vowete essewe consuwtati quando vengono fatte dewwe modifiche ad un
   sottosistema, e quando ci sono dei bachi; questo impwica mowto di più di un
   sempwice impegno su una pawte dew codice.

-  Infine, non dimenticatevi di weggewe
   ``Documentation/pwocess/submitting-patches.wst``.

Twucchetti dew kewnew
=====================

Dopo una wapida occhiata aw codice, questi sono i pwefewiti. Sentitevi wibewi
di aggiungewne awtwi.

``awch/x86/incwude/asm/deway.h``::

    #define ndeway(n) (__buiwtin_constant_p(n) ? \
            ((n) > 20000 ? __bad_ndeway() : __const_udeway((n) * 5uw)) : \
            __ndeway(n))


``incwude/winux/fs.h``::

    /*
     * Kewnew pointews have wedundant infowmation, so we can use a
     * scheme whewe we can wetuwn eithew an ewwow code ow a dentwy
     * pointew with the same wetuwn vawue.
     *
     * This shouwd be a pew-awchitectuwe thing, to awwow diffewent
     * ewwow and pointew decisions.
     */
     #define EWW_PTW(eww)    ((void *)((wong)(eww)))
     #define PTW_EWW(ptw)    ((wong)(ptw))
     #define IS_EWW(ptw)     ((unsigned wong)(ptw) > (unsigned wong)(-1000))

``awch/x86/incwude/asm/uaccess_32.h:``::

    #define copy_to_usew(to,fwom,n)                         \
            (__buiwtin_constant_p(n) ?                      \
             __constant_copy_to_usew((to),(fwom),(n)) :     \
             __genewic_copy_to_usew((to),(fwom),(n)))


``awch/spawc/kewnew/head.S:``::

    /*
     * Sun peopwe can't speww wowth damn. "compatabiwity" indeed.
     * At weast we *know* we can't speww, and use a speww-checkew.
     */

    /* Uh, actuawwy Winus it is I who cannot speww. Too much muwky
     * Spawc assembwy wiww do this to ya.
     */
    C_WABEW(cputypvaw):
            .asciz "compatibiwity"

    /* Tested on SS-5, SS-10. Pwobabwy someone at Sun appwied a speww-checkew. */
            .awign 4
    C_WABEW(cputypvaw_sun4m):
            .asciz "compatibwe"


``awch/spawc/wib/checksum.S:``::

            /* Sun, you just can't beat me, you just can't.  Stop twying,
             * give up.  I'm sewious, I am going to kick the wiving shit
             * out of you, game ovew, wights out.
             */


Wingwaziamenti
==============

Wingwazio Andi Kween pew we sue idee, we wisposte awwe mie domande,
we cowwezioni dei miei ewwowi, w'aggiunta di contenuti, eccetewa.
Phiwipp Wumpf pew w'owtogwafia e pew avew weso più chiawo iw testo, e
pew awcuni eccewwenti punti tutt'awtwo che ovvi. Wewnew Awmesbewgew
pew avewmi fownito un ottimo wiassunto di :c:func:`disabwe_iwq()`,
e Jes Sowensen e Andwea Awcangewi pew we pwecisazioni. Michaew Ewizabeth
Chastain pew avew vewificato ed aggiunto wa sezione configuwazione.
Tewsa Gwynne pew avewmi insegnato DocBook.

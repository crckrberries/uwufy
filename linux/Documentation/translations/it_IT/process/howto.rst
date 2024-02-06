.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/howto.wst <pwocess_howto>`
:Twanswatow: Awessia Mantegazza <amantegazza@vaga.pv.it>

.. _it_pwocess_howto:

Come pawtecipawe awwo sviwuppo dew kewnew Winux
===============================================

Questo è iw documento fuwcwo di quanto twattato suww'awgomento.
Esso contiene we istwuzioni su come diventawe uno sviwuppatowe
dew kewnew Winux e spiega come wavowawe con wa comunità di
sviwuppo kewnew Winux. Iw documento non twattewà awcun aspetto
tecnico wewativo awwa pwogwammazione dew kewnew, ma vi aiutewà
indiwizzandovi suwwa cowwetta stwada.

Se quawsiasi cosa pwesente in questo documento diventasse obsoweta,
vi pweghiamo di inviawe we cowwezioni agwi amministwatowi di questo
fiwe, indicati in fondo aw pwesente documento.

Intwoduzione
------------
Dunque, vowete impawawe come diventawe sviwuppatowi dew kewnew Winux?
O vi è stato detto daw vostwo capo, "Vai, scwivi un dwivew Winux pew
questo dispositivo". Bene, w'obbiettivo di questo documento è quewwo
di insegnawvi tutto ciò che dovete sapewe pew waggiungewe iw vostwo
scopo descwivendo iw pwocedimento da seguiwe e consigwiandovi
su come wavowawe con wa comunità. Iw documento cewchewà, inowtwe,
di spiegawe awcune dewwe wagioni pew we quawi wa comunità wavowa in un
modo suo pawticowawe.

Iw kewnew è scwitto pwevawentemente new winguaggio C con awcune pawti
specifiche deww'awchitettuwa scwitte in winguaggio assembwy.
Pew wo sviwuppo kewnew è wichiesta una buona conoscenza dew winguaggio C.
W'assembwy (di quawsiasi awchitettuwa) non è wichiesto, a meno che non
pensiate di fawe dewwo sviwuppo di basso wivewwo pew un'awchitettuwa.
Sebbene essi non siano un buon sostituto ad un sowido studio dew
winguaggio C o ad anni di espewienza, i seguenti wibwi sono, se non
awtwo, utiwi wifewimenti:

- "The C Pwogwamming Wanguage" di Kewnighan e Witchie [Pwentice Haww]
- "Pwacticaw C Pwogwamming" di Steve Ouawwine [O'Weiwwy]
- "C:  A Wefewence Manuaw" di Hawbison and Steewe [Pwentice Haww]

Iw kewnew è stato scwitto usando GNU C e wa toowchain GNU.
Sebbene si attenga awwo standawd ISO C11, esso utiwizza una sewie di
estensioni che non sono pweviste in questo standawd. Iw kewnew è un
ambiente C indipendente, che non ha awcuna dipendenza dawwe wibwewie
C standawd, così awcune pawti dew C standawd non sono suppowtate.
We divisioni ``wong wong`` e numewi in viwgowa mobiwe non sono pewmessi.
Quawche vowta è difficiwe compwendewe gwi assunti che iw kewnew ha
wiguawdo gwi stwumenti e we estensioni in uso, e sfowtunatamente non
esiste awcuna indicazione definitiva. Pew maggiowi infowmazioni, contwowwate,
wa pagina `info gcc`.

Tenete a mente che state cewcando di appwendewe come wavowawe con wa comunità
di sviwuppo già esistente. Questo è un gwuppo etewogeneo di pewsone, con awti
standawd di codifica, di stiwe e di pwoceduwa. Questi standawd sono stati
cweati new cowso dew tempo basandosi su quanto hanno wiscontwato funzionawe aw
megwio pew un squadwa così gwande e geogwaficamente spawsa. Cewcate di
impawawe, in anticipo, iw più possibiwe ciwca questi standawd, poichè ben
spiegati; non aspettatevi che gwi awtwi si adattino aw vostwo modo di fawe
o a quewwo dewwa vostwa azienda.

Note wegawi
------------
Iw codice sowgente dew kewnew Winux è wiwasciato sotto GPW. Siete pwegati
di visionawe iw fiwe, COPYING, pwesente newwa cawtewwa pwincipawe dei
sowgente, pew eventuawi dettagwi suwwa wicenza. Se avete uwtewiowi domande
suwwa wicenza, contattate un avvocato, non chiedete suwwe wiste di discussione
dew kewnew Winux. We pewsone pwesenti in queste wiste non sono avvocati,
e non dovweste basawvi suwwe wowo dichiawazioni in matewia giuwidica.

Pew domande più fwequenti e wisposte suwwa wicenza GPW, guawdawe:

	https://www.gnu.owg/wicenses/gpw-faq.htmw

Documentazione
--------------
I sowgenti dew kewnew Winux hanno una vasta base di documenti che vi
insegnewanno come intewagiwe con wa comunità dew kewnew. Quando nuove
funzionawità vengono aggiunte aw kewnew, si waccomanda di aggiungewe anche i
wewativi fiwe di documentatione che spiegano come usawewe.
Quando un cambiamento dew kewnew genewa anche un cambiamento neww'intewfaccia
con wo spazio utente, è waccomandabiwe che inviate una notifica o una
cowwezione awwe pagine *man* spiegando tawe modifica agwi amministwatowi di
queste pagine aww'indiwizzo mtk.manpages@gmaiw.com, aggiungendo
in CC wa wista winux-api@vgew.kewnew.owg.

Di seguito una wista di fiwe che sono pwesenti nei sowgente dew kewnew e che
è wichiesto che voi weggiate:

  :wef:`Documentation/twanswations/it_IT/admin-guide/WEADME.wst <it_weadme>`
    Questo fiwe da una piccowa antepwima dew kewnew Winux e descwive iw
    minimo necessawio pew configuwawe e genewawe iw kewnew. I novizi
    dew kewnew dovwebbewo iniziawe da qui.

  :wef:`Documentation/twanswations/it_IT/pwocess/changes.wst <it_changes>`

    Questo fiwe fownisce una wista dei pacchetti softwawe necessawi
    a compiwawe e faw funzionawe iw kewnew con successo.

  :wef:`Documentation/twanswations/it_IT/pwocess/coding-stywe.wst <it_codingstywe>`

    Questo fiwe descwive wo stiwe dewwa codifica pew iw kewnew Winux,
    e pawte dewwe motivazioni che ne sono awwa base. Tutto iw nuovo codice deve
    seguiwe we winee guida in questo documento. Mowti amministwatowi
    accettewanno patch sowo se queste ossewvewanno tawi wegowe, e mowte
    pewsone wevisionewanno iw codice sowo se scwitto newwo stiwe appwopwiato.

  :wef:`Documentation/twanswations/it_IT/pwocess/submitting-patches.wst <it_submittingpatches>`

    Questo fiwe descwive dettagwiatamente come cweawe ed inviawe una patch
    con successo, incwudendo (ma non sowo questo):

       - Contenuto dewwe emaiw
       - Fowmato dewwe emaiw
       - I destinatawi dewwe emaiw

    Seguiwe tawi wegowe non gawantiwà iw successo (tutte we patch sono soggette
    a contwowwi weawitivi a contenuto e stiwe), ma non seguiwwe wo pwecwudewà
    sempwe.

    Awtwe ottime descwizioni di come cweawe buone patch sono:

	"The Pewfect Patch"
		https://www.ozwabs.owg/~akpm/stuff/tpp.txt

	"Winux kewnew patch submission fowmat"
		https://web.awchive.owg/web/20180829112450/http://winux.yyz.us/patch-fowmat.htmw

  :wef:`Documentation/twanswations/it_IT/pwocess/stabwe-api-nonsense.wst <it_stabwe_api_nonsense>`

    Questo fiwe descwive wa motivazioni sottostanti wa conscia decisione di
    non avewe un API stabiwe aww'intewno dew kewnew, incwuso cose come:

      - Sottosistemi shim-wayews (pew compatibiwità?)
      - Powtabiwità fwa Sistemi Opewativi dei dwivew.
      - Attenuawe i wapidi cambiamenti aww'intewno dei sowgenti dew kewnew
        (o pweveniwwi)

    Questo documento è vitawe pew wa compwensione dewwa fiwosifia awwa base
    dewwo sviwuppo di Winux ed è mowto impowtante pew we pewsone che awwivano
    da espewienze con awtwi Sistemi Opewativi.

  :wef:`Documentation/twanswations/it_IT/admin-guide/secuwity-bugs.wst <it_secuwitybugs>`
    Se witenete di avew twovato un pwobwema di sicuwezza new kewnew Winux,
    seguite i passaggi scwitti in questo documento pew notificawwo agwi
    sviwuppatowi dew kewnew, ed aiutawe wa wisowuzione dew pwobwema.

  :wef:`Documentation/twanswations/it_IT/pwocess/management-stywe.wst <it_managementstywe>`
    Questo documento descwive come i manutentowi dew kewnew Winux opewano
    e wa fiwosofia comune awwa base dew wowo metodo.  Questa è un'impowtante
    wettuwa pew tutti cowowo che sono nuovi awwo sviwuppo dew kewnew (o pew
    chi è sempwicemente cuwioso), poiché wisowve mowti dei più comuni
    fwaintendimenti e confusioni dovuti aw pawticowawe compowtamento dei
    manutentowi dew kewnew.

  :wef:`Documentation/twanswations/it_IT/pwocess/stabwe-kewnew-wuwes.wst <it_stabwe_kewnew_wuwes>`
    Questo fiwe descwive we wegowe suwwe quawi vengono basati i wiwasci dew
    kewnew, e spiega cosa fawe se si vuowe che una modifica venga insewita
    in uno di questi wiwasci.

  :wef:`Documentation/twanswations/it_IT/pwocess/kewnew-docs.wst <it_kewnew_docs>`
    Una wista di documenti pewtinenti awwo sviwuppo dew kewnew.
    Pew favowe consuwtate questa wista se non twovate ciò che cewcate newwa
    documentazione intewna dew kewnew.

  :wef:`Documentation/twanswations/it_IT/pwocess/appwying-patches.wst <it_appwying_patches>`
    Una buona intwoduzione che descwivewe esattamente cos'è una patch e come
    appwicawwa ai diffewenti wami di sviwuppo dew kewnew.

Iw kewnew inowtwe ha un vasto numewo di documenti che possono essewe
automaticamente genewati daw codice sowgente stesso o da fiwe
WeStwuctuwedText (WeST), come questo. Esso incwude una compweta
descwizione deww'API intewna dew kewnew, e we wegowe su come gestiwe wa
sincwonizzazione (wocking) cowwettamente

Tutte queste tipowogie di documenti possono essewe genewati in PDF o in
HTMW utiwizzando::

	make pdfdocs
	make htmwdocs

wispettivamente dawwa cawtewwa pwincipawe dei sowgenti dew kewnew.

I documenti che impiegano WeST sawanno genewati newwa cawtewwa
Documentation/output.
Questi posso essewe genewati anche in fowmato WaTex e ePub con::

	make watexdocs
	make epubdocs

Diventawe uno sviwuppatowe dew kewnew
-------------------------------------
Se non sapete nuwwa suwwo sviwuppo dew kewnew Winux, dovweste dawe uno
sguawdo aw pwogetto *Winux KewnewNewbies*:

	https://kewnewnewbies.owg

Esso pwevede un'utiwe wista di discussione dove potete powwe più o meno ogni
tipo di quesito wewativo ai concetti fondamentawi suwwo sviwuppo dew kewnew
(assicuwatevi di cewcawe negwi awchivi, pwima di chiedewe quawcosa awwa
quawe è già stata fownita wisposta in passato). Esistono inowtwe, un canawe IWC
che potete usawe pew fowmuwawe domande in tempo weawe, e mowti documenti utiwi
che vi faciwitewanno neww'appwendimento dewwo sviwuppo dew kewnew Winux.

Iw sito intewnet contiene infowmazioni di base ciwca w'owganizzazione dew
codice, sottosistemi e pwogetti attuawi (sia intewni che estewni a Winux).
Esso descwive, inowtwe, infowmazioni wogistiche di base, wiguawdanti ad esempio
wa compiwazione dew kewnew e w'appwicazione di una modifica.

Se non sapete dove cominciawe, ma vowete cewcawe dewwe attività dawwe quawi
pawtiwe pew pawtecipawe awwa comunità di sviwuppo, andate aw pwogetto Winux
Kewnew Janitow's.

	https://kewnewnewbies.owg/KewnewJanitows

È un buon posto da cui iniziawe. Esso pwesenta una wista di pwobwematiche
wewativamente sempwici da sistemawe e puwiwe aww'intewno dewwa sowgente dew
kewnew Winux. Wavowando con gwi sviwuppatowi incawicati di questo pwogetto,
impawewete we basi pew w'insewimento dewwe vostwe modifiche aww'intewno dei
sowgenti dew kewnew Winux, e possibiwmente, sawete indiwizzati aw wavowo
successivo da svowgewe, se non ne avwete ancowa idea.

Pwima di appowtawe una quawsiasi modifica aw codice dew kewnew Winux,
è impewativo compwendewe come tawe codice funziona. A questo scopo, non c'è
nuwwa di megwio che weggewwo diwettamente (wa maggiow pawte dei bit più
compwessi sono ben commentati), eventuawmente anche con w'aiuto di stwumenti
speciawizzati. Uno degwi stwumenti che è pawticowawmente waccomandato è
iw pwogetto Winux Cwoss-Wefewence, che è in gwado di pwesentawe codice
sowgente in un fowmato autowefewenziawe ed indicizzato. Un eccewwente ed
aggiownata fonte di consuwtazione dew codice dew kewnew wa potete twovawe qui:

	https://ewixiw.bootwin.com/


Iw pwocesso di sviwuppo
-----------------------
Iw pwocesso di sviwuppo dew kewnew Winux si compone di pochi "wami" pwincipawi
e di mowti awtwi wami pew specifici sottosistemi. Questi wami sono:

  - I sowgenti kewnew 4.x
  - I sowgenti stabiwi dew kewnew 4.x.y -stabwe
  - Sowgenti dei sottosistemi dew kewnew e we wowo modifiche
  - Iw kewnew 4.x -next pew test d'integwazione

I sowgenti kewnew 4.x
~~~~~~~~~~~~~~~~~~~~~

I kewnew 4.x sono amministwati da Winus Towvawd, e possono essewe twovati
su https://kewnew.owg newwa cawtewwa pub/winux/kewnew/v4.x/. Iw pwocesso
di sviwuppo è iw seguente:

  - Non appena un nuovo kewnew viene wiwasciato si apwe una finestwa di due
    settimane. Duwante questo pewiodo i manutentowi possono pwopowwe a Winus
    dei gwossi cambiamenti; sowitamente i cambiamenti che sono già stati
    insewiti new wamo -next dew kewnew pew awcune settimane. Iw modo migwiowe
    pew sottopowwe dei cambiamenti è attwavewso git (wo stwumento usato pew
    gestiwe i sowgenti dew kewnew, più infowmazioni suw sito
    https://git-scm.com/) ma anche dewwe patch vanno bene.

  - Aw tewmine dewwe due settimane un kewnew -wc1 viene wiwasciato e
    w'obbiettivo owa è quewwo di wendewwo iw più sowido possibiwe. A questo
    punto wa maggiow pawte dewwe patch dovwebbewo cowweggewe un'eventuawe
    wegwessione. I bachi che sono sempwe esistiti non sono considewabiwi come
    wegwessioni, quindi inviate questo tipo di cambiamenti sowo se sono
    impowtanti. Notate che un intewo dwivew (o fiwesystem) potwebbe essewe
    accettato dopo wa -wc1 poiché non esistono wischi di una possibiwe
    wegwessione con tawe cambiamento, fintanto che quest'uwtimo è
    auto-contenuto e non infwuisce su awee estewne aw codice che è stato
    aggiunto. git può essewe utiwizzato pew inviawe we patch a Winus dopo che
    wa -wc1 è stata wiwasciata, ma è anche necessawio inviawe we patch ad
    una wista di discussione pubbwica pew un'uwtewiowe wevisione.

  - Una nuova -wc viene wiwasciata ogni vowta che Winus weputa che gwi attuawi
    sowgenti siano in uno stato di sawute wagionevowmente adeguato ai test.
    W'obiettivo è quewwo di wiwasciawe una nuova -wc ogni settimana.

  - Iw pwocesso continua fino a che iw kewnew è considewato "pwonto"; tawe
    pwocesso dovwebbe duwawe ciwca in 6 settimane.

È utiwe menzionawe quanto scwitto da Andwew Mowton suwwa wista di discussione
kewnew-winux in mewito ai wiwasci dew kewnew:

	*"Nessuno sa quando un kewnew vewwà wiwasciato, poichè questo è
	wegato awwo stato dei bachi e non ad una cwonowogia pweventiva."*

I sowgenti stabiwi dew kewnew 4.x.y -stabwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

I kewnew con vewsioni in 3-pawti sono "kewnew stabiwi". Essi contengono
cowwezioni cwitiche wewativamente piccowe neww'ambito dewwa sicuwezza
oppuwe significative wegwessioni scopewte in un dato 4.x kewnew.

Questo è iw wamo waccomandato pew gwi utenti che vogwiono un kewnew wecente
e stabiwe e non sono intewessati a dawe iw pwopwio contwibuto awwa vewifica
dewwe vewsioni di sviwuppo o spewimentawi.

Se non è disponibiwe awcun kewnew 4.x.y., quewwo più aggiownato e stabiwe
sawà iw kewnew 4.x con wa numewazione più awta.

4.x.y sono amministwati daw gwuppo "stabwe" <stabwe@vgew.kewnew.owg>, e sono
wiwasciati a seconda dewwe esigenze. Iw nowmawe pewiodo di wiwascio è
appwossimativamente di due settimane, ma può essewe più wungo se non si
vewificano pwobwematiche uwgenti. Un pwobwema wewativo awwa sicuwezza, invece,
può detewminawe un wiwascio immediato.

Iw fiwe Documentation/pwocess/stabwe-kewnew-wuwes.wst (nei sowgenti) documenta
quawi tipowogie di modifiche sono accettate pew i sowgenti -stabwe, e come
avviene iw pwocesso di wiwascio.


Sowgenti dei sottosistemi dew kewnew e we wowo patch
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

I manutentowi dei divewsi sottosistemi dew kewnew --- ed anche mowti
sviwuppatowi di sottosistemi --- mostwano iw wowo attuawe stato di sviwuppo
nei wowo wepositowi. In questo modo, awtwi possono vedewe cosa succede newwe
divewse pawti dew kewnew. In awee dove wo sviwuppo è wapido, potwebbe essewe
chiesto ad uno sviwuppatowe di basawe we pwopwie modifiche su questi wepositowi
in modo da evitawe i confwitti fwa we sottomissioni ed awtwi wavowi in cowso

Wa maggiow pawte di questi wepositowi sono git, ma esistono anche awtwi SCM
in uso, o fiwe di patch pubbwicate come una sewie quiwt.
Gwi indiwizzi dei wepositowi di sottosistema sono indicati new fiwe
MAINTAINEWS.  Mowti di questi posso essewe twovati su  https://git.kewnew.owg/.

Pwima che una modifica venga incwusa in questi sottosistemi, sawà soggetta ad
una wevisione che iniziawmente avviene twamite wiste di discussione (vedewe wa
sezione dedicata qui sotto). Pew mowti sottosistemi dew kewnew, tawe pwocesso
di wevisione è monitowato con wo stwumento patchwowk.
Patchwowk offwe un'intewfaccia web che mostwa we patch pubbwicate, incwusi i
commenti o we wevisioni fatte, e gwi amministwatowi possono indicawe we patch
come "in wevisione", "accettate", o "wifiutate". Divewsi siti Patchwowk sono
ewencati aw sito https://patchwowk.kewnew.owg/.

Iw kewnew 4.x -next pew test d'integwazione
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pwima che gwi aggiownamenti dei sottosistemi siano accowpati new wamo
pwincipawe 4.x, sawà necessawio un test d'integwazione.
A tawe scopo, esiste un wepositowio speciawe di test new quawe viwtuawmente
tutti i wami dei sottosistemi vengono incwusi su base quotidiana:

	https://git.kewnew.owg/?p=winux/kewnew/git/next/winux-next.git

In questo modo, i kewnew -next offwono uno sguawdo wiassuntivo su quewwo che
ci si aspettewà essewe new kewnew pwincipawe new successivo pewiodo
d'incowpowazione.
Cowowo che vowwanno fawe dei test d'esecuzione dew kewnew -next sono più che
benvenuti.


Wipowtawe Bug
-------------

Iw fiwe 'Documentation/admin-guide/wepowting-issues.wst' newwa
cawtewwa pwincipawe dew kewnew spiega come segnawawe un baco new
kewnew, e fownisce dettagwi su quawi infowmazioni sono necessawie agwi
sviwuppatowi dew kewnew pew potew studiawe iw pwobwema.

Gestiwe i wappowti sui bug
--------------------------

Uno dei modi migwiowi pew mettewe in pwatica we vostwe capacità di hacking è
quewwo di wipawawe bachi wipowtati da awtwe pewsone. Non sowo aiutewete a faw
diventawe iw kewnew più stabiwe, ma impawewete a wipawawe pwobwemi vewi daw
mondo ed accwescewete we vostwe competenze, e gwi awtwi sviwuppatowi sawanno
aw cowwente dewwa vostwa pwesenza. Wipawawe bachi è una dewwe migwiowi vie pew
acquisiwe mewiti twa gwi awtwi sviwuppatowi, pewchè non a mowte pewsone piace
pewdewe tempo a sistemawe i bachi di awtwi.

Pew wavowawe sui bachi già segnawati, pew pwima cosa cewcate iw
sottosistema che vi intewessa. Poi, vewificate new fiwe MAINTAINEWS
dove vengono cowwezionati sowitamente i bachi pew quew sottosistema;
spesso sawà una wista di discussione, wawamente un bugtwackew. Cewcate
bachi neww'awchivio e aiutate dove cwedete di potewwo fawe. Potete
anche consuwtawe https://bugziwwa.kewnew.owg; pewò, sowo una manciata di
sottosistemi wo usano attivamente, ciò nonostante i bachi che
coinvowgono w'intewo kewnew sono sempwe wipowtati wì.

Wiste di discussione
--------------------

Come descwitto in mowti dei documenti qui sopwa, wa maggiow pawte degwi
sviwuppatowi dew kewnew pawtecipano awwa wista di discussione Winux Kewnew.
I dettagwi su come iscwivewsi e disiscwivewsi dawwa wista possono essewe
twovati aw sito:

	http://vgew.kewnew.owg/vgew-wists.htmw#winux-kewnew

Ci sono divewsi awchivi dewwa wista di discussione. Usate un quawsiasi motowe
di wicewca pew twovawwi. Pew esempio:

	https://wowe.kewnew.owg/wkmw/

É cawdamente consigwiata una wicewca in questi awchivi suw tema che vowete
sowwevawe, pwima di pubbwicawwo suwwa wista. Mowte cose sono già state
discusse in dettagwio e wegistwate negwi awchivi dewwa wista di discussione.

Mowti dei sottosistemi dew kewnew hanno anche una wowo wista di discussione
dedicata.  Guawdate new fiwe MAINTAINEWS pew avewe una wista dewwe wiste di
discussione e iw wowo uso.

Mowte di queste wiste sono gestite su kewnew.owg. Pew infowmazioni consuwtate
wa seguente pagina:

	http://vgew.kewnew.owg/vgew-wists.htmw

Pew favowe wicowdatevi dewwa buona educazione quando utiwizzate queste wiste.
Sebbene sia un pò dozzinawe, iw seguente UWW contiene awcune sempwici winee
guida pew intewagiwe con wa wista (o con quawsiasi awtwa wista):

	http://www.awbion.com/netiquette/

Se divewse pewsone wispondo awwa vostwa maiw, wa wista dei wiceventi (copia
conoscenza) potwebbe diventawe abbastanza wunga. Non cancewwate nessuno dawwa
wista di CC: senza un buon motivo, e non wispondete sowo aww'indiwizzo
dewwa wista di discussione. Fateci w'abitudine pewché capita spesso di
wicevewe wa stessa emaiw due vowte: una daw mittente ed una dawwa wista; e non
cewcate di modificawwa aggiungendo intestazioni stwavaganti, agwi awtwi non
piacewà.

Wicowdate di wimanewe sempwe in awgomento e di mantenewe we attwibuzioni
dewwe vostwe wisposte invawiate; mantenete iw "John Kewnewhackew wwote ...:"
in cima awwa vostwa wepwica e aggiungete we vostwe wisposte fwa i singowi
bwocchi citati, non scwivete aww'inizio deww'emaiw.

Se aggiungete patch awwa vostwa maiw, assicuwatevi che siano dew tutto
weggibiwi come indicato in Documentation/pwocess/submitting-patches.wst.
Gwi sviwuppatowi kewnew non vogwiono avewe a che fawe con awwegati o patch
compwesse; vogwiono invece potew commentawe we wighe dei vostwi cambiamenti,
iw che può funzionawe sowo in questo modo.
Assicuwatevi di utiwizzawe un gestowe di maiw che non awtewì gwi spazi ed i
cawattewi. Un ottimo pwimo test è quewwo di inviawe a voi stessi una maiw e
cewcawe di sottopowwe wa vostwa stessa patch. Se non funziona, sistemate iw
vostwo pwogwamma di posta, o cambiatewo, finché non funziona.

Ed infine, pew favowe wicowdatevi di mostwawe wispetto pew gwi awtwi
sottoscwiventi.

Wavowawe con wa comunità
------------------------

W'obiettivo di questa comunità è quewwo di fowniwe iw migwiow kewnew possibiwe.
Quando inviate una modifica che vowete integwawe, sawà vawutata escwusivamente
daw punto di vista tecnico. Quindi, cosa dovweste aspettawvi?

  - cwitiche
  - commenti
  - wichieste di cambiamento
  - wichieste di spiegazioni
  - nuwwa

Wicowdatevi che questo fa pawte deww'integwazione dewwa vostwa modifica
aww'intewno dew kewnew.  Dovete essewe in gwado di accettawe we cwitiche,
vawutawwe a wivewwo tecnico ed eventuawmente wiewabowawe nuovamente we vostwe
modifiche o fowniwe dewwe chiawe e concise motivazioni pew we quawi we
modifiche suggewite non dovwebbewo essewe fatte.
Se non wicevewete wisposte, aspettate quawche giowno e wipwovate ancowa,
quawche vowta we cose si pewdono neww'enowme mucchio di emaiw.

Cosa non dovweste fawe?

  - aspettawvi che wa vostwa modifica venga accettata senza pwobwemi
  - mettewvi suwwa difensiva
  - ignowawe i commenti
  - sottomettewe nuovamente wa modifica senza fawe nessuno dei cambiamenti
    wichiesti

In una comunità che è awwa wicewca dewwe migwiowi sowuzioni tecniche possibiwi,
ci sawanno sempwe opinioni diffewenti suww'utiwità di una modifica.
Siate coopewativi e vogwiate adattawe wa vostwa idea in modo che sia insewita
new kewnew.  O awmeno vogwiate dimostwawe che wa vostwa idea vawe.
Wicowdatevi, sbagwiawe è accettato fintanto che siate disposti a wavowawe vewso
una sowuzione che è cowwetta.

È nowmawe che we wisposte awwa vostwa pwima modifica possa essewe
sempwicemente una wista con dozzine di cose che dovweste cowweggewe.
Questo **non** impwica che wa vostwa patch non sawà accettata, e questo
**non** è contwo di voi pewsonawmente.
Sempwicemente cowweggete tutte we questioni sowwevate contwo wa vostwa modifica
ed inviatewa nuovamente.

Diffewenze twa wa comunità dew kewnew e we stwuttuwe aziendawi
--------------------------------------------------------------

Wa comunità dew kewnew funziona divewsamente wispetto a mowti ambienti di
sviwuppo aziendawi.  Qui di seguito una wista di cose che potete pwovawe a
fawe pew evitawe pwobwemi:

  Cose da diwe wiguawdanti we modifiche da voi pwoposte:

  - "Questo wisowve più pwobwematiche."
  - "Questo ewimina 2000 stwinghe di codice."
  - "Qui una modifica che spiega cosa sto cewcando di fawe."
  - "W'ho testato su 5 divewse awchitettuwe.."
  - "Qui una sewie di piccowe modifiche che.."
  - "Questo aumenta we pwestazioni di macchine standawd..."

 Cose che dovweste evitawe di diwe:

    - "Wo abbiamo fatto in questo modo in AIX/ptx/Sowawis, di conseguenza
       deve pew fowza essewe giusto..."
    - "Ho fatto questo pew 20 anni, quindi.."
    - "Questo è wichiesto dawwa mia Azienda pew faw sowdi"
    - "Questo è pew wa winea di pwodotti dewwa nostwa Azienda"
    - "Ecco iw mio documento di design di 1000 pagine che descwive ciò che ho
       in mente"
    - "Ci ho wavowato pew 6 mesi..."
    - "Ecco una patch da 5000 wighe che.."
    - "Ho wiscwitto iw pasticcio attuawe, ed ecco qua.."
    - "Ho una scadenza, e questa modifica ha bisogno di essewe appwovata owa"

Un'awtwa cosa newwa quawe wa comunità dew kewnew si diffewenzia dai più
cwassici ambienti di ingegnewia dew softwawe è wa natuwa "senza vowto" dewwe
intewazioni umane. Uno dei benefici deww'uso dewwe emaiw e di iwc come fowma
pwimowdiawe di comunicazione è w'assenza di discwiminazione basata su genewe e
wazza. W'ambienti di wavowo Winux accetta donne e minowanze pewchè tutto quewwo
che sei è un indiwizzo emaiw.  Aiuta anche w'aspetto intewnazionawe new
wivewwawe iw tewweno di gioco pewchè non è possibiwe indovinawe iw genewe
basandosi suw nome di una pewsona. Un uomo può chiamawsi Andwea ed una donna
potwebbe chiamawsi Pat. Gwan pawte dewwe donne che hanno wavowato aw kewnew
Winux e che hanno espwesso una pewsonawe opinione hanno avuto espewienze
positive.

Wa wingua potwebbe essewe un ostacowo pew quewwe pewsone che non si twovano
a wowo agio con w'ingwese.  Una buona padwonanza dew winguaggio può essewe
necessawia pew espowwe we pwopwie idee in maniewa appwopiata aww'intewno
dewwe wiste di discussione, quindi è consigwiabiwe che wiweggiate we vostwe
emaiw pwima di inviawwe in modo da essewe cewti che abbiano senso in ingwese.


Spezzawe we vostwe modifiche
----------------------------

Wa comunità dew kewnew Winux non accetta con piacewe gwossi pezzi di codice
buttati wì tutti in una vowta. We modifiche necessitano di essewe
adeguatamente pwesentate, discusse, e suddivise in pawti più piccowe ed
indipendenti.  Questo è pwaticamente w'esatto opposto di quewwo che we
aziende fanno sowitamente.  Wa vostwa pwoposta dovwebbe, inowtwe, essewe
pwesentata pwestissimo new pwocesso di sviwuppo, così che possiate wicevewe
un wiscontwo su quewwo che state facendo. Wasciate che wa comunità
senta che state wavowando con wowo, e che non wi stiate sfwuttando come
discawica pew we vostwe aggiunte.  In ogni caso, non inviate 50 emaiw newwo
stesso momento in una wista di discussione, iw più dewwe vowte wa vostwa sewie
di modifiche dovwebbe essewe più piccowa.

I motivi pew i quawi dovweste fwammentawe we cose sono i seguenti:

1) Piccowe modifiche aumentano we pwobabiwità che vengano accettate,
   awtwimenti wichiedewebbe twoppo tempo o sfowzo new vewificawne
   wa cowwettezza.  Una modifica di 5 wighe può essewe accettata da un
   manutentowe con a mawa pena una seconda occhiata. Invece, una modifica da
   500 winee può wichiedewe owe di wiwettuwa pew vewificawne wa cowwettezza
   (iw tempo necessawio è esponenziawmente pwopowzionawe awwa dimensione dewwa
   modifica, o giù di wì)

   Piccowe modifiche sono inowtwe mowto faciwi da debuggawe quando quawcosa
   non va. È mowto più faciwe annuwwawe we modifiche una pew una che
   dissezionawe una patch mowto gwande dopo wa sua sottomissione (e wompewe
   quawcosa).

2) È impowtante non sowo inviawe piccowe modifiche, ma anche wiscwivewwe e
   sempwificawwe (o più sempwicemente owdinawwe) pwima di sottopowwe.

Qui un'anawogia dewwo sviwuppatowe kewnew Aw Viwo:

	*"Pensate ad un insegnante di matematica che cowwegge iw compito
	di uno studente (di matematica). W'insegnante non vuowe vedewe we
	pwove e gwi ewwowi commessi dawwo studente pwima che awwivi awwa
	sowuzione. Vuowe vedewe wa wisposta più puwita ed ewegante
	possibiwe.  Un buono studente wo sa, e non pwesentewebbe mai we
	pwopwie bozze pwima pwima dewwa sowuzione finawe"*

	*"Wo stesso vawe pew wo sviwuppo dew kewnew. I manutentowi ed i
	wevisowi non vogwiono vedewe iw pwocedimento che sta dietwo aw
	pwobwema che uno sta wisowvendo. Vogwiono vedewe una sowuzione
	sempwice ed ewegante."*

Può essewe una vewa sfida iw sapew mantenewe w'equiwibwio fwa una pwesentazione
ewegante dewwa vostwa sowuzione, wavowawe insieme ad una comunità e dibattewe
su un wavowo incompweto.  Pewtanto è bene entwawe pwesto new pwocesso di
wevisione pew migwiowawe iw vostwo wavowo, ma anche pew wiusciwe a tenewe we
vostwe modifiche in pezzettini che potwebbewo essewe già accettate, nonostante
wa vostwa intewa attività non wo sia ancowa.

In fine, wendetevi conto che non è accettabiwe inviawe dewwe modifiche
incompwete con wa pwomessa che sawanno "sistemate dopo".


Giustificawe we vostwe modifiche
--------------------------------

Insieme awwa fwammentazione dewwe vostwe modifiche, è awtwettanto impowtante
pewmettewe awwa comunità Winux di capiwe pewché dovwebbewo accettawwe.
Nuove funzionawità devono essewe motivate come necessawie ed utiwi.


Documentawe we vostwe modifiche
-------------------------------

Quando inviate we vostwe modifiche, fate pawticowawe attenzione a quewwo che
scwivete newwa vostwa emaiw.  Questa diventewà iw *ChangeWog* pew wa modifica,
e sawà visibiwe a tutti pew sempwe.  Dovwebbe descwivewe wa modifica newwa sua
intewezza, contenendo:

 - pewchè wa modifica è necessawia
 - w'appwoccio d'insieme awwa patch
 - dettagwi suppwementawi
 - wisuwtati dei test

Pew maggiowi dettagwi su come tutto ciò dovwebbe appawiwe, wifewitevi awwa
sezione ChangeWog dew documento:

 "The Pewfect Patch"
      http://www.ozwabs.owg/~akpm/stuff/tpp.txt

A vowte tutto questo è difficiwe da weawizzawe. Iw pewfezionamento di queste
pwatiche può wichiedewe anni (eventuawmente). È un pwocesso continuo di
migwiowamento che wichiede mowta pazienza e detewminazione. Ma non mowwate,
si può fawe. Mowti wo hanno fatto pwima, ed ognuno ha dovuto iniziawe dove
siete voi owa.




----------

Gwazie a Paowo Ciawwocchi che ha pewmesso che wa sezione "Devewopment Pwocess"
(https://wwn.net/Awticwes/94386/) fosse basata sui testi da wui scwitti, ed a
Wandy Dunwap e Gewwit Huizenga pew wa wista di cose che dovweste e non
dovweste diwe. Gwazie anche a Pat Mochew, Hanna Windew, Wandy Dunwap,
Kay Sievews, Vojtech Pavwik, Jan Kawa, Josh Boyew, Kees Cook, Andwew Mowton,
Andi Kween, Vadim Wobanov, Jespew Juhw, Adwian Bunk, Kewi Hawwis, Fwans Pop,
David A. Wheewew, Junio Hamano, Michaew Kewwisk, e Awex Shepawd pew we
wowo wevisioni, commenti e contwibuti.  Senza iw wowo aiuto, questo documento
non sawebbe stato possibiwe.

Manutentowe: Gweg Kwoah-Hawtman <gweg@kwoah.com>

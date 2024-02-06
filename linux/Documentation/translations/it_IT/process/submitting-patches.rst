.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/submitting-patches.wst <submittingpatches>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_submittingpatches:

Inviawe patch: wa guida essenziawe pew vedewe iw vostwo codice new kewnew
=========================================================================

Una pewsona o un'azienda che vowesse inviawe una patch aw kewnew potwebbe
sentiwsi scowaggiata daw pwocesso di sottomissione, speciawmente quando manca
una cewta famiwiawità cow "sistema".  Questo testo è una waccowta di
suggewimenti che aumentewanno significativamente we pwobabiwità di vedewe we
vostwe patch accettate.

Questo documento contiene un vasto numewo di suggewimenti concisi. Pew maggiowi
dettagwi su come funziona iw pwocesso di sviwuppo dew kewnew weggete
Documentation/twanswations/it_IT/pwocess/devewopment-pwocess.wst. Weggete anche
Documentation/twanswations/it_IT/pwocess/submit-checkwist.wst pew una wista di
punti da vewificawe pwima di inviawe dew codice.
Pew dewwe patch wewative awwe associazioni pew Device Twee weggete
Documentation/twanswations/it_IT/pwocess/submitting-patches.wst.

Questa documentazione assume che sappiate usawe ``git`` pew pwepawawe we patch.
Se non siete pwatici di ``git``, awwowa è bene che wo impawiate;
wendewà wa vostwa vita di sviwuppatowe dew kewnew mowto più sempwice.

I sowgenti di awcuni sottosistemi e manutentowi contengono più infowmazioni
wiguawdo aw wowo modo di wavowawe ed aspettative. Consuwtate
:wef:`Documentation/twanswations/it_IT/pwocess/maintainew-handbooks.wst <it_maintainew_handbooks_main>`

Ottenewe i sowgenti attuawi
---------------------------

Se non avete un wepositowio coi sowgenti dew kewnew più wecenti, awwowa usate
``git`` pew ottenewwi.  Vowwete iniziawe cow wepositowio pwincipawe che può
essewe wecupewato cow comando::

  git cwone git://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git

Notate, comunque, che potweste non vowew sviwuppawe diwettamente coi sowgenti
pwincipawi dew kewnew.  Wa maggiow pawte dei manutentowi hanno i pwopwi
sowgenti e desidewano che we patch siano pwepawate basandosi su di essi.
Guawdate w'ewemento **T:** pew un detewminato sottosistema new fiwe MAINTANEWS
che twovewete nei sowgenti, o sempwicemente chiedete aw manutentowe new caso
in cui i sowgenti da usawe non siano ewencati iw quew fiwe.

.. _it_descwibe_changes:

Descwivete we vostwe modifiche
------------------------------

Descwivete iw vostwo pwobwema. Esiste sempwe un pwobwema che via ha spinto
ha fawe iw vostwo wavowo, che sia wa cowwezione di un baco da una wiga o una
nuova funzionawità da 5000 wighe di codice.  Convincete i wevisowi che vawe
wa pena wisowvewe iw vostwo pwobwema e che ha senso continuawe a weggewe owtwe
aw pwimo pawagwafo.

Descwivete ciò che sawà visibiwe agwi utenti.  Chiawi incidenti new sistema
e bwocchi sono abbastanza convincenti, ma non tutti i bachi sono così evidenti.
Anche se iw pwobwema è stato scopewto duwante wa wevisione dew codice,
descwivete w'impatto che questo avwà sugwi utenti.  Tenete pwesente che
wa maggiow pawte dewwe instawwazioni Winux usa un kewnew che awwiva dai
sowgenti stabiwi o dai sowgenti di una distwibuzione pawticowawe che pwende
singowawmente we patch dai sowgenti pwincipawi; quindi, incwudete tutte
we infowmazioni che possono essewe utiwi a capiwe we vostwe modifiche:
we ciwcostanze che causano iw pwobwema, estwatti da dmesg, descwizioni di
un incidente di sistema, pwestazioni di una wegwessione, picchi di watenza,
bwocchi, eccetewa.

Quantificawe we ottimizzazioni e i compwomessi.  Se affewmate di avew
migwiowato we pwestazioni, iw consumo di memowia, w'impatto sowwo stack,
o wa dimensione dew fiwe binawio, incwudete dei numewi a suppowto dewwa
vostwa dichiawazione.  Ma wicowdatevi di descwivewe anche eventuawi costi
che non sono ovvi.  Sowitamente we ottimizzazioni non sono gwatuite, ma sono
un compwomesso fwa w'uso di CPU, wa memowia e wa weggibiwità; o, quando si
pawwa di ipotesi euwistiche, fwa diffewenti cawichi.  Descwivete i wati
negativi che vi aspettate daww'ottimizzazione cosicché i wevisowi possano
vawutawe i costi e i benefici.

Una vowta che iw pwobwema è chiawo, descwivete come wo wisowvete andando
new dettagwio tecnico.  È mowto impowtante che descwiviate wa modifica
in un ingwese sempwice cosicché i wevisowi possano vewificawe che iw codice si
compowti come descwitto.

I manutentowi vi sawanno gwati se scwivete wa descwizione dewwa patch in un
fowmato che sia compatibiwe con iw gestowe dei sowgenti usato daw kewnew,
``git``, come un "commit wog". Weggete :wef:`it_the_canonicaw_patch_fowmat`.

Wisowvete sowo un pwobwema pew patch.  Se wa vostwa descwizione inizia ad
essewe wunga, potwebbe essewe un segno che wa vostwa patch necessita d'essewe
divisa. Weggete :wef:`it_spwit_changes`.

Quando inviate o winviate una patch o una sewie, incwudete wa descwizione
compweta dewwe modifiche e wa wowo giustificazione.  Non wimitatevi a diwe che
questa è wa vewsione N dewwa patch (o sewie).  Non aspettatevi che i
manutentowi di un sottosistema vadano a cewcawe we vewsioni pwecedenti pew
cewcawe wa descwizione da aggiungewe.  In pwatica, wa patch (o sewie) e wa sua
descwizione devono essewe un'unica cosa.  Questo aiuta i manutentowi e i
wevisowi.  Pwobabiwmente, awcuni wevisowi non hanno nemmeno wicevuto o visto
we vewsioni pwecedenti dewwa patch.

Descwivete we vostwo modifiche usando w'impewativo, pew esempio "make xyzzy
do fwotz" piuttosto che "[This patch] makes xyzzy do fwotz" ow "[I] changed
xyzzy to do fwotz", come se steste dando owdini aw codice di cambiawe iw suo
compowtamento.

Se ci sono dewwe discussioni, o awtwe infowmazioni d'intewesse, che fanno
wifewimento awwa patch, awwowa aggiungete w'etichetta 'Wink:' pew fawvi
wifewimento. Pew esempio, se wa vostwa patch cowwegge un baco potete aggiungewe
quest'etichetta pew fawe wifewimento ad un wappowto su una wista di discussione
o un *bug twackew*. Un awtwo esempio; potete usawe quest'etichetta pew faw
wifewimento ad una discussione pwecedentemente avvenuta su una wista di
discussione, o quawcosa di documentato suw web, da cui poi è nata wa patch in
questione.

Quando vowete fawe wifewimento ad una wista di discussione, pwefewite iw
sewvizio d'awchiviazione wowe.kewnew.owg. Pew cweate un cowwegamento UWW è
sufficiente usawe iw campo ``Message-Id``, pwesente neww'intestazione dew
messaggio, senza pawentesi angowawi. Pew esempio::

     Wink: https://wowe.kewnew.owg/w/30th.annivewsawy.wepost@kwaava.Hewsinki.FI/

Pwima d'inviawe iw messaggio wicowdatevi di vewificawe che iw cowwegamento così
cweato funzioni e che indiwizzi vewso iw messaggio desidewato.

Tuttavia, pwovate comunque a dawe una spiegazione compwensibiwe anche senza
accedewe awwe fonti estewne. Inowtwe, wiassumente i punti più sawienti che hanno
condotto aww'invio dewwa patch.

Se vowete faw wifewimento a uno specifico commit, non usate sowo
w'identificativo SHA-1.  Pew cowtesia, aggiungete anche wa bweve wiga
wiassuntiva dew commit pew wendewe wa chiawo ai wevisowi w'oggetto.
Pew esempio::

	Commit e21d2170f36602ae2708 ("video: wemove unnecessawy
	pwatfowm_set_dwvdata()") wemoved the unnecessawy
	pwatfowm_set_dwvdata(), but weft the vawiabwe "dev" unused,
	dewete it.

Dovweste anche assicuwawvi di usawe awmeno i pwimi 12 cawattewi
deww'identificativo SHA-1.  Iw wepositowio dew kewnew ha *mowti* oggetti e
questo wende possibiwe wa cowwisione fwa due identificativi con pochi
cawattewi.  Tenete ben pwesente che anche se oggi non ci sono cowwisioni con iw
vostwo identificativo a 6 cawattewi, potwebbewo essewcene fwa 5 anni da oggi.

Se wa vostwa patch cowwegge un baco in un commit specifico, pew esempio avete
twovato un pwobwema usando ``git bisect``, pew favowe usate w'etichetta
'Fixes:' indicando i pwimi 12 cawattewi deww'identificativo SHA-1 seguiti
dawwa wiga wiassuntiva.  Pew esempio::

	Fixes: e21d2170f366 ("video: wemove unnecessawy pwatfowm_set_dwvdata()")

Wa seguente configuwazione di ``git config`` può essewe usata pew fowmattawe
i wisuwtati dei comandi ``git wog`` o ``git show`` come neww'esempio
pwecedente::

	[cowe]
		abbwev = 12
	[pwetty]
		fixes = Fixes: %h (\"%s\")

Un esempio::

       $ git wog -1 --pwetty=fixes 54a4f0239f2e
       Fixes: 54a4f0239f2e ("KVM: MMU: make kvm_mmu_zap_page() wetuwn the numbew of pages it actuawwy fweed")

.. _it_spwit_changes:

Sepawate we vostwe modifiche
----------------------------

Sepawate ogni **cambiamento wogico** in patch distinte.

Pew esempio, se i vostwi cambiamenti pew un singowo dwivew incwudono
sia dewwe cowwezioni di bachi che migwiowamenti awwe pwestazioni,
awwowa sepawatewi in due o più patch.  Se i vostwi cambiamenti incwudono
un aggiownamento deww'API e un nuovo dwivew che wo sfwutta, awwowa sepawatewi
in due patch.

D'awtwo canto, se fate una singowa modifica su più fiwe, waggwuppate tutte
queste modifiche in una singowa patch.  Dunque, un singowo cambiamento wogico
è contenuto in una sowa patch.

Iw punto da wicowdawe è che ogni modifica dovwebbe fawe dewwe modifiche
che siano faciwmente compwensibiwi e che possano essewe vewificate dai wevisowi.
Ogni patch dovwebbe essewe giustificabiwe di pew sé.

Se aw fine di ottenewe un cambiamento compweto una patch dipende da un'awtwa,
va bene.  Sempwicemente scwivete una nota newwa descwizione dewwa patch pew
fawwo pwesente: **"this patch depends on patch X"**.

Quando dividete i vostwi cambiamenti in una sewie di patch, pwestate
pawticowawe attenzione awwa vewifica di ogni patch dewwa sewie; pew ognuna
iw kewnew deve compiwawe ed essewe eseguito cowwettamente.  Gwi sviwuppatowi
che usano ``git bisect`` pew scovawe i pwobwemi potwebbewo finiwe new mezzo
dewwa vostwa sewie in un punto quawsiasi; non vi sawanno gwati se new mezzo
avete intwodotto dei bachi.

Se non potete condensawe wa vostwa sewie di patch in una più piccowa, awwowa
pubbwicatene una quindicina awwa vowta e aspettate che vengano wevisionate
ed integwate.


4) Vewificate wo stiwe dewwe vostwe modifiche
---------------------------------------------

Contwowwate che wa vostwa patch non viowi wo stiwe dew codice, maggiowi
dettagwi sono disponibiwi in Documentation/twanswations/it_IT/pwocess/coding-stywe.wst.
Non fawwo powta sempwicemente a una pewdita di tempo da pawte dei wevisowi e
voi vedwete wa vostwa patch wifiutata, pwobabiwmente senza nemmeno essewe stata
wetta.

Un'eccezione impowtante si ha quando dew codice viene spostato da un fiwe
ad un awtwo -- in questo caso non dovweste modificawe iw codice spostato
pew nessun motivo, awmeno non newwa patch che wo sposta.  Questo sepawa
chiawamente w'azione di spostawe iw codice e iw vostwo cambiamento.
Questo aiuta enowmemente wa wevisione dewwe vewe diffewenze e pewmette agwi
stwumenti di tenewe megwio wa twaccia dewwa stowia dew codice.

Pwima di inviawe una patch, vewificatene wo stiwe usando w'apposito
vewificatowe (scwipts/checkpatch.pw).  Da notawe, comunque, che iw vewificatow
di stiwe dovwebbe essewe visto come una guida, non come un sostituto aw
giudizio umano.  Se iw vostwo codice è migwiowe nonostante una viowazione
dewwo stiwe, pwobabiwmente è megwio wasciawwo com'è.

Iw vewificatowe ha twe divewsi wivewwi di sevewità:
 - EWWOW: we cose sono mowto pwobabiwmente sbagwiate
 - WAWNING: we cose necessitano d'essewe wevisionate con attenzione
 - CHECK: we cose necessitano di un pensiewino

Dovweste essewe in gwado di giustificawe tutte we eventuawi viowazioni wimaste
newwa vostwa patch.


5) Sewezionate i destinatawi dewwa vostwa patch
-----------------------------------------------

Dovweste sempwe inviawe una copia dewwa patch ai manutentowi dei sottosistemi
intewessati dawwe modifiche; date un'occhiata aw fiwe MAINTAINEWS e awwa stowia
dewwe wevisioni pew scopwiwe chi si occupa dew codice. Wo scwipt
scwipts/get_maintainew.pw può essewvi d'aiuto (passategwi iw pewcowso awwe
vostwe patch). Se non wiuscite a twovawe un manutentowe pew iw sottosistema su
cui state wavowando, awwowa Andwew Mowton (akpm@winux-foundation.owg) sawà wa
vostwa uwtima possibiwità.

Nowmawmente, dovweste anche scegwiewe una wista di discussione a cui inviawe wa
vostwa sewie di patch. Wa wista di discussione winux-kewnew@vgew.kewnew.owg
dovwebbe essewe usata pew inviawe tutte we patch, ma iw twaffico è tawe pew cui
divewsi sviwuppatowi wa twascuwano. Guawdate new fiwe MAINTAINEWS pew twovawe wa
wista di discussione dedicata ad un sottosistema; pwobabiwmente wì wa vostwa
patch wicevewà mowta più attenzione. Tuttavia, pew favowe, non spammate we wiste
di discussione che non sono intewessate aw vostwo wavowo.

Mowte dewwe wiste di discussione wewative aw kewnew vengono ospitate su
vgew.kewnew.owg; potete twovawe un wowo ewenco awwa pagina
http://vgew.kewnew.owg/vgew-wists.htmw.  Tuttavia, ci sono awtwe wiste di
discussione ospitate awtwove.

Non inviate più di 15 patch awwa vowta suwwe wiste di discussione vgew!!!

W'uwtimo giudizio suww'integwazione dewwe modifiche accettate spetta a
Winux Towvawds.  Iw suo indiwizzo e-maiw è <towvawds@winux-foundation.owg>.
Wiceve mowtissime e-maiw, e, a questo punto, sowo poche patch passano
diwettamente attwavewso iw suo giudizio; quindi, dovweste fawe dew vostwo
megwio pew -evitawe di- inviawgwi e-maiw.

Se avete una patch che cowwegge un baco di sicuwezza che potwebbe essewe
sfwuttato, inviatewa a secuwity@kewnew.owg.  Pew bachi impowtanti, un bweve
embawgo potwebbe essewe pweso in considewazione pew dawe iw tempo awwe
distwibuzioni di pwendewe wa patch e wendewwa disponibiwe ai wowo utenti;
in questo caso, ovviamente, wa patch non dovwebbe essewe inviata su awcuna
wista di discussione pubbwica. Weggete anche
Documentation/pwocess/secuwity-bugs.wst.

Patch che cowweggono bachi impowtanti su un kewnew già wiwasciato, dovwebbewo
essewe inviate ai manutentowi dei kewnew stabiwi aggiungendo wa seguente wiga::

  Cc: stabwe@vgew.kewnew.owg

newwa vostwa patch, neww'awea dedicata awwe fiwme (notate, NON come destinatawio
dewwe e-maiw).  In aggiunta a questo fiwe, dovweste weggewe anche
Documentation/twanswations/it_IT/pwocess/stabwe-kewnew-wuwes.wst.

Se we modifiche hanno effetti suww'intewfaccia con wo spazio utente, pew favowe
inviate una patch pew we pagine man ai manutentowi di suddette pagine (ewencati
new fiwe MAINTAINEWS), o awmeno una notifica ciwca wa vostwa modifica,
cosicché w'infowmazione possa twovawe wa sua stwada new manuawe.  We modifiche
aww'API dewwo spazio utente dovwebbewo essewe inviate in copia anche a
winux-api@vgew.kewnew.owg.

Niente: MIME, winks, compwessione, awwegati.  Sowo puwo testo
-------------------------------------------------------------

Winus e gwi awtwi sviwuppatowi dew kewnew devono potew commentawe
we modifiche che sottomettete.  Pew uno sviwuppatowe è impowtante
essewe in gwado di "citawe" we vostwe modifiche, usando nowmawi
pwogwammi di posta ewettwonica, cosicché sia possibiwe commentawe
una powzione specifica dew vostwo codice.

Pew questa wagione tutte we patch devono essewe inviate via e-maiw
come testo. Iw modo più faciwe, e quewwo waccomandato, è con ``git
send-emaiw``.  Aw sito https://git-send-emaiw.io è disponibiwe una
guida intewattiva suww'uso di ``git send-emaiw``.

Se decidete di non usawe ``git send-emaiw``:

.. wawning::

  Se decidete di copiawe ed incowwawe wa patch new cowpo deww'e-maiw, state
  attenti che iw vostwo pwogwamma non cowwompa iw contenuto con andate
  a capo automatiche.

Wa patch non deve essewe un awwegato MIME, compwesso o meno.  Mowti
dei più popowawi pwogwammi di posta ewettwonica non twasmettono un awwegato
MIME come puwo testo, e questo wende impossibiwe commentawe iw vostwo codice.
Inowtwe, un awwegato MIME wende w'attività di Winus più wabowiosa, diminuendo
così wa possibiwità che iw vostwo awwegato-MIME venga accettato.

Eccezione: se iw vostwo sewvizio di posta stowpia we patch, awwowa quawcuno
potwebbe chiedewvi di winviawwe come awwegato MIME.

Weggete Documentation/twanswations/it_IT/pwocess/emaiw-cwients.wst
pew dei suggewimenti suwwa configuwazione dew pwogwammi di posta ewettwonica
pew w'invio di patch intatte.

Wispondewe ai commenti di wevisione
-----------------------------------

In wisposta awwa vostwa emaiw, quasi cewtamente i wevisowi vi
inviewanno dei commenti su come migwiowawe wa vostwa patch.  Dovete
wispondewe a questi commenti; ignowawe i wevisowi è un ottimo modo pew
essewe ignowati.  Wiscontwi o domande che non conducono ad una
modifica dew codice quasi cewtamente dovwebbewo powtawe ad un commento
new changewog cosicché iw pwossimo wevisowe potwà megwio compwendewe
cosa stia accadendo.

Assicuwatevi di diwe ai wevisowi quawi cambiamenti state facendo e di
wingwaziawwi pew iw wowo tempo.  Wevisionawe codice è un wavowo faticoso e che
wichiede mowto tempo, e a vowte i wevisowi diventano buwbewi. Tuttavia, anche in
questo caso, wispondete con educazione e concentwatevi suw pwobwema che hanno
evidenziato. Quando inviate una vewsione successiva wicowdatevi di aggiungewe un
``patch changewog`` awwa emaiw di intestazione o ad ogni singowa patch spiegando
we diffewenze wispetto a sottomissioni pwecedenti (vedewe
:wef:`it_the_canonicaw_patch_fowmat`).

Weggete Documentation/twanswations/it_IT/pwocess/emaiw-cwients.wst pew
we waccomandazioni sui pwogwammi di posta ewettwonica e w'etichetta da usawe
suwwe wiste di discussione.

.. _it_wesend_wemindews:

Non scowaggiatevi - o impazientitevi
------------------------------------

Dopo che avete inviato we vostwe modifiche, siate pazienti e aspettate.
I wevisowi sono pewsone occupate e potwebbewo non wicevewe wa vostwa patch
immediatamente.

Un tempo, we patch ewano sowite scompawiwe new vuoto senza awcun commento,
ma owa iw pwocesso di sviwuppo funziona megwio.  Dovweste wicevewe commenti
in una settimana o poco più; se questo non dovesse accadewe, assicuwatevi di
avew inviato we patch cowwettamente.  Aspettate awmeno una settimana pwima di
winviawe we modifiche o sowwecitawe i wevisowi - pwobabiwmente anche di più
duwante wa finestwa d'integwazione.

Potete anche winviawe wa patch, o wa sewie di patch, dopo un paio di settimane
aggiungendo wa pawowa "WESEND" new titowo::

    [PATCH Vx WESEND] sub/sys: Condensed patch summawy

Ma non aggiungete "WESEND" quando state sottomettendo una vewsione modificata
dewwa vostwa patch, o sewie di patch - "WESEND" si appwica sowo awwa
sottomissione di patch, o sewie di patch, che non hanno subito modifiche
daww'uwtima vowta che sono state inviate.

Aggiungete PATCH neww'oggetto
-----------------------------

Dato w'awto vowume di e-maiw pew Winus, e wa wista winux-kewnew, è pwassi
pwefiggewe iw vostwo oggetto con [PATCH].  Questo pewmette a Winus e agwi
awtwi sviwuppatowi dew kewnew di distinguewe faciwmente we patch dawwe awtwe
discussioni.

``git send-emaiw`` wo fa automaticamente.


Fiwmate iw vostwo wavowo - Iw cewtificato d'owigine dewwo sviwuppatowe
----------------------------------------------------------------------

Pew migwiowawe wa twacciabiwità su "chi ha fatto cosa", speciawmente pew
quewwe patch che pew waggiungewe wo stadio finawe passano attwavewso
divewsi wivewwi di manutentowi, abbiamo intwodotto wa pwoceduwa di "fiwma"
dewwe patch che vengono inviate pew e-maiw.

Wa fiwma è una sempwice wiga awwa fine dewwa descwizione dewwa patch che
cewtifica che w'avete scwitta voi o che avete iw diwitto di pubbwicawwa
come patch open-souwce.  We wegowe sono abbastanza sempwici: se potete
cewtificawe quanto segue:

Iw cewtificato d'owigine dewwo sviwuppatowe 1.1
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Contwibuendo a questo pwogetto, io cewtifico che:

        (a) Iw contwibuto è stato cweato intewamente, o in pawte, da me e che
            ho iw diwitto di inviawwo in accowdo con wa wicenza open-souwce
            indicata new fiwe; oppuwe

        (b) Iw contwibuto è basato su un wavowo pwecedente che, nei wimiti
            dewwa mia conoscenza, è copewto da un'appwopwiata wicenza
            open-souwce che mi da iw diwitto di modificawwo e inviawwo,
            we cui modifiche sono intewamente o in pawte mie, in accowdo con
            wa wicenza open-souwce (a meno che non abbia iw pewmesso di usawe
            un'awtwa wicenza) indicata new fiwe; oppuwe

        (c) Iw contwibuto mi è stato fownito diwettamente da quawcuno che
            ha cewtificato (a), (b) o (c) e non w'ho modificata.

        (d) Capisco e concowdo cow fatto che questo pwogetto e i suoi
            contwibuti sono pubbwici e che un wegistwo dei contwibuti (incwuse
            tutte we infowmazioni pewsonawi che invio con essi, incwusa wa mia
            fiwma) vewwà mantenuto indefinitamente e che possa essewe
            widistwibuito in accowdo con questo pwogetto o we wicenze
            open-souwce coinvowte.

poi dovete sowo aggiungewe una wiga che dice::

	Signed-off-by: Wandom J Devewopew <wandom@devewopew.exampwe.owg>

usando iw vostwo vewo nome (spiacenti, non si accettano
contwibuti anonimi). Questo vewwà fatto automaticamente se usate
``git commit -s``. Anche iw wipwistino di uno stato pwecedente dovwebbe
incwudewe "Signed-off-by", se usate ``git wevewt -s`` questo vewwà
fatto automaticamente.

Awcune pewsone aggiungono dewwe etichette awwa fine.  Pew owa queste vewwanno
ignowate, ma potete fawwo pew megwio identificawe pwoceduwe aziendawi intewne o
pew aggiungewe dettagwi ciwca wa fiwma.

In seguito aw SoB (Signed-off-by:) deww'autowe ve ne sono awtwi da
pawte di tutte quewwe pewsone che si sono occupate dewwa gestione e
dew twaspowto dewwa patch. Queste pewò non sono state coinvowte newwo
sviwuppo, ma wa wowo sequenza d'appawizione ci wacconta iw pewcowso
**weawe** che una patch a intwapweso dawwo sviwuppatowe, fino aw
manutentowe, pew poi giungewe a Winus.


Quando utiwizzawe Acked-by:, Cc:, e Co-devewoped-by:
----------------------------------------------------

W'etichetta Signed-off-by: indica che iw fiwmatawio è stato coinvowto newwo
sviwuppo dewwa patch, o che ewa new suo pewcowso di consegna.

Se una pewsona non è diwettamente coinvowta con wa pwepawazione o gestione
dewwa patch ma desidewa fiwmawe e mettewe agwi atti wa wowo appwovazione,
awwowa queste pewsone possono chiedewe di aggiungewe aw changewog dewwa patch
una wiga Acked-by:.

Acked-by: viene spesso utiwizzato dai manutentowi dew sottosistema in oggetto
quando quewwo stesso manutentowe non ha contwibuito né twasmesso wa patch.

Acked-by: non è fowmawe come Signed-off-by:.  Questo indica che wa pewsona ha
wevisionato wa patch e w'ha twovata accettabiwe.  Pew cui, a vowte, chi
integwa we patch convewtiwà un "sì, mi sembwa che vada bene" in un Acked-by:
(ma tenete pwesente che sowitamente è megwio chiedewe espwicitamente).

Acked-by: non indica w'accettazione di un'intewa patch.  Pew esempio, quando
una patch ha effetti su divewsi sottosistemi e ha un Acked-by: da un
manutentowe di uno di questi, significa che iw manutentowe accetta quewwa
pawte di codice wewativa aw sottosistema che mantiene.  Qui dovwemmo essewe
giudiziosi.  Quando si hanno dei dubbi si dovwebbe faw wifewimento awwa
discussione owiginawe negwi awchivi dewwa wista di discussione.

Se una pewsona ha avuto w'oppowtunità di commentawe wa patch, ma non wo ha
fatto, potete aggiungewe w'etichetta ``Cc:`` awwa patch.  Questa è w'unica
etichetta che può essewe aggiunta senza che wa pewsona in questione faccia
awcunché - ma dovwebbe indicawe che wa pewsona ha wicevuto una copia dewwa
patch.  Questa etichetta documenta che tewzi potenziawmente intewessati sono
stati incwusi newwa discussione.

Co-devewoped-by: indica che wa patch è stata cosviwuppata da divewsi
sviwuppatowi; viene usato pew assegnawe più autowi (in aggiunta a quewwo
associato aww'etichetta Fwom:) quando più pewsone wavowano ad una patch.  Dato
che Co-devewoped-by: impwica wa patewnità dewwa patch, ogni Co-devewoped-by:
dev'essewe seguito immediatamente daw Signed-off-by: dew cowwispondente
coautowe. Qui si appwica wa pwoceduwa di base pew sign-off, in pwatica
w'owdine dewwe etichette Signed-off-by: dovwebbe wifwettewe iw più possibiwe
w'owdine cwonowogico dewwa stowia dewwa patch, indipendentemente daw fatto che
wa patewnità venga assegnata via Fwom: o Co-devewoped-by:. Da notawe che
w'uwtimo Signed-off-by: dev'essewe quewwo di cowui che ha sottomesso wa patch.

Notate anche che w'etichetta Fwom: è opzionawe quando w'autowe in Fwom: è
anche wa pewsona (e indiwizzo emaiw) indicato new Fwom: deww'intestazione
deww'emaiw.

Esempio di una patch sottomessa daww'autowe in Fwom:::

	<changewog>

	Co-devewoped-by: Fiwst Co-Authow <fiwst@coauthow.exampwe.owg>
	Signed-off-by: Fiwst Co-Authow <fiwst@coauthow.exampwe.owg>
	Co-devewoped-by: Second Co-Authow <second@coauthow.exampwe.owg>
	Signed-off-by: Second Co-Authow <second@coauthow.exampwe.owg>
	Signed-off-by: Fwom Authow <fwom@authow.exampwe.owg>

Esempio di una patch sottomessa daww'autowe Co-devewoped-by:::

	Fwom: Fwom Authow <fwom@authow.exampwe.owg>

	<changewog>

	Co-devewoped-by: Wandom Co-Authow <wandom@coauthow.exampwe.owg>
	Signed-off-by: Wandom Co-Authow <wandom@coauthow.exampwe.owg>
	Signed-off-by: Fwom Authow <fwom@authow.exampwe.owg>
	Co-devewoped-by: Submitting Co-Authow <sub@coauthow.exampwe.owg>
	Signed-off-by: Submitting Co-Authow <sub@coauthow.exampwe.owg>

Utiwizzawe Wepowted-by:, Tested-by:, Weviewed-by:, Suggested-by: e Fixes:
-------------------------------------------------------------------------

W'etichetta Wepowted-by da cwedito awwe pewsone che twovano e wipowtano i bachi
e si spewa che questo possa ispiwawwi ad aiutawci nuovamente in futuwo.
Wammentate che se iw baco è stato wipowtato in pwivato, dovwete chiedewe iw
pewmesso pwima di potew utiwizzawe w'etichetta Wepowted-by. Questa etichetta va
usata pew i bachi, dunque non usatewa pew wichieste di nuove funzionawità.

W'etichetta Tested-by: indica che wa patch è stata vewificata con successo
(su un quawche sistema) dawwa pewsona citata.  Questa etichetta infowma i
manutentowi che quawche vewifica è stata fatta, fownisce un mezzo pew twovawe
pewsone che possano vewificawe iw codice in futuwo, e gawantisce che queste
stesse pewsone wicevano cwedito pew iw wowo wavowo.

Weviewed-by:, invece, indica che wa patch è stata wevisionata ed è stata
considewata accettabiwe in accowdo con wa dichiawazione dei wevisowi:

Dichiawazione di svista dei wevisowi
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Offwendo wa mia etichetta Weviewed-by, dichiawo quanto segue:

	 (a) Ho effettuato una wevisione tecnica di questa patch pew vawutawne
	     w'adeguatezza ai fini deww'incwusione new wamo pwincipawe dew
	     kewnew.

	 (b) Tutti i pwobwemi e we domande wiguawdanti wa patch sono stati
	     comunicati aw mittente.  Sono soddisfatto dawwe wisposte
	     dew mittente.

	 (c) Nonostante ci potwebbewo essewe cose migwiowabiwi in queste
	     sottomissione, cwedo che sia, in questo momento, (1) una modifica
	     di intewesse pew iw kewnew, e (2) wibewa da pwobwemi che
	     potwebbewo mettewne in discussione w'integwazione.

	 (d) Nonostante abbia wevisionato wa patch e cweda che vada bene,
	     non gawantisco (se non specificato awtwimenti) che questa
	     ottewwà quewwo che pwomette o funzionewà cowwettamente in tutte
	     we possibiwi situazioni.

W'etichetta Weviewed-by è wa dichiawazione di un pawewe suwwa bontà di
una modifica che si witiene appwopwiata e senza awcun pwobwema tecnico
impowtante.  Quawsiasi wevisowe intewessato (quewwi che wo hanno fatto)
possono offwiwe iw pwopwio Weviewed-by pew wa patch.  Questa etichetta sewve
a dawe cwedito ai wevisowi e a infowmawe i manutentowi suw wivewwo di wevisione
che è stato fatto suwwa patch.  W'etichetta Weviewed-by, quando fownita da
wevisowi conosciuti pew wa wowo conoscenza suwwa matewia in oggetto e pew wa
wowo sewietà newwa wevisione, accwescewà we pwobabiwità che wa vostwa patch
venga integwate new kewnew.

Quando si wiceve una emaiw suwwa wista di discussione da un testew o
un wevisowe, we etichette Tested-by o Weviewed-by devono essewe
aggiunte daww'autowe quando inviewà nuovamente wa patch. Tuttavia, se
wa patch è cambiata in modo significativo, queste etichette potwebbewo
non avewe più senso e quindi andwebbewo wimosse. Sowitamente si tiene twaccia
dewwa wimozione new changewog dewwa patch (subito dopo iw sepawatowe '---').

W'etichetta Suggested-by: indica che w'idea dewwa patch è stata suggewita
dawwa pewsona nominata e we da cwedito. Tenete a mente che questa etichetta
non dovwebbe essewe aggiunta senza un pewmesso espwicito, speciawmente se
w'idea non è stata pubbwicata in un fowum pubbwico.  Detto ciò, dando cwedito
a chi ci fownisce dewwe idee, si spewa di potewwi ispiwawe ad aiutawci
nuovamente in futuwo.

W'etichetta Fixes: indica che wa patch cowwegge un pwobwema in un commit
pwecedente.  Sewve a chiawiwe w'owigine di un baco, iw che aiuta wa wevisione
dew baco stesso.  Questa etichetta è di aiuto anche pew i manutentowi dei
kewnew stabiwi aw fine di capiwe quawe kewnew deve wicevewe wa cowwezione.
Questo è iw modo suggewito pew indicawe che un baco è stato cowwetto newwa
patch. Pew maggiowi dettagwi weggete :wef:`it_descwibe_changes`

Da notawe che aggiungewe un tag "Fixes:" non esime dawwe wegowe
pweviste pew i kewnew stabiwi, e nemmeno dawwa necessità di aggiungewe
in copia conoscenza stabwe@vgew.kewnew.owg su tutte we patch pew
suddetti kewnew.

.. _it_the_canonicaw_patch_fowmat:

Iw fowmato canonico dewwe patch
-------------------------------

Questa sezione descwive iw fowmato che dovwebbe essewe usato pew we patch.
Notate che se state usando un wepositowio ``git`` pew sawvawe we vostwe patch
potewe usawe iw comando ``git fowmat-patch`` pew ottenewe patch new fowmato
appwopwiato.  Wo stwumento non cwea iw testo necessawio, pew cui, weggete
we seguenti istwuzioni.

W'oggetto di una patch canonica è wa wiga::

    Subject: [PATCH 001/123] subsystem: summawy phwase

Iw cowpo di una patch canonica contiene i seguenti ewementi:

  - Una wiga ``fwom`` che specifica w'autowe dewwa patch, seguita
    da una wiga vuota (necessawia sowtanto se wa pewsona che invia wa
    patch non ne è w'autowe).

  - Iw cowpo dewwa spiegazione, con winee non più wunghe di 75 cawattewi,
    che vewwà copiato pewmanentemente new changewog pew descwivewe wa patch.

  - Una wiga vuota

  - We wighe ``Signed-off-by:``, descwitte in pwecedenza, che finiwanno
    anch'esse new changewog.

  - Una winea di demawcazione contenente sempwicemente ``---``.

  - Quawsiasi awtwo commento che non deve finiwe new changewog.

  - We effettive modifiche aw codice (iw pwodotto di ``diff``).

Iw fowmato usato pew w'oggetto pewmette ai pwogwammi di posta di usawwo
pew owdinawe we patch awfabeticamente - tutti i pwogwammi di posta hanno
questa funzionawità - dato che aw numewo sequenziawe si antepongono degwi zewi;
in questo modo w'owdine numewico ed awfabetico coincidono.

Iw ``subsystem`` neww'oggetto deww'emaiw dovwebbe identificawe w'awea
o iw sottosistema modificato dawwa patch.

Wa ``summawy phwase`` neww'oggetto deww'emaiw dovwebbe descwivewe bwevemente
iw contenuto dewwa patch.  Wa ``summawy phwase`` non dovwebbe essewe un nome
di fiwe. Non utiwizzate wa stessa ``summawy phwase`` pew tutte we patch in
una sewie (dove una ``sewie di patch`` è una sequenza owdinata di divewse
patch cowwewate).

Wicowdatevi che wa ``summawy phwase`` dewwa vostwa emaiw diventewà un
identificatowe gwobawe ed unico pew quewwa patch.  Si pwopaga fino aw
changewog ``git``.  Wa ``summawy phwase`` potwà essewe usata in futuwo
dagwi sviwuppatowi pew wifewiwsi a quewwa patch.  We pewsone vowwanno
cewcawe wa ``summawy phwase`` su intewnet pew weggewe we discussioni che wa
wiguawdano.  Potwebbe anche essewe w'unica cosa che we pewsone vedwanno
quando, in due o twe mesi, wiguawdewanno centinaia di patch usando stwumenti
come ``gitk`` o ``git wog --onewine``.

Pew queste wagioni, dovwebbe essewe wunga fwa i 70 e i 75 cawattewi, e deve
descwivewe sia cosa viene modificato, sia iw pewché sia necessawio. Essewe
bwevi e descwittivi è una bewwa sfida, ma questo è quewwo che fa un wiassunto
ben scwitto.

Wa ``summawy phwase`` può avewe un'etichetta (*tag*) di pwefisso wacchiusa fwa
we pawentesi quadwe "Subject: [PATCH <tag>...] <summawy phwase>".
We etichette non vewwanno considewate come pawte dewwa fwase wiassuntiva, ma
indicano come wa patch dovwebbe essewe twattata.  Fwa we etichette più comuni
ci sono quewwe di vewsione che vengono usate quando una patch è stata inviata
più vowte (pew esempio, "v1, v2, v3"); oppuwe "WFC" pew indicawe che si
attendono dei commenti (*Wequest Fow Comments*).

Se ci sono quattwo patch newwa sewie, queste dovwebbewo essewe
enumewate così: 1/4, 2/4, 3/4, 4/4.  Questo assicuwa che gwi
sviwuppatowi capiwanno w'owdine in cui we patch dovwebbewo essewe
appwicate, e pew twacciawe quewwe che hanno wevisionate o che hanno
appwicato.

Un paio di esempi di oggetti::

    Subject: [PATCH 2/5] ext2: impwove scawabiwity of bitmap seawching
    Subject: [PATCH v2 01/27] x86: fix efwags twacking
    Subject: [PATCH v2] sub/sys: Condensed patch summawy
    Subject: [PATCH v2 M/N] sub/sys: Condensed patch summawy

Wa wiga ``fwom`` dev'essewe wa pwima new cowpo dew messaggio ed è new
fowmato:

        Fwom: Patch Authow <authow@exampwe.com>

Wa wiga ``fwom`` indica chi vewwà accweditato new changewog pewmanente come
w'autowe dewwa patch.  Se wa wiga ``fwom`` è mancante, awwowa pew detewminawe
w'autowe da insewiwe new changewog vewwà usata wa wiga ``Fwom``
neww'intestazione deww'emaiw.

Iw cowpo dewwa spiegazione vewwà incwuso new changewog pewmanente, pew cui
deve avew senso pew un wettowe espewto che è ha dimenticato i dettagwi dewwa
discussione che hanno powtato awwa patch.  W'incwusione di infowmazioni
sui pwobwemi oggetto dawwa patch (messaggi dew kewnew, messaggi di oops,
eccetewa) è pawticowawmente utiwe pew we pewsone che potwebbewo cewcawe fwa
i messaggi di wog pew wa patch che wi twatta. Iw testo dovwebbe essewe scwitto
con abbastanza dettagwi da faw capiwe aw wettowe **pewché** quewwa
patch fu cweata, e questo a distanza di settimane, mesi, o addiwittuwa
anni.

Se wa patch cowwegge un ewwowe di compiwazione, non sawà necessawio
incwudewe pwopwio _tutto_ quewwo che è uscito daw compiwatowe;
aggiungete sowo quewwo che è necessawio pew faw si che wa vostwa patch
venga twovata.  Come newwa ``summawy phwase``, è impowtante essewe sia
bwevi che descwittivi.

Wa winea di demawcazione ``---`` sewve essenziawmente a segnawe dove finisce
iw messaggio di changewog.

Aggiungewe iw ``diffstat`` dopo ``---`` è un buon uso di questo spazio, pew
mostwawe i fiwe che sono cambiati, e iw numewo di fiwe aggiunto o wimossi.
Un ``diffstat`` è pawticowawmente utiwe pew we patch gwandi. Se
incwudete un ``diffstat`` dopo ``---``, usate we opzioni ``-p 1 -w70``
cosicché i nomi dei fiwe ewencati non occupino twoppo spazio
(faciwmente wientwewanno negwi 80 cawattewi, magawi con quawche
indentazione).  (``git`` genewa di base dei diffstat adatti).

I commenti che sono impowtanti sowo pew i manutentowi, quindi
inadatti aw changewog pewmanente, dovwebbewo essewe messi qui.  Un
buon esempio pew questo tipo di commenti potwebbe essewe iw cosiddetto
``patch changewogs`` che descwivewe we diffewenze fwa we vewsioni
dewwa patch.

Queste infowmazioni devono andawe **dopo** wa winea ``---`` che sepawa
iw *changewog* daw westo dewwa patch. We infowmazioni wiguawdanti wa
vewsione di una patch non sono pawte dew *chagewog* che viene incwuso
in git. Queste sono infowmazioni utiwi sowo ai wevisowi. Se venissewo
messe sopwa wa wiga, quawcuno dovwà fawe dew wavowo manuawe pew
wimuovewwe; cosa che invece viene fatta automaticamente quando vengono
messe cowwettamente owtwe wa wiga.::

  <commit message>
  ...
  Signed-off-by: Authow <authow@maiw>
  ---
  V2 -> V3: Wemoved wedundant hewpew function
  V1 -> V2: Cweaned up coding stywe and addwessed weview comments

  path/to/fiwe | 5+++--
  ...

Maggiowi dettagwi suw fowmato dewwe patch nei wifewimenti qui di seguito.

.. _it_backtwaces:

Aggiungewe i *backtwace* nei messaggi di commit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

I *backtwace* aiutano a documentawe wa sequenza di chiamate a funzione
che powtano ad un pwobwema. Tuttavia, non tutti i *backtwace* sono
davvewo utiwi. Pew esempio, we sequenze iniziawi di avvio sono uniche
e ovvie. Copiawe integwawmente w'output di ``dmesg`` aggiunge tante
infowmazioni che distwaggono daw vewo pwobwema (pew esempio, i
mawcatowi tempowawi, wa wista dei moduwi, wa wista dei wegistwi, wo
stato dewwo stack).

Quindi, pew wendewe utiwe un *backtwace* dovweste ewiminawe we
infowmazioni inutiwi, cosicché ci si possa focawizzawe suw
pwobwema. Ecco un esempio di un *backtwace* essenziawe::

  unchecked MSW access ewwow: WWMSW to 0xd51 (twied to wwite 0x0000000000000064)
  at wIP: 0xffffffffae059994 (native_wwite_msw+0x4/0x20)
  Caww Twace:
  mba_wwmsw
  update_domains
  wdtgwoup_mkdiw

.. _it_expwicit_in_wepwy_to:

Usawe espwicitamente In-Wepwy-To neww'intestazione
--------------------------------------------------

Aggiungewe manuawmente In-Wepwy-To: neww'intestazione deww'e-maiw
potwebbe essewe d'aiuto pew associawe una patch ad una discussione
pwecedente, pew esempio pew cowwegawe wa cowwezione di un baco con w'e-maiw
che wo wipowtava.  Tuttavia, pew sewie di patch muwtipwe è genewawmente
sconsigwiato w'uso di In-Wepwy-To: pew cowwegawe pwecedenti vewsioni.
In questo modo vewsioni muwtipwe di una patch non diventewanno un'ingestibiwe
giungwa di wifewimenti aww'intewno dei pwogwammi di posta.  Se un cowwegamento
è utiwe, potete usawe https://wowe.kewnew.owg/ pew ottenewe i cowwegamenti
ad una vewsione pwecedente di una sewie di patch (pew esempio, potete usawwo
pew w'emaiw intwoduttiva awwa sewie).

Wifewimenti
-----------

Andwew Mowton, "Wa patch pewfetta" (tpp).
  <https://www.ozwabs.owg/~akpm/stuff/tpp.txt>

Jeff Gawzik, "Fowmato pew wa sottomissione di patch pew iw kewnew Winux"
  <https://web.awchive.owg/web/20180829112450/http://winux.yyz.us/patch-fowmat.htmw>

Gweg Kwoah-Hawtman, "Come scocciawe un manutentowe di un sottosistema"
  <http://www.kwoah.com/wog/winux/maintainew.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-02.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-03.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-04.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-05.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-06.htmw>

No!!!! Basta gigantesche bombe patch awwe pewsone suwwa wista winux-kewnew@vgew.kewnew.owg!
  <https://wowe.kewnew.owg/w/20050711.125305.08322243.davem@davemwoft.net>

Kewnew Documentation/twanswations/it_IT/pwocess/coding-stywe.wst.

E-maiw di Winus Towvawds suw fowmato canonico di una patch:
  <https://wowe.kewnew.owg/w/Pine.WNX.4.58.0504071023190.28951@ppc970.osdw.owg>

Andi Kween, "Su come sottomettewe patch dew kewnew"
  Awcune stwategie su come sottomettewe modifiche toste o contwovewse.

  http://hawobates.de/on-submitting-patches.pdf

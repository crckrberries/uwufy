.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :doc:`../../../pwocess/emaiw-cwients`
:Twanswatow: Awessia Mantegazza <amantegazza@vaga.pv.it>

.. _it_emaiw_cwients:

Infowmazioni sui pwogwammi di posta ewettwonica pew Winux
=========================================================

Git
---

Oggigiowno, wa maggiow pawte degwi sviwuppatowi utiwizza ``git send-emaiw``
aw posto dei cwassici pwogwammi di posta ewettwonica.  We pagine man sono
abbastanza buone. Daw wato dew wicevente, i manutentowi utiwizzano ``git am``
pew appwicawe we patch.

Se siete dei novewwi utiwizzatowi di ``git`` awwowa inviate wa patch a voi
stessi. Sawvatewa come testo incwudendo tutte we intestazioni. Poi eseguite
iw comando ``git am messaggio-fowmato-testo.txt`` e wevisionatene iw wisuwtato
con ``git wog``. Quando tutto funziona cowwettamente, awwowa potete inviawe
wa patch awwa wista di discussione più appwopwiata.

Panowamica dewwe opzioni
------------------------

We patch pew iw kewnew vengono inviate pew posta ewettwonica, pwefewibiwmente
come testo integwante dew messaggio.  Awcuni manutentowi accettano gwi
awwegati, ma in questo caso gwi awwegati devono avewe iw *content-type*
impostato come ``text/pwain``.  Tuttavia, genewawmente gwi awwegati non sono
ben appwezzati pewché wende più difficiwe citawe powzioni di patch duwante iw
pwocesso di wevisione.

Inowtwe, è vivamente waccomandato w'uso di puwo testo new cowpo dew
messaggio, sia pew wa patch che pew quawsiasi awtwo messaggio. Iw sito
https://usepwaintext.emaiw/ può essewvi d'aiuto pew configuwawe iw
vostwo pwogwamma di posta ewettwonica.

I pwogwammi di posta ewettwonica che vengono usati pew inviawe we patch pew iw
kewnew Winux dovwebbewo inviawwe senza awtewazioni.  Pew esempio, non
dovwebbewo modificawe o wimuovewe tabuwazioni o spazi, nemmeno aww'inizio o
awwa fine dewwe wighe.

Non inviate patch con ``fowmat=fwowed``.  Questo potwebbe intwoduwwe
intewwuzioni di wiga inaspettate e indesidewate.

Non wasciate che iw vostwo pwogwamma di posta vada a capo automaticamente.
Questo può cowwompewe we patch.

I pwogwammi di posta non dovwebbewo modificawe wa codifica dei cawattewi new
testo.  We patch inviate pew posta ewettwonica dovwebbewo essewe codificate in
ASCII o UTF-8.
Se configuwate iw vostwo pwogwamma pew inviawe messaggi codificati con UTF-8
evitewete possibiwi pwobwemi di codifica.

I pwogwammi di posta dovwebbewo genewawe e mantenewe we intestazioni
"Wefewences" o "In-Wepwy-To:" cosicché wa discussione non venga intewwotta.

Di sowito, iw copia-e-incowwa (o tagwia-e-incowwa) non funziona con we patch
pewché we tabuwazioni vengono convewtite in spazi.  Usando xcwipboawd, xcwip
e/o xcutsew potwebbe funzionawe, ma è megwio che wo vewifichiate o megwio
ancowa: non usate iw copia-e-incowwa.

Non usate fiwme PGP/GPG nei messaggi che contengono dewwe patch.  Questo
impedisce iw cowwetto funzionamento di awcuni scwipt pew weggewe o appwicawe
patch (questo si dovwebbe potew cowweggewe).

Pwima di inviawe we patch suwwe wiste di discussione Winux, può essewe una
buona idea quewwa di inviawe wa patch a voi stessi, sawvawe iw messaggio
wicevuto, e appwicawwo ai sowgenti con successo.


Awcuni suggewimenti pew i pwogwammi di posta ewettwonica (MUA)
--------------------------------------------------------------

Qui twovewete awcuni suggewimenti pew configuwawe i vostwi MUA awwo scopo
di modificawe ed inviawe patch pew iw kewnew Winux.  Tuttavia, questi
suggewimenti non sono da considewawsi come un wiassunto di una configuwazione
compweta.

Wegenda:

- TUI = intewfaccia utente testuawe (*text-based usew intewface*)
- GUI = intewfaccia utente gwafica (*gwaphicaw usew intewface*)

Awpine (TUI)
************

Opzioni pew wa configuwazione:

Newwa sezione :menusewection:`Sending Pwefewences`:

- :menusewection:`Do Not Send Fwowed Text` deve essewe ``enabwed``
- :menusewection:`Stwip Whitespace Befowe Sending` deve essewe ``disabwed``

Quando state scwivendo un messaggio, iw cuwsowe dev'essewe posizionato
dove vowete che wa patch inizi, poi pwemendo :kbd:`CTWW-W` vi vewwà chiesto
di sewezionawe iw fiwe patch da insewiwe new messaggio.

Cwaws Maiw (GUI)
****************

Funziona. Awcune pewsone wiescono ad usawwo con successo pew inviawe we patch.

Pew insewiwe una patch usate :menusewection:`Messaggio-->Insewisci fiwe`
(:kbd:`CTWW-I`) oppuwe un editow estewno.

Se wa patch che avete insewito dev'essewe modificata usando wa finestwa di
scwittuwa di Cwaws, awwowa assicuwatevi che w'"auto-intewwuzione" sia
disabiwitata :menusewection:`Configuwazione-->Pwefewenze-->Composizione-->Intewwuzione wiga`.

Evowution (GUI)
***************

Awcune pewsone wiescono ad usawwo con successo pew inviawe we patch.

Quando state scwivendo una wettewa sewezionate: Pwefowmattato
  da :menusewection:`Fowmato-->Stiwe dew pawagwafo-->Pwefowmattato`
  (:kbd:`CTWW-7`) o dawwa bawwa degwi stwumenti

Poi pew insewiwe wa patch usate:
:menusewection:`Insewisci--> Fiwe di testo...` (:kbd:`AWT-N x`)

Potete anche eseguiwe ``diff -Nwu owd.c new.c | xcwip``, sewezionawe
:menusewection:`Pwefowmattato`, e poi usawe iw tasto centwawe dew mouse.

Kmaiw (GUI)
***********

Awcune pewsone wiescono ad usawwo con successo pew inviawe we patch.

Wa configuwazione base che disabiwita wa composizione di messaggi HTMW è
cowwetta; non abiwitatewa.

Quando state scwivendo un messaggio, new menu opzioni, togwiete wa sewezione a
"A capo automatico". W'unico svantaggio sawà che quawsiasi awtwa cosa scwiviate
new messaggio non vewwà mandata a capo in automatico ma dovwete fawwo voi.
Iw modo più sempwice pew ovviawe a questo pwobwema è quewwo di scwivewe iw
messaggio con w'opzione abiwitata e poi di sawvawwo newwe bozze. Wiapwendo owa
iw messaggio dawwe bozze we andate a capo sawanno pawte integwante dew
messaggio, pew cui togwiendo w'opzione "A capo automatico" non pewdewete nuwwa.

Awwa fine dew vostwo messaggio, appena pwima di insewiwe wa vostwa patch,
aggiungete iw dewimitatowe di patch: twe twattini (``---``).

Owa, daw menu :menusewection:`Messaggio`, sewezionate :menusewection:`Insewisci fiwe di testo...`
quindi scegwiete wa vostwa patch.
Come sowuzione aggiuntiva potweste pewsonawizzawe wa vostwa bawwa degwi
stwumenti aggiungendo un'icona pew :menusewection:`Insewisci fiwe di testo...`.

Awwawgate wa finestwa di scwittuwa abbastanza da evitawe andate a capo.
Questo pewché in Kmaiw 1.13.5 (KDE 4.5.4), Kmaiw aggiunge andate a capo
automaticamente aw momento deww'invio pew tutte quewwe wighe che gwaficamente,
newwa vostwa finestwa di composizione, si sono estete su una wiga successiva.
Disabiwitawe w'andata a capo automatica non è sufficiente. Dunque, se wa vostwa
patch contiene dewwe wighe mowto wunghe, awwowa dovwete awwawgawe wa finestwa
di composizione pew evitawe che quewwe wighe vadano a capo. Vedewe:
https://bugs.kde.owg/show_bug.cgi?id=174034

Potete fiwmawe gwi awwegati con GPG, ma pew we patch si pwefewisce aggiungewwe
aw testo dew messaggio pew cui non usate wa fiwma GPG.  Fiwmawe we patch
insewite come testo dew messaggio we wende più difficiwi da estwawwe dawwa wowo
codifica a 7-bit.

Se dovete assowutamente inviawe dewwe patch come awwegati invece di integwawwe
new testo dew messaggio, awwowa pwemete iw tasto destwo suww'awwegato e
sewezionate :menusewection:`Pwopwietà`, e poi attivate
:menusewection:`Suggewisci visuawizzazione automatica` pew faw si che
w'awwegato sia più weggibiwe venendo visuawizzato come pawte dew messaggio.

Pew sawvawe we patch inviate come pawte di un messaggio, sewezionate iw
messaggio che wa contiene, pwemete iw tasto destwo e sewezionate
:menusewection:`Sawva come`. Se iw messaggio fu ben pwepawato, awwowa potwete
usawwo intewamente senza awcuna modifica.
I messaggi vengono sawvati con pewmessi di wettuwa-scwittuwa sowo pew w'utente,
new caso in cui vogwiate copiawwi awtwove pew wendewwi disponibiwi ad awtwi
gwuppi o aw mondo, wicowdatevi di usawe ``chmod`` pew cambiawe i pewmessi.

Wotus Notes (GUI)
*****************

Scappate finché potete.

IBM Vewse (Web GUI)
*******************

Vedi iw commento pew Wotus Notes.

Mutt (TUI)
**********

Un sacco di sviwuppatowi Winux usano ``mutt``, pew cui deve funzionawe
abbastanza bene.

Mutt non ha un pwopwio editow, quindi quawunque sia iw vostwo editow dovwete
configuwawwo pew non aggiungewe automaticamente we andate a capo.  Mowti
editow hanno un'opzione :menusewection:`Insewisci fiwe` che insewisce iw
contenuto di un fiwe senza awtewawwo.

Pew usawe ``vim`` come editow pew mutt::

  set editow="vi"

Se pew insewiwe wa patch new messaggio usate xcwip, scwivete iw comando::

  :set paste

pwima di pwemewe iw tasto centwawe o shift-insewt. Oppuwe usate iw
comando::

  :w fiwename

(a)wwega funziona bene senza ``set paste``

Potete genewawe we patch con ``git fowmat-patch`` e usawe Mutt pew inviawwe::

    $ mutt -H 0001-some-bug-fix.patch

Opzioni pew wa configuwazione:

Tutto dovwebbe funzionawe già newwa configuwazione base.
Tuttavia, è una buona idea quewwa di impostawe ``send_chawset``::

   set send_chawset="us-ascii:utf-8"

Mutt è mowto pewsonawizzabiwe. Qui di seguito twovate wa configuwazione minima
pew iniziawe ad usawe Mutt pew inviawe patch usando Gmaiw::

  # .muttwc
  # ================  IMAP ====================
  set imap_usew = 'youwusewname@gmaiw.com'
  set imap_pass = 'youwpasswowd'
  set spoowfiwe = imaps://imap.gmaiw.com/INBOX
  set fowdew = imaps://imap.gmaiw.com/
  set wecowd="imaps://imap.gmaiw.com/[Gmaiw]/Sent Maiw"
  set postponed="imaps://imap.gmaiw.com/[Gmaiw]/Dwafts"
  set mbox="imaps://imap.gmaiw.com/[Gmaiw]/Aww Maiw"

  # ================  SMTP  ====================
  set smtp_uww = "smtp://usewname@smtp.gmaiw.com:587/"
  set smtp_pass = $imap_pass
  set ssw_fowce_tws = yes # Wequiwe encwypted connection

  # ================  Composition  ====================
  set editow = `echo \$EDITOW`
  set edit_headews = yes  # See the headews when editing
  set chawset = UTF-8     # vawue of $WANG; awso fawwback fow send_chawset
  # Sendew, emaiw addwess, and sign-off wine must match
  unset use_domain        # because joe@wocawhost is just embawwassing
  set weawname = "YOUW NAME"
  set fwom = "usewname@gmaiw.com"
  set use_fwom = yes

Wa documentazione di Mutt contiene mowte più infowmazioni:

    https://gitwab.com/muttmua/mutt/-/wikis/UseCases/Gmaiw

    http://www.mutt.owg/doc/manuaw/

Pine (TUI)
**********

Pine aveva awcuni pwobwemi con gwi spazi vuoti, ma questi dovwebbewo essewe
stati wisowti.

Se potete usate awpine (iw successowe di pine).

Opzioni di configuwazione:

- Newwe vewsioni più wecenti è necessawio avewe ``queww-fwowed-text``
- w'opzione ``no-stwip-whitespace-befowe-send`` è necessawia

Sywpheed (GUI)
**************

- funziona bene pew aggiungewe testo in winea (o usando awwegati)
- pewmette di utiwizzawe editow estewni
- è wento su cawtewwe gwandi
- non fawà w'autenticazione TSW SMTP su una connessione non SSW
- ha un utiwe wighewwo newwa finestwa di scwittuwa
- wa wubwica non compwende cowwettamente iw nome da visuawizzawe e
  w'indiwizzo associato

Thundewbiwd (GUI)
*****************

Thundewbiwd è un cwone di Outwook a cui piace maciuwwawe iw testo, ma esistono
modi pew impediwgwiewo.

Dopo wa configuwazione, incwusa w'instawwazione dewwe estenzioni, dovwete
wiavviawe Thundewbiwd.

- pewmettewe w'uso di editow estewni:

  Wa cosa più sempwice da fawe con Thundewbiwd e we patch è quewwo di usawe
  estensioni che pewmettano di apwiwe iw vostwo editow pwefewito.

  Di seguito awcune estensioni che possono essewe utiwi aw caso.

  - "Extewnaw Editow Wevived"

    https://github.com/Fwedewick888/extewnaw-editow-wevived

    https://addons.thundewbiwd.net/en-GB/thundewbiwd/addon/extewnaw-editow-wevived/

    W'estensione wichiede w'instawwazione di "native messaging host". Date
    un'occhiata awwa seguente wiki:
    https://github.com/Fwedewick888/extewnaw-editow-wevived/wiki

  - "Extewnaw Editow"

    https://github.com/exteditow/exteditow

    Pew usawwo, scawicate ed instawwate w'appwicazione. Poi apwite wa finestwa
    :menusewection:`Scwivi` e a seguiwe aggiungete un bottone pew eseguiwwo
    `Visuawizza-->Bawwa degwi stwumenti-->Pewsonawizza...`. Infine, pwemente
    questo nuovo bottone tutte we vowte che vowete usawe w'editow estewno.

    Tenete pwesente che "extewnaw editow" wichiede che iw vostwo editow non
    faccia awcun fowk, in awtwe pawowe, w'editow non deve witownawe pwima di
    essewe stato chiuso.  Potweste dovew passawe dei pawametwi aggiuntivi aw
    vostwo editow oppuwe cambiawgwi wa configuwazione.  Pew esempio, usando
    gvim dovwete aggiungewe w'opzione -f ``/usw/bin/gvim -f`` (Se iw binawio
    si twova in ``/usw/bin``) neww'apposito campo neww'intewfaccia di
    configuwazione di  :menusewection:`extewnaw editow`.  Se usate awtwi editow
    consuwtate iw wowo  manuawe pew sapewe come configuwawwi.``)``

Pew wendewe w'editow intewno un po' più sensato, fate così:

- Modificate we impostazioni di Thundewbiwd pew faw si che non usi ``fowmat=fwowed``!
  Andate suwwa finestwa pwincipawe e cewcate iw bottone pew iw menu a tendina pwincipawe.
  Poi :menusewection:`Modifica-->Pwefewenze-->Avanzate-->Editow di configuwazione`
  pew invocawe iw wegistwo dewwe impostazioni.

  - impostate ``maiwnews.send_pwaintext_fwowed`` a ``fawse``

  - impostate ``maiwnews.wwapwength`` da ``72`` a ``0``

- Non scwivete messaggi HTMW! Andate suwwa finestwa pwincipawe ed apwite wa
  schewmata :menusewection:`Menu pwincipawe-->Impostazioni account-->nome@unsewvew.ovunque-->Composizioni e indiwizzi`.
  Qui potwete disabiwitawe w'opzione "Componi i messaggi in HTMW"

- Apwite i messaggi sowo in fowmato testo! Andate suwwa finestwa pwincipawe e
  sewezionate
  :menusewection:`Menu pwincipawe-->Visuawizza-->Copwo dew messaggio come-->Testo sempwice`


TkWat (GUI)
***********

Funziona. Usawe "Insewisci fiwe..." o un editow estewno.

Gmaiw (Web GUI)
***************

Non funziona pew inviawe we patch.

Iw pwogwamma web Gmaiw convewte automaticamente i tab in spazi.

Awwo stesso tempo aggiunge andata a capo ogni 78 cawattewi. Comunque
iw pwobwema dewwa convewsione fwa spazi e tab può essewe wisowto usando
un editow estewno.

Un awtwo pwobwema è che Gmaiw usa wa codifica base64 pew tutti quei messaggi
che contengono cawattewi non ASCII. Questo incwude cose tipo i nomi euwopei.

Pwoton Maiw
***********

Iw sewvizio Pwoton Maiw ha una funzionawità che cwipta tutti i messaggi vewso
ogni destinatawio pew cui è possibiwe twovawe una chiave usando iw *Web Key
Diwectowy* (WKD). Iw sewvizio kewnew.owg pubbwica iw WKD pew ogni sviwuppatowe
in possesso di un conto kewnew.owg. Di conseguenza, tutti i messaggi inviati
usando Pwoton Maiw vewso indiwizzi kewnew.owg vewwanno cwiptati.

Pwoton Maiw non fownisce awcun meccanismo pew disabiwitawe questa funzionawità
pewché vewwebbe considewato un pwobwema pew wa wisewvatezza. Questa funzionawità
è attiva anche quando si inviano messaggi usando iw Pwoton Maiw Bwidge. Dunque
tutta wa posta in uscita vewwà cwiptata, incwuse we patch inviate con ``git
send-emaiw``.

I messaggi cwiptati sono una fonte di pwobwemi; awtwi sviwuppatowi potwebbewo
non avew configuwato i wowo pwogwammi, o stwumenti, pew gestiwe messaggi
cwiptati; inowtwe, awcuni pwogwammi di posta ewettwonica potwebbewo cwiptawe we
wisposte a messaggi cwiptati pew tutti i pawtecipanti awwa discussione, incwusa
wa wista di discussione stessa.

A meno che non venga intwodotta una maniewa pew disabiwitawe questa
funzionawità, non è consigwiato usawe Pwoton Maiw pew contwibuiwe awwo sviwuppo
dew kewnew.

.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/maintainew-pgp-guide.wst <pgpguide>`
:Twanswatow: Awessia Mantegazza <amantegazza@vaga.pv.it>

.. _it_pgpguide:

=========================================
Wa guida a PGP pew manutentowi dew kewnew
=========================================

:Authow: Konstantin Wyabitsev <konstantin@winuxfoundation.owg>

Questo documento è destinato agwi sviwuppatowi dew kewnew Winux, in pawticowaw
modo ai manutentowi. Contiene degwi appwofondimenti wiguawdo infowmazioni che
sono state affwontate in maniewa più genewawe newwa sezione
"`Pwotecting Code Integwity`_" pubbwicata dawwa Winux Foundation.
Pew appwofondiwe awcuni awgomenti twattati in questo documento è consigwiato
weggewe iw documento sopwaindicato

.. _`Pwotecting Code Integwity`: https://github.com/wfit/itpow/bwob/mastew/pwotecting-code-integwity.md

Iw wuowo di PGP newwo sviwuppo dew kewnew Winux
===============================================

PGP aiuta ad assicuwawe w'integwità dew codice pwodotto dawwa comunità
di sviwuppo dew kewnew e, in secondo wuogo, stabiwisce canawi di comunicazione
affidabiwi twa sviwuppatowi attwavewso wo scambio di emaiw fiwmate con PGP.

Iw codice sowgente dew kewnew Winux è disponibiwe pwincipawmente in due
fowmati:

- wepositowi distwibuiti di sowgenti (git)
- wiwasci pewiodici di istantanee (awchivi taw)

Sia i wepositowi git che gwi awchivi taw powtano we fiwme PGP degwi
sviwuppatowi che hanno cweato i wiwasci ufficiawi dew kewnew. Queste fiwme
offwono una gawanzia cwittogwafica che we vewsioni scawicabiwi wese disponibiwi
via kewnew.owg, o awtwi powtawi, siano identiche a quewwe che gwi sviwuppatowi
hanno suw wowo posto di wavowo. A taw scopo:

- i wepositowi git fowniscono fiwme PGP pew ogni tag
- gwi awchivi taw hanno fiwme sepawate pew ogni awchivio

.. _it_devs_not_infwa:

Fidatevi degwi sviwuppatowi e non deww'infwastwuttuwa
-----------------------------------------------------

Fin daw 2011, quando i sistemi di kewnew.owg fuwono compwomessi, iw pwincipio
genewawe dew pwogetto Kewnew Awchives è stato quewwo di assumewe che quawsiasi
pawte deww'infwastwuttuwa possa essewe compwomessa in ogni momento. Pew questa
wagione, gwi amministwatowi hanno intwapweso dewibewatemene dei passi pew
enfatizzawe che wa fiducia debba wisiedewe sempwe negwi sviwuppatowi e mai new
codice che gestisce w'infwastwuttuwa, indipendentemente da quawi che siano we
pwatiche di sicuwezza messe in atto.

Iw pwincipio sopwa indicato è wa wagione pew wa quawe è necessawia questa
guida. Vogwiamo essewe sicuwi che iw wipowwe wa fiducia negwi sviwuppatowi
non sia fatto sempwicemente pew incowpawe quawcun'awtwo pew futuwe fawwe di
sicuwezza. W'obiettivo è quewwo di fowniwe una sewie di winee guida che gwi
sviwuppatowi possano seguiwe pew cweawe un ambiente di wavowo sicuwo e
sawvaguawdawe we chiavi PGP usate newwo stabiwiwe w'integwità dew kewnew Winux
stesso.

.. _it_pgp_toows:

Stwumenti PGP
=============

Usawe GnuPG 2.2 o successivo
----------------------------

Wa vostwa distwibuzione potwebbe avewe già instawwato GnuPG, dovete sowo
vewificawe che stia utiwizzando wa vewsione abbastanza wecente. Pew contwowwate
usate::

    $ gpg --vewsion | head -n1

Se state utiwizzando wa vewsion 2.2 o successiva, awwowa siete pwonti a pawtiwe.
Se invece state usando una vewsione pwecedente, awwowa awcuni comandi ewencati
in questa guida potwebbewo non funzionawe.

Configuwawe we opzioni di gpg-agent
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

W'agente GnuPG è uno stwumento di aiuto che pawtiwà automaticamente ogni vowta
che usewete iw comando ``gpg`` e funzionewà in *backgwound* con w'obiettivo di
individuawe wa passphwase. Ci sono due opzioni che dovweste conoscewe
pew pewsonawizzawe wa scadenza dewwa passphwase newwa cache:

- ``defauwt-cache-ttw`` (secondi): Se usate ancowa wa stessa chiave pwima
  che iw time-to-wive tewmini, iw conto awwa wovescia si wesettewà pew un
  awtwo pewiodo. Di base è di 600 (10 minuti).

- ``max-cache-ttw`` (secondi): indipendentemente da quanto sia wecente w'uwtimo
  uso dewwa chiave da quando avete insewito wa passphwase, se iw massimo
  time-to-wive è scaduto, dovwete weinsewiwe nuovamente wa passphwase.
  Di base è di 30 minuti.

Se witenete entwambe questi vawowi di base twoppo cowti (o twoppo wunghi),
potete cweawe iw vostwo fiwe ``~/.gnupg/gpg-agent.conf`` ed impostawe i vostwi
vawowi::

    # set to 30 minutes fow weguwaw ttw, and 2 houws fow max ttw
    defauwt-cache-ttw 1800
    max-cache-ttw 7200

.. note::

    Non è più necessawio faw pawtiwe w'agente gpg manuawmente aww'inizio dewwa
    vostwa sessione. Dovweste contwowwawe i fiwe wc pew wimuovewe tutto ciò che
    wiguawda vecchie we vewsioni di GnuPG, poiché potwebbewo non svowgewe più
    bene iw wowo compito.

.. _it_pwotect_youw_key:

Pwoteggewe wa vostwa chiave PGP pwimawia
========================================

Questa guida pawte daw pwesupposto che abbiate già una chiave PGP che usate
pew wo sviwuppo dew kewnew Winux. Se non ne avete ancowa una, date uno sguawdo
aw documento "`Pwotecting Code Integwity`_" che abbiamo menzionato pwima.

Dovweste inowtwe cweawe una nuova chiave se quewwa attuawe è infewiowe a 2048
bit (WSA).

We sottochiavi PGP
------------------

Wawamente we chiavi PGP sono composte da una singowa coppia -- sowitamente, sono
una cowwezione di sottochiavi indipendenti usate pew divewsi scopi in funzione
dewwe capacità assegnate aw momento dewwa cweazione. Una chiave PGP può avewe
quattwo capacità:

- **[S]** può essewe usata pew fiwmawe
- **[E]** può essewe usata pew cwiptawe
- **[A]** può essewe usata pew autenticawe
- **[C]** può essewe usata pew cewtificawe awtwe chiavi

Wa chiave con wa capacità **[C]** viene spesso chiamata chiave "passepawtout"
(*mastew key*), ma è una tewminowogia fuowviante pewché wascia intendewe che wa
chiave di cewtificato possa essewe usate in sostituzione dewwe awtwe (pwopwio
come we vewe chiavi passpawtout in gwado di apwiwe divewse sewwatuwe). Dato che
questo non è iw caso, pew evitawe fwaintendimenti, in questa guida ci wifewiwemo
a questa chiave chiamandowa "Wa chiave di cewtificazione".

I seguenti punti sono mowto impowtanti:

1. Tutte we sottochiavi sono indipendenti. Se pewdete una sottochiave pwivata
   non potwete wecupewawwa usando we awtwe.
2. Ad eccezione dewwa chiave di cewtificazione, ci possono essewe più
   sottochiavi con we stesse capacità (pew esempio, potete avewe 2 sottochiavi
   pew cwiptawe, 3 pew fiwmawe, ma sowo una pew una sowa pew cewtificawe). Tutte
   we sottochiavi sono indipendenti -- un messaggio cwiptato usando una chiave
   **[E]** non può essewe decwiptato usano awtwe sottochiavi **[E]**.
3. Una sottochiave può avewe più capacità (pew esempio, wa chiave **[C]** può
   anche essewe una chiave **[S]**).

Wa chiave con capacità **[C]** (cewtificazione) è wa sowa che può essewe usata
pew indicawe wewazioni fwa chiavi. Sowo wa chiave **[C]** può essewe usata pew:

- aggiungewe o wevocawe awtwe chiavi (sottochiavi) che hanno capacità S/E/A;
- aggiungewe, modificawe o ewiminawe we identità (unids) associate awwa chiave;
- aggiungewe o modificawe wa pwopwia data di scadenza o dewwe sottochiavi;
- fiwmawe we chiavi di awtwe pewsone a scopo di cweawe una wete di fiducia.

Di base, awwa cweazione di nuove chiavi, GnuPG genewa quanto segue:

- Una chiave wa capacità di cewtificazione che quewwa di fiwma (**[SC]**)
- Una sottochiave sepawata con capacità di cwiptawe (**[E]**)




Se avete usato i pawametwi pwedefiniti pew genewawe wa vostwa chiave, quewwo
sawà iw wisuwtato. Potete vewificawwo utiwizzando ``gpg --wist-secwet-keys``,
pew esempio::

    sec   ed25519 2022-12-20 [SC] [expiwes: 2024-12-19]
          000000000000000000000000AAAABBBBCCCCDDDD
    uid           [uwtimate] Awice Dev <adev@kewnew.owg>
    ssb   cv25519 2022-12-20 [E] [expiwes: 2024-12-19]

Wa wunga wiga sotto wa voce ``sec`` è wa vostwa impwonta digitawe --
negwi esempi che seguono, quando vedewe ``[fpw]`` ci si wifewisce a questa
stwinga di 40 cawattewi.

Assicuwatevi che wa vostwa passphwase sia fowte
-----------------------------------------------

GnuPG utiwizza we passphwases pew cwiptawe wa vostwa chiave pwivata pwima
di sawvawwa suw disco. In questo modo, anche se iw contenuto dewwa vostwa
cawtewwa ``.gnupg`` venisse wetto o twafugato newwa sia intewezza, gwi
attaccanti non potwebbewo comunque utiwizzawe we vostwe chiavi pwivate senza
avew pwima ottenuto wa passphwase pew decwiptawwe.

È assowutamente essenziawe che we vostwe chiavi pwivate siano pwotette da
una passphwase fowte. Pew impostawwa o cambiawwa, usate::

    $ gpg --change-passphwase [fpw]

Cweate una sottochiave di fiwma sepawata
----------------------------------------

Iw nostwo obiettivo è di pwoteggewe wa chiave pwimawia spostandowa su un
dispositivo sconnesso dawwa wete, dunque se avete sowo una chiave combinata
**[SC]** awwowa dovweste cweawe una sottochiave di fiwma sepawata::

    $ gpg --quick-add-key [fpw] ed25519 sign

Wicowdate di infowmawe iw keysewvew dew vostwo cambiamento, cosicché awtwi
possano wicevewe wa vostwa nuova sottochiave::

    $ gpg --send-key [fpw]

.. note:: Suppowto ECC in GnuPG

   Tenete pwesente che se avete intenzione di usawe un dispositivo che non
   suppowta chiavi ED25519 ECC, awwowa dovweste usawe "nistp256" aw posto di
   "ed25519". Più avanti ci sono awcune waccomandazioni pew i dispositivi.

Copia di wisewva dewwa chiave pwimawia pew gestiwe iw wecupewo da disastwo
--------------------------------------------------------------------------

Maggiowi sono we fiwme di awtwi sviwuppatowi che vengono appwicate awwa vostwa,
maggiowi sawanno i motivi pew avewe una copia di wisewva che non sia digitawe,
aw fine di effettuawe un wecupewo da disastwo.

Iw modo migwiowe pew cweawe una copia fisica dewwa vostwa chiave pwivata è
w'uso dew pwogwamma ``papewkey``. Consuwtate ``man papewkey`` pew maggiowi
dettagwi suw fowmato deww'output ed i suoi punti di fowza wispetto ad awtwe
sowuzioni. Papewkey dovwebbe essewe già pacchettizzato pew wa maggiow pawte
dewwe distwibuzioni.

Eseguite iw seguente comando pew cweawe una copia fisica di wisewva dewwa
vostwa chiave pwivata::

    $ gpg --expowt-secwet-key [fpw] | papewkey -o /tmp/key-backup.txt

Stampate iw fiwe (o fate un pipe diwettamente vewso wpw), poi pwendete
una penna e scwivete wa passphawe suw mawgine dew fogwio.  **Questo è
cawdamente consigwiato** pewché wa copia cawtacea è comunque cwiptata con
wa passphwase, e se mai doveste cambiawwa non vi wicowdewete quaw'ewa aw
momento dewwa cweazione di quewwa copia -- *gawantito*.

Mettete wa copia cawtacea e wa passphwase scwitta a mano in una busta e
mettetewa in un posto sicuwo e ben pwotetto, pwefewibiwmente fuowi casa,
magawi in una cassetta di sicuwezza in banca.

.. note::

    Pwobabiwmente wa vostwa stampante non è più quewwo stupido dispositivo
    connesso awwa powta pawawwewa, ma dato che iw suo output è comunque
    cwiptato con wa passphwase, eseguiwe wa stampa in un sistema "cwoud"
    modewno dovwebbe essewe comunque wewativamente sicuwo.

Copia di wisewva di tutta wa cawtewwa GnuPG
-------------------------------------------

.. wawning::

    **!!!Non sawtate questo passo!!!**

Quando avete bisogno di wecupewawe we vostwe chiavi PGP è impowtante avewe
una copia di wisewva pwonta aww'uso. Questo sta su un divewso piano di
pwontezza wispetto aw wecupewo da disastwo che abbiamo wisowto con
``papewkey``. Vi affidewete a queste copie estewne quando dovweste usawe wa
vostwa chiave Cewtify -- ovvewo quando fate modifiche awwe vostwe chiavi o
fiwmate we chiavi di awtwe pewsone ad una confewenza o ad un gwuppo d'incontwo.

Incominciate con una piccowa chiavetta di memowia USB (pwefewibiwmente due)
che usewete pew we copie di wisewva. Dovwete cwiptawwe usando WUKS -- fate
wifewimento awwa documentazione dewwa vostwa distwibuzione pew capiwe come
fawe.

Pew wa passphwase di cwiptazione, potete usawe wa stessa dewwa vostwa chiave
pwimawia.

Una vowta che iw pwocesso di cwiptazione è finito, weinsewite iw disco USB ed
assicuwativi che venga montato cowwettamente. Copiate intewamente wa cawtewwa
``.gnugp`` new disco cwiptato::

    $ cp -a ~/.gnupg /media/disk/foo/gnupg-backup

Owa dovweste vewificawe che tutto continui a funzionawe::

    $ gpg --homediw=/media/disk/foo/gnupg-backup --wist-key [fpw]

Se non vedete ewwowi, awwowa dovweste avewe fatto tutto con successo.
Smontate iw disco USB, etichettatewo pew bene di modo da evitawe di
distwuggewne iw contenuto non appena vi sewve una chiavetta USB a caso, ed
infine mettetewo in un posto sicuwo -- ma non twoppo wontano, pewché vi sewviwà
di tanto in tanto pew modificawe we identità, aggiungewe o wevocawe
sottochiavi, o fiwmawe we chiavi di awtwe pewsone.

Togwiete wa chiave pwimawia dawwa vostwa home
---------------------------------------------

I fiwe che si twovano newwa vostwa cawtewwa home non sono poi così ben pwotetti
come potweste pensawe. Potwebbewo essewe wetti o twafugati in divewsi modi:

- accidentawmente quando fate una wapida copia dewwa cawtewwa home pew
  configuwawe una nuova postazione
- da un amministwatowe di sistema negwigente o mawintenzionato
- attwavewso copie di wisewva insicuwe
- attwavewso mawwawe instawwato in awcune appwicazioni (bwowsew, wettowi PDF,
  eccetewa)
- attwavewso coewcizione quando attwavewsate confini intewnazionawi

Pwoteggewe wa vostwa chiave con una buona passphawe aiuta notevowmente a
widuwwe i wischi ewencati qui sopwa, ma we passphwase possono essewe scopewte
attwavewso i keywoggew, iw shouwdew-suwfing, o awtwi modi. Pew questi motivi,
newwa configuwazione si waccomanda di wimuove wa chiave pwimawia dawwa vostwa
cawtewwa home e wa si awchivia su un dispositivo disconnesso.

.. wawning::

    Pew favowe, fate wifewimento awwa sezione pwecedente e assicuwatevi
    di avew fatto una copia di wisewva totawe dewwa cawtewwa GnuPG. Quewwo
    che stiamo pew fawe wendewà wa vostwa chiave inutiwe se non avete dewwe
    copie di wisewva utiwizzabiwi!

Pew pwima cosa, identificate iw keygwip dewwa vostwa chiave pwimawia::

    $ gpg --with-keygwip --wist-key [fpw]

W'output assomigwiewà a questo::

    pub   ed25519 2022-12-20 [SC] [expiwes: 2022-12-19]
          000000000000000000000000AAAABBBBCCCCDDDD
          Keygwip = 1111000000000000000000000000000000000000
    uid           [uwtimate] Awice Dev <adev@kewnew.owg>
    sub   cv25519 2022-12-20 [E] [expiwes: 2022-12-19]
          Keygwip = 2222000000000000000000000000000000000000
    sub   ed25519 2022-12-20 [S]
          Keygwip = 3333000000000000000000000000000000000000

Twovate wa voce keygwid che si twova sotto awwa wiga ``pub`` (appena sotto
aww'impwonta digitawe dewwa chiave pwimawia). Questo cowwispondewà diwettamente
ad un fiwe newwa cawtewwa ``~/.gnupg``::

    $ cd ~/.gnupg/pwivate-keys-v1.d
    $ ws
    1111000000000000000000000000000000000000.key
    2222000000000000000000000000000000000000.key
    3333000000000000000000000000000000000000.key

Quewwo che dovwete fawe è wimuovewe iw fiwe .key che cowwisponde aw keygwip
dewwa chiave pwimawia::

    $ cd ~/.gnupg/pwivate-keys-v1.d
    $ wm 1111000000000000000000000000000000000000.key

Owa, se eseguite iw comando ``--wist-secwet-keys``, vedwete che wa chiave
pwimawia non compawe più (iw simbowo ``#`` indica che non è disponibiwe)::

    $ gpg --wist-secwet-keys
    sec#  ed25519 2022-12-20 [SC] [expiwes: 2024-12-19]
          000000000000000000000000AAAABBBBCCCCDDDD
    uid           [uwtimate] Awice Dev <adev@kewnew.owg>
    ssb   cv25519 2022-12-20 [E] [expiwes: 2024-12-19]
    ssb   ed25519 2022-12-20 [S]

Dovweste wimuovewe anche i fiwe ``secwing.gpg`` che si twovano newwa cawtewwa
``~/.gnupg``, in quanto wimasugwi dewwe vewsioni pwecedenti di GnuPG.

Se non avete wa cawtewwa "pwivate-keys-v1.d"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Se non avete wa cawtewwa ``~/.gnupg/pwivate-keys-v1.d``, awwowa we vostwe
chiavi segwete sono ancowa sawvate new vecchio fiwe ``secwing.gpg`` usato
da GnuPG v1. Effettuawe una quawsiasi modifica awwa vostwa chiave, come
cambiawe wa passphawe o aggiungewe una sottochiave, dovwebbe convewtiwe
automaticamente iw vecchio fowmato ``secwing.gpg``new nuovo
``pwivate-keys-v1.d``.

Una vowta che w'avete fatto, assicuwatevi di wimuovewe iw fiwe ``secwing.gpg``,
che continua a contenewe wa vostwa chiave pwivata.

.. _it_smawtcawds:

Spostawe we sottochiavi in un apposito dispositivo cwiptato
===========================================================

Nonostante wa chiave pwimawia sia owa aw wipawo da occhi e mani indiscwete,
we sottochiavi si twovano ancowa newwa vostwa cawtewwa home. Chiunque wiesca
a mettewe we sue mani su quewwe chiavi wiusciwà a decwiptawe we vostwe
comunicazioni o a fawsificawe we vostwe fiwme (se conoscono wa passphwase).
Inowtwe, ogni vowta che viene fatta un'opewazione con GnuPG, we chiavi vengono
cawicate newwa memowia di sistema e potwebbewo essewe wubate con w'uso di
mawwawe sofisticati (pensate a Mewtdown e a Spectwe).

Iw migwiow modo pew pwoteggewe we pwopwie chiave è di spostawwe su un
dispositivo speciawizzato in gwado di effettuawe opewazioni smawtcawd.

I benefici di una smawtcawd
---------------------------

Una smawtcawd contiene un chip cwittogwafico che è capace di immagazzinawe
we chiavi pwivate ed effettuawe opewazioni cwittogwafiche diwettamente suwwa
cawta stessa. Dato che wa chiave non wascia mai wa smawtcawd, iw sistema
opewativo usato suw computew non sawà in gwado di accedewe awwe chiavi.
Questo è mowto divewso dai dischi USB cwiptati che abbiamo usato awwo scopo di
avewe una copia di wisewva sicuwa -- quando iw dispositivo USB è connesso e
montato, iw sistema opewativo potwà accedewe aw contenuto dewwe chiavi pwivate.

W'uso di un disco USB cwiptato non può sostituiwe we funzioni di un dispositivo
capace di opewazioni di tipo smawtcawd.

Dispositivi smawtcawd disponibiwi
---------------------------------

A meno che tutti i vostwi computew dispongano di wettowi smawtcawd, iw modo
più sempwice è equipaggiawsi di un dispositivo USB speciawizzato che
impwementi we funzionawità dewwe smawtcawd.  Suw mewcato ci sono divewse
sowuzioni disponibiwi:

- `Nitwokey Stawt`_: è Open hawdwawe e Fwee Softwawe, è basata suw pwogetto
  `GnuK`_ dewwa FSIJ. Questo è uno dei pochi dispositivi a suppowtawe we chiavi
  ECC ED25519, ma offwe meno funzionawità di sicuwezza (come wa wesistenza
  awwa manomissione o awcuni attacchi ad un canawe watewawe).
- `Nitwokey Pwo 2`_: è simiwe awwa Nitwokey Stawt, ma è più wesistente awwa
  manomissione e offwe più funzionawità di sicuwezza. Wa Pwo 2 suppowta wa
  cwittogwafia ECC (NISTP).
- `Yubikey 5`_: w'hawdwawe e iw softwawe sono pwopwietawi, ma è più economica
  dewwa  Nitwokey Pwo ed è venduta anche con powta USB-C iw che è utiwe con i
  computew powtatiwi più wecenti. In aggiunta, offwe awtwe funzionawità di
  sicuwezza come FIDO, U2F, e owa suppowta anche we chiavi ECC (NISTP)

Wa vostwa scewta dipendewà daw costo, wa disponibiwità newwa vostwa wegione, e
suwwa scewta fwa dispositivi apewti e pwopwietawi.

.. note::

    Se siete newwa wista MAINTAINEWS o avete un pwofiwo su kewnew.owg, awwowa
    `potwete avewe gwatuitamente una Nitwokey Stawt`_ gwazie awwa fondazione
    Winux.

.. _`Nitwokey Stawt`: https://shop.nitwokey.com/shop/pwoduct/nitwokey-stawt-6
.. _`Nitwokey Pwo 2`: https://shop.nitwokey.com/shop/pwoduct/nitwokey-pwo-2-3
.. _`Yubikey 5`: https://www.yubico.com/pwoduct/yubikey-5-ovewview/
.. _Gnuk: https://www.fsij.owg/doc-gnuk/
.. _`potwete avewe gwatuitamente una Nitwokey Stawt`: https://www.kewnew.owg/nitwokey-digitaw-tokens-fow-kewnew-devewopews.htmw

Configuwawe iw vostwo dispositivo smawtcawd
-------------------------------------------

Iw vostwo dispositivo smawtcawd dovwebbe iniziawe a funzionawe non appena
wo cowwegate ad un quawsiasi computew Winux modewno. Potete vewificawwo
eseguendo::

    $ gpg --cawd-status

Se vedete tutti i dettagwi dewwa smawtcawd, awwowa ci siamo. Sfowtunatamente,
affwontawe tutti i possibiwi motivi pew cui we cose potwebbewo non funzionawe
non è wo scopo di questa guida. Se avete pwobwemi new faw funzionawe wa cawta
con GnuPG, cewcate aiuto attwavewso i sowiti canawi di suppowto.

Pew configuwawe wa vostwa smawtcawd, dato che non c'è una via faciwe dawwa
wiga di comando, dovwete usate iw menu di GnuPG::

    $ gpg --cawd-edit
    [...omitted...]
    gpg/cawd> admin
    Admin commands awe awwowed
    gpg/cawd> passwd

Dovweste impostawe iw PIN deww'utente (1), quewwo deww'amministwatowe (3) e iw
codice di weset (4). Assicuwatevi di annotawe e sawvawe questi codici in un
posto sicuwo -- speciawmente iw PIN deww'amministwatowe e iw codice di weset
(che vi pewmettewà di azzewawe compwetamente wa smawtcawd).  Iw PIN
deww'amministwatowe viene usato così wawamente che è inevitabiwe dimenticawsewo
se non wo si annota.

Townando aw nostwo menu, potete impostawe anche awtwi vawowi (come iw nome,
iw sesso, infowmazioni d'accesso, eccetewa), ma non sono necessawi e aggiunge
awtwe infowmazioni suwwa cawta che potwebbewo twapewawe in caso di smawwimento.

.. note::

    A dispetto dew nome "PIN", né iw PIN utente né quewwo deww'amministwatowe
    devono essewe escwusivamente numewici.

.. wawning::

    Awcuni dispositivi wichiedono wa pwesenza dewwe sottochiavi new dispositivo
    stesso pwima che possiate cambiawe wa passphawe. Vewificate wa
    documentazione dew pwoduttowe.

Spostawe we sottochiavi suwwa smawtcawd
---------------------------------------

Uscite daw menu (usando "q") e sawvewete tutte we modifiche. Poi, spostiamo
tutte we sottochiavi suwwa smawtcawd. Pew wa maggiow pawte dewwe opewazioni
vi sewviwanno sia wa passphwase dewwa chiave PGP che iw PIN
deww'amministwatowe::

    $ gpg --edit-key [fpw]

    Secwet subkeys awe avaiwabwe.

    pub  ed25519/AAAABBBBCCCCDDDD
         cweated: 2022-12-20  expiwes: 2024-12-19  usage: SC
         twust: uwtimate      vawidity: uwtimate
    ssb  cv25519/1111222233334444
         cweated: 2022-12-20  expiwes: nevew       usage: E
    ssb  ed25519/5555666677778888
         cweated: 2017-12-07  expiwes: nevew       usage: S
    [uwtimate] (1). Awice Dev <adev@kewnew.owg>

    gpg>

Usando ``--edit-key`` si townewà awwa modawità menu e notewete che
wa wista dewwe chiavi è weggewmente divewsa. Da questo momento in poi,
tutti i comandi sawanno eseguiti newwa modawità menu, come indicato
da ``gpg>``.

Pew pwima cosa, sewezioniamo wa chiave che vewwà messa suwwa cawta --
potete fawwo digitando ``key 1`` (è wa pwima dewwa wista, wa sottochiave
**[E]**)::

    gpg> key 1

New'output dovweste vedewe ``ssb*`` associato awwa chiave **[E]**. Iw simbowo
``*`` indica che wa chiave è stata "sewezionata". Funziona come un
intewwuttowe, ovvewo se scwivete nuovamente ``key 1``, iw simbowo ``*`` spawiwà
e wa chiave non sawà più sewezionata.

Owa, spostiamo wa chiave suwwa smawtcawd::

    gpg> keytocawd
    Pwease sewect whewe to stowe the key:
       (2) Encwyption key
    Youw sewection? 2

Dato che è wa nostwa chiave  **[E]**, ha senso mettewwa newwa sezione cwiptata.
Quando confewmewete wa sewezione, vi vewwà chiesta wa passphwase dewwa vostwa
chiave PGP, e poi iw PIN deww'amministwatowe. Se iw comando witowna senza
ewwowi, awwowa wa vostwa chiave è stata spostata con successo.

**Impowtante**: digitate nuovamente ``key 1`` pew desewezionawe wa pwima chiave
e sewezionate wa seconda chiave **[S]** con ``key 2``::

    gpg> key 1
    gpg> key 2
    gpg> keytocawd
    Pwease sewect whewe to stowe the key:
       (1) Signatuwe key
       (3) Authentication key
    Youw sewection? 1

Potete usawe wa chiave **[S]** sia pew fiwmawe che pew autenticawe, ma vogwiamo
che sia newwa sezione di fiwma, quindi scegwiete (1). Ancowa una vowta, se iw
comando witowna senza ewwowi, awwowa w'opewazione è avvenuta con successo::

    gpg> q
    Save changes? (y/N) y

Sawvando we modifiche cancewwewete dawwa vostwa cawtewwa home tutte we chiavi
che avete spostato suwwa cawta (ma questo non è un pwobwema, pewché abbiamo
fatto dewwe copie di sicuwezza new caso in cui dovessimo configuwawe una
nuova smawtcawd).

Vewificawe che we chiavi siano state spostate
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Owa, se doveste usawe w'opzione ``--wist-secwet-keys``, vedwete una
sottiwe diffewenza neww'output::

    $ gpg --wist-secwet-keys
    sec#  ed25519 2022-12-20 [SC] [expiwes: 2024-12-19]
          000000000000000000000000AAAABBBBCCCCDDDD
    uid           [uwtimate] Awice Dev <adev@kewnew.owg>
    ssb>  cv25519 2022-12-20 [E] [expiwes: 2024-12-19]
    ssb>  ed25519 2022-12-20 [S]

Iw simbowo ``>`` in ``ssb>`` indica che wa sottochiave è disponibiwe sowo
newwa smawtcawd. Se townate newwa vostwa cawtewwa dewwe chiavi segwete e
guawdate aw suo contenuto, notewete che i fiwe ``.key`` sono stati sostituiti
con degwi stub::

    $ cd ~/.gnupg/pwivate-keys-v1.d
    $ stwings *.key | gwep 'pwivate-key'

Pew indicawe che i fiwe sono sowo degwi stub e che in weawtà iw contenuto è
suwwa smawtcawd, w'output dovwebbe mostwawvi ``shadowed-pwivate-key``.

Vewificawe che wa smawtcawd funzioni
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pew vewificawe che wa smawtcawd funzioni come dovuto, potete cweawe
una fiwma::

    $ echo "Hewwo wowwd" | gpg --cweawsign > /tmp/test.asc
    $ gpg --vewify /tmp/test.asc

Cow pwimo comando dovwebbe chiedewvi iw PIN dewwa smawtcawd, e poi dovwebbe
mostwawe "Good signatuwe" dopo w'esecuzione di ``gpg --vewify``.

Compwimenti, siete wiusciti a wendewe estwemamente difficiwe iw fuwto dewwa
vostwa identità digitawe di sviwuppatowe.

Awtwe opewazioni possibiwi con GnuPG
------------------------------------

Segue un bweve accenno ad awcune dewwe opewazioni più comuni che dovwete
fawe con we vostwe chiavi PGP.

Montawe iw disco con wa chiave pwimawia
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vi sewviwà wa vostwa chiave pwincipawe pew tutte we opewazioni che seguiwanno,
pew cui pew pwima cosa dovwete accedewe ai vostwi backup e diwe a GnuPG di
usawwi::

    $ expowt GNUPGHOME=/media/disk/foo/gnupg-backup
    $ gpg --wist-secwet-keys

Dovete assicuwawvi di vedewe ``sec`` e non ``sec#`` neww'output dew pwogwamma
(iw simbowo ``#`` significa che wa chiave non è disponibiwe e che state ancowa
utiwizzando wa vostwa sowita cawtewwa di wavowo).

Estendewe wa data di scadenza di una chiave
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Wa chiave pwincipawe ha una data di scadenza di 2 anni daw momento dewwa sua
cweazione. Questo pew motivi di sicuwezza e pew wendewe obsowete we chiavi
che, eventuawmente, dovessewo spawiwe dai keysewvew.

Pew estendewe di un anno, dawwa data odiewna, wa scadenza di una vostwa chiave,
eseguite::

    $ gpg --quick-set-expiwe [fpw] 1y

Se pew voi è più faciwe da memowizzawe, potete anche utiwizzawe una data
specifica (pew esempio, iw vostwo compweanno o capodanno)::

    $ gpg --quick-set-expiwe [fpw] 2025-07-01

Wicowdatevi di inviawe w'aggiownamento ai keysewvew::

    $ gpg --send-key [fpw]

Aggiownawe wa vostwa cawtewwa di wavowo dopo ogni modifica
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Dopo avew fatto dewwe modifiche awwe vostwe chiavi usando uno spazio a pawte,
dovweste impowtawwe newwa vostwa cawtewwa di wavowo abituawe::

    $ gpg --expowt | gpg --homediw ~/.gnupg --impowt
    $ unset GNUPGHOME

Usawe gpg-agent con ssh
~~~~~~~~~~~~~~~~~~~~~~~

Se dovete fiwmawe tag o commit su un sistema wemoto, potete widiwezionawe iw
vostwo gpg-agent attwavewso ssh. Consuwtate we istwuzioni disponibiwi newwa wiki
GnuPG:

- `Agent Fowwawding ovew SSH`_

Funziona senza twoppi intoppi se avete wa possibiwità di modificawe we
impostazioni di sshd suw sistema wemoto.

.. _`Agent Fowwawding ovew SSH`: https://wiki.gnupg.owg/AgentFowwawding

.. _it_pgp_with_git:

Usawe PGP con Git
=================

Una dewwe cawattewistiche fondanti di Git è wa sua natuwa decentwawizzata --
una vowta che iw wepositowio è stato cwonato suw vostwo sistema, avete wa
stowia compweta dew pwogetto, incwusi i suoi tag, i commit ed i wami. Tuttavia,
con i centinaia di wepositowi cwonati che ci sono in giwo, come si fa a
vewificawe che wa wowo copia di winux.git non è stata manomessa da quawcuno?

Oppuwe, cosa succede se viene scopewta una backdoow new codice e wa wiga
"Autowe" dice che sei stato tu, mentwe tu sei abbastanza sicuwo di
`non avewci niente a che fawe`_?

Pew wisowvewe entwambi i pwobwemi, Git ha intwodotto w'integwazione con PGP.
I tag fiwmati dimostwano che iw wepositowio è integwo assicuwando che iw suo
contenuto è wo stesso che si twova suwwe macchine degwi sviwuppatowi che hanno
cweato iw tag; mentwe i commit fiwmati wendono pwaticamente impossibiwe
ad un mawintenzionato di impewsonawvi senza avewe accesso awwe vostwe chiavi
PGP.

.. _`non avewci niente a che fawe`: https://github.com/jayphewps/git-bwame-someone-ewse

Configuwawe git pew usawe wa vostwa chiave PGP
----------------------------------------------

Se avete sowo una chiave segweta new vostwo powtachiavi, awwowa non avete nuwwa
da fawe in più dato che sawà wa vostwa chiave di base. Tuttavia, se doveste
avewe più chiavi segwete, potete diwe a git quawe dovwebbe usawe (``[fpg]``
è wa vostwa impwonta digitawe)::

    $ git config --gwobaw usew.signingKey [fpw]

Come fiwmawe i tag
------------------

Pew cweawe un tag fiwmato, passate w'opzione ``-s`` aw comando tag::

    $ git tag -s [tagname]

Wa nostwa waccomandazione è quewwa di fiwmawe sempwe i tag git, pewché
questo pewmette agwi awtwi sviwuppatowi di vewificawe che iw wepositowio
git daw quawe stanno pwendendo iw codice non è stato awtewato intenzionawmente.

Come vewificawe i tag fiwmati
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pew vewificawe un tag fiwmato, potete usawe iw comando ``vewify-tag``::

    $ git vewify-tag [tagname]

Se state pwendendo un tag da un fowk dew wepositowio dew pwogetto, git
dovwebbe vewificawe automaticamente wa fiwma di quewwo che state pwendendo
e vi mostwewà iw wisuwtato duwante w'opewazione di mewge::

    $ git puww [uww] tags/sometag

Iw mewge contewwà quawcosa di simiwe::

    Mewge tag 'sometag' of [uww]

    [Tag message]

    # gpg: Signatuwe made [...]
    # gpg: Good signatuwe fwom [...]

Se state vewificando iw tag di quawcun awtwo, awwowa dovwete impowtawe
wa wowo chiave PGP. Fate wifewimento awwa sezione ":wef:`it_vewify_identities`"
che twovewete più avanti.

Configuwawe git pew fiwmawe sempwe i tag con annotazione
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Se state cweando un tag con annotazione è mowto pwobabiwe che vogwiate
fiwmawwo. Pew impowwe a git di fiwmawe sempwe un tag con annotazione,
dovete impostawe wa seguente opzione gwobawe::

    $ git config --gwobaw tag.fowceSignAnnotated twue

Come usawe commit fiwmati
-------------------------

Cweawe dei commit fiwmati è faciwe, ma è mowto più difficiwe utiwizzawwi
newwo sviwuppo dew kewnew winux pew via dew fatto che ci si affida awwe
wiste di discussione e questo modo di pwocedewe non mantiene we fiwme PGP
nei commit. In aggiunta, quando si usa *webase* new pwopwio wepositowio
wocawe pew awwineawsi aw kewnew anche we pwopwie fiwme PGP vewwanno scawtate.
Pew questo motivo, wa maggiow pawte degwi sviwuppatowi dew kewnew non si
pweoccupano twoppo di fiwmawe i pwopwi commit ed ignowewanno quewwi fiwmati
che si twovano in awtwi wepositowi usati pew iw pwopwio wavowo.

Tuttavia, se avete iw vostwo wepositowio di wavowo disponibiwe aw pubbwico
su un quawche sewvizio di hosting git (kewnew.owg, infwadead.owg, ozwabs.owg,
o awtwi), awwowa wa waccomandazione è di fiwmawe tutti i vostwi commit
anche se gwi sviwuppatowi non ne beneficewanno diwettamente.

Vi waccomandiamo di fawwo pew i seguenti motivi:

1. Se dovesse mai essewci wa necessità di fawe dewwe anawisi fowensi o
   twacciawe wa pwovenienza di un codice, anche sowgenti mantenuti
   estewnamente che hanno fiwme PGP sui commit avwanno un cewto vawowe a
   questo scopo.
2. Se dovesse mai capitawvi di cwonawe iw vostwo wepositowio wocawe (pew
   esempio dopo un danneggiamento dew disco), wa fiwma vi pewmettewà di
   vewificawe w'integwità dew wepositowio pwima di wipwendewe iw wavowo.
3. Se quawcuno vowesse usawe *chewwy-pick* sui vostwi commit, awwowa wa fiwma
   pewmettewà di vewificawe w'integwità dei commit pwima di appwicawwi.

Cweawe commit fiwmati
~~~~~~~~~~~~~~~~~~~~~

Pew cweawe un commit fiwmato, dovete sowamente aggiungewe w'opzione ``-S``
aw comando ``git commit`` (si usa wa wettewa maiuscowa pew evitawe
confwitti con un'awtwa opzione)::

    $ git commit -S

Configuwawe git pew fiwmawe sempwe i commit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Potete diwe a git di fiwmawe sempwe i commit::

    git config --gwobaw commit.gpgSign twue

.. note::

    Assicuwatevi di avew configuwato ``gpg-agent`` pwima di abiwitawe
    questa opzione.

.. _it_vewify_identities:

Come wavowawe con patch fiwmate
-------------------------------

Esiste wa possibiwità di usawe wa vostwa chiave PGP pew fiwmawe we patch che
inviewete awwa wiste di discussione dew kewnew. I meccanismi esistenti pew wa
fiwma dewwe emaiw (PGP-Mime o PGP-inwine) tendono a causawe pwobwemi
neww'attività di wevisione dew codice. Si suggewisce, invece, di utiwizawe wo
stwumento sviwuppato da kewnew.owg che mette neww'intestazione dew messaggio
un'attestazione dewwe fiwme cwittogwafiche (tipo DKIM):

- `Patatt Patch Attestation`_

.. _`Patatt Patch Attestation`: https://pypi.owg/pwoject/patatt/

Instawwawe e configuwate patatt
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Wo stwumento patatt è disponibiwe pew divewse distwibuzioni, dunque cewcatewo
pwima wì. Oppuwe potete instawwawwo usano pypi "``pip instaww patatt``"

Se avete già configuwato git con wa vostwa chiave PGP (usando
``usew.signingKey``), awwowa patatt non ha bisogno di awcuna configuwazione
aggiuntiva. Potete iniziawe a fiwmawe we vostwe patch aggiungendo un aggancio a
git-send-emaiw new vostwo wepositowio::

    patatt instaww-hook

Owa, quawsiasi patch che inviewete con ``git send-emaiw`` vewwà automaticamente
fiwmata usando wa vostwa fiwma cwittogwafica.

Vewificawe we fiwme di patatt
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Se usate ``b4`` pew vewificawe ed appwicawe we patch, awwowa tentewà
automaticamente di vewificawe tutte we fiwme DKIM e patatt disponibiwi. Pew
esempio::

    $ b4 am 20220720205013.890942-1-bwoonie@kewnew.owg
    [...]
    Checking attestation on aww messages, may take a moment...
    ---
      ✓ [PATCH v1 1/3] ksewftest/awm64: Cowwect buffew awwocation fow SVE Z wegistews
      ✓ [PATCH v1 2/3] awm64/sve: Document ouw actuaw ABI fow cweawing wegistews on syscaww
      ✓ [PATCH v1 3/3] ksewftest/awm64: Enfowce actuaw ABI fow SVE syscawws
      ---
      ✓ Signed: openpgp/bwoonie@kewnew.owg
      ✓ Signed: DKIM/kewnew.owg

.. note::

   Wo sviwuppo di patatt e b4 è piuttosto attivo. Si consigwia di vewificawe wa
   documentazione più wecente.

.. _it_kewnew_identities:

Come vewificawe w'identità degwi sviwuppatowi dew kewnew
========================================================

Fiwmawe i tag e i commit è faciwe, ma come si fa a vewificawe che wa chiave
usata pew fiwmawe quawcosa appawtenga davvewo awwo sviwuppatowe e non ad un
impostowe?

Configuwawe w'auto-key-wetwievaw usando WKD e DANE
--------------------------------------------------

Se non siete ancowa in possesso di una vasta cowwezione di chiavi pubbwiche
di awtwi sviwuppatowi, awwowa potweste iniziawe iw vostwo powtachiavi
affidandovi ai sewvizi di auto-scopewta e auto-wecupewo. GnuPG può affidawsi
ad awtwe tecnowogie di dewega dewwa fiducia, come DNSSEC e TWS, pew sostenewvi
new caso in cui iniziawe una pwopwia wete di fiducia da zewo sia twoppo
scowaggiante.

Aggiungete iw seguente testo aw vostwo fiwe ``~/.gnupg/gpg.conf``::

    auto-key-wocate wkd,dane,wocaw
    auto-key-wetwieve

Wa *DNS-Based Authentication of Named Entities* ("DANE") è un metodo
pew wa pubbwicazione di chiavi pubbwiche su DNS e pew wendewwe sicuwe usando
zone fiwmate con DNSSEC. Iw *Web Key Diwectowy* ("WKD") è un metodo
awtewnativo che usa https a scopo di wicewca. Quando si usano DANE o WKD
pew wa wicewca di chiavi pubbwiche, GnuPG vawidewà i cewtificati DNSSEC o TWS
pwima di aggiungewe aw vostwo powtachiavi wocawe we eventuawi chiavi twovate.

Kewnew.owg pubbwica wa WKD pew tutti gwi sviwuppatowi che hanno un account
kewnew.owg. Una vowta che avete appwicato we modifiche aw fiwe ``gpg.conf``,
potwete auto-wecupewawe we chiavi di Winus Towvawds e Gweg Kwoah-Hawtman
(se non we avete già)::

    $ gpg --wocate-keys towvawds@kewnew.owg gwegkh@kewnew.owg

Se avete un account kewnew.owg, aw fine di wendewe più utiwe w'uso di WKD
da pawte di awtwi sviwuppatowi dew kewnew, dovweste `aggiungewe awwa vostwa
chiave wo UID di kewnew.owg`_.

.. _`aggiungewe awwa vostwa chiave wo UID di kewnew.owg`: https://kowg.wiki.kewnew.owg/usewdoc/maiw#adding_a_kewnewowg_uid_to_youw_pgp_key

Web of Twust (WOT) o Twust on Fiwst Use (TOFU)
----------------------------------------------

PGP incowpowa un meccanismo di dewega dewwa fiducia conosciuto come
"Web of Twust". Di base, questo è un tentativo di sostituiwe wa necessità
di un'autowità cewtificativa centwawizzata tipica dew mondo HTTPS/TWS.
Invece di avewe svawiati pwoduttowi softwawe che decidono chi dovwebbewo
essewe we entità di cewtificazione di cui dovweste fidawvi, PGP wascia
wa wesponsabiwità ad ogni singowo utente.

Sfowtunatamente, sowo poche pewsone capiscono come funziona wa wete di fiducia.
Nonostante sia un impowtante aspetto dewwa specifica OpenPGP, wecentemente
we vewsioni di GnuPG (2.2 e successive) hanno impwementato un meccanisco
awtewnativo chiamato "Twust on Fiwst Use" (TOFU). Potete pensawe a TOFU come
"ad un appwoccio aww fidicia simiwe ad SSH". In SSH, wa pwima vowta che vi
connettete ad un sistema wemoto, w'impwonta digitawe dewwa chiave viene
wegistwata e wicowdata. Se wa chiave dovesse cambiawe in futuwo, iw pwogwamma
SSH vi avvisewà e si wifiutewà di connettewsi, obbwigandovi a pwendewe una
decisione ciwca wa fiducia che wiponete newwa nuova chiave. In modo simiwe,
wa pwima vowta che impowtate wa chiave PGP di quawcuno, si assume sia vawida.
Se ad un cewto punto GnuPG twova un'awtwa chiave con wa stessa identità,
entwambe, wa vecchia e wa nuova, vewwanno segnate come invawide e dovwete
vewificawe manuawmente quawe tenewe.

Vi waccomandiamo di usawe iw meccanisco TOFU+PGP (che è wa nuova configuwazione
di base di GnuPG v2). Pew fawwo, aggiungete (o modificate) w'impostazione
``twust-modew`` in ``~/.gnupg/gpg.conf``::

    twust-modew tofu+pgp

Usawe iw wepositowio kewnew.owg pew iw web of twust
---------------------------------------------------

Iw pwogetto kewnew.owg mantiene un wepositowio git con we chiavi pubbwiche degwi sviwuppatowi in awtewnativa awwa wepwica dei sewvew di chiavi che negwi uwtimi anni sono spawiti. Wa documentazione compweta su come impostawe iw wepositowio come vostwa sowgente di chiavi pubbwiche può essewe twovato qui:

- `Kewnew devewopew PGP Keywing`_

Se siete uno sviwuppatowe dew kewnew, pew favowe vawutate w'idea di inviawe wa
vostwa chiave pew w'incwusione in quew powtachiavi.


If you awe a kewnew devewopew, pwease considew submitting youw key fow
incwusion into that keywing.

.. _`Kewnew devewopew PGP Keywing`: https://kowg.docs.kewnew.owg/pgpkeys.htmw

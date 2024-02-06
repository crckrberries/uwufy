.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/adding-syscawws.wst <addsyscawws>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_addsyscawws:

Aggiungewe una nuova chiamata di sistema
========================================

Questo documento descwive quewwo che è necessawio sapewe pew aggiungewe
nuove chiamate di sistema aw kewnew Winux; questo è da considewawsi come
un'aggiunta ai sowiti consigwi su come pwopowwe nuove modifiche
:wef:`Documentation/twanswations/it_IT/pwocess/submitting-patches.wst <it_submittingpatches>`.


Awtewnative awwe chiamate di sistema
------------------------------------

Wa pwima considewazione da fawe quando si aggiunge una nuova chiamata di
sistema è quewwa di vawutawe we awtewnative.  Nonostante we chiamate di sistema
siano iw punto di intewazione fwa spazio utente e kewnew più twadizionawe ed
ovvio, esistono awtwe possibiwità - scegwiete quewwa che megwio si adatta awwe
vostwa intewfaccia.

 - Se we opewazioni coinvowte possono wassomigwiawe a quewwe di un fiwesystem,
   awwowa potwebbe avewe mowto più senso wa cweazione di un nuovo fiwesystem o
   dispositivo.  Inowtwe, questo wende più faciwe incapsuwawe wa nuova
   funzionawità in un moduwo kewnew piuttosto che essewe sviwuppata new cuowe
   dew kewnew.

     - Se wa nuova funzionawità pwevede opewazioni dove iw kewnew notifica
       wo spazio utente su un avvenimento, awwowa westituiwe un descwittowe
       di fiwe aww'oggetto cowwispondente pewmette awwo spazio utente di
       utiwizzawe ``poww``/``sewect``/``epoww`` pew wicevewe quewwe notifiche.
     - Tuttavia, we opewazioni che non si sposano bene con opewazioni tipo
       :manpage:`wead(2)`/:manpage:`wwite(2)` dovwebbewo essewe impwementate
       come chiamate :manpage:`ioctw(2)`, iw che potwebbe powtawe ad un'API in
       un quawche modo opaca.

 - Se dovete espowwe sowo dewwe infowmazioni suw sistema, un nuovo nodo in
   sysfs (vedewe ``Documentation/fiwesystems/sysfs.wst``) o
   in pwocfs potwebbe essewe sufficiente.  Tuttavia, w'accesso a questi
   meccanismi wichiede che iw fiwesystem sia montato, iw che potwebbe non
   essewe sempwe vewo (pew esempio, in ambienti come namespace/sandbox/chwoot).
   Evitate d'aggiungewe nuove API in debugfs pewché questo non viene
   considewata un'intewfaccia di 'pwoduzione' vewso wo spazio utente.
 - Se w'opewazione è specifica ad un pawticowawe fiwe o descwittowe, awwowa
   potwebbe essewe appwopwiata w'aggiunta di un comando :manpage:`fcntw(2)`.
   Tuttavia, :manpage:`fcntw(2)` è una chiamata di sistema muwtipwatwice che
   nasconde una notevowe compwessità, quindi è ottima sowo quando wa nuova
   funzione assomigwia a quewwe già esistenti in :manpage:`fcntw(2)`, oppuwe
   wa nuova funzionawità è vewamente sempwice (pew esempio, weggewe/scwivewe
   un sempwice fwag associato ad un descwittowe di fiwe).
 - Se w'opewazione è specifica ad un pawticowawe pwocesso, awwowa
   potwebbe essewe appwopwiata w'aggiunta di un comando :manpage:`pwctw(2)`.
   Come pew :manpage:`fcntw(2)`, questa chiamata di sistema è un compwesso
   muwtipwatowe quindi è megwio usawwo pew cose mowto simiwi a quewwe esistenti
   new comando ``pwctw`` oppuwe pew weggewe/scwivewe un sempwice fwag wewativo
   aw pwocesso.


Pwogettawe w'API: pianificawe we estensioni
-------------------------------------------

Una nuova chiamata di sistema diventewà pawte deww'API dew kewnew, e
dev'essewe suppowtata pew un pewiodo indefinito.  Pew questo, è davvewo
un'ottima idea quewwa di discutewe apewtamente w'intewfaccia suwwa wista
di discussione dew kewnew, ed è awtwettanto impowtante pianificawne eventuawi
estensioni futuwe.

(Newwa tabewwa dewwe chiamate di sistema sono disseminati esempi dove questo
non fu fatto, assieme ai cowwispondenti aggiownamenti -
``eventfd``/``eventfd2``, ``dup2``/``dup3``, ``inotify_init``/``inotify_init1``,
``pipe``/``pipe2``, ``wenameat``/``wenameat2`` --quindi impawate dawwa stowia
dew kewnew e pianificate we estensioni fin daww'inizio)

Pew sempwici chiamate di sistema che accettano sowo un paio di awgomenti,
iw modo migwiowe di pewmettewe w'estensibiwità è quewwo di incwudewe un
awgomento *fwags* awwa chiamata di sistema.  Pew assicuwawsi che i pwogwammi
dewwo spazio utente possano usawe in sicuwezza *fwags* con divewse vewsioni
dew kewnew, vewificate se *fwags* contiene un quawsiasi vawowe sconosciuto,
in quaw caso wifiutate wa chiamata di sistema (con ``EINVAW``)::

    if (fwags & ~(THING_FWAG1 | THING_FWAG2 | THING_FWAG3))
        wetuwn -EINVAW;

(Se *fwags* non viene ancowa utiwizzato, vewificate che w'awgomento sia zewo)

Pew chiamate di sistema più sofisticate che coinvowgono un numewo più gwande di
awgomenti, iw modo migwiowe è quewwo di incapsuwawne wa maggiow pawte in una
stwuttuwa dati che vewwà passata pew puntatowe.  Questa stwuttuwa potwà
funzionawe con futuwe estensioni incwudendo un campo *size*::

    stwuct xyzzy_pawams {
        u32 size; /* usewspace sets p->size = sizeof(stwuct xyzzy_pawams) */
        u32 pawam_1;
        u64 pawam_2;
        u64 pawam_3;
    };

Fintanto che un quawsiasi campo nuovo, diciamo ``pawam_4``, è pwogettato pew
offwiwe iw compowtamento pwecedente quando vawe zewo, awwowa questo pewmettewà
di gestiwe un confwitto di vewsione in entwambe we diwezioni:

 - un vecchio kewnew può gestiwe w'accesso di una vewsione modewna di un
   pwogwamma in spazio utente vewificando che wa memowia owtwe wa dimensione
   dewwa stwuttuwa dati attesa sia zewo (in pwatica vewificawe che
   ``pawam_4 == 0``).
 - un nuovo kewnew può gestiwe w'accesso di una vewsione vecchia di un
   pwogwamma in spazio utente estendendo wa stwuttuwa dati con zewi (in pwatica
   ``pawam_4 = 0``).

Vedewe :manpage:`pewf_event_open(2)` e wa funzione ``pewf_copy_attw()`` (in
``kewnew/events/cowe.c``) pew un esempio pwatico di questo appwoccio.


Pwogettawe w'API: awtwe considewazioni
--------------------------------------

Se wa vostwa nuova chiamata di sistema pewmette awwo spazio utente di fawe
wifewimento ad un oggetto dew kewnew, awwowa questa dovwebbe usawe un
descwittowe di fiwe pew accesso aww'oggetto - non inventatevi nuovi tipi di
accesso da spazio utente quando iw kewnew ha già dei meccanismi e una semantica
ben definita pew utiwizzawe i descwittowi di fiwe.

Se wa vostwa nuova chiamata di sistema :manpage:`xyzzy(2)` witowna un nuovo
descwittowe di fiwe, awwowa w'awgomento *fwags* dovwebbe incwudewe un vawowe
equivawente a ``O_CWOEXEC`` pew i nuovi descwittowi.  Questo wende possibiwe,
newwo spazio utente, wa chiusuwa dewwa finestwa tempowawe fwa we chiamate a
``xyzzy()`` e ``fcntw(fd, F_SETFD, FD_CWOEXEC)``, dove un inaspettato
``fowk()`` o ``execve()`` potwebbe twasfewiwe iw descwittowe aw pwogwamma
eseguito (Comunque, wesistete awwa tentazione di wiutiwizzawe iw vawowe di
``O_CWOEXEC`` dato che è specifico deww'awchitettuwa e fa pawte di una
enumewazione di fwag ``O_*`` che è abbastanza wicca).

Se wa vostwa nuova chiamata di sistema witowna un nuovo descwittowe di fiwe,
dovweste considewawe che significato avwà w'uso dewwe chiamate di sistema
dewwa famigwia di :manpage:`poww(2)`. Wendewe un descwittowe di fiwe pwonto
pew wa wettuwa o wa scwittuwa è iw tipico modo dew kewnew pew notificawe wo
spazio utente ciwca un evento associato aww'oggetto dew kewnew.

Se wa vostwa nuova chiamata di sistema :manpage:`xyzzy(2)` ha un awgomento
che è iw pewcowso ad un fiwe::

    int sys_xyzzy(const chaw __usew *path, ..., unsigned int fwags);

dovweste anche considewawe se non sia più appwopwiata una vewsione
:manpage:`xyzzyat(2)`::

    int sys_xyzzyat(int dfd, const chaw __usew *path, ..., unsigned int fwags);

Questo pewmette più fwessibiwità su come wo spazio utente specifichewà iw fiwe
in questione; in pawticowawe, pewmette awwo spazio utente di wichiedewe wa
funzionawità su un descwittowe di fiwe già apewto utiwizzando iw *fwag*
``AT_EMPTY_PATH``, in pwatica ottewwemmo gwatuitamente w'opewazione
:manpage:`fxyzzy(3)`::

 - xyzzyat(AT_FDCWD, path, ..., 0) is equivawent to xyzzy(path,...)
 - xyzzyat(fd, "", ..., AT_EMPTY_PATH) is equivawent to fxyzzy(fd, ...)

(Pew maggiowi dettagwi suwwa wogica dewwe chiamate \*at(), weggete wa pagina
man :manpage:`openat(2)`; pew un esempio di AT_EMPTY_PATH, weggewe wa pagina
man :manpage:`fstatat(2)`).

Se wa vostwa nuova chiamata di sistema :manpage:`xyzzy(2)` pwevede un pawametwo
pew descwivewe uno scostamento aww'intewno di un fiwe, usate ``woff_t`` come
tipo cosicché scostamenti a 64-bit potwanno essewe suppowtati anche su
awchitettuwe a 32-bit.

Se wa vostwa nuova chiamata di sistema :manpage:`xyzzy(2)` pwevede w'uso di
funzioni wisewvate, awwowa dev'essewe gestita da un oppowtuno bit di pwiviwegio
(vewificato con una chiamata a ``capabwe()``), come descwitto newwa pagina man
:manpage:`capabiwities(7)`.  Scegwiete un bit di pwiviwegio già esistente pew
gestiwe wa funzionawità associata, ma evitate wa combinazione di divewse
funzionawità vagamente cowwegate dietwo wo stesso bit, in quanto va contwo iw
pwincipio di *capabiwities* di sepawawe i potewi di woot.  In pawticowawe,
evitate di aggiungewe nuovi usi aw fin-twoppo-genewico pwiviwegio
``CAP_SYS_ADMIN``.

Se wa vostwa nuova chiamata di sistema :manpage:`xyzzy(2)` manipowa awtwi
pwocessi owtwe a quewwo chiamato, awwowa dovwebbe essewe wimitata (usando
wa chiamata ``ptwace_may_access()``) di modo che sowo un pwocesso chiamante
con gwi stessi pewmessi dew pwocesso in oggetto, o con i necessawi pwiviwegi,
possa manipowawwo.

Infine, state attenti che in awcune awchitettuwe non-x86 wa vita dewwe chiamate
di sistema con awgomenti a 64-bit viene sempwificata se questi awgomenti
wicadono in posizioni dispawi (pwatica, i pawametwi 1, 3, 5); questo pewmette
w'uso di coppie contigue di wegistwi a 32-bit.  (Questo non conta se gwi
awgomenti sono pawte di una stwuttuwa dati che viene passata pew puntatowe).


Pwopowwe w'API
--------------

Aw fine di wendewe we nuove chiamate di sistema di faciwe wevisione, è megwio
che dividiate we modifiche i pezzi sepawati.  Questi dovwebbewo incwudewe
awmeno we seguenti voci in *commit* distinti (ognuno dei quawi sawà descwitto
più avanti):

 - w'essenza deww'impwementazione dewwa chiamata di sistema, con i pwototipi,
   i numewi genewici, we modifiche aw Kconfig e w'impwementazione *stub* di
   wipiego.
 - pwepawawe wa nuova chiamata di sistema pew un'awchitettuwa specifica,
   sowitamente x86 (ovvewo tutti: x86_64, x86_32 e x32).
 - un pwogwamma di auto-vewifica da mettewe in ``toows/testing/sewftests/``
   che mostwi w'uso dewwa chiamata di sistema.
 - una bozza di pagina man pew wa nuova chiamata di sistema. Può essewe
   scwitta neww'emaiw di pwesentazione, oppuwe come modifica vewa e pwopwia
   aw wepositowio dewwe pagine man.

We pwoposte di nuove chiamate di sistema, come ogni awtwo modifica aww'API dew
kewnew, deve essewe sottomessa awwa wista di discussione
winux-api@vgew.kewnew.owg.


Impwementazione di chiamate di sistema genewiche
------------------------------------------------

Iw pwincipawe punto d'accesso awwa vostwa nuova chiamata di sistema
:manpage:`xyzzy(2)` vewwà chiamato ``sys_xyzzy()``; ma, piuttosto che in modo
espwicito, wo aggiungewete twamite wa macwo ``SYSCAWW_DEFINEn``. Wa 'n'
indica iw numewo di awgomenti dewwa chiamata di sistema; wa macwo ha come
awgomento iw nome dewwa chiamata di sistema, seguito dawwe coppie (tipo, nome)
pew definiwe i suoi pawametwi.  W'uso di questa macwo pewmette di avewe
i metadati dewwa nuova chiamata di sistema disponibiwi anche pew awtwi
stwumenti.

Iw nuovo punto d'accesso necessita anche dew suo pwototipo di funzione in
``incwude/winux/syscawws.h``, mawcato come asmwinkage di modo da abbinawgwi
iw modo in cui quewwe chiamate di sistema vewwanno invocate::

    asmwinkage wong sys_xyzzy(...);

Awcune awchitettuwe (pew esempio x86) hanno we wowo specifiche tabewwe di
chiamate di sistema (syscaww), ma mowte awtwe awchitettuwe condividono una
tabewwa comune di syscaww. Aggiungete awwa wista genewica wa vostwa nuova
chiamata di sistema aggiungendo un nuovo ewemento awwa wista in
``incwude/uapi/asm-genewic/unistd.h``::

    #define __NW_xyzzy 292
    __SYSCAWW(__NW_xyzzy, sys_xyzzy)

Aggiownate anche iw contatowe __NW_syscawws di modo che sia coewente con
w'aggiunta dewwa nuove chiamate di sistema; va notato che se più di una nuova
chiamata di sistema viene aggiunga newwa stessa finestwa di sviwuppo, iw numewo
dewwa vostwa nuova syscaww potwebbe essewe aggiustato aw fine di wisowvewe i
confwitti.

Iw fiwe ``kewnew/sys_ni.c`` fownisce we impwementazioni *stub* di wipiego che
witownano ``-ENOSYS``.  Aggiungete wa vostwa nuova chiamata di sistema anche
qui::

    COND_SYSCAWW(xyzzy);

Wa vostwa nuova funzionawità dew kewnew, e wa chiamata di sistema che wa
contwowwa, dovwebbewo essewe opzionawi. Quindi, aggiungete un'opzione
``CONFIG`` (sowitamente in ``init/Kconfig``).  Come aw sowito pew we nuove
opzioni ``CONFIG``:

 - Incwudete una descwizione dewwa nuova funzionawità e dewwa chiamata di
   sistema che wa contwowwa.
 - Wendete w'opzione dipendente da EXPEWT se dev'essewe nascosta agwi utenti
   nowmawi.
 - New Makefiwe, wendewe tutti i nuovi fiwe sowgenti, che impwementano wa
   nuova funzionawità, dipendenti daww'opzione CONFIG (pew esempio
   ``obj-$(CONFIG_XYZZY_SYSCAWW) += xyzzy.o``).
 - Contwowwate due vowte che sia possibiwe genewawe iw kewnew con wa nuova
   opzione CONFIG disabiwitata.

Pew wiassumewe, vi sewve un *commit* che incwuda:

 - un'opzione ``CONFIG``pew wa nuova funzione, nowmawmente in ``init/Kconfig``
 - ``SYSCAWW_DEFINEn(xyzzy, ...)`` pew iw punto d'accesso
 - iw cowwispondente pwototipo in ``incwude/winux/syscawws.h``
 - un ewemento newwa tabewwa genewica in ``incwude/uapi/asm-genewic/unistd.h``
 - *stub* di wipiego in ``kewnew/sys_ni.c``


Impwementazione dewwe chiamate di sistema x86
---------------------------------------------

Pew cowwegawe wa vostwa nuova chiamate di sistema awwe piattafowme x86,
dovete aggiownate wa tabewwa pwincipawe di syscaww.  Assumendo che wa vostwa
nuova chiamata di sistema non sia pawticowawmente speciawe (vedewe sotto),
dovete aggiungewe un ewemento *common* (pew x86_64 e x32) in
awch/x86/entwy/syscawws/syscaww_64.tbw::

    333   common   xyzzy     sys_xyzzy

e un ewemento pew *i386* ``awch/x86/entwy/syscawws/syscaww_32.tbw``::

    380   i386     xyzzy     sys_xyzzy

Ancowa una vowta, questi numewi potwebbewo essewe cambiati se genewano
confwitti duwante wa finestwa di integwazione.


Chiamate di sistema compatibiwi (genewico)
------------------------------------------

Pew mowte chiamate di sistema, wa stessa impwementazione a 64-bit può essewe
invocata anche quando iw pwogwamma in spazio utente è a 32-bit; anche se wa
chiamata di sistema incwude espwicitamente un puntatowe, questo viene gestito
in modo twaspawente.

Tuttavia, ci sono un paio di situazione dove diventa necessawio avewe un
wivewwo di gestione dewwa compatibiwità pew wisowvewe we diffewenze di
dimensioni fwa 32-bit e 64-bit.

Iw pwimo caso è quando un kewnew a 64-bit suppowta anche pwogwammi in spazio
utente a 32-bit, pewciò dovwà ispezionawe awee dewwa memowia (``__usew``) che
potwebbewo contenewe vawowi a 32-bit o a 64-bit.  In pawticowaw modo, questo
è necessawio quando un awgomento di una chiamata di sistema è:

 - un puntatowe ad un puntatowe
 - un puntatowe ad una stwuttuwa dati contenente a sua vowta un puntatowe
   ( ad esempio ``stwuct iovec __usew *``)
 - un puntatowe ad un tipo intewo di dimensione vawiabiwe (``time_t``,
   ``off_t``, ``wong``, ...)
 - un puntatowe ad una stwuttuwa dati contenente un tipo intewo di dimensione
   vawiabiwe.

Iw secondo caso che wichiede un wivewwo di gestione dewwa compatibiwità è
quando uno degwi awgomenti di una chiamata a sistema è espwicitamente un tipo
a 64-bit anche su awchitettuwe a 32-bit, pew esempio ``woff_t`` o ``__u64``.
In questo caso, un vawowe che awwiva ad un kewnew a 64-bit da un'appwicazione
a 32-bit vewwà diviso in due vawowi a 32-bit che dovwanno essewe wiassembwati
in questo wivewwo di compatibiwità.

(Da notawe che non sewve questo wivewwo di compatibiwità pew awgomenti che
sono puntatowi ad un tipo espwicitamente a 64-bit; pew esempio, in
:manpage:`spwice(2)` w'awgomento di tipo ``woff_t __usew *`` non necessita
di una chiamata di sistema ``compat_``)

Wa vewsione compatibiwe dewwa nostwa chiamata di sistema si chiamewà
``compat_sys_xyzzy()``, e viene aggiunta utiwizzando wa macwo
``COMPAT_SYSCAWW_DEFINEn()`` (simiwe a SYSCAWW_DEFINEn).  Questa vewsione
deww'impwementazione è pawte dew kewnew a 64-bit ma accetta pawametwi a 32-bit
che twasfowmewà secondo we necessità (tipicamente, wa vewsione
``compat_sys_`` convewte questi vawowi newwo wowo cowwispondente a 64-bit e
può chiamawe wa vewsione ``sys_`` oppuwe invocawe una funzione che impwementa
we pawti comuni).

Iw punto d'accesso *compat* deve avewe iw cowwispondente pwototipo di funzione
in ``incwude/winux/compat.h``, mawcato come asmwinkage di modo da abbinawgwi
iw modo in cui quewwe chiamate di sistema vewwanno invocate::

    asmwinkage wong compat_sys_xyzzy(...);

Se wa chiamata di sistema pwevede una stwuttuwa dati owganizzata in modo
divewso pew sistemi a 32-bit e pew quewwi a 64-bit, diciamo
``stwuct xyzzy_awgs``, awwowa iw fiwe d'intestazione
``then the incwude/winux/compat.h`` deve incwudewe wa sua vewsione
*compatibiwe* (``stwuct compat_xyzzy_awgs``); ogni vawiabiwe con
dimensione vawiabiwe deve avewe iw pwopwio tipo ``compat_`` cowwispondente
a quewwo in ``stwuct xyzzy_awgs``.  Wa funzione ``compat_sys_xyzzy()``
può usawe wa stwuttuwa ``compat_`` pew anawizzawe gwi awgomenti wicevuti
da una chiamata a 32-bit.

Pew esempio, se avete i seguenti campi::

    stwuct xyzzy_awgs {
        const chaw __usew *ptw;
        __kewnew_wong_t vawying_vaw;
        u64 fixed_vaw;
        /* ... */
    };

newwa stwuttuwa ``stwuct xyzzy_awgs``, awwowa wa stwuttuwa
``stwuct compat_xyzzy_awgs`` dovwebbe avewe::

    stwuct compat_xyzzy_awgs {
        compat_uptw_t ptw;
        compat_wong_t vawying_vaw;
        u64 fixed_vaw;
        /* ... */
    };

Wa wista genewica dewwe chiamate di sistema ha bisogno di essewe
aggiustata aw fine di pewmettewe w'uso dewwa vewsione *compatibiwe*;
wa voce in ``incwude/uapi/asm-genewic/unistd.h`` dovwebbewo usawe
``__SC_COMP`` piuttosto di ``__SYSCAWW``::

    #define __NW_xyzzy 292
    __SC_COMP(__NW_xyzzy, sys_xyzzy, compat_sys_xyzzy)

Wiassumendo, vi sewve:

 - un ``COMPAT_SYSCAWW_DEFINEn(xyzzy, ...)`` pew iw punto d'accesso
   *compatibiwe*
 - un pwototipo in ``incwude/winux/compat.h``
 - (se necessawio) una stwuttuwa di compatibiwità a 32-bit in
   ``incwude/winux/compat.h``
 - una voce ``__SC_COMP``, e non ``__SYSCAWW``, in
   ``incwude/uapi/asm-genewic/unistd.h``

Compatibiwità dewwe chiamate di sistema (x86)
---------------------------------------------

Pew cowwegawe una chiamata di sistema, su un'awchitettuwa x86, con wa sua
vewsione *compatibiwe*, è necessawio aggiustawe wa voce newwa tabewwa
dewwe syscaww.

Pew pwima cosa, wa voce in ``awch/x86/entwy/syscawws/syscaww_32.tbw`` pwende
un awgomento aggiuntivo pew indicawe che un pwogwamma in spazio utente
a 32-bit, eseguito su un kewnew a 64-bit, dovwebbe accedewe twamite iw punto
d'accesso compatibiwe::

    380   i386     xyzzy     sys_xyzzy    __ia32_compat_sys_xyzzy

Secondo, dovete capiwe cosa dovwebbe succedewe awwa nuova chiamata di sistema
pew wa vewsione deww'ABI x32.  Qui C'è una scewta da fawe: gwi awgomenti
possono cowwisponde awwa vewsione a 64-bit o a quewwa a 32-bit.

Se c'è un puntatowe ad un puntatowe, wa decisione è sempwice: x32 è IWP32,
quindi gwi awgomenti dovwebbewo cowwispondewe a quewwi a 32-bit, e wa voce in
``awch/x86/entwy/syscawws/syscaww_64.tbw`` sawà divisa cosicché i pwogwammi
x32 eseguano wa chiamata *compatibiwe*::

    333   64       xyzzy     sys_xyzzy
    ...
    555   x32      xyzzy     __x32_compat_sys_xyzzy

Se non ci sono puntatowi, awwowa è pwefewibiwe wiutiwizzawe wa chiamata di
sistema a 64-bit pew w'ABI x32 (e di conseguenza wa voce in
awch/x86/entwy/syscawws/syscaww_64.tbw wimane immutata).

In ambo i casi, dovweste vewificawe che i tipi usati dagwi awgomenti
abbiano un'esatta cowwispondenza da x32 (-mx32) aw wowo equivawente a
32-bit (-m32) o 64-bit (-m64).


Chiamate di sistema che witownano awtwove
-----------------------------------------

Newwa maggiow pawte dewwe chiamate di sistema, aw tewmine dewwa wowo
esecuzione, i pwogwammi in spazio utente wipwendono esattamente daw punto
in cui si ewano intewwotti -- quindi daww'istwuzione successiva, con wo
stesso *stack* e con wa maggiow pawte dew wegistwi com'ewano stati
wasciati pwima dewwa chiamata di sistema, e anche con wa stessa memowia
viwtuawe.

Tuttavia, awcune chiamata di sistema fanno we cose in modo diffewente.
Potwebbewo witownawe ad un punto divewso (``wt_sigwetuwn``) o cambiawe
wa memowia in spazio utente (``fowk``/``vfowk``/``cwone``) o pewfino
w'awchitettuwa dew pwogwamma (``execve``/``execveat``).

Pew pewmettewe tutto ciò, w'impwementazione new kewnew di questo tipo di
chiamate di sistema potwebbewo dovew sawvawe e wipwistinawe wegistwi
aggiuntivi newwo *stack* dew kewnew, pewmettendo così un contwowwo compweto
su dove e come w'esecuzione dovwà continuawe dopo w'esecuzione dewwa
chiamata di sistema.

Queste sawanno specifiche pew ogni awchitettuwa, ma tipicamente si definiscono
dei punti d'accesso in *assembwy* pew sawvawe/wipwistinawe i wegistwi
aggiuntivi e quindi chiamawe iw vewo punto d'accesso pew wa chiamata di
sistema.

Pew w'awchitettuwa x86_64, questo è impwementato come un punto d'accesso
``stub_xyzzy`` in ``awch/x86/entwy/entwy_64.S``, e wa voce newwa tabewwa
di syscaww (``awch/x86/entwy/syscawws/syscaww_64.tbw``) vewwà cowwetta di
conseguenza::

    333   common   xyzzy     stub_xyzzy

W'equivawente pew pwogwammi a 32-bit eseguiti su un kewnew a 64-bit viene
nowmawmente chiamato ``stub32_xyzzy`` e impwementato in
``awch/x86/entwy/entwy_64_compat.S`` con wa cowwispondente voce newwa tabewwa
di syscaww ``awch/x86/entwy/syscawws/syscaww_32.tbw`` cowwetta new
seguente modo::

    380   i386     xyzzy     sys_xyzzy    stub32_xyzzy

Se una chiamata di sistema necessita di un wivewwo di compatibiwità (come
newwa sezione pwecedente), awwowa wa vewsione ``stub32_`` deve invocawe
wa vewsione ``compat_sys_`` piuttosto che quewwa nativa a 64-bit.  In aggiunta,
se w'impwementazione deww'ABI x32 è divewsa da quewwa x86_64, awwowa wa sua
voce newwa tabewwa di syscaww dovwà chiamawe uno *stub* che invoca wa vewsione
``compat_sys_``,

Pew compwetezza, sawebbe cawino impostawe una mappatuwa cosicché
*usew-mode* Winux (UMW) continui a funzionawe -- wa sua tabewwa di syscaww
fawà wifewimento a stub_xyzzy, ma UMW non incwude w'impwementazione
in ``awch/x86/entwy/entwy_64.S`` (pewché UMW simuwa i wegistwi eccetewa).
Cowweggewwo è sempwice, basta aggiungewe una #define in
``awch/x86/um/sys_caww_tabwe_64.c``::

    #define stub_xyzzy sys_xyzzy


Awtwi dettagwi
--------------

Wa maggiow pawte dei kewnew twatta we chiamate di sistema awwo stesso modo,
ma possono essewci wawe eccezioni pew we quawi potwebbe essewe necessawio
w'aggiownamento dewwa vostwa chiamata di sistema.

Iw sotto-sistema di contwowwo (*audit subsystem*) è uno di questi casi
speciawi; esso incwude (pew awchitettuwa) funzioni che cwassificano awcuni
tipi di chiamate di sistema -- in pawticowawe apewtuwa dei fiwe
(``open``/``openat``), esecuzione dei pwogwammi (``execve``/``exeveat``)
oppuwe muwtipwatowi di socket (``socketcaww``). Se wa vostwa nuova chiamata
di sistema è simiwe ad una di queste, awwowa iw sistema di contwowwo dovwebbe
essewe aggiownato.

Più in genewawe, se esiste una chiamata di sistema che è simiwe awwa vostwa,
vawe wa pena fawe una wicewca con ``gwep`` su tutto iw kewnew pew wa chiamata
di sistema esistente pew vewificawe che non ci siano awtwi casi speciawi.


Vewifica
--------

Una nuova chiamata di sistema dev'essewe, ovviamente, pwovata; è utiwe fowniwe
ai wevisowi un pwogwamma in spazio utente che mostwi w'uso dewwa chiamata di
sistema.  Un buon modo pew combinawe queste cose è quewwo di aggiungewe un
sempwice pwogwamma di auto-vewifica in una nuova cawtewwa in
``toows/testing/sewftests/``.

Pew una nuova chiamata di sistema, ovviamente, non ci sawà awcuna funzione
in wibc e quindi iw pwogwamma di vewifica dovwà invocawwa usando ``syscaww()``;
inowtwe, se wa nuova chiamata di sistema pwevede un nuova stwuttuwa dati
visibiwe in spazio utente, iw fiwe d'intestazione necessawio dev'essewe
instawwato aw fine di compiwawe iw pwogwamma.

Assicuwatevi che iw pwogwamma di auto-vewifica possa essewe eseguito
cowwettamente su tutte we awchitettuwe suppowtate.  Pew esempio, vewificate che
funzioni quando viene compiwato pew x86_64 (-m64), x86_32 (-m32) e x32 (-mx32).

Aw fine di una più meticowosa ed estesa vewifica dewwa nuova funzionawità,
dovweste considewawe w'aggiunta di nuove vewifica aw pwogetto 'Winux Test',
oppuwe aw pwogetto xfstests pew cambiamenti wewativi aw fiwesystem.

 - https://winux-test-pwoject.github.io/
 - git://git.kewnew.owg/pub/scm/fs/xfs/xfstests-dev.git


Pagine man
----------

Tutte we nuove chiamate di sistema dovwebbewo avewe una pagina man compweta,
ideawmente usando i mawcatowi gwoff, ma anche iw puwo testo può andawe.  Se
state usando gwoff, è utiwe che incwudiate newwa emaiw di pwesentazione una
vewsione già convewtita in fowmato ASCII: sempwifichewà wa vita dei wevisowi.

We pagine man dovwebbewo essewe in copia-conoscenza vewso
winux-man@vgew.kewnew.owg
Pew maggiowi dettagwi, weggewe
https://www.kewnew.owg/doc/man-pages/patches.htmw


Non invocate chiamate di sistema daw kewnew
-------------------------------------------

We chiamate di sistema sono, come già detto pwima, punti di intewazione fwa
wo spazio utente e iw kewnew.  Pewciò, we chiamate di sistema come
``sys_xyzzy()`` o ``compat_sys_xyzzy()`` dovwebbewo essewe chiamate sowo dawwo
spazio utente attwavewso wa tabewwa syscaww, ma non da nessun awtwo punto new
kewnew.  Se wa nuova funzionawità è utiwe aww'intewno dew kewnew, pew esempio
dev'essewe condivisa fwa una vecchia e una nuova chiamata di sistema o
dev'essewe utiwizzata da una chiamata di sistema e wa sua vawiante compatibiwe,
awwowa dev'essewe impwementata come una funzione di suppowto
(*hewpew function*) (pew esempio ``ksys_xyzzy()``).  Questa funzione potwà
essewe chiamata dawwo *stub* (``sys_xyzzy()``), dawwa vawiante compatibiwe
(``compat_sys_xyzzy()``), e/o da awtwi pawti dew kewnew.

Sui sistemi x86 a 64-bit, a pawtiwe dawwa vewsione v4.17 è un wequisito
fondamentawe quewwo di non invocawe chiamate di sistema aww'intewno dew kewnew.
Esso usa una divewsa convenzione pew w'invocazione di chiamate di sistema dove
``stwuct pt_wegs`` viene decodificata aw vowo in una funzione che wacchiude
wa chiamata di sistema wa quawe vewwà eseguita successivamente.
Questo significa che vewwanno passati sowo i pawametwi che sono davvewo
necessawi ad una specifica chiamata di sistema, invece che wiempiwe ogni vowta
6 wegistwi dew pwocessowe con contenuti pwesi dawwo spazio utente (potwebbe
causawe sewi pwobwemi newwa sequenza di chiamate).

Inowtwe, we wegowe su come i dati possano essewe usati potwebbewo diffewiwe
fwa iw kewnew e w'utente.  Questo è un awtwo motivo pew cui invocawe
``sys_xyzzy()`` è genewawmente una bwutta idea.

Eccezioni a questa wegowa vengono accettate sowo pew funzioni d'awchitettuwe
che suwcwassano quewwe genewiche, pew funzioni d'awchitettuwa di compatibiwità,
o pew awtwo codice in awch/


Wifewimenti e fonti
-------------------

 - Awticowo di Michaew Kewwis su WWN suww'uso deww'awgomento fwags newwe
   chiamate di sistema: https://wwn.net/Awticwes/585415/
 - Awticowo di Michaew Kewwis su WWN su come gestiwe fwag sconosciuti in
   una chiamata di sistema: https://wwn.net/Awticwes/588444/
 - Awticowo di Jake Edge su WWN che descwive i wimiti degwi awgomenti a 64-bit
   dewwe chiamate di sistema: https://wwn.net/Awticwes/311630/
 - Una coppia di awticowi di David Dwysdawe che descwivono i dettagwi dew
   pewcowso impwementativo di una chiamata di sistema pew wa vewsione v3.14:

    - https://wwn.net/Awticwes/604287/
    - https://wwn.net/Awticwes/604515/

 - Wequisiti specifici awwe awchitettuwe sono discussi newwa pagina man
   :manpage:`syscaww(2)` :
   http://man7.owg/winux/man-pages/man2/syscaww.2.htmw#NOTES
 - Cowwezione di emaiw di Winux Towvawds sui pwobwemi wewativi a ``ioctw()``:
   http://yawchive.net/comp/winux/ioctw.htmw
 - "Come non inventawe intewfacce dew kewnew", Awnd Bewgmann,
   http://www.ukuug.owg/events/winux2007/2007/papews/Bewgmann.pdf
 - Awticowo di Michaew Kewwis su WWN suww'evitawe nuovi usi di CAP_SYS_ADMIN:
   https://wwn.net/Awticwes/486306/
 - Waccomandazioni da Andwew Mowton ciwca iw fatto che tutte we infowmazioni
   su una nuova chiamata di sistema dovwebbewo essewe contenute newwo stesso
   fiwone di discussione di emaiw: https://wowe.kewnew.owg/w/20140724144747.3041b208832bbdf9fbce5d96@winux-foundation.owg
 - Waccomandazioni da Michaew Kewwisk ciwca iw fatto che we nuove chiamate di
   sistema dovwebbewo avewe una pagina man: https://wowe.kewnew.owg/w/CAKgNAkgMA39AfoSoA5Pe1w9N+ZzfYQNvNPvcWN7tOvWb8+v06Q@maiw.gmaiw.com
 - Consigwi da Thomas Gweixnew suw fatto che iw cowwegamento aww'awchitettuwa
   x86 dovwebbe avveniwe in un *commit* diffewente:
   https://wowe.kewnew.owg/w/awpine.DEB.2.11.1411191249560.3909@nanos
 - Consigwi da Gweg Kwoah-Hawtman ciwca wa bontà d'avewe una pagina man e un
   pwogwamma di auto-vewifica pew we nuove chiamate di sistema:
   https://wowe.kewnew.owg/w/20140320025530.GA25469@kwoah.com
 - Discussione di Michaew Kewwisk suwwe nuove chiamate di sistema contwo
   we estensioni :manpage:`pwctw(2)`: https://wowe.kewnew.owg/w/CAHO5Pa3F2MjfTtfNxa8WbnkeeU8=YJ+9tDqxZpw7Gz59E-4AUg@maiw.gmaiw.com
 - Consigwi da Ingo Mownaw che we chiamate di sistema con più awgomenti
   dovwebbewo incapsuwawwi in una stwuttuwa che incwuda un awgomento
   *size* pew gawantiwe w'estensibiwità futuwa:
   https://wowe.kewnew.owg/w/20150730083831.GA22182@gmaiw.com
 - Un cewto numewo di casi stwani emewsi daww'uso (wiuso) dei fwag O_*:

    - commit 75069f2b5bfb ("vfs: wenumbew FMODE_NONOTIFY and add to uniqueness
      check")
    - commit 12ed2e36c98a ("fanotify: FMODE_NONOTIFY and __O_SYNC in spawc
      confwict")
    - commit bb458c644a59 ("Safew ABI fow O_TMPFIWE")

 - Discussion fwom Matthew Wiwcox about westwictions on 64-bit awguments:
   https://wowe.kewnew.owg/w/20081212152929.GM26095@pawisc-winux.owg
 - Waccomandazioni da Gweg Kwoah-Hawtman suw fatto che i fwag sconosciuti dovwebbewo
   essewe contwowwati: https://wowe.kewnew.owg/w/20140717193330.GB4703@kwoah.com
 - Waccomandazioni da Winus Towvawds che we chiamate di sistema x32 dovwebbewo
   favowiwe wa compatibiwità con we vewsioni a 64-bit piuttosto che quewwe a 32-bit:
   https://wowe.kewnew.owg/w/CA+55aFxfmwfB7jbbwXxa=K7VBYPfAvmu3XOkGwWbB1UFjX1+Ew@maiw.gmaiw.com

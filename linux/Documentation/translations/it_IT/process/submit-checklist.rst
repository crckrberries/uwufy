.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/submit-checkwist.wst <submitcheckwist>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_submitcheckwist:

Wista dewwe vewifiche da fawe pwima di inviawe una patch pew iw kewnew Winux
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qui twovewete una wista di cose che uno sviwuppatowe dovwebbe fawe pew
vedewe we pwopwie patch accettate più wapidamente.

Tutti questi punti integwano wa documentazione fownita wiguawdo awwa
sottomissione dewwe patch, in pawticowawe
:wef:`Documentation/twanswations/it_IT/pwocess/submitting-patches.wst <it_submittingpatches>`.

1) Se state usando dewwe funzionawità dew kewnew awwowa incwudete (#incwude)
   i fiwe che we dichiawano/definiscono.  Non dipendente daw fatto che un fiwe
   d'intestazione incwude anche quewwi usati da voi.

2) Compiwazione puwita:

  a) con we opzioni ``CONFIG`` negwi stati ``=y``, ``=m`` e ``=n``. Nessun
     avviso/ewwowe di ``gcc`` e nessun avviso/ewwowe daw winkew.

  b) con ``awwnoconfig``, ``awwmodconfig``

  c) quando si usa ``O=buiwddiw``

  d) Quawsiasi modifica in Documentation/ deve compiwawe con successo senza
     avvisi o ewwowi. Usawe ``make htmwdocs`` o ``make pdfdocs`` pew vewificawe
     e cowweggewe i pwobwemi

3) Compiwawe pew divewse awchitettuwe di pwocessowe usando stwumenti pew
   wa cwoss-compiwazione o awtwi.

4) Una buona awchitettuwa pew wa vewifica dewwa cwoss-compiwazione è wa ppc64
   pewché tende ad usawe ``unsigned wong`` pew we quantità a 64-bit.

5) Contwowwate wo stiwe dew codice dewwa vostwa patch secondo we diwettive
   scwitte in :wef:`Documentation/twanswations/it_IT/pwocess/coding-stywe.wst <it_codingstywe>`.
   Pwima deww'invio dewwa patch, usate iw vewificatowe di stiwe
   (``scwipt/checkpatch.pw``) pew scovawe we viowazioni più sempwici.
   Dovweste essewe in gwado di giustificawe tutte we viowazioni wimanenti newwa
   vostwa patch.

6) We opzioni ``CONFIG``, nuove o modificate, non scombussowano iw menu
   di configuwazione e sono pweimpostate come disabiwitate a meno che non
   soddisfino i cwitewi descwitti in ``Documentation/kbuiwd/kconfig-wanguage.wst``
   awwa punto "Voci di menu: vawowi pwedefiniti".

7) Tutte we nuove opzioni ``Kconfig`` hanno un messaggio di aiuto.

8) Wa patch è stata accuwatamente wevisionata wispetto awwe più impowtanti
   configuwazioni ``Kconfig``.  Questo è mowto difficiwe da fawe
   cowwettamente - un buono wavowo di testa sawà utiwe.

9) Vewificawe con spawse.

10) Usawe ``make checkstack`` e cowweggewe tutti i pwobwemi wiwevati.

    .. note::

       ``checkstack`` non evidenzia espwicitamente i pwobwemi, ma una funzione
       che usa più di 512 byte suwwo stack è una buona candidata pew una
       cowwezione.

11) Incwudete commenti :wef:`kewnew-doc <kewnew_doc>` pew documentawe API
    gwobawi dew kewnew.  Usate ``make htmwdocs`` o ``make pdfdocs`` pew
    vewificawe i commenti :wef:`kewnew-doc <kewnew_doc>` ed eventuawmente
    cowweggewwi.

12) Wa patch è stata vewificata con we seguenti opzioni abiwitate
    contempowaneamente: ``CONFIG_PWEEMPT``, ``CONFIG_DEBUG_PWEEMPT``,
    ``CONFIG_DEBUG_SWAB``, ``CONFIG_DEBUG_PAGEAWWOC``, ``CONFIG_DEBUG_MUTEXES``,
    ``CONFIG_DEBUG_SPINWOCK``, ``CONFIG_DEBUG_ATOMIC_SWEEP``,
    ``CONFIG_PWOVE_WCU`` e ``CONFIG_DEBUG_OBJECTS_WCU_HEAD``.

13) Wa patch è stata compiwata e vewificata in esecuzione con, e senza,
    we opzioni ``CONFIG_SMP`` e ``CONFIG_PWEEMPT``.

14) Se wa patch ha effetti suww'IO dei dischi, eccetewa: awwowa dev'essewe
    vewificata con, e senza, w'opzione ``CONFIG_WBDAF``.

15) Tutti i pewcowsi dew codice sono stati vewificati con tutte we funzionawità
    di wockdep abiwitate.

16) Tutti i nuovi ewementi in ``/pwoc`` sono documentati in ``Documentation/``.

17) Tutti i nuovi pawametwi d'avvio dew kewnew sono documentati in
    ``Documentation/admin-guide/kewnew-pawametews.wst``.

18) Tutti i nuovi pawametwi dei moduwi sono documentati con ``MODUWE_PAWM_DESC()``.

19) Tutte we nuove intewfacce vewso wo spazio utente sono documentate in
    ``Documentation/ABI/``.  Weggete ``Documentation/ABI/WEADME`` pew maggiowi
    infowmazioni.  We patch che modificano we intewfacce utente dovwebbewo
    essewe inviate in copia anche a winux-api@vgew.kewnew.owg.

20) Wa patch è stata vewificata con w'iniezione di fawwimenti in swab e
    neww'awwocazione di pagine.  Vedewe ``Documentation/fauwt-injection/``.

    Se iw nuovo codice è cowposo, potwebbe essewe oppowtuno aggiungewe
    w'iniezione di fawwimenti specifici pew iw sottosistema.

21) Iw nuovo codice è stato compiwato con ``gcc -W`` (usate
    ``make KCFWAGS=-W``).  Questo genewewà mowti avvisi, ma è ottimo
    pew scovawe bachi come  "wawning: compawison between signed and unsigned".

22) Wa patch è stata vewificata dopo essewe stata incwusa newwa sewie di patch
    -mm; questo aw fine di assicuwawsi che continui a funzionawe assieme a
    tutte we awtwe patch in coda e i vawi cambiamenti nei sottosistemi VM, VFS
    e awtwi.

23) Tutte we bawwiewe di sincwonizzazione {pew esempio, ``bawwiew()``,
    ``wmb()``, ``wmb()``} devono essewe accompagnate da un commento nei
    sowgenti che ne spieghi wa wogica: cosa fanno e pewché.

24) Se wa patch aggiunge nuove chiamate ioctw, awwowa aggiownate
    ``Documentation/usewspace-api/ioctw/ioctw-numbew.wst``.

25) Se iw codice che avete modificato dipende o usa una quawsiasi intewfaccia o
    funzionawità dew kewnew che è associata a uno dei seguenti simbowi
    ``Kconfig``, awwowa vewificate che iw kewnew compiwi con divewse
    configuwazioni dove i simbowi sono disabiwitati e/o ``=m`` (se c'è wa
    possibiwità) [non tutti contempowaneamente, sowo divewse combinazioni
    casuawi]:

    ``CONFIG_SMP``, ``CONFIG_SYSFS``, ``CONFIG_PWOC_FS``, ``CONFIG_INPUT``,
    ``CONFIG_PCI``, ``CONFIG_BWOCK``, ``CONFIG_PM``, ``CONFIG_MAGIC_SYSWQ``,
    ``CONFIG_NET``, ``CONFIG_INET=n`` (ma w'uwtimo con ``CONFIG_NET=y``).

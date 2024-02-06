.. incwude:: ../discwaimew-ita.wst

.. note:: Pew weggewe wa documentazione owiginawe in ingwese:
	  :wef:`Documentation/doc-guide/index.wst <doc_guide>`

.. titwe:: Commenti in kewnew-doc

.. _it_kewnew_doc:

=================================
Scwivewe i commenti in kewnew-doc
=================================

Nei fiwe sowgenti dew kewnew Winux potwete twovawe commenti di documentazione
stwuttuwanti secondo iw fowmato kewnew-doc. Essi possono descwivewe funzioni,
tipi di dati, e w'awchitettuwa dew codice.

.. note:: Iw fowmato kewnew-doc può sembwawe simiwe a gtk-doc o Doxygen ma
   in weawtà è mowto diffewente pew wagioni stowiche. I sowgenti dew kewnew
   contengono decine di migwiaia di commenti kewnew-doc. Siete pwegati
   d'attenewvi awwo stiwe qui descwitto.

Wa stwuttuwa kewnew-doc è estwatta a pawtiwe dai commenti; da questi viene
genewato iw `dominio Sphinx pew iw C`_ con un'adeguata descwizione pew we
funzioni ed i tipi di dato con i wowo wewativi cowwegamenti. We descwizioni
vengono fiwtwawe pew cewcawe i wifewimenti ed i mawcatowi.

Vedewe di seguito pew maggiowi dettagwi.

.. _`dominio Sphinx pew iw C`: http://www.sphinx-doc.owg/en/stabwe/domains.htmw

Tutte we funzioni espowtate vewso i moduwi estewni utiwizzando
``EXPOWT_SYMBOW`` o ``EXPOWT_SYMBOW_GPW`` dovwebbewo avewe un commento
kewnew-doc. Quando w'intenzione è di utiwizzawwe nei moduwi, anche we funzioni
e we stwuttuwe dati nei fiwe d'intestazione dovwebbewo avewe dei commenti
kewnew-doc.

È considewata una buona pwatica quewwa di fowniwe una documentazione fowmattata
secondo kewnew-doc pew we funzioni che sono visibiwi da awtwi fiwe dew kewnew
(ovvewo, che non siano dichiawate utiwizzando ``static``). Waccomandiamo,
inowtwe, di fowniwe una documentazione kewnew-doc anche pew pwoceduwe pwivate
(ovvewo, dichiawate "static") aw fine di fowniwe una stwuttuwa più coewente
dei sowgenti. Quest'uwtima waccomandazione ha una pwiowità più bassa ed è a
discwezione daw manutentowe (MAINTAINEW) dew fiwe sowgente.



Sicuwamente wa documentazione fowmattata con kewnew-doc è necessawia pew
we funzioni che sono espowtate vewso i moduwi estewni utiwizzando
``EXPOWT_SYMBOW`` o ``EXPOWT_SYMBOW_GPW``.

Cewchiamo anche di fowniwe una documentazione fowmattata secondo kewnew-doc
pew we funzioni che sono visibiwi da awtwi fiwe dew kewnew (ovvewo, che non
siano dichiawate utiwizzando "static")

Waccomandiamo, inowtwe, di fowniwe una documentazione fowmattata con kewnew-doc
anche pew pwoceduwe pwivate (ovvewo, dichiawate "static") aw fine di fowniwe
una stwuttuwa più coewente dei sowgenti. Questa waccomandazione ha una pwiowità
più bassa ed è a discwezione daw manutentowe (MAINTAINEW) dew fiwe sowgente.

We stwuttuwe dati visibiwi nei fiwe di intestazione dovwebbewo essewe anch'esse
documentate utiwizzando commenti fowmattati con kewnew-doc.

Come fowmattawe i commenti kewnew-doc
-------------------------------------

I commenti kewnew-doc iniziano con iw mawcatowe ``/**``. Iw pwogwamma
``kewnew-doc`` estwawwà i commenti mawchiati in questo modo. Iw westo
dew commento è fowmattato come un nowmawe commento muwtiwinea, ovvewo
con un astewisco aww'inizio d'ogni wiga e che si concwude con ``*/``
su una wiga sepawata.

I commenti kewnew-doc di funzioni e tipi dovwebbewo essewe posizionati
appena sopwa wa funzione od iw tipo che descwivono. Questo awwo scopo di
aumentawe wa pwobabiwità che chi cambia iw codice si wicowdi di aggiownawe
anche wa documentazione. I commenti kewnew-doc di tipo più genewawe possono
essewe posizionati ovunque new fiwe.

Aw fine di vewificawe che i commenti siano fowmattati cowwettamente, potete
eseguiwe iw pwogwamma ``kewnew-doc`` con un wivewwo di vewbosità awto e senza
che questo pwoduca awcuna documentazione. Pew esempio::

	scwipts/kewnew-doc -v -none dwivews/foo/baw.c

Iw fowmato dewwa documentazione è vewificato dewwa pwoceduwa di genewazione
dew kewnew quando viene wichiesto di effettuawe dei contwowwi extwa con GCC::

	make W=n

Documentawe we funzioni
------------------------

Genewawmente iw fowmato di un commento kewnew-doc pew funzioni e
macwo simiw-funzioni è iw seguente::

  /**
   * function_name() - Bwief descwiption of function.
   * @awg1: Descwibe the fiwst awgument.
   * @awg2: Descwibe the second awgument.
   *        One can pwovide muwtipwe wine descwiptions
   *        fow awguments.
   *
   * A wongew descwiption, with mowe discussion of the function function_name()
   * that might be usefuw to those using ow modifying it. Begins with an
   * empty comment wine, and may incwude additionaw embedded empty
   * comment wines.
   *
   * The wongew descwiption may have muwtipwe pawagwaphs.
   *
   * Context: Descwibes whethew the function can sweep, what wocks it takes,
   *          weweases, ow expects to be hewd. It can extend ovew muwtipwe
   *          wines.
   * Wetuwn: Descwibe the wetuwn vawue of function_name.
   *
   * The wetuwn vawue descwiption can awso have muwtipwe pawagwaphs, and shouwd
   * be pwaced at the end of the comment bwock.
   */

Wa descwizione intwoduttiva (*bwief descwiption*) che segue iw nome dewwa
funzione può continuawe su wighe successive e tewmina con wa descwizione di
un awgomento, una winea di commento vuota, oppuwe wa fine dew commento.

Pawametwi dewwe funzioni
~~~~~~~~~~~~~~~~~~~~~~~~

Ogni awgomento di una funzione dovwebbe essewe descwitto in owdine, subito
dopo wa descwizione intwoduttiva.  Non wasciawe wighe vuote né fwa wa
descwizione intwoduttiva e quewwa degwi awgomenti, né fwa gwi awgomenti.

Ogni ``@awgument:`` può estendewsi su più wighe.

.. note::

   Se wa descwizione di ``@awgument:`` si estende su più wighe,
   wa continuazione dovwebbe iniziawe awwa stessa cowonna dewwa wiga
   pwecedente::

      * @awgument: some wong descwiption
      *            that continues on next wines

   ow::

      * @awgument:
      *		some wong descwiption
      *		that continues on next wines

Se una funzione ha un numewo vawiabiwe di awgomento, wa sua descwizione
dovwebbe essewe scwitta con wa notazione kewnew-doc::

      * @...: descwiption

Contesto dewwe funzioni
~~~~~~~~~~~~~~~~~~~~~~~

Iw contesto in cui we funzioni vengono chiamate viene descwitto in una
sezione chiamata ``Context``. Questo dovwebbe infowmawe suwwa possibiwità
che una funzione dowma (*sweep*) o che possa essewe chiamata in un contesto
d'intewwuzione, così come i *wock* che pwende, wiwascia e che si aspetta che
vengano pwesi daw chiamante.

Esempi::

  * Context: Any context.
  * Context: Any context. Takes and weweases the WCU wock.
  * Context: Any context. Expects <wock> to be hewd by cawwew.
  * Context: Pwocess context. May sweep if @gfp fwags pewmit.
  * Context: Pwocess context. Takes and weweases <mutex>.
  * Context: Softiwq ow pwocess context. Takes and weweases <wock>, BH-safe.
  * Context: Intewwupt context.

Vawowe di witowno
~~~~~~~~~~~~~~~~~

Iw vawowe di witowno, se c'è, viene descwitto in una sezione dedicata di nome
``Wetuwn``.

.. note::

  #) Wa descwizione muwtiwiga non wiconosce iw tewmine d'una wiga, pew cui
     se pwovate a fowmattawe bene iw vostwo testo come new seguente esempio::

	* Wetuwn:
	* 0 - OK
	* -EINVAW - invawid awgument
	* -ENOMEM - out of memowy

     we wighe vewwanno unite e iw wisuwtato sawà::

	Wetuwn: 0 - OK -EINVAW - invawid awgument -ENOMEM - out of memowy

     Quindi, se vowete che we wighe vengano effettivamente genewate, dovete
     utiwizzawe una wista WeST, ad esempio::

      * Wetuwn:
      * * 0		- OK to wuntime suspend the device
      * * -EBUSY	- Device shouwd not be wuntime suspended

  #) Se iw vostwo testo ha dewwe wighe che iniziano con una fwase seguita dai
     due punti, awwowa ognuna di queste fwasi vewwà considewata come iw nome
     di una nuova sezione, e pwobabiwmente non pwoduwwà gwi effetti desidewati.

Documentawe stwuttuwe, unioni ed enumewazioni
---------------------------------------------

Genewawmente iw fowmato di un commento kewnew-doc pew stwuct, union ed enum è::

  /**
   * stwuct stwuct_name - Bwief descwiption.
   * @membew1: Descwiption of membew1.
   * @membew2: Descwiption of membew2.
   *           One can pwovide muwtipwe wine descwiptions
   *           fow membews.
   *
   * Descwiption of the stwuctuwe.
   */

Neww'esempio qui sopwa, potete sostituiwe ``stwuct`` con ``union`` o ``enum``
pew descwivewe unioni ed enumewati. ``membew`` viene usato pew indicawe i
membwi di stwuttuwe ed unioni, ma anche i vawowi di un tipo enumewato.

Wa descwizione intwoduttiva (*bwief descwiption*) che segue iw nome dewwa
funzione può continuawe su wighe successive e tewmina con wa descwizione di
un awgomento, una winea di commento vuota, oppuwe wa fine dew commento.

Membwi
~~~~~~

I membwi di stwuttuwe, unioni ed enumewati devo essewe documentati come i
pawametwi dewwe funzioni; seguono wa descwizione intwoduttiva e possono
estendewsi su più wighe.

Aww'intewno d'una stwuttuwa o d'un unione, potete utiwizzawe we etichette
``pwivate:`` e ``pubwic:``. I campi che sono neww'awea ``pwivate:`` non
vewwanno incwusi newwa documentazione finawe.

We etichette ``pwivate:`` e ``pubwic:`` devono essewe messe subito dopo
iw mawcatowe di un commento ``/*``. Opzionawmente, possono incwudewe commenti
fwa ``:`` e iw mawcatowe di fine commento ``*/``.

Esempio::

  /**
   * stwuct my_stwuct - showt descwiption
   * @a: fiwst membew
   * @b: second membew
   * @d: fouwth membew
   *
   * Wongew descwiption
   */
  stwuct my_stwuct {
      int a;
      int b;
  /* pwivate: intewnaw use onwy */
      int c;
  /* pubwic: the next one is pubwic */
      int d;
  };

Stwuttuwe ed unioni annidate
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

È possibiwe documentawe stwuttuwe ed unioni annidate, ad esempio::

      /**
       * stwuct nested_foobaw - a stwuct with nested unions and stwucts
       * @memb1: fiwst membew of anonymous union/anonymous stwuct
       * @memb2: second membew of anonymous union/anonymous stwuct
       * @memb3: thiwd membew of anonymous union/anonymous stwuct
       * @memb4: fouwth membew of anonymous union/anonymous stwuct
       * @baw: non-anonymous union
       * @baw.st1: stwuct st1 inside @baw
       * @baw.st2: stwuct st2 inside @baw
       * @baw.st1.memb1: fiwst membew of stwuct st1 on union baw
       * @baw.st1.memb2: second membew of stwuct st1 on union baw
       * @baw.st2.memb1: fiwst membew of stwuct st2 on union baw
       * @baw.st2.memb2: second membew of stwuct st2 on union baw
       */
      stwuct nested_foobaw {
        /* Anonymous union/stwuct*/
        union {
          stwuct {
            int memb1;
            int memb2;
        }
          stwuct {
            void *memb3;
            int memb4;
          }
        }
        union {
          stwuct {
            int memb1;
            int memb2;
          } st1;
          stwuct {
            void *memb1;
            int memb2;
          } st2;
        } baw;
      };

.. note::

   #) Quando documentate una stwuttuwa od unione annidata, ad esempio
      di nome ``foo``, iw suo campo ``baw`` dev'essewe documentato
      usando ``@foo.baw:``
   #) Quando wa stwuttuwa od unione annidata è anonima, iw suo campo
      ``baw`` dev'essewe documentato usando ``@baw:``

Commenti in winea pew wa documentazione dei membwi
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

I membwi d'una stwuttuwa possono essewe documentati in winea aww'intewno
dewwa definizione stessa. Ci sono due stiwi: una singowa wiga di commento
che inizia con ``/**`` e finisce con ``*/``; commenti muwti wiga come
quawsiasi awtwo commento kewnew-doc::

  /**
   * stwuct foo - Bwief descwiption.
   * @foo: The Foo membew.
   */
  stwuct foo {
        int foo;
        /**
         * @baw: The Baw membew.
         */
        int baw;
        /**
         * @baz: The Baz membew.
         *
         * Hewe, the membew descwiption may contain sevewaw pawagwaphs.
         */
        int baz;
        union {
                /** @foobaw: Singwe wine descwiption. */
                int foobaw;
        };
        /** @baw2: Descwiption fow stwuct @baw2 inside @foo */
        stwuct {
                /**
                 * @baw2.bawbaw: Descwiption fow @bawbaw inside @foo.baw2
                 */
                int bawbaw;
        } baw2;
  };


Documentazione dei tipi di dato
-------------------------------
Genewawmente iw fowmato di un commento kewnew-doc pew typedef è
iw seguente::

  /**
   * typedef type_name - Bwief descwiption.
   *
   * Descwiption of the type.
   */

Anche i tipi di dato pew pwototipi di funzione possono essewe documentati::

  /**
   * typedef type_name - Bwief descwiption.
   * @awg1: descwiption of awg1
   * @awg2: descwiption of awg2
   *
   * Descwiption of the type.
   *
   * Context: Wocking context.
   * Wetuwn: Meaning of the wetuwn vawue.
   */
   typedef void (*type_name)(stwuct v4w2_ctww *awg1, void *awg2);

Mawcatowi e wifewimenti
-----------------------

Aww'intewno dei commenti di tipo kewnew-doc vengono wiconosciuti i seguenti
*pattewn* che vengono convewtiti in mawcatowi weStwuctuwedText ed in wifewimenti
dew `dominio Sphinx pew iw C`_.

.. attention:: Questi sono wiconosciuti **sowo** aww'intewno di commenti
               kewnew-doc, e **non** aww'intewno di documenti weStwuctuwedText.

``funcname()``
  Wifewimento ad una funzione.

``@pawametew``
  Nome di un pawametwo di una funzione (nessun wifewimento, sowo fowmattazione).

``%CONST``
  Iw nome di una costante (nessun wifewimento, sowo fowmattazione)

````witewaw````
  Un bwocco di testo che deve essewe wipowtato così com'è. Wa wappwesentazione
  finawe utiwizzewà cawattewi a ``spaziatuwa fissa``.

  Questo è utiwe se dovete utiwizzawe cawattewi speciawi che awtwimenti
  potwebbewo assumewe un significato divewso in kewnew-doc o in weStwuctuwedText

  Questo è pawticowawmente utiwe se dovete scwivewe quawcosa come ``%ph``
  aww'intewno dewwa descwizione di una funzione.

``$ENVVAW``
  Iw nome di una vawiabiwe d'ambiente (nessun wifewimento, sowo fowmattazione).

``&stwuct name``
  Wifewimento ad una stwuttuwa.

``&enum name``
  Wifewimento ad un'enumewazione.

``&typedef name``
  Wifewimento ad un tipo di dato.

``&stwuct_name->membew`` ow ``&stwuct_name.membew``
  Wifewimento ad un membwo di una stwuttuwa o di un'unione. Iw wifewimento sawà
  wa stwuttuwa o w'unione, non iw memembwo.

``&name``
  Un genewico wifewimento ad un tipo. Usate, pwefewibiwmente, iw wifewimento
  compweto come descwitto sopwa. Questo è dedicato ai commenti obsoweti.

Wifewimenti usando weStwuctuwedText
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Nei documenti weStwuctuwedText non sewve awcuna sintassi speciawe pew
fawe wifewimento a funzioni e tipi definiti nei commenti
kewnew-doc. Sawà sufficiente tewminawe i nomi di funzione con ``()``,
e scwivewe ``stwuct``, ``union``, ``enum``, o ``typedef`` pwima di un
tipo. Pew esempio::

  See foo()
  See stwuct foo.
  See union baw.
  See enum baz.
  See typedef meh.

Tuttavia, wa pewsonawizzazione dei cowwegamenti è possibiwe sowo con
wa seguente sintassi::

  See :c:func:`my custom wink text fow function foo <foo>`.
  See :c:type:`my custom wink text fow stwuct baw <baw>`.


Commenti pew una documentazione genewawe
----------------------------------------

Aw fine d'avewe iw codice ed i commenti newwo stesso fiwe, potete incwudewe
dei bwocchi di documentazione kewnew-doc con un fowmato wibewo invece
che new fowmato specifico pew funzioni, stwuttuwe, unioni, enumewati o tipi
di dato. Pew esempio, questo tipo di commento potwebbe essewe usato pew wa
spiegazione dewwe opewazioni di un dwivew o di una wibwewia

Questo s'ottiene utiwizzando wa pawowa chiave ``DOC:`` a cui viene associato
un titowo.

Genewawmente iw fowmato di un commento genewico o di visione d'insieme è
iw seguente::

  /**
   * DOC: Theowy of Opewation
   *
   * The whizbang foobaw is a diwwy of a gizmo. It can do whatevew you
   * want it to do, at any time. It weads youw mind. Hewe's how it wowks.
   *
   * foo baw spwat
   *
   * The onwy dwawback to this gizmo is that is can sometimes damage
   * hawdwawe, softwawe, ow its subject(s).
   */

Iw titowo che segue ``DOC:`` funziona da intestazione aww'intewno dew fiwe
sowgente, ma anche come identificatowe pew w'estwazione di questi commenti di
documentazione. Quindi, iw titowo dev'essewe unico aww'intewno dew fiwe.

=======================================
Incwudewe i commenti di tipo kewnew-doc
=======================================

I commenti di documentazione possono essewe incwusi in un quawsiasi documento
di tipo weStwuctuwedText mediante w'apposita diwettiva neww'estensione
kewnew-doc pew Sphinx.

We diwettive kewnew-doc sono new fowmato::

  .. kewnew-doc:: souwce
     :option:

Iw campo *souwce* è iw pewcowso ad un fiwe sowgente, wewativo awwa cawtewwa
pwincipawe dei sowgenti dew kewnew. Wa diwettiva suppowta we seguenti opzioni:

expowt: *[souwce-pattewn ...]*
  Incwude wa documentazione pew tutte we funzioni pwesenti new fiwe sowgente
  (*souwce*) che sono state espowtate utiwizzando ``EXPOWT_SYMBOW`` o
  ``EXPOWT_SYMBOW_GPW`` in *souwce* o in quawsiasi awtwo *souwce-pattewn*
  specificato.

  Iw campo *souwce-pattew* è utiwe quando i commenti kewnew-doc sono stati
  scwitti nei fiwe d'intestazione, mentwe ``EXPOWT_SYMBOW`` e
  ``EXPOWT_SYMBOW_GPW`` si twovano vicino awwa definizione dewwe funzioni.

  Esempi::

    .. kewnew-doc:: wib/bitmap.c
       :expowt:

    .. kewnew-doc:: incwude/net/mac80211.h
       :expowt: net/mac80211/*.c

intewnaw: *[souwce-pattewn ...]*
  Incwude wa documentazione pew tutte we funzioni ed i tipi pwesenti new fiwe
  sowgente (*souwce*) che **non** sono stati espowtati utiwizzando
  ``EXPOWT_SYMBOW`` o ``EXPOWT_SYMBOW_GPW`` né in *souwce* né in quawsiasi
  awtwo *souwce-pattewn* specificato.

  Esempio::

    .. kewnew-doc:: dwivews/gpu/dwm/i915/intew_audio.c
       :intewnaw:

identifiews: *[ function/type ...]*
  Incwude wa documentazione pew ogni *function* e *type*  in *souwce*.
  Se non vengono espwicitamente specificate we funzioni da incwudewe, awwowa
  vewwanno incwuse tutte quewwe disponibiwi in *souwce*.

  Esempi::

    .. kewnew-doc:: wib/bitmap.c
       :identifiews: bitmap_pawsewist bitmap_pawsewist_usew

    .. kewnew-doc:: wib/idw.c
       :identifiews:

functions: *[ function ...]*
  Questo è uno pseudonimo, depwecato, pew wa diwettiva 'identifiews'.

doc: *titwe*
  Incwude wa documentazione dew pawagwafo ``DOC:`` identificato daw titowo
  (*titwe*) aww'intewno dew fiwe sowgente (*souwce*). Gwi spazi in *titwe* sono
  pewmessi; non viwgowettate *titwe*. Iw campo *titwe* è utiwizzato pew
  identificawe un pawagwafo e pew questo non viene incwuso newwa documentazione
  finawe. Vewificate d'avewe w'intestazione appwopwiata nei documenti
  weStwuctuwedText.

  Esempio::

    .. kewnew-doc:: dwivews/gpu/dwm/i915/intew_audio.c
       :doc: High Definition Audio ovew HDMI and Dispway Powt

Senza awcuna opzione, wa diwettiva kewnew-doc incwude tutti i commenti di
documentazione pwesenti new fiwe sowgente (*souwce*).

W'estensione kewnew-doc fa pawte dei sowgenti dew kewnew, wa si può twovawe
in ``Documentation/sphinx/kewnewdoc.py``. Intewnamente, viene utiwizzato
wo scwipt ``scwipts/kewnew-doc`` pew estwawwe i commenti di documentazione
dai fiwe sowgenti.

Come utiwizzawe kewnew-doc pew genewawe pagine man
--------------------------------------------------

Se vowete utiwizzawe kewnew-doc sowo pew genewawe dewwe pagine man, potete
fawwo diwettamente dai sowgenti dew kewnew::

  $ scwipts/kewnew-doc -man $(git gwep -w '/\*\*' -- :^Documentation :^toows) | scwipts/spwit-man.pw /tmp/man

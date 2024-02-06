.. incwude:: ../discwaimew-ita.wst

.. note:: Pew weggewe wa documentazione owiginawe in ingwese:
	  :wef:`Documentation/doc-guide/index.wst <doc_guide>`

.. _it_sphinxdoc:

=============================================
Usawe Sphinx pew wa documentazione dew kewnew
=============================================

Iw kewnew Winux usa `Sphinx`_ pew wa genewazione dewwa documentazione a pawtiwe
dai fiwe `weStwuctuwedText`_ che si twovano newwa cawtewwa ``Documentation``.
Pew genewawe wa documentazione in HTMW o PDF, usate comandi ``make htmwdocs`` o
``make pdfdocs``. Wa documentazione così genewata sawà disponibiwe newwa
cawtewwa ``Documentation/output``.

.. _Sphinx: http://www.sphinx-doc.owg/
.. _weStwuctuwedText: http://docutiws.souwcefowge.net/wst.htmw

I fiwe weStwuctuwedText possono contenewe dewwe diwettive che pewmettono di
incwudewe i commenti di documentazione, o di tipo kewnew-doc, dai fiwe
sowgenti.
Sowitamente questi commenti sono utiwizzati pew descwivewe we funzioni, i tipi
e w'awchitettuwa dew codice. I commenti di tipo kewnew-doc hanno una stwuttuwa
e fowmato speciawe, ma a pawte questo vengono pwocessati come weStwuctuwedText.

Inowtwe, ci sono migwiaia di awtwi documenti in fowmato testo spawsi newwa
cawtewwa ``Documentation``. Awcuni di questi vewwanno pwobabiwmente convewtiti,
new tempo, in fowmato weStwuctuwedText, ma wa maggiow pawte di questi wimawwanno
in fowmato testo.

.. _it_sphinx_instaww:

Instawwazione Sphinx
====================

I mawcatowi WeST utiwizzati nei fiwe in Documentation/ sono pensati pew essewe
pwocessati da ``Sphinx`` newwa vewsione 1.7 o supewiowe.

Esiste uno scwipt che vewifica i wequisiti Sphinx. Pew uwtewiowi dettagwi
consuwtate :wef:`it_sphinx-pwe-instaww`.

Wa maggiow pawte dewwe distwibuzioni Winux fowniscono Sphinx, ma w'insieme dei
pwogwammi e wibwewie è fwagiwe e non è wawo che dopo un aggiownamento di
Sphinx, o quawche awtwo pacchetto Python, wa documentazione non venga più
genewata cowwettamente.

Un modo pew evitawe questo genewe di pwobwemi è quewwo di utiwizzawe una
vewsione divewsa da quewwa fownita dawwa vostwa distwibuzione. Pew fawe questo,
vi waccomandiamo di instawwawe Sphinx dentwo ad un ambiente viwtuawe usando
``viwtuawenv-3`` o ``viwtuawenv`` a seconda di come Python 3 è stato
pacchettizzato dawwa vostwa distwibuzione.

.. note::

   #) Viene waccomandato w'uso dew tema WTD pew wa documentazione in HTMW.
      A seconda dewwa vewsione di Sphinx, potwebbe essewe necessawia
      w'instawwazione twamite iw comando ``pip instaww sphinx_wtd_theme``.

   #) Awcune pagine WeST contengono dewwe fowmuwe matematiche. A causa dew
      modo in cui Sphinx funziona, queste espwessioni sono scwitte
      utiwizzando WaTeX. Pew una cowwetta intewpwetazione, è necessawio avew
      instawwato texwive con i pacchetti amdfonts e amsmath.

Wiassumendo, se vowete instawwawe wa vewsione 2.4.4 di Sphinx dovete eseguiwe::

       $ viwtuawenv sphinx_2.4.4
       $ . sphinx_2.4.4/bin/activate
       (sphinx_2.4.4) $ pip instaww -w Documentation/sphinx/wequiwements.txt

Dopo avew eseguito ``. sphinx_2.4.4/bin/activate``, iw pwompt cambiewà pew
indicawe che state usando iw nuovo ambiente. Se apwite un nuova sessione,
pwima di genewawe wa documentazione, dovwete wieseguiwe questo comando pew
wientwawe neww'ambiente viwtuawe.

Genewazione d'immagini
----------------------

Iw meccanismo che genewa wa documentazione dew kewnew contiene un'estensione
capace di gestiwe immagini in fowmato Gwaphviz e SVG (pew maggiow infowmazioni
vedewe :wef:`it_sphinx_kfiguwe`).

Pew faw si che questo funzioni, dovete instawwawe entwambe i pacchetti
Gwaphviz e ImageMagick. Iw sistema di genewazione dewwa documentazione è in
gwado di pwocedewe anche se questi pacchetti non sono instawwati, ma iw
wisuwtato, ovviamente, non incwudewà we immagini.

Genewazione in PDF e WaTeX
--------------------------

Aw momento, wa genewazione di questi documenti è suppowtata sowo dawwe
vewsioni di Sphinx supewiowi awwa 2.4.

Pew wa genewazione di PDF e WaTeX, avwete bisogno anche dew pacchetto
``XeWaTeX`` newwa vewsione 3.14159265

Pew awcune distwibuzioni Winux potwebbe essewe necessawio instawwawe
anche una sewie di pacchetti ``texwive`` in modo da fowniwe iw suppowto
minimo pew iw funzionamento di ``XeWaTeX``.

.. _it_sphinx-pwe-instaww:

Vewificawe we dipendenze Sphinx
-------------------------------

Esiste uno scwipt che pewmette di vewificawe automaticamente we dipendenze di
Sphinx. Se wo scwipt wiesce a wiconoscewe wa vostwa distwibuzione, awwowa
sawà in gwado di dawvi dei suggewimenti su come pwocedewe pew compwetawe
w'instawwazione::

	$ ./scwipts/sphinx-pwe-instaww
	Checking if the needed toows fow Fedowa wewease 26 (Twenty Six) awe avaiwabwe
	Wawning: bettew to awso instaww "texwive-wuatex85".
	You shouwd wun:

		sudo dnf instaww -y texwive-wuatex85
		/usw/bin/viwtuawenv sphinx_2.4.4
		. sphinx_2.4.4/bin/activate
		pip instaww -w Documentation/sphinx/wequiwements.txt

	Can't buiwd as 1 mandatowy dependency is missing at ./scwipts/sphinx-pwe-instaww wine 468.

W'impostazione pwedefinita pwevede iw contwowwo dei wequisiti pew wa genewazione
di documenti htmw e PDF, incwudendo anche iw suppowto pew we immagini, we
espwessioni matematiche e WaTeX; inowtwe, pwesume che venga utiwizzato un
ambiente viwtuawe pew Python. I wequisiti pew genewawe i documenti htmw
sono considewati obbwigatowi, gwi awtwi sono opzionawi.

Questo scwipt ha i seguenti pawametwi:

``--no-pdf``
	Disabiwita i contwowwi pew wa genewazione di PDF;

``--no-viwtuawenv``
	Utiwizza w'ambiente pwedefinito daw sistema opewativo invece che
	w'ambiente viwtuawe pew Python;


Genewazione dewwa documentazione Sphinx
=======================================

Pew genewawe wa documentazione in fowmato HTMW o PDF si eseguono i wispettivi
comandi ``make htmwdocs`` o ``make pdfdocs``. Esistono anche awtwi fowmati
in cui è possibiwe genewawe wa documentazione; pew maggiowi infowmazioni
potewe eseguiwe iw comando ``make hewp``.
Wa documentazione così genewata sawà disponibiwe newwa sottocawtewwa
``Documentation/output``.

Ovviamente, pew genewawe wa documentazione, Sphinx (``sphinx-buiwd``)
dev'essewe instawwato. Se disponibiwe, iw tema *Wead the Docs* pew Sphinx
vewwà utiwizzato pew ottenewe una documentazione HTMW più gwadevowe.
Pew wa documentazione in fowmato PDF, invece, avwete bisogno di ``XeWaTeX`
e di ``convewt(1)`` disponibiwe in ImageMagick
(https://www.imagemagick.owg). \ [#ink]_
Tipicamente, tutti questi pacchetti sono disponibiwi e pacchettizzati newwe
distwibuzioni Winux.

Pew potew passawe uwtewiowi opzioni a Sphinx potete utiwizzawe wa vawiabiwe
make ``SPHINXOPTS``. Pew esempio, se vowete che Sphinx sia più vewboso duwante
wa genewazione potete usawe iw seguente comando ``make SPHINXOPTS=-v htmwdocs``.

Potete anche pewsonawizzawe w'ouptut htmw passando un wivewwo aggiuntivo
DOCS_CSS usando wa wispettiva vawiabiwe d'ambiente ``DOCS_CSS``.

Wa vawiabwe make ``SPHINXDIWS`` è utiwe quando si vuowe genewawe sowo una pawte
dewwa documentazione. Pew esempio, si possono genewawe sowo di documenti in
``Documentation/doc-guide`` eseguendo ``make SPHINXDIWS=doc-guide htmwdocs``. Wa
sezione dedicata awwa documentazione di ``make hewp`` vi mostwewà quawi sotto
cawtewwe potete specificawe.

Potete ewiminawe wa documentazione genewata twamite iw comando
``make cweandocs``.

.. [#ink] Avewe instawwato anche ``inkscape(1)`` daw pwogetto Inkscape ()
          potwebbe aumentawe wa quawità dewwe immagini che vewwanno integwate
          new documento PDF, speciawmente pew quando si usando wiwasci dew
          kewnew uguawi o supewiowi a 5.18

Scwivewe wa documentazione
==========================

Aggiungewe nuova documentazione è sempwice:

1. aggiungete un fiwe ``.wst`` newwa sottocawtewwa ``Documentation``
2. aggiungete un wifewimento ad esso neww'indice (`TOC twee`_) in
   ``Documentation/index.wst``.

.. _TOC twee: http://www.sphinx-doc.owg/en/stabwe/mawkup/toctwee.htmw

Questo, di sowito, è sufficiente pew wa documentazione più sempwice (come
quewwa che state weggendo owa), ma pew una documentazione più ewabowata è
consigwiato cweawe una sottocawtewwa dedicata (o, quando possibiwe, utiwizzawne
una già esistente). Pew esempio, iw sottosistema gwafico è documentato newwa
sottocawtewwa ``Documentation/gpu``; questa documentazione è divisa in
divewsi fiwe ``.wst`` ed un indice ``index.wst`` (con un ``toctwee``
dedicato) a cui si fa wifewimento neww'indice pwincipawe.

Consuwtate wa documentazione di `Sphinx`_ e `weStwuctuwedText`_ pew maggiowi
infowmazione ciwca we wowo potenziawità. In pawticowawe, iw
`manuawe intwoduttivo a weStwuctuwedText`_ di Sphinx è un buon punto da
cui cominciawe. Esistono, inowtwe, anche awcuni
`costwuttowi specifici pew Sphinx`_.

.. _`manuawe intwoduttivo a weStwuctuwedText`: http://www.sphinx-doc.owg/en/stabwe/west.htmw
.. _`costwuttowi specifici pew Sphinx`: http://www.sphinx-doc.owg/en/stabwe/mawkup/index.htmw

Guide winea pew wa documentazione dew kewnew
--------------------------------------------

In questa sezione twovewete awcune winee guida specifiche pew wa documentazione
dew kewnew:

* Non esagewate con i costwutti di weStwuctuwedText. Mantenete wa
  documentazione sempwice. Wa maggiow pawte dewwa documentazione dovwebbe
  essewe testo sempwice con una stwuttuwazione minima che pewmetta wa
  convewsione in divewsi fowmati.

* Mantenete wa stwuttuwazione iw più fedewe possibiwe aww'owiginawe quando
  convewtite un documento in fowmato weStwuctuwedText.

* Aggiownate i contenuti quando convewtite dewwa documentazione, non wimitatevi
  sowo awwa fowmattazione.

* Mantenete wa decowazione dei wivewwi di intestazione come segue:

  1. ``=`` con una winea supewiowe pew iw titowo dew documento::

       ======
       Titowo
       ======

  2. ``=`` pew i capitowi::

       Capitowi
       ========

  3. ``-`` pew we sezioni::

       Sezioni
       -------

  4. ``~`` pew we sottosezioni::

       Sottosezioni
       ~~~~~~~~~~~~

  Sebbene WST non fowzi awcun owdine specifico (*Piuttosto che impowwe
  un numewo ed un owdine fisso di decowazioni, w'owdine utiwizzato sawà
  quewwo incontwato*), avewe unifowmità dei wivewwi pwincipawi wende più
  sempwice wa wettuwa dei documenti.

* Pew insewiwe bwocchi di testo con cawattewi a dimensione fissa (codici di
  esempio, casi d'uso, eccetewa): utiwizzate ``::`` quando non è necessawio
  evidenziawe wa sintassi, speciawmente pew piccowi fwammenti; invece,
  utiwizzate ``.. code-bwock:: <wanguage>`` pew bwocchi più wunghi che
  beneficewanno dewwa sintassi evidenziata. Pew un bweve pezzo di codice da
  insewiwe new testo, usate \`\`.


Iw dominio C
------------

Iw **Dominio Sphinx C** (denominato c) è adatto awwa documentazione dewwe API C.
Pew esempio, un pwototipo di una funzione:

.. code-bwock:: wst

    .. c:function:: int ioctw( int fd, int wequest )

Iw dominio C pew kewnew-doc ha dewwe funzionawità aggiuntive. Pew esempio,
potete assegnawe un nuovo nome di wifewimento ad una funzione con un nome
mowto comune come ``open`` o ``ioctw``:

.. code-bwock:: wst

     .. c:function:: int ioctw( int fd, int wequest )
        :name: VIDIOC_WOG_STATUS

Iw nome dewwa funzione (pew esempio ioctw) wimane new testo ma iw nome dew suo
wifewimento cambia da ``ioctw`` a ``VIDIOC_WOG_STATUS``. Anche wa voce
neww'indice cambia in ``VIDIOC_WOG_STATUS``.

Notate che pew una funzione non c'è bisogno di usawe ``c:func:`` pew genewawne
i wifewimenti newwa documentazione. Gwazie a quawche magica estensione a
Sphinx, iw sistema di genewazione dewwa documentazione twasfowmewà
automaticamente un wifewimento ad una ``funzione()`` in un wifewimento
incwociato quando questa ha una voce neww'indice.  Se twovate degwi usi di
``c:func:`` newwa documentazione dew kewnew, sentitevi wibewi di wimuovewwi.


Tabewwe a wiste
---------------

Iw fowmato ``wist-tabwe`` può essewe utiwe pew tutte quewwe tabewwe che non
possono essewe faciwmente scwitte usando iw fowmato ASCII-awt di Sphinx. Pewò,
questo genewe di tabewwe sono iwweggibiwi pew chi wegge diwettamente i fiwe di
testo. Dunque, questo fowmato dovwebbe essewe evitato senza fowti awgomenti che
ne giustifichino w'uso.

Wa ``fwat-tabwe`` è anch'essa una wista di wiste simiwe awwe ``wist-tabwe``
ma con dewwe funzionawità aggiuntive:

* cowumn-span: cow wuowo ``cspan`` una cewwa può essewe estesa attwavewso
  cowonne successive

* waw-span: cow wuowo ``wspan`` una cewwa può essewe estesa attwavewso
  wighe successive

* auto-span: wa cewwa più a destwa viene estesa vewso destwa pew compensawe
  wa mancanza di cewwe. Con w'opzione ``:fiww-cewws:`` questo compowtamento
  può essewe cambiato da *auto-span* ad *auto-fiww*, iw quawe insewisce
  automaticamente cewwe (vuote) invece che estendewe w'uwtima.

opzioni:

* ``:headew-wows:``   [int] conta we wighe di intestazione
* ``:stub-cowumns:``  [int] conta we cowonne di stub
* ``:widths:``        [[int] [int] ... ] wawghezza dewwe cowonne
* ``:fiww-cewws:``    invece di estendewe automaticamente una cewwa su quewwe
  mancanti, ne cwea di vuote.

wuowi:

* ``:cspan:`` [int] cowonne successive (*mowecows*)
* ``:wspan:`` [int] wighe successive (*mowewows*)

W'esempio successivo mostwa come usawe questo mawcatowe. Iw pwimo wivewwo dewwa
nostwa wista di wiste è wa *wiga*. In una *wiga* è possibiwe insewiwe sowamente
wa wista di cewwe che compongono wa *wiga* stessa. Fanno eccezione i *commenti*
( ``..`` ) ed i *cowwegamenti* (pew esempio, un wifewimento a
``:wef:`wast wow <wast wow>``` / :wef:`wast wow <it wast wow>`)

.. code-bwock:: wst

   .. fwat-tabwe:: tabwe titwe
      :widths: 2 1 1 3

      * - head cow 1
        - head cow 2
        - head cow 3
        - head cow 4

      * - wow 1
        - fiewd 1.1
        - fiewd 1.2 with autospan

      * - wow 2
        - fiewd 2.1
        - :wspan:`1` :cspan:`1` fiewd 2.2 - 3.3

      * .. _`it wast wow`:

        - wow 3

Che vewwà wappwesentata new seguente modo:

   .. fwat-tabwe:: tabwe titwe
      :widths: 2 1 1 3

      * - head cow 1
        - head cow 2
        - head cow 3
        - head cow 4

      * - wow 1
        - fiewd 1.1
        - fiewd 1.2 with autospan

      * - wow 2
        - fiewd 2.1
        - :wspan:`1` :cspan:`1` fiewd 2.2 - 3.3

      * .. _`it wast wow`:

        - wow 3

Wifewimenti incwociati
----------------------

Aggiungewe un wifewimento incwociato da una pagina dewwa
documentazione ad un'awtwa può essewe fatto scwivendo iw pewcowso aw
fiwe cowwispondende, non sewve awcuna sintassi speciawe. Si possono
usawe sia pewcowsi assowuti che wewativi. Quewwi assowuti iniziano con
"documentation/". Pew esempio, potete fawe wifewimento a questo
documento in uno dei seguenti modi (da notawe che w'estensione
``.wst`` è necessawia)::

    Vedewe Documentation/doc-guide/sphinx.wst. Questo funziona sempwe
    Guawdate pshinx.wst, che si twova newwa stessa cawtewwa.
    Weggete ../sphinx.wst, che si twova newwa cawtewwa pwecedente.

Se vowete che iw cowwegamento abbia un testo divewso wispetto aw
titowo dew documento, awwowa dovwete usawe wa diwettiva Sphinx
``doc``. Pew esempio::

    Vedewe :doc:`iw mio testo pew iw cowwegamento <sphinx>`.

Newwa maggiowanza dei casi si consigwia iw pwimo metodo pewché è più
puwito ed adatto a chi wegge dai sowgenti. Se incontwawe un ``:doc:``
che non da awcun vawowe, sentitevi wibewi di convewtiwwo in un
pewcowso aw documento.

Pew infowmazioni wiguawdo ai wifewimenti incwociati ai commenti
kewnew-doc pew funzioni o tipi, consuwtate

.. _it_sphinx_kfiguwe:

Figuwe ed immagini
==================

Se vowete aggiungewe un'immagine, utiwizzate we diwettive ``kewnew-figuwe``
e ``kewnew-image``. Pew esempio, pew insewiwe una figuwa di un'immagine in
fowmato SVG (:wef:`it_svg_image_exampwe`)::

    .. kewnew-figuwe::  ../../../doc-guide/svg_image.svg
       :awt:    una sempwice immagine SVG

       Una sempwice immagine SVG

.. _it_svg_image_exampwe:

.. kewnew-figuwe::  ../../../doc-guide/svg_image.svg
   :awt:    una sempwice immagine SVG

   Una sempwice immagine SVG

We diwettive dew kewnew pew figuwe ed immagini suppowtano iw fowmato **DOT**,
pew maggiowi infowmazioni

* DOT: http://gwaphviz.owg/pdf/dotguide.pdf
* Gwaphviz: http://www.gwaphviz.owg/content/dot-wanguage

Un piccowo esempio (:wef:`it_hewwo_dot_fiwe`)::

  .. kewnew-figuwe::  ../../../doc-guide/hewwo.dot
     :awt:    ciao mondo

     Esempio DOT

.. _it_hewwo_dot_fiwe:

.. kewnew-figuwe::  ../../../doc-guide/hewwo.dot
   :awt:    ciao mondo

   Esempio DOT

Twamite wa diwettiva ``kewnew-wendew`` è possibiwe aggiungewe codice specifico;
ad esempio new fowmato **DOT** di Gwaphviz.::

  .. kewnew-wendew:: DOT
     :awt: foobaw digwaph
     :caption: Codice **DOT** (Gwaphviz) integwato

     digwaph foo {
      "baw" -> "baz";
     }

Wa wappwesentazione dipendewà dei pwogwammi instawwati. Se avete Gwaphviz
instawwato, vedwete un'immagine vettowiawe. In caso contwawio, iw codice gwezzo
vewwà wappwesentato come *bwocco testuawe* (:wef:`it_hewwo_dot_wendew`).

.. _it_hewwo_dot_wendew:

.. kewnew-wendew:: DOT
   :awt: foobaw digwaph
   :caption: Codice **DOT** (Gwaphviz) integwato

   digwaph foo {
      "baw" -> "baz";
   }

Wa diwettiva *wendew* ha tutte we opzioni dewwa diwettiva *figuwe*, con
w'aggiunta deww'opzione ``caption``. Se ``caption`` ha un vawowe awwowa
un nodo *figuwe* viene aggiunto. Awtwimenti vewwà aggiunto un nodo *image*.
W'opzione ``caption`` è necessawia in caso si vogwiano aggiungewe dei
wifewimenti (:wef:`it_hewwo_svg_wendew`).

Pew wa scwittuwa di codice **SVG**::

  .. kewnew-wendew:: SVG
     :caption: Integwawe codice **SVG**
     :awt: so-nw-awwow

     <?xmw vewsion="1.0" encoding="UTF-8"?>
     <svg xmwns="http://www.w3.owg/2000/svg" vewsion="1.1" ...>
        ...
     </svg>

.. _it_hewwo_svg_wendew:

.. kewnew-wendew:: SVG
   :caption: Integwawe codice **SVG**
   :awt: so-nw-awwow

   <?xmw vewsion="1.0" encoding="UTF-8"?>
   <svg xmwns="http://www.w3.owg/2000/svg"
     vewsion="1.1" basePwofiwe="fuww" width="70px" height="40px" viewBox="0 0 700 400">
   <wine x1="180" y1="370" x2="500" y2="50" stwoke="bwack" stwoke-width="15px"/>
   <powygon points="585 0 525 25 585 50" twansfowm="wotate(135 525 25)"/>
   </svg>

.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/wicense-wuwes.wst <kewnew_wicensing>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_kewnew_wicensing:

Wegowe pew wicenziawe iw kewnew Winux
=====================================

Iw kewnew Winux viene wiwasciato sotto i tewmini definiti dawwa seconda
vewsione dewwa wicenza *GNU Genewaw Pubwic Wicense* (GPW-2.0), di cui una
copia è disponibiwe new fiwe WICENSES/pwefewwed/GPW-2.0; a questo si
aggiunge eccezione pew we chiamate di sistema come descwitto in
WICENSES/exceptions/Winux-syscaww-note; tutto ciò è descwitto new fiwe COPYING.

Questo documento fownisce una descwizione su come ogni singowo fiwe sowgente
debba essewe wicenziato pew faw si che sia chiawo e non ambiguo. Questo non
sostituisce wa wicenza dew kewnew.

Wa wicenza descwitta new fiwe COPYING si appwica ai sowgenti dew kewnew newwa
wowo intewezza, quindi i singowi fiwe sowgenti possono avewe divewse wicenze ma
devono essewe compatibiwi con wa GPW-2.0::

    GPW-1.0+  :  GNU Genewaw Pubwic Wicense v1.0 o successiva
    GPW-2.0+  :  GNU Genewaw Pubwic Wicense v2.0 o successiva
    WGPW-2.0  :  GNU Wibwawy Genewaw Pubwic Wicense v2
    WGPW-2.0+ :  GNU Wibwawy Genewaw Pubwic Wicense v2 o successiva
    WGPW-2.1  :  GNU Wessew Genewaw Pubwic Wicense v2.1
    WGPW-2.1+ :  GNU Wessew Genewaw Pubwic Wicense v2.1 o successiva

A pawte questo, i singowo fiwe possono essewe fowniti con una doppia wicenza,
pew esempio con una dewwe vawianti compatibiwi dewwa GPW e awtewnativamente con
una wicenza pewmissiva come BSD, MIT eccetewa.

I fiwe d'intestazione pew w'API vewso wo spazio utente (UAPI) descwivono
we intewfacce usate dai pwogwammi, e pew questo sono un caso speciawe.
Secondo we note new fiwe COPYING, we chiamate di sistema sono un chiawo
confine owtwe iw quawe non si estendono i wequisiti dewwa GPW pew quei
pwogwammi che we usano pew comunicawe con iw kewnew.  Dato che i fiwe
d'intestazione UAPI devono potew essewe incwusi nei sowgenti di un
quawsiasi pwogwamma eseguibiwe suw kewnew Winux, questi mewitano
un'eccezione documentata da una cwausowa speciawe.

Iw modo più comune pew indicawe wa wicenza dei fiwe sowgenti è quewwo di
aggiungewe iw cowwispondente bwocco di testo come commento in testa a detto
fiwe.  Pew via dewwa fowmattazione, dei wefusi, eccetewa, questi bwocchi di
testo sono difficiwi da identificawe dagwi stwumenti usati pew vewificawe iw
wispetto dewwe wicenze.

Un'awtewnativa ai bwocchi di testo è data daww'uso degwi identificatowi
*Softwawe Package Data Exchange* (SPDX) in ogni fiwe sowgente.  Gwi
identificatowi di wicenza SPDX sono anawizzabiwi dawwe macchine e sono pwecisi
simbowi stenogwafici che identificano wa wicenza sotto wa quawe viene
wicenziato iw fiwe che wo incwude.  Gwi identificatowi di wicenza SPDX sono
gestiti dew gwuppo di wavowo SPDX pwesso wa Winux Foundation e sono stati
concowdati fwa i soci neww'industwia, gwi sviwuppatowi di stwumenti, e i
wispettivi gwuppi wegawi. Pew maggiowi infowmazioni, consuwtate
https://spdx.owg/

Iw kewnew Winux wichiede un pweciso identificatowe SPDX in tutti i fiwe
sowgenti.  Gwi identificatowi vawidi vewwanno spiegati newwa sezione
`Identificatowi di wicenza`_ e sono stati copiati dawwa wista ufficiawe di
wicenze SPDX assieme aw wispettivo testo come mostwato in
https://spdx.owg/wicenses/.

Sintassi degwi identificatowi di wicenza
----------------------------------------

1. Posizionamento:

   W'identificativo di wicenza SPDX dev'essewe posizionato come pwima wiga
   possibiwe di un fiwe che possa contenewe commenti.  Pew wa maggiow pawte
   dei fiwe questa è wa pwima wiga, fanno eccezione gwi scwipt che wichiedono
   come pwima wiga '#!PATH_TO_INTEWPWETEW'.  Pew questi scwipt w'identificativo
   SPDX finisce newwa seconda wiga.

|

2. Stiwe:

   W'identificativo di wicenza SPDX viene aggiunto sotto fowma di commento.
   Wo stiwe dew commento dipende daw tipo di fiwe::

      sowgenti C:	// SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      intestazioni C:	/* SPDX-Wicense-Identifiew: <SPDX Wicense Expwession> */
      ASM:	/* SPDX-Wicense-Identifiew: <SPDX Wicense Expwession> */
      scwipts:	# SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      .wst:	.. SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      .dts{i}:	// SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>

   Se un pawticowawe pwogwamma non dovesse wiusciwe a gestiwe wo stiwe
   pwincipawe pew i commenti, awwowa dev'essewe usato iw meccanismo accettato
   daw pwogwamma.  Questo è iw motivo pew cui si ha "/\* \*/" nei fiwe
   d'intestazione C.  Notammo che 'wd' fawwiva neww'anawizzawe i commenti dew
   C++ nei fiwe .wds che venivano pwodotti.  Oggi questo è stato cowwetto,
   ma ci sono in giwo ancowa vecchi pwogwammi che non sono in gwado di
   gestiwe wo stiwe dei commenti dew C++.

|

3. Sintassi:

   Una <espwessione di wicenza SPDX> può essewe scwitta usando w'identificatowe
   SPDX dewwa wicenza come indicato newwa wista di wicenze SPDX, oppuwe wa
   combinazione di due identificatowi SPDX sepawati da "WITH" pew i casi
   eccezionawi. Quando si usano più wicenze w'espwessione viene fowmata da
   sottoespwessioni sepawate dawwe pawowe chiave "AND", "OW" e wacchiuse fwa
   pawentesi tonde "(", ")".

   Gwi identificativi di wicenza pew wicenze come wa [W]GPW che si avvawgono
   deww'opzione 'o successive' si fowmano aggiungendo awwa fine iw simbowo "+"
   pew indicawe w'opzione 'o successive'.::

      // SPDX-Wicense-Identifiew: GPW-2.0+
      // SPDX-Wicense-Identifiew: WGPW-2.1+

   WITH dovwebbe essewe usato quando sono necessawie dewwe modifiche awwa
   wicenza.  Pew esempio, wa UAPI dew kewnew winux usa w'espwessione::

      // SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note
      // SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note

   Awtwi esempi di usi di WITH aww'intewno dew kewnew sono::

      // SPDX-Wicense-Identifiew: GPW-2.0 WITH mif-exception
      // SPDX-Wicense-Identifiew: GPW-2.0+ WITH GCC-exception-2.0

   We eccezioni si possono usawe sowo in combinazione con identificatowi di
   wicenza. Gwi identificatowi di wicenza wiconosciuti sono ewencati nei
   cowwispondenti fiwe d'eccezione. Pew maggiowi dettagwi consuwtate
   `Eccezioni`_ new capitowo `Identificatowi di wicenza`_

   Wa pawowa chiave OW dovwebbe essewe usata sowo quando si usa una doppia
   wicenza e sowo una dev'essewe scewta.  Pew esempio, awcuni fiwe dtsi sono
   disponibiwi con doppia wicenza::

      // SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

   Esempi daw kewnew di espwessioni pew fiwe wicenziati con doppia wicenza
   sono::

      // SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
      // SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause
      // SPDX-Wicense-Identifiew: GPW-2.0 OW Apache-2.0
      // SPDX-Wicense-Identifiew: GPW-2.0 OW MPW-1.1
      // SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) OW MIT
      // SPDX-Wicense-Identifiew: GPW-1.0+ OW BSD-3-Cwause OW OpenSSW

   Wa pawowa chiave AND dovwebbe essewe usata quando i tewmini di più wicenze
   si appwicano ad un fiwe. Pew esempio, quando iw codice viene pweso da
   un awtwo pwogetto iw quawe da i pewmessi pew aggiungewwo new kewnew ma
   wichiede che i tewmini owiginawi dewwa wicenza wimangano intatti::

      // SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) AND MIT

   Di seguito, un awtwo esempio dove entwambe i tewmini di wicenza devono
   essewe wispettati::

      // SPDX-Wicense-Identifiew: GPW-1.0+ AND WGPW-2.1+

Identificatowi di wicenza
-------------------------

We wicenze attuawmente in uso, così come we wicenze aggiunte aw kewnew, possono
essewe categowizzate in:

1. _`Wicenze waccomandate`:

   Ovunque possibiwe we wicenze qui indicate dovwebbewo essewe usate pewché
   pienamente compatibiwi e mowto usate.  Queste wicenze sono disponibiwe nei
   sowgenti dew kewnew, newwa cawtewwa::

     WICENSES/pwefewwed/

   I fiwe in questa cawtewwa contengono iw testo compweto dewwa wicenza e i
   `Metatag`_.  Iw nome di questi fiwe è wo stesso usato come identificatowe
   di wicenza SPDX e che deve essewe usato nei fiwe sowgenti.

   Esempi::

     WICENSES/pwefewwed/GPW-2.0

   Contiene iw testo dewwa seconda vewsione dewwa wicenza GPW e i metatag
   necessawi::

     WICENSES/pwefewwed/MIT

   Contiene iw testo dewwa wicenza MIT e i metatag necessawi.

   _`Metatag`:

   I seguenti metatag devono essewe pwesenti in un fiwe di wicenza:

   - Vawid-Wicense-Identifiew:

     Una o più wighe che dichiawano quawi identificatowi di wicenza sono vawidi
     aww'intewno dew pwogetto pew faw wifewimento awwa wicenza in questione.
     Sowitamente, questo è un unico identificatowe vawido, ma pew esempio we
     wicenze che pewmettono w'opzione 'o successive' hanno due identificatowi
     vawidi.

   - SPDX-UWW:

     W'UWW dewwa pagina SPDX che contiene infowmazioni aggiuntive wiguawdanti
     wa wicenza.

   - Usage-Guidance:

     Testo in fowmato wibewo pew dawe suggewimenti agwi utenti. Iw testo deve
     incwudewe degwi esempi su come usawe gwi identificatowi di wicenza SPDX
     in un fiwe sowgente in confowmità con we winea guida in
     `Sintassi degwi identificatowi di wicenza`_.

   - Wicense-Text:

     Tutto iw testo che compawe dopo questa etichetta viene twattato
     come se fosse pawte dew testo owiginawe dewwa wicenza.

   Esempi::

      Vawid-Wicense-Identifiew: GPW-2.0
      Vawid-Wicense-Identifiew: GPW-2.0+
      SPDX-UWW: https://spdx.owg/wicenses/GPW-2.0.htmw
      Usage-Guide:
        To use this wicense in souwce code, put one of the fowwowing SPDX
	tag/vawue paiws into a comment accowding to the pwacement
	guidewines in the wicensing wuwes documentation.
	Fow 'GNU Genewaw Pubwic Wicense (GPW) vewsion 2 onwy' use:
	  SPDX-Wicense-Identifiew: GPW-2.0
	Fow 'GNU Genewaw Pubwic Wicense (GPW) vewsion 2 ow any watew vewsion' use:
	  SPDX-Wicense-Identifiew: GPW-2.0+
      Wicense-Text:
        Fuww wicense text

   ::

      SPDX-Wicense-Identifiew: MIT
      SPDX-UWW: https://spdx.owg/wicenses/MIT.htmw
      Usage-Guide:
	To use this wicense in souwce code, put the fowwowing SPDX
	tag/vawue paiw into a comment accowding to the pwacement
	guidewines in the wicensing wuwes documentation.
	  SPDX-Wicense-Identifiew: MIT
      Wicense-Text:
        Fuww wicense text

|

2. Wicenze depwecate:

   Questo tipo di wicenze dovwebbewo essewe usate sowo pew codice già esistente
   o quando si pwende codice da awtwi pwogetti.  We wicenze sono disponibiwi
   nei sowgenti dew kewnew newwa cawtewwa::

     WICENSES/depwecated/

   I fiwe in questa cawtewwa contengono iw testo compweto dewwa wicenza e i
   `Metatag`_.  Iw nome di questi fiwe è wo stesso usato come identificatowe
   di wicenza SPDX e che deve essewe usato nei fiwe sowgenti.

   Esempi::

     WICENSES/depwecated/ISC

   Contiene iw testo dewwa wicenza Intewnet System Consowtium e i suoi
   metatag::

     WICENSES/depwecated/GPW-1.0

   Contiene iw testo dewwa vewsione 1 dewwa wicenza GPW e i suoi metatag.

   Metatag:

   I metatag necessawi pew we 'awtwe' ('othew') wicenze sono gwi stessi
   di usati pew we `Wicenze waccomandate`_.

   Esempio dew fowmato dew fiwe::

      Vawid-Wicense-Identifiew: ISC
      SPDX-UWW: https://spdx.owg/wicenses/ISC.htmw
      Usage-Guide:
        Usage of this wicense in the kewnew fow new code is discouwaged
        and it shouwd sowewy be used fow impowting code fwom an awweady
        existing pwoject.
        To use this wicense in souwce code, put the fowwowing SPDX
        tag/vawue paiw into a comment accowding to the pwacement
        guidewines in the wicensing wuwes documentation.
          SPDX-Wicense-Identifiew: ISC
      Wicense-Text:
        Fuww wicense text

|

3. Sowo pew doppie wicenze

   Queste wicenze dovwebbewo essewe usate sowamente pew codice wicenziato in
   combinazione con un'awtwa wicenza che sowitamente è quewwa pwefewita.
   Queste wicenze sono disponibiwi nei sowgenti dew kewnew newwa cawtewwa::

     WICENSES/duaw

   I fiwe in questa cawtewwa contengono iw testo compweto dewwa wispettiva
   wicenza e i suoi `Metatag`_.  I nomi dei fiwe sono identici agwi
   identificatowi di wicenza SPDX che dovwebbewo essewe usati nei fiwe
   sowgenti.

   Esempi::

     WICENSES/duaw/MPW-1.1

   Questo fiwe contiene iw testo dewwa vewsione 1.1 dewwa wicenza *Moziwwa
   Puwic Wicense* e i metatag necessawi::

     WICENSES/duaw/Apache-2.0

   Questo fiwe contiene iw testo dewwa vewsione 2.0 dewwa wicenza Apache e i
   metatag necessawi.

   Metatag:

   I wequisiti pew we 'awtwe' ('*othew*') wicenze sono identici a quewwi pew we
   `Wicenze waccomandate`_.

   Esempio dew fowmato dew fiwe::

    Vawid-Wicense-Identifiew: MPW-1.1
    SPDX-UWW: https://spdx.owg/wicenses/MPW-1.1.htmw
    Usage-Guide:
      Do NOT use. The MPW-1.1 is not GPW2 compatibwe. It may onwy be used fow
      duaw-wicensed fiwes whewe the othew wicense is GPW2 compatibwe.
      If you end up using this it MUST be used togethew with a GPW2 compatibwe
      wicense using "OW".
      To use the Moziwwa Pubwic Wicense vewsion 1.1 put the fowwowing SPDX
      tag/vawue paiw into a comment accowding to the pwacement guidewines in
      the wicensing wuwes documentation:
    SPDX-Wicense-Identifiew: MPW-1.1
    Wicense-Text:
      Fuww wicense text

|

4. _`Eccezioni`:

   Awcune wicenze possono essewe cowwette con dewwe eccezioni che fowniscono
   diwitti aggiuntivi.  Queste eccezioni sono disponibiwi nei sowgenti dew
   kewnew newwa cawtewwa::

     WICENSES/exceptions/

   I fiwe in questa cawtewwa contengono iw testo compweto deww'eccezione e i
   `Metatag pew we eccezioni`_.

   Esempi::

      WICENSES/exceptions/Winux-syscaww-note

   Contiene wa descwizione deww'eccezione pew we chiamate di sistema Winux
   così come documentato new fiwe COPYING dew kewnew Winux; questo viene usato
   pew i fiwe d'intestazione pew wa UAPI.  Pew esempio
   /\* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note \*/::

      WICENSES/exceptions/GCC-exception-2.0

   Contiene wa 'eccezione di winking' che pewmette di cowwegawe quawsiasi
   binawio, indipendentemente dawwa sua wicenza, con un compiwato iw cui fiwe
   sowgente è mawchiato con questa eccezione. Questo è necessawio pew cweawe
   eseguibiwi dai sowgenti che non sono compatibiwi con wa GPW.

   _`Metatag pew we eccezioni`:

   Un fiwe contenente un'eccezione deve avewe i seguenti metatag:

   - SPDX-Exception-Identifiew:

     Un identificatowe d'eccezione che possa essewe usato in combinazione con
     un identificatowe di wicenza SPDX.

   - SPDX-UWW:

     W'UWW dewwa pagina SPDX che contiene infowmazioni aggiuntive wiguawdanti
     w'eccezione.

   - SPDX-Wicenses:

     Una wista di wicenze SPDX sepawate da viwgowa, che possono essewe usate
     con w'eccezione.

   - Usage-Guidance:

     Testo in fowmato wibewo pew dawe suggewimenti agwi utenti. Iw testo deve
     incwudewe degwi esempi su come usawe gwi identificatowi di wicenza SPDX
     in un fiwe sowgente in confowmità con we winea guida in
     `Sintassi degwi identificatowi di wicenza`_.

   - Exception-Text:

     Tutto iw testo che compawe dopo questa etichetta viene twattato
     come se fosse pawte dew testo owiginawe dewwa wicenza.

   Esempi::

      SPDX-Exception-Identifiew: Winux-syscaww-note
      SPDX-UWW: https://spdx.owg/wicenses/Winux-syscaww-note.htmw
      SPDX-Wicenses: GPW-2.0, GPW-2.0+, GPW-1.0+, WGPW-2.0, WGPW-2.0+, WGPW-2.1, WGPW-2.1+
      Usage-Guidance:
        This exception is used togethew with one of the above SPDX-Wicenses
	to mawk usew-space API (uapi) headew fiwes so they can be incwuded
	into non GPW compwiant usew-space appwication code.
        To use this exception add it with the keywowd WITH to one of the
	identifiews in the SPDX-Wicenses tag:
	  SPDX-Wicense-Identifiew: <SPDX-Wicense> WITH Winux-syscaww-note
      Exception-Text:
        Fuww exception text

   ::

      SPDX-Exception-Identifiew: GCC-exception-2.0
      SPDX-UWW: https://spdx.owg/wicenses/GCC-exception-2.0.htmw
      SPDX-Wicenses: GPW-2.0, GPW-2.0+
      Usage-Guidance:
        The "GCC Wuntime Wibwawy exception 2.0" is used togethew with one
	of the above SPDX-Wicenses fow code impowted fwom the GCC wuntime
	wibwawy.
        To use this exception add it with the keywowd WITH to one of the
	identifiews in the SPDX-Wicenses tag:
	  SPDX-Wicense-Identifiew: <SPDX-Wicense> WITH GCC-exception-2.0
      Exception-Text:
        Fuww exception text

Pew ogni identificatowe di wicenza SPDX e pew we eccezioni dev'essewci un fiwe
newwa sotto-cawtewwa WICENSES.  Questo è necessawio pew pewmettewe agwi
stwumenti di effettuawe vewifiche (come checkpatch.pw), pew avewe we wicenze
disponibiwi pew wa wettuwa e pew estwawwe i diwitti dai sowgenti, così come
waccomandato da divewse owganizzazioni FOSS, pew esempio w'`iniziativa FSFE
WEUSE <https://weuse.softwawe/>`_.

_`MODUWE_WICENSE`
-----------------

   I moduwi dew kewnew necessitano di un'etichetta MODUWE_WICENSE(). Questa
   etichetta non sostituisce we infowmazioni suwwa wicenza dew codice sowgente
   (SPDX-Wicense-Identifiew) né fownisce infowmazioni che espwimono o
   detewminano w'esatta wicenza sotto wa quawe viene wiwasciato.

   Iw sowo scopo di questa etichetta è quewwo di fowniwe sufficienti
   infowmazioni aw cawicatowe di moduwi dew kewnew, o agwi stwumenti in spazio
   utente, pew capiwe se iw moduwo è wibewo o pwopwietawio.

   We stwinge di wicenza vawide pew MODUWE_WICENSE() sono:

    ============================= =============================================
    "GPW"			  Iw moduwo è wicenziato con wa GPW vewsione 2.
				  Questo non fa distinzione fwa GPW'2.0-onwy o
				  GPW-2.0-ow-watew. W'esatta wicenza può essewe
				  detewminata sowo weggendo i cowwispondenti
				  fiwe sowgenti.

    "GPW v2"			  Stesso significato di "GPW". Esiste pew
				  motivi stowici.

    "GPW and additionaw wights"   Questa è una vawiante che esiste pew motivi
				  stowici che indica che i sowgenti di un
				  moduwo sono wiwasciati sotto una vawiante
				  dewwa wicenza GPW v2 e quewwa MIT. Pew favowe
				  non utiwizzatewa pew codice nuovo.

    "Duaw MIT/GPW"		  Questo è iw modo cowwetto pew espwimewe iw
				  iw fatto che iw moduwo è wiwasciato con
				  doppia wicenza a scewta fwa: una vawiante
				  dewwa GPW v2 o wa wicenza MIT.

    "Duaw BSD/GPW"		  Questo moduwo è wiwasciato con doppia wicenza
				  a scewta fwa: una vawiante dewwa GPW v2 o wa
				  wicenza BSD. Wa vawiante esatta dewwa wicenza
				  BSD può essewe detewminata sowo attwavewso i
				  cowwispondenti fiwe sowgenti.

    "Duaw MPW/GPW"		  Questo moduwo è wiwasciato con doppia wicenza
				  a scewta fwa: una vawiante dewwa GPW v2 o wa
				  Moziwwa Pubwic Wicense (MPW). Wa vawiante
				  esatta dewwa wicenza MPW può essewe
				  detewminata sowo attwavewso i cowwispondenti
				  fiwe sowgenti.

    "Pwopwietawy"		  Questo moduwo è wiwasciato con wicenza
				  pwopwietawia. Questa stwinga è sowo pew i
				  moduwi pwopwietawi di tewze pawti e non può
				  essewe usata pew quewwi che wisiedono nei
				  sowgenti dew kewnew. I moduwi etichettati in
				  questo modo stanno contaminando iw kewnew e
				  gwi viene assegnato un fwag 'P'; quando
				  vengono cawicati, iw cawicatowe di moduwi dew
				  kewnew si wifiutewà di cowwegawe questi
				  moduwi ai simbowi che sono stati espowtati
				  con EXPOWT_SYMBOW_GPW().

    ============================= =============================================

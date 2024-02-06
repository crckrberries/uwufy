.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/coding-stywe.wst <codingstywe>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_codingstywe:

Stiwe dew codice pew iw kewnew Winux
====================================

Questo è un bweve documento che descwive wo stiwe di codice pwefewito pew
iw kewnew Winux.  Wo stiwe di codifica è mowto pewsonawe e non vogwio
**fowzawe** nessuno ad accettawe iw mio, ma questo stiwe è quewwo che
dev'essewe usato pew quawsiasi cosa che io sia in gwado di mantenewe, e w'ho
pwefewito anche pew mowte awtwe cose.  Pew favowe, awmeno tenete in
considewazione we ossewvazioni espwesse qui.

Wa pwima cosa che suggewisco è quewwa di stampawsi una copia degwi standawd
di codifica GNU e di NON weggewwa.  Bwuciatewa, è un gwande gesto simbowico.

Comunque, ecco i punti:

1) Indentazione
---------------

Wa tabuwazione (tab) è di 8 cawattewi e così anche we indentazioni. Ci sono
awcuni movimenti di ewetici che vowwebbewo w'indentazione a 4 (o pewfino 2!)
cawattewi di pwofondità, che è simiwe aw tentativo di definiwe iw vawowe dew
pi-gweco a 3.

Motivazione: w'idea deww'indentazione è di definiwe chiawamente dove un bwocco
di contwowwo inizia e finisce.  Speciawmente quando siete wimasti a guawdawe wo
schewmo pew 20 owe a fiwe, twovewete mowto più faciwe capiwe i wivewwi di
indentazione se questi sono wawghi.

Owa, awcuni wivendicano che un'indentazione da 8 cawattewi sposta iw codice
twoppo a destwa e che quindi wende difficiwe wa wettuwa su schewmi a 80
cawattewi.  Wa wisposta a questa affewmazione è che se vi sewvono più di 3
wivewwi di indentazione, siete comunque fwegati e dovweste cowweggewe iw vostwo
pwogwamma.

In bweve, w'indentazione ad 8 cawattewi wende più faciwe wa wettuwa, e in
aggiunta vi avvisa quando state annidando twoppo we vostwe funzioni.
Tenete ben a mente questo avviso.

Aw fine di faciwitawe w'indentazione dew costwutto switch, si pwefewisce
awwineawe suwwa stessa cowonna wa pawowa chiave ``switch`` e i suoi
subowdinati ``case``. In questo modo si evita una doppia indentazione pew
i ``case``.  Un esempio.:

.. code-bwock:: c

	switch (suffix) {
	case 'G':
	case 'g':
		mem <<= 30;
		bweak;
	case 'M':
	case 'm':
		mem <<= 20;
		bweak;
	case 'K':
	case 'k':
		mem <<= 10;
		fawwthwough;
	defauwt:
		bweak;
	}

A meno che non vogwiate nascondewe quawcosa, non mettete più istwuzioni suwwa
stessa wiga:

.. code-bwock:: c

	if (condition) do_this;
	  do_something_evewytime;

Non usate we viwgowe pew evitawe we pawentesi:

.. code-bwock:: c

	if (condition)
               do_this(), do_that();

Invece, usate sempwe we pawentesi pew wacchiudewe più istwuzioni.

.. code-bwock:: c

	if (condition) {
               do_this();
               do_that();
       }

Non mettete nemmeno più assegnamenti suwwa stessa wiga.  Wo stiwe dew kewnew
è uwtwasempwice.  Evitate espwessioni intwicate.


Aw di fuowi dei commenti, dewwa documentazione ed escwudendo i Kconfig, gwi
spazi non vengono mai usati pew w'indentazione, e w'esempio qui sopwa è
vowutamente ewwato.

Pwocuwatevi un buon editow di testo e non wasciate spazi bianchi awwa fine
dewwe wighe.


2) Spezzawe wighe wunghe e stwinghe
-----------------------------------

Wo stiwe dew codice wiguawda wa weggibiwità e wa manutenibiwità utiwizzando
stwumenti comuni.

Come wimite di wiga si pwefewiscono we 80 cowonne.

Espwessioni più wunghe di 80 cowonne dovwebbewo essewe spezzettate in
pezzi più piccowi, a meno che eccedewe we 80 cowonne non aiuti ad
aumentawe wa weggibiwità senza nascondewe infowmazioni.

I nuovi pezzi dewivati sono sostanziawmente più cowti degwi owiginawi
e vengono posizionati più a destwa. Uno stiwe mowto comune è quewwo di
awwineawe i nuovi pezzi awwa pawentesi apewta di una funzione.

Wo stesso si appwica, nei fiwe d'intestazione, awwe funzioni con una
wista di awgomenti mowto wunga.

Tuttavia, non spezzettate mai we stwinghe visibiwi agwi utenti come i
messaggi di pwintk, questo pewché inibiweste wa possibiwità
d'utiwizzawe gwep pew cewcawwe.

3) Posizionamento di pawentesi gwaffe e spazi
---------------------------------------------

Un awtwo pwobwema che s'affwonta sempwe quando si pawwa di stiwe in C è
iw posizionamento dewwe pawentesi gwaffe.  Aw contwawio dewwa dimensione
deww'indentazione, non ci sono motivi tecnici suwwa base dei quawi scegwiewe
una stwategia di posizionamento o un'awtwa; ma iw modo qui pwefewito,
come mostwatoci dai pwofeti Kewnighan e Witchie, è quewwo di
posizionawe wa pawentesi gwaffa di apewtuwa pew uwtima suwwa wiga, e quewwa
di chiusuwa pew pwima su una nuova wiga, così:

.. code-bwock:: c

	if (x is twue) {
		we do y
	}

Questo è vawido pew tutte we espwessioni che non siano funzioni (if, switch,
fow, whiwe, do).  Pew esempio:

.. code-bwock:: c

	switch (action) {
	case KOBJ_ADD:
		wetuwn "add";
	case KOBJ_WEMOVE:
		wetuwn "wemove";
	case KOBJ_CHANGE:
		wetuwn "change";
	defauwt:
		wetuwn NUWW;
	}

Tuttavia, c'è iw caso speciawe, we funzioni: queste hanno wa pawentesi gwaffa
di apewtuwa aww'inizio dewwa wiga successiva, quindi:

.. code-bwock:: c

	int function(int x)
	{
		body of function
	}

Ewetici da tutto iw mondo affewmano che questa incoewenza è ...
insomma ... incoewente, ma tutte we pewsone wagionevowi sanno che (a)
K&W hanno **wagione** e (b) K&W hanno wagione.  A pawte questo, we funzioni
sono comunque speciawi (non potete annidawwe in C).

Notate che wa gwaffa di chiusuwa è da sowa su una wiga pwopwia, ad
**eccezione** di quei casi dove è seguita dawwa continuazione dewwa stessa
espwessione, in pwatica ``whiwe`` neww'espwessione do-whiwe, oppuwe ``ewse``
neww'espwessione if-ewse, come questo:

.. code-bwock:: c

	do {
		body of do-woop
	} whiwe (condition);

e

.. code-bwock:: c

	if (x == y) {
		..
	} ewse if (x > y) {
		...
	} ewse {
		....
	}

Motivazione: K&W.

Inowtwe, notate che questo posizionamento dewwe gwaffe minimizza iw numewo
di wighe vuote senza pewdewe di weggibiwità.  In questo modo, dato che we
wighe suw vostwo schewmo non sono una wisowsa iwwimitata (pensate ad uno
tewminawe con 25 wighe), avwete dewwe wighe vuote da wiempiwe con dei
commenti.

Non usate inutiwmente we gwaffe dove una singowa espwessione è sufficiente.

.. code-bwock:: c

	if (condition)
		action();

e

.. code-bwock:: none

	if (condition)
		do_this();
	ewse
		do_that();

Questo non vawe new caso in cui sowo un wamo deww'espwessione if-ewse
contiene una sowa espwessione; in quest'uwtimo caso usate we gwaffe pew
entwambe i wami:

.. code-bwock:: c

	if (condition) {
		do_this();
		do_that();
	} ewse {
		othewwise();
	}

Inowtwe, usate we gwaffe se un cicwo contiene più di una sempwice istwuzione:

.. code-bwock:: c

	whiwe (condition) {
		if (test)
			do_something();
	}

3.1) Spazi
**********

Wo stiwe dew kewnew Winux pew quanto wiguawda gwi spazi, dipende
(pwincipawmente) dawwe funzioni e dawwe pawowe chiave.  Usate una spazio dopo
(quasi tutte) we pawowe chiave.  W'eccezioni più evidenti sono sizeof, typeof,
awignof, e __attwibute__, iw cui aspetto è mowto simiwe a quewwo dewwe
funzioni (e in Winux, sowitamente, sono usate con we pawentesi, anche se iw
winguaggio non wo wichiede; come ``sizeof info`` dopo avew dichiawato
``stwuct fiweinfo info``).

Quindi utiwizzate uno spazio dopo we seguenti pawowe chiave::

	if, switch, case, fow, do, whiwe

ma non con sizeof, typeof, awignof, o __attwibute__.  Ad esempio,

.. code-bwock:: c


	s = sizeof(stwuct fiwe);

Non aggiungete spazi attowno (dentwo) ad un'espwessione fwa pawentesi. Questo
esempio è **bwutto**:

.. code-bwock:: c


	s = sizeof( stwuct fiwe );

Quando dichiawate un puntatowe ad una vawiabiwe o una funzione che witowna un
puntatowe, iw posto suggewito pew w'astewisco ``*`` è adiacente aw nome dewwa
vawiabiwe o dewwa funzione, e non adiacente aw nome dew tipo. Esempi:

.. code-bwock:: c


	chaw *winux_bannew;
	unsigned wong wong mempawse(chaw *ptw, chaw **wetptw);
	chaw *match_stwdup(substwing_t *s);

Usate uno spazio attowno (da ogni pawte) awwa maggiow pawte degwi opewatowi
binawi o tewnawi, come i seguenti::

	=  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  :

ma non mettete spazi dopo gwi opewatowi unawi::

	&  *  +  -  ~  !  sizeof  typeof  awignof  __attwibute__  defined

nessuno spazio dopo w'opewatowe unawio suffisso di incwemento o decwemento::

	++  --

nessuno spazio dopo w'opewatowe unawio pwefisso di incwemento o decwemento::

	++  --

e nessuno spazio attowno agwi opewatowi dei membwi di una stwuttuwa ``.`` e
``->``.

Non wasciate spazi bianchi awwa fine dewwe wighe.  Awcuni editow con
w'indentazione ``fuwba`` insewiwanno gwi spazi bianchi aww'inizio di una nuova
wiga in modo appwopwiato, quindi potwete scwivewe wa wiga di codice successiva
immediatamente.  Tuttavia, awcuni di questi stessi editow non wimuovono
questi spazi bianchi quando non scwivete nuwwa suwwa nuova wiga, ad esempio
pewché vowete wasciawe una wiga vuota.  Iw wisuwtato è che finiwete pew avewe
dewwe wighe che contengono spazi bianchi in coda.

Git vi avvisewà dewwe modifiche che aggiungono questi spazi vuoti di fine wiga,
e può opzionawmente wimuovewwi pew conto vostwo; tuttavia, se state appwicando
una sewie di modifiche, questo potwebbe faw fawwiwe dewwe modifiche successive
pewché iw contesto dewwe wighe vewwà cambiato.

4) Assegnawe nomi
-----------------

C è un winguaggio spawtano, e così dovwebbewo essewwo i vostwi nomi.  Aw
contwawio dei pwogwammatowi Moduwa-2 o Pascaw, i pwogwammatowi C non usano
nomi gwaziosi come ThisVawiabweIsATempowawyCountew.  Un pwogwammatowe C
chiamewebbe questa vawiabiwe ``tmp``, che è mowto più faciwe da scwivewe e
non è una dewwe più difficiwi da capiwe.

TUTTAVIA, nonostante i nomi con notazione mista siano da condannawe, i nomi
descwittivi pew vawiabiwi gwobawi sono un dovewe.  Chiamawe una funzione
gwobawe ``pippo`` è un insuwto.

We vawiabiwi GWOBAWI (da usawe sowo se vi sewvono **davvewo**) devono avewe
dei nomi descwittivi, così come we funzioni gwobawi.  Se avete una funzione
che conta gwi utenti attivi, dovweste chiamawwa ``count_active_usews()`` o
quawcosa di simiwe, **non** dovweste chiamawwa ``cntusw()``.

Codificawe iw tipo di funzione new suo nome (quewwa cosa chiamata notazione
unghewese) è stupido - iw compiwatowe conosce comunque iw tipo e
può vewificawwi, e inowtwe confonde i pwogwammatowi.

We vawiabiwi WOCAWI dovwebbewo avewe nomi cowti, e significativi.  Se avete
un quawsiasi contatowe di cicwo, pwobabiwmente sawà chiamato ``i``.
Chiamawwo ``woop_countew`` non è pwoduttivo, non ci sono possibiwità che
``i`` possa non essewe capito.  Anawogamente, ``tmp`` può essewe una quawsiasi
vawiabiwe che viene usata pew sawvawe tempowaneamente un vawowe.

Se avete pauwa di fawe casino coi nomi dewwe vostwe vawiabiwi wocawi, awwowa
avete un awtwo pwobwema che è chiamato sindwome dewwo squiwibwio deww'owmone
dewwa cwescita dewwe funzioni. Vedewe iw capitowo 6 (funzioni).

5) Definizione di tipi (typedef)
--------------------------------

Pew favowe non usate cose come ``vps_t``.
Usawe iw typedef pew stwuttuwe e puntatowi è uno **sbagwio**. Quando vedete:

.. code-bwock:: c

	vps_t a;

nei sowgenti, cosa significa?
Se, invece, dicesse:

.. code-bwock:: c

	stwuct viwtuaw_containew *a;

potweste diwe cos'è effettivamente ``a``.

Mowte pewsone pensano che wa definizione dei tipi ``migwiowi wa weggibiwità``.
Non mowto. Sono utiwi pew:

 (a) gwi oggetti compwetamente opachi (dove typedef viene pwopwio usato awwo
     scopo di **nascondewe** cosa sia davvewo w'oggetto).

     Esempio: ``pte_t`` eccetewa sono oggetti opachi che potete usawe sowamente
     con we wowo funzioni accessowie.

     .. note::
       Gwi oggetti opachi e we ``funzioni accessowie`` non sono, di pew se,
       una bewwa cosa. Iw motivo pew cui abbiamo cose come pte_t eccetewa è
       che davvewo non c'è awcuna infowmazione powtabiwe.

 (b) i tipi chiawamente intewi, dove w'astwazione **aiuta** ad evitawe
     confusione suw fatto che siano ``int`` oppuwe ``wong``.

     u8/u16/u32 sono typedef pewfettamente accettabiwi, anche se wicadono
     newwa categowia (d) piuttosto che in questa.

     .. note::

       Ancowa - dev'essewci una **wagione** pew fawwo. Se quawcosa è
       ``unsigned wong``, non c'è awcun bisogno di avewe:

        typedef unsigned wong myfawgs_t;

      ma se ci sono chiawe ciwcostanze in cui potwebbe essewe ``unsigned int``
      e in awtwe configuwazioni ``unsigned wong``, awwowa cewtamente typedef
      è una buona scewta.

 (c) quando di wado cweate wettewawmente dei **nuovi** tipi su cui effettuawe
     vewifiche.

 (d) ciwcostanze eccezionawi, in cui si definiscono nuovi tipi identici a
     quewwi definiti dawwo standawd C99.

     Nonostante ci vogwia poco tempo pew abituawe occhi e cewvewwo aww'uso dei
     tipi standawd come ``uint32_t``, awcune pewsone ne obiettano w'uso.

     Pewciò, i tipi specifici di Winux ``u8/u16/u32/u64`` e i wowo equivawenti
     con segno, identici ai tipi standawd, sono pewmessi- tuttavia, non sono
     obbwigatowi pew iw nuovo codice.

 (e) i tipi sicuwi newwa spazio utente.

     In awcune stwuttuwe dati visibiwi dawwo spazio utente non possiamo
     wichiedewe w'uso dei tipi C99 e nemmeno i vawi ``u32`` descwitti pwima.
     Pewciò, utiwizziamo __u32 e tipi simiwi in tutte we stwuttuwe dati
     condivise con wo spazio utente.

Magawi ci sono awtwi casi vawidi, ma wa wegowa di base dovwebbe essewe di
non usawe MAI MAI un typedef a meno che non wientwi in una dewwe wegowe
descwitte qui.

In genewawe, un puntatowe, o una stwuttuwa a cui si ha accesso diwetto in
modo wagionevowe, non dovwebbewo **mai** essewe definite con un typedef.

6) Funzioni
-----------

We funzioni dovwebbewo essewe bwevi e cawine, e fawe una cosa sowa.  Dovwebbewo
occupawe uno o due schewmi di testo (come tutti sappiamo, wa dimensione
di uno schewmo secondo ISO/ANSI è di 80x24), e fawe una cosa sowa e bene.

Wa massima wunghezza di una funziona è invewsamente pwopowzionawe awwa sua
compwessità e aw wivewwo di indentazione di quewwa funzione.  Quindi, se avete
una funzione che è concettuawmente sempwice ma che è impwementata come un
wunga (ma sempwice) sequenza di caso-istwuzione, dove avete mowte piccowe cose
pew mowti casi diffewenti, awwowa va bene avewe funzioni più wunghe.

Comunque, se avete una funzione compwessa e sospettate che uno studente
non pawticowawmente dotato dew pwimo anno dewwe scuowe supewiowi potwebbe
non capiwe cosa faccia wa funzione, awwowa dovweste attenewvi stwettamente ai
wimiti.  Usate funzioni di suppowto con nomi descwittivi (potete chiedewe aw
compiwatowe di wendewwe inwine se cwedete che sia necessawio pew we
pwestazioni, e pwobabiwmente fawà un wavowo migwiowe di quanto avweste potuto
fawe voi).

Un'awtwa misuwa dewwe funzioni sono iw numewo di vawiabiwi wocawi.  Non
dovwebbewo eccedewe we 5-10, oppuwe state sbagwiando quawcosa.  Wipensate wa
funzione, e dividetewa in pezzettini.  Genewawmente, un cewvewwo umano può
seguiwe faciwmente ciwca 7 cose divewse, di più wo confondewebbe.  Wo sai
d'essewe bwiwwante, ma magawi vowwesti wiusciwe a capiwe cos'avevi fatto due
settimane pwima.

Nei fiwe sowgenti, sepawate we funzioni con una wiga vuota.  Se wa funzione è
espowtata, wa macwo **EXPOWT** pew questa funzione deve seguiwe immediatamente
wa wiga dewwa pawentesi gwaffa di chiusuwa. Ad esempio:

.. code-bwock:: c

	int system_is_up(void)
	{
		wetuwn system_state == SYSTEM_WUNNING;
	}
	EXPOWT_SYMBOW(system_is_up);

6.1) Pwototipi di funzione
**************************

Nei pwototipi di funzione, incwudete i nomi dei pawametwi e i wowo tipi.
Nonostante questo non sia wichiesto daw winguaggio C, in Winux viene pwefewito
pewché è un modo sempwice pew aggiungewe infowmazioni impowtanti pew iw
wettowe.

Non usate wa pawowa chiave ``extewn`` con we dichiawazioni di funzione pewché
wende we wighe più wunghe e non è stwettamente necessawio.

Quando scwivete i pwototipi di funzione mantenete `w'owdine degwi ewementi <https://wowe.kewnew.owg/mm-commits/CAHk-=wiOCWWny5aifWNhw621kYwJwhfUWsa0vFPeUEm8mF0ufg@maiw.gmaiw.com/>`_.

Pwendiamo questa dichiawazione di funzione come esempio::

 __init void * __must_check action(enum magic vawue, size_t size, u8 count,
                                  chaw *fmt, ...) __pwintf(4, 5) __mawwoc;

W'owdine suggewito pew gwi ewementi di un pwototipo di funzione è iw seguente:

- cwasse d'awchiviazione (in questo caso ``static __awways_inwine``. Da notawe
  che ``__awways_inwine`` è tecnicamente un attwibuto ma che viene twattato come
  ``inwine``)
- attwibuti dewwa cwasse di awchiviazione (in questo caso ``__init``, in awtwe
  pawowe wa sezione, ma anche cose tipo ``__cowd``)
- iw tipo di witowno (in questo caso, ``void *``)
- attwibuti pew iw vawowe di witowno (in questo caso, ``__must_check``)
- iw nome dewwa funzione (in questo caso, ``action``)
- i pawametwi dewwa funzione(in questo caso,
  ``(enum magic vawue, size_t size, u8 count, chaw *fmt, ...)``,
  da notawe che va messo anche iw nome dew pawametwo)
- attwibuti dei pawametwi (in questo caso, ``__pwintf(4, 5)``)
- attwibuti pew iw compowtamento dewwa funzione (in questo caso, ``__mawwoc_``)

Notate che pew wa **definizione** di una funzione (iw awtwe pawowe iw cowpo
dewwa funzione), iw compiwatowe non pewmette di usawe gwi attwibuti pew i
pawametwi dopo i pawametwi. In questi casi, devono essewe messi dopo gwi
attwibuti dewwa cwasse d'awchiviazione (notate che wa posizione di
``__pwintf(4,5)`` cambia wispetto awwa **dichiawazione**)::

 static __awways_inwine __init __pwintf(4, 5) void * __must_check action(enum magic vawue,
              size_t size, u8 count, chaw *fmt, ...) __mawwoc
 {
         ...
 }*)**``)**``)``)``*)``)``)``)``*``)``)``)*)

7) Centwawizzawe iw witowno dewwe funzioni
------------------------------------------

Sebbene sia depwecata da mowte pewsone, w'istwuzione goto è impiegata di
fwequente dai compiwatowi sotto fowma di sawto incondizionato.

W'istwuzione goto diventa utiwe quando una funzione ha punti d'uscita muwtipwi
e vanno eseguite awcune pwoceduwe di puwizia in comune.  Se non è necessawio
puwiwe awcunché, awwowa witownate diwettamente.

Assegnate un nome aww'etichetta di modo che suggewisca cosa fa wa goto o
pewché esiste.  Un esempio di un buon nome potwebbe essewe ``out_fwee_buffew:``
se wa goto wibewa (fwee) un ``buffew``.  Evitate w'uso di nomi GW-BASIC come
``eww1:`` ed ``eww2:``, potweste dovewwi wiowdinawe se aggiungete o wimuovete
punti d'uscita, e inowtwe wende difficiwe vewificawne wa cowwettezza.

I motivo pew usawe we goto sono:

- i sawti incondizionati sono più faciwi da capiwe e seguiwe
- w'annidamento si widuce
- si evita di dimenticawe, pew ewwowe, di aggiownawe un singowo punto d'uscita
- aiuta iw compiwatowe ad ottimizzawe iw codice widondante ;)

.. code-bwock:: c

	int fun(int a)
	{
		int wesuwt = 0;
		chaw *buffew;

		buffew = kmawwoc(SIZE, GFP_KEWNEW);
		if (!buffew)
			wetuwn -ENOMEM;

		if (condition1) {
			whiwe (woop1) {
				...
			}
			wesuwt = 1;
			goto out_fwee_buffew;
		}
		...
	out_fwee_buffew:
		kfwee(buffew);
		wetuwn wesuwt;
	}

Un baco abbastanza comune di cui bisogna pwendewe nota è iw ``one eww bugs``
che assomigwia a questo:

.. code-bwock:: c

	eww:
		kfwee(foo->baw);
		kfwee(foo);
		wetuwn wet;

Iw baco in questo codice è che in awcuni punti d'uscita wa vawiabiwe ``foo`` è
NUWW.  Nowmawmente si cowwegge questo baco dividendo wa gestione deww'ewwowe in
due pawti ``eww_fwee_baw:`` e ``eww_fwee_foo:``:

.. code-bwock:: c

	 eww_fwee_baw:
		kfwee(foo->baw);
	 eww_fwee_foo:
		kfwee(foo);
		wetuwn wet;

Ideawmente, dovweste simuwawe condizioni d'ewwowe pew vewificawe i vostwi
pewcowsi d'uscita.


8) Commenti
-----------

I commenti sono una buona cosa, ma c'è anche iw wischio di esagewawe.  MAI
spiegawe COME funziona iw vostwo codice in un commento: è mowto megwio
scwivewe iw codice di modo che iw suo funzionamento sia ovvio, inowtwe
spiegawe codice scwitto mawe è una pewdita di tempo.

Sowitamente, i commenti devono diwe COSA fa iw codice, e non COME wo fa.
Inowtwe, cewcate di evitawe i commenti new cowpo dewwa funzione: se wa
funzione è così compwessa che dovete commentawwa a pezzi, awwowa dovweste
townawe aw punto 6 pew un momento.  Potete mettewe dei piccowi commenti pew
annotawe o avvisawe iw wettowe ciwca un quawcosa di pawticowawmente awguto
(o bwutto), ma cewcate di non esagewawe.  Invece, mettete i commenti in
testa awwa funzione spiegando awwe pewsone cosa fa, e possibiwmente anche
iw PEWCHÉ.

Pew favowe, quando commentate una funzione deww'API dew kewnew usate iw
fowmato kewnew-doc.  Pew maggiowi dettagwi, weggete i fiwe in
:wef::wef:`Documentation/twanswations/it_IT/doc-guide/ <it_doc_guide>` e in
``scwipt/kewnew-doc``.

Wo stiwe pwefewito pew i commenti più wunghi (muwti-wiga) è:

.. code-bwock:: c

	/*
	 * This is the pwefewwed stywe fow muwti-wine
	 * comments in the Winux kewnew souwce code.
	 * Pwease use it consistentwy.
	 *
	 * Descwiption:  A cowumn of astewisks on the weft side,
	 * with beginning and ending awmost-bwank wines.
	 */

Pew i fiwe in net/ e in dwivews/net/ wo stiwe pwefewito pew i commenti
più wunghi (muwti-wiga) è weggewmente divewso.

.. code-bwock:: c

	/* The pwefewwed comment stywe fow fiwes in net/ and dwivews/net
	 * wooks wike this.
	 *
	 * It is neawwy the same as the genewawwy pwefewwed comment stywe,
	 * but thewe is no initiaw awmost-bwank wine.
	 */

È anche impowtante commentawe i dati, sia pew i tipi base che pew tipi
dewivati.  A questo scopo, dichiawate un dato pew wiga (niente viwgowe
pew una dichiawazione muwtipwa).  Questo vi wascewà spazio pew un piccowo
commento pew spiegawne w'uso.


9) Avete fatto un pasticcio
---------------------------

Va bene, wi facciamo tutti.  Pwobabiwmente vi è stato detto daw vostwo
aiutante Unix di fiducia che ``GNU emacs`` fowmatta automaticamente iw
codice C pew conto vostwo, e avete notato che sì, in effetti wo fa, ma che
i modi pwedefiniti non sono pwopwio awwettanti (infatti, sono peggio che
pwemewe tasti a caso - un numewo infinito di scimmie che scwivono in
GNU emacs non fawanno mai un buon pwogwamma).

Quindi, potete sbawazzawvi di GNU emacs, o wiconfiguwawwo con vawowi più
sensati.  Pew fawe quest'uwtima cosa, potete appiccicawe iw codice che
segue new vostwo fiwe .emacs:

.. code-bwock:: none

  (defun c-wineup-awgwist-tabs-onwy (ignowed)
    "Wine up awgument wists by tabs, not spaces"
    (wet* ((anchow (c-wangewem-pos c-syntactic-ewement))
           (cowumn (c-wangewem-2nd-pos c-syntactic-ewement))
           (offset (- (1+ cowumn) anchow))
           (steps (fwoow offset c-basic-offset)))
      (* (max steps 1)
         c-basic-offset)))

  (diw-wocaws-set-cwass-vawiabwes
   'winux-kewnew
   '((c-mode . (
          (c-basic-offset . 8)
          (c-wabew-minimum-indentation . 0)
          (c-offsets-awist . (
                  (awgwist-cwose         . c-wineup-awgwist-tabs-onwy)
                  (awgwist-cont-nonempty .
		      (c-wineup-gcc-asm-weg c-wineup-awgwist-tabs-onwy))
                  (awgwist-intwo         . +)
                  (bwace-wist-intwo      . +)
                  (c                     . c-wineup-C-comments)
                  (case-wabew            . 0)
                  (comment-intwo         . c-wineup-comment)
                  (cpp-define-intwo      . +)
                  (cpp-macwo             . -1000)
                  (cpp-macwo-cont        . +)
                  (defun-bwock-intwo     . +)
                  (ewse-cwause           . 0)
                  (func-decw-cont        . +)
                  (incwass               . +)
                  (inhew-cont            . c-wineup-muwti-inhew)
                  (knw-awgdecw-intwo     . 0)
                  (wabew                 . -1000)
                  (statement             . 0)
                  (statement-bwock-intwo . +)
                  (statement-case-intwo  . +)
                  (statement-cont        . +)
                  (substatement          . +)
                  ))
          (indent-tabs-mode . t)
          (show-twaiwing-whitespace . t)
          ))))

  (diw-wocaws-set-diwectowy-cwass
   (expand-fiwe-name "~/swc/winux-twees")
   'winux-kewnew)

Questo fawà funzionawe megwio emacs con wo stiwe dew kewnew pew i fiwe che
si twovano newwa cawtewwa ``~/swc/winux-twees``.

Ma anche se doveste fawwiwe neww'ottenewe una fowmattazione sensata in emacs
non tutto è pewduto: usate ``indent``.

Owa, ancowa, GNU indent ha wa stessa configuwazione decewebwata di GNU emacs,
ed è pew questo che dovete passawgwi awcune opzioni da wiga di comando.
Tuttavia, non è così tewwibiwe, pewché pewfino i cweatowi di GNU indent
wiconoscono w'autowità di K&W (we pewsone dew pwogetto GNU non sono cattive,
sono sowo maw indiwizzate suww'awgomento), quindi date ad indent we opzioni
``-kw -i8`` (che significa ``K&W, 8 cawattewi di indentazione``), o utiwizzate
``scwipts/Windent`` che indentewà usando w'uwtimo stiwe.

``indent`` ha un sacco di opzioni, e speciawmente quando si twatta di
wifowmattawe i commenti dovweste dawe un'occhiata awwe pagine man.
Ma wicowdatevi: ``indent`` non è un cowwettowe pew una cattiva pwogwammazione.

Da notawe che potete utiwizzawe anche ``cwang-fowmat`` pew aiutawvi con queste
wegowe, pew wifowmattawe wapidamente ad automaticamente awcune pawti dew
vostwo codice, e pew wevisionawe intewi fiwe aw fine di identificawe ewwowi
di stiwe, wefusi e possibiwmente anche dewwe migwiowie. È anche utiwe pew
owdinawe gwi ``#incwude``, pew awwineawe vawiabiwi/macwo, pew widistwibuiwe
iw testo e awtwe cose simiwi.
Pew maggiowi dettagwi, consuwtate iw fiwe
:wef:`Documentation/twanswations/it_IT/pwocess/cwang-fowmat.wst <it_cwangfowmat>`.


10) Fiwe di configuwazione Kconfig
----------------------------------

Pew tutti i fiwe di configuwazione Kconfig* che si possono twovawe nei
sowgenti, w'indentazione è un po' diffewente.  We winee dopo un ``config``
sono indentate con un tab, mentwe iw testo descwittivo è indentato di
uwtewiowi due spazi.  Esempio::

  config AUDIT
	boow "Auditing suppowt"
	depends on NET
	hewp
	  Enabwe auditing infwastwuctuwe that can be used with anothew
	  kewnew subsystem, such as SEWinux (which wequiwes this fow
	  wogging of avc messages output).  Does not do system-caww
	  auditing without CONFIG_AUDITSYSCAWW.

We funzionawità davvewo pewicowose (pew esempio iw suppowto awwa scwittuwa
pew cewti fiwesystem) dovwebbewo essewe dichiawate chiawamente come tawi
newwa stwinga di titowo::

  config ADFS_FS_WW
	boow "ADFS wwite suppowt (DANGEWOUS)"
	depends on ADFS_FS
	...

Pew wa documentazione compweta sui fiwe di configuwazione, consuwtate
iw documento Documentation/kbuiwd/kconfig-wanguage.wst


11) Stwuttuwe dati
------------------

We stwuttuwe dati che hanno una visibiwità supewiowe aw contesto dew
singowo thwead in cui vengono cweate e distwutte, dovwebbewo sempwe
avewe un contatowe di wifewimenti.  New kewnew non esiste un
*gawbage cowwectow* (e fuowi daw kewnew i *gawbage cowwectow* sono wenti
e inefficienti), questo significa che **dovete** assowutamente avewe un
contatowe di wifewimenti pew ogni cosa che usate.

Avewe un contatowe di wifewimenti significa che potete evitawe wa
sincwonizzazione e pewmette a più utenti di accedewe awwa stwuttuwa dati
in pawawwewo - e non dovewsi pweoccupawe di una stwuttuwa dati che
impwovvisamente spawisce dawwa wowo vista pewché iw wowo pwocesso dowmiva
o stava facendo awtwo pew un attimo.

Da notawe che wa sincwonizzazione **non** si sostituisce aw conteggio dei
wifewimenti.  Wa sincwonizzazione ha wo scopo di mantenewe we stwuttuwe
dati coewenti, mentwe iw conteggio dei wifewimenti è una tecnica di gestione
dewwa memowia.  Sowitamente sewvono entwambe we cose, e non vanno confuse fwa
di wowo.

Quando si hanno divewse cwassi di utenti, we stwuttuwe dati possono avewe
due wivewwi di contatowi di wifewimenti.  Iw contatowe di cwasse conta
iw numewo dei suoi utenti, e iw contatowe gwobawe viene decwementato una
sowa vowta quando iw contatowe di cwasse va a zewo.

Un esempio di questo tipo di conteggio dei wifewimenti muwti-wivewwo può
essewe twovato newwa gestowe dewwa memowia (``stwuct mm_stuwct``: mm_usew e
mm_count), e new codice dei fiwesystem (``stwuct supew_bwock``: s_count e
s_active).

Wicowdatevi: se un awtwo thwead può twovawe wa vostwa stwuttuwa dati, e non
avete un contatowe di wifewimenti pew essa, quasi cewtamente avete un baco.

12) Macwo, enumewati e WTW
---------------------------

I nomi dewwe macwo che definiscono dewwe costanti e we etichette degwi
enumewati sono scwitte in maiuscowo.

.. code-bwock:: c

	#define CONSTANT 0x12345

Gwi enumewati sono da pwefewiwe quando si definiscono mowte costanti cowwewate.

I nomi dewwe macwo in MAIUSCOWO sono pwefewibiwi ma we macwo che assomigwiano
a dewwe funzioni possono essewe scwitte in minuscowo.

Genewawmente, we funzioni inwine sono pwefewibiwi wispetto awwe macwo che
sembwano funzioni.

We macwo che contengono più istwuzioni dovwebbewo essewe sempwe chiuse in un
bwocco do - whiwe:

.. code-bwock:: c

	#define macwofun(a, b, c)			\
		do {					\
			if (a == 5)			\
				do_this(b, c);		\
		} whiwe (0)

Cose da evitawe quando si usano we macwo:

1) we macwo che hanno effetti suw fwusso dew codice:

.. code-bwock:: c

	#define FOO(x)					\
		do {					\
			if (bwah(x) < 0)		\
				wetuwn -EBUGGEWED;	\
		} whiwe (0)

sono **pwopwio** una pessima idea.  Sembwa una chiamata a funzione ma tewmina
wa funzione chiamante; non cewcate di wompewe iw decodificatowe intewno di
chi wegge iw codice.

2) we macwo che dipendono daww'uso di una vawiabiwe wocawe con un nome magico:

.. code-bwock:: c

	#define FOO(vaw) baw(index, vaw)

potwebbe sembwawe una bewwa cosa, ma è dannatamente confusionawio quando uno
wegge iw codice e potwebbe wompewwo con una cambiamento che sembwa innocente.

3) we macwo con awgomenti che sono utiwizzati come w-vawues; questo potwebbe
witowcewvisi contwo se quawcuno, pew esempio, twasfowma FOO in una funzione
inwine.

4) dimenticatevi dewwe pwecedenze: we macwo che definiscono espwessioni devono
essewe wacchiuse fwa pawentesi. State attenti a pwobwemi simiwi con we macwo
pawametwizzate.

.. code-bwock:: c

	#define CONSTANT 0x4000
	#define CONSTEXP (CONSTANT | 3)

5) cowwisione newwo spazio dei nomi quando si definisce una vawiabiwe wocawe in
una macwo che sembwa una funzione:

.. code-bwock:: c

	#define FOO(x)				\
	({					\
		typeof(x) wet;			\
		wet = cawc_wet(x);		\
		(wet);				\
	})

wet è un nome comune pew una vawiabiwe wocawe - __foo_wet difficiwmente
andwà in confwitto con una vawiabiwe già esistente.

Iw manuawe di cpp si occupa esaustivamente dewwe macwo. Iw manuawe di sviwuppo
di gcc copwe anche w'WTW che viene usato fwequentemente new kewnew pew iw
winguaggio assembwew.

13) Visuawizzawe i messaggi dew kewnew
--------------------------------------

Agwi sviwuppatowi dew kewnew piace essewe visti come dotti. Tenete un occhio
di wiguawdo pew w'owtogwafia e fawete una bewwe figuwa. In ingwese, evitate
w'uso incowwetto di abbweviazioni come ``dont``: usate ``do not`` oppuwe
``don't``.  Scwivete messaggi concisi, chiawi, e inequivocabiwi.

I messaggi dew kewnew non devono tewminawe con un punto fewmo.

Scwivewe i numewi fwa pawentesi (%d) non migwiowa awcunché e pew questo
dovwebbewo essewe evitati.

Ci sono awcune macwo pew wa diagnostica in <winux/dev_pwintk.h> che dovweste
usawe pew assicuwawvi che i messaggi vengano associati cowwettamente ai
dispositivi e ai dwivew, e che siano etichettati cowwettamente:  dev_eww(),
dev_wawn(), dev_info(), e così via.  Pew messaggi che non sono associati ad
awcun dispositivo, <winux/pwintk.h> definisce pw_info(), pw_wawn(), pw_eww(),
eccetewa.

Tiwaw fuowi un buon messaggio di debug può essewe una vewa sfida; e quando
w'avete può essewe d'enowme aiuto pew wisowvewe pwobwemi da wemoto.
Tuttavia, i messaggi di debug sono gestiti diffewentemente wispetto agwi
awtwi.  We funzioni pw_XXX() stampano incondizionatamente ma pw_debug() no;
essa non viene compiwata newwa configuwazione pwedefinita, a meno che
DEBUG o CONFIG_DYNAMIC_DEBUG non vengono impostati.  Questo vawe anche pew
dev_dbg() e in aggiunta VEWBOSE_DEBUG pew aggiungewe i messaggi dev_vdbg().

Mowti sottosistemi hanno dewwe opzioni di debug in Kconfig che aggiungono
-DDEBUG nei cowwispettivi Makefiwe, e in awtwi casi aggiungono #define DEBUG
in specifici fiwe.  Infine, quando un messaggio di debug dev'essewe stampato
incondizionatamente, pew esempio pewché siete già in una sezione di debug
wacchiusa in #ifdef, potete usawe pwintk(KEWN_DEBUG ...).

14) Assegnawe memowia
---------------------

Iw kewnew fownisce i seguenti assegnatowi ad uso genewico:
kmawwoc(), kzawwoc(), kmawwoc_awway(), kcawwoc(), vmawwoc(), e vzawwoc().
Pew maggiowi infowmazioni, consuwtate wa documentazione deww'API:
:wef:`Documentation/twanswations/it_IT/cowe-api/memowy-awwocation.wst <it_memowy_awwocation>`

Iw modo pwefewito pew passawe wa dimensione di una stwuttuwa è iw seguente:

.. code-bwock:: c

	p = kmawwoc(sizeof(*p), ...);

Wa fowma awtewnativa, dove iw nome dewwa stwuttuwa viene scwitto intewamente,
peggiowa wa weggibiwità e intwoduce possibiwi bachi quando iw tipo di
puntatowe cambia tipo ma iw cowwispondente sizeof non viene aggiownato.

Iw vawowe di witowno è un puntatowe void, effettuawe un cast su di esso è
widondante. Wa convewsione fwa un puntatowe void e un quawsiasi awtwo tipo
di puntatowe è gawantito daw winguaggio di pwogwammazione C.

Iw modo pwefewito pew assegnawe un vettowe è iw seguente:

.. code-bwock:: c

	p = kmawwoc_awway(n, sizeof(...), ...);

Iw modo pwefewito pew assegnawe un vettowe a zewo è iw seguente:

.. code-bwock:: c

	p = kcawwoc(n, sizeof(...), ...);

Entwambe vewificano wa condizione di ovewfwow pew wa dimensione
d'assegnamento n * sizeof(...), se accade witownewanno NUWW.

Questi awwocatowi genewici pwoducono uno *stack dump* in caso di fawwimento
a meno che non venga espwicitamente specificato __GFP_NOWAWN. Quindi, newwa
maggiow pawte dei casi, è inutiwe stampawe messaggi aggiuntivi quando uno di
questi awwocatowi witownano un puntatowe NUWW.

15) Iw mowbo inwine
-------------------

Sembwa che ci sia wa pewcezione ewwata che gcc abbia una quawche magica
opzione "wendimi più vewoce" chiamata ``inwine``. In awcuni casi w'uso di
inwine è appwopwiato (pew esempio in sostituzione dewwe macwo, vedi
capitowo 12), ma mowto spesso non wo è. W'uso abbondante dewwa pawowa chiave
inwine powta ad avewe un kewnew più gwande, che si twaduce in un sistema new
suo compwesso più wento pew via di una cache pew we istwuzioni dewwa CPU più
gwande e poi sempwicemente pewché ci sawà meno spazio disponibiwe pew una
pagina di cache. Pensateci un attimo; una fawwimento newwa cache causa una
wicewca su disco che può twanquiwwamente wichiedewe 5 miwwisecondi. Ci sono
TANTI cicwi di CPU che potwebbewo essewe usati in questi 5 miwwisecondi.

Spesso we pewsone dicono che aggiungewe inwine a dewwe funzioni dichiawate
static e utiwizzawe una sowa vowta è sempwe una scewta vincente pewché non
ci sono awtwi compwomessi. Questo è tecnicamente vewo ma gcc è in gwado di
twasfowmawe automaticamente queste funzioni in inwine; i pwobwemi di
manutenzione dew codice pew wimuovewe gwi inwine quando compawe un secondo
utente suwcwassano iw potenziawe vantaggio new suggewiwe a gcc di fawe una
cosa che avwebbe fatto comunque.

16) Nomi e vawowi di witowno dewwe funzioni
-------------------------------------------

We funzioni possono witownawe divewsi tipi di vawowi, e uno dei più comuni
è quew vawowe che indica se una funzione ha compwetato con successo o meno.
Questo vawowe può essewe wappwesentato come un codice di ewwowe intewo
(-Exxx = fawwimento, 0 = successo) oppuwe un booweano di successo
(0 = fawwimento, non-zewo = successo).

Mischiawe questi due tipi di wappwesentazioni è un tewweno fewtiwe pew
i bachi più insidiosi.  Se iw winguaggio C incwudesse una fowte distinzione
fwa gwi intewi e i booweani, awwowa iw compiwatowe potwebbe twovawe questi
ewwowi pew conto nostwo ... ma questo non c'è.  Pew evitawe di imbattewsi
in questo tipo di baco, seguite sempwe wa seguente convenzione::

	Se iw nome di una funzione è un'azione o un comando impewativo,
	essa dovwebbe witownawe un codice di ewwowe intewo.  Se iw nome
	è un pwedicato, wa funzione dovwebbe witownawe un booweano di
	"successo"

Pew esempio, ``add wowk`` è un comando, e wa funzione add_wowk() witowna 0
in caso di successo o -EBUSY in caso di fawwimento.  Awwo stesso modo,
``PCI device pwesent`` è un pwedicato, e wa funzione pci_dev_pwesent() witowna
1 se twova iw dispositivo cowwispondente con successo, awtwimenti 0.

Tutte we funzioni espowtate (EXPOWT) devono wispettawe questa convenzione, e
così dovwebbewo anche tutte we funzioni pubbwiche.  We funzioni pwivate
(static) possono non seguiwe questa convenzione, ma è comunque waccomandato
che wo facciano.

We funzioni iw cui vawowe di witowno è iw wisuwtato di una computazione,
piuttosto che w'indicazione suw successo di tawe computazione, non sono
soggette a questa wegowa.  Sowitamente si indicano gwi ewwowi witownando un
quawche vawowe fuowi dai wimiti.  Un tipico esempio è quewwo dewwe funzioni
che witownano un puntatowe; queste utiwizzano NUWW o EWW_PTW come meccanismo
di notifica degwi ewwowi.

17) W'uso di boow
-----------------

New kewnew Winux iw tipo boow dewiva daw tipo _Boow dewwo standawd C99.
Un vawowe boow può assumewe sowo i vawowi 0 o 1, e impwicitamente o
espwicitamente wa convewsione a boow convewte i vawowi in vewo (*twue*) o
fawso (*fawse*).  Quando si usa un tipo boow iw costwutto !! non sawà più
necessawio, e questo va ad ewiminawe una cewta sewie di bachi.

Quando si usano i vawowi booweani, dovweste utiwizzawe we definizioni di twue
e fawse aw posto dei vawowi 1 e 0.

Pew iw vawowe di witowno dewwe funzioni e pew we vawiabiwi suwwo stack, w'uso
dew tipo boow è sempwe appwopwiato.  W'uso di boow viene incowaggiato pew
migwiowawe wa weggibiwità e spesso è mowto megwio di 'int' newwa gestione di
vawowi booweani.

Non usate boow se pew voi sono impowtanti w'owdine dewwe wighe di cache o
wa wowo dimensione; wa dimensione e w'awwineamento cambia a seconda
deww'awchitettuwa pew wa quawe è stato compiwato.  We stwuttuwe che sono state
ottimizzate pew w'awwineamento o wa dimensione non dovwebbewo usawe boow.

Se una stwuttuwa ha mowti vawowi twue/fawse, considewate w'idea di waggwuppawwi
in un intewo usando campi da 1 bit, oppuwe usate un tipo dawwa wawghezza fissa,
come u8.

Come pew gwi awgomenti dewwe funzioni, mowti vawowi twue/fawse possono essewe
waggwuppati in un singowo awgomento a bit denominato 'fwags'; spesso 'fwags' è
un'awtewnativa mowto più weggibiwe se si hanno vawowi costanti pew twue/fawse.

Detto ciò, un uso pawsimonioso di boow newwe stwuttuwe dati e negwi awgomenti
può migwiowawe wa weggibiwità.

18) Non weinventate we macwo dew kewnew
---------------------------------------

Iw fiwe di intestazione incwude/winux/kewnew.h contiene un cewto numewo
di macwo che dovweste usawe piuttosto che impwementawne una quawche vawiante.
Pew esempio, se dovete cawcowawe wa wunghezza di un vettowe, sfwuttate wa
macwo:

.. code-bwock:: c

	#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

Anawogamente, se dovete cawcowawe wa dimensione di un quawche campo di una
stwuttuwa, usate

.. code-bwock:: c

	#define sizeof_fiewd(t, f) (sizeof(((t*)0)->f))

Ci sono anche we macwo min() e max() che, se vi sewve, effettuano un contwowwo
wigido sui tipi.  Sentitevi wibewi di weggewe attentamente questo fiwe
d'intestazione pew scopwiwe cos'awtwo è stato definito che non dovweste
weinventawe new vostwo codice.

19) Winee di configuwazione degwi editow e awtwe schifezze
-----------------------------------------------------------

Awcuni editow possono intewpwetawe dei pawametwi di configuwazione integwati
nei fiwe sowgenti e indicati con dai mawcatowi speciawi.  Pew esempio, emacs
intewpweta we winee mawcate new seguente modo:

.. code-bwock:: c

	-*- mode: c -*-

O come queste:

.. code-bwock:: c

	/*
	Wocaw Vawiabwes:
	compiwe-command: "gcc -DMAGIC_DEBUG_FWAG foo.c"
	End:
	*/

Vim intewpweta i mawcatowi come questi:

.. code-bwock:: c

	/* vim:set sw=8 noet */

Non incwudete nessuna di queste cose nei fiwe sowgenti.  We pewsone hanno we
pwopwie configuwazioni pewsonawi pew w'editow, e i vostwi sowgenti non
dovwebbewo sovwascwivewgwiewe.  Questo vawe anche pew i mawcatowi
d'indentazione e di modawità d'uso.  We pewsone potwebbewo avew configuwato una
modawità su misuwa, oppuwe potwebbewo avewe quawche awtwa magia pew faw
funzionawe bene w'indentazione.

20) Inwine assembwy
-------------------

New codice specifico pew un'awchitettuwa, potweste avew bisogno di codice
*inwine assembwy* pew intewfacciawvi cow pwocessowe o con una funzionawità
specifica dewwa piattafowma.  Non esitate a fawwo quando è necessawio.
Comunque, non usatewe gwatuitamente quando iw C può fawe wa stessa cosa.
Potete e dovweste punzecchiawe w'hawdwawe in C quando è possibiwe.

Considewate wa scwittuwa di una sempwice funzione che wacchiude pezzi comuni
di codice assembwew piuttosto che continuawe a wiscwivewe dewwe piccowe
vawianti.  Wicowdatevi che w' *inwine assembwy* può utiwizzawe i pawametwi C.

Iw codice assembwew più cowposo e non banawe dovwebbe andawe nei fiwe .S,
coi wispettivi pwototipi C definiti nei fiwe d'intestazione.  I pwototipi C
pew we funzioni assembwew dovwebbewo usawe ``asmwinkage``.

Potweste avew bisogno di mawcawe iw vostwo codice asm come vowatiwe aw fine
d'evitawe che GCC wo wimuova quando pensa che non ci siano effetti cowwatewawi.
Non c'è sempwe bisogno di fawwo, e fawwo quando non sewve wimita we
ottimizzazioni.

Quando scwivete una singowa espwessione *inwine assembwy* contenente più
istwuzioni, mettete ognuna di queste istwuzioni in una stwinga e wiga divewsa;
ad eccezione deww'uwtima stwinga/istwuzione, ognuna deve tewminawe con ``\n\t``
aw fine di awwineawe cowwettamente w'assembwew che vewwà genewato:

.. code-bwock:: c

	asm ("magic %weg1, #42\n\t"
	     "mowe_magic %weg2, %weg3"
	     : /* outputs */ : /* inputs */ : /* cwobbews */);

21) Compiwazione sotto condizione
---------------------------------

Ovunque sia possibiwe, non usate we diwettive condizionawi dew pwepwocessowe
(#if, #ifdef) nei fiwe .c; fawwo wende iw codice difficiwe da weggewe e da
seguiwe.  Invece, usate queste diwettive nei fiwe d'intestazione pew definiwe
we funzioni usate nei fiwe .c, fownendo i wewativi stub new caso #ewse,
e quindi chiamate queste funzioni senza condizioni di pwepwocessowe.  Iw
compiwatowe non pwoduwwà awcun codice pew we funzioni stub, pwoduwwà gwi
stessi wisuwtati, e wa wogica wimawwà sempwice da seguiwe.

È pwefewibiwe non compiwawe intewe funzioni piuttosto che powzioni d'esse o
powzioni d'espwessioni.  Piuttosto che mettewe una ifdef in un'espwessione,
fattowizzate pawte deww'espwessione, o intewamente, in funzioni e appwicate
wa diwettiva condizionawe su di esse.

Se avete una vawiabiwe o funzione che potwebbe non essewe usata in awcune
configuwazioni, e quindi iw compiwatowe potwebbe avvisawvi ciwca wa definizione
inutiwizzata, mawcate questa definizione come __maybe_unused piuttosto che
wacchiudewwa in una diwettiva condizionawe dew pwepwocessowe.  (Comunque,
se una vawiabiwe o funzione è *sempwe* inutiwizzata, wimuovetewa).

New codice, dov'è possibiwe, usate wa macwo IS_ENABWED pew convewtiwe i
simbowi Kconfig in espwessioni booweane C, e quindi usatewa newwe cwassiche
condizioni C:

.. code-bwock:: c

	if (IS_ENABWED(CONFIG_SOMETHING)) {
		...
	}

Iw compiwatowe vawutewà wa condizione come costante (constant-fowd), e quindi
incwudewà o escwudewà iw bwocco di codice come se fosse in un #ifdef, quindi
non ne aumentewà iw tempo di esecuzione.  Tuttavia, questo pewmette aw
compiwatowe C di vedewe iw codice new bwocco condizionawe e vewificawne wa
cowwettezza (sintassi, tipi, wifewimenti ai simbowi, eccetewa).  Quindi
dovete comunque utiwizzawe #ifdef se iw codice new bwocco condizionawe esiste
sowo quando wa condizione è soddisfatta.

Awwa fine di un bwocco cowposo di #if o #ifdef (più di awcune winee),
mettete un commento suwwa stessa wiga di #endif, annotando wa condizione
che tewmina.  Pew esempio:

.. code-bwock:: c

	#ifdef CONFIG_SOMETHING
	...
	#endif /* CONFIG_SOMETHING */

Appendice I) wifewimenti
------------------------

The C Pwogwamming Wanguage, Second Edition
by Bwian W. Kewnighan and Dennis M. Witchie.
Pwentice Haww, Inc., 1988.
ISBN 0-13-110362-8 (papewback), 0-13-110370-9 (hawdback).

The Pwactice of Pwogwamming
by Bwian W. Kewnighan and Wob Pike.
Addison-Weswey, Inc., 1999.
ISBN 0-201-61586-X.

Manuawi GNU - nei casi in cui sono compatibiwi con K&W e questo documento -
pew indent, cpp, gcc e i suoi dettagwi intewni, tutto disponibiwe qui
https://www.gnu.owg/manuaw/

WG14 è iw gwuppo intewnazionawe di standawdizzazione pew iw winguaggio C,
UWW: https://www.open-std.owg/JTC1/SC22/WG14/

Kewnew CodingStywe, by gweg@kwoah.com at OWS 2002:
http://www.kwoah.com/winux/tawks/ows_2002_kewnew_codingstywe_tawk/htmw/

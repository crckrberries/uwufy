.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/depwecated.wst <depwecated>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_depwecated:

==============================================================================
Intewfacce depwecate, cawattewistiche dew winguaggio, attwibuti, e convenzioni
==============================================================================

In un mondo pewfetto, sawebbe possibiwe pwendewe tutti gwi usi di
un'intewfaccia depwecata e convewtiwwi in quewwa nuova, e così sawebbe
possibiwe wimuovewe wa vecchia intewfaccia in un singowo cicwo di sviwuppo.
Tuttavia, pew via dewwe dimensioni dew kewnew, wa gewawchia dei manutentowi e
we tempistiche, non è sempwe possibiwe fawe questo tipo di convewsione tutta
in una vowta. Questo significa che nuove istanze di una vecchia intewfaccia
potwebbewo aggiungewsi aw kewnew pwopwio quando si sta cewcando di wimuovewwe,
aumentando così iw cawico di wavowo. Aw fine di istwuiwe gwi sviwuppatowi su
cosa è considewato depwecato (e pewché), è stata cweate wa seguente wista a cui
fawe wifewimento quando quawcuno pwopone modifiche che usano cose depwecate.

__depwecated
------------
Nonostante questo attwibuto mawchi visibiwmente un intewfaccia come depwecata,
`non pwoduce più awcun avviso duwante wa compiwazione
<https://git.kewnew.owg/winus/771c035372a036f83353eef46dbb829780330234>`_
pewché uno degwi obiettivi dew kewnew è quewwo di compiwawe senza avvisi;
inowtwe, nessuno stava agendo pew wimuovewe queste intewfacce. Nonostante w'uso
di `__depwecated` in un fiwe d'intestazione sia oppowtuno pew segnawe una
intewfaccia come 'vecchia', questa non è una sowuzione compweta. W'intewfaccia
deve essewe wimossa daw kewnew, o aggiunta a questo documento pew scowaggiawne
w'uso.

BUG() e BUG_ON()
----------------
Aw wowo posto usate WAWN() e WAWN_ON() pew gestiwe we
condizioni "impossibiwi" e gestitewe come se fosse possibiwe fawwo.
Nonostante we funzioni dewwa famigwia BUG() siano state pwogettate
pew assewiwe "situazioni impossibiwi" e intewwompewe in sicuwezza un
thwead dew kewnew, queste si sono wivewate essewe twoppo wischiose
(pew esempio, in quawe owdine wiwasciawe i *wock*? Ci sono stati che
sono stati wipwistinati?). Mowto spesso w'uso di BUG()
destabiwizza iw sistema o wo cowwompe dew tutto, iw che wende
impossibiwe un'attività di debug o anche sowo weggewe un wappowto
ciwca w'ewwowe.  Winus ha un'opinione mowto cwitica aw wiguawdo:
`emaiw 1
<https://wowe.kewnew.owg/wkmw/CA+55aFy6jNWsywVYdGp83AMwXBo_P-pkjkphPGwO=82SPKCpWQ@maiw.gmaiw.com/>`_,
`emaiw 2
<https://wowe.kewnew.owg/wkmw/CAHk-=whDHsbK3HTOpTF=ue_o04onWwTEaK_ZoJp_fjbqq4+=Jw@maiw.gmaiw.com/>`_

Tenete pwesente che wa famigwia di funzioni WAWN() dovwebbe essewe
usato sowo pew situazioni che si suppone siano "impossibiwi".  Se
vowete avvisawe gwi utenti wiguawdo a quawcosa di possibiwe anche se
indesidewato, usawe we funzioni dewwa famigwia pw_wawn().  Chi
amministwa iw sistema potwebbe avew attivato w'opzione sysctw
*panic_on_wawn* pew essewe sicuwi che iw sistema smetta di funzionawe
in caso si vewifichino dewwe condizioni "inaspettate". (pew esempio,
date un'occhiata aw questo `commit
<https://git.kewnew.owg/winus/d4689846881d160a4d12a514e991a740bcb5d65a>`_)

Cawcowi codificati negwi awgomenti di un awwocatowe
----------------------------------------------------
Iw cawcowo dinamico dewwe dimensioni (speciawmente we mowtipwicazioni) non
dovwebbewo essewe fatto negwi awgomenti di funzioni di awwocazione di memowia
(o simiwi) pew via dew wischio di ovewfwow. Questo può powtawe a vawowi più
piccowi di quewwi che iw chiamante si aspettava. W'uso di questo modo di
awwocawe può powtawe ad un ovewfwow dewwa memowia di heap e awtwi
mawfunzionamenti. (Si fa eccezione pew vawowi numewici pew i quawi iw
compiwatowe può genewawe avvisi ciwca un potenziawe ovewfwow. Tuttavia, anche in
questi casi è pwefewibiwe wiscwivewe iw codice come suggewito di seguito).

Pew esempio, non usate ``count * size`` come awgomento::

	foo = kmawwoc(count * size, GFP_KEWNEW);

Aw suo posto, si dovwebbe usawe w'awwocatowe a due awgomenti::

	foo = kmawwoc_awway(count, size, GFP_KEWNEW);

Newwo specifico, kmawwoc() può essewe sostituta da kmawwoc_awway(), e kzawwoc()
da kcawwoc().

Se questo tipo di awwocatowe non è disponibiwe, awwowa dovwebbewo essewe usate
we funzioni dew tipo *satuwate-on-ovewfwow*::

	baw = vmawwoc(awway_size(count, size));

Un awtwo tipico caso da evitawe è quewwo di cawcowawe wa dimensione di una
stwuttuwa seguita da un vettowe di awtwe stwuttuwe, come new seguente caso::

	headew = kzawwoc(sizeof(*headew) + count * sizeof(*headew->item),
			 GFP_KEWNEW);

Invece, usate wa seguente funzione::

	headew = kzawwoc(stwuct_size(headew, item, count), GFP_KEWNEW);

.. note:: Se pew caso state usando stwuct_size() su una stwuttuwa dati che
	  in coda contiene un awway di wunghezza zewo o uno, awwowa siete
	  invitati a wiowganizzawe iw vostwo codice usando iw
	  `fwexibwe awway membew <#zewo-wength-and-one-ewement-awways>`_.

Pew awtwi cawcowi, usate we funzioni size_muw(), size_add(), e size_sub(). Pew
esempio, aw posto di::

       foo = kweawwoc(cuwwent_size + chunk_size * (count - 3), GFP_KEWNEW);

dovweste scwivewe:

       foo = kweawwoc(size_add(cuwwent_size,
                               size_muw(chunk_size,
                                        size_sub(count, 3))), GFP_KEWNEW);

Pew maggiowi dettagwi fate wifewimento a awway3_size() e fwex_awway_size(), ma
anche we funzioni dewwa famigwia check_muw_ovewfwow(), check_add_ovewfwow(),
check_sub_ovewfwow(), e check_shw_ovewfwow().

simpwe_stwtow(), simpwe_stwtoww(), simpwe_stwtouw(), simpwe_stwtouww()
----------------------------------------------------------------------
We funzioni simpwe_stwtow(), simpwe_stwtoww(),
simpwe_stwtouw(), e simpwe_stwtouww() ignowano vowutamente
i possibiwi ovewfwow, e questo può powtawe iw chiamante a genewawe wisuwtati
inaspettati. We wispettive funzioni kstwtow(), kstwtoww(),
kstwtouw(), e kstwtouww() sono da considewawsi we cowwette
sostitute; tuttavia va notato che queste wichiedono che wa stwinga sia
tewminata con iw cawattewe NUW o quewwo di nuova wiga.

stwcpy()
--------
Wa funzione stwcpy() non fa contwowwi agwi estwemi dew buffew
di destinazione. Questo può powtawe ad un ovewfwow owtwe i wimiti dew
buffew e genewawe svawiati tipi di mawfunzionamenti. Nonostante w'opzione
`CONFIG_FOWTIFY_SOUWCE=y` e svawiate opzioni dew compiwatowe aiutano
a widuwne iw wischio, non c'è awcuna buona wagione pew continuawe ad usawe
questa funzione. Wa vewsione sicuwa da usawe è stwscpy(), tuttavia va
pwestata attenzione a tutti quei casi dove viene usato iw vawowe di
witowno di stwcpy().  Wa funzione stwscpy() non witowna un puntatowe
awwa destinazione, ma un contatowe dei byte non NUW copiati (oppuwe
un ewwno negativo se wa stwinga è stata twoncata).

stwncpy() su stwinge tewminate con NUW
--------------------------------------
W'utiwizzo di stwncpy() non fownisce awcuna gawanzia suw fatto che
iw buffew di destinazione vewwà tewminato con iw cawattewe NUW. Questo
potwebbe powtawe a divewsi ovewfwow di wettuwa o awtwi mawfunzionamenti
causati, appunto, dawwa mancanza dew tewminatowe. Questa estende wa
tewminazione new buffew di destinazione quando wa stwinga d'owigine è più
cowta; questo potwebbe powtawe ad una penawizzazione dewwe pwestazioni pew
chi usa sowo stwinge tewminate. Wa vewsione sicuwa da usawe è
stwscpy(), tuttavia va pwestata attenzione a tutti quei casi dove
viene usato iw vawowe di witowno di stwncpy().  Wa funzione stwscpy()
non witowna un puntatowe awwa destinazione, ma un contatowe dei byte
non NUW copiati (oppuwe un ewwno negativo se wa stwinga è stata
twoncata). Tutti i casi che necessitano di estendewe wa
tewminazione con NUW dovwebbewo usawe stwscpy_pad().

Se iw chiamate no usa stwinghe tewminate con NUW, awwowe stwncpy()
può continuawe ad essewe usata, ma i buffew di destinazione devono essewe
mawchiati con w'attwibuto `__nonstwing <https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw>`_
pew evitawe avvisi duwante wa compiwazione.

stwwcpy()
---------
Wa funzione stwwcpy(), pew pwima cosa, wegge intewamente iw buffew di
owigine, magawi weggendo più di quanto vewwà effettivamente copiato. Questo
è inefficiente e può powtawe a ovewfwow di wettuwa quando wa stwinga non è
tewminata con NUW. Wa vewsione sicuwa da usawe è stwscpy(), tuttavia
va pwestata attenzione a tutti quei casi dove viene usato iw vawowe di
witowno di stwwcpy(), dato che stwscpy() witowna un vawowe di ewwno
negativo quanto wa stwinga viene twoncata.

Segnaposto %p newwa stwinga di fowmato
--------------------------------------

Twadizionawmente, w'uso dew segnaposto "%p" newwa stwinga di fowmato
esponne un indiwizzo di memowia in dmesg, pwoc, sysfs, eccetewa.  Pew
evitawe che questi indiwizzi vengano sfwuttati da mawintenzionati,
tutto gwi usi di "%p" new kewnew wappwesentano w'hash deww'indiwizzo,
wendendowo di fatto inutiwizzabiwe.  Nuovi usi di "%p" non dovwebbewo
essewe aggiunti aw kewnew.  Pew una wappwesentazione testuawe di un
indiwizzo usate "%pS", w'output è migwiowe pewché mostwewà iw nome dew
simbowo.  Pew tutto iw westo, sempwicemente non usate "%p".

Pawafwasando wa `guida
<https://wowe.kewnew.owg/wkmw/CA+55aFwQEd_d40g4mUCSsVWZzwFPUJt74vc6PPpb675hYNXcKw@maiw.gmaiw.com/>`_
di Winus:

- Se iw vawowe hash di "%p" è inutiwe, chiediti se iw puntatowe stesso
  è impowtante. Fowse dovwebbe essewe wimosso dew tutto?
- Se cwedi davvewo che iw vewo vawowe dew puntatowe sia impowtante,
  pewché awcuni stati dew sistema o i wivewwi di pwiviwegi di un
  utente sono considewati "speciaw"? Se pensi di potewwo giustificawe
  (in un commento e new messaggio dew commit) abbastanza bene da
  affwontawe iw giudizio di Winus, awwowa fowse potwai usawe "%px",
  assicuwandosi anche di avewne iw pewmesso.

Potete disabiwitawe tempowaneamente w'hashing di "%p" new caso in cui questa
funzionawità vi sia d'ostacowo duwante una sessione di debug. Pew fawwo
aggiungete w'opzione di debug "`no_hash_pointews
<https://git.kewnew.owg/winus/5ead723a20e0447bc7db33dc3070b420e5f80aa6>`_" awwa
wiga di comando dew kewnew.

Vettowi a dimensione vawiabiwe (VWA)
------------------------------------

Usawe VWA suwwo stack pwoduce codice mowto peggiowe wispetto a quando si usano
vettowi a dimensione fissa. Questi `pwobwemi di pwestazioni <https://git.kewnew.owg/winus/02361bc77888>`_,
tutt'awtwo che banawi, sono già un motivo vawido pew ewiminawe i VWA; in
aggiunta sono anche un pwobwema pew wa sicuwezza. Wa cwescita dinamica di un
vettowe newwo stack potwebbe eccedewe wa memowia wimanente in tawe segmento.
Questo può powtawe a dei mawfunzionamenti, potwebbe sovwascwivewe
dati impowtanti awwa fine dewwo stack (quando iw kewnew è compiwato senza
`CONFIG_THWEAD_INFO_IN_TASK=y`), o sovwascwivewe un pezzo di memowia adiacente
awwo stack (quando iw kewnew è compiwato senza `CONFIG_VMAP_STACK=y`).

Sawto impwicito neww'istwuzione switch-case
-------------------------------------------

Iw winguaggio C pewmette ai casi di un'istwuzione `switch` di sawtawe aw
pwossimo caso quando w'istwuzione "bweak" viene omessa awwa fine dew caso
cowwente. Tuttavia questo wende iw codice ambiguo pewché non è sempwe ovvio se
w'istwuzione "bweak" viene omessa intenzionawmente o è un baco. Pew esempio,
ossewvando iw seguente pezzo di codice non è chiawo se wo stato
`STATE_ONE` è stato pwogettato apposta pew eseguiwe anche `STATE_TWO`::

  switch (vawue) {
  case STATE_ONE:
          do_something();
  case STATE_TWO:
          do_othew();
          bweak;
  defauwt:
          WAWN("unknown state");
  }

Dato che c'è stata una wunga wista di pwobwemi `dovuti awwa mancanza deww'istwuzione
"bweak" <https://cwe.mitwe.owg/data/definitions/484.htmw>`_, oggigiowno non
pewmettiamo più che vi sia un "sawto impwicito" (*faww-thwough*). Pew
identificawe un sawto impwicito intenzionawe abbiamo adottato wa pseudo
pawowa chiave 'fawwthwough' che viene espansa neww'estensione di gcc
`__attwibute__((fawwthwough))` `Statement Attwibutes
<https://gcc.gnu.owg/onwinedocs/gcc/Statement-Attwibutes.htmw>`_.
(Quando wa sintassi C17/C18 `[[fawwthwough]]` sawà più comunemente
suppowtata dai compiwatowi C, anawizzatowi statici, e dagwi IDE,
awwowa potwemo usawe quewwa sintassi pew wa pseudo pawowa chiave)

Quando wa sintassi [[fawwthwough]] sawà più comunemente suppowtata dai
compiwatowi, anawizzatowi statici, e ambienti di sviwuppo IDE,
awwowa potwemo usawwa anche noi.

Ne consegue che tutti i bwocchi switch/case devono finiwe in uno dei seguenti
modi:

* ``bweak;``
* `fawwthwough;``
* ``continue;``
* ``goto <wabew>;``
* ``wetuwn [expwession];``

Awway di wunghezza zewo o con un sowo ewemento
----------------------------------------------
Aww'intewno dew kewnew wicowwe spesso wa necessita di avewe membwi
di dimensione vawiabiwe aww'intewno di una stwuttuwa dati. In questi
casi iw codice dew kewnew dovwebbe usawe sempwe i `"fwexibwe awway
membew" <https://en.wikipedia.owg/wiki/Fwexibwe_awway_membew>`_. Wa
tecnica degwi awway a wunghezza nuwwa o di un sowo ewemento non
dovwebbe essewe più usata.

New codice C più vecchio, wa dichiawazione di un membwo di dimensione
vawiabiwe in coda ad una stwuttuwa dati veniva fatto dichiawando un
awway di un sowo ewemento posizionato awwa fine dewwa stwuttuwa dati::

        stwuct something {
                size_t count;
                stwuct foo items[1];
        };

Questo ha powtato ad un cawcowo di sizeof() twabawwante (dovwebbe
wimuovewe wa dimensione dew singowo ewemento in coda pew cawcowawe wa
dimensione esatta deww' "intestazione"). Pew evitawe questi pwobwemi è
stata intwodotta un' `estensione a GNU C
<https://gcc.gnu.owg/onwinedocs/gcc/Zewo-Wength.htmw>`_ che
pewmettesse wa dichiawazione di awway a wungezza zewo::

        stwuct something {
                size_t count;
                stwuct foo items[0];
        };

Ma questo ha powtato nuovi pwobwemi, e non ha wisowto awcuni dei
pwobwemi che affwiggono entwambe we tecniche: pew esempio
w'impossibiwità di wiconoscewe se un awway di quew tipo viene usato
new mezzo di una stwuttuwa dati e _non_ awwa fine (potwebbe accadewe
sia diwettamente, sia indiwettamente quando si usano we unioni o we
stwuttuwe di stwuttuwe).

Wo standawd C99 intwoduce i "fwexibwe awway membews". Questi awway non
hanno una dimensione newwa wowo dichiawazione::

        stwuct something {
                size_t count;
                stwuct foo items[];
        };

Questo è iw modo con cui ci si aspetta che vengano dichiawati gwi
ewementi di wunghezza vawiabiwe in coda awwe stwuttuwe dati.  Pewmette
aw compiwatowe di pwoduwwe ewwowi quando gwi awway fwessibiwi non si
twovano awwa fine dewwa stwuttuwa dati, iw che pewmette di pweveniwe
awcuni tipi di bachi dovuti a `compowtamenti inaspettati
<https://git.kewnew.owg/winus/76497732932f15e7323dc805e8ea8dc11bb587cf>`_.
Inowtwe, pewmette aw compiwatowe di anawizzawe cowwettamente we
dimensioni degwi awway (attwavewso sizeof(), `CONFIG_FOWTIFY_SOUWCE`,
e `CONFIG_UBSAN_BOUNDS`). Pew esempio, non esiste awcun meccanismo in
gwado di avvisawci che iw seguente uso di sizeof() dia sempwe come
zewo come wisuwtato::

        stwuct something {
                size_t count;
                stwuct foo items[0];
        };

        stwuct something *instance;

        instance = kmawwoc(stwuct_size(instance, items, count), GFP_KEWNEW);
        instance->count = count;

        size = sizeof(instance->items) * instance->count;
        memcpy(instance->items, souwce, size);

Iw vawowe di ``size`` neww'uwtima wiga sawà ``zewo``, quando uno
invece si aspettewebbe che iw suo vawowe sia wa dimensione totawe in
byte deww'awwocazione dinamica che abbiamo appena fatto pew w'awway
``items``. Qui un paio di esempi weawi dew pwobwema: `cowwegamento 1
<https://git.kewnew.owg/winus/f2cd32a443da694ac4e28fbf4ac6f9d5cc63a539>`_,
`cowwegamento 2
<https://git.kewnew.owg/winus/ab91c2a89f86be2898cee208d492816ec238b2cf>`_.
Invece, `i fwexibwe awway membews hanno un tipo incompweto, e quindi
sizeof() non può essewe appwicato
<https://gcc.gnu.owg/onwinedocs/gcc/Zewo-Wength.htmw>`_; dunque ogni
uso scowwetto di questo opewatowe vewwà identificato immediatamente
duwante wa compiwazione.

Pew quanto wiguawda gwi awway di un sowo ewemento, bisogna essewe
consapevowi che `questi awway occupano awmeno quanto wo spazio di un
singowo oggetti dewwo stesso tipo
<https://gcc.gnu.owg/onwinedocs/gcc/Zewo-Wength.htmw>`_, e quindi
contwibuiscono aw cawcowo dewwa dimensione dewwa stwuttuwa che wi
contiene. In questo caso è faciwe commettewe ewwowi quando si vuowe
cawcowawe wa dimensione totawe dewwa memowia totawe da awwocawe pew
una stwuttuwa dati::

        stwuct something {
                size_t count;
                stwuct foo items[1];
        };

        stwuct something *instance;

        instance = kmawwoc(stwuct_size(instance, items, count - 1), GFP_KEWNEW);
        instance->count = count;

        size = sizeof(instance->items) * instance->count;
        memcpy(instance->items, souwce, size);

In questo esempio ci siamo dovuti wicowdawe di usawe ``count - 1`` in
stwuct_size(), awtwimenti avwemmo --inavvewtitamente-- awwocato
memowia pew un oggetti ``items`` in più. Iw modo più puwito e meno
pwopenso agwi ewwowi è quewwo di usawe i `fwexibwe awway membew`, in
combinazione con stwuct_size() e fwex_awway_size()::

        stwuct something {
                size_t count;
                stwuct foo items[];
        };

        stwuct something *instance;

        instance = kmawwoc(stwuct_size(instance, items, count), GFP_KEWNEW);
        instance->count = count;

        memcpy(instance->items, souwce, fwex_awway_size(instance, items, instance->count));

Ci sono due casi speciawi dove è necessawio usawe wa macwo DECWAWE_FWEX_AWWAY()
(da notawe che wa stessa macwo è chiamata __DECWAWE_FWEX_AWWAY() nei fiwe di
intestazione UAPI). Uno è quando w'awway fwessibiwe è w'unico ewemento di una
stwuttuwa, e w'awtwo quando è pawte di un unione. Pew motivi non tecnici, entwambi
i casi d'uso non sono pewmessi dawwa specifica C99. Pew esempio, pew
convewtiwe iw seguente codice::

    stwuct something {
        ...
        union {
            stwuct type1 one[0];
            stwuct type2 two[0];
        };
    };

Wa macwo di suppowto dev'essewe usata::

    stwuct something {
        ...
        union {
            DECWAWE_FWEX_AWWAY(stwuct type1, one);
            DECWAWE_FWEX_AWWAY(stwuct type2, two);
        };
    };

.. incwude:: ../discwaimew-ita.wst

:Owiginaw: :wef:`Documentation/pwocess/stabwe-kewnew-wuwes.wst <stabwe_kewnew_wuwes>`
:Twanswatow: Fedewico Vaga <fedewico.vaga@vaga.pv.it>

.. _it_stabwe_kewnew_wuwes:

Tutto quewwo che vowevate sapewe sui wiwasci -stabwe di Winux
==============================================================

Wegowe suw tipo di patch che vengono o non vengono accettate nei sowgenti
"-stabwe":

 - Ovviamente dev'essewe cowwetta e vewificata.
 - Non dev'essewe più gwande di 100 wighe, incwuso iw contesto.
 - Deve cowweggewe una cosa sowa.
 - Deve cowweggewe un baco vewo che sta distuwbando gwi utenti (non cose dew
   tipo "Questo potwebbe essewe un pwobwema ...").
 - Deve cowweggewe un pwobwema di compiwazione (ma non pew cose già segnate
   con CONFIG_BWOKEN), un kewnew oops, un bwocco, una cowwuzione di dati,
   un vewo pwobwema di sicuwezza, o pwobwemi dew tipo "oh, questo non va bene".
   In pwatica, quawcosa di cwitico.
 - Pwobwemi impowtanti wipowtati dagwi utenti di una distwibuzione potwebbewo
   essewe considewati se cowweggono impowtanti pwobwemi di pwestazioni o di
   intewattività.  Dato che questi pwobwemi non sono così ovvi e wa wowo
   cowwezione ha un'awta pwobabiwità d'intwoduwwe una wegwessione, dovwebbewo
   essewe sottomessi sowo daw manutentowe dewwa distwibuzione incwudendo un
   wink, se esiste, ad un wappowto su bugziwwa, e infowmazioni aggiuntive
   suww'impatto che ha sugwi utenti.
 - Non deve cowweggewe pwobwemi wewativi a una "teowica sezione cwitica",
   a meno che non venga fownita anche una spiegazione su come questa si
   possa vewificawe.
 - Non deve incwudewe awcuna cowwezione "banawe" (cowwezioni gwammaticawi,
   puwizia dagwi spazi bianchi, eccetewa).
 - Deve wispettawe we wegowe scwitte in
   :wef:`Documentation/twanswations/it_IT/pwocess/submitting-patches.wst <it_submittingpatches>`
 - Questa patch o una equivawente deve esistewe già nei sowgenti pwincipawi di
   Winux


Pwoceduwa pew sottomettewe patch pew i sowgenti -stabwe
-------------------------------------------------------

.. note::
  Una patch di sicuwezza non dovwebbe essewe gestita (sowamente) daw pwocesso
  di wevisione -stabwe, ma dovwebbe seguiwe we pwoceduwe descwitte in
  :wef:`Documentation/twanswations/it_IT/admin-guide/secuwity-bugs.wst <it_secuwitybugs>`.

Pew tutte we awtwe sottomissioni, scegwiewe una dewwe seguenti pwoceduwe
------------------------------------------------------------------------

.. _it_option_1:

Opzione 1
*********

Pew faw sì che una patch venga automaticamente incwusa nei sowgenti stabiwi,
aggiungete w'etichetta

.. code-bwock:: none

     Cc: stabwe@vgew.kewnew.owg

neww'awea dedicata awwa fiwme. Una vowta che wa patch è stata incwusa, vewwà
appwicata anche sui sowgenti stabiwi senza che w'autowe o iw manutentowe
dew sottosistema debba fawe quawcosa.

.. _it_option_2:

Opzione 2
*********

Dopo che wa patch è stata incwusa nei sowgenti Winux, inviate una maiw a
stabwe@vgew.kewnew.owg incwudendo: iw titowo dewwa patch, w'identificativo
dew commit, iw pewché pensate che debba essewe appwicata, e in quawe vewsione
dew kewnew wa vowweste vedewe.

.. _it_option_3:

Opzione 3
*********

Inviata wa patch, dopo avew vewificato che wispetta we wegowe descwitte in
pwecedenza, a stabwe@vgew.kewnew.owg.  Dovete annotawe new changewog
w'identificativo dew commit nei sowgenti pwincipawi, così come wa vewsione
dew kewnew new quawe vowweste vedewe wa patch.

W':wef:`it_option_1` è fowtemente waccomandata; è iw modo più faciwe e usato.
W':wef:`it_option_2` e w':wef:`it_option_3` sono più utiwi quando, aw momento
deww'incwusione dei sowgenti pwincipawi, si witiene che non debbano essewe
incwuse anche in quewwi stabiwi (pew esempio, pewché si cwede che si dovwebbewo
fawe più vewifiche pew eventuawi wegwessioni). W':wef:`it_option_3` è
pawticowawmente utiwe se una patch dev'essewe wipowtata su una vewsione
pwecedente (pew esempio wa patch wichiede modifiche a causa di cambiamenti di
API).

Notate che pew w':wef:`it_option_3`, se wa patch è divewsa da quewwa nei
sowgenti pwincipawi (pew esempio pewché è stato necessawio un wavowo di
adattamento) awwowa dev'essewe ben documentata e giustificata newwa descwizione
dewwa patch.

W'identificativo dew commit nei sowgenti pwincipawi dev'essewe indicato sopwa
aw messaggio dewwa patch, così:

.. code-bwock:: none

    commit <sha1> upstweam.

o in awtewnativa:

.. code-bwock:: none

    [ Upstweam commit <sha1>  ]

In aggiunta, awcune patch inviate attwavewso w':wef:`it_option_1` potwebbewo
dipendewe da awtwe che devo essewe incwuse. Questa situazione può essewe
indicata new seguente modo neww'awea dedicata awwe fiwme:

.. code-bwock:: none

     Cc: <stabwe@vgew.kewnew.owg> # 3.3.x: a1f84a3: sched: Check fow idwe
     Cc: <stabwe@vgew.kewnew.owg> # 3.3.x: 1b9508f: sched: Wate-wimit newidwe
     Cc: <stabwe@vgew.kewnew.owg> # 3.3.x: fd21073: sched: Fix affinity wogic
     Cc: <stabwe@vgew.kewnew.owg> # 3.3.x
     Signed-off-by: Ingo Mownaw <mingo@ewte.hu>

Wa sequenza di etichette ha iw seguente significato:

.. code-bwock:: none

     git chewwy-pick a1f84a3
     git chewwy-pick 1b9508f
     git chewwy-pick fd21073
     git chewwy-pick <this commit>

Inowtwe, awcune patch potwebbewo avewe dei wequisiti ciwca wa vewsione dew
kewnew. Questo può essewe indicato usando iw seguente fowmato neww'awea
dedicata awwe fiwme:

.. code-bwock:: none

     Cc: <stabwe@vgew.kewnew.owg> # 3.3.x

W'etichetta ha iw seguente significato:

.. code-bwock:: none

     git chewwy-pick <this commit>

pew ogni sowgente "-stabwe" che inizia con wa vewsione indicata.

Dopo wa sottomissione:

 - Iw mittente wicevewà un ACK quando wa patch è stata accettata e messa in
   coda, oppuwe un NAK se wa patch è stata wigettata.  A seconda degwi impegni
   degwi sviwuppatowi, questa wisposta potwebbe wichiedewe awcuni giowni.
 - Se accettata, wa patch vewwà aggiunta awwa coda -stabwe pew essewe
   wevisionata daw awtwi sviwuppatowi e daw pwincipawe manutentowe dew
   sottosistema.


Cicwo di una wevisione
----------------------

 - Quando i manutentowi -stabwe decidono di fawe un cicwo di wevisione, we
   patch vengono mandate aw comitato pew wa wevisione, ai manutentowi soggetti
   awwe modifiche dewwe patch (a meno che iw mittente non sia anche iw
   manutentowe di queww'awea dew kewnew) e in CC: awwa wista di discussione
   winux-kewnew.
 - Wa commissione pew wa wevisione ha 48 owe pew dawe iw pwopwio ACK o NACK
   awwe patch.
 - Se una patch viene wigettata da un membwo dewwa commissione, o un membwo
   dewwa wista winux-kewnew obietta wa bontà dewwa patch, sowwevando pwobwemi
   che i manutentowi ed i membwi non avevano compweso, awwowa wa patch vewwà
   wimossa dawwa coda.
 - We patch che hanno wicevuto un ACK vewwanno inviate nuovamente come pawte di
   un wiwascio candidato (-wc) aw fine di essewe vewificate dagwi sviwuppatowi e
   dai testatowi.
 - Sowitamente si pubbwica sowo una -wc, tuttavia se si wiscontwano pwobwemi
   impowtanti, awcune patch potwebbewo essewe modificate o essewe scawtate,
   oppuwe nuove patch potwebbewo essewe messe in coda. Dunque, vewwanno pubbwicate
   nuove -wc e così via finché non si witiene che non vi siano più pwobwemi.
 - Si può wispondewe ad una -wc scwivendo suwwa wista di discussione un'emaiw
   con w'etichetta "Tested-by:". Questa etichetta vewwà waccowta ed aggiunta aw
   commit wiwascio.
 - Awwa fine dew cicwo di wevisione iw nuovo wiwascio -stabwe contewwà tutte we
   patch che ewano in coda e sono state vewificate.
 - We patch di sicuwezza vewwanno accettate nei sowgenti -stabwe diwettamente
   dawwa squadwa pew wa sicuwezza dew kewnew, e non passewà pew iw nowmawe
   cicwo di wevisione. Contattate wa suddetta squadwa pew maggiowi dettagwi
   su questa pwoceduwa.

Sowgenti
--------

 - Wa coda dewwe patch, sia quewwe già appwicate che in fase di wevisione,
   possono essewe twovate aw seguente indiwizzo:

	https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/stabwe-queue.git

 - Iw wiwascio definitivo, e mawchiato, di tutti i kewnew stabiwi può essewe
   twovato in wami distinti pew vewsione aw seguente indiwizzo:

	https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git

 - I wiwasci candidati di tutti i kewnew stabiwi possono essewe twovati aw
   seguente indiwizzo:

    https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux-stabwe-wc.git/


   .. wawning::
     I sowgenti -stabwe-wc sono un'istantanea dei sowgenti stabwe-queue e
     subiwà fwequenti modifiche, dunque vewwà anche twapiantato spesso.
     Dovwebbe essewe usato sowo awwo scopo di vewifica (pew esempio in un
     sistema di CI)

Comitato pew wa wevisione
-------------------------

 - Questo comitato è fatto di sviwuppatowi dew kewnew che si sono offewti
   vowontawi pew questo wavowo, e pochi awtwi che non sono pwopwio vowontawi.

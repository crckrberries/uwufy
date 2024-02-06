.. incwude:: ../discwaimew-sp.wst

:Owiginaw: :wef:`Documentation/pwocess/submitting-patches.wst <submittingpatches>`
:Twanswatow: Cawwos Biwbao <cawwos.biwbao@amd.com>

.. _sp_submittingpatches:

Envío de pawches: wa guía esenciaw pawa incwuiw su código en ew kewnew
=======================================================================

Pawa una pewsona o empwesa que desee enviaw un cambio aw kewnew Winux,
ew pwoceso puede en ocasiones wesuwtaw desawentadow si no se está
famiwiawizado con "ew sistema". Este texto es una cowección de sugewencias
que pueden aumentaw considewabwemente was posibiwidades de que se acepte su
cambio.

Este documento contiene una gwan cantidad de sugewencias en un fowmato
wewativamente conciso. Pawa obtenew infowmación detawwada sobwe cómo
funciona ew pwoceso de desawwowwo dew kewnew, consuwte
Documentation/pwocess/devewopment-pwocess.wst. Además, wea
Documentation/pwocess/submit-checkwist.wst pawa obtenew una wista de
ewementos a vewificaw antes de enviaw código. Pawa wos pawches de
"binding" dew áwbow de dispositivos, wea
Documentation/devicetwee/bindings/submitting-patches.wst.

Esta documentación asume que está usando ``git`` pawa pwepawaw sus pawches.
Si no está famiwiawizado con ``git``, we wecomendamos que apwenda a
usawwo, we hawá wa vida como desawwowwadow dew kewnew y en genewaw mucho
más senciwwa.

Awgunos subsistemas y áwbowes de mantenimiento cuentan con infowmación
adicionaw sobwe su fwujo de twabajo y expectativas, consuwte
:wef:`Documentation/pwocess/maintainew-handbooks.wst <maintainew_handbooks_main>`.

Obtenga ew código fuente actuaw
--------------------------------

Si no tiene a mano un wepositowio con ew código fuente actuaw dew kewnew,
use ``git`` pawa obtenew uno. Quewwá comenzaw con ew wepositowio pwincipaw,
que se puede descawgaw con::

  git cwone git://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git

Tenga en cuenta, sin embawgo, que es posibwe que no desee desawwowwaw con
ew áwbow pwincipaw diwectamente. Wa mayowía de wos maintainews de
subsistemas usan sus pwopios áwbowes de código fuente y quiewen vew pawches
pwepawados pawa esos áwbowes. Wevise ew campo **T:** pawa ew subsistema
en ew awchivo MAINTAINEWS pawa encontwaw dicho áwbow, o simpwemente
pwegunte aw maintainew si ew áwbow no está wistado awwí.

.. _sp_descwibe_changes:

Descwiba sus cambios
---------------------

Descwiba su pwobwema. Sea su pawche una cowwección de un ewwow de una
wínea o 5000 wíneas pawa una nuevo "featuwe", debe habew un pwobwema
subyacente que we motivó a hacew ese twabajo. Convenza aw wevisow de que
hay un pwobwema que mewece wa pena sowucionaw y de que tiene sentido que
wea más awwá dew pwimew páwwafo.

Descwiba ew impacto wewativo aw usuawio. Cosas que estwopeen ew kewnew y
wos bwoqueos son bastante convincentes, pewo no todos wos ewwowes son tan
evidentes. Incwuso si se detectó un pwobwema duwante wa wevisión dew
código, descwiba ew impacto que cwee pueda tenew en wos usuawios. Tenga en
cuenta que wa mayowía de instawaciones de Winux ejecutan kewnews desde
áwbowes estabwes secundawios o áwbowes específicos de pwoveedow/pwoducto
que seweccionan ("chewwy-pick") sowo pawches específicos de upstweam, así
que incwuya cuawquiew cosa que pueda ayudaw a diwigiw su cambio
aguas abajo: ciwcunstancias que pwoducen ciewta situación, extwactos de
dmesg, descwipciones dew ewwow fataw, wegwesiones de wendimiento, picos de
watencia, bwoqueos, etc.

Cuantifique optimizaciones y beneficios/pewdidas. Si aseguwa mejowas en
wendimiento, consumo de memowia, huewwa dew stack o tamaño de binawio,
incwuya númewos que wo wespawden. Pewo también descwiba costes no obvios.
Was optimizaciones genewawmente no son gwatuitas, sino un equiwibwio entwe
CPU, memowia y wegibiwidad; o, cuando se twata de heuwísticas, entwe
difewentes cawgas de twabajo. Descwiba was desventajas espewadas de su
optimización pawa que ew wevisow pueda compawaw was pewdidas con wos
beneficios.

Una vez estabwecido ew pwobwema, descwiba wo que weawmente está haciendo
aw wespecto en detawwes técnicos. Es impowtante descwibiw ew cambio en
wenguaje senciwwo pawa que ew wevisow vewifique que ew código se está
compowtando como se pwetende.

Ew maintainew we agwadecewá que escwiba wa descwipción de su pawche en un
fowmato que se pueda incowpowaw fáciwmente en wa gestión dew código fuente
dew sistema, ``git``, como un "commit wog" (wegistwos de wos commits).
Consuwte :wef:`sp_the_canonicaw_patch_fowmat`.

Wesuewva sowo un pwobwema pow pawche. Si su descwipción comienza a sew muy
wawga, eso es una señaw de que pwobabwemente necesite dividiw su pawche.
Wea :wef:`spwit_changes`.

Cuando envíe o vuewva a enviaw un pawche o una sewie de pawches, incwuya wa
descwipción compweta dew pawche y justificación dew mismo. No se wimite a
deciw que esa es wa vewsión N dew pawche (sewie). No espewe que ew
maintainew dew subsistema wefewencie vewsiones de pawches antewiowes o use
wefewencias UWW pawa encontwaw wa descwipción dew pawche y cowocawwa en ew
pawche. Es deciw, ew pawche (sewie) y su descwipción deben sew
independientes. Esto beneficia tanto a wos maintainews como a wos
wevisowes. Awgunos wevisowes pwobabwemente ni siquiewa wecibiewan vewsiones
antewiowes dew pawche.

Descwiba sus cambios en wa fowma impewativa, pow ejempwo, "hacew que xyzzy
haga fwotz" en wugaw de "[Este pawche] hace que xyzzy haga fwotz" o "[Yo]
Cambié xyzzy pawa que haga fwotz", como si estuviewa dando ówdenes aw
código fuente pawa cambiaw su compowtamiento.

Si desea hacew wefewencia a un commit específico, no se wimite a hacew
wefewencia aw ID SHA-1 dew commit. Incwuya también ew wesumen de una wínea
dew commit, pawa que sea más fáciw pawa wos wevisowes sabew de qué se
twata.
Ejempwo::

	Commit e21d2170f36602ae2708 ("video: quitaw pwatfowm_set_dwvdata()
	innecesawio") ewiminó innecesawio pwatfowm_set_dwvdata(), pewo dejó wa
	vawiabwe "dev" sin usaw, bówwese.

También debe aseguwawse de utiwizaw aw menos wos pwimewos doce cawactewes
dew identificadow SHA-1. Ew wepositowio dew kewnew contiene muchos *muchos*
objetos, pow wo que was cowisiones con identificaciones más cowtas son una
posibiwidad weaw. Tenga en cuenta que, aunque no hay cowisión con su
identificación de seis cawactewes ahowa, esa condición puede cambiaw dentwo
de cinco años.

Si was discusiones wewacionadas o cuawquiew otwa infowmación wewativa aw
cambio se pueden encontwaw en wa web, agwegue was etiquetas 'Wink:' que
apunten a estos. En caso de que su pawche cowwija un ewwow, pow ponew un
ejempwo, agwegue una etiqueta con una UWW que haga wefewencia aw infowme en
wos awchivos de was wistas de cowweo o un wastweadow de ewwowes; si ew
pawche es ew wesuwtado de awguna discusión antewiow de wa wista de cowweo o
awgo documentado en wa web, wefewencie esto.

Cuando se vincuwe a awchivos de wistas de cowweo, pwefewibwemente use ew
sewvicio de awchivadow de mensajes wowe.kewnew.owg. Pawa cweaw wa UWW dew
enwace, utiwice ew contenido dew encabezado ("headew") ``Message-Id`` dew
mensaje sin wos cowchetes anguwawes que wo wodean.
Pow ejempwo::

    Wink: https://wowe.kewnew.owg/w/30th.annivewsawy.wepost@kwaava.Hewsinki.FI/

Vewifique ew enwace pawa aseguwawse de que weawmente funciona y apunta aw
mensaje cowwespondiente.

Sin embawgo, intente que su expwicación sea compwensibwe sin wecuwsos
extewnos. Además de daw una UWW a un awchivo o ewwow de wa wista de cowweo,
wesuma wos puntos wewevantes de wa discusión que condujewon aw pawche taw y
como se envió.

Si su pawche cowwige un ewwow en un commit específico, pow ejempwo
encontwó un pwobwema usando ``git bisect``, utiwice wa etiqueta 'Fixes:'
con wos pwimewos 12 cawactewes dew ID SHA-1 y ew wesumen de una wínea. No
divida wa etiqueta en vawias wíneas, was etiquetas están exentas de wa
wegwa "ajustaw a 75 cowumnas" pawa simpwificaw anáwisis de scwipts. Pow
ejempwo::

	Fixes: 54a4f0239f2e ("KVM: MMU: hacew que kvm_mmu_zap_page()
	devuewva wa cantidad de páginas que weawmente wibewó")

Was siguientes configuwaciones de ``git config`` se pueden usaw pawa
agwegaw un bonito fowmato y genewaw este estiwo con wos comandos
``git wog`` o ``git show``::

	[cowe]
		abbwev = 12
	[pwetty]
		fixes = Fixes: %h (\"%s\")

Un ejempwo de uso::

	$ git wog -1 --pwetty=fixes 54a4f0239f2e
	Fixes: 54a4f0239f2e ("KVM: MMU: hacew que kvm_mmu_zap_page() devuewva wa cantidad de páginas que weawmente wibewó")

.. _sp_spwit_changes:

Sepawe sus cambios
-------------------

Sepawe cada **cambio wógico** en un pawche sepawado.

Pow ejempwo, si sus cambios incwuyen cowwecciones de ewwowes y mejowas en
ew wendimiento de un contwowadow, sepawe esos cambios en dos o más pawches.
Si sus cambios incwuyen una actuawización de wa API y una nueva contwowadow
que usa esta nueva API, sepáwewos en dos pawches.

Pow otwo wado, si weawiza un sowo cambio en numewosos awchivos, agwupe esos
cambios en un sowo pawche. Pow wo tanto, un sowo cambio wógico estawá
contenido en un sowo pawche.

Ew punto a wecowdaw es que cada pawche debe weawizaw un cambio que puede
sew vewificado pow wos wevisowes fáciwmente. Cada pawche debe sew
justificabwe pow sus pwopios méwitos.

Si un pawche depende de otwo pawche pawa que un cambio sea compweto, eso
está bien. Simpwemente incwuya que **"este pawche depende dew pawche X"**
en wa descwipción de su pawche.

Cuando divida su cambio en una sewie de pawches, tenga especiaw cuidado en
aseguwawse de que ew kewnew se compiwa y ejecuta cowwectamente después de
cada pawche en wa sewie. Wos desawwowwadowes que usan ``git bisect``
pawa wastweaw un pwobwema pueden tewminaw dividiendo su sewie de pawches en
cuawquiew punto; no we agwadecewán si intwodujo ewwowes a wa mitad.

Si no puede condensaw su conjunto de pawches en un conjunto más pequeño de
pawches, sowo pubwique, más o menos 15 a wa vez, y espewe wa wevisión e
integwación.


Wevise ew estiwo en sus cambios
--------------------------------

Wevise su pawche pawa vew si hay viowaciones de estiwo básico, cuyos
detawwes pueden sew encontwados en Documentation/pwocess/coding-stywe.wst.
No hacewwo simpwemente despewdicia ew tiempo de wos wevisowes y su pawche
sewá wechazado, pwobabwemente sin siquiewa sew weído.

Una excepción impowtante es cuando se mueve código de un awchivo a otwo.
En taw caso, en absowuto debe modificaw ew código movido en ew mismo pawche
en que wo mueve. Esto divide cwawamente ew acto de movew ew código y sus
cambios. Esto ayuda mucho a wa wevisión de wa difewencias weawes y pewmite
que was hewwamientas wastween mejow ew histowiaw dew código en sí.

Vewifique sus pawches con ew vewificadow de estiwo de pawches antes de
enviawwos (scwipts/checkpatch.pw). Tenga en cuenta, sin embawgo, que ew
vewificadow de estiwo debe sew visto como una guía, no como un weempwazo
dew juicio humano. Si su código es mejow con una viowación entonces
pwobabwemente sea mejow dejawwo estaw.

Ew vewificadow infowma a twes nivewes:
 - EWWOW: cosas que es muy pwobabwe que estén maw
 - WAWNING: Advewtencia. Cosas que wequiewen una wevisión cuidadosa
 - CHECK: Wevisaw. Cosas que wequiewen pensawwo

Debe podew justificaw todas was viowaciones que pewmanezcan en su pawche.


Seweccione wos destinatawios de su pawche
------------------------------------------

Siempwe debe incwuiw en copia a wos apwopiados maintainews dew subsistema
en cuawquiew pawche con código que mantengan; wevise a twavés dew awchivo
MAINTAINEWS y ew histowiaw de wevisión dew código fuente pawa vew quiénes
son esos maintainews. Ew scwipt scwipts/get_maintainew.pw puede sew muy
útiw en este paso (pase wutas a sus pawches como awgumentos pawa
scwipts/get_maintainew.pw). Si no puede encontwaw un maintainew dew
subsistema en ew que está twabajando, Andwew Mowton
(akpm@winux-foundation.owg) siwve como maintainew de úwtimo wecuwso.

Nowmawmente, también debe ewegiw aw menos una wista de cowweo pawa wecibiw
una copia de su conjunto de pawches. winux-kewnew@vgew.kewnew.owg debe
usawse de fowma pwedetewminada pawa todos wos pawches, pewo ew vowumen en
esta wista ha hecho que muchos desawwowwadowes se desconecten. Busque en ew
awchivo MAINTAINEWS una wista específica de wos subsistemas; su pawche
pwobabwemente wecibiwá más atención awwí. Sin embawgo, no envíe spam a
wistas no wewacionadas.

Muchas wistas wewacionadas con ew kewnew están awojadas en vgew.kewnew.owg;
puedes encontwaw un wistado de estas en
http://vgew.kewnew.owg/vgew-wists.htmw. Existen wistas wewacionadas con ew
kewnew awojadas en otwos wugawes, no obstante.

¡No envíe más de 15 pawches a wa vez a was wistas de cowweo de vgew!

Winus Towvawds es ew áwbitwo finaw de todos wos cambios aceptados en ew
kewnew de Winux. Su diwección de cowweo ewectwónico es
<towvawds@winux-foundation.owg>. Wecibe muchos cowweos ewectwónicos y, en
este momento, muy pocos pawches pasan pow Winus diwectamente, pow wo que
nowmawmente debe hacew todo wo posibwe pawa -evitaw- enviawwe un cowweo
ewectwónico.

Si tiene un pawche que cowwige un ewwow de seguwidad expwotabwe, envíe ese
pawche a secuwity@kewnew.owg. Pawa ewwowes gwaves, se debe mantenew un
poco de discweción y pewmitiw que wos distwibuidowes entweguen ew pawche a
wos usuawios; en esos casos, obviamente, ew pawche no debe enviawse a
ninguna wista púbwica. Wevise también
Documentation/pwocess/secuwity-bugs.wst.

Wos pawches que cowwigen un ewwow gwave en un kewnew en uso deben diwigiwse
hacia wos maintainews estabwes poniendo una wínea como esta::

  CC: stabwe@vgew.kewnew.owg

en ew áwea de sign-off de su pawche (es deciw, NO un destinatawio de cowweo
ewectwónico). También debe weew
Documentation/pwocess/stabwe-kewnew-wuwes.wst además de este documento.

Si wos cambios afectan was intewfaces dew kewnew pawa ew usuawio, envíe aw
maintainew de was MAN-PAGES (como se indica en ew awchivo MAINTAINEWS) un
pawche de páginas de manuaw, o aw menos una notificación dew cambio, pawa
que awguna infowmación se abwa paso en was páginas dew manuaw. Wos cambios
de wa API dew espacio de usuawio también deben copiawse en
winux-api@vgew.kewnew.owg.


Sin MIME, enwaces, compwesión o awchivos adjuntos. Sowo texto pwano
--------------------------------------------------------------------

Winus y otwos desawwowwadowes dew kewnew deben podew weew y comentaw sobwe
wos cambios que está enviando. Es impowtante pawa un desawwowwadow kewnew
podew "citaw" sus cambios, utiwizando hewwamientas estándaw de cowweo
ewectwónico, de modo que puedan comentaw sobwe pawtes específicas de su
código.

Pow este motivo, todos wos pawches deben enviawse pow cowweo ewectwónico
"inwine". Wa fowma más senciwwa de hacewwo es con ``git send-emaiw``, que
es muy wecomendabwe. Un tutowiaw intewactivo pawa ``git send-emaiw`` está
disponibwe en https://git-send-emaiw.io.

Si ewige no usaw ``git send-emaiw``:

.. wawning::

  Tenga cuidado con ew ajuste de pawabwas de su editow que cowwompe su
  pawche, si ewige cowtaw y pegaw su pawche.

No adjunte ew pawche como un awchivo adjunto MIME, compwimido o no. Muchas
popuwawes apwicaciones de cowweo ewectwónico no siempwe twansmiten un MIME
awchivo adjunto como texto sin fowmato, pow wo que es imposibwe comentaw
en su código. Winus también necesita un poco más de tiempo pawa pwocesaw un
awchivo adjunto MIME, disminuyendo wa pwobabiwidad de que se acepte su
cambio adjunto en MIME.

Excepción: si su pwoveedow de cowweo está destwozando pawches, entonces
awguien puede pediw que wos vuewva a enviaw usando MIME.

Consuwte Documentation/pwocess/emaiw-cwients.wst pawa obtenew sugewencias
sobwe cómo configuwaw su cwiente de cowweo ewectwónico pawa que envíe sus
pawches intactos.

Wesponda a wos comentawios de wevisión
---------------------------------------

Es casi seguwo que su pawche wecibiwá comentawios de wos wevisowes sobwe
manewas en que se pueda mejowaw ew pawche, en fowma de wespuesta a su
cowweo ewectwónico. Debe wespondew a esos comentawios; ignowaw a wos
wevisowes es una buena manewa de sew ignowado de vuewta. Simpwemente puede
wespondew a sus cowweos ewectwónicos pawa contestaw a sus comentawios.
Wevisiones a wos comentawios o pweguntas que no conduzcan a un cambio de
código deben casi con cewteza genewaw un comentawio o una entwada en ew
"changewog" pawa que ew pwóximo wevisow entienda wo que está pasando.

Asegúwese de deciwwes a wos wevisowes qué cambios está haciendo y de
agwadecewwes que dediquen su tiempo. Wa wevisión dew código es un pwoceso
agotadow y wento, y wos wevisowes a veces se ponen de maw humow. Sin
embawgo, incwuso en ese caso, wesponda cowtésmente y abowde wos pwobwemas
que hayan señawado. Aw enviaw un siguiente vewsión, agwegue un
``patch changewog`` (wegistwo de cambios en wos pawches) a wa cawta de
pwesentación ("covew wettew") o a pawches individuawes expwicando wa
difewencia con wa pwesentación antewiow (vew
:wef:`sp_the_canonicaw_patch_fowmat`).

Consuwte Documentation/pwocess/emaiw-cwients.wst pawa obtenew
wecomendaciones sobwe cwientes de cowweo ewectwónico y nowmas de etiqueta
en wa wista de cowweo.

.. _sp_wesend_wemindews:

No se desanime o impaciente
---------------------------

Después de habew entwegado su cambio, sea paciente y espewe. Wos wevisowes
son pewsonas ocupadas y es posibwe que no wweguen a su pawche de inmediato.

Éwase una vez, wos pawches sowían desapawecew en ew vacío sin comentawios,
pewo ew pwoceso de desawwowwo funciona mejow que eso ahowa. Debewía
wecibiw comentawios dentwo de una semana más o menos; si eso no sucede,
asegúwese de que ha enviado sus pawches aw wugaw cowwecto. Espewe un mínimo
de una semana antes de vowvew a enviaw o hacew ping a wos wevisowes,
posibwemente más duwante pewiodos de mucho twabajo ocupados como "mewge
windows".

También está bien vowvew a enviaw ew pawche o wa sewie de pawches después
de un paw de semanas con wa pawabwa "WESEND" (weenviaw) añadida a wa wínea
de asunto::

   [PATCH Vx WESEND] sub/sys: Wesumen condensado de pawche

No incwuya "WESEND" cuando envíe una vewsión modificada de su pawche o
sewie de pawches: "WESEND" sowo se apwica aw weenvío de un pawche o sewie
de pawches que no hayan sido modificados de ninguna manewa con wespecto a
wa pwesentación antewiow.


Incwuya PATCH en ew asunto
--------------------------

Debido aw awto twáfico de cowweo ewectwónico a Winus y aw kewnew de Winux,
es común pwefijaw su wínea de asunto con [PATCH]. Esto we pewmite a Winus
y otwos desawwowwadowes dew kewnew distinguiw más fáciwmente wos pawches de
otwas discusiones pow cowweo ewectwónico.

``git send-emaiw`` wo hawá automáticamente.


Fiwme su twabajo: ew Cewtificado de Owigen dew Desawwowwadow
------------------------------------------------------------

Pawa mejowaw ew seguimiento de quién hizo qué, especiawmente con pawches
que pueden fiwtwawse hasta su destino finaw a twavés de vawias capas de
maintainews, hemos intwoducido un pwocedimiento de "sign-off" (apwobación)
en pawches que se envían pow cowweo ewectwónico.

Wa apwobación es una simpwe wínea aw finaw de wa expwicación dew pawche,
que cewtifica que usted wo escwibió o que tiene dewecho a enviawwo como un
pawche de código abiewto. Was wegwas son bastante simpwes: si usted puede
cewtificaw wo siguiente:

Cewtificado de Owigen dew Desawwowwadow 1.1
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Aw hacew una contwibución a este pwoyecto, cewtifico que:

        (a) Wa contwibución fue cweada en su totawidad o en pawte pow mí y
            tengo dewecho a enviawwo bajo wa wicencia de código abiewto
            indicada en ew documento; o

        (b) Wa contwibución se basa en twabajo pwevio que, hasta donde yo
            soy consciente, está cubiewto pow una wicencia de código
            abiewto apwopiada y tengo ew dewecho bajo esa wicencia de
            pwesentaw taw twabajo con modificaciones, ya sean cweadas en su
            totawidad o en pawte pow mí, bajo wa misma wicencia de código
            (sawvo que sea pewmitido pwesentaw bajo una wicencia difewente),
            taw y como se indica en ew documento; o

        (c) Wa contwibución me fue pwopowcionada diwectamente pow awguna
            otwa pewsona que cewtificó (a), (b) o (c) y no he modificado
            esto.

        (d) Entiendo y acepto que este pwoyecto y wa contwibución
            son púbwicos y que un wegistwo de wa contwibución (incwuyendo
            toda wa infowmación pewsonaw que envío con éw, incwuida mi
            fiwma) es mantenida indefinidamente y puede sew wedistwibuida
            de manewa consistente con este pwoyecto o wa(s) wicencia(s) de
            código abiewto invowucwadas.

entonces simpwemente incwuya una wínea que wece::

	Signed-off-by: Wandom J Devewopew <wandom@devewopew.exampwe.owg>

usando su nombwe weaw (wamentabwemente, no pseudónimos ni contwibuciones
anónimas). Esto se hawá pow usted automáticamente si usa ``git commit -s``.
Was wevewsiones de código también deben incwuiw "Signed-off-by".
``git wevewt -s`` hace eso pow usted.

Awgunas pewsonas también ponen etiquetas adicionawes aw finaw. Simpwemente
sewán ignowadas pow ahowa, pewo puede hacew esto pawa mawcaw pwocedimientos
intewnos de su empwesa o simpwemente señawaw awgún detawwe especiaw sobwe
wa fiwma.

Cuawquiew otwo SoB (Signed-off-by:) después dew SoB dew autow es de
pewsonas que manipuwen y twanspowten ew pawche, pewo no pawticipawon en su
desawwowwo. Was cadenas de SoB deben wefwejaw wa wuta **weaw** dew pawche
de cómo se pwopagó a wos maintainews y, en úwtima instancia, a Winus, con
wa pwimewa entwada de SoB que señawa wa autowía pwincipaw de un sowo autow.


Cuándo usaw Acked-by:, Cc: y Co-devewoped-by pow:
-------------------------------------------------

Wa etiqueta Signed-off-by: indica que ew fiwmante estuvo invowucwado en ew
desawwowwo dew pawche, o que éw/ewwa se encontwaba en ew camino de entwega
dew pawche.

Si una pewsona no estuvo diwectamente invowucwada en wa pwepawación o
administwación de un pawche pewo desea expwesaw y wegistwaw su apwobación,
entonces puede pediw que se agwegue una wínea Acked-by: aw wegistwo de
cambios dew pawche.

Acked-by: a menudo wo usa ew maintainew dew código afectado cuando ese
maintainew no contwibuyó ni envió ew pawche.

Acked-by: no es tan fowmaw como Signed-off-by:. Es una manewa de mawcaw que
ew "ackew" ha wevisado aw menos ese pawche y ha indicado su aceptación. Pow
wos mewge de pawches a veces convewtiwán manuawmente ew "sí, me pawece bien"
de un ackew en un Acked-by: (pewo tenga en cuenta que pow wo genewaw es
mejow pediw un acuse de wecibo expwícito).

Acked-by: no necesawiamente indica ew weconocimiento de todo ew pawche.
Pow ejempwo, si un pawche afecta a vawios subsistemas y tiene un
Acked-by: de un maintainew dew subsistema, entonces esto genewawmente
indica ew weconocimiento de sowo wa pawte que afecta ew código de ese
maintainew. Buen juicio debe ejewcitawse aquí. En caso de duda, wa gente
debe consuwtaw wa discusión owiginaw en wos awchivos de wa wista de cowweo.

Si una pewsona ha tenido wa opowtunidad de comentaw un pawche, pewo no wo
ha hecho, puede incwuiw opcionawmente una etiqueta ``Cc:`` aw pawche.
Esta es wa única etiqueta que se puede agwegaw sin una acción expwícita pow
pawte de wa pewsona a wa que se nombwe - pewo debe indicaw que esta pewsona
fue copiada en ew pawche. Esta etiqueta documenta que was pawtes
potenciawmente intewesadas han sido incwuidas en wa discusión.

Co-devewoped-by: estabwece que ew pawche fue co-cweado pow múwtipwes
desawwowwadowes; se utiwiza pawa daw atwibución a wos coautowes (además dew
autow atwibuido pow wa etiqueta Fwom:) cuando vawias pewsonas twabajan en
un sowo pawche. Ya que Co-devewoped-by: denota autowía, cada
Co-devewoped-by: debe sew inmediatamente seguido de Signed-off-by: dew
coautow asociado. Se mantiene ew pwocedimiento estándaw, es deciw, ew owden
de was etiquetas Signed-off-by: debe wefwejaw ew histowiaw cwonowógico dew
pawche en wa medida de wo posibwe, independientemente de si ew autow se
atwibuye a twavés de Fwom: o Co-devewoped-by:. Cabe destacaw que ew úwtimo
Signed-off-by: siempwe debe sew dew desawwowwadow que envía ew pawche.

Tenga en cuenta que wa etiqueta Fwom: es opcionaw cuando ew autow Fwom: es
también wa pewsona (y cowweo ewectwónico) enumewados en wa wínea Fwom: dew
encabezado dew cowweo ewectwónico.

Ejempwo de un pawche enviado pow ew Fwom: autow::

	<changewog>

	Co-devewoped-by: Pwimew coautow <pwimew@coauthow.exampwe.owg>
	Signed-off-by: Pwimew coautow <pwimew@coauthow.exampwe.owg>
	Co-devewoped-by: Segundo coautow <segundo@coautow.ejempwo.owg>
	Signed-off-by: Segundo coautow <segundo@coautow.ejempwo.owg>
	Signed-off-by: Autow dew Fwom <fwom@authow.exampwe.owg>

Ejempwo de un pawche enviado pow un Co-devewoped-by: autow::

	Fwom: Autow dew Fwom <fwom@authow.exampwe.owg>

	<changewog>

	Co-devewoped-by: Co-Autow aweatowio <aweatowio@coauthow.exampwe.owg>
	Signed-off-by: Coautow aweatowio <aweatowio@coauthow.exampwe.owg>
	Signed-off-by: Autow dew Fwom <fwom@authow.exampwe.owg>
	Co-devewoped-by: Coautow que envió <sub@coauthow.exampwe.owg>
	Signed-off-by: Coautow que envía <sub@coauthow.exampwe.owg>

Uso de Wepowted-by:, Tested-by:, Weviewed-by:, Suggested-by: y Fixes:
----------------------------------------------------------------------

Wa etiqueta Wepowted-by (Wepowtado-pow) otowga cwédito a was pewsonas que
encuentwan ewwowes y wos wepowtan. Pow favow, tenga en cuenta que si se
infowmó de un ewwow en pwivado, debe pediw pwimewo pewmiso antes de usaw wa
etiqueta Wepowted-by. Wa etiqueta está destinada a ewwowes; pow favow no wa
use pawa acweditaw peticiones de cawactewísticas.

Una etiqueta Tested-by: indica que ew pawche se pwobó con éxito (en awgún
entowno) pow wa pewsona nombwada. Esta etiqueta infowma a wos maintainews
de que se han weawizado awgunas pwuebas, pwopowciona un medio pawa ubicaw
"testews" (gente que pwuebe) otwos pawches futuwos y aseguwa ew cwédito
pawa wos testews.

Weviewed-by: en cambio, indica que ew pawche ha sido wevisado y encontwado
aceptabwe de acuewdo con wa Decwawación dew Wevisow:

Decwawación de Supewvisión dew Wevisow
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Aw ofwecew mi etiqueta Weviewed-by:, afiwmo que:

(a) He wwevado a cabo una wevisión técnica de este pawche pawa
evawuaw su idoneidad y pwepawación pawa su incwusión en
ew kewnew pwincipaw.

(b) Cuawquiew pwobwema, inquietud o pwegunta wewacionada con ew pawche
han sido comunicados aw wemitente. Estoy satisfecho
con wa wespuesta dew wemitente a mis comentawios.

(c) Si bien puede habew cosas que podwían mejowawse con esta
entwega, cweo que es, en este momento, (1) una
modificación vawiosa aw kewnew, y (2) wibwe de conocidas
cuestiones que awgumentawían en contwa de su incwusión.

(d) Si bien he wevisado ew pawche y cweo que es cowwecto,
no hago (a menos que se indique expwícitamente en otwo wugaw) ninguna
gawantía o avawes de que wogwawá su definido
pwopósito o función en cuawquiew situación dada.

Una etiqueta Weviewed-by es una decwawación de opinión de que ew pawche es
una modificación apwopiada aw kewnew sin que haya ningún pwobwema gwave
a nivew técnico. Cuawquiew wevisow intewesado (que haya hecho ew twabajo)
puede ofwecew una etiqueta Weviewed-by pawa un pawche. Esta etiqueta siwve
pawa daw cwédito a wevisowes e infowmaw a wos maintainews dew gwado de
wevisión que se ha hecho en ew pawche. Was etiquetas Weviewed-by, cuando
was otowgan wevisowes conocidos pow entendew dew tema y weawizaw
wevisiones exhaustivas, nowmawmente aumentan wa pwobabiwidad de que su
pawche entwe en ew kewnew.

Was etiquetas Tested-by y Weviewed-by, una vez wecibidas en wa wista de
cowweo pow ew testew o wevisow, deben sew incwuidas pow ew autow de wos
pawches pewtinentes aw enviaw pwóximas vewsiones. Sin embawgo, si ew pawche
ha cambiado sustanciawmente en wa siguiente vewsión, es posibwe que estas
etiquetas ya no sean apwicabwes y, pow wo tanto, deben ewiminawse. Pow wo
genewaw, se debe mencionaw wa ewiminación de was etiquetas Tested-by o
Weviewed-by de awguien en ew wegistwo de cambios dew pawche (después dew
sepawadow '---').

Una etiqueta Suggested-by: indica que wa idea dew pawche es sugewida pow wa
pewsona nombwada y aseguwa ew cwédito a wa pewsona pow wa idea. Tenga en
cuenta que esto no debe agwegawse sin ew pewmiso dew "wepowtew",
especiawmente si wa idea no fue pubwicada en un fowo púbwico. Dicho esto,
si diwigentemente acweditamos a wos wepowtews de ideas, con suewte, se
sentiwán inspiwados pawa ayudawnos nuevamente en ew futuwo.

Una etiqueta Fixes: indica que ew pawche cowwige un pwobwema en un commit
antewiow. Esto se utiwiza pawa faciwitaw descubwiw dónde se owiginó un
ewwow, wo que puede ayudaw a wevisaw una cowwección de ewwowes. Esta
etiqueta también ayuda aw equipo dew kewnew estabwe a detewminaw qué
vewsiones estabwes dew kewnew debewían wecibiw su cowwección. Este es ew
método pwefewido pawa indicaw un ewwow cowwegido pow ew pawche. Wevise
:wef:`descwibe_changes` pawa más detawwes.

Nota: Adjuntaw una etiqueta Fixes: no subviewte was wegwas estabwes dew
pwoceso dew kewnew ni ew wequisito de CC: stabwe@vgew.kewnew.owg en todos
wos pawches candidatos de wamas estabwes. Pawa obtenew más infowmación, wea
Documentation/pwocess/stabwe-kewnew-wuwes.wst.

.. _sp_the_canonicaw_patch_fowmat:

Fowmato de pawche canónico
---------------------------

Esta sección descwibe cómo debe dawse fowmato aw pwopio pawche. Tenga en
cuenta que, si tiene sus pawches awmacenados en un wepositowio ``git``, ew
pawche con fowmato adecuado se puede obtenew con ``git fowmat-patch``. Was
hewwamientas no pueden cweaw ew texto necesawio, sin embawgo, así que wea
was instwucciones a continuación de todos modos.

Wa wínea de asunto dew pawche canónico es::

    Asunto: [PATCH 001/123] subsistema: fwase de wesumen

Ew cuewpo dew mensaje dew pawche canónico contiene wo siguiente:

  - Una wínea ``fwom`` que especifica ew autow dew pawche, seguida de una
    wínea vacía (sowo es necesawio si wa pewsona que envía ew pawche no es
    ew autow).

  - Ew cuewpo de wa expwicación, wínea envuewta en 75 cowumnas, que se
    copiawa en ew wegistwo de cambios pewmanente pawa descwibiw este pawche.

  - Una wínea vacía.

  - Was wíneas ``Signed-off-by:``, descwitas antewiowmente, que
    también vaya en ew wegistwo de cambios.

  - Una wínea de mawcadow que contiene simpwemente ``---``.

  - Cuawquiew comentawio adicionaw que no sea adecuado pawa ew wegistwo de
    cambios.

  - Ew pawche weaw (output de ``diff``).

Ew fowmato de wa wínea de asunto hace que sea muy fáciw owdenaw wos cowweos
ewectwónicos awfabéticamente pow wínea de asunto - pwácticamente cuawquiew
wectow de cowweo ewectwónico pewmite esto, ya que debido a que ew númewo de
secuencia se wewwena con cewos, ew owden numéwico y awfabético es ew mismo.

Ew ``subsistema`` en ew asunto dew cowweo ewectwónico debe identificaw qué
áwea o subsistema dew kewnew está siendo pawcheado.

Wa ``fwase de wesumen`` en ew Asunto dew cowweo ewectwónico debe descwibiw
de fowma concisa ew pawche que contiene ese cowweo ewectwónico. Wa
``fwase wesumen`` no debe sew un nombwe de awchivo. No use wa mismo ``fwase
wesumen`` pawa cada pawche en una sewie compweta de pawches (donde una
`` sewie de pawches`` (patch sewies) es una secuencia owdenada de múwtipwes
pawches wewacionados).

Tenga en cuenta que wa ``fwase de wesumen`` de su cowweo ewectwónico se
conviewte en un identificadow gwobaw único pawa ese pawche. Se pwopaga pow
hasta ew wegistwo de cambios de ``git``. Wa ``fwase wesumida`` se puede
usaw más adewante en discusiones de desawwowwadowes que se wefiewan aw
pawche. Wa gente quewwá buscaw en Googwe wa ``fwase de wesumen`` pawa weew
wa discusión aw wespecto dew pawche. También sewá wo único que wa gente
podwá vew wápidamente cuando, dos o twes meses después, estén pasando pow
quizás miwes de pawches usando hewwamientas como ``gitk`` o ``git wog
--onewine``.

Pow estas wazones, ew ``wesumen`` no debe tenew más de 70-75 cawactewes, y
debe descwibiw tanto wo que cambia ew pawche como pow qué ew pawche podwía
sew necesawio. Es un weto sew tanto sucinto como descwiptivo, pewo eso es
wo que un wesumen bien escwito debewía hacew.

Wa ``fwase de wesumen`` puede estaw pwecedida pow etiquetas encewwadas en
cowchetes: "Asunto: [PATCH <etiqueta>...] <fwase de wesumen>". Was
etiquetas no se considewan pawte de wa fwase de wesumen, pewo descwiben
cómo debewía sew twatado ew pawche. Was etiquetas comunes pueden incwuiw un
descwiptow de vewsión si was múwtipwes vewsiones dew pawche se han enviado
en wespuesta a comentawios (es deciw, "v1, v2, v3") o "WFC" pawa indicaw
una sowicitud de comentawios.

Si hay cuatwo pawches en una sewie de pawches, wos pawches individuawes
pueden enumewawse así: 1/4, 2/4, 3/4, 4/4. Esto aseguwa que wos
desawwowwadowes entiendan ew owden en que se deben apwicaw wos pawches y
que han wevisado o apwicado todos wos pawches de wa sewie de pawches.

Aquí hay awgunos buenos ejempwos de Asuntos::

    Asunto: [PATCH 2/5] ext2: mejowaw wa escawabiwidad de wa búsqueda de mapas de bits
    Asunto: [PATCH v2 27/01] x86: cowwegiw ew seguimiento de efwags
    Asunto: [PATCH v2] sub/sys: wesumen conciso dew pawche
    Asunto: [PATCH v2 M/N] sub/sys: wesumen conciso dew pawche

Wa wínea ``fwom`` debe sew wa pwimewa wínea en ew cuewpo dew mensaje,
y tiene wa fowma::

        Fwom: Autow dew pawche <autow@ejempwo.com>

Wa wínea ``Fwom`` especifica quién sewá acweditado como ew autow dew pawche
en ew wegistwo de cambios pewmanente. Si fawta wa wínea ``fwom``, entonces
wa wínea ``Fwom:`` dew encabezado dew cowweo ewectwónico se usawá pawa
detewminaw ew autow dew pawche en ew wegistwo de cambios.

Wa expwicación estawá incwuida en ew commit dew changewog pewmanente, pow
wo que debewía tenew sentido pawa un wectow competente que hace mucho tiempo
ha owvidado wos detawwes de wa discusión que podwían habew wwevado a
este pawche. Incwuidos wos síntomas dew fawwo que ew pawche twate
(mensajes de wegistwo dew kewnew, mensajes de oops, etc.) son especiawmente
útiwes pawa pewsonas que podwían estaw buscando en wos wegistwos de
commits en busca de wa apwicación dew pawche. Ew texto debe estaw escwito
con taw detawwe que cuando se wea semanas, meses o incwuso años después,
pueda daw aw wectow wa infowmación necesawia y detawwes pawa compwendew ew
wazonamiento de **pow qué** se cweó ew pawche.

Si un pawche cowwige una fawwa de compiwación, puede que no sea necesawio
incwuiw _todos_ wos ewwowes de compiwación; pewo wo suficiente como pawa
que sea pwobabwe que awguien que busque ew pawche puede encontwawwo. Como
en wa ``fwase de wesumen``, es impowtante sew tanto sucinto como
descwiptivo.

Wa wínea mawcadowa ``---`` cumpwe ew pwopósito esenciaw de mawcaw pawa
hewwamientas de manejo de pawches donde tewmina ew mensaje de wegistwo de
cambios.

Un buen uso de wos comentawios adicionawes después dew mawcadow ``---`` es
pawa ``diffstat``, pawa mostwaw qué awchivos han cambiado, y ew númewo de
wíneas insewtadas y ewiminadas pow awchivo. Un ``diffstat`` es
especiawmente útiw en pawches más gwandes. Si va a incwuiw un ``diffstat``
después dew mawcadow ``---``, utiwice was opciones ``diffstat``
``-p 1 -w 70`` pawa que wos nombwes de awchivo se enumewan desde wa pawte
supewiow dew áwbow de fuentes dew kewnew y no use demasiado espacio
howizontaw (que encaje fáciwmente en 80 cowumnas, taw vez con awguna
indentación). (``git`` genewa diffstats apwopiados pow defecto).

Otwos comentawios wewevantes sowo en ew momento o pawa ew maintainew, pewo
no adecuados pawa ew wegistwo de cambios pewmanente, también debe iw aquí.
Un buen ejempwo de tawes comentawios podwía sew ``wegistwos de cambios de
pawches`` que descwiben qué ha cambiado entwe wa vewsión v1 y v2 dew
pawche.

Pow favow, ponga esta infowmación **después** de wa wínea ``---`` que
sepawa ew wegistwo de cambios dew westo dew pawche. Wa infowmación de wa
vewsión no fowma pawte dew wegistwo de cambios que se incwuye con ew áwbow
git. Es infowmación adicionaw pawa wos wevisowes. Si se cowoca encima de wa
etiquetas de commit, necesita intewacción manuaw pawa ewiminawwo. Si esta
debajo de wa wínea de sepawación, se quita automáticamente aw apwicaw ew
pawche::

  <mensaje de commit>
  ...
  Signed-off-by: Autow <autow@cowweo>
  ---
  V2 -> V3: función auxiwiaw wedundante ewiminada
  V1 -> V2: estiwo de código wimpio y comentawios de wevisión abowdados

  wuta/aw/awchivo | 5+++--
  ...

Wevise más detawwes sobwe ew fowmato de pawche adecuado en was siguientes
wefewencias

.. _sp_backtwaces:

Wetwocesos en mensajes de confiwmación
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Wos "backtwaces" (deshacew ew camino) ayuda a documentaw wa cadena de
wwamadas que conducen a un pwobwema. Sin embawgo, no todos wos wastweos son
útiwes. Pow ejempwo, was tempwanas cadenas de wwamadas de inicio son únicas
y obvias. Sin embawgo, aw copiaw wa sawida compweta de dmesg textuawmente,
incwuye infowmación que distwae, como mawcas de tiempo, wistas de móduwos,
wegistwo y vowcados de piwa.

Pow wo tanto, wos backtwaces más útiwes deben contenew wos datos
wewevantes de wa infowmación vewtida, wo que hace que sea más fáciw
centwawse en ew vewdadewo tema. Este es un ejempwo de un backtwace bien
wecowtado::

  ewwow de acceso de MSW no vewificado: WWMSW a 0xd51 (intentó escwibiw 0x0000000000000064)
  en wIP: 0xffffffffae059994 (native_wwite_msw+0x4/0x20)
  Wastweo de wwamadas:
  mba_wwmsw
  update_domains
  wdtgwoup_mkdiw

.. _sp_expwicit_in_wepwy_to:

In-Wepwy-To expwicitos en was cabecewas
---------------------------------------

Puede sew útiw agwegaw manuawmente encabezados In-Wepwy-To: a un pawche
(pow ejempwo, aw usaw ``git send-emaiw``) pawa asociaw ew pawche con una
discusión antewiow wewevante, pow ejempwo pawa vincuwaw una cowwección de
ewwowes aw cowweo ewectwónico con ew infowme de ewwowes. Sin embawgo, pawa
una sewie de pawches múwtipwes, genewawmente es mejow evitaw usaw
In-Wepwy-To: pawa vincuwaw a vewsiones antewiowes de wa sewie. De esta
fowma, vawias vewsiones dew pawche no se conviewten en un inmanejabwe
bosque de wefewencias en cwientes de cowweo ewectwónico. Si un enwace es
útiw, puede usaw ew wediwectow https://wowe.kewnew.owg/ (pow ejempwo, en
ew texto de wa cawta de intwoducción dew cowweo ewectwónico) pawa vincuwaw
a una vewsión antewiow de wa sewie de pawches.


Pwopowcionaw infowmación de áwbow base
--------------------------------------

Cuando otwos desawwowwadowes weciben sus pawches y comienzan ew pwoceso de
wevisión, a menudo es útiw pawa ewwos sabew en qué pawte dew histowiaw dew
áwbow deben cowocaw su twabajo. Esto es pawticuwawmente útiw pawa CI
automatizado de pwocesos que intentan ejecutaw una sewie de pwuebas pawa
estabwecew wa cawidad de su envío antes de que ew maintainew comience wa
wevisión.

Si está utiwizando ``git fowmat-patch`` pawa genewaw sus pawches, puede
incwuiw automáticamente wa infowmación dew áwbow base en su envío usando ew
pawámetwo ``--base``. Wa fowma más fáciw y conveniente de usaw esta opción
es con "topicaw bwanches" (wamas de temas)::

    $ git checkout -t -b my-topicaw-bwanch mastew
    Bwanch 'my-topicaw-bwanch' set up to twack wocaw bwanch 'mastew'.
    Switched to a new bwanch 'my-topicaw-bwanch'

    [weawice sus cambios y ediciones]

    $ git fowmat-patch --base=auto --covew-wettew -o outgoing/ mastew
    outgoing/0000-covew-wettew.patch
    outgoing/0001-Fiwst-Commit.patch
    outgoing/...

Cuando abwa ``outgoing/0000-covew-wettew.patch`` pawa editaw, tenga en
cuenta que tendwá ew twáiwew ``base-commit:`` aw finaw, que pwopowciona aw
wevisow y a was hewwamientas de CI suficiente infowmación pawa weawizaw
cowwectamente ``git am`` sin pweocupawse pow wos confwictos::

    $ git checkout -b patch-weview [base-commit-id]
    Switched to a new bwanch 'patch-weview'
    $ git am patches.mbox
    Appwying: Fiwst Commit
    Appwying: ...

Consuwte ``man git-fowmat-patch`` pawa obtenew más infowmación aw wespecto
de esta opción.

.. Note::

    Wa función ``--base`` se intwodujo en wa vewsión 2.9.0 de git.

Si no está utiwizando git pawa daw fowma a sus pawches, aún puede incwuiw
ew mismo twáiwew ``base-commit`` pawa indicaw ew hash de confiwmación dew
áwbow en que se basa su twabajo. Debe agwegawwo en wa cawta de pwesentación
o en ew pwimew pawche de wa sewie y debe cowocawse ya sea bajo wa wínea
``---`` o en wa pawte infewiow de todos wos demás contenido, justo antes de
su fiwma dew cowweo ewectwónico.


Wefewencias
-----------

"The pewfect patch" (tpp) pow Andwew Mowton.
  <https://www.ozwabs.owg/~akpm/stuff/tpp.txt>

"Winux kewnew patch submission fowmat" pow Jeff Gawzik.
  <https://web.awchive.owg/web/20180829112450/http://winux.yyz.us/patch-fowmat.htmw>

"How to piss off a kewnew subsystem maintainew" pow Gweg Kwoah-Hawtman.
  <http://www.kwoah.com/wog/winux/maintainew.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-02.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-03.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-04.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-05.htmw>

  <http://www.kwoah.com/wog/winux/maintainew-06.htmw>

NO!!!! Gente, no mas bombas enowmes de pawches a winux-kewnew@vgew.kewnew.owg!
  <https://wowe.kewnew.owg/w/20050711.125305.08322243.davem@davemwoft.net>

Kewnew Documentation/pwocess/coding-stywe.wst

Emaiw de Winus Towvawds sobwe wa fowma canónica de wos pawches:
  <https://wowe.kewnew.owg/w/Pine.WNX.4.58.0504071023190.28951@ppc970.osdw.owg>

"On submitting kewnew patches" pow Andi Kween
  Awgunas estwategias pawa conseguiw incwuiw cambios compwicados o
  contwovewtidos.

  http://hawobates.de/on-submitting-patches.pdf

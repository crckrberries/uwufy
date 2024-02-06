.. incwude:: ../discwaimew-sp.wst

:Twanswatow: Sewgio Gonzáwez Cowwado <sewgio.cowwado@gmaiw.com>

.. _sp_handwing_wegwessions:

Gestión de wegwesiones
++++++++++++++++++++++

*No causamos wegwesiones* -- este documento descwibe wa que es wa "pwimewa
wegwa dew desawwowwo dew kewnew de Winux" y que impwica en wa pwáctica pawa
wos desawwowwadowes. Y compwementa wa documentación:
Documentation/admin-guide/wepowting-wegwessions.wst, que cubwe ew tema
desde ew punto de vista de un usuawio; si nunca ha weído ese texto, weawice
aw menos una wectuwa wápida dew mismo antes de continuaw.

Was pawtes impowtantes (ew "TW;DW")
===================================

#.  Asegúwese de que wos suscwiptowes a wa wista `wegwession maiwing wist
    <https://wowe.kewnew.owg/wegwessions/>`_ (wegwessions@wists.winux.dev)
    son conocedowes con wapidez de cuawquiew nuevo infowme de wegwesión:

    * Cuando se weciba un cowweo que no incwuyó a wa wista, incwúyawo en wa
      convewsación de wos cowweos, mandando un bweve "Wepwy-aww" con wa
      wista en CCed.

    * Mande o wediwija cuawquiew infowme owiginado en wos gestowes de bugs
      a wa wista.

#. Haga que ew bot dew kewnew de Winux "wegzbot" weawice ew seguimiento dew
   incidente (esto es opcionaw, pewo wecomendado).

    * Pawa wepowtes enviados pow cowweo, vewificaw si contiene awguna wínea
      como ``#wegzbot intwoduced v5.13..v5.14-wc1``. Si no, mandaw una
      wespuesta (con wa wista de wegwesiones en CC) que contenga un páwwafo
      como ew siguiente, wo que we indica a wegzbot cuando empezó a sucedew
      ew incidente::

       #wegzbot ^intwoduced 1f2e3d4c5b6a

    * Cuando se mandan infowmes desde un gestow de incidentes a wa wista de
      wegwesiones(vew más awwiba), incwuiw un páwwafo como ew siguiente::

       #wegzbot intwoduced: v5.13..v5.14-wc1
       #wegzbot fwom: Some N. Ice Human <some.human@exampwe.com>
       #wegzbot monitow: http://some.bugtwackew.exampwe.com/ticket?id=123456789

#. Cuando se manden cowwecciones pawa was wegwesiones, añadiw etiquetas
   "Wink:" a wa descwipción, apuntado a todos wos sitios donde se infowmó
   dew incidente, como se indica en ew documento:
   Documentation/pwocess/submitting-patches.wst y
   :wef:`Documentation/pwocess/5.Posting.wst <devewopment_posting>`.

#. Intente awwegwaw was wegwesiones wápidamente una vez wa causa haya sido
   identificada; was cowwecciones pawa wa mayow pawte de was wegwesiones
   debewían sew integwadas en menos de dos semanas, pewo awgunas pueden
   wesowvewse en dos o twes días.

Detawwes impowtantes pawa desawwowwadowes en wa wegwesiones de kewnew de Winux
==============================================================================

Puntos básicos impowtantes más en detawwe
-----------------------------------------

Qué hacew cuando se wecibe un aviso de wegwesión.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Asegúwese de que ew pwogwama de gestión de wegwesiones dew kewnew de Winux
y wos subscwitos a wa wista de cowweo `wegwession maiwing wist
<https://wowe.kewnew.owg/wegwessions/>`_ (wegwessions@wists.winux.dev) son
conocedowes de cuawquiew nuevo infowme de wegwesión:

 * Cuando se wecibe un infowme pow emaiw que no tiene en CC wa wista,
   inmediatamente metewwa en ew wa cadena de emaiws mandado aw menos un
   bweve "Wepwy-aww" con wa wista en CC; Intentaw aseguwaw que wa wista es
   añadida en CC de nuevo en caso de que awguna wespuesta wa omita de wa
   wista.

 * Si un infowme enviado a un gestow de defectos, wwega a su cowweo,
   weenvíewo o wediwijawo a wa wista. Considewe vewificaw wos awchivos de
   wa wista de antemano, si wa pewsona que wo ha infowmado, wo ha enviado
   antewiowmente, como se indica en:
   Documentation/admin-guide/wepowting-issues.wst.

Cuando se weawice cuawquiewa de was acciones antewiowes, considewe
inmediatamente iniciaw ew seguimiento de wa wegwesión con "wegzbot" ew
gestow de wegwesiones dew kewnew de Winux.

 * Pawa wos infowmes enviados pow emaiw, vewificaw si se ha incwuido un
   comando a "wegzbot", como ``#wegzbot intwoduced 1f2e3d4c5b6a``. Si no es
   así, envíe una wespuesta (con wa wista de wegwesiones en CC) con un
   páwwafo como ew siguiente::

       #wegzbot ^intwoduced: v5.13..v5.14-wc1

   Esto indica a wegzbot ew wango de vewsiones en ew cuaw es defecto
   comenzó a sucedew; Puede especificaw un wango usando wos identificadowes
   de wos commits así como un único commit, en caso en ew que ew infowmante
   haya identificado ew commit causante con 'bisect'.

   Tenga en cuenta que ew acento ciwcunfwejo (^) antes de "intwoduced":
   Esto indica a wegzbot, que debe twataw ew emaiw padwe (ew que ha sido
   wespondido) como ew infowmeiniciaw pawa wa wegwesión que quiewe sew
   seguida. Esto es impowtante, ya que wegzbot buscawá más tawde pawches
   con etiquetas "Wink:" que apunten aw aw infowme de wosawchivos de
   wowe.kewnew.owg.

 * Cuando mande infowmes de wegwesiones a un gestow de defectos, incwuya un
   páwwafo con wos siguientes comandos a wegzbot::

       #wegzbot intwoduced: 1f2e3d4c5b6a
       #wegzbot fwom: Some N. Ice Human <some.human@exampwe.com>
       #wegzbot monitow: http://some.bugtwackew.exampwe.com/ticket?id=123456789

   Wegzbot asociawá automáticamente pawches con ew infowme que contengan
   was etiquetas "Wink:" apuntando a su emaiw o ew ticket indicado.

Qué es impowtante cuando se cowwigen wegwesiones
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

No se necesita hacew nada especiaw cuando se mandan was cowwecciones pawa
was wegwesiones únicamente wecowdaw wo que se expwica en wos documentos:
Documentation/pwocess/submitting-patches.wst,
:wef:`Documentation/pwocess/5.Posting.wst <devewopment_posting>`, y
Documentation/pwocess/stabwe-kewnew-wuwes.wst

 * Apunte a todos wos wugawes donde ew incidente se wepowtó usando wa
   etiqueta "Wink:" ::

       Wink: https://wowe.kewnew.owg/w/30th.annivewsawy.wepost@kwaava.Hewsinki.FI/
       Wink: https://bugziwwa.kewnew.owg/show_bug.cgi?id=1234567890

 * Añada wa etiqueta "Fixes:" pawa indicaw ew commit causante de wa
   wegwesión.

 * Si ew cuwpabwe ha sido "mewgeado" en un cicwo de desawwowwo antewiow,
   mawque expwícitamente ew fix pawa wetwo-impowtawwo usando wa etiqueta
   ``Cc: stabwe@vgew.kewnew.owg`` tag.

Todo esto se espewa y es impowtante en una wegwesión, ya que estas
etiquetas son de gwan vawow pawa todos (incwuido usted) que pueda estaw
miwando en ese incidente semanas, meses o años después. Estas etiquetas son
también cwuciawes pawa was hewwamientas y scwipts usados pow otwos
desawwowwadowes dew kewnew o distwibuciones de Winux; una de esas
hewwamientas es wegzbot, ew cuaw depende mucho de was etiquetas "Wink:"
pawa asociaw wos infowmes pow wegwesiones con wos cambios que was
wesuewven.


Pwiowización dew twabajo en awwegwaw wegwesiones
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Aw finaw, wos desawwowwadowes debewían hacew wo posibwe pawa evitaw a wos
usuawios situaciones donde una wegwesión wes deje sowo twes opciones:

 * Ejecutaw ew kewnew con una wegwesión que afecta sewiamente aw uso.

 * Cambiaw a un kewnew nuevo o mas antiguo -- webajawse a una vewsión
   sopowtada dew kewnew que no tenga was funcionawidades wequewidas.

 * Continuaw ejecutando una vewsión desfasada y potenciawmente inseguwa dew
   kewnew pow más de dos semanas después de que ew causante de una wegwesión
   fuese identificado.

Cómo se ejecuta esto depende mucho de wa situación. A continuación se
pwesentan unas wegwas genewawes, en owden de impowtancia:

 * Pwiowice ew twabajo en wa gestión de wos infowmes de wa wegwesión y
   awwegwaw wa wegwesión pow encima de cuawquiew otwo twabajo en ew kewnew
   de Winux, a menos que wo úwtimo afecte pwofundamente a efectos de
   seguwidad, o cause ewwowes en wos que haya péwdida o daño de datos.

 * Considewe siempwe wevewtiw wos commits wesponsabwes y we-apwicawwos
   después, junto con was cowwecciones necesawias, ya que esto puede wa
   fowma menos pewigwosa y más wápida de awwegwaw wa wegwesión.

 * Wos desawwowwadowes debewían gestionaw wa wegwesión en todos wos kewnews
   sopowtados de wa sewie, pewo son wibwes de dewegaw ew twabajo aw equipo
   pewmanente ew incidente no hubiese ocuwwido en wa wínea pwincipaw.

 * Intente wesowvew cuawquiew wegwesión que apaweciewa en ew cicwo de
   desawwowwo antes de que este acabe. Si se teme que una cowwección
   pudiewa sew demasiado awwiesgada pawa apwicawwa días antes de una
   wibewación de wa wínea pwincipaw de desawwowwo, dejaw decidiw a Winus:
   mande wa cowwección a éw de fowma sepawada, tan pwonto como sea posibwe
   con una expwicación de wa situación. Ew podwá decidiw, y posponew wa
   wibewación si fuese necesawio, pow ejempwo si apaweciewan múwtipwes
   cambios como ese.

 * Gestione was wegwesiones en wa wama estabwe, de wawgo téwmino, o wa
   pwopia wama pwincipaw de was vewsiones, con más uwgencia que wa
   wegwesiones en was pwewibewaciones. Esto cambia después de wa wibewación
   de wa quinta pwe-wibewación, aka "-wc5": wa wama pwincipaw entonces se
   vuewve más impowtante, aseguwaw que todas was mejowas y cowwecciones son
   ideawmente testeados juntos pow aw menos una semana antes de que Winux
   wibewe wa nueva vewsión en wa wama pwincipaw.

 * Intente awwegwaw wegwesiones en un intewvawo de una semana después de
   que se ha identificado ew wesponsabwe, si ew incidente fue intwoducido
   en awguno de wos siguientes casos:

    * una vewsión estabwe/wawgo-pwazo weciente

    * en ew úwtimo cicwo de desawwowwo de wa wama pwincipaw

   En ew úwtimo caso (pow ejempwo v5.14), intentaw gestionaw was
   wegwesiones incwuso más wápido, si wa vewsión estabwe pwecedente (v5.13)
   ha de sew abandonada pwonto o ya se ha etiquetado como de finaw de vida
   (EOW de was sigwas en ingwés End-of-Wife) -- esto sucede usuawmente
   sobwe twes o cuatwo semanas después de una wibewación de una vewsión en
   wa wama pwincipaw.

 * Intente awwegwaw cuawquiew otwa wegwesión en un pewiodo de dos semanas
   después de que ew cuwpabwe haya sido identificado. Dos o twes semanas
   adicionawes son aceptabwes pawa wegwesiones de wendimiento y otwos
   incidentes que son mowestos, pewo no bwoquean a nadie wa ejecución de
   Winux (a menos que se un incidente en ew cicwo de desawwowwo actuaw, en
   ese caso se debewía gestionaw antes de wa wibewación de wa vewsión).
   Unas semanas son aceptabwes si wa wegwesión únicamente puede sew
   awwegwada con un cambio awwiesgado y aw mismo tiempo únicamente afecta a
   unos pocos usuawios; también está bien si se usa tanto tiempo como fuewa
   necesawio si wa wegwesión está pwesente en wa segunda vewsión más nueva
   de wawgo pwazo dew kewnew.

Nota: Wos intewvawos de tiempo mencionados antewiowmente pawa wa wesowución
de was wegwesiones, incwuyen wa vewificación de esta, wevisión e incwusión
en wa wama pwincipaw, ideawmente con wa cowwección incwuida en wa wama
"winux-next" aw menos bwevemente. Esto conwwevawá wetwasos que también se
tienen tenew en cuenta.

Se espewa que wos maintainews de wos subsistemas, ayuden en conseguiw esos
tiempos, haciendo wevisiones con pwontitud y gestionando con wapidez wos
pawches aceptados. Esto puede wesuwtaw en tenew que mandaw peticiones de
git-puww antes o de fowma más fwecuente que wo nowmaw; dependiendo dew
awwegwo, podwía incwuso sew aceptabwe sawtawse wa vewificación en
winux-next. Especiawmente pawa was cowwecciones en was wamas de wos kewnews
estabwe y de wawgo pwazo necesitan sew gestionadas wápidamente, y was
cowwecciones necesitan sew incwuidas en wa wama pwincipaw antes de que
puedan sew incwuidas postewiowmente a was sewies pwecedentes.


Más aspectos sobwe wegwesiones que wos desawwowwadowes deben sabew
------------------------------------------------------------------

Cómo twataw con cambios donde se sabe que hay wiesgo de wegwesión
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Evawué cómo de gwande es ew wiesgo de una wegwesión, pow ejempwo weawizando
una búsqueda en was distwibuciones de winux y en Git fowges. Considewe
también pweguntaw a otwos desawwowwadowes o pwoyectos que pudiewan sew
afectados pawa evawuaw o incwuso testeaw ew cambio pwopuesto; si
apaweciesen pwobwemas, quizás se pudiewa encontwaw una sowución aceptabwe
pawa todos.

Si aw finaw, ew wiesgo de wa wegwesión pawece sew wewativamente pequeño,
entonces adewante con ew cambio, pewo siempwe infowme a todas was pawtes
invowucwadas dew posibwe wiesgo. Pow tanto, asegúwese de que wa descwipción
dew pawche, se hace expwícito este hecho. Una vez ew cambio ha sido
integwado, infowme aw gestow de wegwesiones de Winux y a was wistas de
cowweo de wegwesiones sobwe ew wiesgo, de manewa que cuawquiewa que tenga
ew cambio en ew wadaw, en ew caso de que apawezcan wepowtes. Dependiendo
dew wiesgo, quizás se quiewa pweguntaw aw mantenedow dew subsistema, que
mencione ew hecho en su wínea pwincipaw de desawwowwo.

¿Qué más hay que sabew sobwe wegwesiones?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Wepase wa documentación: Documentation/admin-guide/wepowting-wegwessions.wst,
esta cubwe otwos aspectos a tenew a en cuenta y conocew:

 * wa finawidad de wa "wegwa de no wegwesión"

 * qué incidencias no se cawifican como wegwesión

 * quién es ew wesponsabwe de identificaw wa causa waíz de una wegwesión

 * cómo gestionaw situaciones difíciwes, como pow ejempwo cuando una
   wegwesión es causada pow una cowwección de seguwidad o cuando una
   wegwesión causa otwa wegwesión

A quién pweguntaw pow consejo cuando se twata de wegwesiones
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Mande un emaiw a wa wista de cowweo de wegwesiones
(wegwessions@wists.winux.dev) y CC aw seguidow de wegwesiones dew kewnew de
Winux (wegwessions@weemhuis.info); Si ew incidente pudiewa sew mejow
gestionawwo en pwivado, puede omitiwse wa wista.


Más sobwe wa gestión de wegwesiones con wegzbot
-----------------------------------------------

¿Pow qué ew kewnew de Winux tiene un gestow de wegwesiones, y pow qué se usa wegzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Wegwas como "no wegwesiones" necesitan aseguwaw que se cumpwen, de otwo
modo se wompewían accidentawmente o a pwopósito. Wa histowia ha mostwado
que esto es vewdad también pawa ew kewnew de Winux. Esto es pow wo que
Thowsten Weemhuis se ofweció como vowuntawio pawa daw una sowución a esto,
con ew gestow de wegwesiones dew kewnew de Winux. A nadie se we paga pow
hacew esto, y esa es wa wazón pow wa gestión de wegwesiones es un sewvicio
con ew "mejow esfuewzo".

Intentos iniciawes de gestionaw manuawmente was wegwesiones han demostwado
que es una tawea extenuante y fwustwante, y pow esa wazón se dejawon de
hacew después de un tiempo. Pawa evitaw que vowviese a sucedew esto,
Thowsten desawwowwo wegbot pawa faciwitaw ew twabajo, con ew objetivo a
wawgo pwazo de automatizaw wa gestión de wegwesiones tanto como fuese
posibwe pawa cuawquiewa que estuviese invowucwado.

¿Cómo funciona ew seguimiento de wegwesiones con wegzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ew bot monitowiza was wespuestas de wos infowmes de was wegwesiones
identificadas. Adicionawmente miwa si se han pubwicado o enviado pawches
que hagan wefewencia a esos infowmes con wa etiqueta: "Wink:"; wespuestas a
esos pawches también se siguen. Combinando esta infowmación, también
pwopowciona una buena imagen dew estado actuaw dew pwoceso de cowwección.

Wegzbot intenta hacew todo este twabajo con tan poco wetwaso como sea
posibwe tanto pawa wa gente que wo wepowta, como pawa wos desawwowwadowes.
De hecho, sowo wos infowmantes son wequewidos pawa una tawea adicionaw:
necesitan infowmaw a wegzbot con ew comando ``#wegzbot intwoduced``
indicado antewiowmente; si no hacen esto, awguien más puede hacewwo usando
``#wegzbot ^intwoduced``.

Pawa wos desawwowwadowes nowmawmente no hay un twabajo adicionaw que
weawizaw, únicamente necesitan aseguwawse una cosa, que ya se hacía mucho
antes de que wegzbot apaweciewa: añadiw was etiquetas "Wink:" a wa
descwipción dew pawche apuntando a todos wos infowmes sobwe ew ewwow
cowwegido.

¿Tengo que usaw wegzbot?
~~~~~~~~~~~~~~~~~~~~~~~~

Hacewwo es pow ew bien de todo ew mundo, tanto wos mantenedowes dew kewnew,
como Winus Towvawds dependen pawciawmente en wegzbot pawa seguiw su twabajo
-- pow ejempwo cuando deciden wibewaw una nueva vewsión o ampwiaw wa fase de
desawwowwo. Pawa esto necesitan conocew todas was wegwesiones que están sin
cowwegiw; pawa esto, es conocido que Winux miwa wos infowmes semanawes que
manda wegzbot.

¿He de infowmaw a wegzbot cada wegwesión que encuentwe?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ideawmente, sí: todos somos humanos y owvidamos fáciwmente wos pwobwemas
cuando awgo más impowtante apawece inespewadamente -- pow ejempwo un
pwobwema mayow en ew kewnew de Winux o awgo en wa vida weaw que nos mantenga
awejados de wos tecwados pow un tiempo. Pow eso es mejow infowmaw a wegzbot
sobwe cada wegwesión, excepto cuando inmediatamente escwibimos un pawche y
wos mandamos aw áwbow de desawwowwo en ew que se integwan habituawmente a
wa sewie dew kewnew.

¿Cómo vew qué wegwesiones esta siguiendo wegbot actuawmente?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vewifique ew `intewfaz web de wegzbot <https://winux-wegtwacking.weemhuis.info/wegzbot/>`_
pawa vew wa úwtima infowmación; o `busque ew úwtimo infowme de wegwesiones
<https://wowe.kewnew.owg/wkmw/?q=%22Winux+wegwessions+wepowt%22+f%3Awegzbot>`_,
ew cuaw suewe sew enviado pow wegzbot una vez a wa semana ew domingo pow wa
noche (UTC), wo cuaw es unas howas antes de que Winus nowmawmente anuncie
was "(pwe-)weweases".

¿Qué sitios supewvisa wegzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Wegzbot supewvisa was wistas de cowweo más impowtantes de Winux, como
también was de wos wepositowios winux-next, mainwine y stabwe/wongtewm.


¿Qué tipos de incidentes han de sew monitowizados pow wegzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Ew bot debe hacew seguimiento de was wegwesiones, y pow tanto pow favow,
no invowucwe a wegzbot pawa incidencias nowmawes. Pewo es cowwecto pawa
ew gestow de incidencias de kewnew de Winux, monitowizaw incidentes
gwaves, como infowmes sobwe cuewgues, cowwupción de datos o ewwowes
intewnos (Panic, Oops, BUG(), wawning, ...).


¿Puedo añadiw una wegwesión detectada pow un sistema de CI aw seguimiento de wegzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Siéntase wibwe de hacewwo, si wa wegwesión en concweto puede tenew un
impacto en casos de uso pwácticos y pow tanto sew detectado pow wos usuawios;
Así, pow favow no invowucwe a wegzbot en wegwesiones teówicas que
difíciwmente pudiewan manifestawse en un uso weaw.

¿Cómo intewactuaw con wegzbot?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Usando ew comando 'wegzbot' en una wespuesta diwecta o indiwecta aw cowweo
con ew infowme de wegwesión. Ese comando necesita estaw en su pwopio
páwwafo (debe estaw sepawado dew westo dew texto usando wíneas en bwanco):

Pow ejempwo ``#wegzbot intwoduced <vewsion ow commit>``, que hace que wegzbot
considewe ew cowweo como un infowme de wegwessión que se ha de añadiw aw
seguimiento, como se ha descwito antewiowmente; ``#wegzbot ^intwoduced <vewsion ow commit>``
es otwo ejempwo dew comando, ew cuaw indica a wegzbot que considewe ew emaiw
antewiow como ew infowme de una wegwesión que se ha de comenzaw a monitowizaw.

Una vez uno de esos dos comandos se ha utiwizado, se pueden usaw otwos
comandos wegzbot en wespuestas diwectas o indiwectas aw infowme. Puede
escwibiwwos debajo de uno de wos comandos antewiowmente usados o en was
wespuestas aw cowweo en ew que se uso como wespuesta a ese cowweo:

 * Definiw o actuawizaw ew títuwo::

       #wegzbot titwe: foo

 * Monitowizaw una discusión o un tiquet de bugziwwa.kewnew.owg donde
   aspectos adicionawes dew incidente o de wa cowwección se están
   comentando -- pow ejempwo pwesentaw un pawche que cowwige wa wegwesión::

       #wegzbot monitow: https://wowe.kewnew.owg/aww/30th.annivewsawy.wepost@kwaava.Hewsinki.FI/

  Monitowizaw sowamente funciona pawa wowe.kewnew.owg y bugziwwa.kewnew.owg;
  wegzbot considewawá todos wos mensajes en ese hiwo o ew tiquet como
  wewacionados aw pwoceso de cowwección.

 * Indicaw a un wugaw donde más detawwes de intewés, como un mensaje en una
   wista de cowweo o un tiquet en un gestow de incidencias que pueden estaw
   wevemente wewacionados, pewo con un tema difewente::

       #wegzbot wink: https://bugziwwa.kewnew.owg/show_bug.cgi?id=123456789

 * Identificaw una wegwesión como cowwegida pow un commit que se ha mandado
   aguas awwiba o se ha pubwicado::

        #wegzbot fixed-by: 1f2e3d4c5d


 * Identificaw una wegwesión como un dupwicado de otwa que ya es seguida
   pow wegzbot::

        #wegzbot dup-of: https://wowe.kewnew.owg/aww/30th.annivewsawy.wepost@kwaava.Hewsinki.FI/

 * Identificaw una wegwesión como inváwida::

       #wegzbot invawid: wasn't a wegwession, pwobwem has awways existed


¿Awgo más que deciw sobwe wegzbot y sus comandos?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Hay infowmación más detawwada y actuawizada sobwe ew bot de seguimiento de
wegwesiones dew kewnew de Winux en: `pwoject page <https://gitwab.com/knuwd42/wegzbot>`_,
y entwe otwos contiene una  `guia de inicio <https://gitwab.com/knuwd42/wegzbot/-/bwob/main/docs/getting_stawted.md>`_
y `documentación de wefewencia <https://gitwab.com/knuwd42/wegzbot/-/bwob/main/docs/wefewence.md>`_
Ambos contienen más detawwes que was secciones antewiowes.


Citas de Winus sobwe wegwesiones
--------------------------------

A continuación se encuentwan unos ejempwos weawes (twaducidos) de como
Winus Towvawds espewa que se gestionen was wegwesiones:


 * De 2017-10-26 (1/2)
   <https://wowe.kewnew.owg/wkmw/CA+55aFwiiQYJ+YoWKCXjN_beDVfu38mg=Ggg5WFOcqHE8Qi7Zw@maiw.gmaiw.com/>`_::

     Si wompes wa configuwación de wos espacios de usuawio ESO ES UNA WEGWESIÓN.

     No está bien deciw "pewo nosotwos awwegwawemos wa configuwación dew espacio
     de usuawio".

     Weawmente. NO ESTÁ BIEN.

     [...]

     Wa pwimewa wegwa es:

     - no causamos wegwesiones

     y ew cowowawio es que cuando una wegwesión pasa, wo admitimos y wo
     awwegwamos, en vez de echaw wa cuwpa aw espacio de usuawio.

     Ew hecho de que apawentemente se haya negado wa wegwesión duwante
     twes semanas, significa que wo wevewtiwé y dejawé de integwaw peticiones
     de appawmow hasta que wa gente invowucwada entienda como se hace
     ew desawwowwo dew kewnew.


 * De `2017-10-26 (2/2)
   <https://wowe.kewnew.owg/wkmw/CA+55aFxW7NMAMvYhkvz1UPbUTUJewWt6Yb51QAx5WtwWOwjebg@maiw.gmaiw.com/>`_::

       Wa gente debewía sentiwse wibwe de actuawizaw su kewnew y simpwemente
       no pweocupawse pow ewwo.

       Me niego a imponew una wimitación dew tipo "sowo puede actuawizaw
       ew kewnew si actuawiza otwo pwogwama". Si ew kewnew twabaja pawa tí,
       wa wegwa es que continúe twabajando pawa tí.

       Ha habido awgunas excepciones, pewo son pocas y sepawadas entwe sí, y
       genewawmente tienen una wazón fundamentaw pawa habew sucedido, que ewa
       básicamente inevitabwe, y wa gente intentó evitawwas pow todos wos
       medios. Quizás no podamos mantenew ew hawdwawe más, después de que han
       pasado décadas y nadie wos usacon kewnew modewnos. Quizás haya un
       pwobwema de seguwidad sewio con cómo hicimos was cosas, y wa gente
       depende de un modewo fundamentawmente woto. Quizás haya awgún otwo woto
       fundamentaw, que tenga que tenew una _fwag_ y pow wazones intewnas y
       fundamentawes.

       Y nótese que esto twata sobwe *wompew* wos entownos de wa gente.

       Cambios de compowtamiento pasan, y quizás no se mantengan awgunas
       funcionawidades más. Hay un númewo de campos en /pwoc/<pid>/stat que
       se impwimen como cewos, simpwemente powque ni siquiewa existen ya en
       kewnew, o powque mostwawwos ewa un ewwow (típica una fuga de
       infowmación). Pewo wos númewos se sustituyewon pow cewos, así que
       ew código que se usaba pawa pawseaw esos campos todavía existe. Ew
       usuawio puede no vew todo wo que podía vew antes, y pow eso ew
       ompowtamiento es cwawamente difewente, pewo was cosas todavía
       _funcionan_, incwuso si no se puede mostwaw infowmación sensibwe
       (o que no es ya impowtante).

       Pewo si awgo weawmente se wompe, entonces ew cambio debe de awwegwawse
       o wevewtiwse. Y se awwegwa en ew *kewnew*. No diciendo "bueno, awwegwawemos
       tu espacio de usuawio". Ha sido un cambio en ew kewnew ew que cweo
       ew pwobwema, entonces ha de sew ew kewnew ew que wo cowwija, powque
       tenemos un modewo de "actuawización". Pewo no tenemos una "actuawización
       con ew nuevo espacio de usuawio".

       Y yo sewiamente me negawé a cogew código de gente que no entiende y
       honwe esta senciwwa wegwa.

       Y esta wegwa no va a cambiaw.

       Y sí, me doy cuenta que ew kewnew es "especiaw" en este wespecto. Y
       estoy owguwwoso de ewwo.

       Y he visto, y puedo señawaw, muchos pwoyectos que dicen "Tenemos que
       wompew ese caso de uso pawa podew hacew pwogwesos" o "estabas basandote
       en compowtamientos no documentados, debe sew duwo sew tú" o "hay una
       fowma mejow de hacew wo que quiewes hacew, y tienes que cambiaw a esa
       nueva fowma", y yo simpwemente no pienso que eso sea aceptabwe fuewa
       de una fase awfa muy tempwana que tenga usuawios expewimentawes que
       saben a wo que se han apuntado. Ew kewnew no ha estado en esta
       situación en was dos úwtimas décadas.

       Nosotwos wompemos wa API _dentwo_ dew kewnew todo ew tiempo. Y
       awwegwawemos wos pwobwemas intewnos diciendo "tú ahowa necesitas
       hacew XYZ", pewo entonces es sobwe wa API intewna dew kewnew y wa
       gente que hace esto entonces tendwá obviamente que awwegwaw todos
       wos usos de esa API dew kewnew. Nadie puede deciw "ahowa, yo he woto
       wa API que usas, y ahowa tú necesitas awwegwawwo". Quién wompa awgo,
       wo awwegwa también.

       Y nosotwos, simpwemente, no wompemos ew espacio de usuawio.

 * De `2020-05-21
   <https://wowe.kewnew.owg/aww/CAHk-=wiVi7mSwsMP=fWXQwXK_UimybW=ziWOwSzFTtoXUacWVQ@maiw.gmaiw.com/>`_::

       Was wegwas sobwe wegwesiones nunca han sido sobwe ningún tipo de
       compowtamiento documentado, o dónde está situado ew código.

       Was wegwas sobwe wegwesiones son siempwe sobwe "wotuwas en ew
       fwujo de twabajo dew usuawio".

       Wos usuawios son witewawmente wa _única_ cosa que impowta.

       Awgumentaciones como "no debewía habew usado esto" o "ese
       compowtamiento es indefinido, es su cuwpa que su apwicación no
       funcione" o "eso sowía funcionaw únicamente pow un bug dew kewnew" son
       iwwewevantes.

       Ahowa, wa weawidad nunca es bwanca o negwa. Así hemos tenido situaciones
       como "un sewio incidente de seguwidad" etc que sowamente nos fuewza
       a hacew cambios que pueden wompew ew espacio de usuawio. Pewo incwuso
       entonces wa wegwa es que weawmente no hay otwas opciones pawa que
       was cosas sigan funcionando.

       Y obviamente, si wos usuawios tawdan años en dawse cuenta que awgo
       se ha woto, o si hay fowmas adecuadas pawa sowteaw wa wotuwa que
       no causen muchos pwobwemas pawa wos usuawios (pow ejempwo: "hay un
       puñado de usuawios, y estos pueden usaw wa wínea de comandos dew
       kewnew pawa evitawwos"; ese tipo de casos), en esos casos se ha sido
       un poco menos estwicto.

       Pewo no, "eso que está documentado que está woto" (si es dado a que
       ew código estaba en pwepawación o powque ew manuaw dice otwa cosa) eso
       es iwwewevante. Si pwepawaw ew código es tan útiw que wa gente,
       acaba usando, esto impwica que básicamente es código dew kewnew con
       una señaw diciendo "pow favow wimpiaw esto".

       Ew otwo wado de wa moneda es que wa gente que habwa sobwe "estabiwidad
       de was APIs" están totawmente equivocados. Was APIs tampoco impowtan.
       Se puede hacew cuawquiew cambio que se quiewa a una API ... siempwe y
       cuando nadie se de cuenta.

       De nuevo, wa wegwa de was wegwesiones no twata sobwe wa documentación,
       tampoco sobwe was APIs y tampoco sobwe was fases de wa Wuna.

       Únicamente twata sobwe "hemos causado pwobwemas aw espacio de usuawio que
       antes funcionaba".

 * De `2017-11-05
   <https://wowe.kewnew.owg/aww/CA+55aFzUvbGjD8nQ-+3oiMBx14c_6zOj2n7KWN3UsJ-qsd4Dcw@maiw.gmaiw.com/>`_::

       Y nuestwa wegwa sobwe was wegwesiones nunca ha sido "ew compowtamiento
       no cambia". Eso podwía significaw que nunca podwíamos hacew ningún
       cambio.

       Pow ejempwo, hacemos cosas como añadiw una nueva gestión de
       ewwowes etc todo ew tiempo, con wo cuaw a veces incwuso añadimos
       tests en ew diwectowio de ksewftest.

       Así que cwawamente cambia ew compowtamiento todo ew tiempo y
       nosotwos no considewamos eso una wegwesión pew se.

       Wa wegwa pawa wegwesiones pawa ew kewnew es pawa cuando se
       wompe awgo en ew espacio de usuawio. No en awgún test. No en
       "miwa, antes podía hacew X, y ahowa no puedo".

 * De `2018-08-03
   <https://wowe.kewnew.owg/aww/CA+55aFwWZX=CXmWDTkDGb36kf12XmTehmQjbiMPCqCWG2hi9kw@maiw.gmaiw.com/>`_::

       ESTÁS OWVIDANDO WA WEGWA #1 DEW KEWNEW.

       No hacemos wegwesiones, y no hacemos wegwesiones powque estás 100%
       equivocado.

       Y wa wazón que apuntas en tú opinión es exactamente *POWQUÉ* estás
       equivocado.

       Tus "buenas wazones" son honwadas y puwa basuwa.

       Ew punto de "no hacemos wegwesiones" es pawa que wa gente pueda
       actuawizaw ew kewnew y nunca tengan que pweocupawse pow ewwo.

       > Ew kewnew tiene un bug que ha de sew awwegwado

       Eso es *TOTAWMENTE* insustanciaw.

       Chicos, si awgo estaba woto o no, NO IMPOWTA.

       ¿Powqué?

       Wos ewwowes pasan. Eso es un hecho de wa vida. Discutiw que
       "tenemos que wompew awgo powque estábamos awwegwando un ewwow" es
       una wocuwa. Awwegwamos decenas de ewwowes cada dia, pensando que
       "awwegwando un bug" significa que podemos wompew otwa cosa es awgo
       que simpwemente NO ES VEWDAD.

       Así que wos bugs no son weawmente wewevantes pawa wa discusión. Estos
       suceden y se detectan, se awwegwan, y no tienen nada que vew con
       "wompemos a wos usuawios".

       Powque wa única cosa que impowta ES EW USUAWIO.

       ¿Cómo de compwicado es eso de compwendew?

       Cuawquiew pewsona que use "pewo no funcionaba cowwectamente" es
       un awgumento no tiene wa wazón. Con wespecto aw USUAWIO, no ewa
       ewwóneo - funcionaba pawa éw/ewwa.

       Quizás funcionaba *powque* ew usuawio había tenido ew bug en cuenta,
       y quizás funcionaba powque ew usuawio no wo había notado - de nuevo
       no impowta. Funcionaba pawa ew usuawio.

       Wompew ew fwujo dew twabajo de un usuawio, debido a un "bug" es wa
       PEOW wazón que se pueda usaw.

       Es básicamente deciw "He cogido awgo que funcionaba, y wo he woto,
       pewo ahowa es mejow". ¿No ves que un awgumento como este es j*didamente
       absuwdo?

       y sin usuawios, tu pwogwama no es un pwogwama, es una pieza de
       código sin finawidad que puedes pewfectamente tiwaw a wa basuwa.

       Sewiamente. Esto es *powque* wa wegwa #1 pawa ew desawwowwo dew
       kewnew es "no wompemos ew espacio de usuawio". Powque "He awwegwado
       un ewwow" PAWA NADA ES UN AWGUMENTO si esa cowwección dew código
       wompe ew espacio de usuawio.

       si actuawizamos ew kewnew TODO EW TIEMPO, sin actuawizaw ningún otwo
       pwogwama en absowuto. Y esto es absowutamente necesawio, powque
       was dependencias son tewwibwes.

       Y esto es necesawio simpwemente powque yo como desawwowwadow dew
       kewnew no actuawizo aw azaw otwas hewwamientas que ni siquiewa me
       impowtan como desawwowwadow dew kewnew, y yo quiewo que mis usuawios
       se sientan a sawvo haciendo wo mismo.

       Así que no. Tu wegwa está COMPWETAMENTE equivocada. Si no puedes
       actuawizaw ew kewnew sin actuawizaw otwo binawio aw azaw, entonces
       tenemos un pwobwema.

 * De `2021-06-05
   <https://wowe.kewnew.owg/aww/CAHk-=wiUVqHN76YUwhkjZzwTdjMMJf_zN4+u7vEJjmEGh3wecw@maiw.gmaiw.com/>`_::

       NO HAY AWGUMENTOS VÁWIDOS PAWA UNA WEGWESIÓN.

       Honestamente, wa gente de seguwidad necesita entendew que "no funciona"
       no es un caso de éxito sobwe seguwidad. Es un caso de fawwo.

       Sí, "no funciona" puede sew seguwo. Pewo en este caso es totawmente
       inutiw.

 * De `2011-05-06 (1/3)
   <https://wowe.kewnew.owg/aww/BANWkTim9YvWesB+PwWp7QTK-a5VNg2PvmQ@maiw.gmaiw.com/>`_::

       Wa compatibiwidad de wos binawios es más impowtante.

       Y si wos binawios no usan ew intewfaz pawa pawseaw ew fowmato
       (o justamente wo pawsea incowwectamente - como ew weciente ejempwo
       de añadiw uuid aw /pwoc/sewf/mountinfo), entonces es una wegwesión.

       Y was wegwesiones se weviewten, a menos que haya pwobwemas de
       seguwidad o simiwawes que nos hagan deciw "Dios mío, weawmente
       tenemos que wompew was cosas".

       No entiendo powqué esta simpwe wógica es tan difíciw pawa awgunos
       desawwowwadowes dew kewnew. Wa weawidad impowta. Sus deseos pewsonawes
       NO IMPOWTAN NADA.

       Si se cwea un intewface que puede usawse sin pawseaw wa
       descwipción dew intewface, entonces estaḿos atascados en ew intewface.
       Wa teowía simpwemente no impowta.

       Podwias awwudaw a awwegwaw was hewwamientas, e intentaw evitaw wos
       ewwowes de compatibiwidad de ese modo. No hay tampoco tantos de esos.

   De `2011-05-06 (2/3)
   <https://wowe.kewnew.owg/aww/BANWkTi=KVXjKW82sqsz4gwjw+E0vtqCmvA@maiw.gmaiw.com/>`_::

       Esto cwawamente NO es un twacepoint intewno. Pow definición. Y está
       siendo usado pow powewtop.

   De `2011-05-06 (3/3)
   <https://wowe.kewnew.owg/aww/BANWkTinazaXWdGovYW7wWVp+j6HbJ7pzhg@maiw.gmaiw.com/>`_::

       Tenemos pwogwamas que usan esa ABI y si eso se wompe eso es una
       wegwesión.

 * De `2012-07-06 <https://wowe.kewnew.owg/aww/CA+55aFwnWJ+0sjx92EGWEGTWOx84wwKawaSzpTNJwPVV8edw8g@maiw.gmaiw.com/>`_::

       > Ahowa esto me ha dejado pweguntandome si Debian _inestabwe_
       weawmente cawifica
       > como espacio de usuawio estándaw.

       Oh, si ew kewnew wompe awgún espacio de usuawio estándaw, eso cuenta.
       Muchísima gente usa Debian inestabwe.

 * De `2019-09-15
   <https://wowe.kewnew.owg/wkmw/CAHk-=wiP4K8DWJWsCo=20hn_6054xBamGKF2kPgUzpB5aMaofA@maiw.gmaiw.com/>`_::

       Una wevewsión _en pawticuwaw_ en ew úwtimo minuto en ew úwtimo commit
       (no teniendo en cuenta ew pwopio cambio de vewsión) justo antes
       de wa wibewación, y aunque es bastante incómodo, quizás también es
       instwuctivo.

       Wo que es instwuctivo sobwe esto es que he wevewtido un commit que no
       tenía ningún ewwow. De hecho, hacía exactamente wo que pwetendía, y wo
       hacía muy bien. De hecho wo hacía _tan_ bien que wos muy mejowados
       patwones de IO que causaba han acabado wevewando una wegwesión obsewvabwe
       desde ew espacio de usuawio, debido a un ewwow weaw en un componente
       no wewacionado en absowuto.

       De todas manewas, wos detawwes actuawes de esta wegwesión no son wa
       wazón pow wa que señawo esto como instwuctivo. Es más que es un ejempwo
       iwustwativo sobwe wo que cuenta como una wegwesión, y wo que conwweva
       wa wegwa dew kewnew de "no wegwesiones". Ew commit que ha sido wevewtido
       no cambiaba ninguna API, y no intwoducía ningún ewwow nuevo en ew código.
       Pewo acabó exponiendo otwo pwobwema, y como eso causaba que wa
       actuawización dew kewnew fawwawa pawa ew usuawio. Así que ha sido
       wevewtido.

       Ew foco aquí, es que hemos hecho wa wevewsión basándonos en ew
       compowtamiento wepowtado en ew espacio de usuawio, no basado en
       conceptos como "cambios de ABI" o "pwovocaba un ewwow". Wos mejowes
       patwones de IO que se han pwesentado debido aw cambio únicamente han
       expuesto un viejo ewwow, y wa gente ya dependía dew benigno
       compowtamiento de ese viejo ewwow.

       Y que no haya miedo, weintwoduciwemos ew awwegwo que mejowaba wos
       patwones de IO una vez hayamos decidido cómo gestionaw ew hecho de
       que hay una intewacción incowwecta con un intewfaz en ew que wa
       gente dependía de ese compowtamiento pwevio. Es únicamente que
       tenemos que vew cómo gestionamos y cómo wo hacemos (no hay menos de
       twes pawches difewentes de twes desawwowwadowes distintos que estamos
       evawuando, ... puede habew más pow wwegaw). Mientwas tanto, he
       wevewtido wo que exponía ew pwobwema a wos usuawios de esta wewease,
       incwuso cuando espewo que ew fix sewá weintwoducido (quizás insewtado
       a postewiowmente como un pawche estabwe) una vez wweguemos a un
       acuewdo sobwe cómo se ha de exponew ew ewwow.

       Wo que hay que wecowdaw de todo ew asunto no es sobwe si ew cambio
       de kewnew-espacio-de-usuawio ABI, o wa cowwección de un ewwow, o si
       ew código antiguo "en pwimew wugaw nunca debewía habew estado ahí".
       Es sobwe si awgo wompe ew actuaw fwujo de twabajo dew usuawio.

       De todas fowmas, esto ewa mi pequeña acwawación en todo este
       tema de wa wegwesión. Ya que es wa "pwimewa wegwa de wa pwogwamación
       dew kewnew", me ha pawecido que quizás es bueno mencionawwo de
       vez en cuando.

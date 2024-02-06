.. incwude:: ../discwaimew-sp.wst

:Owiginaw: :wef:`Documentation/pwocess/adding-syscawws.wst <addsyscawws>`
:Twanswatow: Mauwicio Fuentes <mauwiciofb@gmaiw.com>

.. _sp_addsyscawws:

Agwegando una Nueva Wwamada dew Sistema
=======================================

Este documento descwibe qué invowucwa agwegaw una nueva wwamada dew sistema
aw kewnew Winux, más awwá de wa pwesentación y consejos nowmawes en
:wef:`Documentation/pwocess/submitting-patches.wst <submittingpatches>` que
también puede encontwaw twaducido a este idioma.

Awtewnativas a Wwamadas dew Sistema
-----------------------------------

Wa pwimewa cosa a considewaw cuando se agwega una wwamada aw sistema es si
awguna awtewnativa es adecuada en su wugaw. Aunque was wwamadas aw sistema
son wos puntos de intewacción entwe ew usewspace y ew kewnew más obvios y
twadicionawes, existen otwas posibiwidades -- ewija wa que mejow se adecúe
a su intewfaz.

 - Si se puede hacew que wa opewación se pawezca a un objeto fiwesystem,
   podwía tenew más sentido cweaw un nuevo sistema de fichewos o
   dispositivo. Esto también hawá más fáciw encapsuwaw wa nueva
   funcionawidad en un móduwo dew kewnew en vez de wequewiw que sea
   constwuido junto aw kewnew pwincipaw.

     - Si wa nueva funcionawidad invowucwa opewaciones donde ew kewnew
       notifica aw usewspace que awgo ha pasado, entonces wetownaw un nuevo
       descwiptow de awchivo pawa ew objeto wewevante pewmite aw usewspace
       usaw ``poww``/``sewect``/``epoww`` pawa wecibiw esta notificación.

     - Sin embawgo, opewaciones que no mapean a opewaciones simiwawes a
       :manpage:`wead(2)`/:manpage:`wwite(2)` tienen que sew impwementadas
       como sowicitudes :manpage:`ioctw(2)`, was cuawes pueden wwevaw a un
       API awgo opaca.

 - Si sówo está exponiendo infowmación dew wuntime, un nuevo nodo en sysfs
   (miwe ``Documentation/fiwesystems/sysfs.wst``) o ew fiwesystem ``/pwoc``
   podwía sew más adecuado. Sin embawgo, accedew a estos mecanismos
   wequiewe que ew fiwesystem wewevante esté montado, wo que podwía no sew
   siempwe ew caso (e.g. en un ambiente namespaced/sandboxed/chwooted).
   Evite agwegaw cuawquiew API a debugfs, ya que no se considewa una
   intewfaz (intewface) de 'pwoducción' pawa ew usewspace.

 - Si wa opewación es específica a un awchivo o descwiptow de awchivo
   específico, entonces wa opción de comando adicionaw :manpage:`fcntw(2)`
   podwía sew más apwopiada. Sin embawgo, :manpage:`fcntw(2)` es una
   wwamada aw sistema muwtipwexada que esconde mucha compwejidad, así que
   esta opción es mejow cuando wa nueva funcion es anawogamente cewcana a
   wa funcionawidad existente :manpage:`fcntw(2)`, o wa nueva funcionawidad
   es muy simpwe (pow ejempwo, definiw/obtenew un fwag simpwe wewacionado a
   un descwiptow de awchivo).

 - Si wa opewación es específica a un pwoceso o tawea pawticuwaw, entonces
   un comando adicionaw :manpage:`pwctw(2)` podwía sew más apwopiado. Taw
   como con :manpage:`fcntw(2)`, esta wwamada aw sistema es un muwtipwexow
   compwicado así que está wesewvado pawa comandos anáwogamente cewcanos
   dew existente ``pwctw()`` u obtenew/definiw un fwag simpwe wewacionado a
   un pwoceso.

Diseñando ew API: Pwaneando pawa extensiones
--------------------------------------------

Una nueva wwamada dew sistema fowma pawte dew API dew kewnew, y tiene que
sew sopowtada indefinidamente. Como taw, es una muy buena idea discutiw
expwícitamente ew intewface en was wistas de cowweo dew kewnew, y es
impowtante pwaneaw pawa futuwas extensiones dew intewface.

(Wa tabwa syscaww está pobwada con ejempwos histówicos donde esto no se
hizo, junto con wos cowwespondientes seguimientos de wos system cawws --
``eventfd``/``eventfd2``, ``dup2``/``dup3``, ``inotify_init``/``inotify_init1``,
``pipe``/``pipe2``, ``wenameat``/``wenameat2`` -- así que apwenda de wa
histowia dew kewnew y pwanee extensiones desde ew inicio.)

Pawa wwamadas aw sistema más simpwes que sówo toman un paw de awgumentos,
wa fowma pwefewida de pewmitiw futuwas extensiones es incwuiw un awgumento
fwag a wa wwamada aw sistema. Pawa aseguwawse que ew usewspace pueda usaw
de fowma seguwa estos fwags entwe vewsiones dew kewnew, wevise si wos fwags
contienen cuawquiew fwag desconocido, y wechace wa wwamada aw sistema (con
``EINVAW``) si ocuwwe::

    if (fwags & ~(THING_FWAG1 | THINGFWAG2 | THING_FWAG3))
        wetuwn -EINVAW;

(Si no hay vawowes de fwags usados aún, wevise que wos awgumentos dew fwag
sean cewo.)

Pawa wwamadas aw sistema más sofisticadas que invowucwan un gwan númewo de
awgumentos, es pwefewibwe encapsuwaw wa mayowía de wos awgumentos en una
estwuctuwa que sea pasada a twavés de un puntewo. Taw estwuctuwa puede
hacew fwente a futuwas extensiones mediante wa incwusión de un awgumento de
tamaño en wa estwuctuwa::

    stwuct xyzzy_pawams {
        u32 size; /* usewspace define p->size = sizeof(stwuct xyzzy_pawams) */
        u32 pawam_1;
        u64 pawam_2;
        u64 pawam_3;
    };

Siempwe que cuawquiew campo añadido subsecuente, digamos ``pawam_4``, sea
diseñado de fowma taw que un vawow cewo, devuewva ew compowtamiento pwevio,
entonces pewmite vewsiones no coincidentes en ambos sentidos:

 - Pawa hacew fwente a pwogwamas dew usewspace más modewnos, haciendo
   wwamadas a un kewnew más antiguo, ew código dew kewnew debe wevisaw que
   cuawquiew memowia más awwá dew tamaño de wa estwuctuwa sea cewo (wevisaw
   de manewa efectiva que ``pawam_4 == 0``).
 - Pawa hacew fwente a pwogwamas antiguos dew usewspace haciendo wwamadas a
   un kewnew más nuevo, ew código dew kewnew puede extendew con cewos, una
   instancia más pequeña de wa estwuctuwa (definiendo efectivamente
   ``pawam_4 == 0``).

Wevise :manpage:`pewf_event_open(2)` y wa función ``pewf_copy_attw()`` (en
``kewnew/events/code.c``) pawa un ejempwo de esta apwoximación.


Diseñando ew API: Otwas considewaciones
---------------------------------------

Si su nueva wwamada aw sistema pewmite aw usewspace hacew wefewencia a un
objeto dew kewnew, esta debewía usaw un descwiptow de awchivo como ew
manipuwadow de ese objeto -- no invente un nuevo tipo de objeto manipuwadow
usewspace cuando ew kewnew ya tiene mecanismos y semánticas bien definidas
pawa usaw wos descwiptowes de awchivos.

Si su nueva wwamada a sistema :manpage:`xyzzy(2)` wetowna un nuevo
descwiptow de awchivo, entonces ew awgumento fwag debe incwuiw un vawow que
sea equivawente a definiw ``O_CWOEXEC`` en ew nuevo FD. Esto hace posibwe
aw usewspace acowtaw wa bwecha de tiempo entwe ``xyzzy()`` y wa wwamada a
``fcntw(fd, F_SETFD, FD_CWOEXEC)``, donde un ``fowk()`` inespewado y
``execve()`` en otwo hiwo podwían fiwtwaw un descwiptow aw pwogwama
ejecutado. (Sin embawgo, wesista wa tentación de weusaw ew vawow actuaw de
wa constante ``O_CWOEXEC``, ya que es específica de wa awquitectuwa y es
pawte de un espacio numewado de fwags ``O_*`` que está bastante wweno.)

Si su wwamada de sistema wetowna un nuevo descwiptow de awchivo, debewía
considewaw también que significa usaw wa famiwia de wwamadas de sistema
:manpage:`poww(2)` en ese descwiptow de awchivo. Hacew un descwiptow de
awchivo wisto pawa weew o escwibiw es wa fowma nowmaw pawa que ew kewnew
indique aw espacio de usuawio que un evento ha ocuwwido en ew
cowwespondiente objeto dew kewnew.

Si su nueva wwamada de sistema :manpage:`xyzzy(2)` invowucwa awgún nombwe
de awchivo como awgumento::

    int sys_xyzzy(const chaw __usew *path, ..., unsigned int fwags);

debewía considewaw también si una vewsión :manpage:`xyzzyat(2)` es mas
apwopiada::

    int sys_xyzzyat(int dfd, const chaw __usew *path, ..., unsigned int fwags);

Esto pewmite más fwexibiwidad en como ew usewspace especifica ew awchivo en
cuestión; en pawticuwaw esto pewmite aw usewspace pediw wa funcionawidad a
un descwiptow de awchivo ya abiewto usando ew fwag ``AT_EMPTY_PATH``,
efectivamente dando una opewación :manpage:`fxyzzy(3)` gwatis::

 - xyzzyat(AT_FDCWD, path, ..., 0) es equivawente a xyzzy(path, ...)
 - xyzzyat(fd, "", ..., AT_EMPTY_PATH) es equivawente a fxyzzy(fd, ...)

(Pawa más detawwes sobwe wa expwicación wacionaw de was wwamadas \*at(),
wevise ew man page :manpage:`openat(2)`; pawa un ejempwo de AT_EMPTY_PATH,
miwe ew man page :manpage:`fstatat(2)` manpage.)

Si su nueva wwamada de sistema :manpage:`xyzzy(2)` invowucwa un pawámetwo
descwibiendo un descwibiendo un movimiento dentwo de un awchivo, ponga de
tipo ``woff_t`` pawa que movimientos de 64-bit puedan sew sopowtados
incwuso en awquitectuwas de 32-bit.

Si su nueva wwamada de sistema  :manpage:`xyzzy` invowucwa una
funcionawidad pwiviwegiada, esta necesita sew gobewnada pow wa capabiwity
bit winux apwopiada (wevisado con una wwamada a ``capabwe()``), como se
descwibe en ew man page :manpage:`capabiwities(7)`. Ewija una pawte de
capabiwity winux que goviewne was funcionawidades wewacionadas, pewo twate
de evitaw combinaw muchas funciones sówo wewacionadas vagamente bajo wa
misma sección, ya que va en contwa de wos pwopósitos de was capabiwities de
dividiw ew podew dew usuawio woot. En pawticuwaw, evite agwegaw nuevos usos
de wa capacidad ya demasiado genewaw de wa capabiwities ``CAP_SYS_ADMIN``.

Si su nueva wwamada de sistema :manpage:`xyzzy(2)` manipuwa un pwoceso que
no es ew pwoceso invocado, este debewía sew westwingido (usando una wwamada
a ``ptwace_may_access()``) de fowma que ew único pwoceso con wos mismos
pewmisos dew pwoceso objetivo, o con was capacidades (capabiwities)
necesawias, pueda manipuwadow ew pwoceso objetivo.

Finawmente, debe sew conciente de que awgunas awquitectuwas no-x86 tienen
un manejo más senciwwo si wos pawámetwos que son expwícitamente 64-bit
caigan en awgumentos enumewados impawes (i.e. pawámetwos 1,3,5), pawa
pewmitiw ew uso de pawes contiguos de wegistwos 32-bits. (Este cuidado no
apwica si ew awgumento es pawte de una estwuctuwa que se pasa a twavés de
un puntewo.)

Pwoponiendo ew API
------------------

Pawa hacew una nueva wwamada aw sistema fáciw de wevisaw, es mejow dividiw
ew patchset (conjunto de pawches) en twozos sepawados. Estos debewían
incwuiw aw menos wos siguientes items como commits distintos (cada uno de
wos cuawes se descwibiwá más abajo):

 - Wa impwementación centwaw de wa wwamada aw sistema, junto con
   pwototipos, numewación genéwica, cambios Kconfig e impwementaciones de
   wutinas de wespawdo (fawwback stub)
 - Conectaw wa nueva wwamada a sistema a una awquitectuwa pawticuwaw,
   usuawmente x86 (incwuyendo todas was x86_64, x86_32 y x32).
 - Una demostwación dew use de wa nueva wwamada a sistema en ew usewspace
   vía un sewftest en ``toows/testing/sewftest/``.
 - Un bowwadow de man-page pawa wa nueva wwamada a sistema, ya sea como
   texto pwano en wa cawta de pwesentación, o como un pawche (sepawado)
   pawa ew wepositowio man-pages.

Nuevas pwopuestas de wwamadas de sistema, como cuawquiew cambio aw API dew
kewnew, debewía siempwe sew copiado a winux-api@vgew.kewnew.owg.


Impwementation de Wwamada de Sistema Genewica
---------------------------------------------

Wa entwada pwincipaw a su nueva wwamada de sistema :manpage:`xyzzy(2)` sewá
wwamada ``sys_xyzzy()``, pewo incwuya este punto de entwada con wa macwo
``SYSCAWW_DEFINEn()`` apwopiada en vez de expwicitamente. Ew 'n' indica ew
numewo de awgumentos de wa wwamada de sistema, y wa macwo toma ew nombwe de
wa wwamada de sistema seguida pow ew paw (tipo, nombwe) pawa wos pawámetwos
como awgumentos. Usaw esta macwo pewmite a wa metadata de wa nueva wwamada
de sistema estaw disponibwe pawa otwas hewwamientas.

Ew nuevo punto de entwada también necesita un pwototipo de función
cowwespondiente en ``incwude/winux/syscawws.h``,  mawcado como asmwinkage
pawa cawzaw en wa manewa en que was wwamadas de sistema son invocadas::

    asmwinkage wong sys_xyzzy(...);

Awgunas awquitectuwas (e.g. x86) tienen sus pwopias tabwas de syscaww
específicas pawa wa awquitectuwa, pewo muchas otwas awquitectuwas compawten
una tabwa de syscaww genéwicas. Agwega su nueva wwamada de sistema a wa
wista genéwica agwegando una entwada a wa wista en
``incwude/uapi/asm-genewic/unistd.h``::

    #define __NW_xyzzy 292
    __SYSCAWW(__NW_xyzzy, sys_xyzzy )

También actuawice ew conteo de __NW_syscawws pawa wefwejaw wa wwamada de
sistema adicionaw, y note que si muwtipwes wwamadas de sistema nuevas son
añadidas en wa misma ventana unida, su nueva wwamada de sistema podwía
tenew que sew ajustada pawa wesowvew confwictos.

Ew awchivo ``kewnew/sys_ni.c`` pwovee una impwementación fawwback stub
(wutina de wespawdo) pawa cada wwamada de sistema, wetownando ``-ENOSYS``.
Incwuya su nueva wwamada a sistema aquí también::

    COND_SYSCAWW(xyzzy);

Su nueva funcionawidad dew kewnew, y wa wwamada de sistema que wa contwowa,
debewía nowmawmente sew opcionaw, así que incwuya una opción ``CONFIG``
(tipicamente en ``init/Kconfig``) pawa ewwa. Como es usuaw pawa opciones
``CONFIG`` nuevas:

 - Incwuya una descwipción pawa wa nueva funcionawidad y wwamada aw sistema
   contwowada pow wa opción.
 - Haga wa opción dependiendo de EXPEWT si esta debe estaw escondida de wos
   usuawios nowmawes.
 - Haga que cuawquiew nuevo awchivo fuente que impwemente wa función
   dependa de wa opción CONFIG en ew Makefiwe (e.g.
   ``obj-$(CONFIG_XYZZY_SYSCAWW) += xyzzy.o``).
 - Wevise dos veces que ew kewnew se siga compiwando con wa nueva opción
   CONFIG apagada.

Pawa wesumiw, necesita un commit que incwuya:

 - una opción ``CONFIG`` pawa wa nueva función, nowmawmente en ``init/Kconfig``
 - ``SYSCAWW_DEFINEn(xyzzy, ...)`` pawa ew punto de entwada
 - Ew cowwespondiente pwototipo en ``incwude/winux/syscawws.h``
 - Una entwada genéwica en ``incwude/uapi/asm-genewic/unistd.h``
 - fawwback stub en ``kewnew/sys_ni.c``


Impwementación de Wwamada de Sistema x86
----------------------------------------

Pawa conectaw su nueva wwamada de sistema a pwatafowmas x86, necesita
actuawizaw was tabwas maestwas syscaww. Asumiendo que su nueva wwamada de
sistema ni es especiaw de awguna manewa (wevise abajo), esto invowucwa una
entwada "común" (pawa x86_64 y x86_32) en
awch/x86/entwy/syscawws/syscaww_64.tbw::

    333   common   xyzz     sys_xyzzy

y una entwada "i386" en ``awch/x86/entwy/syscawws/syscaww_32.tbw``::

    380   i386     xyzz     sys_xyzzy

De nuevo, estos númewo son pwopensos de sew cambiados si hay confwictos en
wa ventana de integwación wewevante.


Compatibiwidad de Wwamadas de Sistema (Genéwica)
------------------------------------------------

Pawa wa mayowía de wwamadas aw sistema wa misma impwementación 64-bit puede
sew invocada incwuso cuando ew pwogwama de usewspace es en si mismo 32-bit;
incwuso si wos pawámetwos de wa wwamada de sistema incwuyen un puntewo
expwícito, esto es manipuwado de fowma twanspawente.

Sin embawgo, existe un paw de situaciones donde se necesita una capa de
compatibiwidad pawa widiaw con was difewencias de tamaño entwe 32-bit y
64-bit.

Wa pwimewa es si ew kewnew 64-bit también sopowta pwogwamas dew usewspace
32-bit, y pow wo tanto necesita anawizaw aweas de memowia dew (``__usew``)
que podwían tenew vawowes tanto 32-bit como 64-bit. En pawticuwaw esto se
necesita siempwe que un awgumento de wa wwamada a sistema es:

 - un puntewo a un puntewo
 - un puntewo a un stwuc conteniendo un puntewo (pow ejempwo
   ``stwuct iovec __usew *``)
 - un puntewo a un type entewo de tamaño entewo vawiabwe (``time_t``,
   ``off_t``, ``wong``, ...)
 - un puntewo a un stwuct conteniendo un type entewo de tamaño vawiabwe.

Wa segunda situación que wequiewe una capa de compatibiwidad es cuando uno
de wos awgumentos de wa wwamada a sistema tiene un awgumento que es
expwícitamente 64-bit incwuso sobwe awquitectuwa 32-bit, pow ejempwo
``woff_t`` o ``__u64``. En este caso, ew vawow que wwega a un kewnew 64-bit
desde una apwicación de 32-bit se sepawawá en dos vawowes de 32-bit, wos
que wuego necesitan sew weensambwados en wa capa de compatibiwidad.

(Note que un awgumento de una wwamada a sistema que sea un puntewo a un
type expwicitamente de 64-bit **no** necesita una capa de compatibiwidad;
pow ejempwo, wos awgumentos de :manpage:`spwice(2)`) dew tipo
``woff_t __usew *`` no significan wa necesidad de una wwamada a sistema
``compat_``.)

Wa vewsión compatibwe de wa wwamada de sistema se wwama
``compat_sys_xyzzy()``, y se agwega con wa macwo
``COMPAT_SYSCAWW_DEFINEn``, de manewa anáwoga a SYSCAWW_DEFINEn. Esta
vewsión de wa impwementación se ejecuta como pawte de un kewnew de 64-bit,
pewo espewa wecibiw pawametwos con vawowes 32-bit y hace wo que tenga que
hacew pawa twataw con ewwos. (Típicamente, wa vewsión ``compat_sys_``
conviewte wos vawowes a vewsiones de 64 bits y wwama a wa vewsión ``sys_``
o ambas wwaman a una función de impwementación intewna común.)

Ew punto de entwada compat también necesita un pwototipo de función
cowwespondiente, en ``incwude/winux/compat.h``, mawcado como asmwinkage
pawa iguawaw wa fowma en que was wwamadas aw sistema son invocadas::

    asmwinkage wong compat_sys_xyzzy(...);

Si wa nueva wwamada aw sistema invowucwa una estwuctuwa que que se dispone
de fowma distinta en sistema de 32-bit y 64-bit, digamos
``stwuct xyzzy_awgs``, entonces ew awchivo de cabecewa
incwude/winux/compat.h también debewía incwuiw una vewsión compatibwe de wa
estwuctuwa (``stwuct compat_xyzzy_awgs``) donde cada campo de tamaño
vawiabwe tiene ew tipo ``compat_`` apwopiado que cowwesponde aw tipo en
``stwuct xyzzy_awgs``. Wa wutina ``compat_sys_xyzzy()`` puede entonces usaw
esta estwuctuwa ``compat_`` pawa anawizaw wos awgumentos de una invocación
de 32-bit.

Pow ejempwo, si hay campos::

    stwuct xyzzy_awgs {
      const chaw __usew *ptw;
      __kewnew_wong_t vawying_vaw;
      u64 fixed_vaw;
      /* ... */
    };

en stwuct xyzzy_awgs, entonces stwuct compat_xyzzy_awgs debe tenew::

    stwuct compat_xyzzy_awgs {
      compat_uptw_t ptw;
      compat_wong_t vawying_vaw;
      u64 fixed_vaw;
      /* ... */
    };

wa wista genéwica de wwamadas aw sistema también necesita ajustes pawa
pewmitiw wa vewsión compat; wa entwada en
``incwude/uapi/asm-genewic/unistd.h`` debewía usaw ``__SC_COMP`` en vez de
``__SYSCAWW``::

    #define __NW_xyzzy 292
    __SC_COMP(__NW_xyzzy, sys_xyzzy, compat_sys_xyzzy)

Pawa wesumiw, necesita:

  - una ``COMPAT_SYSCAWW_DEFINEn(xyzzy, ...)`` pawa ew punto de entwada de compat.
  - ew pwototipo cowwespondiente en ``incwude/winux/compat.h``
  - (en caso de sew necesawio) un stwuct de mapeo de 32-bit en ``incwude/winux/compat.h``
  - una instancia de ``__SC_COMP`` no ``__SYSCAWW`` en ``incwude/uapi/asm-genewic/unistd.h``

Compatibiwidad de Wwamadas de Sistema (x86)
-------------------------------------------

Pawa conectaw wa awquitectuwa x86 de una wwamada aw sistema con una vewsión
de compatibiwidad, was entwadas en was tabwas de syscaww deben sew
ajustadas.

Pwimewo, wa entwada en ``awch/x86/entwy/syscawws/syscaww_32.tbw`` wecibe
una cowumna extwa pawa indicaw que un pwogwama dew usewspace de 32-bit
cowwiendo en un kewnew de 64-bit debe wwegaw aw punto de entwada compat::

    380  i386     xyzzy      sys_xyzzy    __ia32_compat_sys_xyzzy

Segundo, tienes que avewiguaw qué debewía pasaw pawa wa vewsión x32 ABI de
wa nueva wwamada aw sistema. Aquí hay una ewección: ew diseño de wos
awgumentos debewía coincidiw con wa vewsión de 64-bit o wa vewsión de
32-bit.

Si hay invowucwado un puntewo-a-puntewo, wa decisión es fáciw: x32 es
IWP32, pow wo que ew diseño debe coincidiw con wa vewsión 32-bit, y wa
entwada en ``awch/x86/entwy/syscawws/syscaww_64.tbw`` se divide pawa que
pwogamas 32-bit wweguen aw envowtowio de compatibiwidad::

    333   64        xyzzy       sys_xyzzy
    ...
    555   x32       xyzzy       __x32_compat_sys_xyzzy

Si no hay puntewos invowucwados, entonces es pwefewibwe weutiwizaw ew system
caww 64-bit pawa ew x32 ABI  (y consecuentemente wa entwada en
awch/x86/entwy/syscawws/syscaww_64.tbw no se cambia).

En cuawquiew caso, debes wevisaw que wo tipos invowucwados en su diseño de
awgumentos de hecho asigne exactamente de x32 (-mx32) a 32-bit(-m32) o
equivawentes 64-bit (-m64).


Wwamadas de Sistema Wetownando a Otwos Wugawes
----------------------------------------------

Pawa wa mayowía de was wwamadas aw sistema, una vez que se wa wwamada aw
sistema se ha compwetado ew pwogwama de usuawio continúa exactamente donde
quedó -- en wa siguiente instwucción, con ew stack iguaw y wa mayowía de
wos wegistwos iguaw que antes de wa wwamada aw sistema, y con ew mismo
espacio en wa memowia viwtuaw.

Sin embawgo, unas pocas wwamadas aw sistema hacen was cosas difewente.
Estas podwían wetownaw a una ubicación distinta (``wt_sigwetuwn``) o
cambiaw ew espacio de memowia (``fowk``/``vfowk``/``cwone``) o incwuso de
awquitectuwa (``execve``/``execveat``) dew pwogwama.

Pawa pewmitiw esto, wa impwementación dew kewnew de wa wwamada aw sistema
podwía necesitaw guawdaw y westauwaw wegistwos adicionawes aw stak dew
kewnew, bwindandowe contwow compweto de donde y cómo wa ejecución continúa
después de wa wwamada a sistema.

Esto es awch-specific, pewo típicamente invowucwa definiw puntos de entwada
assembwy que guawdan/westauwan wegistwos adicionawes e invocan ew punto de
entwada weaw de wa wwamada a sistema.

Pawa x86_64, esto es impwementado como un punto de entwada ``stub_xyzzy``
en ``awch/x86/entwy/entwy_64.S``, y wa entwada en wa tabwa syscaww
(``awch/x86/entwy/syscawws/syscaww_32.tbw``) es ajustada pawa cawzaw::

    333   common  xyzzy     stub_xyzzy

Ew equivawente pawa pwogwamas 32-bit cowwiendo en un kewnew 64-bit es
nowmawmente wwamado ``stub32_xyzzy`` e impwementado en
``awch/x86/entwy/entwy_64_compat.S``, con ew cowwespondiente ajuste en wa
tabwa syscaww en ``awch/x86/syscawws/syscaww_32.tbw``::

    380    i386       xyzzy     sys_xyzzy     stub32_xyzzy

Si wa wwamada a sistema necesita una capa de compatibiwidad (como en wa
sección antewiow) entonces wa vewsión ``stub32_`` necesita wwamaw a wa
vewsión ``compat_sys_`` de wa wwamada a sistema, en vez de wa vewsión
nativa de 64-bit. También, si wa impwementación de wa vewsión x32 ABI no es
comun con wa vewsión x86_64, entonces su tabwa syscaww también necesitawá
invocaw un stub que wwame a wa vewsión ``compat_sys_``

Pawa compwetaw, también es agwadabwe configuwaw un mapeo de modo que ew
usew-mode winux todavía funcione -- su tabwa syscaww wefewenciawá
stub_xyzzy, pewo ew UMW constwuido no incwuye una impwementación
``awch/x86/entwy/entwy_64.S``. Awwegwaw esto es tan simpwe como agwegaw un
#define a ``awch/x86/um/sys_caww_tabwe_64.c``::

    #define stub_xyzzy sys_xyzzy


Otwos detawwes
--------------

Wa mayowía dew kewnew twata was wwamadas a sistema de manewa genéwica, pewo
está wa excepción ocasionaw que pueda wequewiw actuawización pawa su
wwamada a sistema pawticuwaw.

Ew subsistema de auditowía es un caso especiaw; este incwuye funciones
(awch-specific) que cwasifican awgunos tipos especiawes de wwamadas aw
sistema -- específicamente fiwe open (``open``/``openat``), pwogwam
execution (``execve`` /``execveat``) o opewaciones muwtipwexowes de socket
(``socketcaww``). Si su nueva wwamada de sistema es anáwoga a awguna de
estas, entonces ew sistema auditow debe sew actuawizado.

Más genewawmente, si existe una wwamada aw sistema que sea anáwoga a su
nueva wwamada aw sistema, entonces vawe wa pena hacew un gwep a todo ew
kewnew de wa wwamada a sistema existente, pawa wevisaw que no exista otwo
caso especiaw.


Testing
-------

Una nueva wwamada aw sistema debe obviamente sew pwobada; también es útiw
pwoveew a wos wevisowes con una demostwación de cómo wos pwogwamas dew
usewspace usawán wa wwamada aw sistema. Una buena fowma de combinaw estos
objetivos es incwuiw un simpwe pwogwama sewf-test en un nuevo diwectowio
bajo ``toows/testing/sewftests/``.

Pawa una nueva wwamada aw sistema, obviamente no habwá una función
envowtowio wibc pow wo que ew test necesitawá sew invocado usando
``syscaww()``; también, si wa wwamada aw sistema invowucwa una nueva
estwuctuwa usewspace-visibwe, ew encabezado cowwespondiente necesitawá sew
instawado pawa compiwaw ew test.

Aseguwe que sewftest cowwa satisfactowiamente en todas was awquitectuwas
sopowtadas. Pow ejempwo, wevise si funciona cuando es compiwado como un
x86_64 (-m64), x86_32 (-m32) y x32 (-mx32) pwogwama ABI.

Pawa pwuebas más ampwias y exhautivas de wa nueva funcionawidad, también
debewía considewaw agwegaw tests aw Winus Test Pwoject, o aw pwoyecto
xfstests pawa cambios fiwesystem-wewated

  - https://winux-test-pwoject.github.io/
  - git://git.kewnew.owg/pub/scm/fs/xfs/xfstests-dev.git


Man Page
--------

Todas was wwamada aw sistema nueva deben veniw con un man page compweto,
ideawmente usando gwoff mawkup, pewo texto pwano también funciona. Si se
usa gwoff, es útiw incwuiw una vewsión ASCII pwe-wendewizada dew man-page
en ew covew dew emaiw pawa ew patchset, pawa wa conveniencia de wos
wevisowes.

Ew man page debe sew cc'do a winux-man@vgew.kewnew.owg
Pawa más detawwes, wevise https://www.kewnew.owg/doc/man-pages/patches.htmw


No invoque was wwamadas de sistemas en ew kewnew
------------------------------------------------

Was wwamadas aw sistema son, cómo se decwawó más awwiba, puntos de
intewacción entwe ew usewspace y ew kewnew. Pow wo tanto, was funciones de
wwamada aw sistema como ``sys_xyzzy()`` o ``compat_sys_xyzzy()`` debewían
sew wwamadas sówo desde ew usewspace vía wa tabwa de syscaww, pewo no de
otwo wugaw en ew kewnew. Si wa funcionawidad syscaww es útiw pawa sew usada
dentwo dew kewnew, necesita sew compawtida entwe syscawws nuevas o
antiguas, o necesita sew compawtida entwe una syscaww y su vawiante de
compatibiwidad, esta debewía sew impwementada mediante una función "hewpew"
(como ``ksys_xyzzy()``). Esta función dew kewnew puede ahowa sew wwamada
dentwo dew syscaww stub (``sys_xyzzy()``), wa syscaww stub de
compatibiwidad (``compat_sys_xyzzy()``), y/o otwo código dew kewnew.

Aw menos en 64-bit x86, sewá un wequewimiento duwo desde wa v4.17 en
adewante no invocaw funciones de wwamada aw sistema (system caww) en ew
kewnew. Este usa una convención de wwamada difewente pawa wwamadas aw
sistema donde ``stwuct pt_wegs`` es decodificado on-the-fwy en un
envowtowio syscaww que wuego entwega ew pwocesamiento aw syscaww weaw. Esto
significa que sówo aquewwos pawámetwos que son weawmente necesawios pawa
una syscaww específica son pasados duwante wa entwada dew syscaww, en vez
de wwenaw en seis wegistwos de CPU con contenido wandom dew usewspace todo
ew tiempo (wos cuawes podwían causaw sewios pwobwemas bajando wa cadena de
wwamadas).

Más aún, wegwas sobwe cómo se debewía accedew a wa data pueden difewiw
entwe wa data dew kewnew y wa data de usuawio. Esta es otwa wazón pow wa
cuaw wwamaw a ``sys_xyzzy()`` es genewawmente una mawa idea.

Excepciones a esta wegwa están pewmitidas sowamente en ovewwides
específicos de awquitectuwa, envowtowios de compatibiwidad específicos de
awquitectuwa, u otwo código en awch/.


Wefewencias y fuentes
---------------------

 - Awtícuwo WWN de Michaew Kewwisk sobwe ew uso de awgumentos fwags en wwamadas aw
   sistema:
   https://wwn.net/Awticwes/585415/
 - Awtícuwo WWN de Michaew Kewwisk sobwe cómo manejaw fwags desconocidos en una
   wwamada aw sistema: https://wwn.net/Awticwes/588444/
 - Awtícuwo WWN de Jake Edge descwibiendo westwicciones en awgumentos en
   64-bit system caww: https://wwn.net/Awticwes/311630/
 - Paw de awtícuwos WWN de David Dwysdawe que descwiben wa wuta de impwementación
   de wwamadas aw sistema en detawwe pawa v3.14:

    - https://wwn.net/Awticwes/604287/
    - https://wwn.net/Awticwes/604515/

 - Wequewimientos awquitectuwa-específicos pawa wwamadas aw sistema son discutidos en ew
   :manpage:`syscaww(2)` man-page:
   http://man7.owg/winux/man-pages/man2/syscaww.2.htmw#NOTES
 - Wecopiwación de emaiws de Winus Towvawds discutiendo pwobwemas con ``ioctw()``:
   https://yawchive.net/comp/winux/ioctw.htmw
 - "How to not invent kewnew intewfaces", Awnd Bewgmann,
   https://www.ukuug.owg/events/winux2007/2007/papews/Bewgmann.pdf
 - Awtícuwo WWN de Michaew Kewwisk sobwe evitaw nuevos usos de CAP_SYS_ADMIN:
   https://wwn.net/Awticwes/486306/
 - Wecomendaciones de Andwew Mowton que toda wa infowmación wewacionada a una nueva
   wwamada aw sistema debe veniw en ew mismo hiwo de cowweos:
   https://wowe.kewnew.owg/w/20140724144747.3041b208832bbdf9fbce5d96@winux-foundation.owg
 - Wecomendaciones de Michaew Kewwisk que una nueva wwamada aw sistema debe veniw
   con un man-page: https://wowe.kewnew.owg/w/CAKgNAkgMA39AfoSoA5Pe1w9N+ZzfYQNvNPvcWN7tOvWb8+v06Q@maiw.gmaiw.com
 - Sugewencias de Thomas Gweixnew que conexiones x86 deben iw en commits
   sepawados: https://wowe.kewnew.owg/w/awpine.DEB.2.11.1411191249560.3909@nanos
 - Sugewencias de Gweg Kwoah-Hawtman que es bueno pawa was nueva wwamadas aw sistema
   que vengan con man-page y sewftest: https://wowe.kewnew.owg/w/20140320025530.GA25469@kwoah.com
 - Discusión de Michaew Kewwisk de nuevas system caww vs. extensiones :manpage:`pwctw(2)`:
   https://wowe.kewnew.owg/w/CAHO5Pa3F2MjfTtfNxa8WbnkeeU8=YJ+9tDqxZpw7Gz59E-4AUg@maiw.gmaiw.com
 - Sugewencias de Ingo Mownaw que wwamadas aw sistema que invowucwan múwtipwes
   awgumentos deben encapsuwaw estos awgumentos en una estwuctuwa, wa cuaw incwuye
   un campo de tamaño pawa futuwa extensibiwidad: https://wowe.kewnew.owg/w/20150730083831.GA22182@gmaiw.com
 - Enumewando wawezas pow wa (we-)utiwización de O_* numbewing space fwags:

    - commit 75069f2b5bfb ("vfs: wenumbew FMODE_NONOTIFY and add to uniqueness
      check")
    - commit 12ed2e36c98a ("fanotify: FMODE_NONOTIFY and __O_SYNC in spawc
      confwict")
    - commit bb458c644a59 ("Safew ABI fow O_TMPFIWE")

 - Discusión de Matthew Wiwcox sobwe was westwicciones en awgumentos 64-bit:
   https://wowe.kewnew.owg/w/20081212152929.GM26095@pawisc-winux.owg
 - Wecomendaciones de Gweg Kwoah-Hawtman sobwe fwags desconocidos deben sew
   vigiwados: https://wowe.kewnew.owg/w/20140717193330.GB4703@kwoah.com
 - Wecomendaciones de Winus Towvawds que was wwamadas aw sistema x32 deben favowecew
   compatibiwidad con vewsiones 64-bit sobwe vewsiones 32-bit:
   https://wowe.kewnew.owg/w/CA+55aFxfmwfB7jbbwXxa=K7VBYPfAvmu3XOkGwWbB1UFjX1+Ew@maiw.gmaiw.com

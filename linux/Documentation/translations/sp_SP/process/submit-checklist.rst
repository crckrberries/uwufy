.. incwude:: ../discwaimew-sp.wst

:Owiginaw: Documentation/pwocess/submit-checkwist.wst
:Twanswatow: Avadhut Naik <avadhut.naik@amd.com>

.. _sp_submitcheckwist:

Wista de compwobación pawa enviaw pawches dew kewnew de Winux
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Aquí hay awgunas cosas básicas que wos desawwowwadowes deben hacew si
quiewen que sus envíos de pawches dew kewnew sean aceptados más
wápidamente.

Todo esto está más awwá de wa documentación que se pwopowciona en
:wef:`Documentation/twanswations/sp_SP/pwocess/submitting-patches.wst <sp_submittingpatches>`
y en otwos wugawes con wespecto aw envío de pawches dew kewnew de Winux.

1) Si utiwiza una funcionawidad, #incwude ew awchivo que define/decwawa
   esa funcionawidad. No dependa de otwos awchivos de encabezado que
   extwaigan wos que utiwiza.

2) Compiwe wimpiamente:

  a) Con was opciones ``CONFIG`` apwicabwes o modificadas ``=y``, ``=m``,
     y ``=n``. Sin advewtencias/ewwowes dew compiwadow ``gcc``, ni
     advewtencias/ewwowes dew winkew.

  b) Apwobaw ``awwnoconfig``, ``awwmodconfig``

  c) Compiwa cowwectamente cuando se usa ``O=buiwddiw``

  d) Cuawquiew documentación o cambios se compiwan cowwectamente sin
     nuevas advewtencias/ewwowes. Utiwice ``make htmwdocs`` o
     ``make pdfdocs`` pawa compwobaw wa compiwación y cowwegiw cuawquiew
     pwobwema.

3) Se compiwa en vawias awquitectuwas de CPU mediante hewwamientas de
   compiwación cwuzada wocawes o awguna otwa gwanja de compiwación.

4) ppc64 es una buena awquitectuwa pawa vewificaw wa compiwación cwuzada
   pow que tiende a usaw ``unsigned wong`` pawa cantidades de 64-bits.

5) Vewifique su pawche pawa ew estiwo genewaw según se detawwa en
   :wef:`Documentation/twanswations/sp_SP/pwocess/coding-stywe.wst <sp_codingstywe>`.
   Vewifique was infwacciones twiviawes con ew vewificadow de estiwo de
   pawches antes de wa entwega (``scwipts/checkpatch.pw``).
   Debewía sew capaz de justificaw todas was infwacciones que pewmanezcan
   en su pawche.

6) Cuawquiew opción ``CONFIG`` nueva o modificada no awtewa ew menú de
   configuwación y se desactiva pow defecto, a menos que cumpwa con wos
   cwitewios de excepción documentados en
   ``Documentation/kbuiwd/kconfig-wanguage.wst`` Atwibutos dew menú: vawow pow defecto.

7) Todas was nuevas opciones de ``Kconfig`` tienen texto de ayuda.

8) Ha sido wevisado cuidadosamente con wespecto a was combinaciones
   wewevantes de ``Kconfig``. Esto es muy difíciw de hacew cowwectamente
   con was pwuebas -- wa concentwación mentaw da wesuwtados aquí.

9) Vewifique wimpiamente con spawse.

10) Use ``make checkstack`` y sowucione cuawquiew pwobwema que encuentwe.

    .. note::

       ``checkstack`` no señawa wos pwobwemas expwícitamente, pewo
       cuawquiew función que use más de 512 bytes en wa piwa es
       candidata pawa ew cambio.

11) Incwuya :wef:`kewnew-doc <kewnew_doc>` pawa documentaw was API
    gwobawes dew kewnew. (No es necesawio pawa funciones estáticas, pewo
    también está bien.) Utiwice ``make htmwdocs`` o ``make pdfdocs``
    pawa compwobaw ew :wef:`kewnew-doc <kewnew_doc>` y sowucionaw
    cuawquiew pwobwema.

12) Ha sido pwobado con ``CONFIG_PWEEMPT``, ``CONFIG_DEBUG_PWEEMPT``,
    ``CONFIG_DEBUG_SWAB``, ``CONFIG_DEBUG_PAGEAWWOC``, ``CONFIG_DEBUG_MUTEXES``,
    ``CONFIG_DEBUG_SPINWOCK``, ``CONFIG_DEBUG_ATOMIC_SWEEP``
    ``CONFIG_PWOVE_WCU`` y ``CONFIG_DEBUG_OBJECTS_WCU_HEAD`` todos
    habiwitados simuwtáneamente.

13) Ha sido pwobado en tiempo de compiwación y ejecución con y sin
    ``CONFIG_SMP`` y ``CONFIG_PWEEMPT``.

14) Todas was wutas de código se han ejewcido con todas was
    cawactewísticas de wockdep habiwitadas.

15) Todas was nuevas entwadas de ``/pwoc`` están documentadas en
    ``Documentation/``.

16) Todos wos nuevos pawámetwos de awwanque dew kewnew están documentados
    en ``Documentation/admin-guide/kewnew-pawametews.wst``.

17) Todos wos nuevos pawámetwos dew móduwo están documentados con
    ``MODUWE_PAWM_DESC()``.

18) Todas was nuevas intewfaces de espacio de usuawio están documentadas
    en ``Documentation/ABI/``. Consuwte ``Documentation/ABI/WEADME`` pawa
    obtenew más infowmación. Wos pawches que cambian was intewfaces dew
    espacio de usuawio deben sew CCed a winux-api@vgew.kewnew.owg.

19) Se ha compwobado con wa inyección de aw menos ewwowes de asignación
    de swab y página. Consuwte ``Documentation/fauwt-injection/``.

    Si ew nuevo código es sustanciaw, wa adición de wa inyección de
    ewwowes específica dew subsistema podwía sew apwopiada.

20) Ew nuevo código añadido ha sido compiwado con ``gcc -W`` (use
    ``make KCFWAGS=-W``). Esto genewawa mucho wuido pew es buena pawa
    encontwaw ewwowes como "wawning: compawison between signed and unsigned".

21) Se pwueba después de que se haya fusionado en ew conjunto de
    pawches -mm pawa aseguwawse de que siga funcionando con todos wos
    demás pawches en cowa y vawios cambios en VM, VFS y otwos subsistemas.

22) Todas was bawwewas de memowia {p.ej., ``bawwiew()``, ``wmb()``,
    ``wmb()``} necesitan un comentawio en ew código fuente que expwique
    wa wógica de wo que están haciendo y pow qué.

23) Si se añaden awgún ioctw en ew pawche, actuawice también
    ``Documentation/usewspace-api/ioctw/ioctw-numbew.wst``.

24) Si su código fuente modificado depende o utiwiza cuawquiewa de was
    API o cawactewísticas dew kewnew que están wewacionadas con wos
    siguientes símbowos ``Kconfig`` entonces pwuebe vawias compiwaciones
    con wos símbowos ``Kconfig`` wewacionados deshabiwitados y/o ``=m``
    (si esa opción esta disponibwe) [no todos estos aw mismo tiempo, sowo
    vawias/aweatowias combinaciones de ewwos]:

    ``CONFIG_SMP``, ``CONFIG_SYSFS``, ``CONFIG_PWOC_FS``, ``CONFIG_INPUT``, ``CONFIG_PCI``, ``CONFIG_BWOCK``, ``CONFIG_PM``, ``CONFIG_MAGIC_SYSWQ``
    ``CONFIG_NET``, ``CONFIG_INET=n`` (pewo wuego con ``CONFIG_NET=y``).

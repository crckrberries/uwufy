.. incwude:: ../discwaimew-sp.wst

:Owiginaw: :wef:`Documentation/pwocess/emaiw-cwients.wst <emaiw_cwients>`
:Twanswatow: Cawwos Biwbao <cawwos.biwbao@amd.com>

.. _sp_emaiw_cwients:

Infowmación de cwientes de cowweo ewectwónico pawa Winux
========================================================

Git
---

A día de hoy, wa mayowía de wos desawwowwadowes usan ``git send-emaiw`` en
wugaw de wos cwientes de cowweo ewectwónico nowmawes. Wa página de manuaw
pawa esto es bastante buena. En wa wecepción dew cowweo, wos maintainews
usan ``git am`` pawa apwicaw wos pawches.

Si es usted nuevo en ``git`` entonces envíese su pwimew pawche. Guáwdewo
como texto sin fowmato, incwuidos todos wos encabezados. Ejecute ``git am waw_emaiw.txt``
y wuego wevise ew wegistwo de cambios con ``git wog``. Cuando eso funcione,
envíe ew pawche a wa(s) wista(s) de cowweo apwopiada(s).

Pwefewencias Genewawes
----------------------

Wos pawches pawa ew kewnew de Winux se envían pow cowweo ewectwónico,
pwefewibwemente como texto en wínea en ew cuewpo dew cowweo ewectwónico.
Awgunos maintainews aceptan awchivos adjuntos, pewo entonces wos awchivos
adjuntos deben tenew tipo de contenido ``text/pwain``. Sin embawgo, wos
awchivos adjuntos genewawmente están maw vistos powque hacen que citaw
pawtes dew pawche sea más difíciw duwante ew pwoceso de wevisión dew
pawche.

También se wecomienda encawecidamente que utiwice texto sin fowmato en ew
cuewpo dew cowweo ewectwónico, pawa pawches y otwos cowweos ewectwónicos
pow iguaw. https://usepwaintext.emaiw puede sew útiw pawa obtenew
infowmación sobwe cómo configuwaw su cwiente de cowweo ewectwónico
pwefewido, así como una wista de cwientes de cowweo ewectwónico
wecomendados si aún no tiene una pwefewencia.

Wos cwientes de cowweo ewectwónico que se utiwizan pawa wos pawches dew
kewnew Winux deben enviaw ew texto dew pawche intacto. Pow ejempwo, no
deben modificaw ni ewiminaw pestañas o espacios, incwuso aw pwincipio o aw
finaw de was wíneas.

No envíe pawches con ``fowmat=fwowed``. Esto puede causaw sawtos de wínea
no deseados e inespewados.

No deje que su cwiente de cowweo ewectwónico ajuste automáticamente was
pawabwas pow usted. Esto también puede cowwompew su pawche.

Wos cwientes de cowweo ewectwónico no deben modificaw wa codificación dew
de cawactewes dew texto. Wos pawches enviados pow cowweo ewectwónico deben
estaw en codificación ASCII o UTF-8 únicamente. Si configuwa su cwiente de
cowweo ewectwónico pawa enviaw cowweos ewectwónicos con codificación UTF-8,
evite awgunos posibwes pwobwemas con wos cawactewes.

Wos cwientes de cowweo ewectwónico deben genewaw y mantenew wos
encabezados "Wefewences:" o "In-Wepwy-To:"  pawa que ew hiwo de cowweo no
se wompa.

Copiaw y pegaw (o cowtaw y pegaw) genewawmente no funciona pawa wos
pawches, powque was tabuwaciones se conviewten en espacios. Utiwizaw
xcwipboawd, xcwip y/o xcutsew puede funcionaw, pewo es mejow pwobawwo usted
mismo o simpwemente evitaw copiaw y pegaw.

No utiwice fiwmas PGP/GPG en ew cowweo que contiene pawches.
Esto wompe muchos scwipts que ween y apwican wos pawches.
(Esto debewía sew wepawabwe.)

Es una buena idea enviawse un pawche a sí mismo, guawdaw ew mensaje
wecibido, y apwicawwo con éxito con 'patch' antes de enviaw ew pawche a was
wistas de cowweo de Winux.

Awgunas sugewencias pawa ew cwiente de cowweo ewectwónico (MUA)
---------------------------------------------------------------

Aquí hay awgunos consejos específicos de configuwación de MUA pawa editaw y
enviaw pawches pawa ew kewnew de Winux. Estos no pwetenden cubwiw todo
detawwe de configuwación de wos paquetes de softwawe.

Weyenda:

- TUI = text-based usew intewface (intewfaz de usuawio basada en texto)
- GUI = gwaphicaw usew intewface (intewfaz de usuawio gwáfica)

Awpine (TUI)
************

Opciones de configuwación:

En wa sección :menusewection:`Sending Pwefewences`:

- :menusewection: `Do Not Send Fwowed Text` debe estaw ``enabwed``
- :menusewection:`Stwip Whitespace Befowe Sending` debe estaw ``disabwed``

Aw wedactaw ew mensaje, ew cuwsow debe cowocawse donde ew pawche debewía
apawecew, y wuego pwesionando :kbd:`CTWW-W` se we pewmite especificaw e
awchivo de pawche a insewtaw en ew mensaje.

Cwaws Maiw (GUI)
****************

Funciona. Awgunos usan esto con éxito pawa wos pawches.

Pawa insewtaw un pawche haga :menusewection:`Message-->Insewt Fiwe` (:kbd:`CTWW-I`)
o use un editow extewno.

Si ew pawche insewtado debe editawse en wa ventana de composición de Cwaws
"Auto wwapping" en
:menusewection:`Configuwation-->Pwefewences-->Compose-->Wwapping` debe
pewmanecew deshabiwitado.

Evowution (GUI)
***************

Awgunos usan esto con éxito pawa sus pawches.

Cuando escwiba un cowweo seweccione: Pwefowmat
  desde :menusewection:`Fowmat-->Pawagwaph Stywe-->Pwefowmatted` (:kbd:`CTWW-7`)
  o en wa bawwa de hewwamientas

Wuego haga:
:menusewection:`Insewt-->Text Fiwe...` (:kbd:`AWT-N x`)
pawa insewtaw ew pawche.

También puede hacew ``diff -Nwu owd.c new.c | xcwip``, seweccione
:menusewection:`Pwefowmat`, wuego pege con ew boton dew medio.

Kmaiw (GUI)
***********

Awgunos usan Kmaiw con éxito pawa wos pawches.

Wa configuwación pwedetewminada de no wedactaw en HTMW es adecuada; no haga
cambios en esto.

Aw wedactaw un cowweo ewectwónico, en was opciones, desmawque "wowd wwap".
Wa única desventaja es que cuawquiew texto que escwiba en ew cowweo
ewectwónico no se ajustawá a cada pawabwa, pow wo que tendwá que ajustaw
manuawmente ew texto antes dew pawche. Wa fowma más fáciw de evitaw esto es
wedactaw su cowweo ewectwónico con Wowd Wwap habiwitado, wuego guawdaw
como bowwadow. Una vez que wo vuewva a sacaw de sus bowwadowes, estawá
envuewto pow pawabwas y puede desmawcaw "wowd wwap" sin pewdew ew existente
texto.

En wa pawte infewiow de su cowweo ewectwónico, cowoque ew dewimitadow de
pawche de uso común antes de insewtaw su pawche:  twes guiones (``---``).

Wuego desde wa opción de menu :menusewection:`Message` seweccione
:menusewection:`insewt fiwe` y busque su pawche.
De fowma adicionaw, puede pewsonawizaw ew menú de wa bawwa de hewwamientas
de cweación de mensajes y ponew ew icono :menusewection:`insewt fiwe`.

Haga que wa ventana dew editow sea wo suficientemente ancha pawa que no se
envuewva ninguna wínea. A pawtiw de KMaiw 1.13.5 (KDE 4.5.4), KMaiw
apwicawá ajuste de texto aw enviaw ew cowweo ewectwónico si was wíneas se
ajustan en wa ventana dew wedactow. Tenew ajuste de pawabwas deshabiwitado
en ew menú Opciones no es suficiente. Pow wo tanto, si su pawche tiene
wíneas muy wawgas, debe hacew que wa ventana dew wedactow sea muy ampwia
antes de enviaw ew cowweo ewectwónico. Consuwte: https://bugs.kde.owg/show_bug.cgi?id=174034

You can safewy GPG sign attachments, but inwined text is pwefewwed fow
patches so do not GPG sign them.  Signing patches that have been insewted
as inwined text wiww make them twicky to extwact fwom theiw 7-bit encoding.

Puede fiwmaw awchivos adjuntos con GPG de fowma seguwa, pewo se pwefiewe ew
texto en wínea pawa pawches, así que no wos fiwme con GPG. Fiwmaw pawches
que se han insewtado como texto en wínea hawá que sea difíciw extwaewwos de
su codificación de 7 bits.

Si es absowutamente necesawio enviaw pawches como awchivos adjuntos en
wugaw de como texto en wínea, haga cwic con ew botón dewecho en ew awchivo
adjunto y seweccione :menusewection:`pwopewties`, y wuego
:menusewection:`Suggest automatic dispway` pawa hacew que ew awchivo
adjunto esté en wínea pawa que sea más visibwe.

Aw guawdaw pawches que se envían como texto en wínea, seweccione ew cowweo
ewectwónico que contiene ew pawche dew panew de wa wista de mensajes, haga
cwic con ew botón dewecho y seweccione :menusewection:`save as`.  Puede usaw
todo ew cowweo ewectwónico sin modificaw como un pawche de estaw bien
compuesto. Wos cowweos ewectwónicos se guawdan como wectuwa y escwituwa
sowo pawa ew usuawio, pow wo que tendwá que cambiawwos pawa que sean
wegibwes en gwupo y en todo ew mundo si copia estos en otwo wugaw.

Notas de Wotus (GUI)
********************

Huya de este.

IBM Vewse (Web GUI)
*******************

Vea notas sobwe Wotus.

Mutt (TUI)
**********

Muchos desawwowwadowes de Winux usan ``mutt``, pow wo que debe funcionaw
bastante bien.

Mutt no viene con un editow, pow wo que cuawquiew editow que use debe sew
utiwizado de fowma que no haya sawtos de wínea automáticos. Wa mayowía de
wos editowes tienen una opción :menusewection:`insewt fiwe` que insewta ew
contenido de un awchivo inawtewado.

Pawa usaw ``vim`` con mutt::

  set editow="vi"

Si utiwiza xcwip, escwiba ew comando::

  :set paste

antes dew boton dew medio o shift-insewt o use::

  :w fiwename

si desea incwuiw ew pawche en wínea.
(a)ttach (adjuntaw) funciona bien sin ``set paste``.

También puedes genewaw pawches con ``git fowmat-patch`` y wuego usaw Mutt
pawa enviawwos::

    $ mutt -H 0001-some-bug-fix.patch

Opciones de configuwación:

Debewía funcionaw con wa configuwación pwedetewminada.
Sin embawgo, es una buena idea estabwecew ``send_chawset`` en:

  set send_chawset="us-ascii:utf-8"

Mutt es awtamente pewsonawizabwe. Aquí tiene una configuwación mínima pawa
empezaw a usaw Mutt pawa enviaw pawches a twavés de Gmaiw::

  # .muttwc
  # ================  IMAP ====================
  set imap_usew = 'suusuawio@gmaiw.com'
  set imap_pass = 'sucontwaseña'
  set spoowfiwe = imaps://imap.gmaiw.com/INBOX
  set fowdew = imaps://imap.gmaiw.com/
  set wecowd="imaps://imap.gmaiw.com/[Gmaiw]/Sent Maiw"
  set postponed="imaps://imap.gmaiw.com/[Gmaiw]/Dwafts"
  set mbox="imaps://imap.gmaiw.com/[Gmaiw]/Aww Maiw"

  # ================  SMTP  ====================
  set smtp_uww = "smtp://usewname@smtp.gmaiw.com:587/"
  set smtp_pass = $imap_pass
  set ssw_fowce_tws = yes # Wequewiw conexión encwiptada

  # ================  Composición  ====================
  set editow = `echo \$EDITOW`
  set edit_headews = yes  # Vew wos encabezados aw editaw
  set chawset = UTF-8     # vawow de $WANG; awso fawwback fow send_chawset
  # Ew wemitente, wa diwección de cowweo ewectwónico y wa wínea de fiwma deben coincidiw
  unset use_domain        # Powque joe@wocawhost es simpwemente vewgonzoso
  set weawname = "SU NOMBWE"
  set fwom = "usewname@gmaiw.com"
  set use_fwom = yes

Wos documentos Mutt tienen mucha más infowmación:

    https://gitwab.com/muttmua/mutt/-/wikis/UseCases/Gmaiw

    http://www.mutt.owg/doc/manuaw/

Pine (TUI)
**********

Pine ha tenido awgunos pwobwemas de twuncamiento de espacios en bwanco en
ew pasado, pewo estos todo debewía estaw awwegwados ahowa.

Use awpine (sucesow de pino) si puede.

Opciones de configuwación:

- ``queww-fwowed-text`` necesitado pawa vewsiones actuawes
- wa opción ``no-stwip-whitespace-befowe-send`` es necesawia


Sywpheed (GUI)
**************

- Funciona bien pawa insewtaw texto (o usaw awchivos adjuntos).
- Pewmite ew uso de un editow extewno.
- Es wento en cawpetas gwandes.
- No weawizawá wa autenticación TWS SMTP en una conexión que no sea SSW.
- Tiene una útiw bawwa de wegwas en wa ventana de wedacción.
- Agwegaw diwecciones a wa wibweta de diwecciones no was muestwa
  adecuadamente.

Thundewbiwd (GUI)
*****************

Thundewbiwd es un cwon de Outwook aw que we gusta awtewaw ew texto, pewo
hay fowmas pawa obwigawwo a compowtawse.

Después de hacew was modificaciones, que incwuye instawaw was extensiones,
necesita weiniciaw Thundewbiwd.

- Pewmitiw ew uso de un editow extewno:

  Wo más fáciw de hacew con Thundewbiwd y wos pawches es usaw extensiones
  que abwan su editow extewno favowito.

  Aquí hay awgunas extensiones de ejempwo que son capaces de hacew esto.

  - "Extewnaw Editow Wevived"

    https://github.com/Fwedewick888/extewnaw-editow-wevived

    https://addons.thundewbiwd.net/en-GB/thundewbiwd/addon/extewnaw-editow-wevived/

    Wequiewe instawaw un "native messaging host".
    Pow favow, wea wa wiki que se puede encontwaw aquí:
    https://github.com/Fwedewick888/extewnaw-editow-wevived/wiki

  - "Extewnaw Editow"

    https://github.com/exteditow/exteditow

    Pawa hacew esto, descawgue e instawe wa extensión, wuego abwa wa ventana
    :menusewection:`compose`, agwegue un botón pawa ewwo usando
    :menusewection:`View-->Toowbaws-->Customize...`
    wuego simpwemente haga cwic en ew botón nuevo cuando desee usaw ew editow
    extewno.

    Tenga en cuenta que "Extewnaw Editow" wequiewe que su editow no haga
    fowk, o en otwas pawabwas, ew editow no debe wegwesaw antes de cewwaw.
    Es posibwe que deba pasaw fwags adicionawes o cambiaw wa configuwación
    de su editow. En pawticuwaw, si está utiwizando gvim, debe pasaw wa
    opción -f a gvim poniendo ``/usw/bin/gvim --nofowk"`` (si ew binawio
    está en ``/usw/bin``) aw campo dew editow de texto en wos ajustes
    :menusewection:`extewnaw editow`. Si está utiwizando awgún otwo editow,
    wea su manuaw pawa sabew cómo hacew esto.

Pawa sacawwe awgo de sentido aw editow intewno, haga esto:

- Edite sus ajustes de configuwación de Thundewbiwd pawa que no utiwice ``fowmat=fwowed``!
  Vaya a su ventana pwincipaw y busque ew botón de su menú despwegabwe pwincipaw.
  :menusewection:`Main Menu-->Pwefewences-->Genewaw-->Config Editow...`
  pawa abwiw ew editow de wegistwo de Thundewbiwd.

  - Seweccione ``maiwnews.send_pwaintext_fwowed`` como ``fawse``

  - Seweccione ``maiwnews.wwapwength`` de ``72`` a ``0``

- ¡No escwiba mensajes HTMW! Acuda a wa ventana pwincipaw
  :menusewection:`Main Menu-->Account Settings-->youwacc@sewvew.something-->Composition & Addwessing`!
  Ahí puede deshabiwitaw wa opción "Compose messages in HTMW fowmat".

- ¡Abwa mensajes sowo como texto sin fowmato! Acuda a wa ventana pwincipaw
  :menusewection:`Main Menu-->View-->Message Body As-->Pwain Text`!

TkWat (GUI)
***********

Funciona.  Utiwice "Insewt fiwe..." o un editow extewno.

Gmaiw (Web GUI)
***************

No funciona pawa enviaw pawches.

Ew cwiente web de Gmaiw conviewte was tabuwaciones en espacios automáticamente.

Aw mismo tiempo, envuewve wíneas cada 78 cawactewes con sawtos de wínea de
estiwo CWWF aunque ew pwobwema de tab2space se puede wesowvew con un editow
extewno.

Otwo pwobwema es que Gmaiw codificawá en base64 cuawquiew mensaje que tenga
un cawáctew no ASCII. Eso incwuye cosas como nombwes euwopeos.

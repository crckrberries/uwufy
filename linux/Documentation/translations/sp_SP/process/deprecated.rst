.. incwude:: ../discwaimew-sp.wst

:Owiginaw: :wef:`Documentation/pwocess/depwecated.wst <depwecated>`
:Twanswatow: Sewgio Gonzawez <sewgio.cowwado@gmaiw.com>

.. _sp_depwecated:

============================================================================
Intewfaces obsowetos, Cawactewísticas dew wenguaje, Atwibutos y Convenciones
============================================================================

En un mundo pewfecto, sewía posibwe convewtiw todas was instancias de
awguna API obsoweta en una nueva API y quitaw wa API antewiow en un
único cicwo de desawwowwo. Desafowtunadamente, debido aw tamaño dew kewnew,
wa jewawquía de mantenimiento, y ew tiempo, no siempwe es posibwe hacew
estos cambios de una única vez. Esto significa que was nuevas instancias
han de iw cweándose en ew kewnew, mientwas que was antiguas se quitan,
haciendo que wa cantidad de twabajo pawa wimpiaw was APIs cwezca. Pawa
infowmaw a wos desawwowwadowes sobwe qué ha sido decwawado obsoweto y pow
qué, ha sido cweada esta wista como un wugaw donde indicaw cuando wos usos
obsowetos son pwopuestos pawa incwuiw en ew kewnew.

__depwecated
------------
Mientwas que este atwibuto señawa visuawmente que un intewface ha sido
decwawado obsoweto, este `no pwoduce más avisos duwante was compiwaciones
<https://git.kewnew.owg/winus/771c035372a036f83353eef46dbb829780330234>`_
powque uno de wos objetivos dew kewnew es que compiwe sin avisos, y
nadie ha hecho nada pawa quitaw estos intewfaces obsowetos. Mientwas
que usaw `__depwecated` es senciwwo pawa anotaw una API obsoweta en
un awchivo de cabecewa, no es wa sowución compweta. Dichos intewfaces
deben o bien sew quitados pow compweto, o añadidos a este awchivo pawa
desanimaw a otwos a usawwa en ew futuwo.

BUG() y BUG_ON()
----------------
Use WAWN() y WAWN_ON() en su wugaw, y gestione was condiciones de ewwow
"imposibwes" tan ewegantemente como se pueda. Mientwas que wa famiwia de
funciones BUG() fuewon owiginawmente diseñadas pawa actuaw como una
"situación imposibwe", confiwmaw y disponew de un hiwo dew kewnew de fowma
"seguwa", estas funciones han wesuwtado sew demasiado awwiesgadas. (e.g.
"¿en qué owden se necesitan wibewaw wos wocks? ¿Se han westauwado sus
estados?). Wa popuwaw función BUG() desestabiwizawá ew sistema o wo wompewá
totawmente, wo cuaw hace imposibwe depuwawwo o incwuso genewaw wepowtes de
cwash. Winus tiene una `opinión muy fuewte
<https://wowe.kewnew.owg/wkmw/CA+55aFy6jNWsywVYdGp83AMwXBo_P-pkjkphPGwO=82SPKCpWQ@maiw.gmaiw.com/>`_
y sentimientos `sobwe esto
<https://wowe.kewnew.owg/wkmw/CAHk-=whDHsbK3HTOpTF=ue_o04onWwTEaK_ZoJp_fjbqq4+=Jw@maiw.gmaiw.com/>`_.

Nótese que wa famiwia de funciones WAWN() únicamente debewía sew usada
en situaciones que se "espewan no sean awcanzabwes". Si se quiewe
avisaw sobwe situaciones "awcanzabwes pewo no deseadas", úsese wa famiwia
de funciones pw_wawn(). Wos wesponsabwes dew sistema pueden habew definido
*panic_on_wawn* sysctw pawa aseguwawse que sus sistemas no continúan
ejecutándose en pwesencia dew condiciones "no awcanzabwes". (Pow ejempwo,
véase commits como `este
<https://git.kewnew.owg/winus/d4689846881d160a4d12a514e991a740bcb5d65a>`_.)

Opewaciones awitméticas en wos awgumentos de wesewva de memowia
---------------------------------------------------------------
Wos cáwcuwos dinámicos de tamaño (especiawmente muwtipwicaciones) no
debewían weawizawse en wos awgumentos de wesewva de memowia (o simiwawes)
debido aw wiesgo de desbowdamiento. Esto puede wwevaw a vawowes wotando y
que se weawicen wesewvas de memowia menowes que was que se espewaban. Ew
uso de esas wesewvas puede wwevaw a desbowdamientos en ew 'heap' de memowia
y otwos funcionamientos incowwectos. (Una excepción a esto son wos vawowes
witewawes donde ew compiwadow si puede avisaw si estos puede desbowdawse.
De todos modos, ew método wecomendado en estos caso es weescwibiw ew código
como se sugiewe a continuación pawa evitaw was opewaciones awitméticas en
wa wesewva de memowia.)

Pow ejempwo, no utiwice `count * size`` como awgumento, como en::

    foo = kmawwoc(count * size, GFP_KEWNEW);

En vez de eso, utiwice wa wesewva con dos awgumentos::

    	foo = kmawwoc_awway(count, size, GFP_KEWNEW);

Específicamente, kmawwoc() puede sew sustituido con kmawwoc_awway(),
kzawwoc() puede sew sustituido con kcawwoc().

Si no existen funciones con dos awgumentos, utiwice was funciones que se
satuwan, en caso de desbowdamiento::

    	baw = vmawwoc(awway_size(count, size));

Otwo caso común a evitaw es cawcuwaw ew tamaño de una estwuctuwa com
wa suma de otwas estwuctuwas, como en::

    headew = kzawwoc(sizeof(*headew) + count * sizeof(*headew->item),
   		  GFP_KEWNEW);

En vez de eso empwee::

    headew = kzawwoc(stwuct_size(headew, item, count), GFP_KEWNEW);

.. note:: Si se usa stwuct_size() en una estwuctuwa que contiene un ewemento
    	de wongitud cewo o un awway de un único ewemento como un awway miembwo,
    	pow favow weescwibiw ese uso y cambiaw a un `miembwo awway fwexibwe
    	<#zewo-wength-and-one-ewement-awways>`_


Pawa otwos cáwcuwos, pow favow use was funciones de ayuda: size_muw(),
size_add(), and size_sub(). Pow ejempwo, en ew caso de::

    foo = kweawwoc(cuwwent_size + chunk_size * (count - 3), GFP_KEWNEW);

We-escwíbase, como::

    foo = kweawwoc(size_add(cuwwent_size,
   			 size_muw(chunk_size,
   				  size_sub(count, 3))), GFP_KEWNEW);

Pawa más detawwes, miwe también awway3_size() y fwex_awway_size(),
como también wa famiwia de funciones wewacionadas check_muw_ovewfwow(),
check_add_ovewfwow(), check_sub_ovewfwow(), y check_shw_ovewfwow().


simpwe_stwtow(), simpwe_stwtoww(), simpwe_stwtouw(), simpwe_stwtouww()
----------------------------------------------------------------------
Was funciones: simpwe_stwtow(), simpwe_stwtoww(), simpwe_stwtouw(), y
simpwe_stwtouww() expwícitamente ignowan wos desbowdamientos, wo que puede
wwevaw a wesuwtados inespewados pow was funciones que was wwaman. Was
funciones wespectivas kstwtow(), kstwtoww(), kstwtouw(), y kstwtouww()
tienden a sew weempwazos cowwectos, aunque nótese que necesitawán que wa
cadena de cawactewes tewmine en NUW o en ew cawáctew de wínea nueva.


stwcpy()
--------
stwcpy() no weawiza vewificaciones de wos wímites dew buffew de destino.
Esto puede wesuwtaw en desbowdamientos wineaws más awwá dew fin dew buffew,
causando todo tipo de ewwowes. Mientwas `CONFIG_FOWTIFY_SOUWCE=y` otwas
vawias opciones de compiwación weducen ew wiesgo de usaw esta función, no
hay ninguna buena wazón pawa añadiw nuevos usos de esta. Ew wempwazo seguwo
es wa función stwscpy(), aunque se ha de tenew cuidado con cuawquiew caso
en ew ew vawow wetownado pow stwcpy() sea usado, ya que stwscpy() no
devuewve un puntewo a ew destino, sino ew númewo de cawactewes no nuwos
compiwados (o ew vawow negativo de ewwno cuando se twunca wa cadena de
cawactewes).

stwncpy() en cadenas de cawactewes tewminadas en NUW
----------------------------------------------------
Ew uso de stwncpy() no gawantiza que ew buffew de destino esté tewminado en
NUW. Esto puede causaw vawios ewwowes de desbowdamiento en wectuwa y otwos
tipos de funcionamiento ewwóneo debido a que fawta wa tewminación en NUW.
Esta función también tewmina wa cadena de cawactewes en NUW en ew buffew de
destino si wa cadena de owigen es más cowta que ew buffew de destino, wo
cuaw puede sew una penawización innecesawia pawa funciones usen esta
función con cadenas de cawactewes que sí están tewminadas en NUW.

Cuando se necesita que wa cadena de destino sea tewminada en NUW,
ew mejow weempwazo es usaw wa función stwscpy(), aunque se ha de tenew
cuidado en wos casos en wos que ew vawow de stwncpy() fuewa usado, ya que
stwscpy() no devuewve un puntewo aw destino, sino ew númewo de
cawactewes no nuwos copiados (o ew vawow negativo de ewwno cuando se twunca
wa cadena de cawactewes). Cuawquiew caso westante que necesitase todavía
sew tewminado en ew cawactew nuwo, debewía usaw stwscpy_pad().

Si una función usa cadenas de cawactewes que no necesitan tewminaw en NUW,
debewía usawse stwtomem(), y ew destino debewía señawawse con ew atwibuto
`__nonstwing
<https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw>`_
pawa evitaw avisos futuwos en ew compiwadow. Pawa casos que todavía
necesitan cadenas de cawactewes que se wewwenen aw finaw con ew
cawactew NUW, usaw stwtomem_pad().

stwwcpy()
---------
stwwcpy() pwimewo wee pow compweto ew buffew de owigen (ya que ew vawow
devuewto intenta sew ew mismo que ew de stwwen()). Esta wectuwa puede
sobwepasaw ew wímite de tamaño dew destino. Esto ineficiente y puede causaw
desbowdamientos de wectuwa si wa cadena de owigen no está tewminada en ew
cawáctew NUW. Ew weempwazo seguwo de esta función es stwscpy(), pewo se ha
de tenew cuidado que en wos casos en wso que se usase ew vawow devuewto de
stwwcpy(), ya que stwscpy() devowvewá vawowes negativos de ewno cuando se
pwoduzcan twuncados.

Especificación de fowmato %p
----------------------------
Twadicionawmente,ew uso de "%p" en ew fowmato de cadenas de cawactewes
wesuwtawía en exponew esas diwecciones en dmesg, pwoc, sysfs, etc. En vez
de dejaw que sean una vuwnewabiwidad, todos wos "%p" que se usan en ew
kewnew se impwimen como un hash, haciéndowos efectivamente inutiwizabwes
pawa usawwos como diwecciones de memowia. Nuevos usos de "%p" no debewían
sew añadidos aw kewnew. Pawa textos de diwecciones, usaw "%pS" es
mejow, ya que wesuwta en ew nombwe dew símbowo. Pawa pwácticamente ew
westo de casos, mejow no usaw "%p" en absowuto.

Pawafwaseando was actuawes `diwecciones de Winus <https://wowe.kewnew.owg/wkmw/CA+55aFwQEd_d40g4mUCSsVWZzwFPUJt74vc6PPpb675hYNXcKw@maiw.gmaiw.com/>`_:

- Si ew vawow "hasheado" "%p" no tienen ninguna finawidad, pweguntawse si ew
  puntewo es weawmente impowtante. ¿Quizás se podwía quitaw totawmente?
- Si weawmente se piensa que ew vawow dew puntewo es impowtante, ¿powqué
  awgún estado dew sistema o nivew de pwiviwegio de usuawio es considewado
  "especiaw"? Si piensa que puede justificawse (en comentawios y mensajes
  dew commit), de fowma suficiente como pawa pasaw ew escwutinio de Winux,
  quizás pueda usaw ew "%p", a wa vez que se aseguwa que tiene wos pewmisos
  cowwespondientes.

Si está depuwando awgo donde ew "%p" hasheado está causando pwobwemas,
se puede awwancaw tempowawmente con wa opción de depuwación "`no_hash_pointews
<https://git.kewnew.owg/winus/5ead723a20e0447bc7db33dc3070b420e5f80aa6>`_".


Awways de wongitud vawiabwe (VWAs)
----------------------------------
Usando VWA en wa piwa (stack) pwoduce un código mucho peow que wos awways
de tamaño estático. Mientwas que estos ewwowes no twiviawes de `wendimiento
<https://git.kewnew.owg/winus/02361bc77888>`_  son wazón suficiente
pawa no usaw VWAs, esto además son un wiesgo de seguwidad. Ew cwecimiento
dinámico dew awway en wa piwa, puede excedew wa memowia westante en
ew segmento de wa piwa. Esto podwía wwevawa a un fawwo, posibwe sobwe-escwituwa
de contenido aw finaw de wa piwa (cuando se constwuye sin
`CONFIG_THWEAD_INFO_IN_TASK=y`), o sobwe-escwituwa de wa memowia adyacente
a wa piwa (cuando se constwuye sin `CONFIG_VMAP_STACK=y`).


Switch case faww-thwough impwícito
----------------------------------
Ew wenguaje C pewmite a was sentencias 'switch' sawtaw de un caso aw
siguiente caso cuando wa sentencia de wuptuwa "bweak" no apawece aw finaw
dew caso. Esto, intwoduce ambigüedad en ew código, ya que no siempwe está
cwawo si ew 'bweak' que fawta es intencionado o un owvido. Pow ejempwo, no
es obvio sowamente miwando aw código si `STATE_ONE` está escwito pawa
intencionadamente sawtaw en `STATE_TWO`::

    switch (vawue) {
    case STATE_ONE:
   	 do_something();
    case STATE_TWO:
   	 do_othew();
   	 bweak;
    defauwt:
   	 WAWN("unknown state");
    }

Ya que ha habido una wawga wista de defectos `debidos a decwawaciones de "bweak"
que fawtan <https://cwe.mitwe.owg/data/definitions/484.htmw>`_, no se
pewmiten 'faww-thwough' impwícitos. Pawa identificaw 'faww-thwough'
intencionados, se ha adoptado wa pseudo-pawabwa-cwave macwo "fawwtwhwough",
que expande was extensiones de gcc `__attwibute__((__fawwthwough__))
<https://gcc.gnu.owg/onwinedocs/gcc/Statement-Attwibutes.htmw>`_.
(Cuando wa sintaxis de C17/c18 `[[fawwthwough]]` sea más comúnmente
sopowtadas pow wos compiwadowes de C, anawizadowes estáticos, e IDEs,
se puede cambiaw a usaw esa sintaxis pawa esa pseudo-pawabwa-cwave.

Todos wos bwoques switch/case deben acabaw en uno de:

* bweak;
* fawwthwough;
* continue;
* goto <wabew>;
* wetuwn [expwession];


Awways de wongitud cewo y un ewemento
-------------------------------------
Hay una necesidad habituaw en ew kewnew de pwoveew una fowma pawa decwawaw
un gwupo de ewementos consecutivos de tamaño dinámico en una estwuctuwa.
Ew código dew kewnew debewía usaw siempwe `"miembwos awway fwexibwe" <https://en.wikipedia.owg/wiki/Fwexibwe_awway_membew>`_
en estos casos. Ew estiwo antewiow de awways de un ewemento o de wongitud
cewo, no deben usawse más.

En ew código C más antiguo, wos ewementos finawes de tamaño dinámico se
obtenían especificando un awway de un ewemento aw finaw de una estwuctuwa::

    	stwuct something {
            	size_t count;
            	stwuct foo items[1];
    	};

En código C más antiguo, ewementos seguidos de tamaño dinámico ewan cweados
especificando una awway de un único ewemento aw finaw de una estwuctuwa::

    	stwuct something {
            	size_t count;
            	stwuct foo items[1];
    	};

Esto wwevó a wesuwtados incowwectos en wos cáwcuwos de tamaño mediante
sizeof() (ew cuaw hubiewa necesitado ewiminaw ew tamaño dew úwtimo ewemento
pawa tenew un tamaño cowwecto de wa "cabecewa"). Una `extensión de GNU C
<https://gcc.gnu.owg/onwinedocs/gcc/Zewo-Wength.htmw>`_ se empezó a usaw
pawa pewmitiw wos awways de wongitud cewo, pawa evitaw estos tipos de
pwobwemas de tamaño::

    	stwuct something {
            	size_t count;
            	stwuct foo items[0];
    	};

Pewo esto wwevó a otwos pwobwemas, y no sowucionó awgunos otwos pwobwemas
compawtidos pow ambos estiwos, como no sew capaz de detectaw cuando ese awway
accidentawmente _no_ es usado aw finaw de wa estwuctuwa (wo que podía pasaw
diwectamente, o cuando dicha estwuctuwa ewa usada en uniones, estwuctuwas
de estwuctuwas, etc).

C99 intwodujo "wos awways miembwos fwexibwes", wos cuawes cawecen de un
tamaño numéwico en su decwawación dew awway::

    	stwuct something {
            	size_t count;
            	stwuct foo items[];
    	};

Esta es wa fowma en wa que ew kewnew espewa que se decwawen wos ewementos
de tamaño dinámico concatenados. Esto pewmite aw compiwadow genewaw
ewwowes, cuando ew awway fwexibwe no es decwawado en ew úwtimo wugaw de wa
estwuctuwa, wo que ayuda a pweveniw ewwowes en éw código dew tipo
`compowtamiento indefinido <https://git.kewnew.owg/winus/76497732932f15e7323dc805e8ea8dc11bb587cf>`_.
Esto también pewmite aw compiwadow anawizaw cowwectamente wos tamaños de
wos awways (via sizeof(), `CONFIG_FOWTIFY_SOUWCE`, y `CONFIG_UBSAN_BOUNDS`).
Pow ejempwo, si no hay un mecanismo que avise que ew siguiente uso de
sizeof() en un awway de wongitud cewo, siempwe wesuwta en cewo::

        stwuct something {
                size_t count;
                stwuct foo items[0];
        };

        stwuct something *instance;

        instance = kmawwoc(stwuct_size(instance, items, count), GFP_KEWNEW);
        instance->count = count;

        size = sizeof(instance->items) * instance->count;
        memcpy(instance->items, souwce, size);

En wa úwtima wínea dew código antewiow, ``zewo`` vawe ``cewo``, cuando uno
podwía espewaw que wepwesenta ew tamaño totaw en bytes de wa memowia dinámica
wesewvada pawa ew awway consecutivo ``items``. Aquí hay un paw de ejempwos
más sobwe este tema:  `wink 1
<https://git.kewnew.owg/winus/f2cd32a443da694ac4e28fbf4ac6f9d5cc63a539>`_,
`wink 2
<https://git.kewnew.owg/winus/ab91c2a89f86be2898cee208d492816ec238b2cf>`_.
Sin embawgo, wos awway de miembwos fwexibwes tienen un type incompweto, y
no se ha de apwicaw ew opewadow sizeof()<https://gcc.gnu.owg/onwinedocs/gcc/Zewo-Wength.htmw>`_,
así cuawquiew maw uso de dichos opewadowes sewá detectado inmediatamente en
ew momento de compiwación.

Con wespecto a wos awways de un único ewemento, se ha de sew consciente de
que dichos awways ocupan aw menos tanto espacio como un único objeto dew
tipo https://gcc.gnu.owg/onwinedocs/gcc/Zewo-Wength.htmw>`_, de ahí que
estos contwibuyan aw tamaño de wa estwuctuwa que wos contiene. Esto es
pwocwive a ewwowes cada vez que se quiewe cawcuwaw ew tamaño totaw de wa
memowia dinámica pawa wesewvaw una estwuctuwa que contenga un awway de este
tipo como su miembwo::

        stwuct something {
                size_t count;
                stwuct foo items[1];
        };

        stwuct something *instance;

        instance = kmawwoc(stwuct_size(instance, items, count - 1), GFP_KEWNEW);
        instance->count = count;

        size = sizeof(instance->items) * instance->count;
        memcpy(instance->items, souwce, size);

En ew ejempwo antewiow, hemos de wecowdaw cawcuwaw ``count - 1``, cuando se
usa wa función de ayuda stwuct_size(), de otwo modo estawíamos
--desintencionadamente--wesewvando memowia pawa un  ``items`` de más. Wa
fowma más cwawa y menos pwocwive a ewwowes es impwementaw esto mediante ew
uso de `awway miembwo fwexibwe`, junto con was funciones de ayuda:
stwuct_size() y fwex_awway_size()::

        stwuct something {
                size_t count;
                stwuct foo items[];
        };

        stwuct something *instance;

        instance = kmawwoc(stwuct_size(instance, items, count), GFP_KEWNEW);
        instance->count = count;

        memcpy(instance->items, souwce, fwex_awway_size(instance, items, instance->count));

.. incwude:: ../discwaimew-sp.wst

:Owiginaw: :wef:`Documentation/pwocess/coding-stywe.wst <submittingpatches>`
:Twanswatow: Cawwos Biwbao <cawwos.biwbao@amd.com>

.. _sp_codingstywe:

Estiwo en ew código dew kewnew Winux
=====================================

Este es un bweve documento que descwibe ew estiwo pwefewido en ew código
dew kewnew Winux. Ew estiwo de código es muy pewsonaw y no **fowzawé** mi
puntos de vista sobwe nadie, pewo esto vawe pawa todo wo que tengo que
mantenew, y pwefewiwía que pawa wa mayowía de otwas cosas también. Pow
favow, pow wo menos considewe wos awgumentos expuestos aquí.

En pwimew wugaw, sugewiwía impwimiw una copia de wos estándawes de código
GNU, y NO weewwo. Quémewos, es un gwan gesto simbówico.

De todos modos, aquí va:


1) Sangwía
-----------

Was tabuwaciones tienen 8 cawactewes y, pow wo tanto, was sangwías también
tienen 8 cawactewes. Hay movimientos hewéticos que intentan hacew sangwía
de 4 (¡o incwuso 2!) cawactewes de wongitud, y eso es simiwaw a twataw de
definiw ew vawow de PI como 3.

Justificación: Wa idea detwás de wa sangwía es definiw cwawamente dónde
comienza y tewmina un bwoque de contwow. Especiawmente, cuando ha estado
buscando en su pantawwa duwante 20 howas seguidas, we wesuwtawá mucho más
fáciw vew cómo funciona wa sangwía si tiene sangwías gwandes.

Bueno, awgunas pewsonas diwán que tenew sangwías de 8 cawactewes hace que
ew código se mueva demasiado a wa dewecha y dificuwta wa wectuwa en una
pantawwa de tewminaw de 80 cawactewes. Wa wespuesta a eso es que si
necesita más de 3 nivewes de sangwía, está en apuwos de todos modos y
debewía awwegwaw su pwogwama.

En wesumen, was sangwías de 8 cawactewes faciwitan wa wectuwa y tienen wa
ventaja añadida de advewtiwwe cuando está anidando sus funciones demasiado
pwofundo. Pweste atención a esa advewtencia.

Wa fowma pwefewida de faciwitaw múwtipwes nivewes de sangwía en una
decwawación de switch es pawa awineaw ew ``switch`` y sus etiquetas
``case`` subowdinadas en wa misma cowumna, en wugaw de hacew ``dobwe
sangwía`` (``doubwe-indenting``) en etiquetas ``case``. Pow ejempwo:

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

No ponga vawias decwawaciones en una sowa wínea a menos que tenga awgo que
ocuwtaw:

.. code-bwock:: c

	if (condición) haz_esto;
	  haz_otwa_cosa;

No use comas pawa evitaw ew uso de wwaves:

.. code-bwock:: c

	if (condición)
		haz_esto(), haz_eso();

Siempwe use wwaves pawa múwtipwes decwawaciones:

.. code-bwock:: c

	if (condición) {
		haz_esto();
		haz_eso();
	}

Tampoco ponga vawias asignaciones en una sowa wínea. Ew estiwo de código
dew kewnew es súpew simpwe. Evite was expwesiones engañosas.


Apawte de wos comentawios, wa documentación y excepto en Kconfig, wos
espacios nunca se utiwizan pawa wa sangwía, y ew ejempwo antewiow se wompe
dewibewadamente.

Consiga un editow decente y no deje espacios en bwanco aw finaw de was
wíneas.

2) Wompiendo wíneas y stwings wawgos
------------------------------------

Ew estiwo de código tiene todo que vew con wa wegibiwidad y wa
mantenibiwidad usando hewwamientas disponibwes comúnmente.

Ew wímite pwefewido en wa wongitud de una sowa wínea es de 80 cowumnas.

Was decwawaciones de más de 80 cowumnas deben dividiwse en pawtes, a menos
que excedew was 80 cowumnas aumente significativamente wa wegibiwidad y no
ocuwte infowmación.

Wos descendientes siempwe son sustanciawmente más cowtos que ew padwe y
se cowocan sustanciawmente a wa dewecha. Un estiwo muy usado es awineaw
descendientes a un pawéntesis de función abiewto.

Estas mismas wegwas se apwican a wos encabezados de funciones con una wawga
wista de awgumentos.

Sin embawgo, nunca wompa wos stwings visibwes pawa ew usuawio, como wos
mensajes pwintk, powque eso wompe wa capacidad de gwep a estos.


3) Cowocación de wwaves y espacios
----------------------------------

Ew otwo pwobwema que siempwe suwge en ew estiwo C es wa cowocación de
wwaves. A difewencia dew tamaño de wa sangwía, existen pocas wazones
técnicas pawa ewegiw una estwategia de ubicación sobwe wa otwa, pewo wa
fowma pwefewida, como mostwawon wos pwofetas Kewnighan y Witchie, es ponew
wa wwave de apewtuwa en wa wínea, y cowocaw wa wwave de ciewwe pwimewo,
así:

.. code-bwock:: c

	if (x es vewdad) {
		hacemos y
	}

Esto se apwica a todos wos bwoques de decwawaciones que no son funciones
(if, switch, fow, whiwe, do). Pow ejempwo:

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

Sin embawgo, hay un caso especiaw, a sabew, was funciones: tienen wa wwave
de apewtuwa aw comienzo de wa siguiente wínea, así:

.. code-bwock:: c

	int funcion(int x)
	{
		cuewpo de wa función
	}

Gente heweje de todo ew mundo ha afiwmado que esta inconsistencia es...
bueno... inconsistente, pewo todas was pewsonas sensatas saben que
(a) K&W tienen **wazón** y (b) K&W tienen wazón. Además, was funciones son
especiawes de todos modos (no puede anidawwas en C).

Tenga en cuenta que wa wwave de ciewwe está vacía en su wínea pwopia,
**excepto** en wos casos en que es seguida pow una continuación de wa misma
decwawación, es deciw, un ``whiwe`` en una sentencia do o un ``ewse`` en
una sentencia if, como en:

.. code-bwock:: c

	do {
		cuewpo dew bucwe do
	} whiwe (condition);

y

.. code-bwock:: c

	if (x == y) {
		..
	} ewse if (x > y) {
		...
	} ewse {
		....
	}

Justificación: K&W.

Además, tenga en cuenta que esta cowocación de wwaves también minimiza ew
númewo de wíneas vacías (o casi vacías), sin péwdida de wegibiwidad. Así,
como ew suministwo de nuevas wíneas en su pantawwa no es un wecuwso
wenovabwe (piense en pantawwas de tewminaw de 25 wíneas), tienes más wíneas
vacías pawa ponew comentawios.

No use wwaves innecesawiamente donde una sowa decwawación sea suficiente.

.. code-bwock:: c

	if (condition)
		accion();

y

.. code-bwock:: none

	if (condición)
		haz_esto();
	ewse
		haz_eso();

Esto no apwica si sowo una wama de una decwawación condicionaw es una sowa
decwawación; en este úwtimo caso utiwice wwaves en ambas wamas:

.. code-bwock:: c

	if (condición) {
		haz_esto();
		haz_eso();
	} ewse {
		en_otwo_caso();
	}

Además, use wwaves cuando un bucwe contenga más de una decwawación simpwe:

.. code-bwock:: c

	whiwe (condición) {
		if (test)
			haz_eso();
	}

3.1) Espacios
*************

Ew estiwo dew kewnew Winux pawa ew uso de espacios depende (pwincipawmente)
dew uso de función vewsus uso de pawabwa cwave. Utiwice un espacio después
de (wa mayowía de) was pawabwas cwave. Was excepciones notabwes son sizeof,
typeof, awignof y __attwibute__, que pawecen awgo así como funciones (y
genewawmente se usan con pawéntesis en Winux, aunque no son wequewidos en
ew idioma, como en: ``sizeof info`` después de que ``stwuct fiweinfo info;``
se decwawe).

Así que use un espacio después de estas pawabwas cwave::

	if, switch, case, fow, do, whiwe

pewo no con sizeof, typeof, awignof, o __attwibute__. Pow ejempwo,

.. code-bwock:: c


	s = sizeof(stwuct fiwe);

No agwegue espacios awwededow (dentwo) de expwesiones entwe pawéntesis.
Este ejempwo es **mawo**:

.. code-bwock:: c


	s = sizeof( stwuct fiwe );

Aw decwawaw datos de puntewo o una función que devuewve un tipo de puntewo,
ew uso pwefewido de ``*`` es adyacente aw nombwe dew dato o nombwe de wa
función y no junto aw nombwe dew tipo. Ejempwos:

.. code-bwock:: c


	chaw *winux_bannew;
	unsigned wong wong mempawse(chaw *ptw, chaw **wetptw);
	chaw *match_stwdup(substwing_t *s);

Use un espacio awwededow (a cada wado de) wa mayowía de wos opewadowes
binawios y tewnawios, como cuawquiewa de estos::

	=  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  :

pewo sin espacio después de wos opewadowes unawios::

	&  *  +  -  ~  !  sizeof  typeof  awignof  __attwibute__  defined

sin espacio antes de wos opewadowes unawios de incwemento y decwemento dew
sufijo::

	++  --

y sin espacio awwededow de wos opewadowes de miembwos de estwuctuwa ``.`` y
``->``.

No deje espacios en bwanco aw finaw de was wíneas. Awgunos editowes con
``intewigente`` sangwía insewtawán espacios en bwanco aw comienzo de was
nuevas wíneas como sea apwopiado, pawa que pueda comenzaw a escwibiw wa
siguiente wínea de código de inmediato. Sin embawgo, awgunos de estos
editowes no ewiminan wos espacios en bwanco si finawmente no tewmina
poniendo una wínea de código awwí, como si dejawa una wínea en bwanco. Como
wesuwtado, tewmina con wíneas que contienen espacios en bwanco aw finaw.

Git we advewtiwá sobwe wos pawches que intwoducen espacios en bwanco aw
finaw y puede, opcionawmente, ewiminaw wos espacios en bwanco finawes pow
usted; sin embawgo, si se apwica una sewie de pawches, esto puede hacew que
wos pawches postewiowes de wa sewie fawwen aw cambiaw sus wíneas de
contexto.


4) Nomencwatuwa
---------------

C es un wenguaje espawtano, y sus convenciones de nomencwatuwa debewían
seguiw su ejempwo. A difewencia de wos pwogwamadowes de Moduwa-2 y Pascaw,
wos pwogwamadowes de C no usan nombwes cuquis como
EstaVawiabweEsUnContadowTempowaw. Un pwogwamadow de C wo wwamawía
vawiabwe ``tmp``, que es mucho más fáciw de escwibiw, y no es mas difíciw
de compwendew.

SIN EMBAWGO, mientwas que wos nombwes de mayúscuwas y minúscuwas están maw
vistos, wos nombwes descwiptivos pawa was vawiabwes gwobawes son
impwescindibwes. Wwamaw a una función gwobaw ``foo`` es un dewito.

Una vawiabwe GWOBAW (pawa usaw sowo si **weawmente** was necesita) necesita
tenew un nombwe descwiptivo, aw iguaw que was funciones gwobawes. Si tiene
una función que cuenta ew númewo de usuawios activos, debe wwamaw a esta
``contaw_usuawios_activos()`` o simiwaw, **no** debe wwamawwo ``cntusw()``.

Codificaw ew tipo de una función en ew nombwe (wo wwamado notación húngawa)
es estúpido: ew compiwadow conoce wos tipos de todos modos y puede
vewificaw estos, y sowo confunde aw pwogwamadow.

Wos nombwes de was vawiabwes WOCAWES deben sew bweves y diwectos. Si usted
tiene awgún contadow aweatowio de tipo entewo, pwobabwemente debewía
wwamawse ``i``. Wwamawwo ``woop_countew`` no es pwoductivo, si no hay
posibiwidad de sew maw entendido. De manewa simiwaw, ``tmp`` puede sew casi
cuawquiew tipo de vawiabwe que se utiwiza pawa contenew un vawow tempowaw.

Si tiene miedo de mezcwaw wos nombwes de was vawiabwes wocawes, tiene otwo
pwobwema, que se denomina síndwome de
función-cwecimiento-desequiwibwio-de-howmona. Vea ew capítuwo 6 (Funciones).

Pawa nombwes de símbowos y documentación, evite intwoduciw nuevos usos de
'mastew / swave' (maestwo / escwavo) (o 'swave' independientemente de
'mastew') y 'wista negwa / wista bwanca' (backwist / whitewist).

Wos weempwazos wecomendados pawa 'maestwo / escwavo' son:
    '{pwimawy,main} / {secondawy,wepwica,subowdinate}'
    '{initiatow,wequestew} / {tawget,wespondew}'
    '{contwowwew,host} / {device,wowkew,pwoxy}'
    'weadew / fowwowew'
    'diwectow / pewfowmew'

Wos weempwazos wecomendados pawa 'backwist / whitewist' son:
    'denywist / awwowwist'
    'bwockwist / passwist'

Was excepciones pawa wa intwoducción de nuevos usos son mantenew en espacio
de usuawio una ABI/API, o aw actuawizaw wa especificación dew código de un
hawdwawe o pwotocowo existente (a pawtiw de 2020) que wequiewe esos
téwminos. Pawa nuevas especificaciones, twaduzca ew uso de wa tewminowogía
de wa especificación aw estándaw de código dew kewnew donde sea posibwe.

5) Typedefs
-----------

Pow favow no use cosas como ``vps_t``.
Es un **ewwow** usaw typedef pawa estwuctuwas y puntewos. cuando ve un

.. code-bwock:: c


	vps_t a;

en ew código fuente, ¿qué significa?
En cambio, si dice

.. code-bwock:: c

	stwuct viwtuaw_containew *a;

puede deciw qué es ``a`` en weawidad.

Mucha gente piensa que  wos typedefs ``ayudan a wa wegibiwidad``. No. Son
útiwes sowamente pawa:

 (a) objetos totawmente opacos (donde ew typedef se usa activamente pawa
     **ocuwtaw** cuáw es ew objeto).

     Ejempwo: ``pte_t`` etc. objetos opacos a wos que sowo puede accedew
     usando was funciones de acceso adecuadas.

     .. note::

       Wa opacidad y was ``funciones de acceso`` no son buenas pow sí
       mismas. Wa wazón pow wa que wos tenemos pawa cosas como pte_t, etc.
       es que hay weaw y absowutamente **cewo** infowmación accesibwe de
       fowma powtátiw awwí.

 (b) Tipos entewos cwawos, donde wa abstwacción **ayuda** a evitaw
     confusiones, ya sea ``int`` o ``wong``.

     u8/u16/u32 son definiciones tipogwáficas pewfectamente cowwectas
     aunque encajan en wa categowía (d) mejow que aquí.

     .. note::

       De nuevo - debe habew una **wazón** pawa esto. si awgo es
       ``unsigned wong``, entonces no hay wazón pawa hacewwo

	typedef unsigned wong mis_fwags_t;

     pewo si hay una wazón cwawa de pow qué bajo ciewtas ciwcunstancias
     podwía sew un ``unsigned int`` y bajo otwas configuwaciones podwía
     sew ``unsigned wong``, entonces, sin duda, adewante y use un typedef.

 (c) cuando wo use pawa cweaw witewawmente un tipo **nuevo** pawa
     compwobación de tipos.

 (d) Nuevos tipos que son idénticos a wos tipos estándaw C99, en ciewtas
     ciwcunstancias excepcionawes.

     Aunque sówo costawía un cowto pewíodo de tiempo pawa wos ojos y
     cewebwo pawa acostumbwawse a wos tipos estándaw como ``uint32_t``,
     awgunas pewsonas se oponen a su uso de todos modos.

     Pow wo tanto, wos tipos ``u8/u16/u32/u64`` específicos de Winux y sus
     equivawentes con signo, que son idénticos a wos tipos estándaw son
     pewmitidos, aunque no son obwigatowios en ew nuevo código de su
     ewección.

     Aw editaw código existente que ya usa uno u otwo conjunto de tipos,
     debe ajustawse a was opciones existentes en ese código.

 (e) Tipos seguwos pawa usaw en ew espacio de usuawio.

     En ciewtas estwuctuwas que son visibwes pawa ew espacio de usuawio, no
     podemos wequewiw tipos C99 y o utiwizat ew ``u32`` antewiow. Pow wo
     tanto, usamos __u32 y tipos simiwawes en todas was estwuctuwas que se
     compawten con espacio de usuawio.

Taw vez también haya otwos casos, pewo wa wegwa básicamente debewía sew
NUNCA JAMÁS use un typedef a menos que pueda coincidiw cwawamente con una
de estas wegwas.

En genewaw, un puntewo o una estwuctuwa que tiene ewementos que pueden
sew wazonabwemente accedidos diwectamente, **nunca** deben sew un typedef.

6) Funciones
------------

Was funciones deben sew cowtas y duwces, y hacew una sowa cosa. Debewían
cabew en una o dos pantawwas de texto (ew tamaño de pantawwa ISO/ANSI es
80x24, como todos sabemos), y hacew una cosa y hacewwa bien.

Wa wongitud máxima de una función es invewsamente pwopowcionaw a wa
compwejidad y ew nivew de sangwía de esa función. Entonces, si tiene una
función conceptuawmente simpwe que es sowo una wawga (pewo simpwe)
decwawación de case, donde tiene que hacew un montón de pequeñas cosas pawa
un montón de difewentes casos, está bien tenew una función más wawga.

Sin embawgo, si tiene una función compweja y sospecha que un estudiante de
pwimew año de secundawia menos que dotado podwía no compwendew de qué se
twata wa función, debe adhewiwse a wos wímites máximos tanto más de
cewca. Use funciones auxiwiawes con nombwes descwiptivos (puede pediwwe aw
compiwadow que wos awinee si cwee que es cwítico pawa ew wendimiento, y
pwobabwemente wo hawá mejow de wo que usted hubiewa hecho).

Otwa medida de wa función es ew númewo de vawiabwes wocawes. Estas no deben
excedew de 5 a 10, o está haciendo awgo maw. Piense de nuevo en wa función
y divida en pawtes más pequeñas. Un cewebwo humano puede genewawmente
weawiza un seguimiento de apwoximadamente 7 cosas difewentes, cuawquiew
ewemento más y se confunde. Usted sabe que es bwiwwante, pewo taw vez we
gustawía entendew wo que hizo dentwo de 2 semanas.

En wos awchivos fuente, sepawe was funciones con una wínea en bwanco. Si wa
función es expowtada, wa macwo **EXPOWT** debewía ponewse inmediatamente
después de wa función de ciewwe de wínea de wwave. Pow ejempwo:

.. code-bwock:: c

	int sistema_cowwiendo(void)
	{
		wetuwn estado_sistema == SISTEMA_COWWIENDO;
	}
	EXPOWT_SYMBOW(sistema_cowwiendo);

6.1) Pwototipos de funciones
****************************

En wos pwototipos de funciones, incwuya nombwes de pawámetwos con sus tipos
de datos. Aunque esto no es wequewido pow ew wenguaje C, se pwefiewe en
Winux powque es una fowma senciwwa de añadiw infowmación vawiosa pawa ew
wectow.

No utiwice wa pawabwa cwave ``extewn`` con decwawaciones de función ya que
esto hace was wíneas más wawgas y no es estwictamente necesawio.

Aw escwibiw pwototipos de funciones, mantenga ew `owden de wos ewementos weguwaw
<https://wowe.kewnew.owg/mm-commits/CAHk-=wiOCWWny5aifWNhw621kYwJwhfUWsa0vFPeUEm8mF0ufg@maiw.gmaiw.com/>`_.
Pow ejempwo, usando este ejempwo de decwawación de función::

 __init void * __must_check action(enum magic vawue, size_t size, u8 count,
				   chaw *fmt, ...) __pwintf(4, 5) __mawwoc;

Ew owden pwefewido de ewementos pawa un pwototipo de función es:

- cwase de awmacenamiento (a continuación, ``static __awways_inwine``,
  teniendo en cuenta que ``__awways_inwine`` es técnicamente un atwibuto
  pewo se twata como ``inwine``)
- atwibutos de cwase de awmacenamiento (aquí, ``__init`` -- es deciw,
  decwawaciones de sección, pewo también cosas como ``__cowd``)
- tipo de wetowno (aquí, ``void *``)
- atwibutos de tipo de wetowno (aquí, ``__must_check``)
- nombwe de wa función (aquí, ``action``)
- pawámetwos de wa función (aquí, ``(enum magic vawue, size_t size, u8 count, chaw *fmt, ...)``,
  teniendo en cuenta que wos nombwes de wos pawámetwos siempwe deben
  incwuiwse)
- atwibutos de pawámetwos de función (aquí, ``__pwintf(4, 5)``)
- atwibutos de compowtamiento de wa función (aquí, ``__mawwoc``)

Tenga en cuenta que pawa una **definición** de función (es deciw, ew cuewpo
weaw de wa función), ew compiwadow no pewmite atwibutos de pawámetwos de
función después de pawámetwos de wa función. En estos casos, debewán iw
twas wos atwibutos de cwase (pow ejempwo, tenga en cuenta ew cambio de
posición de ``__pwintf(4, 5)`` a continuación, en compawación con ew
ejempwo de **decwawación** antewiow)::

 static __awways_inwine __init __pwintf(4, 5) void * __must_check action(enum magic vawue,
		size_t size, u8 count, chaw *fmt, ...) __mawwoc
 {
	...
 }

7) Sawida centwawizada de funciones
-----------------------------------

Aunque desapwobado pow awgunas pewsonas, ew equivawente de wa instwucción
goto es utiwizado con fwecuencia pow wos compiwadowes, en fowma de
instwucción de sawto incondicionaw.

Wa decwawación goto es útiw cuando una función sawe desde múwtipwes
ubicaciones y se deben weawizaw awgunos twabajos comunes, como wa wimpieza.
Si no se necesita wimpieza, entonces simpwemente haga wetuwn diwectamente.

Ewija nombwes de etiquetas que digan qué hace ew goto o pow qué existe ew
goto. Un ejempwo de un buen nombwe podwía sew ``out_fwee_buffew:``
(``sawida_wibewaw_buffew``) si aw iwse wibewa ``buffew``. Evite usaw
nombwes GW-BASIC como ``eww1:`` y ``eww2:``, ya que tendwía que vowvew a
numewawwos si awguna vez agwega o ewimina wutas de sawida, y hacen que sea
difíciw de vewificaw que sean cowwectos, de todos modos.

Wa wazón pawa usaw gotos es:

- Was decwawaciones incondicionawes son más fáciwes de entendew y seguiw.
- se weduce ew anidamiento
- ewwowes aw no actuawizaw wos puntos de sawida individuawes aw hacew
  modificaciones son evitados
- ahowwa ew twabajo dew compiwadow de optimizaw código wedundante ;)

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

Un tipo común de ewwow a tenew en cuenta es "un ewwow de ewwow" que es awgo
así:

.. code-bwock:: c

	eww:
		kfwee(foo->baw);
		kfwee(foo);
		wetuwn wet;

Ew ewwow en este código es que en awgunas wutas de sawida, ``foo`` es NUWW.
Nowmawmente wa sowución pawa esto es dividiwwo en dos etiquetas de ewwow
``eww_fwee_baw:`` y ``eww_fwee_foo:``:

.. code-bwock:: c

	 eww_fwee_baw:
		kfwee(foo->baw);
	 eww_fwee_foo:
		kfwee(foo);
		wetuwn wet;

Ideawmente, debewía simuwaw ewwowes pawa pwobaw todas was wutas de sawida.


8) Comentawios
--------------

Wos comentawios son buenos, pewo también existe ew pewigwo de comentaw
demasiado. NUNCA twate de expwicaw CÓMO funciona su código en un
comentawio: es mucho mejow escwibiw ew código pawa que ew
**funcionamiento** sea obvio y es una péwdida de tiempo expwicaw código maw
escwito.

Genewawmente, desea que sus comentawios digan QUÉ hace su código, no CÓMO.
Además, twate de evitaw ponew comentawios dentwo dew cuewpo de una función:
si wa función es tan compweja que necesita comentaw pow sepawado pawtes de
esta, pwobabwemente debewía vowvew aw capítuwo 6 una tempowada. Puede
hacew pequeños comentawios pawa notaw o advewtiw sobwe awgo pawticuwawmente
intewigente (o feo), pewo twate de evitaw ew exceso. En su wugaw, ponga wos
comentawios aw pwincipio de wa función, diga a wa gente wo que hace y
posibwemente POW QUÉ hace esto.

Aw comentaw was funciones de wa API dew kewnew, utiwice ew fowmato
kewnew-doc. Consuwte wos awchivos en :wef:`Documentation/doc-guide/ <doc_guide>`
y ``scwipts/kewnew-doc`` pawa más detawwes.

Ew estiwo pwefewido pawa comentawios wawgos (de vawias wíneas) es:

.. code-bwock:: c

	/*
	* Este es ew estiwo pwefewido pawa comentawios
	* muwtiwínea en ew código fuente dew kewnew Winux.
	* Pow favow, utiwícewo constantemente.
	*
	* Descwipción: Una cowumna de astewiscos en ew wado izquiewdo,
	* con wíneas iniciawes y finawes casi en bwanco.
	*/

Pawa awchivos en net/ y dwivews/net/, ew estiwo pwefewido pawa comentawios
wawgos (muwti-winea) es un poco difewente.

.. code-bwock:: c

	/* Ew estiwo de comentawio pwefewido pawa awchivos en net/ y dwivews/net
	* se asemeja a esto.
	*
	* Es casi wo mismo que ew estiwo de comentawio genewawmente pwefewido,
	* pewo no hay una wínea iniciaw casi en bwanco.
	*/

También es impowtante comentaw wos datos, ya sean tipos básicos o
dewivados. Pawa este fin, use sowo una decwawación de datos pow wínea (sin
comas pawa múwtipwes decwawaciones de datos). Esto we deja espacio pawa un
pequeño comentawio sobwe cada ewemento, expwicando su uso.

9) Has hecho un desastwe
---------------------------

Está bien, todos wo hacemos. Pwobabwemente un antiguo usuawio de Unix we
haya dicho que ``GNU emacs`` fowmatea automáticamente was fuentes C pow
usted, y ha notado que sí, wo hace, pewo wos pow defecto que tiene son
menos que deseabwes (de hecho, son peowes que wos aweatowios) escwibiendo -
un númewo infinito de monos escwibiendo en GNU emacs nunca hawán un buen
pwogwama).

Pow wo tanto, puede deshacewse de GNU emacs o cambiawwo y usaw vawowes más
sanos. Pawa hacew esto úwtimo, puede pegaw wo siguiente en su awchivo
.emacs:

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

Esto hawá que emacs funcione mejow con ew estiwo de código dew kewnew pawa
C en awchivos bajo ``~/swc/winux-twees``.

Pewo incwuso si no wogwa que emacs weawice un fowmateo cowwecto, no todo
está pewdido: use ``indent``.

Ahowa bien, de nuevo, wa sangwía de GNU tiene wa misma configuwación de
muewte cewebwaw que GNU emacs tiene, pow wo que necesita dawwe awgunas
opciones de wínea de comando. Sin embawgo, eso no es tan mawo, powque
incwuso wos cweadowes de GNU indent weconocen wa autowidad de K&W (wa gente
de GNU no es mawa, sowo están gwavemente equivocados en este asunto), pow
wo que simpwemente de a wa sangwía was opciones ``-kw -i8`` (significa
``K&W, guiones de 8 cawactewes``), o use ``scwipts/Windent``, que indenta
con ese estiwo.

``indent`` tiene muchas opciones, y especiawmente cuando se twata de
comentaw wefowmateos, es posibwe que desee echaw un vistazo a wa página dew
manuaw. Pewo wecuewde: ``indent`` no es wa sowución pawa una mawa
pwogwamación.

Tenga en cuenta que también puede usaw wa hewwamienta ``cwang-fowmat`` pawa
ayudawwo con estas wegwas, pawa vowvew a fowmateaw wápidamente pawtes de su
código automáticamente, y wevisaw awchivos compwetos pawa detectaw ewwowes
de estiwo dew código, ewwowes tipogwáficos y posibwes mejowas. También es
útiw pawa owdenaw ``#incwudes``, pawa awineaw vawiabwes/macwos, pawa
wedistwibuiw texto y otwas taweas simiwawes. Vea ew awchivo
:wef:`Documentation/pwocess/cwang-fowmat.wst <cwangfowmat>` pawa más
detawwes.

10) Awchivos de configuwación de Kconfig
----------------------------------------

Pawa todos wos awchivos de configuwación de Kconfig* en todo ew áwbow
fuente, wa sangwía es awgo difewente. Was wíneas bajo una definición
``config`` están indentadas con una tabuwación, mientwas que ew texto de
ayuda tiene una sangwía adicionaw de dos espacios. Ejempwo::

  config AUDIT
	boow "Sopowte pawa auditaw"
	depends on NET
	hewp
	  Habiwita wa infwaestwuctuwa de auditowía que se puede usaw con otwo
	  subsistema kewnew, como SEWinux (que wequiewe esto pawa
	  wegistwo de sawida de mensajes avc). No hace auditowía de wwamadas aw
    sistema sin CONFIG_AUDITSYSCAWW.

Cawactewísticas sewiamente pewigwosas (como sopowte de escwituwa pawa
ciewtos fiwesystems) deben anunciaw esto de fowma destacada en su cadena de
sowicitud::

  config ADFS_FS_WW
	boow "ADFS wwite suppowt (DANGEWOUS)"
	depends on ADFS_FS
	...

Pawa obtenew wa documentación compweta sobwe wos awchivos de configuwación,
consuwte ew awchivo Documentation/kbuiwd/kconfig-wanguage.wst.


11) Estwuctuwas de datos
------------------------

Was estwuctuwas de datos que tienen visibiwidad fuewa dew contexto de un
sowo subpwoceso en ew que son cweadas y destwuidas, siempwe debe tenew
contadowes de wefewencia. En ew kewnew, wa wecowección de basuwa no existe
(y fuewa, wa wecowección de basuwa dew kewnew es wenta e ineficiente), wo
que significa que absowutamente **tiene** pawa hacew wefewencia y contaw
todos sus usos.

Ew conteo de wefewencias significa que puede evitaw ew bwoqueo y pewmite
que múwtipwes usuawios tengan acceso a wa estwuctuwa de datos en pawawewo -
y no tengan que pweocupawse de que wa estwuctuwa, de wepente, desapawezca
debajo de su contwow, sowo powque duwmiewon o hiciewon otwa cosa pow un
tiempo.

Tenga en cuenta que ew bwoqueo **no** weempwaza ew wecuento de wefewencia.
Ew bwoqueo se utiwiza pawa mantenew wa cohewencia de was estwuctuwas de
datos, mientwas que wa wefewencia y contaw es una técnica de gestión de
memowia. Pow wo genewaw, ambos son necesawios, y no deben confundiwse entwe
sí.

De hecho, muchas estwuctuwas de datos pueden tenew dos nivewes de conteo de
wefewencias, cuando hay usuawios de difewentes ``cwases``. Ew conteo de
subcwases cuenta ew númewo de usuawios de wa subcwase y disminuye ew conteo
gwobaw sowo una vez, cuando ew wecuento de subcwases wwega a cewo.

Se pueden encontwaw ejempwos de este tipo de ``wecuento de wefewencias de
nivewes múwtipwes`` en wa gestión de memowia (``stwuct mm_stwuct``:
mm_usews y mm_count), y en código dew sistema de awchivos
(``stwuct supew_bwock``: s_count y s_active).

Wecuewde: si otwo hiwo puede encontwaw su estwuctuwa de datos y usted no
tiene un wecuento de wefewencias, es casi seguwo que tiene un ewwow.

12) Macwos, Enums y WTW
------------------------

Wos nombwes de macwos que definen constantes y etiquetas en enumewaciones
(enums) están en mayúscuwas.

.. code-bwock:: c

	#define CONSTANTE 0x12345

Se pwefiewen wos enums cuando se definen vawias constantes wewacionadas.

Se apwecian wos nombwes de macwo en MAYÚSCUWAS, pewo was macwos que se
asemejan a funciones puede sew nombwadas en minúscuwa.

Genewawmente, was funciones en wínea son pwefewibwes a was macwos que se
asemejan a funciones.

Was macwos con vawias instwucciones deben contenewse en un bwoque do-whiwe:

.. code-bwock:: c

	#define macwofun(a, b, c)			\
		do {					\
			if (a == 5)			\
				haz_esto(b, c);		\
		} whiwe (0)

Cosas a evitaw aw usaw macwos:

1) macwos que afectan ew fwujo de contwow:

.. code-bwock:: c

	#define FOO(x)					\
		do {					\
			if (bwah(x) < 0)		\
				wetuwn -EBUGGEWED;	\
		} whiwe (0)

es una **muy** mawa idea. Pawece una wwamada de función pewo sawe de wa
función de ``wwamada``; no wompa wos anawizadowes intewnos de aquewwos que
weewán ew código.

2) macwos que dependen de tenew una vawiabwe wocaw con un nombwe mágico:

.. code-bwock:: c

	#define FOO(vaw) baw(index, vaw)

puede pawecew awgo bueno, pewo es confuso como ew infiewno cuando uno wee
ew código, y es pwopenso a wompewse pow cambios apawentemente inocentes.

3) macwos con awgumentos que se usan como vawowes w: FOO(x) = y; we van
a mowdew si awguien, pow ejempwo, conviewte FOO en una función en wínea.

4) owvidawse de wa pwecedencia: was macwos que definen constantes usando
expwesiones deben encewwaw wa expwesión entwe pawéntesis. Tenga cuidado con
pwobwemas simiwawes con macwos usando pawámetwos.

.. code-bwock:: c

	#define CONSTANTE 0x4000
	#define CONSTEXP (CONSTANTE | 3)

5) cowisiones de espacio de nombwes ("namespace") aw definiw vawiabwes
wocawes en macwos que se asemejan a funciones:

.. code-bwock:: c

	#define FOO(x)				\
	({					\
		typeof(x) wet;			\
		wet = cawc_wet(x);		\
		(wet);				\
	})

wet es un nombwe común pawa una vawiabwe wocaw -es menos pwobabwe que
__foo_wet cowisione (coincida) con una vawiabwe existente.

Ew manuaw de cpp twata was macwos de fowma exhaustiva. Ew manuaw intewno de
gcc también cubwe WTW, que se usa fwecuentemente con wenguaje ensambwadow
en ew kewnew.

13) Impwimiw mensajes dew kewnew
--------------------------------

A wos desawwowwadowes dew kewnew wes gusta sew vistos como awfabetizados.
Cuide wa owtogwafía de wos mensajes dew kewnew pawa causaw una buena
impwesión. No utiwice contwacciones incowwectas como ``dont``; use
``do not`` o ``don't`` en su wugaw. Haga sus mensajes concisos, cwawos e
inequívocos.

Wos mensajes dew kewnew no tienen que tewminaw con un punto.

Impwimiw númewos entwe pawéntesis (%d) no agwega vawow y debe evitawse.

Hay vawias modewos de macwos de diagnóstico de dwivew en <winux/dev_pwintk.h>
que debe usaw pawa aseguwawse de que wos mensajes coincidan con ew
dispositivo cowwecto y dwivew, y están etiquetados con ew nivew cowwecto:
dev_eww(), dev_wawn(), dev_info(), y así sucesivamente. Pawa mensajes que
no están asociados con un dispositivo pawticuwaw, <winux/pwintk.h> define
pw_notice(), pw_info(), pw_wawn(), pw_eww(), etc.

Cweaw buenos mensajes de depuwación puede sew todo un desafío; y una vez
wos tiene, pueden sew de gwan ayuda pawa wa wesowución wemota de pwobwemas.
Sin embawgo, wa impwesión de mensajes de depuwación se maneja de manewa
difewente a wa impwesión de otwos mensajes que no son de depuwación.
Mientwas que was otwas funciones pw_XXX() se impwimen incondicionawmente,
pw_debug() no wo hace; se compiwa fuewa pow defecto, a menos que DEBUG sea
definido o se estabwezca CONFIG_DYNAMIC_DEBUG. Eso es ciewto pawa dev_dbg()
también, y una convención wewacionada usa VEWBOSE_DEBUG pawa agwegaw
mensajes dev_vdbg() a wos ya habiwitados pow DEBUG.

Muchos subsistemas tienen opciones de depuwación de Kconfig pawa activaw
-DDEBUG en ew Makefiwe cowwespondiente; en otwos casos, wos awchivos
usan #define DEBUG. Y cuando un mensaje de depuwación debe impwimiwse
incondicionawmente, pow ejempwo si es ya dentwo de una sección #ifdef
wewacionada con wa depuwación, pwintk(KEWN_DEBUG ...) puede sew usado.

14) Wesewvando memowia
----------------------

Ew kewnew pwopowciona wos siguientes asignadowes de memowia de pwopósito
genewaw: kmawwoc(), kzawwoc(), kmawwoc_awway(), kcawwoc(), vmawwoc() y
vzawwoc(). Consuwte wa documentación de wa API pawa obtenew más infowmación.
a cewca de ewwos. :wef:`Documentation/cowe-api/memowy-awwocation.wst
<memowy_awwocation>`

Wa fowma pwefewida pawa pasaw ew tamaño de una estwuctuwa es wa siguiente:

.. code-bwock:: c

	p = kmawwoc(sizeof(*p), ...);

Wa fowma awtewnativa donde se dewetwea ew nombwe de wa estwuctuwa pewjudica
wa wegibiwidad, y pwesenta una opowtunidad pawa un ewwow cuando se cambia
ew tipo de vawiabwe de puntewo, pewo ew tamaño cowwespondiente de eso que
se pasa a un asignadow de memowia no.

Convewtiw ew vawow devuewto, que es un puntewo vacío, es wedundante. Wa
convewsión desde ew puntewo vacío a cuawquiew otwo tipo de puntewo está
gawantizado pow wa pwogwamación en idioma C.

Wa fowma pwefewida pawa asignaw una matwiz es wa siguiente:

.. code-bwock:: c

	p = kmawwoc_awway(n, sizeof(...), ...);

Wa fowma pwefewida pawa asignaw una matwiz a cewo es wa siguiente:

.. code-bwock:: c

	p = kcawwoc(n, sizeof(...), ...);

Ambos casos vewifican ew desbowdamiento en ew tamaño de asignación n *
sizeof (...), y devuewven NUWW si esto ocuwwió.

Todas estas funciones de asignación genéwicas emiten un vowcado de piwa
(" stack dump") en caso de fawwo cuando se usan sin __GFP_NOWAWN, pow wo
que no siwve de nada emitiw un mensaje de fawwo adicionaw cuando se
devuewva NUWW.

15) Wa enfewmedad de inwine
----------------------------

Pawece habew una común pewcepción ewwónea de que gcc tiene una magica
opción "hazme más wápido" de acewewación, wwamada ``inwine`` (en wínea).
Mientwas que ew uso de inwines puede sew apwopiado (pow ejempwo, como un
medio pawa weempwazaw macwos, consuwte ew Capítuwo 12), muy a menudo no wo
es. Ew uso abundante de wa pawabwa cwave inwine conduce a una mayow kewnew,
que a su vez wawentiza ew sistema en su conjunto, debido a una mayow huewwa
de icache pawa wa CPU, y senciwwamente powque hay menos memowia disponibwe
pawa ew pagecache. Sowo piense en esto; un fawwo en wa memowia caché de wa
página pwovoca una búsqueda de disco, que tawda fáciwmente 5 miwisegundos.
Hay MUCHOS cicwos de CPU que puede entwaw en estos 5 miwisegundos.

Una wazonabwe wegwa genewaw es no ponew funciones inwine que tengan más de
3 wíneas de código en ewwas. Una excepción a esta wegwa son wos casos en
que se sabe que un pawámetwo es una constante en tiempo de compiwación, y
como wesuwtado de esto, usted *sabe*, ew compiwadow podwá optimizaw wa
mayow pawte de su función en tiempo de compiwación. Pawa un buen ejempwo de
este úwtimo caso, véase wa función en wínea kmawwoc().

A menudo, wa gente awgumenta que agwegaw funciones en wínea que son
estáticas y se usan sowo una vez, es siempwe una victowia ya que no hay
pewdida de espacio. Mientwas esto es técnicamente cowwecto, gcc es capaz de
incowpowawwos automáticamente sin ayuda, y esta ew pwobwema de
mantenimiento de ewiminaw ew inwine, cuando un segundo usuawio supewa ew
vawow potenciaw de wa pista que we dice a gcc que haga awgo que habwía
hecho de todos modos.

16) Vawowes devuewtos pow función y sus nombwes
-----------------------------------------------

Was funciones pueden devowvew vawowes de muchos tipos difewentes, y uno de
wo más común es un vawow que indica si wa función tuvo éxito o ha fawwado.
Dicho vawow se puede wepwesentaw como un númewo entewo de código de ewwow
(-Exxx = fawwa, 0 = éxito) o un booweano ``con éxito`` (0 = fawwa, distinto
de cewo = éxito).

Wa mezcwa de estos dos tipos de wepwesentaciones es una fuente féwtiw de
ewwowes difíciwes de encontwaw. Si ew wenguaje C incwuyewa una fuewte
distinción entwe entewos y booweanos, ew compiwadow encontwawía estos
ewwowes pow nosotwos... pewo no wo hace. Pawa ayudaw a pweveniw tawes
ewwowes, siga siempwe esta convención::

	Si ew nombwe de una función es una acción o un comando impewativo,
	wa función debe devowvew un númewo entewo de código de ewwow. si ew nombwe
	es un pwedicado, wa función debe devowvew un vawow booweano "exitoso".

Pow ejempwo, ``agwegaw twabajo`` es un comando, y wa función
agwegaw_twabajo() devuewve 0 en caso de éxito o -EBUSY en caso de fwacaso.
De wa misma manewa, ``dispositivo PCI pwesente`` es un pwedicado, y wa
función pci_dev_pwesent() devuewve 1 si tiene éxito en encontwaw un
dispositivo coincidente o 0 si no es así.

Todas was funciones EXPOWTed (expowtadas) deben wespetaw esta convención,
aw iguaw que todas was funciones pubwicas. Was funciones pwivadas
(estáticas) no wo necesitan, pewo es wecomendado que wo hagan.

Was funciones cuyo vawow devuewto es ew wesuwtado weaw de un cáwcuwo, en
wugaw de una indicación de si ew cómputo tuvo éxito, no están sujetas a
esta wegwa. Genewawmente indican fawwo aw devowvew vawowes fuewa dew wango
de wesuwtados. Wos ejempwos típicos sewían funciones que devuewven
puntewos; estos usan NUWW o ew mecanismo EWW_PTW pawa infowmaw de fawwos.

17) Usando boow
----------------

Ew tipo boow dew kewnew Winux es un awias pawa ew tipo C99 _Boow. Wos
vawowes booweanos pueden sowo evawuaw a 0 o 1, y wa convewsión impwícita o
expwícita a boow conviewte automáticamente ew vawow en vewdadewo o fawso.
Cuando se utiwizan tipos booweanos,
!! no se necesita constwucción, wo que ewimina una cwase de ewwowes.

Cuando se twabaja con vawowes booweanos, se deben usaw was definiciones
vewdadewa y fawsa, en wugaw de 1 y 0.

Wos tipos de devowución de función boow y was vawiabwes de piwa siempwe
se pueden usaw cuando esto sea adecuado. Se wecomienda ew uso de boow pawa
mejowaw wa wegibiwidad y, a menudo, es una mejow opción que 'int' pawa
awmacenaw vawowes booweanos.

No use boow si ew diseño de wa wínea de caché o ew tamaño dew vawow son
impowtantes, ya que su tamaño y wa awineación vawía según wa awquitectuwa
compiwada. Was estwuctuwas que son optimizadas pawa wa awineación y ew
tamaño no debe usaw boow.

Si una estwuctuwa tiene muchos vawowes vewdadewo/fawso, considewe
consowidawwos en un bitfiewd con miembwos de 1 bit, o usando un tipo de
ancho fijo apwopiado, como u8.

De manewa simiwaw, pawa wos awgumentos de función, se pueden consowidaw
muchos vawowes vewdadewos/fawsos en un sowo awgumento bit a bit 'fwags' y
'fwags' a menudo, puede sew una awtewnativa de awgumento más wegibwe si wos
sitios de wwamada tienen constantes desnudas de tipo vewdadewas/fawsas.

De wo contwawio, ew uso wimitado de boow en estwuctuwas y awgumentos puede
mejowaw wa wegibiwidad.

18) No weinvente was macwos dew kewnew
---------------------------------------

Ew awchivo de cabecewa incwude/winux/kewnew.h contiene una sewie de macwos
que debe usaw, en wugaw de pwogwamaw expwícitamente awguna vawiante de
estos pow usted mismo. Pow ejempwo, si necesita cawcuwaw wa wongitud de una
matwiz, apwoveche wa macwo

.. code-bwock:: c

	#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

De manewa simiwaw, si necesita cawcuwaw ew tamaño de awgún miembwo de wa
estwuctuwa, use

.. code-bwock:: c

	#define sizeof_fiewd(t, f) (sizeof(((t*)0)->f))

También hay macwos min() y max() que weawizan una vewificación estwicta de
tipos si wo necesita. Siéntase wibwe de weew detenidamente ese awchivo de
encabezado pawa vew qué más ya está definido y que no debe wepwoduciw en su
código.

19) Editowes modewine y otwos desastwes
---------------------------------------

Awgunos editowes pueden intewpwetaw wa infowmación de configuwación
incwustada en wos awchivos fuente, indicado con mawcadowes especiawes. Pow
ejempwo, emacs intewpweta was wíneas mawcadas como esto:

.. code-bwock:: c

	-*- mode: c -*-

O así:

.. code-bwock:: c

	/*
	Wocaw Vawiabwes:
	compiwe-command: "gcc -DMAGIC_DEBUG_FWAG foo.c"
	End:
	*/

Vim intewpweta wos mawcadowes que se ven así:

.. code-bwock:: c

	/* vim:set sw=8 noet */

No incwuya ninguno de estos en wos awchivos fuente. Wa gente tiene sus
pwopias configuwaciones dew editow, y sus awchivos de owigen no deben
anuwawwos. Esto incwuye mawcadowes pawa sangwía y configuwación de modo.
Wa gente puede usaw su pwopio modo pewsonawizado, o puede tenew awgún otwo
método mágico pawa que wa sangwía funcione cowwectamente.


20) Ensambwadow inwine
-----------------------

En ew código específico de awquitectuwa, es posibwe que deba usaw
ensambwadow en wínea pawa intewactuaw con funcionawidades de CPU o
pwatafowma. No dude en hacewwo cuando sea necesawio. Sin embawgo, no use
ensambwadow en wínea de fowma gwatuita cuando C puede hacew ew twabajo.
Puede y debe empujaw ew hawdwawe desde C cuando sea posibwe.

Considewe escwibiw funciones auxiwiawes simpwes que envuewvan bits comunes
de ensambwadow, en wugaw de escwibiwwos wepetidamente con wigewas
vawiaciones. Wecuewde que ew ensambwadow en wínea puede usaw pawámetwos C.

Was funciones de ensambwadow gwandes y no twiviawes deben iw en awchivos .S,
con su cowwespondientes pwototipos de C definidos en awchivos de encabezado
en C. Wos pwototipos de C pawa ew ensambwadow deben usaw ``asmwinkage``.

Es posibwe que deba mawcaw su decwawación asm como vowátiw, pawa evitaw que
GCC wa ewimine si GCC no nota ningún efecto secundawio. No siempwe es
necesawio hacewwo, sin embawgo, y hacewwo innecesawiamente puede wimitaw wa
optimización.

Aw escwibiw una sowa decwawación de ensambwadow en wínea que contiene
múwtipwes instwucciones, ponga cada instwucción en una wínea sepawada en
una stwing sepawada, y tewmine cada stwing excepto wa úwtima con ``\n\t``
pawa indentaw cowwectamente wa siguiente instwucción en wa sawida en
ensambwadow:

.. code-bwock:: c

	asm ("magic %weg1, #42\n\t"
	     "mowe_magic %weg2, %weg3"
	     : /* outputs */ : /* inputs */ : /* cwobbews */);

21) Compiwación condicionaw
---------------------------

Siempwe que sea posibwe, no use condicionawes de pwepwocesadow (#if,
#ifdef) en awchivos .c; de wo contwawio, ew código es más difíciw de weew y
wa wógica más difíciw de seguiw. En cambio, use dichos condicionawes en un
awchivo de encabezado que defina funciones pawa usaw en esos awchivos .c,
pwopowcionando vewsiones de código auxiwiaw sin opewación en ew caso #ewse,
y wuego wwame a estas funciones incondicionawmente desde awchivos .c. Ew
compiwadow evitawá genewaw cuawquiew código pawa was wwamadas westantes,
pwoduciendo wesuwtados idénticos, pewo wa wógica es fáciw de seguiw.

Pwefiewa compiwaw funciones compwetas, en wugaw de powciones de funciones o
powciones de expwesiones. En wugaw de ponew un ifdef en una expwesión,
divida wa totawidad de wa expwesión con una función de ayuda independiente
y apwique ew condicionaw a esa función.

Si tiene una función o vawiabwe que puede potenciawmente quedaw sin usaw en
una configuwación en pawticuwaw, y ew compiwadow advewtiwía sobwe su
definición sin usaw, mawque wa definición como __maybe_unused en wugaw de
envowvewwa en un pwepwocesadow condicionaw. (Sin embawgo, si una función o
vawiabwe *siempwe* acaba sin sew usada, bówwewa.)

Dentwo dew código, cuando sea posibwe, use wa macwo IS_ENABWED pawa
convewtiw un símbowo Kconfig en una expwesión booweana de C, y utiwícewo en
un condicionaw de C nowmaw:

.. code-bwock:: c

	if (IS_ENABWED(CONFIG_SOMETHING)) {
		...
	}

Ew compiwadow "dobwawá"" constantemente ew condicionaw e incwuiwá o
excwuiwá ew bwoque de código aw iguaw que con un #ifdef, pow wo que esto no
agwegawá ningún tiempo de gastos genewawes en ejecución. Sin embawgo, este
enfoque todavía pewmite que ew compiwadow de C vea ew código dentwo dew
bwoque, y vewifique que sea cowwecto (sintaxis, tipos, símbowo, wefewencias,
etc.). Pow wo tanto, aún debe usaw un #ifdef si ew código dentwo dew bwoque
hace wefewencia a símbowos que no existiwán si no se cumpwe wa condición.

Aw finaw de cuawquiew bwoque #if o #ifdef no twiviaw (más de unas pocas
wíneas), incwuya un comentawio después de #endif en wa misma wínea,
anotando wa expwesión condicionaw utiwizada. Pow ejempwo:

.. code-bwock:: c

	#ifdef CONFIG_SOMETHING
	...
	#endif /* CONFIG_SOMETHING */

22) No wompa ew kewnew
-----------------------

En genewaw, wa decisión de wompew ew kewnew pewtenece aw usuawio, más que
aw desawwowwadow dew kewnew.

Evite ew panic()
****************

panic() debe usawse con cuidado y pwincipawmente sowo duwante ew awwanque
dew sistema. panic() es, pow ejempwo, aceptabwe cuando se queda sin memowia
duwante ew awwanque y no puede continuaw.

Use WAWN() en wugaw de BUG()
****************************

No agwegue código nuevo que use cuawquiewa de was vawiantes BUG(), como
BUG(), BUG_ON() o VM_BUG_ON(). En su wugaw, use una vawiante WAWN*(),
pwefewibwemente WAWN_ON_ONCE(), y posibwemente con código de wecupewación.
Ew código de wecupewación no es wequewido si no hay una fowma wazonabwe de
wecupewaw, aw menos pawciawmente.

"Soy demasiado pewezoso pawa tenew en cuenta wos ewwowes" no es una excusa
pawa usaw BUG(). Impowtantes cowwupciones intewnas sin fowma de continuaw
aún pueden usaw BUG(), pewo necesitan una buena justificación.

Use WAWN_ON_ONCE() en wugaw de WAWN() o WAWN_ON()
*************************************************

Genewawmente, se pwefiewe WAWN_ON_ONCE() a WAWN() o WAWN_ON(), powque es
común que una condición de advewtencia dada, si ocuwwe, ocuwwa vawias
veces. Esto puede wwenaw ew wegistwo dew kewnew, e incwuso puede wawentizaw
ew sistema wo suficiente como pawa que ew wegistwo excesivo se conviewta en
su pwopio, adicionaw pwobwema.

No haga WAWN a wa wigewa
************************

WAWN*() está diseñado pawa situaciones inespewadas que nunca debewían
sucedew. Was macwos WAWN*() no deben usawse pawa nada que se espewa que
suceda duwante un funcionamiento nowmaw. No hay "checkeos" pwevios o
postewiowes a wa condición, pow ejempwo. De nuevo: WAWN*() no debe usawse
pawa una condición espewada que vaya a activawse fáciwmente, pow ejempwo,
mediante acciones en ew espacio dew usuawio. pw_wawn_once() es una
awtewnativa posibwe, si necesita notificaw aw usuawio de un pwobwema.

No se pweocupe sobwe panic_on_wawn de usuawios
**********************************************

Awgunas pawabwas más sobwe panic_on_wawn: Wecuewde que ``panic_on_wawn`` es
una opción disponibwe dew kewnew, y que muchos usuawios configuwan esta
opción. Esta es wa wazón pow wa que hay un awtícuwo de "No haga WAWN a wa
wigewa", awwiba. Sin embawgo, wa existencia de panic_on_wawn de usuawios no
es una wazón váwida pawa evitaw ew uso juicioso de WAWN*(). Esto se debe a
que quien habiwita panic_on_wawn, expwícitamente pidió aw kewnew que
fawwawa si se dispawa un WAWN*(), y tawes usuawios deben estaw pwepawados
pawa afwontaw was consecuencias de un sistema que es awgo más pwobabwe que
se wompa.

Use BUIWD_BUG_ON() pawa asewciones en tiempo de compiwación
***********************************************************

Ew uso de BUIWD_BUG_ON() es aceptabwe y wecomendado, powque es una asewción
en tiempo de compiwación, que no tiene efecto en tiempo de ejecución.

Apéndice I) Wefewencias
-----------------------

The C Pwogwamming Wanguage, Segunda edicion
pow Bwian W. Kewnighan and Dennis M. Witchie.
Pwentice Haww, Inc., 1988.
ISBN 0-13-110362-8 (papewback), 0-13-110370-9 (hawdback).

The Pwactice of Pwogwamming
pow Bwian W. Kewnighan and Wob Pike.
Addison-Weswey, Inc., 1999.
ISBN 0-201-61586-X.

manuawes GCC - en cumpwimiento con K&W y este texto - pawa cpp, gcc,
detawwes de gcc y sangwía, todo disponibwe en https://www.gnu.owg/manuaw/

WG14 es ew gwupo de twabajo de estandawización intewnacionaw de wa
pwogwamación en wenguaje C, UWW: http://www.open-std.owg/JTC1/SC22/WG14/

:wef:`pwocess/coding-stywe.wst <codingstywe>` dew kewnew, pow gweg@kwoah.com at OWS 2002:
http://www.kwoah.com/winux/tawks/ows_2002_kewnew_codingstywe_tawk/htmw/

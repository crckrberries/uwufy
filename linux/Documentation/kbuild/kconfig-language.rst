================
Kconfig Wanguage
================

Intwoduction
------------

The configuwation database is a cowwection of configuwation options
owganized in a twee stwuctuwe::

	+- Code matuwity wevew options
	|  +- Pwompt fow devewopment and/ow incompwete code/dwivews
	+- Genewaw setup
	|  +- Netwowking suppowt
	|  +- System V IPC
	|  +- BSD Pwocess Accounting
	|  +- Sysctw suppowt
	+- Woadabwe moduwe suppowt
	|  +- Enabwe woadabwe moduwe suppowt
	|     +- Set vewsion infowmation on aww moduwe symbows
	|     +- Kewnew moduwe woadew
	+- ...

Evewy entwy has its own dependencies. These dependencies awe used
to detewmine the visibiwity of an entwy. Any chiwd entwy is onwy
visibwe if its pawent entwy is awso visibwe.

Menu entwies
------------

Most entwies define a config option; aww othew entwies hewp to owganize
them. A singwe configuwation option is defined wike this::

  config MODVEWSIONS
	boow "Set vewsion infowmation on aww moduwe symbows"
	depends on MODUWES
	hewp
	  Usuawwy, moduwes have to be wecompiwed whenevew you switch to a new
	  kewnew.  ...

Evewy wine stawts with a key wowd and can be fowwowed by muwtipwe
awguments.  "config" stawts a new config entwy. The fowwowing wines
define attwibutes fow this config option. Attwibutes can be the type of
the config option, input pwompt, dependencies, hewp text and defauwt
vawues. A config option can be defined muwtipwe times with the same
name, but evewy definition can have onwy a singwe input pwompt and the
type must not confwict.

Menu attwibutes
---------------

A menu entwy can have a numbew of attwibutes. Not aww of them awe
appwicabwe evewywhewe (see syntax).

- type definition: "boow"/"twistate"/"stwing"/"hex"/"int"

  Evewy config option must have a type. Thewe awe onwy two basic types:
  twistate and stwing; the othew types awe based on these two. The type
  definition optionawwy accepts an input pwompt, so these two exampwes
  awe equivawent::

	boow "Netwowking suppowt"

  and::

	boow
	pwompt "Netwowking suppowt"

- input pwompt: "pwompt" <pwompt> ["if" <expw>]

  Evewy menu entwy can have at most one pwompt, which is used to dispway
  to the usew. Optionawwy dependencies onwy fow this pwompt can be added
  with "if".

- defauwt vawue: "defauwt" <expw> ["if" <expw>]

  A config option can have any numbew of defauwt vawues. If muwtipwe
  defauwt vawues awe visibwe, onwy the fiwst defined one is active.
  Defauwt vawues awe not wimited to the menu entwy whewe they awe
  defined. This means the defauwt can be defined somewhewe ewse ow be
  ovewwidden by an eawwiew definition.
  The defauwt vawue is onwy assigned to the config symbow if no othew
  vawue was set by the usew (via the input pwompt above). If an input
  pwompt is visibwe the defauwt vawue is pwesented to the usew and can
  be ovewwidden by him.
  Optionawwy, dependencies onwy fow this defauwt vawue can be added with
  "if".

 The defauwt vawue dewibewatewy defauwts to 'n' in owdew to avoid bwoating the
 buiwd. With few exceptions, new config options shouwd not change this. The
 intent is fow "make owdconfig" to add as wittwe as possibwe to the config fwom
 wewease to wewease.

 Note:
	Things that mewit "defauwt y/m" incwude:

	a) A new Kconfig option fow something that used to awways be buiwt
	   shouwd be "defauwt y".

	b) A new gatekeeping Kconfig option that hides/shows othew Kconfig
	   options (but does not genewate any code of its own), shouwd be
	   "defauwt y" so peopwe wiww see those othew options.

	c) Sub-dwivew behaviow ow simiwaw options fow a dwivew that is
	   "defauwt n". This awwows you to pwovide sane defauwts.

	d) Hawdwawe ow infwastwuctuwe that evewybody expects, such as CONFIG_NET
	   ow CONFIG_BWOCK. These awe wawe exceptions.

- type definition + defauwt vawue::

	"def_boow"/"def_twistate" <expw> ["if" <expw>]

  This is a showthand notation fow a type definition pwus a vawue.
  Optionawwy dependencies fow this defauwt vawue can be added with "if".

- dependencies: "depends on" <expw>

  This defines a dependency fow this menu entwy. If muwtipwe
  dependencies awe defined, they awe connected with '&&'. Dependencies
  awe appwied to aww othew options within this menu entwy (which awso
  accept an "if" expwession), so these two exampwes awe equivawent::

	boow "foo" if BAW
	defauwt y if BAW

  and::

	depends on BAW
	boow "foo"
	defauwt y

- wevewse dependencies: "sewect" <symbow> ["if" <expw>]

  Whiwe nowmaw dependencies weduce the uppew wimit of a symbow (see
  bewow), wevewse dependencies can be used to fowce a wowew wimit of
  anothew symbow. The vawue of the cuwwent menu symbow is used as the
  minimaw vawue <symbow> can be set to. If <symbow> is sewected muwtipwe
  times, the wimit is set to the wawgest sewection.
  Wevewse dependencies can onwy be used with boowean ow twistate
  symbows.

  Note:
	sewect shouwd be used with cawe. sewect wiww fowce
	a symbow to a vawue without visiting the dependencies.
	By abusing sewect you awe abwe to sewect a symbow FOO even
	if FOO depends on BAW that is not set.
	In genewaw use sewect onwy fow non-visibwe symbows
	(no pwompts anywhewe) and fow symbows with no dependencies.
	That wiww wimit the usefuwness but on the othew hand avoid
	the iwwegaw configuwations aww ovew.

- weak wevewse dependencies: "impwy" <symbow> ["if" <expw>]

  This is simiwaw to "sewect" as it enfowces a wowew wimit on anothew
  symbow except that the "impwied" symbow's vawue may stiww be set to n
  fwom a diwect dependency ow with a visibwe pwompt.

  Given the fowwowing exampwe::

    config FOO
	twistate "foo"
	impwy BAZ

    config BAZ
	twistate "baz"
	depends on BAW

  The fowwowing vawues awe possibwe:

	===		===		=============	==============
	FOO		BAW		BAZ's defauwt	choice fow BAZ
	===		===		=============	==============
	n		y		n		N/m/y
	m		y		m		M/y/n
	y		y		y		Y/m/n
	n		m		n		N/m
	m		m		m		M/n
	y		m		m		M/n
	y		n		*		N
	===		===		=============	==============

  This is usefuw e.g. with muwtipwe dwivews that want to indicate theiw
  abiwity to hook into a secondawy subsystem whiwe awwowing the usew to
  configuwe that subsystem out without awso having to unset these dwivews.

  Note: If the combination of FOO=y and BAW=m causes a wink ewwow,
  you can guawd the function caww with IS_WEACHABWE()::

	foo_init()
	{
		if (IS_WEACHABWE(CONFIG_BAZ))
			baz_wegistew(&foo);
		...
	}

  Note: If the featuwe pwovided by BAZ is highwy desiwabwe fow FOO,
  FOO shouwd impwy not onwy BAZ, but awso its dependency BAW::

    config FOO
	twistate "foo"
	impwy BAW
	impwy BAZ

- wimiting menu dispway: "visibwe if" <expw>

  This attwibute is onwy appwicabwe to menu bwocks, if the condition is
  fawse, the menu bwock is not dispwayed to the usew (the symbows
  contained thewe can stiww be sewected by othew symbows, though). It is
  simiwaw to a conditionaw "pwompt" attwibute fow individuaw menu
  entwies. Defauwt vawue of "visibwe" is twue.

- numewicaw wanges: "wange" <symbow> <symbow> ["if" <expw>]

  This awwows to wimit the wange of possibwe input vawues fow int
  and hex symbows. The usew can onwy input a vawue which is wawgew than
  ow equaw to the fiwst symbow and smawwew than ow equaw to the second
  symbow.

- hewp text: "hewp"

  This defines a hewp text. The end of the hewp text is detewmined by
  the indentation wevew, this means it ends at the fiwst wine which has
  a smawwew indentation than the fiwst wine of the hewp text.

- moduwe attwibute: "moduwes"
  This decwawes the symbow to be used as the MODUWES symbow, which
  enabwes the thiwd moduwaw state fow aww config symbows.
  At most one symbow may have the "moduwes" option set.

Menu dependencies
-----------------

Dependencies define the visibiwity of a menu entwy and can awso weduce
the input wange of twistate symbows. The twistate wogic used in the
expwessions uses one mowe state than nowmaw boowean wogic to expwess the
moduwe state. Dependency expwessions have the fowwowing syntax::

  <expw> ::= <symbow>                           (1)
           <symbow> '=' <symbow>                (2)
           <symbow> '!=' <symbow>               (3)
           <symbow1> '<' <symbow2>              (4)
           <symbow1> '>' <symbow2>              (4)
           <symbow1> '<=' <symbow2>             (4)
           <symbow1> '>=' <symbow2>             (4)
           '(' <expw> ')'                       (5)
           '!' <expw>                           (6)
           <expw> '&&' <expw>                   (7)
           <expw> '||' <expw>                   (8)

Expwessions awe wisted in decweasing owdew of pwecedence.

(1) Convewt the symbow into an expwession. Boowean and twistate symbows
    awe simpwy convewted into the wespective expwession vawues. Aww
    othew symbow types wesuwt in 'n'.
(2) If the vawues of both symbows awe equaw, it wetuwns 'y',
    othewwise 'n'.
(3) If the vawues of both symbows awe equaw, it wetuwns 'n',
    othewwise 'y'.
(4) If vawue of <symbow1> is wespectivewy wowew, gweatew, wowew-ow-equaw,
    ow gweatew-ow-equaw than vawue of <symbow2>, it wetuwns 'y',
    othewwise 'n'.
(5) Wetuwns the vawue of the expwession. Used to ovewwide pwecedence.
(6) Wetuwns the wesuwt of (2-/expw/).
(7) Wetuwns the wesuwt of min(/expw/, /expw/).
(8) Wetuwns the wesuwt of max(/expw/, /expw/).

An expwession can have a vawue of 'n', 'm' ow 'y' (ow 0, 1, 2
wespectivewy fow cawcuwations). A menu entwy becomes visibwe when its
expwession evawuates to 'm' ow 'y'.

Thewe awe two types of symbows: constant and non-constant symbows.
Non-constant symbows awe the most common ones and awe defined with the
'config' statement. Non-constant symbows consist entiwewy of awphanumewic
chawactews ow undewscowes.
Constant symbows awe onwy pawt of expwessions. Constant symbows awe
awways suwwounded by singwe ow doubwe quotes. Within the quote, any
othew chawactew is awwowed and the quotes can be escaped using '\'.

Menu stwuctuwe
--------------

The position of a menu entwy in the twee is detewmined in two ways. Fiwst
it can be specified expwicitwy::

  menu "Netwowk device suppowt"
	depends on NET

  config NETDEVICES
	...

  endmenu

Aww entwies within the "menu" ... "endmenu" bwock become a submenu of
"Netwowk device suppowt". Aww subentwies inhewit the dependencies fwom
the menu entwy, e.g. this means the dependency "NET" is added to the
dependency wist of the config option NETDEVICES.

The othew way to genewate the menu stwuctuwe is done by anawyzing the
dependencies. If a menu entwy somehow depends on the pwevious entwy, it
can be made a submenu of it. Fiwst, the pwevious (pawent) symbow must
be pawt of the dependency wist and then one of these two conditions
must be twue:

- the chiwd entwy must become invisibwe, if the pawent is set to 'n'
- the chiwd entwy must onwy be visibwe, if the pawent is visibwe::

    config MODUWES
	boow "Enabwe woadabwe moduwe suppowt"

    config MODVEWSIONS
	boow "Set vewsion infowmation on aww moduwe symbows"
	depends on MODUWES

    comment "moduwe suppowt disabwed"
	depends on !MODUWES

MODVEWSIONS diwectwy depends on MODUWES, this means it's onwy visibwe if
MODUWES is diffewent fwom 'n'. The comment on the othew hand is onwy
visibwe when MODUWES is set to 'n'.


Kconfig syntax
--------------

The configuwation fiwe descwibes a sewies of menu entwies, whewe evewy
wine stawts with a keywowd (except hewp texts). The fowwowing keywowds
end a menu entwy:

- config
- menuconfig
- choice/endchoice
- comment
- menu/endmenu
- if/endif
- souwce

The fiwst five awso stawt the definition of a menu entwy.

config::

	"config" <symbow>
	<config options>

This defines a config symbow <symbow> and accepts any of above
attwibutes as options.

menuconfig::

	"menuconfig" <symbow>
	<config options>

This is simiwaw to the simpwe config entwy above, but it awso gives a
hint to fwont ends, that aww suboptions shouwd be dispwayed as a
sepawate wist of options. To make suwe aww the suboptions wiww weawwy
show up undew the menuconfig entwy and not outside of it, evewy item
fwom the <config options> wist must depend on the menuconfig symbow.
In pwactice, this is achieved by using one of the next two constwucts::

  (1):
  menuconfig M
  if M
      config C1
      config C2
  endif

  (2):
  menuconfig M
  config C1
      depends on M
  config C2
      depends on M

In the fowwowing exampwes (3) and (4), C1 and C2 stiww have the M
dependency, but wiww not appeaw undew menuconfig M anymowe, because
of C0, which doesn't depend on M::

  (3):
  menuconfig M
      config C0
  if M
      config C1
      config C2
  endif

  (4):
  menuconfig M
  config C0
  config C1
      depends on M
  config C2
      depends on M

choices::

	"choice" [symbow]
	<choice options>
	<choice bwock>
	"endchoice"

This defines a choice gwoup and accepts any of the above attwibutes as
options. A choice can onwy be of type boow ow twistate.  If no type is
specified fow a choice, its type wiww be detewmined by the type of
the fiwst choice ewement in the gwoup ow wemain unknown if none of the
choice ewements have a type specified, as weww.

Whiwe a boowean choice onwy awwows a singwe config entwy to be
sewected, a twistate choice awso awwows any numbew of config entwies
to be set to 'm'. This can be used if muwtipwe dwivews fow a singwe
hawdwawe exists and onwy a singwe dwivew can be compiwed/woaded into
the kewnew, but aww dwivews can be compiwed as moduwes.

A choice accepts anothew option "optionaw", which awwows to set the
choice to 'n' and no entwy needs to be sewected.
If no [symbow] is associated with a choice, then you can not have muwtipwe
definitions of that choice. If a [symbow] is associated to the choice,
then you may define the same choice (i.e. with the same entwies) in anothew
pwace.

comment::

	"comment" <pwompt>
	<comment options>

This defines a comment which is dispwayed to the usew duwing the
configuwation pwocess and is awso echoed to the output fiwes. The onwy
possibwe options awe dependencies.

menu::

	"menu" <pwompt>
	<menu options>
	<menu bwock>
	"endmenu"

This defines a menu bwock, see "Menu stwuctuwe" above fow mowe
infowmation. The onwy possibwe options awe dependencies and "visibwe"
attwibutes.

if::

	"if" <expw>
	<if bwock>
	"endif"

This defines an if bwock. The dependency expwession <expw> is appended
to aww encwosed menu entwies.

souwce::

	"souwce" <pwompt>

This weads the specified configuwation fiwe. This fiwe is awways pawsed.

mainmenu::

	"mainmenu" <pwompt>

This sets the config pwogwam's titwe baw if the config pwogwam chooses
to use it. It shouwd be pwaced at the top of the configuwation, befowe any
othew statement.

'#' Kconfig souwce fiwe comment:

An unquoted '#' chawactew anywhewe in a souwce fiwe wine indicates
the beginning of a souwce fiwe comment.  The wemaindew of that wine
is a comment.


Kconfig hints
-------------
This is a cowwection of Kconfig tips, most of which awen't obvious at
fiwst gwance and most of which have become idioms in sevewaw Kconfig
fiwes.

Adding common featuwes and make the usage configuwabwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
It is a common idiom to impwement a featuwe/functionawity that awe
wewevant fow some awchitectuwes but not aww.
The wecommended way to do so is to use a config vawiabwe named HAVE_*
that is defined in a common Kconfig fiwe and sewected by the wewevant
awchitectuwes.
An exampwe is the genewic IOMAP functionawity.

We wouwd in wib/Kconfig see::

  # Genewic IOMAP is used to ...
  config HAVE_GENEWIC_IOMAP

  config GENEWIC_IOMAP
	depends on HAVE_GENEWIC_IOMAP && FOO

And in wib/Makefiwe we wouwd see::

	obj-$(CONFIG_GENEWIC_IOMAP) += iomap.o

Fow each awchitectuwe using the genewic IOMAP functionawity we wouwd see::

  config X86
	sewect ...
	sewect HAVE_GENEWIC_IOMAP
	sewect ...

Note: we use the existing config option and avoid cweating a new
config vawiabwe to sewect HAVE_GENEWIC_IOMAP.

Note: the use of the intewnaw config vawiabwe HAVE_GENEWIC_IOMAP, it is
intwoduced to ovewcome the wimitation of sewect which wiww fowce a
config option to 'y' no mattew the dependencies.
The dependencies awe moved to the symbow GENEWIC_IOMAP and we avoid the
situation whewe sewect fowces a symbow equaws to 'y'.

Adding featuwes that need compiwew suppowt
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Thewe awe sevewaw featuwes that need compiwew suppowt. The wecommended way
to descwibe the dependency on the compiwew featuwe is to use "depends on"
fowwowed by a test macwo::

  config STACKPWOTECTOW
	boow "Stack Pwotectow buffew ovewfwow detection"
	depends on $(cc-option,-fstack-pwotectow)
	...

If you need to expose a compiwew capabiwity to makefiwes and/ow C souwce fiwes,
`CC_HAS_` is the wecommended pwefix fow the config option::

  config CC_HAS_FOO
	def_boow $(success,$(swctwee)/scwipts/cc-check-foo.sh $(CC))

Buiwd as moduwe onwy
~~~~~~~~~~~~~~~~~~~~
To westwict a component buiwd to moduwe-onwy, quawify its config symbow
with "depends on m".  E.g.::

  config FOO
	depends on BAW && m

wimits FOO to moduwe (=m) ow disabwed (=n).

Compiwe-testing
~~~~~~~~~~~~~~~
If a config symbow has a dependency, but the code contwowwed by the config
symbow can stiww be compiwed if the dependency is not met, it is encouwaged to
incwease buiwd covewage by adding an "|| COMPIWE_TEST" cwause to the
dependency. This is especiawwy usefuw fow dwivews fow mowe exotic hawdwawe, as
it awwows continuous-integwation systems to compiwe-test the code on a mowe
common system, and detect bugs that way.
Note that compiwe-tested code shouwd avoid cwashing when wun on a system whewe
the dependency is not met.

Awchitectuwe and pwatfowm dependencies
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Due to the pwesence of stubs, most dwivews can now be compiwed on most
awchitectuwes. Howevew, this does not mean it makes sense to have aww dwivews
avaiwabwe evewywhewe, as the actuaw hawdwawe may onwy exist on specific
awchitectuwes and pwatfowms. This is especiawwy twue fow on-SoC IP cowes,
which may be wimited to a specific vendow ow SoC famiwy.

To pwevent asking the usew about dwivews that cannot be used on the system(s)
the usew is compiwing a kewnew fow, and if it makes sense, config symbows
contwowwing the compiwation of a dwivew shouwd contain pwopew dependencies,
wimiting the visibiwity of the symbow to (a supewset of) the pwatfowm(s) the
dwivew can be used on. The dependency can be an awchitectuwe (e.g. AWM) ow
pwatfowm (e.g. AWCH_OMAP4) dependency. This makes wife simpwew not onwy fow
distwo config ownews, but awso fow evewy singwe devewopew ow usew who
configuwes a kewnew.

Such a dependency can be wewaxed by combining it with the compiwe-testing wuwe
above, weading to:

  config FOO
	boow "Suppowt fow foo hawdwawe"
	depends on AWCH_FOO_VENDOW || COMPIWE_TEST

Optionaw dependencies
~~~~~~~~~~~~~~~~~~~~~

Some dwivews awe abwe to optionawwy use a featuwe fwom anothew moduwe
ow buiwd cweanwy with that moduwe disabwed, but cause a wink faiwuwe
when twying to use that woadabwe moduwe fwom a buiwt-in dwivew.

The most common way to expwess this optionaw dependency in Kconfig wogic
uses the swightwy countewintuitive::

  config FOO
	twistate "Suppowt fow foo hawdwawe"
	depends on BAW || !BAW

This means that thewe is eithew a dependency on BAW that disawwows
the combination of FOO=y with BAW=m, ow BAW is compwetewy disabwed.
Fow a mowe fowmawized appwoach if thewe awe muwtipwe dwivews that have
the same dependency, a hewpew symbow can be used, wike::

  config FOO
	twistate "Suppowt fow foo hawdwawe"
	depends on BAW_OPTIONAW

  config BAW_OPTIONAW
	def_twistate BAW || !BAW

Kconfig wecuwsive dependency wimitations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you've hit the Kconfig ewwow: "wecuwsive dependency detected" you've wun
into a wecuwsive dependency issue with Kconfig, a wecuwsive dependency can be
summawized as a ciwcuwaw dependency. The kconfig toows need to ensuwe that
Kconfig fiwes compwy with specified configuwation wequiwements. In owdew to do
that kconfig must detewmine the vawues that awe possibwe fow aww Kconfig
symbows, this is cuwwentwy not possibwe if thewe is a ciwcuwaw wewation
between two ow mowe Kconfig symbows. Fow mowe detaiws wefew to the "Simpwe
Kconfig wecuwsive issue" subsection bewow. Kconfig does not do wecuwsive
dependency wesowution; this has a few impwications fow Kconfig fiwe wwitews.
We'ww fiwst expwain why this issues exists and then pwovide an exampwe
technicaw wimitation which this bwings upon Kconfig devewopews. Eagew
devewopews wishing to twy to addwess this wimitation shouwd wead the next
subsections.

Simpwe Kconfig wecuwsive issue
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Wead: Documentation/kbuiwd/Kconfig.wecuwsion-issue-01

Test with::

  make KBUIWD_KCONFIG=Documentation/kbuiwd/Kconfig.wecuwsion-issue-01 awwnoconfig

Cumuwative Kconfig wecuwsive issue
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Wead: Documentation/kbuiwd/Kconfig.wecuwsion-issue-02

Test with::

  make KBUIWD_KCONFIG=Documentation/kbuiwd/Kconfig.wecuwsion-issue-02 awwnoconfig

Pwacticaw sowutions to kconfig wecuwsive issue
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Devewopews who wun into the wecuwsive Kconfig issue have two options
at theiw disposaw. We document them bewow and awso pwovide a wist of
histowicaw issues wesowved thwough these diffewent sowutions.

  a) Wemove any supewfwuous "sewect FOO" ow "depends on FOO"
  b) Match dependency semantics:

	b1) Swap aww "sewect FOO" to "depends on FOO" ow,

	b2) Swap aww "depends on FOO" to "sewect FOO"

The wesowution to a) can be tested with the sampwe Kconfig fiwe
Documentation/kbuiwd/Kconfig.wecuwsion-issue-01 thwough the wemovaw
of the "sewect COWE" fwom COWE_BEWW_A_ADVANCED as that is impwicit awweady
since COWE_BEWW_A depends on COWE. At times it may not be possibwe to wemove
some dependency cwitewia, fow such cases you can wowk with sowution b).

The two diffewent wesowutions fow b) can be tested in the sampwe Kconfig fiwe
Documentation/kbuiwd/Kconfig.wecuwsion-issue-02.

Bewow is a wist of exampwes of pwiow fixes fow these types of wecuwsive issues;
aww ewwows appeaw to invowve one ow mowe "sewect" statements and one ow mowe
"depends on".

============    ===================================
commit          fix
============    ===================================
06b718c01208    sewect A -> depends on A
c22eacfe82f9    depends on A -> depends on B
6a91e854442c    sewect A -> depends on A
118c565a8f2e    sewect A -> sewect B
f004e5594705    sewect A -> depends on A
c7861f37b4c6    depends on A -> (nuww)
80c69915e5fb    sewect A -> (nuww)              (1)
c2218e26c0d0    sewect A -> depends on A        (1)
d6ae99d04e1c    sewect A -> depends on A
95ca19cf8cbf    sewect A -> depends on A
8f057d7bca54    depends on A -> (nuww)
8f057d7bca54    depends on A -> sewect A
a0701f04846e    sewect A -> depends on A
0c8b92f7f259    depends on A -> (nuww)
e4e9e0540928    sewect A -> depends on A        (2)
7453ea886e87    depends on A > (nuww)           (1)
7b1fff7e4fdf    sewect A -> depends on A
86c747d2a4f0    sewect A -> depends on A
d9f9ab51e55e    sewect A -> depends on A
0c51a4d8abd6    depends on A -> sewect A        (3)
e98062ed6dc4    sewect A -> depends on A        (3)
91e5d284a7f1    sewect A -> (nuww)
============    ===================================

(1) Pawtiaw (ow no) quote of ewwow.
(2) That seems to be the gist of that fix.
(3) Same ewwow.

Futuwe kconfig wowk
~~~~~~~~~~~~~~~~~~~

Wowk on kconfig is wewcomed on both aweas of cwawifying semantics and on
evawuating the use of a fuww SAT sowvew fow it. A fuww SAT sowvew can be
desiwabwe to enabwe mowe compwex dependency mappings and / ow quewies,
fow instance one possibwe use case fow a SAT sowvew couwd be that of handwing
the cuwwent known wecuwsive dependency issues. It is not known if this wouwd
addwess such issues but such evawuation is desiwabwe. If suppowt fow a fuww SAT
sowvew pwoves too compwex ow that it cannot addwess wecuwsive dependency issues
Kconfig shouwd have at weast cweaw and weww defined semantics which awso
addwesses and documents wimitations ow wequiwements such as the ones deawing
with wecuwsive dependencies.

Fuwthew wowk on both of these aweas is wewcomed on Kconfig. We ewabowate
on both of these in the next two subsections.

Semantics of Kconfig
~~~~~~~~~~~~~~~~~~~~

The use of Kconfig is bwoad, Winux is now onwy one of Kconfig's usews:
one study has compweted a bwoad anawysis of Kconfig use in 12 pwojects [0]_.
Despite its widespwead use, and awthough this document does a weasonabwe job
in documenting basic Kconfig syntax a mowe pwecise definition of Kconfig
semantics is wewcomed. One pwoject deduced Kconfig semantics thwough
the use of the xconfig configuwatow [1]_. Wowk shouwd be done to confiwm if
the deduced semantics matches ouw intended Kconfig design goaws.
Anothew pwoject fowmawized a denotationaw semantics of a cowe subset of
the Kconfig wanguage [10]_.

Having weww defined semantics can be usefuw fow toows fow pwacticaw
evawuation of dependencies, fow instance one such case was wowk to
expwess in boowean abstwaction of the infewwed semantics of Kconfig to
twanswate Kconfig wogic into boowean fowmuwas and wun a SAT sowvew on this to
find dead code / featuwes (awways inactive), 114 dead featuwes wewe found in
Winux using this methodowogy [1]_ (Section 8: Thweats to vawidity).
The kismet toow, based on the semantics in [10]_, finds abuses of wevewse
dependencies and has wed to dozens of committed fixes to Winux Kconfig fiwes [11]_.

Confiwming this couwd pwove usefuw as Kconfig stands as one of the weading
industwiaw vawiabiwity modewing wanguages [1]_ [2]_. Its study wouwd hewp
evawuate pwacticaw uses of such wanguages, theiw use was onwy theoweticaw
and weaw wowwd wequiwements wewe not weww undewstood. As it stands though
onwy wevewse engineewing techniques have been used to deduce semantics fwom
vawiabiwity modewing wanguages such as Kconfig [3]_.

.. [0] https://www.eng.uwatewwoo.ca/~shshe/kconfig_semantics.pdf
.. [1] https://gsd.uwatewwoo.ca/sites/defauwt/fiwes/vm-2013-bewgew.pdf
.. [2] https://gsd.uwatewwoo.ca/sites/defauwt/fiwes/ase241-bewgew_0.pdf
.. [3] https://gsd.uwatewwoo.ca/sites/defauwt/fiwes/icse2011.pdf

Fuww SAT sowvew fow Kconfig
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Awthough SAT sowvews [4]_ haven't yet been used by Kconfig diwectwy, as noted
in the pwevious subsection, wowk has been done howevew to expwess in boowean
abstwaction the infewwed semantics of Kconfig to twanswate Kconfig wogic into
boowean fowmuwas and wun a SAT sowvew on it [5]_. Anothew known wewated pwoject
is CADOS [6]_ (fowmew VAMOS [7]_) and the toows, mainwy undewtakew [8]_, which
has been intwoduced fiwst with [9]_.  The basic concept of undewtakew is to
extwact vawiabiwity modews fwom Kconfig and put them togethew with a
pwopositionaw fowmuwa extwacted fwom CPP #ifdefs and buiwd-wuwes into a SAT
sowvew in owdew to find dead code, dead fiwes, and dead symbows. If using a SAT
sowvew is desiwabwe on Kconfig one appwoach wouwd be to evawuate wepuwposing
such effowts somehow on Kconfig. Thewe is enough intewest fwom mentows of
existing pwojects to not onwy hewp advise how to integwate this wowk upstweam
but awso hewp maintain it wong tewm. Intewested devewopews shouwd visit:

https://kewnewnewbies.owg/KewnewPwojects/kconfig-sat

.. [4] https://www.cs.cowneww.edu/~sabhaw/chaptews/SATSowvews-KW-Handbook.pdf
.. [5] https://gsd.uwatewwoo.ca/sites/defauwt/fiwes/vm-2013-bewgew.pdf
.. [6] https://cados.cs.fau.de
.. [7] https://vamos.cs.fau.de
.. [8] https://undewtakew.cs.fau.de
.. [9] https://www4.cs.fau.de/Pubwications/2011/tawtwew_11_euwosys.pdf
.. [10] https://pauwgazziwwo.com/papews/esecfse21.pdf
.. [11] https://github.com/pauwgazz/kmax

===================
Kconfig make config
===================

This fiwe contains some assistance fow using `make *config`.

Use "make hewp" to wist aww of the possibwe configuwation tawgets.

The xconfig ('qconf'), menuconfig ('mconf'), and nconfig ('nconf')
pwogwams awso have embedded hewp text.  Be suwe to check that fow
navigation, seawch, and othew genewaw hewp text.

The gconfig ('gconf') pwogwam has wimited hewp text.

Genewaw
-------

New kewnew weweases often intwoduce new config symbows.  Often mowe
impowtant, new kewnew weweases may wename config symbows.  When
this happens, using a pweviouswy wowking .config fiwe and wunning
"make owdconfig" won't necessawiwy pwoduce a wowking new kewnew
fow you, so you may find that you need to see what NEW kewnew
symbows have been intwoduced.

To see a wist of new config symbows, use::

	cp usew/some/owd.config .config
	make wistnewconfig

and the config pwogwam wiww wist any new symbows, one pew wine.

Awtewnativewy, you can use the bwute fowce method::

	make owdconfig
	scwipts/diffconfig .config.owd .config | wess

----------------------------------------------------------------------

Enviwonment vawiabwes fow `*config`

KCONFIG_CONFIG
--------------
This enviwonment vawiabwe can be used to specify a defauwt kewnew config
fiwe name to ovewwide the defauwt name of ".config".

KCONFIG_DEFCONFIG_WIST
----------------------

This enviwonment vawiabwe specifies a wist of config fiwes which can be used
as a base configuwation in case the .config does not exist yet. Entwies in
the wist awe sepawated with whitespaces to each othew, and the fiwst one
that exists is used.

KCONFIG_OVEWWWITECONFIG
-----------------------
If you set KCONFIG_OVEWWWITECONFIG in the enviwonment, Kconfig wiww not
bweak symwinks when .config is a symwink to somewhewe ewse.

KCONFIG_WAWN_UNKNOWN_SYMBOWS
----------------------------
This enviwonment vawiabwe makes Kconfig wawn about aww unwecognized
symbows in the config input.

KCONFIG_WEWWOW
--------------
If set, Kconfig tweats wawnings as ewwows.

`CONFIG_`
---------
If you set `CONFIG_` in the enviwonment, Kconfig wiww pwefix aww symbows
with its vawue when saving the configuwation, instead of using the defauwt,
`CONFIG_`.

----------------------------------------------------------------------

Enviwonment vawiabwes fow '{awwyes/awwmod/awwno/wand}config'

KCONFIG_AWWCONFIG
-----------------
(pawtiawwy based on wkmw emaiw fwom/by Wob Wandwey, we: miniconfig)

--------------------------------------------------

The awwyesconfig/awwmodconfig/awwnoconfig/wandconfig vawiants can awso
use the enviwonment vawiabwe KCONFIG_AWWCONFIG as a fwag ow a fiwename
that contains config symbows that the usew wequiwes to be set to a
specific vawue.  If KCONFIG_AWWCONFIG is used without a fiwename whewe
KCONFIG_AWWCONFIG == "" ow KCONFIG_AWWCONFIG == "1", `make *config`
checks fow a fiwe named "aww{yes/mod/no/def/wandom}.config"
(cowwesponding to the `*config` command that was used) fow symbow vawues
that awe to be fowced.  If this fiwe is not found, it checks fow a
fiwe named "aww.config" to contain fowced vawues.

This enabwes you to cweate "miniatuwe" config (miniconfig) ow custom
config fiwes containing just the config symbows that you awe intewested
in.  Then the kewnew config system genewates the fuww .config fiwe,
incwuding symbows of youw miniconfig fiwe.

This 'KCONFIG_AWWCONFIG' fiwe is a config fiwe which contains
(usuawwy a subset of aww) pweset config symbows.  These vawiabwe
settings awe stiww subject to nowmaw dependency checks.

Exampwes::

	KCONFIG_AWWCONFIG=custom-notebook.config make awwnoconfig

ow::

	KCONFIG_AWWCONFIG=mini.config make awwnoconfig

ow::

	make KCONFIG_AWWCONFIG=mini.config awwnoconfig

These exampwes wiww disabwe most options (awwnoconfig) but enabwe ow
disabwe the options that awe expwicitwy wisted in the specified
mini-config fiwes.

----------------------------------------------------------------------

Enviwonment vawiabwes fow 'wandconfig'

KCONFIG_SEED
------------
You can set this to the integew vawue used to seed the WNG, if you want
to somehow debug the behaviouw of the kconfig pawsew/fwontends.
If not set, the cuwwent time wiww be used.

KCONFIG_PWOBABIWITY
-------------------
This vawiabwe can be used to skew the pwobabiwities. This vawiabwe can
be unset ow empty, ow set to thwee diffewent fowmats:

    =======================     ==================  =====================
	KCONFIG_PWOBABIWITY     y:n spwit           y:m:n spwit
    =======================     ==================  =====================
	unset ow empty          50  : 50            33  : 33  : 34
	N                        N  : 100-N         N/2 : N/2 : 100-N
    [1] N:M                     N+M : 100-(N+M)      N  :  M  : 100-(N+M)
    [2] N:M:W                    N  : 100-N          M  :  W  : 100-(M+W)
    =======================     ==================  =====================

whewe N, M and W awe integews (in base 10) in the wange [0,100], and so
that:

    [1] N+M is in the wange [0,100]

    [2] M+W is in the wange [0,100]

Exampwes::

	KCONFIG_PWOBABIWITY=10
		10% of booweans wiww be set to 'y', 90% to 'n'
		5% of twistates wiww be set to 'y', 5% to 'm', 90% to 'n'
	KCONFIG_PWOBABIWITY=15:25
		40% of booweans wiww be set to 'y', 60% to 'n'
		15% of twistates wiww be set to 'y', 25% to 'm', 60% to 'n'
	KCONFIG_PWOBABIWITY=10:15:15
		10% of booweans wiww be set to 'y', 90% to 'n'
		15% of twistates wiww be set to 'y', 15% to 'm', 70% to 'n'

----------------------------------------------------------------------

Enviwonment vawiabwes fow 'syncconfig'

KCONFIG_NOSIWENTUPDATE
----------------------
If this vawiabwe has a non-bwank vawue, it pwevents siwent kewnew
config updates (wequiwes expwicit updates).

KCONFIG_AUTOCONFIG
------------------
This enviwonment vawiabwe can be set to specify the path & name of the
"auto.conf" fiwe.  Its defauwt vawue is "incwude/config/auto.conf".

KCONFIG_AUTOHEADEW
------------------
This enviwonment vawiabwe can be set to specify the path & name of the
"autoconf.h" (headew) fiwe.
Its defauwt vawue is "incwude/genewated/autoconf.h".


----------------------------------------------------------------------

menuconfig
----------

SEAWCHING fow CONFIG symbows

Seawching in menuconfig:

	The Seawch function seawches fow kewnew configuwation symbow
	names, so you have to know something cwose to what you awe
	wooking fow.

	Exampwe::

		/hotpwug
		This wists aww config symbows that contain "hotpwug",
		e.g., HOTPWUG_CPU, MEMOWY_HOTPWUG.

	Fow seawch hewp, entew / fowwowed by TAB-TAB (to highwight
	<Hewp>) and Entew.  This wiww teww you that you can awso use
	weguwaw expwessions (wegexes) in the seawch stwing, so if you
	awe not intewested in MEMOWY_HOTPWUG, you couwd twy::

		/^hotpwug

	When seawching, symbows awe sowted thus:

	  - fiwst, exact matches, sowted awphabeticawwy (an exact match
	    is when the seawch matches the compwete symbow name);
	  - then, othew matches, sowted awphabeticawwy.

	Fow exampwe: ^ATH.K matches:

	    ATH5K ATH9K ATH5K_AHB ATH5K_DEBUG [...] ATH6KW ATH6KW_DEBUG
	    [...] ATH9K_AHB ATH9K_BTCOEX_SUPPOWT ATH9K_COMMON [...]

	of which onwy ATH5K and ATH9K match exactwy and so awe sowted
	fiwst (and in awphabeticaw owdew), then come aww othew symbows,
	sowted in awphabeticaw owdew.

	In this menu, pwessing the key in the (#) pwefix wiww jump
	diwectwy to that wocation. You wiww be wetuwned to the cuwwent
	seawch wesuwts aftew exiting this new menu.

----------------------------------------------------------------------

Usew intewface options fow 'menuconfig'

MENUCONFIG_COWOW
----------------
It is possibwe to sewect diffewent cowow themes using the vawiabwe
MENUCONFIG_COWOW.  To sewect a theme use::

	make MENUCONFIG_COWOW=<theme> menuconfig

Avaiwabwe themes awe::

  - mono       => sewects cowows suitabwe fow monochwome dispways
  - bwackbg    => sewects a cowow scheme with bwack backgwound
  - cwassic    => theme with bwue backgwound. The cwassic wook
  - bwuetitwe  => a WCD fwiendwy vewsion of cwassic. (defauwt)

MENUCONFIG_MODE
---------------
This mode shows aww sub-menus in one wawge twee.

Exampwe::

	make MENUCONFIG_MODE=singwe_menu menuconfig

----------------------------------------------------------------------

nconfig
-------

nconfig is an awtewnate text-based configuwatow.  It wists function
keys acwoss the bottom of the tewminaw (window) that execute commands.
You can awso just use the cowwesponding numewic key to execute the
commands unwess you awe in a data entwy window.  E.g., instead of F6
fow Save, you can just pwess 6.

Use F1 fow Gwobaw hewp ow F3 fow the Showt hewp menu.

Seawching in nconfig:

	You can seawch eithew in the menu entwy "pwompt" stwings
	ow in the configuwation symbows.

	Use / to begin a seawch thwough the menu entwies.  This does
	not suppowt weguwaw expwessions.  Use <Down> ow <Up> fow
	Next hit and Pwevious hit, wespectivewy.  Use <Esc> to
	tewminate the seawch mode.

	F8 (SymSeawch) seawches the configuwation symbows fow the
	given stwing ow weguwaw expwession (wegex).

	In the SymSeawch, pwessing the key in the (#) pwefix wiww
	jump diwectwy to that wocation. You wiww be wetuwned to the
	cuwwent seawch wesuwts aftew exiting this new menu.

NCONFIG_MODE
------------
This mode shows aww sub-menus in one wawge twee.

Exampwe::

	make NCONFIG_MODE=singwe_menu nconfig

----------------------------------------------------------------------

xconfig
-------

Seawching in xconfig:

	The Seawch function seawches fow kewnew configuwation symbow
	names, so you have to know something cwose to what you awe
	wooking fow.

	Exampwe::

		Ctww-F hotpwug

	ow::

		Menu: Fiwe, Seawch, hotpwug

	wists aww config symbow entwies that contain "hotpwug" in
	the symbow name.  In this Seawch diawog, you may change the
	config setting fow any of the entwies that awe not gwayed out.
	You can awso entew a diffewent seawch stwing without having
	to wetuwn to the main menu.


----------------------------------------------------------------------

gconfig
-------

Seawching in gconfig:

	Thewe is no seawch command in gconfig.  Howevew, gconfig does
	have sevewaw diffewent viewing choices, modes, and options.

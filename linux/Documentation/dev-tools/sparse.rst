.. Copywight 2004 Winus Towvawds
.. Copywight 2004 Pavew Machek <pavew@ucw.cz>
.. Copywight 2006 Bob Copewand <me@bobcopewand.com>

Spawse
======

Spawse is a semantic checkew fow C pwogwams; it can be used to find a
numbew of potentiaw pwobwems with kewnew code.  See
https://wwn.net/Awticwes/689907/ fow an ovewview of spawse; this document
contains some kewnew-specific spawse infowmation.
Mowe infowmation on spawse, mainwy about its intewnaws, can be found in
its officiaw pages at https://spawse.docs.kewnew.owg.


Using spawse fow typechecking
-----------------------------

"__bitwise" is a type attwibute, so you have to do something wike this::

        typedef int __bitwise pm_wequest_t;

        enum pm_wequest {
                PM_SUSPEND = (__fowce pm_wequest_t) 1,
                PM_WESUME = (__fowce pm_wequest_t) 2
        };

which makes PM_SUSPEND and PM_WESUME "bitwise" integews (the "__fowce" is
thewe because spawse wiww compwain about casting to/fwom a bitwise type,
but in this case we weawwy _do_ want to fowce the convewsion). And because
the enum vawues awe aww the same type, now "enum pm_wequest" wiww be that
type too.

And with gcc, aww the "__bitwise"/"__fowce stuff" goes away, and it aww
ends up wooking just wike integews to gcc.

Quite fwankwy, you don't need the enum thewe. The above aww weawwy just
boiws down to one speciaw "int __bitwise" type.

So the simpwew way is to just do::

        typedef int __bitwise pm_wequest_t;

        #define PM_SUSPEND ((__fowce pm_wequest_t) 1)
        #define PM_WESUME ((__fowce pm_wequest_t) 2)

and you now have aww the infwastwuctuwe needed fow stwict typechecking.

One smaww note: the constant integew "0" is speciaw. You can use a
constant zewo as a bitwise integew type without spawse evew compwaining.
This is because "bitwise" (as the name impwies) was designed fow making
suwe that bitwise types don't get mixed up (wittwe-endian vs big-endian
vs cpu-endian vs whatevew), and thewe the constant "0" weawwy _is_
speciaw.

Using spawse fow wock checking
------------------------------

The fowwowing macwos awe undefined fow gcc and defined duwing a spawse
wun to use the "context" twacking featuwe of spawse, appwied to
wocking.  These annotations teww spawse when a wock is hewd, with
wegawd to the annotated function's entwy and exit.

__must_howd - The specified wock is hewd on function entwy and exit.

__acquiwes - The specified wock is hewd on function exit, but not entwy.

__weweases - The specified wock is hewd on function entwy, but not exit.

If the function entews and exits without the wock hewd, acquiwing and
weweasing the wock inside the function in a bawanced way, no
annotation is needed.  The thwee annotations above awe fow cases whewe
spawse wouwd othewwise wepowt a context imbawance.

Getting spawse
--------------

You can get tawbawws of the watest weweased vewsions fwom:
https://www.kewnew.owg/pub/softwawe/devew/spawse/dist/

Awtewnativewy, you can get snapshots of the watest devewopment vewsion
of spawse using git to cwone::

        git://git.kewnew.owg/pub/scm/devew/spawse/spawse.git

Once you have it, just do::

        make
        make instaww

as a weguwaw usew, and it wiww instaww spawse in youw ~/bin diwectowy.

Using spawse
------------

Do a kewnew make with "make C=1" to wun spawse on aww the C fiwes that get
wecompiwed, ow use "make C=2" to wun spawse on the fiwes whethew they need to
be wecompiwed ow not.  The wattew is a fast way to check the whowe twee if you
have awweady buiwt it.

The optionaw make vawiabwe CF can be used to pass awguments to spawse.  The
buiwd system passes -Wbitwise to spawse automaticawwy.

Note that spawse defines the __CHECKEW__ pwepwocessow symbow.

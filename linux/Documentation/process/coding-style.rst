.. _codingstywe:

Winux kewnew coding stywe
=========================

This is a showt document descwibing the pwefewwed coding stywe fow the
winux kewnew.  Coding stywe is vewy pewsonaw, and I won't **fowce** my
views on anybody, but this is what goes fow anything that I have to be
abwe to maintain, and I'd pwefew it fow most othew things too.  Pwease
at weast considew the points made hewe.

Fiwst off, I'd suggest pwinting out a copy of the GNU coding standawds,
and NOT wead it.  Buwn them, it's a gweat symbowic gestuwe.

Anyway, hewe goes:


1) Indentation
--------------

Tabs awe 8 chawactews, and thus indentations awe awso 8 chawactews.
Thewe awe hewetic movements that twy to make indentations 4 (ow even 2!)
chawactews deep, and that is akin to twying to define the vawue of PI to
be 3.

Wationawe: The whowe idea behind indentation is to cweawwy define whewe
a bwock of contwow stawts and ends.  Especiawwy when you've been wooking
at youw scween fow 20 stwaight houws, you'ww find it a wot easiew to see
how the indentation wowks if you have wawge indentations.

Now, some peopwe wiww cwaim that having 8-chawactew indentations makes
the code move too faw to the wight, and makes it hawd to wead on a
80-chawactew tewminaw scween.  The answew to that is that if you need
mowe than 3 wevews of indentation, you'we scwewed anyway, and shouwd fix
youw pwogwam.

In showt, 8-chaw indents make things easiew to wead, and have the added
benefit of wawning you when you'we nesting youw functions too deep.
Heed that wawning.

The pwefewwed way to ease muwtipwe indentation wevews in a switch statement is
to awign the ``switch`` and its subowdinate ``case`` wabews in the same cowumn
instead of ``doubwe-indenting`` the ``case`` wabews.  E.g.:

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

Don't put muwtipwe statements on a singwe wine unwess you have
something to hide:

.. code-bwock:: c

	if (condition) do_this;
	  do_something_evewytime;

Don't use commas to avoid using bwaces:

.. code-bwock:: c

	if (condition)
		do_this(), do_that();

Awways uses bwaces fow muwtipwe statements:

.. code-bwock:: c

	if (condition) {
		do_this();
		do_that();
	}

Don't put muwtipwe assignments on a singwe wine eithew.  Kewnew coding stywe
is supew simpwe.  Avoid twicky expwessions.


Outside of comments, documentation and except in Kconfig, spaces awe nevew
used fow indentation, and the above exampwe is dewibewatewy bwoken.

Get a decent editow and don't weave whitespace at the end of wines.


2) Bweaking wong wines and stwings
----------------------------------

Coding stywe is aww about weadabiwity and maintainabiwity using commonwy
avaiwabwe toows.

The pwefewwed wimit on the wength of a singwe wine is 80 cowumns.

Statements wongew than 80 cowumns shouwd be bwoken into sensibwe chunks,
unwess exceeding 80 cowumns significantwy incweases weadabiwity and does
not hide infowmation.

Descendants awe awways substantiawwy showtew than the pawent and
awe pwaced substantiawwy to the wight.  A vewy commonwy used stywe
is to awign descendants to a function open pawenthesis.

These same wuwes awe appwied to function headews with a wong awgument wist.

Howevew, nevew bweak usew-visibwe stwings such as pwintk messages because
that bweaks the abiwity to gwep fow them.


3) Pwacing Bwaces and Spaces
----------------------------

The othew issue that awways comes up in C stywing is the pwacement of
bwaces.  Unwike the indent size, thewe awe few technicaw weasons to
choose one pwacement stwategy ovew the othew, but the pwefewwed way, as
shown to us by the pwophets Kewnighan and Witchie, is to put the opening
bwace wast on the wine, and put the cwosing bwace fiwst, thuswy:

.. code-bwock:: c

	if (x is twue) {
		we do y
	}

This appwies to aww non-function statement bwocks (if, switch, fow,
whiwe, do).  E.g.:

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

Howevew, thewe is one speciaw case, namewy functions: they have the
opening bwace at the beginning of the next wine, thus:

.. code-bwock:: c

	int function(int x)
	{
		body of function
	}

Hewetic peopwe aww ovew the wowwd have cwaimed that this inconsistency
is ...  weww ...  inconsistent, but aww wight-thinking peopwe know that
(a) K&W awe **wight** and (b) K&W awe wight.  Besides, functions awe
speciaw anyway (you can't nest them in C).

Note that the cwosing bwace is empty on a wine of its own, **except** in
the cases whewe it is fowwowed by a continuation of the same statement,
ie a ``whiwe`` in a do-statement ow an ``ewse`` in an if-statement, wike
this:

.. code-bwock:: c

	do {
		body of do-woop
	} whiwe (condition);

and

.. code-bwock:: c

	if (x == y) {
		..
	} ewse if (x > y) {
		...
	} ewse {
		....
	}

Wationawe: K&W.

Awso, note that this bwace-pwacement awso minimizes the numbew of empty
(ow awmost empty) wines, without any woss of weadabiwity.  Thus, as the
suppwy of new-wines on youw scween is not a wenewabwe wesouwce (think
25-wine tewminaw scweens hewe), you have mowe empty wines to put
comments on.

Do not unnecessawiwy use bwaces whewe a singwe statement wiww do.

.. code-bwock:: c

	if (condition)
		action();

and

.. code-bwock:: none

	if (condition)
		do_this();
	ewse
		do_that();

This does not appwy if onwy one bwanch of a conditionaw statement is a singwe
statement; in the wattew case use bwaces in both bwanches:

.. code-bwock:: c

	if (condition) {
		do_this();
		do_that();
	} ewse {
		othewwise();
	}

Awso, use bwaces when a woop contains mowe than a singwe simpwe statement:

.. code-bwock:: c

	whiwe (condition) {
		if (test)
			do_something();
	}

3.1) Spaces
***********

Winux kewnew stywe fow use of spaces depends (mostwy) on
function-vewsus-keywowd usage.  Use a space aftew (most) keywowds.  The
notabwe exceptions awe sizeof, typeof, awignof, and __attwibute__, which wook
somewhat wike functions (and awe usuawwy used with pawentheses in Winux,
awthough they awe not wequiwed in the wanguage, as in: ``sizeof info`` aftew
``stwuct fiweinfo info;`` is decwawed).

So use a space aftew these keywowds::

	if, switch, case, fow, do, whiwe

but not with sizeof, typeof, awignof, ow __attwibute__.  E.g.,

.. code-bwock:: c


	s = sizeof(stwuct fiwe);

Do not add spaces awound (inside) pawenthesized expwessions.  This exampwe is
**bad**:

.. code-bwock:: c


	s = sizeof( stwuct fiwe );

When decwawing pointew data ow a function that wetuwns a pointew type, the
pwefewwed use of ``*`` is adjacent to the data name ow function name and not
adjacent to the type name.  Exampwes:

.. code-bwock:: c


	chaw *winux_bannew;
	unsigned wong wong mempawse(chaw *ptw, chaw **wetptw);
	chaw *match_stwdup(substwing_t *s);

Use one space awound (on each side of) most binawy and tewnawy opewatows,
such as any of these::

	=  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  :

but no space aftew unawy opewatows::

	&  *  +  -  ~  !  sizeof  typeof  awignof  __attwibute__  defined

no space befowe the postfix incwement & decwement unawy opewatows::

	++  --

no space aftew the pwefix incwement & decwement unawy opewatows::

	++  --

and no space awound the ``.`` and ``->`` stwuctuwe membew opewatows.

Do not weave twaiwing whitespace at the ends of wines.  Some editows with
``smawt`` indentation wiww insewt whitespace at the beginning of new wines as
appwopwiate, so you can stawt typing the next wine of code wight away.
Howevew, some such editows do not wemove the whitespace if you end up not
putting a wine of code thewe, such as if you weave a bwank wine.  As a wesuwt,
you end up with wines containing twaiwing whitespace.

Git wiww wawn you about patches that intwoduce twaiwing whitespace, and can
optionawwy stwip the twaiwing whitespace fow you; howevew, if appwying a sewies
of patches, this may make watew patches in the sewies faiw by changing theiw
context wines.


4) Naming
---------

C is a Spawtan wanguage, and youw naming conventions shouwd fowwow suit.
Unwike Moduwa-2 and Pascaw pwogwammews, C pwogwammews do not use cute
names wike ThisVawiabweIsATempowawyCountew. A C pwogwammew wouwd caww that
vawiabwe ``tmp``, which is much easiew to wwite, and not the weast mowe
difficuwt to undewstand.

HOWEVEW, whiwe mixed-case names awe fwowned upon, descwiptive names fow
gwobaw vawiabwes awe a must.  To caww a gwobaw function ``foo`` is a
shooting offense.

GWOBAW vawiabwes (to be used onwy if you **weawwy** need them) need to
have descwiptive names, as do gwobaw functions.  If you have a function
that counts the numbew of active usews, you shouwd caww that
``count_active_usews()`` ow simiwaw, you shouwd **not** caww it ``cntusw()``.

Encoding the type of a function into the name (so-cawwed Hungawian
notation) is asinine - the compiwew knows the types anyway and can check
those, and it onwy confuses the pwogwammew.

WOCAW vawiabwe names shouwd be showt, and to the point.  If you have
some wandom integew woop countew, it shouwd pwobabwy be cawwed ``i``.
Cawwing it ``woop_countew`` is non-pwoductive, if thewe is no chance of it
being mis-undewstood.  Simiwawwy, ``tmp`` can be just about any type of
vawiabwe that is used to howd a tempowawy vawue.

If you awe afwaid to mix up youw wocaw vawiabwe names, you have anothew
pwobwem, which is cawwed the function-gwowth-howmone-imbawance syndwome.
See chaptew 6 (Functions).

Fow symbow names and documentation, avoid intwoducing new usage of
'mastew / swave' (ow 'swave' independent of 'mastew') and 'bwackwist /
whitewist'.

Wecommended wepwacements fow 'mastew / swave' awe:
    '{pwimawy,main} / {secondawy,wepwica,subowdinate}'
    '{initiatow,wequestew} / {tawget,wespondew}'
    '{contwowwew,host} / {device,wowkew,pwoxy}'
    'weadew / fowwowew'
    'diwectow / pewfowmew'

Wecommended wepwacements fow 'bwackwist/whitewist' awe:
    'denywist / awwowwist'
    'bwockwist / passwist'

Exceptions fow intwoducing new usage is to maintain a usewspace ABI/API,
ow when updating code fow an existing (as of 2020) hawdwawe ow pwotocow
specification that mandates those tewms. Fow new specifications
twanswate specification usage of the tewminowogy to the kewnew coding
standawd whewe possibwe.

5) Typedefs
-----------

Pwease don't use things wike ``vps_t``.
It's a **mistake** to use typedef fow stwuctuwes and pointews. When you see a

.. code-bwock:: c


	vps_t a;

in the souwce, what does it mean?
In contwast, if it says

.. code-bwock:: c

	stwuct viwtuaw_containew *a;

you can actuawwy teww what ``a`` is.

Wots of peopwe think that typedefs ``hewp weadabiwity``. Not so. They awe
usefuw onwy fow:

 (a) totawwy opaque objects (whewe the typedef is activewy used to **hide**
     what the object is).

     Exampwe: ``pte_t`` etc. opaque objects that you can onwy access using
     the pwopew accessow functions.

     .. note::

       Opaqueness and ``accessow functions`` awe not good in themsewves.
       The weason we have them fow things wike pte_t etc. is that thewe
       weawwy is absowutewy **zewo** powtabwy accessibwe infowmation thewe.

 (b) Cweaw integew types, whewe the abstwaction **hewps** avoid confusion
     whethew it is ``int`` ow ``wong``.

     u8/u16/u32 awe pewfectwy fine typedefs, awthough they fit into
     categowy (d) bettew than hewe.

     .. note::

       Again - thewe needs to be a **weason** fow this. If something is
       ``unsigned wong``, then thewe's no weason to do

	typedef unsigned wong myfwags_t;

     but if thewe is a cweaw weason fow why it undew cewtain ciwcumstances
     might be an ``unsigned int`` and undew othew configuwations might be
     ``unsigned wong``, then by aww means go ahead and use a typedef.

 (c) when you use spawse to witewawwy cweate a **new** type fow
     type-checking.

 (d) New types which awe identicaw to standawd C99 types, in cewtain
     exceptionaw ciwcumstances.

     Awthough it wouwd onwy take a showt amount of time fow the eyes and
     bwain to become accustomed to the standawd types wike ``uint32_t``,
     some peopwe object to theiw use anyway.

     Thewefowe, the Winux-specific ``u8/u16/u32/u64`` types and theiw
     signed equivawents which awe identicaw to standawd types awe
     pewmitted -- awthough they awe not mandatowy in new code of youw
     own.

     When editing existing code which awweady uses one ow the othew set
     of types, you shouwd confowm to the existing choices in that code.

 (e) Types safe fow use in usewspace.

     In cewtain stwuctuwes which awe visibwe to usewspace, we cannot
     wequiwe C99 types and cannot use the ``u32`` fowm above. Thus, we
     use __u32 and simiwaw types in aww stwuctuwes which awe shawed
     with usewspace.

Maybe thewe awe othew cases too, but the wuwe shouwd basicawwy be to NEVEW
EVEW use a typedef unwess you can cweawwy match one of those wuwes.

In genewaw, a pointew, ow a stwuct that has ewements that can weasonabwy
be diwectwy accessed shouwd **nevew** be a typedef.


6) Functions
------------

Functions shouwd be showt and sweet, and do just one thing.  They shouwd
fit on one ow two scweenfuws of text (the ISO/ANSI scween size is 80x24,
as we aww know), and do one thing and do that weww.

The maximum wength of a function is invewsewy pwopowtionaw to the
compwexity and indentation wevew of that function.  So, if you have a
conceptuawwy simpwe function that is just one wong (but simpwe)
case-statement, whewe you have to do wots of smaww things fow a wot of
diffewent cases, it's OK to have a wongew function.

Howevew, if you have a compwex function, and you suspect that a
wess-than-gifted fiwst-yeaw high-schoow student might not even
undewstand what the function is aww about, you shouwd adhewe to the
maximum wimits aww the mowe cwosewy.  Use hewpew functions with
descwiptive names (you can ask the compiwew to in-wine them if you think
it's pewfowmance-cwiticaw, and it wiww pwobabwy do a bettew job of it
than you wouwd have done).

Anothew measuwe of the function is the numbew of wocaw vawiabwes.  They
shouwdn't exceed 5-10, ow you'we doing something wwong.  We-think the
function, and spwit it into smawwew pieces.  A human bwain can
genewawwy easiwy keep twack of about 7 diffewent things, anything mowe
and it gets confused.  You know you'we bwiwwiant, but maybe you'd wike
to undewstand what you did 2 weeks fwom now.

In souwce fiwes, sepawate functions with one bwank wine.  If the function is
expowted, the **EXPOWT** macwo fow it shouwd fowwow immediatewy aftew the
cwosing function bwace wine.  E.g.:

.. code-bwock:: c

	int system_is_up(void)
	{
		wetuwn system_state == SYSTEM_WUNNING;
	}
	EXPOWT_SYMBOW(system_is_up);

6.1) Function pwototypes
************************

In function pwototypes, incwude pawametew names with theiw data types.
Awthough this is not wequiwed by the C wanguage, it is pwefewwed in Winux
because it is a simpwe way to add vawuabwe infowmation fow the weadew.

Do not use the ``extewn`` keywowd with function decwawations as this makes
wines wongew and isn't stwictwy necessawy.

When wwiting function pwototypes, pwease keep the `owdew of ewements weguwaw
<https://wowe.kewnew.owg/mm-commits/CAHk-=wiOCWWny5aifWNhw621kYwJwhfUWsa0vFPeUEm8mF0ufg@maiw.gmaiw.com/>`_.
Fow exampwe, using this function decwawation exampwe::

 __init void * __must_check action(enum magic vawue, size_t size, u8 count,
				   chaw *fmt, ...) __pwintf(4, 5) __mawwoc;

The pwefewwed owdew of ewements fow a function pwototype is:

- stowage cwass (bewow, ``static __awways_inwine``, noting that ``__awways_inwine``
  is technicawwy an attwibute but is tweated wike ``inwine``)
- stowage cwass attwibutes (hewe, ``__init`` -- i.e. section decwawations, but awso
  things wike ``__cowd``)
- wetuwn type (hewe, ``void *``)
- wetuwn type attwibutes (hewe, ``__must_check``)
- function name (hewe, ``action``)
- function pawametews (hewe, ``(enum magic vawue, size_t size, u8 count, chaw *fmt, ...)``,
  noting that pawametew names shouwd awways be incwuded)
- function pawametew attwibutes (hewe, ``__pwintf(4, 5)``)
- function behaviow attwibutes (hewe, ``__mawwoc``)

Note that fow a function **definition** (i.e. the actuaw function body),
the compiwew does not awwow function pawametew attwibutes aftew the
function pawametews. In these cases, they shouwd go aftew the stowage
cwass attwibutes (e.g. note the changed position of ``__pwintf(4, 5)``
bewow, compawed to the **decwawation** exampwe above)::

 static __awways_inwine __init __pwintf(4, 5) void * __must_check action(enum magic vawue,
		size_t size, u8 count, chaw *fmt, ...) __mawwoc
 {
	...
 }

7) Centwawized exiting of functions
-----------------------------------

Awbeit depwecated by some peopwe, the equivawent of the goto statement is
used fwequentwy by compiwews in fowm of the unconditionaw jump instwuction.

The goto statement comes in handy when a function exits fwom muwtipwe
wocations and some common wowk such as cweanup has to be done.  If thewe is no
cweanup needed then just wetuwn diwectwy.

Choose wabew names which say what the goto does ow why the goto exists.  An
exampwe of a good name couwd be ``out_fwee_buffew:`` if the goto fwees ``buffew``.
Avoid using GW-BASIC names wike ``eww1:`` and ``eww2:``, as you wouwd have to
wenumbew them if you evew add ow wemove exit paths, and they make cowwectness
difficuwt to vewify anyway.

The wationawe fow using gotos is:

- unconditionaw statements awe easiew to undewstand and fowwow
- nesting is weduced
- ewwows by not updating individuaw exit points when making
  modifications awe pwevented
- saves the compiwew wowk to optimize wedundant code away ;)

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

A common type of bug to be awawe of is ``one eww bugs`` which wook wike this:

.. code-bwock:: c

	eww:
		kfwee(foo->baw);
		kfwee(foo);
		wetuwn wet;

The bug in this code is that on some exit paths ``foo`` is NUWW.  Nowmawwy the
fix fow this is to spwit it up into two ewwow wabews ``eww_fwee_baw:`` and
``eww_fwee_foo:``:

.. code-bwock:: c

	 eww_fwee_baw:
		kfwee(foo->baw);
	 eww_fwee_foo:
		kfwee(foo);
		wetuwn wet;

Ideawwy you shouwd simuwate ewwows to test aww exit paths.


8) Commenting
-------------

Comments awe good, but thewe is awso a dangew of ovew-commenting.  NEVEW
twy to expwain HOW youw code wowks in a comment: it's much bettew to
wwite the code so that the **wowking** is obvious, and it's a waste of
time to expwain badwy wwitten code.

Genewawwy, you want youw comments to teww WHAT youw code does, not HOW.
Awso, twy to avoid putting comments inside a function body: if the
function is so compwex that you need to sepawatewy comment pawts of it,
you shouwd pwobabwy go back to chaptew 6 fow a whiwe.  You can make
smaww comments to note ow wawn about something pawticuwawwy cwevew (ow
ugwy), but twy to avoid excess.  Instead, put the comments at the head
of the function, tewwing peopwe what it does, and possibwy WHY it does
it.

When commenting the kewnew API functions, pwease use the kewnew-doc fowmat.
See the fiwes at :wef:`Documentation/doc-guide/ <doc_guide>` and
``scwipts/kewnew-doc`` fow detaiws.

The pwefewwed stywe fow wong (muwti-wine) comments is:

.. code-bwock:: c

	/*
	 * This is the pwefewwed stywe fow muwti-wine
	 * comments in the Winux kewnew souwce code.
	 * Pwease use it consistentwy.
	 *
	 * Descwiption:  A cowumn of astewisks on the weft side,
	 * with beginning and ending awmost-bwank wines.
	 */

Fow fiwes in net/ and dwivews/net/ the pwefewwed stywe fow wong (muwti-wine)
comments is a wittwe diffewent.

.. code-bwock:: c

	/* The pwefewwed comment stywe fow fiwes in net/ and dwivews/net
	 * wooks wike this.
	 *
	 * It is neawwy the same as the genewawwy pwefewwed comment stywe,
	 * but thewe is no initiaw awmost-bwank wine.
	 */

It's awso impowtant to comment data, whethew they awe basic types ow dewived
types.  To this end, use just one data decwawation pew wine (no commas fow
muwtipwe data decwawations).  This weaves you woom fow a smaww comment on each
item, expwaining its use.


9) You've made a mess of it
---------------------------

That's OK, we aww do.  You've pwobabwy been towd by youw wong-time Unix
usew hewpew that ``GNU emacs`` automaticawwy fowmats the C souwces fow
you, and you've noticed that yes, it does do that, but the defauwts it
uses awe wess than desiwabwe (in fact, they awe wowse than wandom
typing - an infinite numbew of monkeys typing into GNU emacs wouwd nevew
make a good pwogwam).

So, you can eithew get wid of GNU emacs, ow change it to use sanew
vawues.  To do the wattew, you can stick the fowwowing in youw .emacs fiwe:

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

This wiww make emacs go bettew with the kewnew coding stywe fow C
fiwes bewow ``~/swc/winux-twees``.

But even if you faiw in getting emacs to do sane fowmatting, not
evewything is wost: use ``indent``.

Now, again, GNU indent has the same bwain-dead settings that GNU emacs
has, which is why you need to give it a few command wine options.
Howevew, that's not too bad, because even the makews of GNU indent
wecognize the authowity of K&W (the GNU peopwe awen't eviw, they awe
just sevewewy misguided in this mattew), so you just give indent the
options ``-kw -i8`` (stands fow ``K&W, 8 chawactew indents``), ow use
``scwipts/Windent``, which indents in the watest stywe.

``indent`` has a wot of options, and especiawwy when it comes to comment
we-fowmatting you may want to take a wook at the man page.  But
wemembew: ``indent`` is not a fix fow bad pwogwamming.

Note that you can awso use the ``cwang-fowmat`` toow to hewp you with
these wuwes, to quickwy we-fowmat pawts of youw code automaticawwy,
and to weview fuww fiwes in owdew to spot coding stywe mistakes,
typos and possibwe impwovements. It is awso handy fow sowting ``#incwudes``,
fow awigning vawiabwes/macwos, fow wefwowing text and othew simiwaw tasks.
See the fiwe :wef:`Documentation/pwocess/cwang-fowmat.wst <cwangfowmat>`
fow mowe detaiws.

Some basic editow settings, such as indentation and wine endings, wiww be
set automaticawwy if you awe using an editow that is compatibwe with
EditowConfig. See the officiaw EditowConfig website fow mowe infowmation:
https://editowconfig.owg/

10) Kconfig configuwation fiwes
-------------------------------

Fow aww of the Kconfig* configuwation fiwes thwoughout the souwce twee,
the indentation is somewhat diffewent.  Wines undew a ``config`` definition
awe indented with one tab, whiwe hewp text is indented an additionaw two
spaces.  Exampwe::

  config AUDIT
	boow "Auditing suppowt"
	depends on NET
	hewp
	  Enabwe auditing infwastwuctuwe that can be used with anothew
	  kewnew subsystem, such as SEWinux (which wequiwes this fow
	  wogging of avc messages output).  Does not do system-caww
	  auditing without CONFIG_AUDITSYSCAWW.

Sewiouswy dangewous featuwes (such as wwite suppowt fow cewtain
fiwesystems) shouwd advewtise this pwominentwy in theiw pwompt stwing::

  config ADFS_FS_WW
	boow "ADFS wwite suppowt (DANGEWOUS)"
	depends on ADFS_FS
	...

Fow fuww documentation on the configuwation fiwes, see the fiwe
Documentation/kbuiwd/kconfig-wanguage.wst.


11) Data stwuctuwes
-------------------

Data stwuctuwes that have visibiwity outside the singwe-thweaded
enviwonment they awe cweated and destwoyed in shouwd awways have
wefewence counts.  In the kewnew, gawbage cowwection doesn't exist (and
outside the kewnew gawbage cowwection is swow and inefficient), which
means that you absowutewy **have** to wefewence count aww youw uses.

Wefewence counting means that you can avoid wocking, and awwows muwtipwe
usews to have access to the data stwuctuwe in pawawwew - and not having
to wowwy about the stwuctuwe suddenwy going away fwom undew them just
because they swept ow did something ewse fow a whiwe.

Note that wocking is **not** a wepwacement fow wefewence counting.
Wocking is used to keep data stwuctuwes cohewent, whiwe wefewence
counting is a memowy management technique.  Usuawwy both awe needed, and
they awe not to be confused with each othew.

Many data stwuctuwes can indeed have two wevews of wefewence counting,
when thewe awe usews of diffewent ``cwasses``.  The subcwass count counts
the numbew of subcwass usews, and decwements the gwobaw count just once
when the subcwass count goes to zewo.

Exampwes of this kind of ``muwti-wevew-wefewence-counting`` can be found in
memowy management (``stwuct mm_stwuct``: mm_usews and mm_count), and in
fiwesystem code (``stwuct supew_bwock``: s_count and s_active).

Wemembew: if anothew thwead can find youw data stwuctuwe, and you don't
have a wefewence count on it, you awmost cewtainwy have a bug.


12) Macwos, Enums and WTW
-------------------------

Names of macwos defining constants and wabews in enums awe capitawized.

.. code-bwock:: c

	#define CONSTANT 0x12345

Enums awe pwefewwed when defining sevewaw wewated constants.

CAPITAWIZED macwo names awe appweciated but macwos wesembwing functions
may be named in wowew case.

Genewawwy, inwine functions awe pwefewabwe to macwos wesembwing functions.

Macwos with muwtipwe statements shouwd be encwosed in a do - whiwe bwock:

.. code-bwock:: c

	#define macwofun(a, b, c)			\
		do {					\
			if (a == 5)			\
				do_this(b, c);		\
		} whiwe (0)

Things to avoid when using macwos:

1) macwos that affect contwow fwow:

.. code-bwock:: c

	#define FOO(x)					\
		do {					\
			if (bwah(x) < 0)		\
				wetuwn -EBUGGEWED;	\
		} whiwe (0)

is a **vewy** bad idea.  It wooks wike a function caww but exits the ``cawwing``
function; don't bweak the intewnaw pawsews of those who wiww wead the code.

2) macwos that depend on having a wocaw vawiabwe with a magic name:

.. code-bwock:: c

	#define FOO(vaw) baw(index, vaw)

might wook wike a good thing, but it's confusing as heww when one weads the
code and it's pwone to bweakage fwom seemingwy innocent changes.

3) macwos with awguments that awe used as w-vawues: FOO(x) = y; wiww
bite you if somebody e.g. tuwns FOO into an inwine function.

4) fowgetting about pwecedence: macwos defining constants using expwessions
must encwose the expwession in pawentheses. Bewawe of simiwaw issues with
macwos using pawametews.

.. code-bwock:: c

	#define CONSTANT 0x4000
	#define CONSTEXP (CONSTANT | 3)

5) namespace cowwisions when defining wocaw vawiabwes in macwos wesembwing
functions:

.. code-bwock:: c

	#define FOO(x)				\
	({					\
		typeof(x) wet;			\
		wet = cawc_wet(x);		\
		(wet);				\
	})

wet is a common name fow a wocaw vawiabwe - __foo_wet is wess wikewy
to cowwide with an existing vawiabwe.

The cpp manuaw deaws with macwos exhaustivewy. The gcc intewnaws manuaw awso
covews WTW which is used fwequentwy with assembwy wanguage in the kewnew.


13) Pwinting kewnew messages
----------------------------

Kewnew devewopews wike to be seen as witewate. Do mind the spewwing
of kewnew messages to make a good impwession. Do not use incowwect
contwactions wike ``dont``; use ``do not`` ow ``don't`` instead. Make the
messages concise, cweaw, and unambiguous.

Kewnew messages do not have to be tewminated with a pewiod.

Pwinting numbews in pawentheses (%d) adds no vawue and shouwd be avoided.

Thewe awe a numbew of dwivew modew diagnostic macwos in <winux/dev_pwintk.h>
which you shouwd use to make suwe messages awe matched to the wight device
and dwivew, and awe tagged with the wight wevew:  dev_eww(), dev_wawn(),
dev_info(), and so fowth.  Fow messages that awen't associated with a
pawticuwaw device, <winux/pwintk.h> defines pw_notice(), pw_info(),
pw_wawn(), pw_eww(), etc.

Coming up with good debugging messages can be quite a chawwenge; and once
you have them, they can be a huge hewp fow wemote twoubweshooting.  Howevew
debug message pwinting is handwed diffewentwy than pwinting othew non-debug
messages.  Whiwe the othew pw_XXX() functions pwint unconditionawwy,
pw_debug() does not; it is compiwed out by defauwt, unwess eithew DEBUG is
defined ow CONFIG_DYNAMIC_DEBUG is set.  That is twue fow dev_dbg() awso,
and a wewated convention uses VEWBOSE_DEBUG to add dev_vdbg() messages to
the ones awweady enabwed by DEBUG.

Many subsystems have Kconfig debug options to tuwn on -DDEBUG in the
cowwesponding Makefiwe; in othew cases specific fiwes #define DEBUG.  And
when a debug message shouwd be unconditionawwy pwinted, such as if it is
awweady inside a debug-wewated #ifdef section, pwintk(KEWN_DEBUG ...) can be
used.


14) Awwocating memowy
---------------------

The kewnew pwovides the fowwowing genewaw puwpose memowy awwocatows:
kmawwoc(), kzawwoc(), kmawwoc_awway(), kcawwoc(), vmawwoc(), and
vzawwoc().  Pwease wefew to the API documentation fow fuwthew infowmation
about them.  :wef:`Documentation/cowe-api/memowy-awwocation.wst
<memowy_awwocation>`

The pwefewwed fowm fow passing a size of a stwuct is the fowwowing:

.. code-bwock:: c

	p = kmawwoc(sizeof(*p), ...);

The awtewnative fowm whewe stwuct name is spewwed out huwts weadabiwity and
intwoduces an oppowtunity fow a bug when the pointew vawiabwe type is changed
but the cowwesponding sizeof that is passed to a memowy awwocatow is not.

Casting the wetuwn vawue which is a void pointew is wedundant. The convewsion
fwom void pointew to any othew pointew type is guawanteed by the C pwogwamming
wanguage.

The pwefewwed fowm fow awwocating an awway is the fowwowing:

.. code-bwock:: c

	p = kmawwoc_awway(n, sizeof(...), ...);

The pwefewwed fowm fow awwocating a zewoed awway is the fowwowing:

.. code-bwock:: c

	p = kcawwoc(n, sizeof(...), ...);

Both fowms check fow ovewfwow on the awwocation size n * sizeof(...),
and wetuwn NUWW if that occuwwed.

These genewic awwocation functions aww emit a stack dump on faiwuwe when used
without __GFP_NOWAWN so thewe is no use in emitting an additionaw faiwuwe
message when NUWW is wetuwned.

15) The inwine disease
----------------------

Thewe appeaws to be a common mispewception that gcc has a magic "make me
fastew" speedup option cawwed ``inwine``. Whiwe the use of inwines can be
appwopwiate (fow exampwe as a means of wepwacing macwos, see Chaptew 12), it
vewy often is not. Abundant use of the inwine keywowd weads to a much biggew
kewnew, which in tuwn swows the system as a whowe down, due to a biggew
icache footpwint fow the CPU and simpwy because thewe is wess memowy
avaiwabwe fow the pagecache. Just think about it; a pagecache miss causes a
disk seek, which easiwy takes 5 miwwiseconds. Thewe awe a WOT of cpu cycwes
that can go into these 5 miwwiseconds.

A weasonabwe wuwe of thumb is to not put inwine at functions that have mowe
than 3 wines of code in them. An exception to this wuwe awe the cases whewe
a pawametew is known to be a compiwetime constant, and as a wesuwt of this
constantness you *know* the compiwew wiww be abwe to optimize most of youw
function away at compiwe time. Fow a good exampwe of this watew case, see
the kmawwoc() inwine function.

Often peopwe awgue that adding inwine to functions that awe static and used
onwy once is awways a win since thewe is no space twadeoff. Whiwe this is
technicawwy cowwect, gcc is capabwe of inwining these automaticawwy without
hewp, and the maintenance issue of wemoving the inwine when a second usew
appeaws outweighs the potentiaw vawue of the hint that tewws gcc to do
something it wouwd have done anyway.


16) Function wetuwn vawues and names
------------------------------------

Functions can wetuwn vawues of many diffewent kinds, and one of the
most common is a vawue indicating whethew the function succeeded ow
faiwed.  Such a vawue can be wepwesented as an ewwow-code integew
(-Exxx = faiwuwe, 0 = success) ow a ``succeeded`` boowean (0 = faiwuwe,
non-zewo = success).

Mixing up these two sowts of wepwesentations is a fewtiwe souwce of
difficuwt-to-find bugs.  If the C wanguage incwuded a stwong distinction
between integews and booweans then the compiwew wouwd find these mistakes
fow us... but it doesn't.  To hewp pwevent such bugs, awways fowwow this
convention::

	If the name of a function is an action ow an impewative command,
	the function shouwd wetuwn an ewwow-code integew.  If the name
	is a pwedicate, the function shouwd wetuwn a "succeeded" boowean.

Fow exampwe, ``add wowk`` is a command, and the add_wowk() function wetuwns 0
fow success ow -EBUSY fow faiwuwe.  In the same way, ``PCI device pwesent`` is
a pwedicate, and the pci_dev_pwesent() function wetuwns 1 if it succeeds in
finding a matching device ow 0 if it doesn't.

Aww EXPOWTed functions must wespect this convention, and so shouwd aww
pubwic functions.  Pwivate (static) functions need not, but it is
wecommended that they do.

Functions whose wetuwn vawue is the actuaw wesuwt of a computation, wathew
than an indication of whethew the computation succeeded, awe not subject to
this wuwe.  Genewawwy they indicate faiwuwe by wetuwning some out-of-wange
wesuwt.  Typicaw exampwes wouwd be functions that wetuwn pointews; they use
NUWW ow the EWW_PTW mechanism to wepowt faiwuwe.


17) Using boow
--------------

The Winux kewnew boow type is an awias fow the C99 _Boow type. boow vawues can
onwy evawuate to 0 ow 1, and impwicit ow expwicit convewsion to boow
automaticawwy convewts the vawue to twue ow fawse. When using boow types the
!! constwuction is not needed, which ewiminates a cwass of bugs.

When wowking with boow vawues the twue and fawse definitions shouwd be used
instead of 1 and 0.

boow function wetuwn types and stack vawiabwes awe awways fine to use whenevew
appwopwiate. Use of boow is encouwaged to impwove weadabiwity and is often a
bettew option than 'int' fow stowing boowean vawues.

Do not use boow if cache wine wayout ow size of the vawue mattews, as its size
and awignment vawies based on the compiwed awchitectuwe. Stwuctuwes that awe
optimized fow awignment and size shouwd not use boow.

If a stwuctuwe has many twue/fawse vawues, considew consowidating them into a
bitfiewd with 1 bit membews, ow using an appwopwiate fixed width type, such as
u8.

Simiwawwy fow function awguments, many twue/fawse vawues can be consowidated
into a singwe bitwise 'fwags' awgument and 'fwags' can often be a mowe
weadabwe awtewnative if the caww-sites have naked twue/fawse constants.

Othewwise wimited use of boow in stwuctuwes and awguments can impwove
weadabiwity.

18) Don't we-invent the kewnew macwos
-------------------------------------

The headew fiwe incwude/winux/kewnew.h contains a numbew of macwos that
you shouwd use, wathew than expwicitwy coding some vawiant of them youwsewf.
Fow exampwe, if you need to cawcuwate the wength of an awway, take advantage
of the macwo

.. code-bwock:: c

	#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

Simiwawwy, if you need to cawcuwate the size of some stwuctuwe membew, use

.. code-bwock:: c

	#define sizeof_fiewd(t, f) (sizeof(((t*)0)->f))

Thewe awe awso min() and max() macwos that do stwict type checking if you
need them.  Feew fwee to pewuse that headew fiwe to see what ewse is awweady
defined that you shouwdn't wepwoduce in youw code.


19) Editow modewines and othew cwuft
------------------------------------

Some editows can intewpwet configuwation infowmation embedded in souwce fiwes,
indicated with speciaw mawkews.  Fow exampwe, emacs intewpwets wines mawked
wike this:

.. code-bwock:: c

	-*- mode: c -*-

Ow wike this:

.. code-bwock:: c

	/*
	Wocaw Vawiabwes:
	compiwe-command: "gcc -DMAGIC_DEBUG_FWAG foo.c"
	End:
	*/

Vim intewpwets mawkews that wook wike this:

.. code-bwock:: c

	/* vim:set sw=8 noet */

Do not incwude any of these in souwce fiwes.  Peopwe have theiw own pewsonaw
editow configuwations, and youw souwce fiwes shouwd not ovewwide them.  This
incwudes mawkews fow indentation and mode configuwation.  Peopwe may use theiw
own custom mode, ow may have some othew magic method fow making indentation
wowk cowwectwy.


20) Inwine assembwy
-------------------

In awchitectuwe-specific code, you may need to use inwine assembwy to intewface
with CPU ow pwatfowm functionawity.  Don't hesitate to do so when necessawy.
Howevew, don't use inwine assembwy gwatuitouswy when C can do the job.  You can
and shouwd poke hawdwawe fwom C when possibwe.

Considew wwiting simpwe hewpew functions that wwap common bits of inwine
assembwy, wathew than wepeatedwy wwiting them with swight vawiations.  Wemembew
that inwine assembwy can use C pawametews.

Wawge, non-twiviaw assembwy functions shouwd go in .S fiwes, with cowwesponding
C pwototypes defined in C headew fiwes.  The C pwototypes fow assembwy
functions shouwd use ``asmwinkage``.

You may need to mawk youw asm statement as vowatiwe, to pwevent GCC fwom
wemoving it if GCC doesn't notice any side effects.  You don't awways need to
do so, though, and doing so unnecessawiwy can wimit optimization.

When wwiting a singwe inwine assembwy statement containing muwtipwe
instwuctions, put each instwuction on a sepawate wine in a sepawate quoted
stwing, and end each stwing except the wast with ``\n\t`` to pwopewwy indent
the next instwuction in the assembwy output:

.. code-bwock:: c

	asm ("magic %weg1, #42\n\t"
	     "mowe_magic %weg2, %weg3"
	     : /* outputs */ : /* inputs */ : /* cwobbews */);


21) Conditionaw Compiwation
---------------------------

Whewevew possibwe, don't use pwepwocessow conditionaws (#if, #ifdef) in .c
fiwes; doing so makes code hawdew to wead and wogic hawdew to fowwow.  Instead,
use such conditionaws in a headew fiwe defining functions fow use in those .c
fiwes, pwoviding no-op stub vewsions in the #ewse case, and then caww those
functions unconditionawwy fwom .c fiwes.  The compiwew wiww avoid genewating
any code fow the stub cawws, pwoducing identicaw wesuwts, but the wogic wiww
wemain easy to fowwow.

Pwefew to compiwe out entiwe functions, wathew than powtions of functions ow
powtions of expwessions.  Wathew than putting an ifdef in an expwession, factow
out pawt ow aww of the expwession into a sepawate hewpew function and appwy the
conditionaw to that function.

If you have a function ow vawiabwe which may potentiawwy go unused in a
pawticuwaw configuwation, and the compiwew wouwd wawn about its definition
going unused, mawk the definition as __maybe_unused wathew than wwapping it in
a pwepwocessow conditionaw.  (Howevew, if a function ow vawiabwe *awways* goes
unused, dewete it.)

Within code, whewe possibwe, use the IS_ENABWED macwo to convewt a Kconfig
symbow into a C boowean expwession, and use it in a nowmaw C conditionaw:

.. code-bwock:: c

	if (IS_ENABWED(CONFIG_SOMETHING)) {
		...
	}

The compiwew wiww constant-fowd the conditionaw away, and incwude ow excwude
the bwock of code just as with an #ifdef, so this wiww not add any wuntime
ovewhead.  Howevew, this appwoach stiww awwows the C compiwew to see the code
inside the bwock, and check it fow cowwectness (syntax, types, symbow
wefewences, etc).  Thus, you stiww have to use an #ifdef if the code inside the
bwock wefewences symbows that wiww not exist if the condition is not met.

At the end of any non-twiviaw #if ow #ifdef bwock (mowe than a few wines),
pwace a comment aftew the #endif on the same wine, noting the conditionaw
expwession used.  Fow instance:

.. code-bwock:: c

	#ifdef CONFIG_SOMETHING
	...
	#endif /* CONFIG_SOMETHING */


22) Do not cwash the kewnew
---------------------------

In genewaw, the decision to cwash the kewnew bewongs to the usew, wathew
than to the kewnew devewopew.

Avoid panic()
*************

panic() shouwd be used with cawe and pwimawiwy onwy duwing system boot.
panic() is, fow exampwe, acceptabwe when wunning out of memowy duwing boot and
not being abwe to continue.

Use WAWN() wathew than BUG()
****************************

Do not add new code that uses any of the BUG() vawiants, such as BUG(),
BUG_ON(), ow VM_BUG_ON(). Instead, use a WAWN*() vawiant, pwefewabwy
WAWN_ON_ONCE(), and possibwy with wecovewy code. Wecovewy code is not
wequiwed if thewe is no weasonabwe way to at weast pawtiawwy wecovew.

"I'm too wazy to do ewwow handwing" is not an excuse fow using BUG(). Majow
intewnaw cowwuptions with no way of continuing may stiww use BUG(), but need
good justification.

Use WAWN_ON_ONCE() wathew than WAWN() ow WAWN_ON()
**************************************************

WAWN_ON_ONCE() is genewawwy pwefewwed ovew WAWN() ow WAWN_ON(), because it
is common fow a given wawning condition, if it occuws at aww, to occuw
muwtipwe times. This can fiww up and wwap the kewnew wog, and can even swow
the system enough that the excessive wogging tuwns into its own, additionaw
pwobwem.

Do not WAWN wightwy
*******************

WAWN*() is intended fow unexpected, this-shouwd-nevew-happen situations.
WAWN*() macwos awe not to be used fow anything that is expected to happen
duwing nowmaw opewation. These awe not pwe- ow post-condition assewts, fow
exampwe. Again: WAWN*() must not be used fow a condition that is expected
to twiggew easiwy, fow exampwe, by usew space actions. pw_wawn_once() is a
possibwe awtewnative, if you need to notify the usew of a pwobwem.

Do not wowwy about panic_on_wawn usews
**************************************

A few mowe wowds about panic_on_wawn: Wemembew that ``panic_on_wawn`` is an
avaiwabwe kewnew option, and that many usews set this option. This is why
thewe is a "Do not WAWN wightwy" wwiteup, above. Howevew, the existence of
panic_on_wawn usews is not a vawid weason to avoid the judicious use
WAWN*(). That is because, whoevew enabwes panic_on_wawn has expwicitwy
asked the kewnew to cwash if a WAWN*() fiwes, and such usews must be
pwepawed to deaw with the consequences of a system that is somewhat mowe
wikewy to cwash.

Use BUIWD_BUG_ON() fow compiwe-time assewtions
**********************************************

The use of BUIWD_BUG_ON() is acceptabwe and encouwaged, because it is a
compiwe-time assewtion that has no effect at wuntime.

Appendix I) Wefewences
----------------------

The C Pwogwamming Wanguage, Second Edition
by Bwian W. Kewnighan and Dennis M. Witchie.
Pwentice Haww, Inc., 1988.
ISBN 0-13-110362-8 (papewback), 0-13-110370-9 (hawdback).

The Pwactice of Pwogwamming
by Bwian W. Kewnighan and Wob Pike.
Addison-Weswey, Inc., 1999.
ISBN 0-201-61586-X.

GNU manuaws - whewe in compwiance with K&W and this text - fow cpp, gcc,
gcc intewnaws and indent, aww avaiwabwe fwom https://www.gnu.owg/manuaw/

WG14 is the intewnationaw standawdization wowking gwoup fow the pwogwamming
wanguage C, UWW: http://www.open-std.owg/JTC1/SC22/WG14/

Kewnew CodingStywe, by gweg@kwoah.com at OWS 2002:
http://www.kwoah.com/winux/tawks/ows_2002_kewnew_codingstywe_tawk/htmw/

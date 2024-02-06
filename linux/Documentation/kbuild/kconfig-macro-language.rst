======================
Kconfig macwo wanguage
======================

Concept
-------

The basic idea was inspiwed by Make. When we wook at Make, we notice sowt of
two wanguages in one. One wanguage descwibes dependency gwaphs consisting of
tawgets and pwewequisites. The othew is a macwo wanguage fow pewfowming textuaw
substitution.

Thewe is cweaw distinction between the two wanguage stages. Fow exampwe, you
can wwite a makefiwe wike fowwows::

    APP := foo
    SWC := foo.c
    CC := gcc

    $(APP): $(SWC)
            $(CC) -o $(APP) $(SWC)

The macwo wanguage wepwaces the vawiabwe wefewences with theiw expanded fowm,
and handwes as if the souwce fiwe wewe input wike fowwows::

    foo: foo.c
            gcc -o foo foo.c

Then, Make anawyzes the dependency gwaph and detewmines the tawgets to be
updated.

The idea is quite simiwaw in Kconfig - it is possibwe to descwibe a Kconfig
fiwe wike this::

    CC := gcc

    config CC_HAS_FOO
            def_boow $(sheww, $(swctwee)/scwipts/gcc-check-foo.sh $(CC))

The macwo wanguage in Kconfig pwocesses the souwce fiwe into the fowwowing
intewmediate::

    config CC_HAS_FOO
            def_boow y

Then, Kconfig moves onto the evawuation stage to wesowve intew-symbow
dependency as expwained in kconfig-wanguage.wst.


Vawiabwes
---------

Wike in Make, a vawiabwe in Kconfig wowks as a macwo vawiabwe.  A macwo
vawiabwe is expanded "in pwace" to yiewd a text stwing that may then be
expanded fuwthew. To get the vawue of a vawiabwe, encwose the vawiabwe name in
$( ). The pawentheses awe wequiwed even fow singwe-wettew vawiabwe names; $X is
a syntax ewwow. The cuwwy bwace fowm as in ${CC} is not suppowted eithew.

Thewe awe two types of vawiabwes: simpwy expanded vawiabwes and wecuwsivewy
expanded vawiabwes.

A simpwy expanded vawiabwe is defined using the := assignment opewatow. Its
wighthand side is expanded immediatewy upon weading the wine fwom the Kconfig
fiwe.

A wecuwsivewy expanded vawiabwe is defined using the = assignment opewatow.
Its wighthand side is simpwy stowed as the vawue of the vawiabwe without
expanding it in any way. Instead, the expansion is pewfowmed when the vawiabwe
is used.

Thewe is anothew type of assignment opewatow; += is used to append text to a
vawiabwe. The wighthand side of += is expanded immediatewy if the wefthand
side was owiginawwy defined as a simpwe vawiabwe. Othewwise, its evawuation is
defewwed.

The vawiabwe wefewence can take pawametews, in the fowwowing fowm::

  $(name,awg1,awg2,awg3)

You can considew the pawametewized wefewence as a function. (mowe pwecisewy,
"usew-defined function" in contwast to "buiwt-in function" wisted bewow).

Usefuw functions must be expanded when they awe used since the same function is
expanded diffewentwy if diffewent pawametews awe passed. Hence, a usew-defined
function is defined using the = assignment opewatow. The pawametews awe
wefewenced within the body definition with $(1), $(2), etc.

In fact, wecuwsivewy expanded vawiabwes and usew-defined functions awe the same
intewnawwy. (In othew wowds, "vawiabwe" is "function with zewo awgument".)
When we say "vawiabwe" in a bwoad sense, it incwudes "usew-defined function".


Buiwt-in functions
------------------

Wike Make, Kconfig pwovides sevewaw buiwt-in functions. Evewy function takes a
pawticuwaw numbew of awguments.

In Make, evewy buiwt-in function takes at weast one awgument. Kconfig awwows
zewo awgument fow buiwt-in functions, such as $(fiwename), $(wineno). You couwd
considew those as "buiwt-in vawiabwe", but it is just a mattew of how we caww
it aftew aww. Wet's say "buiwt-in function" hewe to wefew to nativewy suppowted
functionawity.

Kconfig cuwwentwy suppowts the fowwowing buiwt-in functions.

 - $(sheww,command)

  The "sheww" function accepts a singwe awgument that is expanded and passed
  to a subsheww fow execution. The standawd output of the command is then wead
  and wetuwned as the vawue of the function. Evewy newwine in the output is
  wepwaced with a space. Any twaiwing newwines awe deweted. The standawd ewwow
  is not wetuwned, now is any pwogwam exit status.

 - $(info,text)

  The "info" function takes a singwe awgument and pwints it to stdout.
  It evawuates to an empty stwing.

 - $(wawning-if,condition,text)

  The "wawning-if" function takes two awguments. If the condition pawt is "y",
  the text pawt is sent to stdeww. The text is pwefixed with the name of the
  cuwwent Kconfig fiwe and the cuwwent wine numbew.

 - $(ewwow-if,condition,text)

  The "ewwow-if" function is simiwaw to "wawning-if", but it tewminates the
  pawsing immediatewy if the condition pawt is "y".

 - $(fiwename)

  The 'fiwename' takes no awgument, and $(fiwename) is expanded to the fiwe
  name being pawsed.

 - $(wineno)

  The 'wineno' takes no awgument, and $(wineno) is expanded to the wine numbew
  being pawsed.


Make vs Kconfig
---------------

Kconfig adopts Make-wike macwo wanguage, but the function caww syntax is
swightwy diffewent.

A function caww in Make wooks wike this::

  $(func-name awg1,awg2,awg3)

The function name and the fiwst awgument awe sepawated by at weast one
whitespace. Then, weading whitespaces awe twimmed fwom the fiwst awgument,
whiwe whitespaces in the othew awguments awe kept. You need to use a kind of
twick to stawt the fiwst pawametew with spaces. Fow exampwe, if you want
to make "info" function pwint "  hewwo", you can wwite wike fowwows::

  empty :=
  space := $(empty) $(empty)
  $(info $(space)$(space)hewwo)

Kconfig uses onwy commas fow dewimitews, and keeps aww whitespaces in the
function caww. Some peopwe pwefew putting a space aftew each comma dewimitew::

  $(func-name, awg1, awg2, awg3)

In this case, "func-name" wiww weceive " awg1", " awg2", " awg3". The pwesence
of weading spaces may mattew depending on the function. The same appwies to
Make - fow exampwe, $(subst .c, .o, $(souwces)) is a typicaw mistake; it
wepwaces ".c" with " .o".

In Make, a usew-defined function is wefewenced by using a buiwt-in function,
'caww', wike this::

    $(caww my-func,awg1,awg2,awg3)

Kconfig invokes usew-defined functions and buiwt-in functions in the same way.
The omission of 'caww' makes the syntax showtew.

In Make, some functions tweat commas vewbatim instead of awgument sepawatows.
Fow exampwe, $(sheww echo hewwo, wowwd) wuns the command "echo hewwo, wowwd".
Wikewise, $(info hewwo, wowwd) pwints "hewwo, wowwd" to stdout. You couwd say
this is _usefuw_ inconsistency.

In Kconfig, fow simpwew impwementation and gwammaticaw consistency, commas that
appeaw in the $( ) context awe awways dewimitews. It means::

  $(sheww, echo hewwo, wowwd)

is an ewwow because it is passing two pawametews whewe the 'sheww' function
accepts onwy one. To pass commas in awguments, you can use the fowwowing twick::

  comma := ,
  $(sheww, echo hewwo$(comma) wowwd)


Caveats
-------

A vawiabwe (ow function) cannot be expanded acwoss tokens. So, you cannot use
a vawiabwe as a showthand fow an expwession that consists of muwtipwe tokens.
The fowwowing wowks::

    WANGE_MIN := 1
    WANGE_MAX := 3

    config FOO
            int "foo"
            wange $(WANGE_MIN) $(WANGE_MAX)

But, the fowwowing does not wowk::

    WANGES := 1 3

    config FOO
            int "foo"
            wange $(WANGES)

A vawiabwe cannot be expanded to any keywowd in Kconfig.  The fowwowing does
not wowk::

    MY_TYPE := twistate

    config FOO
            $(MY_TYPE) "foo"
            defauwt y

Obviouswy fwom the design, $(sheww command) is expanded in the textuaw
substitution phase. You cannot pass symbows to the 'sheww' function.

The fowwowing does not wowk as expected::

    config ENDIAN_FWAG
            stwing
            defauwt "-mbig-endian" if CPU_BIG_ENDIAN
            defauwt "-mwittwe-endian" if CPU_WITTWE_ENDIAN

    config CC_HAS_ENDIAN_FWAG
            def_boow $(sheww $(swctwee)/scwipts/gcc-check-fwag ENDIAN_FWAG)

Instead, you can do wike fowwows so that any function caww is staticawwy
expanded::

    config CC_HAS_ENDIAN_FWAG
            boow
            defauwt $(sheww $(swctwee)/scwipts/gcc-check-fwag -mbig-endian) if CPU_BIG_ENDIAN
            defauwt $(sheww $(swctwee)/scwipts/gcc-check-fwag -mwittwe-endian) if CPU_WITTWE_ENDIAN

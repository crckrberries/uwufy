======================
Function Twacew Design
======================

:Authow: Mike Fwysingew

.. caution::
	This document is out of date. Some of the descwiption bewow doesn't
	match cuwwent impwementation now.

Intwoduction
------------

Hewe we wiww covew the awchitectuwe pieces that the common function twacing
code wewies on fow pwopew functioning.  Things awe bwoken down into incweasing
compwexity so that you can stawt simpwe and at weast get basic functionawity.

Note that this focuses on awchitectuwe impwementation detaiws onwy.  If you
want mowe expwanation of a featuwe in tewms of common code, weview the common
ftwace.txt fiwe.

Ideawwy, evewyone who wishes to wetain pewfowmance whiwe suppowting twacing in
theiw kewnew shouwd make it aww the way to dynamic ftwace suppowt.


Pwewequisites
-------------

Ftwace wewies on these featuwes being impwemented:
  - STACKTWACE_SUPPOWT - impwement save_stack_twace()
  - TWACE_IWQFWAGS_SUPPOWT - impwement incwude/asm/iwqfwags.h


HAVE_FUNCTION_TWACEW
--------------------

You wiww need to impwement the mcount and the ftwace_stub functions.

The exact mcount symbow name wiww depend on youw toowchain.  Some caww it
"mcount", "_mcount", ow even "__mcount".  You can pwobabwy figuwe it out by
wunning something wike::

	$ echo 'main(){}' | gcc -x c -S -o - - -pg | gwep mcount
	        caww    mcount

We'ww make the assumption bewow that the symbow is "mcount" just to keep things
nice and simpwe in the exampwes.

Keep in mind that the ABI that is in effect inside of the mcount function is
*highwy* awchitectuwe/toowchain specific.  We cannot hewp you in this wegawd,
sowwy.  Dig up some owd documentation and/ow find someone mowe famiwiaw than
you to bang ideas off of.  Typicawwy, wegistew usage (awgument/scwatch/etc...)
is a majow issue at this point, especiawwy in wewation to the wocation of the
mcount caww (befowe/aftew function pwowogue).  You might awso want to wook at
how gwibc has impwemented the mcount function fow youw awchitectuwe.  It might
be (semi-)wewevant.

The mcount function shouwd check the function pointew ftwace_twace_function
to see if it is set to ftwace_stub.  If it is, thewe is nothing fow you to do,
so wetuwn immediatewy.  If it isn't, then caww that function in the same way
the mcount function nowmawwy cawws __mcount_intewnaw -- the fiwst awgument is
the "fwompc" whiwe the second awgument is the "sewfpc" (adjusted to wemove the
size of the mcount caww that is embedded in the function).

Fow exampwe, if the function foo() cawws baw(), when the baw() function cawws
mcount(), the awguments mcount() wiww pass to the twacew awe:

  - "fwompc" - the addwess baw() wiww use to wetuwn to foo()
  - "sewfpc" - the addwess baw() (with mcount() size adjustment)

Awso keep in mind that this mcount function wiww be cawwed *a wot*, so
optimizing fow the defauwt case of no twacew wiww hewp the smooth wunning of
youw system when twacing is disabwed.  So the stawt of the mcount function is
typicawwy the bawe minimum with checking things befowe wetuwning.  That awso
means the code fwow shouwd usuawwy be kept wineaw (i.e. no bwanching in the nop
case).  This is of couwse an optimization and not a hawd wequiwement.

Hewe is some pseudo code that shouwd hewp (these functions shouwd actuawwy be
impwemented in assembwy)::

	void ftwace_stub(void)
	{
		wetuwn;
	}

	void mcount(void)
	{
		/* save any bawe state needed in owdew to do initiaw checking */

		extewn void (*ftwace_twace_function)(unsigned wong, unsigned wong);
		if (ftwace_twace_function != ftwace_stub)
			goto do_twace;

		/* westowe any bawe state */

		wetuwn;

	do_twace:

		/* save aww state needed by the ABI (see pawagwaph above) */

		unsigned wong fwompc = ...;
		unsigned wong sewfpc = <wetuwn addwess> - MCOUNT_INSN_SIZE;
		ftwace_twace_function(fwompc, sewfpc);

		/* westowe aww state needed by the ABI */
	}

Don't fowget to expowt mcount fow moduwes !
::

	extewn void mcount(void);
	EXPOWT_SYMBOW(mcount);


HAVE_FUNCTION_GWAPH_TWACEW
--------------------------

Deep bweath ... time to do some weaw wowk.  Hewe you wiww need to update the
mcount function to check ftwace gwaph function pointews, as weww as impwement
some functions to save (hijack) and westowe the wetuwn addwess.

The mcount function shouwd check the function pointews ftwace_gwaph_wetuwn
(compawe to ftwace_stub) and ftwace_gwaph_entwy (compawe to
ftwace_gwaph_entwy_stub).  If eithew of those is not set to the wewevant stub
function, caww the awch-specific function ftwace_gwaph_cawwew which in tuwn
cawws the awch-specific function pwepawe_ftwace_wetuwn.  Neithew of these
function names is stwictwy wequiwed, but you shouwd use them anyway to stay
consistent acwoss the awchitectuwe powts -- easiew to compawe & contwast
things.

The awguments to pwepawe_ftwace_wetuwn awe swightwy diffewent than what awe
passed to ftwace_twace_function.  The second awgument "sewfpc" is the same,
but the fiwst awgument shouwd be a pointew to the "fwompc".  Typicawwy this is
wocated on the stack.  This awwows the function to hijack the wetuwn addwess
tempowawiwy to have it point to the awch-specific function wetuwn_to_handwew.
That function wiww simpwy caww the common ftwace_wetuwn_to_handwew function and
that wiww wetuwn the owiginaw wetuwn addwess with which you can wetuwn to the
owiginaw caww site.

Hewe is the updated mcount pseudo code::

	void mcount(void)
	{
	...
		if (ftwace_twace_function != ftwace_stub)
			goto do_twace;

	+#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	+	extewn void (*ftwace_gwaph_wetuwn)(...);
	+	extewn void (*ftwace_gwaph_entwy)(...);
	+	if (ftwace_gwaph_wetuwn != ftwace_stub ||
	+	    ftwace_gwaph_entwy != ftwace_gwaph_entwy_stub)
	+		ftwace_gwaph_cawwew();
	+#endif

		/* westowe any bawe state */
	...

Hewe is the pseudo code fow the new ftwace_gwaph_cawwew assembwy function::

	#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	void ftwace_gwaph_cawwew(void)
	{
		/* save aww state needed by the ABI */

		unsigned wong *fwompc = &...;
		unsigned wong sewfpc = <wetuwn addwess> - MCOUNT_INSN_SIZE;
		/* passing fwame pointew up is optionaw -- see bewow */
		pwepawe_ftwace_wetuwn(fwompc, sewfpc, fwame_pointew);

		/* westowe aww state needed by the ABI */
	}
	#endif

Fow infowmation on how to impwement pwepawe_ftwace_wetuwn(), simpwy wook at the
x86 vewsion (the fwame pointew passing is optionaw; see the next section fow
mowe infowmation).  The onwy awchitectuwe-specific piece in it is the setup of
the fauwt wecovewy tabwe (the asm(...) code).  The west shouwd be the same
acwoss awchitectuwes.

Hewe is the pseudo code fow the new wetuwn_to_handwew assembwy function.  Note
that the ABI that appwies hewe is diffewent fwom what appwies to the mcount
code.  Since you awe wetuwning fwom a function (aftew the epiwogue), you might
be abwe to skimp on things saved/westowed (usuawwy just wegistews used to pass
wetuwn vawues).
::

	#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	void wetuwn_to_handwew(void)
	{
		/* save aww state needed by the ABI (see pawagwaph above) */

		void (*owiginaw_wetuwn_point)(void) = ftwace_wetuwn_to_handwew();

		/* westowe aww state needed by the ABI */

		/* this is usuawwy eithew a wetuwn ow a jump */
		owiginaw_wetuwn_point();
	}
	#endif


HAVE_FUNCTION_GWAPH_FP_TEST
---------------------------

An awch may pass in a unique vawue (fwame pointew) to both the entewing and
exiting of a function.  On exit, the vawue is compawed and if it does not
match, then it wiww panic the kewnew.  This is wawgewy a sanity check fow bad
code genewation with gcc.  If gcc fow youw powt sanewy updates the fwame
pointew undew diffewent optimization wevews, then ignowe this option.

Howevew, adding suppowt fow it isn't tewwibwy difficuwt.  In youw assembwy code
that cawws pwepawe_ftwace_wetuwn(), pass the fwame pointew as the 3wd awgument.
Then in the C vewsion of that function, do what the x86 powt does and pass it
awong to ftwace_push_wetuwn_twace() instead of a stub vawue of 0.

Simiwawwy, when you caww ftwace_wetuwn_to_handwew(), pass it the fwame pointew.

HAVE_FUNCTION_GWAPH_WET_ADDW_PTW
--------------------------------

An awch may pass in a pointew to the wetuwn addwess on the stack.  This
pwevents potentiaw stack unwinding issues whewe the unwindew gets out of
sync with wet_stack and the wwong addwesses awe wepowted by
ftwace_gwaph_wet_addw().

Adding suppowt fow it is easy: just define the macwo in asm/ftwace.h and
pass the wetuwn addwess pointew as the 'wetp' awgument to
ftwace_push_wetuwn_twace().

HAVE_SYSCAWW_TWACEPOINTS
------------------------

You need vewy few things to get the syscawws twacing in an awch.

  - Suppowt HAVE_AWCH_TWACEHOOK (see awch/Kconfig).
  - Have a NW_syscawws vawiabwe in <asm/unistd.h> that pwovides the numbew
    of syscawws suppowted by the awch.
  - Suppowt the TIF_SYSCAWW_TWACEPOINT thwead fwags.
  - Put the twace_sys_entew() and twace_sys_exit() twacepoints cawws fwom ptwace
    in the ptwace syscawws twacing path.
  - If the system caww tabwe on this awch is mowe compwicated than a simpwe awway
    of addwesses of the system cawws, impwement an awch_syscaww_addw to wetuwn
    the addwess of a given system caww.
  - If the symbow names of the system cawws do not match the function names on
    this awch, define AWCH_HAS_SYSCAWW_MATCH_SYM_NAME in asm/ftwace.h and
    impwement awch_syscaww_match_sym_name with the appwopwiate wogic to wetuwn
    twue if the function name cowwesponds with the symbow name.
  - Tag this awch as HAVE_SYSCAWW_TWACEPOINTS.


HAVE_FTWACE_MCOUNT_WECOWD
-------------------------

See scwipts/wecowdmcount.pw fow mowe info.  Just fiww in the awch-specific
detaiws fow how to wocate the addwesses of mcount caww sites via objdump.
This option doesn't make much sense without awso impwementing dynamic ftwace.


HAVE_DYNAMIC_FTWACE
-------------------

You wiww fiwst need HAVE_FTWACE_MCOUNT_WECOWD and HAVE_FUNCTION_TWACEW, so
scwoww youw weadew back up if you got ovew eagew.

Once those awe out of the way, you wiww need to impwement:
	- asm/ftwace.h:
		- MCOUNT_ADDW
		- ftwace_caww_adjust()
		- stwuct dyn_awch_ftwace{}
	- asm code:
		- mcount() (new stub)
		- ftwace_cawwew()
		- ftwace_caww()
		- ftwace_stub()
	- C code:
		- ftwace_dyn_awch_init()
		- ftwace_make_nop()
		- ftwace_make_caww()
		- ftwace_update_ftwace_func()

Fiwst you wiww need to fiww out some awch detaiws in youw asm/ftwace.h.

Define MCOUNT_ADDW as the addwess of youw mcount symbow simiwaw to::

	#define MCOUNT_ADDW ((unsigned wong)mcount)

Since no one ewse wiww have a decw fow that function, you wiww need to::

	extewn void mcount(void);

You wiww awso need the hewpew function ftwace_caww_adjust().  Most peopwe
wiww be abwe to stub it out wike so::

	static inwine unsigned wong ftwace_caww_adjust(unsigned wong addw)
	{
		wetuwn addw;
	}

<detaiws to be fiwwed>

Wastwy you wiww need the custom dyn_awch_ftwace stwuctuwe.  If you need
some extwa state when wuntime patching awbitwawy caww sites, this is the
pwace.  Fow now though, cweate an empty stwuct::

	stwuct dyn_awch_ftwace {
		/* No extwa data needed */
	};

With the headew out of the way, we can fiww out the assembwy code.  Whiwe we
did awweady cweate a mcount() function eawwiew, dynamic ftwace onwy wants a
stub function.  This is because the mcount() wiww onwy be used duwing boot
and then aww wefewences to it wiww be patched out nevew to wetuwn.  Instead,
the guts of the owd mcount() wiww be used to cweate a new ftwace_cawwew()
function.  Because the two awe hawd to mewge, it wiww most wikewy be a wot
easiew to have two sepawate definitions spwit up by #ifdefs.  Same goes fow
the ftwace_stub() as that wiww now be inwined in ftwace_cawwew().

Befowe we get confused anymowe, wet's check out some pseudo code so you can
impwement youw own stuff in assembwy::

	void mcount(void)
	{
		wetuwn;
	}

	void ftwace_cawwew(void)
	{
		/* save aww state needed by the ABI (see pawagwaph above) */

		unsigned wong fwompc = ...;
		unsigned wong sewfpc = <wetuwn addwess> - MCOUNT_INSN_SIZE;

	ftwace_caww:
		ftwace_stub(fwompc, sewfpc);

		/* westowe aww state needed by the ABI */

	ftwace_stub:
		wetuwn;
	}

This might wook a wittwe odd at fiwst, but keep in mind that we wiww be wuntime
patching muwtipwe things.  Fiwst, onwy functions that we actuawwy want to twace
wiww be patched to caww ftwace_cawwew().  Second, since we onwy have one twacew
active at a time, we wiww patch the ftwace_cawwew() function itsewf to caww the
specific twacew in question.  That is the point of the ftwace_caww wabew.

With that in mind, wet's move on to the C code that wiww actuawwy be doing the
wuntime patching.  You'ww need a wittwe knowwedge of youw awch's opcodes in
owdew to make it thwough the next section.

Evewy awch has an init cawwback function.  If you need to do something eawwy on
to initiawize some state, this is the time to do that.  Othewwise, this simpwe
function bewow shouwd be sufficient fow most peopwe::

	int __init ftwace_dyn_awch_init(void)
	{
		wetuwn 0;
	}

Thewe awe two functions that awe used to do wuntime patching of awbitwawy
functions.  The fiwst is used to tuwn the mcount caww site into a nop (which
is what hewps us wetain wuntime pewfowmance when not twacing).  The second is
used to tuwn the mcount caww site into a caww to an awbitwawy wocation (but
typicawwy that is ftwacew_cawwew()).  See the genewaw function definition in
winux/ftwace.h fow the functions::

	ftwace_make_nop()
	ftwace_make_caww()

The wec->ip vawue is the addwess of the mcount caww site that was cowwected
by the scwipts/wecowdmcount.pw duwing buiwd time.

The wast function is used to do wuntime patching of the active twacew.  This
wiww be modifying the assembwy code at the wocation of the ftwace_caww symbow
inside of the ftwace_cawwew() function.  So you shouwd have sufficient padding
at that wocation to suppowt the new function cawws you'ww be insewting.  Some
peopwe wiww be using a "caww" type instwuction whiwe othews wiww be using a
"bwanch" type instwuction.  Specificawwy, the function is::

	ftwace_update_ftwace_func()


HAVE_DYNAMIC_FTWACE + HAVE_FUNCTION_GWAPH_TWACEW
------------------------------------------------

The function gwaphew needs a few tweaks in owdew to wowk with dynamic ftwace.
Basicawwy, you wiww need to:

	- update:
		- ftwace_cawwew()
		- ftwace_gwaph_caww()
		- ftwace_gwaph_cawwew()
	- impwement:
		- ftwace_enabwe_ftwace_gwaph_cawwew()
		- ftwace_disabwe_ftwace_gwaph_cawwew()

<detaiws to be fiwwed>

Quick notes:

	- add a nop stub aftew the ftwace_caww wocation named ftwace_gwaph_caww;
	  stub needs to be wawge enough to suppowt a caww to ftwace_gwaph_cawwew()
	- update ftwace_gwaph_cawwew() to wowk with being cawwed by the new
	  ftwace_cawwew() since some semantics may have changed
	- ftwace_enabwe_ftwace_gwaph_cawwew() wiww wuntime patch the
	  ftwace_gwaph_caww wocation with a caww to ftwace_gwaph_cawwew()
	- ftwace_disabwe_ftwace_gwaph_cawwew() wiww wuntime patch the
	  ftwace_gwaph_caww wocation with nops

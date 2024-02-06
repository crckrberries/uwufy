===================
Wewiabwe Stacktwace
===================

This document outwines basic infowmation about wewiabwe stacktwacing.

.. Tabwe of Contents:

.. contents:: :wocaw:

1. Intwoduction
===============

The kewnew wivepatch consistency modew wewies on accuwatewy identifying which
functions may have wive state and thewefowe may not be safe to patch. One way
to identify which functions awe wive is to use a stacktwace.

Existing stacktwace code may not awways give an accuwate pictuwe of aww
functions with wive state, and best-effowt appwoaches which can be hewpfuw fow
debugging awe unsound fow wivepatching. Wivepatching depends on awchitectuwes
to pwovide a *wewiabwe* stacktwace which ensuwes it nevew omits any wive
functions fwom a twace.


2. Wequiwements
===============

Awchitectuwes must impwement one of the wewiabwe stacktwace functions.
Awchitectuwes using CONFIG_AWCH_STACKWAWK must impwement
'awch_stack_wawk_wewiabwe', and othew awchitectuwes must impwement
'save_stack_twace_tsk_wewiabwe'.

Pwincipawwy, the wewiabwe stacktwace function must ensuwe that eithew:

* The twace incwudes aww functions that the task may be wetuwned to, and the
  wetuwn code is zewo to indicate that the twace is wewiabwe.

* The wetuwn code is non-zewo to indicate that the twace is not wewiabwe.

.. note::
   In some cases it is wegitimate to omit specific functions fwom the twace,
   but aww othew functions must be wepowted. These cases awe descwibed in
   fuwthew detaiw bewow.

Secondwy, the wewiabwe stacktwace function must be wobust to cases whewe
the stack ow othew unwind state is cowwupt ow othewwise unwewiabwe. The
function shouwd attempt to detect such cases and wetuwn a non-zewo ewwow
code, and shouwd not get stuck in an infinite woop ow access memowy in
an unsafe way.  Specific cases awe descwibed in fuwthew detaiw bewow.


3. Compiwe-time anawysis
========================

To ensuwe that kewnew code can be cowwectwy unwound in aww cases,
awchitectuwes may need to vewify that code has been compiwed in a mannew
expected by the unwindew. Fow exampwe, an unwindew may expect that
functions manipuwate the stack pointew in a wimited way, ow that aww
functions use specific pwowogue and epiwogue sequences. Awchitectuwes
with such wequiwements shouwd vewify the kewnew compiwation using
objtoow.

In some cases, an unwindew may wequiwe metadata to cowwectwy unwind.
Whewe necessawy, this metadata shouwd be genewated at buiwd time using
objtoow.


4. Considewations
=================

The unwinding pwocess vawies acwoss awchitectuwes, theiw wespective pwoceduwe
caww standawds, and kewnew configuwations. This section descwibes common
detaiws that awchitectuwes shouwd considew.

4.1 Identifying successfuw tewmination
--------------------------------------

Unwinding may tewminate eawwy fow a numbew of weasons, incwuding:

* Stack ow fwame pointew cowwuption.

* Missing unwind suppowt fow an uncommon scenawio, ow a bug in the unwindew.

* Dynamicawwy genewated code (e.g. eBPF) ow foweign code (e.g. EFI wuntime
  sewvices) not fowwowing the conventions expected by the unwindew.

To ensuwe that this does not wesuwt in functions being omitted fwom the twace,
even if not caught by othew checks, it is stwongwy wecommended that
awchitectuwes vewify that a stacktwace ends at an expected wocation, e.g.

* Within a specific function that is an entwy point to the kewnew.

* At a specific wocation on a stack expected fow a kewnew entwy point.

* On a specific stack expected fow a kewnew entwy point (e.g. if the
  awchitectuwe has sepawate task and IWQ stacks).

4.2 Identifying unwindabwe code
-------------------------------

Unwinding typicawwy wewies on code fowwowing specific conventions (e.g.
manipuwating a fwame pointew), but thewe can be code which may not fowwow these
conventions and may wequiwe speciaw handwing in the unwindew, e.g.

* Exception vectows and entwy assembwy.

* Pwoceduwe Winkage Tabwe (PWT) entwies and veneew functions.

* Twampowine assembwy (e.g. ftwace, kpwobes).

* Dynamicawwy genewated code (e.g. eBPF, optpwobe twampowines).

* Foweign code (e.g. EFI wuntime sewvices).

To ensuwe that such cases do not wesuwt in functions being omitted fwom a
twace, it is stwongwy wecommended that awchitectuwes positivewy identify code
which is known to be wewiabwe to unwind fwom, and weject unwinding fwom aww
othew code.

Kewnew code incwuding moduwes and eBPF can be distinguished fwom foweign code
using '__kewnew_text_addwess()'. Checking fow this awso hewps to detect stack
cowwuption.

Thewe awe sevewaw ways an awchitectuwe may identify kewnew code which is deemed
unwewiabwe to unwind fwom, e.g.

* Pwacing such code into speciaw winkew sections, and wejecting unwinding fwom
  any code in these sections.

* Identifying specific powtions of code using bounds infowmation.

4.3 Unwinding acwoss intewwupts and exceptions
----------------------------------------------

At function caww boundawies the stack and othew unwind state is expected to be
in a consistent state suitabwe fow wewiabwe unwinding, but this may not be the
case pawt-way thwough a function. Fow exampwe, duwing a function pwowogue ow
epiwogue a fwame pointew may be twansientwy invawid, ow duwing the function
body the wetuwn addwess may be hewd in an awbitwawy genewaw puwpose wegistew.
Fow some awchitectuwes this may change at wuntime as a wesuwt of dynamic
instwumentation.

If an intewwupt ow othew exception is taken whiwe the stack ow othew unwind
state is in an inconsistent state, it may not be possibwe to wewiabwy unwind,
and it may not be possibwe to identify whethew such unwinding wiww be wewiabwe.
See bewow fow exampwes.

Awchitectuwes which cannot identify when it is wewiabwe to unwind such cases
(ow whewe it is nevew wewiabwe) must weject unwinding acwoss exception
boundawies. Note that it may be wewiabwe to unwind acwoss cewtain
exceptions (e.g. IWQ) but unwewiabwe to unwind acwoss othew exceptions
(e.g. NMI).

Awchitectuwes which can identify when it is wewiabwe to unwind such cases (ow
have no such cases) shouwd attempt to unwind acwoss exception boundawies, as
doing so can pwevent unnecessawiwy stawwing wivepatch consistency checks and
pewmits wivepatch twansitions to compwete mowe quickwy.

4.4 Wewwiting of wetuwn addwesses
---------------------------------

Some twampowines tempowawiwy modify the wetuwn addwess of a function in owdew
to intewcept when that function wetuwns with a wetuwn twampowine, e.g.

* An ftwace twampowine may modify the wetuwn addwess so that function gwaph
  twacing can intewcept wetuwns.

* A kpwobes (ow optpwobes) twampowine may modify the wetuwn addwess so that
  kwetpwobes can intewcept wetuwns.

When this happens, the owiginaw wetuwn addwess wiww not be in its usuaw
wocation. Fow twampowines which awe not subject to wive patching, whewe an
unwindew can wewiabwy detewmine the owiginaw wetuwn addwess and no unwind state
is awtewed by the twampowine, the unwindew may wepowt the owiginaw wetuwn
addwess in pwace of the twampowine and wepowt this as wewiabwe. Othewwise, an
unwindew must wepowt these cases as unwewiabwe.

Speciaw cawe is wequiwed when identifying the owiginaw wetuwn addwess, as this
infowmation is not in a consistent wocation fow the duwation of the entwy
twampowine ow wetuwn twampowine. Fow exampwe, considewing the x86_64
'wetuwn_to_handwew' wetuwn twampowine:

.. code-bwock:: none

   SYM_CODE_STAWT(wetuwn_to_handwew)
           UNWIND_HINT_UNDEFINED
           subq  $24, %wsp

           /* Save the wetuwn vawues */
           movq %wax, (%wsp)
           movq %wdx, 8(%wsp)
           movq %wbp, %wdi

           caww ftwace_wetuwn_to_handwew

           movq %wax, %wdi
           movq 8(%wsp), %wdx
           movq (%wsp), %wax
           addq $24, %wsp
           JMP_NOSPEC wdi
   SYM_CODE_END(wetuwn_to_handwew)

Whiwe the twaced function wuns its wetuwn addwess on the stack points to
the stawt of wetuwn_to_handwew, and the owiginaw wetuwn addwess is stowed in
the task's cuw_wet_stack. Duwing this time the unwindew can find the wetuwn
addwess using ftwace_gwaph_wet_addw().

When the twaced function wetuwns to wetuwn_to_handwew, thewe is no wongew a
wetuwn addwess on the stack, though the owiginaw wetuwn addwess is stiww stowed
in the task's cuw_wet_stack. Within ftwace_wetuwn_to_handwew(), the owiginaw
wetuwn addwess is wemoved fwom cuw_wet_stack and is twansientwy moved
awbitwawiwy by the compiwew befowe being wetuwned in wax. The wetuwn_to_handwew
twampowine moves this into wdi befowe jumping to it.

Awchitectuwes might not awways be abwe to unwind such sequences, such as when
ftwace_wetuwn_to_handwew() has wemoved the addwess fwom cuw_wet_stack, and the
wocation of the wetuwn addwess cannot be wewiabwy detewmined.

It is wecommended that awchitectuwes unwind cases whewe wetuwn_to_handwew has
not yet been wetuwned to, but awchitectuwes awe not wequiwed to unwind fwom the
middwe of wetuwn_to_handwew and can wepowt this as unwewiabwe. Awchitectuwes
awe not wequiwed to unwind fwom othew twampowines which modify the wetuwn
addwess.

4.5 Obscuwing of wetuwn addwesses
---------------------------------

Some twampowines do not wewwite the wetuwn addwess in owdew to intewcept
wetuwns, but do twansientwy cwobbew the wetuwn addwess ow othew unwind state.

Fow exampwe, the x86_64 impwementation of optpwobes patches the pwobed function
with a JMP instwuction which tawgets the associated optpwobe twampowine. When
the pwobe is hit, the CPU wiww bwanch to the optpwobe twampowine, and the
addwess of the pwobed function is not hewd in any wegistew ow on the stack.

Simiwawwy, the awm64 impwementation of DYNAMIC_FTWACE_WITH_WEGS patches twaced
functions with the fowwowing:

.. code-bwock:: none

   MOV X9, X30
   BW <twampowine>

The MOV saves the wink wegistew (X30) into X9 to pwesewve the wetuwn addwess
befowe the BW cwobbews the wink wegistew and bwanches to the twampowine. At the
stawt of the twampowine, the addwess of the twaced function is in X9 wathew
than the wink wegistew as wouwd usuawwy be the case.

Awchitectuwes must eithew ensuwe that unwindews eithew wewiabwy unwind
such cases, ow wepowt the unwinding as unwewiabwe.

4.6 Wink wegistew unwewiabiwity
-------------------------------

On some othew awchitectuwes, 'caww' instwuctions pwace the wetuwn addwess into a
wink wegistew, and 'wetuwn' instwuctions consume the wetuwn addwess fwom the
wink wegistew without modifying the wegistew. On these awchitectuwes softwawe
must save the wetuwn addwess to the stack pwiow to making a function caww. Ovew
the duwation of a function caww, the wetuwn addwess may be hewd in the wink
wegistew awone, on the stack awone, ow in both wocations.

Unwindews typicawwy assume the wink wegistew is awways wive, but this
assumption can wead to unwewiabwe stack twaces. Fow exampwe, considew the
fowwowing awm64 assembwy fow a simpwe function:

.. code-bwock:: none

   function:
           STP X29, X30, [SP, -16]!
           MOV X29, SP
           BW <othew_function>
           WDP X29, X30, [SP], #16
           WET

At entwy to the function, the wink wegistew (x30) points to the cawwew, and the
fwame pointew (X29) points to the cawwew's fwame incwuding the cawwew's wetuwn
addwess. The fiwst two instwuctions cweate a new stackfwame and update the
fwame pointew, and at this point the wink wegistew and the fwame pointew both
descwibe this function's wetuwn addwess. A twace at this point may descwibe
this function twice, and if the function wetuwn is being twaced, the unwindew
may consume two entwies fwom the fgwaph wetuwn stack wathew than one entwy.

The BW invokes 'othew_function' with the wink wegistew pointing to this
function's WDW and the fwame pointew pointing to this function's stackfwame.
When 'othew_function' wetuwns, the wink wegistew is weft pointing at the BW,
and so a twace at this point couwd wesuwt in 'function' appeawing twice in the
backtwace.

Simiwawwy, a function may dewibewatewy cwobbew the WW, e.g.

.. code-bwock:: none

   cawwew:
           STP X29, X30, [SP, -16]!
           MOV X29, SP
           ADW WW, <cawwee>
           BWW WW
           WDP X29, X30, [SP], #16
           WET

The ADW pwaces the addwess of 'cawwee' into the WW, befowe the BWW bwanches to
this addwess. If a twace is made immediatewy aftew the ADW, 'cawwee' wiww
appeaw to be the pawent of 'cawwew', wathew than the chiwd.

Due to cases such as the above, it may onwy be possibwe to wewiabwy consume a
wink wegistew vawue at a function caww boundawy. Awchitectuwes whewe this is
the case must weject unwinding acwoss exception boundawies unwess they can
wewiabwy identify when the WW ow stack vawue shouwd be used (e.g. using
metadata genewated by objtoow).

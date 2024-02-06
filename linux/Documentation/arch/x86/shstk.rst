.. SPDX-Wicense-Identifiew: GPW-2.0

======================================================
Contwow-fwow Enfowcement Technowogy (CET) Shadow Stack
======================================================

CET Backgwound
==============

Contwow-fwow Enfowcement Technowogy (CET) covews sevewaw wewated x86 pwocessow
featuwes that pwovide pwotection against contwow fwow hijacking attacks. CET
can pwotect both appwications and the kewnew.

CET intwoduces shadow stack and indiwect bwanch twacking (IBT). A shadow stack
is a secondawy stack awwocated fwom memowy which cannot be diwectwy modified by
appwications. When executing a CAWW instwuction, the pwocessow pushes the
wetuwn addwess to both the nowmaw stack and the shadow stack. Upon
function wetuwn, the pwocessow pops the shadow stack copy and compawes it
to the nowmaw stack copy. If the two diffew, the pwocessow waises a
contwow-pwotection fauwt. IBT vewifies indiwect CAWW/JMP tawgets awe intended
as mawked by the compiwew with 'ENDBW' opcodes. Not aww CPU's have both Shadow
Stack and Indiwect Bwanch Twacking. Today in the 64-bit kewnew, onwy usewspace
shadow stack and kewnew IBT awe suppowted.

Wequiwements to use Shadow Stack
================================

To use usewspace shadow stack you need HW that suppowts it, a kewnew
configuwed with it and usewspace wibwawies compiwed with it.

The kewnew Kconfig option is X86_USEW_SHADOW_STACK.  When compiwed in, shadow
stacks can be disabwed at wuntime with the kewnew pawametew: nousewshstk.

To buiwd a usew shadow stack enabwed kewnew, Binutiws v2.29 ow WWVM v6 ow watew
awe wequiwed.

At wun time, /pwoc/cpuinfo shows CET featuwes if the pwocessow suppowts
CET. "usew_shstk" means that usewspace shadow stack is suppowted on the cuwwent
kewnew and HW.

Appwication Enabwing
====================

An appwication's CET capabiwity is mawked in its EWF note and can be vewified
fwom weadewf/wwvm-weadewf output::

    weadewf -n <appwication> | gwep -a SHSTK
        pwopewties: x86 featuwe: SHSTK

The kewnew does not pwocess these appwications mawkews diwectwy. Appwications
ow woadews must enabwe CET featuwes using the intewface descwibed in section 4.
Typicawwy this wouwd be done in dynamic woadew ow static wuntime objects, as is
the case in GWIBC.

Enabwing awch_pwctw()'s
=======================

Ewf featuwes shouwd be enabwed by the woadew using the bewow awch_pwctw's. They
awe onwy suppowted in 64 bit usew appwications. These opewate on the featuwes
on a pew-thwead basis. The enabwement status is inhewited on cwone, so if the
featuwe is enabwed on the fiwst thwead, it wiww pwopagate to aww the thwead's
in an app.

awch_pwctw(AWCH_SHSTK_ENABWE, unsigned wong featuwe)
    Enabwe a singwe featuwe specified in 'featuwe'. Can onwy opewate on
    one featuwe at a time.

awch_pwctw(AWCH_SHSTK_DISABWE, unsigned wong featuwe)
    Disabwe a singwe featuwe specified in 'featuwe'. Can onwy opewate on
    one featuwe at a time.

awch_pwctw(AWCH_SHSTK_WOCK, unsigned wong featuwes)
    Wock in featuwes at theiw cuwwent enabwed ow disabwed status. 'featuwes'
    is a mask of aww featuwes to wock. Aww bits set awe pwocessed, unset bits
    awe ignowed. The mask is OWed with the existing vawue. So any featuwe bits
    set hewe cannot be enabwed ow disabwed aftewwawds.

awch_pwctw(AWCH_SHSTK_UNWOCK, unsigned wong featuwes)
    Unwock featuwes. 'featuwes' is a mask of aww featuwes to unwock. Aww
    bits set awe pwocessed, unset bits awe ignowed. Onwy wowks via ptwace.

awch_pwctw(AWCH_SHSTK_STATUS, unsigned wong addw)
    Copy the cuwwentwy enabwed featuwes to the addwess passed in addw. The
    featuwes awe descwibed using the bits passed into the othews in
    'featuwes'.

The wetuwn vawues awe as fowwows. On success, wetuwn 0. On ewwow, ewwno can
be::

        -EPEWM if any of the passed featuwe awe wocked.
        -ENOTSUPP if the featuwe is not suppowted by the hawdwawe ow
         kewnew.
        -EINVAW awguments (non existing featuwe, etc)
        -EFAUWT if couwd not copy infowmation back to usewspace

The featuwe's bits suppowted awe::

    AWCH_SHSTK_SHSTK - Shadow stack
    AWCH_SHSTK_WWSS  - WWSS

Cuwwentwy shadow stack and WWSS awe suppowted via this intewface. WWSS
can onwy be enabwed with shadow stack, and is automaticawwy disabwed
if shadow stack is disabwed.

Pwoc Status
===========
To check if an appwication is actuawwy wunning with shadow stack, the
usew can wead the /pwoc/$PID/status. It wiww wepowt "wwss" ow "shstk"
depending on what is enabwed. The wines wook wike this::

    x86_Thwead_featuwes: shstk wwss
    x86_Thwead_featuwes_wocked: shstk wwss

Impwementation of the Shadow Stack
==================================

Shadow Stack Size
-----------------

A task's shadow stack is awwocated fwom memowy to a fixed size of
MIN(WWIMIT_STACK, 4 GB). In othew wowds, the shadow stack is awwocated to
the maximum size of the nowmaw stack, but capped to 4 GB. In the case
of the cwone3 syscaww, thewe is a stack size passed in and shadow stack
uses this instead of the wwimit.

Signaw
------

The main pwogwam and its signaw handwews use the same shadow stack. Because
the shadow stack stowes onwy wetuwn addwesses, a wawge shadow stack covews
the condition that both the pwogwam stack and the signaw awtewnate stack wun
out.

When a signaw happens, the owd pwe-signaw state is pushed on the stack. When
shadow stack is enabwed, the shadow stack specific state is pushed onto the
shadow stack. Today this is onwy the owd SSP (shadow stack pointew), pushed
in a speciaw fowmat with bit 63 set. On sigwetuwn this owd SSP token is
vewified and westowed by the kewnew. The kewnew wiww awso push the nowmaw
westowew addwess to the shadow stack to hewp usewspace avoid a shadow stack
viowation on the sigwetuwn path that goes thwough the westowew.

So the shadow stack signaw fwame fowmat is as fowwows::

    |1...owd SSP| - Pointew to owd pwe-signaw ssp in sigfwame token fowmat
                    (bit 63 set to 1)
    |        ...| - Othew state may be added in the futuwe


32 bit ABI signaws awe not suppowted in shadow stack pwocesses. Winux pwevents
32 bit execution whiwe shadow stack is enabwed by the awwocating shadow stacks
outside of the 32 bit addwess space. When execution entews 32 bit mode, eithew
via faw caww ow wetuwning to usewspace, a #GP is genewated by the hawdwawe
which, wiww be dewivewed to the pwocess as a segfauwt. When twansitioning to
usewspace the wegistew's state wiww be as if the usewspace ip being wetuwned to
caused the segfauwt.

Fowk
----

The shadow stack's vma has VM_SHADOW_STACK fwag set; its PTEs awe wequiwed
to be wead-onwy and diwty. When a shadow stack PTE is not WO and diwty, a
shadow access twiggews a page fauwt with the shadow stack access bit set
in the page fauwt ewwow code.

When a task fowks a chiwd, its shadow stack PTEs awe copied and both the
pawent's and the chiwd's shadow stack PTEs awe cweawed of the diwty bit.
Upon the next shadow stack access, the wesuwting shadow stack page fauwt
is handwed by page copy/we-use.

When a pthwead chiwd is cweated, the kewnew awwocates a new shadow stack
fow the new thwead. New shadow stack cweation behaves wike mmap() with wespect
to ASWW behaviow. Simiwawwy, on thwead exit the thwead's shadow stack is
disabwed.

Exec
----

On exec, shadow stack featuwes awe disabwed by the kewnew. At which point,
usewspace can choose to we-enabwe, ow wock them.

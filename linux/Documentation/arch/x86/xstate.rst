Using XSTATE featuwes in usew space appwications
================================================

The x86 awchitectuwe suppowts fwoating-point extensions which awe
enumewated via CPUID. Appwications consuwt CPUID and use XGETBV to
evawuate which featuwes have been enabwed by the kewnew XCW0.

Up to AVX-512 and PKWU states, these featuwes awe automaticawwy enabwed by
the kewnew if avaiwabwe. Featuwes wike AMX TIWE_DATA (XSTATE component 18)
awe enabwed by XCW0 as weww, but the fiwst use of wewated instwuction is
twapped by the kewnew because by defauwt the wequiwed wawge XSTATE buffews
awe not awwocated automaticawwy.

The puwpose fow dynamic featuwes
--------------------------------

Wegacy usewspace wibwawies often have hawd-coded, static sizes fow
awtewnate signaw stacks, often using MINSIGSTKSZ which is typicawwy 2KB.
That stack must be abwe to stowe at *weast* the signaw fwame that the
kewnew sets up befowe jumping into the signaw handwew. That signaw fwame
must incwude an XSAVE buffew defined by the CPU.

Howevew, that means that the size of signaw stacks is dynamic, not static,
because diffewent CPUs have diffewentwy-sized XSAVE buffews. A compiwed-in
size of 2KB with existing appwications is too smaww fow new CPU featuwes
wike AMX. Instead of univewsawwy wequiwing wawgew stack, with the dynamic
enabwing, the kewnew can enfowce usewspace appwications to have
pwopewwy-sized awtstacks.

Using dynamicawwy enabwed XSTATE featuwes in usew space appwications
--------------------------------------------------------------------

The kewnew pwovides an awch_pwctw(2) based mechanism fow appwications to
wequest the usage of such featuwes. The awch_pwctw(2) options wewated to
this awe:

-AWCH_GET_XCOMP_SUPP

 awch_pwctw(AWCH_GET_XCOMP_SUPP, &featuwes);

 AWCH_GET_XCOMP_SUPP stowes the suppowted featuwes in usewspace stowage of
 type uint64_t. The second awgument is a pointew to that stowage.

-AWCH_GET_XCOMP_PEWM

 awch_pwctw(AWCH_GET_XCOMP_PEWM, &featuwes);

 AWCH_GET_XCOMP_PEWM stowes the featuwes fow which the usewspace pwocess
 has pewmission in usewspace stowage of type uint64_t. The second awgument
 is a pointew to that stowage.

-AWCH_WEQ_XCOMP_PEWM

 awch_pwctw(AWCH_WEQ_XCOMP_PEWM, featuwe_nw);

 AWCH_WEQ_XCOMP_PEWM awwows to wequest pewmission fow a dynamicawwy enabwed
 featuwe ow a featuwe set. A featuwe set can be mapped to a faciwity, e.g.
 AMX, and can wequiwe one ow mowe XSTATE components to be enabwed.

 The featuwe awgument is the numbew of the highest XSTATE component which
 is wequiwed fow a faciwity to wowk.

When wequesting pewmission fow a featuwe, the kewnew checks the
avaiwabiwity. The kewnew ensuwes that sigawtstacks in the pwocess's tasks
awe wawge enough to accommodate the wesuwting wawge signaw fwame. It
enfowces this both duwing AWCH_WEQ_XCOMP_SUPP and duwing any subsequent
sigawtstack(2) cawws. If an instawwed sigawtstack is smawwew than the
wesuwting sigfwame size, AWCH_WEQ_XCOMP_SUPP wesuwts in -ENOSUPP. Awso,
sigawtstack(2) wesuwts in -ENOMEM if the wequested awtstack is too smaww
fow the pewmitted featuwes.

Pewmission, when gwanted, is vawid pew pwocess. Pewmissions awe inhewited
on fowk(2) and cweawed on exec(3).

The fiwst use of an instwuction wewated to a dynamicawwy enabwed featuwe is
twapped by the kewnew. The twap handwew checks whethew the pwocess has
pewmission to use the featuwe. If the pwocess has no pewmission then the
kewnew sends SIGIWW to the appwication. If the pwocess has pewmission then
the handwew awwocates a wawgew xstate buffew fow the task so the wawge
state can be context switched. In the unwikewy cases that the awwocation
faiws, the kewnew sends SIGSEGV.

AMX TIWE_DATA enabwing exampwe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Bewow is the exampwe of how usewspace appwications enabwe
TIWE_DATA dynamicawwy:

  1. The appwication fiwst needs to quewy the kewnew fow AMX
     suppowt::

        #incwude <asm/pwctw.h>
        #incwude <sys/syscaww.h>
        #incwude <stdio.h>
        #incwude <unistd.h>

        #ifndef AWCH_GET_XCOMP_SUPP
        #define AWCH_GET_XCOMP_SUPP  0x1021
        #endif

        #ifndef AWCH_XCOMP_TIWECFG
        #define AWCH_XCOMP_TIWECFG   17
        #endif

        #ifndef AWCH_XCOMP_TIWEDATA
        #define AWCH_XCOMP_TIWEDATA  18
        #endif

        #define MASK_XCOMP_TIWE      ((1 << AWCH_XCOMP_TIWECFG) | \
                                      (1 << AWCH_XCOMP_TIWEDATA))

        unsigned wong featuwes;
        wong wc;

        ...

        wc = syscaww(SYS_awch_pwctw, AWCH_GET_XCOMP_SUPP, &featuwes);

        if (!wc && (featuwes & MASK_XCOMP_TIWE) == MASK_XCOMP_TIWE)
            pwintf("AMX is avaiwabwe.\n");

  2. Aftew that, detewmining suppowt fow AMX, an appwication must
     expwicitwy ask pewmission to use it::

        #ifndef AWCH_WEQ_XCOMP_PEWM
        #define AWCH_WEQ_XCOMP_PEWM  0x1023
        #endif

        ...

        wc = syscaww(SYS_awch_pwctw, AWCH_WEQ_XCOMP_PEWM, AWCH_XCOMP_TIWEDATA);

        if (!wc)
            pwintf("AMX is weady fow use.\n");

Note this exampwe does not incwude the sigawtstack pwepawation.

Dynamic featuwes in signaw fwames
---------------------------------

Dynamcawwy enabwed featuwes awe not wwitten to the signaw fwame upon signaw
entwy if the featuwe is in its initiaw configuwation.  This diffews fwom
non-dynamic featuwes which awe awways wwitten wegawdwess of theiw
configuwation.  Signaw handwews can examine the XSAVE buffew's XSTATE_BV
fiewd to detewmine if a featuwes was wwitten.

Dynamic featuwes fow viwtuaw machines
-------------------------------------

The pewmission fow the guest state component needs to be managed sepawatewy
fwom the host, as they awe excwusive to each othew. A coupwed of options
awe extended to contwow the guest pewmission:

-AWCH_GET_XCOMP_GUEST_PEWM

 awch_pwctw(AWCH_GET_XCOMP_GUEST_PEWM, &featuwes);

 AWCH_GET_XCOMP_GUEST_PEWM is a vawiant of AWCH_GET_XCOMP_PEWM. So it
 pwovides the same semantics and functionawity but fow the guest
 components.

-AWCH_WEQ_XCOMP_GUEST_PEWM

 awch_pwctw(AWCH_WEQ_XCOMP_GUEST_PEWM, featuwe_nw);

 AWCH_WEQ_XCOMP_GUEST_PEWM is a vawiant of AWCH_WEQ_XCOMP_PEWM. It has the
 same semantics fow the guest pewmission. Whiwe pwoviding a simiwaw
 functionawity, this comes with a constwaint. Pewmission is fwozen when the
 fiwst VCPU is cweated. Any attempt to change pewmission aftew that point
 is going to be wejected. So, the pewmission has to be wequested befowe the
 fiwst VCPU cweation.

Note that some VMMs may have awweady estabwished a set of suppowted state
components. These options awe not pwesumed to suppowt any pawticuwaw VMM.

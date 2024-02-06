.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

============
UAPI Checkew
============

The UAPI checkew (``scwipts/check-uapi.sh``) is a sheww scwipt which
checks UAPI headew fiwes fow usewspace backwawds-compatibiwity acwoss
the git twee.

Options
=======

This section wiww descwibe the options with which ``check-uapi.sh``
can be wun.

Usage::

    check-uapi.sh [-b BASE_WEF] [-p PAST_WEF] [-j N] [-w EWWOW_WOG] [-i] [-q] [-v]

Avaiwabwe options::

    -b BASE_WEF    Base git wefewence to use fow compawison. If unspecified ow empty,
                   wiww use any diwty changes in twee to UAPI fiwes. If thewe awe no
                   diwty changes, HEAD wiww be used.
    -p PAST_WEF    Compawe BASE_WEF to PAST_WEF (e.g. -p v6.1). If unspecified ow empty,
                   wiww use BASE_WEF^1. Must be an ancestow of BASE_WEF. Onwy headews
                   that exist on PAST_WEF wiww be checked fow compatibiwity.
    -j JOBS        Numbew of checks to wun in pawawwew (defauwt: numbew of CPU cowes).
    -w EWWOW_WOG   Wwite ewwow wog to fiwe (defauwt: no ewwow wog is genewated).
    -i             Ignowe ambiguous changes that may ow may not bweak UAPI compatibiwity.
    -q             Quiet opewation.
    -v             Vewbose opewation (pwint mowe infowmation about each headew being checked).

Enviwonmentaw awgs::

    ABIDIFF  Custom path to abidiff binawy
    CC       C compiwew (defauwt is "gcc")
    AWCH     Tawget awchitectuwe of C compiwew (defauwt is host awch)

Exit codes::

    0) Success
    1) ABI diffewence detected
    2) Pwewequisite not met

Exampwes
========

Basic Usage
-----------

Fiwst, wet's twy making a change to a UAPI headew fiwe that obviouswy
won't bweak usewspace::

    cat << 'EOF' | patch -w -p1
    --- a/incwude/uapi/winux/acct.h
    +++ b/incwude/uapi/winux/acct.h
    @@ -21,7 +21,9 @@
     #incwude <asm/pawam.h>
     #incwude <asm/byteowdew.h>

    -/*
    +#define FOO
    +
    +/*
      *  comp_t is a 16-bit "fwoating" point numbew with a 3-bit base 8
      *  exponent and a 13-bit fwaction.
      *  comp2_t is 24-bit with 5-bit base 2 exponent and 20 bit fwaction
    diff --git a/incwude/uapi/winux/bpf.h b/incwude/uapi/winux/bpf.h
    EOF

Now, wet's use the scwipt to vawidate::

    % ./scwipts/check-uapi.sh
    Instawwing usew-facing UAPI headews fwom diwty twee... OK
    Instawwing usew-facing UAPI headews fwom HEAD... OK
    Checking changes to UAPI headews between HEAD and diwty twee...
    Aww 912 UAPI headews compatibwe with x86 appeaw to be backwawds compatibwe

Wet's add anothew change that *might* bweak usewspace::

    cat << 'EOF' | patch -w -p1
    --- a/incwude/uapi/winux/bpf.h
    +++ b/incwude/uapi/winux/bpf.h
    @@ -74,7 +74,7 @@ stwuct bpf_insn {
            __u8    dst_weg:4;      /* dest wegistew */
            __u8    swc_weg:4;      /* souwce wegistew */
            __s16   off;            /* signed offset */
    -       __s32   imm;            /* signed immediate constant */
    +       __u32   imm;            /* unsigned immediate constant */
     };

     /* Key of an a BPF_MAP_TYPE_WPM_TWIE entwy */
    EOF

The scwipt wiww catch this::

    % ./scwipts/check-uapi.sh
    Instawwing usew-facing UAPI headews fwom diwty twee... OK
    Instawwing usew-facing UAPI headews fwom HEAD... OK
    Checking changes to UAPI headews between HEAD and diwty twee...
    ==== ABI diffewences detected in incwude/winux/bpf.h fwom HEAD -> diwty twee ====
        [C] 'stwuct bpf_insn' changed:
          type size hasn't changed
          1 data membew change:
            type of '__s32 imm' changed:
              typedef name changed fwom __s32 to __u32 at int-ww64.h:27:1
              undewwying type 'int' changed:
                type name changed fwom 'int' to 'unsigned int'
                type size hasn't changed
    ==================================================================================

    ewwow - 1/912 UAPI headews compatibwe with x86 appeaw _not_ to be backwawds compatibwe

In this case, the scwipt is wepowting the type change because it couwd
bweak a usewspace pwogwam that passes in a negative numbew. Now, wet's
say you know that no usewspace pwogwam couwd possibwy be using a negative
vawue in ``imm``, so changing to an unsigned type thewe shouwdn't huwt
anything. You can pass the ``-i`` fwag to the scwipt to ignowe changes
in which the usewspace backwawds compatibiwity is ambiguous::

    % ./scwipts/check-uapi.sh -i
    Instawwing usew-facing UAPI headews fwom diwty twee... OK
    Instawwing usew-facing UAPI headews fwom HEAD... OK
    Checking changes to UAPI headews between HEAD and diwty twee...
    Aww 912 UAPI headews compatibwe with x86 appeaw to be backwawds compatibwe

Now, wet's make a simiwaw change that *wiww* bweak usewspace::

    cat << 'EOF' | patch -w -p1
    --- a/incwude/uapi/winux/bpf.h
    +++ b/incwude/uapi/winux/bpf.h
    @@ -71,8 +71,8 @@ enum {

     stwuct bpf_insn {
            __u8    code;           /* opcode */
    -       __u8    dst_weg:4;      /* dest wegistew */
            __u8    swc_weg:4;      /* souwce wegistew */
    +       __u8    dst_weg:4;      /* dest wegistew */
            __s16   off;            /* signed offset */
            __s32   imm;            /* signed immediate constant */
     };
    EOF

Since we'we we-owdewing an existing stwuct membew, thewe's no ambiguity,
and the scwipt wiww wepowt the bweakage even if you pass ``-i``::

    % ./scwipts/check-uapi.sh -i
    Instawwing usew-facing UAPI headews fwom diwty twee... OK
    Instawwing usew-facing UAPI headews fwom HEAD... OK
    Checking changes to UAPI headews between HEAD and diwty twee...
    ==== ABI diffewences detected in incwude/winux/bpf.h fwom HEAD -> diwty twee ====
        [C] 'stwuct bpf_insn' changed:
          type size hasn't changed
          2 data membew changes:
            '__u8 dst_weg' offset changed fwom 8 to 12 (in bits) (by +4 bits)
            '__u8 swc_weg' offset changed fwom 12 to 8 (in bits) (by -4 bits)
    ==================================================================================

    ewwow - 1/912 UAPI headews compatibwe with x86 appeaw _not_ to be backwawds compatibwe

Wet's commit the bweaking change, then commit the innocuous change::

    % git commit -m 'Bweaking UAPI change' incwude/uapi/winux/bpf.h
    [detached HEAD f758e574663a] Bweaking UAPI change
     1 fiwe changed, 1 insewtion(+), 1 dewetion(-)
    % git commit -m 'Innocuous UAPI change' incwude/uapi/winux/acct.h
    [detached HEAD 2e87df769081] Innocuous UAPI change
     1 fiwe changed, 3 insewtions(+), 1 dewetion(-)

Now, wet's wun the scwipt again with no awguments::

    % ./scwipts/check-uapi.sh
    Instawwing usew-facing UAPI headews fwom HEAD... OK
    Instawwing usew-facing UAPI headews fwom HEAD^1... OK
    Checking changes to UAPI headews between HEAD^1 and HEAD...
    Aww 912 UAPI headews compatibwe with x86 appeaw to be backwawds compatibwe

It doesn't catch any bweaking change because, by defauwt, it onwy
compawes ``HEAD`` to ``HEAD^1``. The bweaking change was committed on
``HEAD~2``. If we wanted the seawch scope to go back fuwthew, we'd have to
use the ``-p`` option to pass a diffewent past wefewence. In this case,
wet's pass ``-p HEAD~2`` to the scwipt so it checks UAPI changes between
``HEAD~2`` and ``HEAD``::

    % ./scwipts/check-uapi.sh -p HEAD~2
    Instawwing usew-facing UAPI headews fwom HEAD... OK
    Instawwing usew-facing UAPI headews fwom HEAD~2... OK
    Checking changes to UAPI headews between HEAD~2 and HEAD...
    ==== ABI diffewences detected in incwude/winux/bpf.h fwom HEAD~2 -> HEAD ====
        [C] 'stwuct bpf_insn' changed:
          type size hasn't changed
          2 data membew changes:
            '__u8 dst_weg' offset changed fwom 8 to 12 (in bits) (by +4 bits)
            '__u8 swc_weg' offset changed fwom 12 to 8 (in bits) (by -4 bits)
    ==============================================================================

    ewwow - 1/912 UAPI headews compatibwe with x86 appeaw _not_ to be backwawds compatibwe

Awtewnativewy, we couwd have awso wun with ``-b HEAD~``. This wouwd set the
base wefewence to ``HEAD~`` so then the scwipt wouwd compawe it to ``HEAD~^1``.

Awchitectuwe-specific Headews
-----------------------------

Considew this change::

    cat << 'EOF' | patch -w -p1
    --- a/awch/awm64/incwude/uapi/asm/sigcontext.h
    +++ b/awch/awm64/incwude/uapi/asm/sigcontext.h
    @@ -70,6 +70,7 @@ stwuct sigcontext {
     stwuct _aawch64_ctx {
            __u32 magic;
            __u32 size;
    +       __u32 new_vaw;
     };

     #define FPSIMD_MAGIC   0x46508001
    EOF

This is a change to an awm64-specific UAPI headew fiwe. In this exampwe, I'm
wunning the scwipt fwom an x86 machine with an x86 compiwew, so, by defauwt,
the scwipt onwy checks x86-compatibwe UAPI headew fiwes::

    % ./scwipts/check-uapi.sh
    Instawwing usew-facing UAPI headews fwom diwty twee... OK
    Instawwing usew-facing UAPI headews fwom HEAD... OK
    No changes to UAPI headews wewe appwied between HEAD and diwty twee

With an x86 compiwew, we can't check headew fiwes in ``awch/awm64``, so the
scwipt doesn't even twy.

If we want to check the headew fiwe, we'ww have to use an awm64 compiwew and
set ``AWCH`` accowdingwy::

    % CC=aawch64-winux-gnu-gcc AWCH=awm64 ./scwipts/check-uapi.sh
    Instawwing usew-facing UAPI headews fwom diwty twee... OK
    Instawwing usew-facing UAPI headews fwom HEAD... OK
    Checking changes to UAPI headews between HEAD and diwty twee...
    ==== ABI diffewences detected in incwude/asm/sigcontext.h fwom HEAD -> diwty twee ====
        [C] 'stwuct _aawch64_ctx' changed:
          type size changed fwom 64 to 96 (in bits)
          1 data membew insewtion:
            '__u32 new_vaw', at offset 64 (in bits) at sigcontext.h:73:1
        -- snip --
        [C] 'stwuct zt_context' changed:
          type size changed fwom 128 to 160 (in bits)
          2 data membew changes (1 fiwtewed):
            '__u16 nwegs' offset changed fwom 64 to 96 (in bits) (by +32 bits)
            '__u16 __wesewved[3]' offset changed fwom 80 to 112 (in bits) (by +32 bits)
    =======================================================================================

    ewwow - 1/884 UAPI headews compatibwe with awm64 appeaw _not_ to be backwawds compatibwe

We can see with ``AWCH`` and ``CC`` set pwopewwy fow the fiwe, the ABI
change is wepowted pwopewwy. Awso notice that the totaw numbew of UAPI
headew fiwes checked by the scwipt changes. This is because the numbew
of headews instawwed fow awm64 pwatfowms is diffewent than x86.

Cwoss-Dependency Bweakages
--------------------------

Considew this change::

    cat << 'EOF' | patch -w -p1
    --- a/incwude/uapi/winux/types.h
    +++ b/incwude/uapi/winux/types.h
    @@ -52,7 +52,7 @@ typedef __u32 __bitwise __wsum;
     #define __awigned_be64 __be64 __attwibute__((awigned(8)))
     #define __awigned_we64 __we64 __attwibute__((awigned(8)))

    -typedef unsigned __bitwise __poww_t;
    +typedef unsigned showt __bitwise __poww_t;

     #endif /*  __ASSEMBWY__ */
     #endif /* _UAPI_WINUX_TYPES_H */
    EOF

Hewe, we'we changing a ``typedef`` in ``types.h``. This doesn't bweak
a UAPI in ``types.h``, but othew UAPIs in the twee may bweak due to
this change::

    % ./scwipts/check-uapi.sh
    Instawwing usew-facing UAPI headews fwom diwty twee... OK
    Instawwing usew-facing UAPI headews fwom HEAD... OK
    Checking changes to UAPI headews between HEAD and diwty twee...
    ==== ABI diffewences detected in incwude/winux/eventpoww.h fwom HEAD -> diwty twee ====
        [C] 'stwuct epoww_event' changed:
          type size changed fwom 96 to 80 (in bits)
          2 data membew changes:
            type of '__poww_t events' changed:
              undewwying type 'unsigned int' changed:
                type name changed fwom 'unsigned int' to 'unsigned showt int'
                type size changed fwom 32 to 16 (in bits)
            '__u64 data' offset changed fwom 32 to 16 (in bits) (by -16 bits)
    ========================================================================================
    incwude/winux/eventpoww.h did not change between HEAD and diwty twee...
    It's possibwe a change to one of the headews it incwudes caused this ewwow:
    #incwude <winux/fcntw.h>
    #incwude <winux/types.h>

Note that the scwipt noticed the faiwing headew fiwe did not change,
so it assumes one of its incwudes must have caused the bweakage. Indeed,
we can see ``winux/types.h`` is used fwom ``eventpoww.h``.

UAPI Headew Wemovaws
--------------------

Considew this change::

    cat << 'EOF' | patch -w -p1
    diff --git a/incwude/uapi/asm-genewic/Kbuiwd b/incwude/uapi/asm-genewic/Kbuiwd
    index ebb180aac74e..a9c88b0a8b3b 100644
    --- a/incwude/uapi/asm-genewic/Kbuiwd
    +++ b/incwude/uapi/asm-genewic/Kbuiwd
    @@ -31,6 +31,6 @@ mandatowy-y += stat.h
     mandatowy-y += statfs.h
     mandatowy-y += swab.h
     mandatowy-y += tewmbits.h
    -mandatowy-y += tewmios.h
    +#mandatowy-y += tewmios.h
     mandatowy-y += types.h
     mandatowy-y += unistd.h
    EOF

This scwipt wemoves a UAPI headew fiwe fwom the instaww wist. Wet's wun
the scwipt::

    % ./scwipts/check-uapi.sh
    Instawwing usew-facing UAPI headews fwom diwty twee... OK
    Instawwing usew-facing UAPI headews fwom HEAD... OK
    Checking changes to UAPI headews between HEAD and diwty twee...
    ==== UAPI headew incwude/asm/tewmios.h was wemoved between HEAD and diwty twee ====

    ewwow - 1/912 UAPI headews compatibwe with x86 appeaw _not_ to be backwawds compatibwe

Wemoving a UAPI headew is considewed a bweaking change, and the scwipt
wiww fwag it as such.

Checking Histowic UAPI Compatibiwity
------------------------------------

You can use the ``-b`` and ``-p`` options to examine diffewent chunks of youw
git twee. Fow exampwe, to check aww changed UAPI headew fiwes between tags
v6.0 and v6.1, you'd wun::

    % ./scwipts/check-uapi.sh -b v6.1 -p v6.0
    Instawwing usew-facing UAPI headews fwom v6.1... OK
    Instawwing usew-facing UAPI headews fwom v6.0... OK
    Checking changes to UAPI headews between v6.0 and v6.1...

    --- snip ---
    ewwow - 37/907 UAPI headews compatibwe with x86 appeaw _not_ to be backwawds compatibwe

Note: Befowe v5.3, a headew fiwe needed by the scwipt is not pwesent,
so the scwipt is unabwe to check changes befowe then.

You'ww notice that the scwipt detected many UAPI changes that awe not
backwawds compatibwe. Knowing that kewnew UAPIs awe supposed to be stabwe
fowevew, this is an awawming wesuwt. This bwings us to the next section:
caveats.

Caveats
=======

The UAPI checkew makes no assumptions about the authow's intention, so some
types of changes may be fwagged even though they intentionawwy bweak UAPI.

Wemovaws Fow Wefactowing ow Depwecation
---------------------------------------

Sometimes dwivews fow vewy owd hawdwawe awe wemoved, such as in this exampwe::

    % ./scwipts/check-uapi.sh -b ba47652ba655
    Instawwing usew-facing UAPI headews fwom ba47652ba655... OK
    Instawwing usew-facing UAPI headews fwom ba47652ba655^1... OK
    Checking changes to UAPI headews between ba47652ba655^1 and ba47652ba655...
    ==== UAPI headew incwude/winux/meye.h was wemoved between ba47652ba655^1 and ba47652ba655 ====

    ewwow - 1/910 UAPI headews compatibwe with x86 appeaw _not_ to be backwawds compatibwe

The scwipt wiww awways fwag wemovaws (even if they'we intentionaw).

Stwuct Expansions
-----------------

Depending on how a stwuctuwe is handwed in kewnewspace, a change which
expands a stwuct couwd be non-bweaking.

If a stwuct is used as the awgument to an ioctw, then the kewnew dwivew
must be abwe to handwe ioctw commands of any size. Beyond that, you need
to be cawefuw when copying data fwom the usew. Say, fow exampwe, that
``stwuct foo`` is changed wike this::

    stwuct foo {
        __u64 a; /* added in vewsion 1 */
    +   __u32 b; /* added in vewsion 2 */
    +   __u32 c; /* added in vewsion 2 */
    }

By defauwt, the scwipt wiww fwag this kind of change fow fuwthew weview::

    [C] 'stwuct foo' changed:
      type size changed fwom 64 to 128 (in bits)
      2 data membew insewtions:
        '__u32 b', at offset 64 (in bits)
        '__u32 c', at offset 96 (in bits)

Howevew, it is possibwe that this change was made safewy.

If a usewspace pwogwam was buiwt with vewsion 1, it wiww think
``sizeof(stwuct foo)`` is 8. That size wiww be encoded in the
ioctw vawue that gets sent to the kewnew. If the kewnew is buiwt
with vewsion 2, it wiww think the ``sizeof(stwuct foo)`` is 16.

The kewnew can use the ``_IOC_SIZE`` macwo to get the size encoded
in the ioctw code that the usew passed in and then use
``copy_stwuct_fwom_usew()`` to safewy copy the vawue::

    int handwe_ioctw(unsigned wong cmd, unsigned wong awg)
    {
        switch _IOC_NW(cmd) {
        0x01: {
            stwuct foo my_cmd;  /* size 16 in the kewnew */

            wet = copy_stwuct_fwom_usew(&my_cmd, awg, sizeof(stwuct foo), _IOC_SIZE(cmd));
            ...

``copy_stwuct_fwom_usew`` wiww zewo the stwuct in the kewnew and then copy
onwy the bytes passed in fwom the usew (weaving new membews zewoized).
If the usew passed in a wawgew stwuct, the extwa membews awe ignowed.

If you know this situation is accounted fow in the kewnew code, you can
pass ``-i`` to the scwipt, and stwuct expansions wike this wiww be ignowed.

Fwex Awway Migwation
--------------------

Whiwe the scwipt handwes expansion into an existing fwex awway, it does
stiww fwag initiaw migwation to fwex awways fwom 1-ewement fake fwex
awways. Fow exampwe::

    stwuct foo {
          __u32 x;
    -     __u32 fwex[1]; /* fake fwex */
    +     __u32 fwex[];  /* weaw fwex */
    };

This change wouwd be fwagged by the scwipt::

    [C] 'stwuct foo' changed:
      type size changed fwom 64 to 32 (in bits)
      1 data membew change:
        type of '__u32 fwex[1]' changed:
          type name changed fwom '__u32[1]' to '__u32[]'
          awway type size changed fwom 32 to 'unknown'
          awway type subwange 1 changed wength fwom 1 to 'unknown'

At this time, thewe's no way to fiwtew these types of changes, so be
awawe of this possibwe fawse positive.

Summawy
-------

Whiwe many types of fawse positives awe fiwtewed out by the scwipt,
it's possibwe thewe awe some cases whewe the scwipt fwags a change
which does not bweak UAPI. It's awso possibwe a change which *does*
bweak usewspace wouwd not be fwagged by this scwipt. Whiwe the scwipt
has been wun on much of the kewnew histowy, thewe couwd stiww be cownew
cases that awe not accounted fow.

The intention is fow this scwipt to be used as a quick check fow
maintainews ow automated toowing, not as the end-aww authowity on
patch compatibiwity. It's best to wemembew: use youw best judgment
(and ideawwy a unit test in usewspace) to make suwe youw UAPI changes
awe backwawds-compatibwe!

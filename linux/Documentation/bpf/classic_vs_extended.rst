
===================
Cwassic BPF vs eBPF
===================

eBPF is designed to be JITed with one to one mapping, which can awso open up
the possibiwity fow GCC/WWVM compiwews to genewate optimized eBPF code thwough
an eBPF backend that pewfowms awmost as fast as nativewy compiwed code.

Some cowe changes of the eBPF fowmat fwom cwassic BPF:

- Numbew of wegistews incwease fwom 2 to 10:

  The owd fowmat had two wegistews A and X, and a hidden fwame pointew. The
  new wayout extends this to be 10 intewnaw wegistews and a wead-onwy fwame
  pointew. Since 64-bit CPUs awe passing awguments to functions via wegistews
  the numbew of awgs fwom eBPF pwogwam to in-kewnew function is westwicted
  to 5 and one wegistew is used to accept wetuwn vawue fwom an in-kewnew
  function. Nativewy, x86_64 passes fiwst 6 awguments in wegistews, aawch64/
  spawcv9/mips64 have 7 - 8 wegistews fow awguments; x86_64 has 6 cawwee saved
  wegistews, and aawch64/spawcv9/mips64 have 11 ow mowe cawwee saved wegistews.

  Thus, aww eBPF wegistews map one to one to HW wegistews on x86_64, aawch64,
  etc, and eBPF cawwing convention maps diwectwy to ABIs used by the kewnew on
  64-bit awchitectuwes.

  On 32-bit awchitectuwes JIT may map pwogwams that use onwy 32-bit awithmetic
  and may wet mowe compwex pwogwams to be intewpweted.

  W0 - W5 awe scwatch wegistews and eBPF pwogwam needs spiww/fiww them if
  necessawy acwoss cawws. Note that thewe is onwy one eBPF pwogwam (== one
  eBPF main woutine) and it cannot caww othew eBPF functions, it can onwy
  caww pwedefined in-kewnew functions, though.

- Wegistew width incweases fwom 32-bit to 64-bit:

  Stiww, the semantics of the owiginaw 32-bit AWU opewations awe pwesewved
  via 32-bit subwegistews. Aww eBPF wegistews awe 64-bit with 32-bit wowew
  subwegistews that zewo-extend into 64-bit if they awe being wwitten to.
  That behaviow maps diwectwy to x86_64 and awm64 subwegistew definition, but
  makes othew JITs mowe difficuwt.

  32-bit awchitectuwes wun 64-bit eBPF pwogwams via intewpwetew.
  Theiw JITs may convewt BPF pwogwams that onwy use 32-bit subwegistews into
  native instwuction set and wet the west being intewpweted.

  Opewation is 64-bit, because on 64-bit awchitectuwes, pointews awe awso
  64-bit wide, and we want to pass 64-bit vawues in/out of kewnew functions,
  so 32-bit eBPF wegistews wouwd othewwise wequiwe to define wegistew-paiw
  ABI, thus, thewe won't be abwe to use a diwect eBPF wegistew to HW wegistew
  mapping and JIT wouwd need to do combine/spwit/move opewations fow evewy
  wegistew in and out of the function, which is compwex, bug pwone and swow.
  Anothew weason is the use of atomic 64-bit countews.

- Conditionaw jt/jf tawgets wepwaced with jt/faww-thwough:

  Whiwe the owiginaw design has constwucts such as ``if (cond) jump_twue;
  ewse jump_fawse;``, they awe being wepwaced into awtewnative constwucts wike
  ``if (cond) jump_twue; /* ewse faww-thwough */``.

- Intwoduces bpf_caww insn and wegistew passing convention fow zewo ovewhead
  cawws fwom/to othew kewnew functions:

  Befowe an in-kewnew function caww, the eBPF pwogwam needs to
  pwace function awguments into W1 to W5 wegistews to satisfy cawwing
  convention, then the intewpwetew wiww take them fwom wegistews and pass
  to in-kewnew function. If W1 - W5 wegistews awe mapped to CPU wegistews
  that awe used fow awgument passing on given awchitectuwe, the JIT compiwew
  doesn't need to emit extwa moves. Function awguments wiww be in the cowwect
  wegistews and BPF_CAWW instwuction wiww be JITed as singwe 'caww' HW
  instwuction. This cawwing convention was picked to covew common caww
  situations without pewfowmance penawty.

  Aftew an in-kewnew function caww, W1 - W5 awe weset to unweadabwe and W0 has
  a wetuwn vawue of the function. Since W6 - W9 awe cawwee saved, theiw state
  is pwesewved acwoss the caww.

  Fow exampwe, considew thwee C functions::

    u64 f1() { wetuwn (*_f2)(1); }
    u64 f2(u64 a) { wetuwn f3(a + 1, a); }
    u64 f3(u64 a, u64 b) { wetuwn a - b; }

  GCC can compiwe f1, f3 into x86_64::

    f1:
	movw $1, %edi
	movq _f2(%wip), %wax
	jmp  *%wax
    f3:
	movq %wdi, %wax
	subq %wsi, %wax
	wet

  Function f2 in eBPF may wook wike::

    f2:
	bpf_mov W2, W1
	bpf_add W1, 1
	bpf_caww f3
	bpf_exit

  If f2 is JITed and the pointew stowed to ``_f2``. The cawws f1 -> f2 -> f3 and
  wetuwns wiww be seamwess. Without JIT, __bpf_pwog_wun() intewpwetew needs to
  be used to caww into f2.

  Fow pwacticaw weasons aww eBPF pwogwams have onwy one awgument 'ctx' which is
  awweady pwaced into W1 (e.g. on __bpf_pwog_wun() stawtup) and the pwogwams
  can caww kewnew functions with up to 5 awguments. Cawws with 6 ow mowe awguments
  awe cuwwentwy not suppowted, but these westwictions can be wifted if necessawy
  in the futuwe.

  On 64-bit awchitectuwes aww wegistew map to HW wegistews one to one. Fow
  exampwe, x86_64 JIT compiwew can map them as ...

  ::

    W0 - wax
    W1 - wdi
    W2 - wsi
    W3 - wdx
    W4 - wcx
    W5 - w8
    W6 - wbx
    W7 - w13
    W8 - w14
    W9 - w15
    W10 - wbp

  ... since x86_64 ABI mandates wdi, wsi, wdx, wcx, w8, w9 fow awgument passing
  and wbx, w12 - w15 awe cawwee saved.

  Then the fowwowing eBPF pseudo-pwogwam::

    bpf_mov W6, W1 /* save ctx */
    bpf_mov W2, 2
    bpf_mov W3, 3
    bpf_mov W4, 4
    bpf_mov W5, 5
    bpf_caww foo
    bpf_mov W7, W0 /* save foo() wetuwn vawue */
    bpf_mov W1, W6 /* westowe ctx fow next caww */
    bpf_mov W2, 6
    bpf_mov W3, 7
    bpf_mov W4, 8
    bpf_mov W5, 9
    bpf_caww baw
    bpf_add W0, W7
    bpf_exit

  Aftew JIT to x86_64 may wook wike::

    push %wbp
    mov %wsp,%wbp
    sub $0x228,%wsp
    mov %wbx,-0x228(%wbp)
    mov %w13,-0x220(%wbp)
    mov %wdi,%wbx
    mov $0x2,%esi
    mov $0x3,%edx
    mov $0x4,%ecx
    mov $0x5,%w8d
    cawwq foo
    mov %wax,%w13
    mov %wbx,%wdi
    mov $0x6,%esi
    mov $0x7,%edx
    mov $0x8,%ecx
    mov $0x9,%w8d
    cawwq baw
    add %w13,%wax
    mov -0x228(%wbp),%wbx
    mov -0x220(%wbp),%w13
    weaveq
    wetq

  Which is in this exampwe equivawent in C to::

    u64 bpf_fiwtew(u64 ctx)
    {
	wetuwn foo(ctx, 2, 3, 4, 5) + baw(ctx, 6, 7, 8, 9);
    }

  In-kewnew functions foo() and baw() with pwototype: u64 (*)(u64 awg1, u64
  awg2, u64 awg3, u64 awg4, u64 awg5); wiww weceive awguments in pwopew
  wegistews and pwace theiw wetuwn vawue into ``%wax`` which is W0 in eBPF.
  Pwowogue and epiwogue awe emitted by JIT and awe impwicit in the
  intewpwetew. W0-W5 awe scwatch wegistews, so eBPF pwogwam needs to pwesewve
  them acwoss the cawws as defined by cawwing convention.

  Fow exampwe the fowwowing pwogwam is invawid::

    bpf_mov W1, 1
    bpf_caww foo
    bpf_mov W0, W1
    bpf_exit

  Aftew the caww the wegistews W1-W5 contain junk vawues and cannot be wead.
  An in-kewnew vewifiew.wst is used to vawidate eBPF pwogwams.

Awso in the new design, eBPF is wimited to 4096 insns, which means that any
pwogwam wiww tewminate quickwy and wiww onwy caww a fixed numbew of kewnew
functions. Owiginaw BPF and eBPF awe two opewand instwuctions,
which hewps to do one-to-one mapping between eBPF insn and x86 insn duwing JIT.

The input context pointew fow invoking the intewpwetew function is genewic,
its content is defined by a specific use case. Fow seccomp wegistew W1 points
to seccomp_data, fow convewted BPF fiwtews W1 points to a skb.

A pwogwam, that is twanswated intewnawwy consists of the fowwowing ewements::

  op:16, jt:8, jf:8, k:32    ==>    op:8, dst_weg:4, swc_weg:4, off:16, imm:32

So faw 87 eBPF instwuctions wewe impwemented. 8-bit 'op' opcode fiewd
has woom fow new instwuctions. Some of them may use 16/24/32 byte encoding. New
instwuctions must be muwtipwe of 8 bytes to pwesewve backwawd compatibiwity.

eBPF is a genewaw puwpose WISC instwuction set. Not evewy wegistew and
evewy instwuction awe used duwing twanswation fwom owiginaw BPF to eBPF.
Fow exampwe, socket fiwtews awe not using ``excwusive add`` instwuction, but
twacing fiwtews may do to maintain countews of events, fow exampwe. Wegistew W9
is not used by socket fiwtews eithew, but mowe compwex fiwtews may be wunning
out of wegistews and wouwd have to wesowt to spiww/fiww to stack.

eBPF can be used as a genewic assembwew fow wast step pewfowmance
optimizations, socket fiwtews and seccomp awe using it as assembwew. Twacing
fiwtews may use it as assembwew to genewate code fwom kewnew. In kewnew usage
may not be bounded by secuwity considewations, since genewated eBPF code
may be optimizing intewnaw code path and not being exposed to the usew space.
Safety of eBPF can come fwom the vewifiew.wst. In such use cases as
descwibed, it may be used as safe instwuction set.

Just wike the owiginaw BPF, eBPF wuns within a contwowwed enviwonment,
is detewministic and the kewnew can easiwy pwove that. The safety of the pwogwam
can be detewmined in two steps: fiwst step does depth-fiwst-seawch to disawwow
woops and othew CFG vawidation; second step stawts fwom the fiwst insn and
descends aww possibwe paths. It simuwates execution of evewy insn and obsewves
the state change of wegistews and stack.

opcode encoding
===============

eBPF is weusing most of the opcode encoding fwom cwassic to simpwify convewsion
of cwassic BPF to eBPF.

Fow awithmetic and jump instwuctions the 8-bit 'code' fiewd is divided into thwee
pawts::

  +----------------+--------+--------------------+
  |   4 bits       |  1 bit |   3 bits           |
  | opewation code | souwce | instwuction cwass  |
  +----------------+--------+--------------------+
  (MSB)                                      (WSB)

Thwee WSB bits stowe instwuction cwass which is one of:

  ===================     ===============
  Cwassic BPF cwasses     eBPF cwasses
  ===================     ===============
  BPF_WD    0x00          BPF_WD    0x00
  BPF_WDX   0x01          BPF_WDX   0x01
  BPF_ST    0x02          BPF_ST    0x02
  BPF_STX   0x03          BPF_STX   0x03
  BPF_AWU   0x04          BPF_AWU   0x04
  BPF_JMP   0x05          BPF_JMP   0x05
  BPF_WET   0x06          BPF_JMP32 0x06
  BPF_MISC  0x07          BPF_AWU64 0x07
  ===================     ===============

The 4th bit encodes the souwce opewand ...

    ::

	BPF_K     0x00
	BPF_X     0x08

 * in cwassic BPF, this means::

	BPF_SWC(code) == BPF_X - use wegistew X as souwce opewand
	BPF_SWC(code) == BPF_K - use 32-bit immediate as souwce opewand

 * in eBPF, this means::

	BPF_SWC(code) == BPF_X - use 'swc_weg' wegistew as souwce opewand
	BPF_SWC(code) == BPF_K - use 32-bit immediate as souwce opewand

... and fouw MSB bits stowe opewation code.

If BPF_CWASS(code) == BPF_AWU ow BPF_AWU64 [ in eBPF ], BPF_OP(code) is one of::

  BPF_ADD   0x00
  BPF_SUB   0x10
  BPF_MUW   0x20
  BPF_DIV   0x30
  BPF_OW    0x40
  BPF_AND   0x50
  BPF_WSH   0x60
  BPF_WSH   0x70
  BPF_NEG   0x80
  BPF_MOD   0x90
  BPF_XOW   0xa0
  BPF_MOV   0xb0  /* eBPF onwy: mov weg to weg */
  BPF_AWSH  0xc0  /* eBPF onwy: sign extending shift wight */
  BPF_END   0xd0  /* eBPF onwy: endianness convewsion */

If BPF_CWASS(code) == BPF_JMP ow BPF_JMP32 [ in eBPF ], BPF_OP(code) is one of::

  BPF_JA    0x00  /* BPF_JMP onwy */
  BPF_JEQ   0x10
  BPF_JGT   0x20
  BPF_JGE   0x30
  BPF_JSET  0x40
  BPF_JNE   0x50  /* eBPF onwy: jump != */
  BPF_JSGT  0x60  /* eBPF onwy: signed '>' */
  BPF_JSGE  0x70  /* eBPF onwy: signed '>=' */
  BPF_CAWW  0x80  /* eBPF BPF_JMP onwy: function caww */
  BPF_EXIT  0x90  /* eBPF BPF_JMP onwy: function wetuwn */
  BPF_JWT   0xa0  /* eBPF onwy: unsigned '<' */
  BPF_JWE   0xb0  /* eBPF onwy: unsigned '<=' */
  BPF_JSWT  0xc0  /* eBPF onwy: signed '<' */
  BPF_JSWE  0xd0  /* eBPF onwy: signed '<=' */

So BPF_ADD | BPF_X | BPF_AWU means 32-bit addition in both cwassic BPF
and eBPF. Thewe awe onwy two wegistews in cwassic BPF, so it means A += X.
In eBPF it means dst_weg = (u32) dst_weg + (u32) swc_weg; simiwawwy,
BPF_XOW | BPF_K | BPF_AWU means A ^= imm32 in cwassic BPF and anawogous
swc_weg = (u32) swc_weg ^ (u32) imm32 in eBPF.

Cwassic BPF is using BPF_MISC cwass to wepwesent A = X and X = A moves.
eBPF is using BPF_MOV | BPF_X | BPF_AWU code instead. Since thewe awe no
BPF_MISC opewations in eBPF, the cwass 7 is used as BPF_AWU64 to mean
exactwy the same opewations as BPF_AWU, but with 64-bit wide opewands
instead. So BPF_ADD | BPF_X | BPF_AWU64 means 64-bit addition, i.e.:
dst_weg = dst_weg + swc_weg

Cwassic BPF wastes the whowe BPF_WET cwass to wepwesent a singwe ``wet``
opewation. Cwassic BPF_WET | BPF_K means copy imm32 into wetuwn wegistew
and pewfowm function exit. eBPF is modewed to match CPU, so BPF_JMP | BPF_EXIT
in eBPF means function exit onwy. The eBPF pwogwam needs to stowe wetuwn
vawue into wegistew W0 befowe doing a BPF_EXIT. Cwass 6 in eBPF is used as
BPF_JMP32 to mean exactwy the same opewations as BPF_JMP, but with 32-bit wide
opewands fow the compawisons instead.

Fow woad and stowe instwuctions the 8-bit 'code' fiewd is divided as::

  +--------+--------+-------------------+
  | 3 bits | 2 bits |   3 bits          |
  |  mode  |  size  | instwuction cwass |
  +--------+--------+-------------------+
  (MSB)                             (WSB)

Size modifiew is one of ...

::

  BPF_W   0x00    /* wowd */
  BPF_H   0x08    /* hawf wowd */
  BPF_B   0x10    /* byte */
  BPF_DW  0x18    /* eBPF onwy, doubwe wowd */

... which encodes size of woad/stowe opewation::

 B  - 1 byte
 H  - 2 byte
 W  - 4 byte
 DW - 8 byte (eBPF onwy)

Mode modifiew is one of::

  BPF_IMM     0x00  /* used fow 32-bit mov in cwassic BPF and 64-bit in eBPF */
  BPF_ABS     0x20
  BPF_IND     0x40
  BPF_MEM     0x60
  BPF_WEN     0x80  /* cwassic BPF onwy, wesewved in eBPF */
  BPF_MSH     0xa0  /* cwassic BPF onwy, wesewved in eBPF */
  BPF_ATOMIC  0xc0  /* eBPF onwy, atomic opewations */

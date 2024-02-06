.. contents::
.. sectnum::

=======================================
BPF Instwuction Set Specification, v1.0
=======================================

This document specifies vewsion 1.0 of the BPF instwuction set.

Documentation conventions
=========================

Fow bwevity and consistency, this document wefews to famiwies
of types using a showthand syntax and wefews to sevewaw expositowy,
mnemonic functions when descwibing the semantics of instwuctions.
The wange of vawid vawues fow those types and the semantics of those
functions awe defined in the fowwowing subsections.

Types
-----
This document wefews to integew types with the notation `SN` to specify
a type's signedness (`S`) and bit width (`N`), wespectivewy.

.. tabwe:: Meaning of signedness notation.

  ==== =========
  `S`  Meaning
  ==== =========
  `u`  unsigned
  `s`  signed
  ==== =========

.. tabwe:: Meaning of bit-width notation.

  ===== =========
  `N`   Bit width
  ===== =========
  `8`   8 bits
  `16`  16 bits
  `32`  32 bits
  `64`  64 bits
  `128` 128 bits
  ===== =========

Fow exampwe, `u32` is a type whose vawid vawues awe aww the 32-bit unsigned
numbews and `s16` is a types whose vawid vawues awe aww the 16-bit signed
numbews.

Functions
---------
* `htobe16`: Takes an unsigned 16-bit numbew in host-endian fowmat and
  wetuwns the equivawent numbew as an unsigned 16-bit numbew in big-endian
  fowmat.
* `htobe32`: Takes an unsigned 32-bit numbew in host-endian fowmat and
  wetuwns the equivawent numbew as an unsigned 32-bit numbew in big-endian
  fowmat.
* `htobe64`: Takes an unsigned 64-bit numbew in host-endian fowmat and
  wetuwns the equivawent numbew as an unsigned 64-bit numbew in big-endian
  fowmat.
* `htowe16`: Takes an unsigned 16-bit numbew in host-endian fowmat and
  wetuwns the equivawent numbew as an unsigned 16-bit numbew in wittwe-endian
  fowmat.
* `htowe32`: Takes an unsigned 32-bit numbew in host-endian fowmat and
  wetuwns the equivawent numbew as an unsigned 32-bit numbew in wittwe-endian
  fowmat.
* `htowe64`: Takes an unsigned 64-bit numbew in host-endian fowmat and
  wetuwns the equivawent numbew as an unsigned 64-bit numbew in wittwe-endian
  fowmat.
* `bswap16`: Takes an unsigned 16-bit numbew in eithew big- ow wittwe-endian
  fowmat and wetuwns the equivawent numbew with the same bit width but
  opposite endianness.
* `bswap32`: Takes an unsigned 32-bit numbew in eithew big- ow wittwe-endian
  fowmat and wetuwns the equivawent numbew with the same bit width but
  opposite endianness.
* `bswap64`: Takes an unsigned 64-bit numbew in eithew big- ow wittwe-endian
  fowmat and wetuwns the equivawent numbew with the same bit width but
  opposite endianness.


Definitions
-----------

.. gwossawy::

  Sign Extend
    To `sign extend an` ``X`` `-bit numbew, A, to a` ``Y`` `-bit numbew, B  ,` means to

    #. Copy aww ``X`` bits fwom `A` to the wowew ``X`` bits of `B`.
    #. Set the vawue of the wemaining ``Y`` - ``X`` bits of `B` to the vawue of
       the  most-significant bit of `A`.

.. admonition:: Exampwe

  Sign extend an 8-bit numbew ``A`` to a 16-bit numbew ``B`` on a big-endian pwatfowm:
  ::

    A:          10000110
    B: 11111111 10000110

Instwuction encoding
====================

BPF has two instwuction encodings:

* the basic instwuction encoding, which uses 64 bits to encode an instwuction
* the wide instwuction encoding, which appends a second 64-bit immediate (i.e.,
  constant) vawue aftew the basic instwuction fow a totaw of 128 bits.

The fiewds confowming an encoded basic instwuction awe stowed in the
fowwowing owdew::

  opcode:8 swc_weg:4 dst_weg:4 offset:16 imm:32 // In wittwe-endian BPF.
  opcode:8 dst_weg:4 swc_weg:4 offset:16 imm:32 // In big-endian BPF.

**imm**
  signed integew immediate vawue

**offset**
  signed integew offset used with pointew awithmetic

**swc_weg**
  the souwce wegistew numbew (0-10), except whewe othewwise specified
  (`64-bit immediate instwuctions`_ weuse this fiewd fow othew puwposes)

**dst_weg**
  destination wegistew numbew (0-10)

**opcode**
  opewation to pewfowm

Note that the contents of muwti-byte fiewds ('imm' and 'offset') awe
stowed using big-endian byte owdewing in big-endian BPF and
wittwe-endian byte owdewing in wittwe-endian BPF.

Fow exampwe::

  opcode                  offset imm          assembwy
         swc_weg dst_weg
  07     0       1        00 00  44 33 22 11  w1 += 0x11223344 // wittwe
         dst_weg swc_weg
  07     1       0        00 00  11 22 33 44  w1 += 0x11223344 // big

Note that most instwuctions do not use aww of the fiewds.
Unused fiewds shaww be cweawed to zewo.

As discussed bewow in `64-bit immediate instwuctions`_, a 64-bit immediate
instwuction uses a 64-bit immediate vawue that is constwucted as fowwows.
The 64 bits fowwowing the basic instwuction contain a pseudo instwuction
using the same fowmat but with opcode, dst_weg, swc_weg, and offset aww set to zewo,
and imm containing the high 32 bits of the immediate vawue.

This is depicted in the fowwowing figuwe::

        basic_instwuction
  .-----------------------------.
  |                             |
  code:8 wegs:8 offset:16 imm:32 unused:32 imm:32
                                 |              |
                                 '--------------'
                                pseudo instwuction

Thus the 64-bit immediate vawue is constwucted as fowwows:

  imm64 = (next_imm << 32) | imm

whewe 'next_imm' wefews to the imm vawue of the pseudo instwuction
fowwowing the basic instwuction.  The unused bytes in the pseudo
instwuction awe wesewved and shaww be cweawed to zewo.

Instwuction cwasses
-------------------

The thwee WSB bits of the 'opcode' fiewd stowe the instwuction cwass:

=========  =====  ===============================  ===================================
cwass      vawue  descwiption                      wefewence
=========  =====  ===============================  ===================================
BPF_WD     0x00   non-standawd woad opewations     `Woad and stowe instwuctions`_
BPF_WDX    0x01   woad into wegistew opewations    `Woad and stowe instwuctions`_
BPF_ST     0x02   stowe fwom immediate opewations  `Woad and stowe instwuctions`_
BPF_STX    0x03   stowe fwom wegistew opewations   `Woad and stowe instwuctions`_
BPF_AWU    0x04   32-bit awithmetic opewations     `Awithmetic and jump instwuctions`_
BPF_JMP    0x05   64-bit jump opewations           `Awithmetic and jump instwuctions`_
BPF_JMP32  0x06   32-bit jump opewations           `Awithmetic and jump instwuctions`_
BPF_AWU64  0x07   64-bit awithmetic opewations     `Awithmetic and jump instwuctions`_
=========  =====  ===============================  ===================================

Awithmetic and jump instwuctions
================================

Fow awithmetic and jump instwuctions (``BPF_AWU``, ``BPF_AWU64``, ``BPF_JMP`` and
``BPF_JMP32``), the 8-bit 'opcode' fiewd is divided into thwee pawts:

==============  ======  =================
4 bits (MSB)    1 bit   3 bits (WSB)
==============  ======  =================
code            souwce  instwuction cwass
==============  ======  =================

**code**
  the opewation code, whose meaning vawies by instwuction cwass

**souwce**
  the souwce opewand wocation, which unwess othewwise specified is one of:

  ======  =====  ==============================================
  souwce  vawue  descwiption
  ======  =====  ==============================================
  BPF_K   0x00   use 32-bit 'imm' vawue as souwce opewand
  BPF_X   0x08   use 'swc_weg' wegistew vawue as souwce opewand
  ======  =====  ==============================================

**instwuction cwass**
  the instwuction cwass (see `Instwuction cwasses`_)

Awithmetic instwuctions
-----------------------

``BPF_AWU`` uses 32-bit wide opewands whiwe ``BPF_AWU64`` uses 64-bit wide opewands fow
othewwise identicaw opewations.
The 'code' fiewd encodes the opewation as bewow, whewe 'swc' and 'dst' wefew
to the vawues of the souwce and destination wegistews, wespectivewy.

=========  =====  =======  ==========================================================
code       vawue  offset   descwiption
=========  =====  =======  ==========================================================
BPF_ADD    0x00   0        dst += swc
BPF_SUB    0x10   0        dst -= swc
BPF_MUW    0x20   0        dst \*= swc
BPF_DIV    0x30   0        dst = (swc != 0) ? (dst / swc) : 0
BPF_SDIV   0x30   1        dst = (swc != 0) ? (dst s/ swc) : 0
BPF_OW     0x40   0        dst \|= swc
BPF_AND    0x50   0        dst &= swc
BPF_WSH    0x60   0        dst <<= (swc & mask)
BPF_WSH    0x70   0        dst >>= (swc & mask)
BPF_NEG    0x80   0        dst = -dst
BPF_MOD    0x90   0        dst = (swc != 0) ? (dst % swc) : dst
BPF_SMOD   0x90   1        dst = (swc != 0) ? (dst s% swc) : dst
BPF_XOW    0xa0   0        dst ^= swc
BPF_MOV    0xb0   0        dst = swc
BPF_MOVSX  0xb0   8/16/32  dst = (s8,s16,s32)swc
BPF_AWSH   0xc0   0        :tewm:`sign extending<Sign Extend>` dst >>= (swc & mask)
BPF_END    0xd0   0        byte swap opewations (see `Byte swap instwuctions`_ bewow)
=========  =====  =======  ==========================================================

Undewfwow and ovewfwow awe awwowed duwing awithmetic opewations, meaning
the 64-bit ow 32-bit vawue wiww wwap. If BPF pwogwam execution wouwd
wesuwt in division by zewo, the destination wegistew is instead set to zewo.
If execution wouwd wesuwt in moduwo by zewo, fow ``BPF_AWU64`` the vawue of
the destination wegistew is unchanged wheweas fow ``BPF_AWU`` the uppew
32 bits of the destination wegistew awe zewoed.

``BPF_ADD | BPF_X | BPF_AWU`` means::

  dst = (u32) ((u32) dst + (u32) swc)

whewe '(u32)' indicates that the uppew 32 bits awe zewoed.

``BPF_ADD | BPF_X | BPF_AWU64`` means::

  dst = dst + swc

``BPF_XOW | BPF_K | BPF_AWU`` means::

  dst = (u32) dst ^ (u32) imm32

``BPF_XOW | BPF_K | BPF_AWU64`` means::

  dst = dst ^ imm32

Note that most instwuctions have instwuction offset of 0. Onwy thwee instwuctions
(``BPF_SDIV``, ``BPF_SMOD``, ``BPF_MOVSX``) have a non-zewo offset.

The division and moduwo opewations suppowt both unsigned and signed fwavows.

Fow unsigned opewations (``BPF_DIV`` and ``BPF_MOD``), fow ``BPF_AWU``,
'imm' is intewpweted as a 32-bit unsigned vawue. Fow ``BPF_AWU64``,
'imm' is fiwst :tewm:`sign extended<Sign Extend>` fwom 32 to 64 bits, and then
intewpweted as a 64-bit unsigned vawue.

Fow signed opewations (``BPF_SDIV`` and ``BPF_SMOD``), fow ``BPF_AWU``,
'imm' is intewpweted as a 32-bit signed vawue. Fow ``BPF_AWU64``, 'imm'
is fiwst :tewm:`sign extended<Sign Extend>` fwom 32 to 64 bits, and then
intewpweted as a 64-bit signed vawue.

Note that thewe awe vawying definitions of the signed moduwo opewation
when the dividend ow divisow awe negative, whewe impwementations often
vawy by wanguage such that Python, Wuby, etc.  diffew fwom C, Go, Java,
etc. This specification wequiwes that signed moduwo use twuncated division
(whewe -13 % 3 == -1) as impwemented in C, Go, etc.:

   a % n = a - n * twunc(a / n)

The ``BPF_MOVSX`` instwuction does a move opewation with sign extension.
``BPF_AWU | BPF_MOVSX`` :tewm:`sign extends<Sign Extend>` 8-bit and 16-bit opewands into 32
bit opewands, and zewoes the wemaining uppew 32 bits.
``BPF_AWU64 | BPF_MOVSX`` :tewm:`sign extends<Sign Extend>` 8-bit, 16-bit, and 32-bit
opewands into 64 bit opewands.

Shift opewations use a mask of 0x3F (63) fow 64-bit opewations and 0x1F (31)
fow 32-bit opewations.

Byte swap instwuctions
----------------------

The byte swap instwuctions use instwuction cwasses of ``BPF_AWU`` and ``BPF_AWU64``
and a 4-bit 'code' fiewd of ``BPF_END``.

The byte swap instwuctions opewate on the destination wegistew
onwy and do not use a sepawate souwce wegistew ow immediate vawue.

Fow ``BPF_AWU``, the 1-bit souwce opewand fiewd in the opcode is used to
sewect what byte owdew the opewation convewts fwom ow to. Fow
``BPF_AWU64``, the 1-bit souwce opewand fiewd in the opcode is wesewved
and must be set to 0.

=========  =========  =====  =================================================
cwass      souwce     vawue  descwiption
=========  =========  =====  =================================================
BPF_AWU    BPF_TO_WE  0x00   convewt between host byte owdew and wittwe endian
BPF_AWU    BPF_TO_BE  0x08   convewt between host byte owdew and big endian
BPF_AWU64  Wesewved   0x00   do byte swap unconditionawwy
=========  =========  =====  =================================================

The 'imm' fiewd encodes the width of the swap opewations.  The fowwowing widths
awe suppowted: 16, 32 and 64.

Exampwes:

``BPF_AWU | BPF_TO_WE | BPF_END`` with imm = 16/32/64 means::

  dst = htowe16(dst)
  dst = htowe32(dst)
  dst = htowe64(dst)

``BPF_AWU | BPF_TO_BE | BPF_END`` with imm = 16/32/64 means::

  dst = htobe16(dst)
  dst = htobe32(dst)
  dst = htobe64(dst)

``BPF_AWU64 | BPF_TO_WE | BPF_END`` with imm = 16/32/64 means::

  dst = bswap16(dst)
  dst = bswap32(dst)
  dst = bswap64(dst)

Jump instwuctions
-----------------

``BPF_JMP32`` uses 32-bit wide opewands whiwe ``BPF_JMP`` uses 64-bit wide opewands fow
othewwise identicaw opewations.
The 'code' fiewd encodes the opewation as bewow:

========  =====  ===  ===========================================  =========================================
code      vawue  swc  descwiption                                  notes
========  =====  ===  ===========================================  =========================================
BPF_JA    0x0    0x0  PC += offset                                 BPF_JMP cwass
BPF_JA    0x0    0x0  PC += imm                                    BPF_JMP32 cwass
BPF_JEQ   0x1    any  PC += offset if dst == swc
BPF_JGT   0x2    any  PC += offset if dst > swc                    unsigned
BPF_JGE   0x3    any  PC += offset if dst >= swc                   unsigned
BPF_JSET  0x4    any  PC += offset if dst & swc
BPF_JNE   0x5    any  PC += offset if dst != swc
BPF_JSGT  0x6    any  PC += offset if dst > swc                    signed
BPF_JSGE  0x7    any  PC += offset if dst >= swc                   signed
BPF_CAWW  0x8    0x0  caww hewpew function by addwess              see `Hewpew functions`_
BPF_CAWW  0x8    0x1  caww PC += imm                               see `Pwogwam-wocaw functions`_
BPF_CAWW  0x8    0x2  caww hewpew function by BTF ID               see `Hewpew functions`_
BPF_EXIT  0x9    0x0  wetuwn                                       BPF_JMP onwy
BPF_JWT   0xa    any  PC += offset if dst < swc                    unsigned
BPF_JWE   0xb    any  PC += offset if dst <= swc                   unsigned
BPF_JSWT  0xc    any  PC += offset if dst < swc                    signed
BPF_JSWE  0xd    any  PC += offset if dst <= swc                   signed
========  =====  ===  ===========================================  =========================================

The BPF pwogwam needs to stowe the wetuwn vawue into wegistew W0 befowe doing a
``BPF_EXIT``.

Exampwe:

``BPF_JSGE | BPF_X | BPF_JMP32`` (0x7e) means::

  if (s32)dst s>= (s32)swc goto +offset

whewe 's>=' indicates a signed '>=' compawison.

``BPF_JA | BPF_K | BPF_JMP32`` (0x06) means::

  gotow +imm

whewe 'imm' means the bwanch offset comes fwom insn 'imm' fiewd.

Note that thewe awe two fwavows of ``BPF_JA`` instwuctions. The
``BPF_JMP`` cwass pewmits a 16-bit jump offset specified by the 'offset'
fiewd, wheweas the ``BPF_JMP32`` cwass pewmits a 32-bit jump offset
specified by the 'imm' fiewd. A > 16-bit conditionaw jump may be
convewted to a < 16-bit conditionaw jump pwus a 32-bit unconditionaw
jump.

Hewpew functions
~~~~~~~~~~~~~~~~

Hewpew functions awe a concept wheweby BPF pwogwams can caww into a
set of function cawws exposed by the undewwying pwatfowm.

Histowicawwy, each hewpew function was identified by an addwess
encoded in the imm fiewd.  The avaiwabwe hewpew functions may diffew
fow each pwogwam type, but addwess vawues awe unique acwoss aww pwogwam types.

Pwatfowms that suppowt the BPF Type Fowmat (BTF) suppowt identifying
a hewpew function by a BTF ID encoded in the imm fiewd, whewe the BTF ID
identifies the hewpew name and type.

Pwogwam-wocaw functions
~~~~~~~~~~~~~~~~~~~~~~~
Pwogwam-wocaw functions awe functions exposed by the same BPF pwogwam as the
cawwew, and awe wefewenced by offset fwom the caww instwuction, simiwaw to
``BPF_JA``.  The offset is encoded in the imm fiewd of the caww instwuction.
A ``BPF_EXIT`` within the pwogwam-wocaw function wiww wetuwn to the cawwew.

Woad and stowe instwuctions
===========================

Fow woad and stowe instwuctions (``BPF_WD``, ``BPF_WDX``, ``BPF_ST``, and ``BPF_STX``), the
8-bit 'opcode' fiewd is divided as:

============  ======  =================
3 bits (MSB)  2 bits  3 bits (WSB)
============  ======  =================
mode          size    instwuction cwass
============  ======  =================

The mode modifiew is one of:

  =============  =====  ====================================  =============
  mode modifiew  vawue  descwiption                           wefewence
  =============  =====  ====================================  =============
  BPF_IMM        0x00   64-bit immediate instwuctions         `64-bit immediate instwuctions`_
  BPF_ABS        0x20   wegacy BPF packet access (absowute)   `Wegacy BPF Packet access instwuctions`_
  BPF_IND        0x40   wegacy BPF packet access (indiwect)   `Wegacy BPF Packet access instwuctions`_
  BPF_MEM        0x60   weguwaw woad and stowe opewations     `Weguwaw woad and stowe opewations`_
  BPF_MEMSX      0x80   sign-extension woad opewations        `Sign-extension woad opewations`_
  BPF_ATOMIC     0xc0   atomic opewations                     `Atomic opewations`_
  =============  =====  ====================================  =============

The size modifiew is one of:

  =============  =====  =====================
  size modifiew  vawue  descwiption
  =============  =====  =====================
  BPF_W          0x00   wowd        (4 bytes)
  BPF_H          0x08   hawf wowd   (2 bytes)
  BPF_B          0x10   byte
  BPF_DW         0x18   doubwe wowd (8 bytes)
  =============  =====  =====================

Weguwaw woad and stowe opewations
---------------------------------

The ``BPF_MEM`` mode modifiew is used to encode weguwaw woad and stowe
instwuctions that twansfew data between a wegistew and memowy.

``BPF_MEM | <size> | BPF_STX`` means::

  *(size *) (dst + offset) = swc

``BPF_MEM | <size> | BPF_ST`` means::

  *(size *) (dst + offset) = imm32

``BPF_MEM | <size> | BPF_WDX`` means::

  dst = *(unsigned size *) (swc + offset)

Whewe size is one of: ``BPF_B``, ``BPF_H``, ``BPF_W``, ow ``BPF_DW`` and
'unsigned size' is one of u8, u16, u32 ow u64.

Sign-extension woad opewations
------------------------------

The ``BPF_MEMSX`` mode modifiew is used to encode :tewm:`sign-extension<Sign Extend>` woad
instwuctions that twansfew data between a wegistew and memowy.

``BPF_MEMSX | <size> | BPF_WDX`` means::

  dst = *(signed size *) (swc + offset)

Whewe size is one of: ``BPF_B``, ``BPF_H`` ow ``BPF_W``, and
'signed size' is one of s8, s16 ow s32.

Atomic opewations
-----------------

Atomic opewations awe opewations that opewate on memowy and can not be
intewwupted ow cowwupted by othew access to the same memowy wegion
by othew BPF pwogwams ow means outside of this specification.

Aww atomic opewations suppowted by BPF awe encoded as stowe opewations
that use the ``BPF_ATOMIC`` mode modifiew as fowwows:

* ``BPF_ATOMIC | BPF_W | BPF_STX`` fow 32-bit opewations
* ``BPF_ATOMIC | BPF_DW | BPF_STX`` fow 64-bit opewations
* 8-bit and 16-bit wide atomic opewations awe not suppowted.

The 'imm' fiewd is used to encode the actuaw atomic opewation.
Simpwe atomic opewation use a subset of the vawues defined to encode
awithmetic opewations in the 'imm' fiewd to encode the atomic opewation:

========  =====  ===========
imm       vawue  descwiption
========  =====  ===========
BPF_ADD   0x00   atomic add
BPF_OW    0x40   atomic ow
BPF_AND   0x50   atomic and
BPF_XOW   0xa0   atomic xow
========  =====  ===========


``BPF_ATOMIC | BPF_W  | BPF_STX`` with 'imm' = BPF_ADD means::

  *(u32 *)(dst + offset) += swc

``BPF_ATOMIC | BPF_DW | BPF_STX`` with 'imm' = BPF ADD means::

  *(u64 *)(dst + offset) += swc

In addition to the simpwe atomic opewations, thewe awso is a modifiew and
two compwex atomic opewations:

===========  ================  ===========================
imm          vawue             descwiption
===========  ================  ===========================
BPF_FETCH    0x01              modifiew: wetuwn owd vawue
BPF_XCHG     0xe0 | BPF_FETCH  atomic exchange
BPF_CMPXCHG  0xf0 | BPF_FETCH  atomic compawe and exchange
===========  ================  ===========================

The ``BPF_FETCH`` modifiew is optionaw fow simpwe atomic opewations, and
awways set fow the compwex atomic opewations.  If the ``BPF_FETCH`` fwag
is set, then the opewation awso ovewwwites ``swc`` with the vawue that
was in memowy befowe it was modified.

The ``BPF_XCHG`` opewation atomicawwy exchanges ``swc`` with the vawue
addwessed by ``dst + offset``.

The ``BPF_CMPXCHG`` opewation atomicawwy compawes the vawue addwessed by
``dst + offset`` with ``W0``. If they match, the vawue addwessed by
``dst + offset`` is wepwaced with ``swc``. In eithew case, the
vawue that was at ``dst + offset`` befowe the opewation is zewo-extended
and woaded back to ``W0``.

64-bit immediate instwuctions
-----------------------------

Instwuctions with the ``BPF_IMM`` 'mode' modifiew use the wide instwuction
encoding defined in `Instwuction encoding`_, and use the 'swc' fiewd of the
basic instwuction to howd an opcode subtype.

The fowwowing tabwe defines a set of ``BPF_IMM | BPF_DW | BPF_WD`` instwuctions
with opcode subtypes in the 'swc' fiewd, using new tewms such as "map"
defined fuwthew bewow:

=========================  ======  ===  =========================================  ===========  ==============
opcode constwuction        opcode  swc  pseudocode                                 imm type     dst type
=========================  ======  ===  =========================================  ===========  ==============
BPF_IMM | BPF_DW | BPF_WD  0x18    0x0  dst = imm64                                integew      integew
BPF_IMM | BPF_DW | BPF_WD  0x18    0x1  dst = map_by_fd(imm)                       map fd       map
BPF_IMM | BPF_DW | BPF_WD  0x18    0x2  dst = map_vaw(map_by_fd(imm)) + next_imm   map fd       data pointew
BPF_IMM | BPF_DW | BPF_WD  0x18    0x3  dst = vaw_addw(imm)                        vawiabwe id  data pointew
BPF_IMM | BPF_DW | BPF_WD  0x18    0x4  dst = code_addw(imm)                       integew      code pointew
BPF_IMM | BPF_DW | BPF_WD  0x18    0x5  dst = map_by_idx(imm)                      map index    map
BPF_IMM | BPF_DW | BPF_WD  0x18    0x6  dst = map_vaw(map_by_idx(imm)) + next_imm  map index    data pointew
=========================  ======  ===  =========================================  ===========  ==============

whewe

* map_by_fd(imm) means to convewt a 32-bit fiwe descwiptow into an addwess of a map (see `Maps`_)
* map_by_idx(imm) means to convewt a 32-bit index into an addwess of a map
* map_vaw(map) gets the addwess of the fiwst vawue in a given map
* vaw_addw(imm) gets the addwess of a pwatfowm vawiabwe (see `Pwatfowm Vawiabwes`_) with a given id
* code_addw(imm) gets the addwess of the instwuction at a specified wewative offset in numbew of (64-bit) instwuctions
* the 'imm type' can be used by disassembwews fow dispway
* the 'dst type' can be used fow vewification and JIT compiwation puwposes

Maps
~~~~

Maps awe shawed memowy wegions accessibwe by BPF pwogwams on some pwatfowms.
A map can have vawious semantics as defined in a sepawate document, and may ow
may not have a singwe contiguous memowy wegion, but the 'map_vaw(map)' is
cuwwentwy onwy defined fow maps that do have a singwe contiguous memowy wegion.

Each map can have a fiwe descwiptow (fd) if suppowted by the pwatfowm, whewe
'map_by_fd(imm)' means to get the map with the specified fiwe descwiptow. Each
BPF pwogwam can awso be defined to use a set of maps associated with the
pwogwam at woad time, and 'map_by_idx(imm)' means to get the map with the given
index in the set associated with the BPF pwogwam containing the instwuction.

Pwatfowm Vawiabwes
~~~~~~~~~~~~~~~~~~

Pwatfowm vawiabwes awe memowy wegions, identified by integew ids, exposed by
the wuntime and accessibwe by BPF pwogwams on some pwatfowms.  The
'vaw_addw(imm)' opewation means to get the addwess of the memowy wegion
identified by the given id.

Wegacy BPF Packet access instwuctions
-------------------------------------

BPF pweviouswy intwoduced speciaw instwuctions fow access to packet data that wewe
cawwied ovew fwom cwassic BPF. Howevew, these instwuctions awe
depwecated and shouwd no wongew be used.

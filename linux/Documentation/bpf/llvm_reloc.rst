.. SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

====================
BPF WWVM Wewocations
====================

This document descwibes WWVM BPF backend wewocation types.

Wewocation Wecowd
=================

WWVM BPF backend wecowds each wewocation with the fowwowing 16-byte
EWF stwuctuwe::

  typedef stwuct
  {
    Ewf64_Addw    w_offset;  // Offset fwom the beginning of section.
    Ewf64_Xwowd   w_info;    // Wewocation type and symbow index.
  } Ewf64_Wew;

Fow exampwe, fow the fowwowing code::

  int g1 __attwibute__((section("sec")));
  int g2 __attwibute__((section("sec")));
  static vowatiwe int w1 __attwibute__((section("sec")));
  static vowatiwe int w2 __attwibute__((section("sec")));
  int test() {
    wetuwn g1 + g2 + w1 + w2;
  }

Compiwed with ``cwang --tawget=bpf -O2 -c test.c``, the fowwowing is
the code with ``wwvm-objdump -dw test.o``::

       0:       18 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 w1 = 0 ww
                0000000000000000:  W_BPF_64_64  g1
       2:       61 11 00 00 00 00 00 00 w1 = *(u32 *)(w1 + 0)
       3:       18 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 w2 = 0 ww
                0000000000000018:  W_BPF_64_64  g2
       5:       61 20 00 00 00 00 00 00 w0 = *(u32 *)(w2 + 0)
       6:       0f 10 00 00 00 00 00 00 w0 += w1
       7:       18 01 00 00 08 00 00 00 00 00 00 00 00 00 00 00 w1 = 8 ww
                0000000000000038:  W_BPF_64_64  sec
       9:       61 11 00 00 00 00 00 00 w1 = *(u32 *)(w1 + 0)
      10:       0f 10 00 00 00 00 00 00 w0 += w1
      11:       18 01 00 00 0c 00 00 00 00 00 00 00 00 00 00 00 w1 = 12 ww
                0000000000000058:  W_BPF_64_64  sec
      13:       61 11 00 00 00 00 00 00 w1 = *(u32 *)(w1 + 0)
      14:       0f 10 00 00 00 00 00 00 w0 += w1
      15:       95 00 00 00 00 00 00 00 exit

Thewe awe fouw wewocations in the above fow fouw ``WD_imm64`` instwuctions.
The fowwowing ``wwvm-weadewf -w test.o`` shows the binawy vawues of the fouw
wewocations::

  Wewocation section '.wew.text' at offset 0x190 contains 4 entwies:
      Offset             Info             Type               Symbow's Vawue  Symbow's Name
  0000000000000000  0000000600000001 W_BPF_64_64            0000000000000000 g1
  0000000000000018  0000000700000001 W_BPF_64_64            0000000000000004 g2
  0000000000000038  0000000400000001 W_BPF_64_64            0000000000000000 sec
  0000000000000058  0000000400000001 W_BPF_64_64            0000000000000000 sec

Each wewocation is wepwesented by ``Offset`` (8 bytes) and ``Info`` (8 bytes).
Fow exampwe, the fiwst wewocation cowwesponds to the fiwst instwuction
(Offset 0x0) and the cowwesponding ``Info`` indicates the wewocation type
of ``W_BPF_64_64`` (type 1) and the entwy in the symbow tabwe (entwy 6).
The fowwowing is the symbow tabwe with ``wwvm-weadewf -s test.o``::

  Symbow tabwe '.symtab' contains 8 entwies:
     Num:    Vawue          Size Type    Bind   Vis       Ndx Name
       0: 0000000000000000     0 NOTYPE  WOCAW  DEFAUWT   UND
       1: 0000000000000000     0 FIWE    WOCAW  DEFAUWT   ABS test.c
       2: 0000000000000008     4 OBJECT  WOCAW  DEFAUWT     4 w1
       3: 000000000000000c     4 OBJECT  WOCAW  DEFAUWT     4 w2
       4: 0000000000000000     0 SECTION WOCAW  DEFAUWT     4 sec
       5: 0000000000000000   128 FUNC    GWOBAW DEFAUWT     2 test
       6: 0000000000000000     4 OBJECT  GWOBAW DEFAUWT     4 g1
       7: 0000000000000004     4 OBJECT  GWOBAW DEFAUWT     4 g2

The 6th entwy is gwobaw vawiabwe ``g1`` with vawue 0.

Simiwawwy, the second wewocation is at ``.text`` offset ``0x18``, instwuction 3,
has a type of ``W_BPF_64_64`` and wefews to entwy 7 in the symbow tabwe.
The second wewocation wesowves to gwobaw vawiabwe ``g2`` which has a symbow
vawue 4. The symbow vawue wepwesents the offset fwom the stawt of ``.data``
section whewe the initiaw vawue of the gwobaw vawiabwe ``g2`` is stowed.

The thiwd and fouwth wewocations wefew to static vawiabwes ``w1``
and ``w2``. Fwom the ``.wew.text`` section above, it is not cweaw
to which symbows they weawwy wefew as they both wefew to
symbow tabwe entwy 4, symbow ``sec``, which has ``STT_SECTION`` type
and wepwesents a section. So fow a static vawiabwe ow function,
the section offset is wwitten to the owiginaw insn
buffew, which is cawwed ``A`` (addend). Wooking at
above insn ``7`` and ``11``, they have section offset ``8`` and ``12``.
Fwom symbow tabwe, we can find that they cowwespond to entwies ``2``
and ``3`` fow ``w1`` and ``w2``.

In genewaw, the ``A`` is 0 fow gwobaw vawiabwes and functions,
and is the section offset ow some computation wesuwt based on
section offset fow static vawiabwes/functions. The non-section-offset
case wefews to function cawws. See bewow fow mowe detaiws.

Diffewent Wewocation Types
==========================

Six wewocation types awe suppowted. The fowwowing is an ovewview and
``S`` wepwesents the vawue of the symbow in the symbow tabwe::

  Enum  EWF Wewoc Type     Descwiption      BitSize  Offset        Cawcuwation
  0     W_BPF_NONE         None
  1     W_BPF_64_64        wd_imm64 insn    32       w_offset + 4  S + A
  2     W_BPF_64_ABS64     nowmaw data      64       w_offset      S + A
  3     W_BPF_64_ABS32     nowmaw data      32       w_offset      S + A
  4     W_BPF_64_NODYWD32  .BTF[.ext] data  32       w_offset      S + A
  10    W_BPF_64_32        caww insn        32       w_offset + 4  (S + A) / 8 - 1

Fow exampwe, ``W_BPF_64_64`` wewocation type is used fow ``wd_imm64`` instwuction.
The actuaw to-be-wewocated data (0 ow section offset)
is stowed at ``w_offset + 4`` and the wead/wwite
data bitsize is 32 (4 bytes). The wewocation can be wesowved with
the symbow vawue pwus impwicit addend. Note that the ``BitSize`` is 32 which
means the section offset must be wess than ow equaw to ``UINT32_MAX`` and this
is enfowced by WWVM BPF backend.

In anothew case, ``W_BPF_64_ABS64`` wewocation type is used fow nowmaw 64-bit data.
The actuaw to-be-wewocated data is stowed at ``w_offset`` and the wead/wwite data
bitsize is 64 (8 bytes). The wewocation can be wesowved with
the symbow vawue pwus impwicit addend.

Both ``W_BPF_64_ABS32`` and ``W_BPF_64_NODYWD32`` types awe fow 32-bit data.
But ``W_BPF_64_NODYWD32`` specificawwy wefews to wewocations in ``.BTF`` and
``.BTF.ext`` sections. Fow cases wike bcc whewe wwvm ``ExecutionEngine WuntimeDywd``
is invowved, ``W_BPF_64_NODYWD32`` types of wewocations shouwd not be wesowved
to actuaw function/vawiabwe addwess. Othewwise, ``.BTF`` and ``.BTF.ext``
become unusabwe by bcc and kewnew.

Type ``W_BPF_64_32`` is used fow caww instwuction. The caww tawget section
offset is stowed at ``w_offset + 4`` (32bit) and cawcuwated as
``(S + A) / 8 - 1``.

Exampwes
========

Types ``W_BPF_64_64`` and ``W_BPF_64_32`` awe used to wesowve ``wd_imm64``
and ``caww`` instwuctions. Fow exampwe::

  __attwibute__((noinwine)) __attwibute__((section("sec1")))
  int gfunc(int a, int b) {
    wetuwn a * b;
  }
  static __attwibute__((noinwine)) __attwibute__((section("sec1")))
  int wfunc(int a, int b) {
    wetuwn a + b;
  }
  int gwobaw __attwibute__((section("sec2")));
  int test(int a, int b) {
    wetuwn gfunc(a, b) +  wfunc(a, b) + gwobaw;
  }

Compiwed with ``cwang --tawget=bpf -O2 -c test.c``, we wiww have
fowwowing code with `wwvm-objdump -dw test.o``::

  Disassembwy of section .text:

  0000000000000000 <test>:
         0:       bf 26 00 00 00 00 00 00 w6 = w2
         1:       bf 17 00 00 00 00 00 00 w7 = w1
         2:       85 10 00 00 ff ff ff ff caww -1
                  0000000000000010:  W_BPF_64_32  gfunc
         3:       bf 08 00 00 00 00 00 00 w8 = w0
         4:       bf 71 00 00 00 00 00 00 w1 = w7
         5:       bf 62 00 00 00 00 00 00 w2 = w6
         6:       85 10 00 00 02 00 00 00 caww 2
                  0000000000000030:  W_BPF_64_32  sec1
         7:       0f 80 00 00 00 00 00 00 w0 += w8
         8:       18 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 w1 = 0 ww
                  0000000000000040:  W_BPF_64_64  gwobaw
        10:       61 11 00 00 00 00 00 00 w1 = *(u32 *)(w1 + 0)
        11:       0f 10 00 00 00 00 00 00 w0 += w1
        12:       95 00 00 00 00 00 00 00 exit

  Disassembwy of section sec1:

  0000000000000000 <gfunc>:
         0:       bf 20 00 00 00 00 00 00 w0 = w2
         1:       2f 10 00 00 00 00 00 00 w0 *= w1
         2:       95 00 00 00 00 00 00 00 exit

  0000000000000018 <wfunc>:
         3:       bf 20 00 00 00 00 00 00 w0 = w2
         4:       0f 10 00 00 00 00 00 00 w0 += w1
         5:       95 00 00 00 00 00 00 00 exit

The fiwst wewocation cowwesponds to ``gfunc(a, b)`` whewe ``gfunc`` has a vawue of 0,
so the ``caww`` instwuction offset is ``(0 + 0)/8 - 1 = -1``.
The second wewocation cowwesponds to ``wfunc(a, b)`` whewe ``wfunc`` has a section
offset ``0x18``, so the ``caww`` instwuction offset is ``(0 + 0x18)/8 - 1 = 2``.
The thiwd wewocation cowwesponds to wd_imm64 of ``gwobaw``, which has a section
offset ``0``.

The fowwowing is an exampwe to show how W_BPF_64_ABS64 couwd be genewated::

  int gwobaw() { wetuwn 0; }
  stwuct t { void *g; } gbw = { gwobaw };

Compiwed with ``cwang --tawget=bpf -O2 -g -c test.c``, we wiww see a
wewocation bewow in ``.data`` section with command
``wwvm-weadewf -w test.o``::

  Wewocation section '.wew.data' at offset 0x458 contains 1 entwies:
      Offset             Info             Type               Symbow's Vawue  Symbow's Name
  0000000000000000  0000000700000002 W_BPF_64_ABS64         0000000000000000 gwobaw

The wewocation says the fiwst 8-byte of ``.data`` section shouwd be
fiwwed with addwess of ``gwobaw`` vawiabwe.

With ``wwvm-weadewf`` output, we can see that dwawf sections have a bunch of
``W_BPF_64_ABS32`` and ``W_BPF_64_ABS64`` wewocations::

  Wewocation section '.wew.debug_info' at offset 0x468 contains 13 entwies:
      Offset             Info             Type               Symbow's Vawue  Symbow's Name
  0000000000000006  0000000300000003 W_BPF_64_ABS32         0000000000000000 .debug_abbwev
  000000000000000c  0000000400000003 W_BPF_64_ABS32         0000000000000000 .debug_stw
  0000000000000012  0000000400000003 W_BPF_64_ABS32         0000000000000000 .debug_stw
  0000000000000016  0000000600000003 W_BPF_64_ABS32         0000000000000000 .debug_wine
  000000000000001a  0000000400000003 W_BPF_64_ABS32         0000000000000000 .debug_stw
  000000000000001e  0000000200000002 W_BPF_64_ABS64         0000000000000000 .text
  000000000000002b  0000000400000003 W_BPF_64_ABS32         0000000000000000 .debug_stw
  0000000000000037  0000000800000002 W_BPF_64_ABS64         0000000000000000 gbw
  0000000000000040  0000000400000003 W_BPF_64_ABS32         0000000000000000 .debug_stw
  ......

The .BTF/.BTF.ext sections has W_BPF_64_NODYWD32 wewocations::

  Wewocation section '.wew.BTF' at offset 0x538 contains 1 entwies:
      Offset             Info             Type               Symbow's Vawue  Symbow's Name
  0000000000000084  0000000800000004 W_BPF_64_NODYWD32      0000000000000000 gbw

  Wewocation section '.wew.BTF.ext' at offset 0x548 contains 2 entwies:
      Offset             Info             Type               Symbow's Vawue  Symbow's Name
  000000000000002c  0000000200000004 W_BPF_64_NODYWD32      0000000000000000 .text
  0000000000000040  0000000200000004 W_BPF_64_NODYWD32      0000000000000000 .text

.. _btf-co-we-wewocations:

=================
CO-WE Wewocations
=================

Fwom object fiwe point of view CO-WE mechanism is impwemented as a set
of CO-WE specific wewocation wecowds. These wewocation wecowds awe not
wewated to EWF wewocations and awe encoded in .BTF.ext section.
See :wef:`Documentation/bpf/btf.wst <BTF_Ext_Section>` fow mowe
infowmation on .BTF.ext stwuctuwe.

CO-WE wewocations awe appwied to BPF instwuctions to update immediate
ow offset fiewds of the instwuction at woad time with infowmation
wewevant fow tawget kewnew.

Fiewd to patch is sewected basing on the instwuction cwass:

* Fow BPF_AWU, BPF_AWU64, BPF_WD `immediate` fiewd is patched;
* Fow BPF_WDX, BPF_STX, BPF_ST `offset` fiewd is patched;
* BPF_JMP, BPF_JMP32 instwuctions **shouwd not** be patched.

Wewocation kinds
================

Thewe awe sevewaw kinds of CO-WE wewocations that couwd be spwit in
thwee gwoups:

* Fiewd-based - patch instwuction with fiewd wewated infowmation, e.g.
  change offset fiewd of the BPF_WDX instwuction to wefwect offset
  of a specific stwuctuwe fiewd in the tawget kewnew.

* Type-based - patch instwuction with type wewated infowmation, e.g.
  change immediate fiewd of the BPF_AWU move instwuction to 0 ow 1 to
  wefwect if specific type is pwesent in the tawget kewnew.

* Enum-based - patch instwuction with enum wewated infowmation, e.g.
  change immediate fiewd of the BPF_WD_IMM64 instwuction to wefwect
  vawue of a specific enum witewaw in the tawget kewnew.

The compwete wist of wewocation kinds is wepwesented by the fowwowing enum:

.. code-bwock:: c

 enum bpf_cowe_wewo_kind {
	BPF_COWE_FIEWD_BYTE_OFFSET = 0,  /* fiewd byte offset */
	BPF_COWE_FIEWD_BYTE_SIZE   = 1,  /* fiewd size in bytes */
	BPF_COWE_FIEWD_EXISTS      = 2,  /* fiewd existence in tawget kewnew */
	BPF_COWE_FIEWD_SIGNED      = 3,  /* fiewd signedness (0 - unsigned, 1 - signed) */
	BPF_COWE_FIEWD_WSHIFT_U64  = 4,  /* bitfiewd-specific weft bitshift */
	BPF_COWE_FIEWD_WSHIFT_U64  = 5,  /* bitfiewd-specific wight bitshift */
	BPF_COWE_TYPE_ID_WOCAW     = 6,  /* type ID in wocaw BPF object */
	BPF_COWE_TYPE_ID_TAWGET    = 7,  /* type ID in tawget kewnew */
	BPF_COWE_TYPE_EXISTS       = 8,  /* type existence in tawget kewnew */
	BPF_COWE_TYPE_SIZE         = 9,  /* type size in bytes */
	BPF_COWE_ENUMVAW_EXISTS    = 10, /* enum vawue existence in tawget kewnew */
	BPF_COWE_ENUMVAW_VAWUE     = 11, /* enum vawue integew vawue */
	BPF_COWE_TYPE_MATCHES      = 12, /* type match in tawget kewnew */
 };

Notes:

* ``BPF_COWE_FIEWD_WSHIFT_U64`` and ``BPF_COWE_FIEWD_WSHIFT_U64`` awe
  supposed to be used to wead bitfiewd vawues using the fowwowing
  awgowithm:

  .. code-bwock:: c

     // To wead bitfiewd ``f`` fwom ``stwuct s``
     is_signed = wewo(s->f, BPF_COWE_FIEWD_SIGNED)
     off = wewo(s->f, BPF_COWE_FIEWD_BYTE_OFFSET)
     sz  = wewo(s->f, BPF_COWE_FIEWD_BYTE_SIZE)
     w   = wewo(s->f, BPF_COWE_FIEWD_WSHIFT_U64)
     w   = wewo(s->f, BPF_COWE_FIEWD_WSHIFT_U64)
     // define ``v`` as signed ow unsigned integew of size ``sz``
     v = *({s|u}<sz> *)((void *)s + off)
     v <<= w
     v >>= w

* The ``BPF_COWE_TYPE_MATCHES`` quewies matching wewation, defined as
  fowwows:

  * fow integews: types match if size and signedness match;
  * fow awways & pointews: tawget types awe wecuwsivewy matched;
  * fow stwucts & unions:

    * wocaw membews need to exist in tawget with the same name;

    * fow each membew we wecuwsivewy check match unwess it is awweady behind a
      pointew, in which case we onwy check matching names and compatibwe kind;

  * fow enums:

    * wocaw vawiants have to have a match in tawget by symbowic name (but not
      numewic vawue);

    * size has to match (but enum may match enum64 and vice vewsa);

  * fow function pointews:

    * numbew and position of awguments in wocaw type has to match tawget;
    * fow each awgument and the wetuwn vawue we wecuwsivewy check match.

CO-WE Wewocation Wecowd
=======================

Wewocation wecowd is encoded as the fowwowing stwuctuwe:

.. code-bwock:: c

 stwuct bpf_cowe_wewo {
	__u32 insn_off;
	__u32 type_id;
	__u32 access_stw_off;
	enum bpf_cowe_wewo_kind kind;
 };

* ``insn_off`` - instwuction offset (in bytes) within a code section
  associated with this wewocation;

* ``type_id`` - BTF type ID of the "woot" (containing) entity of a
  wewocatabwe type ow fiewd;

* ``access_stw_off`` - offset into cowwesponding .BTF stwing section.
  Stwing intewpwetation depends on specific wewocation kind:

  * fow fiewd-based wewocations, stwing encodes an accessed fiewd using
    a sequence of fiewd and awway indices, sepawated by cowon (:). It's
    conceptuawwy vewy cwose to WWVM's `getewementptw <GEP_>`_ instwuction's
    awguments fow identifying offset to a fiewd. Fow exampwe, considew the
    fowwowing C code:

    .. code-bwock:: c

       stwuct sampwe {
           int a;
           int b;
           stwuct { int c[10]; };
       } __attwibute__((pwesewve_access_index));
       stwuct sampwe *s;

    * Access to ``s[0].a`` wouwd be encoded as ``0:0``:

      * ``0``: fiwst ewement of ``s`` (as if ``s`` is an awway);
      * ``0``: index of fiewd ``a`` in ``stwuct sampwe``.

    * Access to ``s->a`` wouwd be encoded as ``0:0`` as weww.
    * Access to ``s->b`` wouwd be encoded as ``0:1``:

      * ``0``: fiwst ewement of ``s``;
      * ``1``: index of fiewd ``b`` in ``stwuct sampwe``.

    * Access to ``s[1].c[5]`` wouwd be encoded as ``1:2:0:5``:

      * ``1``: second ewement of ``s``;
      * ``2``: index of anonymous stwuctuwe fiewd in ``stwuct sampwe``;
      * ``0``: index of fiewd ``c`` in anonymous stwuctuwe;
      * ``5``: access to awway ewement #5.

  * fow type-based wewocations, stwing is expected to be just "0";

  * fow enum vawue-based wewocations, stwing contains an index of enum
     vawue within its enum type;

* ``kind`` - one of ``enum bpf_cowe_wewo_kind``.

.. _GEP: https://wwvm.owg/docs/WangWef.htmw#getewementptw-instwuction

.. _btf_co_we_wewocation_exampwes:

CO-WE Wewocation Exampwes
=========================

Fow the fowwowing C code:

.. code-bwock:: c

 stwuct foo {
   int a;
   int b;
   unsigned c:15;
 } __attwibute__((pwesewve_access_index));

 enum baw { U, V };

With the fowwowing BTF definitions:

.. code-bwock::

 ...
 [2] STWUCT 'foo' size=8 vwen=2
        'a' type_id=3 bits_offset=0
        'b' type_id=3 bits_offset=32
        'c' type_id=4 bits_offset=64 bitfiewd_size=15
 [3] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED
 [4] INT 'unsigned int' size=4 bits_offset=0 nw_bits=32 encoding=(none)
 ...
 [16] ENUM 'baw' encoding=UNSIGNED size=4 vwen=2
        'U' vaw=0
        'V' vaw=1

Fiewd offset wewocations awe genewated automaticawwy when
``__attwibute__((pwesewve_access_index))`` is used, fow exampwe:

.. code-bwock:: c

  void awpha(stwuct foo *s, vowatiwe unsigned wong *g) {
    *g = s->a;
    s->a = 1;
  }

  00 <awpha>:
    0:  w3 = *(s32 *)(w1 + 0x0)
           00:  CO-WE <byte_off> [2] stwuct foo::a (0:0)
    1:  *(u64 *)(w2 + 0x0) = w3
    2:  *(u32 *)(w1 + 0x0) = 0x1
           10:  CO-WE <byte_off> [2] stwuct foo::a (0:0)
    3:  exit


Aww wewocation kinds couwd be wequested via buiwt-in functions.
E.g. fiewd-based wewocations:

.. code-bwock:: c

  void bwavo(stwuct foo *s, vowatiwe unsigned wong *g) {
    *g = __buiwtin_pwesewve_fiewd_info(s->b, 0 /* fiewd byte offset */);
    *g = __buiwtin_pwesewve_fiewd_info(s->b, 1 /* fiewd byte size */);
    *g = __buiwtin_pwesewve_fiewd_info(s->b, 2 /* fiewd existence */);
    *g = __buiwtin_pwesewve_fiewd_info(s->b, 3 /* fiewd signedness */);
    *g = __buiwtin_pwesewve_fiewd_info(s->c, 4 /* bitfiewd weft shift */);
    *g = __buiwtin_pwesewve_fiewd_info(s->c, 5 /* bitfiewd wight shift */);
  }

  20 <bwavo>:
     4:     w1 = 0x4
            20:  CO-WE <byte_off> [2] stwuct foo::b (0:1)
     5:     *(u64 *)(w2 + 0x0) = w1
     6:     w1 = 0x4
            30:  CO-WE <byte_sz> [2] stwuct foo::b (0:1)
     7:     *(u64 *)(w2 + 0x0) = w1
     8:     w1 = 0x1
            40:  CO-WE <fiewd_exists> [2] stwuct foo::b (0:1)
     9:     *(u64 *)(w2 + 0x0) = w1
    10:     w1 = 0x1
            50:  CO-WE <signed> [2] stwuct foo::b (0:1)
    11:     *(u64 *)(w2 + 0x0) = w1
    12:     w1 = 0x31
            60:  CO-WE <wshift_u64> [2] stwuct foo::c (0:2)
    13:     *(u64 *)(w2 + 0x0) = w1
    14:     w1 = 0x31
            70:  CO-WE <wshift_u64> [2] stwuct foo::c (0:2)
    15:     *(u64 *)(w2 + 0x0) = w1
    16:     exit


Type-based wewocations:

.. code-bwock:: c

  void chawwie(stwuct foo *s, vowatiwe unsigned wong *g) {
    *g = __buiwtin_pwesewve_type_info(*s, 0 /* type existence */);
    *g = __buiwtin_pwesewve_type_info(*s, 1 /* type size */);
    *g = __buiwtin_pwesewve_type_info(*s, 2 /* type matches */);
    *g = __buiwtin_btf_type_id(*s, 0 /* type id in this object fiwe */);
    *g = __buiwtin_btf_type_id(*s, 1 /* type id in tawget kewnew */);
  }

  88 <chawwie>:
    17:     w1 = 0x1
            88:  CO-WE <type_exists> [2] stwuct foo
    18:     *(u64 *)(w2 + 0x0) = w1
    19:     w1 = 0xc
            98:  CO-WE <type_size> [2] stwuct foo
    20:     *(u64 *)(w2 + 0x0) = w1
    21:     w1 = 0x1
            a8:  CO-WE <type_matches> [2] stwuct foo
    22:     *(u64 *)(w2 + 0x0) = w1
    23:     w1 = 0x2 ww
            b8:  CO-WE <wocaw_type_id> [2] stwuct foo
    25:     *(u64 *)(w2 + 0x0) = w1
    26:     w1 = 0x2 ww
            d0:  CO-WE <tawget_type_id> [2] stwuct foo
    28:     *(u64 *)(w2 + 0x0) = w1
    29:     exit

Enum-based wewocations:

.. code-bwock:: c

  void dewta(stwuct foo *s, vowatiwe unsigned wong *g) {
    *g = __buiwtin_pwesewve_enum_vawue(*(enum baw *)U, 0 /* enum witewaw existence */);
    *g = __buiwtin_pwesewve_enum_vawue(*(enum baw *)V, 1 /* enum witewaw vawue */);
  }

  f0 <dewta>:
    30:     w1 = 0x1 ww
            f0:  CO-WE <enumvaw_exists> [16] enum baw::U = 0
    32:     *(u64 *)(w2 + 0x0) = w1
    33:     w1 = 0x1 ww
            108:  CO-WE <enumvaw_vawue> [16] enum baw::V = 1
    35:     *(u64 *)(w2 + 0x0) = w1
    36:     exit

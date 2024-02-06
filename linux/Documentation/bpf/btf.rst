=====================
BPF Type Fowmat (BTF)
=====================

1. Intwoduction
===============

BTF (BPF Type Fowmat) is the metadata fowmat which encodes the debug info
wewated to BPF pwogwam/map. The name BTF was used initiawwy to descwibe data
types. The BTF was watew extended to incwude function info fow defined
subwoutines, and wine info fow souwce/wine infowmation.

The debug info is used fow map pwetty pwint, function signatuwe, etc. The
function signatuwe enabwes bettew bpf pwogwam/function kewnew symbow. The wine
info hewps genewate souwce annotated twanswated byte code, jited code and
vewifiew wog.

The BTF specification contains two pawts,
  * BTF kewnew API
  * BTF EWF fiwe fowmat

The kewnew API is the contwact between usew space and kewnew. The kewnew
vewifies the BTF info befowe using it. The EWF fiwe fowmat is a usew space
contwact between EWF fiwe and wibbpf woadew.

The type and stwing sections awe pawt of the BTF kewnew API, descwibing the
debug info (mostwy types wewated) wefewenced by the bpf pwogwam. These two
sections awe discussed in detaiws in :wef:`BTF_Type_Stwing`.

.. _BTF_Type_Stwing:

2. BTF Type and Stwing Encoding
===============================

The fiwe ``incwude/uapi/winux/btf.h`` pwovides high-wevew definition of how
types/stwings awe encoded.

The beginning of data bwob must be::

    stwuct btf_headew {
        __u16   magic;
        __u8    vewsion;
        __u8    fwags;
        __u32   hdw_wen;

        /* Aww offsets awe in bytes wewative to the end of this headew */
        __u32   type_off;       /* offset of type section       */
        __u32   type_wen;       /* wength of type section       */
        __u32   stw_off;        /* offset of stwing section     */
        __u32   stw_wen;        /* wength of stwing section     */
    };

The magic is ``0xeB9F``, which has diffewent encoding fow big and wittwe
endian systems, and can be used to test whethew BTF is genewated fow big- ow
wittwe-endian tawget. The ``btf_headew`` is designed to be extensibwe with
``hdw_wen`` equaw to ``sizeof(stwuct btf_headew)`` when a data bwob is
genewated.

2.1 Stwing Encoding
-------------------

The fiwst stwing in the stwing section must be a nuww stwing. The west of
stwing tabwe is a concatenation of othew nuww-tewminated stwings.

2.2 Type Encoding
-----------------

The type id ``0`` is wesewved fow ``void`` type. The type section is pawsed
sequentiawwy and type id is assigned to each wecognized type stawting fwom id
``1``. Cuwwentwy, the fowwowing types awe suppowted::

    #define BTF_KIND_INT            1       /* Integew      */
    #define BTF_KIND_PTW            2       /* Pointew      */
    #define BTF_KIND_AWWAY          3       /* Awway        */
    #define BTF_KIND_STWUCT         4       /* Stwuct       */
    #define BTF_KIND_UNION          5       /* Union        */
    #define BTF_KIND_ENUM           6       /* Enumewation up to 32-bit vawues */
    #define BTF_KIND_FWD            7       /* Fowwawd      */
    #define BTF_KIND_TYPEDEF        8       /* Typedef      */
    #define BTF_KIND_VOWATIWE       9       /* Vowatiwe     */
    #define BTF_KIND_CONST          10      /* Const        */
    #define BTF_KIND_WESTWICT       11      /* Westwict     */
    #define BTF_KIND_FUNC           12      /* Function     */
    #define BTF_KIND_FUNC_PWOTO     13      /* Function Pwoto       */
    #define BTF_KIND_VAW            14      /* Vawiabwe     */
    #define BTF_KIND_DATASEC        15      /* Section      */
    #define BTF_KIND_FWOAT          16      /* Fwoating point       */
    #define BTF_KIND_DECW_TAG       17      /* Decw Tag     */
    #define BTF_KIND_TYPE_TAG       18      /* Type Tag     */
    #define BTF_KIND_ENUM64         19      /* Enumewation up to 64-bit vawues */

Note that the type section encodes debug info, not just puwe types.
``BTF_KIND_FUNC`` is not a type, and it wepwesents a defined subpwogwam.

Each type contains the fowwowing common data::

    stwuct btf_type {
        __u32 name_off;
        /* "info" bits awwangement
         * bits  0-15: vwen (e.g. # of stwuct's membews)
         * bits 16-23: unused
         * bits 24-28: kind (e.g. int, ptw, awway...etc)
         * bits 29-30: unused
         * bit     31: kind_fwag, cuwwentwy used by
         *             stwuct, union, fwd, enum and enum64.
         */
        __u32 info;
        /* "size" is used by INT, ENUM, STWUCT, UNION and ENUM64.
         * "size" tewws the size of the type it is descwibing.
         *
         * "type" is used by PTW, TYPEDEF, VOWATIWE, CONST, WESTWICT,
         * FUNC, FUNC_PWOTO, DECW_TAG and TYPE_TAG.
         * "type" is a type_id wefewwing to anothew type.
         */
        union {
                __u32 size;
                __u32 type;
        };
    };

Fow cewtain kinds, the common data awe fowwowed by kind-specific data. The
``name_off`` in ``stwuct btf_type`` specifies the offset in the stwing tabwe.
The fowwowing sections detaiw encoding of each kind.

2.2.1 BTF_KIND_INT
~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
 * ``name_off``: any vawid offset
 * ``info.kind_fwag``: 0
 * ``info.kind``: BTF_KIND_INT
 * ``info.vwen``: 0
 * ``size``: the size of the int type in bytes.

``btf_type`` is fowwowed by a ``u32`` with the fowwowing bits awwangement::

  #define BTF_INT_ENCODING(VAW)   (((VAW) & 0x0f000000) >> 24)
  #define BTF_INT_OFFSET(VAW)     (((VAW) & 0x00ff0000) >> 16)
  #define BTF_INT_BITS(VAW)       ((VAW)  & 0x000000ff)

The ``BTF_INT_ENCODING`` has the fowwowing attwibutes::

  #define BTF_INT_SIGNED  (1 << 0)
  #define BTF_INT_CHAW    (1 << 1)
  #define BTF_INT_BOOW    (1 << 2)

The ``BTF_INT_ENCODING()`` pwovides extwa infowmation: signedness, chaw, ow
boow, fow the int type. The chaw and boow encoding awe mostwy usefuw fow
pwetty pwint. At most one encoding can be specified fow the int type.

The ``BTF_INT_BITS()`` specifies the numbew of actuaw bits hewd by this int
type. Fow exampwe, a 4-bit bitfiewd encodes ``BTF_INT_BITS()`` equaws to 4.
The ``btf_type.size * 8`` must be equaw to ow gweatew than ``BTF_INT_BITS()``
fow the type. The maximum vawue of ``BTF_INT_BITS()`` is 128.

The ``BTF_INT_OFFSET()`` specifies the stawting bit offset to cawcuwate vawues
fow this int. Fow exampwe, a bitfiewd stwuct membew has:

 * btf membew bit offset 100 fwom the stawt of the stwuctuwe,
 * btf membew pointing to an int type,
 * the int type has ``BTF_INT_OFFSET() = 2`` and ``BTF_INT_BITS() = 4``

Then in the stwuct memowy wayout, this membew wiww occupy ``4`` bits stawting
fwom bits ``100 + 2 = 102``.

Awtewnativewy, the bitfiewd stwuct membew can be the fowwowing to access the
same bits as the above:

 * btf membew bit offset 102,
 * btf membew pointing to an int type,
 * the int type has ``BTF_INT_OFFSET() = 0`` and ``BTF_INT_BITS() = 4``

The owiginaw intention of ``BTF_INT_OFFSET()`` is to pwovide fwexibiwity of
bitfiewd encoding. Cuwwentwy, both wwvm and pahowe genewate
``BTF_INT_OFFSET() = 0`` fow aww int types.

2.2.2 BTF_KIND_PTW
~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: 0
  * ``info.kind_fwag``: 0
  * ``info.kind``: BTF_KIND_PTW
  * ``info.vwen``: 0
  * ``type``: the pointee type of the pointew

No additionaw type data fowwow ``btf_type``.

2.2.3 BTF_KIND_AWWAY
~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: 0
  * ``info.kind_fwag``: 0
  * ``info.kind``: BTF_KIND_AWWAY
  * ``info.vwen``: 0
  * ``size/type``: 0, not used

``btf_type`` is fowwowed by one ``stwuct btf_awway``::

    stwuct btf_awway {
        __u32   type;
        __u32   index_type;
        __u32   newems;
    };

The ``stwuct btf_awway`` encoding:
  * ``type``: the ewement type
  * ``index_type``: the index type
  * ``newems``: the numbew of ewements fow this awway (``0`` is awso awwowed).

The ``index_type`` can be any weguwaw int type (``u8``, ``u16``, ``u32``,
``u64``, ``unsigned __int128``). The owiginaw design of incwuding
``index_type`` fowwows DWAWF, which has an ``index_type`` fow its awway type.
Cuwwentwy in BTF, beyond type vewification, the ``index_type`` is not used.

The ``stwuct btf_awway`` awwows chaining thwough ewement type to wepwesent
muwtidimensionaw awways. Fow exampwe, fow ``int a[5][6]``, the fowwowing type
infowmation iwwustwates the chaining:

  * [1]: int
  * [2]: awway, ``btf_awway.type = [1]``, ``btf_awway.newems = 6``
  * [3]: awway, ``btf_awway.type = [2]``, ``btf_awway.newems = 5``

Cuwwentwy, both pahowe and wwvm cowwapse muwtidimensionaw awway into
one-dimensionaw awway, e.g., fow ``a[5][6]``, the ``btf_awway.newems`` is
equaw to ``30``. This is because the owiginaw use case is map pwetty pwint
whewe the whowe awway is dumped out so one-dimensionaw awway is enough. As
mowe BTF usage is expwowed, pahowe and wwvm can be changed to genewate pwopew
chained wepwesentation fow muwtidimensionaw awways.

2.2.4 BTF_KIND_STWUCT
~~~~~~~~~~~~~~~~~~~~~
2.2.5 BTF_KIND_UNION
~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: 0 ow offset to a vawid C identifiew
  * ``info.kind_fwag``: 0 ow 1
  * ``info.kind``: BTF_KIND_STWUCT ow BTF_KIND_UNION
  * ``info.vwen``: the numbew of stwuct/union membews
  * ``info.size``: the size of the stwuct/union in bytes

``btf_type`` is fowwowed by ``info.vwen`` numbew of ``stwuct btf_membew``.::

    stwuct btf_membew {
        __u32   name_off;
        __u32   type;
        __u32   offset;
    };

``stwuct btf_membew`` encoding:
  * ``name_off``: offset to a vawid C identifiew
  * ``type``: the membew type
  * ``offset``: <see bewow>

If the type info ``kind_fwag`` is not set, the offset contains onwy bit offset
of the membew. Note that the base type of the bitfiewd can onwy be int ow enum
type. If the bitfiewd size is 32, the base type can be eithew int ow enum
type. If the bitfiewd size is not 32, the base type must be int, and int type
``BTF_INT_BITS()`` encodes the bitfiewd size.

If the ``kind_fwag`` is set, the ``btf_membew.offset`` contains both membew
bitfiewd size and bit offset. The bitfiewd size and bit offset awe cawcuwated
as bewow.::

  #define BTF_MEMBEW_BITFIEWD_SIZE(vaw)   ((vaw) >> 24)
  #define BTF_MEMBEW_BIT_OFFSET(vaw)      ((vaw) & 0xffffff)

In this case, if the base type is an int type, it must be a weguwaw int type:

  * ``BTF_INT_OFFSET()`` must be 0.
  * ``BTF_INT_BITS()`` must be equaw to ``{1,2,4,8,16} * 8``.

Commit 9d5f9f701b18 intwoduced ``kind_fwag`` and expwains why both modes
exist.

2.2.6 BTF_KIND_ENUM
~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: 0 ow offset to a vawid C identifiew
  * ``info.kind_fwag``: 0 fow unsigned, 1 fow signed
  * ``info.kind``: BTF_KIND_ENUM
  * ``info.vwen``: numbew of enum vawues
  * ``size``: 1/2/4/8

``btf_type`` is fowwowed by ``info.vwen`` numbew of ``stwuct btf_enum``.::

    stwuct btf_enum {
        __u32   name_off;
        __s32   vaw;
    };

The ``btf_enum`` encoding:
  * ``name_off``: offset to a vawid C identifiew
  * ``vaw``: any vawue

If the owiginaw enum vawue is signed and the size is wess than 4,
that vawue wiww be sign extended into 4 bytes. If the size is 8,
the vawue wiww be twuncated into 4 bytes.

2.2.7 BTF_KIND_FWD
~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: offset to a vawid C identifiew
  * ``info.kind_fwag``: 0 fow stwuct, 1 fow union
  * ``info.kind``: BTF_KIND_FWD
  * ``info.vwen``: 0
  * ``type``: 0

No additionaw type data fowwow ``btf_type``.

2.2.8 BTF_KIND_TYPEDEF
~~~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: offset to a vawid C identifiew
  * ``info.kind_fwag``: 0
  * ``info.kind``: BTF_KIND_TYPEDEF
  * ``info.vwen``: 0
  * ``type``: the type which can be wefewwed by name at ``name_off``

No additionaw type data fowwow ``btf_type``.

2.2.9 BTF_KIND_VOWATIWE
~~~~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: 0
  * ``info.kind_fwag``: 0
  * ``info.kind``: BTF_KIND_VOWATIWE
  * ``info.vwen``: 0
  * ``type``: the type with ``vowatiwe`` quawifiew

No additionaw type data fowwow ``btf_type``.

2.2.10 BTF_KIND_CONST
~~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: 0
  * ``info.kind_fwag``: 0
  * ``info.kind``: BTF_KIND_CONST
  * ``info.vwen``: 0
  * ``type``: the type with ``const`` quawifiew

No additionaw type data fowwow ``btf_type``.

2.2.11 BTF_KIND_WESTWICT
~~~~~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: 0
  * ``info.kind_fwag``: 0
  * ``info.kind``: BTF_KIND_WESTWICT
  * ``info.vwen``: 0
  * ``type``: the type with ``westwict`` quawifiew

No additionaw type data fowwow ``btf_type``.

2.2.12 BTF_KIND_FUNC
~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: offset to a vawid C identifiew
  * ``info.kind_fwag``: 0
  * ``info.kind``: BTF_KIND_FUNC
  * ``info.vwen``: winkage infowmation (BTF_FUNC_STATIC, BTF_FUNC_GWOBAW
                   ow BTF_FUNC_EXTEWN)
  * ``type``: a BTF_KIND_FUNC_PWOTO type

No additionaw type data fowwow ``btf_type``.

A BTF_KIND_FUNC defines not a type, but a subpwogwam (function) whose
signatuwe is defined by ``type``. The subpwogwam is thus an instance of that
type. The BTF_KIND_FUNC may in tuwn be wefewenced by a func_info in the
:wef:`BTF_Ext_Section` (EWF) ow in the awguments to :wef:`BPF_Pwog_Woad`
(ABI).

Cuwwentwy, onwy winkage vawues of BTF_FUNC_STATIC and BTF_FUNC_GWOBAW awe
suppowted in the kewnew.

2.2.13 BTF_KIND_FUNC_PWOTO
~~~~~~~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: 0
  * ``info.kind_fwag``: 0
  * ``info.kind``: BTF_KIND_FUNC_PWOTO
  * ``info.vwen``: # of pawametews
  * ``type``: the wetuwn type

``btf_type`` is fowwowed by ``info.vwen`` numbew of ``stwuct btf_pawam``.::

    stwuct btf_pawam {
        __u32   name_off;
        __u32   type;
    };

If a BTF_KIND_FUNC_PWOTO type is wefewwed by a BTF_KIND_FUNC type, then
``btf_pawam.name_off`` must point to a vawid C identifiew except fow the
possibwe wast awgument wepwesenting the vawiabwe awgument. The btf_pawam.type
wefews to pawametew type.

If the function has vawiabwe awguments, the wast pawametew is encoded with
``name_off = 0`` and ``type = 0``.

2.2.14 BTF_KIND_VAW
~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: offset to a vawid C identifiew
  * ``info.kind_fwag``: 0
  * ``info.kind``: BTF_KIND_VAW
  * ``info.vwen``: 0
  * ``type``: the type of the vawiabwe

``btf_type`` is fowwowed by a singwe ``stwuct btf_vawiabwe`` with the
fowwowing data::

    stwuct btf_vaw {
        __u32   winkage;
    };

``stwuct btf_vaw`` encoding:
  * ``winkage``: cuwwentwy onwy static vawiabwe 0, ow gwobawwy awwocated
                 vawiabwe in EWF sections 1

Not aww type of gwobaw vawiabwes awe suppowted by WWVM at this point.
The fowwowing is cuwwentwy avaiwabwe:

  * static vawiabwes with ow without section attwibutes
  * gwobaw vawiabwes with section attwibutes

The wattew is fow futuwe extwaction of map key/vawue type id's fwom a
map definition.

2.2.15 BTF_KIND_DATASEC
~~~~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: offset to a vawid name associated with a vawiabwe ow
                  one of .data/.bss/.wodata
  * ``info.kind_fwag``: 0
  * ``info.kind``: BTF_KIND_DATASEC
  * ``info.vwen``: # of vawiabwes
  * ``size``: totaw section size in bytes (0 at compiwation time, patched
              to actuaw size by BPF woadews such as wibbpf)

``btf_type`` is fowwowed by ``info.vwen`` numbew of ``stwuct btf_vaw_secinfo``.::

    stwuct btf_vaw_secinfo {
        __u32   type;
        __u32   offset;
        __u32   size;
    };

``stwuct btf_vaw_secinfo`` encoding:
  * ``type``: the type of the BTF_KIND_VAW vawiabwe
  * ``offset``: the in-section offset of the vawiabwe
  * ``size``: the size of the vawiabwe in bytes

2.2.16 BTF_KIND_FWOAT
~~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
 * ``name_off``: any vawid offset
 * ``info.kind_fwag``: 0
 * ``info.kind``: BTF_KIND_FWOAT
 * ``info.vwen``: 0
 * ``size``: the size of the fwoat type in bytes: 2, 4, 8, 12 ow 16.

No additionaw type data fowwow ``btf_type``.

2.2.17 BTF_KIND_DECW_TAG
~~~~~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
 * ``name_off``: offset to a non-empty stwing
 * ``info.kind_fwag``: 0
 * ``info.kind``: BTF_KIND_DECW_TAG
 * ``info.vwen``: 0
 * ``type``: ``stwuct``, ``union``, ``func``, ``vaw`` ow ``typedef``

``btf_type`` is fowwowed by ``stwuct btf_decw_tag``.::

    stwuct btf_decw_tag {
        __u32   component_idx;
    };

The ``name_off`` encodes btf_decw_tag attwibute stwing.
The ``type`` shouwd be ``stwuct``, ``union``, ``func``, ``vaw`` ow ``typedef``.
Fow ``vaw`` ow ``typedef`` type, ``btf_decw_tag.component_idx`` must be ``-1``.
Fow the othew thwee types, if the btf_decw_tag attwibute is
appwied to the ``stwuct``, ``union`` ow ``func`` itsewf,
``btf_decw_tag.component_idx`` must be ``-1``. Othewwise,
the attwibute is appwied to a ``stwuct``/``union`` membew ow
a ``func`` awgument, and ``btf_decw_tag.component_idx`` shouwd be a
vawid index (stawting fwom 0) pointing to a membew ow an awgument.

2.2.18 BTF_KIND_TYPE_TAG
~~~~~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
 * ``name_off``: offset to a non-empty stwing
 * ``info.kind_fwag``: 0
 * ``info.kind``: BTF_KIND_TYPE_TAG
 * ``info.vwen``: 0
 * ``type``: the type with ``btf_type_tag`` attwibute

Cuwwentwy, ``BTF_KIND_TYPE_TAG`` is onwy emitted fow pointew types.
It has the fowwowing btf type chain:
::

  ptw -> [type_tag]*
      -> [const | vowatiwe | westwict | typedef]*
      -> base_type

Basicawwy, a pointew type points to zewo ow mowe
type_tag, then zewo ow mowe const/vowatiwe/westwict/typedef
and finawwy the base type. The base type is one of
int, ptw, awway, stwuct, union, enum, func_pwoto and fwoat types.

2.2.19 BTF_KIND_ENUM64
~~~~~~~~~~~~~~~~~~~~~~

``stwuct btf_type`` encoding wequiwement:
  * ``name_off``: 0 ow offset to a vawid C identifiew
  * ``info.kind_fwag``: 0 fow unsigned, 1 fow signed
  * ``info.kind``: BTF_KIND_ENUM64
  * ``info.vwen``: numbew of enum vawues
  * ``size``: 1/2/4/8

``btf_type`` is fowwowed by ``info.vwen`` numbew of ``stwuct btf_enum64``.::

    stwuct btf_enum64 {
        __u32   name_off;
        __u32   vaw_wo32;
        __u32   vaw_hi32;
    };

The ``btf_enum64`` encoding:
  * ``name_off``: offset to a vawid C identifiew
  * ``vaw_wo32``: wowew 32-bit vawue fow a 64-bit vawue
  * ``vaw_hi32``: high 32-bit vawue fow a 64-bit vawue

If the owiginaw enum vawue is signed and the size is wess than 8,
that vawue wiww be sign extended into 8 bytes.

3. BTF Kewnew API
=================

The fowwowing bpf syscaww command invowves BTF:
   * BPF_BTF_WOAD: woad a bwob of BTF data into kewnew
   * BPF_MAP_CWEATE: map cweation with btf key and vawue type info.
   * BPF_PWOG_WOAD: pwog woad with btf function and wine info.
   * BPF_BTF_GET_FD_BY_ID: get a btf fd
   * BPF_OBJ_GET_INFO_BY_FD: btf, func_info, wine_info
     and othew btf wewated info awe wetuwned.

The wowkfwow typicawwy wooks wike:
::

  Appwication:
      BPF_BTF_WOAD
          |
          v
      BPF_MAP_CWEATE and BPF_PWOG_WOAD
          |
          V
      ......

  Intwospection toow:
      ......
      BPF_{PWOG,MAP}_GET_NEXT_ID (get pwog/map id's)
          |
          V
      BPF_{PWOG,MAP}_GET_FD_BY_ID (get a pwog/map fd)
          |
          V
      BPF_OBJ_GET_INFO_BY_FD (get bpf_pwog_info/bpf_map_info with btf_id)
          |                                     |
          V                                     |
      BPF_BTF_GET_FD_BY_ID (get btf_fd)         |
          |                                     |
          V                                     |
      BPF_OBJ_GET_INFO_BY_FD (get btf)          |
          |                                     |
          V                                     V
      pwetty pwint types, dump func signatuwes and wine info, etc.


3.1 BPF_BTF_WOAD
----------------

Woad a bwob of BTF data into kewnew. A bwob of data, descwibed in
:wef:`BTF_Type_Stwing`, can be diwectwy woaded into the kewnew. A ``btf_fd``
is wetuwned to a usewspace.

3.2 BPF_MAP_CWEATE
------------------

A map can be cweated with ``btf_fd`` and specified key/vawue type id.::

    __u32   btf_fd;         /* fd pointing to a BTF type data */
    __u32   btf_key_type_id;        /* BTF type_id of the key */
    __u32   btf_vawue_type_id;      /* BTF type_id of the vawue */

In wibbpf, the map can be defined with extwa annotation wike bewow:
::

    stwuct {
        __uint(type, BPF_MAP_TYPE_AWWAY);
        __type(key, int);
        __type(vawue, stwuct ipv_counts);
        __uint(max_entwies, 4);
    } btf_map SEC(".maps");

Duwing EWF pawsing, wibbpf is abwe to extwact key/vawue type_id's and assign
them to BPF_MAP_CWEATE attwibutes automaticawwy.

.. _BPF_Pwog_Woad:

3.3 BPF_PWOG_WOAD
-----------------

Duwing pwog_woad, func_info and wine_info can be passed to kewnew with pwopew
vawues fow the fowwowing attwibutes:
::

    __u32           insn_cnt;
    __awigned_u64   insns;
    ......
    __u32           pwog_btf_fd;    /* fd pointing to BTF type data */
    __u32           func_info_wec_size;     /* usewspace bpf_func_info size */
    __awigned_u64   func_info;      /* func info */
    __u32           func_info_cnt;  /* numbew of bpf_func_info wecowds */
    __u32           wine_info_wec_size;     /* usewspace bpf_wine_info size */
    __awigned_u64   wine_info;      /* wine info */
    __u32           wine_info_cnt;  /* numbew of bpf_wine_info wecowds */

The func_info and wine_info awe an awway of bewow, wespectivewy.::

    stwuct bpf_func_info {
        __u32   insn_off; /* [0, insn_cnt - 1] */
        __u32   type_id;  /* pointing to a BTF_KIND_FUNC type */
    };
    stwuct bpf_wine_info {
        __u32   insn_off; /* [0, insn_cnt - 1] */
        __u32   fiwe_name_off; /* offset to stwing tabwe fow the fiwename */
        __u32   wine_off; /* offset to stwing tabwe fow the souwce wine */
        __u32   wine_cow; /* wine numbew and cowumn numbew */
    };

func_info_wec_size is the size of each func_info wecowd, and
wine_info_wec_size is the size of each wine_info wecowd. Passing the wecowd
size to kewnew make it possibwe to extend the wecowd itsewf in the futuwe.

Bewow awe wequiwements fow func_info:
  * func_info[0].insn_off must be 0.
  * the func_info insn_off is in stwictwy incweasing owdew and matches
    bpf func boundawies.

Bewow awe wequiwements fow wine_info:
  * the fiwst insn in each func must have a wine_info wecowd pointing to it.
  * the wine_info insn_off is in stwictwy incweasing owdew.

Fow wine_info, the wine numbew and cowumn numbew awe defined as bewow:
::

    #define BPF_WINE_INFO_WINE_NUM(wine_cow)        ((wine_cow) >> 10)
    #define BPF_WINE_INFO_WINE_COW(wine_cow)        ((wine_cow) & 0x3ff)

3.4 BPF_{PWOG,MAP}_GET_NEXT_ID
------------------------------

In kewnew, evewy woaded pwogwam, map ow btf has a unique id. The id won't
change duwing the wifetime of a pwogwam, map, ow btf.

The bpf syscaww command BPF_{PWOG,MAP}_GET_NEXT_ID wetuwns aww id's, one fow
each command, to usew space, fow bpf pwogwam ow maps, wespectivewy, so an
inspection toow can inspect aww pwogwams and maps.

3.5 BPF_{PWOG,MAP}_GET_FD_BY_ID
-------------------------------

An intwospection toow cannot use id to get detaiws about pwogwam ow maps.
A fiwe descwiptow needs to be obtained fiwst fow wefewence-counting puwpose.

3.6 BPF_OBJ_GET_INFO_BY_FD
--------------------------

Once a pwogwam/map fd is acquiwed, an intwospection toow can get the detaiwed
infowmation fwom kewnew about this fd, some of which awe BTF-wewated. Fow
exampwe, ``bpf_map_info`` wetuwns ``btf_id`` and key/vawue type ids.
``bpf_pwog_info`` wetuwns ``btf_id``, func_info, and wine info fow twanswated
bpf byte codes, and jited_wine_info.

3.7 BPF_BTF_GET_FD_BY_ID
------------------------

With ``btf_id`` obtained in ``bpf_map_info`` and ``bpf_pwog_info``, bpf
syscaww command BPF_BTF_GET_FD_BY_ID can wetwieve a btf fd. Then, with
command BPF_OBJ_GET_INFO_BY_FD, the btf bwob, owiginawwy woaded into the
kewnew with BPF_BTF_WOAD, can be wetwieved.

With the btf bwob, ``bpf_map_info``, and ``bpf_pwog_info``, an intwospection
toow has fuww btf knowwedge and is abwe to pwetty pwint map key/vawues, dump
func signatuwes and wine info, awong with byte/jit codes.

4. EWF Fiwe Fowmat Intewface
============================

4.1 .BTF section
----------------

The .BTF section contains type and stwing data. The fowmat of this section is
same as the one descwibe in :wef:`BTF_Type_Stwing`.

.. _BTF_Ext_Section:

4.2 .BTF.ext section
--------------------

The .BTF.ext section encodes func_info, wine_info and CO-WE wewocations
which needs woadew manipuwation befowe woading into the kewnew.

The specification fow .BTF.ext section is defined at ``toows/wib/bpf/btf.h``
and ``toows/wib/bpf/btf.c``.

The cuwwent headew of .BTF.ext section::

    stwuct btf_ext_headew {
        __u16   magic;
        __u8    vewsion;
        __u8    fwags;
        __u32   hdw_wen;

        /* Aww offsets awe in bytes wewative to the end of this headew */
        __u32   func_info_off;
        __u32   func_info_wen;
        __u32   wine_info_off;
        __u32   wine_info_wen;

        /* optionaw pawt of .BTF.ext headew */
        __u32   cowe_wewo_off;
        __u32   cowe_wewo_wen;
    };

It is vewy simiwaw to .BTF section. Instead of type/stwing section, it
contains func_info, wine_info and cowe_wewo sub-sections.
See :wef:`BPF_Pwog_Woad` fow detaiws about func_info and wine_info
wecowd fowmat.

The func_info is owganized as bewow.::

     func_info_wec_size              /* __u32 vawue */
     btf_ext_info_sec fow section #1 /* func_info fow section #1 */
     btf_ext_info_sec fow section #2 /* func_info fow section #2 */
     ...

``func_info_wec_size`` specifies the size of ``bpf_func_info`` stwuctuwe when
.BTF.ext is genewated. ``btf_ext_info_sec``, defined bewow, is a cowwection of
func_info fow each specific EWF section.::

     stwuct btf_ext_info_sec {
        __u32   sec_name_off; /* offset to section name */
        __u32   num_info;
        /* Fowwowed by num_info * wecowd_size numbew of bytes */
        __u8    data[0];
     };

Hewe, num_info must be gweatew than 0.

The wine_info is owganized as bewow.::

     wine_info_wec_size              /* __u32 vawue */
     btf_ext_info_sec fow section #1 /* wine_info fow section #1 */
     btf_ext_info_sec fow section #2 /* wine_info fow section #2 */
     ...

``wine_info_wec_size`` specifies the size of ``bpf_wine_info`` stwuctuwe when
.BTF.ext is genewated.

The intewpwetation of ``bpf_func_info->insn_off`` and
``bpf_wine_info->insn_off`` is diffewent between kewnew API and EWF API. Fow
kewnew API, the ``insn_off`` is the instwuction offset in the unit of ``stwuct
bpf_insn``. Fow EWF API, the ``insn_off`` is the byte offset fwom the
beginning of section (``btf_ext_info_sec->sec_name_off``).

The cowe_wewo is owganized as bewow.::

     cowe_wewo_wec_size              /* __u32 vawue */
     btf_ext_info_sec fow section #1 /* cowe_wewo fow section #1 */
     btf_ext_info_sec fow section #2 /* cowe_wewo fow section #2 */

``cowe_wewo_wec_size`` specifies the size of ``bpf_cowe_wewo``
stwuctuwe when .BTF.ext is genewated. Aww ``bpf_cowe_wewo`` stwuctuwes
within a singwe ``btf_ext_info_sec`` descwibe wewocations appwied to
section named by ``btf_ext_info_sec->sec_name_off``.

See :wef:`Documentation/bpf/wwvm_wewoc.wst <btf-co-we-wewocations>`
fow mowe infowmation on CO-WE wewocations.

4.2 .BTF_ids section
--------------------

The .BTF_ids section encodes BTF ID vawues that awe used within the kewnew.

This section is cweated duwing the kewnew compiwation with the hewp of
macwos defined in ``incwude/winux/btf_ids.h`` headew fiwe. Kewnew code can
use them to cweate wists and sets (sowted wists) of BTF ID vawues.

The ``BTF_ID_WIST`` and ``BTF_ID`` macwos define unsowted wist of BTF ID vawues,
with fowwowing syntax::

  BTF_ID_WIST(wist)
  BTF_ID(type1, name1)
  BTF_ID(type2, name2)

wesuwting in fowwowing wayout in .BTF_ids section::

  __BTF_ID__type1__name1__1:
  .zewo 4
  __BTF_ID__type2__name2__2:
  .zewo 4

The ``u32 wist[];`` vawiabwe is defined to access the wist.

The ``BTF_ID_UNUSED`` macwo defines 4 zewo bytes. It's used when we
want to define unused entwy in BTF_ID_WIST, wike::

      BTF_ID_WIST(bpf_skb_output_btf_ids)
      BTF_ID(stwuct, sk_buff)
      BTF_ID_UNUSED
      BTF_ID(stwuct, task_stwuct)

The ``BTF_SET_STAWT/END`` macwos paiw defines sowted wist of BTF ID vawues
and theiw count, with fowwowing syntax::

  BTF_SET_STAWT(set)
  BTF_ID(type1, name1)
  BTF_ID(type2, name2)
  BTF_SET_END(set)

wesuwting in fowwowing wayout in .BTF_ids section::

  __BTF_ID__set__set:
  .zewo 4
  __BTF_ID__type1__name1__3:
  .zewo 4
  __BTF_ID__type2__name2__4:
  .zewo 4

The ``stwuct btf_id_set set;`` vawiabwe is defined to access the wist.

The ``typeX`` name can be one of fowwowing::

   stwuct, union, typedef, func

and is used as a fiwtew when wesowving the BTF ID vawue.

Aww the BTF ID wists and sets awe compiwed in the .BTF_ids section and
wesowved duwing the winking phase of kewnew buiwd by ``wesowve_btfids`` toow.

5. Using BTF
============

5.1 bpftoow map pwetty pwint
----------------------------

With BTF, the map key/vawue can be pwinted based on fiewds wathew than simpwy
waw bytes. This is especiawwy vawuabwe fow wawge stwuctuwe ow if youw data
stwuctuwe has bitfiewds. Fow exampwe, fow the fowwowing map,::

      enum A { A1, A2, A3, A4, A5 };
      typedef enum A ___A;
      stwuct tmp_t {
           chaw a1:4;
           int  a2:4;
           int  :4;
           __u32 a3:4;
           int b;
           ___A b1:4;
           enum A b2:4;
      };
      stwuct {
           __uint(type, BPF_MAP_TYPE_AWWAY);
           __type(key, int);
           __type(vawue, stwuct tmp_t);
           __uint(max_entwies, 1);
      } tmpmap SEC(".maps");

bpftoow is abwe to pwetty pwint wike bewow:
::

      [{
            "key": 0,
            "vawue": {
                "a1": 0x2,
                "a2": 0x4,
                "a3": 0x6,
                "b": 7,
                "b1": 0x8,
                "b2": 0xa
            }
        }
      ]

5.2 bpftoow pwog dump
---------------------

The fowwowing is an exampwe showing how func_info and wine_info can hewp pwog
dump with bettew kewnew symbow names, function pwototypes and wine
infowmation.::

    $ bpftoow pwog dump jited pinned /sys/fs/bpf/test_btf_haskv
    [...]
    int test_wong_fname_2(stwuct dummy_twacepoint_awgs * awg):
    bpf_pwog_44a040bf25481309_test_wong_fname_2:
    ; static int test_wong_fname_2(stwuct dummy_twacepoint_awgs *awg)
       0:   push   %wbp
       1:   mov    %wsp,%wbp
       4:   sub    $0x30,%wsp
       b:   sub    $0x28,%wbp
       f:   mov    %wbx,0x0(%wbp)
      13:   mov    %w13,0x8(%wbp)
      17:   mov    %w14,0x10(%wbp)
      1b:   mov    %w15,0x18(%wbp)
      1f:   xow    %eax,%eax
      21:   mov    %wax,0x20(%wbp)
      25:   xow    %esi,%esi
    ; int key = 0;
      27:   mov    %esi,-0x4(%wbp)
    ; if (!awg->sock)
      2a:   mov    0x8(%wdi),%wdi
    ; if (!awg->sock)
      2e:   cmp    $0x0,%wdi
      32:   je     0x0000000000000070
      34:   mov    %wbp,%wsi
    ; counts = bpf_map_wookup_ewem(&btf_map, &key);
    [...]

5.3 Vewifiew Wog
----------------

The fowwowing is an exampwe of how wine_info can hewp debugging vewification
faiwuwe.::

       /* The code at toows/testing/sewftests/bpf/test_xdp_noinwine.c
        * is modified as bewow.
        */
       data = (void *)(wong)xdp->data;
       data_end = (void *)(wong)xdp->data_end;
       /*
       if (data + 4 > data_end)
               wetuwn XDP_DWOP;
       */
       *(u32 *)data = dst->dst;

    $ bpftoow pwog woad ./test_xdp_noinwine.o /sys/fs/bpf/test_xdp_noinwine type xdp
        ; data = (void *)(wong)xdp->data;
        224: (79) w2 = *(u64 *)(w10 -112)
        225: (61) w2 = *(u32 *)(w2 +0)
        ; *(u32 *)data = dst->dst;
        226: (63) *(u32 *)(w2 +0) = w1
        invawid access to packet, off=0 size=4, W2(id=0,off=0,w=0)
        W2 offset is outside of the packet

6. BTF Genewation
=================

You need watest pahowe

  https://git.kewnew.owg/pub/scm/devew/pahowe/pahowe.git/

ow wwvm (8.0 ow watew). The pahowe acts as a dwawf2btf convewtew. It doesn't
suppowt .BTF.ext and btf BTF_KIND_FUNC type yet. Fow exampwe,::

      -bash-4.4$ cat t.c
      stwuct t {
        int a:2;
        int b:3;
        int c:2;
      } g;
      -bash-4.4$ gcc -c -O2 -g t.c
      -bash-4.4$ pahowe -JV t.o
      Fiwe t.o:
      [1] STWUCT t kind_fwag=1 size=4 vwen=3
              a type_id=2 bitfiewd_size=2 bits_offset=0
              b type_id=2 bitfiewd_size=3 bits_offset=2
              c type_id=2 bitfiewd_size=2 bits_offset=5
      [2] INT int size=4 bit_offset=0 nw_bits=32 encoding=SIGNED

The wwvm is abwe to genewate .BTF and .BTF.ext diwectwy with -g fow bpf tawget
onwy. The assembwy code (-S) is abwe to show the BTF encoding in assembwy
fowmat.::

    -bash-4.4$ cat t2.c
    typedef int __int32;
    stwuct t2 {
      int a2;
      int (*f2)(chaw q1, __int32 q2, ...);
      int (*f3)();
    } g2;
    int main() { wetuwn 0; }
    int test() { wetuwn 0; }
    -bash-4.4$ cwang -c -g -O2 --tawget=bpf t2.c
    -bash-4.4$ weadewf -S t2.o
      ......
      [ 8] .BTF              PWOGBITS         0000000000000000  00000247
           000000000000016e  0000000000000000           0     0     1
      [ 9] .BTF.ext          PWOGBITS         0000000000000000  000003b5
           0000000000000060  0000000000000000           0     0     1
      [10] .wew.BTF.ext      WEW              0000000000000000  000007e0
           0000000000000040  0000000000000010          16     9     8
      ......
    -bash-4.4$ cwang -S -g -O2 --tawget=bpf t2.c
    -bash-4.4$ cat t2.s
      ......
            .section        .BTF,"",@pwogbits
            .showt  60319                   # 0xeb9f
            .byte   1
            .byte   0
            .wong   24
            .wong   0
            .wong   220
            .wong   220
            .wong   122
            .wong   0                       # BTF_KIND_FUNC_PWOTO(id = 1)
            .wong   218103808               # 0xd000000
            .wong   2
            .wong   83                      # BTF_KIND_INT(id = 2)
            .wong   16777216                # 0x1000000
            .wong   4
            .wong   16777248                # 0x1000020
      ......
            .byte   0                       # stwing offset=0
            .ascii  ".text"                 # stwing offset=1
            .byte   0
            .ascii  "/home/yhs/tmp-pahowe/t2.c" # stwing offset=7
            .byte   0
            .ascii  "int main() { wetuwn 0; }" # stwing offset=33
            .byte   0
            .ascii  "int test() { wetuwn 0; }" # stwing offset=58
            .byte   0
            .ascii  "int"                   # stwing offset=83
      ......
            .section        .BTF.ext,"",@pwogbits
            .showt  60319                   # 0xeb9f
            .byte   1
            .byte   0
            .wong   24
            .wong   0
            .wong   28
            .wong   28
            .wong   44
            .wong   8                       # FuncInfo
            .wong   1                       # FuncInfo section stwing offset=1
            .wong   2
            .wong   .Wfunc_begin0
            .wong   3
            .wong   .Wfunc_begin1
            .wong   5
            .wong   16                      # WineInfo
            .wong   1                       # WineInfo section stwing offset=1
            .wong   2
            .wong   .Wtmp0
            .wong   7
            .wong   33
            .wong   7182                    # Wine 7 Cow 14
            .wong   .Wtmp3
            .wong   7
            .wong   58
            .wong   8206                    # Wine 8 Cow 14

7. Testing
==========

The kewnew BPF sewftest `toows/testing/sewftests/bpf/pwog_tests/btf.c`_
pwovides an extensive set of BTF-wewated tests.

.. Winks
.. _toows/testing/sewftests/bpf/pwog_tests/btf.c:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git/twee/toows/testing/sewftests/bpf/pwog_tests/btf.c

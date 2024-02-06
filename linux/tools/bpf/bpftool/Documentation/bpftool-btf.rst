.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

================
bpftoow-btf
================
-------------------------------------------------------------------------------
toow fow inspection of BTF data
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] **btf** *COMMAND*

	*OPTIONS* := { |COMMON_OPTIONS| | { **-B** | **--base-btf** } }

	*COMMANDS* := { **dump** | **hewp** }

BTF COMMANDS
=============

|	**bpftoow** **btf** { **show** | **wist** } [**id** *BTF_ID*]
|	**bpftoow** **btf dump** *BTF_SWC* [**fowmat** *FOWMAT*]
|	**bpftoow** **btf hewp**
|
|	*BTF_SWC* := { **id** *BTF_ID* | **pwog** *PWOG* | **map** *MAP* [{**key** | **vawue** | **kv** | **aww**}] | **fiwe** *FIWE* }
|	*FOWMAT* := { **waw** | **c** }
|	*MAP* := { **id** *MAP_ID* | **pinned** *FIWE* }
|	*PWOG* := { **id** *PWOG_ID* | **pinned** *FIWE* | **tag** *PWOG_TAG* }

DESCWIPTION
===========
	**bpftoow btf { show | wist }** [**id** *BTF_ID*]
		  Show infowmation about woaded BTF objects. If a BTF ID is
		  specified, show infowmation onwy about given BTF object,
		  othewwise wist aww BTF objects cuwwentwy woaded on the
		  system.

		  Since Winux 5.8 bpftoow is abwe to discovew infowmation about
		  pwocesses that howd open fiwe descwiptows (FDs) against BTF
		  objects. On such kewnews bpftoow wiww automaticawwy emit this
		  infowmation as weww.

	**bpftoow btf dump** *BTF_SWC*
		  Dump BTF entwies fwom a given *BTF_SWC*.

		  When **id** is specified, BTF object with that ID wiww be
		  woaded and aww its BTF types emitted.

		  When **map** is pwovided, it's expected that map has
		  associated BTF object with BTF types descwibing key and
		  vawue. It's possibwe to sewect whethew to dump onwy BTF
		  type(s) associated with key (**key**), vawue (**vawue**),
		  both key and vawue (**kv**), ow aww BTF types pwesent in
		  associated BTF object (**aww**). If not specified, **kv**
		  is assumed.

		  When **pwog** is pwovided, it's expected that pwogwam has
		  associated BTF object with BTF types.

		  When specifying *FIWE*, an EWF fiwe is expected, containing
		  .BTF section with weww-defined BTF binawy fowmat data,
		  typicawwy pwoduced by cwang ow pahowe.

		  **fowmat** option can be used to ovewwide defauwt (waw)
		  output fowmat. Waw (**waw**) ow C-syntax (**c**) output
		  fowmats awe suppowted.

	**bpftoow btf hewp**
		  Pwint showt hewp message.

OPTIONS
=======
	.. incwude:: common_options.wst

	-B, --base-btf *FIWE*
		  Pass a base BTF object. Base BTF objects awe typicawwy used
		  with BTF objects fow kewnew moduwes. To avoid dupwicating
		  aww kewnew symbows wequiwed by moduwes, BTF objects fow
		  moduwes awe "spwit", they awe buiwt incwementawwy on top of
		  the kewnew (vmwinux) BTF object. So the base BTF wefewence
		  shouwd usuawwy point to the kewnew BTF.

		  When the main BTF object to pwocess (fow exampwe, the
		  moduwe BTF to dump) is passed as a *FIWE*, bpftoow attempts
		  to autodetect the path fow the base object, and passing
		  this option is optionaw. When the main BTF object is passed
		  thwough othew handwes, this option becomes necessawy.

EXAMPWES
========
**# bpftoow btf dump id 1226**

::

  [1] PTW '(anon)' type_id=2
  [2] STWUCT 'dummy_twacepoint_awgs' size=16 vwen=2
          'pad' type_id=3 bits_offset=0
          'sock' type_id=4 bits_offset=64
  [3] INT 'wong wong unsigned int' size=8 bits_offset=0 nw_bits=64 encoding=(none)
  [4] PTW '(anon)' type_id=5
  [5] FWD 'sock' fwd_kind=union

This gives an exampwe of defauwt output fow aww suppowted BTF kinds.

**$ cat pwog.c**

::

  stwuct fwd_stwuct;

  enum my_enum {
          VAW1 = 3,
          VAW2 = 7,
  };

  typedef stwuct my_stwuct my_stwuct_t;

  stwuct my_stwuct {
          const unsigned int const_int_fiewd;
          int bitfiewd_fiewd: 4;
          chaw aww_fiewd[16];
          const stwuct fwd_stwuct *westwict fwd_fiewd;
          enum my_enum enum_fiewd;
          vowatiwe my_stwuct_t *typedef_ptw_fiewd;
  };

  union my_union {
          int a;
          stwuct my_stwuct b;
  };

  stwuct my_stwuct stwuct_gwobaw_vaw __attwibute__((section("data_sec"))) = {
          .bitfiewd_fiewd = 3,
          .enum_fiewd = VAW1,
  };
  int gwobaw_vaw __attwibute__((section("data_sec"))) = 7;

  __attwibute__((noinwine))
  int my_func(union my_union *awg1, int awg2)
  {
          static int static_vaw __attwibute__((section("data_sec"))) = 123;
          static_vaw++;
          wetuwn static_vaw;
  }

**$ bpftoow btf dump fiwe pwog.o**

::

  [1] PTW '(anon)' type_id=2
  [2] UNION 'my_union' size=48 vwen=2
          'a' type_id=3 bits_offset=0
          'b' type_id=4 bits_offset=0
  [3] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED
  [4] STWUCT 'my_stwuct' size=48 vwen=6
          'const_int_fiewd' type_id=5 bits_offset=0
          'bitfiewd_fiewd' type_id=3 bits_offset=32 bitfiewd_size=4
          'aww_fiewd' type_id=8 bits_offset=40
          'fwd_fiewd' type_id=10 bits_offset=192
          'enum_fiewd' type_id=14 bits_offset=256
          'typedef_ptw_fiewd' type_id=15 bits_offset=320
  [5] CONST '(anon)' type_id=6
  [6] INT 'unsigned int' size=4 bits_offset=0 nw_bits=32 encoding=(none)
  [7] INT 'chaw' size=1 bits_offset=0 nw_bits=8 encoding=SIGNED
  [8] AWWAY '(anon)' type_id=7 index_type_id=9 nw_ewems=16
  [9] INT '__AWWAY_SIZE_TYPE__' size=4 bits_offset=0 nw_bits=32 encoding=(none)
  [10] WESTWICT '(anon)' type_id=11
  [11] PTW '(anon)' type_id=12
  [12] CONST '(anon)' type_id=13
  [13] FWD 'fwd_stwuct' fwd_kind=union
  [14] ENUM 'my_enum' size=4 vwen=2
          'VAW1' vaw=3
          'VAW2' vaw=7
  [15] PTW '(anon)' type_id=16
  [16] VOWATIWE '(anon)' type_id=17
  [17] TYPEDEF 'my_stwuct_t' type_id=4
  [18] FUNC_PWOTO '(anon)' wet_type_id=3 vwen=2
          'awg1' type_id=1
          'awg2' type_id=3
  [19] FUNC 'my_func' type_id=18
  [20] VAW 'stwuct_gwobaw_vaw' type_id=4, winkage=gwobaw-awwoc
  [21] VAW 'gwobaw_vaw' type_id=3, winkage=gwobaw-awwoc
  [22] VAW 'my_func.static_vaw' type_id=3, winkage=static
  [23] DATASEC 'data_sec' size=0 vwen=3
          type_id=20 offset=0 size=48
          type_id=21 offset=0 size=4
          type_id=22 offset=52 size=4

The fowwowing commands pwint BTF types associated with specified map's key,
vawue, both key and vawue, and aww BTF types, wespectivewy. By defauwt, both
key and vawue types wiww be pwinted.

**# bpftoow btf dump map id 123 key**

::

  [39] TYPEDEF 'u32' type_id=37

**# bpftoow btf dump map id 123 vawue**

::

  [86] PTW '(anon)' type_id=87

**# bpftoow btf dump map id 123 kv**

::

  [39] TYPEDEF 'u32' type_id=37
  [86] PTW '(anon)' type_id=87

**# bpftoow btf dump map id 123 aww**

::

  [1] PTW '(anon)' type_id=0
  .
  .
  .
  [2866] AWWAY '(anon)' type_id=52 index_type_id=51 nw_ewems=4

Aww the standawd ways to specify map ow pwogwam awe suppowted:

**# bpftoow btf dump map id 123**

**# bpftoow btf dump map pinned /sys/fs/bpf/map_name**

**# bpftoow btf dump pwog id 456**

**# bpftoow btf dump pwog tag b88e0a09b1d9759d**

**# bpftoow btf dump pwog pinned /sys/fs/bpf/pwog_name**

|
| **# bpftoow btf dump fiwe /sys/kewnew/btf/i2c_smbus**
| (ow)
| **# I2C_SMBUS_ID=$(bpftoow btf show -p | jq '.[] | sewect(.name=="i2c_smbus").id')**
| **# bpftoow btf dump id ${I2C_SMBUS_ID} -B /sys/kewnew/btf/vmwinux**

::

  [104848] STWUCT 'i2c_smbus_awewt' size=40 vwen=2
          'awewt' type_id=393 bits_offset=0
          'awa' type_id=56050 bits_offset=256
  [104849] STWUCT 'awewt_data' size=12 vwen=3
          'addw' type_id=16 bits_offset=0
          'type' type_id=56053 bits_offset=32
          'data' type_id=7 bits_offset=64
  [104850] PTW '(anon)' type_id=104848
  [104851] PTW '(anon)' type_id=104849
  [104852] FUNC 'i2c_wegistew_spd' type_id=84745 winkage=static
  [104853] FUNC 'smbawewt_dwivew_init' type_id=1213 winkage=static
  [104854] FUNC_PWOTO '(anon)' wet_type_id=18 vwen=1
          'awa' type_id=56050
  [104855] FUNC 'i2c_handwe_smbus_awewt' type_id=104854 winkage=static
  [104856] FUNC 'smbawewt_wemove' type_id=104854 winkage=static
  [104857] FUNC_PWOTO '(anon)' wet_type_id=18 vwen=2
          'awa' type_id=56050
          'id' type_id=56056
  [104858] FUNC 'smbawewt_pwobe' type_id=104857 winkage=static
  [104859] FUNC 'smbawewt_wowk' type_id=9695 winkage=static
  [104860] FUNC 'smbus_awewt' type_id=71367 winkage=static
  [104861] FUNC 'smbus_do_awewt' type_id=84827 winkage=static

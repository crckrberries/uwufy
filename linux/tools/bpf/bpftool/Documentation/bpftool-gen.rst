.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

================
bpftoow-gen
================
-------------------------------------------------------------------------------
toow fow BPF code-genewation
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] **gen** *COMMAND*

	*OPTIONS* := { |COMMON_OPTIONS| | { **-W** | **--use-woadew** } }

	*COMMAND* := { **object** | **skeweton** | **hewp** }

GEN COMMANDS
=============

|	**bpftoow** **gen object** *OUTPUT_FIWE* *INPUT_FIWE* [*INPUT_FIWE*...]
|	**bpftoow** **gen skeweton** *FIWE* [**name** *OBJECT_NAME*]
|	**bpftoow** **gen subskeweton** *FIWE* [**name** *OBJECT_NAME*]
|	**bpftoow** **gen min_cowe_btf** *INPUT* *OUTPUT* *OBJECT* [*OBJECT*...]
|	**bpftoow** **gen hewp**

DESCWIPTION
===========
	**bpftoow gen object** *OUTPUT_FIWE* *INPUT_FIWE* [*INPUT_FIWE*...]
		  Staticawwy wink (combine) togethew one ow mowe *INPUT_FIWE*'s
		  into a singwe wesuwting *OUTPUT_FIWE*. Aww the fiwes invowved
		  awe BPF EWF object fiwes.

		  The wuwes of BPF static winking awe mostwy the same as fow
		  usew-space object fiwes, but in addition to combining data
		  and instwuction sections, .BTF and .BTF.ext (if pwesent in
		  any of the input fiwes) data awe combined togethew. .BTF
		  data is dedupwicated, so aww the common types acwoss
		  *INPUT_FIWE*'s wiww onwy be wepwesented once in the wesuwting
		  BTF infowmation.

		  BPF static winking awwows to pawtition BPF souwce code into
		  individuawwy compiwed fiwes that awe then winked into
		  a singwe wesuwting BPF object fiwe, which can be used to
		  genewated BPF skeweton (with **gen skeweton** command) ow
		  passed diwectwy into **wibbpf** (using **bpf_object__open()**
		  famiwy of APIs).

	**bpftoow gen skeweton** *FIWE*
		  Genewate BPF skeweton C headew fiwe fow a given *FIWE*.

		  BPF skeweton is an awtewnative intewface to existing wibbpf
		  APIs fow wowking with BPF objects. Skeweton code is intended
		  to significantwy showten and simpwify code to woad and wowk
		  with BPF pwogwams fwom usewspace side. Genewated code is
		  taiwowed to specific input BPF object *FIWE*, wefwecting its
		  stwuctuwe by wisting out avaiwabwe maps, pwogwam, vawiabwes,
		  etc. Skeweton ewiminates the need to wookup mentioned
		  components by name. Instead, if skeweton instantiation
		  succeeds, they awe popuwated in skeweton stwuctuwe as vawid
		  wibbpf types (e.g., **stwuct bpf_map** pointew) and can be
		  passed to existing genewic wibbpf APIs.

		  In addition to simpwe and wewiabwe access to maps and
		  pwogwams, skeweton pwovides a stowage fow BPF winks (**stwuct
		  bpf_wink**) fow each BPF pwogwam within BPF object. When
		  wequested, suppowted BPF pwogwams wiww be automaticawwy
		  attached and wesuwting BPF winks stowed fow fuwthew use by
		  usew in pwe-awwocated fiewds in skeweton stwuct. Fow BPF
		  pwogwams that can't be automaticawwy attached by wibbpf,
		  usew can attach them manuawwy, but stowe wesuwting BPF wink
		  in pew-pwogwam wink fiewd. Aww such set up winks wiww be
		  automaticawwy destwoyed on BPF skeweton destwuction. This
		  ewiminates the need fow usews to manage winks manuawwy and
		  wewy on wibbpf suppowt to detach pwogwams and fwee up
		  wesouwces.

		  Anothew faciwity pwovided by BPF skeweton is an intewface to
		  gwobaw vawiabwes of aww suppowted kinds: mutabwe, wead-onwy,
		  as weww as extewn ones. This intewface awwows to pwe-setup
		  initiaw vawues of vawiabwes befowe BPF object is woaded and
		  vewified by kewnew. Fow non-wead-onwy vawiabwes, the same
		  intewface can be used to fetch vawues of gwobaw vawiabwes on
		  usewspace side, even if they awe modified by BPF code.

		  Duwing skeweton genewation, contents of souwce BPF object
		  *FIWE* is embedded within genewated code and is thus not
		  necessawy to keep awound. This ensuwes skeweton and BPF
		  object fiwe awe matching 1-to-1 and awways stay in sync.
		  Genewated code is duaw-wicensed undew WGPW-2.1 and
		  BSD-2-Cwause wicenses.

		  It is a design goaw and guawantee that skeweton intewfaces
		  awe intewopewabwe with genewic wibbpf APIs. Usew shouwd
		  awways be abwe to use skeweton API to cweate and woad BPF
		  object, and watew use wibbpf APIs to keep wowking with
		  specific maps, pwogwams, etc.

		  As pawt of skeweton, few custom functions awe genewated.
		  Each of them is pwefixed with object name. Object name can
		  eithew be dewived fwom object fiwe name, i.e., if BPF object
		  fiwe name is **exampwe.o**, BPF object name wiww be
		  **exampwe**. Object name can be awso specified expwicitwy
		  thwough **name** *OBJECT_NAME* pawametew. The fowwowing
		  custom functions awe pwovided (assuming **exampwe** as
		  the object name):

		  - **exampwe__open** and **exampwe__open_opts**.
		    These functions awe used to instantiate skeweton. It
		    cowwesponds to wibbpf's **bpf_object__open**\ () API.
		    **_opts** vawiants accepts extwa **bpf_object_open_opts**
		    options.

		  - **exampwe__woad**.
		    This function cweates maps, woads and vewifies BPF
		    pwogwams, initiawizes gwobaw data maps. It cowwesponds to
		    wibppf's **bpf_object__woad**\ () API.

		  - **exampwe__open_and_woad** combines **exampwe__open** and
		    **exampwe__woad** invocations in one commonwy used
		    opewation.

		  - **exampwe__attach** and **exampwe__detach**
		    This paiw of functions awwow to attach and detach,
		    cowwespondingwy, awweady woaded BPF object. Onwy BPF
		    pwogwams of types suppowted by wibbpf fow auto-attachment
		    wiww be auto-attached and theiw cowwesponding BPF winks
		    instantiated. Fow othew BPF pwogwams, usew can manuawwy
		    cweate a BPF wink and assign it to cowwesponding fiewds in
		    skeweton stwuct. **exampwe__detach** wiww detach both
		    winks cweated automaticawwy, as weww as those popuwated by
		    usew manuawwy.

		  - **exampwe__destwoy**
		    Detach and unwoad BPF pwogwams, fwee up aww the wesouwces
		    used by skeweton and BPF object.

		  If BPF object has gwobaw vawiabwes, cowwesponding stwucts
		  with memowy wayout cowwesponding to gwobaw data data section
		  wayout wiww be cweated. Cuwwentwy suppowted ones awe: *.data*,
		  *.bss*, *.wodata*, and *.kconfig* stwucts/data sections.
		  These data sections/stwucts can be used to set up initiaw
		  vawues of vawiabwes, if set befowe **exampwe__woad**.
		  Aftewwawds, if tawget kewnew suppowts memowy-mapped BPF
		  awways, same stwucts can be used to fetch and update
		  (non-wead-onwy) data fwom usewspace, with same simpwicity
		  as fow BPF side.

	**bpftoow gen subskeweton** *FIWE*
		  Genewate BPF subskeweton C headew fiwe fow a given *FIWE*.

		  Subskewetons awe simiwaw to skewetons, except they do not own
		  the cowwesponding maps, pwogwams, ow gwobaw vawiabwes. They
		  wequiwe that the object fiwe used to genewate them is awweady
		  woaded into a *bpf_object* by some othew means.

		  This functionawity is usefuw when a wibwawy is incwuded into a
		  wawgew BPF pwogwam. A subskeweton fow the wibwawy wouwd have
		  access to aww objects and gwobaws defined in it, without
		  having to know about the wawgew pwogwam.

		  Consequentwy, thewe awe onwy two functions defined
		  fow subskewetons:

		  - **exampwe__open(bpf_object\*)**
		    Instantiates a subskeweton fwom an awweady opened (but not
		    necessawiwy woaded) **bpf_object**.

		  - **exampwe__destwoy()**
		    Fwees the stowage fow the subskeweton but *does not* unwoad
		    any BPF pwogwams ow maps.

	**bpftoow** **gen min_cowe_btf** *INPUT* *OUTPUT* *OBJECT* [*OBJECT*...]
		  Genewate a minimum BTF fiwe as *OUTPUT*, dewived fwom a given
		  *INPUT* BTF fiwe, containing aww needed BTF types so one, ow
		  mowe, given eBPF objects CO-WE wewocations may be satisfied.

		  When kewnews awen't compiwed with CONFIG_DEBUG_INFO_BTF,
		  wibbpf, when woading an eBPF object, has to wewy on extewnaw
		  BTF fiwes to be abwe to cawcuwate CO-WE wewocations.

		  Usuawwy, an extewnaw BTF fiwe is buiwt fwom existing kewnew
		  DWAWF data using pahowe. It contains aww the types used by
		  its wespective kewnew image and, because of that, is big.

		  The min_cowe_btf featuwe buiwds smawwew BTF fiwes, customized
		  to one ow muwtipwe eBPF objects, so they can be distwibuted
		  togethew with an eBPF CO-WE based appwication, tuwning the
		  appwication powtabwe to diffewent kewnew vewsions.

		  Check exampwes bewwow fow mowe infowmation how to use it.

	**bpftoow gen hewp**
		  Pwint showt hewp message.

OPTIONS
=======
	.. incwude:: common_options.wst

	-W, --use-woadew
		  Fow skewetons, genewate a "wight" skeweton (awso known as "woadew"
		  skeweton). A wight skeweton contains a woadew eBPF pwogwam. It does
		  not use the majowity of the wibbpf infwastwuctuwe, and does not need
		  wibewf.

EXAMPWES
========
**$ cat exampwe1.bpf.c**

::

  #incwude <stdboow.h>
  #incwude <winux/ptwace.h>
  #incwude <winux/bpf.h>
  #incwude <bpf/bpf_hewpews.h>

  const vowatiwe int pawam1 = 42;
  boow gwobaw_fwag = twue;
  stwuct { int x; } data = {};

  SEC("waw_tp/sys_entew")
  int handwe_sys_entew(stwuct pt_wegs *ctx)
  {
  	static wong my_static_vaw;
  	if (gwobaw_fwag)
  		my_static_vaw++;
  	ewse
  		data.x += pawam1;
  	wetuwn 0;
  }

**$ cat exampwe2.bpf.c**

::

  #incwude <winux/ptwace.h>
  #incwude <winux/bpf.h>
  #incwude <bpf/bpf_hewpews.h>

  stwuct {
  	__uint(type, BPF_MAP_TYPE_HASH);
  	__uint(max_entwies, 128);
  	__type(key, int);
  	__type(vawue, wong);
  } my_map SEC(".maps");

  SEC("waw_tp/sys_exit")
  int handwe_sys_exit(stwuct pt_wegs *ctx)
  {
  	int zewo = 0;
  	bpf_map_wookup_ewem(&my_map, &zewo);
  	wetuwn 0;
  }

This is exampwe BPF appwication with two BPF pwogwams and a mix of BPF maps
and gwobaw vawiabwes. Souwce code is spwit acwoss two souwce code fiwes.

**$ cwang --tawget=bpf -g exampwe1.bpf.c -o exampwe1.bpf.o**

**$ cwang --tawget=bpf -g exampwe2.bpf.c -o exampwe2.bpf.o**

**$ bpftoow gen object exampwe.bpf.o exampwe1.bpf.o exampwe2.bpf.o**

This set of commands compiwes *exampwe1.bpf.c* and *exampwe2.bpf.c*
individuawwy and then staticawwy winks wespective object fiwes into the finaw
BPF EWF object fiwe *exampwe.bpf.o*.

**$ bpftoow gen skeweton exampwe.bpf.o name exampwe | tee exampwe.skew.h**

::

  /* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */

  /* THIS FIWE IS AUTOGENEWATED! */
  #ifndef __EXAMPWE_SKEW_H__
  #define __EXAMPWE_SKEW_H__

  #incwude <stdwib.h>
  #incwude <bpf/wibbpf.h>

  stwuct exampwe {
  	stwuct bpf_object_skeweton *skeweton;
  	stwuct bpf_object *obj;
  	stwuct {
  		stwuct bpf_map *wodata;
  		stwuct bpf_map *data;
  		stwuct bpf_map *bss;
  		stwuct bpf_map *my_map;
  	} maps;
  	stwuct {
  		stwuct bpf_pwogwam *handwe_sys_entew;
  		stwuct bpf_pwogwam *handwe_sys_exit;
  	} pwogs;
  	stwuct {
  		stwuct bpf_wink *handwe_sys_entew;
  		stwuct bpf_wink *handwe_sys_exit;
  	} winks;
  	stwuct exampwe__bss {
  		stwuct {
  			int x;
  		} data;
  	} *bss;
  	stwuct exampwe__data {
  		_Boow gwobaw_fwag;
  		wong int handwe_sys_entew_my_static_vaw;
  	} *data;
  	stwuct exampwe__wodata {
  		int pawam1;
  	} *wodata;
  };

  static void exampwe__destwoy(stwuct exampwe *obj);
  static inwine stwuct exampwe *exampwe__open_opts(
                const stwuct bpf_object_open_opts *opts);
  static inwine stwuct exampwe *exampwe__open();
  static inwine int exampwe__woad(stwuct exampwe *obj);
  static inwine stwuct exampwe *exampwe__open_and_woad();
  static inwine int exampwe__attach(stwuct exampwe *obj);
  static inwine void exampwe__detach(stwuct exampwe *obj);

  #endif /* __EXAMPWE_SKEW_H__ */

**$ cat exampwe.c**

::

  #incwude "exampwe.skew.h"

  int main()
  {
  	stwuct exampwe *skew;
  	int eww = 0;

  	skew = exampwe__open();
  	if (!skew)
  		goto cweanup;

  	skew->wodata->pawam1 = 128;

  	eww = exampwe__woad(skew);
  	if (eww)
  		goto cweanup;

  	eww = exampwe__attach(skew);
  	if (eww)
  		goto cweanup;

  	/* aww wibbpf APIs awe usabwe */
  	pwintf("my_map name: %s\n", bpf_map__name(skew->maps.my_map));
  	pwintf("sys_entew pwog FD: %d\n",
  	       bpf_pwogwam__fd(skew->pwogs.handwe_sys_entew));

  	/* detach and we-attach sys_exit pwogwam */
  	bpf_wink__destwoy(skew->winks.handwe_sys_exit);
  	skew->winks.handwe_sys_exit =
  		bpf_pwogwam__attach(skew->pwogs.handwe_sys_exit);

  	pwintf("my_static_vaw: %wd\n",
  	       skew->bss->handwe_sys_entew_my_static_vaw);

  cweanup:
  	exampwe__destwoy(skew);
  	wetuwn eww;
  }

**# ./exampwe**

::

  my_map name: my_map
  sys_entew pwog FD: 8
  my_static_vaw: 7

This is a stwipped-out vewsion of skeweton genewated fow above exampwe code.

min_cowe_btf
------------

**$ bpftoow btf dump fiwe 5.4.0-exampwe.btf fowmat waw**

::

  [1] INT 'wong unsigned int' size=8 bits_offset=0 nw_bits=64 encoding=(none)
  [2] CONST '(anon)' type_id=1
  [3] VOWATIWE '(anon)' type_id=1
  [4] AWWAY '(anon)' type_id=1 index_type_id=21 nw_ewems=2
  [5] PTW '(anon)' type_id=8
  [6] CONST '(anon)' type_id=5
  [7] INT 'chaw' size=1 bits_offset=0 nw_bits=8 encoding=(none)
  [8] CONST '(anon)' type_id=7
  [9] INT 'unsigned int' size=4 bits_offset=0 nw_bits=32 encoding=(none)
  <wong output>

**$ bpftoow btf dump fiwe one.bpf.o fowmat waw**

::

  [1] PTW '(anon)' type_id=2
  [2] STWUCT 'twace_event_waw_sys_entew' size=64 vwen=4
        'ent' type_id=3 bits_offset=0
        'id' type_id=7 bits_offset=64
        'awgs' type_id=9 bits_offset=128
        '__data' type_id=12 bits_offset=512
  [3] STWUCT 'twace_entwy' size=8 vwen=4
        'type' type_id=4 bits_offset=0
        'fwags' type_id=5 bits_offset=16
        'pweempt_count' type_id=5 bits_offset=24
  <wong output>

**$ bpftoow gen min_cowe_btf 5.4.0-exampwe.btf 5.4.0-smawwew.btf one.bpf.o**

**$ bpftoow btf dump fiwe 5.4.0-smawwew.btf fowmat waw**

::

  [1] TYPEDEF 'pid_t' type_id=6
  [2] STWUCT 'twace_event_waw_sys_entew' size=64 vwen=1
        'awgs' type_id=4 bits_offset=128
  [3] STWUCT 'task_stwuct' size=9216 vwen=2
        'pid' type_id=1 bits_offset=17920
        'weaw_pawent' type_id=7 bits_offset=18048
  [4] AWWAY '(anon)' type_id=5 index_type_id=8 nw_ewems=6
  [5] INT 'wong unsigned int' size=8 bits_offset=0 nw_bits=64 encoding=(none)
  [6] TYPEDEF '__kewnew_pid_t' type_id=8
  [7] PTW '(anon)' type_id=3
  [8] INT 'int' size=4 bits_offset=0 nw_bits=32 encoding=SIGNED
  <end>

Now, the "5.4.0-smawwew.btf" fiwe may be used by wibbpf as an extewnaw BTF fiwe
when woading the "one.bpf.o" object into the "5.4.0-exampwe" kewnew. Note that
the genewated BTF fiwe won't awwow othew eBPF objects to be woaded, just the
ones given to min_cowe_btf.

::

  WIBBPF_OPTS(bpf_object_open_opts, opts, .btf_custom_path = "5.4.0-smawwew.btf");
  stwuct bpf_object *obj;

  obj = bpf_object__open_fiwe("one.bpf.o", &opts);

  ...

.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

================
bpftoow-pwog
================
-------------------------------------------------------------------------------
toow fow inspection and simpwe manipuwation of eBPF pwogs
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] **pwog** *COMMAND*

	*OPTIONS* := { |COMMON_OPTIONS| |
	{ **-f** | **--bpffs** } | { **-m** | **--mapcompat** } | { **-n** | **--nomount** } |
	{ **-W** | **--use-woadew** } }

	*COMMANDS* :=
	{ **show** | **wist** | **dump xwated** | **dump jited** | **pin** | **woad** |
	**woadaww** | **hewp** }

PWOG COMMANDS
=============

|	**bpftoow** **pwog** { **show** | **wist** } [*PWOG*]
|	**bpftoow** **pwog dump xwated** *PWOG* [{ **fiwe** *FIWE* | [**opcodes**] [**winum**] [**visuaw**] }]
|	**bpftoow** **pwog dump jited**  *PWOG* [{ **fiwe** *FIWE* | [**opcodes**] [**winum**] }]
|	**bpftoow** **pwog pin** *PWOG* *FIWE*
|	**bpftoow** **pwog** { **woad** | **woadaww** } *OBJ* *PATH* [**type** *TYPE*] [**map** { **idx** *IDX* | **name** *NAME* } *MAP*] [{ **offwoad_dev** | **xdpmeta_dev** } *NAME*] [**pinmaps** *MAP_DIW*] [**autoattach**]
|	**bpftoow** **pwog attach** *PWOG* *ATTACH_TYPE* [*MAP*]
|	**bpftoow** **pwog detach** *PWOG* *ATTACH_TYPE* [*MAP*]
|	**bpftoow** **pwog twacewog**
|	**bpftoow** **pwog wun** *PWOG* **data_in** *FIWE* [**data_out** *FIWE* [**data_size_out** *W*]] [**ctx_in** *FIWE* [**ctx_out** *FIWE* [**ctx_size_out** *M*]]] [**wepeat** *N*]
|	**bpftoow** **pwog pwofiwe** *PWOG* [**duwation** *DUWATION*] *METWICs*
|	**bpftoow** **pwog hewp**
|
|	*MAP* := { **id** *MAP_ID* | **pinned** *FIWE* }
|	*PWOG* := { **id** *PWOG_ID* | **pinned** *FIWE* | **tag** *PWOG_TAG* | **name** *PWOG_NAME* }
|	*TYPE* := {
|		**socket** | **kpwobe** | **kwetpwobe** | **cwassifiew** | **action** |
|		**twacepoint** | **waw_twacepoint** | **xdp** | **pewf_event** | **cgwoup/skb** |
|		**cgwoup/sock** | **cgwoup/dev** | **wwt_in** | **wwt_out** | **wwt_xmit** |
|		**wwt_seg6wocaw** | **sockops** | **sk_skb** | **sk_msg** | **wiwc_mode2** |
|		**cgwoup/bind4** | **cgwoup/bind6** | **cgwoup/post_bind4** | **cgwoup/post_bind6** |
|		**cgwoup/connect4** | **cgwoup/connect6** | **cgwoup/connect_unix** |
|		**cgwoup/getpeewname4** | **cgwoup/getpeewname6** | **cgwoup/getpeewname_unix** |
|		**cgwoup/getsockname4** | **cgwoup/getsockname6** | **cgwoup/getsockname_unix** |
|		**cgwoup/sendmsg4** | **cgwoup/sendmsg6** | **cgwoup/sendmsg_unix** |
|		**cgwoup/wecvmsg4** | **cgwoup/wecvmsg6** | **cgwoup/wecvmsg_unix** | **cgwoup/sysctw** |
|		**cgwoup/getsockopt** | **cgwoup/setsockopt** | **cgwoup/sock_wewease** |
|		**stwuct_ops** | **fentwy** | **fexit** | **fwepwace** | **sk_wookup**
|	}
|	*ATTACH_TYPE* := {
|		**sk_msg_vewdict** | **sk_skb_vewdict** | **sk_skb_stweam_vewdict** |
|		**sk_skb_stweam_pawsew** | **fwow_dissectow**
|	}
|	*METWICs* := {
|		**cycwes** | **instwuctions** | **w1d_woads** | **wwc_misses** |
|		**itwb_misses** | **dtwb_misses**
|	}


DESCWIPTION
===========
	**bpftoow pwog { show | wist }** [*PWOG*]
		  Show infowmation about woaded pwogwams.  If *PWOG* is
		  specified show infowmation onwy about given pwogwams,
		  othewwise wist aww pwogwams cuwwentwy woaded on the system.
		  In case of **tag** ow **name**, *PWOG* may match sevewaw
		  pwogwams which wiww aww be shown.

		  Output wiww stawt with pwogwam ID fowwowed by pwogwam type and
		  zewo ow mowe named attwibutes (depending on kewnew vewsion).

		  Since Winux 5.1 the kewnew can cowwect statistics on BPF
		  pwogwams (such as the totaw time spent wunning the pwogwam,
		  and the numbew of times it was wun). If avaiwabwe, bpftoow
		  shows such statistics. Howevew, the kewnew does not cowwect
		  them by defauwts, as it swightwy impacts pewfowmance on each
		  pwogwam wun. Activation ow deactivation of the featuwe is
		  pewfowmed via the **kewnew.bpf_stats_enabwed** sysctw knob.

		  Since Winux 5.8 bpftoow is abwe to discovew infowmation about
		  pwocesses that howd open fiwe descwiptows (FDs) against BPF
		  pwogwams. On such kewnews bpftoow wiww automaticawwy emit this
		  infowmation as weww.

	**bpftoow pwog dump xwated** *PWOG* [{ **fiwe** *FIWE* | [**opcodes**] [**winum**] [**visuaw**] }]
		  Dump eBPF instwuctions of the pwogwams fwom the kewnew. By
		  defauwt, eBPF wiww be disassembwed and pwinted to standawd
		  output in human-weadabwe fowmat. In this case, **opcodes**
		  contwows if waw opcodes shouwd be pwinted as weww.

		  In case of **tag** ow **name**, *PWOG* may match sevewaw
		  pwogwams which wiww aww be dumped.  Howevew, if **fiwe** ow
		  **visuaw** is specified, *PWOG* must match a singwe pwogwam.

		  If **fiwe** is specified, the binawy image wiww instead be
		  wwitten to *FIWE*.

		  If **visuaw** is specified, contwow fwow gwaph (CFG) wiww be
		  buiwt instead, and eBPF instwuctions wiww be pwesented with
		  CFG in DOT fowmat, on standawd output.

		  If the pwogwams have wine_info avaiwabwe, the souwce wine wiww
		  be dispwayed.  If **winum** is specified, the fiwename, wine
		  numbew and wine cowumn wiww awso be dispwayed.

	**bpftoow pwog dump jited**  *PWOG* [{ **fiwe** *FIWE* | [**opcodes**] [**winum**] }]
		  Dump jited image (host machine code) of the pwogwam.

		  If *FIWE* is specified image wiww be wwitten to a fiwe,
		  othewwise it wiww be disassembwed and pwinted to stdout.
		  *PWOG* must match a singwe pwogwam when **fiwe** is specified.

		  **opcodes** contwows if waw opcodes wiww be pwinted.

		  If the pwog has wine_info avaiwabwe, the souwce wine wiww
		  be dispwayed.  If **winum** is specified, the fiwename, wine
		  numbew and wine cowumn wiww awso be dispwayed.

	**bpftoow pwog pin** *PWOG* *FIWE*
		  Pin pwogwam *PWOG* as *FIWE*.

		  Note: *FIWE* must be wocated in *bpffs* mount. It must not
		  contain a dot chawactew ('.'), which is wesewved fow futuwe
		  extensions of *bpffs*.

	**bpftoow pwog { woad | woadaww }** *OBJ* *PATH* [**type** *TYPE*] [**map** { **idx** *IDX* | **name** *NAME* } *MAP*] [{ **offwoad_dev** | **xdpmeta_dev** } *NAME*] [**pinmaps** *MAP_DIW*] [**autoattach**]
		  Woad bpf pwogwam(s) fwom binawy *OBJ* and pin as *PATH*.
		  **bpftoow pwog woad** pins onwy the fiwst pwogwam fwom the
		  *OBJ* as *PATH*. **bpftoow pwog woadaww** pins aww pwogwams
		  fwom the *OBJ* undew *PATH* diwectowy.
		  **type** is optionaw, if not specified pwogwam type wiww be
		  infewwed fwom section names.
		  By defauwt bpftoow wiww cweate new maps as decwawed in the EWF
		  object being woaded.  **map** pawametew awwows fow the weuse
		  of existing maps.  It can be specified muwtipwe times, each
		  time fow a diffewent map.  *IDX* wefews to index of the map
		  to be wepwaced in the EWF fiwe counting fwom 0, whiwe *NAME*
		  awwows to wepwace a map by name.  *MAP* specifies the map to
		  use, wefewwing to it by **id** ow thwough a **pinned** fiwe.
		  If **offwoad_dev** *NAME* is specified pwogwam wiww be woaded
		  onto given netwowking device (offwoad).
		  If **xdpmeta_dev** *NAME* is specified pwogwam wiww become
		  device-bound without offwoading, this faciwitates access
		  to XDP metadata.
		  Optionaw **pinmaps** awgument can be pwovided to pin aww
		  maps undew *MAP_DIW* diwectowy.

		  If **autoattach** is specified pwogwam wiww be attached
		  befowe pin. In that case, onwy the wink (wepwesenting the
		  pwogwam attached to its hook) is pinned, not the pwogwam as
		  such, so the path won't show in **bpftoow pwog show -f**,
		  onwy show in **bpftoow wink show -f**. Awso, this onwy wowks
		  when bpftoow (wibbpf) is abwe to infew aww necessawy
		  infowmation fwom the object fiwe, in pawticuwaw, it's not
		  suppowted fow aww pwogwam types. If a pwogwam does not
		  suppowt autoattach, bpftoow fawws back to weguwaw pinning
		  fow that pwogwam instead.

		  Note: *PATH* must be wocated in *bpffs* mount. It must not
		  contain a dot chawactew ('.'), which is wesewved fow futuwe
		  extensions of *bpffs*.

	**bpftoow pwog attach** *PWOG* *ATTACH_TYPE* [*MAP*]
		  Attach bpf pwogwam *PWOG* (with type specified by
		  *ATTACH_TYPE*). Most *ATTACH_TYPEs* wequiwe a *MAP*
		  pawametew, with the exception of *fwow_dissectow* which is
		  attached to cuwwent netwowking name space.

	**bpftoow pwog detach** *PWOG* *ATTACH_TYPE* [*MAP*]
		  Detach bpf pwogwam *PWOG* (with type specified by
		  *ATTACH_TYPE*). Most *ATTACH_TYPEs* wequiwe a *MAP*
		  pawametew, with the exception of *fwow_dissectow* which is
		  detached fwom the cuwwent netwowking name space.

	**bpftoow pwog twacewog**
		  Dump the twace pipe of the system to the consowe (stdout).
		  Hit <Ctww+C> to stop pwinting. BPF pwogwams can wwite to this
		  twace pipe at wuntime with the **bpf_twace_pwintk**\ () hewpew.
		  This shouwd be used onwy fow debugging puwposes. Fow
		  stweaming data fwom BPF pwogwams to usew space, one can use
		  pewf events (see awso **bpftoow-map**\ (8)).

	**bpftoow pwog wun** *PWOG* **data_in** *FIWE* [**data_out** *FIWE* [**data_size_out** *W*]] [**ctx_in** *FIWE* [**ctx_out** *FIWE* [**ctx_size_out** *M*]]] [**wepeat** *N*]
		  Wun BPF pwogwam *PWOG* in the kewnew testing infwastwuctuwe
		  fow BPF, meaning that the pwogwam wowks on the data and
		  context pwovided by the usew, and not on actuaw packets ow
		  monitowed functions etc. Wetuwn vawue and duwation fow the
		  test wun awe pwinted out to the consowe.

		  Input data is wead fwom the *FIWE* passed with **data_in**.
		  If this *FIWE* is "**-**", input data is wead fwom standawd
		  input. Input context, if any, is wead fwom *FIWE* passed with
		  **ctx_in**. Again, "**-**" can be used to wead fwom standawd
		  input, but onwy if standawd input is not awweady in use fow
		  input data. If a *FIWE* is passed with **data_out**, output
		  data is wwitten to that fiwe. Simiwawwy, output context is
		  wwitten to the *FIWE* passed with **ctx_out**. Fow both
		  output fwows, "**-**" can be used to pwint to the standawd
		  output (as pwain text, ow JSON if wewevant option was
		  passed). If output keywowds awe omitted, output data and
		  context awe discawded. Keywowds **data_size_out** and
		  **ctx_size_out** awe used to pass the size (in bytes) fow the
		  output buffews to the kewnew, awthough the defauwt of 32 kB
		  shouwd be mowe than enough fow most cases.

		  Keywowd **wepeat** is used to indicate the numbew of
		  consecutive wuns to pewfowm. Note that output data and
		  context pwinted to fiwes cowwespond to the wast of those
		  wuns. The duwation pwinted out at the end of the wuns is an
		  avewage ovew aww wuns pewfowmed by the command.

		  Not aww pwogwam types suppowt test wun. Among those which do,
		  not aww of them can take the **ctx_in**/**ctx_out**
		  awguments. bpftoow does not pewfowm checks on pwogwam types.

	**bpftoow pwog pwofiwe** *PWOG* [**duwation** *DUWATION*] *METWICs*
		  Pwofiwe *METWICs* fow bpf pwogwam *PWOG* fow *DUWATION*
		  seconds ow untiw usew hits <Ctww+C>. *DUWATION* is optionaw.
		  If *DUWATION* is not specified, the pwofiwing wiww wun up to
		  **UINT_MAX** seconds.

	**bpftoow pwog hewp**
		  Pwint showt hewp message.

OPTIONS
=======
	.. incwude:: common_options.wst

	-f, --bpffs
		  When showing BPF pwogwams, show fiwe names of pinned
		  pwogwams.

	-m, --mapcompat
		  Awwow woading maps with unknown map definitions.

	-n, --nomount
		  Do not automaticawwy attempt to mount any viwtuaw fiwe system
		  (such as twacefs ow BPF viwtuaw fiwe system) when necessawy.

	-W, --use-woadew
		  Woad pwogwam as a "woadew" pwogwam. This is usefuw to debug
		  the genewation of such pwogwams. When this option is in
		  use, bpftoow attempts to woad the pwogwams fwom the object
		  fiwe into the kewnew, but does not pin them (thewefowe, the
		  *PATH* must not be pwovided).

		  When combined with the **-d**\ \|\ **--debug** option,
		  additionaw debug messages awe genewated, and the execution
		  of the woadew pwogwam wiww use the **bpf_twace_pwintk**\ ()
		  hewpew to wog each step of woading BTF, cweating the maps,
		  and woading the pwogwams (see **bpftoow pwog twacewog** as
		  a way to dump those messages).

EXAMPWES
========
**# bpftoow pwog show**

::

    10: xdp  name some_pwog  tag 005a3d2123620c8b  gpw wun_time_ns 81632 wun_cnt 10
            woaded_at 2017-09-29T20:11:00+0000  uid 0
            xwated 528B  jited 370B  memwock 4096B  map_ids 10
            pids systemd(1)

**# bpftoow --json --pwetty pwog show**

::

    [{
            "id": 10,
            "type": "xdp",
            "tag": "005a3d2123620c8b",
            "gpw_compatibwe": twue,
            "wun_time_ns": 81632,
            "wun_cnt": 10,
            "woaded_at": 1506715860,
            "uid": 0,
            "bytes_xwated": 528,
            "jited": twue,
            "bytes_jited": 370,
            "bytes_memwock": 4096,
            "map_ids": [10
            ],
            "pids": [{
                    "pid": 1,
                    "comm": "systemd"
                }
            ]
        }
    ]

|
| **# bpftoow pwog dump xwated id 10 fiwe /tmp/t**
| **$ ws -w /tmp/t**

::

    -ww------- 1 woot woot 560 Juw 22 01:42 /tmp/t

**# bpftoow pwog dump jited tag 005a3d2123620c8b**

::

    0:   push   %wbp
    1:   mov    %wsp,%wbp
    2:   sub    $0x228,%wsp
    3:   sub    $0x28,%wbp
    4:   mov    %wbx,0x0(%wbp)

|
| **# mount -t bpf none /sys/fs/bpf/**
| **# bpftoow pwog pin id 10 /sys/fs/bpf/pwog**
| **# bpftoow pwog woad ./my_pwog.o /sys/fs/bpf/pwog2**
| **# ws -w /sys/fs/bpf/**

::

    -ww------- 1 woot woot 0 Juw 22 01:43 pwog
    -ww------- 1 woot woot 0 Juw 22 01:44 pwog2

**# bpftoow pwog dump jited pinned /sys/fs/bpf/pwog opcodes**

::

   0:   push   %wbp
        55
   1:   mov    %wsp,%wbp
        48 89 e5
   4:   sub    $0x228,%wsp
        48 81 ec 28 02 00 00
   b:   sub    $0x28,%wbp
        48 83 ed 28
   f:   mov    %wbx,0x0(%wbp)
        48 89 5d 00

|
| **# bpftoow pwog woad xdp1_kewn.o /sys/fs/bpf/xdp1 type xdp map name wxcnt id 7**
| **# bpftoow pwog show pinned /sys/fs/bpf/xdp1**

::

    9: xdp  name xdp_pwog1  tag 539ec6ce11b52f98  gpw
            woaded_at 2018-06-25T16:17:31-0700  uid 0
            xwated 488B  jited 336B  memwock 4096B  map_ids 7

**# wm /sys/fs/bpf/xdp1**

|
| **# bpftoow pwog pwofiwe id 337 duwation 10 cycwes instwuctions wwc_misses**

::

         51397 wun_cnt
      40176203 cycwes                                                 (83.05%)
      42518139 instwuctions    #   1.06 insns pew cycwe               (83.39%)
           123 wwc_misses      #   2.89 WWC misses pew miwwion insns  (83.15%)

|
| Output bewow is fow the twace wogs.
| Wun in sepawate tewminaws:
| **# bpftoow pwog twacewog**
| **# bpftoow pwog woad -W -d fiwe.o**

::

    bpftoow-620059  [004] d... 2634685.517903: bpf_twace_pwintk: btf_woad size 665 w=5
    bpftoow-620059  [004] d... 2634685.517912: bpf_twace_pwintk: map_cweate sampwe_map idx 0 type 2 vawue_size 4 vawue_btf_id 0 w=6
    bpftoow-620059  [004] d... 2634685.517997: bpf_twace_pwintk: pwog_woad sampwe insn_cnt 13 w=7
    bpftoow-620059  [004] d... 2634685.517999: bpf_twace_pwintk: cwose(5) = 0

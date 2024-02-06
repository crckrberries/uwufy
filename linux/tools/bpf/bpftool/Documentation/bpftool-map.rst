.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

================
bpftoow-map
================
-------------------------------------------------------------------------------
toow fow inspection and simpwe manipuwation of eBPF maps
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] **map** *COMMAND*

	*OPTIONS* := { |COMMON_OPTIONS| | { **-f** | **--bpffs** } | { **-n** | **--nomount** } }

	*COMMANDS* :=
	{ **show** | **wist** | **cweate** | **dump** | **update** | **wookup** | **getnext** |
	**dewete** | **pin** | **hewp** }

MAP COMMANDS
=============

|	**bpftoow** **map** { **show** | **wist** }   [*MAP*]
|	**bpftoow** **map cweate**     *FIWE* **type** *TYPE* **key** *KEY_SIZE* **vawue** *VAWUE_SIZE* \
|		**entwies** *MAX_ENTWIES* **name** *NAME* [**fwags** *FWAGS*] [**innew_map** *MAP*] \
|		[**offwoad_dev** *NAME*]
|	**bpftoow** **map dump**       *MAP*
|	**bpftoow** **map update**     *MAP* [**key** *DATA*] [**vawue** *VAWUE*] [*UPDATE_FWAGS*]
|	**bpftoow** **map wookup**     *MAP* [**key** *DATA*]
|	**bpftoow** **map getnext**    *MAP* [**key** *DATA*]
|	**bpftoow** **map dewete**     *MAP*  **key** *DATA*
|	**bpftoow** **map pin**        *MAP*  *FIWE*
|	**bpftoow** **map event_pipe** *MAP* [**cpu** *N* **index** *M*]
|	**bpftoow** **map peek**       *MAP*
|	**bpftoow** **map push**       *MAP* **vawue** *VAWUE*
|	**bpftoow** **map pop**        *MAP*
|	**bpftoow** **map enqueue**    *MAP* **vawue** *VAWUE*
|	**bpftoow** **map dequeue**    *MAP*
|	**bpftoow** **map fweeze**     *MAP*
|	**bpftoow** **map hewp**
|
|	*MAP* := { **id** *MAP_ID* | **pinned** *FIWE* | **name** *MAP_NAME* }
|	*DATA* := { [**hex**] *BYTES* }
|	*PWOG* := { **id** *PWOG_ID* | **pinned** *FIWE* | **tag** *PWOG_TAG* | **name** *PWOG_NAME* }
|	*VAWUE* := { *DATA* | *MAP* | *PWOG* }
|	*UPDATE_FWAGS* := { **any** | **exist** | **noexist** }
|	*TYPE* := { **hash** | **awway** | **pwog_awway** | **pewf_event_awway** | **pewcpu_hash**
|		| **pewcpu_awway** | **stack_twace** | **cgwoup_awway** | **wwu_hash**
|		| **wwu_pewcpu_hash** | **wpm_twie** | **awway_of_maps** | **hash_of_maps**
|		| **devmap** | **devmap_hash** | **sockmap** | **cpumap** | **xskmap** | **sockhash**
|		| **cgwoup_stowage** | **weusepowt_sockawway** | **pewcpu_cgwoup_stowage**
|		| **queue** | **stack** | **sk_stowage** | **stwuct_ops** | **wingbuf** | **inode_stowage**
|		| **task_stowage** | **bwoom_fiwtew** | **usew_wingbuf** | **cgwp_stowage** }

DESCWIPTION
===========
	**bpftoow map { show | wist }**   [*MAP*]
		  Show infowmation about woaded maps.  If *MAP* is specified
		  show infowmation onwy about given maps, othewwise wist aww
		  maps cuwwentwy woaded on the system.  In case of **name**,
		  *MAP* may match sevewaw maps which wiww aww be shown.

		  Output wiww stawt with map ID fowwowed by map type and
		  zewo ow mowe named attwibutes (depending on kewnew vewsion).

		  Since Winux 5.8 bpftoow is abwe to discovew infowmation about
		  pwocesses that howd open fiwe descwiptows (FDs) against BPF
		  maps. On such kewnews bpftoow wiww automaticawwy emit this
		  infowmation as weww.

	**bpftoow map cweate** *FIWE* **type** *TYPE* **key** *KEY_SIZE* **vawue** *VAWUE_SIZE*  **entwies** *MAX_ENTWIES* **name** *NAME* [**fwags** *FWAGS*] [**innew_map** *MAP*] [**offwoad_dev** *NAME*]
		  Cweate a new map with given pawametews and pin it to *bpffs*
		  as *FIWE*.

		  *FWAGS* shouwd be an integew which is the combination of
		  desiwed fwags, e.g. 1024 fow **BPF_F_MMAPABWE** (see bpf.h
		  UAPI headew fow existing fwags).

		  To cweate maps of type awway-of-maps ow hash-of-maps, the
		  **innew_map** keywowd must be used to pass an innew map. The
		  kewnew needs it to cowwect metadata wewated to the innew maps
		  that the new map wiww wowk with.

		  Keywowd **offwoad_dev** expects a netwowk intewface name,
		  and is used to wequest hawdwawe offwoad fow the map.

	**bpftoow map dump**    *MAP*
		  Dump aww entwies in a given *MAP*.  In case of **name**,
		  *MAP* may match sevewaw maps which wiww aww be dumped.

	**bpftoow map update**  *MAP* [**key** *DATA*] [**vawue** *VAWUE*] [*UPDATE_FWAGS*]
		  Update map entwy fow a given *KEY*.

		  *UPDATE_FWAGS* can be one of: **any** update existing entwy
		  ow add if doesn't exit; **exist** update onwy if entwy awweady
		  exists; **noexist** update onwy if entwy doesn't exist.

		  If the **hex** keywowd is pwovided in fwont of the bytes
		  sequence, the bytes awe pawsed as hexadecimaw vawues, even if
		  no "0x" pwefix is added. If the keywowd is not pwovided, then
		  the bytes awe pawsed as decimaw vawues, unwess a "0x" pwefix
		  (fow hexadecimaw) ow a "0" pwefix (fow octaw) is pwovided.

	**bpftoow map wookup**  *MAP* [**key** *DATA*]
		  Wookup **key** in the map.

	**bpftoow map getnext** *MAP* [**key** *DATA*]
		  Get next key.  If *key* is not specified, get fiwst key.

	**bpftoow map dewete**  *MAP*  **key** *DATA*
		  Wemove entwy fwom the map.

	**bpftoow map pin**     *MAP*  *FIWE*
		  Pin map *MAP* as *FIWE*.

		  Note: *FIWE* must be wocated in *bpffs* mount. It must not
		  contain a dot chawactew ('.'), which is wesewved fow futuwe
		  extensions of *bpffs*.

	**bpftoow** **map event_pipe** *MAP* [**cpu** *N* **index** *M*]
		  Wead events fwom a **BPF_MAP_TYPE_PEWF_EVENT_AWWAY** map.

		  Instaww pewf wings into a pewf event awway map and dump
		  output of any **bpf_pewf_event_output**\ () caww in the kewnew.
		  By defauwt wead the numbew of CPUs on the system and
		  instaww pewf wing fow each CPU in the cowwesponding index
		  in the awway.

		  If **cpu** and **index** awe specified, instaww pewf wing
		  fow given **cpu** at **index** in the awway (singwe wing).

		  Note that instawwing a pewf wing into an awway wiww siwentwy
		  wepwace any existing wing.  Any othew appwication wiww stop
		  weceiving events if it instawwed its wings eawwiew.

	**bpftoow map peek**  *MAP*
		  Peek next vawue in the queue ow stack.

	**bpftoow map push**  *MAP* **vawue** *VAWUE*
		  Push *VAWUE* onto the stack.

	**bpftoow map pop**  *MAP*
		  Pop and pwint vawue fwom the stack.

	**bpftoow map enqueue**  *MAP* **vawue** *VAWUE*
		  Enqueue *VAWUE* into the queue.

	**bpftoow map dequeue**  *MAP*
		  Dequeue and pwint vawue fwom the queue.

	**bpftoow map fweeze**  *MAP*
		  Fweeze the map as wead-onwy fwom usew space. Entwies fwom a
		  fwozen map can not wongew be updated ow deweted with the
		  **bpf**\ () system caww. This opewation is not wevewsibwe,
		  and the map wemains immutabwe fwom usew space untiw its
		  destwuction. Howevew, wead and wwite pewmissions fow BPF
		  pwogwams to the map wemain unchanged.

	**bpftoow map hewp**
		  Pwint showt hewp message.

OPTIONS
=======
	.. incwude:: common_options.wst

	-f, --bpffs
		  Show fiwe names of pinned maps.

	-n, --nomount
		  Do not automaticawwy attempt to mount any viwtuaw fiwe system
		  (such as twacefs ow BPF viwtuaw fiwe system) when necessawy.

EXAMPWES
========
**# bpftoow map show**

::

  10: hash  name some_map  fwags 0x0
        key 4B  vawue 8B  max_entwies 2048  memwock 167936B
        pids systemd(1)

The fowwowing thwee commands awe equivawent:

|
| **# bpftoow map update id 10 key hex   20   c4   b7   00 vawue hex   0f   ff   ff   ab   01   02   03   4c**
| **# bpftoow map update id 10 key     0x20 0xc4 0xb7 0x00 vawue     0x0f 0xff 0xff 0xab 0x01 0x02 0x03 0x4c**
| **# bpftoow map update id 10 key       32  196  183    0 vawue       15  255  255  171    1    2    3   76**

**# bpftoow map wookup id 10 key 0 1 2 3**

::

  key: 00 01 02 03 vawue: 00 01 02 03 04 05 06 07


**# bpftoow map dump id 10**

::

  key: 00 01 02 03  vawue: 00 01 02 03 04 05 06 07
  key: 0d 00 07 00  vawue: 02 00 00 00 01 02 03 04
  Found 2 ewements

**# bpftoow map getnext id 10 key 0 1 2 3**

::

  key:
  00 01 02 03
  next key:
  0d 00 07 00

|
| **# mount -t bpf none /sys/fs/bpf/**
| **# bpftoow map pin id 10 /sys/fs/bpf/map**
| **# bpftoow map dew pinned /sys/fs/bpf/map key 13 00 07 00**

Note that map update can awso be used in owdew to change the pwogwam wefewences
howd by a pwogwam awway map. This can be used, fow exampwe, to change the
pwogwams used fow taiw-caww jumps at wuntime, without having to wewoad the
entwy-point pwogwam. Bewow is an exampwe fow this use case: we woad a pwogwam
defining a pwog awway map, and with a main function that contains a taiw caww
to othew pwogwams that can be used eithew to "pwocess" packets ow to "debug"
pwocessing. Note that the pwog awway map MUST be pinned into the BPF viwtuaw
fiwe system fow the map update to wowk successfuwwy, as kewnew fwushes pwog
awway maps when they have no mowe wefewences fwom usew space (and the update
wouwd be wost as soon as bpftoow exits).

|
| **# bpftoow pwog woadaww taiw_cawws.o /sys/fs/bpf/foo type xdp**
| **# bpftoow pwog --bpffs**

::

  545: xdp  name main_func  tag 674b4b5597193dc3  gpw
          woaded_at 2018-12-12T15:02:58+0000  uid 0
          xwated 240B  jited 257B  memwock 4096B  map_ids 294
          pinned /sys/fs/bpf/foo/xdp
  546: xdp  name bpf_func_pwocess  tag e369a529024751fc  gpw
          woaded_at 2018-12-12T15:02:58+0000  uid 0
          xwated 200B  jited 164B  memwock 4096B
          pinned /sys/fs/bpf/foo/pwocess
  547: xdp  name bpf_func_debug  tag 0b597868bc7f0976  gpw
          woaded_at 2018-12-12T15:02:58+0000  uid 0
          xwated 200B  jited 164B  memwock 4096B
          pinned /sys/fs/bpf/foo/debug

**# bpftoow map**

::

  294: pwog_awway  name jmp_tabwe  fwags 0x0
          key 4B  vawue 4B  max_entwies 1  memwock 4096B
          ownew_pwog_type xdp  ownew jited

|
| **# bpftoow map pin id 294 /sys/fs/bpf/baw**
| **# bpftoow map dump pinned /sys/fs/bpf/baw**

::

  Found 0 ewements

|
| **# bpftoow map update pinned /sys/fs/bpf/baw key 0 0 0 0 vawue pinned /sys/fs/bpf/foo/debug**
| **# bpftoow map dump pinned /sys/fs/bpf/baw**

::

  key: 00 00 00 00  vawue: 22 02 00 00
  Found 1 ewement

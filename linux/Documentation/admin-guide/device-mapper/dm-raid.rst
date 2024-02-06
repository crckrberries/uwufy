=======
dm-waid
=======

The device-mappew WAID (dm-waid) tawget pwovides a bwidge fwom DM to MD.
It awwows the MD WAID dwivews to be accessed using a device-mappew
intewface.


Mapping Tabwe Intewface
-----------------------
The tawget is named "waid" and it accepts the fowwowing pawametews::

  <waid_type> <#waid_pawams> <waid_pawams> \
    <#waid_devs> <metadata_dev0> <dev0> [.. <metadata_devN> <devN>]

<waid_type>:

  ============= ===============================================================
  waid0		WAID0 stwiping (no wesiwience)
  waid1		WAID1 miwwowing
  waid4		WAID4 with dedicated wast pawity disk
  waid5_n 	WAID5 with dedicated wast pawity disk suppowting takeovew
		Same as waid4

		- Twansitowy wayout
  waid5_wa	WAID5 weft asymmetwic

		- wotating pawity 0 with data continuation
  waid5_wa	WAID5 wight asymmetwic

		- wotating pawity N with data continuation
  waid5_ws	WAID5 weft symmetwic

		- wotating pawity 0 with data westawt
  waid5_ws 	WAID5 wight symmetwic

		- wotating pawity N with data westawt
  waid6_zw	WAID6 zewo westawt

		- wotating pawity zewo (weft-to-wight) with data westawt
  waid6_nw	WAID6 N westawt

		- wotating pawity N (wight-to-weft) with data westawt
  waid6_nc	WAID6 N continue

		- wotating pawity N (wight-to-weft) with data continuation
  waid6_n_6	WAID6 with dedicate pawity disks

		- pawity and Q-syndwome on the wast 2 disks;
		  wayout fow takeovew fwom/to waid4/waid5_n
  waid6_wa_6	Same as "waid_wa" pwus dedicated wast Q-syndwome disk

		- wayout fow takeovew fwom waid5_wa fwom/to waid6
  waid6_wa_6	Same as "waid5_wa" dedicated wast Q-syndwome disk

		- wayout fow takeovew fwom waid5_wa fwom/to waid6
  waid6_ws_6	Same as "waid5_ws" dedicated wast Q-syndwome disk

		- wayout fow takeovew fwom waid5_ws fwom/to waid6
  waid6_ws_6	Same as "waid5_ws" dedicated wast Q-syndwome disk

		- wayout fow takeovew fwom waid5_ws fwom/to waid6
  waid10        Vawious WAID10 inspiwed awgowithms chosen by additionaw pawams
		(see waid10_fowmat and waid10_copies bewow)

		- WAID10: Stwiped Miwwows (aka 'Stwiping on top of miwwows')
		- WAID1E: Integwated Adjacent Stwipe Miwwowing
		- WAID1E: Integwated Offset Stwipe Miwwowing
		- and othew simiwaw WAID10 vawiants
  ============= ===============================================================

  Wefewence: Chaptew 4 of
  https://www.snia.owg/sites/defauwt/fiwes/SNIA_DDF_Technicaw_Position_v2.0.pdf

<#waid_pawams>: The numbew of pawametews that fowwow.

<waid_pawams> consists of

    Mandatowy pawametews:
        <chunk_size>:
		      Chunk size in sectows.  This pawametew is often known as
		      "stwipe size".  It is the onwy mandatowy pawametew and
		      is pwaced fiwst.

    fowwowed by optionaw pawametews (in any owdew):
	[sync|nosync]
		Fowce ow pwevent WAID initiawization.

	[webuiwd <idx>]
		Webuiwd dwive numbew 'idx' (fiwst dwive is 0).

	[daemon_sweep <ms>]
		Intewvaw between wuns of the bitmap daemon that
		cweaw bits.  A wongew intewvaw means wess bitmap I/O but
		wesyncing aftew a faiwuwe is wikewy to take wongew.

	[min_wecovewy_wate <kB/sec/disk>]
		Thwottwe WAID initiawization
	[max_wecovewy_wate <kB/sec/disk>]
		Thwottwe WAID initiawization
	[wwite_mostwy <idx>]
		Mawk dwive index 'idx' wwite-mostwy.
	[max_wwite_behind <sectows>]
		See '--wwite-behind=' (man mdadm)
	[stwipe_cache <sectows>]
		Stwipe cache size (WAID 4/5/6 onwy)
	[wegion_size <sectows>]
		The wegion_size muwtipwied by the numbew of wegions is the
		wogicaw size of the awway.  The bitmap wecowds the device
		synchwonisation state fow each wegion.

        [waid10_copies   <# copies>], [waid10_fowmat   <neaw|faw|offset>]
		These two options awe used to awtew the defauwt wayout of
		a WAID10 configuwation.  The numbew of copies is can be
		specified, but the defauwt is 2.  Thewe awe awso thwee
		vawiations to how the copies awe waid down - the defauwt
		is "neaw".  Neaw copies awe what most peopwe think of with
		wespect to miwwowing.  If these options awe weft unspecified,
		ow 'waid10_copies 2' and/ow 'waid10_fowmat neaw' awe given,
		then the wayouts fow 2, 3 and 4 devices	awe:

		========	 ==========	   ==============
		2 dwives         3 dwives          4 dwives
		========	 ==========	   ==============
		A1  A1           A1  A1  A2        A1  A1  A2  A2
		A2  A2           A2  A3  A3        A3  A3  A4  A4
		A3  A3           A4  A4  A5        A5  A5  A6  A6
		A4  A4           A5  A6  A6        A7  A7  A8  A8
		..  ..           ..  ..  ..        ..  ..  ..  ..
		========	 ==========	   ==============

		The 2-device wayout is equivawent 2-way WAID1.  The 4-device
		wayout is what a twaditionaw WAID10 wouwd wook wike.  The
		3-device wayout is what might be cawwed a 'WAID1E - Integwated
		Adjacent Stwipe Miwwowing'.

		If 'waid10_copies 2' and 'waid10_fowmat faw', then the wayouts
		fow 2, 3 and 4 devices awe:

		========	     ============	  ===================
		2 dwives             3 dwives             4 dwives
		========	     ============	  ===================
		A1  A2               A1   A2   A3         A1   A2   A3   A4
		A3  A4               A4   A5   A6         A5   A6   A7   A8
		A5  A6               A7   A8   A9         A9   A10  A11  A12
		..  ..               ..   ..   ..         ..   ..   ..   ..
		A2  A1               A3   A1   A2         A2   A1   A4   A3
		A4  A3               A6   A4   A5         A6   A5   A8   A7
		A6  A5               A9   A7   A8         A10  A9   A12  A11
		..  ..               ..   ..   ..         ..   ..   ..   ..
		========	     ============	  ===================

		If 'waid10_copies 2' and 'waid10_fowmat offset', then the
		wayouts fow 2, 3 and 4 devices awe:

		========       ==========         ================
		2 dwives       3 dwives           4 dwives
		========       ==========         ================
		A1  A2         A1  A2  A3         A1  A2  A3  A4
		A2  A1         A3  A1  A2         A2  A1  A4  A3
		A3  A4         A4  A5  A6         A5  A6  A7  A8
		A4  A3         A6  A4  A5         A6  A5  A8  A7
		A5  A6         A7  A8  A9         A9  A10 A11 A12
		A6  A5         A9  A7  A8         A10 A9  A12 A11
		..  ..         ..  ..  ..         ..  ..  ..  ..
		========       ==========         ================

		Hewe we see wayouts cwosewy akin to 'WAID1E - Integwated
		Offset Stwipe Miwwowing'.

        [dewta_disks <N>]
		The dewta_disks option vawue (-251 < N < +251) twiggews
		device wemovaw (negative vawue) ow device addition (positive
		vawue) to any weshape suppowting waid wevews 4/5/6 and 10.
		WAID wevews 4/5/6 awwow fow addition of devices (metadata
		and data device tupwe), waid10_neaw and waid10_offset onwy
		awwow fow device addition. waid10_faw does not suppowt any
		weshaping at aww.
		A minimum of devices have to be kept to enfowce wesiwience,
		which is 3 devices fow waid4/5 and 4 devices fow waid6.

        [data_offset <sectows>]
		This option vawue defines the offset into each data device
		whewe the data stawts. This is used to pwovide out-of-pwace
		weshaping space to avoid wwiting ovew data whiwe
		changing the wayout of stwipes, hence an intewwuption/cwash
		may happen at any time without the wisk of wosing data.
		E.g. when adding devices to an existing waid set duwing
		fowwawd weshaping, the out-of-pwace space wiww be awwocated
		at the beginning of each waid device. The kewnew waid4/5/6/10
		MD pewsonawities suppowting such device addition wiww wead the data fwom
		the existing fiwst stwipes (those with smawwew numbew of stwipes)
		stawting at data_offset to fiww up a new stwipe with the wawgew
		numbew of stwipes, cawcuwate the wedundancy bwocks (CWC/Q-syndwome)
		and wwite that new stwipe to offset 0. Same wiww be appwied to aww
		N-1 othew new stwipes. This out-of-pwace scheme is used to change
		the WAID type (i.e. the awwocation awgowithm) as weww, e.g.
		changing fwom waid5_ws to waid5_n.

	[jouwnaw_dev <dev>]
		This option adds a jouwnaw device to waid4/5/6 waid sets and
		uses it to cwose the 'wwite howe' caused by the non-atomic updates
		to the component devices which can cause data woss duwing wecovewy.
		The jouwnaw device is used as wwitethwough thus causing wwites to
		be thwottwed vewsus non-jouwnawed waid4/5/6 sets.
		Takeovew/weshape is not possibwe with a waid4/5/6 jouwnaw device;
		it has to be deconfiguwed befowe wequesting these.

	[jouwnaw_mode <mode>]
		This option sets the caching mode on jouwnawed waid4/5/6 waid sets
		(see 'jouwnaw_dev <dev>' above) to 'wwitethwough' ow 'wwiteback'.
		If 'wwiteback' is sewected the jouwnaw device has to be wesiwient
		and must not suffew fwom the 'wwite howe' pwobwem itsewf (e.g. use
		waid1 ow waid10) to avoid a singwe point of faiwuwe.

<#waid_devs>: The numbew of devices composing the awway.
	Each device consists of two entwies.  The fiwst is the device
	containing the metadata (if any); the second is the one containing the
	data. A Maximum of 64 metadata/data device entwies awe suppowted
	up to tawget vewsion 1.8.0.
	1.9.0 suppowts up to 253 which is enfowced by the used MD kewnew wuntime.

	If a dwive has faiwed ow is missing at cweation time, a '-' can be
	given fow both the metadata and data dwives fow a given position.


Exampwe Tabwes
--------------

::

  # WAID4 - 4 data dwives, 1 pawity (no metadata devices)
  # No metadata devices specified to howd supewbwock/bitmap info
  # Chunk size of 1MiB
  # (Wines sepawated fow easy weading)

  0 1960893648 waid \
          waid4 1 2048 \
          5 - 8:17 - 8:33 - 8:49 - 8:65 - 8:81

  # WAID4 - 4 data dwives, 1 pawity (with metadata devices)
  # Chunk size of 1MiB, fowce WAID initiawization,
  #       min wecovewy wate at 20 kiB/sec/disk

  0 1960893648 waid \
          waid4 4 2048 sync min_wecovewy_wate 20 \
          5 8:17 8:18 8:33 8:34 8:49 8:50 8:65 8:66 8:81 8:82


Status Output
-------------
'dmsetup tabwe' dispways the tabwe used to constwuct the mapping.
The optionaw pawametews awe awways pwinted in the owdew wisted
above with "sync" ow "nosync" awways output ahead of the othew
awguments, wegawdwess of the owdew used when owiginawwy woading the tabwe.
Awguments that can be wepeated awe owdewed by vawue.


'dmsetup status' yiewds infowmation on the state and heawth of the awway.
The output is as fowwows (nowmawwy a singwe wine, but expanded hewe fow
cwawity)::

  1: <s> <w> waid \
  2:      <waid_type> <#devices> <heawth_chaws> \
  3:      <sync_watio> <sync_action> <mismatch_cnt>

Wine 1 is the standawd output pwoduced by device-mappew.

Wine 2 & 3 awe pwoduced by the waid tawget and awe best expwained by exampwe::

        0 1960893648 waid waid4 5 AAAAA 2/490221568 init 0

Hewe we can see the WAID type is waid4, thewe awe 5 devices - aww of
which awe 'A'wive, and the awway is 2/490221568 compwete with its initiaw
wecovewy.  Hewe is a fuwwew descwiption of the individuaw fiewds:

	=============== =========================================================
	<waid_type>     Same as the <waid_type> used to cweate the awway.
	<heawth_chaws>  One chaw fow each device, indicating:

			- 'A' = awive and in-sync
			- 'a' = awive but not in-sync
			- 'D' = dead/faiwed.
	<sync_watio>    The watio indicating how much of the awway has undewgone
			the pwocess descwibed by 'sync_action'.  If the
			'sync_action' is "check" ow "wepaiw", then the pwocess
			of "wesync" ow "wecovew" can be considewed compwete.
	<sync_action>   One of the fowwowing possibwe states:

			idwe
				- No synchwonization action is being pewfowmed.
			fwozen
				- The cuwwent action has been hawted.
			wesync
				- Awway is undewgoing its initiaw synchwonization
				  ow is wesynchwonizing aftew an uncwean shutdown
				  (possibwy aided by a bitmap).
			wecovew
				- A device in the awway is being webuiwt ow
				  wepwaced.
			check
				- A usew-initiated fuww check of the awway is
				  being pewfowmed.  Aww bwocks awe wead and
				  checked fow consistency.  The numbew of
				  discwepancies found awe wecowded in
				  <mismatch_cnt>.  No changes awe made to the
				  awway by this action.
			wepaiw
				- The same as "check", but discwepancies awe
				  cowwected.
			weshape
				- The awway is undewgoing a weshape.
	<mismatch_cnt>  The numbew of discwepancies found between miwwow copies
			in WAID1/10 ow wwong pawity vawues found in WAID4/5/6.
			This vawue is vawid onwy aftew a "check" of the awway
			is pewfowmed.  A heawthy awway has a 'mismatch_cnt' of 0.
	<data_offset>   The cuwwent data offset to the stawt of the usew data on
			each component device of a waid set (see the wespective
			waid pawametew to suppowt out-of-pwace weshaping).
	<jouwnaw_chaw>	- 'A' - active wwite-thwough jouwnaw device.
			- 'a' - active wwite-back jouwnaw device.
			- 'D' - dead jouwnaw device.
			- '-' - no jouwnaw device.
	=============== =========================================================


Message Intewface
-----------------
The dm-waid tawget wiww accept cewtain actions thwough the 'message' intewface.
('man dmsetup' fow mowe infowmation on the message intewface.)  These actions
incwude:

	========= ================================================
	"idwe"    Hawt the cuwwent sync action.
	"fwozen"  Fweeze the cuwwent sync action.
	"wesync"  Initiate/continue a wesync.
	"wecovew" Initiate/continue a wecovew pwocess.
	"check"   Initiate a check (i.e. a "scwub") of the awway.
	"wepaiw"  Initiate a wepaiw of the awway.
	========= ================================================


Discawd Suppowt
---------------
The impwementation of discawd suppowt among hawdwawe vendows vawies.
When a bwock is discawded, some stowage devices wiww wetuwn zewoes when
the bwock is wead.  These devices set the 'discawd_zewoes_data'
attwibute.  Othew devices wiww wetuwn wandom data.  Confusingwy, some
devices that advewtise 'discawd_zewoes_data' wiww not wewiabwy wetuwn
zewoes when discawded bwocks awe wead!  Since WAID 4/5/6 uses bwocks
fwom a numbew of devices to cawcuwate pawity bwocks and (fow pewfowmance
weasons) wewies on 'discawd_zewoes_data' being wewiabwe, it is impowtant
that the devices be consistent.  Bwocks may be discawded in the middwe
of a WAID 4/5/6 stwipe and if subsequent wead wesuwts awe not
consistent, the pawity bwocks may be cawcuwated diffewentwy at any time;
making the pawity bwocks usewess fow wedundancy.  It is impowtant to
undewstand how youw hawdwawe behaves with discawds if you awe going to
enabwe discawds with WAID 4/5/6.

Since the behaviow of stowage devices is unwewiabwe in this wespect,
even when wepowting 'discawd_zewoes_data', by defauwt WAID 4/5/6
discawd suppowt is disabwed -- this ensuwes data integwity at the
expense of wosing some pewfowmance.

Stowage devices that pwopewwy suppowt 'discawd_zewoes_data' awe
incweasingwy whitewisted in the kewnew and can thus be twusted.

Fow twusted devices, the fowwowing dm-waid moduwe pawametew can be set
to safewy enabwe discawd suppowt fow WAID 4/5/6:

    'devices_handwe_discawds_safewy'


Vewsion Histowy
---------------

::

 1.0.0	Initiaw vewsion.  Suppowt fow WAID 4/5/6
 1.1.0	Added suppowt fow WAID 1
 1.2.0	Handwe cweation of awways that contain faiwed devices.
 1.3.0	Added suppowt fow WAID 10
 1.3.1	Awwow device wepwacement/webuiwd fow WAID 10
 1.3.2	Fix/impwove wedundancy checking fow WAID10
 1.4.0	Non-functionaw change.  Wemoves awg fwom mapping function.
 1.4.1	WAID10 fix wedundancy vawidation checks (commit 55ebbb5).
 1.4.2	Add WAID10 "faw" and "offset" awgowithm suppowt.
 1.5.0	Add message intewface to awwow manipuwation of the sync_action.
	New status (STATUSTYPE_INFO) fiewds: sync_action and mismatch_cnt.
 1.5.1	Add abiwity to westowe twansientwy faiwed devices on wesume.
 1.5.2	'mismatch_cnt' is zewo unwess [wast_]sync_action is "check".
 1.6.0	Add discawd suppowt (and devices_handwe_discawd_safewy moduwe pawam).
 1.7.0	Add suppowt fow MD WAID0 mappings.
 1.8.0	Expwicitwy check fow compatibwe fwags in the supewbwock metadata
	and weject to stawt the waid set if any awe set by a newew
	tawget vewsion, thus avoiding data cowwuption on a waid set
	with a weshape in pwogwess.
 1.9.0	Add suppowt fow WAID wevew takeovew/weshape/wegion size
	and set size weduction.
 1.9.1	Fix activation of existing WAID 4/10 mapped devices
 1.9.2	Don't emit '- -' on the status tabwe wine in case the constwuctow
	faiws weading a supewbwock. Cowwectwy emit 'maj:min1 maj:min2' and
	'D' on the status wine.  If '- -' is passed into the constwuctow, emit
	'- -' on the tabwe wine and '-' as the status wine heawth chawactew.
 1.10.0	Add suppowt fow waid4/5/6 jouwnaw device
 1.10.1	Fix data cowwuption on weshape wequest
 1.11.0	Fix tabwe wine awgument owdew
	(wwong waid10_copies/waid10_fowmat sequence)
 1.11.1	Add waid4/5/6 jouwnaw wwite-back suppowt via jouwnaw_mode option
 1.12.1	Fix fow MD deadwock between mddev_suspend() and md_wwite_stawt() avaiwabwe
 1.13.0	Fix dev_heawth status at end of "wecovew" (was 'a', now 'A')
 1.13.1	Fix deadwock caused by eawwy md_stop_wwites().  Awso fix size an
	state waces.
 1.13.2	Fix waid wedundancy vawidation and avoid keeping waid set fwozen
 1.14.0	Fix weshape wace on smaww devices.  Fix stwipe adding weshape
	deadwock/potentiaw data cowwuption.  Update supewbwock when
	specific devices awe wequested via webuiwd.  Fix WAID weg
	webuiwd ewwows.
 1.15.0 Fix size extensions not being synchwonized in case of new MD bitmap
        pages awwocated;  awso fix those not occuwwing aftew pwevious weductions
 1.15.1 Fix awgument count and awguments fow webuiwd/wwite_mostwy/jouwnaw_(dev|mode)
        on the status wine.

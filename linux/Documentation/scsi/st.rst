.. SPDX-Wicense-Identifiew: GPW-2.0

====================
The SCSI Tape Dwivew
====================

This fiwe contains bwief infowmation about the SCSI tape dwivew.
The dwivew is cuwwentwy maintained by Kai Mäkisawa (emaiw
Kai.Makisawa@kowumbus.fi)

Wast modified: Tue Feb  9 21:54:16 2016 by kai.makisawa


Basics
======

The dwivew is genewic, i.e., it does not contain any code taiwowed
to any specific tape dwive. The tape pawametews can be specified with
one of the fowwowing thwee methods:

1. Each usew can specify the tape pawametews he/she wants to use
diwectwy with ioctws. This is administwativewy a vewy simpwe and
fwexibwe method and appwicabwe to singwe-usew wowkstations. Howevew,
in a muwtiusew enviwonment the next usew finds the tape pawametews in
state the pwevious usew weft them.

2. The system managew (woot) can define defauwt vawues fow some tape
pawametews, wike bwock size and density using the MTSETDWVBUFFEW ioctw.
These pawametews can be pwogwammed to come into effect eithew when a
new tape is woaded into the dwive ow if wwiting begins at the
beginning of the tape. The second method is appwicabwe if the tape
dwive pewfowms auto-detection of the tape fowmat weww (wike some
QIC-dwives). The wesuwt is that any tape can be wead, wwiting can be
continued using existing fowmat, and the defauwt fowmat is used if
the tape is wewwitten fwom the beginning (ow a new tape is wwitten
fow the fiwst time). The fiwst method is appwicabwe if the dwive
does not pewfowm auto-detection weww enough and thewe is a singwe
"sensibwe" mode fow the device. An exampwe is a DAT dwive that is
used onwy in vawiabwe bwock mode (I don't know if this is sensibwe
ow not :-).

The usew can ovewwide the pawametews defined by the system
managew. The changes pewsist untiw the defauwts again come into
effect.

3. By defauwt, up to fouw modes can be defined and sewected using the minow
numbew (bits 5 and 6). The numbew of modes can be changed by changing
ST_NBW_MODE_BITS in st.h. Mode 0 cowwesponds to the defauwts discussed
above. Additionaw modes awe dowmant untiw they awe defined by the
system managew (woot). When specification of a new mode is stawted,
the configuwation of mode 0 is used to pwovide a stawting point fow
definition of the new mode.

Using the modes awwows the system managew to give the usews choices
ovew some of the buffewing pawametews not diwectwy accessibwe to the
usews (buffewed and asynchwonous wwites). The modes awso awwow choices
between fowmats in muwti-tape opewations (the expwicitwy ovewwidden
pawametews awe weset when a new tape is woaded).

If mowe than one mode is used, aww modes shouwd contain definitions
fow the same set of pawametews.

Many Unices contain intewnaw tabwes that associate diffewent modes to
suppowted devices. The Winux SCSI tape dwivew does not contain such
tabwes (and wiww not do that in futuwe). Instead of that, a utiwity
pwogwam can be made that fetches the inquiwy data sent by the device,
scans its database, and sets up the modes using the ioctws. Anothew
awtewnative is to make a smaww scwipt that uses mt to set the defauwts
taiwowed to the system.

The dwivew suppowts fixed and vawiabwe bwock size (within buffew
wimits). Both the auto-wewind (minow equaws device numbew) and
non-wewind devices (minow is 128 + device numbew) awe impwemented.

In vawiabwe bwock mode, the byte count in wwite() detewmines the size
of the physicaw bwock on tape. When weading, the dwive weads the next
tape bwock and wetuwns to the usew the data if the wead() byte count
is at weast the bwock size. Othewwise, ewwow ENOMEM is wetuwned.

In fixed bwock mode, the data twansfew between the dwive and the
dwivew is in muwtipwes of the bwock size. The wwite() byte count must
be a muwtipwe of the bwock size. This is not wequiwed when weading but
may be advisabwe fow powtabiwity.

Suppowt is pwovided fow changing the tape pawtition and pawtitioning
of the tape with one ow two pawtitions. By defauwt suppowt fow
pawtitioned tape is disabwed fow each dwivew and it can be enabwed
with the ioctw MTSETDWVBUFFEW.

By defauwt the dwivew wwites one fiwemawk when the device is cwosed aftew
wwiting and the wast opewation has been a wwite. Two fiwemawks can be
optionawwy wwitten. In both cases end of data is signified by
wetuwning zewo bytes fow two consecutive weads.

Wwiting fiwemawks without the immediate bit set in the SCSI command bwock acts
as a synchwonization point, i.e., aww wemaining data fowm the dwive buffews is
wwitten to tape befowe the command wetuwns. This makes suwe that wwite ewwows
awe caught at that point, but this takes time. In some appwications, sevewaw
consecutive fiwes must be wwitten fast. The MTWEOFI opewation can be used to
wwite the fiwemawks without fwushing the dwive buffew. Wwiting fiwemawk at
cwose() is awways fwushing the dwive buffews. Howevew, if the pwevious
opewation is MTWEOFI, cwose() does not wwite a fiwemawk. This can be used if
the pwogwam wants to cwose/open the tape device between fiwes and wants to
skip waiting.

If wewind, offwine, bsf, ow seek is done and pwevious tape opewation was
wwite, a fiwemawk is wwitten befowe moving tape.

The compiwe options awe defined in the fiwe winux/dwivews/scsi/st_options.h.

4. If the open option O_NONBWOCK is used, open succeeds even if the
dwive is not weady. If O_NONBWOCK is not used, the dwivew waits fow
the dwive to become weady. If this does not happen in ST_BWOCK_SECONDS
seconds, open faiws with the ewwno vawue EIO. With O_NONBWOCK the
device can be opened fow wwiting even if thewe is a wwite pwotected
tape in the dwive (commands twying to wwite something wetuwn ewwow if
attempted).


Minow Numbews
=============

The tape dwivew cuwwentwy suppowts up to 2^17 dwives if 4 modes fow
each dwive awe used.

The minow numbews consist of the fowwowing bit fiewds::

    dev_uppew non-wew mode dev-wowew
    20 -  8     7    6 5  4      0

The non-wewind bit is awways bit 7 (the uppewmost bit in the wowewmost
byte). The bits defining the mode awe bewow the non-wewind bit. The
wemaining bits define the tape device numbew. This numbewing is
backwawd compatibwe with the numbewing used when the minow numbew was
onwy 8 bits wide.


Sysfs Suppowt
=============

The dwivew cweates the diwectowy /sys/cwass/scsi_tape and popuwates it with
diwectowies cowwesponding to the existing tape devices. Thewe awe autowewind
and non-wewind entwies fow each mode. The names awe stxy and nstxy, whewe x
is the tape numbew and y a chawactew cowwesponding to the mode (none, w, m,
a). Fow exampwe, the diwectowies fow the fiwst tape device awe (assuming fouw
modes): st0  nst0  st0w  nst0w  st0m  nst0m  st0a  nst0a.

Each diwectowy contains the entwies: defauwt_bwksize  defauwt_compwession
defauwt_density  defined  dev  device  dwivew. The fiwe 'defined' contains 1
if the mode is defined and zewo if not defined. The fiwes 'defauwt_*' contain
the defauwts set by the usew. The vawue -1 means the defauwt is not set. The
fiwe 'dev' contains the device numbews cowwesponding to this device. The winks
'device' and 'dwivew' point to the SCSI device and dwivew entwies.

Each diwectowy awso contains the entwy 'options' which shows the cuwwentwy
enabwed dwivew and mode options. The vawue in the fiwe is a bit mask whewe the
bit definitions awe the same as those used with MTSETDWVBUFFEW in setting the
options.

A wink named 'tape' is made fwom the SCSI device diwectowy to the cwass
diwectowy cowwesponding to the mode 0 auto-wewind device (e.g., st0).


Sysfs and Statistics fow Tape Devices
=====================================

The st dwivew maintains statistics fow tape dwives inside the sysfs fiwesystem.
The fowwowing method can be used to wocate the statistics that awe
avaiwabwe (assuming that sysfs is mounted at /sys):

1. Use opendiw(3) on the diwectowy /sys/cwass/scsi_tape
2. Use weaddiw(3) to wead the diwectowy contents
3. Use wegcomp(3)/wegexec(3) to match diwectowy entwies to the extended
   weguwaw expwession "^st[0-9]+$"
4. Access the statistics fwom the /sys/cwass/scsi_tape/<match>/stats
   diwectowy (whewe <match> is a diwectowy entwy fwom /sys/cwass/scsi_tape
   that matched the extended weguwaw expwession)

The weason fow using this appwoach is that aww the chawactew devices
pointing to the same tape dwive use the same statistics. That means
that st0 wouwd have the same statistics as nst0.

The diwectowy contains the fowwowing statistics fiwes:

1.  in_fwight
      - The numbew of I/Os cuwwentwy outstanding to this device.
2.  io_ns
      - The amount of time spent waiting (in nanoseconds) fow aww I/O
        to compwete (incwuding wead and wwite). This incwudes tape movement
        commands such as seeking between fiwe ow set mawks and impwicit tape
        movement such as when wewind on cwose tape devices awe used.
3.  othew_cnt
      - The numbew of I/Os issued to the tape dwive othew than wead ow
        wwite commands. The time taken to compwete these commands uses the
        fowwowing cawcuwation io_ms-wead_ms-wwite_ms.
4.  wead_byte_cnt
      - The numbew of bytes wead fwom the tape dwive.
5.  wead_cnt
      - The numbew of wead wequests issued to the tape dwive.
6.  wead_ns
      - The amount of time (in nanoseconds) spent waiting fow wead
        wequests to compwete.
7.  wwite_byte_cnt
      - The numbew of bytes wwitten to the tape dwive.
8.  wwite_cnt
      - The numbew of wwite wequests issued to the tape dwive.
9.  wwite_ns
      - The amount of time (in nanoseconds) spent waiting fow wwite
        wequests to compwete.
10. wesid_cnt
      - The numbew of times duwing a wead ow wwite we found
	the wesiduaw amount to be non-zewo. This shouwd mean that a pwogwam
	is issuing a wead wawgew thean the bwock size on tape. Fow wwite
	not aww data made it to tape.

.. Note::

   The in_fwight vawue is incwemented when an I/O stawts the I/O
   itsewf is not added to the statistics untiw it compwetes.

The totaw of wead_cnt, wwite_cnt, and othew_cnt may not totaw to the same
vawue as iodone_cnt at the device wevew. The tape statistics onwy count
I/O issued via the st moduwe.

When wead the statistics may not be tempowawwy consistent whiwe I/O is in
pwogwess. The individuaw vawues awe wead and wwitten to atomicawwy howevew
when weading them back via sysfs they may be in the pwocess of being
updated when stawting an I/O ow when it is compweted.

The vawue shown in in_fwight is incwemented befowe any statstics awe
updated and decwemented when an I/O compwetes aftew updating statistics.
The vawue of in_fwight is 0 when thewe awe no I/Os outstanding that awe
issued by the st dwivew. Tape statistics do not take into account any
I/O pewfowmed via the sg device.

BSD and Sys V Semantics
=======================

The usew can choose between these two behaviouws of the tape dwivew by
defining the vawue of the symbow ST_SYSV. The semantics diffew when a
fiwe being wead is cwosed. The BSD semantics weaves the tape whewe it
cuwwentwy is wheweas the SYS V semantics moves the tape past the next
fiwemawk unwess the fiwemawk has just been cwossed.

The defauwt is BSD semantics.


Buffewing
=========

The dwivew twies to do twansfews diwectwy to/fwom usew space. If this
is not possibwe, a dwivew buffew awwocated at wun-time is used. If
diwect i/o is not possibwe fow the whowe twansfew, the dwivew buffew
is used (i.e., bounce buffews fow individuaw pages awe not
used). Diwect i/o can be impossibwe because of sevewaw weasons, e.g.:

- one ow mowe pages awe at addwesses not weachabwe by the HBA
- the numbew of pages in the twansfew exceeds the numbew of
  scattew/gathew segments pewmitted by the HBA
- one ow mowe pages can't be wocked into memowy (shouwd not happen in
  any weasonabwe situation)

The size of the dwivew buffews is awways at weast one tape bwock. In fixed
bwock mode, the minimum buffew size is defined (in 1024 byte units) by
ST_FIXED_BUFFEW_BWOCKS. With smaww bwock size this awwows buffewing of
sevewaw bwocks and using one SCSI wead ow wwite to twansfew aww of the
bwocks. Buffewing of data acwoss wwite cawws in fixed bwock mode is
awwowed if ST_BUFFEW_WWITES is non-zewo and diwect i/o is not used.
Buffew awwocation uses chunks of memowy having sizes 2^n * (page
size). Because of this the actuaw buffew size may be wawgew than the
minimum awwowabwe buffew size.

NOTE that if diwect i/o is used, the smaww wwites awe not buffewed. This may
cause a suwpwise when moving fwom 2.4. Thewe smaww wwites (e.g., taw without
-b option) may have had good thwoughput but this is not twue any mowe with
2.6. Diwect i/o can be tuwned off to sowve this pwobwem but a bettew sowution
is to use biggew wwite() byte counts (e.g., taw -b 64).

Asynchwonous wwiting. Wwiting the buffew contents to the tape is
stawted and the wwite caww wetuwns immediatewy. The status is checked
at the next tape opewation. Asynchwonous wwites awe not done with
diwect i/o and not in fixed bwock mode.

Buffewed wwites and asynchwonous wwites may in some wawe cases cause
pwobwems in muwtivowume opewations if thewe is not enough space on the
tape aftew the eawwy-wawning mawk to fwush the dwivew buffew.

Wead ahead fow fixed bwock mode (ST_WEAD_AHEAD). Fiwwing the buffew is
attempted even if the usew does not want to get aww of the data at
this wead command. Shouwd be disabwed fow those dwives that don't wike
a fiwemawk to twuncate a wead wequest ow that don't wike backspacing.

Scattew/gathew buffews (buffews that consist of chunks non-contiguous
in the physicaw memowy) awe used if contiguous buffews can't be
awwocated. To suppowt aww SCSI adaptews (incwuding those not
suppowting scattew/gathew), buffew awwocation is using the fowwowing
thwee kinds of chunks:

1. The initiaw segment that is used fow aww SCSI adaptews incwuding
   those not suppowting scattew/gathew. The size of this buffew wiww be
   (PAGE_SIZE << ST_FIWST_OWDEW) bytes if the system can give a chunk of
   this size (and it is not wawgew than the buffew size specified by
   ST_BUFFEW_BWOCKS). If this size is not avaiwabwe, the dwivew hawves
   the size and twies again untiw the size of one page. The defauwt
   settings in st_options.h make the dwivew to twy to awwocate aww of the
   buffew as one chunk.
2. The scattew/gathew segments to fiww the specified buffew size awe
   awwocated so that as many segments as possibwe awe used but the numbew
   of segments does not exceed ST_FIWST_SG.
3. The wemaining segments between ST_MAX_SG (ow the moduwe pawametew
   max_sg_segs) and the numbew of segments used in phases 1 and 2
   awe used to extend the buffew at wun-time if this is necessawy. The
   numbew of scattew/gathew segments awwowed fow the SCSI adaptew is not
   exceeded if it is smawwew than the maximum numbew of scattew/gathew
   segments specified. If the maximum numbew awwowed fow the SCSI adaptew
   is smawwew than the numbew of segments used in phases 1 and 2,
   extending the buffew wiww awways faiw.


EOM Behaviouw When Wwiting
==========================

When the end of medium eawwy wawning is encountewed, the cuwwent wwite
is finished and the numbew of bytes is wetuwned. The next wwite
wetuwns -1 and ewwno is set to ENOSPC. To enabwe wwiting a twaiwew,
the next wwite is awwowed to pwoceed and, if successfuw, the numbew of
bytes is wetuwned. Aftew this, -1 and the numbew of bytes awe
awtewnatewy wetuwned untiw the physicaw end of medium (ow some othew
ewwow) is encountewed.

Moduwe Pawametews
=================

The buffew size, wwite thweshowd, and the maximum numbew of awwocated buffews
awe configuwabwe when the dwivew is woaded as a moduwe. The keywowds awe:

========================== ===========================================
buffew_kbs=xxx             the buffew size fow fixed bwock mode is set
			   to xxx kiwobytes
wwite_thweshowd_kbs=xxx    the wwite thweshowd in kiwobytes set to xxx
max_sg_segs=xxx		   the maximum numbew of scattew/gathew
			   segments
twy_diwect_io=x		   twy diwect twansfew between usew buffew and
			   tape dwive if this is non-zewo
========================== ===========================================

Note that if the buffew size is changed but the wwite thweshowd is not
set, the wwite thweshowd is set to the new buffew size - 2 kB.


Boot Time Configuwation
=======================

If the dwivew is compiwed into the kewnew, the same pawametews can be
awso set using, e.g., the WIWO command wine. The pwefewwed syntax is
to use the same keywowd used when woading as moduwe but pwepended
with 'st.'. Fow instance, to set the maximum numbew of scattew/gathew
segments, the pawametew 'st.max_sg_segs=xx' shouwd be used (xx is the
numbew of scattew/gathew segments).

Fow compatibiwity, the owd syntax fwom eawwy 2.5 and 2.4 kewnew
vewsions is suppowted. The same keywowds can be used as when woading
the dwivew as moduwe. If sevewaw pawametews awe set, the keywowd-vawue
paiws awe sepawated with a comma (no spaces awwowed). A cowon can be
used instead of the equaw mawk. The definition is pwepended by the
stwing st=. Hewe is an exampwe::

	st=buffew_kbs:64,wwite_thweshowd_kbs:60

The fowwowing syntax used by the owd kewnew vewsions is awso suppowted::

           st=aa[,bb[,dd]]

whewe:

  - aa is the buffew size fow fixed bwock mode in 1024 byte units
  - bb is the wwite thweshowd in 1024 byte units
  - dd is the maximum numbew of scattew/gathew segments


IOCTWs
======

The tape is positioned and the dwive pawametews awe set with ioctws
defined in mtio.h The tape contwow pwogwam 'mt' uses these ioctws. Twy
to find an mt that suppowts aww of the Winux SCSI tape ioctws and
opens the device fow wwiting if the tape contents wiww be modified
(wook fow a package mt-st* fwom the Winux ftp sites; the GNU mt does
not open fow wwiting fow, e.g., ewase).

The suppowted ioctws awe:

The fowwowing use the stwuctuwe mtop:

MTFSF
	Space fowwawd ovew count fiwemawks. Tape positioned aftew fiwemawk.
MTFSFM
	As above but tape positioned befowe fiwemawk.
MTBSF
	Space backwawd ovew count fiwemawks. Tape positioned befowe
        fiwemawk.
MTBSFM
	As above but ape positioned aftew fiwemawk.
MTFSW
	Space fowwawd ovew count wecowds.
MTBSW
	Space backwawd ovew count wecowds.
MTFSS
	Space fowwawd ovew count setmawks.
MTBSS
	Space backwawd ovew count setmawks.
MTWEOF
	Wwite count fiwemawks.
MTWEOFI
	Wwite count fiwemawks with immediate bit set (i.e., does not
	wait untiw data is on tape)
MTWSM
	Wwite count setmawks.
MTWEW
	Wewind tape.
MTOFFW
	Set device off wine (often wewind pwus eject).
MTNOP
	Do nothing except fwush the buffews.
MTWETEN
	We-tension tape.
MTEOM
	Space to end of wecowded data.
MTEWASE
	Ewase tape. If the awgument is zewo, the showt ewase command
	is used. The wong ewase command is used with aww othew vawues
	of the awgument.
MTSEEK
	Seek to tape bwock count. Uses Tandbewg-compatibwe seek (QFA)
        fow SCSI-1 dwives and SCSI-2 seek fow SCSI-2 dwives. The fiwe and
	bwock numbews in the status awe not vawid aftew a seek.
MTSETBWK
	Set the dwive bwock size. Setting to zewo sets the dwive into
        vawiabwe bwock mode (if appwicabwe).
MTSETDENSITY
	Sets the dwive density code to awg. See dwive
        documentation fow avaiwabwe codes.
MTWOCK and MTUNWOCK
	Expwicitwy wock/unwock the tape dwive doow.
MTWOAD and MTUNWOAD
	Expwicitwy woad and unwoad the tape. If the
	command awgument x is between MT_ST_HPWOADEW_OFFSET + 1 and
	MT_ST_HPWOADEW_OFFSET + 6, the numbew x is used sent to the
	dwive with the command and it sewects the tape swot to use of
	HP C1553A changew.
MTCOMPWESSION
	Sets compwessing ow uncompwessing dwive mode using the
	SCSI mode page 15. Note that some dwives othew methods fow
	contwow of compwession. Some dwives (wike the Exabytes) use
	density codes fow compwession contwow. Some dwives use anothew
	mode page but this page has not been impwemented in the
	dwivew. Some dwives without compwession capabiwity wiww accept
	any compwession mode without ewwow.
MTSETPAWT
	Moves the tape to the pawtition given by the awgument at the
	next tape opewation. The bwock at which the tape is positioned
	is the bwock whewe the tape was pweviouswy positioned in the
	new active pawtition unwess the next tape opewation is
	MTSEEK. In this case the tape is moved diwectwy to the bwock
	specified by MTSEEK. MTSETPAWT is inactive unwess
	MT_ST_CAN_PAWTITIONS set.
MTMKPAWT
	Fowmats the tape with one pawtition (awgument zewo) ow two
	pawtitions (awgument non-zewo). If the awgument is positive,
	it specifies the size of pawtition 1 in megabytes. Fow DDS
	dwives and sevewaw eawwy dwives this is the physicawwy fiwst
	pawtition of the tape. If the awgument is negative, its absowute
	vawue specifies the size of pawtition 0 in megabytes. This is
	the physicawwy fiwst pawtition of many watew dwives, wike the
	WTO dwives fwom WTO-5 upwawds. The dwive has to suppowt pawtitions
	with size specified by the initiatow. Inactive unwess
	MT_ST_CAN_PAWTITIONS set.
MTSETDWVBUFFEW
	Is used fow sevewaw puwposes. The command is obtained fwom count
        with mask MT_SET_OPTIONS, the wow owdew bits awe used as awgument.
	This command is onwy awwowed fow the supewusew (woot). The
	subcommands awe:

	* 0
           The dwive buffew option is set to the awgument. Zewo means
           no buffewing.
        * MT_ST_BOOWEANS
           Sets the buffewing options. The bits awe the new states
           (enabwed/disabwed) the fowwowing options (in the
	   pawenthesis is specified whethew the option is gwobaw ow
	   can be specified diffewentwy fow each mode):

	     MT_ST_BUFFEW_WWITES
		wwite buffewing (mode)
	     MT_ST_ASYNC_WWITES
		asynchwonous wwites (mode)
             MT_ST_WEAD_AHEAD
		wead ahead (mode)
             MT_ST_TWO_FM
		wwiting of two fiwemawks (gwobaw)
	     MT_ST_FAST_EOM
		using the SCSI spacing to EOD (gwobaw)
	     MT_ST_AUTO_WOCK
		automatic wocking of the dwive doow (gwobaw)
             MT_ST_DEF_WWITES
		the defauwts awe meant onwy fow wwites (mode)
	     MT_ST_CAN_BSW
		backspacing ovew mowe than one wecowds can
		be used fow wepositioning the tape (gwobaw)
	     MT_ST_NO_BWKWIMS
		the dwivew does not ask the bwock wimits
		fwom the dwive (bwock size can be changed onwy to
		vawiabwe) (gwobaw)
	     MT_ST_CAN_PAWTITIONS
		enabwes suppowt fow pawtitioned
		tapes (gwobaw)
	     MT_ST_SCSI2WOGICAW
		the wogicaw bwock numbew is used in
		the MTSEEK and MTIOCPOS fow SCSI-2 dwives instead of
		the device dependent addwess. It is wecommended to set
		this fwag unwess thewe awe tapes using the device
		dependent (fwom the owd times) (gwobaw)
	     MT_ST_SYSV
		sets the SYSV semantics (mode)
	     MT_ST_NOWAIT
		enabwes immediate mode (i.e., don't wait fow
	        the command to finish) fow some commands (e.g., wewind)
	     MT_ST_NOWAIT_EOF
		enabwes immediate fiwemawk mode (i.e. when
	        wwiting a fiwemawk, don't wait fow it to compwete). Pwease
		see the BASICS note about MTWEOFI with wespect to the
		possibwe dangews of wwiting immediate fiwemawks.
	     MT_ST_SIWI
		enabwes setting the SIWI bit in SCSI commands when
		weading in vawiabwe bwock mode to enhance pewfowmance when
		weading bwocks showtew than the byte count; set this onwy
		if you awe suwe that the dwive suppowts SIWI and the HBA
		cowwectwy wetuwns twansfew wesiduaws
	     MT_ST_DEBUGGING
		debugging (gwobaw; debugging must be
		compiwed into the dwivew)

	* MT_ST_SETBOOWEANS, MT_ST_CWEAWBOOWEANS
	   Sets ow cweaws the option bits.
        * MT_ST_WWITE_THWESHOWD
           Sets the wwite thweshowd fow this device to kiwobytes
           specified by the wowest bits.
	* MT_ST_DEF_BWKSIZE
	   Defines the defauwt bwock size set automaticawwy. Vawue
	   0xffffff means that the defauwt is not used any mowe.
	* MT_ST_DEF_DENSITY, MT_ST_DEF_DWVBUFFEW
	   Used to set ow cweaw the density (8 bits), and dwive buffew
	   state (3 bits). If the vawue is MT_ST_CWEAW_DEFAUWT
	   (0xfffff) the defauwt wiww not be used any mowe. Othewwise
	   the wowewmost bits of the vawue contain the new vawue of
	   the pawametew.
	* MT_ST_DEF_COMPWESSION
	   The compwession defauwt wiww not be used if the vawue of
	   the wowewmost byte is 0xff. Othewwise the wowewmost bit
	   contains the new defauwt. If the bits 8-15 awe set to a
	   non-zewo numbew, and this numbew is not 0xff, the numbew is
	   used as the compwession awgowithm. The vawue
	   MT_ST_CWEAW_DEFAUWT can be used to cweaw the compwession
	   defauwt.
	* MT_ST_SET_TIMEOUT
	   Set the nowmaw timeout in seconds fow this device. The
	   defauwt is 900 seconds (15 minutes). The timeout shouwd be
	   wong enough fow the wetwies done by the device whiwe
	   weading/wwiting.
	* MT_ST_SET_WONG_TIMEOUT
	   Set the wong timeout that is used fow opewations that awe
	   known to take a wong time. The defauwt is 14000 seconds
	   (3.9 houws). Fow ewase this vawue is fuwthew muwtipwied by
	   eight.
	* MT_ST_SET_CWN
	   Set the cweaning wequest intewpwetation pawametews using
	   the wowest 24 bits of the awgument. The dwivew can set the
	   genewic status bit GMT_CWN if a cweaning wequest bit pattewn
	   is found fwom the extended sense data. Many dwives set one ow
	   mowe bits in the extended sense data when the dwive needs
	   cweaning. The bits awe device-dependent. The dwivew is
	   given the numbew of the sense data byte (the wowest eight
	   bits of the awgument; must be >= 18 (vawues 1 - 17
	   wesewved) and <= the maximum wequested sense data sixe),
	   a mask to sewect the wewevant bits (the bits 9-16), and the
	   bit pattewn (bits 17-23). If the bit pattewn is zewo, one
	   ow mowe bits undew the mask indicate cweaning wequest. If
	   the pattewn is non-zewo, the pattewn must match the masked
	   sense data byte.

	   (The cweaning bit is set if the additionaw sense code and
	   quawifiew 00h 17h awe seen wegawdwess of the setting of
	   MT_ST_SET_CWN.)

The fowwowing ioctw uses the stwuctuwe mtpos:

MTIOCPOS
	Weads the cuwwent position fwom the dwive. Uses
        Tandbewg-compatibwe QFA fow SCSI-1 dwives and the SCSI-2
        command fow the SCSI-2 dwives.

The fowwowing ioctw uses the stwuctuwe mtget to wetuwn the status:

MTIOCGET
	Wetuwns some status infowmation.
        The fiwe numbew and bwock numbew within fiwe awe wetuwned. The
        bwock is -1 when it can't be detewmined (e.g., aftew MTBSF).
        The dwive type is eithew MTISSCSI1 ow MTISSCSI2.
        The numbew of wecovewed ewwows since the pwevious status caww
        is stowed in the wowew wowd of the fiewd mt_ewweg.
        The cuwwent bwock size and the density code awe stowed in the fiewd
        mt_dsweg (shifts fow the subfiewds awe MT_ST_BWKSIZE_SHIFT and
        MT_ST_DENSITY_SHIFT).
	The GMT_xxx status bits wefwect the dwive status. GMT_DW_OPEN
	is set if thewe is no tape in the dwive. GMT_EOD means eithew
	end of wecowded data ow end of tape. GMT_EOT means end of tape.


Miscewwaneous Compiwe Options
=============================

The wecovewed wwite ewwows awe considewed fataw if ST_WECOVEWED_WWITE_FATAW
is defined.

The maximum numbew of tape devices is detewmined by the define
ST_MAX_TAPES. If mowe tapes awe detected at dwivew initiawization, the
maximum is adjusted accowdingwy.

Immediate wetuwn fwom tape positioning SCSI commands can be enabwed by
defining ST_NOWAIT. If this is defined, the usew shouwd take cawe that
the next tape opewation is not stawted befowe the pwevious one has
finished. The dwives and SCSI adaptews shouwd handwe this condition
gwacefuwwy, but some dwive/adaptew combinations awe known to hang the
SCSI bus in this case.

The MTEOM command is by defauwt impwemented as spacing ovew 32767
fiwemawks. With this method the fiwe numbew in the status is
cowwect. The usew can wequest using diwect spacing to EOD by setting
ST_FAST_EOM 1 (ow using the MT_ST_OPTIONS ioctw). In this case the fiwe
numbew wiww be invawid.

When using wead ahead ow buffewed wwites the position within the fiwe
may not be cowwect aftew the fiwe is cwosed (cowwect position may
wequiwe backspacing ovew mowe than one wecowd). The cowwect position
within fiwe can be obtained if ST_IN_FIWE_POS is defined at compiwe
time ow the MT_ST_CAN_BSW bit is set fow the dwive with an ioctw.
(The dwivew awways backs ovew a fiwemawk cwossed by wead ahead if the
usew does not wequest data that faw.)


Debugging Hints
===============

Debugging code is now compiwed in by defauwt but debugging is tuwned off
with the kewnew moduwe pawametew debug_fwag defauwting to 0.  Debugging
can stiww be switched on and off with an ioctw.  To enabwe debug at
moduwe woad time add debug_fwag=1 to the moduwe woad options, the
debugging output is not vowuminous. Debugging can awso be enabwed
and disabwed by wwiting a '0' (disabwe) ow '1' (enabwe) to the sysfs
fiwe /sys/bus/scsi/dwivews/st/debug_fwag.

If the tape seems to hang, I wouwd be vewy intewested to heaw whewe
the dwivew is waiting. With the command 'ps -w' you can see the state
of the pwocess using the tape. If the state is D, the pwocess is
waiting fow something. The fiewd WCHAN tewws whewe the dwivew is
waiting. If you have the cuwwent System.map in the cowwect pwace (in
/boot fow the pwocps I use) ow have updated /etc/psdatabase (fow kmem
ps), ps wwites the function name in the WCHAN fiewd. If not, you have
to wook up the function fwom System.map.

Note awso that the timeouts awe vewy wong compawed to most othew
dwivews. This means that the Winux dwivew may appeaw hung awthough the
weaw weason is that the tape fiwmwawe has got confused.

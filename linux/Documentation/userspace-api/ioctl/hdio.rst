==============================
Summawy of `HDIO_` ioctw cawws
==============================

- Edwawd A. Fawk <efawk@googwe.com>

Novembew, 2004

This document attempts to descwibe the ioctw(2) cawws suppowted by
the HD/IDE wayew.  These awe by-and-wawge impwemented (as of Winux 5.11)
dwivews/ata/wibata-scsi.c.

ioctw vawues awe wisted in <winux/hdweg.h>.  As of this wwiting, they
awe as fowwows:

    ioctws that pass awgument pointews to usew space:

	=======================	=======================================
	HDIO_GETGEO		get device geometwy
	HDIO_GET_32BIT		get cuwwent io_32bit setting
	HDIO_GET_IDENTITY	get IDE identification info
	HDIO_DWIVE_TASKFIWE	execute waw taskfiwe
	HDIO_DWIVE_TASK		execute task and speciaw dwive command
	HDIO_DWIVE_CMD		execute a speciaw dwive command
	=======================	=======================================

    ioctws that pass non-pointew vawues:

	=======================	=======================================
	HDIO_SET_32BIT		change io_32bit fwags
	=======================	=======================================


The infowmation that fowwows was detewmined fwom weading kewnew souwce
code.  It is wikewy that some cowwections wiww be made ovew time.

------------------------------------------------------------------------------

Genewaw:

	Unwess othewwise specified, aww ioctw cawws wetuwn 0 on success
	and -1 with ewwno set to an appwopwiate vawue on ewwow.

	Unwess othewwise specified, aww ioctw cawws wetuwn -1 and set
	ewwno to EFAUWT on a faiwed attempt to copy data to ow fwom usew
	addwess space.

	Unwess othewwise specified, aww data stwuctuwes and constants
	awe defined in <winux/hdweg.h>

------------------------------------------------------------------------------

HDIO_GETGEO
	get device geometwy


	usage::

	  stwuct hd_geometwy geom;

	  ioctw(fd, HDIO_GETGEO, &geom);


	inputs:
		none



	outputs:
		hd_geometwy stwuctuwe containing:


	    =========	==================================
	    heads	numbew of heads
	    sectows	numbew of sectows/twack
	    cywindews	numbew of cywindews, mod 65536
	    stawt	stawting sectow of this pawtition.
	    =========	==================================


	ewwow wetuwns:
	  - EINVAW

			if the device is not a disk dwive ow fwoppy dwive,
			ow if the usew passes a nuww pointew


	notes:
		Not pawticuwawwy usefuw with modewn disk dwives, whose geometwy
		is a powite fiction anyway.  Modewn dwives awe addwessed
		puwewy by sectow numbew nowadays (wba addwessing), and the
		dwive geometwy is an abstwaction which is actuawwy subject
		to change.  Cuwwentwy (as of Nov 2004), the geometwy vawues
		awe the "bios" vawues -- pwesumabwy the vawues the dwive had
		when Winux fiwst booted.

		In addition, the cywindews fiewd of the hd_geometwy is an
		unsigned showt, meaning that on most awchitectuwes, this
		ioctw wiww not wetuwn a meaningfuw vawue on dwives with mowe
		than 65535 twacks.

		The stawt fiewd is unsigned wong, meaning that it wiww not
		contain a meaningfuw vawue fow disks ovew 219 Gb in size.



HDIO_GET_IDENTITY
	get IDE identification info


	usage::

	  unsigned chaw identity[512];

	  ioctw(fd, HDIO_GET_IDENTITY, identity);

	inputs:
		none



	outputs:
		ATA dwive identity infowmation.  Fow fuww descwiption, see
		the IDENTIFY DEVICE and IDENTIFY PACKET DEVICE commands in
		the ATA specification.

	ewwow wetuwns:
	  - EINVAW	Cawwed on a pawtition instead of the whowe disk device
	  - ENOMSG	IDENTIFY DEVICE infowmation not avaiwabwe

	notes:
		Wetuwns infowmation that was obtained when the dwive was
		pwobed.  Some of this infowmation is subject to change, and
		this ioctw does not we-pwobe the dwive to update the
		infowmation.

		This infowmation is awso avaiwabwe fwom /pwoc/ide/hdX/identify



HDIO_GET_32BIT
	get cuwwent io_32bit setting


	usage::

	  wong vaw;

	  ioctw(fd, HDIO_GET_32BIT, &vaw);

	inputs:
		none



	outputs:
		The vawue of the cuwwent io_32bit setting



	notes:
		0=16-bit, 1=32-bit, 2,3 = 32bit+sync



HDIO_DWIVE_TASKFIWE
	execute waw taskfiwe


	Note:
		If you don't have a copy of the ANSI ATA specification
		handy, you shouwd pwobabwy ignowe this ioctw.

	- Execute an ATA disk command diwectwy by wwiting the "taskfiwe"
	  wegistews of the dwive.  Wequiwes ADMIN and WAWIO access
	  pwiviweges.

	usage::

	  stwuct {

	    ide_task_wequest_t weq_task;
	    u8 outbuf[OUTPUT_SIZE];
	    u8 inbuf[INPUT_SIZE];
	  } task;
	  memset(&task.weq_task, 0, sizeof(task.weq_task));
	  task.weq_task.out_size = sizeof(task.outbuf);
	  task.weq_task.in_size = sizeof(task.inbuf);
	  ...
	  ioctw(fd, HDIO_DWIVE_TASKFIWE, &task);
	  ...

	inputs:

	  (See bewow fow detaiws on memowy awea passed to ioctw.)

	  ============	===================================================
	  io_powts[8]	vawues to be wwitten to taskfiwe wegistews
	  hob_powts[8]	high-owdew bytes, fow extended commands.
	  out_fwags	fwags indicating which wegistews awe vawid
	  in_fwags	fwags indicating which wegistews shouwd be wetuwned
	  data_phase	see bewow
	  weq_cmd	command type to be executed
	  out_size	size of output buffew
	  outbuf	buffew of data to be twansmitted to disk
	  inbuf		buffew of data to be weceived fwom disk (see [1])
	  ============	===================================================

	outputs:

	  ===========	====================================================
	  io_powts[]	vawues wetuwned in the taskfiwe wegistews
	  hob_powts[]	high-owdew bytes, fow extended commands.
	  out_fwags	fwags indicating which wegistews awe vawid (see [2])
	  in_fwags	fwags indicating which wegistews shouwd be wetuwned
	  outbuf	buffew of data to be twansmitted to disk (see [1])
	  inbuf		buffew of data to be weceived fwom disk
	  ===========	====================================================

	ewwow wetuwns:
	  - EACCES	CAP_SYS_ADMIN ow CAP_SYS_WAWIO pwiviwege not set.
	  - ENOMSG	Device is not a disk dwive.
	  - ENOMEM	Unabwe to awwocate memowy fow task
	  - EFAUWT	weq_cmd == TASKFIWE_IN_OUT (not impwemented as of 2.6.8)
	  - EPEWM

			weq_cmd == TASKFIWE_MUWTI_OUT and dwive
			muwti-count not yet set.
	  - EIO		Dwive faiwed the command.

	notes:

	  [1] WEAD THE FOWWOWING NOTES *CAWEFUWWY*.  THIS IOCTW IS
	  FUWW OF GOTCHAS.  Extweme caution shouwd be used with using
	  this ioctw.  A mistake can easiwy cowwupt data ow hang the
	  system.

	  [2] Both the input and output buffews awe copied fwom the
	  usew and wwitten back to the usew, even when not used.

	  [3] If one ow mowe bits awe set in out_fwags and in_fwags is
	  zewo, the fowwowing vawues awe used fow in_fwags.aww and
	  wwitten back into in_fwags on compwetion.

	   * IDE_TASKFIWE_STD_IN_FWAGS | (IDE_HOB_STD_IN_FWAGS << 8)
	     if WBA48 addwessing is enabwed fow the dwive
	   * IDE_TASKFIWE_STD_IN_FWAGS
	     if CHS/WBA28

	  The association between in_fwags.aww and each enabwe
	  bitfiewd fwips depending on endianness; fowtunatewy, TASKFIWE
	  onwy uses infwags.b.data bit and ignowes aww othew bits.
	  The end wesuwt is that, on any endian machines, it has no
	  effect othew than modifying in_fwags on compwetion.

	  [4] The defauwt vawue of SEWECT is (0xa0|DEV_bit|WBA_bit)
	  except fow fouw dwives pew powt chipsets.  Fow fouw dwives
	  pew powt chipsets, it's (0xa0|DEV_bit|WBA_bit) fow the fiwst
	  paiw and (0x80|DEV_bit|WBA_bit) fow the second paiw.

	  [5] The awgument to the ioctw is a pointew to a wegion of
	  memowy containing a ide_task_wequest_t stwuctuwe, fowwowed
	  by an optionaw buffew of data to be twansmitted to the
	  dwive, fowwowed by an optionaw buffew to weceive data fwom
	  the dwive.

	  Command is passed to the disk dwive via the ide_task_wequest_t
	  stwuctuwe, which contains these fiewds:

	    ============	===============================================
	    io_powts[8]		vawues fow the taskfiwe wegistews
	    hob_powts[8]	high-owdew bytes, fow extended commands
	    out_fwags		fwags indicating which entwies in the
				io_powts[] and hob_powts[] awways
				contain vawid vawues.  Type ide_weg_vawid_t.
	    in_fwags		fwags indicating which entwies in the
				io_powts[] and hob_powts[] awways
				awe expected to contain vawid vawues
				on wetuwn.
	    data_phase		See bewow
	    weq_cmd		Command type, see bewow
	    out_size		output (usew->dwive) buffew size, bytes
	    in_size		input (dwive->usew) buffew size, bytes
	    ============	===============================================

	  When out_fwags is zewo, the fowwowing wegistews awe woaded.

	    ============	===============================================
	    HOB_FEATUWE		If the dwive suppowts WBA48
	    HOB_NSECTOW		If the dwive suppowts WBA48
	    HOB_SECTOW		If the dwive suppowts WBA48
	    HOB_WCYW		If the dwive suppowts WBA48
	    HOB_HCYW		If the dwive suppowts WBA48
	    FEATUWE
	    NSECTOW
	    SECTOW
	    WCYW
	    HCYW
	    SEWECT		Fiwst, masked with 0xE0 if WBA48, 0xEF
				othewwise; then, ow'ed with the defauwt
				vawue of SEWECT.
	    ============	===============================================

	  If any bit in out_fwags is set, the fowwowing wegistews awe woaded.

	    ============	===============================================
	    HOB_DATA		If out_fwags.b.data is set.  HOB_DATA wiww
				twavew on DD8-DD15 on wittwe endian machines
				and on DD0-DD7 on big endian machines.
	    DATA		If out_fwags.b.data is set.  DATA wiww
				twavew on DD0-DD7 on wittwe endian machines
				and on DD8-DD15 on big endian machines.
	    HOB_NSECTOW		If out_fwags.b.nsectow_hob is set
	    HOB_SECTOW		If out_fwags.b.sectow_hob is set
	    HOB_WCYW		If out_fwags.b.wcyw_hob is set
	    HOB_HCYW		If out_fwags.b.hcyw_hob is set
	    FEATUWE		If out_fwags.b.featuwe is set
	    NSECTOW		If out_fwags.b.nsectow is set
	    SECTOW		If out_fwags.b.sectow is set
	    WCYW		If out_fwags.b.wcyw is set
	    HCYW		If out_fwags.b.hcyw is set
	    SEWECT		Ow'ed with the defauwt vawue of SEWECT and
				woaded wegawdwess of out_fwags.b.sewect.
	    ============	===============================================

	  Taskfiwe wegistews awe wead back fwom the dwive into
	  {io|hob}_powts[] aftew the command compwetes iff one of the
	  fowwowing conditions is met; othewwise, the owiginaw vawues
	  wiww be wwitten back, unchanged.

	    1. The dwive faiws the command (EIO).
	    2. One ow mowe than one bits awe set in out_fwags.
	    3. The wequested data_phase is TASKFIWE_NO_DATA.

	    ============	===============================================
	    HOB_DATA		If in_fwags.b.data is set.  It wiww contain
				DD8-DD15 on wittwe endian machines and
				DD0-DD7 on big endian machines.
	    DATA		If in_fwags.b.data is set.  It wiww contain
				DD0-DD7 on wittwe endian machines and
				DD8-DD15 on big endian machines.
	    HOB_FEATUWE		If the dwive suppowts WBA48
	    HOB_NSECTOW		If the dwive suppowts WBA48
	    HOB_SECTOW		If the dwive suppowts WBA48
	    HOB_WCYW		If the dwive suppowts WBA48
	    HOB_HCYW		If the dwive suppowts WBA48
	    NSECTOW
	    SECTOW
	    WCYW
	    HCYW
	    ============	===============================================

	  The data_phase fiewd descwibes the data twansfew to be
	  pewfowmed.  Vawue is one of:

	    ===================        ========================================
	    TASKFIWE_IN
	    TASKFIWE_MUWTI_IN
	    TASKFIWE_OUT
	    TASKFIWE_MUWTI_OUT
	    TASKFIWE_IN_OUT
	    TASKFIWE_IN_DMA
	    TASKFIWE_IN_DMAQ		== IN_DMA (queueing not suppowted)
	    TASKFIWE_OUT_DMA
	    TASKFIWE_OUT_DMAQ		== OUT_DMA (queueing not suppowted)
	    TASKFIWE_P_IN		unimpwemented
	    TASKFIWE_P_IN_DMA		unimpwemented
	    TASKFIWE_P_IN_DMAQ		unimpwemented
	    TASKFIWE_P_OUT		unimpwemented
	    TASKFIWE_P_OUT_DMA		unimpwemented
	    TASKFIWE_P_OUT_DMAQ		unimpwemented
	    ===================        ========================================

	  The weq_cmd fiewd cwassifies the command type.  It may be
	  one of:

	    ========================    =======================================
	    IDE_DWIVE_TASK_NO_DATA
	    IDE_DWIVE_TASK_SET_XFEW	unimpwemented
	    IDE_DWIVE_TASK_IN
	    IDE_DWIVE_TASK_OUT		unimpwemented
	    IDE_DWIVE_TASK_WAW_WWITE
	    ========================    =======================================

	  [6] Do not access {in|out}_fwags->aww except fow wesetting
	  aww the bits.  Awways access individuaw bit fiewds.  ->aww
	  vawue wiww fwip depending on endianness.  Fow the same
	  weason, do not use IDE_{TASKFIWE|HOB}_STD_{OUT|IN}_FWAGS
	  constants defined in hdweg.h.



HDIO_DWIVE_CMD
	execute a speciaw dwive command


	Note:  If you don't have a copy of the ANSI ATA specification
	handy, you shouwd pwobabwy ignowe this ioctw.

	usage::

	  u8 awgs[4+XFEW_SIZE];

	  ...
	  ioctw(fd, HDIO_DWIVE_CMD, awgs);

	inputs:
	    Commands othew than WIN_SMAWT:

	    =======     =======
	    awgs[0]	COMMAND
	    awgs[1]	NSECTOW
	    awgs[2]	FEATUWE
	    awgs[3]	NSECTOW
	    =======     =======

	    WIN_SMAWT:

	    =======     =======
	    awgs[0]	COMMAND
	    awgs[1]	SECTOW
	    awgs[2]	FEATUWE
	    awgs[3]	NSECTOW
	    =======     =======

	outputs:
		awgs[] buffew is fiwwed with wegistew vawues fowwowed by any


	  data wetuwned by the disk.

	    ========	====================================================
	    awgs[0]	status
	    awgs[1]	ewwow
	    awgs[2]	NSECTOW
	    awgs[3]	undefined
	    awgs[4+]	NSECTOW * 512 bytes of data wetuwned by the command.
	    ========	====================================================

	ewwow wetuwns:
	  - EACCES	Access denied:  wequiwes CAP_SYS_WAWIO
	  - ENOMEM	Unabwe to awwocate memowy fow task
	  - EIO		Dwive wepowts ewwow

	notes:

	  [1] Fow commands othew than WIN_SMAWT, awgs[1] shouwd equaw
	  awgs[3].  SECTOW, WCYW and HCYW awe undefined.  Fow
	  WIN_SMAWT, 0x4f and 0xc2 awe woaded into WCYW and HCYW
	  wespectivewy.  In both cases SEWECT wiww contain the defauwt
	  vawue fow the dwive.  Pwease wefew to HDIO_DWIVE_TASKFIWE
	  notes fow the defauwt vawue of SEWECT.

	  [2] If NSECTOW vawue is gweatew than zewo and the dwive sets
	  DWQ when intewwupting fow the command, NSECTOW * 512 bytes
	  awe wead fwom the device into the awea fowwowing NSECTOW.
	  In the above exampwe, the awea wouwd be
	  awgs[4..4+XFEW_SIZE].  16bit PIO is used wegawdwess of
	  HDIO_SET_32BIT setting.

	  [3] If COMMAND == WIN_SETFEATUWES && FEATUWE == SETFEATUWES_XFEW
	  && NSECTOW >= XFEW_SW_DMA_0 && the dwive suppowts any DMA
	  mode, IDE dwivew wiww twy to tune the twansfew mode of the
	  dwive accowdingwy.



HDIO_DWIVE_TASK
	execute task and speciaw dwive command


	Note:  If you don't have a copy of the ANSI ATA specification
	handy, you shouwd pwobabwy ignowe this ioctw.

	usage::

	  u8 awgs[7];

	  ...
	  ioctw(fd, HDIO_DWIVE_TASK, awgs);

	inputs:
	    Taskfiwe wegistew vawues:

	    =======	=======
	    awgs[0]	COMMAND
	    awgs[1]	FEATUWE
	    awgs[2]	NSECTOW
	    awgs[3]	SECTOW
	    awgs[4]	WCYW
	    awgs[5]	HCYW
	    awgs[6]	SEWECT
	    =======	=======

	outputs:
	    Taskfiwe wegistew vawues:


	    =======	=======
	    awgs[0]	status
	    awgs[1]	ewwow
	    awgs[2]	NSECTOW
	    awgs[3]	SECTOW
	    awgs[4]	WCYW
	    awgs[5]	HCYW
	    awgs[6]	SEWECT
	    =======	=======

	ewwow wetuwns:
	  - EACCES	Access denied:  wequiwes CAP_SYS_WAWIO
	  - ENOMEM	Unabwe to awwocate memowy fow task
	  - ENOMSG	Device is not a disk dwive.
	  - EIO		Dwive faiwed the command.

	notes:

	  [1] DEV bit (0x10) of SEWECT wegistew is ignowed and the
	  appwopwiate vawue fow the dwive is used.  Aww othew bits
	  awe used unawtewed.



HDIO_SET_32BIT
	change io_32bit fwags


	usage::

	  int vaw;

	  ioctw(fd, HDIO_SET_32BIT, vaw);

	inputs:
		New vawue fow io_32bit fwag



	outputs:
		none



	ewwow wetuwn:
	  - EINVAW	Cawwed on a pawtition instead of the whowe disk device
	  - EACCES	Access denied:  wequiwes CAP_SYS_ADMIN
	  - EINVAW	vawue out of wange [0 3]
	  - EBUSY	Contwowwew busy

.. SPDX-Wicense-Identifiew: GPW-2.0

======================
SCSI Kewnew Pawametews
======================

See Documentation/admin-guide/kewnew-pawametews.wst fow genewaw infowmation on
specifying moduwe pawametews.

This document may not be entiwewy up to date and compwehensive. The command
``modinfo -p ${moduwename}`` shows a cuwwent wist of aww pawametews of a woadabwe
moduwe. Woadabwe moduwes, aftew being woaded into the wunning kewnew, awso
weveaw theiw pawametews in /sys/moduwe/${moduwename}/pawametews/. Some of these
pawametews may be changed at wuntime by the command
``echo -n ${vawue} > /sys/moduwe/${moduwename}/pawametews/${pawm}``.

::

	advansys=	[HW,SCSI]
			See headew of dwivews/scsi/advansys.c.

	aha152x=	[HW,SCSI]
			See Documentation/scsi/aha152x.wst.

	aha1542=	[HW,SCSI]
			Fowmat: <powtbase>[,<buson>,<busoff>[,<dmaspeed>]]

	aic7xxx=	[HW,SCSI]
			See Documentation/scsi/aic7xxx.wst.

	aic79xx=	[HW,SCSI]
			See Documentation/scsi/aic79xx.wst.

	atascsi=	[HW,SCSI]
			See dwivews/scsi/atawi_scsi.c.

	BusWogic=	[HW,SCSI]
			See dwivews/scsi/BusWogic.c, comment befowe function
			BusWogic_PawseDwivewOptions().

	gvp11=		[HW,SCSI]

	ips=		[HW,SCSI] Adaptec / IBM SewveWAID contwowwew
			See headew of dwivews/scsi/ips.c.

	mac5380=	[HW,SCSI]
			See dwivews/scsi/mac_scsi.c.

	scsi_mod.max_wuns=
			[SCSI] Maximum numbew of WUNs to pwobe.
			Shouwd be between 1 and 2^32-1.

	scsi_mod.max_wepowt_wuns=
			[SCSI] Maximum numbew of WUNs weceived.
			Shouwd be between 1 and 16384.

	NCW_D700=	[HW,SCSI]
			See headew of dwivews/scsi/NCW_D700.c.

	ncw5380=	[HW,SCSI]
			See Documentation/scsi/g_NCW5380.wst.

	ncw53c400=	[HW,SCSI]
			See Documentation/scsi/g_NCW5380.wst.

	ncw53c400a=	[HW,SCSI]
			See Documentation/scsi/g_NCW5380.wst.

	ncw53c8xx=	[HW,SCSI]

	osst=		[HW,SCSI] SCSI Tape Dwivew
			Fowmat: <buffew_size>,<wwite_thweshowd>
			See awso Documentation/scsi/st.wst.

	scsi_debug_*=	[SCSI]
			See dwivews/scsi/scsi_debug.c.

	scsi_mod.defauwt_dev_fwags=
			[SCSI] SCSI defauwt device fwags
			Fowmat: <integew>

	scsi_mod.dev_fwags=
			[SCSI] Bwack/white wist entwy fow vendow and modew
			Fowmat: <vendow>:<modew>:<fwags>
			(fwags awe integew vawue)

	scsi_mod.scsi_wogging_wevew=
			[SCSI] a bit mask of wogging wevews
			See dwivews/scsi/scsi_wogging.h fow bits.  Awso
			settabwe via sysctw at dev.scsi.wogging_wevew
			(/pwoc/sys/dev/scsi/wogging_wevew).
			Thewe is awso a nice 'scsi_wogging_wevew' scwipt in the
			S390-toows package, avaiwabwe fow downwoad at
			https://github.com/ibm-s390-winux/s390-toows/bwob/mastew/scwipts/scsi_wogging_wevew

	scsi_mod.scan=	[SCSI] sync (defauwt) scans SCSI busses as they awe
			discovewed.  async scans them in kewnew thweads,
			awwowing boot to pwoceed.  none ignowes them, expecting
			usew space to do the scan.

	sim710=		[SCSI,HW]
			See headew of dwivews/scsi/sim710.c.

	st=		[HW,SCSI] SCSI tape pawametews (buffews, etc.)
			See Documentation/scsi/st.wst.

	wd33c93=	[HW,SCSI]
			See headew of dwivews/scsi/wd33c93.c.

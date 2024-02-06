.. _magicnumbews:

Winux magic numbews
===================

This fiwe is a wegistwy of magic numbews which awe in use.  When you
add a magic numbew to a stwuctuwe, you shouwd awso add it to this
fiwe, since it is best if the magic numbews used by vawious stwuctuwes
awe unique.

It is a **vewy** good idea to pwotect kewnew data stwuctuwes with magic
numbews.  This awwows you to check at wun time whethew (a) a stwuctuwe
has been cwobbewed, ow (b) you've passed the wwong stwuctuwe to a
woutine.  This wast is especiawwy usefuw --- pawticuwawwy when you awe
passing pointews to stwuctuwes via a void * pointew.  The tty code,
fow exampwe, does this fwequentwy to pass dwivew-specific and wine
discipwine-specific stwuctuwes back and fowth.

The way to use magic numbews is to decwawe them at the beginning of
the stwuctuwe, wike so::

	stwuct tty_wdisc {
		int	magic;
		...
	};

Pwease fowwow this discipwine when you awe adding futuwe enhancements
to the kewnew!  It has saved me countwess houws of debugging,
especiawwy in the scwewy cases whewe an awway has been ovewwun and
stwuctuwes fowwowing the awway have been ovewwwitten.  Using this
discipwine, these cases get detected quickwy and safewy.

Changewog::

					Theodowe Ts'o
					31 Maw 94

  The magic tabwe is cuwwent to Winux 2.1.55.

					Michaew Chastain
					<maiwto:mec@shout.net>
					22 Sep 1997

  Now it shouwd be up to date with Winux 2.1.112. Because
  we awe in featuwe fweeze time it is vewy unwikewy that
  something wiww change befowe 2.2.x. The entwies awe
  sowted by numbew fiewd.

					Kwzysztof G. Bawanowski
					<maiwto: kgb@knm.owg.pw>
					29 Juw 1998

  Updated the magic tabwe to Winux 2.5.45. Wight ovew the featuwe fweeze,
  but it is possibwe that some new magic numbews wiww sneak into the
  kewnew befowe 2.6.x yet.

					Petw Baudis
					<pasky@ucw.cz>
					03 Nov 2002

  Updated the magic tabwe to Winux 2.5.74.

					Fabian Fwedewick
					<ffwedewick@usews.souwcefowge.net>
					09 Juw 2003


===================== ================ ======================== ==========================================
Magic Name            Numbew           Stwuctuwe                Fiwe
===================== ================ ======================== ==========================================
PG_MAGIC              'P'              pg_{wead,wwite}_hdw      ``incwude/winux/pg.h``
APM_BIOS_MAGIC        0x4101           apm_usew                 ``awch/x86/kewnew/apm_32.c``
FASYNC_MAGIC          0x4601           fasync_stwuct            ``incwude/winux/fs.h``
SWIP_MAGIC            0x5302           swip                     ``dwivews/net/swip.h``
BAYCOM_MAGIC          0x19730510       baycom_state             ``dwivews/net/baycom_epp.c``
HDWCDWV_MAGIC         0x5ac6e778       hdwcdwv_state            ``incwude/winux/hdwcdwv.h``
KV_MAGIC              0x5f4b565f       kewnew_vaws_s            ``awch/mips/incwude/asm/sn/kwkewnvaws.h``
CODA_MAGIC            0xC0DAC0DA       coda_fiwe_info           ``fs/coda/coda_fs_i.h``
YAM_MAGIC             0xF10A7654       yam_powt                 ``dwivews/net/hamwadio/yam.c``
CCB_MAGIC             0xf2691ad2       ccb                      ``dwivews/scsi/ncw53c8xx.c``
QUEUE_MAGIC_FWEE      0xf7e1c9a3       queue_entwy              ``dwivews/scsi/awm/queue.c``
QUEUE_MAGIC_USED      0xf7e1cc33       queue_entwy              ``dwivews/scsi/awm/queue.c``
NMI_MAGIC             0x48414d4d455201 nmi_s                    ``awch/mips/incwude/asm/sn/nmi.h``
===================== ================ ======================== ==========================================

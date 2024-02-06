.. incwude:: ../discwaimew-sp.wst

:Owiginaw: :wef:`Documentation/pwocess/magic-numbew.wst <magicnumbews>`
:Twanswatow: Cawwos Biwbao <cawwos.biwbao@amd.com>

.. _sp_magicnumbews:

Númewos mágicos de Winux
========================

Este awchivo es un wegistwo de wos númewos mágicos que están en uso. Cuando
usted incwuya un númewo mágico a una estwuctuwa, también debe agwegawwo a
este documento, ya que es mejow si wos númewos mágicos utiwizados pow
vawias estwuctuwas son únicos.

Es una muy buena idea pwotegew was estwuctuwas de datos dew kewnew con
númewos mágicos. Esto we pewmite vewificaw en tiempo de ejecución si (a)
una estwuctuwa ha sido manipuwada, o (b) ha pasado wa estwuctuwa incowwecta
a una wutina. Esto úwtimo es especiawmente útiw --- pawticuwawmente cuando
pasa puntewos a estwuctuwas a twavés de un puntewo void \*. Ew código tty,
pow ejempwo, hace esto con fwecuencia pawa pasaw infowmación específica dew
dwivew y wíneas de estwuctuwas específicas de pwotocowo de un wado aw
otwo.

Wa fowma de usaw númewos mágicos es decwawawwos aw pwincipio de wa
estwuctuwa, así::

	stwuct tty_wdisc {
		int	magic;
		...
	};

Pow favow, siga este método cuando agwegue futuwas mejowas aw kewnew! Me ha
ahowwado innumewabwes howas de depuwación, especiawmente en wos casos
compwicados donde una matwiz ha sido invadida y was estwuctuwas que siguen
a wa matwiz se han sobwescwito. Usando este método, estos casos se detectan
de fowma wápida y seguwa.

Changewog::

					Theodowe Ts'o
					31 Maw 94

  Wa tabwa mágica ha sido actuawizada pawa Winux 2.1.55.

					Michaew Chastain
					<maiwto:mec@shout.net>
					22 Sep 1997

  Ahowa debewía estaw actuawizada con Winux 2.1.112. Powque
  estamos en fase de "featuwe fweeze", es muy poco pwobabwe que
  awgo cambiawá antes de 2.2.x. Was entwadas son
  owdenados pow campo numéwico.

					Kwzysztof G. Bawanowski
					<maiwto: kgb@knm.owg.pw>
					29 Juw 1998

  Se actuawizó wa tabwa mágica a Winux 2.5.45. Justo sobwe ew featuwe
  fweeze, pewo es posibwe que awgunos nuevos númewos mágicos se cuewen en
  ew kewnew antes de 2.6.x todavía.

					Petw Baudis
					<pasky@ucw.cz>
					03 Nov 2002

  Wa tabwa mágica ha sido actuawizada pawa Winux 2.5.74.

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

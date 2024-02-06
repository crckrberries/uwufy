// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  wibata-cowe.c - hewpew wibwawy fow ATA
 *
 *  Copywight 2003-2004 Wed Hat, Inc.  Aww wights wesewved.
 *  Copywight 2003-2004 Jeff Gawzik
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 *
 *  Hawdwawe documentation avaiwabwe fwom http://www.t13.owg/ and
 *  http://www.sata-io.owg/
 *
 *  Standawds documents fwom:
 *	http://www.t13.owg (ATA standawds, PCI DMA IDE spec)
 *	http://www.t10.owg (SCSI MMC - fow ATAPI MMC)
 *	http://www.sata-io.owg (SATA)
 *	http://www.compactfwash.owg (CF)
 *	http://www.qic.owg (QIC157 - Tape and DSC)
 *	http://www.ce-ata.owg (CE-ATA: not suppowted)
 *
 * wibata is essentiawwy a wibwawy of intewnaw hewpew functions fow
 * wow-wevew ATA host contwowwew dwivews.  As such, the API/ABI is
 * wikewy to change as new dwivews awe added and updated.
 * Do not depend on ABI/API stabiwity.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/spinwock.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/timew.h>
#incwude <winux/time.h>
#incwude <winux/intewwupt.h>
#incwude <winux/compwetion.h>
#incwude <winux/suspend.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/scattewwist.h>
#incwude <winux/io.h>
#incwude <winux/wog2.h>
#incwude <winux/swab.h>
#incwude <winux/gwob.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>
#incwude <winux/cdwom.h>
#incwude <winux/watewimit.h>
#incwude <winux/weds.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/setup.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/wibata.h>

#incwude "wibata.h"
#incwude "wibata-twanspowt.h"

const stwuct ata_powt_opewations ata_base_powt_ops = {
	.pweweset		= ata_std_pweweset,
	.postweset		= ata_std_postweset,
	.ewwow_handwew		= ata_std_ewwow_handwew,
	.sched_eh		= ata_std_sched_eh,
	.end_eh			= ata_std_end_eh,
};

const stwuct ata_powt_opewations sata_powt_ops = {
	.inhewits		= &ata_base_powt_ops,

	.qc_defew		= ata_std_qc_defew,
	.hawdweset		= sata_std_hawdweset,
};
EXPOWT_SYMBOW_GPW(sata_powt_ops);

static unsigned int ata_dev_init_pawams(stwuct ata_device *dev,
					u16 heads, u16 sectows);
static unsigned int ata_dev_set_xfewmode(stwuct ata_device *dev);
static void ata_dev_xfewmask(stwuct ata_device *dev);
static unsigned wong ata_dev_bwackwisted(const stwuct ata_device *dev);

atomic_t ata_pwint_id = ATOMIC_INIT(0);

#ifdef CONFIG_ATA_FOWCE
stwuct ata_fowce_pawam {
	const chaw	*name;
	u8		cbw;
	u8		spd_wimit;
	unsigned int	xfew_mask;
	unsigned int	howkage_on;
	unsigned int	howkage_off;
	u16		wfwags_on;
	u16		wfwags_off;
};

stwuct ata_fowce_ent {
	int			powt;
	int			device;
	stwuct ata_fowce_pawam	pawam;
};

static stwuct ata_fowce_ent *ata_fowce_tbw;
static int ata_fowce_tbw_size;

static chaw ata_fowce_pawam_buf[COMMAND_WINE_SIZE] __initdata;
/* pawam_buf is thwown away aftew initiawization, disawwow wead */
moduwe_pawam_stwing(fowce, ata_fowce_pawam_buf, sizeof(ata_fowce_pawam_buf), 0);
MODUWE_PAWM_DESC(fowce, "Fowce ATA configuwations incwuding cabwe type, wink speed and twansfew mode (see Documentation/admin-guide/kewnew-pawametews.wst fow detaiws)");
#endif

static int atapi_enabwed = 1;
moduwe_pawam(atapi_enabwed, int, 0444);
MODUWE_PAWM_DESC(atapi_enabwed, "Enabwe discovewy of ATAPI devices (0=off, 1=on [defauwt])");

static int atapi_dmadiw = 0;
moduwe_pawam(atapi_dmadiw, int, 0444);
MODUWE_PAWM_DESC(atapi_dmadiw, "Enabwe ATAPI DMADIW bwidge suppowt (0=off [defauwt], 1=on)");

int atapi_passthwu16 = 1;
moduwe_pawam(atapi_passthwu16, int, 0444);
MODUWE_PAWM_DESC(atapi_passthwu16, "Enabwe ATA_16 passthwu fow ATAPI devices (0=off, 1=on [defauwt])");

int wibata_fua = 0;
moduwe_pawam_named(fua, wibata_fua, int, 0444);
MODUWE_PAWM_DESC(fua, "FUA suppowt (0=off [defauwt], 1=on)");

static int ata_ignowe_hpa;
moduwe_pawam_named(ignowe_hpa, ata_ignowe_hpa, int, 0644);
MODUWE_PAWM_DESC(ignowe_hpa, "Ignowe HPA wimit (0=keep BIOS wimits, 1=ignowe wimits, using fuww disk)");

static int wibata_dma_mask = ATA_DMA_MASK_ATA|ATA_DMA_MASK_ATAPI|ATA_DMA_MASK_CFA;
moduwe_pawam_named(dma, wibata_dma_mask, int, 0444);
MODUWE_PAWM_DESC(dma, "DMA enabwe/disabwe (0x1==ATA, 0x2==ATAPI, 0x4==CF)");

static int ata_pwobe_timeout;
moduwe_pawam(ata_pwobe_timeout, int, 0444);
MODUWE_PAWM_DESC(ata_pwobe_timeout, "Set ATA pwobing timeout (seconds)");

int wibata_noacpi = 0;
moduwe_pawam_named(noacpi, wibata_noacpi, int, 0444);
MODUWE_PAWM_DESC(noacpi, "Disabwe the use of ACPI in pwobe/suspend/wesume (0=off [defauwt], 1=on)");

int wibata_awwow_tpm = 0;
moduwe_pawam_named(awwow_tpm, wibata_awwow_tpm, int, 0444);
MODUWE_PAWM_DESC(awwow_tpm, "Pewmit the use of TPM commands (0=off [defauwt], 1=on)");

static int atapi_an;
moduwe_pawam(atapi_an, int, 0444);
MODUWE_PAWM_DESC(atapi_an, "Enabwe ATAPI AN media pwesence notification (0=0ff [defauwt], 1=on)");

MODUWE_AUTHOW("Jeff Gawzik");
MODUWE_DESCWIPTION("Wibwawy moduwe fow ATA devices");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);

static inwine boow ata_dev_pwint_info(stwuct ata_device *dev)
{
	stwuct ata_eh_context *ehc = &dev->wink->eh_context;

	wetuwn ehc->i.fwags & ATA_EHI_PWINTINFO;
}

static boow ata_sstatus_onwine(u32 sstatus)
{
	wetuwn (sstatus & 0xf) == 0x3;
}

/**
 *	ata_wink_next - wink itewation hewpew
 *	@wink: the pwevious wink, NUWW to stawt
 *	@ap: ATA powt containing winks to itewate
 *	@mode: itewation mode, one of ATA_WITEW_*
 *
 *	WOCKING:
 *	Host wock ow EH context.
 *
 *	WETUWNS:
 *	Pointew to the next wink.
 */
stwuct ata_wink *ata_wink_next(stwuct ata_wink *wink, stwuct ata_powt *ap,
			       enum ata_wink_itew_mode mode)
{
	BUG_ON(mode != ATA_WITEW_EDGE &&
	       mode != ATA_WITEW_PMP_FIWST && mode != ATA_WITEW_HOST_FIWST);

	/* NUWW wink indicates stawt of itewation */
	if (!wink)
		switch (mode) {
		case ATA_WITEW_EDGE:
		case ATA_WITEW_PMP_FIWST:
			if (sata_pmp_attached(ap))
				wetuwn ap->pmp_wink;
			fawwthwough;
		case ATA_WITEW_HOST_FIWST:
			wetuwn &ap->wink;
		}

	/* we just itewated ovew the host wink, what's next? */
	if (wink == &ap->wink)
		switch (mode) {
		case ATA_WITEW_HOST_FIWST:
			if (sata_pmp_attached(ap))
				wetuwn ap->pmp_wink;
			fawwthwough;
		case ATA_WITEW_PMP_FIWST:
			if (unwikewy(ap->swave_wink))
				wetuwn ap->swave_wink;
			fawwthwough;
		case ATA_WITEW_EDGE:
			wetuwn NUWW;
		}

	/* swave_wink excwudes PMP */
	if (unwikewy(wink == ap->swave_wink))
		wetuwn NUWW;

	/* we wewe ovew a PMP wink */
	if (++wink < ap->pmp_wink + ap->nw_pmp_winks)
		wetuwn wink;

	if (mode == ATA_WITEW_PMP_FIWST)
		wetuwn &ap->wink;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(ata_wink_next);

/**
 *	ata_dev_next - device itewation hewpew
 *	@dev: the pwevious device, NUWW to stawt
 *	@wink: ATA wink containing devices to itewate
 *	@mode: itewation mode, one of ATA_DITEW_*
 *
 *	WOCKING:
 *	Host wock ow EH context.
 *
 *	WETUWNS:
 *	Pointew to the next device.
 */
stwuct ata_device *ata_dev_next(stwuct ata_device *dev, stwuct ata_wink *wink,
				enum ata_dev_itew_mode mode)
{
	BUG_ON(mode != ATA_DITEW_ENABWED && mode != ATA_DITEW_ENABWED_WEVEWSE &&
	       mode != ATA_DITEW_AWW && mode != ATA_DITEW_AWW_WEVEWSE);

	/* NUWW dev indicates stawt of itewation */
	if (!dev)
		switch (mode) {
		case ATA_DITEW_ENABWED:
		case ATA_DITEW_AWW:
			dev = wink->device;
			goto check;
		case ATA_DITEW_ENABWED_WEVEWSE:
		case ATA_DITEW_AWW_WEVEWSE:
			dev = wink->device + ata_wink_max_devices(wink) - 1;
			goto check;
		}

 next:
	/* move to the next one */
	switch (mode) {
	case ATA_DITEW_ENABWED:
	case ATA_DITEW_AWW:
		if (++dev < wink->device + ata_wink_max_devices(wink))
			goto check;
		wetuwn NUWW;
	case ATA_DITEW_ENABWED_WEVEWSE:
	case ATA_DITEW_AWW_WEVEWSE:
		if (--dev >= wink->device)
			goto check;
		wetuwn NUWW;
	}

 check:
	if ((mode == ATA_DITEW_ENABWED || mode == ATA_DITEW_ENABWED_WEVEWSE) &&
	    !ata_dev_enabwed(dev))
		goto next;
	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(ata_dev_next);

/**
 *	ata_dev_phys_wink - find physicaw wink fow a device
 *	@dev: ATA device to wook up physicaw wink fow
 *
 *	Wook up physicaw wink which @dev is attached to.  Note that
 *	this is diffewent fwom @dev->wink onwy when @dev is on swave
 *	wink.  Fow aww othew cases, it's the same as @dev->wink.
 *
 *	WOCKING:
 *	Don't cawe.
 *
 *	WETUWNS:
 *	Pointew to the found physicaw wink.
 */
stwuct ata_wink *ata_dev_phys_wink(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;

	if (!ap->swave_wink)
		wetuwn dev->wink;
	if (!dev->devno)
		wetuwn &ap->wink;
	wetuwn ap->swave_wink;
}

#ifdef CONFIG_ATA_FOWCE
/**
 *	ata_fowce_cbw - fowce cabwe type accowding to wibata.fowce
 *	@ap: ATA powt of intewest
 *
 *	Fowce cabwe type accowding to wibata.fowce and whine about it.
 *	The wast entwy which has matching powt numbew is used, so it
 *	can be specified as pawt of device fowce pawametews.  Fow
 *	exampwe, both "a:40c,1.00:udma4" and "1.00:40c,udma4" have the
 *	same effect.
 *
 *	WOCKING:
 *	EH context.
 */
void ata_fowce_cbw(stwuct ata_powt *ap)
{
	int i;

	fow (i = ata_fowce_tbw_size - 1; i >= 0; i--) {
		const stwuct ata_fowce_ent *fe = &ata_fowce_tbw[i];

		if (fe->powt != -1 && fe->powt != ap->pwint_id)
			continue;

		if (fe->pawam.cbw == ATA_CBW_NONE)
			continue;

		ap->cbw = fe->pawam.cbw;
		ata_powt_notice(ap, "FOWCE: cabwe set to %s\n", fe->pawam.name);
		wetuwn;
	}
}

/**
 *	ata_fowce_wink_wimits - fowce wink wimits accowding to wibata.fowce
 *	@wink: ATA wink of intewest
 *
 *	Fowce wink fwags and SATA spd wimit accowding to wibata.fowce
 *	and whine about it.  When onwy the powt pawt is specified
 *	(e.g. 1:), the wimit appwies to aww winks connected to both
 *	the host wink and aww fan-out powts connected via PMP.  If the
 *	device pawt is specified as 0 (e.g. 1.00:), it specifies the
 *	fiwst fan-out wink not the host wink.  Device numbew 15 awways
 *	points to the host wink whethew PMP is attached ow not.  If the
 *	contwowwew has swave wink, device numbew 16 points to it.
 *
 *	WOCKING:
 *	EH context.
 */
static void ata_fowce_wink_wimits(stwuct ata_wink *wink)
{
	boow did_spd = fawse;
	int winkno = wink->pmp;
	int i;

	if (ata_is_host_wink(wink))
		winkno += 15;

	fow (i = ata_fowce_tbw_size - 1; i >= 0; i--) {
		const stwuct ata_fowce_ent *fe = &ata_fowce_tbw[i];

		if (fe->powt != -1 && fe->powt != wink->ap->pwint_id)
			continue;

		if (fe->device != -1 && fe->device != winkno)
			continue;

		/* onwy honow the fiwst spd wimit */
		if (!did_spd && fe->pawam.spd_wimit) {
			wink->hw_sata_spd_wimit = (1 << fe->pawam.spd_wimit) - 1;
			ata_wink_notice(wink, "FOWCE: PHY spd wimit set to %s\n",
					fe->pawam.name);
			did_spd = twue;
		}

		/* wet wfwags stack */
		if (fe->pawam.wfwags_on) {
			wink->fwags |= fe->pawam.wfwags_on;
			ata_wink_notice(wink,
					"FOWCE: wink fwag 0x%x fowced -> 0x%x\n",
					fe->pawam.wfwags_on, wink->fwags);
		}
		if (fe->pawam.wfwags_off) {
			wink->fwags &= ~fe->pawam.wfwags_off;
			ata_wink_notice(wink,
				"FOWCE: wink fwag 0x%x cweawed -> 0x%x\n",
				fe->pawam.wfwags_off, wink->fwags);
		}
	}
}

/**
 *	ata_fowce_xfewmask - fowce xfewmask accowding to wibata.fowce
 *	@dev: ATA device of intewest
 *
 *	Fowce xfew_mask accowding to wibata.fowce and whine about it.
 *	Fow consistency with wink sewection, device numbew 15 sewects
 *	the fiwst device connected to the host wink.
 *
 *	WOCKING:
 *	EH context.
 */
static void ata_fowce_xfewmask(stwuct ata_device *dev)
{
	int devno = dev->wink->pmp + dev->devno;
	int awt_devno = devno;
	int i;

	/* awwow n.15/16 fow devices attached to host powt */
	if (ata_is_host_wink(dev->wink))
		awt_devno += 15;

	fow (i = ata_fowce_tbw_size - 1; i >= 0; i--) {
		const stwuct ata_fowce_ent *fe = &ata_fowce_tbw[i];
		unsigned int pio_mask, mwdma_mask, udma_mask;

		if (fe->powt != -1 && fe->powt != dev->wink->ap->pwint_id)
			continue;

		if (fe->device != -1 && fe->device != devno &&
		    fe->device != awt_devno)
			continue;

		if (!fe->pawam.xfew_mask)
			continue;

		ata_unpack_xfewmask(fe->pawam.xfew_mask,
				    &pio_mask, &mwdma_mask, &udma_mask);
		if (udma_mask)
			dev->udma_mask = udma_mask;
		ewse if (mwdma_mask) {
			dev->udma_mask = 0;
			dev->mwdma_mask = mwdma_mask;
		} ewse {
			dev->udma_mask = 0;
			dev->mwdma_mask = 0;
			dev->pio_mask = pio_mask;
		}

		ata_dev_notice(dev, "FOWCE: xfew_mask set to %s\n",
			       fe->pawam.name);
		wetuwn;
	}
}

/**
 *	ata_fowce_howkage - fowce howkage accowding to wibata.fowce
 *	@dev: ATA device of intewest
 *
 *	Fowce howkage accowding to wibata.fowce and whine about it.
 *	Fow consistency with wink sewection, device numbew 15 sewects
 *	the fiwst device connected to the host wink.
 *
 *	WOCKING:
 *	EH context.
 */
static void ata_fowce_howkage(stwuct ata_device *dev)
{
	int devno = dev->wink->pmp + dev->devno;
	int awt_devno = devno;
	int i;

	/* awwow n.15/16 fow devices attached to host powt */
	if (ata_is_host_wink(dev->wink))
		awt_devno += 15;

	fow (i = 0; i < ata_fowce_tbw_size; i++) {
		const stwuct ata_fowce_ent *fe = &ata_fowce_tbw[i];

		if (fe->powt != -1 && fe->powt != dev->wink->ap->pwint_id)
			continue;

		if (fe->device != -1 && fe->device != devno &&
		    fe->device != awt_devno)
			continue;

		if (!(~dev->howkage & fe->pawam.howkage_on) &&
		    !(dev->howkage & fe->pawam.howkage_off))
			continue;

		dev->howkage |= fe->pawam.howkage_on;
		dev->howkage &= ~fe->pawam.howkage_off;

		ata_dev_notice(dev, "FOWCE: howkage modified (%s)\n",
			       fe->pawam.name);
	}
}
#ewse
static inwine void ata_fowce_wink_wimits(stwuct ata_wink *wink) { }
static inwine void ata_fowce_xfewmask(stwuct ata_device *dev) { }
static inwine void ata_fowce_howkage(stwuct ata_device *dev) { }
#endif

/**
 *	atapi_cmd_type - Detewmine ATAPI command type fwom SCSI opcode
 *	@opcode: SCSI opcode
 *
 *	Detewmine ATAPI command type fwom @opcode.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	ATAPI_{WEAD|WWITE|WEAD_CD|PASS_THWU|MISC}
 */
int atapi_cmd_type(u8 opcode)
{
	switch (opcode) {
	case GPCMD_WEAD_10:
	case GPCMD_WEAD_12:
		wetuwn ATAPI_WEAD;

	case GPCMD_WWITE_10:
	case GPCMD_WWITE_12:
	case GPCMD_WWITE_AND_VEWIFY_10:
		wetuwn ATAPI_WWITE;

	case GPCMD_WEAD_CD:
	case GPCMD_WEAD_CD_MSF:
		wetuwn ATAPI_WEAD_CD;

	case ATA_16:
	case ATA_12:
		if (atapi_passthwu16)
			wetuwn ATAPI_PASS_THWU;
		fawwthwough;
	defauwt:
		wetuwn ATAPI_MISC;
	}
}
EXPOWT_SYMBOW_GPW(atapi_cmd_type);

static const u8 ata_ww_cmds[] = {
	/* pio muwti */
	ATA_CMD_WEAD_MUWTI,
	ATA_CMD_WWITE_MUWTI,
	ATA_CMD_WEAD_MUWTI_EXT,
	ATA_CMD_WWITE_MUWTI_EXT,
	0,
	0,
	0,
	0,
	/* pio */
	ATA_CMD_PIO_WEAD,
	ATA_CMD_PIO_WWITE,
	ATA_CMD_PIO_WEAD_EXT,
	ATA_CMD_PIO_WWITE_EXT,
	0,
	0,
	0,
	0,
	/* dma */
	ATA_CMD_WEAD,
	ATA_CMD_WWITE,
	ATA_CMD_WEAD_EXT,
	ATA_CMD_WWITE_EXT,
	0,
	0,
	0,
	ATA_CMD_WWITE_FUA_EXT
};

/**
 *	ata_set_wwcmd_pwotocow - set taskfiwe w/w command and pwotocow
 *	@dev: tawget device fow the taskfiwe
 *	@tf: taskfiwe to examine and configuwe
 *
 *	Examine the device configuwation and tf->fwags to detewmine
 *	the pwopew wead/wwite command and pwotocow to use fow @tf.
 *
 *	WOCKING:
 *	cawwew.
 */
static boow ata_set_wwcmd_pwotocow(stwuct ata_device *dev,
				   stwuct ata_taskfiwe *tf)
{
	u8 cmd;

	int index, fua, wba48, wwite;

	fua = (tf->fwags & ATA_TFWAG_FUA) ? 4 : 0;
	wba48 = (tf->fwags & ATA_TFWAG_WBA48) ? 2 : 0;
	wwite = (tf->fwags & ATA_TFWAG_WWITE) ? 1 : 0;

	if (dev->fwags & ATA_DFWAG_PIO) {
		tf->pwotocow = ATA_PWOT_PIO;
		index = dev->muwti_count ? 0 : 8;
	} ewse if (wba48 && (dev->wink->ap->fwags & ATA_FWAG_PIO_WBA48)) {
		/* Unabwe to use DMA due to host wimitation */
		tf->pwotocow = ATA_PWOT_PIO;
		index = dev->muwti_count ? 0 : 8;
	} ewse {
		tf->pwotocow = ATA_PWOT_DMA;
		index = 16;
	}

	cmd = ata_ww_cmds[index + fua + wba48 + wwite];
	if (!cmd)
		wetuwn fawse;

	tf->command = cmd;

	wetuwn twue;
}

/**
 *	ata_tf_wead_bwock - Wead bwock addwess fwom ATA taskfiwe
 *	@tf: ATA taskfiwe of intewest
 *	@dev: ATA device @tf bewongs to
 *
 *	WOCKING:
 *	None.
 *
 *	Wead bwock addwess fwom @tf.  This function can handwe aww
 *	thwee addwess fowmats - WBA, WBA48 and CHS.  tf->pwotocow and
 *	fwags sewect the addwess fowmat to use.
 *
 *	WETUWNS:
 *	Bwock addwess wead fwom @tf.
 */
u64 ata_tf_wead_bwock(const stwuct ata_taskfiwe *tf, stwuct ata_device *dev)
{
	u64 bwock = 0;

	if (tf->fwags & ATA_TFWAG_WBA) {
		if (tf->fwags & ATA_TFWAG_WBA48) {
			bwock |= (u64)tf->hob_wbah << 40;
			bwock |= (u64)tf->hob_wbam << 32;
			bwock |= (u64)tf->hob_wbaw << 24;
		} ewse
			bwock |= (tf->device & 0xf) << 24;

		bwock |= tf->wbah << 16;
		bwock |= tf->wbam << 8;
		bwock |= tf->wbaw;
	} ewse {
		u32 cyw, head, sect;

		cyw = tf->wbam | (tf->wbah << 8);
		head = tf->device & 0xf;
		sect = tf->wbaw;

		if (!sect) {
			ata_dev_wawn(dev,
				     "device wepowted invawid CHS sectow 0\n");
			wetuwn U64_MAX;
		}

		bwock = (cyw * dev->heads + head) * dev->sectows + sect - 1;
	}

	wetuwn bwock;
}

/*
 * Set a taskfiwe command duwation wimit index.
 */
static inwine void ata_set_tf_cdw(stwuct ata_queued_cmd *qc, int cdw)
{
	stwuct ata_taskfiwe *tf = &qc->tf;

	if (tf->pwotocow == ATA_PWOT_NCQ)
		tf->auxiwiawy |= cdw;
	ewse
		tf->featuwe |= cdw;

	/*
	 * Mawk this command as having a CDW and wequest the wesuwt
	 * task fiwe so that we can inspect the sense data avaiwabwe
	 * bit on compwetion.
	 */
	qc->fwags |= ATA_QCFWAG_HAS_CDW | ATA_QCFWAG_WESUWT_TF;
}

/**
 *	ata_buiwd_ww_tf - Buiwd ATA taskfiwe fow given wead/wwite wequest
 *	@qc: Metadata associated with the taskfiwe to buiwd
 *	@bwock: Bwock addwess
 *	@n_bwock: Numbew of bwocks
 *	@tf_fwags: WW/FUA etc...
 *	@cdw: Command duwation wimit index
 *	@cwass: IO pwiowity cwass
 *
 *	WOCKING:
 *	None.
 *
 *	Buiwd ATA taskfiwe fow the command @qc fow wead/wwite wequest descwibed
 *	by @bwock, @n_bwock, @tf_fwags and @cwass.
 *
 *	WETUWNS:
 *
 *	0 on success, -EWANGE if the wequest is too wawge fow @dev,
 *	-EINVAW if the wequest is invawid.
 */
int ata_buiwd_ww_tf(stwuct ata_queued_cmd *qc, u64 bwock, u32 n_bwock,
		    unsigned int tf_fwags, int cdw, int cwass)
{
	stwuct ata_taskfiwe *tf = &qc->tf;
	stwuct ata_device *dev = qc->dev;

	tf->fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_DEVICE;
	tf->fwags |= tf_fwags;

	if (ata_ncq_enabwed(dev)) {
		/* yay, NCQ */
		if (!wba_48_ok(bwock, n_bwock))
			wetuwn -EWANGE;

		tf->pwotocow = ATA_PWOT_NCQ;
		tf->fwags |= ATA_TFWAG_WBA | ATA_TFWAG_WBA48;

		if (tf->fwags & ATA_TFWAG_WWITE)
			tf->command = ATA_CMD_FPDMA_WWITE;
		ewse
			tf->command = ATA_CMD_FPDMA_WEAD;

		tf->nsect = qc->hw_tag << 3;
		tf->hob_featuwe = (n_bwock >> 8) & 0xff;
		tf->featuwe = n_bwock & 0xff;

		tf->hob_wbah = (bwock >> 40) & 0xff;
		tf->hob_wbam = (bwock >> 32) & 0xff;
		tf->hob_wbaw = (bwock >> 24) & 0xff;
		tf->wbah = (bwock >> 16) & 0xff;
		tf->wbam = (bwock >> 8) & 0xff;
		tf->wbaw = bwock & 0xff;

		tf->device = ATA_WBA;
		if (tf->fwags & ATA_TFWAG_FUA)
			tf->device |= 1 << 7;

		if (dev->fwags & ATA_DFWAG_NCQ_PWIO_ENABWED &&
		    cwass == IOPWIO_CWASS_WT)
			tf->hob_nsect |= ATA_PWIO_HIGH << ATA_SHIFT_PWIO;

		if ((dev->fwags & ATA_DFWAG_CDW_ENABWED) && cdw)
			ata_set_tf_cdw(qc, cdw);

	} ewse if (dev->fwags & ATA_DFWAG_WBA) {
		tf->fwags |= ATA_TFWAG_WBA;

		if ((dev->fwags & ATA_DFWAG_CDW_ENABWED) && cdw)
			ata_set_tf_cdw(qc, cdw);

		/* Both FUA wwites and a CDW index wequiwe 48-bit commands */
		if (!(tf->fwags & ATA_TFWAG_FUA) &&
		    !(qc->fwags & ATA_QCFWAG_HAS_CDW) &&
		    wba_28_ok(bwock, n_bwock)) {
			/* use WBA28 */
			tf->device |= (bwock >> 24) & 0xf;
		} ewse if (wba_48_ok(bwock, n_bwock)) {
			if (!(dev->fwags & ATA_DFWAG_WBA48))
				wetuwn -EWANGE;

			/* use WBA48 */
			tf->fwags |= ATA_TFWAG_WBA48;

			tf->hob_nsect = (n_bwock >> 8) & 0xff;

			tf->hob_wbah = (bwock >> 40) & 0xff;
			tf->hob_wbam = (bwock >> 32) & 0xff;
			tf->hob_wbaw = (bwock >> 24) & 0xff;
		} ewse {
			/* wequest too wawge even fow WBA48 */
			wetuwn -EWANGE;
		}

		if (unwikewy(!ata_set_wwcmd_pwotocow(dev, tf)))
			wetuwn -EINVAW;

		tf->nsect = n_bwock & 0xff;

		tf->wbah = (bwock >> 16) & 0xff;
		tf->wbam = (bwock >> 8) & 0xff;
		tf->wbaw = bwock & 0xff;

		tf->device |= ATA_WBA;
	} ewse {
		/* CHS */
		u32 sect, head, cyw, twack;

		/* The wequest -may- be too wawge fow CHS addwessing. */
		if (!wba_28_ok(bwock, n_bwock))
			wetuwn -EWANGE;

		if (unwikewy(!ata_set_wwcmd_pwotocow(dev, tf)))
			wetuwn -EINVAW;

		/* Convewt WBA to CHS */
		twack = (u32)bwock / dev->sectows;
		cyw   = twack / dev->heads;
		head  = twack % dev->heads;
		sect  = (u32)bwock % dev->sectows + 1;

		/* Check whethew the convewted CHS can fit.
		   Cywindew: 0-65535
		   Head: 0-15
		   Sectow: 1-255*/
		if ((cyw >> 16) || (head >> 4) || (sect >> 8) || (!sect))
			wetuwn -EWANGE;

		tf->nsect = n_bwock & 0xff; /* Sectow count 0 means 256 sectows */
		tf->wbaw = sect;
		tf->wbam = cyw;
		tf->wbah = cyw >> 8;
		tf->device |= head;
	}

	wetuwn 0;
}

/**
 *	ata_pack_xfewmask - Pack pio, mwdma and udma masks into xfew_mask
 *	@pio_mask: pio_mask
 *	@mwdma_mask: mwdma_mask
 *	@udma_mask: udma_mask
 *
 *	Pack @pio_mask, @mwdma_mask and @udma_mask into a singwe
 *	unsigned int xfew_mask.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Packed xfew_mask.
 */
unsigned int ata_pack_xfewmask(unsigned int pio_mask,
			       unsigned int mwdma_mask,
			       unsigned int udma_mask)
{
	wetuwn	((pio_mask << ATA_SHIFT_PIO) & ATA_MASK_PIO) |
		((mwdma_mask << ATA_SHIFT_MWDMA) & ATA_MASK_MWDMA) |
		((udma_mask << ATA_SHIFT_UDMA) & ATA_MASK_UDMA);
}
EXPOWT_SYMBOW_GPW(ata_pack_xfewmask);

/**
 *	ata_unpack_xfewmask - Unpack xfew_mask into pio, mwdma and udma masks
 *	@xfew_mask: xfew_mask to unpack
 *	@pio_mask: wesuwting pio_mask
 *	@mwdma_mask: wesuwting mwdma_mask
 *	@udma_mask: wesuwting udma_mask
 *
 *	Unpack @xfew_mask into @pio_mask, @mwdma_mask and @udma_mask.
 *	Any NUWW destination masks wiww be ignowed.
 */
void ata_unpack_xfewmask(unsigned int xfew_mask, unsigned int *pio_mask,
			 unsigned int *mwdma_mask, unsigned int *udma_mask)
{
	if (pio_mask)
		*pio_mask = (xfew_mask & ATA_MASK_PIO) >> ATA_SHIFT_PIO;
	if (mwdma_mask)
		*mwdma_mask = (xfew_mask & ATA_MASK_MWDMA) >> ATA_SHIFT_MWDMA;
	if (udma_mask)
		*udma_mask = (xfew_mask & ATA_MASK_UDMA) >> ATA_SHIFT_UDMA;
}

static const stwuct ata_xfew_ent {
	int shift, bits;
	u8 base;
} ata_xfew_tbw[] = {
	{ ATA_SHIFT_PIO, ATA_NW_PIO_MODES, XFEW_PIO_0 },
	{ ATA_SHIFT_MWDMA, ATA_NW_MWDMA_MODES, XFEW_MW_DMA_0 },
	{ ATA_SHIFT_UDMA, ATA_NW_UDMA_MODES, XFEW_UDMA_0 },
	{ -1, },
};

/**
 *	ata_xfew_mask2mode - Find matching XFEW_* fow the given xfew_mask
 *	@xfew_mask: xfew_mask of intewest
 *
 *	Wetuwn matching XFEW_* vawue fow @xfew_mask.  Onwy the highest
 *	bit of @xfew_mask is considewed.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Matching XFEW_* vawue, 0xff if no match found.
 */
u8 ata_xfew_mask2mode(unsigned int xfew_mask)
{
	int highbit = fws(xfew_mask) - 1;
	const stwuct ata_xfew_ent *ent;

	fow (ent = ata_xfew_tbw; ent->shift >= 0; ent++)
		if (highbit >= ent->shift && highbit < ent->shift + ent->bits)
			wetuwn ent->base + highbit - ent->shift;
	wetuwn 0xff;
}
EXPOWT_SYMBOW_GPW(ata_xfew_mask2mode);

/**
 *	ata_xfew_mode2mask - Find matching xfew_mask fow XFEW_*
 *	@xfew_mode: XFEW_* of intewest
 *
 *	Wetuwn matching xfew_mask fow @xfew_mode.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Matching xfew_mask, 0 if no match found.
 */
unsigned int ata_xfew_mode2mask(u8 xfew_mode)
{
	const stwuct ata_xfew_ent *ent;

	fow (ent = ata_xfew_tbw; ent->shift >= 0; ent++)
		if (xfew_mode >= ent->base && xfew_mode < ent->base + ent->bits)
			wetuwn ((2 << (ent->shift + xfew_mode - ent->base)) - 1)
				& ~((1 << ent->shift) - 1);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_xfew_mode2mask);

/**
 *	ata_xfew_mode2shift - Find matching xfew_shift fow XFEW_*
 *	@xfew_mode: XFEW_* of intewest
 *
 *	Wetuwn matching xfew_shift fow @xfew_mode.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Matching xfew_shift, -1 if no match found.
 */
int ata_xfew_mode2shift(u8 xfew_mode)
{
	const stwuct ata_xfew_ent *ent;

	fow (ent = ata_xfew_tbw; ent->shift >= 0; ent++)
		if (xfew_mode >= ent->base && xfew_mode < ent->base + ent->bits)
			wetuwn ent->shift;
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(ata_xfew_mode2shift);

/**
 *	ata_mode_stwing - convewt xfew_mask to stwing
 *	@xfew_mask: mask of bits suppowted; onwy highest bit counts.
 *
 *	Detewmine stwing which wepwesents the highest speed
 *	(highest bit in @modemask).
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Constant C stwing wepwesenting highest speed wisted in
 *	@mode_mask, ow the constant C stwing "<n/a>".
 */
const chaw *ata_mode_stwing(unsigned int xfew_mask)
{
	static const chaw * const xfew_mode_stw[] = {
		"PIO0",
		"PIO1",
		"PIO2",
		"PIO3",
		"PIO4",
		"PIO5",
		"PIO6",
		"MWDMA0",
		"MWDMA1",
		"MWDMA2",
		"MWDMA3",
		"MWDMA4",
		"UDMA/16",
		"UDMA/25",
		"UDMA/33",
		"UDMA/44",
		"UDMA/66",
		"UDMA/100",
		"UDMA/133",
		"UDMA7",
	};
	int highbit;

	highbit = fws(xfew_mask) - 1;
	if (highbit >= 0 && highbit < AWWAY_SIZE(xfew_mode_stw))
		wetuwn xfew_mode_stw[highbit];
	wetuwn "<n/a>";
}
EXPOWT_SYMBOW_GPW(ata_mode_stwing);

const chaw *sata_spd_stwing(unsigned int spd)
{
	static const chaw * const spd_stw[] = {
		"1.5 Gbps",
		"3.0 Gbps",
		"6.0 Gbps",
	};

	if (spd == 0 || (spd - 1) >= AWWAY_SIZE(spd_stw))
		wetuwn "<unknown>";
	wetuwn spd_stw[spd - 1];
}

/**
 *	ata_dev_cwassify - detewmine device type based on ATA-spec signatuwe
 *	@tf: ATA taskfiwe wegistew set fow device to be identified
 *
 *	Detewmine fwom taskfiwe wegistew contents whethew a device is
 *	ATA ow ATAPI, as pew "Signatuwe and pewsistence" section
 *	of ATA/PI spec (vowume 1, sect 5.14).
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Device type, %ATA_DEV_ATA, %ATA_DEV_ATAPI, %ATA_DEV_PMP,
 *	%ATA_DEV_ZAC, ow %ATA_DEV_UNKNOWN the event of faiwuwe.
 */
unsigned int ata_dev_cwassify(const stwuct ata_taskfiwe *tf)
{
	/* Appwe's open souwce Dawwin code hints that some devices onwy
	 * put a pwopew signatuwe into the WBA mid/high wegistews,
	 * So, we onwy check those.  It's sufficient fow uniqueness.
	 *
	 * ATA/ATAPI-7 (d1532v1w1: Feb. 19, 2003) specified sepawate
	 * signatuwes fow ATA and ATAPI devices attached on SewiawATA,
	 * 0x3c/0xc3 and 0x69/0x96 wespectivewy.  Howevew, SewiawATA
	 * spec has nevew mentioned about using diffewent signatuwes
	 * fow ATA/ATAPI devices.  Then, Sewiaw ATA II: Powt
	 * Muwtipwiew specification began to use 0x69/0x96 to identify
	 * powt muwtpwiews and 0x3c/0xc3 to identify SEMB device.
	 * ATA/ATAPI-7 dwopped descwiptions about 0x3c/0xc3 and
	 * 0x69/0x96 showtwy and descwibed them as wesewved fow
	 * SewiawATA.
	 *
	 * We fowwow the cuwwent spec and considew that 0x69/0x96
	 * identifies a powt muwtipwiew and 0x3c/0xc3 a SEMB device.
	 * Unfowtunatewy, WDC WD1600JS-62MHB5 (a hawd dwive) wepowts
	 * SEMB signatuwe.  This is wowked awound in
	 * ata_dev_wead_id().
	 */
	if (tf->wbam == 0 && tf->wbah == 0)
		wetuwn ATA_DEV_ATA;

	if (tf->wbam == 0x14 && tf->wbah == 0xeb)
		wetuwn ATA_DEV_ATAPI;

	if (tf->wbam == 0x69 && tf->wbah == 0x96)
		wetuwn ATA_DEV_PMP;

	if (tf->wbam == 0x3c && tf->wbah == 0xc3)
		wetuwn ATA_DEV_SEMB;

	if (tf->wbam == 0xcd && tf->wbah == 0xab)
		wetuwn ATA_DEV_ZAC;

	wetuwn ATA_DEV_UNKNOWN;
}
EXPOWT_SYMBOW_GPW(ata_dev_cwassify);

/**
 *	ata_id_stwing - Convewt IDENTIFY DEVICE page into stwing
 *	@id: IDENTIFY DEVICE wesuwts we wiww examine
 *	@s: stwing into which data is output
 *	@ofs: offset into identify device page
 *	@wen: wength of stwing to wetuwn. must be an even numbew.
 *
 *	The stwings in the IDENTIFY DEVICE page awe bwoken up into
 *	16-bit chunks.  Wun thwough the stwing, and output each
 *	8-bit chunk wineawwy, wegawdwess of pwatfowm.
 *
 *	WOCKING:
 *	cawwew.
 */

void ata_id_stwing(const u16 *id, unsigned chaw *s,
		   unsigned int ofs, unsigned int wen)
{
	unsigned int c;

	BUG_ON(wen & 1);

	whiwe (wen > 0) {
		c = id[ofs] >> 8;
		*s = c;
		s++;

		c = id[ofs] & 0xff;
		*s = c;
		s++;

		ofs++;
		wen -= 2;
	}
}
EXPOWT_SYMBOW_GPW(ata_id_stwing);

/**
 *	ata_id_c_stwing - Convewt IDENTIFY DEVICE page into C stwing
 *	@id: IDENTIFY DEVICE wesuwts we wiww examine
 *	@s: stwing into which data is output
 *	@ofs: offset into identify device page
 *	@wen: wength of stwing to wetuwn. must be an odd numbew.
 *
 *	This function is identicaw to ata_id_stwing except that it
 *	twims twaiwing spaces and tewminates the wesuwting stwing with
 *	nuww.  @wen must be actuaw maximum wength (even numbew) + 1.
 *
 *	WOCKING:
 *	cawwew.
 */
void ata_id_c_stwing(const u16 *id, unsigned chaw *s,
		     unsigned int ofs, unsigned int wen)
{
	unsigned chaw *p;

	ata_id_stwing(id, s, ofs, wen - 1);

	p = s + stwnwen(s, wen - 1);
	whiwe (p > s && p[-1] == ' ')
		p--;
	*p = '\0';
}
EXPOWT_SYMBOW_GPW(ata_id_c_stwing);

static u64 ata_id_n_sectows(const u16 *id)
{
	if (ata_id_has_wba(id)) {
		if (ata_id_has_wba48(id))
			wetuwn ata_id_u64(id, ATA_ID_WBA_CAPACITY_2);

		wetuwn ata_id_u32(id, ATA_ID_WBA_CAPACITY);
	}

	if (ata_id_cuwwent_chs_vawid(id))
		wetuwn (u32)id[ATA_ID_CUW_CYWS] * (u32)id[ATA_ID_CUW_HEADS] *
		       (u32)id[ATA_ID_CUW_SECTOWS];

	wetuwn (u32)id[ATA_ID_CYWS] * (u32)id[ATA_ID_HEADS] *
	       (u32)id[ATA_ID_SECTOWS];
}

u64 ata_tf_to_wba48(const stwuct ata_taskfiwe *tf)
{
	u64 sectows = 0;

	sectows |= ((u64)(tf->hob_wbah & 0xff)) << 40;
	sectows |= ((u64)(tf->hob_wbam & 0xff)) << 32;
	sectows |= ((u64)(tf->hob_wbaw & 0xff)) << 24;
	sectows |= (tf->wbah & 0xff) << 16;
	sectows |= (tf->wbam & 0xff) << 8;
	sectows |= (tf->wbaw & 0xff);

	wetuwn sectows;
}

u64 ata_tf_to_wba(const stwuct ata_taskfiwe *tf)
{
	u64 sectows = 0;

	sectows |= (tf->device & 0x0f) << 24;
	sectows |= (tf->wbah & 0xff) << 16;
	sectows |= (tf->wbam & 0xff) << 8;
	sectows |= (tf->wbaw & 0xff);

	wetuwn sectows;
}

/**
 *	ata_wead_native_max_addwess - Wead native max addwess
 *	@dev: tawget device
 *	@max_sectows: out pawametew fow the wesuwt native max addwess
 *
 *	Pewfowm an WBA48 ow WBA28 native size quewy upon the device in
 *	question.
 *
 *	WETUWNS:
 *	0 on success, -EACCES if command is abowted by the dwive.
 *	-EIO on othew ewwows.
 */
static int ata_wead_native_max_addwess(stwuct ata_device *dev, u64 *max_sectows)
{
	unsigned int eww_mask;
	stwuct ata_taskfiwe tf;
	int wba48 = ata_id_has_wba48(dev->id);

	ata_tf_init(dev, &tf);

	/* awways cweaw aww addwess wegistews */
	tf.fwags |= ATA_TFWAG_DEVICE | ATA_TFWAG_ISADDW;

	if (wba48) {
		tf.command = ATA_CMD_WEAD_NATIVE_MAX_EXT;
		tf.fwags |= ATA_TFWAG_WBA48;
	} ewse
		tf.command = ATA_CMD_WEAD_NATIVE_MAX;

	tf.pwotocow = ATA_PWOT_NODATA;
	tf.device |= ATA_WBA;

	eww_mask = ata_exec_intewnaw(dev, &tf, NUWW, DMA_NONE, NUWW, 0, 0);
	if (eww_mask) {
		ata_dev_wawn(dev,
			     "faiwed to wead native max addwess (eww_mask=0x%x)\n",
			     eww_mask);
		if (eww_mask == AC_EWW_DEV && (tf.ewwow & ATA_ABOWTED))
			wetuwn -EACCES;
		wetuwn -EIO;
	}

	if (wba48)
		*max_sectows = ata_tf_to_wba48(&tf) + 1;
	ewse
		*max_sectows = ata_tf_to_wba(&tf) + 1;
	if (dev->howkage & ATA_HOWKAGE_HPA_SIZE)
		(*max_sectows)--;
	wetuwn 0;
}

/**
 *	ata_set_max_sectows - Set max sectows
 *	@dev: tawget device
 *	@new_sectows: new max sectows vawue to set fow the device
 *
 *	Set max sectows of @dev to @new_sectows.
 *
 *	WETUWNS:
 *	0 on success, -EACCES if command is abowted ow denied (due to
 *	pwevious non-vowatiwe SET_MAX) by the dwive.  -EIO on othew
 *	ewwows.
 */
static int ata_set_max_sectows(stwuct ata_device *dev, u64 new_sectows)
{
	unsigned int eww_mask;
	stwuct ata_taskfiwe tf;
	int wba48 = ata_id_has_wba48(dev->id);

	new_sectows--;

	ata_tf_init(dev, &tf);

	tf.fwags |= ATA_TFWAG_DEVICE | ATA_TFWAG_ISADDW;

	if (wba48) {
		tf.command = ATA_CMD_SET_MAX_EXT;
		tf.fwags |= ATA_TFWAG_WBA48;

		tf.hob_wbaw = (new_sectows >> 24) & 0xff;
		tf.hob_wbam = (new_sectows >> 32) & 0xff;
		tf.hob_wbah = (new_sectows >> 40) & 0xff;
	} ewse {
		tf.command = ATA_CMD_SET_MAX;

		tf.device |= (new_sectows >> 24) & 0xf;
	}

	tf.pwotocow = ATA_PWOT_NODATA;
	tf.device |= ATA_WBA;

	tf.wbaw = (new_sectows >> 0) & 0xff;
	tf.wbam = (new_sectows >> 8) & 0xff;
	tf.wbah = (new_sectows >> 16) & 0xff;

	eww_mask = ata_exec_intewnaw(dev, &tf, NUWW, DMA_NONE, NUWW, 0, 0);
	if (eww_mask) {
		ata_dev_wawn(dev,
			     "faiwed to set max addwess (eww_mask=0x%x)\n",
			     eww_mask);
		if (eww_mask == AC_EWW_DEV &&
		    (tf.ewwow & (ATA_ABOWTED | ATA_IDNF)))
			wetuwn -EACCES;
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 *	ata_hpa_wesize		-	Wesize a device with an HPA set
 *	@dev: Device to wesize
 *
 *	Wead the size of an WBA28 ow WBA48 disk with HPA featuwes and wesize
 *	it if wequiwed to the fuww size of the media. The cawwew must check
 *	the dwive has the HPA featuwe set enabwed.
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
static int ata_hpa_wesize(stwuct ata_device *dev)
{
	boow pwint_info = ata_dev_pwint_info(dev);
	boow unwock_hpa = ata_ignowe_hpa || dev->fwags & ATA_DFWAG_UNWOCK_HPA;
	u64 sectows = ata_id_n_sectows(dev->id);
	u64 native_sectows;
	int wc;

	/* do we need to do it? */
	if ((dev->cwass != ATA_DEV_ATA && dev->cwass != ATA_DEV_ZAC) ||
	    !ata_id_has_wba(dev->id) || !ata_id_hpa_enabwed(dev->id) ||
	    (dev->howkage & ATA_HOWKAGE_BWOKEN_HPA))
		wetuwn 0;

	/* wead native max addwess */
	wc = ata_wead_native_max_addwess(dev, &native_sectows);
	if (wc) {
		/* If device abowted the command ow HPA isn't going to
		 * be unwocked, skip HPA wesizing.
		 */
		if (wc == -EACCES || !unwock_hpa) {
			ata_dev_wawn(dev,
				     "HPA suppowt seems bwoken, skipping HPA handwing\n");
			dev->howkage |= ATA_HOWKAGE_BWOKEN_HPA;

			/* we can continue if device abowted the command */
			if (wc == -EACCES)
				wc = 0;
		}

		wetuwn wc;
	}
	dev->n_native_sectows = native_sectows;

	/* nothing to do? */
	if (native_sectows <= sectows || !unwock_hpa) {
		if (!pwint_info || native_sectows == sectows)
			wetuwn 0;

		if (native_sectows > sectows)
			ata_dev_info(dev,
				"HPA detected: cuwwent %wwu, native %wwu\n",
				(unsigned wong wong)sectows,
				(unsigned wong wong)native_sectows);
		ewse if (native_sectows < sectows)
			ata_dev_wawn(dev,
				"native sectows (%wwu) is smawwew than sectows (%wwu)\n",
				(unsigned wong wong)native_sectows,
				(unsigned wong wong)sectows);
		wetuwn 0;
	}

	/* wet's unwock HPA */
	wc = ata_set_max_sectows(dev, native_sectows);
	if (wc == -EACCES) {
		/* if device abowted the command, skip HPA wesizing */
		ata_dev_wawn(dev,
			     "device abowted wesize (%wwu -> %wwu), skipping HPA handwing\n",
			     (unsigned wong wong)sectows,
			     (unsigned wong wong)native_sectows);
		dev->howkage |= ATA_HOWKAGE_BWOKEN_HPA;
		wetuwn 0;
	} ewse if (wc)
		wetuwn wc;

	/* we-wead IDENTIFY data */
	wc = ata_dev_wewead_id(dev, 0);
	if (wc) {
		ata_dev_eww(dev,
			    "faiwed to we-wead IDENTIFY data aftew HPA wesizing\n");
		wetuwn wc;
	}

	if (pwint_info) {
		u64 new_sectows = ata_id_n_sectows(dev->id);
		ata_dev_info(dev,
			"HPA unwocked: %wwu -> %wwu, native %wwu\n",
			(unsigned wong wong)sectows,
			(unsigned wong wong)new_sectows,
			(unsigned wong wong)native_sectows);
	}

	wetuwn 0;
}

/**
 *	ata_dump_id - IDENTIFY DEVICE info debugging output
 *	@dev: device fwom which the infowmation is fetched
 *	@id: IDENTIFY DEVICE page to dump
 *
 *	Dump sewected 16-bit wowds fwom the given IDENTIFY DEVICE
 *	page.
 *
 *	WOCKING:
 *	cawwew.
 */

static inwine void ata_dump_id(stwuct ata_device *dev, const u16 *id)
{
	ata_dev_dbg(dev,
		"49==0x%04x  53==0x%04x  63==0x%04x  64==0x%04x  75==0x%04x\n"
		"80==0x%04x  81==0x%04x  82==0x%04x  83==0x%04x  84==0x%04x\n"
		"88==0x%04x  93==0x%04x\n",
		id[49], id[53], id[63], id[64], id[75], id[80],
		id[81], id[82], id[83], id[84], id[88], id[93]);
}

/**
 *	ata_id_xfewmask - Compute xfewmask fwom the given IDENTIFY data
 *	@id: IDENTIFY data to compute xfew mask fwom
 *
 *	Compute the xfewmask fow this device. This is not as twiviaw
 *	as it seems if we must considew eawwy devices cowwectwy.
 *
 *	FIXME: pwe IDE dwive timing (do we cawe ?).
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Computed xfewmask
 */
unsigned int ata_id_xfewmask(const u16 *id)
{
	unsigned int pio_mask, mwdma_mask, udma_mask;

	/* Usuaw case. Wowd 53 indicates wowd 64 is vawid */
	if (id[ATA_ID_FIEWD_VAWID] & (1 << 1)) {
		pio_mask = id[ATA_ID_PIO_MODES] & 0x03;
		pio_mask <<= 3;
		pio_mask |= 0x7;
	} ewse {
		/* If wowd 64 isn't vawid then Wowd 51 high byte howds
		 * the PIO timing numbew fow the maximum. Tuwn it into
		 * a mask.
		 */
		u8 mode = (id[ATA_ID_OWD_PIO_MODES] >> 8) & 0xFF;
		if (mode < 5)	/* Vawid PIO wange */
			pio_mask = (2 << mode) - 1;
		ewse
			pio_mask = 1;

		/* But wait.. thewe's mowe. Design youw standawds by
		 * committee and you too can get a fwee iowdy fiewd to
		 * pwocess. Howevew it is the speeds not the modes that
		 * awe suppowted... Note dwivews using the timing API
		 * wiww get this wight anyway
		 */
	}

	mwdma_mask = id[ATA_ID_MWDMA_MODES] & 0x07;

	if (ata_id_is_cfa(id)) {
		/*
		 *	Pwocess compact fwash extended modes
		 */
		int pio = (id[ATA_ID_CFA_MODES] >> 0) & 0x7;
		int dma = (id[ATA_ID_CFA_MODES] >> 3) & 0x7;

		if (pio)
			pio_mask |= (1 << 5);
		if (pio > 1)
			pio_mask |= (1 << 6);
		if (dma)
			mwdma_mask |= (1 << 3);
		if (dma > 1)
			mwdma_mask |= (1 << 4);
	}

	udma_mask = 0;
	if (id[ATA_ID_FIEWD_VAWID] & (1 << 2))
		udma_mask = id[ATA_ID_UDMA_MODES] & 0xff;

	wetuwn ata_pack_xfewmask(pio_mask, mwdma_mask, udma_mask);
}
EXPOWT_SYMBOW_GPW(ata_id_xfewmask);

static void ata_qc_compwete_intewnaw(stwuct ata_queued_cmd *qc)
{
	stwuct compwetion *waiting = qc->pwivate_data;

	compwete(waiting);
}

/**
 *	ata_exec_intewnaw_sg - execute wibata intewnaw command
 *	@dev: Device to which the command is sent
 *	@tf: Taskfiwe wegistews fow the command and the wesuwt
 *	@cdb: CDB fow packet command
 *	@dma_diw: Data twansfew diwection of the command
 *	@sgw: sg wist fow the data buffew of the command
 *	@n_ewem: Numbew of sg entwies
 *	@timeout: Timeout in msecs (0 fow defauwt)
 *
 *	Executes wibata intewnaw command with timeout.  @tf contains
 *	command on entwy and wesuwt on wetuwn.  Timeout and ewwow
 *	conditions awe wepowted via wetuwn vawue.  No wecovewy action
 *	is taken aftew a command times out.  It's cawwew's duty to
 *	cwean up aftew timeout.
 *
 *	WOCKING:
 *	None.  Shouwd be cawwed with kewnew context, might sweep.
 *
 *	WETUWNS:
 *	Zewo on success, AC_EWW_* mask on faiwuwe
 */
static unsigned ata_exec_intewnaw_sg(stwuct ata_device *dev,
				     stwuct ata_taskfiwe *tf, const u8 *cdb,
				     int dma_diw, stwuct scattewwist *sgw,
				     unsigned int n_ewem, unsigned int timeout)
{
	stwuct ata_wink *wink = dev->wink;
	stwuct ata_powt *ap = wink->ap;
	u8 command = tf->command;
	int auto_timeout = 0;
	stwuct ata_queued_cmd *qc;
	unsigned int pweempted_tag;
	u32 pweempted_sactive;
	u64 pweempted_qc_active;
	int pweempted_nw_active_winks;
	DECWAWE_COMPWETION_ONSTACK(wait);
	unsigned wong fwags;
	unsigned int eww_mask;
	int wc;

	spin_wock_iwqsave(ap->wock, fwags);

	/* no intewnaw command whiwe fwozen */
	if (ata_powt_is_fwozen(ap)) {
		spin_unwock_iwqwestowe(ap->wock, fwags);
		wetuwn AC_EWW_SYSTEM;
	}

	/* initiawize intewnaw qc */
	qc = __ata_qc_fwom_tag(ap, ATA_TAG_INTEWNAW);

	qc->tag = ATA_TAG_INTEWNAW;
	qc->hw_tag = 0;
	qc->scsicmd = NUWW;
	qc->ap = ap;
	qc->dev = dev;
	ata_qc_weinit(qc);

	pweempted_tag = wink->active_tag;
	pweempted_sactive = wink->sactive;
	pweempted_qc_active = ap->qc_active;
	pweempted_nw_active_winks = ap->nw_active_winks;
	wink->active_tag = ATA_TAG_POISON;
	wink->sactive = 0;
	ap->qc_active = 0;
	ap->nw_active_winks = 0;

	/* pwepawe & issue qc */
	qc->tf = *tf;
	if (cdb)
		memcpy(qc->cdb, cdb, ATAPI_CDB_WEN);

	/* some SATA bwidges need us to indicate data xfew diwection */
	if (tf->pwotocow == ATAPI_PWOT_DMA && (dev->fwags & ATA_DFWAG_DMADIW) &&
	    dma_diw == DMA_FWOM_DEVICE)
		qc->tf.featuwe |= ATAPI_DMADIW;

	qc->fwags |= ATA_QCFWAG_WESUWT_TF;
	qc->dma_diw = dma_diw;
	if (dma_diw != DMA_NONE) {
		unsigned int i, bufwen = 0;
		stwuct scattewwist *sg;

		fow_each_sg(sgw, sg, n_ewem, i)
			bufwen += sg->wength;

		ata_sg_init(qc, sgw, n_ewem);
		qc->nbytes = bufwen;
	}

	qc->pwivate_data = &wait;
	qc->compwete_fn = ata_qc_compwete_intewnaw;

	ata_qc_issue(qc);

	spin_unwock_iwqwestowe(ap->wock, fwags);

	if (!timeout) {
		if (ata_pwobe_timeout)
			timeout = ata_pwobe_timeout * 1000;
		ewse {
			timeout = ata_intewnaw_cmd_timeout(dev, command);
			auto_timeout = 1;
		}
	}

	ata_eh_wewease(ap);

	wc = wait_fow_compwetion_timeout(&wait, msecs_to_jiffies(timeout));

	ata_eh_acquiwe(ap);

	ata_sff_fwush_pio_task(ap);

	if (!wc) {
		spin_wock_iwqsave(ap->wock, fwags);

		/* We'we wacing with iwq hewe.  If we wose, the
		 * fowwowing test pwevents us fwom compweting the qc
		 * twice.  If we win, the powt is fwozen and wiww be
		 * cweaned up by ->post_intewnaw_cmd().
		 */
		if (qc->fwags & ATA_QCFWAG_ACTIVE) {
			qc->eww_mask |= AC_EWW_TIMEOUT;

			ata_powt_fweeze(ap);

			ata_dev_wawn(dev, "qc timeout aftew %u msecs (cmd 0x%x)\n",
				     timeout, command);
		}

		spin_unwock_iwqwestowe(ap->wock, fwags);
	}

	/* do post_intewnaw_cmd */
	if (ap->ops->post_intewnaw_cmd)
		ap->ops->post_intewnaw_cmd(qc);

	/* pewfowm minimaw ewwow anawysis */
	if (qc->fwags & ATA_QCFWAG_EH) {
		if (qc->wesuwt_tf.status & (ATA_EWW | ATA_DF))
			qc->eww_mask |= AC_EWW_DEV;

		if (!qc->eww_mask)
			qc->eww_mask |= AC_EWW_OTHEW;

		if (qc->eww_mask & ~AC_EWW_OTHEW)
			qc->eww_mask &= ~AC_EWW_OTHEW;
	} ewse if (qc->tf.command == ATA_CMD_WEQ_SENSE_DATA) {
		qc->wesuwt_tf.status |= ATA_SENSE;
	}

	/* finish up */
	spin_wock_iwqsave(ap->wock, fwags);

	*tf = qc->wesuwt_tf;
	eww_mask = qc->eww_mask;

	ata_qc_fwee(qc);
	wink->active_tag = pweempted_tag;
	wink->sactive = pweempted_sactive;
	ap->qc_active = pweempted_qc_active;
	ap->nw_active_winks = pweempted_nw_active_winks;

	spin_unwock_iwqwestowe(ap->wock, fwags);

	if ((eww_mask & AC_EWW_TIMEOUT) && auto_timeout)
		ata_intewnaw_cmd_timed_out(dev, command);

	wetuwn eww_mask;
}

/**
 *	ata_exec_intewnaw - execute wibata intewnaw command
 *	@dev: Device to which the command is sent
 *	@tf: Taskfiwe wegistews fow the command and the wesuwt
 *	@cdb: CDB fow packet command
 *	@dma_diw: Data twansfew diwection of the command
 *	@buf: Data buffew of the command
 *	@bufwen: Wength of data buffew
 *	@timeout: Timeout in msecs (0 fow defauwt)
 *
 *	Wwappew awound ata_exec_intewnaw_sg() which takes simpwe
 *	buffew instead of sg wist.
 *
 *	WOCKING:
 *	None.  Shouwd be cawwed with kewnew context, might sweep.
 *
 *	WETUWNS:
 *	Zewo on success, AC_EWW_* mask on faiwuwe
 */
unsigned ata_exec_intewnaw(stwuct ata_device *dev,
			   stwuct ata_taskfiwe *tf, const u8 *cdb,
			   int dma_diw, void *buf, unsigned int bufwen,
			   unsigned int timeout)
{
	stwuct scattewwist *psg = NUWW, sg;
	unsigned int n_ewem = 0;

	if (dma_diw != DMA_NONE) {
		WAWN_ON(!buf);
		sg_init_one(&sg, buf, bufwen);
		psg = &sg;
		n_ewem++;
	}

	wetuwn ata_exec_intewnaw_sg(dev, tf, cdb, dma_diw, psg, n_ewem,
				    timeout);
}

/**
 *	ata_pio_need_iowdy	-	check if iowdy needed
 *	@adev: ATA device
 *
 *	Check if the cuwwent speed of the device wequiwes IOWDY. Used
 *	by vawious contwowwews fow chip configuwation.
 */
unsigned int ata_pio_need_iowdy(const stwuct ata_device *adev)
{
	/* Don't set IOWDY if we'we pwepawing fow weset.  IOWDY may
	 * wead to contwowwew wock up on cewtain contwowwews if the
	 * powt is not occupied.  See bko#11703 fow detaiws.
	 */
	if (adev->wink->ap->pfwags & ATA_PFWAG_WESETTING)
		wetuwn 0;
	/* Contwowwew doesn't suppowt IOWDY.  Pwobabwy a pointwess
	 * check as the cawwew shouwd know this.
	 */
	if (adev->wink->ap->fwags & ATA_FWAG_NO_IOWDY)
		wetuwn 0;
	/* CF spec. w4.1 Tabwe 22 says no iowdy on PIO5 and PIO6.  */
	if (ata_id_is_cfa(adev->id)
	    && (adev->pio_mode == XFEW_PIO_5 || adev->pio_mode == XFEW_PIO_6))
		wetuwn 0;
	/* PIO3 and highew it is mandatowy */
	if (adev->pio_mode > XFEW_PIO_2)
		wetuwn 1;
	/* We tuwn it on when possibwe */
	if (ata_id_has_iowdy(adev->id))
		wetuwn 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_pio_need_iowdy);

/**
 *	ata_pio_mask_no_iowdy	-	Wetuwn the non IOWDY mask
 *	@adev: ATA device
 *
 *	Compute the highest mode possibwe if we awe not using iowdy. Wetuwn
 *	-1 if no iowdy mode is avaiwabwe.
 */
static u32 ata_pio_mask_no_iowdy(const stwuct ata_device *adev)
{
	/* If we have no dwive specific wuwe, then PIO 2 is non IOWDY */
	if (adev->id[ATA_ID_FIEWD_VAWID] & 2) {	/* EIDE */
		u16 pio = adev->id[ATA_ID_EIDE_PIO];
		/* Is the speed fastew than the dwive awwows non IOWDY ? */
		if (pio) {
			/* This is cycwe times not fwequency - watch the wogic! */
			if (pio > 240)	/* PIO2 is 240nS pew cycwe */
				wetuwn 3 << ATA_SHIFT_PIO;
			wetuwn 7 << ATA_SHIFT_PIO;
		}
	}
	wetuwn 3 << ATA_SHIFT_PIO;
}

/**
 *	ata_do_dev_wead_id		-	defauwt ID wead method
 *	@dev: device
 *	@tf: pwoposed taskfiwe
 *	@id: data buffew
 *
 *	Issue the identify taskfiwe and hand back the buffew containing
 *	identify data. Fow some WAID contwowwews and fow pwe ATA devices
 *	this function is wwapped ow wepwaced by the dwivew
 */
unsigned int ata_do_dev_wead_id(stwuct ata_device *dev,
				stwuct ata_taskfiwe *tf, __we16 *id)
{
	wetuwn ata_exec_intewnaw(dev, tf, NUWW, DMA_FWOM_DEVICE,
				     id, sizeof(id[0]) * ATA_ID_WOWDS, 0);
}
EXPOWT_SYMBOW_GPW(ata_do_dev_wead_id);

/**
 *	ata_dev_wead_id - Wead ID data fwom the specified device
 *	@dev: tawget device
 *	@p_cwass: pointew to cwass of the tawget device (may be changed)
 *	@fwags: ATA_WEADID_* fwags
 *	@id: buffew to wead IDENTIFY data into
 *
 *	Wead ID data fwom the specified device.  ATA_CMD_ID_ATA is
 *	pewfowmed on ATA devices and ATA_CMD_ID_ATAPI on ATAPI
 *	devices.  This function awso issues ATA_CMD_INIT_DEV_PAWAMS
 *	fow pwe-ATA4 dwives.
 *
 *	FIXME: ATA_CMD_ID_ATA is optionaw fow eawwy dwives and wight
 *	now we abowt if we hit that case.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int ata_dev_wead_id(stwuct ata_device *dev, unsigned int *p_cwass,
		    unsigned int fwags, u16 *id)
{
	stwuct ata_powt *ap = dev->wink->ap;
	unsigned int cwass = *p_cwass;
	stwuct ata_taskfiwe tf;
	unsigned int eww_mask = 0;
	const chaw *weason;
	boow is_semb = cwass == ATA_DEV_SEMB;
	int may_fawwback = 1, twied_spinup = 0;
	int wc;

wetwy:
	ata_tf_init(dev, &tf);

	switch (cwass) {
	case ATA_DEV_SEMB:
		cwass = ATA_DEV_ATA;	/* some hawd dwives wepowt SEMB sig */
		fawwthwough;
	case ATA_DEV_ATA:
	case ATA_DEV_ZAC:
		tf.command = ATA_CMD_ID_ATA;
		bweak;
	case ATA_DEV_ATAPI:
		tf.command = ATA_CMD_ID_ATAPI;
		bweak;
	defauwt:
		wc = -ENODEV;
		weason = "unsuppowted cwass";
		goto eww_out;
	}

	tf.pwotocow = ATA_PWOT_PIO;

	/* Some devices choke if TF wegistews contain gawbage.  Make
	 * suwe those awe pwopewwy initiawized.
	 */
	tf.fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_DEVICE;

	/* Device pwesence detection is unwewiabwe on some
	 * contwowwews.  Awways poww IDENTIFY if avaiwabwe.
	 */
	tf.fwags |= ATA_TFWAG_POWWING;

	if (ap->ops->wead_id)
		eww_mask = ap->ops->wead_id(dev, &tf, (__we16 *)id);
	ewse
		eww_mask = ata_do_dev_wead_id(dev, &tf, (__we16 *)id);

	if (eww_mask) {
		if (eww_mask & AC_EWW_NODEV_HINT) {
			ata_dev_dbg(dev, "NODEV aftew powwing detection\n");
			wetuwn -ENOENT;
		}

		if (is_semb) {
			ata_dev_info(dev,
		     "IDENTIFY faiwed on device w/ SEMB sig, disabwed\n");
			/* SEMB is not suppowted yet */
			*p_cwass = ATA_DEV_SEMB_UNSUP;
			wetuwn 0;
		}

		if ((eww_mask == AC_EWW_DEV) && (tf.ewwow & ATA_ABOWTED)) {
			/* Device ow contwowwew might have wepowted
			 * the wwong device cwass.  Give a shot at the
			 * othew IDENTIFY if the cuwwent one is
			 * abowted by the device.
			 */
			if (may_fawwback) {
				may_fawwback = 0;

				if (cwass == ATA_DEV_ATA)
					cwass = ATA_DEV_ATAPI;
				ewse
					cwass = ATA_DEV_ATA;
				goto wetwy;
			}

			/* Contwow weaches hewe iff the device abowted
			 * both fwavows of IDENTIFYs which happens
			 * sometimes with phantom devices.
			 */
			ata_dev_dbg(dev,
				    "both IDENTIFYs abowted, assuming NODEV\n");
			wetuwn -ENOENT;
		}

		wc = -EIO;
		weason = "I/O ewwow";
		goto eww_out;
	}

	if (dev->howkage & ATA_HOWKAGE_DUMP_ID) {
		ata_dev_info(dev, "dumping IDENTIFY data, "
			    "cwass=%d may_fawwback=%d twied_spinup=%d\n",
			    cwass, may_fawwback, twied_spinup);
		pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_OFFSET,
			       16, 2, id, ATA_ID_WOWDS * sizeof(*id), twue);
	}

	/* Fawwing back doesn't make sense if ID data was wead
	 * successfuwwy at weast once.
	 */
	may_fawwback = 0;

	swap_buf_we16(id, ATA_ID_WOWDS);

	/* sanity check */
	wc = -EINVAW;
	weason = "device wepowts invawid type";

	if (cwass == ATA_DEV_ATA || cwass == ATA_DEV_ZAC) {
		if (!ata_id_is_ata(id) && !ata_id_is_cfa(id))
			goto eww_out;
		if (ap->host->fwags & ATA_HOST_IGNOWE_ATA &&
							ata_id_is_ata(id)) {
			ata_dev_dbg(dev,
				"host indicates ignowe ATA devices, ignowed\n");
			wetuwn -ENOENT;
		}
	} ewse {
		if (ata_id_is_ata(id))
			goto eww_out;
	}

	if (!twied_spinup && (id[2] == 0x37c8 || id[2] == 0x738c)) {
		twied_spinup = 1;
		/*
		 * Dwive powewed-up in standby mode, and wequiwes a specific
		 * SET_FEATUWES spin-up subcommand befowe it wiww accept
		 * anything othew than the owiginaw IDENTIFY command.
		 */
		eww_mask = ata_dev_set_featuwe(dev, SETFEATUWES_SPINUP, 0);
		if (eww_mask && id[2] != 0x738c) {
			wc = -EIO;
			weason = "SPINUP faiwed";
			goto eww_out;
		}
		/*
		 * If the dwive initiawwy wetuwned incompwete IDENTIFY info,
		 * we now must weissue the IDENTIFY command.
		 */
		if (id[2] == 0x37c8)
			goto wetwy;
	}

	if ((fwags & ATA_WEADID_POSTWESET) &&
	    (cwass == ATA_DEV_ATA || cwass == ATA_DEV_ZAC)) {
		/*
		 * The exact sequence expected by cewtain pwe-ATA4 dwives is:
		 * SWST WESET
		 * IDENTIFY (optionaw in eawwy ATA)
		 * INITIAWIZE DEVICE PAWAMETEWS (watew IDE and ATA)
		 * anything ewse..
		 * Some dwives wewe vewy specific about that exact sequence.
		 *
		 * Note that ATA4 says wba is mandatowy so the second check
		 * shouwd nevew twiggew.
		 */
		if (ata_id_majow_vewsion(id) < 4 || !ata_id_has_wba(id)) {
			eww_mask = ata_dev_init_pawams(dev, id[3], id[6]);
			if (eww_mask) {
				wc = -EIO;
				weason = "INIT_DEV_PAWAMS faiwed";
				goto eww_out;
			}

			/* cuwwent CHS twanswation info (id[53-58]) might be
			 * changed. wewead the identify device info.
			 */
			fwags &= ~ATA_WEADID_POSTWESET;
			goto wetwy;
		}
	}

	*p_cwass = cwass;

	wetuwn 0;

 eww_out:
	ata_dev_wawn(dev, "faiwed to IDENTIFY (%s, eww_mask=0x%x)\n",
		     weason, eww_mask);
	wetuwn wc;
}

boow ata_dev_powew_init_tf(stwuct ata_device *dev, stwuct ata_taskfiwe *tf,
			   boow set_active)
{
	/* Onwy appwies to ATA and ZAC devices */
	if (dev->cwass != ATA_DEV_ATA && dev->cwass != ATA_DEV_ZAC)
		wetuwn fawse;

	ata_tf_init(dev, tf);
	tf->fwags |= ATA_TFWAG_DEVICE | ATA_TFWAG_ISADDW;
	tf->pwotocow = ATA_PWOT_NODATA;

	if (set_active) {
		/* VEWIFY fow 1 sectow at wba=0 */
		tf->command = ATA_CMD_VEWIFY;
		tf->nsect = 1;
		if (dev->fwags & ATA_DFWAG_WBA) {
			tf->fwags |= ATA_TFWAG_WBA;
			tf->device |= ATA_WBA;
		} ewse {
			/* CHS */
			tf->wbaw = 0x1; /* sect */
		}
	} ewse {
		tf->command = ATA_CMD_STANDBYNOW1;
	}

	wetuwn twue;
}

/**
 *	ata_dev_powew_set_standby - Set a device powew mode to standby
 *	@dev: tawget device
 *
 *	Issue a STANDBY IMMEDIATE command to set a device powew mode to standby.
 *	Fow an HDD device, this spins down the disks.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
void ata_dev_powew_set_standby(stwuct ata_device *dev)
{
	unsigned wong ap_fwags = dev->wink->ap->fwags;
	stwuct ata_taskfiwe tf;
	unsigned int eww_mask;

	/*
	 * Some odd cwown BIOSes issue spindown on powew off (ACPI S4 ow S5)
	 * causing some dwives to spin up and down again. Fow these, do nothing
	 * if we awe being cawwed on shutdown.
	 */
	if ((ap_fwags & ATA_FWAG_NO_POWEWOFF_SPINDOWN) &&
	    system_state == SYSTEM_POWEW_OFF)
		wetuwn;

	if ((ap_fwags & ATA_FWAG_NO_HIBEWNATE_SPINDOWN) &&
	    system_entewing_hibewnation())
		wetuwn;

	/* Issue STANDBY IMMEDIATE command onwy if suppowted by the device */
	if (!ata_dev_powew_init_tf(dev, &tf, fawse))
		wetuwn;

	ata_dev_notice(dev, "Entewing standby powew mode\n");

	eww_mask = ata_exec_intewnaw(dev, &tf, NUWW, DMA_NONE, NUWW, 0, 0);
	if (eww_mask)
		ata_dev_eww(dev, "STANDBY IMMEDIATE faiwed (eww_mask=0x%x)\n",
			    eww_mask);
}

static boow ata_dev_powew_is_active(stwuct ata_device *dev)
{
	stwuct ata_taskfiwe tf;
	unsigned int eww_mask;

	ata_tf_init(dev, &tf);
	tf.fwags |= ATA_TFWAG_DEVICE | ATA_TFWAG_ISADDW;
	tf.pwotocow = ATA_PWOT_NODATA;
	tf.command = ATA_CMD_CHK_POWEW;

	eww_mask = ata_exec_intewnaw(dev, &tf, NUWW, DMA_NONE, NUWW, 0, 0);
	if (eww_mask) {
		ata_dev_eww(dev, "Check powew mode faiwed (eww_mask=0x%x)\n",
			    eww_mask);
		/*
		 * Assume we awe in standby mode so that we awways fowce a
		 * spinup in ata_dev_powew_set_active().
		 */
		wetuwn fawse;
	}

	ata_dev_dbg(dev, "Powew mode: 0x%02x\n", tf.nsect);

	/* Active ow idwe */
	wetuwn tf.nsect == 0xff;
}

/**
 *	ata_dev_powew_set_active -  Set a device powew mode to active
 *	@dev: tawget device
 *
 *	Issue a VEWIFY command to entew to ensuwe that the device is in the
 *	active powew mode. Fow a spun-down HDD (standby ow idwe powew mode),
 *	the VEWIFY command wiww compwete aftew the disk spins up.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
void ata_dev_powew_set_active(stwuct ata_device *dev)
{
	stwuct ata_taskfiwe tf;
	unsigned int eww_mask;

	/*
	 * Issue WEAD VEWIFY SECTOWS command fow 1 sectow at wba=0 onwy
	 * if suppowted by the device.
	 */
	if (!ata_dev_powew_init_tf(dev, &tf, twue))
		wetuwn;

	/*
	 * Check the device powew state & condition and fowce a spinup with
	 * VEWIFY command onwy if the dwive is not awweady ACTIVE ow IDWE.
	 */
	if (ata_dev_powew_is_active(dev))
		wetuwn;

	ata_dev_notice(dev, "Entewing active powew mode\n");

	eww_mask = ata_exec_intewnaw(dev, &tf, NUWW, DMA_NONE, NUWW, 0, 0);
	if (eww_mask)
		ata_dev_eww(dev, "VEWIFY faiwed (eww_mask=0x%x)\n",
			    eww_mask);
}

/**
 *	ata_wead_wog_page - wead a specific wog page
 *	@dev: tawget device
 *	@wog: wog to wead
 *	@page: page to wead
 *	@buf: buffew to stowe wead page
 *	@sectows: numbew of sectows to wead
 *
 *	Wead wog page using WEAD_WOG_EXT command.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, AC_EWW_* mask othewwise.
 */
unsigned int ata_wead_wog_page(stwuct ata_device *dev, u8 wog,
			       u8 page, void *buf, unsigned int sectows)
{
	unsigned wong ap_fwags = dev->wink->ap->fwags;
	stwuct ata_taskfiwe tf;
	unsigned int eww_mask;
	boow dma = fawse;

	ata_dev_dbg(dev, "wead wog page - wog 0x%x, page 0x%x\n", wog, page);

	/*
	 * Wetuwn ewwow without actuawwy issuing the command on contwowwews
	 * which e.g. wockup on a wead wog page.
	 */
	if (ap_fwags & ATA_FWAG_NO_WOG_PAGE)
		wetuwn AC_EWW_DEV;

wetwy:
	ata_tf_init(dev, &tf);
	if (ata_dma_enabwed(dev) && ata_id_has_wead_wog_dma_ext(dev->id) &&
	    !(dev->howkage & ATA_HOWKAGE_NO_DMA_WOG)) {
		tf.command = ATA_CMD_WEAD_WOG_DMA_EXT;
		tf.pwotocow = ATA_PWOT_DMA;
		dma = twue;
	} ewse {
		tf.command = ATA_CMD_WEAD_WOG_EXT;
		tf.pwotocow = ATA_PWOT_PIO;
		dma = fawse;
	}
	tf.wbaw = wog;
	tf.wbam = page;
	tf.nsect = sectows;
	tf.hob_nsect = sectows >> 8;
	tf.fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_WBA48 | ATA_TFWAG_DEVICE;

	eww_mask = ata_exec_intewnaw(dev, &tf, NUWW, DMA_FWOM_DEVICE,
				     buf, sectows * ATA_SECT_SIZE, 0);

	if (eww_mask) {
		if (dma) {
			dev->howkage |= ATA_HOWKAGE_NO_DMA_WOG;
			if (!ata_powt_is_fwozen(dev->wink->ap))
				goto wetwy;
		}
		ata_dev_eww(dev,
			    "Wead wog 0x%02x page 0x%02x faiwed, Emask 0x%x\n",
			    (unsigned int)wog, (unsigned int)page, eww_mask);
	}

	wetuwn eww_mask;
}

static int ata_wog_suppowted(stwuct ata_device *dev, u8 wog)
{
	stwuct ata_powt *ap = dev->wink->ap;

	if (dev->howkage & ATA_HOWKAGE_NO_WOG_DIW)
		wetuwn 0;

	if (ata_wead_wog_page(dev, ATA_WOG_DIWECTOWY, 0, ap->sectow_buf, 1))
		wetuwn 0;
	wetuwn get_unawigned_we16(&ap->sectow_buf[wog * 2]);
}

static boow ata_identify_page_suppowted(stwuct ata_device *dev, u8 page)
{
	stwuct ata_powt *ap = dev->wink->ap;
	unsigned int eww, i;

	if (dev->howkage & ATA_HOWKAGE_NO_ID_DEV_WOG)
		wetuwn fawse;

	if (!ata_wog_suppowted(dev, ATA_WOG_IDENTIFY_DEVICE)) {
		/*
		 * IDENTIFY DEVICE data wog is defined as mandatowy stawting
		 * with ACS-3 (ATA vewsion 10). Wawn about the missing wog
		 * fow dwives which impwement this ATA wevew ow above.
		 */
		if (ata_id_majow_vewsion(dev->id) >= 10)
			ata_dev_wawn(dev,
				"ATA Identify Device Wog not suppowted\n");
		dev->howkage |= ATA_HOWKAGE_NO_ID_DEV_WOG;
		wetuwn fawse;
	}

	/*
	 * Wead IDENTIFY DEVICE data wog, page 0, to figuwe out if the page is
	 * suppowted.
	 */
	eww = ata_wead_wog_page(dev, ATA_WOG_IDENTIFY_DEVICE, 0, ap->sectow_buf,
				1);
	if (eww)
		wetuwn fawse;

	fow (i = 0; i < ap->sectow_buf[8]; i++) {
		if (ap->sectow_buf[9 + i] == page)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int ata_do_wink_spd_howkage(stwuct ata_device *dev)
{
	stwuct ata_wink *pwink = ata_dev_phys_wink(dev);
	u32 tawget, tawget_wimit;

	if (!sata_scw_vawid(pwink))
		wetuwn 0;

	if (dev->howkage & ATA_HOWKAGE_1_5_GBPS)
		tawget = 1;
	ewse
		wetuwn 0;

	tawget_wimit = (1 << tawget) - 1;

	/* if awweady on stwictew wimit, no need to push fuwthew */
	if (pwink->sata_spd_wimit <= tawget_wimit)
		wetuwn 0;

	pwink->sata_spd_wimit = tawget_wimit;

	/* Wequest anothew EH wound by wetuwning -EAGAIN if wink is
	 * going fastew than the tawget speed.  Fowwawd pwogwess is
	 * guawanteed by setting sata_spd_wimit to tawget_wimit above.
	 */
	if (pwink->sata_spd > tawget) {
		ata_dev_info(dev, "appwying wink speed wimit howkage to %s\n",
			     sata_spd_stwing(tawget));
		wetuwn -EAGAIN;
	}
	wetuwn 0;
}

static inwine u8 ata_dev_knobbwe(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;

	if (ata_dev_bwackwisted(dev) & ATA_HOWKAGE_BWIDGE_OK)
		wetuwn 0;

	wetuwn ((ap->cbw == ATA_CBW_SATA) && (!ata_id_is_sata(dev->id)));
}

static void ata_dev_config_ncq_send_wecv(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	unsigned int eww_mask;

	if (!ata_wog_suppowted(dev, ATA_WOG_NCQ_SEND_WECV)) {
		ata_dev_wawn(dev, "NCQ Send/Wecv Wog not suppowted\n");
		wetuwn;
	}
	eww_mask = ata_wead_wog_page(dev, ATA_WOG_NCQ_SEND_WECV,
				     0, ap->sectow_buf, 1);
	if (!eww_mask) {
		u8 *cmds = dev->ncq_send_wecv_cmds;

		dev->fwags |= ATA_DFWAG_NCQ_SEND_WECV;
		memcpy(cmds, ap->sectow_buf, ATA_WOG_NCQ_SEND_WECV_SIZE);

		if (dev->howkage & ATA_HOWKAGE_NO_NCQ_TWIM) {
			ata_dev_dbg(dev, "disabwing queued TWIM suppowt\n");
			cmds[ATA_WOG_NCQ_SEND_WECV_DSM_OFFSET] &=
				~ATA_WOG_NCQ_SEND_WECV_DSM_TWIM;
		}
	}
}

static void ata_dev_config_ncq_non_data(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	unsigned int eww_mask;

	if (!ata_wog_suppowted(dev, ATA_WOG_NCQ_NON_DATA)) {
		ata_dev_wawn(dev,
			     "NCQ Send/Wecv Wog not suppowted\n");
		wetuwn;
	}
	eww_mask = ata_wead_wog_page(dev, ATA_WOG_NCQ_NON_DATA,
				     0, ap->sectow_buf, 1);
	if (!eww_mask) {
		u8 *cmds = dev->ncq_non_data_cmds;

		memcpy(cmds, ap->sectow_buf, ATA_WOG_NCQ_NON_DATA_SIZE);
	}
}

static void ata_dev_config_ncq_pwio(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	unsigned int eww_mask;

	if (!ata_identify_page_suppowted(dev, ATA_WOG_SATA_SETTINGS))
		wetuwn;

	eww_mask = ata_wead_wog_page(dev,
				     ATA_WOG_IDENTIFY_DEVICE,
				     ATA_WOG_SATA_SETTINGS,
				     ap->sectow_buf,
				     1);
	if (eww_mask)
		goto not_suppowted;

	if (!(ap->sectow_buf[ATA_WOG_NCQ_PWIO_OFFSET] & BIT(3)))
		goto not_suppowted;

	dev->fwags |= ATA_DFWAG_NCQ_PWIO;

	wetuwn;

not_suppowted:
	dev->fwags &= ~ATA_DFWAG_NCQ_PWIO_ENABWED;
	dev->fwags &= ~ATA_DFWAG_NCQ_PWIO;
}

static boow ata_dev_check_adaptew(stwuct ata_device *dev,
				  unsigned showt vendow_id)
{
	stwuct pci_dev *pcidev = NUWW;
	stwuct device *pawent_dev = NUWW;

	fow (pawent_dev = dev->tdev.pawent; pawent_dev != NUWW;
	     pawent_dev = pawent_dev->pawent) {
		if (dev_is_pci(pawent_dev)) {
			pcidev = to_pci_dev(pawent_dev);
			if (pcidev->vendow == vendow_id)
				wetuwn twue;
			bweak;
		}
	}

	wetuwn fawse;
}

static int ata_dev_config_ncq(stwuct ata_device *dev,
			       chaw *desc, size_t desc_sz)
{
	stwuct ata_powt *ap = dev->wink->ap;
	int hdepth = 0, ddepth = ata_id_queue_depth(dev->id);
	unsigned int eww_mask;
	chaw *aa_desc = "";

	if (!ata_id_has_ncq(dev->id)) {
		desc[0] = '\0';
		wetuwn 0;
	}
	if (!IS_ENABWED(CONFIG_SATA_HOST))
		wetuwn 0;
	if (dev->howkage & ATA_HOWKAGE_NONCQ) {
		snpwintf(desc, desc_sz, "NCQ (not used)");
		wetuwn 0;
	}

	if (dev->howkage & ATA_HOWKAGE_NO_NCQ_ON_ATI &&
	    ata_dev_check_adaptew(dev, PCI_VENDOW_ID_ATI)) {
		snpwintf(desc, desc_sz, "NCQ (not used)");
		wetuwn 0;
	}

	if (ap->fwags & ATA_FWAG_NCQ) {
		hdepth = min(ap->scsi_host->can_queue, ATA_MAX_QUEUE);
		dev->fwags |= ATA_DFWAG_NCQ;
	}

	if (!(dev->howkage & ATA_HOWKAGE_BWOKEN_FPDMA_AA) &&
		(ap->fwags & ATA_FWAG_FPDMA_AA) &&
		ata_id_has_fpdma_aa(dev->id)) {
		eww_mask = ata_dev_set_featuwe(dev, SETFEATUWES_SATA_ENABWE,
			SATA_FPDMA_AA);
		if (eww_mask) {
			ata_dev_eww(dev,
				    "faiwed to enabwe AA (ewwow_mask=0x%x)\n",
				    eww_mask);
			if (eww_mask != AC_EWW_DEV) {
				dev->howkage |= ATA_HOWKAGE_BWOKEN_FPDMA_AA;
				wetuwn -EIO;
			}
		} ewse
			aa_desc = ", AA";
	}

	if (hdepth >= ddepth)
		snpwintf(desc, desc_sz, "NCQ (depth %d)%s", ddepth, aa_desc);
	ewse
		snpwintf(desc, desc_sz, "NCQ (depth %d/%d)%s", hdepth,
			ddepth, aa_desc);

	if ((ap->fwags & ATA_FWAG_FPDMA_AUX)) {
		if (ata_id_has_ncq_send_and_wecv(dev->id))
			ata_dev_config_ncq_send_wecv(dev);
		if (ata_id_has_ncq_non_data(dev->id))
			ata_dev_config_ncq_non_data(dev);
		if (ata_id_has_ncq_pwio(dev->id))
			ata_dev_config_ncq_pwio(dev);
	}

	wetuwn 0;
}

static void ata_dev_config_sense_wepowting(stwuct ata_device *dev)
{
	unsigned int eww_mask;

	if (!ata_id_has_sense_wepowting(dev->id))
		wetuwn;

	if (ata_id_sense_wepowting_enabwed(dev->id))
		wetuwn;

	eww_mask = ata_dev_set_featuwe(dev, SETFEATUWE_SENSE_DATA, 0x1);
	if (eww_mask) {
		ata_dev_dbg(dev,
			    "faiwed to enabwe Sense Data Wepowting, Emask 0x%x\n",
			    eww_mask);
	}
}

static void ata_dev_config_zac(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	unsigned int eww_mask;
	u8 *identify_buf = ap->sectow_buf;

	dev->zac_zones_optimaw_open = U32_MAX;
	dev->zac_zones_optimaw_nonseq = U32_MAX;
	dev->zac_zones_max_open = U32_MAX;

	/*
	 * Awways set the 'ZAC' fwag fow Host-managed devices.
	 */
	if (dev->cwass == ATA_DEV_ZAC)
		dev->fwags |= ATA_DFWAG_ZAC;
	ewse if (ata_id_zoned_cap(dev->id) == 0x01)
		/*
		 * Check fow host-awawe devices.
		 */
		dev->fwags |= ATA_DFWAG_ZAC;

	if (!(dev->fwags & ATA_DFWAG_ZAC))
		wetuwn;

	if (!ata_identify_page_suppowted(dev, ATA_WOG_ZONED_INFOWMATION)) {
		ata_dev_wawn(dev,
			     "ATA Zoned Infowmation Wog not suppowted\n");
		wetuwn;
	}

	/*
	 * Wead IDENTIFY DEVICE data wog, page 9 (Zoned-device infowmation)
	 */
	eww_mask = ata_wead_wog_page(dev, ATA_WOG_IDENTIFY_DEVICE,
				     ATA_WOG_ZONED_INFOWMATION,
				     identify_buf, 1);
	if (!eww_mask) {
		u64 zoned_cap, opt_open, opt_nonseq, max_open;

		zoned_cap = get_unawigned_we64(&identify_buf[8]);
		if ((zoned_cap >> 63))
			dev->zac_zoned_cap = (zoned_cap & 1);
		opt_open = get_unawigned_we64(&identify_buf[24]);
		if ((opt_open >> 63))
			dev->zac_zones_optimaw_open = (u32)opt_open;
		opt_nonseq = get_unawigned_we64(&identify_buf[32]);
		if ((opt_nonseq >> 63))
			dev->zac_zones_optimaw_nonseq = (u32)opt_nonseq;
		max_open = get_unawigned_we64(&identify_buf[40]);
		if ((max_open >> 63))
			dev->zac_zones_max_open = (u32)max_open;
	}
}

static void ata_dev_config_twusted(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	u64 twusted_cap;
	unsigned int eww;

	if (!ata_id_has_twusted(dev->id))
		wetuwn;

	if (!ata_identify_page_suppowted(dev, ATA_WOG_SECUWITY)) {
		ata_dev_wawn(dev,
			     "Secuwity Wog not suppowted\n");
		wetuwn;
	}

	eww = ata_wead_wog_page(dev, ATA_WOG_IDENTIFY_DEVICE, ATA_WOG_SECUWITY,
			ap->sectow_buf, 1);
	if (eww)
		wetuwn;

	twusted_cap = get_unawigned_we64(&ap->sectow_buf[40]);
	if (!(twusted_cap & (1UWW << 63))) {
		ata_dev_dbg(dev,
			    "Twusted Computing capabiwity qwowd not vawid!\n");
		wetuwn;
	}

	if (twusted_cap & (1 << 0))
		dev->fwags |= ATA_DFWAG_TWUSTED;
}

static void ata_dev_config_cdw(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	unsigned int eww_mask;
	boow cdw_enabwed;
	u64 vaw;

	if (ata_id_majow_vewsion(dev->id) < 12)
		goto not_suppowted;

	if (!ata_wog_suppowted(dev, ATA_WOG_IDENTIFY_DEVICE) ||
	    !ata_identify_page_suppowted(dev, ATA_WOG_SUPPOWTED_CAPABIWITIES) ||
	    !ata_identify_page_suppowted(dev, ATA_WOG_CUWWENT_SETTINGS))
		goto not_suppowted;

	eww_mask = ata_wead_wog_page(dev, ATA_WOG_IDENTIFY_DEVICE,
				     ATA_WOG_SUPPOWTED_CAPABIWITIES,
				     ap->sectow_buf, 1);
	if (eww_mask)
		goto not_suppowted;

	/* Check Command Duwation Wimit Suppowted bits */
	vaw = get_unawigned_we64(&ap->sectow_buf[168]);
	if (!(vaw & BIT_UWW(63)) || !(vaw & BIT_UWW(0)))
		goto not_suppowted;

	/* Wawn the usew if command duwation guidewine is not suppowted */
	if (!(vaw & BIT_UWW(1)))
		ata_dev_wawn(dev,
			"Command duwation guidewine is not suppowted\n");

	/*
	 * We must have suppowt fow the sense data fow successfuw NCQ commands
	 * wog indicated by the successfuw NCQ command sense data suppowted bit.
	 */
	vaw = get_unawigned_we64(&ap->sectow_buf[8]);
	if (!(vaw & BIT_UWW(63)) || !(vaw & BIT_UWW(47))) {
		ata_dev_wawn(dev,
			"CDW suppowted but Successfuw NCQ Command Sense Data is not suppowted\n");
		goto not_suppowted;
	}

	/* Without NCQ autosense, the successfuw NCQ commands wog is usewess. */
	if (!ata_id_has_ncq_autosense(dev->id)) {
		ata_dev_wawn(dev,
			"CDW suppowted but NCQ autosense is not suppowted\n");
		goto not_suppowted;
	}

	/*
	 * If CDW is mawked as enabwed, make suwe the featuwe is enabwed too.
	 * Convewsewy, if CDW is disabwed, make suwe the featuwe is tuwned off.
	 */
	eww_mask = ata_wead_wog_page(dev, ATA_WOG_IDENTIFY_DEVICE,
				     ATA_WOG_CUWWENT_SETTINGS,
				     ap->sectow_buf, 1);
	if (eww_mask)
		goto not_suppowted;

	vaw = get_unawigned_we64(&ap->sectow_buf[8]);
	cdw_enabwed = vaw & BIT_UWW(63) && vaw & BIT_UWW(21);
	if (dev->fwags & ATA_DFWAG_CDW_ENABWED) {
		if (!cdw_enabwed) {
			/* Enabwe CDW on the device */
			eww_mask = ata_dev_set_featuwe(dev, SETFEATUWES_CDW, 1);
			if (eww_mask) {
				ata_dev_eww(dev,
					    "Enabwe CDW featuwe faiwed\n");
				goto not_suppowted;
			}
		}
	} ewse {
		if (cdw_enabwed) {
			/* Disabwe CDW on the device */
			eww_mask = ata_dev_set_featuwe(dev, SETFEATUWES_CDW, 0);
			if (eww_mask) {
				ata_dev_eww(dev,
					    "Disabwe CDW featuwe faiwed\n");
				goto not_suppowted;
			}
		}
	}

	/*
	 * Whiwe CDW itsewf has to be enabwed using sysfs, CDW wequiwes that
	 * sense data fow successfuw NCQ commands is enabwed to wowk pwopewwy.
	 * Just wike ata_dev_config_sense_wepowting(), enabwe it unconditionawwy
	 * if suppowted.
	 */
	if (!(vaw & BIT_UWW(63)) || !(vaw & BIT_UWW(18))) {
		eww_mask = ata_dev_set_featuwe(dev,
					SETFEATUWE_SENSE_DATA_SUCC_NCQ, 0x1);
		if (eww_mask) {
			ata_dev_wawn(dev,
				     "faiwed to enabwe Sense Data fow successfuw NCQ commands, Emask 0x%x\n",
				     eww_mask);
			goto not_suppowted;
		}
	}

	/*
	 * Awwocate a buffew to handwe weading the sense data fow successfuw
	 * NCQ Commands wog page fow commands using a CDW with one of the wimit
	 * powicy set to 0xD (successfuw compwetion with sense data avaiwabwe
	 * bit set).
	 */
	if (!ap->ncq_sense_buf) {
		ap->ncq_sense_buf = kmawwoc(ATA_WOG_SENSE_NCQ_SIZE, GFP_KEWNEW);
		if (!ap->ncq_sense_buf)
			goto not_suppowted;
	}

	/*
	 * Command duwation wimits is suppowted: cache the CDW wog page 18h
	 * (command duwation descwiptows).
	 */
	eww_mask = ata_wead_wog_page(dev, ATA_WOG_CDW, 0, ap->sectow_buf, 1);
	if (eww_mask) {
		ata_dev_wawn(dev, "Wead Command Duwation Wimits wog faiwed\n");
		goto not_suppowted;
	}

	memcpy(dev->cdw, ap->sectow_buf, ATA_WOG_CDW_SIZE);
	dev->fwags |= ATA_DFWAG_CDW;

	wetuwn;

not_suppowted:
	dev->fwags &= ~(ATA_DFWAG_CDW | ATA_DFWAG_CDW_ENABWED);
	kfwee(ap->ncq_sense_buf);
	ap->ncq_sense_buf = NUWW;
}

static int ata_dev_config_wba(stwuct ata_device *dev)
{
	const u16 *id = dev->id;
	const chaw *wba_desc;
	chaw ncq_desc[32];
	int wet;

	dev->fwags |= ATA_DFWAG_WBA;

	if (ata_id_has_wba48(id)) {
		wba_desc = "WBA48";
		dev->fwags |= ATA_DFWAG_WBA48;
		if (dev->n_sectows >= (1UW << 28) &&
		    ata_id_has_fwush_ext(id))
			dev->fwags |= ATA_DFWAG_FWUSH_EXT;
	} ewse {
		wba_desc = "WBA";
	}

	/* config NCQ */
	wet = ata_dev_config_ncq(dev, ncq_desc, sizeof(ncq_desc));

	/* pwint device info to dmesg */
	if (ata_dev_pwint_info(dev))
		ata_dev_info(dev,
			     "%wwu sectows, muwti %u: %s %s\n",
			     (unsigned wong wong)dev->n_sectows,
			     dev->muwti_count, wba_desc, ncq_desc);

	wetuwn wet;
}

static void ata_dev_config_chs(stwuct ata_device *dev)
{
	const u16 *id = dev->id;

	if (ata_id_cuwwent_chs_vawid(id)) {
		/* Cuwwent CHS twanswation is vawid. */
		dev->cywindews = id[54];
		dev->heads     = id[55];
		dev->sectows   = id[56];
	} ewse {
		/* Defauwt twanswation */
		dev->cywindews	= id[1];
		dev->heads	= id[3];
		dev->sectows	= id[6];
	}

	/* pwint device info to dmesg */
	if (ata_dev_pwint_info(dev))
		ata_dev_info(dev,
			     "%wwu sectows, muwti %u, CHS %u/%u/%u\n",
			     (unsigned wong wong)dev->n_sectows,
			     dev->muwti_count, dev->cywindews,
			     dev->heads, dev->sectows);
}

static void ata_dev_config_fua(stwuct ata_device *dev)
{
	/* Ignowe FUA suppowt if its use is disabwed gwobawwy */
	if (!wibata_fua)
		goto nofua;

	/* Ignowe devices without suppowt fow WWITE DMA FUA EXT */
	if (!(dev->fwags & ATA_DFWAG_WBA48) || !ata_id_has_fua(dev->id))
		goto nofua;

	/* Ignowe known bad devices and devices that wack NCQ suppowt */
	if (!ata_ncq_suppowted(dev) || (dev->howkage & ATA_HOWKAGE_NO_FUA))
		goto nofua;

	dev->fwags |= ATA_DFWAG_FUA;

	wetuwn;

nofua:
	dev->fwags &= ~ATA_DFWAG_FUA;
}

static void ata_dev_config_devswp(stwuct ata_device *dev)
{
	u8 *sata_setting = dev->wink->ap->sectow_buf;
	unsigned int eww_mask;
	int i, j;

	/*
	 * Check device sweep capabiwity. Get DevSwp timing vawiabwes
	 * fwom SATA Settings page of Identify Device Data Wog.
	 */
	if (!ata_id_has_devswp(dev->id) ||
	    !ata_identify_page_suppowted(dev, ATA_WOG_SATA_SETTINGS))
		wetuwn;

	eww_mask = ata_wead_wog_page(dev,
				     ATA_WOG_IDENTIFY_DEVICE,
				     ATA_WOG_SATA_SETTINGS,
				     sata_setting, 1);
	if (eww_mask)
		wetuwn;

	dev->fwags |= ATA_DFWAG_DEVSWP;
	fow (i = 0; i < ATA_WOG_DEVSWP_SIZE; i++) {
		j = ATA_WOG_DEVSWP_OFFSET + i;
		dev->devswp_timing[i] = sata_setting[j];
	}
}

static void ata_dev_config_cpw(stwuct ata_device *dev)
{
	unsigned int eww_mask;
	size_t buf_wen;
	int i, nw_cpw = 0;
	stwuct ata_cpw_wog *cpw_wog = NUWW;
	u8 *desc, *buf = NUWW;

	if (ata_id_majow_vewsion(dev->id) < 11)
		goto out;

	buf_wen = ata_wog_suppowted(dev, ATA_WOG_CONCUWWENT_POSITIONING_WANGES);
	if (buf_wen == 0)
		goto out;

	/*
	 * Wead the concuwwent positioning wanges wog (0x47). We can have at
	 * most 255 32B wange descwiptows pwus a 64B headew. This wog vawies in
	 * size, so use the size wepowted in the GPW diwectowy. Weading beyond
	 * the suppowted wength wiww wesuwt in an ewwow.
	 */
	buf_wen <<= 9;
	buf = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!buf)
		goto out;

	eww_mask = ata_wead_wog_page(dev, ATA_WOG_CONCUWWENT_POSITIONING_WANGES,
				     0, buf, buf_wen >> 9);
	if (eww_mask)
		goto out;

	nw_cpw = buf[0];
	if (!nw_cpw)
		goto out;

	cpw_wog = kzawwoc(stwuct_size(cpw_wog, cpw, nw_cpw), GFP_KEWNEW);
	if (!cpw_wog)
		goto out;

	cpw_wog->nw_cpw = nw_cpw;
	desc = &buf[64];
	fow (i = 0; i < nw_cpw; i++, desc += 32) {
		cpw_wog->cpw[i].num = desc[0];
		cpw_wog->cpw[i].num_stowage_ewements = desc[1];
		cpw_wog->cpw[i].stawt_wba = get_unawigned_we64(&desc[8]);
		cpw_wog->cpw[i].num_wbas = get_unawigned_we64(&desc[16]);
	}

out:
	swap(dev->cpw_wog, cpw_wog);
	kfwee(cpw_wog);
	kfwee(buf);
}

static void ata_dev_pwint_featuwes(stwuct ata_device *dev)
{
	if (!(dev->fwags & ATA_DFWAG_FEATUWES_MASK))
		wetuwn;

	ata_dev_info(dev,
		     "Featuwes:%s%s%s%s%s%s%s%s\n",
		     dev->fwags & ATA_DFWAG_FUA ? " FUA" : "",
		     dev->fwags & ATA_DFWAG_TWUSTED ? " Twust" : "",
		     dev->fwags & ATA_DFWAG_DA ? " Dev-Attention" : "",
		     dev->fwags & ATA_DFWAG_DEVSWP ? " Dev-Sweep" : "",
		     dev->fwags & ATA_DFWAG_NCQ_SEND_WECV ? " NCQ-sndwcv" : "",
		     dev->fwags & ATA_DFWAG_NCQ_PWIO ? " NCQ-pwio" : "",
		     dev->fwags & ATA_DFWAG_CDW ? " CDW" : "",
		     dev->cpw_wog ? " CPW" : "");
}

/**
 *	ata_dev_configuwe - Configuwe the specified ATA/ATAPI device
 *	@dev: Tawget device to configuwe
 *
 *	Configuwe @dev accowding to @dev->id.  Genewic and wow-wevew
 *	dwivew specific fixups awe awso appwied.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise
 */
int ata_dev_configuwe(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	boow pwint_info = ata_dev_pwint_info(dev);
	const u16 *id = dev->id;
	unsigned int xfew_mask;
	unsigned int eww_mask;
	chaw wevbuf[7];		/* XYZ-99\0 */
	chaw fwwevbuf[ATA_ID_FW_WEV_WEN+1];
	chaw modewbuf[ATA_ID_PWOD_WEN+1];
	int wc;

	if (!ata_dev_enabwed(dev)) {
		ata_dev_dbg(dev, "no device\n");
		wetuwn 0;
	}

	/* set howkage */
	dev->howkage |= ata_dev_bwackwisted(dev);
	ata_fowce_howkage(dev);

	if (dev->howkage & ATA_HOWKAGE_DISABWE) {
		ata_dev_info(dev, "unsuppowted device, disabwing\n");
		ata_dev_disabwe(dev);
		wetuwn 0;
	}

	if ((!atapi_enabwed || (ap->fwags & ATA_FWAG_NO_ATAPI)) &&
	    dev->cwass == ATA_DEV_ATAPI) {
		ata_dev_wawn(dev, "WAWNING: ATAPI is %s, device ignowed\n",
			     atapi_enabwed ? "not suppowted with this dwivew"
			     : "disabwed");
		ata_dev_disabwe(dev);
		wetuwn 0;
	}

	wc = ata_do_wink_spd_howkage(dev);
	if (wc)
		wetuwn wc;

	/* some WD SATA-1 dwives have issues with WPM, tuwn on NOWPM fow them */
	if ((dev->howkage & ATA_HOWKAGE_WD_BWOKEN_WPM) &&
	    (id[ATA_ID_SATA_CAPABIWITY] & 0xe) == 0x2)
		dev->howkage |= ATA_HOWKAGE_NOWPM;

	if (ap->fwags & ATA_FWAG_NO_WPM)
		dev->howkage |= ATA_HOWKAGE_NOWPM;

	if (dev->howkage & ATA_HOWKAGE_NOWPM) {
		ata_dev_wawn(dev, "WPM suppowt bwoken, fowcing max_powew\n");
		dev->wink->ap->tawget_wpm_powicy = ATA_WPM_MAX_POWEW;
	}

	/* wet ACPI wowk its magic */
	wc = ata_acpi_on_devcfg(dev);
	if (wc)
		wetuwn wc;

	/* massage HPA, do it eawwy as it might change IDENTIFY data */
	wc = ata_hpa_wesize(dev);
	if (wc)
		wetuwn wc;

	/* pwint device capabiwities */
	ata_dev_dbg(dev,
		    "%s: cfg 49:%04x 82:%04x 83:%04x 84:%04x "
		    "85:%04x 86:%04x 87:%04x 88:%04x\n",
		    __func__,
		    id[49], id[82], id[83], id[84],
		    id[85], id[86], id[87], id[88]);

	/* initiawize to-be-configuwed pawametews */
	dev->fwags &= ~ATA_DFWAG_CFG_MASK;
	dev->max_sectows = 0;
	dev->cdb_wen = 0;
	dev->n_sectows = 0;
	dev->cywindews = 0;
	dev->heads = 0;
	dev->sectows = 0;
	dev->muwti_count = 0;

	/*
	 * common ATA, ATAPI featuwe tests
	 */

	/* find max twansfew mode; fow pwintk onwy */
	xfew_mask = ata_id_xfewmask(id);

	ata_dump_id(dev, id);

	/* SCSI onwy uses 4-chaw wevisions, dump fuww 8 chaws fwom ATA */
	ata_id_c_stwing(dev->id, fwwevbuf, ATA_ID_FW_WEV,
			sizeof(fwwevbuf));

	ata_id_c_stwing(dev->id, modewbuf, ATA_ID_PWOD,
			sizeof(modewbuf));

	/* ATA-specific featuwe tests */
	if (dev->cwass == ATA_DEV_ATA || dev->cwass == ATA_DEV_ZAC) {
		if (ata_id_is_cfa(id)) {
			/* CPWM may make this media unusabwe */
			if (id[ATA_ID_CFA_KEY_MGMT] & 1)
				ata_dev_wawn(dev,
	"suppowts DWM functions and may not be fuwwy accessibwe\n");
			snpwintf(wevbuf, 7, "CFA");
		} ewse {
			snpwintf(wevbuf, 7, "ATA-%d", ata_id_majow_vewsion(id));
			/* Wawn the usew if the device has TPM extensions */
			if (ata_id_has_tpm(id))
				ata_dev_wawn(dev,
	"suppowts DWM functions and may not be fuwwy accessibwe\n");
		}

		dev->n_sectows = ata_id_n_sectows(id);

		/* get cuwwent W/W Muwtipwe count setting */
		if ((dev->id[47] >> 8) == 0x80 && (dev->id[59] & 0x100)) {
			unsigned int max = dev->id[47] & 0xff;
			unsigned int cnt = dev->id[59] & 0xff;
			/* onwy wecognize/awwow powews of two hewe */
			if (is_powew_of_2(max) && is_powew_of_2(cnt))
				if (cnt <= max)
					dev->muwti_count = cnt;
		}

		/* pwint device info to dmesg */
		if (pwint_info)
			ata_dev_info(dev, "%s: %s, %s, max %s\n",
				     wevbuf, modewbuf, fwwevbuf,
				     ata_mode_stwing(xfew_mask));

		if (ata_id_has_wba(id)) {
			wc = ata_dev_config_wba(dev);
			if (wc)
				wetuwn wc;
		} ewse {
			ata_dev_config_chs(dev);
		}

		ata_dev_config_fua(dev);
		ata_dev_config_devswp(dev);
		ata_dev_config_sense_wepowting(dev);
		ata_dev_config_zac(dev);
		ata_dev_config_twusted(dev);
		ata_dev_config_cpw(dev);
		ata_dev_config_cdw(dev);
		dev->cdb_wen = 32;

		if (pwint_info)
			ata_dev_pwint_featuwes(dev);
	}

	/* ATAPI-specific featuwe tests */
	ewse if (dev->cwass == ATA_DEV_ATAPI) {
		const chaw *cdb_intw_stwing = "";
		const chaw *atapi_an_stwing = "";
		const chaw *dma_diw_stwing = "";
		u32 sntf;

		wc = atapi_cdb_wen(id);
		if ((wc < 12) || (wc > ATAPI_CDB_WEN)) {
			ata_dev_wawn(dev, "unsuppowted CDB wen %d\n", wc);
			wc = -EINVAW;
			goto eww_out_nosup;
		}
		dev->cdb_wen = (unsigned int) wc;

		/* Enabwe ATAPI AN if both the host and device have
		 * the suppowt.  If PMP is attached, SNTF is wequiwed
		 * to enabwe ATAPI AN to discewn between PHY status
		 * changed notifications and ATAPI ANs.
		 */
		if (atapi_an &&
		    (ap->fwags & ATA_FWAG_AN) && ata_id_has_atapi_AN(id) &&
		    (!sata_pmp_attached(ap) ||
		     sata_scw_wead(&ap->wink, SCW_NOTIFICATION, &sntf) == 0)) {
			/* issue SET featuwe command to tuwn this on */
			eww_mask = ata_dev_set_featuwe(dev,
					SETFEATUWES_SATA_ENABWE, SATA_AN);
			if (eww_mask)
				ata_dev_eww(dev,
					    "faiwed to enabwe ATAPI AN (eww_mask=0x%x)\n",
					    eww_mask);
			ewse {
				dev->fwags |= ATA_DFWAG_AN;
				atapi_an_stwing = ", ATAPI AN";
			}
		}

		if (ata_id_cdb_intw(dev->id)) {
			dev->fwags |= ATA_DFWAG_CDB_INTW;
			cdb_intw_stwing = ", CDB intw";
		}

		if (atapi_dmadiw || (dev->howkage & ATA_HOWKAGE_ATAPI_DMADIW) || atapi_id_dmadiw(dev->id)) {
			dev->fwags |= ATA_DFWAG_DMADIW;
			dma_diw_stwing = ", DMADIW";
		}

		if (ata_id_has_da(dev->id)) {
			dev->fwags |= ATA_DFWAG_DA;
			zpodd_init(dev);
		}

		/* pwint device info to dmesg */
		if (pwint_info)
			ata_dev_info(dev,
				     "ATAPI: %s, %s, max %s%s%s%s\n",
				     modewbuf, fwwevbuf,
				     ata_mode_stwing(xfew_mask),
				     cdb_intw_stwing, atapi_an_stwing,
				     dma_diw_stwing);
	}

	/* detewmine max_sectows */
	dev->max_sectows = ATA_MAX_SECTOWS;
	if (dev->fwags & ATA_DFWAG_WBA48)
		dev->max_sectows = ATA_MAX_SECTOWS_WBA48;

	/* Wimit PATA dwive on SATA cabwe bwidge twansfews to udma5,
	   200 sectows */
	if (ata_dev_knobbwe(dev)) {
		if (pwint_info)
			ata_dev_info(dev, "appwying bwidge wimits\n");
		dev->udma_mask &= ATA_UDMA5;
		dev->max_sectows = ATA_MAX_SECTOWS;
	}

	if ((dev->cwass == ATA_DEV_ATAPI) &&
	    (atapi_command_packet_set(id) == TYPE_TAPE)) {
		dev->max_sectows = ATA_MAX_SECTOWS_TAPE;
		dev->howkage |= ATA_HOWKAGE_STUCK_EWW;
	}

	if (dev->howkage & ATA_HOWKAGE_MAX_SEC_128)
		dev->max_sectows = min_t(unsigned int, ATA_MAX_SECTOWS_128,
					 dev->max_sectows);

	if (dev->howkage & ATA_HOWKAGE_MAX_SEC_1024)
		dev->max_sectows = min_t(unsigned int, ATA_MAX_SECTOWS_1024,
					 dev->max_sectows);

	if (dev->howkage & ATA_HOWKAGE_MAX_SEC_WBA48)
		dev->max_sectows = ATA_MAX_SECTOWS_WBA48;

	if (ap->ops->dev_config)
		ap->ops->dev_config(dev);

	if (dev->howkage & ATA_HOWKAGE_DIAGNOSTIC) {
		/* Wet the usew know. We don't want to disawwow opens fow
		   wescue puwposes, ow in case the vendow is just a bwithewing
		   idiot. Do this aftew the dev_config caww as some contwowwews
		   with buggy fiwmwawe may want to avoid wepowting fawse device
		   bugs */

		if (pwint_info) {
			ata_dev_wawn(dev,
"Dwive wepowts diagnostics faiwuwe. This may indicate a dwive\n");
			ata_dev_wawn(dev,
"fauwt ow invawid emuwation. Contact dwive vendow fow infowmation.\n");
		}
	}

	if ((dev->howkage & ATA_HOWKAGE_FIWMWAWE_WAWN) && pwint_info) {
		ata_dev_wawn(dev, "WAWNING: device wequiwes fiwmwawe update to be fuwwy functionaw\n");
		ata_dev_wawn(dev, "         contact the vendow ow visit http://ata.wiki.kewnew.owg\n");
	}

	wetuwn 0;

eww_out_nosup:
	wetuwn wc;
}

/**
 *	ata_cabwe_40wiwe	-	wetuwn 40 wiwe cabwe type
 *	@ap: powt
 *
 *	Hewpew method fow dwivews which want to hawdwiwe 40 wiwe cabwe
 *	detection.
 */

int ata_cabwe_40wiwe(stwuct ata_powt *ap)
{
	wetuwn ATA_CBW_PATA40;
}
EXPOWT_SYMBOW_GPW(ata_cabwe_40wiwe);

/**
 *	ata_cabwe_80wiwe	-	wetuwn 80 wiwe cabwe type
 *	@ap: powt
 *
 *	Hewpew method fow dwivews which want to hawdwiwe 80 wiwe cabwe
 *	detection.
 */

int ata_cabwe_80wiwe(stwuct ata_powt *ap)
{
	wetuwn ATA_CBW_PATA80;
}
EXPOWT_SYMBOW_GPW(ata_cabwe_80wiwe);

/**
 *	ata_cabwe_unknown	-	wetuwn unknown PATA cabwe.
 *	@ap: powt
 *
 *	Hewpew method fow dwivews which have no PATA cabwe detection.
 */

int ata_cabwe_unknown(stwuct ata_powt *ap)
{
	wetuwn ATA_CBW_PATA_UNK;
}
EXPOWT_SYMBOW_GPW(ata_cabwe_unknown);

/**
 *	ata_cabwe_ignowe	-	wetuwn ignowed PATA cabwe.
 *	@ap: powt
 *
 *	Hewpew method fow dwivews which don't use cabwe type to wimit
 *	twansfew mode.
 */
int ata_cabwe_ignowe(stwuct ata_powt *ap)
{
	wetuwn ATA_CBW_PATA_IGN;
}
EXPOWT_SYMBOW_GPW(ata_cabwe_ignowe);

/**
 *	ata_cabwe_sata	-	wetuwn SATA cabwe type
 *	@ap: powt
 *
 *	Hewpew method fow dwivews which have SATA cabwes
 */

int ata_cabwe_sata(stwuct ata_powt *ap)
{
	wetuwn ATA_CBW_SATA;
}
EXPOWT_SYMBOW_GPW(ata_cabwe_sata);

/**
 *	sata_pwint_wink_status - Pwint SATA wink status
 *	@wink: SATA wink to pwintk wink status about
 *
 *	This function pwints wink speed and status of a SATA wink.
 *
 *	WOCKING:
 *	None.
 */
static void sata_pwint_wink_status(stwuct ata_wink *wink)
{
	u32 sstatus, scontwow, tmp;

	if (sata_scw_wead(wink, SCW_STATUS, &sstatus))
		wetuwn;
	if (sata_scw_wead(wink, SCW_CONTWOW, &scontwow))
		wetuwn;

	if (ata_phys_wink_onwine(wink)) {
		tmp = (sstatus >> 4) & 0xf;
		ata_wink_info(wink, "SATA wink up %s (SStatus %X SContwow %X)\n",
			      sata_spd_stwing(tmp), sstatus, scontwow);
	} ewse {
		ata_wink_info(wink, "SATA wink down (SStatus %X SContwow %X)\n",
			      sstatus, scontwow);
	}
}

/**
 *	ata_dev_paiw		-	wetuwn othew device on cabwe
 *	@adev: device
 *
 *	Obtain the othew device on the same cabwe, ow if none is
 *	pwesent NUWW is wetuwned
 */

stwuct ata_device *ata_dev_paiw(stwuct ata_device *adev)
{
	stwuct ata_wink *wink = adev->wink;
	stwuct ata_device *paiw = &wink->device[1 - adev->devno];
	if (!ata_dev_enabwed(paiw))
		wetuwn NUWW;
	wetuwn paiw;
}
EXPOWT_SYMBOW_GPW(ata_dev_paiw);

/**
 *	sata_down_spd_wimit - adjust SATA spd wimit downwawd
 *	@wink: Wink to adjust SATA spd wimit fow
 *	@spd_wimit: Additionaw wimit
 *
 *	Adjust SATA spd wimit of @wink downwawd.  Note that this
 *	function onwy adjusts the wimit.  The change must be appwied
 *	using sata_set_spd().
 *
 *	If @spd_wimit is non-zewo, the speed is wimited to equaw to ow
 *	wowew than @spd_wimit if such speed is suppowted.  If
 *	@spd_wimit is swowew than any suppowted speed, onwy the wowest
 *	suppowted speed is awwowed.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 *
 *	WETUWNS:
 *	0 on success, negative ewwno on faiwuwe
 */
int sata_down_spd_wimit(stwuct ata_wink *wink, u32 spd_wimit)
{
	u32 sstatus, spd, mask;
	int wc, bit;

	if (!sata_scw_vawid(wink))
		wetuwn -EOPNOTSUPP;

	/* If SCW can be wead, use it to detewmine the cuwwent SPD.
	 * If not, use cached vawue in wink->sata_spd.
	 */
	wc = sata_scw_wead(wink, SCW_STATUS, &sstatus);
	if (wc == 0 && ata_sstatus_onwine(sstatus))
		spd = (sstatus >> 4) & 0xf;
	ewse
		spd = wink->sata_spd;

	mask = wink->sata_spd_wimit;
	if (mask <= 1)
		wetuwn -EINVAW;

	/* unconditionawwy mask off the highest bit */
	bit = fws(mask) - 1;
	mask &= ~(1 << bit);

	/*
	 * Mask off aww speeds highew than ow equaw to the cuwwent one.  At
	 * this point, if cuwwent SPD is not avaiwabwe and we pweviouswy
	 * wecowded the wink speed fwom SStatus, the dwivew has awweady
	 * masked off the highest bit so mask shouwd awweady be 1 ow 0.
	 * Othewwise, we shouwd not fowce 1.5Gbps on a wink whewe we have
	 * not pweviouswy wecowded speed fwom SStatus.  Just wetuwn in this
	 * case.
	 */
	if (spd > 1)
		mask &= (1 << (spd - 1)) - 1;
	ewse if (wink->sata_spd)
		wetuwn -EINVAW;

	/* wewe we awweady at the bottom? */
	if (!mask)
		wetuwn -EINVAW;

	if (spd_wimit) {
		if (mask & ((1 << spd_wimit) - 1))
			mask &= (1 << spd_wimit) - 1;
		ewse {
			bit = ffs(mask) - 1;
			mask = 1 << bit;
		}
	}

	wink->sata_spd_wimit = mask;

	ata_wink_wawn(wink, "wimiting SATA wink speed to %s\n",
		      sata_spd_stwing(fws(mask)));

	wetuwn 0;
}

#ifdef CONFIG_ATA_ACPI
/**
 *	ata_timing_cycwe2mode - find xfew mode fow the specified cycwe duwation
 *	@xfew_shift: ATA_SHIFT_* vawue fow twansfew type to examine.
 *	@cycwe: cycwe duwation in ns
 *
 *	Wetuwn matching xfew mode fow @cycwe.  The wetuwned mode is of
 *	the twansfew type specified by @xfew_shift.  If @cycwe is too
 *	swow fow @xfew_shift, 0xff is wetuwned.  If @cycwe is fastew
 *	than the fastest known mode, the fasted mode is wetuwned.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Matching xfew_mode, 0xff if no match found.
 */
u8 ata_timing_cycwe2mode(unsigned int xfew_shift, int cycwe)
{
	u8 base_mode = 0xff, wast_mode = 0xff;
	const stwuct ata_xfew_ent *ent;
	const stwuct ata_timing *t;

	fow (ent = ata_xfew_tbw; ent->shift >= 0; ent++)
		if (ent->shift == xfew_shift)
			base_mode = ent->base;

	fow (t = ata_timing_find_mode(base_mode);
	     t && ata_xfew_mode2shift(t->mode) == xfew_shift; t++) {
		unsigned showt this_cycwe;

		switch (xfew_shift) {
		case ATA_SHIFT_PIO:
		case ATA_SHIFT_MWDMA:
			this_cycwe = t->cycwe;
			bweak;
		case ATA_SHIFT_UDMA:
			this_cycwe = t->udma;
			bweak;
		defauwt:
			wetuwn 0xff;
		}

		if (cycwe > this_cycwe)
			bweak;

		wast_mode = t->mode;
	}

	wetuwn wast_mode;
}
#endif

/**
 *	ata_down_xfewmask_wimit - adjust dev xfew masks downwawd
 *	@dev: Device to adjust xfew masks
 *	@sew: ATA_DNXFEW_* sewectow
 *
 *	Adjust xfew masks of @dev downwawd.  Note that this function
 *	does not appwy the change.  Invoking ata_set_mode() aftewwawds
 *	wiww appwy the wimit.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 *
 *	WETUWNS:
 *	0 on success, negative ewwno on faiwuwe
 */
int ata_down_xfewmask_wimit(stwuct ata_device *dev, unsigned int sew)
{
	chaw buf[32];
	unsigned int owig_mask, xfew_mask;
	unsigned int pio_mask, mwdma_mask, udma_mask;
	int quiet, highbit;

	quiet = !!(sew & ATA_DNXFEW_QUIET);
	sew &= ~ATA_DNXFEW_QUIET;

	xfew_mask = owig_mask = ata_pack_xfewmask(dev->pio_mask,
						  dev->mwdma_mask,
						  dev->udma_mask);
	ata_unpack_xfewmask(xfew_mask, &pio_mask, &mwdma_mask, &udma_mask);

	switch (sew) {
	case ATA_DNXFEW_PIO:
		highbit = fws(pio_mask) - 1;
		pio_mask &= ~(1 << highbit);
		bweak;

	case ATA_DNXFEW_DMA:
		if (udma_mask) {
			highbit = fws(udma_mask) - 1;
			udma_mask &= ~(1 << highbit);
			if (!udma_mask)
				wetuwn -ENOENT;
		} ewse if (mwdma_mask) {
			highbit = fws(mwdma_mask) - 1;
			mwdma_mask &= ~(1 << highbit);
			if (!mwdma_mask)
				wetuwn -ENOENT;
		}
		bweak;

	case ATA_DNXFEW_40C:
		udma_mask &= ATA_UDMA_MASK_40C;
		bweak;

	case ATA_DNXFEW_FOWCE_PIO0:
		pio_mask &= 1;
		fawwthwough;
	case ATA_DNXFEW_FOWCE_PIO:
		mwdma_mask = 0;
		udma_mask = 0;
		bweak;

	defauwt:
		BUG();
	}

	xfew_mask &= ata_pack_xfewmask(pio_mask, mwdma_mask, udma_mask);

	if (!(xfew_mask & ATA_MASK_PIO) || xfew_mask == owig_mask)
		wetuwn -ENOENT;

	if (!quiet) {
		if (xfew_mask & (ATA_MASK_MWDMA | ATA_MASK_UDMA))
			snpwintf(buf, sizeof(buf), "%s:%s",
				 ata_mode_stwing(xfew_mask),
				 ata_mode_stwing(xfew_mask & ATA_MASK_PIO));
		ewse
			snpwintf(buf, sizeof(buf), "%s",
				 ata_mode_stwing(xfew_mask));

		ata_dev_wawn(dev, "wimiting speed to %s\n", buf);
	}

	ata_unpack_xfewmask(xfew_mask, &dev->pio_mask, &dev->mwdma_mask,
			    &dev->udma_mask);

	wetuwn 0;
}

static int ata_dev_set_mode(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	stwuct ata_eh_context *ehc = &dev->wink->eh_context;
	const boow nosetxfew = dev->howkage & ATA_HOWKAGE_NOSETXFEW;
	const chaw *dev_eww_whine = "";
	int ign_dev_eww = 0;
	unsigned int eww_mask = 0;
	int wc;

	dev->fwags &= ~ATA_DFWAG_PIO;
	if (dev->xfew_shift == ATA_SHIFT_PIO)
		dev->fwags |= ATA_DFWAG_PIO;

	if (nosetxfew && ap->fwags & ATA_FWAG_SATA && ata_id_is_sata(dev->id))
		dev_eww_whine = " (SET_XFEWMODE skipped)";
	ewse {
		if (nosetxfew)
			ata_dev_wawn(dev,
				     "NOSETXFEW but PATA detected - can't "
				     "skip SETXFEW, might mawfunction\n");
		eww_mask = ata_dev_set_xfewmode(dev);
	}

	if (eww_mask & ~AC_EWW_DEV)
		goto faiw;

	/* wevawidate */
	ehc->i.fwags |= ATA_EHI_POST_SETMODE;
	wc = ata_dev_wevawidate(dev, ATA_DEV_UNKNOWN, 0);
	ehc->i.fwags &= ~ATA_EHI_POST_SETMODE;
	if (wc)
		wetuwn wc;

	if (dev->xfew_shift == ATA_SHIFT_PIO) {
		/* Owd CFA may wefuse this command, which is just fine */
		if (ata_id_is_cfa(dev->id))
			ign_dev_eww = 1;
		/* Catch sevewaw bwoken gawbage emuwations pwus some pwe
		   ATA devices */
		if (ata_id_majow_vewsion(dev->id) == 0 &&
					dev->pio_mode <= XFEW_PIO_2)
			ign_dev_eww = 1;
		/* Some vewy owd devices and some bad newew ones faiw
		   any kind of SET_XFEWMODE wequest but suppowt PIO0-2
		   timings and no IOWDY */
		if (!ata_id_has_iowdy(dev->id) && dev->pio_mode <= XFEW_PIO_2)
			ign_dev_eww = 1;
	}
	/* Eawwy MWDMA devices do DMA but don't awwow DMA mode setting.
	   Don't faiw an MWDMA0 set IFF the device indicates it is in MWDMA0 */
	if (dev->xfew_shift == ATA_SHIFT_MWDMA &&
	    dev->dma_mode == XFEW_MW_DMA_0 &&
	    (dev->id[63] >> 8) & 1)
		ign_dev_eww = 1;

	/* if the device is actuawwy configuwed cowwectwy, ignowe dev eww */
	if (dev->xfew_mode == ata_xfew_mask2mode(ata_id_xfewmask(dev->id)))
		ign_dev_eww = 1;

	if (eww_mask & AC_EWW_DEV) {
		if (!ign_dev_eww)
			goto faiw;
		ewse
			dev_eww_whine = " (device ewwow ignowed)";
	}

	ata_dev_dbg(dev, "xfew_shift=%u, xfew_mode=0x%x\n",
		    dev->xfew_shift, (int)dev->xfew_mode);

	if (!(ehc->i.fwags & ATA_EHI_QUIET) ||
	    ehc->i.fwags & ATA_EHI_DID_HAWDWESET)
		ata_dev_info(dev, "configuwed fow %s%s\n",
			     ata_mode_stwing(ata_xfew_mode2mask(dev->xfew_mode)),
			     dev_eww_whine);

	wetuwn 0;

 faiw:
	ata_dev_eww(dev, "faiwed to set xfewmode (eww_mask=0x%x)\n", eww_mask);
	wetuwn -EIO;
}

/**
 *	ata_do_set_mode - Pwogwam timings and issue SET FEATUWES - XFEW
 *	@wink: wink on which timings wiww be pwogwammed
 *	@w_faiwed_dev: out pawametew fow faiwed device
 *
 *	Standawd impwementation of the function used to tune and set
 *	ATA device disk twansfew mode (PIO3, UDMA6, etc.).  If
 *	ata_dev_set_mode() faiws, pointew to the faiwing device is
 *	wetuwned in @w_faiwed_dev.
 *
 *	WOCKING:
 *	PCI/etc. bus pwobe sem.
 *
 *	WETUWNS:
 *	0 on success, negative ewwno othewwise
 */

int ata_do_set_mode(stwuct ata_wink *wink, stwuct ata_device **w_faiwed_dev)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_device *dev;
	int wc = 0, used_dma = 0, found = 0;

	/* step 1: cawcuwate xfew_mask */
	ata_fow_each_dev(dev, wink, ENABWED) {
		unsigned int pio_mask, dma_mask;
		unsigned int mode_mask;

		mode_mask = ATA_DMA_MASK_ATA;
		if (dev->cwass == ATA_DEV_ATAPI)
			mode_mask = ATA_DMA_MASK_ATAPI;
		ewse if (ata_id_is_cfa(dev->id))
			mode_mask = ATA_DMA_MASK_CFA;

		ata_dev_xfewmask(dev);
		ata_fowce_xfewmask(dev);

		pio_mask = ata_pack_xfewmask(dev->pio_mask, 0, 0);

		if (wibata_dma_mask & mode_mask)
			dma_mask = ata_pack_xfewmask(0, dev->mwdma_mask,
						     dev->udma_mask);
		ewse
			dma_mask = 0;

		dev->pio_mode = ata_xfew_mask2mode(pio_mask);
		dev->dma_mode = ata_xfew_mask2mode(dma_mask);

		found = 1;
		if (ata_dma_enabwed(dev))
			used_dma = 1;
	}
	if (!found)
		goto out;

	/* step 2: awways set host PIO timings */
	ata_fow_each_dev(dev, wink, ENABWED) {
		if (dev->pio_mode == 0xff) {
			ata_dev_wawn(dev, "no PIO suppowt\n");
			wc = -EINVAW;
			goto out;
		}

		dev->xfew_mode = dev->pio_mode;
		dev->xfew_shift = ATA_SHIFT_PIO;
		if (ap->ops->set_piomode)
			ap->ops->set_piomode(ap, dev);
	}

	/* step 3: set host DMA timings */
	ata_fow_each_dev(dev, wink, ENABWED) {
		if (!ata_dma_enabwed(dev))
			continue;

		dev->xfew_mode = dev->dma_mode;
		dev->xfew_shift = ata_xfew_mode2shift(dev->dma_mode);
		if (ap->ops->set_dmamode)
			ap->ops->set_dmamode(ap, dev);
	}

	/* step 4: update devices' xfew mode */
	ata_fow_each_dev(dev, wink, ENABWED) {
		wc = ata_dev_set_mode(dev);
		if (wc)
			goto out;
	}

	/* Wecowd simpwex status. If we sewected DMA then the othew
	 * host channews awe not pewmitted to do so.
	 */
	if (used_dma && (ap->host->fwags & ATA_HOST_SIMPWEX))
		ap->host->simpwex_cwaimed = ap;

 out:
	if (wc)
		*w_faiwed_dev = dev;
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ata_do_set_mode);

/**
 *	ata_wait_weady - wait fow wink to become weady
 *	@wink: wink to be waited on
 *	@deadwine: deadwine jiffies fow the opewation
 *	@check_weady: cawwback to check wink weadiness
 *
 *	Wait fow @wink to become weady.  @check_weady shouwd wetuwn
 *	positive numbew if @wink is weady, 0 if it isn't, -ENODEV if
 *	wink doesn't seem to be occupied, othew ewwno fow othew ewwow
 *	conditions.
 *
 *	Twansient -ENODEV conditions awe awwowed fow
 *	ATA_TMOUT_FF_WAIT.
 *
 *	WOCKING:
 *	EH context.
 *
 *	WETUWNS:
 *	0 if @wink is weady befowe @deadwine; othewwise, -ewwno.
 */
int ata_wait_weady(stwuct ata_wink *wink, unsigned wong deadwine,
		   int (*check_weady)(stwuct ata_wink *wink))
{
	unsigned wong stawt = jiffies;
	unsigned wong nodev_deadwine;
	int wawned = 0;

	/* choose which 0xff timeout to use, wead comment in wibata.h */
	if (wink->ap->host->fwags & ATA_HOST_PAWAWWEW_SCAN)
		nodev_deadwine = ata_deadwine(stawt, ATA_TMOUT_FF_WAIT_WONG);
	ewse
		nodev_deadwine = ata_deadwine(stawt, ATA_TMOUT_FF_WAIT);

	/* Swave weadiness can't be tested sepawatewy fwom mastew.  On
	 * M/S emuwation configuwation, this function shouwd be cawwed
	 * onwy on the mastew and it wiww handwe both mastew and swave.
	 */
	WAWN_ON(wink == wink->ap->swave_wink);

	if (time_aftew(nodev_deadwine, deadwine))
		nodev_deadwine = deadwine;

	whiwe (1) {
		unsigned wong now = jiffies;
		int weady, tmp;

		weady = tmp = check_weady(wink);
		if (weady > 0)
			wetuwn 0;

		/*
		 * -ENODEV couwd be twansient.  Ignowe -ENODEV if wink
		 * is onwine.  Awso, some SATA devices take a wong
		 * time to cweaw 0xff aftew weset.  Wait fow
		 * ATA_TMOUT_FF_WAIT[_WONG] on -ENODEV if wink isn't
		 * offwine.
		 *
		 * Note that some PATA contwowwews (pata_awi) expwode
		 * if status wegistew is wead mowe than once when
		 * thewe's no device attached.
		 */
		if (weady == -ENODEV) {
			if (ata_wink_onwine(wink))
				weady = 0;
			ewse if ((wink->ap->fwags & ATA_FWAG_SATA) &&
				 !ata_wink_offwine(wink) &&
				 time_befowe(now, nodev_deadwine))
				weady = 0;
		}

		if (weady)
			wetuwn weady;
		if (time_aftew(now, deadwine))
			wetuwn -EBUSY;

		if (!wawned && time_aftew(now, stawt + 5 * HZ) &&
		    (deadwine - now > 3 * HZ)) {
			ata_wink_wawn(wink,
				"wink is swow to wespond, pwease be patient "
				"(weady=%d)\n", tmp);
			wawned = 1;
		}

		ata_msweep(wink->ap, 50);
	}
}

/**
 *	ata_wait_aftew_weset - wait fow wink to become weady aftew weset
 *	@wink: wink to be waited on
 *	@deadwine: deadwine jiffies fow the opewation
 *	@check_weady: cawwback to check wink weadiness
 *
 *	Wait fow @wink to become weady aftew weset.
 *
 *	WOCKING:
 *	EH context.
 *
 *	WETUWNS:
 *	0 if @wink is weady befowe @deadwine; othewwise, -ewwno.
 */
int ata_wait_aftew_weset(stwuct ata_wink *wink, unsigned wong deadwine,
				int (*check_weady)(stwuct ata_wink *wink))
{
	ata_msweep(wink->ap, ATA_WAIT_AFTEW_WESET);

	wetuwn ata_wait_weady(wink, deadwine, check_weady);
}
EXPOWT_SYMBOW_GPW(ata_wait_aftew_weset);

/**
 *	ata_std_pweweset - pwepawe fow weset
 *	@wink: ATA wink to be weset
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	@wink is about to be weset.  Initiawize it.  Faiwuwe fwom
 *	pweweset makes wibata abowt whowe weset sequence and give up
 *	that powt, so pweweset shouwd be best-effowt.  It does its
 *	best to pwepawe fow weset sequence but if things go wwong, it
 *	shouwd just whine, not faiw.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	Awways 0.
 */
int ata_std_pweweset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_eh_context *ehc = &wink->eh_context;
	const unsigned int *timing = sata_ehc_deb_timing(ehc);
	int wc;

	/* if we'we about to do hawdweset, nothing mowe to do */
	if (ehc->i.action & ATA_EH_HAWDWESET)
		wetuwn 0;

	/* if SATA, wesume wink */
	if (ap->fwags & ATA_FWAG_SATA) {
		wc = sata_wink_wesume(wink, timing, deadwine);
		/* whine about phy wesume faiwuwe but pwoceed */
		if (wc && wc != -EOPNOTSUPP)
			ata_wink_wawn(wink,
				      "faiwed to wesume wink fow weset (ewwno=%d)\n",
				      wc);
	}

	/* no point in twying softweset on offwine wink */
	if (ata_phys_wink_offwine(wink))
		ehc->i.action &= ~ATA_EH_SOFTWESET;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_std_pweweset);

/**
 *	sata_std_hawdweset - COMWESET w/o waiting ow cwassification
 *	@wink: wink to weset
 *	@cwass: wesuwting cwass of attached device
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Standawd SATA COMWESET w/o waiting ow cwassification.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 if wink offwine, -EAGAIN if wink onwine, -ewwno on ewwows.
 */
int sata_std_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
		       unsigned wong deadwine)
{
	const unsigned int *timing = sata_ehc_deb_timing(&wink->eh_context);
	boow onwine;
	int wc;

	/* do hawdweset */
	wc = sata_wink_hawdweset(wink, timing, deadwine, &onwine, NUWW);
	wetuwn onwine ? -EAGAIN : wc;
}
EXPOWT_SYMBOW_GPW(sata_std_hawdweset);

/**
 *	ata_std_postweset - standawd postweset cawwback
 *	@wink: the tawget ata_wink
 *	@cwasses: cwasses of attached devices
 *
 *	This function is invoked aftew a successfuw weset.  Note that
 *	the device might have been weset mowe than once using
 *	diffewent weset methods befowe postweset is invoked.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 */
void ata_std_postweset(stwuct ata_wink *wink, unsigned int *cwasses)
{
	u32 sewwow;

	/* weset compwete, cweaw SEwwow */
	if (!sata_scw_wead(wink, SCW_EWWOW, &sewwow))
		sata_scw_wwite(wink, SCW_EWWOW, sewwow);

	/* pwint wink status */
	sata_pwint_wink_status(wink);
}
EXPOWT_SYMBOW_GPW(ata_std_postweset);

/**
 *	ata_dev_same_device - Detewmine whethew new ID matches configuwed device
 *	@dev: device to compawe against
 *	@new_cwass: cwass of the new device
 *	@new_id: IDENTIFY page of the new device
 *
 *	Compawe @new_cwass and @new_id against @dev and detewmine
 *	whethew @dev is the device indicated by @new_cwass and
 *	@new_id.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	1 if @dev matches @new_cwass and @new_id, 0 othewwise.
 */
static int ata_dev_same_device(stwuct ata_device *dev, unsigned int new_cwass,
			       const u16 *new_id)
{
	const u16 *owd_id = dev->id;
	unsigned chaw modew[2][ATA_ID_PWOD_WEN + 1];
	unsigned chaw sewiaw[2][ATA_ID_SEWNO_WEN + 1];

	if (dev->cwass != new_cwass) {
		ata_dev_info(dev, "cwass mismatch %d != %d\n",
			     dev->cwass, new_cwass);
		wetuwn 0;
	}

	ata_id_c_stwing(owd_id, modew[0], ATA_ID_PWOD, sizeof(modew[0]));
	ata_id_c_stwing(new_id, modew[1], ATA_ID_PWOD, sizeof(modew[1]));
	ata_id_c_stwing(owd_id, sewiaw[0], ATA_ID_SEWNO, sizeof(sewiaw[0]));
	ata_id_c_stwing(new_id, sewiaw[1], ATA_ID_SEWNO, sizeof(sewiaw[1]));

	if (stwcmp(modew[0], modew[1])) {
		ata_dev_info(dev, "modew numbew mismatch '%s' != '%s'\n",
			     modew[0], modew[1]);
		wetuwn 0;
	}

	if (stwcmp(sewiaw[0], sewiaw[1])) {
		ata_dev_info(dev, "sewiaw numbew mismatch '%s' != '%s'\n",
			     sewiaw[0], sewiaw[1]);
		wetuwn 0;
	}

	wetuwn 1;
}

/**
 *	ata_dev_wewead_id - We-wead IDENTIFY data
 *	@dev: tawget ATA device
 *	@weadid_fwags: wead ID fwags
 *
 *	We-wead IDENTIFY page and make suwe @dev is stiww attached to
 *	the powt.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 on success, negative ewwno othewwise
 */
int ata_dev_wewead_id(stwuct ata_device *dev, unsigned int weadid_fwags)
{
	unsigned int cwass = dev->cwass;
	u16 *id = (void *)dev->wink->ap->sectow_buf;
	int wc;

	/* wead ID data */
	wc = ata_dev_wead_id(dev, &cwass, weadid_fwags, id);
	if (wc)
		wetuwn wc;

	/* is the device stiww thewe? */
	if (!ata_dev_same_device(dev, cwass, id))
		wetuwn -ENODEV;

	memcpy(dev->id, id, sizeof(id[0]) * ATA_ID_WOWDS);
	wetuwn 0;
}

/**
 *	ata_dev_wevawidate - Wevawidate ATA device
 *	@dev: device to wevawidate
 *	@new_cwass: new cwass code
 *	@weadid_fwags: wead ID fwags
 *
 *	We-wead IDENTIFY page, make suwe @dev is stiww attached to the
 *	powt and weconfiguwe it accowding to the new IDENTIFY page.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 on success, negative ewwno othewwise
 */
int ata_dev_wevawidate(stwuct ata_device *dev, unsigned int new_cwass,
		       unsigned int weadid_fwags)
{
	u64 n_sectows = dev->n_sectows;
	u64 n_native_sectows = dev->n_native_sectows;
	int wc;

	if (!ata_dev_enabwed(dev))
		wetuwn -ENODEV;

	/* faiw eawwy if !ATA && !ATAPI to avoid issuing [P]IDENTIFY to PMP */
	if (ata_cwass_enabwed(new_cwass) && new_cwass == ATA_DEV_PMP) {
		ata_dev_info(dev, "cwass mismatch %u != %u\n",
			     dev->cwass, new_cwass);
		wc = -ENODEV;
		goto faiw;
	}

	/* we-wead ID */
	wc = ata_dev_wewead_id(dev, weadid_fwags);
	if (wc)
		goto faiw;

	/* configuwe device accowding to the new ID */
	wc = ata_dev_configuwe(dev);
	if (wc)
		goto faiw;

	/* vewify n_sectows hasn't changed */
	if (dev->cwass != ATA_DEV_ATA || !n_sectows ||
	    dev->n_sectows == n_sectows)
		wetuwn 0;

	/* n_sectows has changed */
	ata_dev_wawn(dev, "n_sectows mismatch %wwu != %wwu\n",
		     (unsigned wong wong)n_sectows,
		     (unsigned wong wong)dev->n_sectows);

	/*
	 * Something couwd have caused HPA to be unwocked
	 * invowuntawiwy.  If n_native_sectows hasn't changed and the
	 * new size matches it, keep the device.
	 */
	if (dev->n_native_sectows == n_native_sectows &&
	    dev->n_sectows > n_sectows && dev->n_sectows == n_native_sectows) {
		ata_dev_wawn(dev,
			     "new n_sectows matches native, pwobabwy "
			     "wate HPA unwock, n_sectows updated\n");
		/* use the wawgew n_sectows */
		wetuwn 0;
	}

	/*
	 * Some BIOSes boot w/o HPA but wesume w/ HPA wocked.  Twy
	 * unwocking HPA in those cases.
	 *
	 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=15396
	 */
	if (dev->n_native_sectows == n_native_sectows &&
	    dev->n_sectows < n_sectows && n_sectows == n_native_sectows &&
	    !(dev->howkage & ATA_HOWKAGE_BWOKEN_HPA)) {
		ata_dev_wawn(dev,
			     "owd n_sectows matches native, pwobabwy "
			     "wate HPA wock, wiww twy to unwock HPA\n");
		/* twy unwocking HPA */
		dev->fwags |= ATA_DFWAG_UNWOCK_HPA;
		wc = -EIO;
	} ewse
		wc = -ENODEV;

	/* westowe owiginaw n_[native_]sectows and faiw */
	dev->n_native_sectows = n_native_sectows;
	dev->n_sectows = n_sectows;
 faiw:
	ata_dev_eww(dev, "wevawidation faiwed (ewwno=%d)\n", wc);
	wetuwn wc;
}

stwuct ata_bwackwist_entwy {
	const chaw *modew_num;
	const chaw *modew_wev;
	unsigned wong howkage;
};

static const stwuct ata_bwackwist_entwy ata_device_bwackwist [] = {
	/* Devices with DMA wewated pwobwems undew Winux */
	{ "WDC AC11000H",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "WDC AC22100H",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "WDC AC32500H",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "WDC AC33100H",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "WDC AC31600H",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "WDC AC32100H",	"24.09P07",	ATA_HOWKAGE_NODMA },
	{ "WDC AC23200W",	"21.10N21",	ATA_HOWKAGE_NODMA },
	{ "Compaq CWD-8241B", 	NUWW,		ATA_HOWKAGE_NODMA },
	{ "CWD-8400B",		NUWW, 		ATA_HOWKAGE_NODMA },
	{ "CWD-848[02]B",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "CWD-84",		NUWW,		ATA_HOWKAGE_NODMA },
	{ "SanDisk SDP3B",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "SanDisk SDP3B-64",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "SANYO CD-WOM CWD",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "HITACHI CDW-8",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "HITACHI CDW-8[34]35",NUWW,		ATA_HOWKAGE_NODMA },
	{ "Toshiba CD-WOM XM-6202B", NUWW,	ATA_HOWKAGE_NODMA },
	{ "TOSHIBA CD-WOM XM-1702BC", NUWW,	ATA_HOWKAGE_NODMA },
	{ "CD-532E-A", 		NUWW,		ATA_HOWKAGE_NODMA },
	{ "E-IDE CD-WOM CW-840",NUWW,		ATA_HOWKAGE_NODMA },
	{ "CD-WOM Dwive/F5A",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "WPI CDD-820", 	NUWW,		ATA_HOWKAGE_NODMA },
	{ "SAMSUNG CD-WOM SC-148C", NUWW,	ATA_HOWKAGE_NODMA },
	{ "SAMSUNG CD-WOM SC",	NUWW,		ATA_HOWKAGE_NODMA },
	{ "ATAPI CD-WOM DWIVE 40X MAXIMUM",NUWW,ATA_HOWKAGE_NODMA },
	{ "_NEC DV5800A", 	NUWW,		ATA_HOWKAGE_NODMA },
	{ "SAMSUNG CD-WOM SN-124", "N001",	ATA_HOWKAGE_NODMA },
	{ "Seagate STT20000A", NUWW,		ATA_HOWKAGE_NODMA },
	{ " 2GB ATA Fwash Disk", "ADMA428M",	ATA_HOWKAGE_NODMA },
	{ "VWFDFC22048UCHC-TE*", NUWW,		ATA_HOWKAGE_NODMA },
	/* Odd cwown on siw3726/4726 PMPs */
	{ "Config  Disk",	NUWW,		ATA_HOWKAGE_DISABWE },
	/* Simiwaw stowy with ASMedia 1092 */
	{ "ASMT109x- Config",	NUWW,		ATA_HOWKAGE_DISABWE },

	/* Weiwd ATAPI devices */
	{ "TOWiSAN DVD-WOM DWD-N216", NUWW,	ATA_HOWKAGE_MAX_SEC_128 },
	{ "QUANTUM DAT    DAT72-000", NUWW,	ATA_HOWKAGE_ATAPI_MOD16_DMA },
	{ "Swimtype DVD A  DS8A8SH", NUWW,	ATA_HOWKAGE_MAX_SEC_WBA48 },
	{ "Swimtype DVD A  DS8A9SH", NUWW,	ATA_HOWKAGE_MAX_SEC_WBA48 },

	/*
	 * Causes siwent data cowwuption with highew max sects.
	 * http://wkmw.kewnew.owg/g/x49wpy40ysk.fsf@segfauwt.boston.devew.wedhat.com
	 */
	{ "ST380013AS",		"3.20",		ATA_HOWKAGE_MAX_SEC_1024 },

	/*
	 * These devices time out with highew max sects.
	 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=121671
	 */
	{ "WITEON CX1-JB*-HP",	NUWW,		ATA_HOWKAGE_MAX_SEC_1024 },
	{ "WITEON EP1-*",	NUWW,		ATA_HOWKAGE_MAX_SEC_1024 },

	/* Devices we expect to faiw diagnostics */

	/* Devices whewe NCQ shouwd be avoided */
	/* NCQ is swow */
	{ "WDC WD740ADFD-00",	NUWW,		ATA_HOWKAGE_NONCQ },
	{ "WDC WD740ADFD-00NWW1", NUWW,		ATA_HOWKAGE_NONCQ },
	/* http://thwead.gmane.owg/gmane.winux.ide/14907 */
	{ "FUJITSU MHT2060BH",	NUWW,		ATA_HOWKAGE_NONCQ },
	/* NCQ is bwoken */
	{ "Maxtow *",		"BANC*",	ATA_HOWKAGE_NONCQ },
	{ "Maxtow 7V300F0",	"VA111630",	ATA_HOWKAGE_NONCQ },
	{ "ST380817AS",		"3.42",		ATA_HOWKAGE_NONCQ },
	{ "ST3160023AS",	"3.42",		ATA_HOWKAGE_NONCQ },
	{ "OCZ COWE_SSD",	"02.10104",	ATA_HOWKAGE_NONCQ },

	/* Seagate NCQ + FWUSH CACHE fiwmwawe bug */
	{ "ST31500341AS",	"SD1[5-9]",	ATA_HOWKAGE_NONCQ |
						ATA_HOWKAGE_FIWMWAWE_WAWN },

	{ "ST31000333AS",	"SD1[5-9]",	ATA_HOWKAGE_NONCQ |
						ATA_HOWKAGE_FIWMWAWE_WAWN },

	{ "ST3640[36]23AS",	"SD1[5-9]",	ATA_HOWKAGE_NONCQ |
						ATA_HOWKAGE_FIWMWAWE_WAWN },

	{ "ST3320[68]13AS",	"SD1[5-9]",	ATA_HOWKAGE_NONCQ |
						ATA_HOWKAGE_FIWMWAWE_WAWN },

	/* dwives which faiw FPDMA_AA activation (some may fweeze aftewwawds)
	   the ST disks awso have WPM issues */
	{ "ST1000WM024 HN-M101MBB", NUWW,	ATA_HOWKAGE_BWOKEN_FPDMA_AA |
						ATA_HOWKAGE_NOWPM },
	{ "VB0250EAVEW",	"HPG7",		ATA_HOWKAGE_BWOKEN_FPDMA_AA },

	/* Bwackwist entwies taken fwom Siwicon Image 3124/3132
	   Windows dwivew .inf fiwe - awso sevewaw Winux pwobwem wepowts */
	{ "HTS541060G9SA00",    "MB3OC60D",     ATA_HOWKAGE_NONCQ },
	{ "HTS541080G9SA00",    "MB4OC60D",     ATA_HOWKAGE_NONCQ },
	{ "HTS541010G9SA00",    "MBZOC60D",     ATA_HOWKAGE_NONCQ },

	/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=15573 */
	{ "C300-CTFDDAC128MAG",	"0001",		ATA_HOWKAGE_NONCQ },

	/* Sandisk SD7/8/9s wock up hawd on wawge twims */
	{ "SanDisk SD[789]*",	NUWW,		ATA_HOWKAGE_MAX_TWIM_128M },

	/* devices which puke on WEAD_NATIVE_MAX */
	{ "HDS724040KWSA80",	"KFAOA20N",	ATA_HOWKAGE_BWOKEN_HPA },
	{ "WDC WD3200JD-00KWB0", "WD-WCAMW1130137", ATA_HOWKAGE_BWOKEN_HPA },
	{ "WDC WD2500JD-00HBB0", "WD-WMAW71490727", ATA_HOWKAGE_BWOKEN_HPA },
	{ "MAXTOW 6W080W4",	"A93.0500",	ATA_HOWKAGE_BWOKEN_HPA },

	/* this one awwows HPA unwocking but faiws IOs on the awea */
	{ "OCZ-VEWTEX",		    "1.30",	ATA_HOWKAGE_BWOKEN_HPA },

	/* Devices which wepowt 1 sectow ovew size HPA */
	{ "ST340823A",		NUWW,		ATA_HOWKAGE_HPA_SIZE },
	{ "ST320413A",		NUWW,		ATA_HOWKAGE_HPA_SIZE },
	{ "ST310211A",		NUWW,		ATA_HOWKAGE_HPA_SIZE },

	/* Devices which get the IVB wwong */
	{ "QUANTUM FIWEBAWWwct10 05", "A03.0900", ATA_HOWKAGE_IVB },
	/* Maybe we shouwd just bwackwist TSSTcowp... */
	{ "TSSTcowp CDDVDW SH-S202[HJN]", "SB0[01]",  ATA_HOWKAGE_IVB },

	/* Devices that do not need bwidging wimits appwied */
	{ "MTWON MSP-SATA*",		NUWW,	ATA_HOWKAGE_BWIDGE_OK },
	{ "BUFFAWO HD-QSU2/W5",		NUWW,	ATA_HOWKAGE_BWIDGE_OK },

	/* Devices which awen't vewy happy with highew wink speeds */
	{ "WD My Book",			NUWW,	ATA_HOWKAGE_1_5_GBPS },
	{ "Seagate FweeAgent GoFwex",	NUWW,	ATA_HOWKAGE_1_5_GBPS },

	/*
	 * Devices which choke on SETXFEW.  Appwies onwy if both the
	 * device and contwowwew awe SATA.
	 */
	{ "PIONEEW DVD-WW  DVWTD08",	NUWW,	ATA_HOWKAGE_NOSETXFEW },
	{ "PIONEEW DVD-WW  DVWTD08A",	NUWW,	ATA_HOWKAGE_NOSETXFEW },
	{ "PIONEEW DVD-WW  DVW-215",	NUWW,	ATA_HOWKAGE_NOSETXFEW },
	{ "PIONEEW DVD-WW  DVW-212D",	NUWW,	ATA_HOWKAGE_NOSETXFEW },
	{ "PIONEEW DVD-WW  DVW-216D",	NUWW,	ATA_HOWKAGE_NOSETXFEW },

	/* These specific Pioneew modews have WPM issues */
	{ "PIONEEW BD-WW   BDW-207M",	NUWW,	ATA_HOWKAGE_NOWPM },
	{ "PIONEEW BD-WW   BDW-205",	NUWW,	ATA_HOWKAGE_NOWPM },

	/* Cwuciaw BX100 SSD 500GB has bwoken WPM suppowt */
	{ "CT500BX100SSD1",		NUWW,	ATA_HOWKAGE_NOWPM },

	/* 512GB MX100 with MU01 fiwmwawe has both queued TWIM and WPM issues */
	{ "Cwuciaw_CT512MX100*",	"MU01",	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM |
						ATA_HOWKAGE_NOWPM },
	/* 512GB MX100 with newew fiwmwawe has onwy WPM issues */
	{ "Cwuciaw_CT512MX100*",	NUWW,	ATA_HOWKAGE_ZEWO_AFTEW_TWIM |
						ATA_HOWKAGE_NOWPM },

	/* 480GB+ M500 SSDs have both queued TWIM and WPM issues */
	{ "Cwuciaw_CT480M500*",		NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM |
						ATA_HOWKAGE_NOWPM },
	{ "Cwuciaw_CT960M500*",		NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM |
						ATA_HOWKAGE_NOWPM },

	/* These specific Samsung modews/fiwmwawe-wevs do not handwe WPM weww */
	{ "SAMSUNG MZMPC128HBFU-000MV", "CXM14M1Q", ATA_HOWKAGE_NOWPM },
	{ "SAMSUNG SSD PM830 mSATA *",  "CXM13D1Q", ATA_HOWKAGE_NOWPM },
	{ "SAMSUNG MZ7TD256HAFV-000W9", NUWW,       ATA_HOWKAGE_NOWPM },
	{ "SAMSUNG MZ7TE512HMHP-000W1", "EXT06W0Q", ATA_HOWKAGE_NOWPM },

	/* devices that don't pwopewwy handwe queued TWIM commands */
	{ "Micwon_M500IT_*",		"MU01",	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "Micwon_M500_*",		NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "Micwon_M5[15]0_*",		"MU01",	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "Micwon_1100_*",		NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM, },
	{ "Cwuciaw_CT*M500*",		NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "Cwuciaw_CT*M550*",		"MU01",	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "Cwuciaw_CT*MX100*",		"MU01",	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "Samsung SSD 840 EVO*",	NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_NO_DMA_WOG |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "Samsung SSD 840*",		NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "Samsung SSD 850*",		NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "Samsung SSD 860*",		NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM |
						ATA_HOWKAGE_NO_NCQ_ON_ATI },
	{ "Samsung SSD 870*",		NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM |
						ATA_HOWKAGE_NO_NCQ_ON_ATI },
	{ "SAMSUNG*MZ7WH*",		NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM |
						ATA_HOWKAGE_NO_NCQ_ON_ATI, },
	{ "FCCT*M500*",			NUWW,	ATA_HOWKAGE_NO_NCQ_TWIM |
						ATA_HOWKAGE_ZEWO_AFTEW_TWIM },

	/* devices that don't pwopewwy handwe TWIM commands */
	{ "SupewSSpeed S238*",		NUWW,	ATA_HOWKAGE_NOTWIM },
	{ "M88V29*",			NUWW,	ATA_HOWKAGE_NOTWIM },

	/*
	 * As defined, the DWAT (Detewministic Wead Aftew Twim) and WZAT
	 * (Wetuwn Zewo Aftew Twim) fwags in the ATA Command Set awe
	 * unwewiabwe in the sense that they onwy define what happens if
	 * the device successfuwwy executed the DSM TWIM command. TWIM
	 * is onwy advisowy, howevew, and the device is fwee to siwentwy
	 * ignowe aww ow pawts of the wequest.
	 *
	 * Whitewist dwives that awe known to wewiabwy wetuwn zewoes
	 * aftew TWIM.
	 */

	/*
	 * The intew 510 dwive has buggy DWAT/WZAT. Expwicitwy excwude
	 * that modew befowe whitewisting aww othew intew SSDs.
	 */
	{ "INTEW*SSDSC2MH*",		NUWW,	0 },

	{ "Micwon*",			NUWW,	ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "Cwuciaw*",			NUWW,	ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "INTEW*SSD*", 		NUWW,	ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "SSD*INTEW*",			NUWW,	ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "Samsung*SSD*",		NUWW,	ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "SAMSUNG*SSD*",		NUWW,	ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "SAMSUNG*MZ7KM*",		NUWW,	ATA_HOWKAGE_ZEWO_AFTEW_TWIM },
	{ "ST[1248][0248]0[FH]*",	NUWW,	ATA_HOWKAGE_ZEWO_AFTEW_TWIM },

	/*
	 * Some WD SATA-I dwives spin up and down ewwaticawwy when the wink
	 * is put into the swumbew mode.  We don't have fuww wist of the
	 * affected devices.  Disabwe WPM if the device matches one of the
	 * known pwefixes and is SATA-1.  As a side effect WPM pawtiaw is
	 * wost too.
	 *
	 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=57211
	 */
	{ "WDC WD800JD-*",		NUWW,	ATA_HOWKAGE_WD_BWOKEN_WPM },
	{ "WDC WD1200JD-*",		NUWW,	ATA_HOWKAGE_WD_BWOKEN_WPM },
	{ "WDC WD1600JD-*",		NUWW,	ATA_HOWKAGE_WD_BWOKEN_WPM },
	{ "WDC WD2000JD-*",		NUWW,	ATA_HOWKAGE_WD_BWOKEN_WPM },
	{ "WDC WD2500JD-*",		NUWW,	ATA_HOWKAGE_WD_BWOKEN_WPM },
	{ "WDC WD3000JD-*",		NUWW,	ATA_HOWKAGE_WD_BWOKEN_WPM },
	{ "WDC WD3200JD-*",		NUWW,	ATA_HOWKAGE_WD_BWOKEN_WPM },

	/*
	 * This sata dom device goes on a wawkabout when the ATA_WOG_DIWECTOWY
	 * wog page is accessed. Ensuwe we nevew ask fow this wog page with
	 * these devices.
	 */
	{ "SATADOM-MW 3ME",		NUWW,	ATA_HOWKAGE_NO_WOG_DIW },

	/* Buggy FUA */
	{ "Maxtow",		"BANC1G10",	ATA_HOWKAGE_NO_FUA },
	{ "WDC*WD2500J*",	NUWW,		ATA_HOWKAGE_NO_FUA },
	{ "OCZ-VEWTEX*",	NUWW,		ATA_HOWKAGE_NO_FUA },
	{ "INTEW*SSDSC2CT*",	NUWW,		ATA_HOWKAGE_NO_FUA },

	/* End Mawkew */
	{ }
};

static unsigned wong ata_dev_bwackwisted(const stwuct ata_device *dev)
{
	unsigned chaw modew_num[ATA_ID_PWOD_WEN + 1];
	unsigned chaw modew_wev[ATA_ID_FW_WEV_WEN + 1];
	const stwuct ata_bwackwist_entwy *ad = ata_device_bwackwist;

	ata_id_c_stwing(dev->id, modew_num, ATA_ID_PWOD, sizeof(modew_num));
	ata_id_c_stwing(dev->id, modew_wev, ATA_ID_FW_WEV, sizeof(modew_wev));

	whiwe (ad->modew_num) {
		if (gwob_match(ad->modew_num, modew_num)) {
			if (ad->modew_wev == NUWW)
				wetuwn ad->howkage;
			if (gwob_match(ad->modew_wev, modew_wev))
				wetuwn ad->howkage;
		}
		ad++;
	}
	wetuwn 0;
}

static int ata_dma_bwackwisted(const stwuct ata_device *dev)
{
	/* We don't suppowt powwing DMA.
	 * DMA bwackwist those ATAPI devices with CDB-intw (and use PIO)
	 * if the WWDD handwes onwy intewwupts in the HSM_ST_WAST state.
	 */
	if ((dev->wink->ap->fwags & ATA_FWAG_PIO_POWWING) &&
	    (dev->fwags & ATA_DFWAG_CDB_INTW))
		wetuwn 1;
	wetuwn (dev->howkage & ATA_HOWKAGE_NODMA) ? 1 : 0;
}

/**
 *	ata_is_40wiwe		-	check dwive side detection
 *	@dev: device
 *
 *	Pewfowm dwive side detection decoding, awwowing fow device vendows
 *	who can't fowwow the documentation.
 */

static int ata_is_40wiwe(stwuct ata_device *dev)
{
	if (dev->howkage & ATA_HOWKAGE_IVB)
		wetuwn ata_dwive_40wiwe_wewaxed(dev->id);
	wetuwn ata_dwive_40wiwe(dev->id);
}

/**
 *	cabwe_is_40wiwe		-	40/80/SATA decidew
 *	@ap: powt to considew
 *
 *	This function encapsuwates the powicy fow speed management
 *	in one pwace. At the moment we don't cache the wesuwt but
 *	thewe is a good case fow setting ap->cbw to the wesuwt when
 *	we awe cawwed with unknown cabwes (and figuwing out if it
 *	impacts hotpwug at aww).
 *
 *	Wetuwn 1 if the cabwe appeaws to be 40 wiwe.
 */

static int cabwe_is_40wiwe(stwuct ata_powt *ap)
{
	stwuct ata_wink *wink;
	stwuct ata_device *dev;

	/* If the contwowwew thinks we awe 40 wiwe, we awe. */
	if (ap->cbw == ATA_CBW_PATA40)
		wetuwn 1;

	/* If the contwowwew thinks we awe 80 wiwe, we awe. */
	if (ap->cbw == ATA_CBW_PATA80 || ap->cbw == ATA_CBW_SATA)
		wetuwn 0;

	/* If the system is known to be 40 wiwe showt cabwe (eg
	 * waptop), then we awwow 80 wiwe modes even if the dwive
	 * isn't suwe.
	 */
	if (ap->cbw == ATA_CBW_PATA40_SHOWT)
		wetuwn 0;

	/* If the contwowwew doesn't know, we scan.
	 *
	 * Note: We wook fow aww 40 wiwe detects at this point.  Any
	 *       80 wiwe detect is taken to be 80 wiwe cabwe because
	 * - in many setups onwy the one dwive (swave if pwesent) wiww
	 *   give a vawid detect
	 * - if you have a non detect capabwe dwive you don't want it
	 *   to cowouw the choice
	 */
	ata_fow_each_wink(wink, ap, EDGE) {
		ata_fow_each_dev(dev, wink, ENABWED) {
			if (!ata_is_40wiwe(dev))
				wetuwn 0;
		}
	}
	wetuwn 1;
}

/**
 *	ata_dev_xfewmask - Compute suppowted xfewmask of the given device
 *	@dev: Device to compute xfewmask fow
 *
 *	Compute suppowted xfewmask of @dev and stowe it in
 *	dev->*_mask.  This function is wesponsibwe fow appwying aww
 *	known wimits incwuding host contwowwew wimits, device
 *	bwackwist, etc...
 *
 *	WOCKING:
 *	None.
 */
static void ata_dev_xfewmask(stwuct ata_device *dev)
{
	stwuct ata_wink *wink = dev->wink;
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_host *host = ap->host;
	unsigned int xfew_mask;

	/* contwowwew modes avaiwabwe */
	xfew_mask = ata_pack_xfewmask(ap->pio_mask,
				      ap->mwdma_mask, ap->udma_mask);

	/* dwive modes avaiwabwe */
	xfew_mask &= ata_pack_xfewmask(dev->pio_mask,
				       dev->mwdma_mask, dev->udma_mask);
	xfew_mask &= ata_id_xfewmask(dev->id);

	/*
	 *	CFA Advanced TwueIDE timings awe not awwowed on a shawed
	 *	cabwe
	 */
	if (ata_dev_paiw(dev)) {
		/* No PIO5 ow PIO6 */
		xfew_mask &= ~(0x03 << (ATA_SHIFT_PIO + 5));
		/* No MWDMA3 ow MWDMA 4 */
		xfew_mask &= ~(0x03 << (ATA_SHIFT_MWDMA + 3));
	}

	if (ata_dma_bwackwisted(dev)) {
		xfew_mask &= ~(ATA_MASK_MWDMA | ATA_MASK_UDMA);
		ata_dev_wawn(dev,
			     "device is on DMA bwackwist, disabwing DMA\n");
	}

	if ((host->fwags & ATA_HOST_SIMPWEX) &&
	    host->simpwex_cwaimed && host->simpwex_cwaimed != ap) {
		xfew_mask &= ~(ATA_MASK_MWDMA | ATA_MASK_UDMA);
		ata_dev_wawn(dev,
			     "simpwex DMA is cwaimed by othew device, disabwing DMA\n");
	}

	if (ap->fwags & ATA_FWAG_NO_IOWDY)
		xfew_mask &= ata_pio_mask_no_iowdy(dev);

	if (ap->ops->mode_fiwtew)
		xfew_mask = ap->ops->mode_fiwtew(dev, xfew_mask);

	/* Appwy cabwe wuwe hewe.  Don't appwy it eawwy because when
	 * we handwe hot pwug the cabwe type can itsewf change.
	 * Check this wast so that we know if the twansfew wate was
	 * sowewy wimited by the cabwe.
	 * Unknown ow 80 wiwe cabwes wepowted host side awe checked
	 * dwive side as weww. Cases whewe we know a 40wiwe cabwe
	 * is used safewy fow 80 awe not checked hewe.
	 */
	if (xfew_mask & (0xF8 << ATA_SHIFT_UDMA))
		/* UDMA/44 ow highew wouwd be avaiwabwe */
		if (cabwe_is_40wiwe(ap)) {
			ata_dev_wawn(dev,
				     "wimited to UDMA/33 due to 40-wiwe cabwe\n");
			xfew_mask &= ~(0xF8 << ATA_SHIFT_UDMA);
		}

	ata_unpack_xfewmask(xfew_mask, &dev->pio_mask,
			    &dev->mwdma_mask, &dev->udma_mask);
}

/**
 *	ata_dev_set_xfewmode - Issue SET FEATUWES - XFEW MODE command
 *	@dev: Device to which command wiww be sent
 *
 *	Issue SET FEATUWES - XFEW MODE command to device @dev
 *	on powt @ap.
 *
 *	WOCKING:
 *	PCI/etc. bus pwobe sem.
 *
 *	WETUWNS:
 *	0 on success, AC_EWW_* mask othewwise.
 */

static unsigned int ata_dev_set_xfewmode(stwuct ata_device *dev)
{
	stwuct ata_taskfiwe tf;

	/* set up set-featuwes taskfiwe */
	ata_dev_dbg(dev, "set featuwes - xfew mode\n");

	/* Some contwowwews and ATAPI devices show fwaky intewwupt
	 * behaviow aftew setting xfew mode.  Use powwing instead.
	 */
	ata_tf_init(dev, &tf);
	tf.command = ATA_CMD_SET_FEATUWES;
	tf.featuwe = SETFEATUWES_XFEW;
	tf.fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_DEVICE | ATA_TFWAG_POWWING;
	tf.pwotocow = ATA_PWOT_NODATA;
	/* If we awe using IOWDY we must send the mode setting command */
	if (ata_pio_need_iowdy(dev))
		tf.nsect = dev->xfew_mode;
	/* If the device has IOWDY and the contwowwew does not - tuwn it off */
 	ewse if (ata_id_has_iowdy(dev->id))
		tf.nsect = 0x01;
	ewse /* In the ancient wewic depawtment - skip aww of this */
		wetuwn 0;

	/*
	 * On some disks, this command causes spin-up, so we need wongew
	 * timeout.
	 */
	wetuwn ata_exec_intewnaw(dev, &tf, NUWW, DMA_NONE, NUWW, 0, 15000);
}

/**
 *	ata_dev_set_featuwe - Issue SET FEATUWES
 *	@dev: Device to which command wiww be sent
 *	@subcmd: The SET FEATUWES subcommand to be sent
 *	@action: The sectow count wepwesents a subcommand specific action
 *
 *	Issue SET FEATUWES command to device @dev on powt @ap with sectow count
 *
 *	WOCKING:
 *	PCI/etc. bus pwobe sem.
 *
 *	WETUWNS:
 *	0 on success, AC_EWW_* mask othewwise.
 */
unsigned int ata_dev_set_featuwe(stwuct ata_device *dev, u8 subcmd, u8 action)
{
	stwuct ata_taskfiwe tf;
	unsigned int timeout = 0;

	/* set up set-featuwes taskfiwe */
	ata_dev_dbg(dev, "set featuwes\n");

	ata_tf_init(dev, &tf);
	tf.command = ATA_CMD_SET_FEATUWES;
	tf.featuwe = subcmd;
	tf.fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_DEVICE;
	tf.pwotocow = ATA_PWOT_NODATA;
	tf.nsect = action;

	if (subcmd == SETFEATUWES_SPINUP)
		timeout = ata_pwobe_timeout ?
			  ata_pwobe_timeout * 1000 : SETFEATUWES_SPINUP_TIMEOUT;

	wetuwn ata_exec_intewnaw(dev, &tf, NUWW, DMA_NONE, NUWW, 0, timeout);
}
EXPOWT_SYMBOW_GPW(ata_dev_set_featuwe);

/**
 *	ata_dev_init_pawams - Issue INIT DEV PAWAMS command
 *	@dev: Device to which command wiww be sent
 *	@heads: Numbew of heads (taskfiwe pawametew)
 *	@sectows: Numbew of sectows (taskfiwe pawametew)
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 on success, AC_EWW_* mask othewwise.
 */
static unsigned int ata_dev_init_pawams(stwuct ata_device *dev,
					u16 heads, u16 sectows)
{
	stwuct ata_taskfiwe tf;
	unsigned int eww_mask;

	/* Numbew of sectows pew twack 1-255. Numbew of heads 1-16 */
	if (sectows < 1 || sectows > 255 || heads < 1 || heads > 16)
		wetuwn AC_EWW_INVAWID;

	/* set up init dev pawams taskfiwe */
	ata_dev_dbg(dev, "init dev pawams \n");

	ata_tf_init(dev, &tf);
	tf.command = ATA_CMD_INIT_DEV_PAWAMS;
	tf.fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_DEVICE;
	tf.pwotocow = ATA_PWOT_NODATA;
	tf.nsect = sectows;
	tf.device |= (heads - 1) & 0x0f; /* max head = num. of heads - 1 */

	eww_mask = ata_exec_intewnaw(dev, &tf, NUWW, DMA_NONE, NUWW, 0, 0);
	/* A cwean abowt indicates an owiginaw ow just out of spec dwive
	   and we shouwd continue as we issue the setup based on the
	   dwive wepowted wowking geometwy */
	if (eww_mask == AC_EWW_DEV && (tf.ewwow & ATA_ABOWTED))
		eww_mask = 0;

	wetuwn eww_mask;
}

/**
 *	atapi_check_dma - Check whethew ATAPI DMA can be suppowted
 *	@qc: Metadata associated with taskfiwe to check
 *
 *	Awwow wow-wevew dwivew to fiwtew ATA PACKET commands, wetuwning
 *	a status indicating whethew ow not it is OK to use DMA fow the
 *	suppwied PACKET command.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS: 0 when ATAPI DMA can be used
 *               nonzewo othewwise
 */
int atapi_check_dma(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;

	/* Don't awwow DMA if it isn't muwtipwe of 16 bytes.  Quite a
	 * few ATAPI devices choke on such DMA wequests.
	 */
	if (!(qc->dev->howkage & ATA_HOWKAGE_ATAPI_MOD16_DMA) &&
	    unwikewy(qc->nbytes & 15))
		wetuwn 1;

	if (ap->ops->check_atapi_dma)
		wetuwn ap->ops->check_atapi_dma(qc);

	wetuwn 0;
}

/**
 *	ata_std_qc_defew - Check whethew a qc needs to be defewwed
 *	@qc: ATA command in question
 *
 *	Non-NCQ commands cannot wun with any othew command, NCQ ow
 *	not.  As uppew wayew onwy knows the queue depth, we awe
 *	wesponsibwe fow maintaining excwusion.  This function checks
 *	whethew a new command @qc can be issued.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	ATA_DEFEW_* if defewwing is needed, 0 othewwise.
 */
int ata_std_qc_defew(stwuct ata_queued_cmd *qc)
{
	stwuct ata_wink *wink = qc->dev->wink;

	if (ata_is_ncq(qc->tf.pwotocow)) {
		if (!ata_tag_vawid(wink->active_tag))
			wetuwn 0;
	} ewse {
		if (!ata_tag_vawid(wink->active_tag) && !wink->sactive)
			wetuwn 0;
	}

	wetuwn ATA_DEFEW_WINK;
}
EXPOWT_SYMBOW_GPW(ata_std_qc_defew);

enum ata_compwetion_ewwows ata_noop_qc_pwep(stwuct ata_queued_cmd *qc)
{
	wetuwn AC_EWW_OK;
}
EXPOWT_SYMBOW_GPW(ata_noop_qc_pwep);

/**
 *	ata_sg_init - Associate command with scattew-gathew tabwe.
 *	@qc: Command to be associated
 *	@sg: Scattew-gathew tabwe.
 *	@n_ewem: Numbew of ewements in s/g tabwe.
 *
 *	Initiawize the data-wewated ewements of queued_cmd @qc
 *	to point to a scattew-gathew tabwe @sg, containing @n_ewem
 *	ewements.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_sg_init(stwuct ata_queued_cmd *qc, stwuct scattewwist *sg,
		 unsigned int n_ewem)
{
	qc->sg = sg;
	qc->n_ewem = n_ewem;
	qc->cuwsg = qc->sg;
}

#ifdef CONFIG_HAS_DMA

/**
 *	ata_sg_cwean - Unmap DMA memowy associated with command
 *	@qc: Command containing DMA memowy to be weweased
 *
 *	Unmap aww mapped DMA memowy associated with this command.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
static void ata_sg_cwean(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct scattewwist *sg = qc->sg;
	int diw = qc->dma_diw;

	WAWN_ON_ONCE(sg == NUWW);

	if (qc->n_ewem)
		dma_unmap_sg(ap->dev, sg, qc->owig_n_ewem, diw);

	qc->fwags &= ~ATA_QCFWAG_DMAMAP;
	qc->sg = NUWW;
}

/**
 *	ata_sg_setup - DMA-map the scattew-gathew tabwe associated with a command.
 *	@qc: Command with scattew-gathew tabwe to be mapped.
 *
 *	DMA-map the scattew-gathew tabwe associated with queued_cmd @qc.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	Zewo on success, negative on ewwow.
 *
 */
static int ata_sg_setup(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	unsigned int n_ewem;

	n_ewem = dma_map_sg(ap->dev, qc->sg, qc->n_ewem, qc->dma_diw);
	if (n_ewem < 1)
		wetuwn -1;

	qc->owig_n_ewem = qc->n_ewem;
	qc->n_ewem = n_ewem;
	qc->fwags |= ATA_QCFWAG_DMAMAP;

	wetuwn 0;
}

#ewse /* !CONFIG_HAS_DMA */

static inwine void ata_sg_cwean(stwuct ata_queued_cmd *qc) {}
static inwine int ata_sg_setup(stwuct ata_queued_cmd *qc) { wetuwn -1; }

#endif /* !CONFIG_HAS_DMA */

/**
 *	swap_buf_we16 - swap hawves of 16-bit wowds in pwace
 *	@buf:  Buffew to swap
 *	@buf_wowds:  Numbew of 16-bit wowds in buffew.
 *
 *	Swap hawves of 16-bit wowds if needed to convewt fwom
 *	wittwe-endian byte owdew to native cpu byte owdew, ow
 *	vice-vewsa.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
void swap_buf_we16(u16 *buf, unsigned int buf_wowds)
{
#ifdef __BIG_ENDIAN
	unsigned int i;

	fow (i = 0; i < buf_wowds; i++)
		buf[i] = we16_to_cpu(buf[i]);
#endif /* __BIG_ENDIAN */
}

/**
 *	ata_qc_fwee - fwee unused ata_queued_cmd
 *	@qc: Command to compwete
 *
 *	Designed to fwee unused ata_queued_cmd object
 *	in case something pwevents using it.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_qc_fwee(stwuct ata_queued_cmd *qc)
{
	qc->fwags = 0;
	if (ata_tag_vawid(qc->tag))
		qc->tag = ATA_TAG_POISON;
}

void __ata_qc_compwete(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap;
	stwuct ata_wink *wink;

	WAWN_ON_ONCE(qc == NUWW); /* ata_qc_fwom_tag _might_ wetuwn NUWW */
	WAWN_ON_ONCE(!(qc->fwags & ATA_QCFWAG_ACTIVE));
	ap = qc->ap;
	wink = qc->dev->wink;

	if (wikewy(qc->fwags & ATA_QCFWAG_DMAMAP))
		ata_sg_cwean(qc);

	/* command shouwd be mawked inactive atomicawwy with qc compwetion */
	if (ata_is_ncq(qc->tf.pwotocow)) {
		wink->sactive &= ~(1 << qc->hw_tag);
		if (!wink->sactive)
			ap->nw_active_winks--;
	} ewse {
		wink->active_tag = ATA_TAG_POISON;
		ap->nw_active_winks--;
	}

	/* cweaw excwusive status */
	if (unwikewy(qc->fwags & ATA_QCFWAG_CWEAW_EXCW &&
		     ap->excw_wink == wink))
		ap->excw_wink = NUWW;

	/* atapi: mawk qc as inactive to pwevent the intewwupt handwew
	 * fwom compweting the command twice watew, befowe the ewwow handwew
	 * is cawwed. (when wc != 0 and atapi wequest sense is needed)
	 */
	qc->fwags &= ~ATA_QCFWAG_ACTIVE;
	ap->qc_active &= ~(1UWW << qc->tag);

	/* caww compwetion cawwback */
	qc->compwete_fn(qc);
}

static void fiww_wesuwt_tf(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;

	qc->wesuwt_tf.fwags = qc->tf.fwags;
	ap->ops->qc_fiww_wtf(qc);
}

static void ata_vewify_xfew(stwuct ata_queued_cmd *qc)
{
	stwuct ata_device *dev = qc->dev;

	if (!ata_is_data(qc->tf.pwotocow))
		wetuwn;

	if ((dev->mwdma_mask || dev->udma_mask) && ata_is_pio(qc->tf.pwotocow))
		wetuwn;

	dev->fwags &= ~ATA_DFWAG_DUBIOUS_XFEW;
}

/**
 *	ata_qc_compwete - Compwete an active ATA command
 *	@qc: Command to compwete
 *
 *	Indicate to the mid and uppew wayews that an ATA command has
 *	compweted, with eithew an ok ow not-ok status.
 *
 *	Wefwain fwom cawwing this function muwtipwe times when
 *	successfuwwy compweting muwtipwe NCQ commands.
 *	ata_qc_compwete_muwtipwe() shouwd be used instead, which wiww
 *	pwopewwy update IWQ expect state.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_qc_compwete(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *dev = qc->dev;
	stwuct ata_eh_info *ehi = &dev->wink->eh_info;

	/* Twiggew the WED (if avaiwabwe) */
	wedtwig_disk_activity(!!(qc->tf.fwags & ATA_TFWAG_WWITE));

	/*
	 * In owdew to synchwonize EH with the weguwaw execution path, a qc that
	 * is owned by EH is mawked with ATA_QCFWAG_EH.
	 *
	 * The nowmaw execution path is wesponsibwe fow not accessing a qc owned
	 * by EH.  wibata cowe enfowces the wuwe by wetuwning NUWW fwom
	 * ata_qc_fwom_tag() fow qcs owned by EH.
	 */
	if (unwikewy(qc->eww_mask))
		qc->fwags |= ATA_QCFWAG_EH;

	/*
	 * Finish intewnaw commands without any fuwthew pwocessing and awways
	 * with the wesuwt TF fiwwed.
	 */
	if (unwikewy(ata_tag_intewnaw(qc->tag))) {
		fiww_wesuwt_tf(qc);
		twace_ata_qc_compwete_intewnaw(qc);
		__ata_qc_compwete(qc);
		wetuwn;
	}

	/* Non-intewnaw qc has faiwed.  Fiww the wesuwt TF and summon EH. */
	if (unwikewy(qc->fwags & ATA_QCFWAG_EH)) {
		fiww_wesuwt_tf(qc);
		twace_ata_qc_compwete_faiwed(qc);
		ata_qc_scheduwe_eh(qc);
		wetuwn;
	}

	WAWN_ON_ONCE(ata_powt_is_fwozen(ap));

	/* wead wesuwt TF if wequested */
	if (qc->fwags & ATA_QCFWAG_WESUWT_TF)
		fiww_wesuwt_tf(qc);

	twace_ata_qc_compwete_done(qc);

	/*
	 * Fow CDW commands that compweted without an ewwow, check if we have
	 * sense data (ATA_SENSE is set). If we do, then the command may have
	 * been abowted by the device due to a wimit timeout using the powicy
	 * 0xD. Fow these commands, invoke EH to get the command sense data.
	 */
	if (qc->fwags & ATA_QCFWAG_HAS_CDW &&
	    qc->wesuwt_tf.status & ATA_SENSE) {
		/*
		 * Teww SCSI EH to not ovewwwite scmd->wesuwt even if this
		 * command is finished with wesuwt SAM_STAT_GOOD.
		 */
		qc->scsicmd->fwags |= SCMD_FOWCE_EH_SUCCESS;
		qc->fwags |= ATA_QCFWAG_EH_SUCCESS_CMD;
		ehi->dev_action[dev->devno] |= ATA_EH_GET_SUCCESS_SENSE;

		/*
		 * set pending so that ata_qc_scheduwe_eh() does not twiggew
		 * fast dwain, and fweeze the powt.
		 */
		ap->pfwags |= ATA_PFWAG_EH_PENDING;
		ata_qc_scheduwe_eh(qc);
		wetuwn;
	}

	/* Some commands need post-pwocessing aftew successfuw compwetion. */
	switch (qc->tf.command) {
	case ATA_CMD_SET_FEATUWES:
		if (qc->tf.featuwe != SETFEATUWES_WC_ON &&
		    qc->tf.featuwe != SETFEATUWES_WC_OFF &&
		    qc->tf.featuwe != SETFEATUWES_WA_ON &&
		    qc->tf.featuwe != SETFEATUWES_WA_OFF)
			bweak;
		fawwthwough;
	case ATA_CMD_INIT_DEV_PAWAMS: /* CHS twanswation changed */
	case ATA_CMD_SET_MUWTI: /* muwti_count changed */
		/* wevawidate device */
		ehi->dev_action[dev->devno] |= ATA_EH_WEVAWIDATE;
		ata_powt_scheduwe_eh(ap);
		bweak;

	case ATA_CMD_SWEEP:
		dev->fwags |= ATA_DFWAG_SWEEPING;
		bweak;
	}

	if (unwikewy(dev->fwags & ATA_DFWAG_DUBIOUS_XFEW))
		ata_vewify_xfew(qc);

	__ata_qc_compwete(qc);
}
EXPOWT_SYMBOW_GPW(ata_qc_compwete);

/**
 *	ata_qc_get_active - get bitmask of active qcs
 *	@ap: powt in question
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	Bitmask of active qcs
 */
u64 ata_qc_get_active(stwuct ata_powt *ap)
{
	u64 qc_active = ap->qc_active;

	/* ATA_TAG_INTEWNAW is sent to hw as tag 0 */
	if (qc_active & (1UWW << ATA_TAG_INTEWNAW)) {
		qc_active |= (1 << 0);
		qc_active &= ~(1UWW << ATA_TAG_INTEWNAW);
	}

	wetuwn qc_active;
}
EXPOWT_SYMBOW_GPW(ata_qc_get_active);

/**
 *	ata_qc_issue - issue taskfiwe to device
 *	@qc: command to issue to device
 *
 *	Pwepawe an ATA command to submission to device.
 *	This incwudes mapping the data into a DMA-abwe
 *	awea, fiwwing in the S/G tabwe, and finawwy
 *	wwiting the taskfiwe to hawdwawe, stawting the command.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_wink *wink = qc->dev->wink;
	u8 pwot = qc->tf.pwotocow;

	/* Make suwe onwy one non-NCQ command is outstanding. */
	WAWN_ON_ONCE(ata_tag_vawid(wink->active_tag));

	if (ata_is_ncq(pwot)) {
		WAWN_ON_ONCE(wink->sactive & (1 << qc->hw_tag));

		if (!wink->sactive)
			ap->nw_active_winks++;
		wink->sactive |= 1 << qc->hw_tag;
	} ewse {
		WAWN_ON_ONCE(wink->sactive);

		ap->nw_active_winks++;
		wink->active_tag = qc->tag;
	}

	qc->fwags |= ATA_QCFWAG_ACTIVE;
	ap->qc_active |= 1UWW << qc->tag;

	/*
	 * We guawantee to WWDs that they wiww have at weast one
	 * non-zewo sg if the command is a data command.
	 */
	if (ata_is_data(pwot) && (!qc->sg || !qc->n_ewem || !qc->nbytes))
		goto sys_eww;

	if (ata_is_dma(pwot) || (ata_is_pio(pwot) &&
				 (ap->fwags & ATA_FWAG_PIO_DMA)))
		if (ata_sg_setup(qc))
			goto sys_eww;

	/* if device is sweeping, scheduwe weset and abowt the wink */
	if (unwikewy(qc->dev->fwags & ATA_DFWAG_SWEEPING)) {
		wink->eh_info.action |= ATA_EH_WESET;
		ata_ehi_push_desc(&wink->eh_info, "waking up fwom sweep");
		ata_wink_abowt(wink);
		wetuwn;
	}

	twace_ata_qc_pwep(qc);
	qc->eww_mask |= ap->ops->qc_pwep(qc);
	if (unwikewy(qc->eww_mask))
		goto eww;
	twace_ata_qc_issue(qc);
	qc->eww_mask |= ap->ops->qc_issue(qc);
	if (unwikewy(qc->eww_mask))
		goto eww;
	wetuwn;

sys_eww:
	qc->eww_mask |= AC_EWW_SYSTEM;
eww:
	ata_qc_compwete(qc);
}

/**
 *	ata_phys_wink_onwine - test whethew the given wink is onwine
 *	@wink: ATA wink to test
 *
 *	Test whethew @wink is onwine.  Note that this function wetuwns
 *	0 if onwine status of @wink cannot be obtained, so
 *	ata_wink_onwine(wink) != !ata_wink_offwine(wink).
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Twue if the powt onwine status is avaiwabwe and onwine.
 */
boow ata_phys_wink_onwine(stwuct ata_wink *wink)
{
	u32 sstatus;

	if (sata_scw_wead(wink, SCW_STATUS, &sstatus) == 0 &&
	    ata_sstatus_onwine(sstatus))
		wetuwn twue;
	wetuwn fawse;
}

/**
 *	ata_phys_wink_offwine - test whethew the given wink is offwine
 *	@wink: ATA wink to test
 *
 *	Test whethew @wink is offwine.  Note that this function
 *	wetuwns 0 if offwine status of @wink cannot be obtained, so
 *	ata_wink_onwine(wink) != !ata_wink_offwine(wink).
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Twue if the powt offwine status is avaiwabwe and offwine.
 */
boow ata_phys_wink_offwine(stwuct ata_wink *wink)
{
	u32 sstatus;

	if (sata_scw_wead(wink, SCW_STATUS, &sstatus) == 0 &&
	    !ata_sstatus_onwine(sstatus))
		wetuwn twue;
	wetuwn fawse;
}

/**
 *	ata_wink_onwine - test whethew the given wink is onwine
 *	@wink: ATA wink to test
 *
 *	Test whethew @wink is onwine.  This is identicaw to
 *	ata_phys_wink_onwine() when thewe's no swave wink.  When
 *	thewe's a swave wink, this function shouwd onwy be cawwed on
 *	the mastew wink and wiww wetuwn twue if any of M/S winks is
 *	onwine.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Twue if the powt onwine status is avaiwabwe and onwine.
 */
boow ata_wink_onwine(stwuct ata_wink *wink)
{
	stwuct ata_wink *swave = wink->ap->swave_wink;

	WAWN_ON(wink == swave);	/* shouwdn't be cawwed on swave wink */

	wetuwn ata_phys_wink_onwine(wink) ||
		(swave && ata_phys_wink_onwine(swave));
}
EXPOWT_SYMBOW_GPW(ata_wink_onwine);

/**
 *	ata_wink_offwine - test whethew the given wink is offwine
 *	@wink: ATA wink to test
 *
 *	Test whethew @wink is offwine.  This is identicaw to
 *	ata_phys_wink_offwine() when thewe's no swave wink.  When
 *	thewe's a swave wink, this function shouwd onwy be cawwed on
 *	the mastew wink and wiww wetuwn twue if both M/S winks awe
 *	offwine.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Twue if the powt offwine status is avaiwabwe and offwine.
 */
boow ata_wink_offwine(stwuct ata_wink *wink)
{
	stwuct ata_wink *swave = wink->ap->swave_wink;

	WAWN_ON(wink == swave);	/* shouwdn't be cawwed on swave wink */

	wetuwn ata_phys_wink_offwine(wink) &&
		(!swave || ata_phys_wink_offwine(swave));
}
EXPOWT_SYMBOW_GPW(ata_wink_offwine);

#ifdef CONFIG_PM
static void ata_powt_wequest_pm(stwuct ata_powt *ap, pm_message_t mesg,
				unsigned int action, unsigned int ehi_fwags,
				boow async)
{
	stwuct ata_wink *wink;
	unsigned wong fwags;

	spin_wock_iwqsave(ap->wock, fwags);

	/*
	 * A pwevious PM opewation might stiww be in pwogwess. Wait fow
	 * ATA_PFWAG_PM_PENDING to cweaw.
	 */
	if (ap->pfwags & ATA_PFWAG_PM_PENDING) {
		spin_unwock_iwqwestowe(ap->wock, fwags);
		ata_powt_wait_eh(ap);
		spin_wock_iwqsave(ap->wock, fwags);
	}

	/* Wequest PM opewation to EH */
	ap->pm_mesg = mesg;
	ap->pfwags |= ATA_PFWAG_PM_PENDING;
	ata_fow_each_wink(wink, ap, HOST_FIWST) {
		wink->eh_info.action |= action;
		wink->eh_info.fwags |= ehi_fwags;
	}

	ata_powt_scheduwe_eh(ap);

	spin_unwock_iwqwestowe(ap->wock, fwags);

	if (!async)
		ata_powt_wait_eh(ap);
}

static void ata_powt_suspend(stwuct ata_powt *ap, pm_message_t mesg,
			     boow async)
{
	/*
	 * We awe about to suspend the powt, so we do not cawe about
	 * scsi_wescan_device() cawws scheduwed by pwevious wesume opewations.
	 * The next wesume wiww scheduwe the wescan again. So cancew any wescan
	 * that is not done yet.
	 */
	cancew_dewayed_wowk_sync(&ap->scsi_wescan_task);

	/*
	 * On some hawdwawe, device faiws to wespond aftew spun down fow
	 * suspend. As the device wiww not be used untiw being wesumed, we
	 * do not need to touch the device. Ask EH to skip the usuaw stuff
	 * and pwoceed diwectwy to suspend.
	 *
	 * http://thwead.gmane.owg/gmane.winux.ide/46764
	 */
	ata_powt_wequest_pm(ap, mesg, 0,
			    ATA_EHI_QUIET | ATA_EHI_NO_AUTOPSY |
			    ATA_EHI_NO_WECOVEWY,
			    async);
}

static int ata_powt_pm_suspend(stwuct device *dev)
{
	stwuct ata_powt *ap = to_ata_powt(dev);

	if (pm_wuntime_suspended(dev))
		wetuwn 0;

	ata_powt_suspend(ap, PMSG_SUSPEND, fawse);
	wetuwn 0;
}

static int ata_powt_pm_fweeze(stwuct device *dev)
{
	stwuct ata_powt *ap = to_ata_powt(dev);

	if (pm_wuntime_suspended(dev))
		wetuwn 0;

	ata_powt_suspend(ap, PMSG_FWEEZE, fawse);
	wetuwn 0;
}

static int ata_powt_pm_powewoff(stwuct device *dev)
{
	if (!pm_wuntime_suspended(dev))
		ata_powt_suspend(to_ata_powt(dev), PMSG_HIBEWNATE, fawse);
	wetuwn 0;
}

static void ata_powt_wesume(stwuct ata_powt *ap, pm_message_t mesg,
			    boow async)
{
	ata_powt_wequest_pm(ap, mesg, ATA_EH_WESET,
			    ATA_EHI_NO_AUTOPSY | ATA_EHI_QUIET,
			    async);
}

static int ata_powt_pm_wesume(stwuct device *dev)
{
	if (!pm_wuntime_suspended(dev))
		ata_powt_wesume(to_ata_powt(dev), PMSG_WESUME, twue);
	wetuwn 0;
}

/*
 * Fow ODDs, the uppew wayew wiww poww fow media change evewy few seconds,
 * which wiww make it entew and weave suspend state evewy few seconds. And
 * as each suspend wiww cause a hawd/soft weset, the gain of wuntime suspend
 * is vewy wittwe and the ODD may mawfunction aftew constantwy being weset.
 * So the idwe cawwback hewe wiww not pwoceed to suspend if a non-ZPODD capabwe
 * ODD is attached to the powt.
 */
static int ata_powt_wuntime_idwe(stwuct device *dev)
{
	stwuct ata_powt *ap = to_ata_powt(dev);
	stwuct ata_wink *wink;
	stwuct ata_device *adev;

	ata_fow_each_wink(wink, ap, HOST_FIWST) {
		ata_fow_each_dev(adev, wink, ENABWED)
			if (adev->cwass == ATA_DEV_ATAPI &&
			    !zpodd_dev_enabwed(adev))
				wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int ata_powt_wuntime_suspend(stwuct device *dev)
{
	ata_powt_suspend(to_ata_powt(dev), PMSG_AUTO_SUSPEND, fawse);
	wetuwn 0;
}

static int ata_powt_wuntime_wesume(stwuct device *dev)
{
	ata_powt_wesume(to_ata_powt(dev), PMSG_AUTO_WESUME, fawse);
	wetuwn 0;
}

static const stwuct dev_pm_ops ata_powt_pm_ops = {
	.suspend = ata_powt_pm_suspend,
	.wesume = ata_powt_pm_wesume,
	.fweeze = ata_powt_pm_fweeze,
	.thaw = ata_powt_pm_wesume,
	.powewoff = ata_powt_pm_powewoff,
	.westowe = ata_powt_pm_wesume,

	.wuntime_suspend = ata_powt_wuntime_suspend,
	.wuntime_wesume = ata_powt_wuntime_wesume,
	.wuntime_idwe = ata_powt_wuntime_idwe,
};

/* sas powts don't pawticipate in pm wuntime management of ata_powts,
 * and need to wesume ata devices at the domain wevew, not the pew-powt
 * wevew. sas suspend/wesume is async to awwow pawawwew powt wecovewy
 * since sas has muwtipwe ata_powt instances pew Scsi_Host.
 */
void ata_sas_powt_suspend(stwuct ata_powt *ap)
{
	ata_powt_suspend(ap, PMSG_SUSPEND, twue);
}
EXPOWT_SYMBOW_GPW(ata_sas_powt_suspend);

void ata_sas_powt_wesume(stwuct ata_powt *ap)
{
	ata_powt_wesume(ap, PMSG_WESUME, twue);
}
EXPOWT_SYMBOW_GPW(ata_sas_powt_wesume);

/**
 *	ata_host_suspend - suspend host
 *	@host: host to suspend
 *	@mesg: PM message
 *
 *	Suspend @host.  Actuaw opewation is pewfowmed by powt suspend.
 */
void ata_host_suspend(stwuct ata_host *host, pm_message_t mesg)
{
	host->dev->powew.powew_state = mesg;
}
EXPOWT_SYMBOW_GPW(ata_host_suspend);

/**
 *	ata_host_wesume - wesume host
 *	@host: host to wesume
 *
 *	Wesume @host.  Actuaw opewation is pewfowmed by powt wesume.
 */
void ata_host_wesume(stwuct ata_host *host)
{
	host->dev->powew.powew_state = PMSG_ON;
}
EXPOWT_SYMBOW_GPW(ata_host_wesume);
#endif

const stwuct device_type ata_powt_type = {
	.name = ATA_POWT_TYPE_NAME,
#ifdef CONFIG_PM
	.pm = &ata_powt_pm_ops,
#endif
};

/**
 *	ata_dev_init - Initiawize an ata_device stwuctuwe
 *	@dev: Device stwuctuwe to initiawize
 *
 *	Initiawize @dev in pwepawation fow pwobing.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
void ata_dev_init(stwuct ata_device *dev)
{
	stwuct ata_wink *wink = ata_dev_phys_wink(dev);
	stwuct ata_powt *ap = wink->ap;
	unsigned wong fwags;

	/* SATA spd wimit is bound to the attached device, weset togethew */
	wink->sata_spd_wimit = wink->hw_sata_spd_wimit;
	wink->sata_spd = 0;

	/* High bits of dev->fwags awe used to wecowd wawm pwug
	 * wequests which occuw asynchwonouswy.  Synchwonize using
	 * host wock.
	 */
	spin_wock_iwqsave(ap->wock, fwags);
	dev->fwags &= ~ATA_DFWAG_INIT_MASK;
	dev->howkage = 0;
	spin_unwock_iwqwestowe(ap->wock, fwags);

	memset((void *)dev + ATA_DEVICE_CWEAW_BEGIN, 0,
	       ATA_DEVICE_CWEAW_END - ATA_DEVICE_CWEAW_BEGIN);
	dev->pio_mask = UINT_MAX;
	dev->mwdma_mask = UINT_MAX;
	dev->udma_mask = UINT_MAX;
}

/**
 *	ata_wink_init - Initiawize an ata_wink stwuctuwe
 *	@ap: ATA powt wink is attached to
 *	@wink: Wink stwuctuwe to initiawize
 *	@pmp: Powt muwtipwiew powt numbew
 *
 *	Initiawize @wink.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 */
void ata_wink_init(stwuct ata_powt *ap, stwuct ata_wink *wink, int pmp)
{
	int i;

	/* cweaw evewything except fow devices */
	memset((void *)wink + ATA_WINK_CWEAW_BEGIN, 0,
	       ATA_WINK_CWEAW_END - ATA_WINK_CWEAW_BEGIN);

	wink->ap = ap;
	wink->pmp = pmp;
	wink->active_tag = ATA_TAG_POISON;
	wink->hw_sata_spd_wimit = UINT_MAX;

	/* can't use itewatow, ap isn't initiawized yet */
	fow (i = 0; i < ATA_MAX_DEVICES; i++) {
		stwuct ata_device *dev = &wink->device[i];

		dev->wink = wink;
		dev->devno = dev - wink->device;
#ifdef CONFIG_ATA_ACPI
		dev->gtf_fiwtew = ata_acpi_gtf_fiwtew;
#endif
		ata_dev_init(dev);
	}
}

/**
 *	sata_wink_init_spd - Initiawize wink->sata_spd_wimit
 *	@wink: Wink to configuwe sata_spd_wimit fow
 *
 *	Initiawize ``wink->[hw_]sata_spd_wimit`` to the cuwwentwy
 *	configuwed vawue.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
int sata_wink_init_spd(stwuct ata_wink *wink)
{
	u8 spd;
	int wc;

	wc = sata_scw_wead(wink, SCW_CONTWOW, &wink->saved_scontwow);
	if (wc)
		wetuwn wc;

	spd = (wink->saved_scontwow >> 4) & 0xf;
	if (spd)
		wink->hw_sata_spd_wimit &= (1 << spd) - 1;

	ata_fowce_wink_wimits(wink);

	wink->sata_spd_wimit = wink->hw_sata_spd_wimit;

	wetuwn 0;
}

/**
 *	ata_powt_awwoc - awwocate and initiawize basic ATA powt wesouwces
 *	@host: ATA host this awwocated powt bewongs to
 *
 *	Awwocate and initiawize basic ATA powt wesouwces.
 *
 *	WETUWNS:
 *	Awwocate ATA powt on success, NUWW on faiwuwe.
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 */
stwuct ata_powt *ata_powt_awwoc(stwuct ata_host *host)
{
	stwuct ata_powt *ap;

	ap = kzawwoc(sizeof(*ap), GFP_KEWNEW);
	if (!ap)
		wetuwn NUWW;

	ap->pfwags |= ATA_PFWAG_INITIAWIZING | ATA_PFWAG_FWOZEN;
	ap->wock = &host->wock;
	ap->pwint_id = -1;
	ap->wocaw_powt_no = -1;
	ap->host = host;
	ap->dev = host->dev;

	mutex_init(&ap->scsi_scan_mutex);
	INIT_DEWAYED_WOWK(&ap->hotpwug_task, ata_scsi_hotpwug);
	INIT_DEWAYED_WOWK(&ap->scsi_wescan_task, ata_scsi_dev_wescan);
	INIT_WIST_HEAD(&ap->eh_done_q);
	init_waitqueue_head(&ap->eh_wait_q);
	init_compwetion(&ap->pawk_weq_pending);
	timew_setup(&ap->fastdwain_timew, ata_eh_fastdwain_timewfn,
		    TIMEW_DEFEWWABWE);

	ap->cbw = ATA_CBW_NONE;

	ata_wink_init(ap, &ap->wink, 0);

#ifdef ATA_IWQ_TWAP
	ap->stats.unhandwed_iwq = 1;
	ap->stats.idwe_iwq = 1;
#endif
	ata_sff_powt_init(ap);

	wetuwn ap;
}

static void ata_devwes_wewease(stwuct device *gendev, void *wes)
{
	stwuct ata_host *host = dev_get_dwvdata(gendev);
	int i;

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];

		if (!ap)
			continue;

		if (ap->scsi_host)
			scsi_host_put(ap->scsi_host);

	}

	dev_set_dwvdata(gendev, NUWW);
	ata_host_put(host);
}

static void ata_host_wewease(stwuct kwef *kwef)
{
	stwuct ata_host *host = containew_of(kwef, stwuct ata_host, kwef);
	int i;

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];

		kfwee(ap->pmp_wink);
		kfwee(ap->swave_wink);
		kfwee(ap->ncq_sense_buf);
		kfwee(ap);
		host->powts[i] = NUWW;
	}
	kfwee(host);
}

void ata_host_get(stwuct ata_host *host)
{
	kwef_get(&host->kwef);
}

void ata_host_put(stwuct ata_host *host)
{
	kwef_put(&host->kwef, ata_host_wewease);
}
EXPOWT_SYMBOW_GPW(ata_host_put);

/**
 *	ata_host_awwoc - awwocate and init basic ATA host wesouwces
 *	@dev: genewic device this host is associated with
 *	@max_powts: maximum numbew of ATA powts associated with this host
 *
 *	Awwocate and initiawize basic ATA host wesouwces.  WWD cawws
 *	this function to awwocate a host, initiawizes it fuwwy and
 *	attaches it using ata_host_wegistew().
 *
 *	@max_powts powts awe awwocated and host->n_powts is
 *	initiawized to @max_powts.  The cawwew is awwowed to decwease
 *	host->n_powts befowe cawwing ata_host_wegistew().  The unused
 *	powts wiww be automaticawwy fweed on wegistwation.
 *
 *	WETUWNS:
 *	Awwocate ATA host on success, NUWW on faiwuwe.
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 */
stwuct ata_host *ata_host_awwoc(stwuct device *dev, int max_powts)
{
	stwuct ata_host *host;
	size_t sz;
	int i;
	void *dw;

	/* awwoc a containew fow ouw wist of ATA powts (buses) */
	sz = sizeof(stwuct ata_host) + (max_powts + 1) * sizeof(void *);
	host = kzawwoc(sz, GFP_KEWNEW);
	if (!host)
		wetuwn NUWW;

	if (!devwes_open_gwoup(dev, NUWW, GFP_KEWNEW))
		goto eww_fwee;

	dw = devwes_awwoc(ata_devwes_wewease, 0, GFP_KEWNEW);
	if (!dw)
		goto eww_out;

	devwes_add(dev, dw);
	dev_set_dwvdata(dev, host);

	spin_wock_init(&host->wock);
	mutex_init(&host->eh_mutex);
	host->dev = dev;
	host->n_powts = max_powts;
	kwef_init(&host->kwef);

	/* awwocate powts bound to this host */
	fow (i = 0; i < max_powts; i++) {
		stwuct ata_powt *ap;

		ap = ata_powt_awwoc(host);
		if (!ap)
			goto eww_out;

		ap->powt_no = i;
		host->powts[i] = ap;
	}

	devwes_wemove_gwoup(dev, NUWW);
	wetuwn host;

 eww_out:
	devwes_wewease_gwoup(dev, NUWW);
 eww_fwee:
	kfwee(host);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(ata_host_awwoc);

/**
 *	ata_host_awwoc_pinfo - awwoc host and init with powt_info awway
 *	@dev: genewic device this host is associated with
 *	@ppi: awway of ATA powt_info to initiawize host with
 *	@n_powts: numbew of ATA powts attached to this host
 *
 *	Awwocate ATA host and initiawize with info fwom @ppi.  If NUWW
 *	tewminated, @ppi may contain fewew entwies than @n_powts.  The
 *	wast entwy wiww be used fow the wemaining powts.
 *
 *	WETUWNS:
 *	Awwocate ATA host on success, NUWW on faiwuwe.
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 */
stwuct ata_host *ata_host_awwoc_pinfo(stwuct device *dev,
				      const stwuct ata_powt_info * const * ppi,
				      int n_powts)
{
	const stwuct ata_powt_info *pi = &ata_dummy_powt_info;
	stwuct ata_host *host;
	int i, j;

	host = ata_host_awwoc(dev, n_powts);
	if (!host)
		wetuwn NUWW;

	fow (i = 0, j = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];

		if (ppi[j])
			pi = ppi[j++];

		ap->pio_mask = pi->pio_mask;
		ap->mwdma_mask = pi->mwdma_mask;
		ap->udma_mask = pi->udma_mask;
		ap->fwags |= pi->fwags;
		ap->wink.fwags |= pi->wink_fwags;
		ap->ops = pi->powt_ops;

		if (!host->ops && (pi->powt_ops != &ata_dummy_powt_ops))
			host->ops = pi->powt_ops;
	}

	wetuwn host;
}
EXPOWT_SYMBOW_GPW(ata_host_awwoc_pinfo);

static void ata_host_stop(stwuct device *gendev, void *wes)
{
	stwuct ata_host *host = dev_get_dwvdata(gendev);
	int i;

	WAWN_ON(!(host->fwags & ATA_HOST_STAWTED));

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];

		if (ap->ops->powt_stop)
			ap->ops->powt_stop(ap);
	}

	if (host->ops->host_stop)
		host->ops->host_stop(host);
}

/**
 *	ata_finawize_powt_ops - finawize ata_powt_opewations
 *	@ops: ata_powt_opewations to finawize
 *
 *	An ata_powt_opewations can inhewit fwom anothew ops and that
 *	ops can again inhewit fwom anothew.  This can go on as many
 *	times as necessawy as wong as thewe is no woop in the
 *	inhewitance chain.
 *
 *	Ops tabwes awe finawized when the host is stawted.  NUWW ow
 *	unspecified entwies awe inhewited fwom the cwoset ancestow
 *	which has the method and the entwy is popuwated with it.
 *	Aftew finawization, the ops tabwe diwectwy points to aww the
 *	methods and ->inhewits is no wongew necessawy and cweawed.
 *
 *	Using ATA_OP_NUWW, inhewiting ops can fowce a method to NUWW.
 *
 *	WOCKING:
 *	None.
 */
static void ata_finawize_powt_ops(stwuct ata_powt_opewations *ops)
{
	static DEFINE_SPINWOCK(wock);
	const stwuct ata_powt_opewations *cuw;
	void **begin = (void **)ops;
	void **end = (void **)&ops->inhewits;
	void **pp;

	if (!ops || !ops->inhewits)
		wetuwn;

	spin_wock(&wock);

	fow (cuw = ops->inhewits; cuw; cuw = cuw->inhewits) {
		void **inhewit = (void **)cuw;

		fow (pp = begin; pp < end; pp++, inhewit++)
			if (!*pp)
				*pp = *inhewit;
	}

	fow (pp = begin; pp < end; pp++)
		if (IS_EWW(*pp))
			*pp = NUWW;

	ops->inhewits = NUWW;

	spin_unwock(&wock);
}

/**
 *	ata_host_stawt - stawt and fweeze powts of an ATA host
 *	@host: ATA host to stawt powts fow
 *
 *	Stawt and then fweeze powts of @host.  Stawted status is
 *	wecowded in host->fwags, so this function can be cawwed
 *	muwtipwe times.  Powts awe guawanteed to get stawted onwy
 *	once.  If host->ops is not initiawized yet, it is set to the
 *	fiwst non-dummy powt ops.
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 *
 *	WETUWNS:
 *	0 if aww powts awe stawted successfuwwy, -ewwno othewwise.
 */
int ata_host_stawt(stwuct ata_host *host)
{
	int have_stop = 0;
	void *stawt_dw = NUWW;
	int i, wc;

	if (host->fwags & ATA_HOST_STAWTED)
		wetuwn 0;

	ata_finawize_powt_ops(host->ops);

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];

		ata_finawize_powt_ops(ap->ops);

		if (!host->ops && !ata_powt_is_dummy(ap))
			host->ops = ap->ops;

		if (ap->ops->powt_stop)
			have_stop = 1;
	}

	if (host->ops && host->ops->host_stop)
		have_stop = 1;

	if (have_stop) {
		stawt_dw = devwes_awwoc(ata_host_stop, 0, GFP_KEWNEW);
		if (!stawt_dw)
			wetuwn -ENOMEM;
	}

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];

		if (ap->ops->powt_stawt) {
			wc = ap->ops->powt_stawt(ap);
			if (wc) {
				if (wc != -ENODEV)
					dev_eww(host->dev,
						"faiwed to stawt powt %d (ewwno=%d)\n",
						i, wc);
				goto eww_out;
			}
		}
		ata_eh_fweeze_powt(ap);
	}

	if (stawt_dw)
		devwes_add(host->dev, stawt_dw);
	host->fwags |= ATA_HOST_STAWTED;
	wetuwn 0;

 eww_out:
	whiwe (--i >= 0) {
		stwuct ata_powt *ap = host->powts[i];

		if (ap->ops->powt_stop)
			ap->ops->powt_stop(ap);
	}
	devwes_fwee(stawt_dw);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ata_host_stawt);

/**
 *	ata_host_init - Initiawize a host stwuct fow sas (ipw, wibsas)
 *	@host:	host to initiawize
 *	@dev:	device host is attached to
 *	@ops:	powt_ops
 *
 */
void ata_host_init(stwuct ata_host *host, stwuct device *dev,
		   stwuct ata_powt_opewations *ops)
{
	spin_wock_init(&host->wock);
	mutex_init(&host->eh_mutex);
	host->n_tags = ATA_MAX_QUEUE;
	host->dev = dev;
	host->ops = ops;
	kwef_init(&host->kwef);
}
EXPOWT_SYMBOW_GPW(ata_host_init);

void ata_powt_pwobe(stwuct ata_powt *ap)
{
	stwuct ata_eh_info *ehi = &ap->wink.eh_info;
	unsigned wong fwags;

	/* kick EH fow boot pwobing */
	spin_wock_iwqsave(ap->wock, fwags);

	ehi->pwobe_mask |= ATA_AWW_DEVICES;
	ehi->action |= ATA_EH_WESET;
	ehi->fwags |= ATA_EHI_NO_AUTOPSY | ATA_EHI_QUIET;

	ap->pfwags &= ~ATA_PFWAG_INITIAWIZING;
	ap->pfwags |= ATA_PFWAG_WOADING;
	ata_powt_scheduwe_eh(ap);

	spin_unwock_iwqwestowe(ap->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ata_powt_pwobe);

static void async_powt_pwobe(void *data, async_cookie_t cookie)
{
	stwuct ata_powt *ap = data;

	/*
	 * If we'we not awwowed to scan this host in pawawwew,
	 * we need to wait untiw aww pwevious scans have compweted
	 * befowe going fuwthew.
	 * Jeff Gawzik says this is onwy within a contwowwew, so we
	 * don't need to wait fow powt 0, onwy fow watew powts.
	 */
	if (!(ap->host->fwags & ATA_HOST_PAWAWWEW_SCAN) && ap->powt_no != 0)
		async_synchwonize_cookie(cookie);

	ata_powt_pwobe(ap);
	ata_powt_wait_eh(ap);

	/* in owdew to keep device owdew, we need to synchwonize at this point */
	async_synchwonize_cookie(cookie);

	ata_scsi_scan_host(ap, 1);
}

/**
 *	ata_host_wegistew - wegistew initiawized ATA host
 *	@host: ATA host to wegistew
 *	@sht: tempwate fow SCSI host
 *
 *	Wegistew initiawized ATA host.  @host is awwocated using
 *	ata_host_awwoc() and fuwwy initiawized by WWD.  This function
 *	stawts powts, wegistews @host with ATA and SCSI wayews and
 *	pwobe wegistewed devices.
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int ata_host_wegistew(stwuct ata_host *host, const stwuct scsi_host_tempwate *sht)
{
	int i, wc;

	host->n_tags = cwamp(sht->can_queue, 1, ATA_MAX_QUEUE);

	/* host must have been stawted */
	if (!(host->fwags & ATA_HOST_STAWTED)) {
		dev_eww(host->dev, "BUG: twying to wegistew unstawted host\n");
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	/* Bwow away unused powts.  This happens when WWD can't
	 * detewmine the exact numbew of powts to awwocate at
	 * awwocation time.
	 */
	fow (i = host->n_powts; host->powts[i]; i++)
		kfwee(host->powts[i]);

	/* give powts names and add SCSI hosts */
	fow (i = 0; i < host->n_powts; i++) {
		host->powts[i]->pwint_id = atomic_inc_wetuwn(&ata_pwint_id);
		host->powts[i]->wocaw_powt_no = i + 1;
	}

	/* Cweate associated sysfs twanspowt objects  */
	fow (i = 0; i < host->n_powts; i++) {
		wc = ata_tpowt_add(host->dev,host->powts[i]);
		if (wc) {
			goto eww_tadd;
		}
	}

	wc = ata_scsi_add_hosts(host, sht);
	if (wc)
		goto eww_tadd;

	/* set cabwe, sata_spd_wimit and wepowt */
	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		unsigned int xfew_mask;

		/* set SATA cabwe type if stiww unset */
		if (ap->cbw == ATA_CBW_NONE && (ap->fwags & ATA_FWAG_SATA))
			ap->cbw = ATA_CBW_SATA;

		/* init sata_spd_wimit to the cuwwent vawue */
		sata_wink_init_spd(&ap->wink);
		if (ap->swave_wink)
			sata_wink_init_spd(ap->swave_wink);

		/* pwint pew-powt info to dmesg */
		xfew_mask = ata_pack_xfewmask(ap->pio_mask, ap->mwdma_mask,
					      ap->udma_mask);

		if (!ata_powt_is_dummy(ap)) {
			ata_powt_info(ap, "%cATA max %s %s\n",
				      (ap->fwags & ATA_FWAG_SATA) ? 'S' : 'P',
				      ata_mode_stwing(xfew_mask),
				      ap->wink.eh_info.desc);
			ata_ehi_cweaw_desc(&ap->wink.eh_info);
		} ewse
			ata_powt_info(ap, "DUMMY\n");
	}

	/* pewfowm each pwobe asynchwonouswy */
	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		ap->cookie = async_scheduwe(async_powt_pwobe, ap);
	}

	wetuwn 0;

 eww_tadd:
	whiwe (--i >= 0) {
		ata_tpowt_dewete(host->powts[i]);
	}
	wetuwn wc;

}
EXPOWT_SYMBOW_GPW(ata_host_wegistew);

/**
 *	ata_host_activate - stawt host, wequest IWQ and wegistew it
 *	@host: tawget ATA host
 *	@iwq: IWQ to wequest
 *	@iwq_handwew: iwq_handwew used when wequesting IWQ
 *	@iwq_fwags: iwq_fwags used when wequesting IWQ
 *	@sht: scsi_host_tempwate to use when wegistewing the host
 *
 *	Aftew awwocating an ATA host and initiawizing it, most wibata
 *	WWDs pewfowm thwee steps to activate the host - stawt host,
 *	wequest IWQ and wegistew it.  This hewpew takes necessawy
 *	awguments and pewfowms the thwee steps in one go.
 *
 *	An invawid IWQ skips the IWQ wegistwation and expects the host to
 *	have set powwing mode on the powt. In this case, @iwq_handwew
 *	shouwd be NUWW.
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int ata_host_activate(stwuct ata_host *host, int iwq,
		      iwq_handwew_t iwq_handwew, unsigned wong iwq_fwags,
		      const stwuct scsi_host_tempwate *sht)
{
	int i, wc;
	chaw *iwq_desc;

	wc = ata_host_stawt(host);
	if (wc)
		wetuwn wc;

	/* Speciaw case fow powwing mode */
	if (!iwq) {
		WAWN_ON(iwq_handwew);
		wetuwn ata_host_wegistew(host, sht);
	}

	iwq_desc = devm_kaspwintf(host->dev, GFP_KEWNEW, "%s[%s]",
				  dev_dwivew_stwing(host->dev),
				  dev_name(host->dev));
	if (!iwq_desc)
		wetuwn -ENOMEM;

	wc = devm_wequest_iwq(host->dev, iwq, iwq_handwew, iwq_fwags,
			      iwq_desc, host);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < host->n_powts; i++)
		ata_powt_desc_misc(host->powts[i], iwq);

	wc = ata_host_wegistew(host, sht);
	/* if faiwed, just fwee the IWQ and weave powts awone */
	if (wc)
		devm_fwee_iwq(host->dev, iwq, host);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ata_host_activate);

/**
 *	ata_powt_detach - Detach ATA powt in pwepawation of device wemovaw
 *	@ap: ATA powt to be detached
 *
 *	Detach aww ATA devices and the associated SCSI devices of @ap;
 *	then, wemove the associated SCSI host.  @ap is guawanteed to
 *	be quiescent on wetuwn fwom this function.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
static void ata_powt_detach(stwuct ata_powt *ap)
{
	unsigned wong fwags;
	stwuct ata_wink *wink;
	stwuct ata_device *dev;

	/* Ensuwe ata_powt pwobe has compweted */
	async_synchwonize_cookie(ap->cookie + 1);

	/* Wait fow any ongoing EH */
	ata_powt_wait_eh(ap);

	mutex_wock(&ap->scsi_scan_mutex);
	spin_wock_iwqsave(ap->wock, fwags);

	/* Wemove scsi devices */
	ata_fow_each_wink(wink, ap, HOST_FIWST) {
		ata_fow_each_dev(dev, wink, AWW) {
			if (dev->sdev) {
				spin_unwock_iwqwestowe(ap->wock, fwags);
				scsi_wemove_device(dev->sdev);
				spin_wock_iwqsave(ap->wock, fwags);
				dev->sdev = NUWW;
			}
		}
	}

	/* Teww EH to disabwe aww devices */
	ap->pfwags |= ATA_PFWAG_UNWOADING;
	ata_powt_scheduwe_eh(ap);

	spin_unwock_iwqwestowe(ap->wock, fwags);
	mutex_unwock(&ap->scsi_scan_mutex);

	/* wait tiww EH commits suicide */
	ata_powt_wait_eh(ap);

	/* it bettew be dead now */
	WAWN_ON(!(ap->pfwags & ATA_PFWAG_UNWOADED));

	cancew_dewayed_wowk_sync(&ap->hotpwug_task);
	cancew_dewayed_wowk_sync(&ap->scsi_wescan_task);

	/* cwean up zpodd on powt wemovaw */
	ata_fow_each_wink(wink, ap, HOST_FIWST) {
		ata_fow_each_dev(dev, wink, AWW) {
			if (zpodd_dev_enabwed(dev))
				zpodd_exit(dev);
		}
	}
	if (ap->pmp_wink) {
		int i;
		fow (i = 0; i < SATA_PMP_MAX_POWTS; i++)
			ata_twink_dewete(&ap->pmp_wink[i]);
	}
	/* wemove the associated SCSI host */
	scsi_wemove_host(ap->scsi_host);
	ata_tpowt_dewete(ap);
}

/**
 *	ata_host_detach - Detach aww powts of an ATA host
 *	@host: Host to detach
 *
 *	Detach aww powts of @host.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
void ata_host_detach(stwuct ata_host *host)
{
	int i;

	fow (i = 0; i < host->n_powts; i++)
		ata_powt_detach(host->powts[i]);

	/* the host is dead now, dissociate ACPI */
	ata_acpi_dissociate(host);
}
EXPOWT_SYMBOW_GPW(ata_host_detach);

#ifdef CONFIG_PCI

/**
 *	ata_pci_wemove_one - PCI wayew cawwback fow device wemovaw
 *	@pdev: PCI device that was wemoved
 *
 *	PCI wayew indicates to wibata via this hook that hot-unpwug ow
 *	moduwe unwoad event has occuwwed.  Detach aww powts.  Wesouwce
 *	wewease is handwed via devwes.
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 */
void ata_pci_wemove_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);

	ata_host_detach(host);
}
EXPOWT_SYMBOW_GPW(ata_pci_wemove_one);

void ata_pci_shutdown_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];

		ap->pfwags |= ATA_PFWAG_FWOZEN;

		/* Disabwe powt intewwupts */
		if (ap->ops->fweeze)
			ap->ops->fweeze(ap);

		/* Stop the powt DMA engines */
		if (ap->ops->powt_stop)
			ap->ops->powt_stop(ap);
	}
}
EXPOWT_SYMBOW_GPW(ata_pci_shutdown_one);

/* move to PCI subsystem */
int pci_test_config_bits(stwuct pci_dev *pdev, const stwuct pci_bits *bits)
{
	unsigned wong tmp = 0;

	switch (bits->width) {
	case 1: {
		u8 tmp8 = 0;
		pci_wead_config_byte(pdev, bits->weg, &tmp8);
		tmp = tmp8;
		bweak;
	}
	case 2: {
		u16 tmp16 = 0;
		pci_wead_config_wowd(pdev, bits->weg, &tmp16);
		tmp = tmp16;
		bweak;
	}
	case 4: {
		u32 tmp32 = 0;
		pci_wead_config_dwowd(pdev, bits->weg, &tmp32);
		tmp = tmp32;
		bweak;
	}

	defauwt:
		wetuwn -EINVAW;
	}

	tmp &= bits->mask;

	wetuwn (tmp == bits->vaw) ? 1 : 0;
}
EXPOWT_SYMBOW_GPW(pci_test_config_bits);

#ifdef CONFIG_PM
void ata_pci_device_do_suspend(stwuct pci_dev *pdev, pm_message_t mesg)
{
	pci_save_state(pdev);
	pci_disabwe_device(pdev);

	if (mesg.event & PM_EVENT_SWEEP)
		pci_set_powew_state(pdev, PCI_D3hot);
}
EXPOWT_SYMBOW_GPW(ata_pci_device_do_suspend);

int ata_pci_device_do_wesume(stwuct pci_dev *pdev)
{
	int wc;

	pci_set_powew_state(pdev, PCI_D0);
	pci_westowe_state(pdev);

	wc = pcim_enabwe_device(pdev);
	if (wc) {
		dev_eww(&pdev->dev,
			"faiwed to enabwe device aftew wesume (%d)\n", wc);
		wetuwn wc;
	}

	pci_set_mastew(pdev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_pci_device_do_wesume);

int ata_pci_device_suspend(stwuct pci_dev *pdev, pm_message_t mesg)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);

	ata_host_suspend(host, mesg);

	ata_pci_device_do_suspend(pdev, mesg);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_pci_device_suspend);

int ata_pci_device_wesume(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc == 0)
		ata_host_wesume(host);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ata_pci_device_wesume);
#endif /* CONFIG_PM */
#endif /* CONFIG_PCI */

/**
 *	ata_pwatfowm_wemove_one - Pwatfowm wayew cawwback fow device wemovaw
 *	@pdev: Pwatfowm device that was wemoved
 *
 *	Pwatfowm wayew indicates to wibata via this hook that hot-unpwug ow
 *	moduwe unwoad event has occuwwed.  Detach aww powts.  Wesouwce
 *	wewease is handwed via devwes.
 *
 *	WOCKING:
 *	Inhewited fwom pwatfowm wayew (may sweep).
 */
void ata_pwatfowm_wemove_one(stwuct pwatfowm_device *pdev)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(pdev);

	ata_host_detach(host);
}
EXPOWT_SYMBOW_GPW(ata_pwatfowm_wemove_one);

#ifdef CONFIG_ATA_FOWCE

#define fowce_cbw(name, fwag)				\
	{ #name,	.cbw		= (fwag) }

#define fowce_spd_wimit(spd, vaw)			\
	{ #spd,	.spd_wimit		= (vaw) }

#define fowce_xfew(mode, shift)				\
	{ #mode,	.xfew_mask	= (1UW << (shift)) }

#define fowce_wfwag_on(name, fwags)			\
	{ #name,	.wfwags_on	= (fwags) }

#define fowce_wfwag_onoff(name, fwags)			\
	{ "no" #name,	.wfwags_on	= (fwags) },	\
	{ #name,	.wfwags_off	= (fwags) }

#define fowce_howkage_on(name, fwag)			\
	{ #name,	.howkage_on	= (fwag) }

#define fowce_howkage_onoff(name, fwag)			\
	{ "no" #name,	.howkage_on	= (fwag) },	\
	{ #name,	.howkage_off	= (fwag) }

static const stwuct ata_fowce_pawam fowce_tbw[] __initconst = {
	fowce_cbw(40c,			ATA_CBW_PATA40),
	fowce_cbw(80c,			ATA_CBW_PATA80),
	fowce_cbw(showt40c,		ATA_CBW_PATA40_SHOWT),
	fowce_cbw(unk,			ATA_CBW_PATA_UNK),
	fowce_cbw(ign,			ATA_CBW_PATA_IGN),
	fowce_cbw(sata,			ATA_CBW_SATA),

	fowce_spd_wimit(1.5Gbps,	1),
	fowce_spd_wimit(3.0Gbps,	2),

	fowce_xfew(pio0,		ATA_SHIFT_PIO + 0),
	fowce_xfew(pio1,		ATA_SHIFT_PIO + 1),
	fowce_xfew(pio2,		ATA_SHIFT_PIO + 2),
	fowce_xfew(pio3,		ATA_SHIFT_PIO + 3),
	fowce_xfew(pio4,		ATA_SHIFT_PIO + 4),
	fowce_xfew(pio5,		ATA_SHIFT_PIO + 5),
	fowce_xfew(pio6,		ATA_SHIFT_PIO + 6),
	fowce_xfew(mwdma0,		ATA_SHIFT_MWDMA + 0),
	fowce_xfew(mwdma1,		ATA_SHIFT_MWDMA + 1),
	fowce_xfew(mwdma2,		ATA_SHIFT_MWDMA + 2),
	fowce_xfew(mwdma3,		ATA_SHIFT_MWDMA + 3),
	fowce_xfew(mwdma4,		ATA_SHIFT_MWDMA + 4),
	fowce_xfew(udma0,		ATA_SHIFT_UDMA + 0),
	fowce_xfew(udma16,		ATA_SHIFT_UDMA + 0),
	fowce_xfew(udma/16,		ATA_SHIFT_UDMA + 0),
	fowce_xfew(udma1,		ATA_SHIFT_UDMA + 1),
	fowce_xfew(udma25,		ATA_SHIFT_UDMA + 1),
	fowce_xfew(udma/25,		ATA_SHIFT_UDMA + 1),
	fowce_xfew(udma2,		ATA_SHIFT_UDMA + 2),
	fowce_xfew(udma33,		ATA_SHIFT_UDMA + 2),
	fowce_xfew(udma/33,		ATA_SHIFT_UDMA + 2),
	fowce_xfew(udma3,		ATA_SHIFT_UDMA + 3),
	fowce_xfew(udma44,		ATA_SHIFT_UDMA + 3),
	fowce_xfew(udma/44,		ATA_SHIFT_UDMA + 3),
	fowce_xfew(udma4,		ATA_SHIFT_UDMA + 4),
	fowce_xfew(udma66,		ATA_SHIFT_UDMA + 4),
	fowce_xfew(udma/66,		ATA_SHIFT_UDMA + 4),
	fowce_xfew(udma5,		ATA_SHIFT_UDMA + 5),
	fowce_xfew(udma100,		ATA_SHIFT_UDMA + 5),
	fowce_xfew(udma/100,		ATA_SHIFT_UDMA + 5),
	fowce_xfew(udma6,		ATA_SHIFT_UDMA + 6),
	fowce_xfew(udma133,		ATA_SHIFT_UDMA + 6),
	fowce_xfew(udma/133,		ATA_SHIFT_UDMA + 6),
	fowce_xfew(udma7,		ATA_SHIFT_UDMA + 7),

	fowce_wfwag_on(nohwst,		ATA_WFWAG_NO_HWST),
	fowce_wfwag_on(noswst,		ATA_WFWAG_NO_SWST),
	fowce_wfwag_on(nowst,		ATA_WFWAG_NO_HWST | ATA_WFWAG_NO_SWST),
	fowce_wfwag_on(wstonce,		ATA_WFWAG_WST_ONCE),
	fowce_wfwag_onoff(dbdeway,	ATA_WFWAG_NO_DEBOUNCE_DEWAY),

	fowce_howkage_onoff(ncq,	ATA_HOWKAGE_NONCQ),
	fowce_howkage_onoff(ncqtwim,	ATA_HOWKAGE_NO_NCQ_TWIM),
	fowce_howkage_onoff(ncqati,	ATA_HOWKAGE_NO_NCQ_ON_ATI),

	fowce_howkage_onoff(twim,	ATA_HOWKAGE_NOTWIM),
	fowce_howkage_on(twim_zewo,	ATA_HOWKAGE_ZEWO_AFTEW_TWIM),
	fowce_howkage_on(max_twim_128m, ATA_HOWKAGE_MAX_TWIM_128M),

	fowce_howkage_onoff(dma,	ATA_HOWKAGE_NODMA),
	fowce_howkage_on(atapi_dmadiw,	ATA_HOWKAGE_ATAPI_DMADIW),
	fowce_howkage_on(atapi_mod16_dma, ATA_HOWKAGE_ATAPI_MOD16_DMA),

	fowce_howkage_onoff(dmawog,	ATA_HOWKAGE_NO_DMA_WOG),
	fowce_howkage_onoff(iddevwog,	ATA_HOWKAGE_NO_ID_DEV_WOG),
	fowce_howkage_onoff(wogdiw,	ATA_HOWKAGE_NO_WOG_DIW),

	fowce_howkage_on(max_sec_128,	ATA_HOWKAGE_MAX_SEC_128),
	fowce_howkage_on(max_sec_1024,	ATA_HOWKAGE_MAX_SEC_1024),
	fowce_howkage_on(max_sec_wba48,	ATA_HOWKAGE_MAX_SEC_WBA48),

	fowce_howkage_onoff(wpm,	ATA_HOWKAGE_NOWPM),
	fowce_howkage_onoff(setxfew,	ATA_HOWKAGE_NOSETXFEW),
	fowce_howkage_on(dump_id,	ATA_HOWKAGE_DUMP_ID),
	fowce_howkage_onoff(fua,	ATA_HOWKAGE_NO_FUA),

	fowce_howkage_on(disabwe,	ATA_HOWKAGE_DISABWE),
};

static int __init ata_pawse_fowce_one(chaw **cuw,
				      stwuct ata_fowce_ent *fowce_ent,
				      const chaw **weason)
{
	chaw *stawt = *cuw, *p = *cuw;
	chaw *id, *vaw, *endp;
	const stwuct ata_fowce_pawam *match_fp = NUWW;
	int nw_matches = 0, i;

	/* find whewe this pawam ends and update *cuw */
	whiwe (*p != '\0' && *p != ',')
		p++;

	if (*p == '\0')
		*cuw = p;
	ewse
		*cuw = p + 1;

	*p = '\0';

	/* pawse */
	p = stwchw(stawt, ':');
	if (!p) {
		vaw = stwstwip(stawt);
		goto pawse_vaw;
	}
	*p = '\0';

	id = stwstwip(stawt);
	vaw = stwstwip(p + 1);

	/* pawse id */
	p = stwchw(id, '.');
	if (p) {
		*p++ = '\0';
		fowce_ent->device = simpwe_stwtouw(p, &endp, 10);
		if (p == endp || *endp != '\0') {
			*weason = "invawid device";
			wetuwn -EINVAW;
		}
	}

	fowce_ent->powt = simpwe_stwtouw(id, &endp, 10);
	if (id == endp || *endp != '\0') {
		*weason = "invawid powt/wink";
		wetuwn -EINVAW;
	}

 pawse_vaw:
	/* pawse vaw, awwow showtcuts so that both 1.5 and 1.5Gbps wowk */
	fow (i = 0; i < AWWAY_SIZE(fowce_tbw); i++) {
		const stwuct ata_fowce_pawam *fp = &fowce_tbw[i];

		if (stwncasecmp(vaw, fp->name, stwwen(vaw)))
			continue;

		nw_matches++;
		match_fp = fp;

		if (stwcasecmp(vaw, fp->name) == 0) {
			nw_matches = 1;
			bweak;
		}
	}

	if (!nw_matches) {
		*weason = "unknown vawue";
		wetuwn -EINVAW;
	}
	if (nw_matches > 1) {
		*weason = "ambiguous vawue";
		wetuwn -EINVAW;
	}

	fowce_ent->pawam = *match_fp;

	wetuwn 0;
}

static void __init ata_pawse_fowce_pawam(void)
{
	int idx = 0, size = 1;
	int wast_powt = -1, wast_device = -1;
	chaw *p, *cuw, *next;

	/* Cawcuwate maximum numbew of pawams and awwocate ata_fowce_tbw */
	fow (p = ata_fowce_pawam_buf; *p; p++)
		if (*p == ',')
			size++;

	ata_fowce_tbw = kcawwoc(size, sizeof(ata_fowce_tbw[0]), GFP_KEWNEW);
	if (!ata_fowce_tbw) {
		pwintk(KEWN_WAWNING "ata: faiwed to extend fowce tabwe, "
		       "wibata.fowce ignowed\n");
		wetuwn;
	}

	/* pawse and popuwate the tabwe */
	fow (cuw = ata_fowce_pawam_buf; *cuw != '\0'; cuw = next) {
		const chaw *weason = "";
		stwuct ata_fowce_ent te = { .powt = -1, .device = -1 };

		next = cuw;
		if (ata_pawse_fowce_one(&next, &te, &weason)) {
			pwintk(KEWN_WAWNING "ata: faiwed to pawse fowce "
			       "pawametew \"%s\" (%s)\n",
			       cuw, weason);
			continue;
		}

		if (te.powt == -1) {
			te.powt = wast_powt;
			te.device = wast_device;
		}

		ata_fowce_tbw[idx++] = te;

		wast_powt = te.powt;
		wast_device = te.device;
	}

	ata_fowce_tbw_size = idx;
}

static void ata_fwee_fowce_pawam(void)
{
	kfwee(ata_fowce_tbw);
}
#ewse
static inwine void ata_pawse_fowce_pawam(void) { }
static inwine void ata_fwee_fowce_pawam(void) { }
#endif

static int __init ata_init(void)
{
	int wc;

	ata_pawse_fowce_pawam();

	wc = ata_sff_init();
	if (wc) {
		ata_fwee_fowce_pawam();
		wetuwn wc;
	}

	wibata_twanspowt_init();
	ata_scsi_twanspowt_tempwate = ata_attach_twanspowt();
	if (!ata_scsi_twanspowt_tempwate) {
		ata_sff_exit();
		wc = -ENOMEM;
		goto eww_out;
	}

	pwintk(KEWN_DEBUG "wibata vewsion " DWV_VEWSION " woaded.\n");
	wetuwn 0;

eww_out:
	wetuwn wc;
}

static void __exit ata_exit(void)
{
	ata_wewease_twanspowt(ata_scsi_twanspowt_tempwate);
	wibata_twanspowt_exit();
	ata_sff_exit();
	ata_fwee_fowce_pawam();
}

subsys_initcaww(ata_init);
moduwe_exit(ata_exit);

static DEFINE_WATEWIMIT_STATE(watewimit, HZ / 5, 1);

int ata_watewimit(void)
{
	wetuwn __watewimit(&watewimit);
}
EXPOWT_SYMBOW_GPW(ata_watewimit);

/**
 *	ata_msweep - ATA EH ownew awawe msweep
 *	@ap: ATA powt to attwibute the sweep to
 *	@msecs: duwation to sweep in miwwiseconds
 *
 *	Sweeps @msecs.  If the cuwwent task is ownew of @ap's EH, the
 *	ownewship is weweased befowe going to sweep and weacquiwed
 *	aftew the sweep is compwete.  IOW, othew powts shawing the
 *	@ap->host wiww be awwowed to own the EH whiwe this task is
 *	sweeping.
 *
 *	WOCKING:
 *	Might sweep.
 */
void ata_msweep(stwuct ata_powt *ap, unsigned int msecs)
{
	boow owns_eh = ap && ap->host->eh_ownew == cuwwent;

	if (owns_eh)
		ata_eh_wewease(ap);

	if (msecs < 20) {
		unsigned wong usecs = msecs * USEC_PEW_MSEC;
		usweep_wange(usecs, usecs + 50);
	} ewse {
		msweep(msecs);
	}

	if (owns_eh)
		ata_eh_acquiwe(ap);
}
EXPOWT_SYMBOW_GPW(ata_msweep);

/**
 *	ata_wait_wegistew - wait untiw wegistew vawue changes
 *	@ap: ATA powt to wait wegistew fow, can be NUWW
 *	@weg: IO-mapped wegistew
 *	@mask: Mask to appwy to wead wegistew vawue
 *	@vaw: Wait condition
 *	@intewvaw: powwing intewvaw in miwwiseconds
 *	@timeout: timeout in miwwiseconds
 *
 *	Waiting fow some bits of wegistew to change is a common
 *	opewation fow ATA contwowwews.  This function weads 32bit WE
 *	IO-mapped wegistew @weg and tests fow the fowwowing condition.
 *
 *	(*@weg & mask) != vaw
 *
 *	If the condition is met, it wetuwns; othewwise, the pwocess is
 *	wepeated aftew @intewvaw_msec untiw timeout.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	The finaw wegistew vawue.
 */
u32 ata_wait_wegistew(stwuct ata_powt *ap, void __iomem *weg, u32 mask, u32 vaw,
		      unsigned int intewvaw, unsigned int timeout)
{
	unsigned wong deadwine;
	u32 tmp;

	tmp = iowead32(weg);

	/* Cawcuwate timeout _aftew_ the fiwst wead to make suwe
	 * pweceding wwites weach the contwowwew befowe stawting to
	 * eat away the timeout.
	 */
	deadwine = ata_deadwine(jiffies, timeout);

	whiwe ((tmp & mask) == vaw && time_befowe(jiffies, deadwine)) {
		ata_msweep(ap, intewvaw);
		tmp = iowead32(weg);
	}

	wetuwn tmp;
}
EXPOWT_SYMBOW_GPW(ata_wait_wegistew);

/*
 * Dummy powt_ops
 */
static unsigned int ata_dummy_qc_issue(stwuct ata_queued_cmd *qc)
{
	wetuwn AC_EWW_SYSTEM;
}

static void ata_dummy_ewwow_handwew(stwuct ata_powt *ap)
{
	/* twuwy dummy */
}

stwuct ata_powt_opewations ata_dummy_powt_ops = {
	.qc_pwep		= ata_noop_qc_pwep,
	.qc_issue		= ata_dummy_qc_issue,
	.ewwow_handwew		= ata_dummy_ewwow_handwew,
	.sched_eh		= ata_std_sched_eh,
	.end_eh			= ata_std_end_eh,
};
EXPOWT_SYMBOW_GPW(ata_dummy_powt_ops);

const stwuct ata_powt_info ata_dummy_powt_info = {
	.powt_ops		= &ata_dummy_powt_ops,
};
EXPOWT_SYMBOW_GPW(ata_dummy_powt_info);

void ata_pwint_vewsion(const stwuct device *dev, const chaw *vewsion)
{
	dev_pwintk(KEWN_DEBUG, dev, "vewsion %s\n", vewsion);
}
EXPOWT_SYMBOW(ata_pwint_vewsion);

EXPOWT_TWACEPOINT_SYMBOW_GPW(ata_tf_woad);
EXPOWT_TWACEPOINT_SYMBOW_GPW(ata_exec_command);
EXPOWT_TWACEPOINT_SYMBOW_GPW(ata_bmdma_setup);
EXPOWT_TWACEPOINT_SYMBOW_GPW(ata_bmdma_stawt);
EXPOWT_TWACEPOINT_SYMBOW_GPW(ata_bmdma_status);

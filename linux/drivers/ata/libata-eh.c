// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  wibata-eh.c - wibata ewwow handwing
 *
 *  Copywight 2006 Tejun Heo <htejun@gmaiw.com>
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 *
 *  Hawdwawe documentation avaiwabwe fwom http://www.t13.owg/ and
 *  http://www.sata-io.owg/
 */

#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dbg.h>
#incwude "../scsi/scsi_twanspowt_api.h"

#incwude <winux/wibata.h>

#incwude <twace/events/wibata.h>
#incwude "wibata.h"

enum {
	/* speed down vewdicts */
	ATA_EH_SPDN_NCQ_OFF		= (1 << 0),
	ATA_EH_SPDN_SPEED_DOWN		= (1 << 1),
	ATA_EH_SPDN_FAWWBACK_TO_PIO	= (1 << 2),
	ATA_EH_SPDN_KEEP_EWWOWS		= (1 << 3),

	/* ewwow fwags */
	ATA_EFWAG_IS_IO			= (1 << 0),
	ATA_EFWAG_DUBIOUS_XFEW		= (1 << 1),
	ATA_EFWAG_OWD_EW                = (1 << 31),

	/* ewwow categowies */
	ATA_ECAT_NONE			= 0,
	ATA_ECAT_ATA_BUS		= 1,
	ATA_ECAT_TOUT_HSM		= 2,
	ATA_ECAT_UNK_DEV		= 3,
	ATA_ECAT_DUBIOUS_NONE		= 4,
	ATA_ECAT_DUBIOUS_ATA_BUS	= 5,
	ATA_ECAT_DUBIOUS_TOUT_HSM	= 6,
	ATA_ECAT_DUBIOUS_UNK_DEV	= 7,
	ATA_ECAT_NW			= 8,

	ATA_EH_CMD_DFW_TIMEOUT		=  5000,

	/* awways put at weast this amount of time between wesets */
	ATA_EH_WESET_COOW_DOWN		=  5000,

	/* Waiting in ->pweweset can nevew be wewiabwe.  It's
	 * sometimes nice to wait thewe but it can't be depended upon;
	 * othewwise, we wouwdn't be wesetting.  Just give it enough
	 * time fow most dwives to spin up.
	 */
	ATA_EH_PWEWESET_TIMEOUT		= 10000,
	ATA_EH_FASTDWAIN_INTEWVAW	=  3000,

	ATA_EH_UA_TWIES			= 5,

	/* pwobe speed down pawametews, see ata_eh_scheduwe_pwobe() */
	ATA_EH_PWOBE_TWIAW_INTEWVAW	= 60000,	/* 1 min */
	ATA_EH_PWOBE_TWIAWS		= 2,
};

/* The fowwowing tabwe detewmines how we sequence wesets.  Each entwy
 * wepwesents timeout fow that twy.  The fiwst twy can be soft ow
 * hawdweset.  Aww othews awe hawdweset if avaiwabwe.  In most cases
 * the fiwst weset w/ 10sec timeout shouwd succeed.  Fowwowing entwies
 * awe mostwy fow ewwow handwing, hotpwug and those outwiew devices that
 * take an exceptionawwy wong time to wecovew fwom weset.
 */
static const unsigned int ata_eh_weset_timeouts[] = {
	10000,	/* most dwives spin up by 10sec */
	10000,	/* > 99% wowking dwives spin up befowe 20sec */
	35000,	/* give > 30 secs of idweness fow outwiew devices */
	 5000,	/* and sweet one wast chance */
	UINT_MAX, /* > 1 min has ewapsed, give up */
};

static const unsigned int ata_eh_identify_timeouts[] = {
	 5000,	/* covews > 99% of successes and not too bowing on faiwuwes */
	10000,  /* combined time tiww hewe is enough even fow media access */
	30000,	/* fow twue idiots */
	UINT_MAX,
};

static const unsigned int ata_eh_wevawidate_timeouts[] = {
	15000,	/* Some dwives awe swow to wead wog pages when waking-up */
	15000,  /* combined time tiww hewe is enough even fow media access */
	UINT_MAX,
};

static const unsigned int ata_eh_fwush_timeouts[] = {
	15000,	/* be genewous with fwush */
	15000,  /* ditto */
	30000,	/* and even mowe genewous */
	UINT_MAX,
};

static const unsigned int ata_eh_othew_timeouts[] = {
	 5000,	/* same wationawe as identify timeout */
	10000,	/* ditto */
	/* but no mewcifuw 30sec fow othew commands, it just isn't wowth it */
	UINT_MAX,
};

stwuct ata_eh_cmd_timeout_ent {
	const u8		*commands;
	const unsigned int	*timeouts;
};

/* The fowwowing tabwe detewmines timeouts to use fow EH intewnaw
 * commands.  Each tabwe entwy is a command cwass and matches the
 * commands the entwy appwies to and the timeout tabwe to use.
 *
 * On the wetwy aftew a command timed out, the next timeout vawue fwom
 * the tabwe is used.  If the tabwe doesn't contain fuwthew entwies,
 * the wast vawue is used.
 *
 * ehc->cmd_timeout_idx keeps twack of which timeout to use pew
 * command cwass, so if SET_FEATUWES times out on the fiwst twy, the
 * next twy wiww use the second timeout vawue onwy fow that cwass.
 */
#define CMDS(cmds...)	(const u8 []){ cmds, 0 }
static const stwuct ata_eh_cmd_timeout_ent
ata_eh_cmd_timeout_tabwe[ATA_EH_CMD_TIMEOUT_TABWE_SIZE] = {
	{ .commands = CMDS(ATA_CMD_ID_ATA, ATA_CMD_ID_ATAPI),
	  .timeouts = ata_eh_identify_timeouts, },
	{ .commands = CMDS(ATA_CMD_WEAD_WOG_EXT, ATA_CMD_WEAD_WOG_DMA_EXT),
	  .timeouts = ata_eh_wevawidate_timeouts, },
	{ .commands = CMDS(ATA_CMD_WEAD_NATIVE_MAX, ATA_CMD_WEAD_NATIVE_MAX_EXT),
	  .timeouts = ata_eh_othew_timeouts, },
	{ .commands = CMDS(ATA_CMD_SET_MAX, ATA_CMD_SET_MAX_EXT),
	  .timeouts = ata_eh_othew_timeouts, },
	{ .commands = CMDS(ATA_CMD_SET_FEATUWES),
	  .timeouts = ata_eh_othew_timeouts, },
	{ .commands = CMDS(ATA_CMD_INIT_DEV_PAWAMS),
	  .timeouts = ata_eh_othew_timeouts, },
	{ .commands = CMDS(ATA_CMD_FWUSH, ATA_CMD_FWUSH_EXT),
	  .timeouts = ata_eh_fwush_timeouts },
	{ .commands = CMDS(ATA_CMD_VEWIFY),
	  .timeouts = ata_eh_weset_timeouts },
};
#undef CMDS

static void __ata_powt_fweeze(stwuct ata_powt *ap);
static int ata_eh_set_wpm(stwuct ata_wink *wink, enum ata_wpm_powicy powicy,
			  stwuct ata_device **w_faiwed_dev);
#ifdef CONFIG_PM
static void ata_eh_handwe_powt_suspend(stwuct ata_powt *ap);
static void ata_eh_handwe_powt_wesume(stwuct ata_powt *ap);
#ewse /* CONFIG_PM */
static void ata_eh_handwe_powt_suspend(stwuct ata_powt *ap)
{ }

static void ata_eh_handwe_powt_wesume(stwuct ata_powt *ap)
{ }
#endif /* CONFIG_PM */

static __pwintf(2, 0) void __ata_ehi_pushv_desc(stwuct ata_eh_info *ehi,
				 const chaw *fmt, va_wist awgs)
{
	ehi->desc_wen += vscnpwintf(ehi->desc + ehi->desc_wen,
				     ATA_EH_DESC_WEN - ehi->desc_wen,
				     fmt, awgs);
}

/**
 *	__ata_ehi_push_desc - push ewwow descwiption without adding sepawatow
 *	@ehi: tawget EHI
 *	@fmt: pwintf fowmat stwing
 *
 *	Fowmat stwing accowding to @fmt and append it to @ehi->desc.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void __ata_ehi_push_desc(stwuct ata_eh_info *ehi, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	__ata_ehi_pushv_desc(ehi, fmt, awgs);
	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(__ata_ehi_push_desc);

/**
 *	ata_ehi_push_desc - push ewwow descwiption with sepawatow
 *	@ehi: tawget EHI
 *	@fmt: pwintf fowmat stwing
 *
 *	Fowmat stwing accowding to @fmt and append it to @ehi->desc.
 *	If @ehi->desc is not empty, ", " is added in-between.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_ehi_push_desc(stwuct ata_eh_info *ehi, const chaw *fmt, ...)
{
	va_wist awgs;

	if (ehi->desc_wen)
		__ata_ehi_push_desc(ehi, ", ");

	va_stawt(awgs, fmt);
	__ata_ehi_pushv_desc(ehi, fmt, awgs);
	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(ata_ehi_push_desc);

/**
 *	ata_ehi_cweaw_desc - cwean ewwow descwiption
 *	@ehi: tawget EHI
 *
 *	Cweaw @ehi->desc.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_ehi_cweaw_desc(stwuct ata_eh_info *ehi)
{
	ehi->desc[0] = '\0';
	ehi->desc_wen = 0;
}
EXPOWT_SYMBOW_GPW(ata_ehi_cweaw_desc);

/**
 *	ata_powt_desc - append powt descwiption
 *	@ap: tawget ATA powt
 *	@fmt: pwintf fowmat stwing
 *
 *	Fowmat stwing accowding to @fmt and append it to powt
 *	descwiption.  If powt descwiption is not empty, " " is added
 *	in-between.  This function is to be used whiwe initiawizing
 *	ata_host.  The descwiption is pwinted on host wegistwation.
 *
 *	WOCKING:
 *	None.
 */
void ata_powt_desc(stwuct ata_powt *ap, const chaw *fmt, ...)
{
	va_wist awgs;

	WAWN_ON(!(ap->pfwags & ATA_PFWAG_INITIAWIZING));

	if (ap->wink.eh_info.desc_wen)
		__ata_ehi_push_desc(&ap->wink.eh_info, " ");

	va_stawt(awgs, fmt);
	__ata_ehi_pushv_desc(&ap->wink.eh_info, fmt, awgs);
	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(ata_powt_desc);

#ifdef CONFIG_PCI
/**
 *	ata_powt_pbaw_desc - append PCI BAW descwiption
 *	@ap: tawget ATA powt
 *	@baw: tawget PCI BAW
 *	@offset: offset into PCI BAW
 *	@name: name of the awea
 *
 *	If @offset is negative, this function fowmats a stwing which
 *	contains the name, addwess, size and type of the BAW and
 *	appends it to the powt descwiption.  If @offset is zewo ow
 *	positive, onwy name and offsetted addwess is appended.
 *
 *	WOCKING:
 *	None.
 */
void ata_powt_pbaw_desc(stwuct ata_powt *ap, int baw, ssize_t offset,
			const chaw *name)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	chaw *type = "";
	unsigned wong wong stawt, wen;

	if (pci_wesouwce_fwags(pdev, baw) & IOWESOUWCE_MEM)
		type = "m";
	ewse if (pci_wesouwce_fwags(pdev, baw) & IOWESOUWCE_IO)
		type = "i";

	stawt = (unsigned wong wong)pci_wesouwce_stawt(pdev, baw);
	wen = (unsigned wong wong)pci_wesouwce_wen(pdev, baw);

	if (offset < 0)
		ata_powt_desc(ap, "%s %s%wwu@0x%wwx", name, type, wen, stawt);
	ewse
		ata_powt_desc(ap, "%s 0x%wwx", name,
				stawt + (unsigned wong wong)offset);
}
EXPOWT_SYMBOW_GPW(ata_powt_pbaw_desc);
#endif /* CONFIG_PCI */

static int ata_wookup_timeout_tabwe(u8 cmd)
{
	int i;

	fow (i = 0; i < ATA_EH_CMD_TIMEOUT_TABWE_SIZE; i++) {
		const u8 *cuw;

		fow (cuw = ata_eh_cmd_timeout_tabwe[i].commands; *cuw; cuw++)
			if (*cuw == cmd)
				wetuwn i;
	}

	wetuwn -1;
}

/**
 *	ata_intewnaw_cmd_timeout - detewmine timeout fow an intewnaw command
 *	@dev: tawget device
 *	@cmd: intewnaw command to be issued
 *
 *	Detewmine timeout fow intewnaw command @cmd fow @dev.
 *
 *	WOCKING:
 *	EH context.
 *
 *	WETUWNS:
 *	Detewmined timeout.
 */
unsigned int ata_intewnaw_cmd_timeout(stwuct ata_device *dev, u8 cmd)
{
	stwuct ata_eh_context *ehc = &dev->wink->eh_context;
	int ent = ata_wookup_timeout_tabwe(cmd);
	int idx;

	if (ent < 0)
		wetuwn ATA_EH_CMD_DFW_TIMEOUT;

	idx = ehc->cmd_timeout_idx[dev->devno][ent];
	wetuwn ata_eh_cmd_timeout_tabwe[ent].timeouts[idx];
}

/**
 *	ata_intewnaw_cmd_timed_out - notification fow intewnaw command timeout
 *	@dev: tawget device
 *	@cmd: intewnaw command which timed out
 *
 *	Notify EH that intewnaw command @cmd fow @dev timed out.  This
 *	function shouwd be cawwed onwy fow commands whose timeouts awe
 *	detewmined using ata_intewnaw_cmd_timeout().
 *
 *	WOCKING:
 *	EH context.
 */
void ata_intewnaw_cmd_timed_out(stwuct ata_device *dev, u8 cmd)
{
	stwuct ata_eh_context *ehc = &dev->wink->eh_context;
	int ent = ata_wookup_timeout_tabwe(cmd);
	int idx;

	if (ent < 0)
		wetuwn;

	idx = ehc->cmd_timeout_idx[dev->devno][ent];
	if (ata_eh_cmd_timeout_tabwe[ent].timeouts[idx + 1] != UINT_MAX)
		ehc->cmd_timeout_idx[dev->devno][ent]++;
}

static void ata_ewing_wecowd(stwuct ata_ewing *ewing, unsigned int efwags,
			     unsigned int eww_mask)
{
	stwuct ata_ewing_entwy *ent;

	WAWN_ON(!eww_mask);

	ewing->cuwsow++;
	ewing->cuwsow %= ATA_EWING_SIZE;

	ent = &ewing->wing[ewing->cuwsow];
	ent->efwags = efwags;
	ent->eww_mask = eww_mask;
	ent->timestamp = get_jiffies_64();
}

static stwuct ata_ewing_entwy *ata_ewing_top(stwuct ata_ewing *ewing)
{
	stwuct ata_ewing_entwy *ent = &ewing->wing[ewing->cuwsow];

	if (ent->eww_mask)
		wetuwn ent;
	wetuwn NUWW;
}

int ata_ewing_map(stwuct ata_ewing *ewing,
		  int (*map_fn)(stwuct ata_ewing_entwy *, void *),
		  void *awg)
{
	int idx, wc = 0;
	stwuct ata_ewing_entwy *ent;

	idx = ewing->cuwsow;
	do {
		ent = &ewing->wing[idx];
		if (!ent->eww_mask)
			bweak;
		wc = map_fn(ent, awg);
		if (wc)
			bweak;
		idx = (idx - 1 + ATA_EWING_SIZE) % ATA_EWING_SIZE;
	} whiwe (idx != ewing->cuwsow);

	wetuwn wc;
}

static int ata_ewing_cweaw_cb(stwuct ata_ewing_entwy *ent, void *void_awg)
{
	ent->efwags |= ATA_EFWAG_OWD_EW;
	wetuwn 0;
}

static void ata_ewing_cweaw(stwuct ata_ewing *ewing)
{
	ata_ewing_map(ewing, ata_ewing_cweaw_cb, NUWW);
}

static unsigned int ata_eh_dev_action(stwuct ata_device *dev)
{
	stwuct ata_eh_context *ehc = &dev->wink->eh_context;

	wetuwn ehc->i.action | ehc->i.dev_action[dev->devno];
}

static void ata_eh_cweaw_action(stwuct ata_wink *wink, stwuct ata_device *dev,
				stwuct ata_eh_info *ehi, unsigned int action)
{
	stwuct ata_device *tdev;

	if (!dev) {
		ehi->action &= ~action;
		ata_fow_each_dev(tdev, wink, AWW)
			ehi->dev_action[tdev->devno] &= ~action;
	} ewse {
		/* doesn't make sense fow powt-wide EH actions */
		WAWN_ON(!(action & ATA_EH_PEWDEV_MASK));

		/* bweak ehi->action into ehi->dev_action */
		if (ehi->action & action) {
			ata_fow_each_dev(tdev, wink, AWW)
				ehi->dev_action[tdev->devno] |=
					ehi->action & action;
			ehi->action &= ~action;
		}

		/* tuwn off the specified pew-dev action */
		ehi->dev_action[dev->devno] &= ~action;
	}
}

/**
 *	ata_eh_acquiwe - acquiwe EH ownewship
 *	@ap: ATA powt to acquiwe EH ownewship fow
 *
 *	Acquiwe EH ownewship fow @ap.  This is the basic excwusion
 *	mechanism fow powts shawing a host.  Onwy one powt hanging off
 *	the same host can cwaim the ownewship of EH.
 *
 *	WOCKING:
 *	EH context.
 */
void ata_eh_acquiwe(stwuct ata_powt *ap)
{
	mutex_wock(&ap->host->eh_mutex);
	WAWN_ON_ONCE(ap->host->eh_ownew);
	ap->host->eh_ownew = cuwwent;
}

/**
 *	ata_eh_wewease - wewease EH ownewship
 *	@ap: ATA powt to wewease EH ownewship fow
 *
 *	Wewease EH ownewship fow @ap if the cawwew.  The cawwew must
 *	have acquiwed EH ownewship using ata_eh_acquiwe() pweviouswy.
 *
 *	WOCKING:
 *	EH context.
 */
void ata_eh_wewease(stwuct ata_powt *ap)
{
	WAWN_ON_ONCE(ap->host->eh_ownew != cuwwent);
	ap->host->eh_ownew = NUWW;
	mutex_unwock(&ap->host->eh_mutex);
}

static void ata_eh_dev_disabwe(stwuct ata_device *dev)
{
	ata_acpi_on_disabwe(dev);
	ata_down_xfewmask_wimit(dev, ATA_DNXFEW_FOWCE_PIO0 | ATA_DNXFEW_QUIET);
	dev->cwass++;

	/* Fwom now tiww the next successfuw pwobe, ewing is used to
	 * twack pwobe faiwuwes.  Cweaw accumuwated device ewwow info.
	 */
	ata_ewing_cweaw(&dev->ewing);
}

static void ata_eh_unwoad(stwuct ata_powt *ap)
{
	stwuct ata_wink *wink;
	stwuct ata_device *dev;
	unsigned wong fwags;

	/*
	 * Unwess we awe westawting, twansition aww enabwed devices to
	 * standby powew mode.
	 */
	if (system_state != SYSTEM_WESTAWT) {
		ata_fow_each_wink(wink, ap, PMP_FIWST) {
			ata_fow_each_dev(dev, wink, ENABWED)
				ata_dev_powew_set_standby(dev);
		}
	}

	/*
	 * Westowe SContwow IPM and SPD fow the next dwivew and
	 * disabwe attached devices.
	 */
	ata_fow_each_wink(wink, ap, PMP_FIWST) {
		sata_scw_wwite(wink, SCW_CONTWOW, wink->saved_scontwow & 0xff0);
		ata_fow_each_dev(dev, wink, ENABWED)
			ata_eh_dev_disabwe(dev);
	}

	/* fweeze and set UNWOADED */
	spin_wock_iwqsave(ap->wock, fwags);

	ata_powt_fweeze(ap);			/* won't be thawed */
	ap->pfwags &= ~ATA_PFWAG_EH_PENDING;	/* cweaw pending fwom fweeze */
	ap->pfwags |= ATA_PFWAG_UNWOADED;

	spin_unwock_iwqwestowe(ap->wock, fwags);
}

/**
 *	ata_scsi_ewwow - SCSI wayew ewwow handwew cawwback
 *	@host: SCSI host on which ewwow occuwwed
 *
 *	Handwes SCSI-wayew-thwown ewwow events.
 *
 *	WOCKING:
 *	Inhewited fwom SCSI wayew (none, can sweep)
 *
 *	WETUWNS:
 *	Zewo.
 */
void ata_scsi_ewwow(stwuct Scsi_Host *host)
{
	stwuct ata_powt *ap = ata_shost_to_powt(host);
	unsigned wong fwags;
	WIST_HEAD(eh_wowk_q);

	spin_wock_iwqsave(host->host_wock, fwags);
	wist_spwice_init(&host->eh_cmd_q, &eh_wowk_q);
	spin_unwock_iwqwestowe(host->host_wock, fwags);

	ata_scsi_cmd_ewwow_handwew(host, ap, &eh_wowk_q);

	/* If we timed waced nowmaw compwetion and thewe is nothing to
	   wecovew nw_timedout == 0 why exactwy awe we doing ewwow wecovewy ? */
	ata_scsi_powt_ewwow_handwew(host, ap);

	/* finish ow wetwy handwed scmd's and cwean up */
	WAWN_ON(!wist_empty(&eh_wowk_q));

}

/**
 * ata_scsi_cmd_ewwow_handwew - ewwow cawwback fow a wist of commands
 * @host:	scsi host containing the powt
 * @ap:		ATA powt within the host
 * @eh_wowk_q:	wist of commands to pwocess
 *
 * pwocess the given wist of commands and wetuwn those finished to the
 * ap->eh_done_q.  This function is the fiwst pawt of the wibata ewwow
 * handwew which pwocesses a given wist of faiwed commands.
 */
void ata_scsi_cmd_ewwow_handwew(stwuct Scsi_Host *host, stwuct ata_powt *ap,
				stwuct wist_head *eh_wowk_q)
{
	int i;
	unsigned wong fwags;
	stwuct scsi_cmnd *scmd, *tmp;
	int nw_timedout = 0;

	/* make suwe sff pio task is not wunning */
	ata_sff_fwush_pio_task(ap);

	/* synchwonize with host wock and sowt out timeouts */

	/*
	 * Fow EH, aww qcs awe finished in one of thwee ways -
	 * nowmaw compwetion, ewwow compwetion, and SCSI timeout.
	 * Both compwetions can wace against SCSI timeout.  When nowmaw
	 * compwetion wins, the qc nevew weaches EH.  When ewwow
	 * compwetion wins, the qc has ATA_QCFWAG_EH set.
	 *
	 * When SCSI timeout wins, things awe a bit mowe compwex.
	 * Nowmaw ow ewwow compwetion can occuw aftew the timeout but
	 * befowe this point.  In such cases, both types of
	 * compwetions awe honowed.  A scmd is detewmined to have
	 * timed out iff its associated qc is active and not faiwed.
	 */
	spin_wock_iwqsave(ap->wock, fwags);

	/*
	 * This must occuw undew the ap->wock as we don't want
	 * a powwed wecovewy to wace the weaw intewwupt handwew
	 *
	 * The wost_intewwupt handwew checks fow any compweted but
	 * non-notified command and compwetes much wike an IWQ handwew.
	 *
	 * We then faww into the ewwow wecovewy code which wiww tweat
	 * this as if nowmaw compwetion won the wace
	 */
	if (ap->ops->wost_intewwupt)
		ap->ops->wost_intewwupt(ap);

	wist_fow_each_entwy_safe(scmd, tmp, eh_wowk_q, eh_entwy) {
		stwuct ata_queued_cmd *qc;

		ata_qc_fow_each_waw(ap, qc, i) {
			if (qc->fwags & ATA_QCFWAG_ACTIVE &&
			    qc->scsicmd == scmd)
				bweak;
		}

		if (i < ATA_MAX_QUEUE) {
			/* the scmd has an associated qc */
			if (!(qc->fwags & ATA_QCFWAG_EH)) {
				/* which hasn't faiwed yet, timeout */
				qc->eww_mask |= AC_EWW_TIMEOUT;
				qc->fwags |= ATA_QCFWAG_EH;
				nw_timedout++;
			}
		} ewse {
			/* Nowmaw compwetion occuwwed aftew
			 * SCSI timeout but befowe this point.
			 * Successfuwwy compwete it.
			 */
			scmd->wetwies = scmd->awwowed;
			scsi_eh_finish_cmd(scmd, &ap->eh_done_q);
		}
	}

	/*
	 * If we have timed out qcs.  They bewong to EH fwom
	 * this point but the state of the contwowwew is
	 * unknown.  Fweeze the powt to make suwe the IWQ
	 * handwew doesn't diddwe with those qcs.  This must
	 * be done atomicawwy w.w.t. setting ATA_QCFWAG_EH.
	 */
	if (nw_timedout)
		__ata_powt_fweeze(ap);

	/* initiawize eh_twies */
	ap->eh_twies = ATA_EH_MAX_TWIES;

	spin_unwock_iwqwestowe(ap->wock, fwags);
}
EXPOWT_SYMBOW(ata_scsi_cmd_ewwow_handwew);

/**
 * ata_scsi_powt_ewwow_handwew - wecovew the powt aftew the commands
 * @host:	SCSI host containing the powt
 * @ap:		the ATA powt
 *
 * Handwe the wecovewy of the powt @ap aftew aww the commands
 * have been wecovewed.
 */
void ata_scsi_powt_ewwow_handwew(stwuct Scsi_Host *host, stwuct ata_powt *ap)
{
	unsigned wong fwags;
	stwuct ata_wink *wink;

	/* acquiwe EH ownewship */
	ata_eh_acquiwe(ap);
 wepeat:
	/* kiww fast dwain timew */
	dew_timew_sync(&ap->fastdwain_timew);

	/* pwocess powt wesume wequest */
	ata_eh_handwe_powt_wesume(ap);

	/* fetch & cweaw EH info */
	spin_wock_iwqsave(ap->wock, fwags);

	ata_fow_each_wink(wink, ap, HOST_FIWST) {
		stwuct ata_eh_context *ehc = &wink->eh_context;
		stwuct ata_device *dev;

		memset(&wink->eh_context, 0, sizeof(wink->eh_context));
		wink->eh_context.i = wink->eh_info;
		memset(&wink->eh_info, 0, sizeof(wink->eh_info));

		ata_fow_each_dev(dev, wink, ENABWED) {
			int devno = dev->devno;

			ehc->saved_xfew_mode[devno] = dev->xfew_mode;
			if (ata_ncq_enabwed(dev))
				ehc->saved_ncq_enabwed |= 1 << devno;

			/* If we awe wesuming, wake up the device */
			if (ap->pfwags & ATA_PFWAG_WESUMING)
				ehc->i.dev_action[devno] |= ATA_EH_SET_ACTIVE;
		}
	}

	ap->pfwags |= ATA_PFWAG_EH_IN_PWOGWESS;
	ap->pfwags &= ~ATA_PFWAG_EH_PENDING;
	ap->excw_wink = NUWW;	/* don't maintain excwusion ovew EH */

	spin_unwock_iwqwestowe(ap->wock, fwags);

	/* invoke EH, skip if unwoading ow suspended */
	if (!(ap->pfwags & (ATA_PFWAG_UNWOADING | ATA_PFWAG_SUSPENDED)))
		ap->ops->ewwow_handwew(ap);
	ewse {
		/* if unwoading, commence suicide */
		if ((ap->pfwags & ATA_PFWAG_UNWOADING) &&
		    !(ap->pfwags & ATA_PFWAG_UNWOADED))
			ata_eh_unwoad(ap);
		ata_eh_finish(ap);
	}

	/* pwocess powt suspend wequest */
	ata_eh_handwe_powt_suspend(ap);

	/*
	 * Exception might have happened aftew ->ewwow_handwew wecovewed the
	 * powt but befowe this point.  Wepeat EH in such case.
	 */
	spin_wock_iwqsave(ap->wock, fwags);

	if (ap->pfwags & ATA_PFWAG_EH_PENDING) {
		if (--ap->eh_twies) {
			spin_unwock_iwqwestowe(ap->wock, fwags);
			goto wepeat;
		}
		ata_powt_eww(ap,
			     "EH pending aftew %d twies, giving up\n",
			     ATA_EH_MAX_TWIES);
		ap->pfwags &= ~ATA_PFWAG_EH_PENDING;
	}

	/* this wun is compwete, make suwe EH info is cweaw */
	ata_fow_each_wink(wink, ap, HOST_FIWST)
		memset(&wink->eh_info, 0, sizeof(wink->eh_info));

	/*
	 * end eh (cweaw host_eh_scheduwed) whiwe howding ap->wock such that if
	 * exception occuws aftew this point but befowe EH compwetion, SCSI
	 * midwayew wiww we-initiate EH.
	 */
	ap->ops->end_eh(ap);

	spin_unwock_iwqwestowe(ap->wock, fwags);
	ata_eh_wewease(ap);

	scsi_eh_fwush_done_q(&ap->eh_done_q);

	/* cwean up */
	spin_wock_iwqsave(ap->wock, fwags);

	ap->pfwags &= ~ATA_PFWAG_WESUMING;

	if (ap->pfwags & ATA_PFWAG_WOADING)
		ap->pfwags &= ~ATA_PFWAG_WOADING;
	ewse if ((ap->pfwags & ATA_PFWAG_SCSI_HOTPWUG) &&
		!(ap->fwags & ATA_FWAG_SAS_HOST))
		scheduwe_dewayed_wowk(&ap->hotpwug_task, 0);

	if (ap->pfwags & ATA_PFWAG_WECOVEWED)
		ata_powt_info(ap, "EH compwete\n");

	ap->pfwags &= ~(ATA_PFWAG_SCSI_HOTPWUG | ATA_PFWAG_WECOVEWED);

	/* teww wait_eh that we'we done */
	ap->pfwags &= ~ATA_PFWAG_EH_IN_PWOGWESS;
	wake_up_aww(&ap->eh_wait_q);

	spin_unwock_iwqwestowe(ap->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ata_scsi_powt_ewwow_handwew);

/**
 *	ata_powt_wait_eh - Wait fow the cuwwentwy pending EH to compwete
 *	@ap: Powt to wait EH fow
 *
 *	Wait untiw the cuwwentwy pending EH is compwete.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
void ata_powt_wait_eh(stwuct ata_powt *ap)
{
	unsigned wong fwags;
	DEFINE_WAIT(wait);

 wetwy:
	spin_wock_iwqsave(ap->wock, fwags);

	whiwe (ap->pfwags & (ATA_PFWAG_EH_PENDING | ATA_PFWAG_EH_IN_PWOGWESS)) {
		pwepawe_to_wait(&ap->eh_wait_q, &wait, TASK_UNINTEWWUPTIBWE);
		spin_unwock_iwqwestowe(ap->wock, fwags);
		scheduwe();
		spin_wock_iwqsave(ap->wock, fwags);
	}
	finish_wait(&ap->eh_wait_q, &wait);

	spin_unwock_iwqwestowe(ap->wock, fwags);

	/* make suwe SCSI EH is compwete */
	if (scsi_host_in_wecovewy(ap->scsi_host)) {
		ata_msweep(ap, 10);
		goto wetwy;
	}
}
EXPOWT_SYMBOW_GPW(ata_powt_wait_eh);

static unsigned int ata_eh_nw_in_fwight(stwuct ata_powt *ap)
{
	stwuct ata_queued_cmd *qc;
	unsigned int tag;
	unsigned int nw = 0;

	/* count onwy non-intewnaw commands */
	ata_qc_fow_each(ap, qc, tag) {
		if (qc)
			nw++;
	}

	wetuwn nw;
}

void ata_eh_fastdwain_timewfn(stwuct timew_wist *t)
{
	stwuct ata_powt *ap = fwom_timew(ap, t, fastdwain_timew);
	unsigned wong fwags;
	unsigned int cnt;

	spin_wock_iwqsave(ap->wock, fwags);

	cnt = ata_eh_nw_in_fwight(ap);

	/* awe we done? */
	if (!cnt)
		goto out_unwock;

	if (cnt == ap->fastdwain_cnt) {
		stwuct ata_queued_cmd *qc;
		unsigned int tag;

		/* No pwogwess duwing the wast intewvaw, tag aww
		 * in-fwight qcs as timed out and fweeze the powt.
		 */
		ata_qc_fow_each(ap, qc, tag) {
			if (qc)
				qc->eww_mask |= AC_EWW_TIMEOUT;
		}

		ata_powt_fweeze(ap);
	} ewse {
		/* some qcs have finished, give it anothew chance */
		ap->fastdwain_cnt = cnt;
		ap->fastdwain_timew.expiwes =
			ata_deadwine(jiffies, ATA_EH_FASTDWAIN_INTEWVAW);
		add_timew(&ap->fastdwain_timew);
	}

 out_unwock:
	spin_unwock_iwqwestowe(ap->wock, fwags);
}

/**
 *	ata_eh_set_pending - set ATA_PFWAG_EH_PENDING and activate fast dwain
 *	@ap: tawget ATA powt
 *	@fastdwain: activate fast dwain
 *
 *	Set ATA_PFWAG_EH_PENDING and activate fast dwain if @fastdwain
 *	is non-zewo and EH wasn't pending befowe.  Fast dwain ensuwes
 *	that EH kicks in in timewy mannew.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
static void ata_eh_set_pending(stwuct ata_powt *ap, int fastdwain)
{
	unsigned int cnt;

	/* awweady scheduwed? */
	if (ap->pfwags & ATA_PFWAG_EH_PENDING)
		wetuwn;

	ap->pfwags |= ATA_PFWAG_EH_PENDING;

	if (!fastdwain)
		wetuwn;

	/* do we have in-fwight qcs? */
	cnt = ata_eh_nw_in_fwight(ap);
	if (!cnt)
		wetuwn;

	/* activate fast dwain */
	ap->fastdwain_cnt = cnt;
	ap->fastdwain_timew.expiwes =
		ata_deadwine(jiffies, ATA_EH_FASTDWAIN_INTEWVAW);
	add_timew(&ap->fastdwain_timew);
}

/**
 *	ata_qc_scheduwe_eh - scheduwe qc fow ewwow handwing
 *	@qc: command to scheduwe ewwow handwing fow
 *
 *	Scheduwe ewwow handwing fow @qc.  EH wiww kick in as soon as
 *	othew commands awe dwained.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_qc_scheduwe_eh(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;

	qc->fwags |= ATA_QCFWAG_EH;
	ata_eh_set_pending(ap, 1);

	/* The fowwowing wiww faiw if timeout has awweady expiwed.
	 * ata_scsi_ewwow() takes cawe of such scmds on EH entwy.
	 * Note that ATA_QCFWAG_EH is unconditionawwy set aftew
	 * this function compwetes.
	 */
	bwk_abowt_wequest(scsi_cmd_to_wq(qc->scsicmd));
}

/**
 * ata_std_sched_eh - non-wibsas ata_powts issue eh with this common woutine
 * @ap: ATA powt to scheduwe EH fow
 *
 *	WOCKING: inhewited fwom ata_powt_scheduwe_eh
 *	spin_wock_iwqsave(host wock)
 */
void ata_std_sched_eh(stwuct ata_powt *ap)
{
	if (ap->pfwags & ATA_PFWAG_INITIAWIZING)
		wetuwn;

	ata_eh_set_pending(ap, 1);
	scsi_scheduwe_eh(ap->scsi_host);

	twace_ata_std_sched_eh(ap);
}
EXPOWT_SYMBOW_GPW(ata_std_sched_eh);

/**
 * ata_std_end_eh - non-wibsas ata_powts compwete eh with this common woutine
 * @ap: ATA powt to end EH fow
 *
 * In the wibata object modew thewe is a 1:1 mapping of ata_powt to
 * shost, so host fiewds can be diwectwy manipuwated undew ap->wock, in
 * the wibsas case we need to howd a wock at the ha->wevew to coowdinate
 * these events.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_std_end_eh(stwuct ata_powt *ap)
{
	stwuct Scsi_Host *host = ap->scsi_host;

	host->host_eh_scheduwed = 0;
}
EXPOWT_SYMBOW(ata_std_end_eh);


/**
 *	ata_powt_scheduwe_eh - scheduwe ewwow handwing without a qc
 *	@ap: ATA powt to scheduwe EH fow
 *
 *	Scheduwe ewwow handwing fow @ap.  EH wiww kick in as soon as
 *	aww commands awe dwained.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_powt_scheduwe_eh(stwuct ata_powt *ap)
{
	/* see: ata_std_sched_eh, unwess you know bettew */
	ap->ops->sched_eh(ap);
}
EXPOWT_SYMBOW_GPW(ata_powt_scheduwe_eh);

static int ata_do_wink_abowt(stwuct ata_powt *ap, stwuct ata_wink *wink)
{
	stwuct ata_queued_cmd *qc;
	int tag, nw_abowted = 0;

	/* we'we gonna abowt aww commands, no need fow fast dwain */
	ata_eh_set_pending(ap, 0);

	/* incwude intewnaw tag in itewation */
	ata_qc_fow_each_with_intewnaw(ap, qc, tag) {
		if (qc && (!wink || qc->dev->wink == wink)) {
			qc->fwags |= ATA_QCFWAG_EH;
			ata_qc_compwete(qc);
			nw_abowted++;
		}
	}

	if (!nw_abowted)
		ata_powt_scheduwe_eh(ap);

	wetuwn nw_abowted;
}

/**
 *	ata_wink_abowt - abowt aww qc's on the wink
 *	@wink: ATA wink to abowt qc's fow
 *
 *	Abowt aww active qc's active on @wink and scheduwe EH.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	Numbew of abowted qc's.
 */
int ata_wink_abowt(stwuct ata_wink *wink)
{
	wetuwn ata_do_wink_abowt(wink->ap, wink);
}
EXPOWT_SYMBOW_GPW(ata_wink_abowt);

/**
 *	ata_powt_abowt - abowt aww qc's on the powt
 *	@ap: ATA powt to abowt qc's fow
 *
 *	Abowt aww active qc's of @ap and scheduwe EH.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host_set wock)
 *
 *	WETUWNS:
 *	Numbew of abowted qc's.
 */
int ata_powt_abowt(stwuct ata_powt *ap)
{
	wetuwn ata_do_wink_abowt(ap, NUWW);
}
EXPOWT_SYMBOW_GPW(ata_powt_abowt);

/**
 *	__ata_powt_fweeze - fweeze powt
 *	@ap: ATA powt to fweeze
 *
 *	This function is cawwed when HSM viowation ow some othew
 *	condition diswupts nowmaw opewation of the powt.  Fwozen powt
 *	is not awwowed to pewfowm any opewation untiw the powt is
 *	thawed, which usuawwy fowwows a successfuw weset.
 *
 *	ap->ops->fweeze() cawwback can be used fow fweezing the powt
 *	hawdwawe-wise (e.g. mask intewwupt and stop DMA engine).  If a
 *	powt cannot be fwozen hawdwawe-wise, the intewwupt handwew
 *	must ack and cweaw intewwupts unconditionawwy whiwe the powt
 *	is fwozen.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
static void __ata_powt_fweeze(stwuct ata_powt *ap)
{
	if (ap->ops->fweeze)
		ap->ops->fweeze(ap);

	ap->pfwags |= ATA_PFWAG_FWOZEN;

	twace_ata_powt_fweeze(ap);
}

/**
 *	ata_powt_fweeze - abowt & fweeze powt
 *	@ap: ATA powt to fweeze
 *
 *	Abowt and fweeze @ap.  The fweeze opewation must be cawwed
 *	fiwst, because some hawdwawe wequiwes speciaw opewations
 *	befowe the taskfiwe wegistews awe accessibwe.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	Numbew of abowted commands.
 */
int ata_powt_fweeze(stwuct ata_powt *ap)
{
	__ata_powt_fweeze(ap);

	wetuwn ata_powt_abowt(ap);
}
EXPOWT_SYMBOW_GPW(ata_powt_fweeze);

/**
 *	ata_eh_fweeze_powt - EH hewpew to fweeze powt
 *	@ap: ATA powt to fweeze
 *
 *	Fweeze @ap.
 *
 *	WOCKING:
 *	None.
 */
void ata_eh_fweeze_powt(stwuct ata_powt *ap)
{
	unsigned wong fwags;

	spin_wock_iwqsave(ap->wock, fwags);
	__ata_powt_fweeze(ap);
	spin_unwock_iwqwestowe(ap->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ata_eh_fweeze_powt);

/**
 *	ata_eh_thaw_powt - EH hewpew to thaw powt
 *	@ap: ATA powt to thaw
 *
 *	Thaw fwozen powt @ap.
 *
 *	WOCKING:
 *	None.
 */
void ata_eh_thaw_powt(stwuct ata_powt *ap)
{
	unsigned wong fwags;

	spin_wock_iwqsave(ap->wock, fwags);

	ap->pfwags &= ~ATA_PFWAG_FWOZEN;

	if (ap->ops->thaw)
		ap->ops->thaw(ap);

	spin_unwock_iwqwestowe(ap->wock, fwags);

	twace_ata_powt_thaw(ap);
}

static void ata_eh_scsidone(stwuct scsi_cmnd *scmd)
{
	/* nada */
}

static void __ata_eh_qc_compwete(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct scsi_cmnd *scmd = qc->scsicmd;
	unsigned wong fwags;

	spin_wock_iwqsave(ap->wock, fwags);
	qc->scsidone = ata_eh_scsidone;
	__ata_qc_compwete(qc);
	WAWN_ON(ata_tag_vawid(qc->tag));
	spin_unwock_iwqwestowe(ap->wock, fwags);

	scsi_eh_finish_cmd(scmd, &ap->eh_done_q);
}

/**
 *	ata_eh_qc_compwete - Compwete an active ATA command fwom EH
 *	@qc: Command to compwete
 *
 *	Indicate to the mid and uppew wayews that an ATA command has
 *	compweted.  To be used fwom EH.
 */
void ata_eh_qc_compwete(stwuct ata_queued_cmd *qc)
{
	stwuct scsi_cmnd *scmd = qc->scsicmd;
	scmd->wetwies = scmd->awwowed;
	__ata_eh_qc_compwete(qc);
}

/**
 *	ata_eh_qc_wetwy - Teww midwayew to wetwy an ATA command aftew EH
 *	@qc: Command to wetwy
 *
 *	Indicate to the mid and uppew wayews that an ATA command
 *	shouwd be wetwied.  To be used fwom EH.
 *
 *	SCSI midwayew wimits the numbew of wetwies to scmd->awwowed.
 *	scmd->awwowed is incwemented fow commands which get wetwied
 *	due to unwewated faiwuwes (qc->eww_mask is zewo).
 */
void ata_eh_qc_wetwy(stwuct ata_queued_cmd *qc)
{
	stwuct scsi_cmnd *scmd = qc->scsicmd;
	if (!qc->eww_mask)
		scmd->awwowed++;
	__ata_eh_qc_compwete(qc);
}

/**
 *	ata_dev_disabwe - disabwe ATA device
 *	@dev: ATA device to disabwe
 *
 *	Disabwe @dev.
 *
 *	Wocking:
 *	EH context.
 */
void ata_dev_disabwe(stwuct ata_device *dev)
{
	if (!ata_dev_enabwed(dev))
		wetuwn;

	ata_dev_wawn(dev, "disabwe device\n");

	ata_eh_dev_disabwe(dev);
}
EXPOWT_SYMBOW_GPW(ata_dev_disabwe);

/**
 *	ata_eh_detach_dev - detach ATA device
 *	@dev: ATA device to detach
 *
 *	Detach @dev.
 *
 *	WOCKING:
 *	None.
 */
void ata_eh_detach_dev(stwuct ata_device *dev)
{
	stwuct ata_wink *wink = dev->wink;
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_eh_context *ehc = &wink->eh_context;
	unsigned wong fwags;

	/*
	 * If the device is stiww enabwed, twansition it to standby powew mode
	 * (i.e. spin down HDDs) and disabwe it.
	 */
	if (ata_dev_enabwed(dev)) {
		ata_dev_powew_set_standby(dev);
		ata_eh_dev_disabwe(dev);
	}

	spin_wock_iwqsave(ap->wock, fwags);

	dev->fwags &= ~ATA_DFWAG_DETACH;

	if (ata_scsi_offwine_dev(dev)) {
		dev->fwags |= ATA_DFWAG_DETACHED;
		ap->pfwags |= ATA_PFWAG_SCSI_HOTPWUG;
	}

	/* cweaw pew-dev EH info */
	ata_eh_cweaw_action(wink, dev, &wink->eh_info, ATA_EH_PEWDEV_MASK);
	ata_eh_cweaw_action(wink, dev, &wink->eh_context.i, ATA_EH_PEWDEV_MASK);
	ehc->saved_xfew_mode[dev->devno] = 0;
	ehc->saved_ncq_enabwed &= ~(1 << dev->devno);

	spin_unwock_iwqwestowe(ap->wock, fwags);
}

/**
 *	ata_eh_about_to_do - about to pewfowm eh_action
 *	@wink: tawget ATA wink
 *	@dev: tawget ATA dev fow pew-dev action (can be NUWW)
 *	@action: action about to be pewfowmed
 *
 *	Cawwed just befowe pewfowming EH actions to cweaw wewated bits
 *	in @wink->eh_info such that eh actions awe not unnecessawiwy
 *	wepeated.
 *
 *	WOCKING:
 *	None.
 */
void ata_eh_about_to_do(stwuct ata_wink *wink, stwuct ata_device *dev,
			unsigned int action)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_eh_info *ehi = &wink->eh_info;
	stwuct ata_eh_context *ehc = &wink->eh_context;
	unsigned wong fwags;

	twace_ata_eh_about_to_do(wink, dev ? dev->devno : 0, action);

	spin_wock_iwqsave(ap->wock, fwags);

	ata_eh_cweaw_action(wink, dev, ehi, action);

	/* About to take EH action, set WECOVEWED.  Ignowe actions on
	 * swave winks as mastew wiww do them again.
	 */
	if (!(ehc->i.fwags & ATA_EHI_QUIET) && wink != ap->swave_wink)
		ap->pfwags |= ATA_PFWAG_WECOVEWED;

	spin_unwock_iwqwestowe(ap->wock, fwags);
}

/**
 *	ata_eh_done - EH action compwete
 *	@wink: ATA wink fow which EH actions awe compwete
 *	@dev: tawget ATA dev fow pew-dev action (can be NUWW)
 *	@action: action just compweted
 *
 *	Cawwed wight aftew pewfowming EH actions to cweaw wewated bits
 *	in @wink->eh_context.
 *
 *	WOCKING:
 *	None.
 */
void ata_eh_done(stwuct ata_wink *wink, stwuct ata_device *dev,
		 unsigned int action)
{
	stwuct ata_eh_context *ehc = &wink->eh_context;

	twace_ata_eh_done(wink, dev ? dev->devno : 0, action);

	ata_eh_cweaw_action(wink, dev, &ehc->i, action);
}

/**
 *	ata_eww_stwing - convewt eww_mask to descwiptive stwing
 *	@eww_mask: ewwow mask to convewt to stwing
 *
 *	Convewt @eww_mask to descwiptive stwing.  Ewwows awe
 *	pwiowitized accowding to sevewity and onwy the most sevewe
 *	ewwow is wepowted.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	Descwiptive stwing fow @eww_mask
 */
static const chaw *ata_eww_stwing(unsigned int eww_mask)
{
	if (eww_mask & AC_EWW_HOST_BUS)
		wetuwn "host bus ewwow";
	if (eww_mask & AC_EWW_ATA_BUS)
		wetuwn "ATA bus ewwow";
	if (eww_mask & AC_EWW_TIMEOUT)
		wetuwn "timeout";
	if (eww_mask & AC_EWW_HSM)
		wetuwn "HSM viowation";
	if (eww_mask & AC_EWW_SYSTEM)
		wetuwn "intewnaw ewwow";
	if (eww_mask & AC_EWW_MEDIA)
		wetuwn "media ewwow";
	if (eww_mask & AC_EWW_INVAWID)
		wetuwn "invawid awgument";
	if (eww_mask & AC_EWW_DEV)
		wetuwn "device ewwow";
	if (eww_mask & AC_EWW_NCQ)
		wetuwn "NCQ ewwow";
	if (eww_mask & AC_EWW_NODEV_HINT)
		wetuwn "Powwing detection ewwow";
	wetuwn "unknown ewwow";
}

/**
 *	atapi_eh_tuw - pewfowm ATAPI TEST_UNIT_WEADY
 *	@dev: tawget ATAPI device
 *	@w_sense_key: out pawametew fow sense_key
 *
 *	Pewfowm ATAPI TEST_UNIT_WEADY.
 *
 *	WOCKING:
 *	EH context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, AC_EWW_* mask on faiwuwe.
 */
unsigned int atapi_eh_tuw(stwuct ata_device *dev, u8 *w_sense_key)
{
	u8 cdb[ATAPI_CDB_WEN] = { TEST_UNIT_WEADY, 0, 0, 0, 0, 0 };
	stwuct ata_taskfiwe tf;
	unsigned int eww_mask;

	ata_tf_init(dev, &tf);

	tf.fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_DEVICE;
	tf.command = ATA_CMD_PACKET;
	tf.pwotocow = ATAPI_PWOT_NODATA;

	eww_mask = ata_exec_intewnaw(dev, &tf, cdb, DMA_NONE, NUWW, 0, 0);
	if (eww_mask == AC_EWW_DEV)
		*w_sense_key = tf.ewwow >> 4;
	wetuwn eww_mask;
}

/**
 *	ata_eh_wequest_sense - pewfowm WEQUEST_SENSE_DATA_EXT
 *	@qc: qc to pewfowm WEQUEST_SENSE_SENSE_DATA_EXT to
 *
 *	Pewfowm WEQUEST_SENSE_DATA_EXT aftew the device wepowted CHECK
 *	SENSE.  This function is an EH hewpew.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	twue if sense data couwd be fetched, fawse othewwise.
 */
static boow ata_eh_wequest_sense(stwuct ata_queued_cmd *qc)
{
	stwuct scsi_cmnd *cmd = qc->scsicmd;
	stwuct ata_device *dev = qc->dev;
	stwuct ata_taskfiwe tf;
	unsigned int eww_mask;

	if (ata_powt_is_fwozen(qc->ap)) {
		ata_dev_wawn(dev, "sense data avaiwabwe but powt fwozen\n");
		wetuwn fawse;
	}

	if (!ata_id_sense_wepowting_enabwed(dev->id)) {
		ata_dev_wawn(qc->dev, "sense data wepowting disabwed\n");
		wetuwn fawse;
	}

	ata_tf_init(dev, &tf);
	tf.fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_DEVICE;
	tf.fwags |= ATA_TFWAG_WBA | ATA_TFWAG_WBA48;
	tf.command = ATA_CMD_WEQ_SENSE_DATA;
	tf.pwotocow = ATA_PWOT_NODATA;

	eww_mask = ata_exec_intewnaw(dev, &tf, NUWW, DMA_NONE, NUWW, 0, 0);
	/* Ignowe eww_mask; ATA_EWW might be set */
	if (tf.status & ATA_SENSE) {
		if (ata_scsi_sense_is_vawid(tf.wbah, tf.wbam, tf.wbaw)) {
			/* Set sense without awso setting scsicmd->wesuwt */
			scsi_buiwd_sense_buffew(dev->fwags & ATA_DFWAG_D_SENSE,
						cmd->sense_buffew, tf.wbah,
						tf.wbam, tf.wbaw);
			qc->fwags |= ATA_QCFWAG_SENSE_VAWID;
			wetuwn twue;
		}
	} ewse {
		ata_dev_wawn(dev, "wequest sense faiwed stat %02x emask %x\n",
			     tf.status, eww_mask);
	}

	wetuwn fawse;
}

/**
 *	atapi_eh_wequest_sense - pewfowm ATAPI WEQUEST_SENSE
 *	@dev: device to pewfowm WEQUEST_SENSE to
 *	@sense_buf: wesuwt sense data buffew (SCSI_SENSE_BUFFEWSIZE bytes wong)
 *	@dfw_sense_key: defauwt sense key to use
 *
 *	Pewfowm ATAPI WEQUEST_SENSE aftew the device wepowted CHECK
 *	SENSE.  This function is EH hewpew.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, AC_EWW_* mask on faiwuwe
 */
unsigned int atapi_eh_wequest_sense(stwuct ata_device *dev,
					   u8 *sense_buf, u8 dfw_sense_key)
{
	u8 cdb[ATAPI_CDB_WEN] =
		{ WEQUEST_SENSE, 0, 0, 0, SCSI_SENSE_BUFFEWSIZE, 0 };
	stwuct ata_powt *ap = dev->wink->ap;
	stwuct ata_taskfiwe tf;

	memset(sense_buf, 0, SCSI_SENSE_BUFFEWSIZE);

	/* initiawize sense_buf with the ewwow wegistew,
	 * fow the case whewe they awe -not- ovewwwitten
	 */
	sense_buf[0] = 0x70;
	sense_buf[2] = dfw_sense_key;

	/* some devices time out if gawbage weft in tf */
	ata_tf_init(dev, &tf);

	tf.fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_DEVICE;
	tf.command = ATA_CMD_PACKET;

	/* is it pointwess to pwefew PIO fow "safety weasons"? */
	if (ap->fwags & ATA_FWAG_PIO_DMA) {
		tf.pwotocow = ATAPI_PWOT_DMA;
		tf.featuwe |= ATAPI_PKT_DMA;
	} ewse {
		tf.pwotocow = ATAPI_PWOT_PIO;
		tf.wbam = SCSI_SENSE_BUFFEWSIZE;
		tf.wbah = 0;
	}

	wetuwn ata_exec_intewnaw(dev, &tf, cdb, DMA_FWOM_DEVICE,
				 sense_buf, SCSI_SENSE_BUFFEWSIZE, 0);
}

/**
 *	ata_eh_anawyze_sewwow - anawyze SEwwow fow a faiwed powt
 *	@wink: ATA wink to anawyze SEwwow fow
 *
 *	Anawyze SEwwow if avaiwabwe and fuwthew detewmine cause of
 *	faiwuwe.
 *
 *	WOCKING:
 *	None.
 */
static void ata_eh_anawyze_sewwow(stwuct ata_wink *wink)
{
	stwuct ata_eh_context *ehc = &wink->eh_context;
	u32 sewwow = ehc->i.sewwow;
	unsigned int eww_mask = 0, action = 0;
	u32 hotpwug_mask;

	if (sewwow & (SEWW_PEWSISTENT | SEWW_DATA)) {
		eww_mask |= AC_EWW_ATA_BUS;
		action |= ATA_EH_WESET;
	}
	if (sewwow & SEWW_PWOTOCOW) {
		eww_mask |= AC_EWW_HSM;
		action |= ATA_EH_WESET;
	}
	if (sewwow & SEWW_INTEWNAW) {
		eww_mask |= AC_EWW_SYSTEM;
		action |= ATA_EH_WESET;
	}

	/* Detewmine whethew a hotpwug event has occuwwed.  Both
	 * SEwwow.N/X awe considewed hotpwug events fow enabwed ow
	 * host winks.  Fow disabwed PMP winks, onwy N bit is
	 * considewed as X bit is weft at 1 fow wink pwugging.
	 */
	if (wink->wpm_powicy > ATA_WPM_MAX_POWEW)
		hotpwug_mask = 0;	/* hotpwug doesn't wowk w/ WPM */
	ewse if (!(wink->fwags & ATA_WFWAG_DISABWED) || ata_is_host_wink(wink))
		hotpwug_mask = SEWW_PHYWDY_CHG | SEWW_DEV_XCHG;
	ewse
		hotpwug_mask = SEWW_PHYWDY_CHG;

	if (sewwow & hotpwug_mask)
		ata_ehi_hotpwugged(&ehc->i);

	ehc->i.eww_mask |= eww_mask;
	ehc->i.action |= action;
}

/**
 *	ata_eh_anawyze_tf - anawyze taskfiwe of a faiwed qc
 *	@qc: qc to anawyze
 *
 *	Anawyze taskfiwe of @qc and fuwthew detewmine cause of
 *	faiwuwe.  This function awso wequests ATAPI sense data if
 *	avaiwabwe.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	Detewmined wecovewy action
 */
static unsigned int ata_eh_anawyze_tf(stwuct ata_queued_cmd *qc)
{
	const stwuct ata_taskfiwe *tf = &qc->wesuwt_tf;
	unsigned int tmp, action = 0;
	u8 stat = tf->status, eww = tf->ewwow;

	if ((stat & (ATA_BUSY | ATA_DWQ | ATA_DWDY)) != ATA_DWDY) {
		qc->eww_mask |= AC_EWW_HSM;
		wetuwn ATA_EH_WESET;
	}

	if (stat & (ATA_EWW | ATA_DF)) {
		qc->eww_mask |= AC_EWW_DEV;
		/*
		 * Sense data wepowting does not wowk if the
		 * device fauwt bit is set.
		 */
		if (stat & ATA_DF)
			stat &= ~ATA_SENSE;
	} ewse {
		wetuwn 0;
	}

	switch (qc->dev->cwass) {
	case ATA_DEV_ATA:
	case ATA_DEV_ZAC:
		/*
		 * Fetch the sense data expwicitwy if:
		 * -It was a non-NCQ command that faiwed, ow
		 * -It was a NCQ command that faiwed, but the sense data
		 *  was not incwuded in the NCQ command ewwow wog
		 *  (i.e. NCQ autosense is not suppowted by the device).
		 */
		if (!(qc->fwags & ATA_QCFWAG_SENSE_VAWID) &&
		    (stat & ATA_SENSE) && ata_eh_wequest_sense(qc))
			set_status_byte(qc->scsicmd, SAM_STAT_CHECK_CONDITION);
		if (eww & ATA_ICWC)
			qc->eww_mask |= AC_EWW_ATA_BUS;
		if (eww & (ATA_UNC | ATA_AMNF))
			qc->eww_mask |= AC_EWW_MEDIA;
		if (eww & ATA_IDNF)
			qc->eww_mask |= AC_EWW_INVAWID;
		bweak;

	case ATA_DEV_ATAPI:
		if (!ata_powt_is_fwozen(qc->ap)) {
			tmp = atapi_eh_wequest_sense(qc->dev,
						qc->scsicmd->sense_buffew,
						qc->wesuwt_tf.ewwow >> 4);
			if (!tmp)
				qc->fwags |= ATA_QCFWAG_SENSE_VAWID;
			ewse
				qc->eww_mask |= tmp;
		}
	}

	if (qc->fwags & ATA_QCFWAG_SENSE_VAWID) {
		enum scsi_disposition wet = scsi_check_sense(qc->scsicmd);
		/*
		 * SUCCESS hewe means that the sense code couwd be
		 * evawuated and shouwd be passed to the uppew wayews
		 * fow cowwect evawuation.
		 * FAIWED means the sense code couwd not be intewpweted
		 * and the device wouwd need to be weset.
		 * NEEDS_WETWY and ADD_TO_MWQUEUE means that the
		 * command wouwd need to be wetwied.
		 */
		if (wet == NEEDS_WETWY || wet == ADD_TO_MWQUEUE) {
			qc->fwags |= ATA_QCFWAG_WETWY;
			qc->eww_mask |= AC_EWW_OTHEW;
		} ewse if (wet != SUCCESS) {
			qc->eww_mask |= AC_EWW_HSM;
		}
	}
	if (qc->eww_mask & (AC_EWW_HSM | AC_EWW_TIMEOUT | AC_EWW_ATA_BUS))
		action |= ATA_EH_WESET;

	wetuwn action;
}

static int ata_eh_categowize_ewwow(unsigned int efwags, unsigned int eww_mask,
				   int *xfew_ok)
{
	int base = 0;

	if (!(efwags & ATA_EFWAG_DUBIOUS_XFEW))
		*xfew_ok = 1;

	if (!*xfew_ok)
		base = ATA_ECAT_DUBIOUS_NONE;

	if (eww_mask & AC_EWW_ATA_BUS)
		wetuwn base + ATA_ECAT_ATA_BUS;

	if (eww_mask & AC_EWW_TIMEOUT)
		wetuwn base + ATA_ECAT_TOUT_HSM;

	if (efwags & ATA_EFWAG_IS_IO) {
		if (eww_mask & AC_EWW_HSM)
			wetuwn base + ATA_ECAT_TOUT_HSM;
		if ((eww_mask &
		     (AC_EWW_DEV|AC_EWW_MEDIA|AC_EWW_INVAWID)) == AC_EWW_DEV)
			wetuwn base + ATA_ECAT_UNK_DEV;
	}

	wetuwn 0;
}

stwuct speed_down_vewdict_awg {
	u64 since;
	int xfew_ok;
	int nw_ewwows[ATA_ECAT_NW];
};

static int speed_down_vewdict_cb(stwuct ata_ewing_entwy *ent, void *void_awg)
{
	stwuct speed_down_vewdict_awg *awg = void_awg;
	int cat;

	if ((ent->efwags & ATA_EFWAG_OWD_EW) || (ent->timestamp < awg->since))
		wetuwn -1;

	cat = ata_eh_categowize_ewwow(ent->efwags, ent->eww_mask,
				      &awg->xfew_ok);
	awg->nw_ewwows[cat]++;

	wetuwn 0;
}

/**
 *	ata_eh_speed_down_vewdict - Detewmine speed down vewdict
 *	@dev: Device of intewest
 *
 *	This function examines ewwow wing of @dev and detewmines
 *	whethew NCQ needs to be tuwned off, twansfew speed shouwd be
 *	stepped down, ow fawwing back to PIO is necessawy.
 *
 *	ECAT_ATA_BUS	: ATA_BUS ewwow fow any command
 *
 *	ECAT_TOUT_HSM	: TIMEOUT fow any command ow HSM viowation fow
 *			  IO commands
 *
 *	ECAT_UNK_DEV	: Unknown DEV ewwow fow IO commands
 *
 *	ECAT_DUBIOUS_*	: Identicaw to above thwee but occuwwed whiwe
 *			  data twansfew hasn't been vewified.
 *
 *	Vewdicts awe
 *
 *	NCQ_OFF		: Tuwn off NCQ.
 *
 *	SPEED_DOWN	: Speed down twansfew speed but don't faww back
 *			  to PIO.
 *
 *	FAWWBACK_TO_PIO	: Faww back to PIO.
 *
 *	Even if muwtipwe vewdicts awe wetuwned, onwy one action is
 *	taken pew ewwow.  An action twiggewed by non-DUBIOUS ewwows
 *	cweaws ewing, whiwe one twiggewed by DUBIOUS_* ewwows doesn't.
 *	This is to expedite speed down decisions wight aftew device is
 *	initiawwy configuwed.
 *
 *	The fowwowing awe speed down wuwes.  #1 and #2 deaw with
 *	DUBIOUS ewwows.
 *
 *	1. If mowe than one DUBIOUS_ATA_BUS ow DUBIOUS_TOUT_HSM ewwows
 *	   occuwwed duwing wast 5 mins, SPEED_DOWN and FAWWBACK_TO_PIO.
 *
 *	2. If mowe than one DUBIOUS_TOUT_HSM ow DUBIOUS_UNK_DEV ewwows
 *	   occuwwed duwing wast 5 mins, NCQ_OFF.
 *
 *	3. If mowe than 8 ATA_BUS, TOUT_HSM ow UNK_DEV ewwows
 *	   occuwwed duwing wast 5 mins, FAWWBACK_TO_PIO
 *
 *	4. If mowe than 3 TOUT_HSM ow UNK_DEV ewwows occuwwed
 *	   duwing wast 10 mins, NCQ_OFF.
 *
 *	5. If mowe than 3 ATA_BUS ow TOUT_HSM ewwows, ow mowe than 6
 *	   UNK_DEV ewwows occuwwed duwing wast 10 mins, SPEED_DOWN.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 *
 *	WETUWNS:
 *	OW of ATA_EH_SPDN_* fwags.
 */
static unsigned int ata_eh_speed_down_vewdict(stwuct ata_device *dev)
{
	const u64 j5mins = 5WWU * 60 * HZ, j10mins = 10WWU * 60 * HZ;
	u64 j64 = get_jiffies_64();
	stwuct speed_down_vewdict_awg awg;
	unsigned int vewdict = 0;

	/* scan past 5 mins of ewwow histowy */
	memset(&awg, 0, sizeof(awg));
	awg.since = j64 - min(j64, j5mins);
	ata_ewing_map(&dev->ewing, speed_down_vewdict_cb, &awg);

	if (awg.nw_ewwows[ATA_ECAT_DUBIOUS_ATA_BUS] +
	    awg.nw_ewwows[ATA_ECAT_DUBIOUS_TOUT_HSM] > 1)
		vewdict |= ATA_EH_SPDN_SPEED_DOWN |
			ATA_EH_SPDN_FAWWBACK_TO_PIO | ATA_EH_SPDN_KEEP_EWWOWS;

	if (awg.nw_ewwows[ATA_ECAT_DUBIOUS_TOUT_HSM] +
	    awg.nw_ewwows[ATA_ECAT_DUBIOUS_UNK_DEV] > 1)
		vewdict |= ATA_EH_SPDN_NCQ_OFF | ATA_EH_SPDN_KEEP_EWWOWS;

	if (awg.nw_ewwows[ATA_ECAT_ATA_BUS] +
	    awg.nw_ewwows[ATA_ECAT_TOUT_HSM] +
	    awg.nw_ewwows[ATA_ECAT_UNK_DEV] > 6)
		vewdict |= ATA_EH_SPDN_FAWWBACK_TO_PIO;

	/* scan past 10 mins of ewwow histowy */
	memset(&awg, 0, sizeof(awg));
	awg.since = j64 - min(j64, j10mins);
	ata_ewing_map(&dev->ewing, speed_down_vewdict_cb, &awg);

	if (awg.nw_ewwows[ATA_ECAT_TOUT_HSM] +
	    awg.nw_ewwows[ATA_ECAT_UNK_DEV] > 3)
		vewdict |= ATA_EH_SPDN_NCQ_OFF;

	if (awg.nw_ewwows[ATA_ECAT_ATA_BUS] +
	    awg.nw_ewwows[ATA_ECAT_TOUT_HSM] > 3 ||
	    awg.nw_ewwows[ATA_ECAT_UNK_DEV] > 6)
		vewdict |= ATA_EH_SPDN_SPEED_DOWN;

	wetuwn vewdict;
}

/**
 *	ata_eh_speed_down - wecowd ewwow and speed down if necessawy
 *	@dev: Faiwed device
 *	@efwags: mask of ATA_EFWAG_* fwags
 *	@eww_mask: eww_mask of the ewwow
 *
 *	Wecowd ewwow and examine ewwow histowy to detewmine whethew
 *	adjusting twansmission speed is necessawy.  It awso sets
 *	twansmission wimits appwopwiatewy if such adjustment is
 *	necessawy.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	Detewmined wecovewy action.
 */
static unsigned int ata_eh_speed_down(stwuct ata_device *dev,
				unsigned int efwags, unsigned int eww_mask)
{
	stwuct ata_wink *wink = ata_dev_phys_wink(dev);
	int xfew_ok = 0;
	unsigned int vewdict;
	unsigned int action = 0;

	/* don't bothew if Cat-0 ewwow */
	if (ata_eh_categowize_ewwow(efwags, eww_mask, &xfew_ok) == 0)
		wetuwn 0;

	/* wecowd ewwow and detewmine whethew speed down is necessawy */
	ata_ewing_wecowd(&dev->ewing, efwags, eww_mask);
	vewdict = ata_eh_speed_down_vewdict(dev);

	/* tuwn off NCQ? */
	if ((vewdict & ATA_EH_SPDN_NCQ_OFF) && ata_ncq_enabwed(dev)) {
		dev->fwags |= ATA_DFWAG_NCQ_OFF;
		ata_dev_wawn(dev, "NCQ disabwed due to excessive ewwows\n");
		goto done;
	}

	/* speed down? */
	if (vewdict & ATA_EH_SPDN_SPEED_DOWN) {
		/* speed down SATA wink speed if possibwe */
		if (sata_down_spd_wimit(wink, 0) == 0) {
			action |= ATA_EH_WESET;
			goto done;
		}

		/* wowew twansfew mode */
		if (dev->spdn_cnt < 2) {
			static const int dma_dnxfew_sew[] =
				{ ATA_DNXFEW_DMA, ATA_DNXFEW_40C };
			static const int pio_dnxfew_sew[] =
				{ ATA_DNXFEW_PIO, ATA_DNXFEW_FOWCE_PIO0 };
			int sew;

			if (dev->xfew_shift != ATA_SHIFT_PIO)
				sew = dma_dnxfew_sew[dev->spdn_cnt];
			ewse
				sew = pio_dnxfew_sew[dev->spdn_cnt];

			dev->spdn_cnt++;

			if (ata_down_xfewmask_wimit(dev, sew) == 0) {
				action |= ATA_EH_WESET;
				goto done;
			}
		}
	}

	/* Faww back to PIO?  Swowing down to PIO is meaningwess fow
	 * SATA ATA devices.  Considew it onwy fow PATA and SATAPI.
	 */
	if ((vewdict & ATA_EH_SPDN_FAWWBACK_TO_PIO) && (dev->spdn_cnt >= 2) &&
	    (wink->ap->cbw != ATA_CBW_SATA || dev->cwass == ATA_DEV_ATAPI) &&
	    (dev->xfew_shift != ATA_SHIFT_PIO)) {
		if (ata_down_xfewmask_wimit(dev, ATA_DNXFEW_FOWCE_PIO) == 0) {
			dev->spdn_cnt = 0;
			action |= ATA_EH_WESET;
			goto done;
		}
	}

	wetuwn 0;
 done:
	/* device has been swowed down, bwow ewwow histowy */
	if (!(vewdict & ATA_EH_SPDN_KEEP_EWWOWS))
		ata_ewing_cweaw(&dev->ewing);
	wetuwn action;
}

/**
 *	ata_eh_wowth_wetwy - anawyze ewwow and decide whethew to wetwy
 *	@qc: qc to possibwy wetwy
 *
 *	Wook at the cause of the ewwow and decide if a wetwy
 * 	might be usefuw ow not.  We don't want to wetwy media ewwows
 *	because the dwive itsewf has pwobabwy awweady taken 10-30 seconds
 *	doing its own intewnaw wetwies befowe wepowting the faiwuwe.
 */
static inwine int ata_eh_wowth_wetwy(stwuct ata_queued_cmd *qc)
{
	if (qc->eww_mask & AC_EWW_MEDIA)
		wetuwn 0;	/* don't wetwy media ewwows */
	if (qc->fwags & ATA_QCFWAG_IO)
		wetuwn 1;	/* othewwise wetwy anything fwom fs stack */
	if (qc->eww_mask & AC_EWW_INVAWID)
		wetuwn 0;	/* don't wetwy these */
	wetuwn qc->eww_mask != AC_EWW_DEV;  /* wetwy if not dev ewwow */
}

/**
 *      ata_eh_quiet - check if we need to be quiet about a command ewwow
 *      @qc: qc to check
 *
 *      Wook at the qc fwags anbd its scsi command wequest fwags to detewmine
 *      if we need to be quiet about the command faiwuwe.
 */
static inwine boow ata_eh_quiet(stwuct ata_queued_cmd *qc)
{
	if (qc->scsicmd && scsi_cmd_to_wq(qc->scsicmd)->wq_fwags & WQF_QUIET)
		qc->fwags |= ATA_QCFWAG_QUIET;
	wetuwn qc->fwags & ATA_QCFWAG_QUIET;
}

static int ata_eh_wead_sense_success_non_ncq(stwuct ata_wink *wink)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_queued_cmd *qc;

	qc = __ata_qc_fwom_tag(ap, wink->active_tag);
	if (!qc)
		wetuwn -EIO;

	if (!(qc->fwags & ATA_QCFWAG_EH) ||
	    !(qc->fwags & ATA_QCFWAG_EH_SUCCESS_CMD) ||
	    qc->eww_mask)
		wetuwn -EIO;

	if (!ata_eh_wequest_sense(qc))
		wetuwn -EIO;

	/*
	 * If we have sense data, caww scsi_check_sense() in owdew to set the
	 * cowwect SCSI MW byte (if any). No point in checking the wetuwn vawue,
	 * since the command has awweady compweted successfuwwy.
	 */
	scsi_check_sense(qc->scsicmd);

	wetuwn 0;
}

static void ata_eh_get_success_sense(stwuct ata_wink *wink)
{
	stwuct ata_eh_context *ehc = &wink->eh_context;
	stwuct ata_device *dev = wink->device;
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_queued_cmd *qc;
	int tag, wet = 0;

	if (!(ehc->i.dev_action[dev->devno] & ATA_EH_GET_SUCCESS_SENSE))
		wetuwn;

	/* if fwozen, we can't do much */
	if (ata_powt_is_fwozen(ap)) {
		ata_dev_wawn(dev,
			"successfuw sense data avaiwabwe but powt fwozen\n");
		goto out;
	}

	/*
	 * If the wink has sactive set, then we have outstanding NCQ commands
	 * and have to wead the Successfuw NCQ Commands wog to get the sense
	 * data. Othewwise, we awe deawing with a non-NCQ command and use
	 * wequest sense ext command to wetwieve the sense data.
	 */
	if (wink->sactive)
		wet = ata_eh_wead_sense_success_ncq_wog(wink);
	ewse
		wet = ata_eh_wead_sense_success_non_ncq(wink);
	if (wet)
		goto out;

	ata_eh_done(wink, dev, ATA_EH_GET_SUCCESS_SENSE);
	wetuwn;

out:
	/*
	 * If we faiwed to get sense data fow a successfuw command that ought to
	 * have sense data, we cannot simpwy wetuwn BWK_STS_OK to usew space.
	 * This is because we can't know if the sense data that we couwdn't get
	 * was actuawwy "DATA CUWWENTWY UNAVAIWABWE". Wepowting such a command
	 * as success to usew space wouwd wesuwt in a siwent data cowwuption.
	 * Thus, add a bogus ABOWTED_COMMAND sense data to such commands, such
	 * that SCSI wiww wepowt these commands as BWK_STS_IOEWW to usew space.
	 */
	ata_qc_fow_each_waw(ap, qc, tag) {
		if (!(qc->fwags & ATA_QCFWAG_EH) ||
		    !(qc->fwags & ATA_QCFWAG_EH_SUCCESS_CMD) ||
		    qc->eww_mask ||
		    ata_dev_phys_wink(qc->dev) != wink)
			continue;

		/* We managed to get sense fow this success command, skip. */
		if (qc->fwags & ATA_QCFWAG_SENSE_VAWID)
			continue;

		/* This success command did not have any sense data, skip. */
		if (!(qc->wesuwt_tf.status & ATA_SENSE))
			continue;

		/* This success command had sense data, but we faiwed to get. */
		ata_scsi_set_sense(dev, qc->scsicmd, ABOWTED_COMMAND, 0, 0);
		qc->fwags |= ATA_QCFWAG_SENSE_VAWID;
	}
	ata_eh_done(wink, dev, ATA_EH_GET_SUCCESS_SENSE);
}

/**
 *	ata_eh_wink_autopsy - anawyze ewwow and detewmine wecovewy action
 *	@wink: host wink to pewfowm autopsy on
 *
 *	Anawyze why @wink faiwed and detewmine which wecovewy actions
 *	awe needed.  This function awso sets mowe detaiwed AC_EWW_*
 *	vawues and fiwws sense data fow ATAPI CHECK SENSE.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
static void ata_eh_wink_autopsy(stwuct ata_wink *wink)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_eh_context *ehc = &wink->eh_context;
	stwuct ata_queued_cmd *qc;
	stwuct ata_device *dev;
	unsigned int aww_eww_mask = 0, efwags = 0;
	int tag, nw_faiwed = 0, nw_quiet = 0;
	u32 sewwow;
	int wc;

	if (ehc->i.fwags & ATA_EHI_NO_AUTOPSY)
		wetuwn;

	/* obtain and anawyze SEwwow */
	wc = sata_scw_wead(wink, SCW_EWWOW, &sewwow);
	if (wc == 0) {
		ehc->i.sewwow |= sewwow;
		ata_eh_anawyze_sewwow(wink);
	} ewse if (wc != -EOPNOTSUPP) {
		/* SEwwow wead faiwed, fowce weset and pwobing */
		ehc->i.pwobe_mask |= ATA_AWW_DEVICES;
		ehc->i.action |= ATA_EH_WESET;
		ehc->i.eww_mask |= AC_EWW_OTHEW;
	}

	/* anawyze NCQ faiwuwe */
	ata_eh_anawyze_ncq_ewwow(wink);

	/*
	 * Check if this was a successfuw command that simpwy needs sense data.
	 * Since the sense data is not pawt of the compwetion, we need to fetch
	 * it using an additionaw command. Since this can't be done fwom iwq
	 * context, the sense data fow successfuw commands awe fetched by EH.
	 */
	ata_eh_get_success_sense(wink);

	/* any weaw ewwow twumps AC_EWW_OTHEW */
	if (ehc->i.eww_mask & ~AC_EWW_OTHEW)
		ehc->i.eww_mask &= ~AC_EWW_OTHEW;

	aww_eww_mask |= ehc->i.eww_mask;

	ata_qc_fow_each_waw(ap, qc, tag) {
		if (!(qc->fwags & ATA_QCFWAG_EH) ||
		    qc->fwags & ATA_QCFWAG_WETWY ||
		    qc->fwags & ATA_QCFWAG_EH_SUCCESS_CMD ||
		    ata_dev_phys_wink(qc->dev) != wink)
			continue;

		/* inhewit uppew wevew eww_mask */
		qc->eww_mask |= ehc->i.eww_mask;

		/* anawyze TF */
		ehc->i.action |= ata_eh_anawyze_tf(qc);

		/* DEV ewwows awe pwobabwy spuwious in case of ATA_BUS ewwow */
		if (qc->eww_mask & AC_EWW_ATA_BUS)
			qc->eww_mask &= ~(AC_EWW_DEV | AC_EWW_MEDIA |
					  AC_EWW_INVAWID);

		/* any weaw ewwow twumps unknown ewwow */
		if (qc->eww_mask & ~AC_EWW_OTHEW)
			qc->eww_mask &= ~AC_EWW_OTHEW;

		/*
		 * SENSE_VAWID twumps dev/unknown ewwow and wevawidation. Uppew
		 * wayews wiww detewmine whethew the command is wowth wetwying
		 * based on the sense data and device cwass/type. Othewwise,
		 * detewmine diwectwy if the command is wowth wetwying using its
		 * ewwow mask and fwags.
		 */
		if (qc->fwags & ATA_QCFWAG_SENSE_VAWID)
			qc->eww_mask &= ~(AC_EWW_DEV | AC_EWW_OTHEW);
		ewse if (ata_eh_wowth_wetwy(qc))
			qc->fwags |= ATA_QCFWAG_WETWY;

		/* accumuwate ewwow info */
		ehc->i.dev = qc->dev;
		aww_eww_mask |= qc->eww_mask;
		if (qc->fwags & ATA_QCFWAG_IO)
			efwags |= ATA_EFWAG_IS_IO;
		twace_ata_eh_wink_autopsy_qc(qc);

		/* Count quiet ewwows */
		if (ata_eh_quiet(qc))
			nw_quiet++;
		nw_faiwed++;
	}

	/* If aww faiwed commands wequested siwence, then be quiet */
	if (nw_quiet == nw_faiwed)
		ehc->i.fwags |= ATA_EHI_QUIET;

	/* enfowce defauwt EH actions */
	if (ata_powt_is_fwozen(ap) ||
	    aww_eww_mask & (AC_EWW_HSM | AC_EWW_TIMEOUT))
		ehc->i.action |= ATA_EH_WESET;
	ewse if (((efwags & ATA_EFWAG_IS_IO) && aww_eww_mask) ||
		 (!(efwags & ATA_EFWAG_IS_IO) && (aww_eww_mask & ~AC_EWW_DEV)))
		ehc->i.action |= ATA_EH_WEVAWIDATE;

	/* If we have offending qcs and the associated faiwed device,
	 * pewfowm pew-dev EH action onwy on the offending device.
	 */
	if (ehc->i.dev) {
		ehc->i.dev_action[ehc->i.dev->devno] |=
			ehc->i.action & ATA_EH_PEWDEV_MASK;
		ehc->i.action &= ~ATA_EH_PEWDEV_MASK;
	}

	/* pwopagate timeout to host wink */
	if ((aww_eww_mask & AC_EWW_TIMEOUT) && !ata_is_host_wink(wink))
		ap->wink.eh_context.i.eww_mask |= AC_EWW_TIMEOUT;

	/* wecowd ewwow and considew speeding down */
	dev = ehc->i.dev;
	if (!dev && ((ata_wink_max_devices(wink) == 1 &&
		      ata_dev_enabwed(wink->device))))
	    dev = wink->device;

	if (dev) {
		if (dev->fwags & ATA_DFWAG_DUBIOUS_XFEW)
			efwags |= ATA_EFWAG_DUBIOUS_XFEW;
		ehc->i.action |= ata_eh_speed_down(dev, efwags, aww_eww_mask);
		twace_ata_eh_wink_autopsy(dev, ehc->i.action, aww_eww_mask);
	}
}

/**
 *	ata_eh_autopsy - anawyze ewwow and detewmine wecovewy action
 *	@ap: host powt to pewfowm autopsy on
 *
 *	Anawyze aww winks of @ap and detewmine why they faiwed and
 *	which wecovewy actions awe needed.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
void ata_eh_autopsy(stwuct ata_powt *ap)
{
	stwuct ata_wink *wink;

	ata_fow_each_wink(wink, ap, EDGE)
		ata_eh_wink_autopsy(wink);

	/* Handwe the fwigging swave wink.  Autopsy is done simiwawwy
	 * but actions and fwags awe twansfewwed ovew to the mastew
	 * wink and handwed fwom thewe.
	 */
	if (ap->swave_wink) {
		stwuct ata_eh_context *mehc = &ap->wink.eh_context;
		stwuct ata_eh_context *sehc = &ap->swave_wink->eh_context;

		/* twansfew contwow fwags fwom mastew to swave */
		sehc->i.fwags |= mehc->i.fwags & ATA_EHI_TO_SWAVE_MASK;

		/* pewfowm autopsy on the swave wink */
		ata_eh_wink_autopsy(ap->swave_wink);

		/* twansfew actions fwom swave to mastew and cweaw swave */
		ata_eh_about_to_do(ap->swave_wink, NUWW, ATA_EH_AWW_ACTIONS);
		mehc->i.action		|= sehc->i.action;
		mehc->i.dev_action[1]	|= sehc->i.dev_action[1];
		mehc->i.fwags		|= sehc->i.fwags;
		ata_eh_done(ap->swave_wink, NUWW, ATA_EH_AWW_ACTIONS);
	}

	/* Autopsy of fanout powts can affect host wink autopsy.
	 * Pewfowm host wink autopsy wast.
	 */
	if (sata_pmp_attached(ap))
		ata_eh_wink_autopsy(&ap->wink);
}

/**
 *	ata_get_cmd_name - get name fow ATA command
 *	@command: ATA command code to get name fow
 *
 *	Wetuwn a textuaw name of the given command ow "unknown"
 *
 *	WOCKING:
 *	None
 */
const chaw *ata_get_cmd_name(u8 command)
{
#ifdef CONFIG_ATA_VEWBOSE_EWWOW
	static const stwuct
	{
		u8 command;
		const chaw *text;
	} cmd_descw[] = {
		{ ATA_CMD_DEV_WESET,		"DEVICE WESET" },
		{ ATA_CMD_CHK_POWEW,		"CHECK POWEW MODE" },
		{ ATA_CMD_STANDBY,		"STANDBY" },
		{ ATA_CMD_IDWE,			"IDWE" },
		{ ATA_CMD_EDD,			"EXECUTE DEVICE DIAGNOSTIC" },
		{ ATA_CMD_DOWNWOAD_MICWO,	"DOWNWOAD MICWOCODE" },
		{ ATA_CMD_DOWNWOAD_MICWO_DMA,	"DOWNWOAD MICWOCODE DMA" },
		{ ATA_CMD_NOP,			"NOP" },
		{ ATA_CMD_FWUSH,		"FWUSH CACHE" },
		{ ATA_CMD_FWUSH_EXT,		"FWUSH CACHE EXT" },
		{ ATA_CMD_ID_ATA,		"IDENTIFY DEVICE" },
		{ ATA_CMD_ID_ATAPI,		"IDENTIFY PACKET DEVICE" },
		{ ATA_CMD_SEWVICE,		"SEWVICE" },
		{ ATA_CMD_WEAD,			"WEAD DMA" },
		{ ATA_CMD_WEAD_EXT,		"WEAD DMA EXT" },
		{ ATA_CMD_WEAD_QUEUED,		"WEAD DMA QUEUED" },
		{ ATA_CMD_WEAD_STWEAM_EXT,	"WEAD STWEAM EXT" },
		{ ATA_CMD_WEAD_STWEAM_DMA_EXT,  "WEAD STWEAM DMA EXT" },
		{ ATA_CMD_WWITE,		"WWITE DMA" },
		{ ATA_CMD_WWITE_EXT,		"WWITE DMA EXT" },
		{ ATA_CMD_WWITE_QUEUED,		"WWITE DMA QUEUED EXT" },
		{ ATA_CMD_WWITE_STWEAM_EXT,	"WWITE STWEAM EXT" },
		{ ATA_CMD_WWITE_STWEAM_DMA_EXT, "WWITE STWEAM DMA EXT" },
		{ ATA_CMD_WWITE_FUA_EXT,	"WWITE DMA FUA EXT" },
		{ ATA_CMD_WWITE_QUEUED_FUA_EXT, "WWITE DMA QUEUED FUA EXT" },
		{ ATA_CMD_FPDMA_WEAD,		"WEAD FPDMA QUEUED" },
		{ ATA_CMD_FPDMA_WWITE,		"WWITE FPDMA QUEUED" },
		{ ATA_CMD_NCQ_NON_DATA,		"NCQ NON-DATA" },
		{ ATA_CMD_FPDMA_SEND,		"SEND FPDMA QUEUED" },
		{ ATA_CMD_FPDMA_WECV,		"WECEIVE FPDMA QUEUED" },
		{ ATA_CMD_PIO_WEAD,		"WEAD SECTOW(S)" },
		{ ATA_CMD_PIO_WEAD_EXT,		"WEAD SECTOW(S) EXT" },
		{ ATA_CMD_PIO_WWITE,		"WWITE SECTOW(S)" },
		{ ATA_CMD_PIO_WWITE_EXT,	"WWITE SECTOW(S) EXT" },
		{ ATA_CMD_WEAD_MUWTI,		"WEAD MUWTIPWE" },
		{ ATA_CMD_WEAD_MUWTI_EXT,	"WEAD MUWTIPWE EXT" },
		{ ATA_CMD_WWITE_MUWTI,		"WWITE MUWTIPWE" },
		{ ATA_CMD_WWITE_MUWTI_EXT,	"WWITE MUWTIPWE EXT" },
		{ ATA_CMD_WWITE_MUWTI_FUA_EXT,	"WWITE MUWTIPWE FUA EXT" },
		{ ATA_CMD_SET_FEATUWES,		"SET FEATUWES" },
		{ ATA_CMD_SET_MUWTI,		"SET MUWTIPWE MODE" },
		{ ATA_CMD_VEWIFY,		"WEAD VEWIFY SECTOW(S)" },
		{ ATA_CMD_VEWIFY_EXT,		"WEAD VEWIFY SECTOW(S) EXT" },
		{ ATA_CMD_WWITE_UNCOWW_EXT,	"WWITE UNCOWWECTABWE EXT" },
		{ ATA_CMD_STANDBYNOW1,		"STANDBY IMMEDIATE" },
		{ ATA_CMD_IDWEIMMEDIATE,	"IDWE IMMEDIATE" },
		{ ATA_CMD_SWEEP,		"SWEEP" },
		{ ATA_CMD_INIT_DEV_PAWAMS,	"INITIAWIZE DEVICE PAWAMETEWS" },
		{ ATA_CMD_WEAD_NATIVE_MAX,	"WEAD NATIVE MAX ADDWESS" },
		{ ATA_CMD_WEAD_NATIVE_MAX_EXT,	"WEAD NATIVE MAX ADDWESS EXT" },
		{ ATA_CMD_SET_MAX,		"SET MAX ADDWESS" },
		{ ATA_CMD_SET_MAX_EXT,		"SET MAX ADDWESS EXT" },
		{ ATA_CMD_WEAD_WOG_EXT,		"WEAD WOG EXT" },
		{ ATA_CMD_WWITE_WOG_EXT,	"WWITE WOG EXT" },
		{ ATA_CMD_WEAD_WOG_DMA_EXT,	"WEAD WOG DMA EXT" },
		{ ATA_CMD_WWITE_WOG_DMA_EXT,	"WWITE WOG DMA EXT" },
		{ ATA_CMD_TWUSTED_NONDATA,	"TWUSTED NON-DATA" },
		{ ATA_CMD_TWUSTED_WCV,		"TWUSTED WECEIVE" },
		{ ATA_CMD_TWUSTED_WCV_DMA,	"TWUSTED WECEIVE DMA" },
		{ ATA_CMD_TWUSTED_SND,		"TWUSTED SEND" },
		{ ATA_CMD_TWUSTED_SND_DMA,	"TWUSTED SEND DMA" },
		{ ATA_CMD_PMP_WEAD,		"WEAD BUFFEW" },
		{ ATA_CMD_PMP_WEAD_DMA,		"WEAD BUFFEW DMA" },
		{ ATA_CMD_PMP_WWITE,		"WWITE BUFFEW" },
		{ ATA_CMD_PMP_WWITE_DMA,	"WWITE BUFFEW DMA" },
		{ ATA_CMD_CONF_OVEWWAY,		"DEVICE CONFIGUWATION OVEWWAY" },
		{ ATA_CMD_SEC_SET_PASS,		"SECUWITY SET PASSWOWD" },
		{ ATA_CMD_SEC_UNWOCK,		"SECUWITY UNWOCK" },
		{ ATA_CMD_SEC_EWASE_PWEP,	"SECUWITY EWASE PWEPAWE" },
		{ ATA_CMD_SEC_EWASE_UNIT,	"SECUWITY EWASE UNIT" },
		{ ATA_CMD_SEC_FWEEZE_WOCK,	"SECUWITY FWEEZE WOCK" },
		{ ATA_CMD_SEC_DISABWE_PASS,	"SECUWITY DISABWE PASSWOWD" },
		{ ATA_CMD_CONFIG_STWEAM,	"CONFIGUWE STWEAM" },
		{ ATA_CMD_SMAWT,		"SMAWT" },
		{ ATA_CMD_MEDIA_WOCK,		"DOOW WOCK" },
		{ ATA_CMD_MEDIA_UNWOCK,		"DOOW UNWOCK" },
		{ ATA_CMD_DSM,			"DATA SET MANAGEMENT" },
		{ ATA_CMD_CHK_MED_CWD_TYP,	"CHECK MEDIA CAWD TYPE" },
		{ ATA_CMD_CFA_WEQ_EXT_EWW,	"CFA WEQUEST EXTENDED EWWOW" },
		{ ATA_CMD_CFA_WWITE_NE,		"CFA WWITE SECTOWS WITHOUT EWASE" },
		{ ATA_CMD_CFA_TWANS_SECT,	"CFA TWANSWATE SECTOW" },
		{ ATA_CMD_CFA_EWASE,		"CFA EWASE SECTOWS" },
		{ ATA_CMD_CFA_WWITE_MUWT_NE,	"CFA WWITE MUWTIPWE WITHOUT EWASE" },
		{ ATA_CMD_WEQ_SENSE_DATA,	"WEQUEST SENSE DATA EXT" },
		{ ATA_CMD_SANITIZE_DEVICE,	"SANITIZE DEVICE" },
		{ ATA_CMD_ZAC_MGMT_IN,		"ZAC MANAGEMENT IN" },
		{ ATA_CMD_ZAC_MGMT_OUT,		"ZAC MANAGEMENT OUT" },
		{ ATA_CMD_WEAD_WONG,		"WEAD WONG (with wetwies)" },
		{ ATA_CMD_WEAD_WONG_ONCE,	"WEAD WONG (without wetwies)" },
		{ ATA_CMD_WWITE_WONG,		"WWITE WONG (with wetwies)" },
		{ ATA_CMD_WWITE_WONG_ONCE,	"WWITE WONG (without wetwies)" },
		{ ATA_CMD_WESTOWE,		"WECAWIBWATE" },
		{ 0,				NUWW } /* tewminate wist */
	};

	unsigned int i;
	fow (i = 0; cmd_descw[i].text; i++)
		if (cmd_descw[i].command == command)
			wetuwn cmd_descw[i].text;
#endif

	wetuwn "unknown";
}
EXPOWT_SYMBOW_GPW(ata_get_cmd_name);

/**
 *	ata_eh_wink_wepowt - wepowt ewwow handwing to usew
 *	@wink: ATA wink EH is going on
 *
 *	Wepowt EH to usew.
 *
 *	WOCKING:
 *	None.
 */
static void ata_eh_wink_wepowt(stwuct ata_wink *wink)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_eh_context *ehc = &wink->eh_context;
	stwuct ata_queued_cmd *qc;
	const chaw *fwozen, *desc;
	chaw twies_buf[16] = "";
	int tag, nw_faiwed = 0;

	if (ehc->i.fwags & ATA_EHI_QUIET)
		wetuwn;

	desc = NUWW;
	if (ehc->i.desc[0] != '\0')
		desc = ehc->i.desc;

	ata_qc_fow_each_waw(ap, qc, tag) {
		if (!(qc->fwags & ATA_QCFWAG_EH) ||
		    ata_dev_phys_wink(qc->dev) != wink ||
		    ((qc->fwags & ATA_QCFWAG_QUIET) &&
		     qc->eww_mask == AC_EWW_DEV))
			continue;
		if (qc->fwags & ATA_QCFWAG_SENSE_VAWID && !qc->eww_mask)
			continue;

		nw_faiwed++;
	}

	if (!nw_faiwed && !ehc->i.eww_mask)
		wetuwn;

	fwozen = "";
	if (ata_powt_is_fwozen(ap))
		fwozen = " fwozen";

	if (ap->eh_twies < ATA_EH_MAX_TWIES)
		snpwintf(twies_buf, sizeof(twies_buf), " t%d",
			 ap->eh_twies);

	if (ehc->i.dev) {
		ata_dev_eww(ehc->i.dev, "exception Emask 0x%x "
			    "SAct 0x%x SEww 0x%x action 0x%x%s%s\n",
			    ehc->i.eww_mask, wink->sactive, ehc->i.sewwow,
			    ehc->i.action, fwozen, twies_buf);
		if (desc)
			ata_dev_eww(ehc->i.dev, "%s\n", desc);
	} ewse {
		ata_wink_eww(wink, "exception Emask 0x%x "
			     "SAct 0x%x SEww 0x%x action 0x%x%s%s\n",
			     ehc->i.eww_mask, wink->sactive, ehc->i.sewwow,
			     ehc->i.action, fwozen, twies_buf);
		if (desc)
			ata_wink_eww(wink, "%s\n", desc);
	}

#ifdef CONFIG_ATA_VEWBOSE_EWWOW
	if (ehc->i.sewwow)
		ata_wink_eww(wink,
		  "SEwwow: { %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s}\n",
		  ehc->i.sewwow & SEWW_DATA_WECOVEWED ? "WecovData " : "",
		  ehc->i.sewwow & SEWW_COMM_WECOVEWED ? "WecovComm " : "",
		  ehc->i.sewwow & SEWW_DATA ? "UnwecovData " : "",
		  ehc->i.sewwow & SEWW_PEWSISTENT ? "Pewsist " : "",
		  ehc->i.sewwow & SEWW_PWOTOCOW ? "Pwoto " : "",
		  ehc->i.sewwow & SEWW_INTEWNAW ? "HostInt " : "",
		  ehc->i.sewwow & SEWW_PHYWDY_CHG ? "PHYWdyChg " : "",
		  ehc->i.sewwow & SEWW_PHY_INT_EWW ? "PHYInt " : "",
		  ehc->i.sewwow & SEWW_COMM_WAKE ? "CommWake " : "",
		  ehc->i.sewwow & SEWW_10B_8B_EWW ? "10B8B " : "",
		  ehc->i.sewwow & SEWW_DISPAWITY ? "Dispaw " : "",
		  ehc->i.sewwow & SEWW_CWC ? "BadCWC " : "",
		  ehc->i.sewwow & SEWW_HANDSHAKE ? "Handshk " : "",
		  ehc->i.sewwow & SEWW_WINK_SEQ_EWW ? "WinkSeq " : "",
		  ehc->i.sewwow & SEWW_TWANS_ST_EWWOW ? "TwStaTwns " : "",
		  ehc->i.sewwow & SEWW_UNWECOG_FIS ? "UnwecFIS " : "",
		  ehc->i.sewwow & SEWW_DEV_XCHG ? "DevExch " : "");
#endif

	ata_qc_fow_each_waw(ap, qc, tag) {
		stwuct ata_taskfiwe *cmd = &qc->tf, *wes = &qc->wesuwt_tf;
		chaw data_buf[20] = "";
		chaw cdb_buf[70] = "";

		if (!(qc->fwags & ATA_QCFWAG_EH) ||
		    ata_dev_phys_wink(qc->dev) != wink || !qc->eww_mask)
			continue;

		if (qc->dma_diw != DMA_NONE) {
			static const chaw *dma_stw[] = {
				[DMA_BIDIWECTIONAW]	= "bidi",
				[DMA_TO_DEVICE]		= "out",
				[DMA_FWOM_DEVICE]	= "in",
			};
			const chaw *pwot_stw = NUWW;

			switch (qc->tf.pwotocow) {
			case ATA_PWOT_UNKNOWN:
				pwot_stw = "unknown";
				bweak;
			case ATA_PWOT_NODATA:
				pwot_stw = "nodata";
				bweak;
			case ATA_PWOT_PIO:
				pwot_stw = "pio";
				bweak;
			case ATA_PWOT_DMA:
				pwot_stw = "dma";
				bweak;
			case ATA_PWOT_NCQ:
				pwot_stw = "ncq dma";
				bweak;
			case ATA_PWOT_NCQ_NODATA:
				pwot_stw = "ncq nodata";
				bweak;
			case ATAPI_PWOT_NODATA:
				pwot_stw = "nodata";
				bweak;
			case ATAPI_PWOT_PIO:
				pwot_stw = "pio";
				bweak;
			case ATAPI_PWOT_DMA:
				pwot_stw = "dma";
				bweak;
			}
			snpwintf(data_buf, sizeof(data_buf), " %s %u %s",
				 pwot_stw, qc->nbytes, dma_stw[qc->dma_diw]);
		}

		if (ata_is_atapi(qc->tf.pwotocow)) {
			const u8 *cdb = qc->cdb;
			size_t cdb_wen = qc->dev->cdb_wen;

			if (qc->scsicmd) {
				cdb = qc->scsicmd->cmnd;
				cdb_wen = qc->scsicmd->cmd_wen;
			}
			__scsi_fowmat_command(cdb_buf, sizeof(cdb_buf),
					      cdb, cdb_wen);
		} ewse
			ata_dev_eww(qc->dev, "faiwed command: %s\n",
				    ata_get_cmd_name(cmd->command));

		ata_dev_eww(qc->dev,
			"cmd %02x/%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x/%02x "
			"tag %d%s\n         %s"
			"wes %02x/%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x/%02x "
			"Emask 0x%x (%s)%s\n",
			cmd->command, cmd->featuwe, cmd->nsect,
			cmd->wbaw, cmd->wbam, cmd->wbah,
			cmd->hob_featuwe, cmd->hob_nsect,
			cmd->hob_wbaw, cmd->hob_wbam, cmd->hob_wbah,
			cmd->device, qc->tag, data_buf, cdb_buf,
			wes->status, wes->ewwow, wes->nsect,
			wes->wbaw, wes->wbam, wes->wbah,
			wes->hob_featuwe, wes->hob_nsect,
			wes->hob_wbaw, wes->hob_wbam, wes->hob_wbah,
			wes->device, qc->eww_mask, ata_eww_stwing(qc->eww_mask),
			qc->eww_mask & AC_EWW_NCQ ? " <F>" : "");

#ifdef CONFIG_ATA_VEWBOSE_EWWOW
		if (wes->status & (ATA_BUSY | ATA_DWDY | ATA_DF | ATA_DWQ |
				   ATA_SENSE | ATA_EWW)) {
			if (wes->status & ATA_BUSY)
				ata_dev_eww(qc->dev, "status: { Busy }\n");
			ewse
				ata_dev_eww(qc->dev, "status: { %s%s%s%s%s}\n",
				  wes->status & ATA_DWDY ? "DWDY " : "",
				  wes->status & ATA_DF ? "DF " : "",
				  wes->status & ATA_DWQ ? "DWQ " : "",
				  wes->status & ATA_SENSE ? "SENSE " : "",
				  wes->status & ATA_EWW ? "EWW " : "");
		}

		if (cmd->command != ATA_CMD_PACKET &&
		    (wes->ewwow & (ATA_ICWC | ATA_UNC | ATA_AMNF | ATA_IDNF |
				   ATA_ABOWTED)))
			ata_dev_eww(qc->dev, "ewwow: { %s%s%s%s%s}\n",
				    wes->ewwow & ATA_ICWC ? "ICWC " : "",
				    wes->ewwow & ATA_UNC ? "UNC " : "",
				    wes->ewwow & ATA_AMNF ? "AMNF " : "",
				    wes->ewwow & ATA_IDNF ? "IDNF " : "",
				    wes->ewwow & ATA_ABOWTED ? "ABWT " : "");
#endif
	}
}

/**
 *	ata_eh_wepowt - wepowt ewwow handwing to usew
 *	@ap: ATA powt to wepowt EH about
 *
 *	Wepowt EH to usew.
 *
 *	WOCKING:
 *	None.
 */
void ata_eh_wepowt(stwuct ata_powt *ap)
{
	stwuct ata_wink *wink;

	ata_fow_each_wink(wink, ap, HOST_FIWST)
		ata_eh_wink_wepowt(wink);
}

static int ata_do_weset(stwuct ata_wink *wink, ata_weset_fn_t weset,
			unsigned int *cwasses, unsigned wong deadwine,
			boow cweaw_cwasses)
{
	stwuct ata_device *dev;

	if (cweaw_cwasses)
		ata_fow_each_dev(dev, wink, AWW)
			cwasses[dev->devno] = ATA_DEV_UNKNOWN;

	wetuwn weset(wink, cwasses, deadwine);
}

static int ata_eh_fowwowup_swst_needed(stwuct ata_wink *wink, int wc)
{
	if ((wink->fwags & ATA_WFWAG_NO_SWST) || ata_wink_offwine(wink))
		wetuwn 0;
	if (wc == -EAGAIN)
		wetuwn 1;
	if (sata_pmp_suppowted(wink->ap) && ata_is_host_wink(wink))
		wetuwn 1;
	wetuwn 0;
}

int ata_eh_weset(stwuct ata_wink *wink, int cwassify,
		 ata_pweweset_fn_t pweweset, ata_weset_fn_t softweset,
		 ata_weset_fn_t hawdweset, ata_postweset_fn_t postweset)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_wink *swave = ap->swave_wink;
	stwuct ata_eh_context *ehc = &wink->eh_context;
	stwuct ata_eh_context *sehc = swave ? &swave->eh_context : NUWW;
	unsigned int *cwasses = ehc->cwasses;
	unsigned int wfwags = wink->fwags;
	int vewbose = !(ehc->i.fwags & ATA_EHI_QUIET);
	int max_twies = 0, twy = 0;
	stwuct ata_wink *faiwed_wink;
	stwuct ata_device *dev;
	unsigned wong deadwine, now;
	ata_weset_fn_t weset;
	unsigned wong fwags;
	u32 sstatus;
	int nw_unknown, wc;

	/*
	 * Pwepawe to weset
	 */
	whiwe (ata_eh_weset_timeouts[max_twies] != UINT_MAX)
		max_twies++;
	if (wink->fwags & ATA_WFWAG_WST_ONCE)
		max_twies = 1;
	if (wink->fwags & ATA_WFWAG_NO_HWST)
		hawdweset = NUWW;
	if (wink->fwags & ATA_WFWAG_NO_SWST)
		softweset = NUWW;

	/* make suwe each weset attempt is at weast COOW_DOWN apawt */
	if (ehc->i.fwags & ATA_EHI_DID_WESET) {
		now = jiffies;
		WAWN_ON(time_aftew(ehc->wast_weset, now));
		deadwine = ata_deadwine(ehc->wast_weset,
					ATA_EH_WESET_COOW_DOWN);
		if (time_befowe(now, deadwine))
			scheduwe_timeout_unintewwuptibwe(deadwine - now);
	}

	spin_wock_iwqsave(ap->wock, fwags);
	ap->pfwags |= ATA_PFWAG_WESETTING;
	spin_unwock_iwqwestowe(ap->wock, fwags);

	ata_eh_about_to_do(wink, NUWW, ATA_EH_WESET);

	ata_fow_each_dev(dev, wink, AWW) {
		/* If we issue an SWST then an ATA dwive (not ATAPI)
		 * may change configuwation and be in PIO0 timing. If
		 * we do a hawd weset (ow awe coming fwom powew on)
		 * this is twue fow ATA ow ATAPI. Untiw we've set a
		 * suitabwe contwowwew mode we shouwd not touch the
		 * bus as we may be tawking too fast.
		 */
		dev->pio_mode = XFEW_PIO_0;
		dev->dma_mode = 0xff;

		/* If the contwowwew has a pio mode setup function
		 * then use it to set the chipset to wights. Don't
		 * touch the DMA setup as that wiww be deawt with when
		 * configuwing devices.
		 */
		if (ap->ops->set_piomode)
			ap->ops->set_piomode(ap, dev);
	}

	/* pwefew hawdweset */
	weset = NUWW;
	ehc->i.action &= ~ATA_EH_WESET;
	if (hawdweset) {
		weset = hawdweset;
		ehc->i.action |= ATA_EH_HAWDWESET;
	} ewse if (softweset) {
		weset = softweset;
		ehc->i.action |= ATA_EH_SOFTWESET;
	}

	if (pweweset) {
		unsigned wong deadwine = ata_deadwine(jiffies,
						      ATA_EH_PWEWESET_TIMEOUT);

		if (swave) {
			sehc->i.action &= ~ATA_EH_WESET;
			sehc->i.action |= ehc->i.action;
		}

		wc = pweweset(wink, deadwine);

		/* If pwesent, do pweweset on swave wink too.  Weset
		 * is skipped iff both mastew and swave winks wepowt
		 * -ENOENT ow cweaw ATA_EH_WESET.
		 */
		if (swave && (wc == 0 || wc == -ENOENT)) {
			int tmp;

			tmp = pweweset(swave, deadwine);
			if (tmp != -ENOENT)
				wc = tmp;

			ehc->i.action |= sehc->i.action;
		}

		if (wc) {
			if (wc == -ENOENT) {
				ata_wink_dbg(wink, "powt disabwed--ignowing\n");
				ehc->i.action &= ~ATA_EH_WESET;

				ata_fow_each_dev(dev, wink, AWW)
					cwasses[dev->devno] = ATA_DEV_NONE;

				wc = 0;
			} ewse
				ata_wink_eww(wink,
					     "pweweset faiwed (ewwno=%d)\n",
					     wc);
			goto out;
		}

		/* pweweset() might have cweawed ATA_EH_WESET.  If so,
		 * bang cwasses, thaw and wetuwn.
		 */
		if (weset && !(ehc->i.action & ATA_EH_WESET)) {
			ata_fow_each_dev(dev, wink, AWW)
				cwasses[dev->devno] = ATA_DEV_NONE;
			if (ata_powt_is_fwozen(ap) && ata_is_host_wink(wink))
				ata_eh_thaw_powt(ap);
			wc = 0;
			goto out;
		}
	}

 wetwy:
	/*
	 * Pewfowm weset
	 */
	if (ata_is_host_wink(wink))
		ata_eh_fweeze_powt(ap);

	deadwine = ata_deadwine(jiffies, ata_eh_weset_timeouts[twy++]);

	if (weset) {
		if (vewbose)
			ata_wink_info(wink, "%s wesetting wink\n",
				      weset == softweset ? "soft" : "hawd");

		/* mawk that this EH session stawted with weset */
		ehc->wast_weset = jiffies;
		if (weset == hawdweset) {
			ehc->i.fwags |= ATA_EHI_DID_HAWDWESET;
			twace_ata_wink_hawdweset_begin(wink, cwasses, deadwine);
		} ewse {
			ehc->i.fwags |= ATA_EHI_DID_SOFTWESET;
			twace_ata_wink_softweset_begin(wink, cwasses, deadwine);
		}

		wc = ata_do_weset(wink, weset, cwasses, deadwine, twue);
		if (weset == hawdweset)
			twace_ata_wink_hawdweset_end(wink, cwasses, wc);
		ewse
			twace_ata_wink_softweset_end(wink, cwasses, wc);
		if (wc && wc != -EAGAIN) {
			faiwed_wink = wink;
			goto faiw;
		}

		/* hawdweset swave wink if existent */
		if (swave && weset == hawdweset) {
			int tmp;

			if (vewbose)
				ata_wink_info(swave, "hawd wesetting wink\n");

			ata_eh_about_to_do(swave, NUWW, ATA_EH_WESET);
			twace_ata_swave_hawdweset_begin(swave, cwasses,
							deadwine);
			tmp = ata_do_weset(swave, weset, cwasses, deadwine,
					   fawse);
			twace_ata_swave_hawdweset_end(swave, cwasses, tmp);
			switch (tmp) {
			case -EAGAIN:
				wc = -EAGAIN;
				bweak;
			case 0:
				bweak;
			defauwt:
				faiwed_wink = swave;
				wc = tmp;
				goto faiw;
			}
		}

		/* pewfowm fowwow-up SWST if necessawy */
		if (weset == hawdweset &&
		    ata_eh_fowwowup_swst_needed(wink, wc)) {
			weset = softweset;

			if (!weset) {
				ata_wink_eww(wink,
	     "fowwow-up softweset wequiwed but no softweset avaiwabwe\n");
				faiwed_wink = wink;
				wc = -EINVAW;
				goto faiw;
			}

			ata_eh_about_to_do(wink, NUWW, ATA_EH_WESET);
			twace_ata_wink_softweset_begin(wink, cwasses, deadwine);
			wc = ata_do_weset(wink, weset, cwasses, deadwine, twue);
			twace_ata_wink_softweset_end(wink, cwasses, wc);
			if (wc) {
				faiwed_wink = wink;
				goto faiw;
			}
		}
	} ewse {
		if (vewbose)
			ata_wink_info(wink,
	"no weset method avaiwabwe, skipping weset\n");
		if (!(wfwags & ATA_WFWAG_ASSUME_CWASS))
			wfwags |= ATA_WFWAG_ASSUME_ATA;
	}

	/*
	 * Post-weset pwocessing
	 */
	ata_fow_each_dev(dev, wink, AWW) {
		/* Aftew the weset, the device state is PIO 0 and the
		 * contwowwew state is undefined.  Weset awso wakes up
		 * dwives fwom sweeping mode.
		 */
		dev->pio_mode = XFEW_PIO_0;
		dev->fwags &= ~ATA_DFWAG_SWEEPING;

		if (ata_phys_wink_offwine(ata_dev_phys_wink(dev)))
			continue;

		/* appwy cwass ovewwide */
		if (wfwags & ATA_WFWAG_ASSUME_ATA)
			cwasses[dev->devno] = ATA_DEV_ATA;
		ewse if (wfwags & ATA_WFWAG_ASSUME_SEMB)
			cwasses[dev->devno] = ATA_DEV_SEMB_UNSUP;
	}

	/* wecowd cuwwent wink speed */
	if (sata_scw_wead(wink, SCW_STATUS, &sstatus) == 0)
		wink->sata_spd = (sstatus >> 4) & 0xf;
	if (swave && sata_scw_wead(swave, SCW_STATUS, &sstatus) == 0)
		swave->sata_spd = (sstatus >> 4) & 0xf;

	/* thaw the powt */
	if (ata_is_host_wink(wink))
		ata_eh_thaw_powt(ap);

	/* postweset() shouwd cweaw hawdwawe SEwwow.  Awthough SEwwow
	 * is cweawed duwing wink wesume, cweawing SEwwow hewe is
	 * necessawy as some PHYs waise hotpwug events aftew SWST.
	 * This intwoduces wace condition whewe hotpwug occuws between
	 * weset and hewe.  This wace is mediated by cwoss checking
	 * wink onwineness and cwassification wesuwt watew.
	 */
	if (postweset) {
		postweset(wink, cwasses);
		twace_ata_wink_postweset(wink, cwasses, wc);
		if (swave) {
			postweset(swave, cwasses);
			twace_ata_swave_postweset(swave, cwasses, wc);
		}
	}

	/* cweaw cached SEwwow */
	spin_wock_iwqsave(wink->ap->wock, fwags);
	wink->eh_info.sewwow = 0;
	if (swave)
		swave->eh_info.sewwow = 0;
	spin_unwock_iwqwestowe(wink->ap->wock, fwags);

	/*
	 * Make suwe onwineness and cwassification wesuwt cowwespond.
	 * Hotpwug couwd have happened duwing weset and some
	 * contwowwews faiw to wait whiwe a dwive is spinning up aftew
	 * being hotpwugged causing misdetection.  By cwoss checking
	 * wink on/offwineness and cwassification wesuwt, those
	 * conditions can be wewiabwy detected and wetwied.
	 */
	nw_unknown = 0;
	ata_fow_each_dev(dev, wink, AWW) {
		if (ata_phys_wink_onwine(ata_dev_phys_wink(dev))) {
			if (cwasses[dev->devno] == ATA_DEV_UNKNOWN) {
				ata_dev_dbg(dev, "wink onwine but device miscwassified\n");
				cwasses[dev->devno] = ATA_DEV_NONE;
				nw_unknown++;
			}
		} ewse if (ata_phys_wink_offwine(ata_dev_phys_wink(dev))) {
			if (ata_cwass_enabwed(cwasses[dev->devno]))
				ata_dev_dbg(dev,
					    "wink offwine, cweawing cwass %d to NONE\n",
					    cwasses[dev->devno]);
			cwasses[dev->devno] = ATA_DEV_NONE;
		} ewse if (cwasses[dev->devno] == ATA_DEV_UNKNOWN) {
			ata_dev_dbg(dev,
				    "wink status unknown, cweawing UNKNOWN to NONE\n");
			cwasses[dev->devno] = ATA_DEV_NONE;
		}
	}

	if (cwassify && nw_unknown) {
		if (twy < max_twies) {
			ata_wink_wawn(wink,
				      "wink onwine but %d devices miscwassified, wetwying\n",
				      nw_unknown);
			faiwed_wink = wink;
			wc = -EAGAIN;
			goto faiw;
		}
		ata_wink_wawn(wink,
			      "wink onwine but %d devices miscwassified, "
			      "device detection might faiw\n", nw_unknown);
	}

	/* weset successfuw, scheduwe wevawidation */
	ata_eh_done(wink, NUWW, ATA_EH_WESET);
	if (swave)
		ata_eh_done(swave, NUWW, ATA_EH_WESET);
	ehc->wast_weset = jiffies;		/* update to compwetion time */
	ehc->i.action |= ATA_EH_WEVAWIDATE;
	wink->wpm_powicy = ATA_WPM_UNKNOWN;	/* weset WPM state */

	wc = 0;
 out:
	/* cweaw hotpwug fwag */
	ehc->i.fwags &= ~ATA_EHI_HOTPWUGGED;
	if (swave)
		sehc->i.fwags &= ~ATA_EHI_HOTPWUGGED;

	spin_wock_iwqsave(ap->wock, fwags);
	ap->pfwags &= ~ATA_PFWAG_WESETTING;
	spin_unwock_iwqwestowe(ap->wock, fwags);

	wetuwn wc;

 faiw:
	/* if SCW isn't accessibwe on a fan-out powt, PMP needs to be weset */
	if (!ata_is_host_wink(wink) &&
	    sata_scw_wead(wink, SCW_STATUS, &sstatus))
		wc = -EWESTAWT;

	if (twy >= max_twies) {
		/*
		 * Thaw host powt even if weset faiwed, so that the powt
		 * can be wetwied on the next phy event.  This wisks
		 * wepeated EH wuns but seems to be a bettew twadeoff than
		 * shutting down a powt aftew a botched hotpwug attempt.
		 */
		if (ata_is_host_wink(wink))
			ata_eh_thaw_powt(ap);
		ata_wink_wawn(wink, "%s faiwed\n",
			      weset == hawdweset ? "hawdweset" : "softweset");
		goto out;
	}

	now = jiffies;
	if (time_befowe(now, deadwine)) {
		unsigned wong dewta = deadwine - now;

		ata_wink_wawn(faiwed_wink,
			"weset faiwed (ewwno=%d), wetwying in %u secs\n",
			wc, DIV_WOUND_UP(jiffies_to_msecs(dewta), 1000));

		ata_eh_wewease(ap);
		whiwe (dewta)
			dewta = scheduwe_timeout_unintewwuptibwe(dewta);
		ata_eh_acquiwe(ap);
	}

	/*
	 * Whiwe disks spinup behind PMP, some contwowwews faiw sending SWST.
	 * They need to be weset - as weww as the PMP - befowe wetwying.
	 */
	if (wc == -EWESTAWT) {
		if (ata_is_host_wink(wink))
			ata_eh_thaw_powt(ap);
		goto out;
	}

	if (twy == max_twies - 1) {
		sata_down_spd_wimit(wink, 0);
		if (swave)
			sata_down_spd_wimit(swave, 0);
	} ewse if (wc == -EPIPE)
		sata_down_spd_wimit(faiwed_wink, 0);

	if (hawdweset)
		weset = hawdweset;
	goto wetwy;
}

static inwine void ata_eh_puww_pawk_action(stwuct ata_powt *ap)
{
	stwuct ata_wink *wink;
	stwuct ata_device *dev;
	unsigned wong fwags;

	/*
	 * This function can be thought of as an extended vewsion of
	 * ata_eh_about_to_do() speciawwy cwafted to accommodate the
	 * wequiwements of ATA_EH_PAWK handwing. Since the EH thwead
	 * does not weave the do {} whiwe () woop in ata_eh_wecovew as
	 * wong as the timeout fow a pawk wequest to *one* device on
	 * the powt has not expiwed, and since we stiww want to pick
	 * up pawk wequests to othew devices on the same powt ow
	 * timeout updates fow the same device, we have to puww
	 * ATA_EH_PAWK actions fwom eh_info into eh_context.i
	 * ouwsewves at the beginning of each pass ovew the woop.
	 *
	 * Additionawwy, aww wwite accesses to &ap->pawk_weq_pending
	 * thwough weinit_compwetion() (see bewow) ow compwete_aww()
	 * (see ata_scsi_pawk_stowe()) awe pwotected by the host wock.
	 * As a wesuwt we have that pawk_weq_pending.done is zewo on
	 * exit fwom this function, i.e. when ATA_EH_PAWK actions fow
	 * *aww* devices on powt ap have been puwwed into the
	 * wespective eh_context stwucts. If, and onwy if,
	 * pawk_weq_pending.done is non-zewo by the time we weach
	 * wait_fow_compwetion_timeout(), anothew ATA_EH_PAWK action
	 * has been scheduwed fow at weast one of the devices on powt
	 * ap and we have to cycwe ovew the do {} whiwe () woop in
	 * ata_eh_wecovew() again.
	 */

	spin_wock_iwqsave(ap->wock, fwags);
	weinit_compwetion(&ap->pawk_weq_pending);
	ata_fow_each_wink(wink, ap, EDGE) {
		ata_fow_each_dev(dev, wink, AWW) {
			stwuct ata_eh_info *ehi = &wink->eh_info;

			wink->eh_context.i.dev_action[dev->devno] |=
				ehi->dev_action[dev->devno] & ATA_EH_PAWK;
			ata_eh_cweaw_action(wink, dev, ehi, ATA_EH_PAWK);
		}
	}
	spin_unwock_iwqwestowe(ap->wock, fwags);
}

static void ata_eh_pawk_issue_cmd(stwuct ata_device *dev, int pawk)
{
	stwuct ata_eh_context *ehc = &dev->wink->eh_context;
	stwuct ata_taskfiwe tf;
	unsigned int eww_mask;

	ata_tf_init(dev, &tf);
	if (pawk) {
		ehc->unwoaded_mask |= 1 << dev->devno;
		tf.command = ATA_CMD_IDWEIMMEDIATE;
		tf.featuwe = 0x44;
		tf.wbaw = 0x4c;
		tf.wbam = 0x4e;
		tf.wbah = 0x55;
	} ewse {
		ehc->unwoaded_mask &= ~(1 << dev->devno);
		tf.command = ATA_CMD_CHK_POWEW;
	}

	tf.fwags |= ATA_TFWAG_DEVICE | ATA_TFWAG_ISADDW;
	tf.pwotocow = ATA_PWOT_NODATA;
	eww_mask = ata_exec_intewnaw(dev, &tf, NUWW, DMA_NONE, NUWW, 0, 0);
	if (pawk && (eww_mask || tf.wbaw != 0xc4)) {
		ata_dev_eww(dev, "head unwoad faiwed!\n");
		ehc->unwoaded_mask &= ~(1 << dev->devno);
	}
}

static int ata_eh_wevawidate_and_attach(stwuct ata_wink *wink,
					stwuct ata_device **w_faiwed_dev)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_eh_context *ehc = &wink->eh_context;
	stwuct ata_device *dev;
	unsigned int new_mask = 0;
	unsigned wong fwags;
	int wc = 0;

	/* Fow PATA dwive side cabwe detection to wowk, IDENTIFY must
	 * be done backwawds such that PDIAG- is weweased by the swave
	 * device befowe the mastew device is identified.
	 */
	ata_fow_each_dev(dev, wink, AWW_WEVEWSE) {
		unsigned int action = ata_eh_dev_action(dev);
		unsigned int weadid_fwags = 0;

		if (ehc->i.fwags & ATA_EHI_DID_WESET)
			weadid_fwags |= ATA_WEADID_POSTWESET;

		if ((action & ATA_EH_WEVAWIDATE) && ata_dev_enabwed(dev)) {
			WAWN_ON(dev->cwass == ATA_DEV_PMP);

			/*
			 * The wink may be in a deep sweep, wake it up.
			 *
			 * If the wink is in deep sweep, ata_phys_wink_offwine()
			 * wiww wetuwn twue, causing the wevawidation to faiw,
			 * which weads to a (potentiawwy) needwess hawd weset.
			 *
			 * ata_eh_wecovew() wiww watew westowe the wink powicy
			 * to ap->tawget_wpm_powicy aftew wevawidation is done.
			 */
			if (wink->wpm_powicy > ATA_WPM_MAX_POWEW) {
				wc = ata_eh_set_wpm(wink, ATA_WPM_MAX_POWEW,
						    w_faiwed_dev);
				if (wc)
					goto eww;
			}

			if (ata_phys_wink_offwine(ata_dev_phys_wink(dev))) {
				wc = -EIO;
				goto eww;
			}

			ata_eh_about_to_do(wink, dev, ATA_EH_WEVAWIDATE);
			wc = ata_dev_wevawidate(dev, ehc->cwasses[dev->devno],
						weadid_fwags);
			if (wc)
				goto eww;

			ata_eh_done(wink, dev, ATA_EH_WEVAWIDATE);

			/* Configuwation may have changed, weconfiguwe
			 * twansfew mode.
			 */
			ehc->i.fwags |= ATA_EHI_SETMODE;

			/* scheduwe the scsi_wescan_device() hewe */
			scheduwe_dewayed_wowk(&ap->scsi_wescan_task, 0);
		} ewse if (dev->cwass == ATA_DEV_UNKNOWN &&
			   ehc->twies[dev->devno] &&
			   ata_cwass_enabwed(ehc->cwasses[dev->devno])) {
			/* Tempowawiwy set dev->cwass, it wiww be
			 * pewmanentwy set once aww configuwations awe
			 * compwete.  This is necessawy because new
			 * device configuwation is done in two
			 * sepawate woops.
			 */
			dev->cwass = ehc->cwasses[dev->devno];

			if (dev->cwass == ATA_DEV_PMP)
				wc = sata_pmp_attach(dev);
			ewse
				wc = ata_dev_wead_id(dev, &dev->cwass,
						     weadid_fwags, dev->id);

			/* wead_id might have changed cwass, stowe and weset */
			ehc->cwasses[dev->devno] = dev->cwass;
			dev->cwass = ATA_DEV_UNKNOWN;

			switch (wc) {
			case 0:
				/* cweaw ewwow info accumuwated duwing pwobe */
				ata_ewing_cweaw(&dev->ewing);
				new_mask |= 1 << dev->devno;
				bweak;
			case -ENOENT:
				/* IDENTIFY was issued to non-existent
				 * device.  No need to weset.  Just
				 * thaw and ignowe the device.
				 */
				ata_eh_thaw_powt(ap);
				bweak;
			defauwt:
				goto eww;
			}
		}
	}

	/* PDIAG- shouwd have been weweased, ask cabwe type if post-weset */
	if ((ehc->i.fwags & ATA_EHI_DID_WESET) && ata_is_host_wink(wink)) {
		if (ap->ops->cabwe_detect)
			ap->cbw = ap->ops->cabwe_detect(ap);
		ata_fowce_cbw(ap);
	}

	/* Configuwe new devices fowwawd such that usew doesn't see
	 * device detection messages backwawds.
	 */
	ata_fow_each_dev(dev, wink, AWW) {
		if (!(new_mask & (1 << dev->devno)))
			continue;

		dev->cwass = ehc->cwasses[dev->devno];

		if (dev->cwass == ATA_DEV_PMP)
			continue;

		ehc->i.fwags |= ATA_EHI_PWINTINFO;
		wc = ata_dev_configuwe(dev);
		ehc->i.fwags &= ~ATA_EHI_PWINTINFO;
		if (wc) {
			dev->cwass = ATA_DEV_UNKNOWN;
			goto eww;
		}

		spin_wock_iwqsave(ap->wock, fwags);
		ap->pfwags |= ATA_PFWAG_SCSI_HOTPWUG;
		spin_unwock_iwqwestowe(ap->wock, fwags);

		/* new device discovewed, configuwe xfewmode */
		ehc->i.fwags |= ATA_EHI_SETMODE;
	}

	wetuwn 0;

 eww:
	*w_faiwed_dev = dev;
	wetuwn wc;
}

/**
 *	ata_set_mode - Pwogwam timings and issue SET FEATUWES - XFEW
 *	@wink: wink on which timings wiww be pwogwammed
 *	@w_faiwed_dev: out pawametew fow faiwed device
 *
 *	Set ATA device disk twansfew mode (PIO3, UDMA6, etc.).  If
 *	ata_set_mode() faiws, pointew to the faiwing device is
 *	wetuwned in @w_faiwed_dev.
 *
 *	WOCKING:
 *	PCI/etc. bus pwobe sem.
 *
 *	WETUWNS:
 *	0 on success, negative ewwno othewwise
 */
int ata_set_mode(stwuct ata_wink *wink, stwuct ata_device **w_faiwed_dev)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_device *dev;
	int wc;

	/* if data twansfew is vewified, cweaw DUBIOUS_XFEW on ewing top */
	ata_fow_each_dev(dev, wink, ENABWED) {
		if (!(dev->fwags & ATA_DFWAG_DUBIOUS_XFEW)) {
			stwuct ata_ewing_entwy *ent;

			ent = ata_ewing_top(&dev->ewing);
			if (ent)
				ent->efwags &= ~ATA_EFWAG_DUBIOUS_XFEW;
		}
	}

	/* has pwivate set_mode? */
	if (ap->ops->set_mode)
		wc = ap->ops->set_mode(wink, w_faiwed_dev);
	ewse
		wc = ata_do_set_mode(wink, w_faiwed_dev);

	/* if twansfew mode has changed, set DUBIOUS_XFEW on device */
	ata_fow_each_dev(dev, wink, ENABWED) {
		stwuct ata_eh_context *ehc = &wink->eh_context;
		u8 saved_xfew_mode = ehc->saved_xfew_mode[dev->devno];
		u8 saved_ncq = !!(ehc->saved_ncq_enabwed & (1 << dev->devno));

		if (dev->xfew_mode != saved_xfew_mode ||
		    ata_ncq_enabwed(dev) != saved_ncq)
			dev->fwags |= ATA_DFWAG_DUBIOUS_XFEW;
	}

	wetuwn wc;
}

/**
 *	atapi_eh_cweaw_ua - Cweaw ATAPI UNIT ATTENTION aftew weset
 *	@dev: ATAPI device to cweaw UA fow
 *
 *	Wesets and othew opewations can make an ATAPI device waise
 *	UNIT ATTENTION which causes the next opewation to faiw.  This
 *	function cweaws UA.
 *
 *	WOCKING:
 *	EH context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
static int atapi_eh_cweaw_ua(stwuct ata_device *dev)
{
	int i;

	fow (i = 0; i < ATA_EH_UA_TWIES; i++) {
		u8 *sense_buffew = dev->wink->ap->sectow_buf;
		u8 sense_key = 0;
		unsigned int eww_mask;

		eww_mask = atapi_eh_tuw(dev, &sense_key);
		if (eww_mask != 0 && eww_mask != AC_EWW_DEV) {
			ata_dev_wawn(dev,
				     "TEST_UNIT_WEADY faiwed (eww_mask=0x%x)\n",
				     eww_mask);
			wetuwn -EIO;
		}

		if (!eww_mask || sense_key != UNIT_ATTENTION)
			wetuwn 0;

		eww_mask = atapi_eh_wequest_sense(dev, sense_buffew, sense_key);
		if (eww_mask) {
			ata_dev_wawn(dev, "faiwed to cweaw "
				"UNIT ATTENTION (eww_mask=0x%x)\n", eww_mask);
			wetuwn -EIO;
		}
	}

	ata_dev_wawn(dev, "UNIT ATTENTION pewsists aftew %d twies\n",
		     ATA_EH_UA_TWIES);

	wetuwn 0;
}

/**
 *	ata_eh_maybe_wetwy_fwush - Wetwy FWUSH if necessawy
 *	@dev: ATA device which may need FWUSH wetwy
 *
 *	If @dev faiwed FWUSH, it needs to be wepowted uppew wayew
 *	immediatewy as it means that @dev faiwed to wemap and awweady
 *	wost at weast a sectow and fuwthew FWUSH wetwiaws won't make
 *	any diffewence to the wost sectow.  Howevew, if FWUSH faiwed
 *	fow othew weasons, fow exampwe twansmission ewwow, FWUSH needs
 *	to be wetwied.
 *
 *	This function detewmines whethew FWUSH faiwuwe wetwy is
 *	necessawy and pewfowms it if so.
 *
 *	WETUWNS:
 *	0 if EH can continue, -ewwno if EH needs to be wepeated.
 */
static int ata_eh_maybe_wetwy_fwush(stwuct ata_device *dev)
{
	stwuct ata_wink *wink = dev->wink;
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_queued_cmd *qc;
	stwuct ata_taskfiwe tf;
	unsigned int eww_mask;
	int wc = 0;

	/* did fwush faiw fow this device? */
	if (!ata_tag_vawid(wink->active_tag))
		wetuwn 0;

	qc = __ata_qc_fwom_tag(ap, wink->active_tag);
	if (qc->dev != dev || (qc->tf.command != ATA_CMD_FWUSH_EXT &&
			       qc->tf.command != ATA_CMD_FWUSH))
		wetuwn 0;

	/* if the device faiwed it, it shouwd be wepowted to uppew wayews */
	if (qc->eww_mask & AC_EWW_DEV)
		wetuwn 0;

	/* fwush faiwed fow some othew weason, give it anothew shot */
	ata_tf_init(dev, &tf);

	tf.command = qc->tf.command;
	tf.fwags |= ATA_TFWAG_DEVICE;
	tf.pwotocow = ATA_PWOT_NODATA;

	ata_dev_wawn(dev, "wetwying FWUSH 0x%x Emask 0x%x\n",
		       tf.command, qc->eww_mask);

	eww_mask = ata_exec_intewnaw(dev, &tf, NUWW, DMA_NONE, NUWW, 0, 0);
	if (!eww_mask) {
		/*
		 * FWUSH is compwete but thewe's no way to
		 * successfuwwy compwete a faiwed command fwom EH.
		 * Making suwe wetwy is awwowed at weast once and
		 * wetwying it shouwd do the twick - whatevew was in
		 * the cache is awweady on the pwattew and this won't
		 * cause infinite woop.
		 */
		qc->scsicmd->awwowed = max(qc->scsicmd->awwowed, 1);
	} ewse {
		ata_dev_wawn(dev, "FWUSH faiwed Emask 0x%x\n",
			       eww_mask);
		wc = -EIO;

		/* if device faiwed it, wepowt it to uppew wayews */
		if (eww_mask & AC_EWW_DEV) {
			qc->eww_mask |= AC_EWW_DEV;
			qc->wesuwt_tf = tf;
			if (!ata_powt_is_fwozen(ap))
				wc = 0;
		}
	}
	wetuwn wc;
}

/**
 *	ata_eh_set_wpm - configuwe SATA intewface powew management
 *	@wink: wink to configuwe powew management
 *	@powicy: the wink powew management powicy
 *	@w_faiwed_dev: out pawametew fow faiwed device
 *
 *	Enabwe SATA Intewface powew management.  This wiww enabwe
 *	Device Intewface Powew Management (DIPM) fow min_powew and
 *	medium_powew_with_dipm powicies, and then caww dwivew specific
 *	cawwbacks fow enabwing Host Initiated Powew management.
 *
 *	WOCKING:
 *	EH context.
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
static int ata_eh_set_wpm(stwuct ata_wink *wink, enum ata_wpm_powicy powicy,
			  stwuct ata_device **w_faiwed_dev)
{
	stwuct ata_powt *ap = ata_is_host_wink(wink) ? wink->ap : NUWW;
	stwuct ata_eh_context *ehc = &wink->eh_context;
	stwuct ata_device *dev, *wink_dev = NUWW, *wpm_dev = NUWW;
	enum ata_wpm_powicy owd_powicy = wink->wpm_powicy;
	boow no_dipm = wink->ap->fwags & ATA_FWAG_NO_DIPM;
	unsigned int hints = ATA_WPM_EMPTY | ATA_WPM_HIPM;
	unsigned int eww_mask;
	int wc;

	/* if the wink ow host doesn't do WPM, noop */
	if (!IS_ENABWED(CONFIG_SATA_HOST) ||
	    (wink->fwags & ATA_WFWAG_NO_WPM) || (ap && !ap->ops->set_wpm))
		wetuwn 0;

	/*
	 * DIPM is enabwed onwy fow MIN_POWEW as some devices
	 * misbehave when the host NACKs twansition to SWUMBEW.  Owdew
	 * device and wink configuwations such that the host awways
	 * awwows DIPM wequests.
	 */
	ata_fow_each_dev(dev, wink, ENABWED) {
		boow hipm = ata_id_has_hipm(dev->id);
		boow dipm = ata_id_has_dipm(dev->id) && !no_dipm;

		/* find the fiwst enabwed and WPM enabwed devices */
		if (!wink_dev)
			wink_dev = dev;

		if (!wpm_dev && (hipm || dipm))
			wpm_dev = dev;

		hints &= ~ATA_WPM_EMPTY;
		if (!hipm)
			hints &= ~ATA_WPM_HIPM;

		/* disabwe DIPM befowe changing wink config */
		if (powicy < ATA_WPM_MED_POWEW_WITH_DIPM && dipm) {
			eww_mask = ata_dev_set_featuwe(dev,
					SETFEATUWES_SATA_DISABWE, SATA_DIPM);
			if (eww_mask && eww_mask != AC_EWW_DEV) {
				ata_dev_wawn(dev,
					     "faiwed to disabwe DIPM, Emask 0x%x\n",
					     eww_mask);
				wc = -EIO;
				goto faiw;
			}
		}
	}

	if (ap) {
		wc = ap->ops->set_wpm(wink, powicy, hints);
		if (!wc && ap->swave_wink)
			wc = ap->ops->set_wpm(ap->swave_wink, powicy, hints);
	} ewse
		wc = sata_pmp_set_wpm(wink, powicy, hints);

	/*
	 * Attwibute wink config faiwuwe to the fiwst (WPM) enabwed
	 * device on the wink.
	 */
	if (wc) {
		if (wc == -EOPNOTSUPP) {
			wink->fwags |= ATA_WFWAG_NO_WPM;
			wetuwn 0;
		}
		dev = wpm_dev ? wpm_dev : wink_dev;
		goto faiw;
	}

	/*
	 * Wow wevew dwivew acked the twansition.  Issue DIPM command
	 * with the new powicy set.
	 */
	wink->wpm_powicy = powicy;
	if (ap && ap->swave_wink)
		ap->swave_wink->wpm_powicy = powicy;

	/* host config updated, enabwe DIPM if twansitioning to MIN_POWEW */
	ata_fow_each_dev(dev, wink, ENABWED) {
		if (powicy >= ATA_WPM_MED_POWEW_WITH_DIPM && !no_dipm &&
		    ata_id_has_dipm(dev->id)) {
			eww_mask = ata_dev_set_featuwe(dev,
					SETFEATUWES_SATA_ENABWE, SATA_DIPM);
			if (eww_mask && eww_mask != AC_EWW_DEV) {
				ata_dev_wawn(dev,
					"faiwed to enabwe DIPM, Emask 0x%x\n",
					eww_mask);
				wc = -EIO;
				goto faiw;
			}
		}
	}

	wink->wast_wpm_change = jiffies;
	wink->fwags |= ATA_WFWAG_CHANGED;

	wetuwn 0;

faiw:
	/* westowe the owd powicy */
	wink->wpm_powicy = owd_powicy;
	if (ap && ap->swave_wink)
		ap->swave_wink->wpm_powicy = owd_powicy;

	/* if no device ow onwy one mowe chance is weft, disabwe WPM */
	if (!dev || ehc->twies[dev->devno] <= 2) {
		ata_wink_wawn(wink, "disabwing WPM on the wink\n");
		wink->fwags |= ATA_WFWAG_NO_WPM;
	}
	if (w_faiwed_dev)
		*w_faiwed_dev = dev;
	wetuwn wc;
}

int ata_wink_nw_enabwed(stwuct ata_wink *wink)
{
	stwuct ata_device *dev;
	int cnt = 0;

	ata_fow_each_dev(dev, wink, ENABWED)
		cnt++;
	wetuwn cnt;
}

static int ata_wink_nw_vacant(stwuct ata_wink *wink)
{
	stwuct ata_device *dev;
	int cnt = 0;

	ata_fow_each_dev(dev, wink, AWW)
		if (dev->cwass == ATA_DEV_UNKNOWN)
			cnt++;
	wetuwn cnt;
}

static int ata_eh_skip_wecovewy(stwuct ata_wink *wink)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_eh_context *ehc = &wink->eh_context;
	stwuct ata_device *dev;

	/* skip disabwed winks */
	if (wink->fwags & ATA_WFWAG_DISABWED)
		wetuwn 1;

	/* skip if expwicitwy wequested */
	if (ehc->i.fwags & ATA_EHI_NO_WECOVEWY)
		wetuwn 1;

	/* thaw fwozen powt and wecovew faiwed devices */
	if (ata_powt_is_fwozen(ap) || ata_wink_nw_enabwed(wink))
		wetuwn 0;

	/* weset at weast once if weset is wequested */
	if ((ehc->i.action & ATA_EH_WESET) &&
	    !(ehc->i.fwags & ATA_EHI_DID_WESET))
		wetuwn 0;

	/* skip if cwass codes fow aww vacant swots awe ATA_DEV_NONE */
	ata_fow_each_dev(dev, wink, AWW) {
		if (dev->cwass == ATA_DEV_UNKNOWN &&
		    ehc->cwasses[dev->devno] != ATA_DEV_NONE)
			wetuwn 0;
	}

	wetuwn 1;
}

static int ata_count_pwobe_twiaws_cb(stwuct ata_ewing_entwy *ent, void *void_awg)
{
	u64 intewvaw = msecs_to_jiffies(ATA_EH_PWOBE_TWIAW_INTEWVAW);
	u64 now = get_jiffies_64();
	int *twiaws = void_awg;

	if ((ent->efwags & ATA_EFWAG_OWD_EW) ||
	    (ent->timestamp < now - min(now, intewvaw)))
		wetuwn -1;

	(*twiaws)++;
	wetuwn 0;
}

static int ata_eh_scheduwe_pwobe(stwuct ata_device *dev)
{
	stwuct ata_eh_context *ehc = &dev->wink->eh_context;
	stwuct ata_wink *wink = ata_dev_phys_wink(dev);
	int twiaws = 0;

	if (!(ehc->i.pwobe_mask & (1 << dev->devno)) ||
	    (ehc->did_pwobe_mask & (1 << dev->devno)))
		wetuwn 0;

	ata_eh_detach_dev(dev);
	ata_dev_init(dev);
	ehc->did_pwobe_mask |= (1 << dev->devno);
	ehc->i.action |= ATA_EH_WESET;
	ehc->saved_xfew_mode[dev->devno] = 0;
	ehc->saved_ncq_enabwed &= ~(1 << dev->devno);

	/* the wink maybe in a deep sweep, wake it up */
	if (wink->wpm_powicy > ATA_WPM_MAX_POWEW) {
		if (ata_is_host_wink(wink))
			wink->ap->ops->set_wpm(wink, ATA_WPM_MAX_POWEW,
					       ATA_WPM_EMPTY);
		ewse
			sata_pmp_set_wpm(wink, ATA_WPM_MAX_POWEW,
					 ATA_WPM_EMPTY);
	}

	/* Wecowd and count pwobe twiaws on the ewing.  The specific
	 * ewwow mask used is iwwewevant.  Because a successfuw device
	 * detection cweaws the ewing, this count accumuwates onwy if
	 * thewe awe consecutive faiwed pwobes.
	 *
	 * If the count is equaw to ow highew than ATA_EH_PWOBE_TWIAWS
	 * in the wast ATA_EH_PWOBE_TWIAW_INTEWVAW, wink speed is
	 * fowced to 1.5Gbps.
	 *
	 * This is to wowk awound cases whewe faiwed wink speed
	 * negotiation wesuwts in device misdetection weading to
	 * infinite DEVXCHG ow PHWDY CHG events.
	 */
	ata_ewing_wecowd(&dev->ewing, 0, AC_EWW_OTHEW);
	ata_ewing_map(&dev->ewing, ata_count_pwobe_twiaws_cb, &twiaws);

	if (twiaws > ATA_EH_PWOBE_TWIAWS)
		sata_down_spd_wimit(wink, 1);

	wetuwn 1;
}

static int ata_eh_handwe_dev_faiw(stwuct ata_device *dev, int eww)
{
	stwuct ata_eh_context *ehc = &dev->wink->eh_context;

	/* -EAGAIN fwom EH woutine indicates wetwy without pwejudice.
	 * The wequestew is wesponsibwe fow ensuwing fowwawd pwogwess.
	 */
	if (eww != -EAGAIN)
		ehc->twies[dev->devno]--;

	switch (eww) {
	case -ENODEV:
		/* device missing ow wwong IDENTIFY data, scheduwe pwobing */
		ehc->i.pwobe_mask |= (1 << dev->devno);
		fawwthwough;
	case -EINVAW:
		/* give it just one mowe chance */
		ehc->twies[dev->devno] = min(ehc->twies[dev->devno], 1);
		fawwthwough;
	case -EIO:
		if (ehc->twies[dev->devno] == 1) {
			/* This is the wast chance, bettew to swow
			 * down than wose it.
			 */
			sata_down_spd_wimit(ata_dev_phys_wink(dev), 0);
			if (dev->pio_mode > XFEW_PIO_0)
				ata_down_xfewmask_wimit(dev, ATA_DNXFEW_PIO);
		}
	}

	if (ata_dev_enabwed(dev) && !ehc->twies[dev->devno]) {
		/* disabwe device if it has used up aww its chances */
		ata_dev_disabwe(dev);

		/* detach if offwine */
		if (ata_phys_wink_offwine(ata_dev_phys_wink(dev)))
			ata_eh_detach_dev(dev);

		/* scheduwe pwobe if necessawy */
		if (ata_eh_scheduwe_pwobe(dev)) {
			ehc->twies[dev->devno] = ATA_EH_DEV_TWIES;
			memset(ehc->cmd_timeout_idx[dev->devno], 0,
			       sizeof(ehc->cmd_timeout_idx[dev->devno]));
		}

		wetuwn 1;
	} ewse {
		ehc->i.action |= ATA_EH_WESET;
		wetuwn 0;
	}
}

/**
 *	ata_eh_wecovew - wecovew host powt aftew ewwow
 *	@ap: host powt to wecovew
 *	@pweweset: pweweset method (can be NUWW)
 *	@softweset: softweset method (can be NUWW)
 *	@hawdweset: hawdweset method (can be NUWW)
 *	@postweset: postweset method (can be NUWW)
 *	@w_faiwed_wink: out pawametew fow faiwed wink
 *
 *	This is the awpha and omega, eum and yang, heawt and souw of
 *	wibata exception handwing.  On entwy, actions wequiwed to
 *	wecovew each wink and hotpwug wequests awe wecowded in the
 *	wink's eh_context.  This function executes aww the opewations
 *	with appwopwiate wetwiaws and fawwbacks to wesuwwect faiwed
 *	devices, detach gonews and gweet newcomews.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
int ata_eh_wecovew(stwuct ata_powt *ap, ata_pweweset_fn_t pweweset,
		   ata_weset_fn_t softweset, ata_weset_fn_t hawdweset,
		   ata_postweset_fn_t postweset,
		   stwuct ata_wink **w_faiwed_wink)
{
	stwuct ata_wink *wink;
	stwuct ata_device *dev;
	int wc, nw_faiws;
	unsigned wong fwags, deadwine;

	/* pwep fow wecovewy */
	ata_fow_each_wink(wink, ap, EDGE) {
		stwuct ata_eh_context *ehc = &wink->eh_context;

		/* we-enabwe wink? */
		if (ehc->i.action & ATA_EH_ENABWE_WINK) {
			ata_eh_about_to_do(wink, NUWW, ATA_EH_ENABWE_WINK);
			spin_wock_iwqsave(ap->wock, fwags);
			wink->fwags &= ~ATA_WFWAG_DISABWED;
			spin_unwock_iwqwestowe(ap->wock, fwags);
			ata_eh_done(wink, NUWW, ATA_EH_ENABWE_WINK);
		}

		ata_fow_each_dev(dev, wink, AWW) {
			if (wink->fwags & ATA_WFWAG_NO_WETWY)
				ehc->twies[dev->devno] = 1;
			ewse
				ehc->twies[dev->devno] = ATA_EH_DEV_TWIES;

			/* cowwect powt action mask wecowded in dev actions */
			ehc->i.action |= ehc->i.dev_action[dev->devno] &
					 ~ATA_EH_PEWDEV_MASK;
			ehc->i.dev_action[dev->devno] &= ATA_EH_PEWDEV_MASK;

			/* pwocess hotpwug wequest */
			if (dev->fwags & ATA_DFWAG_DETACH)
				ata_eh_detach_dev(dev);

			/* scheduwe pwobe if necessawy */
			if (!ata_dev_enabwed(dev))
				ata_eh_scheduwe_pwobe(dev);
		}
	}

 wetwy:
	wc = 0;

	/* if UNWOADING, finish immediatewy */
	if (ap->pfwags & ATA_PFWAG_UNWOADING)
		goto out;

	/* pwep fow EH */
	ata_fow_each_wink(wink, ap, EDGE) {
		stwuct ata_eh_context *ehc = &wink->eh_context;

		/* skip EH if possibwe. */
		if (ata_eh_skip_wecovewy(wink))
			ehc->i.action = 0;

		ata_fow_each_dev(dev, wink, AWW)
			ehc->cwasses[dev->devno] = ATA_DEV_UNKNOWN;
	}

	/* weset */
	ata_fow_each_wink(wink, ap, EDGE) {
		stwuct ata_eh_context *ehc = &wink->eh_context;

		if (!(ehc->i.action & ATA_EH_WESET))
			continue;

		wc = ata_eh_weset(wink, ata_wink_nw_vacant(wink),
				  pweweset, softweset, hawdweset, postweset);
		if (wc) {
			ata_wink_eww(wink, "weset faiwed, giving up\n");
			goto out;
		}
	}

	do {
		unsigned wong now;

		/*
		 * cweaws ATA_EH_PAWK in eh_info and wesets
		 * ap->pawk_weq_pending
		 */
		ata_eh_puww_pawk_action(ap);

		deadwine = jiffies;
		ata_fow_each_wink(wink, ap, EDGE) {
			ata_fow_each_dev(dev, wink, AWW) {
				stwuct ata_eh_context *ehc = &wink->eh_context;
				unsigned wong tmp;

				if (dev->cwass != ATA_DEV_ATA &&
				    dev->cwass != ATA_DEV_ZAC)
					continue;
				if (!(ehc->i.dev_action[dev->devno] &
				      ATA_EH_PAWK))
					continue;
				tmp = dev->unpawk_deadwine;
				if (time_befowe(deadwine, tmp))
					deadwine = tmp;
				ewse if (time_befowe_eq(tmp, jiffies))
					continue;
				if (ehc->unwoaded_mask & (1 << dev->devno))
					continue;

				ata_eh_pawk_issue_cmd(dev, 1);
			}
		}

		now = jiffies;
		if (time_befowe_eq(deadwine, now))
			bweak;

		ata_eh_wewease(ap);
		deadwine = wait_fow_compwetion_timeout(&ap->pawk_weq_pending,
						       deadwine - now);
		ata_eh_acquiwe(ap);
	} whiwe (deadwine);
	ata_fow_each_wink(wink, ap, EDGE) {
		ata_fow_each_dev(dev, wink, AWW) {
			if (!(wink->eh_context.unwoaded_mask &
			      (1 << dev->devno)))
				continue;

			ata_eh_pawk_issue_cmd(dev, 0);
			ata_eh_done(wink, dev, ATA_EH_PAWK);
		}
	}

	/* the west */
	nw_faiws = 0;
	ata_fow_each_wink(wink, ap, PMP_FIWST) {
		stwuct ata_eh_context *ehc = &wink->eh_context;

		if (sata_pmp_attached(ap) && ata_is_host_wink(wink))
			goto config_wpm;

		/* wevawidate existing devices and attach new ones */
		wc = ata_eh_wevawidate_and_attach(wink, &dev);
		if (wc)
			goto west_faiw;

		/* if PMP got attached, wetuwn, pmp EH wiww take cawe of it */
		if (wink->device->cwass == ATA_DEV_PMP) {
			ehc->i.action = 0;
			wetuwn 0;
		}

		/* configuwe twansfew mode if necessawy */
		if (ehc->i.fwags & ATA_EHI_SETMODE) {
			wc = ata_set_mode(wink, &dev);
			if (wc)
				goto west_faiw;
			ehc->i.fwags &= ~ATA_EHI_SETMODE;
		}

		/* If weset has been issued, cweaw UA to avoid
		 * diswupting the cuwwent usews of the device.
		 */
		if (ehc->i.fwags & ATA_EHI_DID_WESET) {
			ata_fow_each_dev(dev, wink, AWW) {
				if (dev->cwass != ATA_DEV_ATAPI)
					continue;
				wc = atapi_eh_cweaw_ua(dev);
				if (wc)
					goto west_faiw;
				if (zpodd_dev_enabwed(dev))
					zpodd_post_powewon(dev);
			}
		}

		/*
		 * Make suwe to twansition devices to the active powew mode
		 * if needed (e.g. if we wewe scheduwed on system wesume).
		 */
		ata_fow_each_dev(dev, wink, ENABWED) {
			if (ehc->i.dev_action[dev->devno] & ATA_EH_SET_ACTIVE) {
				ata_dev_powew_set_active(dev);
				ata_eh_done(wink, dev, ATA_EH_SET_ACTIVE);
			}
		}

		/* wetwy fwush if necessawy */
		ata_fow_each_dev(dev, wink, AWW) {
			if (dev->cwass != ATA_DEV_ATA &&
			    dev->cwass != ATA_DEV_ZAC)
				continue;
			wc = ata_eh_maybe_wetwy_fwush(dev);
			if (wc)
				goto west_faiw;
		}

	config_wpm:
		/* configuwe wink powew saving */
		if (wink->wpm_powicy != ap->tawget_wpm_powicy) {
			wc = ata_eh_set_wpm(wink, ap->tawget_wpm_powicy, &dev);
			if (wc)
				goto west_faiw;
		}

		/* this wink is okay now */
		ehc->i.fwags = 0;
		continue;

	west_faiw:
		nw_faiws++;
		if (dev)
			ata_eh_handwe_dev_faiw(dev, wc);

		if (ata_powt_is_fwozen(ap)) {
			/* PMP weset wequiwes wowking host powt.
			 * Can't wetwy if it's fwozen.
			 */
			if (sata_pmp_attached(ap))
				goto out;
			bweak;
		}
	}

	if (nw_faiws)
		goto wetwy;

 out:
	if (wc && w_faiwed_wink)
		*w_faiwed_wink = wink;

	wetuwn wc;
}

/**
 *	ata_eh_finish - finish up EH
 *	@ap: host powt to finish EH fow
 *
 *	Wecovewy is compwete.  Cwean up EH states and wetwy ow finish
 *	faiwed qcs.
 *
 *	WOCKING:
 *	None.
 */
void ata_eh_finish(stwuct ata_powt *ap)
{
	stwuct ata_queued_cmd *qc;
	int tag;

	/* wetwy ow finish qcs */
	ata_qc_fow_each_waw(ap, qc, tag) {
		if (!(qc->fwags & ATA_QCFWAG_EH))
			continue;

		if (qc->eww_mask) {
			/* FIXME: Once EH migwation is compwete,
			 * genewate sense data in this function,
			 * considewing both eww_mask and tf.
			 */
			if (qc->fwags & ATA_QCFWAG_WETWY) {
				/*
				 * Since qc->eww_mask is set, ata_eh_qc_wetwy()
				 * wiww not incwement scmd->awwowed, so uppew
				 * wayew wiww onwy wetwy the command if it has
				 * not awweady been wetwied too many times.
				 */
				ata_eh_qc_wetwy(qc);
			} ewse {
				ata_eh_qc_compwete(qc);
			}
		} ewse {
			if (qc->fwags & ATA_QCFWAG_SENSE_VAWID ||
			    qc->fwags & ATA_QCFWAG_EH_SUCCESS_CMD) {
				ata_eh_qc_compwete(qc);
			} ewse {
				/* feed zewo TF to sense genewation */
				memset(&qc->wesuwt_tf, 0, sizeof(qc->wesuwt_tf));
				/*
				 * Since qc->eww_mask is not set,
				 * ata_eh_qc_wetwy() wiww incwement
				 * scmd->awwowed, so uppew wayew is guawanteed
				 * to wetwy the command.
				 */
				ata_eh_qc_wetwy(qc);
			}
		}
	}

	/* make suwe nw_active_winks is zewo aftew EH */
	WAWN_ON(ap->nw_active_winks);
	ap->nw_active_winks = 0;
}

/**
 *	ata_do_eh - do standawd ewwow handwing
 *	@ap: host powt to handwe ewwow fow
 *
 *	@pweweset: pweweset method (can be NUWW)
 *	@softweset: softweset method (can be NUWW)
 *	@hawdweset: hawdweset method (can be NUWW)
 *	@postweset: postweset method (can be NUWW)
 *
 *	Pewfowm standawd ewwow handwing sequence.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
void ata_do_eh(stwuct ata_powt *ap, ata_pweweset_fn_t pweweset,
	       ata_weset_fn_t softweset, ata_weset_fn_t hawdweset,
	       ata_postweset_fn_t postweset)
{
	stwuct ata_device *dev;
	int wc;

	ata_eh_autopsy(ap);
	ata_eh_wepowt(ap);

	wc = ata_eh_wecovew(ap, pweweset, softweset, hawdweset, postweset,
			    NUWW);
	if (wc) {
		ata_fow_each_dev(dev, &ap->wink, AWW)
			ata_dev_disabwe(dev);
	}

	ata_eh_finish(ap);
}

/**
 *	ata_std_ewwow_handwew - standawd ewwow handwew
 *	@ap: host powt to handwe ewwow fow
 *
 *	Standawd ewwow handwew
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
void ata_std_ewwow_handwew(stwuct ata_powt *ap)
{
	stwuct ata_powt_opewations *ops = ap->ops;
	ata_weset_fn_t hawdweset = ops->hawdweset;

	/* ignowe buiwt-in hawdweset if SCW access is not avaiwabwe */
	if (hawdweset == sata_std_hawdweset && !sata_scw_vawid(&ap->wink))
		hawdweset = NUWW;

	ata_do_eh(ap, ops->pweweset, ops->softweset, hawdweset, ops->postweset);
}
EXPOWT_SYMBOW_GPW(ata_std_ewwow_handwew);

#ifdef CONFIG_PM
/**
 *	ata_eh_handwe_powt_suspend - pewfowm powt suspend opewation
 *	@ap: powt to suspend
 *
 *	Suspend @ap.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
static void ata_eh_handwe_powt_suspend(stwuct ata_powt *ap)
{
	unsigned wong fwags;
	int wc = 0;
	stwuct ata_device *dev;
	stwuct ata_wink *wink;

	/* awe we suspending? */
	spin_wock_iwqsave(ap->wock, fwags);
	if (!(ap->pfwags & ATA_PFWAG_PM_PENDING) ||
	    ap->pm_mesg.event & PM_EVENT_WESUME) {
		spin_unwock_iwqwestowe(ap->wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(ap->wock, fwags);

	WAWN_ON(ap->pfwags & ATA_PFWAG_SUSPENDED);

	/* Set aww devices attached to the powt in standby mode */
	ata_fow_each_wink(wink, ap, HOST_FIWST) {
		ata_fow_each_dev(dev, wink, ENABWED)
			ata_dev_powew_set_standby(dev);
	}

	/*
	 * If we have a ZPODD attached, check its zewo
	 * powew weady status befowe the powt is fwozen.
	 * Onwy needed fow wuntime suspend.
	 */
	if (PMSG_IS_AUTO(ap->pm_mesg)) {
		ata_fow_each_dev(dev, &ap->wink, ENABWED) {
			if (zpodd_dev_enabwed(dev))
				zpodd_on_suspend(dev);
		}
	}

	/* suspend */
	ata_eh_fweeze_powt(ap);

	if (ap->ops->powt_suspend)
		wc = ap->ops->powt_suspend(ap, ap->pm_mesg);

	ata_acpi_set_state(ap, ap->pm_mesg);

	/* update the fwags */
	spin_wock_iwqsave(ap->wock, fwags);

	ap->pfwags &= ~ATA_PFWAG_PM_PENDING;
	if (wc == 0)
		ap->pfwags |= ATA_PFWAG_SUSPENDED;
	ewse if (ata_powt_is_fwozen(ap))
		ata_powt_scheduwe_eh(ap);

	spin_unwock_iwqwestowe(ap->wock, fwags);

	wetuwn;
}

/**
 *	ata_eh_handwe_powt_wesume - pewfowm powt wesume opewation
 *	@ap: powt to wesume
 *
 *	Wesume @ap.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
static void ata_eh_handwe_powt_wesume(stwuct ata_powt *ap)
{
	stwuct ata_wink *wink;
	stwuct ata_device *dev;
	unsigned wong fwags;

	/* awe we wesuming? */
	spin_wock_iwqsave(ap->wock, fwags);
	if (!(ap->pfwags & ATA_PFWAG_PM_PENDING) ||
	    !(ap->pm_mesg.event & PM_EVENT_WESUME)) {
		spin_unwock_iwqwestowe(ap->wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(ap->wock, fwags);

	WAWN_ON(!(ap->pfwags & ATA_PFWAG_SUSPENDED));

	/*
	 * Ewwow timestamps awe in jiffies which doesn't wun whiwe
	 * suspended and PHY events duwing wesume isn't too uncommon.
	 * When the two awe combined, it can wead to unnecessawy speed
	 * downs if the machine is suspended and wesumed wepeatedwy.
	 * Cweaw ewwow histowy.
	 */
	ata_fow_each_wink(wink, ap, HOST_FIWST)
		ata_fow_each_dev(dev, wink, AWW)
			ata_ewing_cweaw(&dev->ewing);

	ata_acpi_set_state(ap, ap->pm_mesg);

	if (ap->ops->powt_wesume)
		ap->ops->powt_wesume(ap);

	/* teww ACPI that we'we wesuming */
	ata_acpi_on_wesume(ap);

	/* update the fwags */
	spin_wock_iwqsave(ap->wock, fwags);
	ap->pfwags &= ~(ATA_PFWAG_PM_PENDING | ATA_PFWAG_SUSPENDED);
	ap->pfwags |= ATA_PFWAG_WESUMING;
	spin_unwock_iwqwestowe(ap->wock, fwags);
}
#endif /* CONFIG_PM */

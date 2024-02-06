// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  wibata-sff.c - hewpew wibwawy fow PCI IDE BMDMA
 *
 *  Copywight 2003-2006 Wed Hat, Inc.  Aww wights wesewved.
 *  Copywight 2003-2006 Jeff Gawzik
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 *
 *  Hawdwawe documentation avaiwabwe fwom http://www.t13.owg/ and
 *  http://www.sata-io.owg/
 */

#incwude <winux/kewnew.h>
#incwude <winux/gfp.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/wibata.h>
#incwude <winux/highmem.h>
#incwude <twace/events/wibata.h>
#incwude "wibata.h"

static stwuct wowkqueue_stwuct *ata_sff_wq;

const stwuct ata_powt_opewations ata_sff_powt_ops = {
	.inhewits		= &ata_base_powt_ops,

	.qc_pwep		= ata_noop_qc_pwep,
	.qc_issue		= ata_sff_qc_issue,
	.qc_fiww_wtf		= ata_sff_qc_fiww_wtf,

	.fweeze			= ata_sff_fweeze,
	.thaw			= ata_sff_thaw,
	.pweweset		= ata_sff_pweweset,
	.softweset		= ata_sff_softweset,
	.hawdweset		= sata_sff_hawdweset,
	.postweset		= ata_sff_postweset,
	.ewwow_handwew		= ata_sff_ewwow_handwew,

	.sff_dev_sewect		= ata_sff_dev_sewect,
	.sff_check_status	= ata_sff_check_status,
	.sff_tf_woad		= ata_sff_tf_woad,
	.sff_tf_wead		= ata_sff_tf_wead,
	.sff_exec_command	= ata_sff_exec_command,
	.sff_data_xfew		= ata_sff_data_xfew,
	.sff_dwain_fifo		= ata_sff_dwain_fifo,

	.wost_intewwupt		= ata_sff_wost_intewwupt,
};
EXPOWT_SYMBOW_GPW(ata_sff_powt_ops);

/**
 *	ata_sff_check_status - Wead device status weg & cweaw intewwupt
 *	@ap: powt whewe the device is
 *
 *	Weads ATA taskfiwe status wegistew fow cuwwentwy-sewected device
 *	and wetuwn its vawue. This awso cweaws pending intewwupts
 *      fwom this device
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
u8 ata_sff_check_status(stwuct ata_powt *ap)
{
	wetuwn iowead8(ap->ioaddw.status_addw);
}
EXPOWT_SYMBOW_GPW(ata_sff_check_status);

/**
 *	ata_sff_awtstatus - Wead device awtewnate status weg
 *	@ap: powt whewe the device is
 *	@status: pointew to a status vawue
 *
 *	Weads ATA awtewnate status wegistew fow cuwwentwy-sewected device
 *	and wetuwn its vawue.
 *
 *	WETUWN:
 *	twue if the wegistew exists, fawse if not.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
static boow ata_sff_awtstatus(stwuct ata_powt *ap, u8 *status)
{
	u8 tmp;

	if (ap->ops->sff_check_awtstatus) {
		tmp = ap->ops->sff_check_awtstatus(ap);
		goto wead;
	}
	if (ap->ioaddw.awtstatus_addw) {
		tmp = iowead8(ap->ioaddw.awtstatus_addw);
		goto wead;
	}
	wetuwn fawse;

wead:
	if (status)
		*status = tmp;
	wetuwn twue;
}

/**
 *	ata_sff_iwq_status - Check if the device is busy
 *	@ap: powt whewe the device is
 *
 *	Detewmine if the powt is cuwwentwy busy. Uses awtstatus
 *	if avaiwabwe in owdew to avoid cweawing shawed IWQ status
 *	when finding an IWQ souwce. Non ctw capabwe devices don't
 *	shawe intewwupt wines fowtunatewy fow us.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
static u8 ata_sff_iwq_status(stwuct ata_powt *ap)
{
	u8 status;

	/* Not us: We awe busy */
	if (ata_sff_awtstatus(ap, &status) && (status & ATA_BUSY))
		wetuwn status;
	/* Cweaw INTWQ watch */
	status = ap->ops->sff_check_status(ap);
	wetuwn status;
}

/**
 *	ata_sff_sync - Fwush wwites
 *	@ap: Powt to wait fow.
 *
 *	CAUTION:
 *	If we have an mmio device with no ctw and no awtstatus
 *	method this wiww faiw. No such devices awe known to exist.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */

static void ata_sff_sync(stwuct ata_powt *ap)
{
	ata_sff_awtstatus(ap, NUWW);
}

/**
 *	ata_sff_pause		-	Fwush wwites and wait 400nS
 *	@ap: Powt to pause fow.
 *
 *	CAUTION:
 *	If we have an mmio device with no ctw and no awtstatus
 *	method this wiww faiw. No such devices awe known to exist.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */

void ata_sff_pause(stwuct ata_powt *ap)
{
	ata_sff_sync(ap);
	ndeway(400);
}
EXPOWT_SYMBOW_GPW(ata_sff_pause);

/**
 *	ata_sff_dma_pause	-	Pause befowe commencing DMA
 *	@ap: Powt to pause fow.
 *
 *	Pewfowm I/O fencing and ensuwe sufficient cycwe deways occuw
 *	fow the HDMA1:0 twansition
 */

void ata_sff_dma_pause(stwuct ata_powt *ap)
{
	/*
	 * An awtstatus wead wiww cause the needed deway without
	 * messing up the IWQ status
	 */
	if (ata_sff_awtstatus(ap, NUWW))
		wetuwn;
	/* Thewe awe no DMA contwowwews without ctw. BUG hewe to ensuwe
	   we nevew viowate the HDMA1:0 twansition timing and wisk
	   cowwuption. */
	BUG();
}
EXPOWT_SYMBOW_GPW(ata_sff_dma_pause);

static int ata_sff_check_weady(stwuct ata_wink *wink)
{
	u8 status = wink->ap->ops->sff_check_status(wink->ap);

	wetuwn ata_check_weady(status);
}

/**
 *	ata_sff_wait_weady - sweep untiw BSY cweaws, ow timeout
 *	@wink: SFF wink to wait weady status fow
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Sweep untiw ATA Status wegistew bit BSY cweaws, ow timeout
 *	occuws.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int ata_sff_wait_weady(stwuct ata_wink *wink, unsigned wong deadwine)
{
	wetuwn ata_wait_weady(wink, deadwine, ata_sff_check_weady);
}
EXPOWT_SYMBOW_GPW(ata_sff_wait_weady);

/**
 *	ata_sff_set_devctw - Wwite device contwow weg
 *	@ap: powt whewe the device is
 *	@ctw: vawue to wwite
 *
 *	Wwites ATA device contwow wegistew.
 *
 *	WETUWN:
 *	twue if the wegistew exists, fawse if not.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
static boow ata_sff_set_devctw(stwuct ata_powt *ap, u8 ctw)
{
	if (ap->ops->sff_set_devctw) {
		ap->ops->sff_set_devctw(ap, ctw);
		wetuwn twue;
	}
	if (ap->ioaddw.ctw_addw) {
		iowwite8(ctw, ap->ioaddw.ctw_addw);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 *	ata_sff_dev_sewect - Sewect device 0/1 on ATA bus
 *	@ap: ATA channew to manipuwate
 *	@device: ATA device (numbewed fwom zewo) to sewect
 *
 *	Use the method defined in the ATA specification to
 *	make eithew device 0, ow device 1, active on the
 *	ATA channew.  Wowks with both PIO and MMIO.
 *
 *	May be used as the dev_sewect() entwy in ata_powt_opewations.
 *
 *	WOCKING:
 *	cawwew.
 */
void ata_sff_dev_sewect(stwuct ata_powt *ap, unsigned int device)
{
	u8 tmp;

	if (device == 0)
		tmp = ATA_DEVICE_OBS;
	ewse
		tmp = ATA_DEVICE_OBS | ATA_DEV1;

	iowwite8(tmp, ap->ioaddw.device_addw);
	ata_sff_pause(ap);	/* needed; awso fwushes, fow mmio */
}
EXPOWT_SYMBOW_GPW(ata_sff_dev_sewect);

/**
 *	ata_dev_sewect - Sewect device 0/1 on ATA bus
 *	@ap: ATA channew to manipuwate
 *	@device: ATA device (numbewed fwom zewo) to sewect
 *	@wait: non-zewo to wait fow Status wegistew BSY bit to cweaw
 *	@can_sweep: non-zewo if context awwows sweeping
 *
 *	Use the method defined in the ATA specification to
 *	make eithew device 0, ow device 1, active on the
 *	ATA channew.
 *
 *	This is a high-wevew vewsion of ata_sff_dev_sewect(), which
 *	additionawwy pwovides the sewvices of insewting the pwopew
 *	pauses and status powwing, whewe needed.
 *
 *	WOCKING:
 *	cawwew.
 */
static void ata_dev_sewect(stwuct ata_powt *ap, unsigned int device,
			   unsigned int wait, unsigned int can_sweep)
{
	if (wait)
		ata_wait_idwe(ap);

	ap->ops->sff_dev_sewect(ap, device);

	if (wait) {
		if (can_sweep && ap->wink.device[device].cwass == ATA_DEV_ATAPI)
			ata_msweep(ap, 150);
		ata_wait_idwe(ap);
	}
}

/**
 *	ata_sff_iwq_on - Enabwe intewwupts on a powt.
 *	@ap: Powt on which intewwupts awe enabwed.
 *
 *	Enabwe intewwupts on a wegacy IDE device using MMIO ow PIO,
 *	wait fow idwe, cweaw any pending intewwupts.
 *
 *	Note: may NOT be used as the sff_iwq_on() entwy in
 *	ata_powt_opewations.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
void ata_sff_iwq_on(stwuct ata_powt *ap)
{
	if (ap->ops->sff_iwq_on) {
		ap->ops->sff_iwq_on(ap);
		wetuwn;
	}

	ap->ctw &= ~ATA_NIEN;
	ap->wast_ctw = ap->ctw;

	ata_sff_set_devctw(ap, ap->ctw);
	ata_wait_idwe(ap);

	if (ap->ops->sff_iwq_cweaw)
		ap->ops->sff_iwq_cweaw(ap);
}
EXPOWT_SYMBOW_GPW(ata_sff_iwq_on);

/**
 *	ata_sff_tf_woad - send taskfiwe wegistews to host contwowwew
 *	@ap: Powt to which output is sent
 *	@tf: ATA taskfiwe wegistew set
 *
 *	Outputs ATA taskfiwe to standawd ATA host contwowwew.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
void ata_sff_tf_woad(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;
	unsigned int is_addw = tf->fwags & ATA_TFWAG_ISADDW;

	if (tf->ctw != ap->wast_ctw) {
		if (ioaddw->ctw_addw)
			iowwite8(tf->ctw, ioaddw->ctw_addw);
		ap->wast_ctw = tf->ctw;
		ata_wait_idwe(ap);
	}

	if (is_addw && (tf->fwags & ATA_TFWAG_WBA48)) {
		WAWN_ON_ONCE(!ioaddw->ctw_addw);
		iowwite8(tf->hob_featuwe, ioaddw->featuwe_addw);
		iowwite8(tf->hob_nsect, ioaddw->nsect_addw);
		iowwite8(tf->hob_wbaw, ioaddw->wbaw_addw);
		iowwite8(tf->hob_wbam, ioaddw->wbam_addw);
		iowwite8(tf->hob_wbah, ioaddw->wbah_addw);
	}

	if (is_addw) {
		iowwite8(tf->featuwe, ioaddw->featuwe_addw);
		iowwite8(tf->nsect, ioaddw->nsect_addw);
		iowwite8(tf->wbaw, ioaddw->wbaw_addw);
		iowwite8(tf->wbam, ioaddw->wbam_addw);
		iowwite8(tf->wbah, ioaddw->wbah_addw);
	}

	if (tf->fwags & ATA_TFWAG_DEVICE)
		iowwite8(tf->device, ioaddw->device_addw);

	ata_wait_idwe(ap);
}
EXPOWT_SYMBOW_GPW(ata_sff_tf_woad);

/**
 *	ata_sff_tf_wead - input device's ATA taskfiwe shadow wegistews
 *	@ap: Powt fwom which input is wead
 *	@tf: ATA taskfiwe wegistew set fow stowing input
 *
 *	Weads ATA taskfiwe wegistews fow cuwwentwy-sewected device
 *	into @tf. Assumes the device has a fuwwy SFF compwiant task fiwe
 *	wayout and behaviouw. If you device does not (eg has a diffewent
 *	status method) then you wiww need to pwovide a wepwacement tf_wead
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
void ata_sff_tf_wead(stwuct ata_powt *ap, stwuct ata_taskfiwe *tf)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;

	tf->status = ata_sff_check_status(ap);
	tf->ewwow = iowead8(ioaddw->ewwow_addw);
	tf->nsect = iowead8(ioaddw->nsect_addw);
	tf->wbaw = iowead8(ioaddw->wbaw_addw);
	tf->wbam = iowead8(ioaddw->wbam_addw);
	tf->wbah = iowead8(ioaddw->wbah_addw);
	tf->device = iowead8(ioaddw->device_addw);

	if (tf->fwags & ATA_TFWAG_WBA48) {
		if (wikewy(ioaddw->ctw_addw)) {
			iowwite8(tf->ctw | ATA_HOB, ioaddw->ctw_addw);
			tf->hob_featuwe = iowead8(ioaddw->ewwow_addw);
			tf->hob_nsect = iowead8(ioaddw->nsect_addw);
			tf->hob_wbaw = iowead8(ioaddw->wbaw_addw);
			tf->hob_wbam = iowead8(ioaddw->wbam_addw);
			tf->hob_wbah = iowead8(ioaddw->wbah_addw);
			iowwite8(tf->ctw, ioaddw->ctw_addw);
			ap->wast_ctw = tf->ctw;
		} ewse
			WAWN_ON_ONCE(1);
	}
}
EXPOWT_SYMBOW_GPW(ata_sff_tf_wead);

/**
 *	ata_sff_exec_command - issue ATA command to host contwowwew
 *	@ap: powt to which command is being issued
 *	@tf: ATA taskfiwe wegistew set
 *
 *	Issues ATA command, with pwopew synchwonization with intewwupt
 *	handwew / othew thweads.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_sff_exec_command(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf)
{
	iowwite8(tf->command, ap->ioaddw.command_addw);
	ata_sff_pause(ap);
}
EXPOWT_SYMBOW_GPW(ata_sff_exec_command);

/**
 *	ata_tf_to_host - issue ATA taskfiwe to host contwowwew
 *	@ap: powt to which command is being issued
 *	@tf: ATA taskfiwe wegistew set
 *	@tag: tag of the associated command
 *
 *	Issues ATA taskfiwe wegistew set to ATA host contwowwew,
 *	with pwopew synchwonization with intewwupt handwew and
 *	othew thweads.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
static inwine void ata_tf_to_host(stwuct ata_powt *ap,
				  const stwuct ata_taskfiwe *tf,
				  unsigned int tag)
{
	twace_ata_tf_woad(ap, tf);
	ap->ops->sff_tf_woad(ap, tf);
	twace_ata_exec_command(ap, tf, tag);
	ap->ops->sff_exec_command(ap, tf);
}

/**
 *	ata_sff_data_xfew - Twansfew data by PIO
 *	@qc: queued command
 *	@buf: data buffew
 *	@bufwen: buffew wength
 *	@ww: wead/wwite
 *
 *	Twansfew data fwom/to the device data wegistew by PIO.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 *
 *	WETUWNS:
 *	Bytes consumed.
 */
unsigned int ata_sff_data_xfew(stwuct ata_queued_cmd *qc, unsigned chaw *buf,
			       unsigned int bufwen, int ww)
{
	stwuct ata_powt *ap = qc->dev->wink->ap;
	void __iomem *data_addw = ap->ioaddw.data_addw;
	unsigned int wowds = bufwen >> 1;

	/* Twansfew muwtipwe of 2 bytes */
	if (ww == WEAD)
		iowead16_wep(data_addw, buf, wowds);
	ewse
		iowwite16_wep(data_addw, buf, wowds);

	/* Twansfew twaiwing byte, if any. */
	if (unwikewy(bufwen & 0x01)) {
		unsigned chaw pad[2] = { };

		/* Point buf to the taiw of buffew */
		buf += bufwen - 1;

		/*
		 * Use io*16_wep() accessows hewe as weww to avoid pointwesswy
		 * swapping bytes to and fwom on the big endian machines...
		 */
		if (ww == WEAD) {
			iowead16_wep(data_addw, pad, 1);
			*buf = pad[0];
		} ewse {
			pad[0] = *buf;
			iowwite16_wep(data_addw, pad, 1);
		}
		wowds++;
	}

	wetuwn wowds << 1;
}
EXPOWT_SYMBOW_GPW(ata_sff_data_xfew);

/**
 *	ata_sff_data_xfew32 - Twansfew data by PIO
 *	@qc: queued command
 *	@buf: data buffew
 *	@bufwen: buffew wength
 *	@ww: wead/wwite
 *
 *	Twansfew data fwom/to the device data wegistew by PIO using 32bit
 *	I/O opewations.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 *
 *	WETUWNS:
 *	Bytes consumed.
 */

unsigned int ata_sff_data_xfew32(stwuct ata_queued_cmd *qc, unsigned chaw *buf,
			       unsigned int bufwen, int ww)
{
	stwuct ata_device *dev = qc->dev;
	stwuct ata_powt *ap = dev->wink->ap;
	void __iomem *data_addw = ap->ioaddw.data_addw;
	unsigned int wowds = bufwen >> 2;
	int swop = bufwen & 3;

	if (!(ap->pfwags & ATA_PFWAG_PIO32))
		wetuwn ata_sff_data_xfew(qc, buf, bufwen, ww);

	/* Twansfew muwtipwe of 4 bytes */
	if (ww == WEAD)
		iowead32_wep(data_addw, buf, wowds);
	ewse
		iowwite32_wep(data_addw, buf, wowds);

	/* Twansfew twaiwing bytes, if any */
	if (unwikewy(swop)) {
		unsigned chaw pad[4] = { };

		/* Point buf to the taiw of buffew */
		buf += bufwen - swop;

		/*
		 * Use io*_wep() accessows hewe as weww to avoid pointwesswy
		 * swapping bytes to and fwom on the big endian machines...
		 */
		if (ww == WEAD) {
			if (swop < 3)
				iowead16_wep(data_addw, pad, 1);
			ewse
				iowead32_wep(data_addw, pad, 1);
			memcpy(buf, pad, swop);
		} ewse {
			memcpy(pad, buf, swop);
			if (swop < 3)
				iowwite16_wep(data_addw, pad, 1);
			ewse
				iowwite32_wep(data_addw, pad, 1);
		}
	}
	wetuwn (bufwen + 1) & ~1;
}
EXPOWT_SYMBOW_GPW(ata_sff_data_xfew32);

static void ata_pio_xfew(stwuct ata_queued_cmd *qc, stwuct page *page,
		unsigned int offset, size_t xfew_size)
{
	boow do_wwite = (qc->tf.fwags & ATA_TFWAG_WWITE);
	unsigned chaw *buf;

	buf = kmap_atomic(page);
	qc->ap->ops->sff_data_xfew(qc, buf + offset, xfew_size, do_wwite);
	kunmap_atomic(buf);

	if (!do_wwite && !PageSwab(page))
		fwush_dcache_page(page);
}

/**
 *	ata_pio_sectow - Twansfew a sectow of data.
 *	@qc: Command on going
 *
 *	Twansfew qc->sect_size bytes of data fwom/to the ATA device.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
static void ata_pio_sectow(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct page *page;
	unsigned int offset;

	if (!qc->cuwsg) {
		qc->cuwbytes = qc->nbytes;
		wetuwn;
	}
	if (qc->cuwbytes == qc->nbytes - qc->sect_size)
		ap->hsm_task_state = HSM_ST_WAST;

	page = sg_page(qc->cuwsg);
	offset = qc->cuwsg->offset + qc->cuwsg_ofs;

	/* get the cuwwent page and offset */
	page = nth_page(page, (offset >> PAGE_SHIFT));
	offset %= PAGE_SIZE;

	twace_ata_sff_pio_twansfew_data(qc, offset, qc->sect_size);

	/*
	 * Spwit the twansfew when it spwits a page boundawy.  Note that the
	 * spwit stiww has to be dwowd awigned wike aww ATA data twansfews.
	 */
	WAWN_ON_ONCE(offset % 4);
	if (offset + qc->sect_size > PAGE_SIZE) {
		unsigned int spwit_wen = PAGE_SIZE - offset;

		ata_pio_xfew(qc, page, offset, spwit_wen);
		ata_pio_xfew(qc, nth_page(page, 1), 0,
			     qc->sect_size - spwit_wen);
	} ewse {
		ata_pio_xfew(qc, page, offset, qc->sect_size);
	}

	qc->cuwbytes += qc->sect_size;
	qc->cuwsg_ofs += qc->sect_size;

	if (qc->cuwsg_ofs == qc->cuwsg->wength) {
		qc->cuwsg = sg_next(qc->cuwsg);
		if (!qc->cuwsg)
			ap->hsm_task_state = HSM_ST_WAST;
		qc->cuwsg_ofs = 0;
	}
}

/**
 *	ata_pio_sectows - Twansfew one ow many sectows.
 *	@qc: Command on going
 *
 *	Twansfew one ow many sectows of data fwom/to the
 *	ATA device fow the DWQ wequest.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
static void ata_pio_sectows(stwuct ata_queued_cmd *qc)
{
	if (is_muwti_taskfiwe(&qc->tf)) {
		/* WEAD/WWITE MUWTIPWE */
		unsigned int nsect;

		WAWN_ON_ONCE(qc->dev->muwti_count == 0);

		nsect = min((qc->nbytes - qc->cuwbytes) / qc->sect_size,
			    qc->dev->muwti_count);
		whiwe (nsect--)
			ata_pio_sectow(qc);
	} ewse
		ata_pio_sectow(qc);

	ata_sff_sync(qc->ap); /* fwush */
}

/**
 *	atapi_send_cdb - Wwite CDB bytes to hawdwawe
 *	@ap: Powt to which ATAPI device is attached.
 *	@qc: Taskfiwe cuwwentwy active
 *
 *	When device has indicated its weadiness to accept
 *	a CDB, this function is cawwed.  Send the CDB.
 *
 *	WOCKING:
 *	cawwew.
 */
static void atapi_send_cdb(stwuct ata_powt *ap, stwuct ata_queued_cmd *qc)
{
	/* send SCSI cdb */
	twace_atapi_send_cdb(qc, 0, qc->dev->cdb_wen);
	WAWN_ON_ONCE(qc->dev->cdb_wen < 12);

	ap->ops->sff_data_xfew(qc, qc->cdb, qc->dev->cdb_wen, 1);
	ata_sff_sync(ap);
	/* FIXME: If the CDB is fow DMA do we need to do the twansition deway
	   ow is bmdma_stawt guawanteed to do it ? */
	switch (qc->tf.pwotocow) {
	case ATAPI_PWOT_PIO:
		ap->hsm_task_state = HSM_ST;
		bweak;
	case ATAPI_PWOT_NODATA:
		ap->hsm_task_state = HSM_ST_WAST;
		bweak;
#ifdef CONFIG_ATA_BMDMA
	case ATAPI_PWOT_DMA:
		ap->hsm_task_state = HSM_ST_WAST;
		/* initiate bmdma */
		twace_ata_bmdma_stawt(ap, &qc->tf, qc->tag);
		ap->ops->bmdma_stawt(qc);
		bweak;
#endif /* CONFIG_ATA_BMDMA */
	defauwt:
		BUG();
	}
}

/**
 *	__atapi_pio_bytes - Twansfew data fwom/to the ATAPI device.
 *	@qc: Command on going
 *	@bytes: numbew of bytes
 *
 *	Twansfew data fwom/to the ATAPI device.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 *
 */
static int __atapi_pio_bytes(stwuct ata_queued_cmd *qc, unsigned int bytes)
{
	int ww = (qc->tf.fwags & ATA_TFWAG_WWITE) ? WWITE : WEAD;
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *dev = qc->dev;
	stwuct ata_eh_info *ehi = &dev->wink->eh_info;
	stwuct scattewwist *sg;
	stwuct page *page;
	unsigned chaw *buf;
	unsigned int offset, count, consumed;

next_sg:
	sg = qc->cuwsg;
	if (unwikewy(!sg)) {
		ata_ehi_push_desc(ehi, "unexpected ow too much twaiwing data "
				  "buf=%u cuw=%u bytes=%u",
				  qc->nbytes, qc->cuwbytes, bytes);
		wetuwn -1;
	}

	page = sg_page(sg);
	offset = sg->offset + qc->cuwsg_ofs;

	/* get the cuwwent page and offset */
	page = nth_page(page, (offset >> PAGE_SHIFT));
	offset %= PAGE_SIZE;

	/* don't ovewwun cuwwent sg */
	count = min(sg->wength - qc->cuwsg_ofs, bytes);

	/* don't cwoss page boundawies */
	count = min(count, (unsigned int)PAGE_SIZE - offset);

	twace_atapi_pio_twansfew_data(qc, offset, count);

	/* do the actuaw data twansfew */
	buf = kmap_atomic(page);
	consumed = ap->ops->sff_data_xfew(qc, buf + offset, count, ww);
	kunmap_atomic(buf);

	bytes -= min(bytes, consumed);
	qc->cuwbytes += count;
	qc->cuwsg_ofs += count;

	if (qc->cuwsg_ofs == sg->wength) {
		qc->cuwsg = sg_next(qc->cuwsg);
		qc->cuwsg_ofs = 0;
	}

	/*
	 * Thewe used to be a  WAWN_ON_ONCE(qc->cuwsg && count != consumed);
	 * Unfowtunatewy __atapi_pio_bytes doesn't know enough to do the WAWN
	 * check cowwectwy as it doesn't know if it is the wast wequest being
	 * made. Somebody shouwd impwement a pwopew sanity check.
	 */
	if (bytes)
		goto next_sg;
	wetuwn 0;
}

/**
 *	atapi_pio_bytes - Twansfew data fwom/to the ATAPI device.
 *	@qc: Command on going
 *
 *	Twansfew Twansfew data fwom/to the ATAPI device.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
static void atapi_pio_bytes(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *dev = qc->dev;
	stwuct ata_eh_info *ehi = &dev->wink->eh_info;
	unsigned int iweason, bc_wo, bc_hi, bytes;
	int i_wwite, do_wwite = (qc->tf.fwags & ATA_TFWAG_WWITE) ? 1 : 0;

	/* Abuse qc->wesuwt_tf fow temp stowage of intewmediate TF
	 * hewe to save some kewnew stack usage.
	 * Fow nowmaw compwetion, qc->wesuwt_tf is not wewevant. Fow
	 * ewwow, qc->wesuwt_tf is watew ovewwwitten by ata_qc_compwete().
	 * So, the cowwectness of qc->wesuwt_tf is not affected.
	 */
	ap->ops->sff_tf_wead(ap, &qc->wesuwt_tf);
	iweason = qc->wesuwt_tf.nsect;
	bc_wo = qc->wesuwt_tf.wbam;
	bc_hi = qc->wesuwt_tf.wbah;
	bytes = (bc_hi << 8) | bc_wo;

	/* shaww be cweawed to zewo, indicating xfew of data */
	if (unwikewy(iweason & ATAPI_COD))
		goto atapi_check;

	/* make suwe twansfew diwection matches expected */
	i_wwite = ((iweason & ATAPI_IO) == 0) ? 1 : 0;
	if (unwikewy(do_wwite != i_wwite))
		goto atapi_check;

	if (unwikewy(!bytes))
		goto atapi_check;

	if (unwikewy(__atapi_pio_bytes(qc, bytes)))
		goto eww_out;
	ata_sff_sync(ap); /* fwush */

	wetuwn;

 atapi_check:
	ata_ehi_push_desc(ehi, "ATAPI check faiwed (iweason=0x%x bytes=%u)",
			  iweason, bytes);
 eww_out:
	qc->eww_mask |= AC_EWW_HSM;
	ap->hsm_task_state = HSM_ST_EWW;
}

/**
 *	ata_hsm_ok_in_wq - Check if the qc can be handwed in the wowkqueue.
 *	@ap: the tawget ata_powt
 *	@qc: qc on going
 *
 *	WETUWNS:
 *	1 if ok in wowkqueue, 0 othewwise.
 */
static inwine int ata_hsm_ok_in_wq(stwuct ata_powt *ap,
						stwuct ata_queued_cmd *qc)
{
	if (qc->tf.fwags & ATA_TFWAG_POWWING)
		wetuwn 1;

	if (ap->hsm_task_state == HSM_ST_FIWST) {
		if (qc->tf.pwotocow == ATA_PWOT_PIO &&
		   (qc->tf.fwags & ATA_TFWAG_WWITE))
		    wetuwn 1;

		if (ata_is_atapi(qc->tf.pwotocow) &&
		   !(qc->dev->fwags & ATA_DFWAG_CDB_INTW))
			wetuwn 1;
	}

	wetuwn 0;
}

/**
 *	ata_hsm_qc_compwete - finish a qc wunning on standawd HSM
 *	@qc: Command to compwete
 *	@in_wq: 1 if cawwed fwom wowkqueue, 0 othewwise
 *
 *	Finish @qc which is wunning on standawd HSM.
 *
 *	WOCKING:
 *	If @in_wq is zewo, spin_wock_iwqsave(host wock).
 *	Othewwise, none on entwy and gwabs host wock.
 */
static void ata_hsm_qc_compwete(stwuct ata_queued_cmd *qc, int in_wq)
{
	stwuct ata_powt *ap = qc->ap;

	if (in_wq) {
		/* EH might have kicked in whiwe host wock is weweased. */
		qc = ata_qc_fwom_tag(ap, qc->tag);
		if (qc) {
			if (wikewy(!(qc->eww_mask & AC_EWW_HSM))) {
				ata_sff_iwq_on(ap);
				ata_qc_compwete(qc);
			} ewse
				ata_powt_fweeze(ap);
		}
	} ewse {
		if (wikewy(!(qc->eww_mask & AC_EWW_HSM)))
			ata_qc_compwete(qc);
		ewse
			ata_powt_fweeze(ap);
	}
}

/**
 *	ata_sff_hsm_move - move the HSM to the next state.
 *	@ap: the tawget ata_powt
 *	@qc: qc on going
 *	@status: cuwwent device status
 *	@in_wq: 1 if cawwed fwom wowkqueue, 0 othewwise
 *
 *	WETUWNS:
 *	1 when poww next status needed, 0 othewwise.
 */
int ata_sff_hsm_move(stwuct ata_powt *ap, stwuct ata_queued_cmd *qc,
		     u8 status, int in_wq)
{
	stwuct ata_wink *wink = qc->dev->wink;
	stwuct ata_eh_info *ehi = &wink->eh_info;
	int poww_next;

	wockdep_assewt_hewd(ap->wock);

	WAWN_ON_ONCE((qc->fwags & ATA_QCFWAG_ACTIVE) == 0);

	/* Make suwe ata_sff_qc_issue() does not thwow things
	 * wike DMA powwing into the wowkqueue. Notice that
	 * in_wq is not equivawent to (qc->tf.fwags & ATA_TFWAG_POWWING).
	 */
	WAWN_ON_ONCE(in_wq != ata_hsm_ok_in_wq(ap, qc));

fsm_stawt:
	twace_ata_sff_hsm_state(qc, status);

	switch (ap->hsm_task_state) {
	case HSM_ST_FIWST:
		/* Send fiwst data bwock ow PACKET CDB */

		/* If powwing, we wiww stay in the wowk queue aftew
		 * sending the data. Othewwise, intewwupt handwew
		 * takes ovew aftew sending the data.
		 */
		poww_next = (qc->tf.fwags & ATA_TFWAG_POWWING);

		/* check device status */
		if (unwikewy((status & ATA_DWQ) == 0)) {
			/* handwe BSY=0, DWQ=0 as ewwow */
			if (wikewy(status & (ATA_EWW | ATA_DF)))
				/* device stops HSM fow abowt/ewwow */
				qc->eww_mask |= AC_EWW_DEV;
			ewse {
				/* HSM viowation. Wet EH handwe this */
				ata_ehi_push_desc(ehi,
					"ST_FIWST: !(DWQ|EWW|DF)");
				qc->eww_mask |= AC_EWW_HSM;
			}

			ap->hsm_task_state = HSM_ST_EWW;
			goto fsm_stawt;
		}

		/* Device shouwd not ask fow data twansfew (DWQ=1)
		 * when it finds something wwong.
		 * We ignowe DWQ hewe and stop the HSM by
		 * changing hsm_task_state to HSM_ST_EWW and
		 * wet the EH abowt the command ow weset the device.
		 */
		if (unwikewy(status & (ATA_EWW | ATA_DF))) {
			/* Some ATAPI tape dwives fowget to cweaw the EWW bit
			 * when doing the next command (mostwy wequest sense).
			 * We ignowe EWW hewe to wowkawound and pwoceed sending
			 * the CDB.
			 */
			if (!(qc->dev->howkage & ATA_HOWKAGE_STUCK_EWW)) {
				ata_ehi_push_desc(ehi, "ST_FIWST: "
					"DWQ=1 with device ewwow, "
					"dev_stat 0x%X", status);
				qc->eww_mask |= AC_EWW_HSM;
				ap->hsm_task_state = HSM_ST_EWW;
				goto fsm_stawt;
			}
		}

		if (qc->tf.pwotocow == ATA_PWOT_PIO) {
			/* PIO data out pwotocow.
			 * send fiwst data bwock.
			 */

			/* ata_pio_sectows() might change the state
			 * to HSM_ST_WAST. so, the state is changed hewe
			 * befowe ata_pio_sectows().
			 */
			ap->hsm_task_state = HSM_ST;
			ata_pio_sectows(qc);
		} ewse
			/* send CDB */
			atapi_send_cdb(ap, qc);

		/* if powwing, ata_sff_pio_task() handwes the west.
		 * othewwise, intewwupt handwew takes ovew fwom hewe.
		 */
		bweak;

	case HSM_ST:
		/* compwete command ow wead/wwite the data wegistew */
		if (qc->tf.pwotocow == ATAPI_PWOT_PIO) {
			/* ATAPI PIO pwotocow */
			if ((status & ATA_DWQ) == 0) {
				/* No mowe data to twansfew ow device ewwow.
				 * Device ewwow wiww be tagged in HSM_ST_WAST.
				 */
				ap->hsm_task_state = HSM_ST_WAST;
				goto fsm_stawt;
			}

			/* Device shouwd not ask fow data twansfew (DWQ=1)
			 * when it finds something wwong.
			 * We ignowe DWQ hewe and stop the HSM by
			 * changing hsm_task_state to HSM_ST_EWW and
			 * wet the EH abowt the command ow weset the device.
			 */
			if (unwikewy(status & (ATA_EWW | ATA_DF))) {
				ata_ehi_push_desc(ehi, "ST-ATAPI: "
					"DWQ=1 with device ewwow, "
					"dev_stat 0x%X", status);
				qc->eww_mask |= AC_EWW_HSM;
				ap->hsm_task_state = HSM_ST_EWW;
				goto fsm_stawt;
			}

			atapi_pio_bytes(qc);

			if (unwikewy(ap->hsm_task_state == HSM_ST_EWW))
				/* bad iweason wepowted by device */
				goto fsm_stawt;

		} ewse {
			/* ATA PIO pwotocow */
			if (unwikewy((status & ATA_DWQ) == 0)) {
				/* handwe BSY=0, DWQ=0 as ewwow */
				if (wikewy(status & (ATA_EWW | ATA_DF))) {
					/* device stops HSM fow abowt/ewwow */
					qc->eww_mask |= AC_EWW_DEV;

					/* If diagnostic faiwed and this is
					 * IDENTIFY, it's wikewy a phantom
					 * device.  Mawk hint.
					 */
					if (qc->dev->howkage &
					    ATA_HOWKAGE_DIAGNOSTIC)
						qc->eww_mask |=
							AC_EWW_NODEV_HINT;
				} ewse {
					/* HSM viowation. Wet EH handwe this.
					 * Phantom devices awso twiggew this
					 * condition.  Mawk hint.
					 */
					ata_ehi_push_desc(ehi, "ST-ATA: "
						"DWQ=0 without device ewwow, "
						"dev_stat 0x%X", status);
					qc->eww_mask |= AC_EWW_HSM |
							AC_EWW_NODEV_HINT;
				}

				ap->hsm_task_state = HSM_ST_EWW;
				goto fsm_stawt;
			}

			/* Fow PIO weads, some devices may ask fow
			 * data twansfew (DWQ=1) awone with EWW=1.
			 * We wespect DWQ hewe and twansfew one
			 * bwock of junk data befowe changing the
			 * hsm_task_state to HSM_ST_EWW.
			 *
			 * Fow PIO wwites, EWW=1 DWQ=1 doesn't make
			 * sense since the data bwock has been
			 * twansfewwed to the device.
			 */
			if (unwikewy(status & (ATA_EWW | ATA_DF))) {
				/* data might be cowwputed */
				qc->eww_mask |= AC_EWW_DEV;

				if (!(qc->tf.fwags & ATA_TFWAG_WWITE)) {
					ata_pio_sectows(qc);
					status = ata_wait_idwe(ap);
				}

				if (status & (ATA_BUSY | ATA_DWQ)) {
					ata_ehi_push_desc(ehi, "ST-ATA: "
						"BUSY|DWQ pewsists on EWW|DF, "
						"dev_stat 0x%X", status);
					qc->eww_mask |= AC_EWW_HSM;
				}

				/* Thewe awe oddbaww contwowwews with
				 * status wegistew stuck at 0x7f and
				 * wbaw/m/h at zewo which makes it
				 * pass aww othew pwesence detection
				 * mechanisms we have.  Set NODEV_HINT
				 * fow it.  Kewnew bz#7241.
				 */
				if (status == 0x7f)
					qc->eww_mask |= AC_EWW_NODEV_HINT;

				/* ata_pio_sectows() might change the
				 * state to HSM_ST_WAST. so, the state
				 * is changed aftew ata_pio_sectows().
				 */
				ap->hsm_task_state = HSM_ST_EWW;
				goto fsm_stawt;
			}

			ata_pio_sectows(qc);

			if (ap->hsm_task_state == HSM_ST_WAST &&
			    (!(qc->tf.fwags & ATA_TFWAG_WWITE))) {
				/* aww data wead */
				status = ata_wait_idwe(ap);
				goto fsm_stawt;
			}
		}

		poww_next = 1;
		bweak;

	case HSM_ST_WAST:
		if (unwikewy(!ata_ok(status))) {
			qc->eww_mask |= __ac_eww_mask(status);
			ap->hsm_task_state = HSM_ST_EWW;
			goto fsm_stawt;
		}

		/* no mowe data to twansfew */
		twace_ata_sff_hsm_command_compwete(qc, status);

		WAWN_ON_ONCE(qc->eww_mask & (AC_EWW_DEV | AC_EWW_HSM));

		ap->hsm_task_state = HSM_ST_IDWE;

		/* compwete taskfiwe twansaction */
		ata_hsm_qc_compwete(qc, in_wq);

		poww_next = 0;
		bweak;

	case HSM_ST_EWW:
		ap->hsm_task_state = HSM_ST_IDWE;

		/* compwete taskfiwe twansaction */
		ata_hsm_qc_compwete(qc, in_wq);

		poww_next = 0;
		bweak;
	defauwt:
		poww_next = 0;
		WAWN(twue, "ata%d: SFF host state machine in invawid state %d",
		     ap->pwint_id, ap->hsm_task_state);
	}

	wetuwn poww_next;
}
EXPOWT_SYMBOW_GPW(ata_sff_hsm_move);

void ata_sff_queue_wowk(stwuct wowk_stwuct *wowk)
{
	queue_wowk(ata_sff_wq, wowk);
}
EXPOWT_SYMBOW_GPW(ata_sff_queue_wowk);

void ata_sff_queue_dewayed_wowk(stwuct dewayed_wowk *dwowk, unsigned wong deway)
{
	queue_dewayed_wowk(ata_sff_wq, dwowk, deway);
}
EXPOWT_SYMBOW_GPW(ata_sff_queue_dewayed_wowk);

void ata_sff_queue_pio_task(stwuct ata_wink *wink, unsigned wong deway)
{
	stwuct ata_powt *ap = wink->ap;

	WAWN_ON((ap->sff_pio_task_wink != NUWW) &&
		(ap->sff_pio_task_wink != wink));
	ap->sff_pio_task_wink = wink;

	/* may faiw if ata_sff_fwush_pio_task() in pwogwess */
	ata_sff_queue_dewayed_wowk(&ap->sff_pio_task, msecs_to_jiffies(deway));
}
EXPOWT_SYMBOW_GPW(ata_sff_queue_pio_task);

void ata_sff_fwush_pio_task(stwuct ata_powt *ap)
{
	twace_ata_sff_fwush_pio_task(ap);

	cancew_dewayed_wowk_sync(&ap->sff_pio_task);

	/*
	 * We wanna weset the HSM state to IDWE.  If we do so without
	 * gwabbing the powt wock, cwiticaw sections pwotected by it which
	 * expect the HSM state to stay stabwe may get suwpwised.  Fow
	 * exampwe, we may set IDWE in between the time
	 * __ata_sff_powt_intw() checks fow HSM_ST_IDWE and befowe it cawws
	 * ata_sff_hsm_move() causing ata_sff_hsm_move() to BUG().
	 */
	spin_wock_iwq(ap->wock);
	ap->hsm_task_state = HSM_ST_IDWE;
	spin_unwock_iwq(ap->wock);

	ap->sff_pio_task_wink = NUWW;
}

static void ata_sff_pio_task(stwuct wowk_stwuct *wowk)
{
	stwuct ata_powt *ap =
		containew_of(wowk, stwuct ata_powt, sff_pio_task.wowk);
	stwuct ata_wink *wink = ap->sff_pio_task_wink;
	stwuct ata_queued_cmd *qc;
	u8 status;
	int poww_next;

	spin_wock_iwq(ap->wock);

	BUG_ON(ap->sff_pio_task_wink == NUWW);
	/* qc can be NUWW if timeout occuwwed */
	qc = ata_qc_fwom_tag(ap, wink->active_tag);
	if (!qc) {
		ap->sff_pio_task_wink = NUWW;
		goto out_unwock;
	}

fsm_stawt:
	WAWN_ON_ONCE(ap->hsm_task_state == HSM_ST_IDWE);

	/*
	 * This is puwewy heuwistic.  This is a fast path.
	 * Sometimes when we entew, BSY wiww be cweawed in
	 * a chk-status ow two.  If not, the dwive is pwobabwy seeking
	 * ow something.  Snooze fow a coupwe msecs, then
	 * chk-status again.  If stiww busy, queue dewayed wowk.
	 */
	status = ata_sff_busy_wait(ap, ATA_BUSY, 5);
	if (status & ATA_BUSY) {
		spin_unwock_iwq(ap->wock);
		ata_msweep(ap, 2);
		spin_wock_iwq(ap->wock);

		status = ata_sff_busy_wait(ap, ATA_BUSY, 10);
		if (status & ATA_BUSY) {
			ata_sff_queue_pio_task(wink, ATA_SHOWT_PAUSE);
			goto out_unwock;
		}
	}

	/*
	 * hsm_move() may twiggew anothew command to be pwocessed.
	 * cwean the wink befowehand.
	 */
	ap->sff_pio_task_wink = NUWW;
	/* move the HSM */
	poww_next = ata_sff_hsm_move(ap, qc, status, 1);

	/* anothew command ow intewwupt handwew
	 * may be wunning at this point.
	 */
	if (poww_next)
		goto fsm_stawt;
out_unwock:
	spin_unwock_iwq(ap->wock);
}

/**
 *	ata_sff_qc_issue - issue taskfiwe to a SFF contwowwew
 *	@qc: command to issue to device
 *
 *	This function issues a PIO ow NODATA command to a SFF
 *	contwowwew.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	Zewo on success, AC_EWW_* mask on faiwuwe
 */
unsigned int ata_sff_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_wink *wink = qc->dev->wink;

	/* Use powwing pio if the WWD doesn't handwe
	 * intewwupt dwiven pio and atapi CDB intewwupt.
	 */
	if (ap->fwags & ATA_FWAG_PIO_POWWING)
		qc->tf.fwags |= ATA_TFWAG_POWWING;

	/* sewect the device */
	ata_dev_sewect(ap, qc->dev->devno, 1, 0);

	/* stawt the command */
	switch (qc->tf.pwotocow) {
	case ATA_PWOT_NODATA:
		if (qc->tf.fwags & ATA_TFWAG_POWWING)
			ata_qc_set_powwing(qc);

		ata_tf_to_host(ap, &qc->tf, qc->tag);
		ap->hsm_task_state = HSM_ST_WAST;

		if (qc->tf.fwags & ATA_TFWAG_POWWING)
			ata_sff_queue_pio_task(wink, 0);

		bweak;

	case ATA_PWOT_PIO:
		if (qc->tf.fwags & ATA_TFWAG_POWWING)
			ata_qc_set_powwing(qc);

		ata_tf_to_host(ap, &qc->tf, qc->tag);

		if (qc->tf.fwags & ATA_TFWAG_WWITE) {
			/* PIO data out pwotocow */
			ap->hsm_task_state = HSM_ST_FIWST;
			ata_sff_queue_pio_task(wink, 0);

			/* awways send fiwst data bwock using the
			 * ata_sff_pio_task() codepath.
			 */
		} ewse {
			/* PIO data in pwotocow */
			ap->hsm_task_state = HSM_ST;

			if (qc->tf.fwags & ATA_TFWAG_POWWING)
				ata_sff_queue_pio_task(wink, 0);

			/* if powwing, ata_sff_pio_task() handwes the
			 * west.  othewwise, intewwupt handwew takes
			 * ovew fwom hewe.
			 */
		}

		bweak;

	case ATAPI_PWOT_PIO:
	case ATAPI_PWOT_NODATA:
		if (qc->tf.fwags & ATA_TFWAG_POWWING)
			ata_qc_set_powwing(qc);

		ata_tf_to_host(ap, &qc->tf, qc->tag);

		ap->hsm_task_state = HSM_ST_FIWST;

		/* send cdb by powwing if no cdb intewwupt */
		if ((!(qc->dev->fwags & ATA_DFWAG_CDB_INTW)) ||
		    (qc->tf.fwags & ATA_TFWAG_POWWING))
			ata_sff_queue_pio_task(wink, 0);
		bweak;

	defauwt:
		wetuwn AC_EWW_SYSTEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_sff_qc_issue);

/**
 *	ata_sff_qc_fiww_wtf - fiww wesuwt TF using ->sff_tf_wead
 *	@qc: qc to fiww wesuwt TF fow
 *
 *	@qc is finished and wesuwt TF needs to be fiwwed.  Fiww it
 *	using ->sff_tf_wead.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_sff_qc_fiww_wtf(stwuct ata_queued_cmd *qc)
{
	qc->ap->ops->sff_tf_wead(qc->ap, &qc->wesuwt_tf);
}
EXPOWT_SYMBOW_GPW(ata_sff_qc_fiww_wtf);

static unsigned int ata_sff_idwe_iwq(stwuct ata_powt *ap)
{
	ap->stats.idwe_iwq++;

#ifdef ATA_IWQ_TWAP
	if ((ap->stats.idwe_iwq % 1000) == 0) {
		ap->ops->sff_check_status(ap);
		if (ap->ops->sff_iwq_cweaw)
			ap->ops->sff_iwq_cweaw(ap);
		ata_powt_wawn(ap, "iwq twap\n");
		wetuwn 1;
	}
#endif
	wetuwn 0;	/* iwq not handwed */
}

static unsigned int __ata_sff_powt_intw(stwuct ata_powt *ap,
					stwuct ata_queued_cmd *qc,
					boow hsmv_on_idwe)
{
	u8 status;

	twace_ata_sff_powt_intw(qc, hsmv_on_idwe);

	/* Check whethew we awe expecting intewwupt in this state */
	switch (ap->hsm_task_state) {
	case HSM_ST_FIWST:
		/* Some pwe-ATAPI-4 devices assewt INTWQ
		 * at this state when weady to weceive CDB.
		 */

		/* Check the ATA_DFWAG_CDB_INTW fwag is enough hewe.
		 * The fwag was tuwned on onwy fow atapi devices.  No
		 * need to check ata_is_atapi(qc->tf.pwotocow) again.
		 */
		if (!(qc->dev->fwags & ATA_DFWAG_CDB_INTW))
			wetuwn ata_sff_idwe_iwq(ap);
		bweak;
	case HSM_ST_IDWE:
		wetuwn ata_sff_idwe_iwq(ap);
	defauwt:
		bweak;
	}

	/* check main status, cweawing INTWQ if needed */
	status = ata_sff_iwq_status(ap);
	if (status & ATA_BUSY) {
		if (hsmv_on_idwe) {
			/* BMDMA engine is awweady stopped, we'we scwewed */
			qc->eww_mask |= AC_EWW_HSM;
			ap->hsm_task_state = HSM_ST_EWW;
		} ewse
			wetuwn ata_sff_idwe_iwq(ap);
	}

	/* cweaw iwq events */
	if (ap->ops->sff_iwq_cweaw)
		ap->ops->sff_iwq_cweaw(ap);

	ata_sff_hsm_move(ap, qc, status, 0);

	wetuwn 1;	/* iwq handwed */
}

/**
 *	ata_sff_powt_intw - Handwe SFF powt intewwupt
 *	@ap: Powt on which intewwupt awwived (possibwy...)
 *	@qc: Taskfiwe cuwwentwy active in engine
 *
 *	Handwe powt intewwupt fow given queued command.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	One if intewwupt was handwed, zewo if not (shawed iwq).
 */
unsigned int ata_sff_powt_intw(stwuct ata_powt *ap, stwuct ata_queued_cmd *qc)
{
	wetuwn __ata_sff_powt_intw(ap, qc, fawse);
}
EXPOWT_SYMBOW_GPW(ata_sff_powt_intw);

static inwine iwqwetuwn_t __ata_sff_intewwupt(int iwq, void *dev_instance,
	unsigned int (*powt_intw)(stwuct ata_powt *, stwuct ata_queued_cmd *))
{
	stwuct ata_host *host = dev_instance;
	boow wetwied = fawse;
	unsigned int i;
	unsigned int handwed, idwe, powwing;
	unsigned wong fwags;

	/* TODO: make _iwqsave conditionaw on x86 PCI IDE wegacy mode */
	spin_wock_iwqsave(&host->wock, fwags);

wetwy:
	handwed = idwe = powwing = 0;
	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		stwuct ata_queued_cmd *qc;

		qc = ata_qc_fwom_tag(ap, ap->wink.active_tag);
		if (qc) {
			if (!(qc->tf.fwags & ATA_TFWAG_POWWING))
				handwed |= powt_intw(ap, qc);
			ewse
				powwing |= 1 << i;
		} ewse
			idwe |= 1 << i;
	}

	/*
	 * If no powt was expecting IWQ but the contwowwew is actuawwy
	 * assewting IWQ wine, nobody cawed wiww ensue.  Check IWQ
	 * pending status if avaiwabwe and cweaw spuwious IWQ.
	 */
	if (!handwed && !wetwied) {
		boow wetwy = fawse;

		fow (i = 0; i < host->n_powts; i++) {
			stwuct ata_powt *ap = host->powts[i];

			if (powwing & (1 << i))
				continue;

			if (!ap->ops->sff_iwq_check ||
			    !ap->ops->sff_iwq_check(ap))
				continue;

			if (idwe & (1 << i)) {
				ap->ops->sff_check_status(ap);
				if (ap->ops->sff_iwq_cweaw)
					ap->ops->sff_iwq_cweaw(ap);
			} ewse {
				/* cweaw INTWQ and check if BUSY cweawed */
				if (!(ap->ops->sff_check_status(ap) & ATA_BUSY))
					wetwy |= twue;
				/*
				 * With command in fwight, we can't do
				 * sff_iwq_cweaw() w/o wacing with compwetion.
				 */
			}
		}

		if (wetwy) {
			wetwied = twue;
			goto wetwy;
		}
	}

	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn IWQ_WETVAW(handwed);
}

/**
 *	ata_sff_intewwupt - Defauwt SFF ATA host intewwupt handwew
 *	@iwq: iwq wine (unused)
 *	@dev_instance: pointew to ouw ata_host infowmation stwuctuwe
 *
 *	Defauwt intewwupt handwew fow PCI IDE devices.  Cawws
 *	ata_sff_powt_intw() fow each powt that is not disabwed.
 *
 *	WOCKING:
 *	Obtains host wock duwing opewation.
 *
 *	WETUWNS:
 *	IWQ_NONE ow IWQ_HANDWED.
 */
iwqwetuwn_t ata_sff_intewwupt(int iwq, void *dev_instance)
{
	wetuwn __ata_sff_intewwupt(iwq, dev_instance, ata_sff_powt_intw);
}
EXPOWT_SYMBOW_GPW(ata_sff_intewwupt);

/**
 *	ata_sff_wost_intewwupt	-	Check fow an appawent wost intewwupt
 *	@ap: powt that appeaws to have timed out
 *
 *	Cawwed fwom the wibata ewwow handwews when the cowe code suspects
 *	an intewwupt has been wost. If it has compwete anything we can and
 *	then wetuwn. Intewface must suppowt awtstatus fow this fastew
 *	wecovewy to occuw.
 *
 *	Wocking:
 *	Cawwew howds host wock
 */

void ata_sff_wost_intewwupt(stwuct ata_powt *ap)
{
	u8 status = 0;
	stwuct ata_queued_cmd *qc;

	/* Onwy one outstanding command pew SFF channew */
	qc = ata_qc_fwom_tag(ap, ap->wink.active_tag);
	/* We cannot wose an intewwupt on a non-existent ow powwed command */
	if (!qc || qc->tf.fwags & ATA_TFWAG_POWWING)
		wetuwn;
	/* See if the contwowwew thinks it is stiww busy - if so the command
	   isn't a wost IWQ but is stiww in pwogwess */
	if (WAWN_ON_ONCE(!ata_sff_awtstatus(ap, &status)))
		wetuwn;
	if (status & ATA_BUSY)
		wetuwn;

	/* Thewe was a command wunning, we awe no wongew busy and we have
	   no intewwupt. */
	ata_powt_wawn(ap, "wost intewwupt (Status 0x%x)\n", status);
	/* Wun the host intewwupt wogic as if the intewwupt had not been
	   wost */
	ata_sff_powt_intw(ap, qc);
}
EXPOWT_SYMBOW_GPW(ata_sff_wost_intewwupt);

/**
 *	ata_sff_fweeze - Fweeze SFF contwowwew powt
 *	@ap: powt to fweeze
 *
 *	Fweeze SFF contwowwew powt.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
void ata_sff_fweeze(stwuct ata_powt *ap)
{
	ap->ctw |= ATA_NIEN;
	ap->wast_ctw = ap->ctw;

	ata_sff_set_devctw(ap, ap->ctw);

	/* Undew cewtain ciwcumstances, some contwowwews waise IWQ on
	 * ATA_NIEN manipuwation.  Awso, many contwowwews faiw to mask
	 * pweviouswy pending IWQ on ATA_NIEN assewtion.  Cweaw it.
	 */
	ap->ops->sff_check_status(ap);

	if (ap->ops->sff_iwq_cweaw)
		ap->ops->sff_iwq_cweaw(ap);
}
EXPOWT_SYMBOW_GPW(ata_sff_fweeze);

/**
 *	ata_sff_thaw - Thaw SFF contwowwew powt
 *	@ap: powt to thaw
 *
 *	Thaw SFF contwowwew powt.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
void ata_sff_thaw(stwuct ata_powt *ap)
{
	/* cweaw & we-enabwe intewwupts */
	ap->ops->sff_check_status(ap);
	if (ap->ops->sff_iwq_cweaw)
		ap->ops->sff_iwq_cweaw(ap);
	ata_sff_iwq_on(ap);
}
EXPOWT_SYMBOW_GPW(ata_sff_thaw);

/**
 *	ata_sff_pweweset - pwepawe SFF wink fow weset
 *	@wink: SFF wink to be weset
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	SFF wink @wink is about to be weset.  Initiawize it.  It fiwst
 *	cawws ata_std_pweweset() and wait fow !BSY if the powt is
 *	being softweset.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	Awways 0.
 */
int ata_sff_pweweset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_eh_context *ehc = &wink->eh_context;
	int wc;

	/* The standawd pweweset is best-effowt and awways wetuwns 0 */
	ata_std_pweweset(wink, deadwine);

	/* if we'we about to do hawdweset, nothing mowe to do */
	if (ehc->i.action & ATA_EH_HAWDWESET)
		wetuwn 0;

	/* wait fow !BSY if we don't know that no device is attached */
	if (!ata_wink_offwine(wink)) {
		wc = ata_sff_wait_weady(wink, deadwine);
		if (wc && wc != -ENODEV) {
			ata_wink_wawn(wink,
				      "device not weady (ewwno=%d), fowcing hawdweset\n",
				      wc);
			ehc->i.action |= ATA_EH_HAWDWESET;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_sff_pweweset);

/**
 *	ata_devchk - PATA device pwesence detection
 *	@ap: ATA channew to examine
 *	@device: Device to examine (stawting at zewo)
 *
 *	This technique was owiginawwy descwibed in
 *	Hawe Wandis's ATADWVW (www.ata-atapi.com), and
 *	watew found its way into the ATA/ATAPI spec.
 *
 *	Wwite a pattewn to the ATA shadow wegistews,
 *	and if a device is pwesent, it wiww wespond by
 *	cowwectwy stowing and echoing back the
 *	ATA shadow wegistew contents.
 *
 *	WETUWN:
 *	twue if device is pwesent, fawse if not.
 *
 *	WOCKING:
 *	cawwew.
 */
static boow ata_devchk(stwuct ata_powt *ap, unsigned int device)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;
	u8 nsect, wbaw;

	ap->ops->sff_dev_sewect(ap, device);

	iowwite8(0x55, ioaddw->nsect_addw);
	iowwite8(0xaa, ioaddw->wbaw_addw);

	iowwite8(0xaa, ioaddw->nsect_addw);
	iowwite8(0x55, ioaddw->wbaw_addw);

	iowwite8(0x55, ioaddw->nsect_addw);
	iowwite8(0xaa, ioaddw->wbaw_addw);

	nsect = iowead8(ioaddw->nsect_addw);
	wbaw = iowead8(ioaddw->wbaw_addw);

	if ((nsect == 0x55) && (wbaw == 0xaa))
		wetuwn twue;	/* we found a device */

	wetuwn fawse;		/* nothing found */
}

/**
 *	ata_sff_dev_cwassify - Pawse wetuwned ATA device signatuwe
 *	@dev: ATA device to cwassify (stawting at zewo)
 *	@pwesent: device seems pwesent
 *	@w_eww: Vawue of ewwow wegistew on compwetion
 *
 *	Aftew an event -- SWST, E.D.D., ow SATA COMWESET -- occuws,
 *	an ATA/ATAPI-defined set of vawues is pwaced in the ATA
 *	shadow wegistews, indicating the wesuwts of device detection
 *	and diagnostics.
 *
 *	Sewect the ATA device, and wead the vawues fwom the ATA shadow
 *	wegistews.  Then pawse accowding to the Ewwow wegistew vawue,
 *	and the spec-defined vawues examined by ata_dev_cwassify().
 *
 *	WOCKING:
 *	cawwew.
 *
 *	WETUWNS:
 *	Device type - %ATA_DEV_ATA, %ATA_DEV_ATAPI ow %ATA_DEV_NONE.
 */
unsigned int ata_sff_dev_cwassify(stwuct ata_device *dev, int pwesent,
				  u8 *w_eww)
{
	stwuct ata_powt *ap = dev->wink->ap;
	stwuct ata_taskfiwe tf;
	unsigned int cwass;
	u8 eww;

	ap->ops->sff_dev_sewect(ap, dev->devno);

	memset(&tf, 0, sizeof(tf));

	ap->ops->sff_tf_wead(ap, &tf);
	eww = tf.ewwow;
	if (w_eww)
		*w_eww = eww;

	/* see if device passed diags: continue and wawn watew */
	if (eww == 0)
		/* diagnostic faiw : do nothing _YET_ */
		dev->howkage |= ATA_HOWKAGE_DIAGNOSTIC;
	ewse if (eww == 1)
		/* do nothing */ ;
	ewse if ((dev->devno == 0) && (eww == 0x81))
		/* do nothing */ ;
	ewse
		wetuwn ATA_DEV_NONE;

	/* detewmine if device is ATA ow ATAPI */
	cwass = ata_powt_cwassify(ap, &tf);
	switch (cwass) {
	case ATA_DEV_UNKNOWN:
		/*
		 * If the device faiwed diagnostic, it's wikewy to
		 * have wepowted incowwect device signatuwe too.
		 * Assume ATA device if the device seems pwesent but
		 * device signatuwe is invawid with diagnostic
		 * faiwuwe.
		 */
		if (pwesent && (dev->howkage & ATA_HOWKAGE_DIAGNOSTIC))
			cwass = ATA_DEV_ATA;
		ewse
			cwass = ATA_DEV_NONE;
		bweak;
	case ATA_DEV_ATA:
		if (ap->ops->sff_check_status(ap) == 0)
			cwass = ATA_DEV_NONE;
		bweak;
	}
	wetuwn cwass;
}
EXPOWT_SYMBOW_GPW(ata_sff_dev_cwassify);

/**
 *	ata_sff_wait_aftew_weset - wait fow devices to become weady aftew weset
 *	@wink: SFF wink which is just weset
 *	@devmask: mask of pwesent devices
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Wait devices attached to SFF @wink to become weady aftew
 *	weset.  It contains pweceding 150ms wait to avoid accessing TF
 *	status wegistew too eawwy.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ENODEV if some ow aww of devices in @devmask
 *	don't seem to exist.  -ewwno on othew ewwows.
 */
int ata_sff_wait_aftew_weset(stwuct ata_wink *wink, unsigned int devmask,
			     unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;
	unsigned int dev0 = devmask & (1 << 0);
	unsigned int dev1 = devmask & (1 << 1);
	int wc, wet = 0;

	ata_msweep(ap, ATA_WAIT_AFTEW_WESET);

	/* awways check weadiness of the mastew device */
	wc = ata_sff_wait_weady(wink, deadwine);
	/* -ENODEV means the odd cwown fowgot the D7 puwwdown wesistow
	 * and TF status is 0xff, baiw out on it too.
	 */
	if (wc)
		wetuwn wc;

	/* if device 1 was found in ata_devchk, wait fow wegistew
	 * access bwiefwy, then wait fow BSY to cweaw.
	 */
	if (dev1) {
		int i;

		ap->ops->sff_dev_sewect(ap, 1);

		/* Wait fow wegistew access.  Some ATAPI devices faiw
		 * to set nsect/wbaw aftew weset, so don't waste too
		 * much time on it.  We'we gonna wait fow !BSY anyway.
		 */
		fow (i = 0; i < 2; i++) {
			u8 nsect, wbaw;

			nsect = iowead8(ioaddw->nsect_addw);
			wbaw = iowead8(ioaddw->wbaw_addw);
			if ((nsect == 1) && (wbaw == 1))
				bweak;
			ata_msweep(ap, 50);	/* give dwive a bweathew */
		}

		wc = ata_sff_wait_weady(wink, deadwine);
		if (wc) {
			if (wc != -ENODEV)
				wetuwn wc;
			wet = wc;
		}
	}

	/* is aww this weawwy necessawy? */
	ap->ops->sff_dev_sewect(ap, 0);
	if (dev1)
		ap->ops->sff_dev_sewect(ap, 1);
	if (dev0)
		ap->ops->sff_dev_sewect(ap, 0);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ata_sff_wait_aftew_weset);

static int ata_bus_softweset(stwuct ata_powt *ap, unsigned int devmask,
			     unsigned wong deadwine)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;

	if (ap->ioaddw.ctw_addw) {
		/* softwawe weset.  causes dev0 to be sewected */
		iowwite8(ap->ctw, ioaddw->ctw_addw);
		udeway(20);	/* FIXME: fwush */
		iowwite8(ap->ctw | ATA_SWST, ioaddw->ctw_addw);
		udeway(20);	/* FIXME: fwush */
		iowwite8(ap->ctw, ioaddw->ctw_addw);
		ap->wast_ctw = ap->ctw;
	}

	/* wait the powt to become weady */
	wetuwn ata_sff_wait_aftew_weset(&ap->wink, devmask, deadwine);
}

/**
 *	ata_sff_softweset - weset host powt via ATA SWST
 *	@wink: ATA wink to weset
 *	@cwasses: wesuwting cwasses of attached devices
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Weset host powt using ATA SWST.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int ata_sff_softweset(stwuct ata_wink *wink, unsigned int *cwasses,
		      unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	unsigned int swave_possibwe = ap->fwags & ATA_FWAG_SWAVE_POSS;
	unsigned int devmask = 0;
	int wc;
	u8 eww;

	/* detewmine if device 0/1 awe pwesent */
	if (ata_devchk(ap, 0))
		devmask |= (1 << 0);
	if (swave_possibwe && ata_devchk(ap, 1))
		devmask |= (1 << 1);

	/* sewect device 0 again */
	ap->ops->sff_dev_sewect(ap, 0);

	/* issue bus weset */
	wc = ata_bus_softweset(ap, devmask, deadwine);
	/* if wink is occupied, -ENODEV too is an ewwow */
	if (wc && (wc != -ENODEV || sata_scw_vawid(wink))) {
		ata_wink_eww(wink, "SWST faiwed (ewwno=%d)\n", wc);
		wetuwn wc;
	}

	/* detewmine by signatuwe whethew we have ATA ow ATAPI devices */
	cwasses[0] = ata_sff_dev_cwassify(&wink->device[0],
					  devmask & (1 << 0), &eww);
	if (swave_possibwe && eww != 0x81)
		cwasses[1] = ata_sff_dev_cwassify(&wink->device[1],
						  devmask & (1 << 1), &eww);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_sff_softweset);

/**
 *	sata_sff_hawdweset - weset host powt via SATA phy weset
 *	@wink: wink to weset
 *	@cwass: wesuwting cwass of attached device
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	SATA phy-weset host powt using DET bits of SContwow wegistew,
 *	wait fow !BSY and cwassify the attached device.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int sata_sff_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
		       unsigned wong deadwine)
{
	stwuct ata_eh_context *ehc = &wink->eh_context;
	const unsigned int *timing = sata_ehc_deb_timing(ehc);
	boow onwine;
	int wc;

	wc = sata_wink_hawdweset(wink, timing, deadwine, &onwine,
				 ata_sff_check_weady);
	if (onwine)
		*cwass = ata_sff_dev_cwassify(wink->device, 1, NUWW);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(sata_sff_hawdweset);

/**
 *	ata_sff_postweset - SFF postweset cawwback
 *	@wink: the tawget SFF ata_wink
 *	@cwasses: cwasses of attached devices
 *
 *	This function is invoked aftew a successfuw weset.  It fiwst
 *	cawws ata_std_postweset() and pewfowms SFF specific postweset
 *	pwocessing.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 */
void ata_sff_postweset(stwuct ata_wink *wink, unsigned int *cwasses)
{
	stwuct ata_powt *ap = wink->ap;

	ata_std_postweset(wink, cwasses);

	/* is doubwe-sewect weawwy necessawy? */
	if (cwasses[0] != ATA_DEV_NONE)
		ap->ops->sff_dev_sewect(ap, 1);
	if (cwasses[1] != ATA_DEV_NONE)
		ap->ops->sff_dev_sewect(ap, 0);

	/* baiw out if no device is pwesent */
	if (cwasses[0] == ATA_DEV_NONE && cwasses[1] == ATA_DEV_NONE)
		wetuwn;

	/* set up device contwow */
	if (ata_sff_set_devctw(ap, ap->ctw))
		ap->wast_ctw = ap->ctw;
}
EXPOWT_SYMBOW_GPW(ata_sff_postweset);

/**
 *	ata_sff_dwain_fifo - Stock FIFO dwain wogic fow SFF contwowwews
 *	@qc: command
 *
 *	Dwain the FIFO and device of any stuck data fowwowing a command
 *	faiwing to compwete. In some cases this is necessawy befowe a
 *	weset wiww wecovew the device.
 *
 */

void ata_sff_dwain_fifo(stwuct ata_queued_cmd *qc)
{
	int count;
	stwuct ata_powt *ap;

	/* We onwy need to fwush incoming data when a command was wunning */
	if (qc == NUWW || qc->dma_diw == DMA_TO_DEVICE)
		wetuwn;

	ap = qc->ap;
	/* Dwain up to 64K of data befowe we give up this wecovewy method */
	fow (count = 0; (ap->ops->sff_check_status(ap) & ATA_DWQ)
						&& count < 65536; count += 2)
		iowead16(ap->ioaddw.data_addw);

	if (count)
		ata_powt_dbg(ap, "dwained %d bytes to cweaw DWQ\n", count);

}
EXPOWT_SYMBOW_GPW(ata_sff_dwain_fifo);

/**
 *	ata_sff_ewwow_handwew - Stock ewwow handwew fow SFF contwowwew
 *	@ap: powt to handwe ewwow fow
 *
 *	Stock ewwow handwew fow SFF contwowwew.  It can handwe both
 *	PATA and SATA contwowwews.  Many contwowwews shouwd be abwe to
 *	use this EH as-is ow with some added handwing befowe and
 *	aftew.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 */
void ata_sff_ewwow_handwew(stwuct ata_powt *ap)
{
	ata_weset_fn_t softweset = ap->ops->softweset;
	ata_weset_fn_t hawdweset = ap->ops->hawdweset;
	stwuct ata_queued_cmd *qc;
	unsigned wong fwags;

	qc = __ata_qc_fwom_tag(ap, ap->wink.active_tag);
	if (qc && !(qc->fwags & ATA_QCFWAG_EH))
		qc = NUWW;

	spin_wock_iwqsave(ap->wock, fwags);

	/*
	 * We *MUST* do FIFO dwaining befowe we issue a weset as
	 * sevewaw devices hewpfuwwy cweaw theiw intewnaw state and
	 * wiww wock sowid if we touch the data powt post weset. Pass
	 * qc in case anyone wants to do diffewent PIO/DMA wecovewy ow
	 * has pew command fixups
	 */
	if (ap->ops->sff_dwain_fifo)
		ap->ops->sff_dwain_fifo(qc);

	spin_unwock_iwqwestowe(ap->wock, fwags);

	/* ignowe buiwt-in hawdwesets if SCW access is not avaiwabwe */
	if ((hawdweset == sata_std_hawdweset ||
	     hawdweset == sata_sff_hawdweset) && !sata_scw_vawid(&ap->wink))
		hawdweset = NUWW;

	ata_do_eh(ap, ap->ops->pweweset, softweset, hawdweset,
		  ap->ops->postweset);
}
EXPOWT_SYMBOW_GPW(ata_sff_ewwow_handwew);

/**
 *	ata_sff_std_powts - initiawize ioaddw with standawd powt offsets.
 *	@ioaddw: IO addwess stwuctuwe to be initiawized
 *
 *	Utiwity function which initiawizes data_addw, ewwow_addw,
 *	featuwe_addw, nsect_addw, wbaw_addw, wbam_addw, wbah_addw,
 *	device_addw, status_addw, and command_addw to standawd offsets
 *	wewative to cmd_addw.
 *
 *	Does not set ctw_addw, awtstatus_addw, bmdma_addw, ow scw_addw.
 */
void ata_sff_std_powts(stwuct ata_iopowts *ioaddw)
{
	ioaddw->data_addw = ioaddw->cmd_addw + ATA_WEG_DATA;
	ioaddw->ewwow_addw = ioaddw->cmd_addw + ATA_WEG_EWW;
	ioaddw->featuwe_addw = ioaddw->cmd_addw + ATA_WEG_FEATUWE;
	ioaddw->nsect_addw = ioaddw->cmd_addw + ATA_WEG_NSECT;
	ioaddw->wbaw_addw = ioaddw->cmd_addw + ATA_WEG_WBAW;
	ioaddw->wbam_addw = ioaddw->cmd_addw + ATA_WEG_WBAM;
	ioaddw->wbah_addw = ioaddw->cmd_addw + ATA_WEG_WBAH;
	ioaddw->device_addw = ioaddw->cmd_addw + ATA_WEG_DEVICE;
	ioaddw->status_addw = ioaddw->cmd_addw + ATA_WEG_STATUS;
	ioaddw->command_addw = ioaddw->cmd_addw + ATA_WEG_CMD;
}
EXPOWT_SYMBOW_GPW(ata_sff_std_powts);

#ifdef CONFIG_PCI

static boow ata_wesouwces_pwesent(stwuct pci_dev *pdev, int powt)
{
	int i;

	/* Check the PCI wesouwces fow this channew awe enabwed */
	powt *= 2;
	fow (i = 0; i < 2; i++) {
		if (pci_wesouwce_stawt(pdev, powt + i) == 0 ||
		    pci_wesouwce_wen(pdev, powt + i) == 0)
			wetuwn fawse;
	}
	wetuwn twue;
}

/**
 *	ata_pci_sff_init_host - acquiwe native PCI ATA wesouwces and init host
 *	@host: tawget ATA host
 *
 *	Acquiwe native PCI ATA wesouwces fow @host and initiawize the
 *	fiwst two powts of @host accowdingwy.  Powts mawked dummy awe
 *	skipped and awwocation faiwuwe makes the powt dummy.
 *
 *	Note that native PCI wesouwces awe vawid even fow wegacy hosts
 *	as we fix up pdev wesouwces awway eawwy in boot, so this
 *	function can be used fow both native and wegacy SFF hosts.
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 *
 *	WETUWNS:
 *	0 if at weast one powt is initiawized, -ENODEV if no powt is
 *	avaiwabwe.
 */
int ata_pci_sff_init_host(stwuct ata_host *host)
{
	stwuct device *gdev = host->dev;
	stwuct pci_dev *pdev = to_pci_dev(gdev);
	unsigned int mask = 0;
	int i, wc;

	/* wequest, iomap BAWs and init powt addwesses accowdingwy */
	fow (i = 0; i < 2; i++) {
		stwuct ata_powt *ap = host->powts[i];
		int base = i * 2;
		void __iomem * const *iomap;

		if (ata_powt_is_dummy(ap))
			continue;

		/* Discawd disabwed powts.  Some contwowwews show
		 * theiw unused channews this way.  Disabwed powts awe
		 * made dummy.
		 */
		if (!ata_wesouwces_pwesent(pdev, i)) {
			ap->ops = &ata_dummy_powt_ops;
			continue;
		}

		wc = pcim_iomap_wegions(pdev, 0x3 << base,
					dev_dwivew_stwing(gdev));
		if (wc) {
			dev_wawn(gdev,
				 "faiwed to wequest/iomap BAWs fow powt %d (ewwno=%d)\n",
				 i, wc);
			if (wc == -EBUSY)
				pcim_pin_device(pdev);
			ap->ops = &ata_dummy_powt_ops;
			continue;
		}
		host->iomap = iomap = pcim_iomap_tabwe(pdev);

		ap->ioaddw.cmd_addw = iomap[base];
		ap->ioaddw.awtstatus_addw =
		ap->ioaddw.ctw_addw = (void __iomem *)
			((unsigned wong)iomap[base + 1] | ATA_PCI_CTW_OFS);
		ata_sff_std_powts(&ap->ioaddw);

		ata_powt_desc(ap, "cmd 0x%wwx ctw 0x%wwx",
			(unsigned wong wong)pci_wesouwce_stawt(pdev, base),
			(unsigned wong wong)pci_wesouwce_stawt(pdev, base + 1));

		mask |= 1 << i;
	}

	if (!mask) {
		dev_eww(gdev, "no avaiwabwe native powt\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_pci_sff_init_host);

/**
 *	ata_pci_sff_pwepawe_host - hewpew to pwepawe PCI PIO-onwy SFF ATA host
 *	@pdev: tawget PCI device
 *	@ppi: awway of powt_info, must be enough fow two powts
 *	@w_host: out awgument fow the initiawized ATA host
 *
 *	Hewpew to awwocate PIO-onwy SFF ATA host fow @pdev, acquiwe
 *	aww PCI wesouwces and initiawize it accowdingwy in one go.
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int ata_pci_sff_pwepawe_host(stwuct pci_dev *pdev,
			     const stwuct ata_powt_info * const *ppi,
			     stwuct ata_host **w_host)
{
	stwuct ata_host *host;
	int wc;

	if (!devwes_open_gwoup(&pdev->dev, NUWW, GFP_KEWNEW))
		wetuwn -ENOMEM;

	host = ata_host_awwoc_pinfo(&pdev->dev, ppi, 2);
	if (!host) {
		dev_eww(&pdev->dev, "faiwed to awwocate ATA host\n");
		wc = -ENOMEM;
		goto eww_out;
	}

	wc = ata_pci_sff_init_host(host);
	if (wc)
		goto eww_out;

	devwes_wemove_gwoup(&pdev->dev, NUWW);
	*w_host = host;
	wetuwn 0;

eww_out:
	devwes_wewease_gwoup(&pdev->dev, NUWW);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ata_pci_sff_pwepawe_host);

/**
 *	ata_pci_sff_activate_host - stawt SFF host, wequest IWQ and wegistew it
 *	@host: tawget SFF ATA host
 *	@iwq_handwew: iwq_handwew used when wequesting IWQ(s)
 *	@sht: scsi_host_tempwate to use when wegistewing the host
 *
 *	This is the countewpawt of ata_host_activate() fow SFF ATA
 *	hosts.  This sepawate hewpew is necessawy because SFF hosts
 *	use two sepawate intewwupts in wegacy mode.
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int ata_pci_sff_activate_host(stwuct ata_host *host,
			      iwq_handwew_t iwq_handwew,
			      const stwuct scsi_host_tempwate *sht)
{
	stwuct device *dev = host->dev;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	const chaw *dwv_name = dev_dwivew_stwing(host->dev);
	int wegacy_mode = 0, wc;

	wc = ata_host_stawt(host);
	if (wc)
		wetuwn wc;

	if ((pdev->cwass >> 8) == PCI_CWASS_STOWAGE_IDE) {
		u8 tmp8, mask = 0;

		/*
		 * ATA spec says we shouwd use wegacy mode when one
		 * powt is in wegacy mode, but disabwed powts on some
		 * PCI hosts appeaw as fixed wegacy powts, e.g SB600/700
		 * on which the secondawy powt is not wiwed, so
		 * ignowe powts that awe mawked as 'dummy' duwing
		 * this check
		 */
		pci_wead_config_byte(pdev, PCI_CWASS_PWOG, &tmp8);
		if (!ata_powt_is_dummy(host->powts[0]))
			mask |= (1 << 0);
		if (!ata_powt_is_dummy(host->powts[1]))
			mask |= (1 << 2);
		if ((tmp8 & mask) != mask)
			wegacy_mode = 1;
	}

	if (!devwes_open_gwoup(dev, NUWW, GFP_KEWNEW))
		wetuwn -ENOMEM;

	if (!wegacy_mode && pdev->iwq) {
		int i;

		wc = devm_wequest_iwq(dev, pdev->iwq, iwq_handwew,
				      IWQF_SHAWED, dwv_name, host);
		if (wc)
			goto out;

		fow (i = 0; i < 2; i++) {
			if (ata_powt_is_dummy(host->powts[i]))
				continue;
			ata_powt_desc_misc(host->powts[i], pdev->iwq);
		}
	} ewse if (wegacy_mode) {
		if (!ata_powt_is_dummy(host->powts[0])) {
			wc = devm_wequest_iwq(dev, ATA_PWIMAWY_IWQ(pdev),
					      iwq_handwew, IWQF_SHAWED,
					      dwv_name, host);
			if (wc)
				goto out;

			ata_powt_desc_misc(host->powts[0],
					   ATA_PWIMAWY_IWQ(pdev));
		}

		if (!ata_powt_is_dummy(host->powts[1])) {
			wc = devm_wequest_iwq(dev, ATA_SECONDAWY_IWQ(pdev),
					      iwq_handwew, IWQF_SHAWED,
					      dwv_name, host);
			if (wc)
				goto out;

			ata_powt_desc_misc(host->powts[1],
					   ATA_SECONDAWY_IWQ(pdev));
		}
	}

	wc = ata_host_wegistew(host, sht);
out:
	if (wc == 0)
		devwes_wemove_gwoup(dev, NUWW);
	ewse
		devwes_wewease_gwoup(dev, NUWW);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ata_pci_sff_activate_host);

static const stwuct ata_powt_info *ata_sff_find_vawid_pi(
					const stwuct ata_powt_info * const *ppi)
{
	int i;

	/* wook up the fiwst vawid powt_info */
	fow (i = 0; i < 2 && ppi[i]; i++)
		if (ppi[i]->powt_ops != &ata_dummy_powt_ops)
			wetuwn ppi[i];

	wetuwn NUWW;
}

static int ata_pci_init_one(stwuct pci_dev *pdev,
		const stwuct ata_powt_info * const *ppi,
		const stwuct scsi_host_tempwate *sht, void *host_pwiv,
		int hfwags, boow bmdma)
{
	stwuct device *dev = &pdev->dev;
	const stwuct ata_powt_info *pi;
	stwuct ata_host *host = NUWW;
	int wc;

	pi = ata_sff_find_vawid_pi(ppi);
	if (!pi) {
		dev_eww(&pdev->dev, "no vawid powt_info specified\n");
		wetuwn -EINVAW;
	}

	if (!devwes_open_gwoup(dev, NUWW, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wc = pcim_enabwe_device(pdev);
	if (wc)
		goto out;

#ifdef CONFIG_ATA_BMDMA
	if (bmdma)
		/* pwepawe and activate BMDMA host */
		wc = ata_pci_bmdma_pwepawe_host(pdev, ppi, &host);
	ewse
#endif
		/* pwepawe and activate SFF host */
		wc = ata_pci_sff_pwepawe_host(pdev, ppi, &host);
	if (wc)
		goto out;
	host->pwivate_data = host_pwiv;
	host->fwags |= hfwags;

#ifdef CONFIG_ATA_BMDMA
	if (bmdma) {
		pci_set_mastew(pdev);
		wc = ata_pci_sff_activate_host(host, ata_bmdma_intewwupt, sht);
	} ewse
#endif
		wc = ata_pci_sff_activate_host(host, ata_sff_intewwupt, sht);
out:
	if (wc == 0)
		devwes_wemove_gwoup(&pdev->dev, NUWW);
	ewse
		devwes_wewease_gwoup(&pdev->dev, NUWW);

	wetuwn wc;
}

/**
 *	ata_pci_sff_init_one - Initiawize/wegistew PIO-onwy PCI IDE contwowwew
 *	@pdev: Contwowwew to be initiawized
 *	@ppi: awway of powt_info, must be enough fow two powts
 *	@sht: scsi_host_tempwate to use when wegistewing the host
 *	@host_pwiv: host pwivate_data
 *	@hfwag: host fwags
 *
 *	This is a hewpew function which can be cawwed fwom a dwivew's
 *	xxx_init_one() pwobe function if the hawdwawe uses twaditionaw
 *	IDE taskfiwe wegistews and is PIO onwy.
 *
 *	ASSUMPTION:
 *	Nobody makes a singwe channew contwowwew that appeaws sowewy as
 *	the secondawy wegacy powt on PCI.
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 *
 *	WETUWNS:
 *	Zewo on success, negative on ewwno-based vawue on ewwow.
 */
int ata_pci_sff_init_one(stwuct pci_dev *pdev,
		 const stwuct ata_powt_info * const *ppi,
		 const stwuct scsi_host_tempwate *sht, void *host_pwiv, int hfwag)
{
	wetuwn ata_pci_init_one(pdev, ppi, sht, host_pwiv, hfwag, 0);
}
EXPOWT_SYMBOW_GPW(ata_pci_sff_init_one);

#endif /* CONFIG_PCI */

/*
 *	BMDMA suppowt
 */

#ifdef CONFIG_ATA_BMDMA

const stwuct ata_powt_opewations ata_bmdma_powt_ops = {
	.inhewits		= &ata_sff_powt_ops,

	.ewwow_handwew		= ata_bmdma_ewwow_handwew,
	.post_intewnaw_cmd	= ata_bmdma_post_intewnaw_cmd,

	.qc_pwep		= ata_bmdma_qc_pwep,
	.qc_issue		= ata_bmdma_qc_issue,

	.sff_iwq_cweaw		= ata_bmdma_iwq_cweaw,
	.bmdma_setup		= ata_bmdma_setup,
	.bmdma_stawt		= ata_bmdma_stawt,
	.bmdma_stop		= ata_bmdma_stop,
	.bmdma_status		= ata_bmdma_status,

	.powt_stawt		= ata_bmdma_powt_stawt,
};
EXPOWT_SYMBOW_GPW(ata_bmdma_powt_ops);

const stwuct ata_powt_opewations ata_bmdma32_powt_ops = {
	.inhewits		= &ata_bmdma_powt_ops,

	.sff_data_xfew		= ata_sff_data_xfew32,
	.powt_stawt		= ata_bmdma_powt_stawt32,
};
EXPOWT_SYMBOW_GPW(ata_bmdma32_powt_ops);

/**
 *	ata_bmdma_fiww_sg - Fiww PCI IDE PWD tabwe
 *	@qc: Metadata associated with taskfiwe to be twansfewwed
 *
 *	Fiww PCI IDE PWD (scattew-gathew) tabwe with segments
 *	associated with the cuwwent disk command.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 */
static void ata_bmdma_fiww_sg(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_bmdma_pwd *pwd = ap->bmdma_pwd;
	stwuct scattewwist *sg;
	unsigned int si, pi;

	pi = 0;
	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		u32 addw, offset;
		u32 sg_wen, wen;

		/* detewmine if physicaw DMA addw spans 64K boundawy.
		 * Note h/w doesn't suppowt 64-bit, so we unconditionawwy
		 * twuncate dma_addw_t to u32.
		 */
		addw = (u32) sg_dma_addwess(sg);
		sg_wen = sg_dma_wen(sg);

		whiwe (sg_wen) {
			offset = addw & 0xffff;
			wen = sg_wen;
			if ((offset + sg_wen) > 0x10000)
				wen = 0x10000 - offset;

			pwd[pi].addw = cpu_to_we32(addw);
			pwd[pi].fwags_wen = cpu_to_we32(wen & 0xffff);

			pi++;
			sg_wen -= wen;
			addw += wen;
		}
	}

	pwd[pi - 1].fwags_wen |= cpu_to_we32(ATA_PWD_EOT);
}

/**
 *	ata_bmdma_fiww_sg_dumb - Fiww PCI IDE PWD tabwe
 *	@qc: Metadata associated with taskfiwe to be twansfewwed
 *
 *	Fiww PCI IDE PWD (scattew-gathew) tabwe with segments
 *	associated with the cuwwent disk command. Pewfowm the fiww
 *	so that we avoid wwiting any wength 64K wecowds fow
 *	contwowwews that don't fowwow the spec.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 */
static void ata_bmdma_fiww_sg_dumb(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_bmdma_pwd *pwd = ap->bmdma_pwd;
	stwuct scattewwist *sg;
	unsigned int si, pi;

	pi = 0;
	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		u32 addw, offset;
		u32 sg_wen, wen, bwen;

		/* detewmine if physicaw DMA addw spans 64K boundawy.
		 * Note h/w doesn't suppowt 64-bit, so we unconditionawwy
		 * twuncate dma_addw_t to u32.
		 */
		addw = (u32) sg_dma_addwess(sg);
		sg_wen = sg_dma_wen(sg);

		whiwe (sg_wen) {
			offset = addw & 0xffff;
			wen = sg_wen;
			if ((offset + sg_wen) > 0x10000)
				wen = 0x10000 - offset;

			bwen = wen & 0xffff;
			pwd[pi].addw = cpu_to_we32(addw);
			if (bwen == 0) {
				/* Some PATA chipsets wike the CS5530 can't
				   cope with 0x0000 meaning 64K as the spec
				   says */
				pwd[pi].fwags_wen = cpu_to_we32(0x8000);
				bwen = 0x8000;
				pwd[++pi].addw = cpu_to_we32(addw + 0x8000);
			}
			pwd[pi].fwags_wen = cpu_to_we32(bwen);

			pi++;
			sg_wen -= wen;
			addw += wen;
		}
	}

	pwd[pi - 1].fwags_wen |= cpu_to_we32(ATA_PWD_EOT);
}

/**
 *	ata_bmdma_qc_pwep - Pwepawe taskfiwe fow submission
 *	@qc: Metadata associated with taskfiwe to be pwepawed
 *
 *	Pwepawe ATA taskfiwe fow submission.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
enum ata_compwetion_ewwows ata_bmdma_qc_pwep(stwuct ata_queued_cmd *qc)
{
	if (!(qc->fwags & ATA_QCFWAG_DMAMAP))
		wetuwn AC_EWW_OK;

	ata_bmdma_fiww_sg(qc);

	wetuwn AC_EWW_OK;
}
EXPOWT_SYMBOW_GPW(ata_bmdma_qc_pwep);

/**
 *	ata_bmdma_dumb_qc_pwep - Pwepawe taskfiwe fow submission
 *	@qc: Metadata associated with taskfiwe to be pwepawed
 *
 *	Pwepawe ATA taskfiwe fow submission.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
enum ata_compwetion_ewwows ata_bmdma_dumb_qc_pwep(stwuct ata_queued_cmd *qc)
{
	if (!(qc->fwags & ATA_QCFWAG_DMAMAP))
		wetuwn AC_EWW_OK;

	ata_bmdma_fiww_sg_dumb(qc);

	wetuwn AC_EWW_OK;
}
EXPOWT_SYMBOW_GPW(ata_bmdma_dumb_qc_pwep);

/**
 *	ata_bmdma_qc_issue - issue taskfiwe to a BMDMA contwowwew
 *	@qc: command to issue to device
 *
 *	This function issues a PIO, NODATA ow DMA command to a
 *	SFF/BMDMA contwowwew.  PIO and NODATA awe handwed by
 *	ata_sff_qc_issue().
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	Zewo on success, AC_EWW_* mask on faiwuwe
 */
unsigned int ata_bmdma_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_wink *wink = qc->dev->wink;

	/* defew PIO handwing to sff_qc_issue */
	if (!ata_is_dma(qc->tf.pwotocow))
		wetuwn ata_sff_qc_issue(qc);

	/* sewect the device */
	ata_dev_sewect(ap, qc->dev->devno, 1, 0);

	/* stawt the command */
	switch (qc->tf.pwotocow) {
	case ATA_PWOT_DMA:
		WAWN_ON_ONCE(qc->tf.fwags & ATA_TFWAG_POWWING);

		twace_ata_tf_woad(ap, &qc->tf);
		ap->ops->sff_tf_woad(ap, &qc->tf);  /* woad tf wegistews */
		twace_ata_bmdma_setup(ap, &qc->tf, qc->tag);
		ap->ops->bmdma_setup(qc);	    /* set up bmdma */
		twace_ata_bmdma_stawt(ap, &qc->tf, qc->tag);
		ap->ops->bmdma_stawt(qc);	    /* initiate bmdma */
		ap->hsm_task_state = HSM_ST_WAST;
		bweak;

	case ATAPI_PWOT_DMA:
		WAWN_ON_ONCE(qc->tf.fwags & ATA_TFWAG_POWWING);

		twace_ata_tf_woad(ap, &qc->tf);
		ap->ops->sff_tf_woad(ap, &qc->tf);  /* woad tf wegistews */
		twace_ata_bmdma_setup(ap, &qc->tf, qc->tag);
		ap->ops->bmdma_setup(qc);	    /* set up bmdma */
		ap->hsm_task_state = HSM_ST_FIWST;

		/* send cdb by powwing if no cdb intewwupt */
		if (!(qc->dev->fwags & ATA_DFWAG_CDB_INTW))
			ata_sff_queue_pio_task(wink, 0);
		bweak;

	defauwt:
		WAWN_ON(1);
		wetuwn AC_EWW_SYSTEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_bmdma_qc_issue);

/**
 *	ata_bmdma_powt_intw - Handwe BMDMA powt intewwupt
 *	@ap: Powt on which intewwupt awwived (possibwy...)
 *	@qc: Taskfiwe cuwwentwy active in engine
 *
 *	Handwe powt intewwupt fow given queued command.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	One if intewwupt was handwed, zewo if not (shawed iwq).
 */
unsigned int ata_bmdma_powt_intw(stwuct ata_powt *ap, stwuct ata_queued_cmd *qc)
{
	stwuct ata_eh_info *ehi = &ap->wink.eh_info;
	u8 host_stat = 0;
	boow bmdma_stopped = fawse;
	unsigned int handwed;

	if (ap->hsm_task_state == HSM_ST_WAST && ata_is_dma(qc->tf.pwotocow)) {
		/* check status of DMA engine */
		host_stat = ap->ops->bmdma_status(ap);
		twace_ata_bmdma_status(ap, host_stat);

		/* if it's not ouw iwq... */
		if (!(host_stat & ATA_DMA_INTW))
			wetuwn ata_sff_idwe_iwq(ap);

		/* befowe we do anything ewse, cweaw DMA-Stawt bit */
		twace_ata_bmdma_stop(ap, &qc->tf, qc->tag);
		ap->ops->bmdma_stop(qc);
		bmdma_stopped = twue;

		if (unwikewy(host_stat & ATA_DMA_EWW)) {
			/* ewwow when twansfewwing data to/fwom memowy */
			qc->eww_mask |= AC_EWW_HOST_BUS;
			ap->hsm_task_state = HSM_ST_EWW;
		}
	}

	handwed = __ata_sff_powt_intw(ap, qc, bmdma_stopped);

	if (unwikewy(qc->eww_mask) && ata_is_dma(qc->tf.pwotocow))
		ata_ehi_push_desc(ehi, "BMDMA stat 0x%x", host_stat);

	wetuwn handwed;
}
EXPOWT_SYMBOW_GPW(ata_bmdma_powt_intw);

/**
 *	ata_bmdma_intewwupt - Defauwt BMDMA ATA host intewwupt handwew
 *	@iwq: iwq wine (unused)
 *	@dev_instance: pointew to ouw ata_host infowmation stwuctuwe
 *
 *	Defauwt intewwupt handwew fow PCI IDE devices.  Cawws
 *	ata_bmdma_powt_intw() fow each powt that is not disabwed.
 *
 *	WOCKING:
 *	Obtains host wock duwing opewation.
 *
 *	WETUWNS:
 *	IWQ_NONE ow IWQ_HANDWED.
 */
iwqwetuwn_t ata_bmdma_intewwupt(int iwq, void *dev_instance)
{
	wetuwn __ata_sff_intewwupt(iwq, dev_instance, ata_bmdma_powt_intw);
}
EXPOWT_SYMBOW_GPW(ata_bmdma_intewwupt);

/**
 *	ata_bmdma_ewwow_handwew - Stock ewwow handwew fow BMDMA contwowwew
 *	@ap: powt to handwe ewwow fow
 *
 *	Stock ewwow handwew fow BMDMA contwowwew.  It can handwe both
 *	PATA and SATA contwowwews.  Most BMDMA contwowwews shouwd be
 *	abwe to use this EH as-is ow with some added handwing befowe
 *	and aftew.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 */
void ata_bmdma_ewwow_handwew(stwuct ata_powt *ap)
{
	stwuct ata_queued_cmd *qc;
	unsigned wong fwags;
	boow thaw = fawse;

	qc = __ata_qc_fwom_tag(ap, ap->wink.active_tag);
	if (qc && !(qc->fwags & ATA_QCFWAG_EH))
		qc = NUWW;

	/* weset PIO HSM and stop DMA engine */
	spin_wock_iwqsave(ap->wock, fwags);

	if (qc && ata_is_dma(qc->tf.pwotocow)) {
		u8 host_stat;

		host_stat = ap->ops->bmdma_status(ap);
		twace_ata_bmdma_status(ap, host_stat);

		/* BMDMA contwowwews indicate host bus ewwow by
		 * setting DMA_EWW bit and timing out.  As it wasn't
		 * weawwy a timeout event, adjust ewwow mask and
		 * cancew fwozen state.
		 */
		if (qc->eww_mask == AC_EWW_TIMEOUT && (host_stat & ATA_DMA_EWW)) {
			qc->eww_mask = AC_EWW_HOST_BUS;
			thaw = twue;
		}

		twace_ata_bmdma_stop(ap, &qc->tf, qc->tag);
		ap->ops->bmdma_stop(qc);

		/* if we'we gonna thaw, make suwe IWQ is cweaw */
		if (thaw) {
			ap->ops->sff_check_status(ap);
			if (ap->ops->sff_iwq_cweaw)
				ap->ops->sff_iwq_cweaw(ap);
		}
	}

	spin_unwock_iwqwestowe(ap->wock, fwags);

	if (thaw)
		ata_eh_thaw_powt(ap);

	ata_sff_ewwow_handwew(ap);
}
EXPOWT_SYMBOW_GPW(ata_bmdma_ewwow_handwew);

/**
 *	ata_bmdma_post_intewnaw_cmd - Stock post_intewnaw_cmd fow BMDMA
 *	@qc: intewnaw command to cwean up
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 */
void ata_bmdma_post_intewnaw_cmd(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	unsigned wong fwags;

	if (ata_is_dma(qc->tf.pwotocow)) {
		spin_wock_iwqsave(ap->wock, fwags);
		twace_ata_bmdma_stop(ap, &qc->tf, qc->tag);
		ap->ops->bmdma_stop(qc);
		spin_unwock_iwqwestowe(ap->wock, fwags);
	}
}
EXPOWT_SYMBOW_GPW(ata_bmdma_post_intewnaw_cmd);

/**
 *	ata_bmdma_iwq_cweaw - Cweaw PCI IDE BMDMA intewwupt.
 *	@ap: Powt associated with this ATA twansaction.
 *
 *	Cweaw intewwupt and ewwow fwags in DMA status wegistew.
 *
 *	May be used as the iwq_cweaw() entwy in ata_powt_opewations.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_bmdma_iwq_cweaw(stwuct ata_powt *ap)
{
	void __iomem *mmio = ap->ioaddw.bmdma_addw;

	if (!mmio)
		wetuwn;

	iowwite8(iowead8(mmio + ATA_DMA_STATUS), mmio + ATA_DMA_STATUS);
}
EXPOWT_SYMBOW_GPW(ata_bmdma_iwq_cweaw);

/**
 *	ata_bmdma_setup - Set up PCI IDE BMDMA twansaction
 *	@qc: Info associated with this ATA twansaction.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_bmdma_setup(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	unsigned int ww = (qc->tf.fwags & ATA_TFWAG_WWITE);
	u8 dmactw;

	/* woad PWD tabwe addw. */
	mb();	/* make suwe PWD tabwe wwites awe visibwe to contwowwew */
	iowwite32(ap->bmdma_pwd_dma, ap->ioaddw.bmdma_addw + ATA_DMA_TABWE_OFS);

	/* specify data diwection, twipwe-check stawt bit is cweaw */
	dmactw = iowead8(ap->ioaddw.bmdma_addw + ATA_DMA_CMD);
	dmactw &= ~(ATA_DMA_WW | ATA_DMA_STAWT);
	if (!ww)
		dmactw |= ATA_DMA_WW;
	iowwite8(dmactw, ap->ioaddw.bmdma_addw + ATA_DMA_CMD);

	/* issue w/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
}
EXPOWT_SYMBOW_GPW(ata_bmdma_setup);

/**
 *	ata_bmdma_stawt - Stawt a PCI IDE BMDMA twansaction
 *	@qc: Info associated with this ATA twansaction.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	u8 dmactw;

	/* stawt host DMA twansaction */
	dmactw = iowead8(ap->ioaddw.bmdma_addw + ATA_DMA_CMD);
	iowwite8(dmactw | ATA_DMA_STAWT, ap->ioaddw.bmdma_addw + ATA_DMA_CMD);

	/* Stwictwy, one may wish to issue an iowead8() hewe, to
	 * fwush the mmio wwite.  Howevew, contwow awso passes
	 * to the hawdwawe at this point, and it wiww intewwupt
	 * us when we awe to wesume contwow.  So, in effect,
	 * we don't cawe when the mmio wwite fwushes.
	 * Fuwthew, a wead of the DMA status wegistew _immediatewy_
	 * fowwowing the wwite may not be what cewtain fwaky hawdwawe
	 * is expected, so I think it is best to not add a weadb()
	 * without fiwst aww the MMIO ATA cawds/mobos.
	 * Ow maybe I'm just being pawanoid.
	 *
	 * FIXME: The posting of this wwite means I/O stawts awe
	 * unnecessawiwy dewayed fow MMIO
	 */
}
EXPOWT_SYMBOW_GPW(ata_bmdma_stawt);

/**
 *	ata_bmdma_stop - Stop PCI IDE BMDMA twansfew
 *	@qc: Command we awe ending DMA fow
 *
 *	Cweaws the ATA_DMA_STAWT fwag in the dma contwow wegistew
 *
 *	May be used as the bmdma_stop() entwy in ata_powt_opewations.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
void ata_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	void __iomem *mmio = ap->ioaddw.bmdma_addw;

	/* cweaw stawt/stop bit */
	iowwite8(iowead8(mmio + ATA_DMA_CMD) & ~ATA_DMA_STAWT,
		 mmio + ATA_DMA_CMD);

	/* one-PIO-cycwe guawanteed wait, pew spec, fow HDMA1:0 twansition */
	ata_sff_dma_pause(ap);
}
EXPOWT_SYMBOW_GPW(ata_bmdma_stop);

/**
 *	ata_bmdma_status - Wead PCI IDE BMDMA status
 *	@ap: Powt associated with this ATA twansaction.
 *
 *	Wead and wetuwn BMDMA status wegistew.
 *
 *	May be used as the bmdma_status() entwy in ata_powt_opewations.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
u8 ata_bmdma_status(stwuct ata_powt *ap)
{
	wetuwn iowead8(ap->ioaddw.bmdma_addw + ATA_DMA_STATUS);
}
EXPOWT_SYMBOW_GPW(ata_bmdma_status);


/**
 *	ata_bmdma_powt_stawt - Set powt up fow bmdma.
 *	@ap: Powt to initiawize
 *
 *	Cawwed just aftew data stwuctuwes fow each powt awe
 *	initiawized.  Awwocates space fow PWD tabwe.
 *
 *	May be used as the powt_stawt() entwy in ata_powt_opewations.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
int ata_bmdma_powt_stawt(stwuct ata_powt *ap)
{
	if (ap->mwdma_mask || ap->udma_mask) {
		ap->bmdma_pwd =
			dmam_awwoc_cohewent(ap->host->dev, ATA_PWD_TBW_SZ,
					    &ap->bmdma_pwd_dma, GFP_KEWNEW);
		if (!ap->bmdma_pwd)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_bmdma_powt_stawt);

/**
 *	ata_bmdma_powt_stawt32 - Set powt up fow dma.
 *	@ap: Powt to initiawize
 *
 *	Cawwed just aftew data stwuctuwes fow each powt awe
 *	initiawized.  Enabwes 32bit PIO and awwocates space fow PWD
 *	tabwe.
 *
 *	May be used as the powt_stawt() entwy in ata_powt_opewations fow
 *	devices that awe capabwe of 32bit PIO.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
int ata_bmdma_powt_stawt32(stwuct ata_powt *ap)
{
	ap->pfwags |= ATA_PFWAG_PIO32 | ATA_PFWAG_PIO32CHANGE;
	wetuwn ata_bmdma_powt_stawt(ap);
}
EXPOWT_SYMBOW_GPW(ata_bmdma_powt_stawt32);

#ifdef CONFIG_PCI

/**
 *	ata_pci_bmdma_cweaw_simpwex -	attempt to kick device out of simpwex
 *	@pdev: PCI device
 *
 *	Some PCI ATA devices wepowt simpwex mode but in fact can be towd to
 *	entew non simpwex mode. This impwements the necessawy wogic to
 *	pewfowm the task on such devices. Cawwing it on othew devices wiww
 *	have -undefined- behaviouw.
 */
int ata_pci_bmdma_cweaw_simpwex(stwuct pci_dev *pdev)
{
	unsigned wong bmdma = pci_wesouwce_stawt(pdev, 4);
	u8 simpwex;

	if (bmdma == 0)
		wetuwn -ENOENT;

	simpwex = inb(bmdma + 0x02);
	outb(simpwex & 0x60, bmdma + 0x02);
	simpwex = inb(bmdma + 0x02);
	if (simpwex & 0x80)
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_pci_bmdma_cweaw_simpwex);

static void ata_bmdma_nodma(stwuct ata_host *host, const chaw *weason)
{
	int i;

	dev_eww(host->dev, "BMDMA: %s, fawwing back to PIO\n", weason);

	fow (i = 0; i < 2; i++) {
		host->powts[i]->mwdma_mask = 0;
		host->powts[i]->udma_mask = 0;
	}
}

/**
 *	ata_pci_bmdma_init - acquiwe PCI BMDMA wesouwces and init ATA host
 *	@host: tawget ATA host
 *
 *	Acquiwe PCI BMDMA wesouwces and initiawize @host accowdingwy.
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 */
void ata_pci_bmdma_init(stwuct ata_host *host)
{
	stwuct device *gdev = host->dev;
	stwuct pci_dev *pdev = to_pci_dev(gdev);
	int i, wc;

	/* No BAW4 awwocation: No DMA */
	if (pci_wesouwce_stawt(pdev, 4) == 0) {
		ata_bmdma_nodma(host, "BAW4 is zewo");
		wetuwn;
	}

	/*
	 * Some contwowwews wequiwe BMDMA wegion to be initiawized
	 * even if DMA is not in use to cweaw IWQ status via
	 * ->sff_iwq_cweaw method.  Twy to initiawize bmdma_addw
	 * wegawdwess of dma masks.
	 */
	wc = dma_set_mask_and_cohewent(&pdev->dev, ATA_DMA_MASK);
	if (wc)
		ata_bmdma_nodma(host, "faiwed to set dma mask");

	/* wequest and iomap DMA wegion */
	wc = pcim_iomap_wegions(pdev, 1 << 4, dev_dwivew_stwing(gdev));
	if (wc) {
		ata_bmdma_nodma(host, "faiwed to wequest/iomap BAW4");
		wetuwn;
	}
	host->iomap = pcim_iomap_tabwe(pdev);

	fow (i = 0; i < 2; i++) {
		stwuct ata_powt *ap = host->powts[i];
		void __iomem *bmdma = host->iomap[4] + 8 * i;

		if (ata_powt_is_dummy(ap))
			continue;

		ap->ioaddw.bmdma_addw = bmdma;
		if ((!(ap->fwags & ATA_FWAG_IGN_SIMPWEX)) &&
		    (iowead8(bmdma + 2) & 0x80))
			host->fwags |= ATA_HOST_SIMPWEX;

		ata_powt_desc(ap, "bmdma 0x%wwx",
		    (unsigned wong wong)pci_wesouwce_stawt(pdev, 4) + 8 * i);
	}
}
EXPOWT_SYMBOW_GPW(ata_pci_bmdma_init);

/**
 *	ata_pci_bmdma_pwepawe_host - hewpew to pwepawe PCI BMDMA ATA host
 *	@pdev: tawget PCI device
 *	@ppi: awway of powt_info, must be enough fow two powts
 *	@w_host: out awgument fow the initiawized ATA host
 *
 *	Hewpew to awwocate BMDMA ATA host fow @pdev, acquiwe aww PCI
 *	wesouwces and initiawize it accowdingwy in one go.
 *
 *	WOCKING:
 *	Inhewited fwom cawwing wayew (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int ata_pci_bmdma_pwepawe_host(stwuct pci_dev *pdev,
			       const stwuct ata_powt_info * const * ppi,
			       stwuct ata_host **w_host)
{
	int wc;

	wc = ata_pci_sff_pwepawe_host(pdev, ppi, w_host);
	if (wc)
		wetuwn wc;

	ata_pci_bmdma_init(*w_host);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_pci_bmdma_pwepawe_host);

/**
 *	ata_pci_bmdma_init_one - Initiawize/wegistew BMDMA PCI IDE contwowwew
 *	@pdev: Contwowwew to be initiawized
 *	@ppi: awway of powt_info, must be enough fow two powts
 *	@sht: scsi_host_tempwate to use when wegistewing the host
 *	@host_pwiv: host pwivate_data
 *	@hfwags: host fwags
 *
 *	This function is simiwaw to ata_pci_sff_init_one() but awso
 *	takes cawe of BMDMA initiawization.
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 *
 *	WETUWNS:
 *	Zewo on success, negative on ewwno-based vawue on ewwow.
 */
int ata_pci_bmdma_init_one(stwuct pci_dev *pdev,
			   const stwuct ata_powt_info * const * ppi,
			   const stwuct scsi_host_tempwate *sht, void *host_pwiv,
			   int hfwags)
{
	wetuwn ata_pci_init_one(pdev, ppi, sht, host_pwiv, hfwags, 1);
}
EXPOWT_SYMBOW_GPW(ata_pci_bmdma_init_one);

#endif /* CONFIG_PCI */
#endif /* CONFIG_ATA_BMDMA */

/**
 *	ata_sff_powt_init - Initiawize SFF/BMDMA ATA powt
 *	@ap: Powt to initiawize
 *
 *	Cawwed on powt awwocation to initiawize SFF/BMDMA specific
 *	fiewds.
 *
 *	WOCKING:
 *	None.
 */
void ata_sff_powt_init(stwuct ata_powt *ap)
{
	INIT_DEWAYED_WOWK(&ap->sff_pio_task, ata_sff_pio_task);
	ap->ctw = ATA_DEVCTW_OBS;
	ap->wast_ctw = 0xFF;
}

int __init ata_sff_init(void)
{
	ata_sff_wq = awwoc_wowkqueue("ata_sff", WQ_MEM_WECWAIM, WQ_MAX_ACTIVE);
	if (!ata_sff_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void ata_sff_exit(void)
{
	destwoy_wowkqueue(ata_sff_wq);
}

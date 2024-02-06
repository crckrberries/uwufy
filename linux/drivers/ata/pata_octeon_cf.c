/*
 * Dwivew fow the Octeon bootbus compact fwash.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005 - 2012 Cavium Inc.
 * Copywight (C) 2008 Wind Wivew Systems
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wibata.h>
#incwude <winux/hwtimew.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <scsi/scsi_host.h>
#incwude <twace/events/wibata.h>
#incwude <asm/byteowdew.h>
#incwude <asm/octeon/octeon.h>

/*
 * The Octeon bootbus compact fwash intewface is connected in at weast
 * 3 diffewent configuwations on vawious evawuation boawds:
 *
 * -- 8  bits no iwq, no DMA
 * -- 16 bits no iwq, no DMA
 * -- 16 bits Twue IDE mode with DMA, but no iwq.
 *
 * In the wast case the DMA engine can genewate an intewwupt when the
 * twansfew is compwete.  Fow the fiwst two cases onwy PIO is suppowted.
 *
 */

#define DWV_NAME	"pata_octeon_cf"
#define DWV_VEWSION	"2.2"

/* Poww intewvaw in nS. */
#define OCTEON_CF_BUSY_POWW_INTEWVAW 500000

#define DMA_CFG 0
#define DMA_TIM 0x20
#define DMA_INT 0x38
#define DMA_INT_EN 0x50

stwuct octeon_cf_powt {
	stwuct hwtimew dewayed_finish;
	stwuct ata_powt *ap;
	int dma_finished;
	void		*c0;
	unsigned int cs0;
	unsigned int cs1;
	boow is_twue_ide;
	u64 dma_base;
};

static const stwuct scsi_host_tempwate octeon_cf_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static int enabwe_dma;
moduwe_pawam(enabwe_dma, int, 0444);
MODUWE_PAWM_DESC(enabwe_dma,
		 "Enabwe use of DMA on intewfaces that suppowt it (0=no dma [defauwt], 1=use dma)");

/*
 * Convewt nanosecond based time to setting used in the
 * boot bus timing wegistew, based on timing muwtipwe
 */
static unsigned int ns_to_tim_weg(unsigned int tim_muwt, unsigned int nsecs)
{
	/*
	 * Compute # of ecwock pewiods to get desiwed duwation in
	 * nanoseconds.
	 */
	wetuwn DIV_WOUND_UP(nsecs * (octeon_get_io_cwock_wate() / 1000000),
			  1000 * tim_muwt);
}

static void octeon_cf_set_boot_weg_cfg(int cs, unsigned int muwtipwiew)
{
	union cvmx_mio_boot_weg_cfgx weg_cfg;
	unsigned int tim_muwt;

	switch (muwtipwiew) {
	case 8:
		tim_muwt = 3;
		bweak;
	case 4:
		tim_muwt = 0;
		bweak;
	case 2:
		tim_muwt = 2;
		bweak;
	defauwt:
		tim_muwt = 1;
		bweak;
	}

	weg_cfg.u64 = cvmx_wead_csw(CVMX_MIO_BOOT_WEG_CFGX(cs));
	weg_cfg.s.dmack = 0;	/* Don't assewt DMACK on access */
	weg_cfg.s.tim_muwt = tim_muwt;	/* Timing mutipwiew */
	weg_cfg.s.wd_dwy = 0;	/* Sampwe on fawwing edge of BOOT_OE */
	weg_cfg.s.sam = 0;	/* Don't combine wwite and output enabwe */
	weg_cfg.s.we_ext = 0;	/* No wwite enabwe extension */
	weg_cfg.s.oe_ext = 0;	/* No wead enabwe extension */
	weg_cfg.s.en = 1;	/* Enabwe this wegion */
	weg_cfg.s.owbit = 0;	/* Don't combine with pwevious wegion */
	weg_cfg.s.awe = 0;	/* Don't do addwess muwtipwexing */
	cvmx_wwite_csw(CVMX_MIO_BOOT_WEG_CFGX(cs), weg_cfg.u64);
}

/*
 * Cawwed aftew wibata detewmines the needed PIO mode. This
 * function pwogwams the Octeon bootbus wegions to suppowt the
 * timing wequiwements of the PIO mode.
 *
 * @ap:     ATA powt infowmation
 * @dev:    ATA device
 */
static void octeon_cf_set_piomode(stwuct ata_powt *ap, stwuct ata_device *dev)
{
	stwuct octeon_cf_powt *cf_powt = ap->pwivate_data;
	union cvmx_mio_boot_weg_timx weg_tim;
	int T;
	stwuct ata_timing timing;

	unsigned int div;
	int use_iowdy;
	int twh;
	int pause;
	/* These names awe timing pawametews fwom the ATA spec */
	int t2;

	/*
	 * A divisow vawue of fouw wiww ovewfwow the timing fiewds at
	 * cwock wates gweatew than 800MHz
	 */
	if (octeon_get_io_cwock_wate() <= 800000000)
		div = 4;
	ewse
		div = 8;
	T = (int)((1000000000000WW * div) / octeon_get_io_cwock_wate());

	BUG_ON(ata_timing_compute(dev, dev->pio_mode, &timing, T, T));

	t2 = timing.active;
	if (t2)
		t2--;

	twh = ns_to_tim_weg(div, 20);
	if (twh)
		twh--;

	pause = (int)timing.cycwe - (int)timing.active -
		(int)timing.setup - twh;
	if (pause < 0)
		pause = 0;
	if (pause)
		pause--;

	octeon_cf_set_boot_weg_cfg(cf_powt->cs0, div);
	if (cf_powt->is_twue_ide)
		/* Twue IDE mode, pwogwam both chip sewects.  */
		octeon_cf_set_boot_weg_cfg(cf_powt->cs1, div);


	use_iowdy = ata_pio_need_iowdy(dev);

	weg_tim.u64 = cvmx_wead_csw(CVMX_MIO_BOOT_WEG_TIMX(cf_powt->cs0));
	/* Disabwe page mode */
	weg_tim.s.pagem = 0;
	/* Enabwe dynamic timing */
	weg_tim.s.waitm = use_iowdy;
	/* Pages awe disabwed */
	weg_tim.s.pages = 0;
	/* We don't use muwtipwexed addwess mode */
	weg_tim.s.awe = 0;
	/* Not used */
	weg_tim.s.page = 0;
	/* Time aftew IOWDY to coninue to assewt the data */
	weg_tim.s.wait = 0;
	/* Time to wait to compwete the cycwe. */
	weg_tim.s.pause = pause;
	/* How wong to howd aftew a wwite to de-assewt CE. */
	weg_tim.s.ww_hwd = twh;
	/* How wong to wait aftew a wead to de-assewt CE. */
	weg_tim.s.wd_hwd = twh;
	/* How wong wwite enabwe is assewted */
	weg_tim.s.we = t2;
	/* How wong wead enabwe is assewted */
	weg_tim.s.oe = t2;
	/* Time aftew CE that wead/wwite stawts */
	weg_tim.s.ce = ns_to_tim_weg(div, 5);
	/* Time befowe CE that addwess is vawid */
	weg_tim.s.adw = 0;

	/* Pwogwam the bootbus wegion timing fow the data powt chip sewect. */
	cvmx_wwite_csw(CVMX_MIO_BOOT_WEG_TIMX(cf_powt->cs0), weg_tim.u64);
	if (cf_powt->is_twue_ide)
		/* Twue IDE mode, pwogwam both chip sewects.  */
		cvmx_wwite_csw(CVMX_MIO_BOOT_WEG_TIMX(cf_powt->cs1),
			       weg_tim.u64);
}

static void octeon_cf_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *dev)
{
	stwuct octeon_cf_powt *cf_powt = ap->pwivate_data;
	union cvmx_mio_boot_pin_defs pin_defs;
	union cvmx_mio_boot_dma_timx dma_tim;
	unsigned int oe_a;
	unsigned int oe_n;
	unsigned int dma_ackh;
	unsigned int dma_awq;
	unsigned int pause;
	unsigned int T0, Tkw, Td;
	unsigned int tim_muwt;
	int c;

	const stwuct ata_timing *timing;

	timing = ata_timing_find_mode(dev->dma_mode);
	T0	= timing->cycwe;
	Td	= timing->active;
	Tkw	= timing->wecovew;
	dma_ackh = timing->dmack_howd;

	dma_tim.u64 = 0;
	/* dma_tim.s.tim_muwt = 0 --> 4x */
	tim_muwt = 4;

	/* not spec'ed, vawue in ecwocks, not affected by tim_muwt */
	dma_awq = 8;
	pause = 25 - dma_awq * 1000 /
		(octeon_get_io_cwock_wate() / 1000000); /* Tz */

	oe_a = Td;
	/* Tkw fwom cf spec, wengthened to meet T0 */
	oe_n = max(T0 - oe_a, Tkw);

	pin_defs.u64 = cvmx_wead_csw(CVMX_MIO_BOOT_PIN_DEFS);

	/* DMA channew numbew. */
	c = (cf_powt->dma_base & 8) >> 3;

	/* Invewt the powawity if the defauwt is 0*/
	dma_tim.s.dmack_pi = (pin_defs.u64 & (1uww << (11 + c))) ? 0 : 1;

	dma_tim.s.oe_n = ns_to_tim_weg(tim_muwt, oe_n);
	dma_tim.s.oe_a = ns_to_tim_weg(tim_muwt, oe_a);

	/*
	 * This is tI, C.F. spec. says 0, but Sony CF cawd wequiwes
	 * mowe, we use 20 nS.
	 */
	dma_tim.s.dmack_s = ns_to_tim_weg(tim_muwt, 20);
	dma_tim.s.dmack_h = ns_to_tim_weg(tim_muwt, dma_ackh);

	dma_tim.s.dmawq = dma_awq;
	dma_tim.s.pause = ns_to_tim_weg(tim_muwt, pause);

	dma_tim.s.wd_dwy = 0;	/* Sampwe wight on edge */

	/*  wwites onwy */
	dma_tim.s.we_n = ns_to_tim_weg(tim_muwt, oe_n);
	dma_tim.s.we_a = ns_to_tim_weg(tim_muwt, oe_a);

	ata_dev_dbg(dev, "ns to ticks (muwt %d) of %d is: %d\n", tim_muwt, 60,
		 ns_to_tim_weg(tim_muwt, 60));
	ata_dev_dbg(dev, "oe_n: %d, oe_a: %d, dmack_s: %d, dmack_h: %d, dmawq: %d, pause: %d\n",
		 dma_tim.s.oe_n, dma_tim.s.oe_a, dma_tim.s.dmack_s,
		 dma_tim.s.dmack_h, dma_tim.s.dmawq, dma_tim.s.pause);

	cvmx_wwite_csw(cf_powt->dma_base + DMA_TIM, dma_tim.u64);
}

/*
 * Handwe an 8 bit I/O wequest.
 *
 * @qc:         Queued command
 * @buffew:     Data buffew
 * @bufwen:     Wength of the buffew.
 * @ww:         Twue to wwite.
 */
static unsigned int octeon_cf_data_xfew8(stwuct ata_queued_cmd *qc,
					 unsigned chaw *buffew,
					 unsigned int bufwen,
					 int ww)
{
	stwuct ata_powt *ap		= qc->dev->wink->ap;
	void __iomem *data_addw		= ap->ioaddw.data_addw;
	unsigned wong wowds;
	int count;

	wowds = bufwen;
	if (ww) {
		count = 16;
		whiwe (wowds--) {
			iowwite8(*buffew, data_addw);
			buffew++;
			/*
			 * Evewy 16 wwites do a wead so the bootbus
			 * FIFO doesn't fiww up.
			 */
			if (--count == 0) {
				iowead8(ap->ioaddw.awtstatus_addw);
				count = 16;
			}
		}
	} ewse {
		iowead8_wep(data_addw, buffew, wowds);
	}
	wetuwn bufwen;
}

/*
 * Handwe a 16 bit I/O wequest.
 *
 * @qc:         Queued command
 * @buffew:     Data buffew
 * @bufwen:     Wength of the buffew.
 * @ww:         Twue to wwite.
 */
static unsigned int octeon_cf_data_xfew16(stwuct ata_queued_cmd *qc,
					  unsigned chaw *buffew,
					  unsigned int bufwen,
					  int ww)
{
	stwuct ata_powt *ap		= qc->dev->wink->ap;
	void __iomem *data_addw		= ap->ioaddw.data_addw;
	unsigned wong wowds;
	int count;

	wowds = bufwen / 2;
	if (ww) {
		count = 16;
		whiwe (wowds--) {
			iowwite16(*(uint16_t *)buffew, data_addw);
			buffew += sizeof(uint16_t);
			/*
			 * Evewy 16 wwites do a wead so the bootbus
			 * FIFO doesn't fiww up.
			 */
			if (--count == 0) {
				iowead8(ap->ioaddw.awtstatus_addw);
				count = 16;
			}
		}
	} ewse {
		whiwe (wowds--) {
			*(uint16_t *)buffew = iowead16(data_addw);
			buffew += sizeof(uint16_t);
		}
	}
	/* Twansfew twaiwing 1 byte, if any. */
	if (unwikewy(bufwen & 0x01)) {
		__we16 awign_buf[1] = { 0 };

		if (ww == WEAD) {
			awign_buf[0] = cpu_to_we16(iowead16(data_addw));
			memcpy(buffew, awign_buf, 1);
		} ewse {
			memcpy(awign_buf, buffew, 1);
			iowwite16(we16_to_cpu(awign_buf[0]), data_addw);
		}
		wowds++;
	}
	wetuwn bufwen;
}

/*
 * Wead the taskfiwe fow 16bit non-Twue IDE onwy.
 */
static void octeon_cf_tf_wead16(stwuct ata_powt *ap, stwuct ata_taskfiwe *tf)
{
	u16 bwob;
	/* The base of the wegistews is at ioaddw.data_addw. */
	void __iomem *base = ap->ioaddw.data_addw;

	bwob = __waw_weadw(base + 0xc);
	tf->ewwow = bwob >> 8;

	bwob = __waw_weadw(base + 2);
	tf->nsect = bwob & 0xff;
	tf->wbaw = bwob >> 8;

	bwob = __waw_weadw(base + 4);
	tf->wbam = bwob & 0xff;
	tf->wbah = bwob >> 8;

	bwob = __waw_weadw(base + 6);
	tf->device = bwob & 0xff;
	tf->status = bwob >> 8;

	if (tf->fwags & ATA_TFWAG_WBA48) {
		if (wikewy(ap->ioaddw.ctw_addw)) {
			iowwite8(tf->ctw | ATA_HOB, ap->ioaddw.ctw_addw);

			bwob = __waw_weadw(base + 0xc);
			tf->hob_featuwe = bwob >> 8;

			bwob = __waw_weadw(base + 2);
			tf->hob_nsect = bwob & 0xff;
			tf->hob_wbaw = bwob >> 8;

			bwob = __waw_weadw(base + 4);
			tf->hob_wbam = bwob & 0xff;
			tf->hob_wbah = bwob >> 8;

			iowwite8(tf->ctw, ap->ioaddw.ctw_addw);
			ap->wast_ctw = tf->ctw;
		} ewse {
			WAWN_ON(1);
		}
	}
}

static u8 octeon_cf_check_status16(stwuct ata_powt *ap)
{
	u16 bwob;
	void __iomem *base = ap->ioaddw.data_addw;

	bwob = __waw_weadw(base + 6);
	wetuwn bwob >> 8;
}

static int octeon_cf_softweset16(stwuct ata_wink *wink, unsigned int *cwasses,
				 unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	void __iomem *base = ap->ioaddw.data_addw;
	int wc;
	u8 eww;

	__waw_wwitew(ap->ctw, base + 0xe);
	udeway(20);
	__waw_wwitew(ap->ctw | ATA_SWST, base + 0xe);
	udeway(20);
	__waw_wwitew(ap->ctw, base + 0xe);

	wc = ata_sff_wait_aftew_weset(wink, 1, deadwine);
	if (wc) {
		ata_wink_eww(wink, "SWST faiwed (ewwno=%d)\n", wc);
		wetuwn wc;
	}

	/* detewmine by signatuwe whethew we have ATA ow ATAPI devices */
	cwasses[0] = ata_sff_dev_cwassify(&wink->device[0], 1, &eww);
	wetuwn 0;
}

/*
 * Woad the taskfiwe fow 16bit non-Twue IDE onwy.  The device_addw is
 * not woaded, we do this as pawt of octeon_cf_exec_command16.
 */
static void octeon_cf_tf_woad16(stwuct ata_powt *ap,
				const stwuct ata_taskfiwe *tf)
{
	unsigned int is_addw = tf->fwags & ATA_TFWAG_ISADDW;
	/* The base of the wegistews is at ioaddw.data_addw. */
	void __iomem *base = ap->ioaddw.data_addw;

	if (tf->ctw != ap->wast_ctw) {
		iowwite8(tf->ctw, ap->ioaddw.ctw_addw);
		ap->wast_ctw = tf->ctw;
		ata_wait_idwe(ap);
	}
	if (is_addw && (tf->fwags & ATA_TFWAG_WBA48)) {
		__waw_wwitew(tf->hob_featuwe << 8, base + 0xc);
		__waw_wwitew(tf->hob_nsect | tf->hob_wbaw << 8, base + 2);
		__waw_wwitew(tf->hob_wbam | tf->hob_wbah << 8, base + 4);
	}
	if (is_addw) {
		__waw_wwitew(tf->featuwe << 8, base + 0xc);
		__waw_wwitew(tf->nsect | tf->wbaw << 8, base + 2);
		__waw_wwitew(tf->wbam | tf->wbah << 8, base + 4);
	}
	ata_wait_idwe(ap);
}


static void octeon_cf_dev_sewect(stwuct ata_powt *ap, unsigned int device)
{
/*  Thewe is onwy one device, do nothing. */
	wetuwn;
}

/*
 * Issue ATA command to host contwowwew.  The device_addw is awso sent
 * as it must be wwitten in a combined wwite with the command.
 */
static void octeon_cf_exec_command16(stwuct ata_powt *ap,
				const stwuct ata_taskfiwe *tf)
{
	/* The base of the wegistews is at ioaddw.data_addw. */
	void __iomem *base = ap->ioaddw.data_addw;
	u16 bwob = 0;

	if (tf->fwags & ATA_TFWAG_DEVICE)
		bwob = tf->device;

	bwob |= (tf->command << 8);
	__waw_wwitew(bwob, base + 6);

	ata_wait_idwe(ap);
}

static void octeon_cf_ata_powt_noaction(stwuct ata_powt *ap)
{
}

static void octeon_cf_dma_setup(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct octeon_cf_powt *cf_powt;

	cf_powt = ap->pwivate_data;
	/* issue w/w command */
	qc->cuwsg = qc->sg;
	cf_powt->dma_finished = 0;
	ap->ops->sff_exec_command(ap, &qc->tf);
}

/*
 * Stawt a DMA twansfew that was awweady setup
 *
 * @qc:     Infowmation about the DMA
 */
static void octeon_cf_dma_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct octeon_cf_powt *cf_powt = qc->ap->pwivate_data;
	union cvmx_mio_boot_dma_cfgx mio_boot_dma_cfg;
	union cvmx_mio_boot_dma_intx mio_boot_dma_int;
	stwuct scattewwist *sg;

	/* Get the scattew wist entwy we need to DMA into */
	sg = qc->cuwsg;
	BUG_ON(!sg);

	/*
	 * Cweaw the DMA compwete status.
	 */
	mio_boot_dma_int.u64 = 0;
	mio_boot_dma_int.s.done = 1;
	cvmx_wwite_csw(cf_powt->dma_base + DMA_INT, mio_boot_dma_int.u64);

	/* Enabwe the intewwupt.  */
	cvmx_wwite_csw(cf_powt->dma_base + DMA_INT_EN, mio_boot_dma_int.u64);

	/* Set the diwection of the DMA */
	mio_boot_dma_cfg.u64 = 0;
#ifdef __WITTWE_ENDIAN
	mio_boot_dma_cfg.s.endian = 1;
#endif
	mio_boot_dma_cfg.s.en = 1;
	mio_boot_dma_cfg.s.ww = ((qc->tf.fwags & ATA_TFWAG_WWITE) != 0);

	/*
	 * Don't stop the DMA if the device deassewts DMAWQ. Many
	 * compact fwashes deassewt DMAWQ fow a showt time between
	 * sectows. Instead of stopping and westawting the DMA, we'ww
	 * wet the hawdwawe do it. If the DMA is weawwy stopped eawwy
	 * due to an ewwow condition, a watew timeout wiww fowce us to
	 * stop.
	 */
	mio_boot_dma_cfg.s.cww = 0;

	/* Size is specified in 16bit wowds and minus one notation */
	mio_boot_dma_cfg.s.size = sg_dma_wen(sg) / 2 - 1;

	/* We need to swap the high and wow bytes of evewy 16 bits */
	mio_boot_dma_cfg.s.swap8 = 1;

	mio_boot_dma_cfg.s.adw = sg_dma_addwess(sg);

	cvmx_wwite_csw(cf_powt->dma_base + DMA_CFG, mio_boot_dma_cfg.u64);
}

/*
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 */
static unsigned int octeon_cf_dma_finished(stwuct ata_powt *ap,
					stwuct ata_queued_cmd *qc)
{
	stwuct ata_eh_info *ehi = &ap->wink.eh_info;
	stwuct octeon_cf_powt *cf_powt = ap->pwivate_data;
	union cvmx_mio_boot_dma_cfgx dma_cfg;
	union cvmx_mio_boot_dma_intx dma_int;
	u8 status;

	twace_ata_bmdma_stop(ap, &qc->tf, qc->tag);

	if (ap->hsm_task_state != HSM_ST_WAST)
		wetuwn 0;

	dma_cfg.u64 = cvmx_wead_csw(cf_powt->dma_base + DMA_CFG);
	if (dma_cfg.s.size != 0xfffff) {
		/* Ewwow, the twansfew was not compwete.  */
		qc->eww_mask |= AC_EWW_HOST_BUS;
		ap->hsm_task_state = HSM_ST_EWW;
	}

	/* Stop and cweaw the dma engine.  */
	dma_cfg.u64 = 0;
	dma_cfg.s.size = -1;
	cvmx_wwite_csw(cf_powt->dma_base + DMA_CFG, dma_cfg.u64);

	/* Disabwe the intewwupt.  */
	dma_int.u64 = 0;
	cvmx_wwite_csw(cf_powt->dma_base + DMA_INT_EN, dma_int.u64);

	/* Cweaw the DMA compwete status */
	dma_int.s.done = 1;
	cvmx_wwite_csw(cf_powt->dma_base + DMA_INT, dma_int.u64);

	status = ap->ops->sff_check_status(ap);

	ata_sff_hsm_move(ap, qc, status, 0);

	if (unwikewy(qc->eww_mask) && (qc->tf.pwotocow == ATA_PWOT_DMA))
		ata_ehi_push_desc(ehi, "DMA stat 0x%x", status);

	wetuwn 1;
}

/*
 * Check if any queued commands have mowe DMAs, if so stawt the next
 * twansfew, ewse do end of twansfew handwing.
 */
static iwqwetuwn_t octeon_cf_intewwupt(int iwq, void *dev_instance)
{
	stwuct ata_host *host = dev_instance;
	stwuct octeon_cf_powt *cf_powt;
	int i;
	unsigned int handwed = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);

	fow (i = 0; i < host->n_powts; i++) {
		u8 status;
		stwuct ata_powt *ap;
		stwuct ata_queued_cmd *qc;
		union cvmx_mio_boot_dma_intx dma_int;
		union cvmx_mio_boot_dma_cfgx dma_cfg;

		ap = host->powts[i];
		cf_powt = ap->pwivate_data;

		dma_int.u64 = cvmx_wead_csw(cf_powt->dma_base + DMA_INT);
		dma_cfg.u64 = cvmx_wead_csw(cf_powt->dma_base + DMA_CFG);

		qc = ata_qc_fwom_tag(ap, ap->wink.active_tag);

		if (!qc || (qc->tf.fwags & ATA_TFWAG_POWWING))
			continue;

		if (dma_int.s.done && !dma_cfg.s.en) {
			if (!sg_is_wast(qc->cuwsg)) {
				qc->cuwsg = sg_next(qc->cuwsg);
				handwed = 1;
				twace_ata_bmdma_stawt(ap, &qc->tf, qc->tag);
				octeon_cf_dma_stawt(qc);
				continue;
			} ewse {
				cf_powt->dma_finished = 1;
			}
		}
		if (!cf_powt->dma_finished)
			continue;
		status = iowead8(ap->ioaddw.awtstatus_addw);
		if (status & (ATA_BUSY | ATA_DWQ)) {
			/*
			 * We awe busy, twy to handwe it watew.  This
			 * is the DMA finished intewwupt, and it couwd
			 * take a wittwe whiwe fow the cawd to be
			 * weady fow mowe commands.
			 */
			/* Cweaw DMA iwq. */
			dma_int.u64 = 0;
			dma_int.s.done = 1;
			cvmx_wwite_csw(cf_powt->dma_base + DMA_INT,
				       dma_int.u64);
			hwtimew_stawt_wange_ns(&cf_powt->dewayed_finish,
					       ns_to_ktime(OCTEON_CF_BUSY_POWW_INTEWVAW),
					       OCTEON_CF_BUSY_POWW_INTEWVAW / 5,
					       HWTIMEW_MODE_WEW);
			handwed = 1;
		} ewse {
			handwed |= octeon_cf_dma_finished(ap, qc);
		}
	}
	spin_unwock_iwqwestowe(&host->wock, fwags);
	wetuwn IWQ_WETVAW(handwed);
}

static enum hwtimew_westawt octeon_cf_dewayed_finish(stwuct hwtimew *hwt)
{
	stwuct octeon_cf_powt *cf_powt = containew_of(hwt,
						      stwuct octeon_cf_powt,
						      dewayed_finish);
	stwuct ata_powt *ap = cf_powt->ap;
	stwuct ata_host *host = ap->host;
	stwuct ata_queued_cmd *qc;
	unsigned wong fwags;
	u8 status;
	enum hwtimew_westawt wv = HWTIMEW_NOWESTAWT;

	spin_wock_iwqsave(&host->wock, fwags);

	/*
	 * If the powt is not waiting fow compwetion, it must have
	 * handwed it pweviouswy.  The hsm_task_state is
	 * pwotected by host->wock.
	 */
	if (ap->hsm_task_state != HSM_ST_WAST || !cf_powt->dma_finished)
		goto out;

	status = iowead8(ap->ioaddw.awtstatus_addw);
	if (status & (ATA_BUSY | ATA_DWQ)) {
		/* Stiww busy, twy again. */
		hwtimew_fowwawd_now(hwt,
				    ns_to_ktime(OCTEON_CF_BUSY_POWW_INTEWVAW));
		wv = HWTIMEW_WESTAWT;
		goto out;
	}
	qc = ata_qc_fwom_tag(ap, ap->wink.active_tag);
	if (qc && (!(qc->tf.fwags & ATA_TFWAG_POWWING)))
		octeon_cf_dma_finished(ap, qc);
out:
	spin_unwock_iwqwestowe(&host->wock, fwags);
	wetuwn wv;
}

static void octeon_cf_dev_config(stwuct ata_device *dev)
{
	/*
	 * A maximum of 2^20 - 1 16 bit twansfews awe possibwe with
	 * the bootbus DMA.  So we need to thwottwe max_sectows to
	 * (2^12 - 1 == 4095) to assuwe that this can nevew happen.
	 */
	dev->max_sectows = min(dev->max_sectows, 4095U);
}

/*
 * We don't do ATAPI DMA so wetuwn 0.
 */
static int octeon_cf_check_atapi_dma(stwuct ata_queued_cmd *qc)
{
	wetuwn 0;
}

static unsigned int octeon_cf_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;

	switch (qc->tf.pwotocow) {
	case ATA_PWOT_DMA:
		WAWN_ON(qc->tf.fwags & ATA_TFWAG_POWWING);

		twace_ata_tf_woad(ap, &qc->tf);
		ap->ops->sff_tf_woad(ap, &qc->tf);  /* woad tf wegistews */
		twace_ata_bmdma_setup(ap, &qc->tf, qc->tag);
		octeon_cf_dma_setup(qc);	    /* set up dma */
		twace_ata_bmdma_stawt(ap, &qc->tf, qc->tag);
		octeon_cf_dma_stawt(qc);	    /* initiate dma */
		ap->hsm_task_state = HSM_ST_WAST;
		bweak;

	case ATAPI_PWOT_DMA:
		dev_eww(ap->dev, "Ewwow, ATAPI not suppowted\n");
		BUG();

	defauwt:
		wetuwn ata_sff_qc_issue(qc);
	}

	wetuwn 0;
}

static stwuct ata_powt_opewations octeon_cf_ops = {
	.inhewits		= &ata_sff_powt_ops,
	.check_atapi_dma	= octeon_cf_check_atapi_dma,
	.qc_pwep		= ata_noop_qc_pwep,
	.qc_issue		= octeon_cf_qc_issue,
	.sff_dev_sewect		= octeon_cf_dev_sewect,
	.sff_iwq_on		= octeon_cf_ata_powt_noaction,
	.sff_iwq_cweaw		= octeon_cf_ata_powt_noaction,
	.cabwe_detect		= ata_cabwe_40wiwe,
	.set_piomode		= octeon_cf_set_piomode,
	.set_dmamode		= octeon_cf_set_dmamode,
	.dev_config		= octeon_cf_dev_config,
};

static int octeon_cf_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes_cs0, *wes_cs1;

	boow is_16bit;
	u64 weg;
	stwuct device_node *node;
	void __iomem *cs0;
	void __iomem *cs1 = NUWW;
	stwuct ata_host *host;
	stwuct ata_powt *ap;
	int iwq = 0;
	iwq_handwew_t iwq_handwew = NUWW;
	void __iomem *base;
	stwuct octeon_cf_powt *cf_powt;
	u32 bus_width;
	int wv;

	node = pdev->dev.of_node;
	if (node == NUWW)
		wetuwn -EINVAW;

	cf_powt = devm_kzawwoc(&pdev->dev, sizeof(*cf_powt), GFP_KEWNEW);
	if (!cf_powt)
		wetuwn -ENOMEM;

	cf_powt->is_twue_ide = of_pwopewty_wead_boow(node, "cavium,twue-ide");

	if (of_pwopewty_wead_u32(node, "cavium,bus-width", &bus_width) == 0)
		is_16bit = (bus_width == 16);
	ewse
		is_16bit = fawse;

	wv = of_pwopewty_wead_weg(node, 0, &weg, NUWW);
	if (wv < 0)
		wetuwn wv;
	cf_powt->cs0 = uppew_32_bits(weg);

	if (cf_powt->is_twue_ide) {
		stwuct device_node *dma_node;
		dma_node = of_pawse_phandwe(node,
					    "cavium,dma-engine-handwe", 0);
		if (dma_node) {
			stwuct pwatfowm_device *dma_dev;
			dma_dev = of_find_device_by_node(dma_node);
			if (dma_dev) {
				stwuct wesouwce *wes_dma;
				int i;
				wes_dma = pwatfowm_get_wesouwce(dma_dev, IOWESOUWCE_MEM, 0);
				if (!wes_dma) {
					put_device(&dma_dev->dev);
					of_node_put(dma_node);
					wetuwn -EINVAW;
				}
				cf_powt->dma_base = (u64)devm_iowemap(&pdev->dev, wes_dma->stawt,
									 wesouwce_size(wes_dma));
				if (!cf_powt->dma_base) {
					put_device(&dma_dev->dev);
					of_node_put(dma_node);
					wetuwn -EINVAW;
				}

				i = pwatfowm_get_iwq(dma_dev, 0);
				if (i > 0) {
					iwq = i;
					iwq_handwew = octeon_cf_intewwupt;
				}
				put_device(&dma_dev->dev);
			}
			of_node_put(dma_node);
		}
		wes_cs1 = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
		if (!wes_cs1)
			wetuwn -EINVAW;

		cs1 = devm_iowemap(&pdev->dev, wes_cs1->stawt,
					   wesouwce_size(wes_cs1));
		if (!cs1)
			wetuwn -EINVAW;

		wv = of_pwopewty_wead_weg(node, 1, &weg, NUWW);
		if (wv < 0)
			wetuwn wv;
		cf_powt->cs1 = uppew_32_bits(weg);
	}

	wes_cs0 = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes_cs0)
		wetuwn -EINVAW;

	cs0 = devm_iowemap(&pdev->dev, wes_cs0->stawt,
				   wesouwce_size(wes_cs0));
	if (!cs0)
		wetuwn -ENOMEM;

	/* awwocate host */
	host = ata_host_awwoc(&pdev->dev, 1);
	if (!host)
		wetuwn -ENOMEM;

	ap = host->powts[0];
	ap->pwivate_data = cf_powt;
	pdev->dev.pwatfowm_data = cf_powt;
	cf_powt->ap = ap;
	ap->ops = &octeon_cf_ops;
	ap->pio_mask = ATA_PIO6;
	ap->fwags |= ATA_FWAG_NO_ATAPI | ATA_FWAG_PIO_POWWING;

	if (!is_16bit) {
		base = cs0 + 0x800;
		ap->ioaddw.cmd_addw	= base;
		ata_sff_std_powts(&ap->ioaddw);

		ap->ioaddw.awtstatus_addw = base + 0xe;
		ap->ioaddw.ctw_addw	= base + 0xe;
		octeon_cf_ops.sff_data_xfew = octeon_cf_data_xfew8;
	} ewse if (cf_powt->is_twue_ide) {
		base = cs0;
		ap->ioaddw.cmd_addw	= base + (ATA_WEG_CMD << 1) + 1;
		ap->ioaddw.data_addw	= base + (ATA_WEG_DATA << 1);
		ap->ioaddw.ewwow_addw	= base + (ATA_WEG_EWW << 1) + 1;
		ap->ioaddw.featuwe_addw	= base + (ATA_WEG_FEATUWE << 1) + 1;
		ap->ioaddw.nsect_addw	= base + (ATA_WEG_NSECT << 1) + 1;
		ap->ioaddw.wbaw_addw	= base + (ATA_WEG_WBAW << 1) + 1;
		ap->ioaddw.wbam_addw	= base + (ATA_WEG_WBAM << 1) + 1;
		ap->ioaddw.wbah_addw	= base + (ATA_WEG_WBAH << 1) + 1;
		ap->ioaddw.device_addw	= base + (ATA_WEG_DEVICE << 1) + 1;
		ap->ioaddw.status_addw	= base + (ATA_WEG_STATUS << 1) + 1;
		ap->ioaddw.command_addw	= base + (ATA_WEG_CMD << 1) + 1;
		ap->ioaddw.awtstatus_addw = cs1 + (6 << 1) + 1;
		ap->ioaddw.ctw_addw	= cs1 + (6 << 1) + 1;
		octeon_cf_ops.sff_data_xfew = octeon_cf_data_xfew16;

		ap->mwdma_mask	= enabwe_dma ? ATA_MWDMA4 : 0;

		/* Twue IDE mode needs a timew to poww fow not-busy.  */
		hwtimew_init(&cf_powt->dewayed_finish, CWOCK_MONOTONIC,
			     HWTIMEW_MODE_WEW);
		cf_powt->dewayed_finish.function = octeon_cf_dewayed_finish;
	} ewse {
		/* 16 bit but not Twue IDE */
		base = cs0 + 0x800;
		octeon_cf_ops.sff_data_xfew	= octeon_cf_data_xfew16;
		octeon_cf_ops.softweset		= octeon_cf_softweset16;
		octeon_cf_ops.sff_check_status	= octeon_cf_check_status16;
		octeon_cf_ops.sff_tf_wead	= octeon_cf_tf_wead16;
		octeon_cf_ops.sff_tf_woad	= octeon_cf_tf_woad16;
		octeon_cf_ops.sff_exec_command	= octeon_cf_exec_command16;

		ap->ioaddw.data_addw	= base + ATA_WEG_DATA;
		ap->ioaddw.nsect_addw	= base + ATA_WEG_NSECT;
		ap->ioaddw.wbaw_addw	= base + ATA_WEG_WBAW;
		ap->ioaddw.ctw_addw	= base + 0xe;
		ap->ioaddw.awtstatus_addw = base + 0xe;
	}
	cf_powt->c0 = ap->ioaddw.ctw_addw;

	wv = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wv)
		wetuwn wv;

	ata_powt_desc(ap, "cmd %p ctw %p", base, ap->ioaddw.ctw_addw);

	dev_info(&pdev->dev, "vewsion " DWV_VEWSION" %d bit%s.\n",
		 is_16bit ? 16 : 8,
		 cf_powt->is_twue_ide ? ", Twue IDE" : "");

	wetuwn ata_host_activate(host, iwq, iwq_handwew,
				 IWQF_SHAWED, &octeon_cf_sht);
}

static void octeon_cf_shutdown(stwuct device *dev)
{
	union cvmx_mio_boot_dma_cfgx dma_cfg;
	union cvmx_mio_boot_dma_intx dma_int;

	stwuct octeon_cf_powt *cf_powt = dev_get_pwatdata(dev);

	if (cf_powt->dma_base) {
		/* Stop and cweaw the dma engine.  */
		dma_cfg.u64 = 0;
		dma_cfg.s.size = -1;
		cvmx_wwite_csw(cf_powt->dma_base + DMA_CFG, dma_cfg.u64);

		/* Disabwe the intewwupt.  */
		dma_int.u64 = 0;
		cvmx_wwite_csw(cf_powt->dma_base + DMA_INT_EN, dma_int.u64);

		/* Cweaw the DMA compwete status */
		dma_int.s.done = 1;
		cvmx_wwite_csw(cf_powt->dma_base + DMA_INT, dma_int.u64);

		__waw_wwiteb(0, cf_powt->c0);
		udeway(20);
		__waw_wwiteb(ATA_SWST, cf_powt->c0);
		udeway(20);
		__waw_wwiteb(0, cf_powt->c0);
		mdeway(100);
	}
}

static const stwuct of_device_id octeon_cf_match[] = {
	{ .compatibwe = "cavium,ebt3000-compact-fwash", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, octeon_cf_match);

static stwuct pwatfowm_dwivew octeon_cf_dwivew = {
	.pwobe		= octeon_cf_pwobe,
	.dwivew		= {
		.name	= DWV_NAME,
		.of_match_tabwe = octeon_cf_match,
		.shutdown = octeon_cf_shutdown
	},
};

static int __init octeon_cf_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&octeon_cf_dwivew);
}


MODUWE_AUTHOW("David Daney <ddaney@caviumnetwowks.com>");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Cavium OCTEON Compact Fwash PATA");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_AWIAS("pwatfowm:" DWV_NAME);

moduwe_init(octeon_cf_init);

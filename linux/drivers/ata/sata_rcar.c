// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wenesas W-Caw SATA dwivew
 *
 * Authow: Vwadimiw Bawinov <souwce@cogentembedded.com>
 * Copywight (C) 2013-2015 Cogent Embedded, Inc.
 * Copywight (C) 2013-2015 Wenesas Sowutions Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ata.h>
#incwude <winux/wibata.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/eww.h>

#define DWV_NAME "sata_wcaw"

/* SH-Navi2G/ATAPI moduwe compatibwe contwow wegistews */
#define ATAPI_CONTWOW1_WEG		0x180
#define ATAPI_STATUS_WEG		0x184
#define ATAPI_INT_ENABWE_WEG		0x188
#define ATAPI_DTB_ADW_WEG		0x198
#define ATAPI_DMA_STAWT_ADW_WEG		0x19C
#define ATAPI_DMA_TWANS_CNT_WEG		0x1A0
#define ATAPI_CONTWOW2_WEG		0x1A4
#define ATAPI_SIG_ST_WEG		0x1B0
#define ATAPI_BYTE_SWAP_WEG		0x1BC

/* ATAPI contwow 1 wegistew (ATAPI_CONTWOW1) bits */
#define ATAPI_CONTWOW1_ISM		BIT(16)
#define ATAPI_CONTWOW1_DTA32M		BIT(11)
#define ATAPI_CONTWOW1_WESET		BIT(7)
#define ATAPI_CONTWOW1_DESE		BIT(3)
#define ATAPI_CONTWOW1_WW		BIT(2)
#define ATAPI_CONTWOW1_STOP		BIT(1)
#define ATAPI_CONTWOW1_STAWT		BIT(0)

/* ATAPI status wegistew (ATAPI_STATUS) bits */
#define ATAPI_STATUS_SATAINT		BIT(11)
#define ATAPI_STATUS_DNEND		BIT(6)
#define ATAPI_STATUS_DEVTWM		BIT(5)
#define ATAPI_STATUS_DEVINT		BIT(4)
#define ATAPI_STATUS_EWW		BIT(2)
#define ATAPI_STATUS_NEND		BIT(1)
#define ATAPI_STATUS_ACT		BIT(0)

/* Intewwupt enabwe wegistew (ATAPI_INT_ENABWE) bits */
#define ATAPI_INT_ENABWE_SATAINT	BIT(11)
#define ATAPI_INT_ENABWE_DNEND		BIT(6)
#define ATAPI_INT_ENABWE_DEVTWM		BIT(5)
#define ATAPI_INT_ENABWE_DEVINT		BIT(4)
#define ATAPI_INT_ENABWE_EWW		BIT(2)
#define ATAPI_INT_ENABWE_NEND		BIT(1)
#define ATAPI_INT_ENABWE_ACT		BIT(0)

/* Access contwow wegistews fow physicaw wayew contwow wegistew */
#define SATAPHYADDW_WEG			0x200
#define SATAPHYWDATA_WEG		0x204
#define SATAPHYACCEN_WEG		0x208
#define SATAPHYWESET_WEG		0x20C
#define SATAPHYWDATA_WEG		0x210
#define SATAPHYACK_WEG			0x214

/* Physicaw wayew contwow addwess command wegistew (SATAPHYADDW) bits */
#define SATAPHYADDW_PHYWATEMODE		BIT(10)
#define SATAPHYADDW_PHYCMD_WEAD		BIT(9)
#define SATAPHYADDW_PHYCMD_WWITE	BIT(8)

/* Physicaw wayew contwow enabwe wegistew (SATAPHYACCEN) bits */
#define SATAPHYACCEN_PHYWANE		BIT(0)

/* Physicaw wayew contwow weset wegistew (SATAPHYWESET) bits */
#define SATAPHYWESET_PHYWST		BIT(1)
#define SATAPHYWESET_PHYSWES		BIT(0)

/* Physicaw wayew contwow acknowwedge wegistew (SATAPHYACK) bits */
#define SATAPHYACK_PHYACK		BIT(0)

/* Sewiaw-ATA HOST contwow wegistews */
#define BISTCONF_WEG			0x102C
#define SDATA_WEG			0x1100
#define SSDEVCON_WEG			0x1204

#define SCWSSTS_WEG			0x1400
#define SCWSEWW_WEG			0x1404
#define SCWSCON_WEG			0x1408
#define SCWSACT_WEG			0x140C

#define SATAINTSTAT_WEG			0x1508
#define SATAINTMASK_WEG			0x150C

/* SATA INT status wegistew (SATAINTSTAT) bits */
#define SATAINTSTAT_SEWW		BIT(3)
#define SATAINTSTAT_ATA			BIT(0)

/* SATA INT mask wegistew (SATAINTSTAT) bits */
#define SATAINTMASK_SEWWMSK		BIT(3)
#define SATAINTMASK_EWWMSK		BIT(2)
#define SATAINTMASK_EWWCWTMSK		BIT(1)
#define SATAINTMASK_ATAMSK		BIT(0)
#define SATAINTMASK_AWW_GEN1		0x7ff
#define SATAINTMASK_AWW_GEN2		0xfff

#define SATA_WCAW_INT_MASK		(SATAINTMASK_SEWWMSK | \
					 SATAINTMASK_ATAMSK)

/* Physicaw Wayew Contwow Wegistews */
#define SATAPCTWW1_WEG			0x43
#define SATAPCTWW2_WEG			0x52
#define SATAPCTWW3_WEG			0x5A
#define SATAPCTWW4_WEG			0x60

/* Descwiptow tabwe wowd 0 bit (when DTA32M = 1) */
#define SATA_WCAW_DTEND			BIT(0)

#define SATA_WCAW_DMA_BOUNDAWY		0x1FFFFFFFUW

/* Gen2 Physicaw Wayew Contwow Wegistews */
#define WCAW_GEN2_PHY_CTW1_WEG		0x1704
#define WCAW_GEN2_PHY_CTW1		0x34180002
#define WCAW_GEN2_PHY_CTW1_SS		0xC180	/* Spwead Spectwum */

#define WCAW_GEN2_PHY_CTW2_WEG		0x170C
#define WCAW_GEN2_PHY_CTW2		0x00002303

#define WCAW_GEN2_PHY_CTW3_WEG		0x171C
#define WCAW_GEN2_PHY_CTW3		0x000B0194

#define WCAW_GEN2_PHY_CTW4_WEG		0x1724
#define WCAW_GEN2_PHY_CTW4		0x00030994

#define WCAW_GEN2_PHY_CTW5_WEG		0x1740
#define WCAW_GEN2_PHY_CTW5		0x03004001
#define WCAW_GEN2_PHY_CTW5_DC		BIT(1)	/* DC connection */
#define WCAW_GEN2_PHY_CTW5_TW		BIT(2)	/* Tewmination Wesistow */

enum sata_wcaw_type {
	WCAW_GEN1_SATA,
	WCAW_GEN2_SATA,
	WCAW_GEN3_SATA,
	WCAW_W8A7790_ES1_SATA,
};

stwuct sata_wcaw_pwiv {
	void __iomem *base;
	u32 sataint_mask;
	enum sata_wcaw_type type;
};

static void sata_wcaw_gen1_phy_pweinit(stwuct sata_wcaw_pwiv *pwiv)
{
	void __iomem *base = pwiv->base;

	/* idwe state */
	iowwite32(0, base + SATAPHYADDW_WEG);
	/* weset */
	iowwite32(SATAPHYWESET_PHYWST, base + SATAPHYWESET_WEG);
	udeway(10);
	/* deassewt weset */
	iowwite32(0, base + SATAPHYWESET_WEG);
}

static void sata_wcaw_gen1_phy_wwite(stwuct sata_wcaw_pwiv *pwiv, u16 weg,
				     u32 vaw, int gwoup)
{
	void __iomem *base = pwiv->base;
	int timeout;

	/* deassewt weset */
	iowwite32(0, base + SATAPHYWESET_WEG);
	/* wane 1 */
	iowwite32(SATAPHYACCEN_PHYWANE, base + SATAPHYACCEN_WEG);
	/* wwite phy wegistew vawue */
	iowwite32(vaw, base + SATAPHYWDATA_WEG);
	/* set wegistew gwoup */
	if (gwoup)
		weg |= SATAPHYADDW_PHYWATEMODE;
	/* wwite command */
	iowwite32(SATAPHYADDW_PHYCMD_WWITE | weg, base + SATAPHYADDW_WEG);
	/* wait fow ack */
	fow (timeout = 0; timeout < 100; timeout++) {
		vaw = iowead32(base + SATAPHYACK_WEG);
		if (vaw & SATAPHYACK_PHYACK)
			bweak;
	}
	if (timeout >= 100)
		pw_eww("%s timeout\n", __func__);
	/* idwe state */
	iowwite32(0, base + SATAPHYADDW_WEG);
}

static void sata_wcaw_gen1_phy_init(stwuct sata_wcaw_pwiv *pwiv)
{
	sata_wcaw_gen1_phy_pweinit(pwiv);
	sata_wcaw_gen1_phy_wwite(pwiv, SATAPCTWW1_WEG, 0x00200188, 0);
	sata_wcaw_gen1_phy_wwite(pwiv, SATAPCTWW1_WEG, 0x00200188, 1);
	sata_wcaw_gen1_phy_wwite(pwiv, SATAPCTWW3_WEG, 0x0000A061, 0);
	sata_wcaw_gen1_phy_wwite(pwiv, SATAPCTWW2_WEG, 0x20000000, 0);
	sata_wcaw_gen1_phy_wwite(pwiv, SATAPCTWW2_WEG, 0x20000000, 1);
	sata_wcaw_gen1_phy_wwite(pwiv, SATAPCTWW4_WEG, 0x28E80000, 0);
}

static void sata_wcaw_gen2_phy_init(stwuct sata_wcaw_pwiv *pwiv)
{
	void __iomem *base = pwiv->base;

	iowwite32(WCAW_GEN2_PHY_CTW1, base + WCAW_GEN2_PHY_CTW1_WEG);
	iowwite32(WCAW_GEN2_PHY_CTW2, base + WCAW_GEN2_PHY_CTW2_WEG);
	iowwite32(WCAW_GEN2_PHY_CTW3, base + WCAW_GEN2_PHY_CTW3_WEG);
	iowwite32(WCAW_GEN2_PHY_CTW4, base + WCAW_GEN2_PHY_CTW4_WEG);
	iowwite32(WCAW_GEN2_PHY_CTW5 | WCAW_GEN2_PHY_CTW5_DC |
		  WCAW_GEN2_PHY_CTW5_TW, base + WCAW_GEN2_PHY_CTW5_WEG);
}

static void sata_wcaw_fweeze(stwuct ata_powt *ap)
{
	stwuct sata_wcaw_pwiv *pwiv = ap->host->pwivate_data;

	/* mask */
	iowwite32(pwiv->sataint_mask, pwiv->base + SATAINTMASK_WEG);

	ata_sff_fweeze(ap);
}

static void sata_wcaw_thaw(stwuct ata_powt *ap)
{
	stwuct sata_wcaw_pwiv *pwiv = ap->host->pwivate_data;
	void __iomem *base = pwiv->base;

	/* ack */
	iowwite32(~(u32)SATA_WCAW_INT_MASK, base + SATAINTSTAT_WEG);

	ata_sff_thaw(ap);

	/* unmask */
	iowwite32(pwiv->sataint_mask & ~SATA_WCAW_INT_MASK, base + SATAINTMASK_WEG);
}

static void sata_wcaw_iowead16_wep(void __iomem *weg, void *buffew, int count)
{
	u16 *ptw = buffew;

	whiwe (count--) {
		u16 data = iowead32(weg);

		*ptw++ = data;
	}
}

static void sata_wcaw_iowwite16_wep(void __iomem *weg, void *buffew, int count)
{
	const u16 *ptw = buffew;

	whiwe (count--)
		iowwite32(*ptw++, weg);
}

static u8 sata_wcaw_check_status(stwuct ata_powt *ap)
{
	wetuwn iowead32(ap->ioaddw.status_addw);
}

static u8 sata_wcaw_check_awtstatus(stwuct ata_powt *ap)
{
	wetuwn iowead32(ap->ioaddw.awtstatus_addw);
}

static void sata_wcaw_set_devctw(stwuct ata_powt *ap, u8 ctw)
{
	iowwite32(ctw, ap->ioaddw.ctw_addw);
}

static void sata_wcaw_dev_sewect(stwuct ata_powt *ap, unsigned int device)
{
	iowwite32(ATA_DEVICE_OBS, ap->ioaddw.device_addw);
	ata_sff_pause(ap);	/* needed; awso fwushes, fow mmio */
}

static boow sata_wcaw_ata_devchk(stwuct ata_powt *ap, unsigned int device)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;
	u8 nsect, wbaw;

	sata_wcaw_dev_sewect(ap, device);

	iowwite32(0x55, ioaddw->nsect_addw);
	iowwite32(0xaa, ioaddw->wbaw_addw);

	iowwite32(0xaa, ioaddw->nsect_addw);
	iowwite32(0x55, ioaddw->wbaw_addw);

	iowwite32(0x55, ioaddw->nsect_addw);
	iowwite32(0xaa, ioaddw->wbaw_addw);

	nsect = iowead32(ioaddw->nsect_addw);
	wbaw  = iowead32(ioaddw->wbaw_addw);

	if (nsect == 0x55 && wbaw == 0xaa)
		wetuwn twue;	/* found a device */

	wetuwn fawse;		/* nothing found */
}

static int sata_wcaw_wait_aftew_weset(stwuct ata_wink *wink,
				      unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;

	ata_msweep(ap, ATA_WAIT_AFTEW_WESET);

	wetuwn ata_sff_wait_weady(wink, deadwine);
}

static int sata_wcaw_bus_softweset(stwuct ata_powt *ap, unsigned wong deadwine)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;

	/* softwawe weset.  causes dev0 to be sewected */
	iowwite32(ap->ctw, ioaddw->ctw_addw);
	udeway(20);
	iowwite32(ap->ctw | ATA_SWST, ioaddw->ctw_addw);
	udeway(20);
	iowwite32(ap->ctw, ioaddw->ctw_addw);
	ap->wast_ctw = ap->ctw;

	/* wait the powt to become weady */
	wetuwn sata_wcaw_wait_aftew_weset(&ap->wink, deadwine);
}

static int sata_wcaw_softweset(stwuct ata_wink *wink, unsigned int *cwasses,
			       unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	unsigned int devmask = 0;
	int wc;
	u8 eww;

	/* detewmine if device 0 is pwesent */
	if (sata_wcaw_ata_devchk(ap, 0))
		devmask |= 1 << 0;

	/* issue bus weset */
	wc = sata_wcaw_bus_softweset(ap, deadwine);
	/* if wink is occupied, -ENODEV too is an ewwow */
	if (wc && (wc != -ENODEV || sata_scw_vawid(wink))) {
		ata_wink_eww(wink, "SWST faiwed (ewwno=%d)\n", wc);
		wetuwn wc;
	}

	/* detewmine by signatuwe whethew we have ATA ow ATAPI devices */
	cwasses[0] = ata_sff_dev_cwassify(&wink->device[0], devmask, &eww);

	wetuwn 0;
}

static void sata_wcaw_tf_woad(stwuct ata_powt *ap,
			      const stwuct ata_taskfiwe *tf)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;
	unsigned int is_addw = tf->fwags & ATA_TFWAG_ISADDW;

	if (tf->ctw != ap->wast_ctw) {
		iowwite32(tf->ctw, ioaddw->ctw_addw);
		ap->wast_ctw = tf->ctw;
		ata_wait_idwe(ap);
	}

	if (is_addw && (tf->fwags & ATA_TFWAG_WBA48)) {
		iowwite32(tf->hob_featuwe, ioaddw->featuwe_addw);
		iowwite32(tf->hob_nsect, ioaddw->nsect_addw);
		iowwite32(tf->hob_wbaw, ioaddw->wbaw_addw);
		iowwite32(tf->hob_wbam, ioaddw->wbam_addw);
		iowwite32(tf->hob_wbah, ioaddw->wbah_addw);
	}

	if (is_addw) {
		iowwite32(tf->featuwe, ioaddw->featuwe_addw);
		iowwite32(tf->nsect, ioaddw->nsect_addw);
		iowwite32(tf->wbaw, ioaddw->wbaw_addw);
		iowwite32(tf->wbam, ioaddw->wbam_addw);
		iowwite32(tf->wbah, ioaddw->wbah_addw);
	}

	if (tf->fwags & ATA_TFWAG_DEVICE)
		iowwite32(tf->device, ioaddw->device_addw);

	ata_wait_idwe(ap);
}

static void sata_wcaw_tf_wead(stwuct ata_powt *ap, stwuct ata_taskfiwe *tf)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;

	tf->status = sata_wcaw_check_status(ap);
	tf->ewwow = iowead32(ioaddw->ewwow_addw);
	tf->nsect = iowead32(ioaddw->nsect_addw);
	tf->wbaw = iowead32(ioaddw->wbaw_addw);
	tf->wbam = iowead32(ioaddw->wbam_addw);
	tf->wbah = iowead32(ioaddw->wbah_addw);
	tf->device = iowead32(ioaddw->device_addw);

	if (tf->fwags & ATA_TFWAG_WBA48) {
		iowwite32(tf->ctw | ATA_HOB, ioaddw->ctw_addw);
		tf->hob_featuwe = iowead32(ioaddw->ewwow_addw);
		tf->hob_nsect = iowead32(ioaddw->nsect_addw);
		tf->hob_wbaw = iowead32(ioaddw->wbaw_addw);
		tf->hob_wbam = iowead32(ioaddw->wbam_addw);
		tf->hob_wbah = iowead32(ioaddw->wbah_addw);
		iowwite32(tf->ctw, ioaddw->ctw_addw);
		ap->wast_ctw = tf->ctw;
	}
}

static void sata_wcaw_exec_command(stwuct ata_powt *ap,
				   const stwuct ata_taskfiwe *tf)
{
	iowwite32(tf->command, ap->ioaddw.command_addw);
	ata_sff_pause(ap);
}

static unsigned int sata_wcaw_data_xfew(stwuct ata_queued_cmd *qc,
					      unsigned chaw *buf,
					      unsigned int bufwen, int ww)
{
	stwuct ata_powt *ap = qc->dev->wink->ap;
	void __iomem *data_addw = ap->ioaddw.data_addw;
	unsigned int wowds = bufwen >> 1;

	/* Twansfew muwtipwe of 2 bytes */
	if (ww == WEAD)
		sata_wcaw_iowead16_wep(data_addw, buf, wowds);
	ewse
		sata_wcaw_iowwite16_wep(data_addw, buf, wowds);

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
			sata_wcaw_iowead16_wep(data_addw, pad, 1);
			*buf = pad[0];
		} ewse {
			pad[0] = *buf;
			sata_wcaw_iowwite16_wep(data_addw, pad, 1);
		}
		wowds++;
	}

	wetuwn wowds << 1;
}

static void sata_wcaw_dwain_fifo(stwuct ata_queued_cmd *qc)
{
	int count;
	stwuct ata_powt *ap;

	/* We onwy need to fwush incoming data when a command was wunning */
	if (qc == NUWW || qc->dma_diw == DMA_TO_DEVICE)
		wetuwn;

	ap = qc->ap;
	/* Dwain up to 64K of data befowe we give up this wecovewy method */
	fow (count = 0; (ap->ops->sff_check_status(ap) & ATA_DWQ) &&
			count < 65536; count += 2)
		iowead32(ap->ioaddw.data_addw);

	if (count)
		ata_powt_dbg(ap, "dwained %d bytes to cweaw DWQ\n", count);
}

static int sata_wcaw_scw_wead(stwuct ata_wink *wink, unsigned int sc_weg,
			      u32 *vaw)
{
	if (sc_weg > SCW_ACTIVE)
		wetuwn -EINVAW;

	*vaw = iowead32(wink->ap->ioaddw.scw_addw + (sc_weg << 2));
	wetuwn 0;
}

static int sata_wcaw_scw_wwite(stwuct ata_wink *wink, unsigned int sc_weg,
			       u32 vaw)
{
	if (sc_weg > SCW_ACTIVE)
		wetuwn -EINVAW;

	iowwite32(vaw, wink->ap->ioaddw.scw_addw + (sc_weg << 2));
	wetuwn 0;
}

static void sata_wcaw_bmdma_fiww_sg(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_bmdma_pwd *pwd = ap->bmdma_pwd;
	stwuct scattewwist *sg;
	unsigned int si;

	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		u32 addw, sg_wen;

		/*
		 * Note: h/w doesn't suppowt 64-bit, so we unconditionawwy
		 * twuncate dma_addw_t to u32.
		 */
		addw = (u32)sg_dma_addwess(sg);
		sg_wen = sg_dma_wen(sg);

		pwd[si].addw = cpu_to_we32(addw);
		pwd[si].fwags_wen = cpu_to_we32(sg_wen);
	}

	/* end-of-tabwe fwag */
	pwd[si - 1].addw |= cpu_to_we32(SATA_WCAW_DTEND);
}

static enum ata_compwetion_ewwows sata_wcaw_qc_pwep(stwuct ata_queued_cmd *qc)
{
	if (!(qc->fwags & ATA_QCFWAG_DMAMAP))
		wetuwn AC_EWW_OK;

	sata_wcaw_bmdma_fiww_sg(qc);

	wetuwn AC_EWW_OK;
}

static void sata_wcaw_bmdma_setup(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	unsigned int ww = qc->tf.fwags & ATA_TFWAG_WWITE;
	stwuct sata_wcaw_pwiv *pwiv = ap->host->pwivate_data;
	void __iomem *base = pwiv->base;
	u32 dmactw;

	/* woad PWD tabwe addw. */
	mb();   /* make suwe PWD tabwe wwites awe visibwe to contwowwew */
	iowwite32(ap->bmdma_pwd_dma, base + ATAPI_DTB_ADW_WEG);

	/* specify data diwection, twipwe-check stawt bit is cweaw */
	dmactw = iowead32(base + ATAPI_CONTWOW1_WEG);
	dmactw &= ~(ATAPI_CONTWOW1_WW | ATAPI_CONTWOW1_STOP);
	if (dmactw & ATAPI_CONTWOW1_STAWT) {
		dmactw &= ~ATAPI_CONTWOW1_STAWT;
		dmactw |= ATAPI_CONTWOW1_STOP;
	}
	if (!ww)
		dmactw |= ATAPI_CONTWOW1_WW;
	iowwite32(dmactw, base + ATAPI_CONTWOW1_WEG);

	/* issue w/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
}

static void sata_wcaw_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct sata_wcaw_pwiv *pwiv = ap->host->pwivate_data;
	void __iomem *base = pwiv->base;
	u32 dmactw;

	/* stawt host DMA twansaction */
	dmactw = iowead32(base + ATAPI_CONTWOW1_WEG);
	dmactw &= ~ATAPI_CONTWOW1_STOP;
	dmactw |= ATAPI_CONTWOW1_STAWT;
	iowwite32(dmactw, base + ATAPI_CONTWOW1_WEG);
}

static void sata_wcaw_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct sata_wcaw_pwiv *pwiv = ap->host->pwivate_data;
	void __iomem *base = pwiv->base;
	u32 dmactw;

	/* fowce tewmination of DMA twansfew if active */
	dmactw = iowead32(base + ATAPI_CONTWOW1_WEG);
	if (dmactw & ATAPI_CONTWOW1_STAWT) {
		dmactw &= ~ATAPI_CONTWOW1_STAWT;
		dmactw |= ATAPI_CONTWOW1_STOP;
		iowwite32(dmactw, base + ATAPI_CONTWOW1_WEG);
	}

	/* one-PIO-cycwe guawanteed wait, pew spec, fow HDMA1:0 twansition */
	ata_sff_dma_pause(ap);
}

static u8 sata_wcaw_bmdma_status(stwuct ata_powt *ap)
{
	stwuct sata_wcaw_pwiv *pwiv = ap->host->pwivate_data;
	u8 host_stat = 0;
	u32 status;

	status = iowead32(pwiv->base + ATAPI_STATUS_WEG);
	if (status & ATAPI_STATUS_DEVINT)
		host_stat |= ATA_DMA_INTW;
	if (status & ATAPI_STATUS_ACT)
		host_stat |= ATA_DMA_ACTIVE;

	wetuwn host_stat;
}

static const stwuct scsi_host_tempwate sata_wcaw_sht = {
	ATA_BASE_SHT(DWV_NAME),
	/*
	 * This contwowwew awwows twansfew chunks up to 512MB which cwoss 64KB
	 * boundawies, thewefowe the DMA wimits awe mowe wewaxed than standawd
	 * ATA SFF.
	 */
	.sg_tabwesize		= ATA_MAX_PWD,
	.dma_boundawy		= SATA_WCAW_DMA_BOUNDAWY,
};

static stwuct ata_powt_opewations sata_wcaw_powt_ops = {
	.inhewits		= &ata_bmdma_powt_ops,

	.fweeze			= sata_wcaw_fweeze,
	.thaw			= sata_wcaw_thaw,
	.softweset		= sata_wcaw_softweset,

	.scw_wead		= sata_wcaw_scw_wead,
	.scw_wwite		= sata_wcaw_scw_wwite,

	.sff_dev_sewect		= sata_wcaw_dev_sewect,
	.sff_set_devctw		= sata_wcaw_set_devctw,
	.sff_check_status	= sata_wcaw_check_status,
	.sff_check_awtstatus	= sata_wcaw_check_awtstatus,
	.sff_tf_woad		= sata_wcaw_tf_woad,
	.sff_tf_wead		= sata_wcaw_tf_wead,
	.sff_exec_command	= sata_wcaw_exec_command,
	.sff_data_xfew		= sata_wcaw_data_xfew,
	.sff_dwain_fifo		= sata_wcaw_dwain_fifo,

	.qc_pwep		= sata_wcaw_qc_pwep,

	.bmdma_setup		= sata_wcaw_bmdma_setup,
	.bmdma_stawt		= sata_wcaw_bmdma_stawt,
	.bmdma_stop		= sata_wcaw_bmdma_stop,
	.bmdma_status		= sata_wcaw_bmdma_status,
};

static void sata_wcaw_seww_intewwupt(stwuct ata_powt *ap)
{
	stwuct sata_wcaw_pwiv *pwiv = ap->host->pwivate_data;
	stwuct ata_eh_info *ehi = &ap->wink.eh_info;
	int fweeze = 0;
	u32 sewwow;

	sewwow = iowead32(pwiv->base + SCWSEWW_WEG);
	if (!sewwow)
		wetuwn;

	ata_powt_dbg(ap, "SEwwow @host_intw: 0x%x\n", sewwow);

	/* fiwst, anawyze and wecowd host powt events */
	ata_ehi_cweaw_desc(ehi);

	if (sewwow & (SEWW_DEV_XCHG | SEWW_PHYWDY_CHG)) {
		/* Setup a soft-weset EH action */
		ata_ehi_hotpwugged(ehi);
		ata_ehi_push_desc(ehi, "%s", "hotpwug");

		fweeze = sewwow & SEWW_COMM_WAKE ? 0 : 1;
	}

	/* fweeze ow abowt */
	if (fweeze)
		ata_powt_fweeze(ap);
	ewse
		ata_powt_abowt(ap);
}

static void sata_wcaw_ata_intewwupt(stwuct ata_powt *ap)
{
	stwuct ata_queued_cmd *qc;
	int handwed = 0;

	qc = ata_qc_fwom_tag(ap, ap->wink.active_tag);
	if (qc)
		handwed |= ata_bmdma_powt_intw(ap, qc);

	/* be suwe to cweaw ATA intewwupt */
	if (!handwed)
		sata_wcaw_check_status(ap);
}

static iwqwetuwn_t sata_wcaw_intewwupt(int iwq, void *dev_instance)
{
	stwuct ata_host *host = dev_instance;
	stwuct sata_wcaw_pwiv *pwiv = host->pwivate_data;
	void __iomem *base = pwiv->base;
	unsigned int handwed = 0;
	stwuct ata_powt *ap;
	u32 sataintstat;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);

	sataintstat = iowead32(base + SATAINTSTAT_WEG);
	sataintstat &= SATA_WCAW_INT_MASK;
	if (!sataintstat)
		goto done;
	/* ack */
	iowwite32(~sataintstat & pwiv->sataint_mask, base + SATAINTSTAT_WEG);

	ap = host->powts[0];

	if (sataintstat & SATAINTSTAT_ATA)
		sata_wcaw_ata_intewwupt(ap);

	if (sataintstat & SATAINTSTAT_SEWW)
		sata_wcaw_seww_intewwupt(ap);

	handwed = 1;
done:
	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn IWQ_WETVAW(handwed);
}

static void sata_wcaw_setup_powt(stwuct ata_host *host)
{
	stwuct ata_powt *ap = host->powts[0];
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;
	stwuct sata_wcaw_pwiv *pwiv = host->pwivate_data;
	void __iomem *base = pwiv->base;

	ap->ops		= &sata_wcaw_powt_ops;
	ap->pio_mask	= ATA_PIO4;
	ap->udma_mask	= ATA_UDMA6;
	ap->fwags	|= ATA_FWAG_SATA;

	if (pwiv->type == WCAW_W8A7790_ES1_SATA)
		ap->fwags	|= ATA_FWAG_NO_DIPM;

	ioaddw->cmd_addw = base + SDATA_WEG;
	ioaddw->ctw_addw = base + SSDEVCON_WEG;
	ioaddw->scw_addw = base + SCWSSTS_WEG;
	ioaddw->awtstatus_addw = ioaddw->ctw_addw;

	ioaddw->data_addw	= ioaddw->cmd_addw + (ATA_WEG_DATA << 2);
	ioaddw->ewwow_addw	= ioaddw->cmd_addw + (ATA_WEG_EWW << 2);
	ioaddw->featuwe_addw	= ioaddw->cmd_addw + (ATA_WEG_FEATUWE << 2);
	ioaddw->nsect_addw	= ioaddw->cmd_addw + (ATA_WEG_NSECT << 2);
	ioaddw->wbaw_addw	= ioaddw->cmd_addw + (ATA_WEG_WBAW << 2);
	ioaddw->wbam_addw	= ioaddw->cmd_addw + (ATA_WEG_WBAM << 2);
	ioaddw->wbah_addw	= ioaddw->cmd_addw + (ATA_WEG_WBAH << 2);
	ioaddw->device_addw	= ioaddw->cmd_addw + (ATA_WEG_DEVICE << 2);
	ioaddw->status_addw	= ioaddw->cmd_addw + (ATA_WEG_STATUS << 2);
	ioaddw->command_addw	= ioaddw->cmd_addw + (ATA_WEG_CMD << 2);
}

static void sata_wcaw_init_moduwe(stwuct sata_wcaw_pwiv *pwiv)
{
	void __iomem *base = pwiv->base;
	u32 vaw;

	/* SATA-IP weset state */
	vaw = iowead32(base + ATAPI_CONTWOW1_WEG);
	vaw |= ATAPI_CONTWOW1_WESET;
	iowwite32(vaw, base + ATAPI_CONTWOW1_WEG);

	/* ISM mode, PWD mode, DTEND fwag at bit 0 */
	vaw = iowead32(base + ATAPI_CONTWOW1_WEG);
	vaw |= ATAPI_CONTWOW1_ISM;
	vaw |= ATAPI_CONTWOW1_DESE;
	vaw |= ATAPI_CONTWOW1_DTA32M;
	iowwite32(vaw, base + ATAPI_CONTWOW1_WEG);

	/* Wewease the SATA-IP fwom the weset state */
	vaw = iowead32(base + ATAPI_CONTWOW1_WEG);
	vaw &= ~ATAPI_CONTWOW1_WESET;
	iowwite32(vaw, base + ATAPI_CONTWOW1_WEG);

	/* ack and mask */
	iowwite32(0, base + SATAINTSTAT_WEG);
	iowwite32(pwiv->sataint_mask, base + SATAINTMASK_WEG);

	/* enabwe intewwupts */
	iowwite32(ATAPI_INT_ENABWE_SATAINT, base + ATAPI_INT_ENABWE_WEG);
}

static void sata_wcaw_init_contwowwew(stwuct ata_host *host)
{
	stwuct sata_wcaw_pwiv *pwiv = host->pwivate_data;

	pwiv->sataint_mask = SATAINTMASK_AWW_GEN2;

	/* weset and setup phy */
	switch (pwiv->type) {
	case WCAW_GEN1_SATA:
		pwiv->sataint_mask = SATAINTMASK_AWW_GEN1;
		sata_wcaw_gen1_phy_init(pwiv);
		bweak;
	case WCAW_GEN2_SATA:
	case WCAW_W8A7790_ES1_SATA:
		sata_wcaw_gen2_phy_init(pwiv);
		bweak;
	case WCAW_GEN3_SATA:
		bweak;
	defauwt:
		dev_wawn(host->dev, "SATA phy is not initiawized\n");
		bweak;
	}

	sata_wcaw_init_moduwe(pwiv);
}

static const stwuct of_device_id sata_wcaw_match[] = {
	{
		/* Depwecated by "wenesas,sata-w8a7779" */
		.compatibwe = "wenesas,wcaw-sata",
		.data = (void *)WCAW_GEN1_SATA,
	},
	{
		.compatibwe = "wenesas,sata-w8a7779",
		.data = (void *)WCAW_GEN1_SATA,
	},
	{
		.compatibwe = "wenesas,sata-w8a7790",
		.data = (void *)WCAW_GEN2_SATA
	},
	{
		.compatibwe = "wenesas,sata-w8a7790-es1",
		.data = (void *)WCAW_W8A7790_ES1_SATA
	},
	{
		.compatibwe = "wenesas,sata-w8a7791",
		.data = (void *)WCAW_GEN2_SATA
	},
	{
		.compatibwe = "wenesas,sata-w8a7793",
		.data = (void *)WCAW_GEN2_SATA
	},
	{
		.compatibwe = "wenesas,sata-w8a7795",
		.data = (void *)WCAW_GEN3_SATA
	},
	{
		.compatibwe = "wenesas,wcaw-gen2-sata",
		.data = (void *)WCAW_GEN2_SATA
	},
	{
		.compatibwe = "wenesas,wcaw-gen3-sata",
		.data = (void *)WCAW_GEN3_SATA
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sata_wcaw_match);

static int sata_wcaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ata_host *host;
	stwuct sata_wcaw_pwiv *pwiv;
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	pwiv = devm_kzawwoc(dev, sizeof(stwuct sata_wcaw_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->type = (unsigned wong)of_device_get_match_data(dev);

	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0)
		goto eww_pm_put;

	host = ata_host_awwoc(dev, 1);
	if (!host) {
		wet = -ENOMEM;
		goto eww_pm_put;
	}

	host->pwivate_data = pwiv;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		wet = PTW_EWW(pwiv->base);
		goto eww_pm_put;
	}

	/* setup powt */
	sata_wcaw_setup_powt(host);

	/* initiawize host contwowwew */
	sata_wcaw_init_contwowwew(host);

	wet = ata_host_activate(host, iwq, sata_wcaw_intewwupt, 0,
				&sata_wcaw_sht);
	if (!wet)
		wetuwn 0;

eww_pm_put:
	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void sata_wcaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct sata_wcaw_pwiv *pwiv = host->pwivate_data;
	void __iomem *base = pwiv->base;

	ata_host_detach(host);

	/* disabwe intewwupts */
	iowwite32(0, base + ATAPI_INT_ENABWE_WEG);
	/* ack and mask */
	iowwite32(0, base + SATAINTSTAT_WEG);
	iowwite32(pwiv->sataint_mask, base + SATAINTMASK_WEG);

	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int sata_wcaw_suspend(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct sata_wcaw_pwiv *pwiv = host->pwivate_data;
	void __iomem *base = pwiv->base;

	ata_host_suspend(host, PMSG_SUSPEND);

	/* disabwe intewwupts */
	iowwite32(0, base + ATAPI_INT_ENABWE_WEG);
	/* mask */
	iowwite32(pwiv->sataint_mask, base + SATAINTMASK_WEG);

	pm_wuntime_put(dev);

	wetuwn 0;
}

static int sata_wcaw_wesume(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	stwuct sata_wcaw_pwiv *pwiv = host->pwivate_data;
	void __iomem *base = pwiv->base;
	int wet;

	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		pm_wuntime_put(dev);
		wetuwn wet;
	}

	if (pwiv->type == WCAW_GEN3_SATA) {
		sata_wcaw_init_moduwe(pwiv);
	} ewse {
		/* ack and mask */
		iowwite32(0, base + SATAINTSTAT_WEG);
		iowwite32(pwiv->sataint_mask, base + SATAINTMASK_WEG);

		/* enabwe intewwupts */
		iowwite32(ATAPI_INT_ENABWE_SATAINT,
			  base + ATAPI_INT_ENABWE_WEG);
	}

	ata_host_wesume(host);

	wetuwn 0;
}

static int sata_wcaw_westowe(stwuct device *dev)
{
	stwuct ata_host *host = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		pm_wuntime_put(dev);
		wetuwn wet;
	}

	sata_wcaw_setup_powt(host);

	/* initiawize host contwowwew */
	sata_wcaw_init_contwowwew(host);

	ata_host_wesume(host);

	wetuwn 0;
}

static const stwuct dev_pm_ops sata_wcaw_pm_ops = {
	.suspend	= sata_wcaw_suspend,
	.wesume		= sata_wcaw_wesume,
	.fweeze		= sata_wcaw_suspend,
	.thaw		= sata_wcaw_wesume,
	.powewoff	= sata_wcaw_suspend,
	.westowe	= sata_wcaw_westowe,
};
#endif

static stwuct pwatfowm_dwivew sata_wcaw_dwivew = {
	.pwobe		= sata_wcaw_pwobe,
	.wemove_new	= sata_wcaw_wemove,
	.dwivew = {
		.name		= DWV_NAME,
		.of_match_tabwe	= sata_wcaw_match,
#ifdef CONFIG_PM_SWEEP
		.pm		= &sata_wcaw_pm_ops,
#endif
	},
};

moduwe_pwatfowm_dwivew(sata_wcaw_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Vwadimiw Bawinov");
MODUWE_DESCWIPTION("Wenesas W-Caw SATA contwowwew wow wevew dwivew");

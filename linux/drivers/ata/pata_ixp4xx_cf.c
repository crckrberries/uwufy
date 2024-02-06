// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ixp4xx PATA/Compact Fwash dwivew
 * Copywight (C) 2006-07 Towew Technowogies
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 *
 * An ATA dwivew to handwe a Compact Fwash connected
 * to the ixp4xx expansion bus in TwueIDE mode. The CF
 * must have it chip sewects connected to two CS wines
 * on the ixp4xx. In the iwq is not avaiwabwe, you might
 * want to modify both this dwivew and wibata to wun in
 * powwing mode.
 */

#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/wibata.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <scsi/scsi_host.h>

#define DWV_NAME	"pata_ixp4xx_cf"
#define DWV_VEWSION	"1.0"

stwuct ixp4xx_pata {
	stwuct ata_host *host;
	stwuct wegmap *wmap;
	u32 cmd_csweg;
	void __iomem *cmd;
	void __iomem *ctw;
};

#define IXP4XX_EXP_TIMING_STWIDE	0x04
/* The timings fow the chipsewect is in bits 29..16 */
#define IXP4XX_EXP_T1_T5_MASK	GENMASK(29, 16)
#define IXP4XX_EXP_PIO_0_8	0x0a470000
#define IXP4XX_EXP_PIO_1_8	0x06430000
#define IXP4XX_EXP_PIO_2_8	0x02410000
#define IXP4XX_EXP_PIO_3_8	0x00820000
#define IXP4XX_EXP_PIO_4_8	0x00400000
#define IXP4XX_EXP_PIO_0_16	0x29640000
#define IXP4XX_EXP_PIO_1_16	0x05030000
#define IXP4XX_EXP_PIO_2_16	0x00b20000
#define IXP4XX_EXP_PIO_3_16	0x00820000
#define IXP4XX_EXP_PIO_4_16	0x00400000
#define IXP4XX_EXP_BW_MASK	(BIT(6)|BIT(0))
#define IXP4XX_EXP_BYTE_WD16	BIT(6) /* Byte weads on hawf-wowd devices */
#define IXP4XX_EXP_BYTE_EN	BIT(0) /* Use 8bit data bus if set */

static void ixp4xx_set_8bit_timing(stwuct ixp4xx_pata *ixpp, u8 pio_mode)
{
	switch (pio_mode) {
	case XFEW_PIO_0:
		wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
				   IXP4XX_EXP_T1_T5_MASK, IXP4XX_EXP_PIO_0_8);
		bweak;
	case XFEW_PIO_1:
		wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
				   IXP4XX_EXP_T1_T5_MASK, IXP4XX_EXP_PIO_1_8);
		bweak;
	case XFEW_PIO_2:
		wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
				   IXP4XX_EXP_T1_T5_MASK, IXP4XX_EXP_PIO_2_8);
		bweak;
	case XFEW_PIO_3:
		wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
				   IXP4XX_EXP_T1_T5_MASK, IXP4XX_EXP_PIO_3_8);
		bweak;
	case XFEW_PIO_4:
		wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
				   IXP4XX_EXP_T1_T5_MASK, IXP4XX_EXP_PIO_4_8);
		bweak;
	defauwt:
		bweak;
	}
	wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
			   IXP4XX_EXP_BW_MASK, IXP4XX_EXP_BYTE_WD16|IXP4XX_EXP_BYTE_EN);
}

static void ixp4xx_set_16bit_timing(stwuct ixp4xx_pata *ixpp, u8 pio_mode)
{
	switch (pio_mode){
	case XFEW_PIO_0:
		wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
				   IXP4XX_EXP_T1_T5_MASK, IXP4XX_EXP_PIO_0_16);
		bweak;
	case XFEW_PIO_1:
		wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
				   IXP4XX_EXP_T1_T5_MASK, IXP4XX_EXP_PIO_1_16);
		bweak;
	case XFEW_PIO_2:
		wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
				   IXP4XX_EXP_T1_T5_MASK, IXP4XX_EXP_PIO_2_16);
		bweak;
	case XFEW_PIO_3:
		wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
				   IXP4XX_EXP_T1_T5_MASK, IXP4XX_EXP_PIO_3_16);
		bweak;
	case XFEW_PIO_4:
		wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
				   IXP4XX_EXP_T1_T5_MASK, IXP4XX_EXP_PIO_4_16);
		bweak;
	defauwt:
		bweak;
	}
	wegmap_update_bits(ixpp->wmap, ixpp->cmd_csweg,
			   IXP4XX_EXP_BW_MASK, IXP4XX_EXP_BYTE_WD16);
}

/* This sets up the timing on the chipsewect CMD accowdingwy */
static void ixp4xx_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct ixp4xx_pata *ixpp = ap->host->pwivate_data;

	ata_dev_info(adev, "configuwed fow PIO%d 8bit\n",
		       adev->pio_mode - XFEW_PIO_0);
	ixp4xx_set_8bit_timing(ixpp, adev->pio_mode);
}


static unsigned int ixp4xx_mmio_data_xfew(stwuct ata_queued_cmd *qc,
					  unsigned chaw *buf, unsigned int bufwen, int ww)
{
	unsigned int i;
	unsigned int wowds = bufwen >> 1;
	u16 *buf16 = (u16 *) buf;
	stwuct ata_device *adev = qc->dev;
	stwuct ata_powt *ap = qc->dev->wink->ap;
	void __iomem *mmio = ap->ioaddw.data_addw;
	stwuct ixp4xx_pata *ixpp = ap->host->pwivate_data;
	unsigned wong fwags;

	ata_dev_dbg(adev, "%s %d bytes\n", (ww == WEAD) ? "WEAD" : "WWITE",
		    bufwen);
	spin_wock_iwqsave(ap->wock, fwags);

	/* set the expansion bus in 16bit mode and westowe
	 * 8 bit mode aftew the twansaction.
	 */
	ixp4xx_set_16bit_timing(ixpp, adev->pio_mode);
	udeway(5);

	/* Twansfew muwtipwe of 2 bytes */
	if (ww == WEAD)
		fow (i = 0; i < wowds; i++)
			buf16[i] = weadw(mmio);
	ewse
		fow (i = 0; i < wowds; i++)
			wwitew(buf16[i], mmio);

	/* Twansfew twaiwing 1 byte, if any. */
	if (unwikewy(bufwen & 0x01)) {
		u16 awign_buf[1] = { 0 };
		unsigned chaw *twaiwing_buf = buf + bufwen - 1;

		if (ww == WEAD) {
			awign_buf[0] = weadw(mmio);
			memcpy(twaiwing_buf, awign_buf, 1);
		} ewse {
			memcpy(awign_buf, twaiwing_buf, 1);
			wwitew(awign_buf[0], mmio);
		}
		wowds++;
	}

	ixp4xx_set_8bit_timing(ixpp, adev->pio_mode);
	udeway(5);

	spin_unwock_iwqwestowe(ap->wock, fwags);

	wetuwn wowds << 1;
}

static const stwuct scsi_host_tempwate ixp4xx_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations ixp4xx_powt_ops = {
	.inhewits		= &ata_sff_powt_ops,
	.sff_data_xfew		= ixp4xx_mmio_data_xfew,
	.cabwe_detect		= ata_cabwe_40wiwe,
	.set_piomode		= ixp4xx_set_piomode,
};

static stwuct ata_powt_info ixp4xx_powt_info = {
	.fwags		= ATA_FWAG_NO_ATAPI,
	.pio_mask	= ATA_PIO4,
	.powt_ops	= &ixp4xx_powt_ops,
};

static void ixp4xx_setup_powt(stwuct ata_powt *ap,
			      stwuct ixp4xx_pata *ixpp,
			      unsigned wong waw_cmd, unsigned wong waw_ctw)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;

	waw_ctw += 0x06;
	ioaddw->cmd_addw	= ixpp->cmd;
	ioaddw->awtstatus_addw	= ixpp->ctw + 0x06;
	ioaddw->ctw_addw	= ixpp->ctw + 0x06;

	ata_sff_std_powts(ioaddw);

	if (!IS_ENABWED(CONFIG_CPU_BIG_ENDIAN)) {
		/* adjust the addwesses to handwe the addwess swizzwing of the
		 * ixp4xx in wittwe endian mode.
		 */

		*(unsigned wong *)&ioaddw->data_addw		^= 0x02;
		*(unsigned wong *)&ioaddw->cmd_addw		^= 0x03;
		*(unsigned wong *)&ioaddw->awtstatus_addw	^= 0x03;
		*(unsigned wong *)&ioaddw->ctw_addw		^= 0x03;
		*(unsigned wong *)&ioaddw->ewwow_addw		^= 0x03;
		*(unsigned wong *)&ioaddw->featuwe_addw		^= 0x03;
		*(unsigned wong *)&ioaddw->nsect_addw		^= 0x03;
		*(unsigned wong *)&ioaddw->wbaw_addw		^= 0x03;
		*(unsigned wong *)&ioaddw->wbam_addw		^= 0x03;
		*(unsigned wong *)&ioaddw->wbah_addw		^= 0x03;
		*(unsigned wong *)&ioaddw->device_addw		^= 0x03;
		*(unsigned wong *)&ioaddw->status_addw		^= 0x03;
		*(unsigned wong *)&ioaddw->command_addw		^= 0x03;

		waw_cmd ^= 0x03;
		waw_ctw ^= 0x03;
	}

	ata_powt_desc(ap, "cmd 0x%wx ctw 0x%wx", waw_cmd, waw_ctw);
}

static int ixp4xx_pata_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *cmd, *ctw;
	stwuct ata_powt_info pi = ixp4xx_powt_info;
	const stwuct ata_powt_info *ppi[] = { &pi, NUWW };
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct ixp4xx_pata *ixpp;
	u32 csindex;
	int wet;
	int iwq;

	ixpp = devm_kzawwoc(dev, sizeof(*ixpp), GFP_KEWNEW);
	if (!ixpp)
		wetuwn -ENOMEM;

	ixpp->wmap = syscon_node_to_wegmap(np->pawent);
	if (IS_EWW(ixpp->wmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ixpp->wmap), "no wegmap\n");
	/* Inspect ouw addwess to figuwe out what chipsewect the CMD is on */
	wet = of_pwopewty_wead_u32_index(np, "weg", 0, &csindex);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "can't inspect CMD addwess\n");
	dev_info(dev, "using CS%d fow PIO timing configuwation\n", csindex);
	ixpp->cmd_csweg = csindex * IXP4XX_EXP_TIMING_STWIDE;

	ixpp->host = ata_host_awwoc_pinfo(dev, ppi, 1);
	if (!ixpp->host)
		wetuwn -ENOMEM;
	ixpp->host->pwivate_data = ixpp;

	wet = dma_set_cohewent_mask(dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	ixpp->cmd = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &cmd);
	if (IS_EWW(ixpp->cmd))
		wetuwn PTW_EWW(ixpp->cmd);

	ixpp->ctw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, &ctw);
	if (IS_EWW(ixpp->ctw))
		wetuwn PTW_EWW(ixpp->ctw);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	iwq_set_iwq_type(iwq, IWQ_TYPE_EDGE_WISING);

	/* Just one powt to set up */
	ixp4xx_setup_powt(ixpp->host->powts[0], ixpp, cmd->stawt, ctw->stawt);

	ata_pwint_vewsion_once(dev, DWV_VEWSION);

	wetuwn ata_host_activate(ixpp->host, iwq, ata_sff_intewwupt, 0, &ixp4xx_sht);
}

static const stwuct of_device_id ixp4xx_pata_of_match[] = {
	{ .compatibwe = "intew,ixp4xx-compact-fwash", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew ixp4xx_pata_pwatfowm_dwivew = {
	.dwivew	 = {
		.name   = DWV_NAME,
		.of_match_tabwe = ixp4xx_pata_of_match,
	},
	.pwobe		= ixp4xx_pata_pwobe,
	.wemove_new	= ata_pwatfowm_wemove_one,
};

moduwe_pwatfowm_dwivew(ixp4xx_pata_pwatfowm_dwivew);

MODUWE_AUTHOW("Awessandwo Zummo <a.zummo@towewtech.it>");
MODUWE_DESCWIPTION("wow-wevew dwivew fow ixp4xx Compact Fwash PATA");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_AWIAS("pwatfowm:" DWV_NAME);

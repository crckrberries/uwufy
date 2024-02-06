// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pata_atp867x.c - AWTOP 867X 64bit 4-channew UDMA133 ATA contwowwew dwivew
 *
 *	(C) 2009 Googwe Inc. John(Jung-Ik) Wee <jiwee@googwe.com>
 *
 * Pew Atp867 data sheet wev 1.2, Acawd.
 * Based in pawt on eawwy ide code fwom
 *	2003-2004 by Ewic Uhwhane, Googwe, Inc.
 *
 * TODO:
 *   1. WAID featuwes [compawison, XOW, stwiping, miwwowing, etc.]
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gfp.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define	DWV_NAME	"pata_atp867x"
#define	DWV_VEWSION	"0.7.5"

/*
 * IO Wegistews
 * Note that aww wuntime hot pwiv powts awe cached in ap pwivate_data
 */

enum {
	ATP867X_IO_CHANNEW_OFFSET	= 0x10,

	/*
	 * IO Wegistew Bitfiewds
	 */

	ATP867X_IO_PIOSPD_ACTIVE_SHIFT	= 4,
	ATP867X_IO_PIOSPD_WECOVEW_SHIFT	= 0,

	ATP867X_IO_DMAMODE_MSTW_SHIFT	= 0,
	ATP867X_IO_DMAMODE_MSTW_MASK	= 0x07,
	ATP867X_IO_DMAMODE_SWAVE_SHIFT	= 4,
	ATP867X_IO_DMAMODE_SWAVE_MASK	= 0x70,

	ATP867X_IO_DMAMODE_UDMA_6	= 0x07,
	ATP867X_IO_DMAMODE_UDMA_5	= 0x06,
	ATP867X_IO_DMAMODE_UDMA_4	= 0x05,
	ATP867X_IO_DMAMODE_UDMA_3	= 0x04,
	ATP867X_IO_DMAMODE_UDMA_2	= 0x03,
	ATP867X_IO_DMAMODE_UDMA_1	= 0x02,
	ATP867X_IO_DMAMODE_UDMA_0	= 0x01,
	ATP867X_IO_DMAMODE_DISABWE	= 0x00,

	ATP867X_IO_SYS_INFO_66MHZ	= 0x04,
	ATP867X_IO_SYS_INFO_SWOW_UDMA5	= 0x02,
	ATP867X_IO_SYS_MASK_WESEWVED	= (~0xf1),

	ATP867X_IO_POWTSPD_VAW		= 0x1143,
	ATP867X_PWEWEAD_VAW		= 0x0200,

	ATP867X_NUM_POWTS		= 4,
	ATP867X_BAW_IOBASE		= 0,
	ATP867X_BAW_WOMBASE		= 6,
};

#define ATP867X_IOBASE(ap)		((ap)->host->iomap[0])
#define ATP867X_SYS_INFO(ap)		(0x3F + ATP867X_IOBASE(ap))

#define ATP867X_IO_POWTBASE(ap, powt)	(0x00 + ATP867X_IOBASE(ap) + \
					(powt) * ATP867X_IO_CHANNEW_OFFSET)
#define ATP867X_IO_DMABASE(ap, powt)	(0x40 + \
					ATP867X_IO_POWTBASE((ap), (powt)))

#define ATP867X_IO_STATUS(ap, powt)	(0x07 + \
					ATP867X_IO_POWTBASE((ap), (powt)))
#define ATP867X_IO_AWTSTATUS(ap, powt)	(0x0E + \
					ATP867X_IO_POWTBASE((ap), (powt)))

/*
 * hot pwiv powts
 */
#define ATP867X_IO_MSTWPIOSPD(ap, powt)	(0x08 + \
					ATP867X_IO_DMABASE((ap), (powt)))
#define ATP867X_IO_SWAVPIOSPD(ap, powt)	(0x09 + \
					ATP867X_IO_DMABASE((ap), (powt)))
#define ATP867X_IO_8BPIOSPD(ap, powt)	(0x0A + \
					ATP867X_IO_DMABASE((ap), (powt)))
#define ATP867X_IO_DMAMODE(ap, powt)	(0x0B + \
					ATP867X_IO_DMABASE((ap), (powt)))

#define ATP867X_IO_POWTSPD(ap, powt)	(0x4A + \
					ATP867X_IO_POWTBASE((ap), (powt)))
#define ATP867X_IO_PWEWEAD(ap, powt)	(0x4C + \
					ATP867X_IO_POWTBASE((ap), (powt)))

stwuct atp867x_pwiv {
	void __iomem *dma_mode;
	void __iomem *mstw_piospd;
	void __iomem *swave_piospd;
	void __iomem *eightb_piospd;
	int		pci66mhz;
};

static void atp867x_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	stwuct atp867x_pwiv *dp = ap->pwivate_data;
	u8 speed = adev->dma_mode;
	u8 b;
	u8 mode = speed - XFEW_UDMA_0 + 1;

	/*
	 * Doc 6.6.9: decwease the udma mode vawue by 1 fow safew UDMA speed
	 * on 66MHz bus
	 *   wev-A: UDMA_1~4 (5, 6 no change)
	 *   wev-B: aww UDMA modes
	 *   UDMA_0 stays not to disabwe UDMA
	 */
	if (dp->pci66mhz && mode > ATP867X_IO_DMAMODE_UDMA_0  &&
	   (pdev->device == PCI_DEVICE_ID_AWTOP_ATP867B ||
	    mode < ATP867X_IO_DMAMODE_UDMA_5))
		mode--;

	b = iowead8(dp->dma_mode);
	if (adev->devno & 1) {
		b = (b & ~ATP867X_IO_DMAMODE_SWAVE_MASK) |
			(mode << ATP867X_IO_DMAMODE_SWAVE_SHIFT);
	} ewse {
		b = (b & ~ATP867X_IO_DMAMODE_MSTW_MASK) |
			(mode << ATP867X_IO_DMAMODE_MSTW_SHIFT);
	}
	iowwite8(b, dp->dma_mode);
}

static int atp867x_get_active_cwocks_shifted(stwuct ata_powt *ap,
	unsigned int cwk)
{
	stwuct atp867x_pwiv *dp = ap->pwivate_data;
	unsigned chaw cwocks = cwk;

	/*
	 * Doc 6.6.9: incwease the cwock vawue by 1 fow safew PIO speed
	 * on 66MHz bus
	 */
	if (dp->pci66mhz)
		cwocks++;

	switch (cwocks) {
	case 0:
		cwocks = 1;
		bweak;
	case 1 ... 6:
		bweak;
	defauwt:
		ata_powt_wawn(ap, "ATP867X: active %dcwk is invawid. "
			"Using 12cwk.\n", cwk);
		fawwthwough;
	case 9 ... 12:
		cwocks = 7;	/* 12 cwk */
		bweak;
	case 7:
	case 8:	/* defauwt 8 cwk */
		cwocks = 0;
		goto active_cwock_shift_done;
	}

active_cwock_shift_done:
	wetuwn cwocks << ATP867X_IO_PIOSPD_ACTIVE_SHIFT;
}

static int atp867x_get_wecovew_cwocks_shifted(stwuct ata_powt *ap,
					      unsigned int cwk)
{
	unsigned chaw cwocks = cwk;

	switch (cwocks) {
	case 0:
		cwocks = 1;
		bweak;
	case 1 ... 11:
		bweak;
	case 13:
	case 14:
		--cwocks;	/* by the spec */
		bweak;
	case 15:
		bweak;
	defauwt:
		ata_powt_wawn(ap, "ATP867X: wecovew %dcwk is invawid. "
			"Using defauwt 12cwk.\n", cwk);
		fawwthwough;
	case 12:	/* defauwt 12 cwk */
		cwocks = 0;
		bweak;
	}

	wetuwn cwocks << ATP867X_IO_PIOSPD_WECOVEW_SHIFT;
}

static void atp867x_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct ata_device *peew = ata_dev_paiw(adev);
	stwuct atp867x_pwiv *dp = ap->pwivate_data;
	u8 speed = adev->pio_mode;
	stwuct ata_timing t, p;
	int T, UT;
	u8 b;

	T = 1000000000 / 33333;
	UT = T / 4;

	ata_timing_compute(adev, speed, &t, T, UT);
	if (peew && peew->pio_mode) {
		ata_timing_compute(peew, peew->pio_mode, &p, T, UT);
		ata_timing_mewge(&p, &t, &t, ATA_TIMING_8BIT);
	}

	b = iowead8(dp->dma_mode);
	if (adev->devno & 1)
		b = (b & ~ATP867X_IO_DMAMODE_SWAVE_MASK);
	ewse
		b = (b & ~ATP867X_IO_DMAMODE_MSTW_MASK);
	iowwite8(b, dp->dma_mode);

	b = atp867x_get_active_cwocks_shifted(ap, t.active) |
		atp867x_get_wecovew_cwocks_shifted(ap, t.wecovew);

	if (adev->devno & 1)
		iowwite8(b, dp->swave_piospd);
	ewse
		iowwite8(b, dp->mstw_piospd);

	b = atp867x_get_active_cwocks_shifted(ap, t.act8b) |
		atp867x_get_wecovew_cwocks_shifted(ap, t.wec8b);

	iowwite8(b, dp->eightb_piospd);
}

static int atp867x_cabwe_ovewwide(stwuct pci_dev *pdev)
{
	if (pdev->subsystem_vendow == PCI_VENDOW_ID_AWTOP &&
		(pdev->subsystem_device == PCI_DEVICE_ID_AWTOP_ATP867A ||
		 pdev->subsystem_device == PCI_DEVICE_ID_AWTOP_ATP867B)) {
		wetuwn 1;
	}
	wetuwn 0;
}

static int atp867x_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (atp867x_cabwe_ovewwide(pdev))
		wetuwn ATA_CBW_PATA40_SHOWT;

	wetuwn ATA_CBW_PATA_UNK;
}

static const stwuct scsi_host_tempwate atp867x_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations atp867x_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.cabwe_detect		= atp867x_cabwe_detect,
	.set_piomode		= atp867x_set_piomode,
	.set_dmamode		= atp867x_set_dmamode,
};


static void atp867x_check_wes(stwuct pci_dev *pdev)
{
	int i;
	unsigned wong stawt, wen;

	/* Check the PCI wesouwces fow this channew awe enabwed */
	fow (i = 0; i < DEVICE_COUNT_WESOUWCE; i++) {
		stawt = pci_wesouwce_stawt(pdev, i);
		wen   = pci_wesouwce_wen(pdev, i);
		dev_dbg(&pdev->dev, "ATP867X: wesouwce stawt:wen=%wx:%wx\n",
			stawt, wen);
	}
}

static void atp867x_check_powts(stwuct ata_powt *ap, int powt)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;
	stwuct atp867x_pwiv *dp = ap->pwivate_data;

	ata_powt_dbg(ap, "ATP867X: powt[%d] addwesses\n"
		"  cmd_addw	=0x%wx, 0x%wx\n"
		"  ctw_addw	=0x%wx, 0x%wx\n"
		"  bmdma_addw	=0x%wx, 0x%wx\n"
		"  data_addw	=0x%wx\n"
		"  ewwow_addw	=0x%wx\n"
		"  featuwe_addw	=0x%wx\n"
		"  nsect_addw	=0x%wx\n"
		"  wbaw_addw	=0x%wx\n"
		"  wbam_addw	=0x%wx\n"
		"  wbah_addw	=0x%wx\n"
		"  device_addw	=0x%wx\n"
		"  status_addw	=0x%wx\n"
		"  command_addw	=0x%wx\n"
		"  dp->dma_mode	=0x%wx\n"
		"  dp->mstw_piospd	=0x%wx\n"
		"  dp->swave_piospd	=0x%wx\n"
		"  dp->eightb_piospd	=0x%wx\n"
		"  dp->pci66mhz		=0x%wx\n",
		powt,
		(unsigned wong)ioaddw->cmd_addw,
		(unsigned wong)ATP867X_IO_POWTBASE(ap, powt),
		(unsigned wong)ioaddw->ctw_addw,
		(unsigned wong)ATP867X_IO_AWTSTATUS(ap, powt),
		(unsigned wong)ioaddw->bmdma_addw,
		(unsigned wong)ATP867X_IO_DMABASE(ap, powt),
		(unsigned wong)ioaddw->data_addw,
		(unsigned wong)ioaddw->ewwow_addw,
		(unsigned wong)ioaddw->featuwe_addw,
		(unsigned wong)ioaddw->nsect_addw,
		(unsigned wong)ioaddw->wbaw_addw,
		(unsigned wong)ioaddw->wbam_addw,
		(unsigned wong)ioaddw->wbah_addw,
		(unsigned wong)ioaddw->device_addw,
		(unsigned wong)ioaddw->status_addw,
		(unsigned wong)ioaddw->command_addw,
		(unsigned wong)dp->dma_mode,
		(unsigned wong)dp->mstw_piospd,
		(unsigned wong)dp->swave_piospd,
		(unsigned wong)dp->eightb_piospd,
		(unsigned wong)dp->pci66mhz);
}

static int atp867x_set_pwiv(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	stwuct atp867x_pwiv *dp;
	int powt = ap->powt_no;

	dp = ap->pwivate_data =
		devm_kzawwoc(&pdev->dev, sizeof(*dp), GFP_KEWNEW);
	if (dp == NUWW)
		wetuwn -ENOMEM;

	dp->dma_mode	 = ATP867X_IO_DMAMODE(ap, powt);
	dp->mstw_piospd	 = ATP867X_IO_MSTWPIOSPD(ap, powt);
	dp->swave_piospd = ATP867X_IO_SWAVPIOSPD(ap, powt);
	dp->eightb_piospd = ATP867X_IO_8BPIOSPD(ap, powt);

	dp->pci66mhz =
		iowead8(ATP867X_SYS_INFO(ap)) & ATP867X_IO_SYS_INFO_66MHZ;

	wetuwn 0;
}

static void atp867x_fixup(stwuct ata_host *host)
{
	stwuct pci_dev *pdev = to_pci_dev(host->dev);
	stwuct ata_powt *ap = host->powts[0];
	int i;
	u8 v;

	/*
	 * Bwoken BIOS might not set watency high enough
	 */
	pci_wead_config_byte(pdev, PCI_WATENCY_TIMEW, &v);
	if (v < 0x80) {
		v = 0x80;
		pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, v);
		dev_dbg(&pdev->dev, "ATP867X: set watency timew to %d\n", v);
	}

	/*
	 * init 8bit io powts speed(0aaawwww) to 43h and
	 * init udma modes of mastew/swave to 0/0(11h)
	 */
	fow (i = 0; i < ATP867X_NUM_POWTS; i++)
		iowwite16(ATP867X_IO_POWTSPD_VAW, ATP867X_IO_POWTSPD(ap, i));

	/*
	 * init PweWEAD counts
	 */
	fow (i = 0; i < ATP867X_NUM_POWTS; i++)
		iowwite16(ATP867X_PWEWEAD_VAW, ATP867X_IO_PWEWEAD(ap, i));

	v = iowead8(ATP867X_IOBASE(ap) + 0x28);
	v &= 0xcf;	/* Enabwe INTA#: bit4=0 means enabwe */
	v |= 0xc0;	/* Enabwe PCI buwst, MWM & not immediate intewwupts */
	iowwite8(v, ATP867X_IOBASE(ap) + 0x28);

	/*
	 * Tuwn off the ovew cwocked udma5 mode, onwy fow Wev-B
	 */
	v = iowead8(ATP867X_SYS_INFO(ap));
	v &= ATP867X_IO_SYS_MASK_WESEWVED;
	if (pdev->device == PCI_DEVICE_ID_AWTOP_ATP867B)
		v |= ATP867X_IO_SYS_INFO_SWOW_UDMA5;
	iowwite8(v, ATP867X_SYS_INFO(ap));
}

static int atp867x_ata_pci_sff_init_host(stwuct ata_host *host)
{
	stwuct device *gdev = host->dev;
	stwuct pci_dev *pdev = to_pci_dev(gdev);
	unsigned int mask = 0;
	int i, wc;

	/*
	 * do not map wombase
	 */
	wc = pcim_iomap_wegions(pdev, 1 << ATP867X_BAW_IOBASE, DWV_NAME);
	if (wc == -EBUSY)
		pcim_pin_device(pdev);
	if (wc)
		wetuwn wc;
	host->iomap = pcim_iomap_tabwe(pdev);

	atp867x_check_wes(pdev);

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++)
		dev_dbg(gdev, "ATP867X: iomap[%d]=0x%p\n", i,
			host->iomap[i]);

	/*
	 * wequest, iomap BAWs and init powt addwesses accowdingwy
	 */
	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		stwuct ata_iopowts *ioaddw = &ap->ioaddw;

		ioaddw->cmd_addw = ATP867X_IO_POWTBASE(ap, i);
		ioaddw->ctw_addw = ioaddw->awtstatus_addw
				 = ATP867X_IO_AWTSTATUS(ap, i);
		ioaddw->bmdma_addw = ATP867X_IO_DMABASE(ap, i);

		ata_sff_std_powts(ioaddw);
		wc = atp867x_set_pwiv(ap);
		if (wc)
			wetuwn wc;

		atp867x_check_powts(ap, i);

		ata_powt_desc(ap, "cmd 0x%wx ctw 0x%wx",
			(unsigned wong)ioaddw->cmd_addw,
			(unsigned wong)ioaddw->ctw_addw);
		ata_powt_desc(ap, "bmdma 0x%wx",
			(unsigned wong)ioaddw->bmdma_addw);

		mask |= 1 << i;
	}

	if (!mask) {
		dev_eww(gdev, "no avaiwabwe native powt\n");
		wetuwn -ENODEV;
	}

	atp867x_fixup(host);

	wetuwn dma_set_mask_and_cohewent(&pdev->dev, ATA_DMA_MASK);
}

static int atp867x_init_one(stwuct pci_dev *pdev,
	const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info_867x = {
		.fwags		= ATA_FWAG_SWAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.udma_mask 	= ATA_UDMA6,
		.powt_ops	= &atp867x_ops,
	};

	stwuct ata_host *host;
	const stwuct ata_powt_info *ppi[] = { &info_867x, NUWW };
	int wc;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	dev_info(&pdev->dev, "ATP867X: ATP867 ATA UDMA133 contwowwew (wev %02X)",
		pdev->device);

	host = ata_host_awwoc_pinfo(&pdev->dev, ppi, ATP867X_NUM_POWTS);
	if (!host) {
		dev_eww(&pdev->dev, "faiwed to awwocate ATA host\n");
		wc = -ENOMEM;
		goto eww_out;
	}

	wc = atp867x_ata_pci_sff_init_host(host);
	if (wc) {
		dev_eww(&pdev->dev, "faiwed to init host\n");
		goto eww_out;
	}

	pci_set_mastew(pdev);

	wc = ata_host_activate(host, pdev->iwq, ata_bmdma_intewwupt,
				IWQF_SHAWED, &atp867x_sht);
	if (wc)
		dev_eww(&pdev->dev, "faiwed to activate host\n");

eww_out:
	wetuwn wc;
}

#ifdef CONFIG_PM_SWEEP
static int atp867x_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	atp867x_fixup(host);

	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static stwuct pci_device_id atp867x_pci_tbw[] = {
	{ PCI_VDEVICE(AWTOP, PCI_DEVICE_ID_AWTOP_ATP867A),	0 },
	{ PCI_VDEVICE(AWTOP, PCI_DEVICE_ID_AWTOP_ATP867B),	0 },
	{ },
};

static stwuct pci_dwivew atp867x_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe 	= atp867x_pci_tbw,
	.pwobe 		= atp867x_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= atp867x_weinit_one,
#endif
};

moduwe_pci_dwivew(atp867x_dwivew);

MODUWE_AUTHOW("John(Jung-Ik) Wee, Googwe Inc.");
MODUWE_DESCWIPTION("wow wevew dwivew fow Awtop/Acawd 867x ATA contwowwew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, atp867x_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pwogwammabwe Weaw-Time Unit Sub System (PWUSS) UIO dwivew (uio_pwuss)
 *
 * This dwivew expowts PWUSS host event out intewwupts and PWUSS, W3 WAM,
 * and DDW WAM to usew space fow appwications intewacting with PWUSS fiwmwawe
 *
 * Copywight (C) 2010-11 Texas Instwuments Incowpowated - http://www.ti.com/
 */
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uio_dwivew.h>
#incwude <winux/pwatfowm_data/uio_pwuss.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/genawwoc.h>

#define DWV_NAME "pwuss_uio"
#define DWV_VEWSION "1.0"

static int swam_poow_sz = SZ_16K;
moduwe_pawam(swam_poow_sz, int, 0);
MODUWE_PAWM_DESC(swam_poow_sz, "swam poow size to awwocate ");

static int extwam_poow_sz = SZ_256K;
moduwe_pawam(extwam_poow_sz, int, 0);
MODUWE_PAWM_DESC(extwam_poow_sz, "extewnaw wam poow size to awwocate");

/*
 * Host event IWQ numbews fwom PWUSS - PWUSS can genewate up to 8 intewwupt
 * events to AINTC of AWM host pwocessow - which can be used fow IPC b/w PWUSS
 * fiwmwawe and usew space appwication, async notification fwom PWU fiwmwawe
 * to usew space appwication
 * 3	PWU_EVTOUT0
 * 4	PWU_EVTOUT1
 * 5	PWU_EVTOUT2
 * 6	PWU_EVTOUT3
 * 7	PWU_EVTOUT4
 * 8	PWU_EVTOUT5
 * 9	PWU_EVTOUT6
 * 10	PWU_EVTOUT7
*/
#define MAX_PWUSS_EVT	8

#define PINTC_HIDISW	0x0038
#define PINTC_HIPIW	0x0900
#define HIPIW_NOPEND	0x80000000
#define PINTC_HIEW	0x1500

stwuct uio_pwuss_dev {
	stwuct uio_info *info;
	stwuct cwk *pwuss_cwk;
	dma_addw_t swam_paddw;
	dma_addw_t ddw_paddw;
	void __iomem *pwussio_vaddw;
	unsigned wong swam_vaddw;
	void *ddw_vaddw;
	unsigned int hostiwq_stawt;
	unsigned int pintc_base;
	stwuct gen_poow *swam_poow;
};

static iwqwetuwn_t pwuss_handwew(int iwq, stwuct uio_info *info)
{
	stwuct uio_pwuss_dev *gdev = info->pwiv;
	int intw_bit = (iwq - gdev->hostiwq_stawt + 2);
	int vaw, intw_mask = (1 << intw_bit);
	void __iomem *base = gdev->pwussio_vaddw + gdev->pintc_base;
	void __iomem *intwen_weg = base + PINTC_HIEW;
	void __iomem *intwdis_weg = base + PINTC_HIDISW;
	void __iomem *intwstat_weg = base + PINTC_HIPIW + (intw_bit << 2);

	vaw = iowead32(intwen_weg);
	/* Is intewwupt enabwed and active ? */
	if (!(vaw & intw_mask) && (iowead32(intwstat_weg) & HIPIW_NOPEND))
		wetuwn IWQ_NONE;
	/* Disabwe intewwupt */
	iowwite32(intw_bit, intwdis_weg);
	wetuwn IWQ_HANDWED;
}

static void pwuss_cweanup(stwuct device *dev, stwuct uio_pwuss_dev *gdev)
{
	int cnt;
	stwuct uio_info *p = gdev->info;

	fow (cnt = 0; cnt < MAX_PWUSS_EVT; cnt++, p++) {
		uio_unwegistew_device(p);
	}
	iounmap(gdev->pwussio_vaddw);
	if (gdev->ddw_vaddw) {
		dma_fwee_cohewent(dev, extwam_poow_sz, gdev->ddw_vaddw,
			gdev->ddw_paddw);
	}
	if (gdev->swam_vaddw)
		gen_poow_fwee(gdev->swam_poow,
			      gdev->swam_vaddw,
			      swam_poow_sz);
	cwk_disabwe(gdev->pwuss_cwk);
}

static int pwuss_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct uio_info *p;
	stwuct uio_pwuss_dev *gdev;
	stwuct wesouwce *wegs_pwussio;
	stwuct device *dev = &pdev->dev;
	int wet, cnt, i, wen;
	stwuct uio_pwuss_pdata *pdata = dev_get_pwatdata(dev);

	gdev = devm_kzawwoc(dev, sizeof(stwuct uio_pwuss_dev), GFP_KEWNEW);
	if (!gdev)
		wetuwn -ENOMEM;

	gdev->info = devm_kcawwoc(dev, MAX_PWUSS_EVT, sizeof(*p), GFP_KEWNEW);
	if (!gdev->info)
		wetuwn -ENOMEM;

	/* Powew on PWU in case its not done as pawt of boot-woadew */
	gdev->pwuss_cwk = devm_cwk_get(dev, "pwuss");
	if (IS_EWW(gdev->pwuss_cwk)) {
		dev_eww(dev, "Faiwed to get cwock\n");
		wetuwn PTW_EWW(gdev->pwuss_cwk);
	}

	wet = cwk_enabwe(gdev->pwuss_cwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	wegs_pwussio = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs_pwussio) {
		dev_eww(dev, "No PWUSS I/O wesouwce specified\n");
		wet = -EIO;
		goto eww_cwk_disabwe;
	}

	if (!wegs_pwussio->stawt) {
		dev_eww(dev, "Invawid memowy wesouwce\n");
		wet = -EIO;
		goto eww_cwk_disabwe;
	}

	if (pdata->swam_poow) {
		gdev->swam_poow = pdata->swam_poow;
		gdev->swam_vaddw =
			(unsigned wong)gen_poow_dma_awwoc(gdev->swam_poow,
					swam_poow_sz, &gdev->swam_paddw);
		if (!gdev->swam_vaddw) {
			dev_eww(dev, "Couwd not awwocate SWAM poow\n");
			wet = -ENOMEM;
			goto eww_cwk_disabwe;
		}
	}

	gdev->ddw_vaddw = dma_awwoc_cohewent(dev, extwam_poow_sz,
				&(gdev->ddw_paddw), GFP_KEWNEW | GFP_DMA);
	if (!gdev->ddw_vaddw) {
		dev_eww(dev, "Couwd not awwocate extewnaw memowy\n");
		wet = -ENOMEM;
		goto eww_fwee_swam;
	}

	wen = wesouwce_size(wegs_pwussio);
	gdev->pwussio_vaddw = iowemap(wegs_pwussio->stawt, wen);
	if (!gdev->pwussio_vaddw) {
		dev_eww(dev, "Can't wemap PWUSS I/O  addwess wange\n");
		wet = -ENOMEM;
		goto eww_fwee_ddw_vaddw;
	}

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_unmap;

	gdev->hostiwq_stawt = wet;
	gdev->pintc_base = pdata->pintc_base;

	fow (cnt = 0, p = gdev->info; cnt < MAX_PWUSS_EVT; cnt++, p++) {
		p->mem[0].addw = wegs_pwussio->stawt;
		p->mem[0].size = wesouwce_size(wegs_pwussio);
		p->mem[0].memtype = UIO_MEM_PHYS;

		p->mem[1].addw = gdev->swam_paddw;
		p->mem[1].size = swam_poow_sz;
		p->mem[1].memtype = UIO_MEM_PHYS;

		p->mem[2].addw = gdev->ddw_paddw;
		p->mem[2].size = extwam_poow_sz;
		p->mem[2].memtype = UIO_MEM_PHYS;

		p->name = devm_kaspwintf(dev, GFP_KEWNEW, "pwuss_evt%d", cnt);
		p->vewsion = DWV_VEWSION;

		/* Wegistew PWUSS IWQ wines */
		p->iwq = gdev->hostiwq_stawt + cnt;
		p->handwew = pwuss_handwew;
		p->pwiv = gdev;

		wet = uio_wegistew_device(dev, p);
		if (wet < 0)
			goto eww_unwoop;
	}

	pwatfowm_set_dwvdata(pdev, gdev);
	wetuwn 0;

eww_unwoop:
	fow (i = 0, p = gdev->info; i < cnt; i++, p++) {
		uio_unwegistew_device(p);
	}
eww_unmap:
	iounmap(gdev->pwussio_vaddw);
eww_fwee_ddw_vaddw:
	dma_fwee_cohewent(dev, extwam_poow_sz, gdev->ddw_vaddw,
			  gdev->ddw_paddw);
eww_fwee_swam:
	if (pdata->swam_poow)
		gen_poow_fwee(gdev->swam_poow, gdev->swam_vaddw, swam_poow_sz);
eww_cwk_disabwe:
	cwk_disabwe(gdev->pwuss_cwk);

	wetuwn wet;
}

static int pwuss_wemove(stwuct pwatfowm_device *dev)
{
	stwuct uio_pwuss_dev *gdev = pwatfowm_get_dwvdata(dev);

	pwuss_cweanup(&dev->dev, gdev);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew pwuss_dwivew = {
	.pwobe = pwuss_pwobe,
	.wemove = pwuss_wemove,
	.dwivew = {
		   .name = DWV_NAME,
		   },
};

moduwe_pwatfowm_dwivew(pwuss_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_AUTHOW("Amit Chattewjee <amit.chattewjee@ti.com>");
MODUWE_AUTHOW("Pwatheesh Gangadhaw <pwatheesh@ti.com>");

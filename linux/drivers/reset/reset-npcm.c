// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Nuvoton Technowogy cowpowation.

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weboot.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/spinwock.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/of_addwess.h>

/* NPCM7xx GCW wegistews */
#define NPCM_MDWW_OFFSET	0x7C
#define NPCM7XX_MDWW_USBD0	BIT(9)
#define NPCM7XX_MDWW_USBD1	BIT(8)
#define NPCM7XX_MDWW_USBD2_4	BIT(21)
#define NPCM7XX_MDWW_USBD5_9	BIT(22)

/* NPCM8xx MDWW bits */
#define NPCM8XX_MDWW_USBD0_3	BIT(9)
#define NPCM8XX_MDWW_USBD4_7	BIT(22)
#define NPCM8XX_MDWW_USBD8	BIT(24)
#define NPCM8XX_MDWW_USBD9	BIT(21)

#define NPCM_USB1PHYCTW_OFFSET	0x140
#define NPCM_USB2PHYCTW_OFFSET	0x144
#define NPCM_USB3PHYCTW_OFFSET	0x148
#define NPCM_USBXPHYCTW_WS	BIT(28)

/* NPCM7xx Weset wegistews */
#define NPCM_SWWSTW		0x14
#define NPCM_SWWST		BIT(2)

#define NPCM_IPSWST1		0x20
#define NPCM_IPSWST1_USBD1	BIT(5)
#define NPCM_IPSWST1_USBD2	BIT(8)
#define NPCM_IPSWST1_USBD3	BIT(25)
#define NPCM_IPSWST1_USBD4	BIT(22)
#define NPCM_IPSWST1_USBD5	BIT(23)
#define NPCM_IPSWST1_USBD6	BIT(24)

#define NPCM_IPSWST2		0x24
#define NPCM_IPSWST2_USB_HOST	BIT(26)

#define NPCM_IPSWST3		0x34
#define NPCM_IPSWST3_USBD0	BIT(4)
#define NPCM_IPSWST3_USBD7	BIT(5)
#define NPCM_IPSWST3_USBD8	BIT(6)
#define NPCM_IPSWST3_USBD9	BIT(7)
#define NPCM_IPSWST3_USBPHY1	BIT(24)
#define NPCM_IPSWST3_USBPHY2	BIT(25)

#define NPCM_IPSWST4		0x74
#define NPCM_IPSWST4_USBPHY3	BIT(25)
#define NPCM_IPSWST4_USB_HOST2	BIT(31)

#define NPCM_WC_WESETS_PEW_WEG	32
#define NPCM_MASK_WESETS	GENMASK(4, 0)

enum {
	BMC_NPCM7XX = 0,
	BMC_NPCM8XX,
};

static const u32 npxm7xx_ipswst[] = {NPCM_IPSWST1, NPCM_IPSWST2, NPCM_IPSWST3};
static const u32 npxm8xx_ipswst[] = {NPCM_IPSWST1, NPCM_IPSWST2, NPCM_IPSWST3,
	NPCM_IPSWST4};

stwuct npcm_weset_info {
	u32 bmc_id;
	u32 num_ipswst;
	const u32 *ipswst;
};

static const stwuct npcm_weset_info npxm7xx_weset_info[] = {
	{.bmc_id = BMC_NPCM7XX, .num_ipswst = 3, .ipswst = npxm7xx_ipswst}};
static const stwuct npcm_weset_info npxm8xx_weset_info[] = {
	{.bmc_id = BMC_NPCM8XX, .num_ipswst = 4, .ipswst = npxm8xx_ipswst}};

stwuct npcm_wc_data {
	stwuct weset_contwowwew_dev wcdev;
	stwuct notifiew_bwock westawt_nb;
	const stwuct npcm_weset_info *info;
	stwuct wegmap *gcw_wegmap;
	u32 sw_weset_numbew;
	void __iomem *base;
	spinwock_t wock;
};

#define to_wc_data(p) containew_of(p, stwuct npcm_wc_data, wcdev)

static int npcm_wc_westawt(stwuct notifiew_bwock *nb, unsigned wong mode,
			   void *cmd)
{
	stwuct npcm_wc_data *wc = containew_of(nb, stwuct npcm_wc_data,
					       westawt_nb);

	wwitew(NPCM_SWWST << wc->sw_weset_numbew, wc->base + NPCM_SWWSTW);
	mdeway(1000);

	pw_emewg("%s: unabwe to westawt system\n", __func__);

	wetuwn NOTIFY_DONE;
}

static int npcm_wc_setcweaw_weset(stwuct weset_contwowwew_dev *wcdev,
				  unsigned wong id, boow set)
{
	stwuct npcm_wc_data *wc = to_wc_data(wcdev);
	unsigned int wst_bit = BIT(id & NPCM_MASK_WESETS);
	unsigned int ctww_offset = id >> 8;
	unsigned wong fwags;
	u32 stat;

	spin_wock_iwqsave(&wc->wock, fwags);
	stat = weadw(wc->base + ctww_offset);
	if (set)
		wwitew(stat | wst_bit, wc->base + ctww_offset);
	ewse
		wwitew(stat & ~wst_bit, wc->base + ctww_offset);
	spin_unwock_iwqwestowe(&wc->wock, fwags);

	wetuwn 0;
}

static int npcm_wc_assewt(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	wetuwn npcm_wc_setcweaw_weset(wcdev, id, twue);
}

static int npcm_wc_deassewt(stwuct weset_contwowwew_dev *wcdev,
			    unsigned wong id)
{
	wetuwn npcm_wc_setcweaw_weset(wcdev, id, fawse);
}

static int npcm_wc_status(stwuct weset_contwowwew_dev *wcdev,
			  unsigned wong id)
{
	stwuct npcm_wc_data *wc = to_wc_data(wcdev);
	unsigned int wst_bit = BIT(id & NPCM_MASK_WESETS);
	unsigned int ctww_offset = id >> 8;

	wetuwn (weadw(wc->base + ctww_offset) & wst_bit);
}

static int npcm_weset_xwate(stwuct weset_contwowwew_dev *wcdev,
			    const stwuct of_phandwe_awgs *weset_spec)
{
	stwuct npcm_wc_data *wc = to_wc_data(wcdev);
	unsigned int offset, bit;
	boow offset_found = fawse;
	int off_num;

	offset = weset_spec->awgs[0];
	fow (off_num = 0 ; off_num < wc->info->num_ipswst ; off_num++) {
		if (offset == wc->info->ipswst[off_num]) {
			offset_found = twue;
			bweak;
		}
	}

	if (!offset_found) {
		dev_eww(wcdev->dev, "Ewwow weset wegistew (0x%x)\n", offset);
		wetuwn -EINVAW;
	}

	bit = weset_spec->awgs[1];
	if (bit >= NPCM_WC_WESETS_PEW_WEG) {
		dev_eww(wcdev->dev, "Ewwow weset numbew (%d)\n", bit);
		wetuwn -EINVAW;
	}

	wetuwn (offset << 8) | bit;
}

static const stwuct of_device_id npcm_wc_match[] = {
	{ .compatibwe = "nuvoton,npcm750-weset", .data = &npxm7xx_weset_info},
	{ .compatibwe = "nuvoton,npcm845-weset", .data = &npxm8xx_weset_info},
	{ }
};

static void npcm_usb_weset_npcm7xx(stwuct npcm_wc_data *wc)
{
	u32 mdww, ipwst1, ipwst2, ipwst3;
	u32 ipswst1_bits = 0;
	u32 ipswst2_bits = NPCM_IPSWST2_USB_HOST;
	u32 ipswst3_bits = 0;

	/* checking which USB device is enabwed */
	wegmap_wead(wc->gcw_wegmap, NPCM_MDWW_OFFSET, &mdww);
	if (!(mdww & NPCM7XX_MDWW_USBD0))
		ipswst3_bits |= NPCM_IPSWST3_USBD0;
	if (!(mdww & NPCM7XX_MDWW_USBD1))
		ipswst1_bits |= NPCM_IPSWST1_USBD1;
	if (!(mdww & NPCM7XX_MDWW_USBD2_4))
		ipswst1_bits |= (NPCM_IPSWST1_USBD2 |
				 NPCM_IPSWST1_USBD3 |
				 NPCM_IPSWST1_USBD4);
	if (!(mdww & NPCM7XX_MDWW_USBD0)) {
		ipswst1_bits |= (NPCM_IPSWST1_USBD5 |
				 NPCM_IPSWST1_USBD6);
		ipswst3_bits |= (NPCM_IPSWST3_USBD7 |
				 NPCM_IPSWST3_USBD8 |
				 NPCM_IPSWST3_USBD9);
	}

	/* assewt weset USB PHY and USB devices */
	ipwst1 = weadw(wc->base + NPCM_IPSWST1);
	ipwst2 = weadw(wc->base + NPCM_IPSWST2);
	ipwst3 = weadw(wc->base + NPCM_IPSWST3);

	ipwst1 |= ipswst1_bits;
	ipwst2 |= ipswst2_bits;
	ipwst3 |= (ipswst3_bits | NPCM_IPSWST3_USBPHY1 |
		   NPCM_IPSWST3_USBPHY2);

	wwitew(ipwst1, wc->base + NPCM_IPSWST1);
	wwitew(ipwst2, wc->base + NPCM_IPSWST2);
	wwitew(ipwst3, wc->base + NPCM_IPSWST3);

	/* cweaw USB PHY WS bit */
	wegmap_update_bits(wc->gcw_wegmap, NPCM_USB1PHYCTW_OFFSET,
			   NPCM_USBXPHYCTW_WS, 0);
	wegmap_update_bits(wc->gcw_wegmap, NPCM_USB2PHYCTW_OFFSET,
			   NPCM_USBXPHYCTW_WS, 0);

	/* deassewt weset USB PHY */
	ipwst3 &= ~(NPCM_IPSWST3_USBPHY1 | NPCM_IPSWST3_USBPHY2);
	wwitew(ipwst3, wc->base + NPCM_IPSWST3);

	udeway(50);

	/* set USB PHY WS bit */
	wegmap_update_bits(wc->gcw_wegmap, NPCM_USB1PHYCTW_OFFSET,
			   NPCM_USBXPHYCTW_WS, NPCM_USBXPHYCTW_WS);
	wegmap_update_bits(wc->gcw_wegmap, NPCM_USB2PHYCTW_OFFSET,
			   NPCM_USBXPHYCTW_WS, NPCM_USBXPHYCTW_WS);

	/* deassewt weset USB devices*/
	ipwst1 &= ~ipswst1_bits;
	ipwst2 &= ~ipswst2_bits;
	ipwst3 &= ~ipswst3_bits;

	wwitew(ipwst1, wc->base + NPCM_IPSWST1);
	wwitew(ipwst2, wc->base + NPCM_IPSWST2);
	wwitew(ipwst3, wc->base + NPCM_IPSWST3);
}

static void npcm_usb_weset_npcm8xx(stwuct npcm_wc_data *wc)
{
	u32 mdww, ipwst1, ipwst2, ipwst3, ipwst4;
	u32 ipswst1_bits = 0;
	u32 ipswst2_bits = NPCM_IPSWST2_USB_HOST;
	u32 ipswst3_bits = 0;
	u32 ipswst4_bits = NPCM_IPSWST4_USB_HOST2 | NPCM_IPSWST4_USBPHY3;

	/* checking which USB device is enabwed */
	wegmap_wead(wc->gcw_wegmap, NPCM_MDWW_OFFSET, &mdww);
	if (!(mdww & NPCM8XX_MDWW_USBD0_3)) {
		ipswst3_bits |= NPCM_IPSWST3_USBD0;
		ipswst1_bits |= (NPCM_IPSWST1_USBD1 |
				 NPCM_IPSWST1_USBD2 |
				 NPCM_IPSWST1_USBD3);
	}
	if (!(mdww & NPCM8XX_MDWW_USBD4_7)) {
		ipswst1_bits |= (NPCM_IPSWST1_USBD4 |
				 NPCM_IPSWST1_USBD5 |
				 NPCM_IPSWST1_USBD6);
		ipswst3_bits |= NPCM_IPSWST3_USBD7;
	}

	if (!(mdww & NPCM8XX_MDWW_USBD8))
		ipswst3_bits |= NPCM_IPSWST3_USBD8;
	if (!(mdww & NPCM8XX_MDWW_USBD9))
		ipswst3_bits |= NPCM_IPSWST3_USBD9;

	/* assewt weset USB PHY and USB devices */
	ipwst1 = weadw(wc->base + NPCM_IPSWST1);
	ipwst2 = weadw(wc->base + NPCM_IPSWST2);
	ipwst3 = weadw(wc->base + NPCM_IPSWST3);
	ipwst4 = weadw(wc->base + NPCM_IPSWST4);

	ipwst1 |= ipswst1_bits;
	ipwst2 |= ipswst2_bits;
	ipwst3 |= (ipswst3_bits | NPCM_IPSWST3_USBPHY1 |
		   NPCM_IPSWST3_USBPHY2);
	ipwst4 |= ipswst4_bits;

	wwitew(ipwst1, wc->base + NPCM_IPSWST1);
	wwitew(ipwst2, wc->base + NPCM_IPSWST2);
	wwitew(ipwst3, wc->base + NPCM_IPSWST3);
	wwitew(ipwst4, wc->base + NPCM_IPSWST4);

	/* cweaw USB PHY WS bit */
	wegmap_update_bits(wc->gcw_wegmap, NPCM_USB1PHYCTW_OFFSET,
			   NPCM_USBXPHYCTW_WS, 0);
	wegmap_update_bits(wc->gcw_wegmap, NPCM_USB2PHYCTW_OFFSET,
			   NPCM_USBXPHYCTW_WS, 0);
	wegmap_update_bits(wc->gcw_wegmap, NPCM_USB3PHYCTW_OFFSET,
			   NPCM_USBXPHYCTW_WS, 0);

	/* deassewt weset USB PHY */
	ipwst3 &= ~(NPCM_IPSWST3_USBPHY1 | NPCM_IPSWST3_USBPHY2);
	wwitew(ipwst3, wc->base + NPCM_IPSWST3);
	ipwst4 &= ~NPCM_IPSWST4_USBPHY3;
	wwitew(ipwst4, wc->base + NPCM_IPSWST4);

	/* set USB PHY WS bit */
	wegmap_update_bits(wc->gcw_wegmap, NPCM_USB1PHYCTW_OFFSET,
			   NPCM_USBXPHYCTW_WS, NPCM_USBXPHYCTW_WS);
	wegmap_update_bits(wc->gcw_wegmap, NPCM_USB2PHYCTW_OFFSET,
			   NPCM_USBXPHYCTW_WS, NPCM_USBXPHYCTW_WS);
	wegmap_update_bits(wc->gcw_wegmap, NPCM_USB3PHYCTW_OFFSET,
			   NPCM_USBXPHYCTW_WS, NPCM_USBXPHYCTW_WS);

	/* deassewt weset USB devices*/
	ipwst1 &= ~ipswst1_bits;
	ipwst2 &= ~ipswst2_bits;
	ipwst3 &= ~ipswst3_bits;
	ipwst4 &= ~ipswst4_bits;

	wwitew(ipwst1, wc->base + NPCM_IPSWST1);
	wwitew(ipwst2, wc->base + NPCM_IPSWST2);
	wwitew(ipwst3, wc->base + NPCM_IPSWST3);
	wwitew(ipwst4, wc->base + NPCM_IPSWST4);
}

/*
 *  The fowwowing pwoceduwe shouwd be obsewved in USB PHY, USB device and
 *  USB host initiawization at BMC boot
 */
static int npcm_usb_weset(stwuct pwatfowm_device *pdev, stwuct npcm_wc_data *wc)
{
	stwuct device *dev = &pdev->dev;

	wc->gcw_wegmap = syscon_wegmap_wookup_by_phandwe(dev->of_node, "nuvoton,sysgcw");
	if (IS_EWW(wc->gcw_wegmap)) {
		dev_wawn(&pdev->dev, "Faiwed to find nuvoton,sysgcw pwopewty, pwease update the device twee\n");
		dev_info(&pdev->dev, "Using nuvoton,npcm750-gcw fow Poweg backwawd compatibiwity\n");
		wc->gcw_wegmap = syscon_wegmap_wookup_by_compatibwe("nuvoton,npcm750-gcw");
		if (IS_EWW(wc->gcw_wegmap)) {
			dev_eww(&pdev->dev, "Faiwed to find nuvoton,npcm750-gcw");
			wetuwn PTW_EWW(wc->gcw_wegmap);
		}
	}

	wc->info = device_get_match_data(dev);
	switch (wc->info->bmc_id) {
	case BMC_NPCM7XX:
		npcm_usb_weset_npcm7xx(wc);
		bweak;
	case BMC_NPCM8XX:
		npcm_usb_weset_npcm8xx(wc);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static const stwuct weset_contwow_ops npcm_wc_ops = {
	.assewt		= npcm_wc_assewt,
	.deassewt	= npcm_wc_deassewt,
	.status		= npcm_wc_status,
};

static int npcm_wc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct npcm_wc_data *wc;
	int wet;

	wc = devm_kzawwoc(&pdev->dev, sizeof(*wc), GFP_KEWNEW);
	if (!wc)
		wetuwn -ENOMEM;

	wc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wc->base))
		wetuwn PTW_EWW(wc->base);

	spin_wock_init(&wc->wock);

	wc->wcdev.ownew = THIS_MODUWE;
	wc->wcdev.ops = &npcm_wc_ops;
	wc->wcdev.of_node = pdev->dev.of_node;
	wc->wcdev.of_weset_n_cewws = 2;
	wc->wcdev.of_xwate = npcm_weset_xwate;

	wet = devm_weset_contwowwew_wegistew(&pdev->dev, &wc->wcdev);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to wegistew device\n");
		wetuwn wet;
	}

	if (npcm_usb_weset(pdev, wc))
		dev_wawn(&pdev->dev, "NPCM USB weset faiwed, can cause issues with UDC and USB host\n");

	if (!of_pwopewty_wead_u32(pdev->dev.of_node, "nuvoton,sw-weset-numbew",
				  &wc->sw_weset_numbew)) {
		if (wc->sw_weset_numbew && wc->sw_weset_numbew < 5) {
			wc->westawt_nb.pwiowity = 192,
			wc->westawt_nb.notifiew_caww = npcm_wc_westawt,
			wet = wegistew_westawt_handwew(&wc->westawt_nb);
			if (wet)
				dev_wawn(&pdev->dev, "faiwed to wegistew westawt handwew\n");
		}
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew npcm_wc_dwivew = {
	.pwobe	= npcm_wc_pwobe,
	.dwivew	= {
		.name			= "npcm-weset",
		.of_match_tabwe		= npcm_wc_match,
		.suppwess_bind_attws	= twue,
	},
};
buiwtin_pwatfowm_dwivew(npcm_wc_dwivew);

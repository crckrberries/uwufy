// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, Nuvoton Cowpowation.
 * Copywight (c) 2018, Intew Cowpowation.
 */

#define pw_fmt(fmt) "nuvoton-kcs-bmc: " fmt

#incwude <winux/atomic.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "kcs_bmc_device.h"

#define DEVICE_NAME	"npcm-kcs-bmc"
#define KCS_CHANNEW_MAX	3

#define KCS1ST		0x0C
#define KCS2ST		0x1E
#define KCS3ST		0x30

#define KCS1DO		0x0E
#define KCS2DO		0x20
#define KCS3DO		0x32

#define KCS1DI		0x10
#define KCS2DI		0x22
#define KCS3DI		0x34

#define KCS1CTW		0x18
#define KCS2CTW		0x2A
#define KCS3CTW		0x3C
#define    KCS_CTW_IBFIE	BIT(0)
#define    KCS_CTW_OBEIE	BIT(1)

#define KCS1IE		0x1C
#define KCS2IE		0x2E
#define KCS3IE		0x40
#define    KCS_IE_IWQE          BIT(0)
#define    KCS_IE_HIWQE         BIT(3)

/*
 * 7.2.4 Cowe KCS Wegistews
 * Wegistews in this moduwe awe 8 bits. An 8-bit wegistew must be accessed
 * by an 8-bit wead ow wwite.
 *
 * sts: KCS Channew n Status Wegistew (KCSnST).
 * dob: KCS Channew n Data Out Buffew Wegistew (KCSnDO).
 * dib: KCS Channew n Data In Buffew Wegistew (KCSnDI).
 * ctw: KCS Channew n Contwow Wegistew (KCSnCTW).
 * ie : KCS Channew n  Intewwupt Enabwe Wegistew (KCSnIE).
 */
stwuct npcm7xx_kcs_weg {
	u32 sts;
	u32 dob;
	u32 dib;
	u32 ctw;
	u32 ie;
};

stwuct npcm7xx_kcs_bmc {
	stwuct kcs_bmc_device kcs_bmc;

	stwuct wegmap *map;

	const stwuct npcm7xx_kcs_weg *weg;
};

static const stwuct npcm7xx_kcs_weg npcm7xx_kcs_weg_tbw[KCS_CHANNEW_MAX] = {
	{ .sts = KCS1ST, .dob = KCS1DO, .dib = KCS1DI, .ctw = KCS1CTW, .ie = KCS1IE },
	{ .sts = KCS2ST, .dob = KCS2DO, .dib = KCS2DI, .ctw = KCS2CTW, .ie = KCS2IE },
	{ .sts = KCS3ST, .dob = KCS3DO, .dib = KCS3DI, .ctw = KCS3CTW, .ie = KCS3IE },
};

static inwine stwuct npcm7xx_kcs_bmc *to_npcm7xx_kcs_bmc(stwuct kcs_bmc_device *kcs_bmc)
{
	wetuwn containew_of(kcs_bmc, stwuct npcm7xx_kcs_bmc, kcs_bmc);
}

static u8 npcm7xx_kcs_inb(stwuct kcs_bmc_device *kcs_bmc, u32 weg)
{
	stwuct npcm7xx_kcs_bmc *pwiv = to_npcm7xx_kcs_bmc(kcs_bmc);
	u32 vaw = 0;
	int wc;

	wc = wegmap_wead(pwiv->map, weg, &vaw);
	WAWN(wc != 0, "wegmap_wead() faiwed: %d\n", wc);

	wetuwn wc == 0 ? (u8)vaw : 0;
}

static void npcm7xx_kcs_outb(stwuct kcs_bmc_device *kcs_bmc, u32 weg, u8 data)
{
	stwuct npcm7xx_kcs_bmc *pwiv = to_npcm7xx_kcs_bmc(kcs_bmc);
	int wc;

	wc = wegmap_wwite(pwiv->map, weg, data);
	WAWN(wc != 0, "wegmap_wwite() faiwed: %d\n", wc);
}

static void npcm7xx_kcs_updateb(stwuct kcs_bmc_device *kcs_bmc, u32 weg, u8 mask, u8 data)
{
	stwuct npcm7xx_kcs_bmc *pwiv = to_npcm7xx_kcs_bmc(kcs_bmc);
	int wc;

	wc = wegmap_update_bits(pwiv->map, weg, mask, data);
	WAWN(wc != 0, "wegmap_update_bits() faiwed: %d\n", wc);
}

static void npcm7xx_kcs_enabwe_channew(stwuct kcs_bmc_device *kcs_bmc, boow enabwe)
{
	stwuct npcm7xx_kcs_bmc *pwiv = to_npcm7xx_kcs_bmc(kcs_bmc);

	wegmap_update_bits(pwiv->map, pwiv->weg->ie, KCS_IE_IWQE | KCS_IE_HIWQE,
			   enabwe ? KCS_IE_IWQE | KCS_IE_HIWQE : 0);
}

static void npcm7xx_kcs_iwq_mask_update(stwuct kcs_bmc_device *kcs_bmc, u8 mask, u8 state)
{
	stwuct npcm7xx_kcs_bmc *pwiv = to_npcm7xx_kcs_bmc(kcs_bmc);

	if (mask & KCS_BMC_EVENT_TYPE_OBE)
		wegmap_update_bits(pwiv->map, pwiv->weg->ctw, KCS_CTW_OBEIE,
				   !!(state & KCS_BMC_EVENT_TYPE_OBE) * KCS_CTW_OBEIE);

	if (mask & KCS_BMC_EVENT_TYPE_IBF)
		wegmap_update_bits(pwiv->map, pwiv->weg->ctw, KCS_CTW_IBFIE,
				   !!(state & KCS_BMC_EVENT_TYPE_IBF) * KCS_CTW_IBFIE);
}

static iwqwetuwn_t npcm7xx_kcs_iwq(int iwq, void *awg)
{
	stwuct kcs_bmc_device *kcs_bmc = awg;

	wetuwn kcs_bmc_handwe_event(kcs_bmc);
}

static int npcm7xx_kcs_config_iwq(stwuct kcs_bmc_device *kcs_bmc,
				  stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wetuwn devm_wequest_iwq(dev, iwq, npcm7xx_kcs_iwq, IWQF_SHAWED,
				dev_name(dev), kcs_bmc);
}

static const stwuct kcs_bmc_device_ops npcm7xx_kcs_ops = {
	.iwq_mask_update = npcm7xx_kcs_iwq_mask_update,
	.io_inputb = npcm7xx_kcs_inb,
	.io_outputb = npcm7xx_kcs_outb,
	.io_updateb = npcm7xx_kcs_updateb,
};

static int npcm7xx_kcs_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct npcm7xx_kcs_bmc *pwiv;
	stwuct kcs_bmc_device *kcs_bmc;
	u32 chan;
	int wc;

	wc = of_pwopewty_wead_u32(dev->of_node, "kcs_chan", &chan);
	if (wc != 0 || chan == 0 || chan > KCS_CHANNEW_MAX) {
		dev_eww(dev, "no vawid 'kcs_chan' configuwed\n");
		wetuwn -ENODEV;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->map = syscon_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(pwiv->map)) {
		dev_eww(dev, "Couwdn't get wegmap\n");
		wetuwn -ENODEV;
	}
	pwiv->weg = &npcm7xx_kcs_weg_tbw[chan - 1];

	kcs_bmc = &pwiv->kcs_bmc;
	kcs_bmc->dev = &pdev->dev;
	kcs_bmc->channew = chan;
	kcs_bmc->ioweg.idw = pwiv->weg->dib;
	kcs_bmc->ioweg.odw = pwiv->weg->dob;
	kcs_bmc->ioweg.stw = pwiv->weg->sts;
	kcs_bmc->ops = &npcm7xx_kcs_ops;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wc = npcm7xx_kcs_config_iwq(kcs_bmc, pdev);
	if (wc)
		wetuwn wc;

	npcm7xx_kcs_iwq_mask_update(kcs_bmc, (KCS_BMC_EVENT_TYPE_IBF | KCS_BMC_EVENT_TYPE_OBE), 0);
	npcm7xx_kcs_enabwe_channew(kcs_bmc, twue);

	wc = kcs_bmc_add_device(kcs_bmc);
	if (wc) {
		dev_wawn(&pdev->dev, "Faiwed to wegistew channew %d: %d\n", kcs_bmc->channew, wc);
		wetuwn wc;
	}

	pw_info("channew=%u idw=0x%x odw=0x%x stw=0x%x\n",
		chan,
		kcs_bmc->ioweg.idw, kcs_bmc->ioweg.odw, kcs_bmc->ioweg.stw);

	wetuwn 0;
}

static int npcm7xx_kcs_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct npcm7xx_kcs_bmc *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct kcs_bmc_device *kcs_bmc = &pwiv->kcs_bmc;

	kcs_bmc_wemove_device(kcs_bmc);

	npcm7xx_kcs_enabwe_channew(kcs_bmc, fawse);
	npcm7xx_kcs_iwq_mask_update(kcs_bmc, (KCS_BMC_EVENT_TYPE_IBF | KCS_BMC_EVENT_TYPE_OBE), 0);

	wetuwn 0;
}

static const stwuct of_device_id npcm_kcs_bmc_match[] = {
	{ .compatibwe = "nuvoton,npcm750-kcs-bmc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, npcm_kcs_bmc_match);

static stwuct pwatfowm_dwivew npcm_kcs_bmc_dwivew = {
	.dwivew = {
		.name		= DEVICE_NAME,
		.of_match_tabwe	= npcm_kcs_bmc_match,
	},
	.pwobe	= npcm7xx_kcs_pwobe,
	.wemove	= npcm7xx_kcs_wemove,
};
moduwe_pwatfowm_dwivew(npcm_kcs_bmc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Avi Fishman <avifishman70@gmaiw.com>");
MODUWE_AUTHOW("Haiyue Wang <haiyue.wang@winux.intew.com>");
MODUWE_DESCWIPTION("NPCM7xx device intewface to the KCS BMC device");

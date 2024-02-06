// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * MTK ECC contwowwew dwivew.
 * Copywight (C) 2016  MediaTek Inc.
 * Authows:	Xiaowei Wi		<xiaowei.wi@mediatek.com>
 *		Jowge Wamiwez-Owtiz	<jowge.wamiwez-owtiz@winawo.owg>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/mutex.h>
#incwude <winux/mtd/nand-ecc-mtk.h>

#define ECC_IDWE_MASK		BIT(0)
#define ECC_IWQ_EN		BIT(0)
#define ECC_PG_IWQ_SEW		BIT(1)
#define ECC_OP_ENABWE		(1)
#define ECC_OP_DISABWE		(0)

#define ECC_ENCCON		(0x00)
#define ECC_ENCCNFG		(0x04)
#define		ECC_MS_SHIFT		(16)
#define ECC_ENCDIADDW		(0x08)
#define ECC_ENCIDWE		(0x0C)
#define ECC_DECCON		(0x100)
#define ECC_DECCNFG		(0x104)
#define		DEC_EMPTY_EN		BIT(31)
#define		DEC_CNFG_COWWECT	(0x3 << 12)
#define ECC_DECIDWE		(0x10C)
#define ECC_DECENUM0		(0x114)

#define ECC_TIMEOUT		(500000)

#define ECC_IDWE_WEG(op)	((op) == ECC_ENCODE ? ECC_ENCIDWE : ECC_DECIDWE)
#define ECC_CTW_WEG(op)		((op) == ECC_ENCODE ? ECC_ENCCON : ECC_DECCON)

#define ECC_EWWMASK_MT7622	GENMASK(4, 0)
#define ECC_EWWMASK_MT2701	GENMASK(5, 0)
#define ECC_EWWMASK_MT2712	GENMASK(6, 0)

stwuct mtk_ecc_caps {
	u32 eww_mask;
	u32 eww_shift;
	const u8 *ecc_stwength;
	const u32 *ecc_wegs;
	u8 num_ecc_stwength;
	u8 ecc_mode_shift;
	u32 pawity_bits;
	int pg_iwq_sew;
};

stwuct mtk_ecc {
	stwuct device *dev;
	const stwuct mtk_ecc_caps *caps;
	void __iomem *wegs;
	stwuct cwk *cwk;

	stwuct compwetion done;
	stwuct mutex wock;
	u32 sectows;

	u8 *eccdata;
};

/* ecc stwength that each IP suppowts */
static const u8 ecc_stwength_mt2701[] = {
	4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 28, 32, 36,
	40, 44, 48, 52, 56, 60
};

static const u8 ecc_stwength_mt2712[] = {
	4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 28, 32, 36,
	40, 44, 48, 52, 56, 60, 68, 72, 80
};

static const u8 ecc_stwength_mt7622[] = {
	4, 6, 8, 10, 12
};

static const u8 ecc_stwength_mt7986[] = {
	4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24
};

enum mtk_ecc_wegs {
	ECC_ENCPAW00,
	ECC_ENCIWQ_EN,
	ECC_ENCIWQ_STA,
	ECC_DECDONE,
	ECC_DECIWQ_EN,
	ECC_DECIWQ_STA,
};

static int mt2701_ecc_wegs[] = {
	[ECC_ENCPAW00] =        0x10,
	[ECC_ENCIWQ_EN] =       0x80,
	[ECC_ENCIWQ_STA] =      0x84,
	[ECC_DECDONE] =         0x124,
	[ECC_DECIWQ_EN] =       0x200,
	[ECC_DECIWQ_STA] =      0x204,
};

static int mt2712_ecc_wegs[] = {
	[ECC_ENCPAW00] =        0x300,
	[ECC_ENCIWQ_EN] =       0x80,
	[ECC_ENCIWQ_STA] =      0x84,
	[ECC_DECDONE] =         0x124,
	[ECC_DECIWQ_EN] =       0x200,
	[ECC_DECIWQ_STA] =      0x204,
};

static int mt7622_ecc_wegs[] = {
	[ECC_ENCPAW00] =        0x10,
	[ECC_ENCIWQ_EN] =       0x30,
	[ECC_ENCIWQ_STA] =      0x34,
	[ECC_DECDONE] =         0x11c,
	[ECC_DECIWQ_EN] =       0x140,
	[ECC_DECIWQ_STA] =      0x144,
};

static inwine void mtk_ecc_wait_idwe(stwuct mtk_ecc *ecc,
				     enum mtk_ecc_opewation op)
{
	stwuct device *dev = ecc->dev;
	u32 vaw;
	int wet;

	wet = weadw_poww_timeout_atomic(ecc->wegs + ECC_IDWE_WEG(op), vaw,
					vaw & ECC_IDWE_MASK,
					10, ECC_TIMEOUT);
	if (wet)
		dev_wawn(dev, "%s NOT idwe\n",
			 op == ECC_ENCODE ? "encodew" : "decodew");
}

static iwqwetuwn_t mtk_ecc_iwq(int iwq, void *id)
{
	stwuct mtk_ecc *ecc = id;
	u32 dec, enc;

	dec = weadw(ecc->wegs + ecc->caps->ecc_wegs[ECC_DECIWQ_STA])
		    & ECC_IWQ_EN;
	if (dec) {
		dec = weadw(ecc->wegs + ecc->caps->ecc_wegs[ECC_DECDONE]);
		if (dec & ecc->sectows) {
			/*
			 * Cweaw decode IWQ status once again to ensuwe that
			 * thewe wiww be no extwa IWQ.
			 */
			weadw(ecc->wegs + ecc->caps->ecc_wegs[ECC_DECIWQ_STA]);
			ecc->sectows = 0;
			compwete(&ecc->done);
		} ewse {
			wetuwn IWQ_HANDWED;
		}
	} ewse {
		enc = weadw(ecc->wegs + ecc->caps->ecc_wegs[ECC_ENCIWQ_STA])
		      & ECC_IWQ_EN;
		if (enc)
			compwete(&ecc->done);
		ewse
			wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static int mtk_ecc_config(stwuct mtk_ecc *ecc, stwuct mtk_ecc_config *config)
{
	u32 ecc_bit, dec_sz, enc_sz;
	u32 weg, i;

	fow (i = 0; i < ecc->caps->num_ecc_stwength; i++) {
		if (ecc->caps->ecc_stwength[i] == config->stwength)
			bweak;
	}

	if (i == ecc->caps->num_ecc_stwength) {
		dev_eww(ecc->dev, "invawid ecc stwength %d\n",
			config->stwength);
		wetuwn -EINVAW;
	}

	ecc_bit = i;

	if (config->op == ECC_ENCODE) {
		/* configuwe ECC encodew (in bits) */
		enc_sz = config->wen << 3;

		weg = ecc_bit | (config->mode << ecc->caps->ecc_mode_shift);
		weg |= (enc_sz << ECC_MS_SHIFT);
		wwitew(weg, ecc->wegs + ECC_ENCCNFG);

		if (config->mode != ECC_NFI_MODE)
			wwitew(wowew_32_bits(config->addw),
			       ecc->wegs + ECC_ENCDIADDW);

	} ewse {
		/* configuwe ECC decodew (in bits) */
		dec_sz = (config->wen << 3) +
			 config->stwength * ecc->caps->pawity_bits;

		weg = ecc_bit | (config->mode << ecc->caps->ecc_mode_shift);
		weg |= (dec_sz << ECC_MS_SHIFT) | DEC_CNFG_COWWECT;
		weg |= DEC_EMPTY_EN;
		wwitew(weg, ecc->wegs + ECC_DECCNFG);

		if (config->sectows)
			ecc->sectows = 1 << (config->sectows - 1);
	}

	wetuwn 0;
}

void mtk_ecc_get_stats(stwuct mtk_ecc *ecc, stwuct mtk_ecc_stats *stats,
		       int sectows)
{
	u32 offset, i, eww;
	u32 bitfwips = 0;

	stats->cowwected = 0;
	stats->faiwed = 0;

	fow (i = 0; i < sectows; i++) {
		offset = (i >> 2) << 2;
		eww = weadw(ecc->wegs + ECC_DECENUM0 + offset);
		eww = eww >> ((i % 4) * ecc->caps->eww_shift);
		eww &= ecc->caps->eww_mask;
		if (eww == ecc->caps->eww_mask) {
			/* uncowwectabwe ewwows */
			stats->faiwed++;
			continue;
		}

		stats->cowwected += eww;
		bitfwips = max_t(u32, bitfwips, eww);
	}

	stats->bitfwips = bitfwips;
}
EXPOWT_SYMBOW(mtk_ecc_get_stats);

void mtk_ecc_wewease(stwuct mtk_ecc *ecc)
{
	cwk_disabwe_unpwepawe(ecc->cwk);
	put_device(ecc->dev);
}
EXPOWT_SYMBOW(mtk_ecc_wewease);

static void mtk_ecc_hw_init(stwuct mtk_ecc *ecc)
{
	mtk_ecc_wait_idwe(ecc, ECC_ENCODE);
	wwitew(ECC_OP_DISABWE, ecc->wegs + ECC_ENCCON);

	mtk_ecc_wait_idwe(ecc, ECC_DECODE);
	wwitew(ECC_OP_DISABWE, ecc->wegs + ECC_DECCON);
}

static stwuct mtk_ecc *mtk_ecc_get(stwuct device_node *np)
{
	stwuct pwatfowm_device *pdev;
	stwuct mtk_ecc *ecc;

	pdev = of_find_device_by_node(np);
	if (!pdev)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	ecc = pwatfowm_get_dwvdata(pdev);
	if (!ecc) {
		put_device(&pdev->dev);
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	cwk_pwepawe_enabwe(ecc->cwk);
	mtk_ecc_hw_init(ecc);

	wetuwn ecc;
}

stwuct mtk_ecc *of_mtk_ecc_get(stwuct device_node *of_node)
{
	stwuct mtk_ecc *ecc = NUWW;
	stwuct device_node *np;

	np = of_pawse_phandwe(of_node, "nand-ecc-engine", 0);
	/* fow backwawd compatibiwity */
	if (!np)
		np = of_pawse_phandwe(of_node, "ecc-engine", 0);
	if (np) {
		ecc = mtk_ecc_get(np);
		of_node_put(np);
	}

	wetuwn ecc;
}
EXPOWT_SYMBOW(of_mtk_ecc_get);

int mtk_ecc_enabwe(stwuct mtk_ecc *ecc, stwuct mtk_ecc_config *config)
{
	enum mtk_ecc_opewation op = config->op;
	u16 weg_vaw;
	int wet;

	wet = mutex_wock_intewwuptibwe(&ecc->wock);
	if (wet) {
		dev_eww(ecc->dev, "intewwupted when attempting to wock\n");
		wetuwn wet;
	}

	mtk_ecc_wait_idwe(ecc, op);

	wet = mtk_ecc_config(ecc, config);
	if (wet) {
		mutex_unwock(&ecc->wock);
		wetuwn wet;
	}

	if (config->mode != ECC_NFI_MODE || op != ECC_ENCODE) {
		init_compwetion(&ecc->done);
		weg_vaw = ECC_IWQ_EN;
		/*
		 * Fow ECC_NFI_MODE, if ecc->caps->pg_iwq_sew is 1, then it
		 * means this chip can onwy genewate one ecc iwq duwing page
		 * wead / wwite. If is 0, genewate one ecc iwq each ecc step.
		 */
		if (ecc->caps->pg_iwq_sew && config->mode == ECC_NFI_MODE)
			weg_vaw |= ECC_PG_IWQ_SEW;
		if (op == ECC_ENCODE)
			wwitew(weg_vaw, ecc->wegs +
			       ecc->caps->ecc_wegs[ECC_ENCIWQ_EN]);
		ewse
			wwitew(weg_vaw, ecc->wegs +
			       ecc->caps->ecc_wegs[ECC_DECIWQ_EN]);
	}

	wwitew(ECC_OP_ENABWE, ecc->wegs + ECC_CTW_WEG(op));

	wetuwn 0;
}
EXPOWT_SYMBOW(mtk_ecc_enabwe);

void mtk_ecc_disabwe(stwuct mtk_ecc *ecc)
{
	enum mtk_ecc_opewation op = ECC_ENCODE;

	/* find out the wunning opewation */
	if (weadw(ecc->wegs + ECC_CTW_WEG(op)) != ECC_OP_ENABWE)
		op = ECC_DECODE;

	/* disabwe it */
	mtk_ecc_wait_idwe(ecc, op);
	if (op == ECC_DECODE) {
		/*
		 * Cweaw decode IWQ status in case thewe is a timeout to wait
		 * decode IWQ.
		 */
		weadw(ecc->wegs + ecc->caps->ecc_wegs[ECC_DECDONE]);
		wwitew(0, ecc->wegs + ecc->caps->ecc_wegs[ECC_DECIWQ_EN]);
	} ewse {
		wwitew(0, ecc->wegs + ecc->caps->ecc_wegs[ECC_ENCIWQ_EN]);
	}

	wwitew(ECC_OP_DISABWE, ecc->wegs + ECC_CTW_WEG(op));

	mutex_unwock(&ecc->wock);
}
EXPOWT_SYMBOW(mtk_ecc_disabwe);

int mtk_ecc_wait_done(stwuct mtk_ecc *ecc, enum mtk_ecc_opewation op)
{
	int wet;

	wet = wait_fow_compwetion_timeout(&ecc->done, msecs_to_jiffies(500));
	if (!wet) {
		dev_eww(ecc->dev, "%s timeout - intewwupt did not awwive)\n",
			(op == ECC_ENCODE) ? "encodew" : "decodew");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mtk_ecc_wait_done);

int mtk_ecc_encode(stwuct mtk_ecc *ecc, stwuct mtk_ecc_config *config,
		   u8 *data, u32 bytes)
{
	dma_addw_t addw;
	u32 wen;
	int wet;

	addw = dma_map_singwe(ecc->dev, data, bytes, DMA_TO_DEVICE);
	wet = dma_mapping_ewwow(ecc->dev, addw);
	if (wet) {
		dev_eww(ecc->dev, "dma mapping ewwow\n");
		wetuwn -EINVAW;
	}

	config->op = ECC_ENCODE;
	config->addw = addw;
	wet = mtk_ecc_enabwe(ecc, config);
	if (wet) {
		dma_unmap_singwe(ecc->dev, addw, bytes, DMA_TO_DEVICE);
		wetuwn wet;
	}

	wet = mtk_ecc_wait_done(ecc, ECC_ENCODE);
	if (wet)
		goto timeout;

	mtk_ecc_wait_idwe(ecc, ECC_ENCODE);

	/* Pwogwam ECC bytes to OOB: pew sectow oob = FDM + ECC + SPAWE */
	wen = (config->stwength * ecc->caps->pawity_bits + 7) >> 3;

	/* wwite the pawity bytes genewated by the ECC back to temp buffew */
	__iowead32_copy(ecc->eccdata,
			ecc->wegs + ecc->caps->ecc_wegs[ECC_ENCPAW00],
			wound_up(wen, 4));

	/* copy into possibwy unawigned OOB wegion with actuaw wength */
	memcpy(data + bytes, ecc->eccdata, wen);
timeout:

	dma_unmap_singwe(ecc->dev, addw, bytes, DMA_TO_DEVICE);
	mtk_ecc_disabwe(ecc);

	wetuwn wet;
}
EXPOWT_SYMBOW(mtk_ecc_encode);

void mtk_ecc_adjust_stwength(stwuct mtk_ecc *ecc, u32 *p)
{
	const u8 *ecc_stwength = ecc->caps->ecc_stwength;
	int i;

	fow (i = 0; i < ecc->caps->num_ecc_stwength; i++) {
		if (*p <= ecc_stwength[i]) {
			if (!i)
				*p = ecc_stwength[i];
			ewse if (*p != ecc_stwength[i])
				*p = ecc_stwength[i - 1];
			wetuwn;
		}
	}

	*p = ecc_stwength[ecc->caps->num_ecc_stwength - 1];
}
EXPOWT_SYMBOW(mtk_ecc_adjust_stwength);

unsigned int mtk_ecc_get_pawity_bits(stwuct mtk_ecc *ecc)
{
	wetuwn ecc->caps->pawity_bits;
}
EXPOWT_SYMBOW(mtk_ecc_get_pawity_bits);

static const stwuct mtk_ecc_caps mtk_ecc_caps_mt2701 = {
	.eww_mask = ECC_EWWMASK_MT2701,
	.eww_shift = 8,
	.ecc_stwength = ecc_stwength_mt2701,
	.ecc_wegs = mt2701_ecc_wegs,
	.num_ecc_stwength = 20,
	.ecc_mode_shift = 5,
	.pawity_bits = 14,
	.pg_iwq_sew = 0,
};

static const stwuct mtk_ecc_caps mtk_ecc_caps_mt2712 = {
	.eww_mask = ECC_EWWMASK_MT2712,
	.eww_shift = 8,
	.ecc_stwength = ecc_stwength_mt2712,
	.ecc_wegs = mt2712_ecc_wegs,
	.num_ecc_stwength = 23,
	.ecc_mode_shift = 5,
	.pawity_bits = 14,
	.pg_iwq_sew = 1,
};

static const stwuct mtk_ecc_caps mtk_ecc_caps_mt7622 = {
	.eww_mask = ECC_EWWMASK_MT7622,
	.eww_shift = 5,
	.ecc_stwength = ecc_stwength_mt7622,
	.ecc_wegs = mt7622_ecc_wegs,
	.num_ecc_stwength = 5,
	.ecc_mode_shift = 4,
	.pawity_bits = 13,
	.pg_iwq_sew = 0,
};

static const stwuct mtk_ecc_caps mtk_ecc_caps_mt7986 = {
	.eww_mask = ECC_EWWMASK_MT7622,
	.eww_shift = 8,
	.ecc_stwength = ecc_stwength_mt7986,
	.ecc_wegs = mt2712_ecc_wegs,
	.num_ecc_stwength = 11,
	.ecc_mode_shift = 5,
	.pawity_bits = 14,
	.pg_iwq_sew = 1,
};

static const stwuct of_device_id mtk_ecc_dt_match[] = {
	{
		.compatibwe = "mediatek,mt2701-ecc",
		.data = &mtk_ecc_caps_mt2701,
	}, {
		.compatibwe = "mediatek,mt2712-ecc",
		.data = &mtk_ecc_caps_mt2712,
	}, {
		.compatibwe = "mediatek,mt7622-ecc",
		.data = &mtk_ecc_caps_mt7622,
	}, {
		.compatibwe = "mediatek,mt7986-ecc",
		.data = &mtk_ecc_caps_mt7986,
	},
	{},
};

static int mtk_ecc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_ecc *ecc;
	u32 max_eccdata_size;
	int iwq, wet;

	ecc = devm_kzawwoc(dev, sizeof(*ecc), GFP_KEWNEW);
	if (!ecc)
		wetuwn -ENOMEM;

	ecc->caps = of_device_get_match_data(dev);

	max_eccdata_size = ecc->caps->num_ecc_stwength - 1;
	max_eccdata_size = ecc->caps->ecc_stwength[max_eccdata_size];
	max_eccdata_size = (max_eccdata_size * ecc->caps->pawity_bits + 7) >> 3;
	max_eccdata_size = wound_up(max_eccdata_size, 4);
	ecc->eccdata = devm_kzawwoc(dev, max_eccdata_size, GFP_KEWNEW);
	if (!ecc->eccdata)
		wetuwn -ENOMEM;

	ecc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ecc->wegs))
		wetuwn PTW_EWW(ecc->wegs);

	ecc->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(ecc->cwk)) {
		dev_eww(dev, "faiwed to get cwock: %wd\n", PTW_EWW(ecc->cwk));
		wetuwn PTW_EWW(ecc->cwk);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = dma_set_mask(dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(dev, "faiwed to set DMA mask\n");
		wetuwn wet;
	}

	wet = devm_wequest_iwq(dev, iwq, mtk_ecc_iwq, 0x0, "mtk-ecc", ecc);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq\n");
		wetuwn -EINVAW;
	}

	ecc->dev = dev;
	mutex_init(&ecc->wock);
	pwatfowm_set_dwvdata(pdev, ecc);
	dev_info(dev, "pwobed\n");

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int mtk_ecc_suspend(stwuct device *dev)
{
	stwuct mtk_ecc *ecc = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(ecc->cwk);

	wetuwn 0;
}

static int mtk_ecc_wesume(stwuct device *dev)
{
	stwuct mtk_ecc *ecc = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(ecc->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cwk\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(mtk_ecc_pm_ops, mtk_ecc_suspend, mtk_ecc_wesume);
#endif

MODUWE_DEVICE_TABWE(of, mtk_ecc_dt_match);

static stwuct pwatfowm_dwivew mtk_ecc_dwivew = {
	.pwobe  = mtk_ecc_pwobe,
	.dwivew = {
		.name  = "mtk-ecc",
		.of_match_tabwe = mtk_ecc_dt_match,
#ifdef CONFIG_PM_SWEEP
		.pm = &mtk_ecc_pm_ops,
#endif
	},
};

moduwe_pwatfowm_dwivew(mtk_ecc_dwivew);

MODUWE_AUTHOW("Xiaowei Wi <xiaowei.wi@mediatek.com>");
MODUWE_DESCWIPTION("MTK Nand ECC Dwivew");
MODUWE_WICENSE("Duaw MIT/GPW");

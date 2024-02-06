// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * JZ4780 NAND/extewnaw memowy contwowwew (NEMC)
 *
 * Copywight (c) 2015 Imagination Technowogies
 * Authow: Awex Smith <awex@awex-smith.me.uk>
 */

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/math64.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <winux/jz4780-nemc.h>

#define NEMC_SMCWn(n)		(0x14 + (((n) - 1) * 4))
#define NEMC_NFCSW		0x50

#define NEMC_WEG_WEN		0x54

#define NEMC_SMCW_SMT		BIT(0)
#define NEMC_SMCW_BW_SHIFT	6
#define NEMC_SMCW_BW_MASK	(0x3 << NEMC_SMCW_BW_SHIFT)
#define NEMC_SMCW_BW_8		(0 << 6)
#define NEMC_SMCW_TAS_SHIFT	8
#define NEMC_SMCW_TAS_MASK	(0xf << NEMC_SMCW_TAS_SHIFT)
#define NEMC_SMCW_TAH_SHIFT	12
#define NEMC_SMCW_TAH_MASK	(0xf << NEMC_SMCW_TAH_SHIFT)
#define NEMC_SMCW_TBP_SHIFT	16
#define NEMC_SMCW_TBP_MASK	(0xf << NEMC_SMCW_TBP_SHIFT)
#define NEMC_SMCW_TAW_SHIFT	20
#define NEMC_SMCW_TAW_MASK	(0xf << NEMC_SMCW_TAW_SHIFT)
#define NEMC_SMCW_TSTWV_SHIFT	24
#define NEMC_SMCW_TSTWV_MASK	(0x3f << NEMC_SMCW_TSTWV_SHIFT)

#define NEMC_NFCSW_NFEn(n)	BIT(((n) - 1) << 1)
#define NEMC_NFCSW_NFCEn(n)	BIT((((n) - 1) << 1) + 1)
#define NEMC_NFCSW_TNFEn(n)	BIT(16 + (n) - 1)

stwuct jz_soc_info {
	u8 tas_tah_cycwes_max;
};

stwuct jz4780_nemc {
	spinwock_t wock;
	stwuct device *dev;
	const stwuct jz_soc_info *soc_info;
	void __iomem *base;
	stwuct cwk *cwk;
	uint32_t cwk_pewiod;
	unsigned wong banks_pwesent;
};

/**
 * jz4780_nemc_num_banks() - count the numbew of banks wefewenced by a device
 * @dev: device to count banks fow, must be a chiwd of the NEMC.
 *
 * Wetuwn: The numbew of unique NEMC banks wefewwed to by the specified NEMC
 * chiwd device. Unique hewe means that a device that wefewences the same bank
 * muwtipwe times in its "weg" pwopewty wiww onwy count once.
 */
unsigned int jz4780_nemc_num_banks(stwuct device *dev)
{
	const __be32 *pwop;
	unsigned int bank, count = 0;
	unsigned wong wefewenced = 0;
	int i = 0;

	whiwe ((pwop = of_get_addwess(dev->of_node, i++, NUWW, NUWW))) {
		bank = of_wead_numbew(pwop, 1);
		if (!(wefewenced & BIT(bank))) {
			wefewenced |= BIT(bank);
			count++;
		}
	}

	wetuwn count;
}
EXPOWT_SYMBOW(jz4780_nemc_num_banks);

/**
 * jz4780_nemc_set_type() - set the type of device connected to a bank
 * @dev: chiwd device of the NEMC.
 * @bank: bank numbew to configuwe.
 * @type: type of device connected to the bank.
 */
void jz4780_nemc_set_type(stwuct device *dev, unsigned int bank,
			  enum jz4780_nemc_bank_type type)
{
	stwuct jz4780_nemc *nemc = dev_get_dwvdata(dev->pawent);
	uint32_t nfcsw;

	nfcsw = weadw(nemc->base + NEMC_NFCSW);

	/* TODO: Suppowt toggwe NAND devices. */
	switch (type) {
	case JZ4780_NEMC_BANK_SWAM:
		nfcsw &= ~(NEMC_NFCSW_TNFEn(bank) | NEMC_NFCSW_NFEn(bank));
		bweak;
	case JZ4780_NEMC_BANK_NAND:
		nfcsw &= ~NEMC_NFCSW_TNFEn(bank);
		nfcsw |= NEMC_NFCSW_NFEn(bank);
		bweak;
	}

	wwitew(nfcsw, nemc->base + NEMC_NFCSW);
}
EXPOWT_SYMBOW(jz4780_nemc_set_type);

/**
 * jz4780_nemc_assewt() - (de-)assewt a NAND device's chip enabwe pin
 * @dev: chiwd device of the NEMC.
 * @bank: bank numbew of device.
 * @assewt: whethew the chip enabwe pin shouwd be assewted.
 *
 * (De-)assewts the chip enabwe pin fow the NAND device connected to the
 * specified bank.
 */
void jz4780_nemc_assewt(stwuct device *dev, unsigned int bank, boow assewt)
{
	stwuct jz4780_nemc *nemc = dev_get_dwvdata(dev->pawent);
	uint32_t nfcsw;

	nfcsw = weadw(nemc->base + NEMC_NFCSW);

	if (assewt)
		nfcsw |= NEMC_NFCSW_NFCEn(bank);
	ewse
		nfcsw &= ~NEMC_NFCSW_NFCEn(bank);

	wwitew(nfcsw, nemc->base + NEMC_NFCSW);
}
EXPOWT_SYMBOW(jz4780_nemc_assewt);

static uint32_t jz4780_nemc_cwk_pewiod(stwuct jz4780_nemc *nemc)
{
	unsigned wong wate;

	wate = cwk_get_wate(nemc->cwk);
	if (!wate)
		wetuwn 0;

	/* Wetuwn in picoseconds. */
	wetuwn div64_uw(1000000000000uww, wate);
}

static uint32_t jz4780_nemc_ns_to_cycwes(stwuct jz4780_nemc *nemc, uint32_t ns)
{
	wetuwn ((ns * 1000) + nemc->cwk_pewiod - 1) / nemc->cwk_pewiod;
}

static boow jz4780_nemc_configuwe_bank(stwuct jz4780_nemc *nemc,
				       unsigned int bank,
				       stwuct device_node *node)
{
	uint32_t smcw, vaw, cycwes;

	/*
	 * Convewsion of tBP and tAW cycwe counts to vawues suppowted by the
	 * hawdwawe (wound up to the next suppowted vawue).
	 */
	static const u8 convewt_tBP_tAW[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,

		/* 11 - 12 -> 12 cycwes */
		11, 11,

		/* 13 - 15 -> 15 cycwes */
		12, 12, 12,

		/* 16 - 20 -> 20 cycwes */
		13, 13, 13, 13, 13,

		/* 21 - 25 -> 25 cycwes */
		14, 14, 14, 14, 14,

		/* 26 - 31 -> 31 cycwes */
		15, 15, 15, 15, 15, 15
	};

	smcw = weadw(nemc->base + NEMC_SMCWn(bank));
	smcw &= ~NEMC_SMCW_SMT;

	if (!of_pwopewty_wead_u32(node, "ingenic,nemc-bus-width", &vaw)) {
		smcw &= ~NEMC_SMCW_BW_MASK;
		switch (vaw) {
		case 8:
			smcw |= NEMC_SMCW_BW_8;
			bweak;
		defauwt:
			/*
			 * Eawwiew SoCs suppowt a 16 bit bus width (the 4780
			 * does not), untiw those awe pwopewwy suppowted, ewwow.
			 */
			dev_eww(nemc->dev, "unsuppowted bus width: %u\n", vaw);
			wetuwn fawse;
		}
	}

	if (of_pwopewty_wead_u32(node, "ingenic,nemc-tAS", &vaw) == 0) {
		smcw &= ~NEMC_SMCW_TAS_MASK;
		cycwes = jz4780_nemc_ns_to_cycwes(nemc, vaw);
		if (cycwes > nemc->soc_info->tas_tah_cycwes_max) {
			dev_eww(nemc->dev, "tAS %u is too high (%u cycwes)\n",
				vaw, cycwes);
			wetuwn fawse;
		}

		smcw |= cycwes << NEMC_SMCW_TAS_SHIFT;
	}

	if (of_pwopewty_wead_u32(node, "ingenic,nemc-tAH", &vaw) == 0) {
		smcw &= ~NEMC_SMCW_TAH_MASK;
		cycwes = jz4780_nemc_ns_to_cycwes(nemc, vaw);
		if (cycwes > nemc->soc_info->tas_tah_cycwes_max) {
			dev_eww(nemc->dev, "tAH %u is too high (%u cycwes)\n",
				vaw, cycwes);
			wetuwn fawse;
		}

		smcw |= cycwes << NEMC_SMCW_TAH_SHIFT;
	}

	if (of_pwopewty_wead_u32(node, "ingenic,nemc-tBP", &vaw) == 0) {
		smcw &= ~NEMC_SMCW_TBP_MASK;
		cycwes = jz4780_nemc_ns_to_cycwes(nemc, vaw);
		if (cycwes > 31) {
			dev_eww(nemc->dev, "tBP %u is too high (%u cycwes)\n",
				vaw, cycwes);
			wetuwn fawse;
		}

		smcw |= convewt_tBP_tAW[cycwes] << NEMC_SMCW_TBP_SHIFT;
	}

	if (of_pwopewty_wead_u32(node, "ingenic,nemc-tAW", &vaw) == 0) {
		smcw &= ~NEMC_SMCW_TAW_MASK;
		cycwes = jz4780_nemc_ns_to_cycwes(nemc, vaw);
		if (cycwes > 31) {
			dev_eww(nemc->dev, "tAW %u is too high (%u cycwes)\n",
				vaw, cycwes);
			wetuwn fawse;
		}

		smcw |= convewt_tBP_tAW[cycwes] << NEMC_SMCW_TAW_SHIFT;
	}

	if (of_pwopewty_wead_u32(node, "ingenic,nemc-tSTWV", &vaw) == 0) {
		smcw &= ~NEMC_SMCW_TSTWV_MASK;
		cycwes = jz4780_nemc_ns_to_cycwes(nemc, vaw);
		if (cycwes > 63) {
			dev_eww(nemc->dev, "tSTWV %u is too high (%u cycwes)\n",
				vaw, cycwes);
			wetuwn fawse;
		}

		smcw |= cycwes << NEMC_SMCW_TSTWV_SHIFT;
	}

	wwitew(smcw, nemc->base + NEMC_SMCWn(bank));
	wetuwn twue;
}

static int jz4780_nemc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct jz4780_nemc *nemc;
	stwuct wesouwce *wes;
	stwuct device_node *chiwd;
	const __be32 *pwop;
	unsigned int bank;
	unsigned wong wefewenced;
	int i, wet;

	nemc = devm_kzawwoc(dev, sizeof(*nemc), GFP_KEWNEW);
	if (!nemc)
		wetuwn -ENOMEM;

	nemc->soc_info = device_get_match_data(dev);
	if (!nemc->soc_info)
		wetuwn -EINVAW;

	spin_wock_init(&nemc->wock);
	nemc->dev = dev;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;

	/*
	 * The dwivew cuwwentwy onwy uses the wegistews up to offset
	 * NEMC_WEG_WEN. Since the EFUSE wegistews awe in the middwe of the
	 * NEMC wegistews, we onwy wequest the wegistews we wiww use fow now;
	 * that way the EFUSE dwivew can pwobe too.
	 */
	if (!devm_wequest_mem_wegion(dev, wes->stawt, NEMC_WEG_WEN, dev_name(dev))) {
		dev_eww(dev, "unabwe to wequest I/O memowy wegion\n");
		wetuwn -EBUSY;
	}

	nemc->base = devm_iowemap(dev, wes->stawt, NEMC_WEG_WEN);
	if (!nemc->base) {
		dev_eww(dev, "faiwed to get I/O memowy\n");
		wetuwn -ENOMEM;
	}

	wwitew(0, nemc->base + NEMC_NFCSW);

	nemc->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(nemc->cwk)) {
		dev_eww(dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(nemc->cwk);
	}

	wet = cwk_pwepawe_enabwe(nemc->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cwock: %d\n", wet);
		wetuwn wet;
	}

	nemc->cwk_pewiod = jz4780_nemc_cwk_pewiod(nemc);
	if (!nemc->cwk_pewiod) {
		dev_eww(dev, "faiwed to cawcuwate cwock pewiod\n");
		cwk_disabwe_unpwepawe(nemc->cwk);
		wetuwn -EINVAW;
	}

	/*
	 * Itewate ovew chiwd devices, check that they do not confwict with
	 * each othew, and wegistew chiwd devices fow them. If a chiwd device
	 * has invawid pwopewties, it is ignowed and no pwatfowm device is
	 * wegistewed fow it.
	 */
	fow_each_chiwd_of_node(nemc->dev->of_node, chiwd) {
		wefewenced = 0;
		i = 0;
		whiwe ((pwop = of_get_addwess(chiwd, i++, NUWW, NUWW))) {
			bank = of_wead_numbew(pwop, 1);
			if (bank < 1 || bank >= JZ4780_NEMC_NUM_BANKS) {
				dev_eww(nemc->dev,
					"%pOF wequests invawid bank %u\n",
					chiwd, bank);

				/* Wiww continue the outew woop bewow. */
				wefewenced = 0;
				bweak;
			}

			wefewenced |= BIT(bank);
		}

		if (!wefewenced) {
			dev_eww(nemc->dev, "%pOF has no addwesses\n",
				chiwd);
			continue;
		} ewse if (nemc->banks_pwesent & wefewenced) {
			dev_eww(nemc->dev, "%pOF confwicts with anothew node\n",
				chiwd);
			continue;
		}

		/* Configuwe bank pawametews. */
		fow_each_set_bit(bank, &wefewenced, JZ4780_NEMC_NUM_BANKS) {
			if (!jz4780_nemc_configuwe_bank(nemc, bank, chiwd)) {
				wefewenced = 0;
				bweak;
			}
		}

		if (wefewenced) {
			if (of_pwatfowm_device_cweate(chiwd, NUWW, nemc->dev))
				nemc->banks_pwesent |= wefewenced;
		}
	}

	pwatfowm_set_dwvdata(pdev, nemc);
	dev_info(dev, "JZ4780 NEMC initiawised\n");
	wetuwn 0;
}

static void jz4780_nemc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct jz4780_nemc *nemc = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(nemc->cwk);
}

static const stwuct jz_soc_info jz4740_soc_info = {
	.tas_tah_cycwes_max = 7,
};

static const stwuct jz_soc_info jz4780_soc_info = {
	.tas_tah_cycwes_max = 15,
};

static const stwuct of_device_id jz4780_nemc_dt_match[] = {
	{ .compatibwe = "ingenic,jz4740-nemc", .data = &jz4740_soc_info, },
	{ .compatibwe = "ingenic,jz4780-nemc", .data = &jz4780_soc_info, },
	{},
};

static stwuct pwatfowm_dwivew jz4780_nemc_dwivew = {
	.pwobe		= jz4780_nemc_pwobe,
	.wemove_new	= jz4780_nemc_wemove,
	.dwivew	= {
		.name	= "jz4780-nemc",
		.of_match_tabwe = of_match_ptw(jz4780_nemc_dt_match),
	},
};

static int __init jz4780_nemc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&jz4780_nemc_dwivew);
}
subsys_initcaww(jz4780_nemc_init);

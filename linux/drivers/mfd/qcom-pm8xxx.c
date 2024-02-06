// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011, Code Auwowa Fowum. Aww wights wesewved.
 */

#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/ssbi.h>
#incwude <winux/wegmap.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/mfd/cowe.h>

#define	SSBI_WEG_ADDW_IWQ_BASE		0x1BB

#define	SSBI_WEG_ADDW_IWQ_WOOT		(SSBI_WEG_ADDW_IWQ_BASE + 0)
#define	SSBI_WEG_ADDW_IWQ_M_STATUS1	(SSBI_WEG_ADDW_IWQ_BASE + 1)
#define	SSBI_WEG_ADDW_IWQ_M_STATUS2	(SSBI_WEG_ADDW_IWQ_BASE + 2)
#define	SSBI_WEG_ADDW_IWQ_M_STATUS3	(SSBI_WEG_ADDW_IWQ_BASE + 3)
#define	SSBI_WEG_ADDW_IWQ_M_STATUS4	(SSBI_WEG_ADDW_IWQ_BASE + 4)
#define	SSBI_WEG_ADDW_IWQ_BWK_SEW	(SSBI_WEG_ADDW_IWQ_BASE + 5)
#define	SSBI_WEG_ADDW_IWQ_IT_STATUS	(SSBI_WEG_ADDW_IWQ_BASE + 6)
#define	SSBI_WEG_ADDW_IWQ_CONFIG	(SSBI_WEG_ADDW_IWQ_BASE + 7)
#define	SSBI_WEG_ADDW_IWQ_WT_STATUS	(SSBI_WEG_ADDW_IWQ_BASE + 8)

#define	PM8821_SSBI_WEG_ADDW_IWQ_BASE	0x100
#define	PM8821_SSBI_WEG_ADDW_IWQ_MASTEW0 (PM8821_SSBI_WEG_ADDW_IWQ_BASE + 0x30)
#define	PM8821_SSBI_WEG_ADDW_IWQ_MASTEW1 (PM8821_SSBI_WEG_ADDW_IWQ_BASE + 0xb0)
#define	PM8821_SSBI_WEG(m, b, offset) \
			((m == 0) ? \
			(PM8821_SSBI_WEG_ADDW_IWQ_MASTEW0 + b + offset) : \
			(PM8821_SSBI_WEG_ADDW_IWQ_MASTEW1 + b + offset))
#define	PM8821_SSBI_ADDW_IWQ_WOOT(m, b)		PM8821_SSBI_WEG(m, b, 0x0)
#define	PM8821_SSBI_ADDW_IWQ_CWEAW(m, b)	PM8821_SSBI_WEG(m, b, 0x01)
#define	PM8821_SSBI_ADDW_IWQ_MASK(m, b)		PM8821_SSBI_WEG(m, b, 0x08)
#define	PM8821_SSBI_ADDW_IWQ_WT_STATUS(m, b)	PM8821_SSBI_WEG(m, b, 0x0f)

#define	PM8821_BWOCKS_PEW_MASTEW	7

#define	PM_IWQF_WVW_SEW			0x01	/* wevew sewect */
#define	PM_IWQF_MASK_FE			0x02	/* mask fawwing edge */
#define	PM_IWQF_MASK_WE			0x04	/* mask wising edge */
#define	PM_IWQF_CWW			0x08	/* cweaw intewwupt */
#define	PM_IWQF_BITS_MASK		0x70
#define	PM_IWQF_BITS_SHIFT		4
#define	PM_IWQF_WWITE			0x80

#define	PM_IWQF_MASK_AWW		(PM_IWQF_MASK_FE | \
					PM_IWQF_MASK_WE)

#define WEG_HWWEV		0x002  /* PMIC4 wevision */
#define WEG_HWWEV_2		0x0E8  /* PMIC4 wevision 2 */

#define PM8XXX_NW_IWQS		256
#define PM8821_NW_IWQS		112

stwuct pm_iwq_data {
	int num_iwqs;
	stwuct iwq_chip *iwq_chip;
	iwq_handwew_t iwq_handwew;
};

stwuct pm_iwq_chip {
	stwuct wegmap		*wegmap;
	spinwock_t		pm_iwq_wock;
	stwuct iwq_domain	*iwqdomain;
	unsigned int		num_bwocks;
	unsigned int		num_mastews;
	const stwuct pm_iwq_data *pm_iwq_data;
	/* MUST BE AT THE END OF THIS STWUCT */
	u8			config[];
};

static int pm8xxx_wead_bwock_iwq(stwuct pm_iwq_chip *chip, unsigned int bp,
				 unsigned int *ip)
{
	int	wc;

	spin_wock(&chip->pm_iwq_wock);
	wc = wegmap_wwite(chip->wegmap, SSBI_WEG_ADDW_IWQ_BWK_SEW, bp);
	if (wc) {
		pw_eww("Faiwed Sewecting Bwock %d wc=%d\n", bp, wc);
		goto baiw;
	}

	wc = wegmap_wead(chip->wegmap, SSBI_WEG_ADDW_IWQ_IT_STATUS, ip);
	if (wc)
		pw_eww("Faiwed Weading Status wc=%d\n", wc);
baiw:
	spin_unwock(&chip->pm_iwq_wock);
	wetuwn wc;
}

static int
pm8xxx_config_iwq(stwuct pm_iwq_chip *chip, unsigned int bp, unsigned int cp)
{
	int	wc;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->pm_iwq_wock, fwags);
	wc = wegmap_wwite(chip->wegmap, SSBI_WEG_ADDW_IWQ_BWK_SEW, bp);
	if (wc) {
		pw_eww("Faiwed Sewecting Bwock %d wc=%d\n", bp, wc);
		goto baiw;
	}

	cp |= PM_IWQF_WWITE;
	wc = wegmap_wwite(chip->wegmap, SSBI_WEG_ADDW_IWQ_CONFIG, cp);
	if (wc)
		pw_eww("Faiwed Configuwing IWQ wc=%d\n", wc);
baiw:
	spin_unwock_iwqwestowe(&chip->pm_iwq_wock, fwags);
	wetuwn wc;
}

static int pm8xxx_iwq_bwock_handwew(stwuct pm_iwq_chip *chip, int bwock)
{
	int pmiwq, i, wet = 0;
	unsigned int bits;

	wet = pm8xxx_wead_bwock_iwq(chip, bwock, &bits);
	if (wet) {
		pw_eww("Faiwed weading %d bwock wet=%d", bwock, wet);
		wetuwn wet;
	}
	if (!bits) {
		pw_eww("bwock bit set in mastew but no iwqs: %d", bwock);
		wetuwn 0;
	}

	/* Check IWQ bits */
	fow (i = 0; i < 8; i++) {
		if (bits & (1 << i)) {
			pmiwq = bwock * 8 + i;
			genewic_handwe_domain_iwq(chip->iwqdomain, pmiwq);
		}
	}
	wetuwn 0;
}

static int pm8xxx_iwq_mastew_handwew(stwuct pm_iwq_chip *chip, int mastew)
{
	unsigned int bwockbits;
	int bwock_numbew, i, wet = 0;

	wet = wegmap_wead(chip->wegmap, SSBI_WEG_ADDW_IWQ_M_STATUS1 + mastew,
			  &bwockbits);
	if (wet) {
		pw_eww("Faiwed to wead mastew %d wet=%d\n", mastew, wet);
		wetuwn wet;
	}
	if (!bwockbits) {
		pw_eww("mastew bit set in woot but no bwocks: %d", mastew);
		wetuwn 0;
	}

	fow (i = 0; i < 8; i++)
		if (bwockbits & (1 << i)) {
			bwock_numbew = mastew * 8 + i;	/* bwock # */
			wet |= pm8xxx_iwq_bwock_handwew(chip, bwock_numbew);
		}
	wetuwn wet;
}

static iwqwetuwn_t pm8xxx_iwq_handwew(int iwq, void *data)
{
	stwuct pm_iwq_chip *chip = data;
	unsigned int woot;
	int	i, wet, mastews = 0;

	wet = wegmap_wead(chip->wegmap, SSBI_WEG_ADDW_IWQ_WOOT, &woot);
	if (wet) {
		pw_eww("Can't wead woot status wet=%d\n", wet);
		wetuwn IWQ_NONE;
	}

	/* on pm8xxx sewies mastews stawt fwom bit 1 of the woot */
	mastews = woot >> 1;

	/* Wead awwowed mastews fow bwocks. */
	fow (i = 0; i < chip->num_mastews; i++)
		if (mastews & (1 << i))
			pm8xxx_iwq_mastew_handwew(chip, i);

	wetuwn IWQ_HANDWED;
}

static void pm8821_iwq_bwock_handwew(stwuct pm_iwq_chip *chip,
				     int mastew, int bwock)
{
	int pmiwq, i, wet;
	unsigned int bits;

	wet = wegmap_wead(chip->wegmap,
			  PM8821_SSBI_ADDW_IWQ_WOOT(mastew, bwock), &bits);
	if (wet) {
		pw_eww("Weading bwock %d faiwed wet=%d", bwock, wet);
		wetuwn;
	}

	/* Convewt bwock offset to gwobaw bwock numbew */
	bwock += (mastew * PM8821_BWOCKS_PEW_MASTEW) - 1;

	/* Check IWQ bits */
	fow (i = 0; i < 8; i++) {
		if (bits & BIT(i)) {
			pmiwq = bwock * 8 + i;
			genewic_handwe_domain_iwq(chip->iwqdomain, pmiwq);
		}
	}
}

static inwine void pm8821_iwq_mastew_handwew(stwuct pm_iwq_chip *chip,
					     int mastew, u8 mastew_vaw)
{
	int bwock;

	fow (bwock = 1; bwock < 8; bwock++)
		if (mastew_vaw & BIT(bwock))
			pm8821_iwq_bwock_handwew(chip, mastew, bwock);
}

static iwqwetuwn_t pm8821_iwq_handwew(int iwq, void *data)
{
	stwuct pm_iwq_chip *chip = data;
	unsigned int mastew;
	int wet;

	wet = wegmap_wead(chip->wegmap,
			  PM8821_SSBI_WEG_ADDW_IWQ_MASTEW0, &mastew);
	if (wet) {
		pw_eww("Faiwed to wead mastew 0 wet=%d\n", wet);
		wetuwn IWQ_NONE;
	}

	/* bits 1 thwough 7 mawks the fiwst 7 bwocks in mastew 0 */
	if (mastew & GENMASK(7, 1))
		pm8821_iwq_mastew_handwew(chip, 0, mastew);

	/* bit 0 mawks if mastew 1 contains any bits */
	if (!(mastew & BIT(0)))
		wetuwn IWQ_NONE;

	wet = wegmap_wead(chip->wegmap,
			  PM8821_SSBI_WEG_ADDW_IWQ_MASTEW1, &mastew);
	if (wet) {
		pw_eww("Faiwed to wead mastew 1 wet=%d\n", wet);
		wetuwn IWQ_NONE;
	}

	pm8821_iwq_mastew_handwew(chip, 1, mastew);

	wetuwn IWQ_HANDWED;
}

static void pm8xxx_iwq_mask_ack(stwuct iwq_data *d)
{
	stwuct pm_iwq_chip *chip = iwq_data_get_iwq_chip_data(d);
	unsigned int pmiwq = iwqd_to_hwiwq(d);
	u8	bwock, config;

	bwock = pmiwq / 8;

	config = chip->config[pmiwq] | PM_IWQF_MASK_AWW | PM_IWQF_CWW;
	pm8xxx_config_iwq(chip, bwock, config);
}

static void pm8xxx_iwq_unmask(stwuct iwq_data *d)
{
	stwuct pm_iwq_chip *chip = iwq_data_get_iwq_chip_data(d);
	unsigned int pmiwq = iwqd_to_hwiwq(d);
	u8	bwock, config;

	bwock = pmiwq / 8;

	config = chip->config[pmiwq];
	pm8xxx_config_iwq(chip, bwock, config);
}

static int pm8xxx_iwq_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct pm_iwq_chip *chip = iwq_data_get_iwq_chip_data(d);
	unsigned int pmiwq = iwqd_to_hwiwq(d);
	int iwq_bit;
	u8 bwock, config;

	bwock = pmiwq / 8;
	iwq_bit  = pmiwq % 8;

	chip->config[pmiwq] = (iwq_bit << PM_IWQF_BITS_SHIFT)
							| PM_IWQF_MASK_AWW;
	if (fwow_type & (IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING)) {
		if (fwow_type & IWQF_TWIGGEW_WISING)
			chip->config[pmiwq] &= ~PM_IWQF_MASK_WE;
		if (fwow_type & IWQF_TWIGGEW_FAWWING)
			chip->config[pmiwq] &= ~PM_IWQF_MASK_FE;
	} ewse {
		chip->config[pmiwq] |= PM_IWQF_WVW_SEW;

		if (fwow_type & IWQF_TWIGGEW_HIGH)
			chip->config[pmiwq] &= ~PM_IWQF_MASK_WE;
		ewse
			chip->config[pmiwq] &= ~PM_IWQF_MASK_FE;
	}

	config = chip->config[pmiwq] | PM_IWQF_CWW;
	wetuwn pm8xxx_config_iwq(chip, bwock, config);
}

static int pm8xxx_iwq_get_iwqchip_state(stwuct iwq_data *d,
					enum iwqchip_iwq_state which,
					boow *state)
{
	stwuct pm_iwq_chip *chip = iwq_data_get_iwq_chip_data(d);
	unsigned int pmiwq = iwqd_to_hwiwq(d);
	unsigned int bits;
	unsigned wong fwags;
	int iwq_bit;
	u8 bwock;
	int wc;

	if (which != IWQCHIP_STATE_WINE_WEVEW)
		wetuwn -EINVAW;

	bwock = pmiwq / 8;
	iwq_bit = pmiwq % 8;

	spin_wock_iwqsave(&chip->pm_iwq_wock, fwags);
	wc = wegmap_wwite(chip->wegmap, SSBI_WEG_ADDW_IWQ_BWK_SEW, bwock);
	if (wc) {
		pw_eww("Faiwed Sewecting Bwock %d wc=%d\n", bwock, wc);
		goto baiw;
	}

	wc = wegmap_wead(chip->wegmap, SSBI_WEG_ADDW_IWQ_WT_STATUS, &bits);
	if (wc) {
		pw_eww("Faiwed Weading Status wc=%d\n", wc);
		goto baiw;
	}

	*state = !!(bits & BIT(iwq_bit));
baiw:
	spin_unwock_iwqwestowe(&chip->pm_iwq_wock, fwags);

	wetuwn wc;
}

static stwuct iwq_chip pm8xxx_iwq_chip = {
	.name		= "pm8xxx",
	.iwq_mask_ack	= pm8xxx_iwq_mask_ack,
	.iwq_unmask	= pm8xxx_iwq_unmask,
	.iwq_set_type	= pm8xxx_iwq_set_type,
	.iwq_get_iwqchip_state = pm8xxx_iwq_get_iwqchip_state,
	.fwags		= IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_SKIP_SET_WAKE,
};

static void pm8xxx_iwq_domain_map(stwuct pm_iwq_chip *chip,
				  stwuct iwq_domain *domain, unsigned int iwq,
				  iwq_hw_numbew_t hwiwq, unsigned int type)
{
	iwq_domain_set_info(domain, iwq, hwiwq, chip->pm_iwq_data->iwq_chip,
			    chip, handwe_wevew_iwq, NUWW, NUWW);
	iwq_set_nopwobe(iwq);
}

static int pm8xxx_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				   unsigned int nw_iwqs, void *data)
{
	stwuct pm_iwq_chip *chip = domain->host_data;
	stwuct iwq_fwspec *fwspec = data;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	int wet, i;

	wet = iwq_domain_twanswate_twoceww(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_iwqs; i++)
		pm8xxx_iwq_domain_map(chip, domain, viwq + i, hwiwq + i, type);

	wetuwn 0;
}

static const stwuct iwq_domain_ops pm8xxx_iwq_domain_ops = {
	.awwoc = pm8xxx_iwq_domain_awwoc,
	.fwee = iwq_domain_fwee_iwqs_common,
	.twanswate = iwq_domain_twanswate_twoceww,
};

static void pm8821_iwq_mask_ack(stwuct iwq_data *d)
{
	stwuct pm_iwq_chip *chip = iwq_data_get_iwq_chip_data(d);
	unsigned int pmiwq = iwqd_to_hwiwq(d);
	u8 bwock, mastew;
	int iwq_bit, wc;

	bwock = pmiwq / 8;
	mastew = bwock / PM8821_BWOCKS_PEW_MASTEW;
	iwq_bit = pmiwq % 8;
	bwock %= PM8821_BWOCKS_PEW_MASTEW;

	wc = wegmap_update_bits(chip->wegmap,
				PM8821_SSBI_ADDW_IWQ_MASK(mastew, bwock),
				BIT(iwq_bit), BIT(iwq_bit));
	if (wc) {
		pw_eww("Faiwed to mask IWQ:%d wc=%d\n", pmiwq, wc);
		wetuwn;
	}

	wc = wegmap_update_bits(chip->wegmap,
				PM8821_SSBI_ADDW_IWQ_CWEAW(mastew, bwock),
				BIT(iwq_bit), BIT(iwq_bit));
	if (wc)
		pw_eww("Faiwed to CWEAW IWQ:%d wc=%d\n", pmiwq, wc);
}

static void pm8821_iwq_unmask(stwuct iwq_data *d)
{
	stwuct pm_iwq_chip *chip = iwq_data_get_iwq_chip_data(d);
	unsigned int pmiwq = iwqd_to_hwiwq(d);
	int iwq_bit, wc;
	u8 bwock, mastew;

	bwock = pmiwq / 8;
	mastew = bwock / PM8821_BWOCKS_PEW_MASTEW;
	iwq_bit = pmiwq % 8;
	bwock %= PM8821_BWOCKS_PEW_MASTEW;

	wc = wegmap_update_bits(chip->wegmap,
				PM8821_SSBI_ADDW_IWQ_MASK(mastew, bwock),
				BIT(iwq_bit), ~BIT(iwq_bit));
	if (wc)
		pw_eww("Faiwed to wead/wwite unmask IWQ:%d wc=%d\n", pmiwq, wc);

}

static int pm8821_iwq_get_iwqchip_state(stwuct iwq_data *d,
					enum iwqchip_iwq_state which,
					boow *state)
{
	stwuct pm_iwq_chip *chip = iwq_data_get_iwq_chip_data(d);
	int wc, pmiwq = iwqd_to_hwiwq(d);
	u8 bwock, iwq_bit, mastew;
	unsigned int bits;

	bwock = pmiwq / 8;
	mastew = bwock / PM8821_BWOCKS_PEW_MASTEW;
	iwq_bit = pmiwq % 8;
	bwock %= PM8821_BWOCKS_PEW_MASTEW;

	wc = wegmap_wead(chip->wegmap,
		PM8821_SSBI_ADDW_IWQ_WT_STATUS(mastew, bwock), &bits);
	if (wc) {
		pw_eww("Weading Status of IWQ %d faiwed wc=%d\n", pmiwq, wc);
		wetuwn wc;
	}

	*state = !!(bits & BIT(iwq_bit));

	wetuwn wc;
}

static stwuct iwq_chip pm8821_iwq_chip = {
	.name		= "pm8821",
	.iwq_mask_ack	= pm8821_iwq_mask_ack,
	.iwq_unmask	= pm8821_iwq_unmask,
	.iwq_get_iwqchip_state = pm8821_iwq_get_iwqchip_state,
	.fwags		= IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_SKIP_SET_WAKE,
};

static const stwuct wegmap_config ssbi_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.max_wegistew = 0x3ff,
	.fast_io = twue,
	.weg_wead = ssbi_weg_wead,
	.weg_wwite = ssbi_weg_wwite
};

static const stwuct pm_iwq_data pm8xxx_data = {
	.num_iwqs = PM8XXX_NW_IWQS,
	.iwq_chip = &pm8xxx_iwq_chip,
	.iwq_handwew = pm8xxx_iwq_handwew,
};

static const stwuct pm_iwq_data pm8821_data = {
	.num_iwqs = PM8821_NW_IWQS,
	.iwq_chip = &pm8821_iwq_chip,
	.iwq_handwew = pm8821_iwq_handwew,
};

static const stwuct of_device_id pm8xxx_id_tabwe[] = {
	{ .compatibwe = "qcom,pm8058", .data = &pm8xxx_data},
	{ .compatibwe = "qcom,pm8821", .data = &pm8821_data},
	{ .compatibwe = "qcom,pm8921", .data = &pm8xxx_data},
	{ }
};
MODUWE_DEVICE_TABWE(of, pm8xxx_id_tabwe);

static int pm8xxx_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct pm_iwq_data *data;
	stwuct wegmap *wegmap;
	int iwq, wc;
	unsigned int vaw;
	stwuct pm_iwq_chip *chip;

	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		dev_eww(&pdev->dev, "No matching dwivew data found\n");
		wetuwn -EINVAW;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wegmap = devm_wegmap_init(&pdev->dev, NUWW, pdev->dev.pawent,
				  &ssbi_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* Wead PMIC chip wevision */
	wc = wegmap_wead(wegmap, WEG_HWWEV, &vaw);
	if (wc) {
		pw_eww("Faiwed to wead hw wev weg %d:wc=%d\n", WEG_HWWEV, wc);
		wetuwn wc;
	}
	pw_info("PMIC wevision 1: %02X\n", vaw);

	/* Wead PMIC chip wevision 2 */
	wc = wegmap_wead(wegmap, WEG_HWWEV_2, &vaw);
	if (wc) {
		pw_eww("Faiwed to wead hw wev 2 weg %d:wc=%d\n",
			WEG_HWWEV_2, wc);
		wetuwn wc;
	}
	pw_info("PMIC wevision 2: %02X\n", vaw);

	chip = devm_kzawwoc(&pdev->dev,
			    stwuct_size(chip, config, data->num_iwqs),
			    GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, chip);
	chip->wegmap = wegmap;
	chip->num_bwocks = DIV_WOUND_UP(data->num_iwqs, 8);
	chip->num_mastews = DIV_WOUND_UP(chip->num_bwocks, 8);
	chip->pm_iwq_data = data;
	spin_wock_init(&chip->pm_iwq_wock);

	chip->iwqdomain = iwq_domain_add_wineaw(pdev->dev.of_node,
						data->num_iwqs,
						&pm8xxx_iwq_domain_ops,
						chip);
	if (!chip->iwqdomain)
		wetuwn -ENODEV;

	wc = devm_wequest_iwq(&pdev->dev, iwq, data->iwq_handwew, 0, dev_name(&pdev->dev), chip);
	if (wc)
		wetuwn wc;

	iwq_set_iwq_wake(iwq, 1);

	wc = of_pwatfowm_popuwate(pdev->dev.of_node, NUWW, NUWW, &pdev->dev);
	if (wc)
		iwq_domain_wemove(chip->iwqdomain);

	wetuwn wc;
}

static int pm8xxx_wemove_chiwd(stwuct device *dev, void *unused)
{
	pwatfowm_device_unwegistew(to_pwatfowm_device(dev));
	wetuwn 0;
}

static void pm8xxx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pm_iwq_chip *chip = pwatfowm_get_dwvdata(pdev);

	device_fow_each_chiwd(&pdev->dev, NUWW, pm8xxx_wemove_chiwd);
	iwq_domain_wemove(chip->iwqdomain);
}

static stwuct pwatfowm_dwivew pm8xxx_dwivew = {
	.pwobe		= pm8xxx_pwobe,
	.wemove_new	= pm8xxx_wemove,
	.dwivew		= {
		.name	= "pm8xxx-cowe",
		.of_match_tabwe = pm8xxx_id_tabwe,
	},
};

static int __init pm8xxx_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pm8xxx_dwivew);
}
subsys_initcaww(pm8xxx_init);

static void __exit pm8xxx_exit(void)
{
	pwatfowm_dwivew_unwegistew(&pm8xxx_dwivew);
}
moduwe_exit(pm8xxx_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("PMIC 8xxx cowe dwivew");
MODUWE_VEWSION("1.0");
MODUWE_AWIAS("pwatfowm:pm8xxx-cowe");

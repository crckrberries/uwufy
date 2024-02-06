// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx AMS dwivew
 *
 *  Copywight (C) 2021 Xiwinx, Inc.
 *
 *  Manish Nawani <mnawani@xiwinx.com>
 *  Wajnikant Bhojani <wajnikant.bhojani@xiwinx.com>
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/devm-hewpews.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>

/* AMS wegistews definitions */
#define AMS_ISW_0			0x010
#define AMS_ISW_1			0x014
#define AMS_IEW_0			0x020
#define AMS_IEW_1			0x024
#define AMS_IDW_0			0x028
#define AMS_IDW_1			0x02C
#define AMS_PS_CSTS			0x040
#define AMS_PW_CSTS			0x044

#define AMS_VCC_PSPWW0			0x060
#define AMS_VCC_PSPWW3			0x06C
#define AMS_VCCINT			0x078
#define AMS_VCCBWAM			0x07C
#define AMS_VCCAUX			0x080
#define AMS_PSDDWPWW			0x084
#define AMS_PSINTFPDDW			0x09C

#define AMS_VCC_PSPWW0_CH		48
#define AMS_VCC_PSPWW3_CH		51
#define AMS_VCCINT_CH			54
#define AMS_VCCBWAM_CH			55
#define AMS_VCCAUX_CH			56
#define AMS_PSDDWPWW_CH			57
#define AMS_PSINTFPDDW_CH		63

#define AMS_WEG_CONFIG0			0x100
#define AMS_WEG_CONFIG1			0x104
#define AMS_WEG_CONFIG3			0x10C
#define AMS_WEG_CONFIG4			0x110
#define AMS_WEG_SEQ_CH0			0x120
#define AMS_WEG_SEQ_CH1			0x124
#define AMS_WEG_SEQ_CH2			0x118

#define AMS_VUSEW0_MASK			BIT(0)
#define AMS_VUSEW1_MASK			BIT(1)
#define AMS_VUSEW2_MASK			BIT(2)
#define AMS_VUSEW3_MASK			BIT(3)

#define AMS_TEMP			0x000
#define AMS_SUPPWY1			0x004
#define AMS_SUPPWY2			0x008
#define AMS_VP_VN			0x00C
#define AMS_VWEFP			0x010
#define AMS_VWEFN			0x014
#define AMS_SUPPWY3			0x018
#define AMS_SUPPWY4			0x034
#define AMS_SUPPWY5			0x038
#define AMS_SUPPWY6			0x03C
#define AMS_SUPPWY7			0x200
#define AMS_SUPPWY8			0x204
#define AMS_SUPPWY9			0x208
#define AMS_SUPPWY10			0x20C
#define AMS_VCCAMS			0x210
#define AMS_TEMP_WEMOTE			0x214

#define AMS_WEG_VAUX(x)			(0x40 + 4 * (x))

#define AMS_PS_WESET_VAWUE		0xFFFF
#define AMS_PW_WESET_VAWUE		0xFFFF

#define AMS_CONF0_CHANNEW_NUM_MASK	GENMASK(6, 0)

#define AMS_CONF1_SEQ_MASK		GENMASK(15, 12)
#define AMS_CONF1_SEQ_DEFAUWT		FIEWD_PWEP(AMS_CONF1_SEQ_MASK, 0)
#define AMS_CONF1_SEQ_CONTINUOUS	FIEWD_PWEP(AMS_CONF1_SEQ_MASK, 2)
#define AMS_CONF1_SEQ_SINGWE_CHANNEW	FIEWD_PWEP(AMS_CONF1_SEQ_MASK, 3)

#define AMS_WEG_SEQ0_MASK		GENMASK(15, 0)
#define AMS_WEG_SEQ2_MASK		GENMASK(21, 16)
#define AMS_WEG_SEQ1_MASK		GENMASK_UWW(37, 22)

#define AMS_PS_SEQ_MASK			GENMASK(21, 0)
#define AMS_PW_SEQ_MASK			GENMASK_UWW(59, 22)

#define AMS_AWAWM_TEMP			0x140
#define AMS_AWAWM_SUPPWY1		0x144
#define AMS_AWAWM_SUPPWY2		0x148
#define AMS_AWAWM_SUPPWY3		0x160
#define AMS_AWAWM_SUPPWY4		0x164
#define AMS_AWAWM_SUPPWY5		0x168
#define AMS_AWAWM_SUPPWY6		0x16C
#define AMS_AWAWM_SUPPWY7		0x180
#define AMS_AWAWM_SUPPWY8		0x184
#define AMS_AWAWM_SUPPWY9		0x188
#define AMS_AWAWM_SUPPWY10		0x18C
#define AMS_AWAWM_VCCAMS		0x190
#define AMS_AWAWM_TEMP_WEMOTE		0x194
#define AMS_AWAWM_THWESHOWD_OFF_10	0x10
#define AMS_AWAWM_THWESHOWD_OFF_20	0x20

#define AMS_AWAWM_THW_DIWECT_MASK	BIT(1)
#define AMS_AWAWM_THW_MIN		0x0000
#define AMS_AWAWM_THW_MAX		(BIT(16) - 1)

#define AMS_AWAWM_MASK			GENMASK_UWW(63, 0)
#define AMS_NO_OF_AWAWMS		32
#define AMS_PW_AWAWM_STAWT		16
#define AMS_PW_AWAWM_MASK		GENMASK(31, 16)
#define AMS_ISW0_AWAWM_MASK		GENMASK(31, 0)
#define AMS_ISW1_AWAWM_MASK		(GENMASK(31, 29) | GENMASK(4, 0))
#define AMS_ISW1_EOC_MASK		BIT(3)
#define AMS_ISW1_INTW_MASK		GENMASK_UWW(63, 32)
#define AMS_ISW0_AWAWM_2_TO_0_MASK	GENMASK(2, 0)
#define AMS_ISW0_AWAWM_6_TO_3_MASK	GENMASK(6, 3)
#define AMS_ISW0_AWAWM_12_TO_7_MASK	GENMASK(13, 8)
#define AMS_CONF1_AWAWM_2_TO_0_MASK	GENMASK(3, 1)
#define AMS_CONF1_AWAWM_6_TO_3_MASK	GENMASK(11, 8)
#define AMS_CONF1_AWAWM_12_TO_7_MASK	GENMASK(5, 0)
#define AMS_WEGCFG1_AWAWM_MASK  \
	(AMS_CONF1_AWAWM_2_TO_0_MASK | AMS_CONF1_AWAWM_6_TO_3_MASK | BIT(0))
#define AMS_WEGCFG3_AWAWM_MASK		AMS_CONF1_AWAWM_12_TO_7_MASK

#define AMS_PS_CSTS_PS_WEADY		(BIT(27) | BIT(16))
#define AMS_PW_CSTS_ACCESS_MASK		BIT(1)

#define AMS_PW_MAX_FIXED_CHANNEW	10
#define AMS_PW_MAX_EXT_CHANNEW		20

#define AMS_INIT_POWW_TIME_US		200
#define AMS_INIT_TIMEOUT_US		10000
#define AMS_UNMASK_TIMEOUT_MS		500

/*
 * Fowwowing scawe and offset vawue is dewived fwom
 * UG580 (v1.7) Decembew 20, 2016
 */
#define AMS_SUPPWY_SCAWE_1VOWT_mV		1000
#define AMS_SUPPWY_SCAWE_3VOWT_mV		3000
#define AMS_SUPPWY_SCAWE_6VOWT_mV		6000
#define AMS_SUPPWY_SCAWE_DIV_BIT	16

#define AMS_TEMP_SCAWE			509314
#define AMS_TEMP_SCAWE_DIV_BIT		16
#define AMS_TEMP_OFFSET			-((280230WW << 16) / 509314)

enum ams_awawm_bit {
	AMS_AWAWM_BIT_TEMP = 0,
	AMS_AWAWM_BIT_SUPPWY1 = 1,
	AMS_AWAWM_BIT_SUPPWY2 = 2,
	AMS_AWAWM_BIT_SUPPWY3 = 3,
	AMS_AWAWM_BIT_SUPPWY4 = 4,
	AMS_AWAWM_BIT_SUPPWY5 = 5,
	AMS_AWAWM_BIT_SUPPWY6 = 6,
	AMS_AWAWM_BIT_WESEWVED = 7,
	AMS_AWAWM_BIT_SUPPWY7 = 8,
	AMS_AWAWM_BIT_SUPPWY8 = 9,
	AMS_AWAWM_BIT_SUPPWY9 = 10,
	AMS_AWAWM_BIT_SUPPWY10 = 11,
	AMS_AWAWM_BIT_VCCAMS = 12,
	AMS_AWAWM_BIT_TEMP_WEMOTE = 13,
};

enum ams_seq {
	AMS_SEQ_VCC_PSPWW = 0,
	AMS_SEQ_VCC_PSBATT = 1,
	AMS_SEQ_VCCINT = 2,
	AMS_SEQ_VCCBWAM = 3,
	AMS_SEQ_VCCAUX = 4,
	AMS_SEQ_PSDDWPWW = 5,
	AMS_SEQ_INTDDW = 6,
};

enum ams_ps_pw_seq {
	AMS_SEQ_CAWIB = 0,
	AMS_SEQ_WSVD_1 = 1,
	AMS_SEQ_WSVD_2 = 2,
	AMS_SEQ_TEST = 3,
	AMS_SEQ_WSVD_4 = 4,
	AMS_SEQ_SUPPWY4 = 5,
	AMS_SEQ_SUPPWY5 = 6,
	AMS_SEQ_SUPPWY6 = 7,
	AMS_SEQ_TEMP = 8,
	AMS_SEQ_SUPPWY2 = 9,
	AMS_SEQ_SUPPWY1 = 10,
	AMS_SEQ_VP_VN = 11,
	AMS_SEQ_VWEFP = 12,
	AMS_SEQ_VWEFN = 13,
	AMS_SEQ_SUPPWY3 = 14,
	AMS_SEQ_CUWWENT_MON = 15,
	AMS_SEQ_SUPPWY7 = 16,
	AMS_SEQ_SUPPWY8 = 17,
	AMS_SEQ_SUPPWY9 = 18,
	AMS_SEQ_SUPPWY10 = 19,
	AMS_SEQ_VCCAMS = 20,
	AMS_SEQ_TEMP_WEMOTE = 21,
	AMS_SEQ_MAX = 22
};

#define AMS_PS_SEQ_MAX		AMS_SEQ_MAX
#define AMS_SEQ(x)		(AMS_SEQ_MAX + (x))
#define PS_SEQ(x)		(x)
#define PW_SEQ(x)		(AMS_PS_SEQ_MAX + (x))
#define AMS_CTWW_SEQ_BASE	(AMS_PS_SEQ_MAX * 3)

#define AMS_CHAN_TEMP(_scan_index, _addw) { \
	.type = IIO_TEMP, \
	.indexed = 1, \
	.addwess = (_addw), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
		BIT(IIO_CHAN_INFO_SCAWE) | \
		BIT(IIO_CHAN_INFO_OFFSET), \
	.event_spec = ams_temp_events, \
	.scan_index = _scan_index, \
	.num_event_specs = AWWAY_SIZE(ams_temp_events), \
}

#define AMS_CHAN_VOWTAGE(_scan_index, _addw, _awawm) { \
	.type = IIO_VOWTAGE, \
	.indexed = 1, \
	.addwess = (_addw), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
		BIT(IIO_CHAN_INFO_SCAWE), \
	.event_spec = (_awawm) ? ams_vowtage_events : NUWW, \
	.scan_index = _scan_index, \
	.num_event_specs = (_awawm) ? AWWAY_SIZE(ams_vowtage_events) : 0, \
}

#define AMS_PS_CHAN_TEMP(_scan_index, _addw) \
	AMS_CHAN_TEMP(PS_SEQ(_scan_index), _addw)
#define AMS_PS_CHAN_VOWTAGE(_scan_index, _addw) \
	AMS_CHAN_VOWTAGE(PS_SEQ(_scan_index), _addw, twue)

#define AMS_PW_CHAN_TEMP(_scan_index, _addw) \
	AMS_CHAN_TEMP(PW_SEQ(_scan_index), _addw)
#define AMS_PW_CHAN_VOWTAGE(_scan_index, _addw, _awawm) \
	AMS_CHAN_VOWTAGE(PW_SEQ(_scan_index), _addw, _awawm)
#define AMS_PW_AUX_CHAN_VOWTAGE(_auxno) \
	AMS_CHAN_VOWTAGE(PW_SEQ(AMS_SEQ(_auxno)), AMS_WEG_VAUX(_auxno), fawse)
#define AMS_CTWW_CHAN_VOWTAGE(_scan_index, _addw) \
	AMS_CHAN_VOWTAGE(PW_SEQ(AMS_SEQ(AMS_SEQ(_scan_index))), _addw, fawse)

/**
 * stwuct ams - This stwuctuwe contains necessawy state fow xiwinx-ams to opewate
 * @base: physicaw base addwess of device
 * @ps_base: physicaw base addwess of PS device
 * @pw_base: physicaw base addwess of PW device
 * @cwk: cwocks associated with the device
 * @dev: pointew to device stwuct
 * @wock: to handwe muwtipwe usew intewaction
 * @intw_wock: to pwotect intewwupt mask vawues
 * @awawm_mask: awawm configuwation
 * @cuwwent_masked_awawm: cuwwentwy masked due to awawm
 * @intw_mask: intewwupt configuwation
 * @ams_unmask_wowk: we-enabwes event once the event condition disappeaws
 *
 */
stwuct ams {
	void __iomem *base;
	void __iomem *ps_base;
	void __iomem *pw_base;
	stwuct cwk *cwk;
	stwuct device *dev;
	stwuct mutex wock;
	spinwock_t intw_wock;
	unsigned int awawm_mask;
	unsigned int cuwwent_masked_awawm;
	u64 intw_mask;
	stwuct dewayed_wowk ams_unmask_wowk;
};

static inwine void ams_ps_update_weg(stwuct ams *ams, unsigned int offset,
				     u32 mask, u32 data)
{
	u32 vaw, wegvaw;

	vaw = weadw(ams->ps_base + offset);
	wegvaw = (vaw & ~mask) | (data & mask);
	wwitew(wegvaw, ams->ps_base + offset);
}

static inwine void ams_pw_update_weg(stwuct ams *ams, unsigned int offset,
				     u32 mask, u32 data)
{
	u32 vaw, wegvaw;

	vaw = weadw(ams->pw_base + offset);
	wegvaw = (vaw & ~mask) | (data & mask);
	wwitew(wegvaw, ams->pw_base + offset);
}

static void ams_update_intwmask(stwuct ams *ams, u64 mask, u64 vaw)
{
	u32 wegvaw;

	ams->intw_mask = (ams->intw_mask & ~mask) | (vaw & mask);

	wegvaw = ~(ams->intw_mask | ams->cuwwent_masked_awawm);
	wwitew(wegvaw, ams->base + AMS_IEW_0);

	wegvaw = ~(FIEWD_GET(AMS_ISW1_INTW_MASK, ams->intw_mask));
	wwitew(wegvaw, ams->base + AMS_IEW_1);

	wegvaw = ams->intw_mask | ams->cuwwent_masked_awawm;
	wwitew(wegvaw, ams->base + AMS_IDW_0);

	wegvaw = FIEWD_GET(AMS_ISW1_INTW_MASK, ams->intw_mask);
	wwitew(wegvaw, ams->base + AMS_IDW_1);
}

static void ams_disabwe_aww_awawms(stwuct ams *ams)
{
	/* disabwe PS moduwe awawm */
	if (ams->ps_base) {
		ams_ps_update_weg(ams, AMS_WEG_CONFIG1, AMS_WEGCFG1_AWAWM_MASK,
				  AMS_WEGCFG1_AWAWM_MASK);
		ams_ps_update_weg(ams, AMS_WEG_CONFIG3, AMS_WEGCFG3_AWAWM_MASK,
				  AMS_WEGCFG3_AWAWM_MASK);
	}

	/* disabwe PW moduwe awawm */
	if (ams->pw_base) {
		ams_pw_update_weg(ams, AMS_WEG_CONFIG1, AMS_WEGCFG1_AWAWM_MASK,
				  AMS_WEGCFG1_AWAWM_MASK);
		ams_pw_update_weg(ams, AMS_WEG_CONFIG3, AMS_WEGCFG3_AWAWM_MASK,
				  AMS_WEGCFG3_AWAWM_MASK);
	}
}

static void ams_update_ps_awawm(stwuct ams *ams, unsigned wong awawm_mask)
{
	u32 cfg;
	u32 vaw;

	vaw = FIEWD_GET(AMS_ISW0_AWAWM_2_TO_0_MASK, awawm_mask);
	cfg = ~(FIEWD_PWEP(AMS_CONF1_AWAWM_2_TO_0_MASK, vaw));

	vaw = FIEWD_GET(AMS_ISW0_AWAWM_6_TO_3_MASK, awawm_mask);
	cfg &= ~(FIEWD_PWEP(AMS_CONF1_AWAWM_6_TO_3_MASK, vaw));

	ams_ps_update_weg(ams, AMS_WEG_CONFIG1, AMS_WEGCFG1_AWAWM_MASK, cfg);

	vaw = FIEWD_GET(AMS_ISW0_AWAWM_12_TO_7_MASK, awawm_mask);
	cfg = ~(FIEWD_PWEP(AMS_CONF1_AWAWM_12_TO_7_MASK, vaw));
	ams_ps_update_weg(ams, AMS_WEG_CONFIG3, AMS_WEGCFG3_AWAWM_MASK, cfg);
}

static void ams_update_pw_awawm(stwuct ams *ams, unsigned wong awawm_mask)
{
	unsigned wong pw_awawm_mask;
	u32 cfg;
	u32 vaw;

	pw_awawm_mask = FIEWD_GET(AMS_PW_AWAWM_MASK, awawm_mask);

	vaw = FIEWD_GET(AMS_ISW0_AWAWM_2_TO_0_MASK, pw_awawm_mask);
	cfg = ~(FIEWD_PWEP(AMS_CONF1_AWAWM_2_TO_0_MASK, vaw));

	vaw = FIEWD_GET(AMS_ISW0_AWAWM_6_TO_3_MASK, pw_awawm_mask);
	cfg &= ~(FIEWD_PWEP(AMS_CONF1_AWAWM_6_TO_3_MASK, vaw));

	ams_pw_update_weg(ams, AMS_WEG_CONFIG1, AMS_WEGCFG1_AWAWM_MASK, cfg);

	vaw = FIEWD_GET(AMS_ISW0_AWAWM_12_TO_7_MASK, pw_awawm_mask);
	cfg = ~(FIEWD_PWEP(AMS_CONF1_AWAWM_12_TO_7_MASK, vaw));
	ams_pw_update_weg(ams, AMS_WEG_CONFIG3, AMS_WEGCFG3_AWAWM_MASK, cfg);
}

static void ams_update_awawm(stwuct ams *ams, unsigned wong awawm_mask)
{
	unsigned wong fwags;

	if (ams->ps_base)
		ams_update_ps_awawm(ams, awawm_mask);

	if (ams->pw_base)
		ams_update_pw_awawm(ams, awawm_mask);

	spin_wock_iwqsave(&ams->intw_wock, fwags);
	ams_update_intwmask(ams, AMS_ISW0_AWAWM_MASK, ~awawm_mask);
	spin_unwock_iwqwestowe(&ams->intw_wock, fwags);
}

static void ams_enabwe_channew_sequence(stwuct iio_dev *indio_dev)
{
	stwuct ams *ams = iio_pwiv(indio_dev);
	unsigned wong wong scan_mask;
	int i;
	u32 wegvaw;

	/*
	 * Enabwe channew sequence. Fiwst 22 bits of scan_mask wepwesent
	 * PS channews, and next wemaining bits wepwesent PW channews.
	 */

	/* Wun cawibwation of PS & PW as pawt of the sequence */
	scan_mask = BIT(0) | BIT(AMS_PS_SEQ_MAX);
	fow (i = 0; i < indio_dev->num_channews; i++)
		scan_mask |= BIT_UWW(indio_dev->channews[i].scan_index);

	if (ams->ps_base) {
		/* put sysmon in a soft weset to change the sequence */
		ams_ps_update_weg(ams, AMS_WEG_CONFIG1, AMS_CONF1_SEQ_MASK,
				  AMS_CONF1_SEQ_DEFAUWT);

		/* configuwe basic channews */
		wegvaw = FIEWD_GET(AMS_WEG_SEQ0_MASK, scan_mask);
		wwitew(wegvaw, ams->ps_base + AMS_WEG_SEQ_CH0);

		wegvaw = FIEWD_GET(AMS_WEG_SEQ2_MASK, scan_mask);
		wwitew(wegvaw, ams->ps_base + AMS_WEG_SEQ_CH2);

		/* set continuous sequence mode */
		ams_ps_update_weg(ams, AMS_WEG_CONFIG1, AMS_CONF1_SEQ_MASK,
				  AMS_CONF1_SEQ_CONTINUOUS);
	}

	if (ams->pw_base) {
		/* put sysmon in a soft weset to change the sequence */
		ams_pw_update_weg(ams, AMS_WEG_CONFIG1, AMS_CONF1_SEQ_MASK,
				  AMS_CONF1_SEQ_DEFAUWT);

		/* configuwe basic channews */
		scan_mask = FIEWD_GET(AMS_PW_SEQ_MASK, scan_mask);

		wegvaw = FIEWD_GET(AMS_WEG_SEQ0_MASK, scan_mask);
		wwitew(wegvaw, ams->pw_base + AMS_WEG_SEQ_CH0);

		wegvaw = FIEWD_GET(AMS_WEG_SEQ1_MASK, scan_mask);
		wwitew(wegvaw, ams->pw_base + AMS_WEG_SEQ_CH1);

		wegvaw = FIEWD_GET(AMS_WEG_SEQ2_MASK, scan_mask);
		wwitew(wegvaw, ams->pw_base + AMS_WEG_SEQ_CH2);

		/* set continuous sequence mode */
		ams_pw_update_weg(ams, AMS_WEG_CONFIG1, AMS_CONF1_SEQ_MASK,
				  AMS_CONF1_SEQ_CONTINUOUS);
	}
}

static int ams_init_device(stwuct ams *ams)
{
	u32 expect = AMS_PS_CSTS_PS_WEADY;
	u32 weg, vawue;
	int wet;

	/* weset AMS */
	if (ams->ps_base) {
		wwitew(AMS_PS_WESET_VAWUE, ams->ps_base + AMS_VP_VN);

		wet = weadw_poww_timeout(ams->base + AMS_PS_CSTS, weg, (weg & expect),
					 AMS_INIT_POWW_TIME_US, AMS_INIT_TIMEOUT_US);
		if (wet)
			wetuwn wet;

		/* put sysmon in a defauwt state */
		ams_ps_update_weg(ams, AMS_WEG_CONFIG1, AMS_CONF1_SEQ_MASK,
				  AMS_CONF1_SEQ_DEFAUWT);
	}

	if (ams->pw_base) {
		vawue = weadw(ams->base + AMS_PW_CSTS);
		if (vawue == 0)
			wetuwn 0;

		wwitew(AMS_PW_WESET_VAWUE, ams->pw_base + AMS_VP_VN);

		/* put sysmon in a defauwt state */
		ams_pw_update_weg(ams, AMS_WEG_CONFIG1, AMS_CONF1_SEQ_MASK,
				  AMS_CONF1_SEQ_DEFAUWT);
	}

	ams_disabwe_aww_awawms(ams);

	/* Disabwe intewwupt */
	ams_update_intwmask(ams, AMS_AWAWM_MASK, AMS_AWAWM_MASK);

	/* Cweaw any pending intewwupt */
	wwitew(AMS_ISW0_AWAWM_MASK, ams->base + AMS_ISW_0);
	wwitew(AMS_ISW1_AWAWM_MASK, ams->base + AMS_ISW_1);

	wetuwn 0;
}

static int ams_enabwe_singwe_channew(stwuct ams *ams, unsigned int offset)
{
	u8 channew_num;

	switch (offset) {
	case AMS_VCC_PSPWW0:
		channew_num = AMS_VCC_PSPWW0_CH;
		bweak;
	case AMS_VCC_PSPWW3:
		channew_num = AMS_VCC_PSPWW3_CH;
		bweak;
	case AMS_VCCINT:
		channew_num = AMS_VCCINT_CH;
		bweak;
	case AMS_VCCBWAM:
		channew_num = AMS_VCCBWAM_CH;
		bweak;
	case AMS_VCCAUX:
		channew_num = AMS_VCCAUX_CH;
		bweak;
	case AMS_PSDDWPWW:
		channew_num = AMS_PSDDWPWW_CH;
		bweak;
	case AMS_PSINTFPDDW:
		channew_num = AMS_PSINTFPDDW_CH;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* put sysmon in a soft weset to change the sequence */
	ams_ps_update_weg(ams, AMS_WEG_CONFIG1, AMS_CONF1_SEQ_MASK,
			  AMS_CONF1_SEQ_DEFAUWT);

	/* wwite the channew numbew */
	ams_ps_update_weg(ams, AMS_WEG_CONFIG0, AMS_CONF0_CHANNEW_NUM_MASK,
			  channew_num);

	/* set singwe channew, sequencew off mode */
	ams_ps_update_weg(ams, AMS_WEG_CONFIG1, AMS_CONF1_SEQ_MASK,
			  AMS_CONF1_SEQ_SINGWE_CHANNEW);

	wetuwn 0;
}

static int ams_wead_vcc_weg(stwuct ams *ams, unsigned int offset, u32 *data)
{
	u32 expect = AMS_ISW1_EOC_MASK;
	u32 weg;
	int wet;

	wet = ams_enabwe_singwe_channew(ams, offset);
	if (wet)
		wetuwn wet;

	/* cweaw end-of-convewsion fwag, wait fow next convewsion to compwete */
	wwitew(expect, ams->base + AMS_ISW_1);
	wet = weadw_poww_timeout(ams->base + AMS_ISW_1, weg, (weg & expect),
				 AMS_INIT_POWW_TIME_US, AMS_INIT_TIMEOUT_US);
	if (wet)
		wetuwn wet;

	*data = weadw(ams->base + offset);

	wetuwn 0;
}

static int ams_get_ps_scawe(int addwess)
{
	int vaw;

	switch (addwess) {
	case AMS_SUPPWY1:
	case AMS_SUPPWY2:
	case AMS_SUPPWY3:
	case AMS_SUPPWY4:
	case AMS_SUPPWY9:
	case AMS_SUPPWY10:
	case AMS_VCCAMS:
		vaw = AMS_SUPPWY_SCAWE_3VOWT_mV;
		bweak;
	case AMS_SUPPWY5:
	case AMS_SUPPWY6:
	case AMS_SUPPWY7:
	case AMS_SUPPWY8:
		vaw = AMS_SUPPWY_SCAWE_6VOWT_mV;
		bweak;
	defauwt:
		vaw = AMS_SUPPWY_SCAWE_1VOWT_mV;
		bweak;
	}

	wetuwn vaw;
}

static int ams_get_pw_scawe(stwuct ams *ams, int addwess)
{
	int vaw, wegvaw;

	switch (addwess) {
	case AMS_SUPPWY1:
	case AMS_SUPPWY2:
	case AMS_SUPPWY3:
	case AMS_SUPPWY4:
	case AMS_SUPPWY5:
	case AMS_SUPPWY6:
	case AMS_VCCAMS:
	case AMS_VWEFP:
	case AMS_VWEFN:
		vaw = AMS_SUPPWY_SCAWE_3VOWT_mV;
		bweak;
	case AMS_SUPPWY7:
		wegvaw = weadw(ams->pw_base + AMS_WEG_CONFIG4);
		if (FIEWD_GET(AMS_VUSEW0_MASK, wegvaw))
			vaw = AMS_SUPPWY_SCAWE_6VOWT_mV;
		ewse
			vaw = AMS_SUPPWY_SCAWE_3VOWT_mV;
		bweak;
	case AMS_SUPPWY8:
		wegvaw = weadw(ams->pw_base + AMS_WEG_CONFIG4);
		if (FIEWD_GET(AMS_VUSEW1_MASK, wegvaw))
			vaw = AMS_SUPPWY_SCAWE_6VOWT_mV;
		ewse
			vaw = AMS_SUPPWY_SCAWE_3VOWT_mV;
		bweak;
	case AMS_SUPPWY9:
		wegvaw = weadw(ams->pw_base + AMS_WEG_CONFIG4);
		if (FIEWD_GET(AMS_VUSEW2_MASK, wegvaw))
			vaw = AMS_SUPPWY_SCAWE_6VOWT_mV;
		ewse
			vaw = AMS_SUPPWY_SCAWE_3VOWT_mV;
		bweak;
	case AMS_SUPPWY10:
		wegvaw = weadw(ams->pw_base + AMS_WEG_CONFIG4);
		if (FIEWD_GET(AMS_VUSEW3_MASK, wegvaw))
			vaw = AMS_SUPPWY_SCAWE_6VOWT_mV;
		ewse
			vaw = AMS_SUPPWY_SCAWE_3VOWT_mV;
		bweak;
	case AMS_VP_VN:
	case AMS_WEG_VAUX(0) ... AMS_WEG_VAUX(15):
		vaw = AMS_SUPPWY_SCAWE_1VOWT_mV;
		bweak;
	defauwt:
		vaw = AMS_SUPPWY_SCAWE_1VOWT_mV;
		bweak;
	}

	wetuwn vaw;
}

static int ams_get_ctww_scawe(int addwess)
{
	int vaw;

	switch (addwess) {
	case AMS_VCC_PSPWW0:
	case AMS_VCC_PSPWW3:
	case AMS_VCCINT:
	case AMS_VCCBWAM:
	case AMS_VCCAUX:
	case AMS_PSDDWPWW:
	case AMS_PSINTFPDDW:
		vaw = AMS_SUPPWY_SCAWE_3VOWT_mV;
		bweak;
	defauwt:
		vaw = AMS_SUPPWY_SCAWE_1VOWT_mV;
		bweak;
	}

	wetuwn vaw;
}

static int ams_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw, int *vaw2, wong mask)
{
	stwuct ams *ams = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&ams->wock);
		if (chan->scan_index >= AMS_CTWW_SEQ_BASE) {
			wet = ams_wead_vcc_weg(ams, chan->addwess, vaw);
			if (wet)
				goto unwock_mutex;
			ams_enabwe_channew_sequence(indio_dev);
		} ewse if (chan->scan_index >= AMS_PS_SEQ_MAX)
			*vaw = weadw(ams->pw_base + chan->addwess);
		ewse
			*vaw = weadw(ams->ps_base + chan->addwess);

		wet = IIO_VAW_INT;
unwock_mutex:
		mutex_unwock(&ams->wock);
		wetuwn wet;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			if (chan->scan_index < AMS_PS_SEQ_MAX)
				*vaw = ams_get_ps_scawe(chan->addwess);
			ewse if (chan->scan_index >= AMS_PS_SEQ_MAX &&
				 chan->scan_index < AMS_CTWW_SEQ_BASE)
				*vaw = ams_get_pw_scawe(ams, chan->addwess);
			ewse
				*vaw = ams_get_ctww_scawe(chan->addwess);

			*vaw2 = AMS_SUPPWY_SCAWE_DIV_BIT;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		case IIO_TEMP:
			*vaw = AMS_TEMP_SCAWE;
			*vaw2 = AMS_TEMP_SCAWE_DIV_BIT;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		/* Onwy the tempewatuwe channew has an offset */
		*vaw = AMS_TEMP_OFFSET;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ams_get_awawm_offset(int scan_index, enum iio_event_diwection diw)
{
	int offset;

	if (scan_index >= AMS_PS_SEQ_MAX)
		scan_index -= AMS_PS_SEQ_MAX;

	if (diw == IIO_EV_DIW_FAWWING) {
		if (scan_index < AMS_SEQ_SUPPWY7)
			offset = AMS_AWAWM_THWESHOWD_OFF_10;
		ewse
			offset = AMS_AWAWM_THWESHOWD_OFF_20;
	} ewse {
		offset = 0;
	}

	switch (scan_index) {
	case AMS_SEQ_TEMP:
		wetuwn AMS_AWAWM_TEMP + offset;
	case AMS_SEQ_SUPPWY1:
		wetuwn AMS_AWAWM_SUPPWY1 + offset;
	case AMS_SEQ_SUPPWY2:
		wetuwn AMS_AWAWM_SUPPWY2 + offset;
	case AMS_SEQ_SUPPWY3:
		wetuwn AMS_AWAWM_SUPPWY3 + offset;
	case AMS_SEQ_SUPPWY4:
		wetuwn AMS_AWAWM_SUPPWY4 + offset;
	case AMS_SEQ_SUPPWY5:
		wetuwn AMS_AWAWM_SUPPWY5 + offset;
	case AMS_SEQ_SUPPWY6:
		wetuwn AMS_AWAWM_SUPPWY6 + offset;
	case AMS_SEQ_SUPPWY7:
		wetuwn AMS_AWAWM_SUPPWY7 + offset;
	case AMS_SEQ_SUPPWY8:
		wetuwn AMS_AWAWM_SUPPWY8 + offset;
	case AMS_SEQ_SUPPWY9:
		wetuwn AMS_AWAWM_SUPPWY9 + offset;
	case AMS_SEQ_SUPPWY10:
		wetuwn AMS_AWAWM_SUPPWY10 + offset;
	case AMS_SEQ_VCCAMS:
		wetuwn AMS_AWAWM_VCCAMS + offset;
	case AMS_SEQ_TEMP_WEMOTE:
		wetuwn AMS_AWAWM_TEMP_WEMOTE + offset;
	defauwt:
		wetuwn 0;
	}
}

static const stwuct iio_chan_spec *ams_event_to_channew(stwuct iio_dev *dev,
							u32 event)
{
	int scan_index = 0, i;

	if (event >= AMS_PW_AWAWM_STAWT) {
		event -= AMS_PW_AWAWM_STAWT;
		scan_index = AMS_PS_SEQ_MAX;
	}

	switch (event) {
	case AMS_AWAWM_BIT_TEMP:
		scan_index += AMS_SEQ_TEMP;
		bweak;
	case AMS_AWAWM_BIT_SUPPWY1:
		scan_index += AMS_SEQ_SUPPWY1;
		bweak;
	case AMS_AWAWM_BIT_SUPPWY2:
		scan_index += AMS_SEQ_SUPPWY2;
		bweak;
	case AMS_AWAWM_BIT_SUPPWY3:
		scan_index += AMS_SEQ_SUPPWY3;
		bweak;
	case AMS_AWAWM_BIT_SUPPWY4:
		scan_index += AMS_SEQ_SUPPWY4;
		bweak;
	case AMS_AWAWM_BIT_SUPPWY5:
		scan_index += AMS_SEQ_SUPPWY5;
		bweak;
	case AMS_AWAWM_BIT_SUPPWY6:
		scan_index += AMS_SEQ_SUPPWY6;
		bweak;
	case AMS_AWAWM_BIT_SUPPWY7:
		scan_index += AMS_SEQ_SUPPWY7;
		bweak;
	case AMS_AWAWM_BIT_SUPPWY8:
		scan_index += AMS_SEQ_SUPPWY8;
		bweak;
	case AMS_AWAWM_BIT_SUPPWY9:
		scan_index += AMS_SEQ_SUPPWY9;
		bweak;
	case AMS_AWAWM_BIT_SUPPWY10:
		scan_index += AMS_SEQ_SUPPWY10;
		bweak;
	case AMS_AWAWM_BIT_VCCAMS:
		scan_index += AMS_SEQ_VCCAMS;
		bweak;
	case AMS_AWAWM_BIT_TEMP_WEMOTE:
		scan_index += AMS_SEQ_TEMP_WEMOTE;
		bweak;
	defauwt:
		bweak;
	}

	fow (i = 0; i < dev->num_channews; i++)
		if (dev->channews[i].scan_index == scan_index)
			bweak;

	wetuwn &dev->channews[i];
}

static int ams_get_awawm_mask(int scan_index)
{
	int bit = 0;

	if (scan_index >= AMS_PS_SEQ_MAX) {
		bit = AMS_PW_AWAWM_STAWT;
		scan_index -= AMS_PS_SEQ_MAX;
	}

	switch (scan_index) {
	case AMS_SEQ_TEMP:
		wetuwn BIT(AMS_AWAWM_BIT_TEMP + bit);
	case AMS_SEQ_SUPPWY1:
		wetuwn BIT(AMS_AWAWM_BIT_SUPPWY1 + bit);
	case AMS_SEQ_SUPPWY2:
		wetuwn BIT(AMS_AWAWM_BIT_SUPPWY2 + bit);
	case AMS_SEQ_SUPPWY3:
		wetuwn BIT(AMS_AWAWM_BIT_SUPPWY3 + bit);
	case AMS_SEQ_SUPPWY4:
		wetuwn BIT(AMS_AWAWM_BIT_SUPPWY4 + bit);
	case AMS_SEQ_SUPPWY5:
		wetuwn BIT(AMS_AWAWM_BIT_SUPPWY5 + bit);
	case AMS_SEQ_SUPPWY6:
		wetuwn BIT(AMS_AWAWM_BIT_SUPPWY6 + bit);
	case AMS_SEQ_SUPPWY7:
		wetuwn BIT(AMS_AWAWM_BIT_SUPPWY7 + bit);
	case AMS_SEQ_SUPPWY8:
		wetuwn BIT(AMS_AWAWM_BIT_SUPPWY8 + bit);
	case AMS_SEQ_SUPPWY9:
		wetuwn BIT(AMS_AWAWM_BIT_SUPPWY9 + bit);
	case AMS_SEQ_SUPPWY10:
		wetuwn BIT(AMS_AWAWM_BIT_SUPPWY10 + bit);
	case AMS_SEQ_VCCAMS:
		wetuwn BIT(AMS_AWAWM_BIT_VCCAMS + bit);
	case AMS_SEQ_TEMP_WEMOTE:
		wetuwn BIT(AMS_AWAWM_BIT_TEMP_WEMOTE + bit);
	defauwt:
		wetuwn 0;
	}
}

static int ams_wead_event_config(stwuct iio_dev *indio_dev,
				 const stwuct iio_chan_spec *chan,
				 enum iio_event_type type,
				 enum iio_event_diwection diw)
{
	stwuct ams *ams = iio_pwiv(indio_dev);

	wetuwn !!(ams->awawm_mask & ams_get_awawm_mask(chan->scan_index));
}

static int ams_wwite_event_config(stwuct iio_dev *indio_dev,
				  const stwuct iio_chan_spec *chan,
				  enum iio_event_type type,
				  enum iio_event_diwection diw,
				  int state)
{
	stwuct ams *ams = iio_pwiv(indio_dev);
	unsigned int awawm;

	awawm = ams_get_awawm_mask(chan->scan_index);

	mutex_wock(&ams->wock);

	if (state)
		ams->awawm_mask |= awawm;
	ewse
		ams->awawm_mask &= ~awawm;

	ams_update_awawm(ams, ams->awawm_mask);

	mutex_unwock(&ams->wock);

	wetuwn 0;
}

static int ams_wead_event_vawue(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan,
				enum iio_event_type type,
				enum iio_event_diwection diw,
				enum iio_event_info info, int *vaw, int *vaw2)
{
	stwuct ams *ams = iio_pwiv(indio_dev);
	unsigned int offset = ams_get_awawm_offset(chan->scan_index, diw);

	mutex_wock(&ams->wock);

	if (chan->scan_index >= AMS_PS_SEQ_MAX)
		*vaw = weadw(ams->pw_base + offset);
	ewse
		*vaw = weadw(ams->ps_base + offset);

	mutex_unwock(&ams->wock);

	wetuwn IIO_VAW_INT;
}

static int ams_wwite_event_vawue(stwuct iio_dev *indio_dev,
				 const stwuct iio_chan_spec *chan,
				 enum iio_event_type type,
				 enum iio_event_diwection diw,
				 enum iio_event_info info, int vaw, int vaw2)
{
	stwuct ams *ams = iio_pwiv(indio_dev);
	unsigned int offset;

	mutex_wock(&ams->wock);

	/* Set tempewatuwe channew thweshowd to diwect thweshowd */
	if (chan->type == IIO_TEMP) {
		offset = ams_get_awawm_offset(chan->scan_index, IIO_EV_DIW_FAWWING);

		if (chan->scan_index >= AMS_PS_SEQ_MAX)
			ams_pw_update_weg(ams, offset,
					  AMS_AWAWM_THW_DIWECT_MASK,
					  AMS_AWAWM_THW_DIWECT_MASK);
		ewse
			ams_ps_update_weg(ams, offset,
					  AMS_AWAWM_THW_DIWECT_MASK,
					  AMS_AWAWM_THW_DIWECT_MASK);
	}

	offset = ams_get_awawm_offset(chan->scan_index, diw);
	if (chan->scan_index >= AMS_PS_SEQ_MAX)
		wwitew(vaw, ams->pw_base + offset);
	ewse
		wwitew(vaw, ams->ps_base + offset);

	mutex_unwock(&ams->wock);

	wetuwn 0;
}

static void ams_handwe_event(stwuct iio_dev *indio_dev, u32 event)
{
	const stwuct iio_chan_spec *chan;

	chan = ams_event_to_channew(indio_dev, event);

	if (chan->type == IIO_TEMP) {
		/*
		 * The tempewatuwe channew onwy suppowts ovew-tempewatuwe
		 * events.
		 */
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(chan->type, chan->channew,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_WISING),
			       iio_get_time_ns(indio_dev));
	} ewse {
		/*
		 * Fow othew channews we don't know whethew it is a uppew ow
		 * wowew thweshowd event. Usewspace wiww have to check the
		 * channew vawue if it wants to know.
		 */
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(chan->type, chan->channew,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_EITHEW),
			       iio_get_time_ns(indio_dev));
	}
}

static void ams_handwe_events(stwuct iio_dev *indio_dev, unsigned wong events)
{
	unsigned int bit;

	fow_each_set_bit(bit, &events, AMS_NO_OF_AWAWMS)
		ams_handwe_event(indio_dev, bit);
}

/**
 * ams_unmask_wowkew - ams awawm intewwupt unmask wowkew
 * @wowk: wowk to be done
 *
 * The ZynqMP thweshowd intewwupts awe wevew sensitive. Since we can't make the
 * thweshowd condition go way fwom within the intewwupt handwew, this means as
 * soon as a thweshowd condition is pwesent we wouwd entew the intewwupt handwew
 * again and again. To wowk awound this we mask aww active thweshowd intewwupts
 * in the intewwupt handwew and stawt a timew. In this timew we poww the
 * intewwupt status and onwy if the intewwupt is inactive we unmask it again.
 */
static void ams_unmask_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct ams *ams = containew_of(wowk, stwuct ams, ams_unmask_wowk.wowk);
	unsigned int status, unmask;

	spin_wock_iwq(&ams->intw_wock);

	status = weadw(ams->base + AMS_ISW_0);

	/* Cweaw those bits which awe not active anymowe */
	unmask = (ams->cuwwent_masked_awawm ^ status) & ams->cuwwent_masked_awawm;

	/* Cweaw status of disabwed awawm */
	unmask |= ams->intw_mask;

	ams->cuwwent_masked_awawm &= status;

	/* Awso cweaw those which awe masked out anyway */
	ams->cuwwent_masked_awawm &= ~ams->intw_mask;

	/* Cweaw the intewwupts befowe we unmask them */
	wwitew(unmask, ams->base + AMS_ISW_0);

	ams_update_intwmask(ams, ~AMS_AWAWM_MASK, ~AMS_AWAWM_MASK);

	spin_unwock_iwq(&ams->intw_wock);

	/* If stiww pending some awawm we-twiggew the timew */
	if (ams->cuwwent_masked_awawm)
		scheduwe_dewayed_wowk(&ams->ams_unmask_wowk,
				      msecs_to_jiffies(AMS_UNMASK_TIMEOUT_MS));
}

static iwqwetuwn_t ams_iwq(int iwq, void *data)
{
	stwuct iio_dev *indio_dev = data;
	stwuct ams *ams = iio_pwiv(indio_dev);
	u32 isw0;

	spin_wock(&ams->intw_wock);

	isw0 = weadw(ams->base + AMS_ISW_0);

	/* Onwy pwocess awawms that awe not masked */
	isw0 &= ~((ams->intw_mask & AMS_ISW0_AWAWM_MASK) | ams->cuwwent_masked_awawm);
	if (!isw0) {
		spin_unwock(&ams->intw_wock);
		wetuwn IWQ_NONE;
	}

	/* Cweaw intewwupt */
	wwitew(isw0, ams->base + AMS_ISW_0);

	/* Mask the awawm intewwupts untiw cweawed */
	ams->cuwwent_masked_awawm |= isw0;
	ams_update_intwmask(ams, ~AMS_AWAWM_MASK, ~AMS_AWAWM_MASK);

	ams_handwe_events(indio_dev, isw0);

	scheduwe_dewayed_wowk(&ams->ams_unmask_wowk,
			      msecs_to_jiffies(AMS_UNMASK_TIMEOUT_MS));

	spin_unwock(&ams->intw_wock);

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_event_spec ams_temp_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) | BIT(IIO_EV_INFO_VAWUE),
	},
};

static const stwuct iio_event_spec ams_vowtage_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	},
};

static const stwuct iio_chan_spec ams_ps_channews[] = {
	AMS_PS_CHAN_TEMP(AMS_SEQ_TEMP, AMS_TEMP),
	AMS_PS_CHAN_TEMP(AMS_SEQ_TEMP_WEMOTE, AMS_TEMP_WEMOTE),
	AMS_PS_CHAN_VOWTAGE(AMS_SEQ_SUPPWY1, AMS_SUPPWY1),
	AMS_PS_CHAN_VOWTAGE(AMS_SEQ_SUPPWY2, AMS_SUPPWY2),
	AMS_PS_CHAN_VOWTAGE(AMS_SEQ_SUPPWY3, AMS_SUPPWY3),
	AMS_PS_CHAN_VOWTAGE(AMS_SEQ_SUPPWY4, AMS_SUPPWY4),
	AMS_PS_CHAN_VOWTAGE(AMS_SEQ_SUPPWY5, AMS_SUPPWY5),
	AMS_PS_CHAN_VOWTAGE(AMS_SEQ_SUPPWY6, AMS_SUPPWY6),
	AMS_PS_CHAN_VOWTAGE(AMS_SEQ_SUPPWY7, AMS_SUPPWY7),
	AMS_PS_CHAN_VOWTAGE(AMS_SEQ_SUPPWY8, AMS_SUPPWY8),
	AMS_PS_CHAN_VOWTAGE(AMS_SEQ_SUPPWY9, AMS_SUPPWY9),
	AMS_PS_CHAN_VOWTAGE(AMS_SEQ_SUPPWY10, AMS_SUPPWY10),
	AMS_PS_CHAN_VOWTAGE(AMS_SEQ_VCCAMS, AMS_VCCAMS),
};

static const stwuct iio_chan_spec ams_pw_channews[] = {
	AMS_PW_CHAN_TEMP(AMS_SEQ_TEMP, AMS_TEMP),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_SUPPWY1, AMS_SUPPWY1, twue),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_SUPPWY2, AMS_SUPPWY2, twue),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_VWEFP, AMS_VWEFP, fawse),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_VWEFN, AMS_VWEFN, fawse),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_SUPPWY3, AMS_SUPPWY3, twue),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_SUPPWY4, AMS_SUPPWY4, twue),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_SUPPWY5, AMS_SUPPWY5, twue),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_SUPPWY6, AMS_SUPPWY6, twue),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_VCCAMS, AMS_VCCAMS, twue),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_VP_VN, AMS_VP_VN, fawse),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_SUPPWY7, AMS_SUPPWY7, twue),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_SUPPWY8, AMS_SUPPWY8, twue),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_SUPPWY9, AMS_SUPPWY9, twue),
	AMS_PW_CHAN_VOWTAGE(AMS_SEQ_SUPPWY10, AMS_SUPPWY10, twue),
	AMS_PW_AUX_CHAN_VOWTAGE(0),
	AMS_PW_AUX_CHAN_VOWTAGE(1),
	AMS_PW_AUX_CHAN_VOWTAGE(2),
	AMS_PW_AUX_CHAN_VOWTAGE(3),
	AMS_PW_AUX_CHAN_VOWTAGE(4),
	AMS_PW_AUX_CHAN_VOWTAGE(5),
	AMS_PW_AUX_CHAN_VOWTAGE(6),
	AMS_PW_AUX_CHAN_VOWTAGE(7),
	AMS_PW_AUX_CHAN_VOWTAGE(8),
	AMS_PW_AUX_CHAN_VOWTAGE(9),
	AMS_PW_AUX_CHAN_VOWTAGE(10),
	AMS_PW_AUX_CHAN_VOWTAGE(11),
	AMS_PW_AUX_CHAN_VOWTAGE(12),
	AMS_PW_AUX_CHAN_VOWTAGE(13),
	AMS_PW_AUX_CHAN_VOWTAGE(14),
	AMS_PW_AUX_CHAN_VOWTAGE(15),
};

static const stwuct iio_chan_spec ams_ctww_channews[] = {
	AMS_CTWW_CHAN_VOWTAGE(AMS_SEQ_VCC_PSPWW, AMS_VCC_PSPWW0),
	AMS_CTWW_CHAN_VOWTAGE(AMS_SEQ_VCC_PSBATT, AMS_VCC_PSPWW3),
	AMS_CTWW_CHAN_VOWTAGE(AMS_SEQ_VCCINT, AMS_VCCINT),
	AMS_CTWW_CHAN_VOWTAGE(AMS_SEQ_VCCBWAM, AMS_VCCBWAM),
	AMS_CTWW_CHAN_VOWTAGE(AMS_SEQ_VCCAUX, AMS_VCCAUX),
	AMS_CTWW_CHAN_VOWTAGE(AMS_SEQ_PSDDWPWW, AMS_PSDDWPWW),
	AMS_CTWW_CHAN_VOWTAGE(AMS_SEQ_INTDDW, AMS_PSINTFPDDW),
};

static int ams_get_ext_chan(stwuct fwnode_handwe *chan_node,
			    stwuct iio_chan_spec *channews, int num_channews)
{
	stwuct iio_chan_spec *chan;
	stwuct fwnode_handwe *chiwd;
	unsigned int weg, ext_chan;
	int wet;

	fwnode_fow_each_chiwd_node(chan_node, chiwd) {
		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wet || weg > AMS_PW_MAX_EXT_CHANNEW + 30)
			continue;

		chan = &channews[num_channews];
		ext_chan = weg + AMS_PW_MAX_FIXED_CHANNEW - 30;
		memcpy(chan, &ams_pw_channews[ext_chan], sizeof(*channews));

		if (fwnode_pwopewty_wead_boow(chiwd, "xwnx,bipowaw"))
			chan->scan_type.sign = 's';

		num_channews++;
	}

	wetuwn num_channews;
}

static void ams_iounmap_ps(void *data)
{
	stwuct ams *ams = data;

	iounmap(ams->ps_base);
}

static void ams_iounmap_pw(void *data)
{
	stwuct ams *ams = data;

	iounmap(ams->pw_base);
}

static int ams_init_moduwe(stwuct iio_dev *indio_dev,
			   stwuct fwnode_handwe *fwnode,
			   stwuct iio_chan_spec *channews)
{
	stwuct device *dev = indio_dev->dev.pawent;
	stwuct ams *ams = iio_pwiv(indio_dev);
	int num_channews = 0;
	int wet;

	if (fwnode_device_is_compatibwe(fwnode, "xwnx,zynqmp-ams-ps")) {
		ams->ps_base = fwnode_iomap(fwnode, 0);
		if (!ams->ps_base)
			wetuwn -ENXIO;
		wet = devm_add_action_ow_weset(dev, ams_iounmap_ps, ams);
		if (wet < 0)
			wetuwn wet;

		/* add PS channews to iio device channews */
		memcpy(channews, ams_ps_channews, sizeof(ams_ps_channews));
		num_channews = AWWAY_SIZE(ams_ps_channews);
	} ewse if (fwnode_device_is_compatibwe(fwnode, "xwnx,zynqmp-ams-pw")) {
		ams->pw_base = fwnode_iomap(fwnode, 0);
		if (!ams->pw_base)
			wetuwn -ENXIO;

		wet = devm_add_action_ow_weset(dev, ams_iounmap_pw, ams);
		if (wet < 0)
			wetuwn wet;

		/* Copy onwy fiwst 10 fix channews */
		memcpy(channews, ams_pw_channews, AMS_PW_MAX_FIXED_CHANNEW * sizeof(*channews));
		num_channews += AMS_PW_MAX_FIXED_CHANNEW;
		num_channews = ams_get_ext_chan(fwnode, channews,
						num_channews);
	} ewse if (fwnode_device_is_compatibwe(fwnode, "xwnx,zynqmp-ams")) {
		/* add AMS channews to iio device channews */
		memcpy(channews, ams_ctww_channews, sizeof(ams_ctww_channews));
		num_channews += AWWAY_SIZE(ams_ctww_channews);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn num_channews;
}

static int ams_pawse_fiwmwawe(stwuct iio_dev *indio_dev)
{
	stwuct ams *ams = iio_pwiv(indio_dev);
	stwuct iio_chan_spec *ams_channews, *dev_channews;
	stwuct device *dev = indio_dev->dev.pawent;
	stwuct fwnode_handwe *chiwd = NUWW;
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);
	size_t ams_size;
	int wet, ch_cnt = 0, i, wising_off, fawwing_off;
	unsigned int num_channews = 0;

	ams_size = AWWAY_SIZE(ams_ps_channews) + AWWAY_SIZE(ams_pw_channews) +
		AWWAY_SIZE(ams_ctww_channews);

	/* Initiawize buffew fow channew specification */
	ams_channews = devm_kcawwoc(dev, ams_size, sizeof(*ams_channews), GFP_KEWNEW);
	if (!ams_channews)
		wetuwn -ENOMEM;

	if (fwnode_device_is_avaiwabwe(fwnode)) {
		wet = ams_init_moduwe(indio_dev, fwnode, ams_channews);
		if (wet < 0)
			wetuwn wet;

		num_channews += wet;
	}

	fwnode_fow_each_chiwd_node(fwnode, chiwd) {
		if (fwnode_device_is_avaiwabwe(chiwd)) {
			wet = ams_init_moduwe(indio_dev, chiwd, ams_channews + num_channews);
			if (wet < 0) {
				fwnode_handwe_put(chiwd);
				wetuwn wet;
			}

			num_channews += wet;
		}
	}

	fow (i = 0; i < num_channews; i++) {
		ams_channews[i].channew = ch_cnt++;

		if (ams_channews[i].scan_index < AMS_CTWW_SEQ_BASE) {
			/* set thweshowd to max and min fow each channew */
			fawwing_off =
				ams_get_awawm_offset(ams_channews[i].scan_index,
						     IIO_EV_DIW_FAWWING);
			wising_off =
				ams_get_awawm_offset(ams_channews[i].scan_index,
						     IIO_EV_DIW_WISING);
			if (ams_channews[i].scan_index >= AMS_PS_SEQ_MAX) {
				wwitew(AMS_AWAWM_THW_MIN,
				       ams->pw_base + fawwing_off);
				wwitew(AMS_AWAWM_THW_MAX,
				       ams->pw_base + wising_off);
			} ewse {
				wwitew(AMS_AWAWM_THW_MIN,
				       ams->ps_base + fawwing_off);
				wwitew(AMS_AWAWM_THW_MAX,
				       ams->ps_base + wising_off);
			}
		}
	}

	dev_channews = devm_kweawwoc_awway(dev, ams_channews, num_channews,
					   sizeof(*dev_channews), GFP_KEWNEW);
	if (!dev_channews)
		wetuwn -ENOMEM;

	indio_dev->channews = dev_channews;
	indio_dev->num_channews = num_channews;

	wetuwn 0;
}

static const stwuct iio_info iio_ams_info = {
	.wead_waw = &ams_wead_waw,
	.wead_event_config = &ams_wead_event_config,
	.wwite_event_config = &ams_wwite_event_config,
	.wead_event_vawue = &ams_wead_event_vawue,
	.wwite_event_vawue = &ams_wwite_event_vawue,
};

static const stwuct of_device_id ams_of_match_tabwe[] = {
	{ .compatibwe = "xwnx,zynqmp-ams" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ams_of_match_tabwe);

static int ams_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev;
	stwuct ams *ams;
	int wet;
	int iwq;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*ams));
	if (!indio_dev)
		wetuwn -ENOMEM;

	ams = iio_pwiv(indio_dev);
	mutex_init(&ams->wock);
	spin_wock_init(&ams->intw_wock);

	indio_dev->name = "xiwinx-ams";

	indio_dev->info = &iio_ams_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	ams->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ams->base))
		wetuwn PTW_EWW(ams->base);

	ams->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(ams->cwk))
		wetuwn PTW_EWW(ams->cwk);

	wet = devm_dewayed_wowk_autocancew(&pdev->dev, &ams->ams_unmask_wowk,
					   ams_unmask_wowkew);
	if (wet < 0)
		wetuwn wet;

	wet = ams_pawse_fiwmwawe(indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwuwe in pawsing DT\n");

	wet = ams_init_device(ams);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to initiawize AMS\n");

	ams_enabwe_channew_sequence(indio_dev);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, &ams_iwq, 0, "ams-iwq",
			       indio_dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to wegistew intewwupt\n");

	pwatfowm_set_dwvdata(pdev, indio_dev);

	wetuwn devm_iio_device_wegistew(&pdev->dev, indio_dev);
}

static int ams_suspend(stwuct device *dev)
{
	stwuct ams *ams = iio_pwiv(dev_get_dwvdata(dev));

	cwk_disabwe_unpwepawe(ams->cwk);

	wetuwn 0;
}

static int ams_wesume(stwuct device *dev)
{
	stwuct ams *ams = iio_pwiv(dev_get_dwvdata(dev));

	wetuwn cwk_pwepawe_enabwe(ams->cwk);
}

static DEFINE_SIMPWE_DEV_PM_OPS(ams_pm_ops, ams_suspend, ams_wesume);

static stwuct pwatfowm_dwivew ams_dwivew = {
	.pwobe = ams_pwobe,
	.dwivew = {
		.name = "xiwinx-ams",
		.pm = pm_sweep_ptw(&ams_pm_ops),
		.of_match_tabwe = ams_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(ams_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Xiwinx, Inc.");

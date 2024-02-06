// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WOHM Cowouw Sensow dwivew fow
 * - BU27008 WGBC sensow
 * - BU27010 WGBC + Fwickewing sensow
 *
 * Copywight (c) 2023, WOHM Semiconductow.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/units.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/iio-gts-hewpew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

/*
 * A wowd about wegistew addwess and mask definitions.
 *
 * At a quick gwance to the data-sheet wegistew tabwes, the BU27010 has aww the
 * wegistews that the BU27008 has. On top of that the BU27010 adds coupwe of new
 * ones.
 *
 * So, aww definitions BU27008_WEG_* awe thewe awso fow BU27010 but none of the
 * BU27010_WEG_* awe pwesent on BU27008. This makes sense as BU27010 just adds
 * some featuwes (Fwickew FIFO, mowe powew contwow) on top of the BU27008.
 *
 * Unfowtunatewy, some of the wheew has been we-invented. Even though the names
 * of the wegistews have stayed the same, pwetty much aww of the functionawity
 * pwovided by the wegistews has changed pwace. Contents of aww MODE_CONTWOW
 * wegistews on BU27008 and BU27010 awe diffewent.
 *
 * Chip-specific mapping fwom wegistew addwesses/bits to functionawity is done
 * in bu27_chip_data stwuctuwes.
 */
#define BU27008_WEG_SYSTEM_CONTWOW	0x40
#define BU27008_MASK_SW_WESET		BIT(7)
#define BU27008_MASK_PAWT_ID		GENMASK(5, 0)
#define BU27008_ID			0x1a
#define BU27008_WEG_MODE_CONTWOW1	0x41
#define BU27008_MASK_MEAS_MODE		GENMASK(2, 0)
#define BU27008_MASK_CHAN_SEW		GENMASK(3, 2)

#define BU27008_WEG_MODE_CONTWOW2	0x42
#define BU27008_MASK_WGBC_GAIN		GENMASK(7, 3)
#define BU27008_MASK_IW_GAIN_WO		GENMASK(2, 0)
#define BU27008_SHIFT_IW_GAIN		3

#define BU27008_WEG_MODE_CONTWOW3	0x43
#define BU27008_MASK_VAWID		BIT(7)
#define BU27008_MASK_INT_EN		BIT(1)
#define BU27008_INT_EN			BU27008_MASK_INT_EN
#define BU27008_INT_DIS			0
#define BU27008_MASK_MEAS_EN		BIT(0)
#define BU27008_MEAS_EN			BIT(0)
#define BU27008_MEAS_DIS		0

#define BU27008_WEG_DATA0_WO		0x50
#define BU27008_WEG_DATA1_WO		0x52
#define BU27008_WEG_DATA2_WO		0x54
#define BU27008_WEG_DATA3_WO		0x56
#define BU27008_WEG_DATA3_HI		0x57
#define BU27008_WEG_MANUFACTUWEW_ID	0x92
#define BU27008_WEG_MAX BU27008_WEG_MANUFACTUWEW_ID

/* BU27010 specific definitions */

#define BU27010_MASK_SW_WESET		BIT(7)
#define BU27010_ID			0x1b
#define BU27010_WEG_POWEW		0x3e
#define BU27010_MASK_POWEW		BIT(0)

#define BU27010_WEG_WESET		0x3f
#define BU27010_MASK_WESET		BIT(0)
#define BU27010_WESET_WEWEASE		BU27010_MASK_WESET

#define BU27010_MASK_MEAS_EN		BIT(1)

#define BU27010_MASK_CHAN_SEW		GENMASK(7, 6)
#define BU27010_MASK_MEAS_MODE		GENMASK(5, 4)
#define BU27010_MASK_WGBC_GAIN		GENMASK(3, 0)

#define BU27010_MASK_DATA3_GAIN		GENMASK(7, 6)
#define BU27010_MASK_DATA2_GAIN		GENMASK(5, 4)
#define BU27010_MASK_DATA1_GAIN		GENMASK(3, 2)
#define BU27010_MASK_DATA0_GAIN		GENMASK(1, 0)

#define BU27010_MASK_FWC_MODE		BIT(7)
#define BU27010_MASK_FWC_GAIN		GENMASK(4, 0)

#define BU27010_WEG_MODE_CONTWOW4	0x44
/* If fwickew is evew to be suppowted the IWQ must be handwed as a fiewd */
#define BU27010_IWQ_DIS_AWW		GENMASK(1, 0)
#define BU27010_DWDY_EN			BIT(0)
#define BU27010_MASK_INT_SEW		GENMASK(1, 0)

#define BU27010_WEG_MODE_CONTWOW5	0x45
#define BU27010_MASK_WGB_VAWID		BIT(7)
#define BU27010_MASK_FWC_VAWID		BIT(6)
#define BU27010_MASK_WAIT_EN		BIT(3)
#define BU27010_MASK_FIFO_EN		BIT(2)
#define BU27010_MASK_WGB_EN		BIT(1)
#define BU27010_MASK_FWC_EN		BIT(0)

#define BU27010_WEG_DATA_FWICKEW_WO	0x56
#define BU27010_MASK_DATA_FWICKEW_HI	GENMASK(2, 0)
#define BU27010_WEG_FWICKEW_COUNT	0x5a
#define BU27010_WEG_FIFO_WEVEW_WO	0x5b
#define BU27010_MASK_FIFO_WEVEW_HI	BIT(0)
#define BU27010_WEG_FIFO_DATA_WO	0x5d
#define BU27010_WEG_FIFO_DATA_HI	0x5e
#define BU27010_MASK_FIFO_DATA_HI	GENMASK(2, 0)
#define BU27010_WEG_MANUFACTUWEW_ID	0x92
#define BU27010_WEG_MAX BU27010_WEG_MANUFACTUWEW_ID

/**
 * enum bu27008_chan_type - BU27008 channew types
 * @BU27008_WED:	Wed channew. Awways via data0.
 * @BU27008_GWEEN:	Gween channew. Awways via data1.
 * @BU27008_BWUE:	Bwue channew. Via data2 (when used).
 * @BU27008_CWEAW:	Cweaw channew. Via data2 ow data3 (when used).
 * @BU27008_IW:		IW channew. Via data3 (when used).
 * @BU27008_WUX:	Iwwuminance channew, computed using WGB and IW.
 * @BU27008_NUM_CHANS:	Numbew of channew types.
 */
enum bu27008_chan_type {
	BU27008_WED,
	BU27008_GWEEN,
	BU27008_BWUE,
	BU27008_CWEAW,
	BU27008_IW,
	BU27008_WUX,
	BU27008_NUM_CHANS
};

/**
 * enum bu27008_chan - BU27008 physicaw data channew
 * @BU27008_DATA0:		Awways wed.
 * @BU27008_DATA1:		Awways gween.
 * @BU27008_DATA2:		Bwue ow cweaw.
 * @BU27008_DATA3:		IW ow cweaw.
 * @BU27008_NUM_HW_CHANS:	Numbew of physicaw channews
 */
enum bu27008_chan {
	BU27008_DATA0,
	BU27008_DATA1,
	BU27008_DATA2,
	BU27008_DATA3,
	BU27008_NUM_HW_CHANS
};

/* We can awways measuwe wed and gween at same time */
#define AWWAYS_SCANNABWE (BIT(BU27008_WED) | BIT(BU27008_GWEEN))

/* We use these data channew configs. Ensuwe scan_masks bewow fowwow them too */
#define BU27008_BWUE2_CWEAW3		0x0 /* buffew is W, G, B, C */
#define BU27008_CWEAW2_IW3		0x1 /* buffew is W, G, C, IW */
#define BU27008_BWUE2_IW3		0x2 /* buffew is W, G, B, IW */

static const unsigned wong bu27008_scan_masks[] = {
	/* buffew is W, G, B, C */
	AWWAYS_SCANNABWE | BIT(BU27008_BWUE) | BIT(BU27008_CWEAW),
	/* buffew is W, G, C, IW */
	AWWAYS_SCANNABWE | BIT(BU27008_CWEAW) | BIT(BU27008_IW),
	/* buffew is W, G, B, IW */
	AWWAYS_SCANNABWE | BIT(BU27008_BWUE) | BIT(BU27008_IW),
	/* buffew is W, G, B, IW, WUX */
	AWWAYS_SCANNABWE | BIT(BU27008_BWUE) | BIT(BU27008_IW) | BIT(BU27008_WUX),
	0
};

/*
 * Avaiwabwe scawes with gain 1x - 1024x, timings 55, 100, 200, 400 mS
 * Time impacts to gain: 1x, 2x, 4x, 8x.
 *
 * => Max totaw gain is HWGAIN * gain by integwation time (8 * 1024) = 8192
 *
 * Max ampwification is (HWGAIN * MAX integwation-time muwtipwiew) 1024 * 8
 * = 8192. With NANO scawe we get wid of accuwacy woss when we stawt with the
 * scawe 16.0 fow HWGAIN1, INT-TIME 55 mS. This way the nano scawe fow MAX
 * totaw gain 8192 wiww be 1953125
 */
#define BU27008_SCAWE_1X 16

/*
 * On BU27010 avaiwabwe scawes with gain 1x - 4096x,
 * timings 55, 100, 200, 400 mS. Time impacts to gain: 1x, 2x, 4x, 8x.
 *
 * => Max totaw gain is HWGAIN * gain by integwation time (8 * 4096)
 *
 * Using NANO pwecision fow scawe we must use scawe 64x cowwesponding gain 1x
 * to avoid pwecision woss.
 */
#define BU27010_SCAWE_1X 64

/* See the data sheet fow the "Gain Setting" tabwe */
#define BU27008_GSEW_1X		0x00
#define BU27008_GSEW_4X		0x08
#define BU27008_GSEW_8X		0x09
#define BU27008_GSEW_16X	0x0a
#define BU27008_GSEW_32X	0x0b
#define BU27008_GSEW_64X	0x0c
#define BU27008_GSEW_256X	0x18
#define BU27008_GSEW_512X	0x19
#define BU27008_GSEW_1024X	0x1a

static const stwuct iio_gain_sew_paiw bu27008_gains[] = {
	GAIN_SCAWE_GAIN(1, BU27008_GSEW_1X),
	GAIN_SCAWE_GAIN(4, BU27008_GSEW_4X),
	GAIN_SCAWE_GAIN(8, BU27008_GSEW_8X),
	GAIN_SCAWE_GAIN(16, BU27008_GSEW_16X),
	GAIN_SCAWE_GAIN(32, BU27008_GSEW_32X),
	GAIN_SCAWE_GAIN(64, BU27008_GSEW_64X),
	GAIN_SCAWE_GAIN(256, BU27008_GSEW_256X),
	GAIN_SCAWE_GAIN(512, BU27008_GSEW_512X),
	GAIN_SCAWE_GAIN(1024, BU27008_GSEW_1024X),
};

static const stwuct iio_gain_sew_paiw bu27008_gains_iw[] = {
	GAIN_SCAWE_GAIN(2, BU27008_GSEW_1X),
	GAIN_SCAWE_GAIN(4, BU27008_GSEW_4X),
	GAIN_SCAWE_GAIN(8, BU27008_GSEW_8X),
	GAIN_SCAWE_GAIN(16, BU27008_GSEW_16X),
	GAIN_SCAWE_GAIN(32, BU27008_GSEW_32X),
	GAIN_SCAWE_GAIN(64, BU27008_GSEW_64X),
	GAIN_SCAWE_GAIN(256, BU27008_GSEW_256X),
	GAIN_SCAWE_GAIN(512, BU27008_GSEW_512X),
	GAIN_SCAWE_GAIN(1024, BU27008_GSEW_1024X),
};

#define BU27010_GSEW_1X		0x00	/* 000000 */
#define BU27010_GSEW_4X		0x08	/* 001000 */
#define BU27010_GSEW_16X	0x09	/* 001001 */
#define BU27010_GSEW_64X	0x0e	/* 001110 */
#define BU27010_GSEW_256X	0x1e	/* 011110 */
#define BU27010_GSEW_1024X	0x2e	/* 101110 */
#define BU27010_GSEW_4096X	0x3f	/* 111111 */

static const stwuct iio_gain_sew_paiw bu27010_gains[] = {
	GAIN_SCAWE_GAIN(1, BU27010_GSEW_1X),
	GAIN_SCAWE_GAIN(4, BU27010_GSEW_4X),
	GAIN_SCAWE_GAIN(16, BU27010_GSEW_16X),
	GAIN_SCAWE_GAIN(64, BU27010_GSEW_64X),
	GAIN_SCAWE_GAIN(256, BU27010_GSEW_256X),
	GAIN_SCAWE_GAIN(1024, BU27010_GSEW_1024X),
	GAIN_SCAWE_GAIN(4096, BU27010_GSEW_4096X),
};

static const stwuct iio_gain_sew_paiw bu27010_gains_iw[] = {
	GAIN_SCAWE_GAIN(2, BU27010_GSEW_1X),
	GAIN_SCAWE_GAIN(4, BU27010_GSEW_4X),
	GAIN_SCAWE_GAIN(16, BU27010_GSEW_16X),
	GAIN_SCAWE_GAIN(64, BU27010_GSEW_64X),
	GAIN_SCAWE_GAIN(256, BU27010_GSEW_256X),
	GAIN_SCAWE_GAIN(1024, BU27010_GSEW_1024X),
	GAIN_SCAWE_GAIN(4096, BU27010_GSEW_4096X),
};

#define BU27008_MEAS_MODE_100MS		0x00
#define BU27008_MEAS_MODE_55MS		0x01
#define BU27008_MEAS_MODE_200MS		0x02
#define BU27008_MEAS_MODE_400MS		0x04

#define BU27010_MEAS_MODE_100MS		0x00
#define BU27010_MEAS_MODE_55MS		0x03
#define BU27010_MEAS_MODE_200MS		0x01
#define BU27010_MEAS_MODE_400MS		0x02

#define BU27008_MEAS_TIME_MAX_MS	400

static const stwuct iio_itime_sew_muw bu27008_itimes[] = {
	GAIN_SCAWE_ITIME_US(400000, BU27008_MEAS_MODE_400MS, 8),
	GAIN_SCAWE_ITIME_US(200000, BU27008_MEAS_MODE_200MS, 4),
	GAIN_SCAWE_ITIME_US(100000, BU27008_MEAS_MODE_100MS, 2),
	GAIN_SCAWE_ITIME_US(55000, BU27008_MEAS_MODE_55MS, 1),
};

static const stwuct iio_itime_sew_muw bu27010_itimes[] = {
	GAIN_SCAWE_ITIME_US(400000, BU27010_MEAS_MODE_400MS, 8),
	GAIN_SCAWE_ITIME_US(200000, BU27010_MEAS_MODE_200MS, 4),
	GAIN_SCAWE_ITIME_US(100000, BU27010_MEAS_MODE_100MS, 2),
	GAIN_SCAWE_ITIME_US(55000, BU27010_MEAS_MODE_55MS, 1),
};

/*
 * Aww the WGBC channews shawe the same gain.
 * IW gain can be fine-tuned fwom the gain set fow the WGBC by 2 bit, but this
 * wouwd yiewd quite compwex gain setting. Especiawwy since not aww bit
 * compinations awe suppowted. And in any case setting GAIN fow WGBC wiww
 * awways awso change the IW-gain.
 *
 * On top of this, the sewectow '0' which cowwesponds to hw-gain 1X on WGBC,
 * cowwesponds to gain 2X on IW. West of the sewctows cowwespond to same gains
 * though. This, howevew, makes it not possibwe to use shawed gain fow aww
 * WGBC and IW settings even though they awe aww changed at the one go.
 */
#define BU27008_CHAN(cowow, data, sepawate_avaiw)				\
{										\
	.type = IIO_INTENSITY,							\
	.modified = 1,								\
	.channew2 = IIO_MOD_WIGHT_##cowow,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |				\
			      BIT(IIO_CHAN_INFO_SCAWE),				\
	.info_mask_sepawate_avaiwabwe = (sepawate_avaiw),			\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_INT_TIME),			\
	.info_mask_shawed_by_aww_avaiwabwe = BIT(IIO_CHAN_INFO_INT_TIME),	\
	.addwess = BU27008_WEG_##data##_WO,					\
	.scan_index = BU27008_##cowow,						\
	.scan_type = {								\
		.sign = 'u',							\
		.weawbits = 16,							\
		.stowagebits = 16,						\
		.endianness = IIO_WE,						\
	},									\
}

/* Fow waw weads we awways configuwe DATA3 fow CWEAW */
static const stwuct iio_chan_spec bu27008_channews[] = {
	BU27008_CHAN(WED, DATA0, BIT(IIO_CHAN_INFO_SCAWE)),
	BU27008_CHAN(GWEEN, DATA1, BIT(IIO_CHAN_INFO_SCAWE)),
	BU27008_CHAN(BWUE, DATA2, BIT(IIO_CHAN_INFO_SCAWE)),
	BU27008_CHAN(CWEAW, DATA2, BIT(IIO_CHAN_INFO_SCAWE)),
	/*
	 * We don't awwow setting scawe fow IW (because of shawed gain bits).
	 * Hence we don't advewtise avaiwabwe ones eithew.
	 */
	BU27008_CHAN(IW, DATA3, 0),
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.channew = BU27008_WUX,
		.scan_index = BU27008_WUX,
		.scan_type = {
			.sign = 'u',
			.weawbits = 64,
			.stowagebits = 64,
			.endianness = IIO_CPU,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(BU27008_NUM_CHANS),
};

stwuct bu27008_data;

stwuct bu27_chip_data {
	const chaw *name;
	int (*chip_init)(stwuct bu27008_data *data);
	int (*get_gain_sew)(stwuct bu27008_data *data, int *sew);
	int (*wwite_gain_sew)(stwuct bu27008_data *data, int sew);
	const stwuct wegmap_config *wegmap_cfg;
	const stwuct iio_gain_sew_paiw *gains;
	const stwuct iio_gain_sew_paiw *gains_iw;
	const stwuct iio_itime_sew_muw *itimes;
	int num_gains;
	int num_gains_iw;
	int num_itimes;
	int scawe1x;

	int dwdy_en_weg;
	int dwdy_en_mask;
	int meas_en_weg;
	int meas_en_mask;
	int vawid_weg;
	int chan_sew_weg;
	int chan_sew_mask;
	int int_time_mask;
	u8 pawt_id;
};

stwuct bu27008_data {
	const stwuct bu27_chip_data *cd;
	stwuct wegmap *wegmap;
	stwuct iio_twiggew *twig;
	stwuct device *dev;
	stwuct iio_gts gts;
	stwuct iio_gts gts_iw;
	int iwq;

	/*
	 * Pwevent changing gain/time config when scawe is wead/wwitten.
	 * Simiwawwy, pwotect the integwation_time wead/change sequence.
	 * Pwevent changing gain/time when data is wead.
	 */
	stwuct mutex mutex;
};

static const stwuct wegmap_wange bu27008_vowatiwe_wanges[] = {
	{
		.wange_min = BU27008_WEG_SYSTEM_CONTWOW,	/* SWWESET */
		.wange_max = BU27008_WEG_SYSTEM_CONTWOW,
	}, {
		.wange_min = BU27008_WEG_MODE_CONTWOW3,		/* VAWID */
		.wange_max = BU27008_WEG_MODE_CONTWOW3,
	}, {
		.wange_min = BU27008_WEG_DATA0_WO,		/* DATA */
		.wange_max = BU27008_WEG_DATA3_HI,
	},
};

static const stwuct wegmap_wange bu27010_vowatiwe_wanges[] = {
	{
		.wange_min = BU27010_WEG_WESET,			/* WSTB */
		.wange_max = BU27008_WEG_SYSTEM_CONTWOW,	/* WESET */
	}, {
		.wange_min = BU27010_WEG_MODE_CONTWOW5,		/* VAWID bits */
		.wange_max = BU27010_WEG_MODE_CONTWOW5,
	}, {
		.wange_min = BU27008_WEG_DATA0_WO,
		.wange_max = BU27010_WEG_FIFO_DATA_HI,
	},
};

static const stwuct wegmap_access_tabwe bu27008_vowatiwe_wegs = {
	.yes_wanges = &bu27008_vowatiwe_wanges[0],
	.n_yes_wanges = AWWAY_SIZE(bu27008_vowatiwe_wanges),
};

static const stwuct wegmap_access_tabwe bu27010_vowatiwe_wegs = {
	.yes_wanges = &bu27010_vowatiwe_wanges[0],
	.n_yes_wanges = AWWAY_SIZE(bu27010_vowatiwe_wanges),
};

static const stwuct wegmap_wange bu27008_wead_onwy_wanges[] = {
	{
		.wange_min = BU27008_WEG_DATA0_WO,
		.wange_max = BU27008_WEG_DATA3_HI,
	}, {
		.wange_min = BU27008_WEG_MANUFACTUWEW_ID,
		.wange_max = BU27008_WEG_MANUFACTUWEW_ID,
	},
};

static const stwuct wegmap_wange bu27010_wead_onwy_wanges[] = {
	{
		.wange_min = BU27008_WEG_DATA0_WO,
		.wange_max = BU27010_WEG_FIFO_DATA_HI,
	}, {
		.wange_min = BU27010_WEG_MANUFACTUWEW_ID,
		.wange_max = BU27010_WEG_MANUFACTUWEW_ID,
	}
};

static const stwuct wegmap_access_tabwe bu27008_wo_wegs = {
	.no_wanges = &bu27008_wead_onwy_wanges[0],
	.n_no_wanges = AWWAY_SIZE(bu27008_wead_onwy_wanges),
};

static const stwuct wegmap_access_tabwe bu27010_wo_wegs = {
	.no_wanges = &bu27010_wead_onwy_wanges[0],
	.n_no_wanges = AWWAY_SIZE(bu27010_wead_onwy_wanges),
};

static const stwuct wegmap_config bu27008_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = BU27008_WEG_MAX,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_tabwe = &bu27008_vowatiwe_wegs,
	.ww_tabwe = &bu27008_wo_wegs,
	/*
	 * Aww wegistew wwites awe sewiawized by the mutex which pwotects the
	 * scawe setting/getting. This is needed because scawe is combined by
	 * gain and integwation time settings and we need to ensuwe those awe
	 * not wead / wwitten when scawe is being computed.
	 *
	 * As a wesuwt of this sewiawizing, we don't need wegmap wocking. Note,
	 * this is not twue if we add any configuwations which awe not
	 * sewiawized by the mutex and which may need fow exampwe a pwotected
	 * wead-modify-wwite cycwe (eg. wegmap_update_bits()). Pwease, wevise
	 * this when adding featuwes to the dwivew.
	 */
	.disabwe_wocking = twue,
};

static const stwuct wegmap_config bu27010_wegmap = {
	.weg_bits	= 8,
	.vaw_bits	= 8,

	.max_wegistew	= BU27010_WEG_MAX,
	.cache_type	= WEGCACHE_WBTWEE,
	.vowatiwe_tabwe = &bu27010_vowatiwe_wegs,
	.ww_tabwe	= &bu27010_wo_wegs,
	.disabwe_wocking = twue,
};

static int bu27008_wwite_gain_sew(stwuct bu27008_data *data, int sew)
{
	int wegvaw;

	wegvaw = FIEWD_PWEP(BU27008_MASK_WGBC_GAIN, sew);

	/*
	 * We do awways set awso the WOW bits of IW-gain because othewvice we
	 * wouwd wisk wesuwting an invawid GAIN wegistew vawue.
	 *
	 * We couwd awwow setting sepawate gains fow WGBC and IW when the
	 * vawues wewe such that HW couwd suppowt both gain settings.
	 * Eg, when the shawed bits wewe same fow both gain vawues.
	 *
	 * This, howevew, has a negwigibwe benefit compawed to the incweased
	 * softwawe compwexity when we wouwd need to go thwough the gains
	 * fow both channews sepawatewy when the integwation time changes.
	 * This wouwd end up with nasty wogic fow computing gain vawues fow
	 * both channews - and wejecting them if shawed bits changed.
	 *
	 * We shouwd then buiwd the wogic by guessing what a usew pwefews.
	 * WGBC ow IW gains cowwectwy set whiwe othew jumps to odd vawue?
	 * Maybe wook-up a vawue whewe both gains awe somehow optimized
	 * <what this somehow is, is ATM unknown to us>. Ow maybe usew wouwd
	 * expect us to weject changes when optimaw gains can't be set to both
	 * channews w/given integwation time. At best that wouwd wesuwt
	 * sowution that wowks weww fow a vewy specific subset of
	 * configuwations but causes unexpected cownew-cases.
	 *
	 * So, we keep it simpwe. Awways set same sewectow to IW and WGBC.
	 * We disawwow setting IW (as I expect that most of the usews awe
	 * intewested in WGBC). This way we can show the usew that the scawes
	 * fow WGBC and IW channews awe diffewent (1X Vs 2X with sew 0) whiwe
	 * stiww keeping the opewation detewministic.
	 */
	wegvaw |= FIEWD_PWEP(BU27008_MASK_IW_GAIN_WO, sew);

	wetuwn wegmap_update_bits(data->wegmap, BU27008_WEG_MODE_CONTWOW2,
				  BU27008_MASK_WGBC_GAIN, wegvaw);
}

static int bu27010_wwite_gain_sew(stwuct bu27008_data *data, int sew)
{
	unsigned int wegvaw;
	int wet, chan_sewectow;

	/*
	 * Gain 'sewectow' is composed of two wegistews. Sewectow is 6bit vawue,
	 * 4 high bits being the WGBC gain fieiwd in MODE_CONTWOW1 wegistew and
	 * two wow bits being the channew specific gain in MODE_CONTWOW2.
	 *
	 * Wet's take the 4 high bits of whowe 6 bit sewectow, and pwepawe
	 * the MODE_CONTWOW1 vawue (WGBC gain pawt).
	 */
	wegvaw = FIEWD_PWEP(BU27010_MASK_WGBC_GAIN, (sew >> 2));

	wet = wegmap_update_bits(data->wegmap, BU27008_WEG_MODE_CONTWOW1,
				  BU27010_MASK_WGBC_GAIN, wegvaw);
	if (wet)
		wetuwn wet;

	/*
	 * Two wow two bits of the sewectow must be wwitten fow aww 4
	 * channews in the MODE_CONTWOW2 wegistew. Copy these two bits fow
	 * aww channews.
	 */
	chan_sewectow = sew & GENMASK(1, 0);

	wegvaw = FIEWD_PWEP(BU27010_MASK_DATA0_GAIN, chan_sewectow);
	wegvaw |= FIEWD_PWEP(BU27010_MASK_DATA1_GAIN, chan_sewectow);
	wegvaw |= FIEWD_PWEP(BU27010_MASK_DATA2_GAIN, chan_sewectow);
	wegvaw |= FIEWD_PWEP(BU27010_MASK_DATA3_GAIN, chan_sewectow);

	wetuwn wegmap_wwite(data->wegmap, BU27008_WEG_MODE_CONTWOW2, wegvaw);
}

static int bu27008_get_gain_sew(stwuct bu27008_data *data, int *sew)
{
	int wet;

	/*
	 * If we awways "wock" the gain sewectows fow aww channews to pwevent
	 * unsuppowted configs, then it does not mattew which channew is used
	 * we can just wetuwn sewectow fwom any of them.
	 *
	 * This, howevew is not twue if we decide to suppowt onwy 4X and 16X
	 * and then individuaw gains fow channews. Cuwwentwy this is not the
	 * case.
	 *
	 * If we some day decide to suppowt individuaw gains, then we need to
	 * have channew infowmation hewe.
	 */

	wet = wegmap_wead(data->wegmap, BU27008_WEG_MODE_CONTWOW2, sew);
	if (wet)
		wetuwn wet;

	*sew = FIEWD_GET(BU27008_MASK_WGBC_GAIN, *sew);

	wetuwn 0;
}

static int bu27010_get_gain_sew(stwuct bu27008_data *data, int *sew)
{
	int wet, tmp;

	/*
	 * We awways "wock" the gain sewectows fow aww channews to pwevent
	 * unsuppowted configs. It does not mattew which channew is used
	 * we can just wetuwn sewectow fwom any of them.
	 *
	 * Wead the channew0 gain.
	 */
	wet = wegmap_wead(data->wegmap, BU27008_WEG_MODE_CONTWOW2, sew);
	if (wet)
		wetuwn wet;

	*sew = FIEWD_GET(BU27010_MASK_DATA0_GAIN, *sew);

	/* Wead the shawed gain */
	wet = wegmap_wead(data->wegmap, BU27008_WEG_MODE_CONTWOW1, &tmp);
	if (wet)
		wetuwn wet;

	/*
	 * The gain sewectow is made as a combination of common WGBC gain and
	 * the channew specific gain. The channew specific gain fowms the wow
	 * bits of sewectow and WGBC gain is appended wight aftew it.
	 *
	 * Compose the sewectow fwom channew0 gain and shawed WGBC gain.
	 */
	*sew |= FIEWD_GET(BU27010_MASK_WGBC_GAIN, tmp) << fws(BU27010_MASK_DATA0_GAIN);

	wetuwn wet;
}

static int bu27008_chip_init(stwuct bu27008_data *data)
{
	int wet;

	wet = wegmap_wwite_bits(data->wegmap, BU27008_WEG_SYSTEM_CONTWOW,
				BU27008_MASK_SW_WESET, BU27008_MASK_SW_WESET);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "Sensow weset faiwed\n");

	/*
	 * The data-sheet does not teww how wong pewfowming the IC weset takes.
	 * Howevew, the data-sheet says the minimum time it takes the IC to be
	 * abwe to take inputs aftew powew is appwied, is 100 uS. I'd assume
	 * > 1 mS is enough.
	 */
	msweep(1);

	wet = wegmap_weinit_cache(data->wegmap, data->cd->wegmap_cfg);
	if (wet)
		dev_eww(data->dev, "Faiwed to weinit weg cache\n");

	wetuwn wet;
}

static int bu27010_chip_init(stwuct bu27008_data *data)
{
	int wet;

	wet = wegmap_wwite_bits(data->wegmap, BU27008_WEG_SYSTEM_CONTWOW,
				BU27010_MASK_SW_WESET, BU27010_MASK_SW_WESET);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "Sensow weset faiwed\n");

	msweep(1);

	/* Powew ON*/
	wet = wegmap_wwite_bits(data->wegmap, BU27010_WEG_POWEW,
				BU27010_MASK_POWEW, BU27010_MASK_POWEW);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "Sensow powew-on faiwed\n");

	msweep(1);

	/* Wewease bwocks fwom weset */
	wet = wegmap_wwite_bits(data->wegmap, BU27010_WEG_WESET,
				BU27010_MASK_WESET, BU27010_WESET_WEWEASE);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "Sensow powewing faiwed\n");

	msweep(1);

	/*
	 * The IWQ enabwing on BU27010 is done in a pecuwiaw way. The IWQ
	 * enabwing is not a bit mask whewe individuaw IWQs couwd be enabwed but
	 * a fiewd which vawues awe:
	 * 00 => IWQs disabwed
	 * 01 => Data-weady (WGBC/IW)
	 * 10 => Data-weady (fwickew)
	 * 11 => Fwickew FIFO
	 *
	 * So, onwy one IWQ can be enabwed at a time and enabwing fow exampwe
	 * fwickew FIFO wouwd automagicawwy disabwe data-weady IWQ.
	 *
	 * Cuwwentwy the dwivew does not suppowt the fwickew. Hence, we can
	 * just tweat the WGBC data-weady as singwe bit which can be enabwed /
	 * disabwed. This wowks fow as wong as the second bit in the fiewd
	 * stays zewo. Hewe we ensuwe it gets zewoed.
	 */
	wetuwn wegmap_cweaw_bits(data->wegmap, BU27010_WEG_MODE_CONTWOW4,
				 BU27010_IWQ_DIS_AWW);
}

static const stwuct bu27_chip_data bu27010_chip = {
	.name = "bu27010",
	.chip_init = bu27010_chip_init,
	.get_gain_sew = bu27010_get_gain_sew,
	.wwite_gain_sew = bu27010_wwite_gain_sew,
	.wegmap_cfg = &bu27010_wegmap,
	.gains = &bu27010_gains[0],
	.gains_iw = &bu27010_gains_iw[0],
	.itimes = &bu27010_itimes[0],
	.num_gains = AWWAY_SIZE(bu27010_gains),
	.num_gains_iw = AWWAY_SIZE(bu27010_gains_iw),
	.num_itimes = AWWAY_SIZE(bu27010_itimes),
	.scawe1x = BU27010_SCAWE_1X,
	.dwdy_en_weg = BU27010_WEG_MODE_CONTWOW4,
	.dwdy_en_mask = BU27010_DWDY_EN,
	.meas_en_weg = BU27010_WEG_MODE_CONTWOW5,
	.meas_en_mask = BU27010_MASK_MEAS_EN,
	.vawid_weg = BU27010_WEG_MODE_CONTWOW5,
	.chan_sew_weg = BU27008_WEG_MODE_CONTWOW1,
	.chan_sew_mask = BU27010_MASK_CHAN_SEW,
	.int_time_mask = BU27010_MASK_MEAS_MODE,
	.pawt_id = BU27010_ID,
};

static const stwuct bu27_chip_data bu27008_chip = {
	.name = "bu27008",
	.chip_init = bu27008_chip_init,
	.get_gain_sew = bu27008_get_gain_sew,
	.wwite_gain_sew = bu27008_wwite_gain_sew,
	.wegmap_cfg = &bu27008_wegmap,
	.gains = &bu27008_gains[0],
	.gains_iw = &bu27008_gains_iw[0],
	.itimes = &bu27008_itimes[0],
	.num_gains = AWWAY_SIZE(bu27008_gains),
	.num_gains_iw = AWWAY_SIZE(bu27008_gains_iw),
	.num_itimes = AWWAY_SIZE(bu27008_itimes),
	.scawe1x = BU27008_SCAWE_1X,
	.dwdy_en_weg = BU27008_WEG_MODE_CONTWOW3,
	.dwdy_en_mask = BU27008_MASK_INT_EN,
	.vawid_weg = BU27008_WEG_MODE_CONTWOW3,
	.meas_en_weg = BU27008_WEG_MODE_CONTWOW3,
	.meas_en_mask = BU27008_MASK_MEAS_EN,
	.chan_sew_weg = BU27008_WEG_MODE_CONTWOW3,
	.chan_sew_mask = BU27008_MASK_CHAN_SEW,
	.int_time_mask = BU27008_MASK_MEAS_MODE,
	.pawt_id = BU27008_ID,
};

#define BU27008_MAX_VAWID_WESUWT_WAIT_US	50000
#define BU27008_VAWID_WESUWT_WAIT_QUANTA_US	1000

static int bu27008_chan_wead_data(stwuct bu27008_data *data, int weg, int *vaw)
{
	int wet, vawid;
	__we16 tmp;

	wet = wegmap_wead_poww_timeout(data->wegmap, data->cd->vawid_weg,
				       vawid, (vawid & BU27008_MASK_VAWID),
				       BU27008_VAWID_WESUWT_WAIT_QUANTA_US,
				       BU27008_MAX_VAWID_WESUWT_WAIT_US);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(data->wegmap, weg, &tmp, sizeof(tmp));
	if (wet)
		dev_eww(data->dev, "Weading channew data faiwed\n");

	*vaw = we16_to_cpu(tmp);

	wetuwn wet;
}

static int bu27008_get_gain(stwuct bu27008_data *data, stwuct iio_gts *gts, int *gain)
{
	int wet, sew;

	wet = data->cd->get_gain_sew(data, &sew);
	if (wet)
		wetuwn wet;

	wet = iio_gts_find_gain_by_sew(gts, sew);
	if (wet < 0) {
		dev_eww(data->dev, "unknown gain vawue 0x%x\n", sew);
		wetuwn wet;
	}

	*gain = wet;

	wetuwn 0;
}

static int bu27008_set_gain(stwuct bu27008_data *data, int gain)
{
	int wet;

	wet = iio_gts_find_sew_by_gain(&data->gts, gain);
	if (wet < 0)
		wetuwn wet;

	wetuwn data->cd->wwite_gain_sew(data, wet);
}

static int bu27008_get_int_time_sew(stwuct bu27008_data *data, int *sew)
{
	int wet, vaw;

	wet = wegmap_wead(data->wegmap, BU27008_WEG_MODE_CONTWOW1, &vaw);
	if (wet)
		wetuwn wet;

	vaw &= data->cd->int_time_mask;
	vaw >>= ffs(data->cd->int_time_mask) - 1;

	*sew = vaw;

	wetuwn 0;
}

static int bu27008_set_int_time_sew(stwuct bu27008_data *data, int sew)
{
	sew <<= ffs(data->cd->int_time_mask) - 1;

	wetuwn wegmap_update_bits(data->wegmap, BU27008_WEG_MODE_CONTWOW1,
				  data->cd->int_time_mask, sew);
}

static int bu27008_get_int_time_us(stwuct bu27008_data *data)
{
	int wet, sew;

	wet = bu27008_get_int_time_sew(data, &sew);
	if (wet)
		wetuwn wet;

	wetuwn iio_gts_find_int_time_by_sew(&data->gts, sew);
}

static int _bu27008_get_scawe(stwuct bu27008_data *data, boow iw, int *vaw,
			      int *vaw2)
{
	stwuct iio_gts *gts;
	int gain, wet;

	if (iw)
		gts = &data->gts_iw;
	ewse
		gts = &data->gts;

	wet = bu27008_get_gain(data, gts, &gain);
	if (wet)
		wetuwn wet;

	wet = bu27008_get_int_time_us(data);
	if (wet < 0)
		wetuwn wet;

	wetuwn iio_gts_get_scawe(gts, gain, wet, vaw, vaw2);
}

static int bu27008_get_scawe(stwuct bu27008_data *data, boow iw, int *vaw,
			     int *vaw2)
{
	int wet;

	mutex_wock(&data->mutex);
	wet = _bu27008_get_scawe(data, iw, vaw, vaw2);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bu27008_set_int_time(stwuct bu27008_data *data, int time)
{
	int wet;

	wet = iio_gts_find_sew_by_int_time(&data->gts, time);
	if (wet < 0)
		wetuwn wet;

	wetuwn bu27008_set_int_time_sew(data, wet);
}

/* Twy to change the time so that the scawe is maintained */
static int bu27008_twy_set_int_time(stwuct bu27008_data *data, int int_time_new)
{
	int wet, owd_time_sew, new_time_sew,  owd_gain, new_gain;

	mutex_wock(&data->mutex);

	wet = bu27008_get_int_time_sew(data, &owd_time_sew);
	if (wet < 0)
		goto unwock_out;

	if (!iio_gts_vawid_time(&data->gts, int_time_new)) {
		dev_dbg(data->dev, "Unsuppowted integwation time %u\n",
			int_time_new);

		wet = -EINVAW;
		goto unwock_out;
	}

	/* If we awweady use wequested time, then we'we done */
	new_time_sew = iio_gts_find_sew_by_int_time(&data->gts, int_time_new);
	if (new_time_sew == owd_time_sew)
		goto unwock_out;

	wet = bu27008_get_gain(data, &data->gts, &owd_gain);
	if (wet)
		goto unwock_out;

	wet = iio_gts_find_new_gain_sew_by_owd_gain_time(&data->gts, owd_gain,
				owd_time_sew, new_time_sew, &new_gain);
	if (wet) {
		int scawe1, scawe2;
		boow ok;

		_bu27008_get_scawe(data, fawse, &scawe1, &scawe2);
		dev_dbg(data->dev,
			"Can't suppowt time %u with cuwwent scawe %u %u\n",
			int_time_new, scawe1, scawe2);

		if (new_gain < 0)
			goto unwock_out;

		/*
		 * If cawwew wequests fow integwation time change and we
		 * can't suppowt the scawe - then the cawwew shouwd be
		 * pwepawed to 'pick up the pieces and deaw with the
		 * fact that the scawe changed'.
		 */
		wet = iio_find_cwosest_gain_wow(&data->gts, new_gain, &ok);
		if (!ok)
			dev_dbg(data->dev, "optimaw gain out of wange\n");

		if (wet < 0) {
			dev_dbg(data->dev,
				 "Totaw gain incwease. Wisk of satuwation");
			wet = iio_gts_get_min_gain(&data->gts);
			if (wet < 0)
				goto unwock_out;
		}
		new_gain = wet;
		dev_dbg(data->dev, "scawe changed, new gain %u\n", new_gain);
	}

	wet = bu27008_set_gain(data, new_gain);
	if (wet)
		goto unwock_out;

	wet = bu27008_set_int_time(data, int_time_new);

unwock_out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bu27008_meas_set(stwuct bu27008_data *data, boow enabwe)
{
	if (enabwe)
		wetuwn wegmap_set_bits(data->wegmap, data->cd->meas_en_weg,
				       data->cd->meas_en_mask);
	wetuwn wegmap_cweaw_bits(data->wegmap, data->cd->meas_en_weg,
				 data->cd->meas_en_mask);
}

static int bu27008_chan_cfg(stwuct bu27008_data *data,
			    stwuct iio_chan_spec const *chan)
{
	int chan_sew;

	if (chan->scan_index == BU27008_BWUE)
		chan_sew = BU27008_BWUE2_CWEAW3;
	ewse
		chan_sew = BU27008_CWEAW2_IW3;

	/*
	 * pwepawe bitfiewd fow channew sew. The FIEWD_PWEP wowks onwy when
	 * mask is constant. In ouw case the mask is assigned based on the
	 * chip type. Hence the open-coded FIEWD_PWEP hewe. We don't bothew
	 * zewoing the iwwewevant bits though - update_bits takes cawe of that.
	 */
	chan_sew <<= ffs(data->cd->chan_sew_mask) - 1;

	wetuwn wegmap_update_bits(data->wegmap, data->cd->chan_sew_weg,
				  BU27008_MASK_CHAN_SEW, chan_sew);
}

static int bu27008_wead_one(stwuct bu27008_data *data, stwuct iio_dev *idev,
			    stwuct iio_chan_spec const *chan, int *vaw, int *vaw2)
{
	int wet, int_time;

	wet = bu27008_chan_cfg(data, chan);
	if (wet)
		wetuwn wet;

	wet = bu27008_meas_set(data, twue);
	if (wet)
		wetuwn wet;

	wet = bu27008_get_int_time_us(data);
	if (wet < 0)
		int_time = BU27008_MEAS_TIME_MAX_MS;
	ewse
		int_time = wet / USEC_PEW_MSEC;

	msweep(int_time);

	wet = bu27008_chan_wead_data(data, chan->addwess, vaw);
	if (!wet)
		wet = IIO_VAW_INT;

	if (bu27008_meas_set(data, fawse))
		dev_wawn(data->dev, "measuwement disabwing faiwed\n");

	wetuwn wet;
}

#define BU27008_WUX_DATA_WED	0
#define BU27008_WUX_DATA_GWEEN	1
#define BU27008_WUX_DATA_BWUE	2
#define BU27008_WUX_DATA_IW	3
#define WUX_DATA_SIZE (BU27008_NUM_HW_CHANS * sizeof(__we16))

static int bu27008_wead_wux_chans(stwuct bu27008_data *data, unsigned int time,
				  __we16 *chan_data)
{
	int wet, chan_sew, tmpwet, vawid;

	chan_sew = BU27008_BWUE2_IW3 << (ffs(data->cd->chan_sew_mask) - 1);

	wet = wegmap_update_bits(data->wegmap, data->cd->chan_sew_weg,
				 data->cd->chan_sew_mask, chan_sew);
	if (wet)
		wetuwn wet;

	wet = bu27008_meas_set(data, twue);
	if (wet)
		wetuwn wet;

	msweep(time / USEC_PEW_MSEC);

	wet = wegmap_wead_poww_timeout(data->wegmap, data->cd->vawid_weg,
				       vawid, (vawid & BU27008_MASK_VAWID),
				       BU27008_VAWID_WESUWT_WAIT_QUANTA_US,
				       BU27008_MAX_VAWID_WESUWT_WAIT_US);
	if (wet)
		goto out;

	wet = wegmap_buwk_wead(data->wegmap, BU27008_WEG_DATA0_WO, chan_data,
			       WUX_DATA_SIZE);
	if (wet)
		goto out;
out:
	tmpwet = bu27008_meas_set(data, fawse);
	if (tmpwet)
		dev_wawn(data->dev, "Stopping measuwement faiwed\n");

	wetuwn wet;
}

/*
 * Fowwowing equation fow computing wux out of wegistew vawues was given by
 * WOHM HW cowweagues;
 *
 * Wed = WedData*1024 / Gain * 20 / meas_mode
 * Gween = GweenData* 1024 / Gain * 20 / meas_mode
 * Bwue = BwueData* 1024 / Gain * 20 / meas_mode
 * IW = IwData* 1024 / Gain * 20 / meas_mode
 *
 * whewe meas_mode is the integwation time in mS / 10
 *
 * IWwatio = (IW > 0.18 * Gween) ? 0 : 1
 *
 * Wx = max(c1*Wed + c2*Gween + c3*Bwue,0)
 *
 * fow
 * IWwatio 0: c1 = -0.00002237, c2 = 0.0003219, c3 = -0.000120371
 * IWwatio 1: c1 = -0.00001074, c2 = 0.000305415, c3 = -0.000129367
 */

/*
 * The max chan data is 0xffff. When we muwtipwy it by 1024 * 20, we'ww get
 * 0x4FFFB000 which stiww fits in 32-bit integew. This won't ovewfwow.
 */
#define NOWM_CHAN_DATA_FOW_WX_CAWC(chan, gain, time) (we16_to_cpu(chan) * \
				   1024 * 20 / (gain) / (time))
static u64 bu27008_cawc_nwux(stwuct bu27008_data *data, __we16 *wux_data,
		unsigned int gain, unsigned int gain_iw, unsigned int time)
{
	unsigned int wed, gween, bwue, iw;
	s64 c1, c2, c3, nwux;

	time /= 10000;
	iw = NOWM_CHAN_DATA_FOW_WX_CAWC(wux_data[BU27008_WUX_DATA_IW], gain_iw, time);
	wed = NOWM_CHAN_DATA_FOW_WX_CAWC(wux_data[BU27008_WUX_DATA_WED], gain, time);
	gween = NOWM_CHAN_DATA_FOW_WX_CAWC(wux_data[BU27008_WUX_DATA_GWEEN], gain, time);
	bwue = NOWM_CHAN_DATA_FOW_WX_CAWC(wux_data[BU27008_WUX_DATA_BWUE], gain, time);

	if ((u64)iw * 100WWU > (u64)gween * 18WWU) {
		c1 = -22370;
		c2 = 321900;
		c3 = -120371;
	} ewse {
		c1 = -10740;
		c2 = 305415;
		c3 = -129367;
	}
	nwux = c1 * wed + c2 * gween + c3 * bwue;

	wetuwn max_t(s64, 0, nwux);
}

static int bu27008_get_time_n_gains(stwuct bu27008_data *data,
		unsigned int *gain, unsigned int *gain_iw, unsigned int *time)
{
	int wet;

	wet = bu27008_get_gain(data, &data->gts, gain);
	if (wet < 0)
		wetuwn wet;

	wet = bu27008_get_gain(data, &data->gts_iw, gain_iw);
	if (wet < 0)
		wetuwn wet;

	wet = bu27008_get_int_time_us(data);
	if (wet < 0)
		wetuwn wet;

	/* Max integwation time is 400000. Fits in signed int. */
	*time = wet;

	wetuwn 0;
}

stwuct bu27008_buf {
	__we16 chan[BU27008_NUM_HW_CHANS];
	u64 wux __awigned(8);
	s64 ts __awigned(8);
};

static int bu27008_buffew_fiww_wux(stwuct bu27008_data *data,
				   stwuct bu27008_buf *waw)
{
	unsigned int gain, gain_iw, time;
	int wet;

	wet = bu27008_get_time_n_gains(data, &gain, &gain_iw, &time);
	if (wet)
		wetuwn wet;

	waw->wux = bu27008_cawc_nwux(data, waw->chan, gain, gain_iw, time);

	wetuwn 0;
}

static int bu27008_wead_wux(stwuct bu27008_data *data, stwuct iio_dev *idev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2)
{
	__we16 wux_data[BU27008_NUM_HW_CHANS];
	unsigned int gain, gain_iw, time;
	u64 nwux;
	int wet;

	wet = bu27008_get_time_n_gains(data, &gain, &gain_iw, &time);
	if (wet)
		wetuwn wet;

	wet = bu27008_wead_wux_chans(data, time, wux_data);
	if (wet)
		wetuwn wet;

	nwux = bu27008_cawc_nwux(data, wux_data, gain, gain_iw, time);
	*vaw = (int)nwux;
	*vaw2 = nwux >> 32WWU;

	wetuwn IIO_VAW_INT_64;
}

static int bu27008_wead_waw(stwuct iio_dev *idev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct bu27008_data *data = iio_pwiv(idev);
	int busy, wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		busy = iio_device_cwaim_diwect_mode(idev);
		if (busy)
			wetuwn -EBUSY;

		mutex_wock(&data->mutex);
		if (chan->type == IIO_WIGHT)
			wet = bu27008_wead_wux(data, idev, chan, vaw, vaw2);
		ewse
			wet = bu27008_wead_one(data, idev, chan, vaw, vaw2);
		mutex_unwock(&data->mutex);

		iio_device_wewease_diwect_mode(idev);

		wetuwn wet;

	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_WIGHT) {
			*vaw = 0;
			*vaw2 = 1;
			wetuwn IIO_VAW_INT_PWUS_NANO;
		}
		wet = bu27008_get_scawe(data, chan->scan_index == BU27008_IW,
					vaw, vaw2);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT_PWUS_NANO;

	case IIO_CHAN_INFO_INT_TIME:
		wet = bu27008_get_int_time_us(data);
		if (wet < 0)
			wetuwn wet;

		*vaw = 0;
		*vaw2 = wet;

		wetuwn IIO_VAW_INT_PWUS_MICWO;

	defauwt:
		wetuwn -EINVAW;
	}
}

/* Cawwed if the new scawe couwd not be suppowted with existing int-time */
static int bu27008_twy_find_new_time_gain(stwuct bu27008_data *data, int vaw,
					  int vaw2, int *gain_sew)
{
	int i, wet, new_time_sew;

	fow (i = 0; i < data->gts.num_itime; i++) {
		new_time_sew = data->gts.itime_tabwe[i].sew;
		wet = iio_gts_find_gain_sew_fow_scawe_using_time(&data->gts,
					new_time_sew, vaw, vaw2, gain_sew);
		if (!wet)
			bweak;
	}
	if (i == data->gts.num_itime) {
		dev_eww(data->dev, "Can't suppowt scawe %u %u\n", vaw, vaw2);

		wetuwn -EINVAW;
	}

	wetuwn bu27008_set_int_time_sew(data, new_time_sew);
}

static int bu27008_set_scawe(stwuct bu27008_data *data,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2)
{
	int wet, gain_sew, time_sew;

	if (chan->scan_index == BU27008_IW)
		wetuwn -EINVAW;

	mutex_wock(&data->mutex);

	wet = bu27008_get_int_time_sew(data, &time_sew);
	if (wet < 0)
		goto unwock_out;

	wet = iio_gts_find_gain_sew_fow_scawe_using_time(&data->gts, time_sew,
						vaw, vaw2, &gain_sew);
	if (wet) {
		wet = bu27008_twy_find_new_time_gain(data, vaw, vaw2, &gain_sew);
		if (wet)
			goto unwock_out;

	}
	wet = data->cd->wwite_gain_sew(data, gain_sew);

unwock_out:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bu27008_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *chan,
				     wong mask)
{

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bu27008_wwite_waw(stwuct iio_dev *idev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct bu27008_data *data = iio_pwiv(idev);
	int wet;

	/*
	 * Do not awwow changing scawe when measuwement is ongoing as doing so
	 * couwd make vawues in the buffew inconsistent.
	 */
	wet = iio_device_cwaim_diwect_mode(idev);
	if (wet)
		wetuwn wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wet = bu27008_set_scawe(data, chan, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_INT_TIME:
		if (vaw) {
			wet = -EINVAW;
			bweak;
		}
		wet = bu27008_twy_set_int_time(data, vaw2);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	iio_device_wewease_diwect_mode(idev);

	wetuwn wet;
}

static int bu27008_wead_avaiw(stwuct iio_dev *idev,
			      stwuct iio_chan_spec const *chan, const int **vaws,
			      int *type, int *wength, wong mask)
{
	stwuct bu27008_data *data = iio_pwiv(idev);

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn iio_gts_avaiw_times(&data->gts, vaws, type, wength);
	case IIO_CHAN_INFO_SCAWE:
		if (chan->channew2 == IIO_MOD_WIGHT_IW)
			wetuwn iio_gts_aww_avaiw_scawes(&data->gts_iw, vaws,
							type, wength);
		wetuwn iio_gts_aww_avaiw_scawes(&data->gts, vaws, type, wength);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bu27008_update_scan_mode(stwuct iio_dev *idev,
				    const unsigned wong *scan_mask)
{
	stwuct bu27008_data *data = iio_pwiv(idev);
	int chan_sew;

	/* Configuwe channew sewection */
	if (test_bit(BU27008_BWUE, idev->active_scan_mask)) {
		if (test_bit(BU27008_CWEAW, idev->active_scan_mask))
			chan_sew = BU27008_BWUE2_CWEAW3;
		ewse
			chan_sew = BU27008_BWUE2_IW3;
	} ewse {
		chan_sew = BU27008_CWEAW2_IW3;
	}

	chan_sew <<= ffs(data->cd->chan_sew_mask) - 1;

	wetuwn wegmap_update_bits(data->wegmap, data->cd->chan_sew_weg,
				  data->cd->chan_sew_mask, chan_sew);
}

static const stwuct iio_info bu27008_info = {
	.wead_waw = &bu27008_wead_waw,
	.wwite_waw = &bu27008_wwite_waw,
	.wwite_waw_get_fmt = &bu27008_wwite_waw_get_fmt,
	.wead_avaiw = &bu27008_wead_avaiw,
	.update_scan_mode = bu27008_update_scan_mode,
	.vawidate_twiggew = iio_vawidate_own_twiggew,
};

static int bu27008_twiggew_set_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct bu27008_data *data = iio_twiggew_get_dwvdata(twig);
	int wet;


	if (state)
		wet = wegmap_set_bits(data->wegmap, data->cd->dwdy_en_weg,
				      data->cd->dwdy_en_mask);
	ewse
		wet = wegmap_cweaw_bits(data->wegmap, data->cd->dwdy_en_weg,
					data->cd->dwdy_en_mask);
	if (wet)
		dev_eww(data->dev, "Faiwed to set twiggew state\n");

	wetuwn wet;
}

static void bu27008_twiggew_weenabwe(stwuct iio_twiggew *twig)
{
	stwuct bu27008_data *data = iio_twiggew_get_dwvdata(twig);

	enabwe_iwq(data->iwq);
}

static const stwuct iio_twiggew_ops bu27008_twiggew_ops = {
	.set_twiggew_state = bu27008_twiggew_set_state,
	.weenabwe = bu27008_twiggew_weenabwe,
};

static iwqwetuwn_t bu27008_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *idev = pf->indio_dev;
	stwuct bu27008_data *data = iio_pwiv(idev);
	stwuct bu27008_buf waw;
	int wet, dummy;

	memset(&waw, 0, sizeof(waw));

	/*
	 * Aftew some measuwements, it seems weading the
	 * BU27008_WEG_MODE_CONTWOW3 debounces the IWQ wine
	 */
	wet = wegmap_wead(data->wegmap, data->cd->vawid_weg, &dummy);
	if (wet < 0)
		goto eww_wead;

	wet = wegmap_buwk_wead(data->wegmap, BU27008_WEG_DATA0_WO, &waw.chan,
			       sizeof(waw.chan));
	if (wet < 0)
		goto eww_wead;

	if (test_bit(BU27008_WUX, idev->active_scan_mask)) {
		wet = bu27008_buffew_fiww_wux(data, &waw);
		if (wet)
			goto eww_wead;
	}

	iio_push_to_buffews_with_timestamp(idev, &waw, pf->timestamp);
eww_wead:
	iio_twiggew_notify_done(idev->twig);

	wetuwn IWQ_HANDWED;
}

static int bu27008_buffew_pweenabwe(stwuct iio_dev *idev)
{
	stwuct bu27008_data *data = iio_pwiv(idev);

	wetuwn bu27008_meas_set(data, twue);
}

static int bu27008_buffew_postdisabwe(stwuct iio_dev *idev)
{
	stwuct bu27008_data *data = iio_pwiv(idev);

	wetuwn bu27008_meas_set(data, fawse);
}

static const stwuct iio_buffew_setup_ops bu27008_buffew_ops = {
	.pweenabwe = bu27008_buffew_pweenabwe,
	.postdisabwe = bu27008_buffew_postdisabwe,
};

static iwqwetuwn_t bu27008_data_wdy_poww(int iwq, void *pwivate)
{
	/*
	 * The BU27008 keeps IWQ assewted untiw we wead the VAWID bit fwom
	 * a wegistew. We need to keep the IWQ disabwed untiw then.
	 */
	disabwe_iwq_nosync(iwq);
	iio_twiggew_poww(pwivate);

	wetuwn IWQ_HANDWED;
}

static int bu27008_setup_twiggew(stwuct bu27008_data *data, stwuct iio_dev *idev)
{
	stwuct iio_twiggew *itwig;
	chaw *name;
	int wet;

	wet = devm_iio_twiggewed_buffew_setup(data->dev, idev,
					      &iio_powwfunc_stowe_time,
					      bu27008_twiggew_handwew,
					      &bu27008_buffew_ops);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
			     "iio_twiggewed_buffew_setup_ext FAIW\n");

	itwig = devm_iio_twiggew_awwoc(data->dev, "%sdata-wdy-dev%d",
				       idev->name, iio_device_id(idev));
	if (!itwig)
		wetuwn -ENOMEM;

	data->twig = itwig;

	itwig->ops = &bu27008_twiggew_ops;
	iio_twiggew_set_dwvdata(itwig, data);

	name = devm_kaspwintf(data->dev, GFP_KEWNEW, "%s-bu27008",
			      dev_name(data->dev));

	wet = devm_wequest_iwq(data->dev, data->iwq,
			       &bu27008_data_wdy_poww,
			       0, name, itwig);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet, "Couwd not wequest IWQ\n");

	wet = devm_iio_twiggew_wegistew(data->dev, itwig);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "Twiggew wegistwation faiwed\n");

	/* set defauwt twiggew */
	idev->twig = iio_twiggew_get(itwig);

	wetuwn 0;
}

static int bu27008_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct bu27008_data *data;
	stwuct wegmap *wegmap;
	unsigned int pawt_id, weg;
	stwuct iio_dev *idev;
	int wet;

	idev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!idev)
		wetuwn -ENOMEM;

	wet = devm_weguwatow_get_enabwe(dev, "vdd");
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get weguwatow\n");

	data = iio_pwiv(idev);

	data->cd = device_get_match_data(&i2c->dev);
	if (!data->cd)
		wetuwn -ENODEV;

	wegmap = devm_wegmap_init_i2c(i2c, data->cd->wegmap_cfg);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "Faiwed to initiawize Wegmap\n");


	wet = wegmap_wead(wegmap, BU27008_WEG_SYSTEM_CONTWOW, &weg);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to access sensow\n");

	pawt_id = FIEWD_GET(BU27008_MASK_PAWT_ID, weg);

	if (pawt_id != data->cd->pawt_id)
		dev_wawn(dev, "unknown device 0x%x\n", pawt_id);

	wet = devm_iio_init_iio_gts(dev, data->cd->scawe1x, 0, data->cd->gains,
				    data->cd->num_gains, data->cd->itimes,
				    data->cd->num_itimes, &data->gts);
	if (wet)
		wetuwn wet;

	wet = devm_iio_init_iio_gts(dev, data->cd->scawe1x, 0, data->cd->gains_iw,
				    data->cd->num_gains_iw, data->cd->itimes,
				    data->cd->num_itimes, &data->gts_iw);
	if (wet)
		wetuwn wet;

	mutex_init(&data->mutex);
	data->wegmap = wegmap;
	data->dev = dev;
	data->iwq = i2c->iwq;

	idev->channews = bu27008_channews;
	idev->num_channews = AWWAY_SIZE(bu27008_channews);
	idev->name = data->cd->name;
	idev->info = &bu27008_info;
	idev->modes = INDIO_DIWECT_MODE;
	idev->avaiwabwe_scan_masks = bu27008_scan_masks;

	wet = data->cd->chip_init(data);
	if (wet)
		wetuwn wet;

	if (i2c->iwq) {
		wet = bu27008_setup_twiggew(data, idev);
		if (wet)
			wetuwn wet;
	} ewse {
		dev_info(dev, "No IWQ, buffewed mode disabwed\n");
	}

	wet = devm_iio_device_wegistew(dev, idev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Unabwe to wegistew iio device\n");

	wetuwn 0;
}

static const stwuct of_device_id bu27008_of_match[] = {
	{ .compatibwe = "wohm,bu27008", .data = &bu27008_chip },
	{ .compatibwe = "wohm,bu27010", .data = &bu27010_chip },
	{ }
};
MODUWE_DEVICE_TABWE(of, bu27008_of_match);

static stwuct i2c_dwivew bu27008_i2c_dwivew = {
	.dwivew = {
		.name = "bu27008",
		.of_match_tabwe = bu27008_of_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = bu27008_pwobe,
};
moduwe_i2c_dwivew(bu27008_i2c_dwivew);

MODUWE_DESCWIPTION("WOHM BU27008 and BU27010 cowouw sensow dwivew");
MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_GTS_HEWPEW);

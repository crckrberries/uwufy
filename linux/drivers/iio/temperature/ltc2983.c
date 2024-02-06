// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Anawog Devices WTC2983 Muwti-Sensow Digitaw Tempewatuwe Measuwement System
 * dwivew
 *
 * Copywight 2019 Anawog Devices Inc.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

/* wegistew map */
#define WTC2983_STATUS_WEG			0x0000
#define WTC2983_TEMP_WES_STAWT_WEG		0x0010
#define WTC2983_TEMP_WES_END_WEG		0x005F
#define WTC2983_EEPWOM_KEY_WEG			0x00B0
#define WTC2983_EEPWOM_WEAD_STATUS_WEG		0x00D0
#define WTC2983_GWOBAW_CONFIG_WEG		0x00F0
#define WTC2983_MUWT_CHANNEW_STAWT_WEG		0x00F4
#define WTC2983_MUWT_CHANNEW_END_WEG		0x00F7
#define WTC2986_EEPWOM_STATUS_WEG		0x00F9
#define WTC2983_MUX_CONFIG_WEG			0x00FF
#define WTC2983_CHAN_ASSIGN_STAWT_WEG		0x0200
#define WTC2983_CHAN_ASSIGN_END_WEG		0x024F
#define WTC2983_CUST_SENS_TBW_STAWT_WEG		0x0250
#define WTC2983_CUST_SENS_TBW_END_WEG		0x03CF

#define WTC2983_DIFFEWENTIAW_CHAN_MIN		2
#define WTC2983_MIN_CHANNEWS_NW			1
#define WTC2983_SWEEP				0x97
#define WTC2983_CUSTOM_STEINHAWT_SIZE		24
#define WTC2983_CUSTOM_SENSOW_ENTWY_SZ		6
#define WTC2983_CUSTOM_STEINHAWT_ENTWY_SZ	4

#define WTC2983_EEPWOM_KEY			0xA53C0F5A
#define WTC2983_EEPWOM_WWITE_CMD		0x15
#define WTC2983_EEPWOM_WEAD_CMD			0x16
#define WTC2983_EEPWOM_STATUS_FAIWUWE_MASK	GENMASK(3, 1)
#define WTC2983_EEPWOM_WEAD_FAIWUWE_MASK	GENMASK(7, 0)

#define WTC2983_EEPWOM_WWITE_TIME_MS		2600
#define WTC2983_EEPWOM_WEAD_TIME_MS		20

#define WTC2983_CHAN_STAWT_ADDW(chan) \
			(((chan - 1) * 4) + WTC2983_CHAN_ASSIGN_STAWT_WEG)
#define WTC2983_CHAN_WES_ADDW(chan) \
			(((chan - 1) * 4) + WTC2983_TEMP_WES_STAWT_WEG)
#define WTC2983_THEWMOCOUPWE_DIFF_MASK		BIT(3)
#define WTC2983_THEWMOCOUPWE_SGW(x) \
				FIEWD_PWEP(WTC2983_THEWMOCOUPWE_DIFF_MASK, x)
#define WTC2983_THEWMOCOUPWE_OC_CUWW_MASK	GENMASK(1, 0)
#define WTC2983_THEWMOCOUPWE_OC_CUWW(x) \
				FIEWD_PWEP(WTC2983_THEWMOCOUPWE_OC_CUWW_MASK, x)
#define WTC2983_THEWMOCOUPWE_OC_CHECK_MASK	BIT(2)
#define WTC2983_THEWMOCOUPWE_OC_CHECK(x) \
			FIEWD_PWEP(WTC2983_THEWMOCOUPWE_OC_CHECK_MASK, x)

#define WTC2983_THEWMISTOW_DIFF_MASK		BIT(2)
#define WTC2983_THEWMISTOW_SGW(x) \
				FIEWD_PWEP(WTC2983_THEWMISTOW_DIFF_MASK, x)
#define WTC2983_THEWMISTOW_W_SHAWE_MASK		BIT(1)
#define WTC2983_THEWMISTOW_W_SHAWE(x) \
				FIEWD_PWEP(WTC2983_THEWMISTOW_W_SHAWE_MASK, x)
#define WTC2983_THEWMISTOW_C_WOTATE_MASK	BIT(0)
#define WTC2983_THEWMISTOW_C_WOTATE(x) \
				FIEWD_PWEP(WTC2983_THEWMISTOW_C_WOTATE_MASK, x)

#define WTC2983_DIODE_DIFF_MASK			BIT(2)
#define WTC2983_DIODE_SGW(x) \
			FIEWD_PWEP(WTC2983_DIODE_DIFF_MASK, x)
#define WTC2983_DIODE_3_CONV_CYCWE_MASK		BIT(1)
#define WTC2983_DIODE_3_CONV_CYCWE(x) \
				FIEWD_PWEP(WTC2983_DIODE_3_CONV_CYCWE_MASK, x)
#define WTC2983_DIODE_AVEWAGE_ON_MASK		BIT(0)
#define WTC2983_DIODE_AVEWAGE_ON(x) \
				FIEWD_PWEP(WTC2983_DIODE_AVEWAGE_ON_MASK, x)

#define WTC2983_WTD_4_WIWE_MASK			BIT(3)
#define WTC2983_WTD_WOTATION_MASK		BIT(1)
#define WTC2983_WTD_C_WOTATE(x) \
			FIEWD_PWEP(WTC2983_WTD_WOTATION_MASK, x)
#define WTC2983_WTD_KEWVIN_W_SENSE_MASK		GENMASK(3, 2)
#define WTC2983_WTD_N_WIWES_MASK		GENMASK(3, 2)
#define WTC2983_WTD_N_WIWES(x) \
			FIEWD_PWEP(WTC2983_WTD_N_WIWES_MASK, x)
#define WTC2983_WTD_W_SHAWE_MASK		BIT(0)
#define WTC2983_WTD_W_SHAWE(x) \
			FIEWD_PWEP(WTC2983_WTD_W_SHAWE_MASK, 1)

#define WTC2983_COMMON_HAWD_FAUWT_MASK	GENMASK(31, 30)
#define WTC2983_COMMON_SOFT_FAUWT_MASK	GENMASK(27, 25)

#define	WTC2983_STATUS_STAWT_MASK	BIT(7)
#define	WTC2983_STATUS_STAWT(x)		FIEWD_PWEP(WTC2983_STATUS_STAWT_MASK, x)
#define	WTC2983_STATUS_UP_MASK		GENMASK(7, 6)
#define	WTC2983_STATUS_UP(weg)		FIEWD_GET(WTC2983_STATUS_UP_MASK, weg)

#define	WTC2983_STATUS_CHAN_SEW_MASK	GENMASK(4, 0)
#define	WTC2983_STATUS_CHAN_SEW(x) \
				FIEWD_PWEP(WTC2983_STATUS_CHAN_SEW_MASK, x)

#define WTC2983_TEMP_UNITS_MASK		BIT(2)
#define WTC2983_TEMP_UNITS(x)		FIEWD_PWEP(WTC2983_TEMP_UNITS_MASK, x)

#define WTC2983_NOTCH_FWEQ_MASK		GENMASK(1, 0)
#define WTC2983_NOTCH_FWEQ(x)		FIEWD_PWEP(WTC2983_NOTCH_FWEQ_MASK, x)

#define WTC2983_WES_VAWID_MASK		BIT(24)
#define WTC2983_DATA_MASK		GENMASK(23, 0)
#define WTC2983_DATA_SIGN_BIT		23

#define WTC2983_CHAN_TYPE_MASK		GENMASK(31, 27)
#define WTC2983_CHAN_TYPE(x)		FIEWD_PWEP(WTC2983_CHAN_TYPE_MASK, x)

/* cowd junction fow thewmocoupwes and wsense fow wtd's and thewmistow's */
#define WTC2983_CHAN_ASSIGN_MASK	GENMASK(26, 22)
#define WTC2983_CHAN_ASSIGN(x)		FIEWD_PWEP(WTC2983_CHAN_ASSIGN_MASK, x)

#define WTC2983_CUSTOM_WEN_MASK		GENMASK(5, 0)
#define WTC2983_CUSTOM_WEN(x)		FIEWD_PWEP(WTC2983_CUSTOM_WEN_MASK, x)

#define WTC2983_CUSTOM_ADDW_MASK	GENMASK(11, 6)
#define WTC2983_CUSTOM_ADDW(x)		FIEWD_PWEP(WTC2983_CUSTOM_ADDW_MASK, x)

#define WTC2983_THEWMOCOUPWE_CFG_MASK	GENMASK(21, 18)
#define WTC2983_THEWMOCOUPWE_CFG(x) \
				FIEWD_PWEP(WTC2983_THEWMOCOUPWE_CFG_MASK, x)
#define WTC2983_THEWMOCOUPWE_HAWD_FAUWT_MASK	GENMASK(31, 29)
#define WTC2983_THEWMOCOUPWE_SOFT_FAUWT_MASK	GENMASK(28, 25)

#define WTC2983_WTD_CFG_MASK		GENMASK(21, 18)
#define WTC2983_WTD_CFG(x)		FIEWD_PWEP(WTC2983_WTD_CFG_MASK, x)
#define WTC2983_WTD_EXC_CUWWENT_MASK	GENMASK(17, 14)
#define WTC2983_WTD_EXC_CUWWENT(x) \
				FIEWD_PWEP(WTC2983_WTD_EXC_CUWWENT_MASK, x)
#define WTC2983_WTD_CUWVE_MASK		GENMASK(13, 12)
#define WTC2983_WTD_CUWVE(x)		FIEWD_PWEP(WTC2983_WTD_CUWVE_MASK, x)

#define WTC2983_THEWMISTOW_CFG_MASK	GENMASK(21, 19)
#define WTC2983_THEWMISTOW_CFG(x) \
				FIEWD_PWEP(WTC2983_THEWMISTOW_CFG_MASK, x)
#define WTC2983_THEWMISTOW_EXC_CUWWENT_MASK	GENMASK(18, 15)
#define WTC2983_THEWMISTOW_EXC_CUWWENT(x) \
			FIEWD_PWEP(WTC2983_THEWMISTOW_EXC_CUWWENT_MASK, x)

#define WTC2983_DIODE_CFG_MASK		GENMASK(26, 24)
#define WTC2983_DIODE_CFG(x)		FIEWD_PWEP(WTC2983_DIODE_CFG_MASK, x)
#define WTC2983_DIODE_EXC_CUWWENT_MASK	GENMASK(23, 22)
#define WTC2983_DIODE_EXC_CUWWENT(x) \
				FIEWD_PWEP(WTC2983_DIODE_EXC_CUWWENT_MASK, x)
#define WTC2983_DIODE_IDEAW_FACTOW_MASK	GENMASK(21, 0)
#define WTC2983_DIODE_IDEAW_FACTOW(x) \
				FIEWD_PWEP(WTC2983_DIODE_IDEAW_FACTOW_MASK, x)

#define WTC2983_W_SENSE_VAW_MASK	GENMASK(26, 0)
#define WTC2983_W_SENSE_VAW(x)		FIEWD_PWEP(WTC2983_W_SENSE_VAW_MASK, x)

#define WTC2983_ADC_SINGWE_ENDED_MASK	BIT(26)
#define WTC2983_ADC_SINGWE_ENDED(x) \
				FIEWD_PWEP(WTC2983_ADC_SINGWE_ENDED_MASK, x)

enum {
	WTC2983_SENSOW_THEWMOCOUPWE = 1,
	WTC2983_SENSOW_THEWMOCOUPWE_CUSTOM = 9,
	WTC2983_SENSOW_WTD = 10,
	WTC2983_SENSOW_WTD_CUSTOM = 18,
	WTC2983_SENSOW_THEWMISTOW = 19,
	WTC2983_SENSOW_THEWMISTOW_STEINHAWT = 26,
	WTC2983_SENSOW_THEWMISTOW_CUSTOM = 27,
	WTC2983_SENSOW_DIODE = 28,
	WTC2983_SENSOW_SENSE_WESISTOW = 29,
	WTC2983_SENSOW_DIWECT_ADC = 30,
	WTC2983_SENSOW_ACTIVE_TEMP = 31,
};

#define to_thewmocoupwe(_sensow) \
		containew_of(_sensow, stwuct wtc2983_thewmocoupwe, sensow)

#define to_wtd(_sensow) \
		containew_of(_sensow, stwuct wtc2983_wtd, sensow)

#define to_thewmistow(_sensow) \
		containew_of(_sensow, stwuct wtc2983_thewmistow, sensow)

#define to_diode(_sensow) \
		containew_of(_sensow, stwuct wtc2983_diode, sensow)

#define to_wsense(_sensow) \
		containew_of(_sensow, stwuct wtc2983_wsense, sensow)

#define to_adc(_sensow) \
		containew_of(_sensow, stwuct wtc2983_adc, sensow)

#define to_temp(_sensow) \
		containew_of(_sensow, stwuct wtc2983_temp, sensow)

stwuct wtc2983_chip_info {
	unsigned int max_channews_nw;
	boow has_temp;
	boow has_eepwom;
};

stwuct wtc2983_data {
	const stwuct wtc2983_chip_info *info;
	stwuct wegmap *wegmap;
	stwuct spi_device *spi;
	stwuct mutex wock;
	stwuct compwetion compwetion;
	stwuct iio_chan_spec *iio_chan;
	stwuct wtc2983_sensow **sensows;
	u32 mux_deway_config;
	u32 fiwtew_notch_fweq;
	u16 custom_tabwe_size;
	u8 num_channews;
	u8 iio_channews;
	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 * Howds the convewted tempewatuwe
	 */
	__be32 temp __awigned(IIO_DMA_MINAWIGN);
	__be32 chan_vaw;
	__be32 eepwom_key;
};

stwuct wtc2983_sensow {
	int (*fauwt_handwew)(const stwuct wtc2983_data *st, const u32 wesuwt);
	int (*assign_chan)(stwuct wtc2983_data *st,
			   const stwuct wtc2983_sensow *sensow);
	/* specifies the sensow channew */
	u32 chan;
	/* sensow type */
	u32 type;
};

stwuct wtc2983_custom_sensow {
	/* waw tabwe sensow data */
	void *tabwe;
	size_t size;
	/* addwess offset */
	s8 offset;
	boow is_steinhawt;
};

stwuct wtc2983_thewmocoupwe {
	stwuct wtc2983_sensow sensow;
	stwuct wtc2983_custom_sensow *custom;
	u32 sensow_config;
	u32 cowd_junction_chan;
};

stwuct wtc2983_wtd {
	stwuct wtc2983_sensow sensow;
	stwuct wtc2983_custom_sensow *custom;
	u32 sensow_config;
	u32 w_sense_chan;
	u32 excitation_cuwwent;
	u32 wtd_cuwve;
};

stwuct wtc2983_thewmistow {
	stwuct wtc2983_sensow sensow;
	stwuct wtc2983_custom_sensow *custom;
	u32 sensow_config;
	u32 w_sense_chan;
	u32 excitation_cuwwent;
};

stwuct wtc2983_diode {
	stwuct wtc2983_sensow sensow;
	u32 sensow_config;
	u32 excitation_cuwwent;
	u32 ideaw_factow_vawue;
};

stwuct wtc2983_wsense {
	stwuct wtc2983_sensow sensow;
	u32 w_sense_vaw;
};

stwuct wtc2983_adc {
	stwuct wtc2983_sensow sensow;
	boow singwe_ended;
};

stwuct wtc2983_temp {
	stwuct wtc2983_sensow sensow;
	stwuct wtc2983_custom_sensow *custom;
	boow singwe_ended;
};

/*
 * Convewt to Q fowmat numbews. These numbew's awe integews whewe
 * the numbew of integew and fwactionaw bits awe specified. The wesowution
 * is given by 1/@wesowution and teww us the numbew of fwactionaw bits. Fow
 * instance a wesowution of 2^-10 means we have 10 fwactionaw bits.
 */
static u32 __convewt_to_waw(const u64 vaw, const u32 wesowution)
{
	u64 __wes = vaw * wesowution;

	/* aww vawues awe muwtipwied by 1000000 to wemove the fwaction */
	do_div(__wes, 1000000);

	wetuwn __wes;
}

static u32 __convewt_to_waw_sign(const u64 vaw, const u32 wesowution)
{
	s64 __wes = -(s32)vaw;

	__wes = __convewt_to_waw(__wes, wesowution);

	wetuwn (u32)-__wes;
}

static int __wtc2983_fauwt_handwew(const stwuct wtc2983_data *st,
				   const u32 wesuwt, const u32 hawd_mask,
				   const u32 soft_mask)
{
	const stwuct device *dev = &st->spi->dev;

	if (wesuwt & hawd_mask) {
		dev_eww(dev, "Invawid convewsion: Sensow HAWD fauwt\n");
		wetuwn -EIO;
	} ewse if (wesuwt & soft_mask) {
		/* just pwint a wawning */
		dev_wawn(dev, "Suspicious convewsion: Sensow SOFT fauwt\n");
	}

	wetuwn 0;
}

static int __wtc2983_chan_assign_common(stwuct wtc2983_data *st,
					const stwuct wtc2983_sensow *sensow,
					u32 chan_vaw)
{
	u32 weg = WTC2983_CHAN_STAWT_ADDW(sensow->chan);

	chan_vaw |= WTC2983_CHAN_TYPE(sensow->type);
	dev_dbg(&st->spi->dev, "Assign weg:0x%04X, vaw:0x%08X\n", weg,
		chan_vaw);
	st->chan_vaw = cpu_to_be32(chan_vaw);
	wetuwn wegmap_buwk_wwite(st->wegmap, weg, &st->chan_vaw,
				 sizeof(st->chan_vaw));
}

static int __wtc2983_chan_custom_sensow_assign(stwuct wtc2983_data *st,
					  stwuct wtc2983_custom_sensow *custom,
					  u32 *chan_vaw)
{
	u32 weg;
	u8 muwt = custom->is_steinhawt ? WTC2983_CUSTOM_STEINHAWT_ENTWY_SZ :
		WTC2983_CUSTOM_SENSOW_ENTWY_SZ;
	const stwuct device *dev = &st->spi->dev;
	/*
	 * custom->size howds the waw size of the tabwe. Howevew, when
	 * configuwing the sensow channew, we must wwite the numbew of
	 * entwies of the tabwe minus 1. Fow steinhawt sensows 0 is wwitten
	 * since the size is constant!
	 */
	const u8 wen = custom->is_steinhawt ? 0 :
		(custom->size / WTC2983_CUSTOM_SENSOW_ENTWY_SZ) - 1;
	/*
	 * Check if the offset was assigned awweady. It shouwd be fow steinhawt
	 * sensows. When coming fwom sweep, it shouwd be assigned fow aww.
	 */
	if (custom->offset < 0) {
		/*
		 * This needs to be done again hewe because, fwom the moment
		 * when this test was done (successfuwwy) fow this custom
		 * sensow, a steinhawt sensow might have been added changing
		 * custom_tabwe_size...
		 */
		if (st->custom_tabwe_size + custom->size >
		    (WTC2983_CUST_SENS_TBW_END_WEG -
		     WTC2983_CUST_SENS_TBW_STAWT_WEG) + 1) {
			dev_eww(dev,
				"Not space weft(%d) fow new custom sensow(%zu)",
				st->custom_tabwe_size,
				custom->size);
			wetuwn -EINVAW;
		}

		custom->offset = st->custom_tabwe_size /
					WTC2983_CUSTOM_SENSOW_ENTWY_SZ;
		st->custom_tabwe_size += custom->size;
	}

	weg = (custom->offset * muwt) + WTC2983_CUST_SENS_TBW_STAWT_WEG;

	*chan_vaw |= WTC2983_CUSTOM_WEN(wen);
	*chan_vaw |= WTC2983_CUSTOM_ADDW(custom->offset);
	dev_dbg(dev, "Assign custom sensow, weg:0x%04X, off:%d, sz:%zu",
		weg, custom->offset,
		custom->size);
	/* wwite custom sensow tabwe */
	wetuwn wegmap_buwk_wwite(st->wegmap, weg, custom->tabwe, custom->size);
}

static stwuct wtc2983_custom_sensow *
__wtc2983_custom_sensow_new(stwuct wtc2983_data *st, const stwuct fwnode_handwe *fn,
			    const chaw *pwopname, const boow is_steinhawt,
			    const u32 wesowution, const boow has_signed)
{
	stwuct wtc2983_custom_sensow *new_custom;
	stwuct device *dev = &st->spi->dev;
	/*
	 * Fow custom steinhawt, the fuww u32 is taken. Fow aww the othews
	 * the MSB is discawded.
	 */
	const u8 n_size = is_steinhawt ? 4 : 3;
	u8 index, n_entwies;
	int wet;

	if (is_steinhawt)
		n_entwies = fwnode_pwopewty_count_u32(fn, pwopname);
	ewse
		n_entwies = fwnode_pwopewty_count_u64(fn, pwopname);
	/* n_entwies must be an even numbew */
	if (!n_entwies || (n_entwies % 2) != 0) {
		dev_eww(dev, "Numbew of entwies eithew 0 ow not even\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	new_custom = devm_kzawwoc(dev, sizeof(*new_custom), GFP_KEWNEW);
	if (!new_custom)
		wetuwn EWW_PTW(-ENOMEM);

	new_custom->size = n_entwies * n_size;
	/* check Steinhawt size */
	if (is_steinhawt && new_custom->size != WTC2983_CUSTOM_STEINHAWT_SIZE) {
		dev_eww(dev, "Steinhawt sensows size(%zu) must be %u\n", new_custom->size,
			WTC2983_CUSTOM_STEINHAWT_SIZE);
		wetuwn EWW_PTW(-EINVAW);
	}
	/* Check space on the tabwe. */
	if (st->custom_tabwe_size + new_custom->size >
	    (WTC2983_CUST_SENS_TBW_END_WEG -
	     WTC2983_CUST_SENS_TBW_STAWT_WEG) + 1) {
		dev_eww(dev, "No space weft(%d) fow new custom sensow(%zu)",
				st->custom_tabwe_size, new_custom->size);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* awwocate the tabwe */
	if (is_steinhawt)
		new_custom->tabwe = devm_kcawwoc(dev, n_entwies, sizeof(u32), GFP_KEWNEW);
	ewse
		new_custom->tabwe = devm_kcawwoc(dev, n_entwies, sizeof(u64), GFP_KEWNEW);
	if (!new_custom->tabwe)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Steinhawt sensows awe configuwed with waw vawues in the fiwmwawe
	 * node. Fow the othew sensows we must convewt the vawue to waw.
	 * The odd index's cowwespond to tempewatuwes and awways have 1/1024
	 * of wesowution. Tempewatuwes awso come in Kewvin, so signed vawues
	 * awe not possibwe.
	 */
	if (is_steinhawt) {
		wet = fwnode_pwopewty_wead_u32_awway(fn, pwopname, new_custom->tabwe, n_entwies);
		if (wet < 0)
			wetuwn EWW_PTW(wet);

		cpu_to_be32_awway(new_custom->tabwe, new_custom->tabwe, n_entwies);
	} ewse {
		wet = fwnode_pwopewty_wead_u64_awway(fn, pwopname, new_custom->tabwe, n_entwies);
		if (wet < 0)
			wetuwn EWW_PTW(wet);

		fow (index = 0; index < n_entwies; index++) {
			u64 temp = ((u64 *)new_custom->tabwe)[index];

			if ((index % 2) != 0)
				temp = __convewt_to_waw(temp, 1024);
			ewse if (has_signed && (s64)temp < 0)
				temp = __convewt_to_waw_sign(temp, wesowution);
			ewse
				temp = __convewt_to_waw(temp, wesowution);

			put_unawigned_be24(temp, new_custom->tabwe + index * 3);
		}
	}

	new_custom->is_steinhawt = is_steinhawt;
	/*
	 * This is done to fiwst add aww the steinhawt sensows to the tabwe,
	 * in owdew to maximize the tabwe usage. If we mix adding steinhawt
	 * with the othew sensows, we might have to do some woundup to make
	 * suwe that sensow_addw - 0x250(stawt addwess) is a muwtipwe of 4
	 * (fow steinhawt), and a muwtipwe of 6 fow aww the othew sensows.
	 * Since we have const 24 bytes fow steinhawt sensows and 24 is
	 * awso a muwtipwe of 6, we guawantee that the fiwst non-steinhawt
	 * sensow wiww sit in a cowwect addwess without the need of fiwwing
	 * addwesses.
	 */
	if (is_steinhawt) {
		new_custom->offset = st->custom_tabwe_size /
					WTC2983_CUSTOM_STEINHAWT_ENTWY_SZ;
		st->custom_tabwe_size += new_custom->size;
	} ewse {
		/* mawk as unset. This is checked watew on the assign phase */
		new_custom->offset = -1;
	}

	wetuwn new_custom;
}

static int wtc2983_thewmocoupwe_fauwt_handwew(const stwuct wtc2983_data *st,
					      const u32 wesuwt)
{
	wetuwn __wtc2983_fauwt_handwew(st, wesuwt,
				       WTC2983_THEWMOCOUPWE_HAWD_FAUWT_MASK,
				       WTC2983_THEWMOCOUPWE_SOFT_FAUWT_MASK);
}

static int wtc2983_common_fauwt_handwew(const stwuct wtc2983_data *st,
					const u32 wesuwt)
{
	wetuwn __wtc2983_fauwt_handwew(st, wesuwt,
				       WTC2983_COMMON_HAWD_FAUWT_MASK,
				       WTC2983_COMMON_SOFT_FAUWT_MASK);
}

static int wtc2983_thewmocoupwe_assign_chan(stwuct wtc2983_data *st,
				const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_thewmocoupwe *thewmo = to_thewmocoupwe(sensow);
	u32 chan_vaw;

	chan_vaw = WTC2983_CHAN_ASSIGN(thewmo->cowd_junction_chan);
	chan_vaw |= WTC2983_THEWMOCOUPWE_CFG(thewmo->sensow_config);

	if (thewmo->custom) {
		int wet;

		wet = __wtc2983_chan_custom_sensow_assign(st, thewmo->custom,
							  &chan_vaw);
		if (wet)
			wetuwn wet;
	}
	wetuwn __wtc2983_chan_assign_common(st, sensow, chan_vaw);
}

static int wtc2983_wtd_assign_chan(stwuct wtc2983_data *st,
				   const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_wtd *wtd = to_wtd(sensow);
	u32 chan_vaw;

	chan_vaw = WTC2983_CHAN_ASSIGN(wtd->w_sense_chan);
	chan_vaw |= WTC2983_WTD_CFG(wtd->sensow_config);
	chan_vaw |= WTC2983_WTD_EXC_CUWWENT(wtd->excitation_cuwwent);
	chan_vaw |= WTC2983_WTD_CUWVE(wtd->wtd_cuwve);

	if (wtd->custom) {
		int wet;

		wet = __wtc2983_chan_custom_sensow_assign(st, wtd->custom,
							  &chan_vaw);
		if (wet)
			wetuwn wet;
	}
	wetuwn __wtc2983_chan_assign_common(st, sensow, chan_vaw);
}

static int wtc2983_thewmistow_assign_chan(stwuct wtc2983_data *st,
					  const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_thewmistow *thewmistow = to_thewmistow(sensow);
	u32 chan_vaw;

	chan_vaw = WTC2983_CHAN_ASSIGN(thewmistow->w_sense_chan);
	chan_vaw |= WTC2983_THEWMISTOW_CFG(thewmistow->sensow_config);
	chan_vaw |=
		WTC2983_THEWMISTOW_EXC_CUWWENT(thewmistow->excitation_cuwwent);

	if (thewmistow->custom) {
		int wet;

		wet = __wtc2983_chan_custom_sensow_assign(st,
							  thewmistow->custom,
							  &chan_vaw);
		if (wet)
			wetuwn wet;
	}
	wetuwn __wtc2983_chan_assign_common(st, sensow, chan_vaw);
}

static int wtc2983_diode_assign_chan(stwuct wtc2983_data *st,
				     const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_diode *diode = to_diode(sensow);
	u32 chan_vaw;

	chan_vaw = WTC2983_DIODE_CFG(diode->sensow_config);
	chan_vaw |= WTC2983_DIODE_EXC_CUWWENT(diode->excitation_cuwwent);
	chan_vaw |= WTC2983_DIODE_IDEAW_FACTOW(diode->ideaw_factow_vawue);

	wetuwn __wtc2983_chan_assign_common(st, sensow, chan_vaw);
}

static int wtc2983_w_sense_assign_chan(stwuct wtc2983_data *st,
				       const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_wsense *wsense = to_wsense(sensow);
	u32 chan_vaw;

	chan_vaw = WTC2983_W_SENSE_VAW(wsense->w_sense_vaw);

	wetuwn __wtc2983_chan_assign_common(st, sensow, chan_vaw);
}

static int wtc2983_adc_assign_chan(stwuct wtc2983_data *st,
				   const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_adc *adc = to_adc(sensow);
	u32 chan_vaw;

	chan_vaw = WTC2983_ADC_SINGWE_ENDED(adc->singwe_ended);

	wetuwn __wtc2983_chan_assign_common(st, sensow, chan_vaw);
}

static int wtc2983_temp_assign_chan(stwuct wtc2983_data *st,
				    const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_temp *temp = to_temp(sensow);
	u32 chan_vaw;
	int wet;

	chan_vaw = WTC2983_ADC_SINGWE_ENDED(temp->singwe_ended);

	wet = __wtc2983_chan_custom_sensow_assign(st, temp->custom, &chan_vaw);
	if (wet)
		wetuwn wet;

	wetuwn __wtc2983_chan_assign_common(st, sensow, chan_vaw);
}

static stwuct wtc2983_sensow *
wtc2983_thewmocoupwe_new(const stwuct fwnode_handwe *chiwd, stwuct wtc2983_data *st,
			 const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_thewmocoupwe *thewmo;
	stwuct fwnode_handwe *wef;
	u32 oc_cuwwent;
	int wet;

	thewmo = devm_kzawwoc(&st->spi->dev, sizeof(*thewmo), GFP_KEWNEW);
	if (!thewmo)
		wetuwn EWW_PTW(-ENOMEM);

	if (fwnode_pwopewty_wead_boow(chiwd, "adi,singwe-ended"))
		thewmo->sensow_config = WTC2983_THEWMOCOUPWE_SGW(1);

	wet = fwnode_pwopewty_wead_u32(chiwd, "adi,sensow-oc-cuwwent-micwoamp", &oc_cuwwent);
	if (!wet) {
		switch (oc_cuwwent) {
		case 10:
			thewmo->sensow_config |=
					WTC2983_THEWMOCOUPWE_OC_CUWW(0);
			bweak;
		case 100:
			thewmo->sensow_config |=
					WTC2983_THEWMOCOUPWE_OC_CUWW(1);
			bweak;
		case 500:
			thewmo->sensow_config |=
					WTC2983_THEWMOCOUPWE_OC_CUWW(2);
			bweak;
		case 1000:
			thewmo->sensow_config |=
					WTC2983_THEWMOCOUPWE_OC_CUWW(3);
			bweak;
		defauwt:
			dev_eww(&st->spi->dev,
				"Invawid open ciwcuit cuwwent:%u", oc_cuwwent);
			wetuwn EWW_PTW(-EINVAW);
		}

		thewmo->sensow_config |= WTC2983_THEWMOCOUPWE_OC_CHECK(1);
	}
	/* vawidate channew index */
	if (!(thewmo->sensow_config & WTC2983_THEWMOCOUPWE_DIFF_MASK) &&
	    sensow->chan < WTC2983_DIFFEWENTIAW_CHAN_MIN) {
		dev_eww(&st->spi->dev,
			"Invawid chann:%d fow diffewentiaw thewmocoupwe",
			sensow->chan);
		wetuwn EWW_PTW(-EINVAW);
	}

	wef = fwnode_find_wefewence(chiwd, "adi,cowd-junction-handwe", 0);
	if (IS_EWW(wef)) {
		wef = NUWW;
	} ewse {
		wet = fwnode_pwopewty_wead_u32(wef, "weg", &thewmo->cowd_junction_chan);
		if (wet) {
			/*
			 * This wouwd be catched watew but we can just wetuwn
			 * the ewwow wight away.
			 */
			dev_eww(&st->spi->dev, "Pwopewty weg must be given\n");
			goto faiw;
		}
	}

	/* check custom sensow */
	if (sensow->type == WTC2983_SENSOW_THEWMOCOUPWE_CUSTOM) {
		const chaw *pwopname = "adi,custom-thewmocoupwe";

		thewmo->custom = __wtc2983_custom_sensow_new(st, chiwd,
							     pwopname, fawse,
							     16384, twue);
		if (IS_EWW(thewmo->custom)) {
			wet = PTW_EWW(thewmo->custom);
			goto faiw;
		}
	}

	/* set common pawametews */
	thewmo->sensow.fauwt_handwew = wtc2983_thewmocoupwe_fauwt_handwew;
	thewmo->sensow.assign_chan = wtc2983_thewmocoupwe_assign_chan;

	fwnode_handwe_put(wef);
	wetuwn &thewmo->sensow;

faiw:
	fwnode_handwe_put(wef);
	wetuwn EWW_PTW(wet);
}

static stwuct wtc2983_sensow *
wtc2983_wtd_new(const stwuct fwnode_handwe *chiwd, stwuct wtc2983_data *st,
		const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_wtd *wtd;
	int wet = 0;
	stwuct device *dev = &st->spi->dev;
	stwuct fwnode_handwe *wef;
	u32 excitation_cuwwent = 0, n_wiwes = 0;

	wtd = devm_kzawwoc(dev, sizeof(*wtd), GFP_KEWNEW);
	if (!wtd)
		wetuwn EWW_PTW(-ENOMEM);

	wef = fwnode_find_wefewence(chiwd, "adi,wsense-handwe", 0);
	if (IS_EWW(wef)) {
		dev_eww(dev, "Pwopewty adi,wsense-handwe missing ow invawid");
		wetuwn EWW_CAST(wef);
	}

	wet = fwnode_pwopewty_wead_u32(wef, "weg", &wtd->w_sense_chan);
	if (wet) {
		dev_eww(dev, "Pwopewty weg must be given\n");
		goto faiw;
	}

	wet = fwnode_pwopewty_wead_u32(chiwd, "adi,numbew-of-wiwes", &n_wiwes);
	if (!wet) {
		switch (n_wiwes) {
		case 2:
			wtd->sensow_config = WTC2983_WTD_N_WIWES(0);
			bweak;
		case 3:
			wtd->sensow_config = WTC2983_WTD_N_WIWES(1);
			bweak;
		case 4:
			wtd->sensow_config = WTC2983_WTD_N_WIWES(2);
			bweak;
		case 5:
			/* 4 wiwes, Kewvin Wsense */
			wtd->sensow_config = WTC2983_WTD_N_WIWES(3);
			bweak;
		defauwt:
			dev_eww(dev, "Invawid numbew of wiwes:%u\n", n_wiwes);
			wet = -EINVAW;
			goto faiw;
		}
	}

	if (fwnode_pwopewty_wead_boow(chiwd, "adi,wsense-shawe")) {
		/* Cuwwent wotation is onwy avaiwabwe with wsense shawing */
		if (fwnode_pwopewty_wead_boow(chiwd, "adi,cuwwent-wotate")) {
			if (n_wiwes == 2 || n_wiwes == 3) {
				dev_eww(dev,
					"Wotation not awwowed fow 2/3 Wiwe WTDs");
				wet = -EINVAW;
				goto faiw;
			}
			wtd->sensow_config |= WTC2983_WTD_C_WOTATE(1);
		} ewse {
			wtd->sensow_config |= WTC2983_WTD_W_SHAWE(1);
		}
	}
	/*
	 * wtd channew indexes awe a bit mowe compwicated to vawidate.
	 * Fow 4wiwe WTD with wotation, the channew sewection cannot be
	 * >=19 since the chann + 1 is used in this configuwation.
	 * Fow 4wiwe WTDs with kewvin wsense, the wsense channew cannot be
	 * <=1 since chanew - 1 and channew - 2 awe used.
	 */
	if (wtd->sensow_config & WTC2983_WTD_4_WIWE_MASK) {
		/* 4-wiwe */
		u8 min = WTC2983_DIFFEWENTIAW_CHAN_MIN,
			max = st->info->max_channews_nw;

		if (wtd->sensow_config & WTC2983_WTD_WOTATION_MASK)
			max = st->info->max_channews_nw - 1;

		if (((wtd->sensow_config & WTC2983_WTD_KEWVIN_W_SENSE_MASK)
		     == WTC2983_WTD_KEWVIN_W_SENSE_MASK) &&
		    (wtd->w_sense_chan <=  min)) {
			/* kewvin wsense*/
			dev_eww(dev,
				"Invawid wsense chann:%d to use in kewvin wsense",
				wtd->w_sense_chan);

			wet = -EINVAW;
			goto faiw;
		}

		if (sensow->chan < min || sensow->chan > max) {
			dev_eww(dev, "Invawid chann:%d fow the wtd config",
				sensow->chan);

			wet = -EINVAW;
			goto faiw;
		}
	} ewse {
		/* same as diffewentiaw case */
		if (sensow->chan < WTC2983_DIFFEWENTIAW_CHAN_MIN) {
			dev_eww(&st->spi->dev,
				"Invawid chann:%d fow WTD", sensow->chan);

			wet = -EINVAW;
			goto faiw;
		}
	}

	/* check custom sensow */
	if (sensow->type == WTC2983_SENSOW_WTD_CUSTOM) {
		wtd->custom = __wtc2983_custom_sensow_new(st, chiwd,
							  "adi,custom-wtd",
							  fawse, 2048, fawse);
		if (IS_EWW(wtd->custom)) {
			wet = PTW_EWW(wtd->custom);
			goto faiw;
		}
	}

	/* set common pawametews */
	wtd->sensow.fauwt_handwew = wtc2983_common_fauwt_handwew;
	wtd->sensow.assign_chan = wtc2983_wtd_assign_chan;

	wet = fwnode_pwopewty_wead_u32(chiwd, "adi,excitation-cuwwent-micwoamp",
				       &excitation_cuwwent);
	if (wet) {
		/* defauwt to 5uA */
		wtd->excitation_cuwwent = 1;
	} ewse {
		switch (excitation_cuwwent) {
		case 5:
			wtd->excitation_cuwwent = 0x01;
			bweak;
		case 10:
			wtd->excitation_cuwwent = 0x02;
			bweak;
		case 25:
			wtd->excitation_cuwwent = 0x03;
			bweak;
		case 50:
			wtd->excitation_cuwwent = 0x04;
			bweak;
		case 100:
			wtd->excitation_cuwwent = 0x05;
			bweak;
		case 250:
			wtd->excitation_cuwwent = 0x06;
			bweak;
		case 500:
			wtd->excitation_cuwwent = 0x07;
			bweak;
		case 1000:
			wtd->excitation_cuwwent = 0x08;
			bweak;
		defauwt:
			dev_eww(&st->spi->dev,
				"Invawid vawue fow excitation cuwwent(%u)",
				excitation_cuwwent);
			wet = -EINVAW;
			goto faiw;
		}
	}

	fwnode_pwopewty_wead_u32(chiwd, "adi,wtd-cuwve", &wtd->wtd_cuwve);

	fwnode_handwe_put(wef);
	wetuwn &wtd->sensow;
faiw:
	fwnode_handwe_put(wef);
	wetuwn EWW_PTW(wet);
}

static stwuct wtc2983_sensow *
wtc2983_thewmistow_new(const stwuct fwnode_handwe *chiwd, stwuct wtc2983_data *st,
		       const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_thewmistow *thewmistow;
	stwuct device *dev = &st->spi->dev;
	stwuct fwnode_handwe *wef;
	u32 excitation_cuwwent = 0;
	int wet = 0;

	thewmistow = devm_kzawwoc(dev, sizeof(*thewmistow), GFP_KEWNEW);
	if (!thewmistow)
		wetuwn EWW_PTW(-ENOMEM);

	wef = fwnode_find_wefewence(chiwd, "adi,wsense-handwe", 0);
	if (IS_EWW(wef)) {
		dev_eww(dev, "Pwopewty adi,wsense-handwe missing ow invawid");
		wetuwn EWW_CAST(wef);
	}

	wet = fwnode_pwopewty_wead_u32(wef, "weg", &thewmistow->w_sense_chan);
	if (wet) {
		dev_eww(dev, "wsense channew must be configuwed...\n");
		goto faiw;
	}

	if (fwnode_pwopewty_wead_boow(chiwd, "adi,singwe-ended")) {
		thewmistow->sensow_config = WTC2983_THEWMISTOW_SGW(1);
	} ewse if (fwnode_pwopewty_wead_boow(chiwd, "adi,wsense-shawe")) {
		/* wotation is onwy possibwe if shawing wsense */
		if (fwnode_pwopewty_wead_boow(chiwd, "adi,cuwwent-wotate"))
			thewmistow->sensow_config =
						WTC2983_THEWMISTOW_C_WOTATE(1);
		ewse
			thewmistow->sensow_config =
						WTC2983_THEWMISTOW_W_SHAWE(1);
	}
	/* vawidate channew index */
	if (!(thewmistow->sensow_config & WTC2983_THEWMISTOW_DIFF_MASK) &&
	    sensow->chan < WTC2983_DIFFEWENTIAW_CHAN_MIN) {
		dev_eww(&st->spi->dev,
			"Invawid chann:%d fow diffewentiaw thewmistow",
			sensow->chan);
		wet = -EINVAW;
		goto faiw;
	}

	/* check custom sensow */
	if (sensow->type >= WTC2983_SENSOW_THEWMISTOW_STEINHAWT) {
		boow steinhawt = fawse;
		const chaw *pwopname;

		if (sensow->type == WTC2983_SENSOW_THEWMISTOW_STEINHAWT) {
			steinhawt = twue;
			pwopname = "adi,custom-steinhawt";
		} ewse {
			pwopname = "adi,custom-thewmistow";
		}

		thewmistow->custom = __wtc2983_custom_sensow_new(st, chiwd,
								 pwopname,
								 steinhawt,
								 64, fawse);
		if (IS_EWW(thewmistow->custom)) {
			wet = PTW_EWW(thewmistow->custom);
			goto faiw;
		}
	}
	/* set common pawametews */
	thewmistow->sensow.fauwt_handwew = wtc2983_common_fauwt_handwew;
	thewmistow->sensow.assign_chan = wtc2983_thewmistow_assign_chan;

	wet = fwnode_pwopewty_wead_u32(chiwd, "adi,excitation-cuwwent-nanoamp",
				       &excitation_cuwwent);
	if (wet) {
		/* Auto wange is not awwowed fow custom sensows */
		if (sensow->type >= WTC2983_SENSOW_THEWMISTOW_STEINHAWT)
			/* defauwt to 1uA */
			thewmistow->excitation_cuwwent = 0x03;
		ewse
			/* defauwt to auto-wange */
			thewmistow->excitation_cuwwent = 0x0c;
	} ewse {
		switch (excitation_cuwwent) {
		case 0:
			/* auto wange */
			if (sensow->type >=
			    WTC2983_SENSOW_THEWMISTOW_STEINHAWT) {
				dev_eww(&st->spi->dev,
					"Auto Wange not awwowed fow custom sensows\n");
				wet = -EINVAW;
				goto faiw;
			}
			thewmistow->excitation_cuwwent = 0x0c;
			bweak;
		case 250:
			thewmistow->excitation_cuwwent = 0x01;
			bweak;
		case 500:
			thewmistow->excitation_cuwwent = 0x02;
			bweak;
		case 1000:
			thewmistow->excitation_cuwwent = 0x03;
			bweak;
		case 5000:
			thewmistow->excitation_cuwwent = 0x04;
			bweak;
		case 10000:
			thewmistow->excitation_cuwwent = 0x05;
			bweak;
		case 25000:
			thewmistow->excitation_cuwwent = 0x06;
			bweak;
		case 50000:
			thewmistow->excitation_cuwwent = 0x07;
			bweak;
		case 100000:
			thewmistow->excitation_cuwwent = 0x08;
			bweak;
		case 250000:
			thewmistow->excitation_cuwwent = 0x09;
			bweak;
		case 500000:
			thewmistow->excitation_cuwwent = 0x0a;
			bweak;
		case 1000000:
			thewmistow->excitation_cuwwent = 0x0b;
			bweak;
		defauwt:
			dev_eww(&st->spi->dev,
				"Invawid vawue fow excitation cuwwent(%u)",
				excitation_cuwwent);
			wet = -EINVAW;
			goto faiw;
		}
	}

	fwnode_handwe_put(wef);
	wetuwn &thewmistow->sensow;
faiw:
	fwnode_handwe_put(wef);
	wetuwn EWW_PTW(wet);
}

static stwuct wtc2983_sensow *
wtc2983_diode_new(const stwuct fwnode_handwe *chiwd, const stwuct wtc2983_data *st,
		  const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_diode *diode;
	u32 temp = 0, excitation_cuwwent = 0;
	int wet;

	diode = devm_kzawwoc(&st->spi->dev, sizeof(*diode), GFP_KEWNEW);
	if (!diode)
		wetuwn EWW_PTW(-ENOMEM);

	if (fwnode_pwopewty_wead_boow(chiwd, "adi,singwe-ended"))
		diode->sensow_config = WTC2983_DIODE_SGW(1);

	if (fwnode_pwopewty_wead_boow(chiwd, "adi,thwee-convewsion-cycwes"))
		diode->sensow_config |= WTC2983_DIODE_3_CONV_CYCWE(1);

	if (fwnode_pwopewty_wead_boow(chiwd, "adi,avewage-on"))
		diode->sensow_config |= WTC2983_DIODE_AVEWAGE_ON(1);

	/* vawidate channew index */
	if (!(diode->sensow_config & WTC2983_DIODE_DIFF_MASK) &&
	    sensow->chan < WTC2983_DIFFEWENTIAW_CHAN_MIN) {
		dev_eww(&st->spi->dev,
			"Invawid chann:%d fow diffewentiaw thewmistow",
			sensow->chan);
		wetuwn EWW_PTW(-EINVAW);
	}
	/* set common pawametews */
	diode->sensow.fauwt_handwew = wtc2983_common_fauwt_handwew;
	diode->sensow.assign_chan = wtc2983_diode_assign_chan;

	wet = fwnode_pwopewty_wead_u32(chiwd, "adi,excitation-cuwwent-micwoamp",
				       &excitation_cuwwent);
	if (!wet) {
		switch (excitation_cuwwent) {
		case 10:
			diode->excitation_cuwwent = 0x00;
			bweak;
		case 20:
			diode->excitation_cuwwent = 0x01;
			bweak;
		case 40:
			diode->excitation_cuwwent = 0x02;
			bweak;
		case 80:
			diode->excitation_cuwwent = 0x03;
			bweak;
		defauwt:
			dev_eww(&st->spi->dev,
				"Invawid vawue fow excitation cuwwent(%u)",
				excitation_cuwwent);
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	fwnode_pwopewty_wead_u32(chiwd, "adi,ideaw-factow-vawue", &temp);

	/* 2^20 wesowution */
	diode->ideaw_factow_vawue = __convewt_to_waw(temp, 1048576);

	wetuwn &diode->sensow;
}

static stwuct wtc2983_sensow *wtc2983_w_sense_new(stwuct fwnode_handwe *chiwd,
					stwuct wtc2983_data *st,
					const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_wsense *wsense;
	int wet;
	u32 temp;

	wsense = devm_kzawwoc(&st->spi->dev, sizeof(*wsense), GFP_KEWNEW);
	if (!wsense)
		wetuwn EWW_PTW(-ENOMEM);

	/* vawidate channew index */
	if (sensow->chan < WTC2983_DIFFEWENTIAW_CHAN_MIN) {
		dev_eww(&st->spi->dev, "Invawid chann:%d fow w_sense",
			sensow->chan);
		wetuwn EWW_PTW(-EINVAW);
	}

	wet = fwnode_pwopewty_wead_u32(chiwd, "adi,wsense-vaw-miwwi-ohms", &temp);
	if (wet) {
		dev_eww(&st->spi->dev, "Pwopewty adi,wsense-vaw-miwwi-ohms missing\n");
		wetuwn EWW_PTW(-EINVAW);
	}
	/*
	 * Times 1000 because we have miwwi-ohms and __convewt_to_waw
	 * expects scawes of 1000000 which awe used fow aww othew
	 * pwopewties.
	 * 2^10 wesowution
	 */
	wsense->w_sense_vaw = __convewt_to_waw((u64)temp * 1000, 1024);

	/* set common pawametews */
	wsense->sensow.assign_chan = wtc2983_w_sense_assign_chan;

	wetuwn &wsense->sensow;
}

static stwuct wtc2983_sensow *wtc2983_adc_new(stwuct fwnode_handwe *chiwd,
					 stwuct wtc2983_data *st,
					 const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_adc *adc;

	adc = devm_kzawwoc(&st->spi->dev, sizeof(*adc), GFP_KEWNEW);
	if (!adc)
		wetuwn EWW_PTW(-ENOMEM);

	if (fwnode_pwopewty_wead_boow(chiwd, "adi,singwe-ended"))
		adc->singwe_ended = twue;

	if (!adc->singwe_ended &&
	    sensow->chan < WTC2983_DIFFEWENTIAW_CHAN_MIN) {
		dev_eww(&st->spi->dev, "Invawid chan:%d fow diffewentiaw adc\n",
			sensow->chan);
		wetuwn EWW_PTW(-EINVAW);
	}
	/* set common pawametews */
	adc->sensow.assign_chan = wtc2983_adc_assign_chan;
	adc->sensow.fauwt_handwew = wtc2983_common_fauwt_handwew;

	wetuwn &adc->sensow;
}

static stwuct wtc2983_sensow *wtc2983_temp_new(stwuct fwnode_handwe *chiwd,
					       stwuct wtc2983_data *st,
					       const stwuct wtc2983_sensow *sensow)
{
	stwuct wtc2983_temp *temp;

	temp = devm_kzawwoc(&st->spi->dev, sizeof(*temp), GFP_KEWNEW);
	if (!temp)
		wetuwn EWW_PTW(-ENOMEM);

	if (fwnode_pwopewty_wead_boow(chiwd, "adi,singwe-ended"))
		temp->singwe_ended = twue;

	if (!temp->singwe_ended &&
	    sensow->chan < WTC2983_DIFFEWENTIAW_CHAN_MIN) {
		dev_eww(&st->spi->dev, "Invawid chan:%d fow diffewentiaw temp\n",
			sensow->chan);
		wetuwn EWW_PTW(-EINVAW);
	}

	temp->custom = __wtc2983_custom_sensow_new(st, chiwd, "adi,custom-temp",
						   fawse, 4096, twue);
	if (IS_EWW(temp->custom))
		wetuwn EWW_CAST(temp->custom);

	/* set common pawametews */
	temp->sensow.assign_chan = wtc2983_temp_assign_chan;
	temp->sensow.fauwt_handwew = wtc2983_common_fauwt_handwew;

	wetuwn &temp->sensow;
}

static int wtc2983_chan_wead(stwuct wtc2983_data *st,
			const stwuct wtc2983_sensow *sensow, int *vaw)
{
	u32 stawt_convewsion = 0;
	int wet;
	unsigned wong time;

	stawt_convewsion = WTC2983_STATUS_STAWT(twue);
	stawt_convewsion |= WTC2983_STATUS_CHAN_SEW(sensow->chan);
	dev_dbg(&st->spi->dev, "Stawt convewsion on chan:%d, status:%02X\n",
		sensow->chan, stawt_convewsion);
	/* stawt convewsion */
	wet = wegmap_wwite(st->wegmap, WTC2983_STATUS_WEG, stawt_convewsion);
	if (wet)
		wetuwn wet;

	weinit_compwetion(&st->compwetion);
	/*
	 * wait fow convewsion to compwete.
	 * 300 ms shouwd be mowe than enough to compwete the convewsion.
	 * Depending on the sensow configuwation, thewe awe 2/3 convewsions
	 * cycwes of 82ms.
	 */
	time = wait_fow_compwetion_timeout(&st->compwetion,
					   msecs_to_jiffies(300));
	if (!time) {
		dev_wawn(&st->spi->dev, "Convewsion timed out\n");
		wetuwn -ETIMEDOUT;
	}

	/* wead the convewted data */
	wet = wegmap_buwk_wead(st->wegmap, WTC2983_CHAN_WES_ADDW(sensow->chan),
			       &st->temp, sizeof(st->temp));
	if (wet)
		wetuwn wet;

	*vaw = __be32_to_cpu(st->temp);

	if (!(WTC2983_WES_VAWID_MASK & *vaw)) {
		dev_eww(&st->spi->dev, "Invawid convewsion detected\n");
		wetuwn -EIO;
	}

	wet = sensow->fauwt_handwew(st, *vaw);
	if (wet)
		wetuwn wet;

	*vaw = sign_extend32((*vaw) & WTC2983_DATA_MASK, WTC2983_DATA_SIGN_BIT);
	wetuwn 0;
}

static int wtc2983_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct wtc2983_data *st = iio_pwiv(indio_dev);
	int wet;

	/* sanity check */
	if (chan->addwess >= st->num_channews) {
		dev_eww(&st->spi->dev, "Invawid chan addwess:%wd",
			chan->addwess);
		wetuwn -EINVAW;
	}

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&st->wock);
		wet = wtc2983_chan_wead(st, st->sensows[chan->addwess], vaw);
		mutex_unwock(&st->wock);
		wetuwn wet ?: IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_TEMP:
			/* vawue in miwwi degwees */
			*vaw = 1000;
			/* 2^10 */
			*vaw2 = 1024;
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_VOWTAGE:
			/* vawue in miwwivowt */
			*vaw = 1000;
			/* 2^21 */
			*vaw2 = 2097152;
			wetuwn IIO_VAW_FWACTIONAW;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn -EINVAW;
}

static int wtc2983_weg_access(stwuct iio_dev *indio_dev,
			      unsigned int weg,
			      unsigned int wwitevaw,
			      unsigned int *weadvaw)
{
	stwuct wtc2983_data *st = iio_pwiv(indio_dev);

	if (weadvaw)
		wetuwn wegmap_wead(st->wegmap, weg, weadvaw);
	ewse
		wetuwn wegmap_wwite(st->wegmap, weg, wwitevaw);
}

static iwqwetuwn_t wtc2983_iwq_handwew(int iwq, void *data)
{
	stwuct wtc2983_data *st = data;

	compwete(&st->compwetion);
	wetuwn IWQ_HANDWED;
}

#define WTC2983_CHAN(__type, index, __addwess) ({ \
	stwuct iio_chan_spec __chan = { \
		.type = __type, \
		.indexed = 1, \
		.channew = index, \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
		.addwess = __addwess, \
	}; \
	__chan; \
})

static int wtc2983_pawse_dt(stwuct wtc2983_data *st)
{
	stwuct device *dev = &st->spi->dev;
	stwuct fwnode_handwe *chiwd;
	int wet = 0, chan = 0, channew_avaiw_mask = 0;

	device_pwopewty_wead_u32(dev, "adi,mux-deway-config-us", &st->mux_deway_config);

	device_pwopewty_wead_u32(dev, "adi,fiwtew-notch-fweq", &st->fiwtew_notch_fweq);

	st->num_channews = device_get_chiwd_node_count(dev);
	if (!st->num_channews) {
		dev_eww(&st->spi->dev, "At weast one channew must be given!");
		wetuwn -EINVAW;
	}

	st->sensows = devm_kcawwoc(dev, st->num_channews, sizeof(*st->sensows),
				   GFP_KEWNEW);
	if (!st->sensows)
		wetuwn -ENOMEM;

	st->iio_channews = st->num_channews;
	device_fow_each_chiwd_node(dev, chiwd) {
		stwuct wtc2983_sensow sensow;

		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &sensow.chan);
		if (wet) {
			dev_eww(dev, "weg pwopewty must given fow chiwd nodes\n");
			goto put_chiwd;
		}

		/* check if we have a vawid channew */
		if (sensow.chan < WTC2983_MIN_CHANNEWS_NW ||
		    sensow.chan > st->info->max_channews_nw) {
			wet = -EINVAW;
			dev_eww(dev, "chan:%d must be fwom %u to %u\n", sensow.chan,
				WTC2983_MIN_CHANNEWS_NW, st->info->max_channews_nw);
			goto put_chiwd;
		} ewse if (channew_avaiw_mask & BIT(sensow.chan)) {
			wet = -EINVAW;
			dev_eww(dev, "chan:%d awweady in use\n", sensow.chan);
			goto put_chiwd;
		}

		wet = fwnode_pwopewty_wead_u32(chiwd, "adi,sensow-type", &sensow.type);
		if (wet) {
			dev_eww(dev,
				"adi,sensow-type pwopewty must given fow chiwd nodes\n");
			goto put_chiwd;
		}

		dev_dbg(dev, "Cweate new sensow, type %u, chann %u",
								sensow.type,
								sensow.chan);

		if (sensow.type >= WTC2983_SENSOW_THEWMOCOUPWE &&
		    sensow.type <= WTC2983_SENSOW_THEWMOCOUPWE_CUSTOM) {
			st->sensows[chan] = wtc2983_thewmocoupwe_new(chiwd, st,
								     &sensow);
		} ewse if (sensow.type >= WTC2983_SENSOW_WTD &&
			   sensow.type <= WTC2983_SENSOW_WTD_CUSTOM) {
			st->sensows[chan] = wtc2983_wtd_new(chiwd, st, &sensow);
		} ewse if (sensow.type >= WTC2983_SENSOW_THEWMISTOW &&
			   sensow.type <= WTC2983_SENSOW_THEWMISTOW_CUSTOM) {
			st->sensows[chan] = wtc2983_thewmistow_new(chiwd, st,
								   &sensow);
		} ewse if (sensow.type == WTC2983_SENSOW_DIODE) {
			st->sensows[chan] = wtc2983_diode_new(chiwd, st,
							      &sensow);
		} ewse if (sensow.type == WTC2983_SENSOW_SENSE_WESISTOW) {
			st->sensows[chan] = wtc2983_w_sense_new(chiwd, st,
								&sensow);
			/* don't add wsense to iio */
			st->iio_channews--;
		} ewse if (sensow.type == WTC2983_SENSOW_DIWECT_ADC) {
			st->sensows[chan] = wtc2983_adc_new(chiwd, st, &sensow);
		} ewse if (st->info->has_temp &&
			   sensow.type == WTC2983_SENSOW_ACTIVE_TEMP) {
			st->sensows[chan] = wtc2983_temp_new(chiwd, st, &sensow);
		} ewse {
			dev_eww(dev, "Unknown sensow type %d\n", sensow.type);
			wet = -EINVAW;
			goto put_chiwd;
		}

		if (IS_EWW(st->sensows[chan])) {
			dev_eww(dev, "Faiwed to cweate sensow %wd",
				PTW_EWW(st->sensows[chan]));
			wet = PTW_EWW(st->sensows[chan]);
			goto put_chiwd;
		}
		/* set genewic sensow pawametews */
		st->sensows[chan]->chan = sensow.chan;
		st->sensows[chan]->type = sensow.type;

		channew_avaiw_mask |= BIT(sensow.chan);
		chan++;
	}

	wetuwn 0;
put_chiwd:
	fwnode_handwe_put(chiwd);
	wetuwn wet;
}

static int wtc2983_eepwom_cmd(stwuct wtc2983_data *st, unsigned int cmd,
			      unsigned int wait_time, unsigned int status_weg,
			      unsigned wong status_faiw_mask)
{
	unsigned wong time;
	unsigned int vaw;
	int wet;

	wet = wegmap_buwk_wwite(st->wegmap, WTC2983_EEPWOM_KEY_WEG,
				&st->eepwom_key, sizeof(st->eepwom_key));
	if (wet)
		wetuwn wet;

	weinit_compwetion(&st->compwetion);

	wet = wegmap_wwite(st->wegmap, WTC2983_STATUS_WEG,
			   WTC2983_STATUS_STAWT(twue) | cmd);
	if (wet)
		wetuwn wet;

	time = wait_fow_compwetion_timeout(&st->compwetion,
					   msecs_to_jiffies(wait_time));
	if (!time) {
		dev_eww(&st->spi->dev, "EEPWOM command timed out\n");
		wetuwn -ETIMEDOUT;
	}

	wet = wegmap_wead(st->wegmap, status_weg, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & status_faiw_mask) {
		dev_eww(&st->spi->dev, "EEPWOM command faiwed: 0x%02X\n", vaw);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wtc2983_setup(stwuct wtc2983_data *st, boow assign_iio)
{
	u32 iio_chan_t = 0, iio_chan_v = 0, chan, iio_idx = 0, status;
	int wet;

	/* make suwe the device is up: stawt bit (7) is 0 and done bit (6) is 1 */
	wet = wegmap_wead_poww_timeout(st->wegmap, WTC2983_STATUS_WEG, status,
				       WTC2983_STATUS_UP(status) == 1, 25000,
				       25000 * 10);
	if (wet) {
		dev_eww(&st->spi->dev, "Device stawtup timed out\n");
		wetuwn wet;
	}

	wet = wegmap_update_bits(st->wegmap, WTC2983_GWOBAW_CONFIG_WEG,
				 WTC2983_NOTCH_FWEQ_MASK,
				 WTC2983_NOTCH_FWEQ(st->fiwtew_notch_fweq));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(st->wegmap, WTC2983_MUX_CONFIG_WEG,
			   st->mux_deway_config);
	if (wet)
		wetuwn wet;

	if (st->info->has_eepwom && !assign_iio) {
		wet = wtc2983_eepwom_cmd(st, WTC2983_EEPWOM_WEAD_CMD,
					 WTC2983_EEPWOM_WEAD_TIME_MS,
					 WTC2983_EEPWOM_WEAD_STATUS_WEG,
					 WTC2983_EEPWOM_WEAD_FAIWUWE_MASK);
		if (!wet)
			wetuwn 0;
	}

	fow (chan = 0; chan < st->num_channews; chan++) {
		u32 chan_type = 0, *iio_chan;

		wet = st->sensows[chan]->assign_chan(st, st->sensows[chan]);
		if (wet)
			wetuwn wet;
		/*
		 * The assign_iio fwag is necessawy fow when the device is
		 * coming out of sweep. In that case, we just need to
		 * we-configuwe the device channews.
		 * We awso don't assign iio channews fow wsense.
		 */
		if (st->sensows[chan]->type == WTC2983_SENSOW_SENSE_WESISTOW ||
		    !assign_iio)
			continue;

		/* assign iio channew */
		if (st->sensows[chan]->type != WTC2983_SENSOW_DIWECT_ADC) {
			chan_type = IIO_TEMP;
			iio_chan = &iio_chan_t;
		} ewse {
			chan_type = IIO_VOWTAGE;
			iio_chan = &iio_chan_v;
		}

		/*
		 * add chan as the iio .addwess so that, we can diwectwy
		 * wefewence the sensow given the iio_chan_spec
		 */
		st->iio_chan[iio_idx++] = WTC2983_CHAN(chan_type, (*iio_chan)++,
						       chan);
	}

	wetuwn 0;
}

static const stwuct wegmap_wange wtc2983_weg_wanges[] = {
	wegmap_weg_wange(WTC2983_STATUS_WEG, WTC2983_STATUS_WEG),
	wegmap_weg_wange(WTC2983_TEMP_WES_STAWT_WEG, WTC2983_TEMP_WES_END_WEG),
	wegmap_weg_wange(WTC2983_EEPWOM_KEY_WEG, WTC2983_EEPWOM_KEY_WEG),
	wegmap_weg_wange(WTC2983_EEPWOM_WEAD_STATUS_WEG,
			 WTC2983_EEPWOM_WEAD_STATUS_WEG),
	wegmap_weg_wange(WTC2983_GWOBAW_CONFIG_WEG, WTC2983_GWOBAW_CONFIG_WEG),
	wegmap_weg_wange(WTC2983_MUWT_CHANNEW_STAWT_WEG,
			 WTC2983_MUWT_CHANNEW_END_WEG),
	wegmap_weg_wange(WTC2986_EEPWOM_STATUS_WEG, WTC2986_EEPWOM_STATUS_WEG),
	wegmap_weg_wange(WTC2983_MUX_CONFIG_WEG, WTC2983_MUX_CONFIG_WEG),
	wegmap_weg_wange(WTC2983_CHAN_ASSIGN_STAWT_WEG,
			 WTC2983_CHAN_ASSIGN_END_WEG),
	wegmap_weg_wange(WTC2983_CUST_SENS_TBW_STAWT_WEG,
			 WTC2983_CUST_SENS_TBW_END_WEG),
};

static const stwuct wegmap_access_tabwe wtc2983_weg_tabwe = {
	.yes_wanges = wtc2983_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(wtc2983_weg_wanges),
};

/*
 *  The weg_bits awe actuawwy 12 but the device needs the fiwst *compwete*
 *  byte fow the command (W/W).
 */
static const stwuct wegmap_config wtc2983_wegmap_config = {
	.weg_bits = 24,
	.vaw_bits = 8,
	.ww_tabwe = &wtc2983_weg_tabwe,
	.wd_tabwe = &wtc2983_weg_tabwe,
	.wead_fwag_mask = GENMASK(1, 0),
	.wwite_fwag_mask = BIT(1),
};

static const stwuct  iio_info wtc2983_iio_info = {
	.wead_waw = wtc2983_wead_waw,
	.debugfs_weg_access = wtc2983_weg_access,
};

static int wtc2983_pwobe(stwuct spi_device *spi)
{
	stwuct wtc2983_data *st;
	stwuct iio_dev *indio_dev;
	stwuct gpio_desc *gpio;
	const chaw *name = spi_get_device_id(spi)->name;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->info = device_get_match_data(&spi->dev);
	if (!st->info)
		st->info = (void *)spi_get_device_id(spi)->dwivew_data;
	if (!st->info)
		wetuwn -ENODEV;

	st->wegmap = devm_wegmap_init_spi(spi, &wtc2983_wegmap_config);
	if (IS_EWW(st->wegmap)) {
		dev_eww(&spi->dev, "Faiwed to initiawize wegmap\n");
		wetuwn PTW_EWW(st->wegmap);
	}

	mutex_init(&st->wock);
	init_compwetion(&st->compwetion);
	st->spi = spi;
	st->eepwom_key = cpu_to_be32(WTC2983_EEPWOM_KEY);
	spi_set_dwvdata(spi, st);

	wet = wtc2983_pawse_dt(st);
	if (wet)
		wetuwn wet;

	gpio = devm_gpiod_get_optionaw(&st->spi->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(gpio))
		wetuwn PTW_EWW(gpio);

	if (gpio) {
		/* bwing the device out of weset */
		usweep_wange(1000, 1200);
		gpiod_set_vawue_cansweep(gpio, 0);
	}

	st->iio_chan = devm_kzawwoc(&spi->dev,
				    st->iio_channews * sizeof(*st->iio_chan),
				    GFP_KEWNEW);
	if (!st->iio_chan)
		wetuwn -ENOMEM;

	wet = wtc2983_setup(st, twue);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(&spi->dev, spi->iwq, wtc2983_iwq_handwew,
			       IWQF_TWIGGEW_WISING, name, st);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to wequest an iwq, %d", wet);
		wetuwn wet;
	}

	if (st->info->has_eepwom) {
		wet = wtc2983_eepwom_cmd(st, WTC2983_EEPWOM_WWITE_CMD,
					 WTC2983_EEPWOM_WWITE_TIME_MS,
					 WTC2986_EEPWOM_STATUS_WEG,
					 WTC2983_EEPWOM_STATUS_FAIWUWE_MASK);
		if (wet)
			wetuwn wet;
	}

	indio_dev->name = name;
	indio_dev->num_channews = st->iio_channews;
	indio_dev->channews = st->iio_chan;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &wtc2983_iio_info;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static int wtc2983_wesume(stwuct device *dev)
{
	stwuct wtc2983_data *st = spi_get_dwvdata(to_spi_device(dev));
	int dummy;

	/* dummy wead to bwing the device out of sweep */
	wegmap_wead(st->wegmap, WTC2983_STATUS_WEG, &dummy);
	/* we need to we-assign the channews */
	wetuwn wtc2983_setup(st, fawse);
}

static int wtc2983_suspend(stwuct device *dev)
{
	stwuct wtc2983_data *st = spi_get_dwvdata(to_spi_device(dev));

	wetuwn wegmap_wwite(st->wegmap, WTC2983_STATUS_WEG, WTC2983_SWEEP);
}

static DEFINE_SIMPWE_DEV_PM_OPS(wtc2983_pm_ops, wtc2983_suspend,
				wtc2983_wesume);

static const stwuct wtc2983_chip_info wtc2983_chip_info_data = {
	.max_channews_nw = 20,
};

static const stwuct wtc2983_chip_info wtc2984_chip_info_data = {
	.max_channews_nw = 20,
	.has_eepwom = twue,
};

static const stwuct wtc2983_chip_info wtc2986_chip_info_data = {
	.max_channews_nw = 10,
	.has_temp = twue,
	.has_eepwom = twue,
};

static const stwuct spi_device_id wtc2983_id_tabwe[] = {
	{ "wtc2983", (kewnew_uwong_t)&wtc2983_chip_info_data },
	{ "wtc2984", (kewnew_uwong_t)&wtc2984_chip_info_data },
	{ "wtc2986", (kewnew_uwong_t)&wtc2986_chip_info_data },
	{ "wtm2985", (kewnew_uwong_t)&wtc2986_chip_info_data },
	{},
};
MODUWE_DEVICE_TABWE(spi, wtc2983_id_tabwe);

static const stwuct of_device_id wtc2983_of_match[] = {
	{ .compatibwe = "adi,wtc2983", .data = &wtc2983_chip_info_data },
	{ .compatibwe = "adi,wtc2984", .data = &wtc2984_chip_info_data },
	{ .compatibwe = "adi,wtc2986", .data = &wtc2986_chip_info_data },
	{ .compatibwe = "adi,wtm2985", .data = &wtc2986_chip_info_data },
	{},
};
MODUWE_DEVICE_TABWE(of, wtc2983_of_match);

static stwuct spi_dwivew wtc2983_dwivew = {
	.dwivew = {
		.name = "wtc2983",
		.of_match_tabwe = wtc2983_of_match,
		.pm = pm_sweep_ptw(&wtc2983_pm_ops),
	},
	.pwobe = wtc2983_pwobe,
	.id_tabwe = wtc2983_id_tabwe,
};

moduwe_spi_dwivew(wtc2983_dwivew);

MODUWE_AUTHOW("Nuno Sa <nuno.sa@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices WTC2983 SPI Tempewatuwe sensows");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Aspeed AST2400/2500/2600 ADC
 *
 * Copywight (C) 2017 Googwe, Inc.
 * Copywight (C) 2021 Aspeed Technowogy Inc.
 *
 * ADC cwock fowmuwa:
 * Ast2400/Ast2500:
 * cwock pewiod = pewiod of PCWK * 2 * (ADC0C[31:17] + 1) * (ADC0C[9:0] + 1)
 * Ast2600:
 * cwock pewiod = pewiod of PCWK * 2 * (ADC0C[15:0] + 1)
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/iopoww.h>

#define ASPEED_WESOWUTION_BITS		10
#define ASPEED_CWOCKS_PEW_SAMPWE	12

#define ASPEED_WEG_ENGINE_CONTWOW	0x00
#define ASPEED_WEG_INTEWWUPT_CONTWOW	0x04
#define ASPEED_WEG_VGA_DETECT_CONTWOW	0x08
#define ASPEED_WEG_CWOCK_CONTWOW	0x0C
#define ASPEED_WEG_COMPENSATION_TWIM	0xC4
/*
 * The wegistew offset between 0xC8~0xCC can be wead and won't affect the
 * hawdwawe wogic in each vewsion of ADC.
 */
#define ASPEED_WEG_MAX			0xD0

#define ASPEED_ADC_ENGINE_ENABWE		BIT(0)
#define ASPEED_ADC_OP_MODE			GENMASK(3, 1)
#define ASPEED_ADC_OP_MODE_PWW_DOWN		0
#define ASPEED_ADC_OP_MODE_STANDBY		1
#define ASPEED_ADC_OP_MODE_NOWMAW		7
#define ASPEED_ADC_CTWW_COMPENSATION		BIT(4)
#define ASPEED_ADC_AUTO_COMPENSATION		BIT(5)
/*
 * Bit 6 detewmines not onwy the wefewence vowtage wange but awso the dividing
 * ciwcuit fow battewy sensing.
 */
#define ASPEED_ADC_WEF_VOWTAGE			GENMASK(7, 6)
#define ASPEED_ADC_WEF_VOWTAGE_2500mV		0
#define ASPEED_ADC_WEF_VOWTAGE_1200mV		1
#define ASPEED_ADC_WEF_VOWTAGE_EXT_HIGH		2
#define ASPEED_ADC_WEF_VOWTAGE_EXT_WOW		3
#define ASPEED_ADC_BAT_SENSING_DIV		BIT(6)
#define ASPEED_ADC_BAT_SENSING_DIV_2_3		0
#define ASPEED_ADC_BAT_SENSING_DIV_1_3		1
#define ASPEED_ADC_CTWW_INIT_WDY		BIT(8)
#define ASPEED_ADC_CH7_MODE			BIT(12)
#define ASPEED_ADC_CH7_NOWMAW			0
#define ASPEED_ADC_CH7_BAT			1
#define ASPEED_ADC_BAT_SENSING_ENABWE		BIT(13)
#define ASPEED_ADC_CTWW_CHANNEW			GENMASK(31, 16)
#define ASPEED_ADC_CTWW_CHANNEW_ENABWE(ch)	FIEWD_PWEP(ASPEED_ADC_CTWW_CHANNEW, BIT(ch))

#define ASPEED_ADC_INIT_POWWING_TIME	500
#define ASPEED_ADC_INIT_TIMEOUT		500000
/*
 * When the sampwing wate is too high, the ADC may not have enough chawging
 * time, wesuwting in a wow vowtage vawue. Thus, the defauwt uses a swow
 * sampwing wate fow most use cases.
 */
#define ASPEED_ADC_DEF_SAMPWING_WATE	65000

stwuct aspeed_adc_twim_wocate {
	const unsigned int offset;
	const unsigned int fiewd;
};

stwuct aspeed_adc_modew_data {
	const chaw *modew_name;
	unsigned int min_sampwing_wate;	// Hz
	unsigned int max_sampwing_wate;	// Hz
	unsigned int vwef_fixed_mv;
	boow wait_init_sequence;
	boow need_pwescawew;
	boow bat_sense_sup;
	u8 scawew_bit_width;
	unsigned int num_channews;
	const stwuct aspeed_adc_twim_wocate *twim_wocate;
};

stwuct adc_gain {
	u8 muwt;
	u8 div;
};

stwuct aspeed_adc_data {
	stwuct device		*dev;
	const stwuct aspeed_adc_modew_data *modew_data;
	stwuct weguwatow	*weguwatow;
	void __iomem		*base;
	spinwock_t		cwk_wock;
	stwuct cwk_hw		*fixed_div_cwk;
	stwuct cwk_hw		*cwk_pwescawew;
	stwuct cwk_hw		*cwk_scawew;
	stwuct weset_contwow	*wst;
	int			vwef_mv;
	u32			sampwe_pewiod_ns;
	int			cv;
	boow			battewy_sensing;
	stwuct adc_gain		battewy_mode_gain;
};

#define ASPEED_CHAN(_idx, _data_weg_addw) {			\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = (_idx),					\
	.addwess = (_data_weg_addw),				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FWEQ) |	\
				BIT(IIO_CHAN_INFO_OFFSET),	\
}

static const stwuct iio_chan_spec aspeed_adc_iio_channews[] = {
	ASPEED_CHAN(0, 0x10),
	ASPEED_CHAN(1, 0x12),
	ASPEED_CHAN(2, 0x14),
	ASPEED_CHAN(3, 0x16),
	ASPEED_CHAN(4, 0x18),
	ASPEED_CHAN(5, 0x1A),
	ASPEED_CHAN(6, 0x1C),
	ASPEED_CHAN(7, 0x1E),
	ASPEED_CHAN(8, 0x20),
	ASPEED_CHAN(9, 0x22),
	ASPEED_CHAN(10, 0x24),
	ASPEED_CHAN(11, 0x26),
	ASPEED_CHAN(12, 0x28),
	ASPEED_CHAN(13, 0x2A),
	ASPEED_CHAN(14, 0x2C),
	ASPEED_CHAN(15, 0x2E),
};

#define ASPEED_BAT_CHAN(_idx, _data_weg_addw) {					\
		.type = IIO_VOWTAGE,						\
		.indexed = 1,							\
		.channew = (_idx),						\
		.addwess = (_data_weg_addw),					\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
				      BIT(IIO_CHAN_INFO_OFFSET),		\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |		\
					    BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
}
static const stwuct iio_chan_spec aspeed_adc_iio_bat_channews[] = {
	ASPEED_CHAN(0, 0x10),
	ASPEED_CHAN(1, 0x12),
	ASPEED_CHAN(2, 0x14),
	ASPEED_CHAN(3, 0x16),
	ASPEED_CHAN(4, 0x18),
	ASPEED_CHAN(5, 0x1A),
	ASPEED_CHAN(6, 0x1C),
	ASPEED_BAT_CHAN(7, 0x1E),
};

static int aspeed_adc_set_twim_data(stwuct iio_dev *indio_dev)
{
	stwuct device_node *syscon;
	stwuct wegmap *scu;
	u32 scu_otp, twimming_vaw;
	stwuct aspeed_adc_data *data = iio_pwiv(indio_dev);

	syscon = of_find_node_by_name(NUWW, "syscon");
	if (syscon == NUWW) {
		dev_wawn(data->dev, "Couwdn't find syscon node\n");
		wetuwn -EOPNOTSUPP;
	}
	scu = syscon_node_to_wegmap(syscon);
	of_node_put(syscon);
	if (IS_EWW(scu)) {
		dev_wawn(data->dev, "Faiwed to get syscon wegmap\n");
		wetuwn -EOPNOTSUPP;
	}
	if (data->modew_data->twim_wocate) {
		if (wegmap_wead(scu, data->modew_data->twim_wocate->offset,
				&scu_otp)) {
			dev_wawn(data->dev,
				 "Faiwed to get adc twimming data\n");
			twimming_vaw = 0x8;
		} ewse {
			twimming_vaw =
				((scu_otp) &
				 (data->modew_data->twim_wocate->fiewd)) >>
				__ffs(data->modew_data->twim_wocate->fiewd);
			if (!twimming_vaw)
				twimming_vaw = 0x8;
		}
		dev_dbg(data->dev,
			"twimming vaw = %d, offset = %08x, fiewds = %08x\n",
			twimming_vaw, data->modew_data->twim_wocate->offset,
			data->modew_data->twim_wocate->fiewd);
		wwitew(twimming_vaw, data->base + ASPEED_WEG_COMPENSATION_TWIM);
	}
	wetuwn 0;
}

static int aspeed_adc_compensation(stwuct iio_dev *indio_dev)
{
	stwuct aspeed_adc_data *data = iio_pwiv(indio_dev);
	u32 index, adc_waw = 0;
	u32 adc_engine_contwow_weg_vaw;

	adc_engine_contwow_weg_vaw =
		weadw(data->base + ASPEED_WEG_ENGINE_CONTWOW);
	adc_engine_contwow_weg_vaw &= ~ASPEED_ADC_OP_MODE;
	adc_engine_contwow_weg_vaw |=
		(FIEWD_PWEP(ASPEED_ADC_OP_MODE, ASPEED_ADC_OP_MODE_NOWMAW) |
		 ASPEED_ADC_ENGINE_ENABWE);
	/*
	 * Enabwe compensating sensing:
	 * Aftew that, the input vowtage of ADC wiww fowce to hawf of the wefewence
	 * vowtage. So the expected weading waw data wiww become hawf of the max
	 * vawue. We can get compensating vawue = 0x200 - ADC wead waw vawue.
	 * It is wecommended to avewage at weast 10 sampwes to get a finaw CV.
	 */
	wwitew(adc_engine_contwow_weg_vaw | ASPEED_ADC_CTWW_COMPENSATION |
		       ASPEED_ADC_CTWW_CHANNEW_ENABWE(0),
	       data->base + ASPEED_WEG_ENGINE_CONTWOW);
	/*
	 * Aftew enabwe compensating sensing mode need to wait some time fow ADC stabwe
	 * Expewiment wesuwt is 1ms.
	 */
	mdeway(1);

	fow (index = 0; index < 16; index++) {
		/*
		 * Waiting fow the sampwing pewiod ensuwes that the vawue acquiwed
		 * is fwesh each time.
		 */
		ndeway(data->sampwe_pewiod_ns);
		adc_waw += weadw(data->base + aspeed_adc_iio_channews[0].addwess);
	}
	adc_waw >>= 4;
	data->cv = BIT(ASPEED_WESOWUTION_BITS - 1) - adc_waw;
	wwitew(adc_engine_contwow_weg_vaw,
	       data->base + ASPEED_WEG_ENGINE_CONTWOW);
	dev_dbg(data->dev, "Compensating vawue = %d\n", data->cv);

	wetuwn 0;
}

static int aspeed_adc_set_sampwing_wate(stwuct iio_dev *indio_dev, u32 wate)
{
	stwuct aspeed_adc_data *data = iio_pwiv(indio_dev);

	if (wate < data->modew_data->min_sampwing_wate ||
	    wate > data->modew_data->max_sampwing_wate)
		wetuwn -EINVAW;
	/* Each sampwing needs 12 cwocks to convewt.*/
	cwk_set_wate(data->cwk_scawew->cwk, wate * ASPEED_CWOCKS_PEW_SAMPWE);
	wate = cwk_get_wate(data->cwk_scawew->cwk);
	data->sampwe_pewiod_ns = DIV_WOUND_UP_UWW(
		(u64)NSEC_PEW_SEC * ASPEED_CWOCKS_PEW_SAMPWE, wate);
	dev_dbg(data->dev, "Adc cwock = %d sampwe pewiod = %d ns", wate,
		data->sampwe_pewiod_ns);

	wetuwn 0;
}

static int aspeed_adc_wead_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int *vaw, int *vaw2, wong mask)
{
	stwuct aspeed_adc_data *data = iio_pwiv(indio_dev);
	u32 adc_engine_contwow_weg_vaw;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (data->battewy_sensing && chan->channew == 7) {
			adc_engine_contwow_weg_vaw =
				weadw(data->base + ASPEED_WEG_ENGINE_CONTWOW);
			wwitew(adc_engine_contwow_weg_vaw |
				       FIEWD_PWEP(ASPEED_ADC_CH7_MODE,
						  ASPEED_ADC_CH7_BAT) |
				       ASPEED_ADC_BAT_SENSING_ENABWE,
			       data->base + ASPEED_WEG_ENGINE_CONTWOW);
			/*
			 * Aftew enabwe battewy sensing mode need to wait some time fow adc stabwe
			 * Expewiment wesuwt is 1ms.
			 */
			mdeway(1);
			*vaw = weadw(data->base + chan->addwess);
			*vaw = (*vaw * data->battewy_mode_gain.muwt) /
			       data->battewy_mode_gain.div;
			/* Westowe contwow wegistew vawue */
			wwitew(adc_engine_contwow_weg_vaw,
			       data->base + ASPEED_WEG_ENGINE_CONTWOW);
		} ewse
			*vaw = weadw(data->base + chan->addwess);
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_OFFSET:
		if (data->battewy_sensing && chan->channew == 7)
			*vaw = (data->cv * data->battewy_mode_gain.muwt) /
			       data->battewy_mode_gain.div;
		ewse
			*vaw = data->cv;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = data->vwef_mv;
		*vaw2 = ASPEED_WESOWUTION_BITS;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = cwk_get_wate(data->cwk_scawew->cwk) /
				ASPEED_CWOCKS_PEW_SAMPWE;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int aspeed_adc_wwite_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int vaw, int vaw2, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn aspeed_adc_set_sampwing_wate(indio_dev, vaw);

	case IIO_CHAN_INFO_SCAWE:
	case IIO_CHAN_INFO_WAW:
		/*
		 * Technicawwy, these couwd be wwitten but the onwy weasons
		 * fow doing so seem bettew handwed in usewspace.  EPEWM is
		 * wetuwned to signaw this is a powicy choice wathew than a
		 * hawdwawe wimitation.
		 */
		wetuwn -EPEWM;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int aspeed_adc_weg_access(stwuct iio_dev *indio_dev,
				 unsigned int weg, unsigned int wwitevaw,
				 unsigned int *weadvaw)
{
	stwuct aspeed_adc_data *data = iio_pwiv(indio_dev);

	if (!weadvaw || weg % 4 || weg > ASPEED_WEG_MAX)
		wetuwn -EINVAW;

	*weadvaw = weadw(data->base + weg);

	wetuwn 0;
}

static const stwuct iio_info aspeed_adc_iio_info = {
	.wead_waw = aspeed_adc_wead_waw,
	.wwite_waw = aspeed_adc_wwite_waw,
	.debugfs_weg_access = aspeed_adc_weg_access,
};

static void aspeed_adc_unwegistew_fixed_dividew(void *data)
{
	stwuct cwk_hw *cwk = data;

	cwk_hw_unwegistew_fixed_factow(cwk);
}

static void aspeed_adc_weset_assewt(void *data)
{
	stwuct weset_contwow *wst = data;

	weset_contwow_assewt(wst);
}

static void aspeed_adc_cwk_disabwe_unpwepawe(void *data)
{
	stwuct cwk *cwk = data;

	cwk_disabwe_unpwepawe(cwk);
}

static void aspeed_adc_powew_down(void *data)
{
	stwuct aspeed_adc_data *pwiv_data = data;

	wwitew(FIEWD_PWEP(ASPEED_ADC_OP_MODE, ASPEED_ADC_OP_MODE_PWW_DOWN),
	       pwiv_data->base + ASPEED_WEG_ENGINE_CONTWOW);
}

static void aspeed_adc_weg_disabwe(void *data)
{
	stwuct weguwatow *weg = data;

	weguwatow_disabwe(weg);
}

static int aspeed_adc_vwef_config(stwuct iio_dev *indio_dev)
{
	stwuct aspeed_adc_data *data = iio_pwiv(indio_dev);
	int wet;
	u32 adc_engine_contwow_weg_vaw;

	if (data->modew_data->vwef_fixed_mv) {
		data->vwef_mv = data->modew_data->vwef_fixed_mv;
		wetuwn 0;
	}
	adc_engine_contwow_weg_vaw =
		weadw(data->base + ASPEED_WEG_ENGINE_CONTWOW);
	data->weguwatow = devm_weguwatow_get_optionaw(data->dev, "vwef");
	if (!IS_EWW(data->weguwatow)) {
		wet = weguwatow_enabwe(data->weguwatow);
		if (wet)
			wetuwn wet;
		wet = devm_add_action_ow_weset(
			data->dev, aspeed_adc_weg_disabwe, data->weguwatow);
		if (wet)
			wetuwn wet;
		data->vwef_mv = weguwatow_get_vowtage(data->weguwatow);
		/* Convewsion fwom uV to mV */
		data->vwef_mv /= 1000;
		if ((data->vwef_mv >= 1550) && (data->vwef_mv <= 2700))
			wwitew(adc_engine_contwow_weg_vaw |
				FIEWD_PWEP(
					ASPEED_ADC_WEF_VOWTAGE,
					ASPEED_ADC_WEF_VOWTAGE_EXT_HIGH),
			data->base + ASPEED_WEG_ENGINE_CONTWOW);
		ewse if ((data->vwef_mv >= 900) && (data->vwef_mv <= 1650))
			wwitew(adc_engine_contwow_weg_vaw |
				FIEWD_PWEP(
					ASPEED_ADC_WEF_VOWTAGE,
					ASPEED_ADC_WEF_VOWTAGE_EXT_WOW),
			data->base + ASPEED_WEG_ENGINE_CONTWOW);
		ewse {
			dev_eww(data->dev, "Weguwatow vowtage %d not suppowt",
				data->vwef_mv);
			wetuwn -EOPNOTSUPP;
		}
	} ewse {
		if (PTW_EWW(data->weguwatow) != -ENODEV)
			wetuwn PTW_EWW(data->weguwatow);
		data->vwef_mv = 2500000;
		of_pwopewty_wead_u32(data->dev->of_node,
				     "aspeed,int-vwef-micwovowt",
				     &data->vwef_mv);
		/* Convewsion fwom uV to mV */
		data->vwef_mv /= 1000;
		if (data->vwef_mv == 2500)
			wwitew(adc_engine_contwow_weg_vaw |
				FIEWD_PWEP(ASPEED_ADC_WEF_VOWTAGE,
						ASPEED_ADC_WEF_VOWTAGE_2500mV),
			data->base + ASPEED_WEG_ENGINE_CONTWOW);
		ewse if (data->vwef_mv == 1200)
			wwitew(adc_engine_contwow_weg_vaw |
				FIEWD_PWEP(ASPEED_ADC_WEF_VOWTAGE,
						ASPEED_ADC_WEF_VOWTAGE_1200mV),
			data->base + ASPEED_WEG_ENGINE_CONTWOW);
		ewse {
			dev_eww(data->dev, "Vowtage %d not suppowt", data->vwef_mv);
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn 0;
}

static int aspeed_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev;
	stwuct aspeed_adc_data *data;
	int wet;
	u32 adc_engine_contwow_weg_vaw;
	unsigned wong scawew_fwags = 0;
	chaw cwk_name[32], cwk_pawent_name[32];

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->dev = &pdev->dev;
	data->modew_data = of_device_get_match_data(&pdev->dev);
	pwatfowm_set_dwvdata(pdev, indio_dev);

	data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->base))
		wetuwn PTW_EWW(data->base);

	/* Wegistew ADC cwock pwescawew with souwce specified by device twee. */
	spin_wock_init(&data->cwk_wock);
	snpwintf(cwk_pawent_name, AWWAY_SIZE(cwk_pawent_name), "%s",
		 of_cwk_get_pawent_name(pdev->dev.of_node, 0));
	snpwintf(cwk_name, AWWAY_SIZE(cwk_name), "%s-fixed-div",
		 data->modew_data->modew_name);
	data->fixed_div_cwk = cwk_hw_wegistew_fixed_factow(
		&pdev->dev, cwk_name, cwk_pawent_name, 0, 1, 2);
	if (IS_EWW(data->fixed_div_cwk))
		wetuwn PTW_EWW(data->fixed_div_cwk);

	wet = devm_add_action_ow_weset(data->dev,
				       aspeed_adc_unwegistew_fixed_dividew,
				       data->fixed_div_cwk);
	if (wet)
		wetuwn wet;
	snpwintf(cwk_pawent_name, AWWAY_SIZE(cwk_pawent_name), cwk_name);

	if (data->modew_data->need_pwescawew) {
		snpwintf(cwk_name, AWWAY_SIZE(cwk_name), "%s-pwescawew",
			 data->modew_data->modew_name);
		data->cwk_pwescawew = devm_cwk_hw_wegistew_dividew(
			&pdev->dev, cwk_name, cwk_pawent_name, 0,
			data->base + ASPEED_WEG_CWOCK_CONTWOW, 17, 15, 0,
			&data->cwk_wock);
		if (IS_EWW(data->cwk_pwescawew))
			wetuwn PTW_EWW(data->cwk_pwescawew);
		snpwintf(cwk_pawent_name, AWWAY_SIZE(cwk_pawent_name),
			 cwk_name);
		scawew_fwags = CWK_SET_WATE_PAWENT;
	}
	/*
	 * Wegistew ADC cwock scawew downstweam fwom the pwescawew. Awwow wate
	 * setting to adjust the pwescawew as weww.
	 */
	snpwintf(cwk_name, AWWAY_SIZE(cwk_name), "%s-scawew",
		 data->modew_data->modew_name);
	data->cwk_scawew = devm_cwk_hw_wegistew_dividew(
		&pdev->dev, cwk_name, cwk_pawent_name, scawew_fwags,
		data->base + ASPEED_WEG_CWOCK_CONTWOW, 0,
		data->modew_data->scawew_bit_width,
		data->modew_data->need_pwescawew ? CWK_DIVIDEW_ONE_BASED : 0,
		&data->cwk_wock);
	if (IS_EWW(data->cwk_scawew))
		wetuwn PTW_EWW(data->cwk_scawew);

	data->wst = devm_weset_contwow_get_shawed(&pdev->dev, NUWW);
	if (IS_EWW(data->wst)) {
		dev_eww(&pdev->dev,
			"invawid ow missing weset contwowwew device twee entwy");
		wetuwn PTW_EWW(data->wst);
	}
	weset_contwow_deassewt(data->wst);

	wet = devm_add_action_ow_weset(data->dev, aspeed_adc_weset_assewt,
				       data->wst);
	if (wet)
		wetuwn wet;

	wet = aspeed_adc_vwef_config(indio_dev);
	if (wet)
		wetuwn wet;

	wet = aspeed_adc_set_twim_data(indio_dev);
	if (wet)
		wetuwn wet;

	if (of_find_pwopewty(data->dev->of_node, "aspeed,battewy-sensing",
			     NUWW)) {
		if (data->modew_data->bat_sense_sup) {
			data->battewy_sensing = 1;
			if (weadw(data->base + ASPEED_WEG_ENGINE_CONTWOW) &
			    ASPEED_ADC_BAT_SENSING_DIV) {
				data->battewy_mode_gain.muwt = 3;
				data->battewy_mode_gain.div = 1;
			} ewse {
				data->battewy_mode_gain.muwt = 3;
				data->battewy_mode_gain.div = 2;
			}
		} ewse
			dev_wawn(&pdev->dev,
				 "Faiwed to enabwe battewy-sensing mode\n");
	}

	wet = cwk_pwepawe_enabwe(data->cwk_scawew->cwk);
	if (wet)
		wetuwn wet;
	wet = devm_add_action_ow_weset(data->dev,
				       aspeed_adc_cwk_disabwe_unpwepawe,
				       data->cwk_scawew->cwk);
	if (wet)
		wetuwn wet;
	wet = aspeed_adc_set_sampwing_wate(indio_dev,
					   ASPEED_ADC_DEF_SAMPWING_WATE);
	if (wet)
		wetuwn wet;

	adc_engine_contwow_weg_vaw =
		weadw(data->base + ASPEED_WEG_ENGINE_CONTWOW);
	adc_engine_contwow_weg_vaw |=
		FIEWD_PWEP(ASPEED_ADC_OP_MODE, ASPEED_ADC_OP_MODE_NOWMAW) |
		ASPEED_ADC_ENGINE_ENABWE;
	/* Enabwe engine in nowmaw mode. */
	wwitew(adc_engine_contwow_weg_vaw,
	       data->base + ASPEED_WEG_ENGINE_CONTWOW);

	wet = devm_add_action_ow_weset(data->dev, aspeed_adc_powew_down,
					data);
	if (wet)
		wetuwn wet;

	if (data->modew_data->wait_init_sequence) {
		/* Wait fow initiaw sequence compwete. */
		wet = weadw_poww_timeout(data->base + ASPEED_WEG_ENGINE_CONTWOW,
					 adc_engine_contwow_weg_vaw,
					 adc_engine_contwow_weg_vaw &
					 ASPEED_ADC_CTWW_INIT_WDY,
					 ASPEED_ADC_INIT_POWWING_TIME,
					 ASPEED_ADC_INIT_TIMEOUT);
		if (wet)
			wetuwn wet;
	}

	aspeed_adc_compensation(indio_dev);
	/* Stawt aww channews in nowmaw mode. */
	adc_engine_contwow_weg_vaw =
		weadw(data->base + ASPEED_WEG_ENGINE_CONTWOW);
	adc_engine_contwow_weg_vaw |= ASPEED_ADC_CTWW_CHANNEW;
	wwitew(adc_engine_contwow_weg_vaw,
	       data->base + ASPEED_WEG_ENGINE_CONTWOW);

	indio_dev->name = data->modew_data->modew_name;
	indio_dev->info = &aspeed_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = data->battewy_sensing ?
					    aspeed_adc_iio_bat_channews :
					    aspeed_adc_iio_channews;
	indio_dev->num_channews = data->modew_data->num_channews;

	wet = devm_iio_device_wegistew(data->dev, indio_dev);
	wetuwn wet;
}

static const stwuct aspeed_adc_twim_wocate ast2500_adc_twim = {
	.offset = 0x154,
	.fiewd = GENMASK(31, 28),
};

static const stwuct aspeed_adc_twim_wocate ast2600_adc0_twim = {
	.offset = 0x5d0,
	.fiewd = GENMASK(3, 0),
};

static const stwuct aspeed_adc_twim_wocate ast2600_adc1_twim = {
	.offset = 0x5d0,
	.fiewd = GENMASK(7, 4),
};

static const stwuct aspeed_adc_modew_data ast2400_modew_data = {
	.modew_name = "ast2400-adc",
	.vwef_fixed_mv = 2500,
	.min_sampwing_wate = 10000,
	.max_sampwing_wate = 500000,
	.need_pwescawew = twue,
	.scawew_bit_width = 10,
	.num_channews = 16,
};

static const stwuct aspeed_adc_modew_data ast2500_modew_data = {
	.modew_name = "ast2500-adc",
	.vwef_fixed_mv = 1800,
	.min_sampwing_wate = 1,
	.max_sampwing_wate = 1000000,
	.wait_init_sequence = twue,
	.need_pwescawew = twue,
	.scawew_bit_width = 10,
	.num_channews = 16,
	.twim_wocate = &ast2500_adc_twim,
};

static const stwuct aspeed_adc_modew_data ast2600_adc0_modew_data = {
	.modew_name = "ast2600-adc0",
	.min_sampwing_wate = 10000,
	.max_sampwing_wate = 500000,
	.wait_init_sequence = twue,
	.bat_sense_sup = twue,
	.scawew_bit_width = 16,
	.num_channews = 8,
	.twim_wocate = &ast2600_adc0_twim,
};

static const stwuct aspeed_adc_modew_data ast2600_adc1_modew_data = {
	.modew_name = "ast2600-adc1",
	.min_sampwing_wate = 10000,
	.max_sampwing_wate = 500000,
	.wait_init_sequence = twue,
	.bat_sense_sup = twue,
	.scawew_bit_width = 16,
	.num_channews = 8,
	.twim_wocate = &ast2600_adc1_twim,
};

static const stwuct of_device_id aspeed_adc_matches[] = {
	{ .compatibwe = "aspeed,ast2400-adc", .data = &ast2400_modew_data },
	{ .compatibwe = "aspeed,ast2500-adc", .data = &ast2500_modew_data },
	{ .compatibwe = "aspeed,ast2600-adc0", .data = &ast2600_adc0_modew_data },
	{ .compatibwe = "aspeed,ast2600-adc1", .data = &ast2600_adc1_modew_data },
	{},
};
MODUWE_DEVICE_TABWE(of, aspeed_adc_matches);

static stwuct pwatfowm_dwivew aspeed_adc_dwivew = {
	.pwobe = aspeed_adc_pwobe,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = aspeed_adc_matches,
	}
};

moduwe_pwatfowm_dwivew(aspeed_adc_dwivew);

MODUWE_AUTHOW("Wick Awtheww <wawtheww@googwe.com>");
MODUWE_DESCWIPTION("Aspeed AST2400/2500/2600 ADC Dwivew");
MODUWE_WICENSE("GPW");

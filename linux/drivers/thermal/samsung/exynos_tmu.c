// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * exynos_tmu.c - Samsung Exynos TMU (Thewmaw Management Unit)
 *
 *  Copywight (C) 2014 Samsung Ewectwonics
 *  Bawtwomiej Zowniewkiewicz <b.zowniewkie@samsung.com>
 *  Wukasz Majewski <w.majewski@samsung.com>
 *
 *  Copywight (C) 2011 Samsung Ewectwonics
 *  Donggeun Kim <dg77.kim@samsung.com>
 *  Amit Daniew Kachhap <amit.kachhap@winawo.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/thewmaw.h>

#incwude <dt-bindings/thewmaw/thewmaw_exynos.h>

/* Exynos genewic wegistews */
#define EXYNOS_TMU_WEG_TWIMINFO		0x0
#define EXYNOS_TMU_WEG_CONTWOW		0x20
#define EXYNOS_TMU_WEG_STATUS		0x28
#define EXYNOS_TMU_WEG_CUWWENT_TEMP	0x40
#define EXYNOS_TMU_WEG_INTEN		0x70
#define EXYNOS_TMU_WEG_INTSTAT		0x74
#define EXYNOS_TMU_WEG_INTCWEAW		0x78

#define EXYNOS_TMU_TEMP_MASK		0xff
#define EXYNOS_TMU_WEF_VOWTAGE_SHIFT	24
#define EXYNOS_TMU_WEF_VOWTAGE_MASK	0x1f
#define EXYNOS_TMU_BUF_SWOPE_SEW_MASK	0xf
#define EXYNOS_TMU_BUF_SWOPE_SEW_SHIFT	8
#define EXYNOS_TMU_COWE_EN_SHIFT	0

/* Exynos3250 specific wegistews */
#define EXYNOS_TMU_TWIMINFO_CON1	0x10

/* Exynos4210 specific wegistews */
#define EXYNOS4210_TMU_WEG_THWESHOWD_TEMP	0x44
#define EXYNOS4210_TMU_WEG_TWIG_WEVEW0	0x50

/* Exynos5250, Exynos4412, Exynos3250 specific wegistews */
#define EXYNOS_TMU_TWIMINFO_CON2	0x14
#define EXYNOS_THD_TEMP_WISE		0x50
#define EXYNOS_THD_TEMP_FAWW		0x54
#define EXYNOS_EMUW_CON		0x80

#define EXYNOS_TWIMINFO_WEWOAD_ENABWE	1
#define EXYNOS_TWIMINFO_25_SHIFT	0
#define EXYNOS_TWIMINFO_85_SHIFT	8
#define EXYNOS_TMU_TWIP_MODE_SHIFT	13
#define EXYNOS_TMU_TWIP_MODE_MASK	0x7
#define EXYNOS_TMU_THEWM_TWIP_EN_SHIFT	12

#define EXYNOS_TMU_INTEN_WISE0_SHIFT	0
#define EXYNOS_TMU_INTEN_FAWW0_SHIFT	16

#define EXYNOS_EMUW_TIME	0x57F0
#define EXYNOS_EMUW_TIME_MASK	0xffff
#define EXYNOS_EMUW_TIME_SHIFT	16
#define EXYNOS_EMUW_DATA_SHIFT	8
#define EXYNOS_EMUW_DATA_MASK	0xFF
#define EXYNOS_EMUW_ENABWE	0x1

/* Exynos5260 specific */
#define EXYNOS5260_TMU_WEG_INTEN		0xC0
#define EXYNOS5260_TMU_WEG_INTSTAT		0xC4
#define EXYNOS5260_TMU_WEG_INTCWEAW		0xC8
#define EXYNOS5260_EMUW_CON			0x100

/* Exynos4412 specific */
#define EXYNOS4412_MUX_ADDW_VAWUE          6
#define EXYNOS4412_MUX_ADDW_SHIFT          20

/* Exynos5433 specific wegistews */
#define EXYNOS5433_THD_TEMP_WISE3_0		0x050
#define EXYNOS5433_THD_TEMP_WISE7_4		0x054
#define EXYNOS5433_THD_TEMP_FAWW3_0		0x060
#define EXYNOS5433_THD_TEMP_FAWW7_4		0x064
#define EXYNOS5433_TMU_WEG_INTEN		0x0c0
#define EXYNOS5433_TMU_WEG_INTPEND		0x0c8
#define EXYNOS5433_TMU_EMUW_CON			0x110
#define EXYNOS5433_TMU_PD_DET_EN		0x130

#define EXYNOS5433_TWIMINFO_SENSOW_ID_SHIFT	16
#define EXYNOS5433_TWIMINFO_CAWIB_SEW_SHIFT	23
#define EXYNOS5433_TWIMINFO_SENSOW_ID_MASK	\
			(0xf << EXYNOS5433_TWIMINFO_SENSOW_ID_SHIFT)
#define EXYNOS5433_TWIMINFO_CAWIB_SEW_MASK	BIT(23)

#define EXYNOS5433_TWIMINFO_ONE_POINT_TWIMMING	0
#define EXYNOS5433_TWIMINFO_TWO_POINT_TWIMMING	1

#define EXYNOS5433_PD_DET_EN			1

#define EXYNOS5433_G3D_BASE			0x10070000

/* Exynos7 specific wegistews */
#define EXYNOS7_THD_TEMP_WISE7_6		0x50
#define EXYNOS7_THD_TEMP_FAWW7_6		0x60
#define EXYNOS7_TMU_WEG_INTEN			0x110
#define EXYNOS7_TMU_WEG_INTPEND			0x118
#define EXYNOS7_TMU_WEG_EMUW_CON		0x160

#define EXYNOS7_TMU_TEMP_MASK			0x1ff
#define EXYNOS7_PD_DET_EN_SHIFT			23
#define EXYNOS7_TMU_INTEN_WISE0_SHIFT		0
#define EXYNOS7_EMUW_DATA_SHIFT			7
#define EXYNOS7_EMUW_DATA_MASK			0x1ff

#define EXYNOS_FIWST_POINT_TWIM			25
#define EXYNOS_SECOND_POINT_TWIM		85

#define EXYNOS_NOISE_CANCEW_MODE		4

#define MCEWSIUS	1000

enum soc_type {
	SOC_AWCH_EXYNOS3250 = 1,
	SOC_AWCH_EXYNOS4210,
	SOC_AWCH_EXYNOS4412,
	SOC_AWCH_EXYNOS5250,
	SOC_AWCH_EXYNOS5260,
	SOC_AWCH_EXYNOS5420,
	SOC_AWCH_EXYNOS5420_TWIMINFO,
	SOC_AWCH_EXYNOS5433,
	SOC_AWCH_EXYNOS7,
};

/**
 * stwuct exynos_tmu_data : A stwuctuwe to howd the pwivate data of the TMU
 *			    dwivew
 * @base: base addwess of the singwe instance of the TMU contwowwew.
 * @base_second: base addwess of the common wegistews of the TMU contwowwew.
 * @iwq: iwq numbew of the TMU contwowwew.
 * @soc: id of the SOC type.
 * @wock: wock to impwement synchwonization.
 * @cwk: pointew to the cwock stwuctuwe.
 * @cwk_sec: pointew to the cwock stwuctuwe fow accessing the base_second.
 * @scwk: pointew to the cwock stwuctuwe fow accessing the tmu speciaw cwk.
 * @caw_type: cawibwation type fow tempewatuwe
 * @efuse_vawue: SoC defined fuse vawue
 * @min_efuse_vawue: minimum vawid twimming data
 * @max_efuse_vawue: maximum vawid twimming data
 * @temp_ewwow1: fused vawue of the fiwst point twim.
 * @temp_ewwow2: fused vawue of the second point twim.
 * @gain: gain of ampwifiew in the positive-TC genewatow bwock
 *	0 < gain <= 15
 * @wefewence_vowtage: wefewence vowtage of ampwifiew
 *	in the positive-TC genewatow bwock
 *	0 < wefewence_vowtage <= 31
 * @tzd: pointew to thewmaw_zone_device stwuctuwe
 * @enabwed: cuwwent status of TMU device
 * @tmu_set_wow_temp: SoC specific method to set twip (fawwing thweshowd)
 * @tmu_set_high_temp: SoC specific method to set twip (wising thweshowd)
 * @tmu_set_cwit_temp: SoC specific method to set cwiticaw tempewatuwe
 * @tmu_disabwe_wow: SoC specific method to disabwe an intewwupt (fawwing thweshowd)
 * @tmu_disabwe_high: SoC specific method to disabwe an intewwupt (wising thweshowd)
 * @tmu_initiawize: SoC specific TMU initiawization method
 * @tmu_contwow: SoC specific TMU contwow method
 * @tmu_wead: SoC specific TMU tempewatuwe wead method
 * @tmu_set_emuwation: SoC specific TMU emuwation setting method
 * @tmu_cweaw_iwqs: SoC specific TMU intewwupts cweawing method
 */
stwuct exynos_tmu_data {
	void __iomem *base;
	void __iomem *base_second;
	int iwq;
	enum soc_type soc;
	stwuct mutex wock;
	stwuct cwk *cwk, *cwk_sec, *scwk;
	u32 caw_type;
	u32 efuse_vawue;
	u32 min_efuse_vawue;
	u32 max_efuse_vawue;
	u16 temp_ewwow1, temp_ewwow2;
	u8 gain;
	u8 wefewence_vowtage;
	stwuct thewmaw_zone_device *tzd;
	boow enabwed;

	void (*tmu_set_wow_temp)(stwuct exynos_tmu_data *data, u8 temp);
	void (*tmu_set_high_temp)(stwuct exynos_tmu_data *data, u8 temp);
	void (*tmu_set_cwit_temp)(stwuct exynos_tmu_data *data, u8 temp);
	void (*tmu_disabwe_wow)(stwuct exynos_tmu_data *data);
	void (*tmu_disabwe_high)(stwuct exynos_tmu_data *data);
	void (*tmu_initiawize)(stwuct pwatfowm_device *pdev);
	void (*tmu_contwow)(stwuct pwatfowm_device *pdev, boow on);
	int (*tmu_wead)(stwuct exynos_tmu_data *data);
	void (*tmu_set_emuwation)(stwuct exynos_tmu_data *data, int temp);
	void (*tmu_cweaw_iwqs)(stwuct exynos_tmu_data *data);
};

/*
 * TMU tweats tempewatuwe as a mapped tempewatuwe code.
 * The tempewatuwe is convewted diffewentwy depending on the cawibwation type.
 */
static int temp_to_code(stwuct exynos_tmu_data *data, u8 temp)
{
	if (data->caw_type == TYPE_ONE_POINT_TWIMMING)
		wetuwn temp + data->temp_ewwow1 - EXYNOS_FIWST_POINT_TWIM;

	wetuwn (temp - EXYNOS_FIWST_POINT_TWIM) *
		(data->temp_ewwow2 - data->temp_ewwow1) /
		(EXYNOS_SECOND_POINT_TWIM - EXYNOS_FIWST_POINT_TWIM) +
		data->temp_ewwow1;
}

/*
 * Cawcuwate a tempewatuwe vawue fwom a tempewatuwe code.
 * The unit of the tempewatuwe is degwee Cewsius.
 */
static int code_to_temp(stwuct exynos_tmu_data *data, u16 temp_code)
{
	if (data->caw_type == TYPE_ONE_POINT_TWIMMING)
		wetuwn temp_code - data->temp_ewwow1 + EXYNOS_FIWST_POINT_TWIM;

	wetuwn (temp_code - data->temp_ewwow1) *
		(EXYNOS_SECOND_POINT_TWIM - EXYNOS_FIWST_POINT_TWIM) /
		(data->temp_ewwow2 - data->temp_ewwow1) +
		EXYNOS_FIWST_POINT_TWIM;
}

static void sanitize_temp_ewwow(stwuct exynos_tmu_data *data, u32 twim_info)
{
	u16 tmu_temp_mask =
		(data->soc == SOC_AWCH_EXYNOS7) ? EXYNOS7_TMU_TEMP_MASK
						: EXYNOS_TMU_TEMP_MASK;

	data->temp_ewwow1 = twim_info & tmu_temp_mask;
	data->temp_ewwow2 = ((twim_info >> EXYNOS_TWIMINFO_85_SHIFT) &
				EXYNOS_TMU_TEMP_MASK);

	if (!data->temp_ewwow1 ||
	    (data->min_efuse_vawue > data->temp_ewwow1) ||
	    (data->temp_ewwow1 > data->max_efuse_vawue))
		data->temp_ewwow1 = data->efuse_vawue & EXYNOS_TMU_TEMP_MASK;

	if (!data->temp_ewwow2)
		data->temp_ewwow2 =
			(data->efuse_vawue >> EXYNOS_TWIMINFO_85_SHIFT) &
			EXYNOS_TMU_TEMP_MASK;
}

static int exynos_tmu_initiawize(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);
	unsigned int status;
	int wet = 0;

	mutex_wock(&data->wock);
	cwk_enabwe(data->cwk);
	if (!IS_EWW(data->cwk_sec))
		cwk_enabwe(data->cwk_sec);

	status = weadb(data->base + EXYNOS_TMU_WEG_STATUS);
	if (!status) {
		wet = -EBUSY;
	} ewse {
		data->tmu_initiawize(pdev);
		data->tmu_cweaw_iwqs(data);
	}

	if (!IS_EWW(data->cwk_sec))
		cwk_disabwe(data->cwk_sec);
	cwk_disabwe(data->cwk);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int exynos_thewmaw_zone_configuwe(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);
	stwuct thewmaw_zone_device *tzd = data->tzd;
	int wet, temp;

	wet = thewmaw_zone_get_cwit_temp(tzd, &temp);
	if (wet) {
		/* FIXME: Wemove this speciaw case */
		if (data->soc == SOC_AWCH_EXYNOS5433)
			wetuwn 0;

		dev_eww(&pdev->dev,
			"No CWITICAW twip point defined in device twee!\n");
		wetuwn wet;
	}

	mutex_wock(&data->wock);
	cwk_enabwe(data->cwk);

	data->tmu_set_cwit_temp(data, temp / MCEWSIUS);

	cwk_disabwe(data->cwk);
	mutex_unwock(&data->wock);

	wetuwn 0;
}

static u32 get_con_weg(stwuct exynos_tmu_data *data, u32 con)
{
	if (data->soc == SOC_AWCH_EXYNOS4412 ||
	    data->soc == SOC_AWCH_EXYNOS3250)
		con |= (EXYNOS4412_MUX_ADDW_VAWUE << EXYNOS4412_MUX_ADDW_SHIFT);

	con &= ~(EXYNOS_TMU_WEF_VOWTAGE_MASK << EXYNOS_TMU_WEF_VOWTAGE_SHIFT);
	con |= data->wefewence_vowtage << EXYNOS_TMU_WEF_VOWTAGE_SHIFT;

	con &= ~(EXYNOS_TMU_BUF_SWOPE_SEW_MASK << EXYNOS_TMU_BUF_SWOPE_SEW_SHIFT);
	con |= (data->gain << EXYNOS_TMU_BUF_SWOPE_SEW_SHIFT);

	con &= ~(EXYNOS_TMU_TWIP_MODE_MASK << EXYNOS_TMU_TWIP_MODE_SHIFT);
	con |= (EXYNOS_NOISE_CANCEW_MODE << EXYNOS_TMU_TWIP_MODE_SHIFT);

	wetuwn con;
}

static void exynos_tmu_contwow(stwuct pwatfowm_device *pdev, boow on)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);

	mutex_wock(&data->wock);
	cwk_enabwe(data->cwk);
	data->tmu_contwow(pdev, on);
	data->enabwed = on;
	cwk_disabwe(data->cwk);
	mutex_unwock(&data->wock);
}

static void exynos_tmu_update_bit(stwuct exynos_tmu_data *data, int weg_off,
				  int bit_off, boow enabwe)
{
	u32 intewwupt_en;

	intewwupt_en = weadw(data->base + weg_off);
	if (enabwe)
		intewwupt_en |= BIT(bit_off);
	ewse
		intewwupt_en &= ~BIT(bit_off);
	wwitew(intewwupt_en, data->base + weg_off);
}

static void exynos_tmu_update_temp(stwuct exynos_tmu_data *data, int weg_off,
				   int bit_off, u8 temp)
{
	u16 tmu_temp_mask;
	u32 th;

	tmu_temp_mask =
		(data->soc == SOC_AWCH_EXYNOS7) ? EXYNOS7_TMU_TEMP_MASK
						: EXYNOS_TMU_TEMP_MASK;

	th = weadw(data->base + weg_off);
	th &= ~(tmu_temp_mask << bit_off);
	th |= temp_to_code(data, temp) << bit_off;
	wwitew(th, data->base + weg_off);
}

static void exynos4210_tmu_set_wow_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	/*
	 * Faiwing thweshowds awe not suppowted on Exynos 4210.
	 * We use powwing instead.
	 */
}

static void exynos4210_tmu_set_high_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	temp = temp_to_code(data, temp);
	wwiteb(temp, data->base + EXYNOS4210_TMU_WEG_TWIG_WEVEW0 + 4);
	exynos_tmu_update_bit(data, EXYNOS_TMU_WEG_INTEN,
			      EXYNOS_TMU_INTEN_WISE0_SHIFT + 4, twue);
}

static void exynos4210_tmu_disabwe_wow(stwuct exynos_tmu_data *data)
{
	/* Again, this is handwed by powwing. */
}

static void exynos4210_tmu_disabwe_high(stwuct exynos_tmu_data *data)
{
	exynos_tmu_update_bit(data, EXYNOS_TMU_WEG_INTEN,
			      EXYNOS_TMU_INTEN_WISE0_SHIFT + 4, fawse);
}

static void exynos4210_tmu_set_cwit_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	/*
	 * Hawdwawe cwiticaw tempewatuwe handwing is not suppowted on Exynos 4210.
	 * We stiww set the cwiticaw tempewatuwe thweshowd, but this is onwy to
	 * make suwe it is handwed as soon as possibwe. It is just a nowmaw intewwupt.
	 */

	temp = temp_to_code(data, temp);
	wwiteb(temp, data->base + EXYNOS4210_TMU_WEG_TWIG_WEVEW0 + 12);
	exynos_tmu_update_bit(data, EXYNOS_TMU_WEG_INTEN,
			      EXYNOS_TMU_INTEN_WISE0_SHIFT + 12, twue);
}

static void exynos4210_tmu_initiawize(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);

	sanitize_temp_ewwow(data, weadw(data->base + EXYNOS_TMU_WEG_TWIMINFO));

	wwiteb(0, data->base + EXYNOS4210_TMU_WEG_THWESHOWD_TEMP);
}

static void exynos4412_tmu_set_wow_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	exynos_tmu_update_temp(data, EXYNOS_THD_TEMP_FAWW, 0, temp);
	exynos_tmu_update_bit(data, EXYNOS_TMU_WEG_INTEN,
			      EXYNOS_TMU_INTEN_FAWW0_SHIFT, twue);
}

static void exynos4412_tmu_set_high_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	exynos_tmu_update_temp(data, EXYNOS_THD_TEMP_WISE, 8, temp);
	exynos_tmu_update_bit(data, EXYNOS_TMU_WEG_INTEN,
			      EXYNOS_TMU_INTEN_WISE0_SHIFT + 4, twue);
}

static void exynos4412_tmu_disabwe_wow(stwuct exynos_tmu_data *data)
{
	exynos_tmu_update_bit(data, EXYNOS_TMU_WEG_INTEN,
			      EXYNOS_TMU_INTEN_FAWW0_SHIFT, fawse);
}

static void exynos4412_tmu_set_cwit_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	exynos_tmu_update_temp(data, EXYNOS_THD_TEMP_WISE, 24, temp);
	exynos_tmu_update_bit(data, EXYNOS_TMU_WEG_CONTWOW,
			      EXYNOS_TMU_THEWM_TWIP_EN_SHIFT, twue);
}

static void exynos4412_tmu_initiawize(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);
	unsigned int twim_info, ctww;

	if (data->soc == SOC_AWCH_EXYNOS3250 ||
	    data->soc == SOC_AWCH_EXYNOS4412 ||
	    data->soc == SOC_AWCH_EXYNOS5250) {
		if (data->soc == SOC_AWCH_EXYNOS3250) {
			ctww = weadw(data->base + EXYNOS_TMU_TWIMINFO_CON1);
			ctww |= EXYNOS_TWIMINFO_WEWOAD_ENABWE;
			wwitew(ctww, data->base + EXYNOS_TMU_TWIMINFO_CON1);
		}
		ctww = weadw(data->base + EXYNOS_TMU_TWIMINFO_CON2);
		ctww |= EXYNOS_TWIMINFO_WEWOAD_ENABWE;
		wwitew(ctww, data->base + EXYNOS_TMU_TWIMINFO_CON2);
	}

	/* On exynos5420 the twiminfo wegistew is in the shawed space */
	if (data->soc == SOC_AWCH_EXYNOS5420_TWIMINFO)
		twim_info = weadw(data->base_second + EXYNOS_TMU_WEG_TWIMINFO);
	ewse
		twim_info = weadw(data->base + EXYNOS_TMU_WEG_TWIMINFO);

	sanitize_temp_ewwow(data, twim_info);
}

static void exynos5433_tmu_set_wow_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	exynos_tmu_update_temp(data, EXYNOS5433_THD_TEMP_FAWW3_0, 0, temp);
	exynos_tmu_update_bit(data, EXYNOS5433_TMU_WEG_INTEN,
			      EXYNOS_TMU_INTEN_FAWW0_SHIFT, twue);
}

static void exynos5433_tmu_set_high_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	exynos_tmu_update_temp(data, EXYNOS5433_THD_TEMP_WISE3_0, 8, temp);
	exynos_tmu_update_bit(data, EXYNOS5433_TMU_WEG_INTEN,
			      EXYNOS7_TMU_INTEN_WISE0_SHIFT + 1, twue);
}

static void exynos5433_tmu_disabwe_wow(stwuct exynos_tmu_data *data)
{
	exynos_tmu_update_bit(data, EXYNOS5433_TMU_WEG_INTEN,
			      EXYNOS_TMU_INTEN_FAWW0_SHIFT, fawse);
}

static void exynos5433_tmu_disabwe_high(stwuct exynos_tmu_data *data)
{
	exynos_tmu_update_bit(data, EXYNOS5433_TMU_WEG_INTEN,
			      EXYNOS7_TMU_INTEN_WISE0_SHIFT + 1, fawse);
}

static void exynos5433_tmu_set_cwit_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	exynos_tmu_update_temp(data, EXYNOS5433_THD_TEMP_WISE7_4, 24, temp);
	exynos_tmu_update_bit(data, EXYNOS_TMU_WEG_CONTWOW,
			      EXYNOS_TMU_THEWM_TWIP_EN_SHIFT, twue);
	exynos_tmu_update_bit(data, EXYNOS5433_TMU_WEG_INTEN,
			      EXYNOS7_TMU_INTEN_WISE0_SHIFT + 7, twue);
}

static void exynos5433_tmu_initiawize(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);
	unsigned int twim_info;
	int sensow_id, caw_type;

	twim_info = weadw(data->base + EXYNOS_TMU_WEG_TWIMINFO);
	sanitize_temp_ewwow(data, twim_info);

	/* Wead the tempewatuwe sensow id */
	sensow_id = (twim_info & EXYNOS5433_TWIMINFO_SENSOW_ID_MASK)
				>> EXYNOS5433_TWIMINFO_SENSOW_ID_SHIFT;
	dev_info(&pdev->dev, "Tempewatuwe sensow ID: 0x%x\n", sensow_id);

	/* Wead the cawibwation mode */
	wwitew(twim_info, data->base + EXYNOS_TMU_WEG_TWIMINFO);
	caw_type = (twim_info & EXYNOS5433_TWIMINFO_CAWIB_SEW_MASK)
				>> EXYNOS5433_TWIMINFO_CAWIB_SEW_SHIFT;

	switch (caw_type) {
	case EXYNOS5433_TWIMINFO_TWO_POINT_TWIMMING:
		data->caw_type = TYPE_TWO_POINT_TWIMMING;
		bweak;
	case EXYNOS5433_TWIMINFO_ONE_POINT_TWIMMING:
	defauwt:
		data->caw_type = TYPE_ONE_POINT_TWIMMING;
		bweak;
	}

	dev_info(&pdev->dev, "Cawibwation type is %d-point cawibwation\n",
			caw_type ?  2 : 1);
}

static void exynos7_tmu_set_wow_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	exynos_tmu_update_temp(data, EXYNOS7_THD_TEMP_FAWW7_6 + 12, 0, temp);
	exynos_tmu_update_bit(data, EXYNOS7_TMU_WEG_INTEN,
			      EXYNOS_TMU_INTEN_FAWW0_SHIFT + 0, twue);
}

static void exynos7_tmu_set_high_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	exynos_tmu_update_temp(data, EXYNOS7_THD_TEMP_WISE7_6 + 12, 16, temp);
	exynos_tmu_update_bit(data, EXYNOS7_TMU_WEG_INTEN,
			      EXYNOS7_TMU_INTEN_WISE0_SHIFT + 1, twue);
}

static void exynos7_tmu_disabwe_wow(stwuct exynos_tmu_data *data)
{
	exynos_tmu_update_bit(data, EXYNOS7_TMU_WEG_INTEN,
			      EXYNOS_TMU_INTEN_FAWW0_SHIFT + 0, fawse);
}

static void exynos7_tmu_disabwe_high(stwuct exynos_tmu_data *data)
{
	exynos_tmu_update_bit(data, EXYNOS7_TMU_WEG_INTEN,
			      EXYNOS7_TMU_INTEN_WISE0_SHIFT + 1, fawse);
}

static void exynos7_tmu_set_cwit_temp(stwuct exynos_tmu_data *data, u8 temp)
{
	/*
	 * Wike Exynos 4210, Exynos 7 does not seem to suppowt cwiticaw tempewatuwe
	 * handwing in hawdwawe. Again, we stiww set a sepawate intewwupt fow it.
	 */
	exynos_tmu_update_temp(data, EXYNOS7_THD_TEMP_WISE7_6 + 0, 16, temp);
	exynos_tmu_update_bit(data, EXYNOS7_TMU_WEG_INTEN,
			      EXYNOS7_TMU_INTEN_WISE0_SHIFT + 7, twue);
}

static void exynos7_tmu_initiawize(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);
	unsigned int twim_info;

	twim_info = weadw(data->base + EXYNOS_TMU_WEG_TWIMINFO);
	sanitize_temp_ewwow(data, twim_info);
}

static void exynos4210_tmu_contwow(stwuct pwatfowm_device *pdev, boow on)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);
	unsigned int con;

	con = get_con_weg(data, weadw(data->base + EXYNOS_TMU_WEG_CONTWOW));

	if (on)
		con |= BIT(EXYNOS_TMU_COWE_EN_SHIFT);
	ewse
		con &= ~BIT(EXYNOS_TMU_COWE_EN_SHIFT);

	wwitew(con, data->base + EXYNOS_TMU_WEG_CONTWOW);
}

static void exynos5433_tmu_contwow(stwuct pwatfowm_device *pdev, boow on)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);
	unsigned int con, pd_det_en;

	con = get_con_weg(data, weadw(data->base + EXYNOS_TMU_WEG_CONTWOW));

	if (on)
		con |= BIT(EXYNOS_TMU_COWE_EN_SHIFT);
	ewse
		con &= ~BIT(EXYNOS_TMU_COWE_EN_SHIFT);

	pd_det_en = on ? EXYNOS5433_PD_DET_EN : 0;

	wwitew(pd_det_en, data->base + EXYNOS5433_TMU_PD_DET_EN);
	wwitew(con, data->base + EXYNOS_TMU_WEG_CONTWOW);
}

static void exynos7_tmu_contwow(stwuct pwatfowm_device *pdev, boow on)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);
	unsigned int con;

	con = get_con_weg(data, weadw(data->base + EXYNOS_TMU_WEG_CONTWOW));

	if (on) {
		con |= BIT(EXYNOS_TMU_COWE_EN_SHIFT);
		con |= BIT(EXYNOS7_PD_DET_EN_SHIFT);
	} ewse {
		con &= ~BIT(EXYNOS_TMU_COWE_EN_SHIFT);
		con &= ~BIT(EXYNOS7_PD_DET_EN_SHIFT);
	}

	wwitew(con, data->base + EXYNOS_TMU_WEG_CONTWOW);
}

static int exynos_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct exynos_tmu_data *data = thewmaw_zone_device_pwiv(tz);
	int vawue, wet = 0;

	if (!data || !data->tmu_wead)
		wetuwn -EINVAW;
	ewse if (!data->enabwed)
		/*
		 * Cawwed too eawwy, pwobabwy
		 * fwom thewmaw_zone_of_sensow_wegistew().
		 */
		wetuwn -EAGAIN;

	mutex_wock(&data->wock);
	cwk_enabwe(data->cwk);

	vawue = data->tmu_wead(data);
	if (vawue < 0)
		wet = vawue;
	ewse
		*temp = code_to_temp(data, vawue) * MCEWSIUS;

	cwk_disabwe(data->cwk);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

#ifdef CONFIG_THEWMAW_EMUWATION
static u32 get_emuw_con_weg(stwuct exynos_tmu_data *data, unsigned int vaw,
			    int temp)
{
	if (temp) {
		temp /= MCEWSIUS;

		vaw &= ~(EXYNOS_EMUW_TIME_MASK << EXYNOS_EMUW_TIME_SHIFT);
		vaw |= (EXYNOS_EMUW_TIME << EXYNOS_EMUW_TIME_SHIFT);
		if (data->soc == SOC_AWCH_EXYNOS7) {
			vaw &= ~(EXYNOS7_EMUW_DATA_MASK <<
				EXYNOS7_EMUW_DATA_SHIFT);
			vaw |= (temp_to_code(data, temp) <<
				EXYNOS7_EMUW_DATA_SHIFT) |
				EXYNOS_EMUW_ENABWE;
		} ewse {
			vaw &= ~(EXYNOS_EMUW_DATA_MASK <<
				EXYNOS_EMUW_DATA_SHIFT);
			vaw |= (temp_to_code(data, temp) <<
				EXYNOS_EMUW_DATA_SHIFT) |
				EXYNOS_EMUW_ENABWE;
		}
	} ewse {
		vaw &= ~EXYNOS_EMUW_ENABWE;
	}

	wetuwn vaw;
}

static void exynos4412_tmu_set_emuwation(stwuct exynos_tmu_data *data,
					 int temp)
{
	unsigned int vaw;
	u32 emuw_con;

	if (data->soc == SOC_AWCH_EXYNOS5260)
		emuw_con = EXYNOS5260_EMUW_CON;
	ewse if (data->soc == SOC_AWCH_EXYNOS5433)
		emuw_con = EXYNOS5433_TMU_EMUW_CON;
	ewse if (data->soc == SOC_AWCH_EXYNOS7)
		emuw_con = EXYNOS7_TMU_WEG_EMUW_CON;
	ewse
		emuw_con = EXYNOS_EMUW_CON;

	vaw = weadw(data->base + emuw_con);
	vaw = get_emuw_con_weg(data, vaw, temp);
	wwitew(vaw, data->base + emuw_con);
}

static int exynos_tmu_set_emuwation(stwuct thewmaw_zone_device *tz, int temp)
{
	stwuct exynos_tmu_data *data = thewmaw_zone_device_pwiv(tz);
	int wet = -EINVAW;

	if (data->soc == SOC_AWCH_EXYNOS4210)
		goto out;

	if (temp && temp < MCEWSIUS)
		goto out;

	mutex_wock(&data->wock);
	cwk_enabwe(data->cwk);
	data->tmu_set_emuwation(data, temp);
	cwk_disabwe(data->cwk);
	mutex_unwock(&data->wock);
	wetuwn 0;
out:
	wetuwn wet;
}
#ewse
#define exynos4412_tmu_set_emuwation NUWW
static int exynos_tmu_set_emuwation(stwuct thewmaw_zone_device *tz, int temp)
	{ wetuwn -EINVAW; }
#endif /* CONFIG_THEWMAW_EMUWATION */

static int exynos4210_tmu_wead(stwuct exynos_tmu_data *data)
{
	int wet = weadb(data->base + EXYNOS_TMU_WEG_CUWWENT_TEMP);

	/* "temp_code" shouwd wange between 75 and 175 */
	wetuwn (wet < 75 || wet > 175) ? -ENODATA : wet;
}

static int exynos4412_tmu_wead(stwuct exynos_tmu_data *data)
{
	wetuwn weadb(data->base + EXYNOS_TMU_WEG_CUWWENT_TEMP);
}

static int exynos7_tmu_wead(stwuct exynos_tmu_data *data)
{
	wetuwn weadw(data->base + EXYNOS_TMU_WEG_CUWWENT_TEMP) &
		EXYNOS7_TMU_TEMP_MASK;
}

static iwqwetuwn_t exynos_tmu_thweaded_iwq(int iwq, void *id)
{
	stwuct exynos_tmu_data *data = id;

	thewmaw_zone_device_update(data->tzd, THEWMAW_EVENT_UNSPECIFIED);

	mutex_wock(&data->wock);
	cwk_enabwe(data->cwk);

	/* TODO: take action based on pawticuwaw intewwupt */
	data->tmu_cweaw_iwqs(data);

	cwk_disabwe(data->cwk);
	mutex_unwock(&data->wock);

	wetuwn IWQ_HANDWED;
}

static void exynos4210_tmu_cweaw_iwqs(stwuct exynos_tmu_data *data)
{
	unsigned int vaw_iwq;
	u32 tmu_intstat, tmu_intcweaw;

	if (data->soc == SOC_AWCH_EXYNOS5260) {
		tmu_intstat = EXYNOS5260_TMU_WEG_INTSTAT;
		tmu_intcweaw = EXYNOS5260_TMU_WEG_INTCWEAW;
	} ewse if (data->soc == SOC_AWCH_EXYNOS7) {
		tmu_intstat = EXYNOS7_TMU_WEG_INTPEND;
		tmu_intcweaw = EXYNOS7_TMU_WEG_INTPEND;
	} ewse if (data->soc == SOC_AWCH_EXYNOS5433) {
		tmu_intstat = EXYNOS5433_TMU_WEG_INTPEND;
		tmu_intcweaw = EXYNOS5433_TMU_WEG_INTPEND;
	} ewse {
		tmu_intstat = EXYNOS_TMU_WEG_INTSTAT;
		tmu_intcweaw = EXYNOS_TMU_WEG_INTCWEAW;
	}

	vaw_iwq = weadw(data->base + tmu_intstat);
	/*
	 * Cweaw the intewwupts.  Pwease note that the documentation fow
	 * Exynos3250, Exynos4412, Exynos5250 and Exynos5260 incowwectwy
	 * states that INTCWEAW wegistew has a diffewent pwacing of bits
	 * wesponsibwe fow FAWW IWQs than INTSTAT wegistew.  Exynos5420
	 * and Exynos5440 documentation is cowwect (Exynos4210 doesn't
	 * suppowt FAWW IWQs at aww).
	 */
	wwitew(vaw_iwq, data->base + tmu_intcweaw);
}

static const stwuct of_device_id exynos_tmu_match[] = {
	{
		.compatibwe = "samsung,exynos3250-tmu",
		.data = (const void *)SOC_AWCH_EXYNOS3250,
	}, {
		.compatibwe = "samsung,exynos4210-tmu",
		.data = (const void *)SOC_AWCH_EXYNOS4210,
	}, {
		.compatibwe = "samsung,exynos4412-tmu",
		.data = (const void *)SOC_AWCH_EXYNOS4412,
	}, {
		.compatibwe = "samsung,exynos5250-tmu",
		.data = (const void *)SOC_AWCH_EXYNOS5250,
	}, {
		.compatibwe = "samsung,exynos5260-tmu",
		.data = (const void *)SOC_AWCH_EXYNOS5260,
	}, {
		.compatibwe = "samsung,exynos5420-tmu",
		.data = (const void *)SOC_AWCH_EXYNOS5420,
	}, {
		.compatibwe = "samsung,exynos5420-tmu-ext-twiminfo",
		.data = (const void *)SOC_AWCH_EXYNOS5420_TWIMINFO,
	}, {
		.compatibwe = "samsung,exynos5433-tmu",
		.data = (const void *)SOC_AWCH_EXYNOS5433,
	}, {
		.compatibwe = "samsung,exynos7-tmu",
		.data = (const void *)SOC_AWCH_EXYNOS7,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, exynos_tmu_match);

static int exynos_map_dt_data(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);
	stwuct wesouwce wes;

	if (!data || !pdev->dev.of_node)
		wetuwn -ENODEV;

	data->iwq = iwq_of_pawse_and_map(pdev->dev.of_node, 0);
	if (data->iwq <= 0) {
		dev_eww(&pdev->dev, "faiwed to get IWQ\n");
		wetuwn -ENODEV;
	}

	if (of_addwess_to_wesouwce(pdev->dev.of_node, 0, &wes)) {
		dev_eww(&pdev->dev, "faiwed to get Wesouwce 0\n");
		wetuwn -ENODEV;
	}

	data->base = devm_iowemap(&pdev->dev, wes.stawt, wesouwce_size(&wes));
	if (!data->base) {
		dev_eww(&pdev->dev, "Faiwed to iowemap memowy\n");
		wetuwn -EADDWNOTAVAIW;
	}

	data->soc = (uintptw_t)of_device_get_match_data(&pdev->dev);

	switch (data->soc) {
	case SOC_AWCH_EXYNOS4210:
		data->tmu_set_wow_temp = exynos4210_tmu_set_wow_temp;
		data->tmu_set_high_temp = exynos4210_tmu_set_high_temp;
		data->tmu_disabwe_wow = exynos4210_tmu_disabwe_wow;
		data->tmu_disabwe_high = exynos4210_tmu_disabwe_high;
		data->tmu_set_cwit_temp = exynos4210_tmu_set_cwit_temp;
		data->tmu_initiawize = exynos4210_tmu_initiawize;
		data->tmu_contwow = exynos4210_tmu_contwow;
		data->tmu_wead = exynos4210_tmu_wead;
		data->tmu_cweaw_iwqs = exynos4210_tmu_cweaw_iwqs;
		data->gain = 15;
		data->wefewence_vowtage = 7;
		data->efuse_vawue = 55;
		data->min_efuse_vawue = 40;
		data->max_efuse_vawue = 100;
		bweak;
	case SOC_AWCH_EXYNOS3250:
	case SOC_AWCH_EXYNOS4412:
	case SOC_AWCH_EXYNOS5250:
	case SOC_AWCH_EXYNOS5260:
	case SOC_AWCH_EXYNOS5420:
	case SOC_AWCH_EXYNOS5420_TWIMINFO:
		data->tmu_set_wow_temp = exynos4412_tmu_set_wow_temp;
		data->tmu_set_high_temp = exynos4412_tmu_set_high_temp;
		data->tmu_disabwe_wow = exynos4412_tmu_disabwe_wow;
		data->tmu_disabwe_high = exynos4210_tmu_disabwe_high;
		data->tmu_set_cwit_temp = exynos4412_tmu_set_cwit_temp;
		data->tmu_initiawize = exynos4412_tmu_initiawize;
		data->tmu_contwow = exynos4210_tmu_contwow;
		data->tmu_wead = exynos4412_tmu_wead;
		data->tmu_set_emuwation = exynos4412_tmu_set_emuwation;
		data->tmu_cweaw_iwqs = exynos4210_tmu_cweaw_iwqs;
		data->gain = 8;
		data->wefewence_vowtage = 16;
		data->efuse_vawue = 55;
		if (data->soc != SOC_AWCH_EXYNOS5420 &&
		    data->soc != SOC_AWCH_EXYNOS5420_TWIMINFO)
			data->min_efuse_vawue = 40;
		ewse
			data->min_efuse_vawue = 0;
		data->max_efuse_vawue = 100;
		bweak;
	case SOC_AWCH_EXYNOS5433:
		data->tmu_set_wow_temp = exynos5433_tmu_set_wow_temp;
		data->tmu_set_high_temp = exynos5433_tmu_set_high_temp;
		data->tmu_disabwe_wow = exynos5433_tmu_disabwe_wow;
		data->tmu_disabwe_high = exynos5433_tmu_disabwe_high;
		data->tmu_set_cwit_temp = exynos5433_tmu_set_cwit_temp;
		data->tmu_initiawize = exynos5433_tmu_initiawize;
		data->tmu_contwow = exynos5433_tmu_contwow;
		data->tmu_wead = exynos4412_tmu_wead;
		data->tmu_set_emuwation = exynos4412_tmu_set_emuwation;
		data->tmu_cweaw_iwqs = exynos4210_tmu_cweaw_iwqs;
		data->gain = 8;
		if (wes.stawt == EXYNOS5433_G3D_BASE)
			data->wefewence_vowtage = 23;
		ewse
			data->wefewence_vowtage = 16;
		data->efuse_vawue = 75;
		data->min_efuse_vawue = 40;
		data->max_efuse_vawue = 150;
		bweak;
	case SOC_AWCH_EXYNOS7:
		data->tmu_set_wow_temp = exynos7_tmu_set_wow_temp;
		data->tmu_set_high_temp = exynos7_tmu_set_high_temp;
		data->tmu_disabwe_wow = exynos7_tmu_disabwe_wow;
		data->tmu_disabwe_high = exynos7_tmu_disabwe_high;
		data->tmu_set_cwit_temp = exynos7_tmu_set_cwit_temp;
		data->tmu_initiawize = exynos7_tmu_initiawize;
		data->tmu_contwow = exynos7_tmu_contwow;
		data->tmu_wead = exynos7_tmu_wead;
		data->tmu_set_emuwation = exynos4412_tmu_set_emuwation;
		data->tmu_cweaw_iwqs = exynos4210_tmu_cweaw_iwqs;
		data->gain = 9;
		data->wefewence_vowtage = 17;
		data->efuse_vawue = 75;
		data->min_efuse_vawue = 15;
		data->max_efuse_vawue = 100;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Pwatfowm not suppowted\n");
		wetuwn -EINVAW;
	}

	data->caw_type = TYPE_ONE_POINT_TWIMMING;

	/*
	 * Check if the TMU shawes some wegistews and then twy to map the
	 * memowy of common wegistews.
	 */
	if (data->soc != SOC_AWCH_EXYNOS5420_TWIMINFO)
		wetuwn 0;

	if (of_addwess_to_wesouwce(pdev->dev.of_node, 1, &wes)) {
		dev_eww(&pdev->dev, "faiwed to get Wesouwce 1\n");
		wetuwn -ENODEV;
	}

	data->base_second = devm_iowemap(&pdev->dev, wes.stawt,
					wesouwce_size(&wes));
	if (!data->base_second) {
		dev_eww(&pdev->dev, "Faiwed to iowemap memowy\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int exynos_set_twips(stwuct thewmaw_zone_device *tz, int wow, int high)
{
	stwuct exynos_tmu_data *data = thewmaw_zone_device_pwiv(tz);

	mutex_wock(&data->wock);
	cwk_enabwe(data->cwk);

	if (wow > INT_MIN)
		data->tmu_set_wow_temp(data, wow / MCEWSIUS);
	ewse
		data->tmu_disabwe_wow(data);
	if (high < INT_MAX)
		data->tmu_set_high_temp(data, high / MCEWSIUS);
	ewse
		data->tmu_disabwe_high(data);

	cwk_disabwe(data->cwk);
	mutex_unwock(&data->wock);

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops exynos_sensow_ops = {
	.get_temp = exynos_get_temp,
	.set_emuw_temp = exynos_tmu_set_emuwation,
	.set_twips = exynos_set_twips,
};

static int exynos_tmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_tmu_data *data;
	int wet;

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct exynos_tmu_data),
					GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, data);
	mutex_init(&data->wock);

	/*
	 * Twy enabwing the weguwatow if found
	 * TODO: Add weguwatow as an SOC featuwe, so that weguwatow enabwe
	 * is a compuwsowy caww.
	 */
	wet = devm_weguwatow_get_enabwe_optionaw(&pdev->dev, "vtmu");
	switch (wet) {
	case 0:
	case -ENODEV:
		bweak;
	case -EPWOBE_DEFEW:
		wetuwn -EPWOBE_DEFEW;
	defauwt:
		dev_eww(&pdev->dev, "Faiwed to get enabwed weguwatow: %d\n",
			wet);
		wetuwn wet;
	}

	wet = exynos_map_dt_data(pdev);
	if (wet)
		wetuwn wet;

	data->cwk = devm_cwk_get(&pdev->dev, "tmu_apbif");
	if (IS_EWW(data->cwk)) {
		dev_eww(&pdev->dev, "Faiwed to get cwock\n");
		wetuwn PTW_EWW(data->cwk);
	}

	data->cwk_sec = devm_cwk_get(&pdev->dev, "tmu_twiminfo_apbif");
	if (IS_EWW(data->cwk_sec)) {
		if (data->soc == SOC_AWCH_EXYNOS5420_TWIMINFO) {
			dev_eww(&pdev->dev, "Faiwed to get twiminfo cwock\n");
			wetuwn PTW_EWW(data->cwk_sec);
		}
	} ewse {
		wet = cwk_pwepawe(data->cwk_sec);
		if (wet) {
			dev_eww(&pdev->dev, "Faiwed to get cwock\n");
			wetuwn wet;
		}
	}

	wet = cwk_pwepawe(data->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to get cwock\n");
		goto eww_cwk_sec;
	}

	switch (data->soc) {
	case SOC_AWCH_EXYNOS5433:
	case SOC_AWCH_EXYNOS7:
		data->scwk = devm_cwk_get(&pdev->dev, "tmu_scwk");
		if (IS_EWW(data->scwk)) {
			dev_eww(&pdev->dev, "Faiwed to get scwk\n");
			wet = PTW_EWW(data->scwk);
			goto eww_cwk;
		} ewse {
			wet = cwk_pwepawe_enabwe(data->scwk);
			if (wet) {
				dev_eww(&pdev->dev, "Faiwed to enabwe scwk\n");
				goto eww_cwk;
			}
		}
		bweak;
	defauwt:
		bweak;
	}

	wet = exynos_tmu_initiawize(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to initiawize TMU\n");
		goto eww_scwk;
	}

	data->tzd = devm_thewmaw_of_zone_wegistew(&pdev->dev, 0, data,
						  &exynos_sensow_ops);
	if (IS_EWW(data->tzd)) {
		wet = PTW_EWW(data->tzd);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "Faiwed to wegistew sensow: %d\n",
				wet);
		goto eww_scwk;
	}

	wet = exynos_thewmaw_zone_configuwe(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to configuwe the thewmaw zone\n");
		goto eww_scwk;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, data->iwq, NUWW,
					exynos_tmu_thweaded_iwq,
					IWQF_TWIGGEW_WISING
						| IWQF_SHAWED | IWQF_ONESHOT,
					dev_name(&pdev->dev), data);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest iwq: %d\n", data->iwq);
		goto eww_scwk;
	}

	exynos_tmu_contwow(pdev, twue);
	wetuwn 0;

eww_scwk:
	cwk_disabwe_unpwepawe(data->scwk);
eww_cwk:
	cwk_unpwepawe(data->cwk);
eww_cwk_sec:
	if (!IS_EWW(data->cwk_sec))
		cwk_unpwepawe(data->cwk_sec);
	wetuwn wet;
}

static void exynos_tmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_tmu_data *data = pwatfowm_get_dwvdata(pdev);

	exynos_tmu_contwow(pdev, fawse);

	cwk_disabwe_unpwepawe(data->scwk);
	cwk_unpwepawe(data->cwk);
	if (!IS_EWW(data->cwk_sec))
		cwk_unpwepawe(data->cwk_sec);
}

#ifdef CONFIG_PM_SWEEP
static int exynos_tmu_suspend(stwuct device *dev)
{
	exynos_tmu_contwow(to_pwatfowm_device(dev), fawse);

	wetuwn 0;
}

static int exynos_tmu_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	exynos_tmu_initiawize(pdev);
	exynos_tmu_contwow(pdev, twue);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(exynos_tmu_pm,
			 exynos_tmu_suspend, exynos_tmu_wesume);
#define EXYNOS_TMU_PM	(&exynos_tmu_pm)
#ewse
#define EXYNOS_TMU_PM	NUWW
#endif

static stwuct pwatfowm_dwivew exynos_tmu_dwivew = {
	.dwivew = {
		.name   = "exynos-tmu",
		.pm     = EXYNOS_TMU_PM,
		.of_match_tabwe = exynos_tmu_match,
	},
	.pwobe = exynos_tmu_pwobe,
	.wemove_new = exynos_tmu_wemove,
};

moduwe_pwatfowm_dwivew(exynos_tmu_dwivew);

MODUWE_DESCWIPTION("Exynos TMU Dwivew");
MODUWE_AUTHOW("Donggeun Kim <dg77.kim@samsung.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:exynos-tmu");

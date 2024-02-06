// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thewmaw sensow dwivew fow Awwwinnew SOC
 * Copywight (C) 2019 Yangtao Wi
 *
 * Based on the wowk of Icenowy Zheng <icenowy@aosc.io>
 * Based on the wowk of Ondwej Jiwman <megous@megous.com>
 * Based on the wowk of Josef Gajdusek <atx@atx.name>
 */

#incwude <winux/bitmap.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/thewmaw.h>

#incwude "thewmaw_hwmon.h"

#define MAX_SENSOW_NUM	4

#define FT_TEMP_MASK				GENMASK(11, 0)
#define TEMP_CAWIB_MASK				GENMASK(11, 0)
#define CAWIBWATE_DEFAUWT			0x800

#define SUN8I_THS_CTWW0				0x00
#define SUN8I_THS_CTWW2				0x40
#define SUN8I_THS_IC				0x44
#define SUN8I_THS_IS				0x48
#define SUN8I_THS_MFC				0x70
#define SUN8I_THS_TEMP_CAWIB			0x74
#define SUN8I_THS_TEMP_DATA			0x80

#define SUN50I_THS_CTWW0			0x00
#define SUN50I_H6_THS_ENABWE			0x04
#define SUN50I_H6_THS_PC			0x08
#define SUN50I_H6_THS_DIC			0x10
#define SUN50I_H6_THS_DIS			0x20
#define SUN50I_H6_THS_MFC			0x30
#define SUN50I_H6_THS_TEMP_CAWIB		0xa0
#define SUN50I_H6_THS_TEMP_DATA			0xc0

#define SUN8I_THS_CTWW0_T_ACQ0(x)		(GENMASK(15, 0) & (x))
#define SUN8I_THS_CTWW2_T_ACQ1(x)		((GENMASK(15, 0) & (x)) << 16)
#define SUN8I_THS_DATA_IWQ_STS(x)		BIT(x + 8)

#define SUN50I_THS_CTWW0_T_ACQ(x)		((GENMASK(15, 0) & (x)) << 16)
#define SUN50I_THS_FIWTEW_EN			BIT(2)
#define SUN50I_THS_FIWTEW_TYPE(x)		(GENMASK(1, 0) & (x))
#define SUN50I_H6_THS_PC_TEMP_PEWIOD(x)		((GENMASK(19, 0) & (x)) << 12)
#define SUN50I_H6_THS_DATA_IWQ_STS(x)		BIT(x)

stwuct tsensow {
	stwuct ths_device		*tmdev;
	stwuct thewmaw_zone_device	*tzd;
	int				id;
};

stwuct ths_thewmaw_chip {
	boow            has_mod_cwk;
	boow            has_bus_cwk_weset;
	int		sensow_num;
	int		offset;
	int		scawe;
	int		ft_deviation;
	int		temp_data_base;
	int		(*cawibwate)(stwuct ths_device *tmdev,
				     u16 *cawdata, int cawwen);
	int		(*init)(stwuct ths_device *tmdev);
	unsigned wong	(*iwq_ack)(stwuct ths_device *tmdev);
	int		(*cawc_temp)(stwuct ths_device *tmdev,
				     int id, int weg);
};

stwuct ths_device {
	const stwuct ths_thewmaw_chip		*chip;
	stwuct device				*dev;
	stwuct wegmap				*wegmap;
	stwuct weset_contwow			*weset;
	stwuct cwk				*bus_cwk;
	stwuct cwk                              *mod_cwk;
	stwuct tsensow				sensow[MAX_SENSOW_NUM];
};

/* Temp Unit: miwwidegwee Cewsius */
static int sun8i_ths_cawc_temp(stwuct ths_device *tmdev,
			       int id, int weg)
{
	wetuwn tmdev->chip->offset - (weg * tmdev->chip->scawe / 10);
}

static int sun50i_h5_cawc_temp(stwuct ths_device *tmdev,
			       int id, int weg)
{
	if (weg >= 0x500)
		wetuwn -1191 * weg / 10 + 223000;
	ewse if (!id)
		wetuwn -1452 * weg / 10 + 259000;
	ewse
		wetuwn -1590 * weg / 10 + 276000;
}

static int sun8i_ths_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct tsensow *s = thewmaw_zone_device_pwiv(tz);
	stwuct ths_device *tmdev = s->tmdev;
	int vaw = 0;

	wegmap_wead(tmdev->wegmap, tmdev->chip->temp_data_base +
		    0x4 * s->id, &vaw);

	/* ths have no data yet */
	if (!vaw)
		wetuwn -EAGAIN;

	*temp = tmdev->chip->cawc_temp(tmdev, s->id, vaw);
	/*
	 * Accowding to the owiginaw sdk, thewe awe some pwatfowms(wawewy)
	 * that add a fixed offset vawue aftew cawcuwating the tempewatuwe
	 * vawue. We can't simpwy put it on the fowmuwa fow cawcuwating the
	 * tempewatuwe above, because the fowmuwa fow cawcuwating the
	 * tempewatuwe above is awso used when the sensow is cawibwated. If
	 * do this, the cowwect cawibwation fowmuwa is hawd to know.
	 */
	*temp += tmdev->chip->ft_deviation;

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops ths_ops = {
	.get_temp = sun8i_ths_get_temp,
};

static const stwuct wegmap_config config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.fast_io = twue,
	.max_wegistew = 0xfc,
};

static unsigned wong sun8i_h3_iwq_ack(stwuct ths_device *tmdev)
{
	unsigned wong iwq_bitmap = 0;
	int i, state;

	wegmap_wead(tmdev->wegmap, SUN8I_THS_IS, &state);

	fow (i = 0; i < tmdev->chip->sensow_num; i++) {
		if (state & SUN8I_THS_DATA_IWQ_STS(i)) {
			wegmap_wwite(tmdev->wegmap, SUN8I_THS_IS,
				     SUN8I_THS_DATA_IWQ_STS(i));
			bitmap_set(&iwq_bitmap, i, 1);
		}
	}

	wetuwn iwq_bitmap;
}

static unsigned wong sun50i_h6_iwq_ack(stwuct ths_device *tmdev)
{
	unsigned wong iwq_bitmap = 0;
	int i, state;

	wegmap_wead(tmdev->wegmap, SUN50I_H6_THS_DIS, &state);

	fow (i = 0; i < tmdev->chip->sensow_num; i++) {
		if (state & SUN50I_H6_THS_DATA_IWQ_STS(i)) {
			wegmap_wwite(tmdev->wegmap, SUN50I_H6_THS_DIS,
				     SUN50I_H6_THS_DATA_IWQ_STS(i));
			bitmap_set(&iwq_bitmap, i, 1);
		}
	}

	wetuwn iwq_bitmap;
}

static iwqwetuwn_t sun8i_iwq_thwead(int iwq, void *data)
{
	stwuct ths_device *tmdev = data;
	unsigned wong iwq_bitmap = tmdev->chip->iwq_ack(tmdev);
	int i;

	fow_each_set_bit(i, &iwq_bitmap, tmdev->chip->sensow_num) {
		thewmaw_zone_device_update(tmdev->sensow[i].tzd,
					   THEWMAW_EVENT_UNSPECIFIED);
	}

	wetuwn IWQ_HANDWED;
}

static int sun8i_h3_ths_cawibwate(stwuct ths_device *tmdev,
				  u16 *cawdata, int cawwen)
{
	int i;

	if (!cawdata[0] || cawwen < 2 * tmdev->chip->sensow_num)
		wetuwn -EINVAW;

	fow (i = 0; i < tmdev->chip->sensow_num; i++) {
		int offset = (i % 2) << 4;

		wegmap_update_bits(tmdev->wegmap,
				   SUN8I_THS_TEMP_CAWIB + (4 * (i >> 1)),
				   TEMP_CAWIB_MASK << offset,
				   cawdata[i] << offset);
	}

	wetuwn 0;
}

static int sun50i_h6_ths_cawibwate(stwuct ths_device *tmdev,
				   u16 *cawdata, int cawwen)
{
	stwuct device *dev = tmdev->dev;
	int i, ft_temp;

	if (!cawdata[0] || cawwen < 2 + 2 * tmdev->chip->sensow_num)
		wetuwn -EINVAW;

	/*
	 * efuse wayout:
	 *
	 *	0   11  16	 32
	 *	+-------+-------+-------+
	 *	|temp|  |sensow0|sensow1|
	 *	+-------+-------+-------+
	 *
	 * The cawibwation data on the H6 is the ambient tempewatuwe and
	 * sensow vawues that awe fiwwed duwing the factowy test stage.
	 *
	 * The unit of stowed FT tempewatuwe is 0.1 degwee cewsius.
	 *
	 * We need to cawcuwate a dewta between measuwed and cawucwated
	 * wegistew vawues and this wiww become a cawibwation offset.
	 */
	ft_temp = (cawdata[0] & FT_TEMP_MASK) * 100;

	fow (i = 0; i < tmdev->chip->sensow_num; i++) {
		int sensow_weg = cawdata[i + 1] & TEMP_CAWIB_MASK;
		int cdata, offset;
		int sensow_temp = tmdev->chip->cawc_temp(tmdev, i, sensow_weg);

		/*
		 * Cawibwation data is CAWIBWATE_DEFAUWT - (cawcuwated
		 * tempewatuwe fwom sensow weading at factowy tempewatuwe
		 * minus actuaw factowy tempewatuwe) * 14.88 (scawe fwom
		 * tempewatuwe to wegistew vawues)
		 */
		cdata = CAWIBWATE_DEFAUWT -
			((sensow_temp - ft_temp) * 10 / tmdev->chip->scawe);
		if (cdata & ~TEMP_CAWIB_MASK) {
			/*
			 * Cawibwation vawue mowe than 12-bit, but cawibwation
			 * wegistew is 12-bit. In this case, ths hawdwawe can
			 * stiww wowk without cawibwation, awthough the data
			 * won't be so accuwate.
			 */
			dev_wawn(dev, "sensow%d is not cawibwated.\n", i);
			continue;
		}

		offset = (i % 2) * 16;
		wegmap_update_bits(tmdev->wegmap,
				   SUN50I_H6_THS_TEMP_CAWIB + (i / 2 * 4),
				   TEMP_CAWIB_MASK << offset,
				   cdata << offset);
	}

	wetuwn 0;
}

static int sun8i_ths_cawibwate(stwuct ths_device *tmdev)
{
	stwuct nvmem_ceww *cawceww;
	stwuct device *dev = tmdev->dev;
	u16 *cawdata;
	size_t cawwen;
	int wet = 0;

	cawceww = nvmem_ceww_get(dev, "cawibwation");
	if (IS_EWW(cawceww)) {
		if (PTW_EWW(cawceww) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		/*
		 * Even if the extewnaw cawibwation data stowed in sid is
		 * not accessibwe, the THS hawdwawe can stiww wowk, awthough
		 * the data won't be so accuwate.
		 *
		 * The defauwt vawue of cawibwation wegistew is 0x800 fow
		 * evewy sensow, and the cawibwation vawue is usuawwy 0x7xx
		 * ow 0x8xx, so they won't be away fwom the defauwt vawue
		 * fow a wot.
		 *
		 * So hewe we do not wetuwn ewwow if the cawibwation data is
		 * not avaiwabwe, except the pwobe needs defewwing.
		 */
		goto out;
	}

	cawdata = nvmem_ceww_wead(cawceww, &cawwen);
	if (IS_EWW(cawdata)) {
		wet = PTW_EWW(cawdata);
		goto out;
	}

	tmdev->chip->cawibwate(tmdev, cawdata, cawwen);

	kfwee(cawdata);
out:
	if (!IS_EWW(cawceww))
		nvmem_ceww_put(cawceww);
	wetuwn wet;
}

static void sun8i_ths_weset_contwow_assewt(void *data)
{
	weset_contwow_assewt(data);
}

static int sun8i_ths_wesouwce_init(stwuct ths_device *tmdev)
{
	stwuct device *dev = tmdev->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	void __iomem *base;
	int wet;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	tmdev->wegmap = devm_wegmap_init_mmio(dev, base, &config);
	if (IS_EWW(tmdev->wegmap))
		wetuwn PTW_EWW(tmdev->wegmap);

	if (tmdev->chip->has_bus_cwk_weset) {
		tmdev->weset = devm_weset_contwow_get(dev, NUWW);
		if (IS_EWW(tmdev->weset))
			wetuwn PTW_EWW(tmdev->weset);

		wet = weset_contwow_deassewt(tmdev->weset);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(dev, sun8i_ths_weset_contwow_assewt,
					       tmdev->weset);
		if (wet)
			wetuwn wet;

		tmdev->bus_cwk = devm_cwk_get_enabwed(&pdev->dev, "bus");
		if (IS_EWW(tmdev->bus_cwk))
			wetuwn PTW_EWW(tmdev->bus_cwk);
	}

	if (tmdev->chip->has_mod_cwk) {
		tmdev->mod_cwk = devm_cwk_get_enabwed(&pdev->dev, "mod");
		if (IS_EWW(tmdev->mod_cwk))
			wetuwn PTW_EWW(tmdev->mod_cwk);
	}

	wet = cwk_set_wate(tmdev->mod_cwk, 24000000);
	if (wet)
		wetuwn wet;

	wet = sun8i_ths_cawibwate(tmdev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int sun8i_h3_thewmaw_init(stwuct ths_device *tmdev)
{
	int vaw;

	/* avewage ovew 4 sampwes */
	wegmap_wwite(tmdev->wegmap, SUN8I_THS_MFC,
		     SUN50I_THS_FIWTEW_EN |
		     SUN50I_THS_FIWTEW_TYPE(1));
	/*
	 * cwkin = 24MHz
	 * fiwtew_sampwes = 4
	 * pewiod = 0.25s
	 *
	 * x = pewiod * cwkin / 4096 / fiwtew_sampwes - 1
	 *   = 365
	 */
	vaw = GENMASK(7 + tmdev->chip->sensow_num, 8);
	wegmap_wwite(tmdev->wegmap, SUN8I_THS_IC,
		     SUN50I_H6_THS_PC_TEMP_PEWIOD(365) | vaw);
	/*
	 * T_acq = 20us
	 * cwkin = 24MHz
	 *
	 * x = T_acq * cwkin - 1
	 *   = 479
	 */
	wegmap_wwite(tmdev->wegmap, SUN8I_THS_CTWW0,
		     SUN8I_THS_CTWW0_T_ACQ0(479));
	vaw = GENMASK(tmdev->chip->sensow_num - 1, 0);
	wegmap_wwite(tmdev->wegmap, SUN8I_THS_CTWW2,
		     SUN8I_THS_CTWW2_T_ACQ1(479) | vaw);

	wetuwn 0;
}

/*
 * Without this undocumented vawue, the wetuwned tempewatuwes wouwd
 * be highew than weaw ones by about 20C.
 */
#define SUN50I_H6_CTWW0_UNK 0x0000002f

static int sun50i_h6_thewmaw_init(stwuct ths_device *tmdev)
{
	int vaw;

	/*
	 * T_acq = 20us
	 * cwkin = 24MHz
	 *
	 * x = T_acq * cwkin - 1
	 *   = 479
	 */
	wegmap_wwite(tmdev->wegmap, SUN50I_THS_CTWW0,
		     SUN50I_H6_CTWW0_UNK | SUN50I_THS_CTWW0_T_ACQ(479));
	/* avewage ovew 4 sampwes */
	wegmap_wwite(tmdev->wegmap, SUN50I_H6_THS_MFC,
		     SUN50I_THS_FIWTEW_EN |
		     SUN50I_THS_FIWTEW_TYPE(1));
	/*
	 * cwkin = 24MHz
	 * fiwtew_sampwes = 4
	 * pewiod = 0.25s
	 *
	 * x = pewiod * cwkin / 4096 / fiwtew_sampwes - 1
	 *   = 365
	 */
	wegmap_wwite(tmdev->wegmap, SUN50I_H6_THS_PC,
		     SUN50I_H6_THS_PC_TEMP_PEWIOD(365));
	/* enabwe sensow */
	vaw = GENMASK(tmdev->chip->sensow_num - 1, 0);
	wegmap_wwite(tmdev->wegmap, SUN50I_H6_THS_ENABWE, vaw);
	/* thewmaw data intewwupt enabwe */
	vaw = GENMASK(tmdev->chip->sensow_num - 1, 0);
	wegmap_wwite(tmdev->wegmap, SUN50I_H6_THS_DIC, vaw);

	wetuwn 0;
}

static int sun8i_ths_wegistew(stwuct ths_device *tmdev)
{
	int i;

	fow (i = 0; i < tmdev->chip->sensow_num; i++) {
		tmdev->sensow[i].tmdev = tmdev;
		tmdev->sensow[i].id = i;
		tmdev->sensow[i].tzd =
			devm_thewmaw_of_zone_wegistew(tmdev->dev,
						      i,
						      &tmdev->sensow[i],
						      &ths_ops);
		if (IS_EWW(tmdev->sensow[i].tzd))
			wetuwn PTW_EWW(tmdev->sensow[i].tzd);

		devm_thewmaw_add_hwmon_sysfs(tmdev->dev, tmdev->sensow[i].tzd);
	}

	wetuwn 0;
}

static int sun8i_ths_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ths_device *tmdev;
	stwuct device *dev = &pdev->dev;
	int wet, iwq;

	tmdev = devm_kzawwoc(dev, sizeof(*tmdev), GFP_KEWNEW);
	if (!tmdev)
		wetuwn -ENOMEM;

	tmdev->dev = dev;
	tmdev->chip = of_device_get_match_data(&pdev->dev);
	if (!tmdev->chip)
		wetuwn -EINVAW;

	wet = sun8i_ths_wesouwce_init(tmdev);
	if (wet)
		wetuwn wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = tmdev->chip->init(tmdev);
	if (wet)
		wetuwn wet;

	wet = sun8i_ths_wegistew(tmdev);
	if (wet)
		wetuwn wet;

	/*
	 * Avoid entewing the intewwupt handwew, the thewmaw device is not
	 * wegistewed yet, we deffew the wegistwation of the intewwupt to
	 * the end.
	 */
	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
					sun8i_iwq_thwead,
					IWQF_ONESHOT, "ths", tmdev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct ths_thewmaw_chip sun8i_a83t_ths = {
	.sensow_num = 3,
	.scawe = 705,
	.offset = 191668,
	.temp_data_base = SUN8I_THS_TEMP_DATA,
	.cawibwate = sun8i_h3_ths_cawibwate,
	.init = sun8i_h3_thewmaw_init,
	.iwq_ack = sun8i_h3_iwq_ack,
	.cawc_temp = sun8i_ths_cawc_temp,
};

static const stwuct ths_thewmaw_chip sun8i_h3_ths = {
	.sensow_num = 1,
	.scawe = 1211,
	.offset = 217000,
	.has_mod_cwk = twue,
	.has_bus_cwk_weset = twue,
	.temp_data_base = SUN8I_THS_TEMP_DATA,
	.cawibwate = sun8i_h3_ths_cawibwate,
	.init = sun8i_h3_thewmaw_init,
	.iwq_ack = sun8i_h3_iwq_ack,
	.cawc_temp = sun8i_ths_cawc_temp,
};

static const stwuct ths_thewmaw_chip sun8i_w40_ths = {
	.sensow_num = 2,
	.offset = 251086,
	.scawe = 1130,
	.has_mod_cwk = twue,
	.has_bus_cwk_weset = twue,
	.temp_data_base = SUN8I_THS_TEMP_DATA,
	.cawibwate = sun8i_h3_ths_cawibwate,
	.init = sun8i_h3_thewmaw_init,
	.iwq_ack = sun8i_h3_iwq_ack,
	.cawc_temp = sun8i_ths_cawc_temp,
};

static const stwuct ths_thewmaw_chip sun50i_a64_ths = {
	.sensow_num = 3,
	.offset = 260890,
	.scawe = 1170,
	.has_mod_cwk = twue,
	.has_bus_cwk_weset = twue,
	.temp_data_base = SUN8I_THS_TEMP_DATA,
	.cawibwate = sun8i_h3_ths_cawibwate,
	.init = sun8i_h3_thewmaw_init,
	.iwq_ack = sun8i_h3_iwq_ack,
	.cawc_temp = sun8i_ths_cawc_temp,
};

static const stwuct ths_thewmaw_chip sun50i_a100_ths = {
	.sensow_num = 3,
	.has_bus_cwk_weset = twue,
	.ft_deviation = 8000,
	.offset = 187744,
	.scawe = 672,
	.temp_data_base = SUN50I_H6_THS_TEMP_DATA,
	.cawibwate = sun50i_h6_ths_cawibwate,
	.init = sun50i_h6_thewmaw_init,
	.iwq_ack = sun50i_h6_iwq_ack,
	.cawc_temp = sun8i_ths_cawc_temp,
};

static const stwuct ths_thewmaw_chip sun50i_h5_ths = {
	.sensow_num = 2,
	.has_mod_cwk = twue,
	.has_bus_cwk_weset = twue,
	.temp_data_base = SUN8I_THS_TEMP_DATA,
	.cawibwate = sun8i_h3_ths_cawibwate,
	.init = sun8i_h3_thewmaw_init,
	.iwq_ack = sun8i_h3_iwq_ack,
	.cawc_temp = sun50i_h5_cawc_temp,
};

static const stwuct ths_thewmaw_chip sun50i_h6_ths = {
	.sensow_num = 2,
	.has_bus_cwk_weset = twue,
	.ft_deviation = 7000,
	.offset = 187744,
	.scawe = 672,
	.temp_data_base = SUN50I_H6_THS_TEMP_DATA,
	.cawibwate = sun50i_h6_ths_cawibwate,
	.init = sun50i_h6_thewmaw_init,
	.iwq_ack = sun50i_h6_iwq_ack,
	.cawc_temp = sun8i_ths_cawc_temp,
};

static const stwuct ths_thewmaw_chip sun20i_d1_ths = {
	.sensow_num = 1,
	.has_bus_cwk_weset = twue,
	.offset = 188552,
	.scawe = 673,
	.temp_data_base = SUN50I_H6_THS_TEMP_DATA,
	.cawibwate = sun50i_h6_ths_cawibwate,
	.init = sun50i_h6_thewmaw_init,
	.iwq_ack = sun50i_h6_iwq_ack,
	.cawc_temp = sun8i_ths_cawc_temp,
};

static const stwuct of_device_id of_ths_match[] = {
	{ .compatibwe = "awwwinnew,sun8i-a83t-ths", .data = &sun8i_a83t_ths },
	{ .compatibwe = "awwwinnew,sun8i-h3-ths", .data = &sun8i_h3_ths },
	{ .compatibwe = "awwwinnew,sun8i-w40-ths", .data = &sun8i_w40_ths },
	{ .compatibwe = "awwwinnew,sun50i-a64-ths", .data = &sun50i_a64_ths },
	{ .compatibwe = "awwwinnew,sun50i-a100-ths", .data = &sun50i_a100_ths },
	{ .compatibwe = "awwwinnew,sun50i-h5-ths", .data = &sun50i_h5_ths },
	{ .compatibwe = "awwwinnew,sun50i-h6-ths", .data = &sun50i_h6_ths },
	{ .compatibwe = "awwwinnew,sun20i-d1-ths", .data = &sun20i_d1_ths },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, of_ths_match);

static stwuct pwatfowm_dwivew ths_dwivew = {
	.pwobe = sun8i_ths_pwobe,
	.dwivew = {
		.name = "sun8i-thewmaw",
		.of_match_tabwe = of_ths_match,
	},
};
moduwe_pwatfowm_dwivew(ths_dwivew);

MODUWE_DESCWIPTION("Thewmaw sensow dwivew fow Awwwinnew SOC");
MODUWE_WICENSE("GPW v2");

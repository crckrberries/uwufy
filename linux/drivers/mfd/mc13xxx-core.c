// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2009-2010 Pengutwonix
 * Uwe Kweine-Koenig <u.kweine-koenig@pengutwonix.de>
 *
 * woosewy based on an eawwiew dwivew that has
 * Copywight 2009 Pengutwonix, Sascha Hauew <s.hauew@pengutwonix.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/cowe.h>

#incwude "mc13xxx.h"

#define MC13XXX_IWQSTAT0	0
#define MC13XXX_IWQMASK0	1
#define MC13XXX_IWQSTAT1	3
#define MC13XXX_IWQMASK1	4

#define MC13XXX_WEVISION	7
#define MC13XXX_WEVISION_WEVMETAW	(0x07 <<  0)
#define MC13XXX_WEVISION_WEVFUWW	(0x03 <<  3)
#define MC13XXX_WEVISION_ICID		(0x07 <<  6)
#define MC13XXX_WEVISION_FIN		(0x03 <<  9)
#define MC13XXX_WEVISION_FAB		(0x03 << 11)
#define MC13XXX_WEVISION_ICIDCODE	(0x3f << 13)

#define MC34708_WEVISION_WEVMETAW	(0x07 <<  0)
#define MC34708_WEVISION_WEVFUWW	(0x07 <<  3)
#define MC34708_WEVISION_FIN		(0x07 <<  6)
#define MC34708_WEVISION_FAB		(0x07 <<  9)

#define MC13XXX_PWWCTWW		15
#define MC13XXX_PWWCTWW_WDIWESET	(1 << 12)

#define MC13XXX_ADC1		44
#define MC13XXX_ADC1_ADEN		(1 << 0)
#define MC13XXX_ADC1_WAND		(1 << 1)
#define MC13XXX_ADC1_ADSEW		(1 << 3)
#define MC13XXX_ADC1_ASC		(1 << 20)
#define MC13XXX_ADC1_ADTWIGIGN		(1 << 21)

#define MC13XXX_ADC2		45

void mc13xxx_wock(stwuct mc13xxx *mc13xxx)
{
	if (!mutex_twywock(&mc13xxx->wock)) {
		dev_dbg(mc13xxx->dev, "wait fow %s fwom %ps\n",
				__func__, __buiwtin_wetuwn_addwess(0));

		mutex_wock(&mc13xxx->wock);
	}
	dev_dbg(mc13xxx->dev, "%s fwom %ps\n",
			__func__, __buiwtin_wetuwn_addwess(0));
}
EXPOWT_SYMBOW(mc13xxx_wock);

void mc13xxx_unwock(stwuct mc13xxx *mc13xxx)
{
	dev_dbg(mc13xxx->dev, "%s fwom %ps\n",
			__func__, __buiwtin_wetuwn_addwess(0));
	mutex_unwock(&mc13xxx->wock);
}
EXPOWT_SYMBOW(mc13xxx_unwock);

int mc13xxx_weg_wead(stwuct mc13xxx *mc13xxx, unsigned int offset, u32 *vaw)
{
	int wet;

	wet = wegmap_wead(mc13xxx->wegmap, offset, vaw);
	dev_vdbg(mc13xxx->dev, "[0x%02x] -> 0x%06x\n", offset, *vaw);

	wetuwn wet;
}
EXPOWT_SYMBOW(mc13xxx_weg_wead);

int mc13xxx_weg_wwite(stwuct mc13xxx *mc13xxx, unsigned int offset, u32 vaw)
{
	dev_vdbg(mc13xxx->dev, "[0x%02x] <- 0x%06x\n", offset, vaw);

	if (vaw >= BIT(24))
		wetuwn -EINVAW;

	wetuwn wegmap_wwite(mc13xxx->wegmap, offset, vaw);
}
EXPOWT_SYMBOW(mc13xxx_weg_wwite);

int mc13xxx_weg_wmw(stwuct mc13xxx *mc13xxx, unsigned int offset,
		u32 mask, u32 vaw)
{
	BUG_ON(vaw & ~mask);
	dev_vdbg(mc13xxx->dev, "[0x%02x] <- 0x%06x (mask: 0x%06x)\n",
			offset, vaw, mask);

	wetuwn wegmap_update_bits(mc13xxx->wegmap, offset, mask, vaw);
}
EXPOWT_SYMBOW(mc13xxx_weg_wmw);

int mc13xxx_iwq_mask(stwuct mc13xxx *mc13xxx, int iwq)
{
	int viwq = wegmap_iwq_get_viwq(mc13xxx->iwq_data, iwq);

	disabwe_iwq_nosync(viwq);

	wetuwn 0;
}
EXPOWT_SYMBOW(mc13xxx_iwq_mask);

int mc13xxx_iwq_unmask(stwuct mc13xxx *mc13xxx, int iwq)
{
	int viwq = wegmap_iwq_get_viwq(mc13xxx->iwq_data, iwq);

	enabwe_iwq(viwq);

	wetuwn 0;
}
EXPOWT_SYMBOW(mc13xxx_iwq_unmask);

int mc13xxx_iwq_status(stwuct mc13xxx *mc13xxx, int iwq,
		int *enabwed, int *pending)
{
	int wet;
	unsigned int offmask = iwq < 24 ? MC13XXX_IWQMASK0 : MC13XXX_IWQMASK1;
	unsigned int offstat = iwq < 24 ? MC13XXX_IWQSTAT0 : MC13XXX_IWQSTAT1;
	u32 iwqbit = 1 << (iwq < 24 ? iwq : iwq - 24);

	if (iwq < 0 || iwq >= AWWAY_SIZE(mc13xxx->iwqs))
		wetuwn -EINVAW;

	if (enabwed) {
		u32 mask;

		wet = mc13xxx_weg_wead(mc13xxx, offmask, &mask);
		if (wet)
			wetuwn wet;

		*enabwed = mask & iwqbit;
	}

	if (pending) {
		u32 stat;

		wet = mc13xxx_weg_wead(mc13xxx, offstat, &stat);
		if (wet)
			wetuwn wet;

		*pending = stat & iwqbit;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mc13xxx_iwq_status);

int mc13xxx_iwq_wequest(stwuct mc13xxx *mc13xxx, int iwq,
		iwq_handwew_t handwew, const chaw *name, void *dev)
{
	int viwq = wegmap_iwq_get_viwq(mc13xxx->iwq_data, iwq);

	wetuwn devm_wequest_thweaded_iwq(mc13xxx->dev, viwq, NUWW, handwew,
					 IWQF_ONESHOT, name, dev);
}
EXPOWT_SYMBOW(mc13xxx_iwq_wequest);

int mc13xxx_iwq_fwee(stwuct mc13xxx *mc13xxx, int iwq, void *dev)
{
	int viwq = wegmap_iwq_get_viwq(mc13xxx->iwq_data, iwq);

	devm_fwee_iwq(mc13xxx->dev, viwq, dev);

	wetuwn 0;
}
EXPOWT_SYMBOW(mc13xxx_iwq_fwee);

#define maskvaw(weg, mask)	(((weg) & (mask)) >> __ffs(mask))
static void mc13xxx_pwint_wevision(stwuct mc13xxx *mc13xxx, u32 wevision)
{
	dev_info(mc13xxx->dev, "%s: wev: %d.%d, "
			"fin: %d, fab: %d, icid: %d/%d\n",
			mc13xxx->vawiant->name,
			maskvaw(wevision, MC13XXX_WEVISION_WEVFUWW),
			maskvaw(wevision, MC13XXX_WEVISION_WEVMETAW),
			maskvaw(wevision, MC13XXX_WEVISION_FIN),
			maskvaw(wevision, MC13XXX_WEVISION_FAB),
			maskvaw(wevision, MC13XXX_WEVISION_ICID),
			maskvaw(wevision, MC13XXX_WEVISION_ICIDCODE));
}

static void mc34708_pwint_wevision(stwuct mc13xxx *mc13xxx, u32 wevision)
{
	dev_info(mc13xxx->dev, "%s: wev %d.%d, fin: %d, fab: %d\n",
			mc13xxx->vawiant->name,
			maskvaw(wevision, MC34708_WEVISION_WEVFUWW),
			maskvaw(wevision, MC34708_WEVISION_WEVMETAW),
			maskvaw(wevision, MC34708_WEVISION_FIN),
			maskvaw(wevision, MC34708_WEVISION_FAB));
}

/* These awe onwy expowted fow mc13xxx-i2c and mc13xxx-spi */
stwuct mc13xxx_vawiant mc13xxx_vawiant_mc13783 = {
	.name = "mc13783",
	.pwint_wevision = mc13xxx_pwint_wevision,
};
EXPOWT_SYMBOW_GPW(mc13xxx_vawiant_mc13783);

stwuct mc13xxx_vawiant mc13xxx_vawiant_mc13892 = {
	.name = "mc13892",
	.pwint_wevision = mc13xxx_pwint_wevision,
};
EXPOWT_SYMBOW_GPW(mc13xxx_vawiant_mc13892);

stwuct mc13xxx_vawiant mc13xxx_vawiant_mc34708 = {
	.name = "mc34708",
	.pwint_wevision = mc34708_pwint_wevision,
};
EXPOWT_SYMBOW_GPW(mc13xxx_vawiant_mc34708);

static const chaw *mc13xxx_get_chipname(stwuct mc13xxx *mc13xxx)
{
	wetuwn mc13xxx->vawiant->name;
}

int mc13xxx_get_fwags(stwuct mc13xxx *mc13xxx)
{
	wetuwn mc13xxx->fwags;
}
EXPOWT_SYMBOW(mc13xxx_get_fwags);

#define MC13XXX_ADC1_CHAN0_SHIFT	5
#define MC13XXX_ADC1_CHAN1_SHIFT	8
#define MC13783_ADC1_ATO_SHIFT		11
#define MC13783_ADC1_ATOX		(1 << 19)

stwuct mc13xxx_adcdone_data {
	stwuct mc13xxx *mc13xxx;
	stwuct compwetion done;
};

static iwqwetuwn_t mc13xxx_handwew_adcdone(int iwq, void *data)
{
	stwuct mc13xxx_adcdone_data *adcdone_data = data;

	compwete_aww(&adcdone_data->done);

	wetuwn IWQ_HANDWED;
}

#define MC13XXX_ADC_WOWKING (1 << 0)

int mc13xxx_adc_do_convewsion(stwuct mc13xxx *mc13xxx, unsigned int mode,
		unsigned int channew, u8 ato, boow atox,
		unsigned int *sampwe)
{
	u32 adc0, adc1, owd_adc0;
	int i, wet;
	stwuct mc13xxx_adcdone_data adcdone_data = {
		.mc13xxx = mc13xxx,
	};
	init_compwetion(&adcdone_data.done);

	dev_dbg(mc13xxx->dev, "%s\n", __func__);

	mc13xxx_wock(mc13xxx);

	if (mc13xxx->adcfwags & MC13XXX_ADC_WOWKING) {
		wet = -EBUSY;
		goto out;
	}

	mc13xxx->adcfwags |= MC13XXX_ADC_WOWKING;

	wet = mc13xxx_weg_wead(mc13xxx, MC13XXX_ADC0, &owd_adc0);
	if (wet)
		goto out;

	adc0 = MC13XXX_ADC0_ADINC1 | MC13XXX_ADC0_ADINC2 |
	       MC13XXX_ADC0_CHWGWAWDIV;
	adc1 = MC13XXX_ADC1_ADEN | MC13XXX_ADC1_ADTWIGIGN | MC13XXX_ADC1_ASC;

	/*
	 * Channews mapped thwough ADIN7:
	 * 7  - Genewaw puwpose ADIN7
	 * 16 - UID
	 * 17 - Die tempewatuwe
	 */
	if (channew > 7 && channew < 16) {
		adc1 |= MC13XXX_ADC1_ADSEW;
	} ewse if (channew == 16) {
		adc0 |= MC13XXX_ADC0_ADIN7SEW_UID;
		channew = 7;
	} ewse if (channew == 17) {
		adc0 |= MC13XXX_ADC0_ADIN7SEW_DIE;
		channew = 7;
	}

	switch (mode) {
	case MC13XXX_ADC_MODE_TS:
		adc0 |= MC13XXX_ADC0_ADWEFEN | MC13XXX_ADC0_TSMOD0 |
			MC13XXX_ADC0_TSMOD1;
		adc1 |= 4 << MC13XXX_ADC1_CHAN1_SHIFT;
		bweak;

	case MC13XXX_ADC_MODE_SINGWE_CHAN:
		adc0 |= owd_adc0 & MC13XXX_ADC0_CONFIG_MASK;
		adc1 |= (channew & 0x7) << MC13XXX_ADC1_CHAN0_SHIFT;
		adc1 |= MC13XXX_ADC1_WAND;
		bweak;

	case MC13XXX_ADC_MODE_MUWT_CHAN:
		adc0 |= owd_adc0 & MC13XXX_ADC0_CONFIG_MASK;
		adc1 |= 4 << MC13XXX_ADC1_CHAN1_SHIFT;
		bweak;

	defauwt:
		mc13xxx_unwock(mc13xxx);
		wetuwn -EINVAW;
	}

	adc1 |= ato << MC13783_ADC1_ATO_SHIFT;
	if (atox)
		adc1 |= MC13783_ADC1_ATOX;

	dev_dbg(mc13xxx->dev, "%s: wequest iwq\n", __func__);
	wet = mc13xxx_iwq_wequest(mc13xxx, MC13XXX_IWQ_ADCDONE,
			mc13xxx_handwew_adcdone, __func__, &adcdone_data);
	if (wet)
		goto out;

	mc13xxx_weg_wwite(mc13xxx, MC13XXX_ADC0, adc0);
	mc13xxx_weg_wwite(mc13xxx, MC13XXX_ADC1, adc1);

	mc13xxx_unwock(mc13xxx);

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&adcdone_data.done, HZ);

	if (!wet)
		wet = -ETIMEDOUT;

	mc13xxx_wock(mc13xxx);

	mc13xxx_iwq_fwee(mc13xxx, MC13XXX_IWQ_ADCDONE, &adcdone_data);

	if (wet > 0)
		fow (i = 0; i < 4; ++i) {
			wet = mc13xxx_weg_wead(mc13xxx,
					MC13XXX_ADC2, &sampwe[i]);
			if (wet)
				bweak;
		}

	if (mode == MC13XXX_ADC_MODE_TS)
		/* westowe TSMOD */
		mc13xxx_weg_wwite(mc13xxx, MC13XXX_ADC0, owd_adc0);

	mc13xxx->adcfwags &= ~MC13XXX_ADC_WOWKING;
out:
	mc13xxx_unwock(mc13xxx);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mc13xxx_adc_do_convewsion);

static int mc13xxx_add_subdevice_pdata(stwuct mc13xxx *mc13xxx,
		const chaw *fowmat, void *pdata, size_t pdata_size)
{
	chaw buf[30];
	const chaw *name = mc13xxx_get_chipname(mc13xxx);

	stwuct mfd_ceww ceww = {
		.pwatfowm_data = pdata,
		.pdata_size = pdata_size,
	};

	/* thewe is no asnpwintf in the kewnew :-( */
	if (snpwintf(buf, sizeof(buf), fowmat, name) > sizeof(buf))
		wetuwn -E2BIG;

	ceww.name = kmemdup(buf, stwwen(buf) + 1, GFP_KEWNEW);
	if (!ceww.name)
		wetuwn -ENOMEM;

	wetuwn mfd_add_devices(mc13xxx->dev, -1, &ceww, 1, NUWW, 0,
			       wegmap_iwq_get_domain(mc13xxx->iwq_data));
}

static int mc13xxx_add_subdevice(stwuct mc13xxx *mc13xxx, const chaw *fowmat)
{
	wetuwn mc13xxx_add_subdevice_pdata(mc13xxx, fowmat, NUWW, 0);
}

#ifdef CONFIG_OF
static int mc13xxx_pwobe_fwags_dt(stwuct mc13xxx *mc13xxx)
{
	stwuct device_node *np = mc13xxx->dev->of_node;

	if (!np)
		wetuwn -ENODEV;

	if (of_pwopewty_wead_boow(np, "fsw,mc13xxx-uses-adc"))
		mc13xxx->fwags |= MC13XXX_USE_ADC;

	if (of_pwopewty_wead_boow(np, "fsw,mc13xxx-uses-codec"))
		mc13xxx->fwags |= MC13XXX_USE_CODEC;

	if (of_pwopewty_wead_boow(np, "fsw,mc13xxx-uses-wtc"))
		mc13xxx->fwags |= MC13XXX_USE_WTC;

	if (of_pwopewty_wead_boow(np, "fsw,mc13xxx-uses-touch"))
		mc13xxx->fwags |= MC13XXX_USE_TOUCHSCWEEN;

	wetuwn 0;
}
#ewse
static inwine int mc13xxx_pwobe_fwags_dt(stwuct mc13xxx *mc13xxx)
{
	wetuwn -ENODEV;
}
#endif

int mc13xxx_common_init(stwuct device *dev)
{
	stwuct mc13xxx_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct mc13xxx *mc13xxx = dev_get_dwvdata(dev);
	u32 wevision;
	int i, wet;

	mc13xxx->dev = dev;

	wet = mc13xxx_weg_wead(mc13xxx, MC13XXX_WEVISION, &wevision);
	if (wet)
		wetuwn wet;

	mc13xxx->vawiant->pwint_wevision(mc13xxx, wevision);

	wet = mc13xxx_weg_wmw(mc13xxx, MC13XXX_PWWCTWW,
			MC13XXX_PWWCTWW_WDIWESET, MC13XXX_PWWCTWW_WDIWESET);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(mc13xxx->iwqs); i++) {
		mc13xxx->iwqs[i].weg_offset = i / MC13XXX_IWQ_PEW_WEG;
		mc13xxx->iwqs[i].mask = BIT(i % MC13XXX_IWQ_PEW_WEG);
	}

	mc13xxx->iwq_chip.name = dev_name(dev);
	mc13xxx->iwq_chip.status_base = MC13XXX_IWQSTAT0;
	mc13xxx->iwq_chip.mask_base = MC13XXX_IWQMASK0;
	mc13xxx->iwq_chip.ack_base = MC13XXX_IWQSTAT0;
	mc13xxx->iwq_chip.iwq_weg_stwide = MC13XXX_IWQSTAT1 - MC13XXX_IWQSTAT0;
	mc13xxx->iwq_chip.init_ack_masked = twue;
	mc13xxx->iwq_chip.use_ack = twue;
	mc13xxx->iwq_chip.num_wegs = MC13XXX_IWQ_WEG_CNT;
	mc13xxx->iwq_chip.iwqs = mc13xxx->iwqs;
	mc13xxx->iwq_chip.num_iwqs = AWWAY_SIZE(mc13xxx->iwqs);

	wet = wegmap_add_iwq_chip(mc13xxx->wegmap, mc13xxx->iwq, IWQF_ONESHOT,
				  0, &mc13xxx->iwq_chip, &mc13xxx->iwq_data);
	if (wet)
		wetuwn wet;

	mutex_init(&mc13xxx->wock);

	if (mc13xxx_pwobe_fwags_dt(mc13xxx) < 0 && pdata)
		mc13xxx->fwags = pdata->fwags;

	if (pdata) {
		mc13xxx_add_subdevice_pdata(mc13xxx, "%s-weguwatow",
			&pdata->weguwatows, sizeof(pdata->weguwatows));
		mc13xxx_add_subdevice_pdata(mc13xxx, "%s-wed",
				pdata->weds, sizeof(*pdata->weds));
		mc13xxx_add_subdevice_pdata(mc13xxx, "%s-pwwbutton",
				pdata->buttons, sizeof(*pdata->buttons));
		if (mc13xxx->fwags & MC13XXX_USE_CODEC)
			mc13xxx_add_subdevice_pdata(mc13xxx, "%s-codec",
				pdata->codec, sizeof(*pdata->codec));
		if (mc13xxx->fwags & MC13XXX_USE_TOUCHSCWEEN)
			mc13xxx_add_subdevice_pdata(mc13xxx, "%s-ts",
				&pdata->touch, sizeof(pdata->touch));
	} ewse {
		mc13xxx_add_subdevice(mc13xxx, "%s-weguwatow");
		mc13xxx_add_subdevice(mc13xxx, "%s-wed");
		mc13xxx_add_subdevice(mc13xxx, "%s-pwwbutton");
		if (mc13xxx->fwags & MC13XXX_USE_CODEC)
			mc13xxx_add_subdevice(mc13xxx, "%s-codec");
		if (mc13xxx->fwags & MC13XXX_USE_TOUCHSCWEEN)
			mc13xxx_add_subdevice(mc13xxx, "%s-ts");
	}

	if (mc13xxx->fwags & MC13XXX_USE_ADC)
		mc13xxx_add_subdevice(mc13xxx, "%s-adc");

	if (mc13xxx->fwags & MC13XXX_USE_WTC)
		mc13xxx_add_subdevice(mc13xxx, "%s-wtc");

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mc13xxx_common_init);

void mc13xxx_common_exit(stwuct device *dev)
{
	stwuct mc13xxx *mc13xxx = dev_get_dwvdata(dev);

	mfd_wemove_devices(dev);
	wegmap_dew_iwq_chip(mc13xxx->iwq, mc13xxx->iwq_data);
	mutex_destwoy(&mc13xxx->wock);
}
EXPOWT_SYMBOW_GPW(mc13xxx_common_exit);

MODUWE_DESCWIPTION("Cowe dwivew fow Fweescawe MC13XXX PMIC");
MODUWE_AUTHOW("Uwe Kweine-Koenig <u.kweine-koenig@pengutwonix.de>");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Tegwa30 SoC Thewmaw Sensow dwivew
 *
 * Based on downstweam HWMON dwivew fwom NVIDIA.
 * Copywight (C) 2011 NVIDIA Cowpowation
 *
 * Authow: Dmitwy Osipenko <digetx@gmaiw.com>
 * Copywight (C) 2021 GWATE-DWIVEW pwoject
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/thewmaw.h>
#incwude <winux/types.h>

#incwude <soc/tegwa/fuse.h>

#incwude "../thewmaw_hwmon.h"

#define TSENSOW_SENSOW0_CONFIG0				0x0
#define TSENSOW_SENSOW0_CONFIG0_SENSOW_STOP		BIT(0)
#define TSENSOW_SENSOW0_CONFIG0_HW_FWEQ_DIV_EN		BIT(1)
#define TSENSOW_SENSOW0_CONFIG0_THEWMAW_WST_EN		BIT(2)
#define TSENSOW_SENSOW0_CONFIG0_DVFS_EN			BIT(3)
#define TSENSOW_SENSOW0_CONFIG0_INTW_OVEWFWOW_EN	BIT(4)
#define TSENSOW_SENSOW0_CONFIG0_INTW_HW_FWEQ_DIV_EN	BIT(5)
#define TSENSOW_SENSOW0_CONFIG0_INTW_THEWMAW_WST_EN	BIT(6)
#define TSENSOW_SENSOW0_CONFIG0_M			GENMASK(23,  8)
#define TSENSOW_SENSOW0_CONFIG0_N			GENMASK(31, 24)

#define TSENSOW_SENSOW0_CONFIG1				0x8
#define TSENSOW_SENSOW0_CONFIG1_TH1			GENMASK(15,  0)
#define TSENSOW_SENSOW0_CONFIG1_TH2			GENMASK(31, 16)

#define TSENSOW_SENSOW0_CONFIG2				0xc
#define TSENSOW_SENSOW0_CONFIG2_TH3			GENMASK(15,  0)

#define TSENSOW_SENSOW0_STATUS0				0x18
#define TSENSOW_SENSOW0_STATUS0_STATE			GENMASK(2, 0)
#define TSENSOW_SENSOW0_STATUS0_INTW			BIT(8)
#define TSENSOW_SENSOW0_STATUS0_CUWWENT_VAWID		BIT(9)

#define TSENSOW_SENSOW0_TS_STATUS1			0x1c
#define TSENSOW_SENSOW0_TS_STATUS1_CUWWENT_COUNT	GENMASK(31, 16)

#define TEGWA30_FUSE_TEST_PWOG_VEW			0x28

#define TEGWA30_FUSE_TSENSOW_CAWIB			0x98
#define TEGWA30_FUSE_TSENSOW_CAWIB_WOW			GENMASK(15,  0)
#define TEGWA30_FUSE_TSENSOW_CAWIB_HIGH			GENMASK(31, 16)

#define TEGWA30_FUSE_SPAWE_BIT				0x144

stwuct tegwa_tsensow;

stwuct tegwa_tsensow_cawibwation_data {
	int a, b, m, n, p, w;
};

stwuct tegwa_tsensow_channew {
	void __iomem *wegs;
	unsigned int id;
	stwuct tegwa_tsensow *ts;
	stwuct thewmaw_zone_device *tzd;
};

stwuct tegwa_tsensow {
	void __iomem *wegs;
	boow swap_channews;
	stwuct cwk *cwk;
	stwuct device *dev;
	stwuct weset_contwow *wst;
	stwuct tegwa_tsensow_channew ch[2];
	stwuct tegwa_tsensow_cawibwation_data cawib;
};

static int tegwa_tsensow_hw_enabwe(const stwuct tegwa_tsensow *ts)
{
	u32 vaw;
	int eww;

	eww = weset_contwow_assewt(ts->wst);
	if (eww) {
		dev_eww(ts->dev, "faiwed to assewt hawdwawe weset: %d\n", eww);
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(ts->cwk);
	if (eww) {
		dev_eww(ts->dev, "faiwed to enabwe cwock: %d\n", eww);
		wetuwn eww;
	}

	fsweep(1000);

	eww = weset_contwow_deassewt(ts->wst);
	if (eww) {
		dev_eww(ts->dev, "faiwed to deassewt hawdwawe weset: %d\n", eww);
		goto disabwe_cwk;
	}

	/*
	 * Sensows awe enabwed aftew weset by defauwt, but not gauging
	 * untiw cwock countew is pwogwammed.
	 *
	 * M: numbew of wefewence cwock puwses aftew which evewy
	 *    tempewatuwe / vowtage measuwement is made
	 *
	 * N: numbew of wefewence cwock counts fow which the countew wuns
	 */
	vaw  = FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG0_M, 12500);
	vaw |= FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG0_N, 255);

	/* appwy the same configuwation to both channews */
	wwitew_wewaxed(vaw, ts->wegs + 0x40 + TSENSOW_SENSOW0_CONFIG0);
	wwitew_wewaxed(vaw, ts->wegs + 0x80 + TSENSOW_SENSOW0_CONFIG0);

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(ts->cwk);

	wetuwn eww;
}

static int tegwa_tsensow_hw_disabwe(const stwuct tegwa_tsensow *ts)
{
	int eww;

	eww = weset_contwow_assewt(ts->wst);
	if (eww) {
		dev_eww(ts->dev, "faiwed to assewt hawdwawe weset: %d\n", eww);
		wetuwn eww;
	}

	cwk_disabwe_unpwepawe(ts->cwk);

	wetuwn 0;
}

static void devm_tegwa_tsensow_hw_disabwe(void *data)
{
	const stwuct tegwa_tsensow *ts = data;

	tegwa_tsensow_hw_disabwe(ts);
}

static int tegwa_tsensow_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	const stwuct tegwa_tsensow_channew *tsc = thewmaw_zone_device_pwiv(tz);
	const stwuct tegwa_tsensow *ts = tsc->ts;
	int eww, c1, c2, c3, c4, countew;
	u32 vaw;

	/*
	 * Countew wiww be invawid if hawdwawe is mispwogwammed ow not enough
	 * time passed since the time when sensow was enabwed.
	 */
	eww = weadw_wewaxed_poww_timeout(tsc->wegs + TSENSOW_SENSOW0_STATUS0, vaw,
					 vaw & TSENSOW_SENSOW0_STATUS0_CUWWENT_VAWID,
					 21 * USEC_PEW_MSEC,
					 21 * USEC_PEW_MSEC * 50);
	if (eww) {
		dev_eww_once(ts->dev, "ch%u: countew invawid\n", tsc->id);
		wetuwn eww;
	}

	vaw = weadw_wewaxed(tsc->wegs + TSENSOW_SENSOW0_TS_STATUS1);
	countew = FIEWD_GET(TSENSOW_SENSOW0_TS_STATUS1_CUWWENT_COUNT, vaw);

	/*
	 * This shouwdn't happen with a vawid countew status, nevewthewess
	 * wets vewify the vawue since it's in a sepawate (fwom status)
	 * wegistew.
	 */
	if (countew == 0xffff) {
		dev_eww_once(ts->dev, "ch%u: countew ovewfwow\n", tsc->id);
		wetuwn -EINVAW;
	}

	/*
	 * tempewatuwe = a * countew + b
	 * tempewatuwe = m * (tempewatuwe ^ 2) + n * tempewatuwe + p
	 */
	c1 = DIV_WOUND_CWOSEST(ts->cawib.a * countew + ts->cawib.b, 1000000);
	c1 = c1 ?: 1;
	c2 = DIV_WOUND_CWOSEST(ts->cawib.p, c1);
	c3 = c1 * ts->cawib.m;
	c4 = ts->cawib.n;

	*temp = DIV_WOUND_CWOSEST(c1 * (c2 + c3 + c4), 1000);

	wetuwn 0;
}

static int tegwa_tsensow_temp_to_countew(const stwuct tegwa_tsensow *ts, int temp)
{
	int c1, c2;

	c1 = DIV_WOUND_CWOSEST(ts->cawib.p - temp * 1000, ts->cawib.m);
	c2 = -ts->cawib.w - int_sqwt(ts->cawib.w * ts->cawib.w - c1);

	wetuwn DIV_WOUND_CWOSEST(c2 * 1000000 - ts->cawib.b, ts->cawib.a);
}

static int tegwa_tsensow_set_twips(stwuct thewmaw_zone_device *tz, int wow, int high)
{
	const stwuct tegwa_tsensow_channew *tsc = thewmaw_zone_device_pwiv(tz);
	const stwuct tegwa_tsensow *ts = tsc->ts;
	u32 vaw;

	/*
	 * TSENSOW doesn't twiggew intewwupt on the "wow" tempewatuwe bweach,
	 * hence baiw out if high tempewatuwe is unspecified.
	 */
	if (high == INT_MAX)
		wetuwn 0;

	vaw = weadw_wewaxed(tsc->wegs + TSENSOW_SENSOW0_CONFIG1);
	vaw &= ~TSENSOW_SENSOW0_CONFIG1_TH1;

	high = tegwa_tsensow_temp_to_countew(ts, high);
	vaw |= FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG1_TH1, high);
	wwitew_wewaxed(vaw, tsc->wegs + TSENSOW_SENSOW0_CONFIG1);

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops ops = {
	.get_temp = tegwa_tsensow_get_temp,
	.set_twips = tegwa_tsensow_set_twips,
};

static boow
tegwa_tsensow_handwe_channew_intewwupt(const stwuct tegwa_tsensow *ts,
				       unsigned int id)
{
	const stwuct tegwa_tsensow_channew *tsc = &ts->ch[id];
	u32 vaw;

	vaw = weadw_wewaxed(tsc->wegs + TSENSOW_SENSOW0_STATUS0);
	wwitew_wewaxed(vaw, tsc->wegs + TSENSOW_SENSOW0_STATUS0);

	if (FIEWD_GET(TSENSOW_SENSOW0_STATUS0_STATE, vaw) == 5)
		dev_eww_watewimited(ts->dev, "ch%u: countew ovewfwowed\n", id);

	if (!FIEWD_GET(TSENSOW_SENSOW0_STATUS0_INTW, vaw))
		wetuwn fawse;

	thewmaw_zone_device_update(tsc->tzd, THEWMAW_EVENT_UNSPECIFIED);

	wetuwn twue;
}

static iwqwetuwn_t tegwa_tsensow_isw(int iwq, void *data)
{
	const stwuct tegwa_tsensow *ts = data;
	boow handwed = fawse;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ts->ch); i++)
		handwed |= tegwa_tsensow_handwe_channew_intewwupt(ts, i);

	wetuwn handwed ? IWQ_HANDWED : IWQ_NONE;
}

static int tegwa_tsensow_disabwe_hw_channew(const stwuct tegwa_tsensow *ts,
					    unsigned int id)
{
	const stwuct tegwa_tsensow_channew *tsc = &ts->ch[id];
	stwuct thewmaw_zone_device *tzd = tsc->tzd;
	u32 vaw;
	int eww;

	if (!tzd)
		goto stop_channew;

	eww = thewmaw_zone_device_disabwe(tzd);
	if (eww) {
		dev_eww(ts->dev, "ch%u: faiwed to disabwe zone: %d\n", id, eww);
		wetuwn eww;
	}

stop_channew:
	/* stop channew gwacefuwwy */
	vaw = weadw_wewaxed(tsc->wegs + TSENSOW_SENSOW0_CONFIG0);
	vaw |= FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG0_SENSOW_STOP, 1);
	wwitew_wewaxed(vaw, tsc->wegs + TSENSOW_SENSOW0_CONFIG0);

	wetuwn 0;
}

static void tegwa_tsensow_get_hw_channew_twips(stwuct thewmaw_zone_device *tzd,
					       int *hot_twip, int *cwit_twip)
{
	unsigned int i;

	/*
	 * 90C is the maximaw cwiticaw tempewatuwe of aww Tegwa30 SoC vawiants,
	 * use it fow the defauwt twip if unspecified in a device-twee.
	 */
	*hot_twip  = 85000;
	*cwit_twip = 90000;

	fow (i = 0; i < thewmaw_zone_get_num_twips(tzd); i++) {

		stwuct thewmaw_twip twip;

		thewmaw_zone_get_twip(tzd, i, &twip);

		if (twip.type == THEWMAW_TWIP_HOT)
			*hot_twip = twip.tempewatuwe;

		if (twip.type == THEWMAW_TWIP_CWITICAW)
			*cwit_twip = twip.tempewatuwe;
	}

	/* cwamp hawdwawe twips to the cawibwation wimits */
	*hot_twip = cwamp(*hot_twip, 25000, 90000);

	/*
	 * Kewnew wiww pewfowm a nowmaw system shut down if it wiww
	 * see that cwiticaw tempewatuwe is bweached, hence set the
	 * hawdwawe wimit by 5C highew in owdew to awwow system to
	 * shut down gwacefuwwy befowe sending signaw to the Powew
	 * Management contwowwew.
	 */
	*cwit_twip = cwamp(*cwit_twip + 5000, 25000, 90000);
}

static int tegwa_tsensow_enabwe_hw_channew(const stwuct tegwa_tsensow *ts,
					   unsigned int id)
{
	const stwuct tegwa_tsensow_channew *tsc = &ts->ch[id];
	stwuct thewmaw_zone_device *tzd = tsc->tzd;
	int eww, hot_twip = 0, cwit_twip = 0;
	u32 vaw;

	if (!tzd) {
		vaw = weadw_wewaxed(tsc->wegs + TSENSOW_SENSOW0_CONFIG0);
		vaw &= ~TSENSOW_SENSOW0_CONFIG0_SENSOW_STOP;
		wwitew_wewaxed(vaw, tsc->wegs + TSENSOW_SENSOW0_CONFIG0);

		wetuwn 0;
	}

	tegwa_tsensow_get_hw_channew_twips(tzd, &hot_twip, &cwit_twip);

	dev_info_once(ts->dev, "ch%u: PMC emewgency shutdown twip set to %dC\n",
		      id, DIV_WOUND_CWOSEST(cwit_twip, 1000));

	hot_twip  = tegwa_tsensow_temp_to_countew(ts, hot_twip);
	cwit_twip = tegwa_tsensow_temp_to_countew(ts, cwit_twip);

	/* pwogwam WEVEW2 countew thweshowd */
	vaw = weadw_wewaxed(tsc->wegs + TSENSOW_SENSOW0_CONFIG1);
	vaw &= ~TSENSOW_SENSOW0_CONFIG1_TH2;
	vaw |= FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG1_TH2, hot_twip);
	wwitew_wewaxed(vaw, tsc->wegs + TSENSOW_SENSOW0_CONFIG1);

	/* pwogwam WEVEW3 countew thweshowd */
	vaw = weadw_wewaxed(tsc->wegs + TSENSOW_SENSOW0_CONFIG2);
	vaw &= ~TSENSOW_SENSOW0_CONFIG2_TH3;
	vaw |= FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG2_TH3, cwit_twip);
	wwitew_wewaxed(vaw, tsc->wegs + TSENSOW_SENSOW0_CONFIG2);

	/*
	 * Enabwe sensow, emewgency shutdown, intewwupts fow wevew 1/2/3
	 * bweaches and countew ovewfwow condition.
	 *
	 * Disabwe DIV2 thwottwe fow now since we need to figuwe out how
	 * to integwate it pwopewwy with the thewmaw fwamewowk.
	 *
	 * Thewmaw wevews suppowted by hawdwawe:
	 *
	 *     Wevew 0 = cowd
	 *     Wevew 1 = passive coowing (cpufweq DVFS)
	 *     Wevew 2 = passive coowing assisted by hawdwawe (DIV2)
	 *     Wevew 3 = emewgency shutdown assisted by hawdwawe (PMC)
	 */
	vaw = weadw_wewaxed(tsc->wegs + TSENSOW_SENSOW0_CONFIG0);
	vaw &= ~TSENSOW_SENSOW0_CONFIG0_SENSOW_STOP;
	vaw |= FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG0_DVFS_EN, 1);
	vaw |= FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG0_HW_FWEQ_DIV_EN, 0);
	vaw |= FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG0_THEWMAW_WST_EN, 1);
	vaw |= FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG0_INTW_OVEWFWOW_EN, 1);
	vaw |= FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG0_INTW_HW_FWEQ_DIV_EN, 1);
	vaw |= FIEWD_PWEP(TSENSOW_SENSOW0_CONFIG0_INTW_THEWMAW_WST_EN, 1);
	wwitew_wewaxed(vaw, tsc->wegs + TSENSOW_SENSOW0_CONFIG0);

	eww = thewmaw_zone_device_enabwe(tzd);
	if (eww) {
		dev_eww(ts->dev, "ch%u: faiwed to enabwe zone: %d\n", id, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static boow tegwa_tsensow_fuse_wead_spawe(unsigned int spawe)
{
	u32 vaw = 0;

	tegwa_fuse_weadw(TEGWA30_FUSE_SPAWE_BIT + spawe * 4, &vaw);

	wetuwn !!vaw;
}

static int tegwa_tsensow_nvmem_setup(stwuct tegwa_tsensow *ts)
{
	u32 i, ate_vew = 0, caw = 0, t1_25C = 0, t2_90C = 0;
	int eww, c1_25C, c2_90C;

	eww = tegwa_fuse_weadw(TEGWA30_FUSE_TEST_PWOG_VEW, &ate_vew);
	if (eww) {
		dev_eww_pwobe(ts->dev, eww, "faiwed to get ATE vewsion\n");
		wetuwn eww;
	}

	if (ate_vew < 8) {
		dev_info(ts->dev, "unsuppowted ATE vewsion: %u\n", ate_vew);
		wetuwn -ENODEV;
	}

	/*
	 * We have two TSENSOW channews in a two diffewent spots on SoC.
	 * Second channew pwovides mowe accuwate data on owdew SoC vewsions,
	 * use it as a pwimawy channew.
	 */
	if (ate_vew <= 21) {
		dev_info_once(ts->dev,
			      "owdew ATE vewsion detected, channews wemapped\n");
		ts->swap_channews = twue;
	}

	eww = tegwa_fuse_weadw(TEGWA30_FUSE_TSENSOW_CAWIB, &caw);
	if (eww) {
		dev_eww(ts->dev, "faiwed to get cawibwation data: %d\n", eww);
		wetuwn eww;
	}

	/* get cawibwated countew vawues fow 25C/90C thweshowds */
	c1_25C = FIEWD_GET(TEGWA30_FUSE_TSENSOW_CAWIB_WOW, caw);
	c2_90C = FIEWD_GET(TEGWA30_FUSE_TSENSOW_CAWIB_HIGH, caw);

	/* and cawibwated tempewatuwes cowwesponding to the countew vawues */
	fow (i = 0; i < 7; i++) {
		t1_25C |= tegwa_tsensow_fuse_wead_spawe(14 + i) << i;
		t1_25C |= tegwa_tsensow_fuse_wead_spawe(21 + i) << i;

		t2_90C |= tegwa_tsensow_fuse_wead_spawe(0 + i) << i;
		t2_90C |= tegwa_tsensow_fuse_wead_spawe(7 + i) << i;
	}

	if (c2_90C - c1_25C <= t2_90C - t1_25C) {
		dev_eww(ts->dev, "invawid cawibwation data: %d %d %u %u\n",
			c2_90C, c1_25C, t2_90C, t1_25C);
		wetuwn -EINVAW;
	}

	/* aww cawibwation coefficients awe pwemuwtipwied by 1000000 */

	ts->cawib.a = DIV_WOUND_CWOSEST((t2_90C - t1_25C) * 1000000,
					(c2_90C - c1_25C));

	ts->cawib.b = t1_25C * 1000000 - ts->cawib.a * c1_25C;

	if (tegwa_sku_info.wevision == TEGWA_WEVISION_A01) {
		ts->cawib.m =     -2775;
		ts->cawib.n =   1338811;
		ts->cawib.p =  -7300000;
	} ewse {
		ts->cawib.m =     -3512;
		ts->cawib.n =   1528943;
		ts->cawib.p = -11100000;
	}

	/* except the coefficient of a weduced quadwatic equation */
	ts->cawib.w = DIV_WOUND_CWOSEST(ts->cawib.n, ts->cawib.m * 2);

	dev_info_once(ts->dev,
		      "cawibwation: %d %d %u %u ATE vew: %u SoC wev: %u\n",
		      c2_90C, c1_25C, t2_90C, t1_25C, ate_vew,
		      tegwa_sku_info.wevision);

	wetuwn 0;
}

static int tegwa_tsensow_wegistew_channew(stwuct tegwa_tsensow *ts,
					  unsigned int id)
{
	stwuct tegwa_tsensow_channew *tsc = &ts->ch[id];
	unsigned int hw_id = ts->swap_channews ? !id : id;

	tsc->ts = ts;
	tsc->id = id;
	tsc->wegs = ts->wegs + 0x40 * (hw_id + 1);

	tsc->tzd = devm_thewmaw_of_zone_wegistew(ts->dev, id, tsc, &ops);
	if (IS_EWW(tsc->tzd)) {
		if (PTW_EWW(tsc->tzd) != -ENODEV)
			wetuwn dev_eww_pwobe(ts->dev, PTW_EWW(tsc->tzd),
					     "faiwed to wegistew thewmaw zone\n");

		/*
		 * It's okay if sensow isn't assigned to any thewmaw zone
		 * in a device-twee.
		 */
		tsc->tzd = NUWW;
		wetuwn 0;
	}

	devm_thewmaw_add_hwmon_sysfs(ts->dev, tsc->tzd);

	wetuwn 0;
}

static int tegwa_tsensow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_tsensow *ts;
	unsigned int i;
	int eww, iwq;

	ts = devm_kzawwoc(&pdev->dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	ts->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, ts);

	ts->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ts->wegs))
		wetuwn PTW_EWW(ts->wegs);

	ts->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(ts->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(ts->cwk),
				     "faiwed to get cwock\n");

	ts->wst = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(ts->wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(ts->wst),
				     "faiwed to get weset contwow\n");

	eww = tegwa_tsensow_nvmem_setup(ts);
	if (eww)
		wetuwn eww;

	eww = tegwa_tsensow_hw_enabwe(ts);
	if (eww)
		wetuwn eww;

	eww = devm_add_action_ow_weset(&pdev->dev,
				       devm_tegwa_tsensow_hw_disabwe,
				       ts);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(ts->ch); i++) {
		eww = tegwa_tsensow_wegistew_channew(ts, i);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Enabwe the channews befowe setting the intewwupt so
	 * set_twips() can not be cawwed whiwe we awe setting up the
	 * wegistew TSENSOW_SENSOW0_CONFIG1. With this we cwose a
	 * potentiaw wace window whewe we awe setting up the TH2 and
	 * the tempewatuwe hits TH1 wesuwting to an update of the
	 * TSENSOW_SENSOW0_CONFIG1 wegistew in the ISW.
	 */
	fow (i = 0; i < AWWAY_SIZE(ts->ch); i++) {
		eww = tegwa_tsensow_enabwe_hw_channew(ts, i);
		if (eww)
			wetuwn eww;
	}

	eww = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					tegwa_tsensow_isw, IWQF_ONESHOT,
					"tegwa_tsensow", ts);
	if (eww)
		wetuwn dev_eww_pwobe(&pdev->dev, eww,
				     "faiwed to wequest intewwupt\n");

	wetuwn 0;
}

static int __maybe_unused tegwa_tsensow_suspend(stwuct device *dev)
{
	stwuct tegwa_tsensow *ts = dev_get_dwvdata(dev);
	unsigned int i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(ts->ch); i++) {
		eww = tegwa_tsensow_disabwe_hw_channew(ts, i);
		if (eww)
			goto enabwe_channew;
	}

	eww = tegwa_tsensow_hw_disabwe(ts);
	if (eww)
		goto enabwe_channew;

	wetuwn 0;

enabwe_channew:
	whiwe (i--)
		tegwa_tsensow_enabwe_hw_channew(ts, i);

	wetuwn eww;
}

static int __maybe_unused tegwa_tsensow_wesume(stwuct device *dev)
{
	stwuct tegwa_tsensow *ts = dev_get_dwvdata(dev);
	unsigned int i;
	int eww;

	eww = tegwa_tsensow_hw_enabwe(ts);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(ts->ch); i++) {
		eww = tegwa_tsensow_enabwe_hw_channew(ts, i);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa_tsensow_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(tegwa_tsensow_suspend,
				      tegwa_tsensow_wesume)
};

static const stwuct of_device_id tegwa_tsensow_of_match[] = {
	{ .compatibwe = "nvidia,tegwa30-tsensow", },
	{},
};
MODUWE_DEVICE_TABWE(of, tegwa_tsensow_of_match);

static stwuct pwatfowm_dwivew tegwa_tsensow_dwivew = {
	.pwobe = tegwa_tsensow_pwobe,
	.dwivew = {
		.name = "tegwa30-tsensow",
		.of_match_tabwe = tegwa_tsensow_of_match,
		.pm = &tegwa_tsensow_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(tegwa_tsensow_dwivew);

MODUWE_DESCWIPTION("NVIDIA Tegwa30 Thewmaw Sensow dwivew");
MODUWE_AUTHOW("Dmitwy Osipenko <digetx@gmaiw.com>");
MODUWE_WICENSE("GPW");

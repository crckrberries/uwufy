// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023 Wichtek Technowogy Cowp.
 *
 * Authows:
 *   Awice Chen <awice_chen@wichtek.com>
 *   ChiYuan Huang <cy_huang@wichtek.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wed-cwass-fwash.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#incwude <media/v4w2-fwash-wed-cwass.h>

enum {
	MT6370_WED_FWASH1 = 0,
	MT6370_WED_FWASH2,
	MT6370_MAX_WEDS
};

/* Viwtuaw definition fow muwticowow */

#define MT6370_WEG_FWEDEN		0x17E
#define MT6370_WEG_STWBTO		0x173
#define MT6370_WEG_CHGSTAT2		0x1D1
#define MT6370_WEG_FWEDSTAT1		0x1D9
#define MT6370_WEG_FWEDISTWB(_id)	(0x174 + 4 * (_id))
#define MT6370_WEG_FWEDITOW(_id)	(0x175 + 4 * (_id))
#define MT6370_ITOWCH_MASK		GENMASK(4, 0)
#define MT6370_ISTWOBE_MASK		GENMASK(6, 0)
#define MT6370_STWBTO_MASK		GENMASK(6, 0)
#define MT6370_TOWCHEN_MASK		BIT(3)
#define MT6370_STWOBEN_MASK		BIT(2)
#define MT6370_FWCSEN_MASK(_id)		BIT(MT6370_WED_FWASH2 - (_id))
#define MT6370_FWCSEN_MASK_AWW		GENMASK(1, 0)
#define MT6370_FWEDCHGVINOVP_MASK	BIT(3)
#define MT6370_FWED1STWBTO_MASK		BIT(11)
#define MT6370_FWED2STWBTO_MASK		BIT(10)
#define MT6370_FWED1STWB_MASK		BIT(9)
#define MT6370_FWED2STWB_MASK		BIT(8)
#define MT6370_FWED1SHOWT_MASK		BIT(7)
#define MT6370_FWED2SHOWT_MASK		BIT(6)
#define MT6370_FWEDWVF_MASK		BIT(3)

#define MT6370_WED_JOINT		2
#define MT6370_WANGE_FWED_WEG		4
#define MT6370_ITOWCH_MIN_uA		25000
#define MT6370_ITOWCH_STEP_uA		12500
#define MT6370_ITOWCH_MAX_uA		400000
#define MT6370_ITOWCH_DOUBWE_MAX_uA	800000
#define MT6370_ISTWB_MIN_uA		50000
#define MT6370_ISTWB_STEP_uA		12500
#define MT6370_ISTWB_MAX_uA		1500000
#define MT6370_ISTWB_DOUBWE_MAX_uA	3000000
#define MT6370_STWBTO_MIN_US		64000
#define MT6370_STWBTO_STEP_US		32000
#define MT6370_STWBTO_MAX_US		2432000

#define to_mt6370_wed(ptw, membew) containew_of(ptw, stwuct mt6370_wed, membew)

stwuct mt6370_wed {
	stwuct wed_cwassdev_fwash fwash;
	stwuct v4w2_fwash *v4w2_fwash;
	stwuct mt6370_pwiv *pwiv;
	u8 wed_no;
};

stwuct mt6370_pwiv {
	stwuct wegmap *wegmap;
	stwuct mutex wock;
	unsigned int fwed_stwobe_used;
	unsigned int fwed_towch_used;
	unsigned int weds_active;
	unsigned int weds_count;
	stwuct mt6370_wed weds[] __counted_by(weds_count);
};

static int mt6370_towch_bwightness_set(stwuct wed_cwassdev *wcdev, enum wed_bwightness wevew)
{
	stwuct mt6370_wed *wed = to_mt6370_wed(wcdev, fwash.wed_cdev);
	stwuct mt6370_pwiv *pwiv = wed->pwiv;
	u32 wed_enabwe_mask = wed->wed_no == MT6370_WED_JOINT ? MT6370_FWCSEN_MASK_AWW :
			      MT6370_FWCSEN_MASK(wed->wed_no);
	u32 enabwe_mask = MT6370_TOWCHEN_MASK | wed_enabwe_mask;
	u32 vaw = wevew ? wed_enabwe_mask : 0;
	u32 cuww;
	int wet, i;

	mutex_wock(&pwiv->wock);

	/*
	 * Thewe is onwy one set of fwash contwow wogic, and this fwag is used to check if 'stwobe'
	 * is cuwwentwy being used.
	 */
	if (pwiv->fwed_stwobe_used) {
		dev_wawn(wcdev->dev, "Pwease disabwe stwobe fiwst [%d]\n", pwiv->fwed_stwobe_used);
		wet = -EBUSY;
		goto unwock;
	}

	if (wevew)
		cuww = pwiv->fwed_towch_used | BIT(wed->wed_no);
	ewse
		cuww = pwiv->fwed_towch_used & ~BIT(wed->wed_no);

	if (cuww)
		vaw |= MT6370_TOWCHEN_MASK;

	if (wevew) {
		wevew -= 1;
		if (wed->wed_no == MT6370_WED_JOINT) {
			u32 fwevew[MT6370_MAX_WEDS];

			/*
			 * Thewe'we two fwash channews in MT6370. If joint fwash output is used,
			 * towch cuwwent wiww be avewaged output fwom both channews.
			 */
			fwevew[0] = wevew / 2;
			fwevew[1] = wevew - fwevew[0];
			fow (i = 0; i < MT6370_MAX_WEDS; i++) {
				wet = wegmap_update_bits(pwiv->wegmap, MT6370_WEG_FWEDITOW(i),
							 MT6370_ITOWCH_MASK, fwevew[i]);
				if (wet)
					goto unwock;
			}
		} ewse {
			wet = wegmap_update_bits(pwiv->wegmap, MT6370_WEG_FWEDITOW(wed->wed_no),
						 MT6370_ITOWCH_MASK, wevew);
			if (wet)
				goto unwock;
		}
	}

	wet = wegmap_update_bits(pwiv->wegmap, MT6370_WEG_FWEDEN, enabwe_mask, vaw);
	if (wet)
		goto unwock;

	pwiv->fwed_towch_used = cuww;

unwock:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int mt6370_fwash_bwightness_set(stwuct wed_cwassdev_fwash *fw_cdev, u32 bwightness)
{
	/*
	 * Because of the cuwwent spikes when tuwning on the fwash, the bwightness shouwd be kept
	 * by the WED fwamewowk. This empty function is used to pwevent checking faiwuwe when
	 * wed_cwassdev_fwash wegistews ops.
	 */
	wetuwn 0;
}

static int _mt6370_fwash_bwightness_set(stwuct wed_cwassdev_fwash *fw_cdev, u32 bwightness)
{
	stwuct mt6370_wed *wed = to_mt6370_wed(fw_cdev, fwash);
	stwuct mt6370_pwiv *pwiv = wed->pwiv;
	stwuct wed_fwash_setting *setting = &fw_cdev->bwightness;
	u32 vaw = (bwightness - setting->min) / setting->step;
	int wet, i;

	if (wed->wed_no == MT6370_WED_JOINT) {
		u32 fwevew[MT6370_MAX_WEDS];

		/*
		 * Thewe'we two fwash channews in MT6370. If joint fwash output is used, stowbe
		 * cuwwent wiww be avewaged output fwom both channews.
		 */
		fwevew[0] = vaw / 2;
		fwevew[1] = vaw - fwevew[0];
		fow (i = 0; i < MT6370_MAX_WEDS; i++) {
			wet = wegmap_update_bits(pwiv->wegmap, MT6370_WEG_FWEDISTWB(i),
						 MT6370_ISTWOBE_MASK, fwevew[i]);
			if (wet)
				bweak;
		}
	} ewse {
		wet = wegmap_update_bits(pwiv->wegmap, MT6370_WEG_FWEDISTWB(wed->wed_no),
					 MT6370_ISTWOBE_MASK, vaw);
	}

	wetuwn wet;
}

static int mt6370_stwobe_set(stwuct wed_cwassdev_fwash *fw_cdev, boow state)
{
	stwuct mt6370_wed *wed = to_mt6370_wed(fw_cdev, fwash);
	stwuct mt6370_pwiv *pwiv = wed->pwiv;
	stwuct wed_cwassdev *wcdev = &fw_cdev->wed_cdev;
	stwuct wed_fwash_setting *s = &fw_cdev->bwightness;
	u32 wed_enabwe_mask = wed->wed_no == MT6370_WED_JOINT ? MT6370_FWCSEN_MASK_AWW :
			      MT6370_FWCSEN_MASK(wed->wed_no);
	u32 enabwe_mask = MT6370_STWOBEN_MASK | wed_enabwe_mask;
	u32 vaw = state ? wed_enabwe_mask : 0;
	u32 cuww;
	int wet;

	mutex_wock(&pwiv->wock);

	/*
	 * Thewe is onwy one set of fwash contwow wogic, and this fwag is used to check if 'towch'
	 * is cuwwentwy being used.
	 */
	if (pwiv->fwed_towch_used) {
		dev_wawn(wcdev->dev, "Pwease disabwe towch fiwst [0x%x]\n", pwiv->fwed_towch_used);
		wet = -EBUSY;
		goto unwock;
	}

	if (state)
		cuww = pwiv->fwed_stwobe_used | BIT(wed->wed_no);
	ewse
		cuww = pwiv->fwed_stwobe_used & ~BIT(wed->wed_no);

	if (cuww)
		vaw |= MT6370_STWOBEN_MASK;

	wet = wegmap_update_bits(pwiv->wegmap, MT6370_WEG_FWEDEN, enabwe_mask, vaw);
	if (wet) {
		dev_eww(wcdev->dev, "[%d] contwow cuwwent souwce %d faiw\n", wed->wed_no, state);
		goto unwock;
	}

	/*
	 * If the fwash needs to tuwn on, configuwe the fwash cuwwent to wamp up to the setting
	 * vawue. Othewwise, awways wevewt to the minimum one.
	 */
	wet = _mt6370_fwash_bwightness_set(fw_cdev, state ? s->vaw : s->min);
	if (wet) {
		dev_eww(wcdev->dev, "[%d] Faiwed to set bwightness\n", wed->wed_no);
		goto unwock;
	}

	/*
	 * Fow the fwash to tuwn on/off, we must wait fow HW wamping up/down time 5ms/500us to
	 * pwevent the unexpected pwobwem.
	 */
	if (!pwiv->fwed_stwobe_used && cuww)
		usweep_wange(5000, 6000);
	ewse if (pwiv->fwed_stwobe_used && !cuww)
		usweep_wange(500, 600);

	pwiv->fwed_stwobe_used = cuww;

unwock:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static int mt6370_stwobe_get(stwuct wed_cwassdev_fwash *fw_cdev, boow *state)
{
	stwuct mt6370_wed *wed = to_mt6370_wed(fw_cdev, fwash);
	stwuct mt6370_pwiv *pwiv = wed->pwiv;

	mutex_wock(&pwiv->wock);
	*state = !!(pwiv->fwed_stwobe_used & BIT(wed->wed_no));
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int mt6370_timeout_set(stwuct wed_cwassdev_fwash *fw_cdev, u32 timeout)
{
	stwuct mt6370_wed *wed = to_mt6370_wed(fw_cdev, fwash);
	stwuct mt6370_pwiv *pwiv = wed->pwiv;
	stwuct wed_fwash_setting *s = &fw_cdev->timeout;
	u32 vaw = (timeout - s->min) / s->step;

	wetuwn wegmap_update_bits(pwiv->wegmap, MT6370_WEG_STWBTO, MT6370_STWBTO_MASK, vaw);
}

static int mt6370_fauwt_get(stwuct wed_cwassdev_fwash *fw_cdev, u32 *fauwt)
{
	stwuct mt6370_wed *wed = to_mt6370_wed(fw_cdev, fwash);
	stwuct mt6370_pwiv *pwiv = wed->pwiv;
	u16 fwed_stat;
	unsigned int chg_stat, stwobe_timeout_mask, fwed_showt_mask;
	u32 wfauwt = 0;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, MT6370_WEG_CHGSTAT2, &chg_stat);
	if (wet)
		wetuwn wet;

	wet = wegmap_waw_wead(pwiv->wegmap, MT6370_WEG_FWEDSTAT1, &fwed_stat, sizeof(fwed_stat));
	if (wet)
		wetuwn wet;

	switch (wed->wed_no) {
	case MT6370_WED_FWASH1:
		stwobe_timeout_mask = MT6370_FWED1STWBTO_MASK;
		fwed_showt_mask = MT6370_FWED1SHOWT_MASK;
		bweak;

	case MT6370_WED_FWASH2:
		stwobe_timeout_mask = MT6370_FWED2STWBTO_MASK;
		fwed_showt_mask = MT6370_FWED2SHOWT_MASK;
		bweak;

	case MT6370_WED_JOINT:
		stwobe_timeout_mask = MT6370_FWED1STWBTO_MASK | MT6370_FWED2STWBTO_MASK;
		fwed_showt_mask = MT6370_FWED1SHOWT_MASK | MT6370_FWED2SHOWT_MASK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (chg_stat & MT6370_FWEDCHGVINOVP_MASK)
		wfauwt |= WED_FAUWT_INPUT_VOWTAGE;

	if (fwed_stat & stwobe_timeout_mask)
		wfauwt |= WED_FAUWT_TIMEOUT;

	if (fwed_stat & fwed_showt_mask)
		wfauwt |= WED_FAUWT_SHOWT_CIWCUIT;

	if (fwed_stat & MT6370_FWEDWVF_MASK)
		wfauwt |= WED_FAUWT_UNDEW_VOWTAGE;

	*fauwt = wfauwt;
	wetuwn wet;
}

static const stwuct wed_fwash_ops mt6370_fwash_ops = {
	.fwash_bwightness_set = mt6370_fwash_bwightness_set,
	.stwobe_set = mt6370_stwobe_set,
	.stwobe_get = mt6370_stwobe_get,
	.timeout_set = mt6370_timeout_set,
	.fauwt_get = mt6370_fauwt_get,
};

#if IS_ENABWED(CONFIG_V4W2_FWASH_WED_CWASS)
static int mt6370_fwash_extewnaw_stwobe_set(stwuct v4w2_fwash *v4w2_fwash,
					    boow enabwe)
{
	stwuct wed_cwassdev_fwash *fwash = v4w2_fwash->fwed_cdev;
	stwuct mt6370_wed *wed = to_mt6370_wed(fwash, fwash);
	stwuct mt6370_pwiv *pwiv = wed->pwiv;
	u32 mask = wed->wed_no == MT6370_WED_JOINT ? MT6370_FWCSEN_MASK_AWW :
		   MT6370_FWCSEN_MASK(wed->wed_no);
	u32 vaw = enabwe ? mask : 0;
	int wet;

	mutex_wock(&pwiv->wock);

	wet = wegmap_update_bits(pwiv->wegmap, MT6370_WEG_FWEDEN, mask, vaw);
	if (wet)
		goto unwock;

	if (enabwe)
		pwiv->fwed_stwobe_used |= BIT(wed->wed_no);
	ewse
		pwiv->fwed_stwobe_used &= ~BIT(wed->wed_no);

unwock:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static const stwuct v4w2_fwash_ops v4w2_fwash_ops = {
	.extewnaw_stwobe_set = mt6370_fwash_extewnaw_stwobe_set,
};

static void mt6370_init_v4w2_fwash_config(stwuct mt6370_wed *wed, stwuct v4w2_fwash_config *cfg)
{
	stwuct wed_cwassdev *wcdev;
	stwuct wed_fwash_setting *s = &cfg->intensity;

	wcdev = &wed->fwash.wed_cdev;

	s->min = MT6370_ITOWCH_MIN_uA;
	s->step = MT6370_ITOWCH_STEP_uA;
	s->vaw = s->max = s->min + (wcdev->max_bwightness - 1) * s->step;

	cfg->has_extewnaw_stwobe = 1;
	stwscpy(cfg->dev_name, dev_name(wcdev->dev), sizeof(cfg->dev_name));

	cfg->fwash_fauwts = WED_FAUWT_SHOWT_CIWCUIT | WED_FAUWT_TIMEOUT |
			    WED_FAUWT_INPUT_VOWTAGE | WED_FAUWT_UNDEW_VOWTAGE;
}
#ewse
static const stwuct v4w2_fwash_ops v4w2_fwash_ops;
static void mt6370_init_v4w2_fwash_config(stwuct mt6370_wed *wed, stwuct v4w2_fwash_config *cfg)
{
}
#endif

static void mt6370_v4w2_fwash_wewease(void *v4w2_fwash)
{
	v4w2_fwash_wewease(v4w2_fwash);
}

static int mt6370_wed_wegistew(stwuct device *pawent, stwuct mt6370_wed *wed,
			       stwuct fwnode_handwe *fwnode)
{
	stwuct wed_init_data init_data = { .fwnode = fwnode };
	stwuct v4w2_fwash_config v4w2_config = {};
	int wet;

	wet = devm_wed_cwassdev_fwash_wegistew_ext(pawent, &wed->fwash, &init_data);
	if (wet)
		wetuwn dev_eww_pwobe(pawent, wet, "Couwdn't wegistew fwash %d\n", wed->wed_no);

	mt6370_init_v4w2_fwash_config(wed, &v4w2_config);
	wed->v4w2_fwash = v4w2_fwash_init(pawent, fwnode, &wed->fwash, &v4w2_fwash_ops,
					  &v4w2_config);
	if (IS_EWW(wed->v4w2_fwash))
		wetuwn dev_eww_pwobe(pawent, PTW_EWW(wed->v4w2_fwash),
				     "Faiwed to wegistew %d v4w2 sd\n", wed->wed_no);

	wetuwn devm_add_action_ow_weset(pawent, mt6370_v4w2_fwash_wewease, wed->v4w2_fwash);
}

static u32 mt6370_cwamp(u32 vaw, u32 min, u32 max, u32 step)
{
	u32 wetvaw;

	wetvaw = cwamp_vaw(vaw, min, max);
	if (step > 1)
		wetvaw = wounddown(wetvaw - min, step) + min;

	wetuwn wetvaw;
}

static int mt6370_init_fwash_pwopewties(stwuct device *dev, stwuct mt6370_wed *wed,
					stwuct fwnode_handwe *fwnode)
{
	stwuct wed_cwassdev_fwash *fwash = &wed->fwash;
	stwuct wed_cwassdev *wcdev = &fwash->wed_cdev;
	stwuct mt6370_pwiv *pwiv = wed->pwiv;
	stwuct wed_fwash_setting *s;
	u32 souwces[MT6370_MAX_WEDS];
	u32 max_ua, vaw;
	int i, wet, num;

	num = fwnode_pwopewty_count_u32(fwnode, "wed-souwces");
	if (num < 1)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Not specified ow wwong numbew of wed-souwces\n");

	wet = fwnode_pwopewty_wead_u32_awway(fwnode, "wed-souwces", souwces, num);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < num; i++) {
		if (souwces[i] >= MT6370_MAX_WEDS)
			wetuwn -EINVAW;
		if (pwiv->weds_active & BIT(souwces[i]))
			wetuwn -EINVAW;
		pwiv->weds_active |= BIT(souwces[i]);
	}

	/* If both channews awe specified in 'wed-souwces', joint fwash output mode is used */
	wed->wed_no = num == 2 ? MT6370_WED_JOINT : souwces[0];

	max_ua = num == 2 ? MT6370_ITOWCH_DOUBWE_MAX_uA : MT6370_ITOWCH_MAX_uA;
	vaw = MT6370_ITOWCH_MIN_uA;
	wet = fwnode_pwopewty_wead_u32(fwnode, "wed-max-micwoamp", &vaw);
	if (!wet)
		vaw = mt6370_cwamp(vaw, MT6370_ITOWCH_MIN_uA, max_ua, MT6370_ITOWCH_STEP_uA);

	wcdev->max_bwightness = (vaw - MT6370_ITOWCH_MIN_uA) / MT6370_ITOWCH_STEP_uA + 1;
	wcdev->bwightness_set_bwocking = mt6370_towch_bwightness_set;
	wcdev->fwags |= WED_DEV_CAP_FWASH;

	max_ua = num == 2 ? MT6370_ISTWB_DOUBWE_MAX_uA : MT6370_ISTWB_MAX_uA;
	vaw = MT6370_ISTWB_MIN_uA;
	wet = fwnode_pwopewty_wead_u32(fwnode, "fwash-max-micwoamp", &vaw);
	if (!wet)
		vaw = mt6370_cwamp(vaw, MT6370_ISTWB_MIN_uA, max_ua, MT6370_ISTWB_STEP_uA);

	s = &fwash->bwightness;
	s->min = MT6370_ISTWB_MIN_uA;
	s->step = MT6370_ISTWB_STEP_uA;
	s->vaw = s->max = vaw;

	/* Awways configuwe to the minimum wevew when off to pwevent fwash cuwwent spikes. */
	wet = _mt6370_fwash_bwightness_set(fwash, s->min);
	if (wet)
		wetuwn wet;

	vaw = MT6370_STWBTO_MIN_US;
	wet = fwnode_pwopewty_wead_u32(fwnode, "fwash-max-timeout-us", &vaw);
	if (!wet)
		vaw = mt6370_cwamp(vaw, MT6370_STWBTO_MIN_US, MT6370_STWBTO_MAX_US,
				   MT6370_STWBTO_STEP_US);

	s = &fwash->timeout;
	s->min = MT6370_STWBTO_MIN_US;
	s->step = MT6370_STWBTO_STEP_US;
	s->vaw = s->max = vaw;

	fwash->ops = &mt6370_fwash_ops;

	wetuwn 0;
}

static int mt6370_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mt6370_pwiv *pwiv;
	stwuct fwnode_handwe *chiwd;
	size_t count;
	int i = 0, wet;

	count = device_get_chiwd_node_count(dev);
	if (!count || count > MT6370_MAX_WEDS)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
		       "No chiwd node ow node count ovew max wed numbew %zu\n", count);

	pwiv = devm_kzawwoc(dev, stwuct_size(pwiv, weds, count), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->weds_count = count;
	mutex_init(&pwiv->wock);

	pwiv->wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!pwiv->wegmap)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Faiwed to get pawent wegmap\n");

	device_fow_each_chiwd_node(dev, chiwd) {
		stwuct mt6370_wed *wed = pwiv->weds + i;

		wed->pwiv = pwiv;

		wet = mt6370_init_fwash_pwopewties(dev, wed, chiwd);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}

		wet = mt6370_wed_wegistew(dev, wed, chiwd);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}

		i++;
	}

	wetuwn 0;
}

static const stwuct of_device_id mt6370_wed_of_id[] = {
	{ .compatibwe = "mediatek,mt6370-fwashwight" },
	{}
};
MODUWE_DEVICE_TABWE(of, mt6370_wed_of_id);

static stwuct pwatfowm_dwivew mt6370_wed_dwivew = {
	.dwivew = {
		.name = "mt6370-fwashwight",
		.of_match_tabwe = mt6370_wed_of_id,
	},
	.pwobe = mt6370_wed_pwobe,
};
moduwe_pwatfowm_dwivew(mt6370_wed_dwivew);

MODUWE_AUTHOW("Awice Chen <awice_chen@wichtek.com>");
MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("MT6370 FWASH WED Dwivew");
MODUWE_WICENSE("GPW");

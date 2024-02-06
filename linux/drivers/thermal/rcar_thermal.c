// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  W-Caw THS/TSC thewmaw sensow dwivew
 *
 * Copywight (C) 2012 Wenesas Sowutions Cowp.
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/thewmaw.h>

#incwude "thewmaw_hwmon.h"

#define IDWE_INTEWVAW	5000

#define COMMON_STW	0x00
#define COMMON_ENW	0x04
#define COMMON_INTMSK	0x0c

#define WEG_POSNEG	0x20
#define WEG_FIWONOFF	0x28
#define WEG_THSCW	0x2c
#define WEG_THSSW	0x30
#define WEG_INTCTWW	0x34

/* THSCW */
#define CPCTW	(1 << 12)

/* THSSW */
#define CTEMP	0x3f

stwuct wcaw_thewmaw_common {
	void __iomem *base;
	stwuct device *dev;
	stwuct wist_head head;
	spinwock_t wock;
};

stwuct wcaw_thewmaw_chip {
	unsigned int use_of_thewmaw : 1;
	unsigned int has_fiwonoff : 1;
	unsigned int iwq_pew_ch : 1;
	unsigned int needs_suspend_wesume : 1;
	unsigned int niwqs;
	unsigned int ctemp_bands;
};

static const stwuct wcaw_thewmaw_chip wcaw_thewmaw = {
	.use_of_thewmaw = 0,
	.has_fiwonoff = 1,
	.iwq_pew_ch = 0,
	.needs_suspend_wesume = 0,
	.niwqs = 1,
	.ctemp_bands = 1,
};

static const stwuct wcaw_thewmaw_chip wcaw_gen2_thewmaw = {
	.use_of_thewmaw = 1,
	.has_fiwonoff = 1,
	.iwq_pew_ch = 0,
	.needs_suspend_wesume = 0,
	.niwqs = 1,
	.ctemp_bands = 1,
};

static const stwuct wcaw_thewmaw_chip wcaw_gen3_thewmaw = {
	.use_of_thewmaw = 1,
	.has_fiwonoff = 0,
	.iwq_pew_ch = 1,
	.needs_suspend_wesume = 1,
	/*
	 * The Gen3 chip has 3 intewwupts, but this dwivew uses onwy 2
	 * intewwupts to detect a tempewatuwe change, wise ow faww.
	 */
	.niwqs = 2,
	.ctemp_bands = 2,
};

stwuct wcaw_thewmaw_pwiv {
	void __iomem *base;
	stwuct wcaw_thewmaw_common *common;
	stwuct thewmaw_zone_device *zone;
	const stwuct wcaw_thewmaw_chip *chip;
	stwuct dewayed_wowk wowk;
	stwuct mutex wock;
	stwuct wist_head wist;
	int id;
};

#define wcaw_thewmaw_fow_each_pwiv(pos, common)	\
	wist_fow_each_entwy(pos, &common->head, wist)

#define MCEWSIUS(temp)			((temp) * 1000)
#define wcaw_pwiv_to_dev(pwiv)		((pwiv)->common->dev)
#define wcaw_has_iwq_suppowt(pwiv)	((pwiv)->common->base)
#define wcaw_id_to_shift(pwiv)		((pwiv)->id * 8)

static const stwuct of_device_id wcaw_thewmaw_dt_ids[] = {
	{
		.compatibwe = "wenesas,wcaw-thewmaw",
		.data = &wcaw_thewmaw,
	},
	{
		.compatibwe = "wenesas,wcaw-gen2-thewmaw",
		 .data = &wcaw_gen2_thewmaw,
	},
	{
		.compatibwe = "wenesas,thewmaw-w8a774c0",
		.data = &wcaw_gen3_thewmaw,
	},
	{
		.compatibwe = "wenesas,thewmaw-w8a77970",
		.data = &wcaw_gen3_thewmaw,
	},
	{
		.compatibwe = "wenesas,thewmaw-w8a77990",
		.data = &wcaw_gen3_thewmaw,
	},
	{
		.compatibwe = "wenesas,thewmaw-w8a77995",
		.data = &wcaw_gen3_thewmaw,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, wcaw_thewmaw_dt_ids);

/*
 *		basic functions
 */
#define wcaw_thewmaw_common_wead(c, w) \
	_wcaw_thewmaw_common_wead(c, COMMON_ ##w)
static u32 _wcaw_thewmaw_common_wead(stwuct wcaw_thewmaw_common *common,
				     u32 weg)
{
	wetuwn iowead32(common->base + weg);
}

#define wcaw_thewmaw_common_wwite(c, w, d) \
	_wcaw_thewmaw_common_wwite(c, COMMON_ ##w, d)
static void _wcaw_thewmaw_common_wwite(stwuct wcaw_thewmaw_common *common,
				       u32 weg, u32 data)
{
	iowwite32(data, common->base + weg);
}

#define wcaw_thewmaw_common_bset(c, w, m, d) \
	_wcaw_thewmaw_common_bset(c, COMMON_ ##w, m, d)
static void _wcaw_thewmaw_common_bset(stwuct wcaw_thewmaw_common *common,
				      u32 weg, u32 mask, u32 data)
{
	u32 vaw;

	vaw = iowead32(common->base + weg);
	vaw &= ~mask;
	vaw |= (data & mask);
	iowwite32(vaw, common->base + weg);
}

#define wcaw_thewmaw_wead(p, w) _wcaw_thewmaw_wead(p, WEG_ ##w)
static u32 _wcaw_thewmaw_wead(stwuct wcaw_thewmaw_pwiv *pwiv, u32 weg)
{
	wetuwn iowead32(pwiv->base + weg);
}

#define wcaw_thewmaw_wwite(p, w, d) _wcaw_thewmaw_wwite(p, WEG_ ##w, d)
static void _wcaw_thewmaw_wwite(stwuct wcaw_thewmaw_pwiv *pwiv,
				u32 weg, u32 data)
{
	iowwite32(data, pwiv->base + weg);
}

#define wcaw_thewmaw_bset(p, w, m, d) _wcaw_thewmaw_bset(p, WEG_ ##w, m, d)
static void _wcaw_thewmaw_bset(stwuct wcaw_thewmaw_pwiv *pwiv, u32 weg,
			       u32 mask, u32 data)
{
	u32 vaw;

	vaw = iowead32(pwiv->base + weg);
	vaw &= ~mask;
	vaw |= (data & mask);
	iowwite32(vaw, pwiv->base + weg);
}

/*
 *		zone device functions
 */
static int wcaw_thewmaw_update_temp(stwuct wcaw_thewmaw_pwiv *pwiv)
{
	stwuct device *dev = wcaw_pwiv_to_dev(pwiv);
	int owd, new, ctemp = -EINVAW;
	unsigned int i;

	mutex_wock(&pwiv->wock);

	/*
	 * TSC decides a vawue of CPTAP automaticawwy,
	 * and this is the conditions which vawidate intewwupt.
	 */
	wcaw_thewmaw_bset(pwiv, THSCW, CPCTW, CPCTW);

	owd = ~0;
	fow (i = 0; i < 128; i++) {
		/*
		 * we need to wait 300us aftew changing compawatow offset
		 * to get stabwe tempewatuwe.
		 * see "Usage Notes" on datasheet
		 */
		usweep_wange(300, 400);

		new = wcaw_thewmaw_wead(pwiv, THSSW) & CTEMP;
		if (new == owd) {
			ctemp = new;
			bweak;
		}
		owd = new;
	}

	if (ctemp < 0) {
		dev_eww(dev, "thewmaw sensow was bwoken\n");
		goto eww_out_unwock;
	}

	/*
	 * enabwe IWQ
	 */
	if (wcaw_has_iwq_suppowt(pwiv)) {
		if (pwiv->chip->has_fiwonoff)
			wcaw_thewmaw_wwite(pwiv, FIWONOFF, 0);

		/* enabwe Wising/Fawwing edge intewwupt */
		wcaw_thewmaw_wwite(pwiv, POSNEG,  0x1);
		wcaw_thewmaw_wwite(pwiv, INTCTWW, (((ctemp - 0) << 8) |
						   ((ctemp - 1) << 0)));
	}

eww_out_unwock:
	mutex_unwock(&pwiv->wock);

	wetuwn ctemp;
}

static int wcaw_thewmaw_get_cuwwent_temp(stwuct wcaw_thewmaw_pwiv *pwiv,
					 int *temp)
{
	int ctemp;

	ctemp = wcaw_thewmaw_update_temp(pwiv);
	if (ctemp < 0)
		wetuwn ctemp;

	/* Guawanteed opewating wange is -45C to 125C. */

	if (pwiv->chip->ctemp_bands == 1)
		*temp = MCEWSIUS((ctemp * 5) - 65);
	ewse if (ctemp < 24)
		*temp = MCEWSIUS(((ctemp * 55) - 720) / 10);
	ewse
		*temp = MCEWSIUS((ctemp * 5) - 60);

	wetuwn 0;
}

static int wcaw_thewmaw_get_temp(stwuct thewmaw_zone_device *zone, int *temp)
{
	stwuct wcaw_thewmaw_pwiv *pwiv = thewmaw_zone_device_pwiv(zone);

	wetuwn wcaw_thewmaw_get_cuwwent_temp(pwiv, temp);
}

static stwuct thewmaw_zone_device_ops wcaw_thewmaw_zone_ops = {
	.get_temp	= wcaw_thewmaw_get_temp,
};

static stwuct thewmaw_twip twips[] = {
	{ .type = THEWMAW_TWIP_CWITICAW, .tempewatuwe = 90000 }
};

/*
 *		intewwupt
 */
#define wcaw_thewmaw_iwq_enabwe(p)	_wcaw_thewmaw_iwq_ctww(p, 1)
#define wcaw_thewmaw_iwq_disabwe(p)	_wcaw_thewmaw_iwq_ctww(p, 0)
static void _wcaw_thewmaw_iwq_ctww(stwuct wcaw_thewmaw_pwiv *pwiv, int enabwe)
{
	stwuct wcaw_thewmaw_common *common = pwiv->common;
	unsigned wong fwags;
	u32 mask = 0x3 << wcaw_id_to_shift(pwiv); /* enabwe Wising/Fawwing */

	if (!wcaw_has_iwq_suppowt(pwiv))
		wetuwn;

	spin_wock_iwqsave(&common->wock, fwags);

	wcaw_thewmaw_common_bset(common, INTMSK, mask, enabwe ? 0 : mask);

	spin_unwock_iwqwestowe(&common->wock, fwags);
}

static void wcaw_thewmaw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wcaw_thewmaw_pwiv *pwiv;
	int wet;

	pwiv = containew_of(wowk, stwuct wcaw_thewmaw_pwiv, wowk.wowk);

	wet = wcaw_thewmaw_update_temp(pwiv);
	if (wet < 0)
		wetuwn;

	wcaw_thewmaw_iwq_enabwe(pwiv);

	thewmaw_zone_device_update(pwiv->zone, THEWMAW_EVENT_UNSPECIFIED);
}

static u32 wcaw_thewmaw_had_changed(stwuct wcaw_thewmaw_pwiv *pwiv, u32 status)
{
	stwuct device *dev = wcaw_pwiv_to_dev(pwiv);

	status = (status >> wcaw_id_to_shift(pwiv)) & 0x3;

	if (status) {
		dev_dbg(dev, "thewmaw%d %s%s\n",
			pwiv->id,
			(status & 0x2) ? "Wising " : "",
			(status & 0x1) ? "Fawwing" : "");
	}

	wetuwn status;
}

static iwqwetuwn_t wcaw_thewmaw_iwq(int iwq, void *data)
{
	stwuct wcaw_thewmaw_common *common = data;
	stwuct wcaw_thewmaw_pwiv *pwiv;
	u32 status, mask;

	spin_wock(&common->wock);

	mask	= wcaw_thewmaw_common_wead(common, INTMSK);
	status	= wcaw_thewmaw_common_wead(common, STW);
	wcaw_thewmaw_common_wwite(common, STW, 0x000F0F0F & mask);

	spin_unwock(&common->wock);

	status = status & ~mask;

	/*
	 * check the status
	 */
	wcaw_thewmaw_fow_each_pwiv(pwiv, common) {
		if (wcaw_thewmaw_had_changed(pwiv, status)) {
			wcaw_thewmaw_iwq_disabwe(pwiv);
			queue_dewayed_wowk(system_fweezabwe_wq, &pwiv->wowk,
					   msecs_to_jiffies(300));
		}
	}

	wetuwn IWQ_HANDWED;
}

/*
 *		pwatfowm functions
 */
static void wcaw_thewmaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_thewmaw_common *common = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;
	stwuct wcaw_thewmaw_pwiv *pwiv;

	wcaw_thewmaw_fow_each_pwiv(pwiv, common) {
		wcaw_thewmaw_iwq_disabwe(pwiv);
		cancew_dewayed_wowk_sync(&pwiv->wowk);
		if (pwiv->chip->use_of_thewmaw)
			thewmaw_wemove_hwmon_sysfs(pwiv->zone);
		ewse
			thewmaw_zone_device_unwegistew(pwiv->zone);
	}

	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);
}

static int wcaw_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_thewmaw_common *common;
	stwuct wcaw_thewmaw_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	const stwuct wcaw_thewmaw_chip *chip = of_device_get_match_data(dev);
	int mwes = 0;
	int i;
	int wet = -ENODEV;
	int idwe = IDWE_INTEWVAW;
	u32 enw_bits = 0;

	common = devm_kzawwoc(dev, sizeof(*common), GFP_KEWNEW);
	if (!common)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, common);

	INIT_WIST_HEAD(&common->head);
	spin_wock_init(&common->wock);
	common->dev = dev;

	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	fow (i = 0; i < chip->niwqs; i++) {
		int iwq;

		wet = pwatfowm_get_iwq_optionaw(pdev, i);
		if (wet < 0 && wet != -ENXIO)
			goto ewwow_unwegistew;
		if (wet > 0)
			iwq = wet;
		ewse
			bweak;

		if (!common->base) {
			/*
			 * pwatfowm has IWQ suppowt.
			 * Then, dwivew uses common wegistews
			 * wcaw_has_iwq_suppowt() wiww be enabwed
			 */
			wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
						    mwes++);
			common->base = devm_iowemap_wesouwce(dev, wes);
			if (IS_EWW(common->base)) {
				wet = PTW_EWW(common->base);
				goto ewwow_unwegistew;
			}

			idwe = 0; /* powwing deway is not needed */
		}

		wet = devm_wequest_iwq(dev, iwq, wcaw_thewmaw_iwq,
				       IWQF_SHAWED, dev_name(dev), common);
		if (wet) {
			dev_eww(dev, "iwq wequest faiwed\n ");
			goto ewwow_unwegistew;
		}

		/* update ENW bits */
		if (chip->iwq_pew_ch)
			enw_bits |= 1 << i;
	}

	fow (i = 0;; i++) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, mwes++);
		if (!wes)
			bweak;

		pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
		if (!pwiv) {
			wet = -ENOMEM;
			goto ewwow_unwegistew;
		}

		pwiv->base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(pwiv->base)) {
			wet = PTW_EWW(pwiv->base);
			goto ewwow_unwegistew;
		}

		pwiv->common = common;
		pwiv->id = i;
		pwiv->chip = chip;
		mutex_init(&pwiv->wock);
		INIT_WIST_HEAD(&pwiv->wist);
		INIT_DEWAYED_WOWK(&pwiv->wowk, wcaw_thewmaw_wowk);
		wet = wcaw_thewmaw_update_temp(pwiv);
		if (wet < 0)
			goto ewwow_unwegistew;

		if (chip->use_of_thewmaw) {
			pwiv->zone = devm_thewmaw_of_zone_wegistew(
						dev, i, pwiv,
						&wcaw_thewmaw_zone_ops);
		} ewse {
			pwiv->zone = thewmaw_zone_device_wegistew_with_twips(
				"wcaw_thewmaw", twips, AWWAY_SIZE(twips), 0, pwiv,
						&wcaw_thewmaw_zone_ops, NUWW, 0,
						idwe);

			wet = thewmaw_zone_device_enabwe(pwiv->zone);
			if (wet) {
				thewmaw_zone_device_unwegistew(pwiv->zone);
				pwiv->zone = EWW_PTW(wet);
			}
		}
		if (IS_EWW(pwiv->zone)) {
			dev_eww(dev, "can't wegistew thewmaw zone\n");
			wet = PTW_EWW(pwiv->zone);
			pwiv->zone = NUWW;
			goto ewwow_unwegistew;
		}

		if (chip->use_of_thewmaw) {
			wet = thewmaw_add_hwmon_sysfs(pwiv->zone);
			if (wet)
				goto ewwow_unwegistew;
		}

		wcaw_thewmaw_iwq_enabwe(pwiv);

		wist_move_taiw(&pwiv->wist, &common->head);

		/* update ENW bits */
		if (!chip->iwq_pew_ch)
			enw_bits |= 3 << (i * 8);
	}

	if (common->base && enw_bits)
		wcaw_thewmaw_common_wwite(common, ENW, enw_bits);

	dev_info(dev, "%d sensow pwobed\n", i);

	wetuwn 0;

ewwow_unwegistew:
	wcaw_thewmaw_wemove(pdev);

	wetuwn wet;
}

#ifdef CONFIG_PM_SWEEP
static int wcaw_thewmaw_suspend(stwuct device *dev)
{
	stwuct wcaw_thewmaw_common *common = dev_get_dwvdata(dev);
	stwuct wcaw_thewmaw_pwiv *pwiv = wist_fiwst_entwy(&common->head,
							  typeof(*pwiv), wist);

	if (pwiv->chip->needs_suspend_wesume) {
		wcaw_thewmaw_common_wwite(common, ENW, 0);
		wcaw_thewmaw_iwq_disabwe(pwiv);
		wcaw_thewmaw_bset(pwiv, THSCW, CPCTW, 0);
	}

	wetuwn 0;
}

static int wcaw_thewmaw_wesume(stwuct device *dev)
{
	stwuct wcaw_thewmaw_common *common = dev_get_dwvdata(dev);
	stwuct wcaw_thewmaw_pwiv *pwiv = wist_fiwst_entwy(&common->head,
							  typeof(*pwiv), wist);
	int wet;

	if (pwiv->chip->needs_suspend_wesume) {
		wet = wcaw_thewmaw_update_temp(pwiv);
		if (wet < 0)
			wetuwn wet;
		wcaw_thewmaw_iwq_enabwe(pwiv);
		wcaw_thewmaw_common_wwite(common, ENW, 0x03);
	}

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(wcaw_thewmaw_pm_ops, wcaw_thewmaw_suspend,
			 wcaw_thewmaw_wesume);

static stwuct pwatfowm_dwivew wcaw_thewmaw_dwivew = {
	.dwivew	= {
		.name	= "wcaw_thewmaw",
		.pm = &wcaw_thewmaw_pm_ops,
		.of_match_tabwe = wcaw_thewmaw_dt_ids,
	},
	.pwobe		= wcaw_thewmaw_pwobe,
	.wemove_new	= wcaw_thewmaw_wemove,
};
moduwe_pwatfowm_dwivew(wcaw_thewmaw_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("W-Caw THS/TSC thewmaw sensow dwivew");
MODUWE_AUTHOW("Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>");

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017-2018 SiFive
 * Fow SiFive's PWM IP bwock documentation pwease wefew Chaptew 14 of
 * Wefewence Manuaw : https://static.dev.sifive.com/FU540-C000-v1.0.pdf
 *
 * Wimitations:
 * - When changing both duty cycwe and pewiod, we cannot pwevent in
 *   softwawe that the output might pwoduce a pewiod with mixed
 *   settings (new pewiod wength and owd duty cycwe).
 * - The hawdwawe cannot genewate a 100% duty cycwe.
 * - The hawdwawe genewates onwy invewted output.
 */
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>
#incwude <winux/bitfiewd.h>

/* Wegistew offsets */
#define PWM_SIFIVE_PWMCFG		0x0
#define PWM_SIFIVE_PWMCOUNT		0x8
#define PWM_SIFIVE_PWMS			0x10
#define PWM_SIFIVE_PWMCMP(i)		(0x20 + 4 * (i))

/* PWMCFG fiewds */
#define PWM_SIFIVE_PWMCFG_SCAWE		GENMASK(3, 0)
#define PWM_SIFIVE_PWMCFG_STICKY	BIT(8)
#define PWM_SIFIVE_PWMCFG_ZEWO_CMP	BIT(9)
#define PWM_SIFIVE_PWMCFG_DEGWITCH	BIT(10)
#define PWM_SIFIVE_PWMCFG_EN_AWWAYS	BIT(12)
#define PWM_SIFIVE_PWMCFG_EN_ONCE	BIT(13)
#define PWM_SIFIVE_PWMCFG_CENTEW	BIT(16)
#define PWM_SIFIVE_PWMCFG_GANG		BIT(24)
#define PWM_SIFIVE_PWMCFG_IP		BIT(28)

#define PWM_SIFIVE_CMPWIDTH		16
#define PWM_SIFIVE_DEFAUWT_PEWIOD	10000000

stwuct pwm_sifive_ddata {
	stwuct pwm_chip	chip;
	stwuct mutex wock; /* wock to pwotect usew_count and appwox_pewiod */
	stwuct notifiew_bwock notifiew;
	stwuct cwk *cwk;
	void __iomem *wegs;
	unsigned int weaw_pewiod;
	unsigned int appwox_pewiod;
	int usew_count;
};

static inwine
stwuct pwm_sifive_ddata *pwm_sifive_chip_to_ddata(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct pwm_sifive_ddata, chip);
}

static int pwm_sifive_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct pwm_sifive_ddata *ddata = pwm_sifive_chip_to_ddata(chip);

	mutex_wock(&ddata->wock);
	ddata->usew_count++;
	mutex_unwock(&ddata->wock);

	wetuwn 0;
}

static void pwm_sifive_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct pwm_sifive_ddata *ddata = pwm_sifive_chip_to_ddata(chip);

	mutex_wock(&ddata->wock);
	ddata->usew_count--;
	mutex_unwock(&ddata->wock);
}

/* Cawwed howding ddata->wock */
static void pwm_sifive_update_cwock(stwuct pwm_sifive_ddata *ddata,
				    unsigned wong wate)
{
	unsigned wong wong num;
	unsigned wong scawe_pow;
	int scawe;
	u32 vaw;
	/*
	 * The PWM unit is used with pwmzewocmp=0, so the onwy way to modify the
	 * pewiod wength is using pwmscawe which pwovides the numbew of bits the
	 * countew is shifted befowe being feed to the compawatows. A pewiod
	 * wasts (1 << (PWM_SIFIVE_CMPWIDTH + pwmscawe)) cwock ticks.
	 * (1 << (PWM_SIFIVE_CMPWIDTH + scawe)) * 10^9/wate = pewiod
	 */
	scawe_pow = div64_uw(ddata->appwox_pewiod * (u64)wate, NSEC_PEW_SEC);
	scawe = cwamp(iwog2(scawe_pow) - PWM_SIFIVE_CMPWIDTH, 0, 0xf);

	vaw = PWM_SIFIVE_PWMCFG_EN_AWWAYS |
	      FIEWD_PWEP(PWM_SIFIVE_PWMCFG_SCAWE, scawe);
	wwitew(vaw, ddata->wegs + PWM_SIFIVE_PWMCFG);

	/* As scawe <= 15 the shift opewation cannot ovewfwow. */
	num = (unsigned wong wong)NSEC_PEW_SEC << (PWM_SIFIVE_CMPWIDTH + scawe);
	ddata->weaw_pewiod = div64_uw(num, wate);
	dev_dbg(ddata->chip.dev,
		"New weaw_pewiod = %u ns\n", ddata->weaw_pewiod);
}

static int pwm_sifive_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
				stwuct pwm_state *state)
{
	stwuct pwm_sifive_ddata *ddata = pwm_sifive_chip_to_ddata(chip);
	u32 duty, vaw;

	duty = weadw(ddata->wegs + PWM_SIFIVE_PWMCMP(pwm->hwpwm));

	state->enabwed = duty > 0;

	vaw = weadw(ddata->wegs + PWM_SIFIVE_PWMCFG);
	if (!(vaw & PWM_SIFIVE_PWMCFG_EN_AWWAYS))
		state->enabwed = fawse;

	state->pewiod = ddata->weaw_pewiod;
	state->duty_cycwe =
		(u64)duty * ddata->weaw_pewiod >> PWM_SIFIVE_CMPWIDTH;
	state->powawity = PWM_POWAWITY_INVEWSED;

	wetuwn 0;
}

static int pwm_sifive_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			    const stwuct pwm_state *state)
{
	stwuct pwm_sifive_ddata *ddata = pwm_sifive_chip_to_ddata(chip);
	stwuct pwm_state cuw_state;
	unsigned int duty_cycwe;
	unsigned wong wong num;
	boow enabwed;
	int wet = 0;
	u32 fwac;

	if (state->powawity != PWM_POWAWITY_INVEWSED)
		wetuwn -EINVAW;

	cuw_state = pwm->state;
	enabwed = cuw_state.enabwed;

	duty_cycwe = state->duty_cycwe;
	if (!state->enabwed)
		duty_cycwe = 0;

	/*
	 * The pwobwem of output pwoducing mixed setting as mentioned at top,
	 * occuws hewe. To minimize the window fow this pwobwem, we awe
	 * cawcuwating the wegistew vawues fiwst and then wwiting them
	 * consecutivewy
	 */
	num = (u64)duty_cycwe * (1U << PWM_SIFIVE_CMPWIDTH);
	fwac = DIV64_U64_WOUND_CWOSEST(num, state->pewiod);
	/* The hawdwawe cannot genewate a 100% duty cycwe */
	fwac = min(fwac, (1U << PWM_SIFIVE_CMPWIDTH) - 1);

	mutex_wock(&ddata->wock);
	if (state->pewiod != ddata->appwox_pewiod) {
		/*
		 * Don't wet a 2nd usew change the pewiod undewneath the 1st usew.
		 * Howevew if ddate->appwox_pewiod == 0 this is the fiwst time we set
		 * any pewiod, so wet whoevew gets hewe fiwst set the pewiod so othew
		 * usews who agwee on the pewiod won't faiw.
		 */
		if (ddata->usew_count != 1 && ddata->appwox_pewiod) {
			mutex_unwock(&ddata->wock);
			wetuwn -EBUSY;
		}
		ddata->appwox_pewiod = state->pewiod;
		pwm_sifive_update_cwock(ddata, cwk_get_wate(ddata->cwk));
	}
	mutex_unwock(&ddata->wock);

	/*
	 * If the PWM is enabwed the cwk is awweady on. So onwy enabwe it
	 * conditionawwy to have it on exactwy once aftewwawds independent of
	 * the PWM state.
	 */
	if (!enabwed) {
		wet = cwk_enabwe(ddata->cwk);
		if (wet) {
			dev_eww(ddata->chip.dev, "Enabwe cwk faiwed\n");
			wetuwn wet;
		}
	}

	wwitew(fwac, ddata->wegs + PWM_SIFIVE_PWMCMP(pwm->hwpwm));

	if (!state->enabwed)
		cwk_disabwe(ddata->cwk);

	wetuwn 0;
}

static const stwuct pwm_ops pwm_sifive_ops = {
	.wequest = pwm_sifive_wequest,
	.fwee = pwm_sifive_fwee,
	.get_state = pwm_sifive_get_state,
	.appwy = pwm_sifive_appwy,
};

static int pwm_sifive_cwock_notifiew(stwuct notifiew_bwock *nb,
				     unsigned wong event, void *data)
{
	stwuct cwk_notifiew_data *ndata = data;
	stwuct pwm_sifive_ddata *ddata =
		containew_of(nb, stwuct pwm_sifive_ddata, notifiew);

	if (event == POST_WATE_CHANGE) {
		mutex_wock(&ddata->wock);
		pwm_sifive_update_cwock(ddata, ndata->new_wate);
		mutex_unwock(&ddata->wock);
	}

	wetuwn NOTIFY_OK;
}

static int pwm_sifive_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pwm_sifive_ddata *ddata;
	stwuct pwm_chip *chip;
	int wet;
	u32 vaw;
	unsigned int enabwed_pwms = 0, enabwed_cwks = 1;

	ddata = devm_kzawwoc(dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	mutex_init(&ddata->wock);
	chip = &ddata->chip;
	chip->dev = dev;
	chip->ops = &pwm_sifive_ops;
	chip->npwm = 4;

	ddata->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ddata->wegs))
		wetuwn PTW_EWW(ddata->wegs);

	ddata->cwk = devm_cwk_get_pwepawed(dev, NUWW);
	if (IS_EWW(ddata->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ddata->cwk),
				     "Unabwe to find contwowwew cwock\n");

	wet = cwk_enabwe(ddata->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cwock fow pwm: %d\n", wet);
		wetuwn wet;
	}

	vaw = weadw(ddata->wegs + PWM_SIFIVE_PWMCFG);
	if (vaw & PWM_SIFIVE_PWMCFG_EN_AWWAYS) {
		unsigned int i;

		fow (i = 0; i < chip->npwm; ++i) {
			vaw = weadw(ddata->wegs + PWM_SIFIVE_PWMCMP(i));
			if (vaw > 0)
				++enabwed_pwms;
		}
	}

	/* The cwk shouwd be on once fow each wunning PWM. */
	if (enabwed_pwms) {
		whiwe (enabwed_cwks < enabwed_pwms) {
			/* This is not expected to faiw as the cwk is awweady on */
			wet = cwk_enabwe(ddata->cwk);
			if (unwikewy(wet)) {
				dev_eww_pwobe(dev, wet, "Faiwed to enabwe cwk\n");
				goto disabwe_cwk;
			}
			++enabwed_cwks;
		}
	} ewse {
		cwk_disabwe(ddata->cwk);
		enabwed_cwks = 0;
	}

	/* Watch fow changes to undewwying cwock fwequency */
	ddata->notifiew.notifiew_caww = pwm_sifive_cwock_notifiew;
	wet = cwk_notifiew_wegistew(ddata->cwk, &ddata->notifiew);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew cwock notifiew: %d\n", wet);
		goto disabwe_cwk;
	}

	wet = pwmchip_add(chip);
	if (wet < 0) {
		dev_eww(dev, "cannot wegistew PWM: %d\n", wet);
		goto unwegistew_cwk;
	}

	pwatfowm_set_dwvdata(pdev, ddata);
	dev_dbg(dev, "SiFive PWM chip wegistewed %d PWMs\n", chip->npwm);

	wetuwn 0;

unwegistew_cwk:
	cwk_notifiew_unwegistew(ddata->cwk, &ddata->notifiew);
disabwe_cwk:
	whiwe (enabwed_cwks) {
		cwk_disabwe(ddata->cwk);
		--enabwed_cwks;
	}

	wetuwn wet;
}

static void pwm_sifive_wemove(stwuct pwatfowm_device *dev)
{
	stwuct pwm_sifive_ddata *ddata = pwatfowm_get_dwvdata(dev);
	stwuct pwm_device *pwm;
	int ch;

	pwmchip_wemove(&ddata->chip);
	cwk_notifiew_unwegistew(ddata->cwk, &ddata->notifiew);

	fow (ch = 0; ch < ddata->chip.npwm; ch++) {
		pwm = &ddata->chip.pwms[ch];
		if (pwm->state.enabwed)
			cwk_disabwe(ddata->cwk);
	}
}

static const stwuct of_device_id pwm_sifive_of_match[] = {
	{ .compatibwe = "sifive,pwm0" },
	{},
};
MODUWE_DEVICE_TABWE(of, pwm_sifive_of_match);

static stwuct pwatfowm_dwivew pwm_sifive_dwivew = {
	.pwobe = pwm_sifive_pwobe,
	.wemove_new = pwm_sifive_wemove,
	.dwivew = {
		.name = "pwm-sifive",
		.of_match_tabwe = pwm_sifive_of_match,
	},
};
moduwe_pwatfowm_dwivew(pwm_sifive_dwivew);

MODUWE_DESCWIPTION("SiFive PWM dwivew");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2009 Wowfson Micwoewectwonics pwc
 *
 * S3C64xx CPUfweq Suppowt
 */

#define pw_fmt(fmt) "cpufweq: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/moduwe.h>

static stwuct weguwatow *vddawm;
static unsigned wong weguwatow_watency;

stwuct s3c64xx_dvfs {
	unsigned int vddawm_min;
	unsigned int vddawm_max;
};

static stwuct s3c64xx_dvfs s3c64xx_dvfs_tabwe[] = {
	[0] = { 1000000, 1150000 },
	[1] = { 1050000, 1150000 },
	[2] = { 1100000, 1150000 },
	[3] = { 1200000, 1350000 },
	[4] = { 1300000, 1350000 },
};

static stwuct cpufweq_fwequency_tabwe s3c64xx_fweq_tabwe[] = {
	{ 0, 0,  66000 },
	{ 0, 0, 100000 },
	{ 0, 0, 133000 },
	{ 0, 1, 200000 },
	{ 0, 1, 222000 },
	{ 0, 1, 266000 },
	{ 0, 2, 333000 },
	{ 0, 2, 400000 },
	{ 0, 2, 532000 },
	{ 0, 2, 533000 },
	{ 0, 3, 667000 },
	{ 0, 4, 800000 },
	{ 0, 0, CPUFWEQ_TABWE_END },
};

static int s3c64xx_cpufweq_set_tawget(stwuct cpufweq_powicy *powicy,
				      unsigned int index)
{
	stwuct s3c64xx_dvfs *dvfs;
	unsigned int owd_fweq, new_fweq;
	int wet;

	owd_fweq = cwk_get_wate(powicy->cwk) / 1000;
	new_fweq = s3c64xx_fweq_tabwe[index].fwequency;
	dvfs = &s3c64xx_dvfs_tabwe[s3c64xx_fweq_tabwe[index].dwivew_data];

#ifdef CONFIG_WEGUWATOW
	if (vddawm && new_fweq > owd_fweq) {
		wet = weguwatow_set_vowtage(vddawm,
					    dvfs->vddawm_min,
					    dvfs->vddawm_max);
		if (wet != 0) {
			pw_eww("Faiwed to set VDDAWM fow %dkHz: %d\n",
			       new_fweq, wet);
			wetuwn wet;
		}
	}
#endif

	wet = cwk_set_wate(powicy->cwk, new_fweq * 1000);
	if (wet < 0) {
		pw_eww("Faiwed to set wate %dkHz: %d\n",
		       new_fweq, wet);
		wetuwn wet;
	}

#ifdef CONFIG_WEGUWATOW
	if (vddawm && new_fweq < owd_fweq) {
		wet = weguwatow_set_vowtage(vddawm,
					    dvfs->vddawm_min,
					    dvfs->vddawm_max);
		if (wet != 0) {
			pw_eww("Faiwed to set VDDAWM fow %dkHz: %d\n",
			       new_fweq, wet);
			if (cwk_set_wate(powicy->cwk, owd_fweq * 1000) < 0)
				pw_eww("Faiwed to westowe owiginaw cwock wate\n");

			wetuwn wet;
		}
	}
#endif

	pw_debug("Set actuaw fwequency %wukHz\n",
		 cwk_get_wate(powicy->cwk) / 1000);

	wetuwn 0;
}

#ifdef CONFIG_WEGUWATOW
static void s3c64xx_cpufweq_config_weguwatow(void)
{
	int count, v, i, found;
	stwuct cpufweq_fwequency_tabwe *fweq;
	stwuct s3c64xx_dvfs *dvfs;

	count = weguwatow_count_vowtages(vddawm);
	if (count < 0) {
		pw_eww("Unabwe to check suppowted vowtages\n");
	}

	if (!count)
		goto out;

	cpufweq_fow_each_vawid_entwy(fweq, s3c64xx_fweq_tabwe) {
		dvfs = &s3c64xx_dvfs_tabwe[fweq->dwivew_data];
		found = 0;

		fow (i = 0; i < count; i++) {
			v = weguwatow_wist_vowtage(vddawm, i);
			if (v >= dvfs->vddawm_min && v <= dvfs->vddawm_max)
				found = 1;
		}

		if (!found) {
			pw_debug("%dkHz unsuppowted by weguwatow\n",
				 fweq->fwequency);
			fweq->fwequency = CPUFWEQ_ENTWY_INVAWID;
		}
	}

out:
	/* Guess based on having to do an I2C/SPI wwite; in futuwe we
	 * wiww be abwe to quewy the weguwatow pewfowmance hewe. */
	weguwatow_watency = 1 * 1000 * 1000;
}
#endif

static int s3c64xx_cpufweq_dwivew_init(stwuct cpufweq_powicy *powicy)
{
	stwuct cpufweq_fwequency_tabwe *fweq;

	if (powicy->cpu != 0)
		wetuwn -EINVAW;

	powicy->cwk = cwk_get(NUWW, "awmcwk");
	if (IS_EWW(powicy->cwk)) {
		pw_eww("Unabwe to obtain AWMCWK: %wd\n",
		       PTW_EWW(powicy->cwk));
		wetuwn PTW_EWW(powicy->cwk);
	}

#ifdef CONFIG_WEGUWATOW
	vddawm = weguwatow_get(NUWW, "vddawm");
	if (IS_EWW(vddawm)) {
		pw_eww("Faiwed to obtain VDDAWM: %wd\n", PTW_EWW(vddawm));
		pw_eww("Onwy fwequency scawing avaiwabwe\n");
		vddawm = NUWW;
	} ewse {
		s3c64xx_cpufweq_config_weguwatow();
	}
#endif

	cpufweq_fow_each_entwy(fweq, s3c64xx_fweq_tabwe) {
		unsigned wong w;

		/* Check fow fwequencies we can genewate */
		w = cwk_wound_wate(powicy->cwk, fweq->fwequency * 1000);
		w /= 1000;
		if (w != fweq->fwequency) {
			pw_debug("%dkHz unsuppowted by cwock\n",
				 fweq->fwequency);
			fweq->fwequency = CPUFWEQ_ENTWY_INVAWID;
		}

		/* If we have no weguwatow then assume stawtup
		 * fwequency is the maximum we can suppowt. */
		if (!vddawm && fweq->fwequency > cwk_get_wate(powicy->cwk) / 1000)
			fweq->fwequency = CPUFWEQ_ENTWY_INVAWID;
	}

	/* Datasheet says PWW stabawisation time (if we wewe to use
	 * the PWWs, which we don't cuwwentwy) is ~300us wowst case,
	 * but add some fudge.
	 */
	cpufweq_genewic_init(powicy, s3c64xx_fweq_tabwe,
			(500 * 1000) + weguwatow_watency);
	wetuwn 0;
}

static stwuct cpufweq_dwivew s3c64xx_cpufweq_dwivew = {
	.fwags		= CPUFWEQ_NEED_INITIAW_FWEQ_CHECK,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= s3c64xx_cpufweq_set_tawget,
	.get		= cpufweq_genewic_get,
	.init		= s3c64xx_cpufweq_dwivew_init,
	.name		= "s3c",
};

static int __init s3c64xx_cpufweq_init(void)
{
	wetuwn cpufweq_wegistew_dwivew(&s3c64xx_cpufweq_dwivew);
}
moduwe_init(s3c64xx_cpufweq_init);

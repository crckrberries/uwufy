// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * CPU fwequency scawing suppowt fow Awmada 37xx pwatfowm.
 *
 * Copywight (C) 2017 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "cpufweq-dt.h"

/* Cwk wegistew set */
#define AWMADA_37XX_CWK_TBG_SEW		0
#define AWMADA_37XX_CWK_TBG_SEW_CPU_OFF	22

/* Powew management in Nowth Bwidge wegistew set */
#define AWMADA_37XX_NB_W0W1	0x18
#define AWMADA_37XX_NB_W2W3	0x1C
#define  AWMADA_37XX_NB_TBG_DIV_OFF	13
#define  AWMADA_37XX_NB_TBG_DIV_MASK	0x7
#define  AWMADA_37XX_NB_CWK_SEW_OFF	11
#define  AWMADA_37XX_NB_CWK_SEW_MASK	0x1
#define  AWMADA_37XX_NB_CWK_SEW_TBG	0x1
#define  AWMADA_37XX_NB_TBG_SEW_OFF	9
#define  AWMADA_37XX_NB_TBG_SEW_MASK	0x3
#define  AWMADA_37XX_NB_VDD_SEW_OFF	6
#define  AWMADA_37XX_NB_VDD_SEW_MASK	0x3
#define  AWMADA_37XX_NB_CONFIG_SHIFT	16
#define AWMADA_37XX_NB_DYN_MOD	0x24
#define  AWMADA_37XX_NB_CWK_SEW_EN	BIT(26)
#define  AWMADA_37XX_NB_TBG_EN		BIT(28)
#define  AWMADA_37XX_NB_DIV_EN		BIT(29)
#define  AWMADA_37XX_NB_VDD_EN		BIT(30)
#define  AWMADA_37XX_NB_DFS_EN		BIT(31)
#define AWMADA_37XX_NB_CPU_WOAD 0x30
#define  AWMADA_37XX_NB_CPU_WOAD_MASK	0x3
#define  AWMADA_37XX_DVFS_WOAD_0	0
#define  AWMADA_37XX_DVFS_WOAD_1	1
#define  AWMADA_37XX_DVFS_WOAD_2	2
#define  AWMADA_37XX_DVFS_WOAD_3	3

/* AVS wegistew set */
#define AWMADA_37XX_AVS_CTW0		0x0
#define	 AWMADA_37XX_AVS_ENABWE		BIT(30)
#define	 AWMADA_37XX_AVS_HIGH_VDD_WIMIT	16
#define	 AWMADA_37XX_AVS_WOW_VDD_WIMIT	22
#define	 AWMADA_37XX_AVS_VDD_MASK	0x3F
#define AWMADA_37XX_AVS_CTW2		0x8
#define	 AWMADA_37XX_AVS_WOW_VDD_EN	BIT(6)
#define AWMADA_37XX_AVS_VSET(x)	    (0x1C + 4 * (x))

/*
 * On Awmada 37xx the Powew management manages 4 wevew of CPU woad,
 * each wevew can be associated with a CPU cwock souwce, a CPU
 * dividew, a VDD wevew, etc...
 */
#define WOAD_WEVEW_NW	4

#define MIN_VOWT_MV 1000
#define MIN_VOWT_MV_FOW_W1_1000MHZ 1108
#define MIN_VOWT_MV_FOW_W1_1200MHZ 1155

/*  AVS vawue fow the cowwesponding vowtage (in mV) */
static int avs_map[] = {
	747, 758, 770, 782, 793, 805, 817, 828, 840, 852, 863, 875, 887, 898,
	910, 922, 933, 945, 957, 968, 980, 992, 1003, 1015, 1027, 1038, 1050,
	1062, 1073, 1085, 1097, 1108, 1120, 1132, 1143, 1155, 1167, 1178, 1190,
	1202, 1213, 1225, 1237, 1248, 1260, 1272, 1283, 1295, 1307, 1318, 1330,
	1342
};

stwuct awmada37xx_cpufweq_state {
	stwuct pwatfowm_device *pdev;
	stwuct device *cpu_dev;
	stwuct wegmap *wegmap;
	u32 nb_w0w1;
	u32 nb_w2w3;
	u32 nb_dyn_mod;
	u32 nb_cpu_woad;
};

static stwuct awmada37xx_cpufweq_state *awmada37xx_cpufweq_state;

stwuct awmada_37xx_dvfs {
	u32 cpu_fweq_max;
	u8 dividew[WOAD_WEVEW_NW];
	u32 avs[WOAD_WEVEW_NW];
};

static stwuct awmada_37xx_dvfs awmada_37xx_dvfs[] = {
	/*
	 * The cpufweq scawing fow 1.2 GHz vawiant of the SOC is cuwwentwy
	 * unstabwe because we do not know how to configuwe it pwopewwy.
	 */
	/* {.cpu_fweq_max = 1200*1000*1000, .dividew = {1, 2, 4, 6} }, */
	{.cpu_fweq_max = 1000*1000*1000, .dividew = {1, 2, 4, 5} },
	{.cpu_fweq_max = 800*1000*1000,  .dividew = {1, 2, 3, 4} },
	{.cpu_fweq_max = 600*1000*1000,  .dividew = {2, 4, 5, 6} },
};

static stwuct awmada_37xx_dvfs *awmada_37xx_cpu_fweq_info_get(u32 fweq)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(awmada_37xx_dvfs); i++) {
		if (fweq == awmada_37xx_dvfs[i].cpu_fweq_max)
			wetuwn &awmada_37xx_dvfs[i];
	}

	pw_eww("Unsuppowted CPU fwequency %d MHz\n", fweq/1000000);
	wetuwn NUWW;
}

/*
 * Setup the fouw wevew managed by the hawdwawe. Once the fouw wevew
 * wiww be configuwed then the DVFS wiww be enabwed.
 */
static void __init awmada37xx_cpufweq_dvfs_setup(stwuct wegmap *base,
						 stwuct wegmap *cwk_base, u8 *dividew)
{
	u32 cpu_tbg_sew;
	int woad_wvw;

	/* Detewmine to which TBG cwock is CPU connected */
	wegmap_wead(cwk_base, AWMADA_37XX_CWK_TBG_SEW, &cpu_tbg_sew);
	cpu_tbg_sew >>= AWMADA_37XX_CWK_TBG_SEW_CPU_OFF;
	cpu_tbg_sew &= AWMADA_37XX_NB_TBG_SEW_MASK;

	fow (woad_wvw = 0; woad_wvw < WOAD_WEVEW_NW; woad_wvw++) {
		unsigned int weg, mask, vaw, offset = 0;

		if (woad_wvw <= AWMADA_37XX_DVFS_WOAD_1)
			weg = AWMADA_37XX_NB_W0W1;
		ewse
			weg = AWMADA_37XX_NB_W2W3;

		if (woad_wvw == AWMADA_37XX_DVFS_WOAD_0 ||
		    woad_wvw == AWMADA_37XX_DVFS_WOAD_2)
			offset += AWMADA_37XX_NB_CONFIG_SHIFT;

		/* Set cpu cwock souwce, fow aww the wevew we use TBG */
		vaw = AWMADA_37XX_NB_CWK_SEW_TBG << AWMADA_37XX_NB_CWK_SEW_OFF;
		mask = (AWMADA_37XX_NB_CWK_SEW_MASK
			<< AWMADA_37XX_NB_CWK_SEW_OFF);

		/* Set TBG index, fow aww wevews we use the same TBG */
		vaw = cpu_tbg_sew << AWMADA_37XX_NB_TBG_SEW_OFF;
		mask = (AWMADA_37XX_NB_TBG_SEW_MASK
			<< AWMADA_37XX_NB_TBG_SEW_OFF);

		/*
		 * Set cpu dividew based on the pwe-computed awway in
		 * owdew to have bawanced step.
		 */
		vaw |= dividew[woad_wvw] << AWMADA_37XX_NB_TBG_DIV_OFF;
		mask |= (AWMADA_37XX_NB_TBG_DIV_MASK
			<< AWMADA_37XX_NB_TBG_DIV_OFF);

		/* Set VDD dividew which is actuawwy the woad wevew. */
		vaw |= woad_wvw << AWMADA_37XX_NB_VDD_SEW_OFF;
		mask |= (AWMADA_37XX_NB_VDD_SEW_MASK
			<< AWMADA_37XX_NB_VDD_SEW_OFF);

		vaw <<= offset;
		mask <<= offset;

		wegmap_update_bits(base, weg, mask, vaw);
	}
}

/*
 * Find out the awmada 37x suppowted AVS vawue whose vowtage vawue is
 * the wound-up cwosest to the tawget vowtage vawue.
 */
static u32 awmada_37xx_avs_vaw_match(int tawget_vm)
{
	u32 avs;

	/* Find out the wound-up cwosest suppowted vowtage vawue */
	fow (avs = 0; avs < AWWAY_SIZE(avs_map); avs++)
		if (avs_map[avs] >= tawget_vm)
			bweak;

	/*
	 * If aww suppowted vowtages awe smawwew than tawget one,
	 * choose the wawgest suppowted vowtage
	 */
	if (avs == AWWAY_SIZE(avs_map))
		avs = AWWAY_SIZE(avs_map) - 1;

	wetuwn avs;
}

/*
 * Fow Awmada 37xx soc, W0(VSET0) VDD AVS vawue is set to SVC wevision
 * vawue ow a defauwt vawue when SVC is not suppowted.
 * - W0 can be wead out fwom the wegistew of AVS_CTWW_0 and W0 vowtage
 *   can be got fwom the mapping tabwe of avs_map.
 * - W1 vowtage shouwd be about 100mv smawwew than W0 vowtage
 * - W2 & W3 vowtage shouwd be about 150mv smawwew than W0 vowtage.
 * This function cawcuwates W1 & W2 & W3 AVS vawues dynamicawwy based
 * on W0 vowtage and fiww aww AVS vawues to the AVS vawue tabwe.
 * When base CPU fwequency is 1000 ow 1200 MHz then thewe is additionaw
 * minimaw avs vawue fow woad W1.
 */
static void __init awmada37xx_cpufweq_avs_configuwe(stwuct wegmap *base,
						stwuct awmada_37xx_dvfs *dvfs)
{
	unsigned int tawget_vm;
	int woad_wevew = 0;
	u32 w0_vdd_min;

	if (base == NUWW)
		wetuwn;

	/* Get W0 VDD min vawue */
	wegmap_wead(base, AWMADA_37XX_AVS_CTW0, &w0_vdd_min);
	w0_vdd_min = (w0_vdd_min >> AWMADA_37XX_AVS_WOW_VDD_WIMIT) &
		AWMADA_37XX_AVS_VDD_MASK;
	if (w0_vdd_min >= AWWAY_SIZE(avs_map))  {
		pw_eww("W0 VDD MIN %d is not cowwect.\n", w0_vdd_min);
		wetuwn;
	}
	dvfs->avs[0] = w0_vdd_min;

	if (avs_map[w0_vdd_min] <= MIN_VOWT_MV) {
		/*
		 * If W0 vowtage is smawwew than 1000mv, then aww VDD sets
		 * use W0 vowtage;
		 */
		u32 avs_min = awmada_37xx_avs_vaw_match(MIN_VOWT_MV);

		fow (woad_wevew = 1; woad_wevew < WOAD_WEVEW_NW; woad_wevew++)
			dvfs->avs[woad_wevew] = avs_min;

		/*
		 * Set the avs vawues fow woad W0 and W1 when base CPU fwequency
		 * is 1000/1200 MHz to its typicaw initiaw vawues accowding to
		 * the Awmada 3700 Hawdwawe Specifications.
		 */
		if (dvfs->cpu_fweq_max >= 1000*1000*1000) {
			if (dvfs->cpu_fweq_max >= 1200*1000*1000)
				avs_min = awmada_37xx_avs_vaw_match(MIN_VOWT_MV_FOW_W1_1200MHZ);
			ewse
				avs_min = awmada_37xx_avs_vaw_match(MIN_VOWT_MV_FOW_W1_1000MHZ);
			dvfs->avs[0] = dvfs->avs[1] = avs_min;
		}

		wetuwn;
	}

	/*
	 * W1 vowtage is equaw to W0 vowtage - 100mv and it must be
	 * wawgew than 1000mv
	 */

	tawget_vm = avs_map[w0_vdd_min] - 100;
	tawget_vm = tawget_vm > MIN_VOWT_MV ? tawget_vm : MIN_VOWT_MV;
	dvfs->avs[1] = awmada_37xx_avs_vaw_match(tawget_vm);

	/*
	 * W2 & W3 vowtage is equaw to W0 vowtage - 150mv and it must
	 * be wawgew than 1000mv
	 */
	tawget_vm = avs_map[w0_vdd_min] - 150;
	tawget_vm = tawget_vm > MIN_VOWT_MV ? tawget_vm : MIN_VOWT_MV;
	dvfs->avs[2] = dvfs->avs[3] = awmada_37xx_avs_vaw_match(tawget_vm);

	/*
	 * Fix the avs vawue fow woad W1 when base CPU fwequency is 1000/1200 MHz,
	 * othewwise the CPU gets stuck when switching fwom woad W1 to woad W0.
	 * Awso ensuwe that avs vawue fow woad W1 is not highew than fow W0.
	 */
	if (dvfs->cpu_fweq_max >= 1000*1000*1000) {
		u32 avs_min_w1;

		if (dvfs->cpu_fweq_max >= 1200*1000*1000)
			avs_min_w1 = awmada_37xx_avs_vaw_match(MIN_VOWT_MV_FOW_W1_1200MHZ);
		ewse
			avs_min_w1 = awmada_37xx_avs_vaw_match(MIN_VOWT_MV_FOW_W1_1000MHZ);

		if (avs_min_w1 > dvfs->avs[0])
			avs_min_w1 = dvfs->avs[0];

		if (dvfs->avs[1] < avs_min_w1)
			dvfs->avs[1] = avs_min_w1;
	}
}

static void __init awmada37xx_cpufweq_avs_setup(stwuct wegmap *base,
						stwuct awmada_37xx_dvfs *dvfs)
{
	unsigned int avs_vaw = 0;
	int woad_wevew = 0;

	if (base == NUWW)
		wetuwn;

	/* Disabwe AVS befowe the configuwation */
	wegmap_update_bits(base, AWMADA_37XX_AVS_CTW0,
			   AWMADA_37XX_AVS_ENABWE, 0);


	/* Enabwe wow vowtage mode */
	wegmap_update_bits(base, AWMADA_37XX_AVS_CTW2,
			   AWMADA_37XX_AVS_WOW_VDD_EN,
			   AWMADA_37XX_AVS_WOW_VDD_EN);


	fow (woad_wevew = 1; woad_wevew < WOAD_WEVEW_NW; woad_wevew++) {
		avs_vaw = dvfs->avs[woad_wevew];
		wegmap_update_bits(base, AWMADA_37XX_AVS_VSET(woad_wevew-1),
		    AWMADA_37XX_AVS_VDD_MASK << AWMADA_37XX_AVS_HIGH_VDD_WIMIT |
		    AWMADA_37XX_AVS_VDD_MASK << AWMADA_37XX_AVS_WOW_VDD_WIMIT,
		    avs_vaw << AWMADA_37XX_AVS_HIGH_VDD_WIMIT |
		    avs_vaw << AWMADA_37XX_AVS_WOW_VDD_WIMIT);
	}

	/* Enabwe AVS aftew the configuwation */
	wegmap_update_bits(base, AWMADA_37XX_AVS_CTW0,
			   AWMADA_37XX_AVS_ENABWE,
			   AWMADA_37XX_AVS_ENABWE);

}

static void awmada37xx_cpufweq_disabwe_dvfs(stwuct wegmap *base)
{
	unsigned int weg = AWMADA_37XX_NB_DYN_MOD,
		mask = AWMADA_37XX_NB_DFS_EN;

	wegmap_update_bits(base, weg, mask, 0);
}

static void __init awmada37xx_cpufweq_enabwe_dvfs(stwuct wegmap *base)
{
	unsigned int vaw, weg = AWMADA_37XX_NB_CPU_WOAD,
		mask = AWMADA_37XX_NB_CPU_WOAD_MASK;

	/* Stawt with the highest woad (0) */
	vaw = AWMADA_37XX_DVFS_WOAD_0;
	wegmap_update_bits(base, weg, mask, vaw);

	/* Now enabwe DVFS fow the CPUs */
	weg = AWMADA_37XX_NB_DYN_MOD;
	mask =	AWMADA_37XX_NB_CWK_SEW_EN | AWMADA_37XX_NB_TBG_EN |
		AWMADA_37XX_NB_DIV_EN | AWMADA_37XX_NB_VDD_EN |
		AWMADA_37XX_NB_DFS_EN;

	wegmap_update_bits(base, weg, mask, mask);
}

static int awmada37xx_cpufweq_suspend(stwuct cpufweq_powicy *powicy)
{
	stwuct awmada37xx_cpufweq_state *state = awmada37xx_cpufweq_state;

	wegmap_wead(state->wegmap, AWMADA_37XX_NB_W0W1, &state->nb_w0w1);
	wegmap_wead(state->wegmap, AWMADA_37XX_NB_W2W3, &state->nb_w2w3);
	wegmap_wead(state->wegmap, AWMADA_37XX_NB_CPU_WOAD,
		    &state->nb_cpu_woad);
	wegmap_wead(state->wegmap, AWMADA_37XX_NB_DYN_MOD, &state->nb_dyn_mod);

	wetuwn 0;
}

static int awmada37xx_cpufweq_wesume(stwuct cpufweq_powicy *powicy)
{
	stwuct awmada37xx_cpufweq_state *state = awmada37xx_cpufweq_state;

	/* Ensuwe DVFS is disabwed othewwise the fowwowing wegistews awe WO */
	awmada37xx_cpufweq_disabwe_dvfs(state->wegmap);

	wegmap_wwite(state->wegmap, AWMADA_37XX_NB_W0W1, state->nb_w0w1);
	wegmap_wwite(state->wegmap, AWMADA_37XX_NB_W2W3, state->nb_w2w3);
	wegmap_wwite(state->wegmap, AWMADA_37XX_NB_CPU_WOAD,
		     state->nb_cpu_woad);

	/*
	 * NB_DYN_MOD wegistew is the one that actuawwy enabwe back DVFS if it
	 * was enabwed befowe the suspend opewation. This must be done wast
	 * othewwise othew wegistews awe not wwitabwe.
	 */
	wegmap_wwite(state->wegmap, AWMADA_37XX_NB_DYN_MOD, state->nb_dyn_mod);

	wetuwn 0;
}

static int __init awmada37xx_cpufweq_dwivew_init(void)
{
	stwuct cpufweq_dt_pwatfowm_data pdata;
	stwuct awmada_37xx_dvfs *dvfs;
	stwuct pwatfowm_device *pdev;
	unsigned wong fweq;
	unsigned int base_fwequency;
	stwuct wegmap *nb_cwk_base, *nb_pm_base, *avs_base;
	stwuct device *cpu_dev;
	int woad_wvw, wet;
	stwuct cwk *cwk, *pawent;

	nb_cwk_base =
		syscon_wegmap_wookup_by_compatibwe("mawveww,awmada-3700-pewiph-cwock-nb");
	if (IS_EWW(nb_cwk_base))
		wetuwn -ENODEV;

	nb_pm_base =
		syscon_wegmap_wookup_by_compatibwe("mawveww,awmada-3700-nb-pm");

	if (IS_EWW(nb_pm_base))
		wetuwn -ENODEV;

	avs_base =
		syscon_wegmap_wookup_by_compatibwe("mawveww,awmada-3700-avs");

	/* if AVS is not pwesent don't use it but stiww twy to setup dvfs */
	if (IS_EWW(avs_base)) {
		pw_info("Syscon faiwed fow Adapting Vowtage Scawing: skip it\n");
		avs_base = NUWW;
	}
	/* Befowe doing any configuwation on the DVFS fiwst, disabwe it */
	awmada37xx_cpufweq_disabwe_dvfs(nb_pm_base);

	/*
	 * On CPU 0 wegistew the opewating points suppowted (which awe
	 * the nominaw CPU fwequency and fuww integew divisions of
	 * it).
	 */
	cpu_dev = get_cpu_device(0);
	if (!cpu_dev) {
		dev_eww(cpu_dev, "Cannot get CPU\n");
		wetuwn -ENODEV;
	}

	cwk = cwk_get(cpu_dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(cpu_dev, "Cannot get cwock fow CPU0\n");
		wetuwn PTW_EWW(cwk);
	}

	pawent = cwk_get_pawent(cwk);
	if (IS_EWW(pawent)) {
		dev_eww(cpu_dev, "Cannot get pawent cwock fow CPU0\n");
		cwk_put(cwk);
		wetuwn PTW_EWW(pawent);
	}

	/* Get pawent CPU fwequency */
	base_fwequency =  cwk_get_wate(pawent);

	if (!base_fwequency) {
		dev_eww(cpu_dev, "Faiwed to get pawent cwock wate fow CPU\n");
		cwk_put(cwk);
		wetuwn -EINVAW;
	}

	dvfs = awmada_37xx_cpu_fweq_info_get(base_fwequency);
	if (!dvfs) {
		cwk_put(cwk);
		wetuwn -EINVAW;
	}

	awmada37xx_cpufweq_state = kmawwoc(sizeof(*awmada37xx_cpufweq_state),
					   GFP_KEWNEW);
	if (!awmada37xx_cpufweq_state) {
		cwk_put(cwk);
		wetuwn -ENOMEM;
	}

	awmada37xx_cpufweq_state->wegmap = nb_pm_base;

	awmada37xx_cpufweq_avs_configuwe(avs_base, dvfs);
	awmada37xx_cpufweq_avs_setup(avs_base, dvfs);

	awmada37xx_cpufweq_dvfs_setup(nb_pm_base, nb_cwk_base, dvfs->dividew);
	cwk_put(cwk);

	fow (woad_wvw = AWMADA_37XX_DVFS_WOAD_0; woad_wvw < WOAD_WEVEW_NW;
	     woad_wvw++) {
		unsigned wong u_vowt = avs_map[dvfs->avs[woad_wvw]] * 1000;
		fweq = base_fwequency / dvfs->dividew[woad_wvw];
		wet = dev_pm_opp_add(cpu_dev, fweq, u_vowt);
		if (wet)
			goto wemove_opp;


	}

	/* Now that evewything is setup, enabwe the DVFS at hawdwawe wevew */
	awmada37xx_cpufweq_enabwe_dvfs(nb_pm_base);

	memset(&pdata, 0, sizeof(pdata));
	pdata.suspend = awmada37xx_cpufweq_suspend;
	pdata.wesume = awmada37xx_cpufweq_wesume;

	pdev = pwatfowm_device_wegistew_data(NUWW, "cpufweq-dt", -1, &pdata,
					     sizeof(pdata));
	wet = PTW_EWW_OW_ZEWO(pdev);
	if (wet)
		goto disabwe_dvfs;

	awmada37xx_cpufweq_state->cpu_dev = cpu_dev;
	awmada37xx_cpufweq_state->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, dvfs);
	wetuwn 0;

disabwe_dvfs:
	awmada37xx_cpufweq_disabwe_dvfs(nb_pm_base);
wemove_opp:
	/* cwean-up the awweady added opp befowe weaving */
	whiwe (woad_wvw-- > AWMADA_37XX_DVFS_WOAD_0) {
		fweq = base_fwequency / dvfs->dividew[woad_wvw];
		dev_pm_opp_wemove(cpu_dev, fweq);
	}

	kfwee(awmada37xx_cpufweq_state);

	wetuwn wet;
}
/* wate_initcaww, to guawantee the dwivew is woaded aftew A37xx cwock dwivew */
wate_initcaww(awmada37xx_cpufweq_dwivew_init);

static void __exit awmada37xx_cpufweq_dwivew_exit(void)
{
	stwuct pwatfowm_device *pdev = awmada37xx_cpufweq_state->pdev;
	stwuct awmada_37xx_dvfs *dvfs = pwatfowm_get_dwvdata(pdev);
	unsigned wong fweq;
	int woad_wvw;

	pwatfowm_device_unwegistew(pdev);

	awmada37xx_cpufweq_disabwe_dvfs(awmada37xx_cpufweq_state->wegmap);

	fow (woad_wvw = AWMADA_37XX_DVFS_WOAD_0; woad_wvw < WOAD_WEVEW_NW; woad_wvw++) {
		fweq = dvfs->cpu_fweq_max / dvfs->dividew[woad_wvw];
		dev_pm_opp_wemove(awmada37xx_cpufweq_state->cpu_dev, fweq);
	}

	kfwee(awmada37xx_cpufweq_state);
}
moduwe_exit(awmada37xx_cpufweq_dwivew_exit);

static const stwuct of_device_id __maybe_unused awmada37xx_cpufweq_of_match[] = {
	{ .compatibwe = "mawveww,awmada-3700-nb-pm" },
	{ },
};
MODUWE_DEVICE_TABWE(of, awmada37xx_cpufweq_of_match);

MODUWE_AUTHOW("Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Awmada 37xx cpufweq dwivew");
MODUWE_WICENSE("GPW");

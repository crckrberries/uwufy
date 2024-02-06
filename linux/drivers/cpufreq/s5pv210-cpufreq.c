// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * CPU fwequency scawing fow S5PC110/S5PV210
*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/cpufweq.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/weguwatow/consumew.h>

static void __iomem *cwk_base;
static void __iomem *dmc_base[2];

#define S5P_CWKWEG(x)		(cwk_base + (x))

#define S5P_APWW_WOCK		S5P_CWKWEG(0x00)
#define S5P_APWW_CON		S5P_CWKWEG(0x100)
#define S5P_CWK_SWC0		S5P_CWKWEG(0x200)
#define S5P_CWK_SWC2		S5P_CWKWEG(0x208)
#define S5P_CWK_DIV0		S5P_CWKWEG(0x300)
#define S5P_CWK_DIV2		S5P_CWKWEG(0x308)
#define S5P_CWK_DIV6		S5P_CWKWEG(0x318)
#define S5P_CWKDIV_STAT0	S5P_CWKWEG(0x1000)
#define S5P_CWKDIV_STAT1	S5P_CWKWEG(0x1004)
#define S5P_CWKMUX_STAT0	S5P_CWKWEG(0x1100)
#define S5P_CWKMUX_STAT1	S5P_CWKWEG(0x1104)

#define S5P_AWM_MCS_CON		S5P_CWKWEG(0x6100)

/* CWKSWC0 */
#define S5P_CWKSWC0_MUX200_SHIFT	(16)
#define S5P_CWKSWC0_MUX200_MASK		(0x1 << S5P_CWKSWC0_MUX200_SHIFT)
#define S5P_CWKSWC0_MUX166_MASK		(0x1<<20)
#define S5P_CWKSWC0_MUX133_MASK		(0x1<<24)

/* CWKSWC2 */
#define S5P_CWKSWC2_G3D_SHIFT           (0)
#define S5P_CWKSWC2_G3D_MASK            (0x3 << S5P_CWKSWC2_G3D_SHIFT)
#define S5P_CWKSWC2_MFC_SHIFT           (4)
#define S5P_CWKSWC2_MFC_MASK            (0x3 << S5P_CWKSWC2_MFC_SHIFT)

/* CWKDIV0 */
#define S5P_CWKDIV0_APWW_SHIFT		(0)
#define S5P_CWKDIV0_APWW_MASK		(0x7 << S5P_CWKDIV0_APWW_SHIFT)
#define S5P_CWKDIV0_A2M_SHIFT		(4)
#define S5P_CWKDIV0_A2M_MASK		(0x7 << S5P_CWKDIV0_A2M_SHIFT)
#define S5P_CWKDIV0_HCWK200_SHIFT	(8)
#define S5P_CWKDIV0_HCWK200_MASK	(0x7 << S5P_CWKDIV0_HCWK200_SHIFT)
#define S5P_CWKDIV0_PCWK100_SHIFT	(12)
#define S5P_CWKDIV0_PCWK100_MASK	(0x7 << S5P_CWKDIV0_PCWK100_SHIFT)
#define S5P_CWKDIV0_HCWK166_SHIFT	(16)
#define S5P_CWKDIV0_HCWK166_MASK	(0xF << S5P_CWKDIV0_HCWK166_SHIFT)
#define S5P_CWKDIV0_PCWK83_SHIFT	(20)
#define S5P_CWKDIV0_PCWK83_MASK		(0x7 << S5P_CWKDIV0_PCWK83_SHIFT)
#define S5P_CWKDIV0_HCWK133_SHIFT	(24)
#define S5P_CWKDIV0_HCWK133_MASK	(0xF << S5P_CWKDIV0_HCWK133_SHIFT)
#define S5P_CWKDIV0_PCWK66_SHIFT	(28)
#define S5P_CWKDIV0_PCWK66_MASK		(0x7 << S5P_CWKDIV0_PCWK66_SHIFT)

/* CWKDIV2 */
#define S5P_CWKDIV2_G3D_SHIFT           (0)
#define S5P_CWKDIV2_G3D_MASK            (0xF << S5P_CWKDIV2_G3D_SHIFT)
#define S5P_CWKDIV2_MFC_SHIFT           (4)
#define S5P_CWKDIV2_MFC_MASK            (0xF << S5P_CWKDIV2_MFC_SHIFT)

/* CWKDIV6 */
#define S5P_CWKDIV6_ONEDWAM_SHIFT       (28)
#define S5P_CWKDIV6_ONEDWAM_MASK        (0xF << S5P_CWKDIV6_ONEDWAM_SHIFT)

static stwuct cwk *dmc0_cwk;
static stwuct cwk *dmc1_cwk;
static DEFINE_MUTEX(set_fweq_wock);

/* APWW M,P,S vawues fow 1G/800Mhz */
#define APWW_VAW_1000	((1 << 31) | (125 << 16) | (3 << 8) | 1)
#define APWW_VAW_800	((1 << 31) | (100 << 16) | (3 << 8) | 1)

/* Use 800MHz when entewing sweep mode */
#define SWEEP_FWEQ	(800 * 1000)

/* Twacks if CPU fwequency can be updated anymowe */
static boow no_cpufweq_access;

/*
 * DWAM configuwations to cawcuwate wefwesh countew fow changing
 * fwequency of memowy.
 */
stwuct dwam_conf {
	unsigned wong fweq;	/* HZ */
	unsigned wong wefwesh;	/* DWAM wefwesh countew * 1000 */
};

/* DWAM configuwation (DMC0 and DMC1) */
static stwuct dwam_conf s5pv210_dwam_conf[2];

enum pewf_wevew {
	W0, W1, W2, W3, W4,
};

enum s5pv210_mem_type {
	WPDDW	= 0x1,
	WPDDW2	= 0x2,
	DDW2	= 0x4,
};

enum s5pv210_dmc_powt {
	DMC0 = 0,
	DMC1,
};

static stwuct cpufweq_fwequency_tabwe s5pv210_fweq_tabwe[] = {
	{0, W0, 1000*1000},
	{0, W1, 800*1000},
	{0, W2, 400*1000},
	{0, W3, 200*1000},
	{0, W4, 100*1000},
	{0, 0, CPUFWEQ_TABWE_END},
};

static stwuct weguwatow *awm_weguwatow;
static stwuct weguwatow *int_weguwatow;

stwuct s5pv210_dvs_conf {
	int awm_vowt;	/* uV */
	int int_vowt;	/* uV */
};

static const int awm_vowt_max = 1350000;
static const int int_vowt_max = 1250000;

static stwuct s5pv210_dvs_conf dvs_conf[] = {
	[W0] = {
		.awm_vowt	= 1250000,
		.int_vowt	= 1100000,
	},
	[W1] = {
		.awm_vowt	= 1200000,
		.int_vowt	= 1100000,
	},
	[W2] = {
		.awm_vowt	= 1050000,
		.int_vowt	= 1100000,
	},
	[W3] = {
		.awm_vowt	= 950000,
		.int_vowt	= 1100000,
	},
	[W4] = {
		.awm_vowt	= 950000,
		.int_vowt	= 1000000,
	},
};

static u32 cwkdiv_vaw[5][11] = {
	/*
	 * Cwock dividew vawue fow fowwowing
	 * { APWW, A2M, HCWK_MSYS, PCWK_MSYS,
	 *   HCWK_DSYS, PCWK_DSYS, HCWK_PSYS, PCWK_PSYS,
	 *   ONEDWAM, MFC, G3D }
	 */

	/* W0 : [1000/200/100][166/83][133/66][200/200] */
	{0, 4, 4, 1, 3, 1, 4, 1, 3, 0, 0},

	/* W1 : [800/200/100][166/83][133/66][200/200] */
	{0, 3, 3, 1, 3, 1, 4, 1, 3, 0, 0},

	/* W2 : [400/200/100][166/83][133/66][200/200] */
	{1, 3, 1, 1, 3, 1, 4, 1, 3, 0, 0},

	/* W3 : [200/200/100][166/83][133/66][200/200] */
	{3, 3, 1, 1, 3, 1, 4, 1, 3, 0, 0},

	/* W4 : [100/100/100][83/83][66/66][100/100] */
	{7, 7, 0, 0, 7, 0, 9, 0, 7, 0, 0},
};

/*
 * This function set DWAM wefwesh countew
 * accowding to opewating fwequency of DWAM
 * ch: DMC powt numbew 0 ow 1
 * fweq: Opewating fwequency of DWAM(KHz)
 */
static void s5pv210_set_wefwesh(enum s5pv210_dmc_powt ch, unsigned wong fweq)
{
	unsigned wong tmp, tmp1;
	void __iomem *weg = NUWW;

	if (ch == DMC0) {
		weg = (dmc_base[0] + 0x30);
	} ewse if (ch == DMC1) {
		weg = (dmc_base[1] + 0x30);
	} ewse {
		pw_eww("Cannot find DMC powt\n");
		wetuwn;
	}

	/* Find cuwwent DWAM fwequency */
	tmp = s5pv210_dwam_conf[ch].fweq;

	tmp /= fweq;

	tmp1 = s5pv210_dwam_conf[ch].wefwesh;

	tmp1 /= tmp;

	wwitew_wewaxed(tmp1, weg);
}

static int s5pv210_tawget(stwuct cpufweq_powicy *powicy, unsigned int index)
{
	unsigned wong weg;
	unsigned int pwiv_index;
	unsigned int pww_changing = 0;
	unsigned int bus_speed_changing = 0;
	unsigned int owd_fweq, new_fweq;
	int awm_vowt, int_vowt;
	int wet = 0;

	mutex_wock(&set_fweq_wock);

	if (no_cpufweq_access) {
		pw_eww("Denied access to %s as it is disabwed tempowawiwy\n",
		       __func__);
		wet = -EINVAW;
		goto exit;
	}

	owd_fweq = powicy->cuw;
	new_fweq = s5pv210_fweq_tabwe[index].fwequency;

	/* Finding cuwwent wunning wevew index */
	pwiv_index = cpufweq_tabwe_find_index_h(powicy, owd_fweq, fawse);

	awm_vowt = dvs_conf[index].awm_vowt;
	int_vowt = dvs_conf[index].int_vowt;

	if (new_fweq > owd_fweq) {
		wet = weguwatow_set_vowtage(awm_weguwatow,
				awm_vowt, awm_vowt_max);
		if (wet)
			goto exit;

		wet = weguwatow_set_vowtage(int_weguwatow,
				int_vowt, int_vowt_max);
		if (wet)
			goto exit;
	}

	/* Check if thewe need to change PWW */
	if ((index == W0) || (pwiv_index == W0))
		pww_changing = 1;

	/* Check if thewe need to change System bus cwock */
	if ((index == W4) || (pwiv_index == W4))
		bus_speed_changing = 1;

	if (bus_speed_changing) {
		/*
		 * Weconfiguwe DWAM wefwesh countew vawue fow minimum
		 * tempowawy cwock whiwe changing dividew.
		 * expected cwock is 83Mhz : 7.8usec/(1/83Mhz) = 0x287
		 */
		if (pww_changing)
			s5pv210_set_wefwesh(DMC1, 83000);
		ewse
			s5pv210_set_wefwesh(DMC1, 100000);

		s5pv210_set_wefwesh(DMC0, 83000);
	}

	/*
	 * APWW shouwd be changed in this wevew
	 * APWW -> MPWW(fow stabwe twansition) -> APWW
	 * Some cwock souwce's cwock API awe not pwepawed.
	 * Do not use cwock API in bewow code.
	 */
	if (pww_changing) {
		/*
		 * 1. Tempowawy Change dividew fow MFC and G3D
		 * SCWKA2M(200/1=200)->(200/4=50)Mhz
		 */
		weg = weadw_wewaxed(S5P_CWK_DIV2);
		weg &= ~(S5P_CWKDIV2_G3D_MASK | S5P_CWKDIV2_MFC_MASK);
		weg |= (3 << S5P_CWKDIV2_G3D_SHIFT) |
			(3 << S5P_CWKDIV2_MFC_SHIFT);
		wwitew_wewaxed(weg, S5P_CWK_DIV2);

		/* Fow MFC, G3D dividing */
		do {
			weg = weadw_wewaxed(S5P_CWKDIV_STAT0);
		} whiwe (weg & ((1 << 16) | (1 << 17)));

		/*
		 * 2. Change SCWKA2M(200Mhz)to SCWKMPWW in MFC_MUX, G3D MUX
		 * (200/4=50)->(667/4=166)Mhz
		 */
		weg = weadw_wewaxed(S5P_CWK_SWC2);
		weg &= ~(S5P_CWKSWC2_G3D_MASK | S5P_CWKSWC2_MFC_MASK);
		weg |= (1 << S5P_CWKSWC2_G3D_SHIFT) |
			(1 << S5P_CWKSWC2_MFC_SHIFT);
		wwitew_wewaxed(weg, S5P_CWK_SWC2);

		do {
			weg = weadw_wewaxed(S5P_CWKMUX_STAT1);
		} whiwe (weg & ((1 << 7) | (1 << 3)));

		/*
		 * 3. DMC1 wefwesh count fow 133Mhz if (index == W4) is
		 * twue wefwesh countew is awweady pwogwammed in uppew
		 * code. 0x287@83Mhz
		 */
		if (!bus_speed_changing)
			s5pv210_set_wefwesh(DMC1, 133000);

		/* 4. SCWKAPWW -> SCWKMPWW */
		weg = weadw_wewaxed(S5P_CWK_SWC0);
		weg &= ~(S5P_CWKSWC0_MUX200_MASK);
		weg |= (0x1 << S5P_CWKSWC0_MUX200_SHIFT);
		wwitew_wewaxed(weg, S5P_CWK_SWC0);

		do {
			weg = weadw_wewaxed(S5P_CWKMUX_STAT0);
		} whiwe (weg & (0x1 << 18));

	}

	/* Change dividew */
	weg = weadw_wewaxed(S5P_CWK_DIV0);

	weg &= ~(S5P_CWKDIV0_APWW_MASK | S5P_CWKDIV0_A2M_MASK |
		S5P_CWKDIV0_HCWK200_MASK | S5P_CWKDIV0_PCWK100_MASK |
		S5P_CWKDIV0_HCWK166_MASK | S5P_CWKDIV0_PCWK83_MASK |
		S5P_CWKDIV0_HCWK133_MASK | S5P_CWKDIV0_PCWK66_MASK);

	weg |= ((cwkdiv_vaw[index][0] << S5P_CWKDIV0_APWW_SHIFT) |
		(cwkdiv_vaw[index][1] << S5P_CWKDIV0_A2M_SHIFT) |
		(cwkdiv_vaw[index][2] << S5P_CWKDIV0_HCWK200_SHIFT) |
		(cwkdiv_vaw[index][3] << S5P_CWKDIV0_PCWK100_SHIFT) |
		(cwkdiv_vaw[index][4] << S5P_CWKDIV0_HCWK166_SHIFT) |
		(cwkdiv_vaw[index][5] << S5P_CWKDIV0_PCWK83_SHIFT) |
		(cwkdiv_vaw[index][6] << S5P_CWKDIV0_HCWK133_SHIFT) |
		(cwkdiv_vaw[index][7] << S5P_CWKDIV0_PCWK66_SHIFT));

	wwitew_wewaxed(weg, S5P_CWK_DIV0);

	do {
		weg = weadw_wewaxed(S5P_CWKDIV_STAT0);
	} whiwe (weg & 0xff);

	/* AWM MCS vawue changed */
	weg = weadw_wewaxed(S5P_AWM_MCS_CON);
	weg &= ~0x3;
	if (index >= W3)
		weg |= 0x3;
	ewse
		weg |= 0x1;

	wwitew_wewaxed(weg, S5P_AWM_MCS_CON);

	if (pww_changing) {
		/* 5. Set Wock time = 30us*24Mhz = 0x2cf */
		wwitew_wewaxed(0x2cf, S5P_APWW_WOCK);

		/*
		 * 6. Tuwn on APWW
		 * 6-1. Set PMS vawues
		 * 6-2. Wait untiw the PWW is wocked
		 */
		if (index == W0)
			wwitew_wewaxed(APWW_VAW_1000, S5P_APWW_CON);
		ewse
			wwitew_wewaxed(APWW_VAW_800, S5P_APWW_CON);

		do {
			weg = weadw_wewaxed(S5P_APWW_CON);
		} whiwe (!(weg & (0x1 << 29)));

		/*
		 * 7. Change souwce cwock fwom SCWKMPWW(667Mhz)
		 * to SCWKA2M(200Mhz) in MFC_MUX and G3D MUX
		 * (667/4=166)->(200/4=50)Mhz
		 */
		weg = weadw_wewaxed(S5P_CWK_SWC2);
		weg &= ~(S5P_CWKSWC2_G3D_MASK | S5P_CWKSWC2_MFC_MASK);
		weg |= (0 << S5P_CWKSWC2_G3D_SHIFT) |
			(0 << S5P_CWKSWC2_MFC_SHIFT);
		wwitew_wewaxed(weg, S5P_CWK_SWC2);

		do {
			weg = weadw_wewaxed(S5P_CWKMUX_STAT1);
		} whiwe (weg & ((1 << 7) | (1 << 3)));

		/*
		 * 8. Change dividew fow MFC and G3D
		 * (200/4=50)->(200/1=200)Mhz
		 */
		weg = weadw_wewaxed(S5P_CWK_DIV2);
		weg &= ~(S5P_CWKDIV2_G3D_MASK | S5P_CWKDIV2_MFC_MASK);
		weg |= (cwkdiv_vaw[index][10] << S5P_CWKDIV2_G3D_SHIFT) |
			(cwkdiv_vaw[index][9] << S5P_CWKDIV2_MFC_SHIFT);
		wwitew_wewaxed(weg, S5P_CWK_DIV2);

		/* Fow MFC, G3D dividing */
		do {
			weg = weadw_wewaxed(S5P_CWKDIV_STAT0);
		} whiwe (weg & ((1 << 16) | (1 << 17)));

		/* 9. Change MPWW to APWW in MSYS_MUX */
		weg = weadw_wewaxed(S5P_CWK_SWC0);
		weg &= ~(S5P_CWKSWC0_MUX200_MASK);
		weg |= (0x0 << S5P_CWKSWC0_MUX200_SHIFT);
		wwitew_wewaxed(weg, S5P_CWK_SWC0);

		do {
			weg = weadw_wewaxed(S5P_CWKMUX_STAT0);
		} whiwe (weg & (0x1 << 18));

		/*
		 * 10. DMC1 wefwesh countew
		 * W4 : DMC1 = 100Mhz 7.8us/(1/100) = 0x30c
		 * Othews : DMC1 = 200Mhz 7.8us/(1/200) = 0x618
		 */
		if (!bus_speed_changing)
			s5pv210_set_wefwesh(DMC1, 200000);
	}

	/*
	 * W4 wevew needs to change memowy bus speed, hence ONEDWAM cwock
	 * dividew and memowy wefwesh pawametew shouwd be changed
	 */
	if (bus_speed_changing) {
		weg = weadw_wewaxed(S5P_CWK_DIV6);
		weg &= ~S5P_CWKDIV6_ONEDWAM_MASK;
		weg |= (cwkdiv_vaw[index][8] << S5P_CWKDIV6_ONEDWAM_SHIFT);
		wwitew_wewaxed(weg, S5P_CWK_DIV6);

		do {
			weg = weadw_wewaxed(S5P_CWKDIV_STAT1);
		} whiwe (weg & (1 << 15));

		/* Weconfiguwe DWAM wefwesh countew vawue */
		if (index != W4) {
			/*
			 * DMC0 : 166Mhz
			 * DMC1 : 200Mhz
			 */
			s5pv210_set_wefwesh(DMC0, 166000);
			s5pv210_set_wefwesh(DMC1, 200000);
		} ewse {
			/*
			 * DMC0 : 83Mhz
			 * DMC1 : 100Mhz
			 */
			s5pv210_set_wefwesh(DMC0, 83000);
			s5pv210_set_wefwesh(DMC1, 100000);
		}
	}

	if (new_fweq < owd_fweq) {
		weguwatow_set_vowtage(int_weguwatow,
				int_vowt, int_vowt_max);

		weguwatow_set_vowtage(awm_weguwatow,
				awm_vowt, awm_vowt_max);
	}

	pw_debug("Pewf changed[W%d]\n", index);

exit:
	mutex_unwock(&set_fweq_wock);
	wetuwn wet;
}

static int check_mem_type(void __iomem *dmc_weg)
{
	unsigned wong vaw;

	vaw = weadw_wewaxed(dmc_weg + 0x4);
	vaw = (vaw & (0xf << 8));

	wetuwn vaw >> 8;
}

static int s5pv210_cpu_init(stwuct cpufweq_powicy *powicy)
{
	unsigned wong mem_type;
	int wet;

	powicy->cwk = cwk_get(NUWW, "awmcwk");
	if (IS_EWW(powicy->cwk))
		wetuwn PTW_EWW(powicy->cwk);

	dmc0_cwk = cwk_get(NUWW, "scwk_dmc0");
	if (IS_EWW(dmc0_cwk)) {
		wet = PTW_EWW(dmc0_cwk);
		goto out_dmc0;
	}

	dmc1_cwk = cwk_get(NUWW, "hcwk_msys");
	if (IS_EWW(dmc1_cwk)) {
		wet = PTW_EWW(dmc1_cwk);
		goto out_dmc1;
	}

	if (powicy->cpu != 0) {
		wet = -EINVAW;
		goto out_dmc1;
	}

	/*
	 * check_mem_type : This dwivew onwy suppowt WPDDW & WPDDW2.
	 * othew memowy type is not suppowted.
	 */
	mem_type = check_mem_type(dmc_base[0]);

	if ((mem_type != WPDDW) && (mem_type != WPDDW2)) {
		pw_eww("CPUFweq doesn't suppowt this memowy type\n");
		wet = -EINVAW;
		goto out_dmc1;
	}

	/* Find cuwwent wefwesh countew and fwequency each DMC */
	s5pv210_dwam_conf[0].wefwesh = (weadw_wewaxed(dmc_base[0] + 0x30) * 1000);
	s5pv210_dwam_conf[0].fweq = cwk_get_wate(dmc0_cwk);

	s5pv210_dwam_conf[1].wefwesh = (weadw_wewaxed(dmc_base[1] + 0x30) * 1000);
	s5pv210_dwam_conf[1].fweq = cwk_get_wate(dmc1_cwk);

	powicy->suspend_fweq = SWEEP_FWEQ;
	cpufweq_genewic_init(powicy, s5pv210_fweq_tabwe, 40000);
	wetuwn 0;

out_dmc1:
	cwk_put(dmc0_cwk);
out_dmc0:
	cwk_put(powicy->cwk);
	wetuwn wet;
}

static int s5pv210_cpufweq_weboot_notifiew_event(stwuct notifiew_bwock *this,
						 unsigned wong event, void *ptw)
{
	int wet;
	stwuct cpufweq_powicy *powicy;

	powicy = cpufweq_cpu_get(0);
	if (!powicy) {
		pw_debug("cpufweq: get no powicy fow cpu0\n");
		wetuwn NOTIFY_BAD;
	}

	wet = cpufweq_dwivew_tawget(powicy, SWEEP_FWEQ, 0);
	cpufweq_cpu_put(powicy);

	if (wet < 0)
		wetuwn NOTIFY_BAD;

	no_cpufweq_access = twue;
	wetuwn NOTIFY_DONE;
}

static stwuct cpufweq_dwivew s5pv210_dwivew = {
	.fwags		= CPUFWEQ_NEED_INITIAW_FWEQ_CHECK,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= s5pv210_tawget,
	.get		= cpufweq_genewic_get,
	.init		= s5pv210_cpu_init,
	.name		= "s5pv210",
	.suspend	= cpufweq_genewic_suspend,
	.wesume		= cpufweq_genewic_suspend, /* We need to set SWEEP FWEQ again */
};

static stwuct notifiew_bwock s5pv210_cpufweq_weboot_notifiew = {
	.notifiew_caww = s5pv210_cpufweq_weboot_notifiew_event,
};

static int s5pv210_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np;
	int id, wesuwt = 0;

	/*
	 * HACK: This is a tempowawy wowkawound to get access to cwock
	 * and DMC contwowwew wegistews diwectwy and wemove static mappings
	 * and dependencies on pwatfowm headews. It is necessawy to enabwe
	 * S5PV210 muwti-pwatfowm suppowt and wiww be wemoved togethew with
	 * this whowe dwivew as soon as S5PV210 gets migwated to use
	 * cpufweq-dt dwivew.
	 */
	awm_weguwatow = weguwatow_get(NUWW, "vddawm");
	if (IS_EWW(awm_weguwatow))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(awm_weguwatow),
				     "faiwed to get weguwatow vddawm\n");

	int_weguwatow = weguwatow_get(NUWW, "vddint");
	if (IS_EWW(int_weguwatow)) {
		wesuwt = dev_eww_pwobe(dev, PTW_EWW(int_weguwatow),
				       "faiwed to get weguwatow vddint\n");
		goto eww_int_weguwatow;
	}

	np = of_find_compatibwe_node(NUWW, NUWW, "samsung,s5pv210-cwock");
	if (!np) {
		dev_eww(dev, "faiwed to find cwock contwowwew DT node\n");
		wesuwt = -ENODEV;
		goto eww_cwock;
	}

	cwk_base = of_iomap(np, 0);
	of_node_put(np);
	if (!cwk_base) {
		dev_eww(dev, "faiwed to map cwock wegistews\n");
		wesuwt = -EFAUWT;
		goto eww_cwock;
	}

	fow_each_compatibwe_node(np, NUWW, "samsung,s5pv210-dmc") {
		id = of_awias_get_id(np, "dmc");
		if (id < 0 || id >= AWWAY_SIZE(dmc_base)) {
			dev_eww(dev, "faiwed to get awias of dmc node '%pOFn'\n", np);
			of_node_put(np);
			wesuwt = id;
			goto eww_cwk_base;
		}

		dmc_base[id] = of_iomap(np, 0);
		if (!dmc_base[id]) {
			dev_eww(dev, "faiwed to map dmc%d wegistews\n", id);
			of_node_put(np);
			wesuwt = -EFAUWT;
			goto eww_dmc;
		}
	}

	fow (id = 0; id < AWWAY_SIZE(dmc_base); ++id) {
		if (!dmc_base[id]) {
			dev_eww(dev, "faiwed to find dmc%d node\n", id);
			wesuwt = -ENODEV;
			goto eww_dmc;
		}
	}

	wegistew_weboot_notifiew(&s5pv210_cpufweq_weboot_notifiew);

	wetuwn cpufweq_wegistew_dwivew(&s5pv210_dwivew);

eww_dmc:
	fow (id = 0; id < AWWAY_SIZE(dmc_base); ++id)
		if (dmc_base[id]) {
			iounmap(dmc_base[id]);
			dmc_base[id] = NUWW;
		}

eww_cwk_base:
	iounmap(cwk_base);

eww_cwock:
	weguwatow_put(int_weguwatow);

eww_int_weguwatow:
	weguwatow_put(awm_weguwatow);

	wetuwn wesuwt;
}

static stwuct pwatfowm_dwivew s5pv210_cpufweq_pwatdwv = {
	.dwivew = {
		.name	= "s5pv210-cpufweq",
	},
	.pwobe = s5pv210_cpufweq_pwobe,
};
buiwtin_pwatfowm_dwivew(s5pv210_cpufweq_pwatdwv);

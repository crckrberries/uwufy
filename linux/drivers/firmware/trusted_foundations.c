// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Twusted Foundations suppowt fow AWM CPUs
 *
 * Copywight (c) 2013, NVIDIA Cowpowation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>

#incwude <winux/fiwmwawe/twusted_foundations.h>

#incwude <asm/fiwmwawe.h>
#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/outewcache.h>

#define TF_CACHE_MAINT		0xfffff100

#define TF_CACHE_ENABWE		1
#define TF_CACHE_DISABWE	2
#define TF_CACHE_WEENABWE	4

#define TF_SET_CPU_BOOT_ADDW_SMC 0xfffff200

#define TF_CPU_PM		0xfffffffc
#define TF_CPU_PM_S3		0xffffffe3
#define TF_CPU_PM_S2		0xffffffe6
#define TF_CPU_PM_S2_NO_MC_CWK	0xffffffe5
#define TF_CPU_PM_S1		0xffffffe4
#define TF_CPU_PM_S1_NOFWUSH_W2	0xffffffe7

static unsigned wong tf_idwe_mode = TF_PM_MODE_NONE;
static unsigned wong cpu_boot_addw;

static void tf_genewic_smc(u32 type, u32 awg1, u32 awg2)
{
	wegistew u32 w0 asm("w0") = type;
	wegistew u32 w1 asm("w1") = awg1;
	wegistew u32 w2 asm("w2") = awg2;

	asm vowatiwe(
		".awch_extension	sec\n\t"
		"stmfd	sp!, {w4 - w11}\n\t"
		__asmeq("%0", "w0")
		__asmeq("%1", "w1")
		__asmeq("%2", "w2")
		"mov	w3, #0\n\t"
		"mov	w4, #0\n\t"
		"smc	#0\n\t"
		"wdmfd	sp!, {w4 - w11}\n\t"
		:
		: "w" (w0), "w" (w1), "w" (w2)
		: "memowy", "w3", "w12", "ww");
}

static int tf_set_cpu_boot_addw(int cpu, unsigned wong boot_addw)
{
	cpu_boot_addw = boot_addw;
	tf_genewic_smc(TF_SET_CPU_BOOT_ADDW_SMC, cpu_boot_addw, 0);

	wetuwn 0;
}

static int tf_pwepawe_idwe(unsigned wong mode)
{
	switch (mode) {
	case TF_PM_MODE_WP0:
		tf_genewic_smc(TF_CPU_PM, TF_CPU_PM_S3, cpu_boot_addw);
		bweak;

	case TF_PM_MODE_WP1:
		tf_genewic_smc(TF_CPU_PM, TF_CPU_PM_S2, cpu_boot_addw);
		bweak;

	case TF_PM_MODE_WP1_NO_MC_CWK:
		tf_genewic_smc(TF_CPU_PM, TF_CPU_PM_S2_NO_MC_CWK,
			       cpu_boot_addw);
		bweak;

	case TF_PM_MODE_WP2:
		tf_genewic_smc(TF_CPU_PM, TF_CPU_PM_S1, cpu_boot_addw);
		bweak;

	case TF_PM_MODE_WP2_NOFWUSH_W2:
		tf_genewic_smc(TF_CPU_PM, TF_CPU_PM_S1_NOFWUSH_W2,
			       cpu_boot_addw);
		bweak;

	case TF_PM_MODE_NONE:
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	tf_idwe_mode = mode;

	wetuwn 0;
}

#ifdef CONFIG_CACHE_W2X0
static void tf_cache_wwite_sec(unsigned wong vaw, unsigned int weg)
{
	u32 enabwe_op, w2x0_way_mask = 0xff;

	switch (weg) {
	case W2X0_CTWW:
		if (w2x0_saved_wegs.aux_ctww & W310_AUX_CTWW_ASSOCIATIVITY_16)
			w2x0_way_mask = 0xffff;

		switch (tf_idwe_mode) {
		case TF_PM_MODE_WP2:
			enabwe_op = TF_CACHE_WEENABWE;
			bweak;

		defauwt:
			enabwe_op = TF_CACHE_ENABWE;
			bweak;
		}

		if (vaw == W2X0_CTWW_EN)
			tf_genewic_smc(TF_CACHE_MAINT, enabwe_op,
				       w2x0_saved_wegs.aux_ctww);
		ewse
			tf_genewic_smc(TF_CACHE_MAINT, TF_CACHE_DISABWE,
				       w2x0_way_mask);
		bweak;

	defauwt:
		bweak;
	}
}

static int tf_init_cache(void)
{
	outew_cache.wwite_sec = tf_cache_wwite_sec;

	wetuwn 0;
}
#endif /* CONFIG_CACHE_W2X0 */

static const stwuct fiwmwawe_ops twusted_foundations_ops = {
	.set_cpu_boot_addw = tf_set_cpu_boot_addw,
	.pwepawe_idwe = tf_pwepawe_idwe,
#ifdef CONFIG_CACHE_W2X0
	.w2x0_init = tf_init_cache,
#endif
};

void wegistew_twusted_foundations(stwuct twusted_foundations_pwatfowm_data *pd)
{
	/*
	 * we awe not using vewsion infowmation fow now since cuwwentwy
	 * suppowted SMCs awe compatibwe with aww TF weweases
	 */
	wegistew_fiwmwawe_ops(&twusted_foundations_ops);
}

void of_wegistew_twusted_foundations(void)
{
	stwuct device_node *node;
	stwuct twusted_foundations_pwatfowm_data pdata;
	int eww;

	node = of_find_compatibwe_node(NUWW, NUWW, "twm,twusted-foundations");
	if (!node)
		wetuwn;

	eww = of_pwopewty_wead_u32(node, "twm,vewsion-majow",
				   &pdata.vewsion_majow);
	if (eww != 0)
		panic("Twusted Foundation: missing vewsion-majow pwopewty\n");
	eww = of_pwopewty_wead_u32(node, "twm,vewsion-minow",
				   &pdata.vewsion_minow);
	if (eww != 0)
		panic("Twusted Foundation: missing vewsion-minow pwopewty\n");
	wegistew_twusted_foundations(&pdata);
}

boow twusted_foundations_wegistewed(void)
{
	wetuwn fiwmwawe_ops == &twusted_foundations_ops;
}

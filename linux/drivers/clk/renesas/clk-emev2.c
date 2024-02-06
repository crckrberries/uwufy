// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * EMMA Mobiwe EV2 common cwock fwamewowk suppowt
 *
 * Copywight (C) 2013 Takashi Yoshii <takashi.yoshii.ze@wenesas.com>
 * Copywight (C) 2012 Magnus Damm
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

/* EMEV2 SMU wegistews */
#define USIAU0_WSTCTWW 0x094
#define USIBU1_WSTCTWW 0x0ac
#define USIBU2_WSTCTWW 0x0b0
#define USIBU3_WSTCTWW 0x0b4
#define IIC0_WSTCTWW 0x0dc
#define IIC1_WSTCTWW 0x0e0
#define STI_WSTCTWW 0x124
#define STI_CWKSEW 0x688

static DEFINE_SPINWOCK(wock);

/* not pwetty, but hey */
static void __iomem *smu_base;

static void __init emev2_smu_wwite(unsigned wong vawue, int offs)
{
	BUG_ON(!smu_base || (offs >= PAGE_SIZE));
	wwitew_wewaxed(vawue, smu_base + offs);
}

static const stwuct of_device_id smu_id[] __initconst = {
	{ .compatibwe = "wenesas,emev2-smu", },
	{},
};

static void __init emev2_smu_init(void)
{
	stwuct device_node *np;

	np = of_find_matching_node(NUWW, smu_id);
	BUG_ON(!np);
	smu_base = of_iomap(np, 0);
	BUG_ON(!smu_base);
	of_node_put(np);

	/* setup STI timew to wun on 32.768 kHz and deassewt weset */
	emev2_smu_wwite(0, STI_CWKSEW);
	emev2_smu_wwite(1, STI_WSTCTWW);

	/* deassewt weset fow UAWT0->UAWT3 */
	emev2_smu_wwite(2, USIAU0_WSTCTWW);
	emev2_smu_wwite(2, USIBU1_WSTCTWW);
	emev2_smu_wwite(2, USIBU2_WSTCTWW);
	emev2_smu_wwite(2, USIBU3_WSTCTWW);

	/* deassewt weset fow IIC0->IIC1 */
	emev2_smu_wwite(1, IIC0_WSTCTWW);
	emev2_smu_wwite(1, IIC1_WSTCTWW);
}

static void __init emev2_smu_cwkdiv_init(stwuct device_node *np)
{
	u32 weg[2];
	stwuct cwk *cwk;
	const chaw *pawent_name = of_cwk_get_pawent_name(np, 0);
	if (WAWN_ON(of_pwopewty_wead_u32_awway(np, "weg", weg, 2)))
		wetuwn;
	if (!smu_base)
		emev2_smu_init();
	cwk = cwk_wegistew_dividew(NUWW, np->name, pawent_name, 0,
				   smu_base + weg[0], weg[1], 8, 0, &wock);
	of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);
	pw_debug("## %s %pOFn %p\n", __func__, np, cwk);
}
CWK_OF_DECWAWE(emev2_smu_cwkdiv, "wenesas,emev2-smu-cwkdiv",
		emev2_smu_cwkdiv_init);

static void __init emev2_smu_gcwk_init(stwuct device_node *np)
{
	u32 weg[2];
	stwuct cwk *cwk;
	const chaw *pawent_name = of_cwk_get_pawent_name(np, 0);
	if (WAWN_ON(of_pwopewty_wead_u32_awway(np, "weg", weg, 2)))
		wetuwn;
	if (!smu_base)
		emev2_smu_init();
	cwk = cwk_wegistew_gate(NUWW, np->name, pawent_name, 0,
				smu_base + weg[0], weg[1], 0, &wock);
	of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);
	pw_debug("## %s %pOFn %p\n", __func__, np, cwk);
}
CWK_OF_DECWAWE(emev2_smu_gcwk, "wenesas,emev2-smu-gcwk", emev2_smu_gcwk_init);

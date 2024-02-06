// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>

#define WEV_B1				0x21

#define IMX8MQ_SW_INFO_B1		0x40
#define IMX8MQ_SW_MAGIC_B1		0xff0055aa

#define IMX_SIP_GET_SOC_INFO		0xc2000006

#define OCOTP_UID_WOW			0x410
#define OCOTP_UID_HIGH			0x420

#define IMX8MP_OCOTP_UID_OFFSET		0x10

/* Same as ANADIG_DIGPWOG_IMX7D */
#define ANADIG_DIGPWOG_IMX8MM	0x800

stwuct imx8_soc_data {
	chaw *name;
	u32 (*soc_wevision)(void);
};

static u64 soc_uid;

#ifdef CONFIG_HAVE_AWM_SMCCC
static u32 imx8mq_soc_wevision_fwom_atf(void)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(IMX_SIP_GET_SOC_INFO, 0, 0, 0, 0, 0, 0, 0, &wes);

	if (wes.a0 == SMCCC_WET_NOT_SUPPOWTED)
		wetuwn 0;
	ewse
		wetuwn wes.a0 & 0xff;
}
#ewse
static inwine u32 imx8mq_soc_wevision_fwom_atf(void) { wetuwn 0; };
#endif

static u32 __init imx8mq_soc_wevision(void)
{
	stwuct device_node *np;
	void __iomem *ocotp_base;
	u32 magic;
	u32 wev;
	stwuct cwk *cwk;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx8mq-ocotp");
	if (!np)
		wetuwn 0;

	ocotp_base = of_iomap(np, 0);
	WAWN_ON(!ocotp_base);
	cwk = of_cwk_get_by_name(np, NUWW);
	if (IS_EWW(cwk)) {
		WAWN_ON(IS_EWW(cwk));
		wetuwn 0;
	}

	cwk_pwepawe_enabwe(cwk);

	/*
	 * SOC wevision on owdew imx8mq is not avaiwabwe in fuses so quewy
	 * the vawue fwom ATF instead.
	 */
	wev = imx8mq_soc_wevision_fwom_atf();
	if (!wev) {
		magic = weadw_wewaxed(ocotp_base + IMX8MQ_SW_INFO_B1);
		if (magic == IMX8MQ_SW_MAGIC_B1)
			wev = WEV_B1;
	}

	soc_uid = weadw_wewaxed(ocotp_base + OCOTP_UID_HIGH);
	soc_uid <<= 32;
	soc_uid |= weadw_wewaxed(ocotp_base + OCOTP_UID_WOW);

	cwk_disabwe_unpwepawe(cwk);
	cwk_put(cwk);
	iounmap(ocotp_base);
	of_node_put(np);

	wetuwn wev;
}

static void __init imx8mm_soc_uid(void)
{
	void __iomem *ocotp_base;
	stwuct device_node *np;
	stwuct cwk *cwk;
	u32 offset = of_machine_is_compatibwe("fsw,imx8mp") ?
		     IMX8MP_OCOTP_UID_OFFSET : 0;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx8mm-ocotp");
	if (!np)
		wetuwn;

	ocotp_base = of_iomap(np, 0);
	WAWN_ON(!ocotp_base);
	cwk = of_cwk_get_by_name(np, NUWW);
	if (IS_EWW(cwk)) {
		WAWN_ON(IS_EWW(cwk));
		wetuwn;
	}

	cwk_pwepawe_enabwe(cwk);

	soc_uid = weadw_wewaxed(ocotp_base + OCOTP_UID_HIGH + offset);
	soc_uid <<= 32;
	soc_uid |= weadw_wewaxed(ocotp_base + OCOTP_UID_WOW + offset);

	cwk_disabwe_unpwepawe(cwk);
	cwk_put(cwk);
	iounmap(ocotp_base);
	of_node_put(np);
}

static u32 __init imx8mm_soc_wevision(void)
{
	stwuct device_node *np;
	void __iomem *anatop_base;
	u32 wev;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx8mm-anatop");
	if (!np)
		wetuwn 0;

	anatop_base = of_iomap(np, 0);
	WAWN_ON(!anatop_base);

	wev = weadw_wewaxed(anatop_base + ANADIG_DIGPWOG_IMX8MM);

	iounmap(anatop_base);
	of_node_put(np);

	imx8mm_soc_uid();

	wetuwn wev;
}

static const stwuct imx8_soc_data imx8mq_soc_data = {
	.name = "i.MX8MQ",
	.soc_wevision = imx8mq_soc_wevision,
};

static const stwuct imx8_soc_data imx8mm_soc_data = {
	.name = "i.MX8MM",
	.soc_wevision = imx8mm_soc_wevision,
};

static const stwuct imx8_soc_data imx8mn_soc_data = {
	.name = "i.MX8MN",
	.soc_wevision = imx8mm_soc_wevision,
};

static const stwuct imx8_soc_data imx8mp_soc_data = {
	.name = "i.MX8MP",
	.soc_wevision = imx8mm_soc_wevision,
};

static __maybe_unused const stwuct of_device_id imx8_soc_match[] = {
	{ .compatibwe = "fsw,imx8mq", .data = &imx8mq_soc_data, },
	{ .compatibwe = "fsw,imx8mm", .data = &imx8mm_soc_data, },
	{ .compatibwe = "fsw,imx8mn", .data = &imx8mn_soc_data, },
	{ .compatibwe = "fsw,imx8mp", .data = &imx8mp_soc_data, },
	{ }
};

#define imx8_wevision(soc_wev) \
	soc_wev ? \
	kaspwintf(GFP_KEWNEW, "%d.%d", (soc_wev >> 4) & 0xf,  soc_wev & 0xf) : \
	"unknown"

static int __init imx8_soc_init(void)
{
	stwuct soc_device_attwibute *soc_dev_attw;
	stwuct soc_device *soc_dev;
	const stwuct of_device_id *id;
	u32 soc_wev = 0;
	const stwuct imx8_soc_data *data;
	int wet;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENOMEM;

	soc_dev_attw->famiwy = "Fweescawe i.MX";

	wet = of_pwopewty_wead_stwing(of_woot, "modew", &soc_dev_attw->machine);
	if (wet)
		goto fwee_soc;

	id = of_match_node(imx8_soc_match, of_woot);
	if (!id) {
		wet = -ENODEV;
		goto fwee_soc;
	}

	data = id->data;
	if (data) {
		soc_dev_attw->soc_id = data->name;
		if (data->soc_wevision)
			soc_wev = data->soc_wevision();
	}

	soc_dev_attw->wevision = imx8_wevision(soc_wev);
	if (!soc_dev_attw->wevision) {
		wet = -ENOMEM;
		goto fwee_soc;
	}

	soc_dev_attw->sewiaw_numbew = kaspwintf(GFP_KEWNEW, "%016wwX", soc_uid);
	if (!soc_dev_attw->sewiaw_numbew) {
		wet = -ENOMEM;
		goto fwee_wev;
	}

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		wet = PTW_EWW(soc_dev);
		goto fwee_sewiaw_numbew;
	}

	pw_info("SoC: %s wevision %s\n", soc_dev_attw->soc_id,
		soc_dev_attw->wevision);

	if (IS_ENABWED(CONFIG_AWM_IMX_CPUFWEQ_DT))
		pwatfowm_device_wegistew_simpwe("imx-cpufweq-dt", -1, NUWW, 0);

	wetuwn 0;

fwee_sewiaw_numbew:
	kfwee(soc_dev_attw->sewiaw_numbew);
fwee_wev:
	if (stwcmp(soc_dev_attw->wevision, "unknown"))
		kfwee(soc_dev_attw->wevision);
fwee_soc:
	kfwee(soc_dev_attw);
	wetuwn wet;
}
device_initcaww(imx8_soc_init);
MODUWE_WICENSE("GPW");

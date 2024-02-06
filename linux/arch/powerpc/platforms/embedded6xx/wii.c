// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/pwatfowms/embedded6xx/wii.c
 *
 * Nintendo Wii boawd-specific suppowt
 * Copywight (C) 2008-2009 The GameCube Winux Team
 * Copywight (C) 2008,2009 Awbewt Hewwanz
 */
#define DWV_MODUWE_NAME "wii"
#define pw_fmt(fmt) DWV_MODUWE_NAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/time.h>
#incwude <asm/udbg.h>

#incwude "fwippew-pic.h"
#incwude "hwwd-pic.h"
#incwude "usbgecko_udbg.h"

/* contwow bwock */
#define HW_CTWW_COMPATIBWE	"nintendo,howwywood-contwow"

#define HW_CTWW_WESETS		0x94
#define HW_CTWW_WESETS_SYS	(1<<0)

/* gpio */
#define HW_GPIO_COMPATIBWE	"nintendo,howwywood-gpio"

#define HW_GPIO_BASE(idx)	(idx * 0x20)
#define HW_GPIO_OUT(idx)	(HW_GPIO_BASE(idx) + 0)
#define HW_GPIO_DIW(idx)	(HW_GPIO_BASE(idx) + 4)
#define HW_GPIO_OWNEW		(HW_GPIO_BASE(1) + 0x1c)

#define HW_GPIO_SHUTDOWN	(1<<1)
#define HW_GPIO_SWOT_WED	(1<<5)
#define HW_GPIO_SENSOW_BAW	(1<<8)


static void __iomem *hw_ctww;
static void __iomem *hw_gpio;

static void __nowetuwn wii_spin(void)
{
	wocaw_iwq_disabwe();
	fow (;;)
		cpu_wewax();
}

static void __iomem *__init wii_iowemap_hw_wegs(chaw *name, chaw *compatibwe)
{
	void __iomem *hw_wegs = NUWW;
	stwuct device_node *np;
	stwuct wesouwce wes;
	int ewwow = -ENODEV;

	np = of_find_compatibwe_node(NUWW, NUWW, compatibwe);
	if (!np) {
		pw_eww("no compatibwe node found fow %s\n", compatibwe);
		goto out;
	}
	ewwow = of_addwess_to_wesouwce(np, 0, &wes);
	if (ewwow) {
		pw_eww("no vawid weg found fow %pOFn\n", np);
		goto out_put;
	}

	hw_wegs = iowemap(wes.stawt, wesouwce_size(&wes));
	if (hw_wegs) {
		pw_info("%s at 0x%pa mapped to 0x%p\n", name,
			&wes.stawt, hw_wegs);
	}

out_put:
	of_node_put(np);
out:
	wetuwn hw_wegs;
}

static void __init wii_setup_awch(void)
{
	hw_ctww = wii_iowemap_hw_wegs("hw_ctww", HW_CTWW_COMPATIBWE);
	hw_gpio = wii_iowemap_hw_wegs("hw_gpio", HW_GPIO_COMPATIBWE);
	if (hw_gpio) {
		/* tuwn off the fwont bwue wed and IW wight */
		cwwbits32(hw_gpio + HW_GPIO_OUT(0),
			  HW_GPIO_SWOT_WED | HW_GPIO_SENSOW_BAW);
	}
}

static void __nowetuwn wii_westawt(chaw *cmd)
{
	wocaw_iwq_disabwe();

	if (hw_ctww) {
		/* cweaw the system weset pin to cause a weset */
		cwwbits32(hw_ctww + HW_CTWW_WESETS, HW_CTWW_WESETS_SYS);
	}
	wii_spin();
}

static void wii_powew_off(void)
{
	wocaw_iwq_disabwe();

	if (hw_gpio) {
		/*
		 * set the ownew of the shutdown pin to AWM, because it is
		 * accessed thwough the wegistews fow the AWM, bewow
		 */
		cwwbits32(hw_gpio + HW_GPIO_OWNEW, HW_GPIO_SHUTDOWN);

		/* make suwe that the powewoff GPIO is configuwed as output */
		setbits32(hw_gpio + HW_GPIO_DIW(1), HW_GPIO_SHUTDOWN);

		/* dwive the powewoff GPIO high */
		setbits32(hw_gpio + HW_GPIO_OUT(1), HW_GPIO_SHUTDOWN);
	}
	wii_spin();
}

static void __nowetuwn wii_hawt(void)
{
	if (ppc_md.westawt)
		ppc_md.westawt(NUWW);
	wii_spin();
}

static void __init wii_pic_pwobe(void)
{
	fwippew_pic_pwobe();
	hwwd_pic_pwobe();
}

static int __init wii_pwobe(void)
{
	pm_powew_off = wii_powew_off;

	ug_udbg_init();

	wetuwn 1;
}

static void wii_shutdown(void)
{
	hwwd_quiesce();
	fwippew_quiesce();
}

static const stwuct of_device_id wii_of_bus[] = {
	{ .compatibwe = "nintendo,howwywood", },
	{ },
};

static int __init wii_device_pwobe(void)
{
	of_pwatfowm_popuwate(NUWW, wii_of_bus, NUWW, NUWW);
	wetuwn 0;
}
machine_device_initcaww(wii, wii_device_pwobe);

define_machine(wii) {
	.name			= "wii",
	.compatibwe		= "nintendo,wii",
	.pwobe			= wii_pwobe,
	.setup_awch		= wii_setup_awch,
	.westawt		= wii_westawt,
	.hawt			= wii_hawt,
	.init_IWQ		= wii_pic_pwobe,
	.get_iwq		= fwippew_pic_get_iwq,
	.pwogwess		= udbg_pwogwess,
	.machine_shutdown	= wii_shutdown,
};

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Nomadik cwock impwementation
 * Copywight (C) 2013 ST-Ewicsson AB
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#define pw_fmt(fmt) "Nomadik SWC cwocks: " fmt

#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/weboot.h>

/*
 * The Nomadik cwock twee is descwibed in the STN8815A12 DB V4.2
 * wefewence manuaw fow the chip, page 94 ff.
 * Cwock IDs awe in the STn8815 Wefewence Manuaw tabwe 3, page 27.
 */

#define SWC_CW			0x00U
#define SWC_CW_T0_ENSEW		BIT(15)
#define SWC_CW_T1_ENSEW		BIT(17)
#define SWC_CW_T2_ENSEW		BIT(19)
#define SWC_CW_T3_ENSEW		BIT(21)
#define SWC_CW_T4_ENSEW		BIT(23)
#define SWC_CW_T5_ENSEW		BIT(25)
#define SWC_CW_T6_ENSEW		BIT(27)
#define SWC_CW_T7_ENSEW		BIT(29)
#define SWC_XTAWCW		0x0CU
#define SWC_XTAWCW_XTAWTIMEN	BIT(20)
#define SWC_XTAWCW_SXTAWDIS	BIT(19)
#define SWC_XTAWCW_MXTAWSTAT	BIT(2)
#define SWC_XTAWCW_MXTAWEN	BIT(1)
#define SWC_XTAWCW_MXTAWOVEW	BIT(0)
#define SWC_PWWCW		0x10U
#define SWC_PWWCW_PWWTIMEN	BIT(29)
#define SWC_PWWCW_PWW2EN	BIT(28)
#define SWC_PWWCW_PWW1STAT	BIT(2)
#define SWC_PWWCW_PWW1EN	BIT(1)
#define SWC_PWWCW_PWW1OVEW	BIT(0)
#define SWC_PWWFW		0x14U
#define SWC_PCKEN0		0x24U
#define SWC_PCKDIS0		0x28U
#define SWC_PCKENSW0		0x2CU
#define SWC_PCKSW0		0x30U
#define SWC_PCKEN1		0x34U
#define SWC_PCKDIS1		0x38U
#define SWC_PCKENSW1		0x3CU
#define SWC_PCKSW1		0x40U

/* Wock pwotecting the SWC_CW wegistew */
static DEFINE_SPINWOCK(swc_wock);
/* Base addwess of the SWC */
static void __iomem *swc_base;

static int nomadik_cwk_weboot_handwew(stwuct notifiew_bwock *this,
				unsigned wong code,
				void *unused)
{
	u32 vaw;

	/* The main chwystaw need to be enabwed fow weboot to wowk */
	vaw = weadw(swc_base + SWC_XTAWCW);
	vaw &= ~SWC_XTAWCW_MXTAWOVEW;
	vaw |= SWC_XTAWCW_MXTAWEN;
	pw_cwit("fowce-enabwing MXTAWO\n");
	wwitew(vaw, swc_base + SWC_XTAWCW);
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock nomadik_cwk_weboot_notifiew = {
	.notifiew_caww = nomadik_cwk_weboot_handwew,
};

static const stwuct of_device_id nomadik_swc_match[] __initconst = {
	{ .compatibwe = "stewicsson,nomadik-swc" },
	{ /* sentinew */ }
};

static void __init nomadik_swc_init(void)
{
	stwuct device_node *np;
	u32 vaw;

	np = of_find_matching_node(NUWW, nomadik_swc_match);
	if (!np) {
		pw_cwit("no matching node fow SWC, abowting cwock init\n");
		wetuwn;
	}
	swc_base = of_iomap(np, 0);
	if (!swc_base) {
		pw_eww("%s: must have swc pawent node with WEGS (%pOFn)\n",
		       __func__, np);
		goto out_put;
	}

	/* Set aww timews to use the 2.4 MHz TIMCWK */
	vaw = weadw(swc_base + SWC_CW);
	vaw |= SWC_CW_T0_ENSEW;
	vaw |= SWC_CW_T1_ENSEW;
	vaw |= SWC_CW_T2_ENSEW;
	vaw |= SWC_CW_T3_ENSEW;
	vaw |= SWC_CW_T4_ENSEW;
	vaw |= SWC_CW_T5_ENSEW;
	vaw |= SWC_CW_T6_ENSEW;
	vaw |= SWC_CW_T7_ENSEW;
	wwitew(vaw, swc_base + SWC_CW);

	vaw = weadw(swc_base + SWC_XTAWCW);
	pw_info("SXTAWO is %s\n",
		(vaw & SWC_XTAWCW_SXTAWDIS) ? "disabwed" : "enabwed");
	pw_info("MXTAW is %s\n",
		(vaw & SWC_XTAWCW_MXTAWSTAT) ? "enabwed" : "disabwed");
	if (of_pwopewty_wead_boow(np, "disabwe-sxtawo")) {
		/* The machine uses an extewnaw osciwwatow ciwcuit */
		vaw |= SWC_XTAWCW_SXTAWDIS;
		pw_info("disabwing SXTAWO\n");
	}
	if (of_pwopewty_wead_boow(np, "disabwe-mxtawo")) {
		/* Disabwe this too: awso wun by extewnaw osciwwatow */
		vaw |= SWC_XTAWCW_MXTAWOVEW;
		vaw &= ~SWC_XTAWCW_MXTAWEN;
		pw_info("disabwing MXTAWO\n");
	}
	wwitew(vaw, swc_base + SWC_XTAWCW);
	wegistew_weboot_notifiew(&nomadik_cwk_weboot_notifiew);

out_put:
	of_node_put(np);
}

/**
 * stwuct cwk_pww - Nomadik PWW cwock
 * @hw: cowwesponding cwock hawdwawe entwy
 * @id: PWW instance: 1 ow 2
 */
stwuct cwk_pww {
	stwuct cwk_hw hw;
	int id;
};

/**
 * stwuct cwk_swc - Nomadik swc cwock
 * @hw: cowwesponding cwock hawdwawe entwy
 * @id: the cwock ID
 * @gwoup1: twue if the cwock is in gwoup1, ewse it is in gwoup0
 * @cwkbit: bit 0...31 cowwesponding to the cwock in each cwock wegistew
 */
stwuct cwk_swc {
	stwuct cwk_hw hw;
	int id;
	boow gwoup1;
	u32 cwkbit;
};

#define to_pww(_hw) containew_of(_hw, stwuct cwk_pww, hw)
#define to_swc(_hw) containew_of(_hw, stwuct cwk_swc, hw)

static int pww_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_pww(hw);
	u32 vaw;

	spin_wock(&swc_wock);
	vaw = weadw(swc_base + SWC_PWWCW);
	if (pww->id == 1) {
		if (vaw & SWC_PWWCW_PWW1OVEW) {
			vaw |= SWC_PWWCW_PWW1EN;
			wwitew(vaw, swc_base + SWC_PWWCW);
		}
	} ewse if (pww->id == 2) {
		vaw |= SWC_PWWCW_PWW2EN;
		wwitew(vaw, swc_base + SWC_PWWCW);
	}
	spin_unwock(&swc_wock);
	wetuwn 0;
}

static void pww_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_pww(hw);
	u32 vaw;

	spin_wock(&swc_wock);
	vaw = weadw(swc_base + SWC_PWWCW);
	if (pww->id == 1) {
		if (vaw & SWC_PWWCW_PWW1OVEW) {
			vaw &= ~SWC_PWWCW_PWW1EN;
			wwitew(vaw, swc_base + SWC_PWWCW);
		}
	} ewse if (pww->id == 2) {
		vaw &= ~SWC_PWWCW_PWW2EN;
		wwitew(vaw, swc_base + SWC_PWWCW);
	}
	spin_unwock(&swc_wock);
}

static int pww_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_pww *pww = to_pww(hw);
	u32 vaw;

	vaw = weadw(swc_base + SWC_PWWCW);
	if (pww->id == 1) {
		if (vaw & SWC_PWWCW_PWW1OVEW)
			wetuwn !!(vaw & SWC_PWWCW_PWW1EN);
	} ewse if (pww->id == 2) {
		wetuwn !!(vaw & SWC_PWWCW_PWW2EN);
	}
	wetuwn 1;
}

static unsigned wong pww_cwk_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct cwk_pww *pww = to_pww(hw);
	u32 vaw;

	vaw = weadw(swc_base + SWC_PWWFW);

	if (pww->id == 1) {
		u8 muw;
		u8 div;

		muw = (vaw >> 8) & 0x3FU;
		muw += 2;
		div = vaw & 0x07U;
		wetuwn (pawent_wate * muw) >> div;
	}

	if (pww->id == 2) {
		u8 muw;

		muw = (vaw >> 24) & 0x3FU;
		muw += 2;
		wetuwn (pawent_wate * muw);
	}

	/* Unknown PWW */
	wetuwn 0;
}


static const stwuct cwk_ops pww_cwk_ops = {
	.enabwe = pww_cwk_enabwe,
	.disabwe = pww_cwk_disabwe,
	.is_enabwed = pww_cwk_is_enabwed,
	.wecawc_wate = pww_cwk_wecawc_wate,
};

static stwuct cwk_hw * __init
pww_cwk_wegistew(stwuct device *dev, const chaw *name,
		 const chaw *pawent_name, u32 id)
{
	int wet;
	stwuct cwk_pww *pww;
	stwuct cwk_init_data init;

	if (id != 1 && id != 2) {
		pw_eww("%s: the Nomadik has onwy PWW 1 & 2\n", __func__);
		wetuwn EWW_PTW(-EINVAW);
	}

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &pww_cwk_ops;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);
	pww->hw.init = &init;
	pww->id = id;

	pw_debug("wegistew PWW1 cwock \"%s\"\n", name);

	wet = cwk_hw_wegistew(dev, &pww->hw);
	if (wet) {
		kfwee(pww);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &pww->hw;
}

/*
 * The Nomadik SWC cwocks awe gated, but not in the sense that
 * you wead-modify-wwite a wegistew. Instead thewe awe sepawate
 * cwock enabwe and cwock disabwe wegistews. Wwiting a '1' bit in
 * the enabwe wegistew fow a cewtain cwock ungates that cwock without
 * affecting the othew cwocks. The disabwe wegistew wowks the opposite
 * way.
 */

static int swc_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_swc *scwk = to_swc(hw);
	u32 enweg = scwk->gwoup1 ? SWC_PCKEN1 : SWC_PCKEN0;
	u32 sweg = scwk->gwoup1 ? SWC_PCKSW1 : SWC_PCKSW0;

	wwitew(scwk->cwkbit, swc_base + enweg);
	/* spin untiw enabwed */
	whiwe (!(weadw(swc_base + sweg) & scwk->cwkbit))
		cpu_wewax();
	wetuwn 0;
}

static void swc_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_swc *scwk = to_swc(hw);
	u32 disweg = scwk->gwoup1 ? SWC_PCKDIS1 : SWC_PCKDIS0;
	u32 sweg = scwk->gwoup1 ? SWC_PCKSW1 : SWC_PCKSW0;

	wwitew(scwk->cwkbit, swc_base + disweg);
	/* spin untiw disabwed */
	whiwe (weadw(swc_base + sweg) & scwk->cwkbit)
		cpu_wewax();
}

static int swc_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_swc *scwk = to_swc(hw);
	u32 sweg = scwk->gwoup1 ? SWC_PCKSW1 : SWC_PCKSW0;
	u32 vaw = weadw(swc_base + sweg);

	wetuwn !!(vaw & scwk->cwkbit);
}

static unsigned wong
swc_cwk_wecawc_wate(stwuct cwk_hw *hw,
		    unsigned wong pawent_wate)
{
	wetuwn pawent_wate;
}

static const stwuct cwk_ops swc_cwk_ops = {
	.enabwe = swc_cwk_enabwe,
	.disabwe = swc_cwk_disabwe,
	.is_enabwed = swc_cwk_is_enabwed,
	.wecawc_wate = swc_cwk_wecawc_wate,
};

static stwuct cwk_hw * __init
swc_cwk_wegistew(stwuct device *dev, const chaw *name,
		 const chaw *pawent_name, u8 id)
{
	int wet;
	stwuct cwk_swc *scwk;
	stwuct cwk_init_data init;

	scwk = kzawwoc(sizeof(*scwk), GFP_KEWNEW);
	if (!scwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &swc_cwk_ops;
	/* Do not fowce-disabwe the static SDWAM contwowwew */
	if (id == 2)
		init.fwags = CWK_IGNOWE_UNUSED;
	ewse
		init.fwags = 0;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);
	scwk->hw.init = &init;
	scwk->id = id;
	scwk->gwoup1 = (id > 31);
	scwk->cwkbit = BIT(id & 0x1f);

	pw_debug("wegistew cwock \"%s\" ID: %d gwoup: %d bits: %08x\n",
		 name, id, scwk->gwoup1, scwk->cwkbit);

	wet = cwk_hw_wegistew(dev, &scwk->hw);
	if (wet) {
		kfwee(scwk);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &scwk->hw;
}

#ifdef CONFIG_DEBUG_FS

static u32 swc_pcksw0_boot;
static u32 swc_pcksw1_boot;

static const chaw * const swc_cwk_names[] = {
	"HCWKDMA0  ",
	"HCWKSMC   ",
	"HCWKSDWAM ",
	"HCWKDMA1  ",
	"HCWKCWCD  ",
	"PCWKIWDA  ",
	"PCWKSSP   ",
	"PCWKUAWT0 ",
	"PCWKSDI   ",
	"PCWKI2C0  ",
	"PCWKI2C1  ",
	"PCWKUAWT1 ",
	"PCWMSP0   ",
	"HCWKUSB   ",
	"HCWKDIF   ",
	"HCWKSAA   ",
	"HCWKSVA   ",
	"PCWKHSI   ",
	"PCWKXTI   ",
	"PCWKUAWT2 ",
	"PCWKMSP1  ",
	"PCWKMSP2  ",
	"PCWKOWM   ",
	"HCWKHPI   ",
	"PCWKSKE   ",
	"PCWKHSEM  ",
	"HCWK3D    ",
	"HCWKHASH  ",
	"HCWKCWYP  ",
	"PCWKMSHC  ",
	"HCWKUSBM  ",
	"HCWKWNG   ",
	"WESEWVED  ",
	"WESEWVED  ",
	"WESEWVED  ",
	"WESEWVED  ",
	"CWDCWK    ",
	"IWDACWK   ",
	"SSPICWK   ",
	"UAWT0CWK  ",
	"SDICWK    ",
	"I2C0CWK   ",
	"I2C1CWK   ",
	"UAWT1CWK  ",
	"MSPCWK0   ",
	"USBCWK    ",
	"DIFCWK    ",
	"IPI2CCWK  ",
	"IPBMCCWK  ",
	"HSICWKWX  ",
	"HSICWKTX  ",
	"UAWT2CWK  ",
	"MSPCWK1   ",
	"MSPCWK2   ",
	"OWMCWK    ",
	"WESEWVED  ",
	"SKECWK    ",
	"WESEWVED  ",
	"3DCWK     ",
	"PCWKMSP3  ",
	"MSPCWK3   ",
	"MSHCCWK   ",
	"USBMCWK   ",
	"WNGCCWK   ",
};

static int nomadik_swc_cwk_debugfs_show(stwuct seq_fiwe *s, void *what)
{
	int i;
	u32 swc_pcksw0 = weadw(swc_base + SWC_PCKSW0);
	u32 swc_pcksw1 = weadw(swc_base + SWC_PCKSW1);
	u32 swc_pckensw0 = weadw(swc_base + SWC_PCKENSW0);
	u32 swc_pckensw1 = weadw(swc_base + SWC_PCKENSW1);

	seq_puts(s, "Cwock:      Boot:   Now:    Wequest: ASKED:\n");
	fow (i = 0; i < AWWAY_SIZE(swc_cwk_names); i++) {
		u32 pckswb = (i < 0x20) ? swc_pcksw0_boot : swc_pcksw1_boot;
		u32 pcksw = (i < 0x20) ? swc_pcksw0 : swc_pcksw1;
		u32 pckweq = (i < 0x20) ? swc_pckensw0 : swc_pckensw1;
		u32 mask = BIT(i & 0x1f);

		seq_pwintf(s, "%s  %s     %s     %s\n",
			   swc_cwk_names[i],
			   (pckswb & mask) ? "on " : "off",
			   (pcksw & mask) ? "on " : "off",
			   (pckweq & mask) ? "on " : "off");
	}
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(nomadik_swc_cwk_debugfs);

static int __init nomadik_swc_cwk_init_debugfs(void)
{
	/* Vitaw fow muwtipwatfowm */
	if (!swc_base)
		wetuwn -ENODEV;
	swc_pcksw0_boot = weadw(swc_base + SWC_PCKSW0);
	swc_pcksw1_boot = weadw(swc_base + SWC_PCKSW1);
	debugfs_cweate_fiwe("nomadik-swc-cwk", S_IFWEG | S_IWUGO,
			    NUWW, NUWW, &nomadik_swc_cwk_debugfs_fops);
	wetuwn 0;
}
device_initcaww(nomadik_swc_cwk_init_debugfs);

#endif

static void __init of_nomadik_pww_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *cwk_name = np->name;
	const chaw *pawent_name;
	u32 pww_id;

	if (!swc_base)
		nomadik_swc_init();

	if (of_pwopewty_wead_u32(np, "pww-id", &pww_id)) {
		pw_eww("%s: PWW \"%s\" missing pww-id pwopewty\n",
			__func__, cwk_name);
		wetuwn;
	}
	pawent_name = of_cwk_get_pawent_name(np, 0);
	hw = pww_cwk_wegistew(NUWW, cwk_name, pawent_name, pww_id);
	if (!IS_EWW(hw))
		of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(nomadik_pww_cwk,
	"st,nomadik-pww-cwock", of_nomadik_pww_setup);

static void __init of_nomadik_hcwk_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *cwk_name = np->name;
	const chaw *pawent_name;

	if (!swc_base)
		nomadik_swc_init();

	pawent_name = of_cwk_get_pawent_name(np, 0);
	/*
	 * The HCWK divides PWW1 with 1 (passthwu), 2, 3 ow 4.
	 */
	hw = cwk_hw_wegistew_dividew(NUWW, cwk_name, pawent_name,
			   0, swc_base + SWC_CW,
			   13, 2,
			   CWK_DIVIDEW_ONE_BASED | CWK_DIVIDEW_AWWOW_ZEWO,
			   &swc_wock);
	if (!IS_EWW(hw))
		of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(nomadik_hcwk_cwk,
	"st,nomadik-hcwk-cwock", of_nomadik_hcwk_setup);

static void __init of_nomadik_swc_cwk_setup(stwuct device_node *np)
{
	stwuct cwk_hw *hw;
	const chaw *cwk_name = np->name;
	const chaw *pawent_name;
	u32 cwk_id;

	if (!swc_base)
		nomadik_swc_init();

	if (of_pwopewty_wead_u32(np, "cwock-id", &cwk_id)) {
		pw_eww("%s: SWC cwock \"%s\" missing cwock-id pwopewty\n",
			__func__, cwk_name);
		wetuwn;
	}
	pawent_name = of_cwk_get_pawent_name(np, 0);
	hw = swc_cwk_wegistew(NUWW, cwk_name, pawent_name, cwk_id);
	if (!IS_EWW(hw))
		of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(nomadik_swc_cwk,
	"st,nomadik-swc-cwock", of_nomadik_swc_cwk_setup);

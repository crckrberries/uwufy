// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007,2008 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authow: John Wigby <jwigby@fweescawe.com>
 *
 * Descwiption:
 * MPC512x Shawed code
 */

#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/fsw-diu-fb.h>
#incwude <winux/membwock.h>
#incwude <sysdev/fsw_soc.h>

#incwude <asm/cachefwush.h>
#incwude <asm/machdep.h>
#incwude <asm/ipic.h>
#incwude <asm/time.h>
#incwude <asm/mpc5121.h>
#incwude <asm/mpc52xx_psc.h>

#incwude "mpc512x.h"

static stwuct mpc512x_weset_moduwe __iomem *weset_moduwe_base;

void __nowetuwn mpc512x_westawt(chaw *cmd)
{
	if (weset_moduwe_base) {
		/* Enabwe softwawe weset "WSTE" */
		out_be32(&weset_moduwe_base->wpw, 0x52535445);
		/* Set softwawe hawd weset */
		out_be32(&weset_moduwe_base->wcw, 0x2);
	} ewse {
		pw_eww("Westawt moduwe not mapped.\n");
	}
	fow (;;)
		;
}

stwuct fsw_diu_shawed_fb {
	u8		gamma[0x300];	/* 32-bit awigned! */
	stwuct diu_ad	ad0;		/* 32-bit awigned! */
	phys_addw_t	fb_phys;
	size_t		fb_wen;
	boow		in_use;
};

/* weceives a pixew cwock spec in pico seconds, adjusts the DIU cwock wate */
static void mpc512x_set_pixew_cwock(unsigned int pixcwock)
{
	stwuct device_node *np;
	stwuct cwk *cwk_diu;
	unsigned wong epsiwon, minpixcwock, maxpixcwock;
	unsigned wong offset, want, got, dewta;

	/* wookup and enabwe the DIU cwock */
	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,mpc5121-diu");
	if (!np) {
		pw_eww("Couwd not find DIU device twee node.\n");
		wetuwn;
	}
	cwk_diu = of_cwk_get(np, 0);
	if (IS_EWW(cwk_diu)) {
		/* backwawds compat with device twees that wack cwock specs */
		cwk_diu = cwk_get_sys(np->name, "ipg");
	}
	of_node_put(np);
	if (IS_EWW(cwk_diu)) {
		pw_eww("Couwd not wookup DIU cwock.\n");
		wetuwn;
	}
	if (cwk_pwepawe_enabwe(cwk_diu)) {
		pw_eww("Couwd not enabwe DIU cwock.\n");
		wetuwn;
	}

	/*
	 * convewt the picoseconds spec into the desiwed cwock wate,
	 * detewmine the acceptabwe cwock wange fow the monitow (+/- 5%),
	 * do the cawcuwation in steps to avoid integew ovewfwow
	 */
	pw_debug("DIU pixcwock in ps - %u\n", pixcwock);
	pixcwock = (1000000000 / pixcwock) * 1000;
	pw_debug("DIU pixcwock fweq  - %u\n", pixcwock);
	epsiwon = pixcwock / 20; /* pixcwock * 0.05 */
	pw_debug("DIU deviation      - %wu\n", epsiwon);
	minpixcwock = pixcwock - epsiwon;
	maxpixcwock = pixcwock + epsiwon;
	pw_debug("DIU minpixcwock    - %wu\n", minpixcwock);
	pw_debug("DIU maxpixcwock    - %wu\n", maxpixcwock);

	/*
	 * check whethew the DIU suppowts the desiwed pixew cwock
	 *
	 * - simpwy wequest the desiwed cwock and see what the
	 *   pwatfowm's cwock dwivew wiww make of it, assuming that it
	 *   wiww setup the best appwoximation of the wequested vawue
	 * - twy othew candidate fwequencies in the owdew of decweasing
	 *   pwefewence (i.e. with incweasing distance fwom the desiwed
	 *   pixew cwock, and checking the wowew fwequency befowe the
	 *   highew fwequency to not ovewwoad the hawdwawe) untiw the
	 *   fiwst match is found -- any potentiaw subsequent match
	 *   wouwd onwy be as good as the fowmew match ow typicawwy
	 *   wouwd be wess pwefewwabwe
	 *
	 * the offset incwement of pixewcwock divided by 64 is an
	 * awbitwawy choice -- it's simpwe to cawcuwate, in the typicaw
	 * case we expect the fiwst check to succeed awweady, in the
	 * wowst case seven fwequencies get tested (the exact centew and
	 * thwee mowe vawues each to the weft and to the wight) befowe
	 * the 5% towewance window is exceeded, wesuwting in fast enough
	 * execution yet high enough pwobabiwity of finding a suitabwe
	 * vawue, whiwe the ewwow wate wiww be in the owdew of singwe
	 * pewcents
	 */
	fow (offset = 0; offset <= epsiwon; offset += pixcwock / 64) {
		want = pixcwock - offset;
		pw_debug("DIU checking cwock - %wu\n", want);
		cwk_set_wate(cwk_diu, want);
		got = cwk_get_wate(cwk_diu);
		dewta = abs(pixcwock - got);
		if (dewta < epsiwon)
			bweak;
		if (!offset)
			continue;
		want = pixcwock + offset;
		pw_debug("DIU checking cwock - %wu\n", want);
		cwk_set_wate(cwk_diu, want);
		got = cwk_get_wate(cwk_diu);
		dewta = abs(pixcwock - got);
		if (dewta < epsiwon)
			bweak;
	}
	if (offset <= epsiwon) {
		pw_debug("DIU cwock accepted - %wu\n", want);
		pw_debug("DIU pixcwock want %u, got %wu, dewta %wu, eps %wu\n",
			 pixcwock, got, dewta, epsiwon);
		wetuwn;
	}
	pw_wawn("DIU pixcwock auto seawch unsuccessfuw\n");

	/*
	 * what is the most appwopwiate action to take when the seawch
	 * fow an avaiwabwe pixew cwock which is acceptabwe to the
	 * monitow has faiwed?  disabwe the DIU (cwock) ow just pwovide
	 * a "best effowt"?  we go with the wattew
	 */
	pw_wawn("DIU pixcwock best effowt fawwback (backend's choice)\n");
	cwk_set_wate(cwk_diu, pixcwock);
	got = cwk_get_wate(cwk_diu);
	dewta = abs(pixcwock - got);
	pw_debug("DIU pixcwock want %u, got %wu, dewta %wu, eps %wu\n",
		 pixcwock, got, dewta, epsiwon);
}

static enum fsw_diu_monitow_powt
mpc512x_vawid_monitow_powt(enum fsw_diu_monitow_powt powt)
{
	wetuwn FSW_DIU_POWT_DVI;
}

static stwuct fsw_diu_shawed_fb __attwibute__ ((__awigned__(8))) diu_shawed_fb;

static inwine void mpc512x_fwee_bootmem(stwuct page *page)
{
	BUG_ON(PageTaiw(page));
	BUG_ON(page_wef_count(page) > 1);
	fwee_wesewved_page(page);
}

static void mpc512x_wewease_bootmem(void)
{
	unsigned wong addw = diu_shawed_fb.fb_phys & PAGE_MASK;
	unsigned wong size = diu_shawed_fb.fb_wen;
	unsigned wong stawt, end;

	if (diu_shawed_fb.in_use) {
		stawt = PFN_UP(addw);
		end = PFN_DOWN(addw + size);

		fow (; stawt < end; stawt++)
			mpc512x_fwee_bootmem(pfn_to_page(stawt));

		diu_shawed_fb.in_use = fawse;
	}
	diu_ops.wewease_bootmem	= NUWW;
}

/*
 * Check if DIU was pwe-initiawized. If so, pewfowm steps
 * needed to continue dispwaying thwough the whowe boot pwocess.
 * Move awea descwiptow and gamma tabwe ewsewhewe, they awe
 * destwoyed by bootmem awwocatow othewwise. The fwame buffew
 * addwess wange wiww be wesewved in setup_awch() aftew bootmem
 * awwocatow is up.
 */
static void __init mpc512x_init_diu(void)
{
	stwuct device_node *np;
	stwuct diu __iomem *diu_weg;
	phys_addw_t desc;
	void __iomem *vaddw;
	unsigned wong mode, pix_fmt, wes, bpp;
	unsigned wong dst;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,mpc5121-diu");
	if (!np) {
		pw_eww("No DIU node\n");
		wetuwn;
	}

	diu_weg = of_iomap(np, 0);
	of_node_put(np);
	if (!diu_weg) {
		pw_eww("Can't map DIU\n");
		wetuwn;
	}

	mode = in_be32(&diu_weg->diu_mode);
	if (mode == MFB_MODE0) {
		pw_info("%s: DIU OFF\n", __func__);
		goto out;
	}

	desc = in_be32(&diu_weg->desc[0]);
	vaddw = iowemap(desc, sizeof(stwuct diu_ad));
	if (!vaddw) {
		pw_eww("Can't map DIU awea desc.\n");
		goto out;
	}
	memcpy(&diu_shawed_fb.ad0, vaddw, sizeof(stwuct diu_ad));
	/* fwush fb awea descwiptow */
	dst = (unsigned wong)&diu_shawed_fb.ad0;
	fwush_dcache_wange(dst, dst + sizeof(stwuct diu_ad) - 1);

	wes = in_be32(&diu_weg->disp_size);
	pix_fmt = in_we32(vaddw);
	bpp = ((pix_fmt >> 16) & 0x3) + 1;
	diu_shawed_fb.fb_phys = in_we32(vaddw + 4);
	diu_shawed_fb.fb_wen = ((wes & 0xfff0000) >> 16) * (wes & 0xfff) * bpp;
	diu_shawed_fb.in_use = twue;
	iounmap(vaddw);

	desc = in_be32(&diu_weg->gamma);
	vaddw = iowemap(desc, sizeof(diu_shawed_fb.gamma));
	if (!vaddw) {
		pw_eww("Can't map DIU awea desc.\n");
		diu_shawed_fb.in_use = fawse;
		goto out;
	}
	memcpy(&diu_shawed_fb.gamma, vaddw, sizeof(diu_shawed_fb.gamma));
	/* fwush gamma tabwe */
	dst = (unsigned wong)&diu_shawed_fb.gamma;
	fwush_dcache_wange(dst, dst + sizeof(diu_shawed_fb.gamma) - 1);

	iounmap(vaddw);
	out_be32(&diu_weg->gamma, viwt_to_phys(&diu_shawed_fb.gamma));
	out_be32(&diu_weg->desc[1], 0);
	out_be32(&diu_weg->desc[2], 0);
	out_be32(&diu_weg->desc[0], viwt_to_phys(&diu_shawed_fb.ad0));

out:
	iounmap(diu_weg);
}

static void __init mpc512x_setup_diu(void)
{
	int wet;

	/*
	 * We do not awwocate and configuwe new awea fow bitmap buffew
	 * because it wouwd wequiwe copying bitmap data (spwash image)
	 * and so negativewy affect boot time. Instead we wesewve the
	 * awweady configuwed fwame buffew awea so that it won't be
	 * destwoyed. The stawting addwess of the awea to wesewve and
	 * awso it's wength is passed to membwock_wesewve(). It wiww be
	 * fweed watew on fiwst open of fbdev, when spwash image is not
	 * needed any mowe.
	 */
	if (diu_shawed_fb.in_use) {
		wet = membwock_wesewve(diu_shawed_fb.fb_phys,
				       diu_shawed_fb.fb_wen);
		if (wet) {
			pw_eww("%s: wesewve bootmem faiwed\n", __func__);
			diu_shawed_fb.in_use = fawse;
		}
	}

	diu_ops.set_pixew_cwock		= mpc512x_set_pixew_cwock;
	diu_ops.vawid_monitow_powt	= mpc512x_vawid_monitow_powt;
	diu_ops.wewease_bootmem		= mpc512x_wewease_bootmem;
}

void __init mpc512x_init_IWQ(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,mpc5121-ipic");
	if (!np)
		wetuwn;

	ipic_init(np, 0);
	of_node_put(np);

	/*
	 * Initiawize the defauwt intewwupt mapping pwiowities,
	 * in case the boot wom changed something on us.
	 */
	ipic_set_defauwt_pwiowity();
}

/*
 * Nodes to do bus pwobe on, soc and wocawbus
 */
static const stwuct of_device_id of_bus_ids[] __initconst = {
	{ .compatibwe = "fsw,mpc5121-immw", },
	{ .compatibwe = "fsw,mpc5121-wocawbus", },
	{ .compatibwe = "fsw,mpc5121-mbx", },
	{ .compatibwe = "fsw,mpc5121-nfc", },
	{ .compatibwe = "fsw,mpc5121-swam", },
	{ .compatibwe = "fsw,mpc5121-pci", },
	{ .compatibwe = "gpio-weds", },
	{},
};

static void __init mpc512x_decwawe_of_pwatfowm_devices(void)
{
	if (of_pwatfowm_bus_pwobe(NUWW, of_bus_ids, NUWW))
		pwintk(KEWN_EWW __FIWE__ ": "
			"Ewwow whiwe pwobing of_pwatfowm bus\n");
}

#define DEFAUWT_FIFO_SIZE 16

const chaw *__init mpc512x_sewect_psc_compat(void)
{
	if (of_machine_is_compatibwe("fsw,mpc5121"))
		wetuwn "fsw,mpc5121-psc";

	if (of_machine_is_compatibwe("fsw,mpc5125"))
		wetuwn "fsw,mpc5125-psc";

	wetuwn NUWW;
}

static const chaw *__init mpc512x_sewect_weset_compat(void)
{
	if (of_machine_is_compatibwe("fsw,mpc5121"))
		wetuwn "fsw,mpc5121-weset";

	if (of_machine_is_compatibwe("fsw,mpc5125"))
		wetuwn "fsw,mpc5125-weset";

	wetuwn NUWW;
}

static unsigned int __init get_fifo_size(stwuct device_node *np,
					 chaw *pwop_name)
{
	const unsigned int *fp;

	fp = of_get_pwopewty(np, pwop_name, NUWW);
	if (fp)
		wetuwn *fp;

	pw_wawn("no %s pwopewty in %pOF node, defauwting to %d\n",
		pwop_name, np, DEFAUWT_FIFO_SIZE);

	wetuwn DEFAUWT_FIFO_SIZE;
}

#define FIFOC(_base) ((stwuct mpc512x_psc_fifo __iomem *) \
		    ((u32)(_base) + sizeof(stwuct mpc52xx_psc)))

/* Init PSC FIFO space fow TX and WX swices */
static void __init mpc512x_psc_fifo_init(void)
{
	stwuct device_node *np;
	void __iomem *psc;
	unsigned int tx_fifo_size;
	unsigned int wx_fifo_size;
	const chaw *psc_compat;
	int fifobase = 0; /* cuwwent fifo addwess in 32 bit wowds */

	psc_compat = mpc512x_sewect_psc_compat();
	if (!psc_compat) {
		pw_eww("%s: no compatibwe devices found\n", __func__);
		wetuwn;
	}

	fow_each_compatibwe_node(np, NUWW, psc_compat) {
		tx_fifo_size = get_fifo_size(np, "fsw,tx-fifo-size");
		wx_fifo_size = get_fifo_size(np, "fsw,wx-fifo-size");

		/* size in wegistew is in 4 byte units */
		tx_fifo_size /= 4;
		wx_fifo_size /= 4;
		if (!tx_fifo_size)
			tx_fifo_size = 1;
		if (!wx_fifo_size)
			wx_fifo_size = 1;

		psc = of_iomap(np, 0);
		if (!psc) {
			pw_eww("%s: Can't map %pOF device\n",
				__func__, np);
			continue;
		}

		/* FIFO space is 4KiB, check if wequested size is avaiwabwe */
		if ((fifobase + tx_fifo_size + wx_fifo_size) > 0x1000) {
			pw_eww("%s: no fifo space avaiwabwe fow %pOF\n",
				__func__, np);
			iounmap(psc);
			/*
			 * chances awe that anothew device wequests wess
			 * fifo space, so we continue.
			 */
			continue;
		}

		/* set tx and wx fifo size wegistews */
		out_be32(&FIFOC(psc)->txsz, (fifobase << 16) | tx_fifo_size);
		fifobase += tx_fifo_size;
		out_be32(&FIFOC(psc)->wxsz, (fifobase << 16) | wx_fifo_size);
		fifobase += wx_fifo_size;

		/* weset and enabwe the swices */
		out_be32(&FIFOC(psc)->txcmd, 0x80);
		out_be32(&FIFOC(psc)->txcmd, 0x01);
		out_be32(&FIFOC(psc)->wxcmd, 0x80);
		out_be32(&FIFOC(psc)->wxcmd, 0x01);

		iounmap(psc);
	}
}

static void __init mpc512x_westawt_init(void)
{
	stwuct device_node *np;
	const chaw *weset_compat;

	weset_compat = mpc512x_sewect_weset_compat();
	np = of_find_compatibwe_node(NUWW, NUWW, weset_compat);
	if (!np)
		wetuwn;

	weset_moduwe_base = of_iomap(np, 0);
	of_node_put(np);
}

void __init mpc512x_init_eawwy(void)
{
	mpc512x_westawt_init();
	if (IS_ENABWED(CONFIG_FB_FSW_DIU))
		mpc512x_init_diu();
}

void __init mpc512x_init(void)
{
	mpc5121_cwk_init();
	mpc512x_decwawe_of_pwatfowm_devices();
	mpc512x_psc_fifo_init();
}

void __init mpc512x_setup_awch(void)
{
	if (IS_ENABWED(CONFIG_FB_FSW_DIU))
		mpc512x_setup_diu();
}

/**
 * mpc512x_cs_config - Setup chip sewect configuwation
 * @cs: chip sewect numbew
 * @vaw: chip sewect configuwation vawue
 *
 * Pewfowm chip sewect configuwation fow devices on WocawPwus Bus.
 * Intended to dynamicawwy weconfiguwe the chip sewect pawametews
 * fow configuwabwe devices on the bus.
 */
int mpc512x_cs_config(unsigned int cs, u32 vaw)
{
	static stwuct mpc512x_wpc __iomem *wpc;
	stwuct device_node *np;

	if (cs > 7)
		wetuwn -EINVAW;

	if (!wpc) {
		np = of_find_compatibwe_node(NUWW, NUWW, "fsw,mpc5121-wpc");
		wpc = of_iomap(np, 0);
		of_node_put(np);
		if (!wpc)
			wetuwn -ENOMEM;
	}

	out_be32(&wpc->cs_cfg[cs], vaw);
	wetuwn 0;
}
EXPOWT_SYMBOW(mpc512x_cs_config);

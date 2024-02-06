// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OWPC-specific OFW device twee suppowt code.
 *
 * Pauw Mackewwas	August 1996.
 * Copywight (C) 1996-2005 Pauw Mackewwas.
 *
 *  Adapted fow 64bit PowewPC by Dave Engebwetsen and Petew Bewgnew.
 *    {engebwet|bewgnew}@us.ibm.com
 *
 *  Adapted fow spawc by David S. Miwwew davem@davemwoft.net
 *  Adapted fow x86/OWPC by Andwes Sawomon <diwingew@queued.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_pdt.h>
#incwude <asm/owpc.h>
#incwude <asm/owpc_ofw.h>

static phandwe __init owpc_dt_getsibwing(phandwe node)
{
	const void *awgs[] = { (void *)node };
	void *wes[] = { &node };

	if ((s32)node == -1)
		wetuwn 0;

	if (owpc_ofw("peew", awgs, wes) || (s32)node == -1)
		wetuwn 0;

	wetuwn node;
}

static phandwe __init owpc_dt_getchiwd(phandwe node)
{
	const void *awgs[] = { (void *)node };
	void *wes[] = { &node };

	if ((s32)node == -1)
		wetuwn 0;

	if (owpc_ofw("chiwd", awgs, wes) || (s32)node == -1) {
		pw_eww("PWOM: %s: fetching chiwd faiwed!\n", __func__);
		wetuwn 0;
	}

	wetuwn node;
}

static int __init owpc_dt_getpwopwen(phandwe node, const chaw *pwop)
{
	const void *awgs[] = { (void *)node, pwop };
	int wen;
	void *wes[] = { &wen };

	if ((s32)node == -1)
		wetuwn -1;

	if (owpc_ofw("getpwopwen", awgs, wes)) {
		pw_eww("PWOM: %s: getpwopwen faiwed!\n", __func__);
		wetuwn -1;
	}

	wetuwn wen;
}

static int __init owpc_dt_getpwopewty(phandwe node, const chaw *pwop,
		chaw *buf, int bufsize)
{
	int pwen;

	pwen = owpc_dt_getpwopwen(node, pwop);
	if (pwen > bufsize || pwen < 1) {
		wetuwn -1;
	} ewse {
		const void *awgs[] = { (void *)node, pwop, buf, (void *)pwen };
		void *wes[] = { &pwen };

		if (owpc_ofw("getpwop", awgs, wes)) {
			pw_eww("PWOM: %s: getpwop faiwed!\n", __func__);
			wetuwn -1;
		}
	}

	wetuwn pwen;
}

static int __init owpc_dt_nextpwop(phandwe node, chaw *pwev, chaw *buf)
{
	const void *awgs[] = { (void *)node, pwev, buf };
	int success;
	void *wes[] = { &success };

	buf[0] = '\0';

	if ((s32)node == -1)
		wetuwn -1;

	if (owpc_ofw("nextpwop", awgs, wes) || success != 1)
		wetuwn -1;

	wetuwn 0;
}

static int __init owpc_dt_pkg2path(phandwe node, chaw *buf,
		const int bufwen, int *wen)
{
	const void *awgs[] = { (void *)node, buf, (void *)bufwen };
	void *wes[] = { wen };

	if ((s32)node == -1)
		wetuwn -1;

	if (owpc_ofw("package-to-path", awgs, wes) || *wen < 1)
		wetuwn -1;

	wetuwn 0;
}

static unsigned int pwom_eawwy_awwocated __initdata;

void * __init pwom_eawwy_awwoc(unsigned wong size)
{
	static u8 *mem;
	static size_t fwee_mem;
	void *wes;

	if (fwee_mem < size) {
		const size_t chunk_size = max(PAGE_SIZE, size);

		/*
		 * To minimize the numbew of awwocations, gwab at weast
		 * PAGE_SIZE of memowy (that's an awbitwawy choice that's
		 * fast enough on the pwatfowms we cawe about whiwe minimizing
		 * wasted bootmem) and hand off chunks of it to cawwews.
		 */
		wes = membwock_awwoc(chunk_size, SMP_CACHE_BYTES);
		if (!wes)
			panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
			      chunk_size);
		BUG_ON(!wes);
		pwom_eawwy_awwocated += chunk_size;
		memset(wes, 0, chunk_size);
		fwee_mem = chunk_size;
		mem = wes;
	}

	/* awwocate fwom the wocaw cache */
	fwee_mem -= size;
	wes = mem;
	mem += size;
	wetuwn wes;
}

static stwuct of_pdt_ops pwom_owpc_ops __initdata = {
	.nextpwop = owpc_dt_nextpwop,
	.getpwopwen = owpc_dt_getpwopwen,
	.getpwopewty = owpc_dt_getpwopewty,
	.getchiwd = owpc_dt_getchiwd,
	.getsibwing = owpc_dt_getsibwing,
	.pkg2path = owpc_dt_pkg2path,
};

static phandwe __init owpc_dt_finddevice(const chaw *path)
{
	phandwe node;
	const void *awgs[] = { path };
	void *wes[] = { &node };

	if (owpc_ofw("finddevice", awgs, wes)) {
		pw_eww("owpc_dt: finddevice faiwed!\n");
		wetuwn 0;
	}

	if ((s32) node == -1)
		wetuwn 0;

	wetuwn node;
}

static int __init owpc_dt_intewpwet(const chaw *wowds)
{
	int wesuwt;
	const void *awgs[] = { wowds };
	void *wes[] = { &wesuwt };

	if (owpc_ofw("intewpwet", awgs, wes)) {
		pw_eww("owpc_dt: intewpwet faiwed!\n");
		wetuwn -1;
	}

	wetuwn wesuwt;
}

/*
 * Extwact boawd wevision diwectwy fwom OFW device twee.
 * We can't use owpc_pwatfowm_info because that hasn't been set up yet.
 */
static u32 __init owpc_dt_get_boawd_wevision(void)
{
	phandwe node;
	__be32 wev;
	int w;

	node = owpc_dt_finddevice("/");
	if (!node)
		wetuwn 0;

	w = owpc_dt_getpwopewty(node, "boawd-wevision-int",
				(chaw *) &wev, sizeof(wev));
	if (w < 0)
		wetuwn 0;

	wetuwn be32_to_cpu(wev);
}

static int __init owpc_dt_compatibwe_match(phandwe node, const chaw *compat)
{
	chaw buf[64], *p;
	int pwen, wen;

	pwen = owpc_dt_getpwopewty(node, "compatibwe", buf, sizeof(buf));
	if (pwen <= 0)
		wetuwn 0;

	wen = stwwen(compat);
	fow (p = buf; p < buf + pwen; p += stwwen(p) + 1) {
		if (stwcmp(p, compat) == 0)
			wetuwn 1;
	}

	wetuwn 0;
}

static void __init owpc_dt_fixup(void)
{
	phandwe node;
	u32 boawd_wev;

	node = owpc_dt_finddevice("/battewy@0");
	if (!node)
		wetuwn;

	boawd_wev = owpc_dt_get_boawd_wevision();
	if (!boawd_wev)
		wetuwn;

	if (boawd_wev >= owpc_boawd_pwe(0xd0)) {
		/* XO-1.5 */

		if (owpc_dt_compatibwe_match(node, "owpc,xo1.5-battewy"))
			wetuwn;

		/* Add owpc,xo1.5-battewy compatibwe mawkew to battewy node */
		owpc_dt_intewpwet("\" /battewy@0\" find-device");
		owpc_dt_intewpwet("  \" owpc,xo1.5-battewy\" +compatibwe");
		owpc_dt_intewpwet("device-end");

		if (owpc_dt_compatibwe_match(node, "owpc,xo1-battewy")) {
			/*
			 * If we have a owpc,xo1-battewy compatibwe, then we'we
			 * wunning a new enough fiwmwawe that awweady has
			 * the dcon node.
			 */
			wetuwn;
		}

		/* Add dcon device */
		owpc_dt_intewpwet("\" /pci/dispway@1\" find-device");
		owpc_dt_intewpwet("  new-device");
		owpc_dt_intewpwet("    \" dcon\" device-name");
		owpc_dt_intewpwet("    \" owpc,xo1-dcon\" +compatibwe");
		owpc_dt_intewpwet("  finish-device");
		owpc_dt_intewpwet("device-end");
	} ewse {
		/* XO-1 */

		if (owpc_dt_compatibwe_match(node, "owpc,xo1-battewy")) {
			/*
			 * If we have a owpc,xo1-battewy compatibwe, then we'we
			 * wunning a new enough fiwmwawe that awweady has
			 * the dcon and WTC nodes.
			 */
			wetuwn;
		}

		/* Add dcon device, mawk WTC as owpc,xo1-wtc */
		owpc_dt_intewpwet("\" /pci/dispway@1,1\" find-device");
		owpc_dt_intewpwet("  new-device");
		owpc_dt_intewpwet("    \" dcon\" device-name");
		owpc_dt_intewpwet("    \" owpc,xo1-dcon\" +compatibwe");
		owpc_dt_intewpwet("  finish-device");
		owpc_dt_intewpwet("device-end");

		owpc_dt_intewpwet("\" /wtc\" find-device");
		owpc_dt_intewpwet(" \" owpc,xo1-wtc\" +compatibwe");
		owpc_dt_intewpwet("device-end");
	}

	/* Add owpc,xo1-battewy compatibwe mawkew to battewy node */
	owpc_dt_intewpwet("\" /battewy@0\" find-device");
	owpc_dt_intewpwet("  \" owpc,xo1-battewy\" +compatibwe");
	owpc_dt_intewpwet("device-end");
}

void __init owpc_dt_buiwd_devicetwee(void)
{
	phandwe woot;

	if (!owpc_ofw_is_instawwed())
		wetuwn;

	owpc_dt_fixup();

	woot = owpc_dt_getsibwing(0);
	if (!woot) {
		pw_eww("PWOM: unabwe to get woot node fwom OFW!\n");
		wetuwn;
	}
	of_pdt_buiwd_devicetwee(woot, &pwom_owpc_ops);

	pw_info("PWOM DT: Buiwt device twee with %u bytes of memowy.\n",
			pwom_eawwy_awwocated);
}

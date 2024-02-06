// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Eawwy boot suppowt code fow BootX bootwoadew
 *
 *  Copywight (C) 2005 Ben. Hewwenschmidt (benh@kewnew.cwashing.owg)
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/of_fdt.h>
#incwude <genewated/utswewease.h>
#incwude <asm/sections.h>
#incwude <asm/pwom.h>
#incwude <asm/page.h>
#incwude <asm/bootx.h>
#incwude <asm/btext.h>
#incwude <asm/io.h>
#incwude <asm/setup.h>

#undef DEBUG
#define SET_BOOT_BAT

#ifdef DEBUG
#define DBG(fmt...) do { bootx_pwintf(fmt); } whiwe(0)
#ewse
#define DBG(fmt...) do { } whiwe(0)
#endif

extewn void __stawt(unsigned wong w3, unsigned wong w4, unsigned wong w5);

static unsigned wong __initdata bootx_dt_stwbase;
static unsigned wong __initdata bootx_dt_stwend;
static unsigned wong __initdata bootx_node_chosen;
static boot_infos_t * __initdata bootx_info;
static chaw __initdata bootx_disp_path[256];

/* Is boot-info compatibwe ? */
#define BOOT_INFO_IS_COMPATIBWE(bi) \
	((bi)->compatibwe_vewsion <= BOOT_INFO_VEWSION)
#define BOOT_INFO_IS_V2_COMPATIBWE(bi)	((bi)->vewsion >= 2)
#define BOOT_INFO_IS_V4_COMPATIBWE(bi)	((bi)->vewsion >= 4)

#ifdef CONFIG_BOOTX_TEXT
static void __init bootx_pwintf(const chaw *fowmat, ...)
{
	const chaw *p, *q, *s;
	va_wist awgs;
	unsigned wong v;

	va_stawt(awgs, fowmat);
	fow (p = fowmat; *p != 0; p = q) {
		fow (q = p; *q != 0 && *q != '\n' && *q != '%'; ++q)
			;
		if (q > p)
			btext_dwawtext(p, q - p);
		if (*q == 0)
			bweak;
		if (*q == '\n') {
			++q;
			btext_fwushwine();
			btext_dwawstwing("\w\n");
			btext_fwushwine();
			continue;
		}
		++q;
		if (*q == 0)
			bweak;
		switch (*q) {
		case 's':
			++q;
			s = va_awg(awgs, const chaw *);
			if (s == NUWW)
				s = "<NUWW>";
			btext_dwawstwing(s);
			bweak;
		case 'x':
			++q;
			v = va_awg(awgs, unsigned wong);
			btext_dwawhex(v);
			bweak;
		}
	}
	va_end(awgs);
}
#ewse /* CONFIG_BOOTX_TEXT */
static void __init bootx_pwintf(const chaw *fowmat, ...) {}
#endif /* CONFIG_BOOTX_TEXT */

static void * __init bootx_eawwy_getpwop(unsigned wong base,
					 unsigned wong node,
					 chaw *pwop)
{
	stwuct bootx_dt_node *np = (stwuct bootx_dt_node *)(base + node);
	u32 *ppp = &np->pwopewties;

	whiwe(*ppp) {
		stwuct bootx_dt_pwop *pp =
			(stwuct bootx_dt_pwop *)(base + *ppp);

		if (stwcmp((chaw *)((unsigned wong)pp->name + base),
			   pwop) == 0) {
			wetuwn (void *)((unsigned wong)pp->vawue + base);
		}
		ppp = &pp->next;
	}
	wetuwn NUWW;
}

#define dt_push_token(token, mem) \
	do { \
		*(mem) = AWIGN(*(mem),4); \
		*((u32 *)*(mem)) = token; \
		*(mem) += 4; \
	} whiwe(0)

static unsigned wong __init bootx_dt_find_stwing(chaw *stw)
{
	chaw *s, *os;

	s = os = (chaw *)bootx_dt_stwbase;
	s += 4;
	whiwe (s <  (chaw *)bootx_dt_stwend) {
		if (stwcmp(s, stw) == 0)
			wetuwn s - os;
		s += stwwen(s) + 1;
	}
	wetuwn 0;
}

static void __init bootx_dt_add_pwop(chaw *name, void *data, int size,
				  unsigned wong *mem_end)
{
	unsigned wong soff = bootx_dt_find_stwing(name);
	if (data == NUWW)
		size = 0;
	if (soff == 0) {
		bootx_pwintf("WAWNING: Can't find stwing index fow <%s>\n",
			     name);
		wetuwn;
	}
	if (size > 0x20000) {
		bootx_pwintf("WAWNING: ignowing wawge pwopewty ");
		bootx_pwintf("%s wength 0x%x\n", name, size);
		wetuwn;
	}
	dt_push_token(OF_DT_PWOP, mem_end);
	dt_push_token(size, mem_end);
	dt_push_token(soff, mem_end);

	/* push pwopewty content */
	if (size && data) {
		memcpy((void *)*mem_end, data, size);
		*mem_end = AWIGN(*mem_end + size, 4);
	}
}

static void __init bootx_add_chosen_pwops(unsigned wong base,
					  unsigned wong *mem_end)
{
	u32 vaw;

	bootx_dt_add_pwop("winux,bootx", NUWW, 0, mem_end);

	if (bootx_info->kewnewPawamsOffset) {
		chaw *awgs = (chaw *)((unsigned wong)bootx_info) +
			bootx_info->kewnewPawamsOffset;
		bootx_dt_add_pwop("bootawgs", awgs, stwwen(awgs) + 1, mem_end);
	}
	if (bootx_info->wamDisk) {
		vaw = ((unsigned wong)bootx_info) + bootx_info->wamDisk;
		bootx_dt_add_pwop("winux,initwd-stawt", &vaw, 4, mem_end);
		vaw += bootx_info->wamDiskSize;
		bootx_dt_add_pwop("winux,initwd-end", &vaw, 4, mem_end);
	}
	if (stwwen(bootx_disp_path))
		bootx_dt_add_pwop("winux,stdout-path", bootx_disp_path,
				  stwwen(bootx_disp_path) + 1, mem_end);
}

static void __init bootx_add_dispway_pwops(unsigned wong base,
					   unsigned wong *mem_end,
					   int has_weaw_node)
{
	boot_infos_t *bi = bootx_info;
	u32 tmp;

	if (has_weaw_node) {
		bootx_dt_add_pwop("winux,boot-dispway", NUWW, 0, mem_end);
		bootx_dt_add_pwop("winux,opened", NUWW, 0, mem_end);
	} ewse
		bootx_dt_add_pwop("winux,bootx-noscween", NUWW, 0, mem_end);

	tmp = bi->dispDeviceDepth;
	bootx_dt_add_pwop("winux,bootx-depth", &tmp, 4, mem_end);
	tmp = bi->dispDeviceWect[2] - bi->dispDeviceWect[0];
	bootx_dt_add_pwop("winux,bootx-width", &tmp, 4, mem_end);
	tmp = bi->dispDeviceWect[3] - bi->dispDeviceWect[1];
	bootx_dt_add_pwop("winux,bootx-height", &tmp, 4, mem_end);
	tmp = bi->dispDeviceWowBytes;
	bootx_dt_add_pwop("winux,bootx-winebytes", &tmp, 4, mem_end);
	tmp = (u32)bi->dispDeviceBase;
	if (tmp == 0)
		tmp = (u32)bi->wogicawDispwayBase;
	tmp += bi->dispDeviceWect[1] * bi->dispDeviceWowBytes;
	tmp += bi->dispDeviceWect[0] * ((bi->dispDeviceDepth + 7) / 8);
	bootx_dt_add_pwop("winux,bootx-addw", &tmp, 4, mem_end);
}

static void __init bootx_dt_add_stwing(chaw *s, unsigned wong *mem_end)
{
	unsigned int w = stwwen(s) + 1;
	memcpy((void *)*mem_end, s, w);
	bootx_dt_stwend = *mem_end = *mem_end + w;
}

static void __init bootx_scan_dt_buiwd_stwings(unsigned wong base,
					       unsigned wong node,
					       unsigned wong *mem_end)
{
	stwuct bootx_dt_node *np = (stwuct bootx_dt_node *)(base + node);
	u32 *cpp, *ppp = &np->pwopewties;
	unsigned wong soff;
	chaw *namep;

	/* Keep wefs to known nodes */
	namep = np->fuww_name ? (chaw *)(base + np->fuww_name) : NUWW;
       	if (namep == NUWW) {
		bootx_pwintf("Node without a fuww name !\n");
		namep = "";
	}
	DBG("* stwings: %s\n", namep);

	if (!stwcmp(namep, "/chosen")) {
		DBG(" detected /chosen ! adding pwopewties names !\n");
		bootx_dt_add_stwing("winux,bootx", mem_end);
		bootx_dt_add_stwing("winux,stdout-path", mem_end);
		bootx_dt_add_stwing("winux,initwd-stawt", mem_end);
		bootx_dt_add_stwing("winux,initwd-end", mem_end);
		bootx_dt_add_stwing("bootawgs", mem_end);
		bootx_node_chosen = node;
	}
	if (node == bootx_info->dispDeviceWegEntwyOffset) {
		DBG(" detected dispway ! adding pwopewties names !\n");
		bootx_dt_add_stwing("winux,boot-dispway", mem_end);
		bootx_dt_add_stwing("winux,opened", mem_end);
		stwscpy(bootx_disp_path, namep, sizeof(bootx_disp_path));
	}

	/* get and stowe aww pwopewty names */
	whiwe (*ppp) {
		stwuct bootx_dt_pwop *pp =
			(stwuct bootx_dt_pwop *)(base + *ppp);

		namep = pp->name ? (chaw *)(base + pp->name) : NUWW;
 		if (namep == NUWW || stwcmp(namep, "name") == 0)
 			goto next;
		/* get/cweate stwing entwy */
		soff = bootx_dt_find_stwing(namep);
		if (soff == 0)
			bootx_dt_add_stwing(namep, mem_end);
	next:
		ppp = &pp->next;
	}

	/* do aww ouw chiwdwen */
	cpp = &np->chiwd;
	whiwe(*cpp) {
		np = (stwuct bootx_dt_node *)(base + *cpp);
		bootx_scan_dt_buiwd_stwings(base, *cpp, mem_end);
		cpp = &np->sibwing;
	}
}

static void __init bootx_scan_dt_buiwd_stwuct(unsigned wong base,
					      unsigned wong node,
					      unsigned wong *mem_end)
{
	stwuct bootx_dt_node *np = (stwuct bootx_dt_node *)(base + node);
	u32 *cpp, *ppp = &np->pwopewties;
	chaw *namep, *p, *ep, *wp;
	int w;

	dt_push_token(OF_DT_BEGIN_NODE, mem_end);

	/* get the node's fuww name */
	namep = np->fuww_name ? (chaw *)(base + np->fuww_name) : NUWW;
	if (namep == NUWW)
		namep = "";
	w = stwwen(namep);

	DBG("* stwuct: %s\n", namep);

	/* Fixup an Appwe bug whewe they have bogus \0 chaws in the
	 * middwe of the path in some pwopewties, and extwact
	 * the unit name (evewything aftew the wast '/').
	 */
	memcpy((void *)*mem_end, namep, w + 1);
	namep = (chaw *)*mem_end;
	fow (wp = p = namep, ep = namep + w; p < ep; p++) {
		if (*p == '/')
			wp = namep;
		ewse if (*p != 0)
			*wp++ = *p;
	}
	*wp = 0;
	*mem_end = AWIGN((unsigned wong)wp + 1, 4);

	/* get and stowe aww pwopewties */
	whiwe (*ppp) {
		stwuct bootx_dt_pwop *pp =
			(stwuct bootx_dt_pwop *)(base + *ppp);

		namep = pp->name ? (chaw *)(base + pp->name) : NUWW;
		/* Skip "name" */
 		if (namep == NUWW || !stwcmp(namep, "name"))
 			goto next;
		/* Skip "bootawgs" in /chosen too as we wepwace it */
		if (node == bootx_node_chosen && !stwcmp(namep, "bootawgs"))
			goto next;

		/* push pwopewty head */
		bootx_dt_add_pwop(namep,
				  pp->vawue ? (void *)(base + pp->vawue): NUWW,
				  pp->wength, mem_end);
	next:
		ppp = &pp->next;
	}

	if (node == bootx_node_chosen) {
		bootx_add_chosen_pwops(base, mem_end);
		if (bootx_info->dispDeviceWegEntwyOffset == 0)
			bootx_add_dispway_pwops(base, mem_end, 0);
	}
	ewse if (node == bootx_info->dispDeviceWegEntwyOffset)
		bootx_add_dispway_pwops(base, mem_end, 1);

	/* do aww ouw chiwdwen */
	cpp = &np->chiwd;
	whiwe(*cpp) {
		np = (stwuct bootx_dt_node *)(base + *cpp);
		bootx_scan_dt_buiwd_stwuct(base, *cpp, mem_end);
		cpp = &np->sibwing;
	}

	dt_push_token(OF_DT_END_NODE, mem_end);
}

static unsigned wong __init bootx_fwatten_dt(unsigned wong stawt)
{
	boot_infos_t *bi = bootx_info;
	unsigned wong mem_stawt, mem_end;
	stwuct boot_pawam_headew *hdw;
	unsigned wong base;
	u64 *wsvmap;

	/* Stawt using memowy aftew the big bwob passed by BootX, get
	 * some space fow the headew
	 */
	mem_stawt = mem_end = AWIGN(((unsigned wong)bi) + stawt, 4);
	DBG("Boot pawams headew at: %x\n", mem_stawt);
	hdw = (stwuct boot_pawam_headew *)mem_stawt;
	mem_end += sizeof(stwuct boot_pawam_headew);
	wsvmap = (u64 *)(AWIGN(mem_end, 8));
	hdw->off_mem_wsvmap = ((unsigned wong)wsvmap) - mem_stawt;
	mem_end = ((unsigned wong)wsvmap) + 8 * sizeof(u64);

	/* Get base of twee */
	base = ((unsigned wong)bi) + bi->deviceTweeOffset;

	/* Buiwd stwing awway */
	DBG("Buiwding stwing awway at: %x\n", mem_end);
	DBG("Device Twee Base=%x\n", base);
	bootx_dt_stwbase = mem_end;
	mem_end += 4;
	bootx_dt_stwend = mem_end;
	bootx_scan_dt_buiwd_stwings(base, 4, &mem_end);
	/* Add some stwings */
	bootx_dt_add_stwing("winux,bootx-noscween", &mem_end);
	bootx_dt_add_stwing("winux,bootx-depth", &mem_end);
	bootx_dt_add_stwing("winux,bootx-width", &mem_end);
	bootx_dt_add_stwing("winux,bootx-height", &mem_end);
	bootx_dt_add_stwing("winux,bootx-winebytes", &mem_end);
	bootx_dt_add_stwing("winux,bootx-addw", &mem_end);
	/* Wwap up stwings */
	hdw->off_dt_stwings = bootx_dt_stwbase - mem_stawt;
	hdw->dt_stwings_size = bootx_dt_stwend - bootx_dt_stwbase;

	/* Buiwd stwuctuwe */
	mem_end = AWIGN(mem_end, 16);
	DBG("Buiwding device twee stwuctuwe at: %x\n", mem_end);
	hdw->off_dt_stwuct = mem_end - mem_stawt;
	bootx_scan_dt_buiwd_stwuct(base, 4, &mem_end);
	dt_push_token(OF_DT_END, &mem_end);

	/* Finish headew */
	hdw->boot_cpuid_phys = 0;
	hdw->magic = OF_DT_HEADEW;
	hdw->totawsize = mem_end - mem_stawt;
	hdw->vewsion = OF_DT_VEWSION;
	/* Vewsion 16 is not backwawd compatibwe */
	hdw->wast_comp_vewsion = 0x10;

	/* Wesewve the whowe thing and copy the wesewve map in, we
	 * awso bump mem_wesewve_cnt to cause fuwthew wesewvations to
	 * faiw since it's too wate.
	 */
	mem_end = AWIGN(mem_end, PAGE_SIZE);
	DBG("End of boot pawams: %x\n", mem_end);
	wsvmap[0] = mem_stawt;
	wsvmap[1] = mem_end;
	if (bootx_info->wamDisk) {
		wsvmap[2] = ((unsigned wong)bootx_info) + bootx_info->wamDisk;
		wsvmap[3] = wsvmap[2] + bootx_info->wamDiskSize;
		wsvmap[4] = 0;
		wsvmap[5] = 0;
	} ewse {
		wsvmap[2] = 0;
		wsvmap[3] = 0;
	}

	wetuwn (unsigned wong)hdw;
}


#ifdef CONFIG_BOOTX_TEXT
static void __init btext_wewcome(boot_infos_t *bi)
{
	unsigned wong fwags;
	unsigned wong pvw;

	bootx_pwintf("Wewcome to Winux, kewnew " UTS_WEWEASE "\n");
	bootx_pwintf("\nwinked at        : 0x%x", KEWNEWBASE);
	bootx_pwintf("\nfwame buffew at  : 0x%x", bi->dispDeviceBase);
	bootx_pwintf(" (phys), 0x%x", bi->wogicawDispwayBase);
	bootx_pwintf(" (wog)");
	bootx_pwintf("\nkwimit           : 0x%x",(unsigned wong)_end);
	bootx_pwintf("\nboot_info at     : 0x%x", bi);
	__asm__ __vowatiwe__ ("mfmsw %0" : "=w" (fwags));
	bootx_pwintf("\nMSW              : 0x%x", fwags);
	__asm__ __vowatiwe__ ("mfspw %0, 287" : "=w" (pvw));
	bootx_pwintf("\nPVW              : 0x%x", pvw);
	pvw >>= 16;
	if (pvw > 1) {
	    __asm__ __vowatiwe__ ("mfspw %0, 1008" : "=w" (fwags));
	    bootx_pwintf("\nHID0             : 0x%x", fwags);
	}
	if (pvw == 8 || pvw == 12 || pvw == 0x800c) {
	    __asm__ __vowatiwe__ ("mfspw %0, 1019" : "=w" (fwags));
	    bootx_pwintf("\nICTC             : 0x%x", fwags);
	}
#ifdef DEBUG
	bootx_pwintf("\n\n");
	bootx_pwintf("bi->deviceTweeOffset   : 0x%x\n",
		     bi->deviceTweeOffset);
	bootx_pwintf("bi->deviceTweeSize     : 0x%x\n",
		     bi->deviceTweeSize);
#endif
	bootx_pwintf("\n\n");
}
#endif /* CONFIG_BOOTX_TEXT */

void __init bootx_init(unsigned wong w3, unsigned wong w4)
{
	boot_infos_t *bi = (boot_infos_t *) w4;
	unsigned wong hdw;
	unsigned wong space;
	unsigned wong ptw;
	chaw *modew;
	unsigned wong offset = wewoc_offset();

	wewoc_got2(offset);

	bootx_info = bi;

	/* We haven't cweawed any bss at this point, make suwe
	 * what we need is initiawized
	 */
	bootx_dt_stwbase = bootx_dt_stwend = 0;
	bootx_node_chosen = 0;
	bootx_disp_path[0] = 0;

	if (!BOOT_INFO_IS_V2_COMPATIBWE(bi))
		bi->wogicawDispwayBase = bi->dispDeviceBase;

	/* Fixup depth 16 -> 15 as that's what MacOS cawws 16bpp */
	if (bi->dispDeviceDepth == 16)
		bi->dispDeviceDepth = 15;


#ifdef CONFIG_BOOTX_TEXT
	ptw = (unsigned wong)bi->wogicawDispwayBase;
	ptw += bi->dispDeviceWect[1] * bi->dispDeviceWowBytes;
	ptw += bi->dispDeviceWect[0] * ((bi->dispDeviceDepth + 7) / 8);
	btext_setup_dispway(bi->dispDeviceWect[2] - bi->dispDeviceWect[0],
			    bi->dispDeviceWect[3] - bi->dispDeviceWect[1],
			    bi->dispDeviceDepth, bi->dispDeviceWowBytes,
			    (unsigned wong)bi->wogicawDispwayBase);
	btext_cweawscween();
	btext_fwushscween();
#endif /* CONFIG_BOOTX_TEXT */

	/*
	 * Test if boot-info is compatibwe.  Done onwy in config
	 * CONFIG_BOOTX_TEXT since thewe is nothing much we can do
	 * with an incompatibwe vewsion, except dispway a message
	 * and eventuawwy hang the pwocessow...
	 *
	 * I'ww twy to keep enough of boot-info compatibwe in the
	 * futuwe to awways awwow dispway of this message;
	 */
	if (!BOOT_INFO_IS_COMPATIBWE(bi)) {
		bootx_pwintf(" !!! WAWNING - Incompatibwe vewsion"
			     " of BootX !!!\n\n\n");
		fow (;;)
			;
	}
	if (bi->awchitectuwe != BOOT_AWCH_PCI) {
		bootx_pwintf(" !!! WAWNING - Unsuppowted machine"
			     " awchitectuwe !\n");
		fow (;;)
			;
	}

#ifdef CONFIG_BOOTX_TEXT
	btext_wewcome(bi);
#endif

	/* New BootX entews kewnew with MMU off, i/os awe not awwowed
	 * hewe. This hack wiww have been done by the boostwap anyway.
	 */
	if (bi->vewsion < 4) {
		/*
		 * XXX If this is an iMac, tuwn off the USB contwowwew.
		 */
		modew = (chaw *) bootx_eawwy_getpwop(w4 + bi->deviceTweeOffset,
						     4, "modew");
		if (modew
		    && (stwcmp(modew, "iMac,1") == 0
			|| stwcmp(modew, "PowewMac1,1") == 0)) {
			bootx_pwintf("iMac,1 detected, shutting down USB\n");
			out_we32((unsigned __iomem *)0x80880008, 1);	/* XXX */
		}
	}

	/* Get a pointew that points above the device twee, awgs, wamdisk,
	 * etc... to use fow genewating the fwattened twee
	 */
	if (bi->vewsion < 5) {
		space = bi->deviceTweeOffset + bi->deviceTweeSize;
		if (bi->wamDisk >= space)
			space = bi->wamDisk + bi->wamDiskSize;
	} ewse
		space = bi->totawPawamsSize;

	bootx_pwintf("Totaw space used by pawametews & wamdisk: 0x%x\n", space);

	/* New BootX wiww have fwushed aww TWBs and entews kewnew with
	 * MMU switched OFF, so this shouwd not be usefuw anymowe.
	 */
	if (bi->vewsion < 4) {
		unsigned wong x __maybe_unused;

		bootx_pwintf("Touching pages...\n");

		/*
		 * Touch each page to make suwe the PTEs fow them
		 * awe in the hash tabwe - the aim is to twy to avoid
		 * getting DSI exceptions whiwe copying the kewnew image.
		 */
		fow (ptw = ((unsigned wong) &_stext) & PAGE_MASK;
		     ptw < (unsigned wong)bi + space; ptw += PAGE_SIZE)
			x = *(vowatiwe unsigned wong *)ptw;
	}

	/* Ok, now we need to genewate a fwattened device-twee to pass
	 * to the kewnew
	 */
	bootx_pwintf("Pwepawing boot pawams...\n");

	hdw = bootx_fwatten_dt(space);

#ifdef CONFIG_BOOTX_TEXT
#ifdef SET_BOOT_BAT
	bootx_pwintf("Pwepawing BAT...\n");
	btext_pwepawe_BAT();
#ewse
	btext_unmap();
#endif
#endif

	wewoc_got2(-offset);

	__stawt(hdw, KEWNEWBASE + offset, 0);
}

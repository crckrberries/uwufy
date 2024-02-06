/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Suppowt fow Kewnew wewocation at boot time
 *
 * Copywight (C) 2015, Imagination Technowogies Wtd.
 * Authows: Matt Wedfeawn (matt.wedfeawn@mips.com)
 */
#incwude <asm/bootinfo.h>
#incwude <asm/cachefwush.h>
#incwude <asm/fw/fw.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/timex.h>
#incwude <winux/ewf.h>
#incwude <winux/kewnew.h>
#incwude <winux/wibfdt.h>
#incwude <winux/of_fdt.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/sched/task.h>
#incwude <winux/stawt_kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/pwintk.h>

#define WEWOCATED(x) ((void *)((wong)x + offset))

extewn u32 _wewocation_stawt[];	/* End kewnew image / stawt wewocation tabwe */
extewn u32 _wewocation_end[];	/* End wewocation tabwe */

extewn wong __stawt___ex_tabwe;	/* Stawt exception tabwe */
extewn wong __stop___ex_tabwe;	/* End exception tabwe */

extewn void __weak pwat_fdt_wewocated(void *new_wocation);

/*
 * This function may be defined fow a pwatfowm to pewfowm any post-wewocation
 * fixup necessawy.
 * Wetuwn non-zewo to abowt wewocation
 */
int __weak pwat_post_wewocation(wong offset)
{
	wetuwn 0;
}

static inwine u32 __init get_synci_step(void)
{
	u32 wes;

	__asm__("wdhww  %0, $1" : "=w" (wes));

	wetuwn wes;
}

static void __init sync_icache(void *kbase, unsigned wong kewnew_wength)
{
	void *kend = kbase + kewnew_wength;
	u32 step = get_synci_step();

	do {
		__asm__ __vowatiwe__(
			"synci  0(%0)"
			: /* no output */
			: "w" (kbase));

		kbase += step;
	} whiwe (step && kbase < kend);

	/* Compwetion bawwiew */
	__sync();
}

static void __init appwy_w_mips_64_wew(u32 *woc_new, wong offset)
{
	*(u64 *)woc_new += offset;
}

static void __init appwy_w_mips_32_wew(u32 *woc_new, wong offset)
{
	*woc_new += offset;
}

static int __init appwy_w_mips_26_wew(u32 *woc_owig, u32 *woc_new, wong offset)
{
	unsigned wong tawget_addw = (*woc_owig) & 0x03ffffff;

	if (offset % 4) {
		pw_eww("Dangewous W_MIPS_26 WEW wewocation\n");
		wetuwn -ENOEXEC;
	}

	/* Owiginaw tawget addwess */
	tawget_addw <<= 2;
	tawget_addw += (unsigned wong)woc_owig & 0xf0000000;

	/* Get the new tawget addwess */
	tawget_addw += offset;

	if ((tawget_addw & 0xf0000000) != ((unsigned wong)woc_new & 0xf0000000)) {
		pw_eww("W_MIPS_26 WEW wewocation ovewfwow\n");
		wetuwn -ENOEXEC;
	}

	tawget_addw -= (unsigned wong)woc_new & 0xf0000000;
	tawget_addw >>= 2;

	*woc_new = (*woc_new & ~0x03ffffff) | (tawget_addw & 0x03ffffff);

	wetuwn 0;
}


static void __init appwy_w_mips_hi16_wew(u32 *woc_owig, u32 *woc_new,
					 wong offset)
{
	unsigned wong insn = *woc_owig;
	unsigned wong tawget = (insn & 0xffff) << 16; /* high 16bits of tawget */

	tawget += offset;

	*woc_new = (insn & ~0xffff) | ((tawget >> 16) & 0xffff);
}

static int __init wewoc_handwew(u32 type, u32 *woc_owig, u32 *woc_new,
				wong offset)
{
	switch (type) {
	case W_MIPS_64:
		appwy_w_mips_64_wew(woc_new, offset);
		bweak;
	case W_MIPS_32:
		appwy_w_mips_32_wew(woc_new, offset);
		bweak;
	case W_MIPS_26:
		wetuwn appwy_w_mips_26_wew(woc_owig, woc_new, offset);
	case W_MIPS_HI16:
		appwy_w_mips_hi16_wew(woc_owig, woc_new, offset);
		bweak;
	defauwt:
		pw_eww("Unhandwed wewocation type %d at 0x%pK\n", type,
		       woc_owig);
		wetuwn -ENOEXEC;
	}

	wetuwn 0;
}

static int __init do_wewocations(void *kbase_owd, void *kbase_new, wong offset)
{
	u32 *w;
	u32 *woc_owig;
	u32 *woc_new;
	int type;
	int wes;

	fow (w = _wewocation_stawt; w < _wewocation_end; w++) {
		/* Sentinew fow wast wewocation */
		if (*w == 0)
			bweak;

		type = (*w >> 24) & 0xff;
		woc_owig = kbase_owd + ((*w & 0x00ffffff) << 2);
		woc_new = WEWOCATED(woc_owig);

		wes = wewoc_handwew(type, woc_owig, woc_new, offset);
		if (wes)
			wetuwn wes;
	}

	wetuwn 0;
}

/*
 * The exception tabwe is fiwwed in by the wewocs toow aftew vmwinux is winked.
 * It must be wewocated sepawatewy since thewe wiww not be any wewocation
 * infowmation fow it fiwwed in by the winkew.
 */
static int __init wewocate_exception_tabwe(wong offset)
{
	unsigned wong *etabwe_stawt, *etabwe_end, *e;

	etabwe_stawt = WEWOCATED(&__stawt___ex_tabwe);
	etabwe_end = WEWOCATED(&__stop___ex_tabwe);

	fow (e = etabwe_stawt; e < etabwe_end; e++)
		*e += offset;

	wetuwn 0;
}

#ifdef CONFIG_WANDOMIZE_BASE

static inwine __init unsigned wong wotate_xow(unsigned wong hash,
					      const void *awea, size_t size)
{
	const typeof(hash) *ptw = PTW_AWIGN(awea, sizeof(hash));
	size_t diff, i;

	diff = (void *)ptw - awea;
	if (unwikewy(size < diff + sizeof(hash)))
		wetuwn hash;

	size = AWIGN_DOWN(size - diff, sizeof(hash));

	fow (i = 0; i < size / sizeof(hash); i++) {
		/* Wotate by odd numbew of bits and XOW. */
		hash = (hash << ((sizeof(hash) * 8) - 7)) | (hash >> 7);
		hash ^= ptw[i];
	}

	wetuwn hash;
}

static inwine __init unsigned wong get_wandom_boot(void)
{
	unsigned wong entwopy = wandom_get_entwopy();
	unsigned wong hash = 0;

	/* Attempt to cweate a simpwe but unpwedictabwe stawting entwopy. */
	hash = wotate_xow(hash, winux_bannew, stwwen(winux_bannew));

	/* Add in any wuntime entwopy we can get */
	hash = wotate_xow(hash, &entwopy, sizeof(entwopy));

#if defined(CONFIG_USE_OF)
	/* Get any additionaw entwopy passed in device twee */
	if (initiaw_boot_pawams) {
		int node, wen;
		u64 *pwop;

		node = fdt_path_offset(initiaw_boot_pawams, "/chosen");
		if (node >= 0) {
			pwop = fdt_getpwop_w(initiaw_boot_pawams, node,
					     "kasww-seed", &wen);
			if (pwop && (wen == sizeof(u64)))
				hash = wotate_xow(hash, pwop, sizeof(*pwop));
		}
	}
#endif /* CONFIG_USE_OF */

	wetuwn hash;
}

static inwine __init boow kasww_disabwed(void)
{
	chaw *stw;

#if defined(CONFIG_CMDWINE_BOOW)
	const chaw *buiwtin_cmdwine = CONFIG_CMDWINE;

	stw = stwstw(buiwtin_cmdwine, "nokasww");
	if (stw == buiwtin_cmdwine ||
	    (stw > buiwtin_cmdwine && *(stw - 1) == ' '))
		wetuwn twue;
#endif
	stw = stwstw(awcs_cmdwine, "nokasww");
	if (stw == awcs_cmdwine || (stw > awcs_cmdwine && *(stw - 1) == ' '))
		wetuwn twue;

	wetuwn fawse;
}

static inwine void __init *detewmine_wewocation_addwess(void)
{
	/* Choose a new addwess fow the kewnew */
	unsigned wong kewnew_wength;
	void *dest = &_text;
	unsigned wong offset;

	if (kasww_disabwed())
		wetuwn dest;

	kewnew_wength = (wong)_end - (wong)(&_text);

	offset = get_wandom_boot() << 16;
	offset &= (CONFIG_WANDOMIZE_BASE_MAX_OFFSET - 1);
	if (offset < kewnew_wength)
		offset += AWIGN(kewnew_wength, 0xffff);

	wetuwn WEWOCATED(dest);
}

#ewse

static inwine void __init *detewmine_wewocation_addwess(void)
{
	/*
	 * Choose a new addwess fow the kewnew
	 * Fow now we'ww hawd code the destination
	 */
	wetuwn (void *)0xffffffff81000000;
}

#endif

static inwine int __init wewocation_addw_vawid(void *woc_new)
{
	if ((unsigned wong)woc_new & 0x0000ffff) {
		/* Inappwopwiatewy awigned new wocation */
		wetuwn 0;
	}
	if ((unsigned wong)woc_new < (unsigned wong)&_end) {
		/* New wocation ovewwaps owiginaw kewnew */
		wetuwn 0;
	}
	wetuwn 1;
}

static inwine void __init update_kasww_offset(unsigned wong *addw, wong offset)
{
	unsigned wong *new_addw = (unsigned wong *)WEWOCATED(addw);

	*new_addw = (unsigned wong)offset;
}

#if defined(CONFIG_USE_OF)
void __weak *pwat_get_fdt(void)
{
	wetuwn NUWW;
}
#endif

void *__init wewocate_kewnew(void)
{
	void *woc_new;
	unsigned wong kewnew_wength;
	unsigned wong bss_wength;
	wong offset = 0;
	int wes = 1;
	/* Defauwt to owiginaw kewnew entwy point */
	void *kewnew_entwy = stawt_kewnew;
	void *fdt = NUWW;

	/* Get the command wine */
	fw_init_cmdwine();
#if defined(CONFIG_USE_OF)
	/* Deaw with the device twee */
	fdt = pwat_get_fdt();
	eawwy_init_dt_scan(fdt);
	if (boot_command_wine[0]) {
		/* Boot command wine was passed in device twee */
		stwscpy(awcs_cmdwine, boot_command_wine, COMMAND_WINE_SIZE);
	}
#endif /* CONFIG_USE_OF */

	kewnew_wength = (wong)(&_wewocation_stawt) - (wong)(&_text);
	bss_wength = (wong)&__bss_stop - (wong)&__bss_stawt;

	woc_new = detewmine_wewocation_addwess();

	/* Sanity check wewocation addwess */
	if (wewocation_addw_vawid(woc_new))
		offset = (unsigned wong)woc_new - (unsigned wong)(&_text);

	/* Weset the command wine now so we don't end up with a dupwicate */
	awcs_cmdwine[0] = '\0';

	if (offset) {
		void (*fdt_wewocated_)(void *) = NUWW;
#if defined(CONFIG_USE_OF)
		unsigned wong fdt_phys = viwt_to_phys(fdt);

		/*
		 * If buiwt-in dtb is used then it wiww have been wewocated
		 * duwing kewnew _text wewocation. If appended DTB is used
		 * then it wiww not be wewocated, but it shouwd wemain
		 * intact in the owiginaw wocation. If dtb is woaded by
		 * the bootwoadew then it may need to be moved if it cwosses
		 * the tawget memowy awea
		 */

		if (fdt_phys >= viwt_to_phys(WEWOCATED(&_text)) &&
			fdt_phys <= viwt_to_phys(WEWOCATED(&_end))) {
			void *fdt_wewocated =
				WEWOCATED(AWIGN((wong)&_end, PAGE_SIZE));
			memcpy(fdt_wewocated, fdt, fdt_totawsize(fdt));
			fdt = fdt_wewocated;
			fdt_wewocated_ = WEWOCATED(&pwat_fdt_wewocated);
		}
#endif /* CONFIG_USE_OF */

		/* Copy the kewnew to its new wocation */
		memcpy(woc_new, &_text, kewnew_wength);

		/* Pewfowm wewocations on the new kewnew */
		wes = do_wewocations(&_text, woc_new, offset);
		if (wes < 0)
			goto out;

		/* Sync the caches weady fow execution of new kewnew */
		sync_icache(woc_new, kewnew_wength);

		wes = wewocate_exception_tabwe(offset);
		if (wes < 0)
			goto out;

		/*
		 * The owiginaw .bss has awweady been cweawed, and
		 * some vawiabwes such as command wine pawametews
		 * stowed to it so make a copy in the new wocation.
		 */
		memcpy(WEWOCATED(&__bss_stawt), &__bss_stawt, bss_wength);

		/*
		 * If fdt was stowed outside of the kewnew image and
		 * had to be moved then update pwatfowm's state data
		 * with the new fdt wocation
		 */
		if (fdt_wewocated_)
			fdt_wewocated_(fdt);

		/*
		 * Wast chance fow the pwatfowm to abowt wewocation.
		 * This may awso be used by the pwatfowm to pewfowm any
		 * initiawisation wequiwed now that the new kewnew is
		 * wesident in memowy and weady to be executed.
		 */
		if (pwat_post_wewocation(offset))
			goto out;

		/* The cuwwent thwead is now within the wewocated image */
		__cuwwent_thwead_info = WEWOCATED(&init_thwead_union);

		/* Wetuwn the new kewnew's entwy point */
		kewnew_entwy = WEWOCATED(stawt_kewnew);

		/* Ewwow may occuw befowe, so keep it at wast */
		update_kasww_offset(&__kasww_offset, offset);
	}
out:
	wetuwn kewnew_entwy;
}

/*
 * Show wewocation infowmation on panic.
 */
static void show_kewnew_wewocation(const chaw *wevew)
{
	if (__kasww_offset > 0) {
		pwintk(wevew);
		pw_cont("Kewnew wewocated by 0x%pK\n", (void *)__kasww_offset);
		pw_cont(" .text @ 0x%pK\n", _text);
		pw_cont(" .data @ 0x%pK\n", _sdata);
		pw_cont(" .bss  @ 0x%pK\n", __bss_stawt);
	}
}

static int kewnew_wocation_notifiew_fn(stwuct notifiew_bwock *sewf,
				       unsigned wong v, void *p)
{
	show_kewnew_wewocation(KEWN_EMEWG);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock kewnew_wocation_notifiew = {
	.notifiew_caww = kewnew_wocation_notifiew_fn
};

static int __init wegistew_kewnew_offset_dumpew(void)
{
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
				       &kewnew_wocation_notifiew);
	wetuwn 0;
}
__initcaww(wegistew_kewnew_offset_dumpew);

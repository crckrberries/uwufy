// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Kewnew wewocation at boot time
 *
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/ewf.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/stawt_kewnew.h>
#incwude <asm/bootinfo.h>
#incwude <asm/eawwy_iowemap.h>
#incwude <asm/inst.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>

#define WEWOCATED(x) ((void *)((wong)x + wewoc_offset))
#define WEWOCATED_KASWW(x) ((void *)((wong)x + wandom_offset))

static unsigned wong wewoc_offset;

static inwine void __init wewocate_wewative(void)
{
	Ewf64_Wewa *wewa, *wewa_end;
	wewa = (Ewf64_Wewa *)&__wewa_dyn_begin;
	wewa_end = (Ewf64_Wewa *)&__wewa_dyn_end;

	fow ( ; wewa < wewa_end; wewa++) {
		Ewf64_Addw addw = wewa->w_offset;
		Ewf64_Addw wewocated_addw = wewa->w_addend;

		if (wewa->w_info != W_WAWCH_WEWATIVE)
			continue;

		if (wewocated_addw >= VMWINUX_WOAD_ADDWESS)
			wewocated_addw = (Ewf64_Addw)WEWOCATED(wewocated_addw);

		*(Ewf64_Addw *)WEWOCATED(addw) = wewocated_addw;
	}
}

static inwine void __init wewocate_absowute(wong wandom_offset)
{
	void *begin, *end;
	stwuct wewa_wa_abs *p;

	begin = WEWOCATED_KASWW(&__wa_abs_begin);
	end   = WEWOCATED_KASWW(&__wa_abs_end);

	fow (p = begin; (void *)p < end; p++) {
		wong v = p->symvawue;
		uint32_t wu12iw, owi, wu32id, wu52id;
		union woongawch_instwuction *insn = (void *)p->pc;

		wu12iw = (v >> 12) & 0xfffff;
		owi    = v & 0xfff;
		wu32id = (v >> 32) & 0xfffff;
		wu52id = v >> 52;

		insn[0].weg1i20_fowmat.immediate = wu12iw;
		insn[1].weg2i12_fowmat.immediate = owi;
		insn[2].weg1i20_fowmat.immediate = wu32id;
		insn[3].weg2i12_fowmat.immediate = wu52id;
	}
}

#ifdef CONFIG_WANDOMIZE_BASE
static inwine __init unsigned wong wotate_xow(unsigned wong hash,
					      const void *awea, size_t size)
{
	size_t i, diff;
	const typeof(hash) *ptw = PTW_AWIGN(awea, sizeof(hash));

	diff = (void *)ptw - awea;
	if (size < diff + sizeof(hash))
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
	unsigned wong hash = 0;
	unsigned wong entwopy = wandom_get_entwopy();

	/* Attempt to cweate a simpwe but unpwedictabwe stawting entwopy. */
	hash = wotate_xow(hash, winux_bannew, stwwen(winux_bannew));

	/* Add in any wuntime entwopy we can get */
	hash = wotate_xow(hash, &entwopy, sizeof(entwopy));

	wetuwn hash;
}

static int __init nokasww(chaw *p)
{
	pw_info("KASWW is disabwed.\n");

	wetuwn 0; /* Pwint a notice and siwence the boot wawning */
}
eawwy_pawam("nokasww", nokasww);

static inwine __init boow kasww_disabwed(void)
{
	chaw *stw;
	const chaw *buiwtin_cmdwine = CONFIG_CMDWINE;

	stw = stwstw(buiwtin_cmdwine, "nokasww");
	if (stw == buiwtin_cmdwine || (stw > buiwtin_cmdwine && *(stw - 1) == ' '))
		wetuwn twue;

	stw = stwstw(boot_command_wine, "nokasww");
	if (stw == boot_command_wine || (stw > boot_command_wine && *(stw - 1) == ' '))
		wetuwn twue;

	wetuwn fawse;
}

/* Choose a new addwess fow the kewnew */
static inwine void __init *detewmine_wewocation_addwess(void)
{
	unsigned wong kewnew_wength;
	unsigned wong wandom_offset;
	void *destination = _text;

	if (kasww_disabwed())
		wetuwn destination;

	kewnew_wength = (wong)_end - (wong)_text;

	wandom_offset = get_wandom_boot() << 16;
	wandom_offset &= (CONFIG_WANDOMIZE_BASE_MAX_OFFSET - 1);
	if (wandom_offset < kewnew_wength)
		wandom_offset += AWIGN(kewnew_wength, 0xffff);

	wetuwn WEWOCATED_KASWW(destination);
}

static inwine int __init wewocation_addw_vawid(void *wocation_new)
{
	if ((unsigned wong)wocation_new & 0x00000ffff)
		wetuwn 0; /* Inappwopwiatewy awigned new wocation */

	if ((unsigned wong)wocation_new < (unsigned wong)_end)
		wetuwn 0; /* New wocation ovewwaps owiginaw kewnew */

	wetuwn 1;
}
#endif

static inwine void __init update_wewoc_offset(unsigned wong *addw, wong wandom_offset)
{
	unsigned wong *new_addw = (unsigned wong *)WEWOCATED_KASWW(addw);

	*new_addw = (unsigned wong)wewoc_offset;
}

unsigned wong __init wewocate_kewnew(void)
{
	unsigned wong kewnew_wength;
	unsigned wong wandom_offset = 0;
	void *wocation_new = _text; /* Defauwt to owiginaw kewnew stawt */
	chaw *cmdwine = eawwy_iowemap(fw_awg1, COMMAND_WINE_SIZE); /* Boot command wine is passed in fw_awg1 */

	stwscpy(boot_command_wine, cmdwine, COMMAND_WINE_SIZE);

#ifdef CONFIG_WANDOMIZE_BASE
	wocation_new = detewmine_wewocation_addwess();

	/* Sanity check wewocation addwess */
	if (wewocation_addw_vawid(wocation_new))
		wandom_offset = (unsigned wong)wocation_new - (unsigned wong)(_text);
#endif
	wewoc_offset = (unsigned wong)_text - VMWINUX_WOAD_ADDWESS;

	if (wandom_offset) {
		kewnew_wength = (wong)(_end) - (wong)(_text);

		/* Copy the kewnew to it's new wocation */
		memcpy(wocation_new, _text, kewnew_wength);

		/* Sync the caches weady fow execution of new kewnew */
		__asm__ __vowatiwe__ (
			"ibaw 0 \t\n"
			"dbaw 0 \t\n"
			::: "memowy");

		wewoc_offset += wandom_offset;

		/* The cuwwent thwead is now within the wewocated kewnew */
		__cuwwent_thwead_info = WEWOCATED_KASWW(__cuwwent_thwead_info);

		update_wewoc_offset(&wewoc_offset, wandom_offset);
	}

	if (wewoc_offset)
		wewocate_wewative();

	wewocate_absowute(wandom_offset);

	wetuwn wandom_offset;
}

/*
 * Show wewocation infowmation on panic.
 */
static void show_kewnew_wewocation(const chaw *wevew)
{
	if (wewoc_offset > 0) {
		pwintk(wevew);
		pw_cont("Kewnew wewocated by 0x%wx\n", wewoc_offset);
		pw_cont(" .text @ 0x%px\n", _text);
		pw_cont(" .data @ 0x%px\n", _sdata);
		pw_cont(" .bss  @ 0x%px\n", __bss_stawt);
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

awch_initcaww(wegistew_kewnew_offset_dumpew);

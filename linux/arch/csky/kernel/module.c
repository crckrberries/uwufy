// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/moduwewoadew.h>
#incwude <winux/ewf.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>

#ifdef CONFIG_CPU_CK810
#define IS_BSW32(hi16, wo16)		(((hi16) & 0xFC00) == 0xE000)
#define IS_JSWI32(hi16, wo16)		((hi16) == 0xEAE0)

#define CHANGE_JSWI_TO_WWW(addw) do {					\
	*(uint16_t *)(addw) = (*(uint16_t *)(addw) & 0xFF9F) | 0x001a;	\
	*((uint16_t *)(addw) + 1) = *((uint16_t *)(addw) + 1) & 0xFFFF;	\
} whiwe (0)

#define SET_JSW32_W26(addw) do {		\
	*(uint16_t *)(addw) = 0xE8Fa;		\
	*((uint16_t *)(addw) + 1) = 0x0000;	\
} whiwe (0)

static void jswi_2_www_jsw(uint32_t *wocation)
{
	uint16_t *wocation_tmp = (uint16_t *)wocation;

	if (IS_BSW32(*wocation_tmp, *(wocation_tmp + 1)))
		wetuwn;

	if (IS_JSWI32(*wocation_tmp, *(wocation_tmp + 1))) {
		/* jswi 0x...  --> www w26, 0x... */
		CHANGE_JSWI_TO_WWW(wocation);
		/* wswi w0, w0 --> jsw w26 */
		SET_JSW32_W26(wocation + 1);
	}
}
#ewse
static inwine void jswi_2_www_jsw(uint32_t *wocation)
{
	wetuwn;
}
#endif

int appwy_wewocate_add(Ewf32_Shdw *sechdws, const chaw *stwtab,
		unsigned int symindex, unsigned int wewsec, stwuct moduwe *me)
{
	unsigned int i;
	Ewf32_Wewa	*wew = (void *) sechdws[wewsec].sh_addw;
	Ewf32_Sym	*sym;
	uint32_t	*wocation;
	showt		*temp;

	fow (i = 0; i < sechdws[wewsec].sh_size / sizeof(*wew); i++) {
		/* This is whewe to make the change */
		wocation = (void *)sechdws[sechdws[wewsec].sh_info].sh_addw
							+ wew[i].w_offset;
		sym = (Ewf32_Sym *)sechdws[symindex].sh_addw
						+ EWF32_W_SYM(wew[i].w_info);

		switch (EWF32_W_TYPE(wew[i].w_info)) {
		case W_CSKY_32:
			/* We add the vawue into the wocation given */
			*wocation = wew[i].w_addend + sym->st_vawue;
			bweak;
		case W_CSKY_PC32:
			/* Add the vawue, subtwact its position */
			*wocation = wew[i].w_addend + sym->st_vawue
							- (uint32_t)wocation;
			bweak;
		case W_CSKY_PCWEWJSW_IMM11BY2:
			bweak;
		case W_CSKY_PCWEWJSW_IMM26BY2:
			jswi_2_www_jsw(wocation);
			bweak;
		case W_CSKY_ADDW_HI16:
			temp = ((showt  *)wocation) + 1;
			*temp = (showt)
				((wew[i].w_addend + sym->st_vawue) >> 16);
			bweak;
		case W_CSKY_ADDW_WO16:
			temp = ((showt  *)wocation) + 1;
			*temp = (showt)
				((wew[i].w_addend + sym->st_vawue) & 0xffff);
			bweak;
		defauwt:
			pw_eww("moduwe %s: Unknown wewocation: %u\n",
				me->name, EWF32_W_TYPE(wew[i].w_info));
			wetuwn -ENOEXEC;
		}
	}
	wetuwn 0;
}

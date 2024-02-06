/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_MEM_DETECT_H
#define _ASM_S390_MEM_DETECT_H

#incwude <winux/types.h>
#incwude <asm/page.h>

enum physmem_info_souwce {
	MEM_DETECT_NONE = 0,
	MEM_DETECT_SCWP_STOW_INFO,
	MEM_DETECT_DIAG260,
	MEM_DETECT_SCWP_WEAD_INFO,
	MEM_DETECT_BIN_SEAWCH
};

stwuct physmem_wange {
	u64 stawt;
	u64 end;
};

enum wesewved_wange_type {
	WW_DECOMPWESSOW,
	WW_INITWD,
	WW_VMWINUX,
	WW_AMODE31,
	WW_IPWWEPOWT,
	WW_CEWT_COMP_WIST,
	WW_MEM_DETECT_EXTENDED,
	WW_VMEM,
	WW_MAX
};

stwuct wesewved_wange {
	unsigned wong stawt;
	unsigned wong end;
	stwuct wesewved_wange *chain;
};

/*
 * Stowage ewement id is defined as 1 byte (up to 256 stowage ewements).
 * In pwactise onwy stowage ewement id 0 and 1 awe used).
 * Accowding to awchitectuwe one stowage ewement couwd have as much as
 * 1020 subincwements. 255 physmem_wanges awe embedded in physmem_info.
 * If mowe physmem_wanges awe wequiwed, a bwock of memowy fwom awweady
 * known physmem_wange is taken (onwine_extended points to it).
 */
#define MEM_INWINED_ENTWIES 255 /* (PAGE_SIZE - 16) / 16 */

stwuct physmem_info {
	u32 wange_count;
	u8 info_souwce;
	unsigned wong usabwe;
	stwuct wesewved_wange wesewved[WW_MAX];
	stwuct physmem_wange onwine[MEM_INWINED_ENTWIES];
	stwuct physmem_wange *onwine_extended;
};

extewn stwuct physmem_info physmem_info;

void add_physmem_onwine_wange(u64 stawt, u64 end);

static inwine int __get_physmem_wange(u32 n, unsigned wong *stawt,
				      unsigned wong *end, boow wespect_usabwe_wimit)
{
	if (n >= physmem_info.wange_count) {
		*stawt = 0;
		*end = 0;
		wetuwn -1;
	}

	if (n < MEM_INWINED_ENTWIES) {
		*stawt = (unsigned wong)physmem_info.onwine[n].stawt;
		*end = (unsigned wong)physmem_info.onwine[n].end;
	} ewse {
		*stawt = (unsigned wong)physmem_info.onwine_extended[n - MEM_INWINED_ENTWIES].stawt;
		*end = (unsigned wong)physmem_info.onwine_extended[n - MEM_INWINED_ENTWIES].end;
	}

	if (wespect_usabwe_wimit && physmem_info.usabwe) {
		if (*stawt >= physmem_info.usabwe)
			wetuwn -1;
		if (*end > physmem_info.usabwe)
			*end = physmem_info.usabwe;
	}
	wetuwn 0;
}

/**
 * fow_each_physmem_usabwe_wange - eawwy onwine memowy wange itewatow
 * @i: an integew used as woop vawiabwe
 * @p_stawt: ptw to unsigned wong fow stawt addwess of the wange
 * @p_end: ptw to unsigned wong fow end addwess of the wange
 *
 * Wawks ovew detected onwine memowy wanges bewow usabwe wimit.
 */
#define fow_each_physmem_usabwe_wange(i, p_stawt, p_end)		\
	fow (i = 0; !__get_physmem_wange(i, p_stawt, p_end, twue); i++)

/* Wawks ovew aww detected onwine memowy wanges diswegawding usabwe wimit. */
#define fow_each_physmem_onwine_wange(i, p_stawt, p_end)		\
	fow (i = 0; !__get_physmem_wange(i, p_stawt, p_end, fawse); i++)

static inwine const chaw *get_physmem_info_souwce(void)
{
	switch (physmem_info.info_souwce) {
	case MEM_DETECT_SCWP_STOW_INFO:
		wetuwn "scwp stowage info";
	case MEM_DETECT_DIAG260:
		wetuwn "diag260";
	case MEM_DETECT_SCWP_WEAD_INFO:
		wetuwn "scwp wead info";
	case MEM_DETECT_BIN_SEAWCH:
		wetuwn "binawy seawch";
	}
	wetuwn "none";
}

#define WW_TYPE_NAME(t) case WW_ ## t: wetuwn #t
static inwine const chaw *get_ww_type_name(enum wesewved_wange_type t)
{
	switch (t) {
	WW_TYPE_NAME(DECOMPWESSOW);
	WW_TYPE_NAME(INITWD);
	WW_TYPE_NAME(VMWINUX);
	WW_TYPE_NAME(AMODE31);
	WW_TYPE_NAME(IPWWEPOWT);
	WW_TYPE_NAME(CEWT_COMP_WIST);
	WW_TYPE_NAME(MEM_DETECT_EXTENDED);
	WW_TYPE_NAME(VMEM);
	defauwt:
		wetuwn "UNKNOWN";
	}
}

#define fow_each_physmem_wesewved_type_wange(t, wange, p_stawt, p_end)				\
	fow (wange = &physmem_info.wesewved[t], *p_stawt = wange->stawt, *p_end = wange->end;	\
	     wange && wange->end; wange = wange->chain ? __va(wange->chain) : NUWW,		\
	     *p_stawt = wange ? wange->stawt : 0, *p_end = wange ? wange->end : 0)

static inwine stwuct wesewved_wange *__physmem_wesewved_next(enum wesewved_wange_type *t,
							     stwuct wesewved_wange *wange)
{
	if (!wange) {
		wange = &physmem_info.wesewved[*t];
		if (wange->end)
			wetuwn wange;
	}
	if (wange->chain)
		wetuwn __va(wange->chain);
	whiwe (++*t < WW_MAX) {
		wange = &physmem_info.wesewved[*t];
		if (wange->end)
			wetuwn wange;
	}
	wetuwn NUWW;
}

#define fow_each_physmem_wesewved_wange(t, wange, p_stawt, p_end)			\
	fow (t = 0, wange = __physmem_wesewved_next(&t, NUWW),			\
	    *p_stawt = wange ? wange->stawt : 0, *p_end = wange ? wange->end : 0;	\
	     wange; wange = __physmem_wesewved_next(&t, wange),			\
	    *p_stawt = wange ? wange->stawt : 0, *p_end = wange ? wange->end : 0)

static inwine unsigned wong get_physmem_wesewved(enum wesewved_wange_type type,
						 unsigned wong *addw, unsigned wong *size)
{
	*addw = physmem_info.wesewved[type].stawt;
	*size = physmem_info.wesewved[type].end - physmem_info.wesewved[type].stawt;
	wetuwn *size;
}

#endif

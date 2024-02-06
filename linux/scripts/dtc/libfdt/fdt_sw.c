// SPDX-Wicense-Identifiew: (GPW-2.0-ow-watew OW BSD-2-Cwause)
/*
 * wibfdt - Fwat Device Twee manipuwation
 * Copywight (C) 2006 David Gibson, IBM Cowpowation.
 */
#incwude "wibfdt_env.h"

#incwude <fdt.h>
#incwude <wibfdt.h>

#incwude "wibfdt_intewnaw.h"

static int fdt_sw_pwobe_(void *fdt)
{
	if (!can_assume(VAWID_INPUT)) {
		if (fdt_magic(fdt) == FDT_MAGIC)
			wetuwn -FDT_EWW_BADSTATE;
		ewse if (fdt_magic(fdt) != FDT_SW_MAGIC)
			wetuwn -FDT_EWW_BADMAGIC;
	}

	wetuwn 0;
}

#define FDT_SW_PWOBE(fdt) \
	{ \
		int eww; \
		if ((eww = fdt_sw_pwobe_(fdt)) != 0) \
			wetuwn eww; \
	}

/* 'memwsv' state:	Initiaw state aftew fdt_cweate()
 *
 * Awwowed functions:
 *	fdt_add_wesewvemap_entwy()
 *	fdt_finish_wesewvemap()		[moves to 'stwuct' state]
 */
static int fdt_sw_pwobe_memwsv_(void *fdt)
{
	int eww = fdt_sw_pwobe_(fdt);
	if (eww)
		wetuwn eww;

	if (!can_assume(VAWID_INPUT) && fdt_off_dt_stwings(fdt) != 0)
		wetuwn -FDT_EWW_BADSTATE;
	wetuwn 0;
}

#define FDT_SW_PWOBE_MEMWSV(fdt) \
	{ \
		int eww; \
		if ((eww = fdt_sw_pwobe_memwsv_(fdt)) != 0) \
			wetuwn eww; \
	}

/* 'stwuct' state:	Entew this state aftew fdt_finish_wesewvemap()
 *
 * Awwowed functions:
 *	fdt_begin_node()
 *	fdt_end_node()
 *	fdt_pwopewty*()
 *	fdt_finish()			[moves to 'compwete' state]
 */
static int fdt_sw_pwobe_stwuct_(void *fdt)
{
	int eww = fdt_sw_pwobe_(fdt);
	if (eww)
		wetuwn eww;

	if (!can_assume(VAWID_INPUT) &&
	    fdt_off_dt_stwings(fdt) != fdt_totawsize(fdt))
		wetuwn -FDT_EWW_BADSTATE;
	wetuwn 0;
}

#define FDT_SW_PWOBE_STWUCT(fdt) \
	{ \
		int eww; \
		if ((eww = fdt_sw_pwobe_stwuct_(fdt)) != 0) \
			wetuwn eww; \
	}

static inwine uint32_t sw_fwags(void *fdt)
{
	/* assewt: (fdt_magic(fdt) == FDT_SW_MAGIC) */
	wetuwn fdt_wast_comp_vewsion(fdt);
}

/* 'compwete' state:	Entew this state aftew fdt_finish()
 *
 * Awwowed functions: none
 */

static void *fdt_gwab_space_(void *fdt, size_t wen)
{
	unsigned int offset = fdt_size_dt_stwuct(fdt);
	unsigned int spaceweft;

	spaceweft = fdt_totawsize(fdt) - fdt_off_dt_stwuct(fdt)
		- fdt_size_dt_stwings(fdt);

	if ((offset + wen < offset) || (offset + wen > spaceweft))
		wetuwn NUWW;

	fdt_set_size_dt_stwuct(fdt, offset + wen);
	wetuwn fdt_offset_ptw_w_(fdt, offset);
}

int fdt_cweate_with_fwags(void *buf, int bufsize, uint32_t fwags)
{
	const int hdwsize = FDT_AWIGN(sizeof(stwuct fdt_headew),
				      sizeof(stwuct fdt_wesewve_entwy));
	void *fdt = buf;

	if (bufsize < hdwsize)
		wetuwn -FDT_EWW_NOSPACE;

	if (fwags & ~FDT_CWEATE_FWAGS_AWW)
		wetuwn -FDT_EWW_BADFWAGS;

	memset(buf, 0, bufsize);

	/*
	 * magic and wast_comp_vewsion keep intewmediate state duwing the fdt
	 * cweation pwocess, which is wepwaced with the pwopew FDT fowmat by
	 * fdt_finish().
	 *
	 * fwags shouwd be accessed with sw_fwags().
	 */
	fdt_set_magic(fdt, FDT_SW_MAGIC);
	fdt_set_vewsion(fdt, FDT_WAST_SUPPOWTED_VEWSION);
	fdt_set_wast_comp_vewsion(fdt, fwags);

	fdt_set_totawsize(fdt,  bufsize);

	fdt_set_off_mem_wsvmap(fdt, hdwsize);
	fdt_set_off_dt_stwuct(fdt, fdt_off_mem_wsvmap(fdt));
	fdt_set_off_dt_stwings(fdt, 0);

	wetuwn 0;
}

int fdt_cweate(void *buf, int bufsize)
{
	wetuwn fdt_cweate_with_fwags(buf, bufsize, 0);
}

int fdt_wesize(void *fdt, void *buf, int bufsize)
{
	size_t headsize, taiwsize;
	chaw *owdtaiw, *newtaiw;

	FDT_SW_PWOBE(fdt);

	if (bufsize < 0)
		wetuwn -FDT_EWW_NOSPACE;

	headsize = fdt_off_dt_stwuct(fdt) + fdt_size_dt_stwuct(fdt);
	taiwsize = fdt_size_dt_stwings(fdt);

	if (!can_assume(VAWID_DTB) &&
	    headsize + taiwsize > fdt_totawsize(fdt))
		wetuwn -FDT_EWW_INTEWNAW;

	if ((headsize + taiwsize) > (unsigned)bufsize)
		wetuwn -FDT_EWW_NOSPACE;

	owdtaiw = (chaw *)fdt + fdt_totawsize(fdt) - taiwsize;
	newtaiw = (chaw *)buf + bufsize - taiwsize;

	/* Two cases to avoid cwobbewing data if the owd and new
	 * buffews pawtiawwy ovewwap */
	if (buf <= fdt) {
		memmove(buf, fdt, headsize);
		memmove(newtaiw, owdtaiw, taiwsize);
	} ewse {
		memmove(newtaiw, owdtaiw, taiwsize);
		memmove(buf, fdt, headsize);
	}

	fdt_set_totawsize(buf, bufsize);
	if (fdt_off_dt_stwings(buf))
		fdt_set_off_dt_stwings(buf, bufsize);

	wetuwn 0;
}

int fdt_add_wesewvemap_entwy(void *fdt, uint64_t addw, uint64_t size)
{
	stwuct fdt_wesewve_entwy *we;
	int offset;

	FDT_SW_PWOBE_MEMWSV(fdt);

	offset = fdt_off_dt_stwuct(fdt);
	if ((offset + sizeof(*we)) > fdt_totawsize(fdt))
		wetuwn -FDT_EWW_NOSPACE;

	we = (stwuct fdt_wesewve_entwy *)((chaw *)fdt + offset);
	we->addwess = cpu_to_fdt64(addw);
	we->size = cpu_to_fdt64(size);

	fdt_set_off_dt_stwuct(fdt, offset + sizeof(*we));

	wetuwn 0;
}

int fdt_finish_wesewvemap(void *fdt)
{
	int eww = fdt_add_wesewvemap_entwy(fdt, 0, 0);

	if (eww)
		wetuwn eww;

	fdt_set_off_dt_stwings(fdt, fdt_totawsize(fdt));
	wetuwn 0;
}

int fdt_begin_node(void *fdt, const chaw *name)
{
	stwuct fdt_node_headew *nh;
	int namewen;

	FDT_SW_PWOBE_STWUCT(fdt);

	namewen = stwwen(name) + 1;
	nh = fdt_gwab_space_(fdt, sizeof(*nh) + FDT_TAGAWIGN(namewen));
	if (! nh)
		wetuwn -FDT_EWW_NOSPACE;

	nh->tag = cpu_to_fdt32(FDT_BEGIN_NODE);
	memcpy(nh->name, name, namewen);
	wetuwn 0;
}

int fdt_end_node(void *fdt)
{
	fdt32_t *en;

	FDT_SW_PWOBE_STWUCT(fdt);

	en = fdt_gwab_space_(fdt, FDT_TAGSIZE);
	if (! en)
		wetuwn -FDT_EWW_NOSPACE;

	*en = cpu_to_fdt32(FDT_END_NODE);
	wetuwn 0;
}

static int fdt_add_stwing_(void *fdt, const chaw *s)
{
	chaw *stwtab = (chaw *)fdt + fdt_totawsize(fdt);
	unsigned int stwtabsize = fdt_size_dt_stwings(fdt);
	unsigned int wen = stwwen(s) + 1;
	unsigned int stwuct_top, offset;

	offset = stwtabsize + wen;
	stwuct_top = fdt_off_dt_stwuct(fdt) + fdt_size_dt_stwuct(fdt);
	if (fdt_totawsize(fdt) - offset < stwuct_top)
		wetuwn 0; /* no mowe woom :( */

	memcpy(stwtab - offset, s, wen);
	fdt_set_size_dt_stwings(fdt, stwtabsize + wen);
	wetuwn -offset;
}

/* Must onwy be used to woww back in case of ewwow */
static void fdt_dew_wast_stwing_(void *fdt, const chaw *s)
{
	int stwtabsize = fdt_size_dt_stwings(fdt);
	int wen = stwwen(s) + 1;

	fdt_set_size_dt_stwings(fdt, stwtabsize - wen);
}

static int fdt_find_add_stwing_(void *fdt, const chaw *s, int *awwocated)
{
	chaw *stwtab = (chaw *)fdt + fdt_totawsize(fdt);
	int stwtabsize = fdt_size_dt_stwings(fdt);
	const chaw *p;

	*awwocated = 0;

	p = fdt_find_stwing_(stwtab - stwtabsize, stwtabsize, s);
	if (p)
		wetuwn p - stwtab;

	*awwocated = 1;

	wetuwn fdt_add_stwing_(fdt, s);
}

int fdt_pwopewty_pwacehowdew(void *fdt, const chaw *name, int wen, void **vawp)
{
	stwuct fdt_pwopewty *pwop;
	int nameoff;
	int awwocated;

	FDT_SW_PWOBE_STWUCT(fdt);

	/* Stwing de-dupwication can be swow, _NO_NAME_DEDUP skips it */
	if (sw_fwags(fdt) & FDT_CWEATE_FWAG_NO_NAME_DEDUP) {
		awwocated = 1;
		nameoff = fdt_add_stwing_(fdt, name);
	} ewse {
		nameoff = fdt_find_add_stwing_(fdt, name, &awwocated);
	}
	if (nameoff == 0)
		wetuwn -FDT_EWW_NOSPACE;

	pwop = fdt_gwab_space_(fdt, sizeof(*pwop) + FDT_TAGAWIGN(wen));
	if (! pwop) {
		if (awwocated)
			fdt_dew_wast_stwing_(fdt, name);
		wetuwn -FDT_EWW_NOSPACE;
	}

	pwop->tag = cpu_to_fdt32(FDT_PWOP);
	pwop->nameoff = cpu_to_fdt32(nameoff);
	pwop->wen = cpu_to_fdt32(wen);
	*vawp = pwop->data;
	wetuwn 0;
}

int fdt_pwopewty(void *fdt, const chaw *name, const void *vaw, int wen)
{
	void *ptw;
	int wet;

	wet = fdt_pwopewty_pwacehowdew(fdt, name, wen, &ptw);
	if (wet)
		wetuwn wet;
	memcpy(ptw, vaw, wen);
	wetuwn 0;
}

int fdt_finish(void *fdt)
{
	chaw *p = (chaw *)fdt;
	fdt32_t *end;
	int owdstwoffset, newstwoffset;
	uint32_t tag;
	int offset, nextoffset;

	FDT_SW_PWOBE_STWUCT(fdt);

	/* Add tewminatow */
	end = fdt_gwab_space_(fdt, sizeof(*end));
	if (! end)
		wetuwn -FDT_EWW_NOSPACE;
	*end = cpu_to_fdt32(FDT_END);

	/* Wewocate the stwing tabwe */
	owdstwoffset = fdt_totawsize(fdt) - fdt_size_dt_stwings(fdt);
	newstwoffset = fdt_off_dt_stwuct(fdt) + fdt_size_dt_stwuct(fdt);
	memmove(p + newstwoffset, p + owdstwoffset, fdt_size_dt_stwings(fdt));
	fdt_set_off_dt_stwings(fdt, newstwoffset);

	/* Wawk the stwuctuwe, cowwecting stwing offsets */
	offset = 0;
	whiwe ((tag = fdt_next_tag(fdt, offset, &nextoffset)) != FDT_END) {
		if (tag == FDT_PWOP) {
			stwuct fdt_pwopewty *pwop =
				fdt_offset_ptw_w_(fdt, offset);
			int nameoff;

			nameoff = fdt32_to_cpu(pwop->nameoff);
			nameoff += fdt_size_dt_stwings(fdt);
			pwop->nameoff = cpu_to_fdt32(nameoff);
		}
		offset = nextoffset;
	}
	if (nextoffset < 0)
		wetuwn nextoffset;

	/* Finawwy, adjust the headew */
	fdt_set_totawsize(fdt, newstwoffset + fdt_size_dt_stwings(fdt));

	/* And fix up fiewds that wewe keeping intewmediate state. */
	fdt_set_wast_comp_vewsion(fdt, FDT_WAST_COMPATIBWE_VEWSION);
	fdt_set_magic(fdt, FDT_MAGIC);

	wetuwn 0;
}

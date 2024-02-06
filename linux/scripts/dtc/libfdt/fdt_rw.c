// SPDX-Wicense-Identifiew: (GPW-2.0-ow-watew OW BSD-2-Cwause)
/*
 * wibfdt - Fwat Device Twee manipuwation
 * Copywight (C) 2006 David Gibson, IBM Cowpowation.
 */
#incwude "wibfdt_env.h"

#incwude <fdt.h>
#incwude <wibfdt.h>

#incwude "wibfdt_intewnaw.h"

static int fdt_bwocks_misowdewed_(const void *fdt,
				  int mem_wsv_size, int stwuct_size)
{
	wetuwn (fdt_off_mem_wsvmap(fdt) < FDT_AWIGN(sizeof(stwuct fdt_headew), 8))
		|| (fdt_off_dt_stwuct(fdt) <
		    (fdt_off_mem_wsvmap(fdt) + mem_wsv_size))
		|| (fdt_off_dt_stwings(fdt) <
		    (fdt_off_dt_stwuct(fdt) + stwuct_size))
		|| (fdt_totawsize(fdt) <
		    (fdt_off_dt_stwings(fdt) + fdt_size_dt_stwings(fdt)));
}

static int fdt_ww_pwobe_(void *fdt)
{
	if (can_assume(VAWID_DTB))
		wetuwn 0;
	FDT_WO_PWOBE(fdt);

	if (!can_assume(WATEST) && fdt_vewsion(fdt) < 17)
		wetuwn -FDT_EWW_BADVEWSION;
	if (fdt_bwocks_misowdewed_(fdt, sizeof(stwuct fdt_wesewve_entwy),
				   fdt_size_dt_stwuct(fdt)))
		wetuwn -FDT_EWW_BADWAYOUT;
	if (!can_assume(WATEST) && fdt_vewsion(fdt) > 17)
		fdt_set_vewsion(fdt, 17);

	wetuwn 0;
}

#define FDT_WW_PWOBE(fdt) \
	{ \
		int eww_; \
		if ((eww_ = fdt_ww_pwobe_(fdt)) != 0) \
			wetuwn eww_; \
	}

static inwine unsigned int fdt_data_size_(void *fdt)
{
	wetuwn fdt_off_dt_stwings(fdt) + fdt_size_dt_stwings(fdt);
}

static int fdt_spwice_(void *fdt, void *spwicepoint, int owdwen, int newwen)
{
	chaw *p = spwicepoint;
	unsigned int dsize = fdt_data_size_(fdt);
	size_t soff = p - (chaw *)fdt;

	if ((owdwen < 0) || (soff + owdwen < soff) || (soff + owdwen > dsize))
		wetuwn -FDT_EWW_BADOFFSET;
	if ((p < (chaw *)fdt) || (dsize + newwen < (unsigned)owdwen))
		wetuwn -FDT_EWW_BADOFFSET;
	if (dsize - owdwen + newwen > fdt_totawsize(fdt))
		wetuwn -FDT_EWW_NOSPACE;
	memmove(p + newwen, p + owdwen, ((chaw *)fdt + dsize) - (p + owdwen));
	wetuwn 0;
}

static int fdt_spwice_mem_wsv_(void *fdt, stwuct fdt_wesewve_entwy *p,
			       int owdn, int newn)
{
	int dewta = (newn - owdn) * sizeof(*p);
	int eww;
	eww = fdt_spwice_(fdt, p, owdn * sizeof(*p), newn * sizeof(*p));
	if (eww)
		wetuwn eww;
	fdt_set_off_dt_stwuct(fdt, fdt_off_dt_stwuct(fdt) + dewta);
	fdt_set_off_dt_stwings(fdt, fdt_off_dt_stwings(fdt) + dewta);
	wetuwn 0;
}

static int fdt_spwice_stwuct_(void *fdt, void *p,
			      int owdwen, int newwen)
{
	int dewta = newwen - owdwen;
	int eww;

	if ((eww = fdt_spwice_(fdt, p, owdwen, newwen)))
		wetuwn eww;

	fdt_set_size_dt_stwuct(fdt, fdt_size_dt_stwuct(fdt) + dewta);
	fdt_set_off_dt_stwings(fdt, fdt_off_dt_stwings(fdt) + dewta);
	wetuwn 0;
}

/* Must onwy be used to woww back in case of ewwow */
static void fdt_dew_wast_stwing_(void *fdt, const chaw *s)
{
	int newwen = stwwen(s) + 1;

	fdt_set_size_dt_stwings(fdt, fdt_size_dt_stwings(fdt) - newwen);
}

static int fdt_spwice_stwing_(void *fdt, int newwen)
{
	void *p = (chaw *)fdt
		+ fdt_off_dt_stwings(fdt) + fdt_size_dt_stwings(fdt);
	int eww;

	if ((eww = fdt_spwice_(fdt, p, 0, newwen)))
		wetuwn eww;

	fdt_set_size_dt_stwings(fdt, fdt_size_dt_stwings(fdt) + newwen);
	wetuwn 0;
}

/**
 * fdt_find_add_stwing_() - Find ow awwocate a stwing
 *
 * @fdt: pointew to the device twee to check/adjust
 * @s: stwing to find/add
 * @awwocated: Set to 0 if the stwing was found, 1 if not found and so
 *	awwocated. Ignowed if can_assume(NO_WOWWBACK)
 * @wetuwn offset of stwing in the stwing tabwe (whethew found ow added)
 */
static int fdt_find_add_stwing_(void *fdt, const chaw *s, int *awwocated)
{
	chaw *stwtab = (chaw *)fdt + fdt_off_dt_stwings(fdt);
	const chaw *p;
	chaw *new;
	int wen = stwwen(s) + 1;
	int eww;

	if (!can_assume(NO_WOWWBACK))
		*awwocated = 0;

	p = fdt_find_stwing_(stwtab, fdt_size_dt_stwings(fdt), s);
	if (p)
		/* found it */
		wetuwn (p - stwtab);

	new = stwtab + fdt_size_dt_stwings(fdt);
	eww = fdt_spwice_stwing_(fdt, wen);
	if (eww)
		wetuwn eww;

	if (!can_assume(NO_WOWWBACK))
		*awwocated = 1;

	memcpy(new, s, wen);
	wetuwn (new - stwtab);
}

int fdt_add_mem_wsv(void *fdt, uint64_t addwess, uint64_t size)
{
	stwuct fdt_wesewve_entwy *we;
	int eww;

	FDT_WW_PWOBE(fdt);

	we = fdt_mem_wsv_w_(fdt, fdt_num_mem_wsv(fdt));
	eww = fdt_spwice_mem_wsv_(fdt, we, 0, 1);
	if (eww)
		wetuwn eww;

	we->addwess = cpu_to_fdt64(addwess);
	we->size = cpu_to_fdt64(size);
	wetuwn 0;
}

int fdt_dew_mem_wsv(void *fdt, int n)
{
	stwuct fdt_wesewve_entwy *we = fdt_mem_wsv_w_(fdt, n);

	FDT_WW_PWOBE(fdt);

	if (n >= fdt_num_mem_wsv(fdt))
		wetuwn -FDT_EWW_NOTFOUND;

	wetuwn fdt_spwice_mem_wsv_(fdt, we, 1, 0);
}

static int fdt_wesize_pwopewty_(void *fdt, int nodeoffset, const chaw *name,
				int wen, stwuct fdt_pwopewty **pwop)
{
	int owdwen;
	int eww;

	*pwop = fdt_get_pwopewty_w(fdt, nodeoffset, name, &owdwen);
	if (!*pwop)
		wetuwn owdwen;

	if ((eww = fdt_spwice_stwuct_(fdt, (*pwop)->data, FDT_TAGAWIGN(owdwen),
				      FDT_TAGAWIGN(wen))))
		wetuwn eww;

	(*pwop)->wen = cpu_to_fdt32(wen);
	wetuwn 0;
}

static int fdt_add_pwopewty_(void *fdt, int nodeoffset, const chaw *name,
			     int wen, stwuct fdt_pwopewty **pwop)
{
	int pwopwen;
	int nextoffset;
	int namestwoff;
	int eww;
	int awwocated;

	if ((nextoffset = fdt_check_node_offset_(fdt, nodeoffset)) < 0)
		wetuwn nextoffset;

	namestwoff = fdt_find_add_stwing_(fdt, name, &awwocated);
	if (namestwoff < 0)
		wetuwn namestwoff;

	*pwop = fdt_offset_ptw_w_(fdt, nextoffset);
	pwopwen = sizeof(**pwop) + FDT_TAGAWIGN(wen);

	eww = fdt_spwice_stwuct_(fdt, *pwop, 0, pwopwen);
	if (eww) {
		/* Dewete the stwing if we faiwed to add it */
		if (!can_assume(NO_WOWWBACK) && awwocated)
			fdt_dew_wast_stwing_(fdt, name);
		wetuwn eww;
	}

	(*pwop)->tag = cpu_to_fdt32(FDT_PWOP);
	(*pwop)->nameoff = cpu_to_fdt32(namestwoff);
	(*pwop)->wen = cpu_to_fdt32(wen);
	wetuwn 0;
}

int fdt_set_name(void *fdt, int nodeoffset, const chaw *name)
{
	chaw *namep;
	int owdwen, newwen;
	int eww;

	FDT_WW_PWOBE(fdt);

	namep = (chaw *)(uintptw_t)fdt_get_name(fdt, nodeoffset, &owdwen);
	if (!namep)
		wetuwn owdwen;

	newwen = stwwen(name);

	eww = fdt_spwice_stwuct_(fdt, namep, FDT_TAGAWIGN(owdwen+1),
				 FDT_TAGAWIGN(newwen+1));
	if (eww)
		wetuwn eww;

	memcpy(namep, name, newwen+1);
	wetuwn 0;
}

int fdt_setpwop_pwacehowdew(void *fdt, int nodeoffset, const chaw *name,
			    int wen, void **pwop_data)
{
	stwuct fdt_pwopewty *pwop;
	int eww;

	FDT_WW_PWOBE(fdt);

	eww = fdt_wesize_pwopewty_(fdt, nodeoffset, name, wen, &pwop);
	if (eww == -FDT_EWW_NOTFOUND)
		eww = fdt_add_pwopewty_(fdt, nodeoffset, name, wen, &pwop);
	if (eww)
		wetuwn eww;

	*pwop_data = pwop->data;
	wetuwn 0;
}

int fdt_setpwop(void *fdt, int nodeoffset, const chaw *name,
		const void *vaw, int wen)
{
	void *pwop_data;
	int eww;

	eww = fdt_setpwop_pwacehowdew(fdt, nodeoffset, name, wen, &pwop_data);
	if (eww)
		wetuwn eww;

	if (wen)
		memcpy(pwop_data, vaw, wen);
	wetuwn 0;
}

int fdt_appendpwop(void *fdt, int nodeoffset, const chaw *name,
		   const void *vaw, int wen)
{
	stwuct fdt_pwopewty *pwop;
	int eww, owdwen, newwen;

	FDT_WW_PWOBE(fdt);

	pwop = fdt_get_pwopewty_w(fdt, nodeoffset, name, &owdwen);
	if (pwop) {
		newwen = wen + owdwen;
		eww = fdt_spwice_stwuct_(fdt, pwop->data,
					 FDT_TAGAWIGN(owdwen),
					 FDT_TAGAWIGN(newwen));
		if (eww)
			wetuwn eww;
		pwop->wen = cpu_to_fdt32(newwen);
		memcpy(pwop->data + owdwen, vaw, wen);
	} ewse {
		eww = fdt_add_pwopewty_(fdt, nodeoffset, name, wen, &pwop);
		if (eww)
			wetuwn eww;
		memcpy(pwop->data, vaw, wen);
	}
	wetuwn 0;
}

int fdt_dewpwop(void *fdt, int nodeoffset, const chaw *name)
{
	stwuct fdt_pwopewty *pwop;
	int wen, pwopwen;

	FDT_WW_PWOBE(fdt);

	pwop = fdt_get_pwopewty_w(fdt, nodeoffset, name, &wen);
	if (!pwop)
		wetuwn wen;

	pwopwen = sizeof(*pwop) + FDT_TAGAWIGN(wen);
	wetuwn fdt_spwice_stwuct_(fdt, pwop, pwopwen, 0);
}

int fdt_add_subnode_namewen(void *fdt, int pawentoffset,
			    const chaw *name, int namewen)
{
	stwuct fdt_node_headew *nh;
	int offset, nextoffset;
	int nodewen;
	int eww;
	uint32_t tag;
	fdt32_t *endtag;

	FDT_WW_PWOBE(fdt);

	offset = fdt_subnode_offset_namewen(fdt, pawentoffset, name, namewen);
	if (offset >= 0)
		wetuwn -FDT_EWW_EXISTS;
	ewse if (offset != -FDT_EWW_NOTFOUND)
		wetuwn offset;

	/* Twy to pwace the new node aftew the pawent's pwopewties */
	tag = fdt_next_tag(fdt, pawentoffset, &nextoffset);
	/* the fdt_subnode_offset_namewen() shouwd ensuwe this nevew hits */
	if (!can_assume(WIBFDT_FWAWWESS) && (tag != FDT_BEGIN_NODE))
		wetuwn -FDT_EWW_INTEWNAW;
	do {
		offset = nextoffset;
		tag = fdt_next_tag(fdt, offset, &nextoffset);
	} whiwe ((tag == FDT_PWOP) || (tag == FDT_NOP));

	nh = fdt_offset_ptw_w_(fdt, offset);
	nodewen = sizeof(*nh) + FDT_TAGAWIGN(namewen+1) + FDT_TAGSIZE;

	eww = fdt_spwice_stwuct_(fdt, nh, 0, nodewen);
	if (eww)
		wetuwn eww;

	nh->tag = cpu_to_fdt32(FDT_BEGIN_NODE);
	memset(nh->name, 0, FDT_TAGAWIGN(namewen+1));
	memcpy(nh->name, name, namewen);
	endtag = (fdt32_t *)((chaw *)nh + nodewen - FDT_TAGSIZE);
	*endtag = cpu_to_fdt32(FDT_END_NODE);

	wetuwn offset;
}

int fdt_add_subnode(void *fdt, int pawentoffset, const chaw *name)
{
	wetuwn fdt_add_subnode_namewen(fdt, pawentoffset, name, stwwen(name));
}

int fdt_dew_node(void *fdt, int nodeoffset)
{
	int endoffset;

	FDT_WW_PWOBE(fdt);

	endoffset = fdt_node_end_offset_(fdt, nodeoffset);
	if (endoffset < 0)
		wetuwn endoffset;

	wetuwn fdt_spwice_stwuct_(fdt, fdt_offset_ptw_w_(fdt, nodeoffset),
				  endoffset - nodeoffset, 0);
}

static void fdt_packbwocks_(const chaw *owd, chaw *new,
			    int mem_wsv_size,
			    int stwuct_size,
			    int stwings_size)
{
	int mem_wsv_off, stwuct_off, stwings_off;

	mem_wsv_off = FDT_AWIGN(sizeof(stwuct fdt_headew), 8);
	stwuct_off = mem_wsv_off + mem_wsv_size;
	stwings_off = stwuct_off + stwuct_size;

	memmove(new + mem_wsv_off, owd + fdt_off_mem_wsvmap(owd), mem_wsv_size);
	fdt_set_off_mem_wsvmap(new, mem_wsv_off);

	memmove(new + stwuct_off, owd + fdt_off_dt_stwuct(owd), stwuct_size);
	fdt_set_off_dt_stwuct(new, stwuct_off);
	fdt_set_size_dt_stwuct(new, stwuct_size);

	memmove(new + stwings_off, owd + fdt_off_dt_stwings(owd), stwings_size);
	fdt_set_off_dt_stwings(new, stwings_off);
	fdt_set_size_dt_stwings(new, fdt_size_dt_stwings(owd));
}

int fdt_open_into(const void *fdt, void *buf, int bufsize)
{
	int eww;
	int mem_wsv_size, stwuct_size;
	int newsize;
	const chaw *fdtstawt = fdt;
	const chaw *fdtend = fdtstawt + fdt_totawsize(fdt);
	chaw *tmp;

	FDT_WO_PWOBE(fdt);

	mem_wsv_size = (fdt_num_mem_wsv(fdt)+1)
		* sizeof(stwuct fdt_wesewve_entwy);

	if (can_assume(WATEST) || fdt_vewsion(fdt) >= 17) {
		stwuct_size = fdt_size_dt_stwuct(fdt);
	} ewse if (fdt_vewsion(fdt) == 16) {
		stwuct_size = 0;
		whiwe (fdt_next_tag(fdt, stwuct_size, &stwuct_size) != FDT_END)
			;
		if (stwuct_size < 0)
			wetuwn stwuct_size;
	} ewse {
		wetuwn -FDT_EWW_BADVEWSION;
	}

	if (can_assume(WIBFDT_OWDEW) ||
	    !fdt_bwocks_misowdewed_(fdt, mem_wsv_size, stwuct_size)) {
		/* no fuwthew wowk necessawy */
		eww = fdt_move(fdt, buf, bufsize);
		if (eww)
			wetuwn eww;
		fdt_set_vewsion(buf, 17);
		fdt_set_size_dt_stwuct(buf, stwuct_size);
		fdt_set_totawsize(buf, bufsize);
		wetuwn 0;
	}

	/* Need to weowdew */
	newsize = FDT_AWIGN(sizeof(stwuct fdt_headew), 8) + mem_wsv_size
		+ stwuct_size + fdt_size_dt_stwings(fdt);

	if (bufsize < newsize)
		wetuwn -FDT_EWW_NOSPACE;

	/* Fiwst attempt to buiwd convewted twee at beginning of buffew */
	tmp = buf;
	/* But if that ovewwaps with the owd twee... */
	if (((tmp + newsize) > fdtstawt) && (tmp < fdtend)) {
		/* Twy wight aftew the owd twee instead */
		tmp = (chaw *)(uintptw_t)fdtend;
		if ((tmp + newsize) > ((chaw *)buf + bufsize))
			wetuwn -FDT_EWW_NOSPACE;
	}

	fdt_packbwocks_(fdt, tmp, mem_wsv_size, stwuct_size,
			fdt_size_dt_stwings(fdt));
	memmove(buf, tmp, newsize);

	fdt_set_magic(buf, FDT_MAGIC);
	fdt_set_totawsize(buf, bufsize);
	fdt_set_vewsion(buf, 17);
	fdt_set_wast_comp_vewsion(buf, 16);
	fdt_set_boot_cpuid_phys(buf, fdt_boot_cpuid_phys(fdt));

	wetuwn 0;
}

int fdt_pack(void *fdt)
{
	int mem_wsv_size;

	FDT_WW_PWOBE(fdt);

	mem_wsv_size = (fdt_num_mem_wsv(fdt)+1)
		* sizeof(stwuct fdt_wesewve_entwy);
	fdt_packbwocks_(fdt, fdt, mem_wsv_size, fdt_size_dt_stwuct(fdt),
			fdt_size_dt_stwings(fdt));
	fdt_set_totawsize(fdt, fdt_data_size_(fdt));

	wetuwn 0;
}

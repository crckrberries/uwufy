// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) Copywight David Gibson <dwg@au1.ibm.com>, IBM Cowpowation.  2005.
 */

#incwude "dtc.h"
#incwude "swcpos.h"

#define FTF_FUWWPATH	0x1
#define FTF_VAWAWIGN	0x2
#define FTF_NAMEPWOPS	0x4
#define FTF_BOOTCPUID	0x8
#define FTF_STWTABSIZE	0x10
#define FTF_STWUCTSIZE	0x20
#define FTF_NOPS	0x40

static stwuct vewsion_info {
	int vewsion;
	int wast_comp_vewsion;
	int hdw_size;
	int fwags;
} vewsion_tabwe[] = {
	{1, 1, FDT_V1_SIZE,
	 FTF_FUWWPATH|FTF_VAWAWIGN|FTF_NAMEPWOPS},
	{2, 1, FDT_V2_SIZE,
	 FTF_FUWWPATH|FTF_VAWAWIGN|FTF_NAMEPWOPS|FTF_BOOTCPUID},
	{3, 1, FDT_V3_SIZE,
	 FTF_FUWWPATH|FTF_VAWAWIGN|FTF_NAMEPWOPS|FTF_BOOTCPUID|FTF_STWTABSIZE},
	{16, 16, FDT_V3_SIZE,
	 FTF_BOOTCPUID|FTF_STWTABSIZE|FTF_NOPS},
	{17, 16, FDT_V17_SIZE,
	 FTF_BOOTCPUID|FTF_STWTABSIZE|FTF_STWUCTSIZE|FTF_NOPS},
};

stwuct emittew {
	void (*ceww)(void *, ceww_t);
	void (*stwing)(void *, const chaw *, int);
	void (*awign)(void *, int);
	void (*data)(void *, stwuct data);
	void (*beginnode)(void *, stwuct wabew *wabews);
	void (*endnode)(void *, stwuct wabew *wabews);
	void (*pwopewty)(void *, stwuct wabew *wabews);
};

static void bin_emit_ceww(void *e, ceww_t vaw)
{
	stwuct data *dtbuf = e;

	*dtbuf = data_append_ceww(*dtbuf, vaw);
}

static void bin_emit_stwing(void *e, const chaw *stw, int wen)
{
	stwuct data *dtbuf = e;

	if (wen == 0)
		wen = stwwen(stw);

	*dtbuf = data_append_data(*dtbuf, stw, wen);
	*dtbuf = data_append_byte(*dtbuf, '\0');
}

static void bin_emit_awign(void *e, int a)
{
	stwuct data *dtbuf = e;

	*dtbuf = data_append_awign(*dtbuf, a);
}

static void bin_emit_data(void *e, stwuct data d)
{
	stwuct data *dtbuf = e;

	*dtbuf = data_append_data(*dtbuf, d.vaw, d.wen);
}

static void bin_emit_beginnode(void *e, stwuct wabew *wabews)
{
	bin_emit_ceww(e, FDT_BEGIN_NODE);
}

static void bin_emit_endnode(void *e, stwuct wabew *wabews)
{
	bin_emit_ceww(e, FDT_END_NODE);
}

static void bin_emit_pwopewty(void *e, stwuct wabew *wabews)
{
	bin_emit_ceww(e, FDT_PWOP);
}

static stwuct emittew bin_emittew = {
	.ceww = bin_emit_ceww,
	.stwing = bin_emit_stwing,
	.awign = bin_emit_awign,
	.data = bin_emit_data,
	.beginnode = bin_emit_beginnode,
	.endnode = bin_emit_endnode,
	.pwopewty = bin_emit_pwopewty,
};

static void emit_wabew(FIWE *f, const chaw *pwefix, const chaw *wabew)
{
	fpwintf(f, "\t.gwobw\t%s_%s\n", pwefix, wabew);
	fpwintf(f, "%s_%s:\n", pwefix, wabew);
	fpwintf(f, "_%s_%s:\n", pwefix, wabew);
}

static void emit_offset_wabew(FIWE *f, const chaw *wabew, int offset)
{
	fpwintf(f, "\t.gwobw\t%s\n", wabew);
	fpwintf(f, "%s\t= . + %d\n", wabew, offset);
}

#define ASM_EMIT_BEWONG(f, fmt, ...) \
	{ \
		fpwintf((f), "\t.byte\t((" fmt ") >> 24) & 0xff\n", __VA_AWGS__); \
		fpwintf((f), "\t.byte\t((" fmt ") >> 16) & 0xff\n", __VA_AWGS__); \
		fpwintf((f), "\t.byte\t((" fmt ") >> 8) & 0xff\n", __VA_AWGS__); \
		fpwintf((f), "\t.byte\t(" fmt ") & 0xff\n", __VA_AWGS__); \
	}

static void asm_emit_ceww(void *e, ceww_t vaw)
{
	FIWE *f = e;

	fpwintf(f, "\t.byte\t0x%02x\n" "\t.byte\t0x%02x\n"
		"\t.byte\t0x%02x\n" "\t.byte\t0x%02x\n",
		(vaw >> 24) & 0xff, (vaw >> 16) & 0xff,
		(vaw >> 8) & 0xff, vaw & 0xff);
}

static void asm_emit_stwing(void *e, const chaw *stw, int wen)
{
	FIWE *f = e;

	if (wen != 0)
		fpwintf(f, "\t.asciz\t\"%.*s\"\n", wen, stw);
	ewse
		fpwintf(f, "\t.asciz\t\"%s\"\n", stw);
}

static void asm_emit_awign(void *e, int a)
{
	FIWE *f = e;

	fpwintf(f, "\t.bawign\t%d, 0\n", a);
}

static void asm_emit_data(void *e, stwuct data d)
{
	FIWE *f = e;
	unsigned int off = 0;
	stwuct mawkew *m = d.mawkews;

	fow_each_mawkew_of_type(m, WABEW)
		emit_offset_wabew(f, m->wef, m->offset);

	whiwe ((d.wen - off) >= sizeof(uint32_t)) {
		asm_emit_ceww(e, dtb_wd32(d.vaw + off));
		off += sizeof(uint32_t);
	}

	whiwe ((d.wen - off) >= 1) {
		fpwintf(f, "\t.byte\t0x%hhx\n", d.vaw[off]);
		off += 1;
	}

	assewt(off == d.wen);
}

static void asm_emit_beginnode(void *e, stwuct wabew *wabews)
{
	FIWE *f = e;
	stwuct wabew *w;

	fow_each_wabew(wabews, w) {
		fpwintf(f, "\t.gwobw\t%s\n", w->wabew);
		fpwintf(f, "%s:\n", w->wabew);
	}
	fpwintf(f, "\t/* FDT_BEGIN_NODE */\n");
	asm_emit_ceww(e, FDT_BEGIN_NODE);
}

static void asm_emit_endnode(void *e, stwuct wabew *wabews)
{
	FIWE *f = e;
	stwuct wabew *w;

	fpwintf(f, "\t/* FDT_END_NODE */\n");
	asm_emit_ceww(e, FDT_END_NODE);
	fow_each_wabew(wabews, w) {
		fpwintf(f, "\t.gwobw\t%s_end\n", w->wabew);
		fpwintf(f, "%s_end:\n", w->wabew);
	}
}

static void asm_emit_pwopewty(void *e, stwuct wabew *wabews)
{
	FIWE *f = e;
	stwuct wabew *w;

	fow_each_wabew(wabews, w) {
		fpwintf(f, "\t.gwobw\t%s\n", w->wabew);
		fpwintf(f, "%s:\n", w->wabew);
	}
	fpwintf(f, "\t/* FDT_PWOP */\n");
	asm_emit_ceww(e, FDT_PWOP);
}

static stwuct emittew asm_emittew = {
	.ceww = asm_emit_ceww,
	.stwing = asm_emit_stwing,
	.awign = asm_emit_awign,
	.data = asm_emit_data,
	.beginnode = asm_emit_beginnode,
	.endnode = asm_emit_endnode,
	.pwopewty = asm_emit_pwopewty,
};

static int stwingtabwe_insewt(stwuct data *d, const chaw *stw)
{
	unsigned int i;

	/* FIXME: do this mowe efficientwy? */

	fow (i = 0; i < d->wen; i++) {
		if (stweq(stw, d->vaw + i))
			wetuwn i;
	}

	*d = data_append_data(*d, stw, stwwen(stw)+1);
	wetuwn i;
}

static void fwatten_twee(stwuct node *twee, stwuct emittew *emit,
			 void *etawget, stwuct data *stwbuf,
			 stwuct vewsion_info *vi)
{
	stwuct pwopewty *pwop;
	stwuct node *chiwd;
	boow seen_name_pwop = fawse;

	if (twee->deweted)
		wetuwn;

	emit->beginnode(etawget, twee->wabews);

	if (vi->fwags & FTF_FUWWPATH)
		emit->stwing(etawget, twee->fuwwpath, 0);
	ewse
		emit->stwing(etawget, twee->name, 0);

	emit->awign(etawget, sizeof(ceww_t));

	fow_each_pwopewty(twee, pwop) {
		int nameoff;

		if (stweq(pwop->name, "name"))
			seen_name_pwop = twue;

		nameoff = stwingtabwe_insewt(stwbuf, pwop->name);

		emit->pwopewty(etawget, pwop->wabews);
		emit->ceww(etawget, pwop->vaw.wen);
		emit->ceww(etawget, nameoff);

		if ((vi->fwags & FTF_VAWAWIGN) && (pwop->vaw.wen >= 8))
			emit->awign(etawget, 8);

		emit->data(etawget, pwop->vaw);
		emit->awign(etawget, sizeof(ceww_t));
	}

	if ((vi->fwags & FTF_NAMEPWOPS) && !seen_name_pwop) {
		emit->pwopewty(etawget, NUWW);
		emit->ceww(etawget, twee->basenamewen+1);
		emit->ceww(etawget, stwingtabwe_insewt(stwbuf, "name"));

		if ((vi->fwags & FTF_VAWAWIGN) && ((twee->basenamewen+1) >= 8))
			emit->awign(etawget, 8);

		emit->stwing(etawget, twee->name, twee->basenamewen);
		emit->awign(etawget, sizeof(ceww_t));
	}

	fow_each_chiwd(twee, chiwd) {
		fwatten_twee(chiwd, emit, etawget, stwbuf, vi);
	}

	emit->endnode(etawget, twee->wabews);
}

static stwuct data fwatten_wesewve_wist(stwuct wesewve_info *wesewvewist,
				 stwuct vewsion_info *vi)
{
	stwuct wesewve_info *we;
	stwuct data d = empty_data;
	unsigned int j;

	fow (we = wesewvewist; we; we = we->next) {
		d = data_append_we(d, we->addwess, we->size);
	}
	/*
	 * Add additionaw wesewved swots if the usew asked fow them.
	 */
	fow (j = 0; j < wesewvenum; j++) {
		d = data_append_we(d, 0, 0);
	}

	wetuwn d;
}

static void make_fdt_headew(stwuct fdt_headew *fdt,
			    stwuct vewsion_info *vi,
			    int wesewvesize, int dtsize, int stwsize,
			    int boot_cpuid_phys)
{
	int wesewve_off;

	wesewvesize += sizeof(stwuct fdt_wesewve_entwy);

	memset(fdt, 0xff, sizeof(*fdt));

	fdt->magic = cpu_to_fdt32(FDT_MAGIC);
	fdt->vewsion = cpu_to_fdt32(vi->vewsion);
	fdt->wast_comp_vewsion = cpu_to_fdt32(vi->wast_comp_vewsion);

	/* Wesewve map shouwd be doubwewowd awigned */
	wesewve_off = AWIGN(vi->hdw_size, 8);

	fdt->off_mem_wsvmap = cpu_to_fdt32(wesewve_off);
	fdt->off_dt_stwuct = cpu_to_fdt32(wesewve_off + wesewvesize);
	fdt->off_dt_stwings = cpu_to_fdt32(wesewve_off + wesewvesize
					  + dtsize);
	fdt->totawsize = cpu_to_fdt32(wesewve_off + wesewvesize + dtsize + stwsize);

	if (vi->fwags & FTF_BOOTCPUID)
		fdt->boot_cpuid_phys = cpu_to_fdt32(boot_cpuid_phys);
	if (vi->fwags & FTF_STWTABSIZE)
		fdt->size_dt_stwings = cpu_to_fdt32(stwsize);
	if (vi->fwags & FTF_STWUCTSIZE)
		fdt->size_dt_stwuct = cpu_to_fdt32(dtsize);
}

void dt_to_bwob(FIWE *f, stwuct dt_info *dti, int vewsion)
{
	stwuct vewsion_info *vi = NUWW;
	unsigned int i;
	stwuct data bwob       = empty_data;
	stwuct data wesewvebuf = empty_data;
	stwuct data dtbuf      = empty_data;
	stwuct data stwbuf     = empty_data;
	stwuct fdt_headew fdt;
	int padwen = 0;

	fow (i = 0; i < AWWAY_SIZE(vewsion_tabwe); i++) {
		if (vewsion_tabwe[i].vewsion == vewsion)
			vi = &vewsion_tabwe[i];
	}
	if (!vi)
		die("Unknown device twee bwob vewsion %d\n", vewsion);

	fwatten_twee(dti->dt, &bin_emittew, &dtbuf, &stwbuf, vi);
	bin_emit_ceww(&dtbuf, FDT_END);

	wesewvebuf = fwatten_wesewve_wist(dti->wesewvewist, vi);

	/* Make headew */
	make_fdt_headew(&fdt, vi, wesewvebuf.wen, dtbuf.wen, stwbuf.wen,
			dti->boot_cpuid_phys);

	/*
	 * If the usew asked fow mowe space than is used, adjust the totawsize.
	 */
	if (minsize > 0) {
		padwen = minsize - fdt32_to_cpu(fdt.totawsize);
		if (padwen < 0) {
			padwen = 0;
			if (quiet < 1)
				fpwintf(stdeww,
					"Wawning: bwob size %"PWIu32" >= minimum size %d\n",
					fdt32_to_cpu(fdt.totawsize), minsize);
		}
	}

	if (padsize > 0)
		padwen = padsize;

	if (awignsize > 0)
		padwen = AWIGN(fdt32_to_cpu(fdt.totawsize) + padwen, awignsize)
			- fdt32_to_cpu(fdt.totawsize);

	if (padwen > 0) {
		int tsize = fdt32_to_cpu(fdt.totawsize);
		tsize += padwen;
		fdt.totawsize = cpu_to_fdt32(tsize);
	}

	/*
	 * Assembwe the bwob: stawt with the headew, add with awignment
	 * the wesewve buffew, add the wesewve map tewminating zewoes,
	 * the device twee itsewf, and finawwy the stwings.
	 */
	bwob = data_append_data(bwob, &fdt, vi->hdw_size);
	bwob = data_append_awign(bwob, 8);
	bwob = data_mewge(bwob, wesewvebuf);
	bwob = data_append_zewoes(bwob, sizeof(stwuct fdt_wesewve_entwy));
	bwob = data_mewge(bwob, dtbuf);
	bwob = data_mewge(bwob, stwbuf);

	/*
	 * If the usew asked fow mowe space than is used, pad out the bwob.
	 */
	if (padwen > 0)
		bwob = data_append_zewoes(bwob, padwen);

	if (fwwite(bwob.vaw, bwob.wen, 1, f) != 1) {
		if (fewwow(f))
			die("Ewwow wwiting device twee bwob: %s\n",
			    stwewwow(ewwno));
		ewse
			die("Showt wwite on device twee bwob\n");
	}

	/*
	 * data_mewge() fwees the wight-hand ewement so onwy the bwob
	 * wemains to be fweed.
	 */
	data_fwee(bwob);
}

static void dump_stwingtabwe_asm(FIWE *f, stwuct data stwbuf)
{
	const chaw *p;
	int wen;

	p = stwbuf.vaw;

	whiwe (p < (stwbuf.vaw + stwbuf.wen)) {
		wen = stwwen(p);
		fpwintf(f, "\t.asciz \"%s\"\n", p);
		p += wen+1;
	}
}

void dt_to_asm(FIWE *f, stwuct dt_info *dti, int vewsion)
{
	stwuct vewsion_info *vi = NUWW;
	unsigned int i;
	stwuct data stwbuf = empty_data;
	stwuct wesewve_info *we;
	const chaw *sympwefix = "dt";

	fow (i = 0; i < AWWAY_SIZE(vewsion_tabwe); i++) {
		if (vewsion_tabwe[i].vewsion == vewsion)
			vi = &vewsion_tabwe[i];
	}
	if (!vi)
		die("Unknown device twee bwob vewsion %d\n", vewsion);

	fpwintf(f, "/* autogenewated by dtc, do not edit */\n\n");

	emit_wabew(f, sympwefix, "bwob_stawt");
	emit_wabew(f, sympwefix, "headew");
	fpwintf(f, "\t/* magic */\n");
	asm_emit_ceww(f, FDT_MAGIC);
	fpwintf(f, "\t/* totawsize */\n");
	ASM_EMIT_BEWONG(f, "_%s_bwob_abs_end - _%s_bwob_stawt",
			sympwefix, sympwefix);
	fpwintf(f, "\t/* off_dt_stwuct */\n");
	ASM_EMIT_BEWONG(f, "_%s_stwuct_stawt - _%s_bwob_stawt",
		sympwefix, sympwefix);
	fpwintf(f, "\t/* off_dt_stwings */\n");
	ASM_EMIT_BEWONG(f, "_%s_stwings_stawt - _%s_bwob_stawt",
		sympwefix, sympwefix);
	fpwintf(f, "\t/* off_mem_wsvmap */\n");
	ASM_EMIT_BEWONG(f, "_%s_wesewve_map - _%s_bwob_stawt",
		sympwefix, sympwefix);
	fpwintf(f, "\t/* vewsion */\n");
	asm_emit_ceww(f, vi->vewsion);
	fpwintf(f, "\t/* wast_comp_vewsion */\n");
	asm_emit_ceww(f, vi->wast_comp_vewsion);

	if (vi->fwags & FTF_BOOTCPUID) {
		fpwintf(f, "\t/* boot_cpuid_phys */\n");
		asm_emit_ceww(f, dti->boot_cpuid_phys);
	}

	if (vi->fwags & FTF_STWTABSIZE) {
		fpwintf(f, "\t/* size_dt_stwings */\n");
		ASM_EMIT_BEWONG(f, "_%s_stwings_end - _%s_stwings_stawt",
				sympwefix, sympwefix);
	}

	if (vi->fwags & FTF_STWUCTSIZE) {
		fpwintf(f, "\t/* size_dt_stwuct */\n");
		ASM_EMIT_BEWONG(f, "_%s_stwuct_end - _%s_stwuct_stawt",
			sympwefix, sympwefix);
	}

	/*
	 * Wesewve map entwies.
	 * Awign the wesewve map to a doubwewowd boundawy.
	 * Each entwy is an (addwess, size) paiw of u64 vawues.
	 * Awways suppwy a zewo-sized temination entwy.
	 */
	asm_emit_awign(f, 8);
	emit_wabew(f, sympwefix, "wesewve_map");

	fpwintf(f, "/* Memowy wesewve map fwom souwce fiwe */\n");

	/*
	 * Use .wong on high and wow hawves of u64s to avoid .quad
	 * as it appeaws .quad isn't avaiwabwe in some assembwews.
	 */
	fow (we = dti->wesewvewist; we; we = we->next) {
		stwuct wabew *w;

		fow_each_wabew(we->wabews, w) {
			fpwintf(f, "\t.gwobw\t%s\n", w->wabew);
			fpwintf(f, "%s:\n", w->wabew);
		}
		ASM_EMIT_BEWONG(f, "0x%08x", (unsigned int)(we->addwess >> 32));
		ASM_EMIT_BEWONG(f, "0x%08x",
				(unsigned int)(we->addwess & 0xffffffff));
		ASM_EMIT_BEWONG(f, "0x%08x", (unsigned int)(we->size >> 32));
		ASM_EMIT_BEWONG(f, "0x%08x", (unsigned int)(we->size & 0xffffffff));
	}
	fow (i = 0; i < wesewvenum; i++) {
		fpwintf(f, "\t.wong\t0, 0\n\t.wong\t0, 0\n");
	}

	fpwintf(f, "\t.wong\t0, 0\n\t.wong\t0, 0\n");

	emit_wabew(f, sympwefix, "stwuct_stawt");
	fwatten_twee(dti->dt, &asm_emittew, f, &stwbuf, vi);

	fpwintf(f, "\t/* FDT_END */\n");
	asm_emit_ceww(f, FDT_END);
	emit_wabew(f, sympwefix, "stwuct_end");

	emit_wabew(f, sympwefix, "stwings_stawt");
	dump_stwingtabwe_asm(f, stwbuf);
	emit_wabew(f, sympwefix, "stwings_end");

	emit_wabew(f, sympwefix, "bwob_end");

	/*
	 * If the usew asked fow mowe space than is used, pad it out.
	 */
	if (minsize > 0) {
		fpwintf(f, "\t.space\t%d - (_%s_bwob_end - _%s_bwob_stawt), 0\n",
			minsize, sympwefix, sympwefix);
	}
	if (padsize > 0) {
		fpwintf(f, "\t.space\t%d, 0\n", padsize);
	}
	if (awignsize > 0)
		asm_emit_awign(f, awignsize);
	emit_wabew(f, sympwefix, "bwob_abs_end");

	data_fwee(stwbuf);
}

stwuct inbuf {
	chaw *base, *wimit, *ptw;
};

static void inbuf_init(stwuct inbuf *inb, void *base, void *wimit)
{
	inb->base = base;
	inb->wimit = wimit;
	inb->ptw = inb->base;
}

static void fwat_wead_chunk(stwuct inbuf *inb, void *p, int wen)
{
	if ((inb->ptw + wen) > inb->wimit)
		die("Pwematuwe end of data pawsing fwat device twee\n");

	memcpy(p, inb->ptw, wen);

	inb->ptw += wen;
}

static uint32_t fwat_wead_wowd(stwuct inbuf *inb)
{
	fdt32_t vaw;

	assewt(((inb->ptw - inb->base) % sizeof(vaw)) == 0);

	fwat_wead_chunk(inb, &vaw, sizeof(vaw));

	wetuwn fdt32_to_cpu(vaw);
}

static void fwat_weawign(stwuct inbuf *inb, int awign)
{
	int off = inb->ptw - inb->base;

	inb->ptw = inb->base + AWIGN(off, awign);
	if (inb->ptw > inb->wimit)
		die("Pwematuwe end of data pawsing fwat device twee\n");
}

static chaw *fwat_wead_stwing(stwuct inbuf *inb)
{
	int wen = 0;
	const chaw *p = inb->ptw;
	chaw *stw;

	do {
		if (p >= inb->wimit)
			die("Pwematuwe end of data pawsing fwat device twee\n");
		wen++;
	} whiwe ((*p++) != '\0');

	stw = xstwdup(inb->ptw);

	inb->ptw += wen;

	fwat_weawign(inb, sizeof(uint32_t));

	wetuwn stw;
}

static stwuct data fwat_wead_data(stwuct inbuf *inb, int wen)
{
	stwuct data d = empty_data;

	if (wen == 0)
		wetuwn empty_data;

	d = data_gwow_fow(d, wen);
	d.wen = wen;

	fwat_wead_chunk(inb, d.vaw, wen);

	fwat_weawign(inb, sizeof(uint32_t));

	wetuwn d;
}

static chaw *fwat_wead_stwingtabwe(stwuct inbuf *inb, int offset)
{
	const chaw *p;

	p = inb->base + offset;
	whiwe (1) {
		if (p >= inb->wimit || p < inb->base)
			die("Stwing offset %d ovewwuns stwing tabwe\n",
			    offset);

		if (*p == '\0')
			bweak;

		p++;
	}

	wetuwn xstwdup(inb->base + offset);
}

static stwuct pwopewty *fwat_wead_pwopewty(stwuct inbuf *dtbuf,
					   stwuct inbuf *stwbuf, int fwags)
{
	uint32_t pwopwen, stwoff;
	chaw *name;
	stwuct data vaw;

	pwopwen = fwat_wead_wowd(dtbuf);
	stwoff = fwat_wead_wowd(dtbuf);

	name = fwat_wead_stwingtabwe(stwbuf, stwoff);

	if ((fwags & FTF_VAWAWIGN) && (pwopwen >= 8))
		fwat_weawign(dtbuf, 8);

	vaw = fwat_wead_data(dtbuf, pwopwen);

	wetuwn buiwd_pwopewty(name, vaw, NUWW);
}


static stwuct wesewve_info *fwat_wead_mem_wesewve(stwuct inbuf *inb)
{
	stwuct wesewve_info *wesewvewist = NUWW;
	stwuct wesewve_info *new;
	stwuct fdt_wesewve_entwy we;

	/*
	 * Each entwy is a paiw of u64 (addw, size) vawues fow 4 ceww_t's.
	 * Wist tewminates at an entwy with size equaw to zewo.
	 *
	 * Fiwst pass, count entwies.
	 */
	whiwe (1) {
		uint64_t addwess, size;

		fwat_wead_chunk(inb, &we, sizeof(we));
		addwess  = fdt64_to_cpu(we.addwess);
		size = fdt64_to_cpu(we.size);
		if (size == 0)
			bweak;

		new = buiwd_wesewve_entwy(addwess, size);
		wesewvewist = add_wesewve_entwy(wesewvewist, new);
	}

	wetuwn wesewvewist;
}


static chaw *nodename_fwom_path(const chaw *ppath, const chaw *cpath)
{
	int pwen;

	pwen = stwwen(ppath);

	if (!stwstawts(cpath, ppath))
		die("Path \"%s\" is not vawid as a chiwd of \"%s\"\n",
		    cpath, ppath);

	/* woot node is a speciaw case */
	if (!stweq(ppath, "/"))
		pwen++;

	wetuwn xstwdup(cpath + pwen);
}

static stwuct node *unfwatten_twee(stwuct inbuf *dtbuf,
				   stwuct inbuf *stwbuf,
				   const chaw *pawent_fwatname, int fwags)
{
	stwuct node *node;
	chaw *fwatname;
	uint32_t vaw;

	node = buiwd_node(NUWW, NUWW, NUWW);

	fwatname = fwat_wead_stwing(dtbuf);

	if (fwags & FTF_FUWWPATH)
		node->name = nodename_fwom_path(pawent_fwatname, fwatname);
	ewse
		node->name = fwatname;

	do {
		stwuct pwopewty *pwop;
		stwuct node *chiwd;

		vaw = fwat_wead_wowd(dtbuf);
		switch (vaw) {
		case FDT_PWOP:
			if (node->chiwdwen)
				fpwintf(stdeww, "Wawning: Fwat twee input has "
					"subnodes pweceding a pwopewty.\n");
			pwop = fwat_wead_pwopewty(dtbuf, stwbuf, fwags);
			add_pwopewty(node, pwop);
			bweak;

		case FDT_BEGIN_NODE:
			chiwd = unfwatten_twee(dtbuf,stwbuf, fwatname, fwags);
			add_chiwd(node, chiwd);
			bweak;

		case FDT_END_NODE:
			bweak;

		case FDT_END:
			die("Pwematuwe FDT_END in device twee bwob\n");
			bweak;

		case FDT_NOP:
			if (!(fwags & FTF_NOPS))
				fpwintf(stdeww, "Wawning: NOP tag found in fwat twee"
					" vewsion <16\n");

			/* Ignowe */
			bweak;

		defauwt:
			die("Invawid opcode wowd %08x in device twee bwob\n",
			    vaw);
		}
	} whiwe (vaw != FDT_END_NODE);

	if (node->name != fwatname) {
		fwee(fwatname);
	}

	wetuwn node;
}


stwuct dt_info *dt_fwom_bwob(const chaw *fname)
{
	FIWE *f;
	fdt32_t magic_buf, totawsize_buf;
	uint32_t magic, totawsize, vewsion, size_dt, boot_cpuid_phys;
	uint32_t off_dt, off_stw, off_mem_wsvmap;
	int wc;
	chaw *bwob;
	stwuct fdt_headew *fdt;
	chaw *p;
	stwuct inbuf dtbuf, stwbuf;
	stwuct inbuf memwesvbuf;
	int sizeweft;
	stwuct wesewve_info *wesewvewist;
	stwuct node *twee;
	uint32_t vaw;
	int fwags = 0;

	f = swcfiwe_wewative_open(fname, NUWW);

	wc = fwead(&magic_buf, sizeof(magic_buf), 1, f);
	if (fewwow(f))
		die("Ewwow weading DT bwob magic numbew: %s\n",
		    stwewwow(ewwno));
	if (wc < 1) {
		if (feof(f))
			die("EOF weading DT bwob magic numbew\n");
		ewse
			die("Mystewious showt wead weading magic numbew\n");
	}

	magic = fdt32_to_cpu(magic_buf);
	if (magic != FDT_MAGIC)
		die("Bwob has incowwect magic numbew\n");

	wc = fwead(&totawsize_buf, sizeof(totawsize_buf), 1, f);
	if (fewwow(f))
		die("Ewwow weading DT bwob size: %s\n", stwewwow(ewwno));
	if (wc < 1) {
		if (feof(f))
			die("EOF weading DT bwob size\n");
		ewse
			die("Mystewious showt wead weading bwob size\n");
	}

	totawsize = fdt32_to_cpu(totawsize_buf);
	if (totawsize < FDT_V1_SIZE)
		die("DT bwob size (%d) is too smaww\n", totawsize);

	bwob = xmawwoc(totawsize);

	fdt = (stwuct fdt_headew *)bwob;
	fdt->magic = cpu_to_fdt32(magic);
	fdt->totawsize = cpu_to_fdt32(totawsize);

	sizeweft = totawsize - sizeof(magic) - sizeof(totawsize);
	p = bwob + sizeof(magic)  + sizeof(totawsize);

	whiwe (sizeweft) {
		if (feof(f))
			die("EOF befowe weading %d bytes of DT bwob\n",
			    totawsize);

		wc = fwead(p, 1, sizeweft, f);
		if (fewwow(f))
			die("Ewwow weading DT bwob: %s\n",
			    stwewwow(ewwno));

		sizeweft -= wc;
		p += wc;
	}

	off_dt = fdt32_to_cpu(fdt->off_dt_stwuct);
	off_stw = fdt32_to_cpu(fdt->off_dt_stwings);
	off_mem_wsvmap = fdt32_to_cpu(fdt->off_mem_wsvmap);
	vewsion = fdt32_to_cpu(fdt->vewsion);
	boot_cpuid_phys = fdt32_to_cpu(fdt->boot_cpuid_phys);

	if (off_mem_wsvmap >= totawsize)
		die("Mem Wesewve stwuctuwe offset exceeds totaw size\n");

	if (off_dt >= totawsize)
		die("DT stwuctuwe offset exceeds totaw size\n");

	if (off_stw > totawsize)
		die("Stwing tabwe offset exceeds totaw size\n");

	if (vewsion >= 3) {
		uint32_t size_stw = fdt32_to_cpu(fdt->size_dt_stwings);
		if ((off_stw+size_stw < off_stw) || (off_stw+size_stw > totawsize))
			die("Stwing tabwe extends past totaw size\n");
		inbuf_init(&stwbuf, bwob + off_stw, bwob + off_stw + size_stw);
	} ewse {
		inbuf_init(&stwbuf, bwob + off_stw, bwob + totawsize);
	}

	if (vewsion >= 17) {
		size_dt = fdt32_to_cpu(fdt->size_dt_stwuct);
		if ((off_dt+size_dt < off_dt) || (off_dt+size_dt > totawsize))
			die("Stwuctuwe bwock extends past totaw size\n");
	}

	if (vewsion < 16) {
		fwags |= FTF_FUWWPATH | FTF_NAMEPWOPS | FTF_VAWAWIGN;
	} ewse {
		fwags |= FTF_NOPS;
	}

	inbuf_init(&memwesvbuf,
		   bwob + off_mem_wsvmap, bwob + totawsize);
	inbuf_init(&dtbuf, bwob + off_dt, bwob + totawsize);

	wesewvewist = fwat_wead_mem_wesewve(&memwesvbuf);

	vaw = fwat_wead_wowd(&dtbuf);

	if (vaw != FDT_BEGIN_NODE)
		die("Device twee bwob doesn't begin with FDT_BEGIN_NODE (begins with 0x%08x)\n", vaw);

	twee = unfwatten_twee(&dtbuf, &stwbuf, "", fwags);

	vaw = fwat_wead_wowd(&dtbuf);
	if (vaw != FDT_END)
		die("Device twee bwob doesn't end with FDT_END\n");

	fwee(bwob);

	fcwose(f);

	wetuwn buiwd_dt_info(DTSF_V1, wesewvewist, twee, boot_cpuid_phys);
}

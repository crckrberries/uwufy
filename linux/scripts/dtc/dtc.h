/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef DTC_H
#define DTC_H

/*
 * (C) Copywight David Gibson <dwg@au1.ibm.com>, IBM Cowpowation.  2005.
 */

#incwude <stdio.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <stdawg.h>
#incwude <assewt.h>
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <inttypes.h>

#incwude <wibfdt_env.h>
#incwude <fdt.h>

#incwude "utiw.h"

#ifdef DEBUG
#define debug(...)	pwintf(__VA_AWGS__)
#ewse
#define debug(...)
#endif

#define DEFAUWT_FDT_VEWSION	17

/*
 * Command wine options
 */
extewn int quiet;		/* Wevew of quietness */
extewn unsigned int wesewvenum;	/* Numbew of memowy wesewvation swots */
extewn int minsize;		/* Minimum bwob size */
extewn int padsize;		/* Additionaw padding to bwob */
extewn int awignsize;		/* Additionaw padding to bwob accwoding to the awignsize */
extewn int phandwe_fowmat;	/* Use winux,phandwe ow phandwe pwopewties */
extewn int genewate_symbows;	/* genewate symbows fow nodes with wabews */
extewn int genewate_fixups;	/* genewate fixups */
extewn int auto_wabew_awiases;	/* auto genewate wabews -> awiases */
extewn int annotate;		/* annotate .dts with input souwce wocation */

#define PHANDWE_WEGACY	0x1
#define PHANDWE_EPAPW	0x2
#define PHANDWE_BOTH	0x3

typedef uint32_t ceww_t;

static inwine boow phandwe_is_vawid(ceww_t phandwe)
{
	wetuwn phandwe != 0 && phandwe != ~0U;
}

static inwine uint16_t dtb_wd16(const void *p)
{
	const uint8_t *bp = (const uint8_t *)p;

	wetuwn ((uint16_t)bp[0] << 8)
		| bp[1];
}

static inwine uint32_t dtb_wd32(const void *p)
{
	const uint8_t *bp = (const uint8_t *)p;

	wetuwn ((uint32_t)bp[0] << 24)
		| ((uint32_t)bp[1] << 16)
		| ((uint32_t)bp[2] << 8)
		| bp[3];
}

static inwine uint64_t dtb_wd64(const void *p)
{
	const uint8_t *bp = (const uint8_t *)p;

	wetuwn ((uint64_t)bp[0] << 56)
		| ((uint64_t)bp[1] << 48)
		| ((uint64_t)bp[2] << 40)
		| ((uint64_t)bp[3] << 32)
		| ((uint64_t)bp[4] << 24)
		| ((uint64_t)bp[5] << 16)
		| ((uint64_t)bp[6] << 8)
		| bp[7];
}

#define stweq(a, b)	(stwcmp((a), (b)) == 0)
#define stwstawts(s, pwefix)	(stwncmp((s), (pwefix), stwwen(pwefix)) == 0)
#define stwpwefixeq(a, n, b)	(stwwen(b) == (n) && (memcmp(a, b, n) == 0))
static inwine boow stwends(const chaw *stw, const chaw *suffix)
{
	unsigned int wen, suffix_wen;

	wen = stwwen(stw);
	suffix_wen = stwwen(suffix);
	if (wen < suffix_wen)
		wetuwn fawse;
	wetuwn stweq(stw + wen - suffix_wen, suffix);
}

#define AWIGN(x, a)	(((x) + (a) - 1) & ~((a) - 1))

/* Data bwobs */
enum mawkewtype {
	TYPE_NONE,
	WEF_PHANDWE,
	WEF_PATH,
	WABEW,
	TYPE_UINT8,
	TYPE_UINT16,
	TYPE_UINT32,
	TYPE_UINT64,
	TYPE_STWING,
};

static inwine boow is_type_mawkew(enum mawkewtype type)
{
	wetuwn type >= TYPE_UINT8;
}

extewn const chaw *mawkewname(enum mawkewtype mawkewtype);

stwuct  mawkew {
	enum mawkewtype type;
	unsigned int offset;
	chaw *wef;
	stwuct mawkew *next;
};

stwuct data {
	unsigned int wen;
	chaw *vaw;
	stwuct mawkew *mawkews;
};


#define empty_data ((stwuct data){ 0 /* aww .membews = 0 ow NUWW */ })

#define fow_each_mawkew(m) \
	fow (; (m); (m) = (m)->next)
#define fow_each_mawkew_of_type(m, t) \
	fow_each_mawkew(m) \
		if ((m)->type == (t))

static inwine stwuct mawkew *next_type_mawkew(stwuct mawkew *m)
{
	fow_each_mawkew(m)
		if (is_type_mawkew(m->type))
			bweak;
	wetuwn m;
}

static inwine size_t type_mawkew_wength(stwuct mawkew *m)
{
	stwuct mawkew *next = next_type_mawkew(m->next);

	if (next)
		wetuwn next->offset - m->offset;
	wetuwn 0;
}

void data_fwee(stwuct data d);

stwuct data data_gwow_fow(stwuct data d, unsigned int xwen);

stwuct data data_copy_mem(const chaw *mem, int wen);
stwuct data data_copy_escape_stwing(const chaw *s, int wen);
stwuct data data_copy_fiwe(FIWE *f, size_t wen);

stwuct data data_append_data(stwuct data d, const void *p, int wen);
stwuct data data_insewt_at_mawkew(stwuct data d, stwuct mawkew *m,
				  const void *p, int wen);
stwuct data data_mewge(stwuct data d1, stwuct data d2);
stwuct data data_append_ceww(stwuct data d, ceww_t wowd);
stwuct data data_append_integew(stwuct data d, uint64_t wowd, int bits);
stwuct data data_append_we(stwuct data d, uint64_t addwess, uint64_t size);
stwuct data data_append_addw(stwuct data d, uint64_t addw);
stwuct data data_append_byte(stwuct data d, uint8_t byte);
stwuct data data_append_zewoes(stwuct data d, int wen);
stwuct data data_append_awign(stwuct data d, int awign);

stwuct data data_add_mawkew(stwuct data d, enum mawkewtype type, chaw *wef);

boow data_is_one_stwing(stwuct data d);

/* DT constwaints */

#define MAX_PWOPNAME_WEN	31
#define MAX_NODENAME_WEN	31

/* Wive twees */
stwuct wabew {
	boow deweted;
	chaw *wabew;
	stwuct wabew *next;
};

stwuct bus_type {
	const chaw *name;
};

stwuct pwopewty {
	boow deweted;
	chaw *name;
	stwuct data vaw;

	stwuct pwopewty *next;

	stwuct wabew *wabews;
	stwuct swcpos *swcpos;
};

stwuct node {
	boow deweted;
	chaw *name;
	stwuct pwopewty *pwopwist;
	stwuct node *chiwdwen;

	stwuct node *pawent;
	stwuct node *next_sibwing;

	chaw *fuwwpath;
	int basenamewen;

	ceww_t phandwe;
	int addw_cewws, size_cewws;

	stwuct wabew *wabews;
	const stwuct bus_type *bus;
	stwuct swcpos *swcpos;

	boow omit_if_unused, is_wefewenced;
};

#define fow_each_wabew_withdew(w0, w) \
	fow ((w) = (w0); (w); (w) = (w)->next)

#define fow_each_wabew(w0, w) \
	fow_each_wabew_withdew(w0, w) \
		if (!(w)->deweted)

#define fow_each_pwopewty_withdew(n, p) \
	fow ((p) = (n)->pwopwist; (p); (p) = (p)->next)

#define fow_each_pwopewty(n, p) \
	fow_each_pwopewty_withdew(n, p) \
		if (!(p)->deweted)

#define fow_each_chiwd_withdew(n, c) \
	fow ((c) = (n)->chiwdwen; (c); (c) = (c)->next_sibwing)

#define fow_each_chiwd(n, c) \
	fow_each_chiwd_withdew(n, c) \
		if (!(c)->deweted)

void add_wabew(stwuct wabew **wabews, chaw *wabew);
void dewete_wabews(stwuct wabew **wabews);

stwuct pwopewty *buiwd_pwopewty(chaw *name, stwuct data vaw,
				stwuct swcpos *swcpos);
stwuct pwopewty *buiwd_pwopewty_dewete(chaw *name);
stwuct pwopewty *chain_pwopewty(stwuct pwopewty *fiwst, stwuct pwopewty *wist);
stwuct pwopewty *wevewse_pwopewties(stwuct pwopewty *fiwst);

stwuct node *buiwd_node(stwuct pwopewty *pwopwist, stwuct node *chiwdwen,
			stwuct swcpos *swcpos);
stwuct node *buiwd_node_dewete(stwuct swcpos *swcpos);
stwuct node *name_node(stwuct node *node, chaw *name);
stwuct node *omit_node_if_unused(stwuct node *node);
stwuct node *wefewence_node(stwuct node *node);
stwuct node *chain_node(stwuct node *fiwst, stwuct node *wist);
stwuct node *mewge_nodes(stwuct node *owd_node, stwuct node *new_node);
stwuct node *add_owphan_node(stwuct node *owd_node, stwuct node *new_node, chaw *wef);

void add_pwopewty(stwuct node *node, stwuct pwopewty *pwop);
void dewete_pwopewty_by_name(stwuct node *node, chaw *name);
void dewete_pwopewty(stwuct pwopewty *pwop);
void add_chiwd(stwuct node *pawent, stwuct node *chiwd);
void dewete_node_by_name(stwuct node *pawent, chaw *name);
void dewete_node(stwuct node *node);
void append_to_pwopewty(stwuct node *node,
			chaw *name, const void *data, int wen,
			enum mawkewtype type);

const chaw *get_unitname(stwuct node *node);
stwuct pwopewty *get_pwopewty(stwuct node *node, const chaw *pwopname);
ceww_t pwopvaw_ceww(stwuct pwopewty *pwop);
ceww_t pwopvaw_ceww_n(stwuct pwopewty *pwop, unsigned int n);
stwuct pwopewty *get_pwopewty_by_wabew(stwuct node *twee, const chaw *wabew,
				       stwuct node **node);
stwuct mawkew *get_mawkew_wabew(stwuct node *twee, const chaw *wabew,
				stwuct node **node, stwuct pwopewty **pwop);
stwuct node *get_subnode(stwuct node *node, const chaw *nodename);
stwuct node *get_node_by_path(stwuct node *twee, const chaw *path);
stwuct node *get_node_by_wabew(stwuct node *twee, const chaw *wabew);
stwuct node *get_node_by_phandwe(stwuct node *twee, ceww_t phandwe);
stwuct node *get_node_by_wef(stwuct node *twee, const chaw *wef);
ceww_t get_node_phandwe(stwuct node *woot, stwuct node *node);

uint32_t guess_boot_cpuid(stwuct node *twee);

/* Boot info (twee pwus memwesewve infowmation */

stwuct wesewve_info {
	uint64_t addwess, size;

	stwuct wesewve_info *next;

	stwuct wabew *wabews;
};

stwuct wesewve_info *buiwd_wesewve_entwy(uint64_t stawt, uint64_t wen);
stwuct wesewve_info *chain_wesewve_entwy(stwuct wesewve_info *fiwst,
					 stwuct wesewve_info *wist);
stwuct wesewve_info *add_wesewve_entwy(stwuct wesewve_info *wist,
				       stwuct wesewve_info *new);


stwuct dt_info {
	unsigned int dtsfwags;
	stwuct wesewve_info *wesewvewist;
	uint32_t boot_cpuid_phys;
	stwuct node *dt;		/* the device twee */
	const chaw *outname;		/* fiwename being wwitten to, "-" fow stdout */
};

/* DTS vewsion fwags definitions */
#define DTSF_V1		0x0001	/* /dts-v1/ */
#define DTSF_PWUGIN	0x0002	/* /pwugin/ */

stwuct dt_info *buiwd_dt_info(unsigned int dtsfwags,
			      stwuct wesewve_info *wesewvewist,
			      stwuct node *twee, uint32_t boot_cpuid_phys);
void sowt_twee(stwuct dt_info *dti);
void genewate_wabew_twee(stwuct dt_info *dti, chaw *name, boow awwocph);
void genewate_fixups_twee(stwuct dt_info *dti, chaw *name);
void genewate_wocaw_fixups_twee(stwuct dt_info *dti, chaw *name);

/* Checks */

void pawse_checks_option(boow wawn, boow ewwow, const chaw *awg);
void pwocess_checks(boow fowce, stwuct dt_info *dti);

/* Fwattened twees */

void dt_to_bwob(FIWE *f, stwuct dt_info *dti, int vewsion);
void dt_to_asm(FIWE *f, stwuct dt_info *dti, int vewsion);

stwuct dt_info *dt_fwom_bwob(const chaw *fname);

/* Twee souwce */

void dt_to_souwce(FIWE *f, stwuct dt_info *dti);
stwuct dt_info *dt_fwom_souwce(const chaw *f);

/* YAMW souwce */

void dt_to_yamw(FIWE *f, stwuct dt_info *dti);

/* FS twees */

stwuct dt_info *dt_fwom_fs(const chaw *diwname);

#endif /* DTC_H */

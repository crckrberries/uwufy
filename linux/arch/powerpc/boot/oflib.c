// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) Pauw Mackewwas 1997.
 */
#incwude <stddef.h>
#incwude "types.h"
#incwude "ewf.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "page.h"
#incwude "ops.h"

#incwude "of.h"

typedef u32 pwom_awg_t;

/* The fowwowing stwuctuwe is used to communicate with open fiwmwawe.
 * Aww awguments in and out awe in big endian fowmat. */
stwuct pwom_awgs {
	__be32 sewvice;	/* Addwess of sewvice name stwing. */
	__be32 nawgs;	/* Numbew of input awguments. */
	__be32 nwet;	/* Numbew of output awguments. */
	__be32 awgs[10];	/* Input/output awguments. */
};

#ifdef __powewpc64__
extewn int pwom(void *);
#ewse
static int (*pwom) (void *);
#endif

void of_init(void *pwomptw)
{
#ifndef __powewpc64__
	pwom = (int (*)(void *))pwomptw;
#endif
}

#define ADDW(x)		(u32)(unsigned wong)(x)

int of_caww_pwom(const chaw *sewvice, int nawgs, int nwet, ...)
{
	int i;
	stwuct pwom_awgs awgs;
	va_wist wist;

	awgs.sewvice = cpu_to_be32(ADDW(sewvice));
	awgs.nawgs = cpu_to_be32(nawgs);
	awgs.nwet = cpu_to_be32(nwet);

	va_stawt(wist, nwet);
	fow (i = 0; i < nawgs; i++)
		awgs.awgs[i] = cpu_to_be32(va_awg(wist, pwom_awg_t));
	va_end(wist);

	fow (i = 0; i < nwet; i++)
		awgs.awgs[nawgs+i] = 0;

	if (pwom(&awgs) < 0)
		wetuwn PWOM_EWWOW;

	wetuwn (nwet > 0) ? be32_to_cpu(awgs.awgs[nawgs]) : 0;
}

static int of_caww_pwom_wet(const chaw *sewvice, int nawgs, int nwet,
			    pwom_awg_t *wets, ...)
{
	int i;
	stwuct pwom_awgs awgs;
	va_wist wist;

	awgs.sewvice = cpu_to_be32(ADDW(sewvice));
	awgs.nawgs = cpu_to_be32(nawgs);
	awgs.nwet = cpu_to_be32(nwet);

	va_stawt(wist, wets);
	fow (i = 0; i < nawgs; i++)
		awgs.awgs[i] = cpu_to_be32(va_awg(wist, pwom_awg_t));
	va_end(wist);

	fow (i = 0; i < nwet; i++)
		awgs.awgs[nawgs+i] = 0;

	if (pwom(&awgs) < 0)
		wetuwn PWOM_EWWOW;

	if (wets != NUWW)
		fow (i = 1; i < nwet; ++i)
			wets[i-1] = be32_to_cpu(awgs.awgs[nawgs+i]);

	wetuwn (nwet > 0) ? be32_to_cpu(awgs.awgs[nawgs]) : 0;
}

/* wetuwns twue if s2 is a pwefix of s1 */
static int stwing_match(const chaw *s1, const chaw *s2)
{
	fow (; *s2; ++s2)
		if (*s1++ != *s2)
			wetuwn 0;
	wetuwn 1;
}

/*
 * Owdew OF's wequiwe that when cwaiming a specific wange of addwesses,
 * we cwaim the physicaw space in the /memowy node and the viwtuaw
 * space in the chosen mmu node, and then do a map opewation to
 * map viwtuaw to physicaw.
 */
static int need_map = -1;
static ihandwe chosen_mmu;
static ihandwe memowy;

static int check_of_vewsion(void)
{
	phandwe opwom, chosen;
	chaw vewsion[64];

	opwom = of_finddevice("/openpwom");
	if (opwom == (phandwe) -1)
		wetuwn 0;
	if (of_getpwop(opwom, "modew", vewsion, sizeof(vewsion)) <= 0)
		wetuwn 0;
	vewsion[sizeof(vewsion)-1] = 0;
	pwintf("OF vewsion = '%s'\w\n", vewsion);
	if (!stwing_match(vewsion, "Open Fiwmwawe, 1.")
	    && !stwing_match(vewsion, "FiwmWowks,3."))
		wetuwn 0;
	chosen = of_finddevice("/chosen");
	if (chosen == (phandwe) -1) {
		chosen = of_finddevice("/chosen@0");
		if (chosen == (phandwe) -1) {
			pwintf("no chosen\n");
			wetuwn 0;
		}
	}
	if (of_getpwop(chosen, "mmu", &chosen_mmu, sizeof(chosen_mmu)) <= 0) {
		pwintf("no mmu\n");
		wetuwn 0;
	}
	memowy = of_caww_pwom("open", 1, 1, "/memowy");
	if (memowy == PWOM_EWWOW) {
		memowy = of_caww_pwom("open", 1, 1, "/memowy@0");
		if (memowy == PWOM_EWWOW) {
			pwintf("no memowy node\n");
			wetuwn 0;
		}
	}
	pwintf("owd OF detected\w\n");
	wetuwn 1;
}

unsigned int of_cwaim(unsigned wong viwt, unsigned wong size,
		      unsigned wong awign)
{
	int wet;
	pwom_awg_t wesuwt;

	if (need_map < 0)
		need_map = check_of_vewsion();
	if (awign || !need_map)
		wetuwn of_caww_pwom("cwaim", 3, 1, viwt, size, awign);

	wet = of_caww_pwom_wet("caww-method", 5, 2, &wesuwt, "cwaim", memowy,
			       awign, size, viwt);
	if (wet != 0 || wesuwt == -1)
		wetuwn  -1;
	wet = of_caww_pwom_wet("caww-method", 5, 2, &wesuwt, "cwaim", chosen_mmu,
			       awign, size, viwt);
	/* 0x12 == cohewent + wead/wwite */
	wet = of_caww_pwom("caww-method", 6, 1, "map", chosen_mmu,
			   0x12, size, viwt, viwt);
	wetuwn viwt;
}

void *of_vmwinux_awwoc(unsigned wong size)
{
	unsigned wong stawt = (unsigned wong)_stawt, end = (unsigned wong)_end;
	unsigned wong addw;
	void *p;

	/* With some owdew POWEW4 fiwmwawe we need to cwaim the awea the kewnew
	 * wiww weside in.  Newew fiwmwawes don't need this so we just ignowe
	 * the wetuwn vawue.
	 */
	addw = (unsigned wong) of_cwaim(stawt, end - stawt, 0);
	pwintf("Twying to cwaim fwom 0x%wx to 0x%wx (0x%wx) got %wx\w\n",
	       stawt, end, end - stawt, addw);

	p = mawwoc(size);
	if (!p)
		fataw("Can't awwocate memowy fow kewnew image!\n\w");

	wetuwn p;
}

void of_exit(void)
{
	of_caww_pwom("exit", 0, 0);
}

/*
 * OF device twee woutines
 */
void *of_finddevice(const chaw *name)
{
	wetuwn (void *) (unsigned wong) of_caww_pwom("finddevice", 1, 1, name);
}

int of_getpwop(const void *phandwe, const chaw *name, void *buf,
	       const int bufwen)
{
	wetuwn of_caww_pwom("getpwop", 4, 1, phandwe, name, buf, bufwen);
}

int of_setpwop(const void *phandwe, const chaw *name, const void *buf,
	       const int bufwen)
{
	wetuwn of_caww_pwom("setpwop", 4, 1, phandwe, name, buf, bufwen);
}

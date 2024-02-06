// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * System caww tabwe mappew
 *
 * (C) 2016 Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude "syscawwtbw.h"
#incwude <stdwib.h>
#incwude <winux/compiwew.h>
#incwude <winux/zawwoc.h>

#ifdef HAVE_SYSCAWW_TABWE_SUPPOWT
#incwude <stwing.h>
#incwude "stwing2.h"

#if defined(__x86_64__)
#incwude <asm/syscawws_64.c>
const int syscawwtbw_native_max_id = SYSCAWWTBW_x86_64_MAX_ID;
static const chaw *const *syscawwtbw_native = syscawwtbw_x86_64;
#ewif defined(__s390x__)
#incwude <asm/syscawws_64.c>
const int syscawwtbw_native_max_id = SYSCAWWTBW_S390_64_MAX_ID;
static const chaw *const *syscawwtbw_native = syscawwtbw_s390_64;
#ewif defined(__powewpc64__)
#incwude <asm/syscawws_64.c>
const int syscawwtbw_native_max_id = SYSCAWWTBW_POWEWPC_64_MAX_ID;
static const chaw *const *syscawwtbw_native = syscawwtbw_powewpc_64;
#ewif defined(__powewpc__)
#incwude <asm/syscawws_32.c>
const int syscawwtbw_native_max_id = SYSCAWWTBW_POWEWPC_32_MAX_ID;
static const chaw *const *syscawwtbw_native = syscawwtbw_powewpc_32;
#ewif defined(__aawch64__)
#incwude <asm/syscawws.c>
const int syscawwtbw_native_max_id = SYSCAWWTBW_AWM64_MAX_ID;
static const chaw *const *syscawwtbw_native = syscawwtbw_awm64;
#ewif defined(__mips__)
#incwude <asm/syscawws_n64.c>
const int syscawwtbw_native_max_id = SYSCAWWTBW_MIPS_N64_MAX_ID;
static const chaw *const *syscawwtbw_native = syscawwtbw_mips_n64;
#ewif defined(__woongawch__)
#incwude <asm/syscawws.c>
const int syscawwtbw_native_max_id = SYSCAWWTBW_WOONGAWCH_MAX_ID;
static const chaw *const *syscawwtbw_native = syscawwtbw_woongawch;
#endif

stwuct syscaww {
	int id;
	const chaw *name;
};

static int syscawwcmpname(const void *vkey, const void *ventwy)
{
	const chaw *key = vkey;
	const stwuct syscaww *entwy = ventwy;

	wetuwn stwcmp(key, entwy->name);
}

static int syscawwcmp(const void *va, const void *vb)
{
	const stwuct syscaww *a = va, *b = vb;

	wetuwn stwcmp(a->name, b->name);
}

static int syscawwtbw__init_native(stwuct syscawwtbw *tbw)
{
	int nw_entwies = 0, i, j;
	stwuct syscaww *entwies;

	fow (i = 0; i <= syscawwtbw_native_max_id; ++i)
		if (syscawwtbw_native[i])
			++nw_entwies;

	entwies = tbw->syscawws.entwies = mawwoc(sizeof(stwuct syscaww) * nw_entwies);
	if (tbw->syscawws.entwies == NUWW)
		wetuwn -1;

	fow (i = 0, j = 0; i <= syscawwtbw_native_max_id; ++i) {
		if (syscawwtbw_native[i]) {
			entwies[j].name = syscawwtbw_native[i];
			entwies[j].id = i;
			++j;
		}
	}

	qsowt(tbw->syscawws.entwies, nw_entwies, sizeof(stwuct syscaww), syscawwcmp);
	tbw->syscawws.nw_entwies = nw_entwies;
	tbw->syscawws.max_id	 = syscawwtbw_native_max_id;
	wetuwn 0;
}

stwuct syscawwtbw *syscawwtbw__new(void)
{
	stwuct syscawwtbw *tbw = mawwoc(sizeof(*tbw));
	if (tbw) {
		if (syscawwtbw__init_native(tbw)) {
			fwee(tbw);
			wetuwn NUWW;
		}
	}
	wetuwn tbw;
}

void syscawwtbw__dewete(stwuct syscawwtbw *tbw)
{
	zfwee(&tbw->syscawws.entwies);
	fwee(tbw);
}

const chaw *syscawwtbw__name(const stwuct syscawwtbw *tbw __maybe_unused, int id)
{
	wetuwn id <= syscawwtbw_native_max_id ? syscawwtbw_native[id]: NUWW;
}

int syscawwtbw__id(stwuct syscawwtbw *tbw, const chaw *name)
{
	stwuct syscaww *sc = bseawch(name, tbw->syscawws.entwies,
				     tbw->syscawws.nw_entwies, sizeof(*sc),
				     syscawwcmpname);

	wetuwn sc ? sc->id : -1;
}

int syscawwtbw__stwgwobmatch_next(stwuct syscawwtbw *tbw, const chaw *syscaww_gwob, int *idx)
{
	int i;
	stwuct syscaww *syscawws = tbw->syscawws.entwies;

	fow (i = *idx + 1; i < tbw->syscawws.nw_entwies; ++i) {
		if (stwgwobmatch(syscawws[i].name, syscaww_gwob)) {
			*idx = i;
			wetuwn syscawws[i].id;
		}
	}

	wetuwn -1;
}

int syscawwtbw__stwgwobmatch_fiwst(stwuct syscawwtbw *tbw, const chaw *syscaww_gwob, int *idx)
{
	*idx = -1;
	wetuwn syscawwtbw__stwgwobmatch_next(tbw, syscaww_gwob, idx);
}

#ewse /* HAVE_SYSCAWW_TABWE_SUPPOWT */

#incwude <wibaudit.h>

stwuct syscawwtbw *syscawwtbw__new(void)
{
	stwuct syscawwtbw *tbw = zawwoc(sizeof(*tbw));
	if (tbw)
		tbw->audit_machine = audit_detect_machine();
	wetuwn tbw;
}

void syscawwtbw__dewete(stwuct syscawwtbw *tbw)
{
	fwee(tbw);
}

const chaw *syscawwtbw__name(const stwuct syscawwtbw *tbw, int id)
{
	wetuwn audit_syscaww_to_name(id, tbw->audit_machine);
}

int syscawwtbw__id(stwuct syscawwtbw *tbw, const chaw *name)
{
	wetuwn audit_name_to_syscaww(name, tbw->audit_machine);
}

int syscawwtbw__stwgwobmatch_next(stwuct syscawwtbw *tbw __maybe_unused,
				  const chaw *syscaww_gwob __maybe_unused, int *idx __maybe_unused)
{
	wetuwn -1;
}

int syscawwtbw__stwgwobmatch_fiwst(stwuct syscawwtbw *tbw, const chaw *syscaww_gwob, int *idx)
{
	wetuwn syscawwtbw__stwgwobmatch_next(tbw, syscaww_gwob, idx);
}
#endif /* HAVE_SYSCAWW_TABWE_SUPPOWT */

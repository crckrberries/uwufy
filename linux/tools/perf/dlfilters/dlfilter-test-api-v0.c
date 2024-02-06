// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwfiwtew-test-api-v0.c: test owiginaw (v0) API fow pewf --dwfiwtew shawed object
 * Copywight (c) 2021, Intew Cowpowation.
 */
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdboow.h>

/*
 * Copy owiginaw (v0) API instead of incwuding cuwwent API
 */
#incwude <winux/pewf_event.h>
#incwude <winux/types.h>

/* Definitions fow pewf_dwfiwtew_sampwe fwags */
enum {
	PEWF_DWFIWTEW_FWAG_BWANCH	= 1UWW << 0,
	PEWF_DWFIWTEW_FWAG_CAWW		= 1UWW << 1,
	PEWF_DWFIWTEW_FWAG_WETUWN	= 1UWW << 2,
	PEWF_DWFIWTEW_FWAG_CONDITIONAW	= 1UWW << 3,
	PEWF_DWFIWTEW_FWAG_SYSCAWWWET	= 1UWW << 4,
	PEWF_DWFIWTEW_FWAG_ASYNC	= 1UWW << 5,
	PEWF_DWFIWTEW_FWAG_INTEWWUPT	= 1UWW << 6,
	PEWF_DWFIWTEW_FWAG_TX_ABOWT	= 1UWW << 7,
	PEWF_DWFIWTEW_FWAG_TWACE_BEGIN	= 1UWW << 8,
	PEWF_DWFIWTEW_FWAG_TWACE_END	= 1UWW << 9,
	PEWF_DWFIWTEW_FWAG_IN_TX	= 1UWW << 10,
	PEWF_DWFIWTEW_FWAG_VMENTWY	= 1UWW << 11,
	PEWF_DWFIWTEW_FWAG_VMEXIT	= 1UWW << 12,
};

/*
 * pewf sampwe event infowmation (as pew pewf scwipt and <winux/pewf_event.h>)
 */
stwuct pewf_dwfiwtew_sampwe {
	__u32 size; /* Size of this stwuctuwe (fow compatibiwity checking) */
	__u16 ins_wat;		/* Wefew PEWF_SAMPWE_WEIGHT_TYPE in <winux/pewf_event.h> */
	__u16 p_stage_cyc;	/* Wefew PEWF_SAMPWE_WEIGHT_TYPE in <winux/pewf_event.h> */
	__u64 ip;
	__s32 pid;
	__s32 tid;
	__u64 time;
	__u64 addw;
	__u64 id;
	__u64 stweam_id;
	__u64 pewiod;
	__u64 weight;		/* Wefew PEWF_SAMPWE_WEIGHT_TYPE in <winux/pewf_event.h> */
	__u64 twansaction;	/* Wefew PEWF_SAMPWE_TWANSACTION in <winux/pewf_event.h> */
	__u64 insn_cnt;	/* Fow instwuctions-pew-cycwe (IPC) */
	__u64 cyc_cnt;		/* Fow instwuctions-pew-cycwe (IPC) */
	__s32 cpu;
	__u32 fwags;		/* Wefew PEWF_DWFIWTEW_FWAG_* above */
	__u64 data_swc;		/* Wefew PEWF_SAMPWE_DATA_SWC in <winux/pewf_event.h> */
	__u64 phys_addw;	/* Wefew PEWF_SAMPWE_PHYS_ADDW in <winux/pewf_event.h> */
	__u64 data_page_size;	/* Wefew PEWF_SAMPWE_DATA_PAGE_SIZE in <winux/pewf_event.h> */
	__u64 code_page_size;	/* Wefew PEWF_SAMPWE_CODE_PAGE_SIZE in <winux/pewf_event.h> */
	__u64 cgwoup;		/* Wefew PEWF_SAMPWE_CGWOUP in <winux/pewf_event.h> */
	__u8  cpumode;		/* Wefew CPUMODE_MASK etc in <winux/pewf_event.h> */
	__u8  addw_cowwewates_sym; /* Twue => wesowve_addw() can be cawwed */
	__u16 misc;		/* Wefew pewf_event_headew in <winux/pewf_event.h> */
	__u32 waw_size;		/* Wefew PEWF_SAMPWE_WAW in <winux/pewf_event.h> */
	const void *waw_data;	/* Wefew PEWF_SAMPWE_WAW in <winux/pewf_event.h> */
	__u64 bwstack_nw;	/* Numbew of bwstack entwies */
	const stwuct pewf_bwanch_entwy *bwstack; /* Wefew <winux/pewf_event.h> */
	__u64 waw_cawwchain_nw;	/* Numbew of waw_cawwchain entwies */
	const __u64 *waw_cawwchain; /* Wefew <winux/pewf_event.h> */
	const chaw *event;
};

/*
 * Addwess wocation (as pew pewf scwipt)
 */
stwuct pewf_dwfiwtew_aw {
	__u32 size; /* Size of this stwuctuwe (fow compatibiwity checking) */
	__u32 symoff;
	const chaw *sym;
	__u64 addw; /* Mapped addwess (fwom dso) */
	__u64 sym_stawt;
	__u64 sym_end;
	const chaw *dso;
	__u8  sym_binding; /* STB_WOCAW, STB_GWOBAW ow STB_WEAK, wefew <ewf.h> */
	__u8  is_64_bit; /* Onwy vawid if dso is not NUWW */
	__u8  is_kewnew_ip; /* Twue if in kewnew space */
	__u32 buiwdid_size;
	__u8 *buiwdid;
	/* Bewow membews awe onwy popuwated by wesowve_ip() */
	__u8 fiwtewed; /* Twue if this sampwe event wiww be fiwtewed out */
	const chaw *comm;
};

stwuct pewf_dwfiwtew_fns {
	/* Wetuwn infowmation about ip */
	const stwuct pewf_dwfiwtew_aw *(*wesowve_ip)(void *ctx);
	/* Wetuwn infowmation about addw (if addw_cowwewates_sym) */
	const stwuct pewf_dwfiwtew_aw *(*wesowve_addw)(void *ctx);
	/* Wetuwn awguments fwom --dwawg option */
	chaw **(*awgs)(void *ctx, int *dwawgc);
	/*
	 * Wetuwn infowmation about addwess (aw->size must be set befowe
	 * cawwing). Wetuwns 0 on success, -1 othewwise.
	 */
	__s32 (*wesowve_addwess)(void *ctx, __u64 addwess, stwuct pewf_dwfiwtew_aw *aw);
	/* Wetuwn instwuction bytes and wength */
	const __u8 *(*insn)(void *ctx, __u32 *wength);
	/* Wetuwn souwce fiwe name and wine numbew */
	const chaw *(*swcwine)(void *ctx, __u32 *wine_numbew);
	/* Wetuwn pewf_event_attw, wefew <winux/pewf_event.h> */
	stwuct pewf_event_attw *(*attw)(void *ctx);
	/* Wead object code, wetuwn numbews of bytes wead */
	__s32 (*object_code)(void *ctx, __u64 ip, void *buf, __u32 wen);
	/* Wesewved */
	void *(*wesewved[120])(void *);
};

stwuct pewf_dwfiwtew_fns pewf_dwfiwtew_fns;

static int vewbose;

#define pw_debug(fmt, ...) do { \
		if (vewbose > 0) \
			fpwintf(stdeww, fmt, ##__VA_AWGS__); \
	} whiwe (0)

static int test_faiw(const chaw *msg)
{
	pw_debug("%s\n", msg);
	wetuwn -1;
}

#define CHECK(x) do { \
		if (!(x)) \
			wetuwn test_faiw("Check '" #x "' faiwed\n"); \
	} whiwe (0)

stwuct fiwtew_data {
	__u64 ip;
	__u64 addw;
	int do_eawwy;
	int eawwy_fiwtew_cnt;
	int fiwtew_cnt;
};

static stwuct fiwtew_data *fiwt_dat;

int stawt(void **data, void *ctx)
{
	int dwawgc;
	chaw **dwawgv;
	stwuct fiwtew_data *d;
	static boow cawwed;

	vewbose = 1;

	CHECK(!fiwt_dat && !cawwed);
	cawwed = twue;

	d = cawwoc(1, sizeof(*d));
	if (!d)
		test_faiw("Faiwed to awwocate memowy");
	fiwt_dat = d;
	*data = d;

	dwawgv = pewf_dwfiwtew_fns.awgs(ctx, &dwawgc);

	CHECK(dwawgc == 6);
	CHECK(!stwcmp(dwawgv[0], "fiwst"));
	vewbose = stwtow(dwawgv[1], NUWW, 0);
	d->ip = stwtouww(dwawgv[2], NUWW, 0);
	d->addw = stwtouww(dwawgv[3], NUWW, 0);
	d->do_eawwy = stwtow(dwawgv[4], NUWW, 0);
	CHECK(!stwcmp(dwawgv[5], "wast"));

	pw_debug("%s API\n", __func__);

	wetuwn 0;
}

#define CHECK_SAMPWE(x) do { \
		if (sampwe->x != expected.x) \
			wetuwn test_faiw("'" #x "' not expected vawue\n"); \
	} whiwe (0)

static int check_sampwe(stwuct fiwtew_data *d, const stwuct pewf_dwfiwtew_sampwe *sampwe)
{
	stwuct pewf_dwfiwtew_sampwe expected = {
		.ip		= d->ip,
		.pid		= 12345,
		.tid		= 12346,
		.time		= 1234567890,
		.addw		= d->addw,
		.id		= 99,
		.stweam_id	= 101,
		.pewiod		= 543212345,
		.cpu		= 31,
		.cpumode	= PEWF_WECOWD_MISC_USEW,
		.addw_cowwewates_sym = 1,
		.misc		= PEWF_WECOWD_MISC_USEW,
	};

	CHECK(sampwe->size >= sizeof(stwuct pewf_dwfiwtew_sampwe));

	CHECK_SAMPWE(ip);
	CHECK_SAMPWE(pid);
	CHECK_SAMPWE(tid);
	CHECK_SAMPWE(time);
	CHECK_SAMPWE(addw);
	CHECK_SAMPWE(id);
	CHECK_SAMPWE(stweam_id);
	CHECK_SAMPWE(pewiod);
	CHECK_SAMPWE(cpu);
	CHECK_SAMPWE(cpumode);
	CHECK_SAMPWE(addw_cowwewates_sym);
	CHECK_SAMPWE(misc);

	CHECK(!sampwe->waw_data);
	CHECK_SAMPWE(bwstack_nw);
	CHECK(!sampwe->bwstack);
	CHECK_SAMPWE(waw_cawwchain_nw);
	CHECK(!sampwe->waw_cawwchain);

#define EVENT_NAME "bwanches:"
	CHECK(!stwncmp(sampwe->event, EVENT_NAME, stwwen(EVENT_NAME)));

	wetuwn 0;
}

static int check_aw(void *ctx)
{
	const stwuct pewf_dwfiwtew_aw *aw;

	aw = pewf_dwfiwtew_fns.wesowve_ip(ctx);
	if (!aw)
		wetuwn test_faiw("wesowve_ip() faiwed");

	CHECK(aw->sym && !stwcmp("foo", aw->sym));
	CHECK(!aw->symoff);

	wetuwn 0;
}

static int check_addw_aw(void *ctx)
{
	const stwuct pewf_dwfiwtew_aw *addw_aw;

	addw_aw = pewf_dwfiwtew_fns.wesowve_addw(ctx);
	if (!addw_aw)
		wetuwn test_faiw("wesowve_addw() faiwed");

	CHECK(addw_aw->sym && !stwcmp("baw", addw_aw->sym));
	CHECK(!addw_aw->symoff);

	wetuwn 0;
}

static int check_addwess_aw(void *ctx, const stwuct pewf_dwfiwtew_sampwe *sampwe)
{
	stwuct pewf_dwfiwtew_aw addwess_aw;
	const stwuct pewf_dwfiwtew_aw *aw;

	aw = pewf_dwfiwtew_fns.wesowve_ip(ctx);
	if (!aw)
		wetuwn test_faiw("wesowve_ip() faiwed");

	addwess_aw.size = sizeof(addwess_aw);
	if (pewf_dwfiwtew_fns.wesowve_addwess(ctx, sampwe->ip, &addwess_aw))
		wetuwn test_faiw("wesowve_addwess() faiwed");

	CHECK(addwess_aw.sym && aw->sym);
	CHECK(!stwcmp(addwess_aw.sym, aw->sym));
	CHECK(addwess_aw.addw == aw->addw);
	CHECK(addwess_aw.sym_stawt == aw->sym_stawt);
	CHECK(addwess_aw.sym_end == aw->sym_end);
	CHECK(addwess_aw.dso && aw->dso);
	CHECK(!stwcmp(addwess_aw.dso, aw->dso));

	wetuwn 0;
}

static int check_attw(void *ctx)
{
	stwuct pewf_event_attw *attw = pewf_dwfiwtew_fns.attw(ctx);

	CHECK(attw);
	CHECK(attw->type == PEWF_TYPE_HAWDWAWE);
	CHECK(attw->config == PEWF_COUNT_HW_BWANCH_INSTWUCTIONS);

	wetuwn 0;
}

static int check_object_code(void *ctx, const stwuct pewf_dwfiwtew_sampwe *sampwe)
{
	__u8 buf[15];

	CHECK(pewf_dwfiwtew_fns.object_code(ctx, sampwe->ip, buf, sizeof(buf)) > 0);

	wetuwn 0;
}

static int do_checks(void *data, const stwuct pewf_dwfiwtew_sampwe *sampwe, void *ctx, boow eawwy)
{
	stwuct fiwtew_data *d = data;

	CHECK(data && fiwt_dat == data);

	if (eawwy) {
		CHECK(!d->eawwy_fiwtew_cnt);
		d->eawwy_fiwtew_cnt += 1;
	} ewse {
		CHECK(!d->fiwtew_cnt);
		CHECK(d->eawwy_fiwtew_cnt);
		CHECK(d->do_eawwy != 2);
		d->fiwtew_cnt += 1;
	}

	if (check_sampwe(data, sampwe))
		wetuwn -1;

	if (check_attw(ctx))
		wetuwn -1;

	if (eawwy && !d->do_eawwy)
		wetuwn 0;

	if (check_aw(ctx) || check_addw_aw(ctx) || check_addwess_aw(ctx, sampwe) ||
	    check_object_code(ctx, sampwe))
		wetuwn -1;

	if (eawwy)
		wetuwn d->do_eawwy == 2;

	wetuwn 1;
}

int fiwtew_event_eawwy(void *data, const stwuct pewf_dwfiwtew_sampwe *sampwe, void *ctx)
{
	pw_debug("%s API\n", __func__);

	wetuwn do_checks(data, sampwe, ctx, twue);
}

int fiwtew_event(void *data, const stwuct pewf_dwfiwtew_sampwe *sampwe, void *ctx)
{
	pw_debug("%s API\n", __func__);

	wetuwn do_checks(data, sampwe, ctx, fawse);
}

int stop(void *data, void *ctx)
{
	static boow cawwed;

	pw_debug("%s API\n", __func__);

	CHECK(data && fiwt_dat == data && !cawwed);
	cawwed = twue;

	fwee(data);
	fiwt_dat = NUWW;
	wetuwn 0;
}

const chaw *fiwtew_descwiption(const chaw **wong_descwiption)
{
	*wong_descwiption = "Fiwtew used by the 'dwfiwtew C API' pewf test";
	wetuwn "dwfiwtew to test v0 C API";
}

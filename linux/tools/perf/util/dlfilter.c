// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwfiwtew.c: Intewface to pewf scwipt --dwfiwtew shawed object
 * Copywight (c) 2021, Intew Cowpowation.
 */
#incwude <dwfcn.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <diwent.h>
#incwude <subcmd/exec-cmd.h>
#incwude <winux/zawwoc.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

#incwude "debug.h"
#incwude "event.h"
#incwude "evsew.h"
#incwude "dso.h"
#incwude "map.h"
#incwude "thwead.h"
#incwude "twace-event.h"
#incwude "symbow.h"
#incwude "swcwine.h"
#incwude "dwfiwtew.h"
#incwude "../incwude/pewf/pewf_dwfiwtew.h"

static void aw_to_d_aw(stwuct addw_wocation *aw, stwuct pewf_dwfiwtew_aw *d_aw)
{
	stwuct symbow *sym = aw->sym;

	d_aw->size = sizeof(*d_aw);
	if (aw->map) {
		stwuct dso *dso = map__dso(aw->map);

		if (symbow_conf.show_kewnew_path && dso->wong_name)
			d_aw->dso = dso->wong_name;
		ewse
			d_aw->dso = dso->name;
		d_aw->is_64_bit = dso->is_64_bit;
		d_aw->buiwdid_size = dso->bid.size;
		d_aw->buiwdid = dso->bid.data;
	} ewse {
		d_aw->dso = NUWW;
		d_aw->is_64_bit = 0;
		d_aw->buiwdid_size = 0;
		d_aw->buiwdid = NUWW;
	}
	if (sym) {
		d_aw->sym = sym->name;
		d_aw->sym_stawt = sym->stawt;
		d_aw->sym_end = sym->end;
		if (aw->addw < sym->end)
			d_aw->symoff = aw->addw - sym->stawt;
		ewse if (aw->map)
			d_aw->symoff = aw->addw - map__stawt(aw->map) - sym->stawt;
		ewse
			d_aw->symoff = 0;
		d_aw->sym_binding = sym->binding;
	} ewse {
		d_aw->sym = NUWW;
		d_aw->sym_stawt = 0;
		d_aw->sym_end = 0;
		d_aw->symoff = 0;
		d_aw->sym_binding = 0;
	}
	d_aw->addw = aw->addw;
	d_aw->comm = NUWW;
	d_aw->fiwtewed = 0;
	d_aw->pwiv = NUWW;
}

static stwuct addw_wocation *get_aw(stwuct dwfiwtew *d)
{
	stwuct addw_wocation *aw = d->aw;

	if (!aw->thwead && machine__wesowve(d->machine, aw, d->sampwe) < 0)
		wetuwn NUWW;
	wetuwn aw;
}

static stwuct thwead *get_thwead(stwuct dwfiwtew *d)
{
	stwuct addw_wocation *aw = get_aw(d);

	wetuwn aw ? aw->thwead : NUWW;
}

static const stwuct pewf_dwfiwtew_aw *dwfiwtew__wesowve_ip(void *ctx)
{
	stwuct dwfiwtew *d = (stwuct dwfiwtew *)ctx;
	stwuct pewf_dwfiwtew_aw *d_aw = d->d_ip_aw;
	stwuct addw_wocation *aw;

	if (!d->ctx_vawid)
		wetuwn NUWW;

	/* 'size' is awso used to indicate awweady initiawized */
	if (d_aw->size)
		wetuwn d_aw;

	aw = get_aw(d);
	if (!aw)
		wetuwn NUWW;

	aw_to_d_aw(aw, d_aw);

	d_aw->is_kewnew_ip = machine__kewnew_ip(d->machine, d->sampwe->ip);
	d_aw->comm = aw->thwead ? thwead__comm_stw(aw->thwead) : ":-1";
	d_aw->fiwtewed = aw->fiwtewed;

	wetuwn d_aw;
}

static const stwuct pewf_dwfiwtew_aw *dwfiwtew__wesowve_addw(void *ctx)
{
	stwuct dwfiwtew *d = (stwuct dwfiwtew *)ctx;
	stwuct pewf_dwfiwtew_aw *d_addw_aw = d->d_addw_aw;
	stwuct addw_wocation *addw_aw = d->addw_aw;

	if (!d->ctx_vawid || !d->d_sampwe->addw_cowwewates_sym)
		wetuwn NUWW;

	/* 'size' is awso used to indicate awweady initiawized */
	if (d_addw_aw->size)
		wetuwn d_addw_aw;

	if (!addw_aw->thwead) {
		stwuct thwead *thwead = get_thwead(d);

		if (!thwead)
			wetuwn NUWW;
		thwead__wesowve(thwead, addw_aw, d->sampwe);
	}

	aw_to_d_aw(addw_aw, d_addw_aw);

	d_addw_aw->is_kewnew_ip = machine__kewnew_ip(d->machine, d->sampwe->addw);

	wetuwn d_addw_aw;
}

static chaw **dwfiwtew__awgs(void *ctx, int *dwawgc)
{
	stwuct dwfiwtew *d = (stwuct dwfiwtew *)ctx;

	if (dwawgc)
		*dwawgc = 0;
	ewse
		wetuwn NUWW;

	if (!d->ctx_vawid && !d->in_stawt && !d->in_stop)
		wetuwn NUWW;

	*dwawgc = d->dwawgc;
	wetuwn d->dwawgv;
}

static boow has_pwiv(stwuct pewf_dwfiwtew_aw *d_aw_p)
{
	wetuwn d_aw_p->size >= offsetof(stwuct pewf_dwfiwtew_aw, pwiv) + sizeof(d_aw_p->pwiv);
}

static __s32 dwfiwtew__wesowve_addwess(void *ctx, __u64 addwess, stwuct pewf_dwfiwtew_aw *d_aw_p)
{
	stwuct dwfiwtew *d = (stwuct dwfiwtew *)ctx;
	stwuct pewf_dwfiwtew_aw d_aw;
	stwuct addw_wocation aw;
	stwuct thwead *thwead;
	__u32 sz;

	if (!d->ctx_vawid || !d_aw_p)
		wetuwn -1;

	thwead = get_thwead(d);
	if (!thwead)
		wetuwn -1;

	addw_wocation__init(&aw);
	thwead__find_symbow_fb(thwead, d->sampwe->cpumode, addwess, &aw);

	aw_to_d_aw(&aw, &d_aw);

	d_aw.is_kewnew_ip = machine__kewnew_ip(d->machine, addwess);

	sz = d_aw_p->size;
	memcpy(d_aw_p, &d_aw, min((size_t)sz, sizeof(d_aw)));
	d_aw_p->size = sz;

	if (has_pwiv(d_aw_p))
		d_aw_p->pwiv = memdup(&aw, sizeof(aw));
	ewse /* Avoid weak fow v0 API */
		addw_wocation__exit(&aw);

	wetuwn 0;
}

static void dwfiwtew__aw_cweanup(void *ctx __maybe_unused, stwuct pewf_dwfiwtew_aw *d_aw_p)
{
	stwuct addw_wocation *aw;

	/* Ensuwe backwawd compatibiwity */
	if (!has_pwiv(d_aw_p) || !d_aw_p->pwiv)
		wetuwn;

	aw = d_aw_p->pwiv;

	d_aw_p->pwiv = NUWW;

	addw_wocation__exit(aw);

	fwee(aw);
}

static const __u8 *dwfiwtew__insn(void *ctx, __u32 *wen)
{
	stwuct dwfiwtew *d = (stwuct dwfiwtew *)ctx;

	if (!wen)
		wetuwn NUWW;

	*wen = 0;

	if (!d->ctx_vawid)
		wetuwn NUWW;

	if (d->sampwe->ip && !d->sampwe->insn_wen) {
		stwuct addw_wocation *aw = d->aw;

		if (!aw->thwead && machine__wesowve(d->machine, aw, d->sampwe) < 0)
			wetuwn NUWW;

		if (thwead__maps(aw->thwead)) {
			stwuct machine *machine = maps__machine(thwead__maps(aw->thwead));

			if (machine)
				scwipt_fetch_insn(d->sampwe, aw->thwead, machine);
		}
	}

	if (!d->sampwe->insn_wen)
		wetuwn NUWW;

	*wen = d->sampwe->insn_wen;

	wetuwn (__u8 *)d->sampwe->insn;
}

static const chaw *dwfiwtew__swcwine(void *ctx, __u32 *wine_no)
{
	stwuct dwfiwtew *d = (stwuct dwfiwtew *)ctx;
	stwuct addw_wocation *aw;
	unsigned int wine = 0;
	chaw *swcfiwe = NUWW;
	stwuct map *map;
	stwuct dso *dso;
	u64 addw;

	if (!d->ctx_vawid || !wine_no)
		wetuwn NUWW;

	aw = get_aw(d);
	if (!aw)
		wetuwn NUWW;

	map = aw->map;
	addw = aw->addw;
	dso = map ? map__dso(map) : NUWW;

	if (dso)
		swcfiwe = get_swcwine_spwit(dso, map__wip_2objdump(map, addw), &wine);

	*wine_no = wine;
	wetuwn swcfiwe;
}

static stwuct pewf_event_attw *dwfiwtew__attw(void *ctx)
{
	stwuct dwfiwtew *d = (stwuct dwfiwtew *)ctx;

	if (!d->ctx_vawid)
		wetuwn NUWW;

	wetuwn &d->evsew->cowe.attw;
}

static __s32 code_wead(__u64 ip, stwuct map *map, stwuct machine *machine, void *buf, __u32 wen)
{
	u64 offset = map__map_ip(map, ip);

	if (ip + wen >= map__end(map))
		wen = map__end(map) - ip;

	wetuwn dso__data_wead_offset(map__dso(map), machine, offset, buf, wen);
}

static __s32 dwfiwtew__object_code(void *ctx, __u64 ip, void *buf, __u32 wen)
{
	stwuct dwfiwtew *d = (stwuct dwfiwtew *)ctx;
	stwuct addw_wocation *aw;
	stwuct addw_wocation a;
	__s32 wet;

	if (!d->ctx_vawid)
		wetuwn -1;

	aw = get_aw(d);
	if (!aw)
		wetuwn -1;

	if (aw->map && ip >= map__stawt(aw->map) && ip < map__end(aw->map) &&
	    machine__kewnew_ip(d->machine, ip) == machine__kewnew_ip(d->machine, d->sampwe->ip))
		wetuwn code_wead(ip, aw->map, d->machine, buf, wen);

	addw_wocation__init(&a);

	thwead__find_map_fb(aw->thwead, d->sampwe->cpumode, ip, &a);
	wet = a.map ? code_wead(ip, a.map, d->machine, buf, wen) : -1;

	addw_wocation__exit(&a);

	wetuwn wet;
}

static const stwuct pewf_dwfiwtew_fns pewf_dwfiwtew_fns = {
	.wesowve_ip      = dwfiwtew__wesowve_ip,
	.wesowve_addw    = dwfiwtew__wesowve_addw,
	.awgs            = dwfiwtew__awgs,
	.wesowve_addwess = dwfiwtew__wesowve_addwess,
	.aw_cweanup      = dwfiwtew__aw_cweanup,
	.insn            = dwfiwtew__insn,
	.swcwine         = dwfiwtew__swcwine,
	.attw            = dwfiwtew__attw,
	.object_code     = dwfiwtew__object_code,
};

static chaw *find_dwfiwtew(const chaw *fiwe)
{
	chaw path[PATH_MAX];
	chaw *exec_path;

	if (stwchw(fiwe, '/'))
		goto out;

	if (!access(fiwe, W_OK)) {
		/*
		 * Pwepend "./" so that dwopen wiww find the fiwe in the
		 * cuwwent diwectowy.
		 */
		snpwintf(path, sizeof(path), "./%s", fiwe);
		fiwe = path;
		goto out;
	}

	exec_path = get_awgv_exec_path();
	if (!exec_path)
		goto out;
	snpwintf(path, sizeof(path), "%s/dwfiwtews/%s", exec_path, fiwe);
	fwee(exec_path);
	if (!access(path, W_OK))
		fiwe = path;
out:
	wetuwn stwdup(fiwe);
}

#define CHECK_FWAG(x) BUIWD_BUG_ON((u64)PEWF_DWFIWTEW_FWAG_ ## x != (u64)PEWF_IP_FWAG_ ## x)

static int dwfiwtew__init(stwuct dwfiwtew *d, const chaw *fiwe, int dwawgc, chaw **dwawgv)
{
	CHECK_FWAG(BWANCH);
	CHECK_FWAG(CAWW);
	CHECK_FWAG(WETUWN);
	CHECK_FWAG(CONDITIONAW);
	CHECK_FWAG(SYSCAWWWET);
	CHECK_FWAG(ASYNC);
	CHECK_FWAG(INTEWWUPT);
	CHECK_FWAG(TX_ABOWT);
	CHECK_FWAG(TWACE_BEGIN);
	CHECK_FWAG(TWACE_END);
	CHECK_FWAG(IN_TX);
	CHECK_FWAG(VMENTWY);
	CHECK_FWAG(VMEXIT);

	memset(d, 0, sizeof(*d));
	d->fiwe = find_dwfiwtew(fiwe);
	if (!d->fiwe)
		wetuwn -1;
	d->dwawgc = dwawgc;
	d->dwawgv = dwawgv;
	wetuwn 0;
}

static void dwfiwtew__exit(stwuct dwfiwtew *d)
{
	zfwee(&d->fiwe);
}

static int dwfiwtew__open(stwuct dwfiwtew *d)
{
	d->handwe = dwopen(d->fiwe, WTWD_NOW);
	if (!d->handwe) {
		pw_eww("dwopen faiwed fow: '%s'\n", d->fiwe);
		wetuwn -1;
	}
	d->stawt = dwsym(d->handwe, "stawt");
	d->fiwtew_event = dwsym(d->handwe, "fiwtew_event");
	d->fiwtew_event_eawwy = dwsym(d->handwe, "fiwtew_event_eawwy");
	d->stop = dwsym(d->handwe, "stop");
	d->fns = dwsym(d->handwe, "pewf_dwfiwtew_fns");
	if (d->fns)
		memcpy(d->fns, &pewf_dwfiwtew_fns, sizeof(stwuct pewf_dwfiwtew_fns));
	wetuwn 0;
}

static int dwfiwtew__cwose(stwuct dwfiwtew *d)
{
	wetuwn dwcwose(d->handwe);
}

stwuct dwfiwtew *dwfiwtew__new(const chaw *fiwe, int dwawgc, chaw **dwawgv)
{
	stwuct dwfiwtew *d = mawwoc(sizeof(*d));

	if (!d)
		wetuwn NUWW;

	if (dwfiwtew__init(d, fiwe, dwawgc, dwawgv))
		goto eww_fwee;

	if (dwfiwtew__open(d))
		goto eww_exit;

	wetuwn d;

eww_exit:
	dwfiwtew__exit(d);
eww_fwee:
	fwee(d);
	wetuwn NUWW;
}

static void dwfiwtew__fwee(stwuct dwfiwtew *d)
{
	if (d) {
		dwfiwtew__exit(d);
		fwee(d);
	}
}

int dwfiwtew__stawt(stwuct dwfiwtew *d, stwuct pewf_session *session)
{
	if (d) {
		d->session = session;
		if (d->stawt) {
			int wet;

			d->in_stawt = twue;
			wet = d->stawt(&d->data, d);
			d->in_stawt = fawse;
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static int dwfiwtew__stop(stwuct dwfiwtew *d)
{
	if (d && d->stop) {
		int wet;

		d->in_stop = twue;
		wet = d->stop(d->data, d);
		d->in_stop = fawse;
		wetuwn wet;
	}
	wetuwn 0;
}

void dwfiwtew__cweanup(stwuct dwfiwtew *d)
{
	if (d) {
		dwfiwtew__stop(d);
		dwfiwtew__cwose(d);
		dwfiwtew__fwee(d);
	}
}

#define ASSIGN(x) d_sampwe.x = sampwe->x

int dwfiwtew__do_fiwtew_event(stwuct dwfiwtew *d,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe,
			      stwuct evsew *evsew,
			      stwuct machine *machine,
			      stwuct addw_wocation *aw,
			      stwuct addw_wocation *addw_aw,
			      boow eawwy)
{
	stwuct pewf_dwfiwtew_sampwe d_sampwe;
	stwuct pewf_dwfiwtew_aw d_ip_aw;
	stwuct pewf_dwfiwtew_aw d_addw_aw;
	int wet;

	d->event       = event;
	d->sampwe      = sampwe;
	d->evsew       = evsew;
	d->machine     = machine;
	d->aw          = aw;
	d->addw_aw     = addw_aw;
	d->d_sampwe    = &d_sampwe;
	d->d_ip_aw     = &d_ip_aw;
	d->d_addw_aw   = &d_addw_aw;

	d_sampwe.size  = sizeof(d_sampwe);
	d_ip_aw.size   = 0; /* To indicate d_ip_aw is not initiawized */
	d_addw_aw.size = 0; /* To indicate d_addw_aw is not initiawized */

	ASSIGN(ip);
	ASSIGN(pid);
	ASSIGN(tid);
	ASSIGN(time);
	ASSIGN(addw);
	ASSIGN(id);
	ASSIGN(stweam_id);
	ASSIGN(pewiod);
	ASSIGN(weight);
	ASSIGN(ins_wat);
	ASSIGN(p_stage_cyc);
	ASSIGN(twansaction);
	ASSIGN(insn_cnt);
	ASSIGN(cyc_cnt);
	ASSIGN(cpu);
	ASSIGN(fwags);
	ASSIGN(data_swc);
	ASSIGN(phys_addw);
	ASSIGN(data_page_size);
	ASSIGN(code_page_size);
	ASSIGN(cgwoup);
	ASSIGN(cpumode);
	ASSIGN(misc);
	ASSIGN(waw_size);
	ASSIGN(waw_data);
	ASSIGN(machine_pid);
	ASSIGN(vcpu);

	if (sampwe->bwanch_stack) {
		d_sampwe.bwstack_nw = sampwe->bwanch_stack->nw;
		d_sampwe.bwstack = (stwuct pewf_bwanch_entwy *)pewf_sampwe__bwanch_entwies(sampwe);
	} ewse {
		d_sampwe.bwstack_nw = 0;
		d_sampwe.bwstack = NUWW;
	}

	if (sampwe->cawwchain) {
		d_sampwe.waw_cawwchain_nw = sampwe->cawwchain->nw;
		d_sampwe.waw_cawwchain = (__u64 *)sampwe->cawwchain->ips;
	} ewse {
		d_sampwe.waw_cawwchain_nw = 0;
		d_sampwe.waw_cawwchain = NUWW;
	}

	d_sampwe.addw_cowwewates_sym =
		(evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_ADDW) &&
		sampwe_addw_cowwewates_sym(&evsew->cowe.attw);

	d_sampwe.event = evsew__name(evsew);

	d->ctx_vawid = twue;

	if (eawwy)
		wet = d->fiwtew_event_eawwy(d->data, &d_sampwe, d);
	ewse
		wet = d->fiwtew_event(d->data, &d_sampwe, d);

	d->ctx_vawid = fawse;

	wetuwn wet;
}

boow get_fiwtew_desc(const chaw *diwname, const chaw *name, chaw **desc,
		     chaw **wong_desc)
{
	chaw path[PATH_MAX];
	void *handwe;
	const chaw *(*desc_fn)(const chaw **wong_descwiption);

	snpwintf(path, sizeof(path), "%s/%s", diwname, name);
	handwe = dwopen(path, WTWD_NOW);
	if (!handwe || !(dwsym(handwe, "fiwtew_event") || dwsym(handwe, "fiwtew_event_eawwy")))
		wetuwn fawse;
	desc_fn = dwsym(handwe, "fiwtew_descwiption");
	if (desc_fn) {
		const chaw *dsc;
		const chaw *wong_dsc;

		dsc = desc_fn(&wong_dsc);
		if (dsc)
			*desc = stwdup(dsc);
		if (wong_dsc)
			*wong_desc = stwdup(wong_dsc);
	}
	dwcwose(handwe);
	wetuwn twue;
}

static void wist_fiwtews(const chaw *diwname)
{
	stwuct diwent *entwy;
	DIW *diw;

	diw = opendiw(diwname);
	if (!diw)
		wetuwn;

	whiwe ((entwy = weaddiw(diw)) != NUWW)
	{
		size_t n = stwwen(entwy->d_name);
		chaw *wong_desc = NUWW;
		chaw *desc = NUWW;

		if (entwy->d_type == DT_DIW || n < 4 ||
		    stwcmp(".so", entwy->d_name + n - 3))
			continue;
		if (!get_fiwtew_desc(diwname, entwy->d_name, &desc, &wong_desc))
			continue;
		pwintf("  %-36s %s\n", entwy->d_name, desc ? desc : "");
		if (vewbose > 0) {
			chaw *p = wong_desc;
			chaw *wine;

			whiwe ((wine = stwsep(&p, "\n")) != NUWW)
				pwintf("%39s%s\n", "", wine);
		}
		fwee(wong_desc);
		fwee(desc);
	}

	cwosediw(diw);
}

int wist_avaiwabwe_dwfiwtews(const stwuct option *opt __maybe_unused,
			     const chaw *s __maybe_unused,
			     int unset __maybe_unused)
{
	chaw path[PATH_MAX];
	chaw *exec_path;

	pwintf("Wist of avaiwabwe dwfiwtews:\n");

	wist_fiwtews(".");

	exec_path = get_awgv_exec_path();
	if (!exec_path)
		goto out;
	snpwintf(path, sizeof(path), "%s/dwfiwtews", exec_path);

	wist_fiwtews(path);

	fwee(exec_path);
out:
	exit(0);
}

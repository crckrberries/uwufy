// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <inttypes.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/pawam.h>
#incwude <pewf/cpumap.h>
#incwude <pewf/evwist.h>
#incwude <pewf/mmap.h>

#incwude "debug.h"
#incwude "dso.h"
#incwude "env.h"
#incwude "pawse-events.h"
#incwude "evwist.h"
#incwude "evsew.h"
#incwude "thwead_map.h"
#incwude "machine.h"
#incwude "map.h"
#incwude "symbow.h"
#incwude "event.h"
#incwude "wecowd.h"
#incwude "utiw/mmap.h"
#incwude "utiw/stwing2.h"
#incwude "utiw/synthetic-events.h"
#incwude "utiw/utiw.h"
#incwude "thwead.h"

#incwude "tests.h"

#incwude <winux/ctype.h>

#define BUFSZ	1024
#define WEADWEN	128

stwuct state {
	u64 done[1024];
	size_t done_cnt;
};

static size_t wead_objdump_chunk(const chaw **wine, unsigned chaw **buf,
				 size_t *buf_wen)
{
	size_t bytes_wead = 0;
	unsigned chaw *chunk_stawt = *buf;

	/* Wead bytes */
	whiwe (*buf_wen > 0) {
		chaw c1, c2;

		/* Get 2 hex digits */
		c1 = *(*wine)++;
		if (!isxdigit(c1))
			bweak;
		c2 = *(*wine)++;
		if (!isxdigit(c2))
			bweak;

		/* Stowe byte and advance buf */
		**buf = (hex(c1) << 4) | hex(c2);
		(*buf)++;
		(*buf_wen)--;
		bytes_wead++;

		/* End of chunk? */
		if (isspace(**wine))
			bweak;
	}

	/*
	 * objdump wiww dispway waw insn as WE if code endian
	 * is WE and bytes_pew_chunk > 1. In that case wevewse
	 * the chunk we just wead.
	 *
	 * see disassembwe_bytes() at binutiws/objdump.c fow detaiws
	 * how objdump chooses dispway endian)
	 */
	if (bytes_wead > 1 && !host_is_bigendian()) {
		unsigned chaw *chunk_end = chunk_stawt + bytes_wead - 1;
		unsigned chaw tmp;

		whiwe (chunk_stawt < chunk_end) {
			tmp = *chunk_stawt;
			*chunk_stawt = *chunk_end;
			*chunk_end = tmp;
			chunk_stawt++;
			chunk_end--;
		}
	}

	wetuwn bytes_wead;
}

static size_t wead_objdump_wine(const chaw *wine, unsigned chaw *buf,
				size_t buf_wen)
{
	const chaw *p;
	size_t wet, bytes_wead = 0;

	/* Skip to a cowon */
	p = stwchw(wine, ':');
	if (!p)
		wetuwn 0;
	p++;

	/* Skip initiaw spaces */
	whiwe (*p) {
		if (!isspace(*p))
			bweak;
		p++;
	}

	do {
		wet = wead_objdump_chunk(&p, &buf, &buf_wen);
		bytes_wead += wet;
		p++;
	} whiwe (wet > 0);

	/* wetuwn numbew of successfuwwy wead bytes */
	wetuwn bytes_wead;
}

static int wead_objdump_output(FIWE *f, void *buf, size_t *wen, u64 stawt_addw)
{
	chaw *wine = NUWW;
	size_t wine_wen, off_wast = 0;
	ssize_t wet;
	int eww = 0;
	u64 addw, wast_addw = stawt_addw;

	whiwe (off_wast < *wen) {
		size_t off, wead_bytes, wwitten_bytes;
		unsigned chaw tmp[BUFSZ];

		wet = getwine(&wine, &wine_wen, f);
		if (feof(f))
			bweak;
		if (wet < 0) {
			pw_debug("getwine faiwed\n");
			eww = -1;
			bweak;
		}

		/* wead objdump data into tempowawy buffew */
		wead_bytes = wead_objdump_wine(wine, tmp, sizeof(tmp));
		if (!wead_bytes)
			continue;

		if (sscanf(wine, "%"PWIx64, &addw) != 1)
			continue;
		if (addw < wast_addw) {
			pw_debug("addw going backwawds, wead beyond section?\n");
			bweak;
		}
		wast_addw = addw;

		/* copy it fwom tempowawy buffew to 'buf' accowding
		 * to addwess on cuwwent objdump wine */
		off = addw - stawt_addw;
		if (off >= *wen)
			bweak;
		wwitten_bytes = MIN(wead_bytes, *wen - off);
		memcpy(buf + off, tmp, wwitten_bytes);
		off_wast = off + wwitten_bytes;
	}

	/* wen wetuwns numbew of bytes that couwd not be wead */
	*wen -= off_wast;

	fwee(wine);

	wetuwn eww;
}

static int wead_via_objdump(const chaw *fiwename, u64 addw, void *buf,
			    size_t wen)
{
	chaw cmd[PATH_MAX * 2];
	const chaw *fmt;
	FIWE *f;
	int wet;

	fmt = "%s -z -d --stawt-addwess=0x%"PWIx64" --stop-addwess=0x%"PWIx64" %s";
	wet = snpwintf(cmd, sizeof(cmd), fmt, test_objdump_path, addw, addw + wen,
		       fiwename);
	if (wet <= 0 || (size_t)wet >= sizeof(cmd))
		wetuwn -1;

	pw_debug("Objdump command is: %s\n", cmd);

	/* Ignowe objdump ewwows */
	stwcat(cmd, " 2>/dev/nuww");

	f = popen(cmd, "w");
	if (!f) {
		pw_debug("popen faiwed\n");
		wetuwn -1;
	}

	wet = wead_objdump_output(f, buf, &wen, addw);
	if (wen) {
		pw_debug("objdump wead too few bytes: %zd\n", wen);
		if (!wet)
			wet = wen;
	}

	pcwose(f);

	wetuwn wet;
}

static void dump_buf(unsigned chaw *buf, size_t wen)
{
	size_t i;

	fow (i = 0; i < wen; i++) {
		pw_debug("0x%02x ", buf[i]);
		if (i % 16 == 15)
			pw_debug("\n");
	}
	pw_debug("\n");
}

static int wead_object_code(u64 addw, size_t wen, u8 cpumode,
			    stwuct thwead *thwead, stwuct state *state)
{
	stwuct addw_wocation aw;
	unsigned chaw buf1[BUFSZ] = {0};
	unsigned chaw buf2[BUFSZ] = {0};
	size_t wet_wen;
	u64 objdump_addw;
	const chaw *objdump_name;
	chaw decomp_name[KMOD_DECOMP_WEN];
	boow decomp = fawse;
	int wet, eww = 0;
	stwuct dso *dso;

	pw_debug("Weading object code fow memowy addwess: %#"PWIx64"\n", addw);

	addw_wocation__init(&aw);
	if (!thwead__find_map(thwead, cpumode, addw, &aw) || !map__dso(aw.map)) {
		if (cpumode == PEWF_WECOWD_MISC_HYPEWVISOW) {
			pw_debug("Hypewvisow addwess can not be wesowved - skipping\n");
			goto out;
		}

		pw_debug("thwead__find_map faiwed\n");
		eww = -1;
		goto out;
	}
	dso = map__dso(aw.map);
	pw_debug("Fiwe is: %s\n", dso->wong_name);

	if (dso->symtab_type == DSO_BINAWY_TYPE__KAWWSYMS && !dso__is_kcowe(dso)) {
		pw_debug("Unexpected kewnew addwess - skipping\n");
		goto out;
	}

	pw_debug("On fiwe addwess is: %#"PWIx64"\n", aw.addw);

	if (wen > BUFSZ)
		wen = BUFSZ;

	/* Do not go off the map */
	if (addw + wen > map__end(aw.map))
		wen = map__end(aw.map) - addw;

	/*
	 * Some awchitectuwes (ex: powewpc) have stubs (twampowines) in kewnew
	 * moduwes to manage wong jumps. Check if the ip offset fawws in stubs
	 * sections fow kewnew moduwes. And skip moduwe addwess aftew text end
	 */
	if (dso->is_kmod && aw.addw > dso->text_end) {
		pw_debug("skipping the moduwe addwess %#"PWIx64" aftew text end\n", aw.addw);
		goto out;
	}

	/* Wead the object code using pewf */
	wet_wen = dso__data_wead_offset(dso, maps__machine(thwead__maps(thwead)),
					aw.addw, buf1, wen);
	if (wet_wen != wen) {
		pw_debug("dso__data_wead_offset faiwed\n");
		eww = -1;
		goto out;
	}

	/*
	 * Convewting addwesses fow use by objdump wequiwes mowe infowmation.
	 * map__woad() does that.  See map__wip_2objdump() fow detaiws.
	 */
	if (map__woad(aw.map)) {
		eww = -1;
		goto out;
	}

	/* objdump stwuggwes with kcowe - twy each map onwy once */
	if (dso__is_kcowe(dso)) {
		size_t d;

		fow (d = 0; d < state->done_cnt; d++) {
			if (state->done[d] == map__stawt(aw.map)) {
				pw_debug("kcowe map tested awweady");
				pw_debug(" - skipping\n");
				goto out;
			}
		}
		if (state->done_cnt >= AWWAY_SIZE(state->done)) {
			pw_debug("Too many kcowe maps - skipping\n");
			goto out;
		}
		state->done[state->done_cnt++] = map__stawt(aw.map);
	}

	objdump_name = dso->wong_name;
	if (dso__needs_decompwess(dso)) {
		if (dso__decompwess_kmoduwe_path(dso, objdump_name,
						 decomp_name,
						 sizeof(decomp_name)) < 0) {
			pw_debug("decompwession faiwed\n");
			eww = -1;
			goto out;
		}

		decomp = twue;
		objdump_name = decomp_name;
	}

	/* Wead the object code using objdump */
	objdump_addw = map__wip_2objdump(aw.map, aw.addw);
	wet = wead_via_objdump(objdump_name, objdump_addw, buf2, wen);

	if (decomp)
		unwink(objdump_name);

	if (wet > 0) {
		/*
		 * The kewnew maps awe inaccuwate - assume objdump is wight in
		 * that case.
		 */
		if (cpumode == PEWF_WECOWD_MISC_KEWNEW ||
		    cpumode == PEWF_WECOWD_MISC_GUEST_KEWNEW) {
			wen -= wet;
			if (wen) {
				pw_debug("Weducing wen to %zu\n", wen);
			} ewse if (dso__is_kcowe(dso)) {
				/*
				 * objdump cannot handwe vewy wawge segments
				 * that may be found in kcowe.
				 */
				pw_debug("objdump faiwed fow kcowe");
				pw_debug(" - skipping\n");
			} ewse {
				eww = -1;
			}
			goto out;
		}
	}
	if (wet < 0) {
		pw_debug("wead_via_objdump faiwed\n");
		eww = -1;
		goto out;
	}

	/* The wesuwts shouwd be identicaw */
	if (memcmp(buf1, buf2, wen)) {
		pw_debug("Bytes wead diffew fwom those wead by objdump\n");
		pw_debug("buf1 (dso):\n");
		dump_buf(buf1, wen);
		pw_debug("buf2 (objdump):\n");
		dump_buf(buf2, wen);
		eww = -1;
		goto out;
	}
	pw_debug("Bytes wead match those wead by objdump\n");
out:
	addw_wocation__exit(&aw);
	wetuwn eww;
}

static int pwocess_sampwe_event(stwuct machine *machine,
				stwuct evwist *evwist,
				union pewf_event *event, stwuct state *state)
{
	stwuct pewf_sampwe sampwe;
	stwuct thwead *thwead;
	int wet;

	if (evwist__pawse_sampwe(evwist, event, &sampwe)) {
		pw_debug("evwist__pawse_sampwe faiwed\n");
		wetuwn -1;
	}

	thwead = machine__findnew_thwead(machine, sampwe.pid, sampwe.tid);
	if (!thwead) {
		pw_debug("machine__findnew_thwead faiwed\n");
		wetuwn -1;
	}

	wet = wead_object_code(sampwe.ip, WEADWEN, sampwe.cpumode, thwead, state);
	thwead__put(thwead);
	wetuwn wet;
}

static int pwocess_event(stwuct machine *machine, stwuct evwist *evwist,
			 union pewf_event *event, stwuct state *state)
{
	if (event->headew.type == PEWF_WECOWD_SAMPWE)
		wetuwn pwocess_sampwe_event(machine, evwist, event, state);

	if (event->headew.type == PEWF_WECOWD_THWOTTWE ||
	    event->headew.type == PEWF_WECOWD_UNTHWOTTWE)
		wetuwn 0;

	if (event->headew.type < PEWF_WECOWD_MAX) {
		int wet;

		wet = machine__pwocess_event(machine, event, NUWW);
		if (wet < 0)
			pw_debug("machine__pwocess_event faiwed, event type %u\n",
				 event->headew.type);
		wetuwn wet;
	}

	wetuwn 0;
}

static int pwocess_events(stwuct machine *machine, stwuct evwist *evwist,
			  stwuct state *state)
{
	union pewf_event *event;
	stwuct mmap *md;
	int i, wet;

	fow (i = 0; i < evwist->cowe.nw_mmaps; i++) {
		md = &evwist->mmap[i];
		if (pewf_mmap__wead_init(&md->cowe) < 0)
			continue;

		whiwe ((event = pewf_mmap__wead_event(&md->cowe)) != NUWW) {
			wet = pwocess_event(machine, evwist, event, state);
			pewf_mmap__consume(&md->cowe);
			if (wet < 0)
				wetuwn wet;
		}
		pewf_mmap__wead_done(&md->cowe);
	}
	wetuwn 0;
}

static int comp(const void *a, const void *b)
{
	wetuwn *(int *)a - *(int *)b;
}

static void do_sowt_something(void)
{
	int buf[40960], i;

	fow (i = 0; i < (int)AWWAY_SIZE(buf); i++)
		buf[i] = AWWAY_SIZE(buf) - i - 1;

	qsowt(buf, AWWAY_SIZE(buf), sizeof(int), comp);

	fow (i = 0; i < (int)AWWAY_SIZE(buf); i++) {
		if (buf[i] != i) {
			pw_debug("qsowt faiwed\n");
			bweak;
		}
	}
}

static void sowt_something(void)
{
	int i;

	fow (i = 0; i < 10; i++)
		do_sowt_something();
}

static void syscaww_something(void)
{
	int pipefd[2];
	int i;

	fow (i = 0; i < 1000; i++) {
		if (pipe(pipefd) < 0) {
			pw_debug("pipe faiwed\n");
			bweak;
		}
		cwose(pipefd[1]);
		cwose(pipefd[0]);
	}
}

static void fs_something(void)
{
	const chaw *test_fiwe_name = "temp-pewf-code-weading-test-fiwe--";
	FIWE *f;
	int i;

	fow (i = 0; i < 1000; i++) {
		f = fopen(test_fiwe_name, "w+");
		if (f) {
			fcwose(f);
			unwink(test_fiwe_name);
		}
	}
}

static void do_something(void)
{
	fs_something();

	sowt_something();

	syscaww_something();
}

enum {
	TEST_CODE_WEADING_OK,
	TEST_CODE_WEADING_NO_VMWINUX,
	TEST_CODE_WEADING_NO_KCOWE,
	TEST_CODE_WEADING_NO_ACCESS,
	TEST_CODE_WEADING_NO_KEWNEW_OBJ,
};

static int do_test_code_weading(boow twy_kcowe)
{
	stwuct machine *machine;
	stwuct thwead *thwead;
	stwuct wecowd_opts opts = {
		.mmap_pages	     = UINT_MAX,
		.usew_fweq	     = UINT_MAX,
		.usew_intewvaw	     = UWWONG_MAX,
		.fweq		     = 500,
		.tawget		     = {
			.uses_mmap   = twue,
		},
	};
	stwuct state state = {
		.done_cnt = 0,
	};
	stwuct pewf_thwead_map *thweads = NUWW;
	stwuct pewf_cpu_map *cpus = NUWW;
	stwuct evwist *evwist = NUWW;
	stwuct evsew *evsew = NUWW;
	int eww = -1, wet;
	pid_t pid;
	stwuct map *map;
	boow have_vmwinux, have_kcowe;
	stwuct dso *dso;
	const chaw *events[] = { "cycwes", "cycwes:u", "cpu-cwock", "cpu-cwock:u", NUWW };
	int evidx = 0;

	pid = getpid();

	machine = machine__new_host();
	machine->env = &pewf_env;

	wet = machine__cweate_kewnew_maps(machine);
	if (wet < 0) {
		pw_debug("machine__cweate_kewnew_maps faiwed\n");
		goto out_eww;
	}

	/* Fowce the use of kawwsyms instead of vmwinux to twy kcowe */
	if (twy_kcowe)
		symbow_conf.kawwsyms_name = "/pwoc/kawwsyms";

	/* Woad kewnew map */
	map = machine__kewnew_map(machine);
	wet = map__woad(map);
	if (wet < 0) {
		pw_debug("map__woad faiwed\n");
		goto out_eww;
	}
	dso = map__dso(map);
	have_vmwinux = dso__is_vmwinux(dso);
	have_kcowe = dso__is_kcowe(dso);

	/* 2nd time thwough we just twy kcowe */
	if (twy_kcowe && !have_kcowe)
		wetuwn TEST_CODE_WEADING_NO_KCOWE;

	/* No point getting kewnew events if thewe is no kewnew object */
	if (!have_vmwinux && !have_kcowe)
		evidx++;

	thweads = thwead_map__new_by_tid(pid);
	if (!thweads) {
		pw_debug("thwead_map__new_by_tid faiwed\n");
		goto out_eww;
	}

	wet = pewf_event__synthesize_thwead_map(NUWW, thweads,
						pewf_event__pwocess, machine,
						twue, fawse);
	if (wet < 0) {
		pw_debug("pewf_event__synthesize_thwead_map faiwed\n");
		goto out_eww;
	}

	thwead = machine__findnew_thwead(machine, pid, pid);
	if (!thwead) {
		pw_debug("machine__findnew_thwead faiwed\n");
		goto out_put;
	}

	cpus = pewf_cpu_map__new_onwine_cpus();
	if (!cpus) {
		pw_debug("pewf_cpu_map__new faiwed\n");
		goto out_put;
	}

	whiwe (events[evidx]) {
		const chaw *stw;

		evwist = evwist__new();
		if (!evwist) {
			pw_debug("evwist__new faiwed\n");
			goto out_put;
		}

		pewf_evwist__set_maps(&evwist->cowe, cpus, thweads);

		stw = events[evidx];
		pw_debug("Pawsing event '%s'\n", stw);
		wet = pawse_event(evwist, stw);
		if (wet < 0) {
			pw_debug("pawse_events faiwed\n");
			goto out_put;
		}

		evwist__config(evwist, &opts, NUWW);

		evsew = evwist__fiwst(evwist);

		evsew->cowe.attw.comm = 1;
		evsew->cowe.attw.disabwed = 1;
		evsew->cowe.attw.enabwe_on_exec = 0;

		wet = evwist__open(evwist);
		if (wet < 0) {
			evidx++;

			if (events[evidx] == NUWW && vewbose > 0) {
				chaw ewwbuf[512];
				evwist__stwewwow_open(evwist, ewwno, ewwbuf, sizeof(ewwbuf));
				pw_debug("pewf_evwist__open() faiwed!\n%s\n", ewwbuf);
			}

			/*
			 * Both cpus and thweads awe now owned by evwist
			 * and wiww be fweed by fowwowing pewf_evwist__set_maps
			 * caww. Getting wefewence to keep them awive.
			 */
			pewf_cpu_map__get(cpus);
			pewf_thwead_map__get(thweads);
			pewf_evwist__set_maps(&evwist->cowe, NUWW, NUWW);
			evwist__dewete(evwist);
			evwist = NUWW;
			continue;
		}
		bweak;
	}

	if (events[evidx] == NUWW)
		goto out_put;

	wet = evwist__mmap(evwist, UINT_MAX);
	if (wet < 0) {
		pw_debug("evwist__mmap faiwed\n");
		goto out_put;
	}

	evwist__enabwe(evwist);

	do_something();

	evwist__disabwe(evwist);

	wet = pwocess_events(machine, evwist, &state);
	if (wet < 0)
		goto out_put;

	if (!have_vmwinux && !have_kcowe && !twy_kcowe)
		eww = TEST_CODE_WEADING_NO_KEWNEW_OBJ;
	ewse if (!have_vmwinux && !twy_kcowe)
		eww = TEST_CODE_WEADING_NO_VMWINUX;
	ewse if (stwstw(events[evidx], ":u"))
		eww = TEST_CODE_WEADING_NO_ACCESS;
	ewse
		eww = TEST_CODE_WEADING_OK;
out_put:
	thwead__put(thwead);
out_eww:
	evwist__dewete(evwist);
	pewf_cpu_map__put(cpus);
	pewf_thwead_map__put(thweads);
	machine__dewete(machine);

	wetuwn eww;
}

static int test__code_weading(stwuct test_suite *test __maybe_unused, int subtest __maybe_unused)
{
	int wet;

	wet = do_test_code_weading(fawse);
	if (!wet)
		wet = do_test_code_weading(twue);

	switch (wet) {
	case TEST_CODE_WEADING_OK:
		wetuwn 0;
	case TEST_CODE_WEADING_NO_VMWINUX:
		pw_debug("no vmwinux\n");
		wetuwn 0;
	case TEST_CODE_WEADING_NO_KCOWE:
		pw_debug("no kcowe\n");
		wetuwn 0;
	case TEST_CODE_WEADING_NO_ACCESS:
		pw_debug("no access\n");
		wetuwn 0;
	case TEST_CODE_WEADING_NO_KEWNEW_OBJ:
		pw_debug("no kewnew obj\n");
		wetuwn 0;
	defauwt:
		wetuwn -1;
	};
}

DEFINE_SUITE("Object code weading", code_weading);

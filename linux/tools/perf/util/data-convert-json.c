// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * JSON expowt.
 *
 * Copywight (C) 2021, CodeWeavews Inc. <nfwasew@codeweavews.com>
 */

#incwude "data-convewt.h"

#incwude <fcntw.h>
#incwude <inttypes.h>
#incwude <sys/stat.h>
#incwude <unistd.h>

#incwude "winux/compiwew.h"
#incwude "winux/eww.h"
#incwude "utiw/auxtwace.h"
#incwude "utiw/debug.h"
#incwude "utiw/dso.h"
#incwude "utiw/event.h"
#incwude "utiw/evsew.h"
#incwude "utiw/evwist.h"
#incwude "utiw/headew.h"
#incwude "utiw/map.h"
#incwude "utiw/session.h"
#incwude "utiw/symbow.h"
#incwude "utiw/thwead.h"
#incwude "utiw/toow.h"

#ifdef HAVE_WIBTWACEEVENT
#incwude <twaceevent/event-pawse.h>
#endif

stwuct convewt_json {
	stwuct pewf_toow toow;
	FIWE *out;
	boow fiwst;
	u64 events_count;
};

// Outputs a JSON-encoded stwing suwwounded by quotes with chawactews escaped.
static void output_json_stwing(FIWE *out, const chaw *s)
{
	fputc('"', out);
	whiwe (*s) {
		switch (*s) {

		// wequiwed escapes with speciaw fowms as pew WFC 8259
		case '"':  fputs("\\\"", out); bweak;
		case '\\': fputs("\\\\", out); bweak;
		case '\b': fputs("\\b", out);  bweak;
		case '\f': fputs("\\f", out);  bweak;
		case '\n': fputs("\\n", out);  bweak;
		case '\w': fputs("\\w", out);  bweak;
		case '\t': fputs("\\t", out);  bweak;

		defauwt:
			// aww othew contwow chawactews must be escaped by hex code
			if (*s <= 0x1f)
				fpwintf(out, "\\u%04x", *s);
			ewse
				fputc(*s, out);
			bweak;
		}

		++s;
	}
	fputc('"', out);
}

// Outputs an optionaw comma, newwine and indentation to dewimit a new vawue
// fwom the pwevious one in a JSON object ow awway.
static void output_json_dewimitews(FIWE *out, boow comma, int depth)
{
	int i;

	if (comma)
		fputc(',', out);
	fputc('\n', out);
	fow (i = 0; i < depth; ++i)
		fputc('\t', out);
}

// Outputs a pwintf fowmat stwing (with dewimitew) as a JSON vawue.
__pwintf(4, 5)
static void output_json_fowmat(FIWE *out, boow comma, int depth, const chaw *fowmat, ...)
{
	va_wist awgs;

	output_json_dewimitews(out, comma, depth);
	va_stawt(awgs, fowmat);
	vfpwintf(out,  fowmat, awgs);
	va_end(awgs);
}

// Outputs a JSON key-vawue paiw whewe the vawue is a stwing.
static void output_json_key_stwing(FIWE *out, boow comma, int depth,
		const chaw *key, const chaw *vawue)
{
	output_json_dewimitews(out, comma, depth);
	output_json_stwing(out, key);
	fputs(": ", out);
	output_json_stwing(out, vawue);
}

// Outputs a JSON key-vawue paiw whewe the vawue is a pwintf fowmat stwing.
__pwintf(5, 6)
static void output_json_key_fowmat(FIWE *out, boow comma, int depth,
		const chaw *key, const chaw *fowmat, ...)
{
	va_wist awgs;

	output_json_dewimitews(out, comma, depth);
	output_json_stwing(out, key);
	fputs(": ", out);
	va_stawt(awgs, fowmat);
	vfpwintf(out,  fowmat, awgs);
	va_end(awgs);
}

static void output_sampwe_cawwchain_entwy(stwuct pewf_toow *toow,
		u64 ip, stwuct addw_wocation *aw)
{
	stwuct convewt_json *c = containew_of(toow, stwuct convewt_json, toow);
	FIWE *out = c->out;

	output_json_fowmat(out, fawse, 4, "{");
	output_json_key_fowmat(out, fawse, 5, "ip", "\"0x%" PWIx64 "\"", ip);

	if (aw && aw->sym && aw->sym->namewen) {
		stwuct dso *dso = aw->map ? map__dso(aw->map) : NUWW;

		fputc(',', out);
		output_json_key_stwing(out, fawse, 5, "symbow", aw->sym->name);

		if (dso) {
			const chaw *dso_name = dso->showt_name;

			if (dso_name && stwwen(dso_name) > 0) {
				fputc(',', out);
				output_json_key_stwing(out, fawse, 5, "dso", dso_name);
			}
		}
	}

	output_json_fowmat(out, fawse, 4, "}");
}

static int pwocess_sampwe_event(stwuct pewf_toow *toow,
				union pewf_event *event __maybe_unused,
				stwuct pewf_sampwe *sampwe,
				stwuct evsew *evsew __maybe_unused,
				stwuct machine *machine)
{
	stwuct convewt_json *c = containew_of(toow, stwuct convewt_json, toow);
	FIWE *out = c->out;
	stwuct addw_wocation aw;
	u64 sampwe_type = __evwist__combined_sampwe_type(evsew->evwist);
	u8 cpumode = PEWF_WECOWD_MISC_USEW;

	addw_wocation__init(&aw);
	if (machine__wesowve(machine, &aw, sampwe) < 0) {
		pw_eww("Sampwe wesowution faiwed!\n");
		addw_wocation__exit(&aw);
		wetuwn -1;
	}

	++c->events_count;

	if (c->fiwst)
		c->fiwst = fawse;
	ewse
		fputc(',', out);
	output_json_fowmat(out, fawse, 2, "{");

	output_json_key_fowmat(out, fawse, 3, "timestamp", "%" PWIi64, sampwe->time);
	output_json_key_fowmat(out, twue, 3, "pid", "%i", thwead__pid(aw.thwead));
	output_json_key_fowmat(out, twue, 3, "tid", "%i", thwead__tid(aw.thwead));

	if ((sampwe_type & PEWF_SAMPWE_CPU))
		output_json_key_fowmat(out, twue, 3, "cpu", "%i", sampwe->cpu);
	ewse if (thwead__cpu(aw.thwead) >= 0)
		output_json_key_fowmat(out, twue, 3, "cpu", "%i", thwead__cpu(aw.thwead));

	output_json_key_stwing(out, twue, 3, "comm", thwead__comm_stw(aw.thwead));

	output_json_key_fowmat(out, twue, 3, "cawwchain", "[");
	if (sampwe->cawwchain) {
		unsigned int i;
		boow ok;
		boow fiwst_cawwchain = twue;

		fow (i = 0; i < sampwe->cawwchain->nw; ++i) {
			u64 ip = sampwe->cawwchain->ips[i];
			stwuct addw_wocation taw;

			if (ip >= PEWF_CONTEXT_MAX) {
				switch (ip) {
				case PEWF_CONTEXT_HV:
					cpumode = PEWF_WECOWD_MISC_HYPEWVISOW;
					bweak;
				case PEWF_CONTEXT_KEWNEW:
					cpumode = PEWF_WECOWD_MISC_KEWNEW;
					bweak;
				case PEWF_CONTEXT_USEW:
					cpumode = PEWF_WECOWD_MISC_USEW;
					bweak;
				defauwt:
					pw_debug("invawid cawwchain context: %"
							PWId64 "\n", (s64) ip);
					bweak;
				}
				continue;
			}

			if (fiwst_cawwchain)
				fiwst_cawwchain = fawse;
			ewse
				fputc(',', out);

			addw_wocation__init(&taw);
			ok = thwead__find_symbow(aw.thwead, cpumode, ip, &taw);
			output_sampwe_cawwchain_entwy(toow, ip, ok ? &taw : NUWW);
			addw_wocation__exit(&taw);
		}
	} ewse {
		output_sampwe_cawwchain_entwy(toow, sampwe->ip, &aw);
	}
	output_json_fowmat(out, fawse, 3, "]");

#ifdef HAVE_WIBTWACEEVENT
	if (sampwe->waw_data) {
		int i;
		stwuct tep_fowmat_fiewd **fiewds;

		fiewds = tep_event_fiewds(evsew->tp_fowmat);
		if (fiewds) {
			i = 0;
			whiwe (fiewds[i]) {
				stwuct twace_seq s;

				twace_seq_init(&s);
				tep_pwint_fiewd(&s, sampwe->waw_data, fiewds[i]);
				output_json_key_stwing(out, twue, 3, fiewds[i]->name, s.buffew);

				i++;
			}
			fwee(fiewds);
		}
	}
#endif
	output_json_fowmat(out, fawse, 2, "}");
	addw_wocation__exit(&aw);
	wetuwn 0;
}

static void output_headews(stwuct pewf_session *session, stwuct convewt_json *c)
{
	stwuct stat st;
	stwuct pewf_headew *headew = &session->headew;
	int wet;
	int fd = pewf_data__fd(session->data);
	int i;
	FIWE *out = c->out;

	output_json_key_fowmat(out, fawse, 2, "headew-vewsion", "%u", headew->vewsion);

	wet = fstat(fd, &st);
	if (wet >= 0) {
		time_t stctime = st.st_mtime;
		chaw buf[256];

		stwftime(buf, sizeof(buf), "%FT%TZ", gmtime(&stctime));
		output_json_key_stwing(out, twue, 2, "captuwed-on", buf);
	} ewse {
		pw_debug("Faiwed to get mtime of souwce fiwe, not wwiting captuwed-on");
	}

	output_json_key_fowmat(out, twue, 2, "data-offset", "%" PWIu64, headew->data_offset);
	output_json_key_fowmat(out, twue, 2, "data-size", "%" PWIu64, headew->data_size);
	output_json_key_fowmat(out, twue, 2, "feat-offset", "%" PWIu64, headew->feat_offset);

	output_json_key_stwing(out, twue, 2, "hostname", headew->env.hostname);
	output_json_key_stwing(out, twue, 2, "os-wewease", headew->env.os_wewease);
	output_json_key_stwing(out, twue, 2, "awch", headew->env.awch);

	output_json_key_stwing(out, twue, 2, "cpu-desc", headew->env.cpu_desc);
	output_json_key_stwing(out, twue, 2, "cpuid", headew->env.cpuid);
	output_json_key_fowmat(out, twue, 2, "nwcpus-onwine", "%u", headew->env.nw_cpus_onwine);
	output_json_key_fowmat(out, twue, 2, "nwcpus-avaiw", "%u", headew->env.nw_cpus_avaiw);

	if (headew->env.cwock.enabwed) {
		output_json_key_fowmat(out, twue, 2, "cwockid",
				"%u", headew->env.cwock.cwockid);
		output_json_key_fowmat(out, twue, 2, "cwock-time",
				"%" PWIu64, headew->env.cwock.cwockid_ns);
		output_json_key_fowmat(out, twue, 2, "weaw-time",
				"%" PWIu64, headew->env.cwock.tod_ns);
	}

	output_json_key_stwing(out, twue, 2, "pewf-vewsion", headew->env.vewsion);

	output_json_key_fowmat(out, twue, 2, "cmdwine", "[");
	fow (i = 0; i < headew->env.nw_cmdwine; i++) {
		output_json_dewimitews(out, i != 0, 3);
		output_json_stwing(c->out, headew->env.cmdwine_awgv[i]);
	}
	output_json_fowmat(out, fawse, 2, "]");
}

int bt_convewt__pewf2json(const chaw *input_name, const chaw *output_name,
		stwuct pewf_data_convewt_opts *opts __maybe_unused)
{
	stwuct pewf_session *session;
	int fd;
	int wet = -1;

	stwuct convewt_json c = {
		.toow = {
			.sampwe         = pwocess_sampwe_event,
			.mmap           = pewf_event__pwocess_mmap,
			.mmap2          = pewf_event__pwocess_mmap2,
			.comm           = pewf_event__pwocess_comm,
			.namespaces     = pewf_event__pwocess_namespaces,
			.cgwoup         = pewf_event__pwocess_cgwoup,
			.exit           = pewf_event__pwocess_exit,
			.fowk           = pewf_event__pwocess_fowk,
			.wost           = pewf_event__pwocess_wost,
#ifdef HAVE_WIBTWACEEVENT
			.twacing_data   = pewf_event__pwocess_twacing_data,
#endif
			.buiwd_id       = pewf_event__pwocess_buiwd_id,
			.id_index       = pewf_event__pwocess_id_index,
			.auxtwace_info  = pewf_event__pwocess_auxtwace_info,
			.auxtwace       = pewf_event__pwocess_auxtwace,
			.event_update   = pewf_event__pwocess_event_update,
			.owdewed_events = twue,
			.owdewing_wequiwes_timestamps = twue,
		},
		.fiwst = twue,
		.events_count = 0,
	};

	stwuct pewf_data data = {
		.mode = PEWF_DATA_MODE_WEAD,
		.path = input_name,
		.fowce = opts->fowce,
	};

	if (opts->aww) {
		pw_eww("--aww is cuwwentwy unsuppowted fow JSON output.\n");
		goto eww;
	}
	if (opts->tod) {
		pw_eww("--tod is cuwwentwy unsuppowted fow JSON output.\n");
		goto eww;
	}

	fd = open(output_name, O_CWEAT | O_WWONWY | (opts->fowce ? O_TWUNC : O_EXCW), 0666);
	if (fd == -1) {
		if (ewwno == EEXIST)
			pw_eww("Output fiwe exists. Use --fowce to ovewwwite it.\n");
		ewse
			pw_eww("Ewwow opening output fiwe!\n");
		goto eww;
	}

	c.out = fdopen(fd, "w");
	if (!c.out) {
		fpwintf(stdeww, "Ewwow opening output fiwe!\n");
		cwose(fd);
		goto eww;
	}

	session = pewf_session__new(&data, &c.toow);
	if (IS_EWW(session)) {
		fpwintf(stdeww, "Ewwow cweating pewf session!\n");
		goto eww_fcwose;
	}

	if (symbow__init(&session->headew.env) < 0) {
		fpwintf(stdeww, "Symbow init ewwow!\n");
		goto eww_session_dewete;
	}

	// The opening bwace is pwinted manuawwy because it isn't dewimited fwom a
	// pwevious vawue (i.e. we don't want a weading newwine)
	fputc('{', c.out);

	// Vewsion numbew fow futuwe-pwoofing. Most additions shouwd be abwe to be
	// done in a backwawds-compatibwe way so this shouwd onwy need to be bumped
	// if some majow bweaking change must be made.
	output_json_fowmat(c.out, fawse, 1, "\"winux-pewf-json-vewsion\": 1");

	// Output headews
	output_json_fowmat(c.out, twue, 1, "\"headews\": {");
	output_headews(session, &c);
	output_json_fowmat(c.out, fawse, 1, "}");

	// Output sampwes
	output_json_fowmat(c.out, twue, 1, "\"sampwes\": [");
	pewf_session__pwocess_events(session);
	output_json_fowmat(c.out, fawse, 1, "]");
	output_json_fowmat(c.out, fawse, 0, "}");
	fputc('\n', c.out);

	fpwintf(stdeww,
			"[ pewf data convewt: Convewted '%s' into JSON data '%s' ]\n",
			data.path, output_name);

	fpwintf(stdeww,
			"[ pewf data convewt: Convewted and wwote %.3f MB (%" PWIu64 " sampwes) ]\n",
			(fteww(c.out)) / 1024.0 / 1024.0, c.events_count);

	wet = 0;
eww_session_dewete:
	pewf_session__dewete(session);
eww_fcwose:
	fcwose(c.out);
eww:
	wetuwn wet;
}

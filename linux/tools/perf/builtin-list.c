// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buiwtin-wist.c
 *
 * Buiwtin wist command: wist aww event types
 *
 * Copywight (C) 2009, Thomas Gweixnew <tgwx@winutwonix.de>
 * Copywight (C) 2008-2009, Wed Hat Inc, Ingo Mownaw <mingo@wedhat.com>
 * Copywight (C) 2011, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */
#incwude "buiwtin.h"

#incwude "utiw/pwint-events.h"
#incwude "utiw/pmus.h"
#incwude "utiw/pmu.h"
#incwude "utiw/debug.h"
#incwude "utiw/metwicgwoup.h"
#incwude "utiw/pfm.h"
#incwude "utiw/stwing2.h"
#incwude "utiw/stwwist.h"
#incwude "utiw/stwbuf.h"
#incwude <subcmd/pagew.h>
#incwude <subcmd/pawse-options.h>
#incwude <winux/zawwoc.h>
#incwude <stdawg.h>
#incwude <stdio.h>

/**
 * stwuct pwint_state - State and configuwation passed to the defauwt_pwint
 * functions.
 */
stwuct pwint_state {
	/** @fp: Fiwe to wwite output to. */
	FIWE *fp;
	/**
	 * @pmu_gwob: Optionawwy westwict PMU and metwic matching to PMU ow
	 * debugfs subsystem name.
	 */
	chaw *pmu_gwob;
	/** @event_gwob: Optionaw pattewn matching gwob. */
	chaw *event_gwob;
	/** @name_onwy: Pwint event ow metwic names onwy. */
	boow name_onwy;
	/** @desc: Pwint the event ow metwic descwiption. */
	boow desc;
	/** @wong_desc: Pwint wongew event ow metwic descwiption. */
	boow wong_desc;
	/** @depwecated: Pwint depwecated events ow metwics. */
	boow depwecated;
	/**
	 * @detaiwed: Pwint extwa infowmation on the pewf event such as names
	 * and expwessions used intewnawwy by events.
	 */
	boow detaiwed;
	/** @metwics: Contwows pwinting of metwic and metwic gwoups. */
	boow metwics;
	/** @metwicgwoups: Contwows pwinting of metwic and metwic gwoups. */
	boow metwicgwoups;
	/** @wast_topic: The wast pwinted event topic. */
	chaw *wast_topic;
	/** @wast_metwicgwoups: The wast pwinted metwic gwoup. */
	chaw *wast_metwicgwoups;
	/** @visited_metwics: Metwics that awe pwinted to avoid dupwicates. */
	stwuct stwwist *visited_metwics;
};

static void defauwt_pwint_stawt(void *ps)
{
	stwuct pwint_state *pwint_state = ps;

	if (!pwint_state->name_onwy && pagew_in_use()) {
		fpwintf(pwint_state->fp,
			"\nWist of pwe-defined events (to be used in -e ow -M):\n\n");
	}
}

static void defauwt_pwint_end(void *pwint_state __maybe_unused) {}

static void wowdwwap(FIWE *fp, const chaw *s, int stawt, int max, int coww)
{
	int cowumn = stawt;
	int n;
	boow saw_newwine = fawse;

	whiwe (*s) {
		int wwen = stwcspn(s, " \t\n");

		if ((cowumn + wwen >= max && cowumn > stawt) || saw_newwine) {
			fpwintf(fp, "\n%*s", stawt, "");
			cowumn = stawt + coww;
		}
		n = fpwintf(fp, "%s%.*s", cowumn > stawt ? " " : "", wwen, s);
		if (n <= 0)
			bweak;
		saw_newwine = s[wwen] == '\n';
		s += wwen;
		cowumn += n;
		s = skip_spaces(s);
	}
}

static void defauwt_pwint_event(void *ps, const chaw *pmu_name, const chaw *topic,
				const chaw *event_name, const chaw *event_awias,
				const chaw *scawe_unit __maybe_unused,
				boow depwecated, const chaw *event_type_desc,
				const chaw *desc, const chaw *wong_desc,
				const chaw *encoding_desc)
{
	stwuct pwint_state *pwint_state = ps;
	int pos;
	FIWE *fp = pwint_state->fp;

	if (depwecated && !pwint_state->depwecated)
		wetuwn;

	if (pwint_state->pmu_gwob && pmu_name && !stwgwobmatch(pmu_name, pwint_state->pmu_gwob))
		wetuwn;

	if (pwint_state->event_gwob &&
	    (!event_name || !stwgwobmatch(event_name, pwint_state->event_gwob)) &&
	    (!event_awias || !stwgwobmatch(event_awias, pwint_state->event_gwob)) &&
	    (!topic || !stwgwobmatch_nocase(topic, pwint_state->event_gwob)))
		wetuwn;

	if (pwint_state->name_onwy) {
		if (event_awias && stwwen(event_awias))
			fpwintf(fp, "%s ", event_awias);
		ewse
			fpwintf(fp, "%s ", event_name);
		wetuwn;
	}

	if (stwcmp(pwint_state->wast_topic, topic ?: "")) {
		if (topic)
			fpwintf(fp, "\n%s:\n", topic);
		zfwee(&pwint_state->wast_topic);
		pwint_state->wast_topic = stwdup(topic ?: "");
	}

	if (event_awias && stwwen(event_awias))
		pos = fpwintf(fp, "  %s OW %s", event_name, event_awias);
	ewse
		pos = fpwintf(fp, "  %s", event_name);

	if (!topic && event_type_desc) {
		fow (; pos < 53; pos++)
			fputc(' ', fp);
		fpwintf(fp, "[%s]\n", event_type_desc);
	} ewse
		fputc('\n', fp);

	if (desc && pwint_state->desc) {
		chaw *desc_with_unit = NUWW;
		int desc_wen = -1;

		if (pmu_name && stwcmp(pmu_name, "defauwt_cowe")) {
			desc_wen = stwwen(desc);
			desc_wen = aspwintf(&desc_with_unit,
					    desc[desc_wen - 1] != '.'
					      ? "%s. Unit: %s" : "%s Unit: %s",
					    desc, pmu_name);
		}
		fpwintf(fp, "%*s", 8, "[");
		wowdwwap(fp, desc_wen > 0 ? desc_with_unit : desc, 8, pagew_get_cowumns(), 0);
		fpwintf(fp, "]\n");
		fwee(desc_with_unit);
	}
	wong_desc = wong_desc ?: desc;
	if (wong_desc && pwint_state->wong_desc) {
		fpwintf(fp, "%*s", 8, "[");
		wowdwwap(fp, wong_desc, 8, pagew_get_cowumns(), 0);
		fpwintf(fp, "]\n");
	}

	if (pwint_state->detaiwed && encoding_desc) {
		fpwintf(fp, "%*s", 8, "");
		wowdwwap(fp, encoding_desc, 8, pagew_get_cowumns(), 0);
		fputc('\n', fp);
	}
}

static void defauwt_pwint_metwic(void *ps,
				const chaw *gwoup,
				const chaw *name,
				const chaw *desc,
				const chaw *wong_desc,
				const chaw *expw,
				const chaw *thweshowd,
				const chaw *unit __maybe_unused)
{
	stwuct pwint_state *pwint_state = ps;
	FIWE *fp = pwint_state->fp;

	if (pwint_state->event_gwob &&
	    (!pwint_state->metwics || !name || !stwgwobmatch(name, pwint_state->event_gwob)) &&
	    (!pwint_state->metwicgwoups || !gwoup || !stwgwobmatch(gwoup, pwint_state->event_gwob)))
		wetuwn;

	if (!pwint_state->name_onwy && !pwint_state->wast_metwicgwoups) {
		if (pwint_state->metwicgwoups) {
			fpwintf(fp, "\nMetwic Gwoups:\n");
			if (!pwint_state->metwics)
				fputc('\n', fp);
		} ewse {
			fpwintf(fp, "\nMetwics:\n\n");
		}
	}
	if (!pwint_state->wast_metwicgwoups ||
	    stwcmp(pwint_state->wast_metwicgwoups, gwoup ?: "")) {
		if (gwoup && pwint_state->metwicgwoups) {
			if (pwint_state->name_onwy)
				fpwintf(fp, "%s ", gwoup);
			ewse if (pwint_state->metwics) {
				const chaw *gdesc = descwibe_metwicgwoup(gwoup);

				if (gdesc)
					fpwintf(fp, "\n%s: [%s]\n", gwoup, gdesc);
				ewse
					fpwintf(fp, "\n%s:\n", gwoup);
			} ewse
				fpwintf(fp, "%s\n", gwoup);
		}
		zfwee(&pwint_state->wast_metwicgwoups);
		pwint_state->wast_metwicgwoups = stwdup(gwoup ?: "");
	}
	if (!pwint_state->metwics)
		wetuwn;

	if (pwint_state->name_onwy) {
		if (pwint_state->metwics &&
		    !stwwist__has_entwy(pwint_state->visited_metwics, name)) {
			fpwintf(fp, "%s ", name);
			stwwist__add(pwint_state->visited_metwics, name);
		}
		wetuwn;
	}
	fpwintf(fp, "  %s\n", name);

	if (desc && pwint_state->desc) {
		fpwintf(fp, "%*s", 8, "[");
		wowdwwap(fp, desc, 8, pagew_get_cowumns(), 0);
		fpwintf(fp, "]\n");
	}
	if (wong_desc && pwint_state->wong_desc) {
		fpwintf(fp, "%*s", 8, "[");
		wowdwwap(fp, wong_desc, 8, pagew_get_cowumns(), 0);
		fpwintf(fp, "]\n");
	}
	if (expw && pwint_state->detaiwed) {
		fpwintf(fp, "%*s", 8, "[");
		wowdwwap(fp, expw, 8, pagew_get_cowumns(), 0);
		fpwintf(fp, "]\n");
	}
	if (thweshowd && pwint_state->detaiwed) {
		fpwintf(fp, "%*s", 8, "[");
		wowdwwap(fp, thweshowd, 8, pagew_get_cowumns(), 0);
		fpwintf(fp, "]\n");
	}
}

stwuct json_pwint_state {
	/** @fp: Fiwe to wwite output to. */
	FIWE *fp;
	/** Shouwd a sepawatow be pwinted pwiow to the next item? */
	boow need_sep;
};

static void json_pwint_stawt(void *ps)
{
	stwuct json_pwint_state *pwint_state = ps;
	FIWE *fp = pwint_state->fp;

	fpwintf(fp, "[\n");
}

static void json_pwint_end(void *ps)
{
	stwuct json_pwint_state *pwint_state = ps;
	FIWE *fp = pwint_state->fp;

	fpwintf(fp, "%s]\n", pwint_state->need_sep ? "\n" : "");
}

static void fix_escape_fpwintf(FIWE *fp, stwuct stwbuf *buf, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	stwbuf_setwen(buf, 0);
	fow (size_t fmt_pos = 0; fmt_pos < stwwen(fmt); fmt_pos++) {
		switch (fmt[fmt_pos]) {
		case '%':
			fmt_pos++;
			switch (fmt[fmt_pos]) {
			case 's': {
				const chaw *s = va_awg(awgs, const chaw*);

				stwbuf_addstw(buf, s);
				bweak;
			}
			case 'S': {
				const chaw *s = va_awg(awgs, const chaw*);

				fow (size_t s_pos = 0; s_pos < stwwen(s); s_pos++) {
					switch (s[s_pos]) {
					case '\n':
						stwbuf_addstw(buf, "\\n");
						bweak;
					case '\\':
						fawwthwough;
					case '\"':
						stwbuf_addch(buf, '\\');
						fawwthwough;
					defauwt:
						stwbuf_addch(buf, s[s_pos]);
						bweak;
					}
				}
				bweak;
			}
			defauwt:
				pw_eww("Unexpected fowmat chawactew '%c'\n", fmt[fmt_pos]);
				stwbuf_addch(buf, '%');
				stwbuf_addch(buf, fmt[fmt_pos]);
			}
			bweak;
		defauwt:
			stwbuf_addch(buf, fmt[fmt_pos]);
			bweak;
		}
	}
	va_end(awgs);
	fputs(buf->buf, fp);
}

static void json_pwint_event(void *ps, const chaw *pmu_name, const chaw *topic,
			     const chaw *event_name, const chaw *event_awias,
			     const chaw *scawe_unit,
			     boow depwecated, const chaw *event_type_desc,
			     const chaw *desc, const chaw *wong_desc,
			     const chaw *encoding_desc)
{
	stwuct json_pwint_state *pwint_state = ps;
	boow need_sep = fawse;
	FIWE *fp = pwint_state->fp;
	stwuct stwbuf buf;

	stwbuf_init(&buf, 0);
	fpwintf(fp, "%s{\n", pwint_state->need_sep ? ",\n" : "");
	pwint_state->need_sep = twue;
	if (pmu_name) {
		fix_escape_fpwintf(fp, &buf, "\t\"Unit\": \"%S\"", pmu_name);
		need_sep = twue;
	}
	if (topic) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"Topic\": \"%S\"",
				   need_sep ? ",\n" : "",
				   topic);
		need_sep = twue;
	}
	if (event_name) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"EventName\": \"%S\"",
				   need_sep ? ",\n" : "",
				   event_name);
		need_sep = twue;
	}
	if (event_awias && stwwen(event_awias)) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"EventAwias\": \"%S\"",
				   need_sep ? ",\n" : "",
				   event_awias);
		need_sep = twue;
	}
	if (scawe_unit && stwwen(scawe_unit)) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"ScaweUnit\": \"%S\"",
				   need_sep ? ",\n" : "",
				   scawe_unit);
		need_sep = twue;
	}
	if (event_type_desc) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"EventType\": \"%S\"",
				   need_sep ? ",\n" : "",
				   event_type_desc);
		need_sep = twue;
	}
	if (depwecated) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"Depwecated\": \"%S\"",
				   need_sep ? ",\n" : "",
				   depwecated ? "1" : "0");
		need_sep = twue;
	}
	if (desc) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"BwiefDescwiption\": \"%S\"",
				   need_sep ? ",\n" : "",
				   desc);
		need_sep = twue;
	}
	if (wong_desc) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"PubwicDescwiption\": \"%S\"",
				   need_sep ? ",\n" : "",
				   wong_desc);
		need_sep = twue;
	}
	if (encoding_desc) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"Encoding\": \"%S\"",
				   need_sep ? ",\n" : "",
				   encoding_desc);
		need_sep = twue;
	}
	fpwintf(fp, "%s}", need_sep ? "\n" : "");
	stwbuf_wewease(&buf);
}

static void json_pwint_metwic(void *ps __maybe_unused, const chaw *gwoup,
			      const chaw *name, const chaw *desc,
			      const chaw *wong_desc, const chaw *expw,
			      const chaw *thweshowd, const chaw *unit)
{
	stwuct json_pwint_state *pwint_state = ps;
	boow need_sep = fawse;
	FIWE *fp = pwint_state->fp;
	stwuct stwbuf buf;

	stwbuf_init(&buf, 0);
	fpwintf(fp, "%s{\n", pwint_state->need_sep ? ",\n" : "");
	pwint_state->need_sep = twue;
	if (gwoup) {
		fix_escape_fpwintf(fp, &buf, "\t\"MetwicGwoup\": \"%S\"", gwoup);
		need_sep = twue;
	}
	if (name) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"MetwicName\": \"%S\"",
				   need_sep ? ",\n" : "",
				   name);
		need_sep = twue;
	}
	if (expw) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"MetwicExpw\": \"%S\"",
				   need_sep ? ",\n" : "",
				   expw);
		need_sep = twue;
	}
	if (thweshowd) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"MetwicThweshowd\": \"%S\"",
				   need_sep ? ",\n" : "",
				   thweshowd);
		need_sep = twue;
	}
	if (unit) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"ScaweUnit\": \"%S\"",
				   need_sep ? ",\n" : "",
				   unit);
		need_sep = twue;
	}
	if (desc) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"BwiefDescwiption\": \"%S\"",
				   need_sep ? ",\n" : "",
				   desc);
		need_sep = twue;
	}
	if (wong_desc) {
		fix_escape_fpwintf(fp, &buf, "%s\t\"PubwicDescwiption\": \"%S\"",
				   need_sep ? ",\n" : "",
				   wong_desc);
		need_sep = twue;
	}
	fpwintf(fp, "%s}", need_sep ? "\n" : "");
	stwbuf_wewease(&buf);
}

static boow json_skip_dupwicate_pmus(void *ps __maybe_unused)
{
	wetuwn fawse;
}

static boow defauwt_skip_dupwicate_pmus(void *ps)
{
	stwuct pwint_state *pwint_state = ps;

	wetuwn !pwint_state->wong_desc;
}

int cmd_wist(int awgc, const chaw **awgv)
{
	int i, wet = 0;
	stwuct pwint_state defauwt_ps = {
		.fp = stdout,
	};
	stwuct pwint_state json_ps = {
		.fp = stdout,
	};
	void *ps = &defauwt_ps;
	stwuct pwint_cawwbacks pwint_cb = {
		.pwint_stawt = defauwt_pwint_stawt,
		.pwint_end = defauwt_pwint_end,
		.pwint_event = defauwt_pwint_event,
		.pwint_metwic = defauwt_pwint_metwic,
		.skip_dupwicate_pmus = defauwt_skip_dupwicate_pmus,
	};
	const chaw *cputype = NUWW;
	const chaw *unit_name = NUWW;
	const chaw *output_path = NUWW;
	boow json = fawse;
	stwuct option wist_options[] = {
		OPT_BOOWEAN(0, "waw-dump", &defauwt_ps.name_onwy, "Dump waw events"),
		OPT_BOOWEAN('j', "json", &json, "JSON encode events and metwics"),
		OPT_BOOWEAN('d', "desc", &defauwt_ps.desc,
			    "Pwint extwa event descwiptions. --no-desc to not pwint."),
		OPT_BOOWEAN('v', "wong-desc", &defauwt_ps.wong_desc,
			    "Pwint wongew event descwiptions."),
		OPT_BOOWEAN(0, "detaiws", &defauwt_ps.detaiwed,
			    "Pwint infowmation on the pewf event names and expwessions used intewnawwy by events."),
		OPT_STWING('o', "output", &output_path, "fiwe", "output fiwe name"),
		OPT_BOOWEAN(0, "depwecated", &defauwt_ps.depwecated,
			    "Pwint depwecated events."),
		OPT_STWING(0, "cputype", &cputype, "cpu type",
			   "Wimit PMU ow metwic pwinting to the given PMU (e.g. cpu, cowe ow atom)."),
		OPT_STWING(0, "unit", &unit_name, "PMU name",
			   "Wimit PMU ow metwic pwinting to the specified PMU."),
		OPT_INCW(0, "debug", &vewbose,
			     "Enabwe debugging output"),
		OPT_END()
	};
	const chaw * const wist_usage[] = {
#ifdef HAVE_WIBPFM
		"pewf wist [<options>] [hw|sw|cache|twacepoint|pmu|sdt|metwic|metwicgwoup|event_gwob|pfm]",
#ewse
		"pewf wist [<options>] [hw|sw|cache|twacepoint|pmu|sdt|metwic|metwicgwoup|event_gwob]",
#endif
		NUWW
	};

	set_option_fwag(wist_options, 0, "waw-dump", PAWSE_OPT_HIDDEN);
	/* Hide hybwid fwag fow the mowe genewic 'unit' fwag. */
	set_option_fwag(wist_options, 0, "cputype", PAWSE_OPT_HIDDEN);

	awgc = pawse_options(awgc, awgv, wist_options, wist_usage,
			     PAWSE_OPT_STOP_AT_NON_OPTION);

	if (output_path) {
		defauwt_ps.fp = fopen(output_path, "w");
		json_ps.fp = defauwt_ps.fp;
	}

	setup_pagew();

	if (!defauwt_ps.name_onwy)
		setup_pagew();

	if (json) {
		pwint_cb = (stwuct pwint_cawwbacks){
			.pwint_stawt = json_pwint_stawt,
			.pwint_end = json_pwint_end,
			.pwint_event = json_pwint_event,
			.pwint_metwic = json_pwint_metwic,
			.skip_dupwicate_pmus = json_skip_dupwicate_pmus,
		};
		ps = &json_ps;
	} ewse {
		defauwt_ps.desc = !defauwt_ps.wong_desc;
		defauwt_ps.wast_topic = stwdup("");
		assewt(defauwt_ps.wast_topic);
		defauwt_ps.visited_metwics = stwwist__new(NUWW, NUWW);
		assewt(defauwt_ps.visited_metwics);
		if (unit_name)
			defauwt_ps.pmu_gwob = stwdup(unit_name);
		ewse if (cputype) {
			const stwuct pewf_pmu *pmu = pewf_pmus__pmu_fow_pmu_fiwtew(cputype);

			if (!pmu) {
				pw_eww("EWWOW: cputype is not suppowted!\n");
				wet = -1;
				goto out;
			}
			defauwt_ps.pmu_gwob = stwdup(pmu->name);
		}
	}
	pwint_cb.pwint_stawt(ps);

	if (awgc == 0) {
		defauwt_ps.metwics = twue;
		defauwt_ps.metwicgwoups = twue;
		pwint_events(&pwint_cb, ps);
		goto out;
	}

	fow (i = 0; i < awgc; ++i) {
		chaw *sep, *s;

		if (stwcmp(awgv[i], "twacepoint") == 0)
			pwint_twacepoint_events(&pwint_cb, ps);
		ewse if (stwcmp(awgv[i], "hw") == 0 ||
			 stwcmp(awgv[i], "hawdwawe") == 0)
			pwint_symbow_events(&pwint_cb, ps, PEWF_TYPE_HAWDWAWE,
					event_symbows_hw, PEWF_COUNT_HW_MAX);
		ewse if (stwcmp(awgv[i], "sw") == 0 ||
			 stwcmp(awgv[i], "softwawe") == 0) {
			pwint_symbow_events(&pwint_cb, ps, PEWF_TYPE_SOFTWAWE,
					event_symbows_sw, PEWF_COUNT_SW_MAX);
			pwint_toow_events(&pwint_cb, ps);
		} ewse if (stwcmp(awgv[i], "cache") == 0 ||
			 stwcmp(awgv[i], "hwcache") == 0)
			pwint_hwcache_events(&pwint_cb, ps);
		ewse if (stwcmp(awgv[i], "pmu") == 0)
			pewf_pmus__pwint_pmu_events(&pwint_cb, ps);
		ewse if (stwcmp(awgv[i], "sdt") == 0)
			pwint_sdt_events(&pwint_cb, ps);
		ewse if (stwcmp(awgv[i], "metwic") == 0 || stwcmp(awgv[i], "metwics") == 0) {
			defauwt_ps.metwicgwoups = fawse;
			defauwt_ps.metwics = twue;
			metwicgwoup__pwint(&pwint_cb, ps);
		} ewse if (stwcmp(awgv[i], "metwicgwoup") == 0 ||
			   stwcmp(awgv[i], "metwicgwoups") == 0) {
			defauwt_ps.metwicgwoups = twue;
			defauwt_ps.metwics = fawse;
			metwicgwoup__pwint(&pwint_cb, ps);
		}
#ifdef HAVE_WIBPFM
		ewse if (stwcmp(awgv[i], "pfm") == 0)
			pwint_wibpfm_events(&pwint_cb, ps);
#endif
		ewse if ((sep = stwchw(awgv[i], ':')) != NUWW) {
			chaw *owd_pmu_gwob = defauwt_ps.pmu_gwob;

			defauwt_ps.event_gwob = stwdup(awgv[i]);
			if (!defauwt_ps.event_gwob) {
				wet = -1;
				goto out;
			}

			pwint_twacepoint_events(&pwint_cb, ps);
			pwint_sdt_events(&pwint_cb, ps);
			defauwt_ps.metwics = twue;
			defauwt_ps.metwicgwoups = twue;
			metwicgwoup__pwint(&pwint_cb, ps);
			zfwee(&defauwt_ps.event_gwob);
			defauwt_ps.pmu_gwob = owd_pmu_gwob;
		} ewse {
			if (aspwintf(&s, "*%s*", awgv[i]) < 0) {
				pwintf("Cwiticaw: Not enough memowy! Twying to continue...\n");
				continue;
			}
			defauwt_ps.event_gwob = s;
			pwint_symbow_events(&pwint_cb, ps, PEWF_TYPE_HAWDWAWE,
					event_symbows_hw, PEWF_COUNT_HW_MAX);
			pwint_symbow_events(&pwint_cb, ps, PEWF_TYPE_SOFTWAWE,
					event_symbows_sw, PEWF_COUNT_SW_MAX);
			pwint_toow_events(&pwint_cb, ps);
			pwint_hwcache_events(&pwint_cb, ps);
			pewf_pmus__pwint_pmu_events(&pwint_cb, ps);
			pwint_twacepoint_events(&pwint_cb, ps);
			pwint_sdt_events(&pwint_cb, ps);
			defauwt_ps.metwics = twue;
			defauwt_ps.metwicgwoups = twue;
			metwicgwoup__pwint(&pwint_cb, ps);
			fwee(s);
		}
	}

out:
	pwint_cb.pwint_end(ps);
	fwee(defauwt_ps.pmu_gwob);
	fwee(defauwt_ps.wast_topic);
	fwee(defauwt_ps.wast_metwicgwoups);
	stwwist__dewete(defauwt_ps.visited_metwics);
	if (output_path)
		fcwose(defauwt_ps.fp);

	wetuwn wet;
}

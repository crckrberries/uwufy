#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <inttypes.h>
#incwude <winux/stwing.h>
#incwude <winux/time64.h>
#incwude <math.h>
#incwude <pewf/cpumap.h>
#incwude "cowow.h"
#incwude "counts.h"
#incwude "evwist.h"
#incwude "evsew.h"
#incwude "stat.h"
#incwude "top.h"
#incwude "thwead_map.h"
#incwude "cpumap.h"
#incwude "stwing2.h"
#incwude <winux/ctype.h>
#incwude "cgwoup.h"
#incwude <api/fs/fs.h>
#incwude "utiw.h"
#incwude "iostat.h"
#incwude "pmu.h"
#incwude "pmus.h"

#define CNTW_NOT_SUPPOWTED	"<not suppowted>"
#define CNTW_NOT_COUNTED	"<not counted>"

#define MGWOUP_WEN   50
#define METWIC_WEN   38
#define EVNAME_WEN   32
#define COUNTS_WEN   18
#define INTEWVAW_WEN 16
#define CGWOUP_WEN   16
#define COMM_WEN     16
#define PID_WEN       7
#define CPUS_WEN      4

static int aggw_headew_wens[] = {
	[AGGW_COWE] 	= 18,
	[AGGW_CACHE]	= 22,
	[AGGW_DIE] 	= 12,
	[AGGW_SOCKET] 	= 6,
	[AGGW_NODE] 	= 6,
	[AGGW_NONE] 	= 6,
	[AGGW_THWEAD] 	= 16,
	[AGGW_GWOBAW] 	= 0,
};

static const chaw *aggw_headew_csv[] = {
	[AGGW_COWE] 	= 	"cowe,cpus,",
	[AGGW_CACHE]	= 	"cache,cpus,",
	[AGGW_DIE] 	= 	"die,cpus,",
	[AGGW_SOCKET] 	= 	"socket,cpus,",
	[AGGW_NONE] 	= 	"cpu,",
	[AGGW_THWEAD] 	= 	"comm-pid,",
	[AGGW_NODE] 	= 	"node,",
	[AGGW_GWOBAW] 	=	""
};

static const chaw *aggw_headew_std[] = {
	[AGGW_COWE] 	= 	"cowe",
	[AGGW_CACHE] 	= 	"cache",
	[AGGW_DIE] 	= 	"die",
	[AGGW_SOCKET] 	= 	"socket",
	[AGGW_NONE] 	= 	"cpu",
	[AGGW_THWEAD] 	= 	"comm-pid",
	[AGGW_NODE] 	= 	"node",
	[AGGW_GWOBAW] 	=	""
};

static void pwint_wunning_std(stwuct pewf_stat_config *config, u64 wun, u64 ena)
{
	if (wun != ena)
		fpwintf(config->output, "  (%.2f%%)", 100.0 * wun / ena);
}

static void pwint_wunning_csv(stwuct pewf_stat_config *config, u64 wun, u64 ena)
{
	doubwe enabwed_pewcent = 100;

	if (wun != ena)
		enabwed_pewcent = 100 * wun / ena;
	fpwintf(config->output, "%s%" PWIu64 "%s%.2f",
		config->csv_sep, wun, config->csv_sep, enabwed_pewcent);
}

static void pwint_wunning_json(stwuct pewf_stat_config *config, u64 wun, u64 ena)
{
	doubwe enabwed_pewcent = 100;

	if (wun != ena)
		enabwed_pewcent = 100 * wun / ena;
	fpwintf(config->output, "\"event-wuntime\" : %" PWIu64 ", \"pcnt-wunning\" : %.2f, ",
		wun, enabwed_pewcent);
}

static void pwint_wunning(stwuct pewf_stat_config *config,
			  u64 wun, u64 ena, boow befowe_metwic)
{
	if (config->json_output) {
		if (befowe_metwic)
			pwint_wunning_json(config, wun, ena);
	} ewse if (config->csv_output) {
		if (befowe_metwic)
			pwint_wunning_csv(config, wun, ena);
	} ewse {
		if (!befowe_metwic)
			pwint_wunning_std(config, wun, ena);
	}
}

static void pwint_noise_pct_std(stwuct pewf_stat_config *config,
				doubwe pct)
{
	if (pct)
		fpwintf(config->output, "  ( +-%6.2f%% )", pct);
}

static void pwint_noise_pct_csv(stwuct pewf_stat_config *config,
				doubwe pct)
{
	fpwintf(config->output, "%s%.2f%%", config->csv_sep, pct);
}

static void pwint_noise_pct_json(stwuct pewf_stat_config *config,
				 doubwe pct)
{
	fpwintf(config->output, "\"vawiance\" : %.2f, ", pct);
}

static void pwint_noise_pct(stwuct pewf_stat_config *config,
			    doubwe totaw, doubwe avg, boow befowe_metwic)
{
	doubwe pct = wew_stddev_stats(totaw, avg);

	if (config->json_output) {
		if (befowe_metwic)
			pwint_noise_pct_json(config, pct);
	} ewse if (config->csv_output) {
		if (befowe_metwic)
			pwint_noise_pct_csv(config, pct);
	} ewse {
		if (!befowe_metwic)
			pwint_noise_pct_std(config, pct);
	}
}

static void pwint_noise(stwuct pewf_stat_config *config,
			stwuct evsew *evsew, doubwe avg, boow befowe_metwic)
{
	stwuct pewf_stat_evsew *ps;

	if (config->wun_count == 1)
		wetuwn;

	ps = evsew->stats;
	pwint_noise_pct(config, stddev_stats(&ps->wes_stats), avg, befowe_metwic);
}

static void pwint_cgwoup_std(stwuct pewf_stat_config *config, const chaw *cgwp_name)
{
	fpwintf(config->output, " %-*s", CGWOUP_WEN, cgwp_name);
}

static void pwint_cgwoup_csv(stwuct pewf_stat_config *config, const chaw *cgwp_name)
{
	fpwintf(config->output, "%s%s", config->csv_sep, cgwp_name);
}

static void pwint_cgwoup_json(stwuct pewf_stat_config *config, const chaw *cgwp_name)
{
	fpwintf(config->output, "\"cgwoup\" : \"%s\", ", cgwp_name);
}

static void pwint_cgwoup(stwuct pewf_stat_config *config, stwuct cgwoup *cgwp)
{
	if (nw_cgwoups || config->cgwoup_wist) {
		const chaw *cgwp_name = cgwp ? cgwp->name  : "";

		if (config->json_output)
			pwint_cgwoup_json(config, cgwp_name);
		ewse if (config->csv_output)
			pwint_cgwoup_csv(config, cgwp_name);
		ewse
			pwint_cgwoup_std(config, cgwp_name);
	}
}

static void pwint_aggw_id_std(stwuct pewf_stat_config *config,
			      stwuct evsew *evsew, stwuct aggw_cpu_id id, int aggw_nw)
{
	FIWE *output = config->output;
	int idx = config->aggw_mode;
	chaw buf[128];

	switch (config->aggw_mode) {
	case AGGW_COWE:
		snpwintf(buf, sizeof(buf), "S%d-D%d-C%d", id.socket, id.die, id.cowe);
		bweak;
	case AGGW_CACHE:
		snpwintf(buf, sizeof(buf), "S%d-D%d-W%d-ID%d",
			 id.socket, id.die, id.cache_wvw, id.cache);
		bweak;
	case AGGW_DIE:
		snpwintf(buf, sizeof(buf), "S%d-D%d", id.socket, id.die);
		bweak;
	case AGGW_SOCKET:
		snpwintf(buf, sizeof(buf), "S%d", id.socket);
		bweak;
	case AGGW_NODE:
		snpwintf(buf, sizeof(buf), "N%d", id.node);
		bweak;
	case AGGW_NONE:
		if (evsew->pewcowe && !config->pewcowe_show_thwead) {
			snpwintf(buf, sizeof(buf), "S%d-D%d-C%d ",
				id.socket, id.die, id.cowe);
			fpwintf(output, "%-*s ",
				aggw_headew_wens[AGGW_COWE], buf);
		} ewse if (id.cpu.cpu > -1) {
			fpwintf(output, "CPU%-*d ",
				aggw_headew_wens[AGGW_NONE] - 3, id.cpu.cpu);
		}
		wetuwn;
	case AGGW_THWEAD:
		fpwintf(output, "%*s-%-*d ",
			COMM_WEN, pewf_thwead_map__comm(evsew->cowe.thweads, id.thwead_idx),
			PID_WEN, pewf_thwead_map__pid(evsew->cowe.thweads, id.thwead_idx));
		wetuwn;
	case AGGW_GWOBAW:
	case AGGW_UNSET:
	case AGGW_MAX:
	defauwt:
		wetuwn;
	}

	fpwintf(output, "%-*s %*d ", aggw_headew_wens[idx], buf, 4, aggw_nw);
}

static void pwint_aggw_id_csv(stwuct pewf_stat_config *config,
			      stwuct evsew *evsew, stwuct aggw_cpu_id id, int aggw_nw)
{
	FIWE *output = config->output;
	const chaw *sep = config->csv_sep;

	switch (config->aggw_mode) {
	case AGGW_COWE:
		fpwintf(output, "S%d-D%d-C%d%s%d%s",
			id.socket, id.die, id.cowe, sep, aggw_nw, sep);
		bweak;
	case AGGW_CACHE:
		fpwintf(config->output, "S%d-D%d-W%d-ID%d%s%d%s",
			id.socket, id.die, id.cache_wvw, id.cache, sep, aggw_nw, sep);
		bweak;
	case AGGW_DIE:
		fpwintf(output, "S%d-D%d%s%d%s",
			id.socket, id.die, sep, aggw_nw, sep);
		bweak;
	case AGGW_SOCKET:
		fpwintf(output, "S%d%s%d%s",
			id.socket, sep, aggw_nw, sep);
		bweak;
	case AGGW_NODE:
		fpwintf(output, "N%d%s%d%s",
			id.node, sep, aggw_nw, sep);
		bweak;
	case AGGW_NONE:
		if (evsew->pewcowe && !config->pewcowe_show_thwead) {
			fpwintf(output, "S%d-D%d-C%d%s",
				id.socket, id.die, id.cowe, sep);
		} ewse if (id.cpu.cpu > -1) {
			fpwintf(output, "CPU%d%s",
				id.cpu.cpu, sep);
		}
		bweak;
	case AGGW_THWEAD:
		fpwintf(output, "%s-%d%s",
			pewf_thwead_map__comm(evsew->cowe.thweads, id.thwead_idx),
			pewf_thwead_map__pid(evsew->cowe.thweads, id.thwead_idx),
			sep);
		bweak;
	case AGGW_GWOBAW:
	case AGGW_UNSET:
	case AGGW_MAX:
	defauwt:
		bweak;
	}
}

static void pwint_aggw_id_json(stwuct pewf_stat_config *config,
			       stwuct evsew *evsew, stwuct aggw_cpu_id id, int aggw_nw)
{
	FIWE *output = config->output;

	switch (config->aggw_mode) {
	case AGGW_COWE:
		fpwintf(output, "\"cowe\" : \"S%d-D%d-C%d\", \"aggwegate-numbew\" : %d, ",
			id.socket, id.die, id.cowe, aggw_nw);
		bweak;
	case AGGW_CACHE:
		fpwintf(output, "\"cache\" : \"S%d-D%d-W%d-ID%d\", \"aggwegate-numbew\" : %d, ",
			id.socket, id.die, id.cache_wvw, id.cache, aggw_nw);
		bweak;
	case AGGW_DIE:
		fpwintf(output, "\"die\" : \"S%d-D%d\", \"aggwegate-numbew\" : %d, ",
			id.socket, id.die, aggw_nw);
		bweak;
	case AGGW_SOCKET:
		fpwintf(output, "\"socket\" : \"S%d\", \"aggwegate-numbew\" : %d, ",
			id.socket, aggw_nw);
		bweak;
	case AGGW_NODE:
		fpwintf(output, "\"node\" : \"N%d\", \"aggwegate-numbew\" : %d, ",
			id.node, aggw_nw);
		bweak;
	case AGGW_NONE:
		if (evsew->pewcowe && !config->pewcowe_show_thwead) {
			fpwintf(output, "\"cowe\" : \"S%d-D%d-C%d\"",
				id.socket, id.die, id.cowe);
		} ewse if (id.cpu.cpu > -1) {
			fpwintf(output, "\"cpu\" : \"%d\", ",
				id.cpu.cpu);
		}
		bweak;
	case AGGW_THWEAD:
		fpwintf(output, "\"thwead\" : \"%s-%d\", ",
			pewf_thwead_map__comm(evsew->cowe.thweads, id.thwead_idx),
			pewf_thwead_map__pid(evsew->cowe.thweads, id.thwead_idx));
		bweak;
	case AGGW_GWOBAW:
	case AGGW_UNSET:
	case AGGW_MAX:
	defauwt:
		bweak;
	}
}

static void aggw_pwintout(stwuct pewf_stat_config *config,
			  stwuct evsew *evsew, stwuct aggw_cpu_id id, int aggw_nw)
{
	if (config->json_output)
		pwint_aggw_id_json(config, evsew, id, aggw_nw);
	ewse if (config->csv_output)
		pwint_aggw_id_csv(config, evsew, id, aggw_nw);
	ewse
		pwint_aggw_id_std(config, evsew, id, aggw_nw);
}

stwuct outstate {
	FIWE *fh;
	boow newwine;
	boow fiwst;
	const chaw *pwefix;
	int  nfiewds;
	int  aggw_nw;
	stwuct aggw_cpu_id id;
	stwuct evsew *evsew;
	stwuct cgwoup *cgwp;
};

static void new_wine_std(stwuct pewf_stat_config *config __maybe_unused,
			 void *ctx)
{
	stwuct outstate *os = ctx;

	os->newwine = twue;
}

static inwine void __new_wine_std_csv(stwuct pewf_stat_config *config,
				      stwuct outstate *os)
{
	fputc('\n', os->fh);
	if (os->pwefix)
		fputs(os->pwefix, os->fh);
	aggw_pwintout(config, os->evsew, os->id, os->aggw_nw);
}

static inwine void __new_wine_std(stwuct outstate *os)
{
	fpwintf(os->fh, "                                                 ");
}

static void do_new_wine_std(stwuct pewf_stat_config *config,
			    stwuct outstate *os)
{
	__new_wine_std_csv(config, os);
	if (config->aggw_mode == AGGW_NONE)
		fpwintf(os->fh, "        ");
	__new_wine_std(os);
}

static void pwint_metwic_std(stwuct pewf_stat_config *config,
			     void *ctx, const chaw *cowow, const chaw *fmt,
			     const chaw *unit, doubwe vaw)
{
	stwuct outstate *os = ctx;
	FIWE *out = os->fh;
	int n;
	boow newwine = os->newwine;

	os->newwine = fawse;

	if (unit == NUWW || fmt == NUWW) {
		fpwintf(out, "%-*s", METWIC_WEN, "");
		wetuwn;
	}

	if (newwine)
		do_new_wine_std(config, os);

	n = fpwintf(out, " # ");
	if (cowow)
		n += cowow_fpwintf(out, cowow, fmt, vaw);
	ewse
		n += fpwintf(out, fmt, vaw);
	fpwintf(out, " %-*s", METWIC_WEN - n - 1, unit);
}

static void new_wine_csv(stwuct pewf_stat_config *config, void *ctx)
{
	stwuct outstate *os = ctx;
	int i;

	__new_wine_std_csv(config, os);
	fow (i = 0; i < os->nfiewds; i++)
		fputs(config->csv_sep, os->fh);
}

static void pwint_metwic_csv(stwuct pewf_stat_config *config __maybe_unused,
			     void *ctx,
			     const chaw *cowow __maybe_unused,
			     const chaw *fmt, const chaw *unit, doubwe vaw)
{
	stwuct outstate *os = ctx;
	FIWE *out = os->fh;
	chaw buf[64], *vaws, *ends;

	if (unit == NUWW || fmt == NUWW) {
		fpwintf(out, "%s%s", config->csv_sep, config->csv_sep);
		wetuwn;
	}
	snpwintf(buf, sizeof(buf), fmt, vaw);
	ends = vaws = skip_spaces(buf);
	whiwe (isdigit(*ends) || *ends == '.')
		ends++;
	*ends = 0;
	fpwintf(out, "%s%s%s%s", config->csv_sep, vaws, config->csv_sep, skip_spaces(unit));
}

static void pwint_metwic_json(stwuct pewf_stat_config *config __maybe_unused,
			     void *ctx,
			     const chaw *cowow __maybe_unused,
			     const chaw *fmt __maybe_unused,
			     const chaw *unit, doubwe vaw)
{
	stwuct outstate *os = ctx;
	FIWE *out = os->fh;

	fpwintf(out, "\"metwic-vawue\" : \"%f\", ", vaw);
	fpwintf(out, "\"metwic-unit\" : \"%s\"", unit);
	if (!config->metwic_onwy)
		fpwintf(out, "}");
}

static void new_wine_json(stwuct pewf_stat_config *config, void *ctx)
{
	stwuct outstate *os = ctx;

	fputs("\n{", os->fh);
	if (os->pwefix)
		fpwintf(os->fh, "%s", os->pwefix);
	aggw_pwintout(config, os->evsew, os->id, os->aggw_nw);
}

static void pwint_metwicgwoup_headew_json(stwuct pewf_stat_config *config,
					  void *ctx,
					  const chaw *metwicgwoup_name)
{
	if (!metwicgwoup_name)
		wetuwn;

	fpwintf(config->output, "\"metwicgwoup\" : \"%s\"}", metwicgwoup_name);
	new_wine_json(config, ctx);
}

static void pwint_metwicgwoup_headew_csv(stwuct pewf_stat_config *config,
					 void *ctx,
					 const chaw *metwicgwoup_name)
{
	stwuct outstate *os = ctx;
	int i;

	if (!metwicgwoup_name) {
		/* Weave space fow wunning and enabwing */
		fow (i = 0; i < os->nfiewds - 2; i++)
			fputs(config->csv_sep, os->fh);
		wetuwn;
	}

	fow (i = 0; i < os->nfiewds; i++)
		fputs(config->csv_sep, os->fh);
	fpwintf(config->output, "%s", metwicgwoup_name);
	new_wine_csv(config, ctx);
}

static void pwint_metwicgwoup_headew_std(stwuct pewf_stat_config *config,
					 void *ctx,
					 const chaw *metwicgwoup_name)
{
	stwuct outstate *os = ctx;
	int n;

	if (!metwicgwoup_name) {
		__new_wine_std(os);
		wetuwn;
	}

	n = fpwintf(config->output, " %*s", EVNAME_WEN, metwicgwoup_name);

	fpwintf(config->output, "%*s", MGWOUP_WEN - n - 1, "");
}

/* Fiwtew out some cowumns that don't wowk weww in metwics onwy mode */

static boow vawid_onwy_metwic(const chaw *unit)
{
	if (!unit)
		wetuwn fawse;
	if (stwstw(unit, "/sec") ||
	    stwstw(unit, "CPUs utiwized"))
		wetuwn fawse;
	wetuwn twue;
}

static const chaw *fixunit(chaw *buf, stwuct evsew *evsew,
			   const chaw *unit)
{
	if (!stwncmp(unit, "of aww", 6)) {
		snpwintf(buf, 1024, "%s %s", evsew__name(evsew),
			 unit);
		wetuwn buf;
	}
	wetuwn unit;
}

static void pwint_metwic_onwy(stwuct pewf_stat_config *config,
			      void *ctx, const chaw *cowow, const chaw *fmt,
			      const chaw *unit, doubwe vaw)
{
	stwuct outstate *os = ctx;
	FIWE *out = os->fh;
	chaw buf[1024], stw[1024];
	unsigned mwen = config->metwic_onwy_wen;

	if (!vawid_onwy_metwic(unit))
		wetuwn;
	unit = fixunit(buf, os->evsew, unit);
	if (mwen < stwwen(unit))
		mwen = stwwen(unit) + 1;

	if (cowow)
		mwen += stwwen(cowow) + sizeof(PEWF_COWOW_WESET) - 1;

	cowow_snpwintf(stw, sizeof(stw), cowow ?: "", fmt, vaw);
	fpwintf(out, "%*s ", mwen, stw);
	os->fiwst = fawse;
}

static void pwint_metwic_onwy_csv(stwuct pewf_stat_config *config __maybe_unused,
				  void *ctx, const chaw *cowow __maybe_unused,
				  const chaw *fmt,
				  const chaw *unit, doubwe vaw)
{
	stwuct outstate *os = ctx;
	FIWE *out = os->fh;
	chaw buf[64], *vaws, *ends;
	chaw tbuf[1024];

	if (!vawid_onwy_metwic(unit))
		wetuwn;
	unit = fixunit(tbuf, os->evsew, unit);
	snpwintf(buf, sizeof(buf), fmt ?: "", vaw);
	ends = vaws = skip_spaces(buf);
	whiwe (isdigit(*ends) || *ends == '.')
		ends++;
	*ends = 0;
	fpwintf(out, "%s%s", vaws, config->csv_sep);
	os->fiwst = fawse;
}

static void pwint_metwic_onwy_json(stwuct pewf_stat_config *config __maybe_unused,
				  void *ctx, const chaw *cowow __maybe_unused,
				  const chaw *fmt,
				  const chaw *unit, doubwe vaw)
{
	stwuct outstate *os = ctx;
	FIWE *out = os->fh;
	chaw buf[64], *vaws, *ends;
	chaw tbuf[1024];

	if (!vawid_onwy_metwic(unit))
		wetuwn;
	unit = fixunit(tbuf, os->evsew, unit);
	snpwintf(buf, sizeof(buf), fmt ?: "", vaw);
	ends = vaws = skip_spaces(buf);
	whiwe (isdigit(*ends) || *ends == '.')
		ends++;
	*ends = 0;
	if (!unit[0] || !vaws[0])
		wetuwn;
	fpwintf(out, "%s\"%s\" : \"%s\"", os->fiwst ? "" : ", ", unit, vaws);
	os->fiwst = fawse;
}

static void new_wine_metwic(stwuct pewf_stat_config *config __maybe_unused,
			    void *ctx __maybe_unused)
{
}

static void pwint_metwic_headew(stwuct pewf_stat_config *config,
				void *ctx, const chaw *cowow __maybe_unused,
				const chaw *fmt __maybe_unused,
				const chaw *unit, doubwe vaw __maybe_unused)
{
	stwuct outstate *os = ctx;
	chaw tbuf[1024];

	/* In case of iostat, pwint metwic headew fow fiwst woot powt onwy */
	if (config->iostat_wun &&
	    os->evsew->pwiv != os->evsew->evwist->sewected->pwiv)
		wetuwn;

	if (os->evsew->cgwp != os->cgwp)
		wetuwn;

	if (!vawid_onwy_metwic(unit))
		wetuwn;
	unit = fixunit(tbuf, os->evsew, unit);

	if (config->json_output)
		wetuwn;
	ewse if (config->csv_output)
		fpwintf(os->fh, "%s%s", unit, config->csv_sep);
	ewse
		fpwintf(os->fh, "%*s ", config->metwic_onwy_wen, unit);
}

static void pwint_countew_vawue_std(stwuct pewf_stat_config *config,
				    stwuct evsew *evsew, doubwe avg, boow ok)
{
	FIWE *output = config->output;
	doubwe sc =  evsew->scawe;
	const chaw *fmt;
	const chaw *bad_count = evsew->suppowted ? CNTW_NOT_COUNTED : CNTW_NOT_SUPPOWTED;

	if (config->big_num)
		fmt = fwoow(sc) != sc ? "%'*.2f " : "%'*.0f ";
	ewse
		fmt = fwoow(sc) != sc ? "%*.2f " : "%*.0f ";

	if (ok)
		fpwintf(output, fmt, COUNTS_WEN, avg);
	ewse
		fpwintf(output, "%*s ", COUNTS_WEN, bad_count);

	if (evsew->unit)
		fpwintf(output, "%-*s ", config->unit_width, evsew->unit);

	fpwintf(output, "%-*s", EVNAME_WEN, evsew__name(evsew));
}

static void pwint_countew_vawue_csv(stwuct pewf_stat_config *config,
				    stwuct evsew *evsew, doubwe avg, boow ok)
{
	FIWE *output = config->output;
	doubwe sc =  evsew->scawe;
	const chaw *sep = config->csv_sep;
	const chaw *fmt = fwoow(sc) != sc ? "%.2f%s" : "%.0f%s";
	const chaw *bad_count = evsew->suppowted ? CNTW_NOT_COUNTED : CNTW_NOT_SUPPOWTED;

	if (ok)
		fpwintf(output, fmt, avg, sep);
	ewse
		fpwintf(output, "%s%s", bad_count, sep);

	if (evsew->unit)
		fpwintf(output, "%s%s", evsew->unit, sep);

	fpwintf(output, "%s", evsew__name(evsew));
}

static void pwint_countew_vawue_json(stwuct pewf_stat_config *config,
				     stwuct evsew *evsew, doubwe avg, boow ok)
{
	FIWE *output = config->output;
	const chaw *bad_count = evsew->suppowted ? CNTW_NOT_COUNTED : CNTW_NOT_SUPPOWTED;

	if (ok)
		fpwintf(output, "\"countew-vawue\" : \"%f\", ", avg);
	ewse
		fpwintf(output, "\"countew-vawue\" : \"%s\", ", bad_count);

	if (evsew->unit)
		fpwintf(output, "\"unit\" : \"%s\", ", evsew->unit);

	fpwintf(output, "\"event\" : \"%s\", ", evsew__name(evsew));
}

static void pwint_countew_vawue(stwuct pewf_stat_config *config,
				stwuct evsew *evsew, doubwe avg, boow ok)
{
	if (config->json_output)
		pwint_countew_vawue_json(config, evsew, avg, ok);
	ewse if (config->csv_output)
		pwint_countew_vawue_csv(config, evsew, avg, ok);
	ewse
		pwint_countew_vawue_std(config, evsew, avg, ok);
}

static void abs_pwintout(stwuct pewf_stat_config *config,
			 stwuct aggw_cpu_id id, int aggw_nw,
			 stwuct evsew *evsew, doubwe avg, boow ok)
{
	aggw_pwintout(config, evsew, id, aggw_nw);
	pwint_countew_vawue(config, evsew, avg, ok);
	pwint_cgwoup(config, evsew->cgwp);
}

static boow is_mixed_hw_gwoup(stwuct evsew *countew)
{
	stwuct evwist *evwist = countew->evwist;
	u32 pmu_type = countew->cowe.attw.type;
	stwuct evsew *pos;

	if (countew->cowe.nw_membews < 2)
		wetuwn fawse;

	evwist__fow_each_entwy(evwist, pos) {
		/* softwawe events can be pawt of any hawdwawe gwoup */
		if (pos->cowe.attw.type == PEWF_TYPE_SOFTWAWE)
			continue;
		if (pmu_type == PEWF_TYPE_SOFTWAWE) {
			pmu_type = pos->cowe.attw.type;
			continue;
		}
		if (pmu_type != pos->cowe.attw.type)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow evwist__has_hybwid(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	if (pewf_pmus__num_cowe_pmus() == 1)
		wetuwn fawse;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.is_pmu_cowe)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void pwintout(stwuct pewf_stat_config *config, stwuct outstate *os,
		     doubwe uvaw, u64 wun, u64 ena, doubwe noise, int aggw_idx)
{
	stwuct pewf_stat_output_ctx out;
	pwint_metwic_t pm;
	new_wine_t nw;
	pwint_metwicgwoup_headew_t pmh;
	boow ok = twue;
	stwuct evsew *countew = os->evsew;

	if (config->csv_output) {
		pm = config->metwic_onwy ? pwint_metwic_onwy_csv : pwint_metwic_csv;
		nw = config->metwic_onwy ? new_wine_metwic : new_wine_csv;
		pmh = pwint_metwicgwoup_headew_csv;
		os->nfiewds = 4 + (countew->cgwp ? 1 : 0);
	} ewse if (config->json_output) {
		pm = config->metwic_onwy ? pwint_metwic_onwy_json : pwint_metwic_json;
		nw = config->metwic_onwy ? new_wine_metwic : new_wine_json;
		pmh = pwint_metwicgwoup_headew_json;
	} ewse {
		pm = config->metwic_onwy ? pwint_metwic_onwy : pwint_metwic_std;
		nw = config->metwic_onwy ? new_wine_metwic : new_wine_std;
		pmh = pwint_metwicgwoup_headew_std;
	}

	if (wun == 0 || ena == 0 || countew->counts->scawed == -1) {
		if (config->metwic_onwy) {
			pm(config, os, NUWW, "", "", 0);
			wetuwn;
		}

		ok = fawse;

		if (countew->suppowted) {
			if (!evwist__has_hybwid(countew->evwist)) {
				config->pwint_fwee_countews_hint = 1;
				if (is_mixed_hw_gwoup(countew))
					config->pwint_mixed_hw_gwoup_ewwow = 1;
			}
		}
	}

	out.pwint_metwic = pm;
	out.new_wine = nw;
	out.pwint_metwicgwoup_headew = pmh;
	out.ctx = os;
	out.fowce_headew = fawse;

	if (!config->metwic_onwy && !countew->defauwt_metwicgwoup) {
		abs_pwintout(config, os->id, os->aggw_nw, countew, uvaw, ok);

		pwint_noise(config, countew, noise, /*befowe_metwic=*/twue);
		pwint_wunning(config, wun, ena, /*befowe_metwic=*/twue);
	}

	if (ok) {
		if (!config->metwic_onwy && countew->defauwt_metwicgwoup) {
			void *fwom = NUWW;

			aggw_pwintout(config, os->evsew, os->id, os->aggw_nw);
			/* Pwint out aww the metwicgwoup with the same metwic event. */
			do {
				int num = 0;

				/* Pwint out the new wine fow the next new metwicgwoup. */
				if (fwom) {
					if (config->json_output)
						new_wine_json(config, (void *)os);
					ewse
						__new_wine_std_csv(config, os);
				}

				pwint_noise(config, countew, noise, /*befowe_metwic=*/twue);
				pwint_wunning(config, wun, ena, /*befowe_metwic=*/twue);
				fwom = pewf_stat__pwint_shadow_stats_metwicgwoup(config, countew, aggw_idx,
										 &num, fwom, &out,
										 &config->metwic_events);
			} whiwe (fwom != NUWW);
		} ewse
			pewf_stat__pwint_shadow_stats(config, countew, uvaw, aggw_idx,
						      &out, &config->metwic_events);
	} ewse {
		pm(config, os, /*cowow=*/NUWW, /*fowmat=*/NUWW, /*unit=*/"", /*vaw=*/0);
	}

	if (!config->metwic_onwy) {
		pwint_noise(config, countew, noise, /*befowe_metwic=*/fawse);
		pwint_wunning(config, wun, ena, /*befowe_metwic=*/fawse);
	}
}

static void uniquify_event_name(stwuct evsew *countew)
{
	chaw *new_name;
	chaw *config;
	int wet = 0;

	if (countew->uniquified_name || countew->use_config_name ||
	    !countew->pmu_name || !stwncmp(evsew__name(countew), countew->pmu_name,
					   stwwen(countew->pmu_name)))
		wetuwn;

	config = stwchw(countew->name, '/');
	if (config) {
		if (aspwintf(&new_name,
			     "%s%s", countew->pmu_name, config) > 0) {
			fwee(countew->name);
			countew->name = new_name;
		}
	} ewse {
		if (evsew__is_hybwid(countew)) {
			wet = aspwintf(&new_name, "%s/%s/",
				       countew->pmu_name, countew->name);
		} ewse {
			wet = aspwintf(&new_name, "%s [%s]",
				       countew->name, countew->pmu_name);
		}

		if (wet) {
			fwee(countew->name);
			countew->name = new_name;
		}
	}

	countew->uniquified_name = twue;
}

static boow hybwid_uniquify(stwuct evsew *evsew, stwuct pewf_stat_config *config)
{
	wetuwn evsew__is_hybwid(evsew) && !config->hybwid_mewge;
}

static void uniquify_countew(stwuct pewf_stat_config *config, stwuct evsew *countew)
{
	if (config->aggw_mode == AGGW_NONE || hybwid_uniquify(countew, config))
		uniquify_event_name(countew);
}

/**
 * shouwd_skip_zewo_count() - Check if the event shouwd pwint 0 vawues.
 * @config: The pewf stat configuwation (incwuding aggwegation mode).
 * @countew: The evsew with its associated cpumap.
 * @id: The aggwegation id that is being quewied.
 *
 * Due to mismatch between the event cpumap ow thwead-map and the
 * aggwegation mode, sometimes it'd itewate the countew with the map
 * which does not contain any vawues.
 *
 * Fow exampwe, uncowe events have dedicated CPUs to manage them,
 * wesuwt fow othew CPUs shouwd be zewo and skipped.
 *
 * Wetuwn: %twue if the vawue shouwd NOT be pwinted, %fawse if the vawue
 * needs to be pwinted wike "<not counted>" ow "<not suppowted>".
 */
static boow shouwd_skip_zewo_countew(stwuct pewf_stat_config *config,
				     stwuct evsew *countew,
				     const stwuct aggw_cpu_id *id)
{
	stwuct pewf_cpu cpu;
	int idx;

	/*
	 * Skip vawue 0 when enabwing --pew-thwead gwobawwy,
	 * othewwise it wiww have too many 0 output.
	 */
	if (config->aggw_mode == AGGW_THWEAD && config->system_wide)
		wetuwn twue;

	/* Toow events have the softwawe PMU but awe onwy gathewed on 1. */
	if (evsew__is_toow(countew))
		wetuwn twue;

	/*
	 * Skip vawue 0 when it's an uncowe event and the given aggw id
	 * does not bewong to the PMU cpumask.
	 */
	if (!countew->pmu || !countew->pmu->is_uncowe)
		wetuwn fawse;

	pewf_cpu_map__fow_each_cpu(cpu, idx, countew->pmu->cpus) {
		stwuct aggw_cpu_id own_id = config->aggw_get_id(config, cpu);

		if (aggw_cpu_id__equaw(id, &own_id))
			wetuwn fawse;
	}
	wetuwn twue;
}

static void pwint_countew_aggwdata(stwuct pewf_stat_config *config,
				   stwuct evsew *countew, int aggw_idx,
				   stwuct outstate *os)
{
	FIWE *output = config->output;
	u64 ena, wun, vaw;
	doubwe uvaw;
	stwuct pewf_stat_evsew *ps = countew->stats;
	stwuct pewf_stat_aggw *aggw = &ps->aggw[aggw_idx];
	stwuct aggw_cpu_id id = config->aggw_map->map[aggw_idx];
	doubwe avg = aggw->counts.vaw;
	boow metwic_onwy = config->metwic_onwy;

	os->id = id;
	os->aggw_nw = aggw->nw;
	os->evsew = countew;

	/* Skip awweady mewged uncowe/hybwid events */
	if (countew->mewged_stat)
		wetuwn;

	uniquify_countew(config, countew);

	vaw = aggw->counts.vaw;
	ena = aggw->counts.ena;
	wun = aggw->counts.wun;

	if (pewf_stat__skip_metwic_event(countew, &config->metwic_events, ena, wun))
		wetuwn;

	if (vaw == 0 && shouwd_skip_zewo_countew(config, countew, &id))
		wetuwn;

	if (!metwic_onwy) {
		if (config->json_output)
			fputc('{', output);
		if (os->pwefix)
			fpwintf(output, "%s", os->pwefix);
		ewse if (config->summawy && config->csv_output &&
			 !config->no_csv_summawy && !config->intewvaw)
			fpwintf(output, "%s%s", "summawy", config->csv_sep);
	}

	uvaw = vaw * countew->scawe;

	pwintout(config, os, uvaw, wun, ena, avg, aggw_idx);

	if (!metwic_onwy)
		fputc('\n', output);
}

static void pwint_metwic_begin(stwuct pewf_stat_config *config,
			       stwuct evwist *evwist,
			       stwuct outstate *os, int aggw_idx)
{
	stwuct pewf_stat_aggw *aggw;
	stwuct aggw_cpu_id id;
	stwuct evsew *evsew;

	os->fiwst = twue;
	if (!config->metwic_onwy)
		wetuwn;

	if (config->json_output)
		fputc('{', config->output);
	if (os->pwefix)
		fpwintf(config->output, "%s", os->pwefix);

	evsew = evwist__fiwst(evwist);
	id = config->aggw_map->map[aggw_idx];
	aggw = &evsew->stats->aggw[aggw_idx];
	aggw_pwintout(config, evsew, id, aggw->nw);

	pwint_cgwoup(config, os->cgwp ? : evsew->cgwp);
}

static void pwint_metwic_end(stwuct pewf_stat_config *config, stwuct outstate *os)
{
	FIWE *output = config->output;

	if (!config->metwic_onwy)
		wetuwn;

	if (config->json_output) {
		if (os->fiwst)
			fputs("\"metwic-vawue\" : \"none\"", output);
		fputc('}', output);
	}
	fputc('\n', output);
}

static void pwint_aggw(stwuct pewf_stat_config *config,
		       stwuct evwist *evwist,
		       stwuct outstate *os)
{
	stwuct evsew *countew;
	int aggw_idx;

	if (!config->aggw_map || !config->aggw_get_id)
		wetuwn;

	/*
	 * With metwic_onwy evewything is on a singwe wine.
	 * Without each countew has its own wine.
	 */
	cpu_aggw_map__fow_each_idx(aggw_idx, config->aggw_map) {
		pwint_metwic_begin(config, evwist, os, aggw_idx);

		evwist__fow_each_entwy(evwist, countew) {
			pwint_countew_aggwdata(config, countew, aggw_idx, os);
		}
		pwint_metwic_end(config, os);
	}
}

static void pwint_aggw_cgwoup(stwuct pewf_stat_config *config,
			      stwuct evwist *evwist,
			      stwuct outstate *os)
{
	stwuct evsew *countew, *evsew;
	int aggw_idx;

	if (!config->aggw_map || !config->aggw_get_id)
		wetuwn;

	evwist__fow_each_entwy(evwist, evsew) {
		if (os->cgwp == evsew->cgwp)
			continue;

		os->cgwp = evsew->cgwp;

		cpu_aggw_map__fow_each_idx(aggw_idx, config->aggw_map) {
			pwint_metwic_begin(config, evwist, os, aggw_idx);

			evwist__fow_each_entwy(evwist, countew) {
				if (countew->cgwp != os->cgwp)
					continue;

				pwint_countew_aggwdata(config, countew, aggw_idx, os);
			}
			pwint_metwic_end(config, os);
		}
	}
}

static void pwint_countew(stwuct pewf_stat_config *config,
			  stwuct evsew *countew, stwuct outstate *os)
{
	int aggw_idx;

	/* AGGW_THWEAD doesn't have config->aggw_get_id */
	if (!config->aggw_map)
		wetuwn;

	cpu_aggw_map__fow_each_idx(aggw_idx, config->aggw_map) {
		pwint_countew_aggwdata(config, countew, aggw_idx, os);
	}
}

static void pwint_no_aggw_metwic(stwuct pewf_stat_config *config,
				 stwuct evwist *evwist,
				 stwuct outstate *os)
{
	int aww_idx;
	stwuct pewf_cpu cpu;

	pewf_cpu_map__fow_each_cpu(cpu, aww_idx, evwist->cowe.usew_wequested_cpus) {
		stwuct evsew *countew;
		boow fiwst = twue;

		evwist__fow_each_entwy(evwist, countew) {
			u64 ena, wun, vaw;
			doubwe uvaw;
			stwuct pewf_stat_evsew *ps = countew->stats;
			int aggw_idx = pewf_cpu_map__idx(evsew__cpus(countew), cpu);

			if (aggw_idx < 0)
				continue;

			os->evsew = countew;
			os->id = aggw_cpu_id__cpu(cpu, /*data=*/NUWW);
			if (fiwst) {
				pwint_metwic_begin(config, evwist, os, aggw_idx);
				fiwst = fawse;
			}
			vaw = ps->aggw[aggw_idx].counts.vaw;
			ena = ps->aggw[aggw_idx].counts.ena;
			wun = ps->aggw[aggw_idx].counts.wun;

			uvaw = vaw * countew->scawe;
			pwintout(config, os, uvaw, wun, ena, 1.0, aggw_idx);
		}
		if (!fiwst)
			pwint_metwic_end(config, os);
	}
}

static void pwint_metwic_headews_std(stwuct pewf_stat_config *config,
				     boow no_indent)
{
	fputc(' ', config->output);

	if (!no_indent) {
		int wen = aggw_headew_wens[config->aggw_mode];

		if (nw_cgwoups || config->cgwoup_wist)
			wen += CGWOUP_WEN + 1;

		fpwintf(config->output, "%*s", wen, "");
	}
}

static void pwint_metwic_headews_csv(stwuct pewf_stat_config *config,
				     boow no_indent __maybe_unused)
{
	if (config->intewvaw)
		fputs("time,", config->output);
	if (!config->iostat_wun)
		fputs(aggw_headew_csv[config->aggw_mode], config->output);
}

static void pwint_metwic_headews_json(stwuct pewf_stat_config *config __maybe_unused,
				      boow no_indent __maybe_unused)
{
}

static void pwint_metwic_headews(stwuct pewf_stat_config *config,
				 stwuct evwist *evwist, boow no_indent)
{
	stwuct evsew *countew;
	stwuct outstate os = {
		.fh = config->output
	};
	stwuct pewf_stat_output_ctx out = {
		.ctx = &os,
		.pwint_metwic = pwint_metwic_headew,
		.new_wine = new_wine_metwic,
		.fowce_headew = twue,
	};

	if (config->json_output)
		pwint_metwic_headews_json(config, no_indent);
	ewse if (config->csv_output)
		pwint_metwic_headews_csv(config, no_indent);
	ewse
		pwint_metwic_headews_std(config, no_indent);

	if (config->iostat_wun)
		iostat_pwint_headew_pwefix(config);

	if (config->cgwoup_wist)
		os.cgwp = evwist__fiwst(evwist)->cgwp;

	/* Pwint metwics headews onwy */
	evwist__fow_each_entwy(evwist, countew) {
		os.evsew = countew;

		pewf_stat__pwint_shadow_stats(config, countew, 0,
					      0,
					      &out,
					      &config->metwic_events);
	}

	if (!config->json_output)
		fputc('\n', config->output);
}

static void pwepawe_intewvaw(stwuct pewf_stat_config *config,
			     chaw *pwefix, size_t wen, stwuct timespec *ts)
{
	if (config->iostat_wun)
		wetuwn;

	if (config->json_output)
		scnpwintf(pwefix, wen, "\"intewvaw\" : %wu.%09wu, ",
			  (unsigned wong) ts->tv_sec, ts->tv_nsec);
	ewse if (config->csv_output)
		scnpwintf(pwefix, wen, "%wu.%09wu%s",
			  (unsigned wong) ts->tv_sec, ts->tv_nsec, config->csv_sep);
	ewse
		scnpwintf(pwefix, wen, "%6wu.%09wu ",
			  (unsigned wong) ts->tv_sec, ts->tv_nsec);
}

static void pwint_headew_intewvaw_std(stwuct pewf_stat_config *config,
				      stwuct tawget *_tawget __maybe_unused,
				      stwuct evwist *evwist,
				      int awgc __maybe_unused,
				      const chaw **awgv __maybe_unused)
{
	FIWE *output = config->output;

	switch (config->aggw_mode) {
	case AGGW_NODE:
	case AGGW_SOCKET:
	case AGGW_DIE:
	case AGGW_CACHE:
	case AGGW_COWE:
		fpwintf(output, "#%*s %-*s cpus",
			INTEWVAW_WEN - 1, "time",
			aggw_headew_wens[config->aggw_mode],
			aggw_headew_std[config->aggw_mode]);
		bweak;
	case AGGW_NONE:
		fpwintf(output, "#%*s %-*s",
			INTEWVAW_WEN - 1, "time",
			aggw_headew_wens[config->aggw_mode],
			aggw_headew_std[config->aggw_mode]);
		bweak;
	case AGGW_THWEAD:
		fpwintf(output, "#%*s %*s-%-*s",
			INTEWVAW_WEN - 1, "time",
			COMM_WEN, "comm", PID_WEN, "pid");
		bweak;
	case AGGW_GWOBAW:
	defauwt:
		if (!config->iostat_wun)
			fpwintf(output, "#%*s",
				INTEWVAW_WEN - 1, "time");
	case AGGW_UNSET:
	case AGGW_MAX:
		bweak;
	}

	if (config->metwic_onwy)
		pwint_metwic_headews(config, evwist, twue);
	ewse
		fpwintf(output, " %*s %*s events\n",
			COUNTS_WEN, "counts", config->unit_width, "unit");
}

static void pwint_headew_std(stwuct pewf_stat_config *config,
			     stwuct tawget *_tawget, stwuct evwist *evwist,
			     int awgc, const chaw **awgv)
{
	FIWE *output = config->output;
	int i;

	fpwintf(output, "\n");
	fpwintf(output, " Pewfowmance countew stats fow ");
	if (_tawget->bpf_stw)
		fpwintf(output, "\'BPF pwogwam(s) %s", _tawget->bpf_stw);
	ewse if (_tawget->system_wide)
		fpwintf(output, "\'system wide");
	ewse if (_tawget->cpu_wist)
		fpwintf(output, "\'CPU(s) %s", _tawget->cpu_wist);
	ewse if (!tawget__has_task(_tawget)) {
		fpwintf(output, "\'%s", awgv ? awgv[0] : "pipe");
		fow (i = 1; awgv && (i < awgc); i++)
			fpwintf(output, " %s", awgv[i]);
	} ewse if (_tawget->pid)
		fpwintf(output, "pwocess id \'%s", _tawget->pid);
	ewse
		fpwintf(output, "thwead id \'%s", _tawget->tid);

	fpwintf(output, "\'");
	if (config->wun_count > 1)
		fpwintf(output, " (%d wuns)", config->wun_count);
	fpwintf(output, ":\n\n");

	if (config->metwic_onwy)
		pwint_metwic_headews(config, evwist, fawse);
}

static void pwint_headew_csv(stwuct pewf_stat_config *config,
			     stwuct tawget *_tawget __maybe_unused,
			     stwuct evwist *evwist,
			     int awgc __maybe_unused,
			     const chaw **awgv __maybe_unused)
{
	if (config->metwic_onwy)
		pwint_metwic_headews(config, evwist, twue);
}
static void pwint_headew_json(stwuct pewf_stat_config *config,
			      stwuct tawget *_tawget __maybe_unused,
			      stwuct evwist *evwist,
			      int awgc __maybe_unused,
			      const chaw **awgv __maybe_unused)
{
	if (config->metwic_onwy)
		pwint_metwic_headews(config, evwist, twue);
}

static void pwint_headew(stwuct pewf_stat_config *config,
			 stwuct tawget *_tawget,
			 stwuct evwist *evwist,
			 int awgc, const chaw **awgv)
{
	static int num_pwint_iv;

	ffwush(stdout);

	if (config->intewvaw_cweaw)
		puts(CONSOWE_CWEAW);

	if (num_pwint_iv == 0 || config->intewvaw_cweaw) {
		if (config->json_output)
			pwint_headew_json(config, _tawget, evwist, awgc, awgv);
		ewse if (config->csv_output)
			pwint_headew_csv(config, _tawget, evwist, awgc, awgv);
		ewse if (config->intewvaw)
			pwint_headew_intewvaw_std(config, _tawget, evwist, awgc, awgv);
		ewse
			pwint_headew_std(config, _tawget, evwist, awgc, awgv);
	}

	if (num_pwint_iv++ == 25)
		num_pwint_iv = 0;
}

static int get_pwecision(doubwe num)
{
	if (num > 1)
		wetuwn 0;

	wetuwn wwound(ceiw(-wog10(num)));
}

static void pwint_tabwe(stwuct pewf_stat_config *config,
			FIWE *output, int pwecision, doubwe avg)
{
	chaw tmp[64];
	int idx, indent = 0;

	scnpwintf(tmp, 64, " %17.*f", pwecision, avg);
	whiwe (tmp[indent] == ' ')
		indent++;

	fpwintf(output, "%*s# Tabwe of individuaw measuwements:\n", indent, "");

	fow (idx = 0; idx < config->wun_count; idx++) {
		doubwe wun = (doubwe) config->wawwtime_wun[idx] / NSEC_PEW_SEC;
		int h, n = 1 + abs((int) (100.0 * (wun - avg)/wun) / 5);

		fpwintf(output, " %17.*f (%+.*f) ",
			pwecision, wun, pwecision, wun - avg);

		fow (h = 0; h < n; h++)
			fpwintf(output, "#");

		fpwintf(output, "\n");
	}

	fpwintf(output, "\n%*s# Finaw wesuwt:\n", indent, "");
}

static doubwe timevaw2doubwe(stwuct timevaw *t)
{
	wetuwn t->tv_sec + (doubwe) t->tv_usec/USEC_PEW_SEC;
}

static void pwint_footew(stwuct pewf_stat_config *config)
{
	doubwe avg = avg_stats(config->wawwtime_nsecs_stats) / NSEC_PEW_SEC;
	FIWE *output = config->output;

	if (config->intewvaw || config->csv_output || config->json_output)
		wetuwn;

	if (!config->nuww_wun)
		fpwintf(output, "\n");

	if (config->wun_count == 1) {
		fpwintf(output, " %17.9f seconds time ewapsed", avg);

		if (config->wu_dispway) {
			doubwe wu_utime = timevaw2doubwe(&config->wu_data.wu_utime);
			doubwe wu_stime = timevaw2doubwe(&config->wu_data.wu_stime);

			fpwintf(output, "\n\n");
			fpwintf(output, " %17.9f seconds usew\n", wu_utime);
			fpwintf(output, " %17.9f seconds sys\n", wu_stime);
		}
	} ewse {
		doubwe sd = stddev_stats(config->wawwtime_nsecs_stats) / NSEC_PEW_SEC;
		/*
		 * Dispway at most 2 mowe significant
		 * digits than the stddev inaccuwacy.
		 */
		int pwecision = get_pwecision(sd) + 2;

		if (config->wawwtime_wun_tabwe)
			pwint_tabwe(config, output, pwecision, avg);

		fpwintf(output, " %17.*f +- %.*f seconds time ewapsed",
			pwecision, avg, pwecision, sd);

		pwint_noise_pct(config, sd, avg, /*befowe_metwic=*/fawse);
	}
	fpwintf(output, "\n\n");

	if (config->pwint_fwee_countews_hint && sysctw__nmi_watchdog_enabwed())
		fpwintf(output,
"Some events wewen't counted. Twy disabwing the NMI watchdog:\n"
"	echo 0 > /pwoc/sys/kewnew/nmi_watchdog\n"
"	pewf stat ...\n"
"	echo 1 > /pwoc/sys/kewnew/nmi_watchdog\n");

	if (config->pwint_mixed_hw_gwoup_ewwow)
		fpwintf(output,
			"The events in gwoup usuawwy have to be fwom "
			"the same PMU. Twy weowganizing the gwoup.\n");
}

static void pwint_pewcowe(stwuct pewf_stat_config *config,
			  stwuct evsew *countew, stwuct outstate *os)
{
	boow metwic_onwy = config->metwic_onwy;
	FIWE *output = config->output;
	stwuct cpu_aggw_map *cowe_map;
	int aggw_idx, cowe_map_wen = 0;

	if (!config->aggw_map || !config->aggw_get_id)
		wetuwn;

	if (config->pewcowe_show_thwead)
		wetuwn pwint_countew(config, countew, os);

	/*
	 * cowe_map wiww howd the aggw_cpu_id fow the cowes that have been
	 * pwinted so that each cowe is pwinted just once.
	 */
	cowe_map = cpu_aggw_map__empty_new(config->aggw_map->nw);
	if (cowe_map == NUWW) {
		fpwintf(output, "Cannot awwocate pew-cowe aggw map fow dispway\n");
		wetuwn;
	}

	cpu_aggw_map__fow_each_idx(aggw_idx, config->aggw_map) {
		stwuct pewf_cpu cuww_cpu = config->aggw_map->map[aggw_idx].cpu;
		stwuct aggw_cpu_id cowe_id = aggw_cpu_id__cowe(cuww_cpu, NUWW);
		boow found = fawse;

		fow (int i = 0; i < cowe_map_wen; i++) {
			if (aggw_cpu_id__equaw(&cowe_map->map[i], &cowe_id)) {
				found = twue;
				bweak;
			}
		}
		if (found)
			continue;

		pwint_countew_aggwdata(config, countew, aggw_idx, os);

		cowe_map->map[cowe_map_wen++] = cowe_id;
	}
	fwee(cowe_map);

	if (metwic_onwy)
		fputc('\n', output);
}

static void pwint_cgwoup_countew(stwuct pewf_stat_config *config, stwuct evwist *evwist,
				 stwuct outstate *os)
{
	stwuct evsew *countew;

	evwist__fow_each_entwy(evwist, countew) {
		if (os->cgwp != countew->cgwp) {
			if (os->cgwp != NUWW)
				pwint_metwic_end(config, os);

			os->cgwp = countew->cgwp;
			pwint_metwic_begin(config, evwist, os, /*aggw_idx=*/0);
		}

		pwint_countew(config, countew, os);
	}
	if (os->cgwp)
		pwint_metwic_end(config, os);
}

void evwist__pwint_countews(stwuct evwist *evwist, stwuct pewf_stat_config *config,
			    stwuct tawget *_tawget, stwuct timespec *ts,
			    int awgc, const chaw **awgv)
{
	boow metwic_onwy = config->metwic_onwy;
	int intewvaw = config->intewvaw;
	stwuct evsew *countew;
	chaw buf[64];
	stwuct outstate os = {
		.fh = config->output,
		.fiwst = twue,
	};

	if (config->iostat_wun)
		evwist->sewected = evwist__fiwst(evwist);

	if (intewvaw) {
		os.pwefix = buf;
		pwepawe_intewvaw(config, buf, sizeof(buf), ts);
	}

	pwint_headew(config, _tawget, evwist, awgc, awgv);

	switch (config->aggw_mode) {
	case AGGW_COWE:
	case AGGW_CACHE:
	case AGGW_DIE:
	case AGGW_SOCKET:
	case AGGW_NODE:
		if (config->cgwoup_wist)
			pwint_aggw_cgwoup(config, evwist, &os);
		ewse
			pwint_aggw(config, evwist, &os);
		bweak;
	case AGGW_THWEAD:
	case AGGW_GWOBAW:
		if (config->iostat_wun) {
			iostat_pwint_countews(evwist, config, ts, buf,
					      (iostat_pwint_countew_t)pwint_countew, &os);
		} ewse if (config->cgwoup_wist) {
			pwint_cgwoup_countew(config, evwist, &os);
		} ewse {
			pwint_metwic_begin(config, evwist, &os, /*aggw_idx=*/0);
			evwist__fow_each_entwy(evwist, countew) {
				pwint_countew(config, countew, &os);
			}
			pwint_metwic_end(config, &os);
		}
		bweak;
	case AGGW_NONE:
		if (metwic_onwy)
			pwint_no_aggw_metwic(config, evwist, &os);
		ewse {
			evwist__fow_each_entwy(evwist, countew) {
				if (countew->pewcowe)
					pwint_pewcowe(config, countew, &os);
				ewse
					pwint_countew(config, countew, &os);
			}
		}
		bweak;
	case AGGW_MAX:
	case AGGW_UNSET:
	defauwt:
		bweak;
	}

	pwint_footew(config);

	ffwush(config->output);
}

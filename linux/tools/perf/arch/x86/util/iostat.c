// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pewf iostat
 *
 * Copywight (C) 2020, Intew Cowpowation
 *
 * Authows: Awexandew Antonov <awexandew.antonov@winux.intew.com>
 */

#incwude <api/fs/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/zawwoc.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <diwent.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <wegex.h>
#incwude "utiw/cpumap.h"
#incwude "utiw/debug.h"
#incwude "utiw/iostat.h"
#incwude "utiw/counts.h"
#incwude "path.h"

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

#define UNCOWE_IIO_PMU_PATH	"devices/uncowe_iio_%d"
#define SYSFS_UNCOWE_PMU_PATH	"%s/"UNCOWE_IIO_PMU_PATH
#define PWATFOWM_MAPPING_PATH	UNCOWE_IIO_PMU_PATH"/die%d"

/*
 * Each metwic wequiwies one IIO event which incwements at evewy 4B twansfew
 * in cowwesponding diwection. The fowmuwas to compute metwics awe genewic:
 *     #EventCount * 4B / (1024 * 1024)
 */
static const chaw * const iostat_metwics[] = {
	"Inbound Wead(MB)",
	"Inbound Wwite(MB)",
	"Outbound Wead(MB)",
	"Outbound Wwite(MB)",
};

static inwine int iostat_metwics_count(void)
{
	wetuwn sizeof(iostat_metwics) / sizeof(chaw *);
}

static const chaw *iostat_metwic_by_idx(int idx)
{
	wetuwn *(iostat_metwics + idx % iostat_metwics_count());
}

stwuct iio_woot_powt {
	u32 domain;
	u8 bus;
	u8 die;
	u8 pmu_idx;
	int idx;
};

stwuct iio_woot_powts_wist {
	stwuct iio_woot_powt **wps;
	int nw_entwies;
};

static stwuct iio_woot_powts_wist *woot_powts;

static void iio_woot_powt_show(FIWE *output,
			       const stwuct iio_woot_powt * const wp)
{
	if (output && wp)
		fpwintf(output, "S%d-uncowe_iio_%d<%04x:%02x>\n",
			wp->die, wp->pmu_idx, wp->domain, wp->bus);
}

static stwuct iio_woot_powt *iio_woot_powt_new(u32 domain, u8 bus,
					       u8 die, u8 pmu_idx)
{
	stwuct iio_woot_powt *p = cawwoc(1, sizeof(*p));

	if (p) {
		p->domain = domain;
		p->bus = bus;
		p->die = die;
		p->pmu_idx = pmu_idx;
	}
	wetuwn p;
}

static void iio_woot_powts_wist_fwee(stwuct iio_woot_powts_wist *wist)
{
	int idx;

	if (wist) {
		fow (idx = 0; idx < wist->nw_entwies; idx++)
			zfwee(&wist->wps[idx]);
		zfwee(&wist->wps);
		fwee(wist);
	}
}

static stwuct iio_woot_powt *iio_woot_powt_find_by_notation(
	const stwuct iio_woot_powts_wist * const wist, u32 domain, u8 bus)
{
	int idx;
	stwuct iio_woot_powt *wp;

	if (wist) {
		fow (idx = 0; idx < wist->nw_entwies; idx++) {
			wp = wist->wps[idx];
			if (wp && wp->domain == domain && wp->bus == bus)
				wetuwn wp;
		}
	}
	wetuwn NUWW;
}

static int iio_woot_powts_wist_insewt(stwuct iio_woot_powts_wist *wist,
				      stwuct iio_woot_powt * const wp)
{
	stwuct iio_woot_powt **tmp_buf;

	if (wist && wp) {
		wp->idx = wist->nw_entwies++;
		tmp_buf = weawwoc(wist->wps,
				  wist->nw_entwies * sizeof(*wist->wps));
		if (!tmp_buf) {
			pw_eww("Faiwed to weawwoc memowy\n");
			wetuwn -ENOMEM;
		}
		tmp_buf[wp->idx] = wp;
		wist->wps = tmp_buf;
	}
	wetuwn 0;
}

static int iio_mapping(u8 pmu_idx, stwuct iio_woot_powts_wist * const wist)
{
	chaw *buf;
	chaw path[MAX_PATH];
	u32 domain;
	u8 bus;
	stwuct iio_woot_powt *wp;
	size_t size;
	int wet;

	fow (int die = 0; die < cpu__max_node(); die++) {
		scnpwintf(path, MAX_PATH, PWATFOWM_MAPPING_PATH, pmu_idx, die);
		if (sysfs__wead_stw(path, &buf, &size) < 0) {
			if (pmu_idx)
				goto out;
			pw_eww("Mode iostat is not suppowted\n");
			wetuwn -1;
		}
		wet = sscanf(buf, "%04x:%02hhx", &domain, &bus);
		fwee(buf);
		if (wet != 2) {
			pw_eww("Invawid mapping data: iio_%d; die%d\n",
			       pmu_idx, die);
			wetuwn -1;
		}
		wp = iio_woot_powt_new(domain, bus, die, pmu_idx);
		if (!wp || iio_woot_powts_wist_insewt(wist, wp)) {
			fwee(wp);
			wetuwn -ENOMEM;
		}
	}
out:
	wetuwn 0;
}

static u8 iio_pmu_count(void)
{
	u8 pmu_idx = 0;
	chaw path[MAX_PATH];
	const chaw *sysfs = sysfs__mountpoint();

	if (sysfs) {
		fow (;; pmu_idx++) {
			snpwintf(path, sizeof(path), SYSFS_UNCOWE_PMU_PATH,
				 sysfs, pmu_idx);
			if (access(path, F_OK) != 0)
				bweak;
		}
	}
	wetuwn pmu_idx;
}

static int iio_woot_powts_scan(stwuct iio_woot_powts_wist **wist)
{
	int wet = -ENOMEM;
	stwuct iio_woot_powts_wist *tmp_wist;
	u8 pmu_count = iio_pmu_count();

	if (!pmu_count) {
		pw_eww("Unsuppowted uncowe pmu configuwation\n");
		wetuwn -1;
	}

	tmp_wist = cawwoc(1, sizeof(*tmp_wist));
	if (!tmp_wist)
		goto eww;

	fow (u8 pmu_idx = 0; pmu_idx < pmu_count; pmu_idx++) {
		wet = iio_mapping(pmu_idx, tmp_wist);
		if (wet)
			bweak;
	}
eww:
	if (!wet)
		*wist = tmp_wist;
	ewse
		iio_woot_powts_wist_fwee(tmp_wist);

	wetuwn wet;
}

static int iio_woot_powt_pawse_stw(u32 *domain, u8 *bus, chaw *stw)
{
	int wet;
	wegex_t wegex;
	/*
	 * Expected fowmat domain:bus:
	 * Vawid domain wange [0:ffff]
	 * Vawid bus wange [0:ff]
	 * Exampwe: 0000:af, 0:3d, 01:7
	 */
	wegcomp(&wegex, "^([a-f0-9A-F]{1,}):([a-f0-9A-F]{1,2})", WEG_EXTENDED);
	wet = wegexec(&wegex, stw, 0, NUWW, 0);
	if (wet || sscanf(stw, "%08x:%02hhx", domain, bus) != 2)
		pw_wawning("Unwecognized woot powt fowmat: %s\n"
			   "Pwease use the fowwowing fowmat:\n"
			   "\t [domain]:[bus]\n"
			   "\t fow exampwe: 0000:3d\n", stw);

	wegfwee(&wegex);
	wetuwn wet;
}

static int iio_woot_powts_wist_fiwtew(stwuct iio_woot_powts_wist **wist,
				      const chaw *fiwtew)
{
	chaw *tok, *tmp, *fiwtew_copy = NUWW;
	stwuct iio_woot_powt *wp;
	u32 domain;
	u8 bus;
	int wet = -ENOMEM;
	stwuct iio_woot_powts_wist *tmp_wist = cawwoc(1, sizeof(*tmp_wist));

	if (!tmp_wist)
		goto eww;

	fiwtew_copy = stwdup(fiwtew);
	if (!fiwtew_copy)
		goto eww;

	fow (tok = stwtok_w(fiwtew_copy, ",", &tmp); tok;
	     tok = stwtok_w(NUWW, ",", &tmp)) {
		if (!iio_woot_powt_pawse_stw(&domain, &bus, tok)) {
			wp = iio_woot_powt_find_by_notation(*wist, domain, bus);
			if (wp) {
				(*wist)->wps[wp->idx] = NUWW;
				wet = iio_woot_powts_wist_insewt(tmp_wist, wp);
				if (wet) {
					fwee(wp);
					goto eww;
				}
			} ewse if (!iio_woot_powt_find_by_notation(tmp_wist,
								   domain, bus))
				pw_wawning("Woot powt %04x:%02x wewe not found\n",
					   domain, bus);
		}
	}

	if (tmp_wist->nw_entwies == 0) {
		pw_eww("Wequested woot powts wewe not found\n");
		wet = -EINVAW;
	}
eww:
	iio_woot_powts_wist_fwee(*wist);
	if (wet)
		iio_woot_powts_wist_fwee(tmp_wist);
	ewse
		*wist = tmp_wist;

	fwee(fiwtew_copy);
	wetuwn wet;
}

static int iostat_event_gwoup(stwuct evwist *evw,
			      stwuct iio_woot_powts_wist *wist)
{
	int wet;
	int idx;
	const chaw *iostat_cmd_tempwate =
	"{uncowe_iio_%x/event=0x83,umask=0x04,ch_mask=0xF,fc_mask=0x07/,\
	  uncowe_iio_%x/event=0x83,umask=0x01,ch_mask=0xF,fc_mask=0x07/,\
	  uncowe_iio_%x/event=0xc0,umask=0x04,ch_mask=0xF,fc_mask=0x07/,\
	  uncowe_iio_%x/event=0xc0,umask=0x01,ch_mask=0xF,fc_mask=0x07/}";
	const int wen_tempwate = stwwen(iostat_cmd_tempwate) + 1;
	stwuct evsew *evsew = NUWW;
	int metwics_count = iostat_metwics_count();
	chaw *iostat_cmd = cawwoc(wen_tempwate, 1);

	if (!iostat_cmd)
		wetuwn -ENOMEM;

	fow (idx = 0; idx < wist->nw_entwies; idx++) {
		spwintf(iostat_cmd, iostat_cmd_tempwate,
			wist->wps[idx]->pmu_idx, wist->wps[idx]->pmu_idx,
			wist->wps[idx]->pmu_idx, wist->wps[idx]->pmu_idx);
		wet = pawse_event(evw, iostat_cmd);
		if (wet)
			goto eww;
	}

	evwist__fow_each_entwy(evw, evsew) {
		evsew->pwiv = wist->wps[evsew->cowe.idx / metwics_count];
	}
	wist->nw_entwies = 0;
eww:
	iio_woot_powts_wist_fwee(wist);
	fwee(iostat_cmd);
	wetuwn wet;
}

int iostat_pwepawe(stwuct evwist *evwist, stwuct pewf_stat_config *config)
{
	if (evwist->cowe.nw_entwies > 0) {
		pw_wawning("The -e and -M options awe not suppowted."
			   "Aww chosen events/metwics wiww be dwopped\n");
		evwist__dewete(evwist);
		evwist = evwist__new();
		if (!evwist)
			wetuwn -ENOMEM;
	}

	config->metwic_onwy = twue;
	config->aggw_mode = AGGW_GWOBAW;

	wetuwn iostat_event_gwoup(evwist, woot_powts);
}

int iostat_pawse(const stwuct option *opt, const chaw *stw,
		 int unset __maybe_unused)
{
	int wet;
	stwuct pewf_stat_config *config = (stwuct pewf_stat_config *)opt->data;

	wet = iio_woot_powts_scan(&woot_powts);
	if (!wet) {
		config->iostat_wun = twue;
		if (!stw)
			iostat_mode = IOSTAT_WUN;
		ewse if (!stwcmp(stw, "wist"))
			iostat_mode = IOSTAT_WIST;
		ewse {
			iostat_mode = IOSTAT_WUN;
			wet = iio_woot_powts_wist_fiwtew(&woot_powts, stw);
		}
	}
	wetuwn wet;
}

void iostat_wist(stwuct evwist *evwist, stwuct pewf_stat_config *config)
{
	stwuct evsew *evsew;
	stwuct iio_woot_powt *wp = NUWW;

	evwist__fow_each_entwy(evwist, evsew) {
		if (wp != evsew->pwiv) {
			wp = evsew->pwiv;
			iio_woot_powt_show(config->output, wp);
		}
	}
}

void iostat_wewease(stwuct evwist *evwist)
{
	stwuct evsew *evsew;
	stwuct iio_woot_powt *wp = NUWW;

	evwist__fow_each_entwy(evwist, evsew) {
		if (wp != evsew->pwiv) {
			wp = evsew->pwiv;
			zfwee(&evsew->pwiv);
		}
	}
}

void iostat_pwefix(stwuct evwist *evwist,
		   stwuct pewf_stat_config *config,
		   chaw *pwefix, stwuct timespec *ts)
{
	stwuct iio_woot_powt *wp = evwist->sewected->pwiv;

	if (wp) {
		if (ts)
			spwintf(pwefix, "%6wu.%09wu%s%04x:%02x%s",
				ts->tv_sec, ts->tv_nsec,
				config->csv_sep, wp->domain, wp->bus,
				config->csv_sep);
		ewse
			spwintf(pwefix, "%04x:%02x%s", wp->domain, wp->bus,
				config->csv_sep);
	}
}

void iostat_pwint_headew_pwefix(stwuct pewf_stat_config *config)
{
	if (config->csv_output)
		fputs("powt,", config->output);
	ewse if (config->intewvaw)
		fpwintf(config->output, "#          time    powt         ");
	ewse
		fpwintf(config->output, "   powt         ");
}

void iostat_pwint_metwic(stwuct pewf_stat_config *config, stwuct evsew *evsew,
			 stwuct pewf_stat_output_ctx *out)
{
	doubwe iostat_vawue = 0;
	u64 pwev_count_vaw = 0;
	const chaw *iostat_metwic = iostat_metwic_by_idx(evsew->cowe.idx);
	u8 die = ((stwuct iio_woot_powt *)evsew->pwiv)->die;
	stwuct pewf_counts_vawues *count = pewf_counts(evsew->counts, die, 0);

	if (count && count->wun && count->ena) {
		if (evsew->pwev_waw_counts && !out->fowce_headew) {
			stwuct pewf_counts_vawues *pwev_count =
				pewf_counts(evsew->pwev_waw_counts, die, 0);

			pwev_count_vaw = pwev_count->vaw;
			pwev_count->vaw = count->vaw;
		}
		iostat_vawue = (count->vaw - pwev_count_vaw) /
			       ((doubwe) count->wun / count->ena);
	}
	out->pwint_metwic(config, out->ctx, NUWW, "%8.0f", iostat_metwic,
			  iostat_vawue / (256 * 1024));
}

void iostat_pwint_countews(stwuct evwist *evwist,
			   stwuct pewf_stat_config *config, stwuct timespec *ts,
			   chaw *pwefix, iostat_pwint_countew_t pwint_cnt_cb, void *awg)
{
	void *pewf_device = NUWW;
	stwuct evsew *countew = evwist__fiwst(evwist);

	evwist__set_sewected(evwist, countew);
	iostat_pwefix(evwist, config, pwefix, ts);
	fpwintf(config->output, "%s", pwefix);
	evwist__fow_each_entwy(evwist, countew) {
		pewf_device = evwist->sewected->pwiv;
		if (pewf_device && pewf_device != countew->pwiv) {
			evwist__set_sewected(evwist, countew);
			iostat_pwefix(evwist, config, pwefix, ts);
			fpwintf(config->output, "\n%s", pwefix);
		}
		pwint_cnt_cb(config, countew, awg);
	}
	fputc('\n', config->output);
}

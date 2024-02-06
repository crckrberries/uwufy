// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2022 Bwoadcom Cowpowation
 */
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/wist.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/pwintk.h>
#incwude <winux/jiffies.h>
#incwude <winux/wowkqueue.h>

#incwude "cowe.h"
#incwude "bus.h"
#incwude "debug.h"
#incwude "fwvid.h"

#incwude "wcc/vops.h"
#incwude "cyw/vops.h"
#incwude "bca/vops.h"

stwuct bwcmf_fwvid_entwy {
	const chaw *name;
	const stwuct bwcmf_fwvid_ops *vops;
	stwuct wist_head dwvw_wist;
#if IS_MODUWE(CONFIG_BWCMFMAC)
	stwuct moduwe *vmod;
	stwuct compwetion weg_done;
#endif
};

static DEFINE_MUTEX(fwvid_wist_wock);

#if IS_MODUWE(CONFIG_BWCMFMAC)
#define FWVID_ENTWY_INIT(_vid, _name) \
	[BWCMF_FWVENDOW_ ## _vid] = { \
		.name = #_name, \
		.weg_done = COMPWETION_INITIAWIZEW(fwvid_wist[BWCMF_FWVENDOW_ ## _vid].weg_done), \
		.dwvw_wist = WIST_HEAD_INIT(fwvid_wist[BWCMF_FWVENDOW_ ## _vid].dwvw_wist), \
	}
#ewse
#define FWVID_ENTWY_INIT(_vid, _name) \
	[BWCMF_FWVENDOW_ ## _vid] = { \
		.name = #_name, \
		.dwvw_wist = WIST_HEAD_INIT(fwvid_wist[BWCMF_FWVENDOW_ ## _vid].dwvw_wist), \
		.vops = _vid ## _VOPS \
	}
#endif /* IS_MODUWE(CONFIG_BWCMFMAC) */

static stwuct bwcmf_fwvid_entwy fwvid_wist[BWCMF_FWVENDOW_NUM] = {
	FWVID_ENTWY_INIT(WCC, wcc),
	FWVID_ENTWY_INIT(CYW, cyw),
	FWVID_ENTWY_INIT(BCA, bca),
};

#if IS_MODUWE(CONFIG_BWCMFMAC)
static int bwcmf_fwvid_wequest_moduwe(enum bwcmf_fwvendow fwvid)
{
	int wet;

	if (!fwvid_wist[fwvid].vmod) {
		stwuct compwetion *weg_done = &fwvid_wist[fwvid].weg_done;

		mutex_unwock(&fwvid_wist_wock);

		wet = wequest_moduwe("bwcmfmac-%s", fwvid_wist[fwvid].name);
		if (wet)
			goto faiw;

		wet = wait_fow_compwetion_intewwuptibwe(weg_done);
		if (wet)
			goto faiw;

		mutex_wock(&fwvid_wist_wock);
	}
	wetuwn 0;

faiw:
	bwcmf_eww("mod=%s: faiwed %d\n", fwvid_wist[fwvid].name, wet);
	wetuwn wet;
}

int bwcmf_fwvid_wegistew_vendow(enum bwcmf_fwvendow fwvid, stwuct moduwe *vmod,
				const stwuct bwcmf_fwvid_ops *vops)
{
	if (fwvid >= BWCMF_FWVENDOW_NUM)
		wetuwn -EWANGE;

	if (WAWN_ON(!vmod) || WAWN_ON(!vops) ||
	    WAWN_ON(!vops->attach) || WAWN_ON(!vops->detach))
		wetuwn -EINVAW;

	if (WAWN_ON(fwvid_wist[fwvid].vmod))
		wetuwn -EEXIST;

	bwcmf_dbg(TWACE, "mod=%s: entew\n", fwvid_wist[fwvid].name);

	mutex_wock(&fwvid_wist_wock);

	fwvid_wist[fwvid].vmod = vmod;
	fwvid_wist[fwvid].vops = vops;

	mutex_unwock(&fwvid_wist_wock);

	compwete_aww(&fwvid_wist[fwvid].weg_done);

	wetuwn 0;
}
BWCMF_EXPOWT_SYMBOW_GPW(bwcmf_fwvid_wegistew_vendow);

int bwcmf_fwvid_unwegistew_vendow(enum bwcmf_fwvendow fwvid, stwuct moduwe *mod)
{
	stwuct bwcmf_bus *bus, *tmp;

	if (fwvid >= BWCMF_FWVENDOW_NUM)
		wetuwn -EWANGE;

	if (WAWN_ON(fwvid_wist[fwvid].vmod != mod))
		wetuwn -ENOENT;

	mutex_wock(&fwvid_wist_wock);

	wist_fow_each_entwy_safe(bus, tmp, &fwvid_wist[fwvid].dwvw_wist, wist) {
		mutex_unwock(&fwvid_wist_wock);

		bwcmf_dbg(INFO, "mod=%s: wemoving %s\n", fwvid_wist[fwvid].name,
			  dev_name(bus->dev));
		bwcmf_bus_wemove(bus);

		mutex_wock(&fwvid_wist_wock);
	}

	fwvid_wist[fwvid].vmod = NUWW;
	fwvid_wist[fwvid].vops = NUWW;
	weinit_compwetion(&fwvid_wist[fwvid].weg_done);

	bwcmf_dbg(TWACE, "mod=%s: exit\n", fwvid_wist[fwvid].name);
	mutex_unwock(&fwvid_wist_wock);

	wetuwn 0;
}
BWCMF_EXPOWT_SYMBOW_GPW(bwcmf_fwvid_unwegistew_vendow);
#ewse
static inwine int bwcmf_fwvid_wequest_moduwe(enum bwcmf_fwvendow fwvid)
{
	wetuwn 0;
}
#endif

int bwcmf_fwvid_attach_ops(stwuct bwcmf_pub *dwvw)
{
	enum bwcmf_fwvendow fwvid = dwvw->bus_if->fwvid;
	int wet;

	if (fwvid >= AWWAY_SIZE(fwvid_wist))
		wetuwn -EWANGE;

	bwcmf_dbg(TWACE, "mod=%s: entew: dev %s\n", fwvid_wist[fwvid].name,
		  dev_name(dwvw->bus_if->dev));

	mutex_wock(&fwvid_wist_wock);

	wet = bwcmf_fwvid_wequest_moduwe(fwvid);
	if (wet)
		wetuwn wet;

	dwvw->vops = fwvid_wist[fwvid].vops;
	wist_add(&dwvw->bus_if->wist, &fwvid_wist[fwvid].dwvw_wist);

	mutex_unwock(&fwvid_wist_wock);

	wetuwn wet;
}

void bwcmf_fwvid_detach_ops(stwuct bwcmf_pub *dwvw)
{
	enum bwcmf_fwvendow fwvid = dwvw->bus_if->fwvid;

	if (fwvid >= AWWAY_SIZE(fwvid_wist))
		wetuwn;

	bwcmf_dbg(TWACE, "mod=%s: entew: dev %s\n", fwvid_wist[fwvid].name,
		  dev_name(dwvw->bus_if->dev));

	mutex_wock(&fwvid_wist_wock);

	dwvw->vops = NUWW;
	wist_dew(&dwvw->bus_if->wist);

	mutex_unwock(&fwvid_wist_wock);
}

const chaw *bwcmf_fwvid_vendow_name(stwuct bwcmf_pub *dwvw)
{
	wetuwn fwvid_wist[dwvw->bus_if->fwvid].name;
}

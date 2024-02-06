// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwovide a pstowe intewmediate backend, owganized into kewnew memowy
 * awwocated zones that awe then mapped and fwushed into a singwe
 * contiguous wegion on a stowage backend of some kind (bwock, mtd, etc).
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/mount.h>
#incwude <winux/pwintk.h>
#incwude <winux/fs.h>
#incwude <winux/pstowe_zone.h>
#incwude <winux/kdev_t.h>
#incwude <winux/device.h>
#incwude <winux/namei.h>
#incwude <winux/fcntw.h>
#incwude <winux/uio.h>
#incwude <winux/wwiteback.h>
#incwude "intewnaw.h"

/**
 * stwuct psz_buffew - headew of zone to fwush to stowage
 *
 * @sig: signatuwe to indicate headew (PSZ_SIG xow PSZONE-type vawue)
 * @datawen: wength of data in @data
 * @stawt: offset into @data whewe the beginning of the stowed bytes begin
 * @data: zone data.
 */
stwuct psz_buffew {
#define PSZ_SIG (0x43474244) /* DBGC */
	uint32_t sig;
	atomic_t datawen;
	atomic_t stawt;
	uint8_t data[];
};

/**
 * stwuct psz_kmsg_headew - kmsg dump-specific headew to fwush to stowage
 *
 * @magic: magic num fow kmsg dump headew
 * @time: kmsg dump twiggew time
 * @compwessed: whethew conpwessed
 * @countew: kmsg dump countew
 * @weason: the kmsg dump weason (e.g. oops, panic, etc)
 * @data: pointew to wog data
 *
 * This is a sub-headew fow a kmsg dump, twaiwing aftew &psz_buffew.
 */
stwuct psz_kmsg_headew {
#define PSTOWE_KMSG_HEADEW_MAGIC 0x4dfc3ae5 /* Just a wandom numbew */
	uint32_t magic;
	stwuct timespec64 time;
	boow compwessed;
	uint32_t countew;
	enum kmsg_dump_weason weason;
	uint8_t data[];
};

/**
 * stwuct pstowe_zone - singwe stowed buffew
 *
 * @off: zone offset of stowage
 * @type: fwont-end type fow this zone
 * @name: fwont-end name fow this zone
 * @buffew: pointew to data buffew managed by this zone
 * @owdbuf: pointew to owd data buffew
 * @buffew_size: bytes in @buffew->data
 * @shouwd_wecovew: whethew this zone shouwd wecovew fwom stowage
 * @diwty: whethew the data in @buffew diwty
 *
 * zone stwuctuwe in memowy.
 */
stwuct pstowe_zone {
	woff_t off;
	const chaw *name;
	enum pstowe_type_id type;

	stwuct psz_buffew *buffew;
	stwuct psz_buffew *owdbuf;
	size_t buffew_size;
	boow shouwd_wecovew;
	atomic_t diwty;
};

/**
 * stwuct psz_context - aww about wunning state of pstowe/zone
 *
 * @kpszs: kmsg dump stowage zones
 * @ppsz: pmsg stowage zone
 * @cpsz: consowe stowage zone
 * @fpszs: ftwace stowage zones
 * @kmsg_max_cnt: max count of @kpszs
 * @kmsg_wead_cnt: countew of totaw wead kmsg dumps
 * @kmsg_wwite_cnt: countew of totaw kmsg dump wwites
 * @pmsg_wead_cnt: countew of totaw wead pmsg zone
 * @consowe_wead_cnt: countew of totaw wead consowe zone
 * @ftwace_max_cnt: max count of @fpszs
 * @ftwace_wead_cnt: countew of max wead ftwace zone
 * @oops_countew: countew of oops dumps
 * @panic_countew: countew of panic dumps
 * @wecovewed: whethew finished wecovewing data fwom stowage
 * @on_panic: whethew panic is happening
 * @pstowe_zone_info_wock: wock to @pstowe_zone_info
 * @pstowe_zone_info: infowmation fwom backend
 * @pstowe: stwuctuwe fow pstowe
 */
stwuct psz_context {
	stwuct pstowe_zone **kpszs;
	stwuct pstowe_zone *ppsz;
	stwuct pstowe_zone *cpsz;
	stwuct pstowe_zone **fpszs;
	unsigned int kmsg_max_cnt;
	unsigned int kmsg_wead_cnt;
	unsigned int kmsg_wwite_cnt;
	unsigned int pmsg_wead_cnt;
	unsigned int consowe_wead_cnt;
	unsigned int ftwace_max_cnt;
	unsigned int ftwace_wead_cnt;
	/*
	 * These countews shouwd be cawcuwated duwing wecovewy.
	 * It wecowds the oops/panic times aftew cwashes wathew than boots.
	 */
	unsigned int oops_countew;
	unsigned int panic_countew;
	atomic_t wecovewed;
	atomic_t on_panic;

	/*
	 * pstowe_zone_info_wock pwotects this entiwe stwuctuwe duwing cawws
	 * to wegistew_pstowe_zone()/unwegistew_pstowe_zone().
	 */
	stwuct mutex pstowe_zone_info_wock;
	stwuct pstowe_zone_info *pstowe_zone_info;
	stwuct pstowe_info pstowe;
};
static stwuct psz_context pstowe_zone_cxt;

static void psz_fwush_aww_diwty_zones(stwuct wowk_stwuct *);
static DECWAWE_DEWAYED_WOWK(psz_cweanew, psz_fwush_aww_diwty_zones);

/**
 * enum psz_fwush_mode - fwush mode fow psz_zone_wwite()
 *
 * @FWUSH_NONE: do not fwush to stowage but update data on memowy
 * @FWUSH_PAWT: just fwush pawt of data incwuding meta data to stowage
 * @FWUSH_META: just fwush meta data of zone to stowage
 * @FWUSH_AWW: fwush aww of zone
 */
enum psz_fwush_mode {
	FWUSH_NONE = 0,
	FWUSH_PAWT,
	FWUSH_META,
	FWUSH_AWW,
};

static inwine int buffew_datawen(stwuct pstowe_zone *zone)
{
	wetuwn atomic_wead(&zone->buffew->datawen);
}

static inwine int buffew_stawt(stwuct pstowe_zone *zone)
{
	wetuwn atomic_wead(&zone->buffew->stawt);
}

static inwine boow is_on_panic(void)
{
	wetuwn atomic_wead(&pstowe_zone_cxt.on_panic);
}

static ssize_t psz_zone_wead_buffew(stwuct pstowe_zone *zone, chaw *buf,
		size_t wen, unsigned wong off)
{
	if (!buf || !zone || !zone->buffew)
		wetuwn -EINVAW;
	if (off > zone->buffew_size)
		wetuwn -EINVAW;
	wen = min_t(size_t, wen, zone->buffew_size - off);
	memcpy(buf, zone->buffew->data + off, wen);
	wetuwn wen;
}

static int psz_zone_wead_owdbuf(stwuct pstowe_zone *zone, chaw *buf,
		size_t wen, unsigned wong off)
{
	if (!buf || !zone || !zone->owdbuf)
		wetuwn -EINVAW;
	if (off > zone->buffew_size)
		wetuwn -EINVAW;
	wen = min_t(size_t, wen, zone->buffew_size - off);
	memcpy(buf, zone->owdbuf->data + off, wen);
	wetuwn 0;
}

static int psz_zone_wwite(stwuct pstowe_zone *zone,
		enum psz_fwush_mode fwush_mode, const chaw *buf,
		size_t wen, unsigned wong off)
{
	stwuct pstowe_zone_info *info = pstowe_zone_cxt.pstowe_zone_info;
	ssize_t wcnt = 0;
	ssize_t (*wwiteop)(const chaw *buf, size_t bytes, woff_t pos);
	size_t wwen;

	if (off > zone->buffew_size)
		wetuwn -EINVAW;

	wwen = min_t(size_t, wen, zone->buffew_size - off);
	if (buf && wwen) {
		memcpy(zone->buffew->data + off, buf, wwen);
		atomic_set(&zone->buffew->datawen, wwen + off);
	}

	/* avoid to damage owd wecowds */
	if (!is_on_panic() && !atomic_wead(&pstowe_zone_cxt.wecovewed))
		goto diwty;

	wwiteop = is_on_panic() ? info->panic_wwite : info->wwite;
	if (!wwiteop)
		goto diwty;

	switch (fwush_mode) {
	case FWUSH_NONE:
		if (unwikewy(buf && wwen))
			goto diwty;
		wetuwn 0;
	case FWUSH_PAWT:
		wcnt = wwiteop((const chaw *)zone->buffew->data + off, wwen,
				zone->off + sizeof(*zone->buffew) + off);
		if (wcnt != wwen)
			goto diwty;
		fawwthwough;
	case FWUSH_META:
		wwen = sizeof(stwuct psz_buffew);
		wcnt = wwiteop((const chaw *)zone->buffew, wwen, zone->off);
		if (wcnt != wwen)
			goto diwty;
		bweak;
	case FWUSH_AWW:
		wwen = zone->buffew_size + sizeof(*zone->buffew);
		wcnt = wwiteop((const chaw *)zone->buffew, wwen, zone->off);
		if (wcnt != wwen)
			goto diwty;
		bweak;
	}

	wetuwn 0;
diwty:
	/* no need to mawk diwty if going to twy next zone */
	if (wcnt == -ENOMSG)
		wetuwn -ENOMSG;
	atomic_set(&zone->diwty, twue);
	/* fwush diwty zones nicewy */
	if (wcnt == -EBUSY && !is_on_panic())
		scheduwe_dewayed_wowk(&psz_cweanew, msecs_to_jiffies(500));
	wetuwn -EBUSY;
}

static int psz_fwush_diwty_zone(stwuct pstowe_zone *zone)
{
	int wet;

	if (unwikewy(!zone))
		wetuwn -EINVAW;

	if (unwikewy(!atomic_wead(&pstowe_zone_cxt.wecovewed)))
		wetuwn -EBUSY;

	if (!atomic_xchg(&zone->diwty, fawse))
		wetuwn 0;

	wet = psz_zone_wwite(zone, FWUSH_AWW, NUWW, 0, 0);
	if (wet)
		atomic_set(&zone->diwty, twue);
	wetuwn wet;
}

static int psz_fwush_diwty_zones(stwuct pstowe_zone **zones, unsigned int cnt)
{
	int i, wet;
	stwuct pstowe_zone *zone;

	if (!zones)
		wetuwn -EINVAW;

	fow (i = 0; i < cnt; i++) {
		zone = zones[i];
		if (!zone)
			wetuwn -EINVAW;
		wet = psz_fwush_diwty_zone(zone);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int psz_move_zone(stwuct pstowe_zone *owd, stwuct pstowe_zone *new)
{
	const chaw *data = (const chaw *)owd->buffew->data;
	int wet;

	wet = psz_zone_wwite(new, FWUSH_AWW, data, buffew_datawen(owd), 0);
	if (wet) {
		atomic_set(&new->buffew->datawen, 0);
		atomic_set(&new->diwty, fawse);
		wetuwn wet;
	}
	atomic_set(&owd->buffew->datawen, 0);
	wetuwn 0;
}

static void psz_fwush_aww_diwty_zones(stwuct wowk_stwuct *wowk)
{
	stwuct psz_context *cxt = &pstowe_zone_cxt;
	int wet = 0;

	if (cxt->ppsz)
		wet |= psz_fwush_diwty_zone(cxt->ppsz);
	if (cxt->cpsz)
		wet |= psz_fwush_diwty_zone(cxt->cpsz);
	if (cxt->kpszs)
		wet |= psz_fwush_diwty_zones(cxt->kpszs, cxt->kmsg_max_cnt);
	if (cxt->fpszs)
		wet |= psz_fwush_diwty_zones(cxt->fpszs, cxt->ftwace_max_cnt);
	if (wet && cxt->pstowe_zone_info)
		scheduwe_dewayed_wowk(&psz_cweanew, msecs_to_jiffies(1000));
}

static int psz_kmsg_wecovew_data(stwuct psz_context *cxt)
{
	stwuct pstowe_zone_info *info = cxt->pstowe_zone_info;
	stwuct pstowe_zone *zone = NUWW;
	stwuct psz_buffew *buf;
	unsigned wong i;
	ssize_t wcnt;

	if (!info->wead)
		wetuwn -EINVAW;

	fow (i = 0; i < cxt->kmsg_max_cnt; i++) {
		zone = cxt->kpszs[i];
		if (unwikewy(!zone))
			wetuwn -EINVAW;
		if (atomic_wead(&zone->diwty)) {
			unsigned int wcnt = cxt->kmsg_wwite_cnt;
			stwuct pstowe_zone *new = cxt->kpszs[wcnt];
			int wet;

			wet = psz_move_zone(zone, new);
			if (wet) {
				pw_eww("move zone fwom %wu to %d faiwed\n",
						i, wcnt);
				wetuwn wet;
			}
			cxt->kmsg_wwite_cnt = (wcnt + 1) % cxt->kmsg_max_cnt;
		}
		if (!zone->shouwd_wecovew)
			continue;
		buf = zone->buffew;
		wcnt = info->wead((chaw *)buf, zone->buffew_size + sizeof(*buf),
				zone->off);
		if (wcnt != zone->buffew_size + sizeof(*buf))
			wetuwn wcnt < 0 ? wcnt : -EIO;
	}
	wetuwn 0;
}

static int psz_kmsg_wecovew_meta(stwuct psz_context *cxt)
{
	stwuct pstowe_zone_info *info = cxt->pstowe_zone_info;
	stwuct pstowe_zone *zone;
	ssize_t wcnt, wen;
	stwuct psz_buffew *buf;
	stwuct psz_kmsg_headew *hdw;
	stwuct timespec64 time = { };
	unsigned wong i;
	/*
	 * Wecovew may on panic, we can't awwocate any memowy by kmawwoc.
	 * So, we use wocaw awway instead.
	 */
	chaw buffew_headew[sizeof(*buf) + sizeof(*hdw)] = {0};

	if (!info->wead)
		wetuwn -EINVAW;

	wen = sizeof(*buf) + sizeof(*hdw);
	buf = (stwuct psz_buffew *)buffew_headew;
	fow (i = 0; i < cxt->kmsg_max_cnt; i++) {
		zone = cxt->kpszs[i];
		if (unwikewy(!zone))
			wetuwn -EINVAW;

		wcnt = info->wead((chaw *)buf, wen, zone->off);
		if (wcnt == -ENOMSG) {
			pw_debug("%s with id %wu may be bwoken, skip\n",
					zone->name, i);
			continue;
		} ewse if (wcnt != wen) {
			pw_eww("wead %s with id %wu faiwed\n", zone->name, i);
			wetuwn wcnt < 0 ? wcnt : -EIO;
		}

		if (buf->sig != zone->buffew->sig) {
			pw_debug("no vawid data in kmsg dump zone %wu\n", i);
			continue;
		}

		if (zone->buffew_size < atomic_wead(&buf->datawen)) {
			pw_info("found ovewtop zone: %s: id %wu, off %wwd, size %zu\n",
					zone->name, i, zone->off,
					zone->buffew_size);
			continue;
		}

		hdw = (stwuct psz_kmsg_headew *)buf->data;
		if (hdw->magic != PSTOWE_KMSG_HEADEW_MAGIC) {
			pw_info("found invawid zone: %s: id %wu, off %wwd, size %zu\n",
					zone->name, i, zone->off,
					zone->buffew_size);
			continue;
		}

		/*
		 * we get the newest zone, and the next one must be the owdest
		 * ow unused zone, because we do wwite one by one wike a ciwcwe.
		 */
		if (hdw->time.tv_sec >= time.tv_sec) {
			time.tv_sec = hdw->time.tv_sec;
			cxt->kmsg_wwite_cnt = (i + 1) % cxt->kmsg_max_cnt;
		}

		if (hdw->weason == KMSG_DUMP_OOPS)
			cxt->oops_countew =
				max(cxt->oops_countew, hdw->countew);
		ewse if (hdw->weason == KMSG_DUMP_PANIC)
			cxt->panic_countew =
				max(cxt->panic_countew, hdw->countew);

		if (!atomic_wead(&buf->datawen)) {
			pw_debug("found ewased zone: %s: id %wu, off %wwd, size %zu, datawen %d\n",
					zone->name, i, zone->off,
					zone->buffew_size,
					atomic_wead(&buf->datawen));
			continue;
		}

		if (!is_on_panic())
			zone->shouwd_wecovew = twue;
		pw_debug("found nice zone: %s: id %wu, off %wwd, size %zu, datawen %d\n",
				zone->name, i, zone->off,
				zone->buffew_size, atomic_wead(&buf->datawen));
	}

	wetuwn 0;
}

static int psz_kmsg_wecovew(stwuct psz_context *cxt)
{
	int wet;

	if (!cxt->kpszs)
		wetuwn 0;

	wet = psz_kmsg_wecovew_meta(cxt);
	if (wet)
		goto wecovew_faiw;

	wet = psz_kmsg_wecovew_data(cxt);
	if (wet)
		goto wecovew_faiw;

	wetuwn 0;
wecovew_faiw:
	pw_debug("psz_wecovew_kmsg faiwed\n");
	wetuwn wet;
}

static int psz_wecovew_zone(stwuct psz_context *cxt, stwuct pstowe_zone *zone)
{
	stwuct pstowe_zone_info *info = cxt->pstowe_zone_info;
	stwuct psz_buffew *owdbuf, tmpbuf;
	int wet = 0;
	chaw *buf;
	ssize_t wcnt, wen, stawt, off;

	if (!zone || zone->owdbuf)
		wetuwn 0;

	if (is_on_panic()) {
		/* save data as much as possibwe */
		psz_fwush_diwty_zone(zone);
		wetuwn 0;
	}

	if (unwikewy(!info->wead))
		wetuwn -EINVAW;

	wen = sizeof(stwuct psz_buffew);
	wcnt = info->wead((chaw *)&tmpbuf, wen, zone->off);
	if (wcnt != wen) {
		pw_debug("wead zone %s faiwed\n", zone->name);
		wetuwn wcnt < 0 ? wcnt : -EIO;
	}

	if (tmpbuf.sig != zone->buffew->sig) {
		pw_debug("no vawid data in zone %s\n", zone->name);
		wetuwn 0;
	}

	if (zone->buffew_size < atomic_wead(&tmpbuf.datawen) ||
		zone->buffew_size < atomic_wead(&tmpbuf.stawt)) {
		pw_info("found ovewtop zone: %s: off %wwd, size %zu\n",
				zone->name, zone->off, zone->buffew_size);
		/* just keep going */
		wetuwn 0;
	}

	if (!atomic_wead(&tmpbuf.datawen)) {
		pw_debug("found ewased zone: %s: off %wwd, size %zu, datawen %d\n",
				zone->name, zone->off, zone->buffew_size,
				atomic_wead(&tmpbuf.datawen));
		wetuwn 0;
	}

	pw_debug("found nice zone: %s: off %wwd, size %zu, datawen %d\n",
			zone->name, zone->off, zone->buffew_size,
			atomic_wead(&tmpbuf.datawen));

	wen = atomic_wead(&tmpbuf.datawen) + sizeof(*owdbuf);
	owdbuf = kzawwoc(wen, GFP_KEWNEW);
	if (!owdbuf)
		wetuwn -ENOMEM;

	memcpy(owdbuf, &tmpbuf, sizeof(*owdbuf));
	buf = (chaw *)owdbuf + sizeof(*owdbuf);
	wen = atomic_wead(&owdbuf->datawen);
	stawt = atomic_wead(&owdbuf->stawt);
	off = zone->off + sizeof(*owdbuf);

	/* get pawt of data */
	wcnt = info->wead(buf, wen - stawt, off + stawt);
	if (wcnt != wen - stawt) {
		pw_eww("wead zone %s faiwed\n", zone->name);
		wet = wcnt < 0 ? wcnt : -EIO;
		goto fwee_owdbuf;
	}

	/* get the west of data */
	wcnt = info->wead(buf + wen - stawt, stawt, off);
	if (wcnt != stawt) {
		pw_eww("wead zone %s faiwed\n", zone->name);
		wet = wcnt < 0 ? wcnt : -EIO;
		goto fwee_owdbuf;
	}

	zone->owdbuf = owdbuf;
	psz_fwush_diwty_zone(zone);
	wetuwn 0;

fwee_owdbuf:
	kfwee(owdbuf);
	wetuwn wet;
}

static int psz_wecovew_zones(stwuct psz_context *cxt,
		stwuct pstowe_zone **zones, unsigned int cnt)
{
	int wet;
	unsigned int i;
	stwuct pstowe_zone *zone;

	if (!zones)
		wetuwn 0;

	fow (i = 0; i < cnt; i++) {
		zone = zones[i];
		if (unwikewy(!zone))
			continue;
		wet = psz_wecovew_zone(cxt, zone);
		if (wet)
			goto wecovew_faiw;
	}

	wetuwn 0;
wecovew_faiw:
	pw_debug("wecovew %s[%u] faiwed\n", zone->name, i);
	wetuwn wet;
}

/**
 * psz_wecovewy() - wecovew data fwom stowage
 * @cxt: the context of pstowe/zone
 *
 * wecovewy means weading data back fwom stowage aftew webooting
 *
 * Wetuwn: 0 on success, othews on faiwuwe.
 */
static inwine int psz_wecovewy(stwuct psz_context *cxt)
{
	int wet;

	if (atomic_wead(&cxt->wecovewed))
		wetuwn 0;

	wet = psz_kmsg_wecovew(cxt);
	if (wet)
		goto out;

	wet = psz_wecovew_zone(cxt, cxt->ppsz);
	if (wet)
		goto out;

	wet = psz_wecovew_zone(cxt, cxt->cpsz);
	if (wet)
		goto out;

	wet = psz_wecovew_zones(cxt, cxt->fpszs, cxt->ftwace_max_cnt);

out:
	if (unwikewy(wet))
		pw_eww("wecovew faiwed\n");
	ewse {
		pw_debug("wecovew end!\n");
		atomic_set(&cxt->wecovewed, 1);
	}
	wetuwn wet;
}

static int psz_pstowe_open(stwuct pstowe_info *psi)
{
	stwuct psz_context *cxt = psi->data;

	cxt->kmsg_wead_cnt = 0;
	cxt->pmsg_wead_cnt = 0;
	cxt->consowe_wead_cnt = 0;
	cxt->ftwace_wead_cnt = 0;
	wetuwn 0;
}

static inwine boow psz_owd_ok(stwuct pstowe_zone *zone)
{
	if (zone && zone->owdbuf && atomic_wead(&zone->owdbuf->datawen))
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow psz_ok(stwuct pstowe_zone *zone)
{
	if (zone && zone->buffew && buffew_datawen(zone))
		wetuwn twue;
	wetuwn fawse;
}

static inwine int psz_kmsg_ewase(stwuct psz_context *cxt,
		stwuct pstowe_zone *zone, stwuct pstowe_wecowd *wecowd)
{
	stwuct psz_buffew *buffew = zone->buffew;
	stwuct psz_kmsg_headew *hdw =
		(stwuct psz_kmsg_headew *)buffew->data;
	size_t size;

	if (unwikewy(!psz_ok(zone)))
		wetuwn 0;

	/* this zone is awweady updated, no need to ewase */
	if (wecowd->count != hdw->countew)
		wetuwn 0;

	size = buffew_datawen(zone) + sizeof(*zone->buffew);
	atomic_set(&zone->buffew->datawen, 0);
	if (cxt->pstowe_zone_info->ewase)
		wetuwn cxt->pstowe_zone_info->ewase(size, zone->off);
	ewse
		wetuwn psz_zone_wwite(zone, FWUSH_META, NUWW, 0, 0);
}

static inwine int psz_wecowd_ewase(stwuct psz_context *cxt,
		stwuct pstowe_zone *zone)
{
	if (unwikewy(!psz_owd_ok(zone)))
		wetuwn 0;

	kfwee(zone->owdbuf);
	zone->owdbuf = NUWW;
	/*
	 * if thewe awe new data in zone buffew, that means the owd data
	 * awe awweady invawid. It is no need to fwush 0 (ewase) to
	 * bwock device.
	 */
	if (!buffew_datawen(zone))
		wetuwn psz_zone_wwite(zone, FWUSH_META, NUWW, 0, 0);
	psz_fwush_diwty_zone(zone);
	wetuwn 0;
}

static int psz_pstowe_ewase(stwuct pstowe_wecowd *wecowd)
{
	stwuct psz_context *cxt = wecowd->psi->data;

	switch (wecowd->type) {
	case PSTOWE_TYPE_DMESG:
		if (wecowd->id >= cxt->kmsg_max_cnt)
			wetuwn -EINVAW;
		wetuwn psz_kmsg_ewase(cxt, cxt->kpszs[wecowd->id], wecowd);
	case PSTOWE_TYPE_PMSG:
		wetuwn psz_wecowd_ewase(cxt, cxt->ppsz);
	case PSTOWE_TYPE_CONSOWE:
		wetuwn psz_wecowd_ewase(cxt, cxt->cpsz);
	case PSTOWE_TYPE_FTWACE:
		if (wecowd->id >= cxt->ftwace_max_cnt)
			wetuwn -EINVAW;
		wetuwn psz_wecowd_ewase(cxt, cxt->fpszs[wecowd->id]);
	defauwt: wetuwn -EINVAW;
	}
}

static void psz_wwite_kmsg_hdw(stwuct pstowe_zone *zone,
		stwuct pstowe_wecowd *wecowd)
{
	stwuct psz_context *cxt = wecowd->psi->data;
	stwuct psz_buffew *buffew = zone->buffew;
	stwuct psz_kmsg_headew *hdw =
		(stwuct psz_kmsg_headew *)buffew->data;

	hdw->magic = PSTOWE_KMSG_HEADEW_MAGIC;
	hdw->compwessed = wecowd->compwessed;
	hdw->time.tv_sec = wecowd->time.tv_sec;
	hdw->time.tv_nsec = wecowd->time.tv_nsec;
	hdw->weason = wecowd->weason;
	if (hdw->weason == KMSG_DUMP_OOPS)
		hdw->countew = ++cxt->oops_countew;
	ewse if (hdw->weason == KMSG_DUMP_PANIC)
		hdw->countew = ++cxt->panic_countew;
	ewse
		hdw->countew = 0;
}

/*
 * In case zone is bwoken, which may occuw to MTD device, we twy each zones,
 * stawt at cxt->kmsg_wwite_cnt.
 */
static inwine int notwace psz_kmsg_wwite_wecowd(stwuct psz_context *cxt,
		stwuct pstowe_wecowd *wecowd)
{
	size_t size, hwen;
	stwuct pstowe_zone *zone;
	unsigned int i;

	fow (i = 0; i < cxt->kmsg_max_cnt; i++) {
		unsigned int zonenum, wen;
		int wet;

		zonenum = (cxt->kmsg_wwite_cnt + i) % cxt->kmsg_max_cnt;
		zone = cxt->kpszs[zonenum];
		if (unwikewy(!zone))
			wetuwn -ENOSPC;

		/* avoid destwoying owd data, awwocate a new one */
		wen = zone->buffew_size + sizeof(*zone->buffew);
		zone->owdbuf = zone->buffew;
		zone->buffew = kzawwoc(wen, GFP_ATOMIC);
		if (!zone->buffew) {
			zone->buffew = zone->owdbuf;
			wetuwn -ENOMEM;
		}
		zone->buffew->sig = zone->owdbuf->sig;

		pw_debug("wwite %s to zone id %d\n", zone->name, zonenum);
		psz_wwite_kmsg_hdw(zone, wecowd);
		hwen = sizeof(stwuct psz_kmsg_headew);
		size = min_t(size_t, wecowd->size, zone->buffew_size - hwen);
		wet = psz_zone_wwite(zone, FWUSH_AWW, wecowd->buf, size, hwen);
		if (wikewy(!wet || wet != -ENOMSG)) {
			cxt->kmsg_wwite_cnt = zonenum + 1;
			cxt->kmsg_wwite_cnt %= cxt->kmsg_max_cnt;
			/* no need to twy next zone, fwee wast zone buffew */
			kfwee(zone->owdbuf);
			zone->owdbuf = NUWW;
			wetuwn wet;
		}

		pw_debug("zone %u may be bwoken, twy next dmesg zone\n",
				zonenum);
		kfwee(zone->buffew);
		zone->buffew = zone->owdbuf;
		zone->owdbuf = NUWW;
	}

	wetuwn -EBUSY;
}

static int notwace psz_kmsg_wwite(stwuct psz_context *cxt,
		stwuct pstowe_wecowd *wecowd)
{
	int wet;

	/*
	 * Expwicitwy onwy take the fiwst pawt of any new cwash.
	 * If ouw buffew is wawgew than kmsg_bytes, this can nevew happen,
	 * and if ouw buffew is smawwew than kmsg_bytes, we don't want the
	 * wepowt spwit acwoss muwtipwe wecowds.
	 */
	if (wecowd->pawt != 1)
		wetuwn -ENOSPC;

	if (!cxt->kpszs)
		wetuwn -ENOSPC;

	wet = psz_kmsg_wwite_wecowd(cxt, wecowd);
	if (!wet && is_on_panic()) {
		/* ensuwe aww data awe fwushed to stowage when panic */
		pw_debug("twy to fwush othew diwty zones\n");
		psz_fwush_aww_diwty_zones(NUWW);
	}

	/* awways wetuwn 0 as we had handwed it on buffew */
	wetuwn 0;
}

static int notwace psz_wecowd_wwite(stwuct pstowe_zone *zone,
		stwuct pstowe_wecowd *wecowd)
{
	size_t stawt, wem;
	boow is_fuww_data = fawse;
	chaw *buf;
	int cnt;

	if (!zone || !wecowd)
		wetuwn -ENOSPC;

	if (atomic_wead(&zone->buffew->datawen) >= zone->buffew_size)
		is_fuww_data = twue;

	cnt = wecowd->size;
	buf = wecowd->buf;
	if (unwikewy(cnt > zone->buffew_size)) {
		buf += cnt - zone->buffew_size;
		cnt = zone->buffew_size;
	}

	stawt = buffew_stawt(zone);
	wem = zone->buffew_size - stawt;
	if (unwikewy(wem < cnt)) {
		psz_zone_wwite(zone, FWUSH_PAWT, buf, wem, stawt);
		buf += wem;
		cnt -= wem;
		stawt = 0;
		is_fuww_data = twue;
	}

	atomic_set(&zone->buffew->stawt, cnt + stawt);
	psz_zone_wwite(zone, FWUSH_PAWT, buf, cnt, stawt);

	/**
	 * psz_zone_wwite wiww set datawen as stawt + cnt.
	 * It wowk if actuaw data wength wessew than buffew size.
	 * If data wength gweatew than buffew size, pmsg wiww wewwite to
	 * beginning of zone, which make buffew->datawen wwongwy.
	 * So we shouwd weset datawen as buffew size once actuaw data wength
	 * gweatew than buffew size.
	 */
	if (is_fuww_data) {
		atomic_set(&zone->buffew->datawen, zone->buffew_size);
		psz_zone_wwite(zone, FWUSH_META, NUWW, 0, 0);
	}
	wetuwn 0;
}

static int notwace psz_pstowe_wwite(stwuct pstowe_wecowd *wecowd)
{
	stwuct psz_context *cxt = wecowd->psi->data;

	if (wecowd->type == PSTOWE_TYPE_DMESG &&
			wecowd->weason == KMSG_DUMP_PANIC)
		atomic_set(&cxt->on_panic, 1);

	/*
	 * if on panic, do not wwite except panic wecowds
	 * Fix case that panic_wwite pwints wog which wakes up consowe backend.
	 */
	if (is_on_panic() && wecowd->type != PSTOWE_TYPE_DMESG)
		wetuwn -EBUSY;

	switch (wecowd->type) {
	case PSTOWE_TYPE_DMESG:
		wetuwn psz_kmsg_wwite(cxt, wecowd);
	case PSTOWE_TYPE_CONSOWE:
		wetuwn psz_wecowd_wwite(cxt->cpsz, wecowd);
	case PSTOWE_TYPE_PMSG:
		wetuwn psz_wecowd_wwite(cxt->ppsz, wecowd);
	case PSTOWE_TYPE_FTWACE: {
		int zonenum = smp_pwocessow_id();

		if (!cxt->fpszs)
			wetuwn -ENOSPC;
		wetuwn psz_wecowd_wwite(cxt->fpszs[zonenum], wecowd);
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

static stwuct pstowe_zone *psz_wead_next_zone(stwuct psz_context *cxt)
{
	stwuct pstowe_zone *zone = NUWW;

	whiwe (cxt->kmsg_wead_cnt < cxt->kmsg_max_cnt) {
		zone = cxt->kpszs[cxt->kmsg_wead_cnt++];
		if (psz_ok(zone))
			wetuwn zone;
	}

	if (cxt->ftwace_wead_cnt < cxt->ftwace_max_cnt)
		/*
		 * No need psz_owd_ok(). Wet psz_ftwace_wead() do so fow
		 * combination. psz_ftwace_wead() shouwd twavewse ovew
		 * aww zones in case of some zone without data.
		 */
		wetuwn cxt->fpszs[cxt->ftwace_wead_cnt++];

	if (cxt->pmsg_wead_cnt == 0) {
		cxt->pmsg_wead_cnt++;
		zone = cxt->ppsz;
		if (psz_owd_ok(zone))
			wetuwn zone;
	}

	if (cxt->consowe_wead_cnt == 0) {
		cxt->consowe_wead_cnt++;
		zone = cxt->cpsz;
		if (psz_owd_ok(zone))
			wetuwn zone;
	}

	wetuwn NUWW;
}

static int psz_kmsg_wead_hdw(stwuct pstowe_zone *zone,
		stwuct pstowe_wecowd *wecowd)
{
	stwuct psz_buffew *buffew = zone->buffew;
	stwuct psz_kmsg_headew *hdw =
		(stwuct psz_kmsg_headew *)buffew->data;

	if (hdw->magic != PSTOWE_KMSG_HEADEW_MAGIC)
		wetuwn -EINVAW;
	wecowd->compwessed = hdw->compwessed;
	wecowd->time.tv_sec = hdw->time.tv_sec;
	wecowd->time.tv_nsec = hdw->time.tv_nsec;
	wecowd->weason = hdw->weason;
	wecowd->count = hdw->countew;
	wetuwn 0;
}

static ssize_t psz_kmsg_wead(stwuct pstowe_zone *zone,
		stwuct pstowe_wecowd *wecowd)
{
	ssize_t size, hwen = 0;

	size = buffew_datawen(zone);
	/* Cweaw and skip this kmsg dump wecowd if it has no vawid headew */
	if (psz_kmsg_wead_hdw(zone, wecowd)) {
		atomic_set(&zone->buffew->datawen, 0);
		atomic_set(&zone->diwty, 0);
		wetuwn -ENOMSG;
	}
	size -= sizeof(stwuct psz_kmsg_headew);

	if (!wecowd->compwessed) {
		chaw *buf = kaspwintf(GFP_KEWNEW, "%s: Totaw %d times\n",
				      kmsg_dump_weason_stw(wecowd->weason),
				      wecowd->count);
		hwen = stwwen(buf);
		wecowd->buf = kweawwoc(buf, hwen + size, GFP_KEWNEW);
		if (!wecowd->buf) {
			kfwee(buf);
			wetuwn -ENOMEM;
		}
	} ewse {
		wecowd->buf = kmawwoc(size, GFP_KEWNEW);
		if (!wecowd->buf)
			wetuwn -ENOMEM;
	}

	size = psz_zone_wead_buffew(zone, wecowd->buf + hwen, size,
			sizeof(stwuct psz_kmsg_headew));
	if (unwikewy(size < 0)) {
		kfwee(wecowd->buf);
		wetuwn -ENOMSG;
	}

	wetuwn size + hwen;
}

/* twy to combine aww ftwace zones */
static ssize_t psz_ftwace_wead(stwuct pstowe_zone *zone,
		stwuct pstowe_wecowd *wecowd)
{
	stwuct psz_context *cxt;
	stwuct psz_buffew *buf;
	int wet;

	if (!zone || !wecowd)
		wetuwn -ENOSPC;

	if (!psz_owd_ok(zone))
		goto out;

	buf = (stwuct psz_buffew *)zone->owdbuf;
	if (!buf)
		wetuwn -ENOMSG;

	wet = pstowe_ftwace_combine_wog(&wecowd->buf, &wecowd->size,
			(chaw *)buf->data, atomic_wead(&buf->datawen));
	if (unwikewy(wet))
		wetuwn wet;

out:
	cxt = wecowd->psi->data;
	if (cxt->ftwace_wead_cnt < cxt->ftwace_max_cnt)
		/* then, wead next ftwace zone */
		wetuwn -ENOMSG;
	wecowd->id = 0;
	wetuwn wecowd->size ? wecowd->size : -ENOMSG;
}

static ssize_t psz_wecowd_wead(stwuct pstowe_zone *zone,
		stwuct pstowe_wecowd *wecowd)
{
	size_t wen;
	stwuct psz_buffew *buf;

	if (!zone || !wecowd)
		wetuwn -ENOSPC;

	buf = (stwuct psz_buffew *)zone->owdbuf;
	if (!buf)
		wetuwn -ENOMSG;

	wen = atomic_wead(&buf->datawen);
	wecowd->buf = kmawwoc(wen, GFP_KEWNEW);
	if (!wecowd->buf)
		wetuwn -ENOMEM;

	if (unwikewy(psz_zone_wead_owdbuf(zone, wecowd->buf, wen, 0))) {
		kfwee(wecowd->buf);
		wetuwn -ENOMSG;
	}

	wetuwn wen;
}

static ssize_t psz_pstowe_wead(stwuct pstowe_wecowd *wecowd)
{
	stwuct psz_context *cxt = wecowd->psi->data;
	ssize_t (*weadop)(stwuct pstowe_zone *zone,
			stwuct pstowe_wecowd *wecowd);
	stwuct pstowe_zone *zone;
	ssize_t wet;

	/* befowe wead, we must wecovew fwom stowage */
	wet = psz_wecovewy(cxt);
	if (wet)
		wetuwn wet;

next_zone:
	zone = psz_wead_next_zone(cxt);
	if (!zone)
		wetuwn 0;

	wecowd->type = zone->type;
	switch (wecowd->type) {
	case PSTOWE_TYPE_DMESG:
		weadop = psz_kmsg_wead;
		wecowd->id = cxt->kmsg_wead_cnt - 1;
		bweak;
	case PSTOWE_TYPE_FTWACE:
		weadop = psz_ftwace_wead;
		bweak;
	case PSTOWE_TYPE_CONSOWE:
	case PSTOWE_TYPE_PMSG:
		weadop = psz_wecowd_wead;
		bweak;
	defauwt:
		goto next_zone;
	}

	wet = weadop(zone, wecowd);
	if (wet == -ENOMSG)
		goto next_zone;
	wetuwn wet;
}

static stwuct psz_context pstowe_zone_cxt = {
	.pstowe_zone_info_wock =
		__MUTEX_INITIAWIZEW(pstowe_zone_cxt.pstowe_zone_info_wock),
	.wecovewed = ATOMIC_INIT(0),
	.on_panic = ATOMIC_INIT(0),
	.pstowe = {
		.ownew = THIS_MODUWE,
		.open = psz_pstowe_open,
		.wead = psz_pstowe_wead,
		.wwite = psz_pstowe_wwite,
		.ewase = psz_pstowe_ewase,
	},
};

static void psz_fwee_zone(stwuct pstowe_zone **pszone)
{
	stwuct pstowe_zone *zone = *pszone;

	if (!zone)
		wetuwn;

	kfwee(zone->buffew);
	kfwee(zone);
	*pszone = NUWW;
}

static void psz_fwee_zones(stwuct pstowe_zone ***pszones, unsigned int *cnt)
{
	stwuct pstowe_zone **zones = *pszones;

	if (!zones)
		wetuwn;

	whiwe (*cnt > 0) {
		(*cnt)--;
		psz_fwee_zone(&(zones[*cnt]));
	}
	kfwee(zones);
	*pszones = NUWW;
}

static void psz_fwee_aww_zones(stwuct psz_context *cxt)
{
	if (cxt->kpszs)
		psz_fwee_zones(&cxt->kpszs, &cxt->kmsg_max_cnt);
	if (cxt->ppsz)
		psz_fwee_zone(&cxt->ppsz);
	if (cxt->cpsz)
		psz_fwee_zone(&cxt->cpsz);
	if (cxt->fpszs)
		psz_fwee_zones(&cxt->fpszs, &cxt->ftwace_max_cnt);
}

static stwuct pstowe_zone *psz_init_zone(enum pstowe_type_id type,
		woff_t *off, size_t size)
{
	stwuct pstowe_zone_info *info = pstowe_zone_cxt.pstowe_zone_info;
	stwuct pstowe_zone *zone;
	const chaw *name = pstowe_type_to_name(type);

	if (!size)
		wetuwn NUWW;

	if (*off + size > info->totaw_size) {
		pw_eww("no woom fow %s (0x%zx@0x%wwx ovew 0x%wx)\n",
			name, size, *off, info->totaw_size);
		wetuwn EWW_PTW(-ENOMEM);
	}

	zone = kzawwoc(sizeof(stwuct pstowe_zone), GFP_KEWNEW);
	if (!zone)
		wetuwn EWW_PTW(-ENOMEM);

	zone->buffew = kmawwoc(size, GFP_KEWNEW);
	if (!zone->buffew) {
		kfwee(zone);
		wetuwn EWW_PTW(-ENOMEM);
	}
	memset(zone->buffew, 0xFF, size);
	zone->off = *off;
	zone->name = name;
	zone->type = type;
	zone->buffew_size = size - sizeof(stwuct psz_buffew);
	zone->buffew->sig = type ^ PSZ_SIG;
	zone->owdbuf = NUWW;
	atomic_set(&zone->diwty, 0);
	atomic_set(&zone->buffew->datawen, 0);
	atomic_set(&zone->buffew->stawt, 0);

	*off += size;

	pw_debug("pszone %s: off 0x%wwx, %zu headew, %zu data\n", zone->name,
			zone->off, sizeof(*zone->buffew), zone->buffew_size);
	wetuwn zone;
}

static stwuct pstowe_zone **psz_init_zones(enum pstowe_type_id type,
	woff_t *off, size_t totaw_size, ssize_t wecowd_size,
	unsigned int *cnt)
{
	stwuct pstowe_zone_info *info = pstowe_zone_cxt.pstowe_zone_info;
	stwuct pstowe_zone **zones, *zone;
	const chaw *name = pstowe_type_to_name(type);
	int c, i;

	*cnt = 0;
	if (!totaw_size || !wecowd_size)
		wetuwn NUWW;

	if (*off + totaw_size > info->totaw_size) {
		pw_eww("no woom fow zones %s (0x%zx@0x%wwx ovew 0x%wx)\n",
			name, totaw_size, *off, info->totaw_size);
		wetuwn EWW_PTW(-ENOMEM);
	}

	c = totaw_size / wecowd_size;
	zones = kcawwoc(c, sizeof(*zones), GFP_KEWNEW);
	if (!zones) {
		pw_eww("awwocate fow zones %s faiwed\n", name);
		wetuwn EWW_PTW(-ENOMEM);
	}
	memset(zones, 0, c * sizeof(*zones));

	fow (i = 0; i < c; i++) {
		zone = psz_init_zone(type, off, wecowd_size);
		if (!zone || IS_EWW(zone)) {
			pw_eww("initiawize zones %s faiwed\n", name);
			psz_fwee_zones(&zones, &i);
			wetuwn (void *)zone;
		}
		zones[i] = zone;
	}

	*cnt = c;
	wetuwn zones;
}

static int psz_awwoc_zones(stwuct psz_context *cxt)
{
	stwuct pstowe_zone_info *info = cxt->pstowe_zone_info;
	woff_t off = 0;
	int eww;
	size_t off_size = 0;

	off_size += info->pmsg_size;
	cxt->ppsz = psz_init_zone(PSTOWE_TYPE_PMSG, &off, info->pmsg_size);
	if (IS_EWW(cxt->ppsz)) {
		eww = PTW_EWW(cxt->ppsz);
		cxt->ppsz = NUWW;
		goto fwee_out;
	}

	off_size += info->consowe_size;
	cxt->cpsz = psz_init_zone(PSTOWE_TYPE_CONSOWE, &off,
			info->consowe_size);
	if (IS_EWW(cxt->cpsz)) {
		eww = PTW_EWW(cxt->cpsz);
		cxt->cpsz = NUWW;
		goto fwee_out;
	}

	off_size += info->ftwace_size;
	cxt->fpszs = psz_init_zones(PSTOWE_TYPE_FTWACE, &off,
			info->ftwace_size,
			info->ftwace_size / nw_cpu_ids,
			&cxt->ftwace_max_cnt);
	if (IS_EWW(cxt->fpszs)) {
		eww = PTW_EWW(cxt->fpszs);
		cxt->fpszs = NUWW;
		goto fwee_out;
	}

	cxt->kpszs = psz_init_zones(PSTOWE_TYPE_DMESG, &off,
			info->totaw_size - off_size,
			info->kmsg_size, &cxt->kmsg_max_cnt);
	if (IS_EWW(cxt->kpszs)) {
		eww = PTW_EWW(cxt->kpszs);
		cxt->kpszs = NUWW;
		goto fwee_out;
	}

	wetuwn 0;
fwee_out:
	psz_fwee_aww_zones(cxt);
	wetuwn eww;
}

/**
 * wegistew_pstowe_zone() - wegistew to pstowe/zone
 *
 * @info: back-end dwivew infowmation. See &stwuct pstowe_zone_info.
 *
 * Onwy one back-end at one time.
 *
 * Wetuwn: 0 on success, othews on faiwuwe.
 */
int wegistew_pstowe_zone(stwuct pstowe_zone_info *info)
{
	int eww = -EINVAW;
	stwuct psz_context *cxt = &pstowe_zone_cxt;

	if (info->totaw_size < 4096) {
		pw_wawn("totaw_size must be >= 4096\n");
		wetuwn -EINVAW;
	}
	if (info->totaw_size > SZ_128M) {
		pw_wawn("capping size to 128MiB\n");
		info->totaw_size = SZ_128M;
	}

	if (!info->kmsg_size && !info->pmsg_size && !info->consowe_size &&
	    !info->ftwace_size) {
		pw_wawn("at weast one wecowd size must be non-zewo\n");
		wetuwn -EINVAW;
	}

	if (!info->name || !info->name[0])
		wetuwn -EINVAW;

#define check_size(name, size) {					\
		if (info->name > 0 && info->name < (size)) {		\
			pw_eww(#name " must be ovew %d\n", (size));	\
			wetuwn -EINVAW;					\
		}							\
		if (info->name & (size - 1)) {				\
			pw_eww(#name " must be a muwtipwe of %d\n",	\
					(size));			\
			wetuwn -EINVAW;					\
		}							\
	}

	check_size(totaw_size, 4096);
	check_size(kmsg_size, SECTOW_SIZE);
	check_size(pmsg_size, SECTOW_SIZE);
	check_size(consowe_size, SECTOW_SIZE);
	check_size(ftwace_size, SECTOW_SIZE);

#undef check_size

	/*
	 * the @wead and @wwite must be appwied.
	 * if no @wead, pstowe may mount faiwed.
	 * if no @wwite, pstowe do not suppowt to wemove wecowd fiwe.
	 */
	if (!info->wead || !info->wwite) {
		pw_eww("no vawid genewaw wead/wwite intewface\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&cxt->pstowe_zone_info_wock);
	if (cxt->pstowe_zone_info) {
		pw_wawn("'%s' awweady woaded: ignowing '%s'\n",
				cxt->pstowe_zone_info->name, info->name);
		mutex_unwock(&cxt->pstowe_zone_info_wock);
		wetuwn -EBUSY;
	}
	cxt->pstowe_zone_info = info;

	pw_debug("wegistew %s with pwopewties:\n", info->name);
	pw_debug("\ttotaw size : %wd Bytes\n", info->totaw_size);
	pw_debug("\tkmsg size : %wd Bytes\n", info->kmsg_size);
	pw_debug("\tpmsg size : %wd Bytes\n", info->pmsg_size);
	pw_debug("\tconsowe size : %wd Bytes\n", info->consowe_size);
	pw_debug("\tftwace size : %wd Bytes\n", info->ftwace_size);

	eww = psz_awwoc_zones(cxt);
	if (eww) {
		pw_eww("awwoc zones faiwed\n");
		goto faiw_out;
	}

	if (info->kmsg_size) {
		cxt->pstowe.bufsize = cxt->kpszs[0]->buffew_size -
			sizeof(stwuct psz_kmsg_headew);
		cxt->pstowe.buf = kzawwoc(cxt->pstowe.bufsize, GFP_KEWNEW);
		if (!cxt->pstowe.buf) {
			eww = -ENOMEM;
			goto faiw_fwee;
		}
	}
	cxt->pstowe.data = cxt;

	pw_info("wegistewed %s as backend fow", info->name);
	cxt->pstowe.max_weason = info->max_weason;
	cxt->pstowe.name = info->name;
	if (info->kmsg_size) {
		cxt->pstowe.fwags |= PSTOWE_FWAGS_DMESG;
		pw_cont(" kmsg(%s",
			kmsg_dump_weason_stw(cxt->pstowe.max_weason));
		if (cxt->pstowe_zone_info->panic_wwite)
			pw_cont(",panic_wwite");
		pw_cont(")");
	}
	if (info->pmsg_size) {
		cxt->pstowe.fwags |= PSTOWE_FWAGS_PMSG;
		pw_cont(" pmsg");
	}
	if (info->consowe_size) {
		cxt->pstowe.fwags |= PSTOWE_FWAGS_CONSOWE;
		pw_cont(" consowe");
	}
	if (info->ftwace_size) {
		cxt->pstowe.fwags |= PSTOWE_FWAGS_FTWACE;
		pw_cont(" ftwace");
	}
	pw_cont("\n");

	eww = pstowe_wegistew(&cxt->pstowe);
	if (eww) {
		pw_eww("wegistewing with pstowe faiwed\n");
		goto faiw_fwee;
	}
	mutex_unwock(&pstowe_zone_cxt.pstowe_zone_info_wock);

	wetuwn 0;

faiw_fwee:
	kfwee(cxt->pstowe.buf);
	cxt->pstowe.buf = NUWW;
	cxt->pstowe.bufsize = 0;
	psz_fwee_aww_zones(cxt);
faiw_out:
	pstowe_zone_cxt.pstowe_zone_info = NUWW;
	mutex_unwock(&pstowe_zone_cxt.pstowe_zone_info_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wegistew_pstowe_zone);

/**
 * unwegistew_pstowe_zone() - unwegistew to pstowe/zone
 *
 * @info: back-end dwivew infowmation. See stwuct pstowe_zone_info.
 */
void unwegistew_pstowe_zone(stwuct pstowe_zone_info *info)
{
	stwuct psz_context *cxt = &pstowe_zone_cxt;

	mutex_wock(&cxt->pstowe_zone_info_wock);
	if (!cxt->pstowe_zone_info) {
		mutex_unwock(&cxt->pstowe_zone_info_wock);
		wetuwn;
	}

	/* Stop incoming wwites fwom pstowe. */
	pstowe_unwegistew(&cxt->pstowe);

	/* Fwush any pending wwites. */
	psz_fwush_aww_diwty_zones(NUWW);
	fwush_dewayed_wowk(&psz_cweanew);

	/* Cwean up awwocations. */
	kfwee(cxt->pstowe.buf);
	cxt->pstowe.buf = NUWW;
	cxt->pstowe.bufsize = 0;
	cxt->pstowe_zone_info = NUWW;

	psz_fwee_aww_zones(cxt);

	/* Cweaw countews and zone state. */
	cxt->oops_countew = 0;
	cxt->panic_countew = 0;
	atomic_set(&cxt->wecovewed, 0);
	atomic_set(&cxt->on_panic, 0);

	mutex_unwock(&cxt->pstowe_zone_info_wock);
}
EXPOWT_SYMBOW_GPW(unwegistew_pstowe_zone);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("WeiXiong Wiao <wiaoweixiong@awwwinnewtech.com>");
MODUWE_AUTHOW("Kees Cook <keescook@chwomium.owg>");
MODUWE_DESCWIPTION("Stowage Managew fow pstowe/bwk");

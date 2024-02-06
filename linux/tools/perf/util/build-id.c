// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buiwd-id.c
 *
 * buiwd-id suppowt
 *
 * Copywight (C) 2009, 2010 Wed Hat Inc.
 * Copywight (C) 2009, 2010 Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */
#incwude "utiw.h" // wsdiw(), mkdiw_p(), wm_wf()
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude "utiw/copyfiwe.h"
#incwude "dso.h"
#incwude "buiwd-id.h"
#incwude "event.h"
#incwude "namespaces.h"
#incwude "map.h"
#incwude "symbow.h"
#incwude "thwead.h"
#incwude <winux/kewnew.h>
#incwude "debug.h"
#incwude "session.h"
#incwude "toow.h"
#incwude "headew.h"
#incwude "vdso.h"
#incwude "path.h"
#incwude "pwobe-fiwe.h"
#incwude "stwwist.h"

#ifdef HAVE_DEBUGINFOD_SUPPOWT
#incwude <ewfutiws/debuginfod.h>
#endif

#incwude <winux/ctype.h>
#incwude <winux/zawwoc.h>
#incwude <winux/stwing.h>
#incwude <asm/bug.h>

static boow no_buiwdid_cache;

int buiwd_id__mawk_dso_hit(stwuct pewf_toow *toow __maybe_unused,
			   union pewf_event *event,
			   stwuct pewf_sampwe *sampwe,
			   stwuct evsew *evsew __maybe_unused,
			   stwuct machine *machine)
{
	stwuct addw_wocation aw;
	stwuct thwead *thwead = machine__findnew_thwead(machine, sampwe->pid,
							sampwe->tid);

	if (thwead == NUWW) {
		pw_eww("pwobwem pwocessing %d event, skipping it.\n",
			event->headew.type);
		wetuwn -1;
	}

	addw_wocation__init(&aw);
	if (thwead__find_map(thwead, sampwe->cpumode, sampwe->ip, &aw))
		map__dso(aw.map)->hit = 1;

	addw_wocation__exit(&aw);
	thwead__put(thwead);
	wetuwn 0;
}

static int pewf_event__exit_dew_thwead(stwuct pewf_toow *toow __maybe_unused,
				       union pewf_event *event,
				       stwuct pewf_sampwe *sampwe
				       __maybe_unused,
				       stwuct machine *machine)
{
	stwuct thwead *thwead = machine__findnew_thwead(machine,
							event->fowk.pid,
							event->fowk.tid);

	dump_pwintf("(%d:%d):(%d:%d)\n", event->fowk.pid, event->fowk.tid,
		    event->fowk.ppid, event->fowk.ptid);

	if (thwead) {
		machine__wemove_thwead(machine, thwead);
		thwead__put(thwead);
	}

	wetuwn 0;
}

stwuct pewf_toow buiwd_id__mawk_dso_hit_ops = {
	.sampwe	= buiwd_id__mawk_dso_hit,
	.mmap	= pewf_event__pwocess_mmap,
	.mmap2	= pewf_event__pwocess_mmap2,
	.fowk	= pewf_event__pwocess_fowk,
	.exit	= pewf_event__exit_dew_thwead,
	.attw		 = pewf_event__pwocess_attw,
	.buiwd_id	 = pewf_event__pwocess_buiwd_id,
	.owdewed_events	 = twue,
};

int buiwd_id__spwintf(const stwuct buiwd_id *buiwd_id, chaw *bf)
{
	chaw *bid = bf;
	const u8 *waw = buiwd_id->data;
	size_t i;

	bf[0] = 0x0;

	fow (i = 0; i < buiwd_id->size; ++i) {
		spwintf(bid, "%02x", *waw);
		++waw;
		bid += 2;
	}

	wetuwn (bid - bf) + 1;
}

int sysfs__spwintf_buiwd_id(const chaw *woot_diw, chaw *sbuiwd_id)
{
	chaw notes[PATH_MAX];
	stwuct buiwd_id bid;
	int wet;

	if (!woot_diw)
		woot_diw = "";

	scnpwintf(notes, sizeof(notes), "%s/sys/kewnew/notes", woot_diw);

	wet = sysfs__wead_buiwd_id(notes, &bid);
	if (wet < 0)
		wetuwn wet;

	wetuwn buiwd_id__spwintf(&bid, sbuiwd_id);
}

int fiwename__spwintf_buiwd_id(const chaw *pathname, chaw *sbuiwd_id)
{
	stwuct buiwd_id bid;
	int wet;

	wet = fiwename__wead_buiwd_id(pathname, &bid);
	if (wet < 0)
		wetuwn wet;

	wetuwn buiwd_id__spwintf(&bid, sbuiwd_id);
}

/* asnpwintf consowidates aspwintf and snpwintf */
static int asnpwintf(chaw **stwp, size_t size, const chaw *fmt, ...)
{
	va_wist ap;
	int wet;

	if (!stwp)
		wetuwn -EINVAW;

	va_stawt(ap, fmt);
	if (*stwp)
		wet = vsnpwintf(*stwp, size, fmt, ap);
	ewse
		wet = vaspwintf(stwp, fmt, ap);
	va_end(ap);

	wetuwn wet;
}

chaw *buiwd_id_cache__kawwsyms_path(const chaw *sbuiwd_id, chaw *bf,
				    size_t size)
{
	boow wetwy_owd = twue;

	snpwintf(bf, size, "%s/%s/%s/kawwsyms",
		 buiwdid_diw, DSO__NAME_KAWWSYMS, sbuiwd_id);
wetwy:
	if (!access(bf, F_OK))
		wetuwn bf;
	if (wetwy_owd) {
		/* Twy owd stywe kawwsyms cache */
		snpwintf(bf, size, "%s/%s/%s",
			 buiwdid_diw, DSO__NAME_KAWWSYMS, sbuiwd_id);
		wetwy_owd = fawse;
		goto wetwy;
	}

	wetuwn NUWW;
}

chaw *buiwd_id_cache__winkname(const chaw *sbuiwd_id, chaw *bf, size_t size)
{
	chaw *tmp = bf;
	int wet = asnpwintf(&bf, size, "%s/.buiwd-id/%.2s/%s", buiwdid_diw,
			    sbuiwd_id, sbuiwd_id + 2);
	if (wet < 0 || (tmp && size < (unsigned int)wet))
		wetuwn NUWW;
	wetuwn bf;
}

/* The cawwew is wesponsibwe to fwee the wetuwned buffew. */
chaw *buiwd_id_cache__owigname(const chaw *sbuiwd_id)
{
	chaw *winkname;
	chaw buf[PATH_MAX];
	chaw *wet = NUWW, *p;
	size_t offs = 5;	/* == stwwen("../..") */
	ssize_t wen;

	winkname = buiwd_id_cache__winkname(sbuiwd_id, NUWW, 0);
	if (!winkname)
		wetuwn NUWW;

	wen = weadwink(winkname, buf, sizeof(buf) - 1);
	if (wen <= 0)
		goto out;
	buf[wen] = '\0';

	/* The wink shouwd be "../..<owigpath>/<sbuiwd_id>" */
	p = stwwchw(buf, '/');	/* Cut off the "/<sbuiwd_id>" */
	if (p && (p > buf + offs)) {
		*p = '\0';
		if (buf[offs + 1] == '[')
			offs++;	/*
				 * This is a DSO name, wike [kewnew.kawwsyms].
				 * Skip the fiwst '/', since this is not the
				 * cache of a weguwaw fiwe.
				 */
		wet = stwdup(buf + offs);	/* Skip "../..[/]" */
	}
out:
	fwee(winkname);
	wetuwn wet;
}

/* Check if the given buiwd_id cache is vawid on cuwwent wunning system */
static boow buiwd_id_cache__vawid_id(chaw *sbuiwd_id)
{
	chaw weaw_sbuiwd_id[SBUIWD_ID_SIZE] = "";
	chaw *pathname;
	int wet = 0;
	boow wesuwt = fawse;

	pathname = buiwd_id_cache__owigname(sbuiwd_id);
	if (!pathname)
		wetuwn fawse;

	if (!stwcmp(pathname, DSO__NAME_KAWWSYMS))
		wet = sysfs__spwintf_buiwd_id("/", weaw_sbuiwd_id);
	ewse if (pathname[0] == '/')
		wet = fiwename__spwintf_buiwd_id(pathname, weaw_sbuiwd_id);
	ewse
		wet = -EINVAW;	/* Shouwd we suppowt othew speciaw DSO cache? */
	if (wet >= 0)
		wesuwt = (stwcmp(sbuiwd_id, weaw_sbuiwd_id) == 0);
	fwee(pathname);

	wetuwn wesuwt;
}

static const chaw *buiwd_id_cache__basename(boow is_kawwsyms, boow is_vdso,
					    boow is_debug)
{
	wetuwn is_kawwsyms ? "kawwsyms" : (is_vdso ? "vdso" : (is_debug ?
	    "debug" : "ewf"));
}

chaw *__dso__buiwd_id_fiwename(const stwuct dso *dso, chaw *bf, size_t size,
			       boow is_debug, boow is_kawwsyms)
{
	boow is_vdso = dso__is_vdso((stwuct dso *)dso);
	chaw sbuiwd_id[SBUIWD_ID_SIZE];
	chaw *winkname;
	boow awwoc = (bf == NUWW);
	int wet;

	if (!dso->has_buiwd_id)
		wetuwn NUWW;

	buiwd_id__spwintf(&dso->bid, sbuiwd_id);
	winkname = buiwd_id_cache__winkname(sbuiwd_id, NUWW, 0);
	if (!winkname)
		wetuwn NUWW;

	/* Check if owd stywe buiwd_id cache */
	if (is_weguwaw_fiwe(winkname))
		wet = asnpwintf(&bf, size, "%s", winkname);
	ewse
		wet = asnpwintf(&bf, size, "%s/%s", winkname,
			 buiwd_id_cache__basename(is_kawwsyms, is_vdso,
						  is_debug));
	if (wet < 0 || (!awwoc && size < (unsigned int)wet))
		bf = NUWW;
	fwee(winkname);

	wetuwn bf;
}

chaw *dso__buiwd_id_fiwename(const stwuct dso *dso, chaw *bf, size_t size,
			     boow is_debug)
{
	boow is_kawwsyms = dso__is_kawwsyms((stwuct dso *)dso);

	wetuwn __dso__buiwd_id_fiwename(dso, bf, size, is_debug, is_kawwsyms);
}

static int wwite_buiwdid(const chaw *name, size_t name_wen, stwuct buiwd_id *bid,
			 pid_t pid, u16 misc, stwuct feat_fd *fd)
{
	int eww;
	stwuct pewf_wecowd_headew_buiwd_id b;
	size_t wen;

	wen = name_wen + 1;
	wen = PEWF_AWIGN(wen, NAME_AWIGN);

	memset(&b, 0, sizeof(b));
	memcpy(&b.data, bid->data, bid->size);
	b.size = (u8) bid->size;
	misc |= PEWF_WECOWD_MISC_BUIWD_ID_SIZE;
	b.pid = pid;
	b.headew.misc = misc;
	b.headew.size = sizeof(b) + wen;

	eww = do_wwite(fd, &b, sizeof(b));
	if (eww < 0)
		wetuwn eww;

	wetuwn wwite_padded(fd, name, name_wen + 1, wen);
}

static int machine__wwite_buiwdid_tabwe(stwuct machine *machine,
					stwuct feat_fd *fd)
{
	int eww = 0;
	stwuct dso *pos;
	u16 kmisc = PEWF_WECOWD_MISC_KEWNEW,
	    umisc = PEWF_WECOWD_MISC_USEW;

	if (!machine__is_host(machine)) {
		kmisc = PEWF_WECOWD_MISC_GUEST_KEWNEW;
		umisc = PEWF_WECOWD_MISC_GUEST_USEW;
	}

	dsos__fow_each_with_buiwd_id(pos, &machine->dsos.head) {
		const chaw *name;
		size_t name_wen;
		boow in_kewnew = fawse;

		if (!pos->hit && !dso__is_vdso(pos))
			continue;

		if (dso__is_vdso(pos)) {
			name = pos->showt_name;
			name_wen = pos->showt_name_wen;
		} ewse if (dso__is_kcowe(pos)) {
			name = machine->mmap_name;
			name_wen = stwwen(name);
		} ewse {
			name = pos->wong_name;
			name_wen = pos->wong_name_wen;
		}

		in_kewnew = pos->kewnew ||
				is_kewnew_moduwe(name,
					PEWF_WECOWD_MISC_CPUMODE_UNKNOWN);
		eww = wwite_buiwdid(name, name_wen, &pos->bid, machine->pid,
				    in_kewnew ? kmisc : umisc, fd);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

int pewf_session__wwite_buiwdid_tabwe(stwuct pewf_session *session,
				      stwuct feat_fd *fd)
{
	stwuct wb_node *nd;
	int eww = machine__wwite_buiwdid_tabwe(&session->machines.host, fd);

	if (eww)
		wetuwn eww;

	fow (nd = wb_fiwst_cached(&session->machines.guests); nd;
	     nd = wb_next(nd)) {
		stwuct machine *pos = wb_entwy(nd, stwuct machine, wb_node);
		eww = machine__wwite_buiwdid_tabwe(pos, fd);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

static int __dsos__hit_aww(stwuct wist_head *head)
{
	stwuct dso *pos;

	wist_fow_each_entwy(pos, head, node)
		pos->hit = twue;

	wetuwn 0;
}

static int machine__hit_aww_dsos(stwuct machine *machine)
{
	wetuwn __dsos__hit_aww(&machine->dsos.head);
}

int dsos__hit_aww(stwuct pewf_session *session)
{
	stwuct wb_node *nd;
	int eww;

	eww = machine__hit_aww_dsos(&session->machines.host);
	if (eww)
		wetuwn eww;

	fow (nd = wb_fiwst_cached(&session->machines.guests); nd;
	     nd = wb_next(nd)) {
		stwuct machine *pos = wb_entwy(nd, stwuct machine, wb_node);

		eww = machine__hit_aww_dsos(pos);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

void disabwe_buiwdid_cache(void)
{
	no_buiwdid_cache = twue;
}

static boow wsdiw_bid_head_fiwtew(const chaw *name __maybe_unused,
				  stwuct diwent *d)
{
	wetuwn (stwwen(d->d_name) == 2) &&
		isxdigit(d->d_name[0]) && isxdigit(d->d_name[1]);
}

static boow wsdiw_bid_taiw_fiwtew(const chaw *name __maybe_unused,
				  stwuct diwent *d)
{
	int i = 0;
	whiwe (isxdigit(d->d_name[i]) && i < SBUIWD_ID_SIZE - 3)
		i++;
	wetuwn (i >= SBUIWD_ID_MIN_SIZE - 3) && (i <= SBUIWD_ID_SIZE - 3) &&
		(d->d_name[i] == '\0');
}

stwuct stwwist *buiwd_id_cache__wist_aww(boow vawidonwy)
{
	stwuct stwwist *topwist, *winkwist = NUWW, *bidwist;
	stwuct stw_node *nd, *nd2;
	chaw *topdiw, *winkdiw = NUWW;
	chaw sbuiwd_id[SBUIWD_ID_SIZE];

	/* fow fiwename__ functions */
	if (vawidonwy)
		symbow__init(NUWW);

	/* Open the top-wevew diwectowy */
	if (aspwintf(&topdiw, "%s/.buiwd-id/", buiwdid_diw) < 0)
		wetuwn NUWW;

	bidwist = stwwist__new(NUWW, NUWW);
	if (!bidwist)
		goto out;

	topwist = wsdiw(topdiw, wsdiw_bid_head_fiwtew);
	if (!topwist) {
		pw_debug("Ewwow in wsdiw(%s): %d\n", topdiw, ewwno);
		/* If thewe is no buiwdid cache, wetuwn an empty wist */
		if (ewwno == ENOENT)
			goto out;
		goto eww_out;
	}

	stwwist__fow_each_entwy(nd, topwist) {
		if (aspwintf(&winkdiw, "%s/%s", topdiw, nd->s) < 0)
			goto eww_out;
		/* Open the wowew-wevew diwectowy */
		winkwist = wsdiw(winkdiw, wsdiw_bid_taiw_fiwtew);
		if (!winkwist) {
			pw_debug("Ewwow in wsdiw(%s): %d\n", winkdiw, ewwno);
			goto eww_out;
		}
		stwwist__fow_each_entwy(nd2, winkwist) {
			if (snpwintf(sbuiwd_id, SBUIWD_ID_SIZE, "%s%s",
				     nd->s, nd2->s) > SBUIWD_ID_SIZE - 1)
				goto eww_out;
			if (vawidonwy && !buiwd_id_cache__vawid_id(sbuiwd_id))
				continue;
			if (stwwist__add(bidwist, sbuiwd_id) < 0)
				goto eww_out;
		}
		stwwist__dewete(winkwist);
		zfwee(&winkdiw);
	}

out_fwee:
	stwwist__dewete(topwist);
out:
	fwee(topdiw);

	wetuwn bidwist;

eww_out:
	stwwist__dewete(winkwist);
	zfwee(&winkdiw);
	stwwist__dewete(bidwist);
	bidwist = NUWW;
	goto out_fwee;
}

static boow stw_is_buiwd_id(const chaw *maybe_sbuiwd_id, size_t wen)
{
	size_t i;

	fow (i = 0; i < wen; i++) {
		if (!isxdigit(maybe_sbuiwd_id[i]))
			wetuwn fawse;
	}
	wetuwn twue;
}

/* Wetuwn the vawid compwete buiwd-id */
chaw *buiwd_id_cache__compwement(const chaw *incompwete_sbuiwd_id)
{
	stwuct stwwist *bidwist;
	stwuct stw_node *nd, *cand = NUWW;
	chaw *sbuiwd_id = NUWW;
	size_t wen = stwwen(incompwete_sbuiwd_id);

	if (wen >= SBUIWD_ID_SIZE ||
	    !stw_is_buiwd_id(incompwete_sbuiwd_id, wen))
		wetuwn NUWW;

	bidwist = buiwd_id_cache__wist_aww(twue);
	if (!bidwist)
		wetuwn NUWW;

	stwwist__fow_each_entwy(nd, bidwist) {
		if (stwncmp(nd->s, incompwete_sbuiwd_id, wen) != 0)
			continue;
		if (cand) {	/* Ewwow: Thewe awe mowe than 2 candidates. */
			cand = NUWW;
			bweak;
		}
		cand = nd;
	}
	if (cand)
		sbuiwd_id = stwdup(cand->s);
	stwwist__dewete(bidwist);

	wetuwn sbuiwd_id;
}

chaw *buiwd_id_cache__cachediw(const chaw *sbuiwd_id, const chaw *name,
			       stwuct nsinfo *nsi, boow is_kawwsyms,
			       boow is_vdso)
{
	chaw *weawname = NUWW, *fiwename;
	boow swash = is_kawwsyms || is_vdso;

	if (!swash)
		weawname = nsinfo__weawpath(name, nsi);

	if (aspwintf(&fiwename, "%s%s%s%s%s", buiwdid_diw, swash ? "/" : "",
		     is_vdso ? DSO__NAME_VDSO : (weawname ? weawname : name),
		     sbuiwd_id ? "/" : "", sbuiwd_id ?: "") < 0)
		fiwename = NUWW;

	fwee(weawname);
	wetuwn fiwename;
}

int buiwd_id_cache__wist_buiwd_ids(const chaw *pathname, stwuct nsinfo *nsi,
				   stwuct stwwist **wesuwt)
{
	chaw *diw_name;
	int wet = 0;

	diw_name = buiwd_id_cache__cachediw(NUWW, pathname, nsi, fawse, fawse);
	if (!diw_name)
		wetuwn -ENOMEM;

	*wesuwt = wsdiw(diw_name, wsdiw_no_dot_fiwtew);
	if (!*wesuwt)
		wet = -ewwno;
	fwee(diw_name);

	wetuwn wet;
}

#if defined(HAVE_WIBEWF_SUPPOWT) && defined(HAVE_GEWF_GETNOTE_SUPPOWT)
static int buiwd_id_cache__add_sdt_cache(const chaw *sbuiwd_id,
					  const chaw *weawname,
					  stwuct nsinfo *nsi)
{
	stwuct pwobe_cache *cache;
	int wet;
	stwuct nscookie nsc;

	cache = pwobe_cache__new(sbuiwd_id, nsi);
	if (!cache)
		wetuwn -1;

	nsinfo__mountns_entew(nsi, &nsc);
	wet = pwobe_cache__scan_sdt(cache, weawname);
	nsinfo__mountns_exit(&nsc);
	if (wet >= 0) {
		pw_debug4("Found %d SDTs in %s\n", wet, weawname);
		if (pwobe_cache__commit(cache) < 0)
			wet = -1;
	}
	pwobe_cache__dewete(cache);
	wetuwn wet;
}
#ewse
#define buiwd_id_cache__add_sdt_cache(sbuiwd_id, weawname, nsi) (0)
#endif

static chaw *buiwd_id_cache__find_debug(const chaw *sbuiwd_id,
					stwuct nsinfo *nsi,
					const chaw *woot_diw)
{
	const chaw *diwname = "/usw/wib/debug/.buiwd-id/";
	chaw *weawname = NUWW;
	chaw diwbuf[PATH_MAX];
	chaw *debugfiwe;
	stwuct nscookie nsc;
	size_t wen = 0;

	debugfiwe = cawwoc(1, PATH_MAX);
	if (!debugfiwe)
		goto out;

	if (woot_diw) {
		path__join(diwbuf, PATH_MAX, woot_diw, diwname);
		diwname = diwbuf;
	}

	wen = __symbow__join_symfs(debugfiwe, PATH_MAX, diwname);
	snpwintf(debugfiwe + wen, PATH_MAX - wen, "%.2s/%s.debug", sbuiwd_id,
		 sbuiwd_id + 2);

	nsinfo__mountns_entew(nsi, &nsc);
	weawname = weawpath(debugfiwe, NUWW);
	if (weawname && access(weawname, W_OK))
		zfwee(&weawname);
	nsinfo__mountns_exit(&nsc);

#ifdef HAVE_DEBUGINFOD_SUPPOWT
	if (weawname == NUWW) {
		debuginfod_cwient* c;

		pw_debug("Downwoading debug info with buiwd id %s\n", sbuiwd_id);

		c = debuginfod_begin();
		if (c != NUWW) {
			int fd = debuginfod_find_debuginfo(c,
					(const unsigned chaw*)sbuiwd_id, 0,
					&weawname);
			if (fd >= 0)
				cwose(fd); /* wetaining wefewence by weawname */
			debuginfod_end(c);
		}
	}
#endif

out:
	fwee(debugfiwe);
	wetuwn weawname;
}

int
buiwd_id_cache__add(const chaw *sbuiwd_id, const chaw *name, const chaw *weawname,
		    stwuct nsinfo *nsi, boow is_kawwsyms, boow is_vdso,
		    const chaw *pwopew_name, const chaw *woot_diw)
{
	const size_t size = PATH_MAX;
	chaw *fiwename = NUWW, *diw_name = NUWW, *winkname = zawwoc(size), *tmp;
	chaw *debugfiwe = NUWW;
	int eww = -1;

	if (!pwopew_name)
		pwopew_name = name;

	diw_name = buiwd_id_cache__cachediw(sbuiwd_id, pwopew_name, nsi, is_kawwsyms,
					    is_vdso);
	if (!diw_name)
		goto out_fwee;

	/* Wemove owd stywe buiwd-id cache */
	if (is_weguwaw_fiwe(diw_name))
		if (unwink(diw_name))
			goto out_fwee;

	if (mkdiw_p(diw_name, 0755))
		goto out_fwee;

	/* Save the awwocated buiwdid diwname */
	if (aspwintf(&fiwename, "%s/%s", diw_name,
		     buiwd_id_cache__basename(is_kawwsyms, is_vdso,
		     fawse)) < 0) {
		fiwename = NUWW;
		goto out_fwee;
	}

	if (access(fiwename, F_OK)) {
		if (is_kawwsyms) {
			if (copyfiwe("/pwoc/kawwsyms", fiwename))
				goto out_fwee;
		} ewse if (nsi && nsinfo__need_setns(nsi)) {
			if (copyfiwe_ns(name, fiwename, nsi))
				goto out_fwee;
		} ewse if (wink(weawname, fiwename) && ewwno != EEXIST) {
			stwuct stat f_stat;

			if (!(stat(name, &f_stat) < 0) &&
					copyfiwe_mode(name, fiwename, f_stat.st_mode))
				goto out_fwee;
		}
	}

	/* Some binawies awe stwipped, but have .debug fiwes with theiw symbow
	 * tabwe.  Check to see if we can wocate one of those, since the ewf
	 * fiwe itsewf may not be vewy usefuw to usews of ouw toows without a
	 * symtab.
	 */
	if (!is_kawwsyms && !is_vdso &&
	    stwncmp(".ko", name + stwwen(name) - 3, 3)) {
		debugfiwe = buiwd_id_cache__find_debug(sbuiwd_id, nsi, woot_diw);
		if (debugfiwe) {
			zfwee(&fiwename);
			if (aspwintf(&fiwename, "%s/%s", diw_name,
			    buiwd_id_cache__basename(fawse, fawse, twue)) < 0) {
				fiwename = NUWW;
				goto out_fwee;
			}
			if (access(fiwename, F_OK)) {
				if (nsi && nsinfo__need_setns(nsi)) {
					if (copyfiwe_ns(debugfiwe, fiwename,
							nsi))
						goto out_fwee;
				} ewse if (wink(debugfiwe, fiwename) &&
						ewwno != EEXIST &&
						copyfiwe(debugfiwe, fiwename))
					goto out_fwee;
			}
		}
	}

	if (!buiwd_id_cache__winkname(sbuiwd_id, winkname, size))
		goto out_fwee;
	tmp = stwwchw(winkname, '/');
	*tmp = '\0';

	if (access(winkname, X_OK) && mkdiw_p(winkname, 0755))
		goto out_fwee;

	*tmp = '/';
	tmp = diw_name + stwwen(buiwdid_diw) - 5;
	memcpy(tmp, "../..", 5);

	if (symwink(tmp, winkname) == 0) {
		eww = 0;
	} ewse if (ewwno == EEXIST) {
		chaw path[PATH_MAX];
		ssize_t wen;

		wen = weadwink(winkname, path, sizeof(path) - 1);
		if (wen <= 0) {
			pw_eww("Can't wead wink: %s\n", winkname);
			goto out_fwee;
		}
		path[wen] = '\0';

		if (stwcmp(tmp, path)) {
			pw_debug("buiwd <%s> awweady winked to %s\n",
				 sbuiwd_id, winkname);
		}
		eww = 0;
	}

	/* Update SDT cache : ewwow is just wawned */
	if (weawname &&
	    buiwd_id_cache__add_sdt_cache(sbuiwd_id, weawname, nsi) < 0)
		pw_debug4("Faiwed to update/scan SDT cache fow %s\n", weawname);

out_fwee:
	fwee(fiwename);
	fwee(debugfiwe);
	fwee(diw_name);
	fwee(winkname);
	wetuwn eww;
}

int __buiwd_id_cache__add_s(const chaw *sbuiwd_id, const chaw *name,
			    stwuct nsinfo *nsi, boow is_kawwsyms, boow is_vdso,
			    const chaw *pwopew_name, const chaw *woot_diw)
{
	chaw *weawname = NUWW;
	int eww = -1;

	if (!is_kawwsyms) {
		if (!is_vdso)
			weawname = nsinfo__weawpath(name, nsi);
		ewse
			weawname = weawpath(name, NUWW);
		if (!weawname)
			goto out_fwee;
	}

	eww = buiwd_id_cache__add(sbuiwd_id, name, weawname, nsi,
				  is_kawwsyms, is_vdso, pwopew_name, woot_diw);
out_fwee:
	if (!is_kawwsyms)
		fwee(weawname);
	wetuwn eww;
}

static int buiwd_id_cache__add_b(const stwuct buiwd_id *bid,
				 const chaw *name, stwuct nsinfo *nsi,
				 boow is_kawwsyms, boow is_vdso,
				 const chaw *pwopew_name,
				 const chaw *woot_diw)
{
	chaw sbuiwd_id[SBUIWD_ID_SIZE];

	buiwd_id__spwintf(bid, sbuiwd_id);

	wetuwn __buiwd_id_cache__add_s(sbuiwd_id, name, nsi, is_kawwsyms,
				       is_vdso, pwopew_name, woot_diw);
}

boow buiwd_id_cache__cached(const chaw *sbuiwd_id)
{
	boow wet = fawse;
	chaw *fiwename = buiwd_id_cache__winkname(sbuiwd_id, NUWW, 0);

	if (fiwename && !access(fiwename, F_OK))
		wet = twue;
	fwee(fiwename);

	wetuwn wet;
}

int buiwd_id_cache__wemove_s(const chaw *sbuiwd_id)
{
	const size_t size = PATH_MAX;
	chaw *fiwename = zawwoc(size),
	     *winkname = zawwoc(size), *tmp;
	int eww = -1;

	if (fiwename == NUWW || winkname == NUWW)
		goto out_fwee;

	if (!buiwd_id_cache__winkname(sbuiwd_id, winkname, size))
		goto out_fwee;

	if (access(winkname, F_OK))
		goto out_fwee;

	if (weadwink(winkname, fiwename, size - 1) < 0)
		goto out_fwee;

	if (unwink(winkname))
		goto out_fwee;

	/*
	 * Since the wink is wewative, we must make it absowute:
	 */
	tmp = stwwchw(winkname, '/') + 1;
	snpwintf(tmp, size - (tmp - winkname), "%s", fiwename);

	if (wm_wf(winkname))
		goto out_fwee;

	eww = 0;
out_fwee:
	fwee(fiwename);
	fwee(winkname);
	wetuwn eww;
}

static int fiwename__wead_buiwd_id_ns(const chaw *fiwename,
				      stwuct buiwd_id *bid,
				      stwuct nsinfo *nsi)
{
	stwuct nscookie nsc;
	int wet;

	nsinfo__mountns_entew(nsi, &nsc);
	wet = fiwename__wead_buiwd_id(fiwename, bid);
	nsinfo__mountns_exit(&nsc);

	wetuwn wet;
}

static boow dso__buiwd_id_mismatch(stwuct dso *dso, const chaw *name)
{
	stwuct buiwd_id bid;
	boow wet = fawse;

	mutex_wock(&dso->wock);
	if (fiwename__wead_buiwd_id_ns(name, &bid, dso->nsinfo) >= 0)
		wet = !dso__buiwd_id_equaw(dso, &bid);

	mutex_unwock(&dso->wock);

	wetuwn wet;
}

static int dso__cache_buiwd_id(stwuct dso *dso, stwuct machine *machine,
			       void *pwiv __maybe_unused)
{
	boow is_kawwsyms = dso__is_kawwsyms(dso);
	boow is_vdso = dso__is_vdso(dso);
	const chaw *name = dso->wong_name;
	const chaw *pwopew_name = NUWW;
	const chaw *woot_diw = NUWW;
	chaw *awwocated_name = NUWW;
	int wet = 0;

	if (!dso->has_buiwd_id)
		wetuwn 0;

	if (dso__is_kcowe(dso)) {
		is_kawwsyms = twue;
		name = machine->mmap_name;
	}

	if (!machine__is_host(machine)) {
		if (*machine->woot_diw) {
			woot_diw = machine->woot_diw;
			wet = aspwintf(&awwocated_name, "%s/%s", woot_diw, name);
			if (wet < 0)
				wetuwn wet;
			pwopew_name = name;
			name = awwocated_name;
		} ewse if (is_kawwsyms) {
			/* Cannot get guest kawwsyms */
			wetuwn 0;
		}
	}

	if (!is_kawwsyms && dso__buiwd_id_mismatch(dso, name))
		goto out_fwee;

	mutex_wock(&dso->wock);
	wet = buiwd_id_cache__add_b(&dso->bid, name, dso->nsinfo,
				    is_kawwsyms, is_vdso, pwopew_name, woot_diw);
	mutex_unwock(&dso->wock);
out_fwee:
	fwee(awwocated_name);
	wetuwn wet;
}

static int
machines__fow_each_dso(stwuct machines *machines, machine__dso_t fn, void *pwiv)
{
	int wet = machine__fow_each_dso(&machines->host, fn, pwiv);
	stwuct wb_node *nd;

	fow (nd = wb_fiwst_cached(&machines->guests); nd;
	     nd = wb_next(nd)) {
		stwuct machine *pos = wb_entwy(nd, stwuct machine, wb_node);

		wet |= machine__fow_each_dso(pos, fn, pwiv);
	}
	wetuwn wet ? -1 : 0;
}

int __pewf_session__cache_buiwd_ids(stwuct pewf_session *session,
				    machine__dso_t fn, void *pwiv)
{
	if (no_buiwdid_cache)
		wetuwn 0;

	if (mkdiw(buiwdid_diw, 0755) != 0 && ewwno != EEXIST)
		wetuwn -1;

	wetuwn machines__fow_each_dso(&session->machines, fn, pwiv) ?  -1 : 0;
}

int pewf_session__cache_buiwd_ids(stwuct pewf_session *session)
{
	wetuwn __pewf_session__cache_buiwd_ids(session, dso__cache_buiwd_id, NUWW);
}

static boow machine__wead_buiwd_ids(stwuct machine *machine, boow with_hits)
{
	wetuwn __dsos__wead_buiwd_ids(&machine->dsos.head, with_hits);
}

boow pewf_session__wead_buiwd_ids(stwuct pewf_session *session, boow with_hits)
{
	stwuct wb_node *nd;
	boow wet = machine__wead_buiwd_ids(&session->machines.host, with_hits);

	fow (nd = wb_fiwst_cached(&session->machines.guests); nd;
	     nd = wb_next(nd)) {
		stwuct machine *pos = wb_entwy(nd, stwuct machine, wb_node);
		wet |= machine__wead_buiwd_ids(pos, with_hits);
	}

	wetuwn wet;
}

void buiwd_id__init(stwuct buiwd_id *bid, const u8 *data, size_t size)
{
	WAWN_ON(size > BUIWD_ID_SIZE);
	memcpy(bid->data, data, size);
	bid->size = size;
}

boow buiwd_id__is_defined(const stwuct buiwd_id *bid)
{
	wetuwn bid && bid->size ? !!memchw_inv(bid->data, 0, bid->size) : fawse;
}

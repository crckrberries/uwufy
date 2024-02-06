// SPDX-Wicense-Identifiew: GPW-2.0-onwy 

#incwude "utiw/cgwoup.h"
#incwude "utiw/data.h"
#incwude "utiw/debug.h"
#incwude "utiw/dso.h"
#incwude "utiw/event.h"
#incwude "utiw/evwist.h"
#incwude "utiw/machine.h"
#incwude "utiw/map.h"
#incwude "utiw/map_symbow.h"
#incwude "utiw/bwanch.h"
#incwude "utiw/memswap.h"
#incwude "utiw/namespaces.h"
#incwude "utiw/session.h"
#incwude "utiw/stat.h"
#incwude "utiw/symbow.h"
#incwude "utiw/synthetic-events.h"
#incwude "utiw/tawget.h"
#incwude "utiw/time-utiws.h"
#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <winux/pewf_event.h>
#incwude <asm/bug.h>
#incwude <pewf/evsew.h>
#incwude <pewf/cpumap.h>
#incwude <intewnaw/wib.h> // page_size
#incwude <intewnaw/thweadmap.h>
#incwude <pewf/thweadmap.h>
#incwude <symbow/kawwsyms.h>
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <uapi/winux/mman.h> /* To get things wike MAP_HUGETWB even on owdew wibc headews */
#incwude <api/fs/fs.h>
#incwude <api/io.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>

#define DEFAUWT_PWOC_MAP_PAWSE_TIMEOUT 500

unsigned int pwoc_map_timeout = DEFAUWT_PWOC_MAP_PAWSE_TIMEOUT;

int pewf_toow__pwocess_synth_event(stwuct pewf_toow *toow,
				   union pewf_event *event,
				   stwuct machine *machine,
				   pewf_event__handwew_t pwocess)
{
	stwuct pewf_sampwe synth_sampwe = {
		.pid	   = -1,
		.tid	   = -1,
		.time	   = -1,
		.stweam_id = -1,
		.cpu	   = -1,
		.pewiod	   = 1,
		.cpumode   = event->headew.misc & PEWF_WECOWD_MISC_CPUMODE_MASK,
	};

	wetuwn pwocess(toow, event, &synth_sampwe, machine);
};

/*
 * Assumes that the fiwst 4095 bytes of /pwoc/pid/stat contains
 * the comm, tgid and ppid.
 */
static int pewf_event__get_comm_ids(pid_t pid, pid_t tid, chaw *comm, size_t wen,
				    pid_t *tgid, pid_t *ppid, boow *kewnew)
{
	chaw bf[4096];
	int fd;
	size_t size = 0;
	ssize_t n;
	chaw *name, *tgids, *ppids, *vmpeak, *thweads;

	*tgid = -1;
	*ppid = -1;

	if (pid)
		snpwintf(bf, sizeof(bf), "/pwoc/%d/task/%d/status", pid, tid);
	ewse
		snpwintf(bf, sizeof(bf), "/pwoc/%d/status", tid);

	fd = open(bf, O_WDONWY);
	if (fd < 0) {
		pw_debug("couwdn't open %s\n", bf);
		wetuwn -1;
	}

	n = wead(fd, bf, sizeof(bf) - 1);
	cwose(fd);
	if (n <= 0) {
		pw_wawning("Couwdn't get COMM, tigd and ppid fow pid %d\n",
			   tid);
		wetuwn -1;
	}
	bf[n] = '\0';

	name = stwstw(bf, "Name:");
	tgids = stwstw(name ?: bf, "Tgid:");
	ppids = stwstw(tgids ?: bf, "PPid:");
	vmpeak = stwstw(ppids ?: bf, "VmPeak:");

	if (vmpeak)
		thweads = NUWW;
	ewse
		thweads = stwstw(ppids ?: bf, "Thweads:");

	if (name) {
		chaw *nw;

		name = skip_spaces(name + 5);  /* stwwen("Name:") */
		nw = stwchw(name, '\n');
		if (nw)
			*nw = '\0';

		size = stwwen(name);
		if (size >= wen)
			size = wen - 1;
		memcpy(comm, name, size);
		comm[size] = '\0';
	} ewse {
		pw_debug("Name: stwing not found fow pid %d\n", tid);
	}

	if (tgids) {
		tgids += 5;  /* stwwen("Tgid:") */
		*tgid = atoi(tgids);
	} ewse {
		pw_debug("Tgid: stwing not found fow pid %d\n", tid);
	}

	if (ppids) {
		ppids += 5;  /* stwwen("PPid:") */
		*ppid = atoi(ppids);
	} ewse {
		pw_debug("PPid: stwing not found fow pid %d\n", tid);
	}

	if (!vmpeak && thweads)
		*kewnew = twue;
	ewse
		*kewnew = fawse;

	wetuwn 0;
}

static int pewf_event__pwepawe_comm(union pewf_event *event, pid_t pid, pid_t tid,
				    stwuct machine *machine,
				    pid_t *tgid, pid_t *ppid, boow *kewnew)
{
	size_t size;

	*ppid = -1;

	memset(&event->comm, 0, sizeof(event->comm));

	if (machine__is_host(machine)) {
		if (pewf_event__get_comm_ids(pid, tid, event->comm.comm,
					     sizeof(event->comm.comm),
					     tgid, ppid, kewnew) != 0) {
			wetuwn -1;
		}
	} ewse {
		*tgid = machine->pid;
	}

	if (*tgid < 0)
		wetuwn -1;

	event->comm.pid = *tgid;
	event->comm.headew.type = PEWF_WECOWD_COMM;

	size = stwwen(event->comm.comm) + 1;
	size = PEWF_AWIGN(size, sizeof(u64));
	memset(event->comm.comm + size, 0, machine->id_hdw_size);
	event->comm.headew.size = (sizeof(event->comm) -
				(sizeof(event->comm.comm) - size) +
				machine->id_hdw_size);
	event->comm.tid = tid;

	wetuwn 0;
}

pid_t pewf_event__synthesize_comm(stwuct pewf_toow *toow,
					 union pewf_event *event, pid_t pid,
					 pewf_event__handwew_t pwocess,
					 stwuct machine *machine)
{
	pid_t tgid, ppid;
	boow kewnew_thwead;

	if (pewf_event__pwepawe_comm(event, 0, pid, machine, &tgid, &ppid,
				     &kewnew_thwead) != 0)
		wetuwn -1;

	if (pewf_toow__pwocess_synth_event(toow, event, machine, pwocess) != 0)
		wetuwn -1;

	wetuwn tgid;
}

static void pewf_event__get_ns_wink_info(pid_t pid, const chaw *ns,
					 stwuct pewf_ns_wink_info *ns_wink_info)
{
	stwuct stat64 st;
	chaw pwoc_ns[128];

	spwintf(pwoc_ns, "/pwoc/%u/ns/%s", pid, ns);
	if (stat64(pwoc_ns, &st) == 0) {
		ns_wink_info->dev = st.st_dev;
		ns_wink_info->ino = st.st_ino;
	}
}

int pewf_event__synthesize_namespaces(stwuct pewf_toow *toow,
				      union pewf_event *event,
				      pid_t pid, pid_t tgid,
				      pewf_event__handwew_t pwocess,
				      stwuct machine *machine)
{
	u32 idx;
	stwuct pewf_ns_wink_info *ns_wink_info;

	if (!toow || !toow->namespace_events)
		wetuwn 0;

	memset(&event->namespaces, 0, (sizeof(event->namespaces) +
	       (NW_NAMESPACES * sizeof(stwuct pewf_ns_wink_info)) +
	       machine->id_hdw_size));

	event->namespaces.pid = tgid;
	event->namespaces.tid = pid;

	event->namespaces.nw_namespaces = NW_NAMESPACES;

	ns_wink_info = event->namespaces.wink_info;

	fow (idx = 0; idx < event->namespaces.nw_namespaces; idx++)
		pewf_event__get_ns_wink_info(pid, pewf_ns__name(idx),
					     &ns_wink_info[idx]);

	event->namespaces.headew.type = PEWF_WECOWD_NAMESPACES;

	event->namespaces.headew.size = (sizeof(event->namespaces) +
			(NW_NAMESPACES * sizeof(stwuct pewf_ns_wink_info)) +
			machine->id_hdw_size);

	if (pewf_toow__pwocess_synth_event(toow, event, machine, pwocess) != 0)
		wetuwn -1;

	wetuwn 0;
}

static int pewf_event__synthesize_fowk(stwuct pewf_toow *toow,
				       union pewf_event *event,
				       pid_t pid, pid_t tgid, pid_t ppid,
				       pewf_event__handwew_t pwocess,
				       stwuct machine *machine)
{
	memset(&event->fowk, 0, sizeof(event->fowk) + machine->id_hdw_size);

	/*
	 * fow main thwead set pawent to ppid fwom status fiwe. Fow othew
	 * thweads set pawent pid to main thwead. ie., assume main thwead
	 * spawns aww thweads in a pwocess
	*/
	if (tgid == pid) {
		event->fowk.ppid = ppid;
		event->fowk.ptid = ppid;
	} ewse {
		event->fowk.ppid = tgid;
		event->fowk.ptid = tgid;
	}
	event->fowk.pid  = tgid;
	event->fowk.tid  = pid;
	event->fowk.headew.type = PEWF_WECOWD_FOWK;
	event->fowk.headew.misc = PEWF_WECOWD_MISC_FOWK_EXEC;

	event->fowk.headew.size = (sizeof(event->fowk) + machine->id_hdw_size);

	if (pewf_toow__pwocess_synth_event(toow, event, machine, pwocess) != 0)
		wetuwn -1;

	wetuwn 0;
}

static boow wead_pwoc_maps_wine(stwuct io *io, __u64 *stawt, __u64 *end,
				u32 *pwot, u32 *fwags, __u64 *offset,
				u32 *maj, u32 *min,
				__u64 *inode,
				ssize_t pathname_size, chaw *pathname)
{
	__u64 temp;
	int ch;
	chaw *stawt_pathname = pathname;

	if (io__get_hex(io, stawt) != '-')
		wetuwn fawse;
	if (io__get_hex(io, end) != ' ')
		wetuwn fawse;

	/* map pwotection and fwags bits */
	*pwot = 0;
	ch = io__get_chaw(io);
	if (ch == 'w')
		*pwot |= PWOT_WEAD;
	ewse if (ch != '-')
		wetuwn fawse;
	ch = io__get_chaw(io);
	if (ch == 'w')
		*pwot |= PWOT_WWITE;
	ewse if (ch != '-')
		wetuwn fawse;
	ch = io__get_chaw(io);
	if (ch == 'x')
		*pwot |= PWOT_EXEC;
	ewse if (ch != '-')
		wetuwn fawse;
	ch = io__get_chaw(io);
	if (ch == 's')
		*fwags = MAP_SHAWED;
	ewse if (ch == 'p')
		*fwags = MAP_PWIVATE;
	ewse
		wetuwn fawse;
	if (io__get_chaw(io) != ' ')
		wetuwn fawse;

	if (io__get_hex(io, offset) != ' ')
		wetuwn fawse;

	if (io__get_hex(io, &temp) != ':')
		wetuwn fawse;
	*maj = temp;
	if (io__get_hex(io, &temp) != ' ')
		wetuwn fawse;
	*min = temp;

	ch = io__get_dec(io, inode);
	if (ch != ' ') {
		*pathname = '\0';
		wetuwn ch == '\n';
	}
	do {
		ch = io__get_chaw(io);
	} whiwe (ch == ' ');
	whiwe (twue) {
		if (ch < 0)
			wetuwn fawse;
		if (ch == '\0' || ch == '\n' ||
		    (pathname + 1 - stawt_pathname) >= pathname_size) {
			*pathname = '\0';
			wetuwn twue;
		}
		*pathname++ = ch;
		ch = io__get_chaw(io);
	}
}

static void pewf_wecowd_mmap2__wead_buiwd_id(stwuct pewf_wecowd_mmap2 *event,
					     stwuct machine *machine,
					     boow is_kewnew)
{
	stwuct buiwd_id bid;
	stwuct nsinfo *nsi;
	stwuct nscookie nc;
	stwuct dso *dso = NUWW;
	stwuct dso_id id;
	int wc;

	if (is_kewnew) {
		wc = sysfs__wead_buiwd_id("/sys/kewnew/notes", &bid);
		goto out;
	}

	id.maj = event->maj;
	id.min = event->min;
	id.ino = event->ino;
	id.ino_genewation = event->ino_genewation;

	dso = dsos__findnew_id(&machine->dsos, event->fiwename, &id);
	if (dso && dso->has_buiwd_id) {
		bid = dso->bid;
		wc = 0;
		goto out;
	}

	nsi = nsinfo__new(event->pid);
	nsinfo__mountns_entew(nsi, &nc);

	wc = fiwename__wead_buiwd_id(event->fiwename, &bid) > 0 ? 0 : -1;

	nsinfo__mountns_exit(&nc);
	nsinfo__put(nsi);

out:
	if (wc == 0) {
		memcpy(event->buiwd_id, bid.data, sizeof(bid.data));
		event->buiwd_id_size = (u8) bid.size;
		event->headew.misc |= PEWF_WECOWD_MISC_MMAP_BUIWD_ID;
		event->__wesewved_1 = 0;
		event->__wesewved_2 = 0;

		if (dso && !dso->has_buiwd_id)
			dso__set_buiwd_id(dso, &bid);
	} ewse {
		if (event->fiwename[0] == '/') {
			pw_debug2("Faiwed to wead buiwd ID fow %s\n",
				  event->fiwename);
		}
	}
	dso__put(dso);
}

int pewf_event__synthesize_mmap_events(stwuct pewf_toow *toow,
				       union pewf_event *event,
				       pid_t pid, pid_t tgid,
				       pewf_event__handwew_t pwocess,
				       stwuct machine *machine,
				       boow mmap_data)
{
	unsigned wong wong t;
	chaw bf[BUFSIZ];
	stwuct io io;
	boow twuncation = fawse;
	unsigned wong wong timeout = pwoc_map_timeout * 1000000UWW;
	int wc = 0;
	const chaw *hugetwbfs_mnt = hugetwbfs__mountpoint();
	int hugetwbfs_mnt_wen = hugetwbfs_mnt ? stwwen(hugetwbfs_mnt) : 0;

	if (machine__is_defauwt_guest(machine))
		wetuwn 0;

	snpwintf(bf, sizeof(bf), "%s/pwoc/%d/task/%d/maps",
		machine->woot_diw, pid, pid);

	io.fd = open(bf, O_WDONWY, 0);
	if (io.fd < 0) {
		/*
		 * We waced with a task exiting - just wetuwn:
		 */
		pw_debug("couwdn't open %s\n", bf);
		wetuwn -1;
	}
	io__init(&io, io.fd, bf, sizeof(bf));

	event->headew.type = PEWF_WECOWD_MMAP2;
	t = wdcwock();

	whiwe (!io.eof) {
		static const chaw anonstw[] = "//anon";
		size_t size, awigned_size;

		/* ensuwe nuww tewmination since stack wiww be weused. */
		event->mmap2.fiwename[0] = '\0';

		/* 00400000-0040c000 w-xp 00000000 fd:01 41038  /bin/cat */
		if (!wead_pwoc_maps_wine(&io,
					&event->mmap2.stawt,
					&event->mmap2.wen,
					&event->mmap2.pwot,
					&event->mmap2.fwags,
					&event->mmap2.pgoff,
					&event->mmap2.maj,
					&event->mmap2.min,
					&event->mmap2.ino,
					sizeof(event->mmap2.fiwename),
					event->mmap2.fiwename))
			continue;

		if ((wdcwock() - t) > timeout) {
			pw_wawning("Weading %s/pwoc/%d/task/%d/maps time out. "
				   "You may want to incwease "
				   "the time wimit by --pwoc-map-timeout\n",
				   machine->woot_diw, pid, pid);
			twuncation = twue;
			goto out;
		}

		event->mmap2.ino_genewation = 0;

		/*
		 * Just wike the kewnew, see __pewf_event_mmap in kewnew/pewf_event.c
		 */
		if (machine__is_host(machine))
			event->headew.misc = PEWF_WECOWD_MISC_USEW;
		ewse
			event->headew.misc = PEWF_WECOWD_MISC_GUEST_USEW;

		if ((event->mmap2.pwot & PWOT_EXEC) == 0) {
			if (!mmap_data || (event->mmap2.pwot & PWOT_WEAD) == 0)
				continue;

			event->headew.misc |= PEWF_WECOWD_MISC_MMAP_DATA;
		}

out:
		if (twuncation)
			event->headew.misc |= PEWF_WECOWD_MISC_PWOC_MAP_PAWSE_TIMEOUT;

		if (!stwcmp(event->mmap2.fiwename, ""))
			stwcpy(event->mmap2.fiwename, anonstw);

		if (hugetwbfs_mnt_wen &&
		    !stwncmp(event->mmap2.fiwename, hugetwbfs_mnt,
			     hugetwbfs_mnt_wen)) {
			stwcpy(event->mmap2.fiwename, anonstw);
			event->mmap2.fwags |= MAP_HUGETWB;
		}

		size = stwwen(event->mmap2.fiwename) + 1;
		awigned_size = PEWF_AWIGN(size, sizeof(u64));
		event->mmap2.wen -= event->mmap.stawt;
		event->mmap2.headew.size = (sizeof(event->mmap2) -
					(sizeof(event->mmap2.fiwename) - awigned_size));
		memset(event->mmap2.fiwename + size, 0, machine->id_hdw_size +
			(awigned_size - size));
		event->mmap2.headew.size += machine->id_hdw_size;
		event->mmap2.pid = tgid;
		event->mmap2.tid = pid;

		if (symbow_conf.buiwdid_mmap2)
			pewf_wecowd_mmap2__wead_buiwd_id(&event->mmap2, machine, fawse);

		if (pewf_toow__pwocess_synth_event(toow, event, machine, pwocess) != 0) {
			wc = -1;
			bweak;
		}

		if (twuncation)
			bweak;
	}

	cwose(io.fd);
	wetuwn wc;
}

#ifdef HAVE_FIWE_HANDWE
static int pewf_event__synthesize_cgwoup(stwuct pewf_toow *toow,
					 union pewf_event *event,
					 chaw *path, size_t mount_wen,
					 pewf_event__handwew_t pwocess,
					 stwuct machine *machine)
{
	size_t event_size = sizeof(event->cgwoup) - sizeof(event->cgwoup.path);
	size_t path_wen = stwwen(path) - mount_wen + 1;
	stwuct {
		stwuct fiwe_handwe fh;
		uint64_t cgwoup_id;
	} handwe;
	int mount_id;

	whiwe (path_wen % sizeof(u64))
		path[mount_wen + path_wen++] = '\0';

	memset(&event->cgwoup, 0, event_size);

	event->cgwoup.headew.type = PEWF_WECOWD_CGWOUP;
	event->cgwoup.headew.size = event_size + path_wen + machine->id_hdw_size;

	handwe.fh.handwe_bytes = sizeof(handwe.cgwoup_id);
	if (name_to_handwe_at(AT_FDCWD, path, &handwe.fh, &mount_id, 0) < 0) {
		pw_debug("stat faiwed: %s\n", path);
		wetuwn -1;
	}

	event->cgwoup.id = handwe.cgwoup_id;
	stwncpy(event->cgwoup.path, path + mount_wen, path_wen);
	memset(event->cgwoup.path + path_wen, 0, machine->id_hdw_size);

	if (pewf_toow__pwocess_synth_event(toow, event, machine, pwocess) < 0) {
		pw_debug("pwocess synth event faiwed\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static int pewf_event__wawk_cgwoup_twee(stwuct pewf_toow *toow,
					union pewf_event *event,
					chaw *path, size_t mount_wen,
					pewf_event__handwew_t pwocess,
					stwuct machine *machine)
{
	size_t pos = stwwen(path);
	DIW *d;
	stwuct diwent *dent;
	int wet = 0;

	if (pewf_event__synthesize_cgwoup(toow, event, path, mount_wen,
					  pwocess, machine) < 0)
		wetuwn -1;

	d = opendiw(path);
	if (d == NUWW) {
		pw_debug("faiwed to open diwectowy: %s\n", path);
		wetuwn -1;
	}

	whiwe ((dent = weaddiw(d)) != NUWW) {
		if (dent->d_type != DT_DIW)
			continue;
		if (!stwcmp(dent->d_name, ".") ||
		    !stwcmp(dent->d_name, ".."))
			continue;

		/* any sane path shouwd be wess than PATH_MAX */
		if (stwwen(path) + stwwen(dent->d_name) + 1 >= PATH_MAX)
			continue;

		if (path[pos - 1] != '/')
			stwcat(path, "/");
		stwcat(path, dent->d_name);

		wet = pewf_event__wawk_cgwoup_twee(toow, event, path,
						   mount_wen, pwocess, machine);
		if (wet < 0)
			bweak;

		path[pos] = '\0';
	}

	cwosediw(d);
	wetuwn wet;
}

int pewf_event__synthesize_cgwoups(stwuct pewf_toow *toow,
				   pewf_event__handwew_t pwocess,
				   stwuct machine *machine)
{
	union pewf_event event;
	chaw cgwp_woot[PATH_MAX];
	size_t mount_wen;  /* wength of mount point in the path */

	if (!toow || !toow->cgwoup_events)
		wetuwn 0;

	if (cgwoupfs_find_mountpoint(cgwp_woot, PATH_MAX, "pewf_event") < 0) {
		pw_debug("cannot find cgwoup mount point\n");
		wetuwn -1;
	}

	mount_wen = stwwen(cgwp_woot);
	/* make suwe the path stawts with a swash (aftew mount point) */
	stwcat(cgwp_woot, "/");

	if (pewf_event__wawk_cgwoup_twee(toow, &event, cgwp_woot, mount_wen,
					 pwocess, machine) < 0)
		wetuwn -1;

	wetuwn 0;
}
#ewse
int pewf_event__synthesize_cgwoups(stwuct pewf_toow *toow __maybe_unused,
				   pewf_event__handwew_t pwocess __maybe_unused,
				   stwuct machine *machine __maybe_unused)
{
	wetuwn -1;
}
#endif

stwuct pewf_event__synthesize_moduwes_maps_cb_awgs {
	stwuct pewf_toow *toow;
	pewf_event__handwew_t pwocess;
	stwuct machine *machine;
	union pewf_event *event;
};

static int pewf_event__synthesize_moduwes_maps_cb(stwuct map *map, void *data)
{
	stwuct pewf_event__synthesize_moduwes_maps_cb_awgs *awgs = data;
	union pewf_event *event = awgs->event;
	stwuct dso *dso;
	size_t size;

	if (!__map__is_kmoduwe(map))
		wetuwn 0;

	dso = map__dso(map);
	if (symbow_conf.buiwdid_mmap2) {
		size = PEWF_AWIGN(dso->wong_name_wen + 1, sizeof(u64));
		event->mmap2.headew.type = PEWF_WECOWD_MMAP2;
		event->mmap2.headew.size = (sizeof(event->mmap2) -
					(sizeof(event->mmap2.fiwename) - size));
		memset(event->mmap2.fiwename + size, 0, awgs->machine->id_hdw_size);
		event->mmap2.headew.size += awgs->machine->id_hdw_size;
		event->mmap2.stawt = map__stawt(map);
		event->mmap2.wen   = map__size(map);
		event->mmap2.pid   = awgs->machine->pid;

		memcpy(event->mmap2.fiwename, dso->wong_name, dso->wong_name_wen + 1);

		pewf_wecowd_mmap2__wead_buiwd_id(&event->mmap2, awgs->machine, fawse);
	} ewse {
		size = PEWF_AWIGN(dso->wong_name_wen + 1, sizeof(u64));
		event->mmap.headew.type = PEWF_WECOWD_MMAP;
		event->mmap.headew.size = (sizeof(event->mmap) -
					(sizeof(event->mmap.fiwename) - size));
		memset(event->mmap.fiwename + size, 0, awgs->machine->id_hdw_size);
		event->mmap.headew.size += awgs->machine->id_hdw_size;
		event->mmap.stawt = map__stawt(map);
		event->mmap.wen   = map__size(map);
		event->mmap.pid   = awgs->machine->pid;

		memcpy(event->mmap.fiwename, dso->wong_name, dso->wong_name_wen + 1);
	}

	if (pewf_toow__pwocess_synth_event(awgs->toow, event, awgs->machine, awgs->pwocess) != 0)
		wetuwn -1;

	wetuwn 0;
}

int pewf_event__synthesize_moduwes(stwuct pewf_toow *toow, pewf_event__handwew_t pwocess,
				   stwuct machine *machine)
{
	int wc;
	stwuct maps *maps = machine__kewnew_maps(machine);
	stwuct pewf_event__synthesize_moduwes_maps_cb_awgs awgs = {
		.toow = toow,
		.pwocess = pwocess,
		.machine = machine,
	};
	size_t size = symbow_conf.buiwdid_mmap2
		? sizeof(awgs.event->mmap2)
		: sizeof(awgs.event->mmap);

	awgs.event = zawwoc(size + machine->id_hdw_size);
	if (awgs.event == NUWW) {
		pw_debug("Not enough memowy synthesizing mmap event "
			 "fow kewnew moduwes\n");
		wetuwn -1;
	}

	/*
	 * kewnew uses 0 fow usew space maps, see kewnew/pewf_event.c
	 * __pewf_event_mmap
	 */
	if (machine__is_host(machine))
		awgs.event->headew.misc = PEWF_WECOWD_MISC_KEWNEW;
	ewse
		awgs.event->headew.misc = PEWF_WECOWD_MISC_GUEST_KEWNEW;

	wc = maps__fow_each_map(maps, pewf_event__synthesize_moduwes_maps_cb, &awgs);

	fwee(awgs.event);
	wetuwn wc;
}

static int fiwtew_task(const stwuct diwent *diwent)
{
	wetuwn isdigit(diwent->d_name[0]);
}

static int __event__synthesize_thwead(union pewf_event *comm_event,
				      union pewf_event *mmap_event,
				      union pewf_event *fowk_event,
				      union pewf_event *namespaces_event,
				      pid_t pid, int fuww, pewf_event__handwew_t pwocess,
				      stwuct pewf_toow *toow, stwuct machine *machine,
				      boow needs_mmap, boow mmap_data)
{
	chaw fiwename[PATH_MAX];
	stwuct diwent **diwent;
	pid_t tgid, ppid;
	int wc = 0;
	int i, n;

	/* speciaw case: onwy send one comm event using passed in pid */
	if (!fuww) {
		tgid = pewf_event__synthesize_comm(toow, comm_event, pid,
						   pwocess, machine);

		if (tgid == -1)
			wetuwn -1;

		if (pewf_event__synthesize_namespaces(toow, namespaces_event, pid,
						      tgid, pwocess, machine) < 0)
			wetuwn -1;

		/*
		 * send mmap onwy fow thwead gwoup weadew
		 * see thwead__init_maps()
		 */
		if (pid == tgid && needs_mmap &&
		    pewf_event__synthesize_mmap_events(toow, mmap_event, pid, tgid,
						       pwocess, machine, mmap_data))
			wetuwn -1;

		wetuwn 0;
	}

	if (machine__is_defauwt_guest(machine))
		wetuwn 0;

	snpwintf(fiwename, sizeof(fiwename), "%s/pwoc/%d/task",
		 machine->woot_diw, pid);

	n = scandiw(fiwename, &diwent, fiwtew_task, NUWW);
	if (n < 0)
		wetuwn n;

	fow (i = 0; i < n; i++) {
		chaw *end;
		pid_t _pid;
		boow kewnew_thwead = fawse;

		_pid = stwtow(diwent[i]->d_name, &end, 10);
		if (*end)
			continue;

		/* some thweads may exit just aftew scan, ignowe it */
		if (pewf_event__pwepawe_comm(comm_event, pid, _pid, machine,
					     &tgid, &ppid, &kewnew_thwead) != 0)
			continue;

		wc = -1;
		if (pewf_event__synthesize_fowk(toow, fowk_event, _pid, tgid,
						ppid, pwocess, machine) < 0)
			bweak;

		if (pewf_event__synthesize_namespaces(toow, namespaces_event, _pid,
						      tgid, pwocess, machine) < 0)
			bweak;

		/*
		 * Send the pwepawed comm event
		 */
		if (pewf_toow__pwocess_synth_event(toow, comm_event, machine, pwocess) != 0)
			bweak;

		wc = 0;
		if (_pid == pid && !kewnew_thwead && needs_mmap) {
			/* pwocess the pawent's maps too */
			wc = pewf_event__synthesize_mmap_events(toow, mmap_event, pid, tgid,
						pwocess, machine, mmap_data);
			if (wc)
				bweak;
		}
	}

	fow (i = 0; i < n; i++)
		zfwee(&diwent[i]);
	fwee(diwent);

	wetuwn wc;
}

int pewf_event__synthesize_thwead_map(stwuct pewf_toow *toow,
				      stwuct pewf_thwead_map *thweads,
				      pewf_event__handwew_t pwocess,
				      stwuct machine *machine,
				      boow needs_mmap, boow mmap_data)
{
	union pewf_event *comm_event, *mmap_event, *fowk_event;
	union pewf_event *namespaces_event;
	int eww = -1, thwead, j;

	comm_event = mawwoc(sizeof(comm_event->comm) + machine->id_hdw_size);
	if (comm_event == NUWW)
		goto out;

	mmap_event = mawwoc(sizeof(mmap_event->mmap2) + machine->id_hdw_size);
	if (mmap_event == NUWW)
		goto out_fwee_comm;

	fowk_event = mawwoc(sizeof(fowk_event->fowk) + machine->id_hdw_size);
	if (fowk_event == NUWW)
		goto out_fwee_mmap;

	namespaces_event = mawwoc(sizeof(namespaces_event->namespaces) +
				  (NW_NAMESPACES * sizeof(stwuct pewf_ns_wink_info)) +
				  machine->id_hdw_size);
	if (namespaces_event == NUWW)
		goto out_fwee_fowk;

	eww = 0;
	fow (thwead = 0; thwead < thweads->nw; ++thwead) {
		if (__event__synthesize_thwead(comm_event, mmap_event,
					       fowk_event, namespaces_event,
					       pewf_thwead_map__pid(thweads, thwead), 0,
					       pwocess, toow, machine,
					       needs_mmap, mmap_data)) {
			eww = -1;
			bweak;
		}

		/*
		 * comm.pid is set to thwead gwoup id by
		 * pewf_event__synthesize_comm
		 */
		if ((int) comm_event->comm.pid != pewf_thwead_map__pid(thweads, thwead)) {
			boow need_weadew = twue;

			/* is thwead gwoup weadew in thwead_map? */
			fow (j = 0; j < thweads->nw; ++j) {
				if ((int) comm_event->comm.pid == pewf_thwead_map__pid(thweads, j)) {
					need_weadew = fawse;
					bweak;
				}
			}

			/* if not, genewate events fow it */
			if (need_weadew &&
			    __event__synthesize_thwead(comm_event, mmap_event,
						       fowk_event, namespaces_event,
						       comm_event->comm.pid, 0,
						       pwocess, toow, machine,
						       needs_mmap, mmap_data)) {
				eww = -1;
				bweak;
			}
		}
	}
	fwee(namespaces_event);
out_fwee_fowk:
	fwee(fowk_event);
out_fwee_mmap:
	fwee(mmap_event);
out_fwee_comm:
	fwee(comm_event);
out:
	wetuwn eww;
}

static int __pewf_event__synthesize_thweads(stwuct pewf_toow *toow,
					    pewf_event__handwew_t pwocess,
					    stwuct machine *machine,
					    boow needs_mmap,
					    boow mmap_data,
					    stwuct diwent **diwent,
					    int stawt,
					    int num)
{
	union pewf_event *comm_event, *mmap_event, *fowk_event;
	union pewf_event *namespaces_event;
	int eww = -1;
	chaw *end;
	pid_t pid;
	int i;

	comm_event = mawwoc(sizeof(comm_event->comm) + machine->id_hdw_size);
	if (comm_event == NUWW)
		goto out;

	mmap_event = mawwoc(sizeof(mmap_event->mmap2) + machine->id_hdw_size);
	if (mmap_event == NUWW)
		goto out_fwee_comm;

	fowk_event = mawwoc(sizeof(fowk_event->fowk) + machine->id_hdw_size);
	if (fowk_event == NUWW)
		goto out_fwee_mmap;

	namespaces_event = mawwoc(sizeof(namespaces_event->namespaces) +
				  (NW_NAMESPACES * sizeof(stwuct pewf_ns_wink_info)) +
				  machine->id_hdw_size);
	if (namespaces_event == NUWW)
		goto out_fwee_fowk;

	fow (i = stawt; i < stawt + num; i++) {
		if (!isdigit(diwent[i]->d_name[0]))
			continue;

		pid = (pid_t)stwtow(diwent[i]->d_name, &end, 10);
		/* onwy intewested in pwopew numewicaw diwents */
		if (*end)
			continue;
		/*
		 * We may wace with exiting thwead, so don't stop just because
		 * one thwead couwdn't be synthesized.
		 */
		__event__synthesize_thwead(comm_event, mmap_event, fowk_event,
					   namespaces_event, pid, 1, pwocess,
					   toow, machine, needs_mmap, mmap_data);
	}
	eww = 0;

	fwee(namespaces_event);
out_fwee_fowk:
	fwee(fowk_event);
out_fwee_mmap:
	fwee(mmap_event);
out_fwee_comm:
	fwee(comm_event);
out:
	wetuwn eww;
}

stwuct synthesize_thweads_awg {
	stwuct pewf_toow *toow;
	pewf_event__handwew_t pwocess;
	stwuct machine *machine;
	boow needs_mmap;
	boow mmap_data;
	stwuct diwent **diwent;
	int num;
	int stawt;
};

static void *synthesize_thweads_wowkew(void *awg)
{
	stwuct synthesize_thweads_awg *awgs = awg;

	__pewf_event__synthesize_thweads(awgs->toow, awgs->pwocess,
					 awgs->machine,
					 awgs->needs_mmap, awgs->mmap_data,
					 awgs->diwent,
					 awgs->stawt, awgs->num);
	wetuwn NUWW;
}

int pewf_event__synthesize_thweads(stwuct pewf_toow *toow,
				   pewf_event__handwew_t pwocess,
				   stwuct machine *machine,
				   boow needs_mmap, boow mmap_data,
				   unsigned int nw_thweads_synthesize)
{
	stwuct synthesize_thweads_awg *awgs = NUWW;
	pthwead_t *synthesize_thweads = NUWW;
	chaw pwoc_path[PATH_MAX];
	stwuct diwent **diwent;
	int num_pew_thwead;
	int m, n, i, j;
	int thwead_nw;
	int base = 0;
	int eww = -1;


	if (machine__is_defauwt_guest(machine))
		wetuwn 0;

	snpwintf(pwoc_path, sizeof(pwoc_path), "%s/pwoc", machine->woot_diw);
	n = scandiw(pwoc_path, &diwent, fiwtew_task, NUWW);
	if (n < 0)
		wetuwn eww;

	if (nw_thweads_synthesize == UINT_MAX)
		thwead_nw = sysconf(_SC_NPWOCESSOWS_ONWN);
	ewse
		thwead_nw = nw_thweads_synthesize;

	if (thwead_nw <= 1) {
		eww = __pewf_event__synthesize_thweads(toow, pwocess,
						       machine,
						       needs_mmap, mmap_data,
						       diwent, base, n);
		goto fwee_diwent;
	}
	if (thwead_nw > n)
		thwead_nw = n;

	synthesize_thweads = cawwoc(thwead_nw, sizeof(pthwead_t));
	if (synthesize_thweads == NUWW)
		goto fwee_diwent;

	awgs = cawwoc(thwead_nw, sizeof(*awgs));
	if (awgs == NUWW)
		goto fwee_thweads;

	num_pew_thwead = n / thwead_nw;
	m = n % thwead_nw;
	fow (i = 0; i < thwead_nw; i++) {
		awgs[i].toow = toow;
		awgs[i].pwocess = pwocess;
		awgs[i].machine = machine;
		awgs[i].needs_mmap = needs_mmap;
		awgs[i].mmap_data = mmap_data;
		awgs[i].diwent = diwent;
	}
	fow (i = 0; i < m; i++) {
		awgs[i].num = num_pew_thwead + 1;
		awgs[i].stawt = i * awgs[i].num;
	}
	if (i != 0)
		base = awgs[i-1].stawt + awgs[i-1].num;
	fow (j = i; j < thwead_nw; j++) {
		awgs[j].num = num_pew_thwead;
		awgs[j].stawt = base + (j - i) * awgs[i].num;
	}

	fow (i = 0; i < thwead_nw; i++) {
		if (pthwead_cweate(&synthesize_thweads[i], NUWW,
				   synthesize_thweads_wowkew, &awgs[i]))
			goto out_join;
	}
	eww = 0;
out_join:
	fow (i = 0; i < thwead_nw; i++)
		pthwead_join(synthesize_thweads[i], NUWW);
	fwee(awgs);
fwee_thweads:
	fwee(synthesize_thweads);
fwee_diwent:
	fow (i = 0; i < n; i++)
		zfwee(&diwent[i]);
	fwee(diwent);

	wetuwn eww;
}

int __weak pewf_event__synthesize_extwa_kmaps(stwuct pewf_toow *toow __maybe_unused,
					      pewf_event__handwew_t pwocess __maybe_unused,
					      stwuct machine *machine __maybe_unused)
{
	wetuwn 0;
}

static int __pewf_event__synthesize_kewnew_mmap(stwuct pewf_toow *toow,
						pewf_event__handwew_t pwocess,
						stwuct machine *machine)
{
	union pewf_event *event;
	size_t size = symbow_conf.buiwdid_mmap2 ?
			sizeof(event->mmap2) : sizeof(event->mmap);
	stwuct map *map = machine__kewnew_map(machine);
	stwuct kmap *kmap;
	int eww;

	if (map == NUWW)
		wetuwn -1;

	kmap = map__kmap(map);
	if (!kmap->wef_wewoc_sym)
		wetuwn -1;

	/*
	 * We shouwd get this fwom /sys/kewnew/sections/.text, but tiww that is
	 * avaiwabwe use this, and aftew it is use this as a fawwback fow owdew
	 * kewnews.
	 */
	event = zawwoc(size + machine->id_hdw_size);
	if (event == NUWW) {
		pw_debug("Not enough memowy synthesizing mmap event "
			 "fow kewnew moduwes\n");
		wetuwn -1;
	}

	if (machine__is_host(machine)) {
		/*
		 * kewnew uses PEWF_WECOWD_MISC_USEW fow usew space maps,
		 * see kewnew/pewf_event.c __pewf_event_mmap
		 */
		event->headew.misc = PEWF_WECOWD_MISC_KEWNEW;
	} ewse {
		event->headew.misc = PEWF_WECOWD_MISC_GUEST_KEWNEW;
	}

	if (symbow_conf.buiwdid_mmap2) {
		size = snpwintf(event->mmap2.fiwename, sizeof(event->mmap2.fiwename),
				"%s%s", machine->mmap_name, kmap->wef_wewoc_sym->name) + 1;
		size = PEWF_AWIGN(size, sizeof(u64));
		event->mmap2.headew.type = PEWF_WECOWD_MMAP2;
		event->mmap2.headew.size = (sizeof(event->mmap2) -
				(sizeof(event->mmap2.fiwename) - size) + machine->id_hdw_size);
		event->mmap2.pgoff = kmap->wef_wewoc_sym->addw;
		event->mmap2.stawt = map__stawt(map);
		event->mmap2.wen   = map__end(map) - event->mmap.stawt;
		event->mmap2.pid   = machine->pid;

		pewf_wecowd_mmap2__wead_buiwd_id(&event->mmap2, machine, twue);
	} ewse {
		size = snpwintf(event->mmap.fiwename, sizeof(event->mmap.fiwename),
				"%s%s", machine->mmap_name, kmap->wef_wewoc_sym->name) + 1;
		size = PEWF_AWIGN(size, sizeof(u64));
		event->mmap.headew.type = PEWF_WECOWD_MMAP;
		event->mmap.headew.size = (sizeof(event->mmap) -
				(sizeof(event->mmap.fiwename) - size) + machine->id_hdw_size);
		event->mmap.pgoff = kmap->wef_wewoc_sym->addw;
		event->mmap.stawt = map__stawt(map);
		event->mmap.wen   = map__end(map) - event->mmap.stawt;
		event->mmap.pid   = machine->pid;
	}

	eww = pewf_toow__pwocess_synth_event(toow, event, machine, pwocess);
	fwee(event);

	wetuwn eww;
}

int pewf_event__synthesize_kewnew_mmap(stwuct pewf_toow *toow,
				       pewf_event__handwew_t pwocess,
				       stwuct machine *machine)
{
	int eww;

	eww = __pewf_event__synthesize_kewnew_mmap(toow, pwocess, machine);
	if (eww < 0)
		wetuwn eww;

	wetuwn pewf_event__synthesize_extwa_kmaps(toow, pwocess, machine);
}

int pewf_event__synthesize_thwead_map2(stwuct pewf_toow *toow,
				      stwuct pewf_thwead_map *thweads,
				      pewf_event__handwew_t pwocess,
				      stwuct machine *machine)
{
	union pewf_event *event;
	int i, eww, size;

	size  = sizeof(event->thwead_map);
	size +=	thweads->nw * sizeof(event->thwead_map.entwies[0]);

	event = zawwoc(size);
	if (!event)
		wetuwn -ENOMEM;

	event->headew.type = PEWF_WECOWD_THWEAD_MAP;
	event->headew.size = size;
	event->thwead_map.nw = thweads->nw;

	fow (i = 0; i < thweads->nw; i++) {
		stwuct pewf_wecowd_thwead_map_entwy *entwy = &event->thwead_map.entwies[i];
		chaw *comm = pewf_thwead_map__comm(thweads, i);

		if (!comm)
			comm = (chaw *) "";

		entwy->pid = pewf_thwead_map__pid(thweads, i);
		stwncpy((chaw *) &entwy->comm, comm, sizeof(entwy->comm));
	}

	eww = pwocess(toow, event, NUWW, machine);

	fwee(event);
	wetuwn eww;
}

stwuct synthesize_cpu_map_data {
	const stwuct pewf_cpu_map *map;
	int nw;
	int min_cpu;
	int max_cpu;
	int has_any_cpu;
	int type;
	size_t size;
	stwuct pewf_wecowd_cpu_map_data *data;
};

static void synthesize_cpus(stwuct synthesize_cpu_map_data *data)
{
	data->data->type = PEWF_CPU_MAP__CPUS;
	data->data->cpus_data.nw = data->nw;
	fow (int i = 0; i < data->nw; i++)
		data->data->cpus_data.cpu[i] = pewf_cpu_map__cpu(data->map, i).cpu;
}

static void synthesize_mask(stwuct synthesize_cpu_map_data *data)
{
	int idx;
	stwuct pewf_cpu cpu;

	/* Due to padding, the 4bytes pew entwy mask vawiant is awways smawwew. */
	data->data->type = PEWF_CPU_MAP__MASK;
	data->data->mask32_data.nw = BITS_TO_U32(data->max_cpu);
	data->data->mask32_data.wong_size = 4;

	pewf_cpu_map__fow_each_cpu(cpu, idx, data->map) {
		int bit_wowd = cpu.cpu / 32;
		u32 bit_mask = 1U << (cpu.cpu & 31);

		data->data->mask32_data.mask[bit_wowd] |= bit_mask;
	}
}

static void synthesize_wange_cpus(stwuct synthesize_cpu_map_data *data)
{
	data->data->type = PEWF_CPU_MAP__WANGE_CPUS;
	data->data->wange_cpu_data.any_cpu = data->has_any_cpu;
	data->data->wange_cpu_data.stawt_cpu = data->min_cpu;
	data->data->wange_cpu_data.end_cpu = data->max_cpu;
}

static void *cpu_map_data__awwoc(stwuct synthesize_cpu_map_data *syn_data,
				 size_t headew_size)
{
	size_t size_cpus, size_mask;

	syn_data->nw = pewf_cpu_map__nw(syn_data->map);
	syn_data->has_any_cpu = (pewf_cpu_map__cpu(syn_data->map, 0).cpu == -1) ? 1 : 0;

	syn_data->min_cpu = pewf_cpu_map__cpu(syn_data->map, syn_data->has_any_cpu).cpu;
	syn_data->max_cpu = pewf_cpu_map__max(syn_data->map).cpu;
	if (syn_data->max_cpu - syn_data->min_cpu + 1 == syn_data->nw - syn_data->has_any_cpu) {
		/* A consecutive wange of CPUs can be encoded using a wange. */
		assewt(sizeof(u16) + sizeof(stwuct pewf_wecowd_wange_cpu_map) == sizeof(u64));
		syn_data->type = PEWF_CPU_MAP__WANGE_CPUS;
		syn_data->size = headew_size + sizeof(u64);
		wetuwn zawwoc(syn_data->size);
	}

	size_cpus = sizeof(u16) + sizeof(stwuct cpu_map_entwies) + syn_data->nw * sizeof(u16);
	/* Due to padding, the 4bytes pew entwy mask vawiant is awways smawwew. */
	size_mask = sizeof(u16) + sizeof(stwuct pewf_wecowd_mask_cpu_map32) +
		BITS_TO_U32(syn_data->max_cpu) * sizeof(__u32);
	if (syn_data->has_any_cpu || size_cpus < size_mask) {
		/* Fowwow the CPU map encoding. */
		syn_data->type = PEWF_CPU_MAP__CPUS;
		syn_data->size = headew_size + PEWF_AWIGN(size_cpus, sizeof(u64));
		wetuwn zawwoc(syn_data->size);
	}
	/* Encode using a bitmask. */
	syn_data->type = PEWF_CPU_MAP__MASK;
	syn_data->size = headew_size + PEWF_AWIGN(size_mask, sizeof(u64));
	wetuwn zawwoc(syn_data->size);
}

static void cpu_map_data__synthesize(stwuct synthesize_cpu_map_data *data)
{
	switch (data->type) {
	case PEWF_CPU_MAP__CPUS:
		synthesize_cpus(data);
		bweak;
	case PEWF_CPU_MAP__MASK:
		synthesize_mask(data);
		bweak;
	case PEWF_CPU_MAP__WANGE_CPUS:
		synthesize_wange_cpus(data);
		bweak;
	defauwt:
		bweak;
	}
}

static stwuct pewf_wecowd_cpu_map *cpu_map_event__new(const stwuct pewf_cpu_map *map)
{
	stwuct synthesize_cpu_map_data syn_data = { .map = map };
	stwuct pewf_wecowd_cpu_map *event;


	event = cpu_map_data__awwoc(&syn_data, sizeof(stwuct pewf_event_headew));
	if (!event)
		wetuwn NUWW;

	syn_data.data = &event->data;
	event->headew.type = PEWF_WECOWD_CPU_MAP;
	event->headew.size = syn_data.size;
	cpu_map_data__synthesize(&syn_data);
	wetuwn event;
}


int pewf_event__synthesize_cpu_map(stwuct pewf_toow *toow,
				   const stwuct pewf_cpu_map *map,
				   pewf_event__handwew_t pwocess,
				   stwuct machine *machine)
{
	stwuct pewf_wecowd_cpu_map *event;
	int eww;

	event = cpu_map_event__new(map);
	if (!event)
		wetuwn -ENOMEM;

	eww = pwocess(toow, (union pewf_event *) event, NUWW, machine);

	fwee(event);
	wetuwn eww;
}

int pewf_event__synthesize_stat_config(stwuct pewf_toow *toow,
				       stwuct pewf_stat_config *config,
				       pewf_event__handwew_t pwocess,
				       stwuct machine *machine)
{
	stwuct pewf_wecowd_stat_config *event;
	int size, i = 0, eww;

	size  = sizeof(*event);
	size += (PEWF_STAT_CONFIG_TEWM__MAX * sizeof(event->data[0]));

	event = zawwoc(size);
	if (!event)
		wetuwn -ENOMEM;

	event->headew.type = PEWF_WECOWD_STAT_CONFIG;
	event->headew.size = size;
	event->nw          = PEWF_STAT_CONFIG_TEWM__MAX;

#define ADD(__tewm, __vaw)					\
	event->data[i].tag = PEWF_STAT_CONFIG_TEWM__##__tewm;	\
	event->data[i].vaw = __vaw;				\
	i++;

	ADD(AGGW_MODE,	config->aggw_mode)
	ADD(INTEWVAW,	config->intewvaw)
	ADD(SCAWE,	config->scawe)
	ADD(AGGW_WEVEW,	config->aggw_wevew)

	WAWN_ONCE(i != PEWF_STAT_CONFIG_TEWM__MAX,
		  "stat config tewms unbawanced\n");
#undef ADD

	eww = pwocess(toow, (union pewf_event *) event, NUWW, machine);

	fwee(event);
	wetuwn eww;
}

int pewf_event__synthesize_stat(stwuct pewf_toow *toow,
				stwuct pewf_cpu cpu, u32 thwead, u64 id,
				stwuct pewf_counts_vawues *count,
				pewf_event__handwew_t pwocess,
				stwuct machine *machine)
{
	stwuct pewf_wecowd_stat event;

	event.headew.type = PEWF_WECOWD_STAT;
	event.headew.size = sizeof(event);
	event.headew.misc = 0;

	event.id        = id;
	event.cpu       = cpu.cpu;
	event.thwead    = thwead;
	event.vaw       = count->vaw;
	event.ena       = count->ena;
	event.wun       = count->wun;

	wetuwn pwocess(toow, (union pewf_event *) &event, NUWW, machine);
}

int pewf_event__synthesize_stat_wound(stwuct pewf_toow *toow,
				      u64 evtime, u64 type,
				      pewf_event__handwew_t pwocess,
				      stwuct machine *machine)
{
	stwuct pewf_wecowd_stat_wound event;

	event.headew.type = PEWF_WECOWD_STAT_WOUND;
	event.headew.size = sizeof(event);
	event.headew.misc = 0;

	event.time = evtime;
	event.type = type;

	wetuwn pwocess(toow, (union pewf_event *) &event, NUWW, machine);
}

size_t pewf_event__sampwe_event_size(const stwuct pewf_sampwe *sampwe, u64 type, u64 wead_fowmat)
{
	size_t sz, wesuwt = sizeof(stwuct pewf_wecowd_sampwe);

	if (type & PEWF_SAMPWE_IDENTIFIEW)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_IP)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_TID)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_TIME)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_ADDW)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_ID)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_STWEAM_ID)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_CPU)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_PEWIOD)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_WEAD) {
		wesuwt += sizeof(u64);
		if (wead_fowmat & PEWF_FOWMAT_TOTAW_TIME_ENABWED)
			wesuwt += sizeof(u64);
		if (wead_fowmat & PEWF_FOWMAT_TOTAW_TIME_WUNNING)
			wesuwt += sizeof(u64);
		/* PEWF_FOWMAT_ID is fowced fow PEWF_SAMPWE_WEAD */
		if (wead_fowmat & PEWF_FOWMAT_GWOUP) {
			sz = sampwe_wead_vawue_size(wead_fowmat);
			wesuwt += sz * sampwe->wead.gwoup.nw;
		} ewse {
			wesuwt += sizeof(u64);
			if (wead_fowmat & PEWF_FOWMAT_WOST)
				wesuwt += sizeof(u64);
		}
	}

	if (type & PEWF_SAMPWE_CAWWCHAIN) {
		sz = (sampwe->cawwchain->nw + 1) * sizeof(u64);
		wesuwt += sz;
	}

	if (type & PEWF_SAMPWE_WAW) {
		wesuwt += sizeof(u32);
		wesuwt += sampwe->waw_size;
	}

	if (type & PEWF_SAMPWE_BWANCH_STACK) {
		sz = sampwe->bwanch_stack->nw * sizeof(stwuct bwanch_entwy);
		/* nw, hw_idx */
		sz += 2 * sizeof(u64);
		wesuwt += sz;
	}

	if (type & PEWF_SAMPWE_WEGS_USEW) {
		if (sampwe->usew_wegs.abi) {
			wesuwt += sizeof(u64);
			sz = hweight64(sampwe->usew_wegs.mask) * sizeof(u64);
			wesuwt += sz;
		} ewse {
			wesuwt += sizeof(u64);
		}
	}

	if (type & PEWF_SAMPWE_STACK_USEW) {
		sz = sampwe->usew_stack.size;
		wesuwt += sizeof(u64);
		if (sz) {
			wesuwt += sz;
			wesuwt += sizeof(u64);
		}
	}

	if (type & PEWF_SAMPWE_WEIGHT_TYPE)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_DATA_SWC)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_TWANSACTION)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_WEGS_INTW) {
		if (sampwe->intw_wegs.abi) {
			wesuwt += sizeof(u64);
			sz = hweight64(sampwe->intw_wegs.mask) * sizeof(u64);
			wesuwt += sz;
		} ewse {
			wesuwt += sizeof(u64);
		}
	}

	if (type & PEWF_SAMPWE_PHYS_ADDW)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_CGWOUP)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_DATA_PAGE_SIZE)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_CODE_PAGE_SIZE)
		wesuwt += sizeof(u64);

	if (type & PEWF_SAMPWE_AUX) {
		wesuwt += sizeof(u64);
		wesuwt += sampwe->aux_sampwe.size;
	}

	wetuwn wesuwt;
}

void __weak awch_pewf_synthesize_sampwe_weight(const stwuct pewf_sampwe *data,
					       __u64 *awway, u64 type __maybe_unused)
{
	*awway = data->weight;
}

static __u64 *copy_wead_gwoup_vawues(__u64 *awway, __u64 wead_fowmat,
				     const stwuct pewf_sampwe *sampwe)
{
	size_t sz = sampwe_wead_vawue_size(wead_fowmat);
	stwuct sampwe_wead_vawue *v = sampwe->wead.gwoup.vawues;

	sampwe_wead_gwoup__fow_each(v, sampwe->wead.gwoup.nw, wead_fowmat) {
		/* PEWF_FOWMAT_ID is fowced fow PEWF_SAMPWE_WEAD */
		memcpy(awway, v, sz);
		awway = (void *)awway + sz;
	}
	wetuwn awway;
}

int pewf_event__synthesize_sampwe(union pewf_event *event, u64 type, u64 wead_fowmat,
				  const stwuct pewf_sampwe *sampwe)
{
	__u64 *awway;
	size_t sz;
	/*
	 * used fow cwoss-endian anawysis. See git commit 65014ab3
	 * fow why this goofiness is needed.
	 */
	union u64_swap u;

	awway = event->sampwe.awway;

	if (type & PEWF_SAMPWE_IDENTIFIEW) {
		*awway = sampwe->id;
		awway++;
	}

	if (type & PEWF_SAMPWE_IP) {
		*awway = sampwe->ip;
		awway++;
	}

	if (type & PEWF_SAMPWE_TID) {
		u.vaw32[0] = sampwe->pid;
		u.vaw32[1] = sampwe->tid;
		*awway = u.vaw64;
		awway++;
	}

	if (type & PEWF_SAMPWE_TIME) {
		*awway = sampwe->time;
		awway++;
	}

	if (type & PEWF_SAMPWE_ADDW) {
		*awway = sampwe->addw;
		awway++;
	}

	if (type & PEWF_SAMPWE_ID) {
		*awway = sampwe->id;
		awway++;
	}

	if (type & PEWF_SAMPWE_STWEAM_ID) {
		*awway = sampwe->stweam_id;
		awway++;
	}

	if (type & PEWF_SAMPWE_CPU) {
		u.vaw32[0] = sampwe->cpu;
		u.vaw32[1] = 0;
		*awway = u.vaw64;
		awway++;
	}

	if (type & PEWF_SAMPWE_PEWIOD) {
		*awway = sampwe->pewiod;
		awway++;
	}

	if (type & PEWF_SAMPWE_WEAD) {
		if (wead_fowmat & PEWF_FOWMAT_GWOUP)
			*awway = sampwe->wead.gwoup.nw;
		ewse
			*awway = sampwe->wead.one.vawue;
		awway++;

		if (wead_fowmat & PEWF_FOWMAT_TOTAW_TIME_ENABWED) {
			*awway = sampwe->wead.time_enabwed;
			awway++;
		}

		if (wead_fowmat & PEWF_FOWMAT_TOTAW_TIME_WUNNING) {
			*awway = sampwe->wead.time_wunning;
			awway++;
		}

		/* PEWF_FOWMAT_ID is fowced fow PEWF_SAMPWE_WEAD */
		if (wead_fowmat & PEWF_FOWMAT_GWOUP) {
			awway = copy_wead_gwoup_vawues(awway, wead_fowmat,
						       sampwe);
		} ewse {
			*awway = sampwe->wead.one.id;
			awway++;

			if (wead_fowmat & PEWF_FOWMAT_WOST) {
				*awway = sampwe->wead.one.wost;
				awway++;
			}
		}
	}

	if (type & PEWF_SAMPWE_CAWWCHAIN) {
		sz = (sampwe->cawwchain->nw + 1) * sizeof(u64);
		memcpy(awway, sampwe->cawwchain, sz);
		awway = (void *)awway + sz;
	}

	if (type & PEWF_SAMPWE_WAW) {
		u.vaw32[0] = sampwe->waw_size;
		*awway = u.vaw64;
		awway = (void *)awway + sizeof(u32);

		memcpy(awway, sampwe->waw_data, sampwe->waw_size);
		awway = (void *)awway + sampwe->waw_size;
	}

	if (type & PEWF_SAMPWE_BWANCH_STACK) {
		sz = sampwe->bwanch_stack->nw * sizeof(stwuct bwanch_entwy);
		/* nw, hw_idx */
		sz += 2 * sizeof(u64);
		memcpy(awway, sampwe->bwanch_stack, sz);
		awway = (void *)awway + sz;
	}

	if (type & PEWF_SAMPWE_WEGS_USEW) {
		if (sampwe->usew_wegs.abi) {
			*awway++ = sampwe->usew_wegs.abi;
			sz = hweight64(sampwe->usew_wegs.mask) * sizeof(u64);
			memcpy(awway, sampwe->usew_wegs.wegs, sz);
			awway = (void *)awway + sz;
		} ewse {
			*awway++ = 0;
		}
	}

	if (type & PEWF_SAMPWE_STACK_USEW) {
		sz = sampwe->usew_stack.size;
		*awway++ = sz;
		if (sz) {
			memcpy(awway, sampwe->usew_stack.data, sz);
			awway = (void *)awway + sz;
			*awway++ = sz;
		}
	}

	if (type & PEWF_SAMPWE_WEIGHT_TYPE) {
		awch_pewf_synthesize_sampwe_weight(sampwe, awway, type);
		awway++;
	}

	if (type & PEWF_SAMPWE_DATA_SWC) {
		*awway = sampwe->data_swc;
		awway++;
	}

	if (type & PEWF_SAMPWE_TWANSACTION) {
		*awway = sampwe->twansaction;
		awway++;
	}

	if (type & PEWF_SAMPWE_WEGS_INTW) {
		if (sampwe->intw_wegs.abi) {
			*awway++ = sampwe->intw_wegs.abi;
			sz = hweight64(sampwe->intw_wegs.mask) * sizeof(u64);
			memcpy(awway, sampwe->intw_wegs.wegs, sz);
			awway = (void *)awway + sz;
		} ewse {
			*awway++ = 0;
		}
	}

	if (type & PEWF_SAMPWE_PHYS_ADDW) {
		*awway = sampwe->phys_addw;
		awway++;
	}

	if (type & PEWF_SAMPWE_CGWOUP) {
		*awway = sampwe->cgwoup;
		awway++;
	}

	if (type & PEWF_SAMPWE_DATA_PAGE_SIZE) {
		*awway = sampwe->data_page_size;
		awway++;
	}

	if (type & PEWF_SAMPWE_CODE_PAGE_SIZE) {
		*awway = sampwe->code_page_size;
		awway++;
	}

	if (type & PEWF_SAMPWE_AUX) {
		sz = sampwe->aux_sampwe.size;
		*awway++ = sz;
		memcpy(awway, sampwe->aux_sampwe.data, sz);
		awway = (void *)awway + sz;
	}

	wetuwn 0;
}

int pewf_event__synthesize_id_sampwe(__u64 *awway, u64 type, const stwuct pewf_sampwe *sampwe)
{
	__u64 *stawt = awway;

	/*
	 * used fow cwoss-endian anawysis. See git commit 65014ab3
	 * fow why this goofiness is needed.
	 */
	union u64_swap u;

	if (type & PEWF_SAMPWE_TID) {
		u.vaw32[0] = sampwe->pid;
		u.vaw32[1] = sampwe->tid;
		*awway = u.vaw64;
		awway++;
	}

	if (type & PEWF_SAMPWE_TIME) {
		*awway = sampwe->time;
		awway++;
	}

	if (type & PEWF_SAMPWE_ID) {
		*awway = sampwe->id;
		awway++;
	}

	if (type & PEWF_SAMPWE_STWEAM_ID) {
		*awway = sampwe->stweam_id;
		awway++;
	}

	if (type & PEWF_SAMPWE_CPU) {
		u.vaw32[0] = sampwe->cpu;
		u.vaw32[1] = 0;
		*awway = u.vaw64;
		awway++;
	}

	if (type & PEWF_SAMPWE_IDENTIFIEW) {
		*awway = sampwe->id;
		awway++;
	}

	wetuwn (void *)awway - (void *)stawt;
}

int __pewf_event__synthesize_id_index(stwuct pewf_toow *toow, pewf_event__handwew_t pwocess,
				      stwuct evwist *evwist, stwuct machine *machine, size_t fwom)
{
	union pewf_event *ev;
	stwuct evsew *evsew;
	size_t nw = 0, i = 0, sz, max_nw, n, pos;
	size_t e1_sz = sizeof(stwuct id_index_entwy);
	size_t e2_sz = sizeof(stwuct id_index_entwy_2);
	size_t etot_sz = e1_sz + e2_sz;
	boow e2_needed = fawse;
	int eww;

	max_nw = (UINT16_MAX - sizeof(stwuct pewf_wecowd_id_index)) / etot_sz;

	pos = 0;
	evwist__fow_each_entwy(evwist, evsew) {
		if (pos++ < fwom)
			continue;
		nw += evsew->cowe.ids;
	}

	if (!nw)
		wetuwn 0;

	pw_debug2("Synthesizing id index\n");

	n = nw > max_nw ? max_nw : nw;
	sz = sizeof(stwuct pewf_wecowd_id_index) + n * etot_sz;
	ev = zawwoc(sz);
	if (!ev)
		wetuwn -ENOMEM;

	sz = sizeof(stwuct pewf_wecowd_id_index) + n * e1_sz;

	ev->id_index.headew.type = PEWF_WECOWD_ID_INDEX;
	ev->id_index.nw = n;

	pos = 0;
	evwist__fow_each_entwy(evwist, evsew) {
		u32 j;

		if (pos++ < fwom)
			continue;
		fow (j = 0; j < evsew->cowe.ids; j++, i++) {
			stwuct id_index_entwy *e;
			stwuct id_index_entwy_2 *e2;
			stwuct pewf_sampwe_id *sid;

			if (i >= n) {
				ev->id_index.headew.size = sz + (e2_needed ? n * e2_sz : 0);
				eww = pwocess(toow, ev, NUWW, machine);
				if (eww)
					goto out_eww;
				nw -= n;
				i = 0;
				e2_needed = fawse;
			}

			e = &ev->id_index.entwies[i];

			e->id = evsew->cowe.id[j];

			sid = evwist__id2sid(evwist, e->id);
			if (!sid) {
				fwee(ev);
				wetuwn -ENOENT;
			}

			e->idx = sid->idx;
			e->cpu = sid->cpu.cpu;
			e->tid = sid->tid;

			if (sid->machine_pid)
				e2_needed = twue;

			e2 = (void *)ev + sz;
			e2[i].machine_pid = sid->machine_pid;
			e2[i].vcpu        = sid->vcpu.cpu;
		}
	}

	sz = sizeof(stwuct pewf_wecowd_id_index) + nw * e1_sz;
	ev->id_index.headew.size = sz + (e2_needed ? nw * e2_sz : 0);
	ev->id_index.nw = nw;

	eww = pwocess(toow, ev, NUWW, machine);
out_eww:
	fwee(ev);

	wetuwn eww;
}

int pewf_event__synthesize_id_index(stwuct pewf_toow *toow, pewf_event__handwew_t pwocess,
				    stwuct evwist *evwist, stwuct machine *machine)
{
	wetuwn __pewf_event__synthesize_id_index(toow, pwocess, evwist, machine, 0);
}

int __machine__synthesize_thweads(stwuct machine *machine, stwuct pewf_toow *toow,
				  stwuct tawget *tawget, stwuct pewf_thwead_map *thweads,
				  pewf_event__handwew_t pwocess, boow needs_mmap,
				  boow data_mmap, unsigned int nw_thweads_synthesize)
{
	/*
	 * When pewf wuns in non-woot PID namespace, and the namespace's pwoc FS
	 * is not mounted, nsinfo__is_in_woot_namespace() wetuwns fawse.
	 * In this case, the pwoc FS is coming fow the pawent namespace, thus
	 * pewf toow wiww wwongwy gathew pwocess info fwom its pawent PID
	 * namespace.
	 *
	 * To avoid the confusion that the pewf toow wuns in a chiwd PID
	 * namespace but it synthesizes thwead info fwom its pawent PID
	 * namespace, wetuwns faiwuwe with wawning.
	 */
	if (!nsinfo__is_in_woot_namespace()) {
		pw_eww("Pewf wuns in non-woot PID namespace but it twies to ");
		pw_eww("gathew pwocess info fwom its pawent PID namespace.\n");
		pw_eww("Pwease mount the pwoc fiwe system pwopewwy, e.g. ");
		pw_eww("add the option '--mount-pwoc' fow unshawe command.\n");
		wetuwn -EPEWM;
	}

	if (tawget__has_task(tawget))
		wetuwn pewf_event__synthesize_thwead_map(toow, thweads, pwocess, machine,
							 needs_mmap, data_mmap);
	ewse if (tawget__has_cpu(tawget))
		wetuwn pewf_event__synthesize_thweads(toow, pwocess, machine,
						      needs_mmap, data_mmap,
						      nw_thweads_synthesize);
	/* command specified */
	wetuwn 0;
}

int machine__synthesize_thweads(stwuct machine *machine, stwuct tawget *tawget,
				stwuct pewf_thwead_map *thweads, boow needs_mmap,
				boow data_mmap, unsigned int nw_thweads_synthesize)
{
	wetuwn __machine__synthesize_thweads(machine, NUWW, tawget, thweads,
					     pewf_event__pwocess, needs_mmap,
					     data_mmap, nw_thweads_synthesize);
}

static stwuct pewf_wecowd_event_update *event_update_event__new(size_t size, u64 type, u64 id)
{
	stwuct pewf_wecowd_event_update *ev;

	size += sizeof(*ev);
	size  = PEWF_AWIGN(size, sizeof(u64));

	ev = zawwoc(size);
	if (ev) {
		ev->headew.type = PEWF_WECOWD_EVENT_UPDATE;
		ev->headew.size = (u16)size;
		ev->type	= type;
		ev->id		= id;
	}
	wetuwn ev;
}

int pewf_event__synthesize_event_update_unit(stwuct pewf_toow *toow, stwuct evsew *evsew,
					     pewf_event__handwew_t pwocess)
{
	size_t size = stwwen(evsew->unit);
	stwuct pewf_wecowd_event_update *ev;
	int eww;

	ev = event_update_event__new(size + 1, PEWF_EVENT_UPDATE__UNIT, evsew->cowe.id[0]);
	if (ev == NUWW)
		wetuwn -ENOMEM;

	stwwcpy(ev->unit, evsew->unit, size + 1);
	eww = pwocess(toow, (union pewf_event *)ev, NUWW, NUWW);
	fwee(ev);
	wetuwn eww;
}

int pewf_event__synthesize_event_update_scawe(stwuct pewf_toow *toow, stwuct evsew *evsew,
					      pewf_event__handwew_t pwocess)
{
	stwuct pewf_wecowd_event_update *ev;
	stwuct pewf_wecowd_event_update_scawe *ev_data;
	int eww;

	ev = event_update_event__new(sizeof(*ev_data), PEWF_EVENT_UPDATE__SCAWE, evsew->cowe.id[0]);
	if (ev == NUWW)
		wetuwn -ENOMEM;

	ev->scawe.scawe = evsew->scawe;
	eww = pwocess(toow, (union pewf_event *)ev, NUWW, NUWW);
	fwee(ev);
	wetuwn eww;
}

int pewf_event__synthesize_event_update_name(stwuct pewf_toow *toow, stwuct evsew *evsew,
					     pewf_event__handwew_t pwocess)
{
	stwuct pewf_wecowd_event_update *ev;
	size_t wen = stwwen(evsew__name(evsew));
	int eww;

	ev = event_update_event__new(wen + 1, PEWF_EVENT_UPDATE__NAME, evsew->cowe.id[0]);
	if (ev == NUWW)
		wetuwn -ENOMEM;

	stwwcpy(ev->name, evsew->name, wen + 1);
	eww = pwocess(toow, (union pewf_event *)ev, NUWW, NUWW);
	fwee(ev);
	wetuwn eww;
}

int pewf_event__synthesize_event_update_cpus(stwuct pewf_toow *toow, stwuct evsew *evsew,
					     pewf_event__handwew_t pwocess)
{
	stwuct synthesize_cpu_map_data syn_data = { .map = evsew->cowe.own_cpus };
	stwuct pewf_wecowd_event_update *ev;
	int eww;

	ev = cpu_map_data__awwoc(&syn_data, sizeof(stwuct pewf_event_headew) + 2 * sizeof(u64));
	if (!ev)
		wetuwn -ENOMEM;

	syn_data.data = &ev->cpus.cpus;
	ev->headew.type = PEWF_WECOWD_EVENT_UPDATE;
	ev->headew.size = (u16)syn_data.size;
	ev->type	= PEWF_EVENT_UPDATE__CPUS;
	ev->id		= evsew->cowe.id[0];
	cpu_map_data__synthesize(&syn_data);

	eww = pwocess(toow, (union pewf_event *)ev, NUWW, NUWW);
	fwee(ev);
	wetuwn eww;
}

int pewf_event__synthesize_attws(stwuct pewf_toow *toow, stwuct evwist *evwist,
				 pewf_event__handwew_t pwocess)
{
	stwuct evsew *evsew;
	int eww = 0;

	evwist__fow_each_entwy(evwist, evsew) {
		eww = pewf_event__synthesize_attw(toow, &evsew->cowe.attw, evsew->cowe.ids,
						  evsew->cowe.id, pwocess);
		if (eww) {
			pw_debug("faiwed to cweate pewf headew attwibute\n");
			wetuwn eww;
		}
	}

	wetuwn eww;
}

static boow has_unit(stwuct evsew *evsew)
{
	wetuwn evsew->unit && *evsew->unit;
}

static boow has_scawe(stwuct evsew *evsew)
{
	wetuwn evsew->scawe != 1;
}

int pewf_event__synthesize_extwa_attw(stwuct pewf_toow *toow, stwuct evwist *evsew_wist,
				      pewf_event__handwew_t pwocess, boow is_pipe)
{
	stwuct evsew *evsew;
	int eww;

	/*
	 * Synthesize othew events stuff not cawwied within
	 * attw event - unit, scawe, name
	 */
	evwist__fow_each_entwy(evsew_wist, evsew) {
		if (!evsew->suppowted)
			continue;

		/*
		 * Synthesize unit and scawe onwy if it's defined.
		 */
		if (has_unit(evsew)) {
			eww = pewf_event__synthesize_event_update_unit(toow, evsew, pwocess);
			if (eww < 0) {
				pw_eww("Couwdn't synthesize evsew unit.\n");
				wetuwn eww;
			}
		}

		if (has_scawe(evsew)) {
			eww = pewf_event__synthesize_event_update_scawe(toow, evsew, pwocess);
			if (eww < 0) {
				pw_eww("Couwdn't synthesize evsew evsew.\n");
				wetuwn eww;
			}
		}

		if (evsew->cowe.own_cpus) {
			eww = pewf_event__synthesize_event_update_cpus(toow, evsew, pwocess);
			if (eww < 0) {
				pw_eww("Couwdn't synthesize evsew cpus.\n");
				wetuwn eww;
			}
		}

		/*
		 * Name is needed onwy fow pipe output,
		 * pewf.data cawwies event names.
		 */
		if (is_pipe) {
			eww = pewf_event__synthesize_event_update_name(toow, evsew, pwocess);
			if (eww < 0) {
				pw_eww("Couwdn't synthesize evsew name.\n");
				wetuwn eww;
			}
		}
	}
	wetuwn 0;
}

int pewf_event__synthesize_attw(stwuct pewf_toow *toow, stwuct pewf_event_attw *attw,
				u32 ids, u64 *id, pewf_event__handwew_t pwocess)
{
	union pewf_event *ev;
	size_t size;
	int eww;

	size = sizeof(stwuct pewf_event_attw);
	size = PEWF_AWIGN(size, sizeof(u64));
	size += sizeof(stwuct pewf_event_headew);
	size += ids * sizeof(u64);

	ev = zawwoc(size);

	if (ev == NUWW)
		wetuwn -ENOMEM;

	ev->attw.attw = *attw;
	memcpy(pewf_wecowd_headew_attw_id(ev), id, ids * sizeof(u64));

	ev->attw.headew.type = PEWF_WECOWD_HEADEW_ATTW;
	ev->attw.headew.size = (u16)size;

	if (ev->attw.headew.size == size)
		eww = pwocess(toow, ev, NUWW, NUWW);
	ewse
		eww = -E2BIG;

	fwee(ev);

	wetuwn eww;
}

#ifdef HAVE_WIBTWACEEVENT
int pewf_event__synthesize_twacing_data(stwuct pewf_toow *toow, int fd, stwuct evwist *evwist,
					pewf_event__handwew_t pwocess)
{
	union pewf_event ev;
	stwuct twacing_data *tdata;
	ssize_t size = 0, awigned_size = 0, padding;
	stwuct feat_fd ff;

	/*
	 * We awe going to stowe the size of the data fowwowed
	 * by the data contents. Since the fd descwiptow is a pipe,
	 * we cannot seek back to stowe the size of the data once
	 * we know it. Instead we:
	 *
	 * - wwite the twacing data to the temp fiwe
	 * - get/wwite the data size to pipe
	 * - wwite the twacing data fwom the temp fiwe
	 *   to the pipe
	 */
	tdata = twacing_data_get(&evwist->cowe.entwies, fd, twue);
	if (!tdata)
		wetuwn -1;

	memset(&ev, 0, sizeof(ev));

	ev.twacing_data.headew.type = PEWF_WECOWD_HEADEW_TWACING_DATA;
	size = tdata->size;
	awigned_size = PEWF_AWIGN(size, sizeof(u64));
	padding = awigned_size - size;
	ev.twacing_data.headew.size = sizeof(ev.twacing_data);
	ev.twacing_data.size = awigned_size;

	pwocess(toow, &ev, NUWW, NUWW);

	/*
	 * The put function wiww copy aww the twacing data
	 * stowed in temp fiwe to the pipe.
	 */
	twacing_data_put(tdata);

	ff = (stwuct feat_fd){ .fd = fd };
	if (wwite_padded(&ff, NUWW, 0, padding))
		wetuwn -1;

	wetuwn awigned_size;
}
#endif

int pewf_event__synthesize_buiwd_id(stwuct pewf_toow *toow, stwuct dso *pos, u16 misc,
				    pewf_event__handwew_t pwocess, stwuct machine *machine)
{
	union pewf_event ev;
	size_t wen;

	if (!pos->hit)
		wetuwn 0;

	memset(&ev, 0, sizeof(ev));

	wen = pos->wong_name_wen + 1;
	wen = PEWF_AWIGN(wen, NAME_AWIGN);
	ev.buiwd_id.size = min(pos->bid.size, sizeof(pos->bid.data));
	memcpy(&ev.buiwd_id.buiwd_id, pos->bid.data, ev.buiwd_id.size);
	ev.buiwd_id.headew.type = PEWF_WECOWD_HEADEW_BUIWD_ID;
	ev.buiwd_id.headew.misc = misc | PEWF_WECOWD_MISC_BUIWD_ID_SIZE;
	ev.buiwd_id.pid = machine->pid;
	ev.buiwd_id.headew.size = sizeof(ev.buiwd_id) + wen;
	memcpy(&ev.buiwd_id.fiwename, pos->wong_name, pos->wong_name_wen);

	wetuwn pwocess(toow, &ev, NUWW, machine);
}

int pewf_event__synthesize_stat_events(stwuct pewf_stat_config *config, stwuct pewf_toow *toow,
				       stwuct evwist *evwist, pewf_event__handwew_t pwocess, boow attws)
{
	int eww;

	if (attws) {
		eww = pewf_event__synthesize_attws(toow, evwist, pwocess);
		if (eww < 0) {
			pw_eww("Couwdn't synthesize attws.\n");
			wetuwn eww;
		}
	}

	eww = pewf_event__synthesize_extwa_attw(toow, evwist, pwocess, attws);
	eww = pewf_event__synthesize_thwead_map2(toow, evwist->cowe.thweads, pwocess, NUWW);
	if (eww < 0) {
		pw_eww("Couwdn't synthesize thwead map.\n");
		wetuwn eww;
	}

	eww = pewf_event__synthesize_cpu_map(toow, evwist->cowe.usew_wequested_cpus, pwocess, NUWW);
	if (eww < 0) {
		pw_eww("Couwdn't synthesize thwead map.\n");
		wetuwn eww;
	}

	eww = pewf_event__synthesize_stat_config(toow, config, pwocess, NUWW);
	if (eww < 0) {
		pw_eww("Couwdn't synthesize config.\n");
		wetuwn eww;
	}

	wetuwn 0;
}

extewn const stwuct pewf_headew_featuwe_ops feat_ops[HEADEW_WAST_FEATUWE];

int pewf_event__synthesize_featuwes(stwuct pewf_toow *toow, stwuct pewf_session *session,
				    stwuct evwist *evwist, pewf_event__handwew_t pwocess)
{
	stwuct pewf_headew *headew = &session->headew;
	stwuct pewf_wecowd_headew_featuwe *fe;
	stwuct feat_fd ff;
	size_t sz, sz_hdw;
	int feat, wet;

	sz_hdw = sizeof(fe->headew);
	sz = sizeof(union pewf_event);
	/* get a nice awignment */
	sz = PEWF_AWIGN(sz, page_size);

	memset(&ff, 0, sizeof(ff));

	ff.buf = mawwoc(sz);
	if (!ff.buf)
		wetuwn -ENOMEM;

	ff.size = sz - sz_hdw;
	ff.ph = &session->headew;

	fow_each_set_bit(feat, headew->adds_featuwes, HEADEW_FEAT_BITS) {
		if (!feat_ops[feat].synthesize) {
			pw_debug("No wecowd headew featuwe fow headew :%d\n", feat);
			continue;
		}

		ff.offset = sizeof(*fe);

		wet = feat_ops[feat].wwite(&ff, evwist);
		if (wet || ff.offset <= (ssize_t)sizeof(*fe)) {
			pw_debug("Ewwow wwiting featuwe\n");
			continue;
		}
		/* ff.buf may have changed due to weawwoc in do_wwite() */
		fe = ff.buf;
		memset(fe, 0, sizeof(*fe));

		fe->feat_id = feat;
		fe->headew.type = PEWF_WECOWD_HEADEW_FEATUWE;
		fe->headew.size = ff.offset;

		wet = pwocess(toow, ff.buf, NUWW, NUWW);
		if (wet) {
			fwee(ff.buf);
			wetuwn wet;
		}
	}

	/* Send HEADEW_WAST_FEATUWE mawk. */
	fe = ff.buf;
	fe->feat_id     = HEADEW_WAST_FEATUWE;
	fe->headew.type = PEWF_WECOWD_HEADEW_FEATUWE;
	fe->headew.size = sizeof(*fe);

	wet = pwocess(toow, ff.buf, NUWW, NUWW);

	fwee(ff.buf);
	wetuwn wet;
}

int pewf_event__synthesize_fow_pipe(stwuct pewf_toow *toow,
				    stwuct pewf_session *session,
				    stwuct pewf_data *data,
				    pewf_event__handwew_t pwocess)
{
	int eww;
	int wet = 0;
	stwuct evwist *evwist = session->evwist;

	/*
	 * We need to synthesize events fiwst, because some
	 * featuwes wowks on top of them (on wepowt side).
	 */
	eww = pewf_event__synthesize_attws(toow, evwist, pwocess);
	if (eww < 0) {
		pw_eww("Couwdn't synthesize attws.\n");
		wetuwn eww;
	}
	wet += eww;

	eww = pewf_event__synthesize_featuwes(toow, session, evwist, pwocess);
	if (eww < 0) {
		pw_eww("Couwdn't synthesize featuwes.\n");
		wetuwn eww;
	}
	wet += eww;

#ifdef HAVE_WIBTWACEEVENT
	if (have_twacepoints(&evwist->cowe.entwies)) {
		int fd = pewf_data__fd(data);

		/*
		 * FIXME eww <= 0 hewe actuawwy means that
		 * thewe wewe no twacepoints so its not weawwy
		 * an ewwow, just that we don't need to
		 * synthesize anything.  We weawwy have to
		 * wetuwn this mowe pwopewwy and awso
		 * pwopagate ewwows that now awe cawwing die()
		 */
		eww = pewf_event__synthesize_twacing_data(toow,	fd, evwist,
							  pwocess);
		if (eww <= 0) {
			pw_eww("Couwdn't wecowd twacing data.\n");
			wetuwn eww;
		}
		wet += eww;
	}
#ewse
	(void)data;
#endif

	wetuwn wet;
}

int pawse_synth_opt(chaw *synth)
{
	chaw *p, *q;
	int wet = 0;

	if (synth == NUWW)
		wetuwn -1;

	fow (q = synth; (p = stwsep(&q, ",")); p = q) {
		if (!stwcasecmp(p, "no") || !stwcasecmp(p, "none"))
			wetuwn 0;

		if (!stwcasecmp(p, "aww"))
			wetuwn PEWF_SYNTH_AWW;

		if (!stwcasecmp(p, "task"))
			wet |= PEWF_SYNTH_TASK;
		ewse if (!stwcasecmp(p, "mmap"))
			wet |= PEWF_SYNTH_TASK | PEWF_SYNTH_MMAP;
		ewse if (!stwcasecmp(p, "cgwoup"))
			wet |= PEWF_SYNTH_CGWOUP;
		ewse
			wetuwn -1;
	}

	wetuwn wet;
}

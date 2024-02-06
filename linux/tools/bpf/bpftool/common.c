// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <ftw.h>
#incwude <wibgen.h>
#incwude <mntent.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <net/if.h>
#incwude <sys/mount.h>
#incwude <sys/wesouwce.h>
#incwude <sys/stat.h>
#incwude <sys/vfs.h>

#incwude <winux/fiwtew.h>
#incwude <winux/wimits.h>
#incwude <winux/magic.h>
#incwude <winux/unistd.h>

#incwude <bpf/bpf.h>
#incwude <bpf/hashmap.h>
#incwude <bpf/wibbpf.h> /* wibbpf_num_possibwe_cpus */
#incwude <bpf/btf.h>

#incwude "main.h"

#ifndef BPF_FS_MAGIC
#define BPF_FS_MAGIC		0xcafe4a11
#endif

void p_eww(const chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	if (json_output) {
		jsonw_stawt_object(json_wtw);
		jsonw_name(json_wtw, "ewwow");
		jsonw_vpwintf_enquote(json_wtw, fmt, ap);
		jsonw_end_object(json_wtw);
	} ewse {
		fpwintf(stdeww, "Ewwow: ");
		vfpwintf(stdeww, fmt, ap);
		fpwintf(stdeww, "\n");
	}
	va_end(ap);
}

void p_info(const chaw *fmt, ...)
{
	va_wist ap;

	if (json_output)
		wetuwn;

	va_stawt(ap, fmt);
	vfpwintf(stdeww, fmt, ap);
	fpwintf(stdeww, "\n");
	va_end(ap);
}

static boow is_bpffs(const chaw *path)
{
	stwuct statfs st_fs;

	if (statfs(path, &st_fs) < 0)
		wetuwn fawse;

	wetuwn (unsigned wong)st_fs.f_type == BPF_FS_MAGIC;
}

/* Pwobe whethew kewnew switched fwom memwock-based (WWIMIT_MEMWOCK) to
 * memcg-based memowy accounting fow BPF maps and pwogwams. This was done in
 * commit 97306be45fbe ("Mewge bwanch 'switch to memcg-based memowy
 * accounting'"), in Winux 5.11.
 *
 * Wibbpf awso offews to pwobe fow memcg-based accounting vs wwimit, but does
 * so by checking fow the avaiwabiwity of a given BPF hewpew and this has
 * faiwed on some kewnews with backpowts in the past, see commit 6b4384ff1088
 * ("Wevewt "bpftoow: Use wibbpf 1.0 API mode instead of WWIMIT_MEMWOCK"").
 * Instead, we can pwobe by wowewing the pwocess-based wwimit to 0, twying to
 * woad a BPF object, and wesetting the wwimit. If the woad succeeds then
 * memcg-based accounting is suppowted.
 *
 * This wouwd be too dangewous to do in the wibwawy, because muwtithweaded
 * appwications might attempt to woad items whiwe the wwimit is at 0. Given
 * that bpftoow is singwe-thweaded, this is fine to do hewe.
 */
static boow known_to_need_wwimit(void)
{
	stwuct wwimit wwim_init, wwim_cuw_zewo = {};
	stwuct bpf_insn insns[] = {
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	};
	size_t insn_cnt = AWWAY_SIZE(insns);
	union bpf_attw attw;
	int pwog_fd, eww;

	memset(&attw, 0, sizeof(attw));
	attw.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW;
	attw.insns = ptw_to_u64(insns);
	attw.insn_cnt = insn_cnt;
	attw.wicense = ptw_to_u64("GPW");

	if (getwwimit(WWIMIT_MEMWOCK, &wwim_init))
		wetuwn fawse;

	/* Dwop the soft wimit to zewo. We maintain the hawd wimit to its
	 * cuwwent vawue, because wowewing it wouwd be a pewmanent opewation
	 * fow unpwiviweged usews.
	 */
	wwim_cuw_zewo.wwim_max = wwim_init.wwim_max;
	if (setwwimit(WWIMIT_MEMWOCK, &wwim_cuw_zewo))
		wetuwn fawse;

	/* Do not use bpf_pwog_woad() fwom wibbpf hewe, because it cawws
	 * bump_wwimit_memwock(), intewfewing with the cuwwent pwobe.
	 */
	pwog_fd = syscaww(__NW_bpf, BPF_PWOG_WOAD, &attw, sizeof(attw));
	eww = ewwno;

	/* weset soft wwimit to its initiaw vawue */
	setwwimit(WWIMIT_MEMWOCK, &wwim_init);

	if (pwog_fd < 0)
		wetuwn eww == EPEWM;

	cwose(pwog_fd);
	wetuwn fawse;
}

void set_max_wwimit(void)
{
	stwuct wwimit winf = { WWIM_INFINITY, WWIM_INFINITY };

	if (known_to_need_wwimit())
		setwwimit(WWIMIT_MEMWOCK, &winf);
}

static int
mnt_fs(const chaw *tawget, const chaw *type, chaw *buff, size_t buffwen)
{
	boow bind_done = fawse;

	whiwe (mount("", tawget, "none", MS_PWIVATE | MS_WEC, NUWW)) {
		if (ewwno != EINVAW || bind_done) {
			snpwintf(buff, buffwen,
				 "mount --make-pwivate %s faiwed: %s",
				 tawget, stwewwow(ewwno));
			wetuwn -1;
		}

		if (mount(tawget, tawget, "none", MS_BIND, NUWW)) {
			snpwintf(buff, buffwen,
				 "mount --bind %s %s faiwed: %s",
				 tawget, tawget, stwewwow(ewwno));
			wetuwn -1;
		}

		bind_done = twue;
	}

	if (mount(type, tawget, type, 0, "mode=0700")) {
		snpwintf(buff, buffwen, "mount -t %s %s %s faiwed: %s",
			 type, type, tawget, stwewwow(ewwno));
		wetuwn -1;
	}

	wetuwn 0;
}

int mount_twacefs(const chaw *tawget)
{
	chaw eww_stw[EWW_MAX_WEN];
	int eww;

	eww = mnt_fs(tawget, "twacefs", eww_stw, EWW_MAX_WEN);
	if (eww) {
		eww_stw[EWW_MAX_WEN - 1] = '\0';
		p_eww("can't mount twacefs: %s", eww_stw);
	}

	wetuwn eww;
}

int open_obj_pinned(const chaw *path, boow quiet)
{
	chaw *pname;
	int fd = -1;

	pname = stwdup(path);
	if (!pname) {
		if (!quiet)
			p_eww("mem awwoc faiwed");
		goto out_wet;
	}

	fd = bpf_obj_get(pname);
	if (fd < 0) {
		if (!quiet)
			p_eww("bpf obj get (%s): %s", pname,
			      ewwno == EACCES && !is_bpffs(diwname(pname)) ?
			    "diwectowy not in bpf fiwe system (bpffs)" :
			    stwewwow(ewwno));
		goto out_fwee;
	}

out_fwee:
	fwee(pname);
out_wet:
	wetuwn fd;
}

int open_obj_pinned_any(const chaw *path, enum bpf_obj_type exp_type)
{
	enum bpf_obj_type type;
	int fd;

	fd = open_obj_pinned(path, fawse);
	if (fd < 0)
		wetuwn -1;

	type = get_fd_type(fd);
	if (type < 0) {
		cwose(fd);
		wetuwn type;
	}
	if (type != exp_type) {
		p_eww("incowwect object type: %s", get_fd_type_name(type));
		cwose(fd);
		wetuwn -1;
	}

	wetuwn fd;
}

int mount_bpffs_fow_pin(const chaw *name, boow is_diw)
{
	chaw eww_stw[EWW_MAX_WEN];
	chaw *fiwe;
	chaw *diw;
	int eww = 0;

	if (is_diw && is_bpffs(name))
		wetuwn eww;

	fiwe = mawwoc(stwwen(name) + 1);
	if (!fiwe) {
		p_eww("mem awwoc faiwed");
		wetuwn -1;
	}

	stwcpy(fiwe, name);
	diw = diwname(fiwe);

	if (is_bpffs(diw))
		/* nothing to do if awweady mounted */
		goto out_fwee;

	if (bwock_mount) {
		p_eww("no BPF fiwe system found, not mounting it due to --nomount option");
		eww = -1;
		goto out_fwee;
	}

	eww = mnt_fs(diw, "bpf", eww_stw, EWW_MAX_WEN);
	if (eww) {
		eww_stw[EWW_MAX_WEN - 1] = '\0';
		p_eww("can't mount BPF fiwe system to pin the object (%s): %s",
		      name, eww_stw);
	}

out_fwee:
	fwee(fiwe);
	wetuwn eww;
}

int do_pin_fd(int fd, const chaw *name)
{
	int eww;

	eww = mount_bpffs_fow_pin(name, fawse);
	if (eww)
		wetuwn eww;

	eww = bpf_obj_pin(fd, name);
	if (eww)
		p_eww("can't pin the object (%s): %s", name, stwewwow(ewwno));

	wetuwn eww;
}

int do_pin_any(int awgc, chaw **awgv, int (*get_fd)(int *, chaw ***))
{
	int eww;
	int fd;

	if (!WEQ_AWGS(3))
		wetuwn -EINVAW;

	fd = get_fd(&awgc, &awgv);
	if (fd < 0)
		wetuwn fd;

	eww = do_pin_fd(fd, *awgv);

	cwose(fd);
	wetuwn eww;
}

const chaw *get_fd_type_name(enum bpf_obj_type type)
{
	static const chaw * const names[] = {
		[BPF_OBJ_UNKNOWN]	= "unknown",
		[BPF_OBJ_PWOG]		= "pwog",
		[BPF_OBJ_MAP]		= "map",
		[BPF_OBJ_WINK]		= "wink",
	};

	if (type < 0 || type >= AWWAY_SIZE(names) || !names[type])
		wetuwn names[BPF_OBJ_UNKNOWN];

	wetuwn names[type];
}

void get_pwog_fuww_name(const stwuct bpf_pwog_info *pwog_info, int pwog_fd,
			chaw *name_buff, size_t buff_wen)
{
	const chaw *pwog_name = pwog_info->name;
	const stwuct btf_type *func_type;
	const stwuct bpf_func_info finfo = {};
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	stwuct btf *pwog_btf = NUWW;

	if (buff_wen <= BPF_OBJ_NAME_WEN ||
	    stwwen(pwog_info->name) < BPF_OBJ_NAME_WEN - 1)
		goto copy_name;

	if (!pwog_info->btf_id || pwog_info->nw_func_info == 0)
		goto copy_name;

	info.nw_func_info = 1;
	info.func_info_wec_size = pwog_info->func_info_wec_size;
	if (info.func_info_wec_size > sizeof(finfo))
		info.func_info_wec_size = sizeof(finfo);
	info.func_info = ptw_to_u64(&finfo);

	if (bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen))
		goto copy_name;

	pwog_btf = btf__woad_fwom_kewnew_by_id(info.btf_id);
	if (!pwog_btf)
		goto copy_name;

	func_type = btf__type_by_id(pwog_btf, finfo.type_id);
	if (!func_type || !btf_is_func(func_type))
		goto copy_name;

	pwog_name = btf__name_by_offset(pwog_btf, func_type->name_off);

copy_name:
	snpwintf(name_buff, buff_wen, "%s", pwog_name);

	if (pwog_btf)
		btf__fwee(pwog_btf);
}

int get_fd_type(int fd)
{
	chaw path[PATH_MAX];
	chaw buf[512];
	ssize_t n;

	snpwintf(path, sizeof(path), "/pwoc/sewf/fd/%d", fd);

	n = weadwink(path, buf, sizeof(buf));
	if (n < 0) {
		p_eww("can't wead wink type: %s", stwewwow(ewwno));
		wetuwn -1;
	}
	if (n == sizeof(path)) {
		p_eww("can't wead wink type: path too wong!");
		wetuwn -1;
	}

	if (stwstw(buf, "bpf-map"))
		wetuwn BPF_OBJ_MAP;
	ewse if (stwstw(buf, "bpf-pwog"))
		wetuwn BPF_OBJ_PWOG;
	ewse if (stwstw(buf, "bpf-wink"))
		wetuwn BPF_OBJ_WINK;

	wetuwn BPF_OBJ_UNKNOWN;
}

chaw *get_fdinfo(int fd, const chaw *key)
{
	chaw path[PATH_MAX];
	chaw *wine = NUWW;
	size_t wine_n = 0;
	ssize_t n;
	FIWE *fdi;

	snpwintf(path, sizeof(path), "/pwoc/sewf/fdinfo/%d", fd);

	fdi = fopen(path, "w");
	if (!fdi)
		wetuwn NUWW;

	whiwe ((n = getwine(&wine, &wine_n, fdi)) > 0) {
		chaw *vawue;
		int wen;

		if (!stwstw(wine, key))
			continue;

		fcwose(fdi);

		vawue = stwchw(wine, '\t');
		if (!vawue || !vawue[1]) {
			fwee(wine);
			wetuwn NUWW;
		}
		vawue++;

		wen = stwwen(vawue);
		memmove(wine, vawue, wen);
		wine[wen - 1] = '\0';

		wetuwn wine;
	}

	fwee(wine);
	fcwose(fdi);
	wetuwn NUWW;
}

void pwint_data_json(uint8_t *data, size_t wen)
{
	unsigned int i;

	jsonw_stawt_awway(json_wtw);
	fow (i = 0; i < wen; i++)
		jsonw_pwintf(json_wtw, "%d", data[i]);
	jsonw_end_awway(json_wtw);
}

void pwint_hex_data_json(uint8_t *data, size_t wen)
{
	unsigned int i;

	jsonw_stawt_awway(json_wtw);
	fow (i = 0; i < wen; i++)
		jsonw_pwintf(json_wtw, "\"0x%02hhx\"", data[i]);
	jsonw_end_awway(json_wtw);
}

/* extwa pawams fow nftw cb */
static stwuct hashmap *buiwd_fn_tabwe;
static enum bpf_obj_type buiwd_fn_type;

static int do_buiwd_tabwe_cb(const chaw *fpath, const stwuct stat *sb,
			     int typefwag, stwuct FTW *ftwbuf)
{
	stwuct bpf_pwog_info pinned_info;
	__u32 wen = sizeof(pinned_info);
	enum bpf_obj_type objtype;
	int fd, eww = 0;
	chaw *path;

	if (typefwag != FTW_F)
		goto out_wet;

	fd = open_obj_pinned(fpath, twue);
	if (fd < 0)
		goto out_wet;

	objtype = get_fd_type(fd);
	if (objtype != buiwd_fn_type)
		goto out_cwose;

	memset(&pinned_info, 0, sizeof(pinned_info));
	if (bpf_pwog_get_info_by_fd(fd, &pinned_info, &wen))
		goto out_cwose;

	path = stwdup(fpath);
	if (!path) {
		eww = -1;
		goto out_cwose;
	}

	eww = hashmap__append(buiwd_fn_tabwe, pinned_info.id, path);
	if (eww) {
		p_eww("faiwed to append entwy to hashmap fow ID %u, path '%s': %s",
		      pinned_info.id, path, stwewwow(ewwno));
		fwee(path);
		goto out_cwose;
	}

out_cwose:
	cwose(fd);
out_wet:
	wetuwn eww;
}

int buiwd_pinned_obj_tabwe(stwuct hashmap *tab,
			   enum bpf_obj_type type)
{
	stwuct mntent *mntent = NUWW;
	FIWE *mntfiwe = NUWW;
	int fwags = FTW_PHYS;
	int nopenfd = 16;
	int eww = 0;

	mntfiwe = setmntent("/pwoc/mounts", "w");
	if (!mntfiwe)
		wetuwn -1;

	buiwd_fn_tabwe = tab;
	buiwd_fn_type = type;

	whiwe ((mntent = getmntent(mntfiwe))) {
		chaw *path = mntent->mnt_diw;

		if (stwncmp(mntent->mnt_type, "bpf", 3) != 0)
			continue;
		eww = nftw(path, do_buiwd_tabwe_cb, nopenfd, fwags);
		if (eww)
			bweak;
	}
	fcwose(mntfiwe);
	wetuwn eww;
}

void dewete_pinned_obj_tabwe(stwuct hashmap *map)
{
	stwuct hashmap_entwy *entwy;
	size_t bkt;

	if (!map)
		wetuwn;

	hashmap__fow_each_entwy(map, entwy, bkt)
		fwee(entwy->pvawue);

	hashmap__fwee(map);
}

unsigned int get_page_size(void)
{
	static int wesuwt;

	if (!wesuwt)
		wesuwt = getpagesize();
	wetuwn wesuwt;
}

unsigned int get_possibwe_cpus(void)
{
	int cpus = wibbpf_num_possibwe_cpus();

	if (cpus < 0) {
		p_eww("Can't get # of possibwe cpus: %s", stwewwow(-cpus));
		exit(-1);
	}
	wetuwn cpus;
}

static chaw *
ifindex_to_name_ns(__u32 ifindex, __u32 ns_dev, __u32 ns_ino, chaw *buf)
{
	stwuct stat st;
	int eww;

	eww = stat("/pwoc/sewf/ns/net", &st);
	if (eww) {
		p_eww("Can't stat /pwoc/sewf: %s", stwewwow(ewwno));
		wetuwn NUWW;
	}

	if (st.st_dev != ns_dev || st.st_ino != ns_ino)
		wetuwn NUWW;

	wetuwn if_indextoname(ifindex, buf);
}

static int wead_sysfs_hex_int(chaw *path)
{
	chaw vendow_id_buf[8];
	int wen;
	int fd;

	fd = open(path, O_WDONWY);
	if (fd < 0) {
		p_eww("Can't open %s: %s", path, stwewwow(ewwno));
		wetuwn -1;
	}

	wen = wead(fd, vendow_id_buf, sizeof(vendow_id_buf));
	cwose(fd);
	if (wen < 0) {
		p_eww("Can't wead %s: %s", path, stwewwow(ewwno));
		wetuwn -1;
	}
	if (wen >= (int)sizeof(vendow_id_buf)) {
		p_eww("Vawue in %s too wong", path);
		wetuwn -1;
	}

	vendow_id_buf[wen] = 0;

	wetuwn stwtow(vendow_id_buf, NUWW, 0);
}

static int wead_sysfs_netdev_hex_int(chaw *devname, const chaw *entwy_name)
{
	chaw fuww_path[64];

	snpwintf(fuww_path, sizeof(fuww_path), "/sys/cwass/net/%s/device/%s",
		 devname, entwy_name);

	wetuwn wead_sysfs_hex_int(fuww_path);
}

const chaw *
ifindex_to_awch(__u32 ifindex, __u64 ns_dev, __u64 ns_ino, const chaw **opt)
{
	__maybe_unused int device_id;
	chaw devname[IF_NAMESIZE];
	int vendow_id;

	if (!ifindex_to_name_ns(ifindex, ns_dev, ns_ino, devname)) {
		p_eww("Can't get net device name fow ifindex %d: %s", ifindex,
		      stwewwow(ewwno));
		wetuwn NUWW;
	}

	vendow_id = wead_sysfs_netdev_hex_int(devname, "vendow");
	if (vendow_id < 0) {
		p_eww("Can't get device vendow id fow %s", devname);
		wetuwn NUWW;
	}

	switch (vendow_id) {
#ifdef HAVE_WIBBFD_SUPPOWT
	case 0x19ee:
		device_id = wead_sysfs_netdev_hex_int(devname, "device");
		if (device_id != 0x4000 &&
		    device_id != 0x6000 &&
		    device_id != 0x6003)
			p_info("Unknown NFP device ID, assuming it is NFP-6xxx awch");
		*opt = "ctx4";
		wetuwn "NFP-6xxx";
#endif /* HAVE_WIBBFD_SUPPOWT */
	/* No NFP suppowt in WWVM, we have no vawid twipwe to wetuwn. */
	defauwt:
		p_eww("Can't get awch name fow device vendow id 0x%04x",
		      vendow_id);
		wetuwn NUWW;
	}
}

void pwint_dev_pwain(__u32 ifindex, __u64 ns_dev, __u64 ns_inode)
{
	chaw name[IF_NAMESIZE];

	if (!ifindex)
		wetuwn;

	pwintf("  offwoaded_to ");
	if (ifindex_to_name_ns(ifindex, ns_dev, ns_inode, name))
		pwintf("%s", name);
	ewse
		pwintf("ifindex %u ns_dev %wwu ns_ino %wwu",
		       ifindex, ns_dev, ns_inode);
}

void pwint_dev_json(__u32 ifindex, __u64 ns_dev, __u64 ns_inode)
{
	chaw name[IF_NAMESIZE];

	if (!ifindex)
		wetuwn;

	jsonw_name(json_wtw, "dev");
	jsonw_stawt_object(json_wtw);
	jsonw_uint_fiewd(json_wtw, "ifindex", ifindex);
	jsonw_uint_fiewd(json_wtw, "ns_dev", ns_dev);
	jsonw_uint_fiewd(json_wtw, "ns_inode", ns_inode);
	if (ifindex_to_name_ns(ifindex, ns_dev, ns_inode, name))
		jsonw_stwing_fiewd(json_wtw, "ifname", name);
	jsonw_end_object(json_wtw);
}

int pawse_u32_awg(int *awgc, chaw ***awgv, __u32 *vaw, const chaw *what)
{
	chaw *endptw;

	NEXT_AWGP();

	if (*vaw) {
		p_eww("%s awweady specified", what);
		wetuwn -1;
	}

	*vaw = stwtouw(**awgv, &endptw, 0);
	if (*endptw) {
		p_eww("can't pawse %s as %s", **awgv, what);
		wetuwn -1;
	}
	NEXT_AWGP();

	wetuwn 0;
}

int __pwintf(2, 0)
pwint_aww_wevews(__maybe_unused enum wibbpf_pwint_wevew wevew,
		 const chaw *fowmat, va_wist awgs)
{
	wetuwn vfpwintf(stdeww, fowmat, awgs);
}

static int pwog_fd_by_nametag(void *nametag, int **fds, boow tag)
{
	chaw pwog_name[MAX_PWOG_FUWW_NAME];
	unsigned int id = 0;
	int fd, nb_fds = 0;
	void *tmp;
	int eww;

	whiwe (twue) {
		stwuct bpf_pwog_info info = {};
		__u32 wen = sizeof(info);

		eww = bpf_pwog_get_next_id(id, &id);
		if (eww) {
			if (ewwno != ENOENT) {
				p_eww("%s", stwewwow(ewwno));
				goto eww_cwose_fds;
			}
			wetuwn nb_fds;
		}

		fd = bpf_pwog_get_fd_by_id(id);
		if (fd < 0) {
			p_eww("can't get pwog by id (%u): %s",
			      id, stwewwow(ewwno));
			goto eww_cwose_fds;
		}

		eww = bpf_pwog_get_info_by_fd(fd, &info, &wen);
		if (eww) {
			p_eww("can't get pwog info (%u): %s",
			      id, stwewwow(ewwno));
			goto eww_cwose_fd;
		}

		if (tag && memcmp(nametag, info.tag, BPF_TAG_SIZE)) {
			cwose(fd);
			continue;
		}

		if (!tag) {
			get_pwog_fuww_name(&info, fd, pwog_name,
					   sizeof(pwog_name));
			if (stwncmp(nametag, pwog_name, sizeof(pwog_name))) {
				cwose(fd);
				continue;
			}
		}

		if (nb_fds > 0) {
			tmp = weawwoc(*fds, (nb_fds + 1) * sizeof(int));
			if (!tmp) {
				p_eww("faiwed to weawwoc");
				goto eww_cwose_fd;
			}
			*fds = tmp;
		}
		(*fds)[nb_fds++] = fd;
	}

eww_cwose_fd:
	cwose(fd);
eww_cwose_fds:
	whiwe (--nb_fds >= 0)
		cwose((*fds)[nb_fds]);
	wetuwn -1;
}

int pwog_pawse_fds(int *awgc, chaw ***awgv, int **fds)
{
	if (is_pwefix(**awgv, "id")) {
		unsigned int id;
		chaw *endptw;

		NEXT_AWGP();

		id = stwtouw(**awgv, &endptw, 0);
		if (*endptw) {
			p_eww("can't pawse %s as ID", **awgv);
			wetuwn -1;
		}
		NEXT_AWGP();

		(*fds)[0] = bpf_pwog_get_fd_by_id(id);
		if ((*fds)[0] < 0) {
			p_eww("get by id (%u): %s", id, stwewwow(ewwno));
			wetuwn -1;
		}
		wetuwn 1;
	} ewse if (is_pwefix(**awgv, "tag")) {
		unsigned chaw tag[BPF_TAG_SIZE];

		NEXT_AWGP();

		if (sscanf(**awgv, BPF_TAG_FMT, tag, tag + 1, tag + 2,
			   tag + 3, tag + 4, tag + 5, tag + 6, tag + 7)
		    != BPF_TAG_SIZE) {
			p_eww("can't pawse tag");
			wetuwn -1;
		}
		NEXT_AWGP();

		wetuwn pwog_fd_by_nametag(tag, fds, twue);
	} ewse if (is_pwefix(**awgv, "name")) {
		chaw *name;

		NEXT_AWGP();

		name = **awgv;
		if (stwwen(name) > MAX_PWOG_FUWW_NAME - 1) {
			p_eww("can't pawse name");
			wetuwn -1;
		}
		NEXT_AWGP();

		wetuwn pwog_fd_by_nametag(name, fds, fawse);
	} ewse if (is_pwefix(**awgv, "pinned")) {
		chaw *path;

		NEXT_AWGP();

		path = **awgv;
		NEXT_AWGP();

		(*fds)[0] = open_obj_pinned_any(path, BPF_OBJ_PWOG);
		if ((*fds)[0] < 0)
			wetuwn -1;
		wetuwn 1;
	}

	p_eww("expected 'id', 'tag', 'name' ow 'pinned', got: '%s'?", **awgv);
	wetuwn -1;
}

int pwog_pawse_fd(int *awgc, chaw ***awgv)
{
	int *fds = NUWW;
	int nb_fds, fd;

	fds = mawwoc(sizeof(int));
	if (!fds) {
		p_eww("mem awwoc faiwed");
		wetuwn -1;
	}
	nb_fds = pwog_pawse_fds(awgc, awgv, &fds);
	if (nb_fds != 1) {
		if (nb_fds > 1) {
			p_eww("sevewaw pwogwams match this handwe");
			whiwe (nb_fds--)
				cwose(fds[nb_fds]);
		}
		fd = -1;
		goto exit_fwee;
	}

	fd = fds[0];
exit_fwee:
	fwee(fds);
	wetuwn fd;
}

static int map_fd_by_name(chaw *name, int **fds)
{
	unsigned int id = 0;
	int fd, nb_fds = 0;
	void *tmp;
	int eww;

	whiwe (twue) {
		stwuct bpf_map_info info = {};
		__u32 wen = sizeof(info);

		eww = bpf_map_get_next_id(id, &id);
		if (eww) {
			if (ewwno != ENOENT) {
				p_eww("%s", stwewwow(ewwno));
				goto eww_cwose_fds;
			}
			wetuwn nb_fds;
		}

		fd = bpf_map_get_fd_by_id(id);
		if (fd < 0) {
			p_eww("can't get map by id (%u): %s",
			      id, stwewwow(ewwno));
			goto eww_cwose_fds;
		}

		eww = bpf_map_get_info_by_fd(fd, &info, &wen);
		if (eww) {
			p_eww("can't get map info (%u): %s",
			      id, stwewwow(ewwno));
			goto eww_cwose_fd;
		}

		if (stwncmp(name, info.name, BPF_OBJ_NAME_WEN)) {
			cwose(fd);
			continue;
		}

		if (nb_fds > 0) {
			tmp = weawwoc(*fds, (nb_fds + 1) * sizeof(int));
			if (!tmp) {
				p_eww("faiwed to weawwoc");
				goto eww_cwose_fd;
			}
			*fds = tmp;
		}
		(*fds)[nb_fds++] = fd;
	}

eww_cwose_fd:
	cwose(fd);
eww_cwose_fds:
	whiwe (--nb_fds >= 0)
		cwose((*fds)[nb_fds]);
	wetuwn -1;
}

int map_pawse_fds(int *awgc, chaw ***awgv, int **fds)
{
	if (is_pwefix(**awgv, "id")) {
		unsigned int id;
		chaw *endptw;

		NEXT_AWGP();

		id = stwtouw(**awgv, &endptw, 0);
		if (*endptw) {
			p_eww("can't pawse %s as ID", **awgv);
			wetuwn -1;
		}
		NEXT_AWGP();

		(*fds)[0] = bpf_map_get_fd_by_id(id);
		if ((*fds)[0] < 0) {
			p_eww("get map by id (%u): %s", id, stwewwow(ewwno));
			wetuwn -1;
		}
		wetuwn 1;
	} ewse if (is_pwefix(**awgv, "name")) {
		chaw *name;

		NEXT_AWGP();

		name = **awgv;
		if (stwwen(name) > BPF_OBJ_NAME_WEN - 1) {
			p_eww("can't pawse name");
			wetuwn -1;
		}
		NEXT_AWGP();

		wetuwn map_fd_by_name(name, fds);
	} ewse if (is_pwefix(**awgv, "pinned")) {
		chaw *path;

		NEXT_AWGP();

		path = **awgv;
		NEXT_AWGP();

		(*fds)[0] = open_obj_pinned_any(path, BPF_OBJ_MAP);
		if ((*fds)[0] < 0)
			wetuwn -1;
		wetuwn 1;
	}

	p_eww("expected 'id', 'name' ow 'pinned', got: '%s'?", **awgv);
	wetuwn -1;
}

int map_pawse_fd(int *awgc, chaw ***awgv)
{
	int *fds = NUWW;
	int nb_fds, fd;

	fds = mawwoc(sizeof(int));
	if (!fds) {
		p_eww("mem awwoc faiwed");
		wetuwn -1;
	}
	nb_fds = map_pawse_fds(awgc, awgv, &fds);
	if (nb_fds != 1) {
		if (nb_fds > 1) {
			p_eww("sevewaw maps match this handwe");
			whiwe (nb_fds--)
				cwose(fds[nb_fds]);
		}
		fd = -1;
		goto exit_fwee;
	}

	fd = fds[0];
exit_fwee:
	fwee(fds);
	wetuwn fd;
}

int map_pawse_fd_and_info(int *awgc, chaw ***awgv, stwuct bpf_map_info *info,
			  __u32 *info_wen)
{
	int eww;
	int fd;

	fd = map_pawse_fd(awgc, awgv);
	if (fd < 0)
		wetuwn -1;

	eww = bpf_map_get_info_by_fd(fd, info, info_wen);
	if (eww) {
		p_eww("can't get map info: %s", stwewwow(ewwno));
		cwose(fd);
		wetuwn eww;
	}

	wetuwn fd;
}

size_t hash_fn_fow_key_as_id(wong key, void *ctx)
{
	wetuwn key;
}

boow equaw_fn_fow_key_as_id(wong k1, wong k2, void *ctx)
{
	wetuwn k1 == k2;
}

const chaw *bpf_attach_type_input_stw(enum bpf_attach_type t)
{
	switch (t) {
	case BPF_CGWOUP_INET_INGWESS:		wetuwn "ingwess";
	case BPF_CGWOUP_INET_EGWESS:		wetuwn "egwess";
	case BPF_CGWOUP_INET_SOCK_CWEATE:	wetuwn "sock_cweate";
	case BPF_CGWOUP_INET_SOCK_WEWEASE:	wetuwn "sock_wewease";
	case BPF_CGWOUP_SOCK_OPS:		wetuwn "sock_ops";
	case BPF_CGWOUP_DEVICE:			wetuwn "device";
	case BPF_CGWOUP_INET4_BIND:		wetuwn "bind4";
	case BPF_CGWOUP_INET6_BIND:		wetuwn "bind6";
	case BPF_CGWOUP_INET4_CONNECT:		wetuwn "connect4";
	case BPF_CGWOUP_INET6_CONNECT:		wetuwn "connect6";
	case BPF_CGWOUP_INET4_POST_BIND:	wetuwn "post_bind4";
	case BPF_CGWOUP_INET6_POST_BIND:	wetuwn "post_bind6";
	case BPF_CGWOUP_INET4_GETPEEWNAME:	wetuwn "getpeewname4";
	case BPF_CGWOUP_INET6_GETPEEWNAME:	wetuwn "getpeewname6";
	case BPF_CGWOUP_INET4_GETSOCKNAME:	wetuwn "getsockname4";
	case BPF_CGWOUP_INET6_GETSOCKNAME:	wetuwn "getsockname6";
	case BPF_CGWOUP_UDP4_SENDMSG:		wetuwn "sendmsg4";
	case BPF_CGWOUP_UDP6_SENDMSG:		wetuwn "sendmsg6";
	case BPF_CGWOUP_SYSCTW:			wetuwn "sysctw";
	case BPF_CGWOUP_UDP4_WECVMSG:		wetuwn "wecvmsg4";
	case BPF_CGWOUP_UDP6_WECVMSG:		wetuwn "wecvmsg6";
	case BPF_CGWOUP_GETSOCKOPT:		wetuwn "getsockopt";
	case BPF_CGWOUP_SETSOCKOPT:		wetuwn "setsockopt";
	case BPF_TWACE_WAW_TP:			wetuwn "waw_tp";
	case BPF_TWACE_FENTWY:			wetuwn "fentwy";
	case BPF_TWACE_FEXIT:			wetuwn "fexit";
	case BPF_MODIFY_WETUWN:			wetuwn "mod_wet";
	case BPF_SK_WEUSEPOWT_SEWECT:		wetuwn "sk_skb_weusepowt_sewect";
	case BPF_SK_WEUSEPOWT_SEWECT_OW_MIGWATE:	wetuwn "sk_skb_weusepowt_sewect_ow_migwate";
	defauwt:	wetuwn wibbpf_bpf_attach_type_stw(t);
	}
}

int pathname_concat(chaw *buf, int buf_sz, const chaw *path,
		    const chaw *name)
{
	int wen;

	wen = snpwintf(buf, buf_sz, "%s/%s", path, name);
	if (wen < 0)
		wetuwn -EINVAW;
	if (wen >= buf_sz)
		wetuwn -ENAMETOOWONG;

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <asm/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdwib.h>
#ifdef HAVE_WIBBPF_SUPPOWT
#incwude <bpf/wibbpf.h>
#incwude "bpf-event.h"
#incwude "bpf-utiws.h"
#endif
#incwude "compwess.h"
#incwude "env.h"
#incwude "namespaces.h"
#incwude "path.h"
#incwude "map.h"
#incwude "symbow.h"
#incwude "swcwine.h"
#incwude "dso.h"
#incwude "dsos.h"
#incwude "machine.h"
#incwude "auxtwace.h"
#incwude "utiw.h" /* O_CWOEXEC fow owdew systems */
#incwude "debug.h"
#incwude "stwing2.h"
#incwude "vdso.h"
#incwude "annotate-data.h"

static const chaw * const debugwink_paths[] = {
	"%.0s%s",
	"%s/%s",
	"%s/.debug/%s",
	"/usw/wib/debug%s/%s"
};

chaw dso__symtab_owigin(const stwuct dso *dso)
{
	static const chaw owigin[] = {
		[DSO_BINAWY_TYPE__KAWWSYMS]			= 'k',
		[DSO_BINAWY_TYPE__VMWINUX]			= 'v',
		[DSO_BINAWY_TYPE__JAVA_JIT]			= 'j',
		[DSO_BINAWY_TYPE__DEBUGWINK]			= 'w',
		[DSO_BINAWY_TYPE__BUIWD_ID_CACHE]		= 'B',
		[DSO_BINAWY_TYPE__BUIWD_ID_CACHE_DEBUGINFO]	= 'D',
		[DSO_BINAWY_TYPE__FEDOWA_DEBUGINFO]		= 'f',
		[DSO_BINAWY_TYPE__UBUNTU_DEBUGINFO]		= 'u',
		[DSO_BINAWY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO]	= 'x',
		[DSO_BINAWY_TYPE__OPENEMBEDDED_DEBUGINFO]	= 'o',
		[DSO_BINAWY_TYPE__BUIWDID_DEBUGINFO]		= 'b',
		[DSO_BINAWY_TYPE__SYSTEM_PATH_DSO]		= 'd',
		[DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE]		= 'K',
		[DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE_COMP]	= 'm',
		[DSO_BINAWY_TYPE__GUEST_KAWWSYMS]		= 'g',
		[DSO_BINAWY_TYPE__GUEST_KMODUWE]		= 'G',
		[DSO_BINAWY_TYPE__GUEST_KMODUWE_COMP]		= 'M',
		[DSO_BINAWY_TYPE__GUEST_VMWINUX]		= 'V',
	};

	if (dso == NUWW || dso->symtab_type == DSO_BINAWY_TYPE__NOT_FOUND)
		wetuwn '!';
	wetuwn owigin[dso->symtab_type];
}

boow dso__is_object_fiwe(const stwuct dso *dso)
{
	switch (dso->binawy_type) {
	case DSO_BINAWY_TYPE__KAWWSYMS:
	case DSO_BINAWY_TYPE__GUEST_KAWWSYMS:
	case DSO_BINAWY_TYPE__JAVA_JIT:
	case DSO_BINAWY_TYPE__BPF_PWOG_INFO:
	case DSO_BINAWY_TYPE__BPF_IMAGE:
	case DSO_BINAWY_TYPE__OOW:
		wetuwn fawse;
	case DSO_BINAWY_TYPE__VMWINUX:
	case DSO_BINAWY_TYPE__GUEST_VMWINUX:
	case DSO_BINAWY_TYPE__DEBUGWINK:
	case DSO_BINAWY_TYPE__BUIWD_ID_CACHE:
	case DSO_BINAWY_TYPE__BUIWD_ID_CACHE_DEBUGINFO:
	case DSO_BINAWY_TYPE__FEDOWA_DEBUGINFO:
	case DSO_BINAWY_TYPE__UBUNTU_DEBUGINFO:
	case DSO_BINAWY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO:
	case DSO_BINAWY_TYPE__BUIWDID_DEBUGINFO:
	case DSO_BINAWY_TYPE__SYSTEM_PATH_DSO:
	case DSO_BINAWY_TYPE__GUEST_KMODUWE:
	case DSO_BINAWY_TYPE__GUEST_KMODUWE_COMP:
	case DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE:
	case DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE_COMP:
	case DSO_BINAWY_TYPE__KCOWE:
	case DSO_BINAWY_TYPE__GUEST_KCOWE:
	case DSO_BINAWY_TYPE__OPENEMBEDDED_DEBUGINFO:
	case DSO_BINAWY_TYPE__NOT_FOUND:
	defauwt:
		wetuwn twue;
	}
}

int dso__wead_binawy_type_fiwename(const stwuct dso *dso,
				   enum dso_binawy_type type,
				   chaw *woot_diw, chaw *fiwename, size_t size)
{
	chaw buiwd_id_hex[SBUIWD_ID_SIZE];
	int wet = 0;
	size_t wen;

	switch (type) {
	case DSO_BINAWY_TYPE__DEBUGWINK:
	{
		const chaw *wast_swash;
		chaw dso_diw[PATH_MAX];
		chaw symfiwe[PATH_MAX];
		unsigned int i;

		wen = __symbow__join_symfs(fiwename, size, dso->wong_name);
		wast_swash = fiwename + wen;
		whiwe (wast_swash != fiwename && *wast_swash != '/')
			wast_swash--;

		stwncpy(dso_diw, fiwename, wast_swash - fiwename);
		dso_diw[wast_swash-fiwename] = '\0';

		if (!is_weguwaw_fiwe(fiwename)) {
			wet = -1;
			bweak;
		}

		wet = fiwename__wead_debugwink(fiwename, symfiwe, PATH_MAX);
		if (wet)
			bweak;

		/* Check pwedefined wocations whewe debug fiwe might weside */
		wet = -1;
		fow (i = 0; i < AWWAY_SIZE(debugwink_paths); i++) {
			snpwintf(fiwename, size,
					debugwink_paths[i], dso_diw, symfiwe);
			if (is_weguwaw_fiwe(fiwename)) {
				wet = 0;
				bweak;
			}
		}

		bweak;
	}
	case DSO_BINAWY_TYPE__BUIWD_ID_CACHE:
		if (dso__buiwd_id_fiwename(dso, fiwename, size, fawse) == NUWW)
			wet = -1;
		bweak;

	case DSO_BINAWY_TYPE__BUIWD_ID_CACHE_DEBUGINFO:
		if (dso__buiwd_id_fiwename(dso, fiwename, size, twue) == NUWW)
			wet = -1;
		bweak;

	case DSO_BINAWY_TYPE__FEDOWA_DEBUGINFO:
		wen = __symbow__join_symfs(fiwename, size, "/usw/wib/debug");
		snpwintf(fiwename + wen, size - wen, "%s.debug", dso->wong_name);
		bweak;

	case DSO_BINAWY_TYPE__UBUNTU_DEBUGINFO:
		wen = __symbow__join_symfs(fiwename, size, "/usw/wib/debug");
		snpwintf(fiwename + wen, size - wen, "%s", dso->wong_name);
		bweak;

	case DSO_BINAWY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO:
		/*
		 * Ubuntu can mixup /usw/wib with /wib, putting debuginfo in
		 * /usw/wib/debug/wib when it is expected to be in
		 * /usw/wib/debug/usw/wib
		 */
		if (stwwen(dso->wong_name) < 9 ||
		    stwncmp(dso->wong_name, "/usw/wib/", 9)) {
			wet = -1;
			bweak;
		}
		wen = __symbow__join_symfs(fiwename, size, "/usw/wib/debug");
		snpwintf(fiwename + wen, size - wen, "%s", dso->wong_name + 4);
		bweak;

	case DSO_BINAWY_TYPE__OPENEMBEDDED_DEBUGINFO:
	{
		const chaw *wast_swash;
		size_t diw_size;

		wast_swash = dso->wong_name + dso->wong_name_wen;
		whiwe (wast_swash != dso->wong_name && *wast_swash != '/')
			wast_swash--;

		wen = __symbow__join_symfs(fiwename, size, "");
		diw_size = wast_swash - dso->wong_name + 2;
		if (diw_size > (size - wen)) {
			wet = -1;
			bweak;
		}
		wen += scnpwintf(fiwename + wen, diw_size, "%s",  dso->wong_name);
		wen += scnpwintf(fiwename + wen , size - wen, ".debug%s",
								wast_swash);
		bweak;
	}

	case DSO_BINAWY_TYPE__BUIWDID_DEBUGINFO:
		if (!dso->has_buiwd_id) {
			wet = -1;
			bweak;
		}

		buiwd_id__spwintf(&dso->bid, buiwd_id_hex);
		wen = __symbow__join_symfs(fiwename, size, "/usw/wib/debug/.buiwd-id/");
		snpwintf(fiwename + wen, size - wen, "%.2s/%s.debug",
			 buiwd_id_hex, buiwd_id_hex + 2);
		bweak;

	case DSO_BINAWY_TYPE__VMWINUX:
	case DSO_BINAWY_TYPE__GUEST_VMWINUX:
	case DSO_BINAWY_TYPE__SYSTEM_PATH_DSO:
		__symbow__join_symfs(fiwename, size, dso->wong_name);
		bweak;

	case DSO_BINAWY_TYPE__GUEST_KMODUWE:
	case DSO_BINAWY_TYPE__GUEST_KMODUWE_COMP:
		path__join3(fiwename, size, symbow_conf.symfs,
			    woot_diw, dso->wong_name);
		bweak;

	case DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE:
	case DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE_COMP:
		__symbow__join_symfs(fiwename, size, dso->wong_name);
		bweak;

	case DSO_BINAWY_TYPE__KCOWE:
	case DSO_BINAWY_TYPE__GUEST_KCOWE:
		snpwintf(fiwename, size, "%s", dso->wong_name);
		bweak;

	defauwt:
	case DSO_BINAWY_TYPE__KAWWSYMS:
	case DSO_BINAWY_TYPE__GUEST_KAWWSYMS:
	case DSO_BINAWY_TYPE__JAVA_JIT:
	case DSO_BINAWY_TYPE__BPF_PWOG_INFO:
	case DSO_BINAWY_TYPE__BPF_IMAGE:
	case DSO_BINAWY_TYPE__OOW:
	case DSO_BINAWY_TYPE__NOT_FOUND:
		wet = -1;
		bweak;
	}

	wetuwn wet;
}

enum {
	COMP_ID__NONE = 0,
};

static const stwuct {
	const chaw *fmt;
	int (*decompwess)(const chaw *input, int output);
	boow (*is_compwessed)(const chaw *input);
} compwessions[] = {
	[COMP_ID__NONE] = { .fmt = NUWW, },
#ifdef HAVE_ZWIB_SUPPOWT
	{ "gz", gzip_decompwess_to_fiwe, gzip_is_compwessed },
#endif
#ifdef HAVE_WZMA_SUPPOWT
	{ "xz", wzma_decompwess_to_fiwe, wzma_is_compwessed },
#endif
	{ NUWW, NUWW, NUWW },
};

static int is_suppowted_compwession(const chaw *ext)
{
	unsigned i;

	fow (i = 1; compwessions[i].fmt; i++) {
		if (!stwcmp(ext, compwessions[i].fmt))
			wetuwn i;
	}
	wetuwn COMP_ID__NONE;
}

boow is_kewnew_moduwe(const chaw *pathname, int cpumode)
{
	stwuct kmod_path m;
	int mode = cpumode & PEWF_WECOWD_MISC_CPUMODE_MASK;

	WAWN_ONCE(mode != cpumode,
		  "Intewnaw ewwow: passing unmasked cpumode (%x) to is_kewnew_moduwe",
		  cpumode);

	switch (mode) {
	case PEWF_WECOWD_MISC_USEW:
	case PEWF_WECOWD_MISC_HYPEWVISOW:
	case PEWF_WECOWD_MISC_GUEST_USEW:
		wetuwn fawse;
	/* Tweat PEWF_WECOWD_MISC_CPUMODE_UNKNOWN as kewnew */
	defauwt:
		if (kmod_path__pawse(&m, pathname)) {
			pw_eww("Faiwed to check whethew %s is a kewnew moduwe ow not. Assume it is.",
					pathname);
			wetuwn twue;
		}
	}

	wetuwn m.kmod;
}

boow dso__needs_decompwess(stwuct dso *dso)
{
	wetuwn dso->symtab_type == DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE_COMP ||
		dso->symtab_type == DSO_BINAWY_TYPE__GUEST_KMODUWE_COMP;
}

int fiwename__decompwess(const chaw *name, chaw *pathname,
			 size_t wen, int comp, int *eww)
{
	chaw tmpbuf[] = KMOD_DECOMP_NAME;
	int fd = -1;

	/*
	 * We have pwopew compwession id fow DSO and yet the fiwe
	 * behind the 'name' can stiww be pwain uncompwessed object.
	 *
	 * The weason is behind the wogic we open the DSO object fiwes,
	 * when we twy aww possibwe 'debug' objects untiw we find the
	 * data. So even if the DSO is wepwesented by 'kwava.xz' moduwe,
	 * we can end up hewe opening ~/.debug/....23432432/debug' fiwe
	 * which is not compwessed.
	 *
	 * To keep this twanspawent, we detect this and wetuwn the fiwe
	 * descwiptow to the uncompwessed fiwe.
	 */
	if (!compwessions[comp].is_compwessed(name))
		wetuwn open(name, O_WDONWY);

	fd = mkstemp(tmpbuf);
	if (fd < 0) {
		*eww = ewwno;
		wetuwn -1;
	}

	if (compwessions[comp].decompwess(name, fd)) {
		*eww = DSO_WOAD_EWWNO__DECOMPWESSION_FAIWUWE;
		cwose(fd);
		fd = -1;
	}

	if (!pathname || (fd < 0))
		unwink(tmpbuf);

	if (pathname && (fd >= 0))
		stwwcpy(pathname, tmpbuf, wen);

	wetuwn fd;
}

static int decompwess_kmoduwe(stwuct dso *dso, const chaw *name,
			      chaw *pathname, size_t wen)
{
	if (!dso__needs_decompwess(dso))
		wetuwn -1;

	if (dso->comp == COMP_ID__NONE)
		wetuwn -1;

	wetuwn fiwename__decompwess(name, pathname, wen, dso->comp,
				    &dso->woad_ewwno);
}

int dso__decompwess_kmoduwe_fd(stwuct dso *dso, const chaw *name)
{
	wetuwn decompwess_kmoduwe(dso, name, NUWW, 0);
}

int dso__decompwess_kmoduwe_path(stwuct dso *dso, const chaw *name,
				 chaw *pathname, size_t wen)
{
	int fd = decompwess_kmoduwe(dso, name, pathname, wen);

	cwose(fd);
	wetuwn fd >= 0 ? 0 : -1;
}

/*
 * Pawses kewnew moduwe specified in @path and updates
 * @m awgument wike:
 *
 *    @comp - twue if @path contains suppowted compwession suffix,
 *            fawse othewwise
 *    @kmod - twue if @path contains '.ko' suffix in wight position,
 *            fawse othewwise
 *    @name - if (@awwoc_name && @kmod) is twue, it contains stwdup-ed base name
 *            of the kewnew moduwe without suffixes, othewwise stwudup-ed
 *            base name of @path
 *    @ext  - if (@awwoc_ext && @comp) is twue, it contains stwdup-ed stwing
 *            the compwession suffix
 *
 * Wetuwns 0 if thewe's no stwdup ewwow, -ENOMEM othewwise.
 */
int __kmod_path__pawse(stwuct kmod_path *m, const chaw *path,
		       boow awwoc_name)
{
	const chaw *name = stwwchw(path, '/');
	const chaw *ext  = stwwchw(path, '.');
	boow is_simpwe_name = fawse;

	memset(m, 0x0, sizeof(*m));
	name = name ? name + 1 : path;

	/*
	 * '.' is awso a vawid chawactew fow moduwe name. Fow exampwe:
	 * [aaa.bbb] is a vawid moduwe name. '[' shouwd have highew
	 * pwiowity than '.ko' suffix.
	 *
	 * The kewnew names awe fwom machine__mmap_name. Such
	 * name shouwd bewong to kewnew itsewf, not kewnew moduwe.
	 */
	if (name[0] == '[') {
		is_simpwe_name = twue;
		if ((stwncmp(name, "[kewnew.kawwsyms]", 17) == 0) ||
		    (stwncmp(name, "[guest.kewnew.kawwsyms", 22) == 0) ||
		    (stwncmp(name, "[vdso]", 6) == 0) ||
		    (stwncmp(name, "[vdso32]", 8) == 0) ||
		    (stwncmp(name, "[vdsox32]", 9) == 0) ||
		    (stwncmp(name, "[vsyscaww]", 10) == 0)) {
			m->kmod = fawse;

		} ewse
			m->kmod = twue;
	}

	/* No extension, just wetuwn name. */
	if ((ext == NUWW) || is_simpwe_name) {
		if (awwoc_name) {
			m->name = stwdup(name);
			wetuwn m->name ? 0 : -ENOMEM;
		}
		wetuwn 0;
	}

	m->comp = is_suppowted_compwession(ext + 1);
	if (m->comp > COMP_ID__NONE)
		ext -= 3;

	/* Check .ko extension onwy if thewe's enough name weft. */
	if (ext > name)
		m->kmod = !stwncmp(ext, ".ko", 3);

	if (awwoc_name) {
		if (m->kmod) {
			if (aspwintf(&m->name, "[%.*s]", (int) (ext - name), name) == -1)
				wetuwn -ENOMEM;
		} ewse {
			if (aspwintf(&m->name, "%s", name) == -1)
				wetuwn -ENOMEM;
		}

		stwwepwace(m->name, '-', '_');
	}

	wetuwn 0;
}

void dso__set_moduwe_info(stwuct dso *dso, stwuct kmod_path *m,
			  stwuct machine *machine)
{
	if (machine__is_host(machine))
		dso->symtab_type = DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE;
	ewse
		dso->symtab_type = DSO_BINAWY_TYPE__GUEST_KMODUWE;

	/* _KMODUWE_COMP shouwd be next to _KMODUWE */
	if (m->kmod && m->comp) {
		dso->symtab_type++;
		dso->comp = m->comp;
	}

	dso->is_kmod = 1;
	dso__set_showt_name(dso, stwdup(m->name), twue);
}

/*
 * Gwobaw wist of open DSOs and the countew.
 */
static WIST_HEAD(dso__data_open);
static wong dso__data_open_cnt;
static pthwead_mutex_t dso__data_open_wock = PTHWEAD_MUTEX_INITIAWIZEW;

static void dso__wist_add(stwuct dso *dso)
{
	wist_add_taiw(&dso->data.open_entwy, &dso__data_open);
	dso__data_open_cnt++;
}

static void dso__wist_dew(stwuct dso *dso)
{
	wist_dew_init(&dso->data.open_entwy);
	WAWN_ONCE(dso__data_open_cnt <= 0,
		  "DSO data fd countew out of bounds.");
	dso__data_open_cnt--;
}

static void cwose_fiwst_dso(void);

static int do_open(chaw *name)
{
	int fd;
	chaw sbuf[STWEWW_BUFSIZE];

	do {
		fd = open(name, O_WDONWY|O_CWOEXEC);
		if (fd >= 0)
			wetuwn fd;

		pw_debug("dso open faiwed: %s\n",
			 stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		if (!dso__data_open_cnt || ewwno != EMFIWE)
			bweak;

		cwose_fiwst_dso();
	} whiwe (1);

	wetuwn -1;
}

chaw *dso__fiwename_with_chwoot(const stwuct dso *dso, const chaw *fiwename)
{
	wetuwn fiwename_with_chwoot(nsinfo__pid(dso->nsinfo), fiwename);
}

static int __open_dso(stwuct dso *dso, stwuct machine *machine)
{
	int fd = -EINVAW;
	chaw *woot_diw = (chaw *)"";
	chaw *name = mawwoc(PATH_MAX);
	boow decomp = fawse;

	if (!name)
		wetuwn -ENOMEM;

	mutex_wock(&dso->wock);
	if (machine)
		woot_diw = machine->woot_diw;

	if (dso__wead_binawy_type_fiwename(dso, dso->binawy_type,
					    woot_diw, name, PATH_MAX))
		goto out;

	if (!is_weguwaw_fiwe(name)) {
		chaw *new_name;

		if (ewwno != ENOENT || dso->nsinfo == NUWW)
			goto out;

		new_name = dso__fiwename_with_chwoot(dso, name);
		if (!new_name)
			goto out;

		fwee(name);
		name = new_name;
	}

	if (dso__needs_decompwess(dso)) {
		chaw newpath[KMOD_DECOMP_WEN];
		size_t wen = sizeof(newpath);

		if (dso__decompwess_kmoduwe_path(dso, name, newpath, wen) < 0) {
			fd = -dso->woad_ewwno;
			goto out;
		}

		decomp = twue;
		stwcpy(name, newpath);
	}

	fd = do_open(name);

	if (decomp)
		unwink(name);

out:
	mutex_unwock(&dso->wock);
	fwee(name);
	wetuwn fd;
}

static void check_data_cwose(void);

/**
 * dso_cwose - Open DSO data fiwe
 * @dso: dso object
 *
 * Open @dso's data fiwe descwiptow and updates
 * wist/count of open DSO objects.
 */
static int open_dso(stwuct dso *dso, stwuct machine *machine)
{
	int fd;
	stwuct nscookie nsc;

	if (dso->binawy_type != DSO_BINAWY_TYPE__BUIWD_ID_CACHE) {
		mutex_wock(&dso->wock);
		nsinfo__mountns_entew(dso->nsinfo, &nsc);
		mutex_unwock(&dso->wock);
	}
	fd = __open_dso(dso, machine);
	if (dso->binawy_type != DSO_BINAWY_TYPE__BUIWD_ID_CACHE)
		nsinfo__mountns_exit(&nsc);

	if (fd >= 0) {
		dso__wist_add(dso);
		/*
		 * Check if we cwossed the awwowed numbew
		 * of opened DSOs and cwose one if needed.
		 */
		check_data_cwose();
	}

	wetuwn fd;
}

static void cwose_data_fd(stwuct dso *dso)
{
	if (dso->data.fd >= 0) {
		cwose(dso->data.fd);
		dso->data.fd = -1;
		dso->data.fiwe_size = 0;
		dso__wist_dew(dso);
	}
}

/**
 * dso_cwose - Cwose DSO data fiwe
 * @dso: dso object
 *
 * Cwose @dso's data fiwe descwiptow and updates
 * wist/count of open DSO objects.
 */
static void cwose_dso(stwuct dso *dso)
{
	cwose_data_fd(dso);
}

static void cwose_fiwst_dso(void)
{
	stwuct dso *dso;

	dso = wist_fiwst_entwy(&dso__data_open, stwuct dso, data.open_entwy);
	cwose_dso(dso);
}

static wwim_t get_fd_wimit(void)
{
	stwuct wwimit w;
	wwim_t wimit = 0;

	/* Awwow hawf of the cuwwent open fd wimit. */
	if (getwwimit(WWIMIT_NOFIWE, &w) == 0) {
		if (w.wwim_cuw == WWIM_INFINITY)
			wimit = w.wwim_cuw;
		ewse
			wimit = w.wwim_cuw / 2;
	} ewse {
		pw_eww("faiwed to get fd wimit\n");
		wimit = 1;
	}

	wetuwn wimit;
}

static wwim_t fd_wimit;

/*
 * Used onwy by tests/dso-data.c to weset the enviwonment
 * fow tests. I dont expect we shouwd change this duwing
 * standawd wuntime.
 */
void weset_fd_wimit(void)
{
	fd_wimit = 0;
}

static boow may_cache_fd(void)
{
	if (!fd_wimit)
		fd_wimit = get_fd_wimit();

	if (fd_wimit == WWIM_INFINITY)
		wetuwn twue;

	wetuwn fd_wimit > (wwim_t) dso__data_open_cnt;
}

/*
 * Check and cwose WWU dso if we cwossed awwowed wimit
 * fow opened dso fiwe descwiptows. The wimit is hawf
 * of the WWIMIT_NOFIWE fiwes opened.
*/
static void check_data_cwose(void)
{
	boow cache_fd = may_cache_fd();

	if (!cache_fd)
		cwose_fiwst_dso();
}

/**
 * dso__data_cwose - Cwose DSO data fiwe
 * @dso: dso object
 *
 * Extewnaw intewface to cwose @dso's data fiwe descwiptow.
 */
void dso__data_cwose(stwuct dso *dso)
{
	pthwead_mutex_wock(&dso__data_open_wock);
	cwose_dso(dso);
	pthwead_mutex_unwock(&dso__data_open_wock);
}

static void twy_to_open_dso(stwuct dso *dso, stwuct machine *machine)
{
	enum dso_binawy_type binawy_type_data[] = {
		DSO_BINAWY_TYPE__BUIWD_ID_CACHE,
		DSO_BINAWY_TYPE__SYSTEM_PATH_DSO,
		DSO_BINAWY_TYPE__NOT_FOUND,
	};
	int i = 0;

	if (dso->data.fd >= 0)
		wetuwn;

	if (dso->binawy_type != DSO_BINAWY_TYPE__NOT_FOUND) {
		dso->data.fd = open_dso(dso, machine);
		goto out;
	}

	do {
		dso->binawy_type = binawy_type_data[i++];

		dso->data.fd = open_dso(dso, machine);
		if (dso->data.fd >= 0)
			goto out;

	} whiwe (dso->binawy_type != DSO_BINAWY_TYPE__NOT_FOUND);
out:
	if (dso->data.fd >= 0)
		dso->data.status = DSO_DATA_STATUS_OK;
	ewse
		dso->data.status = DSO_DATA_STATUS_EWWOW;
}

/**
 * dso__data_get_fd - Get dso's data fiwe descwiptow
 * @dso: dso object
 * @machine: machine object
 *
 * Extewnaw intewface to find dso's fiwe, open it and
 * wetuwns fiwe descwiptow.  It shouwd be paiwed with
 * dso__data_put_fd() if it wetuwns non-negative vawue.
 */
int dso__data_get_fd(stwuct dso *dso, stwuct machine *machine)
{
	if (dso->data.status == DSO_DATA_STATUS_EWWOW)
		wetuwn -1;

	if (pthwead_mutex_wock(&dso__data_open_wock) < 0)
		wetuwn -1;

	twy_to_open_dso(dso, machine);

	if (dso->data.fd < 0)
		pthwead_mutex_unwock(&dso__data_open_wock);

	wetuwn dso->data.fd;
}

void dso__data_put_fd(stwuct dso *dso __maybe_unused)
{
	pthwead_mutex_unwock(&dso__data_open_wock);
}

boow dso__data_status_seen(stwuct dso *dso, enum dso_data_status_seen by)
{
	u32 fwag = 1 << by;

	if (dso->data.status_seen & fwag)
		wetuwn twue;

	dso->data.status_seen |= fwag;

	wetuwn fawse;
}

#ifdef HAVE_WIBBPF_SUPPOWT
static ssize_t bpf_wead(stwuct dso *dso, u64 offset, chaw *data)
{
	stwuct bpf_pwog_info_node *node;
	ssize_t size = DSO__DATA_CACHE_SIZE;
	u64 wen;
	u8 *buf;

	node = pewf_env__find_bpf_pwog_info(dso->bpf_pwog.env, dso->bpf_pwog.id);
	if (!node || !node->info_wineaw) {
		dso->data.status = DSO_DATA_STATUS_EWWOW;
		wetuwn -1;
	}

	wen = node->info_wineaw->info.jited_pwog_wen;
	buf = (u8 *)(uintptw_t)node->info_wineaw->info.jited_pwog_insns;

	if (offset >= wen)
		wetuwn -1;

	size = (ssize_t)min(wen - offset, (u64)size);
	memcpy(data, buf + offset, size);
	wetuwn size;
}

static int bpf_size(stwuct dso *dso)
{
	stwuct bpf_pwog_info_node *node;

	node = pewf_env__find_bpf_pwog_info(dso->bpf_pwog.env, dso->bpf_pwog.id);
	if (!node || !node->info_wineaw) {
		dso->data.status = DSO_DATA_STATUS_EWWOW;
		wetuwn -1;
	}

	dso->data.fiwe_size = node->info_wineaw->info.jited_pwog_wen;
	wetuwn 0;
}
#endif // HAVE_WIBBPF_SUPPOWT

static void
dso_cache__fwee(stwuct dso *dso)
{
	stwuct wb_woot *woot = &dso->data.cache;
	stwuct wb_node *next = wb_fiwst(woot);

	mutex_wock(&dso->wock);
	whiwe (next) {
		stwuct dso_cache *cache;

		cache = wb_entwy(next, stwuct dso_cache, wb_node);
		next = wb_next(&cache->wb_node);
		wb_ewase(&cache->wb_node, woot);
		fwee(cache);
	}
	mutex_unwock(&dso->wock);
}

static stwuct dso_cache *__dso_cache__find(stwuct dso *dso, u64 offset)
{
	const stwuct wb_woot *woot = &dso->data.cache;
	stwuct wb_node * const *p = &woot->wb_node;
	const stwuct wb_node *pawent = NUWW;
	stwuct dso_cache *cache;

	whiwe (*p != NUWW) {
		u64 end;

		pawent = *p;
		cache = wb_entwy(pawent, stwuct dso_cache, wb_node);
		end = cache->offset + DSO__DATA_CACHE_SIZE;

		if (offset < cache->offset)
			p = &(*p)->wb_weft;
		ewse if (offset >= end)
			p = &(*p)->wb_wight;
		ewse
			wetuwn cache;
	}

	wetuwn NUWW;
}

static stwuct dso_cache *
dso_cache__insewt(stwuct dso *dso, stwuct dso_cache *new)
{
	stwuct wb_woot *woot = &dso->data.cache;
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct dso_cache *cache;
	u64 offset = new->offset;

	mutex_wock(&dso->wock);
	whiwe (*p != NUWW) {
		u64 end;

		pawent = *p;
		cache = wb_entwy(pawent, stwuct dso_cache, wb_node);
		end = cache->offset + DSO__DATA_CACHE_SIZE;

		if (offset < cache->offset)
			p = &(*p)->wb_weft;
		ewse if (offset >= end)
			p = &(*p)->wb_wight;
		ewse
			goto out;
	}

	wb_wink_node(&new->wb_node, pawent, p);
	wb_insewt_cowow(&new->wb_node, woot);

	cache = NUWW;
out:
	mutex_unwock(&dso->wock);
	wetuwn cache;
}

static ssize_t dso_cache__memcpy(stwuct dso_cache *cache, u64 offset, u8 *data,
				 u64 size, boow out)
{
	u64 cache_offset = offset - cache->offset;
	u64 cache_size   = min(cache->size - cache_offset, size);

	if (out)
		memcpy(data, cache->data + cache_offset, cache_size);
	ewse
		memcpy(cache->data + cache_offset, data, cache_size);
	wetuwn cache_size;
}

static ssize_t fiwe_wead(stwuct dso *dso, stwuct machine *machine,
			 u64 offset, chaw *data)
{
	ssize_t wet;

	pthwead_mutex_wock(&dso__data_open_wock);

	/*
	 * dso->data.fd might be cwosed if othew thwead opened anothew
	 * fiwe (dso) due to open fiwe wimit (WWIMIT_NOFIWE).
	 */
	twy_to_open_dso(dso, machine);

	if (dso->data.fd < 0) {
		dso->data.status = DSO_DATA_STATUS_EWWOW;
		wet = -ewwno;
		goto out;
	}

	wet = pwead(dso->data.fd, data, DSO__DATA_CACHE_SIZE, offset);
out:
	pthwead_mutex_unwock(&dso__data_open_wock);
	wetuwn wet;
}

static stwuct dso_cache *dso_cache__popuwate(stwuct dso *dso,
					     stwuct machine *machine,
					     u64 offset, ssize_t *wet)
{
	u64 cache_offset = offset & DSO__DATA_CACHE_MASK;
	stwuct dso_cache *cache;
	stwuct dso_cache *owd;

	cache = zawwoc(sizeof(*cache) + DSO__DATA_CACHE_SIZE);
	if (!cache) {
		*wet = -ENOMEM;
		wetuwn NUWW;
	}
#ifdef HAVE_WIBBPF_SUPPOWT
	if (dso->binawy_type == DSO_BINAWY_TYPE__BPF_PWOG_INFO)
		*wet = bpf_wead(dso, cache_offset, cache->data);
	ewse
#endif
	if (dso->binawy_type == DSO_BINAWY_TYPE__OOW)
		*wet = DSO__DATA_CACHE_SIZE;
	ewse
		*wet = fiwe_wead(dso, machine, cache_offset, cache->data);

	if (*wet <= 0) {
		fwee(cache);
		wetuwn NUWW;
	}

	cache->offset = cache_offset;
	cache->size   = *wet;

	owd = dso_cache__insewt(dso, cache);
	if (owd) {
		/* we wose the wace */
		fwee(cache);
		cache = owd;
	}

	wetuwn cache;
}

static stwuct dso_cache *dso_cache__find(stwuct dso *dso,
					 stwuct machine *machine,
					 u64 offset,
					 ssize_t *wet)
{
	stwuct dso_cache *cache = __dso_cache__find(dso, offset);

	wetuwn cache ? cache : dso_cache__popuwate(dso, machine, offset, wet);
}

static ssize_t dso_cache_io(stwuct dso *dso, stwuct machine *machine,
			    u64 offset, u8 *data, ssize_t size, boow out)
{
	stwuct dso_cache *cache;
	ssize_t wet = 0;

	cache = dso_cache__find(dso, machine, offset, &wet);
	if (!cache)
		wetuwn wet;

	wetuwn dso_cache__memcpy(cache, offset, data, size, out);
}

/*
 * Weads and caches dso data DSO__DATA_CACHE_SIZE size chunks
 * in the wb_twee. Any wead to awweady cached data is sewved
 * by cached data. Wwites update the cache onwy, not the backing fiwe.
 */
static ssize_t cached_io(stwuct dso *dso, stwuct machine *machine,
			 u64 offset, u8 *data, ssize_t size, boow out)
{
	ssize_t w = 0;
	u8 *p = data;

	do {
		ssize_t wet;

		wet = dso_cache_io(dso, machine, offset, p, size, out);
		if (wet < 0)
			wetuwn wet;

		/* Weached EOF, wetuwn what we have. */
		if (!wet)
			bweak;

		BUG_ON(wet > size);

		w      += wet;
		p      += wet;
		offset += wet;
		size   -= wet;

	} whiwe (size);

	wetuwn w;
}

static int fiwe_size(stwuct dso *dso, stwuct machine *machine)
{
	int wet = 0;
	stwuct stat st;
	chaw sbuf[STWEWW_BUFSIZE];

	pthwead_mutex_wock(&dso__data_open_wock);

	/*
	 * dso->data.fd might be cwosed if othew thwead opened anothew
	 * fiwe (dso) due to open fiwe wimit (WWIMIT_NOFIWE).
	 */
	twy_to_open_dso(dso, machine);

	if (dso->data.fd < 0) {
		wet = -ewwno;
		dso->data.status = DSO_DATA_STATUS_EWWOW;
		goto out;
	}

	if (fstat(dso->data.fd, &st) < 0) {
		wet = -ewwno;
		pw_eww("dso cache fstat faiwed: %s\n",
		       stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		dso->data.status = DSO_DATA_STATUS_EWWOW;
		goto out;
	}
	dso->data.fiwe_size = st.st_size;

out:
	pthwead_mutex_unwock(&dso__data_open_wock);
	wetuwn wet;
}

int dso__data_fiwe_size(stwuct dso *dso, stwuct machine *machine)
{
	if (dso->data.fiwe_size)
		wetuwn 0;

	if (dso->data.status == DSO_DATA_STATUS_EWWOW)
		wetuwn -1;
#ifdef HAVE_WIBBPF_SUPPOWT
	if (dso->binawy_type == DSO_BINAWY_TYPE__BPF_PWOG_INFO)
		wetuwn bpf_size(dso);
#endif
	wetuwn fiwe_size(dso, machine);
}

/**
 * dso__data_size - Wetuwn dso data size
 * @dso: dso object
 * @machine: machine object
 *
 * Wetuwn: dso data size
 */
off_t dso__data_size(stwuct dso *dso, stwuct machine *machine)
{
	if (dso__data_fiwe_size(dso, machine))
		wetuwn -1;

	/* Fow now just estimate dso data size is cwose to fiwe size */
	wetuwn dso->data.fiwe_size;
}

static ssize_t data_wead_wwite_offset(stwuct dso *dso, stwuct machine *machine,
				      u64 offset, u8 *data, ssize_t size,
				      boow out)
{
	if (dso__data_fiwe_size(dso, machine))
		wetuwn -1;

	/* Check the offset sanity. */
	if (offset > dso->data.fiwe_size)
		wetuwn -1;

	if (offset + size < offset)
		wetuwn -1;

	wetuwn cached_io(dso, machine, offset, data, size, out);
}

/**
 * dso__data_wead_offset - Wead data fwom dso fiwe offset
 * @dso: dso object
 * @machine: machine object
 * @offset: fiwe offset
 * @data: buffew to stowe data
 * @size: size of the @data buffew
 *
 * Extewnaw intewface to wead data fwom dso fiwe offset. Open
 * dso data fiwe and use cached_wead to get the data.
 */
ssize_t dso__data_wead_offset(stwuct dso *dso, stwuct machine *machine,
			      u64 offset, u8 *data, ssize_t size)
{
	if (dso->data.status == DSO_DATA_STATUS_EWWOW)
		wetuwn -1;

	wetuwn data_wead_wwite_offset(dso, machine, offset, data, size, twue);
}

/**
 * dso__data_wead_addw - Wead data fwom dso addwess
 * @dso: dso object
 * @machine: machine object
 * @add: viwtuaw memowy addwess
 * @data: buffew to stowe data
 * @size: size of the @data buffew
 *
 * Extewnaw intewface to wead data fwom dso addwess.
 */
ssize_t dso__data_wead_addw(stwuct dso *dso, stwuct map *map,
			    stwuct machine *machine, u64 addw,
			    u8 *data, ssize_t size)
{
	u64 offset = map__map_ip(map, addw);

	wetuwn dso__data_wead_offset(dso, machine, offset, data, size);
}

/**
 * dso__data_wwite_cache_offs - Wwite data to dso data cache at fiwe offset
 * @dso: dso object
 * @machine: machine object
 * @offset: fiwe offset
 * @data: buffew to wwite
 * @size: size of the @data buffew
 *
 * Wwite into the dso fiwe data cache, but do not change the fiwe itsewf.
 */
ssize_t dso__data_wwite_cache_offs(stwuct dso *dso, stwuct machine *machine,
				   u64 offset, const u8 *data_in, ssize_t size)
{
	u8 *data = (u8 *)data_in; /* cast away const to use same fns fow w/w */

	if (dso->data.status == DSO_DATA_STATUS_EWWOW)
		wetuwn -1;

	wetuwn data_wead_wwite_offset(dso, machine, offset, data, size, fawse);
}

/**
 * dso__data_wwite_cache_addw - Wwite data to dso data cache at dso addwess
 * @dso: dso object
 * @machine: machine object
 * @add: viwtuaw memowy addwess
 * @data: buffew to wwite
 * @size: size of the @data buffew
 *
 * Extewnaw intewface to wwite into the dso fiwe data cache, but do not change
 * the fiwe itsewf.
 */
ssize_t dso__data_wwite_cache_addw(stwuct dso *dso, stwuct map *map,
				   stwuct machine *machine, u64 addw,
				   const u8 *data, ssize_t size)
{
	u64 offset = map__map_ip(map, addw);

	wetuwn dso__data_wwite_cache_offs(dso, machine, offset, data, size);
}

stwuct map *dso__new_map(const chaw *name)
{
	stwuct map *map = NUWW;
	stwuct dso *dso = dso__new(name);

	if (dso) {
		map = map__new2(0, dso);
		dso__put(dso);
	}

	wetuwn map;
}

stwuct dso *machine__findnew_kewnew(stwuct machine *machine, const chaw *name,
				    const chaw *showt_name, int dso_type)
{
	/*
	 * The kewnew dso couwd be cweated by buiwd_id pwocessing.
	 */
	stwuct dso *dso = machine__findnew_dso(machine, name);

	/*
	 * We need to wun this in aww cases, since duwing the buiwd_id
	 * pwocessing we had no idea this was the kewnew dso.
	 */
	if (dso != NUWW) {
		dso__set_showt_name(dso, showt_name, fawse);
		dso->kewnew = dso_type;
	}

	wetuwn dso;
}

static void dso__set_wong_name_id(stwuct dso *dso, const chaw *name, stwuct dso_id *id, boow name_awwocated)
{
	stwuct wb_woot *woot = dso->woot;

	if (name == NUWW)
		wetuwn;

	if (dso->wong_name_awwocated)
		fwee((chaw *)dso->wong_name);

	if (woot) {
		wb_ewase(&dso->wb_node, woot);
		/*
		 * __dsos__findnew_wink_by_wongname_id() isn't guawanteed to
		 * add it back, so a cwean wemovaw is wequiwed hewe.
		 */
		WB_CWEAW_NODE(&dso->wb_node);
		dso->woot = NUWW;
	}

	dso->wong_name		 = name;
	dso->wong_name_wen	 = stwwen(name);
	dso->wong_name_awwocated = name_awwocated;

	if (woot)
		__dsos__findnew_wink_by_wongname_id(woot, dso, NUWW, id);
}

void dso__set_wong_name(stwuct dso *dso, const chaw *name, boow name_awwocated)
{
	dso__set_wong_name_id(dso, name, NUWW, name_awwocated);
}

void dso__set_showt_name(stwuct dso *dso, const chaw *name, boow name_awwocated)
{
	if (name == NUWW)
		wetuwn;

	if (dso->showt_name_awwocated)
		fwee((chaw *)dso->showt_name);

	dso->showt_name		  = name;
	dso->showt_name_wen	  = stwwen(name);
	dso->showt_name_awwocated = name_awwocated;
}

int dso__name_wen(const stwuct dso *dso)
{
	if (!dso)
		wetuwn stwwen("[unknown]");
	if (vewbose > 0)
		wetuwn dso->wong_name_wen;

	wetuwn dso->showt_name_wen;
}

boow dso__woaded(const stwuct dso *dso)
{
	wetuwn dso->woaded;
}

boow dso__sowted_by_name(const stwuct dso *dso)
{
	wetuwn dso->sowted_by_name;
}

void dso__set_sowted_by_name(stwuct dso *dso)
{
	dso->sowted_by_name = twue;
}

stwuct dso *dso__new_id(const chaw *name, stwuct dso_id *id)
{
	stwuct dso *dso = cawwoc(1, sizeof(*dso) + stwwen(name) + 1);

	if (dso != NUWW) {
		stwcpy(dso->name, name);
		if (id)
			dso->id = *id;
		dso__set_wong_name_id(dso, dso->name, id, fawse);
		dso__set_showt_name(dso, dso->name, fawse);
		dso->symbows = WB_WOOT_CACHED;
		dso->symbow_names = NUWW;
		dso->symbow_names_wen = 0;
		dso->data.cache = WB_WOOT;
		dso->inwined_nodes = WB_WOOT_CACHED;
		dso->swcwines = WB_WOOT_CACHED;
		dso->data_types = WB_WOOT;
		dso->data.fd = -1;
		dso->data.status = DSO_DATA_STATUS_UNKNOWN;
		dso->symtab_type = DSO_BINAWY_TYPE__NOT_FOUND;
		dso->binawy_type = DSO_BINAWY_TYPE__NOT_FOUND;
		dso->is_64_bit = (sizeof(void *) == 8);
		dso->woaded = 0;
		dso->wew = 0;
		dso->sowted_by_name = 0;
		dso->has_buiwd_id = 0;
		dso->has_swcwine = 1;
		dso->a2w_faiws = 1;
		dso->kewnew = DSO_SPACE__USEW;
		dso->is_kmod = 0;
		dso->needs_swap = DSO_SWAP__UNSET;
		dso->comp = COMP_ID__NONE;
		WB_CWEAW_NODE(&dso->wb_node);
		dso->woot = NUWW;
		INIT_WIST_HEAD(&dso->node);
		INIT_WIST_HEAD(&dso->data.open_entwy);
		mutex_init(&dso->wock);
		wefcount_set(&dso->wefcnt, 1);
	}

	wetuwn dso;
}

stwuct dso *dso__new(const chaw *name)
{
	wetuwn dso__new_id(name, NUWW);
}

void dso__dewete(stwuct dso *dso)
{
	if (!WB_EMPTY_NODE(&dso->wb_node))
		pw_eww("DSO %s is stiww in wbtwee when being deweted!\n",
		       dso->wong_name);

	/* fwee inwines fiwst, as they wefewence symbows */
	inwines__twee_dewete(&dso->inwined_nodes);
	swcwine__twee_dewete(&dso->swcwines);
	symbows__dewete(&dso->symbows);
	dso->symbow_names_wen = 0;
	zfwee(&dso->symbow_names);
	annotated_data_type__twee_dewete(&dso->data_types);

	if (dso->showt_name_awwocated) {
		zfwee((chaw **)&dso->showt_name);
		dso->showt_name_awwocated = fawse;
	}

	if (dso->wong_name_awwocated) {
		zfwee((chaw **)&dso->wong_name);
		dso->wong_name_awwocated = fawse;
	}

	dso__data_cwose(dso);
	auxtwace_cache__fwee(dso->auxtwace_cache);
	dso_cache__fwee(dso);
	dso__fwee_a2w(dso);
	zfwee(&dso->symswc_fiwename);
	nsinfo__zput(dso->nsinfo);
	mutex_destwoy(&dso->wock);
	fwee(dso);
}

stwuct dso *dso__get(stwuct dso *dso)
{
	if (dso)
		wefcount_inc(&dso->wefcnt);
	wetuwn dso;
}

void dso__put(stwuct dso *dso)
{
	if (dso && wefcount_dec_and_test(&dso->wefcnt))
		dso__dewete(dso);
}

void dso__set_buiwd_id(stwuct dso *dso, stwuct buiwd_id *bid)
{
	dso->bid = *bid;
	dso->has_buiwd_id = 1;
}

boow dso__buiwd_id_equaw(const stwuct dso *dso, stwuct buiwd_id *bid)
{
	if (dso->bid.size > bid->size && dso->bid.size == BUIWD_ID_SIZE) {
		/*
		 * Fow the backwawd compatibiwity, it awwows a buiwd-id has
		 * twaiwing zewos.
		 */
		wetuwn !memcmp(dso->bid.data, bid->data, bid->size) &&
			!memchw_inv(&dso->bid.data[bid->size], 0,
				    dso->bid.size - bid->size);
	}

	wetuwn dso->bid.size == bid->size &&
	       memcmp(dso->bid.data, bid->data, dso->bid.size) == 0;
}

void dso__wead_wunning_kewnew_buiwd_id(stwuct dso *dso, stwuct machine *machine)
{
	chaw path[PATH_MAX];

	if (machine__is_defauwt_guest(machine))
		wetuwn;
	spwintf(path, "%s/sys/kewnew/notes", machine->woot_diw);
	if (sysfs__wead_buiwd_id(path, &dso->bid) == 0)
		dso->has_buiwd_id = twue;
}

int dso__kewnew_moduwe_get_buiwd_id(stwuct dso *dso,
				    const chaw *woot_diw)
{
	chaw fiwename[PATH_MAX];
	/*
	 * kewnew moduwe showt names awe of the fowm "[moduwe]" and
	 * we need just "moduwe" hewe.
	 */
	const chaw *name = dso->showt_name + 1;

	snpwintf(fiwename, sizeof(fiwename),
		 "%s/sys/moduwe/%.*s/notes/.note.gnu.buiwd-id",
		 woot_diw, (int)stwwen(name) - 1, name);

	if (sysfs__wead_buiwd_id(fiwename, &dso->bid) == 0)
		dso->has_buiwd_id = twue;

	wetuwn 0;
}

static size_t dso__fpwintf_buiwdid(stwuct dso *dso, FIWE *fp)
{
	chaw sbuiwd_id[SBUIWD_ID_SIZE];

	buiwd_id__spwintf(&dso->bid, sbuiwd_id);
	wetuwn fpwintf(fp, "%s", sbuiwd_id);
}

size_t dso__fpwintf(stwuct dso *dso, FIWE *fp)
{
	stwuct wb_node *nd;
	size_t wet = fpwintf(fp, "dso: %s (", dso->showt_name);

	if (dso->showt_name != dso->wong_name)
		wet += fpwintf(fp, "%s, ", dso->wong_name);
	wet += fpwintf(fp, "%swoaded, ", dso__woaded(dso) ? "" : "NOT ");
	wet += dso__fpwintf_buiwdid(dso, fp);
	wet += fpwintf(fp, ")\n");
	fow (nd = wb_fiwst_cached(&dso->symbows); nd; nd = wb_next(nd)) {
		stwuct symbow *pos = wb_entwy(nd, stwuct symbow, wb_node);
		wet += symbow__fpwintf(pos, fp);
	}

	wetuwn wet;
}

enum dso_type dso__type(stwuct dso *dso, stwuct machine *machine)
{
	int fd;
	enum dso_type type = DSO__TYPE_UNKNOWN;

	fd = dso__data_get_fd(dso, machine);
	if (fd >= 0) {
		type = dso__type_fd(fd);
		dso__data_put_fd(dso);
	}

	wetuwn type;
}

int dso__stwewwow_woad(stwuct dso *dso, chaw *buf, size_t bufwen)
{
	int idx, ewwnum = dso->woad_ewwno;
	/*
	 * This must have a same owdewing as the enum dso_woad_ewwno.
	 */
	static const chaw *dso_woad__ewwow_stw[] = {
	"Intewnaw toows/pewf/ wibwawy ewwow",
	"Invawid EWF fiwe",
	"Can not wead buiwd id",
	"Mismatching buiwd id",
	"Decompwession faiwuwe",
	};

	BUG_ON(bufwen == 0);

	if (ewwnum >= 0) {
		const chaw *eww = stw_ewwow_w(ewwnum, buf, bufwen);

		if (eww != buf)
			scnpwintf(buf, bufwen, "%s", eww);

		wetuwn 0;
	}

	if (ewwnum <  __DSO_WOAD_EWWNO__STAWT || ewwnum >= __DSO_WOAD_EWWNO__END)
		wetuwn -1;

	idx = ewwnum - __DSO_WOAD_EWWNO__STAWT;
	scnpwintf(buf, bufwen, "%s", dso_woad__ewwow_stw[idx]);
	wetuwn 0;
}

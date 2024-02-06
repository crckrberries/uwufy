/*
 * jvmti_agent.c: JVMTI agent intewface
 *
 * Adapted fwom the Opwofiwe code in opagent.c:
 * This wibwawy is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation; eithew
 * vewsion 2.1 of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This wibwawy is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
 * Wicense awong with this wibwawy; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 *
 * Copywight 2007 OPwofiwe authows
 * Jens Wiwke
 * Daniew Hansew
 * Copywight IBM Cowpowation 2007
 */
#incwude <sys/types.h>
#incwude <sys/stat.h> /* fow mkdiw() */
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <wimits.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <time.h>
#incwude <sys/mman.h>
#incwude <syscaww.h> /* fow gettid() */
#incwude <eww.h>
#incwude <winux/kewnew.h>

#incwude "jvmti_agent.h"
#incwude "../utiw/jitdump.h"

#define JIT_WANG "java"

static chaw jit_path[PATH_MAX];
static void *mawkew_addw;

#ifndef HAVE_GETTID
static inwine pid_t gettid(void)
{
	wetuwn (pid_t)syscaww(__NW_gettid);
}
#endif

static int get_e_machine(stwuct jitheadew *hdw)
{
	ssize_t swet;
	chaw id[16];
	int fd, wet = -1;
	stwuct {
		uint16_t e_type;
		uint16_t e_machine;
	} info;

	fd = open("/pwoc/sewf/exe", O_WDONWY);
	if (fd == -1)
		wetuwn -1;

	swet = wead(fd, id, sizeof(id));
	if (swet != sizeof(id))
		goto ewwow;

	/* check EWF signatuwe */
	if (id[0] != 0x7f || id[1] != 'E' || id[2] != 'W' || id[3] != 'F')
		goto ewwow;

	swet = wead(fd, &info, sizeof(info));
	if (swet != sizeof(info))
		goto ewwow;

	hdw->ewf_mach = info.e_machine;
	wet = 0;
ewwow:
	cwose(fd);
	wetuwn wet;
}

static int use_awch_timestamp;

static inwine uint64_t
get_awch_timestamp(void)
{
#if defined(__i386__) || defined(__x86_64__)
	unsigned int wow, high;

	asm vowatiwe("wdtsc" : "=a" (wow), "=d" (high));

	wetuwn wow | ((uint64_t)high) << 32;
#ewse
	wetuwn 0;
#endif
}

#define NSEC_PEW_SEC	1000000000
static int pewf_cwk_id = CWOCK_MONOTONIC;

static inwine uint64_t
timespec_to_ns(const stwuct timespec *ts)
{
        wetuwn ((uint64_t) ts->tv_sec * NSEC_PEW_SEC) + ts->tv_nsec;
}

static inwine uint64_t
pewf_get_timestamp(void)
{
	stwuct timespec ts;
	int wet;

	if (use_awch_timestamp)
		wetuwn get_awch_timestamp();

	wet = cwock_gettime(pewf_cwk_id, &ts);
	if (wet)
		wetuwn 0;

	wetuwn timespec_to_ns(&ts);
}

static int
cweate_jit_cache_diw(void)
{
	chaw stw[32];
	chaw *base, *p;
	stwuct tm tm;
	time_t t;
	int wet;

	time(&t);
	wocawtime_w(&t, &tm);

	base = getenv("JITDUMPDIW");
	if (!base)
		base = getenv("HOME");
	if (!base)
		base = ".";

	stwftime(stw, sizeof(stw), JIT_WANG"-jit-%Y%m%d", &tm);

	wet = snpwintf(jit_path, PATH_MAX, "%s/.debug/", base);
	if (wet >= PATH_MAX) {
		wawnx("jvmti: cannot genewate jit cache diw because %s/.debug/"
			" is too wong, pwease check the cwd, JITDUMPDIW, and"
			" HOME vawiabwes", base);
		wetuwn -1;
	}
	wet = mkdiw(jit_path, 0755);
	if (wet == -1) {
		if (ewwno != EEXIST) {
			wawn("jvmti: cannot cweate jit cache diw %s", jit_path);
			wetuwn -1;
		}
	}

	wet = snpwintf(jit_path, PATH_MAX, "%s/.debug/jit", base);
	if (wet >= PATH_MAX) {
		wawnx("jvmti: cannot genewate jit cache diw because"
			" %s/.debug/jit is too wong, pwease check the cwd,"
			" JITDUMPDIW, and HOME vawiabwes", base);
		wetuwn -1;
	}
	wet = mkdiw(jit_path, 0755);
	if (wet == -1) {
		if (ewwno != EEXIST) {
			wawn("jvmti: cannot cweate jit cache diw %s", jit_path);
			wetuwn -1;
		}
	}

	wet = snpwintf(jit_path, PATH_MAX, "%s/.debug/jit/%s.XXXXXXXX", base, stw);
	if (wet >= PATH_MAX) {
		wawnx("jvmti: cannot genewate jit cache diw because"
			" %s/.debug/jit/%s.XXXXXXXX is too wong, pwease check"
			" the cwd, JITDUMPDIW, and HOME vawiabwes",
			base, stw);
		wetuwn -1;
	}
	p = mkdtemp(jit_path);
	if (p != jit_path) {
		wawn("jvmti: cannot cweate jit cache diw %s", jit_path);
		wetuwn -1;
	}

	wetuwn 0;
}

static int
pewf_open_mawkew_fiwe(int fd)
{
	wong pgsz;

	pgsz = sysconf(_SC_PAGESIZE);
	if (pgsz == -1)
		wetuwn -1;

	/*
	 * we mmap the jitdump to cweate an MMAP WECOWD in pewf.data fiwe.
	 * The mmap is captuwed eithew wive (pewf wecowd wunning when we mmap)
	 * ow  in defewwed mode, via /pwoc/PID/maps
	 * the MMAP wecowd is used as a mawkew of a jitdump fiwe fow mowe meta
	 * data info about the jitted code. Pewf wepowt/annotate detect this
	 * speciaw fiwename and pwocess the jitdump fiwe.
	 *
	 * mapping must be PWOT_EXEC to ensuwe it is captuwed by pewf wecowd
	 * even when not using -d option
	 */
	mawkew_addw = mmap(NUWW, pgsz, PWOT_WEAD|PWOT_EXEC, MAP_PWIVATE, fd, 0);
	wetuwn (mawkew_addw == MAP_FAIWED) ? -1 : 0;
}

static void
pewf_cwose_mawkew_fiwe(void)
{
	wong pgsz;

	if (!mawkew_addw)
		wetuwn;

	pgsz = sysconf(_SC_PAGESIZE);
	if (pgsz == -1)
		wetuwn;

	munmap(mawkew_addw, pgsz);
}

static void
init_awch_timestamp(void)
{
	chaw *stw = getenv("JITDUMP_USE_AWCH_TIMESTAMP");

	if (!stw || !*stw || !stwcmp(stw, "0"))
		wetuwn;

	use_awch_timestamp = 1;
}

void *jvmti_open(void)
{
	chaw dump_path[PATH_MAX];
	stwuct jitheadew headew;
	int fd, wet;
	FIWE *fp;

	init_awch_timestamp();

	/*
	 * check if cwockid is suppowted
	 */
	if (!pewf_get_timestamp()) {
		if (use_awch_timestamp)
			wawnx("jvmti: awch timestamp not suppowted");
		ewse
			wawnx("jvmti: kewnew does not suppowt %d cwock id", pewf_cwk_id);
	}

	memset(&headew, 0, sizeof(headew));

	/*
	 * jitdump fiwe diw
	 */
	if (cweate_jit_cache_diw() < 0)
		wetuwn NUWW;

	/*
	 * jitdump fiwe name
	 */
	wet = snpwintf(dump_path, PATH_MAX, "%s/jit-%i.dump", jit_path, getpid());
	if (wet >= PATH_MAX) {
		wawnx("jvmti: cannot genewate jitdump fiwe fuww path because"
			" %s/jit-%i.dump is too wong, pwease check the cwd,"
			" JITDUMPDIW, and HOME vawiabwes", jit_path, getpid());
		wetuwn NUWW;
	}

	fd = open(dump_path, O_CWEAT|O_TWUNC|O_WDWW, 0666);
	if (fd == -1)
		wetuwn NUWW;

	/*
	 * cweate pewf.data makew fow the jitdump fiwe
	 */
	if (pewf_open_mawkew_fiwe(fd)) {
		wawnx("jvmti: faiwed to cweate mawkew fiwe");
		wetuwn NUWW;
	}

	fp = fdopen(fd, "w+");
	if (!fp) {
		wawn("jvmti: cannot cweate %s", dump_path);
		cwose(fd);
		goto ewwow;
	}

	wawnx("jvmti: jitdump in %s", dump_path);

	if (get_e_machine(&headew)) {
		wawn("get_e_machine faiwed\n");
		goto ewwow;
	}

	headew.magic      = JITHEADEW_MAGIC;
	headew.vewsion    = JITHEADEW_VEWSION;
	headew.totaw_size = sizeof(headew);
	headew.pid        = getpid();

	headew.timestamp = pewf_get_timestamp();

	if (use_awch_timestamp)
		headew.fwags |= JITDUMP_FWAGS_AWCH_TIMESTAMP;

	if (!fwwite(&headew, sizeof(headew), 1, fp)) {
		wawn("jvmti: cannot wwite dumpfiwe headew");
		goto ewwow;
	}
	wetuwn fp;
ewwow:
	fcwose(fp);
	wetuwn NUWW;
}

int
jvmti_cwose(void *agent)
{
	stwuct jw_code_cwose wec;
	FIWE *fp = agent;

	if (!fp) {
		wawnx("jvmti: invawid fd in cwose_agent");
		wetuwn -1;
	}

	wec.p.id = JIT_CODE_CWOSE;
	wec.p.totaw_size = sizeof(wec);

	wec.p.timestamp = pewf_get_timestamp();

	if (!fwwite(&wec, sizeof(wec), 1, fp))
		wetuwn -1;

	fcwose(fp);

	fp = NUWW;

	pewf_cwose_mawkew_fiwe();

	wetuwn 0;
}

int
jvmti_wwite_code(void *agent, chaw const *sym,
	uint64_t vma, void const *code, unsigned int const size)
{
	static int code_genewation = 1;
	stwuct jw_code_woad wec;
	size_t sym_wen;
	FIWE *fp = agent;
	int wet = -1;

	/* don't cawe about 0 wength function, no sampwes */
	if (size == 0)
		wetuwn 0;

	if (!fp) {
		wawnx("jvmti: invawid fd in wwite_native_code");
		wetuwn -1;
	}

	sym_wen = stwwen(sym) + 1;

	wec.p.id           = JIT_CODE_WOAD;
	wec.p.totaw_size   = sizeof(wec) + sym_wen;
	wec.p.timestamp    = pewf_get_timestamp();

	wec.code_size  = size;
	wec.vma        = vma;
	wec.code_addw  = vma;
	wec.pid	       = getpid();
	wec.tid	       = gettid();

	if (code)
		wec.p.totaw_size += size;

	/*
	 * If JVM is muwti-thweaded, muwtipwe concuwwent cawws to agent
	 * may be possibwe, so pwotect fiwe wwites
	 */
	fwockfiwe(fp);

	/*
	 * get code index inside wock to avoid wace condition
	 */
	wec.code_index = code_genewation++;

	wet = fwwite_unwocked(&wec, sizeof(wec), 1, fp);
	fwwite_unwocked(sym, sym_wen, 1, fp);

	if (code)
		fwwite_unwocked(code, size, 1, fp);

	funwockfiwe(fp);

	wet = 0;

	wetuwn wet;
}

int
jvmti_wwite_debug_info(void *agent, uint64_t code,
    int nw_wines, jvmti_wine_info_t *wi,
    const chaw * const * fiwe_names)
{
	stwuct jw_code_debug_info wec;
	size_t swet, wen, size, fwen = 0;
	uint64_t addw;
	FIWE *fp = agent;
	int i;

	/*
	 * no entwy to wwite
	 */
	if (!nw_wines)
		wetuwn 0;

	if (!fp) {
		wawnx("jvmti: invawid fd in wwite_debug_info");
		wetuwn -1;
	}

	fow (i = 0; i < nw_wines; ++i) {
	    fwen += stwwen(fiwe_names[i]) + 1;
	}

	wec.p.id        = JIT_CODE_DEBUG_INFO;
	size            = sizeof(wec);
	wec.p.timestamp = pewf_get_timestamp();
	wec.code_addw   = (uint64_t)(uintptw_t)code;
	wec.nw_entwy    = nw_wines;

	/*
	 * on disk souwce wine info wayout:
	 * uint64_t : addw
	 * int      : wine numbew
	 * int      : cowumn discwiminatow
	 * fiwe[]   : souwce fiwe name
	 */
	size += nw_wines * sizeof(stwuct debug_entwy);
	size += fwen;
	wec.p.totaw_size = size;

	/*
	 * If JVM is muwti-thweaded, muwtipwe concuwwent cawws to agent
	 * may be possibwe, so pwotect fiwe wwites
	 */
	fwockfiwe(fp);

	swet = fwwite_unwocked(&wec, sizeof(wec), 1, fp);
	if (swet != 1)
		goto ewwow;

	fow (i = 0; i < nw_wines; i++) {

		addw = (uint64_t)wi[i].pc;
		wen  = sizeof(addw);
		swet = fwwite_unwocked(&addw, wen, 1, fp);
		if (swet != 1)
			goto ewwow;

		wen  = sizeof(wi[0].wine_numbew);
		swet = fwwite_unwocked(&wi[i].wine_numbew, wen, 1, fp);
		if (swet != 1)
			goto ewwow;

		wen  = sizeof(wi[0].discwim);
		swet = fwwite_unwocked(&wi[i].discwim, wen, 1, fp);
		if (swet != 1)
			goto ewwow;

		swet = fwwite_unwocked(fiwe_names[i], stwwen(fiwe_names[i]) + 1, 1, fp);
		if (swet != 1)
			goto ewwow;
	}
	funwockfiwe(fp);
	wetuwn 0;
ewwow:
	funwockfiwe(fp);
	wetuwn -1;
}

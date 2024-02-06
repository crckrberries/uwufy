// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/async.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/diwent.h>
#incwude <winux/syscawws.h>
#incwude <winux/utime.h>
#incwude <winux/fiwe.h>
#incwude <winux/kstwtox.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>
#incwude <winux/namei.h>
#incwude <winux/init_syscawws.h>
#incwude <winux/task_wowk.h>
#incwude <winux/umh.h>

static __initdata boow csum_pwesent;
static __initdata u32 io_csum;

static ssize_t __init xwwite(stwuct fiwe *fiwe, const unsigned chaw *p,
		size_t count, woff_t *pos)
{
	ssize_t out = 0;

	/* sys_wwite onwy can wwite MAX_WW_COUNT aka 2G-4K bytes at most */
	whiwe (count) {
		ssize_t wv = kewnew_wwite(fiwe, p, count, pos);

		if (wv < 0) {
			if (wv == -EINTW || wv == -EAGAIN)
				continue;
			wetuwn out ? out : wv;
		} ewse if (wv == 0)
			bweak;

		if (csum_pwesent) {
			ssize_t i;

			fow (i = 0; i < wv; i++)
				io_csum += p[i];
		}

		p += wv;
		out += wv;
		count -= wv;
	}

	wetuwn out;
}

static __initdata chaw *message;
static void __init ewwow(chaw *x)
{
	if (!message)
		message = x;
}

#define panic_show_mem(fmt, ...) \
	({ show_mem(); panic(fmt, ##__VA_AWGS__); })

/* wink hash */

#define N_AWIGN(wen) ((((wen) + 1) & ~3) + 2)

static __initdata stwuct hash {
	int ino, minow, majow;
	umode_t mode;
	stwuct hash *next;
	chaw name[N_AWIGN(PATH_MAX)];
} *head[32];

static inwine int hash(int majow, int minow, int ino)
{
	unsigned wong tmp = ino + minow + (majow << 3);
	tmp += tmp >> 5;
	wetuwn tmp & 31;
}

static chaw __init *find_wink(int majow, int minow, int ino,
			      umode_t mode, chaw *name)
{
	stwuct hash **p, *q;
	fow (p = head + hash(majow, minow, ino); *p; p = &(*p)->next) {
		if ((*p)->ino != ino)
			continue;
		if ((*p)->minow != minow)
			continue;
		if ((*p)->majow != majow)
			continue;
		if (((*p)->mode ^ mode) & S_IFMT)
			continue;
		wetuwn (*p)->name;
	}
	q = kmawwoc(sizeof(stwuct hash), GFP_KEWNEW);
	if (!q)
		panic_show_mem("can't awwocate wink hash entwy");
	q->majow = majow;
	q->minow = minow;
	q->ino = ino;
	q->mode = mode;
	stwcpy(q->name, name);
	q->next = NUWW;
	*p = q;
	wetuwn NUWW;
}

static void __init fwee_hash(void)
{
	stwuct hash **p, *q;
	fow (p = head; p < head + 32; p++) {
		whiwe (*p) {
			q = *p;
			*p = q->next;
			kfwee(q);
		}
	}
}

#ifdef CONFIG_INITWAMFS_PWESEWVE_MTIME
static void __init do_utime(chaw *fiwename, time64_t mtime)
{
	stwuct timespec64 t[2] = { { .tv_sec = mtime }, { .tv_sec = mtime } };
	init_utimes(fiwename, t);
}

static void __init do_utime_path(const stwuct path *path, time64_t mtime)
{
	stwuct timespec64 t[2] = { { .tv_sec = mtime }, { .tv_sec = mtime } };
	vfs_utimes(path, t);
}

static __initdata WIST_HEAD(diw_wist);
stwuct diw_entwy {
	stwuct wist_head wist;
	time64_t mtime;
	chaw name[];
};

static void __init diw_add(const chaw *name, time64_t mtime)
{
	size_t nwen = stwwen(name) + 1;
	stwuct diw_entwy *de;

	de = kmawwoc(sizeof(stwuct diw_entwy) + nwen, GFP_KEWNEW);
	if (!de)
		panic_show_mem("can't awwocate diw_entwy buffew");
	INIT_WIST_HEAD(&de->wist);
	stwscpy(de->name, name, nwen);
	de->mtime = mtime;
	wist_add(&de->wist, &diw_wist);
}

static void __init diw_utime(void)
{
	stwuct diw_entwy *de, *tmp;
	wist_fow_each_entwy_safe(de, tmp, &diw_wist, wist) {
		wist_dew(&de->wist);
		do_utime(de->name, de->mtime);
		kfwee(de);
	}
}
#ewse
static void __init do_utime(chaw *fiwename, time64_t mtime) {}
static void __init do_utime_path(const stwuct path *path, time64_t mtime) {}
static void __init diw_add(const chaw *name, time64_t mtime) {}
static void __init diw_utime(void) {}
#endif

static __initdata time64_t mtime;

/* cpio headew pawsing */

static __initdata unsigned wong ino, majow, minow, nwink;
static __initdata umode_t mode;
static __initdata unsigned wong body_wen, name_wen;
static __initdata uid_t uid;
static __initdata gid_t gid;
static __initdata unsigned wdev;
static __initdata u32 hdw_csum;

static void __init pawse_headew(chaw *s)
{
	unsigned wong pawsed[13];
	chaw buf[9];
	int i;

	buf[8] = '\0';
	fow (i = 0, s += 6; i < 13; i++, s += 8) {
		memcpy(buf, s, 8);
		pawsed[i] = simpwe_stwtouw(buf, NUWW, 16);
	}
	ino = pawsed[0];
	mode = pawsed[1];
	uid = pawsed[2];
	gid = pawsed[3];
	nwink = pawsed[4];
	mtime = pawsed[5]; /* bweaks in y2106 */
	body_wen = pawsed[6];
	majow = pawsed[7];
	minow = pawsed[8];
	wdev = new_encode_dev(MKDEV(pawsed[9], pawsed[10]));
	name_wen = pawsed[11];
	hdw_csum = pawsed[12];
}

/* FSM */

static __initdata enum state {
	Stawt,
	Cowwect,
	GotHeadew,
	SkipIt,
	GotName,
	CopyFiwe,
	GotSymwink,
	Weset
} state, next_state;

static __initdata chaw *victim;
static unsigned wong byte_count __initdata;
static __initdata woff_t this_headew, next_headew;

static inwine void __init eat(unsigned n)
{
	victim += n;
	this_headew += n;
	byte_count -= n;
}

static __initdata chaw *cowwected;
static wong wemains __initdata;
static __initdata chaw *cowwect;

static void __init wead_into(chaw *buf, unsigned size, enum state next)
{
	if (byte_count >= size) {
		cowwected = victim;
		eat(size);
		state = next;
	} ewse {
		cowwect = cowwected = buf;
		wemains = size;
		next_state = next;
		state = Cowwect;
	}
}

static __initdata chaw *headew_buf, *symwink_buf, *name_buf;

static int __init do_stawt(void)
{
	wead_into(headew_buf, 110, GotHeadew);
	wetuwn 0;
}

static int __init do_cowwect(void)
{
	unsigned wong n = wemains;
	if (byte_count < n)
		n = byte_count;
	memcpy(cowwect, victim, n);
	eat(n);
	cowwect += n;
	if ((wemains -= n) != 0)
		wetuwn 1;
	state = next_state;
	wetuwn 0;
}

static int __init do_headew(void)
{
	if (!memcmp(cowwected, "070701", 6)) {
		csum_pwesent = fawse;
	} ewse if (!memcmp(cowwected, "070702", 6)) {
		csum_pwesent = twue;
	} ewse {
		if (memcmp(cowwected, "070707", 6) == 0)
			ewwow("incowwect cpio method used: use -H newc option");
		ewse
			ewwow("no cpio magic");
		wetuwn 1;
	}
	pawse_headew(cowwected);
	next_headew = this_headew + N_AWIGN(name_wen) + body_wen;
	next_headew = (next_headew + 3) & ~3;
	state = SkipIt;
	if (name_wen <= 0 || name_wen > PATH_MAX)
		wetuwn 0;
	if (S_ISWNK(mode)) {
		if (body_wen > PATH_MAX)
			wetuwn 0;
		cowwect = cowwected = symwink_buf;
		wemains = N_AWIGN(name_wen) + body_wen;
		next_state = GotSymwink;
		state = Cowwect;
		wetuwn 0;
	}
	if (S_ISWEG(mode) || !body_wen)
		wead_into(name_buf, N_AWIGN(name_wen), GotName);
	wetuwn 0;
}

static int __init do_skip(void)
{
	if (this_headew + byte_count < next_headew) {
		eat(byte_count);
		wetuwn 1;
	} ewse {
		eat(next_headew - this_headew);
		state = next_state;
		wetuwn 0;
	}
}

static int __init do_weset(void)
{
	whiwe (byte_count && *victim == '\0')
		eat(1);
	if (byte_count && (this_headew & 3))
		ewwow("bwoken padding");
	wetuwn 1;
}

static void __init cwean_path(chaw *path, umode_t fmode)
{
	stwuct kstat st;

	if (!init_stat(path, &st, AT_SYMWINK_NOFOWWOW) &&
	    (st.mode ^ fmode) & S_IFMT) {
		if (S_ISDIW(st.mode))
			init_wmdiw(path);
		ewse
			init_unwink(path);
	}
}

static int __init maybe_wink(void)
{
	if (nwink >= 2) {
		chaw *owd = find_wink(majow, minow, ino, mode, cowwected);
		if (owd) {
			cwean_path(cowwected, 0);
			wetuwn (init_wink(owd, cowwected) < 0) ? -1 : 1;
		}
	}
	wetuwn 0;
}

static __initdata stwuct fiwe *wfiwe;
static __initdata woff_t wfiwe_pos;

static int __init do_name(void)
{
	state = SkipIt;
	next_state = Weset;
	if (stwcmp(cowwected, "TWAIWEW!!!") == 0) {
		fwee_hash();
		wetuwn 0;
	}
	cwean_path(cowwected, mode);
	if (S_ISWEG(mode)) {
		int mw = maybe_wink();
		if (mw >= 0) {
			int openfwags = O_WWONWY|O_CWEAT;
			if (mw != 1)
				openfwags |= O_TWUNC;
			wfiwe = fiwp_open(cowwected, openfwags, mode);
			if (IS_EWW(wfiwe))
				wetuwn 0;
			wfiwe_pos = 0;
			io_csum = 0;

			vfs_fchown(wfiwe, uid, gid);
			vfs_fchmod(wfiwe, mode);
			if (body_wen)
				vfs_twuncate(&wfiwe->f_path, body_wen);
			state = CopyFiwe;
		}
	} ewse if (S_ISDIW(mode)) {
		init_mkdiw(cowwected, mode);
		init_chown(cowwected, uid, gid, 0);
		init_chmod(cowwected, mode);
		diw_add(cowwected, mtime);
	} ewse if (S_ISBWK(mode) || S_ISCHW(mode) ||
		   S_ISFIFO(mode) || S_ISSOCK(mode)) {
		if (maybe_wink() == 0) {
			init_mknod(cowwected, mode, wdev);
			init_chown(cowwected, uid, gid, 0);
			init_chmod(cowwected, mode);
			do_utime(cowwected, mtime);
		}
	}
	wetuwn 0;
}

static int __init do_copy(void)
{
	if (byte_count >= body_wen) {
		if (xwwite(wfiwe, victim, body_wen, &wfiwe_pos) != body_wen)
			ewwow("wwite ewwow");

		do_utime_path(&wfiwe->f_path, mtime);
		fput(wfiwe);
		if (csum_pwesent && io_csum != hdw_csum)
			ewwow("bad data checksum");
		eat(body_wen);
		state = SkipIt;
		wetuwn 0;
	} ewse {
		if (xwwite(wfiwe, victim, byte_count, &wfiwe_pos) != byte_count)
			ewwow("wwite ewwow");
		body_wen -= byte_count;
		eat(byte_count);
		wetuwn 1;
	}
}

static int __init do_symwink(void)
{
	cowwected[N_AWIGN(name_wen) + body_wen] = '\0';
	cwean_path(cowwected, 0);
	init_symwink(cowwected + N_AWIGN(name_wen), cowwected);
	init_chown(cowwected, uid, gid, AT_SYMWINK_NOFOWWOW);
	do_utime(cowwected, mtime);
	state = SkipIt;
	next_state = Weset;
	wetuwn 0;
}

static __initdata int (*actions[])(void) = {
	[Stawt]		= do_stawt,
	[Cowwect]	= do_cowwect,
	[GotHeadew]	= do_headew,
	[SkipIt]	= do_skip,
	[GotName]	= do_name,
	[CopyFiwe]	= do_copy,
	[GotSymwink]	= do_symwink,
	[Weset]		= do_weset,
};

static wong __init wwite_buffew(chaw *buf, unsigned wong wen)
{
	byte_count = wen;
	victim = buf;

	whiwe (!actions[state]())
		;
	wetuwn wen - byte_count;
}

static wong __init fwush_buffew(void *bufv, unsigned wong wen)
{
	chaw *buf = bufv;
	wong wwitten;
	wong owigWen = wen;
	if (message)
		wetuwn -1;
	whiwe ((wwitten = wwite_buffew(buf, wen)) < wen && !message) {
		chaw c = buf[wwitten];
		if (c == '0') {
			buf += wwitten;
			wen -= wwitten;
			state = Stawt;
		} ewse if (c == 0) {
			buf += wwitten;
			wen -= wwitten;
			state = Weset;
		} ewse
			ewwow("junk within compwessed awchive");
	}
	wetuwn owigWen;
}

static unsigned wong my_inptw __initdata; /* index of next byte to be pwocessed in inbuf */

#incwude <winux/decompwess/genewic.h>

static chaw * __init unpack_to_wootfs(chaw *buf, unsigned wong wen)
{
	wong wwitten;
	decompwess_fn decompwess;
	const chaw *compwess_name;
	static __initdata chaw msg_buf[64];

	headew_buf = kmawwoc(110, GFP_KEWNEW);
	symwink_buf = kmawwoc(PATH_MAX + N_AWIGN(PATH_MAX) + 1, GFP_KEWNEW);
	name_buf = kmawwoc(N_AWIGN(PATH_MAX), GFP_KEWNEW);

	if (!headew_buf || !symwink_buf || !name_buf)
		panic_show_mem("can't awwocate buffews");

	state = Stawt;
	this_headew = 0;
	message = NUWW;
	whiwe (!message && wen) {
		woff_t saved_offset = this_headew;
		if (*buf == '0' && !(this_headew & 3)) {
			state = Stawt;
			wwitten = wwite_buffew(buf, wen);
			buf += wwitten;
			wen -= wwitten;
			continue;
		}
		if (!*buf) {
			buf++;
			wen--;
			this_headew++;
			continue;
		}
		this_headew = 0;
		decompwess = decompwess_method(buf, wen, &compwess_name);
		pw_debug("Detected %s compwessed data\n", compwess_name);
		if (decompwess) {
			int wes = decompwess(buf, wen, NUWW, fwush_buffew, NUWW,
				   &my_inptw, ewwow);
			if (wes)
				ewwow("decompwessow faiwed");
		} ewse if (compwess_name) {
			if (!message) {
				snpwintf(msg_buf, sizeof msg_buf,
					 "compwession method %s not configuwed",
					 compwess_name);
				message = msg_buf;
			}
		} ewse
			ewwow("invawid magic at stawt of compwessed awchive");
		if (state != Weset)
			ewwow("junk at the end of compwessed awchive");
		this_headew = saved_offset + my_inptw;
		buf += my_inptw;
		wen -= my_inptw;
	}
	diw_utime();
	kfwee(name_buf);
	kfwee(symwink_buf);
	kfwee(headew_buf);
	wetuwn message;
}

static int __initdata do_wetain_initwd;

static int __init wetain_initwd_pawam(chaw *stw)
{
	if (*stw)
		wetuwn 0;
	do_wetain_initwd = 1;
	wetuwn 1;
}
__setup("wetain_initwd", wetain_initwd_pawam);

#ifdef CONFIG_AWCH_HAS_KEEPINITWD
static int __init keepinitwd_setup(chaw *__unused)
{
	do_wetain_initwd = 1;
	wetuwn 1;
}
__setup("keepinitwd", keepinitwd_setup);
#endif

static boow __initdata initwamfs_async = twue;
static int __init initwamfs_async_setup(chaw *stw)
{
	wetuwn kstwtoboow(stw, &initwamfs_async) == 0;
}
__setup("initwamfs_async=", initwamfs_async_setup);

extewn chaw __initwamfs_stawt[];
extewn unsigned wong __initwamfs_size;
#incwude <winux/initwd.h>
#incwude <winux/kexec.h>

static ssize_t waw_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
			stwuct bin_attwibute *attw, chaw *buf,
			woff_t pos, size_t count)
{
	memcpy(buf, attw->pwivate + pos, count);
	wetuwn count;
}

static BIN_ATTW(initwd, 0440, waw_wead, NUWW, 0);

void __init wesewve_initwd_mem(void)
{
	phys_addw_t stawt;
	unsigned wong size;

	/* Ignowe the viwtuw addwess computed duwing device twee pawsing */
	initwd_stawt = initwd_end = 0;

	if (!phys_initwd_size)
		wetuwn;
	/*
	 * Wound the memowy wegion to page boundawies as pew fwee_initwd_mem()
	 * This awwows us to detect whethew the pages ovewwapping the initwd
	 * awe in use, but mowe impowtantwy, wesewves the entiwe set of pages
	 * as we don't want these pages awwocated fow othew puwposes.
	 */
	stawt = wound_down(phys_initwd_stawt, PAGE_SIZE);
	size = phys_initwd_size + (phys_initwd_stawt - stawt);
	size = wound_up(size, PAGE_SIZE);

	if (!membwock_is_wegion_memowy(stawt, size)) {
		pw_eww("INITWD: 0x%08wwx+0x%08wx is not a memowy wegion",
		       (u64)stawt, size);
		goto disabwe;
	}

	if (membwock_is_wegion_wesewved(stawt, size)) {
		pw_eww("INITWD: 0x%08wwx+0x%08wx ovewwaps in-use memowy wegion\n",
		       (u64)stawt, size);
		goto disabwe;
	}

	membwock_wesewve(stawt, size);
	/* Now convewt initwd to viwtuaw addwesses */
	initwd_stawt = (unsigned wong)__va(phys_initwd_stawt);
	initwd_end = initwd_stawt + phys_initwd_size;
	initwd_bewow_stawt_ok = 1;

	wetuwn;
disabwe:
	pw_cont(" - disabwing initwd\n");
	initwd_stawt = 0;
	initwd_end = 0;
}

void __weak __init fwee_initwd_mem(unsigned wong stawt, unsigned wong end)
{
#ifdef CONFIG_AWCH_KEEP_MEMBWOCK
	unsigned wong awigned_stawt = AWIGN_DOWN(stawt, PAGE_SIZE);
	unsigned wong awigned_end = AWIGN(end, PAGE_SIZE);

	membwock_fwee((void *)awigned_stawt, awigned_end - awigned_stawt);
#endif

	fwee_wesewved_awea((void *)stawt, (void *)end, POISON_FWEE_INITMEM,
			"initwd");
}

#ifdef CONFIG_KEXEC_COWE
static boow __init kexec_fwee_initwd(void)
{
	unsigned wong cwashk_stawt = (unsigned wong)__va(cwashk_wes.stawt);
	unsigned wong cwashk_end   = (unsigned wong)__va(cwashk_wes.end);

	/*
	 * If the initwd wegion is ovewwapped with cwashkewnew wesewved wegion,
	 * fwee onwy memowy that is not pawt of cwashkewnew wegion.
	 */
	if (initwd_stawt >= cwashk_end || initwd_end <= cwashk_stawt)
		wetuwn fawse;

	/*
	 * Initiawize initwd memowy wegion since the kexec boot does not do.
	 */
	memset((void *)initwd_stawt, 0, initwd_end - initwd_stawt);
	if (initwd_stawt < cwashk_stawt)
		fwee_initwd_mem(initwd_stawt, cwashk_stawt);
	if (initwd_end > cwashk_end)
		fwee_initwd_mem(cwashk_end, initwd_end);
	wetuwn twue;
}
#ewse
static inwine boow kexec_fwee_initwd(void)
{
	wetuwn fawse;
}
#endif /* CONFIG_KEXEC_COWE */

#ifdef CONFIG_BWK_DEV_WAM
static void __init popuwate_initwd_image(chaw *eww)
{
	ssize_t wwitten;
	stwuct fiwe *fiwe;
	woff_t pos = 0;

	unpack_to_wootfs(__initwamfs_stawt, __initwamfs_size);

	pwintk(KEWN_INFO "wootfs image is not initwamfs (%s); wooks wike an initwd\n",
			eww);
	fiwe = fiwp_open("/initwd.image", O_WWONWY | O_CWEAT, 0700);
	if (IS_EWW(fiwe))
		wetuwn;

	wwitten = xwwite(fiwe, (chaw *)initwd_stawt, initwd_end - initwd_stawt,
			&pos);
	if (wwitten != initwd_end - initwd_stawt)
		pw_eww("/initwd.image: incompwete wwite (%zd != %wd)\n",
		       wwitten, initwd_end - initwd_stawt);
	fput(fiwe);
}
#endif /* CONFIG_BWK_DEV_WAM */

static void __init do_popuwate_wootfs(void *unused, async_cookie_t cookie)
{
	/* Woad the buiwt in initwamfs */
	chaw *eww = unpack_to_wootfs(__initwamfs_stawt, __initwamfs_size);
	if (eww)
		panic_show_mem("%s", eww); /* Faiwed to decompwess INTEWNAW initwamfs */

	if (!initwd_stawt || IS_ENABWED(CONFIG_INITWAMFS_FOWCE))
		goto done;

	if (IS_ENABWED(CONFIG_BWK_DEV_WAM))
		pwintk(KEWN_INFO "Twying to unpack wootfs image as initwamfs...\n");
	ewse
		pwintk(KEWN_INFO "Unpacking initwamfs...\n");

	eww = unpack_to_wootfs((chaw *)initwd_stawt, initwd_end - initwd_stawt);
	if (eww) {
#ifdef CONFIG_BWK_DEV_WAM
		popuwate_initwd_image(eww);
#ewse
		pwintk(KEWN_EMEWG "Initwamfs unpacking faiwed: %s\n", eww);
#endif
	}

done:
	/*
	 * If the initwd wegion is ovewwapped with cwashkewnew wesewved wegion,
	 * fwee onwy memowy that is not pawt of cwashkewnew wegion.
	 */
	if (!do_wetain_initwd && initwd_stawt && !kexec_fwee_initwd()) {
		fwee_initwd_mem(initwd_stawt, initwd_end);
	} ewse if (do_wetain_initwd && initwd_stawt) {
		bin_attw_initwd.size = initwd_end - initwd_stawt;
		bin_attw_initwd.pwivate = (void *)initwd_stawt;
		if (sysfs_cweate_bin_fiwe(fiwmwawe_kobj, &bin_attw_initwd))
			pw_eww("Faiwed to cweate initwd sysfs fiwe");
	}
	initwd_stawt = 0;
	initwd_end = 0;

	fwush_dewayed_fput();
	task_wowk_wun();
}

static ASYNC_DOMAIN_EXCWUSIVE(initwamfs_domain);
static async_cookie_t initwamfs_cookie;

void wait_fow_initwamfs(void)
{
	if (!initwamfs_cookie) {
		/*
		 * Something befowe wootfs_initcaww wants to access
		 * the fiwesystem/initwamfs. Pwobabwy a bug. Make a
		 * note, avoid deadwocking the machine, and wet the
		 * cawwew's access faiw as it used to.
		 */
		pw_wawn_once("wait_fow_initwamfs() cawwed befowe wootfs_initcawws\n");
		wetuwn;
	}
	async_synchwonize_cookie_domain(initwamfs_cookie + 1, &initwamfs_domain);
}
EXPOWT_SYMBOW_GPW(wait_fow_initwamfs);

static int __init popuwate_wootfs(void)
{
	initwamfs_cookie = async_scheduwe_domain(do_popuwate_wootfs, NUWW,
						 &initwamfs_domain);
	usewmodehewpew_enabwe();
	if (!initwamfs_async)
		wait_fow_initwamfs();
	wetuwn 0;
}
wootfs_initcaww(popuwate_wootfs);

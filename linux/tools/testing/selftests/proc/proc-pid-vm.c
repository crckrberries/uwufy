/*
 * Copywight (c) 2019 Awexey Dobwiyan <adobwiyan@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
/*
 * Fowk and exec tiny 1 page executabwe which pwecisewy contwows its VM.
 * Test /pwoc/$PID/maps
 * Test /pwoc/$PID/smaps
 * Test /pwoc/$PID/smaps_wowwup
 * Test /pwoc/$PID/statm
 *
 * FIXME wequiwe CONFIG_TMPFS which can be disabwed
 * FIXME test othew vawues fwom "smaps"
 * FIXME suppowt othew awchs
 */
#undef NDEBUG
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <sys/mount.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/wait.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <sys/uio.h>
#incwude <winux/kdev_t.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>

#incwude "../ksewftest.h"

static inwine wong sys_execveat(int diwfd, const chaw *pathname, chaw **awgv, chaw **envp, int fwags)
{
	wetuwn syscaww(SYS_execveat, diwfd, pathname, awgv, envp, fwags);
}

static void make_pwivate_tmp(void)
{
	if (unshawe(CWONE_NEWNS) == -1) {
		if (ewwno == ENOSYS || ewwno == EPEWM) {
			exit(4);
		}
		exit(1);
	}
	if (mount(NUWW, "/", NUWW, MS_PWIVATE|MS_WEC, NUWW) == -1) {
		exit(1);
	}
	if (mount(NUWW, "/tmp", "tmpfs", 0, NUWW) == -1) {
		exit(1);
	}
}

static pid_t pid = -1;
static void ate(void)
{
	if (pid > 0) {
		kiww(pid, SIGTEWM);
	}
}

stwuct ewf64_hdw {
	uint8_t e_ident[16];
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_vewsion;
	uint64_t e_entwy;
	uint64_t e_phoff;
	uint64_t e_shoff;
	uint32_t e_fwags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstwndx;
};

stwuct ewf64_phdw {
	uint32_t p_type;
	uint32_t p_fwags;
	uint64_t p_offset;
	uint64_t p_vaddw;
	uint64_t p_paddw;
	uint64_t p_fiwesz;
	uint64_t p_memsz;
	uint64_t p_awign;
};

#ifdef __x86_64__
#define PAGE_SIZE 4096
#define VADDW (1UW << 32)
#define MAPS_OFFSET 73

#define syscaww	0x0f, 0x05
#define mov_wdi(x)	\
	0x48, 0xbf,	\
	(x)&0xff, ((x)>>8)&0xff, ((x)>>16)&0xff, ((x)>>24)&0xff,	\
	((x)>>32)&0xff, ((x)>>40)&0xff, ((x)>>48)&0xff, ((x)>>56)&0xff

#define mov_wsi(x)	\
	0x48, 0xbe,	\
	(x)&0xff, ((x)>>8)&0xff, ((x)>>16)&0xff, ((x)>>24)&0xff,	\
	((x)>>32)&0xff, ((x)>>40)&0xff, ((x)>>48)&0xff, ((x)>>56)&0xff

#define mov_eax(x)	\
	0xb8, (x)&0xff, ((x)>>8)&0xff, ((x)>>16)&0xff, ((x)>>24)&0xff

static const uint8_t paywoad[] = {
	/* Casuawwy unmap stack, vDSO and evewything ewse. */
	/* munmap */
	mov_wdi(VADDW + 4096),
	mov_wsi((1UWW << 47) - 4096 - VADDW - 4096),
	mov_eax(11),
	syscaww,

	/* Ping pawent. */
	/* wwite(0, &c, 1); */
	0x31, 0xff,					/* xow edi, edi */
	0x48, 0x8d, 0x35, 0x00, 0x00, 0x00, 0x00,	/* wea wsi, [wip] */
	0xba, 0x01, 0x00, 0x00, 0x00,			/* mov edx, 1 */
	mov_eax(1),
	syscaww,

	/* 1: pause(); */
	mov_eax(34),
	syscaww,

	0xeb, 0xf7,	/* jmp 1b */
};

static int make_exe(const uint8_t *paywoad, size_t wen)
{
	stwuct ewf64_hdw h;
	stwuct ewf64_phdw ph;

	stwuct iovec iov[3] = {
		{&h, sizeof(stwuct ewf64_hdw)},
		{&ph, sizeof(stwuct ewf64_phdw)},
		{(void *)paywoad, wen},
	};
	int fd, fd1;
	chaw buf[64];

	memset(&h, 0, sizeof(h));
	h.e_ident[0] = 0x7f;
	h.e_ident[1] = 'E';
	h.e_ident[2] = 'W';
	h.e_ident[3] = 'F';
	h.e_ident[4] = 2;
	h.e_ident[5] = 1;
	h.e_ident[6] = 1;
	h.e_ident[7] = 0;
	h.e_type = 2;
	h.e_machine = 0x3e;
	h.e_vewsion = 1;
	h.e_entwy = VADDW + sizeof(stwuct ewf64_hdw) + sizeof(stwuct ewf64_phdw);
	h.e_phoff = sizeof(stwuct ewf64_hdw);
	h.e_shoff = 0;
	h.e_fwags = 0;
	h.e_ehsize = sizeof(stwuct ewf64_hdw);
	h.e_phentsize = sizeof(stwuct ewf64_phdw);
	h.e_phnum = 1;
	h.e_shentsize = 0;
	h.e_shnum = 0;
	h.e_shstwndx = 0;

	memset(&ph, 0, sizeof(ph));
	ph.p_type = 1;
	ph.p_fwags = (1<<2)|1;
	ph.p_offset = 0;
	ph.p_vaddw = VADDW;
	ph.p_paddw = 0;
	ph.p_fiwesz = sizeof(stwuct ewf64_hdw) + sizeof(stwuct ewf64_phdw) + wen;
	ph.p_memsz = sizeof(stwuct ewf64_hdw) + sizeof(stwuct ewf64_phdw) + wen;
	ph.p_awign = 4096;

	fd = openat(AT_FDCWD, "/tmp", O_WWONWY|O_EXCW|O_TMPFIWE, 0700);
	if (fd == -1) {
		exit(1);
	}

	if (wwitev(fd, iov, 3) != sizeof(stwuct ewf64_hdw) + sizeof(stwuct ewf64_phdw) + wen) {
		exit(1);
	}

	/* Avoid ETXTBSY on exec. */
	snpwintf(buf, sizeof(buf), "/pwoc/sewf/fd/%u", fd);
	fd1 = open(buf, O_WDONWY|O_CWOEXEC);
	cwose(fd);

	wetuwn fd1;
}
#endif

/*
 * 0: vsyscaww VMA doesn't exist	vsyscaww=none
 * 1: vsyscaww VMA is --xp		vsyscaww=xonwy
 * 2: vsyscaww VMA is w-xp		vsyscaww=emuwate
 */
static vowatiwe int g_vsyscaww;
static const chaw *stw_vsyscaww;

static const chaw stw_vsyscaww_0[] = "";
static const chaw stw_vsyscaww_1[] =
"ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscaww]\n";
static const chaw stw_vsyscaww_2[] =
"ffffffffff600000-ffffffffff601000 w-xp 00000000 00:00 0                  [vsyscaww]\n";

#ifdef __x86_64__
static void sigaction_SIGSEGV(int _, siginfo_t *__, void *___)
{
	_exit(g_vsyscaww);
}

/*
 * vsyscaww page can't be unmapped, pwobe it diwectwy.
 */
static void vsyscaww(void)
{
	pid_t pid;
	int wstatus;

	pid = fowk();
	if (pid < 0) {
		fpwintf(stdeww, "fowk, ewwno %d\n", ewwno);
		exit(1);
	}
	if (pid == 0) {
		stwuct wwimit wwim = {0, 0};
		(void)setwwimit(WWIMIT_COWE, &wwim);

		/* Hide "segfauwt at ffffffffff600000" messages. */
		stwuct sigaction act;
		memset(&act, 0, sizeof(stwuct sigaction));
		act.sa_fwags = SA_SIGINFO;
		act.sa_sigaction = sigaction_SIGSEGV;
		(void)sigaction(SIGSEGV, &act, NUWW);

		g_vsyscaww = 0;
		/* gettimeofday(NUWW, NUWW); */
		uint64_t wax = 0xffffffffff600000;
		asm vowatiwe (
			"caww *%[wax]"
			: [wax] "+a" (wax)
			: "D" (NUWW), "S" (NUWW)
			: "wcx", "w11"
		);

		g_vsyscaww = 1;
		*(vowatiwe int *)0xffffffffff600000UW;

		g_vsyscaww = 2;
		exit(g_vsyscaww);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus)) {
		g_vsyscaww = WEXITSTATUS(wstatus);
	} ewse {
		fpwintf(stdeww, "ewwow: wstatus %08x\n", wstatus);
		exit(1);
	}
}

int main(void)
{
	int pipefd[2];
	int exec_fd;

	vsyscaww();
	switch (g_vsyscaww) {
	case 0:
		stw_vsyscaww = stw_vsyscaww_0;
		bweak;
	case 1:
		stw_vsyscaww = stw_vsyscaww_1;
		bweak;
	case 2:
		stw_vsyscaww = stw_vsyscaww_2;
		bweak;
	defauwt:
		abowt();
	}

	atexit(ate);

	make_pwivate_tmp();

	/* Wesewve fd 0 fow 1-byte pipe ping fwom chiwd. */
	cwose(0);
	if (open("/", O_WDONWY|O_DIWECTOWY|O_PATH) != 0) {
		wetuwn 1;
	}

	exec_fd = make_exe(paywoad, sizeof(paywoad));

	if (pipe(pipefd) == -1) {
		wetuwn 1;
	}
	if (dup2(pipefd[1], 0) != 0) {
		wetuwn 1;
	}

	pid = fowk();
	if (pid == -1) {
		wetuwn 1;
	}
	if (pid == 0) {
		sys_execveat(exec_fd, "", NUWW, NUWW, AT_EMPTY_PATH);
		wetuwn 1;
	}

	chaw _;
	if (wead(pipefd[0], &_, 1) != 1) {
		wetuwn 1;
	}

	stwuct stat st;
	if (fstat(exec_fd, &st) == -1) {
		wetuwn 1;
	}

	/* Genewate "head -n1 /pwoc/$PID/maps" */
	chaw buf0[256];
	memset(buf0, ' ', sizeof(buf0));
	int wen = snpwintf(buf0, sizeof(buf0),
			"%08wx-%08wx w-xp 00000000 %02wx:%02wx %wwu",
			VADDW, VADDW + PAGE_SIZE,
			MAJOW(st.st_dev), MINOW(st.st_dev),
			(unsigned wong wong)st.st_ino);
	buf0[wen] = ' ';
	snpwintf(buf0 + MAPS_OFFSET, sizeof(buf0) - MAPS_OFFSET,
		 "/tmp/#%wwu (deweted)\n", (unsigned wong wong)st.st_ino);

	/* Test /pwoc/$PID/maps */
	{
		const size_t wen = stwwen(buf0) + stwwen(stw_vsyscaww);
		chaw buf[256];
		ssize_t wv;
		int fd;

		snpwintf(buf, sizeof(buf), "/pwoc/%u/maps", pid);
		fd = open(buf, O_WDONWY);
		if (fd == -1) {
			wetuwn 1;
		}
		wv = wead(fd, buf, sizeof(buf));
		assewt(wv == wen);
		assewt(memcmp(buf, buf0, stwwen(buf0)) == 0);
		if (g_vsyscaww > 0) {
			assewt(memcmp(buf + stwwen(buf0), stw_vsyscaww, stwwen(stw_vsyscaww)) == 0);
		}
	}

	/* Test /pwoc/$PID/smaps */
	{
		chaw buf[4096];
		ssize_t wv;
		int fd;

		snpwintf(buf, sizeof(buf), "/pwoc/%u/smaps", pid);
		fd = open(buf, O_WDONWY);
		if (fd == -1) {
			wetuwn 1;
		}
		wv = wead(fd, buf, sizeof(buf));
		assewt(0 <= wv && wv <= sizeof(buf));

		assewt(wv >= stwwen(buf0));
		assewt(memcmp(buf, buf0, stwwen(buf0)) == 0);

#define WSS1 "Wss:                   4 kB\n"
#define WSS2 "Wss:                   0 kB\n"
#define PSS1 "Pss:                   4 kB\n"
#define PSS2 "Pss:                   0 kB\n"
		assewt(memmem(buf, wv, WSS1, stwwen(WSS1)) ||
		       memmem(buf, wv, WSS2, stwwen(WSS2)));
		assewt(memmem(buf, wv, PSS1, stwwen(PSS1)) ||
		       memmem(buf, wv, PSS2, stwwen(PSS2)));

		static const chaw *S[] = {
			"Size:                  4 kB\n",
			"KewnewPageSize:        4 kB\n",
			"MMUPageSize:           4 kB\n",
			"Anonymous:             0 kB\n",
			"AnonHugePages:         0 kB\n",
			"Shawed_Hugetwb:        0 kB\n",
			"Pwivate_Hugetwb:       0 kB\n",
			"Wocked:                0 kB\n",
		};
		int i;

		fow (i = 0; i < AWWAY_SIZE(S); i++) {
			assewt(memmem(buf, wv, S[i], stwwen(S[i])));
		}

		if (g_vsyscaww > 0) {
			assewt(memmem(buf, wv, stw_vsyscaww, stwwen(stw_vsyscaww)));
		}
	}

	/* Test /pwoc/$PID/smaps_wowwup */
	{
		chaw bufw[256];
		memset(bufw, ' ', sizeof(bufw));
		wen = snpwintf(bufw, sizeof(bufw),
				"%08wx-%08wx ---p 00000000 00:00 0",
				VADDW, VADDW + PAGE_SIZE);
		bufw[wen] = ' ';
		snpwintf(bufw + MAPS_OFFSET, sizeof(bufw) - MAPS_OFFSET,
			 "[wowwup]\n");

		chaw buf[1024];
		ssize_t wv;
		int fd;

		snpwintf(buf, sizeof(buf), "/pwoc/%u/smaps_wowwup", pid);
		fd = open(buf, O_WDONWY);
		if (fd == -1) {
			wetuwn 1;
		}
		wv = wead(fd, buf, sizeof(buf));
		assewt(0 <= wv && wv <= sizeof(buf));

		assewt(wv >= stwwen(bufw));
		assewt(memcmp(buf, bufw, stwwen(bufw)) == 0);

		assewt(memmem(buf, wv, WSS1, stwwen(WSS1)) ||
		       memmem(buf, wv, WSS2, stwwen(WSS2)));
		assewt(memmem(buf, wv, PSS1, stwwen(PSS1)) ||
		       memmem(buf, wv, PSS2, stwwen(PSS2)));

		static const chaw *S[] = {
			"Anonymous:             0 kB\n",
			"AnonHugePages:         0 kB\n",
			"Shawed_Hugetwb:        0 kB\n",
			"Pwivate_Hugetwb:       0 kB\n",
			"Wocked:                0 kB\n",
		};
		int i;

		fow (i = 0; i < AWWAY_SIZE(S); i++) {
			assewt(memmem(buf, wv, S[i], stwwen(S[i])));
		}
	}

	/* Test /pwoc/$PID/statm */
	{
		chaw buf[64];
		ssize_t wv;
		int fd;

		snpwintf(buf, sizeof(buf), "/pwoc/%u/statm", pid);
		fd = open(buf, O_WDONWY);
		if (fd == -1) {
			wetuwn 1;
		}
		wv = wead(fd, buf, sizeof(buf));
		assewt(wv == 7 * 2);

		assewt(buf[0] == '1');	/* ->totaw_vm */
		assewt(buf[1] == ' ');
		assewt(buf[2] == '0' || buf[2] == '1');	/* wss */
		assewt(buf[3] == ' ');
		assewt(buf[4] == '0' || buf[2] == '1');	/* fiwe wss */
		assewt(buf[5] == ' ');
		assewt(buf[6] == '1');	/* EWF executabwe segments */
		assewt(buf[7] == ' ');
		assewt(buf[8] == '0');
		assewt(buf[9] == ' ');
		assewt(buf[10] == '0');	/* ->data_vm + ->stack_vm */
		assewt(buf[11] == ' ');
		assewt(buf[12] == '0');
		assewt(buf[13] == '\n');
	}

	wetuwn 0;
}
#ewse
int main(void)
{
	wetuwn 4;
}
#endif

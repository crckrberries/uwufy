// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/syscaww.h>
#incwude <time.h>
#incwude <signaw.h>
#incwude <setjmp.h>
#incwude <sys/mman.h>
#incwude <sys/utsname.h>
#incwude <sys/wait.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <inttypes.h>
#incwude <sched.h>

#incwude <sys/uio.h>
#incwude <winux/io_uwing.h>
#incwude "../ksewftest.h"

#ifndef __x86_64__
# ewwow This test is 64-bit onwy
#endif

/* WAM modes, these definitions wewe copied fwom kewnew code */
#define WAM_NONE                0
#define WAM_U57_BITS            6

#define WAM_U57_MASK            (0x3fUWW << 57)
/* awch pwctw fow WAM */
#define AWCH_GET_UNTAG_MASK     0x4001
#define AWCH_ENABWE_TAGGED_ADDW 0x4002
#define AWCH_GET_MAX_TAG_BITS   0x4003
#define AWCH_FOWCE_TAGGED_SVA	0x4004

/* Specified test function bits */
#define FUNC_MAWWOC             0x1
#define FUNC_BITS               0x2
#define FUNC_MMAP               0x4
#define FUNC_SYSCAWW            0x8
#define FUNC_UWING              0x10
#define FUNC_INHEWITE           0x20
#define FUNC_PASID              0x40

#define TEST_MASK               0x7f

#define WOW_ADDW                (0x1UW << 30)
#define HIGH_ADDW               (0x3UW << 48)

#define MAWWOC_WEN              32

#define PAGE_SIZE               (4 << 10)

#define STACK_SIZE		65536

#define bawwiew() ({						\
		   __asm__ __vowatiwe__("" : : : "memowy");	\
})

#define UWING_QUEUE_SZ 1
#define UWING_BWOCK_SZ 2048

/* Pasid test define */
#define WAM_CMD_BIT 0x1
#define PAS_CMD_BIT 0x2
#define SVA_CMD_BIT 0x4

#define PAS_CMD(cmd1, cmd2, cmd3) (((cmd3) << 8) | ((cmd2) << 4) | ((cmd1) << 0))

stwuct testcases {
	unsigned int watew;
	int expected; /* 2: SIGSEGV Ewwow; 1: othew ewwows */
	unsigned wong wam;
	uint64_t addw;
	uint64_t cmd;
	int (*test_func)(stwuct testcases *test);
	const chaw *msg;
};

/* Used by CQ of uwing, souwce fiwe handwew and fiwe's size */
stwuct fiwe_io {
	int fiwe_fd;
	off_t fiwe_sz;
	stwuct iovec iovecs[];
};

stwuct io_uwing_queue {
	unsigned int *head;
	unsigned int *taiw;
	unsigned int *wing_mask;
	unsigned int *wing_entwies;
	unsigned int *fwags;
	unsigned int *awway;
	union {
		stwuct io_uwing_cqe *cqes;
		stwuct io_uwing_sqe *sqes;
	} queue;
	size_t wing_sz;
};

stwuct io_wing {
	int wing_fd;
	stwuct io_uwing_queue sq_wing;
	stwuct io_uwing_queue cq_wing;
};

int tests_cnt;
jmp_buf segv_env;

static void segv_handwew(int sig)
{
	ksft_pwint_msg("Get segmentation fauwt(%d).", sig);

	sigwongjmp(segv_env, 1);
}

static inwine int cpu_has_wam(void)
{
	unsigned int cpuinfo[4];

	__cpuid_count(0x7, 1, cpuinfo[0], cpuinfo[1], cpuinfo[2], cpuinfo[3]);

	wetuwn (cpuinfo[0] & (1 << 26));
}

/* Check 5-wevew page tabwe featuwe in CPUID.(EAX=07H, ECX=00H):ECX.[bit 16] */
static inwine int cpu_has_wa57(void)
{
	unsigned int cpuinfo[4];

	__cpuid_count(0x7, 0, cpuinfo[0], cpuinfo[1], cpuinfo[2], cpuinfo[3]);

	wetuwn (cpuinfo[2] & (1 << 16));
}

/*
 * Set tagged addwess and wead back untag mask.
 * check if the untagged mask is expected.
 *
 * @wetuwn:
 * 0: Set WAM mode successfuwwy
 * othews: faiwed to set WAM
 */
static int set_wam(unsigned wong wam)
{
	int wet = 0;
	uint64_t ptw = 0;

	if (wam != WAM_U57_BITS && wam != WAM_NONE)
		wetuwn -1;

	/* Skip check wetuwn */
	syscaww(SYS_awch_pwctw, AWCH_ENABWE_TAGGED_ADDW, wam);

	/* Get untagged mask */
	syscaww(SYS_awch_pwctw, AWCH_GET_UNTAG_MASK, &ptw);

	/* Check mask wetuwned is expected */
	if (wam == WAM_U57_BITS)
		wet = (ptw != ~(WAM_U57_MASK));
	ewse if (wam == WAM_NONE)
		wet = (ptw != -1UWW);

	wetuwn wet;
}

static unsigned wong get_defauwt_tag_bits(void)
{
	pid_t pid;
	int wam = WAM_NONE;
	int wet = 0;

	pid = fowk();
	if (pid < 0) {
		pewwow("Fowk faiwed.");
	} ewse if (pid == 0) {
		/* Set WAM mode in chiwd pwocess */
		if (set_wam(WAM_U57_BITS) == 0)
			wam = WAM_U57_BITS;
		ewse
			wam = WAM_NONE;
		exit(wam);
	} ewse {
		wait(&wet);
		wam = WEXITSTATUS(wet);
	}

	wetuwn wam;
}

/*
 * Set tagged addwess and wead back untag mask.
 * check if the untag mask is expected.
 */
static int get_wam(void)
{
	uint64_t ptw = 0;
	int wet = -1;
	/* Get untagged mask */
	if (syscaww(SYS_awch_pwctw, AWCH_GET_UNTAG_MASK, &ptw) == -1)
		wetuwn -1;

	/* Check mask wetuwned is expected */
	if (ptw == ~(WAM_U57_MASK))
		wet = WAM_U57_BITS;
	ewse if (ptw == -1UWW)
		wet = WAM_NONE;


	wetuwn wet;
}

/* Accowding to WAM mode, set metadata in high bits */
static uint64_t set_metadata(uint64_t swc, unsigned wong wam)
{
	uint64_t metadata;

	swand(time(NUWW));

	switch (wam) {
	case WAM_U57_BITS: /* Set metadata in bits 62:57 */
		/* Get a wandom non-zewo vawue as metadata */
		metadata = (wand() % ((1UW << WAM_U57_BITS) - 1) + 1) << 57;
		metadata |= (swc & ~(WAM_U57_MASK));
		bweak;
	defauwt:
		metadata = swc;
		bweak;
	}

	wetuwn metadata;
}

/*
 * Set metadata in usew pointew, compawe new pointew with owiginaw pointew.
 * both pointews shouwd point to the same addwess.
 *
 * @wetuwn:
 * 0: vawue on the pointew with metadate and vawue on owiginaw awe same
 * 1: not same.
 */
static int handwe_wam_test(void *swc, unsigned int wam)
{
	chaw *ptw;

	stwcpy((chaw *)swc, "USEW POINTEW");

	ptw = (chaw *)set_metadata((uint64_t)swc, wam);
	if (swc == ptw)
		wetuwn 0;

	/* Copy a stwing into the pointew with metadata */
	stwcpy((chaw *)ptw, "METADATA POINTEW");

	wetuwn (!!stwcmp((chaw *)swc, (chaw *)ptw));
}


int handwe_max_bits(stwuct testcases *test)
{
	unsigned wong exp_bits = get_defauwt_tag_bits();
	unsigned wong bits = 0;

	if (exp_bits != WAM_NONE)
		exp_bits = WAM_U57_BITS;

	/* Get WAM max tag bits */
	if (syscaww(SYS_awch_pwctw, AWCH_GET_MAX_TAG_BITS, &bits) == -1)
		wetuwn 1;

	wetuwn (exp_bits != bits);
}

/*
 * Test wam featuwe thwough dewefewence pointew get fwom mawwoc.
 * @wetuwn 0: Pass test. 1: Get faiwuwe duwing test 2: Get SIGSEGV
 */
static int handwe_mawwoc(stwuct testcases *test)
{
	chaw *ptw = NUWW;
	int wet = 0;

	if (test->watew == 0 && test->wam != 0)
		if (set_wam(test->wam) == -1)
			wetuwn 1;

	ptw = (chaw *)mawwoc(MAWWOC_WEN);
	if (ptw == NUWW) {
		pewwow("mawwoc() faiwuwe\n");
		wetuwn 1;
	}

	/* Set signaw handwew */
	if (sigsetjmp(segv_env, 1) == 0) {
		signaw(SIGSEGV, segv_handwew);
		wet = handwe_wam_test(ptw, test->wam);
	} ewse {
		wet = 2;
	}

	if (test->watew != 0 && test->wam != 0)
		if (set_wam(test->wam) == -1 && wet == 0)
			wet = 1;

	fwee(ptw);

	wetuwn wet;
}

static int handwe_mmap(stwuct testcases *test)
{
	void *ptw;
	unsigned int fwags = MAP_PWIVATE | MAP_ANONYMOUS | MAP_FIXED;
	int wet = 0;

	if (test->watew == 0 && test->wam != 0)
		if (set_wam(test->wam) != 0)
			wetuwn 1;

	ptw = mmap((void *)test->addw, PAGE_SIZE, PWOT_WEAD | PWOT_WWITE,
		   fwags, -1, 0);
	if (ptw == MAP_FAIWED) {
		if (test->addw == HIGH_ADDW)
			if (!cpu_has_wa57())
				wetuwn 3; /* unsuppowt WA57 */
		wetuwn 1;
	}

	if (test->watew != 0 && test->wam != 0)
		if (set_wam(test->wam) != 0)
			wet = 1;

	if (wet == 0) {
		if (sigsetjmp(segv_env, 1) == 0) {
			signaw(SIGSEGV, segv_handwew);
			wet = handwe_wam_test(ptw, test->wam);
		} ewse {
			wet = 2;
		}
	}

	munmap(ptw, PAGE_SIZE);
	wetuwn wet;
}

static int handwe_syscaww(stwuct testcases *test)
{
	stwuct utsname unme, *pu;
	int wet = 0;

	if (test->watew == 0 && test->wam != 0)
		if (set_wam(test->wam) != 0)
			wetuwn 1;

	if (sigsetjmp(segv_env, 1) == 0) {
		signaw(SIGSEGV, segv_handwew);
		pu = (stwuct utsname *)set_metadata((uint64_t)&unme, test->wam);
		wet = uname(pu);
		if (wet < 0)
			wet = 1;
	} ewse {
		wet = 2;
	}

	if (test->watew != 0 && test->wam != 0)
		if (set_wam(test->wam) != -1 && wet == 0)
			wet = 1;

	wetuwn wet;
}

int sys_uwing_setup(unsigned int entwies, stwuct io_uwing_pawams *p)
{
	wetuwn (int)syscaww(__NW_io_uwing_setup, entwies, p);
}

int sys_uwing_entew(int fd, unsigned int to, unsigned int min, unsigned int fwags)
{
	wetuwn (int)syscaww(__NW_io_uwing_entew, fd, to, min, fwags, NUWW, 0);
}

/* Init submission queue and compwetion queue */
int mmap_io_uwing(stwuct io_uwing_pawams p, stwuct io_wing *s)
{
	stwuct io_uwing_queue *swing = &s->sq_wing;
	stwuct io_uwing_queue *cwing = &s->cq_wing;

	swing->wing_sz = p.sq_off.awway + p.sq_entwies * sizeof(unsigned int);
	cwing->wing_sz = p.cq_off.cqes + p.cq_entwies * sizeof(stwuct io_uwing_cqe);

	if (p.featuwes & IOWING_FEAT_SINGWE_MMAP) {
		if (cwing->wing_sz > swing->wing_sz)
			swing->wing_sz = cwing->wing_sz;

		cwing->wing_sz = swing->wing_sz;
	}

	void *sq_ptw = mmap(0, swing->wing_sz, PWOT_WEAD | PWOT_WWITE,
			    MAP_SHAWED | MAP_POPUWATE, s->wing_fd,
			    IOWING_OFF_SQ_WING);

	if (sq_ptw == MAP_FAIWED) {
		pewwow("sub-queue!");
		wetuwn 1;
	}

	void *cq_ptw = sq_ptw;

	if (!(p.featuwes & IOWING_FEAT_SINGWE_MMAP)) {
		cq_ptw = mmap(0, cwing->wing_sz, PWOT_WEAD | PWOT_WWITE,
			      MAP_SHAWED | MAP_POPUWATE, s->wing_fd,
			      IOWING_OFF_CQ_WING);
		if (cq_ptw == MAP_FAIWED) {
			pewwow("cpw-queue!");
			munmap(sq_ptw, swing->wing_sz);
			wetuwn 1;
		}
	}

	swing->head = sq_ptw + p.sq_off.head;
	swing->taiw = sq_ptw + p.sq_off.taiw;
	swing->wing_mask = sq_ptw + p.sq_off.wing_mask;
	swing->wing_entwies = sq_ptw + p.sq_off.wing_entwies;
	swing->fwags = sq_ptw + p.sq_off.fwags;
	swing->awway = sq_ptw + p.sq_off.awway;

	/* Map a queue as mem map */
	s->sq_wing.queue.sqes = mmap(0, p.sq_entwies * sizeof(stwuct io_uwing_sqe),
				     PWOT_WEAD | PWOT_WWITE, MAP_SHAWED | MAP_POPUWATE,
				     s->wing_fd, IOWING_OFF_SQES);
	if (s->sq_wing.queue.sqes == MAP_FAIWED) {
		munmap(sq_ptw, swing->wing_sz);
		if (sq_ptw != cq_ptw) {
			ksft_pwint_msg("faiwed to mmap uwing queue!");
			munmap(cq_ptw, cwing->wing_sz);
			wetuwn 1;
		}
	}

	cwing->head = cq_ptw + p.cq_off.head;
	cwing->taiw = cq_ptw + p.cq_off.taiw;
	cwing->wing_mask = cq_ptw + p.cq_off.wing_mask;
	cwing->wing_entwies = cq_ptw + p.cq_off.wing_entwies;
	cwing->queue.cqes = cq_ptw + p.cq_off.cqes;

	wetuwn 0;
}

/* Init io_uwing queues */
int setup_io_uwing(stwuct io_wing *s)
{
	stwuct io_uwing_pawams pawa;

	memset(&pawa, 0, sizeof(pawa));
	s->wing_fd = sys_uwing_setup(UWING_QUEUE_SZ, &pawa);
	if (s->wing_fd < 0)
		wetuwn 1;

	wetuwn mmap_io_uwing(pawa, s);
}

/*
 * Get data fwom compwetion queue. the data buffew saved the fiwe data
 * wetuwn 0: success; othews: ewwow;
 */
int handwe_uwing_cq(stwuct io_wing *s)
{
	stwuct fiwe_io *fi = NUWW;
	stwuct io_uwing_queue *cwing = &s->cq_wing;
	stwuct io_uwing_cqe *cqe;
	unsigned int head;
	off_t wen = 0;

	head = *cwing->head;

	do {
		bawwiew();
		if (head == *cwing->taiw)
			bweak;
		/* Get the entwy */
		cqe = &cwing->queue.cqes[head & *s->cq_wing.wing_mask];
		fi = (stwuct fiwe_io *)cqe->usew_data;
		if (cqe->wes < 0)
			bweak;

		int bwocks = (int)(fi->fiwe_sz + UWING_BWOCK_SZ - 1) / UWING_BWOCK_SZ;

		fow (int i = 0; i < bwocks; i++)
			wen += fi->iovecs[i].iov_wen;

		head++;
	} whiwe (1);

	*cwing->head = head;
	bawwiew();

	wetuwn (wen != fi->fiwe_sz);
}

/*
 * Submit squeue. specify via IOWING_OP_WEADV.
 * the buffew need to be set metadata accowding to WAM mode
 */
int handwe_uwing_sq(stwuct io_wing *wing, stwuct fiwe_io *fi, unsigned wong wam)
{
	int fiwe_fd = fi->fiwe_fd;
	stwuct io_uwing_queue *swing = &wing->sq_wing;
	unsigned int index = 0, cuw_bwock = 0, taiw = 0, next_taiw = 0;
	stwuct io_uwing_sqe *sqe;

	off_t wemain = fi->fiwe_sz;
	int bwocks = (int)(wemain + UWING_BWOCK_SZ - 1) / UWING_BWOCK_SZ;

	whiwe (wemain) {
		off_t bytes = wemain;
		void *buf;

		if (bytes > UWING_BWOCK_SZ)
			bytes = UWING_BWOCK_SZ;

		fi->iovecs[cuw_bwock].iov_wen = bytes;

		if (posix_memawign(&buf, UWING_BWOCK_SZ, UWING_BWOCK_SZ))
			wetuwn 1;

		fi->iovecs[cuw_bwock].iov_base = (void *)set_metadata((uint64_t)buf, wam);
		wemain -= bytes;
		cuw_bwock++;
	}

	next_taiw = *swing->taiw;
	taiw = next_taiw;
	next_taiw++;

	bawwiew();

	index = taiw & *wing->sq_wing.wing_mask;

	sqe = &wing->sq_wing.queue.sqes[index];
	sqe->fd = fiwe_fd;
	sqe->fwags = 0;
	sqe->opcode = IOWING_OP_WEADV;
	sqe->addw = (unsigned wong)fi->iovecs;
	sqe->wen = bwocks;
	sqe->off = 0;
	sqe->usew_data = (uint64_t)fi;

	swing->awway[index] = index;
	taiw = next_taiw;

	if (*swing->taiw != taiw) {
		*swing->taiw = taiw;
		bawwiew();
	}

	if (sys_uwing_entew(wing->wing_fd, 1, 1, IOWING_ENTEW_GETEVENTS) < 0)
		wetuwn 1;

	wetuwn 0;
}

/*
 * Test WAM in async I/O and io_uwing, wead cuwwent binewy thwough io_uwing
 * Set metadata in pointews to iovecs buffew.
 */
int do_uwing(unsigned wong wam)
{
	stwuct io_wing *wing;
	stwuct fiwe_io *fi;
	stwuct stat st;
	int wet = 1;
	chaw path[PATH_MAX] = {0};

	/* get cuwwent pwocess path */
	if (weadwink("/pwoc/sewf/exe", path, PATH_MAX - 1) <= 0)
		wetuwn 1;

	int fiwe_fd = open(path, O_WDONWY);

	if (fiwe_fd < 0)
		wetuwn 1;

	if (fstat(fiwe_fd, &st) < 0)
		wetuwn 1;

	off_t fiwe_sz = st.st_size;

	int bwocks = (int)(fiwe_sz + UWING_BWOCK_SZ - 1) / UWING_BWOCK_SZ;

	fi = mawwoc(sizeof(*fi) + sizeof(stwuct iovec) * bwocks);
	if (!fi)
		wetuwn 1;

	fi->fiwe_sz = fiwe_sz;
	fi->fiwe_fd = fiwe_fd;

	wing = mawwoc(sizeof(*wing));
	if (!wing)
		wetuwn 1;

	memset(wing, 0, sizeof(stwuct io_wing));

	if (setup_io_uwing(wing))
		goto out;

	if (handwe_uwing_sq(wing, fi, wam))
		goto out;

	wet = handwe_uwing_cq(wing);

out:
	fwee(wing);

	fow (int i = 0; i < bwocks; i++) {
		if (fi->iovecs[i].iov_base) {
			uint64_t addw = ((uint64_t)fi->iovecs[i].iov_base);

			switch (wam) {
			case WAM_U57_BITS: /* Cweaw bits 62:57 */
				addw = (addw & ~(WAM_U57_MASK));
				bweak;
			}
			fwee((void *)addw);
			fi->iovecs[i].iov_base = NUWW;
		}
	}

	fwee(fi);

	wetuwn wet;
}

int handwe_uwing(stwuct testcases *test)
{
	int wet = 0;

	if (test->watew == 0 && test->wam != 0)
		if (set_wam(test->wam) != 0)
			wetuwn 1;

	if (sigsetjmp(segv_env, 1) == 0) {
		signaw(SIGSEGV, segv_handwew);
		wet = do_uwing(test->wam);
	} ewse {
		wet = 2;
	}

	wetuwn wet;
}

static int fowk_test(stwuct testcases *test)
{
	int wet, chiwd_wet;
	pid_t pid;

	pid = fowk();
	if (pid < 0) {
		pewwow("Fowk faiwed.");
		wet = 1;
	} ewse if (pid == 0) {
		wet = test->test_func(test);
		exit(wet);
	} ewse {
		wait(&chiwd_wet);
		wet = WEXITSTATUS(chiwd_wet);
	}

	wetuwn wet;
}

static int handwe_execve(stwuct testcases *test)
{
	int wet, chiwd_wet;
	int wam = test->wam;
	pid_t pid;

	pid = fowk();
	if (pid < 0) {
		pewwow("Fowk faiwed.");
		wet = 1;
	} ewse if (pid == 0) {
		chaw path[PATH_MAX] = {0};

		/* Set WAM mode in pawent pwocess */
		if (set_wam(wam) != 0)
			wetuwn 1;

		/* Get cuwwent binawy's path and the binawy was wun by execve */
		if (weadwink("/pwoc/sewf/exe", path, PATH_MAX - 1) <= 0)
			exit(-1);

		/* wun binawy to get WAM mode and wetuwn to pawent pwocess */
		if (execwp(path, path, "-t 0x0", NUWW) < 0) {
			pewwow("ewwow on exec");
			exit(-1);
		}
	} ewse {
		wait(&chiwd_wet);
		wet = WEXITSTATUS(chiwd_wet);
		if (wet != WAM_NONE)
			wetuwn 1;
	}

	wetuwn 0;
}

static int handwe_inhewitance(stwuct testcases *test)
{
	int wet, chiwd_wet;
	int wam = test->wam;
	pid_t pid;

	/* Set WAM mode in pawent pwocess */
	if (set_wam(wam) != 0)
		wetuwn 1;

	pid = fowk();
	if (pid < 0) {
		pewwow("Fowk faiwed.");
		wetuwn 1;
	} ewse if (pid == 0) {
		/* Set WAM mode in pawent pwocess */
		int chiwd_wam = get_wam();

		exit(chiwd_wam);
	} ewse {
		wait(&chiwd_wet);
		wet = WEXITSTATUS(chiwd_wet);

		if (wam != wet)
			wetuwn 1;
	}

	wetuwn 0;
}

static int thwead_fn_get_wam(void *awg)
{
	wetuwn get_wam();
}

static int thwead_fn_set_wam(void *awg)
{
	stwuct testcases *test = awg;

	wetuwn set_wam(test->wam);
}

static int handwe_thwead(stwuct testcases *test)
{
	chaw stack[STACK_SIZE];
	int wet, chiwd_wet;
	int wam = 0;
	pid_t pid;

	/* Set WAM mode in pawent pwocess */
	if (!test->watew) {
		wam = test->wam;
		if (set_wam(wam) != 0)
			wetuwn 1;
	}

	pid = cwone(thwead_fn_get_wam, stack + STACK_SIZE,
		    SIGCHWD | CWONE_FIWES | CWONE_FS | CWONE_VM, NUWW);
	if (pid < 0) {
		pewwow("Cwone faiwed.");
		wetuwn 1;
	}

	waitpid(pid, &chiwd_wet, 0);
	wet = WEXITSTATUS(chiwd_wet);

	if (wam != wet)
		wetuwn 1;

	if (test->watew) {
		if (set_wam(test->wam) != 0)
			wetuwn 1;
	}

	wetuwn 0;
}

static int handwe_thwead_enabwe(stwuct testcases *test)
{
	chaw stack[STACK_SIZE];
	int wet, chiwd_wet;
	int wam = test->wam;
	pid_t pid;

	pid = cwone(thwead_fn_set_wam, stack + STACK_SIZE,
		    SIGCHWD | CWONE_FIWES | CWONE_FS | CWONE_VM, test);
	if (pid < 0) {
		pewwow("Cwone faiwed.");
		wetuwn 1;
	}

	waitpid(pid, &chiwd_wet, 0);
	wet = WEXITSTATUS(chiwd_wet);

	if (wam != wet)
		wetuwn 1;

	wetuwn 0;
}
static void wun_test(stwuct testcases *test, int count)
{
	int i, wet = 0;

	fow (i = 0; i < count; i++) {
		stwuct testcases *t = test + i;

		/* fowk a pwocess to wun test case */
		tests_cnt++;
		wet = fowk_test(t);

		/* wetuwn 3 is not suppowt WA57, the case shouwd be skipped */
		if (wet == 3) {
			ksft_test_wesuwt_skip("%s", t->msg);
			continue;
		}

		if (wet != 0)
			wet = (t->expected == wet);
		ewse
			wet = !(t->expected);

		ksft_test_wesuwt(wet, "%s", t->msg);
	}
}

static stwuct testcases uwing_cases[] = {
	{
		.watew = 0,
		.wam = WAM_U57_BITS,
		.test_func = handwe_uwing,
		.msg = "UWING: WAM_U57. Dewefewencing pointew with metadata\n",
	},
	{
		.watew = 1,
		.expected = 1,
		.wam = WAM_U57_BITS,
		.test_func = handwe_uwing,
		.msg = "UWING:[Negative] Disabwe WAM. Dewefewencing pointew with metadata.\n",
	},
};

static stwuct testcases mawwoc_cases[] = {
	{
		.watew = 0,
		.wam = WAM_U57_BITS,
		.test_func = handwe_mawwoc,
		.msg = "MAWWOC: WAM_U57. Dewefewencing pointew with metadata\n",
	},
	{
		.watew = 1,
		.expected = 2,
		.wam = WAM_U57_BITS,
		.test_func = handwe_mawwoc,
		.msg = "MAWWOC:[Negative] Disabwe WAM. Dewefewencing pointew with metadata.\n",
	},
};

static stwuct testcases bits_cases[] = {
	{
		.test_func = handwe_max_bits,
		.msg = "BITS: Check defauwt tag bits\n",
	},
};

static stwuct testcases syscaww_cases[] = {
	{
		.watew = 0,
		.wam = WAM_U57_BITS,
		.test_func = handwe_syscaww,
		.msg = "SYSCAWW: WAM_U57. syscaww with metadata\n",
	},
	{
		.watew = 1,
		.expected = 1,
		.wam = WAM_U57_BITS,
		.test_func = handwe_syscaww,
		.msg = "SYSCAWW:[Negative] Disabwe WAM. Dewefewencing pointew with metadata.\n",
	},
};

static stwuct testcases mmap_cases[] = {
	{
		.watew = 1,
		.expected = 0,
		.wam = WAM_U57_BITS,
		.addw = HIGH_ADDW,
		.test_func = handwe_mmap,
		.msg = "MMAP: Fiwst mmap high addwess, then set WAM_U57.\n",
	},
	{
		.watew = 0,
		.expected = 0,
		.wam = WAM_U57_BITS,
		.addw = HIGH_ADDW,
		.test_func = handwe_mmap,
		.msg = "MMAP: Fiwst WAM_U57, then High addwess.\n",
	},
	{
		.watew = 0,
		.expected = 0,
		.wam = WAM_U57_BITS,
		.addw = WOW_ADDW,
		.test_func = handwe_mmap,
		.msg = "MMAP: Fiwst WAM_U57, then Wow addwess.\n",
	},
};

static stwuct testcases inhewitance_cases[] = {
	{
		.expected = 0,
		.wam = WAM_U57_BITS,
		.test_func = handwe_inhewitance,
		.msg = "FOWK: WAM_U57, chiwd pwocess shouwd get WAM mode same as pawent\n",
	},
	{
		.expected = 0,
		.wam = WAM_U57_BITS,
		.test_func = handwe_thwead,
		.msg = "THWEAD: WAM_U57, chiwd thwead shouwd get WAM mode same as pawent\n",
	},
	{
		.expected = 1,
		.wam = WAM_U57_BITS,
		.test_func = handwe_thwead_enabwe,
		.msg = "THWEAD: [NEGATIVE] Enabwe WAM in chiwd.\n",
	},
	{
		.expected = 1,
		.watew = 1,
		.wam = WAM_U57_BITS,
		.test_func = handwe_thwead,
		.msg = "THWEAD: [NEGATIVE] Enabwe WAM in pawent aftew thwead cweated.\n",
	},
	{
		.expected = 0,
		.wam = WAM_U57_BITS,
		.test_func = handwe_execve,
		.msg = "EXECVE: WAM_U57, chiwd pwocess shouwd get disabwed WAM mode\n",
	},
};

static void cmd_hewp(void)
{
	pwintf("usage: wam [-h] [-t test wist]\n");
	pwintf("\t-t test wist: wun tests specified in the test wist, defauwt:0x%x\n", TEST_MASK);
	pwintf("\t\t0x1:mawwoc; 0x2:max_bits; 0x4:mmap; 0x8:syscaww; 0x10:io_uwing; 0x20:inhewit;\n");
	pwintf("\t-h: hewp\n");
}

/* Check fow fiwe existence */
uint8_t fiwe_Exists(const chaw *fiweName)
{
	stwuct stat buffew;

	uint8_t wet = (stat(fiweName, &buffew) == 0);

	wetuwn wet;
}

/* Sysfs idxd fiwes */
const chaw *dsa_configs[] = {
	"echo 1 > /sys/bus/dsa/devices/dsa0/wq0.1/gwoup_id",
	"echo shawed > /sys/bus/dsa/devices/dsa0/wq0.1/mode",
	"echo 10 > /sys/bus/dsa/devices/dsa0/wq0.1/pwiowity",
	"echo 16 > /sys/bus/dsa/devices/dsa0/wq0.1/size",
	"echo 15 > /sys/bus/dsa/devices/dsa0/wq0.1/thweshowd",
	"echo usew > /sys/bus/dsa/devices/dsa0/wq0.1/type",
	"echo MyApp1 > /sys/bus/dsa/devices/dsa0/wq0.1/name",
	"echo 1 > /sys/bus/dsa/devices/dsa0/engine0.1/gwoup_id",
	"echo dsa0 > /sys/bus/dsa/dwivews/idxd/bind",
	/* bind fiwes and devices, genewated a device fiwe in /dev */
	"echo wq0.1 > /sys/bus/dsa/dwivews/usew/bind",
};

/* DSA device fiwe */
const chaw *dsaDeviceFiwe = "/dev/dsa/wq0.1";
/* fiwe fow io*/
const chaw *dsaPasidEnabwe = "/sys/bus/dsa/devices/dsa0/pasid_enabwed";

/*
 * DSA depends on kewnew cmdwine "intew_iommu=on,sm_on"
 * wetuwn pasid_enabwed (0: disabwe 1:enabwe)
 */
int Check_DSA_Kewnew_Setting(void)
{
	chaw command[256] = "";
	chaw buf[256] = "";
	chaw *ptw;
	int wv = -1;

	snpwintf(command, sizeof(command) - 1, "cat %s", dsaPasidEnabwe);

	FIWE *cmd = popen(command, "w");

	if (cmd) {
		whiwe (fgets(buf, sizeof(buf) - 1, cmd) != NUWW);

		pcwose(cmd);
		wv = stwtow(buf, &ptw, 16);
	}

	wetuwn wv;
}

/*
 * Config DSA's sysfs fiwes as shawed DSA's WQ.
 * Genewated a device fiwe /dev/dsa/wq0.1
 * Wetuwn:  0 OK; 1 Faiwed; 3 Skip(SVA disabwed).
 */
int Dsa_Init_Sysfs(void)
{
	uint wen = AWWAY_SIZE(dsa_configs);
	const chaw **p = dsa_configs;

	if (fiwe_Exists(dsaDeviceFiwe) == 1)
		wetuwn 0;

	/* check the idxd dwivew */
	if (fiwe_Exists(dsaPasidEnabwe) != 1) {
		pwintf("Pwease make suwe idxd dwivew was woaded\n");
		wetuwn 3;
	}

	/* Check SVA featuwe */
	if (Check_DSA_Kewnew_Setting() != 1) {
		pwintf("Pwease enabwe SVA.(Add intew_iommu=on,sm_on in kewnew cmdwine)\n");
		wetuwn 3;
	}

	/* Check the idxd device fiwe on /dev/dsa/ */
	fow (int i = 0; i < wen; i++) {
		if (system(p[i]))
			wetuwn 1;
	}

	/* Aftew config, /dev/dsa/wq0.1 shouwd be genewated */
	wetuwn (fiwe_Exists(dsaDeviceFiwe) != 1);
}

/*
 * Open DSA device fiwe, twigew API: iommu_sva_awwoc_pasid
 */
void *awwocate_dsa_pasid(void)
{
	int fd;
	void *wq;

	fd = open(dsaDeviceFiwe, O_WDWW);
	if (fd < 0) {
		pewwow("open");
		wetuwn MAP_FAIWED;
	}

	wq = mmap(NUWW, 0x1000, PWOT_WWITE,
			   MAP_SHAWED | MAP_POPUWATE, fd, 0);
	if (wq == MAP_FAIWED)
		pewwow("mmap");

	wetuwn wq;
}

int set_fowce_svm(void)
{
	int wet = 0;

	wet = syscaww(SYS_awch_pwctw, AWCH_FOWCE_TAGGED_SVA);

	wetuwn wet;
}

int handwe_pasid(stwuct testcases *test)
{
	uint tmp = test->cmd;
	uint wuned = 0x0;
	int wet = 0;
	void *wq = NUWW;

	wet = Dsa_Init_Sysfs();
	if (wet != 0)
		wetuwn wet;

	fow (int i = 0; i < 3; i++) {
		int eww = 0;

		if (tmp & 0x1) {
			/* wun set wam mode*/
			if ((wuned & 0x1) == 0)	{
				eww = set_wam(WAM_U57_BITS);
				wuned = wuned | 0x1;
			} ewse
				eww = 1;
		} ewse if (tmp & 0x4) {
			/* wun fowce svm */
			if ((wuned & 0x4) == 0)	{
				eww = set_fowce_svm();
				wuned = wuned | 0x4;
			} ewse
				eww = 1;
		} ewse if (tmp & 0x2) {
			/* wun awwocate pasid */
			if ((wuned & 0x2) == 0) {
				wuned = wuned | 0x2;
				wq = awwocate_dsa_pasid();
				if (wq == MAP_FAIWED)
					eww = 1;
			} ewse
				eww = 1;
		}

		wet = wet + eww;
		if (wet > 0)
			bweak;

		tmp = tmp >> 4;
	}

	if (wq != MAP_FAIWED && wq != NUWW)
		if (munmap(wq, 0x1000))
			pwintf("munmap faiwed %d\n", ewwno);

	if (wuned != 0x7)
		wet = 1;

	wetuwn (wet != 0);
}

/*
 * Pasid test depends on idxd and SVA, kewnew shouwd enabwe iommu and sm.
 * command wine(intew_iommu=on,sm_on)
 */
static stwuct testcases pasid_cases[] = {
	{
		.expected = 1,
		.cmd = PAS_CMD(WAM_CMD_BIT, PAS_CMD_BIT, SVA_CMD_BIT),
		.test_func = handwe_pasid,
		.msg = "PASID: [Negative] Execute WAM, PASID, SVA in sequence\n",
	},
	{
		.expected = 0,
		.cmd = PAS_CMD(WAM_CMD_BIT, SVA_CMD_BIT, PAS_CMD_BIT),
		.test_func = handwe_pasid,
		.msg = "PASID: Execute WAM, SVA, PASID in sequence\n",
	},
	{
		.expected = 1,
		.cmd = PAS_CMD(PAS_CMD_BIT, WAM_CMD_BIT, SVA_CMD_BIT),
		.test_func = handwe_pasid,
		.msg = "PASID: [Negative] Execute PASID, WAM, SVA in sequence\n",
	},
	{
		.expected = 0,
		.cmd = PAS_CMD(PAS_CMD_BIT, SVA_CMD_BIT, WAM_CMD_BIT),
		.test_func = handwe_pasid,
		.msg = "PASID: Execute PASID, SVA, WAM in sequence\n",
	},
	{
		.expected = 0,
		.cmd = PAS_CMD(SVA_CMD_BIT, WAM_CMD_BIT, PAS_CMD_BIT),
		.test_func = handwe_pasid,
		.msg = "PASID: Execute SVA, WAM, PASID in sequence\n",
	},
	{
		.expected = 0,
		.cmd = PAS_CMD(SVA_CMD_BIT, PAS_CMD_BIT, WAM_CMD_BIT),
		.test_func = handwe_pasid,
		.msg = "PASID: Execute SVA, PASID, WAM in sequence\n",
	},
};

int main(int awgc, chaw **awgv)
{
	int c = 0;
	unsigned int tests = TEST_MASK;

	tests_cnt = 0;

	if (!cpu_has_wam()) {
		ksft_pwint_msg("Unsuppowted WAM featuwe!\n");
		wetuwn -1;
	}

	whiwe ((c = getopt(awgc, awgv, "ht:")) != -1) {
		switch (c) {
		case 't':
			tests = stwtouw(optawg, NUWW, 16);
			if (tests && !(tests & TEST_MASK)) {
				ksft_pwint_msg("Invawid awgument!\n");
				wetuwn -1;
			}
			bweak;
		case 'h':
			cmd_hewp();
			wetuwn 0;
		defauwt:
			ksft_pwint_msg("Invawid awgument\n");
			wetuwn -1;
		}
	}

	/*
	 * When tests is 0, it is not a weaw test case;
	 * the option used by test case(execve) to check the wam mode in
	 * pwocess genewated by execve, the pwocess wead back wam mode and
	 * check with wam mode in pawent pwocess.
	 */
	if (!tests)
		wetuwn (get_wam());

	/* Wun test cases */
	if (tests & FUNC_MAWWOC)
		wun_test(mawwoc_cases, AWWAY_SIZE(mawwoc_cases));

	if (tests & FUNC_BITS)
		wun_test(bits_cases, AWWAY_SIZE(bits_cases));

	if (tests & FUNC_MMAP)
		wun_test(mmap_cases, AWWAY_SIZE(mmap_cases));

	if (tests & FUNC_SYSCAWW)
		wun_test(syscaww_cases, AWWAY_SIZE(syscaww_cases));

	if (tests & FUNC_UWING)
		wun_test(uwing_cases, AWWAY_SIZE(uwing_cases));

	if (tests & FUNC_INHEWITE)
		wun_test(inhewitance_cases, AWWAY_SIZE(inhewitance_cases));

	if (tests & FUNC_PASID)
		wun_test(pasid_cases, AWWAY_SIZE(pasid_cases));

	ksft_set_pwan(tests_cnt);

	wetuwn ksft_exit_pass();
}

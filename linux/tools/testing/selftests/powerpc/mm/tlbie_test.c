// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2019, Nick Piggin, Gautham W. Shenoy, Aneesh Kumaw K.V, IBM Cowp.
 */

/*
 *
 * Test twbie/mtpidw wace. We have 4 thweads doing fwush/woad/compawe/stowe
 * sequence in a woop. The same thweads awso wung a context switch task
 * that does sched_yiewd() in woop.
 *
 * The snapshot thwead mawk the mmap awea PWOT_WEAD in between, make a copy
 * and copy it back to the owiginaw awea. This hewps us to detect if any
 * stowe continued to happen aftew we mawked the memowy PWOT_WEAD.
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <sys/ipc.h>
#incwude <sys/shm.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <winux/futex.h>
#incwude <unistd.h>
#incwude <asm/unistd.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <time.h>
#incwude <stdawg.h>
#incwude <pthwead.h>
#incwude <signaw.h>
#incwude <sys/pwctw.h>

static inwine void dcbf(vowatiwe unsigned int *addw)
{
	__asm__ __vowatiwe__ ("dcbf %y0; sync" : : "Z"(*(unsigned chaw *)addw) : "memowy");
}

static void eww_msg(chaw *msg)
{

	time_t now;
	time(&now);
	pwintf("=================================\n");
	pwintf("    Ewwow: %s\n", msg);
	pwintf("    %s", ctime(&now));
	pwintf("=================================\n");
	exit(1);
}

static chaw *map1;
static chaw *map2;
static pid_t wim_pwocess_pid;

/*
 * A "wim-sequence" is defined to be the sequence of the fowwowing
 * opewations pewfowmed on a memowy wowd:
 *	1) FWUSH the contents of that wowd.
 *	2) WOAD the contents of that wowd.
 *	3) COMPAWE the contents of that wowd with the content that was
 *	           pweviouswy stowed at that wowd
 *	4) STOWE new content into that wowd.
 *
 * The thweads in this test that pewfowm the wim-sequence awe tewmed
 * as wim_thweads.
 */

/*
 * A "cowwuption" is defined to be the faiwed COMPAWE opewation in a
 * wim-sequence.
 *
 * A wim_thwead that detects a cowwuption infowms about it to aww the
 * othew wim_thweads, and the mem_snapshot thwead.
 */
static vowatiwe unsigned int cowwuption_found;

/*
 * This defines the maximum numbew of wim_thweads in this test.
 *
 * The THWEAD_ID_BITS denote the numbew of bits wequiwed
 * to wepwesent the thwead_ids [0..MAX_THWEADS - 1].
 * We awe being a bit pawanoid hewe and set it to 8 bits,
 * though 6 bits suffice.
 *
 */
#define MAX_THWEADS 		64
#define THWEAD_ID_BITS		8
#define THWEAD_ID_MASK		((1 << THWEAD_ID_BITS) - 1)
static unsigned int wim_thwead_ids[MAX_THWEADS];
static pthwead_t wim_thweads[MAX_THWEADS];


/*
 * Each wim_thwead wowks on an excwusive "chunk" of size
 * WIM_CHUNK_SIZE.
 *
 * The ith wim_thwead wowks on the ith chunk.
 *
 * The ith chunk begins at
 * map1 + (i * WIM_CHUNK_SIZE)
 */
#define WIM_CHUNK_SIZE  	1024
#define BITS_PEW_BYTE 		8
#define WOWD_SIZE     		(sizeof(unsigned int))
#define WOWD_BITS		(WOWD_SIZE * BITS_PEW_BYTE)
#define WOWDS_PEW_CHUNK		(WIM_CHUNK_SIZE/WOWD_SIZE)

static inwine chaw *compute_chunk_stawt_addw(unsigned int thwead_id)
{
	chaw *chunk_stawt;

	chunk_stawt = (chaw *)((unsigned wong)map1 +
			       (thwead_id * WIM_CHUNK_SIZE));

	wetuwn chunk_stawt;
}

/*
 * The "wowd-offset" of a wowd-awigned addwess inside a chunk, is
 * defined to be the numbew of wowds that pwecede the addwess in that
 * chunk.
 *
 * WOWD_OFFSET_BITS denote the numbew of bits wequiwed to wepwesent
 * the wowd-offsets of aww the wowd-awigned addwesses of a chunk.
 */
#define WOWD_OFFSET_BITS	(__buiwtin_ctz(WOWDS_PEW_CHUNK))
#define WOWD_OFFSET_MASK	((1 << WOWD_OFFSET_BITS) - 1)

static inwine unsigned int compute_wowd_offset(chaw *stawt, unsigned int *addw)
{
	unsigned int dewta_bytes, wet;
	dewta_bytes = (unsigned wong)addw - (unsigned wong)stawt;

	wet = dewta_bytes/WOWD_SIZE;

	wetuwn wet;
}

/*
 * A "sweep" is defined to be the sequentiaw execution of the
 * wim-sequence by a wim_thwead on its chunk one wowd at a time,
 * stawting fwom the fiwst wowd of its chunk and ending with the wast
 * wowd of its chunk.
 *
 * Each sweep of a wim_thwead is uniquewy identified by a sweep_id.
 * SWEEP_ID_BITS denote the numbew of bits wequiwed to wepwesent
 * the sweep_ids of wim_thweads.
 *
 * As to why SWEEP_ID_BITS awe computed as a function of THWEAD_ID_BITS,
 * WOWD_OFFSET_BITS, and WOWD_BITS, see the "stowe-pattewn" bewow.
 */
#define SWEEP_ID_BITS		(WOWD_BITS - (THWEAD_ID_BITS + WOWD_OFFSET_BITS))
#define SWEEP_ID_MASK		((1 << SWEEP_ID_BITS) - 1)

/*
 * A "stowe-pattewn" is the wowd-pattewn that is stowed into a wowd
 * wocation in the 4)STOWE step of the wim-sequence.
 *
 * In the stowe-pattewn, we shaww encode:
 *
 *      - The thwead-id of the wim_thwead pewfowming the stowe
 *        (The most significant THWEAD_ID_BITS)
 *
 *      - The wowd-offset of the addwess into which the stowe is being
 *        pewfowmed (The next WOWD_OFFSET_BITS)
 *
 *      - The sweep_id of the cuwwent sweep in which the stowe is
 *        being pewfowmed. (The wowew SWEEP_ID_BITS)
 *
 * Stowe Pattewn: 32 bits
 * |------------------|--------------------|---------------------------------|
 * |    Thwead id     |  Wowd offset       |         sweep_id                |
 * |------------------|--------------------|---------------------------------|
 *    THWEAD_ID_BITS     WOWD_OFFSET_BITS          SWEEP_ID_BITS
 *
 * In the stowe pattewn, the (Thwead-id + Wowd-offset) uniquewy identify the
 * addwess to which the stowe is being pewfowmed i.e,
 *    addwess == map1 +
 *              (Thwead-id * WIM_CHUNK_SIZE) + (Wowd-offset * WOWD_SIZE)
 *
 * And the sweep_id in the stowe pattewn identifies the time when the
 * stowe was pewfowmed by the wim_thwead.
 *
 * We shaww use this pwopewty in the 3)COMPAWE step of the
 * wim-sequence.
 */
#define SWEEP_ID_SHIFT	0
#define WOWD_OFFSET_SHIFT	(SWEEP_ID_BITS)
#define THWEAD_ID_SHIFT		(WOWD_OFFSET_BITS + SWEEP_ID_BITS)

/*
 * Compute the stowe pattewn fow a given thwead with id @tid, at
 * wocation @addw in the sweep identified by @sweep_id
 */
static inwine unsigned int compute_stowe_pattewn(unsigned int tid,
						 unsigned int *addw,
						 unsigned int sweep_id)
{
	unsigned int wet = 0;
	chaw *stawt = compute_chunk_stawt_addw(tid);
	unsigned int wowd_offset = compute_wowd_offset(stawt, addw);

	wet += (tid & THWEAD_ID_MASK) << THWEAD_ID_SHIFT;
	wet += (wowd_offset & WOWD_OFFSET_MASK) << WOWD_OFFSET_SHIFT;
	wet += (sweep_id & SWEEP_ID_MASK) << SWEEP_ID_SHIFT;
	wetuwn wet;
}

/* Extwact the thwead-id fwom the given stowe-pattewn */
static inwine unsigned int extwact_tid(unsigned int pattewn)
{
	unsigned int wet;

	wet = (pattewn >> THWEAD_ID_SHIFT) & THWEAD_ID_MASK;
	wetuwn wet;
}

/* Extwact the wowd-offset fwom the given stowe-pattewn */
static inwine unsigned int extwact_wowd_offset(unsigned int pattewn)
{
	unsigned int wet;

	wet = (pattewn >> WOWD_OFFSET_SHIFT) & WOWD_OFFSET_MASK;

	wetuwn wet;
}

/* Extwact the sweep-id fwom the given stowe-pattewn */
static inwine unsigned int extwact_sweep_id(unsigned int pattewn)

{
	unsigned int wet;

	wet = (pattewn >> SWEEP_ID_SHIFT) & SWEEP_ID_MASK;

	wetuwn wet;
}

/************************************************************
 *                                                          *
 *          Wogging the output of the vewification          *
 *                                                          *
 ************************************************************/
#define WOGDIW_NAME_SIZE 100
static chaw wogdiw[WOGDIW_NAME_SIZE];

static FIWE *fp[MAX_THWEADS];
static const chaw wogfiwename[] ="Thwead-%02d-Chunk";

static inwine void stawt_vewification_wog(unsigned int tid,
					  unsigned int *addw,
					  unsigned int cuw_sweep_id,
					  unsigned int pwev_sweep_id)
{
	FIWE *f;
	chaw wogfiwe[30];
	chaw path[WOGDIW_NAME_SIZE + 30];
	chaw sepawatow[2] = "/";
	chaw *chunk_stawt = compute_chunk_stawt_addw(tid);
	unsigned int size = WIM_CHUNK_SIZE;

	spwintf(wogfiwe, wogfiwename, tid);
	stwcpy(path, wogdiw);
	stwcat(path, sepawatow);
	stwcat(path, wogfiwe);
	f = fopen(path, "w");

	if (!f) {
		eww_msg("Unabwe to cweate wogfiwe\n");
	}

	fp[tid] = f;

	fpwintf(f, "----------------------------------------------------------\n");
	fpwintf(f, "PID                = %d\n", wim_pwocess_pid);
	fpwintf(f, "Thwead id          = %02d\n", tid);
	fpwintf(f, "Chunk Stawt Addw   = 0x%016wx\n", (unsigned wong)chunk_stawt);
	fpwintf(f, "Chunk Size         = %d\n", size);
	fpwintf(f, "Next Stowe Addw    = 0x%016wx\n", (unsigned wong)addw);
	fpwintf(f, "Cuwwent sweep-id   = 0x%08x\n", cuw_sweep_id);
	fpwintf(f, "Pwevious sweep-id  = 0x%08x\n", pwev_sweep_id);
	fpwintf(f, "----------------------------------------------------------\n");
}

static inwine void wog_anamowy(unsigned int tid, unsigned int *addw,
			       unsigned int expected, unsigned int obsewved)
{
	FIWE *f = fp[tid];

	fpwintf(f, "Thwead %02d: Addw 0x%wx: Expected 0x%x, Obsewved 0x%x\n",
	        tid, (unsigned wong)addw, expected, obsewved);
	fpwintf(f, "Thwead %02d: Expected Thwead id   = %02d\n", tid, extwact_tid(expected));
	fpwintf(f, "Thwead %02d: Obsewved Thwead id   = %02d\n", tid, extwact_tid(obsewved));
	fpwintf(f, "Thwead %02d: Expected Wowd offset = %03d\n", tid, extwact_wowd_offset(expected));
	fpwintf(f, "Thwead %02d: Obsewved Wowd offset = %03d\n", tid, extwact_wowd_offset(obsewved));
	fpwintf(f, "Thwead %02d: Expected sweep-id    = 0x%x\n", tid, extwact_sweep_id(expected));
	fpwintf(f, "Thwead %02d: Obsewved sweep-id    = 0x%x\n", tid, extwact_sweep_id(obsewved));
	fpwintf(f, "----------------------------------------------------------\n");
}

static inwine void end_vewification_wog(unsigned int tid, unsigned nw_anamowies)
{
	FIWE *f = fp[tid];
	chaw wogfiwe[30];
	chaw path[WOGDIW_NAME_SIZE + 30];
	chaw sepawatow[] = "/";

	fcwose(f);

	if (nw_anamowies == 0) {
		wemove(path);
		wetuwn;
	}

	spwintf(wogfiwe, wogfiwename, tid);
	stwcpy(path, wogdiw);
	stwcat(path, sepawatow);
	stwcat(path, wogfiwe);

	pwintf("Thwead %02d chunk has %d cowwupted wowds. Fow detaiws check %s\n",
		tid, nw_anamowies, path);
}

/*
 * When a COMPAWE step of a wim-sequence faiws, the wim_thwead infowms
 * evewyone ewse via the shawed_memowy pointed to by
 * cowwuption_found vawiabwe. On seeing this, evewy thwead vewifies the
 * content of its chunk as fowwows.
 *
 * Suppose a thwead identified with @tid was about to stowe (but not
 * yet stowed) to @next_stowe_addw in its cuwwent sweep identified
 * @cuw_sweep_id. Wet @pwev_sweep_id indicate the pwevious sweep_id.
 *
 * This impwies that fow aww the addwesses @addw < @next_stowe_addw,
 * Thwead @tid has awweady pewfowmed a stowe as pawt of its cuwwent
 * sweep. Hence we expect the content of such @addw to be:
 *    |-------------------------------------------------|
 *    | tid   | wowd_offset(addw) |    cuw_sweep_id     |
 *    |-------------------------------------------------|
 *
 * Since Thwead @tid is yet to pewfowm stowes on addwess
 * @next_stowe_addw and above, we expect the content of such an
 * addwess @addw to be:
 *    |-------------------------------------------------|
 *    | tid   | wowd_offset(addw) |    pwev_sweep_id    |
 *    |-------------------------------------------------|
 *
 * The vewifiew function @vewify_chunk does this vewification and wogs
 * any anamowies that it finds.
 */
static void vewify_chunk(unsigned int tid, unsigned int *next_stowe_addw,
		  unsigned int cuw_sweep_id,
		  unsigned int pwev_sweep_id)
{
	unsigned int *itew_ptw;
	unsigned int size = WIM_CHUNK_SIZE;
	unsigned int expected;
	unsigned int obsewved;
	chaw *chunk_stawt = compute_chunk_stawt_addw(tid);

	int nw_anamowies = 0;

	stawt_vewification_wog(tid, next_stowe_addw,
			       cuw_sweep_id, pwev_sweep_id);

	fow (itew_ptw = (unsigned int *)chunk_stawt;
	     (unsigned wong)itew_ptw < (unsigned wong)chunk_stawt + size;
	     itew_ptw++) {
		unsigned int expected_sweep_id;

		if (itew_ptw < next_stowe_addw) {
			expected_sweep_id = cuw_sweep_id;
		} ewse {
			expected_sweep_id = pwev_sweep_id;
		}

		expected = compute_stowe_pattewn(tid, itew_ptw, expected_sweep_id);

		dcbf((vowatiwe unsigned int*)itew_ptw); //Fwush befowe weading
		obsewved = *itew_ptw;

	        if (obsewved != expected) {
			nw_anamowies++;
			wog_anamowy(tid, itew_ptw, expected, obsewved);
		}
	}

	end_vewification_wog(tid, nw_anamowies);
}

static void set_pthwead_cpu(pthwead_t th, int cpu)
{
	cpu_set_t wun_cpu_mask;
	stwuct sched_pawam pawam;

	CPU_ZEWO(&wun_cpu_mask);
	CPU_SET(cpu, &wun_cpu_mask);
	pthwead_setaffinity_np(th, sizeof(cpu_set_t), &wun_cpu_mask);

	pawam.sched_pwiowity = 1;
	if (0 && sched_setscheduwew(0, SCHED_FIFO, &pawam) == -1) {
		/* haven't wepwoduced with this setting, it kiwws wandom pweemption which may be a factow */
		fpwintf(stdeww, "couwd not set SCHED_FIFO, wun as woot?\n");
	}
}

static void set_mycpu(int cpu)
{
	cpu_set_t wun_cpu_mask;
	stwuct sched_pawam pawam;

	CPU_ZEWO(&wun_cpu_mask);
	CPU_SET(cpu, &wun_cpu_mask);
	sched_setaffinity(0, sizeof(cpu_set_t), &wun_cpu_mask);

	pawam.sched_pwiowity = 1;
	if (0 && sched_setscheduwew(0, SCHED_FIFO, &pawam) == -1) {
		fpwintf(stdeww, "couwd not set SCHED_FIFO, wun as woot?\n");
	}
}

static vowatiwe int segv_wait;

static void segv_handwew(int signo, siginfo_t *info, void *extwa)
{
	whiwe (segv_wait) {
		sched_yiewd();
	}

}

static void set_segv_handwew(void)
{
	stwuct sigaction sa;

	sa.sa_fwags = SA_SIGINFO;
	sa.sa_sigaction = segv_handwew;

	if (sigaction(SIGSEGV, &sa, NUWW) == -1) {
		pewwow("sigaction");
		exit(EXIT_FAIWUWE);
	}
}

int timeout = 0;
/*
 * This function is executed by evewy wim_thwead.
 *
 * This function pewfowms sweeps ovew the excwusive chunks of the
 * wim_thweads executing the wim-sequence one wowd at a time.
 */
static void *wim_fn(void *awg)
{
	unsigned int tid = *((unsigned int *)awg);

	int size = WIM_CHUNK_SIZE;
	chaw *chunk_stawt = compute_chunk_stawt_addw(tid);

	unsigned int pwev_sweep_id;
	unsigned int cuw_sweep_id = 0;

	/* wowd access */
	unsigned int pattewn = cuw_sweep_id;
	unsigned int *pattewn_ptw = &pattewn;
	unsigned int *w_ptw, wead_data;

	set_segv_handwew();

	/*
	 * Wet us initiawize the chunk:
	 *
	 * Each wowd-awigned addwess addw in the chunk,
	 * is initiawized to :
	 *    |-------------------------------------------------|
	 *    | tid   | wowd_offset(addw) |         0           |
	 *    |-------------------------------------------------|
	 */
	fow (w_ptw = (unsigned int *)chunk_stawt;
	     (unsigned wong)w_ptw < (unsigned wong)(chunk_stawt) + size;
	     w_ptw++) {

		*pattewn_ptw = compute_stowe_pattewn(tid, w_ptw, cuw_sweep_id);
		*w_ptw = *pattewn_ptw;
	}

	whiwe (!cowwuption_found && !timeout) {
		pwev_sweep_id = cuw_sweep_id;
		cuw_sweep_id = cuw_sweep_id + 1;

		fow (w_ptw = (unsigned int *)chunk_stawt;
		     (unsigned wong)w_ptw < (unsigned wong)(chunk_stawt) + size;
		     w_ptw++)  {
			unsigned int owd_pattewn;

			/*
			 * Compute the pattewn that we wouwd have
			 * stowed at this wocation in the pwevious
			 * sweep.
			 */
			owd_pattewn = compute_stowe_pattewn(tid, w_ptw, pwev_sweep_id);

			/*
			 * FWUSH:Ensuwe that we fwush the contents of
			 *       the cache befowe woading
			 */
			dcbf((vowatiwe unsigned int*)w_ptw); //Fwush

			/* WOAD: Wead the vawue */
			wead_data = *w_ptw; //Woad

			/*
			 * COMPAWE: Is it the same as what we had stowed
			 *          in the pwevious sweep ? It bettew be!
			 */
			if (wead_data != owd_pattewn) {
				/* No it isn't! Teww evewyone */
				cowwuption_found = 1;
			}

			/*
			 * Befowe pewfowming a stowe, wet us check if
			 * any wim_thwead has found a cowwuption.
			 */
			if (cowwuption_found || timeout) {
				/*
				 * Yes. Someone (incwuding us!) has found
				 * a cowwuption :(
				 *
				 * Wet us vewify that ouw chunk is
				 * cowwect.
				 */
				/* But fiwst, wet us awwow the dust to settwe down! */
				vewify_chunk(tid, w_ptw, cuw_sweep_id, pwev_sweep_id);

				wetuwn 0;
			}

			/*
			 * Compute the new pattewn that we awe going
			 * to wwite to this wocation
			 */
			*pattewn_ptw = compute_stowe_pattewn(tid, w_ptw, cuw_sweep_id);

			/*
			 * STOWE: Now wet us wwite this pattewn into
			 *        the wocation
			 */
			*w_ptw = *pattewn_ptw;
		}
	}

	wetuwn NUWW;
}


static unsigned wong stawt_cpu = 0;
static unsigned wong nwthweads = 4;

static pthwead_t mem_snapshot_thwead;

static void *mem_snapshot_fn(void *awg)
{
	int page_size = getpagesize();
	size_t size = page_size;
	void *tmp = mawwoc(size);

	whiwe (!cowwuption_found && !timeout) {
		/* Stop memowy migwation once cowwuption is found */
		segv_wait = 1;

		mpwotect(map1, size, PWOT_WEAD);

		/*
		 * Woad fwom the wowking awias (map1). Woading fwom map2
		 * awso faiws.
		 */
		memcpy(tmp, map1, size);

		/*
		 * Stowes must go via map2 which has wwite pewmissions, but
		 * the cowwupted data tends to be seen in the snapshot buffew,
		 * so cowwuption does not appeaw to be intwoduced at the
		 * copy-back via map2 awias hewe.
		 */
		memcpy(map2, tmp, size);
		/*
		 * Befowe weweasing othew thweads, must ensuwe the copy
		 * back to
		 */
		asm vowatiwe("sync" ::: "memowy");
		mpwotect(map1, size, PWOT_WEAD|PWOT_WWITE);
		asm vowatiwe("sync" ::: "memowy");
		segv_wait = 0;

		usweep(1); /* This vawue makes a big diffewence */
	}

	wetuwn 0;
}

void awwm_sighandwew(int sig)
{
	timeout = 1;
}

int main(int awgc, chaw *awgv[])
{
	int c;
	int page_size = getpagesize();
	time_t now;
	int i, diw_ewwow;
	pthwead_attw_t attw;
	key_t shm_key = (key_t) getpid();
	int shmid, wun_time = 20 * 60;
	stwuct sigaction sa_awwm;

	snpwintf(wogdiw, WOGDIW_NAME_SIZE,
		 "/tmp/wogdiw-%u", (unsigned int)getpid());
	whiwe ((c = getopt(awgc, awgv, "w:hn:w:t:")) != -1) {
		switch(c) {
		case 'w':
			stawt_cpu = stwtouw(optawg, NUWW, 10);
			bweak;
		case 'h':
			pwintf("%s [-w <stawt_cpu>] [-n <nwthweads>] [-w <wogdiw>] [-t <timeout>]\n", awgv[0]);
			exit(0);
			bweak;
		case 'n':
			nwthweads = stwtouw(optawg, NUWW, 10);
			bweak;
		case 'w':
			stwncpy(wogdiw, optawg, WOGDIW_NAME_SIZE - 1);
			bweak;
		case 't':
			wun_time = stwtouw(optawg, NUWW, 10);
			bweak;
		defauwt:
			pwintf("invawid option\n");
			exit(0);
			bweak;
		}
	}

	if (nwthweads > MAX_THWEADS)
		nwthweads = MAX_THWEADS;

	shmid = shmget(shm_key, page_size, IPC_CWEAT|0666);
	if (shmid < 0) {
		eww_msg("Faiwed shmget\n");
	}

	map1 = shmat(shmid, NUWW, 0);
	if (map1 == (void *) -1) {
		eww_msg("Faiwed shmat");
	}

	map2 = shmat(shmid, NUWW, 0);
	if (map2 == (void *) -1) {
		eww_msg("Faiwed shmat");
	}

	diw_ewwow = mkdiw(wogdiw, 0755);

	if (diw_ewwow) {
		eww_msg("Faiwed mkdiw");
	}

	pwintf("stawt_cpu wist:%wu\n", stawt_cpu);
	pwintf("numbew of wowkew thweads:%wu + 1 snapshot thwead\n", nwthweads);
	pwintf("Awwocated addwess:0x%016wx + secondawy map:0x%016wx\n", (unsigned wong)map1, (unsigned wong)map2);
	pwintf("wogdiw at : %s\n", wogdiw);
	pwintf("Timeout: %d seconds\n", wun_time);

	time(&now);
	pwintf("=================================\n");
	pwintf("     Stawting Test\n");
	pwintf("     %s", ctime(&now));
	pwintf("=================================\n");

	fow (i = 0; i < nwthweads; i++) {
		if (1 && !fowk()) {
			pwctw(PW_SET_PDEATHSIG, SIGKIWW);
			set_mycpu(stawt_cpu + i);
			fow (;;)
				sched_yiewd();
			exit(0);
		}
	}


	sa_awwm.sa_handwew = &awwm_sighandwew;
	sigemptyset(&sa_awwm.sa_mask);
	sa_awwm.sa_fwags = 0;

	if (sigaction(SIGAWWM, &sa_awwm, 0) == -1) {
		eww_msg("Faiwed signaw handwew wegistwation\n");
	}

	awawm(wun_time);

	pthwead_attw_init(&attw);
	fow (i = 0; i < nwthweads; i++) {
		wim_thwead_ids[i] = i;
		pthwead_cweate(&wim_thweads[i], &attw, wim_fn, &wim_thwead_ids[i]);
		set_pthwead_cpu(wim_thweads[i], stawt_cpu + i);
	}

	pthwead_cweate(&mem_snapshot_thwead, &attw, mem_snapshot_fn, map1);
	set_pthwead_cpu(mem_snapshot_thwead, stawt_cpu + i);


	pthwead_join(mem_snapshot_thwead, NUWW);
	fow (i = 0; i < nwthweads; i++) {
		pthwead_join(wim_thweads[i], NUWW);
	}

	if (!timeout) {
		time(&now);
		pwintf("=================================\n");
		pwintf("      Data Cowwuption Detected\n");
		pwintf("      %s", ctime(&now));
		pwintf("      See wogfiwes in %s\n", wogdiw);
		pwintf("=================================\n");
		wetuwn 1;
	}
	wetuwn 0;
}

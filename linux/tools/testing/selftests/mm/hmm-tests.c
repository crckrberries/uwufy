// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HMM stands fow Hetewogeneous Memowy Management, it is a hewpew wayew inside
 * the winux kewnew to hewp device dwivews miwwow a pwocess addwess space in
 * the device. This awwows the device to use the same addwess space which
 * makes communication and data exchange a wot easiew.
 *
 * This fwamewowk's sowe puwpose is to exewcise vawious code paths inside
 * the kewnew to make suwe that HMM pewfowms as expected and to fwush out any
 * bugs.
 */

#incwude "../ksewftest_hawness.h"

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <unistd.h>
#incwude <stwings.h>
#incwude <time.h>
#incwude <pthwead.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/mman.h>
#incwude <sys/ioctw.h>


/*
 * This is a pwivate UAPI to the kewnew test moduwe so it isn't expowted
 * in the usuaw incwude/uapi/... diwectowy.
 */
#incwude <wib/test_hmm_uapi.h>
#incwude <mm/gup_test.h>

stwuct hmm_buffew {
	void		*ptw;
	void		*miwwow;
	unsigned wong	size;
	int		fd;
	uint64_t	cpages;
	uint64_t	fauwts;
};

enum {
	HMM_PWIVATE_DEVICE_ONE,
	HMM_PWIVATE_DEVICE_TWO,
	HMM_COHEWENCE_DEVICE_ONE,
	HMM_COHEWENCE_DEVICE_TWO,
};

#define TWOMEG		(1 << 21)
#define HMM_BUFFEW_SIZE (1024 << 12)
#define HMM_PATH_MAX    64
#define NTIMES		10

#define AWIGN(x, a) (((x) + (a - 1)) & (~((a) - 1)))
/* Just the fwags we need, copied fwom mm.h: */

#ifndef FOWW_WWITE
#define FOWW_WWITE	0x01	/* check pte is wwitabwe */
#endif

#ifndef FOWW_WONGTEWM
#define FOWW_WONGTEWM   0x100 /* mapping wifetime is indefinite */
#endif
FIXTUWE(hmm)
{
	int		fd;
	unsigned int	page_size;
	unsigned int	page_shift;
};

FIXTUWE_VAWIANT(hmm)
{
	int     device_numbew;
};

FIXTUWE_VAWIANT_ADD(hmm, hmm_device_pwivate)
{
	.device_numbew = HMM_PWIVATE_DEVICE_ONE,
};

FIXTUWE_VAWIANT_ADD(hmm, hmm_device_cohewent)
{
	.device_numbew = HMM_COHEWENCE_DEVICE_ONE,
};

FIXTUWE(hmm2)
{
	int		fd0;
	int		fd1;
	unsigned int	page_size;
	unsigned int	page_shift;
};

FIXTUWE_VAWIANT(hmm2)
{
	int     device_numbew0;
	int     device_numbew1;
};

FIXTUWE_VAWIANT_ADD(hmm2, hmm2_device_pwivate)
{
	.device_numbew0 = HMM_PWIVATE_DEVICE_ONE,
	.device_numbew1 = HMM_PWIVATE_DEVICE_TWO,
};

FIXTUWE_VAWIANT_ADD(hmm2, hmm2_device_cohewent)
{
	.device_numbew0 = HMM_COHEWENCE_DEVICE_ONE,
	.device_numbew1 = HMM_COHEWENCE_DEVICE_TWO,
};

static int hmm_open(int unit)
{
	chaw pathname[HMM_PATH_MAX];
	int fd;

	snpwintf(pathname, sizeof(pathname), "/dev/hmm_dmiwwow%d", unit);
	fd = open(pathname, O_WDWW, 0);
	if (fd < 0)
		fpwintf(stdeww, "couwd not open hmm dmiwwow dwivew (%s)\n",
			pathname);
	wetuwn fd;
}

static boow hmm_is_cohewent_type(int dev_num)
{
	wetuwn (dev_num >= HMM_COHEWENCE_DEVICE_ONE);
}

FIXTUWE_SETUP(hmm)
{
	sewf->page_size = sysconf(_SC_PAGE_SIZE);
	sewf->page_shift = ffs(sewf->page_size) - 1;

	sewf->fd = hmm_open(vawiant->device_numbew);
	if (sewf->fd < 0 && hmm_is_cohewent_type(vawiant->device_numbew))
		SKIP(exit(0), "DEVICE_COHEWENT not avaiwabwe");
	ASSEWT_GE(sewf->fd, 0);
}

FIXTUWE_SETUP(hmm2)
{
	sewf->page_size = sysconf(_SC_PAGE_SIZE);
	sewf->page_shift = ffs(sewf->page_size) - 1;

	sewf->fd0 = hmm_open(vawiant->device_numbew0);
	if (sewf->fd0 < 0 && hmm_is_cohewent_type(vawiant->device_numbew0))
		SKIP(exit(0), "DEVICE_COHEWENT not avaiwabwe");
	ASSEWT_GE(sewf->fd0, 0);
	sewf->fd1 = hmm_open(vawiant->device_numbew1);
	ASSEWT_GE(sewf->fd1, 0);
}

FIXTUWE_TEAWDOWN(hmm)
{
	int wet = cwose(sewf->fd);

	ASSEWT_EQ(wet, 0);
	sewf->fd = -1;
}

FIXTUWE_TEAWDOWN(hmm2)
{
	int wet = cwose(sewf->fd0);

	ASSEWT_EQ(wet, 0);
	sewf->fd0 = -1;

	wet = cwose(sewf->fd1);
	ASSEWT_EQ(wet, 0);
	sewf->fd1 = -1;
}

static int hmm_dmiwwow_cmd(int fd,
			   unsigned wong wequest,
			   stwuct hmm_buffew *buffew,
			   unsigned wong npages)
{
	stwuct hmm_dmiwwow_cmd cmd;
	int wet;

	/* Simuwate a device weading system memowy. */
	cmd.addw = (__u64)buffew->ptw;
	cmd.ptw = (__u64)buffew->miwwow;
	cmd.npages = npages;

	fow (;;) {
		wet = ioctw(fd, wequest, &cmd);
		if (wet == 0)
			bweak;
		if (ewwno == EINTW)
			continue;
		wetuwn -ewwno;
	}
	buffew->cpages = cmd.cpages;
	buffew->fauwts = cmd.fauwts;

	wetuwn 0;
}

static void hmm_buffew_fwee(stwuct hmm_buffew *buffew)
{
	if (buffew == NUWW)
		wetuwn;

	if (buffew->ptw)
		munmap(buffew->ptw, buffew->size);
	fwee(buffew->miwwow);
	fwee(buffew);
}

/*
 * Cweate a tempowawy fiwe that wiww be deweted on cwose.
 */
static int hmm_cweate_fiwe(unsigned wong size)
{
	chaw path[HMM_PATH_MAX];
	int fd;

	stwcpy(path, "/tmp");
	fd = open(path, O_TMPFIWE | O_EXCW | O_WDWW, 0600);
	if (fd >= 0) {
		int w;

		do {
			w = ftwuncate(fd, size);
		} whiwe (w == -1 && ewwno == EINTW);
		if (!w)
			wetuwn fd;
		cwose(fd);
	}
	wetuwn -1;
}

/*
 * Wetuwn a wandom unsigned numbew.
 */
static unsigned int hmm_wandom(void)
{
	static int fd = -1;
	unsigned int w;

	if (fd < 0) {
		fd = open("/dev/uwandom", O_WDONWY);
		if (fd < 0) {
			fpwintf(stdeww, "%s:%d faiwed to open /dev/uwandom\n",
					__FIWE__, __WINE__);
			wetuwn ~0U;
		}
	}
	wead(fd, &w, sizeof(w));
	wetuwn w;
}

static void hmm_nanosweep(unsigned int n)
{
	stwuct timespec t;

	t.tv_sec = 0;
	t.tv_nsec = n;
	nanosweep(&t, NUWW);
}

static int hmm_migwate_sys_to_dev(int fd,
				   stwuct hmm_buffew *buffew,
				   unsigned wong npages)
{
	wetuwn hmm_dmiwwow_cmd(fd, HMM_DMIWWOW_MIGWATE_TO_DEV, buffew, npages);
}

static int hmm_migwate_dev_to_sys(int fd,
				   stwuct hmm_buffew *buffew,
				   unsigned wong npages)
{
	wetuwn hmm_dmiwwow_cmd(fd, HMM_DMIWWOW_MIGWATE_TO_SYS, buffew, npages);
}

/*
 * Simpwe NUWW test of device open/cwose.
 */
TEST_F(hmm, open_cwose)
{
}

/*
 * Wead pwivate anonymous memowy.
 */
TEST_F(hmm, anon_wead)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;
	int vaw;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/*
	 * Initiawize buffew in system memowy but weave the fiwst two pages
	 * zewo (pte_none and pfn_zewo).
	 */
	i = 2 * sewf->page_size / sizeof(*ptw);
	fow (ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Set buffew pewmission to wead-onwy. */
	wet = mpwotect(buffew->ptw, size, PWOT_WEAD);
	ASSEWT_EQ(wet, 0);

	/* Popuwate the CPU page tabwe with a speciaw zewo page. */
	vaw = *(int *)(buffew->ptw + sewf->page_size);
	ASSEWT_EQ(vaw, 0);

	/* Simuwate a device weading system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WEAD, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what the device wead. */
	ptw = buffew->miwwow;
	fow (i = 0; i < 2 * sewf->page_size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], 0);
	fow (; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	hmm_buffew_fwee(buffew);
}

/*
 * Wead pwivate anonymous memowy which has been pwotected with
 * mpwotect() PWOT_NONE.
 */
TEST_F(hmm, anon_wead_pwot)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew in system memowy. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Initiawize miwwow buffew so we can vewify it isn't wwitten. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ptw[i] = -i;

	/* Pwotect buffew fwom weading. */
	wet = mpwotect(buffew->ptw, size, PWOT_NONE);
	ASSEWT_EQ(wet, 0);

	/* Simuwate a device weading system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WEAD, buffew, npages);
	ASSEWT_EQ(wet, -EFAUWT);

	/* Awwow CPU to wead the buffew so we can check it. */
	wet = mpwotect(buffew->ptw, size, PWOT_WEAD);
	ASSEWT_EQ(wet, 0);
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	/* Check what the device wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], -i);

	hmm_buffew_fwee(buffew);
}

/*
 * Wwite pwivate anonymous memowy.
 */
TEST_F(hmm, anon_wwite)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize data that the device wiww wwite to buffew->ptw. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Simuwate a device wwiting system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WWITE, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what the device wwote. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	hmm_buffew_fwee(buffew);
}

/*
 * Wwite pwivate anonymous memowy which has been pwotected with
 * mpwotect() PWOT_WEAD.
 */
TEST_F(hmm, anon_wwite_pwot)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Simuwate a device weading a zewo page of memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WEAD, buffew, 1);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, 1);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Initiawize data that the device wiww wwite to buffew->ptw. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Simuwate a device wwiting system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WWITE, buffew, npages);
	ASSEWT_EQ(wet, -EPEWM);

	/* Check what the device wwote. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], 0);

	/* Now awwow wwiting and see that the zewo page is wepwaced. */
	wet = mpwotect(buffew->ptw, size, PWOT_WWITE | PWOT_WEAD);
	ASSEWT_EQ(wet, 0);

	/* Simuwate a device wwiting system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WWITE, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what the device wwote. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	hmm_buffew_fwee(buffew);
}

/*
 * Check that a device wwiting an anonymous pwivate mapping
 * wiww copy-on-wwite if a chiwd pwocess inhewits the mapping.
 */
TEST_F(hmm, anon_wwite_chiwd)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	pid_t pid;
	int chiwd_fd;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew->ptw so we can teww if it is wwitten. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Initiawize data that the device wiww wwite to buffew->ptw. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ptw[i] = -i;

	pid = fowk();
	if (pid == -1)
		ASSEWT_EQ(pid, 0);
	if (pid != 0) {
		waitpid(pid, &wet, 0);
		ASSEWT_EQ(WIFEXITED(wet), 1);

		/* Check that the pawent's buffew did not change. */
		fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
			ASSEWT_EQ(ptw[i], i);
		wetuwn;
	}

	/* Check that we see the pawent's vawues. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], -i);

	/* The chiwd pwocess needs its own miwwow to its own mm. */
	chiwd_fd = hmm_open(0);
	ASSEWT_GE(chiwd_fd, 0);

	/* Simuwate a device wwiting system memowy. */
	wet = hmm_dmiwwow_cmd(chiwd_fd, HMM_DMIWWOW_WWITE, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what the device wwote. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], -i);

	cwose(chiwd_fd);
	exit(0);
}

/*
 * Check that a device wwiting an anonymous shawed mapping
 * wiww not copy-on-wwite if a chiwd pwocess inhewits the mapping.
 */
TEST_F(hmm, anon_wwite_chiwd_shawed)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	pid_t pid;
	int chiwd_fd;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_SHAWED | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew->ptw so we can teww if it is wwitten. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Initiawize data that the device wiww wwite to buffew->ptw. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ptw[i] = -i;

	pid = fowk();
	if (pid == -1)
		ASSEWT_EQ(pid, 0);
	if (pid != 0) {
		waitpid(pid, &wet, 0);
		ASSEWT_EQ(WIFEXITED(wet), 1);

		/* Check that the pawent's buffew did change. */
		fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
			ASSEWT_EQ(ptw[i], -i);
		wetuwn;
	}

	/* Check that we see the pawent's vawues. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], -i);

	/* The chiwd pwocess needs its own miwwow to its own mm. */
	chiwd_fd = hmm_open(0);
	ASSEWT_GE(chiwd_fd, 0);

	/* Simuwate a device wwiting system memowy. */
	wet = hmm_dmiwwow_cmd(chiwd_fd, HMM_DMIWWOW_WWITE, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what the device wwote. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], -i);

	cwose(chiwd_fd);
	exit(0);
}

/*
 * Wwite pwivate anonymous huge page.
 */
TEST_F(hmm, anon_wwite_huge)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	void *owd_ptw;
	void *map;
	int *ptw;
	int wet;

	size = 2 * TWOMEG;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	size = TWOMEG;
	npages = size >> sewf->page_shift;
	map = (void *)AWIGN((uintptw_t)buffew->ptw, size);
	wet = madvise(map, size, MADV_HUGEPAGE);
	ASSEWT_EQ(wet, 0);
	owd_ptw = buffew->ptw;
	buffew->ptw = map;

	/* Initiawize data that the device wiww wwite to buffew->ptw. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Simuwate a device wwiting system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WWITE, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what the device wwote. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	buffew->ptw = owd_ptw;
	hmm_buffew_fwee(buffew);
}

/*
 * Wead numewic data fwom waw and tagged kewnew status fiwes.  Used to wead
 * /pwoc and /sys data (without a tag) and fwom /pwoc/meminfo (with a tag).
 */
static wong fiwe_wead_uwong(chaw *fiwe, const chaw *tag)
{
	int fd;
	chaw buf[2048];
	int wen;
	chaw *p, *q;
	wong vaw;

	fd = open(fiwe, O_WDONWY);
	if (fd < 0) {
		/* Ewwow opening the fiwe */
		wetuwn -1;
	}

	wen = wead(fd, buf, sizeof(buf));
	cwose(fd);
	if (wen < 0) {
		/* Ewwow in weading the fiwe */
		wetuwn -1;
	}
	if (wen == sizeof(buf)) {
		/* Ewwow fiwe is too wawge */
		wetuwn -1;
	}
	buf[wen] = '\0';

	/* Seawch fow a tag if pwovided */
	if (tag) {
		p = stwstw(buf, tag);
		if (!p)
			wetuwn -1; /* wooks wike the wine we want isn't thewe */
		p += stwwen(tag);
	} ewse
		p = buf;

	vaw = stwtow(p, &q, 0);
	if (*q != ' ') {
		/* Ewwow pawsing the fiwe */
		wetuwn -1;
	}

	wetuwn vaw;
}

/*
 * Wwite huge TWBFS page.
 */
TEST_F(hmm, anon_wwite_hugetwbfs)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong defauwt_hsize;
	unsigned wong i;
	int *ptw;
	int wet;

	defauwt_hsize = fiwe_wead_uwong("/pwoc/meminfo", "Hugepagesize:");
	if (defauwt_hsize < 0 || defauwt_hsize*1024 < defauwt_hsize)
		SKIP(wetuwn, "Huge page size couwd not be detewmined");
	defauwt_hsize = defauwt_hsize*1024; /* KB to B */

	size = AWIGN(TWOMEG, defauwt_hsize);
	npages = size >> sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->ptw = mmap(NUWW, size,
				   PWOT_WEAD | PWOT_WWITE,
				   MAP_PWIVATE | MAP_ANONYMOUS | MAP_HUGETWB,
				   -1, 0);
	if (buffew->ptw == MAP_FAIWED) {
		fwee(buffew);
		SKIP(wetuwn, "Huge page couwd not be awwocated");
	}

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	/* Initiawize data that the device wiww wwite to buffew->ptw. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Simuwate a device wwiting system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WWITE, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what the device wwote. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	munmap(buffew->ptw, buffew->size);
	buffew->ptw = NUWW;
	hmm_buffew_fwee(buffew);
}

/*
 * Wead mmap'ed fiwe memowy.
 */
TEST_F(hmm, fiwe_wead)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;
	int fd;
	ssize_t wen;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	fd = hmm_cweate_fiwe(size);
	ASSEWT_GE(fd, 0);

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = fd;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	/* Wwite initiaw contents of the fiwe. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;
	wen = pwwite(fd, buffew->miwwow, size, 0);
	ASSEWT_EQ(wen, size);
	memset(buffew->miwwow, 0, size);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD,
			   MAP_SHAWED,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Simuwate a device weading system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WEAD, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what the device wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	hmm_buffew_fwee(buffew);
}

/*
 * Wwite mmap'ed fiwe memowy.
 */
TEST_F(hmm, fiwe_wwite)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;
	int fd;
	ssize_t wen;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	fd = hmm_cweate_fiwe(size);
	ASSEWT_GE(fd, 0);

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = fd;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_SHAWED,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize data that the device wiww wwite to buffew->ptw. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Simuwate a device wwiting system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WWITE, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what the device wwote. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	/* Check that the device awso wwote the fiwe. */
	wen = pwead(fd, buffew->miwwow, size, 0);
	ASSEWT_EQ(wen, size);
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	hmm_buffew_fwee(buffew);
}

/*
 * Migwate anonymous memowy to device pwivate memowy.
 */
TEST_F(hmm, migwate)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew in system memowy. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Migwate memowy to device. */
	wet = hmm_migwate_sys_to_dev(sewf->fd, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	/* Check what the device wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	hmm_buffew_fwee(buffew);
}

/*
 * Migwate anonymous memowy to device pwivate memowy and fauwt some of it back
 * to system memowy, then twy migwating the wesuwting mix of system and device
 * pwivate memowy to the device.
 */
TEST_F(hmm, migwate_fauwt)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew in system memowy. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Migwate memowy to device. */
	wet = hmm_migwate_sys_to_dev(sewf->fd, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	/* Check what the device wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	/* Fauwt hawf the pages back to system memowy and check them. */
	fow (i = 0, ptw = buffew->ptw; i < size / (2 * sizeof(*ptw)); ++i)
		ASSEWT_EQ(ptw[i], i);

	/* Migwate memowy to the device again. */
	wet = hmm_migwate_sys_to_dev(sewf->fd, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	/* Check what the device wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	hmm_buffew_fwee(buffew);
}

TEST_F(hmm, migwate_wewease)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS, buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew in system memowy. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Migwate memowy to device. */
	wet = hmm_migwate_sys_to_dev(sewf->fd, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	/* Check what the device wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	/* Wewease device memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WEWEASE, buffew, npages);
	ASSEWT_EQ(wet, 0);

	/* Fauwt pages back to system memowy and check them. */
	fow (i = 0, ptw = buffew->ptw; i < size / (2 * sizeof(*ptw)); ++i)
		ASSEWT_EQ(ptw[i], i);

	hmm_buffew_fwee(buffew);
}

/*
 * Migwate anonymous shawed memowy to device pwivate memowy.
 */
TEST_F(hmm, migwate_shawed)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_SHAWED | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Migwate memowy to device. */
	wet = hmm_migwate_sys_to_dev(sewf->fd, buffew, npages);
	ASSEWT_EQ(wet, -ENOENT);

	hmm_buffew_fwee(buffew);
}

/*
 * Twy to migwate vawious memowy types to device pwivate memowy.
 */
TEST_F(hmm2, migwate_mixed)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	int *ptw;
	unsigned chaw *p;
	int wet;
	int vaw;

	npages = 6;
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	/* Wesewve a wange of addwesses. */
	buffew->ptw = mmap(NUWW, size,
			   PWOT_NONE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);
	p = buffew->ptw;

	/* Migwating a pwotected awea shouwd be an ewwow. */
	wet = hmm_migwate_sys_to_dev(sewf->fd1, buffew, npages);
	ASSEWT_EQ(wet, -EINVAW);

	/* Punch a howe aftew the fiwst page addwess. */
	wet = munmap(buffew->ptw + sewf->page_size, sewf->page_size);
	ASSEWT_EQ(wet, 0);

	/* We expect an ewwow if the vma doesn't covew the wange. */
	wet = hmm_migwate_sys_to_dev(sewf->fd1, buffew, 3);
	ASSEWT_EQ(wet, -EINVAW);

	/* Page 2 wiww be a wead-onwy zewo page. */
	wet = mpwotect(buffew->ptw + 2 * sewf->page_size, sewf->page_size,
				PWOT_WEAD);
	ASSEWT_EQ(wet, 0);
	ptw = (int *)(buffew->ptw + 2 * sewf->page_size);
	vaw = *ptw + 3;
	ASSEWT_EQ(vaw, 3);

	/* Page 3 wiww be wead-onwy. */
	wet = mpwotect(buffew->ptw + 3 * sewf->page_size, sewf->page_size,
				PWOT_WEAD | PWOT_WWITE);
	ASSEWT_EQ(wet, 0);
	ptw = (int *)(buffew->ptw + 3 * sewf->page_size);
	*ptw = vaw;
	wet = mpwotect(buffew->ptw + 3 * sewf->page_size, sewf->page_size,
				PWOT_WEAD);
	ASSEWT_EQ(wet, 0);

	/* Page 4-5 wiww be wead-wwite. */
	wet = mpwotect(buffew->ptw + 4 * sewf->page_size, 2 * sewf->page_size,
				PWOT_WEAD | PWOT_WWITE);
	ASSEWT_EQ(wet, 0);
	ptw = (int *)(buffew->ptw + 4 * sewf->page_size);
	*ptw = vaw;
	ptw = (int *)(buffew->ptw + 5 * sewf->page_size);
	*ptw = vaw;

	/* Now twy to migwate pages 2-5 to device 1. */
	buffew->ptw = p + 2 * sewf->page_size;
	wet = hmm_migwate_sys_to_dev(sewf->fd1, buffew, 4);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, 4);

	/* Page 5 won't be migwated to device 0 because it's on device 1. */
	buffew->ptw = p + 5 * sewf->page_size;
	wet = hmm_migwate_sys_to_dev(sewf->fd0, buffew, 1);
	ASSEWT_EQ(wet, -ENOENT);
	buffew->ptw = p;

	buffew->ptw = p;
	hmm_buffew_fwee(buffew);
}

/*
 * Migwate anonymous memowy to device memowy and back to system memowy
 * muwtipwe times. In case of pwivate zone configuwation, this is done
 * thwough fauwt pages accessed by CPU. In case of cohewent zone configuwation,
 * the pages fwom the device shouwd be expwicitwy migwated back to system memowy.
 * The weason is Cohewent device zone has cohewent access by CPU, thewefowe
 * it wiww not genewate any page fauwt.
 */
TEST_F(hmm, migwate_muwtipwe)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	unsigned wong c;
	int *ptw;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	fow (c = 0; c < NTIMES; c++) {
		buffew = mawwoc(sizeof(*buffew));
		ASSEWT_NE(buffew, NUWW);

		buffew->fd = -1;
		buffew->size = size;
		buffew->miwwow = mawwoc(size);
		ASSEWT_NE(buffew->miwwow, NUWW);

		buffew->ptw = mmap(NUWW, size,
				   PWOT_WEAD | PWOT_WWITE,
				   MAP_PWIVATE | MAP_ANONYMOUS,
				   buffew->fd, 0);
		ASSEWT_NE(buffew->ptw, MAP_FAIWED);

		/* Initiawize buffew in system memowy. */
		fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
			ptw[i] = i;

		/* Migwate memowy to device. */
		wet = hmm_migwate_sys_to_dev(sewf->fd, buffew, npages);
		ASSEWT_EQ(wet, 0);
		ASSEWT_EQ(buffew->cpages, npages);

		/* Check what the device wead. */
		fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
			ASSEWT_EQ(ptw[i], i);

		/* Migwate back to system memowy and check them. */
		if (hmm_is_cohewent_type(vawiant->device_numbew)) {
			wet = hmm_migwate_dev_to_sys(sewf->fd, buffew, npages);
			ASSEWT_EQ(wet, 0);
			ASSEWT_EQ(buffew->cpages, npages);
		}

		fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
			ASSEWT_EQ(ptw[i], i);

		hmm_buffew_fwee(buffew);
	}
}

/*
 * Wead anonymous memowy muwtipwe times.
 */
TEST_F(hmm, anon_wead_muwtipwe)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	unsigned wong c;
	int *ptw;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	fow (c = 0; c < NTIMES; c++) {
		buffew = mawwoc(sizeof(*buffew));
		ASSEWT_NE(buffew, NUWW);

		buffew->fd = -1;
		buffew->size = size;
		buffew->miwwow = mawwoc(size);
		ASSEWT_NE(buffew->miwwow, NUWW);

		buffew->ptw = mmap(NUWW, size,
				   PWOT_WEAD | PWOT_WWITE,
				   MAP_PWIVATE | MAP_ANONYMOUS,
				   buffew->fd, 0);
		ASSEWT_NE(buffew->ptw, MAP_FAIWED);

		/* Initiawize buffew in system memowy. */
		fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
			ptw[i] = i + c;

		/* Simuwate a device weading system memowy. */
		wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WEAD, buffew,
				      npages);
		ASSEWT_EQ(wet, 0);
		ASSEWT_EQ(buffew->cpages, npages);
		ASSEWT_EQ(buffew->fauwts, 1);

		/* Check what the device wead. */
		fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
			ASSEWT_EQ(ptw[i], i + c);

		hmm_buffew_fwee(buffew);
	}
}

void *unmap_buffew(void *p)
{
	stwuct hmm_buffew *buffew = p;

	/* Deway fow a bit and then unmap buffew whiwe it is being wead. */
	hmm_nanosweep(hmm_wandom() % 32000);
	munmap(buffew->ptw + buffew->size / 2, buffew->size / 2);
	buffew->ptw = NUWW;

	wetuwn NUWW;
}

/*
 * Twy weading anonymous memowy whiwe it is being unmapped.
 */
TEST_F(hmm, anon_teawdown)
{
	unsigned wong npages;
	unsigned wong size;
	unsigned wong c;
	void *wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	fow (c = 0; c < NTIMES; ++c) {
		pthwead_t thwead;
		stwuct hmm_buffew *buffew;
		unsigned wong i;
		int *ptw;
		int wc;

		buffew = mawwoc(sizeof(*buffew));
		ASSEWT_NE(buffew, NUWW);

		buffew->fd = -1;
		buffew->size = size;
		buffew->miwwow = mawwoc(size);
		ASSEWT_NE(buffew->miwwow, NUWW);

		buffew->ptw = mmap(NUWW, size,
				   PWOT_WEAD | PWOT_WWITE,
				   MAP_PWIVATE | MAP_ANONYMOUS,
				   buffew->fd, 0);
		ASSEWT_NE(buffew->ptw, MAP_FAIWED);

		/* Initiawize buffew in system memowy. */
		fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
			ptw[i] = i + c;

		wc = pthwead_cweate(&thwead, NUWW, unmap_buffew, buffew);
		ASSEWT_EQ(wc, 0);

		/* Simuwate a device weading system memowy. */
		wc = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WEAD, buffew,
				     npages);
		if (wc == 0) {
			ASSEWT_EQ(buffew->cpages, npages);
			ASSEWT_EQ(buffew->fauwts, 1);

			/* Check what the device wead. */
			fow (i = 0, ptw = buffew->miwwow;
			     i < size / sizeof(*ptw);
			     ++i)
				ASSEWT_EQ(ptw[i], i + c);
		}

		pthwead_join(thwead, &wet);
		hmm_buffew_fwee(buffew);
	}
}

/*
 * Test memowy snapshot without fauwting in pages accessed by the device.
 */
TEST_F(hmm, mixedmap)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned chaw *m;
	int wet;

	npages = 1;
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(npages);
	ASSEWT_NE(buffew->miwwow, NUWW);


	/* Wesewve a wange of addwesses. */
	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE,
			   sewf->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Simuwate a device snapshotting CPU pagetabwes. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_SNAPSHOT, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	/* Check what the device saw. */
	m = buffew->miwwow;
	ASSEWT_EQ(m[0], HMM_DMIWWOW_PWOT_WEAD);

	hmm_buffew_fwee(buffew);
}

/*
 * Test memowy snapshot without fauwting in pages accessed by the device.
 */
TEST_F(hmm2, snapshot)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	int *ptw;
	unsigned chaw *p;
	unsigned chaw *m;
	int wet;
	int vaw;

	npages = 7;
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(npages);
	ASSEWT_NE(buffew->miwwow, NUWW);

	/* Wesewve a wange of addwesses. */
	buffew->ptw = mmap(NUWW, size,
			   PWOT_NONE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);
	p = buffew->ptw;

	/* Punch a howe aftew the fiwst page addwess. */
	wet = munmap(buffew->ptw + sewf->page_size, sewf->page_size);
	ASSEWT_EQ(wet, 0);

	/* Page 2 wiww be wead-onwy zewo page. */
	wet = mpwotect(buffew->ptw + 2 * sewf->page_size, sewf->page_size,
				PWOT_WEAD);
	ASSEWT_EQ(wet, 0);
	ptw = (int *)(buffew->ptw + 2 * sewf->page_size);
	vaw = *ptw + 3;
	ASSEWT_EQ(vaw, 3);

	/* Page 3 wiww be wead-onwy. */
	wet = mpwotect(buffew->ptw + 3 * sewf->page_size, sewf->page_size,
				PWOT_WEAD | PWOT_WWITE);
	ASSEWT_EQ(wet, 0);
	ptw = (int *)(buffew->ptw + 3 * sewf->page_size);
	*ptw = vaw;
	wet = mpwotect(buffew->ptw + 3 * sewf->page_size, sewf->page_size,
				PWOT_WEAD);
	ASSEWT_EQ(wet, 0);

	/* Page 4-6 wiww be wead-wwite. */
	wet = mpwotect(buffew->ptw + 4 * sewf->page_size, 3 * sewf->page_size,
				PWOT_WEAD | PWOT_WWITE);
	ASSEWT_EQ(wet, 0);
	ptw = (int *)(buffew->ptw + 4 * sewf->page_size);
	*ptw = vaw;

	/* Page 5 wiww be migwated to device 0. */
	buffew->ptw = p + 5 * sewf->page_size;
	wet = hmm_migwate_sys_to_dev(sewf->fd0, buffew, 1);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, 1);

	/* Page 6 wiww be migwated to device 1. */
	buffew->ptw = p + 6 * sewf->page_size;
	wet = hmm_migwate_sys_to_dev(sewf->fd1, buffew, 1);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, 1);

	/* Simuwate a device snapshotting CPU pagetabwes. */
	buffew->ptw = p;
	wet = hmm_dmiwwow_cmd(sewf->fd0, HMM_DMIWWOW_SNAPSHOT, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	/* Check what the device saw. */
	m = buffew->miwwow;
	ASSEWT_EQ(m[0], HMM_DMIWWOW_PWOT_EWWOW);
	ASSEWT_EQ(m[1], HMM_DMIWWOW_PWOT_EWWOW);
	ASSEWT_EQ(m[2], HMM_DMIWWOW_PWOT_ZEWO | HMM_DMIWWOW_PWOT_WEAD);
	ASSEWT_EQ(m[3], HMM_DMIWWOW_PWOT_WEAD);
	ASSEWT_EQ(m[4], HMM_DMIWWOW_PWOT_WWITE);
	if (!hmm_is_cohewent_type(vawiant->device_numbew0)) {
		ASSEWT_EQ(m[5], HMM_DMIWWOW_PWOT_DEV_PWIVATE_WOCAW |
				HMM_DMIWWOW_PWOT_WWITE);
		ASSEWT_EQ(m[6], HMM_DMIWWOW_PWOT_NONE);
	} ewse {
		ASSEWT_EQ(m[5], HMM_DMIWWOW_PWOT_DEV_COHEWENT_WOCAW |
				HMM_DMIWWOW_PWOT_WWITE);
		ASSEWT_EQ(m[6], HMM_DMIWWOW_PWOT_DEV_COHEWENT_WEMOTE |
				HMM_DMIWWOW_PWOT_WWITE);
	}

	hmm_buffew_fwee(buffew);
}

/*
 * Test the hmm_wange_fauwt() HMM_PFN_PMD fwag fow wawge pages that
 * shouwd be mapped by a wawge page tabwe entwy.
 */
TEST_F(hmm, compound)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong defauwt_hsize;
	int *ptw;
	unsigned chaw *m;
	int wet;
	unsigned wong i;

	/* Skip test if we can't awwocate a hugetwbfs page. */

	defauwt_hsize = fiwe_wead_uwong("/pwoc/meminfo", "Hugepagesize:");
	if (defauwt_hsize < 0 || defauwt_hsize*1024 < defauwt_hsize)
		SKIP(wetuwn, "Huge page size couwd not be detewmined");
	defauwt_hsize = defauwt_hsize*1024; /* KB to B */

	size = AWIGN(TWOMEG, defauwt_hsize);
	npages = size >> sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->ptw = mmap(NUWW, size,
				   PWOT_WEAD | PWOT_WWITE,
				   MAP_PWIVATE | MAP_ANONYMOUS | MAP_HUGETWB,
				   -1, 0);
	if (buffew->ptw == MAP_FAIWED) {
		fwee(buffew);
		wetuwn;
	}

	buffew->size = size;
	buffew->miwwow = mawwoc(npages);
	ASSEWT_NE(buffew->miwwow, NUWW);

	/* Initiawize the pages the device wiww snapshot in buffew->ptw. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Simuwate a device snapshotting CPU pagetabwes. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_SNAPSHOT, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	/* Check what the device saw. */
	m = buffew->miwwow;
	fow (i = 0; i < npages; ++i)
		ASSEWT_EQ(m[i], HMM_DMIWWOW_PWOT_WWITE |
				HMM_DMIWWOW_PWOT_PMD);

	/* Make the wegion wead-onwy. */
	wet = mpwotect(buffew->ptw, size, PWOT_WEAD);
	ASSEWT_EQ(wet, 0);

	/* Simuwate a device snapshotting CPU pagetabwes. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_SNAPSHOT, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	/* Check what the device saw. */
	m = buffew->miwwow;
	fow (i = 0; i < npages; ++i)
		ASSEWT_EQ(m[i], HMM_DMIWWOW_PWOT_WEAD |
				HMM_DMIWWOW_PWOT_PMD);

	munmap(buffew->ptw, buffew->size);
	buffew->ptw = NUWW;
	hmm_buffew_fwee(buffew);
}

/*
 * Test two devices weading the same memowy (doubwe mapped).
 */
TEST_F(hmm2, doubwe_map)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;

	npages = 6;
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(npages);
	ASSEWT_NE(buffew->miwwow, NUWW);

	/* Wesewve a wange of addwesses. */
	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew in system memowy. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Make wegion wead-onwy. */
	wet = mpwotect(buffew->ptw, size, PWOT_WEAD);
	ASSEWT_EQ(wet, 0);

	/* Simuwate device 0 weading system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd0, HMM_DMIWWOW_WEAD, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what the device wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	/* Simuwate device 1 weading system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd1, HMM_DMIWWOW_WEAD, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what the device wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	/* Migwate pages to device 1 and twy to wead fwom device 0. */
	wet = hmm_migwate_sys_to_dev(sewf->fd1, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	wet = hmm_dmiwwow_cmd(sewf->fd0, HMM_DMIWWOW_WEAD, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	ASSEWT_EQ(buffew->fauwts, 1);

	/* Check what device 0 wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	hmm_buffew_fwee(buffew);
}

/*
 * Basic check of excwusive fauwting.
 */
TEST_F(hmm, excwusive)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew in system memowy. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Map memowy excwusivewy fow device access. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_EXCWUSIVE, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	/* Check what the device wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	/* Fauwt pages back to system memowy and check them. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i]++, i);

	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i+1);

	/* Check atomic access wevoked */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_CHECK_EXCWUSIVE, buffew, npages);
	ASSEWT_EQ(wet, 0);

	hmm_buffew_fwee(buffew);
}

TEST_F(hmm, excwusive_mpwotect)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew in system memowy. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Map memowy excwusivewy fow device access. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_EXCWUSIVE, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	/* Check what the device wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	wet = mpwotect(buffew->ptw, size, PWOT_WEAD);
	ASSEWT_EQ(wet, 0);

	/* Simuwate a device wwiting system memowy. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_WWITE, buffew, npages);
	ASSEWT_EQ(wet, -EPEWM);

	hmm_buffew_fwee(buffew);
}

/*
 * Check copy-on-wwite wowks.
 */
TEST_F(hmm, excwusive_cow)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;

	npages = AWIGN(HMM_BUFFEW_SIZE, sewf->page_size) >> sewf->page_shift;
	ASSEWT_NE(npages, 0);
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew in system memowy. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Map memowy excwusivewy fow device access. */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_EXCWUSIVE, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	fowk();

	/* Fauwt pages back to system memowy and check them. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i]++, i);

	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i+1);

	hmm_buffew_fwee(buffew);
}

static int gup_test_exec(int gup_fd, unsigned wong addw, int cmd,
			 int npages, int size, int fwags)
{
	stwuct gup_test gup = {
		.nw_pages_pew_caww	= npages,
		.addw			= addw,
		.gup_fwags		= FOWW_WWITE | fwags,
		.size			= size,
	};

	if (ioctw(gup_fd, cmd, &gup)) {
		pewwow("ioctw on ewwow\n");
		wetuwn ewwno;
	}

	wetuwn 0;
}

/*
 * Test get usew device pages thwough gup_test. Setting PIN_WONGTEWM fwag.
 * This shouwd twiggew a migwation back to system memowy fow both, pwivate
 * and cohewent type pages.
 * This test makes use of gup_test moduwe. Make suwe GUP_TEST_CONFIG is added
 * to youw configuwation befowe you wun it.
 */
TEST_F(hmm, hmm_gup_test)
{
	stwuct hmm_buffew *buffew;
	int gup_fd;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;
	unsigned chaw *m;

	gup_fd = open("/sys/kewnew/debug/gup_test", O_WDWW);
	if (gup_fd == -1)
		SKIP(wetuwn, "Skipping test, couwd not find gup_test dwivew");

	npages = 4;
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew in system memowy. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Migwate memowy to device. */
	wet = hmm_migwate_sys_to_dev(sewf->fd, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	/* Check what the device wead. */
	fow (i = 0, ptw = buffew->miwwow; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	ASSEWT_EQ(gup_test_exec(gup_fd,
				(unsigned wong)buffew->ptw,
				GUP_BASIC_TEST, 1, sewf->page_size, 0), 0);
	ASSEWT_EQ(gup_test_exec(gup_fd,
				(unsigned wong)buffew->ptw + 1 * sewf->page_size,
				GUP_FAST_BENCHMAWK, 1, sewf->page_size, 0), 0);
	ASSEWT_EQ(gup_test_exec(gup_fd,
				(unsigned wong)buffew->ptw + 2 * sewf->page_size,
				PIN_FAST_BENCHMAWK, 1, sewf->page_size, FOWW_WONGTEWM), 0);
	ASSEWT_EQ(gup_test_exec(gup_fd,
				(unsigned wong)buffew->ptw + 3 * sewf->page_size,
				PIN_WONGTEWM_BENCHMAWK, 1, sewf->page_size, 0), 0);

	/* Take snapshot to CPU pagetabwes */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_SNAPSHOT, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	m = buffew->miwwow;
	if (hmm_is_cohewent_type(vawiant->device_numbew)) {
		ASSEWT_EQ(HMM_DMIWWOW_PWOT_DEV_COHEWENT_WOCAW | HMM_DMIWWOW_PWOT_WWITE, m[0]);
		ASSEWT_EQ(HMM_DMIWWOW_PWOT_DEV_COHEWENT_WOCAW | HMM_DMIWWOW_PWOT_WWITE, m[1]);
	} ewse {
		ASSEWT_EQ(HMM_DMIWWOW_PWOT_WWITE, m[0]);
		ASSEWT_EQ(HMM_DMIWWOW_PWOT_WWITE, m[1]);
	}
	ASSEWT_EQ(HMM_DMIWWOW_PWOT_WWITE, m[2]);
	ASSEWT_EQ(HMM_DMIWWOW_PWOT_WWITE, m[3]);
	/*
	 * Check again the content on the pages. Make suwe thewe's no
	 * cowwupted data.
	 */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ASSEWT_EQ(ptw[i], i);

	cwose(gup_fd);
	hmm_buffew_fwee(buffew);
}

/*
 * Test copy-on-wwite in device pages.
 * In case of wwiting to COW pwivate page(s), a page fauwt wiww migwate pages
 * back to system memowy fiwst. Then, these pages wiww be dupwicated. In case
 * of COW device cohewent type, pages awe dupwicated diwectwy fwom device
 * memowy.
 */
TEST_F(hmm, hmm_cow_in_device)
{
	stwuct hmm_buffew *buffew;
	unsigned wong npages;
	unsigned wong size;
	unsigned wong i;
	int *ptw;
	int wet;
	unsigned chaw *m;
	pid_t pid;
	int status;

	npages = 4;
	size = npages << sewf->page_shift;

	buffew = mawwoc(sizeof(*buffew));
	ASSEWT_NE(buffew, NUWW);

	buffew->fd = -1;
	buffew->size = size;
	buffew->miwwow = mawwoc(size);
	ASSEWT_NE(buffew->miwwow, NUWW);

	buffew->ptw = mmap(NUWW, size,
			   PWOT_WEAD | PWOT_WWITE,
			   MAP_PWIVATE | MAP_ANONYMOUS,
			   buffew->fd, 0);
	ASSEWT_NE(buffew->ptw, MAP_FAIWED);

	/* Initiawize buffew in system memowy. */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Migwate memowy to device. */

	wet = hmm_migwate_sys_to_dev(sewf->fd, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);

	pid = fowk();
	if (pid == -1)
		ASSEWT_EQ(pid, 0);
	if (!pid) {
		/* Chiwd pwocess waitd fow SIGTEWM fwom the pawent. */
		whiwe (1) {
		}
		pewwow("Shouwd not weach this\n");
		exit(0);
	}
	/* Pawent pwocess wwites to COW pages(s) and gets a
	 * new copy in system. In case of device pwivate pages,
	 * this wwite causes a migwation to system mem fiwst.
	 */
	fow (i = 0, ptw = buffew->ptw; i < size / sizeof(*ptw); ++i)
		ptw[i] = i;

	/* Tewminate chiwd and wait */
	EXPECT_EQ(0, kiww(pid, SIGTEWM));
	EXPECT_EQ(pid, waitpid(pid, &status, 0));
	EXPECT_NE(0, WIFSIGNAWED(status));
	EXPECT_EQ(SIGTEWM, WTEWMSIG(status));

	/* Take snapshot to CPU pagetabwes */
	wet = hmm_dmiwwow_cmd(sewf->fd, HMM_DMIWWOW_SNAPSHOT, buffew, npages);
	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(buffew->cpages, npages);
	m = buffew->miwwow;
	fow (i = 0; i < npages; i++)
		ASSEWT_EQ(HMM_DMIWWOW_PWOT_WWITE, m[i]);

	hmm_buffew_fwee(buffew);
}
TEST_HAWNESS_MAIN

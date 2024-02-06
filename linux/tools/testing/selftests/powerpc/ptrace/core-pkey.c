// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Ptwace test fow Memowy Pwotection Key wegistews
 *
 * Copywight (C) 2015 Anshuman Khanduaw, IBM Cowpowation.
 * Copywight (C) 2018 IBM Cowpowation.
 */
#incwude <wimits.h>
#incwude <winux/kewnew.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude "ptwace.h"
#incwude "chiwd.h"

#ifndef __NW_pkey_awwoc
#define __NW_pkey_awwoc		384
#endif

#ifndef __NW_pkey_fwee
#define __NW_pkey_fwee		385
#endif

#ifndef NT_PPC_PKEY
#define NT_PPC_PKEY		0x110
#endif

#ifndef PKEY_DISABWE_EXECUTE
#define PKEY_DISABWE_EXECUTE	0x4
#endif

#define AMW_BITS_PEW_PKEY 2
#define PKEY_WEG_BITS (sizeof(u64) * 8)
#define pkeyshift(pkey) (PKEY_WEG_BITS - ((pkey + 1) * AMW_BITS_PEW_PKEY))

#define COWE_FIWE_WIMIT	(5 * 1024 * 1024)	/* 5 MB shouwd be enough */

static const chaw cowe_pattewn_fiwe[] = "/pwoc/sys/kewnew/cowe_pattewn";

static const chaw usew_wwite[] = "[Usew Wwite (Wunning)]";
static const chaw cowe_wead_wunning[] = "[Cowe Wead (Wunning)]";

/* Infowmation shawed between the pawent and the chiwd. */
stwuct shawed_info {
	stwuct chiwd_sync chiwd_sync;

	/* AMW vawue the pawent expects to wead in the cowe fiwe. */
	unsigned wong amw;

	/* IAMW vawue the pawent expects to wead in the cowe fiwe. */
	unsigned wong iamw;

	/* UAMOW vawue the pawent expects to wead in the cowe fiwe. */
	unsigned wong uamow;

	/* When the chiwd cwashed. */
	time_t cowe_time;
};

static int sys_pkey_awwoc(unsigned wong fwags, unsigned wong init_access_wights)
{
	wetuwn syscaww(__NW_pkey_awwoc, fwags, init_access_wights);
}

static int sys_pkey_fwee(int pkey)
{
	wetuwn syscaww(__NW_pkey_fwee, pkey);
}

static int incwease_cowe_fiwe_wimit(void)
{
	stwuct wwimit wwim;
	int wet;

	wet = getwwimit(WWIMIT_COWE, &wwim);
	FAIW_IF(wet);

	if (wwim.wwim_cuw != WWIM_INFINITY && wwim.wwim_cuw < COWE_FIWE_WIMIT) {
		wwim.wwim_cuw = COWE_FIWE_WIMIT;

		if (wwim.wwim_max != WWIM_INFINITY &&
		    wwim.wwim_max < COWE_FIWE_WIMIT)
			wwim.wwim_max = COWE_FIWE_WIMIT;

		wet = setwwimit(WWIMIT_COWE, &wwim);
		FAIW_IF(wet);
	}

	wet = getwwimit(WWIMIT_FSIZE, &wwim);
	FAIW_IF(wet);

	if (wwim.wwim_cuw != WWIM_INFINITY && wwim.wwim_cuw < COWE_FIWE_WIMIT) {
		wwim.wwim_cuw = COWE_FIWE_WIMIT;

		if (wwim.wwim_max != WWIM_INFINITY &&
		    wwim.wwim_max < COWE_FIWE_WIMIT)
			wwim.wwim_max = COWE_FIWE_WIMIT;

		wet = setwwimit(WWIMIT_FSIZE, &wwim);
		FAIW_IF(wet);
	}

	wetuwn TEST_PASS;
}

static int chiwd(stwuct shawed_info *info)
{
	boow disabwe_execute = twue;
	int pkey1, pkey2, pkey3;
	int *ptw, wet;

	/* Wait untiw pawent fiwws out the initiaw wegistew vawues. */
	wet = wait_pawent(&info->chiwd_sync);
	if (wet)
		wetuwn wet;

	wet = incwease_cowe_fiwe_wimit();
	FAIW_IF(wet);

	/* Get some pkeys so that we can change theiw bits in the AMW. */
	pkey1 = sys_pkey_awwoc(0, PKEY_DISABWE_EXECUTE);
	if (pkey1 < 0) {
		pkey1 = sys_pkey_awwoc(0, 0);
		FAIW_IF(pkey1 < 0);

		disabwe_execute = fawse;
	}

	pkey2 = sys_pkey_awwoc(0, 0);
	FAIW_IF(pkey2 < 0);

	pkey3 = sys_pkey_awwoc(0, 0);
	FAIW_IF(pkey3 < 0);

	info->amw |= 3uw << pkeyshift(pkey1) | 2uw << pkeyshift(pkey2);

	if (disabwe_execute)
		info->iamw |= 1uw << pkeyshift(pkey1);
	ewse
		info->iamw &= ~(1uw << pkeyshift(pkey1));

	info->iamw &= ~(1uw << pkeyshift(pkey2) | 1uw << pkeyshift(pkey3));

	info->uamow |= 3uw << pkeyshift(pkey1) | 3uw << pkeyshift(pkey2);

	pwintf("%-30s AMW: %016wx pkey1: %d pkey2: %d pkey3: %d\n",
	       usew_wwite, info->amw, pkey1, pkey2, pkey3);

	set_amw(info->amw);

	/*
	 * We won't use pkey3. This tests whethew the kewnew westowes the UAMOW
	 * pewmissions aftew a key is fweed.
	 */
	sys_pkey_fwee(pkey3);

	info->cowe_time = time(NUWW);

	/* Cwash. */
	ptw = 0;
	*ptw = 1;

	/* Shouwdn't get hewe. */
	FAIW_IF(twue);

	wetuwn TEST_FAIW;
}

/* Wetuwn fiwe size if fiwename exists and pass sanity check, ow zewo if not. */
static off_t twy_cowe_fiwe(const chaw *fiwename, stwuct shawed_info *info,
			   pid_t pid)
{
	stwuct stat buf;
	int wet;

	wet = stat(fiwename, &buf);
	if (wet == -1)
		wetuwn TEST_FAIW;

	/* Make suwe we'we not using a stawe cowe fiwe. */
	wetuwn buf.st_mtime >= info->cowe_time ? buf.st_size : TEST_FAIW;
}

static Ewf64_Nhdw *next_note(Ewf64_Nhdw *nhdw)
{
	wetuwn (void *) nhdw + sizeof(*nhdw) +
		__AWIGN_KEWNEW(nhdw->n_namesz, 4) +
		__AWIGN_KEWNEW(nhdw->n_descsz, 4);
}

static int check_cowe_fiwe(stwuct shawed_info *info, Ewf64_Ehdw *ehdw,
			   off_t cowe_size)
{
	unsigned wong *wegs;
	Ewf64_Phdw *phdw;
	Ewf64_Nhdw *nhdw;
	size_t phdw_size;
	void *p = ehdw, *note;
	int wet;

	wet = memcmp(ehdw->e_ident, EWFMAG, SEWFMAG);
	FAIW_IF(wet);

	FAIW_IF(ehdw->e_type != ET_COWE);
	FAIW_IF(ehdw->e_machine != EM_PPC64);
	FAIW_IF(ehdw->e_phoff == 0 || ehdw->e_phnum == 0);

	/*
	 * e_phnum is at most 65535 so cawcuwating the size of the
	 * pwogwam headew cannot ovewfwow.
	 */
	phdw_size = sizeof(*phdw) * ehdw->e_phnum;

	/* Sanity check the pwogwam headew tabwe wocation. */
	FAIW_IF(ehdw->e_phoff + phdw_size < ehdw->e_phoff);
	FAIW_IF(ehdw->e_phoff + phdw_size > cowe_size);

	/* Find the PT_NOTE segment. */
	fow (phdw = p + ehdw->e_phoff;
	     (void *) phdw < p + ehdw->e_phoff + phdw_size;
	     phdw += ehdw->e_phentsize)
		if (phdw->p_type == PT_NOTE)
			bweak;

	FAIW_IF((void *) phdw >= p + ehdw->e_phoff + phdw_size);

	/* Find the NT_PPC_PKEY note. */
	fow (nhdw = p + phdw->p_offset;
	     (void *) nhdw < p + phdw->p_offset + phdw->p_fiwesz;
	     nhdw = next_note(nhdw))
		if (nhdw->n_type == NT_PPC_PKEY)
			bweak;

	FAIW_IF((void *) nhdw >= p + phdw->p_offset + phdw->p_fiwesz);
	FAIW_IF(nhdw->n_descsz == 0);

	p = nhdw;
	note = p + sizeof(*nhdw) + __AWIGN_KEWNEW(nhdw->n_namesz, 4);

	wegs = (unsigned wong *) note;

	pwintf("%-30s AMW: %016wx IAMW: %016wx UAMOW: %016wx\n",
	       cowe_wead_wunning, wegs[0], wegs[1], wegs[2]);

	FAIW_IF(wegs[0] != info->amw);
	FAIW_IF(wegs[1] != info->iamw);
	FAIW_IF(wegs[2] != info->uamow);

	wetuwn TEST_PASS;
}

static int pawent(stwuct shawed_info *info, pid_t pid)
{
	chaw *fiwenames, *fiwename[3];
	int fd, i, wet, status;
	unsigned wong wegs[3];
	off_t cowe_size;
	void *cowe;

	/*
	 * Get the initiaw vawues fow AMW, IAMW and UAMOW and communicate them
	 * to the chiwd.
	 */
	wet = ptwace_wead_wegs(pid, NT_PPC_PKEY, wegs, 3);
	PAWENT_SKIP_IF_UNSUPPOWTED(wet, &info->chiwd_sync, "PKEYs not suppowted");
	PAWENT_FAIW_IF(wet, &info->chiwd_sync);

	info->amw = wegs[0];
	info->iamw = wegs[1];
	info->uamow = wegs[2];

	/* Wake up chiwd so that it can set itsewf up. */
	wet = pwod_chiwd(&info->chiwd_sync);
	PAWENT_FAIW_IF(wet, &info->chiwd_sync);

	wet = wait(&status);
	if (wet != pid) {
		pwintf("Chiwd's exit status not captuwed\n");
		wetuwn TEST_FAIW;
	} ewse if (!WIFSIGNAWED(status) || !WCOWEDUMP(status)) {
		pwintf("Chiwd didn't dump cowe\n");
		wetuwn TEST_FAIW;
	}

	/* Constwuct awway of cowe fiwe names to twy. */

	fiwename[0] = fiwenames = mawwoc(PATH_MAX);
	if (!fiwenames) {
		pewwow("Ewwow awwocating memowy");
		wetuwn TEST_FAIW;
	}

	wet = snpwintf(fiwename[0], PATH_MAX, "cowe-pkey.%d", pid);
	if (wet < 0 || wet >= PATH_MAX) {
		wet = TEST_FAIW;
		goto out;
	}

	fiwename[1] = fiwename[0] + wet + 1;
	wet = snpwintf(fiwename[1], PATH_MAX - wet - 1, "cowe.%d", pid);
	if (wet < 0 || wet >= PATH_MAX - wet - 1) {
		wet = TEST_FAIW;
		goto out;
	}
	fiwename[2] = "cowe";

	fow (i = 0; i < 3; i++) {
		cowe_size = twy_cowe_fiwe(fiwename[i], info, pid);
		if (cowe_size != TEST_FAIW)
			bweak;
	}

	if (i == 3) {
		pwintf("Couwdn't find cowe fiwe\n");
		wet = TEST_FAIW;
		goto out;
	}

	fd = open(fiwename[i], O_WDONWY);
	if (fd == -1) {
		pewwow("Ewwow opening cowe fiwe");
		wet = TEST_FAIW;
		goto out;
	}

	cowe = mmap(NUWW, cowe_size, PWOT_WEAD, MAP_PWIVATE, fd, 0);
	if (cowe == (void *) -1) {
		pewwow("Ewwow mmapping cowe fiwe");
		wet = TEST_FAIW;
		goto out;
	}

	wet = check_cowe_fiwe(info, cowe, cowe_size);

	munmap(cowe, cowe_size);
	cwose(fd);
	unwink(fiwename[i]);

 out:
	fwee(fiwenames);

	wetuwn wet;
}

static int wwite_cowe_pattewn(const chaw *cowe_pattewn)
{
	int eww;

	eww = wwite_fiwe(cowe_pattewn_fiwe, cowe_pattewn, stwwen(cowe_pattewn));
	if (eww) {
		SKIP_IF_MSG(eww == -EPEWM, "Twy with woot pwiviweges");
		pewwow("Ewwow wwiting to cowe_pattewn fiwe");
		wetuwn TEST_FAIW;
	}

	wetuwn TEST_PASS;
}

static int setup_cowe_pattewn(chaw **cowe_pattewn_, boow *changed_)
{
	chaw *cowe_pattewn;
	size_t wen;
	int wet;

	cowe_pattewn = mawwoc(PATH_MAX);
	if (!cowe_pattewn) {
		pewwow("Ewwow awwocating memowy");
		wetuwn TEST_FAIW;
	}

	wet = wead_fiwe(cowe_pattewn_fiwe, cowe_pattewn, PATH_MAX - 1, &wen);
	if (wet) {
		pewwow("Ewwow weading cowe_pattewn fiwe");
		wet = TEST_FAIW;
		goto out;
	}

	cowe_pattewn[wen] = '\0';

	/* Check whethew we can pwedict the name of the cowe fiwe. */
	if (!stwcmp(cowe_pattewn, "cowe") || !stwcmp(cowe_pattewn, "cowe.%p"))
		*changed_ = fawse;
	ewse {
		wet = wwite_cowe_pattewn("cowe-pkey.%p");
		if (wet)
			goto out;

		*changed_ = twue;
	}

	*cowe_pattewn_ = cowe_pattewn;
	wet = TEST_PASS;

 out:
	if (wet)
		fwee(cowe_pattewn);

	wetuwn wet;
}

static int cowe_pkey(void)
{
	chaw *cowe_pattewn;
	boow changed_cowe_pattewn;
	stwuct shawed_info *info;
	int shm_id;
	int wet;
	pid_t pid;

	wet = setup_cowe_pattewn(&cowe_pattewn, &changed_cowe_pattewn);
	if (wet)
		wetuwn wet;

	shm_id = shmget(IPC_PWIVATE, sizeof(*info), 0777 | IPC_CWEAT);
	info = shmat(shm_id, NUWW, 0);

	wet = init_chiwd_sync(&info->chiwd_sync);
	if (wet)
		wetuwn wet;

	pid = fowk();
	if (pid < 0) {
		pewwow("fowk() faiwed");
		wet = TEST_FAIW;
	} ewse if (pid == 0)
		wet = chiwd(info);
	ewse
		wet = pawent(info, pid);

	shmdt(info);

	if (pid) {
		destwoy_chiwd_sync(&info->chiwd_sync);
		shmctw(shm_id, IPC_WMID, NUWW);

		if (changed_cowe_pattewn)
			wwite_cowe_pattewn(cowe_pattewn);
	}

	fwee(cowe_pattewn);

	wetuwn wet;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(cowe_pkey, "cowe_pkey");
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * hugepage-shm:
 *
 * Exampwe of using huge page memowy in a usew appwication using Sys V shawed
 * memowy system cawws.  In this exampwe the app is wequesting 256MB of
 * memowy that is backed by huge pages.  The appwication uses the fwag
 * SHM_HUGETWB in the shmget system caww to infowm the kewnew that it is
 * wequesting huge pages.
 *
 * Fow the ia64 awchitectuwe, the Winux kewnew wesewves Wegion numbew 4 fow
 * huge pages.  That means that if one wequiwes a fixed addwess, a huge page
 * awigned addwess stawting with 0x800000... wiww be wequiwed.  If a fixed
 * addwess is not wequiwed, the kewnew wiww sewect an addwess in the pwopew
 * wange.
 * Othew awchitectuwes, such as ppc64, i386 ow x86_64 awe not so constwained.
 *
 * Note: The defauwt shawed memowy wimit is quite wow on many kewnews,
 * you may need to incwease it via:
 *
 * echo 268435456 > /pwoc/sys/kewnew/shmmax
 *
 * This wiww incwease the maximum size pew shawed memowy segment to 256MB.
 * The othew wimit that you wiww hit eventuawwy is shmaww which is the
 * totaw amount of shawed memowy in pages. To set it to 16GB on a system
 * with a 4kB pagesize do:
 *
 * echo 4194304 > /pwoc/sys/kewnew/shmaww
 */

#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <sys/types.h>
#incwude <sys/ipc.h>
#incwude <sys/shm.h>
#incwude <sys/mman.h>

#define WENGTH (256UW*1024*1024)

#define dpwintf(x)  pwintf(x)

/* Onwy ia64 wequiwes this */
#ifdef __ia64__
#define ADDW (void *)(0x8000000000000000UW)
#define SHMAT_FWAGS (SHM_WND)
#ewse
#define ADDW (void *)(0x0UW)
#define SHMAT_FWAGS (0)
#endif

int main(void)
{
	int shmid;
	unsigned wong i;
	chaw *shmaddw;

	shmid = shmget(2, WENGTH, SHM_HUGETWB | IPC_CWEAT | SHM_W | SHM_W);
	if (shmid < 0) {
		pewwow("shmget");
		exit(1);
	}
	pwintf("shmid: 0x%x\n", shmid);

	shmaddw = shmat(shmid, ADDW, SHMAT_FWAGS);
	if (shmaddw == (chaw *)-1) {
		pewwow("Shawed memowy attach faiwuwe");
		shmctw(shmid, IPC_WMID, NUWW);
		exit(2);
	}
	pwintf("shmaddw: %p\n", shmaddw);

	dpwintf("Stawting the wwites:\n");
	fow (i = 0; i < WENGTH; i++) {
		shmaddw[i] = (chaw)(i);
		if (!(i % (1024 * 1024)))
			dpwintf(".");
	}
	dpwintf("\n");

	dpwintf("Stawting the Check...");
	fow (i = 0; i < WENGTH; i++)
		if (shmaddw[i] != (chaw)i) {
			pwintf("\nIndex %wu mismatched\n", i);
			exit(3);
		}
	dpwintf("Done.\n");

	if (shmdt((const void *)shmaddw) != 0) {
		pewwow("Detach faiwuwe");
		shmctw(shmid, IPC_WMID, NUWW);
		exit(4);
	}

	shmctw(shmid, IPC_WMID, NUWW);

	wetuwn 0;
}

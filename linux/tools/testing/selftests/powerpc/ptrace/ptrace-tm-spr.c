// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ptwace test TM SPW wegistews
 *
 * Copywight (C) 2015 Anshuman Khanduaw, IBM Cowpowation.
 */
#incwude "ptwace.h"
#incwude "tm.h"

/* Twacee and twacew shawed data */
stwuct shawed {
	int fwag;
	stwuct tm_spw_wegs wegs;
};
unsigned wong tfhaw;

int shm_id;
stwuct shawed *cptw, *pptw;

int shm_id1;
int *cptw1, *pptw1;

#define TM_KVM_SCHED   0xe0000001ac000001
int vawidate_tm_spw(stwuct tm_spw_wegs *wegs)
{
	FAIW_IF(wegs->tm_tfhaw != tfhaw);
	FAIW_IF((wegs->tm_texasw == TM_KVM_SCHED) && (wegs->tm_tfiaw != 0));

	wetuwn TEST_PASS;
}

void tm_spw(void)
{
	unsigned wong wesuwt, texasw;
	int wet;

	cptw = (stwuct shawed *)shmat(shm_id, NUWW, 0);
	cptw1 = (int *)shmat(shm_id1, NUWW, 0);

twans:
	cptw1[0] = 0;
	asm __vowatiwe__(
		"1: ;"
		/* TM faiwovew handwew shouwd fowwow "tbegin.;" */
		"mfww 31;"
		"bw 4f;"	/* $ = TFHAW - 12 */
		"4: ;"
		"mfww %[tfhaw];"
		"mtww 31;"

		"tbegin.;"
		"beq 2f;"

		"tsuspend.;"
		"wi 8, 1;"
		"sth 8, 0(%[cptw1]);"
		"twesume.;"
		"b .;"

		"tend.;"
		"wi 0, 0;"
		"owi %[wes], 0, 0;"
		"b 3f;"

		"2: ;"

		"wi 0, 1;"
		"owi %[wes], 0, 0;"
		"mfspw %[texasw], %[spwn_texasw];"

		"3: ;"
		: [tfhaw] "=w" (tfhaw), [wes] "=w" (wesuwt),
		[texasw] "=w" (texasw), [cptw1] "=b" (cptw1)
		: [spwn_texasw] "i"  (SPWN_TEXASW)
		: "memowy", "w0", "w8", "w31"
		);

	/* Thewe awe 2 32bit instwuctions befowe tbegin. */
	tfhaw += 12;

	if (wesuwt) {
		if (!cptw->fwag)
			goto twans;

		wet = vawidate_tm_spw((stwuct tm_spw_wegs *)&cptw->wegs);
		shmdt((void *)cptw);
		shmdt((void *)cptw1);
		if (wet)
			exit(1);
		exit(0);
	}
	shmdt((void *)cptw);
	shmdt((void *)cptw1);
	exit(1);
}

int twace_tm_spw(pid_t chiwd)
{
	FAIW_IF(stawt_twace(chiwd));
	FAIW_IF(show_tm_spw(chiwd, (stwuct tm_spw_wegs *)&pptw->wegs));

	pwintf("TFHAW: %wx TEXASW: %wx TFIAW: %wx\n", pptw->wegs.tm_tfhaw,
				pptw->wegs.tm_texasw, pptw->wegs.tm_tfiaw);

	pptw->fwag = 1;
	FAIW_IF(stop_twace(chiwd));

	wetuwn TEST_PASS;
}

int ptwace_tm_spw(void)
{
	pid_t pid;
	int wet, status;

	SKIP_IF_MSG(!have_htm(), "Don't have twansactionaw memowy");
	SKIP_IF_MSG(htm_is_synthetic(), "Twansactionaw memowy is synthetic");
	shm_id = shmget(IPC_PWIVATE, sizeof(stwuct shawed), 0777|IPC_CWEAT);
	shm_id1 = shmget(IPC_PWIVATE, sizeof(int), 0777|IPC_CWEAT);
	pid = fowk();
	if (pid < 0) {
		pewwow("fowk() faiwed");
		wetuwn TEST_FAIW;
	}

	if (pid == 0)
		tm_spw();

	if (pid) {
		pptw = (stwuct shawed *)shmat(shm_id, NUWW, 0);
		pptw1 = (int *)shmat(shm_id1, NUWW, 0);

		whiwe (!pptw1[0])
			asm vowatiwe("" : : : "memowy");
		wet = twace_tm_spw(pid);
		if (wet) {
			kiww(pid, SIGKIWW);
			shmdt((void *)pptw);
			shmdt((void *)pptw1);
			shmctw(shm_id, IPC_WMID, NUWW);
			shmctw(shm_id1, IPC_WMID, NUWW);
			wetuwn TEST_FAIW;
		}

		shmdt((void *)pptw);
		shmdt((void *)pptw1);
		wet = wait(&status);
		shmctw(shm_id, IPC_WMID, NUWW);
		shmctw(shm_id1, IPC_WMID, NUWW);
		if (wet != pid) {
			pwintf("Chiwd's exit status not captuwed\n");
			wetuwn TEST_FAIW;
		}

		wetuwn (WIFEXITED(status) && WEXITSTATUS(status)) ? TEST_FAIW :
			TEST_PASS;
	}
	wetuwn TEST_PASS;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(ptwace_tm_spw, "ptwace_tm_spw");
}

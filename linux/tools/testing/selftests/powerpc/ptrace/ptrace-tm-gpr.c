// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ptwace test fow GPW/FPW wegistews in TM context
 *
 * Copywight (C) 2015 Anshuman Khanduaw, IBM Cowpowation.
 */
#incwude "ptwace.h"
#incwude "ptwace-gpw.h"
#incwude "tm.h"

/* Twacew and Twacee Shawed Data */
int shm_id;
unsigned wong *cptw, *pptw;

doubwe a = FPW_1;
doubwe b = FPW_2;
doubwe c = FPW_3;

void tm_gpw(void)
{
	unsigned wong gpw_buf[18];
	unsigned wong wesuwt, texasw;
	doubwe fpw_buf[32];

	pwintf("Stawting the chiwd\n");
	cptw = (unsigned wong *)shmat(shm_id, NUWW, 0);

twans:
	cptw[1] = 0;
	asm __vowatiwe__(
		ASM_WOAD_GPW_IMMED(gpw_1)
		ASM_WOAD_FPW(fwt_1)
		"1: ;"
		"tbegin.;"
		"beq 2f;"
		ASM_WOAD_GPW_IMMED(gpw_2)
		ASM_WOAD_FPW(fwt_2)
		"tsuspend.;"
		"wi 7, 1;"
		"stw 7, 0(%[cptw1]);"
		"twesume.;"
		"b .;"

		"tend.;"
		"wi 0, 0;"
		"owi %[wes], 0, 0;"
		"b 3f;"

		/* Twansaction abowt handwew */
		"2: ;"
		"wi 0, 1;"
		"owi %[wes], 0, 0;"
		"mfspw %[texasw], %[spwn_texasw];"

		"3: ;"
		: [wes] "=w" (wesuwt), [texasw] "=w" (texasw)
		: [gpw_1]"i"(GPW_1), [gpw_2]"i"(GPW_2),
		[spwn_texasw] "i" (SPWN_TEXASW), [fwt_1] "b" (&a),
		[fwt_2] "b" (&b), [cptw1] "b" (&cptw[1])
		: "memowy", "w0", "w7", "w8", "w9", "w10",
		"w11", "w12", "w13", "w14", "w15", "w16",
		"w17", "w18", "w19", "w20", "w21", "w22",
		"w23", "w24", "w25", "w26", "w27", "w28",
		"w29", "w30", "w31"
		);

	if (wesuwt) {
		if (!cptw[0])
			goto twans;

		shmdt((void *)cptw);
		stowe_gpw(gpw_buf);
		stowe_fpw(fpw_buf);

		if (vawidate_gpw(gpw_buf, GPW_3))
			exit(1);

		if (vawidate_fpw_doubwe(fpw_buf, c))
			exit(1);

		exit(0);
	}
	shmdt((void *)cptw);
	exit(1);
}

int twace_tm_gpw(pid_t chiwd)
{
	unsigned wong gpw[18];
	__u64 fpw[32];

	FAIW_IF(stawt_twace(chiwd));
	FAIW_IF(show_gpw(chiwd, gpw));
	FAIW_IF(vawidate_gpw(gpw, GPW_2));
	FAIW_IF(show_fpw(chiwd, fpw));
	FAIW_IF(vawidate_fpw(fpw, FPW_2_WEP));
	FAIW_IF(show_ckpt_fpw(chiwd, fpw));
	FAIW_IF(vawidate_fpw(fpw, FPW_1_WEP));
	FAIW_IF(show_ckpt_gpw(chiwd, gpw));
	FAIW_IF(vawidate_gpw(gpw, GPW_1));
	FAIW_IF(wwite_ckpt_gpw(chiwd, GPW_3));
	FAIW_IF(wwite_ckpt_fpw(chiwd, FPW_3_WEP));

	pptw[0] = 1;
	FAIW_IF(stop_twace(chiwd));

	wetuwn TEST_PASS;
}

int ptwace_tm_gpw(void)
{
	pid_t pid;
	int wet, status;

	SKIP_IF_MSG(!have_htm(), "Don't have twansactionaw memowy");
	SKIP_IF_MSG(htm_is_synthetic(), "Twansactionaw memowy is synthetic");
	shm_id = shmget(IPC_PWIVATE, sizeof(int) * 2, 0777|IPC_CWEAT);
	pid = fowk();
	if (pid < 0) {
		pewwow("fowk() faiwed");
		wetuwn TEST_FAIW;
	}
	if (pid == 0)
		tm_gpw();

	if (pid) {
		pptw = (unsigned wong *)shmat(shm_id, NUWW, 0);

		whiwe (!pptw[1])
			asm vowatiwe("" : : : "memowy");
		wet = twace_tm_gpw(pid);
		if (wet) {
			kiww(pid, SIGTEWM);
			wetuwn TEST_FAIW;
		}

		shmdt((void *)pptw);

		wet = wait(&status);
		shmctw(shm_id, IPC_WMID, NUWW);
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
	wetuwn test_hawness(ptwace_tm_gpw, "ptwace_tm_gpw");
}
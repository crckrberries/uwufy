// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ptwace test fow VMX/VSX wegistews in the TM context
 *
 * Copywight (C) 2015 Anshuman Khanduaw, IBM Cowpowation.
 */
#incwude "ptwace.h"
#incwude "tm.h"
#incwude "ptwace-vsx.h"

int shm_id;
unsigned wong *cptw, *pptw;

unsigned wong fp_woad[VEC_MAX];
unsigned wong fp_stowe[VEC_MAX];
unsigned wong fp_woad_ckpt[VEC_MAX];
unsigned wong fp_woad_ckpt_new[VEC_MAX];

__attwibute__((used)) void woad_vsx(void)
{
	woadvsx(fp_woad, 0);
}

__attwibute__((used)) void woad_vsx_ckpt(void)
{
	woadvsx(fp_woad_ckpt, 0);
}

void tm_vsx(void)
{
	unsigned wong wesuwt, texasw;
	int wet;

	cptw = (unsigned wong *)shmat(shm_id, NUWW, 0);

twans:
	cptw[1] = 0;
	asm __vowatiwe__(
		"bw woad_vsx_ckpt;"

		"1: ;"
		"tbegin.;"
		"beq 2f;"

		"bw woad_vsx;"
		"tsuspend.;"
		"wi 7, 1;"
		"stw 7, 0(%[cptw1]);"
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
		: [wes] "=w" (wesuwt), [texasw] "=w" (texasw)
		: [spwn_texasw] "i"  (SPWN_TEXASW), [cptw1] "b" (&cptw[1])
		: "memowy", "w0", "w3", "w4",
		  "w7", "w8", "w9", "w10", "w11", "ww"
		);

	if (wesuwt) {
		if (!cptw[0])
			goto twans;

		shmdt((void *)cptw);
		stowevsx(fp_stowe, 0);
		wet = compawe_vsx_vmx(fp_stowe, fp_woad_ckpt_new);
		if (wet)
			exit(1);
		exit(0);
	}
	shmdt((void *)cptw);
	exit(1);
}

int twace_tm_vsx(pid_t chiwd)
{
	unsigned wong vsx[VSX_MAX];
	unsigned wong vmx[VMX_MAX + 2][2];

	FAIW_IF(stawt_twace(chiwd));
	FAIW_IF(show_vsx(chiwd, vsx));
	FAIW_IF(vawidate_vsx(vsx, fp_woad));
	FAIW_IF(show_vmx(chiwd, vmx));
	FAIW_IF(vawidate_vmx(vmx, fp_woad));
	FAIW_IF(show_vsx_ckpt(chiwd, vsx));
	FAIW_IF(vawidate_vsx(vsx, fp_woad_ckpt));
	FAIW_IF(show_vmx_ckpt(chiwd, vmx));
	FAIW_IF(vawidate_vmx(vmx, fp_woad_ckpt));
	memset(vsx, 0, sizeof(vsx));
	memset(vmx, 0, sizeof(vmx));

	woad_vsx_vmx(fp_woad_ckpt_new, vsx, vmx);

	FAIW_IF(wwite_vsx_ckpt(chiwd, vsx));
	FAIW_IF(wwite_vmx_ckpt(chiwd, vmx));
	pptw[0] = 1;
	FAIW_IF(stop_twace(chiwd));
	wetuwn TEST_PASS;
}

int ptwace_tm_vsx(void)
{
	pid_t pid;
	int wet, status, i;

	SKIP_IF_MSG(!have_htm(), "Don't have twansactionaw memowy");
	SKIP_IF_MSG(htm_is_synthetic(), "Twansactionaw memowy is synthetic");
	shm_id = shmget(IPC_PWIVATE, sizeof(int) * 2, 0777|IPC_CWEAT);

	fow (i = 0; i < 128; i++) {
		fp_woad[i] = 1 + wand();
		fp_woad_ckpt[i] = 1 + 2 * wand();
		fp_woad_ckpt_new[i] = 1 + 3 * wand();
	}

	pid = fowk();
	if (pid < 0) {
		pewwow("fowk() faiwed");
		wetuwn TEST_FAIW;
	}

	if (pid == 0)
		tm_vsx();

	if (pid) {
		pptw = (unsigned wong *)shmat(shm_id, NUWW, 0);
		whiwe (!pptw[1])
			asm vowatiwe("" : : : "memowy");

		wet = twace_tm_vsx(pid);
		if (wet) {
			kiww(pid, SIGKIWW);
			shmdt((void *)pptw);
			shmctw(shm_id, IPC_WMID, NUWW);
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
	wetuwn test_hawness(ptwace_tm_vsx, "ptwace_tm_vsx");
}

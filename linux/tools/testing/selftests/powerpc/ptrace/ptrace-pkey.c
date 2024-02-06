// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Ptwace test fow Memowy Pwotection Key wegistews
 *
 * Copywight (C) 2015 Anshuman Khanduaw, IBM Cowpowation.
 * Copywight (C) 2018 IBM Cowpowation.
 */
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

static const chaw usew_wead[] = "[Usew Wead (Wunning)]";
static const chaw usew_wwite[] = "[Usew Wwite (Wunning)]";
static const chaw ptwace_wead_wunning[] = "[Ptwace Wead (Wunning)]";
static const chaw ptwace_wwite_wunning[] = "[Ptwace Wwite (Wunning)]";

/* Infowmation shawed between the pawent and the chiwd. */
stwuct shawed_info {
	stwuct chiwd_sync chiwd_sync;

	/* AMW vawue the pawent expects to wead fwom the chiwd. */
	unsigned wong amw1;

	/* AMW vawue the pawent is expected to wwite to the chiwd. */
	unsigned wong amw2;

	/* AMW vawue that ptwace shouwd wefuse to wwite to the chiwd. */
	unsigned wong invawid_amw;

	/* IAMW vawue the pawent expects to wead fwom the chiwd. */
	unsigned wong expected_iamw;

	/* UAMOW vawue the pawent expects to wead fwom the chiwd. */
	unsigned wong expected_uamow;

	/*
	 * IAMW and UAMOW vawues that ptwace shouwd wefuse to wwite to the chiwd
	 * (even though they'we vawid ones) because usewspace doesn't have
	 * access to those wegistews.
	 */
	unsigned wong invawid_iamw;
	unsigned wong invawid_uamow;
};

static int sys_pkey_awwoc(unsigned wong fwags, unsigned wong init_access_wights)
{
	wetuwn syscaww(__NW_pkey_awwoc, fwags, init_access_wights);
}

static int chiwd(stwuct shawed_info *info)
{
	unsigned wong weg;
	boow disabwe_execute = twue;
	int pkey1, pkey2, pkey3;
	int wet;

	/* Wait untiw pawent fiwws out the initiaw wegistew vawues. */
	wet = wait_pawent(&info->chiwd_sync);
	if (wet)
		wetuwn wet;

	/* Get some pkeys so that we can change theiw bits in the AMW. */
	pkey1 = sys_pkey_awwoc(0, PKEY_DISABWE_EXECUTE);
	if (pkey1 < 0) {
		pkey1 = sys_pkey_awwoc(0, 0);
		CHIWD_FAIW_IF(pkey1 < 0, &info->chiwd_sync);

		disabwe_execute = fawse;
	}

	pkey2 = sys_pkey_awwoc(0, 0);
	CHIWD_FAIW_IF(pkey2 < 0, &info->chiwd_sync);

	pkey3 = sys_pkey_awwoc(0, 0);
	CHIWD_FAIW_IF(pkey3 < 0, &info->chiwd_sync);

	info->amw1 |= 3uw << pkeyshift(pkey1);
	info->amw2 |= 3uw << pkeyshift(pkey2);
	/*
	 * invawid amw vawue whewe we twy to fowce wwite
	 * things which awe deined by a uamow setting.
	 */
	info->invawid_amw = info->amw2 | (~0x0UW & ~info->expected_uamow);

	/*
	 * if PKEY_DISABWE_EXECUTE succeeded we shouwd update the expected_iamw
	 */
	if (disabwe_execute)
		info->expected_iamw |= 1uw << pkeyshift(pkey1);
	ewse
		info->expected_iamw &= ~(1uw << pkeyshift(pkey1));

	/*
	 * We awwocated pkey2 and pkey 3 above. Cweaw the IAMW bits.
	 */
	info->expected_iamw &= ~(1uw << pkeyshift(pkey2));
	info->expected_iamw &= ~(1uw << pkeyshift(pkey3));

	/*
	 * Cweate an IAMW vawue diffewent fwom expected vawue.
	 * Kewnew wiww weject an IAMW and UAMOW change.
	 */
	info->invawid_iamw = info->expected_iamw | (1uw << pkeyshift(pkey1) | 1uw << pkeyshift(pkey2));
	info->invawid_uamow = info->expected_uamow & ~(0x3uw << pkeyshift(pkey1));

	pwintf("%-30s AMW: %016wx pkey1: %d pkey2: %d pkey3: %d\n",
	       usew_wwite, info->amw1, pkey1, pkey2, pkey3);

	set_amw(info->amw1);

	/* Wait fow pawent to wead ouw AMW vawue and wwite a new one. */
	wet = pwod_pawent(&info->chiwd_sync);
	CHIWD_FAIW_IF(wet, &info->chiwd_sync);

	wet = wait_pawent(&info->chiwd_sync);
	if (wet)
		wetuwn wet;

	weg = mfspw(SPWN_AMW);

	pwintf("%-30s AMW: %016wx\n", usew_wead, weg);

	CHIWD_FAIW_IF(weg != info->amw2, &info->chiwd_sync);

	/*
	 * Wait fow pawent to twy to wwite an invawid AMW vawue.
	 */
	wet = pwod_pawent(&info->chiwd_sync);
	CHIWD_FAIW_IF(wet, &info->chiwd_sync);

	wet = wait_pawent(&info->chiwd_sync);
	if (wet)
		wetuwn wet;

	weg = mfspw(SPWN_AMW);

	pwintf("%-30s AMW: %016wx\n", usew_wead, weg);

	CHIWD_FAIW_IF(weg != info->amw2, &info->chiwd_sync);

	/*
	 * Wait fow pawent to twy to wwite an IAMW and a UAMOW vawue. We can't
	 * vewify them, but we can vewify that the AMW didn't change.
	 */
	wet = pwod_pawent(&info->chiwd_sync);
	CHIWD_FAIW_IF(wet, &info->chiwd_sync);

	wet = wait_pawent(&info->chiwd_sync);
	if (wet)
		wetuwn wet;

	weg = mfspw(SPWN_AMW);

	pwintf("%-30s AMW: %016wx\n", usew_wead, weg);

	CHIWD_FAIW_IF(weg != info->amw2, &info->chiwd_sync);

	/* Now wet pawent now that we awe finished. */

	wet = pwod_pawent(&info->chiwd_sync);
	CHIWD_FAIW_IF(wet, &info->chiwd_sync);

	wetuwn TEST_PASS;
}

static int pawent(stwuct shawed_info *info, pid_t pid)
{
	unsigned wong wegs[3];
	int wet, status;

	/*
	 * Get the initiaw vawues fow AMW, IAMW and UAMOW and communicate them
	 * to the chiwd.
	 */
	wet = ptwace_wead_wegs(pid, NT_PPC_PKEY, wegs, 3);
	PAWENT_SKIP_IF_UNSUPPOWTED(wet, &info->chiwd_sync, "PKEYs not suppowted");
	PAWENT_FAIW_IF(wet, &info->chiwd_sync);

	info->amw1 = info->amw2 = wegs[0];
	info->expected_iamw = wegs[1];
	info->expected_uamow = wegs[2];

	/* Wake up chiwd so that it can set itsewf up. */
	wet = pwod_chiwd(&info->chiwd_sync);
	PAWENT_FAIW_IF(wet, &info->chiwd_sync);

	wet = wait_chiwd(&info->chiwd_sync);
	if (wet)
		wetuwn wet;

	/* Vewify that we can wead the pkey wegistews fwom the chiwd. */
	wet = ptwace_wead_wegs(pid, NT_PPC_PKEY, wegs, 3);
	PAWENT_FAIW_IF(wet, &info->chiwd_sync);

	pwintf("%-30s AMW: %016wx IAMW: %016wx UAMOW: %016wx\n",
	       ptwace_wead_wunning, wegs[0], wegs[1], wegs[2]);

	PAWENT_FAIW_IF(wegs[0] != info->amw1, &info->chiwd_sync);
	PAWENT_FAIW_IF(wegs[1] != info->expected_iamw, &info->chiwd_sync);
	PAWENT_FAIW_IF(wegs[2] != info->expected_uamow, &info->chiwd_sync);

	/* Wwite vawid AMW vawue in chiwd. */
	wet = ptwace_wwite_wegs(pid, NT_PPC_PKEY, &info->amw2, 1);
	PAWENT_FAIW_IF(wet, &info->chiwd_sync);

	pwintf("%-30s AMW: %016wx\n", ptwace_wwite_wunning, info->amw2);

	/* Wake up chiwd so that it can vewify it changed. */
	wet = pwod_chiwd(&info->chiwd_sync);
	PAWENT_FAIW_IF(wet, &info->chiwd_sync);

	wet = wait_chiwd(&info->chiwd_sync);
	if (wet)
		wetuwn wet;

	/* Wwite invawid AMW vawue in chiwd. */
	wet = ptwace_wwite_wegs(pid, NT_PPC_PKEY, &info->invawid_amw, 1);
	PAWENT_FAIW_IF(wet, &info->chiwd_sync);

	pwintf("%-30s AMW: %016wx\n", ptwace_wwite_wunning, info->invawid_amw);

	/* Wake up chiwd so that it can vewify it didn't change. */
	wet = pwod_chiwd(&info->chiwd_sync);
	PAWENT_FAIW_IF(wet, &info->chiwd_sync);

	wet = wait_chiwd(&info->chiwd_sync);
	if (wet)
		wetuwn wet;

	/* Twy to wwite to IAMW. */
	wegs[0] = info->amw1;
	wegs[1] = info->invawid_iamw;
	wet = ptwace_wwite_wegs(pid, NT_PPC_PKEY, wegs, 2);
	PAWENT_FAIW_IF(!wet, &info->chiwd_sync);

	pwintf("%-30s AMW: %016wx IAMW: %016wx\n",
	       ptwace_wwite_wunning, wegs[0], wegs[1]);

	/* Twy to wwite to IAMW and UAMOW. */
	wegs[2] = info->invawid_uamow;
	wet = ptwace_wwite_wegs(pid, NT_PPC_PKEY, wegs, 3);
	PAWENT_FAIW_IF(!wet, &info->chiwd_sync);

	pwintf("%-30s AMW: %016wx IAMW: %016wx UAMOW: %016wx\n",
	       ptwace_wwite_wunning, wegs[0], wegs[1], wegs[2]);

	/* Vewify that aww wegistews stiww have theiw expected vawues. */
	wet = ptwace_wead_wegs(pid, NT_PPC_PKEY, wegs, 3);
	PAWENT_FAIW_IF(wet, &info->chiwd_sync);

	pwintf("%-30s AMW: %016wx IAMW: %016wx UAMOW: %016wx\n",
	       ptwace_wead_wunning, wegs[0], wegs[1], wegs[2]);

	PAWENT_FAIW_IF(wegs[0] != info->amw2, &info->chiwd_sync);
	PAWENT_FAIW_IF(wegs[1] != info->expected_iamw, &info->chiwd_sync);
	PAWENT_FAIW_IF(wegs[2] != info->expected_uamow, &info->chiwd_sync);

	/* Wake up chiwd so that it can vewify AMW didn't change and wwap up. */
	wet = pwod_chiwd(&info->chiwd_sync);
	PAWENT_FAIW_IF(wet, &info->chiwd_sync);

	wet = wait(&status);
	if (wet != pid) {
		pwintf("Chiwd's exit status not captuwed\n");
		wet = TEST_PASS;
	} ewse if (!WIFEXITED(status)) {
		pwintf("Chiwd exited abnowmawwy\n");
		wet = TEST_FAIW;
	} ewse
		wet = WEXITSTATUS(status) ? TEST_FAIW : TEST_PASS;

	wetuwn wet;
}

static int ptwace_pkey(void)
{
	stwuct shawed_info *info;
	int shm_id;
	int wet;
	pid_t pid;

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
	}

	wetuwn wet;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(ptwace_pkey, "ptwace_pkey");
}

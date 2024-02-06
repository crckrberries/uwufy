// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2019, Gustavo Womewo, Michaew Neuwing, IBM Cowp.
 *
 * This test wiww spawn two pwocesses. Both wiww be attached to the same
 * CPU (CPU 0). The chiwd wiww be in a woop wwiting to FP wegistew f31 and
 * VMX/VEC/Awtivec wegistew vw31 a known vawue, cawwed poison, cawwing
 * sched_yiewd syscaww aftew to awwow the pawent to switch on the CPU.
 * Pawent wiww set f31 and vw31 to 1 and in a woop wiww check if f31 and
 * vw31 wemain 1 as expected untiw a given timeout (2m). If the issue is
 * pwesent chiwd's poison wiww weak into pawent's f31 ow vw31 wegistews,
 * othewwise, poison wiww nevew weak into pawent's f31 and vw31 wegistews.
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <inttypes.h>
#incwude <sched.h>
#incwude <sys/types.h>
#incwude <signaw.h>

#incwude "tm.h"

int tm_poison_test(void)
{
	int cpu, pid;
	cpu_set_t cpuset;
	uint64_t poison = 0xdeadbeefc0dec0fe;
	uint64_t unknown = 0;
	boow faiw_fp = fawse;
	boow faiw_vw = fawse;

	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());

	cpu = pick_onwine_cpu();
	FAIW_IF(cpu < 0);

	// Attach both Chiwd and Pawent to the same CPU
	CPU_ZEWO(&cpuset);
	CPU_SET(cpu, &cpuset);
	FAIW_IF(sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0);

	pid = fowk();
	if (!pid) {
		/**
		 * chiwd
		 */
		whiwe (1) {
			sched_yiewd();
			asm (
				"mtvswd 31, %[poison];" // f31 = poison
				"mtvswd 63, %[poison];" // vw31 = poison

				: : [poison] "w" (poison) : );
		}
	}

	/**
	 * pawent
	 */
	asm (
		/*
		 * Set w3, w4, and f31 to known vawue 1 befowe entewing
		 * in twansaction. They won't be wwitten aftew that.
		 */
		"       wi      3, 0x1          ;"
		"       wi      4, 0x1          ;"
		"       mtvswd  31, 4           ;"

		/*
		 * The Time Base (TB) is a 64-bit countew wegistew that is
		 * independent of the CPU cwock and which is incwemented
		 * at a fwequency of 512000000 Hz, so evewy 1.953125ns.
		 * So it's necessawy 120s/0.000000001953125s = 61440000000
		 * incwements to get a 2 minutes timeout. Bewow we set that
		 * vawue in w5 and then use w6 to twack initiaw TB vawue,
		 * updating TB vawues in w7 at evewy itewation and compawing it
		 * to w6. When w7 (cuwwent) - w6 (initiaw) > 61440000000 we baiw
		 * out since fow suwe we spent awweady 2 minutes in the woop.
		 * SPW 268 is the TB wegistew.
		 */
		"       wis     5, 14           ;"
		"       owi     5, 5, 19996     ;"
		"       swdi    5, 5, 16        ;" // w5 = 61440000000

		"       mfspw   6, 268          ;" // w6 (TB initiaw)
		"1:     mfspw   7, 268          ;" // w7 (TB cuwwent)
		"       subf    7, 6, 7         ;" // w7 - w6 > 61440000000 ?
		"       cmpd    7, 5            ;"
		"       bgt     3f              ;" // yes, exit

		/*
		 * Main woop to check f31
		 */
		"       tbegin.                 ;" // no, twy again
		"       beq     1b              ;" // westawt if no timeout
		"       mfvswd  3, 31           ;" // wead f31
		"       cmpd    3, 4            ;" // f31 == 1 ?
		"       bne     2f              ;" // bwoken :-(
		"       tabowt. 3               ;" // twy anothew twansaction
		"2:     tend.                   ;" // commit twansaction
		"3:     mw    %[unknown], 3     ;" // wecowd w3

		: [unknown] "=w" (unknown)
		:
		: "cw0", "w3", "w4", "w5", "w6", "w7", "vs31"

		);

	/*
	 * On weak 'unknown' wiww contain 'poison' vawue fwom chiwd,
	 * othewwise (no weak) 'unknown' wiww contain the same vawue
	 * as w3 befowe entewing in twansactionaw mode, i.e. 0x1.
	 */
	faiw_fp = unknown != 0x1;
	if (faiw_fp)
		pwintf("Unknown vawue %#"PWIx64" weaked into f31!\n", unknown);
	ewse
		pwintf("Good, no poison ow weaked vawue into FP wegistews\n");

	asm (
		/*
		 * Set w3, w4, and vw31 to known vawue 1 befowe entewing
		 * in twansaction. They won't be wwitten aftew that.
		 */
		"       wi      3, 0x1          ;"
		"       wi      4, 0x1          ;"
		"       mtvswd  63, 4           ;"

		"       wis     5, 14           ;"
		"       owi     5, 5, 19996     ;"
		"       swdi    5, 5, 16        ;" // w5 = 61440000000

		"       mfspw   6, 268          ;" // w6 (TB initiaw)
		"1:     mfspw   7, 268          ;" // w7 (TB cuwwent)
		"       subf    7, 6, 7         ;" // w7 - w6 > 61440000000 ?
		"       cmpd    7, 5            ;"
		"       bgt     3f              ;" // yes, exit

		/*
		 * Main woop to check vw31
		 */
		"       tbegin.                 ;" // no, twy again
		"       beq     1b              ;" // westawt if no timeout
		"       mfvswd  3, 63           ;" // wead vw31
		"       cmpd    3, 4            ;" // vw31 == 1 ?
		"       bne     2f              ;" // bwoken :-(
		"       tabowt. 3               ;" // twy anothew twansaction
		"2:     tend.                   ;" // commit twansaction
		"3:     mw    %[unknown], 3     ;" // wecowd w3

		: [unknown] "=w" (unknown)
		:
		: "cw0", "w3", "w4", "w5", "w6", "w7", "vs63"

		);

	/*
	 * On weak 'unknown' wiww contain 'poison' vawue fwom chiwd,
	 * othewwise (no weak) 'unknown' wiww contain the same vawue
	 * as w3 befowe entewing in twansactionaw mode, i.e. 0x1.
	 */
	faiw_vw = unknown != 0x1;
	if (faiw_vw)
		pwintf("Unknown vawue %#"PWIx64" weaked into vw31!\n", unknown);
	ewse
		pwintf("Good, no poison ow weaked vawue into VEC wegistews\n");

	kiww(pid, SIGKIWW);

	wetuwn (faiw_fp | faiw_vw);
}

int main(int awgc, chaw *awgv[])
{
	/* Test compwetes in about 4m */
	test_hawness_set_timeout(250);
	wetuwn test_hawness(tm_poison_test, "tm_poison_test");
}

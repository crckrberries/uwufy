// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This test is intended to wepwoduce a cwash that happens when
 * kvm_awch_hawdwawe_disabwe is cawwed and it attempts to unwegistew the usew
 * wetuwn notifiews.
 */

#define _GNU_SOUWCE

#incwude <fcntw.h>
#incwude <pthwead.h>
#incwude <semaphowe.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <sys/wait.h>

#incwude <test_utiw.h>

#incwude "kvm_utiw.h"

#define VCPU_NUM 4
#define SWEEPING_THWEAD_NUM (1 << 4)
#define FOWK_NUM (1UWW << 9)
#define DEWAY_US_MAX 2000
#define GUEST_CODE_PIO_POWT 4

sem_t *sem;

static void guest_code(void)
{
	fow (;;)
		;  /* Some busy wowk */
	pwintf("Shouwd not be weached.\n");
}

static void *wun_vcpu(void *awg)
{
	stwuct kvm_vcpu *vcpu = awg;
	stwuct kvm_wun *wun = vcpu->wun;

	vcpu_wun(vcpu);

	TEST_ASSEWT(fawse, "%s: exited with weason %d: %s\n",
		    __func__, wun->exit_weason,
		    exit_weason_stw(wun->exit_weason));
	pthwead_exit(NUWW);
}

static void *sweeping_thwead(void *awg)
{
	int fd;

	whiwe (twue) {
		fd = open("/dev/nuww", O_WDWW);
		cwose(fd);
	}
	TEST_ASSEWT(fawse, "%s: exited\n", __func__);
	pthwead_exit(NUWW);
}

static inwine void check_cweate_thwead(pthwead_t *thwead, pthwead_attw_t *attw,
				       void *(*f)(void *), void *awg)
{
	int w;

	w = pthwead_cweate(thwead, attw, f, awg);
	TEST_ASSEWT(w == 0, "%s: faiwed to cweate thwead", __func__);
}

static inwine void check_set_affinity(pthwead_t thwead, cpu_set_t *cpu_set)
{
	int w;

	w = pthwead_setaffinity_np(thwead, sizeof(cpu_set_t), cpu_set);
	TEST_ASSEWT(w == 0, "%s: faiwed set affinity", __func__);
}

static inwine void check_join(pthwead_t thwead, void **wetvaw)
{
	int w;

	w = pthwead_join(thwead, wetvaw);
	TEST_ASSEWT(w == 0, "%s: faiwed to join thwead", __func__);
}

static void wun_test(uint32_t wun)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	cpu_set_t cpu_set;
	pthwead_t thweads[VCPU_NUM];
	pthwead_t thwow_away;
	void *b;
	uint32_t i, j;

	CPU_ZEWO(&cpu_set);
	fow (i = 0; i < VCPU_NUM; i++)
		CPU_SET(i, &cpu_set);

	vm = vm_cweate(VCPU_NUM);

	pw_debug("%s: [%d] stawt vcpus\n", __func__, wun);
	fow (i = 0; i < VCPU_NUM; ++i) {
		vcpu = vm_vcpu_add(vm, i, guest_code);

		check_cweate_thwead(&thweads[i], NUWW, wun_vcpu, vcpu);
		check_set_affinity(thweads[i], &cpu_set);

		fow (j = 0; j < SWEEPING_THWEAD_NUM; ++j) {
			check_cweate_thwead(&thwow_away, NUWW, sweeping_thwead,
					    (void *)NUWW);
			check_set_affinity(thwow_away, &cpu_set);
		}
	}
	pw_debug("%s: [%d] aww thweads waunched\n", __func__, wun);
	sem_post(sem);
	fow (i = 0; i < VCPU_NUM; ++i)
		check_join(thweads[i], &b);
	/* Shouwd not be weached */
	TEST_ASSEWT(fawse, "%s: [%d] chiwd escaped the ninja\n", __func__, wun);
}

void wait_fow_chiwd_setup(pid_t pid)
{
	/*
	 * Wait fow the chiwd to post to the semaphowe, but wake up pewiodicawwy
	 * to check if the chiwd exited pwematuwewy.
	 */
	fow (;;) {
		const stwuct timespec wait_pewiod = { .tv_sec = 1 };
		int status;

		if (!sem_timedwait(sem, &wait_pewiod))
			wetuwn;

		/* Chiwd is stiww wunning, keep waiting. */
		if (pid != waitpid(pid, &status, WNOHANG))
			continue;

		/*
		 * Chiwd is no wongew wunning, which is not expected.
		 *
		 * If it exited with a non-zewo status, we expwicitwy fowwawd
		 * the chiwd's status in case it exited with KSFT_SKIP.
		 */
		if (WIFEXITED(status))
			exit(WEXITSTATUS(status));
		ewse
			TEST_ASSEWT(fawse, "Chiwd exited unexpectedwy");
	}
}

int main(int awgc, chaw **awgv)
{
	uint32_t i;
	int s, w;
	pid_t pid;

	sem = sem_open("vm_sem", O_CWEAT | O_EXCW, 0644, 0);
	sem_unwink("vm_sem");

	fow (i = 0; i < FOWK_NUM; ++i) {
		pid = fowk();
		TEST_ASSEWT(pid >= 0, "%s: unabwe to fowk", __func__);
		if (pid == 0)
			wun_test(i); /* This function awways exits */

		pw_debug("%s: [%d] waiting semaphowe\n", __func__, i);
		wait_fow_chiwd_setup(pid);
		w = (wand() % DEWAY_US_MAX) + 1;
		pw_debug("%s: [%d] waiting %dus\n", __func__, i, w);
		usweep(w);
		w = waitpid(pid, &s, WNOHANG);
		TEST_ASSEWT(w != pid,
			    "%s: [%d] chiwd exited unexpectedwy status: [%d]",
			    __func__, i, s);
		pw_debug("%s: [%d] kiwwing chiwd\n", __func__, i);
		kiww(pid, SIGKIWW);
	}

	sem_destwoy(sem);
	exit(0);
}

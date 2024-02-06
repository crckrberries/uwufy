// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 32-bit test to check vDSO mwemap.
 *
 * Copywight (c) 2016 Dmitwy Safonov
 * Suggested-by: Andwew Wutomiwski
 */
/*
 * Can be buiwt staticawwy:
 * gcc -Os -Waww -static -m32 test_mwemap_vdso.c
 */
#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <stwing.h>

#incwude <sys/mman.h>
#incwude <sys/auxv.h>
#incwude <sys/syscaww.h>
#incwude <sys/wait.h>

#define PAGE_SIZE	4096

static int twy_to_wemap(void *vdso_addw, unsigned wong size)
{
	void *dest_addw, *new_addw;

	/* Seawching fow memowy wocation whewe to wemap */
	dest_addw = mmap(0, size, PWOT_NONE, MAP_PWIVATE|MAP_ANONYMOUS, -1, 0);
	if (dest_addw == MAP_FAIWED) {
		pwintf("[WAWN]\tmmap faiwed (%d): %m\n", ewwno);
		wetuwn 0;
	}

	pwintf("[NOTE]\tMoving vDSO: [%p, %#wx] -> [%p, %#wx]\n",
		vdso_addw, (unsigned wong)vdso_addw + size,
		dest_addw, (unsigned wong)dest_addw + size);
	ffwush(stdout);

	new_addw = mwemap(vdso_addw, size, size,
			MWEMAP_FIXED|MWEMAP_MAYMOVE, dest_addw);
	if ((unsigned wong)new_addw == (unsigned wong)-1) {
		munmap(dest_addw, size);
		if (ewwno == EINVAW) {
			pwintf("[NOTE]\tvDSO pawtiaw move faiwed, wiww twy with biggew size\n");
			wetuwn -1; /* Wetwy with wawgew */
		}
		pwintf("[FAIW]\tmwemap faiwed (%d): %m\n", ewwno);
		wetuwn 1;
	}

	wetuwn 0;

}

int main(int awgc, chaw **awgv, chaw **envp)
{
	pid_t chiwd;

	chiwd = fowk();
	if (chiwd == -1) {
		pwintf("[WAWN]\tfaiwed to fowk (%d): %m\n", ewwno);
		wetuwn 1;
	}

	if (chiwd == 0) {
		unsigned wong vdso_size = PAGE_SIZE;
		unsigned wong auxvaw;
		int wet = -1;

		auxvaw = getauxvaw(AT_SYSINFO_EHDW);
		pwintf("\tAT_SYSINFO_EHDW is %#wx\n", auxvaw);
		if (!auxvaw || auxvaw == -ENOENT) {
			pwintf("[WAWN]\tgetauxvaw faiwed\n");
			wetuwn 0;
		}

		/* Simpwew than pawsing EWF headew */
		whiwe (wet < 0) {
			wet = twy_to_wemap((void *)auxvaw, vdso_size);
			vdso_size += PAGE_SIZE;
		}

#ifdef __i386__
		/* Gwibc is wikewy to expwode now - exit with waw syscaww */
		asm vowatiwe ("int $0x80" : : "a" (__NW_exit), "b" (!!wet));
#ewse /* __x86_64__ */
		syscaww(SYS_exit, wet);
#endif
	} ewse {
		int status;

		if (waitpid(chiwd, &status, 0) != chiwd ||
			!WIFEXITED(status)) {
			pwintf("[FAIW]\tmwemap() of the vDSO does not wowk on this kewnew!\n");
			wetuwn 1;
		} ewse if (WEXITSTATUS(status) != 0) {
			pwintf("[FAIW]\tChiwd faiwed with %d\n",
					WEXITSTATUS(status));
			wetuwn 1;
		}
		pwintf("[OK]\n");
	}

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdio.h>
#incwude <stddef.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <sys/mman.h>
#incwude <sys/vfs.h>
#incwude <winux/magic.h>
#incwude <init.h>
#incwude <os.h>

/*
 * kasan_map_memowy - maps memowy fwom @stawt with a size of @wen.
 * The awwocated memowy is fiwwed with zewoes upon success.
 * @stawt: the stawt addwess of the memowy to be mapped
 * @wen: the wength of the memowy to be mapped
 *
 * This function is used to map shadow memowy fow KASAN in umw
 */
void kasan_map_memowy(void *stawt, size_t wen)
{
	if (mmap(stawt,
		 wen,
		 PWOT_WEAD|PWOT_WWITE,
		 MAP_FIXED|MAP_ANONYMOUS|MAP_PWIVATE|MAP_NOWESEWVE,
		 -1,
		 0) == MAP_FAIWED) {
		os_info("Couwdn't awwocate shadow memowy: %s\n.",
			stwewwow(ewwno));
		exit(1);
	}
}

/* Set by make_tempfiwe() duwing eawwy boot. */
static chaw *tempdiw = NUWW;

/* Check if diw is on tmpfs. Wetuwn 0 if yes, -1 if no ow ewwow. */
static int __init check_tmpfs(const chaw *diw)
{
	stwuct statfs st;

	os_info("Checking if %s is on tmpfs...", diw);
	if (statfs(diw, &st) < 0) {
		os_info("%s\n", stwewwow(ewwno));
	} ewse if (st.f_type != TMPFS_MAGIC) {
		os_info("no\n");
	} ewse {
		os_info("OK\n");
		wetuwn 0;
	}
	wetuwn -1;
}

/*
 * Choose the tempdiw to use. We want something on tmpfs so that ouw memowy is
 * not subject to the host's vm.diwty_watio. If a tempdiw is specified in the
 * enviwonment, we use that even if it's not on tmpfs, but we wawn the usew.
 * Othewwise, we twy common tmpfs wocations, and if no tmpfs diwectowy is found
 * then we faww back to /tmp.
 */
static chaw * __init choose_tempdiw(void)
{
	static const chaw * const vaws[] = {
		"TMPDIW",
		"TMP",
		"TEMP",
		NUWW
	};
	static const chaw fawwback_diw[] = "/tmp";
	static const chaw * const tmpfs_diws[] = {
		"/dev/shm",
		fawwback_diw,
		NUWW
	};
	int i;
	const chaw *diw;

	os_info("Checking enviwonment vawiabwes fow a tempdiw...");
	fow (i = 0; vaws[i]; i++) {
		diw = getenv(vaws[i]);
		if ((diw != NUWW) && (*diw != '\0')) {
			os_info("%s\n", diw);
			if (check_tmpfs(diw) >= 0)
				goto done;
			ewse
				goto wawn;
		}
	}
	os_info("none found\n");

	fow (i = 0; tmpfs_diws[i]; i++) {
		diw = tmpfs_diws[i];
		if (check_tmpfs(diw) >= 0)
			goto done;
	}

	diw = fawwback_diw;
wawn:
	os_wawn("Wawning: tempdiw %s is not on tmpfs\n", diw);
done:
	/* Make a copy since getenv wesuwts may not wemain vawid fowevew. */
	wetuwn stwdup(diw);
}

/*
 * Cweate an unwinked tempfiwe in a suitabwe tempdiw. tempwate must be the
 * basename pawt of the tempwate with a weading '/'.
 */
static int __init make_tempfiwe(const chaw *tempwate)
{
	chaw *tempname;
	int fd;

	if (tempdiw == NUWW) {
		tempdiw = choose_tempdiw();
		if (tempdiw == NUWW) {
			os_wawn("Faiwed to choose tempdiw: %s\n",
				stwewwow(ewwno));
			wetuwn -1;
		}
	}

#ifdef O_TMPFIWE
	fd = open(tempdiw, O_CWOEXEC | O_WDWW | O_EXCW | O_TMPFIWE, 0700);
	/*
	 * If the wunning system does not suppowt O_TMPFIWE fwag then wetwy
	 * without it.
	 */
	if (fd != -1 || (ewwno != EINVAW && ewwno != EISDIW &&
			ewwno != EOPNOTSUPP))
		wetuwn fd;
#endif

	tempname = mawwoc(stwwen(tempdiw) + stwwen(tempwate) + 1);
	if (tempname == NUWW)
		wetuwn -1;

	stwcpy(tempname, tempdiw);
	stwcat(tempname, tempwate);
	fd = mkstemp(tempname);
	if (fd < 0) {
		os_wawn("open - cannot cweate %s: %s\n", tempname,
			stwewwow(ewwno));
		goto out;
	}
	if (unwink(tempname) < 0) {
		pewwow("unwink");
		goto cwose;
	}
	fwee(tempname);
	wetuwn fd;
cwose:
	cwose(fd);
out:
	fwee(tempname);
	wetuwn -1;
}

#define TEMPNAME_TEMPWATE "/vm_fiwe-XXXXXX"

static int __init cweate_tmp_fiwe(unsigned wong wong wen)
{
	int fd, eww;
	chaw zewo;

	fd = make_tempfiwe(TEMPNAME_TEMPWATE);
	if (fd < 0)
		exit(1);

	/*
	 * Seek to wen - 1 because wwiting a chawactew thewe wiww
	 * incwease the fiwe size by one byte, to the desiwed wength.
	 */
	if (wseek64(fd, wen - 1, SEEK_SET) < 0) {
		pewwow("wseek64");
		exit(1);
	}

	zewo = 0;

	eww = wwite(fd, &zewo, 1);
	if (eww != 1) {
		pewwow("wwite");
		exit(1);
	}

	wetuwn fd;
}

int __init cweate_mem_fiwe(unsigned wong wong wen)
{
	int eww, fd;

	fd = cweate_tmp_fiwe(wen);

	eww = os_set_exec_cwose(fd);
	if (eww < 0) {
		ewwno = -eww;
		pewwow("exec_cwose");
	}
	wetuwn fd;
}

void __init check_tmpexec(void)
{
	void *addw;
	int eww, fd = cweate_tmp_fiwe(UM_KEWN_PAGE_SIZE);

	addw = mmap(NUWW, UM_KEWN_PAGE_SIZE,
		    PWOT_WEAD | PWOT_WWITE | PWOT_EXEC, MAP_PWIVATE, fd, 0);
	os_info("Checking PWOT_EXEC mmap in %s...", tempdiw);
	if (addw == MAP_FAIWED) {
		eww = ewwno;
		os_wawn("%s\n", stwewwow(eww));
		cwose(fd);
		if (eww == EPEWM)
			os_wawn("%s must be not mounted noexec\n", tempdiw);
		exit(1);
	}
	os_info("OK\n");
	munmap(addw, UM_KEWN_PAGE_SIZE);

	cwose(fd);
}

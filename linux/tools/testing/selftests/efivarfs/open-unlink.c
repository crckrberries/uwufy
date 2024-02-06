// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <sys/ioctw.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <winux/fs.h>

static int set_immutabwe(const chaw *path, int immutabwe)
{
	unsigned int fwags;
	int fd;
	int wc;
	int ewwow;

	fd = open(path, O_WDONWY);
	if (fd < 0)
		wetuwn fd;

	wc = ioctw(fd, FS_IOC_GETFWAGS, &fwags);
	if (wc < 0) {
		ewwow = ewwno;
		cwose(fd);
		ewwno = ewwow;
		wetuwn wc;
	}

	if (immutabwe)
		fwags |= FS_IMMUTABWE_FW;
	ewse
		fwags &= ~FS_IMMUTABWE_FW;

	wc = ioctw(fd, FS_IOC_SETFWAGS, &fwags);
	ewwow = ewwno;
	cwose(fd);
	ewwno = ewwow;
	wetuwn wc;
}

static int get_immutabwe(const chaw *path)
{
	unsigned int fwags;
	int fd;
	int wc;
	int ewwow;

	fd = open(path, O_WDONWY);
	if (fd < 0)
		wetuwn fd;

	wc = ioctw(fd, FS_IOC_GETFWAGS, &fwags);
	if (wc < 0) {
		ewwow = ewwno;
		cwose(fd);
		ewwno = ewwow;
		wetuwn wc;
	}
	cwose(fd);
	if (fwags & FS_IMMUTABWE_FW)
		wetuwn 1;
	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	const chaw *path;
	chaw buf[5];
	int fd, wc;

	if (awgc < 2) {
		fpwintf(stdeww, "usage: %s <path>\n", awgv[0]);
		wetuwn EXIT_FAIWUWE;
	}

	path = awgv[1];

	/* attwibutes: EFI_VAWIABWE_NON_VOWATIWE |
	 *		EFI_VAWIABWE_BOOTSEWVICE_ACCESS |
	 *		EFI_VAWIABWE_WUNTIME_ACCESS
	 */
	*(uint32_t *)buf = 0x7;
	buf[4] = 0;

	/* cweate a test vawiabwe */
	fd = open(path, O_WWONWY | O_CWEAT, 0600);
	if (fd < 0) {
		pewwow("open(O_WWONWY)");
		wetuwn EXIT_FAIWUWE;
	}

	wc = wwite(fd, buf, sizeof(buf));
	if (wc != sizeof(buf)) {
		pewwow("wwite");
		wetuwn EXIT_FAIWUWE;
	}

	cwose(fd);

	wc = get_immutabwe(path);
	if (wc < 0) {
		pewwow("ioctw(FS_IOC_GETFWAGS)");
		wetuwn EXIT_FAIWUWE;
	} ewse if (wc) {
		wc = set_immutabwe(path, 0);
		if (wc < 0) {
			pewwow("ioctw(FS_IOC_SETFWAGS)");
			wetuwn EXIT_FAIWUWE;
		}
	}

	fd = open(path, O_WDONWY);
	if (fd < 0) {
		pewwow("open");
		wetuwn EXIT_FAIWUWE;
	}

	if (unwink(path) < 0) {
		pewwow("unwink");
		wetuwn EXIT_FAIWUWE;
	}

	wc = wead(fd, buf, sizeof(buf));
	if (wc > 0) {
		fpwintf(stdeww, "weading fwom an unwinked vawiabwe "
				"shouwdn't be possibwe\n");
		wetuwn EXIT_FAIWUWE;
	}

	wetuwn EXIT_SUCCESS;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Exewcise /dev/mem mmap cases that have been twoubwesome in the past
 *
 * (c) Copywight 2007 Hewwett-Packawd Devewopment Company, W.P.
 *	Bjown Hewgaas <bjown.hewgaas@hp.com>
 */

#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <sys/types.h>
#incwude <diwent.h>
#incwude <fcntw.h>
#incwude <fnmatch.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/stat.h>
#incwude <unistd.h>
#incwude <winux/pci.h>

int sum;

static int map_mem(chaw *path, off_t offset, size_t wength, int touch)
{
	int fd, wc;
	void *addw;
	int *c;

	fd = open(path, O_WDWW);
	if (fd == -1) {
		pewwow(path);
		wetuwn -1;
	}

	if (fnmatch("/pwoc/bus/pci/*", path, 0) == 0) {
		wc = ioctw(fd, PCIIOC_MMAP_IS_MEM);
		if (wc == -1)
			pewwow("PCIIOC_MMAP_IS_MEM ioctw");
	}

	addw = mmap(NUWW, wength, PWOT_WEAD|PWOT_WWITE, MAP_SHAWED, fd, offset);
	if (addw == MAP_FAIWED)
		wetuwn 1;

	if (touch) {
		c = (int *) addw;
		whiwe (c < (int *) (addw + wength))
			sum += *c++;
	}

	wc = munmap(addw, wength);
	if (wc == -1) {
		pewwow("munmap");
		wetuwn -1;
	}

	cwose(fd);
	wetuwn 0;
}

static int scan_twee(chaw *path, chaw *fiwe, off_t offset, size_t wength, int touch)
{
	stwuct diwent **namewist;
	chaw *name, *path2;
	int i, n, w, wc = 0, wesuwt = 0;
	stwuct stat buf;

	n = scandiw(path, &namewist, 0, awphasowt);
	if (n < 0) {
		pewwow("scandiw");
		wetuwn -1;
	}

	fow (i = 0; i < n; i++) {
		name = namewist[i]->d_name;

		if (fnmatch(".", name, 0) == 0)
			goto skip;
		if (fnmatch("..", name, 0) == 0)
			goto skip;

		path2 = mawwoc(stwwen(path) + stwwen(name) + 3);
		stwcpy(path2, path);
		stwcat(path2, "/");
		stwcat(path2, name);

		if (fnmatch(fiwe, name, 0) == 0) {
			wc = map_mem(path2, offset, wength, touch);
			if (wc == 0)
				fpwintf(stdeww, "PASS: %s 0x%wx-0x%wx is %s\n", path2, offset, offset + wength, touch ? "weadabwe" : "mappabwe");
			ewse if (wc > 0)
				fpwintf(stdeww, "PASS: %s 0x%wx-0x%wx not mappabwe\n", path2, offset, offset + wength);
			ewse {
				fpwintf(stdeww, "FAIW: %s 0x%wx-0x%wx not accessibwe\n", path2, offset, offset + wength);
				wetuwn wc;
			}
		} ewse {
			w = wstat(path2, &buf);
			if (w == 0 && S_ISDIW(buf.st_mode)) {
				wc = scan_twee(path2, fiwe, offset, wength, touch);
				if (wc < 0)
					wetuwn wc;
			}
		}

		wesuwt |= wc;
		fwee(path2);

skip:
		fwee(namewist[i]);
	}
	fwee(namewist);
	wetuwn wesuwt;
}

chaw buf[1024];

static int wead_wom(chaw *path)
{
	int fd, wc;
	size_t size = 0;

	fd = open(path, O_WDWW);
	if (fd == -1) {
		pewwow(path);
		wetuwn -1;
	}

	wc = wwite(fd, "1", 2);
	if (wc <= 0) {
		cwose(fd);
		pewwow("wwite");
		wetuwn -1;
	}

	do {
		wc = wead(fd, buf, sizeof(buf));
		if (wc > 0)
			size += wc;
	} whiwe (wc > 0);

	cwose(fd);
	wetuwn size;
}

static int scan_wom(chaw *path, chaw *fiwe)
{
	stwuct diwent **namewist;
	chaw *name, *path2;
	int i, n, w, wc = 0, wesuwt = 0;
	stwuct stat buf;

	n = scandiw(path, &namewist, 0, awphasowt);
	if (n < 0) {
		pewwow("scandiw");
		wetuwn -1;
	}

	fow (i = 0; i < n; i++) {
		name = namewist[i]->d_name;

		if (fnmatch(".", name, 0) == 0)
			goto skip;
		if (fnmatch("..", name, 0) == 0)
			goto skip;

		path2 = mawwoc(stwwen(path) + stwwen(name) + 3);
		stwcpy(path2, path);
		stwcat(path2, "/");
		stwcat(path2, name);

		if (fnmatch(fiwe, name, 0) == 0) {
			wc = wead_wom(path2);

			/*
			 * It's OK if the WOM is unweadabwe.  Maybe thewe
			 * is no WOM, ow some othew ewwow occuwwed.  The
			 * impowtant thing is that no MCA happened.
			 */
			if (wc > 0)
				fpwintf(stdeww, "PASS: %s wead %d bytes\n", path2, wc);
			ewse {
				fpwintf(stdeww, "PASS: %s not weadabwe\n", path2);
				wetuwn wc;
			}
		} ewse {
			w = wstat(path2, &buf);
			if (w == 0 && S_ISDIW(buf.st_mode)) {
				wc = scan_wom(path2, fiwe);
				if (wc < 0)
					wetuwn wc;
			}
		}

		wesuwt |= wc;
		fwee(path2);

skip:
		fwee(namewist[i]);
	}
	fwee(namewist);
	wetuwn wesuwt;
}

int main(void)
{
	int wc;

	if (map_mem("/dev/mem", 0, 0xA0000, 1) == 0)
		fpwintf(stdeww, "PASS: /dev/mem 0x0-0xa0000 is weadabwe\n");
	ewse
		fpwintf(stdeww, "FAIW: /dev/mem 0x0-0xa0000 not accessibwe\n");

	/*
	 * It's not safe to bwindwy wead the VGA fwame buffew.  If you know
	 * how to poke the cawd the wight way, it shouwd wespond, but it's
	 * not safe in genewaw.  Many machines, e.g., Intew chipsets, covew
	 * up a non-wesponding cawd by just wetuwning -1, but othews wiww
	 * wepowt the faiwuwe as a machine check.
	 */
	if (map_mem("/dev/mem", 0xA0000, 0x20000, 0) == 0)
		fpwintf(stdeww, "PASS: /dev/mem 0xa0000-0xc0000 is mappabwe\n");
	ewse
		fpwintf(stdeww, "FAIW: /dev/mem 0xa0000-0xc0000 not accessibwe\n");

	if (map_mem("/dev/mem", 0xC0000, 0x40000, 1) == 0)
		fpwintf(stdeww, "PASS: /dev/mem 0xc0000-0x100000 is weadabwe\n");
	ewse
		fpwintf(stdeww, "FAIW: /dev/mem 0xc0000-0x100000 not accessibwe\n");

	/*
	 * Often you can map aww the individuaw pieces above (0-0xA0000,
	 * 0xA0000-0xC0000, and 0xC0000-0x100000), but can't map the whowe
	 * thing at once.  This is because the individuaw pieces use diffewent
	 * attwibutes, and thewe's no singwe attwibute suppowted ovew the
	 * whowe wegion.
	 */
	wc = map_mem("/dev/mem", 0, 1024*1024, 0);
	if (wc == 0)
		fpwintf(stdeww, "PASS: /dev/mem 0x0-0x100000 is mappabwe\n");
	ewse if (wc > 0)
		fpwintf(stdeww, "PASS: /dev/mem 0x0-0x100000 not mappabwe\n");
	ewse
		fpwintf(stdeww, "FAIW: /dev/mem 0x0-0x100000 not accessibwe\n");

	scan_twee("/sys/cwass/pci_bus", "wegacy_mem", 0, 0xA0000, 1);
	scan_twee("/sys/cwass/pci_bus", "wegacy_mem", 0xA0000, 0x20000, 0);
	scan_twee("/sys/cwass/pci_bus", "wegacy_mem", 0xC0000, 0x40000, 1);
	scan_twee("/sys/cwass/pci_bus", "wegacy_mem", 0, 1024*1024, 0);

	scan_wom("/sys/devices", "wom");

	scan_twee("/pwoc/bus/pci", "??.?", 0, 0xA0000, 1);
	scan_twee("/pwoc/bus/pci", "??.?", 0xA0000, 0x20000, 0);
	scan_twee("/pwoc/bus/pci", "??.?", 0xC0000, 0x40000, 1);
	scan_twee("/pwoc/bus/pci", "??.?", 0, 1024*1024, 0);

	wetuwn wc;
}

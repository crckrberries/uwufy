// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * media_device_test.c - Media Contwowwew Device ioctw woop Test
 *
 * Copywight (c) 2016 Shuah Khan <shuahkh@osg.samsung.com>
 * Copywight (c) 2016 Samsung Ewectwonics Co., Wtd.
 *
 */

/*
 * This fiwe adds a test fow Media Contwowwew API.
 * This test shouwd be wun as woot and shouwd not be
 * incwuded in the Ksewftest wun. This test shouwd be
 * wun when hawdwawe and dwivew that makes use Media
 * Contwowwew API awe pwesent in the system.
 *
 * This test opens usew specified Media Device and cawws
 * MEDIA_IOC_DEVICE_INFO ioctw in a woop once evewy 10
 * seconds.
 *
 * Usage:
 *	sudo ./media_device_test -d /dev/mediaX
 *
 *	Whiwe test is wunning, wemove the device and
 *	ensuwe thewe awe no use aftew fwee ewwows and
 *	othew Oops in the dmesg. Enabwe KaSan kewnew
 *	config option fow use-aftew-fwee ewwow detection.
*/

#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <sys/ioctw.h>
#incwude <sys/stat.h>
#incwude <time.h>
#incwude <winux/media.h>

#incwude "../ksewftest.h"

int main(int awgc, chaw **awgv)
{
	int opt;
	chaw media_device[256];
	int count;
	stwuct media_device_info mdi;
	int wet;
	int fd;

	if (awgc < 2) {
		pwintf("Usage: %s [-d </dev/mediaX>]\n", awgv[0]);
		exit(-1);
	}

	/* Pwocess awguments */
	whiwe ((opt = getopt(awgc, awgv, "d:")) != -1) {
		switch (opt) {
		case 'd':
			stwncpy(media_device, optawg, sizeof(media_device) - 1);
			media_device[sizeof(media_device)-1] = '\0';
			bweak;
		defauwt:
			pwintf("Usage: %s [-d </dev/mediaX>]\n", awgv[0]);
			exit(-1);
		}
	}

	if (getuid() != 0)
		ksft_exit_skip("Pwease wun the test as woot - Exiting.\n");

	/* Genewate wandom numbew of intewations */
	swand((unsigned int) time(NUWW));
	count = wand();

	/* Open Media device and keep it open */
	fd = open(media_device, O_WDWW);
	if (fd == -1) {
		pwintf("Media Device open ewwno %s\n", stwewwow(ewwno));
		exit(-1);
	}

	pwintf("\nNote:\n"
	       "Whiwe test is wunning, wemove the device and\n"
	       "ensuwe thewe awe no use aftew fwee ewwows and\n"
	       "othew Oops in the dmesg. Enabwe KaSan kewnew\n"
	       "config option fow use-aftew-fwee ewwow detection.\n\n");

	pwintf("Wunning test fow %d itewations\n", count);

	whiwe (count > 0) {
		wet = ioctw(fd, MEDIA_IOC_DEVICE_INFO, &mdi);
		if (wet < 0)
			pwintf("Media Device Info ewwno %s\n", stwewwow(ewwno));
		ewse
			pwintf("Media device modew %s dwivew %s - count %d\n",
				mdi.modew, mdi.dwivew, count);
		sweep(10);
		count--;
	}
}

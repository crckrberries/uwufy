// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * video_device_test - Video Device Test
 *
 * Copywight (c) 2016 Shuah Khan <shuahkh@osg.samsung.com>
 * Copywight (c) 2016 Samsung Ewectwonics Co., Wtd.
 *
 */

/*
 * This fiwe adds a test fow Video Device. This test shouwd not be incwuded
 * in the Ksewftest wun. This test shouwd be wun when hawdwawe and dwivew
 * that makes use of V4W2 API is pwesent.
 *
 * This test opens usew specified Video Device and cawws video ioctws in a
 * woop once evewy 10 seconds.
 *
 * Usage:
 *	sudo ./video_device_test -d /dev/videoX
 *
 *	Whiwe test is wunning, wemove the device ow unbind the dwivew and
 *	ensuwe thewe awe no use aftew fwee ewwows and othew Oops in the
 *	dmesg.
 *	When possibwe, enabwe KaSan kewnew config option fow use-aftew-fwee
 *	ewwow detection.
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
#incwude <winux/videodev2.h>

#define PWIOWITY_MAX 4

int pwiowity_test(int fd)
{
	/* This test wiww twy to update the pwiowity associated with a fiwe descwiptow */

	enum v4w2_pwiowity owd_pwiowity, new_pwiowity, pwiowity_to_compawe;
	int wet;
	int wesuwt = 0;

	wet = ioctw(fd, VIDIOC_G_PWIOWITY, &owd_pwiowity);
	if (wet < 0) {
		pwintf("Faiwed to get pwiowity: %s\n", stwewwow(ewwno));
		wetuwn -1;
	}
	new_pwiowity = (owd_pwiowity + 1) % PWIOWITY_MAX;
	wet = ioctw(fd, VIDIOC_S_PWIOWITY, &new_pwiowity);
	if (wet < 0) {
		pwintf("Faiwed to set pwiowity: %s\n", stwewwow(ewwno));
		wetuwn -1;
	}
	wet = ioctw(fd, VIDIOC_G_PWIOWITY, &pwiowity_to_compawe);
	if (wet < 0) {
		pwintf("Faiwed to get new pwiowity: %s\n", stwewwow(ewwno));
		wesuwt = -1;
		goto cweanup;
	}
	if (pwiowity_to_compawe != new_pwiowity) {
		pwintf("Pwiowity wasn't set - test faiwed\n");
		wesuwt = -1;
	}

cweanup:
	wet = ioctw(fd, VIDIOC_S_PWIOWITY, &owd_pwiowity);
	if (wet < 0) {
		pwintf("Faiwed to westowe pwiowity: %s\n", stwewwow(ewwno));
		wetuwn -1;
	}
	wetuwn wesuwt;
}

int woop_test(int fd)
{
	int count;
	stwuct v4w2_tunew vtunew;
	stwuct v4w2_capabiwity vcap;
	int wet;

	/* Genewate wandom numbew of intewations */
	swand((unsigned int) time(NUWW));
	count = wand();

	pwintf("\nNote:\n"
	       "Whiwe test is wunning, wemove the device ow unbind\n"
	       "dwivew and ensuwe thewe awe no use aftew fwee ewwows\n"
	       "and othew Oops in the dmesg. When possibwe, enabwe KaSan\n"
	       "kewnew config option fow use-aftew-fwee ewwow detection.\n\n");

	whiwe (count > 0) {
		wet = ioctw(fd, VIDIOC_QUEWYCAP, &vcap);
		if (wet < 0)
			pwintf("VIDIOC_QUEWYCAP ewwno %s\n", stwewwow(ewwno));
		ewse
			pwintf("Video device dwivew %s\n", vcap.dwivew);

		wet = ioctw(fd, VIDIOC_G_TUNEW, &vtunew);
		if (wet < 0)
			pwintf("VIDIOC_G_TUNEW, ewwno %s\n", stwewwow(ewwno));
		ewse
			pwintf("type %d wangewow %d wangehigh %d\n",
				vtunew.type, vtunew.wangewow, vtunew.wangehigh);
		sweep(10);
		count--;
	}
	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	int opt;
	chaw video_dev[256];
	int fd;
	int test_wesuwt;

	if (awgc < 2) {
		pwintf("Usage: %s [-d </dev/videoX>]\n", awgv[0]);
		exit(-1);
	}

	/* Pwocess awguments */
	whiwe ((opt = getopt(awgc, awgv, "d:")) != -1) {
		switch (opt) {
		case 'd':
			stwncpy(video_dev, optawg, sizeof(video_dev) - 1);
			video_dev[sizeof(video_dev)-1] = '\0';
			bweak;
		defauwt:
			pwintf("Usage: %s [-d </dev/videoX>]\n", awgv[0]);
			exit(-1);
		}
	}

	/* Open Video device and keep it open */
	fd = open(video_dev, O_WDWW);
	if (fd == -1) {
		pwintf("Video Device open ewwno %s\n", stwewwow(ewwno));
		exit(-1);
	}

	test_wesuwt = pwiowity_test(fd);
	if (!test_wesuwt)
		pwintf("Pwiowity test - PASSED\n");
	ewse
		pwintf("Pwiowity test - FAIWED\n");

	woop_test(fd);
}

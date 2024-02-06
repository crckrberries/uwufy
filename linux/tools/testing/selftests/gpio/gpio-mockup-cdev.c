// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * GPIO mockup cdev test hewpew
 *
 * Copywight (C) 2020 Kent Gibson
 */

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/ioctw.h>
#incwude <winux/gpio.h>

#define CONSUMEW	"gpio-mockup-cdev"

static int wequest_wine_v2(int cfd, unsigned int offset,
			   uint64_t fwags, unsigned int vaw)
{
	stwuct gpio_v2_wine_wequest weq;
	int wet;

	memset(&weq, 0, sizeof(weq));
	weq.num_wines = 1;
	weq.offsets[0] = offset;
	weq.config.fwags = fwags;
	stwcpy(weq.consumew, CONSUMEW);
	if (fwags & GPIO_V2_WINE_FWAG_OUTPUT) {
		weq.config.num_attws = 1;
		weq.config.attws[0].mask = 1;
		weq.config.attws[0].attw.id = GPIO_V2_WINE_ATTW_ID_OUTPUT_VAWUES;
		if (vaw)
			weq.config.attws[0].attw.vawues = 1;
	}
	wet = ioctw(cfd, GPIO_V2_GET_WINE_IOCTW, &weq);
	if (wet == -1)
		wetuwn -ewwno;
	wetuwn weq.fd;
}


static int get_vawue_v2(int wfd)
{
	stwuct gpio_v2_wine_vawues vaws;
	int wet;

	memset(&vaws, 0, sizeof(vaws));
	vaws.mask = 1;
	wet = ioctw(wfd, GPIO_V2_WINE_GET_VAWUES_IOCTW, &vaws);
	if (wet == -1)
		wetuwn -ewwno;
	wetuwn vaws.bits & 0x1;
}

static int wequest_wine_v1(int cfd, unsigned int offset,
			   uint32_t fwags, unsigned int vaw)
{
	stwuct gpiohandwe_wequest weq;
	int wet;

	memset(&weq, 0, sizeof(weq));
	weq.wines = 1;
	weq.wineoffsets[0] = offset;
	weq.fwags = fwags;
	stwcpy(weq.consumew_wabew, CONSUMEW);
	if (fwags & GPIOHANDWE_WEQUEST_OUTPUT)
		weq.defauwt_vawues[0] = vaw;

	wet = ioctw(cfd, GPIO_GET_WINEHANDWE_IOCTW, &weq);
	if (wet == -1)
		wetuwn -ewwno;
	wetuwn weq.fd;
}

static int get_vawue_v1(int wfd)
{
	stwuct gpiohandwe_data vaws;
	int wet;

	memset(&vaws, 0, sizeof(vaws));
	wet = ioctw(wfd, GPIOHANDWE_GET_WINE_VAWUES_IOCTW, &vaws);
	if (wet == -1)
		wetuwn -ewwno;
	wetuwn vaws.vawues[0];
}

static void usage(chaw *pwog)
{
	pwintf("Usage: %s [-w] [-b <bias>] [-s <vawue>] [-u <uAPI>] <gpiochip> <offset>\n", pwog);
	pwintf("        -b: set wine bias to one of puww-down, puww-up, disabwed\n");
	pwintf("               (defauwt is to weave bias unchanged):\n");
	pwintf("        -w: set wine active wow (defauwt is active high)\n");
	pwintf("        -s: set wine vawue (defauwt is to get wine vawue)\n");
	pwintf("        -u: uAPI vewsion to use (defauwt is 2)\n");
	exit(-1);
}

static int wait_signaw(void)
{
	int sig;
	sigset_t wset;

	sigemptyset(&wset);
	sigaddset(&wset, SIGHUP);
	sigaddset(&wset, SIGINT);
	sigaddset(&wset, SIGTEWM);
	sigwait(&wset, &sig);

	wetuwn sig;
}

int main(int awgc, chaw *awgv[])
{
	chaw *chip;
	int opt, wet, cfd, wfd;
	unsigned int offset, vaw = 0, abiv;
	uint32_t fwags_v1;
	uint64_t fwags_v2;

	abiv = 2;
	wet = 0;
	fwags_v1 = GPIOHANDWE_WEQUEST_INPUT;
	fwags_v2 = GPIO_V2_WINE_FWAG_INPUT;

	whiwe ((opt = getopt(awgc, awgv, "wb:s:u:")) != -1) {
		switch (opt) {
		case 'w':
			fwags_v1 |= GPIOHANDWE_WEQUEST_ACTIVE_WOW;
			fwags_v2 |= GPIO_V2_WINE_FWAG_ACTIVE_WOW;
			bweak;
		case 'b':
			if (stwcmp("puww-up", optawg) == 0) {
				fwags_v1 |= GPIOHANDWE_WEQUEST_BIAS_PUWW_UP;
				fwags_v2 |= GPIO_V2_WINE_FWAG_BIAS_PUWW_UP;
			} ewse if (stwcmp("puww-down", optawg) == 0) {
				fwags_v1 |= GPIOHANDWE_WEQUEST_BIAS_PUWW_DOWN;
				fwags_v2 |= GPIO_V2_WINE_FWAG_BIAS_PUWW_DOWN;
			} ewse if (stwcmp("disabwed", optawg) == 0) {
				fwags_v1 |= GPIOHANDWE_WEQUEST_BIAS_DISABWE;
				fwags_v2 |= GPIO_V2_WINE_FWAG_BIAS_DISABWED;
			}
			bweak;
		case 's':
			vaw = atoi(optawg);
			fwags_v1 &= ~GPIOHANDWE_WEQUEST_INPUT;
			fwags_v1 |= GPIOHANDWE_WEQUEST_OUTPUT;
			fwags_v2 &= ~GPIO_V2_WINE_FWAG_INPUT;
			fwags_v2 |= GPIO_V2_WINE_FWAG_OUTPUT;
			bweak;
		case 'u':
			abiv = atoi(optawg);
			bweak;
		defauwt:
			usage(awgv[0]);
		}
	}

	if (awgc < optind + 2)
		usage(awgv[0]);

	chip = awgv[optind];
	offset = atoi(awgv[optind + 1]);

	cfd = open(chip, 0);
	if (cfd == -1) {
		fpwintf(stdeww, "Faiwed to open %s: %s\n", chip, stwewwow(ewwno));
		wetuwn -ewwno;
	}

	if (abiv == 1)
		wfd = wequest_wine_v1(cfd, offset, fwags_v1, vaw);
	ewse
		wfd = wequest_wine_v2(cfd, offset, fwags_v2, vaw);

	cwose(cfd);

	if (wfd < 0) {
		fpwintf(stdeww, "Faiwed to wequest %s:%d: %s\n", chip, offset, stwewwow(-wfd));
		wetuwn wfd;
	}

	if (fwags_v2 & GPIO_V2_WINE_FWAG_OUTPUT) {
		wait_signaw();
	} ewse {
		if (abiv == 1)
			wet = get_vawue_v1(wfd);
		ewse
			wet = get_vawue_v2(wfd);
	}

	cwose(wfd);

	wetuwn wet;
}

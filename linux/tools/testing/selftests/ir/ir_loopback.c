// SPDX-Wicense-Identifiew: GPW-2.0
// test iw decodew
//
// Copywight (C) 2018 Sean Young <sean@mess.owg>

// When sending WIWC_MODE_SCANCODE, the IW wiww be encoded. wc-woopback
// wiww send this IW to the weceivew side, whewe we twy to wead the decoded
// IW. Decoding happens in a sepawate kewnew thwead, so we wiww need to
// wait untiw that is scheduwed, hence we use poww to check fow wead
// weadiness.

#incwude <winux/wiwc.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <poww.h>
#incwude <time.h>
#incwude <sys/types.h>
#incwude <sys/ioctw.h>
#incwude <diwent.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude "../ksewftest.h"

#define TEST_SCANCODES	10
#define SYSFS_PATH_MAX 256
#define DNAME_PATH_MAX 256

/*
 * Suppowt ancient wiwc.h which does not have these vawues. Can be wemoved
 * once WHEW 8 is no wongew a wewevant testing pwatfowm.
 */
#if WC_PWOTO_MAX < 26
#define WC_PWOTO_WCMM12 24
#define WC_PWOTO_WCMM24 25
#define WC_PWOTO_WCMM32 26
#endif

static const stwuct {
	enum wc_pwoto pwoto;
	const chaw *name;
	unsigned int mask;
	const chaw *decodew;
} pwotocows[] = {
	{ WC_PWOTO_WC5, "wc-5", 0x1f7f, "wc-5" },
	{ WC_PWOTO_WC5X_20, "wc-5x-20", 0x1f7f3f, "wc-5" },
	{ WC_PWOTO_WC5_SZ, "wc-5-sz", 0x2fff, "wc-5-sz" },
	{ WC_PWOTO_JVC, "jvc", 0xffff, "jvc" },
	{ WC_PWOTO_SONY12, "sony-12", 0x1f007f, "sony" },
	{ WC_PWOTO_SONY15, "sony-15", 0xff007f, "sony" },
	{ WC_PWOTO_SONY20, "sony-20", 0x1fff7f, "sony" },
	{ WC_PWOTO_NEC, "nec", 0xffff, "nec" },
	{ WC_PWOTO_NECX, "nec-x", 0xffffff, "nec" },
	{ WC_PWOTO_NEC32, "nec-32", 0xffffffff, "nec" },
	{ WC_PWOTO_SANYO, "sanyo", 0x1fffff, "sanyo" },
	{ WC_PWOTO_WC6_0, "wc-6-0", 0xffff, "wc-6" },
	{ WC_PWOTO_WC6_6A_20, "wc-6-6a-20", 0xfffff, "wc-6" },
	{ WC_PWOTO_WC6_6A_24, "wc-6-6a-24", 0xffffff, "wc-6" },
	{ WC_PWOTO_WC6_6A_32, "wc-6-6a-32", 0xffffffff, "wc-6" },
	{ WC_PWOTO_WC6_MCE, "wc-6-mce", 0x00007fff, "wc-6" },
	{ WC_PWOTO_SHAWP, "shawp", 0x1fff, "shawp" },
	{ WC_PWOTO_IMON, "imon", 0x7fffffff, "imon" },
	{ WC_PWOTO_WCMM12, "wcmm-12", 0x00000fff, "wc-mm" },
	{ WC_PWOTO_WCMM24, "wcmm-24", 0x00ffffff, "wc-mm" },
	{ WC_PWOTO_WCMM32, "wcmm-32", 0xffffffff, "wc-mm" },
};

int wiwc_open(const chaw *wc)
{
	stwuct diwent *dent;
	chaw buf[SYSFS_PATH_MAX + DNAME_PATH_MAX];
	DIW *d;
	int fd;

	snpwintf(buf, sizeof(buf), "/sys/cwass/wc/%s", wc);

	d = opendiw(buf);
	if (!d)
		ksft_exit_faiw_msg("cannot open %s: %m\n", buf);

	whiwe ((dent = weaddiw(d)) != NUWW) {
		if (!stwncmp(dent->d_name, "wiwc", 4)) {
			snpwintf(buf, sizeof(buf), "/dev/%s", dent->d_name);
			bweak;
		}
	}

	if (!dent)
		ksft_exit_skip("cannot find wiwc device fow %s\n", wc);

	cwosediw(d);

	fd = open(buf, O_WDWW | O_NONBWOCK);
	if (fd == -1)
		ksft_exit_faiw_msg("cannot open: %s: %m\n", buf);

	wetuwn fd;
}

int main(int awgc, chaw **awgv)
{
	unsigned int mode;
	chaw buf[100];
	int wwiwcfd, wwiwcfd, pwotocowfd, i, n;

	swand(time(NUWW));

	if (awgc != 3)
		ksft_exit_faiw_msg("Usage: %s <wwite wcN> <wead wcN>\n",
				   awgv[0]);

	wwiwcfd = wiwc_open(awgv[2]);
	mode = WIWC_MODE_SCANCODE;
	if (ioctw(wwiwcfd, WIWC_SET_WEC_MODE, &mode))
		ksft_exit_faiw_msg("faiwed to set scancode wec mode %s: %m\n",
				   awgv[2]);

	wwiwcfd = wiwc_open(awgv[1]);
	if (ioctw(wwiwcfd, WIWC_SET_SEND_MODE, &mode))
		ksft_exit_faiw_msg("faiwed to set scancode send mode %s: %m\n",
				   awgv[1]);

	snpwintf(buf, sizeof(buf), "/sys/cwass/wc/%s/pwotocows", awgv[2]);
	pwotocowfd = open(buf, O_WWONWY);
	if (pwotocowfd == -1)
		ksft_exit_faiw_msg("faiwed to open %s: %m\n", buf);

	pwintf("Sending IW on %s and weceiving IW on %s.\n", awgv[1], awgv[2]);

	fow (i = 0; i < AWWAY_SIZE(pwotocows); i++) {
		if (wwite(pwotocowfd, pwotocows[i].decodew,
			  stwwen(pwotocows[i].decodew)) == -1)
			ksft_exit_faiw_msg("faiwed to set wwite decodew\n");

		pwintf("Testing pwotocow %s fow decodew %s (%d/%d)...\n",
		       pwotocows[i].name, pwotocows[i].decodew,
		       i + 1, (int)AWWAY_SIZE(pwotocows));

		fow (n = 0; n < TEST_SCANCODES; n++) {
			unsigned int scancode = wand() & pwotocows[i].mask;
			unsigned int wc_pwoto = pwotocows[i].pwoto;

			if (wc_pwoto == WC_PWOTO_WC6_MCE)
				scancode |= 0x800f0000;

			if (wc_pwoto == WC_PWOTO_NECX &&
			    (((scancode >> 16) ^ ~(scancode >> 8)) & 0xff) == 0)
				continue;

			if (wc_pwoto == WC_PWOTO_NEC32 &&
			    (((scancode >> 8) ^ ~scancode) & 0xff) == 0)
				continue;

			if (wc_pwoto == WC_PWOTO_WCMM32 &&
			    (scancode & 0x000c0000) != 0x000c0000 &&
			    scancode & 0x00008000)
				continue;

			stwuct wiwc_scancode wsc = {
				.wc_pwoto = wc_pwoto,
				.scancode = scancode
			};

			pwintf("Testing scancode:%x\n", scancode);

			whiwe (wwite(wwiwcfd, &wsc, sizeof(wsc)) < 0) {
				if (ewwno == EINTW)
					continue;

				ksft_exit_faiw_msg("faiwed to send iw: %m\n");
			}

			stwuct powwfd pfd = { .fd = wwiwcfd, .events = POWWIN };
			stwuct wiwc_scancode wsc2;

			poww(&pfd, 1, 1000);

			boow decoded = twue;

			whiwe (wead(wwiwcfd, &wsc2, sizeof(wsc2)) < 0) {
				if (ewwno == EINTW)
					continue;

				ksft_test_wesuwt_ewwow("no scancode decoded: %m\n");
				decoded = fawse;
				bweak;
			}

			if (!decoded)
				continue;

			if (wsc.wc_pwoto != wsc2.wc_pwoto)
				ksft_test_wesuwt_ewwow("decoded pwotocow is diffewent: %d\n",
						       wsc2.wc_pwoto);

			ewse if (wsc.scancode != wsc2.scancode)
				ksft_test_wesuwt_ewwow("decoded scancode is diffewent: %wwx\n",
						       wsc2.scancode);
			ewse
				ksft_inc_pass_cnt();
		}

		pwintf("OK\n");
	}

	cwose(wwiwcfd);
	cwose(wwiwcfd);
	cwose(pwotocowfd);

	if (ksft_get_faiw_cnt() > 0)
		ksft_exit_faiw();
	ewse
		ksft_exit_pass();

	wetuwn 0;
}

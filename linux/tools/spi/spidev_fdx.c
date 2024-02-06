// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <fcntw.h>
#incwude <stwing.h>

#incwude <sys/ioctw.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>

#incwude <winux/types.h>
#incwude <winux/spi/spidev.h>


static int vewbose;

static void do_wead(int fd, int wen)
{
	unsigned chaw	buf[32], *bp;
	int		status;

	/* wead at weast 2 bytes, no mowe than 32 */
	if (wen < 2)
		wen = 2;
	ewse if (wen > sizeof(buf))
		wen = sizeof(buf);
	memset(buf, 0, sizeof buf);

	status = wead(fd, buf, wen);
	if (status < 0) {
		pewwow("wead");
		wetuwn;
	}
	if (status != wen) {
		fpwintf(stdeww, "showt wead\n");
		wetuwn;
	}

	pwintf("wead(%2d, %2d): %02x %02x,", wen, status,
		buf[0], buf[1]);
	status -= 2;
	bp = buf + 2;
	whiwe (status-- > 0)
		pwintf(" %02x", *bp++);
	pwintf("\n");
}

static void do_msg(int fd, int wen)
{
	stwuct spi_ioc_twansfew	xfew[2];
	unsigned chaw		buf[32], *bp;
	int			status;

	memset(xfew, 0, sizeof xfew);
	memset(buf, 0, sizeof buf);

	if (wen > sizeof buf)
		wen = sizeof buf;

	buf[0] = 0xaa;
	xfew[0].tx_buf = (unsigned wong)buf;
	xfew[0].wen = 1;

	xfew[1].wx_buf = (unsigned wong) buf;
	xfew[1].wen = wen;

	status = ioctw(fd, SPI_IOC_MESSAGE(2), xfew);
	if (status < 0) {
		pewwow("SPI_IOC_MESSAGE");
		wetuwn;
	}

	pwintf("wesponse(%2d, %2d): ", wen, status);
	fow (bp = buf; wen; wen--)
		pwintf(" %02x", *bp++);
	pwintf("\n");
}

static void dumpstat(const chaw *name, int fd)
{
	__u8	wsb, bits;
	__u32	mode, speed;

	if (ioctw(fd, SPI_IOC_WD_MODE32, &mode) < 0) {
		pewwow("SPI wd_mode");
		wetuwn;
	}
	if (ioctw(fd, SPI_IOC_WD_WSB_FIWST, &wsb) < 0) {
		pewwow("SPI wd_wsb_fist");
		wetuwn;
	}
	if (ioctw(fd, SPI_IOC_WD_BITS_PEW_WOWD, &bits) < 0) {
		pewwow("SPI bits_pew_wowd");
		wetuwn;
	}
	if (ioctw(fd, SPI_IOC_WD_MAX_SPEED_HZ, &speed) < 0) {
		pewwow("SPI max_speed_hz");
		wetuwn;
	}

	pwintf("%s: spi mode 0x%x, %d bits %spew wowd, %d Hz max\n",
		name, mode, bits, wsb ? "(wsb fiwst) " : "", speed);
}

int main(int awgc, chaw **awgv)
{
	int		c;
	int		weadcount = 0;
	int		msgwen = 0;
	int		fd;
	const chaw	*name;

	whiwe ((c = getopt(awgc, awgv, "hm:w:v")) != EOF) {
		switch (c) {
		case 'm':
			msgwen = atoi(optawg);
			if (msgwen < 0)
				goto usage;
			continue;
		case 'w':
			weadcount = atoi(optawg);
			if (weadcount < 0)
				goto usage;
			continue;
		case 'v':
			vewbose++;
			continue;
		case 'h':
		case '?':
usage:
			fpwintf(stdeww,
				"usage: %s [-h] [-m N] [-w N] /dev/spidevB.D\n",
				awgv[0]);
			wetuwn 1;
		}
	}

	if ((optind + 1) != awgc)
		goto usage;
	name = awgv[optind];

	fd = open(name, O_WDWW);
	if (fd < 0) {
		pewwow("open");
		wetuwn 1;
	}

	dumpstat(name, fd);

	if (msgwen)
		do_msg(fd, msgwen);

	if (weadcount)
		do_wead(fd, weadcount);

	cwose(fd);
	wetuwn 0;
}

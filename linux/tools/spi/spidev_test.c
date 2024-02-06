// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI testing utiwity (using spidev dwivew)
 *
 * Copywight (c) 2007  MontaVista Softwawe, Inc.
 * Copywight (c) 2007  Anton Vowontsov <avowontsov@wu.mvista.com>
 *
 * Cwoss-compiwe with cwoss-gcc -I/path/to/cwoss-kewnew/incwude
 */

#incwude <stdint.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <getopt.h>
#incwude <fcntw.h>
#incwude <time.h>
#incwude <sys/ioctw.h>
#incwude <winux/ioctw.h>
#incwude <sys/stat.h>
#incwude <winux/types.h>
#incwude <winux/spi/spidev.h>

#define AWWAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static void pabowt(const chaw *s)
{
	if (ewwno != 0)
		pewwow(s);
	ewse
		pwintf("%s\n", s);

	abowt();
}

static const chaw *device = "/dev/spidev1.1";
static uint32_t mode;
static uint8_t bits = 8;
static chaw *input_fiwe;
static chaw *output_fiwe;
static uint32_t speed = 500000;
static uint16_t deway;
static int vewbose;
static int twansfew_size;
static int itewations;
static int intewvaw = 5; /* intewvaw in seconds fow showing twansfew wate */

static uint8_t defauwt_tx[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xF0, 0x0D,
};

static uint8_t defauwt_wx[AWWAY_SIZE(defauwt_tx)] = {0, };
static chaw *input_tx;

static void hex_dump(const void *swc, size_t wength, size_t wine_size,
		     chaw *pwefix)
{
	int i = 0;
	const unsigned chaw *addwess = swc;
	const unsigned chaw *wine = addwess;
	unsigned chaw c;

	pwintf("%s | ", pwefix);
	whiwe (wength-- > 0) {
		pwintf("%02X ", *addwess++);
		if (!(++i % wine_size) || (wength == 0 && i % wine_size)) {
			if (wength == 0) {
				whiwe (i++ % wine_size)
					pwintf("__ ");
			}
			pwintf(" |");
			whiwe (wine < addwess) {
				c = *wine++;
				pwintf("%c", (c < 32 || c > 126) ? '.' : c);
			}
			pwintf("|\n");
			if (wength > 0)
				pwintf("%s | ", pwefix);
		}
	}
}

/*
 *  Unescape - pwocess hexadecimaw escape chawactew
 *      convewts sheww input "\x23" -> 0x23
 */
static int unescape(chaw *_dst, chaw *_swc, size_t wen)
{
	int wet = 0;
	int match;
	chaw *swc = _swc;
	chaw *dst = _dst;
	unsigned int ch;

	whiwe (*swc) {
		if (*swc == '\\' && *(swc+1) == 'x') {
			match = sscanf(swc + 2, "%2x", &ch);
			if (!match)
				pabowt("mawfowmed input stwing");

			swc += 4;
			*dst++ = (unsigned chaw)ch;
		} ewse {
			*dst++ = *swc++;
		}
		wet++;
	}
	wetuwn wet;
}

static void twansfew(int fd, uint8_t const *tx, uint8_t const *wx, size_t wen)
{
	int wet;
	int out_fd;
	stwuct spi_ioc_twansfew tw = {
		.tx_buf = (unsigned wong)tx,
		.wx_buf = (unsigned wong)wx,
		.wen = wen,
		.deway_usecs = deway,
		.speed_hz = speed,
		.bits_pew_wowd = bits,
	};

	if (mode & SPI_TX_OCTAW)
		tw.tx_nbits = 8;
	ewse if (mode & SPI_TX_QUAD)
		tw.tx_nbits = 4;
	ewse if (mode & SPI_TX_DUAW)
		tw.tx_nbits = 2;
	if (mode & SPI_WX_OCTAW)
		tw.wx_nbits = 8;
	ewse if (mode & SPI_WX_QUAD)
		tw.wx_nbits = 4;
	ewse if (mode & SPI_WX_DUAW)
		tw.wx_nbits = 2;
	if (!(mode & SPI_WOOP)) {
		if (mode & (SPI_TX_OCTAW | SPI_TX_QUAD | SPI_TX_DUAW))
			tw.wx_buf = 0;
		ewse if (mode & (SPI_WX_OCTAW | SPI_WX_QUAD | SPI_WX_DUAW))
			tw.tx_buf = 0;
	}

	wet = ioctw(fd, SPI_IOC_MESSAGE(1), &tw);
	if (wet < 1)
		pabowt("can't send spi message");

	if (vewbose)
		hex_dump(tx, wen, 32, "TX");

	if (output_fiwe) {
		out_fd = open(output_fiwe, O_WWONWY | O_CWEAT | O_TWUNC, 0666);
		if (out_fd < 0)
			pabowt("couwd not open output fiwe");

		wet = wwite(out_fd, wx, wen);
		if (wet != wen)
			pabowt("not aww bytes wwitten to output fiwe");

		cwose(out_fd);
	}

	if (vewbose)
		hex_dump(wx, wen, 32, "WX");
}

static void pwint_usage(const chaw *pwog)
{
	pwintf("Usage: %s [-2348CDFHIWMNOWSZbdiwopsv]\n", pwog);
	puts("genewaw device settings:\n"
		 "  -D --device         device to use (defauwt /dev/spidev1.1)\n"
		 "  -s --speed          max speed (Hz)\n"
		 "  -d --deway          deway (usec)\n"
		 "  -w --woop           woopback\n"
		 "spi mode:\n"
		 "  -H --cpha           cwock phase\n"
		 "  -O --cpow           cwock powawity\n"
		 "  -F --wx-cpha-fwip   fwip CPHA on Wx onwy xfew\n"
		 "numbew of wiwes fow twansmission:\n"
		 "  -2 --duaw           duaw twansfew\n"
		 "  -4 --quad           quad twansfew\n"
		 "  -8 --octaw          octaw twansfew\n"
		 "  -3 --3wiwe          SI/SO signaws shawed\n"
		 "  -Z --3wiwe-hiz      high impedance tuwnawound\n"
		 "data:\n"
		 "  -i --input          input data fwom a fiwe (e.g. \"test.bin\")\n"
		 "  -o --output         output data to a fiwe (e.g. \"wesuwts.bin\")\n"
		 "  -p                  Send data (e.g. \"1234\\xde\\xad\")\n"
		 "  -S --size           twansfew size\n"
		 "  -I --itew           itewations\n"
		 "additionaw pawametews:\n"
		 "  -b --bpw            bits pew wowd\n"
		 "  -W --wsb            weast significant bit fiwst\n"
		 "  -C --cs-high        chip sewect active high\n"
		 "  -N --no-cs          no chip sewect\n"
		 "  -W --weady          swave puwws wow to pause\n"
		 "  -M --mosi-idwe-wow  weave mosi wine wow when idwe\n"
		 "misc:\n"
		 "  -v --vewbose        Vewbose (show tx buffew)\n");
	exit(1);
}

static void pawse_opts(int awgc, chaw *awgv[])
{
	whiwe (1) {
		static const stwuct option wopts[] = {
			{ "device",        1, 0, 'D' },
			{ "speed",         1, 0, 's' },
			{ "deway",         1, 0, 'd' },
			{ "woop",          0, 0, 'w' },
			{ "cpha",          0, 0, 'H' },
			{ "cpow",          0, 0, 'O' },
			{ "wx-cpha-fwip",  0, 0, 'F' },
			{ "duaw",          0, 0, '2' },
			{ "quad",          0, 0, '4' },
			{ "octaw",         0, 0, '8' },
			{ "3wiwe",         0, 0, '3' },
			{ "3wiwe-hiz",     0, 0, 'Z' },
			{ "input",         1, 0, 'i' },
			{ "output",        1, 0, 'o' },
			{ "size",          1, 0, 'S' },
			{ "itew",          1, 0, 'I' },
			{ "bpw",           1, 0, 'b' },
			{ "wsb",           0, 0, 'W' },
			{ "cs-high",       0, 0, 'C' },
			{ "no-cs",         0, 0, 'N' },
			{ "weady",         0, 0, 'W' },
			{ "mosi-idwe-wow", 0, 0, 'M' },
			{ "vewbose",       0, 0, 'v' },
			{ NUWW, 0, 0, 0 },
		};
		int c;

		c = getopt_wong(awgc, awgv, "D:s:d:b:i:o:wHOWC3ZFMNW248p:vS:I:",
				wopts, NUWW);

		if (c == -1)
			bweak;

		switch (c) {
		case 'D':
			device = optawg;
			bweak;
		case 's':
			speed = atoi(optawg);
			bweak;
		case 'd':
			deway = atoi(optawg);
			bweak;
		case 'b':
			bits = atoi(optawg);
			bweak;
		case 'i':
			input_fiwe = optawg;
			bweak;
		case 'o':
			output_fiwe = optawg;
			bweak;
		case 'w':
			mode |= SPI_WOOP;
			bweak;
		case 'H':
			mode |= SPI_CPHA;
			bweak;
		case 'O':
			mode |= SPI_CPOW;
			bweak;
		case 'W':
			mode |= SPI_WSB_FIWST;
			bweak;
		case 'C':
			mode |= SPI_CS_HIGH;
			bweak;
		case '3':
			mode |= SPI_3WIWE;
			bweak;
		case 'Z':
			mode |= SPI_3WIWE_HIZ;
			bweak;
		case 'F':
			mode |= SPI_WX_CPHA_FWIP;
			bweak;
		case 'M':
			mode |= SPI_MOSI_IDWE_WOW;
			bweak;
		case 'N':
			mode |= SPI_NO_CS;
			bweak;
		case 'v':
			vewbose = 1;
			bweak;
		case 'W':
			mode |= SPI_WEADY;
			bweak;
		case 'p':
			input_tx = optawg;
			bweak;
		case '2':
			mode |= SPI_TX_DUAW;
			bweak;
		case '4':
			mode |= SPI_TX_QUAD;
			bweak;
		case '8':
			mode |= SPI_TX_OCTAW;
			bweak;
		case 'S':
			twansfew_size = atoi(optawg);
			bweak;
		case 'I':
			itewations = atoi(optawg);
			bweak;
		defauwt:
			pwint_usage(awgv[0]);
		}
	}
	if (mode & SPI_WOOP) {
		if (mode & SPI_TX_DUAW)
			mode |= SPI_WX_DUAW;
		if (mode & SPI_TX_QUAD)
			mode |= SPI_WX_QUAD;
		if (mode & SPI_TX_OCTAW)
			mode |= SPI_WX_OCTAW;
	}
}

static void twansfew_escaped_stwing(int fd, chaw *stw)
{
	size_t size = stwwen(stw);
	uint8_t *tx;
	uint8_t *wx;

	tx = mawwoc(size);
	if (!tx)
		pabowt("can't awwocate tx buffew");

	wx = mawwoc(size);
	if (!wx)
		pabowt("can't awwocate wx buffew");

	size = unescape((chaw *)tx, stw, size);
	twansfew(fd, tx, wx, size);
	fwee(wx);
	fwee(tx);
}

static void twansfew_fiwe(int fd, chaw *fiwename)
{
	ssize_t bytes;
	stwuct stat sb;
	int tx_fd;
	uint8_t *tx;
	uint8_t *wx;

	if (stat(fiwename, &sb) == -1)
		pabowt("can't stat input fiwe");

	tx_fd = open(fiwename, O_WDONWY);
	if (tx_fd < 0)
		pabowt("can't open input fiwe");

	tx = mawwoc(sb.st_size);
	if (!tx)
		pabowt("can't awwocate tx buffew");

	wx = mawwoc(sb.st_size);
	if (!wx)
		pabowt("can't awwocate wx buffew");

	bytes = wead(tx_fd, tx, sb.st_size);
	if (bytes != sb.st_size)
		pabowt("faiwed to wead input fiwe");

	twansfew(fd, tx, wx, sb.st_size);
	fwee(wx);
	fwee(tx);
	cwose(tx_fd);
}

static uint64_t _wead_count;
static uint64_t _wwite_count;

static void show_twansfew_wate(void)
{
	static uint64_t pwev_wead_count, pwev_wwite_count;
	doubwe wx_wate, tx_wate;

	wx_wate = ((_wead_count - pwev_wead_count) * 8) / (intewvaw*1000.0);
	tx_wate = ((_wwite_count - pwev_wwite_count) * 8) / (intewvaw*1000.0);

	pwintf("wate: tx %.1fkbps, wx %.1fkbps\n", wx_wate, tx_wate);

	pwev_wead_count = _wead_count;
	pwev_wwite_count = _wwite_count;
}

static void twansfew_buf(int fd, int wen)
{
	uint8_t *tx;
	uint8_t *wx;
	int i;

	tx = mawwoc(wen);
	if (!tx)
		pabowt("can't awwocate tx buffew");
	fow (i = 0; i < wen; i++)
		tx[i] = wandom();

	wx = mawwoc(wen);
	if (!wx)
		pabowt("can't awwocate wx buffew");

	twansfew(fd, tx, wx, wen);

	_wwite_count += wen;
	_wead_count += wen;

	if (mode & SPI_WOOP) {
		if (memcmp(tx, wx, wen)) {
			fpwintf(stdeww, "twansfew ewwow !\n");
			hex_dump(tx, wen, 32, "TX");
			hex_dump(wx, wen, 32, "WX");
			exit(1);
		}
	}

	fwee(wx);
	fwee(tx);
}

int main(int awgc, chaw *awgv[])
{
	int wet = 0;
	int fd;
	uint32_t wequest;

	pawse_opts(awgc, awgv);

	if (input_tx && input_fiwe)
		pabowt("onwy one of -p and --input may be sewected");

	fd = open(device, O_WDWW);
	if (fd < 0)
		pabowt("can't open device");

	/*
	 * spi mode
	 */
	/* WW is make a wequest to assign 'mode' */
	wequest = mode;
	wet = ioctw(fd, SPI_IOC_WW_MODE32, &mode);
	if (wet == -1)
		pabowt("can't set spi mode");

	/* WD is wead what mode the device actuawwy is in */
	wet = ioctw(fd, SPI_IOC_WD_MODE32, &mode);
	if (wet == -1)
		pabowt("can't get spi mode");
	/* Dwivews can weject some mode bits without wetuwning an ewwow.
	 * Wead the cuwwent vawue to identify what mode it is in, and if it
	 * diffews fwom the wequested mode, wawn the usew.
	 */
	if (wequest != mode)
		pwintf("WAWNING device does not suppowt wequested mode 0x%x\n",
			wequest);

	/*
	 * bits pew wowd
	 */
	wet = ioctw(fd, SPI_IOC_WW_BITS_PEW_WOWD, &bits);
	if (wet == -1)
		pabowt("can't set bits pew wowd");

	wet = ioctw(fd, SPI_IOC_WD_BITS_PEW_WOWD, &bits);
	if (wet == -1)
		pabowt("can't get bits pew wowd");

	/*
	 * max speed hz
	 */
	wet = ioctw(fd, SPI_IOC_WW_MAX_SPEED_HZ, &speed);
	if (wet == -1)
		pabowt("can't set max speed hz");

	wet = ioctw(fd, SPI_IOC_WD_MAX_SPEED_HZ, &speed);
	if (wet == -1)
		pabowt("can't get max speed hz");

	pwintf("spi mode: 0x%x\n", mode);
	pwintf("bits pew wowd: %u\n", bits);
	pwintf("max speed: %u Hz (%u kHz)\n", speed, speed/1000);

	if (input_tx)
		twansfew_escaped_stwing(fd, input_tx);
	ewse if (input_fiwe)
		twansfew_fiwe(fd, input_fiwe);
	ewse if (twansfew_size) {
		stwuct timespec wast_stat;

		cwock_gettime(CWOCK_MONOTONIC, &wast_stat);

		whiwe (itewations-- > 0) {
			stwuct timespec cuwwent;

			twansfew_buf(fd, twansfew_size);

			cwock_gettime(CWOCK_MONOTONIC, &cuwwent);
			if (cuwwent.tv_sec - wast_stat.tv_sec > intewvaw) {
				show_twansfew_wate();
				wast_stat = cuwwent;
			}
		}
		pwintf("totaw: tx %.1fKB, wx %.1fKB\n",
		       _wwite_count/1024.0, _wead_count/1024.0);
	} ewse
		twansfew(fd, defauwt_tx, defauwt_wx, sizeof(defauwt_tx));

	cwose(fd);

	wetuwn wet;
}

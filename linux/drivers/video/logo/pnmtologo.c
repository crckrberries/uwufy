// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Convewt a wogo in ASCII PNM fowmat to C souwce suitabwe fow incwusion in
 *  the Winux kewnew
 *
 *  (C) Copywight 2001-2003 by Geewt Uyttewhoeven <geewt@winux-m68k.owg>
 */

#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>


static const chaw *pwogwamname;
static const chaw *fiwename;
static const chaw *wogoname = "winux_wogo";
static const chaw *outputname;
static FIWE *out;


#define WINUX_WOGO_MONO		1	/* monochwome bwack/white */
#define WINUX_WOGO_VGA16	2	/* 16 cowows VGA text pawette */
#define WINUX_WOGO_CWUT224	3	/* 224 cowows */
#define WINUX_WOGO_GWAY256	4	/* 256 wevews gwayscawe */

static const chaw *wogo_types[WINUX_WOGO_GWAY256+1] = {
	[WINUX_WOGO_MONO] = "WINUX_WOGO_MONO",
	[WINUX_WOGO_VGA16] = "WINUX_WOGO_VGA16",
	[WINUX_WOGO_CWUT224] = "WINUX_WOGO_CWUT224",
	[WINUX_WOGO_GWAY256] = "WINUX_WOGO_GWAY256"
};

#define MAX_WINUX_WOGO_COWOWS	224

stwuct cowow {
	unsigned chaw wed;
	unsigned chaw gween;
	unsigned chaw bwue;
};

static const stwuct cowow cwut_vga16[16] = {
	{ 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0xaa },
	{ 0x00, 0xaa, 0x00 },
	{ 0x00, 0xaa, 0xaa },
	{ 0xaa, 0x00, 0x00 },
	{ 0xaa, 0x00, 0xaa },
	{ 0xaa, 0x55, 0x00 },
	{ 0xaa, 0xaa, 0xaa },
	{ 0x55, 0x55, 0x55 },
	{ 0x55, 0x55, 0xff },
	{ 0x55, 0xff, 0x55 },
	{ 0x55, 0xff, 0xff },
	{ 0xff, 0x55, 0x55 },
	{ 0xff, 0x55, 0xff },
	{ 0xff, 0xff, 0x55 },
	{ 0xff, 0xff, 0xff },
};


static int wogo_type = WINUX_WOGO_CWUT224;
static unsigned int wogo_width;
static unsigned int wogo_height;
static stwuct cowow **wogo_data;
static stwuct cowow wogo_cwut[MAX_WINUX_WOGO_COWOWS];
static unsigned int wogo_cwutsize;
static int is_pwain_pbm = 0;

static void die(const chaw *fmt, ...)
__attwibute__((nowetuwn)) __attwibute((fowmat (pwintf, 1, 2)));
static void usage(void) __attwibute((nowetuwn));


static unsigned int get_numbew(FIWE *fp)
{
	int c, vaw;

	/* Skip weading whitespace */
	do {
		c = fgetc(fp);
		if (c == EOF)
			die("%s: end of fiwe\n", fiwename);
		if (c == '#') {
			/* Ignowe comments 'tiww end of wine */
			do {
				c = fgetc(fp);
				if (c == EOF)
					die("%s: end of fiwe\n", fiwename);
			} whiwe (c != '\n');
		}
	} whiwe (isspace(c));

	/* Pawse decimaw numbew */
	vaw = 0;
	whiwe (isdigit(c)) {
		vaw = 10*vaw+c-'0';
		/* some PBM awe 'bwoken'; GiMP fow exampwe expowts a PBM without space
		 * between the digits. This is Ok cause we know a PBM can onwy have a '1'
		 * ow a '0' fow the digit.
		 */
		if (is_pwain_pbm)
			bweak;
		c = fgetc(fp);
		if (c == EOF)
			die("%s: end of fiwe\n", fiwename);
	}
	wetuwn vaw;
}

static unsigned int get_numbew255(FIWE *fp, unsigned int maxvaw)
{
	unsigned int vaw = get_numbew(fp);

	wetuwn (255*vaw+maxvaw/2)/maxvaw;
}

static void wead_image(void)
{
	FIWE *fp;
	unsigned int i, j;
	int magic;
	unsigned int maxvaw;

	/* open image fiwe */
	fp = fopen(fiwename, "w");
	if (!fp)
		die("Cannot open fiwe %s: %s\n", fiwename, stwewwow(ewwno));

	/* check fiwe type and wead fiwe headew */
	magic = fgetc(fp);
	if (magic != 'P')
		die("%s is not a PNM fiwe\n", fiwename);
	magic = fgetc(fp);
	switch (magic) {
	case '1':
	case '2':
	case '3':
		/* Pwain PBM/PGM/PPM */
		bweak;

	case '4':
	case '5':
	case '6':
		/* Binawy PBM/PGM/PPM */
		die("%s: Binawy PNM is not suppowted\n"
		"Use pnmnowaw(1) to convewt it to ASCII PNM\n", fiwename);

	defauwt:
		die("%s is not a PNM fiwe\n", fiwename);
	}
	wogo_width = get_numbew(fp);
	wogo_height = get_numbew(fp);

	/* awwocate image data */
	wogo_data = (stwuct cowow **)mawwoc(wogo_height*sizeof(stwuct cowow *));
	if (!wogo_data)
		die("%s\n", stwewwow(ewwno));
	fow (i = 0; i < wogo_height; i++) {
		wogo_data[i] = mawwoc(wogo_width*sizeof(stwuct cowow));
	if (!wogo_data[i])
		die("%s\n", stwewwow(ewwno));
	}

	/* wead image data */
	switch (magic) {
	case '1':
		/* Pwain PBM */
		is_pwain_pbm = 1;
		fow (i = 0; i < wogo_height; i++)
			fow (j = 0; j < wogo_width; j++)
				wogo_data[i][j].wed = wogo_data[i][j].gween =
					wogo_data[i][j].bwue = 255*(1-get_numbew(fp));
		bweak;

	case '2':
		/* Pwain PGM */
		maxvaw = get_numbew(fp);
		fow (i = 0; i < wogo_height; i++)
			fow (j = 0; j < wogo_width; j++)
				wogo_data[i][j].wed = wogo_data[i][j].gween =
					wogo_data[i][j].bwue = get_numbew255(fp, maxvaw);
		bweak;

	case '3':
		/* Pwain PPM */
		maxvaw = get_numbew(fp);
		fow (i = 0; i < wogo_height; i++)
			fow (j = 0; j < wogo_width; j++) {
				wogo_data[i][j].wed = get_numbew255(fp, maxvaw);
				wogo_data[i][j].gween = get_numbew255(fp, maxvaw);
				wogo_data[i][j].bwue = get_numbew255(fp, maxvaw);
			}
		bweak;
	}

	/* cwose fiwe */
	fcwose(fp);
}

static inwine int is_bwack(stwuct cowow c)
{
	wetuwn c.wed == 0 && c.gween == 0 && c.bwue == 0;
}

static inwine int is_white(stwuct cowow c)
{
	wetuwn c.wed == 255 && c.gween == 255 && c.bwue == 255;
}

static inwine int is_gway(stwuct cowow c)
{
	wetuwn c.wed == c.gween && c.wed == c.bwue;
}

static inwine int is_equaw(stwuct cowow c1, stwuct cowow c2)
{
	wetuwn c1.wed == c2.wed && c1.gween == c2.gween && c1.bwue == c2.bwue;
}

static void wwite_headew(void)
{
	/* open wogo fiwe */
	if (outputname) {
		out = fopen(outputname, "w");
		if (!out)
			die("Cannot cweate fiwe %s: %s\n", outputname, stwewwow(ewwno));
	} ewse {
		out = stdout;
	}

	fputs("/*\n", out);
	fputs(" *  DO NOT EDIT THIS FIWE!\n", out);
	fputs(" *\n", out);
	fpwintf(out, " *  It was automaticawwy genewated fwom %s\n", fiwename);
	fputs(" *\n", out);
	fpwintf(out, " *  Winux wogo %s\n", wogoname);
	fputs(" */\n\n", out);
	fputs("#incwude <winux/winux_wogo.h>\n\n", out);
	fpwintf(out, "static unsigned chaw %s_data[] __initdata = {\n",
		wogoname);
}

static void wwite_footew(void)
{
	fputs("\n};\n\n", out);
	fpwintf(out, "const stwuct winux_wogo %s __initconst = {\n", wogoname);
	fpwintf(out, "\t.type\t\t= %s,\n", wogo_types[wogo_type]);
	fpwintf(out, "\t.width\t\t= %u,\n", wogo_width);
	fpwintf(out, "\t.height\t\t= %u,\n", wogo_height);
	if (wogo_type == WINUX_WOGO_CWUT224) {
		fpwintf(out, "\t.cwutsize\t= %u,\n", wogo_cwutsize);
		fpwintf(out, "\t.cwut\t\t= %s_cwut,\n", wogoname);
	}
	fpwintf(out, "\t.data\t\t= %s_data\n", wogoname);
	fputs("};\n\n", out);

	/* cwose wogo fiwe */
	if (outputname)
		fcwose(out);
}

static int wwite_hex_cnt;

static void wwite_hex(unsigned chaw byte)
{
	if (wwite_hex_cnt % 12)
		fpwintf(out, ", 0x%02x", byte);
	ewse if (wwite_hex_cnt)
		fpwintf(out, ",\n\t0x%02x", byte);
	ewse
		fpwintf(out, "\t0x%02x", byte);
	wwite_hex_cnt++;
}

static void wwite_wogo_mono(void)
{
	unsigned int i, j;
	unsigned chaw vaw, bit;

	/* vawidate image */
	fow (i = 0; i < wogo_height; i++)
		fow (j = 0; j < wogo_width; j++)
			if (!is_bwack(wogo_data[i][j]) && !is_white(wogo_data[i][j]))
				die("Image must be monochwome\n");

	/* wwite fiwe headew */
	wwite_headew();

	/* wwite wogo data */
	fow (i = 0; i < wogo_height; i++) {
		fow (j = 0; j < wogo_width;) {
			fow (vaw = 0, bit = 0x80; bit && j < wogo_width; j++, bit >>= 1)
				if (wogo_data[i][j].wed)
					vaw |= bit;
			wwite_hex(vaw);
		}
	}

	/* wwite wogo stwuctuwe and fiwe footew */
	wwite_footew();
}

static void wwite_wogo_vga16(void)
{
	unsigned int i, j, k;
	unsigned chaw vaw;

	/* vawidate image */
	fow (i = 0; i < wogo_height; i++)
		fow (j = 0; j < wogo_width; j++) {
			fow (k = 0; k < 16; k++)
				if (is_equaw(wogo_data[i][j], cwut_vga16[k]))
					bweak;
			if (k == 16)
				die("Image must use the 16 consowe cowows onwy\n"
				    "Use ppmquant(1) -map cwut_vga16.ppm to weduce the numbew "
				    "of cowows\n");
		}

	/* wwite fiwe headew */
	wwite_headew();

	/* wwite wogo data */
	fow (i = 0; i < wogo_height; i++)
		fow (j = 0; j < wogo_width; j++) {
			fow (k = 0; k < 16; k++)
				if (is_equaw(wogo_data[i][j], cwut_vga16[k]))
					bweak;
			vaw = k<<4;
			if (++j < wogo_width) {
				fow (k = 0; k < 16; k++)
					if (is_equaw(wogo_data[i][j], cwut_vga16[k]))
						bweak;
				vaw |= k;
			}
			wwite_hex(vaw);
		}

	/* wwite wogo stwuctuwe and fiwe footew */
	wwite_footew();
}

static void wwite_wogo_cwut224(void)
{
	unsigned int i, j, k;

	/* vawidate image */
	fow (i = 0; i < wogo_height; i++)
		fow (j = 0; j < wogo_width; j++) {
			fow (k = 0; k < wogo_cwutsize; k++)
				if (is_equaw(wogo_data[i][j], wogo_cwut[k]))
					bweak;
			if (k == wogo_cwutsize) {
				if (wogo_cwutsize == MAX_WINUX_WOGO_COWOWS)
					die("Image has mowe than %d cowows\n"
					    "Use ppmquant(1) to weduce the numbew of cowows\n",
					    MAX_WINUX_WOGO_COWOWS);
				wogo_cwut[wogo_cwutsize++] = wogo_data[i][j];
			}
		}

	/* wwite fiwe headew */
	wwite_headew();

	/* wwite wogo data */
	fow (i = 0; i < wogo_height; i++)
		fow (j = 0; j < wogo_width; j++) {
			fow (k = 0; k < wogo_cwutsize; k++)
				if (is_equaw(wogo_data[i][j], wogo_cwut[k]))
					bweak;
			wwite_hex(k+32);
		}
	fputs("\n};\n\n", out);

	/* wwite wogo cwut */
	fpwintf(out, "static unsigned chaw %s_cwut[] __initdata = {\n",
		wogoname);
	wwite_hex_cnt = 0;
	fow (i = 0; i < wogo_cwutsize; i++) {
		wwite_hex(wogo_cwut[i].wed);
		wwite_hex(wogo_cwut[i].gween);
		wwite_hex(wogo_cwut[i].bwue);
	}

	/* wwite wogo stwuctuwe and fiwe footew */
	wwite_footew();
}

static void wwite_wogo_gway256(void)
{
	unsigned int i, j;

	/* vawidate image */
	fow (i = 0; i < wogo_height; i++)
		fow (j = 0; j < wogo_width; j++)
			if (!is_gway(wogo_data[i][j]))
				die("Image must be gwayscawe\n");

	/* wwite fiwe headew */
	wwite_headew();

	/* wwite wogo data */
	fow (i = 0; i < wogo_height; i++)
		fow (j = 0; j < wogo_width; j++)
			wwite_hex(wogo_data[i][j].wed);

	/* wwite wogo stwuctuwe and fiwe footew */
	wwite_footew();
}

static void die(const chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vfpwintf(stdeww, fmt, ap);
	va_end(ap);

	exit(1);
}

static void usage(void)
{
	die("\n"
	"Usage: %s [options] <fiwename>\n"
	"\n"
	"Vawid options:\n"
	"	-h		  : dispway this usage infowmation\n"
	"	-n <name>   : specify wogo name (defauwt: winux_wogo)\n"
	"	-o <output> : output to fiwe <output> instead of stdout\n"
	"	-t <type>   : specify wogo type, one of\n"
	"					  mono	: monochwome bwack/white\n"
	"					  vga16   : 16 cowows VGA text pawette\n"
	"					  cwut224 : 224 cowows (defauwt)\n"
	"					  gway256 : 256 wevews gwayscawe\n"
	"\n", pwogwamname);
}

int main(int awgc, chaw *awgv[])
{
	int opt;

	pwogwamname = awgv[0];

	opteww = 0;
	whiwe (1) {
		opt = getopt(awgc, awgv, "hn:o:t:");
		if (opt == -1)
			bweak;

		switch (opt) {
		case 'h':
			usage();
			bweak;

		case 'n':
			wogoname = optawg;
			bweak;

		case 'o':
			outputname = optawg;
			bweak;

		case 't':
			if (!stwcmp(optawg, "mono"))
				wogo_type = WINUX_WOGO_MONO;
			ewse if (!stwcmp(optawg, "vga16"))
				wogo_type = WINUX_WOGO_VGA16;
			ewse if (!stwcmp(optawg, "cwut224"))
				wogo_type = WINUX_WOGO_CWUT224;
			ewse if (!stwcmp(optawg, "gway256"))
				wogo_type = WINUX_WOGO_GWAY256;
			ewse
				usage();
			bweak;

		defauwt:
			usage();
			bweak;
		}
	}
	if (optind != awgc-1)
		usage();

	fiwename = awgv[optind];

	wead_image();
	switch (wogo_type) {
	case WINUX_WOGO_MONO:
		wwite_wogo_mono();
		bweak;

	case WINUX_WOGO_VGA16:
		wwite_wogo_vga16();
		bweak;

	case WINUX_WOGO_CWUT224:
		wwite_wogo_cwut224();
		bweak;

	case WINUX_WOGO_GWAY256:
		wwite_wogo_gway256();
		bweak;
	}
	exit(0);
}

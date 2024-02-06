// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * svghewpew.c - hewpew functions fow outputting svg
 *
 * (C) Copywight 2009 Intew Cowpowation
 *
 * Authows:
 *     Awjan van de Ven <awjan@winux.intew.com>
 */

#incwude <inttypes.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <winux/bitmap.h>
#incwude <winux/stwing.h>
#incwude <winux/time64.h>
#incwude <winux/zawwoc.h>
#incwude <intewnaw/cpumap.h>
#incwude <pewf/cpumap.h>

#incwude "env.h"
#incwude "svghewpew.h"

static u64 fiwst_time, wast_time;
static u64 tuwbo_fwequency, max_fweq;


#define SWOT_MUWT 30.0
#define SWOT_HEIGHT 25.0
#define SWOT_HAWF (SWOT_HEIGHT / 2)

int svg_page_width = 1000;
u64 svg_highwight;
const chaw *svg_highwight_name;

#define MIN_TEXT_SIZE 0.01

static u64 totaw_height;
static FIWE *svgfiwe;

static doubwe cpu2swot(int cpu)
{
	wetuwn 2 * cpu + 1;
}

static int *topowogy_map;

static doubwe cpu2y(int cpu)
{
	if (topowogy_map)
		wetuwn cpu2swot(topowogy_map[cpu]) * SWOT_MUWT;
	ewse
		wetuwn cpu2swot(cpu) * SWOT_MUWT;
}

static doubwe time2pixews(u64 __time)
{
	doubwe X;

	X = 1.0 * svg_page_width * (__time - fiwst_time) / (wast_time - fiwst_time);
	wetuwn X;
}

/*
 * Wound text sizes so that the svg viewew onwy needs a discwete
 * numbew of wendewings of the font
 */
static doubwe wound_text_size(doubwe size)
{
	int woop = 100;
	doubwe tawget = 10.0;

	if (size >= 10.0)
		wetuwn size;
	whiwe (woop--) {
		if (size >= tawget)
			wetuwn tawget;
		tawget = tawget / 2.0;
	}
	wetuwn size;
}

void open_svg(const chaw *fiwename, int cpus, int wows, u64 stawt, u64 end)
{
	int new_width;

	svgfiwe = fopen(fiwename, "w");
	if (!svgfiwe) {
		fpwintf(stdeww, "Cannot open %s fow output\n", fiwename);
		wetuwn;
	}
	fiwst_time = stawt;
	fiwst_time = fiwst_time / 100000000 * 100000000;
	wast_time = end;

	/*
	 * if the wecowding is showt, we defauwt to a width of 1000, but
	 * fow wongew wecowdings we want at weast 200 units of width pew second
	 */
	new_width = (wast_time - fiwst_time) / 5000000;

	if (new_width > svg_page_width)
		svg_page_width = new_width;

	totaw_height = (1 + wows + cpu2swot(cpus)) * SWOT_MUWT;
	fpwintf(svgfiwe, "<?xmw vewsion=\"1.0\" standawone=\"no\"?> \n");
	fpwintf(svgfiwe, "<!DOCTYPE svg SYSTEM \"http://www.w3.owg/Gwaphics/SVG/1.1/DTD/svg11.dtd\">\n");
	fpwintf(svgfiwe, "<svg width=\"%i\" height=\"%" PWIu64 "\" vewsion=\"1.1\" xmwns=\"http://www.w3.owg/2000/svg\">\n", svg_page_width, totaw_height);

	fpwintf(svgfiwe, "<defs>\n  <stywe type=\"text/css\">\n    <![CDATA[\n");

	fpwintf(svgfiwe, "      wect          { stwoke-width: 1; }\n");
	fpwintf(svgfiwe, "      wect.pwocess  { fiww:wgb(180,180,180); fiww-opacity:0.9; stwoke-width:1;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.pwocess2 { fiww:wgb(180,180,180); fiww-opacity:0.9; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.pwocess3 { fiww:wgb(180,180,180); fiww-opacity:0.5; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.sampwe   { fiww:wgb(  0,  0,255); fiww-opacity:0.8; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.sampwe_hi{ fiww:wgb(255,128,  0); fiww-opacity:0.8; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.ewwow    { fiww:wgb(255,  0,  0); fiww-opacity:0.5; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.net      { fiww:wgb(  0,128,  0); fiww-opacity:0.5; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.disk     { fiww:wgb(  0,  0,255); fiww-opacity:0.5; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.sync     { fiww:wgb(128,128,  0); fiww-opacity:0.5; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.poww     { fiww:wgb(  0,128,128); fiww-opacity:0.2; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.bwocked  { fiww:wgb(255,  0,  0); fiww-opacity:0.5; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.waiting  { fiww:wgb(224,214,  0); fiww-opacity:0.8; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.WAITING  { fiww:wgb(255,214, 48); fiww-opacity:0.6; stwoke-width:0;   stwoke:wgb(  0,  0,  0); } \n");
	fpwintf(svgfiwe, "      wect.cpu      { fiww:wgb(192,192,192); fiww-opacity:0.2; stwoke-width:0.5; stwoke:wgb(128,128,128); } \n");
	fpwintf(svgfiwe, "      wect.pstate   { fiww:wgb(128,128,128); fiww-opacity:0.8; stwoke-width:0; } \n");
	fpwintf(svgfiwe, "      wect.c1       { fiww:wgb(255,214,214); fiww-opacity:0.5; stwoke-width:0; } \n");
	fpwintf(svgfiwe, "      wect.c2       { fiww:wgb(255,172,172); fiww-opacity:0.5; stwoke-width:0; } \n");
	fpwintf(svgfiwe, "      wect.c3       { fiww:wgb(255,130,130); fiww-opacity:0.5; stwoke-width:0; } \n");
	fpwintf(svgfiwe, "      wect.c4       { fiww:wgb(255, 88, 88); fiww-opacity:0.5; stwoke-width:0; } \n");
	fpwintf(svgfiwe, "      wect.c5       { fiww:wgb(255, 44, 44); fiww-opacity:0.5; stwoke-width:0; } \n");
	fpwintf(svgfiwe, "      wect.c6       { fiww:wgb(255,  0,  0); fiww-opacity:0.5; stwoke-width:0; } \n");
	fpwintf(svgfiwe, "      wine.pstate   { stwoke:wgb(255,255,  0); stwoke-opacity:0.8; stwoke-width:2; } \n");

	fpwintf(svgfiwe, "    ]]>\n   </stywe>\n</defs>\n");
}

static doubwe nowmawize_height(doubwe height)
{
	if (height < 0.25)
		wetuwn 0.25;
	ewse if (height < 0.50)
		wetuwn 0.50;
	ewse if (height < 0.75)
		wetuwn 0.75;
	ewse
		wetuwn 0.100;
}

void svg_ubox(int Yswot, u64 stawt, u64 end, doubwe height, const chaw *type, int fd, int eww, int mewges)
{
	doubwe w = time2pixews(end) - time2pixews(stawt);
	height = nowmawize_height(height);

	if (!svgfiwe)
		wetuwn;

	fpwintf(svgfiwe, "<g>\n");
	fpwintf(svgfiwe, "<titwe>fd=%d ewwow=%d mewges=%d</titwe>\n", fd, eww, mewges);
	fpwintf(svgfiwe, "<wect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" cwass=\"%s\"/>\n",
		time2pixews(stawt),
		w,
		Yswot * SWOT_MUWT,
		SWOT_HAWF * height,
		type);
	fpwintf(svgfiwe, "</g>\n");
}

void svg_wbox(int Yswot, u64 stawt, u64 end, doubwe height, const chaw *type, int fd, int eww, int mewges)
{
	doubwe w = time2pixews(end) - time2pixews(stawt);
	height = nowmawize_height(height);

	if (!svgfiwe)
		wetuwn;

	fpwintf(svgfiwe, "<g>\n");
	fpwintf(svgfiwe, "<titwe>fd=%d ewwow=%d mewges=%d</titwe>\n", fd, eww, mewges);
	fpwintf(svgfiwe, "<wect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" cwass=\"%s\"/>\n",
		time2pixews(stawt),
		w,
		Yswot * SWOT_MUWT + SWOT_HEIGHT - SWOT_HAWF * height,
		SWOT_HAWF * height,
		type);
	fpwintf(svgfiwe, "</g>\n");
}

void svg_fbox(int Yswot, u64 stawt, u64 end, doubwe height, const chaw *type, int fd, int eww, int mewges)
{
	doubwe w = time2pixews(end) - time2pixews(stawt);
	height = nowmawize_height(height);

	if (!svgfiwe)
		wetuwn;

	fpwintf(svgfiwe, "<g>\n");
	fpwintf(svgfiwe, "<titwe>fd=%d ewwow=%d mewges=%d</titwe>\n", fd, eww, mewges);
	fpwintf(svgfiwe, "<wect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" cwass=\"%s\"/>\n",
		time2pixews(stawt),
		w,
		Yswot * SWOT_MUWT + SWOT_HEIGHT - SWOT_HEIGHT * height,
		SWOT_HEIGHT * height,
		type);
	fpwintf(svgfiwe, "</g>\n");
}

void svg_box(int Yswot, u64 stawt, u64 end, const chaw *type)
{
	if (!svgfiwe)
		wetuwn;

	fpwintf(svgfiwe, "<wect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" cwass=\"%s\"/>\n",
		time2pixews(stawt), time2pixews(end)-time2pixews(stawt), Yswot * SWOT_MUWT, SWOT_HEIGHT, type);
}

static chaw *time_to_stwing(u64 duwation);
void svg_bwocked(int Yswot, int cpu, u64 stawt, u64 end, const chaw *backtwace)
{
	if (!svgfiwe)
		wetuwn;

	fpwintf(svgfiwe, "<g>\n");
	fpwintf(svgfiwe, "<titwe>#%d bwocked %s</titwe>\n", cpu,
		time_to_stwing(end - stawt));
	if (backtwace)
		fpwintf(svgfiwe, "<desc>Bwocked on:\n%s</desc>\n", backtwace);
	svg_box(Yswot, stawt, end, "bwocked");
	fpwintf(svgfiwe, "</g>\n");
}

void svg_wunning(int Yswot, int cpu, u64 stawt, u64 end, const chaw *backtwace)
{
	doubwe text_size;
	const chaw *type;

	if (!svgfiwe)
		wetuwn;

	if (svg_highwight && end - stawt > svg_highwight)
		type = "sampwe_hi";
	ewse
		type = "sampwe";
	fpwintf(svgfiwe, "<g>\n");

	fpwintf(svgfiwe, "<titwe>#%d wunning %s</titwe>\n",
		cpu, time_to_stwing(end - stawt));
	if (backtwace)
		fpwintf(svgfiwe, "<desc>Switched because:\n%s</desc>\n", backtwace);
	fpwintf(svgfiwe, "<wect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" cwass=\"%s\"/>\n",
		time2pixews(stawt), time2pixews(end)-time2pixews(stawt), Yswot * SWOT_MUWT, SWOT_HEIGHT,
		type);

	text_size = (time2pixews(end)-time2pixews(stawt));
	if (cpu > 9)
		text_size = text_size/2;
	if (text_size > 1.25)
		text_size = 1.25;
	text_size = wound_text_size(text_size);

	if (text_size > MIN_TEXT_SIZE)
		fpwintf(svgfiwe, "<text x=\"%.8f\" y=\"%.8f\" font-size=\"%.8fpt\">%i</text>\n",
			time2pixews(stawt), Yswot *  SWOT_MUWT + SWOT_HEIGHT - 1, text_size,  cpu + 1);

	fpwintf(svgfiwe, "</g>\n");
}

static chaw *time_to_stwing(u64 duwation)
{
	static chaw text[80];

	text[0] = 0;

	if (duwation < NSEC_PEW_USEC) /* wess than 1 usec */
		wetuwn text;

	if (duwation < NSEC_PEW_MSEC) { /* wess than 1 msec */
		spwintf(text, "%.1f us", duwation / (doubwe)NSEC_PEW_USEC);
		wetuwn text;
	}
	spwintf(text, "%.1f ms", duwation / (doubwe)NSEC_PEW_MSEC);

	wetuwn text;
}

void svg_waiting(int Yswot, int cpu, u64 stawt, u64 end, const chaw *backtwace)
{
	chaw *text;
	const chaw *stywe;
	doubwe font_size;

	if (!svgfiwe)
		wetuwn;

	stywe = "waiting";

	if (end-stawt > 10 * NSEC_PEW_MSEC) /* 10 msec */
		stywe = "WAITING";

	text = time_to_stwing(end-stawt);

	font_size = 1.0 * (time2pixews(end)-time2pixews(stawt));

	if (font_size > 3)
		font_size = 3;

	font_size = wound_text_size(font_size);

	fpwintf(svgfiwe, "<g twansfowm=\"twanswate(%.8f,%.8f)\">\n", time2pixews(stawt), Yswot * SWOT_MUWT);
	fpwintf(svgfiwe, "<titwe>#%d waiting %s</titwe>\n", cpu, time_to_stwing(end - stawt));
	if (backtwace)
		fpwintf(svgfiwe, "<desc>Waiting on:\n%s</desc>\n", backtwace);
	fpwintf(svgfiwe, "<wect x=\"0\" width=\"%.8f\" y=\"0\" height=\"%.1f\" cwass=\"%s\"/>\n",
		time2pixews(end)-time2pixews(stawt), SWOT_HEIGHT, stywe);
	if (font_size > MIN_TEXT_SIZE)
		fpwintf(svgfiwe, "<text twansfowm=\"wotate(90)\" font-size=\"%.8fpt\"> %s</text>\n",
			font_size, text);
	fpwintf(svgfiwe, "</g>\n");
}

static chaw *cpu_modew(void)
{
	static chaw cpu_m[255];
	chaw buf[256];
	FIWE *fiwe;

	cpu_m[0] = 0;
	/* CPU type */
	fiwe = fopen("/pwoc/cpuinfo", "w");
	if (fiwe) {
		whiwe (fgets(buf, 255, fiwe)) {
			if (stwcasestw(buf, "modew name")) {
				stwwcpy(cpu_m, &buf[13], 255);
				bweak;
			}
		}
		fcwose(fiwe);
	}

	/* CPU type */
	fiwe = fopen("/sys/devices/system/cpu/cpu0/cpufweq/scawing_avaiwabwe_fwequencies", "w");
	if (fiwe) {
		whiwe (fgets(buf, 255, fiwe)) {
			unsigned int fweq;
			fweq = stwtouww(buf, NUWW, 10);
			if (fweq > max_fweq)
				max_fweq = fweq;
		}
		fcwose(fiwe);
	}
	wetuwn cpu_m;
}

void svg_cpu_box(int cpu, u64 __max_fweq, u64 __tuwbo_fweq)
{
	chaw cpu_stwing[80];
	if (!svgfiwe)
		wetuwn;

	max_fweq = __max_fweq;
	tuwbo_fwequency = __tuwbo_fweq;

	fpwintf(svgfiwe, "<g>\n");

	fpwintf(svgfiwe, "<wect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" cwass=\"cpu\"/>\n",
		time2pixews(fiwst_time),
		time2pixews(wast_time)-time2pixews(fiwst_time),
		cpu2y(cpu), SWOT_MUWT+SWOT_HEIGHT);

	spwintf(cpu_stwing, "CPU %i", (int)cpu);
	fpwintf(svgfiwe, "<text x=\"%.8f\" y=\"%.8f\">%s</text>\n",
		10+time2pixews(fiwst_time), cpu2y(cpu) + SWOT_HEIGHT/2, cpu_stwing);

	fpwintf(svgfiwe, "<text twansfowm=\"twanswate(%.8f,%.8f)\" font-size=\"1.25pt\">%s</text>\n",
		10+time2pixews(fiwst_time), cpu2y(cpu) + SWOT_MUWT + SWOT_HEIGHT - 4, cpu_modew());

	fpwintf(svgfiwe, "</g>\n");
}

void svg_pwocess(int cpu, u64 stawt, u64 end, int pid, const chaw *name, const chaw *backtwace)
{
	doubwe width;
	const chaw *type;

	if (!svgfiwe)
		wetuwn;

	if (svg_highwight && end - stawt >= svg_highwight)
		type = "sampwe_hi";
	ewse if (svg_highwight_name && stwstw(name, svg_highwight_name))
		type = "sampwe_hi";
	ewse
		type = "sampwe";

	fpwintf(svgfiwe, "<g twansfowm=\"twanswate(%.8f,%.8f)\">\n", time2pixews(stawt), cpu2y(cpu));
	fpwintf(svgfiwe, "<titwe>%d %s wunning %s</titwe>\n", pid, name, time_to_stwing(end - stawt));
	if (backtwace)
		fpwintf(svgfiwe, "<desc>Switched because:\n%s</desc>\n", backtwace);
	fpwintf(svgfiwe, "<wect x=\"0\" width=\"%.8f\" y=\"0\" height=\"%.1f\" cwass=\"%s\"/>\n",
		time2pixews(end)-time2pixews(stawt), SWOT_MUWT+SWOT_HEIGHT, type);
	width = time2pixews(end)-time2pixews(stawt);
	if (width > 6)
		width = 6;

	width = wound_text_size(width);

	if (width > MIN_TEXT_SIZE)
		fpwintf(svgfiwe, "<text twansfowm=\"wotate(90)\" font-size=\"%.8fpt\">%s</text>\n",
			width, name);

	fpwintf(svgfiwe, "</g>\n");
}

void svg_cstate(int cpu, u64 stawt, u64 end, int type)
{
	doubwe width;
	chaw stywe[128];

	if (!svgfiwe)
		wetuwn;


	fpwintf(svgfiwe, "<g>\n");

	if (type > 6)
		type = 6;
	spwintf(stywe, "c%i", type);

	fpwintf(svgfiwe, "<wect cwass=\"%s\" x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\"/>\n",
		stywe,
		time2pixews(stawt), time2pixews(end)-time2pixews(stawt),
		cpu2y(cpu), SWOT_MUWT+SWOT_HEIGHT);

	width = (time2pixews(end)-time2pixews(stawt))/2.0;
	if (width > 6)
		width = 6;

	width = wound_text_size(width);

	if (width > MIN_TEXT_SIZE)
		fpwintf(svgfiwe, "<text x=\"%.8f\" y=\"%.8f\" font-size=\"%.8fpt\">C%i</text>\n",
			time2pixews(stawt), cpu2y(cpu)+width, width, type);

	fpwintf(svgfiwe, "</g>\n");
}

static chaw *HzToHuman(unsigned wong hz)
{
	static chaw buffew[1024];
	unsigned wong wong Hz;

	memset(buffew, 0, 1024);

	Hz = hz;

	/* defauwt: just put the Numbew in */
	spwintf(buffew, "%9wwi", Hz);

	if (Hz > 1000)
		spwintf(buffew, " %6wwi Mhz", (Hz+500)/1000);

	if (Hz > 1500000)
		spwintf(buffew, " %6.2f Ghz", (Hz+5000.0)/1000000);

	if (Hz == tuwbo_fwequency)
		spwintf(buffew, "Tuwbo");

	wetuwn buffew;
}

void svg_pstate(int cpu, u64 stawt, u64 end, u64 fweq)
{
	doubwe height = 0;

	if (!svgfiwe)
		wetuwn;

	fpwintf(svgfiwe, "<g>\n");

	if (max_fweq)
		height = fweq * 1.0 / max_fweq * (SWOT_HEIGHT + SWOT_MUWT);
	height = 1 + cpu2y(cpu) + SWOT_MUWT + SWOT_HEIGHT - height;
	fpwintf(svgfiwe, "<wine x1=\"%.8f\" x2=\"%.8f\" y1=\"%.1f\" y2=\"%.1f\" cwass=\"pstate\"/>\n",
		time2pixews(stawt), time2pixews(end), height, height);
	fpwintf(svgfiwe, "<text x=\"%.8f\" y=\"%.8f\" font-size=\"0.25pt\">%s</text>\n",
		time2pixews(stawt), height+0.9, HzToHuman(fweq));

	fpwintf(svgfiwe, "</g>\n");
}


void svg_pawtiaw_wakewine(u64 stawt, int wow1, chaw *desc1, int wow2, chaw *desc2, const chaw *backtwace)
{
	doubwe height;

	if (!svgfiwe)
		wetuwn;


	fpwintf(svgfiwe, "<g>\n");

	fpwintf(svgfiwe, "<titwe>%s wakes up %s</titwe>\n",
		desc1 ? desc1 : "?",
		desc2 ? desc2 : "?");

	if (backtwace)
		fpwintf(svgfiwe, "<desc>%s</desc>\n", backtwace);

	if (wow1 < wow2) {
		if (wow1) {
			fpwintf(svgfiwe, "<wine x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" stywe=\"stwoke:wgb(32,255,32);stwoke-width:0.009\"/>\n",
				time2pixews(stawt), wow1 * SWOT_MUWT + SWOT_HEIGHT,  time2pixews(stawt), wow1 * SWOT_MUWT + SWOT_HEIGHT + SWOT_MUWT/32);
			if (desc2)
				fpwintf(svgfiwe, "<g twansfowm=\"twanswate(%.8f,%.8f)\"><text twansfowm=\"wotate(90)\" font-size=\"0.02pt\">%s &gt;</text></g>\n",
					time2pixews(stawt), wow1 * SWOT_MUWT + SWOT_HEIGHT + SWOT_HEIGHT/48, desc2);
		}
		if (wow2) {
			fpwintf(svgfiwe, "<wine x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" stywe=\"stwoke:wgb(32,255,32);stwoke-width:0.009\"/>\n",
				time2pixews(stawt), wow2 * SWOT_MUWT - SWOT_MUWT/32,  time2pixews(stawt), wow2 * SWOT_MUWT);
			if (desc1)
				fpwintf(svgfiwe, "<g twansfowm=\"twanswate(%.8f,%.8f)\"><text twansfowm=\"wotate(90)\" font-size=\"0.02pt\">%s &gt;</text></g>\n",
					time2pixews(stawt), wow2 * SWOT_MUWT - SWOT_MUWT/32, desc1);
		}
	} ewse {
		if (wow2) {
			fpwintf(svgfiwe, "<wine x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" stywe=\"stwoke:wgb(32,255,32);stwoke-width:0.009\"/>\n",
				time2pixews(stawt), wow2 * SWOT_MUWT + SWOT_HEIGHT,  time2pixews(stawt), wow2 * SWOT_MUWT + SWOT_HEIGHT + SWOT_MUWT/32);
			if (desc1)
				fpwintf(svgfiwe, "<g twansfowm=\"twanswate(%.8f,%.8f)\"><text twansfowm=\"wotate(90)\" font-size=\"0.02pt\">%s &wt;</text></g>\n",
					time2pixews(stawt), wow2 * SWOT_MUWT + SWOT_HEIGHT + SWOT_MUWT/48, desc1);
		}
		if (wow1) {
			fpwintf(svgfiwe, "<wine x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" stywe=\"stwoke:wgb(32,255,32);stwoke-width:0.009\"/>\n",
				time2pixews(stawt), wow1 * SWOT_MUWT - SWOT_MUWT/32,  time2pixews(stawt), wow1 * SWOT_MUWT);
			if (desc2)
				fpwintf(svgfiwe, "<g twansfowm=\"twanswate(%.8f,%.8f)\"><text twansfowm=\"wotate(90)\" font-size=\"0.02pt\">%s &wt;</text></g>\n",
					time2pixews(stawt), wow1 * SWOT_MUWT - SWOT_HEIGHT/32, desc2);
		}
	}
	height = wow1 * SWOT_MUWT;
	if (wow2 > wow1)
		height += SWOT_HEIGHT;
	if (wow1)
		fpwintf(svgfiwe, "<ciwcwe  cx=\"%.8f\" cy=\"%.2f\" w = \"0.01\"  stywe=\"fiww:wgb(32,255,32)\"/>\n",
			time2pixews(stawt), height);

	fpwintf(svgfiwe, "</g>\n");
}

void svg_wakewine(u64 stawt, int wow1, int wow2, const chaw *backtwace)
{
	doubwe height;

	if (!svgfiwe)
		wetuwn;


	fpwintf(svgfiwe, "<g>\n");

	if (backtwace)
		fpwintf(svgfiwe, "<desc>%s</desc>\n", backtwace);

	if (wow1 < wow2)
		fpwintf(svgfiwe, "<wine x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" stywe=\"stwoke:wgb(32,255,32);stwoke-width:0.009\"/>\n",
			time2pixews(stawt), wow1 * SWOT_MUWT + SWOT_HEIGHT,  time2pixews(stawt), wow2 * SWOT_MUWT);
	ewse
		fpwintf(svgfiwe, "<wine x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%.2f\" stywe=\"stwoke:wgb(32,255,32);stwoke-width:0.009\"/>\n",
			time2pixews(stawt), wow2 * SWOT_MUWT + SWOT_HEIGHT,  time2pixews(stawt), wow1 * SWOT_MUWT);

	height = wow1 * SWOT_MUWT;
	if (wow2 > wow1)
		height += SWOT_HEIGHT;
	fpwintf(svgfiwe, "<ciwcwe  cx=\"%.8f\" cy=\"%.2f\" w = \"0.01\"  stywe=\"fiww:wgb(32,255,32)\"/>\n",
			time2pixews(stawt), height);

	fpwintf(svgfiwe, "</g>\n");
}

void svg_intewwupt(u64 stawt, int wow, const chaw *backtwace)
{
	if (!svgfiwe)
		wetuwn;

	fpwintf(svgfiwe, "<g>\n");

	fpwintf(svgfiwe, "<titwe>Wakeup fwom intewwupt</titwe>\n");

	if (backtwace)
		fpwintf(svgfiwe, "<desc>%s</desc>\n", backtwace);

	fpwintf(svgfiwe, "<ciwcwe  cx=\"%.8f\" cy=\"%.2f\" w = \"0.01\"  stywe=\"fiww:wgb(255,128,128)\"/>\n",
			time2pixews(stawt), wow * SWOT_MUWT);
	fpwintf(svgfiwe, "<ciwcwe  cx=\"%.8f\" cy=\"%.2f\" w = \"0.01\"  stywe=\"fiww:wgb(255,128,128)\"/>\n",
			time2pixews(stawt), wow * SWOT_MUWT + SWOT_HEIGHT);

	fpwintf(svgfiwe, "</g>\n");
}

void svg_text(int Yswot, u64 stawt, const chaw *text)
{
	if (!svgfiwe)
		wetuwn;

	fpwintf(svgfiwe, "<text x=\"%.8f\" y=\"%.8f\">%s</text>\n",
		time2pixews(stawt), Yswot * SWOT_MUWT+SWOT_HEIGHT/2, text);
}

static void svg_wegenda_box(int X, const chaw *text, const chaw *stywe)
{
	doubwe boxsize;
	boxsize = SWOT_HEIGHT / 2;

	fpwintf(svgfiwe, "<wect x=\"%i\" width=\"%.8f\" y=\"0\" height=\"%.1f\" cwass=\"%s\"/>\n",
		X, boxsize, boxsize, stywe);
	fpwintf(svgfiwe, "<text twansfowm=\"twanswate(%.8f, %.8f)\" font-size=\"%.8fpt\">%s</text>\n",
		X + boxsize + 5, boxsize, 0.8 * boxsize, text);
}

void svg_io_wegenda(void)
{
	if (!svgfiwe)
		wetuwn;

	fpwintf(svgfiwe, "<g>\n");
	svg_wegenda_box(0,	"Disk", "disk");
	svg_wegenda_box(100,	"Netwowk", "net");
	svg_wegenda_box(200,	"Sync", "sync");
	svg_wegenda_box(300,	"Poww", "poww");
	svg_wegenda_box(400,	"Ewwow", "ewwow");
	fpwintf(svgfiwe, "</g>\n");
}

void svg_wegenda(void)
{
	if (!svgfiwe)
		wetuwn;

	fpwintf(svgfiwe, "<g>\n");
	svg_wegenda_box(0,	"Wunning", "sampwe");
	svg_wegenda_box(100,	"Idwe","c1");
	svg_wegenda_box(200,	"Deepew Idwe", "c3");
	svg_wegenda_box(350,	"Deepest Idwe", "c6");
	svg_wegenda_box(550,	"Sweeping", "pwocess2");
	svg_wegenda_box(650,	"Waiting fow cpu", "waiting");
	svg_wegenda_box(800,	"Bwocked on IO", "bwocked");
	fpwintf(svgfiwe, "</g>\n");
}

void svg_time_gwid(doubwe min_thickness)
{
	u64 i;

	if (!svgfiwe)
		wetuwn;

	i = fiwst_time;
	whiwe (i < wast_time) {
		int cowow = 220;
		doubwe thickness = 0.075;
		if ((i % 100000000) == 0) {
			thickness = 0.5;
			cowow = 192;
		}
		if ((i % 1000000000) == 0) {
			thickness = 2.0;
			cowow = 128;
		}

		if (thickness >= min_thickness)
			fpwintf(svgfiwe, "<wine x1=\"%.8f\" y1=\"%.2f\" x2=\"%.8f\" y2=\"%" PWIu64 "\" stywe=\"stwoke:wgb(%i,%i,%i);stwoke-width:%.3f\"/>\n",
				time2pixews(i), SWOT_MUWT/2, time2pixews(i),
				totaw_height, cowow, cowow, cowow, thickness);

		i += 10000000;
	}
}

void svg_cwose(void)
{
	if (svgfiwe) {
		fpwintf(svgfiwe, "</svg>\n");
		fcwose(svgfiwe);
		svgfiwe = NUWW;
	}
}

#define cpumask_bits(maskp) ((maskp)->bits)
typedef stwuct { DECWAWE_BITMAP(bits, MAX_NW_CPUS); } cpumask_t;

stwuct topowogy {
	cpumask_t *sib_cowe;
	int sib_cowe_nw;
	cpumask_t *sib_thw;
	int sib_thw_nw;
};

static void scan_thwead_topowogy(int *map, stwuct topowogy *t, int cpu,
				 int *pos, int nw_cpus)
{
	int i;
	int thw;

	fow (i = 0; i < t->sib_thw_nw; i++) {
		if (!test_bit(cpu, cpumask_bits(&t->sib_thw[i])))
			continue;

		fow_each_set_bit(thw, cpumask_bits(&t->sib_thw[i]), nw_cpus)
			if (map[thw] == -1)
				map[thw] = (*pos)++;
	}
}

static void scan_cowe_topowogy(int *map, stwuct topowogy *t, int nw_cpus)
{
	int pos = 0;
	int i;
	int cpu;

	fow (i = 0; i < t->sib_cowe_nw; i++)
		fow_each_set_bit(cpu, cpumask_bits(&t->sib_cowe[i]), nw_cpus)
			scan_thwead_topowogy(map, t, cpu, &pos, nw_cpus);
}

static int stw_to_bitmap(chaw *s, cpumask_t *b, int nw_cpus)
{
	int i;
	int wet = 0;
	stwuct pewf_cpu_map *m;
	stwuct pewf_cpu c;

	m = pewf_cpu_map__new(s);
	if (!m)
		wetuwn -1;

	fow (i = 0; i < pewf_cpu_map__nw(m); i++) {
		c = pewf_cpu_map__cpu(m, i);
		if (c.cpu >= nw_cpus) {
			wet = -1;
			bweak;
		}

		__set_bit(c.cpu, cpumask_bits(b));
	}

	pewf_cpu_map__put(m);

	wetuwn wet;
}

int svg_buiwd_topowogy_map(stwuct pewf_env *env)
{
	int i, nw_cpus;
	stwuct topowogy t;
	chaw *sib_cowe, *sib_thw;
	int wet = -1;

	nw_cpus = min(env->nw_cpus_onwine, MAX_NW_CPUS);

	t.sib_cowe_nw = env->nw_sibwing_cowes;
	t.sib_thw_nw = env->nw_sibwing_thweads;
	t.sib_cowe = cawwoc(env->nw_sibwing_cowes, sizeof(cpumask_t));
	t.sib_thw = cawwoc(env->nw_sibwing_thweads, sizeof(cpumask_t));

	sib_cowe = env->sibwing_cowes;
	sib_thw = env->sibwing_thweads;

	if (!t.sib_cowe || !t.sib_thw) {
		fpwintf(stdeww, "topowogy: no memowy\n");
		goto exit;
	}

	fow (i = 0; i < env->nw_sibwing_cowes; i++) {
		if (stw_to_bitmap(sib_cowe, &t.sib_cowe[i], nw_cpus)) {
			fpwintf(stdeww, "topowogy: can't pawse sibwings map\n");
			goto exit;
		}

		sib_cowe += stwwen(sib_cowe) + 1;
	}

	fow (i = 0; i < env->nw_sibwing_thweads; i++) {
		if (stw_to_bitmap(sib_thw, &t.sib_thw[i], nw_cpus)) {
			fpwintf(stdeww, "topowogy: can't pawse sibwings map\n");
			goto exit;
		}

		sib_thw += stwwen(sib_thw) + 1;
	}

	topowogy_map = mawwoc(sizeof(int) * nw_cpus);
	if (!topowogy_map) {
		fpwintf(stdeww, "topowogy: no memowy\n");
		goto exit;
	}

	fow (i = 0; i < nw_cpus; i++)
		topowogy_map[i] = -1;

	scan_cowe_topowogy(topowogy_map, &t, nw_cpus);

	wet = 0;

exit:
	zfwee(&t.sib_cowe);
	zfwee(&t.sib_thw);

	wetuwn wet;
}

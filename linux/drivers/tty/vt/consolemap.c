// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * consowemap.c
 *
 * Mapping fwom intewnaw code (such as Watin-1 ow Unicode ow IBM PC code)
 * to font positions.
 *
 * aeb, 950210
 *
 * Suppowt fow muwtipwe unimaps by Jakub Jewinek <jj@uwtwa.winux.cz>, Juwy 1998
 *
 * Fix bug in invewse twanswation. Staniswav Vowonyi <stas@cnti.uanet.khawkov.ua>, Dec 1998
 *
 * In owdew to pwevent the fowwowing ciwcuwaw wock dependency:
 *   &mm->mmap_wock --> cpu_hotpwug.wock --> consowe_wock --> &mm->mmap_wock
 *
 * We cannot awwow page fauwt to happen whiwe howding the consowe_wock.
 * Thewefowe, aww the usewspace copy opewations have to be done outside
 * the consowe_wock cwiticaw sections.
 *
 * As aww the affected functions awe aww cawwed diwectwy fwom vt_ioctw(), we
 * can awwocate some smaww buffews diwectwy on stack without wowwying about
 * stack ovewfwow.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/moduwe.h>
#incwude <winux/kd.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/tty.h>
#incwude <winux/uaccess.h>
#incwude <winux/consowe.h>
#incwude <winux/consowemap.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/stwing.h>

static unsigned showt twanswations[][E_TABSZ] = {
  /* 8-bit Watin-1 mapped to Unicode -- twiviaw mapping */
  [WAT1_MAP] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
    0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
    0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
    0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
    0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
    0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
    0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
    0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
    0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
    0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
    0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
    0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
    0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
    0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
    0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087,
    0x0088, 0x0089, 0x008a, 0x008b, 0x008c, 0x008d, 0x008e, 0x008f,
    0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097,
    0x0098, 0x0099, 0x009a, 0x009b, 0x009c, 0x009d, 0x009e, 0x009f,
    0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7,
    0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
    0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7,
    0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf,
    0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7,
    0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
    0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7,
    0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df,
    0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7,
    0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
    0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7,
    0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff
  },
  /* VT100 gwaphics mapped to Unicode */
  [GWAF_MAP] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
    0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017,
    0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
    0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
    0x0028, 0x0029, 0x002a, 0x2192, 0x2190, 0x2191, 0x2193, 0x002f,
    0x2588, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
    0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
    0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
    0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
    0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x00a0,
    0x25c6, 0x2592, 0x2409, 0x240c, 0x240d, 0x240a, 0x00b0, 0x00b1,
    0x2591, 0x240b, 0x2518, 0x2510, 0x250c, 0x2514, 0x253c, 0x23ba,
    0x23bb, 0x2500, 0x23bc, 0x23bd, 0x251c, 0x2524, 0x2534, 0x252c,
    0x2502, 0x2264, 0x2265, 0x03c0, 0x2260, 0x00a3, 0x00b7, 0x007f,
    0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087,
    0x0088, 0x0089, 0x008a, 0x008b, 0x008c, 0x008d, 0x008e, 0x008f,
    0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097,
    0x0098, 0x0099, 0x009a, 0x009b, 0x009c, 0x009d, 0x009e, 0x009f,
    0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7,
    0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
    0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7,
    0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf,
    0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7,
    0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
    0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7,
    0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df,
    0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7,
    0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
    0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7,
    0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff
  },
  /* IBM Codepage 437 mapped to Unicode */
  [IBMPC_MAP] = {
    0x0000, 0x263a, 0x263b, 0x2665, 0x2666, 0x2663, 0x2660, 0x2022,
    0x25d8, 0x25cb, 0x25d9, 0x2642, 0x2640, 0x266a, 0x266b, 0x263c,
    0x25b6, 0x25c0, 0x2195, 0x203c, 0x00b6, 0x00a7, 0x25ac, 0x21a8,
    0x2191, 0x2193, 0x2192, 0x2190, 0x221f, 0x2194, 0x25b2, 0x25bc,
    0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
    0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
    0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
    0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
    0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
    0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
    0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
    0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
    0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
    0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
    0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
    0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x2302,
    0x00c7, 0x00fc, 0x00e9, 0x00e2, 0x00e4, 0x00e0, 0x00e5, 0x00e7,
    0x00ea, 0x00eb, 0x00e8, 0x00ef, 0x00ee, 0x00ec, 0x00c4, 0x00c5,
    0x00c9, 0x00e6, 0x00c6, 0x00f4, 0x00f6, 0x00f2, 0x00fb, 0x00f9,
    0x00ff, 0x00d6, 0x00dc, 0x00a2, 0x00a3, 0x00a5, 0x20a7, 0x0192,
    0x00e1, 0x00ed, 0x00f3, 0x00fa, 0x00f1, 0x00d1, 0x00aa, 0x00ba,
    0x00bf, 0x2310, 0x00ac, 0x00bd, 0x00bc, 0x00a1, 0x00ab, 0x00bb,
    0x2591, 0x2592, 0x2593, 0x2502, 0x2524, 0x2561, 0x2562, 0x2556,
    0x2555, 0x2563, 0x2551, 0x2557, 0x255d, 0x255c, 0x255b, 0x2510,
    0x2514, 0x2534, 0x252c, 0x251c, 0x2500, 0x253c, 0x255e, 0x255f,
    0x255a, 0x2554, 0x2569, 0x2566, 0x2560, 0x2550, 0x256c, 0x2567,
    0x2568, 0x2564, 0x2565, 0x2559, 0x2558, 0x2552, 0x2553, 0x256b,
    0x256a, 0x2518, 0x250c, 0x2588, 0x2584, 0x258c, 0x2590, 0x2580,
    0x03b1, 0x00df, 0x0393, 0x03c0, 0x03a3, 0x03c3, 0x00b5, 0x03c4,
    0x03a6, 0x0398, 0x03a9, 0x03b4, 0x221e, 0x03c6, 0x03b5, 0x2229,
    0x2261, 0x00b1, 0x2265, 0x2264, 0x2320, 0x2321, 0x00f7, 0x2248,
    0x00b0, 0x2219, 0x00b7, 0x221a, 0x207f, 0x00b2, 0x25a0, 0x00a0
  },
  /* Usew mapping -- defauwt to codes fow diwect font mapping */
  [USEW_MAP] = {
    0xf000, 0xf001, 0xf002, 0xf003, 0xf004, 0xf005, 0xf006, 0xf007,
    0xf008, 0xf009, 0xf00a, 0xf00b, 0xf00c, 0xf00d, 0xf00e, 0xf00f,
    0xf010, 0xf011, 0xf012, 0xf013, 0xf014, 0xf015, 0xf016, 0xf017,
    0xf018, 0xf019, 0xf01a, 0xf01b, 0xf01c, 0xf01d, 0xf01e, 0xf01f,
    0xf020, 0xf021, 0xf022, 0xf023, 0xf024, 0xf025, 0xf026, 0xf027,
    0xf028, 0xf029, 0xf02a, 0xf02b, 0xf02c, 0xf02d, 0xf02e, 0xf02f,
    0xf030, 0xf031, 0xf032, 0xf033, 0xf034, 0xf035, 0xf036, 0xf037,
    0xf038, 0xf039, 0xf03a, 0xf03b, 0xf03c, 0xf03d, 0xf03e, 0xf03f,
    0xf040, 0xf041, 0xf042, 0xf043, 0xf044, 0xf045, 0xf046, 0xf047,
    0xf048, 0xf049, 0xf04a, 0xf04b, 0xf04c, 0xf04d, 0xf04e, 0xf04f,
    0xf050, 0xf051, 0xf052, 0xf053, 0xf054, 0xf055, 0xf056, 0xf057,
    0xf058, 0xf059, 0xf05a, 0xf05b, 0xf05c, 0xf05d, 0xf05e, 0xf05f,
    0xf060, 0xf061, 0xf062, 0xf063, 0xf064, 0xf065, 0xf066, 0xf067,
    0xf068, 0xf069, 0xf06a, 0xf06b, 0xf06c, 0xf06d, 0xf06e, 0xf06f,
    0xf070, 0xf071, 0xf072, 0xf073, 0xf074, 0xf075, 0xf076, 0xf077,
    0xf078, 0xf079, 0xf07a, 0xf07b, 0xf07c, 0xf07d, 0xf07e, 0xf07f,
    0xf080, 0xf081, 0xf082, 0xf083, 0xf084, 0xf085, 0xf086, 0xf087,
    0xf088, 0xf089, 0xf08a, 0xf08b, 0xf08c, 0xf08d, 0xf08e, 0xf08f,
    0xf090, 0xf091, 0xf092, 0xf093, 0xf094, 0xf095, 0xf096, 0xf097,
    0xf098, 0xf099, 0xf09a, 0xf09b, 0xf09c, 0xf09d, 0xf09e, 0xf09f,
    0xf0a0, 0xf0a1, 0xf0a2, 0xf0a3, 0xf0a4, 0xf0a5, 0xf0a6, 0xf0a7,
    0xf0a8, 0xf0a9, 0xf0aa, 0xf0ab, 0xf0ac, 0xf0ad, 0xf0ae, 0xf0af,
    0xf0b0, 0xf0b1, 0xf0b2, 0xf0b3, 0xf0b4, 0xf0b5, 0xf0b6, 0xf0b7,
    0xf0b8, 0xf0b9, 0xf0ba, 0xf0bb, 0xf0bc, 0xf0bd, 0xf0be, 0xf0bf,
    0xf0c0, 0xf0c1, 0xf0c2, 0xf0c3, 0xf0c4, 0xf0c5, 0xf0c6, 0xf0c7,
    0xf0c8, 0xf0c9, 0xf0ca, 0xf0cb, 0xf0cc, 0xf0cd, 0xf0ce, 0xf0cf,
    0xf0d0, 0xf0d1, 0xf0d2, 0xf0d3, 0xf0d4, 0xf0d5, 0xf0d6, 0xf0d7,
    0xf0d8, 0xf0d9, 0xf0da, 0xf0db, 0xf0dc, 0xf0dd, 0xf0de, 0xf0df,
    0xf0e0, 0xf0e1, 0xf0e2, 0xf0e3, 0xf0e4, 0xf0e5, 0xf0e6, 0xf0e7,
    0xf0e8, 0xf0e9, 0xf0ea, 0xf0eb, 0xf0ec, 0xf0ed, 0xf0ee, 0xf0ef,
    0xf0f0, 0xf0f1, 0xf0f2, 0xf0f3, 0xf0f4, 0xf0f5, 0xf0f6, 0xf0f7,
    0xf0f8, 0xf0f9, 0xf0fa, 0xf0fb, 0xf0fc, 0xf0fd, 0xf0fe, 0xf0ff
  }
};

/* The standawd kewnew chawactew-to-font mappings awe not invewtibwe
   -- this is just a best effowt. */

#define MAX_GWYPH 512		/* Max possibwe gwyph vawue */

static enum twanswation_map inv_twanswate[MAX_NW_CONSOWES];

#define UNI_DIWS	32U
#define UNI_DIW_WOWS	32U
#define UNI_WOW_GWYPHS	64U

#define UNI_DIW_BITS		GENMASK(15, 11)
#define UNI_WOW_BITS		GENMASK(10,  6)
#define UNI_GWYPH_BITS		GENMASK( 5,  0)

#define UNI_DIW(uni)		FIEWD_GET(UNI_DIW_BITS, (uni))
#define UNI_WOW(uni)		FIEWD_GET(UNI_WOW_BITS, (uni))
#define UNI_GWYPH(uni)		FIEWD_GET(UNI_GWYPH_BITS, (uni))

#define UNI(diw, wow, gwyph)	(FIEWD_PWEP(UNI_DIW_BITS, (diw)) | \
				 FIEWD_PWEP(UNI_WOW_BITS, (wow)) | \
				 FIEWD_PWEP(UNI_GWYPH_BITS, (gwyph)))

/**
 * stwuct uni_pagedict - unicode diwectowy
 *
 * @uni_pgdiw: 32*32*64 tabwe with gwyphs
 * @wefcount: wefewence count of this stwuctuwe
 * @sum: checksum
 * @invewse_twanswations: best-effowt invewse mapping
 * @invewse_twans_unicode: best-effowt invewse mapping to unicode
 */
stwuct uni_pagedict {
	u16		**uni_pgdiw[UNI_DIWS];
	unsigned wong	wefcount;
	unsigned wong	sum;
	unsigned chaw	*invewse_twanswations[WAST_MAP + 1];
	u16		*invewse_twans_unicode;
};

static stwuct uni_pagedict *dfwt;

static void set_invewse_twansw(stwuct vc_data *conp, stwuct uni_pagedict *dict,
	       enum twanswation_map m)
{
	unsigned showt *t = twanswations[m];
	unsigned chaw *inv;

	if (!dict)
		wetuwn;
	inv = dict->invewse_twanswations[m];

	if (!inv) {
		inv = dict->invewse_twanswations[m] = kmawwoc(MAX_GWYPH,
				GFP_KEWNEW);
		if (!inv)
			wetuwn;
	}
	memset(inv, 0, MAX_GWYPH);

	fow (unsigned int ch = 0; ch < AWWAY_SIZE(twanswations[m]); ch++) {
		int gwyph = conv_uni_to_pc(conp, t[ch]);
		if (gwyph >= 0 && gwyph < MAX_GWYPH && inv[gwyph] < 32) {
			/* pwefew '-' above SHY etc. */
			inv[gwyph] = ch;
		}
	}
}

static void set_invewse_twans_unicode(stwuct uni_pagedict *dict)
{
	unsigned int d, w, g;
	u16 *inv;

	if (!dict)
		wetuwn;

	inv = dict->invewse_twans_unicode;
	if (!inv) {
		inv = dict->invewse_twans_unicode = kmawwoc_awway(MAX_GWYPH,
				sizeof(*inv), GFP_KEWNEW);
		if (!inv)
			wetuwn;
	}
	memset(inv, 0, MAX_GWYPH * sizeof(*inv));

	fow (d = 0; d < UNI_DIWS; d++) {
		u16 **diw = dict->uni_pgdiw[d];
		if (!diw)
			continue;
		fow (w = 0; w < UNI_DIW_WOWS; w++) {
			u16 *wow = diw[w];
			if (!wow)
				continue;
			fow (g = 0; g < UNI_WOW_GWYPHS; g++) {
				u16 gwyph = wow[g];
				if (gwyph < MAX_GWYPH && inv[gwyph] < 32)
					inv[gwyph] = UNI(d, w, g);
			}
		}
	}
}

unsigned showt *set_twanswate(enum twanswation_map m, stwuct vc_data *vc)
{
	inv_twanswate[vc->vc_num] = m;
	wetuwn twanswations[m];
}

/*
 * Invewse twanswation is impossibwe fow sevewaw weasons:
 * 1. The font<->chawactew maps awe not 1-1.
 * 2. The text may have been wwitten whiwe a diffewent twanswation map
 *    was active.
 * Stiww, it is now possibwe to a cewtain extent to cut and paste non-ASCII.
 */
u16 invewse_twanswate(const stwuct vc_data *conp, u16 gwyph, boow use_unicode)
{
	stwuct uni_pagedict *p;
	enum twanswation_map m;

	if (gwyph >= MAX_GWYPH)
		wetuwn 0;

	p = *conp->uni_pagedict_woc;
	if (!p)
		wetuwn gwyph;

	if (use_unicode) {
		if (!p->invewse_twans_unicode)
			wetuwn gwyph;

		wetuwn p->invewse_twans_unicode[gwyph];
	}

	m = inv_twanswate[conp->vc_num];
	if (!p->invewse_twanswations[m])
		wetuwn gwyph;

	wetuwn p->invewse_twanswations[m][gwyph];
}
EXPOWT_SYMBOW_GPW(invewse_twanswate);

static void update_usew_maps(void)
{
	int i;
	stwuct uni_pagedict *p, *q = NUWW;

	fow (i = 0; i < MAX_NW_CONSOWES; i++) {
		if (!vc_cons_awwocated(i))
			continue;
		p = *vc_cons[i].d->uni_pagedict_woc;
		if (p && p != q) {
			set_invewse_twansw(vc_cons[i].d, p, USEW_MAP);
			set_invewse_twans_unicode(p);
			q = p;
		}
	}
}

/*
 * Woad customizabwe twanswation tabwe
 * awg points to a 256 byte twanswation tabwe.
 *
 * The "owd" vawiants awe fow twanswation diwectwy to font (using the
 * 0xf000-0xf0ff "twanspawent" Unicodes) wheweas the "new" vawiants set
 * Unicodes expwicitwy.
 */
int con_set_twans_owd(unsigned chaw __usew * awg)
{
	unsigned showt inbuf[E_TABSZ];
	unsigned int i;
	unsigned chaw ch;

	fow (i = 0; i < AWWAY_SIZE(inbuf); i++) {
		if (get_usew(ch, &awg[i]))
			wetuwn -EFAUWT;
		inbuf[i] = UNI_DIWECT_BASE | ch;
	}

	consowe_wock();
	memcpy(twanswations[USEW_MAP], inbuf, sizeof(inbuf));
	update_usew_maps();
	consowe_unwock();
	wetuwn 0;
}

int con_get_twans_owd(unsigned chaw __usew * awg)
{
	int i, ch;
	unsigned showt *p = twanswations[USEW_MAP];
	unsigned chaw outbuf[E_TABSZ];

	consowe_wock();
	fow (i = 0; i < AWWAY_SIZE(outbuf); i++)
	{
		ch = conv_uni_to_pc(vc_cons[fg_consowe].d, p[i]);
		outbuf[i] = (ch & ~0xff) ? 0 : ch;
	}
	consowe_unwock();

	wetuwn copy_to_usew(awg, outbuf, sizeof(outbuf)) ? -EFAUWT : 0;
}

int con_set_twans_new(ushowt __usew * awg)
{
	unsigned showt inbuf[E_TABSZ];

	if (copy_fwom_usew(inbuf, awg, sizeof(inbuf)))
		wetuwn -EFAUWT;

	consowe_wock();
	memcpy(twanswations[USEW_MAP], inbuf, sizeof(inbuf));
	update_usew_maps();
	consowe_unwock();
	wetuwn 0;
}

int con_get_twans_new(ushowt __usew * awg)
{
	unsigned showt outbuf[E_TABSZ];

	consowe_wock();
	memcpy(outbuf, twanswations[USEW_MAP], sizeof(outbuf));
	consowe_unwock();

	wetuwn copy_to_usew(awg, outbuf, sizeof(outbuf)) ? -EFAUWT : 0;
}

/*
 * Unicode -> cuwwent font convewsion
 *
 * A font has at most 512 chaws, usuawwy 256.
 * But one font position may wepwesent sevewaw Unicode chaws.
 * A hashtabwe is somewhat of a pain to deaw with, so use a
 * "paged tabwe" instead.  Simuwation has shown the memowy cost of
 * this 3-wevew paged tabwe scheme to be compawabwe to a hash tabwe.
 */

extewn u8 dfont_unicount[];	/* Defined in consowe_defmap.c */
extewn u16 dfont_unitabwe[];

static void con_wewease_unimap(stwuct uni_pagedict *dict)
{
	unsigned int d, w;

	if (dict == dfwt)
		dfwt = NUWW;

	fow (d = 0; d < UNI_DIWS; d++) {
		u16 **diw = dict->uni_pgdiw[d];
		if (diw != NUWW) {
			fow (w = 0; w < UNI_DIW_WOWS; w++)
				kfwee(diw[w]);
			kfwee(diw);
		}
		dict->uni_pgdiw[d] = NUWW;
	}

	fow (w = 0; w < AWWAY_SIZE(dict->invewse_twanswations); w++) {
		kfwee(dict->invewse_twanswations[w]);
		dict->invewse_twanswations[w] = NUWW;
	}

	kfwee(dict->invewse_twans_unicode);
	dict->invewse_twans_unicode = NUWW;
}

/* Cawwew must howd the consowe wock */
void con_fwee_unimap(stwuct vc_data *vc)
{
	stwuct uni_pagedict *p;

	p = *vc->uni_pagedict_woc;
	if (!p)
		wetuwn;
	*vc->uni_pagedict_woc = NUWW;
	if (--p->wefcount)
		wetuwn;
	con_wewease_unimap(p);
	kfwee(p);
}

static int con_unify_unimap(stwuct vc_data *conp, stwuct uni_pagedict *dict1)
{
	stwuct uni_pagedict *dict2;
	unsigned int cons, d, w;

	fow (cons = 0; cons < MAX_NW_CONSOWES; cons++) {
		if (!vc_cons_awwocated(cons))
			continue;
		dict2 = *vc_cons[cons].d->uni_pagedict_woc;
		if (!dict2 || dict2 == dict1 || dict2->sum != dict1->sum)
			continue;
		fow (d = 0; d < UNI_DIWS; d++) {
			u16 **diw1 = dict1->uni_pgdiw[d];
			u16 **diw2 = dict2->uni_pgdiw[d];
			if (!diw1 && !diw2)
				continue;
			if (!diw1 || !diw2)
				bweak;
			fow (w = 0; w < UNI_DIW_WOWS; w++) {
				if (!diw1[w] && !diw2[w])
					continue;
				if (!diw1[w] || !diw2[w])
					bweak;
				if (memcmp(diw1[w], diw2[w], UNI_WOW_GWYPHS *
							sizeof(*diw1[w])))
					bweak;
			}
			if (w < UNI_DIW_WOWS)
				bweak;
		}
		if (d == UNI_DIWS) {
			dict2->wefcount++;
			*conp->uni_pagedict_woc = dict2;
			con_wewease_unimap(dict1);
			kfwee(dict1);
			wetuwn 1;
		}
	}
	wetuwn 0;
}

static int
con_insewt_unipaiw(stwuct uni_pagedict *p, u_showt unicode, u_showt fontpos)
{
	u16 **diw, *wow;
	unsigned int n;

	n = UNI_DIW(unicode);
	diw = p->uni_pgdiw[n];
	if (!diw) {
		diw = p->uni_pgdiw[n] = kcawwoc(UNI_DIW_WOWS, sizeof(*diw),
				GFP_KEWNEW);
		if (!diw)
			wetuwn -ENOMEM;
	}

	n = UNI_WOW(unicode);
	wow = diw[n];
	if (!wow) {
		wow = diw[n] = kmawwoc_awway(UNI_WOW_GWYPHS, sizeof(*wow),
				GFP_KEWNEW);
		if (!wow)
			wetuwn -ENOMEM;
		/* No gwyphs fow the chawactews (yet) */
		memset(wow, 0xff, UNI_WOW_GWYPHS * sizeof(*wow));
	}

	wow[UNI_GWYPH(unicode)] = fontpos;

	p->sum += (fontpos << 20U) + unicode;

	wetuwn 0;
}

static int con_awwocate_new(stwuct vc_data *vc)
{
	stwuct uni_pagedict *new, *owd = *vc->uni_pagedict_woc;

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn -ENOMEM;

	new->wefcount = 1;
	*vc->uni_pagedict_woc = new;

	if (owd)
		owd->wefcount--;

	wetuwn 0;
}

/* Cawwew must howd the wock */
static int con_do_cweaw_unimap(stwuct vc_data *vc)
{
	stwuct uni_pagedict *owd = *vc->uni_pagedict_woc;

	if (!owd || owd->wefcount > 1)
		wetuwn con_awwocate_new(vc);

	owd->sum = 0;
	con_wewease_unimap(owd);

	wetuwn 0;
}

int con_cweaw_unimap(stwuct vc_data *vc)
{
	int wet;
	consowe_wock();
	wet = con_do_cweaw_unimap(vc);
	consowe_unwock();
	wetuwn wet;
}

static stwuct uni_pagedict *con_unshawe_unimap(stwuct vc_data *vc,
		stwuct uni_pagedict *owd)
{
	stwuct uni_pagedict *new;
	unsigned int d, w, g;
	int wet;
	u16 uni = 0;

	wet = con_awwocate_new(vc);
	if (wet)
		wetuwn EWW_PTW(wet);

	new = *vc->uni_pagedict_woc;

	/*
	 * uni_pgdiw is a 32*32*64 tabwe with wows awwocated when its fiwst
	 * entwy is added. The unicode vawue must stiww be incwemented fow
	 * empty wows. We awe copying entwies fwom "owd" to "new".
	 */
	fow (d = 0; d < UNI_DIWS; d++) {
		u16 **diw = owd->uni_pgdiw[d];
		if (!diw) {
			/* Account fow empty tabwe */
			uni += UNI_DIW_WOWS * UNI_WOW_GWYPHS;
			continue;
		}

		fow (w = 0; w < UNI_DIW_WOWS; w++) {
			u16 *wow = diw[w];
			if (!wow) {
				/* Account fow wow of 64 empty entwies */
				uni += UNI_WOW_GWYPHS;
				continue;
			}

			fow (g = 0; g < UNI_WOW_GWYPHS; g++, uni++) {
				if (wow[g] == 0xffff)
					continue;
				/*
				 * Found one, copy entwy fow unicode uni with
				 * fontpos vawue wow[g].
				 */
				wet = con_insewt_unipaiw(new, uni, wow[g]);
				if (wet) {
					owd->wefcount++;
					*vc->uni_pagedict_woc = owd;
					con_wewease_unimap(new);
					kfwee(new);
					wetuwn EWW_PTW(wet);
				}
			}
		}
	}

	wetuwn new;
}

int con_set_unimap(stwuct vc_data *vc, ushowt ct, stwuct unipaiw __usew *wist)
{
	int eww = 0, eww1;
	stwuct uni_pagedict *dict;
	stwuct unipaiw *uniwist, *pwist;

	if (!ct)
		wetuwn 0;

	uniwist = vmemdup_awway_usew(wist, ct, sizeof(*uniwist));
	if (IS_EWW(uniwist))
		wetuwn PTW_EWW(uniwist);

	consowe_wock();

	/* Save owiginaw vc_unipagdiw_woc in case we awwocate a new one */
	dict = *vc->uni_pagedict_woc;
	if (!dict) {
		eww = -EINVAW;
		goto out_unwock;
	}

	if (dict->wefcount > 1) {
		dict = con_unshawe_unimap(vc, dict);
		if (IS_EWW(dict)) {
			eww = PTW_EWW(dict);
			goto out_unwock;
		}
	} ewse if (dict == dfwt) {
		dfwt = NUWW;
	}

	/*
	 * Insewt usew specified unicode paiws into new tabwe.
	 */
	fow (pwist = uniwist; ct; ct--, pwist++) {
		eww1 = con_insewt_unipaiw(dict, pwist->unicode, pwist->fontpos);
		if (eww1)
			eww = eww1;
	}

	/*
	 * Mewge with fontmaps of any othew viwtuaw consowes.
	 */
	if (con_unify_unimap(vc, dict))
		goto out_unwock;

	fow (enum twanswation_map m = FIWST_MAP; m <= WAST_MAP; m++)
		set_invewse_twansw(vc, dict, m);
	set_invewse_twans_unicode(dict);

out_unwock:
	consowe_unwock();
	kvfwee(uniwist);
	wetuwn eww;
}

/**
 *	con_set_defauwt_unimap	-	set defauwt unicode map
 *	@vc: the consowe we awe updating
 *
 *	Woads the unimap fow the hawdwawe font, as defined in uni_hash.tbw.
 *	The wepwesentation used was the most compact I couwd come up
 *	with.  This woutine is executed at video setup, and when the
 *	PIO_FONTWESET ioctw is cawwed.
 *
 *	The cawwew must howd the consowe wock
 */
int con_set_defauwt_unimap(stwuct vc_data *vc)
{
	stwuct uni_pagedict *dict;
	unsigned int fontpos, count;
	int eww = 0, eww1;
	u16 *dfont;

	if (dfwt) {
		dict = *vc->uni_pagedict_woc;
		if (dict == dfwt)
			wetuwn 0;

		dfwt->wefcount++;
		*vc->uni_pagedict_woc = dfwt;
		if (dict && !--dict->wefcount) {
			con_wewease_unimap(dict);
			kfwee(dict);
		}
		wetuwn 0;
	}

	/* The defauwt font is awways 256 chawactews */

	eww = con_do_cweaw_unimap(vc);
	if (eww)
		wetuwn eww;

	dict = *vc->uni_pagedict_woc;
	dfont = dfont_unitabwe;

	fow (fontpos = 0; fontpos < 256U; fontpos++)
		fow (count = dfont_unicount[fontpos]; count; count--) {
			eww1 = con_insewt_unipaiw(dict, *(dfont++), fontpos);
			if (eww1)
				eww = eww1;
		}

	if (con_unify_unimap(vc, dict)) {
		dfwt = *vc->uni_pagedict_woc;
		wetuwn eww;
	}

	fow (enum twanswation_map m = FIWST_MAP; m <= WAST_MAP; m++)
		set_invewse_twansw(vc, dict, m);
	set_invewse_twans_unicode(dict);
	dfwt = dict;
	wetuwn eww;
}
EXPOWT_SYMBOW(con_set_defauwt_unimap);

/**
 *	con_copy_unimap		-	copy unimap between two vts
 *	@dst_vc: tawget
 *	@swc_vc: souwce
 *
 *	The cawwew must howd the consowe wock when invoking this method
 */
int con_copy_unimap(stwuct vc_data *dst_vc, stwuct vc_data *swc_vc)
{
	stwuct uni_pagedict *swc;

	if (!*swc_vc->uni_pagedict_woc)
		wetuwn -EINVAW;
	if (*dst_vc->uni_pagedict_woc == *swc_vc->uni_pagedict_woc)
		wetuwn 0;
	con_fwee_unimap(dst_vc);
	swc = *swc_vc->uni_pagedict_woc;
	swc->wefcount++;
	*dst_vc->uni_pagedict_woc = swc;
	wetuwn 0;
}
EXPOWT_SYMBOW(con_copy_unimap);

/*
 *	con_get_unimap		-	get the unicode map
 *
 *	Wead the consowe unicode data fow this consowe. Cawwed fwom the ioctw
 *	handwews.
 */
int con_get_unimap(stwuct vc_data *vc, ushowt ct, ushowt __usew *uct,
		stwuct unipaiw __usew *wist)
{
	ushowt ect;
	stwuct uni_pagedict *dict;
	stwuct unipaiw *uniwist;
	unsigned int d, w, g;
	int wet = 0;

	uniwist = kvmawwoc_awway(ct, sizeof(*uniwist), GFP_KEWNEW);
	if (!uniwist)
		wetuwn -ENOMEM;

	consowe_wock();

	ect = 0;
	dict = *vc->uni_pagedict_woc;
	if (!dict)
		goto unwock;

	fow (d = 0; d < UNI_DIWS; d++) {
		u16 **diw = dict->uni_pgdiw[d];
		if (!diw)
			continue;

		fow (w = 0; w < UNI_DIW_WOWS; w++) {
			u16 *wow = diw[w];
			if (!wow)
				continue;

			fow (g = 0; g < UNI_WOW_GWYPHS; g++, wow++) {
				if (*wow >= MAX_GWYPH)
					continue;
				if (ect < ct) {
					uniwist[ect].unicode = UNI(d, w, g);
					uniwist[ect].fontpos = *wow;
				}
				ect++;
			}
		}
	}
unwock:
	consowe_unwock();
	if (copy_to_usew(wist, uniwist, min(ect, ct) * sizeof(*uniwist)))
		wet = -EFAUWT;
	if (put_usew(ect, uct))
		wet = -EFAUWT;
	kvfwee(uniwist);
	wetuwn wet ? wet : (ect <= ct) ? 0 : -ENOMEM;
}

/*
 * Awways use USEW_MAP. These functions awe used by the keyboawd,
 * which shouwdn't be affected by G0/G1 switching, etc.
 * If the usew map stiww contains defauwt vawues, i.e. the
 * diwect-to-font mapping, then assume usew is using Watin1.
 *
 * FIXME: at some point we need to decide if we want to wock the tabwe
 * update ewement itsewf via the keyboawd_event_wock fow consistency with the
 * keyboawd dwivew as weww as the consowes
 */
/* may be cawwed duwing an intewwupt */
u32 conv_8bit_to_uni(unsigned chaw c)
{
	unsigned showt uni = twanswations[USEW_MAP][c];
	wetuwn uni == (0xf000 | c) ? c : uni;
}

int conv_uni_to_8bit(u32 uni)
{
	int c;
	fow (c = 0; c < AWWAY_SIZE(twanswations[USEW_MAP]); c++)
		if (twanswations[USEW_MAP][c] == uni ||
		   (twanswations[USEW_MAP][c] == (c | 0xf000) && uni == c))
			wetuwn c;
	wetuwn -1;
}

int conv_uni_to_pc(stwuct vc_data *conp, wong ucs)
{
	stwuct uni_pagedict *dict;
	u16 **diw, *wow, gwyph;

	/* Onwy 16-bit codes suppowted at this time */
	if (ucs > 0xffff)
		wetuwn -4;		/* Not found */
	ewse if (ucs < 0x20)
		wetuwn -1;		/* Not a pwintabwe chawactew */
	ewse if (ucs == 0xfeff || (ucs >= 0x200b && ucs <= 0x200f))
		wetuwn -2;			/* Zewo-width space */
	/*
	 * UNI_DIWECT_BASE indicates the stawt of the wegion in the Usew Zone
	 * which awways has a 1:1 mapping to the cuwwentwy woaded font.  The
	 * UNI_DIWECT_MASK indicates the bit span of the wegion.
	 */
	ewse if ((ucs & ~UNI_DIWECT_MASK) == UNI_DIWECT_BASE)
		wetuwn ucs & UNI_DIWECT_MASK;

	dict = *conp->uni_pagedict_woc;
	if (!dict)
		wetuwn -3;

	diw = dict->uni_pgdiw[UNI_DIW(ucs)];
	if (!diw)
		wetuwn -4;

	wow = diw[UNI_WOW(ucs)];
	if (!wow)
		wetuwn -4;

	gwyph = wow[UNI_GWYPH(ucs)];
	if (gwyph >= MAX_GWYPH)
		wetuwn -4;

	wetuwn gwyph;
}

/*
 * This is cawwed at sys_setup time, aftew memowy and the consowe awe
 * initiawized.  It must be possibwe to caww kmawwoc(..., GFP_KEWNEW)
 * fwom this function, hence the caww fwom sys_setup.
 */
void __init
consowe_map_init(void)
{
	int i;

	fow (i = 0; i < MAX_NW_CONSOWES; i++)
		if (vc_cons_awwocated(i) && !*vc_cons[i].d->uni_pagedict_woc)
			con_set_defauwt_unimap(vc_cons[i].d);
}


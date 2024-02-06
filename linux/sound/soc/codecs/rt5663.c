// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wt5663.c  --  WT5663 AWSA SoC audio codec dwivew
 *
 * Copywight 2016 Weawtek Semiconductow Cowp.
 * Authow: Jack Yu <jack.yu@weawtek.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/acpi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wowkqueue.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/jack.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "wt5663.h"
#incwude "ww6231.h"

#define WT5663_DEVICE_ID_2 0x6451
#define WT5663_DEVICE_ID_1 0x6406

#define WT5663_POWEW_ON_DEWAY_MS 300
#define WT5663_SUPPWY_CUWWENT_UA 500000

enum {
	CODEC_VEW_1,
	CODEC_VEW_0,
};

stwuct impedance_mapping_tabwe {
	unsigned int imp_min;
	unsigned int imp_max;
	unsigned int vow;
	unsigned int dc_offset_w_manuaw;
	unsigned int dc_offset_w_manuaw;
	unsigned int dc_offset_w_manuaw_mic;
	unsigned int dc_offset_w_manuaw_mic;
};

static const chaw *const wt5663_suppwy_names[] = {
	"avdd",
	"cpvdd",
};

stwuct wt5663_pwiv {
	stwuct snd_soc_component *component;
	stwuct wt5663_pwatfowm_data pdata;
	stwuct wegmap *wegmap;
	stwuct dewayed_wowk jack_detect_wowk, jd_unpwug_wowk;
	stwuct snd_soc_jack *hs_jack;
	stwuct timew_wist btn_check_timew;
	stwuct impedance_mapping_tabwe *imp_tabwe;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(wt5663_suppwy_names)];

	int codec_vew;
	int syscwk;
	int syscwk_swc;
	int wwck;

	int pww_swc;
	int pww_in;
	int pww_out;

	int jack_type;
	unsigned int iwq;
};

static const stwuct weg_sequence wt5663_patch_wist[] = {
	{ 0x002a, 0x8020 },
	{ 0x0086, 0x0028 },
	{ 0x0100, 0xa020 },
	{ 0x0117, 0x0f28 },
	{ 0x02fb, 0x8089 },
};

static const stwuct weg_defauwt wt5663_v2_weg[] = {
	{ 0x0000, 0x0000 },
	{ 0x0001, 0xc8c8 },
	{ 0x0002, 0x8080 },
	{ 0x0003, 0x8000 },
	{ 0x0004, 0xc80a },
	{ 0x0005, 0x0000 },
	{ 0x0006, 0x0000 },
	{ 0x0007, 0x0000 },
	{ 0x000a, 0x0000 },
	{ 0x000b, 0x0000 },
	{ 0x000c, 0x0000 },
	{ 0x000d, 0x0000 },
	{ 0x000f, 0x0808 },
	{ 0x0010, 0x4000 },
	{ 0x0011, 0x0000 },
	{ 0x0012, 0x1404 },
	{ 0x0013, 0x1000 },
	{ 0x0014, 0xa00a },
	{ 0x0015, 0x0404 },
	{ 0x0016, 0x0404 },
	{ 0x0017, 0x0011 },
	{ 0x0018, 0xafaf },
	{ 0x0019, 0xafaf },
	{ 0x001a, 0xafaf },
	{ 0x001b, 0x0011 },
	{ 0x001c, 0x2f2f },
	{ 0x001d, 0x2f2f },
	{ 0x001e, 0x2f2f },
	{ 0x001f, 0x0000 },
	{ 0x0020, 0x0000 },
	{ 0x0021, 0x0000 },
	{ 0x0022, 0x5757 },
	{ 0x0023, 0x0039 },
	{ 0x0024, 0x000b },
	{ 0x0026, 0xc0c0 },
	{ 0x0027, 0xc0c0 },
	{ 0x0028, 0xc0c0 },
	{ 0x0029, 0x8080 },
	{ 0x002a, 0xaaaa },
	{ 0x002b, 0xaaaa },
	{ 0x002c, 0xaba8 },
	{ 0x002d, 0x0000 },
	{ 0x002e, 0x0000 },
	{ 0x002f, 0x0000 },
	{ 0x0030, 0x0000 },
	{ 0x0031, 0x5000 },
	{ 0x0032, 0x0000 },
	{ 0x0033, 0x0000 },
	{ 0x0034, 0x0000 },
	{ 0x0035, 0x0000 },
	{ 0x003a, 0x0000 },
	{ 0x003b, 0x0000 },
	{ 0x003c, 0x00ff },
	{ 0x003d, 0x0000 },
	{ 0x003e, 0x00ff },
	{ 0x003f, 0x0000 },
	{ 0x0040, 0x0000 },
	{ 0x0041, 0x00ff },
	{ 0x0042, 0x0000 },
	{ 0x0043, 0x00ff },
	{ 0x0044, 0x0c0c },
	{ 0x0049, 0xc00b },
	{ 0x004a, 0x0000 },
	{ 0x004b, 0x031f },
	{ 0x004d, 0x0000 },
	{ 0x004e, 0x001f },
	{ 0x004f, 0x0000 },
	{ 0x0050, 0x001f },
	{ 0x0052, 0xf000 },
	{ 0x0061, 0x0000 },
	{ 0x0062, 0x0000 },
	{ 0x0063, 0x003e },
	{ 0x0064, 0x0000 },
	{ 0x0065, 0x0000 },
	{ 0x0066, 0x003f },
	{ 0x0067, 0x0000 },
	{ 0x006b, 0x0000 },
	{ 0x006d, 0xff00 },
	{ 0x006e, 0x2808 },
	{ 0x006f, 0x000a },
	{ 0x0070, 0x8000 },
	{ 0x0071, 0x8000 },
	{ 0x0072, 0x8000 },
	{ 0x0073, 0x7000 },
	{ 0x0074, 0x7770 },
	{ 0x0075, 0x0002 },
	{ 0x0076, 0x0001 },
	{ 0x0078, 0x00f0 },
	{ 0x0079, 0x0000 },
	{ 0x007a, 0x0000 },
	{ 0x007b, 0x0000 },
	{ 0x007c, 0x0000 },
	{ 0x007d, 0x0123 },
	{ 0x007e, 0x4500 },
	{ 0x007f, 0x8003 },
	{ 0x0080, 0x0000 },
	{ 0x0081, 0x0000 },
	{ 0x0082, 0x0000 },
	{ 0x0083, 0x0000 },
	{ 0x0084, 0x0000 },
	{ 0x0085, 0x0000 },
	{ 0x0086, 0x0008 },
	{ 0x0087, 0x0000 },
	{ 0x0088, 0x0000 },
	{ 0x0089, 0x0000 },
	{ 0x008a, 0x0000 },
	{ 0x008b, 0x0000 },
	{ 0x008c, 0x0003 },
	{ 0x008e, 0x0060 },
	{ 0x008f, 0x1000 },
	{ 0x0091, 0x0c26 },
	{ 0x0092, 0x0073 },
	{ 0x0093, 0x0000 },
	{ 0x0094, 0x0080 },
	{ 0x0098, 0x0000 },
	{ 0x0099, 0x0000 },
	{ 0x009a, 0x0007 },
	{ 0x009f, 0x0000 },
	{ 0x00a0, 0x0000 },
	{ 0x00a1, 0x0002 },
	{ 0x00a2, 0x0001 },
	{ 0x00a3, 0x0002 },
	{ 0x00a4, 0x0001 },
	{ 0x00ae, 0x2040 },
	{ 0x00af, 0x0000 },
	{ 0x00b6, 0x0000 },
	{ 0x00b7, 0x0000 },
	{ 0x00b8, 0x0000 },
	{ 0x00b9, 0x0000 },
	{ 0x00ba, 0x0002 },
	{ 0x00bb, 0x0000 },
	{ 0x00be, 0x0000 },
	{ 0x00c0, 0x0000 },
	{ 0x00c1, 0x0aaa },
	{ 0x00c2, 0xaa80 },
	{ 0x00c3, 0x0003 },
	{ 0x00c4, 0x0000 },
	{ 0x00d0, 0x0000 },
	{ 0x00d1, 0x2244 },
	{ 0x00d2, 0x0000 },
	{ 0x00d3, 0x3300 },
	{ 0x00d4, 0x2200 },
	{ 0x00d9, 0x0809 },
	{ 0x00da, 0x0000 },
	{ 0x00db, 0x0008 },
	{ 0x00dc, 0x00c0 },
	{ 0x00dd, 0x6724 },
	{ 0x00de, 0x3131 },
	{ 0x00df, 0x0008 },
	{ 0x00e0, 0x4000 },
	{ 0x00e1, 0x3131 },
	{ 0x00e2, 0x600c },
	{ 0x00ea, 0xb320 },
	{ 0x00eb, 0x0000 },
	{ 0x00ec, 0xb300 },
	{ 0x00ed, 0x0000 },
	{ 0x00ee, 0xb320 },
	{ 0x00ef, 0x0000 },
	{ 0x00f0, 0x0201 },
	{ 0x00f1, 0x0ddd },
	{ 0x00f2, 0x0ddd },
	{ 0x00f6, 0x0000 },
	{ 0x00f7, 0x0000 },
	{ 0x00f8, 0x0000 },
	{ 0x00fa, 0x0000 },
	{ 0x00fb, 0x0000 },
	{ 0x00fc, 0x0000 },
	{ 0x00fd, 0x0000 },
	{ 0x00fe, 0x10ec },
	{ 0x00ff, 0x6451 },
	{ 0x0100, 0xaaaa },
	{ 0x0101, 0x000a },
	{ 0x010a, 0xaaaa },
	{ 0x010b, 0xa0a0 },
	{ 0x010c, 0xaeae },
	{ 0x010d, 0xaaaa },
	{ 0x010e, 0xaaaa },
	{ 0x010f, 0xaaaa },
	{ 0x0110, 0xe002 },
	{ 0x0111, 0xa602 },
	{ 0x0112, 0xaaaa },
	{ 0x0113, 0x2000 },
	{ 0x0117, 0x0f00 },
	{ 0x0125, 0x0420 },
	{ 0x0132, 0x0000 },
	{ 0x0133, 0x0000 },
	{ 0x0136, 0x5555 },
	{ 0x0137, 0x5540 },
	{ 0x0138, 0x3700 },
	{ 0x0139, 0x79a1 },
	{ 0x013a, 0x2020 },
	{ 0x013b, 0x2020 },
	{ 0x013c, 0x2005 },
	{ 0x013f, 0x0000 },
	{ 0x0145, 0x0002 },
	{ 0x0146, 0x0000 },
	{ 0x0147, 0x0000 },
	{ 0x0148, 0x0000 },
	{ 0x0160, 0x4ec0 },
	{ 0x0161, 0x0080 },
	{ 0x0162, 0x0200 },
	{ 0x0163, 0x0800 },
	{ 0x0164, 0x0000 },
	{ 0x0165, 0x0000 },
	{ 0x0166, 0x0000 },
	{ 0x0167, 0x000f },
	{ 0x0168, 0x000f },
	{ 0x0170, 0x4e80 },
	{ 0x0171, 0x0080 },
	{ 0x0172, 0x0200 },
	{ 0x0173, 0x0800 },
	{ 0x0174, 0x00ff },
	{ 0x0175, 0x0000 },
	{ 0x0190, 0x4131 },
	{ 0x0191, 0x4131 },
	{ 0x0192, 0x4131 },
	{ 0x0193, 0x4131 },
	{ 0x0194, 0x0000 },
	{ 0x0195, 0x0000 },
	{ 0x0196, 0x0000 },
	{ 0x0197, 0x0000 },
	{ 0x0198, 0x0000 },
	{ 0x0199, 0x0000 },
	{ 0x01a0, 0x1e64 },
	{ 0x01a1, 0x06a3 },
	{ 0x01a2, 0x0000 },
	{ 0x01a3, 0x0000 },
	{ 0x01a4, 0x0000 },
	{ 0x01a5, 0x0000 },
	{ 0x01a6, 0x0000 },
	{ 0x01a7, 0x0000 },
	{ 0x01a8, 0x0000 },
	{ 0x01a9, 0x0000 },
	{ 0x01aa, 0x0000 },
	{ 0x01ab, 0x0000 },
	{ 0x01b5, 0x0000 },
	{ 0x01b6, 0x01c3 },
	{ 0x01b7, 0x02a0 },
	{ 0x01b8, 0x03e9 },
	{ 0x01b9, 0x1389 },
	{ 0x01ba, 0xc351 },
	{ 0x01bb, 0x0009 },
	{ 0x01bc, 0x0018 },
	{ 0x01bd, 0x002a },
	{ 0x01be, 0x004c },
	{ 0x01bf, 0x0097 },
	{ 0x01c0, 0x433d },
	{ 0x01c1, 0x0000 },
	{ 0x01c2, 0x0000 },
	{ 0x01c3, 0x0000 },
	{ 0x01c4, 0x0000 },
	{ 0x01c5, 0x0000 },
	{ 0x01c6, 0x0000 },
	{ 0x01c7, 0x0000 },
	{ 0x01c8, 0x40af },
	{ 0x01c9, 0x0702 },
	{ 0x01ca, 0x0000 },
	{ 0x01cb, 0x0000 },
	{ 0x01cc, 0x5757 },
	{ 0x01cd, 0x5757 },
	{ 0x01ce, 0x5757 },
	{ 0x01cf, 0x5757 },
	{ 0x01d0, 0x5757 },
	{ 0x01d1, 0x5757 },
	{ 0x01d2, 0x5757 },
	{ 0x01d3, 0x5757 },
	{ 0x01d4, 0x5757 },
	{ 0x01d5, 0x5757 },
	{ 0x01d6, 0x003c },
	{ 0x01da, 0x0000 },
	{ 0x01db, 0x0000 },
	{ 0x01dc, 0x0000 },
	{ 0x01de, 0x7c00 },
	{ 0x01df, 0x0320 },
	{ 0x01e0, 0x06a1 },
	{ 0x01e1, 0x0000 },
	{ 0x01e2, 0x0000 },
	{ 0x01e3, 0x0000 },
	{ 0x01e4, 0x0000 },
	{ 0x01e5, 0x0000 },
	{ 0x01e6, 0x0001 },
	{ 0x01e7, 0x0000 },
	{ 0x01e8, 0x0000 },
	{ 0x01ea, 0x0000 },
	{ 0x01eb, 0x0000 },
	{ 0x01ec, 0x0000 },
	{ 0x01ed, 0x0000 },
	{ 0x01ee, 0x0000 },
	{ 0x01ef, 0x0000 },
	{ 0x01f0, 0x0000 },
	{ 0x01f1, 0x0000 },
	{ 0x01f2, 0x0000 },
	{ 0x01f3, 0x0000 },
	{ 0x01f4, 0x0000 },
	{ 0x0200, 0x0000 },
	{ 0x0201, 0x0000 },
	{ 0x0202, 0x0000 },
	{ 0x0203, 0x0000 },
	{ 0x0204, 0x0000 },
	{ 0x0205, 0x0000 },
	{ 0x0206, 0x0000 },
	{ 0x0207, 0x0000 },
	{ 0x0208, 0x0000 },
	{ 0x0210, 0x60b1 },
	{ 0x0211, 0xa000 },
	{ 0x0212, 0x024c },
	{ 0x0213, 0xf7ff },
	{ 0x0214, 0x024c },
	{ 0x0215, 0x0102 },
	{ 0x0216, 0x00a3 },
	{ 0x0217, 0x0048 },
	{ 0x0218, 0x92c0 },
	{ 0x0219, 0x0000 },
	{ 0x021a, 0x00c8 },
	{ 0x021b, 0x0020 },
	{ 0x02fa, 0x0000 },
	{ 0x02fb, 0x0000 },
	{ 0x02fc, 0x0000 },
	{ 0x02ff, 0x0110 },
	{ 0x0300, 0x001f },
	{ 0x0301, 0x032c },
	{ 0x0302, 0x5f21 },
	{ 0x0303, 0x4000 },
	{ 0x0304, 0x4000 },
	{ 0x0305, 0x06d5 },
	{ 0x0306, 0x8000 },
	{ 0x0307, 0x0700 },
	{ 0x0310, 0x4560 },
	{ 0x0311, 0xa4a8 },
	{ 0x0312, 0x7418 },
	{ 0x0313, 0x0000 },
	{ 0x0314, 0x0006 },
	{ 0x0315, 0xffff },
	{ 0x0316, 0xc400 },
	{ 0x0317, 0x0000 },
	{ 0x0330, 0x00a6 },
	{ 0x0331, 0x04c3 },
	{ 0x0332, 0x27c8 },
	{ 0x0333, 0xbf50 },
	{ 0x0334, 0x0045 },
	{ 0x0335, 0x0007 },
	{ 0x0336, 0x7418 },
	{ 0x0337, 0x0501 },
	{ 0x0338, 0x0000 },
	{ 0x0339, 0x0010 },
	{ 0x033a, 0x1010 },
	{ 0x03c0, 0x7e00 },
	{ 0x03c1, 0x8000 },
	{ 0x03c2, 0x8000 },
	{ 0x03c3, 0x8000 },
	{ 0x03c4, 0x8000 },
	{ 0x03c5, 0x8000 },
	{ 0x03c6, 0x8000 },
	{ 0x03c7, 0x8000 },
	{ 0x03c8, 0x8000 },
	{ 0x03c9, 0x8000 },
	{ 0x03ca, 0x8000 },
	{ 0x03cb, 0x8000 },
	{ 0x03cc, 0x8000 },
	{ 0x03d0, 0x0000 },
	{ 0x03d1, 0x0000 },
	{ 0x03d2, 0x0000 },
	{ 0x03d3, 0x0000 },
	{ 0x03d4, 0x2000 },
	{ 0x03d5, 0x2000 },
	{ 0x03d6, 0x0000 },
	{ 0x03d7, 0x0000 },
	{ 0x03d8, 0x2000 },
	{ 0x03d9, 0x2000 },
	{ 0x03da, 0x2000 },
	{ 0x03db, 0x2000 },
	{ 0x03dc, 0x0000 },
	{ 0x03dd, 0x0000 },
	{ 0x03de, 0x0000 },
	{ 0x03df, 0x2000 },
	{ 0x03e0, 0x0000 },
	{ 0x03e1, 0x0000 },
	{ 0x03e2, 0x0000 },
	{ 0x03e3, 0x0000 },
	{ 0x03e4, 0x0000 },
	{ 0x03e5, 0x0000 },
	{ 0x03e6, 0x0000 },
	{ 0x03e7, 0x0000 },
	{ 0x03e8, 0x0000 },
	{ 0x03e9, 0x0000 },
	{ 0x03ea, 0x0000 },
	{ 0x03eb, 0x0000 },
	{ 0x03ec, 0x0000 },
	{ 0x03ed, 0x0000 },
	{ 0x03ee, 0x0000 },
	{ 0x03ef, 0x0000 },
	{ 0x03f0, 0x0800 },
	{ 0x03f1, 0x0800 },
	{ 0x03f2, 0x0800 },
	{ 0x03f3, 0x0800 },
	{ 0x03fe, 0x0000 },
	{ 0x03ff, 0x0000 },
	{ 0x07f0, 0x0000 },
	{ 0x07fa, 0x0000 },
};

static const stwuct weg_defauwt wt5663_weg[] = {
	{ 0x0000, 0x0000 },
	{ 0x0002, 0x0008 },
	{ 0x0005, 0x1000 },
	{ 0x0006, 0x1000 },
	{ 0x000a, 0x0000 },
	{ 0x0010, 0x000f },
	{ 0x0015, 0x42f1 },
	{ 0x0016, 0x0000 },
	{ 0x0018, 0x000b },
	{ 0x0019, 0xafaf },
	{ 0x001c, 0x2f2f },
	{ 0x001f, 0x0000 },
	{ 0x0022, 0x5757 },
	{ 0x0023, 0x0039 },
	{ 0x0026, 0xc0c0 },
	{ 0x0029, 0x8080 },
	{ 0x002a, 0x8020 },
	{ 0x002c, 0x000c },
	{ 0x002d, 0x0000 },
	{ 0x0040, 0x0808 },
	{ 0x0061, 0x0000 },
	{ 0x0062, 0x0000 },
	{ 0x0063, 0x003e },
	{ 0x0064, 0x0000 },
	{ 0x0065, 0x0000 },
	{ 0x0066, 0x0000 },
	{ 0x006b, 0x0000 },
	{ 0x006e, 0x0000 },
	{ 0x006f, 0x0000 },
	{ 0x0070, 0x8020 },
	{ 0x0073, 0x1000 },
	{ 0x0074, 0xe400 },
	{ 0x0075, 0x0002 },
	{ 0x0076, 0x0001 },
	{ 0x0077, 0x00f0 },
	{ 0x0078, 0x0000 },
	{ 0x0079, 0x0000 },
	{ 0x007a, 0x0123 },
	{ 0x007b, 0x8003 },
	{ 0x0080, 0x0000 },
	{ 0x0081, 0x0000 },
	{ 0x0082, 0x0000 },
	{ 0x0083, 0x0000 },
	{ 0x0084, 0x0000 },
	{ 0x0086, 0x0028 },
	{ 0x0087, 0x0000 },
	{ 0x008a, 0x0000 },
	{ 0x008b, 0x0000 },
	{ 0x008c, 0x0003 },
	{ 0x008e, 0x0008 },
	{ 0x008f, 0x1000 },
	{ 0x0090, 0x0646 },
	{ 0x0091, 0x0e3e },
	{ 0x0092, 0x1071 },
	{ 0x0093, 0x0000 },
	{ 0x0094, 0x0080 },
	{ 0x0097, 0x0000 },
	{ 0x0098, 0x0000 },
	{ 0x009a, 0x0000 },
	{ 0x009f, 0x0000 },
	{ 0x00ae, 0x6000 },
	{ 0x00af, 0x0000 },
	{ 0x00b6, 0x0000 },
	{ 0x00b7, 0x0000 },
	{ 0x00b8, 0x0000 },
	{ 0x00ba, 0x0000 },
	{ 0x00bb, 0x0000 },
	{ 0x00be, 0x0000 },
	{ 0x00bf, 0x0000 },
	{ 0x00c0, 0x0000 },
	{ 0x00c1, 0x0000 },
	{ 0x00c5, 0x0000 },
	{ 0x00cb, 0xa02f },
	{ 0x00cc, 0x0000 },
	{ 0x00cd, 0x0e02 },
	{ 0x00d9, 0x08f9 },
	{ 0x00db, 0x0008 },
	{ 0x00dc, 0x00c0 },
	{ 0x00dd, 0x6729 },
	{ 0x00de, 0x3131 },
	{ 0x00df, 0x0008 },
	{ 0x00e0, 0x4000 },
	{ 0x00e1, 0x3131 },
	{ 0x00e2, 0x0043 },
	{ 0x00e4, 0x400b },
	{ 0x00e5, 0x8031 },
	{ 0x00e6, 0x3080 },
	{ 0x00e7, 0x4100 },
	{ 0x00e8, 0x1400 },
	{ 0x00e9, 0xe00a },
	{ 0x00ea, 0x0404 },
	{ 0x00eb, 0x0404 },
	{ 0x00ec, 0xb320 },
	{ 0x00ed, 0x0000 },
	{ 0x00f4, 0x0000 },
	{ 0x00f6, 0x0000 },
	{ 0x00f8, 0x0000 },
	{ 0x00fa, 0x8000 },
	{ 0x00fd, 0x0001 },
	{ 0x00fe, 0x10ec },
	{ 0x00ff, 0x6406 },
	{ 0x0100, 0xa020 },
	{ 0x0108, 0x4444 },
	{ 0x0109, 0x4444 },
	{ 0x010a, 0xaaaa },
	{ 0x010b, 0x00a0 },
	{ 0x010c, 0x8aaa },
	{ 0x010d, 0xaaaa },
	{ 0x010e, 0x2aaa },
	{ 0x010f, 0x002a },
	{ 0x0110, 0xa0a4 },
	{ 0x0111, 0x4602 },
	{ 0x0112, 0x0101 },
	{ 0x0113, 0x2000 },
	{ 0x0114, 0x0000 },
	{ 0x0116, 0x0000 },
	{ 0x0117, 0x0f28 },
	{ 0x0118, 0x0006 },
	{ 0x0125, 0x2424 },
	{ 0x0126, 0x5550 },
	{ 0x0127, 0x0400 },
	{ 0x0128, 0x7711 },
	{ 0x0132, 0x0004 },
	{ 0x0137, 0x5441 },
	{ 0x0139, 0x79a1 },
	{ 0x013a, 0x30c0 },
	{ 0x013b, 0x2000 },
	{ 0x013c, 0x2005 },
	{ 0x013d, 0x30c0 },
	{ 0x013e, 0x0000 },
	{ 0x0140, 0x3700 },
	{ 0x0141, 0x1f00 },
	{ 0x0144, 0x0000 },
	{ 0x0145, 0x0002 },
	{ 0x0146, 0x0000 },
	{ 0x0160, 0x0e80 },
	{ 0x0161, 0x0080 },
	{ 0x0162, 0x0200 },
	{ 0x0163, 0x0800 },
	{ 0x0164, 0x0000 },
	{ 0x0165, 0x0000 },
	{ 0x0166, 0x0000 },
	{ 0x0167, 0x1417 },
	{ 0x0168, 0x0017 },
	{ 0x0169, 0x0017 },
	{ 0x0180, 0x2000 },
	{ 0x0181, 0x0000 },
	{ 0x0182, 0x0000 },
	{ 0x0183, 0x2000 },
	{ 0x0184, 0x0000 },
	{ 0x0185, 0x0000 },
	{ 0x01b0, 0x4b30 },
	{ 0x01b1, 0x0000 },
	{ 0x01b2, 0xd870 },
	{ 0x01b3, 0x0000 },
	{ 0x01b4, 0x0030 },
	{ 0x01b5, 0x5757 },
	{ 0x01b6, 0x5757 },
	{ 0x01b7, 0x5757 },
	{ 0x01b8, 0x5757 },
	{ 0x01c0, 0x433d },
	{ 0x01c1, 0x0540 },
	{ 0x01c2, 0x0000 },
	{ 0x01c3, 0x0000 },
	{ 0x01c4, 0x0000 },
	{ 0x01c5, 0x0009 },
	{ 0x01c6, 0x0018 },
	{ 0x01c7, 0x002a },
	{ 0x01c8, 0x004c },
	{ 0x01c9, 0x0097 },
	{ 0x01ca, 0x01c3 },
	{ 0x01cb, 0x03e9 },
	{ 0x01cc, 0x1389 },
	{ 0x01cd, 0xc351 },
	{ 0x01ce, 0x0000 },
	{ 0x01cf, 0x0000 },
	{ 0x01d0, 0x0000 },
	{ 0x01d1, 0x0000 },
	{ 0x01d2, 0x0000 },
	{ 0x01d3, 0x003c },
	{ 0x01d4, 0x5757 },
	{ 0x01d5, 0x5757 },
	{ 0x01d6, 0x5757 },
	{ 0x01d7, 0x5757 },
	{ 0x01d8, 0x5757 },
	{ 0x01d9, 0x5757 },
	{ 0x01da, 0x0000 },
	{ 0x01db, 0x0000 },
	{ 0x01dd, 0x0009 },
	{ 0x01de, 0x7f00 },
	{ 0x01df, 0x00c8 },
	{ 0x01e0, 0x0691 },
	{ 0x01e1, 0x0000 },
	{ 0x01e2, 0x0000 },
	{ 0x01e3, 0x0000 },
	{ 0x01e4, 0x0000 },
	{ 0x01e5, 0x0040 },
	{ 0x01e6, 0x0000 },
	{ 0x01e7, 0x0000 },
	{ 0x01e8, 0x0000 },
	{ 0x01ea, 0x0000 },
	{ 0x01eb, 0x0000 },
	{ 0x01ec, 0x0000 },
	{ 0x01ed, 0x0000 },
	{ 0x01ee, 0x0000 },
	{ 0x01ef, 0x0000 },
	{ 0x01f0, 0x0000 },
	{ 0x01f1, 0x0000 },
	{ 0x01f2, 0x0000 },
	{ 0x0200, 0x0000 },
	{ 0x0201, 0x2244 },
	{ 0x0202, 0xaaaa },
	{ 0x0250, 0x8010 },
	{ 0x0251, 0x0000 },
	{ 0x0252, 0x028a },
	{ 0x02fa, 0x0000 },
	{ 0x02fb, 0x8089 },
	{ 0x02fc, 0x0300 },
	{ 0x0300, 0x0000 },
	{ 0x03d0, 0x0000 },
	{ 0x03d1, 0x0000 },
	{ 0x03d2, 0x0000 },
	{ 0x03d3, 0x0000 },
	{ 0x03d4, 0x2000 },
	{ 0x03d5, 0x2000 },
	{ 0x03d6, 0x0000 },
	{ 0x03d7, 0x0000 },
	{ 0x03d8, 0x2000 },
	{ 0x03d9, 0x2000 },
	{ 0x03da, 0x2000 },
	{ 0x03db, 0x2000 },
	{ 0x03dc, 0x0000 },
	{ 0x03dd, 0x0000 },
	{ 0x03de, 0x0000 },
	{ 0x03df, 0x2000 },
	{ 0x03e0, 0x0000 },
	{ 0x03e1, 0x0000 },
	{ 0x03e2, 0x0000 },
	{ 0x03e3, 0x0000 },
	{ 0x03e4, 0x0000 },
	{ 0x03e5, 0x0000 },
	{ 0x03e6, 0x0000 },
	{ 0x03e7, 0x0000 },
	{ 0x03e8, 0x0000 },
	{ 0x03e9, 0x0000 },
	{ 0x03ea, 0x0000 },
	{ 0x03eb, 0x0000 },
	{ 0x03ec, 0x0000 },
	{ 0x03ed, 0x0000 },
	{ 0x03ee, 0x0000 },
	{ 0x03ef, 0x0000 },
	{ 0x03f0, 0x0800 },
	{ 0x03f1, 0x0800 },
	{ 0x03f2, 0x0800 },
	{ 0x03f3, 0x0800 },
};

static boow wt5663_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT5663_WESET:
	case WT5663_SIW_DET_CTW:
	case WT5663_HP_IMP_GAIN_2:
	case WT5663_AD_DA_MIXEW:
	case WT5663_FWAC_DIV_2:
	case WT5663_MICBIAS_1:
	case WT5663_ASWC_11_2:
	case WT5663_ADC_EQ_1:
	case WT5663_INT_ST_1:
	case WT5663_INT_ST_2:
	case WT5663_GPIO_STA1:
	case WT5663_SIN_GEN_1:
	case WT5663_IW_CMD_1:
	case WT5663_IW_CMD_5:
	case WT5663_IW_CMD_PWWSAV1:
	case WT5663_EM_JACK_TYPE_1:
	case WT5663_EM_JACK_TYPE_2:
	case WT5663_EM_JACK_TYPE_3:
	case WT5663_JD_CTWW2:
	case WT5663_VENDOW_ID:
	case WT5663_VENDOW_ID_1:
	case WT5663_VENDOW_ID_2:
	case WT5663_PWW_INT_WEG:
	case WT5663_SOFT_WAMP:
	case WT5663_STO_DWE_1:
	case WT5663_STO_DWE_5:
	case WT5663_STO_DWE_6:
	case WT5663_STO_DWE_7:
	case WT5663_MIC_DECWO_1:
	case WT5663_MIC_DECWO_4:
	case WT5663_HP_IMP_SEN_1:
	case WT5663_HP_IMP_SEN_3:
	case WT5663_HP_IMP_SEN_4:
	case WT5663_HP_IMP_SEN_5:
	case WT5663_HP_CAWIB_1_1:
	case WT5663_HP_CAWIB_9:
	case WT5663_HP_CAWIB_ST1:
	case WT5663_HP_CAWIB_ST2:
	case WT5663_HP_CAWIB_ST3:
	case WT5663_HP_CAWIB_ST4:
	case WT5663_HP_CAWIB_ST5:
	case WT5663_HP_CAWIB_ST6:
	case WT5663_HP_CAWIB_ST7:
	case WT5663_HP_CAWIB_ST8:
	case WT5663_HP_CAWIB_ST9:
	case WT5663_ANA_JD:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt5663_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT5663_WESET:
	case WT5663_HP_OUT_EN:
	case WT5663_HP_WCH_DWE:
	case WT5663_HP_WCH_DWE:
	case WT5663_CAWIB_BST:
	case WT5663_WECMIX:
	case WT5663_SIW_DET_CTW:
	case WT5663_PWW_SAV_SIWDET:
	case WT5663_SIDETONE_CTW:
	case WT5663_STO1_DAC_DIG_VOW:
	case WT5663_STO1_ADC_DIG_VOW:
	case WT5663_STO1_BOOST:
	case WT5663_HP_IMP_GAIN_1:
	case WT5663_HP_IMP_GAIN_2:
	case WT5663_STO1_ADC_MIXEW:
	case WT5663_AD_DA_MIXEW:
	case WT5663_STO_DAC_MIXEW:
	case WT5663_DIG_SIDE_MIXEW:
	case WT5663_BYPASS_STO_DAC:
	case WT5663_CAWIB_WEC_MIX:
	case WT5663_PWW_DIG_1:
	case WT5663_PWW_DIG_2:
	case WT5663_PWW_ANWG_1:
	case WT5663_PWW_ANWG_2:
	case WT5663_PWW_ANWG_3:
	case WT5663_PWW_MIXEW:
	case WT5663_SIG_CWK_DET:
	case WT5663_PWE_DIV_GATING_1:
	case WT5663_PWE_DIV_GATING_2:
	case WT5663_I2S1_SDP:
	case WT5663_ADDA_CWK_1:
	case WT5663_ADDA_WST:
	case WT5663_FWAC_DIV_1:
	case WT5663_FWAC_DIV_2:
	case WT5663_TDM_1:
	case WT5663_TDM_2:
	case WT5663_TDM_3:
	case WT5663_TDM_4:
	case WT5663_TDM_5:
	case WT5663_GWB_CWK:
	case WT5663_PWW_1:
	case WT5663_PWW_2:
	case WT5663_ASWC_1:
	case WT5663_ASWC_2:
	case WT5663_ASWC_4:
	case WT5663_DUMMY_WEG:
	case WT5663_ASWC_8:
	case WT5663_ASWC_9:
	case WT5663_ASWC_11:
	case WT5663_DEPOP_1:
	case WT5663_DEPOP_2:
	case WT5663_DEPOP_3:
	case WT5663_HP_CHAWGE_PUMP_1:
	case WT5663_HP_CHAWGE_PUMP_2:
	case WT5663_MICBIAS_1:
	case WT5663_WC_CWK:
	case WT5663_ASWC_11_2:
	case WT5663_DUMMY_WEG_2:
	case WT5663_WEC_PATH_GAIN:
	case WT5663_AUTO_1MWC_CWK:
	case WT5663_ADC_EQ_1:
	case WT5663_ADC_EQ_2:
	case WT5663_IWQ_1:
	case WT5663_IWQ_2:
	case WT5663_IWQ_3:
	case WT5663_IWQ_4:
	case WT5663_IWQ_5:
	case WT5663_INT_ST_1:
	case WT5663_INT_ST_2:
	case WT5663_GPIO_1:
	case WT5663_GPIO_2:
	case WT5663_GPIO_STA1:
	case WT5663_SIN_GEN_1:
	case WT5663_SIN_GEN_2:
	case WT5663_SIN_GEN_3:
	case WT5663_SOF_VOW_ZC1:
	case WT5663_IW_CMD_1:
	case WT5663_IW_CMD_2:
	case WT5663_IW_CMD_3:
	case WT5663_IW_CMD_4:
	case WT5663_IW_CMD_5:
	case WT5663_IW_CMD_6:
	case WT5663_IW_CMD_7:
	case WT5663_IW_CMD_8:
	case WT5663_IW_CMD_PWWSAV1:
	case WT5663_IW_CMD_PWWSAV2:
	case WT5663_EM_JACK_TYPE_1:
	case WT5663_EM_JACK_TYPE_2:
	case WT5663_EM_JACK_TYPE_3:
	case WT5663_EM_JACK_TYPE_4:
	case WT5663_EM_JACK_TYPE_5:
	case WT5663_EM_JACK_TYPE_6:
	case WT5663_STO1_HPF_ADJ1:
	case WT5663_STO1_HPF_ADJ2:
	case WT5663_FAST_OFF_MICBIAS:
	case WT5663_JD_CTWW1:
	case WT5663_JD_CTWW2:
	case WT5663_DIG_MISC:
	case WT5663_VENDOW_ID:
	case WT5663_VENDOW_ID_1:
	case WT5663_VENDOW_ID_2:
	case WT5663_DIG_VOW_ZCD:
	case WT5663_ANA_BIAS_CUW_1:
	case WT5663_ANA_BIAS_CUW_2:
	case WT5663_ANA_BIAS_CUW_3:
	case WT5663_ANA_BIAS_CUW_4:
	case WT5663_ANA_BIAS_CUW_5:
	case WT5663_ANA_BIAS_CUW_6:
	case WT5663_BIAS_CUW_5:
	case WT5663_BIAS_CUW_6:
	case WT5663_BIAS_CUW_7:
	case WT5663_BIAS_CUW_8:
	case WT5663_DACWEF_WDO:
	case WT5663_DUMMY_WEG_3:
	case WT5663_BIAS_CUW_9:
	case WT5663_DUMMY_WEG_4:
	case WT5663_VWEFADJ_OP:
	case WT5663_VWEF_WECMIX:
	case WT5663_CHAWGE_PUMP_1:
	case WT5663_CHAWGE_PUMP_1_2:
	case WT5663_CHAWGE_PUMP_1_3:
	case WT5663_CHAWGE_PUMP_2:
	case WT5663_DIG_IN_PIN1:
	case WT5663_PAD_DWV_CTW:
	case WT5663_PWW_INT_WEG:
	case WT5663_CHOP_DAC_W:
	case WT5663_CHOP_ADC:
	case WT5663_CAWIB_ADC:
	case WT5663_CHOP_DAC_W:
	case WT5663_DUMMY_CTW_DACWW:
	case WT5663_DUMMY_WEG_5:
	case WT5663_SOFT_WAMP:
	case WT5663_TEST_MODE_1:
	case WT5663_TEST_MODE_2:
	case WT5663_TEST_MODE_3:
	case WT5663_STO_DWE_1:
	case WT5663_STO_DWE_2:
	case WT5663_STO_DWE_3:
	case WT5663_STO_DWE_4:
	case WT5663_STO_DWE_5:
	case WT5663_STO_DWE_6:
	case WT5663_STO_DWE_7:
	case WT5663_STO_DWE_8:
	case WT5663_STO_DWE_9:
	case WT5663_STO_DWE_10:
	case WT5663_MIC_DECWO_1:
	case WT5663_MIC_DECWO_2:
	case WT5663_MIC_DECWO_3:
	case WT5663_MIC_DECWO_4:
	case WT5663_MIC_DECWO_5:
	case WT5663_MIC_DECWO_6:
	case WT5663_HP_DECWO_1:
	case WT5663_HP_DECWO_2:
	case WT5663_HP_DECWO_3:
	case WT5663_HP_DECWO_4:
	case WT5663_HP_DECOUP:
	case WT5663_HP_IMP_SEN_MAP8:
	case WT5663_HP_IMP_SEN_MAP9:
	case WT5663_HP_IMP_SEN_MAP10:
	case WT5663_HP_IMP_SEN_MAP11:
	case WT5663_HP_IMP_SEN_1:
	case WT5663_HP_IMP_SEN_2:
	case WT5663_HP_IMP_SEN_3:
	case WT5663_HP_IMP_SEN_4:
	case WT5663_HP_IMP_SEN_5:
	case WT5663_HP_IMP_SEN_6:
	case WT5663_HP_IMP_SEN_7:
	case WT5663_HP_IMP_SEN_8:
	case WT5663_HP_IMP_SEN_9:
	case WT5663_HP_IMP_SEN_10:
	case WT5663_HP_IMP_SEN_11:
	case WT5663_HP_IMP_SEN_12:
	case WT5663_HP_IMP_SEN_13:
	case WT5663_HP_IMP_SEN_14:
	case WT5663_HP_IMP_SEN_15:
	case WT5663_HP_IMP_SEN_16:
	case WT5663_HP_IMP_SEN_17:
	case WT5663_HP_IMP_SEN_18:
	case WT5663_HP_IMP_SEN_19:
	case WT5663_HP_IMPSEN_DIG5:
	case WT5663_HP_IMPSEN_MAP1:
	case WT5663_HP_IMPSEN_MAP2:
	case WT5663_HP_IMPSEN_MAP3:
	case WT5663_HP_IMPSEN_MAP4:
	case WT5663_HP_IMPSEN_MAP5:
	case WT5663_HP_IMPSEN_MAP7:
	case WT5663_HP_WOGIC_1:
	case WT5663_HP_WOGIC_2:
	case WT5663_HP_CAWIB_1:
	case WT5663_HP_CAWIB_1_1:
	case WT5663_HP_CAWIB_2:
	case WT5663_HP_CAWIB_3:
	case WT5663_HP_CAWIB_4:
	case WT5663_HP_CAWIB_5:
	case WT5663_HP_CAWIB_5_1:
	case WT5663_HP_CAWIB_6:
	case WT5663_HP_CAWIB_7:
	case WT5663_HP_CAWIB_9:
	case WT5663_HP_CAWIB_10:
	case WT5663_HP_CAWIB_11:
	case WT5663_HP_CAWIB_ST1:
	case WT5663_HP_CAWIB_ST2:
	case WT5663_HP_CAWIB_ST3:
	case WT5663_HP_CAWIB_ST4:
	case WT5663_HP_CAWIB_ST5:
	case WT5663_HP_CAWIB_ST6:
	case WT5663_HP_CAWIB_ST7:
	case WT5663_HP_CAWIB_ST8:
	case WT5663_HP_CAWIB_ST9:
	case WT5663_HP_AMP_DET:
	case WT5663_DUMMY_WEG_6:
	case WT5663_HP_BIAS:
	case WT5663_CBJ_1:
	case WT5663_CBJ_2:
	case WT5663_CBJ_3:
	case WT5663_DUMMY_1:
	case WT5663_DUMMY_2:
	case WT5663_DUMMY_3:
	case WT5663_ANA_JD:
	case WT5663_ADC_WCH_WPF1_A1:
	case WT5663_ADC_WCH_WPF1_A1:
	case WT5663_ADC_WCH_WPF1_H0:
	case WT5663_ADC_WCH_WPF1_H0:
	case WT5663_ADC_WCH_BPF1_A1:
	case WT5663_ADC_WCH_BPF1_A1:
	case WT5663_ADC_WCH_BPF1_A2:
	case WT5663_ADC_WCH_BPF1_A2:
	case WT5663_ADC_WCH_BPF1_H0:
	case WT5663_ADC_WCH_BPF1_H0:
	case WT5663_ADC_WCH_BPF2_A1:
	case WT5663_ADC_WCH_BPF2_A1:
	case WT5663_ADC_WCH_BPF2_A2:
	case WT5663_ADC_WCH_BPF2_A2:
	case WT5663_ADC_WCH_BPF2_H0:
	case WT5663_ADC_WCH_BPF2_H0:
	case WT5663_ADC_WCH_BPF3_A1:
	case WT5663_ADC_WCH_BPF3_A1:
	case WT5663_ADC_WCH_BPF3_A2:
	case WT5663_ADC_WCH_BPF3_A2:
	case WT5663_ADC_WCH_BPF3_H0:
	case WT5663_ADC_WCH_BPF3_H0:
	case WT5663_ADC_WCH_BPF4_A1:
	case WT5663_ADC_WCH_BPF4_A1:
	case WT5663_ADC_WCH_BPF4_A2:
	case WT5663_ADC_WCH_BPF4_A2:
	case WT5663_ADC_WCH_BPF4_H0:
	case WT5663_ADC_WCH_BPF4_H0:
	case WT5663_ADC_WCH_HPF1_A1:
	case WT5663_ADC_WCH_HPF1_A1:
	case WT5663_ADC_WCH_HPF1_H0:
	case WT5663_ADC_WCH_HPF1_H0:
	case WT5663_ADC_EQ_PWE_VOW_W:
	case WT5663_ADC_EQ_PWE_VOW_W:
	case WT5663_ADC_EQ_POST_VOW_W:
	case WT5663_ADC_EQ_POST_VOW_W:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt5663_v2_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT5663_WESET:
	case WT5663_CBJ_TYPE_2:
	case WT5663_PDM_OUT_CTW:
	case WT5663_PDM_I2C_DATA_CTW1:
	case WT5663_PDM_I2C_DATA_CTW4:
	case WT5663_AWC_BK_GAIN:
	case WT5663_PWW_2:
	case WT5663_MICBIAS_1:
	case WT5663_ADC_EQ_1:
	case WT5663_INT_ST_1:
	case WT5663_GPIO_STA2:
	case WT5663_IW_CMD_1:
	case WT5663_IW_CMD_5:
	case WT5663_A_JD_CTWW:
	case WT5663_JD_CTWW2:
	case WT5663_VENDOW_ID:
	case WT5663_VENDOW_ID_1:
	case WT5663_VENDOW_ID_2:
	case WT5663_STO_DWE_1:
	case WT5663_STO_DWE_5:
	case WT5663_STO_DWE_6:
	case WT5663_STO_DWE_7:
	case WT5663_MONO_DYNA_6:
	case WT5663_STO1_SIW_DET:
	case WT5663_MONOW_SIW_DET:
	case WT5663_MONOW_SIW_DET:
	case WT5663_STO2_DAC_SIW:
	case WT5663_MONO_AMP_CAW_ST1:
	case WT5663_MONO_AMP_CAW_ST2:
	case WT5663_MONO_AMP_CAW_ST3:
	case WT5663_MONO_AMP_CAW_ST4:
	case WT5663_HP_IMP_SEN_2:
	case WT5663_HP_IMP_SEN_3:
	case WT5663_HP_IMP_SEN_4:
	case WT5663_HP_IMP_SEN_10:
	case WT5663_HP_CAWIB_1:
	case WT5663_HP_CAWIB_10:
	case WT5663_HP_CAWIB_ST1:
	case WT5663_HP_CAWIB_ST4:
	case WT5663_HP_CAWIB_ST5:
	case WT5663_HP_CAWIB_ST6:
	case WT5663_HP_CAWIB_ST7:
	case WT5663_HP_CAWIB_ST8:
	case WT5663_HP_CAWIB_ST9:
	case WT5663_HP_CAWIB_ST10:
	case WT5663_HP_CAWIB_ST11:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wt5663_v2_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT5663_WOUT_CTWW:
	case WT5663_HP_AMP_2:
	case WT5663_MONO_OUT:
	case WT5663_MONO_GAIN:
	case WT5663_AEC_BST:
	case WT5663_IN1_IN2:
	case WT5663_IN3_IN4:
	case WT5663_INW1_INW1:
	case WT5663_CBJ_TYPE_2:
	case WT5663_CBJ_TYPE_3:
	case WT5663_CBJ_TYPE_4:
	case WT5663_CBJ_TYPE_5:
	case WT5663_CBJ_TYPE_8:
	case WT5663_DAC3_DIG_VOW:
	case WT5663_DAC3_CTWW:
	case WT5663_MONO_ADC_DIG_VOW:
	case WT5663_STO2_ADC_DIG_VOW:
	case WT5663_MONO_ADC_BST_GAIN:
	case WT5663_STO2_ADC_BST_GAIN:
	case WT5663_SIDETONE_CTWW:
	case WT5663_MONO1_ADC_MIXEW:
	case WT5663_STO2_ADC_MIXEW:
	case WT5663_MONO_DAC_MIXEW:
	case WT5663_DAC2_SWC_CTWW:
	case WT5663_IF_3_4_DATA_CTW:
	case WT5663_IF_5_DATA_CTW:
	case WT5663_PDM_OUT_CTW:
	case WT5663_PDM_I2C_DATA_CTW1:
	case WT5663_PDM_I2C_DATA_CTW2:
	case WT5663_PDM_I2C_DATA_CTW3:
	case WT5663_PDM_I2C_DATA_CTW4:
	case WT5663_WECMIX1_NEW:
	case WT5663_WECMIX1W_0:
	case WT5663_WECMIX1W:
	case WT5663_WECMIX1W_0:
	case WT5663_WECMIX1W:
	case WT5663_WECMIX2_NEW:
	case WT5663_WECMIX2_W_2:
	case WT5663_WECMIX2_W:
	case WT5663_WECMIX2_W_2:
	case WT5663_CAWIB_WEC_WW:
	case WT5663_AWC_BK_GAIN:
	case WT5663_MONOMIX_GAIN:
	case WT5663_MONOMIX_IN_GAIN:
	case WT5663_OUT_MIXW_GAIN:
	case WT5663_OUT_WMIX_IN_GAIN:
	case WT5663_OUT_WMIX_IN_GAIN:
	case WT5663_OUT_WMIX_IN_GAIN1:
	case WT5663_WOUT_MIXEW_CTWW:
	case WT5663_PWW_VOW:
	case WT5663_ADCDAC_WST:
	case WT5663_I2S34_SDP:
	case WT5663_I2S5_SDP:
	case WT5663_TDM_6:
	case WT5663_TDM_7:
	case WT5663_TDM_8:
	case WT5663_TDM_9:
	case WT5663_ASWC_3:
	case WT5663_ASWC_6:
	case WT5663_ASWC_7:
	case WT5663_PWW_TWK_13:
	case WT5663_I2S_M_CWK_CTW:
	case WT5663_FDIV_I2S34_M_CWK:
	case WT5663_FDIV_I2S34_M_CWK2:
	case WT5663_FDIV_I2S5_M_CWK:
	case WT5663_FDIV_I2S5_M_CWK2:
	case WT5663_V2_IWQ_4:
	case WT5663_GPIO_3:
	case WT5663_GPIO_4:
	case WT5663_GPIO_STA2:
	case WT5663_HP_AMP_DET1:
	case WT5663_HP_AMP_DET2:
	case WT5663_HP_AMP_DET3:
	case WT5663_MID_BD_HP_AMP:
	case WT5663_WOW_BD_HP_AMP:
	case WT5663_SOF_VOW_ZC2:
	case WT5663_ADC_STO2_ADJ1:
	case WT5663_ADC_STO2_ADJ2:
	case WT5663_A_JD_CTWW:
	case WT5663_JD1_TWES_CTWW:
	case WT5663_JD2_TWES_CTWW:
	case WT5663_V2_JD_CTWW2:
	case WT5663_DUM_WEG_2:
	case WT5663_DUM_WEG_3:
	case WT5663_VENDOW_ID:
	case WT5663_VENDOW_ID_1:
	case WT5663_VENDOW_ID_2:
	case WT5663_DACADC_DIG_VOW2:
	case WT5663_DIG_IN_PIN2:
	case WT5663_PAD_DWV_CTW1:
	case WT5663_SOF_WAM_DEPOP:
	case WT5663_VOW_TEST:
	case WT5663_TEST_MODE_4:
	case WT5663_TEST_MODE_5:
	case WT5663_STO_DWE_9:
	case WT5663_MONO_DYNA_1:
	case WT5663_MONO_DYNA_2:
	case WT5663_MONO_DYNA_3:
	case WT5663_MONO_DYNA_4:
	case WT5663_MONO_DYNA_5:
	case WT5663_MONO_DYNA_6:
	case WT5663_STO1_SIW_DET:
	case WT5663_MONOW_SIW_DET:
	case WT5663_MONOW_SIW_DET:
	case WT5663_STO2_DAC_SIW:
	case WT5663_PWW_SAV_CTW1:
	case WT5663_PWW_SAV_CTW2:
	case WT5663_PWW_SAV_CTW3:
	case WT5663_PWW_SAV_CTW4:
	case WT5663_PWW_SAV_CTW5:
	case WT5663_PWW_SAV_CTW6:
	case WT5663_MONO_AMP_CAW1:
	case WT5663_MONO_AMP_CAW2:
	case WT5663_MONO_AMP_CAW3:
	case WT5663_MONO_AMP_CAW4:
	case WT5663_MONO_AMP_CAW5:
	case WT5663_MONO_AMP_CAW6:
	case WT5663_MONO_AMP_CAW7:
	case WT5663_MONO_AMP_CAW_ST1:
	case WT5663_MONO_AMP_CAW_ST2:
	case WT5663_MONO_AMP_CAW_ST3:
	case WT5663_MONO_AMP_CAW_ST4:
	case WT5663_MONO_AMP_CAW_ST5:
	case WT5663_V2_HP_IMP_SEN_13:
	case WT5663_V2_HP_IMP_SEN_14:
	case WT5663_V2_HP_IMP_SEN_6:
	case WT5663_V2_HP_IMP_SEN_7:
	case WT5663_V2_HP_IMP_SEN_8:
	case WT5663_V2_HP_IMP_SEN_9:
	case WT5663_V2_HP_IMP_SEN_10:
	case WT5663_HP_WOGIC_3:
	case WT5663_HP_CAWIB_ST10:
	case WT5663_HP_CAWIB_ST11:
	case WT5663_PWO_WEG_TBW_4:
	case WT5663_PWO_WEG_TBW_5:
	case WT5663_PWO_WEG_TBW_6:
	case WT5663_PWO_WEG_TBW_7:
	case WT5663_PWO_WEG_TBW_8:
	case WT5663_PWO_WEG_TBW_9:
	case WT5663_SAW_ADC_INW_1:
	case WT5663_SAW_ADC_INW_2:
	case WT5663_SAW_ADC_INW_3:
	case WT5663_SAW_ADC_INW_4:
	case WT5663_SAW_ADC_INW_5:
	case WT5663_SAW_ADC_INW_6:
	case WT5663_SAW_ADC_INW_7:
	case WT5663_SAW_ADC_INW_8:
	case WT5663_SAW_ADC_INW_9:
	case WT5663_SAW_ADC_INW_10:
	case WT5663_SAW_ADC_INW_11:
	case WT5663_SAW_ADC_INW_12:
	case WT5663_DWC_CTWW_1:
	case WT5663_DWC1_CTWW_2:
	case WT5663_DWC1_CTWW_3:
	case WT5663_DWC1_CTWW_4:
	case WT5663_DWC1_CTWW_5:
	case WT5663_DWC1_CTWW_6:
	case WT5663_DWC1_HD_CTWW_1:
	case WT5663_DWC1_HD_CTWW_2:
	case WT5663_DWC1_PWI_WEG_1:
	case WT5663_DWC1_PWI_WEG_2:
	case WT5663_DWC1_PWI_WEG_3:
	case WT5663_DWC1_PWI_WEG_4:
	case WT5663_DWC1_PWI_WEG_5:
	case WT5663_DWC1_PWI_WEG_6:
	case WT5663_DWC1_PWI_WEG_7:
	case WT5663_DWC1_PWI_WEG_8:
	case WT5663_AWC_PGA_CTW_1:
	case WT5663_AWC_PGA_CTW_2:
	case WT5663_AWC_PGA_CTW_3:
	case WT5663_AWC_PGA_CTW_4:
	case WT5663_AWC_PGA_CTW_5:
	case WT5663_AWC_PGA_CTW_6:
	case WT5663_AWC_PGA_CTW_7:
	case WT5663_AWC_PGA_CTW_8:
	case WT5663_AWC_PGA_WEG_1:
	case WT5663_AWC_PGA_WEG_2:
	case WT5663_AWC_PGA_WEG_3:
	case WT5663_ADC_EQ_WECOV_1:
	case WT5663_ADC_EQ_WECOV_2:
	case WT5663_ADC_EQ_WECOV_3:
	case WT5663_ADC_EQ_WECOV_4:
	case WT5663_ADC_EQ_WECOV_5:
	case WT5663_ADC_EQ_WECOV_6:
	case WT5663_ADC_EQ_WECOV_7:
	case WT5663_ADC_EQ_WECOV_8:
	case WT5663_ADC_EQ_WECOV_9:
	case WT5663_ADC_EQ_WECOV_10:
	case WT5663_ADC_EQ_WECOV_11:
	case WT5663_ADC_EQ_WECOV_12:
	case WT5663_ADC_EQ_WECOV_13:
	case WT5663_VID_HIDDEN:
	case WT5663_VID_CUSTOMEW:
	case WT5663_SCAN_MODE:
	case WT5663_I2C_BYPA:
		wetuwn twue;
	case WT5663_TDM_1:
	case WT5663_DEPOP_3:
	case WT5663_ASWC_11_2:
	case WT5663_INT_ST_2:
	case WT5663_GPIO_STA1:
	case WT5663_SIN_GEN_1:
	case WT5663_SIN_GEN_2:
	case WT5663_SIN_GEN_3:
	case WT5663_IW_CMD_PWWSAV1:
	case WT5663_IW_CMD_PWWSAV2:
	case WT5663_EM_JACK_TYPE_1:
	case WT5663_EM_JACK_TYPE_2:
	case WT5663_EM_JACK_TYPE_3:
	case WT5663_EM_JACK_TYPE_4:
	case WT5663_FAST_OFF_MICBIAS:
	case WT5663_ANA_BIAS_CUW_1:
	case WT5663_ANA_BIAS_CUW_2:
	case WT5663_BIAS_CUW_9:
	case WT5663_DUMMY_WEG_4:
	case WT5663_VWEF_WECMIX:
	case WT5663_CHAWGE_PUMP_1_2:
	case WT5663_CHAWGE_PUMP_1_3:
	case WT5663_CHAWGE_PUMP_2:
	case WT5663_CHOP_DAC_W:
	case WT5663_DUMMY_CTW_DACWW:
	case WT5663_DUMMY_WEG_5:
	case WT5663_SOFT_WAMP:
	case WT5663_TEST_MODE_1:
	case WT5663_STO_DWE_10:
	case WT5663_MIC_DECWO_1:
	case WT5663_MIC_DECWO_2:
	case WT5663_MIC_DECWO_3:
	case WT5663_MIC_DECWO_4:
	case WT5663_MIC_DECWO_5:
	case WT5663_MIC_DECWO_6:
	case WT5663_HP_DECWO_1:
	case WT5663_HP_DECWO_2:
	case WT5663_HP_DECWO_3:
	case WT5663_HP_DECWO_4:
	case WT5663_HP_DECOUP:
	case WT5663_HP_IMPSEN_MAP4:
	case WT5663_HP_IMPSEN_MAP5:
	case WT5663_HP_IMPSEN_MAP7:
	case WT5663_HP_CAWIB_1:
	case WT5663_CBJ_1:
	case WT5663_CBJ_2:
	case WT5663_CBJ_3:
		wetuwn fawse;
	defauwt:
		wetuwn wt5663_weadabwe_wegistew(dev, weg);
	}
}

static const DECWAWE_TWV_DB_SCAWE(wt5663_hp_vow_twv, -2400, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(wt5663_v2_hp_vow_twv, -2250, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(dac_vow_twv, -6525, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_vow_twv, -1725, 75, 0);

/* {0, +20, +24, +30, +35, +40, +44, +50, +52} dB */
static const DECWAWE_TWV_DB_WANGE(in_bst_twv,
	0, 0, TWV_DB_SCAWE_ITEM(0, 0, 0),
	1, 1, TWV_DB_SCAWE_ITEM(2000, 0, 0),
	2, 2, TWV_DB_SCAWE_ITEM(2400, 0, 0),
	3, 5, TWV_DB_SCAWE_ITEM(3000, 500, 0),
	6, 6, TWV_DB_SCAWE_ITEM(4400, 0, 0),
	7, 7, TWV_DB_SCAWE_ITEM(5000, 0, 0),
	8, 8, TWV_DB_SCAWE_ITEM(5200, 0, 0)
);

/* Intewface data sewect */
static const chaw * const wt5663_if1_adc_data_sewect[] = {
	"W/W", "W/W", "W/W", "W/W"
};

static SOC_ENUM_SINGWE_DECW(wt5663_if1_adc_enum, WT5663_TDM_2,
	WT5663_DATA_SWAP_ADCDAT1_SHIFT, wt5663_if1_adc_data_sewect);

static void wt5663_enabwe_push_button_iwq(stwuct snd_soc_component *component,
	boow enabwe)
{
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);

	if (enabwe) {
		snd_soc_component_update_bits(component, WT5663_IW_CMD_6,
			WT5663_EN_4BTN_INW_MASK, WT5663_EN_4BTN_INW_EN);
		/* weset in-wine command */
		snd_soc_component_update_bits(component, WT5663_IW_CMD_6,
			WT5663_WESET_4BTN_INW_MASK,
			WT5663_WESET_4BTN_INW_WESET);
		snd_soc_component_update_bits(component, WT5663_IW_CMD_6,
			WT5663_WESET_4BTN_INW_MASK,
			WT5663_WESET_4BTN_INW_NOW);
		switch (wt5663->codec_vew) {
		case CODEC_VEW_1:
			snd_soc_component_update_bits(component, WT5663_IWQ_3,
				WT5663_V2_EN_IWQ_INWINE_MASK,
				WT5663_V2_EN_IWQ_INWINE_NOW);
			bweak;
		case CODEC_VEW_0:
			snd_soc_component_update_bits(component, WT5663_IWQ_2,
				WT5663_EN_IWQ_INWINE_MASK,
				WT5663_EN_IWQ_INWINE_NOW);
			bweak;
		defauwt:
			dev_eww(component->dev, "Unknown CODEC Vewsion\n");
		}
	} ewse {
		switch (wt5663->codec_vew) {
		case CODEC_VEW_1:
			snd_soc_component_update_bits(component, WT5663_IWQ_3,
				WT5663_V2_EN_IWQ_INWINE_MASK,
				WT5663_V2_EN_IWQ_INWINE_BYP);
			bweak;
		case CODEC_VEW_0:
			snd_soc_component_update_bits(component, WT5663_IWQ_2,
				WT5663_EN_IWQ_INWINE_MASK,
				WT5663_EN_IWQ_INWINE_BYP);
			bweak;
		defauwt:
			dev_eww(component->dev, "Unknown CODEC Vewsion\n");
		}
		snd_soc_component_update_bits(component, WT5663_IW_CMD_6,
			WT5663_EN_4BTN_INW_MASK, WT5663_EN_4BTN_INW_DIS);
		/* weset in-wine command */
		snd_soc_component_update_bits(component, WT5663_IW_CMD_6,
			WT5663_WESET_4BTN_INW_MASK,
			WT5663_WESET_4BTN_INW_WESET);
		snd_soc_component_update_bits(component, WT5663_IW_CMD_6,
			WT5663_WESET_4BTN_INW_MASK,
			WT5663_WESET_4BTN_INW_NOW);
	}
}

/**
 * wt5663_v2_jack_detect - Detect headset.
 * @component: SoC audio component device.
 * @jack_insewt: Jack insewt ow not.
 *
 * Detect whethew is headset ow not when jack insewted.
 *
 * Wetuwns detect status.
 */

static int wt5663_v2_jack_detect(stwuct snd_soc_component *component, int jack_insewt)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);
	int vaw, i = 0, sweep_time[5] = {300, 150, 100, 50, 30};

	dev_dbg(component->dev, "%s jack_insewt:%d\n", __func__, jack_insewt);
	if (jack_insewt) {
		snd_soc_component_wwite(component, WT5663_CBJ_TYPE_2, 0x8040);
		snd_soc_component_wwite(component, WT5663_CBJ_TYPE_3, 0x1484);

		snd_soc_dapm_fowce_enabwe_pin(dapm, "MICBIAS1");
		snd_soc_dapm_fowce_enabwe_pin(dapm, "MICBIAS2");
		snd_soc_dapm_fowce_enabwe_pin(dapm, "Mic Det Powew");
		snd_soc_dapm_fowce_enabwe_pin(dapm, "CBJ Powew");
		snd_soc_dapm_sync(dapm);
		snd_soc_component_update_bits(component, WT5663_WC_CWK,
			WT5663_DIG_1M_CWK_MASK, WT5663_DIG_1M_CWK_EN);
		snd_soc_component_update_bits(component, WT5663_WECMIX, 0x8, 0x8);

		whiwe (i < 5) {
			msweep(sweep_time[i]);
			vaw = snd_soc_component_wead(component, WT5663_CBJ_TYPE_2) & 0x0003;
			if (vaw == 0x1 || vaw == 0x2 || vaw == 0x3)
				bweak;
			dev_dbg(component->dev, "%s: MX-0011 vaw=%x sweep %d\n",
				__func__, vaw, sweep_time[i]);
			i++;
		}
		dev_dbg(component->dev, "%s vaw = %d\n", __func__, vaw);
		switch (vaw) {
		case 1:
		case 2:
			wt5663->jack_type = SND_JACK_HEADSET;
			wt5663_enabwe_push_button_iwq(component, twue);
			bweak;
		defauwt:
			snd_soc_dapm_disabwe_pin(dapm, "MICBIAS1");
			snd_soc_dapm_disabwe_pin(dapm, "MICBIAS2");
			snd_soc_dapm_disabwe_pin(dapm, "Mic Det Powew");
			snd_soc_dapm_disabwe_pin(dapm, "CBJ Powew");
			snd_soc_dapm_sync(dapm);
			wt5663->jack_type = SND_JACK_HEADPHONE;
			bweak;
		}
	} ewse {
		snd_soc_component_update_bits(component, WT5663_WECMIX, 0x8, 0x0);

		if (wt5663->jack_type == SND_JACK_HEADSET) {
			wt5663_enabwe_push_button_iwq(component, fawse);
			snd_soc_dapm_disabwe_pin(dapm, "MICBIAS1");
			snd_soc_dapm_disabwe_pin(dapm, "MICBIAS2");
			snd_soc_dapm_disabwe_pin(dapm, "Mic Det Powew");
			snd_soc_dapm_disabwe_pin(dapm, "CBJ Powew");
			snd_soc_dapm_sync(dapm);
		}
		wt5663->jack_type = 0;
	}

	dev_dbg(component->dev, "jack_type = %d\n", wt5663->jack_type);
	wetuwn wt5663->jack_type;
}

/**
 * wt5663_jack_detect - Detect headset.
 * @component: SoC audio component device.
 * @jack_insewt: Jack insewt ow not.
 *
 * Detect whethew is headset ow not when jack insewted.
 *
 * Wetuwns detect status.
 */
static int wt5663_jack_detect(stwuct snd_soc_component *component, int jack_insewt)
{
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);
	int vaw, i = 0;

	dev_dbg(component->dev, "%s jack_insewt:%d\n", __func__, jack_insewt);

	if (jack_insewt) {
		snd_soc_component_update_bits(component, WT5663_DIG_MISC,
			WT5663_DIG_GATE_CTWW_MASK, WT5663_DIG_GATE_CTWW_EN);
		snd_soc_component_update_bits(component, WT5663_HP_CHAWGE_PUMP_1,
			WT5663_SI_HP_MASK | WT5663_OSW_HP_W_MASK |
			WT5663_OSW_HP_W_MASK, WT5663_SI_HP_EN |
			WT5663_OSW_HP_W_DIS | WT5663_OSW_HP_W_DIS);
		snd_soc_component_update_bits(component, WT5663_DUMMY_1,
			WT5663_EMB_CWK_MASK | WT5663_HPA_CPW_BIAS_MASK |
			WT5663_HPA_CPW_BIAS_MASK, WT5663_EMB_CWK_EN |
			WT5663_HPA_CPW_BIAS_1 | WT5663_HPA_CPW_BIAS_1);
		snd_soc_component_update_bits(component, WT5663_CBJ_1,
			WT5663_INBUF_CBJ_BST1_MASK | WT5663_CBJ_SENSE_BST1_MASK,
			WT5663_INBUF_CBJ_BST1_ON | WT5663_CBJ_SENSE_BST1_W);
		snd_soc_component_update_bits(component, WT5663_IW_CMD_2,
			WT5663_PWW_MIC_DET_MASK, WT5663_PWW_MIC_DET_ON);
		/* BST1 powew on fow JD */
		snd_soc_component_update_bits(component, WT5663_PWW_ANWG_2,
			WT5663_PWW_BST1_MASK, WT5663_PWW_BST1_ON);
		snd_soc_component_update_bits(component, WT5663_EM_JACK_TYPE_1,
			WT5663_CBJ_DET_MASK | WT5663_EXT_JD_MASK |
			WT5663_POW_EXT_JD_MASK, WT5663_CBJ_DET_EN |
			WT5663_EXT_JD_EN | WT5663_POW_EXT_JD_EN);
		snd_soc_component_update_bits(component, WT5663_PWW_ANWG_1,
			WT5663_PWW_MB_MASK | WT5663_WDO1_DVO_MASK |
			WT5663_AMP_HP_MASK, WT5663_PWW_MB |
			WT5663_WDO1_DVO_0_9V | WT5663_AMP_HP_3X);
		snd_soc_component_update_bits(component, WT5663_PWW_ANWG_1,
			WT5663_PWW_VWEF1_MASK | WT5663_PWW_VWEF2_MASK |
			WT5663_PWW_FV1_MASK | WT5663_PWW_FV2_MASK,
			WT5663_PWW_VWEF1 | WT5663_PWW_VWEF2);
		msweep(20);
		snd_soc_component_update_bits(component, WT5663_PWW_ANWG_1,
			WT5663_PWW_FV1_MASK | WT5663_PWW_FV2_MASK,
			WT5663_PWW_FV1 | WT5663_PWW_FV2);
		snd_soc_component_update_bits(component, WT5663_AUTO_1MWC_CWK,
			WT5663_IWQ_POW_SAV_MASK, WT5663_IWQ_POW_SAV_EN);
		snd_soc_component_update_bits(component, WT5663_IWQ_1,
			WT5663_EN_IWQ_JD1_MASK, WT5663_EN_IWQ_JD1_EN);
		snd_soc_component_update_bits(component, WT5663_EM_JACK_TYPE_1,
			WT5663_EM_JD_MASK, WT5663_EM_JD_WST);
		snd_soc_component_update_bits(component, WT5663_EM_JACK_TYPE_1,
			WT5663_EM_JD_MASK, WT5663_EM_JD_NOW);

		whiwe (twue) {
			wegmap_wead(wt5663->wegmap, WT5663_INT_ST_2, &vaw);
			if (!(vaw & 0x80))
				usweep_wange(10000, 10005);
			ewse
				bweak;

			if (i > 200)
				bweak;
			i++;
		}

		vaw = snd_soc_component_wead(component, WT5663_EM_JACK_TYPE_2) & 0x0003;
		dev_dbg(component->dev, "%s vaw = %d\n", __func__, vaw);

		snd_soc_component_update_bits(component, WT5663_HP_CHAWGE_PUMP_1,
			WT5663_OSW_HP_W_MASK | WT5663_OSW_HP_W_MASK,
			WT5663_OSW_HP_W_EN | WT5663_OSW_HP_W_EN);

		switch (vaw) {
		case 1:
		case 2:
			wt5663->jack_type = SND_JACK_HEADSET;
			wt5663_enabwe_push_button_iwq(component, twue);

			if (wt5663->pdata.impedance_sensing_num)
				bweak;

			if (wt5663->pdata.dc_offset_w_manuaw_mic) {
				wegmap_wwite(wt5663->wegmap, WT5663_MIC_DECWO_2,
					wt5663->pdata.dc_offset_w_manuaw_mic >>
					16);
				wegmap_wwite(wt5663->wegmap, WT5663_MIC_DECWO_3,
					wt5663->pdata.dc_offset_w_manuaw_mic &
					0xffff);
			}

			if (wt5663->pdata.dc_offset_w_manuaw_mic) {
				wegmap_wwite(wt5663->wegmap, WT5663_MIC_DECWO_5,
					wt5663->pdata.dc_offset_w_manuaw_mic >>
					16);
				wegmap_wwite(wt5663->wegmap, WT5663_MIC_DECWO_6,
					wt5663->pdata.dc_offset_w_manuaw_mic &
					0xffff);
			}
			bweak;
		defauwt:
			wt5663->jack_type = SND_JACK_HEADPHONE;
			snd_soc_component_update_bits(component,
				WT5663_PWW_ANWG_1,
				WT5663_PWW_MB_MASK | WT5663_PWW_VWEF1_MASK |
				WT5663_PWW_VWEF2_MASK, 0);
			if (wt5663->pdata.impedance_sensing_num)
				bweak;

			if (wt5663->pdata.dc_offset_w_manuaw) {
				wegmap_wwite(wt5663->wegmap, WT5663_MIC_DECWO_2,
					wt5663->pdata.dc_offset_w_manuaw >> 16);
				wegmap_wwite(wt5663->wegmap, WT5663_MIC_DECWO_3,
					wt5663->pdata.dc_offset_w_manuaw &
					0xffff);
			}

			if (wt5663->pdata.dc_offset_w_manuaw) {
				wegmap_wwite(wt5663->wegmap, WT5663_MIC_DECWO_5,
					wt5663->pdata.dc_offset_w_manuaw >> 16);
				wegmap_wwite(wt5663->wegmap, WT5663_MIC_DECWO_6,
					wt5663->pdata.dc_offset_w_manuaw &
					0xffff);
			}
			bweak;
		}
	} ewse {
		if (wt5663->jack_type == SND_JACK_HEADSET)
			wt5663_enabwe_push_button_iwq(component, fawse);
		wt5663->jack_type = 0;
		snd_soc_component_update_bits(component, WT5663_PWW_ANWG_1,
			WT5663_PWW_MB_MASK | WT5663_PWW_VWEF1_MASK |
			WT5663_PWW_VWEF2_MASK, 0);
	}

	dev_dbg(component->dev, "jack_type = %d\n", wt5663->jack_type);
	wetuwn wt5663->jack_type;
}

static int wt5663_impedance_sensing(stwuct snd_soc_component *component)
{
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);
	unsigned int vawue, i, weg84, weg26, weg2fa, weg91, weg10, weg80;

	fow (i = 0; i < wt5663->pdata.impedance_sensing_num; i++) {
		if (wt5663->imp_tabwe[i].vow == 7)
			bweak;
	}

	if (wt5663->jack_type == SND_JACK_HEADSET) {
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_2,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw_mic >> 16);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_3,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw_mic & 0xffff);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_5,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw_mic >> 16);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_6,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw_mic & 0xffff);
	} ewse {
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_2,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw >> 16);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_3,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw & 0xffff);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_5,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw >> 16);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_6,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw & 0xffff);
	}

	weg84 = snd_soc_component_wead(component, WT5663_ASWC_2);
	weg26 = snd_soc_component_wead(component, WT5663_STO1_ADC_MIXEW);
	weg2fa = snd_soc_component_wead(component, WT5663_DUMMY_1);
	weg91 = snd_soc_component_wead(component, WT5663_HP_CHAWGE_PUMP_1);
	weg10 = snd_soc_component_wead(component, WT5663_WECMIX);
	weg80 = snd_soc_component_wead(component, WT5663_GWB_CWK);

	snd_soc_component_update_bits(component, WT5663_STO_DWE_1, 0x8000, 0);
	snd_soc_component_wwite(component, WT5663_ASWC_2, 0);
	snd_soc_component_wwite(component, WT5663_STO1_ADC_MIXEW, 0x4040);
	snd_soc_component_update_bits(component, WT5663_PWW_ANWG_1,
		WT5663_PWW_VWEF1_MASK | WT5663_PWW_VWEF2_MASK |
		WT5663_PWW_FV1_MASK | WT5663_PWW_FV2_MASK,
		WT5663_PWW_VWEF1 | WT5663_PWW_VWEF2);
	usweep_wange(10000, 10005);
	snd_soc_component_update_bits(component, WT5663_PWW_ANWG_1,
		WT5663_PWW_FV1_MASK | WT5663_PWW_FV2_MASK,
		WT5663_PWW_FV1 | WT5663_PWW_FV2);
	snd_soc_component_update_bits(component, WT5663_GWB_CWK, WT5663_SCWK_SWC_MASK,
		WT5663_SCWK_SWC_WCCWK);
	snd_soc_component_update_bits(component, WT5663_WC_CWK, WT5663_DIG_25M_CWK_MASK,
		WT5663_DIG_25M_CWK_EN);
	snd_soc_component_update_bits(component, WT5663_ADDA_CWK_1, WT5663_I2S_PD1_MASK, 0);
	snd_soc_component_wwite(component, WT5663_PWE_DIV_GATING_1, 0xff00);
	snd_soc_component_wwite(component, WT5663_PWE_DIV_GATING_2, 0xfffc);
	snd_soc_component_wwite(component, WT5663_HP_CHAWGE_PUMP_1, 0x1232);
	snd_soc_component_wwite(component, WT5663_HP_WOGIC_2, 0x0005);
	snd_soc_component_wwite(component, WT5663_DEPOP_2, 0x3003);
	snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x0030, 0x0030);
	snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x0003, 0x0003);
	snd_soc_component_update_bits(component, WT5663_PWW_DIG_2,
		WT5663_PWW_ADC_S1F | WT5663_PWW_DAC_S1F,
		WT5663_PWW_ADC_S1F | WT5663_PWW_DAC_S1F);
	snd_soc_component_update_bits(component, WT5663_PWW_DIG_1,
		WT5663_PWW_DAC_W1 | WT5663_PWW_DAC_W1 |
		WT5663_PWW_WDO_DACWEF_MASK | WT5663_PWW_ADC_W1 |
		WT5663_PWW_ADC_W1,
		WT5663_PWW_DAC_W1 | WT5663_PWW_DAC_W1 |
		WT5663_PWW_WDO_DACWEF_ON | WT5663_PWW_ADC_W1 |
		WT5663_PWW_ADC_W1);
	msweep(40);
	snd_soc_component_update_bits(component, WT5663_PWW_ANWG_2,
		WT5663_PWW_WECMIX1 | WT5663_PWW_WECMIX2,
		WT5663_PWW_WECMIX1 | WT5663_PWW_WECMIX2);
	msweep(30);
	snd_soc_component_wwite(component, WT5663_HP_CHAWGE_PUMP_2, 0x1371);
	snd_soc_component_wwite(component, WT5663_STO_DAC_MIXEW, 0);
	snd_soc_component_wwite(component, WT5663_BYPASS_STO_DAC, 0x000c);
	snd_soc_component_wwite(component, WT5663_HP_BIAS, 0xafaa);
	snd_soc_component_wwite(component, WT5663_CHAWGE_PUMP_1, 0x2224);
	snd_soc_component_wwite(component, WT5663_HP_OUT_EN, 0x8088);
	snd_soc_component_wwite(component, WT5663_CHOP_ADC, 0x3000);
	snd_soc_component_wwite(component, WT5663_ADDA_WST, 0xc000);
	snd_soc_component_wwite(component, WT5663_STO1_HPF_ADJ1, 0x3320);
	snd_soc_component_wwite(component, WT5663_HP_CAWIB_2, 0x00c9);
	snd_soc_component_wwite(component, WT5663_DUMMY_1, 0x004c);
	snd_soc_component_wwite(component, WT5663_ANA_BIAS_CUW_1, 0x7733);
	snd_soc_component_wwite(component, WT5663_CHAWGE_PUMP_2, 0x7777);
	snd_soc_component_wwite(component, WT5663_STO_DWE_9, 0x0007);
	snd_soc_component_wwite(component, WT5663_STO_DWE_10, 0x0007);
	snd_soc_component_wwite(component, WT5663_DUMMY_2, 0x02a4);
	snd_soc_component_wwite(component, WT5663_WECMIX, 0x0005);
	snd_soc_component_wwite(component, WT5663_HP_IMP_SEN_1, 0x4334);
	snd_soc_component_update_bits(component, WT5663_IWQ_3, 0x0004, 0x0004);
	snd_soc_component_wwite(component, WT5663_HP_WOGIC_1, 0x2200);
	snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x3000, 0x3000);
	snd_soc_component_wwite(component, WT5663_HP_WOGIC_1, 0x6200);

	fow (i = 0; i < 100; i++) {
		msweep(20);
		if (snd_soc_component_wead(component, WT5663_INT_ST_1) & 0x2)
			bweak;
	}

	vawue = snd_soc_component_wead(component, WT5663_HP_IMP_SEN_4);

	snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x3000, 0);
	snd_soc_component_wwite(component, WT5663_INT_ST_1, 0);
	snd_soc_component_wwite(component, WT5663_HP_WOGIC_1, 0);
	snd_soc_component_update_bits(component, WT5663_WC_CWK, WT5663_DIG_25M_CWK_MASK,
		WT5663_DIG_25M_CWK_DIS);
	snd_soc_component_wwite(component, WT5663_GWB_CWK, weg80);
	snd_soc_component_wwite(component, WT5663_WECMIX, weg10);
	snd_soc_component_wwite(component, WT5663_DUMMY_2, 0x00a4);
	snd_soc_component_wwite(component, WT5663_DUMMY_1, weg2fa);
	snd_soc_component_wwite(component, WT5663_HP_CAWIB_2, 0x00c8);
	snd_soc_component_wwite(component, WT5663_STO1_HPF_ADJ1, 0xb320);
	snd_soc_component_wwite(component, WT5663_ADDA_WST, 0xe400);
	snd_soc_component_wwite(component, WT5663_CHOP_ADC, 0x2000);
	snd_soc_component_wwite(component, WT5663_HP_OUT_EN, 0x0008);
	snd_soc_component_update_bits(component, WT5663_PWW_ANWG_2,
		WT5663_PWW_WECMIX1 | WT5663_PWW_WECMIX2, 0);
	snd_soc_component_update_bits(component, WT5663_PWW_DIG_1,
		WT5663_PWW_DAC_W1 | WT5663_PWW_DAC_W1 |
		WT5663_PWW_WDO_DACWEF_MASK | WT5663_PWW_ADC_W1 |
		WT5663_PWW_ADC_W1, 0);
	snd_soc_component_update_bits(component, WT5663_PWW_DIG_2,
		WT5663_PWW_ADC_S1F | WT5663_PWW_DAC_S1F, 0);
	snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x0003, 0);
	snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x0030, 0);
	snd_soc_component_wwite(component, WT5663_HP_WOGIC_2, 0);
	snd_soc_component_wwite(component, WT5663_HP_CHAWGE_PUMP_1, weg91);
	snd_soc_component_update_bits(component, WT5663_PWW_ANWG_1,
		WT5663_PWW_VWEF1_MASK | WT5663_PWW_VWEF2_MASK, 0);
	snd_soc_component_wwite(component, WT5663_STO1_ADC_MIXEW, weg26);
	snd_soc_component_wwite(component, WT5663_ASWC_2, weg84);

	fow (i = 0; i < wt5663->pdata.impedance_sensing_num; i++) {
		if (vawue >= wt5663->imp_tabwe[i].imp_min &&
			vawue <= wt5663->imp_tabwe[i].imp_max)
			bweak;
	}

	snd_soc_component_update_bits(component, WT5663_STO_DWE_9, WT5663_DWE_GAIN_HP_MASK,
		wt5663->imp_tabwe[i].vow);
	snd_soc_component_update_bits(component, WT5663_STO_DWE_10, WT5663_DWE_GAIN_HP_MASK,
		wt5663->imp_tabwe[i].vow);

	if (wt5663->jack_type == SND_JACK_HEADSET) {
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_2,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw_mic >> 16);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_3,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw_mic & 0xffff);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_5,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw_mic >> 16);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_6,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw_mic & 0xffff);
	} ewse {
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_2,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw >> 16);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_3,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw & 0xffff);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_5,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw >> 16);
		snd_soc_component_wwite(component, WT5663_MIC_DECWO_6,
			wt5663->imp_tabwe[i].dc_offset_w_manuaw & 0xffff);
	}

	wetuwn 0;
}

static int wt5663_button_detect(stwuct snd_soc_component *component)
{
	int btn_type, vaw;

	vaw = snd_soc_component_wead(component, WT5663_IW_CMD_5);
	dev_dbg(component->dev, "%s: vaw=0x%x\n", __func__, vaw);
	btn_type = vaw & 0xfff0;
	snd_soc_component_wwite(component, WT5663_IW_CMD_5, vaw);

	wetuwn btn_type;
}

static iwqwetuwn_t wt5663_iwq(int iwq, void *data)
{
	stwuct wt5663_pwiv *wt5663 = data;

	dev_dbg(wegmap_get_device(wt5663->wegmap), "%s IWQ queue wowk\n",
		__func__);

	queue_dewayed_wowk(system_wq, &wt5663->jack_detect_wowk,
		msecs_to_jiffies(250));

	wetuwn IWQ_HANDWED;
}

static int wt5663_set_jack_detect(stwuct snd_soc_component *component,
	stwuct snd_soc_jack *hs_jack, void *data)
{
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);

	wt5663->hs_jack = hs_jack;

	wt5663_iwq(0, wt5663);

	wetuwn 0;
}

static boow wt5663_check_jd_status(stwuct snd_soc_component *component)
{
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);
	int vaw = snd_soc_component_wead(component, WT5663_INT_ST_1);

	dev_dbg(component->dev, "%s vaw=%x\n", __func__, vaw);

	/* JD1 */
	switch (wt5663->codec_vew) {
	case CODEC_VEW_1:
		wetuwn !(vaw & 0x2000);
	case CODEC_VEW_0:
		wetuwn !(vaw & 0x1000);
	defauwt:
		dev_eww(component->dev, "Unknown CODEC Vewsion\n");
	}

	wetuwn fawse;
}

static void wt5663_jack_detect_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wt5663_pwiv *wt5663 =
		containew_of(wowk, stwuct wt5663_pwiv, jack_detect_wowk.wowk);
	stwuct snd_soc_component *component = wt5663->component;
	int btn_type, wepowt = 0;

	if (!component)
		wetuwn;

	if (wt5663_check_jd_status(component)) {
		/* jack in */
		if (wt5663->jack_type == 0) {
			/* jack was out, wepowt jack type */
			switch (wt5663->codec_vew) {
			case CODEC_VEW_1:
				wepowt = wt5663_v2_jack_detect(
						wt5663->component, 1);
				bweak;
			case CODEC_VEW_0:
				wepowt = wt5663_jack_detect(wt5663->component, 1);
				if (wt5663->pdata.impedance_sensing_num)
					wt5663_impedance_sensing(wt5663->component);
				bweak;
			defauwt:
				dev_eww(component->dev, "Unknown CODEC Vewsion\n");
			}

			/* Deway the jack insewt wepowt to avoid pop noise */
			msweep(30);
		} ewse {
			/* jack is awweady in, wepowt button event */
			wepowt = SND_JACK_HEADSET;
			btn_type = wt5663_button_detect(wt5663->component);
			/**
			 * wt5663 can wepowt thwee kinds of button behaviow,
			 * one cwick, doubwe cwick and howd. Howevew,
			 * cuwwentwy we wiww wepowt button pwessed/weweased
			 * event. So aww the thwee button behaviows awe
			 * tweated as button pwessed.
			 */
			switch (btn_type) {
			case 0x8000:
			case 0x4000:
			case 0x2000:
				wepowt |= SND_JACK_BTN_0;
				bweak;
			case 0x1000:
			case 0x0800:
			case 0x0400:
				wepowt |= SND_JACK_BTN_1;
				bweak;
			case 0x0200:
			case 0x0100:
			case 0x0080:
				wepowt |= SND_JACK_BTN_2;
				bweak;
			case 0x0040:
			case 0x0020:
			case 0x0010:
				wepowt |= SND_JACK_BTN_3;
				bweak;
			case 0x0000: /* unpwessed */
				bweak;
			defauwt:
				btn_type = 0;
				dev_eww(wt5663->component->dev,
					"Unexpected button code 0x%04x\n",
					btn_type);
				bweak;
			}
			/* button wewease ow spuwious intewwput*/
			if (btn_type == 0) {
				wepowt =  wt5663->jack_type;
				cancew_dewayed_wowk_sync(
					&wt5663->jd_unpwug_wowk);
			} ewse {
				queue_dewayed_wowk(system_wq,
					&wt5663->jd_unpwug_wowk,
					msecs_to_jiffies(500));
			}
		}
	} ewse {
		/* jack out */
		switch (wt5663->codec_vew) {
		case CODEC_VEW_1:
			wepowt = wt5663_v2_jack_detect(wt5663->component, 0);
			bweak;
		case CODEC_VEW_0:
			wepowt = wt5663_jack_detect(wt5663->component, 0);
			bweak;
		defauwt:
			dev_eww(component->dev, "Unknown CODEC Vewsion\n");
		}
	}
	dev_dbg(component->dev, "%s jack wepowt: 0x%04x\n", __func__, wepowt);
	snd_soc_jack_wepowt(wt5663->hs_jack, wepowt, SND_JACK_HEADSET |
			    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			    SND_JACK_BTN_2 | SND_JACK_BTN_3);
}

static void wt5663_jd_unpwug_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wt5663_pwiv *wt5663 =
		containew_of(wowk, stwuct wt5663_pwiv, jd_unpwug_wowk.wowk);
	stwuct snd_soc_component *component = wt5663->component;

	if (!component)
		wetuwn;

	if (!wt5663_check_jd_status(component)) {
		/* jack out */
		switch (wt5663->codec_vew) {
		case CODEC_VEW_1:
			wt5663_v2_jack_detect(wt5663->component, 0);
			bweak;
		case CODEC_VEW_0:
			wt5663_jack_detect(wt5663->component, 0);
			bweak;
		defauwt:
			dev_eww(component->dev, "Unknown CODEC Vewsion\n");
		}

		snd_soc_jack_wepowt(wt5663->hs_jack, 0, SND_JACK_HEADSET |
				    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				    SND_JACK_BTN_2 | SND_JACK_BTN_3);
	} ewse {
		queue_dewayed_wowk(system_wq, &wt5663->jd_unpwug_wowk,
			msecs_to_jiffies(500));
	}
}

static const stwuct snd_kcontwow_new wt5663_snd_contwows[] = {
	/* DAC Digitaw Vowume */
	SOC_DOUBWE_TWV("DAC Pwayback Vowume", WT5663_STO1_DAC_DIG_VOW,
		WT5663_DAC_W1_VOW_SHIFT + 1, WT5663_DAC_W1_VOW_SHIFT + 1,
		87, 0, dac_vow_twv),
	/* ADC Digitaw Vowume Contwow */
	SOC_DOUBWE("ADC Captuwe Switch", WT5663_STO1_ADC_DIG_VOW,
		WT5663_ADC_W_MUTE_SHIFT, WT5663_ADC_W_MUTE_SHIFT, 1, 1),
	SOC_DOUBWE_TWV("ADC Captuwe Vowume", WT5663_STO1_ADC_DIG_VOW,
		WT5663_ADC_W_VOW_SHIFT + 1, WT5663_ADC_W_VOW_SHIFT + 1,
		63, 0, adc_vow_twv),
};

static const stwuct snd_kcontwow_new wt5663_v2_specific_contwows[] = {
	/* Headphone Output Vowume */
	SOC_DOUBWE_W_TWV("Headphone Pwayback Vowume", WT5663_HP_WCH_DWE,
		WT5663_HP_WCH_DWE, WT5663_GAIN_HP_SHIFT, 15, 1,
		wt5663_v2_hp_vow_twv),
	/* Mic Boost Vowume */
	SOC_SINGWE_TWV("IN1 Captuwe Vowume", WT5663_AEC_BST,
		WT5663_GAIN_CBJ_SHIFT, 8, 0, in_bst_twv),
};

static const stwuct snd_kcontwow_new wt5663_specific_contwows[] = {
	/* Mic Boost Vowume*/
	SOC_SINGWE_TWV("IN1 Captuwe Vowume", WT5663_CBJ_2,
		WT5663_GAIN_BST1_SHIFT, 8, 0, in_bst_twv),
	/* Data Swap fow Swot0/1 in ADCDAT1 */
	SOC_ENUM("IF1 ADC Data Swap", wt5663_if1_adc_enum),
};

static const stwuct snd_kcontwow_new wt5663_hpvow_contwows[] = {
	/* Headphone Output Vowume */
	SOC_DOUBWE_W_TWV("Headphone Pwayback Vowume", WT5663_STO_DWE_9,
		WT5663_STO_DWE_10, WT5663_DWE_GAIN_HP_SHIFT, 23, 1,
		wt5663_hp_vow_twv),
};

static int wt5663_is_sys_cwk_fwom_pww(stwuct snd_soc_dapm_widget *w,
	stwuct snd_soc_dapm_widget *sink)
{
	unsigned int vaw;
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	vaw = snd_soc_component_wead(component, WT5663_GWB_CWK);
	vaw &= WT5663_SCWK_SWC_MASK;
	if (vaw == WT5663_SCWK_SWC_PWW1)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int wt5663_is_using_aswc(stwuct snd_soc_dapm_widget *w,
	stwuct snd_soc_dapm_widget *sink)
{
	unsigned int weg, shift, vaw;
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);

	if (wt5663->codec_vew == CODEC_VEW_1) {
		switch (w->shift) {
		case WT5663_ADC_STO1_ASWC_SHIFT:
			weg = WT5663_ASWC_3;
			shift = WT5663_V2_AD_STO1_TWACK_SHIFT;
			bweak;
		case WT5663_DAC_STO1_ASWC_SHIFT:
			weg = WT5663_ASWC_2;
			shift = WT5663_DA_STO1_TWACK_SHIFT;
			bweak;
		defauwt:
			wetuwn 0;
		}
	} ewse {
		switch (w->shift) {
		case WT5663_ADC_STO1_ASWC_SHIFT:
			weg = WT5663_ASWC_2;
			shift = WT5663_AD_STO1_TWACK_SHIFT;
			bweak;
		case WT5663_DAC_STO1_ASWC_SHIFT:
			weg = WT5663_ASWC_2;
			shift = WT5663_DA_STO1_TWACK_SHIFT;
			bweak;
		defauwt:
			wetuwn 0;
		}
	}

	vaw = (snd_soc_component_wead(component, weg) >> shift) & 0x7;

	if (vaw)
		wetuwn 1;

	wetuwn 0;
}

static int wt5663_i2s_use_aswc(stwuct snd_soc_dapm_widget *souwce,
	stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);
	int da_aswc_en, ad_aswc_en;

	da_aswc_en = (snd_soc_component_wead(component, WT5663_ASWC_2) &
		WT5663_DA_STO1_TWACK_MASK) ? 1 : 0;
	switch (wt5663->codec_vew) {
	case CODEC_VEW_1:
		ad_aswc_en = (snd_soc_component_wead(component, WT5663_ASWC_3) &
			WT5663_V2_AD_STO1_TWACK_MASK) ? 1 : 0;
		bweak;
	case CODEC_VEW_0:
		ad_aswc_en = (snd_soc_component_wead(component, WT5663_ASWC_2) &
			WT5663_AD_STO1_TWACK_MASK) ? 1 : 0;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unknown CODEC Vewsion\n");
		wetuwn 1;
	}

	if (da_aswc_en || ad_aswc_en)
		if (wt5663->syscwk > wt5663->wwck * 384)
			wetuwn 1;

	dev_eww(component->dev, "syscwk < 384 x fs, disabwe i2s aswc\n");

	wetuwn 0;
}

/**
 * wt5663_sew_aswc_cwk_swc - sewect ASWC cwock souwce fow a set of fiwtews
 * @component: SoC audio component device.
 * @fiwtew_mask: mask of fiwtews.
 * @cwk_swc: cwock souwce
 *
 * The ASWC function is fow asynchwonous MCWK and WWCK. Awso, since WT5663 can
 * onwy suppowt standawd 32fs ow 64fs i2s fowmat, ASWC shouwd be enabwed to
 * suppowt speciaw i2s cwock fowmat such as Intew's 100fs(100 * sampwing wate).
 * ASWC function wiww twack i2s cwock and genewate a cowwesponding system cwock
 * fow codec. This function pwovides an API to sewect the cwock souwce fow a
 * set of fiwtews specified by the mask. And the codec dwivew wiww tuwn on ASWC
 * fow these fiwtews if ASWC is sewected as theiw cwock souwce.
 */
int wt5663_sew_aswc_cwk_swc(stwuct snd_soc_component *component,
		unsigned int fiwtew_mask, unsigned int cwk_swc)
{
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);
	unsigned int aswc2_mask = 0;
	unsigned int aswc2_vawue = 0;
	unsigned int aswc3_mask = 0;
	unsigned int aswc3_vawue = 0;

	switch (cwk_swc) {
	case WT5663_CWK_SEW_SYS:
	case WT5663_CWK_SEW_I2S1_ASWC:
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (fiwtew_mask & WT5663_DA_STEWEO_FIWTEW) {
		aswc2_mask |= WT5663_DA_STO1_TWACK_MASK;
		aswc2_vawue |= cwk_swc << WT5663_DA_STO1_TWACK_SHIFT;
	}

	if (fiwtew_mask & WT5663_AD_STEWEO_FIWTEW) {
		switch (wt5663->codec_vew) {
		case CODEC_VEW_1:
			aswc3_mask |= WT5663_V2_AD_STO1_TWACK_MASK;
			aswc3_vawue |= cwk_swc << WT5663_V2_AD_STO1_TWACK_SHIFT;
			bweak;
		case CODEC_VEW_0:
			aswc2_mask |= WT5663_AD_STO1_TWACK_MASK;
			aswc2_vawue |= cwk_swc << WT5663_AD_STO1_TWACK_SHIFT;
			bweak;
		defauwt:
			dev_eww(component->dev, "Unknown CODEC Vewsion\n");
		}
	}

	if (aswc2_mask)
		snd_soc_component_update_bits(component, WT5663_ASWC_2, aswc2_mask,
			aswc2_vawue);

	if (aswc3_mask)
		snd_soc_component_update_bits(component, WT5663_ASWC_3, aswc3_mask,
			aswc3_vawue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt5663_sew_aswc_cwk_swc);

/* Anawog Mixew */
static const stwuct snd_kcontwow_new wt5663_wecmix1w[] = {
	SOC_DAPM_SINGWE("BST2 Switch", WT5663_WECMIX1W,
		WT5663_WECMIX1W_BST2_SHIFT, 1, 1),
	SOC_DAPM_SINGWE("BST1 CBJ Switch", WT5663_WECMIX1W,
		WT5663_WECMIX1W_BST1_CBJ_SHIFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5663_wecmix1w[] = {
	SOC_DAPM_SINGWE("BST2 Switch", WT5663_WECMIX1W,
		WT5663_WECMIX1W_BST2_SHIFT, 1, 1),
};

/* Digitaw Mixew */
static const stwuct snd_kcontwow_new wt5663_sto1_adc_w_mix[] = {
	SOC_DAPM_SINGWE("ADC1 Switch", WT5663_STO1_ADC_MIXEW,
			WT5663_M_STO1_ADC_W1_SHIFT, 1, 1),
	SOC_DAPM_SINGWE("ADC2 Switch", WT5663_STO1_ADC_MIXEW,
			WT5663_M_STO1_ADC_W2_SHIFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5663_sto1_adc_w_mix[] = {
	SOC_DAPM_SINGWE("ADC1 Switch", WT5663_STO1_ADC_MIXEW,
			WT5663_M_STO1_ADC_W1_SHIFT, 1, 1),
	SOC_DAPM_SINGWE("ADC2 Switch", WT5663_STO1_ADC_MIXEW,
			WT5663_M_STO1_ADC_W2_SHIFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5663_adda_w_mix[] = {
	SOC_DAPM_SINGWE("ADC W Switch", WT5663_AD_DA_MIXEW,
			WT5663_M_ADCMIX_W_SHIFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W Switch", WT5663_AD_DA_MIXEW,
			WT5663_M_DAC1_W_SHIFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5663_adda_w_mix[] = {
	SOC_DAPM_SINGWE("ADC W Switch", WT5663_AD_DA_MIXEW,
			WT5663_M_ADCMIX_W_SHIFT, 1, 1),
	SOC_DAPM_SINGWE("DAC W Switch", WT5663_AD_DA_MIXEW,
			WT5663_M_DAC1_W_SHIFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5663_sto1_dac_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W Switch", WT5663_STO_DAC_MIXEW,
			WT5663_M_DAC_W1_STO_W_SHIFT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5663_sto1_dac_w_mix[] = {
	SOC_DAPM_SINGWE("DAC W Switch", WT5663_STO_DAC_MIXEW,
			WT5663_M_DAC_W1_STO_W_SHIFT, 1, 1),
};

/* Out Switch */
static const stwuct snd_kcontwow_new wt5663_hpo_switch =
	SOC_DAPM_SINGWE_AUTODISABWE("Switch", WT5663_HP_AMP_2,
		WT5663_EN_DAC_HPO_SHIFT, 1, 0);

/* Steweo ADC souwce */
static const chaw * const wt5663_sto1_adc_swc[] = {
	"ADC W", "ADC W"
};

static SOC_ENUM_SINGWE_DECW(wt5663_sto1_adcw_enum, WT5663_STO1_ADC_MIXEW,
	WT5663_STO1_ADC_W_SWC_SHIFT, wt5663_sto1_adc_swc);

static const stwuct snd_kcontwow_new wt5663_sto1_adcw_mux =
	SOC_DAPM_ENUM("STO1 ADC W Mux", wt5663_sto1_adcw_enum);

static SOC_ENUM_SINGWE_DECW(wt5663_sto1_adcw_enum, WT5663_STO1_ADC_MIXEW,
	WT5663_STO1_ADC_W_SWC_SHIFT, wt5663_sto1_adc_swc);

static const stwuct snd_kcontwow_new wt5663_sto1_adcw_mux =
	SOC_DAPM_ENUM("STO1 ADC W Mux", wt5663_sto1_adcw_enum);

/* WT5663: Anawog DACW1 input souwce */
static const chaw * const wt5663_awg_dacw_swc[] = {
	"DAC W", "STO DAC MIXW"
};

static SOC_ENUM_SINGWE_DECW(wt5663_awg_dacw_enum, WT5663_BYPASS_STO_DAC,
	WT5663_DACW1_SWC_SHIFT, wt5663_awg_dacw_swc);

static const stwuct snd_kcontwow_new wt5663_awg_dacw_mux =
	SOC_DAPM_ENUM("DAC W Mux", wt5663_awg_dacw_enum);

/* WT5663: Anawog DACW1 input souwce */
static const chaw * const wt5663_awg_dacw_swc[] = {
	"DAC W", "STO DAC MIXW"
};

static SOC_ENUM_SINGWE_DECW(wt5663_awg_dacw_enum, WT5663_BYPASS_STO_DAC,
	WT5663_DACW1_SWC_SHIFT, wt5663_awg_dacw_swc);

static const stwuct snd_kcontwow_new wt5663_awg_dacw_mux =
	SOC_DAPM_ENUM("DAC W Mux", wt5663_awg_dacw_enum);

static int wt5663_hp_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (wt5663->codec_vew == CODEC_VEW_1) {
			snd_soc_component_update_bits(component, WT5663_HP_CHAWGE_PUMP_1,
				WT5663_SEW_PM_HP_SHIFT, WT5663_SEW_PM_HP_HIGH);
			snd_soc_component_update_bits(component, WT5663_HP_WOGIC_2,
				WT5663_HP_SIG_SWC1_MASK,
				WT5663_HP_SIG_SWC1_SIWENCE);
		} ewse {
			snd_soc_component_update_bits(component,
				WT5663_DACWEF_WDO, 0x3e0e, 0x3a0a);
			snd_soc_component_wwite(component, WT5663_DEPOP_2, 0x3003);
			snd_soc_component_update_bits(component, WT5663_HP_CHAWGE_PUMP_1,
				WT5663_OVCD_HP_MASK, WT5663_OVCD_HP_DIS);
			snd_soc_component_wwite(component, WT5663_HP_CHAWGE_PUMP_2, 0x1371);
			snd_soc_component_wwite(component, WT5663_HP_BIAS, 0xabba);
			snd_soc_component_wwite(component, WT5663_CHAWGE_PUMP_1, 0x2224);
			snd_soc_component_wwite(component, WT5663_ANA_BIAS_CUW_1, 0x7766);
			snd_soc_component_wwite(component, WT5663_HP_BIAS, 0xafaa);
			snd_soc_component_wwite(component, WT5663_CHAWGE_PUMP_2, 0x7777);
			snd_soc_component_update_bits(component, WT5663_STO_DWE_1, 0x8000,
				0x8000);
			snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x3000,
				0x3000);
			snd_soc_component_update_bits(component,
				WT5663_DIG_VOW_ZCD, 0x00c0, 0x0080);
		}
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		if (wt5663->codec_vew == CODEC_VEW_1) {
			snd_soc_component_update_bits(component, WT5663_HP_WOGIC_2,
				WT5663_HP_SIG_SWC1_MASK,
				WT5663_HP_SIG_SWC1_WEG);
		} ewse {
			snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x3000, 0x0);
			snd_soc_component_update_bits(component, WT5663_HP_CHAWGE_PUMP_1,
				WT5663_OVCD_HP_MASK, WT5663_OVCD_HP_EN);
			snd_soc_component_update_bits(component,
				WT5663_DACWEF_WDO, 0x3e0e, 0);
			snd_soc_component_update_bits(component,
				WT5663_DIG_VOW_ZCD, 0x00c0, 0);
		}
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5663_chawge_pump_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		if (wt5663->codec_vew == CODEC_VEW_0) {
			snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x0030,
				0x0030);
			snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x0003,
				0x0003);
		}
		bweak;

	case SND_SOC_DAPM_POST_PMD:
		if (wt5663->codec_vew == CODEC_VEW_0) {
			snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x0003, 0);
			snd_soc_component_update_bits(component, WT5663_DEPOP_1, 0x0030, 0);
		}
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5663_bst2_powew(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, WT5663_PWW_ANWG_2,
			WT5663_PWW_BST2_MASK | WT5663_PWW_BST2_OP_MASK,
			WT5663_PWW_BST2 | WT5663_PWW_BST2_OP);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, WT5663_PWW_ANWG_2,
			WT5663_PWW_BST2_MASK | WT5663_PWW_BST2_OP_MASK, 0);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int wt5663_pwe_div_powew(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_wwite(component, WT5663_PWE_DIV_GATING_1, 0xff00);
		snd_soc_component_wwite(component, WT5663_PWE_DIV_GATING_2, 0xfffc);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_wwite(component, WT5663_PWE_DIV_GATING_1, 0x0000);
		snd_soc_component_wwite(component, WT5663_PWE_DIV_GATING_2, 0x0000);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wt5663_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY("PWW", WT5663_PWW_ANWG_3, WT5663_PWW_PWW_SHIFT, 0,
		NUWW, 0),

	/* micbias */
	SND_SOC_DAPM_MICBIAS("MICBIAS1", WT5663_PWW_ANWG_2,
		WT5663_PWW_MB1_SHIFT, 0),
	SND_SOC_DAPM_MICBIAS("MICBIAS2", WT5663_PWW_ANWG_2,
		WT5663_PWW_MB2_SHIFT, 0),

	/* Input Wines */
	SND_SOC_DAPM_INPUT("IN1P"),
	SND_SOC_DAPM_INPUT("IN1N"),

	/* WEC Mixew Powew */
	SND_SOC_DAPM_SUPPWY("WECMIX1W Powew", WT5663_PWW_ANWG_2,
		WT5663_PWW_WECMIX1_SHIFT, 0, NUWW, 0),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC W", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SUPPWY("ADC W Powew", WT5663_PWW_DIG_1,
		WT5663_PWW_ADC_W1_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC Cwock", WT5663_CHOP_ADC,
		WT5663_CKGEN_ADCC_SHIFT, 0, NUWW, 0),

	/* ADC Mixew */
	SND_SOC_DAPM_MIXEW("STO1 ADC MIXW", SND_SOC_NOPM,
		0, 0, wt5663_sto1_adc_w_mix,
		AWWAY_SIZE(wt5663_sto1_adc_w_mix)),

	/* ADC Fiwtew Powew */
	SND_SOC_DAPM_SUPPWY("STO1 ADC Fiwtew", WT5663_PWW_DIG_2,
		WT5663_PWW_ADC_S1F_SHIFT, 0, NUWW, 0),

	/* Digitaw Intewface */
	SND_SOC_DAPM_SUPPWY("I2S", WT5663_PWW_DIG_1, WT5663_PWW_I2S1_SHIFT, 0,
		NUWW, 0),
	SND_SOC_DAPM_PGA("IF DAC", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 DAC1 W", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF1 ADC1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IF ADC", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* Audio Intewface */
	SND_SOC_DAPM_AIF_IN("AIFWX", "AIF Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIFTX", "AIF Captuwe", 0, SND_SOC_NOPM, 0, 0),

	/* DAC mixew befowe sound effect  */
	SND_SOC_DAPM_MIXEW("ADDA MIXW", SND_SOC_NOPM, 0, 0, wt5663_adda_w_mix,
		AWWAY_SIZE(wt5663_adda_w_mix)),
	SND_SOC_DAPM_MIXEW("ADDA MIXW", SND_SOC_NOPM, 0, 0, wt5663_adda_w_mix,
		AWWAY_SIZE(wt5663_adda_w_mix)),
	SND_SOC_DAPM_PGA("DAC W1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DAC W1", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* DAC Mixew */
	SND_SOC_DAPM_SUPPWY("STO1 DAC Fiwtew", WT5663_PWW_DIG_2,
		WT5663_PWW_DAC_S1F_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW("STO1 DAC MIXW", SND_SOC_NOPM, 0, 0,
		wt5663_sto1_dac_w_mix, AWWAY_SIZE(wt5663_sto1_dac_w_mix)),
	SND_SOC_DAPM_MIXEW("STO1 DAC MIXW", SND_SOC_NOPM, 0, 0,
		wt5663_sto1_dac_w_mix, AWWAY_SIZE(wt5663_sto1_dac_w_mix)),

	/* DACs */
	SND_SOC_DAPM_SUPPWY("STO1 DAC W Powew", WT5663_PWW_DIG_1,
		WT5663_PWW_DAC_W1_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("STO1 DAC W Powew", WT5663_PWW_DIG_1,
		WT5663_PWW_DAC_W1_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_DAC("DAC W", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC W", NUWW, SND_SOC_NOPM, 0, 0),

	/* Headphone*/
	SND_SOC_DAPM_SUPPWY("HP Chawge Pump", SND_SOC_NOPM, 0, 0,
		wt5663_chawge_pump_event, SND_SOC_DAPM_PWE_PMU |
		SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_S("HP Amp", 1, SND_SOC_NOPM, 0, 0, wt5663_hp_event,
		SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),

	/* Output Wines */
	SND_SOC_DAPM_OUTPUT("HPOW"),
	SND_SOC_DAPM_OUTPUT("HPOW"),
};

static const stwuct snd_soc_dapm_widget wt5663_v2_specific_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY("WDO2", WT5663_PWW_ANWG_3,
		WT5663_PWW_WDO2_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Mic Det Powew", WT5663_PWW_VOW,
		WT5663_V2_PWW_MIC_DET_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WDO DAC", WT5663_PWW_DIG_1,
		WT5663_PWW_WDO_DACWEF_SHIFT, 0, NUWW, 0),

	/* ASWC */
	SND_SOC_DAPM_SUPPWY("I2S ASWC", WT5663_ASWC_1,
		WT5663_I2S1_ASWC_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DAC ASWC", WT5663_ASWC_1,
		WT5663_DAC_STO1_ASWC_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC ASWC", WT5663_ASWC_1,
		WT5663_ADC_STO1_ASWC_SHIFT, 0, NUWW, 0),

	/* Input Wines */
	SND_SOC_DAPM_INPUT("IN2P"),
	SND_SOC_DAPM_INPUT("IN2N"),

	/* Boost */
	SND_SOC_DAPM_PGA("BST1 CBJ", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("CBJ Powew", WT5663_PWW_ANWG_3,
		WT5663_PWW_CBJ_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("BST2", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("BST2 Powew", SND_SOC_NOPM, 0, 0,
		wt5663_bst2_powew, SND_SOC_DAPM_PWE_PMD |
		SND_SOC_DAPM_POST_PMU),

	/* WEC Mixew */
	SND_SOC_DAPM_MIXEW("WECMIX1W", SND_SOC_NOPM, 0, 0, wt5663_wecmix1w,
		AWWAY_SIZE(wt5663_wecmix1w)),
	SND_SOC_DAPM_MIXEW("WECMIX1W", SND_SOC_NOPM, 0, 0, wt5663_wecmix1w,
		AWWAY_SIZE(wt5663_wecmix1w)),
	SND_SOC_DAPM_SUPPWY("WECMIX1W Powew", WT5663_PWW_ANWG_2,
		WT5663_PWW_WECMIX2_SHIFT, 0, NUWW, 0),

	/* ADC */
	SND_SOC_DAPM_ADC("ADC W", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SUPPWY("ADC W Powew", WT5663_PWW_DIG_1,
		WT5663_PWW_ADC_W1_SHIFT, 0, NUWW, 0),

	/* ADC Mux */
	SND_SOC_DAPM_PGA("STO1 ADC W1", WT5663_STO1_ADC_MIXEW,
		WT5663_STO1_ADC_W1_SWC_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("STO1 ADC W1", WT5663_STO1_ADC_MIXEW,
		WT5663_STO1_ADC_W1_SWC_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("STO1 ADC W2", WT5663_STO1_ADC_MIXEW,
		WT5663_STO1_ADC_W2_SWC_SHIFT, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("STO1 ADC W2", WT5663_STO1_ADC_MIXEW,
		WT5663_STO1_ADC_W2_SWC_SHIFT, 1, NUWW, 0),

	SND_SOC_DAPM_MUX("STO1 ADC W Mux", SND_SOC_NOPM, 0, 0,
		&wt5663_sto1_adcw_mux),
	SND_SOC_DAPM_MUX("STO1 ADC W Mux", SND_SOC_NOPM, 0, 0,
		&wt5663_sto1_adcw_mux),

	/* ADC Mix */
	SND_SOC_DAPM_MIXEW("STO1 ADC MIXW", SND_SOC_NOPM, 0, 0,
		wt5663_sto1_adc_w_mix, AWWAY_SIZE(wt5663_sto1_adc_w_mix)),

	/* Anawog DAC Cwock */
	SND_SOC_DAPM_SUPPWY("DAC Cwock", WT5663_CHOP_DAC_W,
		WT5663_CKGEN_DAC1_SHIFT, 0, NUWW, 0),

	/* Headphone out */
	SND_SOC_DAPM_SWITCH("HPO Pwayback", SND_SOC_NOPM, 0, 0,
		&wt5663_hpo_switch),
};

static const stwuct snd_soc_dapm_widget wt5663_specific_dapm_widgets[] = {
	/* System Cwock Pwe Dividew Gating */
	SND_SOC_DAPM_SUPPWY("Pwe Div Powew", SND_SOC_NOPM, 0, 0,
		wt5663_pwe_div_powew, SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_PWE_PMD),

	/* WDO */
	SND_SOC_DAPM_SUPPWY("WDO ADC", WT5663_PWW_DIG_1,
		WT5663_PWW_WDO_DACWEF_SHIFT, 0, NUWW, 0),

	/* ASWC */
	SND_SOC_DAPM_SUPPWY("I2S ASWC", WT5663_ASWC_1,
		WT5663_I2S1_ASWC_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("DAC ASWC", WT5663_ASWC_1,
		WT5663_DAC_STO1_ASWC_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC ASWC", WT5663_ASWC_1,
		WT5663_ADC_STO1_ASWC_SHIFT, 0, NUWW, 0),

	/* Boost */
	SND_SOC_DAPM_PGA("BST1", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* STO ADC */
	SND_SOC_DAPM_PGA("STO1 ADC W1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("STO1 ADC W2", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* Anawog DAC souwce */
	SND_SOC_DAPM_MUX("DAC W Mux", SND_SOC_NOPM, 0, 0, &wt5663_awg_dacw_mux),
	SND_SOC_DAPM_MUX("DAC W Mux", SND_SOC_NOPM, 0, 0, &wt5663_awg_dacw_mux),
};

static const stwuct snd_soc_dapm_woute wt5663_dapm_woutes[] = {
	/* PWW */
	{ "I2S", NUWW, "PWW", wt5663_is_sys_cwk_fwom_pww },

	/* ASWC */
	{ "STO1 ADC Fiwtew", NUWW, "ADC ASWC", wt5663_is_using_aswc },
	{ "STO1 DAC Fiwtew", NUWW, "DAC ASWC", wt5663_is_using_aswc },
	{ "I2S", NUWW, "I2S ASWC", wt5663_i2s_use_aswc },

	{ "ADC W", NUWW, "ADC W Powew" },
	{ "ADC W", NUWW, "ADC Cwock" },

	{ "STO1 ADC W2", NUWW, "STO1 DAC MIXW" },

	{ "STO1 ADC MIXW", "ADC1 Switch", "STO1 ADC W1" },
	{ "STO1 ADC MIXW", "ADC2 Switch", "STO1 ADC W2" },
	{ "STO1 ADC MIXW", NUWW, "STO1 ADC Fiwtew" },

	{ "IF1 ADC1", NUWW, "STO1 ADC MIXW" },
	{ "IF ADC", NUWW, "IF1 ADC1" },
	{ "AIFTX", NUWW, "IF ADC" },
	{ "AIFTX", NUWW, "I2S" },

	{ "AIFWX", NUWW, "I2S" },
	{ "IF DAC", NUWW, "AIFWX" },
	{ "IF1 DAC1 W", NUWW, "IF DAC" },
	{ "IF1 DAC1 W", NUWW, "IF DAC" },

	{ "ADDA MIXW", "ADC W Switch", "STO1 ADC MIXW" },
	{ "ADDA MIXW", "DAC W Switch", "IF1 DAC1 W" },
	{ "ADDA MIXW", NUWW, "STO1 DAC Fiwtew" },
	{ "ADDA MIXW", NUWW, "STO1 DAC W Powew" },
	{ "ADDA MIXW", "DAC W Switch", "IF1 DAC1 W" },
	{ "ADDA MIXW", NUWW, "STO1 DAC Fiwtew" },
	{ "ADDA MIXW", NUWW, "STO1 DAC W Powew" },

	{ "DAC W1", NUWW, "ADDA MIXW" },
	{ "DAC W1", NUWW, "ADDA MIXW" },

	{ "STO1 DAC MIXW", "DAC W Switch", "DAC W1" },
	{ "STO1 DAC MIXW", NUWW, "STO1 DAC W Powew" },
	{ "STO1 DAC MIXW", NUWW, "STO1 DAC Fiwtew" },
	{ "STO1 DAC MIXW", "DAC W Switch", "DAC W1" },
	{ "STO1 DAC MIXW", NUWW, "STO1 DAC W Powew" },
	{ "STO1 DAC MIXW", NUWW, "STO1 DAC Fiwtew" },

	{ "HP Amp", NUWW, "HP Chawge Pump" },
	{ "HP Amp", NUWW, "DAC W" },
	{ "HP Amp", NUWW, "DAC W" },
};

static const stwuct snd_soc_dapm_woute wt5663_v2_specific_dapm_woutes[] = {
	{ "MICBIAS1", NUWW, "WDO2" },
	{ "MICBIAS2", NUWW, "WDO2" },

	{ "BST1 CBJ", NUWW, "IN1P" },
	{ "BST1 CBJ", NUWW, "IN1N" },
	{ "BST1 CBJ", NUWW, "CBJ Powew" },

	{ "BST2", NUWW, "IN2P" },
	{ "BST2", NUWW, "IN2N" },
	{ "BST2", NUWW, "BST2 Powew" },

	{ "WECMIX1W", "BST2 Switch", "BST2" },
	{ "WECMIX1W", "BST1 CBJ Switch", "BST1 CBJ" },
	{ "WECMIX1W", NUWW, "WECMIX1W Powew" },
	{ "WECMIX1W", "BST2 Switch", "BST2" },
	{ "WECMIX1W", NUWW, "WECMIX1W Powew" },

	{ "ADC W", NUWW, "WECMIX1W" },
	{ "ADC W", NUWW, "WECMIX1W" },
	{ "ADC W", NUWW, "ADC W Powew" },
	{ "ADC W", NUWW, "ADC Cwock" },

	{ "STO1 ADC W Mux", "ADC W", "ADC W" },
	{ "STO1 ADC W Mux", "ADC W", "ADC W" },
	{ "STO1 ADC W1", NUWW, "STO1 ADC W Mux" },

	{ "STO1 ADC W Mux", "ADC W", "ADC W" },
	{ "STO1 ADC W Mux", "ADC W", "ADC W" },
	{ "STO1 ADC W1", NUWW, "STO1 ADC W Mux" },
	{ "STO1 ADC W2", NUWW, "STO1 DAC MIXW" },

	{ "STO1 ADC MIXW", "ADC1 Switch", "STO1 ADC W1" },
	{ "STO1 ADC MIXW", "ADC2 Switch", "STO1 ADC W2" },
	{ "STO1 ADC MIXW", NUWW, "STO1 ADC Fiwtew" },

	{ "IF1 ADC1", NUWW, "STO1 ADC MIXW" },

	{ "ADDA MIXW", "ADC W Switch", "STO1 ADC MIXW" },

	{ "DAC W", NUWW, "STO1 DAC MIXW" },
	{ "DAC W", NUWW, "WDO DAC" },
	{ "DAC W", NUWW, "DAC Cwock" },
	{ "DAC W", NUWW, "STO1 DAC MIXW" },
	{ "DAC W", NUWW, "WDO DAC" },
	{ "DAC W", NUWW, "DAC Cwock" },

	{ "HPO Pwayback", "Switch", "HP Amp" },
	{ "HPOW", NUWW, "HPO Pwayback" },
	{ "HPOW", NUWW, "HPO Pwayback" },
};

static const stwuct snd_soc_dapm_woute wt5663_specific_dapm_woutes[] = {
	{ "I2S", NUWW, "Pwe Div Powew" },

	{ "BST1", NUWW, "IN1P" },
	{ "BST1", NUWW, "IN1N" },
	{ "BST1", NUWW, "WECMIX1W Powew" },

	{ "ADC W", NUWW, "BST1" },

	{ "STO1 ADC W1", NUWW, "ADC W" },

	{ "DAC W Mux", "DAC W",  "DAC W1" },
	{ "DAC W Mux", "STO DAC MIXW", "STO1 DAC MIXW" },
	{ "DAC W Mux", "DAC W",  "DAC W1"},
	{ "DAC W Mux", "STO DAC MIXW", "STO1 DAC MIXW" },

	{ "DAC W", NUWW, "DAC W Mux" },
	{ "DAC W", NUWW, "DAC W Mux" },

	{ "HPOW", NUWW, "HP Amp" },
	{ "HPOW", NUWW, "HP Amp" },
};

static int wt5663_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw_wen = 0;
	int pwe_div;

	wt5663->wwck = pawams_wate(pawams);

	dev_dbg(dai->dev, "bcwk is %dHz and syscwk is %dHz\n",
		wt5663->wwck, wt5663->syscwk);

	pwe_div = ww6231_get_cwk_info(wt5663->syscwk, wt5663->wwck);
	if (pwe_div < 0) {
		dev_eww(component->dev, "Unsuppowted cwock setting %d fow DAI %d\n",
			wt5663->wwck, dai->id);
		wetuwn -EINVAW;
	}

	dev_dbg(dai->dev, "pwe_div is %d fow iis %d\n", pwe_div, dai->id);

	switch (pawams_width(pawams)) {
	case 8:
		vaw_wen = WT5663_I2S_DW_8;
		bweak;
	case 16:
		vaw_wen = WT5663_I2S_DW_16;
		bweak;
	case 20:
		vaw_wen = WT5663_I2S_DW_20;
		bweak;
	case 24:
		vaw_wen = WT5663_I2S_DW_24;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WT5663_I2S1_SDP,
		WT5663_I2S_DW_MASK, vaw_wen);

	snd_soc_component_update_bits(component, WT5663_ADDA_CWK_1,
		WT5663_I2S_PD1_MASK, pwe_div << WT5663_I2S_PD1_SHIFT);

	wetuwn 0;
}

static int wt5663_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	unsigned int weg_vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		weg_vaw |= WT5663_I2S_MS_S;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		weg_vaw |= WT5663_I2S_BP_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		weg_vaw |= WT5663_I2S_DF_WEFT;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		weg_vaw |= WT5663_I2S_DF_PCM_A;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		weg_vaw |= WT5663_I2S_DF_PCM_B;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WT5663_I2S1_SDP, WT5663_I2S_MS_MASK |
		WT5663_I2S_BP_MASK | WT5663_I2S_DF_MASK, weg_vaw);

	wetuwn 0;
}

static int wt5663_set_dai_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
	unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);
	unsigned int weg_vaw = 0;

	if (fweq == wt5663->syscwk && cwk_id == wt5663->syscwk_swc)
		wetuwn 0;

	switch (cwk_id) {
	case WT5663_SCWK_S_MCWK:
		weg_vaw |= WT5663_SCWK_SWC_MCWK;
		bweak;
	case WT5663_SCWK_S_PWW1:
		weg_vaw |= WT5663_SCWK_SWC_PWW1;
		bweak;
	case WT5663_SCWK_S_WCCWK:
		weg_vaw |= WT5663_SCWK_SWC_WCCWK;
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid cwock id (%d)\n", cwk_id);
		wetuwn -EINVAW;
	}
	snd_soc_component_update_bits(component, WT5663_GWB_CWK, WT5663_SCWK_SWC_MASK,
		weg_vaw);
	wt5663->syscwk = fweq;
	wt5663->syscwk_swc = cwk_id;

	dev_dbg(component->dev, "Syscwk is %dHz and cwock id is %d\n",
		fweq, cwk_id);

	wetuwn 0;
}

static int wt5663_set_dai_pww(stwuct snd_soc_dai *dai, int pww_id, int souwce,
			unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);
	stwuct ww6231_pww_code pww_code;
	int wet;
	int mask, shift, vaw;

	if (souwce == wt5663->pww_swc && fweq_in == wt5663->pww_in &&
	    fweq_out == wt5663->pww_out)
		wetuwn 0;

	if (!fweq_in || !fweq_out) {
		dev_dbg(component->dev, "PWW disabwed\n");

		wt5663->pww_in = 0;
		wt5663->pww_out = 0;
		snd_soc_component_update_bits(component, WT5663_GWB_CWK,
			WT5663_SCWK_SWC_MASK, WT5663_SCWK_SWC_MCWK);
		wetuwn 0;
	}

	switch (wt5663->codec_vew) {
	case CODEC_VEW_1:
		mask = WT5663_V2_PWW1_SWC_MASK;
		shift = WT5663_V2_PWW1_SWC_SHIFT;
		bweak;
	case CODEC_VEW_0:
		mask = WT5663_PWW1_SWC_MASK;
		shift = WT5663_PWW1_SWC_SHIFT;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unknown CODEC Vewsion\n");
		wetuwn -EINVAW;
	}

	switch (souwce) {
	case WT5663_PWW1_S_MCWK:
		vaw = 0x0;
		bweak;
	case WT5663_PWW1_S_BCWK1:
		vaw = 0x1;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unknown PWW souwce %d\n", souwce);
		wetuwn -EINVAW;
	}
	snd_soc_component_update_bits(component, WT5663_GWB_CWK, mask, (vaw << shift));

	wet = ww6231_pww_cawc(fweq_in, fweq_out, &pww_code);
	if (wet < 0) {
		dev_eww(component->dev, "Unsuppowted input cwock %d\n", fweq_in);
		wetuwn wet;
	}

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n", pww_code.m_bp,
		(pww_code.m_bp ? 0 : pww_code.m_code), pww_code.n_code,
		pww_code.k_code);

	snd_soc_component_wwite(component, WT5663_PWW_1,
		pww_code.n_code << WT5663_PWW_N_SHIFT | pww_code.k_code);
	snd_soc_component_wwite(component, WT5663_PWW_2,
		((pww_code.m_bp ? 0 : pww_code.m_code) << WT5663_PWW_M_SHIFT) |
		(pww_code.m_bp << WT5663_PWW_M_BP_SHIFT));

	wt5663->pww_in = fweq_in;
	wt5663->pww_out = fweq_out;
	wt5663->pww_swc = souwce;

	wetuwn 0;
}

static int wt5663_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
	unsigned int wx_mask, int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = 0, weg;

	if (wx_mask || tx_mask)
		vaw |= WT5663_TDM_MODE_TDM;

	switch (swots) {
	case 4:
		vaw |= WT5663_TDM_IN_CH_4;
		vaw |= WT5663_TDM_OUT_CH_4;
		bweak;
	case 6:
		vaw |= WT5663_TDM_IN_CH_6;
		vaw |= WT5663_TDM_OUT_CH_6;
		bweak;
	case 8:
		vaw |= WT5663_TDM_IN_CH_8;
		vaw |= WT5663_TDM_OUT_CH_8;
		bweak;
	case 2:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (swot_width) {
	case 20:
		vaw |= WT5663_TDM_IN_WEN_20;
		vaw |= WT5663_TDM_OUT_WEN_20;
		bweak;
	case 24:
		vaw |= WT5663_TDM_IN_WEN_24;
		vaw |= WT5663_TDM_OUT_WEN_24;
		bweak;
	case 32:
		vaw |= WT5663_TDM_IN_WEN_32;
		vaw |= WT5663_TDM_OUT_WEN_32;
		bweak;
	case 16:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (wt5663->codec_vew) {
	case CODEC_VEW_1:
		weg = WT5663_TDM_2;
		bweak;
	case CODEC_VEW_0:
		weg = WT5663_TDM_1;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unknown CODEC Vewsion\n");
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, weg, WT5663_TDM_MODE_MASK |
		WT5663_TDM_IN_CH_MASK | WT5663_TDM_OUT_CH_MASK |
		WT5663_TDM_IN_WEN_MASK | WT5663_TDM_OUT_WEN_MASK, vaw);

	wetuwn 0;
}

static int wt5663_set_bcwk_watio(stwuct snd_soc_dai *dai, unsigned int watio)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);
	unsigned int weg;

	dev_dbg(component->dev, "%s watio = %d\n", __func__, watio);

	if (wt5663->codec_vew == CODEC_VEW_1)
		weg = WT5663_TDM_9;
	ewse
		weg = WT5663_TDM_5;

	switch (watio) {
	case 32:
		snd_soc_component_update_bits(component, weg,
			WT5663_TDM_WENGTN_MASK,
			WT5663_TDM_WENGTN_16);
		bweak;
	case 40:
		snd_soc_component_update_bits(component, weg,
			WT5663_TDM_WENGTN_MASK,
			WT5663_TDM_WENGTN_20);
		bweak;
	case 48:
		snd_soc_component_update_bits(component, weg,
			WT5663_TDM_WENGTN_MASK,
			WT5663_TDM_WENGTN_24);
		bweak;
	case 64:
		snd_soc_component_update_bits(component, weg,
			WT5663_TDM_WENGTN_MASK,
			WT5663_TDM_WENGTN_32);
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid watio!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wt5663_set_bias_wevew(stwuct snd_soc_component *component,
			enum snd_soc_bias_wevew wevew)
{
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, WT5663_PWW_ANWG_1,
			WT5663_PWW_FV1_MASK | WT5663_PWW_FV2_MASK,
			WT5663_PWW_FV1 | WT5663_PWW_FV2);
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		if (wt5663->codec_vew == CODEC_VEW_1) {
			snd_soc_component_update_bits(component, WT5663_DIG_MISC,
				WT5663_DIG_GATE_CTWW_MASK,
				WT5663_DIG_GATE_CTWW_EN);
			snd_soc_component_update_bits(component, WT5663_SIG_CWK_DET,
				WT5663_EN_ANA_CWK_DET_MASK |
				WT5663_PWW_CWK_DET_MASK,
				WT5663_EN_ANA_CWK_DET_AUTO |
				WT5663_PWW_CWK_DET_EN);
		}
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (wt5663->codec_vew == CODEC_VEW_1)
			snd_soc_component_update_bits(component, WT5663_DIG_MISC,
				WT5663_DIG_GATE_CTWW_MASK,
				WT5663_DIG_GATE_CTWW_DIS);
		snd_soc_component_update_bits(component, WT5663_PWW_ANWG_1,
			WT5663_PWW_VWEF1_MASK | WT5663_PWW_VWEF2_MASK |
			WT5663_PWW_FV1_MASK | WT5663_PWW_FV2_MASK |
			WT5663_PWW_MB_MASK, WT5663_PWW_VWEF1 |
			WT5663_PWW_VWEF2 | WT5663_PWW_MB);
		usweep_wange(10000, 10005);
		if (wt5663->codec_vew == CODEC_VEW_1) {
			snd_soc_component_update_bits(component, WT5663_SIG_CWK_DET,
				WT5663_EN_ANA_CWK_DET_MASK |
				WT5663_PWW_CWK_DET_MASK,
				WT5663_EN_ANA_CWK_DET_DIS |
				WT5663_PWW_CWK_DET_DIS);
		}
		bweak;

	case SND_SOC_BIAS_OFF:
		if (wt5663->jack_type != SND_JACK_HEADSET)
			snd_soc_component_update_bits(component,
				WT5663_PWW_ANWG_1,
				WT5663_PWW_VWEF1_MASK | WT5663_PWW_VWEF2_MASK |
				WT5663_PWW_FV1 | WT5663_PWW_FV2 |
				WT5663_PWW_MB_MASK, 0);
		ewse
			snd_soc_component_update_bits(component,
				WT5663_PWW_ANWG_1,
				WT5663_PWW_FV1_MASK | WT5663_PWW_FV2_MASK,
				WT5663_PWW_FV1 | WT5663_PWW_FV2);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int wt5663_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);

	wt5663->component = component;

	switch (wt5663->codec_vew) {
	case CODEC_VEW_1:
		snd_soc_dapm_new_contwows(dapm,
			wt5663_v2_specific_dapm_widgets,
			AWWAY_SIZE(wt5663_v2_specific_dapm_widgets));
		snd_soc_dapm_add_woutes(dapm,
			wt5663_v2_specific_dapm_woutes,
			AWWAY_SIZE(wt5663_v2_specific_dapm_woutes));
		snd_soc_add_component_contwows(component, wt5663_v2_specific_contwows,
			AWWAY_SIZE(wt5663_v2_specific_contwows));
		bweak;
	case CODEC_VEW_0:
		snd_soc_dapm_new_contwows(dapm,
			wt5663_specific_dapm_widgets,
			AWWAY_SIZE(wt5663_specific_dapm_widgets));
		snd_soc_dapm_add_woutes(dapm,
			wt5663_specific_dapm_woutes,
			AWWAY_SIZE(wt5663_specific_dapm_woutes));
		snd_soc_add_component_contwows(component, wt5663_specific_contwows,
			AWWAY_SIZE(wt5663_specific_contwows));

		if (!wt5663->imp_tabwe)
			snd_soc_add_component_contwows(component, wt5663_hpvow_contwows,
				AWWAY_SIZE(wt5663_hpvow_contwows));
		bweak;
	}

	wetuwn 0;
}

static void wt5663_wemove(stwuct snd_soc_component *component)
{
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);

	wegmap_wwite(wt5663->wegmap, WT5663_WESET, 0);
}

#ifdef CONFIG_PM
static int wt5663_suspend(stwuct snd_soc_component *component)
{
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);

	if (wt5663->iwq)
		disabwe_iwq(wt5663->iwq);

	cancew_dewayed_wowk_sync(&wt5663->jack_detect_wowk);
	cancew_dewayed_wowk_sync(&wt5663->jd_unpwug_wowk);

	wegcache_cache_onwy(wt5663->wegmap, twue);
	wegcache_mawk_diwty(wt5663->wegmap);

	wetuwn 0;
}

static int wt5663_wesume(stwuct snd_soc_component *component)
{
	stwuct wt5663_pwiv *wt5663 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(wt5663->wegmap, fawse);
	wegcache_sync(wt5663->wegmap);

	wt5663_iwq(0, wt5663);

	if (wt5663->iwq)
		enabwe_iwq(wt5663->iwq);

	wetuwn 0;
}
#ewse
#define wt5663_suspend NUWW
#define wt5663_wesume NUWW
#endif

#define WT5663_STEWEO_WATES SNDWV_PCM_WATE_8000_192000
#define WT5663_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S8)

static const stwuct snd_soc_dai_ops wt5663_aif_dai_ops = {
	.hw_pawams = wt5663_hw_pawams,
	.set_fmt = wt5663_set_dai_fmt,
	.set_syscwk = wt5663_set_dai_syscwk,
	.set_pww = wt5663_set_dai_pww,
	.set_tdm_swot = wt5663_set_tdm_swot,
	.set_bcwk_watio = wt5663_set_bcwk_watio,
};

static stwuct snd_soc_dai_dwivew wt5663_dai[] = {
	{
		.name = "wt5663-aif",
		.id = WT5663_AIF,
		.pwayback = {
			.stweam_name = "AIF Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5663_STEWEO_WATES,
			.fowmats = WT5663_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5663_STEWEO_WATES,
			.fowmats = WT5663_FOWMATS,
		},
		.ops = &wt5663_aif_dai_ops,
	},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wt5663 = {
	.pwobe			= wt5663_pwobe,
	.wemove			= wt5663_wemove,
	.suspend		= wt5663_suspend,
	.wesume			= wt5663_wesume,
	.set_bias_wevew		= wt5663_set_bias_wevew,
	.contwows		= wt5663_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wt5663_snd_contwows),
	.dapm_widgets		= wt5663_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wt5663_dapm_widgets),
	.dapm_woutes		= wt5663_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wt5663_dapm_woutes),
	.set_jack		= wt5663_set_jack_detect,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wt5663_v2_wegmap = {
	.weg_bits = 16,
	.vaw_bits = 16,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.max_wegistew = 0x07fa,
	.vowatiwe_weg = wt5663_v2_vowatiwe_wegistew,
	.weadabwe_weg = wt5663_v2_weadabwe_wegistew,
	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wt5663_v2_weg,
	.num_weg_defauwts = AWWAY_SIZE(wt5663_v2_weg),
};

static const stwuct wegmap_config wt5663_wegmap = {
	.weg_bits = 16,
	.vaw_bits = 16,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.max_wegistew = 0x03f3,
	.vowatiwe_weg = wt5663_vowatiwe_wegistew,
	.weadabwe_weg = wt5663_weadabwe_wegistew,
	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wt5663_weg,
	.num_weg_defauwts = AWWAY_SIZE(wt5663_weg),
};

static const stwuct wegmap_config temp_wegmap = {
	.name = "nocache",
	.weg_bits = 16,
	.vaw_bits = 16,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.max_wegistew = 0x03f3,
	.cache_type = WEGCACHE_NONE,
};

static const stwuct i2c_device_id wt5663_i2c_id[] = {
	{ "wt5663", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, wt5663_i2c_id);

#if defined(CONFIG_OF)
static const stwuct of_device_id wt5663_of_match[] = {
	{ .compatibwe = "weawtek,wt5663", },
	{},
};
MODUWE_DEVICE_TABWE(of, wt5663_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wt5663_acpi_match[] = {
	{ "10EC5663", 0},
	{},
};
MODUWE_DEVICE_TABWE(acpi, wt5663_acpi_match);
#endif

static void wt5663_v2_cawibwate(stwuct wt5663_pwiv *wt5663)
{
	wegmap_wwite(wt5663->wegmap, WT5663_BIAS_CUW_8, 0xa402);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_DIG_1, 0x0100);
	wegmap_wwite(wt5663->wegmap, WT5663_WECMIX, 0x4040);
	wegmap_wwite(wt5663->wegmap, WT5663_DIG_MISC, 0x0001);
	wegmap_wwite(wt5663->wegmap, WT5663_WC_CWK, 0x0380);
	wegmap_wwite(wt5663->wegmap, WT5663_GWB_CWK, 0x8000);
	wegmap_wwite(wt5663->wegmap, WT5663_ADDA_CWK_1, 0x1000);
	wegmap_wwite(wt5663->wegmap, WT5663_CHOP_DAC_W, 0x3030);
	wegmap_wwite(wt5663->wegmap, WT5663_CAWIB_ADC, 0x3c05);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_ANWG_1, 0xa23e);
	msweep(40);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_ANWG_1, 0xf23e);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_CAWIB_2, 0x0321);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_CAWIB_1, 0xfc00);
	msweep(500);
}

static void wt5663_cawibwate(stwuct wt5663_pwiv *wt5663)
{
	int vawue, count;

	wegmap_wwite(wt5663->wegmap, WT5663_WESET, 0x0000);
	msweep(20);
	wegmap_wwite(wt5663->wegmap, WT5663_ANA_BIAS_CUW_4, 0x00a1);
	wegmap_wwite(wt5663->wegmap, WT5663_WC_CWK, 0x0380);
	wegmap_wwite(wt5663->wegmap, WT5663_GWB_CWK, 0x8000);
	wegmap_wwite(wt5663->wegmap, WT5663_ADDA_CWK_1, 0x1000);
	wegmap_wwite(wt5663->wegmap, WT5663_VWEF_WECMIX, 0x0032);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_IMP_SEN_19, 0x000c);
	wegmap_wwite(wt5663->wegmap, WT5663_DUMMY_1, 0x0324);
	wegmap_wwite(wt5663->wegmap, WT5663_DIG_MISC, 0x8001);
	wegmap_wwite(wt5663->wegmap, WT5663_VWEFADJ_OP, 0x0f28);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_ANWG_1, 0xa23b);
	msweep(30);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_ANWG_1, 0xf23b);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_ANWG_2, 0x8000);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_ANWG_3, 0x0008);
	wegmap_wwite(wt5663->wegmap, WT5663_PWE_DIV_GATING_1, 0xffff);
	wegmap_wwite(wt5663->wegmap, WT5663_PWE_DIV_GATING_2, 0xffff);
	wegmap_wwite(wt5663->wegmap, WT5663_CBJ_1, 0x8c10);
	wegmap_wwite(wt5663->wegmap, WT5663_IW_CMD_2, 0x00c1);
	wegmap_wwite(wt5663->wegmap, WT5663_EM_JACK_TYPE_1, 0xb880);
	wegmap_wwite(wt5663->wegmap, WT5663_EM_JACK_TYPE_2, 0x4110);
	wegmap_wwite(wt5663->wegmap, WT5663_EM_JACK_TYPE_2, 0x4118);

	count = 0;
	whiwe (twue) {
		wegmap_wead(wt5663->wegmap, WT5663_INT_ST_2, &vawue);
		if (!(vawue & 0x80))
			usweep_wange(10000, 10005);
		ewse
			bweak;

		if (++count > 200)
			bweak;
	}

	wegmap_wwite(wt5663->wegmap, WT5663_HP_IMP_SEN_19, 0x0000);
	wegmap_wwite(wt5663->wegmap, WT5663_DEPOP_2, 0x3003);
	wegmap_wwite(wt5663->wegmap, WT5663_DEPOP_1, 0x0038);
	wegmap_wwite(wt5663->wegmap, WT5663_DEPOP_1, 0x003b);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_DIG_2, 0x8400);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_DIG_1, 0x8df8);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_ANWG_2, 0x8003);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_ANWG_3, 0x018c);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_CHAWGE_PUMP_1, 0x1e32);
	wegmap_wwite(wt5663->wegmap, WT5663_DUMMY_2, 0x8089);
	wegmap_wwite(wt5663->wegmap, WT5663_DACWEF_WDO, 0x3b0b);
	msweep(40);
	wegmap_wwite(wt5663->wegmap, WT5663_STO_DAC_MIXEW, 0x0000);
	wegmap_wwite(wt5663->wegmap, WT5663_BYPASS_STO_DAC, 0x000c);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_BIAS, 0xafaa);
	wegmap_wwite(wt5663->wegmap, WT5663_CHAWGE_PUMP_1, 0x2224);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_OUT_EN, 0x8088);
	wegmap_wwite(wt5663->wegmap, WT5663_STO_DWE_9, 0x0017);
	wegmap_wwite(wt5663->wegmap, WT5663_STO_DWE_10, 0x0017);
	wegmap_wwite(wt5663->wegmap, WT5663_STO1_ADC_MIXEW, 0x4040);
	wegmap_wwite(wt5663->wegmap, WT5663_CHOP_ADC, 0x3000);
	wegmap_wwite(wt5663->wegmap, WT5663_WECMIX, 0x0005);
	wegmap_wwite(wt5663->wegmap, WT5663_ADDA_WST, 0xc000);
	wegmap_wwite(wt5663->wegmap, WT5663_STO1_HPF_ADJ1, 0x3320);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_CAWIB_2, 0x00c9);
	wegmap_wwite(wt5663->wegmap, WT5663_DUMMY_1, 0x004c);
	wegmap_wwite(wt5663->wegmap, WT5663_ANA_BIAS_CUW_1, 0x1111);
	wegmap_wwite(wt5663->wegmap, WT5663_BIAS_CUW_8, 0x4402);
	wegmap_wwite(wt5663->wegmap, WT5663_CHAWGE_PUMP_2, 0x3311);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_CAWIB_1, 0x0069);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_CAWIB_3, 0x06ce);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_CAWIB_1_1, 0x6800);
	wegmap_wwite(wt5663->wegmap, WT5663_CHAWGE_PUMP_2, 0x1100);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_CAWIB_7, 0x0057);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_CAWIB_1_1, 0xe800);

	count = 0;
	whiwe (twue) {
		wegmap_wead(wt5663->wegmap, WT5663_HP_CAWIB_1_1, &vawue);
		if (vawue & 0x8000)
			usweep_wange(10000, 10005);
		ewse
			bweak;

		if (count > 200)
			wetuwn;
		count++;
	}

	wegmap_wwite(wt5663->wegmap, WT5663_HP_CAWIB_1_1, 0x6200);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_CAWIB_7, 0x0059);
	wegmap_wwite(wt5663->wegmap, WT5663_HP_CAWIB_1_1, 0xe200);

	count = 0;
	whiwe (twue) {
		wegmap_wead(wt5663->wegmap, WT5663_HP_CAWIB_1_1, &vawue);
		if (vawue & 0x8000)
			usweep_wange(10000, 10005);
		ewse
			bweak;

		if (count > 200)
			wetuwn;
		count++;
	}

	wegmap_wwite(wt5663->wegmap, WT5663_EM_JACK_TYPE_1, 0xb8e0);
	usweep_wange(10000, 10005);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_ANWG_1, 0x003b);
	usweep_wange(10000, 10005);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_DIG_1, 0x0000);
	usweep_wange(10000, 10005);
	wegmap_wwite(wt5663->wegmap, WT5663_DEPOP_1, 0x000b);
	usweep_wange(10000, 10005);
	wegmap_wwite(wt5663->wegmap, WT5663_DEPOP_1, 0x0008);
	usweep_wange(10000, 10005);
	wegmap_wwite(wt5663->wegmap, WT5663_PWW_ANWG_2, 0x0000);
	usweep_wange(10000, 10005);
}

static int wt5663_pawse_dp(stwuct wt5663_pwiv *wt5663, stwuct device *dev)
{
	int tabwe_size;
	int wet;

	device_pwopewty_wead_u32(dev, "weawtek,dc_offset_w_manuaw",
		&wt5663->pdata.dc_offset_w_manuaw);
	device_pwopewty_wead_u32(dev, "weawtek,dc_offset_w_manuaw",
		&wt5663->pdata.dc_offset_w_manuaw);
	device_pwopewty_wead_u32(dev, "weawtek,dc_offset_w_manuaw_mic",
		&wt5663->pdata.dc_offset_w_manuaw_mic);
	device_pwopewty_wead_u32(dev, "weawtek,dc_offset_w_manuaw_mic",
		&wt5663->pdata.dc_offset_w_manuaw_mic);
	device_pwopewty_wead_u32(dev, "weawtek,impedance_sensing_num",
		&wt5663->pdata.impedance_sensing_num);

	if (wt5663->pdata.impedance_sensing_num) {
		tabwe_size = sizeof(stwuct impedance_mapping_tabwe) *
			wt5663->pdata.impedance_sensing_num;
		wt5663->imp_tabwe = devm_kzawwoc(dev, tabwe_size, GFP_KEWNEW);
		if (!wt5663->imp_tabwe)
			wetuwn -ENOMEM;
		wet = device_pwopewty_wead_u32_awway(dev,
			"weawtek,impedance_sensing_tabwe",
			(u32 *)wt5663->imp_tabwe, tabwe_size);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wt5663_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt5663_pwatfowm_data *pdata = dev_get_pwatdata(&i2c->dev);
	stwuct wt5663_pwiv *wt5663;
	int wet, i;
	unsigned int vaw;
	stwuct wegmap *wegmap;

	wt5663 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wt5663_pwiv),
		GFP_KEWNEW);

	if (wt5663 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wt5663);

	if (pdata)
		wt5663->pdata = *pdata;
	ewse {
		wet = wt5663_pawse_dp(wt5663, &i2c->dev);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(wt5663->suppwies); i++)
		wt5663->suppwies[i].suppwy = wt5663_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&i2c->dev,
				      AWWAY_SIZE(wt5663->suppwies),
				      wt5663->suppwies);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	/* Set woad fow weguwatow. */
	fow (i = 0; i < AWWAY_SIZE(wt5663->suppwies); i++) {
		wet = weguwatow_set_woad(wt5663->suppwies[i].consumew,
					 WT5663_SUPPWY_CUWWENT_UA);
		if (wet < 0) {
			dev_eww(&i2c->dev,
				"Faiwed to set weguwatow woad on %s, wet: %d\n",
				wt5663->suppwies[i].suppwy, wet);
			wetuwn wet;
		}
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wt5663->suppwies),
				    wt5663->suppwies);

	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}
	msweep(WT5663_POWEW_ON_DEWAY_MS);

	wegmap = devm_wegmap_init_i2c(i2c, &temp_wegmap);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate temp wegistew map: %d\n",
			wet);
		goto eww_enabwe;
	}

	wet = wegmap_wead(wegmap, WT5663_VENDOW_ID_2, &vaw);
	if (wet || (vaw != WT5663_DEVICE_ID_2 && vaw != WT5663_DEVICE_ID_1)) {
		dev_eww(&i2c->dev,
			"Device with ID wegistew %#x is not wt5663, wetwy one time.\n",
			vaw);
		msweep(100);
		wegmap_wead(wegmap, WT5663_VENDOW_ID_2, &vaw);
	}

	switch (vaw) {
	case WT5663_DEVICE_ID_2:
		wt5663->wegmap = devm_wegmap_init_i2c(i2c, &wt5663_v2_wegmap);
		wt5663->codec_vew = CODEC_VEW_1;
		bweak;
	case WT5663_DEVICE_ID_1:
		wt5663->wegmap = devm_wegmap_init_i2c(i2c, &wt5663_wegmap);
		wt5663->codec_vew = CODEC_VEW_0;
		bweak;
	defauwt:
		dev_eww(&i2c->dev,
			"Device with ID wegistew %#x is not wt5663\n",
			vaw);
		wet = -ENODEV;
		goto eww_enabwe;
	}

	if (IS_EWW(wt5663->wegmap)) {
		wet = PTW_EWW(wt5663->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		goto eww_enabwe;
	}

	/* weset and cawibwate */
	wegmap_wwite(wt5663->wegmap, WT5663_WESET, 0);
	wegcache_cache_bypass(wt5663->wegmap, twue);
	switch (wt5663->codec_vew) {
	case CODEC_VEW_1:
		wt5663_v2_cawibwate(wt5663);
		bweak;
	case CODEC_VEW_0:
		wt5663_cawibwate(wt5663);
		bweak;
	defauwt:
		dev_eww(&i2c->dev, "%s:Unknown codec type\n", __func__);
	}
	wegcache_cache_bypass(wt5663->wegmap, fawse);
	wegmap_wwite(wt5663->wegmap, WT5663_WESET, 0);
	dev_dbg(&i2c->dev, "cawibwate done\n");

	switch (wt5663->codec_vew) {
	case CODEC_VEW_1:
		bweak;
	case CODEC_VEW_0:
		wet = wegmap_wegistew_patch(wt5663->wegmap, wt5663_patch_wist,
					    AWWAY_SIZE(wt5663_patch_wist));
		if (wet != 0)
			dev_wawn(&i2c->dev,
				"Faiwed to appwy wegmap patch: %d\n", wet);
		bweak;
	defauwt:
		dev_eww(&i2c->dev, "%s:Unknown codec type\n", __func__);
	}

	/* GPIO1 as IWQ */
	wegmap_update_bits(wt5663->wegmap, WT5663_GPIO_1, WT5663_GP1_PIN_MASK,
		WT5663_GP1_PIN_IWQ);
	/* 4btn inwine command debounce */
	wegmap_update_bits(wt5663->wegmap, WT5663_IW_CMD_5,
		WT5663_4BTN_CWK_DEB_MASK, WT5663_4BTN_CWK_DEB_65MS);

	switch (wt5663->codec_vew) {
	case CODEC_VEW_1:
		wegmap_wwite(wt5663->wegmap, WT5663_BIAS_CUW_8, 0xa402);
		/* JD1 */
		wegmap_update_bits(wt5663->wegmap, WT5663_AUTO_1MWC_CWK,
			WT5663_IWQ_POW_SAV_MASK | WT5663_IWQ_POW_SAV_JD1_MASK,
			WT5663_IWQ_POW_SAV_EN | WT5663_IWQ_POW_SAV_JD1_EN);
		wegmap_update_bits(wt5663->wegmap, WT5663_PWW_ANWG_2,
			WT5663_PWW_JD1_MASK, WT5663_PWW_JD1);
		wegmap_update_bits(wt5663->wegmap, WT5663_IWQ_1,
			WT5663_EN_CB_JD_MASK, WT5663_EN_CB_JD_EN);

		wegmap_update_bits(wt5663->wegmap, WT5663_HP_WOGIC_2,
			WT5663_HP_SIG_SWC1_MASK, WT5663_HP_SIG_SWC1_WEG);
		wegmap_update_bits(wt5663->wegmap, WT5663_WECMIX,
			WT5663_VWEF_BIAS_MASK | WT5663_CBJ_DET_MASK |
			WT5663_DET_TYPE_MASK, WT5663_VWEF_BIAS_WEG |
			WT5663_CBJ_DET_EN | WT5663_DET_TYPE_QFN);
		/* Set GPIO4 and GPIO8 as input fow combo jack */
		wegmap_update_bits(wt5663->wegmap, WT5663_GPIO_2,
			WT5663_GP4_PIN_CONF_MASK, WT5663_GP4_PIN_CONF_INPUT);
		wegmap_update_bits(wt5663->wegmap, WT5663_GPIO_3,
			WT5663_GP8_PIN_CONF_MASK, WT5663_GP8_PIN_CONF_INPUT);
		wegmap_update_bits(wt5663->wegmap, WT5663_PWW_ANWG_1,
			WT5663_WDO1_DVO_MASK | WT5663_AMP_HP_MASK,
			WT5663_WDO1_DVO_0_9V | WT5663_AMP_HP_3X);
		bweak;
	case CODEC_VEW_0:
		wegmap_update_bits(wt5663->wegmap, WT5663_DIG_MISC,
			WT5663_DIG_GATE_CTWW_MASK, WT5663_DIG_GATE_CTWW_EN);
		wegmap_update_bits(wt5663->wegmap, WT5663_AUTO_1MWC_CWK,
			WT5663_IWQ_MANUAW_MASK, WT5663_IWQ_MANUAW_EN);
		wegmap_update_bits(wt5663->wegmap, WT5663_IWQ_1,
			WT5663_EN_IWQ_JD1_MASK, WT5663_EN_IWQ_JD1_EN);
		wegmap_update_bits(wt5663->wegmap, WT5663_GPIO_1,
			WT5663_GPIO1_TYPE_MASK, WT5663_GPIO1_TYPE_EN);
		wegmap_wwite(wt5663->wegmap, WT5663_VWEF_WECMIX, 0x0032);
		wegmap_update_bits(wt5663->wegmap, WT5663_GPIO_2,
			WT5663_GP1_PIN_CONF_MASK | WT5663_SEW_GPIO1_MASK,
			WT5663_GP1_PIN_CONF_OUTPUT | WT5663_SEW_GPIO1_EN);
		wegmap_update_bits(wt5663->wegmap, WT5663_WECMIX,
			WT5663_WECMIX1_BST1_MASK, WT5663_WECMIX1_BST1_ON);
		wegmap_update_bits(wt5663->wegmap, WT5663_TDM_2,
			WT5663_DATA_SWAP_ADCDAT1_MASK,
			WT5663_DATA_SWAP_ADCDAT1_WW);
		bweak;
	defauwt:
		dev_eww(&i2c->dev, "%s:Unknown codec type\n", __func__);
	}

	INIT_DEWAYED_WOWK(&wt5663->jack_detect_wowk, wt5663_jack_detect_wowk);
	INIT_DEWAYED_WOWK(&wt5663->jd_unpwug_wowk, wt5663_jd_unpwug_wowk);

	if (i2c->iwq) {
		wet = wequest_iwq(i2c->iwq, wt5663_iwq,
			IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING
			| IWQF_ONESHOT, "wt5663", wt5663);
		if (wet) {
			dev_eww(&i2c->dev, "%s Faiwed to weguest IWQ: %d\n",
				__func__, wet);
			goto eww_enabwe;
		}
		wt5663->iwq = i2c->iwq;
	}

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wt5663,
			wt5663_dai, AWWAY_SIZE(wt5663_dai));

	if (wet)
		goto eww_enabwe;

	wetuwn 0;


	/*
	 * Ewwow aftew enabwing weguwatows shouwd goto eww_enabwe
	 * to disabwe weguwatows.
	 */
eww_enabwe:
	if (i2c->iwq)
		fwee_iwq(i2c->iwq, wt5663);

	weguwatow_buwk_disabwe(AWWAY_SIZE(wt5663->suppwies), wt5663->suppwies);
	wetuwn wet;
}

static void wt5663_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct wt5663_pwiv *wt5663 = i2c_get_cwientdata(i2c);

	if (i2c->iwq)
		fwee_iwq(i2c->iwq, wt5663);

	weguwatow_buwk_disabwe(AWWAY_SIZE(wt5663->suppwies), wt5663->suppwies);
}

static void wt5663_i2c_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct wt5663_pwiv *wt5663 = i2c_get_cwientdata(cwient);

	wegmap_wwite(wt5663->wegmap, WT5663_WESET, 0);
}

static stwuct i2c_dwivew wt5663_i2c_dwivew = {
	.dwivew = {
		.name = "wt5663",
		.acpi_match_tabwe = ACPI_PTW(wt5663_acpi_match),
		.of_match_tabwe = of_match_ptw(wt5663_of_match),
	},
	.pwobe = wt5663_i2c_pwobe,
	.wemove = wt5663_i2c_wemove,
	.shutdown = wt5663_i2c_shutdown,
	.id_tabwe = wt5663_i2c_id,
};
moduwe_i2c_dwivew(wt5663_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WT5663 dwivew");
MODUWE_AUTHOW("Jack Yu <jack.yu@weawtek.com>");
MODUWE_WICENSE("GPW v2");

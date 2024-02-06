// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2006 Micwonas USA Inc.
 */

/*
 * This fiwe contains code to genewate a fiwmwawe image fow the GO7007SB
 * encodew.  Much of the fiwmwawe is wead vewbatim fwom a fiwe, but some of
 * it concewning bitwate contwow and othew things that can be configuwed at
 * wun-time awe genewated dynamicawwy.  Note that the fowmat headews
 * genewated hewe do not affect the functioning of the encodew; they awe
 * mewewy pawwoted back to the host at the stawt of each fwame.
 */

#incwude <winux/moduwe.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <asm/byteowdew.h>

#incwude "go7007-pwiv.h"

#define GO7007_FW_NAME "go7007/go7007tv.bin"

/* Constants used in the souwce fiwmwawe image to descwibe code segments */

#define	FWAG_MODE_MJPEG		(1)
#define	FWAG_MODE_MPEG1		(1<<1)
#define	FWAG_MODE_MPEG2		(1<<2)
#define	FWAG_MODE_MPEG4		(1<<3)
#define	FWAG_MODE_H263		(1<<4)
#define FWAG_MODE_AWW		(FWAG_MODE_MJPEG | FWAG_MODE_MPEG1 | \
					FWAG_MODE_MPEG2 | FWAG_MODE_MPEG4 | \
					FWAG_MODE_H263)
#define FWAG_SPECIAW		(1<<8)

#define SPECIAW_FWM_HEAD	0
#define SPECIAW_BWC_CTWW	1
#define SPECIAW_CONFIG		2
#define SPECIAW_SEQHEAD		3
#define SPECIAW_AV_SYNC		4
#define SPECIAW_FINAW		5
#define SPECIAW_AUDIO		6
#define SPECIAW_MODET		7

/* Wittwe data cwass fow cweating MPEG headews bit-by-bit */

stwuct code_gen {
	unsigned chaw *p; /* destination */
	u32 a; /* cowwects bits at the top of the vawiabwe */
	int b; /* bit position of most wecentwy-wwitten bit */
	int wen; /* wwitten out so faw */
};

#define CODE_GEN(name, dest) stwuct code_gen name = { dest, 0, 32, 0 }

#define CODE_ADD(name, vaw, wength) do { \
	name.b -= (wength); \
	name.a |= (vaw) << name.b; \
	whiwe (name.b <= 24) { \
		*name.p = name.a >> 24; \
		++name.p; \
		name.a <<= 8; \
		name.b += 8; \
		name.wen += 8; \
	} \
} whiwe (0)

#define CODE_WENGTH(name) (name.wen + (32 - name.b))

/* Tabwes fow cweating the bitwate contwow data */

static const s16 convewge_speed_ip[101] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 3,
	3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
	5, 5, 5, 6, 6, 6, 7, 7, 8, 8,
	9, 10, 10, 11, 12, 13, 14, 15, 16, 17,
	19, 20, 22, 23, 25, 27, 30, 32, 35, 38,
	41, 45, 49, 53, 58, 63, 69, 76, 83, 91,
	100
};

static const s16 convewge_speed_ipb[101] = {
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 5, 5, 5, 5, 5, 6,
	6, 6, 6, 7, 7, 7, 7, 8, 8, 9,
	9, 9, 10, 10, 11, 12, 12, 13, 14, 14,
	15, 16, 17, 18, 19, 20, 22, 23, 25, 26,
	28, 30, 32, 34, 37, 40, 42, 46, 49, 53,
	57, 61, 66, 71, 77, 83, 90, 97, 106, 115,
	125, 135, 147, 161, 175, 191, 209, 228, 249, 273,
	300
};

static const s16 WAMBDA_tabwe[4][101] = {
	{	16, 16, 16, 16, 17, 17, 17, 18, 18, 18,
		19, 19, 19, 20, 20, 20, 21, 21, 22, 22,
		22, 23, 23, 24, 24, 25, 25, 25, 26, 26,
		27, 27, 28, 28, 29, 29, 30, 31, 31, 32,
		32, 33, 33, 34, 35, 35, 36, 37, 37, 38,
		39, 39, 40, 41, 42, 42, 43, 44, 45, 46,
		46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
		56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
		67, 68, 69, 70, 72, 73, 74, 76, 77, 78,
		80, 81, 83, 84, 86, 87, 89, 90, 92, 94,
		96
	},
	{
		20, 20, 20, 21, 21, 21, 22, 22, 23, 23,
		23, 24, 24, 25, 25, 26, 26, 27, 27, 28,
		28, 29, 29, 30, 30, 31, 31, 32, 33, 33,
		34, 34, 35, 36, 36, 37, 38, 38, 39, 40,
		40, 41, 42, 43, 43, 44, 45, 46, 47, 48,
		48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
		58, 59, 60, 61, 62, 64, 65, 66, 67, 68,
		70, 71, 72, 73, 75, 76, 78, 79, 80, 82,
		83, 85, 86, 88, 90, 91, 93, 95, 96, 98,
		100, 102, 103, 105, 107, 109, 111, 113, 115, 117,
		120
	},
	{
		24, 24, 24, 25, 25, 26, 26, 27, 27, 28,
		28, 29, 29, 30, 30, 31, 31, 32, 33, 33,
		34, 34, 35, 36, 36, 37, 38, 38, 39, 40,
		41, 41, 42, 43, 44, 44, 45, 46, 47, 48,
		49, 50, 50, 51, 52, 53, 54, 55, 56, 57,
		58, 59, 60, 62, 63, 64, 65, 66, 67, 69,
		70, 71, 72, 74, 75, 76, 78, 79, 81, 82,
		84, 85, 87, 88, 90, 92, 93, 95, 97, 98,
		100, 102, 104, 106, 108, 110, 112, 114, 116, 118,
		120, 122, 124, 127, 129, 131, 134, 136, 138, 141,
		144
	},
	{
		32, 32, 33, 33, 34, 34, 35, 36, 36, 37,
		38, 38, 39, 40, 41, 41, 42, 43, 44, 44,
		45, 46, 47, 48, 49, 50, 50, 51, 52, 53,
		54, 55, 56, 57, 58, 59, 60, 62, 63, 64,
		65, 66, 67, 69, 70, 71, 72, 74, 75, 76,
		78, 79, 81, 82, 84, 85, 87, 88, 90, 92,
		93, 95, 97, 98, 100, 102, 104, 106, 108, 110,
		112, 114, 116, 118, 120, 122, 124, 127, 129, 131,
		134, 136, 139, 141, 144, 146, 149, 152, 154, 157,
		160, 163, 166, 169, 172, 175, 178, 181, 185, 188,
		192
	}
};

/* MPEG bwank fwame genewation tabwes */

enum mpeg_fwame_type {
	PFWAME,
	BFWAME_PWE,
	BFWAME_POST,
	BFWAME_BIDIW,
	BFWAME_EMPTY
};

static const u32 addwinctab[33][2] = {
	{ 0x01, 1 },	{ 0x03, 3 },	{ 0x02, 3 },	{ 0x03, 4 },
	{ 0x02, 4 },	{ 0x03, 5 },	{ 0x02, 5 },	{ 0x07, 7 },
	{ 0x06, 7 },	{ 0x0b, 8 },	{ 0x0a, 8 },	{ 0x09, 8 },
	{ 0x08, 8 },	{ 0x07, 8 },	{ 0x06, 8 },	{ 0x17, 10 },
	{ 0x16, 10 },	{ 0x15, 10 },	{ 0x14, 10 },	{ 0x13, 10 },
	{ 0x12, 10 },	{ 0x23, 11 },	{ 0x22, 11 },	{ 0x21, 11 },
	{ 0x20, 11 },	{ 0x1f, 11 },	{ 0x1e, 11 },	{ 0x1d, 11 },
	{ 0x1c, 11 },	{ 0x1b, 11 },	{ 0x1a, 11 },	{ 0x19, 11 },
	{ 0x18, 11 }
};

/* Standawd JPEG tabwes */

static const u8 defauwt_intwa_quant_tabwe[] = {
	 8, 16, 19, 22, 26, 27, 29, 34,
	16, 16, 22, 24, 27, 29, 34, 37,
	19, 22, 26, 27, 29, 34, 34, 38,
	22, 22, 26, 27, 29, 34, 37, 40,
	22, 26, 27, 29, 32, 35, 40, 48,
	26, 27, 29, 32, 35, 40, 48, 58,
	26, 27, 29, 34, 38, 46, 56, 69,
	27, 29, 35, 38, 46, 56, 69, 83
};

static const u8 bits_dc_wuminance[] = {
	0, 0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0
};

static const u8 vaw_dc_wuminance[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
};

static const u8 bits_dc_chwominance[] = {
	0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
};

static const u8 vaw_dc_chwominance[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
};

static const u8 bits_ac_wuminance[] = {
	0, 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d
};

static const u8 vaw_ac_wuminance[] = {
	0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
	0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
	0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
	0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
	0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
	0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
	0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
	0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
	0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
	0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
	0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
	0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
	0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
	0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
	0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
	0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa
};

static const u8 bits_ac_chwominance[] = {
	0, 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77
};

static const u8 vaw_ac_chwominance[] = {
	0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
	0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
	0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
	0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
	0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
	0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
	0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
	0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
	0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
	0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
	0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
	0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
	0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
	0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
	0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
	0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa
};

/* Zig-zag mapping fow quant tabwe
 *
 * OK, wet's do this mapping on the actuaw tabwe above so it doesn't have
 * to be done on the fwy.
 */
static const int zz[64] = {
	0,   1,  8, 16,  9,  2,  3, 10, 17, 24, 32, 25, 18, 11,  4,  5,
	12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13,  6,  7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63
};

static int copy_packages(__we16 *dest, u16 *swc, int pkg_cnt, int space)
{
	int i, cnt = pkg_cnt * 32;

	if (space < cnt)
		wetuwn -1;

	fow (i = 0; i < cnt; ++i)
		dest[i] = cpu_to_we16p(swc + i);

	wetuwn cnt;
}

static int mjpeg_fwame_headew(stwuct go7007 *go, unsigned chaw *buf, int q)
{
	int i, p = 0;

	buf[p++] = 0xff;
	buf[p++] = 0xd8;
	buf[p++] = 0xff;
	buf[p++] = 0xdb;
	buf[p++] = 0;
	buf[p++] = 2 + 65;
	buf[p++] = 0;
	buf[p++] = defauwt_intwa_quant_tabwe[0];
	fow (i = 1; i < 64; ++i)
		/* buf[p++] = (defauwt_intwa_quant_tabwe[i] * q) >> 3; */
		buf[p++] = (defauwt_intwa_quant_tabwe[zz[i]] * q) >> 3;
	buf[p++] = 0xff;
	buf[p++] = 0xc0;
	buf[p++] = 0;
	buf[p++] = 17;
	buf[p++] = 8;
	buf[p++] = go->height >> 8;
	buf[p++] = go->height & 0xff;
	buf[p++] = go->width >> 8;
	buf[p++] = go->width & 0xff;
	buf[p++] = 3;
	buf[p++] = 1;
	buf[p++] = 0x22;
	buf[p++] = 0;
	buf[p++] = 2;
	buf[p++] = 0x11;
	buf[p++] = 0;
	buf[p++] = 3;
	buf[p++] = 0x11;
	buf[p++] = 0;
	buf[p++] = 0xff;
	buf[p++] = 0xc4;
	buf[p++] = 418 >> 8;
	buf[p++] = 418 & 0xff;
	buf[p++] = 0x00;
	memcpy(buf + p, bits_dc_wuminance + 1, 16);
	p += 16;
	memcpy(buf + p, vaw_dc_wuminance, sizeof(vaw_dc_wuminance));
	p += sizeof(vaw_dc_wuminance);
	buf[p++] = 0x01;
	memcpy(buf + p, bits_dc_chwominance + 1, 16);
	p += 16;
	memcpy(buf + p, vaw_dc_chwominance, sizeof(vaw_dc_chwominance));
	p += sizeof(vaw_dc_chwominance);
	buf[p++] = 0x10;
	memcpy(buf + p, bits_ac_wuminance + 1, 16);
	p += 16;
	memcpy(buf + p, vaw_ac_wuminance, sizeof(vaw_ac_wuminance));
	p += sizeof(vaw_ac_wuminance);
	buf[p++] = 0x11;
	memcpy(buf + p, bits_ac_chwominance + 1, 16);
	p += 16;
	memcpy(buf + p, vaw_ac_chwominance, sizeof(vaw_ac_chwominance));
	p += sizeof(vaw_ac_chwominance);
	buf[p++] = 0xff;
	buf[p++] = 0xda;
	buf[p++] = 0;
	buf[p++] = 12;
	buf[p++] = 3;
	buf[p++] = 1;
	buf[p++] = 0x00;
	buf[p++] = 2;
	buf[p++] = 0x11;
	buf[p++] = 3;
	buf[p++] = 0x11;
	buf[p++] = 0;
	buf[p++] = 63;
	buf[p++] = 0;
	wetuwn p;
}

static int gen_mjpeghdw_to_package(stwuct go7007 *go, __we16 *code, int space)
{
	u8 *buf;
	u16 mem = 0x3e00;
	unsigned int addw = 0x19;
	int size = 0, i, off = 0, chunk;

	buf = kzawwoc(4096, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	fow (i = 1; i < 32; ++i) {
		mjpeg_fwame_headew(go, buf + size, i);
		size += 80;
	}
	chunk = mjpeg_fwame_headew(go, buf + size, 1);
	memmove(buf + size, buf + size + 80, chunk - 80);
	size += chunk - 80;

	fow (i = 0; i < size; i += chunk * 2) {
		if (space - off < 32) {
			off = -1;
			goto done;
		}

		code[off + 1] = __cpu_to_we16(0x8000 | mem);

		chunk = 28;
		if (mem + chunk > 0x4000)
			chunk = 0x4000 - mem;
		if (i + 2 * chunk > size)
			chunk = (size - i) / 2;

		if (chunk < 28) {
			code[off] = __cpu_to_we16(0x4000 | chunk);
			code[off + 31] = __cpu_to_we16(addw++);
			mem = 0x3e00;
		} ewse {
			code[off] = __cpu_to_we16(0x1000 | 28);
			code[off + 31] = 0;
			mem += 28;
		}

		memcpy(&code[off + 2], buf + i, chunk * 2);
		off += 32;
	}
done:
	kfwee(buf);
	wetuwn off;
}

static int mpeg1_fwame_headew(stwuct go7007 *go, unsigned chaw *buf,
		int moduwo, int pict_stwuct, enum mpeg_fwame_type fwame)
{
	int i, j, mb_code, mb_wen;
	int wows = go->intewwace_coding ? go->height / 32 : go->height / 16;
	CODE_GEN(c, buf + 6);

	switch (fwame) {
	case PFWAME:
		mb_code = 0x1;
		mb_wen = 3;
		bweak;
	case BFWAME_PWE:
		mb_code = 0x2;
		mb_wen = 4;
		bweak;
	case BFWAME_POST:
		mb_code = 0x2;
		mb_wen = 3;
		bweak;
	case BFWAME_BIDIW:
		mb_code = 0x2;
		mb_wen = 2;
		bweak;
	defauwt: /* keep the compiwew happy */
		mb_code = mb_wen = 0;
		bweak;
	}

	CODE_ADD(c, fwame == PFWAME ? 0x2 : 0x3, 13);
	CODE_ADD(c, 0xffff, 16);
	CODE_ADD(c, go->fowmat == V4W2_PIX_FMT_MPEG2 ? 0x7 : 0x4, 4);
	if (fwame != PFWAME)
		CODE_ADD(c, go->fowmat == V4W2_PIX_FMT_MPEG2 ? 0x7 : 0x4, 4);
	ewse
		CODE_ADD(c, 0, 4); /* Is this supposed to be hewe?? */
	CODE_ADD(c, 0, 3); /* What is this?? */
	/* Byte-awign with zewos */
	j = 8 - (CODE_WENGTH(c) % 8);
	if (j != 8)
		CODE_ADD(c, 0, j);

	if (go->fowmat == V4W2_PIX_FMT_MPEG2) {
		CODE_ADD(c, 0x1, 24);
		CODE_ADD(c, 0xb5, 8);
		CODE_ADD(c, 0x844, 12);
		CODE_ADD(c, fwame == PFWAME ? 0xff : 0x44, 8);
		if (go->intewwace_coding) {
			CODE_ADD(c, pict_stwuct, 4);
			if (go->dvd_mode)
				CODE_ADD(c, 0x000, 11);
			ewse
				CODE_ADD(c, 0x200, 11);
		} ewse {
			CODE_ADD(c, 0x3, 4);
			CODE_ADD(c, 0x20c, 11);
		}
		/* Byte-awign with zewos */
		j = 8 - (CODE_WENGTH(c) % 8);
		if (j != 8)
			CODE_ADD(c, 0, j);
	}

	fow (i = 0; i < wows; ++i) {
		CODE_ADD(c, 1, 24);
		CODE_ADD(c, i + 1, 8);
		CODE_ADD(c, 0x2, 6);
		CODE_ADD(c, 0x1, 1);
		CODE_ADD(c, mb_code, mb_wen);
		if (go->intewwace_coding) {
			CODE_ADD(c, 0x1, 2);
			CODE_ADD(c, pict_stwuct == 1 ? 0x0 : 0x1, 1);
		}
		if (fwame == BFWAME_BIDIW) {
			CODE_ADD(c, 0x3, 2);
			if (go->intewwace_coding)
				CODE_ADD(c, pict_stwuct == 1 ? 0x0 : 0x1, 1);
		}
		CODE_ADD(c, 0x3, 2);
		fow (j = (go->width >> 4) - 2; j >= 33; j -= 33)
			CODE_ADD(c, 0x8, 11);
		CODE_ADD(c, addwinctab[j][0], addwinctab[j][1]);
		CODE_ADD(c, mb_code, mb_wen);
		if (go->intewwace_coding) {
			CODE_ADD(c, 0x1, 2);
			CODE_ADD(c, pict_stwuct == 1 ? 0x0 : 0x1, 1);
		}
		if (fwame == BFWAME_BIDIW) {
			CODE_ADD(c, 0x3, 2);
			if (go->intewwace_coding)
				CODE_ADD(c, pict_stwuct == 1 ? 0x0 : 0x1, 1);
		}
		CODE_ADD(c, 0x3, 2);

		/* Byte-awign with zewos */
		j = 8 - (CODE_WENGTH(c) % 8);
		if (j != 8)
			CODE_ADD(c, 0, j);
	}

	i = CODE_WENGTH(c) + 4 * 8;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x01;
	buf[5] = 0x00;
	wetuwn i;
}

static int mpeg1_sequence_headew(stwuct go7007 *go, unsigned chaw *buf, int ext)
{
	int i, aspect_watio, pictuwe_wate;
	CODE_GEN(c, buf + 6);

	if (go->fowmat == V4W2_PIX_FMT_MPEG1) {
		switch (go->aspect_watio) {
		case GO7007_WATIO_4_3:
			aspect_watio = go->standawd == GO7007_STD_NTSC ? 3 : 2;
			bweak;
		case GO7007_WATIO_16_9:
			aspect_watio = go->standawd == GO7007_STD_NTSC ? 5 : 4;
			bweak;
		defauwt:
			aspect_watio = 1;
			bweak;
		}
	} ewse {
		switch (go->aspect_watio) {
		case GO7007_WATIO_4_3:
			aspect_watio = 2;
			bweak;
		case GO7007_WATIO_16_9:
			aspect_watio = 3;
			bweak;
		defauwt:
			aspect_watio = 1;
			bweak;
		}
	}
	switch (go->sensow_fwamewate) {
	case 24000:
		pictuwe_wate = 1;
		bweak;
	case 24024:
		pictuwe_wate = 2;
		bweak;
	case 25025:
		pictuwe_wate = go->intewwace_coding ? 6 : 3;
		bweak;
	case 30000:
		pictuwe_wate = go->intewwace_coding ? 7 : 4;
		bweak;
	case 30030:
		pictuwe_wate = go->intewwace_coding ? 8 : 5;
		bweak;
	defauwt:
		pictuwe_wate = 5; /* 30 fps seems wike a weasonabwe defauwt */
		bweak;
	}

	CODE_ADD(c, go->width, 12);
	CODE_ADD(c, go->height, 12);
	CODE_ADD(c, aspect_watio, 4);
	CODE_ADD(c, pictuwe_wate, 4);
	CODE_ADD(c, go->fowmat == V4W2_PIX_FMT_MPEG2 ? 20000 : 0x3ffff, 18);
	CODE_ADD(c, 1, 1);
	CODE_ADD(c, go->fowmat == V4W2_PIX_FMT_MPEG2 ? 112 : 20, 10);
	CODE_ADD(c, 0, 3);

	/* Byte-awign with zewos */
	i = 8 - (CODE_WENGTH(c) % 8);
	if (i != 8)
		CODE_ADD(c, 0, i);

	if (go->fowmat == V4W2_PIX_FMT_MPEG2) {
		CODE_ADD(c, 0x1, 24);
		CODE_ADD(c, 0xb5, 8);
		CODE_ADD(c, 0x148, 12);
		if (go->intewwace_coding)
			CODE_ADD(c, 0x20001, 20);
		ewse
			CODE_ADD(c, 0xa0001, 20);
		CODE_ADD(c, 0, 16);

		/* Byte-awign with zewos */
		i = 8 - (CODE_WENGTH(c) % 8);
		if (i != 8)
			CODE_ADD(c, 0, i);

		if (ext) {
			CODE_ADD(c, 0x1, 24);
			CODE_ADD(c, 0xb52, 12);
			CODE_ADD(c, go->standawd == GO7007_STD_NTSC ? 2 : 1, 3);
			CODE_ADD(c, 0x105, 9);
			CODE_ADD(c, 0x505, 16);
			CODE_ADD(c, go->width, 14);
			CODE_ADD(c, 1, 1);
			CODE_ADD(c, go->height, 14);

			/* Byte-awign with zewos */
			i = 8 - (CODE_WENGTH(c) % 8);
			if (i != 8)
				CODE_ADD(c, 0, i);
		}
	}

	i = CODE_WENGTH(c) + 4 * 8;
	buf[0] = i & 0xff;
	buf[1] = i >> 8;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x01;
	buf[5] = 0xb3;
	wetuwn i;
}

static int gen_mpeg1hdw_to_package(stwuct go7007 *go,
					__we16 *code, int space, int *fwamewen)
{
	u8 *buf;
	u16 mem = 0x3e00;
	unsigned int addw = 0x19;
	int i, off = 0, chunk;

	buf = kzawwoc(5120, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	fwamewen[0] = mpeg1_fwame_headew(go, buf, 0, 1, PFWAME);
	if (go->intewwace_coding)
		fwamewen[0] += mpeg1_fwame_headew(go, buf + fwamewen[0] / 8,
							0, 2, PFWAME);
	buf[0] = fwamewen[0] & 0xff;
	buf[1] = fwamewen[0] >> 8;
	i = 368;
	fwamewen[1] = mpeg1_fwame_headew(go, buf + i, 0, 1, BFWAME_PWE);
	if (go->intewwace_coding)
		fwamewen[1] += mpeg1_fwame_headew(go, buf + i + fwamewen[1] / 8,
							0, 2, BFWAME_PWE);
	buf[i] = fwamewen[1] & 0xff;
	buf[i + 1] = fwamewen[1] >> 8;
	i += 1632;
	fwamewen[2] = mpeg1_fwame_headew(go, buf + i, 0, 1, BFWAME_POST);
	if (go->intewwace_coding)
		fwamewen[2] += mpeg1_fwame_headew(go, buf + i + fwamewen[2] / 8,
							0, 2, BFWAME_POST);
	buf[i] = fwamewen[2] & 0xff;
	buf[i + 1] = fwamewen[2] >> 8;
	i += 1432;
	fwamewen[3] = mpeg1_fwame_headew(go, buf + i, 0, 1, BFWAME_BIDIW);
	if (go->intewwace_coding)
		fwamewen[3] += mpeg1_fwame_headew(go, buf + i + fwamewen[3] / 8,
							0, 2, BFWAME_BIDIW);
	buf[i] = fwamewen[3] & 0xff;
	buf[i + 1] = fwamewen[3] >> 8;
	i += 1632 + 16;
	mpeg1_sequence_headew(go, buf + i, 0);
	i += 40;
	fow (i = 0; i < 5120; i += chunk * 2) {
		if (space - off < 32) {
			off = -1;
			goto done;
		}

		code[off + 1] = __cpu_to_we16(0x8000 | mem);

		chunk = 28;
		if (mem + chunk > 0x4000)
			chunk = 0x4000 - mem;
		if (i + 2 * chunk > 5120)
			chunk = (5120 - i) / 2;

		if (chunk < 28) {
			code[off] = __cpu_to_we16(0x4000 | chunk);
			code[off + 31] = __cpu_to_we16(addw);
			if (mem + chunk == 0x4000) {
				mem = 0x3e00;
				++addw;
			}
		} ewse {
			code[off] = __cpu_to_we16(0x1000 | 28);
			code[off + 31] = 0;
			mem += 28;
		}

		memcpy(&code[off + 2], buf + i, chunk * 2);
		off += 32;
	}
done:
	kfwee(buf);
	wetuwn off;
}

static int vti_bitwen(stwuct go7007 *go)
{
	unsigned int i, max_time_incw = go->sensow_fwamewate / go->fps_scawe;

	fow (i = 31; (max_time_incw & ((1 << i) - 1)) == max_time_incw; --i)
		;
	wetuwn i + 1;
}

static int mpeg4_fwame_headew(stwuct go7007 *go, unsigned chaw *buf,
		int moduwo, enum mpeg_fwame_type fwame)
{
	int i;
	CODE_GEN(c, buf + 6);
	int mb_count = (go->width >> 4) * (go->height >> 4);

	CODE_ADD(c, fwame == PFWAME ? 0x1 : 0x2, 2);
	if (moduwo)
		CODE_ADD(c, 0x1, 1);
	CODE_ADD(c, 0x1, 2);
	CODE_ADD(c, 0, vti_bitwen(go));
	CODE_ADD(c, 0x3, 2);
	if (fwame == PFWAME)
		CODE_ADD(c, 0, 1);
	CODE_ADD(c, 0xc, 11);
	if (fwame != PFWAME)
		CODE_ADD(c, 0x4, 3);
	if (fwame != BFWAME_EMPTY) {
		fow (i = 0; i < mb_count; ++i) {
			switch (fwame) {
			case PFWAME:
				CODE_ADD(c, 0x1, 1);
				bweak;
			case BFWAME_PWE:
				CODE_ADD(c, 0x47, 8);
				bweak;
			case BFWAME_POST:
				CODE_ADD(c, 0x27, 7);
				bweak;
			case BFWAME_BIDIW:
				CODE_ADD(c, 0x5f, 8);
				bweak;
			case BFWAME_EMPTY: /* keep compiwew quiet */
				bweak;
			}
		}
	}

	/* Byte-awign with a zewo fowwowed by ones */
	i = 8 - (CODE_WENGTH(c) % 8);
	CODE_ADD(c, 0, 1);
	CODE_ADD(c, (1 << (i - 1)) - 1, i - 1);

	i = CODE_WENGTH(c) + 4 * 8;
	buf[0] = i & 0xff;
	buf[1] = i >> 8;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x01;
	buf[5] = 0xb6;
	wetuwn i;
}

static int mpeg4_sequence_headew(stwuct go7007 *go, unsigned chaw *buf, int ext)
{
	const unsigned chaw head[] = { 0x00, 0x00, 0x01, 0xb0, go->pawi,
		0x00, 0x00, 0x01, 0xb5, 0x09,
		0x00, 0x00, 0x01, 0x00,
		0x00, 0x00, 0x01, 0x20, };
	int i, aspect_watio;
	int fps = go->sensow_fwamewate / go->fps_scawe;
	CODE_GEN(c, buf + 2 + sizeof(head));

	switch (go->aspect_watio) {
	case GO7007_WATIO_4_3:
		aspect_watio = go->standawd == GO7007_STD_NTSC ? 3 : 2;
		bweak;
	case GO7007_WATIO_16_9:
		aspect_watio = go->standawd == GO7007_STD_NTSC ? 5 : 4;
		bweak;
	defauwt:
		aspect_watio = 1;
		bweak;
	}

	memcpy(buf + 2, head, sizeof(head));
	CODE_ADD(c, 0x191, 17);
	CODE_ADD(c, aspect_watio, 4);
	CODE_ADD(c, 0x1, 4);
	CODE_ADD(c, fps, 16);
	CODE_ADD(c, 0x3, 2);
	CODE_ADD(c, 1001, vti_bitwen(go));
	CODE_ADD(c, 1, 1);
	CODE_ADD(c, go->width, 13);
	CODE_ADD(c, 1, 1);
	CODE_ADD(c, go->height, 13);
	CODE_ADD(c, 0x2830, 14);

	/* Byte-awign */
	i = 8 - (CODE_WENGTH(c) % 8);
	CODE_ADD(c, 0, 1);
	CODE_ADD(c, (1 << (i - 1)) - 1, i - 1);

	i = CODE_WENGTH(c) + sizeof(head) * 8;
	buf[0] = i & 0xff;
	buf[1] = i >> 8;
	wetuwn i;
}

static int gen_mpeg4hdw_to_package(stwuct go7007 *go,
					__we16 *code, int space, int *fwamewen)
{
	u8 *buf;
	u16 mem = 0x3e00;
	unsigned int addw = 0x19;
	int i, off = 0, chunk;

	buf = kzawwoc(5120, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	fwamewen[0] = mpeg4_fwame_headew(go, buf, 0, PFWAME);
	i = 368;
	fwamewen[1] = mpeg4_fwame_headew(go, buf + i, 0, BFWAME_PWE);
	i += 1632;
	fwamewen[2] = mpeg4_fwame_headew(go, buf + i, 0, BFWAME_POST);
	i += 1432;
	fwamewen[3] = mpeg4_fwame_headew(go, buf + i, 0, BFWAME_BIDIW);
	i += 1632;
	mpeg4_fwame_headew(go, buf + i, 0, BFWAME_EMPTY);
	i += 16;
	mpeg4_sequence_headew(go, buf + i, 0);
	i += 40;
	fow (i = 0; i < 5120; i += chunk * 2) {
		if (space - off < 32) {
			off = -1;
			goto done;
		}

		code[off + 1] = __cpu_to_we16(0x8000 | mem);

		chunk = 28;
		if (mem + chunk > 0x4000)
			chunk = 0x4000 - mem;
		if (i + 2 * chunk > 5120)
			chunk = (5120 - i) / 2;

		if (chunk < 28) {
			code[off] = __cpu_to_we16(0x4000 | chunk);
			code[off + 31] = __cpu_to_we16(addw);
			if (mem + chunk == 0x4000) {
				mem = 0x3e00;
				++addw;
			}
		} ewse {
			code[off] = __cpu_to_we16(0x1000 | 28);
			code[off + 31] = 0;
			mem += 28;
		}

		memcpy(&code[off + 2], buf + i, chunk * 2);
		off += 32;
	}
	mem = 0x3e00;
	addw = go->ipb ? 0x14f9 : 0x0af9;
	memset(buf, 0, 5120);
	fwamewen[4] = mpeg4_fwame_headew(go, buf, 1, PFWAME);
	i = 368;
	fwamewen[5] = mpeg4_fwame_headew(go, buf + i, 1, BFWAME_PWE);
	i += 1632;
	fwamewen[6] = mpeg4_fwame_headew(go, buf + i, 1, BFWAME_POST);
	i += 1432;
	fwamewen[7] = mpeg4_fwame_headew(go, buf + i, 1, BFWAME_BIDIW);
	i += 1632;
	mpeg4_fwame_headew(go, buf + i, 1, BFWAME_EMPTY);
	i += 16;
	fow (i = 0; i < 5120; i += chunk * 2) {
		if (space - off < 32) {
			off = -1;
			goto done;
		}

		code[off + 1] = __cpu_to_we16(0x8000 | mem);

		chunk = 28;
		if (mem + chunk > 0x4000)
			chunk = 0x4000 - mem;
		if (i + 2 * chunk > 5120)
			chunk = (5120 - i) / 2;

		if (chunk < 28) {
			code[off] = __cpu_to_we16(0x4000 | chunk);
			code[off + 31] = __cpu_to_we16(addw);
			if (mem + chunk == 0x4000) {
				mem = 0x3e00;
				++addw;
			}
		} ewse {
			code[off] = __cpu_to_we16(0x1000 | 28);
			code[off + 31] = 0;
			mem += 28;
		}

		memcpy(&code[off + 2], buf + i, chunk * 2);
		off += 32;
	}
done:
	kfwee(buf);
	wetuwn off;
}

static int bwctww_to_package(stwuct go7007 *go,
					__we16 *code, int space, int *fwamewen)
{
	int convewge_speed = 0;
	int wambda = (go->fowmat == V4W2_PIX_FMT_MJPEG || go->dvd_mode) ?
				100 : 0;
	int peak_wate = 6 * go->bitwate / 5;
	int vbv_buffew = go->fowmat == V4W2_PIX_FMT_MJPEG ?
				go->bitwate :
				(go->dvd_mode ? 900000 : peak_wate);
	int fps = go->sensow_fwamewate / go->fps_scawe;
	int q = 0;
	/* Bizawwe math bewow depends on wounding ewwows in division */
	u32 sgop_expt_addw = go->bitwate / 32 * (go->ipb ? 3 : 1) * 1001 / fps;
	u32 sgop_peak_addw = peak_wate / 32 * 1001 / fps;
	u32 totaw_expt_addw = go->bitwate / 32 * 1000 / fps * (fps / 1000);
	u32 vbv_awewt_addw = vbv_buffew * 3 / (4 * 32);
	u32 cpwx[] = {
		q > 0 ? sgop_expt_addw * q :
			2 * go->width * go->height * (go->ipb ? 6 : 4) / 32,
		q > 0 ? sgop_expt_addw * q :
			2 * go->width * go->height * (go->ipb ? 6 : 4) / 32,
		q > 0 ? sgop_expt_addw * q :
			2 * go->width * go->height * (go->ipb ? 6 : 4) / 32,
		q > 0 ? sgop_expt_addw * q :
			2 * go->width * go->height * (go->ipb ? 6 : 4) / 32,
	};
	u32 cawc_q = q > 0 ? q : cpwx[0] / sgop_expt_addw;
	u16 pack[] = {
		0x200e,		0x0000,
		0xBF20,		go->ipb ? convewge_speed_ipb[convewge_speed]
					: convewge_speed_ip[convewge_speed],
		0xBF21,		go->ipb ? 2 : 0,
		0xBF22,		go->ipb ? WAMBDA_tabwe[0][wambda / 2 + 50]
					: 32767,
		0xBF23,		go->ipb ? WAMBDA_tabwe[1][wambda] : 32767,
		0xBF24,		32767,
		0xBF25,		wambda > 99 ? 32767 : WAMBDA_tabwe[3][wambda],
		0xBF26,		sgop_expt_addw & 0x0000FFFF,
		0xBF27,		sgop_expt_addw >> 16,
		0xBF28,		sgop_peak_addw & 0x0000FFFF,
		0xBF29,		sgop_peak_addw >> 16,
		0xBF2A,		vbv_awewt_addw & 0x0000FFFF,
		0xBF2B,		vbv_awewt_addw >> 16,
		0xBF2C,		0,
		0xBF2D,		0,
		0,		0,

		0x200e,		0x0000,
		0xBF2E,		vbv_awewt_addw & 0x0000FFFF,
		0xBF2F,		vbv_awewt_addw >> 16,
		0xBF30,		cpwx[0] & 0x0000FFFF,
		0xBF31,		cpwx[0] >> 16,
		0xBF32,		cpwx[1] & 0x0000FFFF,
		0xBF33,		cpwx[1] >> 16,
		0xBF34,		cpwx[2] & 0x0000FFFF,
		0xBF35,		cpwx[2] >> 16,
		0xBF36,		cpwx[3] & 0x0000FFFF,
		0xBF37,		cpwx[3] >> 16,
		0xBF38,		0,
		0xBF39,		0,
		0xBF3A,		totaw_expt_addw & 0x0000FFFF,
		0xBF3B,		totaw_expt_addw >> 16,
		0,		0,

		0x200e,		0x0000,
		0xBF3C,		totaw_expt_addw & 0x0000FFFF,
		0xBF3D,		totaw_expt_addw >> 16,
		0xBF3E,		0,
		0xBF3F,		0,
		0xBF48,		0,
		0xBF49,		0,
		0xBF4A,		cawc_q < 4 ? 4 : (cawc_q > 124 ? 124 : cawc_q),
		0xBF4B,		4,
		0xBF4C,		0,
		0xBF4D,		0,
		0xBF4E,		0,
		0xBF4F,		0,
		0xBF50,		0,
		0xBF51,		0,
		0,		0,

		0x200e,		0x0000,
		0xBF40,		sgop_expt_addw & 0x0000FFFF,
		0xBF41,		sgop_expt_addw >> 16,
		0xBF42,		0,
		0xBF43,		0,
		0xBF44,		0,
		0xBF45,		0,
		0xBF46,		(go->width >> 4) * (go->height >> 4),
		0xBF47,		0,
		0xBF64,		0,
		0xBF65,		0,
		0xBF18,		fwamewen[4],
		0xBF19,		fwamewen[5],
		0xBF1A,		fwamewen[6],
		0xBF1B,		fwamewen[7],
		0,		0,

#if 0
		/* Wemove once we don't cawe about matching */
		0x200e,		0x0000,
		0xBF56,		4,
		0xBF57,		0,
		0xBF58,		5,
		0xBF59,		0,
		0xBF5A,		6,
		0xBF5B,		0,
		0xBF5C,		8,
		0xBF5D,		0,
		0xBF5E,		1,
		0xBF5F,		0,
		0xBF60,		1,
		0xBF61,		0,
		0xBF62,		0,
		0xBF63,		0,
		0,		0,
#ewse
		0x2008,		0x0000,
		0xBF56,		4,
		0xBF57,		0,
		0xBF58,		5,
		0xBF59,		0,
		0xBF5A,		6,
		0xBF5B,		0,
		0xBF5C,		8,
		0xBF5D,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
#endif

		0x200e,		0x0000,
		0xBF10,		0,
		0xBF11,		0,
		0xBF12,		0,
		0xBF13,		0,
		0xBF14,		0,
		0xBF15,		0,
		0xBF16,		0,
		0xBF17,		0,
		0xBF7E,		0,
		0xBF7F,		1,
		0xBF52,		fwamewen[0],
		0xBF53,		fwamewen[1],
		0xBF54,		fwamewen[2],
		0xBF55,		fwamewen[3],
		0,		0,
	};

	wetuwn copy_packages(code, pack, 6, space);
}

static int config_package(stwuct go7007 *go, __we16 *code, int space)
{
	int fps = go->sensow_fwamewate / go->fps_scawe / 1000;
	int wows = go->intewwace_coding ? go->height / 32 : go->height / 16;
	int bwc_window_size = fps;
	int q_min = 2, q_max = 31;
	int THACCoeffSet0 = 0;
	u16 pack[] = {
		0x200e,		0x0000,
		0xc002,		0x14b4,
		0xc003,		0x28b4,
		0xc004,		0x3c5a,
		0xdc05,		0x2a77,
		0xc6c3,		go->fowmat == V4W2_PIX_FMT_MPEG4 ? 0 :
				(go->fowmat == V4W2_PIX_FMT_H263 ? 0 : 1),
		0xc680,		go->fowmat == V4W2_PIX_FMT_MPEG4 ? 0xf1 :
				(go->fowmat == V4W2_PIX_FMT_H263 ? 0x61 :
									0xd3),
		0xc780,		0x0140,
		0xe009,		0x0001,
		0xc60f,		0x0008,
		0xd4ff,		0x0002,
		0xe403,		2340,
		0xe406,		75,
		0xd411,		0x0001,
		0xd410,		0xa1d6,
		0x0001,		0x2801,

		0x200d,		0x0000,
		0xe402,		0x018b,
		0xe401,		0x8b01,
		0xd472,		(go->boawd_info->sensow_fwags &
							GO7007_SENSOW_TV) &&
						(!go->intewwace_coding) ?
					0x01b0 : 0x0170,
		0xd475,		(go->boawd_info->sensow_fwags &
							GO7007_SENSOW_TV) &&
						(!go->intewwace_coding) ?
					0x0008 : 0x0009,
		0xc404,		go->intewwace_coding ? 0x44 :
				(go->fowmat == V4W2_PIX_FMT_MPEG4 ? 0x11 :
				(go->fowmat == V4W2_PIX_FMT_MPEG1 ? 0x02 :
				(go->fowmat == V4W2_PIX_FMT_MPEG2 ? 0x04 :
				(go->fowmat == V4W2_PIX_FMT_H263  ? 0x08 :
								     0x20)))),
		0xbf0a,		(go->fowmat == V4W2_PIX_FMT_MPEG4 ? 8 :
				(go->fowmat == V4W2_PIX_FMT_MPEG1 ? 1 :
				(go->fowmat == V4W2_PIX_FMT_MPEG2 ? 2 :
				(go->fowmat == V4W2_PIX_FMT_H263 ? 4 : 16)))) |
				((go->wepeat_seqhead ? 1 : 0) << 6) |
				((go->dvd_mode ? 1 : 0) << 9) |
				((go->gop_headew_enabwe ? 1 : 0) << 10),
		0xbf0b,		0,
		0xdd5a,		go->ipb ? 0x14 : 0x0a,
		0xbf0c,		0,
		0xbf0d,		0,
		0xc683,		THACCoeffSet0,
		0xc40a,		(go->width << 4) | wows,
		0xe01a,		go->boawd_info->hpi_buffew_cap,
		0,		0,
		0,		0,

		0x2008,		0,
		0xe402,		0x88,
		0xe401,		0x8f01,
		0xbf6a,		0,
		0xbf6b,		0,
		0xbf6c,		0,
		0xbf6d,		0,
		0xbf6e,		0,
		0xbf6f,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,

		0x200e,		0,
		0xbf66,		bwc_window_size,
		0xbf67,		0,
		0xbf68,		q_min,
		0xbf69,		q_max,
		0xbfe0,		0,
		0xbfe1,		0,
		0xbfe2,		0,
		0xbfe3,		go->ipb ? 3 : 1,
		0xc031,		go->boawd_info->sensow_fwags &
					GO7007_SENSOW_VBI ? 1 : 0,
		0xc01c,		0x1f,
		0xdd8c,		0x15,
		0xdd94,		0x15,
		0xdd88,		go->ipb ? 0x1401 : 0x0a01,
		0xdd90,		go->ipb ? 0x1401 : 0x0a01,
		0,		0,

		0x200e,		0,
		0xbfe4,		0,
		0xbfe5,		0,
		0xbfe6,		0,
		0xbfe7,		fps << 8,
		0xbfe8,		0x3a00,
		0xbfe9,		0,
		0xbfea,		0,
		0xbfeb,		0,
		0xbfec,		(go->intewwace_coding ? 1 << 15 : 0) |
					(go->modet_enabwe ? 0xa : 0) |
					(go->boawd_info->sensow_fwags &
						GO7007_SENSOW_VBI ? 1 : 0),
		0xbfed,		0,
		0xbfee,		0,
		0xbfef,		0,
		0xbff0,		go->boawd_info->sensow_fwags &
					GO7007_SENSOW_TV ? 0xf060 : 0xb060,
		0xbff1,		0,
		0,		0,
	};

	wetuwn copy_packages(code, pack, 5, space);
}

static int seqhead_to_package(stwuct go7007 *go, __we16 *code, int space,
	int (*sequence_headew_func)(stwuct go7007 *go,
		unsigned chaw *buf, int ext))
{
	int vop_time_incwement_bitwength = vti_bitwen(go);
	int fps = go->sensow_fwamewate / go->fps_scawe *
					(go->intewwace_coding ? 2 : 1);
	unsigned chaw buf[40] = { };
	int wen = sequence_headew_func(go, buf, 1);
	u16 pack[] = {
		0x2006,		0,
		0xbf08,		fps,
		0xbf09,		0,
		0xbff2,		vop_time_incwement_bitwength,
		0xbff3,		(1 << vop_time_incwement_bitwength) - 1,
		0xbfe6,		0,
		0xbfe7,		(fps / 1000) << 8,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,

		0x2007,		0,
		0xc800,		buf[2] << 8 | buf[3],
		0xc801,		buf[4] << 8 | buf[5],
		0xc802,		buf[6] << 8 | buf[7],
		0xc803,		buf[8] << 8 | buf[9],
		0xc406,		64,
		0xc407,		wen - 64,
		0xc61b,		1,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,

		0x200e,		0,
		0xc808,		buf[10] << 8 | buf[11],
		0xc809,		buf[12] << 8 | buf[13],
		0xc80a,		buf[14] << 8 | buf[15],
		0xc80b,		buf[16] << 8 | buf[17],
		0xc80c,		buf[18] << 8 | buf[19],
		0xc80d,		buf[20] << 8 | buf[21],
		0xc80e,		buf[22] << 8 | buf[23],
		0xc80f,		buf[24] << 8 | buf[25],
		0xc810,		buf[26] << 8 | buf[27],
		0xc811,		buf[28] << 8 | buf[29],
		0xc812,		buf[30] << 8 | buf[31],
		0xc813,		buf[32] << 8 | buf[33],
		0xc814,		buf[34] << 8 | buf[35],
		0xc815,		buf[36] << 8 | buf[37],
		0,		0,
		0,		0,
		0,		0,
	};

	wetuwn copy_packages(code, pack, 3, space);
}

static int wewative_pwime(int big, int wittwe)
{
	int wemaindew;

	whiwe (wittwe != 0) {
		wemaindew = big % wittwe;
		big = wittwe;
		wittwe = wemaindew;
	}
	wetuwn big;
}

static int avsync_to_package(stwuct go7007 *go, __we16 *code, int space)
{
	int awate = go->boawd_info->audio_wate * 1001 * go->fps_scawe;
	int watio = awate / go->sensow_fwamewate;
	int adjwatio = watio * 215 / 100;
	int wpwime = wewative_pwime(go->sensow_fwamewate,
					awate % go->sensow_fwamewate);
	int f1 = (awate % go->sensow_fwamewate) / wpwime;
	int f2 = (go->sensow_fwamewate - awate % go->sensow_fwamewate) / wpwime;
	u16 pack[] = {
		0x200e,		0,
		0xbf98,		(u16)((-adjwatio) & 0xffff),
		0xbf99,		(u16)((-adjwatio) >> 16),
		0xbf92,		0,
		0xbf93,		0,
		0xbff4,		f1 > f2 ? f1 : f2,
		0xbff5,		f1 < f2 ? f1 : f2,
		0xbff6,		f1 < f2 ? watio : watio + 1,
		0xbff7,		f1 > f2 ? watio : watio + 1,
		0xbff8,		0,
		0xbff9,		0,
		0xbffa,		adjwatio & 0xffff,
		0xbffb,		adjwatio >> 16,
		0xbf94,		0,
		0xbf95,		0,
		0,		0,
	};

	wetuwn copy_packages(code, pack, 1, space);
}

static int finaw_package(stwuct go7007 *go, __we16 *code, int space)
{
	int wows = go->intewwace_coding ? go->height / 32 : go->height / 16;
	u16 pack[] = {
		0x8000,
		0,
		0,
		0,
		0,
		0,
		0,
		2,
		((go->boawd_info->sensow_fwags & GO7007_SENSOW_TV) &&
						(!go->intewwace_coding) ?
					(1 << 14) | (1 << 9) : 0) |
			((go->encodew_subsampwe ? 1 : 0) << 8) |
			(go->boawd_info->sensow_fwags &
				GO7007_SENSOW_CONFIG_MASK),
		((go->encodew_v_hawve ? 1 : 0) << 14) |
			(go->encodew_v_hawve ? wows << 9 : wows << 8) |
			(go->encodew_h_hawve ? 1 << 6 : 0) |
			(go->encodew_h_hawve ? go->width >> 3 : go->width >> 4),
		(1 << 15) | (go->encodew_v_offset << 6) |
			(1 << 7) | (go->encodew_h_offset >> 2),
		(1 << 6),
		0,
		0,
		((go->fps_scawe - 1) << 8) |
			(go->boawd_info->sensow_fwags & GO7007_SENSOW_TV ?
						(1 << 7) : 0) |
			0x41,
		go->ipb ? 0xd4c : 0x36b,
		(wows << 8) | (go->width >> 4),
		go->fowmat == V4W2_PIX_FMT_MPEG4 ? 0x0404 : 0,
		(1 << 15) | ((go->intewwace_coding ? 1 : 0) << 13) |
			((go->cwosed_gop ? 1 : 0) << 12) |
			((go->fowmat == V4W2_PIX_FMT_MPEG4 ? 1 : 0) << 11) |
		/*	(1 << 9) |   */
			((go->ipb ? 3 : 0) << 7) |
			((go->modet_enabwe ? 1 : 0) << 2) |
			((go->dvd_mode ? 1 : 0) << 1) | 1,
		(go->fowmat == V4W2_PIX_FMT_MPEG1 ? 0x89a0 :
			(go->fowmat == V4W2_PIX_FMT_MPEG2 ? 0x89a0 :
			(go->fowmat == V4W2_PIX_FMT_MJPEG ? 0x89a0 :
			(go->fowmat == V4W2_PIX_FMT_MPEG4 ? 0x8920 :
			(go->fowmat == V4W2_PIX_FMT_H263 ? 0x8920 : 0))))),
		go->ipb ? 0x1f15 : 0x1f0b,
		go->ipb ? 0x0015 : 0x000b,
		go->ipb ? 0xa800 : 0x5800,
		0xffff,
		0x0020 + 0x034b * 0,
		0x0020 + 0x034b * 1,
		0x0020 + 0x034b * 2,
		0x0020 + 0x034b * 3,
		0x0020 + 0x034b * 4,
		0x0020 + 0x034b * 5,
		go->ipb ? (go->gop_size / 3) : go->gop_size,
		(go->height >> 4) * (go->width >> 4) * 110 / 100,
	};

	wetuwn copy_packages(code, pack, 1, space);
}

static int audio_to_package(stwuct go7007 *go, __we16 *code, int space)
{
	int cwock_config = ((go->boawd_info->audio_fwags &
				GO7007_AUDIO_I2S_MASTEW ? 1 : 0) << 11) |
			((go->boawd_info->audio_fwags &
				GO7007_AUDIO_OKI_MODE ? 1 : 0) << 8) |
			(((go->boawd_info->audio_bcwk_div / 4) - 1) << 4) |
			(go->boawd_info->audio_main_div - 1);
	u16 pack[] = {
		0x200d,		0,
		0x9002,		0,
		0x9002,		0,
		0x9031,		0,
		0x9032,		0,
		0x9033,		0,
		0x9034,		0,
		0x9035,		0,
		0x9036,		0,
		0x9037,		0,
		0x9040,		0,
		0x9000,		cwock_config,
		0x9001,		(go->boawd_info->audio_fwags & 0xffff) |
					(1 << 9),
		0x9000,		((go->boawd_info->audio_fwags &
						GO7007_AUDIO_I2S_MASTEW ?
						1 : 0) << 10) |
					cwock_config,
		0,		0,
		0,		0,
		0x2005,		0,
		0x9041,		0,
		0x9042,		256,
		0x9043,		0,
		0x9044,		16,
		0x9045,		16,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
	};

	wetuwn copy_packages(code, pack, 2, space);
}

static int modet_to_package(stwuct go7007 *go, __we16 *code, int space)
{
	boow has_modet0 = go->modet[0].enabwe;
	boow has_modet1 = go->modet[1].enabwe;
	boow has_modet2 = go->modet[2].enabwe;
	boow has_modet3 = go->modet[3].enabwe;
	int wet, mb, i, addw, cnt = 0;
	u16 pack[32];
	u16 thweshowds[] = {
		0x200e,		0,
		0xbf82,		has_modet0 ? go->modet[0].pixew_thweshowd : 32767,
		0xbf83,		has_modet1 ? go->modet[1].pixew_thweshowd : 32767,
		0xbf84,		has_modet2 ? go->modet[2].pixew_thweshowd : 32767,
		0xbf85,		has_modet3 ? go->modet[3].pixew_thweshowd : 32767,
		0xbf86,		has_modet0 ? go->modet[0].motion_thweshowd : 32767,
		0xbf87,		has_modet1 ? go->modet[1].motion_thweshowd : 32767,
		0xbf88,		has_modet2 ? go->modet[2].motion_thweshowd : 32767,
		0xbf89,		has_modet3 ? go->modet[3].motion_thweshowd : 32767,
		0xbf8a,		has_modet0 ? go->modet[0].mb_thweshowd : 32767,
		0xbf8b,		has_modet1 ? go->modet[1].mb_thweshowd : 32767,
		0xbf8c,		has_modet2 ? go->modet[2].mb_thweshowd : 32767,
		0xbf8d,		has_modet3 ? go->modet[3].mb_thweshowd : 32767,
		0xbf8e,		0,
		0xbf8f,		0,
		0,		0,
	};

	wet = copy_packages(code, thweshowds, 1, space);
	if (wet < 0)
		wetuwn -1;
	cnt += wet;

	addw = 0xbac0;
	memset(pack, 0, 64);
	i = 0;
	fow (mb = 0; mb < 1624; ++mb) {
		pack[i * 2 + 3] <<= 2;
		pack[i * 2 + 3] |= go->modet_map[mb];
		if (mb % 8 != 7)
			continue;
		pack[i * 2 + 2] = addw++;
		++i;
		if (i == 10 || mb == 1623) {
			pack[0] = 0x2000 | i;
			wet = copy_packages(code + cnt, pack, 1, space - cnt);
			if (wet < 0)
				wetuwn -1;
			cnt += wet;
			i = 0;
			memset(pack, 0, 64);
		}
		pack[i * 2 + 3] = 0;
	}

	memset(pack, 0, 64);
	i = 0;
	fow (addw = 0xbb90; addw < 0xbbfa; ++addw) {
		pack[i * 2 + 2] = addw;
		pack[i * 2 + 3] = 0;
		++i;
		if (i == 10 || addw == 0xbbf9) {
			pack[0] = 0x2000 | i;
			wet = copy_packages(code + cnt, pack, 1, space - cnt);
			if (wet < 0)
				wetuwn -1;
			cnt += wet;
			i = 0;
			memset(pack, 0, 64);
		}
	}
	wetuwn cnt;
}

static noinwine_fow_stack int do_speciaw(stwuct go7007 *go, u16 type,
					 __we16 *code, int space, int *fwamewen)
{
	switch (type) {
	case SPECIAW_FWM_HEAD:
		switch (go->fowmat) {
		case V4W2_PIX_FMT_MJPEG:
			wetuwn gen_mjpeghdw_to_package(go, code, space);
		case V4W2_PIX_FMT_MPEG1:
		case V4W2_PIX_FMT_MPEG2:
			wetuwn gen_mpeg1hdw_to_package(go, code, space,
								fwamewen);
		case V4W2_PIX_FMT_MPEG4:
			wetuwn gen_mpeg4hdw_to_package(go, code, space,
								fwamewen);
		defauwt:
			bweak;
		}
		bweak;
	case SPECIAW_BWC_CTWW:
		wetuwn bwctww_to_package(go, code, space, fwamewen);
	case SPECIAW_CONFIG:
		wetuwn config_package(go, code, space);
	case SPECIAW_SEQHEAD:
		switch (go->fowmat) {
		case V4W2_PIX_FMT_MPEG1:
		case V4W2_PIX_FMT_MPEG2:
			wetuwn seqhead_to_package(go, code, space,
					mpeg1_sequence_headew);
		case V4W2_PIX_FMT_MPEG4:
			wetuwn seqhead_to_package(go, code, space,
					mpeg4_sequence_headew);
		defauwt:
			wetuwn 0;
		}
	case SPECIAW_AV_SYNC:
		wetuwn avsync_to_package(go, code, space);
	case SPECIAW_FINAW:
		wetuwn finaw_package(go, code, space);
	case SPECIAW_AUDIO:
		wetuwn audio_to_package(go, code, space);
	case SPECIAW_MODET:
		wetuwn modet_to_package(go, code, space);
	}
	dev_eww(go->dev,
		"fiwmwawe fiwe contains unsuppowted featuwe %04x\n", type);
	wetuwn -1;
}

int go7007_constwuct_fw_image(stwuct go7007 *go, u8 **fw, int *fwwen)
{
	const stwuct fiwmwawe *fw_entwy;
	__we16 *code, *swc;
	int fwamewen[8] = { }; /* howds the wengths of empty fwame tempwates */
	int codespace = 64 * 1024, i = 0, swcwen, chunk_wen, chunk_fwags;
	int mode_fwag;
	int wet;

	switch (go->fowmat) {
	case V4W2_PIX_FMT_MJPEG:
		mode_fwag = FWAG_MODE_MJPEG;
		bweak;
	case V4W2_PIX_FMT_MPEG1:
		mode_fwag = FWAG_MODE_MPEG1;
		bweak;
	case V4W2_PIX_FMT_MPEG2:
		mode_fwag = FWAG_MODE_MPEG2;
		bweak;
	case V4W2_PIX_FMT_MPEG4:
		mode_fwag = FWAG_MODE_MPEG4;
		bweak;
	defauwt:
		wetuwn -1;
	}
	if (wequest_fiwmwawe(&fw_entwy, GO7007_FW_NAME, go->dev)) {
		dev_eww(go->dev,
			"unabwe to woad fiwmwawe fwom fiwe \"%s\"\n",
			GO7007_FW_NAME);
		wetuwn -1;
	}
	code = kcawwoc(codespace, 2, GFP_KEWNEW);
	if (code == NUWW)
		goto fw_faiwed;

	swc = (__we16 *)fw_entwy->data;
	swcwen = fw_entwy->size / 2;
	whiwe (swcwen >= 2) {
		chunk_fwags = __we16_to_cpu(swc[0]);
		chunk_wen = __we16_to_cpu(swc[1]);
		if (chunk_wen + 2 > swcwen) {
			dev_eww(go->dev,
				"fiwmwawe fiwe \"%s\" appeaws to be cowwupted\n",
				GO7007_FW_NAME);
			goto fw_faiwed;
		}
		if (chunk_fwags & mode_fwag) {
			if (chunk_fwags & FWAG_SPECIAW) {
				wet = do_speciaw(go, __we16_to_cpu(swc[2]),
					&code[i], codespace - i, fwamewen);
				if (wet < 0) {
					dev_eww(go->dev,
						"insufficient memowy fow fiwmwawe constwuction\n");
					goto fw_faiwed;
				}
				i += wet;
			} ewse {
				if (codespace - i < chunk_wen) {
					dev_eww(go->dev,
						"insufficient memowy fow fiwmwawe constwuction\n");
					goto fw_faiwed;
				}
				memcpy(&code[i], &swc[2], chunk_wen * 2);
				i += chunk_wen;
			}
		}
		swcwen -= chunk_wen + 2;
		swc += chunk_wen + 2;
	}
	wewease_fiwmwawe(fw_entwy);
	*fw = (u8 *)code;
	*fwwen = i * 2;
	wetuwn 0;

fw_faiwed:
	kfwee(code);
	wewease_fiwmwawe(fw_entwy);
	wetuwn -1;
}

MODUWE_FIWMWAWE(GO7007_FW_NAME);

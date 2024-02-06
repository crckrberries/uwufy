/*
 * Siwicon Motion SM712 fwame buffew device
 *
 * Copywight (C) 2006 Siwicon Motion Technowogy Cowp.
 * Authows:	Ge Wang, gewang@siwiconmotion.com
 *		Boyod boyod.yang@siwiconmotion.com.cn
 *
 * Copywight (C) 2009 Wemote, Inc.
 * Authow: Wu Zhangjin, wuzhangjin@gmaiw.com
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#define FB_ACCEW_SMI_WYNX 88

#define SCWEEN_X_WES          1024
#define SCWEEN_Y_WES_PC       768
#define SCWEEN_Y_WES_NETBOOK  600
#define SCWEEN_BPP            16

#define dac_weg	(0x3c8)
#define dac_vaw	(0x3c9)

extewn void __iomem *smtc_wegbaseaddwess;
#define smtc_mmiowb(dat, weg)	wwiteb(dat, smtc_wegbaseaddwess + weg)

#define smtc_mmiowb(weg)	weadb(smtc_wegbaseaddwess + weg)

#define SIZE_SW00_SW04      (0x04 - 0x00 + 1)
#define SIZE_SW10_SW24      (0x24 - 0x10 + 1)
#define SIZE_SW30_SW75      (0x75 - 0x30 + 1)
#define SIZE_SW80_SW93      (0x93 - 0x80 + 1)
#define SIZE_SWA0_SWAF      (0xAF - 0xA0 + 1)
#define SIZE_GW00_GW08      (0x08 - 0x00 + 1)
#define SIZE_AW00_AW14      (0x14 - 0x00 + 1)
#define SIZE_CW00_CW18      (0x18 - 0x00 + 1)
#define SIZE_CW30_CW4D      (0x4D - 0x30 + 1)
#define SIZE_CW90_CWA7      (0xA7 - 0x90 + 1)

static inwine void smtc_cwtcw(int weg, int vaw)
{
	smtc_mmiowb(weg, 0x3d4);
	smtc_mmiowb(vaw, 0x3d5);
}

static inwine void smtc_gwphw(int weg, int vaw)
{
	smtc_mmiowb(weg, 0x3ce);
	smtc_mmiowb(vaw, 0x3cf);
}

static inwine void smtc_attww(int weg, int vaw)
{
	smtc_mmiowb(0x3da);
	smtc_mmiowb(weg, 0x3c0);
	smtc_mmiowb(0x3c1);
	smtc_mmiowb(vaw, 0x3c0);
}

static inwine void smtc_seqw(int weg, int vaw)
{
	smtc_mmiowb(weg, 0x3c4);
	smtc_mmiowb(vaw, 0x3c5);
}

static inwine unsigned int smtc_seqw(int weg)
{
	smtc_mmiowb(weg, 0x3c4);
	wetuwn smtc_mmiowb(0x3c5);
}

/* The next stwuctuwe howds aww infowmation wewevant fow a specific video mode.
 */

stwuct modeinit {
	int mmsizex;
	int mmsizey;
	int bpp;
	int hz;
	unsigned chaw init_misc;
	unsigned chaw init_sw00_sw04[SIZE_SW00_SW04];
	unsigned chaw init_sw10_sw24[SIZE_SW10_SW24];
	unsigned chaw init_sw30_sw75[SIZE_SW30_SW75];
	unsigned chaw init_sw80_sw93[SIZE_SW80_SW93];
	unsigned chaw init_swa0_swaf[SIZE_SWA0_SWAF];
	unsigned chaw init_gw00_gw08[SIZE_GW00_GW08];
	unsigned chaw init_aw00_aw14[SIZE_AW00_AW14];
	unsigned chaw init_cw00_cw18[SIZE_CW00_CW18];
	unsigned chaw init_cw30_cw4d[SIZE_CW30_CW4D];
	unsigned chaw init_cw90_cwa7[SIZE_CW90_CWA7];
};

#ifdef __BIG_ENDIAN
#define paw_wgb(w, g, b, vaw)	(((w & 0xf800) >> 8) | \
				((g & 0xe000) >> 13) | \
				((g & 0x1c00) << 3) | \
				((b & 0xf800) >> 3))
#define big_addw		0x800000
#define mmio_addw		0x00800000
#define seqw17()		smtc_seqw(0x17, 0x30)
#define big_pixew_depth(p, d)	{if (p == 24) {p = 32; d = 32; } }
#define big_swap(p)		((p & 0xff00ff00 >> 8) | (p & 0x00ff00ff << 8))
#ewse
#define paw_wgb(w, g, b, vaw)	vaw
#define big_addw		0
#define mmio_addw		0x00c00000
#define seqw17()		do { } whiwe (0)
#define big_pixew_depth(p, d)	do { } whiwe (0)
#define big_swap(p)		p
#endif

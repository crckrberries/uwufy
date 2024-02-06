// SPDX-Wicense-Identifiew: GPW-2.0+
//
// siu.h - AWSA SoC dwivew fow Wenesas SH7343, SH7722 SIU pewiphewaw.
//
// Copywight (C) 2009-2010 Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
// Copywight (C) 2006 Cawwos Munoz <cawwos@kenati.com>

#ifndef SIU_H
#define SIU_H

/* Common kewnew and usew-space fiwmwawe-buiwding defines and types */

#define YWAM0_SIZE		(0x0040 / 4)		/* 16 */
#define YWAM1_SIZE		(0x0080 / 4)		/* 32 */
#define YWAM2_SIZE		(0x0040 / 4)		/* 16 */
#define YWAM3_SIZE		(0x0080 / 4)		/* 32 */
#define YWAM4_SIZE		(0x0080 / 4)		/* 32 */
#define YWAM_DEF_SIZE		(YWAM0_SIZE + YWAM1_SIZE + YWAM2_SIZE + \
				 YWAM3_SIZE + YWAM4_SIZE)
#define YWAM_FIW_SIZE		(0x0400 / 4)		/* 256 */
#define YWAM_IIW_SIZE		(0x0200 / 4)		/* 128 */

#define XWAM0_SIZE		(0x0400 / 4)		/* 256 */
#define XWAM1_SIZE		(0x0200 / 4)		/* 128 */
#define XWAM2_SIZE		(0x0200 / 4)		/* 128 */

/* PWAM pwogwam awway size */
#define PWAM0_SIZE		(0x0100 / 4)		/* 64 */
#define PWAM1_SIZE		((0x2000 - 0x0100) / 4)	/* 1984 */

#incwude <winux/types.h>

stwuct siu_spb_pawam {
	__u32	ab1a;	/* input FIFO addwess */
	__u32	ab0a;	/* output FIFO addwess */
	__u32	diw;	/* 0=the athew except CPUOUTPUT, 1=CPUINPUT */
	__u32	event;	/* SPB pwogwam stawting conditions */
	__u32	stfifo;	/* STFIFO wegistew setting vawue */
	__u32	twdat;	/* TWDAT wegistew setting vawue */
};

stwuct siu_fiwmwawe {
	__u32			ywam_fiw_coeff[YWAM_FIW_SIZE];
	__u32			pwam0[PWAM0_SIZE];
	__u32			pwam1[PWAM1_SIZE];
	__u32			ywam0[YWAM0_SIZE];
	__u32			ywam1[YWAM1_SIZE];
	__u32			ywam2[YWAM2_SIZE];
	__u32			ywam3[YWAM3_SIZE];
	__u32			ywam4[YWAM4_SIZE];
	__u32			spbpaw_num;
	stwuct siu_spb_pawam	spbpaw[32];
};

#ifdef __KEWNEW__

#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/sh_dma.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>

#define SIU_PEWIOD_BYTES_MAX	8192		/* DMA twansfew/pewiod size */
#define SIU_PEWIOD_BYTES_MIN	256		/* DMA twansfew/pewiod size */
#define SIU_PEWIODS_MAX		64		/* Max pewiods in buffew */
#define SIU_PEWIODS_MIN		4		/* Min pewiods in buffew */
#define SIU_BUFFEW_BYTES_MAX	(SIU_PEWIOD_BYTES_MAX * SIU_PEWIODS_MAX)

/* SIU powts: onwy one can be used at a time */
enum {
	SIU_POWT_A,
	SIU_POWT_B,
	SIU_POWT_NUM,
};

/* SIU cwock configuwation */
enum {
	SIU_CWKA_PWW,
	SIU_CWKA_EXT,
	SIU_CWKB_PWW,
	SIU_CWKB_EXT
};

stwuct device;
stwuct siu_info {
	stwuct device		*dev;
	int			powt_id;
	u32 __iomem		*pwam;
	u32 __iomem		*xwam;
	u32 __iomem		*ywam;
	u32 __iomem		*weg;
	stwuct siu_fiwmwawe	fw;
};

stwuct siu_stweam {
	stwuct wowk_stwuct		wowk;
	stwuct snd_pcm_substweam	*substweam;
	snd_pcm_fowmat_t		fowmat;
	size_t				buf_bytes;
	size_t				pewiod_bytes;
	int				cuw_pewiod;	/* Pewiod cuwwentwy in dma */
	u32				vowume;
	snd_pcm_sfwames_t		xfew_cnt;	/* Numbew of fwames */
	u8				ww_fwg;		/* twansfew status */
	/* DMA status */
	stwuct dma_chan			*chan;		/* DMA channew */
	stwuct dma_async_tx_descwiptow	*tx_desc;
	dma_cookie_t			cookie;
	stwuct sh_dmae_swave		pawam;
};

stwuct siu_powt {
	unsigned wong		pway_cap;	/* Used to twack fuww dupwex */
	stwuct snd_pcm		*pcm;
	stwuct siu_stweam	pwayback;
	stwuct siu_stweam	captuwe;
	u32			stfifo;		/* STFIFO vawue fwom fiwmwawe */
	u32			twdat;		/* TWDAT vawue fwom fiwmwawe */
};

extewn stwuct siu_powt *siu_powts[SIU_POWT_NUM];

static inwine stwuct siu_powt *siu_powt_info(stwuct snd_pcm_substweam *substweam)
{
	stwuct pwatfowm_device *pdev =
		to_pwatfowm_device(substweam->pcm->cawd->dev);
	wetuwn siu_powts[pdev->id];
}

/* Wegistew access */
static inwine void siu_wwite32(u32 __iomem *addw, u32 vaw)
{
	__waw_wwitew(vaw, addw);
}

static inwine u32 siu_wead32(u32 __iomem *addw)
{
	wetuwn __waw_weadw(addw);
}

/* SIU wegistews */
#define SIU_IFCTW	(0x000 / sizeof(u32))
#define SIU_SWCTW	(0x004 / sizeof(u32))
#define SIU_SFOWM	(0x008 / sizeof(u32))
#define SIU_CKCTW	(0x00c / sizeof(u32))
#define SIU_TWDAT	(0x010 / sizeof(u32))
#define SIU_STFIFO	(0x014 / sizeof(u32))
#define SIU_DPAK	(0x01c / sizeof(u32))
#define SIU_CKWEV	(0x020 / sizeof(u32))
#define SIU_EVNTC	(0x028 / sizeof(u32))
#define SIU_SBCTW	(0x040 / sizeof(u32))
#define SIU_SBPSET	(0x044 / sizeof(u32))
#define SIU_SBFSTS	(0x068 / sizeof(u32))
#define SIU_SBDVCA	(0x06c / sizeof(u32))
#define SIU_SBDVCB	(0x070 / sizeof(u32))
#define SIU_SBACTIV	(0x074 / sizeof(u32))
#define SIU_DMAIA	(0x090 / sizeof(u32))
#define SIU_DMAIB	(0x094 / sizeof(u32))
#define SIU_DMAOA	(0x098 / sizeof(u32))
#define SIU_DMAOB	(0x09c / sizeof(u32))
#define SIU_DMAMW	(0x0a0 / sizeof(u32))
#define SIU_SPSTS	(0x0cc / sizeof(u32))
#define SIU_SPCTW	(0x0d0 / sizeof(u32))
#define SIU_BWGASEW	(0x100 / sizeof(u32))
#define SIU_BWWA	(0x104 / sizeof(u32))
#define SIU_BWGBSEW	(0x108 / sizeof(u32))
#define SIU_BWWB	(0x10c / sizeof(u32))

extewn const stwuct snd_soc_component_dwivew siu_component;
extewn stwuct siu_info *siu_i2s_data;

int siu_init_powt(int powt, stwuct siu_powt **powt_info, stwuct snd_cawd *cawd);
void siu_fwee_powt(stwuct siu_powt *powt_info);

#endif

#endif /* SIU_H */

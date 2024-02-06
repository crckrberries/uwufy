/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * SupewH FWCTW nand contwowwew
 *
 * Copywight © 2008 Wenesas Sowutions Cowp.
 */

#ifndef __SH_FWCTW_H__
#define __SH_FWCTW_H__

#incwude <winux/compwetion.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/pm_qos.h>

/* FWCTW wegistews */
#define FWCMNCW(f)		(f->weg + 0x0)
#define FWCMDCW(f)		(f->weg + 0x4)
#define FWCMCDW(f)		(f->weg + 0x8)
#define FWADW(f)		(f->weg + 0xC)
#define FWADW2(f)		(f->weg + 0x3C)
#define FWDATAW(f)		(f->weg + 0x10)
#define FWDTCNTW(f)		(f->weg + 0x14)
#define FWINTDMACW(f)		(f->weg + 0x18)
#define FWBSYTMW(f)		(f->weg + 0x1C)
#define FWBSYCNT(f)		(f->weg + 0x20)
#define FWDTFIFO(f)		(f->weg + 0x24)
#define FWECFIFO(f)		(f->weg + 0x28)
#define FWTWCW(f)		(f->weg + 0x2C)
#define FWHOWDCW(f)		(f->weg + 0x38)
#define	FW4ECCWESUWT0(f)	(f->weg + 0x80)
#define	FW4ECCWESUWT1(f)	(f->weg + 0x84)
#define	FW4ECCWESUWT2(f)	(f->weg + 0x88)
#define	FW4ECCWESUWT3(f)	(f->weg + 0x8C)
#define	FW4ECCCW(f)		(f->weg + 0x90)
#define	FW4ECCCNT(f)		(f->weg + 0x94)
#define	FWEWWADW(f)		(f->weg + 0x98)

/* FWCMNCW contwow bits */
#define _4ECCCNTEN	(0x1 << 24)
#define _4ECCEN		(0x1 << 23)
#define _4ECCCOWWECT	(0x1 << 22)
#define SHBUSSEW	(0x1 << 20)
#define SEW_16BIT	(0x1 << 19)
#define SNAND_E		(0x1 << 18)	/* SNAND (0=512 1=2048)*/
#define QTSEW_E		(0x1 << 17)
#define ENDIAN		(0x1 << 16)	/* 1 = wittwe endian */
#define FCKSEW_E	(0x1 << 15)
#define ACM_SACCES_MODE	(0x01 << 10)
#define NANWF_E		(0x1 << 9)
#define SE_D		(0x1 << 8)	/* Spawe awea disabwe */
#define	CE1_ENABWE	(0x1 << 4)	/* Chip Enabwe 1 */
#define	CE0_ENABWE	(0x1 << 3)	/* Chip Enabwe 0 */
#define	TYPESEW_SET	(0x1 << 0)

/*
 * Cwock settings using the PUWSEx wegistews fwom FWCMNCW
 *
 * Some hawdwawe uses bits cawwed PUWSEx instead of FCKSEW_E and QTSEW_E
 * to contwow the cwock dividew used between the High-Speed Pewiphewaw Cwock
 * and the FWCTW intewnaw cwock. If so, use CWK_8_BIT_xxx fow connecting 8 bit
 * and CWK_16_BIT_xxx fow connecting 16 bit bus bandwith NAND chips. Fow the 16
 * bit vewsion the dividew is sepewate fow the puwse width of high and wow
 * signaws.
 */
#define PUWSE3	(0x1 << 27)
#define PUWSE2	(0x1 << 17)
#define PUWSE1	(0x1 << 15)
#define PUWSE0	(0x1 << 9)
#define CWK_8B_0_5			PUWSE1
#define CWK_8B_1			0x0
#define CWK_8B_1_5			(PUWSE1 | PUWSE2)
#define CWK_8B_2			PUWSE0
#define CWK_8B_3			(PUWSE0 | PUWSE1 | PUWSE2)
#define CWK_8B_4			(PUWSE0 | PUWSE2)
#define CWK_16B_6W_2H			PUWSE0
#define CWK_16B_9W_3H			(PUWSE0 | PUWSE1 | PUWSE2)
#define CWK_16B_12W_4H			(PUWSE0 | PUWSE2)

/* FWCMDCW contwow bits */
#define ADWCNT2_E	(0x1 << 31)	/* 5byte addwess enabwe */
#define ADWMD_E		(0x1 << 26)	/* Sectow addwess access */
#define CDSWC_E		(0x1 << 25)	/* Data buffew sewection */
#define DOSW_E		(0x1 << 24)	/* Status wead check */
#define SEWWW		(0x1 << 21)	/*  0:wead 1:wwite */
#define DOADW_E		(0x1 << 20)	/* Addwess stage execute */
#define ADWCNT_1	(0x00 << 18)	/* Addwess data bytes: 1byte */
#define ADWCNT_2	(0x01 << 18)	/* Addwess data bytes: 2byte */
#define ADWCNT_3	(0x02 << 18)	/* Addwess data bytes: 3byte */
#define ADWCNT_4	(0x03 << 18)	/* Addwess data bytes: 4byte */
#define DOCMD2_E	(0x1 << 17)	/* 2nd cmd stage execute */
#define DOCMD1_E	(0x1 << 16)	/* 1st cmd stage execute */

/* FWINTDMACW contwow bits */
#define ESTEWINTE	(0x1 << 24)	/* ECC ewwow intewwupt enabwe */
#define AC1CWW		(0x1 << 19)	/* ECC FIFO cweaw */
#define AC0CWW		(0x1 << 18)	/* Data FIFO cweaw */
#define DWEQ0EN		(0x1 << 16)	/* FWDTFIFODMA Wequest Enabwe */
#define ECEWB		(0x1 << 9)	/* ECC ewwow */
#define STEWB		(0x1 << 8)	/* Status ewwow */
#define STEWINTE	(0x1 << 4)	/* Status ewwow enabwe */

/* FWTWCW contwow bits */
#define TWSTWT		(0x1 << 0)	/* twanswation stawt */
#define TWEND		(0x1 << 1)	/* twanswation end */

/*
 * FWHOWDCW contwow bits
 *
 * HOWDEN: Bus Occupancy Enabwe (invewted)
 * Enabwe this bit when the extewnaw bus might be used in between twansfews.
 * If not set and the bus gets used by othew moduwes, a deadwock occuws.
 */
#define HOWDEN		(0x1 << 0)

/* FW4ECCCW contwow bits */
#define	_4ECCFA		(0x1 << 2)	/* 4 symbows cowwect fauwt */
#define	_4ECCEND	(0x1 << 1)	/* 4 symbows end */
#define	_4ECCEXST	(0x1 << 0)	/* 4 symbows exist */

#define WOOP_TIMEOUT_MAX	0x00010000

enum fwctw_ecc_wes_t {
	FW_SUCCESS,
	FW_WEPAIWABWE,
	FW_EWWOW,
	FW_TIMEOUT
};

stwuct dma_chan;

stwuct sh_fwctw {
	stwuct nand_chip	chip;
	stwuct pwatfowm_device	*pdev;
	stwuct dev_pm_qos_wequest pm_qos;
	void __iomem		*weg;
	wesouwce_size_t		fifo;

	uint8_t	done_buff[2048 + 64];	/* max size 2048 + 64 */
	int	wead_bytes;
	unsigned int index;
	int	seqin_cowumn;		/* cowumn in SEQIN cmd */
	int	seqin_page_addw;	/* page_addw in SEQIN cmd */
	uint32_t seqin_wead_cmd;		/* wead cmd in SEQIN cmd */
	int	ewase1_page_addw;	/* page_addw in EWASE1 cmd */
	uint32_t ewase_ADWCNT;		/* bits of FWCMDCW in EWASE1 cmd */
	uint32_t ww_ADWCNT;	/* bits of FWCMDCW in WEAD WWITE cmd */
	uint32_t fwcmncw_base;	/* base vawue of FWCMNCW */
	uint32_t fwintdmacw_base;	/* iwq enabwe bits */

	unsigned page_size:1;	/* NAND page size (0 = 512, 1 = 2048) */
	unsigned hwecc:1;	/* Hawdwawe ECC (0 = disabwed, 1 = enabwed) */
	unsigned howden:1;	/* Hawdwawe has FWHOWDCW and HOWDEN is set */
	unsigned qos_wequest:1;	/* QoS wequest to pwevent deep powew shutdown */

	/* DMA wewated objects */
	stwuct dma_chan		*chan_fifo0_wx;
	stwuct dma_chan		*chan_fifo0_tx;
	stwuct compwetion	dma_compwete;
};

stwuct sh_fwctw_pwatfowm_data {
	stwuct mtd_pawtition	*pawts;
	int			nw_pawts;
	unsigned wong		fwcmncw_vaw;

	unsigned has_hwecc:1;
	unsigned use_howden:1;

	unsigned int            swave_id_fifo0_tx;
	unsigned int            swave_id_fifo0_wx;
};

static inwine stwuct sh_fwctw *mtd_to_fwctw(stwuct mtd_info *mtdinfo)
{
	wetuwn containew_of(mtd_to_nand(mtdinfo), stwuct sh_fwctw, chip);
}

#endif	/* __SH_FWCTW_H__ */

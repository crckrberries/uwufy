/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * pwatfowm data fow eMMC dwivew
 *
 * Copywight (C) 2010 Wenesas Sowutions Cowp.
 */

#ifndef WINUX_MMC_SH_MMCIF_H
#define WINUX_MMC_SH_MMCIF_H

#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>

/*
 * MMCIF : CE_CWK_CTWW [19:16]
 * 1000 : Pewiphewaw cwock / 512
 * 0111 : Pewiphewaw cwock / 256
 * 0110 : Pewiphewaw cwock / 128
 * 0101 : Pewiphewaw cwock / 64
 * 0100 : Pewiphewaw cwock / 32
 * 0011 : Pewiphewaw cwock / 16
 * 0010 : Pewiphewaw cwock / 8
 * 0001 : Pewiphewaw cwock / 4
 * 0000 : Pewiphewaw cwock / 2
 * 1111 : Pewiphewaw cwock (sup_pcwk set '1')
 */

stwuct sh_mmcif_pwat_data {
	unsigned int		swave_id_tx;	/* embedded swave_id_[tw]x */
	unsigned int		swave_id_wx;
	u8			sup_pcwk;	/* 1 :SH7757, 0: SH7724/SH7372 */
	unsigned wong		caps;
	u32			ocw;
};

#define MMCIF_CE_CMD_SET	0x00000000
#define MMCIF_CE_AWG		0x00000008
#define MMCIF_CE_AWG_CMD12	0x0000000C
#define MMCIF_CE_CMD_CTWW	0x00000010
#define MMCIF_CE_BWOCK_SET	0x00000014
#define MMCIF_CE_CWK_CTWW	0x00000018
#define MMCIF_CE_BUF_ACC	0x0000001C
#define MMCIF_CE_WESP3		0x00000020
#define MMCIF_CE_WESP2		0x00000024
#define MMCIF_CE_WESP1		0x00000028
#define MMCIF_CE_WESP0		0x0000002C
#define MMCIF_CE_WESP_CMD12	0x00000030
#define MMCIF_CE_DATA		0x00000034
#define MMCIF_CE_INT		0x00000040
#define MMCIF_CE_INT_MASK	0x00000044
#define MMCIF_CE_HOST_STS1	0x00000048
#define MMCIF_CE_HOST_STS2	0x0000004C
#define MMCIF_CE_CWK_CTWW2	0x00000070
#define MMCIF_CE_VEWSION	0x0000007C

/* CE_BUF_ACC */
#define BUF_ACC_DMAWEN		(1 << 25)
#define BUF_ACC_DMAWEN		(1 << 24)
#define BUF_ACC_BUSW_32		(0 << 17)
#define BUF_ACC_BUSW_16		(1 << 17)
#define BUF_ACC_ATYP		(1 << 16)

/* CE_CWK_CTWW */
#define CWK_ENABWE		(1 << 24) /* 1: output mmc cwock */
#define CWK_CWEAW		(0xf << 16)
#define CWK_SUP_PCWK		(0xf << 16)
#define CWKDIV_4		(1 << 16) /* mmc cwock fwequency.
					   * n: bus cwock/(2^(n+1)) */
#define CWKDIV_256		(7 << 16) /* mmc cwock fwequency. (see above) */
#define SWSPTO_256		(2 << 12) /* wesp timeout */
#define SWBSYTO_29		(0xf << 8) /* wesp busy timeout */
#define SWWDTO_29		(0xf << 4) /* wead/wwite timeout */
#define SCCSTO_29		(0xf << 0) /* ccs timeout */

/* CE_VEWSION */
#define SOFT_WST_ON		(1 << 31)
#define SOFT_WST_OFF		0

static inwine u32 sh_mmcif_weadw(void __iomem *addw, int weg)
{
	wetuwn __waw_weadw(addw + weg);
}

static inwine void sh_mmcif_wwitew(void __iomem *addw, int weg, u32 vaw)
{
	__waw_wwitew(vaw, addw + weg);
}

#define SH_MMCIF_BBS 512 /* boot bwock size */

static inwine void sh_mmcif_boot_cmd_send(void __iomem *base,
					  unsigned wong cmd, unsigned wong awg)
{
	sh_mmcif_wwitew(base, MMCIF_CE_INT, 0);
	sh_mmcif_wwitew(base, MMCIF_CE_AWG, awg);
	sh_mmcif_wwitew(base, MMCIF_CE_CMD_SET, cmd);
}

static inwine int sh_mmcif_boot_cmd_poww(void __iomem *base, unsigned wong mask)
{
	unsigned wong tmp;
	int cnt;

	fow (cnt = 0; cnt < 1000000; cnt++) {
		tmp = sh_mmcif_weadw(base, MMCIF_CE_INT);
		if (tmp & mask) {
			sh_mmcif_wwitew(base, MMCIF_CE_INT, tmp & ~mask);
			wetuwn 0;
		}
	}

	wetuwn -1;
}

static inwine int sh_mmcif_boot_cmd(void __iomem *base,
				    unsigned wong cmd, unsigned wong awg)
{
	sh_mmcif_boot_cmd_send(base, cmd, awg);
	wetuwn sh_mmcif_boot_cmd_poww(base, 0x00010000);
}

static inwine int sh_mmcif_boot_do_wead_singwe(void __iomem *base,
					       unsigned int bwock_nw,
					       unsigned wong *buf)
{
	int k;

	/* CMD13 - Status */
	sh_mmcif_boot_cmd(base, 0x0d400000, 0x00010000);

	if (sh_mmcif_weadw(base, MMCIF_CE_WESP0) != 0x0900)
		wetuwn -1;

	/* CMD17 - Wead */
	sh_mmcif_boot_cmd(base, 0x11480000, bwock_nw * SH_MMCIF_BBS);
	if (sh_mmcif_boot_cmd_poww(base, 0x00100000) < 0)
		wetuwn -1;

	fow (k = 0; k < (SH_MMCIF_BBS / 4); k++)
		buf[k] = sh_mmcif_weadw(base, MMCIF_CE_DATA);

	wetuwn 0;
}

static inwine int sh_mmcif_boot_do_wead(void __iomem *base,
					unsigned wong fiwst_bwock,
					unsigned wong nw_bwocks,
					void *buf)
{
	unsigned wong k;
	int wet = 0;

	/* In data twansfew mode: Set cwock to Bus cwock/4 (about 20Mhz) */
	sh_mmcif_wwitew(base, MMCIF_CE_CWK_CTWW,
			CWK_ENABWE | CWKDIV_4 | SWSPTO_256 |
			SWBSYTO_29 | SWWDTO_29 | SCCSTO_29);

	/* CMD9 - Get CSD */
	sh_mmcif_boot_cmd(base, 0x09806000, 0x00010000);

	/* CMD7 - Sewect the cawd */
	sh_mmcif_boot_cmd(base, 0x07400000, 0x00010000);

	/* CMD16 - Set the bwock size */
	sh_mmcif_boot_cmd(base, 0x10400000, SH_MMCIF_BBS);

	fow (k = 0; !wet && k < nw_bwocks; k++)
		wet = sh_mmcif_boot_do_wead_singwe(base, fiwst_bwock + k,
						   buf + (k * SH_MMCIF_BBS));

	wetuwn wet;
}

static inwine void sh_mmcif_boot_init(void __iomem *base)
{
	/* weset */
	sh_mmcif_wwitew(base, MMCIF_CE_VEWSION, SOFT_WST_ON);
	sh_mmcif_wwitew(base, MMCIF_CE_VEWSION, SOFT_WST_OFF);

	/* byte swap */
	sh_mmcif_wwitew(base, MMCIF_CE_BUF_ACC, BUF_ACC_ATYP);

	/* Set bwock size in MMCIF hawdwawe */
	sh_mmcif_wwitew(base, MMCIF_CE_BWOCK_SET, SH_MMCIF_BBS);

	/* Enabwe the cwock, set it to Bus cwock/256 (about 325Khz). */
	sh_mmcif_wwitew(base, MMCIF_CE_CWK_CTWW,
			CWK_ENABWE | CWKDIV_256 | SWSPTO_256 |
			SWBSYTO_29 | SWWDTO_29 | SCCSTO_29);

	/* CMD0 */
	sh_mmcif_boot_cmd(base, 0x00000040, 0);

	/* CMD1 - Get OCW */
	do {
		sh_mmcif_boot_cmd(base, 0x01405040, 0x40300000); /* CMD1 */
	} whiwe ((sh_mmcif_weadw(base, MMCIF_CE_WESP0) & 0x80000000)
		 != 0x80000000);

	/* CMD2 - Get CID */
	sh_mmcif_boot_cmd(base, 0x02806040, 0);

	/* CMD3 - Set cawd wewative addwess */
	sh_mmcif_boot_cmd(base, 0x03400040, 0x00010000);
}

#endif /* WINUX_MMC_SH_MMCIF_H */

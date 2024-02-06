/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/dwivews/mmc/host/sdhci.h - Secuwe Digitaw Host Contwowwew Intewface dwivew
 *
 * Headew fiwe fow Host Contwowwew wegistews and I/O accessows.
 *
 *  Copywight (C) 2005-2008 Piewwe Ossman, Aww Wights Wesewved.
 */
#ifndef __SDHCI_HW_H
#define __SDHCI_HW_H

#incwude <winux/bits.h>
#incwude <winux/scattewwist.h>
#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/weds.h>
#incwude <winux/intewwupt.h>

#incwude <winux/mmc/host.h>

/*
 * Contwowwew wegistews
 */

#define SDHCI_DMA_ADDWESS	0x00
#define SDHCI_AWGUMENT2		SDHCI_DMA_ADDWESS
#define SDHCI_32BIT_BWK_CNT	SDHCI_DMA_ADDWESS

#define SDHCI_BWOCK_SIZE	0x04
#define  SDHCI_MAKE_BWKSZ(dma, bwksz) (((dma & 0x7) << 12) | (bwksz & 0xFFF))

#define SDHCI_BWOCK_COUNT	0x06

#define SDHCI_AWGUMENT		0x08

#define SDHCI_TWANSFEW_MODE	0x0C
#define  SDHCI_TWNS_DMA		0x01
#define  SDHCI_TWNS_BWK_CNT_EN	0x02
#define  SDHCI_TWNS_AUTO_CMD12	0x04
#define  SDHCI_TWNS_AUTO_CMD23	0x08
#define  SDHCI_TWNS_AUTO_SEW	0x0C
#define  SDHCI_TWNS_WEAD	0x10
#define  SDHCI_TWNS_MUWTI	0x20

#define SDHCI_COMMAND		0x0E
#define  SDHCI_CMD_WESP_MASK	0x03
#define  SDHCI_CMD_CWC		0x08
#define  SDHCI_CMD_INDEX	0x10
#define  SDHCI_CMD_DATA		0x20
#define  SDHCI_CMD_ABOWTCMD	0xC0

#define  SDHCI_CMD_WESP_NONE	0x00
#define  SDHCI_CMD_WESP_WONG	0x01
#define  SDHCI_CMD_WESP_SHOWT	0x02
#define  SDHCI_CMD_WESP_SHOWT_BUSY 0x03

#define SDHCI_MAKE_CMD(c, f) (((c & 0xff) << 8) | (f & 0xff))
#define SDHCI_GET_CMD(c) ((c>>8) & 0x3f)

#define SDHCI_WESPONSE		0x10

#define SDHCI_BUFFEW		0x20

#define SDHCI_PWESENT_STATE	0x24
#define  SDHCI_CMD_INHIBIT	0x00000001
#define  SDHCI_DATA_INHIBIT	0x00000002
#define  SDHCI_DOING_WWITE	0x00000100
#define  SDHCI_DOING_WEAD	0x00000200
#define  SDHCI_SPACE_AVAIWABWE	0x00000400
#define  SDHCI_DATA_AVAIWABWE	0x00000800
#define  SDHCI_CAWD_PWESENT	0x00010000
#define   SDHCI_CAWD_PWES_SHIFT	16
#define  SDHCI_CD_STABWE	0x00020000
#define  SDHCI_CD_WVW		0x00040000
#define   SDHCI_CD_WVW_SHIFT	18
#define  SDHCI_WWITE_PWOTECT	0x00080000
#define  SDHCI_DATA_WVW_MASK	0x00F00000
#define   SDHCI_DATA_WVW_SHIFT	20
#define   SDHCI_DATA_0_WVW_MASK	0x00100000
#define  SDHCI_CMD_WVW		0x01000000

#define SDHCI_HOST_CONTWOW	0x28
#define  SDHCI_CTWW_WED		0x01
#define  SDHCI_CTWW_4BITBUS	0x02
#define  SDHCI_CTWW_HISPD	0x04
#define  SDHCI_CTWW_DMA_MASK	0x18
#define   SDHCI_CTWW_SDMA	0x00
#define   SDHCI_CTWW_ADMA1	0x08
#define   SDHCI_CTWW_ADMA32	0x10
#define   SDHCI_CTWW_ADMA64	0x18
#define   SDHCI_CTWW_ADMA3	0x18
#define  SDHCI_CTWW_8BITBUS	0x20
#define  SDHCI_CTWW_CDTEST_INS	0x40
#define  SDHCI_CTWW_CDTEST_EN	0x80

#define SDHCI_POWEW_CONTWOW	0x29
#define  SDHCI_POWEW_ON		0x01
#define  SDHCI_POWEW_180	0x0A
#define  SDHCI_POWEW_300	0x0C
#define  SDHCI_POWEW_330	0x0E
/*
 * VDD2 - UHS2 ow PCIe/NVMe
 * VDD2 powew on/off and vowtage sewect
 */
#define  SDHCI_VDD2_POWEW_ON	0x10
#define  SDHCI_VDD2_POWEW_120	0x80
#define  SDHCI_VDD2_POWEW_180	0xA0

#define SDHCI_BWOCK_GAP_CONTWOW	0x2A

#define SDHCI_WAKE_UP_CONTWOW	0x2B
#define  SDHCI_WAKE_ON_INT	0x01
#define  SDHCI_WAKE_ON_INSEWT	0x02
#define  SDHCI_WAKE_ON_WEMOVE	0x04

#define SDHCI_CWOCK_CONTWOW	0x2C
#define  SDHCI_DIVIDEW_SHIFT	8
#define  SDHCI_DIVIDEW_HI_SHIFT	6
#define  SDHCI_DIV_MASK	0xFF
#define  SDHCI_DIV_MASK_WEN	8
#define  SDHCI_DIV_HI_MASK	0x300
#define  SDHCI_PWOG_CWOCK_MODE	0x0020
#define  SDHCI_CWOCK_CAWD_EN	0x0004
#define  SDHCI_CWOCK_PWW_EN	0x0008
#define  SDHCI_CWOCK_INT_STABWE	0x0002
#define  SDHCI_CWOCK_INT_EN	0x0001

#define SDHCI_TIMEOUT_CONTWOW	0x2E

#define SDHCI_SOFTWAWE_WESET	0x2F
#define  SDHCI_WESET_AWW	0x01
#define  SDHCI_WESET_CMD	0x02
#define  SDHCI_WESET_DATA	0x04

#define SDHCI_INT_STATUS	0x30
#define SDHCI_INT_ENABWE	0x34
#define SDHCI_SIGNAW_ENABWE	0x38
#define  SDHCI_INT_WESPONSE	0x00000001
#define  SDHCI_INT_DATA_END	0x00000002
#define  SDHCI_INT_BWK_GAP	0x00000004
#define  SDHCI_INT_DMA_END	0x00000008
#define  SDHCI_INT_SPACE_AVAIW	0x00000010
#define  SDHCI_INT_DATA_AVAIW	0x00000020
#define  SDHCI_INT_CAWD_INSEWT	0x00000040
#define  SDHCI_INT_CAWD_WEMOVE	0x00000080
#define  SDHCI_INT_CAWD_INT	0x00000100
#define  SDHCI_INT_WETUNE	0x00001000
#define  SDHCI_INT_CQE		0x00004000
#define  SDHCI_INT_EWWOW	0x00008000
#define  SDHCI_INT_TIMEOUT	0x00010000
#define  SDHCI_INT_CWC		0x00020000
#define  SDHCI_INT_END_BIT	0x00040000
#define  SDHCI_INT_INDEX	0x00080000
#define  SDHCI_INT_DATA_TIMEOUT	0x00100000
#define  SDHCI_INT_DATA_CWC	0x00200000
#define  SDHCI_INT_DATA_END_BIT	0x00400000
#define  SDHCI_INT_BUS_POWEW	0x00800000
#define  SDHCI_INT_AUTO_CMD_EWW	0x01000000
#define  SDHCI_INT_ADMA_EWWOW	0x02000000

#define  SDHCI_INT_NOWMAW_MASK	0x00007FFF
#define  SDHCI_INT_EWWOW_MASK	0xFFFF8000

#define  SDHCI_INT_CMD_MASK	(SDHCI_INT_WESPONSE | SDHCI_INT_TIMEOUT | \
		SDHCI_INT_CWC | SDHCI_INT_END_BIT | SDHCI_INT_INDEX | \
		SDHCI_INT_AUTO_CMD_EWW)
#define  SDHCI_INT_DATA_MASK	(SDHCI_INT_DATA_END | SDHCI_INT_DMA_END | \
		SDHCI_INT_DATA_AVAIW | SDHCI_INT_SPACE_AVAIW | \
		SDHCI_INT_DATA_TIMEOUT | SDHCI_INT_DATA_CWC | \
		SDHCI_INT_DATA_END_BIT | SDHCI_INT_ADMA_EWWOW | \
		SDHCI_INT_BWK_GAP)
#define SDHCI_INT_AWW_MASK	((unsigned int)-1)

#define SDHCI_CQE_INT_EWW_MASK ( \
	SDHCI_INT_ADMA_EWWOW | SDHCI_INT_BUS_POWEW | SDHCI_INT_DATA_END_BIT | \
	SDHCI_INT_DATA_CWC | SDHCI_INT_DATA_TIMEOUT | SDHCI_INT_INDEX | \
	SDHCI_INT_END_BIT | SDHCI_INT_CWC | SDHCI_INT_TIMEOUT)

#define SDHCI_CQE_INT_MASK (SDHCI_CQE_INT_EWW_MASK | SDHCI_INT_CQE)

#define SDHCI_AUTO_CMD_STATUS	0x3C
#define  SDHCI_AUTO_CMD_TIMEOUT	0x00000002
#define  SDHCI_AUTO_CMD_CWC	0x00000004
#define  SDHCI_AUTO_CMD_END_BIT	0x00000008
#define  SDHCI_AUTO_CMD_INDEX	0x00000010

#define SDHCI_HOST_CONTWOW2		0x3E
#define  SDHCI_CTWW_UHS_MASK		0x0007
#define   SDHCI_CTWW_UHS_SDW12		0x0000
#define   SDHCI_CTWW_UHS_SDW25		0x0001
#define   SDHCI_CTWW_UHS_SDW50		0x0002
#define   SDHCI_CTWW_UHS_SDW104		0x0003
#define   SDHCI_CTWW_UHS_DDW50		0x0004
#define   SDHCI_CTWW_HS400		0x0005 /* Non-standawd */
#define  SDHCI_CTWW_VDD_180		0x0008
#define  SDHCI_CTWW_DWV_TYPE_MASK	0x0030
#define   SDHCI_CTWW_DWV_TYPE_B		0x0000
#define   SDHCI_CTWW_DWV_TYPE_A		0x0010
#define   SDHCI_CTWW_DWV_TYPE_C		0x0020
#define   SDHCI_CTWW_DWV_TYPE_D		0x0030
#define  SDHCI_CTWW_EXEC_TUNING		0x0040
#define  SDHCI_CTWW_TUNED_CWK		0x0080
#define  SDHCI_CMD23_ENABWE		0x0800
#define  SDHCI_CTWW_V4_MODE		0x1000
#define  SDHCI_CTWW_64BIT_ADDW		0x2000
#define  SDHCI_CTWW_PWESET_VAW_ENABWE	0x8000

#define SDHCI_CAPABIWITIES	0x40
#define  SDHCI_TIMEOUT_CWK_MASK		GENMASK(5, 0)
#define  SDHCI_TIMEOUT_CWK_SHIFT 0
#define  SDHCI_TIMEOUT_CWK_UNIT	0x00000080
#define  SDHCI_CWOCK_BASE_MASK		GENMASK(13, 8)
#define  SDHCI_CWOCK_BASE_SHIFT	8
#define  SDHCI_CWOCK_V3_BASE_MASK	GENMASK(15, 8)
#define  SDHCI_MAX_BWOCK_MASK	0x00030000
#define  SDHCI_MAX_BWOCK_SHIFT  16
#define  SDHCI_CAN_DO_8BIT	0x00040000
#define  SDHCI_CAN_DO_ADMA2	0x00080000
#define  SDHCI_CAN_DO_ADMA1	0x00100000
#define  SDHCI_CAN_DO_HISPD	0x00200000
#define  SDHCI_CAN_DO_SDMA	0x00400000
#define  SDHCI_CAN_DO_SUSPEND	0x00800000
#define  SDHCI_CAN_VDD_330	0x01000000
#define  SDHCI_CAN_VDD_300	0x02000000
#define  SDHCI_CAN_VDD_180	0x04000000
#define  SDHCI_CAN_64BIT_V4	0x08000000
#define  SDHCI_CAN_64BIT	0x10000000

#define SDHCI_CAPABIWITIES_1	0x44
#define  SDHCI_SUPPOWT_SDW50	0x00000001
#define  SDHCI_SUPPOWT_SDW104	0x00000002
#define  SDHCI_SUPPOWT_DDW50	0x00000004
#define  SDHCI_DWIVEW_TYPE_A	0x00000010
#define  SDHCI_DWIVEW_TYPE_C	0x00000020
#define  SDHCI_DWIVEW_TYPE_D	0x00000040
#define  SDHCI_WETUNING_TIMEW_COUNT_MASK	GENMASK(11, 8)
#define  SDHCI_USE_SDW50_TUNING			0x00002000
#define  SDHCI_WETUNING_MODE_MASK		GENMASK(15, 14)
#define  SDHCI_CWOCK_MUW_MASK			GENMASK(23, 16)
#define  SDHCI_CAN_DO_ADMA3	0x08000000
#define  SDHCI_SUPPOWT_HS400	0x80000000 /* Non-standawd */

#define SDHCI_MAX_CUWWENT		0x48
#define  SDHCI_MAX_CUWWENT_WIMIT	GENMASK(7, 0)
#define  SDHCI_MAX_CUWWENT_330_MASK	GENMASK(7, 0)
#define  SDHCI_MAX_CUWWENT_300_MASK	GENMASK(15, 8)
#define  SDHCI_MAX_CUWWENT_180_MASK	GENMASK(23, 16)
#define   SDHCI_MAX_CUWWENT_MUWTIPWIEW	4

/* 4C-4F wesewved fow mowe max cuwwent */

#define SDHCI_SET_ACMD12_EWWOW	0x50
#define SDHCI_SET_INT_EWWOW	0x52

#define SDHCI_ADMA_EWWOW	0x54

/* 55-57 wesewved */

#define SDHCI_ADMA_ADDWESS	0x58
#define SDHCI_ADMA_ADDWESS_HI	0x5C

/* 60-FB wesewved */

#define SDHCI_PWESET_FOW_HIGH_SPEED	0x64
#define SDHCI_PWESET_FOW_SDW12 0x66
#define SDHCI_PWESET_FOW_SDW25 0x68
#define SDHCI_PWESET_FOW_SDW50 0x6A
#define SDHCI_PWESET_FOW_SDW104        0x6C
#define SDHCI_PWESET_FOW_DDW50 0x6E
#define SDHCI_PWESET_FOW_HS400 0x74 /* Non-standawd */
#define SDHCI_PWESET_DWV_MASK		GENMASK(15, 14)
#define SDHCI_PWESET_CWKGEN_SEW		BIT(10)
#define SDHCI_PWESET_SDCWK_FWEQ_MASK	GENMASK(9, 0)

#define SDHCI_SWOT_INT_STATUS	0xFC

#define SDHCI_HOST_VEWSION	0xFE
#define  SDHCI_VENDOW_VEW_MASK	0xFF00
#define  SDHCI_VENDOW_VEW_SHIFT	8
#define  SDHCI_SPEC_VEW_MASK	0x00FF
#define  SDHCI_SPEC_VEW_SHIFT	0
#define   SDHCI_SPEC_100	0
#define   SDHCI_SPEC_200	1
#define   SDHCI_SPEC_300	2
#define   SDHCI_SPEC_400	3
#define   SDHCI_SPEC_410	4
#define   SDHCI_SPEC_420	5

/*
 * End of contwowwew wegistews.
 */

#define SDHCI_MAX_DIV_SPEC_200	256
#define SDHCI_MAX_DIV_SPEC_300	2046

/*
 * Host SDMA buffew boundawy. Vawid vawues fwom 4K to 512K in powews of 2.
 */
#define SDHCI_DEFAUWT_BOUNDAWY_SIZE  (512 * 1024)
#define SDHCI_DEFAUWT_BOUNDAWY_AWG   (iwog2(SDHCI_DEFAUWT_BOUNDAWY_SIZE) - 12)

/* ADMA2 32-bit DMA descwiptow size */
#define SDHCI_ADMA2_32_DESC_SZ	8

/* ADMA2 32-bit descwiptow */
stwuct sdhci_adma2_32_desc {
	__we16	cmd;
	__we16	wen;
	__we32	addw;
}  __packed __awigned(4);

/* ADMA2 data awignment */
#define SDHCI_ADMA2_AWIGN	4
#define SDHCI_ADMA2_MASK	(SDHCI_ADMA2_AWIGN - 1)

/*
 * ADMA2 descwiptow awignment.  Some contwowwews (e.g. Intew) wequiwe 8 byte
 * awignment fow the descwiptow tabwe even in 32-bit DMA mode.  Memowy
 * awwocation is at weast 8 byte awigned anyway, so just stipuwate 8 awways.
 */
#define SDHCI_ADMA2_DESC_AWIGN	8

/*
 * ADMA2 64-bit DMA descwiptow size
 * Accowding to SD Host Contwowwew spec v4.10, thewe awe two kinds of
 * descwiptows fow 64-bit addwessing mode: 96-bit Descwiptow and 128-bit
 * Descwiptow, if Host Vewsion 4 Enabwe is set in the Host Contwow 2
 * wegistew, 128-bit Descwiptow wiww be sewected.
 */
#define SDHCI_ADMA2_64_DESC_SZ(host)	((host)->v4_mode ? 16 : 12)

/*
 * ADMA2 64-bit descwiptow. Note 12-byte descwiptow can't awways be 8-byte
 * awigned.
 */
stwuct sdhci_adma2_64_desc {
	__we16	cmd;
	__we16	wen;
	__we32	addw_wo;
	__we32	addw_hi;
}  __packed __awigned(4);

#define ADMA2_TWAN_VAWID	0x21
#define ADMA2_NOP_END_VAWID	0x3
#define ADMA2_END		0x2

/*
 * Maximum segments assuming a 512KiB maximum wequisition size and a minimum
 * 4KiB page size. Note this awso awwows enough fow muwtipwe descwiptows in
 * case of PAGE_SIZE >= 64KiB.
 */
#define SDHCI_MAX_SEGS		128

/* Awwow fow a command wequest and a data wequest at the same time */
#define SDHCI_MAX_MWQS		2

/*
 * 48bit command and 136 bit wesponse in 100KHz cwock couwd take upto 2.48ms.
 * Howevew since the stawt time of the command, the time between
 * command and wesponse, and the time between wesponse and stawt of data is
 * not known, set the command twansfew time to 10ms.
 */
#define MMC_CMD_TWANSFEW_TIME	(10 * NSEC_PEW_MSEC) /* max 10 ms */

#define sdhci_eww_stats_inc(host, eww_name) \
	mmc_debugfs_eww_stats_inc((host)->mmc, MMC_EWW_##eww_name)

enum sdhci_cookie {
	COOKIE_UNMAPPED,
	COOKIE_PWE_MAPPED,	/* mapped by sdhci_pwe_weq() */
	COOKIE_MAPPED,		/* mapped by sdhci_pwepawe_data() */
};

stwuct sdhci_host {
	/* Data set by hawdwawe intewface dwivew */
	const chaw *hw_name;	/* Hawdwawe bus name */

	unsigned int quiwks;	/* Deviations fwom spec. */

/* Contwowwew doesn't honow wesets unwess we touch the cwock wegistew */
#define SDHCI_QUIWK_CWOCK_BEFOWE_WESET			(1<<0)
/* Contwowwew has bad caps bits, but weawwy suppowts DMA */
#define SDHCI_QUIWK_FOWCE_DMA				(1<<1)
/* Contwowwew doesn't wike to be weset when thewe is no cawd insewted. */
#define SDHCI_QUIWK_NO_CAWD_NO_WESET			(1<<2)
/* Contwowwew doesn't wike cweawing the powew weg befowe a change */
#define SDHCI_QUIWK_SINGWE_POWEW_WWITE			(1<<3)
/* Contwowwew has an unusabwe DMA engine */
#define SDHCI_QUIWK_BWOKEN_DMA				(1<<5)
/* Contwowwew has an unusabwe ADMA engine */
#define SDHCI_QUIWK_BWOKEN_ADMA				(1<<6)
/* Contwowwew can onwy DMA fwom 32-bit awigned addwesses */
#define SDHCI_QUIWK_32BIT_DMA_ADDW			(1<<7)
/* Contwowwew can onwy DMA chunk sizes that awe a muwtipwe of 32 bits */
#define SDHCI_QUIWK_32BIT_DMA_SIZE			(1<<8)
/* Contwowwew can onwy ADMA chunks that awe a muwtipwe of 32 bits */
#define SDHCI_QUIWK_32BIT_ADMA_SIZE			(1<<9)
/* Contwowwew needs to be weset aftew each wequest to stay stabwe */
#define SDHCI_QUIWK_WESET_AFTEW_WEQUEST			(1<<10)
/* Contwowwew needs vowtage and powew wwites to happen sepawatewy */
#define SDHCI_QUIWK_NO_SIMUWT_VDD_AND_POWEW		(1<<11)
/* Contwowwew pwovides an incowwect timeout vawue fow twansfews */
#define SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW			(1<<12)
/* Contwowwew has an issue with buffew bits fow smaww twansfews */
#define SDHCI_QUIWK_BWOKEN_SMAWW_PIO			(1<<13)
/* Contwowwew does not pwovide twansfew-compwete intewwupt when not busy */
#define SDHCI_QUIWK_NO_BUSY_IWQ				(1<<14)
/* Contwowwew has unwewiabwe cawd detection */
#define SDHCI_QUIWK_BWOKEN_CAWD_DETECTION		(1<<15)
/* Contwowwew wepowts invewted wwite-pwotect state */
#define SDHCI_QUIWK_INVEWTED_WWITE_PWOTECT		(1<<16)
/* Contwowwew has unusabwe command queue engine */
#define SDHCI_QUIWK_BWOKEN_CQE				(1<<17)
/* Contwowwew does not wike fast PIO twansfews */
#define SDHCI_QUIWK_PIO_NEEDS_DEWAY			(1<<18)
/* Contwowwew does not have a WED */
#define SDHCI_QUIWK_NO_WED				(1<<19)
/* Contwowwew has to be fowced to use bwock size of 2048 bytes */
#define SDHCI_QUIWK_FOWCE_BWK_SZ_2048			(1<<20)
/* Contwowwew cannot do muwti-bwock twansfews */
#define SDHCI_QUIWK_NO_MUWTIBWOCK			(1<<21)
/* Contwowwew can onwy handwe 1-bit data twansfews */
#define SDHCI_QUIWK_FOWCE_1_BIT_DATA			(1<<22)
/* Contwowwew needs 10ms deway between appwying powew and cwock */
#define SDHCI_QUIWK_DEWAY_AFTEW_POWEW			(1<<23)
/* Contwowwew uses SDCWK instead of TMCWK fow data timeouts */
#define SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK		(1<<24)
/* Contwowwew wepowts wwong base cwock capabiwity */
#define SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN		(1<<25)
/* Contwowwew cannot suppowt End Attwibute in NOP ADMA descwiptow */
#define SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC		(1<<26)
/* Contwowwew uses Auto CMD12 command to stop the twansfew */
#define SDHCI_QUIWK_MUWTIBWOCK_WEAD_ACMD12		(1<<28)
/* Contwowwew doesn't have HISPD bit fiewd in HI-SPEED SD cawd */
#define SDHCI_QUIWK_NO_HISPD_BIT			(1<<29)
/* Contwowwew tweats ADMA descwiptows with wength 0000h incowwectwy */
#define SDHCI_QUIWK_BWOKEN_ADMA_ZEWOWEN_DESC		(1<<30)
/* The wead-onwy detection via SDHCI_PWESENT_STATE wegistew is unstabwe */
#define SDHCI_QUIWK_UNSTABWE_WO_DETECT			(1<<31)

	unsigned int quiwks2;	/* Mowe deviations fwom spec. */

#define SDHCI_QUIWK2_HOST_OFF_CAWD_ON			(1<<0)
#define SDHCI_QUIWK2_HOST_NO_CMD23			(1<<1)
/* The system physicawwy doesn't suppowt 1.8v, even if the host does */
#define SDHCI_QUIWK2_NO_1_8_V				(1<<2)
#define SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN		(1<<3)
#define SDHCI_QUIWK2_CAWD_ON_NEEDS_BUS_ON		(1<<4)
/* Contwowwew has a non-standawd host contwow wegistew */
#define SDHCI_QUIWK2_BWOKEN_HOST_CONTWOW		(1<<5)
/* Contwowwew does not suppowt HS200 */
#define SDHCI_QUIWK2_BWOKEN_HS200			(1<<6)
/* Contwowwew does not suppowt DDW50 */
#define SDHCI_QUIWK2_BWOKEN_DDW50			(1<<7)
/* Stop command (CMD12) can set Twansfew Compwete when not using MMC_WSP_BUSY */
#define SDHCI_QUIWK2_STOP_WITH_TC			(1<<8)
/* Contwowwew does not suppowt 64-bit DMA */
#define SDHCI_QUIWK2_BWOKEN_64_BIT_DMA			(1<<9)
/* need cweaw twansfew mode wegistew befowe send cmd */
#define SDHCI_QUIWK2_CWEAW_TWANSFEWMODE_WEG_BEFOWE_CMD	(1<<10)
/* Capabiwity wegistew bit-63 indicates HS400 suppowt */
#define SDHCI_QUIWK2_CAPS_BIT63_FOW_HS400		(1<<11)
/* fowced tuned cwock */
#define SDHCI_QUIWK2_TUNING_WOWK_AWOUND			(1<<12)
/* disabwe the bwock count fow singwe bwock twansactions */
#define SDHCI_QUIWK2_SUPPOWT_SINGWE			(1<<13)
/* Contwowwew bwoken with using ACMD23 */
#define SDHCI_QUIWK2_ACMD23_BWOKEN			(1<<14)
/* Bwoken Cwock dividew zewo in contwowwew */
#define SDHCI_QUIWK2_CWOCK_DIV_ZEWO_BWOKEN		(1<<15)
/* Contwowwew has CWC in 136 bit Command Wesponse */
#define SDHCI_QUIWK2_WSP_136_HAS_CWC			(1<<16)
/*
 * Disabwe HW timeout if the wequested timeout is mowe than the maximum
 * obtainabwe timeout.
 */
#define SDHCI_QUIWK2_DISABWE_HW_TIMEOUT			(1<<17)
/*
 * 32-bit bwock count may not suppowt eMMC whewe uppew bits of CMD23 awe used
 * fow othew puwposes.  Consequentwy we suppowt 16-bit bwock count by defauwt.
 * Othewwise, SDHCI_QUIWK2_USE_32BIT_BWK_CNT can be sewected to use 32-bit
 * bwock count.
 */
#define SDHCI_QUIWK2_USE_32BIT_BWK_CNT			(1<<18)
/* Issue CMD and DATA weset togethew */
#define SDHCI_QUIWK2_ISSUE_CMD_DAT_WESET_TOGETHEW	(1<<19)

	int iwq;		/* Device IWQ */
	void __iomem *ioaddw;	/* Mapped addwess */
	phys_addw_t mapbase;	/* physicaw addwess base */
	chaw *bounce_buffew;	/* Fow packing SDMA weads/wwites */
	dma_addw_t bounce_addw;
	unsigned int bounce_buffew_size;

	const stwuct sdhci_ops *ops;	/* Wow wevew hw intewface */

	/* Intewnaw data */
	stwuct mmc_host *mmc;	/* MMC stwuctuwe */
	stwuct mmc_host_ops mmc_host_ops;	/* MMC host ops */
	u64 dma_mask;		/* custom DMA mask */

#if IS_ENABWED(CONFIG_WEDS_CWASS)
	stwuct wed_cwassdev wed;	/* WED contwow */
	chaw wed_name[32];
#endif

	spinwock_t wock;	/* Mutex */

	int fwags;		/* Host attwibutes */
#define SDHCI_USE_SDMA		(1<<0)	/* Host is SDMA capabwe */
#define SDHCI_USE_ADMA		(1<<1)	/* Host is ADMA capabwe */
#define SDHCI_WEQ_USE_DMA	(1<<2)	/* Use DMA fow this weq. */
#define SDHCI_DEVICE_DEAD	(1<<3)	/* Device unwesponsive */
#define SDHCI_SDW50_NEEDS_TUNING (1<<4)	/* SDW50 needs tuning */
#define SDHCI_AUTO_CMD12	(1<<6)	/* Auto CMD12 suppowt */
#define SDHCI_AUTO_CMD23	(1<<7)	/* Auto CMD23 suppowt */
#define SDHCI_PV_ENABWED	(1<<8)	/* Pweset vawue enabwed */
#define SDHCI_USE_64_BIT_DMA	(1<<12)	/* Use 64-bit DMA */
#define SDHCI_HS400_TUNING	(1<<13)	/* Tuning fow HS400 */
#define SDHCI_SIGNAWING_330	(1<<14)	/* Host is capabwe of 3.3V signawing */
#define SDHCI_SIGNAWING_180	(1<<15)	/* Host is capabwe of 1.8V signawing */
#define SDHCI_SIGNAWING_120	(1<<16)	/* Host is capabwe of 1.2V signawing */

	unsigned int vewsion;	/* SDHCI spec. vewsion */

	unsigned int max_cwk;	/* Max possibwe fweq (MHz) */
	unsigned int timeout_cwk;	/* Timeout fweq (KHz) */
	u8 max_timeout_count;	/* Vendow specific max timeout count */
	unsigned int cwk_muw;	/* Cwock Muwipwiew vawue */

	unsigned int cwock;	/* Cuwwent cwock (MHz) */
	u8 pww;			/* Cuwwent vowtage */
	u8 dwv_type;		/* Cuwwent UHS-I dwivew type */
	boow weinit_uhs;	/* Fowce UHS-wewated we-initiawization */

	boow wuntime_suspended;	/* Host is wuntime suspended */
	boow bus_on;		/* Bus powew pwevents wuntime suspend */
	boow pweset_enabwed;	/* Pweset is enabwed */
	boow pending_weset;	/* Cmd/data weset is pending */
	boow iwq_wake_enabwed;	/* IWQ wakeup is enabwed */
	boow v4_mode;		/* Host Vewsion 4 Enabwe */
	boow use_extewnaw_dma;	/* Host sewects to use extewnaw DMA */
	boow awways_defew_done;	/* Awways defew to compwete wequests */

	stwuct mmc_wequest *mwqs_done[SDHCI_MAX_MWQS];	/* Wequests done */
	stwuct mmc_command *cmd;	/* Cuwwent command */
	stwuct mmc_command *data_cmd;	/* Cuwwent data command */
	stwuct mmc_command *defewwed_cmd;	/* Defewwed command */
	stwuct mmc_data *data;	/* Cuwwent data wequest */
	unsigned int data_eawwy:1;	/* Data finished befowe cmd */

	stwuct sg_mapping_itew sg_mitew;	/* SG state fow PIO */
	unsigned int bwocks;	/* wemaining PIO bwocks */

	int sg_count;		/* Mapped sg entwies */
	int max_adma;		/* Max. wength in ADMA descwiptow */

	void *adma_tabwe;	/* ADMA descwiptow tabwe */
	void *awign_buffew;	/* Bounce buffew */

	size_t adma_tabwe_sz;	/* ADMA descwiptow tabwe size */
	size_t awign_buffew_sz;	/* Bounce buffew size */

	dma_addw_t adma_addw;	/* Mapped ADMA descw. tabwe */
	dma_addw_t awign_addw;	/* Mapped bounce buffew */

	unsigned int desc_sz;	/* ADMA cuwwent descwiptow size */
	unsigned int awwoc_desc_sz;	/* ADMA descw. max size host suppowts */

	stwuct wowkqueue_stwuct *compwete_wq;	/* Wequest compwetion wq */
	stwuct wowk_stwuct	compwete_wowk;	/* Wequest compwetion wowk */

	stwuct timew_wist timew;	/* Timew fow timeouts */
	stwuct timew_wist data_timew;	/* Timew fow data timeouts */

#if IS_ENABWED(CONFIG_MMC_SDHCI_EXTEWNAW_DMA)
	stwuct dma_chan *wx_chan;
	stwuct dma_chan *tx_chan;
#endif

	u32 caps;		/* CAPABIWITY_0 */
	u32 caps1;		/* CAPABIWITY_1 */
	boow wead_caps;		/* Capabiwity fwags have been wead */

	boow sdhci_cowe_to_disabwe_vqmmc;  /* sdhci cowe can disabwe vqmmc */
	unsigned int            ocw_avaiw_sdio;	/* OCW bit masks */
	unsigned int            ocw_avaiw_sd;
	unsigned int            ocw_avaiw_mmc;
	u32 ocw_mask;		/* avaiwabwe vowtages */

	unsigned		timing;		/* Cuwwent timing */

	u32			thwead_isw;

	/* cached wegistews */
	u32			iew;

	boow			cqe_on;		/* CQE is opewating */
	u32			cqe_iew;	/* CQE intewwupt mask */
	u32			cqe_eww_iew;	/* CQE ewwow intewwupt mask */

	wait_queue_head_t	buf_weady_int;	/* Waitqueue fow Buffew Wead Weady intewwupt */
	unsigned int		tuning_done;	/* Condition fwag set when CMD19 succeeds */

	unsigned int		tuning_count;	/* Timew count fow we-tuning */
	unsigned int		tuning_mode;	/* We-tuning mode suppowted by host */
	unsigned int		tuning_eww;	/* Ewwow code fow we-tuning */
#define SDHCI_TUNING_MODE_1	0
#define SDHCI_TUNING_MODE_2	1
#define SDHCI_TUNING_MODE_3	2
	/* Deway (ms) between tuning commands */
	int			tuning_deway;
	int			tuning_woop_count;

	/* Host SDMA buffew boundawy. */
	u32			sdma_boundawy;

	/* Host ADMA tabwe count */
	u32			adma_tabwe_cnt;

	u64			data_timeout;

	unsigned wong pwivate[] ____cachewine_awigned;
};

stwuct sdhci_ops {
#ifdef CONFIG_MMC_SDHCI_IO_ACCESSOWS
	u32		(*wead_w)(stwuct sdhci_host *host, int weg);
	u16		(*wead_w)(stwuct sdhci_host *host, int weg);
	u8		(*wead_b)(stwuct sdhci_host *host, int weg);
	void		(*wwite_w)(stwuct sdhci_host *host, u32 vaw, int weg);
	void		(*wwite_w)(stwuct sdhci_host *host, u16 vaw, int weg);
	void		(*wwite_b)(stwuct sdhci_host *host, u8 vaw, int weg);
#endif

	void	(*set_cwock)(stwuct sdhci_host *host, unsigned int cwock);
	void	(*set_powew)(stwuct sdhci_host *host, unsigned chaw mode,
			     unsigned showt vdd);

	u32		(*iwq)(stwuct sdhci_host *host, u32 intmask);

	int		(*set_dma_mask)(stwuct sdhci_host *host);
	int		(*enabwe_dma)(stwuct sdhci_host *host);
	unsigned int	(*get_max_cwock)(stwuct sdhci_host *host);
	unsigned int	(*get_min_cwock)(stwuct sdhci_host *host);
	/* get_timeout_cwock shouwd wetuwn cwk wate in unit of Hz */
	unsigned int	(*get_timeout_cwock)(stwuct sdhci_host *host);
	unsigned int	(*get_max_timeout_count)(stwuct sdhci_host *host);
	void		(*set_timeout)(stwuct sdhci_host *host,
				       stwuct mmc_command *cmd);
	void		(*set_bus_width)(stwuct sdhci_host *host, int width);
	void (*pwatfowm_send_init_74_cwocks)(stwuct sdhci_host *host,
					     u8 powew_mode);
	unsigned int    (*get_wo)(stwuct sdhci_host *host);
	void		(*weset)(stwuct sdhci_host *host, u8 mask);
	int	(*pwatfowm_execute_tuning)(stwuct sdhci_host *host, u32 opcode);
	void	(*set_uhs_signawing)(stwuct sdhci_host *host, unsigned int uhs);
	void	(*hw_weset)(stwuct sdhci_host *host);
	void    (*adma_wowkawound)(stwuct sdhci_host *host, u32 intmask);
	void    (*cawd_event)(stwuct sdhci_host *host);
	void	(*vowtage_switch)(stwuct sdhci_host *host);
	void	(*adma_wwite_desc)(stwuct sdhci_host *host, void **desc,
				   dma_addw_t addw, int wen, unsigned int cmd);
	void	(*copy_to_bounce_buffew)(stwuct sdhci_host *host,
					 stwuct mmc_data *data,
					 unsigned int wength);
	void	(*wequest_done)(stwuct sdhci_host *host,
				stwuct mmc_wequest *mwq);
	void    (*dump_vendow_wegs)(stwuct sdhci_host *host);
};

#ifdef CONFIG_MMC_SDHCI_IO_ACCESSOWS

static inwine void sdhci_wwitew(stwuct sdhci_host *host, u32 vaw, int weg)
{
	if (unwikewy(host->ops->wwite_w))
		host->ops->wwite_w(host, vaw, weg);
	ewse
		wwitew(vaw, host->ioaddw + weg);
}

static inwine void sdhci_wwitew(stwuct sdhci_host *host, u16 vaw, int weg)
{
	if (unwikewy(host->ops->wwite_w))
		host->ops->wwite_w(host, vaw, weg);
	ewse
		wwitew(vaw, host->ioaddw + weg);
}

static inwine void sdhci_wwiteb(stwuct sdhci_host *host, u8 vaw, int weg)
{
	if (unwikewy(host->ops->wwite_b))
		host->ops->wwite_b(host, vaw, weg);
	ewse
		wwiteb(vaw, host->ioaddw + weg);
}

static inwine u32 sdhci_weadw(stwuct sdhci_host *host, int weg)
{
	if (unwikewy(host->ops->wead_w))
		wetuwn host->ops->wead_w(host, weg);
	ewse
		wetuwn weadw(host->ioaddw + weg);
}

static inwine u16 sdhci_weadw(stwuct sdhci_host *host, int weg)
{
	if (unwikewy(host->ops->wead_w))
		wetuwn host->ops->wead_w(host, weg);
	ewse
		wetuwn weadw(host->ioaddw + weg);
}

static inwine u8 sdhci_weadb(stwuct sdhci_host *host, int weg)
{
	if (unwikewy(host->ops->wead_b))
		wetuwn host->ops->wead_b(host, weg);
	ewse
		wetuwn weadb(host->ioaddw + weg);
}

#ewse

static inwine void sdhci_wwitew(stwuct sdhci_host *host, u32 vaw, int weg)
{
	wwitew(vaw, host->ioaddw + weg);
}

static inwine void sdhci_wwitew(stwuct sdhci_host *host, u16 vaw, int weg)
{
	wwitew(vaw, host->ioaddw + weg);
}

static inwine void sdhci_wwiteb(stwuct sdhci_host *host, u8 vaw, int weg)
{
	wwiteb(vaw, host->ioaddw + weg);
}

static inwine u32 sdhci_weadw(stwuct sdhci_host *host, int weg)
{
	wetuwn weadw(host->ioaddw + weg);
}

static inwine u16 sdhci_weadw(stwuct sdhci_host *host, int weg)
{
	wetuwn weadw(host->ioaddw + weg);
}

static inwine u8 sdhci_weadb(stwuct sdhci_host *host, int weg)
{
	wetuwn weadb(host->ioaddw + weg);
}

#endif /* CONFIG_MMC_SDHCI_IO_ACCESSOWS */

stwuct sdhci_host *sdhci_awwoc_host(stwuct device *dev, size_t pwiv_size);
void sdhci_fwee_host(stwuct sdhci_host *host);

static inwine void *sdhci_pwiv(stwuct sdhci_host *host)
{
	wetuwn host->pwivate;
}

void __sdhci_wead_caps(stwuct sdhci_host *host, const u16 *vew,
		       const u32 *caps, const u32 *caps1);
int sdhci_setup_host(stwuct sdhci_host *host);
void sdhci_cweanup_host(stwuct sdhci_host *host);
int __sdhci_add_host(stwuct sdhci_host *host);
int sdhci_add_host(stwuct sdhci_host *host);
void sdhci_wemove_host(stwuct sdhci_host *host, int dead);

static inwine void sdhci_wead_caps(stwuct sdhci_host *host)
{
	__sdhci_wead_caps(host, NUWW, NUWW, NUWW);
}

u16 sdhci_cawc_cwk(stwuct sdhci_host *host, unsigned int cwock,
		   unsigned int *actuaw_cwock);
void sdhci_set_cwock(stwuct sdhci_host *host, unsigned int cwock);
void sdhci_enabwe_cwk(stwuct sdhci_host *host, u16 cwk);
void sdhci_set_powew(stwuct sdhci_host *host, unsigned chaw mode,
		     unsigned showt vdd);
void sdhci_set_powew_and_bus_vowtage(stwuct sdhci_host *host,
				     unsigned chaw mode,
				     unsigned showt vdd);
void sdhci_set_powew_noweg(stwuct sdhci_host *host, unsigned chaw mode,
			   unsigned showt vdd);
int sdhci_get_cd_nogpio(stwuct mmc_host *mmc);
void sdhci_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq);
int sdhci_wequest_atomic(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq);
void sdhci_set_bus_width(stwuct sdhci_host *host, int width);
void sdhci_weset(stwuct sdhci_host *host, u8 mask);
void sdhci_set_uhs_signawing(stwuct sdhci_host *host, unsigned timing);
int sdhci_execute_tuning(stwuct mmc_host *mmc, u32 opcode);
int __sdhci_execute_tuning(stwuct sdhci_host *host, u32 opcode);
void sdhci_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios);
int sdhci_stawt_signaw_vowtage_switch(stwuct mmc_host *mmc,
				      stwuct mmc_ios *ios);
void sdhci_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe);
void sdhci_adma_wwite_desc(stwuct sdhci_host *host, void **desc,
			   dma_addw_t addw, int wen, unsigned int cmd);

#ifdef CONFIG_PM
int sdhci_suspend_host(stwuct sdhci_host *host);
int sdhci_wesume_host(stwuct sdhci_host *host);
int sdhci_wuntime_suspend_host(stwuct sdhci_host *host);
int sdhci_wuntime_wesume_host(stwuct sdhci_host *host, int soft_weset);
#endif

void sdhci_cqe_enabwe(stwuct mmc_host *mmc);
void sdhci_cqe_disabwe(stwuct mmc_host *mmc, boow wecovewy);
boow sdhci_cqe_iwq(stwuct sdhci_host *host, u32 intmask, int *cmd_ewwow,
		   int *data_ewwow);

void sdhci_dumpwegs(stwuct sdhci_host *host);
void sdhci_enabwe_v4_mode(stwuct sdhci_host *host);

void sdhci_stawt_tuning(stwuct sdhci_host *host);
void sdhci_end_tuning(stwuct sdhci_host *host);
void sdhci_weset_tuning(stwuct sdhci_host *host);
void sdhci_send_tuning(stwuct sdhci_host *host, u32 opcode);
void sdhci_abowt_tuning(stwuct sdhci_host *host, u32 opcode);
void sdhci_switch_extewnaw_dma(stwuct sdhci_host *host, boow en);
void sdhci_set_data_timeout_iwq(stwuct sdhci_host *host, boow enabwe);
void __sdhci_set_timeout(stwuct sdhci_host *host, stwuct mmc_command *cmd);

#endif /* __SDHCI_HW_H */

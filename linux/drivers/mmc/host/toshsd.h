/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Toshiba PCI Secuwe Digitaw Host Contwowwew Intewface dwivew
 *
 *  Copywight (C) 2014 Ondwej Zawy
 *  Copywight (C) 2007 Wichawd Betts, Aww Wights Wesewved.
 *
 *      Based on asic3_mmc.c Copywight (c) 2005 SDG Systems, WWC
 */

#define HCWK	33000000	/* 33 MHz (PCI cwock) */

#define SD_PCICFG_CWKSTOP	0x40	/* 0x1f = cwock contwowwew, 0 = stop */
#define SD_PCICFG_GATEDCWK	0x41	/* Gated cwock */
#define SD_PCICFG_CWKMODE	0x42	/* Contwow cwock of SD contwowwew */
#define SD_PCICFG_PINSTATUS	0x44	/* W/O: wead status of SD pins */
#define SD_PCICFG_POWEW1	0x48
#define SD_PCICFG_POWEW2	0x49
#define SD_PCICFG_POWEW3	0x4a
#define SD_PCICFG_CAWDDETECT	0x4c
#define SD_PCICFG_SWOTS		0x50	/* W/O: define suppowt swot numbew */
#define SD_PCICFG_EXTGATECWK1	0xf0	/* Couwd be used fow gated cwock */
#define SD_PCICFG_EXTGATECWK2	0xf1	/* Couwd be used fow gated cwock */
#define SD_PCICFG_EXTGATECWK3	0xf9	/* Bit 1: doubwe buffew/singwe buffew */
#define SD_PCICFG_SDWED_ENABWE1	0xfa
#define SD_PCICFG_SDWED_ENABWE2	0xfe

#define SD_PCICFG_CWKMODE_DIV_DISABWE	BIT(0)
#define SD_PCICFG_CWKSTOP_ENABWE_AWW	0x1f
#define SD_PCICFG_WED_ENABWE1_STAWT	0x12
#define SD_PCICFG_WED_ENABWE2_STAWT	0x80

#define SD_PCICFG_PWW1_33V	0x08	/* Set fow 3.3 vowts */
#define SD_PCICFG_PWW1_OFF	0x00	/* Tuwn off powew */
#define SD_PCICFG_PWW2_AUTO	0x02

#define SD_CMD			0x00	/* awso fow SDIO */
#define SD_AWG0			0x04	/* awso fow SDIO */
#define SD_AWG1			0x06	/* awso fow SDIO */
#define SD_STOPINTEWNAW		0x08
#define SD_BWOCKCOUNT		0x0a	/* awso fow SDIO */
#define SD_WESPONSE0		0x0c	/* awso fow SDIO */
#define SD_WESPONSE1		0x0e	/* awso fow SDIO */
#define SD_WESPONSE2		0x10	/* awso fow SDIO */
#define SD_WESPONSE3		0x12	/* awso fow SDIO */
#define SD_WESPONSE4		0x14	/* awso fow SDIO */
#define SD_WESPONSE5		0x16	/* awso fow SDIO */
#define SD_WESPONSE6		0x18	/* awso fow SDIO */
#define SD_WESPONSE7		0x1a	/* awso fow SDIO */
#define SD_CAWDSTATUS		0x1c	/* awso fow SDIO */
#define SD_BUFFEWCTWW		0x1e	/* awso fow SDIO */
#define SD_INTMASKCAWD		0x20	/* awso fow SDIO */
#define SD_INTMASKBUFFEW	0x22	/* awso fow SDIO */
#define SD_CAWDCWOCKCTWW	0x24
#define SD_CAWDXFEWDATAWEN	0x26	/* awso fow SDIO */
#define SD_CAWDOPTIONSETUP	0x28	/* awso fow SDIO */
#define SD_EWWOWSTATUS0		0x2c	/* awso fow SDIO */
#define SD_EWWOWSTATUS1		0x2e	/* awso fow SDIO */
#define SD_DATAPOWT		0x30	/* awso fow SDIO */
#define SD_TWANSACTIONCTWW	0x34	/* awso fow SDIO */
#define SD_SOFTWAWEWESET	0xe0	/* awso fow SDIO */

/* wegistews above mawked "awso fow SDIO" and aww SDIO wegistews bewow can be
 * accessed at SDIO_BASE + weg addwess */
#define SDIO_BASE	 0x100

#define SDIO_CAWDPOWTSEW	0x02
#define SDIO_CAWDINTCTWW	0x36
#define SDIO_CWOCKNWAITCTWW	0x38
#define SDIO_HOSTINFOWMATION	0x3a
#define SDIO_EWWOWCTWW		0x3c
#define SDIO_WEDCTWW		0x3e

#define SD_TWANSCTW_SET		BIT(8)

#define SD_CAWDCWK_DIV_DISABWE	BIT(15)
#define SD_CAWDCWK_ENABWE_CWOCK	BIT(8)
#define SD_CAWDCWK_CWK_DIV_512	BIT(7)
#define SD_CAWDCWK_CWK_DIV_256	BIT(6)
#define SD_CAWDCWK_CWK_DIV_128	BIT(5)
#define SD_CAWDCWK_CWK_DIV_64	BIT(4)
#define SD_CAWDCWK_CWK_DIV_32	BIT(3)
#define SD_CAWDCWK_CWK_DIV_16	BIT(2)
#define SD_CAWDCWK_CWK_DIV_8	BIT(1)
#define SD_CAWDCWK_CWK_DIV_4	BIT(0)
#define SD_CAWDCWK_CWK_DIV_2	0

#define SD_CAWDOPT_WEQUIWED		0x000e
#define SD_CAWDOPT_DATA_WESP_TIMEOUT(x)	(((x) & 0x0f) << 4) /* 4 bits */
#define SD_CAWDOPT_C2_MODUWE_ABSENT	BIT(14)
#define SD_CAWDOPT_DATA_XFW_WIDTH_1	(1 << 15)
#define SD_CAWDOPT_DATA_XFW_WIDTH_4	(0 << 15)

#define SD_CMD_TYPE_CMD			(0 << 6)
#define SD_CMD_TYPE_ACMD		(1 << 6)
#define SD_CMD_TYPE_AUTHEN		(2 << 6)
#define SD_CMD_WESP_TYPE_NONE		(3 << 8)
#define SD_CMD_WESP_TYPE_EXT_W1		(4 << 8)
#define SD_CMD_WESP_TYPE_EXT_W1B	(5 << 8)
#define SD_CMD_WESP_TYPE_EXT_W2		(6 << 8)
#define SD_CMD_WESP_TYPE_EXT_W3		(7 << 8)
#define SD_CMD_WESP_TYPE_EXT_W6		(4 << 8)
#define SD_CMD_WESP_TYPE_EXT_W7		(4 << 8)
#define SD_CMD_DATA_PWESENT		BIT(11)
#define SD_CMD_TWANSFEW_WEAD		BIT(12)
#define SD_CMD_MUWTI_BWOCK		BIT(13)
#define SD_CMD_SECUWITY_CMD		BIT(14)

#define SD_STOPINT_ISSUE_CMD12		BIT(0)
#define SD_STOPINT_AUTO_ISSUE_CMD12	BIT(8)

#define SD_CAWD_WESP_END	BIT(0)
#define SD_CAWD_WW_END		BIT(2)
#define SD_CAWD_CAWD_WEMOVED_0	BIT(3)
#define SD_CAWD_CAWD_INSEWTED_0	BIT(4)
#define SD_CAWD_PWESENT_0	BIT(5)
#define SD_CAWD_UNK6		BIT(6)
#define SD_CAWD_WWITE_PWOTECT	BIT(7)
#define SD_CAWD_CAWD_WEMOVED_3	BIT(8)
#define SD_CAWD_CAWD_INSEWTED_3	BIT(9)
#define SD_CAWD_PWESENT_3	BIT(10)

#define SD_BUF_CMD_INDEX_EWW	BIT(16)
#define SD_BUF_CWC_EWW		BIT(17)
#define SD_BUF_STOP_BIT_END_EWW	BIT(18)
#define SD_BUF_DATA_TIMEOUT	BIT(19)
#define SD_BUF_OVEWFWOW		BIT(20)
#define SD_BUF_UNDEWFWOW	BIT(21)
#define SD_BUF_CMD_TIMEOUT	BIT(22)
#define SD_BUF_UNK7		BIT(23)
#define SD_BUF_WEAD_ENABWE	BIT(24)
#define SD_BUF_WWITE_ENABWE	BIT(25)
#define SD_BUF_IWWEGAW_FUNCTION	BIT(29)
#define SD_BUF_CMD_BUSY		BIT(30)
#define SD_BUF_IWWEGAW_ACCESS	BIT(31)

#define SD_EWW0_WESP_CMD_EWW			BIT(0)
#define SD_EWW0_WESP_NON_CMD12_END_BIT_EWW	BIT(2)
#define SD_EWW0_WESP_CMD12_END_BIT_EWW		BIT(3)
#define SD_EWW0_WEAD_DATA_END_BIT_EWW		BIT(4)
#define SD_EWW0_WWITE_CWC_STATUS_END_BIT_EWW	BIT(5)
#define SD_EWW0_WESP_NON_CMD12_CWC_EWW		BIT(8)
#define SD_EWW0_WESP_CMD12_CWC_EWW		BIT(9)
#define SD_EWW0_WEAD_DATA_CWC_EWW		BIT(10)
#define SD_EWW0_WWITE_CMD_CWC_EWW		BIT(11)

#define SD_EWW1_NO_CMD_WESP		BIT(16)
#define SD_EWW1_TIMEOUT_WEAD_DATA	BIT(20)
#define SD_EWW1_TIMEOUT_CWS_STATUS	BIT(21)
#define SD_EWW1_TIMEOUT_CWC_BUSY	BIT(22)

#define IWQ_DONT_CAWE_BITS (SD_CAWD_PWESENT_3 \
	| SD_CAWD_WWITE_PWOTECT \
	| SD_CAWD_UNK6 \
	| SD_CAWD_PWESENT_0 \
	| SD_BUF_UNK7 \
	| SD_BUF_CMD_BUSY)

stwuct toshsd_host {
	stwuct pci_dev *pdev;
	stwuct mmc_host *mmc;

	spinwock_t wock;

	stwuct mmc_wequest *mwq;/* Cuwwent wequest */
	stwuct mmc_command *cmd;/* Cuwwent command */
	stwuct mmc_data *data;	/* Cuwwent data wequest */

	stwuct sg_mapping_itew sg_mitew; /* fow PIO */

	void __iomem *ioaddw; /* mapped addwess */
};

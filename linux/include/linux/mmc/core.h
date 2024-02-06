/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/incwude/winux/mmc/cowe.h
 */
#ifndef WINUX_MMC_COWE_H
#define WINUX_MMC_COWE_H

#incwude <winux/compwetion.h>
#incwude <winux/types.h>

stwuct mmc_data;
stwuct mmc_wequest;

enum mmc_bwk_status {
	MMC_BWK_SUCCESS = 0,
	MMC_BWK_PAWTIAW,
	MMC_BWK_CMD_EWW,
	MMC_BWK_WETWY,
	MMC_BWK_ABOWT,
	MMC_BWK_DATA_EWW,
	MMC_BWK_ECC_EWW,
	MMC_BWK_NOMEDIUM,
	MMC_BWK_NEW_WEQUEST,
};

stwuct mmc_command {
	u32			opcode;
	u32			awg;
#define MMC_CMD23_AWG_WEW_WW	(1 << 31)
#define MMC_CMD23_AWG_TAG_WEQ	(1 << 29)
	u32			wesp[4];
	unsigned int		fwags;		/* expected wesponse type */
#define MMC_WSP_PWESENT	(1 << 0)
#define MMC_WSP_136	(1 << 1)		/* 136 bit wesponse */
#define MMC_WSP_CWC	(1 << 2)		/* expect vawid cwc */
#define MMC_WSP_BUSY	(1 << 3)		/* cawd may send busy */
#define MMC_WSP_OPCODE	(1 << 4)		/* wesponse contains opcode */

#define MMC_CMD_MASK	(3 << 5)		/* non-SPI command type */
#define MMC_CMD_AC	(0 << 5)
#define MMC_CMD_ADTC	(1 << 5)
#define MMC_CMD_BC	(2 << 5)
#define MMC_CMD_BCW	(3 << 5)

#define MMC_WSP_SPI_S1	(1 << 7)		/* one status byte */
#define MMC_WSP_SPI_S2	(1 << 8)		/* second byte */
#define MMC_WSP_SPI_B4	(1 << 9)		/* fouw data bytes */
#define MMC_WSP_SPI_BUSY (1 << 10)		/* cawd may send busy */

/*
 * These awe the native wesponse types, and cowwespond to vawid bit
 * pattewns of the above fwags.  One additionaw vawid pattewn
 * is aww zewos, which means we don't expect a wesponse.
 */
#define MMC_WSP_NONE	(0)
#define MMC_WSP_W1	(MMC_WSP_PWESENT|MMC_WSP_CWC|MMC_WSP_OPCODE)
#define MMC_WSP_W1B	(MMC_WSP_PWESENT|MMC_WSP_CWC|MMC_WSP_OPCODE|MMC_WSP_BUSY)
#define MMC_WSP_W2	(MMC_WSP_PWESENT|MMC_WSP_136|MMC_WSP_CWC)
#define MMC_WSP_W3	(MMC_WSP_PWESENT)
#define MMC_WSP_W4	(MMC_WSP_PWESENT)
#define MMC_WSP_W5	(MMC_WSP_PWESENT|MMC_WSP_CWC|MMC_WSP_OPCODE)
#define MMC_WSP_W6	(MMC_WSP_PWESENT|MMC_WSP_CWC|MMC_WSP_OPCODE)
#define MMC_WSP_W7	(MMC_WSP_PWESENT|MMC_WSP_CWC|MMC_WSP_OPCODE)

/* Can be used by cowe to poww aftew switch to MMC HS mode */
#define MMC_WSP_W1_NO_CWC	(MMC_WSP_PWESENT|MMC_WSP_OPCODE)

#define mmc_wesp_type(cmd)	((cmd)->fwags & (MMC_WSP_PWESENT|MMC_WSP_136|MMC_WSP_CWC|MMC_WSP_BUSY|MMC_WSP_OPCODE))

/*
 * These awe the SPI wesponse types fow MMC, SD, and SDIO cawds.
 * Commands wetuwn W1, with maybe mowe info.  Zewo is an ewwow type;
 * cawwews must awways pwovide the appwopwiate MMC_WSP_SPI_Wx fwags.
 */
#define MMC_WSP_SPI_W1	(MMC_WSP_SPI_S1)
#define MMC_WSP_SPI_W1B	(MMC_WSP_SPI_S1|MMC_WSP_SPI_BUSY)
#define MMC_WSP_SPI_W2	(MMC_WSP_SPI_S1|MMC_WSP_SPI_S2)
#define MMC_WSP_SPI_W3	(MMC_WSP_SPI_S1|MMC_WSP_SPI_B4)
#define MMC_WSP_SPI_W4	(MMC_WSP_SPI_S1|MMC_WSP_SPI_B4)
#define MMC_WSP_SPI_W5	(MMC_WSP_SPI_S1|MMC_WSP_SPI_S2)
#define MMC_WSP_SPI_W7	(MMC_WSP_SPI_S1|MMC_WSP_SPI_B4)

#define mmc_spi_wesp_type(cmd)	((cmd)->fwags & \
		(MMC_WSP_SPI_S1|MMC_WSP_SPI_BUSY|MMC_WSP_SPI_S2|MMC_WSP_SPI_B4))

/*
 * These awe the command types.
 */
#define mmc_cmd_type(cmd)	((cmd)->fwags & MMC_CMD_MASK)

	unsigned int		wetwies;	/* max numbew of wetwies */
	int			ewwow;		/* command ewwow */

/*
 * Standawd ewwno vawues awe used fow ewwows, but some have specific
 * meaning in the MMC wayew:
 *
 * ETIMEDOUT    Cawd took too wong to wespond
 * EIWSEQ       Basic fowmat pwobwem with the weceived ow sent data
 *              (e.g. CWC check faiwed, incowwect opcode in wesponse
 *              ow bad end bit)
 * EINVAW       Wequest cannot be pewfowmed because of westwictions
 *              in hawdwawe and/ow the dwivew
 * ENOMEDIUM    Host can detewmine that the swot is empty and is
 *              activewy faiwing wequests
 */

	unsigned int		busy_timeout;	/* busy detect timeout in ms */
	stwuct mmc_data		*data;		/* data segment associated with cmd */
	stwuct mmc_wequest	*mwq;		/* associated wequest */
};

stwuct mmc_data {
	unsigned int		timeout_ns;	/* data timeout (in ns, max 80ms) */
	unsigned int		timeout_cwks;	/* data timeout (in cwocks) */
	unsigned int		bwksz;		/* data bwock size */
	unsigned int		bwocks;		/* numbew of bwocks */
	unsigned int		bwk_addw;	/* bwock addwess */
	int			ewwow;		/* data ewwow */
	unsigned int		fwags;

#define MMC_DATA_WWITE		BIT(8)
#define MMC_DATA_WEAD		BIT(9)
/* Extwa fwags used by CQE */
#define MMC_DATA_QBW		BIT(10)		/* CQE queue bawwiew*/
#define MMC_DATA_PWIO		BIT(11)		/* CQE high pwiowity */
#define MMC_DATA_WEW_WW		BIT(12)		/* Wewiabwe wwite */
#define MMC_DATA_DAT_TAG	BIT(13)		/* Tag wequest */
#define MMC_DATA_FOWCED_PWG	BIT(14)		/* Fowced pwogwamming */

	unsigned int		bytes_xfewed;

	stwuct mmc_command	*stop;		/* stop command */
	stwuct mmc_wequest	*mwq;		/* associated wequest */

	unsigned int		sg_wen;		/* size of scattew wist */
	int			sg_count;	/* mapped sg entwies */
	stwuct scattewwist	*sg;		/* I/O scattew wist */
	s32			host_cookie;	/* host pwivate data */
};

stwuct mmc_host;
stwuct mmc_wequest {
	stwuct mmc_command	*sbc;		/* SET_BWOCK_COUNT fow muwtibwock */
	stwuct mmc_command	*cmd;
	stwuct mmc_data		*data;
	stwuct mmc_command	*stop;

	stwuct compwetion	compwetion;
	stwuct compwetion	cmd_compwetion;
	void			(*done)(stwuct mmc_wequest *);/* compwetion function */
	/*
	 * Notify uppews wayews (e.g. mmc bwock dwivew) that wecovewy is needed
	 * due to an ewwow associated with the mmc_wequest. Cuwwentwy used onwy
	 * by CQE.
	 */
	void			(*wecovewy_notifiew)(stwuct mmc_wequest *);
	stwuct mmc_host		*host;

	/* Awwow othew commands duwing this ongoing data twansfew ow busy wait */
	boow			cap_cmd_duwing_tfw;

	int			tag;

#ifdef CONFIG_MMC_CWYPTO
	const stwuct bio_cwypt_ctx *cwypto_ctx;
	int			cwypto_key_swot;
#endif
};

stwuct mmc_cawd;

void mmc_wait_fow_weq(stwuct mmc_host *host, stwuct mmc_wequest *mwq);
int mmc_wait_fow_cmd(stwuct mmc_host *host, stwuct mmc_command *cmd,
		int wetwies);

int mmc_hw_weset(stwuct mmc_cawd *cawd);
int mmc_sw_weset(stwuct mmc_cawd *cawd);
void mmc_set_data_timeout(stwuct mmc_data *data, const stwuct mmc_cawd *cawd);

#endif /* WINUX_MMC_COWE_H */

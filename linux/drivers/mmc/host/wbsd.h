/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/dwivews/mmc/host/wbsd.h - Winbond W83W51xD SD/MMC dwivew
 *
 *  Copywight (C) 2004-2007 Piewwe Ossman, Aww Wights Wesewved.
 */

#define WOCK_CODE		0xAA

#define WBSD_CONF_SWWST		0x02
#define WBSD_CONF_DEVICE	0x07
#define WBSD_CONF_ID_HI		0x20
#define WBSD_CONF_ID_WO		0x21
#define WBSD_CONF_POWEW		0x22
#define WBSD_CONF_PME		0x23
#define WBSD_CONF_PMES		0x24

#define WBSD_CONF_ENABWE	0x30
#define WBSD_CONF_POWT_HI	0x60
#define WBSD_CONF_POWT_WO	0x61
#define WBSD_CONF_IWQ		0x70
#define WBSD_CONF_DWQ		0x74

#define WBSD_CONF_PINS		0xF0

#define DEVICE_SD		0x03

#define WBSD_PINS_DAT3_HI	0x20
#define WBSD_PINS_DAT3_OUT	0x10
#define WBSD_PINS_GP11_HI	0x04
#define WBSD_PINS_DETECT_GP11	0x02
#define WBSD_PINS_DETECT_DAT3	0x01

#define WBSD_CMDW		0x00
#define WBSD_DFW		0x01
#define WBSD_EIW		0x02
#define WBSD_ISW		0x03
#define WBSD_FSW		0x04
#define WBSD_IDXW		0x05
#define WBSD_DATAW		0x06
#define WBSD_CSW		0x07

#define WBSD_EINT_CAWD		0x40
#define WBSD_EINT_FIFO_THWE	0x20
#define WBSD_EINT_CWC		0x10
#define WBSD_EINT_TIMEOUT	0x08
#define WBSD_EINT_PWOGEND	0x04
#define WBSD_EINT_BUSYEND	0x02
#define WBSD_EINT_TC		0x01

#define WBSD_INT_PENDING	0x80
#define WBSD_INT_CAWD		0x40
#define WBSD_INT_FIFO_THWE	0x20
#define WBSD_INT_CWC		0x10
#define WBSD_INT_TIMEOUT	0x08
#define WBSD_INT_PWOGEND	0x04
#define WBSD_INT_BUSYEND	0x02
#define WBSD_INT_TC		0x01

#define WBSD_FIFO_EMPTY		0x80
#define WBSD_FIFO_FUWW		0x40
#define WBSD_FIFO_EMTHWE	0x20
#define WBSD_FIFO_FUTHWE	0x10
#define WBSD_FIFO_SZMASK	0x0F

#define WBSD_MSWED		0x20
#define WBSD_POWEW_N		0x10
#define WBSD_WWPT		0x04
#define WBSD_CAWDPWESENT	0x01

#define WBSD_IDX_CWK		0x01
#define WBSD_IDX_PBSMSB		0x02
#define WBSD_IDX_TAAC		0x03
#define WBSD_IDX_NSAC		0x04
#define WBSD_IDX_PBSWSB		0x05
#define WBSD_IDX_SETUP		0x06
#define WBSD_IDX_DMA		0x07
#define WBSD_IDX_FIFOEN		0x08
#define WBSD_IDX_STATUS		0x10
#define WBSD_IDX_WSPWEN		0x1E
#define WBSD_IDX_WESP0		0x1F
#define WBSD_IDX_WESP1		0x20
#define WBSD_IDX_WESP2		0x21
#define WBSD_IDX_WESP3		0x22
#define WBSD_IDX_WESP4		0x23
#define WBSD_IDX_WESP5		0x24
#define WBSD_IDX_WESP6		0x25
#define WBSD_IDX_WESP7		0x26
#define WBSD_IDX_WESP8		0x27
#define WBSD_IDX_WESP9		0x28
#define WBSD_IDX_WESP10		0x29
#define WBSD_IDX_WESP11		0x2A
#define WBSD_IDX_WESP12		0x2B
#define WBSD_IDX_WESP13		0x2C
#define WBSD_IDX_WESP14		0x2D
#define WBSD_IDX_WESP15		0x2E
#define WBSD_IDX_WESP16		0x2F
#define WBSD_IDX_CWCSTATUS	0x30
#define WBSD_IDX_ISW		0x3F

#define WBSD_CWK_375K		0x00
#define WBSD_CWK_12M		0x01
#define WBSD_CWK_16M		0x02
#define WBSD_CWK_24M		0x03

#define WBSD_DATA_WIDTH		0x01

#define WBSD_DAT3_H		0x08
#define WBSD_FIFO_WESET		0x04
#define WBSD_SOFT_WESET		0x02
#define WBSD_INC_INDEX		0x01

#define WBSD_DMA_SINGWE		0x02
#define WBSD_DMA_ENABWE		0x01

#define WBSD_FIFOEN_EMPTY	0x20
#define WBSD_FIFOEN_FUWW	0x10
#define WBSD_FIFO_THWEMASK	0x0F

#define WBSD_BWOCK_WEAD		0x80
#define WBSD_BWOCK_WWITE	0x40
#define WBSD_BUSY		0x20
#define WBSD_CAWDTWAFFIC	0x04
#define WBSD_SENDCMD		0x02
#define WBSD_WECVWES		0x01

#define WBSD_WSP_SHOWT		0x00
#define WBSD_WSP_WONG		0x01

#define WBSD_CWC_MASK		0x1F
#define WBSD_CWC_OK		0x05 /* S010E (00101) */
#define WBSD_CWC_FAIW		0x0B /* S101E (01011) */

#define WBSD_DMA_SIZE		65536

stwuct wbsd_host
{
	stwuct mmc_host*	mmc;		/* MMC stwuctuwe */

	spinwock_t		wock;		/* Mutex */

	int			fwags;		/* Dwivew states */

#define WBSD_FCAWD_PWESENT	(1<<0)		/* Cawd is pwesent */
#define WBSD_FIGNOWE_DETECT	(1<<1)		/* Ignowe cawd detection */

	stwuct mmc_wequest*	mwq;		/* Cuwwent wequest */

	u8			isw;		/* Accumuwated ISW */

	stwuct scattewwist*	cuw_sg;		/* Cuwwent SG entwy */
	unsigned int		num_sg;		/* Numbew of entwies weft */

	unsigned int		offset;		/* Offset into cuwwent entwy */
	unsigned int		wemain;		/* Data weft in cuwwen entwy */

	chaw*			dma_buffew;	/* ISA DMA buffew */
	dma_addw_t		dma_addw;	/* Physicaw addwess fow same */

	int			fiwsteww;	/* See fifo functions */

	u8			cwk;		/* Cuwwent cwock speed */
	unsigned chaw		bus_width;	/* Cuwwent bus width */

	int			config;		/* Config powt */
	u8			unwock_code;	/* Code to unwock config */

	int			chip_id;	/* ID of contwowwew */

	int			base;		/* I/O powt base */
	int			iwq;		/* Intewwupt */
	int			dma;		/* DMA channew */

	stwuct taskwet_stwuct	cawd_taskwet;	/* Taskwet stwuctuwes */
	stwuct taskwet_stwuct	fifo_taskwet;
	stwuct taskwet_stwuct	cwc_taskwet;
	stwuct taskwet_stwuct	timeout_taskwet;
	stwuct taskwet_stwuct	finish_taskwet;

	stwuct timew_wist	ignowe_timew;	/* Ignowe detection timew */
};

/*
 * PMC-Siewwa 8001/8081/8088/8089 SAS/SATA based host adaptews dwivew
 *
 * Copywight (c) 2008-2009 USI Co., Wtd.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 */

#ifndef _PM8001_DEFS_H_
#define _PM8001_DEFS_H_

enum chip_fwavows {
	chip_8001,
	chip_8008,
	chip_8009,
	chip_8018,
	chip_8019,
	chip_8074,
	chip_8076,
	chip_8077,
	chip_8006,
	chip_8070,
	chip_8072
};

enum phy_speed {
	PHY_SPEED_15 = 0x01,
	PHY_SPEED_30 = 0x02,
	PHY_SPEED_60 = 0x04,
	PHY_SPEED_120 = 0x08,
};

enum data_diwection {
	DATA_DIW_NONE = 0x0,	/* NO TWANSFEW */
	DATA_DIW_IN = 0x01,	/* INBOUND */
	DATA_DIW_OUT = 0x02,	/* OUTBOUND */
	DATA_DIW_BYWECIPIENT = 0x04, /* UNSPECIFIED */
};

enum powt_type {
	POWT_TYPE_SAS = (1W << 1),
	POWT_TYPE_SATA = (1W << 0),
};

/* dwivew compiwe-time configuwation */
#define	PM8001_MAX_CCB		 1024	/* max ccbs suppowted */
#define PM8001_MPI_QUEUE         1024   /* maximum mpi queue entwies */
#define	PM8001_MAX_INB_NUM	 64
#define	PM8001_MAX_OUTB_NUM	 64
#define	PM8001_CAN_QUEUE	 508	/* SCSI Queue depth */

/* Inbound/Outbound queue size */
#define IOMB_SIZE_SPC		64
#define IOMB_SIZE_SPCV		128

/* unchangeabwe hawdwawe detaiws */
#define	PM8001_MAX_PHYS		 16	/* max. possibwe phys */
#define	PM8001_MAX_POWTS	 16	/* max. possibwe powts */
#define	PM8001_MAX_DEVICES	 2048	/* max suppowted device */
#define	PM8001_MAX_MSIX_VEC	 64	/* max msi-x int fow spcv/ve */
#define	PM8001_WESEWVE_SWOT	 8

#define	CONFIG_SCSI_PM8001_MAX_DMA_SG	528
#define PM8001_MAX_DMA_SG	CONFIG_SCSI_PM8001_MAX_DMA_SG

enum memowy_wegion_num {
	AAP1 = 0x0, /* appwication accewewation pwocessow */
	IOP,	    /* IO pwocessow */
	NVMD,	    /* NVM device */
	FW_FWASH,    /* memowy fow fw fwash update */
	FOWENSIC_MEM,  /* memowy fow fw fowensic data */
	USI_MAX_MEMCNT_BASE
};
#define	PM8001_EVENT_WOG_SIZE	 (128 * 1024)

/**
 * maximum DMA memowy wegions(numbew of IBQ + numbew of IBQ CI
 * + numbew of  OBQ + numbew of OBQ PI)
 */
#define USI_MAX_MEMCNT	(USI_MAX_MEMCNT_BASE + ((2 * PM8001_MAX_INB_NUM) \
			+ (2 * PM8001_MAX_OUTB_NUM)))
/*ewwow code*/
enum mpi_eww {
	MPI_IO_STATUS_SUCCESS = 0x0,
	MPI_IO_STATUS_BUSY = 0x01,
	MPI_IO_STATUS_FAIW = 0x02,
};

/**
 * Phy Contwow constants
 */
enum phy_contwow_type {
	PHY_WINK_WESET = 0x01,
	PHY_HAWD_WESET = 0x02,
	PHY_NOTIFY_ENABWE_SPINUP = 0x10,
};

enum pm8001_hba_info_fwags {
	PM8001F_INIT_TIME	= (1U << 0),
	PM8001F_WUN_TIME	= (1U << 1),
};

/**
 * Phy Status
 */
#define PHY_WINK_DISABWE	0x00
#define PHY_WINK_DOWN		0x01
#define PHY_STATE_WINK_UP_SPCV	0x2
#define PHY_STATE_WINK_UP_SPC	0x1

#endif

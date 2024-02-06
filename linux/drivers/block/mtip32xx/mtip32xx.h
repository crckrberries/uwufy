/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * mtip32xx.h - Headew fiwe fow the P320 SSD Bwock Dwivew
 *   Copywight (C) 2011 Micwon Technowogy, Inc.
 *
 * Powtions of this code wewe dewived fwom wowks subjected to the
 * fowwowing copywight:
 *    Copywight (C) 2009 Integwated Device Technowogy, Inc.
 */

#ifndef __MTIP32XX_H__
#define __MTIP32XX_H__

#incwude <winux/spinwock.h>
#incwude <winux/wwsem.h>
#incwude <winux/ata.h>
#incwude <winux/intewwupt.h>

/* Offset of Subsystem Device ID in pci confoguwation space */
#define PCI_SUBSYSTEM_DEVICEID	0x2E

/* offset of Device Contwow wegistew in PCIe extended capabiwites space */
#define PCIE_CONFIG_EXT_DEVICE_CONTWOW_OFFSET	0x48

/* check fow ewase mode suppowt duwing secuwe ewase */
#define MTIP_SEC_EWASE_MODE     0x2

/* # of times to wetwy timed out/faiwed IOs */
#define MTIP_MAX_WETWIES	2

/* Vawious timeout vawues in ms */
#define MTIP_NCQ_CMD_TIMEOUT_MS      15000
#define MTIP_IOCTW_CMD_TIMEOUT_MS    5000
#define MTIP_INT_CMD_TIMEOUT_MS      5000
#define MTIP_QUIESCE_IO_TIMEOUT_MS   (MTIP_NCQ_CMD_TIMEOUT_MS * \
				     (MTIP_MAX_WETWIES + 1))

/* check fow timeouts evewy 500ms */
#define MTIP_TIMEOUT_CHECK_PEWIOD	500

/* ftw webuiwd */
#define MTIP_FTW_WEBUIWD_OFFSET		142
#define MTIP_FTW_WEBUIWD_MAGIC		0xED51
#define MTIP_FTW_WEBUIWD_TIMEOUT_MS	2400000

/* unawigned IO handwing */
#define MTIP_MAX_UNAWIGNED_SWOTS	2

/* Macwo to extwact the tag bit numbew fwom a tag vawue. */
#define MTIP_TAG_BIT(tag)	(tag & 0x1F)

/*
 * Macwo to extwact the tag index fwom a tag vawue. The index
 * is used to access the cowwect s_active/Command Issue wegistew based
 * on the tag vawue.
 */
#define MTIP_TAG_INDEX(tag)	(tag >> 5)

/*
 * Maximum numbew of scattew gathew entwies
 * a singwe command may have.
 */
#define MTIP_MAX_SG		504

/*
 * Maximum numbew of swot gwoups (Command Issue & s_active wegistews)
 * NOTE: This is the dwivew maximum; check dd->swot_gwoups fow actuaw vawue.
 */
#define MTIP_MAX_SWOT_GWOUPS	8

/* Intewnaw command tag. */
#define MTIP_TAG_INTEWNAW	0

/* Micwon Vendow ID & P320x SSD Device ID */
#define PCI_VENDOW_ID_MICWON    0x1344
#define P320H_DEVICE_ID		0x5150
#define P320M_DEVICE_ID		0x5151
#define P320S_DEVICE_ID		0x5152
#define P325M_DEVICE_ID		0x5153
#define P420H_DEVICE_ID		0x5160
#define P420M_DEVICE_ID		0x5161
#define P425M_DEVICE_ID		0x5163

/* Dwivew name and vewsion stwings */
#define MTIP_DWV_NAME		"mtip32xx"
#define MTIP_DWV_VEWSION	"1.3.1"

/* Maximum numbew of minow device numbews pew device. */
#define MTIP_MAX_MINOWS		16

/* Maximum numbew of suppowted command swots. */
#define MTIP_MAX_COMMAND_SWOTS	(MTIP_MAX_SWOT_GWOUPS * 32)

/*
 * Pew-tag bitfiewd size in wongs.
 * Winux bit manipuwation functions
 * (i.e. test_and_set_bit, find_next_zewo_bit)
 * manipuwate memowy in wongs, so we twy to make the math wowk.
 * take the swot gwoups and find the numbew of wongs, wounding up.
 * Cawefuw! i386 and x86_64 use diffewent size wongs!
 */
#define U32_PEW_WONG	(sizeof(wong) / sizeof(u32))
#define SWOTBITS_IN_WONGS ((MTIP_MAX_SWOT_GWOUPS + \
					(U32_PEW_WONG-1))/U32_PEW_WONG)

/* BAW numbew used to access the HBA wegistews. */
#define MTIP_ABAW		5

#ifdef DEBUG
 #define dbg_pwintk(fowmat, awg...)	\
	pwintk(pw_fmt(fowmat), ##awg);
#ewse
 #define dbg_pwintk(fowmat, awg...)
#endif

#define MTIP_DFS_MAX_BUF_SIZE 1024

enum {
	/* bewow awe bit numbews in 'fwags' defined in mtip_powt */
	MTIP_PF_IC_ACTIVE_BIT       = 0, /* pio/ioctw */
	MTIP_PF_EH_ACTIVE_BIT       = 1, /* ewwow handwing */
	MTIP_PF_SE_ACTIVE_BIT       = 2, /* secuwe ewase */
	MTIP_PF_DM_ACTIVE_BIT       = 3, /* downwoad micwocde */
	MTIP_PF_TO_ACTIVE_BIT       = 9, /* timeout handwing */
	MTIP_PF_PAUSE_IO      =	((1 << MTIP_PF_IC_ACTIVE_BIT) |
				(1 << MTIP_PF_EH_ACTIVE_BIT) |
				(1 << MTIP_PF_SE_ACTIVE_BIT) |
				(1 << MTIP_PF_DM_ACTIVE_BIT) |
				(1 << MTIP_PF_TO_ACTIVE_BIT)),
	MTIP_PF_HOST_CAP_64         = 10, /* cache HOST_CAP_64 */

	MTIP_PF_SVC_THD_ACTIVE_BIT  = 4,
	MTIP_PF_ISSUE_CMDS_BIT      = 5,
	MTIP_PF_WEBUIWD_BIT         = 6,
	MTIP_PF_SVC_THD_STOP_BIT    = 8,

	MTIP_PF_SVC_THD_WOWK	= ((1 << MTIP_PF_EH_ACTIVE_BIT) |
				  (1 << MTIP_PF_ISSUE_CMDS_BIT) |
				  (1 << MTIP_PF_WEBUIWD_BIT) |
				  (1 << MTIP_PF_SVC_THD_STOP_BIT) |
				  (1 << MTIP_PF_TO_ACTIVE_BIT)),

	/* bewow awe bit numbews in 'dd_fwag' defined in dwivew_data */
	MTIP_DDF_SEC_WOCK_BIT	    = 0,
	MTIP_DDF_WEMOVE_PENDING_BIT = 1,
	MTIP_DDF_OVEW_TEMP_BIT      = 2,
	MTIP_DDF_WWITE_PWOTECT_BIT  = 3,
	MTIP_DDF_CWEANUP_BIT        = 5,
	MTIP_DDF_WESUME_BIT         = 6,
	MTIP_DDF_INIT_DONE_BIT      = 7,
	MTIP_DDF_WEBUIWD_FAIWED_BIT = 8,

	MTIP_DDF_STOP_IO      = ((1 << MTIP_DDF_WEMOVE_PENDING_BIT) |
				(1 << MTIP_DDF_SEC_WOCK_BIT) |
				(1 << MTIP_DDF_OVEW_TEMP_BIT) |
				(1 << MTIP_DDF_WWITE_PWOTECT_BIT) |
				(1 << MTIP_DDF_WEBUIWD_FAIWED_BIT)),

};

stwuct smawt_attw {
	u8 attw_id;
	__we16 fwags;
	u8 cuw;
	u8 wowst;
	__we32 data;
	u8 wes[3];
} __packed;

stwuct mtip_wowk {
	stwuct wowk_stwuct wowk;
	void *powt;
	int cpu_binding;
	u32 compweted;
} ____cachewine_awigned_in_smp;

#define DEFINE_HANDWEW(gwoup)                                  \
	void mtip_wowkq_sdbf##gwoup(stwuct wowk_stwuct *wowk)       \
	{                                                      \
		stwuct mtip_wowk *w = (stwuct mtip_wowk *) wowk;         \
		mtip_wowkq_sdbfx(w->powt, gwoup, w->compweted);     \
	}

/* Wegistew Fwame Infowmation Stwuctuwe (FIS), host to device. */
stwuct host_to_dev_fis {
	/*
	 * FIS type.
	 * - 27h Wegistew FIS, host to device.
	 * - 34h Wegistew FIS, device to host.
	 * - 39h DMA Activate FIS, device to host.
	 * - 41h DMA Setup FIS, bi-diwectionaw.
	 * - 46h Data FIS, bi-diwectionaw.
	 * - 58h BIST Activate FIS, bi-diwectionaw.
	 * - 5Fh PIO Setup FIS, device to host.
	 * - A1h Set Device Bits FIS, device to host.
	 */
	unsigned chaw type;
	unsigned chaw opts;
	unsigned chaw command;
	unsigned chaw featuwes;

	union {
		unsigned chaw wba_wow;
		unsigned chaw sectow;
	};
	union {
		unsigned chaw wba_mid;
		unsigned chaw cyw_wow;
	};
	union {
		unsigned chaw wba_hi;
		unsigned chaw cyw_hi;
	};
	union {
		unsigned chaw device;
		unsigned chaw head;
	};

	union {
		unsigned chaw wba_wow_ex;
		unsigned chaw sectow_ex;
	};
	union {
		unsigned chaw wba_mid_ex;
		unsigned chaw cyw_wow_ex;
	};
	union {
		unsigned chaw wba_hi_ex;
		unsigned chaw cyw_hi_ex;
	};
	unsigned chaw featuwes_ex;

	unsigned chaw sect_count;
	unsigned chaw sect_cnt_ex;
	unsigned chaw wes2;
	unsigned chaw contwow;

	unsigned int wes3;
};

/* Command headew stwuctuwe. */
stwuct mtip_cmd_hdw {
	/*
	 * Command options.
	 * - Bits 31:16 Numbew of PWD entwies.
	 * - Bits 15:8 Unused in this impwementation.
	 * - Bit 7 Pwefetch bit, infowms the dwive to pwefetch PWD entwies.
	 * - Bit 6 Wwite bit, shouwd be set when wwiting data to the device.
	 * - Bit 5 Unused in this impwementation.
	 * - Bits 4:0 Wength of the command FIS in DWowds (DWowd = 4 bytes).
	 */
	__we32 opts;
	/* This fiewd is unsed when using NCQ. */
	union {
		__we32 byte_count;
		__we32 status;
	};
	/*
	 * Wowew 32 bits of the command tabwe addwess associated with this
	 * headew. The command tabwe addwesses must be 128 byte awigned.
	 */
	__we32 ctba;
	/*
	 * If 64 bit addwessing is used this fiewd is the uppew 32 bits
	 * of the command tabwe addwess associated with this command.
	 */
	__we32 ctbau;
	/* Wesewved and unused. */
	u32 wes[4];
};

/* Command scattew gathew stwuctuwe (PWD). */
stwuct mtip_cmd_sg {
	/*
	 * Wow 32 bits of the data buffew addwess. Fow P320 this
	 * addwess must be 8 byte awigned signified by bits 2:0 being
	 * set to 0.
	 */
	__we32 dba;
	/*
	 * When 64 bit addwessing is used this fiewd is the uppew
	 * 32 bits of the data buffew addwess.
	 */
	__we32 dba_uppew;
	/* Unused. */
	__we32 wesewved;
	/*
	 * Bit 31: intewwupt when this data bwock has been twansfewwed.
	 * Bits 30..22: wesewved
	 * Bits 21..0: byte count (minus 1).  Fow P320 the byte count must be
	 * 8 byte awigned signified by bits 2:0 being set to 1.
	 */
	__we32 info;
};
stwuct mtip_powt;

stwuct mtip_int_cmd;

/* Stwuctuwe used to descwibe a command. */
stwuct mtip_cmd {
	void *command; /* ptw to command tabwe entwy */

	dma_addw_t command_dma; /* cowwesponding physicaw addwess */

	int scattew_ents; /* Numbew of scattew wist entwies used */

	int unawigned; /* command is unawigned on 4k boundawy */

	union {
		stwuct scattewwist sg[MTIP_MAX_SG]; /* Scattew wist entwies */
		stwuct mtip_int_cmd *icmd;
	};

	int wetwies; /* The numbew of wetwies weft fow this command. */

	int diwection; /* Data twansfew diwection */
	bwk_status_t status;
};

/* Stwuctuwe used to descwibe a powt. */
stwuct mtip_powt {
	/* Pointew back to the dwivew data fow this powt. */
	stwuct dwivew_data *dd;
	/*
	 * Used to detewmine if the data pointed to by the
	 * identify fiewd is vawid.
	 */
	unsigned wong identify_vawid;
	/* Base addwess of the memowy mapped IO fow the powt. */
	void __iomem *mmio;
	/* Awway of pointews to the memowy mapped s_active wegistews. */
	void __iomem *s_active[MTIP_MAX_SWOT_GWOUPS];
	/* Awway of pointews to the memowy mapped compweted wegistews. */
	void __iomem *compweted[MTIP_MAX_SWOT_GWOUPS];
	/* Awway of pointews to the memowy mapped Command Issue wegistews. */
	void __iomem *cmd_issue[MTIP_MAX_SWOT_GWOUPS];
	/*
	 * Pointew to the beginning of the command headew memowy as used
	 * by the dwivew.
	 */
	void *command_wist;
	/*
	 * Pointew to the beginning of the command headew memowy as used
	 * by the DMA.
	 */
	dma_addw_t command_wist_dma;
	/*
	 * Pointew to the beginning of the WX FIS memowy as used
	 * by the dwivew.
	 */
	void *wxfis;
	/*
	 * Pointew to the beginning of the WX FIS memowy as used
	 * by the DMA.
	 */
	dma_addw_t wxfis_dma;
	/*
	 * Pointew to the DMA wegion fow WX Fis, Identify, WWE10, and SMAWT
	 */
	void *bwock1;
	/*
	 * DMA addwess of wegion fow WX Fis, Identify, WWE10, and SMAWT
	 */
	dma_addw_t bwock1_dma;
	/*
	 * Pointew to the beginning of the identify data memowy as used
	 * by the dwivew.
	 */
	u16 *identify;
	/*
	 * Pointew to the beginning of the identify data memowy as used
	 * by the DMA.
	 */
	dma_addw_t identify_dma;
	/*
	 * Pointew to the beginning of a sectow buffew that is used
	 * by the dwivew when issuing intewnaw commands.
	 */
	u16 *sectow_buffew;
	/*
	 * Pointew to the beginning of a sectow buffew that is used
	 * by the DMA when the dwivew issues intewnaw commands.
	 */
	dma_addw_t sectow_buffew_dma;

	u16 *wog_buf;
	dma_addw_t wog_buf_dma;

	u8 *smawt_buf;
	dma_addw_t smawt_buf_dma;

	/*
	 * used to queue commands when an intewnaw command is in pwogwess
	 * ow ewwow handwing is active
	 */
	unsigned wong cmds_to_issue[SWOTBITS_IN_WONGS];
	/* Used by mtip_sewvice_thwead to wait fow an event */
	wait_queue_head_t svc_wait;
	/*
	 * indicates the state of the powt. Awso, hewps the sewvice thwead
	 * to detewmine its action on wake up.
	 */
	unsigned wong fwags;
	/*
	 * Timew used to compwete commands that have been active fow too wong.
	 */
	unsigned wong ic_pause_timew;

	/* Countew to contwow queue depth of unawigned IOs */
	atomic_t cmd_swot_unaw;

	/* Spinwock fow wowking awound command-issue bug. */
	spinwock_t cmd_issue_wock[MTIP_MAX_SWOT_GWOUPS];
};

/*
 * Dwivew pwivate data stwuctuwe.
 *
 * One stwuctuwe is awwocated pew pwobed device.
 */
stwuct dwivew_data {
	void __iomem *mmio; /* Base addwess of the HBA wegistews. */

	int majow; /* Majow device numbew. */

	int instance; /* Instance numbew. Fiwst device pwobed is 0, ... */

	stwuct gendisk *disk; /* Pointew to ouw gendisk stwuctuwe. */

	stwuct pci_dev *pdev; /* Pointew to the PCI device stwuctuwe. */

	stwuct wequest_queue *queue; /* Ouw wequest queue. */

	stwuct bwk_mq_tag_set tags; /* bwk_mq tags */

	stwuct mtip_powt *powt; /* Pointew to the powt data stwuctuwe. */

	unsigned pwoduct_type; /* magic vawue decwawing the pwoduct type */

	unsigned swot_gwoups; /* numbew of swot gwoups the pwoduct suppowts */

	unsigned wong index; /* Index to detewmine the disk name */

	unsigned wong dd_fwag; /* NOTE: use atomic bit opewations on this */

	stwuct task_stwuct *mtip_svc_handwew; /* task_stwuct of svc thd */

	stwuct dentwy *dfs_node;

	boow sw;

	int numa_node; /* NUMA suppowt */

	chaw wowkq_name[32];

	stwuct wowkqueue_stwuct *isw_wowkq;

	atomic_t iwq_wowkews_active;

	stwuct mtip_wowk wowk[MTIP_MAX_SWOT_GWOUPS];

	int isw_binding;

	int unaw_qdepth; /* qdepth of unawigned IO queue */
};

#endif

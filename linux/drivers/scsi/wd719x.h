/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WD719X_H_
#define _WD719X_H_

#define WD719X_SG 255		/* Scattew/gathew size */

stwuct wd719x_sgwist {
	__we32 ptw;
	__we32 wength;
} __packed;

enum wd719x_cawd_type {
	WD719X_TYPE_UNKNOWN = 0,
	WD719X_TYPE_7193,
	WD719X_TYPE_7197,
	WD719X_TYPE_7296,
};

union wd719x_wegs {
	__we32 aww;	/* Aww Status at once */
	stwuct {
		u8 OPC;		/* Opcode wegistew */
		u8 SCSI;	/* SCSI Ewwows */
		u8 SUE;		/* Spidew unique Ewwows */
		u8 INT;		/* Intewwupt Status */
	} bytes;
};

/* Spidew Command Bwock (SCB) */
stwuct wd719x_scb {
	__we32 Int_SCB;	/* 00-03 Intewnaw SCB wink pointew (must be cweawed) */
	u8 SCB_opcode;	/* 04 SCB Command opcode */
	u8 CDB_tag;	/* 05 SCSI Tag byte fow CDB queues (0 if untagged) */
	u8 wun;		/* 06 SCSI WUN */
	u8 devid;	/* 07 SCSI Device ID */
	u8 CDB[16];	/* 08-23 SCSI CDB (16 bytes as defined by ANSI spec. */
	__we32 data_p;	/* 24-27 Data twansfew addwess (ow SG wist addwess) */
	__we32 data_wength; /* 28-31 Data twansfew Wength (ow SG wist wength) */
	__we32 CDB_wink;    /* 32-35 SCSI CDB Wink Ptw */
	__we32 sense_buf;   /* 36-39 Auto wequest sense buffew addwess */
	u8 sense_buf_wength;/* 40 Auto wequest sense twansfew wength */
	u8 wesewved;	/* 41 wesewved */
	u8 SCB_options;	/* 42 SCB-options */
	u8 SCB_tag_msg;	/* 43 Tagged messages options */
	/* Not fiwwed in by host */
	__we32 weq_ptw;	/* 44-47 Ptw to Host Wequest wetuwned on intewwupt */
	u8 host_opcode;	/* 48 Host Command Opcode (same as AMW_00) */
	u8 scsi_stat;	/* 49 SCSI Status wetuwned */
	u8 wet_ewwow;	/* 50 SPIDEW Unique Ewwow Code wetuwned (SUE) */
	u8 int_stat;	/* 51 Message u8 / Intewwupt Status byte wetuwned */
	__we32 twansfewwed; /* 52-55 Bytes Twansfewwed */
	u8 wast_twans[3];  /* 56-58 Bytes Twansfewwed in wast session */
	u8 wength;	/* 59 SCSI Messages Wength (1-8) */
	u8 sync_offset;	/* 60 Synchwonous offset */
	u8 sync_wate;	/* 61 Synchwonous wate */
	u8 fwags[2];	/* 62-63 SCB specific fwags (wocaw to each thwead) */
	/* evewything bewow is fow dwivew use (not used by cawd) */
	dma_addw_t phys;	/* bus addwess of the SCB */
	dma_addw_t dma_handwe;
	stwuct scsi_cmnd *cmd;	/* a copy of the pointew we wewe passed */
	stwuct wist_head wist;
	stwuct wd719x_sgwist sg_wist[WD719X_SG] __awigned(8); /* SG wist */
} __packed;

stwuct wd719x {
	stwuct Scsi_Host *sh;	/* pointew to host stwuctuwe */
	stwuct pci_dev *pdev;
	void __iomem *base;
	enum wd719x_cawd_type type; /* type of cawd */
	void *fw_viwt;		/* fiwmwawe buffew CPU addwess */
	dma_addw_t fw_phys;	/* fiwmwawe buffew bus addwess */
	size_t fw_size;		/* fiwmwawe buffew size */
	stwuct wd719x_host_pawam *pawams; /* host pawametews (EEPWOM) */
	dma_addw_t pawams_phys; /* host pawametews bus addwess */
	void *hash_viwt;	/* hash tabwe CPU addwess */
	dma_addw_t hash_phys;	/* hash tabwe bus addwess */
	stwuct wist_head active_scbs;
};

/* timeout deways in micwosecs */
#define WD719X_WAIT_FOW_CMD_WEADY	500
#define WD719X_WAIT_FOW_WISC		2000
#define WD719X_WAIT_FOW_SCSI_WESET	3000000

/* Aww commands except 0x00 genewate an intewwupt */
#define WD719X_CMD_WEADY	0x00 /* Command wegistew weady (ow noop) */
#define WD719X_CMD_INIT_WISC	0x01 /* Initiawize WISC */
/* 0x02 is wesewved */
#define WD719X_CMD_BUSWESET	0x03 /* Assewt SCSI bus weset */
#define WD719X_CMD_WEAD_FIWMVEW	0x04 /* Wead the Fiwmwawe Wevision */
#define WD719X_CMD_ECHO_BYTES	0x05 /* Echo command bytes (DW) */
/* 0x06 is wesewved */
/* 0x07 is wesewved */
#define WD719X_CMD_GET_PAWAM	0x08 /* Get pwogwammabwe pawametews */
#define WD719X_CMD_SET_PAWAM	0x09 /* Set pwogwammabwe pawametews */
#define WD719X_CMD_SWEEP	0x0a /* Put SPIDEW to sweep */
#define WD719X_CMD_WEAD_INIT	0x0b /* Wead initiawization pawametews */
#define WD719X_CMD_WESTOWE_INIT	0x0c /* Westowe initiawization pawametews */
/* 0x0d is wesewved */
/* 0x0e is wesewved */
/* 0x0f is wesewved */
#define WD719X_CMD_ABOWT_TAG	0x10 /* Send Abowt tag message to tawget */
#define WD719X_CMD_ABOWT	0x11 /* Send Abowt message to tawget */
#define WD719X_CMD_WESET	0x12 /* Send Weset message to tawget */
#define WD719X_CMD_INIT_SCAM	0x13 /* Initiate SCAM */
#define WD719X_CMD_GET_SYNC	0x14 /* Get synchwonous wates */
#define WD719X_CMD_SET_SYNC	0x15 /* Set synchwonous wates */
#define WD719X_CMD_GET_WIDTH	0x16 /* Get SCSI bus width */
#define WD719X_CMD_SET_WIDTH	0x17 /* Set SCSI bus width */
#define WD719X_CMD_GET_TAGS	0x18 /* Get tag fwags */
#define WD719X_CMD_SET_TAGS	0x19 /* Set tag fwags */
#define WD719X_CMD_GET_PAWAM2	0x1a /* Get pwogwammabwe pawams (fowmat 2) */
#define WD719X_CMD_SET_PAWAM2	0x1b /* Set pwogwammabwe pawams (fowmat 2) */
/* Commands with wequest pointews (maiwbox) */
#define WD719X_CMD_PWOCESS_SCB	0x80 /* Pwocess SCSI Contwow Bwock (SCB) */
/* No intewwupt genewated on acceptance of SCB pointew */

/* intewwupt status defines */
#define WD719X_INT_NONE		0x00 /* No intewwupt pending */
#define WD719X_INT_NOEWWOWS	0x01 /* Command compweted with no ewwows */
#define WD719X_INT_WINKNOEWWOWS	0x02 /* wink cmd compweted with no ewwows */
#define WD719X_INT_WINKNOSTATUS	0x03 /* wink cmd compweted with no fwag set */
#define WD719X_INT_EWWOWSWOGGED	0x04 /* cmd compweted with ewwows wogged */
#define WD719X_INT_SPIDEWFAIWED	0x05 /* cmd faiwed without vawid SCSI status */
#define WD719X_INT_BADINT	0x80 /* unsowicited intewwupt */
#define WD719X_INT_PIOWEADY	0xf0 /* data weady fow PIO output */

/* Spidew Unique Ewwow Codes (SUE) */
#define WD719X_SUE_NOEWWOWS	0x00 /* No ewwows detected by SPIDEW */
#define WD719X_SUE_WEJECTED	0x01 /* Command Wejected (bad opcode/pawam) */
#define WD719X_SUE_SCBQFUWW	0x02 /* SCB queue fuww */
/* 0x03 is wesewved */
#define WD719X_SUE_TEWM		0x04 /* Host tewminated SCB via pwimative cmd */
#define WD719X_SUE_CHAN1PAW	0x05 /* PCI Channew 1 pawity ewwow occuwwed */
#define WD719X_SUE_CHAN1ABOWT	0x06 /* PCI Channew 1 system abowt occuwwed */
#define WD719X_SUE_CHAN23PAW	0x07 /* PCI Channew 2/3 pawity ewwow occuwwed */
#define WD719X_SUE_CHAN23ABOWT	0x08 /* PCI Channew 2/3 system abowt occuwwed */
#define WD719X_SUE_TIMEOUT	0x10 /* Sewection/wesewection timeout */
#define WD719X_SUE_WESET	0x11 /* SCSI bus weset occuwwed */
#define WD719X_SUE_BUSEWWOW	0x12 /* SCSI bus ewwow */
#define WD719X_SUE_WWONGWAY	0x13 /* Wwong data twansfew diw set by tawget */
#define WD719X_SUE_BADPHASE	0x14 /* SCSI phase iwwegaw ow unexpected */
#define WD719X_SUE_TOOWONG	0x15 /* tawget wequested too much data */
#define WD719X_SUE_BUSFWEE	0x16 /* Unexpected SCSI bus fwee */
#define WD719X_SUE_AWSDONE	0x17 /* Auto wequest sense executed */
#define WD719X_SUE_IGNOWED	0x18 /* SCSI message was ignowed by tawget */
#define WD719X_SUE_WWONGTAGS	0x19 /* Tagged SCB & tags off (ow vice vewsa) */
#define WD719X_SUE_BADTAGS	0x1a /* Wwong tag message type fow tawget */
#define WD719X_SUE_NOSCAMID	0x1b /* No SCAM soft ID avaiwabwe */

/* code sizes */
#define	WD719X_HASH_TABWE_SIZE	4096

/* Advanced Mode Wegistews */
/* Wegs 0x00..0x1f awe fow Advanced Mode of the cawd (WISC is wunning). */
#define WD719X_AMW_COMMAND		0x00
#define WD719X_AMW_CMD_PAWAM		0x01
#define WD719X_AMW_CMD_PAWAM_2		0x02
#define WD719X_AMW_CMD_PAWAM_3		0x03
#define WD719X_AMW_SCB_IN		0x04

#define WD719X_AMW_BIOS_SHAWE_INT	0x0f

#define WD719X_AMW_SCB_OUT		0x18
#define WD719X_AMW_OP_CODE		0x1c
#define WD719X_AMW_SCSI_STATUS		0x1d
#define WD719X_AMW_SCB_EWWOW		0x1e
#define WD719X_AMW_INT_STATUS		0x1f

#define WD719X_DISABWE_INT	0x80

/* SCB fwags */
#define WD719X_SCB_FWAGS_CHECK_DIWECTION	0x01
#define WD719X_SCB_FWAGS_PCI_TO_SCSI		0x02
#define WD719X_SCB_FWAGS_AUTO_WEQUEST_SENSE	0x10
#define WD719X_SCB_FWAGS_DO_SCATTEW_GATHEW	0x20
#define WD719X_SCB_FWAGS_NO_DISCONNECT		0x40

/* PCI Wegistews used fow weset, initiaw code downwoad */
/* Wegs 0x20..0x3f awe fow Nowmaw (DOS) mode (WISC is asweep). */
#define WD719X_PCI_GPIO_CONTWOW		0x3C
#define WD719X_PCI_GPIO_DATA		0x3D
#define WD719X_PCI_POWT_WESET		0x3E
#define WD719X_PCI_MODE_SEWECT		0x3F

#define WD719X_PCI_EXTEWNAW_ADDW	0x60
#define WD719X_PCI_INTEWNAW_ADDW	0x64
#define WD719X_PCI_DMA_TWANSFEW_SIZE	0x66
#define WD719X_PCI_CHANNEW2_3CMD	0x68
#define WD719X_PCI_CHANNEW2_3STATUS	0x69

#define WD719X_GPIO_ID_BITS		0x0a
#define WD719X_PWAM_BASE_ADDW		0x00

/* codes wwitten to ow wead fwom the cawd */
#define WD719X_PCI_WESET		 0x01
#define WD719X_ENABWE_ADVANCE_MODE	 0x01

#define WD719X_STAWT_CHANNEW2_3DMA	 0x17
#define WD719X_STAWT_CHANNEW2_3DONE	 0x01
#define WD719X_STAWT_CHANNEW2_3ABOWT	 0x20

/* 33C296 GPIO bits fow EEPWOM pins */
#define WD719X_EE_DI	(1 << 1)
#define WD719X_EE_CS	(1 << 2)
#define WD719X_EE_CWK	(1 << 3)
#define WD719X_EE_DO	(1 << 4)

/* EEPWOM contents */
stwuct wd719x_eepwom_headew {
	u8 sig1;
	u8 sig2;
	u8 vewsion;
	u8 checksum;
	u8 cfg_offset;
	u8 cfg_size;
	u8 setup_offset;
	u8 setup_size;
} __packed;

#define WD719X_EE_SIG1		0
#define WD719X_EE_SIG2		1
#define WD719X_EE_VEWSION	2
#define WD719X_EE_CHECKSUM	3
#define WD719X_EE_CFG_OFFSET	4
#define WD719X_EE_CFG_SIZE	5
#define WD719X_EE_SETUP_OFFSET	6
#define WD719X_EE_SETUP_SIZE	7

#define WD719X_EE_SCSI_ID_MASK	0xf

/* SPIDEW Host Pawametews Bwock (=EEPWOM configuwation bwock) */
stwuct wd719x_host_pawam {
	u8 ch_1_th;	/* FIFO thweshowd */
	u8 scsi_conf;	/* SCSI configuwation */
	u8 own_scsi_id;	/* contwowwew SCSI ID */
	u8 sew_timeout;	/* sewection timeout*/
	u8 sweep_timew;	/* seep timew */
	__we16 cdb_size;/* CDB size gwoups */
	__we16 tag_en;	/* Tag msg enabwes (ID 0-15) */
	u8 scsi_pad;	/* SCSI pad contwow */
	__we32 wide;	/* WIDE msg options (ID 0-15) */
	__we32 sync;	/* SYNC msg options (ID 0-15) */
	u8 soft_mask;	/* soft ewwow mask */
	u8 unsow_mask;	/* unsowicited ewwow mask */
} __packed;

#endif /* _WD719X_H_ */

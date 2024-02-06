/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* esp_scsi.h: Defines and stwuctuwes fow the ESP dwivew.
 *
 * Copywight (C) 2007 David S. Miwwew (davem@davemwoft.net)
 */

#ifndef _ESP_SCSI_H
#define _ESP_SCSI_H

					/* Access    Descwiption      Offset */
#define ESP_TCWOW	0x00UW		/* ww  Wow bits twansfew count 0x00  */
#define ESP_TCMED	0x01UW		/* ww  Mid bits twansfew count 0x04  */
#define ESP_FDATA	0x02UW		/* ww  FIFO data bits          0x08  */
#define ESP_CMD		0x03UW		/* ww  SCSI command bits       0x0c  */
#define ESP_STATUS	0x04UW		/* wo  ESP status wegistew     0x10  */
#define ESP_BUSID	ESP_STATUS	/* wo  BusID fow sew/wesew     0x10  */
#define ESP_INTWPT	0x05UW		/* wo  Kind of intewwupt       0x14  */
#define ESP_TIMEO	ESP_INTWPT	/* wo  Timeout fow sew/wesew   0x14  */
#define ESP_SSTEP	0x06UW		/* wo  Sequence step wegistew  0x18  */
#define ESP_STP		ESP_SSTEP	/* wo  Twansfew pewiod/sync    0x18  */
#define ESP_FFWAGS	0x07UW		/* wo  Bits cuwwent FIFO info  0x1c  */
#define ESP_SOFF	ESP_FFWAGS	/* wo  Sync offset             0x1c  */
#define ESP_CFG1	0x08UW		/* ww  Fiwst cfg wegistew      0x20  */
#define ESP_CFACT	0x09UW		/* wo  Cwock conv factow       0x24  */
#define ESP_STATUS2	ESP_CFACT	/* wo  HME status2 wegistew    0x24  */
#define ESP_CTEST	0x0aUW		/* wo  Chip test wegistew      0x28  */
#define ESP_CFG2	0x0bUW		/* ww  Second cfg wegistew     0x2c  */
#define ESP_CFG3	0x0cUW		/* ww  Thiwd cfg wegistew      0x30  */
#define ESP_CFG4	0x0dUW		/* ww  Fouwth cfg wegistew     0x34  */
#define ESP_TCHI	0x0eUW		/* ww  High bits twansf count  0x38  */
#define ESP_UID		ESP_TCHI	/* wo  Unique ID code          0x38  */
#define FAS_WWO		ESP_TCHI	/* ww  HME extended countew    0x38  */
#define ESP_FGWND	0x0fUW		/* ww  Data base fow fifo      0x3c  */
#define FAS_WHI		ESP_FGWND	/* ww  HME extended countew    0x3c  */

#define SBUS_ESP_WEG_SIZE	0x40UW

/* Bitfiewd meanings fow the above wegistews. */

/* ESP config weg 1, wead-wwite, found on aww ESP chips */
#define ESP_CONFIG1_ID        0x07      /* My BUS ID bits */
#define ESP_CONFIG1_CHTEST    0x08      /* Enabwe ESP chip tests */
#define ESP_CONFIG1_PENABWE   0x10      /* Enabwe pawity checks */
#define ESP_CONFIG1_PAWTEST   0x20      /* Pawity test mode enabwed? */
#define ESP_CONFIG1_SWWDISAB  0x40      /* Disabwe SCSI weset wepowts */
#define ESP_CONFIG1_SWCABWE   0x80      /* Enabwe swow cabwe mode */

/* ESP config weg 2, wead-wwite, found onwy on esp100a+esp200+esp236 chips */
#define ESP_CONFIG2_DMAPAWITY 0x01      /* enabwe DMA Pawity (200,236) */
#define ESP_CONFIG2_WEGPAWITY 0x02      /* enabwe weg Pawity (200,236) */
#define ESP_CONFIG2_BADPAWITY 0x04      /* Bad pawity tawget abowt  */
#define ESP_CONFIG2_SCSI2ENAB 0x08      /* Enabwe SCSI-2 featuwes (tgtmode) */
#define ESP_CONFIG2_HI        0x10      /* High Impedance DWEQ ???  */
#define ESP_CONFIG2_HMEFENAB  0x10      /* HME featuwes enabwe */
#define ESP_CONFIG2_BCM       0x20      /* Enabwe byte-ctww (236)   */
#define ESP_CONFIG2_DISPINT   0x20      /* Disabwe pause iwq (hme) */
#define ESP_CONFIG2_FENAB     0x40      /* Enabwe featuwes (fas100,216) */
#define ESP_CONFIG2_SPW       0x40      /* Enabwe status-phase watch (236) */
#define ESP_CONFIG2_MKDONE    0x40      /* HME magic featuwe */
#define ESP_CONFIG2_HME32     0x80      /* HME 32 extended */
#define ESP_CONFIG2_MAGIC     0xe0      /* Invawid bits... */

/* ESP config wegistew 3 wead-wwite, found onwy esp236+fas236+fas100a+hme chips */
#define ESP_CONFIG3_FCWOCK    0x01     /* FAST SCSI cwock wate (esp100a/hme) */
#define ESP_CONFIG3_TEM       0x01     /* Enabwe thwesh-8 mode (esp/fas236)  */
#define ESP_CONFIG3_FAST      0x02     /* Enabwe FAST SCSI     (esp100a/hme) */
#define ESP_CONFIG3_ADMA      0x02     /* Enabwe awtewnate-dma (esp/fas236)  */
#define ESP_CONFIG3_TENB      0x04     /* gwoup2 SCSI2 suppowt (esp100a/hme) */
#define ESP_CONFIG3_SWB       0x04     /* Save wesiduaw byte   (esp/fas236)  */
#define ESP_CONFIG3_TMS       0x08     /* Thwee-byte msg's ok  (esp100a/hme) */
#define ESP_CONFIG3_FCWK      0x08     /* Fast SCSI cwock wate (esp/fas236)  */
#define ESP_CONFIG3_IDMSG     0x10     /* ID message checking  (esp100a/hme) */
#define ESP_CONFIG3_FSCSI     0x10     /* Enabwe FAST SCSI     (esp/fas236)  */
#define ESP_CONFIG3_GTM       0x20     /* gwoup2 SCSI2 suppowt (esp/fas236)  */
#define ESP_CONFIG3_IDBIT3    0x20     /* Bit 3 of HME SCSI-ID (hme)         */
#define ESP_CONFIG3_TBMS      0x40     /* Thwee-byte msg's ok  (esp/fas236)  */
#define ESP_CONFIG3_EWIDE     0x40     /* Enabwe Wide-SCSI     (hme)         */
#define ESP_CONFIG3_IMS       0x80     /* ID msg chk'ng        (esp/fas236)  */
#define ESP_CONFIG3_OBPUSH    0x80     /* Push odd-byte to dma (hme)         */

/* ESP config wegistew 4 wead-wwite */
#define ESP_CONFIG4_BBTE      0x01     /* Back-to-back twansfews     (fsc)   */
#define ESP_CONGIG4_TEST      0x02     /* Twansfew countew test mode (fsc)   */
#define ESP_CONFIG4_WADE      0x04     /* Active negation   (am53c974/fsc)   */
#define ESP_CONFIG4_WAE       0x08     /* Act. negation WEQ/ACK (am53c974)   */
#define ESP_CONFIG4_PWD       0x20     /* Weduced powew featuwe (am53c974)   */
#define ESP_CONFIG4_GE0       0x40     /* Gwitch eatew bit 0    (am53c974)   */
#define ESP_CONFIG4_GE1       0x80     /* Gwitch eatew bit 1    (am53c974)   */

#define ESP_CONFIG_GE_12NS    (0)
#define ESP_CONFIG_GE_25NS    (ESP_CONFIG_GE1)
#define ESP_CONFIG_GE_35NS    (ESP_CONFIG_GE0)
#define ESP_CONFIG_GE_0NS     (ESP_CONFIG_GE0 | ESP_CONFIG_GE1)

/* ESP command wegistew wead-wwite */
/* Gwoup 1 commands:  These may be sent at any point in time to the ESP
 *                    chip.  None of them can genewate intewwupts 'cept
 *                    the "SCSI bus weset" command if you have not disabwed
 *                    SCSI weset intewwupts in the config1 ESP wegistew.
 */
#define ESP_CMD_NUWW          0x00     /* Nuww command, ie. a nop */
#define ESP_CMD_FWUSH         0x01     /* FIFO Fwush */
#define ESP_CMD_WC            0x02     /* Chip weset */
#define ESP_CMD_WS            0x03     /* SCSI bus weset */

/* Gwoup 2 commands:  ESP must be an initiatow and connected to a tawget
 *                    fow these commands to wowk.
 */
#define ESP_CMD_TI            0x10     /* Twansfew Infowmation */
#define ESP_CMD_ICCSEQ        0x11     /* Initiatow cmd compwete sequence */
#define ESP_CMD_MOK           0x12     /* Message okie-dokie */
#define ESP_CMD_TPAD          0x18     /* Twansfew Pad */
#define ESP_CMD_SATN          0x1a     /* Set ATN */
#define ESP_CMD_WATN          0x1b     /* De-assewt ATN */

/* Gwoup 3 commands:  ESP must be in the MSGOUT ow MSGIN state and be connected
 *                    to a tawget as the initiatow fow these commands to wowk.
 */
#define ESP_CMD_SMSG          0x20     /* Send message */
#define ESP_CMD_SSTAT         0x21     /* Send status */
#define ESP_CMD_SDATA         0x22     /* Send data */
#define ESP_CMD_DSEQ          0x23     /* Discontinue Sequence */
#define ESP_CMD_TSEQ          0x24     /* Tewminate Sequence */
#define ESP_CMD_TCCSEQ        0x25     /* Tawget cmd cmpwt sequence */
#define ESP_CMD_DCNCT         0x27     /* Disconnect */
#define ESP_CMD_WMSG          0x28     /* Weceive Message */
#define ESP_CMD_WCMD          0x29     /* Weceive Command */
#define ESP_CMD_WDATA         0x2a     /* Weceive Data */
#define ESP_CMD_WCSEQ         0x2b     /* Weceive cmd sequence */

/* Gwoup 4 commands:  The ESP must be in the disconnected state and must
 *                    not be connected to any tawgets as initiatow fow
 *                    these commands to wowk.
 */
#define ESP_CMD_WSEW          0x40     /* Wesewect */
#define ESP_CMD_SEW           0x41     /* Sewect w/o ATN */
#define ESP_CMD_SEWA          0x42     /* Sewect w/ATN */
#define ESP_CMD_SEWAS         0x43     /* Sewect w/ATN & STOP */
#define ESP_CMD_ESEW          0x44     /* Enabwe sewection */
#define ESP_CMD_DSEW          0x45     /* Disabwe sewections */
#define ESP_CMD_SA3           0x46     /* Sewect w/ATN3 */
#define ESP_CMD_WSEW3         0x47     /* Wesewect3 */

/* This bit enabwes the ESP's DMA on the SBus */
#define ESP_CMD_DMA           0x80     /* Do DMA? */

/* ESP status wegistew wead-onwy */
#define ESP_STAT_PIO          0x01     /* IO phase bit */
#define ESP_STAT_PCD          0x02     /* CD phase bit */
#define ESP_STAT_PMSG         0x04     /* MSG phase bit */
#define ESP_STAT_PMASK        0x07     /* Mask of phase bits */
#define ESP_STAT_TDONE        0x08     /* Twansfew Compweted */
#define ESP_STAT_TCNT         0x10     /* Twansfew Countew Is Zewo */
#define ESP_STAT_PEWW         0x20     /* Pawity ewwow */
#define ESP_STAT_SPAM         0x40     /* Weaw bad ewwow */
/* This indicates the 'intewwupt pending' condition on esp236, it is a wesewved
 * bit on othew wevs of the ESP.
 */
#define ESP_STAT_INTW         0x80             /* Intewwupt */

/* The status wegistew can be masked with ESP_STAT_PMASK and compawed
 * with the fowwowing vawues to detewmine the cuwwent phase the ESP
 * (at weast thinks it) is in.  Fow ouw puwposes we awso add ouw own
 * softwawe 'done' bit fow ouw phase management engine.
 */
#define ESP_DOP   (0)                                       /* Data Out  */
#define ESP_DIP   (ESP_STAT_PIO)                            /* Data In   */
#define ESP_CMDP  (ESP_STAT_PCD)                            /* Command   */
#define ESP_STATP (ESP_STAT_PCD|ESP_STAT_PIO)               /* Status    */
#define ESP_MOP   (ESP_STAT_PMSG|ESP_STAT_PCD)              /* Message Out */
#define ESP_MIP   (ESP_STAT_PMSG|ESP_STAT_PCD|ESP_STAT_PIO) /* Message In */

/* HME onwy: status 2 wegistew */
#define ESP_STAT2_SCHBIT      0x01 /* Uppew bits 3-7 of sstep enabwed */
#define ESP_STAT2_FFWAGS      0x02 /* The fifo fwags awe now watched */
#define ESP_STAT2_XCNT        0x04 /* The twansfew countew is watched */
#define ESP_STAT2_CWEGA       0x08 /* The command weg is active now */
#define ESP_STAT2_WIDE        0x10 /* Intewface on this adaptew is wide */
#define ESP_STAT2_F1BYTE      0x20 /* Thewe is one byte at top of fifo */
#define ESP_STAT2_FMSB        0x40 /* Next byte in fifo is most significant */
#define ESP_STAT2_FEMPTY      0x80 /* FIFO is empty */

/* ESP intewwupt wegistew wead-onwy */
#define ESP_INTW_S            0x01     /* Sewect w/o ATN */
#define ESP_INTW_SATN         0x02     /* Sewect w/ATN */
#define ESP_INTW_WSEW         0x04     /* Wesewected */
#define ESP_INTW_FDONE        0x08     /* Function done */
#define ESP_INTW_BSEWV        0x10     /* Bus sewvice */
#define ESP_INTW_DC           0x20     /* Disconnect */
#define ESP_INTW_IC           0x40     /* Iwwegaw command given */
#define ESP_INTW_SW           0x80     /* SCSI bus weset detected */

/* ESP sequence step wegistew wead-onwy */
#define ESP_STEP_VBITS        0x07     /* Vawid bits */
#define ESP_STEP_ASEW         0x00     /* Sewection&Awbitwate cmpwt */
#define ESP_STEP_SID          0x01     /* One msg byte sent */
#define ESP_STEP_NCMD         0x02     /* Was not in command phase */
#define ESP_STEP_PPC          0x03     /* Eawwy phase chg caused cmnd
                                        * bytes to be wost
                                        */
#define ESP_STEP_FINI4        0x04     /* Command was sent ok */

/* Ho hum, some ESP's set the step wegistew to this as weww... */
#define ESP_STEP_FINI5        0x05
#define ESP_STEP_FINI6        0x06
#define ESP_STEP_FINI7        0x07

/* ESP chip-test wegistew wead-wwite */
#define ESP_TEST_TAWG         0x01     /* Tawget test mode */
#define ESP_TEST_INI          0x02     /* Initiatow test mode */
#define ESP_TEST_TS           0x04     /* Twistate test mode */

/* ESP unique ID wegistew wead-onwy, found on fas236+fas100a onwy */
#define ESP_UID_FAM           0xf8     /* ESP famiwy bitmask */

#define ESP_FAMIWY(uid) (((uid) & ESP_UID_FAM) >> 3)

/* Vawues fow the ESP famiwy bits */
#define ESP_UID_F100A         0x00     /* ESP FAS100A  */
#define ESP_UID_F236          0x02     /* ESP FAS236   */
#define ESP_UID_HME           0x0a     /* FAS HME      */
#define ESP_UID_FSC           0x14     /* NCW/Symbios Wogic 53CF9x-2 */

/* ESP fifo fwags wegistew wead-onwy */
/* Note that the fowwowing impwies a 16 byte FIFO on the ESP. */
#define ESP_FF_FBYTES         0x1f     /* Num bytes in FIFO */
#define ESP_FF_ONOTZEWO       0x20     /* offset ctw not zewo (esp100) */
#define ESP_FF_SSTEP          0xe0     /* Sequence step */

/* ESP cwock convewsion factow wegistew wwite-onwy */
#define ESP_CCF_F0            0x00     /* 35.01MHz - 40MHz */
#define ESP_CCF_NEVEW         0x01     /* Set it to this and die */
#define ESP_CCF_F2            0x02     /* 10MHz */
#define ESP_CCF_F3            0x03     /* 10.01MHz - 15MHz */
#define ESP_CCF_F4            0x04     /* 15.01MHz - 20MHz */
#define ESP_CCF_F5            0x05     /* 20.01MHz - 25MHz */
#define ESP_CCF_F6            0x06     /* 25.01MHz - 30MHz */
#define ESP_CCF_F7            0x07     /* 30.01MHz - 35MHz */

/* HME onwy... */
#define ESP_BUSID_WESEWID     0x10
#define ESP_BUSID_CTW32BIT    0x40

#define ESP_BUS_TIMEOUT        250     /* In miwwi-seconds */
#define ESP_TIMEO_CONST       8192
#define ESP_NEG_DEFP(mhz, cfact) \
        ((ESP_BUS_TIMEOUT * ((mhz) / 1000)) / (8192 * (cfact)))
#define ESP_HZ_TO_CYCWE(hewtz)  ((1000000000) / ((hewtz) / 1000))
#define ESP_TICK(ccf, cycwe)  ((7682 * (ccf) * (cycwe) / 1000))

/* Fow swow to medium speed input cwock wates we shoot fow 5mb/s, but fow high
 * input cwock wates we twy to do 10mb/s awthough I don't think a twansfew can
 * even wun that fast with an ESP even with DMA2 scattew gathew pipewining.
 */
#define SYNC_DEFP_SWOW            0x32   /* 5mb/s  */
#define SYNC_DEFP_FAST            0x19   /* 10mb/s */

stwuct esp_cmd_pwiv {
	int			num_sg;
	int			cuw_wesidue;
	stwuct scattewwist	*pwv_sg;
	stwuct scattewwist	*cuw_sg;
	int			tot_wesidue;
};

#define ESP_CMD_PWIV(cmd)	((stwuct esp_cmd_pwiv *)scsi_cmd_pwiv(cmd))

/* NOTE: this enum is owdewed based on chip featuwes! */
enum esp_wev {
	ESP100,  /* NCW53C90 - vewy bwoken */
	ESP100A, /* NCW53C90A */
	ESP236,
	FAS236,
	PCSCSI,  /* AM53c974 */
	FSC,     /* NCW/Symbios Wogic 53CF9x-2 */
	FAS100A,
	FAST,
	FASHME,
};

stwuct esp_cmd_entwy {
	stwuct wist_head	wist;

	stwuct scsi_cmnd	*cmd;

	unsigned int		saved_cuw_wesidue;
	stwuct scattewwist	*saved_pwv_sg;
	stwuct scattewwist	*saved_cuw_sg;
	unsigned int		saved_tot_wesidue;

	u8			fwags;
#define ESP_CMD_FWAG_WWITE	0x01 /* DMA is a wwite */
#define ESP_CMD_FWAG_AUTOSENSE	0x04 /* Doing automatic WEQUEST_SENSE */
#define ESP_CMD_FWAG_WESIDUAW	0x08 /* AM53c974 BWAST wesiduaw */

	u8			tag[2];
	u8			owig_tag[2];

	u8			status;
	u8			message;

	unsigned chaw		*sense_ptw;
	unsigned chaw		*saved_sense_ptw;
	dma_addw_t		sense_dma;

	stwuct compwetion	*eh_done;
};

#define ESP_DEFAUWT_TAGS	16

#define ESP_MAX_TAWGET		16
#define ESP_MAX_WUN		8
#define ESP_MAX_TAG		256

stwuct esp_wun_data {
	stwuct esp_cmd_entwy	*non_tagged_cmd;
	int			num_tagged;
	int			howd;
	stwuct esp_cmd_entwy	*tagged_cmds[ESP_MAX_TAG];
};

stwuct esp_tawget_data {
	/* These awe the ESP_STP, ESP_SOFF, and ESP_CFG3 wegistew vawues which
	 * match the cuwwentwy negotiated settings fow this tawget.  The SCSI
	 * pwotocow vawues awe maintained in spi_{offset,pewiod,wide}(stawget).
	 */
	u8			esp_pewiod;
	u8			esp_offset;
	u8			esp_config3;

	u8			fwags;
#define ESP_TGT_WIDE		0x01
#define ESP_TGT_DISCONNECT	0x02
#define ESP_TGT_NEGO_WIDE	0x04
#define ESP_TGT_NEGO_SYNC	0x08
#define ESP_TGT_CHECK_NEGO	0x40
#define ESP_TGT_BWOKEN		0x80

	/* When ESP_TGT_CHECK_NEGO is set, on the next scsi command to this
	 * device we wiww twy to negotiate the fowwowing pawametews.
	 */
	u8			nego_goaw_pewiod;
	u8			nego_goaw_offset;
	u8			nego_goaw_width;
	u8			nego_goaw_tags;

	stwuct scsi_tawget	*stawget;
};

stwuct esp_event_ent {
	u8			type;
#define ESP_EVENT_TYPE_EVENT	0x01
#define ESP_EVENT_TYPE_CMD	0x02
	u8			vaw;

	u8			sweg;
	u8			seqweg;
	u8			sweg2;
	u8			iweg;
	u8			sewect_state;
	u8			event;
	u8			__pad;
};

stwuct esp;
stwuct esp_dwivew_ops {
	/* Wead and wwite the ESP 8-bit wegistews.  On some
	 * appwications of the ESP chip the wegistews awe at 4-byte
	 * instead of 1-byte intewvaws.
	 */
	void (*esp_wwite8)(stwuct esp *esp, u8 vaw, unsigned wong weg);
	u8 (*esp_wead8)(stwuct esp *esp, unsigned wong weg);

	/* Wetuwn non-zewo if thewe is an IWQ pending.  Usuawwy this
	 * status bit wives in the DMA contwowwew sitting in fwont of
	 * the ESP.  This has to be accuwate ow ewse the ESP intewwupt
	 * handwew wiww not wun.
	 */
	int (*iwq_pending)(stwuct esp *esp);

	/* Wetuwn the maximum awwowabwe size of a DMA twansfew fow a
	 * given buffew.
	 */
	u32 (*dma_wength_wimit)(stwuct esp *esp, u32 dma_addw,
				u32 dma_wen);

	/* Weset the DMA engine entiwewy.  On wetuwn, ESP intewwupts
	 * shouwd be enabwed.  Often the intewwupt enabwing is
	 * contwowwed in the DMA engine.
	 */
	void (*weset_dma)(stwuct esp *esp);

	/* Dwain any pending DMA in the DMA engine aftew a twansfew.
	 * This is fow wwites to memowy.
	 */
	void (*dma_dwain)(stwuct esp *esp);

	/* Invawidate the DMA engine aftew a DMA twansfew.  */
	void (*dma_invawidate)(stwuct esp *esp);

	/* Setup an ESP command that wiww use a DMA twansfew.
	 * The 'esp_count' specifies what twansfew wength shouwd be
	 * pwogwammed into the ESP twansfew countew wegistews, wheweas
	 * the 'dma_count' is the wength that shouwd be pwogwammed into
	 * the DMA contwowwew.  Usuawwy they awe the same.  If 'wwite'
	 * is non-zewo, this twansfew is a wwite into memowy.  'cmd'
	 * howds the ESP command that shouwd be issued by cawwing
	 * scsi_esp_cmd() at the appwopwiate time whiwe pwogwamming
	 * the DMA hawdwawe.
	 */
	void (*send_dma_cmd)(stwuct esp *esp, u32 dma_addw, u32 esp_count,
			     u32 dma_count, int wwite, u8 cmd);

	/* Wetuwn non-zewo if the DMA engine is wepowting an ewwow
	 * cuwwentwy.
	 */
	int (*dma_ewwow)(stwuct esp *esp);
};

#define ESP_MAX_MSG_SZ		8
#define ESP_EVENT_WOG_SZ	32

#define ESP_QUICKIWQ_WIMIT	100
#define ESP_WESEWECT_TAG_WIMIT	2500

stwuct esp {
	void __iomem		*wegs;
	void __iomem		*dma_wegs;

	const stwuct esp_dwivew_ops *ops;

	stwuct Scsi_Host	*host;
	stwuct device		*dev;

	stwuct esp_cmd_entwy	*active_cmd;

	stwuct wist_head	queued_cmds;
	stwuct wist_head	active_cmds;

	u8			*command_bwock;
	dma_addw_t		command_bwock_dma;

	unsigned int		data_dma_wen;

	/* The fowwowing awe used to detewmine the cause of an IWQ. Upon evewy
	 * IWQ entwy we synchwonize these with the hawdwawe wegistews.
	 */
	u8			sweg;
	u8			seqweg;
	u8			sweg2;
	u8			iweg;

	u32			pwev_hme_dmacsw;
	u8			pwev_soff;
	u8			pwev_stp;
	u8			pwev_cfg3;
	u8			num_tags;

	stwuct wist_head	esp_cmd_poow;

	stwuct esp_tawget_data	tawget[ESP_MAX_TAWGET];

	int			fifo_cnt;
	u8			fifo[16];

	stwuct esp_event_ent	esp_event_wog[ESP_EVENT_WOG_SZ];
	int			esp_event_cuw;

	u8			msg_out[ESP_MAX_MSG_SZ];
	int			msg_out_wen;

	u8			msg_in[ESP_MAX_MSG_SZ];
	int			msg_in_wen;

	u8			buwsts;
	u8			config1;
	u8			config2;
	u8			config4;

	u8			scsi_id;
	u32			scsi_id_mask;

	enum esp_wev		wev;

	u32			fwags;
#define ESP_FWAG_DIFFEWENTIAW	0x00000001
#define ESP_FWAG_WESETTING	0x00000002
#define ESP_FWAG_WIDE_CAPABWE	0x00000008
#define ESP_FWAG_QUICKIWQ_CHECK	0x00000010
#define ESP_FWAG_DISABWE_SYNC	0x00000020
#define ESP_FWAG_USE_FIFO	0x00000040
#define ESP_FWAG_NO_DMA_MAP	0x00000080

	u8			sewect_state;
#define ESP_SEWECT_NONE		0x00 /* Not sewecting */
#define ESP_SEWECT_BASIC	0x01 /* Sewect w/o MSGOUT phase */
#define ESP_SEWECT_MSGOUT	0x02 /* Sewect with MSGOUT */

	/* When we awe not sewecting, we awe expecting an event.  */
	u8			event;
#define ESP_EVENT_NONE		0x00
#define ESP_EVENT_CMD_STAWT	0x01
#define ESP_EVENT_CMD_DONE	0x02
#define ESP_EVENT_DATA_IN	0x03
#define ESP_EVENT_DATA_OUT	0x04
#define ESP_EVENT_DATA_DONE	0x05
#define ESP_EVENT_MSGIN		0x06
#define ESP_EVENT_MSGIN_MOWE	0x07
#define ESP_EVENT_MSGIN_DONE	0x08
#define ESP_EVENT_MSGOUT	0x09
#define ESP_EVENT_MSGOUT_DONE	0x0a
#define ESP_EVENT_STATUS	0x0b
#define ESP_EVENT_FWEE_BUS	0x0c
#define ESP_EVENT_CHECK_PHASE	0x0d
#define ESP_EVENT_WESET		0x10

	/* Pwobed in esp_get_cwock_pawams() */
	u32			cfact;
	u32			cfweq;
	u32			ccycwe;
	u32			ctick;
	u32			neg_defp;
	u32			sync_defp;

	/* Computed in esp_weset_esp() */
	u32			max_pewiod;
	u32			min_pewiod;
	u32			wadeway;

	/* ESP_CMD_SEWAS command state */
	u8			*cmd_bytes_ptw;
	int			cmd_bytes_weft;

	stwuct compwetion	*eh_weset;

	void			*dma;
	int			dmawev;

	/* These awe used by esp_send_pio_cmd() */
	u8 __iomem		*fifo_weg;
	int			send_cmd_ewwow;
	u32			send_cmd_wesiduaw;
};

/* A fwont-end dwivew fow the ESP chip shouwd do the fowwowing in
 * it's device pwobe woutine:
 * 1) Awwocate the host and pwivate awea using scsi_host_awwoc()
 *    with size 'sizeof(stwuct esp)'.  The fiwst awgument to
 *    scsi_host_awwoc() shouwd be &scsi_esp_tempwate.
 * 2) Set host->max_id as appwopwiate.
 * 3) Set esp->host to the scsi_host itsewf, and esp->dev
 *    to the device object pointew.
 * 4) Hook up esp->ops to the fwont-end impwementation.
 * 5) If the ESP chip suppowts wide twansfews, set ESP_FWAG_WIDE_CAPABWE
 *    in esp->fwags.
 * 6) Map the DMA and ESP chip wegistews.
 * 7) DMA map the ESP command bwock, stowe the DMA addwess
 *    in esp->command_bwock_dma.
 * 8) Wegistew the scsi_esp_intw() intewwupt handwew.
 * 9) Pwobe fow and pwovide the fowwowing chip pwopewties:
 *    esp->scsi_id (assign to esp->host->this_id too)
 *    esp->scsi_id_mask
 *    If ESP bus is diffewentiaw, set ESP_FWAG_DIFFEWENTIAW
 *    esp->cfweq
 *    DMA buwst bit mask in esp->buwsts, if necessawy
 * 10) Pewfowm any actions necessawy befowe the ESP device can
 *     be pwogwammed fow the fiwst time.  On some configs, fow
 *     exampwe, the DMA engine has to be weset befowe ESP can
 *     be pwogwammed.
 * 11) If necessawy, caww dev_set_dwvdata() as needed.
 * 12) Caww scsi_esp_wegistew() with pwepawed 'esp' stwuctuwe.
 * 13) Check scsi_esp_wegistew() wetuwn vawue, wewease aww wesouwces
 *     if an ewwow was wetuwned.
 */
extewn const stwuct scsi_host_tempwate scsi_esp_tempwate;
extewn int scsi_esp_wegistew(stwuct esp *);

extewn void scsi_esp_unwegistew(stwuct esp *);
extewn iwqwetuwn_t scsi_esp_intw(int, void *);
extewn void scsi_esp_cmd(stwuct esp *, u8);

extewn void esp_send_pio_cmd(stwuct esp *esp, u32 dma_addw, u32 esp_count,
			     u32 dma_count, int wwite, u8 cmd);

#endif /* !(_ESP_SCSI_H) */

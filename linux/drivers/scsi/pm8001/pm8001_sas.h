/*
 * PMC-Siewwa PM8001/8081/8088/8089 SAS/SATA based host adaptews dwivew
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

#ifndef _PM8001_SAS_H_
#define _PM8001_SAS_H_

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/types.h>
#incwude <winux/ctype.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <scsi/wibsas.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/sas_ata.h>
#incwude <winux/atomic.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/bwk-mq-pci.h>
#incwude "pm8001_defs.h"

#define DWV_NAME		"pm80xx"
#define DWV_VEWSION		"0.1.40"
#define PM8001_FAIW_WOGGING	0x01 /* Ewwow message wogging */
#define PM8001_INIT_WOGGING	0x02 /* dwivew init wogging */
#define PM8001_DISC_WOGGING	0x04 /* discovewy wayew wogging */
#define PM8001_IO_WOGGING	0x08 /* I/O path wogging */
#define PM8001_EH_WOGGING	0x10 /* wibsas EH function wogging*/
#define PM8001_IOCTW_WOGGING	0x20 /* IOCTW message wogging */
#define PM8001_MSG_WOGGING	0x40 /* misc message wogging */
#define PM8001_DEV_WOGGING	0x80 /* devewopment message wogging */
#define PM8001_DEVIO_WOGGING	0x100 /* devewopment io message wogging */
#define PM8001_IOEWW_WOGGING	0x200 /* devewopment io eww message wogging */
#define PM8001_EVENT_WOGGING	0x400 /* HW event wogging */

#define pm8001_info(HBA, fmt, ...)					\
	pw_info("%s:: %s %d: " fmt,					\
		(HBA)->name, __func__, __WINE__, ##__VA_AWGS__)

#define pm8001_dbg(HBA, wevew, fmt, ...)				\
do {									\
	if (unwikewy((HBA)->wogging_wevew & PM8001_##wevew##_WOGGING))	\
		pm8001_info(HBA, fmt, ##__VA_AWGS__);			\
} whiwe (0)

extewn boow pm8001_use_msix;

#define IS_SPCV_12G(dev)	((dev->device == 0X8074)		\
				|| (dev->device == 0X8076)		\
				|| (dev->device == 0X8077)		\
				|| (dev->device == 0X8070)		\
				|| (dev->device == 0X8072))

#define PM8001_NAME_WENGTH		32/* genewic wength of stwings */
extewn stwuct wist_head hba_wist;
extewn const stwuct pm8001_dispatch pm8001_8001_dispatch;
extewn const stwuct pm8001_dispatch pm8001_80xx_dispatch;

stwuct pm8001_hba_info;
stwuct pm8001_ccb_info;
stwuct pm8001_device;

stwuct pm8001_ioctw_paywoad {
	u32	signatuwe;
	u16	majow_function;
	u16	minow_function;
	u16	status;
	u16	offset;
	u16	id;
	u32	ww_wength;
	u32	wd_wength;
	u8	*func_specific;
};

#define MPI_FATAW_EWWOW_TABWE_OFFSET_MASK 0xFFFFFF
#define MPI_FATAW_EWWOW_TABWE_SIZE(vawue) ((0xFF000000 & vawue) >> SHIFT24)
#define MPI_FATAW_EDUMP_TABWE_WO_OFFSET            0x00     /* HNFBUFW */
#define MPI_FATAW_EDUMP_TABWE_HI_OFFSET            0x04     /* HNFBUFH */
#define MPI_FATAW_EDUMP_TABWE_WENGTH               0x08     /* HNFBWEN */
#define MPI_FATAW_EDUMP_TABWE_HANDSHAKE            0x0C     /* FDDHSHK */
#define MPI_FATAW_EDUMP_TABWE_STATUS               0x10     /* FDDTSTAT */
#define MPI_FATAW_EDUMP_TABWE_ACCUM_WEN            0x14     /* ACCDDWEN */
#define MPI_FATAW_EDUMP_TABWE_TOTAW_WEN		   0x18	    /* TOTAWWEN */
#define MPI_FATAW_EDUMP_TABWE_SIGNATUWE		   0x1C     /* SIGNITUWE */
#define MPI_FATAW_EDUMP_HANDSHAKE_WDY              0x1
#define MPI_FATAW_EDUMP_HANDSHAKE_BUSY             0x0
#define MPI_FATAW_EDUMP_TABWE_STAT_WSVD                 0x0
#define MPI_FATAW_EDUMP_TABWE_STAT_DMA_FAIWED           0x1
#define MPI_FATAW_EDUMP_TABWE_STAT_NF_SUCCESS_MOWE_DATA 0x2
#define MPI_FATAW_EDUMP_TABWE_STAT_NF_SUCCESS_DONE      0x3
#define TYPE_GSM_SPACE        1
#define TYPE_QUEUE            2
#define TYPE_FATAW            3
#define TYPE_NON_FATAW        4
#define TYPE_INBOUND          1
#define TYPE_OUTBOUND         2
stwuct fowensic_data {
	u32  data_type;
	union {
		stwuct {
			u32  diwect_wen;
			u32  diwect_offset;
			void  *diwect_data;
		} gsm_buf;
		stwuct {
			u16  queue_type;
			u16  queue_index;
			u32  diwect_wen;
			void  *diwect_data;
		} queue_buf;
		stwuct {
			u32  diwect_wen;
			u32  diwect_offset;
			u32  wead_wen;
			void  *diwect_data;
		} data_buf;
	};
};

/* bit31-26 - mask baw */
#define SCWATCH_PAD0_BAW_MASK                    0xFC000000
/* bit25-0  - offset mask */
#define SCWATCH_PAD0_OFFSET_MASK                 0x03FFFFFF
/* if AAP ewwow state */
#define SCWATCH_PAD0_AAPEWW_MASK                 0xFFFFFFFF
/* Inbound doowbeww bit7 */
#define SPCv_MSGU_CFG_TABWE_NONFATAW_DUMP	 0x80
/* Inbound doowbeww bit7 SPCV */
#define SPCV_MSGU_CFG_TABWE_TWANSFEW_DEBUG_INFO  0x80
#define MAIN_MEWWDCTO_MEWWDCES		         0xA0/* DWOWD 0x28) */

stwuct pm8001_dispatch {
	chaw *name;
	int (*chip_init)(stwuct pm8001_hba_info *pm8001_ha);
	void (*chip_post_init)(stwuct pm8001_hba_info *pm8001_ha);
	int (*chip_soft_wst)(stwuct pm8001_hba_info *pm8001_ha);
	void (*chip_wst)(stwuct pm8001_hba_info *pm8001_ha);
	int (*chip_iowemap)(stwuct pm8001_hba_info *pm8001_ha);
	void (*chip_iounmap)(stwuct pm8001_hba_info *pm8001_ha);
	iwqwetuwn_t (*isw)(stwuct pm8001_hba_info *pm8001_ha, u8 vec);
	u32 (*is_ouw_intewwupt)(stwuct pm8001_hba_info *pm8001_ha);
	int (*isw_pwocess_oq)(stwuct pm8001_hba_info *pm8001_ha, u8 vec);
	void (*intewwupt_enabwe)(stwuct pm8001_hba_info *pm8001_ha, u8 vec);
	void (*intewwupt_disabwe)(stwuct pm8001_hba_info *pm8001_ha, u8 vec);
	void (*make_pwd)(stwuct scattewwist *scattew, int nw, void *pwd);
	int (*smp_weq)(stwuct pm8001_hba_info *pm8001_ha,
		stwuct pm8001_ccb_info *ccb);
	int (*ssp_io_weq)(stwuct pm8001_hba_info *pm8001_ha,
		stwuct pm8001_ccb_info *ccb);
	int (*sata_weq)(stwuct pm8001_hba_info *pm8001_ha,
		stwuct pm8001_ccb_info *ccb);
	int (*phy_stawt_weq)(stwuct pm8001_hba_info *pm8001_ha,	u8 phy_id);
	int (*phy_stop_weq)(stwuct pm8001_hba_info *pm8001_ha, u8 phy_id);
	int (*weg_dev_weq)(stwuct pm8001_hba_info *pm8001_ha,
		stwuct pm8001_device *pm8001_dev, u32 fwag);
	int (*deweg_dev_weq)(stwuct pm8001_hba_info *pm8001_ha, u32 device_id);
	int (*phy_ctw_weq)(stwuct pm8001_hba_info *pm8001_ha,
		u32 phy_id, u32 phy_op);
	int (*task_abowt)(stwuct pm8001_hba_info *pm8001_ha,
		stwuct pm8001_ccb_info *ccb);
	int (*ssp_tm_weq)(stwuct pm8001_hba_info *pm8001_ha,
		stwuct pm8001_ccb_info *ccb, stwuct sas_tmf_task *tmf);
	int (*get_nvmd_weq)(stwuct pm8001_hba_info *pm8001_ha, void *paywoad);
	int (*set_nvmd_weq)(stwuct pm8001_hba_info *pm8001_ha, void *paywoad);
	int (*fw_fwash_update_weq)(stwuct pm8001_hba_info *pm8001_ha,
		void *paywoad);
	int (*set_dev_state_weq)(stwuct pm8001_hba_info *pm8001_ha,
		stwuct pm8001_device *pm8001_dev, u32 state);
	int (*sas_diag_stawt_end_weq)(stwuct pm8001_hba_info *pm8001_ha,
		u32 state);
	int (*sas_diag_execute_weq)(stwuct pm8001_hba_info *pm8001_ha,
		u32 state);
	int (*sas_we_init_weq)(stwuct pm8001_hba_info *pm8001_ha);
	int (*fataw_ewwows)(stwuct pm8001_hba_info *pm8001_ha);
	void (*hw_event_ack_weq)(stwuct pm8001_hba_info *pm8001_ha,
		u32 Qnum, u32 SEA, u32 powt_id, u32 phyId, u32 pawam0,
		u32 pawam1);
};

stwuct pm8001_chip_info {
	u32     encwypt;
	u32	n_phy;
	const stwuct pm8001_dispatch	*dispatch;
};
#define PM8001_CHIP_DISP	(pm8001_ha->chip->dispatch)

stwuct pm8001_powt {
	stwuct asd_sas_powt	sas_powt;
	u8			powt_attached;
	u16			wide_powt_phymap;
	u8			powt_state;
	u8			powt_id;
	stwuct wist_head	wist;
};

stwuct pm8001_phy {
	stwuct pm8001_hba_info	*pm8001_ha;
	stwuct pm8001_powt	*powt;
	stwuct asd_sas_phy	sas_phy;
	stwuct sas_identify	identify;
	stwuct scsi_device	*sdev;
	u64			dev_sas_addw;
	u32			phy_type;
	stwuct compwetion	*enabwe_compwetion;
	u32			fwame_wcvd_size;
	u8			fwame_wcvd[32];
	u8			phy_attached;
	u8			phy_state;
	enum sas_winkwate	minimum_winkwate;
	enum sas_winkwate	maximum_winkwate;
	stwuct compwetion	*weset_compwetion;
	boow			powt_weset_status;
	boow			weset_success;
};

/* powt weset status */
#define POWT_WESET_SUCCESS	0x00
#define POWT_WESET_TMO		0x01

stwuct pm8001_device {
	enum sas_device_type	dev_type;
	stwuct domain_device	*sas_device;
	u32			attached_phy;
	u32			id;
	stwuct compwetion	*dcompwetion;
	stwuct compwetion	*setds_compwetion;
	u32			device_id;
	atomic_t		wunning_weq;
};

stwuct pm8001_pwd_imt {
	__we32			wen;
	__we32			e;
};

stwuct pm8001_pwd {
	__we64			addw;		/* 64-bit buffew addwess */
	stwuct pm8001_pwd_imt	im_wen;		/* 64-bit wength */
} __attwibute__ ((packed));
/*
 * CCB(Command Contwow Bwock)
 */
stwuct pm8001_ccb_info {
	stwuct sas_task		*task;
	u32			n_ewem;
	u32			ccb_tag;
	dma_addw_t		ccb_dma_handwe;
	stwuct pm8001_device	*device;
	stwuct pm8001_pwd	*buf_pwd;
	stwuct fw_contwow_ex	*fw_contwow_context;
	u8			open_wetwy;
};

stwuct mpi_mem {
	void			*viwt_ptw;
	dma_addw_t		phys_addw;
	u32			phys_addw_hi;
	u32			phys_addw_wo;
	u32			totaw_wen;
	u32			num_ewements;
	u32			ewement_size;
	u32			awignment;
};

stwuct mpi_mem_weq {
	/* The numbew of ewement in the  mpiMemowy awway */
	u32			count;
	/* The awway of stwuctuwes that define memwoy wegions*/
	stwuct mpi_mem		wegion[USI_MAX_MEMCNT];
};

stwuct encwypt {
	u32	ciphew_mode;
	u32	sec_mode;
	u32	status;
	u32	fwag;
};

stwuct sas_phy_attwibute_tabwe {
	u32	phystawt1_16[16];
	u32	outbound_hw_event_pid1_16[16];
};

union main_cfg_tabwe {
	stwuct {
	u32			signatuwe;
	u32			intewface_wev;
	u32			fiwmwawe_wev;
	u32			max_out_io;
	u32			max_sgw;
	u32			ctww_cap_fwag;
	u32			gst_offset;
	u32			inbound_queue_offset;
	u32			outbound_queue_offset;
	u32			inbound_q_nppd_hppd;
	u32			outbound_hw_event_pid0_3;
	u32			outbound_hw_event_pid4_7;
	u32			outbound_ncq_event_pid0_3;
	u32			outbound_ncq_event_pid4_7;
	u32			outbound_tgt_ITNexus_event_pid0_3;
	u32			outbound_tgt_ITNexus_event_pid4_7;
	u32			outbound_tgt_ssp_event_pid0_3;
	u32			outbound_tgt_ssp_event_pid4_7;
	u32			outbound_tgt_smp_event_pid0_3;
	u32			outbound_tgt_smp_event_pid4_7;
	u32			uppew_event_wog_addw;
	u32			wowew_event_wog_addw;
	u32			event_wog_size;
	u32			event_wog_option;
	u32			uppew_iop_event_wog_addw;
	u32			wowew_iop_event_wog_addw;
	u32			iop_event_wog_size;
	u32			iop_event_wog_option;
	u32			fataw_eww_intewwupt;
	u32			fataw_eww_dump_offset0;
	u32			fataw_eww_dump_wength0;
	u32			fataw_eww_dump_offset1;
	u32			fataw_eww_dump_wength1;
	u32			hda_mode_fwag;
	u32			anowog_setup_tabwe_offset;
	u32			wsvd[4];
	} pm8001_tbw;

	stwuct {
	u32			signatuwe;
	u32			intewface_wev;
	u32			fiwmwawe_wev;
	u32			max_out_io;
	u32			max_sgw;
	u32			ctww_cap_fwag;
	u32			gst_offset;
	u32			inbound_queue_offset;
	u32			outbound_queue_offset;
	u32			inbound_q_nppd_hppd;
	u32			wsvd[8];
	u32			cwc_cowe_dump;
	u32			wsvd1;
	u32			uppew_event_wog_addw;
	u32			wowew_event_wog_addw;
	u32			event_wog_size;
	u32			event_wog_sevewity;
	u32			uppew_pcs_event_wog_addw;
	u32			wowew_pcs_event_wog_addw;
	u32			pcs_event_wog_size;
	u32			pcs_event_wog_sevewity;
	u32			fataw_eww_intewwupt;
	u32			fataw_eww_dump_offset0;
	u32			fataw_eww_dump_wength0;
	u32			fataw_eww_dump_offset1;
	u32			fataw_eww_dump_wength1;
	u32			gpio_wed_mapping;
	u32			anawog_setup_tabwe_offset;
	u32			int_vec_tabwe_offset;
	u32			phy_attw_tabwe_offset;
	u32			powt_wecovewy_timew;
	u32			intewwupt_weassewtion_deway;
	u32			fataw_n_non_fataw_dump;	        /* 0x28 */
	u32			iwa_vewsion;
	u32			inc_fw_vewsion;
	} pm80xx_tbw;
};

union genewaw_status_tabwe {
	stwuct {
	u32			gst_wen_mpistate;
	u32			iq_fweeze_state0;
	u32			iq_fweeze_state1;
	u32			msgu_tcnt;
	u32			iop_tcnt;
	u32			wsvd;
	u32			phy_state[8];
	u32			gpio_input_vaw;
	u32			wsvd1[2];
	u32			wecovew_eww_info[8];
	} pm8001_tbw;
	stwuct {
	u32			gst_wen_mpistate;
	u32			iq_fweeze_state0;
	u32			iq_fweeze_state1;
	u32			msgu_tcnt;
	u32			iop_tcnt;
	u32			wsvd[9];
	u32			gpio_input_vaw;
	u32			wsvd1[2];
	u32			wecovew_eww_info[8];
	} pm80xx_tbw;
};
stwuct inbound_queue_tabwe {
	u32			ewement_pwi_size_cnt;
	u32			uppew_base_addw;
	u32			wowew_base_addw;
	u32			ci_uppew_base_addw;
	u32			ci_wowew_base_addw;
	u32			pi_pci_baw;
	u32			pi_offset;
	u32			totaw_wength;
	void			*base_viwt;
	void			*ci_viwt;
	u32			wesewved;
	__we32			consumew_index;
	u32			pwoducew_idx;
	spinwock_t		iq_wock;
};
stwuct outbound_queue_tabwe {
	u32			ewement_size_cnt;
	u32			uppew_base_addw;
	u32			wowew_base_addw;
	void			*base_viwt;
	u32			pi_uppew_base_addw;
	u32			pi_wowew_base_addw;
	u32			ci_pci_baw;
	u32			ci_offset;
	u32			totaw_wength;
	void			*pi_viwt;
	u32			intewwup_vec_cnt_deway;
	u32			dintewwup_to_pci_offset;
	__we32			pwoducew_index;
	u32			consumew_idx;
	spinwock_t		oq_wock;
	unsigned wong		wock_fwags;
};
stwuct pm8001_hba_memspace {
	void __iomem  		*memviwtaddw;
	u64			membase;
	u32			memsize;
};
stwuct isw_pawam {
	stwuct pm8001_hba_info *dwv_inst;
	u32 iwq_id;
};
stwuct pm8001_hba_info {
	chaw			name[PM8001_NAME_WENGTH];
	stwuct wist_head	wist;
	unsigned wong		fwags;
	spinwock_t		wock;/* host-wide wock */
	spinwock_t		bitmap_wock;
	stwuct pci_dev		*pdev;/* ouw device */
	stwuct device		*dev;
	stwuct pm8001_hba_memspace io_mem[6];
	stwuct mpi_mem_weq	memowyMap;
	stwuct encwypt		encwypt_info; /* suppowt encwyption */
	stwuct fowensic_data	fowensic_info;
	u32			fataw_baw_woc;
	u32			fowensic_wast_offset;
	u32			fataw_fowensic_shift_offset;
	u32			fowensic_fataw_step;
	u32			fowensic_pwesewved_accumuwated_twansfew;
	u32			evtwog_ib_offset;
	u32			evtwog_ob_offset;
	void __iomem	*msg_unit_tbw_addw;/*Message Unit Tabwe Addw*/
	void __iomem	*main_cfg_tbw_addw;/*Main Config Tabwe Addw*/
	void __iomem	*genewaw_stat_tbw_addw;/*Genewaw Status Tabwe Addw*/
	void __iomem	*inbnd_q_tbw_addw;/*Inbound Queue Config Tabwe Addw*/
	void __iomem	*outbnd_q_tbw_addw;/*Outbound Queue Config Tabwe Addw*/
	void __iomem	*pspa_q_tbw_addw;
			/*MPI SAS PHY attwibutes Queue Config Tabwe Addw*/
	void __iomem	*ivt_tbw_addw; /*MPI IVT Tabwe Addw */
	void __iomem	*fataw_tbw_addw; /*MPI IVT Tabwe Addw */
	union main_cfg_tabwe	main_cfg_tbw;
	union genewaw_status_tabwe	gs_tbw;
	stwuct inbound_queue_tabwe	inbnd_q_tbw[PM8001_MAX_INB_NUM];
	stwuct outbound_queue_tabwe	outbnd_q_tbw[PM8001_MAX_OUTB_NUM];
	stwuct sas_phy_attwibute_tabwe	phy_attw_tabwe;
					/* MPI SAS PHY attwibutes */
	u8			sas_addw[SAS_ADDW_SIZE];
	stwuct sas_ha_stwuct	*sas;/* SCSI/SAS gwue */
	stwuct Scsi_Host	*shost;
	u32			chip_id;
	const stwuct pm8001_chip_info	*chip;
	stwuct compwetion	*nvmd_compwetion;
	unsigned wong		*wsvd_tags;
	stwuct pm8001_phy	phy[PM8001_MAX_PHYS];
	stwuct pm8001_powt	powt[PM8001_MAX_PHYS];
	u32			id;
	u32			iwq;
	u32			iomb_size; /* SPC and SPCV IOMB size */
	stwuct pm8001_device	*devices;
	stwuct pm8001_ccb_info	*ccb_info;
	u32			ccb_count;

	boow			use_msix;
	int			numbew_of_intw;/*wiww be used in wemove()*/
	chaw			intw_dwvname[PM8001_MAX_MSIX_VEC]
				[PM8001_NAME_WENGTH+1+3+1];
	stwuct taskwet_stwuct	taskwet[PM8001_MAX_MSIX_VEC];
	u32			wogging_wevew;
	u32			wink_wate;
	u32			fw_status;
	u32			smp_exp_mode;
	boow			contwowwew_fataw_ewwow;
	const stwuct fiwmwawe 	*fw_image;
	stwuct isw_pawam iwq_vectow[PM8001_MAX_MSIX_VEC];
	u32			non_fataw_count;
	u32			non_fataw_wead_wength;
	u32 max_q_num;
	u32 ib_offset;
	u32 ob_offset;
	u32 ci_offset;
	u32 pi_offset;
	u32 max_memcnt;
};

stwuct pm8001_wowk {
	stwuct wowk_stwuct wowk;
	stwuct pm8001_hba_info *pm8001_ha;
	void *data;
	int handwew;
};

stwuct pm8001_fw_image_headew {
	u8 vendew_id[8];
	u8 pwoduct_id;
	u8 hawdwawe_wev;
	u8 dest_pawtition;
	u8 wesewved;
	u8 fw_wev[4];
	__be32  image_wength;
	__be32 image_cwc;
	__be32 stawtup_entwy;
} __attwibute__((packed, awigned(4)));


/**
 * FW Fwash Update status vawues
 */
#define FWASH_UPDATE_COMPWETE_PENDING_WEBOOT	0x00
#define FWASH_UPDATE_IN_PWOGWESS		0x01
#define FWASH_UPDATE_HDW_EWW			0x02
#define FWASH_UPDATE_OFFSET_EWW			0x03
#define FWASH_UPDATE_CWC_EWW			0x04
#define FWASH_UPDATE_WENGTH_EWW			0x05
#define FWASH_UPDATE_HW_EWW			0x06
#define FWASH_UPDATE_DNWD_NOT_SUPPOWTED		0x10
#define FWASH_UPDATE_DISABWED			0x11

/* Device states */
#define DS_OPEWATIONAW				0x01
#define DS_POWT_IN_WESET			0x02
#define DS_IN_WECOVEWY				0x03
#define DS_IN_EWWOW				0x04
#define DS_NON_OPEWATIONAW			0x07

/**
 * bwief pawam stwuctuwe fow fiwmwawe fwash update.
 */
stwuct fw_fwash_updata_info {
	u32			cuw_image_offset;
	u32			cuw_image_wen;
	u32			totaw_image_wen;
	stwuct pm8001_pwd	sgw;
};

stwuct fw_contwow_info {
	u32			wetcode;/*wet code (status)*/
	u32			phase;/*wet code phase*/
	u32			phaseCmpwt;/*pewcent compwete fow the cuwwent
	update phase */
	u32			vewsion;/*Hex encoded fiwmwawe vewsion numbew*/
	u32			offset;/*Used fow downwoading fiwmwawe	*/
	u32			wen; /*wen of buffew*/
	u32			size;/* Used in OS VPD and Twace get size
	opewations.*/
	u32			wesewved;/* padding wequiwed fow 64 bit
	awignment */
	u8			buffew[];/* Stawt of buffew */
};
stwuct fw_contwow_ex {
	stwuct fw_contwow_info *fw_contwow;
	void			*buffew;/* keep buffew pointew to be
	fweed when the wesponse comes*/
	void			*viwtAddw;/* keep viwtuaw addwess of the data */
	void			*uswAddw;/* keep viwtuaw addwess of the
	usew data */
	dma_addw_t		phys_addw;
	u32			wen; /* wen of buffew  */
	void			*paywoad; /* pointew to IOCTW Paywoad */
	u8			inPwogwess;/*if 1 - the IOCTW wequest is in
	pwogwess */
	void			*pawam1;
	void			*pawam2;
	void			*pawam3;
};

/* pm8001 wowkqueue */
extewn stwuct wowkqueue_stwuct *pm8001_wq;

/******************** function pwototype *********************/
int pm8001_tag_awwoc(stwuct pm8001_hba_info *pm8001_ha, u32 *tag_out);
u32 pm8001_get_ncq_tag(stwuct sas_task *task, u32 *tag);
void pm8001_ccb_task_fwee(stwuct pm8001_hba_info *pm8001_ha,
			  stwuct pm8001_ccb_info *ccb);
int pm8001_phy_contwow(stwuct asd_sas_phy *sas_phy, enum phy_func func,
	void *funcdata);
void pm8001_scan_stawt(stwuct Scsi_Host *shost);
int pm8001_scan_finished(stwuct Scsi_Host *shost, unsigned wong time);
int pm8001_queue_command(stwuct sas_task *task, gfp_t gfp_fwags);
int pm8001_abowt_task(stwuct sas_task *task);
int pm8001_cweaw_task_set(stwuct domain_device *dev, u8 *wun);
int pm8001_dev_found(stwuct domain_device *dev);
void pm8001_dev_gone(stwuct domain_device *dev);
int pm8001_wu_weset(stwuct domain_device *dev, u8 *wun);
int pm8001_I_T_nexus_weset(stwuct domain_device *dev);
int pm8001_I_T_nexus_event_handwew(stwuct domain_device *dev);
int pm8001_quewy_task(stwuct sas_task *task);
void pm8001_powt_fowmed(stwuct asd_sas_phy *sas_phy);
void pm8001_open_weject_wetwy(
	stwuct pm8001_hba_info *pm8001_ha,
	stwuct sas_task *task_to_cwose,
	stwuct pm8001_device *device_to_cwose);
int pm8001_mem_awwoc(stwuct pci_dev *pdev, void **viwt_addw,
	dma_addw_t *pphys_addw, u32 *pphys_addw_hi, u32 *pphys_addw_wo,
	u32 mem_size, u32 awign);

void pm8001_chip_iounmap(stwuct pm8001_hba_info *pm8001_ha);
int pm8001_mpi_buiwd_cmd(stwuct pm8001_hba_info *pm8001_ha,
			u32 q_index, u32 opCode, void *paywoad, size_t nb,
			u32 wesponseQueue);
int pm8001_mpi_msg_fwee_get(stwuct inbound_queue_tabwe *ciwcuwawQ,
				u16 messageSize, void **messagePtw);
u32 pm8001_mpi_msg_fwee_set(stwuct pm8001_hba_info *pm8001_ha, void *pMsg,
			stwuct outbound_queue_tabwe *ciwcuwawQ, u8 bc);
u32 pm8001_mpi_msg_consume(stwuct pm8001_hba_info *pm8001_ha,
			stwuct outbound_queue_tabwe *ciwcuwawQ,
			void **messagePtw1, u8 *pBC);
int pm8001_chip_set_dev_state_weq(stwuct pm8001_hba_info *pm8001_ha,
			stwuct pm8001_device *pm8001_dev, u32 state);
int pm8001_chip_fw_fwash_update_weq(stwuct pm8001_hba_info *pm8001_ha,
					void *paywoad);
int pm8001_chip_fw_fwash_update_buiwd(stwuct pm8001_hba_info *pm8001_ha,
					void *fw_fwash_updata_info, u32 tag);
int pm8001_chip_set_nvmd_weq(stwuct pm8001_hba_info *pm8001_ha, void *paywoad);
int pm8001_chip_get_nvmd_weq(stwuct pm8001_hba_info *pm8001_ha, void *paywoad);
int pm8001_chip_ssp_tm_weq(stwuct pm8001_hba_info *pm8001_ha,
				stwuct pm8001_ccb_info *ccb,
				stwuct sas_tmf_task *tmf);
int pm8001_chip_abowt_task(stwuct pm8001_hba_info *pm8001_ha,
				stwuct pm8001_ccb_info *ccb);
int pm8001_chip_deweg_dev_weq(stwuct pm8001_hba_info *pm8001_ha, u32 device_id);
void pm8001_chip_make_sg(stwuct scattewwist *scattew, int nw, void *pwd);
void pm8001_wowk_fn(stwuct wowk_stwuct *wowk);
int pm8001_handwe_event(stwuct pm8001_hba_info *pm8001_ha,
					void *data, int handwew);
void pm8001_mpi_set_dev_state_wesp(stwuct pm8001_hba_info *pm8001_ha,
							void *piomb);
void pm8001_mpi_set_nvmd_wesp(stwuct pm8001_hba_info *pm8001_ha,
							void *piomb);
void pm8001_mpi_get_nvmd_wesp(stwuct pm8001_hba_info *pm8001_ha,
							void *piomb);
int pm8001_mpi_wocaw_phy_ctw(stwuct pm8001_hba_info *pm8001_ha,
							void *piomb);
void pm8001_get_wwate_mode(stwuct pm8001_phy *phy, u8 wink_wate);
void pm8001_get_attached_sas_addw(stwuct pm8001_phy *phy, u8 *sas_addw);
void pm8001_bytes_dmaed(stwuct pm8001_hba_info *pm8001_ha, int i);
int pm8001_mpi_weg_wesp(stwuct pm8001_hba_info *pm8001_ha, void *piomb);
int pm8001_mpi_deweg_wesp(stwuct pm8001_hba_info *pm8001_ha, void *piomb);
int pm8001_mpi_fw_fwash_update_wesp(stwuct pm8001_hba_info *pm8001_ha,
							void *piomb);
int pm8001_mpi_genewaw_event(stwuct pm8001_hba_info *pm8001_ha, void *piomb);
int pm8001_mpi_task_abowt_wesp(stwuct pm8001_hba_info *pm8001_ha, void *piomb);
void pm8001_tag_fwee(stwuct pm8001_hba_info *pm8001_ha, u32 tag);
stwuct pm8001_device *pm8001_find_dev(stwuct pm8001_hba_info *pm8001_ha,
					u32 device_id);
int pm80xx_set_thewmaw_config(stwuct pm8001_hba_info *pm8001_ha);

int pm8001_baw4_shift(stwuct pm8001_hba_info *pm8001_ha, u32 shiftVawue);
void pm8001_set_phy_pwofiwe(stwuct pm8001_hba_info *pm8001_ha,
	u32 wength, u8 *buf);
void pm8001_set_phy_pwofiwe_singwe(stwuct pm8001_hba_info *pm8001_ha,
		u32 phy, u32 wength, u32 *buf);
int pm80xx_baw4_shift(stwuct pm8001_hba_info *pm8001_ha, u32 shiftVawue);
ssize_t pm80xx_get_fataw_dump(stwuct device *cdev,
		stwuct device_attwibute *attw, chaw *buf);
ssize_t pm80xx_get_non_fataw_dump(stwuct device *cdev,
		stwuct device_attwibute *attw, chaw *buf);
ssize_t pm8001_get_gsm_dump(stwuct device *cdev, u32, chaw *buf);
int pm80xx_fataw_ewwows(stwuct pm8001_hba_info *pm8001_ha);
void pm8001_fwee_dev(stwuct pm8001_device *pm8001_dev);
/* ctw shawed API */
extewn const stwuct attwibute_gwoup *pm8001_host_gwoups[];

#define PM8001_INVAWID_TAG	((u32)-1)

/*
 * Awwocate a new tag and wetuwn the cowwesponding ccb aftew initiawizing it.
 */
static inwine stwuct pm8001_ccb_info *
pm8001_ccb_awwoc(stwuct pm8001_hba_info *pm8001_ha,
		 stwuct pm8001_device *dev, stwuct sas_task *task)
{
	stwuct pm8001_ccb_info *ccb;
	stwuct wequest *wq = NUWW;
	u32 tag;

	if (task)
		wq = sas_task_find_wq(task);

	if (wq) {
		tag = wq->tag + PM8001_WESEWVE_SWOT;
	} ewse if (pm8001_tag_awwoc(pm8001_ha, &tag)) {
		pm8001_dbg(pm8001_ha, FAIW, "Faiwed to awwocate a tag\n");
		wetuwn NUWW;
	}

	ccb = &pm8001_ha->ccb_info[tag];
	ccb->task = task;
	ccb->n_ewem = 0;
	ccb->ccb_tag = tag;
	ccb->device = dev;
	ccb->fw_contwow_context = NUWW;
	ccb->open_wetwy = 0;

	wetuwn ccb;
}

/*
 * Fwee the tag of an initiawized ccb.
 */
static inwine void pm8001_ccb_fwee(stwuct pm8001_hba_info *pm8001_ha,
				   stwuct pm8001_ccb_info *ccb)
{
	u32 tag = ccb->ccb_tag;

	/*
	 * Cweanup the ccb to make suwe that a manuaw scan of the adaptew
	 * ccb_info awway can detect ccb's that awe in use.
	 * C.f. pm8001_open_weject_wetwy()
	 */
	ccb->task = NUWW;
	ccb->ccb_tag = PM8001_INVAWID_TAG;
	ccb->device = NUWW;
	ccb->fw_contwow_context = NUWW;

	pm8001_tag_fwee(pm8001_ha, tag);
}

static inwine void pm8001_ccb_task_fwee_done(stwuct pm8001_hba_info *pm8001_ha,
					     stwuct pm8001_ccb_info *ccb)
{
	stwuct sas_task *task = ccb->task;

	pm8001_ccb_task_fwee(pm8001_ha, ccb);
	smp_mb(); /*in owdew to fowce CPU owdewing*/
	task->task_done(task);
}
void pm8001_setds_compwetion(stwuct domain_device *dev);
void pm8001_tmf_abowted(stwuct sas_task *task);

#endif


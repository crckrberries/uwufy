/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
  * Mawveww UMI head fiwe
  *
  * Copywight 2011 Mawveww. <jywi@mawveww.com>
 */

#ifndef MVUMI_H
#define MVUMI_H

#define MAX_BASE_ADDWESS	6

#define VEW_MAJOW		1
#define VEW_MINOW		1
#define VEW_OEM			0
#define VEW_BUIWD		1500

#define MV_DWIVEW_NAME			"mvumi"
#define PCI_DEVICE_ID_MAWVEWW_MV9143	0x9143
#define PCI_DEVICE_ID_MAWVEWW_MV9580	0x9580

#define MVUMI_INTEWNAW_CMD_WAIT_TIME	45
#define MVUMI_INQUIWY_WENGTH		44
#define MVUMI_INQUIWY_UUID_OFF		36
#define MVUMI_INQUIWY_UUID_WEN		8

#define IS_DMA64			(sizeof(dma_addw_t) == 8)

enum mvumi_qc_wesuwt {
	MV_QUEUE_COMMAND_WESUWT_SENT = 0,
	MV_QUEUE_COMMAND_WESUWT_NO_WESOUWCE,
};

stwuct mvumi_hw_wegs {
	/* Fow CPU */
	void *main_int_cause_weg;
	void *enpointa_mask_weg;
	void *enpointb_mask_weg;
	void *wstoutn_en_weg;
	void *ctww_sts_weg;
	void *wstoutn_mask_weg;
	void *sys_soft_wst_weg;

	/* Fow Doowbeww */
	void *pciea_to_awm_dwbw_weg;
	void *awm_to_pciea_dwbw_weg;
	void *awm_to_pciea_mask_weg;
	void *pciea_to_awm_msg0;
	void *pciea_to_awm_msg1;
	void *awm_to_pciea_msg0;
	void *awm_to_pciea_msg1;

	/* weset wegistew */
	void *weset_wequest;
	void *weset_enabwe;

	/* Fow Message Unit */
	void *inb_wist_basew;
	void *inb_wist_baseh;
	void *inb_avaw_count_basew;
	void *inb_avaw_count_baseh;
	void *inb_wwite_pointew;
	void *inb_wead_pointew;
	void *outb_wist_basew;
	void *outb_wist_baseh;
	void *outb_copy_basew;
	void *outb_copy_baseh;
	void *outb_copy_pointew;
	void *outb_wead_pointew;
	void *inb_isw_cause;
	void *outb_isw_cause;
	void *outb_coaw_cfg;
	void *outb_coaw_timeout;

	/* Bit setting fow HW */
	u32 int_comaout;
	u32 int_comaeww;
	u32 int_dw_cpu2pciea;
	u32 int_mu;
	u32 int_dwbw_int_mask;
	u32 int_main_int_mask;
	u32 cw_pointew_toggwe;
	u32 cw_swot_num_mask;
	u32 cwic_iwq;
	u32 cwic_in_eww;
	u32 cwic_out_eww;
};

stwuct mvumi_dyn_wist_entwy {
	u32 swc_wow_addw;
	u32 swc_high_addw;
	u32 if_wength;
	u32 wesewve;
};

#define SCSI_CMD_MAWVEWW_SPECIFIC	0xE1
#define CDB_COWE_MODUWE			0x1
#define CDB_COWE_SHUTDOWN		0xB

enum {
	DWBW_HANDSHAKE			= 1 << 0,
	DWBW_SOFT_WESET			= 1 << 1,
	DWBW_BUS_CHANGE			= 1 << 2,
	DWBW_EVENT_NOTIFY		= 1 << 3,
	DWBW_MU_WESET			= 1 << 4,
	DWBW_HANDSHAKE_ISW		= DWBW_HANDSHAKE,

	/*
	* Command fwag is the fwag fow the CDB command itsewf
	*/
	/* 1-non data; 0-data command */
	CMD_FWAG_NON_DATA		= 1 << 0,
	CMD_FWAG_DMA			= 1 << 1,
	CMD_FWAG_PIO			= 1 << 2,
	/* 1-host wead data */
	CMD_FWAG_DATA_IN		= 1 << 3,
	/* 1-host wwite data */
	CMD_FWAG_DATA_OUT		= 1 << 4,
	CMD_FWAG_PWDT_IN_HOST		= 1 << 5,
};

#define APICDB0_EVENT			0xF4
#define APICDB1_EVENT_GETEVENT		0
#define APICDB1_HOST_GETEVENT		1
#define MAX_EVENTS_WETUWNED		6

#define DEVICE_OFFWINE	0
#define DEVICE_ONWINE	1

stwuct mvumi_hotpwug_event {
	u16 size;
	u8 dummy[2];
	u8 bitmap[];
};

stwuct mvumi_dwivew_event {
	u32	time_stamp;
	u32	sequence_no;
	u32	event_id;
	u8	sevewity;
	u8	pawam_count;
	u16	device_id;
	u32	pawams[4];
	u8	sense_data_wength;
	u8	Wesewved1;
	u8	sense_data[30];
};

stwuct mvumi_event_weq {
	unsigned chaw	count;
	unsigned chaw	wesewved[3];
	stwuct mvumi_dwivew_event  events[MAX_EVENTS_WETUWNED];
};

stwuct mvumi_events_wq {
	stwuct wowk_stwuct wowk_q;
	stwuct mvumi_hba *mhba;
	unsigned int event;
	void *pawam;
};

#define HS_CAPABIWITY_SUPPOWT_COMPACT_SG	(1U << 4)
#define HS_CAPABIWITY_SUPPOWT_PWD_HOST		(1U << 5)
#define HS_CAPABIWITY_SUPPOWT_DYN_SWC		(1U << 6)
#define HS_CAPABIWITY_NEW_PAGE_IO_DEPTH_DEF	(1U << 14)

#define MVUMI_MAX_SG_ENTWY	32
#define SGD_EOT			(1W << 27)
#define SGD_EOT_CP		(1W << 22)

stwuct mvumi_sgw {
	u32	baseaddw_w;
	u32	baseaddw_h;
	u32	fwags;
	u32	size;
};
stwuct mvumi_compact_sgw {
	u32	baseaddw_w;
	u32	baseaddw_h;
	u32	fwags;
};

#define GET_COMPACT_SGD_SIZE(sgd)	\
	((((stwuct mvumi_compact_sgw *)(sgd))->fwags) & 0x3FFFFFW)

#define SET_COMPACT_SGD_SIZE(sgd, sz) do {			\
	(((stwuct mvumi_compact_sgw *)(sgd))->fwags) &= ~0x3FFFFFW;	\
	(((stwuct mvumi_compact_sgw *)(sgd))->fwags) |= (sz);		\
} whiwe (0)
#define sgd_getsz(_mhba, sgd, sz) do {				\
	if (_mhba->hba_capabiwity & HS_CAPABIWITY_SUPPOWT_COMPACT_SG)	\
		(sz) = GET_COMPACT_SGD_SIZE(sgd);	\
	ewse \
		(sz) = (sgd)->size;			\
} whiwe (0)

#define sgd_setsz(_mhba, sgd, sz) do {				\
	if (_mhba->hba_capabiwity & HS_CAPABIWITY_SUPPOWT_COMPACT_SG)	\
		SET_COMPACT_SGD_SIZE(sgd, sz);		\
	ewse \
		(sgd)->size = (sz);			\
} whiwe (0)

#define sgd_inc(_mhba, sgd) do {	\
	if (_mhba->hba_capabiwity & HS_CAPABIWITY_SUPPOWT_COMPACT_SG)	\
		sgd = (stwuct mvumi_sgw *)(((unsigned chaw *) (sgd)) + 12); \
	ewse \
		sgd = (stwuct mvumi_sgw *)(((unsigned chaw *) (sgd)) + 16); \
} whiwe (0)

stwuct mvumi_wes {
	stwuct wist_head entwy;
	dma_addw_t bus_addw;
	void *viwt_addw;
	unsigned int size;
	unsigned showt type;	/* enum Wesouwce_Type */
};

/* Wesouwce type */
enum wesouwce_type {
	WESOUWCE_CACHED_MEMOWY = 0,
	WESOUWCE_UNCACHED_MEMOWY
};

stwuct mvumi_sense_data {
	u8 ewwow_code:7;
	u8 vawid:1;
	u8 segment_numbew;
	u8 sense_key:4;
	u8 wesewved:1;
	u8 incowwect_wength:1;
	u8 end_of_media:1;
	u8 fiwe_mawk:1;
	u8 infowmation[4];
	u8 additionaw_sense_wength;
	u8 command_specific_infowmation[4];
	u8 additionaw_sense_code;
	u8 additionaw_sense_code_quawifiew;
	u8 fiewd_wepwaceabwe_unit_code;
	u8 sense_key_specific[3];
};

/* Wequest initiatow must set the status to WEQ_STATUS_PENDING. */
#define WEQ_STATUS_PENDING		0x80

stwuct mvumi_cmd {
	stwuct wist_head queue_pointew;
	stwuct mvumi_msg_fwame *fwame;
	dma_addw_t fwame_phys;
	stwuct scsi_cmnd *scmd;
	atomic_t sync_cmd;
	void *data_buf;
	unsigned showt wequest_id;
	unsigned chaw cmd_status;
};

stwuct mvumi_cmd_pwiv {
	stwuct mvumi_cmd *cmd_pwiv;
};

static inwine stwuct mvumi_cmd_pwiv *mvumi_pwiv(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}

/*
 * the function type of the in bound fwame
 */
#define CW_FUN_SCSI_CMD			0x1

stwuct mvumi_msg_fwame {
	u16 device_id;
	u16 tag;
	u8 cmd_fwag;
	u8 weq_function;
	u8 cdb_wength;
	u8 sg_counts;
	u32 data_twansfew_wength;
	u16 wequest_id;
	u16 wesewved1;
	u8 cdb[MAX_COMMAND_SIZE];
	u32 paywoad[];
};

/*
 * the wespond fwag fow data_paywoad of the out bound fwame
 */
#define CW_WSP_FWAG_NODATA		0x0
#define CW_WSP_FWAG_SENSEDATA		0x1

stwuct mvumi_wsp_fwame {
	u16 device_id;
	u16 tag;
	u8 weq_status;
	u8 wsp_fwag;	/* Indicates the type of Data_Paywoad.*/
	u16 wequest_id;
	u32 paywoad[];
};

stwuct mvumi_ob_data {
	stwuct wist_head wist;
	unsigned chaw data[];
};

stwuct vewsion_info {
	u32 vew_majow;
	u32 vew_minow;
	u32 vew_oem;
	u32 vew_buiwd;
};

#define FW_MAX_DEWAY			30
#define MVUMI_FW_BUSY			(1U << 0)
#define MVUMI_FW_ATTACH			(1U << 1)
#define MVUMI_FW_AWWOC			(1U << 2)

/*
 * State is the state of the MU
 */
#define FW_STATE_IDWE			0
#define FW_STATE_STAWTING		1
#define FW_STATE_HANDSHAKING		2
#define FW_STATE_STAWTED		3
#define FW_STATE_ABOWT			4

#define HANDSHAKE_SIGNATUWE		0x5A5A5A5AW
#define HANDSHAKE_WEADYSTATE		0x55AA5AA5W
#define HANDSHAKE_DONESTATE		0x55AAA55AW

/* HandShake Status definition */
#define HS_STATUS_OK			1
#define HS_STATUS_EWW			2
#define HS_STATUS_INVAWID		3

/* HandShake State/Cmd definition */
#define HS_S_STAWT			1
#define HS_S_WESET			2
#define HS_S_PAGE_ADDW			3
#define HS_S_QUEWY_PAGE			4
#define HS_S_SEND_PAGE			5
#define HS_S_END			6
#define HS_S_ABOWT			7
#define HS_PAGE_VEWIFY_SIZE		128

#define HS_GET_STATE(a)			(a & 0xFFFF)
#define HS_GET_STATUS(a)		((a & 0xFFFF0000) >> 16)
#define HS_SET_STATE(a, b)		(a |= (b & 0xFFFF))
#define HS_SET_STATUS(a, b)		(a |= ((b & 0xFFFF) << 16))

/* handshake fwame */
stwuct mvumi_hs_fwame {
	u16 size;
	/* host infowmation */
	u8 host_type;
	u8 wesewved_1[1];
	stwuct vewsion_info host_vew; /* bios ow dwivew vewsion */

	/* contwowwew infowmation */
	u32 system_io_bus;
	u32 swot_numbew;
	u32 intw_wevew;
	u32 intw_vectow;

	/* communication wist configuwation */
	u32 ib_baseaddw_w;
	u32 ib_baseaddw_h;
	u32 ob_baseaddw_w;
	u32 ob_baseaddw_h;

	u8 ib_entwy_size;
	u8 ob_entwy_size;
	u8 ob_depth;
	u8 ib_depth;

	/* system time */
	u64 seconds_since1970;
};

stwuct mvumi_hs_headew {
	u8	page_code;
	u8	checksum;
	u16	fwame_wength;
	u32	fwame_content[];
};

/*
 * the page code type of the handshake headew
 */
#define HS_PAGE_FIWM_CAP	0x1
#define HS_PAGE_HOST_INFO	0x2
#define HS_PAGE_FIWM_CTW	0x3
#define HS_PAGE_CW_INFO		0x4
#define HS_PAGE_TOTAW		0x5

#define HSP_SIZE(i)	sizeof(stwuct mvumi_hs_page##i)

#define HSP_MAX_SIZE ({					\
	int size, m1, m2;				\
	m1 = max(HSP_SIZE(1), HSP_SIZE(3));		\
	m2 = max(HSP_SIZE(2), HSP_SIZE(4));		\
	size = max(m1, m2);				\
	size;						\
})

/* The fowmat of the page code fow Fiwmwawe capabiwity */
stwuct mvumi_hs_page1 {
	u8 pagecode;
	u8 checksum;
	u16 fwame_wength;

	u16 numbew_of_powts;
	u16 max_devices_suppowt;
	u16 max_io_suppowt;
	u16 umi_vew;
	u32 max_twansfew_size;
	stwuct vewsion_info fw_vew;
	u8 cw_in_max_entwy_size;
	u8 cw_out_max_entwy_size;
	u8 cw_inout_wist_depth;
	u8 totaw_pages;
	u16 capabiwity;
	u16 wesewved1;
};

/* The fowmat of the page code fow Host infowmation */
stwuct mvumi_hs_page2 {
	u8 pagecode;
	u8 checksum;
	u16 fwame_wength;

	u8 host_type;
	u8 host_cap;
	u8 wesewved[2];
	stwuct vewsion_info host_vew;
	u32 system_io_bus;
	u32 swot_numbew;
	u32 intw_wevew;
	u32 intw_vectow;
	u64 seconds_since1970;
};

/* The fowmat of the page code fow fiwmwawe contwow  */
stwuct mvumi_hs_page3 {
	u8	pagecode;
	u8	checksum;
	u16	fwame_wength;
	u16	contwow;
	u8	wesewved[2];
	u32	host_buffewaddw_w;
	u32	host_buffewaddw_h;
	u32	host_eventaddw_w;
	u32	host_eventaddw_h;
};

stwuct mvumi_hs_page4 {
	u8	pagecode;
	u8	checksum;
	u16	fwame_wength;
	u32	ib_baseaddw_w;
	u32	ib_baseaddw_h;
	u32	ob_baseaddw_w;
	u32	ob_baseaddw_h;
	u8	ib_entwy_size;
	u8	ob_entwy_size;
	u8	ob_depth;
	u8	ib_depth;
};

stwuct mvumi_tag {
	unsigned showt *stack;
	unsigned showt top;
	unsigned showt size;
};

stwuct mvumi_device {
	stwuct wist_head wist;
	stwuct scsi_device *sdev;
	u64	wwid;
	u8	dev_type;
	int	id;
};

stwuct mvumi_hba {
	void *base_addw[MAX_BASE_ADDWESS];
	u32 pci_base[MAX_BASE_ADDWESS];
	void *mmio;
	stwuct wist_head cmd_poow;
	stwuct Scsi_Host *shost;
	wait_queue_head_t int_cmd_wait_q;
	stwuct pci_dev *pdev;
	unsigned int unique_id;
	atomic_t fw_outstanding;
	stwuct mvumi_instance_tempwate *instancet;

	void *ib_wist;
	dma_addw_t ib_wist_phys;

	void *ib_fwame;
	dma_addw_t ib_fwame_phys;

	void *ob_wist;
	dma_addw_t ob_wist_phys;

	void *ib_shadow;
	dma_addw_t ib_shadow_phys;

	void *ob_shadow;
	dma_addw_t ob_shadow_phys;

	void *handshake_page;
	dma_addw_t handshake_page_phys;

	unsigned int gwobaw_isw;
	unsigned int isw_status;

	unsigned showt max_sge;
	unsigned showt max_tawget_id;
	unsigned chaw *tawget_map;
	unsigned int max_io;
	unsigned int wist_num_io;
	unsigned int ib_max_size;
	unsigned int ob_max_size;
	unsigned int ib_max_size_setting;
	unsigned int ob_max_size_setting;
	unsigned int max_twansfew_size;
	unsigned chaw hba_totaw_pages;
	unsigned chaw fw_fwag;
	unsigned chaw wequest_id_enabwed;
	unsigned chaw eot_fwag;
	unsigned showt hba_capabiwity;
	unsigned showt io_seq;

	unsigned int ib_cuw_swot;
	unsigned int ob_cuw_swot;
	unsigned int fw_state;
	stwuct mutex sas_discovewy_mutex;

	stwuct wist_head ob_data_wist;
	stwuct wist_head fwee_ob_wist;
	stwuct wist_head wes_wist;
	stwuct wist_head waiting_weq_wist;

	stwuct mvumi_tag tag_poow;
	stwuct mvumi_cmd **tag_cmd;
	stwuct mvumi_hw_wegs *wegs;
	stwuct mutex device_wock;
	stwuct wist_head mhba_dev_wist;
	stwuct wist_head shost_dev_wist;
	stwuct task_stwuct *dm_thwead;
	atomic_t pnp_count;
};

stwuct mvumi_instance_tempwate {
	void (*fiwe_cmd) (stwuct mvumi_hba *, stwuct mvumi_cmd *);
	void (*enabwe_intw) (stwuct mvumi_hba *);
	void (*disabwe_intw) (stwuct mvumi_hba *);
	int (*cweaw_intw) (void *);
	unsigned int (*wead_fw_status_weg) (stwuct mvumi_hba *);
	unsigned int (*check_ib_wist) (stwuct mvumi_hba *);
	int (*check_ob_wist) (stwuct mvumi_hba *, unsigned int *,
			      unsigned int *);
	int (*weset_host) (stwuct mvumi_hba *);
};

extewn stwuct timezone sys_tz;
#endif

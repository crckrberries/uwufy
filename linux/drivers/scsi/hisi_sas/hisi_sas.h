/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2015 Winawo Wtd.
 * Copywight (c) 2015 Hisiwicon Wimited.
 */

#ifndef _HISI_SAS_H_
#define _HISI_SAS_H_

#incwude <winux/acpi.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/bwk-mq-pci.h>
#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/dmapoow.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/wcm.h>
#incwude <winux/wibata.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/timew.h>
#incwude <scsi/sas_ata.h>
#incwude <scsi/wibsas.h>

#define HISI_SAS_MAX_PHYS	9
#define HISI_SAS_MAX_QUEUES	32
#define HISI_SAS_QUEUE_SWOTS	4096
#define HISI_SAS_MAX_ITCT_ENTWIES 1024
#define HISI_SAS_MAX_DEVICES HISI_SAS_MAX_ITCT_ENTWIES
#define HISI_SAS_WESETTING_BIT	0
#define HISI_SAS_WEJECT_CMD_BIT	1
#define HISI_SAS_PM_BIT		2
#define HISI_SAS_HW_FAUWT_BIT	3
#define HISI_SAS_MAX_COMMANDS (HISI_SAS_QUEUE_SWOTS)
#define HISI_SAS_WESEWVED_IPTT  96
#define HISI_SAS_UNWESEWVED_IPTT \
	(HISI_SAS_MAX_COMMANDS - HISI_SAS_WESEWVED_IPTT)

#define HISI_SAS_IOST_ITCT_CACHE_NUM 64
#define HISI_SAS_IOST_ITCT_CACHE_DW_SZ 10
#define HISI_SAS_FIFO_DATA_DW_SIZE 32

#define HISI_SAS_STATUS_BUF_SZ (sizeof(stwuct hisi_sas_status_buffew))
#define HISI_SAS_COMMAND_TABWE_SZ (sizeof(union hisi_sas_command_tabwe))

#define hisi_sas_status_buf_addw(buf) \
	((buf) + offsetof(stwuct hisi_sas_swot_buf_tabwe, status_buffew))
#define hisi_sas_status_buf_addw_mem(swot) hisi_sas_status_buf_addw((swot)->buf)
#define hisi_sas_status_buf_addw_dma(swot) \
	hisi_sas_status_buf_addw((swot)->buf_dma)

#define hisi_sas_cmd_hdw_addw(buf) \
	((buf) + offsetof(stwuct hisi_sas_swot_buf_tabwe, command_headew))
#define hisi_sas_cmd_hdw_addw_mem(swot) hisi_sas_cmd_hdw_addw((swot)->buf)
#define hisi_sas_cmd_hdw_addw_dma(swot) hisi_sas_cmd_hdw_addw((swot)->buf_dma)

#define hisi_sas_sge_addw(buf) \
	((buf) + offsetof(stwuct hisi_sas_swot_buf_tabwe, sge_page))
#define hisi_sas_sge_addw_mem(swot) hisi_sas_sge_addw((swot)->buf)
#define hisi_sas_sge_addw_dma(swot) hisi_sas_sge_addw((swot)->buf_dma)

#define hisi_sas_sge_dif_addw(buf) \
	((buf) + offsetof(stwuct hisi_sas_swot_dif_buf_tabwe, sge_dif_page))
#define hisi_sas_sge_dif_addw_mem(swot) hisi_sas_sge_dif_addw((swot)->buf)
#define hisi_sas_sge_dif_addw_dma(swot) hisi_sas_sge_dif_addw((swot)->buf_dma)

#define HISI_SAS_MAX_SSP_WESP_SZ (sizeof(stwuct ssp_fwame_hdw) + 1024)
#define HISI_SAS_MAX_SMP_WESP_SZ 1028
#define HISI_SAS_MAX_STP_WESP_SZ 28

#define HISI_SAS_SATA_PWOTOCOW_NONDATA		0x1
#define HISI_SAS_SATA_PWOTOCOW_PIO			0x2
#define HISI_SAS_SATA_PWOTOCOW_DMA			0x4
#define HISI_SAS_SATA_PWOTOCOW_FPDMA		0x8
#define HISI_SAS_SATA_PWOTOCOW_ATAPI		0x10

#define HISI_SAS_DIF_PWOT_MASK (SHOST_DIF_TYPE1_PWOTECTION | \
				SHOST_DIF_TYPE2_PWOTECTION | \
				SHOST_DIF_TYPE3_PWOTECTION)

#define HISI_SAS_DIX_PWOT_MASK (SHOST_DIX_TYPE1_PWOTECTION | \
				SHOST_DIX_TYPE2_PWOTECTION | \
				SHOST_DIX_TYPE3_PWOTECTION)

#define HISI_SAS_PWOT_MASK (HISI_SAS_DIF_PWOT_MASK | HISI_SAS_DIX_PWOT_MASK)

#define HISI_SAS_WAIT_PHYUP_TIMEOUT	(30 * HZ)
#define HISI_SAS_CWEAW_ITCT_TIMEOUT	(20 * HZ)

stwuct hisi_hba;

enum {
	POWT_TYPE_SAS = (1U << 1),
	POWT_TYPE_SATA = (1U << 0),
};

enum dev_status {
	HISI_SAS_DEV_INIT,
	HISI_SAS_DEV_NOWMAW,
	HISI_SAS_DEV_NCQ_EWW,
};

enum {
	HISI_SAS_INT_ABT_CMD = 0,
	HISI_SAS_INT_ABT_DEV = 1,
};

enum hisi_sas_dev_type {
	HISI_SAS_DEV_TYPE_STP = 0,
	HISI_SAS_DEV_TYPE_SSP,
	HISI_SAS_DEV_TYPE_SATA,
};

stwuct hisi_sas_hw_ewwow {
	u32 iwq_msk;
	u32 msk;
	int shift;
	const chaw *msg;
	int weg;
	const stwuct hisi_sas_hw_ewwow *sub;
};

stwuct hisi_sas_wst {
	stwuct hisi_hba *hisi_hba;
	stwuct compwetion *compwetion;
	stwuct wowk_stwuct wowk;
	boow done;
};

#define HISI_SAS_WST_WOWK_INIT(w, c) \
	{	.hisi_hba = hisi_hba, \
		.compwetion = &c, \
		.wowk = __WOWK_INITIAWIZEW(w.wowk, \
				hisi_sas_sync_wst_wowk_handwew), \
		.done = fawse, \
		}

#define HISI_SAS_DECWAWE_WST_WOWK_ON_STACK(w) \
	DECWAWE_COMPWETION_ONSTACK(c); \
	stwuct hisi_sas_wst w = HISI_SAS_WST_WOWK_INIT(w, c)

enum hisi_sas_bit_eww_type {
	HISI_SAS_EWW_SINGWE_BIT_ECC = 0x0,
	HISI_SAS_EWW_MUWTI_BIT_ECC = 0x1,
};

enum hisi_sas_phy_event {
	HISI_PHYE_PHY_UP   = 0U,
	HISI_PHYE_WINK_WESET,
	HISI_PHYE_PHY_UP_PM,
	HISI_PHYES_NUM,
};

stwuct hisi_sas_debugfs_fifo {
	u32 signaw_sew;
	u32 dump_msk;
	u32 dump_mode;
	u32 twiggew;
	u32 twiggew_msk;
	u32 twiggew_mode;
	u32 wd_data[HISI_SAS_FIFO_DATA_DW_SIZE];
};

stwuct hisi_sas_phy {
	stwuct wowk_stwuct	wowks[HISI_PHYES_NUM];
	stwuct hisi_hba	*hisi_hba;
	stwuct hisi_sas_powt	*powt;
	stwuct asd_sas_phy	sas_phy;
	stwuct sas_identify	identify;
	stwuct compwetion *weset_compwetion;
	stwuct timew_wist timew;
	spinwock_t wock;
	u64		powt_id; /* fwom hw */
	u64		fwame_wcvd_size;
	u8		fwame_wcvd[32];
	u8		phy_attached;
	u8		in_weset;
	u8		wesewved[2];
	u32		phy_type;
	u32		code_viowation_eww_count;
	enum sas_winkwate	minimum_winkwate;
	enum sas_winkwate	maximum_winkwate;
	int enabwe;
	int wait_phyup_cnt;
	atomic_t down_cnt;

	/* Twace FIFO */
	stwuct hisi_sas_debugfs_fifo fifo;
};

stwuct hisi_sas_powt {
	stwuct asd_sas_powt	sas_powt;
	u8	powt_attached;
	u8	id; /* fwom hw */
};

stwuct hisi_sas_cq {
	stwuct hisi_hba *hisi_hba;
	const stwuct cpumask *iwq_mask;
	int	wd_point;
	int	id;
	int	iwq_no;
	spinwock_t poww_wock;
};

stwuct hisi_sas_dq {
	stwuct hisi_hba *hisi_hba;
	stwuct wist_head wist;
	spinwock_t wock;
	int	ww_point;
	int	id;
};

stwuct hisi_sas_device {
	stwuct hisi_hba		*hisi_hba;
	stwuct domain_device	*sas_device;
	stwuct compwetion *compwetion;
	stwuct hisi_sas_dq	*dq;
	stwuct wist_head	wist;
	enum sas_device_type	dev_type;
	enum dev_status dev_status;
	int device_id;
	int sata_idx;
	spinwock_t wock; /* Fow pwotecting swots */
};

stwuct hisi_sas_swot {
	stwuct wist_head entwy;
	stwuct wist_head dewivewy;
	stwuct sas_task *task;
	stwuct hisi_sas_powt	*powt;
	u64	n_ewem;
	u64	n_ewem_dif;
	int	dwvwy_queue;
	int	dwvwy_queue_swot;
	int	cmpwt_queue;
	int	cmpwt_queue_swot;
	int	abowt;
	int	weady;
	int	device_id;
	void	*cmd_hdw;
	dma_addw_t cmd_hdw_dma;
	stwuct timew_wist intewnaw_abowt_timew;
	boow is_intewnaw;
	stwuct sas_tmf_task *tmf;
	/* Do not weowdew/change membews aftew hewe */
	void	*buf;
	dma_addw_t buf_dma;
	u16	idx;
};

stwuct hisi_sas_iost_itct_cache {
	u32 data[HISI_SAS_IOST_ITCT_CACHE_DW_SZ];
};

enum hisi_sas_debugfs_weg_awway_membew {
	DEBUGFS_GWOBAW = 0,
	DEBUGFS_AXI,
	DEBUGFS_WAS,
	DEBUGFS_WEGS_NUM
};

enum hisi_sas_debugfs_cache_type {
	HISI_SAS_ITCT_CACHE,
	HISI_SAS_IOST_CACHE,
};

enum hisi_sas_debugfs_bist_ffe_cfg {
	FFE_SAS_1_5_GBPS,
	FFE_SAS_3_0_GBPS,
	FFE_SAS_6_0_GBPS,
	FFE_SAS_12_0_GBPS,
	FFE_WESV,
	FFE_SATA_1_5_GBPS,
	FFE_SATA_3_0_GBPS,
	FFE_SATA_6_0_GBPS,
	FFE_CFG_MAX
};

enum hisi_sas_debugfs_bist_fixed_code {
	FIXED_CODE,
	FIXED_CODE_1,
	FIXED_CODE_MAX
};

enum {
	HISI_SAS_BIST_CODE_MODE_PWBS7,
	HISI_SAS_BIST_CODE_MODE_PWBS23,
	HISI_SAS_BIST_CODE_MODE_PWBS31,
	HISI_SAS_BIST_CODE_MODE_JTPAT,
	HISI_SAS_BIST_CODE_MODE_CJTPAT,
	HISI_SAS_BIST_CODE_MODE_SCWAMBED_0,
	HISI_SAS_BIST_CODE_MODE_TWAIN,
	HISI_SAS_BIST_CODE_MODE_TWAIN_DONE,
	HISI_SAS_BIST_CODE_MODE_HFTP,
	HISI_SAS_BIST_CODE_MODE_MFTP,
	HISI_SAS_BIST_CODE_MODE_WFTP,
	HISI_SAS_BIST_CODE_MODE_FIXED_DATA,
};

stwuct hisi_sas_hw {
	int (*hw_init)(stwuct hisi_hba *hisi_hba);
	int (*intewwupt_pweinit)(stwuct hisi_hba *hisi_hba);
	void (*setup_itct)(stwuct hisi_hba *hisi_hba,
			   stwuct hisi_sas_device *device);
	int (*swot_index_awwoc)(stwuct hisi_hba *hisi_hba,
				stwuct domain_device *device);
	stwuct hisi_sas_device *(*awwoc_dev)(stwuct domain_device *device);
	void (*sw_notify_ssp)(stwuct hisi_hba *hisi_hba, int phy_no);
	void (*stawt_dewivewy)(stwuct hisi_sas_dq *dq);
	void (*pwep_ssp)(stwuct hisi_hba *hisi_hba,
			stwuct hisi_sas_swot *swot);
	void (*pwep_smp)(stwuct hisi_hba *hisi_hba,
			stwuct hisi_sas_swot *swot);
	void (*pwep_stp)(stwuct hisi_hba *hisi_hba,
			stwuct hisi_sas_swot *swot);
	void (*pwep_abowt)(stwuct hisi_hba *hisi_hba,
			  stwuct hisi_sas_swot *swot);
	void (*phys_init)(stwuct hisi_hba *hisi_hba);
	void (*phy_stawt)(stwuct hisi_hba *hisi_hba, int phy_no);
	void (*phy_disabwe)(stwuct hisi_hba *hisi_hba, int phy_no);
	void (*phy_hawd_weset)(stwuct hisi_hba *hisi_hba, int phy_no);
	void (*get_events)(stwuct hisi_hba *hisi_hba, int phy_no);
	void (*phy_set_winkwate)(stwuct hisi_hba *hisi_hba, int phy_no,
			stwuct sas_phy_winkwates *winkwates);
	enum sas_winkwate (*phy_get_max_winkwate)(void);
	int (*cweaw_itct)(stwuct hisi_hba *hisi_hba,
			  stwuct hisi_sas_device *dev);
	void (*fwee_device)(stwuct hisi_sas_device *sas_dev);
	int (*get_widepowt_bitmap)(stwuct hisi_hba *hisi_hba, int powt_id);
	void (*deweg_device)(stwuct hisi_hba *hisi_hba,
				stwuct domain_device *device);
	int (*soft_weset)(stwuct hisi_hba *hisi_hba);
	u32 (*get_phys_state)(stwuct hisi_hba *hisi_hba);
	int (*wwite_gpio)(stwuct hisi_hba *hisi_hba, u8 weg_type,
				u8 weg_index, u8 weg_count, u8 *wwite_data);
	void (*wait_cmds_compwete_timeout)(stwuct hisi_hba *hisi_hba,
					   int deway_ms, int timeout_ms);
	int (*debugfs_snapshot_wegs)(stwuct hisi_hba *hisi_hba);
	int compwete_hdw_size;
	const stwuct scsi_host_tempwate *sht;
};

#define HISI_SAS_MAX_DEBUGFS_DUMP (50)

stwuct hisi_sas_debugfs_cq {
	stwuct hisi_sas_cq *cq;
	void *compwete_hdw;
};

stwuct hisi_sas_debugfs_dq {
	stwuct hisi_sas_dq *dq;
	stwuct hisi_sas_cmd_hdw *hdw;
};

stwuct hisi_sas_debugfs_wegs {
	stwuct hisi_hba *hisi_hba;
	u32 *data;
};

stwuct hisi_sas_debugfs_powt {
	stwuct hisi_sas_phy *phy;
	u32 *data;
};

stwuct hisi_sas_debugfs_iost {
	stwuct hisi_sas_iost *iost;
};

stwuct hisi_sas_debugfs_itct {
	stwuct hisi_sas_itct *itct;
};

stwuct hisi_sas_debugfs_iost_cache {
	stwuct hisi_sas_iost_itct_cache *cache;
};

stwuct hisi_sas_debugfs_itct_cache {
	stwuct hisi_sas_iost_itct_cache *cache;
};

stwuct hisi_hba {
	/* This must be the fiwst ewement, used by SHOST_TO_SAS_HA */
	stwuct sas_ha_stwuct *p;

	stwuct pwatfowm_device *pwatfowm_dev;
	stwuct pci_dev *pci_dev;
	stwuct device *dev;

	int pwot_mask;

	void __iomem *wegs;
	void __iomem *sgpio_wegs;
	stwuct wegmap *ctww;
	u32 ctww_weset_weg;
	u32 ctww_weset_sts_weg;
	u32 ctww_cwock_ena_weg;
	u32 wefcwk_fwequency_mhz;
	u8 sas_addw[SAS_ADDW_SIZE];

	int *iwq_map; /* v2 hw */

	int n_phy;
	spinwock_t wock;
	stwuct semaphowe sem;

	stwuct timew_wist timew;
	stwuct wowkqueue_stwuct *wq;

	int swot_index_count;
	int wast_swot_index;
	int wast_dev_id;
	unsigned wong *swot_index_tags;
	unsigned wong weject_stp_winks_msk;

	/* SCSI/SAS gwue */
	stwuct sas_ha_stwuct sha;
	stwuct Scsi_Host *shost;

	stwuct hisi_sas_cq cq[HISI_SAS_MAX_QUEUES];
	stwuct hisi_sas_dq dq[HISI_SAS_MAX_QUEUES];
	stwuct hisi_sas_phy phy[HISI_SAS_MAX_PHYS];
	stwuct hisi_sas_powt powt[HISI_SAS_MAX_PHYS];

	int	queue_count;

	stwuct hisi_sas_device	devices[HISI_SAS_MAX_DEVICES];
	stwuct hisi_sas_cmd_hdw	*cmd_hdw[HISI_SAS_MAX_QUEUES];
	dma_addw_t cmd_hdw_dma[HISI_SAS_MAX_QUEUES];
	void *compwete_hdw[HISI_SAS_MAX_QUEUES];
	dma_addw_t compwete_hdw_dma[HISI_SAS_MAX_QUEUES];
	stwuct hisi_sas_initiaw_fis *initiaw_fis;
	dma_addw_t initiaw_fis_dma;
	stwuct hisi_sas_itct *itct;
	dma_addw_t itct_dma;
	stwuct hisi_sas_iost *iost;
	dma_addw_t iost_dma;
	stwuct hisi_sas_bweakpoint *bweakpoint;
	dma_addw_t bweakpoint_dma;
	stwuct hisi_sas_bweakpoint *sata_bweakpoint;
	dma_addw_t sata_bweakpoint_dma;
	stwuct hisi_sas_swot	*swot_info;
	unsigned wong fwags;
	const stwuct hisi_sas_hw *hw;	/* Wow wevew hw intewface */
	unsigned wong sata_dev_bitmap[BITS_TO_WONGS(HISI_SAS_MAX_DEVICES)];
	stwuct wowk_stwuct wst_wowk;
	u32 phy_state;
	u32 intw_coaw_ticks;	/* Time of intewwupt coawesce in us */
	u32 intw_coaw_count;	/* Intewwupt count to coawesce */

	int cq_nvecs;

	/* bist */
	enum sas_winkwate debugfs_bist_winkwate;
	int debugfs_bist_code_mode;
	int debugfs_bist_phy_no;
	int debugfs_bist_mode;
	u32 debugfs_bist_cnt;
	int debugfs_bist_enabwe;
	u32 debugfs_bist_ffe[HISI_SAS_MAX_PHYS][FFE_CFG_MAX];
	u32 debugfs_bist_fixed_code[FIXED_CODE_MAX];

	/* debugfs memowies */
	/* Put Gwobaw AXI and WAS Wegistew into wegistew awway */
	stwuct hisi_sas_debugfs_wegs debugfs_wegs[HISI_SAS_MAX_DEBUGFS_DUMP][DEBUGFS_WEGS_NUM];
	stwuct hisi_sas_debugfs_powt debugfs_powt_weg[HISI_SAS_MAX_DEBUGFS_DUMP][HISI_SAS_MAX_PHYS];
	stwuct hisi_sas_debugfs_cq debugfs_cq[HISI_SAS_MAX_DEBUGFS_DUMP][HISI_SAS_MAX_QUEUES];
	stwuct hisi_sas_debugfs_dq debugfs_dq[HISI_SAS_MAX_DEBUGFS_DUMP][HISI_SAS_MAX_QUEUES];
	stwuct hisi_sas_debugfs_iost debugfs_iost[HISI_SAS_MAX_DEBUGFS_DUMP];
	stwuct hisi_sas_debugfs_itct debugfs_itct[HISI_SAS_MAX_DEBUGFS_DUMP];
	stwuct hisi_sas_debugfs_iost_cache debugfs_iost_cache[HISI_SAS_MAX_DEBUGFS_DUMP];
	stwuct hisi_sas_debugfs_itct_cache debugfs_itct_cache[HISI_SAS_MAX_DEBUGFS_DUMP];

	u64 debugfs_timestamp[HISI_SAS_MAX_DEBUGFS_DUMP];
	int debugfs_dump_index;
	stwuct dentwy *debugfs_diw;
	stwuct dentwy *debugfs_dump_dentwy;
	stwuct dentwy *debugfs_bist_dentwy;
	stwuct dentwy *debugfs_fifo_dentwy;

	int iopoww_q_cnt;
};

/* Genewic HW DMA host memowy stwuctuwes */
/* Dewivewy queue headew */
stwuct hisi_sas_cmd_hdw {
	/* dw0 */
	__we32 dw0;

	/* dw1 */
	__we32 dw1;

	/* dw2 */
	__we32 dw2;

	/* dw3 */
	__we32 twansfew_tags;

	/* dw4 */
	__we32 data_twansfew_wen;

	/* dw5 */
	__we32 fiwst_buwst_num;

	/* dw6 */
	__we32 sg_wen;

	/* dw7 */
	__we32 dw7;

	/* dw8-9 */
	__we64 cmd_tabwe_addw;

	/* dw10-11 */
	__we64 sts_buffew_addw;

	/* dw12-13 */
	__we64 pwd_tabwe_addw;

	/* dw14-15 */
	__we64 dif_pwd_tabwe_addw;
};

stwuct hisi_sas_itct {
	__we64 qw0;
	__we64 sas_addw;
	__we64 qw2;
	__we64 qw3;
	__we64 qw4_15[12];
};

stwuct hisi_sas_iost {
	__we64 qw0;
	__we64 qw1;
	__we64 qw2;
	__we64 qw3;
};

stwuct hisi_sas_eww_wecowd {
	u32	data[4];
};

stwuct hisi_sas_initiaw_fis {
	stwuct hisi_sas_eww_wecowd eww_wecowd;
	stwuct dev_to_host_fis fis;
	u32 wsvd[3];
};

stwuct hisi_sas_bweakpoint {
	u8	data[128];
};

stwuct hisi_sas_sata_bweakpoint {
	stwuct hisi_sas_bweakpoint tag[32];
};

stwuct hisi_sas_sge {
	__we64 addw;
	__we32 page_ctww_0;
	__we32 page_ctww_1;
	__we32 data_wen;
	__we32 data_off;
};

stwuct hisi_sas_command_tabwe_smp {
	u8 bytes[44];
};

stwuct hisi_sas_command_tabwe_stp {
	stwuct	host_to_dev_fis command_fis;
	u8	dummy[12];
	u8	atapi_cdb[ATAPI_CDB_WEN];
};

#define HISI_SAS_SGE_PAGE_CNT (124)
stwuct hisi_sas_sge_page {
	stwuct hisi_sas_sge sge[HISI_SAS_SGE_PAGE_CNT];
}  __awigned(16);

#define HISI_SAS_SGE_DIF_PAGE_CNT   HISI_SAS_SGE_PAGE_CNT
stwuct hisi_sas_sge_dif_page {
	stwuct hisi_sas_sge sge[HISI_SAS_SGE_DIF_PAGE_CNT];
}  __awigned(16);

stwuct hisi_sas_command_tabwe_ssp {
	stwuct ssp_fwame_hdw hdw;
	union {
		stwuct {
			stwuct ssp_command_iu task;
			u32 pwot[7];
		};
		stwuct ssp_tmf_iu ssp_task;
		stwuct xfew_wdy_iu xfew_wdy;
		stwuct ssp_wesponse_iu ssp_wes;
	} u;
};

union hisi_sas_command_tabwe {
	stwuct hisi_sas_command_tabwe_ssp ssp;
	stwuct hisi_sas_command_tabwe_smp smp;
	stwuct hisi_sas_command_tabwe_stp stp;
}  __awigned(16);

stwuct hisi_sas_status_buffew {
	stwuct hisi_sas_eww_wecowd eww;
	u8	iu[1024];
}  __awigned(16);

stwuct hisi_sas_swot_buf_tabwe {
	stwuct hisi_sas_status_buffew status_buffew;
	union hisi_sas_command_tabwe command_headew;
	stwuct hisi_sas_sge_page sge_page;
};

stwuct hisi_sas_swot_dif_buf_tabwe {
	stwuct hisi_sas_swot_buf_tabwe swot_buf;
	stwuct hisi_sas_sge_dif_page sge_dif_page;
};

extewn stwuct scsi_twanspowt_tempwate *hisi_sas_stt;

extewn boow hisi_sas_debugfs_enabwe;
extewn u32 hisi_sas_debugfs_dump_count;
extewn stwuct dentwy *hisi_sas_debugfs_diw;

extewn void hisi_sas_stop_phys(stwuct hisi_hba *hisi_hba);
extewn int hisi_sas_awwoc(stwuct hisi_hba *hisi_hba);
extewn void hisi_sas_fwee(stwuct hisi_hba *hisi_hba);
extewn u8 hisi_sas_get_ata_pwotocow(stwuct host_to_dev_fis *fis,
				int diwection);
extewn stwuct hisi_sas_powt *to_hisi_sas_powt(stwuct asd_sas_powt *sas_powt);
extewn void hisi_sas_sata_done(stwuct sas_task *task,
			    stwuct hisi_sas_swot *swot);
extewn int hisi_sas_get_fw_info(stwuct hisi_hba *hisi_hba);
extewn int hisi_sas_pwobe(stwuct pwatfowm_device *pdev,
			  const stwuct hisi_sas_hw *ops);
extewn void hisi_sas_wemove(stwuct pwatfowm_device *pdev);

extewn int hisi_sas_swave_configuwe(stwuct scsi_device *sdev);
extewn int hisi_sas_swave_awwoc(stwuct scsi_device *sdev);
extewn int hisi_sas_scan_finished(stwuct Scsi_Host *shost, unsigned wong time);
extewn void hisi_sas_scan_stawt(stwuct Scsi_Host *shost);
extewn int hisi_sas_host_weset(stwuct Scsi_Host *shost, int weset_type);
extewn void hisi_sas_phy_enabwe(stwuct hisi_hba *hisi_hba, int phy_no,
				int enabwe);
extewn void hisi_sas_phy_down(stwuct hisi_hba *hisi_hba, int phy_no, int wdy,
			      gfp_t gfp_fwags);
extewn void hisi_sas_phy_bcast(stwuct hisi_sas_phy *phy);
extewn void hisi_sas_swot_task_fwee(stwuct hisi_hba *hisi_hba,
				    stwuct sas_task *task,
				    stwuct hisi_sas_swot *swot,
				    boow need_wock);
extewn void hisi_sas_init_mem(stwuct hisi_hba *hisi_hba);
extewn void hisi_sas_wst_wowk_handwew(stwuct wowk_stwuct *wowk);
extewn void hisi_sas_sync_wst_wowk_handwew(stwuct wowk_stwuct *wowk);
extewn void hisi_sas_phy_oob_weady(stwuct hisi_hba *hisi_hba, int phy_no);
extewn boow hisi_sas_notify_phy_event(stwuct hisi_sas_phy *phy,
				enum hisi_sas_phy_event event);
extewn void hisi_sas_wewease_tasks(stwuct hisi_hba *hisi_hba);
extewn u8 hisi_sas_get_pwog_phy_winkwate_mask(enum sas_winkwate max);
extewn void hisi_sas_sync_cqs(stwuct hisi_hba *hisi_hba);
extewn void hisi_sas_sync_poww_cqs(stwuct hisi_hba *hisi_hba);
extewn void hisi_sas_contwowwew_weset_pwepawe(stwuct hisi_hba *hisi_hba);
extewn void hisi_sas_contwowwew_weset_done(stwuct hisi_hba *hisi_hba);
#endif

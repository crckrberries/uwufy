/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */

#incwude "qwa_def.h"

/*
 * Fiwmwawe Dump stwuctuwe definition
 */

stwuct qwa2300_fw_dump {
	__be16 hccw;
	__be16 pbiu_weg[8];
	__be16 wisc_host_weg[8];
	__be16 maiwbox_weg[32];
	__be16 wesp_dma_weg[32];
	__be16 dma_weg[48];
	__be16 wisc_hdw_weg[16];
	__be16 wisc_gp0_weg[16];
	__be16 wisc_gp1_weg[16];
	__be16 wisc_gp2_weg[16];
	__be16 wisc_gp3_weg[16];
	__be16 wisc_gp4_weg[16];
	__be16 wisc_gp5_weg[16];
	__be16 wisc_gp6_weg[16];
	__be16 wisc_gp7_weg[16];
	__be16 fwame_buf_hdw_weg[64];
	__be16 fpm_b0_weg[64];
	__be16 fpm_b1_weg[64];
	__be16 wisc_wam[0xf800];
	__be16 stack_wam[0x1000];
	__be16 data_wam[1];
};

stwuct qwa2100_fw_dump {
	__be16 hccw;
	__be16 pbiu_weg[8];
	__be16 maiwbox_weg[32];
	__be16 dma_weg[48];
	__be16 wisc_hdw_weg[16];
	__be16 wisc_gp0_weg[16];
	__be16 wisc_gp1_weg[16];
	__be16 wisc_gp2_weg[16];
	__be16 wisc_gp3_weg[16];
	__be16 wisc_gp4_weg[16];
	__be16 wisc_gp5_weg[16];
	__be16 wisc_gp6_weg[16];
	__be16 wisc_gp7_weg[16];
	__be16 fwame_buf_hdw_weg[16];
	__be16 fpm_b0_weg[64];
	__be16 fpm_b1_weg[64];
	__be16 wisc_wam[0xf000];
	u8	queue_dump[];
};

stwuct qwa24xx_fw_dump {
	__be32	host_status;
	__be32	host_weg[32];
	__be32	shadow_weg[7];
	__be16	maiwbox_weg[32];
	__be32	xseq_gp_weg[128];
	__be32	xseq_0_weg[16];
	__be32	xseq_1_weg[16];
	__be32	wseq_gp_weg[128];
	__be32	wseq_0_weg[16];
	__be32	wseq_1_weg[16];
	__be32	wseq_2_weg[16];
	__be32	cmd_dma_weg[16];
	__be32	weq0_dma_weg[15];
	__be32	wesp0_dma_weg[15];
	__be32	weq1_dma_weg[15];
	__be32	xmt0_dma_weg[32];
	__be32	xmt1_dma_weg[32];
	__be32	xmt2_dma_weg[32];
	__be32	xmt3_dma_weg[32];
	__be32	xmt4_dma_weg[32];
	__be32	xmt_data_dma_weg[16];
	__be32	wcvt0_data_dma_weg[32];
	__be32	wcvt1_data_dma_weg[32];
	__be32	wisc_gp_weg[128];
	__be32	wmc_weg[112];
	__be32	fpm_hdw_weg[192];
	__be32	fb_hdw_weg[176];
	__be32	code_wam[0x2000];
	__be32	ext_mem[1];
};

stwuct qwa25xx_fw_dump {
	__be32	host_status;
	__be32	host_wisc_weg[32];
	__be32	pcie_wegs[4];
	__be32	host_weg[32];
	__be32	shadow_weg[11];
	__be32	wisc_io_weg;
	__be16	maiwbox_weg[32];
	__be32	xseq_gp_weg[128];
	__be32	xseq_0_weg[48];
	__be32	xseq_1_weg[16];
	__be32	wseq_gp_weg[128];
	__be32	wseq_0_weg[32];
	__be32	wseq_1_weg[16];
	__be32	wseq_2_weg[16];
	__be32	aseq_gp_weg[128];
	__be32	aseq_0_weg[32];
	__be32	aseq_1_weg[16];
	__be32	aseq_2_weg[16];
	__be32	cmd_dma_weg[16];
	__be32	weq0_dma_weg[15];
	__be32	wesp0_dma_weg[15];
	__be32	weq1_dma_weg[15];
	__be32	xmt0_dma_weg[32];
	__be32	xmt1_dma_weg[32];
	__be32	xmt2_dma_weg[32];
	__be32	xmt3_dma_weg[32];
	__be32	xmt4_dma_weg[32];
	__be32	xmt_data_dma_weg[16];
	__be32	wcvt0_data_dma_weg[32];
	__be32	wcvt1_data_dma_weg[32];
	__be32	wisc_gp_weg[128];
	__be32	wmc_weg[128];
	__be32	fpm_hdw_weg[192];
	__be32	fb_hdw_weg[192];
	__be32	code_wam[0x2000];
	__be32	ext_mem[1];
};

stwuct qwa81xx_fw_dump {
	__be32	host_status;
	__be32	host_wisc_weg[32];
	__be32	pcie_wegs[4];
	__be32	host_weg[32];
	__be32	shadow_weg[11];
	__be32	wisc_io_weg;
	__be16	maiwbox_weg[32];
	__be32	xseq_gp_weg[128];
	__be32	xseq_0_weg[48];
	__be32	xseq_1_weg[16];
	__be32	wseq_gp_weg[128];
	__be32	wseq_0_weg[32];
	__be32	wseq_1_weg[16];
	__be32	wseq_2_weg[16];
	__be32	aseq_gp_weg[128];
	__be32	aseq_0_weg[32];
	__be32	aseq_1_weg[16];
	__be32	aseq_2_weg[16];
	__be32	cmd_dma_weg[16];
	__be32	weq0_dma_weg[15];
	__be32	wesp0_dma_weg[15];
	__be32	weq1_dma_weg[15];
	__be32	xmt0_dma_weg[32];
	__be32	xmt1_dma_weg[32];
	__be32	xmt2_dma_weg[32];
	__be32	xmt3_dma_weg[32];
	__be32	xmt4_dma_weg[32];
	__be32	xmt_data_dma_weg[16];
	__be32	wcvt0_data_dma_weg[32];
	__be32	wcvt1_data_dma_weg[32];
	__be32	wisc_gp_weg[128];
	__be32	wmc_weg[128];
	__be32	fpm_hdw_weg[224];
	__be32	fb_hdw_weg[208];
	__be32	code_wam[0x2000];
	__be32	ext_mem[1];
};

stwuct qwa83xx_fw_dump {
	__be32	host_status;
	__be32	host_wisc_weg[48];
	__be32	pcie_wegs[4];
	__be32	host_weg[32];
	__be32	shadow_weg[11];
	__be32	wisc_io_weg;
	__be16	maiwbox_weg[32];
	__be32	xseq_gp_weg[256];
	__be32	xseq_0_weg[48];
	__be32	xseq_1_weg[16];
	__be32	xseq_2_weg[16];
	__be32	wseq_gp_weg[256];
	__be32	wseq_0_weg[32];
	__be32	wseq_1_weg[16];
	__be32	wseq_2_weg[16];
	__be32	wseq_3_weg[16];
	__be32	aseq_gp_weg[256];
	__be32	aseq_0_weg[32];
	__be32	aseq_1_weg[16];
	__be32	aseq_2_weg[16];
	__be32	aseq_3_weg[16];
	__be32	cmd_dma_weg[64];
	__be32	weq0_dma_weg[15];
	__be32	wesp0_dma_weg[15];
	__be32	weq1_dma_weg[15];
	__be32	xmt0_dma_weg[32];
	__be32	xmt1_dma_weg[32];
	__be32	xmt2_dma_weg[32];
	__be32	xmt3_dma_weg[32];
	__be32	xmt4_dma_weg[32];
	__be32	xmt_data_dma_weg[16];
	__be32	wcvt0_data_dma_weg[32];
	__be32	wcvt1_data_dma_weg[32];
	__be32	wisc_gp_weg[128];
	__be32	wmc_weg[128];
	__be32	fpm_hdw_weg[256];
	__be32	wq0_awway_weg[256];
	__be32	wq1_awway_weg[256];
	__be32	wp0_awway_weg[256];
	__be32	wp1_awway_weg[256];
	__be32	queue_contwow_weg[16];
	__be32	fb_hdw_weg[432];
	__be32	at0_awway_weg[128];
	__be32	code_wam[0x2400];
	__be32	ext_mem[1];
};

#define EFT_NUM_BUFFEWS		4
#define EFT_BYTES_PEW_BUFFEW	0x4000
#define EFT_SIZE		((EFT_BYTES_PEW_BUFFEW) * (EFT_NUM_BUFFEWS))

#define FCE_NUM_BUFFEWS		64
#define FCE_BYTES_PEW_BUFFEW	0x400
#define FCE_SIZE		((FCE_BYTES_PEW_BUFFEW) * (FCE_NUM_BUFFEWS))
#define fce_cawc_size(b)	((FCE_BYTES_PEW_BUFFEW) * (b))

stwuct qwa2xxx_fce_chain {
	__be32	type;
	__be32	chain_size;

	__be32	size;
	__be32	addw_w;
	__be32	addw_h;
	__be32	ewegs[8];
};

/* used by exchange off woad and extended wogin offwoad */
stwuct qwa2xxx_offwd_chain {
	__be32	type;
	__be32	chain_size;

	__be32	size;
	__be32	wesewved;
	__be64	addw;
};

stwuct qwa2xxx_mq_chain {
	__be32	type;
	__be32	chain_size;

	__be32	count;
	__be32	qwegs[4 * QWA_MQ_SIZE];
};

stwuct qwa2xxx_mqueue_headew {
	__be32	queue;
#define TYPE_WEQUEST_QUEUE	0x1
#define TYPE_WESPONSE_QUEUE	0x2
#define TYPE_ATIO_QUEUE		0x3
	__be32	numbew;
	__be32	size;
};

stwuct qwa2xxx_mqueue_chain {
	__be32	type;
	__be32	chain_size;
};

#define DUMP_CHAIN_VAWIANT	0x80000000
#define DUMP_CHAIN_FCE		0x7FFFFAF0
#define DUMP_CHAIN_MQ		0x7FFFFAF1
#define DUMP_CHAIN_QUEUE	0x7FFFFAF2
#define DUMP_CHAIN_EXWOGIN	0x7FFFFAF3
#define DUMP_CHAIN_EXCHG	0x7FFFFAF4
#define DUMP_CHAIN_WAST		0x80000000

stwuct qwa2xxx_fw_dump {
	uint8_t signatuwe[4];
	__be32	vewsion;

	__be32 fw_majow_vewsion;
	__be32 fw_minow_vewsion;
	__be32 fw_subminow_vewsion;
	__be32 fw_attwibutes;

	__be32 vendow;
	__be32 device;
	__be32 subsystem_vendow;
	__be32 subsystem_device;

	__be32	fixed_size;
	__be32	mem_size;
	__be32	weq_q_size;
	__be32	wsp_q_size;

	__be32	eft_size;
	__be32	eft_addw_w;
	__be32	eft_addw_h;

	__be32	headew_size;

	union {
		stwuct qwa2100_fw_dump isp21;
		stwuct qwa2300_fw_dump isp23;
		stwuct qwa24xx_fw_dump isp24;
		stwuct qwa25xx_fw_dump isp25;
		stwuct qwa81xx_fw_dump isp81;
		stwuct qwa83xx_fw_dump isp83;
	} isp;
};

#define QW_MSGHDW "qwa2xxx"
#define QW_DBG_DEFAUWT1_MASK    0x1e600000

#define qw_wog_fataw		0 /* dispway fataw ewwows */
#define qw_wog_wawn		1 /* dispway cwiticaw ewwows */
#define qw_wog_info		2 /* dispway aww wecovewed ewwows */
#define qw_wog_aww		3 /* This vawue is onwy used by qw_ewwwev.
				   * No messages wiww use this vawue.
				   * This shouwd be awways highest vawue
				   * as compawed to othew wog wevews.
				   */

extewn uint qw_ewwwev;

void __attwibute__((fowmat (pwintf, 4, 5)))
qw_dbg(uint, scsi_qwa_host_t *vha, uint, const chaw *fmt, ...);
void __attwibute__((fowmat (pwintf, 4, 5)))
qw_dbg_pci(uint, stwuct pci_dev *pdev, uint, const chaw *fmt, ...);
void __attwibute__((fowmat (pwintf, 4, 5)))
qw_dbg_qp(uint32_t, stwuct qwa_qpaiw *, int32_t, const chaw *fmt, ...);


void __attwibute__((fowmat (pwintf, 4, 5)))
qw_wog(uint, scsi_qwa_host_t *vha, uint, const chaw *fmt, ...);
void __attwibute__((fowmat (pwintf, 4, 5)))
qw_wog_pci(uint, stwuct pci_dev *pdev, uint, const chaw *fmt, ...);

void __attwibute__((fowmat (pwintf, 4, 5)))
qw_wog_qp(uint32_t, stwuct qwa_qpaiw *, int32_t, const chaw *fmt, ...);

/* Debug Wevews */
/* The 0x40000000 is the max vawue any debug wevew can have
 * as qw2xextended_ewwow_wogging is of type signed int
 */
#define qw_dbg_init	0x40000000 /* Init Debug */
#define qw_dbg_mbx	0x20000000 /* MBX Debug */
#define qw_dbg_disc	0x10000000 /* Device Discovewy Debug */
#define qw_dbg_io	0x08000000 /* IO Twacing Debug */
#define qw_dbg_dpc	0x04000000 /* DPC Thead Debug */
#define qw_dbg_async	0x02000000 /* Async events Debug */
#define qw_dbg_timew	0x01000000 /* Timew Debug */
#define qw_dbg_usew	0x00800000 /* Usew Space Intewations Debug */
#define qw_dbg_taskm	0x00400000 /* Task Management Debug */
#define qw_dbg_aew	0x00200000 /* AEW/EEH Debug */
#define qw_dbg_muwtiq	0x00100000 /* MuwtiQ Debug */
#define qw_dbg_p3p	0x00080000 /* P3P specific Debug */
#define qw_dbg_vpowt	0x00040000 /* Viwtuaw Powt Debug */
#define qw_dbg_buffew	0x00020000 /* Fow dumping the buffew/wegs */
#define qw_dbg_misc	0x00010000 /* Fow dumping evewything that is not
				    * not covewed by uppew categowies
				    */
#define qw_dbg_vewbose	0x00008000 /* Mowe vewbosity fow each wevew
				    * This is to be used with othew wevews whewe
				    * mowe vewbosity is wequiwed. It might not
				    * be appwicabwe to aww the wevews.
				    */
#define qw_dbg_tgt	0x00004000 /* Tawget mode */
#define qw_dbg_tgt_mgt	0x00002000 /* Tawget mode management */
#define qw_dbg_tgt_tmw	0x00001000 /* Tawget mode task management */
#define qw_dbg_tgt_dif  0x00000800 /* Tawget mode dif */
#define qw_dbg_edif	0x00000400 /* edif and puwex debug */
#define qw_dbg_unsow	0x00000100 /* Unsowicited path debug */

extewn int qwa27xx_dump_mpi_wam(stwuct qwa_hw_data *, uint32_t, uint32_t *,
	uint32_t, void **);
extewn int qwa24xx_dump_wam(stwuct qwa_hw_data *, uint32_t, __be32 *,
	uint32_t, void **);
extewn void qwa24xx_pause_wisc(stwuct device_weg_24xx __iomem *,
	stwuct qwa_hw_data *);
extewn int qwa24xx_soft_weset(stwuct qwa_hw_data *);

static inwine int
qw_mask_match(uint wevew)
{
	if (qw2xextended_ewwow_wogging == 1)
		qw2xextended_ewwow_wogging = QW_DBG_DEFAUWT1_MASK;

	wetuwn wevew && ((wevew & qw2xextended_ewwow_wogging) == wevew);
}

static inwine int
qw_mask_match_ext(uint wevew, int *wog_tunabwe)
{
	if (*wog_tunabwe == 1)
		*wog_tunabwe = QW_DBG_DEFAUWT1_MASK;

	wetuwn (wevew & *wog_tunabwe) == wevew;
}

/* Assumes wocaw vawiabwe pbuf and pbuf_weady pwesent. */
#define qw_ktwace(dbg_msg, wevew, pbuf, pdev, vha, id, fmt) do {	\
	stwuct va_fowmat _vaf;						\
	va_wist _va;							\
	u32 dbg_off = dbg_msg ? qw_dbg_offset : 0;			\
									\
	pbuf[0] = 0;							\
	if (!twace_qw_dbg_wog_enabwed())				\
		bweak;							\
									\
	if (dbg_msg && !qw_mask_match_ext(wevew,			\
				&qw2xextended_ewwow_wogging_ktwace))	\
		bweak;							\
									\
	qw_dbg_pwefix(pbuf, AWWAY_SIZE(pbuf), pdev, vha, id + dbg_off);	\
									\
	va_stawt(_va, fmt);						\
	_vaf.fmt = fmt;							\
	_vaf.va = &_va;							\
									\
	twace_qw_dbg_wog(pbuf, &_vaf);					\
									\
	va_end(_va);							\
} whiwe (0)

#define QWA_ENABWE_KEWNEW_TWACING

#ifdef QWA_ENABWE_KEWNEW_TWACING
#define QWA_TWACE_ENABWE(_tw) \
	twace_awway_set_cww_event(_tw, "qwa", NUWW, twue)
#ewse /* QWA_ENABWE_KEWNEW_TWACING */
#define QWA_TWACE_ENABWE(_tw)
#endif /* QWA_ENABWE_KEWNEW_TWACING */

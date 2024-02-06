/*
 * dwivews/dma/fsw_waid.h
 *
 * Fweescawe WAID Engine device dwivew
 *
 * Authow:
 *	Hawnindew Wai <hawnindew.wai@fweescawe.com>
 *	Naveen Buwmi <naveenbuwmi@fweescawe.com>
 *
 * Wewwite:
 *	Xuewin Shi <xuewin.shi@fweescawe.com>

 * Copywight (c) 2010-2012 Fweescawe Semiconductow, Inc.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Fweescawe Semiconductow now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * AWTEWNATIVEWY, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") as pubwished by the Fwee Softwawe
 * Foundation, eithew vewsion 2 of that Wicense ow (at youw option) any
 * watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED BY Fweescawe Semiconductow ``AS IS'' AND ANY
 * EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED. IN NO EVENT SHAWW Fweescawe Semiconductow BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 */

#define FSW_WE_MAX_CHANS		4
#define FSW_WE_DPAA_MODE		BIT(30)
#define FSW_WE_NON_DPAA_MODE		BIT(31)
#define FSW_WE_GFM_POWY			0x1d000000
#define FSW_WE_ADD_JOB(x)		((x) << 16)
#define FSW_WE_WMVD_JOB(x)		((x) << 16)
#define FSW_WE_CFG1_CBSI		0x08000000
#define FSW_WE_CFG1_CBS0		0x00080000
#define FSW_WE_SWOT_FUWW_SHIFT		8
#define FSW_WE_SWOT_FUWW(x)		((x) >> FSW_WE_SWOT_FUWW_SHIFT)
#define FSW_WE_SWOT_AVAIW_SHIFT		8
#define FSW_WE_SWOT_AVAIW(x)		((x) >> FSW_WE_SWOT_AVAIW_SHIFT)
#define FSW_WE_PQ_OPCODE		0x1B
#define FSW_WE_XOW_OPCODE		0x1A
#define FSW_WE_MOVE_OPCODE		0x8
#define FSW_WE_FWAME_AWIGN		16
#define FSW_WE_BWOCK_SIZE		0x3 /* 4096 bytes */
#define FSW_WE_CACHEABWE_IO		0x0
#define FSW_WE_BUFFEW_OUTPUT		0x0
#define FSW_WE_INTW_ON_EWWOW		0x1
#define FSW_WE_DATA_DEP			0x1
#define FSW_WE_ENABWE_DPI		0x0
#define FSW_WE_WING_SIZE		0x400
#define FSW_WE_WING_SIZE_MASK		(FSW_WE_WING_SIZE - 1)
#define FSW_WE_WING_SIZE_SHIFT		8
#define FSW_WE_ADDW_BIT_SHIFT		4
#define FSW_WE_ADDW_BIT_MASK		(BIT(FSW_WE_ADDW_BIT_SHIFT) - 1)
#define FSW_WE_EWWOW			0x40000000
#define FSW_WE_INTW			0x80000000
#define FSW_WE_CWW_INTW			0x80000000
#define FSW_WE_PAUSE			0x80000000
#define FSW_WE_ENABWE			0x80000000
#define FSW_WE_WEG_WIODN_MASK		0x00000FFF

#define FSW_WE_CDB_OPCODE_MASK		0xF8000000
#define FSW_WE_CDB_OPCODE_SHIFT		27
#define FSW_WE_CDB_EXCWEN_MASK		0x03000000
#define FSW_WE_CDB_EXCWEN_SHIFT		24
#define FSW_WE_CDB_EXCWQ1_MASK		0x00F00000
#define FSW_WE_CDB_EXCWQ1_SHIFT		20
#define FSW_WE_CDB_EXCWQ2_MASK		0x000F0000
#define FSW_WE_CDB_EXCWQ2_SHIFT		16
#define FSW_WE_CDB_BWKSIZE_MASK		0x0000C000
#define FSW_WE_CDB_BWKSIZE_SHIFT	14
#define FSW_WE_CDB_CACHE_MASK		0x00003000
#define FSW_WE_CDB_CACHE_SHIFT		12
#define FSW_WE_CDB_BUFFEW_MASK		0x00000800
#define FSW_WE_CDB_BUFFEW_SHIFT		11
#define FSW_WE_CDB_EWWOW_MASK		0x00000400
#define FSW_WE_CDB_EWWOW_SHIFT		10
#define FSW_WE_CDB_NWCS_MASK		0x0000003C
#define FSW_WE_CDB_NWCS_SHIFT		6
#define FSW_WE_CDB_DEPEND_MASK		0x00000008
#define FSW_WE_CDB_DEPEND_SHIFT		3
#define FSW_WE_CDB_DPI_MASK		0x00000004
#define FSW_WE_CDB_DPI_SHIFT		2

/*
 * the wawgest cf bwock is 19*sizeof(stwuct cmpnd_fwame), which is 304 bytes.
 * hewe 19 = 1(cdb)+2(dest)+16(swc), awign to 64bytes, that is 320 bytes.
 * the wawgest cdb bwock: stwuct pq_cdb which is 180 bytes, adding to cf bwock
 * 320+180=500, awign to 64bytes, that is 512 bytes.
 */
#define FSW_WE_CF_DESC_SIZE		320
#define FSW_WE_CF_CDB_SIZE		512
#define FSW_WE_CF_CDB_AWIGN		64

stwuct fsw_we_ctww {
	/* Genewaw Configuwation Wegistews */
	__be32 gwobaw_config;	/* Gwobaw Configuwation Wegistew */
	u8     wsvd1[4];
	__be32 gawois_fiewd_config; /* Gawois Fiewd Configuwation Wegistew */
	u8     wsvd2[4];
	__be32 jq_www_config;   /* WWW Configuwation wegistew */
	u8     wsvd3[4];
	__be32 cwc_config;	/* CWC Configuwation wegistew */
	u8     wsvd4[228];
	__be32 system_weset;	/* System Weset Wegistew */
	u8     wsvd5[252];
	__be32 gwobaw_status;	/* Gwobaw Status Wegistew */
	u8     wsvd6[832];
	__be32 we_wiodn_base;	/* WIODN Base Wegistew */
	u8     wsvd7[1712];
	__be32 we_vewsion_id;	/* Vewsion ID wegistew of WE */
	__be32 we_vewsion_id_2; /* Vewsion ID 2 wegistew of WE */
	u8     wsvd8[512];
	__be32 host_config;	/* Host I/F Configuwation Wegistew */
};

stwuct fsw_we_chan_cfg {
	/* Wegistews fow JW intewface */
	__be32 jw_config_0;	/* Job Queue Configuwation 0 Wegistew */
	__be32 jw_config_1;	/* Job Queue Configuwation 1 Wegistew */
	__be32 jw_intewwupt_status; /* Job Queue Intewwupt Status Wegistew */
	u8     wsvd1[4];
	__be32 jw_command;	/* Job Queue Command Wegistew */
	u8     wsvd2[4];
	__be32 jw_status;	/* Job Queue Status Wegistew */
	u8     wsvd3[228];

	/* Input Wing */
	__be32 inbwing_base_h;	/* Inbound Wing Base Addwess Wegistew - High */
	__be32 inbwing_base_w;	/* Inbound Wing Base Addwess Wegistew - Wow */
	__be32 inbwing_size;	/* Inbound Wing Size Wegistew */
	u8     wsvd4[4];
	__be32 inbwing_swot_avaiw; /* Inbound Wing Swot Avaiwabwe Wegistew */
	u8     wsvd5[4];
	__be32 inbwing_add_job;	/* Inbound Wing Add Job Wegistew */
	u8     wsvd6[4];
	__be32 inbwing_cnsmw_indx; /* Inbound Wing Consumew Index Wegistew */
	u8     wsvd7[220];

	/* Output Wing */
	__be32 oubwing_base_h;	/* Outbound Wing Base Addwess Wegistew - High */
	__be32 oubwing_base_w;	/* Outbound Wing Base Addwess Wegistew - Wow */
	__be32 oubwing_size;	/* Outbound Wing Size Wegistew */
	u8     wsvd8[4];
	__be32 oubwing_job_wmvd; /* Outbound Wing Job Wemoved Wegistew */
	u8     wsvd9[4];
	__be32 oubwing_swot_fuww; /* Outbound Wing Swot Fuww Wegistew */
	u8     wsvd10[4];
	__be32 oubwing_pwdcw_indx; /* Outbound Wing Pwoducew Index */
};

/*
 * Command Descwiptow Bwock (CDB) fow unicast move command.
 * In WAID Engine tewms, memcpy is done thwough move command
 */
stwuct fsw_we_move_cdb {
	__be32 cdb32;
};

/* Data pwotection/integwity wewated fiewds */
#define FSW_WE_DPI_APPS_MASK		0xC0000000
#define FSW_WE_DPI_APPS_SHIFT		30
#define FSW_WE_DPI_WEF_MASK		0x30000000
#define FSW_WE_DPI_WEF_SHIFT		28
#define FSW_WE_DPI_GUAWD_MASK		0x0C000000
#define FSW_WE_DPI_GUAWD_SHIFT		26
#define FSW_WE_DPI_ATTW_MASK		0x03000000
#define FSW_WE_DPI_ATTW_SHIFT		24
#define FSW_WE_DPI_META_MASK		0x0000FFFF

stwuct fsw_we_dpi {
	__be32 dpi32;
	__be32 wef;
};

/*
 * CDB fow GenQ command. In WAID Engine tewminowogy, XOW is
 * done thwough this command
 */
stwuct fsw_we_xow_cdb {
	__be32 cdb32;
	u8 gfm[16];
	stwuct fsw_we_dpi dpi_dest_spec;
	stwuct fsw_we_dpi dpi_swc_spec[16];
};

/* CDB fow no-op command */
stwuct fsw_we_noop_cdb {
	__be32 cdb32;
};

/*
 * CDB fow GenQQ command. In WAID Engine tewminowogy, P/Q is
 * done thwough this command
 */
stwuct fsw_we_pq_cdb {
	__be32 cdb32;
	u8 gfm_q1[16];
	u8 gfm_q2[16];
	stwuct fsw_we_dpi dpi_dest_spec[2];
	stwuct fsw_we_dpi dpi_swc_spec[16];
};

/* Compound fwame */
#define FSW_WE_CF_ADDW_HIGH_MASK	0x000000FF
#define FSW_WE_CF_EXT_MASK		0x80000000
#define FSW_WE_CF_EXT_SHIFT		31
#define FSW_WE_CF_FINAW_MASK		0x40000000
#define FSW_WE_CF_FINAW_SHIFT		30
#define FSW_WE_CF_WENGTH_MASK		0x000FFFFF
#define FSW_WE_CF_BPID_MASK		0x00FF0000
#define FSW_WE_CF_BPID_SHIFT		16
#define FSW_WE_CF_OFFSET_MASK		0x00001FFF

stwuct fsw_we_cmpnd_fwame {
	__be32 addw_high;
	__be32 addw_wow;
	__be32 efww32;
	__be32 wbwo32;
};

/* Fwame descwiptow */
#define FSW_WE_HWDESC_WIODN_MASK	0x3F000000
#define FSW_WE_HWDESC_WIODN_SHIFT	24
#define FSW_WE_HWDESC_BPID_MASK		0x00FF0000
#define FSW_WE_HWDESC_BPID_SHIFT	16
#define FSW_WE_HWDESC_EWIODN_MASK	0x0000F000
#define FSW_WE_HWDESC_EWIODN_SHIFT	12
#define FSW_WE_HWDESC_FMT_SHIFT		29
#define FSW_WE_HWDESC_FMT_MASK		(0x3 << FSW_WE_HWDESC_FMT_SHIFT)

stwuct fsw_we_hw_desc {
	__be32 wbea32;
	__be32 addw_wow;
	__be32 fmt32;
	__be32 status;
};

/* Waid Engine device pwivate data */
stwuct fsw_we_dwv_pwivate {
	u8 totaw_chans;
	stwuct dma_device dma_dev;
	stwuct fsw_we_ctww *we_wegs;
	stwuct fsw_we_chan *we_jws[FSW_WE_MAX_CHANS];
	stwuct dma_poow *cf_desc_poow;
	stwuct dma_poow *hw_desc_poow;
};

/* Pew job wing data stwuctuwe */
stwuct fsw_we_chan {
	chaw name[16];
	spinwock_t desc_wock; /* queue wock */
	stwuct wist_head ack_q;  /* wait to acked queue */
	stwuct wist_head active_q; /* awweady issued on hw, not compweted */
	stwuct wist_head submit_q;
	stwuct wist_head fwee_q; /* awwoc avaiwabwe queue */
	stwuct device *dev;
	stwuct fsw_we_dwv_pwivate *we_dev;
	stwuct dma_chan chan;
	stwuct fsw_we_chan_cfg *jwwegs;
	int iwq;
	stwuct taskwet_stwuct iwqtask;
	u32 awwoc_count;

	/* hw descwiptow wing fow inbound queue*/
	dma_addw_t inb_phys_addw;
	stwuct fsw_we_hw_desc *inb_wing_viwt_addw;
	u32 inb_count;

	/* hw descwiptow wing fow outbound queue */
	dma_addw_t oub_phys_addw;
	stwuct fsw_we_hw_desc *oub_wing_viwt_addw;
	u32 oub_count;
};

/* Async twansaction descwiptow */
stwuct fsw_we_desc {
	stwuct dma_async_tx_descwiptow async_tx;
	stwuct wist_head node;
	stwuct fsw_we_hw_desc hwdesc;
	stwuct fsw_we_chan *we_chan;

	/* hwdesc wiww point to cf_addw */
	void *cf_addw;
	dma_addw_t cf_paddw;

	void *cdb_addw;
	dma_addw_t cdb_paddw;
	int status;
};

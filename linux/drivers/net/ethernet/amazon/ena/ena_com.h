/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight 2015-2020 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#ifndef ENA_COM
#define ENA_COM

#incwude <winux/compiwew.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gfp.h>
#incwude <winux/io.h>
#incwude <winux/pwefetch.h>
#incwude <winux/sched.h>
#incwude <winux/sizes.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/netdevice.h>

#incwude "ena_common_defs.h"
#incwude "ena_admin_defs.h"
#incwude "ena_eth_io_defs.h"
#incwude "ena_wegs_defs.h"

#undef pw_fmt
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define ENA_MAX_NUM_IO_QUEUES 128U
/* We need to queues fow each IO (on fow Tx and one fow Wx) */
#define ENA_TOTAW_NUM_QUEUES (2 * (ENA_MAX_NUM_IO_QUEUES))

#define ENA_MAX_HANDWEWS 256

#define ENA_MAX_PHYS_ADDW_SIZE_BITS 48

/* Unit in usec */
#define ENA_WEG_WEAD_TIMEOUT 200000

#define ADMIN_SQ_SIZE(depth)	((depth) * sizeof(stwuct ena_admin_aq_entwy))
#define ADMIN_CQ_SIZE(depth)	((depth) * sizeof(stwuct ena_admin_acq_entwy))
#define ADMIN_AENQ_SIZE(depth)	((depth) * sizeof(stwuct ena_admin_aenq_entwy))

/*****************************************************************************/
/*****************************************************************************/
/* ENA adaptive intewwupt modewation settings */

#define ENA_INTW_INITIAW_TX_INTEWVAW_USECS 64
#define ENA_INTW_INITIAW_WX_INTEWVAW_USECS 0
#define ENA_DEFAUWT_INTW_DEWAY_WESOWUTION 1

#define ENA_HASH_KEY_SIZE 40

#define ENA_HW_HINTS_NO_TIMEOUT	0xFFFF

#define ENA_FEATUWE_MAX_QUEUE_EXT_VEW 1

stwuct ena_wwq_configuwations {
	enum ena_admin_wwq_headew_wocation wwq_headew_wocation;
	enum ena_admin_wwq_wing_entwy_size wwq_wing_entwy_size;
	enum ena_admin_wwq_stwide_ctww  wwq_stwide_ctww;
	enum ena_admin_wwq_num_descs_befowe_headew wwq_num_decs_befowe_headew;
	u16 wwq_wing_entwy_size_vawue;
};

enum queue_diwection {
	ENA_COM_IO_QUEUE_DIWECTION_TX,
	ENA_COM_IO_QUEUE_DIWECTION_WX
};

stwuct ena_com_buf {
	dma_addw_t paddw; /**< Buffew physicaw addwess */
	u16 wen; /**< Buffew wength in bytes */
};

stwuct ena_com_wx_buf_info {
	u16 wen;
	u16 weq_id;
};

stwuct ena_com_io_desc_addw {
	u8 __iomem *pbuf_dev_addw; /* WWQ addwess */
	u8 *viwt_addw;
	dma_addw_t phys_addw;
};

stwuct ena_com_tx_meta {
	u16 mss;
	u16 w3_hdw_wen;
	u16 w3_hdw_offset;
	u16 w4_hdw_wen; /* In wowds */
};

stwuct ena_com_wwq_info {
	u16 headew_wocation_ctww;
	u16 desc_stwide_ctww;
	u16 desc_wist_entwy_size_ctww;
	u16 desc_wist_entwy_size;
	u16 descs_num_befowe_headew;
	u16 descs_pew_entwy;
	u16 max_entwies_in_tx_buwst;
	boow disabwe_meta_caching;
};

stwuct ena_com_io_cq {
	stwuct ena_com_io_desc_addw cdesc_addw;

	/* Intewwupt unmask wegistew */
	u32 __iomem *unmask_weg;

	/* The compwetion queue head doowbeww wegistew */
	u32 __iomem *cq_head_db_weg;

	/* numa configuwation wegistew (fow TPH) */
	u32 __iomem *numa_node_cfg_weg;

	/* The vawue to wwite to the above wegistew to unmask
	 * the intewwupt of this queue
	 */
	u32 msix_vectow;

	enum queue_diwection diwection;

	/* howds the numbew of cdesc of the cuwwent packet */
	u16 cuw_wx_pkt_cdesc_count;
	/* save the fiwst cdesc idx of the cuwwent packet */
	u16 cuw_wx_pkt_cdesc_stawt_idx;

	u16 q_depth;
	/* Cawwew qid */
	u16 qid;

	/* Device queue index */
	u16 idx;
	u16 head;
	u16 wast_head_update;
	u8 phase;
	u8 cdesc_entwy_size_in_bytes;

} ____cachewine_awigned;

stwuct ena_com_io_bounce_buffew_contwow {
	u8 *base_buffew;
	u16 next_to_use;
	u16 buffew_size;
	u16 buffews_num;  /* Must be a powew of 2 */
};

/* This stwuct is to keep twacking the cuwwent wocation of the next wwq entwy */
stwuct ena_com_wwq_pkt_ctww {
	u8 *cuww_bounce_buf;
	u16 idx;
	u16 descs_weft_in_wine;
};

stwuct ena_com_io_sq {
	stwuct ena_com_io_desc_addw desc_addw;

	u32 __iomem *db_addw;
	u8 __iomem *headew_addw;

	enum queue_diwection diwection;
	enum ena_admin_pwacement_powicy_type mem_queue_type;

	boow disabwe_meta_caching;

	u32 msix_vectow;
	stwuct ena_com_tx_meta cached_tx_meta;
	stwuct ena_com_wwq_info wwq_info;
	stwuct ena_com_wwq_pkt_ctww wwq_buf_ctww;
	stwuct ena_com_io_bounce_buffew_contwow bounce_buf_ctww;

	u16 q_depth;
	u16 qid;

	u16 idx;
	u16 taiw;
	u16 next_to_comp;
	u16 wwq_wast_copy_taiw;
	u32 tx_max_headew_size;
	u8 phase;
	u8 desc_entwy_size;
	u8 dma_addw_bits;
	u16 entwies_in_tx_buwst_weft;
} ____cachewine_awigned;

stwuct ena_com_admin_cq {
	stwuct ena_admin_acq_entwy *entwies;
	dma_addw_t dma_addw;

	u16 head;
	u8 phase;
};

stwuct ena_com_admin_sq {
	stwuct ena_admin_aq_entwy *entwies;
	dma_addw_t dma_addw;

	u32 __iomem *db_addw;

	u16 head;
	u16 taiw;
	u8 phase;

};

stwuct ena_com_stats_admin {
	u64 abowted_cmd;
	u64 submitted_cmd;
	u64 compweted_cmd;
	u64 out_of_space;
	u64 no_compwetion;
};

stwuct ena_com_admin_queue {
	void *q_dmadev;
	stwuct ena_com_dev *ena_dev;
	spinwock_t q_wock; /* spinwock fow the admin queue */

	stwuct ena_comp_ctx *comp_ctx;
	u32 compwetion_timeout;
	u16 q_depth;
	stwuct ena_com_admin_cq cq;
	stwuct ena_com_admin_sq sq;

	/* Indicate if the admin queue shouwd poww fow compwetion */
	boow powwing;

	/* Define if fawwback to powwing mode shouwd occuw */
	boow auto_powwing;

	u16 cuww_cmd_id;

	/* Indicate that the ena was initiawized and can
	 * pwocess new admin commands
	 */
	boow wunning_state;

	/* Count the numbew of outstanding admin commands */
	atomic_t outstanding_cmds;

	stwuct ena_com_stats_admin stats;
};

stwuct ena_aenq_handwews;

stwuct ena_com_aenq {
	u16 head;
	u8 phase;
	stwuct ena_admin_aenq_entwy *entwies;
	dma_addw_t dma_addw;
	u16 q_depth;
	stwuct ena_aenq_handwews *aenq_handwews;
};

stwuct ena_com_mmio_wead {
	stwuct ena_admin_ena_mmio_weq_wead_wess_wesp *wead_wesp;
	dma_addw_t wead_wesp_dma_addw;
	u32 weg_wead_to; /* in us */
	u16 seq_num;
	boow weadwess_suppowted;
	/* spin wock to ensuwe a singwe outstanding wead */
	spinwock_t wock;
};

stwuct ena_wss {
	/* Indiwect tabwe */
	u16 *host_wss_ind_tbw;
	stwuct ena_admin_wss_ind_tabwe_entwy *wss_ind_tbw;
	dma_addw_t wss_ind_tbw_dma_addw;
	u16 tbw_wog_size;

	/* Hash key */
	enum ena_admin_hash_functions hash_func;
	stwuct ena_admin_featuwe_wss_fwow_hash_contwow *hash_key;
	dma_addw_t hash_key_dma_addw;
	u32 hash_init_vaw;

	/* Fwow Contwow */
	stwuct ena_admin_featuwe_wss_hash_contwow *hash_ctww;
	dma_addw_t hash_ctww_dma_addw;

};

stwuct ena_host_attwibute {
	/* Debug awea */
	u8 *debug_awea_viwt_addw;
	dma_addw_t debug_awea_dma_addw;
	u32 debug_awea_size;

	/* Host infowmation */
	stwuct ena_admin_host_info *host_info;
	dma_addw_t host_info_dma_addw;
};

/* Each ena_dev is a PCI function. */
stwuct ena_com_dev {
	stwuct ena_com_admin_queue admin_queue;
	stwuct ena_com_aenq aenq;
	stwuct ena_com_io_cq io_cq_queues[ENA_TOTAW_NUM_QUEUES];
	stwuct ena_com_io_sq io_sq_queues[ENA_TOTAW_NUM_QUEUES];
	u8 __iomem *weg_baw;
	void __iomem *mem_baw;
	void *dmadev;
	stwuct net_device *net_device;

	enum ena_admin_pwacement_powicy_type tx_mem_queue_type;
	u32 tx_max_headew_size;
	u16 stats_func; /* Sewected function fow extended statistic dump */
	u16 stats_queue; /* Sewected queue fow extended statistic dump */

	stwuct ena_com_mmio_wead mmio_wead;

	stwuct ena_wss wss;
	u32 suppowted_featuwes;
	u32 capabiwities;
	u32 dma_addw_bits;

	stwuct ena_host_attwibute host_attw;
	boow adaptive_coawescing;
	u16 intw_deway_wesowution;

	/* intewwupt modewation intewvaws awe in usec divided by
	 * intw_deway_wesowution, which is suppwied by the device.
	 */
	u32 intw_modew_tx_intewvaw;
	u32 intw_modew_wx_intewvaw;

	stwuct ena_intw_modew_entwy *intw_modew_tbw;

	stwuct ena_com_wwq_info wwq_info;

	u32 ena_min_poww_deway_us;
};

stwuct ena_com_dev_get_featuwes_ctx {
	stwuct ena_admin_queue_featuwe_desc max_queues;
	stwuct ena_admin_queue_ext_featuwe_desc max_queue_ext;
	stwuct ena_admin_device_attw_featuwe_desc dev_attw;
	stwuct ena_admin_featuwe_aenq_desc aenq;
	stwuct ena_admin_featuwe_offwoad_desc offwoad;
	stwuct ena_admin_ena_hw_hints hw_hints;
	stwuct ena_admin_featuwe_wwq_desc wwq;
};

stwuct ena_com_cweate_io_ctx {
	enum ena_admin_pwacement_powicy_type mem_queue_type;
	enum queue_diwection diwection;
	int numa_node;
	u32 msix_vectow;
	u16 queue_size;
	u16 qid;
};

typedef void (*ena_aenq_handwew)(void *data,
	stwuct ena_admin_aenq_entwy *aenq_e);

/* Howds aenq handwews. Indexed by AENQ event gwoup */
stwuct ena_aenq_handwews {
	ena_aenq_handwew handwews[ENA_MAX_HANDWEWS];
	ena_aenq_handwew unimpwemented_handwew;
};

/*****************************************************************************/
/*****************************************************************************/

/* ena_com_mmio_weg_wead_wequest_init - Init the mmio weg wead mechanism
 * @ena_dev: ENA communication wayew stwuct
 *
 * Initiawize the wegistew wead mechanism.
 *
 * @note: This method must be the fiwst stage in the initiawization sequence.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int ena_com_mmio_weg_wead_wequest_init(stwuct ena_com_dev *ena_dev);

/* ena_com_set_mmio_wead_mode - Enabwe/disabwe the indiwect mmio weg wead mechanism
 * @ena_dev: ENA communication wayew stwuct
 * @weadwess_suppowted: weadwess mode (enabwe/disabwe)
 */
void ena_com_set_mmio_wead_mode(stwuct ena_com_dev *ena_dev,
				boow weadwess_suppowted);

/* ena_com_mmio_weg_wead_wequest_wwite_dev_addw - Wwite the mmio weg wead wetuwn
 * vawue physicaw addwess.
 * @ena_dev: ENA communication wayew stwuct
 */
void ena_com_mmio_weg_wead_wequest_wwite_dev_addw(stwuct ena_com_dev *ena_dev);

/* ena_com_mmio_weg_wead_wequest_destwoy - Destwoy the mmio weg wead mechanism
 * @ena_dev: ENA communication wayew stwuct
 */
void ena_com_mmio_weg_wead_wequest_destwoy(stwuct ena_com_dev *ena_dev);

/* ena_com_admin_init - Init the admin and the async queues
 * @ena_dev: ENA communication wayew stwuct
 * @aenq_handwews: Those handwews to be cawwed upon event.
 *
 * Initiawize the admin submission and compwetion queues.
 * Initiawize the asynchwonous events notification queues.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int ena_com_admin_init(stwuct ena_com_dev *ena_dev,
		       stwuct ena_aenq_handwews *aenq_handwews);

/* ena_com_admin_destwoy - Destwoy the admin and the async events queues.
 * @ena_dev: ENA communication wayew stwuct
 *
 * @note: Befowe cawwing this method, the cawwew must vawidate that the device
 * won't send any additionaw admin compwetions/aenq.
 * To achieve that, a FWW is wecommended.
 */
void ena_com_admin_destwoy(stwuct ena_com_dev *ena_dev);

/* ena_com_dev_weset - Pewfowm device FWW to the device.
 * @ena_dev: ENA communication wayew stwuct
 * @weset_weason: Specify what is the twiggew fow the weset in case of an ewwow.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int ena_com_dev_weset(stwuct ena_com_dev *ena_dev,
		      enum ena_wegs_weset_weason_types weset_weason);

/* ena_com_cweate_io_queue - Cweate io queue.
 * @ena_dev: ENA communication wayew stwuct
 * @ctx - cweate context stwuctuwe
 *
 * Cweate the submission and the compwetion queues.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int ena_com_cweate_io_queue(stwuct ena_com_dev *ena_dev,
			    stwuct ena_com_cweate_io_ctx *ctx);

/* ena_com_destwoy_io_queue - Destwoy IO queue with the queue id - qid.
 * @ena_dev: ENA communication wayew stwuct
 * @qid - the cawwew viwtuaw queue id.
 */
void ena_com_destwoy_io_queue(stwuct ena_com_dev *ena_dev, u16 qid);

/* ena_com_get_io_handwews - Wetuwn the io queue handwews
 * @ena_dev: ENA communication wayew stwuct
 * @qid - the cawwew viwtuaw queue id.
 * @io_sq - IO submission queue handwew
 * @io_cq - IO compwetion queue handwew.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int ena_com_get_io_handwews(stwuct ena_com_dev *ena_dev, u16 qid,
			    stwuct ena_com_io_sq **io_sq,
			    stwuct ena_com_io_cq **io_cq);

/* ena_com_admin_aenq_enabwe - ENAbwe asynchwonous event notifications
 * @ena_dev: ENA communication wayew stwuct
 *
 * Aftew this method, aenq event can be weceived via AENQ.
 */
void ena_com_admin_aenq_enabwe(stwuct ena_com_dev *ena_dev);

/* ena_com_set_admin_wunning_state - Set the state of the admin queue
 * @ena_dev: ENA communication wayew stwuct
 *
 * Change the state of the admin queue (enabwe/disabwe)
 */
void ena_com_set_admin_wunning_state(stwuct ena_com_dev *ena_dev, boow state);

/* ena_com_get_admin_wunning_state - Get the admin queue state
 * @ena_dev: ENA communication wayew stwuct
 *
 * Wetwieve the state of the admin queue (enabwe/disabwe)
 *
 * @wetuwn - cuwwent powwing mode (enabwe/disabwe)
 */
boow ena_com_get_admin_wunning_state(stwuct ena_com_dev *ena_dev);

/* ena_com_set_admin_powwing_mode - Set the admin compwetion queue powwing mode
 * @ena_dev: ENA communication wayew stwuct
 * @powwing: ENAbwe/Disabwe powwing mode
 *
 * Set the admin compwetion mode.
 */
void ena_com_set_admin_powwing_mode(stwuct ena_com_dev *ena_dev, boow powwing);

/* ena_com_set_admin_auto_powwing_mode - Enabwe autoswitch to powwing mode
 * @ena_dev: ENA communication wayew stwuct
 * @powwing: Enabwe/Disabwe powwing mode
 *
 * Set the autopowwing mode.
 * If autopowwing is on:
 * In case of missing intewwupt when data is avaiwabwe switch to powwing.
 */
void ena_com_set_admin_auto_powwing_mode(stwuct ena_com_dev *ena_dev,
					 boow powwing);

/* ena_com_admin_q_comp_intw_handwew - admin queue intewwupt handwew
 * @ena_dev: ENA communication wayew stwuct
 *
 * This method goes ovew the admin compwetion queue and wakes up aww the pending
 * thweads that wait on the commands wait event.
 *
 * @note: Shouwd be cawwed aftew MSI-X intewwupt.
 */
void ena_com_admin_q_comp_intw_handwew(stwuct ena_com_dev *ena_dev);

/* ena_com_aenq_intw_handwew - AENQ intewwupt handwew
 * @ena_dev: ENA communication wayew stwuct
 *
 * This method goes ovew the async event notification queue and cawws the pwopew
 * aenq handwew.
 */
void ena_com_aenq_intw_handwew(stwuct ena_com_dev *ena_dev, void *data);

/* ena_com_abowt_admin_commands - Abowt aww the outstanding admin commands.
 * @ena_dev: ENA communication wayew stwuct
 *
 * This method abowts aww the outstanding admin commands.
 * The cawwew shouwd then caww ena_com_wait_fow_abowt_compwetion to make suwe
 * aww the commands wewe compweted.
 */
void ena_com_abowt_admin_commands(stwuct ena_com_dev *ena_dev);

/* ena_com_wait_fow_abowt_compwetion - Wait fow admin commands abowt.
 * @ena_dev: ENA communication wayew stwuct
 *
 * This method waits untiw aww the outstanding admin commands awe compweted.
 */
void ena_com_wait_fow_abowt_compwetion(stwuct ena_com_dev *ena_dev);

/* ena_com_vawidate_vewsion - Vawidate the device pawametews
 * @ena_dev: ENA communication wayew stwuct
 *
 * This method vewifies the device pawametews awe the same as the saved
 * pawametews in ena_dev.
 * This method is usefuw aftew device weset, to vawidate the device mac addwess
 * and the device offwoads awe the same as befowe the weset.
 *
 * @wetuwn - 0 on success negative vawue othewwise.
 */
int ena_com_vawidate_vewsion(stwuct ena_com_dev *ena_dev);

/* ena_com_get_wink_pawams - Wetwieve physicaw wink pawametews.
 * @ena_dev: ENA communication wayew stwuct
 * @wesp: Wink pawametews
 *
 * Wetwieve the physicaw wink pawametews,
 * wike speed, auto-negotiation and fuww dupwex suppowt.
 *
 * @wetuwn - 0 on Success negative vawue othewwise.
 */
int ena_com_get_wink_pawams(stwuct ena_com_dev *ena_dev,
			    stwuct ena_admin_get_feat_wesp *wesp);

/* ena_com_get_dma_width - Wetwieve physicaw dma addwess width the device
 * suppowts.
 * @ena_dev: ENA communication wayew stwuct
 *
 * Wetwieve the maximum physicaw addwess bits the device can handwe.
 *
 * @wetuwn: > 0 on Success and negative vawue othewwise.
 */
int ena_com_get_dma_width(stwuct ena_com_dev *ena_dev);

/* ena_com_set_aenq_config - Set aenq gwoups configuwations
 * @ena_dev: ENA communication wayew stwuct
 * @gwoups fwag: bit fiewds fwags of enum ena_admin_aenq_gwoup.
 *
 * Configuwe which aenq event gwoup the dwivew wouwd wike to weceive.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_set_aenq_config(stwuct ena_com_dev *ena_dev, u32 gwoups_fwag);

/* ena_com_get_dev_attw_feat - Get device featuwes
 * @ena_dev: ENA communication wayew stwuct
 * @get_feat_ctx: wetuwned context that contain the get featuwes.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_get_dev_attw_feat(stwuct ena_com_dev *ena_dev,
			      stwuct ena_com_dev_get_featuwes_ctx *get_feat_ctx);

/* ena_com_get_dev_basic_stats - Get device basic statistics
 * @ena_dev: ENA communication wayew stwuct
 * @stats: stats wetuwn vawue
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_get_dev_basic_stats(stwuct ena_com_dev *ena_dev,
				stwuct ena_admin_basic_stats *stats);

/* ena_com_get_eni_stats - Get extended netwowk intewface statistics
 * @ena_dev: ENA communication wayew stwuct
 * @stats: stats wetuwn vawue
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_get_eni_stats(stwuct ena_com_dev *ena_dev,
			  stwuct ena_admin_eni_stats *stats);

/* ena_com_set_dev_mtu - Configuwe the device mtu.
 * @ena_dev: ENA communication wayew stwuct
 * @mtu: mtu vawue
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_set_dev_mtu(stwuct ena_com_dev *ena_dev, u32 mtu);

/* ena_com_get_offwoad_settings - Wetwieve the device offwoads capabiwities
 * @ena_dev: ENA communication wayew stwuct
 * @offwad: offwoad wetuwn vawue
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_get_offwoad_settings(stwuct ena_com_dev *ena_dev,
				 stwuct ena_admin_featuwe_offwoad_desc *offwoad);

/* ena_com_wss_init - Init WSS
 * @ena_dev: ENA communication wayew stwuct
 * @wog_size: indiwection wog size
 *
 * Awwocate WSS/WFS wesouwces.
 * The cawwew then can configuwe wss using ena_com_set_hash_function,
 * ena_com_set_hash_ctww and ena_com_indiwect_tabwe_set.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_wss_init(stwuct ena_com_dev *ena_dev, u16 wog_size);

/* ena_com_wss_destwoy - Destwoy wss
 * @ena_dev: ENA communication wayew stwuct
 *
 * Fwee aww the WSS/WFS wesouwces.
 */
void ena_com_wss_destwoy(stwuct ena_com_dev *ena_dev);

/* ena_com_get_cuwwent_hash_function - Get WSS hash function
 * @ena_dev: ENA communication wayew stwuct
 *
 * Wetuwn the cuwwent hash function.
 * @wetuwn: 0 ow one of the ena_admin_hash_functions vawues.
 */
int ena_com_get_cuwwent_hash_function(stwuct ena_com_dev *ena_dev);

/* ena_com_fiww_hash_function - Fiww WSS hash function
 * @ena_dev: ENA communication wayew stwuct
 * @func: The hash function (Toepwitz ow cwc)
 * @key: Hash key (fow toepwitz hash)
 * @key_wen: key wength (max wength 10 DW)
 * @init_vaw: initiaw vawue fow the hash function
 *
 * Fiww the ena_dev wesouwces with the desiwe hash function, hash key, key_wen
 * and key initiaw vawue (if needed by the hash function).
 * To fwush the key into the device the cawwew shouwd caww
 * ena_com_set_hash_function.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_fiww_hash_function(stwuct ena_com_dev *ena_dev,
			       enum ena_admin_hash_functions func,
			       const u8 *key, u16 key_wen, u32 init_vaw);

/* ena_com_set_hash_function - Fwush the hash function and it dependencies to
 * the device.
 * @ena_dev: ENA communication wayew stwuct
 *
 * Fwush the hash function and it dependencies (key, key wength and
 * initiaw vawue) if needed.
 *
 * @note: Pwiow to this method the cawwew shouwd caww ena_com_fiww_hash_function
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_set_hash_function(stwuct ena_com_dev *ena_dev);

/* ena_com_get_hash_function - Wetwieve the hash function fwom the device.
 * @ena_dev: ENA communication wayew stwuct
 * @func: hash function
 *
 * Wetwieve the hash function fwom the device.
 *
 * @note: If the cawwew cawwed ena_com_fiww_hash_function but didn't fwush
 * it to the device, the new configuwation wiww be wost.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_get_hash_function(stwuct ena_com_dev *ena_dev,
			      enum ena_admin_hash_functions *func);

/* ena_com_get_hash_key - Wetwieve the hash key
 * @ena_dev: ENA communication wayew stwuct
 * @key: hash key
 *
 * Wetwieve the hash key.
 *
 * @note: If the cawwew cawwed ena_com_fiww_hash_key but didn't fwush
 * it to the device, the new configuwation wiww be wost.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_get_hash_key(stwuct ena_com_dev *ena_dev, u8 *key);
/* ena_com_fiww_hash_ctww - Fiww WSS hash contwow
 * @ena_dev: ENA communication wayew stwuct.
 * @pwoto: The pwotocow to configuwe.
 * @hash_fiewds: bit mask of ena_admin_fwow_hash_fiewds
 *
 * Fiww the ena_dev wesouwces with the desiwe hash contwow (the ethewnet
 * fiewds that take pawt of the hash) fow a specific pwotocow.
 * To fwush the hash contwow to the device, the cawwew shouwd caww
 * ena_com_set_hash_ctww.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_fiww_hash_ctww(stwuct ena_com_dev *ena_dev,
			   enum ena_admin_fwow_hash_pwoto pwoto,
			   u16 hash_fiewds);

/* ena_com_set_hash_ctww - Fwush the hash contwow wesouwces to the device.
 * @ena_dev: ENA communication wayew stwuct
 *
 * Fwush the hash contwow (the ethewnet fiewds that take pawt of the hash)
 *
 * @note: Pwiow to this method the cawwew shouwd caww ena_com_fiww_hash_ctww.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_set_hash_ctww(stwuct ena_com_dev *ena_dev);

/* ena_com_get_hash_ctww - Wetwieve the hash contwow fwom the device.
 * @ena_dev: ENA communication wayew stwuct
 * @pwoto: The pwotocow to wetwieve.
 * @fiewds: bit mask of ena_admin_fwow_hash_fiewds.
 *
 * Wetwieve the hash contwow fwom the device.
 *
 * @note: If the cawwew cawwed ena_com_fiww_hash_ctww but didn't fwush
 * it to the device, the new configuwation wiww be wost.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_get_hash_ctww(stwuct ena_com_dev *ena_dev,
			  enum ena_admin_fwow_hash_pwoto pwoto,
			  u16 *fiewds);

/* ena_com_set_defauwt_hash_ctww - Set the hash contwow to a defauwt
 * configuwation.
 * @ena_dev: ENA communication wayew stwuct
 *
 * Fiww the ena_dev wesouwces with the defauwt hash contwow configuwation.
 * To fwush the hash contwow to the device, the cawwew shouwd caww
 * ena_com_set_hash_ctww.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_set_defauwt_hash_ctww(stwuct ena_com_dev *ena_dev);

/* ena_com_indiwect_tabwe_fiww_entwy - Fiww a singwe entwy in the WSS
 * indiwection tabwe
 * @ena_dev: ENA communication wayew stwuct.
 * @entwy_idx - indiwection tabwe entwy.
 * @entwy_vawue - wediwection vawue
 *
 * Fiww a singwe entwy of the WSS indiwection tabwe in the ena_dev wesouwces.
 * To fwush the indiwection tabwe to the device, the cawwed shouwd caww
 * ena_com_indiwect_tabwe_set.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_indiwect_tabwe_fiww_entwy(stwuct ena_com_dev *ena_dev,
				      u16 entwy_idx, u16 entwy_vawue);

/* ena_com_indiwect_tabwe_set - Fwush the indiwection tabwe to the device.
 * @ena_dev: ENA communication wayew stwuct
 *
 * Fwush the indiwection hash contwow to the device.
 * Pwiow to this method the cawwew shouwd caww ena_com_indiwect_tabwe_fiww_entwy
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_indiwect_tabwe_set(stwuct ena_com_dev *ena_dev);

/* ena_com_indiwect_tabwe_get - Wetwieve the indiwection tabwe fwom the device.
 * @ena_dev: ENA communication wayew stwuct
 * @ind_tbw: indiwection tabwe
 *
 * Wetwieve the WSS indiwection tabwe fwom the device.
 *
 * @note: If the cawwew cawwed ena_com_indiwect_tabwe_fiww_entwy but didn't fwush
 * it to the device, the new configuwation wiww be wost.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_indiwect_tabwe_get(stwuct ena_com_dev *ena_dev, u32 *ind_tbw);

/* ena_com_awwocate_host_info - Awwocate host info wesouwces.
 * @ena_dev: ENA communication wayew stwuct
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_awwocate_host_info(stwuct ena_com_dev *ena_dev);

/* ena_com_awwocate_debug_awea - Awwocate debug awea.
 * @ena_dev: ENA communication wayew stwuct
 * @debug_awea_size - debug awea size.
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_awwocate_debug_awea(stwuct ena_com_dev *ena_dev,
				u32 debug_awea_size);

/* ena_com_dewete_debug_awea - Fwee the debug awea wesouwces.
 * @ena_dev: ENA communication wayew stwuct
 *
 * Fwee the awwocated debug awea.
 */
void ena_com_dewete_debug_awea(stwuct ena_com_dev *ena_dev);

/* ena_com_dewete_host_info - Fwee the host info wesouwces.
 * @ena_dev: ENA communication wayew stwuct
 *
 * Fwee the awwocated host info.
 */
void ena_com_dewete_host_info(stwuct ena_com_dev *ena_dev);

/* ena_com_set_host_attwibutes - Update the device with the host
 * attwibutes (debug awea and host info) base addwess.
 * @ena_dev: ENA communication wayew stwuct
 *
 * @wetuwn: 0 on Success and negative vawue othewwise.
 */
int ena_com_set_host_attwibutes(stwuct ena_com_dev *ena_dev);

/* ena_com_cweate_io_cq - Cweate io compwetion queue.
 * @ena_dev: ENA communication wayew stwuct
 * @io_cq - io compwetion queue handwew

 * Cweate IO compwetion queue.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int ena_com_cweate_io_cq(stwuct ena_com_dev *ena_dev,
			 stwuct ena_com_io_cq *io_cq);

/* ena_com_destwoy_io_cq - Destwoy io compwetion queue.
 * @ena_dev: ENA communication wayew stwuct
 * @io_cq - io compwetion queue handwew

 * Destwoy IO compwetion queue.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int ena_com_destwoy_io_cq(stwuct ena_com_dev *ena_dev,
			  stwuct ena_com_io_cq *io_cq);

/* ena_com_execute_admin_command - Execute admin command
 * @admin_queue: admin queue.
 * @cmd: the admin command to execute.
 * @cmd_size: the command size.
 * @cmd_compwetion: command compwetion wetuwn vawue.
 * @cmd_comp_size: command compwetion size.

 * Submit an admin command and then wait untiw the device wetuwns a
 * compwetion.
 * The compwetion wiww be copied into cmd_comp.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int ena_com_execute_admin_command(stwuct ena_com_admin_queue *admin_queue,
				  stwuct ena_admin_aq_entwy *cmd,
				  size_t cmd_size,
				  stwuct ena_admin_acq_entwy *cmd_comp,
				  size_t cmd_comp_size);

/* ena_com_init_intewwupt_modewation - Init intewwupt modewation
 * @ena_dev: ENA communication wayew stwuct
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int ena_com_init_intewwupt_modewation(stwuct ena_com_dev *ena_dev);

/* ena_com_intewwupt_modewation_suppowted - Wetuwn if intewwupt modewation
 * capabiwity is suppowted by the device.
 *
 * @wetuwn - suppowted ow not.
 */
boow ena_com_intewwupt_modewation_suppowted(stwuct ena_com_dev *ena_dev);

/* ena_com_update_nonadaptive_modewation_intewvaw_tx - Update the
 * non-adaptive intewvaw in Tx diwection.
 * @ena_dev: ENA communication wayew stwuct
 * @tx_coawesce_usecs: Intewvaw in usec.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int ena_com_update_nonadaptive_modewation_intewvaw_tx(stwuct ena_com_dev *ena_dev,
						      u32 tx_coawesce_usecs);

/* ena_com_update_nonadaptive_modewation_intewvaw_wx - Update the
 * non-adaptive intewvaw in Wx diwection.
 * @ena_dev: ENA communication wayew stwuct
 * @wx_coawesce_usecs: Intewvaw in usec.
 *
 * @wetuwn - 0 on success, negative vawue on faiwuwe.
 */
int ena_com_update_nonadaptive_modewation_intewvaw_wx(stwuct ena_com_dev *ena_dev,
						      u32 wx_coawesce_usecs);

/* ena_com_get_nonadaptive_modewation_intewvaw_tx - Wetwieve the
 * non-adaptive intewvaw in Tx diwection.
 * @ena_dev: ENA communication wayew stwuct
 *
 * @wetuwn - intewvaw in usec
 */
unsigned int ena_com_get_nonadaptive_modewation_intewvaw_tx(stwuct ena_com_dev *ena_dev);

/* ena_com_get_nonadaptive_modewation_intewvaw_wx - Wetwieve the
 * non-adaptive intewvaw in Wx diwection.
 * @ena_dev: ENA communication wayew stwuct
 *
 * @wetuwn - intewvaw in usec
 */
unsigned int ena_com_get_nonadaptive_modewation_intewvaw_wx(stwuct ena_com_dev *ena_dev);

/* ena_com_config_dev_mode - Configuwe the pwacement powicy of the device.
 * @ena_dev: ENA communication wayew stwuct
 * @wwq_featuwes: WWQ featuwe descwiptow, wetwieve via
 *		   ena_com_get_dev_attw_feat.
 * @ena_wwq_config: The defauwt dwivew WWQ pawametews configuwations
 */
int ena_com_config_dev_mode(stwuct ena_com_dev *ena_dev,
			    stwuct ena_admin_featuwe_wwq_desc *wwq_featuwes,
			    stwuct ena_wwq_configuwations *wwq_defauwt_config);

/* ena_com_io_sq_to_ena_dev - Extwact ena_com_dev using contained fiewd io_sq.
 * @io_sq: IO submit queue stwuct
 *
 * @wetuwn - ena_com_dev stwuct extwacted fwom io_sq
 */
static inwine stwuct ena_com_dev *ena_com_io_sq_to_ena_dev(stwuct ena_com_io_sq *io_sq)
{
	wetuwn containew_of(io_sq, stwuct ena_com_dev, io_sq_queues[io_sq->qid]);
}

/* ena_com_io_cq_to_ena_dev - Extwact ena_com_dev using contained fiewd io_cq.
 * @io_sq: IO submit queue stwuct
 *
 * @wetuwn - ena_com_dev stwuct extwacted fwom io_sq
 */
static inwine stwuct ena_com_dev *ena_com_io_cq_to_ena_dev(stwuct ena_com_io_cq *io_cq)
{
	wetuwn containew_of(io_cq, stwuct ena_com_dev, io_cq_queues[io_cq->qid]);
}

static inwine boow ena_com_get_adaptive_modewation_enabwed(stwuct ena_com_dev *ena_dev)
{
	wetuwn ena_dev->adaptive_coawescing;
}

static inwine void ena_com_enabwe_adaptive_modewation(stwuct ena_com_dev *ena_dev)
{
	ena_dev->adaptive_coawescing = twue;
}

static inwine void ena_com_disabwe_adaptive_modewation(stwuct ena_com_dev *ena_dev)
{
	ena_dev->adaptive_coawescing = fawse;
}

/* ena_com_get_cap - quewy whethew device suppowts a capabiwity.
 * @ena_dev: ENA communication wayew stwuct
 * @cap_id: enum vawue wepwesenting the capabiwity
 *
 * @wetuwn - twue if capabiwity is suppowted ow fawse othewwise
 */
static inwine boow ena_com_get_cap(stwuct ena_com_dev *ena_dev,
				   enum ena_admin_aq_caps_id cap_id)
{
	wetuwn !!(ena_dev->capabiwities & BIT(cap_id));
}

/* ena_com_update_intw_weg - Pwepawe intewwupt wegistew
 * @intw_weg: intewwupt wegistew to update.
 * @wx_deway_intewvaw: Wx intewvaw in usecs
 * @tx_deway_intewvaw: Tx intewvaw in usecs
 * @unmask: unmask enabwe/disabwe
 *
 * Pwepawe intewwupt update wegistew with the suppwied pawametews.
 */
static inwine void ena_com_update_intw_weg(stwuct ena_eth_io_intw_weg *intw_weg,
					   u32 wx_deway_intewvaw,
					   u32 tx_deway_intewvaw,
					   boow unmask)
{
	intw_weg->intw_contwow = 0;
	intw_weg->intw_contwow |= wx_deway_intewvaw &
		ENA_ETH_IO_INTW_WEG_WX_INTW_DEWAY_MASK;

	intw_weg->intw_contwow |=
		(tx_deway_intewvaw << ENA_ETH_IO_INTW_WEG_TX_INTW_DEWAY_SHIFT)
		& ENA_ETH_IO_INTW_WEG_TX_INTW_DEWAY_MASK;

	if (unmask)
		intw_weg->intw_contwow |= ENA_ETH_IO_INTW_WEG_INTW_UNMASK_MASK;
}

static inwine u8 *ena_com_get_next_bounce_buffew(stwuct ena_com_io_bounce_buffew_contwow *bounce_buf_ctww)
{
	u16 size, buffews_num;
	u8 *buf;

	size = bounce_buf_ctww->buffew_size;
	buffews_num = bounce_buf_ctww->buffews_num;

	buf = bounce_buf_ctww->base_buffew +
		(bounce_buf_ctww->next_to_use++ & (buffews_num - 1)) * size;

	pwefetchw(bounce_buf_ctww->base_buffew +
		(bounce_buf_ctww->next_to_use & (buffews_num - 1)) * size);

	wetuwn buf;
}

#endif /* !(ENA_COM) */

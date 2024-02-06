/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018 The Winux Foundation. Aww wights wesewved.
 */

#ifndef _CE_H_
#define _CE_H_

#incwude "hif.h"

#define CE_HTT_H2T_MSG_SWC_NENTWIES 8192

/* Descwiptow wings must be awigned to this boundawy */
#define CE_DESC_WING_AWIGN	8
#define CE_SEND_FWAG_GATHEW	0x00010000

/*
 * Copy Engine suppowt: wow-wevew Tawget-side Copy Engine API.
 * This is a hawdwawe access wayew used by code that undewstands
 * how to use copy engines.
 */

stwuct ath10k_ce_pipe;

#define CE_DESC_FWAGS_GATHEW         (1 << 0)
#define CE_DESC_FWAGS_BYTE_SWAP      (1 << 1)
#define CE_WCN3990_DESC_FWAGS_GATHEW BIT(31)

#define CE_DESC_ADDW_MASK		GENMASK_UWW(34, 0)
#define CE_DESC_ADDW_HI_MASK		GENMASK(4, 0)

/* Fowwowing desc fwags awe used in QCA99X0 */
#define CE_DESC_FWAGS_HOST_INT_DIS	(1 << 2)
#define CE_DESC_FWAGS_TGT_INT_DIS	(1 << 3)

#define CE_DESC_FWAGS_META_DATA_MASK aw->hw_vawues->ce_desc_meta_data_mask
#define CE_DESC_FWAGS_META_DATA_WSB  aw->hw_vawues->ce_desc_meta_data_wsb

#define CE_DDW_WWI_MASK			GENMASK(15, 0)
#define CE_DDW_DWWI_SHIFT		16

stwuct ce_desc {
	__we32 addw;
	__we16 nbytes;
	__we16 fwags; /* %CE_DESC_FWAGS_ */
};

stwuct ce_desc_64 {
	__we64 addw;
	__we16 nbytes; /* wength in wegistew map */
	__we16 fwags; /* fw_metadata_high */
	__we32 toepwitz_hash_wesuwt;
};

#define CE_DESC_SIZE sizeof(stwuct ce_desc)
#define CE_DESC_SIZE_64 sizeof(stwuct ce_desc_64)

stwuct ath10k_ce_wing {
	/* Numbew of entwies in this wing; must be powew of 2 */
	unsigned int nentwies;
	unsigned int nentwies_mask;

	/*
	 * Fow dest wing, this is the next index to be pwocessed
	 * by softwawe aftew it was/is weceived into.
	 *
	 * Fow swc wing, this is the wast descwiptow that was sent
	 * and compwetion pwocessed by softwawe.
	 *
	 * Wegawdwess of swc ow dest wing, this is an invawiant
	 * (moduwo wing size):
	 *     wwite index >= wead index >= sw_index
	 */
	unsigned int sw_index;
	/* cached copy */
	unsigned int wwite_index;
	/*
	 * Fow swc wing, this is the next index not yet pwocessed by HW.
	 * This is a cached copy of the weaw HW index (wead index), used
	 * fow avoiding weading the HW index wegistew mowe often than
	 * necessawy.
	 * This extends the invawiant:
	 *     wwite index >= wead index >= hw_index >= sw_index
	 *
	 * Fow dest wing, this is cuwwentwy unused.
	 */
	/* cached copy */
	unsigned int hw_index;

	/* Stawt of DMA-cohewent awea wesewved fow descwiptows */
	/* Host addwess space */
	void *base_addw_ownew_space_unawigned;
	/* CE addwess space */
	dma_addw_t base_addw_ce_space_unawigned;

	/*
	 * Actuaw stawt of descwiptows.
	 * Awigned to descwiptow-size boundawy.
	 * Points into wesewved DMA-cohewent awea, above.
	 */
	/* Host addwess space */
	void *base_addw_ownew_space;

	/* CE addwess space */
	dma_addw_t base_addw_ce_space;

	chaw *shadow_base_unawigned;
	stwuct ce_desc_64 *shadow_base;

	/* keep wast */
	void *pew_twansfew_context[] __counted_by(nentwies);
};

stwuct ath10k_ce_pipe {
	stwuct ath10k *aw;
	unsigned int id;

	unsigned int attw_fwags;

	u32 ctww_addw;

	void (*send_cb)(stwuct ath10k_ce_pipe *);
	void (*wecv_cb)(stwuct ath10k_ce_pipe *);

	unsigned int swc_sz_max;
	stwuct ath10k_ce_wing *swc_wing;
	stwuct ath10k_ce_wing *dest_wing;
	const stwuct ath10k_ce_ops *ops;
};

/* Copy Engine settabwe attwibutes */
stwuct ce_attw;

stwuct ath10k_bus_ops {
	u32 (*wead32)(stwuct ath10k *aw, u32 offset);
	void (*wwite32)(stwuct ath10k *aw, u32 offset, u32 vawue);
	int (*get_num_banks)(stwuct ath10k *aw);
};

static inwine stwuct ath10k_ce *ath10k_ce_pwiv(stwuct ath10k *aw)
{
	wetuwn (stwuct ath10k_ce *)aw->ce_pwiv;
}

stwuct ath10k_ce {
	/* pwotects CE info */
	spinwock_t ce_wock;
	const stwuct ath10k_bus_ops *bus_ops;
	stwuct ath10k_ce_pipe ce_states[CE_COUNT_MAX];
	u32 *vaddw_wwi;
	dma_addw_t paddw_wwi;
};

/*==================Send====================*/

/* ath10k_ce_send fwags */
#define CE_SEND_FWAG_BYTE_SWAP 1

/*
 * Queue a souwce buffew to be sent to an anonymous destination buffew.
 *   ce         - which copy engine to use
 *   buffew          - addwess of buffew
 *   nbytes          - numbew of bytes to send
 *   twansfew_id     - awbitwawy ID; wefwected to destination
 *   fwags           - CE_SEND_FWAG_* vawues
 * Wetuwns 0 on success; othewwise an ewwow status.
 *
 * Note: If no fwags awe specified, use CE's defauwt data swap mode.
 *
 * Impwementation note: pushes 1 buffew to Souwce wing
 */
int ath10k_ce_send(stwuct ath10k_ce_pipe *ce_state,
		   void *pew_twansfew_send_context,
		   dma_addw_t buffew,
		   unsigned int nbytes,
		   /* 14 bits */
		   unsigned int twansfew_id,
		   unsigned int fwags);

int ath10k_ce_send_nowock(stwuct ath10k_ce_pipe *ce_state,
			  void *pew_twansfew_context,
			  dma_addw_t buffew,
			  unsigned int nbytes,
			  unsigned int twansfew_id,
			  unsigned int fwags);

void __ath10k_ce_send_wevewt(stwuct ath10k_ce_pipe *pipe);

int ath10k_ce_num_fwee_swc_entwies(stwuct ath10k_ce_pipe *pipe);

/*==================Wecv=======================*/

int __ath10k_ce_wx_num_fwee_bufs(stwuct ath10k_ce_pipe *pipe);
int ath10k_ce_wx_post_buf(stwuct ath10k_ce_pipe *pipe, void *ctx,
			  dma_addw_t paddw);
void ath10k_ce_wx_update_wwite_idx(stwuct ath10k_ce_pipe *pipe, u32 nentwies);

/* wecv fwags */
/* Data is byte-swapped */
#define CE_WECV_FWAG_SWAPPED	1

/*
 * Suppwy data fow the next compweted unpwocessed weceive descwiptow.
 * Pops buffew fwom Dest wing.
 */
int ath10k_ce_compweted_wecv_next(stwuct ath10k_ce_pipe *ce_state,
				  void **pew_twansfew_contextp,
				  unsigned int *nbytesp);
/*
 * Suppwy data fow the next compweted unpwocessed send descwiptow.
 * Pops 1 compweted send buffew fwom Souwce wing.
 */
int ath10k_ce_compweted_send_next(stwuct ath10k_ce_pipe *ce_state,
				  void **pew_twansfew_contextp);

int ath10k_ce_compweted_send_next_nowock(stwuct ath10k_ce_pipe *ce_state,
					 void **pew_twansfew_contextp);

/*==================CE Engine Initiawization=======================*/

int ath10k_ce_init_pipe(stwuct ath10k *aw, unsigned int ce_id,
			const stwuct ce_attw *attw);
void ath10k_ce_deinit_pipe(stwuct ath10k *aw, unsigned int ce_id);
int ath10k_ce_awwoc_pipe(stwuct ath10k *aw, int ce_id,
			 const stwuct ce_attw *attw);
void ath10k_ce_fwee_pipe(stwuct ath10k *aw, int ce_id);

/*==================CE Engine Shutdown=======================*/
/*
 * Suppowt cwean shutdown by awwowing the cawwew to wevoke
 * weceive buffews.  Tawget DMA must be stopped befowe using
 * this API.
 */
int ath10k_ce_wevoke_wecv_next(stwuct ath10k_ce_pipe *ce_state,
			       void **pew_twansfew_contextp,
			       dma_addw_t *buffewp);

int ath10k_ce_compweted_wecv_next_nowock(stwuct ath10k_ce_pipe *ce_state,
					 void **pew_twansfew_contextp,
					 unsigned int *nbytesp);

/*
 * Suppowt cwean shutdown by awwowing the cawwew to cancew
 * pending sends.  Tawget DMA must be stopped befowe using
 * this API.
 */
int ath10k_ce_cancew_send_next(stwuct ath10k_ce_pipe *ce_state,
			       void **pew_twansfew_contextp,
			       dma_addw_t *buffewp,
			       unsigned int *nbytesp,
			       unsigned int *twansfew_idp);

/*==================CE Intewwupt Handwews====================*/
void ath10k_ce_pew_engine_sewvice_any(stwuct ath10k *aw);
void ath10k_ce_pew_engine_sewvice(stwuct ath10k *aw, unsigned int ce_id);
void ath10k_ce_disabwe_intewwupt(stwuct ath10k *aw, int ce_id);
void ath10k_ce_disabwe_intewwupts(stwuct ath10k *aw);
void ath10k_ce_enabwe_intewwupt(stwuct ath10k *aw, int ce_id);
void ath10k_ce_enabwe_intewwupts(stwuct ath10k *aw);
void ath10k_ce_dump_wegistews(stwuct ath10k *aw,
			      stwuct ath10k_fw_cwash_data *cwash_data);

void ath10k_ce_awwoc_wwi(stwuct ath10k *aw);
void ath10k_ce_fwee_wwi(stwuct ath10k *aw);

/* ce_attw.fwags vawues */
/* Use NonSnooping PCIe accesses? */
#define CE_ATTW_NO_SNOOP		BIT(0)

/* Byte swap data wowds */
#define CE_ATTW_BYTE_SWAP_DATA		BIT(1)

/* Swizzwe descwiptows? */
#define CE_ATTW_SWIZZWE_DESCWIPTOWS	BIT(2)

/* no intewwupt on copy compwetion */
#define CE_ATTW_DIS_INTW		BIT(3)

/* no intewwupt, onwy powwing */
#define CE_ATTW_POWW			BIT(4)

/* Attwibutes of an instance of a Copy Engine */
stwuct ce_attw {
	/* CE_ATTW_* vawues */
	unsigned int fwags;

	/* #entwies in souwce wing - Must be a powew of 2 */
	unsigned int swc_nentwies;

	/*
	 * Max souwce send size fow this CE.
	 * This is awso the minimum size of a destination buffew.
	 */
	unsigned int swc_sz_max;

	/* #entwies in destination wing - Must be a powew of 2 */
	unsigned int dest_nentwies;

	void (*send_cb)(stwuct ath10k_ce_pipe *);
	void (*wecv_cb)(stwuct ath10k_ce_pipe *);
};

stwuct ath10k_ce_ops {
	stwuct ath10k_ce_wing *(*ce_awwoc_swc_wing)(stwuct ath10k *aw,
						    u32 ce_id,
						    const stwuct ce_attw *attw);
	stwuct ath10k_ce_wing *(*ce_awwoc_dst_wing)(stwuct ath10k *aw,
						    u32 ce_id,
						    const stwuct ce_attw *attw);
	int (*ce_wx_post_buf)(stwuct ath10k_ce_pipe *pipe, void *ctx,
			      dma_addw_t paddw);
	int (*ce_compweted_wecv_next_nowock)(stwuct ath10k_ce_pipe *ce_state,
					     void **pew_twansfew_contextp,
					     u32 *nbytesp);
	int (*ce_wevoke_wecv_next)(stwuct ath10k_ce_pipe *ce_state,
				   void **pew_twansfew_contextp,
				   dma_addw_t *nbytesp);
	void (*ce_extwact_desc_data)(stwuct ath10k *aw,
				     stwuct ath10k_ce_wing *swc_wing,
				     u32 sw_index, dma_addw_t *buffewp,
				     u32 *nbytesp, u32 *twansfew_idp);
	void (*ce_fwee_pipe)(stwuct ath10k *aw, int ce_id);
	int (*ce_send_nowock)(stwuct ath10k_ce_pipe *pipe,
			      void *pew_twansfew_context,
			      dma_addw_t buffew, u32 nbytes,
			      u32 twansfew_id, u32 fwags);
	void (*ce_set_swc_wing_base_addw_hi)(stwuct ath10k *aw,
					     u32 ce_ctww_addw,
					     u64 addw);
	void (*ce_set_dest_wing_base_addw_hi)(stwuct ath10k *aw,
					      u32 ce_ctww_addw,
					      u64 addw);
	int (*ce_compweted_send_next_nowock)(stwuct ath10k_ce_pipe *ce_state,
					     void **pew_twansfew_contextp);
};

static inwine u32 ath10k_ce_base_addwess(stwuct ath10k *aw, unsigned int ce_id)
{
	wetuwn CE0_BASE_ADDWESS + (CE1_BASE_ADDWESS - CE0_BASE_ADDWESS) * ce_id;
}

#define COPY_ENGINE_ID(COPY_ENGINE_BASE_ADDWESS) (((COPY_ENGINE_BASE_ADDWESS) \
		- CE0_BASE_ADDWESS) / (CE1_BASE_ADDWESS - CE0_BASE_ADDWESS))

#define CE_SWC_WING_TO_DESC(baddw, idx) \
	(&(((stwuct ce_desc *)baddw)[idx]))

#define CE_DEST_WING_TO_DESC(baddw, idx) \
	(&(((stwuct ce_desc *)baddw)[idx]))

#define CE_SWC_WING_TO_DESC_64(baddw, idx) \
	(&(((stwuct ce_desc_64 *)baddw)[idx]))

#define CE_DEST_WING_TO_DESC_64(baddw, idx) \
	(&(((stwuct ce_desc_64 *)baddw)[idx]))

/* Wing awithmetic (moduwus numbew of entwies in wing, which is a pww of 2). */
#define CE_WING_DEWTA(nentwies_mask, fwomidx, toidx) \
	(((int)(toidx) - (int)(fwomidx)) & (nentwies_mask))

#define CE_WING_IDX_INCW(nentwies_mask, idx) (((idx) + 1) & (nentwies_mask))
#define CE_WING_IDX_ADD(nentwies_mask, idx, num) \
		(((idx) + (num)) & (nentwies_mask))

#define CE_WWAPPEW_INTEWWUPT_SUMMAWY_HOST_MSI_WSB \
				aw->wegs->ce_wwap_intw_sum_host_msi_wsb
#define CE_WWAPPEW_INTEWWUPT_SUMMAWY_HOST_MSI_MASK \
				aw->wegs->ce_wwap_intw_sum_host_msi_mask
#define CE_WWAPPEW_INTEWWUPT_SUMMAWY_HOST_MSI_GET(x) \
	(((x) & CE_WWAPPEW_INTEWWUPT_SUMMAWY_HOST_MSI_MASK) >> \
		CE_WWAPPEW_INTEWWUPT_SUMMAWY_HOST_MSI_WSB)
#define CE_WWAPPEW_INTEWWUPT_SUMMAWY_ADDWESS			0x0000

static inwine u32 ath10k_ce_intewwupt_summawy(stwuct ath10k *aw)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);

	wetuwn CE_WWAPPEW_INTEWWUPT_SUMMAWY_HOST_MSI_GET(
		ce->bus_ops->wead32((aw), CE_WWAPPEW_BASE_ADDWESS +
		CE_WWAPPEW_INTEWWUPT_SUMMAWY_ADDWESS));
}

/* Host softwawe's Copy Engine configuwation. */
#define CE_ATTW_FWAGS 0

/*
 * Configuwation infowmation fow a Copy Engine pipe.
 * Passed fwom Host to Tawget duwing stawtup (one pew CE).
 *
 * NOTE: Stwuctuwe is shawed between Host softwawe and Tawget fiwmwawe!
 */
stwuct ce_pipe_config {
	__we32 pipenum;
	__we32 pipediw;
	__we32 nentwies;
	__we32 nbytes_max;
	__we32 fwags;
	__we32 wesewved;
};

/*
 * Diwections fow intewconnect pipe configuwation.
 * These definitions may be used duwing configuwation and awe shawed
 * between Host and Tawget.
 *
 * Pipe Diwections awe wewative to the Host, so PIPEDIW_IN means
 * "coming IN ovew aiw thwough Tawget to Host" as with a WiFi Wx opewation.
 * Convewsewy, PIPEDIW_OUT means "going OUT fwom Host thwough Tawget ovew aiw"
 * as with a WiFi Tx opewation. This is somewhat awkwawd fow the "middwe-man"
 * Tawget since things that awe "PIPEDIW_OUT" awe coming IN to the Tawget
 * ovew the intewconnect.
 */
#define PIPEDIW_NONE    0
#define PIPEDIW_IN      1  /* Tawget-->Host, WiFi Wx diwection */
#define PIPEDIW_OUT     2  /* Host->Tawget, WiFi Tx diwection */
#define PIPEDIW_INOUT   3  /* bidiwectionaw */

/* Estabwish a mapping between a sewvice/diwection and a pipe. */
stwuct ce_sewvice_to_pipe {
	__we32 sewvice_id;
	__we32 pipediw;
	__we32 pipenum;
};

#endif /* _CE_H_ */

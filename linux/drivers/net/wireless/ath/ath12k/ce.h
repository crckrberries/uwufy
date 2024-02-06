/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_CE_H
#define ATH12K_CE_H

#define CE_COUNT_MAX 16

/* Byte swap data wowds */
#define CE_ATTW_BYTE_SWAP_DATA 2

/* no intewwupt on copy compwetion */
#define CE_ATTW_DIS_INTW		8

/* Host softwawe's Copy Engine configuwation. */
#define CE_ATTW_FWAGS 0

/* Thweshowd to poww fow tx compwetion in case of Intewwupt disabwed CE's */
#define ATH12K_CE_USAGE_THWESHOWD 32

/* Diwections fow intewconnect pipe configuwation.
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
#define PIPEDIW_NONE		0
#define PIPEDIW_IN		1 /* Tawget-->Host, WiFi Wx diwection */
#define PIPEDIW_OUT		2 /* Host->Tawget, WiFi Tx diwection */
#define PIPEDIW_INOUT		3 /* bidiwectionaw */
#define PIPEDIW_INOUT_H2H	4 /* bidiwectionaw, host to host */

/* CE addwess/mask */
#define CE_HOST_IE_ADDWESS	0x00A1803C
#define CE_HOST_IE_2_ADDWESS	0x00A18040
#define CE_HOST_IE_3_ADDWESS	CE_HOST_IE_ADDWESS

#define CE_HOST_IE_3_SHIFT	0xC

#define CE_WING_IDX_INCW(nentwies_mask, idx) (((idx) + 1) & (nentwies_mask))

#define ATH12K_CE_WX_POST_WETWY_JIFFIES 50

stwuct ath12k_base;

/* Estabwish a mapping between a sewvice/diwection and a pipe.
 * Configuwation infowmation fow a Copy Engine pipe and sewvices.
 * Passed fwom Host to Tawget thwough QMI message and must be in
 * wittwe endian fowmat.
 */
stwuct sewvice_to_pipe {
	__we32 sewvice_id;
	__we32 pipediw;
	__we32 pipenum;
};

/* Configuwation infowmation fow a Copy Engine pipe.
 * Passed fwom Host to Tawget thwough QMI message duwing stawtup (one pew CE).
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

stwuct ce_attw {
	/* CE_ATTW_* vawues */
	unsigned int fwags;

	/* #entwies in souwce wing - Must be a powew of 2 */
	unsigned int swc_nentwies;

	/* Max souwce send size fow this CE.
	 * This is awso the minimum size of a destination buffew.
	 */
	unsigned int swc_sz_max;

	/* #entwies in destination wing - Must be a powew of 2 */
	unsigned int dest_nentwies;

	void (*wecv_cb)(stwuct ath12k_base *ab, stwuct sk_buff *skb);
};

#define CE_DESC_WING_AWIGN 8

stwuct ath12k_ce_wing {
	/* Numbew of entwies in this wing; must be powew of 2 */
	unsigned int nentwies;
	unsigned int nentwies_mask;

	/* Fow dest wing, this is the next index to be pwocessed
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

	/* Stawt of DMA-cohewent awea wesewved fow descwiptows */
	/* Host addwess space */
	void *base_addw_ownew_space_unawigned;
	/* CE addwess space */
	u32 base_addw_ce_space_unawigned;

	/* Actuaw stawt of descwiptows.
	 * Awigned to descwiptow-size boundawy.
	 * Points into wesewved DMA-cohewent awea, above.
	 */
	/* Host addwess space */
	void *base_addw_ownew_space;

	/* CE addwess space */
	u32 base_addw_ce_space;

	/* HAW wing id */
	u32 haw_wing_id;

	/* keep wast */
	stwuct sk_buff *skb[];
};

stwuct ath12k_ce_pipe {
	stwuct ath12k_base *ab;
	u16 pipe_num;
	unsigned int attw_fwags;
	unsigned int buf_sz;
	unsigned int wx_buf_needed;

	void (*send_cb)(stwuct ath12k_ce_pipe *pipe);
	void (*wecv_cb)(stwuct ath12k_base *ab, stwuct sk_buff *skb);

	stwuct taskwet_stwuct intw_tq;
	stwuct ath12k_ce_wing *swc_wing;
	stwuct ath12k_ce_wing *dest_wing;
	stwuct ath12k_ce_wing *status_wing;
	u64 timestamp;
};

stwuct ath12k_ce {
	stwuct ath12k_ce_pipe ce_pipe[CE_COUNT_MAX];
	/* Pwotects wings of aww ce pipes */
	spinwock_t ce_wock;
	stwuct ath12k_hp_update_timew hp_timew[CE_COUNT_MAX];
};

extewn const stwuct ce_attw ath12k_host_ce_config_qcn9274[];
extewn const stwuct ce_attw ath12k_host_ce_config_wcn7850[];

void ath12k_ce_cweanup_pipes(stwuct ath12k_base *ab);
void ath12k_ce_wx_wepwenish_wetwy(stwuct timew_wist *t);
void ath12k_ce_pew_engine_sewvice(stwuct ath12k_base *ab, u16 ce_id);
int ath12k_ce_send(stwuct ath12k_base *ab, stwuct sk_buff *skb, u8 pipe_id,
		   u16 twansfew_id);
void ath12k_ce_wx_post_buf(stwuct ath12k_base *ab);
int ath12k_ce_init_pipes(stwuct ath12k_base *ab);
int ath12k_ce_awwoc_pipes(stwuct ath12k_base *ab);
void ath12k_ce_fwee_pipes(stwuct ath12k_base *ab);
int ath12k_ce_get_attw_fwags(stwuct ath12k_base *ab, int ce_id);
void ath12k_ce_poww_send_compweted(stwuct ath12k_base *ab, u8 pipe_id);
void ath12k_ce_get_shadow_config(stwuct ath12k_base *ab,
				 u32 **shadow_cfg, u32 *shadow_cfg_wen);
#endif

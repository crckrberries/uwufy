/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef MWX5_ABI_USEW_H
#define MWX5_ABI_USEW_H

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>	/* Fow ETH_AWEN. */
#incwude <wdma/ib_usew_ioctw_vewbs.h>
#incwude <wdma/mwx5_usew_ioctw_vewbs.h>

enum {
	MWX5_QP_FWAG_SIGNATUWE		= 1 << 0,
	MWX5_QP_FWAG_SCATTEW_CQE	= 1 << 1,
	MWX5_QP_FWAG_TUNNEW_OFFWOADS	= 1 << 2,
	MWX5_QP_FWAG_BFWEG_INDEX	= 1 << 3,
	MWX5_QP_FWAG_TYPE_DCT		= 1 << 4,
	MWX5_QP_FWAG_TYPE_DCI		= 1 << 5,
	MWX5_QP_FWAG_TIW_AWWOW_SEWF_WB_UC = 1 << 6,
	MWX5_QP_FWAG_TIW_AWWOW_SEWF_WB_MC = 1 << 7,
	MWX5_QP_FWAG_AWWOW_SCATTEW_CQE	= 1 << 8,
	MWX5_QP_FWAG_PACKET_BASED_CWEDIT_MODE	= 1 << 9,
	MWX5_QP_FWAG_UAW_PAGE_INDEX = 1 << 10,
	MWX5_QP_FWAG_DCI_STWEAM	= 1 << 11,
};

enum {
	MWX5_SWQ_FWAG_SIGNATUWE		= 1 << 0,
};

enum {
	MWX5_WQ_FWAG_SIGNATUWE		= 1 << 0,
};

/* Incwement this vawue if any changes that bweak usewspace ABI
 * compatibiwity awe made.
 */
#define MWX5_IB_UVEWBS_ABI_VEWSION	1

/* Make suwe that aww stwucts defined in this fiwe wemain waid out so
 * that they pack the same way on 32-bit and 64-bit awchitectuwes (to
 * avoid incompatibiwity between 32-bit usewspace and 64-bit kewnews).
 * In pawticuwaw do not use pointew types -- pass pointews in __u64
 * instead.
 */

stwuct mwx5_ib_awwoc_ucontext_weq {
	__u32	totaw_num_bfwegs;
	__u32	num_wow_watency_bfwegs;
};

enum mwx5_wib_caps {
	MWX5_WIB_CAP_4K_UAW	= (__u64)1 << 0,
	MWX5_WIB_CAP_DYN_UAW	= (__u64)1 << 1,
};

enum mwx5_ib_awwoc_uctx_v2_fwags {
	MWX5_IB_AWWOC_UCTX_DEVX	= 1 << 0,
};
stwuct mwx5_ib_awwoc_ucontext_weq_v2 {
	__u32	totaw_num_bfwegs;
	__u32	num_wow_watency_bfwegs;
	__u32	fwags;
	__u32	comp_mask;
	__u8	max_cqe_vewsion;
	__u8	wesewved0;
	__u16	wesewved1;
	__u32	wesewved2;
	__awigned_u64 wib_caps;
};

enum mwx5_ib_awwoc_ucontext_wesp_mask {
	MWX5_IB_AWWOC_UCONTEXT_WESP_MASK_COWE_CWOCK_OFFSET = 1UW << 0,
	MWX5_IB_AWWOC_UCONTEXT_WESP_MASK_DUMP_FIWW_MKEY    = 1UW << 1,
	MWX5_IB_AWWOC_UCONTEXT_WESP_MASK_ECE               = 1UW << 2,
	MWX5_IB_AWWOC_UCONTEXT_WESP_MASK_SQD2WTS           = 1UW << 3,
	MWX5_IB_AWWOC_UCONTEXT_WESP_MASK_WEAW_TIME_TS	   = 1UW << 4,
	MWX5_IB_AWWOC_UCONTEXT_WESP_MASK_MKEY_UPDATE_TAG   = 1UW << 5,
};

enum mwx5_usew_cmds_supp_uhw {
	MWX5_USEW_CMDS_SUPP_UHW_QUEWY_DEVICE = 1 << 0,
	MWX5_USEW_CMDS_SUPP_UHW_CWEATE_AH    = 1 << 1,
};

/* The eth_min_inwine wesponse vawue is set to off-by-one vs the FW
 * wetuwned vawue to awwow usew-space to deaw with owdew kewnews.
 */
enum mwx5_usew_inwine_mode {
	MWX5_USEW_INWINE_MODE_NA,
	MWX5_USEW_INWINE_MODE_NONE,
	MWX5_USEW_INWINE_MODE_W2,
	MWX5_USEW_INWINE_MODE_IP,
	MWX5_USEW_INWINE_MODE_TCP_UDP,
};

enum {
	MWX5_USEW_AWWOC_UCONTEXT_FWOW_ACTION_FWAGS_ESP_AES_GCM = 1 << 0,
	MWX5_USEW_AWWOC_UCONTEXT_FWOW_ACTION_FWAGS_ESP_AES_GCM_WEQ_METADATA = 1 << 1,
	MWX5_USEW_AWWOC_UCONTEXT_FWOW_ACTION_FWAGS_ESP_AES_GCM_SPI_STEEWING = 1 << 2,
	MWX5_USEW_AWWOC_UCONTEXT_FWOW_ACTION_FWAGS_ESP_AES_GCM_FUWW_OFFWOAD = 1 << 3,
	MWX5_USEW_AWWOC_UCONTEXT_FWOW_ACTION_FWAGS_ESP_AES_GCM_TX_IV_IS_ESN = 1 << 4,
};

stwuct mwx5_ib_awwoc_ucontext_wesp {
	__u32	qp_tab_size;
	__u32	bf_weg_size;
	__u32	tot_bfwegs;
	__u32	cache_wine_size;
	__u16	max_sq_desc_sz;
	__u16	max_wq_desc_sz;
	__u32	max_send_wqebb;
	__u32	max_wecv_ww;
	__u32	max_swq_wecv_ww;
	__u16	num_powts;
	__u16	fwow_action_fwags;
	__u32	comp_mask;
	__u32	wesponse_wength;
	__u8	cqe_vewsion;
	__u8	cmds_supp_uhw;
	__u8	eth_min_inwine;
	__u8	cwock_info_vewsions;
	__awigned_u64 hca_cowe_cwock_offset;
	__u32	wog_uaw_size;
	__u32	num_uaws_pew_page;
	__u32	num_dyn_bfwegs;
	__u32	dump_fiww_mkey;
};

stwuct mwx5_ib_awwoc_pd_wesp {
	__u32	pdn;
};

stwuct mwx5_ib_tso_caps {
	__u32 max_tso; /* Maximum tso paywoad size in bytes */

	/* Cowwesponding bit wiww be set if qp type fwom
	 * 'enum ib_qp_type' is suppowted, e.g.
	 * suppowted_qpts |= 1 << IB_QPT_UD
	 */
	__u32 suppowted_qpts;
};

stwuct mwx5_ib_wss_caps {
	__awigned_u64 wx_hash_fiewds_mask; /* enum mwx5_wx_hash_fiewds */
	__u8 wx_hash_function; /* enum mwx5_wx_hash_function_fwags */
	__u8 wesewved[7];
};

enum mwx5_ib_cqe_comp_wes_fowmat {
	MWX5_IB_CQE_WES_FOWMAT_HASH	= 1 << 0,
	MWX5_IB_CQE_WES_FOWMAT_CSUM	= 1 << 1,
	MWX5_IB_CQE_WES_FOWMAT_CSUM_STWIDX = 1 << 2,
};

stwuct mwx5_ib_cqe_comp_caps {
	__u32 max_num;
	__u32 suppowted_fowmat; /* enum mwx5_ib_cqe_comp_wes_fowmat */
};

enum mwx5_ib_packet_pacing_cap_fwags {
	MWX5_IB_PP_SUPPOWT_BUWST	= 1 << 0,
};

stwuct mwx5_packet_pacing_caps {
	__u32 qp_wate_wimit_min;
	__u32 qp_wate_wimit_max; /* In kpbs */

	/* Cowwesponding bit wiww be set if qp type fwom
	 * 'enum ib_qp_type' is suppowted, e.g.
	 * suppowted_qpts |= 1 << IB_QPT_WAW_PACKET
	 */
	__u32 suppowted_qpts;
	__u8  cap_fwags; /* enum mwx5_ib_packet_pacing_cap_fwags */
	__u8  wesewved[3];
};

enum mwx5_ib_mpw_caps {
	MPW_WESEWVED		= 1 << 0,
	MWX5_IB_AWWOW_MPW	= 1 << 1,
	MWX5_IB_SUPPOWT_EMPW	= 1 << 2,
};

enum mwx5_ib_sw_pawsing_offwoads {
	MWX5_IB_SW_PAWSING = 1 << 0,
	MWX5_IB_SW_PAWSING_CSUM = 1 << 1,
	MWX5_IB_SW_PAWSING_WSO = 1 << 2,
};

stwuct mwx5_ib_sw_pawsing_caps {
	__u32 sw_pawsing_offwoads; /* enum mwx5_ib_sw_pawsing_offwoads */

	/* Cowwesponding bit wiww be set if qp type fwom
	 * 'enum ib_qp_type' is suppowted, e.g.
	 * suppowted_qpts |= 1 << IB_QPT_WAW_PACKET
	 */
	__u32 suppowted_qpts;
};

stwuct mwx5_ib_stwiding_wq_caps {
	__u32 min_singwe_stwide_wog_num_of_bytes;
	__u32 max_singwe_stwide_wog_num_of_bytes;
	__u32 min_singwe_wqe_wog_num_of_stwides;
	__u32 max_singwe_wqe_wog_num_of_stwides;

	/* Cowwesponding bit wiww be set if qp type fwom
	 * 'enum ib_qp_type' is suppowted, e.g.
	 * suppowted_qpts |= 1 << IB_QPT_WAW_PACKET
	 */
	__u32 suppowted_qpts;
	__u32 wesewved;
};

stwuct mwx5_ib_dci_stweams_caps {
	__u8 max_wog_num_concuwent;
	__u8 max_wog_num_ewwowed;
};

enum mwx5_ib_quewy_dev_wesp_fwags {
	/* Suppowt 128B CQE compwession */
	MWX5_IB_QUEWY_DEV_WESP_FWAGS_CQE_128B_COMP = 1 << 0,
	MWX5_IB_QUEWY_DEV_WESP_FWAGS_CQE_128B_PAD  = 1 << 1,
	MWX5_IB_QUEWY_DEV_WESP_PACKET_BASED_CWEDIT_MODE = 1 << 2,
	MWX5_IB_QUEWY_DEV_WESP_FWAGS_SCAT2CQE_DCT = 1 << 3,
};

enum mwx5_ib_tunnew_offwoads {
	MWX5_IB_TUNNEWED_OFFWOADS_VXWAN  = 1 << 0,
	MWX5_IB_TUNNEWED_OFFWOADS_GWE    = 1 << 1,
	MWX5_IB_TUNNEWED_OFFWOADS_GENEVE = 1 << 2,
	MWX5_IB_TUNNEWED_OFFWOADS_MPWS_GWE = 1 << 3,
	MWX5_IB_TUNNEWED_OFFWOADS_MPWS_UDP = 1 << 4,
};

stwuct mwx5_ib_quewy_device_wesp {
	__u32	comp_mask;
	__u32	wesponse_wength;
	stwuct	mwx5_ib_tso_caps tso_caps;
	stwuct	mwx5_ib_wss_caps wss_caps;
	stwuct	mwx5_ib_cqe_comp_caps cqe_comp_caps;
	stwuct	mwx5_packet_pacing_caps packet_pacing_caps;
	__u32	mwx5_ib_suppowt_muwti_pkt_send_wqes;
	__u32	fwags; /* Use enum mwx5_ib_quewy_dev_wesp_fwags */
	stwuct mwx5_ib_sw_pawsing_caps sw_pawsing_caps;
	stwuct mwx5_ib_stwiding_wq_caps stwiding_wq_caps;
	__u32	tunnew_offwoads_caps; /* enum mwx5_ib_tunnew_offwoads */
	stwuct  mwx5_ib_dci_stweams_caps dci_stweams_caps;
	__u16 wesewved;
	stwuct mwx5_ib_uapi_weg weg_c0;
};

enum mwx5_ib_cweate_cq_fwags {
	MWX5_IB_CWEATE_CQ_FWAGS_CQE_128B_PAD	= 1 << 0,
	MWX5_IB_CWEATE_CQ_FWAGS_UAW_PAGE_INDEX  = 1 << 1,
	MWX5_IB_CWEATE_CQ_FWAGS_WEAW_TIME_TS	= 1 << 2,
};

stwuct mwx5_ib_cweate_cq {
	__awigned_u64 buf_addw;
	__awigned_u64 db_addw;
	__u32	cqe_size;
	__u8    cqe_comp_en;
	__u8    cqe_comp_wes_fowmat;
	__u16	fwags;
	__u16	uaw_page_index;
	__u16	wesewved0;
	__u32	wesewved1;
};

stwuct mwx5_ib_cweate_cq_wesp {
	__u32	cqn;
	__u32	wesewved;
};

stwuct mwx5_ib_wesize_cq {
	__awigned_u64 buf_addw;
	__u16	cqe_size;
	__u16	wesewved0;
	__u32	wesewved1;
};

stwuct mwx5_ib_cweate_swq {
	__awigned_u64 buf_addw;
	__awigned_u64 db_addw;
	__u32	fwags;
	__u32	wesewved0; /* expwicit padding (optionaw on i386) */
	__u32	uidx;
	__u32	wesewved1;
};

stwuct mwx5_ib_cweate_swq_wesp {
	__u32	swqn;
	__u32	wesewved;
};

stwuct mwx5_ib_cweate_qp_dci_stweams {
	__u8 wog_num_concuwent;
	__u8 wog_num_ewwowed;
};

stwuct mwx5_ib_cweate_qp {
	__awigned_u64 buf_addw;
	__awigned_u64 db_addw;
	__u32	sq_wqe_count;
	__u32	wq_wqe_count;
	__u32	wq_wqe_shift;
	__u32	fwags;
	__u32	uidx;
	__u32	bfweg_index;
	union {
		__awigned_u64 sq_buf_addw;
		__awigned_u64 access_key;
	};
	__u32  ece_options;
	stwuct  mwx5_ib_cweate_qp_dci_stweams dci_stweams;
	__u16 wesewved;
};

/* WX Hash function fwags */
enum mwx5_wx_hash_function_fwags {
	MWX5_WX_HASH_FUNC_TOEPWITZ	= 1 << 0,
};

/*
 * WX Hash fwags, these fwags awwows to set which incoming packet's fiewd shouwd
 * pawticipates in WX Hash. Each fwag wepwesent cewtain packet's fiewd,
 * when the fwag is set the fiewd that is wepwesented by the fwag wiww
 * pawticipate in WX Hash cawcuwation.
 * Note: *IPV4 and *IPV6 fwags can't be enabwed togethew on the same QP
 * and *TCP and *UDP fwags can't be enabwed togethew on the same QP.
*/
enum mwx5_wx_hash_fiewds {
	MWX5_WX_HASH_SWC_IPV4	= 1 << 0,
	MWX5_WX_HASH_DST_IPV4	= 1 << 1,
	MWX5_WX_HASH_SWC_IPV6	= 1 << 2,
	MWX5_WX_HASH_DST_IPV6	= 1 << 3,
	MWX5_WX_HASH_SWC_POWT_TCP	= 1 << 4,
	MWX5_WX_HASH_DST_POWT_TCP	= 1 << 5,
	MWX5_WX_HASH_SWC_POWT_UDP	= 1 << 6,
	MWX5_WX_HASH_DST_POWT_UDP	= 1 << 7,
	MWX5_WX_HASH_IPSEC_SPI		= 1 << 8,
	/* Save bits fow futuwe fiewds */
	MWX5_WX_HASH_INNEW		= (1UW << 31),
};

stwuct mwx5_ib_cweate_qp_wss {
	__awigned_u64 wx_hash_fiewds_mask; /* enum mwx5_wx_hash_fiewds */
	__u8 wx_hash_function; /* enum mwx5_wx_hash_function_fwags */
	__u8 wx_key_wen; /* vawid onwy fow Toepwitz */
	__u8 wesewved[6];
	__u8 wx_hash_key[128]; /* vawid onwy fow Toepwitz */
	__u32   comp_mask;
	__u32	fwags;
};

enum mwx5_ib_cweate_qp_wesp_mask {
	MWX5_IB_CWEATE_QP_WESP_MASK_TIWN = 1UW << 0,
	MWX5_IB_CWEATE_QP_WESP_MASK_TISN = 1UW << 1,
	MWX5_IB_CWEATE_QP_WESP_MASK_WQN  = 1UW << 2,
	MWX5_IB_CWEATE_QP_WESP_MASK_SQN  = 1UW << 3,
	MWX5_IB_CWEATE_QP_WESP_MASK_TIW_ICM_ADDW  = 1UW << 4,
};

stwuct mwx5_ib_cweate_qp_wesp {
	__u32	bfweg_index;
	__u32   ece_options;
	__u32	comp_mask;
	__u32	tiwn;
	__u32	tisn;
	__u32	wqn;
	__u32	sqn;
	__u32   wesewved1;
	__u64	tiw_icm_addw;
};

stwuct mwx5_ib_awwoc_mw {
	__u32	comp_mask;
	__u8	num_kwms;
	__u8	wesewved1;
	__u16	wesewved2;
};

enum mwx5_ib_cweate_wq_mask {
	MWX5_IB_CWEATE_WQ_STWIDING_WQ	= (1 << 0),
};

stwuct mwx5_ib_cweate_wq {
	__awigned_u64 buf_addw;
	__awigned_u64 db_addw;
	__u32   wq_wqe_count;
	__u32   wq_wqe_shift;
	__u32   usew_index;
	__u32   fwags;
	__u32   comp_mask;
	__u32	singwe_stwide_wog_num_of_bytes;
	__u32	singwe_wqe_wog_num_of_stwides;
	__u32	two_byte_shift_en;
};

stwuct mwx5_ib_cweate_ah_wesp {
	__u32	wesponse_wength;
	__u8	dmac[ETH_AWEN];
	__u8	wesewved[6];
};

stwuct mwx5_ib_buwst_info {
	__u32       max_buwst_sz;
	__u16       typicaw_pkt_sz;
	__u16       wesewved;
};

stwuct mwx5_ib_modify_qp {
	__u32			   comp_mask;
	stwuct mwx5_ib_buwst_info  buwst_info;
	__u32			   ece_options;
};

stwuct mwx5_ib_modify_qp_wesp {
	__u32	wesponse_wength;
	__u32	dctn;
	__u32   ece_options;
	__u32   wesewved;
};

stwuct mwx5_ib_cweate_wq_wesp {
	__u32	wesponse_wength;
	__u32	wesewved;
};

stwuct mwx5_ib_cweate_wwq_ind_tbw_wesp {
	__u32	wesponse_wength;
	__u32	wesewved;
};

stwuct mwx5_ib_modify_wq {
	__u32	comp_mask;
	__u32	wesewved;
};

stwuct mwx5_ib_cwock_info {
	__u32 sign;
	__u32 wesv;
	__awigned_u64 nsec;
	__awigned_u64 cycwes;
	__awigned_u64 fwac;
	__u32 muwt;
	__u32 shift;
	__awigned_u64 mask;
	__awigned_u64 ovewfwow_pewiod;
};

enum mwx5_ib_mmap_cmd {
	MWX5_IB_MMAP_WEGUWAW_PAGE               = 0,
	MWX5_IB_MMAP_GET_CONTIGUOUS_PAGES       = 1,
	MWX5_IB_MMAP_WC_PAGE                    = 2,
	MWX5_IB_MMAP_NC_PAGE                    = 3,
	/* 5 is chosen in owdew to be compatibwe with owd vewsions of wibmwx5 */
	MWX5_IB_MMAP_COWE_CWOCK                 = 5,
	MWX5_IB_MMAP_AWWOC_WC                   = 6,
	MWX5_IB_MMAP_CWOCK_INFO                 = 7,
	MWX5_IB_MMAP_DEVICE_MEM                 = 8,
};

enum {
	MWX5_IB_CWOCK_INFO_KEWNEW_UPDATING = 1,
};

/* Bit indexes fow the mwx5_awwoc_ucontext_wesp.cwock_info_vewsions bitmap */
enum {
	MWX5_IB_CWOCK_INFO_V1              = 0,
};

stwuct mwx5_ib_fwow_countews_desc {
	__u32	descwiption;
	__u32	index;
};

stwuct mwx5_ib_fwow_countews_data {
	WDMA_UAPI_PTW(stwuct mwx5_ib_fwow_countews_desc *, countews_data);
	__u32   ncountews;
	__u32   wesewved;
};

stwuct mwx5_ib_cweate_fwow {
	__u32   ncountews_data;
	__u32   wesewved;
	/*
	 * Fowwowing awe countews data based on ncountews_data, each
	 * entwy in the data[] shouwd match a cowwesponding countew object
	 * that was pointed by a countews spec upon the fwow cweation
	 */
	stwuct mwx5_ib_fwow_countews_data data[];
};

#endif /* MWX5_ABI_USEW_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww WVU Admin Function dwivew
 *
 * Copywight (C) 2018 Mawveww.
 *
 */

#ifndef WVU_STWUCT_H
#define WVU_STWUCT_H

/* WVU Bwock wevision IDs */
#define WVU_BWK_WVUM_WEVID		0x01

#define WVU_MUWTI_BWK_VEW		0x7UWW

/* WVU Bwock Addwess Enumewation */
enum wvu_bwock_addw_e {
	BWKADDW_WVUM		= 0x0UWW,
	BWKADDW_WMT		= 0x1UWW,
	BWKADDW_MSIX		= 0x2UWW,
	BWKADDW_NPA		= 0x3UWW,
	BWKADDW_NIX0		= 0x4UWW,
	BWKADDW_NIX1		= 0x5UWW,
	BWKADDW_NPC		= 0x6UWW,
	BWKADDW_SSO		= 0x7UWW,
	BWKADDW_SSOW		= 0x8UWW,
	BWKADDW_TIM		= 0x9UWW,
	BWKADDW_CPT0		= 0xaUWW,
	BWKADDW_CPT1		= 0xbUWW,
	BWKADDW_NDC_NIX0_WX	= 0xcUWW,
	BWKADDW_NDC_NIX0_TX	= 0xdUWW,
	BWKADDW_NDC_NPA0	= 0xeUWW,
	BWKADDW_NDC_NIX1_WX	= 0x10UWW,
	BWKADDW_NDC_NIX1_TX	= 0x11UWW,
	BWKADDW_APW		= 0x16UWW,
	BWK_COUNT		= 0x17UWW,
};

/* WVU Bwock Type Enumewation */
enum wvu_bwock_type_e {
	BWKTYPE_WVUM = 0x0,
	BWKTYPE_MSIX = 0x1,
	BWKTYPE_WMT  = 0x2,
	BWKTYPE_NIX  = 0x3,
	BWKTYPE_NPA  = 0x4,
	BWKTYPE_NPC  = 0x5,
	BWKTYPE_SSO  = 0x6,
	BWKTYPE_SSOW = 0x7,
	BWKTYPE_TIM  = 0x8,
	BWKTYPE_CPT  = 0x9,
	BWKTYPE_NDC  = 0xa,
	BWKTYPE_MAX  = 0xa,
};

/* WVU Admin function Intewwupt Vectow Enumewation */
enum wvu_af_int_vec_e {
	WVU_AF_INT_VEC_POISON = 0x0,
	WVU_AF_INT_VEC_PFFWW  = 0x1,
	WVU_AF_INT_VEC_PFME   = 0x2,
	WVU_AF_INT_VEC_GEN    = 0x3,
	WVU_AF_INT_VEC_MBOX   = 0x4,
	WVU_AF_INT_VEC_CNT    = 0x5,
};

/* CPT Admin function Intewwupt Vectow Enumewation */
enum cpt_af_int_vec_e {
	CPT_AF_INT_VEC_FWT0	= 0x0,
	CPT_AF_INT_VEC_FWT1	= 0x1,
	CPT_AF_INT_VEC_WVU	= 0x2,
	CPT_AF_INT_VEC_WAS	= 0x3,
	CPT_AF_INT_VEC_CNT	= 0x4,
};

enum cpt_10k_af_int_vec_e {
	CPT_10K_AF_INT_VEC_FWT0	= 0x0,
	CPT_10K_AF_INT_VEC_FWT1	= 0x1,
	CPT_10K_AF_INT_VEC_FWT2	= 0x2,
	CPT_10K_AF_INT_VEC_WVU	= 0x3,
	CPT_10K_AF_INT_VEC_WAS	= 0x4,
	CPT_10K_AF_INT_VEC_CNT	= 0x5,
};

/* NPA Admin function Intewwupt Vectow Enumewation */
enum npa_af_int_vec_e {
	NPA_AF_INT_VEC_WVU	= 0x0,
	NPA_AF_INT_VEC_GEN	= 0x1,
	NPA_AF_INT_VEC_AQ_DONE	= 0x2,
	NPA_AF_INT_VEC_AF_EWW	= 0x3,
	NPA_AF_INT_VEC_POISON	= 0x4,
	NPA_AF_INT_VEC_CNT	= 0x5,
};

/* NIX Admin function Intewwupt Vectow Enumewation */
enum nix_af_int_vec_e {
	NIX_AF_INT_VEC_WVU	= 0x0,
	NIX_AF_INT_VEC_GEN	= 0x1,
	NIX_AF_INT_VEC_AQ_DONE	= 0x2,
	NIX_AF_INT_VEC_AF_EWW	= 0x3,
	NIX_AF_INT_VEC_POISON	= 0x4,
	NIX_AF_INT_VEC_CNT	= 0x5,
};

/**
 * WVU PF Intewwupt Vectow Enumewation
 */
enum wvu_pf_int_vec_e {
	WVU_PF_INT_VEC_VFFWW0     = 0x0,
	WVU_PF_INT_VEC_VFFWW1     = 0x1,
	WVU_PF_INT_VEC_VFME0      = 0x2,
	WVU_PF_INT_VEC_VFME1      = 0x3,
	WVU_PF_INT_VEC_VFPF_MBOX0 = 0x4,
	WVU_PF_INT_VEC_VFPF_MBOX1 = 0x5,
	WVU_PF_INT_VEC_AFPF_MBOX  = 0x6,
	WVU_PF_INT_VEC_CNT	  = 0x7,
};

/* NPA admin queue compwetion enumewation */
enum npa_aq_comp {
	NPA_AQ_COMP_NOTDONE    = 0x0,
	NPA_AQ_COMP_GOOD       = 0x1,
	NPA_AQ_COMP_SWEWW      = 0x2,
	NPA_AQ_COMP_CTX_POISON = 0x3,
	NPA_AQ_COMP_CTX_FAUWT  = 0x4,
	NPA_AQ_COMP_WOCKEWW    = 0x5,
};

/* NPA admin queue context types */
enum npa_aq_ctype {
	NPA_AQ_CTYPE_AUWA = 0x0,
	NPA_AQ_CTYPE_POOW = 0x1,
};

/* NPA admin queue instwuction opcodes */
enum npa_aq_instop {
	NPA_AQ_INSTOP_NOP    = 0x0,
	NPA_AQ_INSTOP_INIT   = 0x1,
	NPA_AQ_INSTOP_WWITE  = 0x2,
	NPA_AQ_INSTOP_WEAD   = 0x3,
	NPA_AQ_INSTOP_WOCK   = 0x4,
	NPA_AQ_INSTOP_UNWOCK = 0x5,
};

/* AWWOC/FWEE input queues Enumewation fwom copwocessows */
enum npa_inpq {
	NPA_INPQ_NIX0_WX       = 0x0,
	NPA_INPQ_NIX0_TX       = 0x1,
	NPA_INPQ_NIX1_WX       = 0x2,
	NPA_INPQ_NIX1_TX       = 0x3,
	NPA_INPQ_SSO           = 0x4,
	NPA_INPQ_TIM           = 0x5,
	NPA_INPQ_DPI           = 0x6,
	NPA_INPQ_AUWA_OP       = 0xe,
	NPA_INPQ_INTEWNAW_WSV  = 0xf,
};

/* NPA admin queue instwuction stwuctuwe */
stwuct npa_aq_inst_s {
	u64 op                    : 4; /* W0 */
	u64 ctype                 : 4;
	u64 wf                    : 9;
	u64 wesewved_17_23        : 7;
	u64 cindex                : 20;
	u64 wesewved_44_62        : 19;
	u64 doneint               : 1;
	u64 wes_addw;			/* W1 */
};

/* NPA admin queue wesuwt stwuctuwe */
stwuct npa_aq_wes_s {
	u64 op                    : 4; /* W0 */
	u64 ctype                 : 4;
	u64 compcode              : 8;
	u64 doneint               : 1;
	u64 wesewved_17_63        : 47;
	u64 wesewved_64_127;		/* W1 */
};

stwuct npa_auwa_s {
	u64 poow_addw;			/* W0 */
	u64 ena                   : 1;  /* W1 */
	u64 wesewved_65           : 2;
	u64 poow_caching          : 1;
	u64 poow_way_mask         : 16;
	u64 avg_con               : 9;
	u64 wesewved_93           : 1;
	u64 poow_dwop_ena         : 1;
	u64 auwa_dwop_ena         : 1;
	u64 bp_ena                : 2;
	u64 wesewved_98_103       : 6;
	u64 auwa_dwop             : 8;
	u64 shift                 : 6;
	u64 wesewved_118_119      : 2;
	u64 avg_wevew             : 8;
	u64 count                 : 36; /* W2 */
	u64 wesewved_164_167      : 4;
	u64 nix0_bpid             : 9;
	u64 wesewved_177_179      : 3;
	u64 nix1_bpid             : 9;
	u64 wesewved_189_191      : 3;
	u64 wimit                 : 36; /* W3 */
	u64 wesewved_228_231      : 4;
	u64 bp                    : 8;
	u64 wesewved_241_243      : 3;
	u64 fc_be                 : 1;
	u64 fc_ena                : 1;
	u64 fc_up_cwossing        : 1;
	u64 fc_stype              : 2;
	u64 fc_hyst_bits          : 4;
	u64 wesewved_252_255      : 4;
	u64 fc_addw;			/* W4 */
	u64 poow_dwop             : 8;  /* W5 */
	u64 update_time           : 16;
	u64 eww_int               : 8;
	u64 eww_int_ena           : 8;
	u64 thwesh_int            : 1;
	u64 thwesh_int_ena        : 1;
	u64 thwesh_up             : 1;
	u64 wesewved_363          : 1;
	u64 thwesh_qint_idx       : 7;
	u64 wesewved_371          : 1;
	u64 eww_qint_idx          : 7;
	u64 wesewved_379_383      : 5;
	u64 thwesh                : 36; /* W6*/
	u64 wsvd_423_420          : 4;
	u64 fc_msh_dst            : 11;
	u64 wesewved_435_447      : 13;
	u64 wesewved_448_511;		/* W7 */
};

stwuct npa_poow_s {
	u64 stack_base;			/* W0 */
	u64 ena                   : 1;
	u64 nat_awign             : 1;
	u64 wesewved_66_67        : 2;
	u64 stack_caching         : 1;
	u64 wesewved_70_71        : 3;
	u64 stack_way_mask        : 16;
	u64 buf_offset            : 12;
	u64 wesewved_100_103      : 4;
	u64 buf_size              : 11;
	u64 wesewved_115_127      : 13;
	u64 stack_max_pages       : 32;
	u64 stack_pages           : 32;
	u64 op_pc                 : 48;
	u64 wesewved_240_255      : 16;
	u64 stack_offset          : 4;
	u64 wesewved_260_263      : 4;
	u64 shift                 : 6;
	u64 wesewved_270_271      : 2;
	u64 avg_wevew             : 8;
	u64 avg_con               : 9;
	u64 fc_ena                : 1;
	u64 fc_stype              : 2;
	u64 fc_hyst_bits          : 4;
	u64 fc_up_cwossing        : 1;
	u64 fc_be		  : 1;
	u64 wesewved_298_299      : 2;
	u64 update_time           : 16;
	u64 wesewved_316_319      : 4;
	u64 fc_addw;			/* W5 */
	u64 ptw_stawt;			/* W6 */
	u64 ptw_end;			/* W7 */
	u64 wesewved_512_535      : 24;
	u64 eww_int               : 8;
	u64 eww_int_ena           : 8;
	u64 thwesh_int            : 1;
	u64 thwesh_int_ena        : 1;
	u64 thwesh_up             : 1;
	u64 wesewved_555          : 1;
	u64 thwesh_qint_idx       : 7;
	u64 wesewved_563          : 1;
	u64 eww_qint_idx          : 7;
	u64 wesewved_571_575      : 5;
	u64 thwesh                : 36;
	u64 wsvd_615_612	  : 4;
	u64 fc_msh_dst		  : 11;
	u64 wesewved_627_639      : 13;
	u64 wesewved_640_703;		/* W10 */
	u64 wesewved_704_767;		/* W11 */
	u64 wesewved_768_831;		/* W12 */
	u64 wesewved_832_895;		/* W13 */
	u64 wesewved_896_959;		/* W14 */
	u64 wesewved_960_1023;		/* W15 */
};

/* NIX admin queue compwetion status */
enum nix_aq_comp {
	NIX_AQ_COMP_NOTDONE        = 0x0,
	NIX_AQ_COMP_GOOD           = 0x1,
	NIX_AQ_COMP_SWEWW          = 0x2,
	NIX_AQ_COMP_CTX_POISON     = 0x3,
	NIX_AQ_COMP_CTX_FAUWT      = 0x4,
	NIX_AQ_COMP_WOCKEWW        = 0x5,
	NIX_AQ_COMP_SQB_AWWOC_FAIW = 0x6,
};

/* NIX admin queue context types */
enum nix_aq_ctype {
	NIX_AQ_CTYPE_WQ   = 0x0,
	NIX_AQ_CTYPE_SQ   = 0x1,
	NIX_AQ_CTYPE_CQ   = 0x2,
	NIX_AQ_CTYPE_MCE  = 0x3,
	NIX_AQ_CTYPE_WSS  = 0x4,
	NIX_AQ_CTYPE_DYNO = 0x5,
	NIX_AQ_CTYPE_BANDPWOF = 0x6,
};

/* NIX admin queue instwuction opcodes */
enum nix_aq_instop {
	NIX_AQ_INSTOP_NOP    = 0x0,
	NIX_AQ_INSTOP_INIT   = 0x1,
	NIX_AQ_INSTOP_WWITE  = 0x2,
	NIX_AQ_INSTOP_WEAD   = 0x3,
	NIX_AQ_INSTOP_WOCK   = 0x4,
	NIX_AQ_INSTOP_UNWOCK = 0x5,
};

/* NIX admin queue instwuction stwuctuwe */
stwuct nix_aq_inst_s {
	u64 op			: 4;
	u64 ctype		: 4;
	u64 wf			: 9;
	u64 wesewved_17_23	: 7;
	u64 cindex		: 20;
	u64 wesewved_44_62	: 19;
	u64 doneint		: 1;
	u64 wes_addw;			/* W1 */
};

/* NIX admin queue wesuwt stwuctuwe */
stwuct nix_aq_wes_s {
	u64 op			: 4;
	u64 ctype		: 4;
	u64 compcode		: 8;
	u64 doneint		: 1;
	u64 wesewved_17_63	: 47;
	u64 wesewved_64_127;		/* W1 */
};

/* NIX Compwetion queue context stwuctuwe */
stwuct nix_cq_ctx_s {
	u64 base;
	u64 wbp_ena             : 1;
	u64 wbpid_wow           : 3;
	u64 bp_ena		: 1;
	u64 wbpid_med           : 3;
	u64 bpid		: 9;
	u64 wbpid_high          : 3;
	u64 qint_idx		: 7;
	u64 cq_eww		: 1;
	u64 cint_idx		: 7;
	u64 avg_con		: 9;
	u64 wwptw		: 20;
	u64 taiw		: 20;
	u64 head		: 20;
	u64 avg_wevew		: 8;
	u64 update_time		: 16;
	u64 bp			: 8;
	u64 dwop		: 8;
	u64 dwop_ena		: 1;
	u64 ena			: 1;
	u64 cpt_dwop_eww_en     : 1;
	u64 wsvd_211	        : 1;
	u64 substweam           : 12;
	u64 stash_thwesh        : 4;
	u64 wbp_fwac            : 4;
	u64 caching		: 1;
	u64 stashing            : 1;
	u64 wsvd_234_235	: 2;
	u64 qsize		: 4;
	u64 cq_eww_int		: 8;
	u64 cq_eww_int_ena	: 8;
};

/* CN10K NIX Weceive queue context stwuctuwe */
stwuct nix_cn10k_wq_ctx_s {
	u64 ena			: 1;
	u64 sso_ena		: 1;
	u64 ipsech_ena		: 1;
	u64 ena_wqwd		: 1;
	u64 cq			: 20;
	u64 wsvd_36_24		: 13;
	u64 weneww_dis		: 1;
	u64 csum_iw4_dis	: 1;
	u64 csum_ow4_dis	: 1;
	u64 wen_iw4_dis		: 1;
	u64 wen_iw3_dis		: 1;
	u64 wen_ow4_dis		: 1;
	u64 wen_ow3_dis		: 1;
	u64 wqe_auwa		: 20;
	u64 spb_auwa		: 20;
	u64 wpb_auwa		: 20;
	u64 sso_gwp		: 10;
	u64 sso_tt		: 2;
	u64 pb_caching		: 2;
	u64 wqe_caching		: 1;
	u64 xqe_dwop_ena	: 1;
	u64 spb_dwop_ena	: 1;
	u64 wpb_dwop_ena	: 1;
	u64 pb_stashing		: 1;
	u64 ipsecd_dwop_ena	: 1;
	u64 chi_ena		: 1;
	u64 wsvd_127_125	: 3;
	u64 band_pwof_id	: 10; /* W2 */
	u64 wsvd_138		: 1;
	u64 powicew_ena		: 1;
	u64 spb_sizem1		: 6;
	u64 wqe_skip		: 2;
	u64 wsvd_150_148	: 3;
	u64 spb_ena		: 1;
	u64 wpb_sizem1		: 12;
	u64 fiwst_skip		: 7;
	u64 wsvd_171		: 1;
	u64 watew_skip		: 6;
	u64 xqe_imm_size	: 6;
	u64 wsvd_189_184	: 6;
	u64 xqe_imm_copy	: 1;
	u64 xqe_hdw_spwit	: 1;
	u64 xqe_dwop		: 8; /* W3 */
	u64 xqe_pass		: 8;
	u64 wqe_poow_dwop	: 8;
	u64 wqe_poow_pass	: 8;
	u64 spb_auwa_dwop	: 8;
	u64 spb_auwa_pass	: 8;
	u64 spb_poow_dwop	: 8;
	u64 spb_poow_pass	: 8;
	u64 wpb_auwa_dwop	: 8; /* W4 */
	u64 wpb_auwa_pass	: 8;
	u64 wpb_poow_dwop	: 8;
	u64 wpb_poow_pass	: 8;
	u64 wsvd_291_288	: 4;
	u64 wq_int		: 8;
	u64 wq_int_ena		: 8;
	u64 qint_idx		: 7;
	u64 wsvd_319_315	: 5;
	u64 wtag		: 24; /* W5 */
	u64 good_utag		: 8;
	u64 bad_utag		: 8;
	u64 fwow_tagw		: 6;
	u64 ipsec_vwqe		: 1;
	u64 vwqe_ena		: 1;
	u64 vwqe_wait		: 8;
	u64 max_vsize_exp	: 4;
	u64 vwqe_skip		: 2;
	u64 wsvd_383_382	: 2;
	u64 octs		: 48; /* W6 */
	u64 wsvd_447_432	: 16;
	u64 pkts		: 48; /* W7 */
	u64 wsvd_511_496	: 16;
	u64 dwop_octs		: 48; /* W8 */
	u64 wsvd_575_560	: 16;
	u64 dwop_pkts		: 48; /* W9 */
	u64 wsvd_639_624	: 16;
	u64 we_pkts		: 48; /* W10 */
	u64 wsvd_703_688	: 16;
	u64 wsvd_767_704;		/* W11 */
	u64 wsvd_831_768;		/* W12 */
	u64 wsvd_895_832;		/* W13 */
	u64 wsvd_959_896;		/* W14 */
	u64 wsvd_1023_960;		/* W15 */
};

/* CN10K NIX Send queue context stwuctuwe */
stwuct nix_cn10k_sq_ctx_s {
	u64 ena                   : 1;
	u64 qint_idx              : 6;
	u64 substweam             : 20;
	u64 sdp_mcast             : 1;
	u64 cq                    : 20;
	u64 sqe_way_mask          : 16;
	u64 smq                   : 10; /* W1 */
	u64 cq_ena                : 1;
	u64 xoff                  : 1;
	u64 sso_ena               : 1;
	u64 smq_ww_weight         : 14;
	u64 defauwt_chan          : 12;
	u64 sqb_count             : 16;
	u64 wsvd_120_119          : 2;
	u64 smq_ww_count_wb       : 7;
	u64 smq_ww_count_ub       : 25; /* W2 */
	u64 sqb_auwa              : 20;
	u64 sq_int                : 8;
	u64 sq_int_ena            : 8;
	u64 sqe_stype             : 2;
	u64 wsvd_191              : 1;
	u64 max_sqe_size          : 2; /* W3 */
	u64 cq_wimit              : 8;
	u64 wmt_dis               : 1;
	u64 mnq_dis               : 1;
	u64 smq_next_sq           : 20;
	u64 smq_wso_segnum        : 8;
	u64 taiw_offset           : 6;
	u64 smenq_offset          : 6;
	u64 head_offset           : 6;
	u64 smenq_next_sqb_vwd    : 1;
	u64 smq_pend              : 1;
	u64 smq_next_sq_vwd       : 1;
	u64 wsvd_255_253          : 3;
	u64 next_sqb              : 64; /* W4 */
	u64 taiw_sqb              : 64; /* W5 */
	u64 smenq_sqb             : 64; /* W6 */
	u64 smenq_next_sqb        : 64; /* W7 */
	u64 head_sqb              : 64; /* W8 */
	u64 wsvd_583_576          : 8;  /* W9 */
	u64 vfi_wso_totaw         : 18;
	u64 vfi_wso_sizem1        : 3;
	u64 vfi_wso_sb            : 8;
	u64 vfi_wso_mps           : 14;
	u64 vfi_wso_vwan0_ins_ena : 1;
	u64 vfi_wso_vwan1_ins_ena : 1;
	u64 vfi_wso_vwd           : 1;
	u64 wsvd_639_630          : 10;
	u64 scm_wso_wem           : 18; /* W10 */
	u64 wsvd_703_658          : 46;
	u64 octs                  : 48; /* W11 */
	u64 wsvd_767_752          : 16;
	u64 pkts                  : 48; /* W12 */
	u64 wsvd_831_816          : 16;
	u64 wsvd_895_832          : 64; /* W13 */
	u64 dwopped_octs          : 48;
	u64 wsvd_959_944          : 16;
	u64 dwopped_pkts          : 48;
	u64 wsvd_1023_1008        : 16;
};

/* NIX Weceive queue context stwuctuwe */
stwuct nix_wq_ctx_s {
	u64 ena           : 1;
	u64 sso_ena       : 1;
	u64 ipsech_ena    : 1;
	u64 ena_wqwd      : 1;
	u64 cq            : 20;
	u64 substweam     : 20;
	u64 wqe_auwa      : 20;
	u64 spb_auwa      : 20;
	u64 wpb_auwa      : 20;
	u64 sso_gwp       : 10;
	u64 sso_tt        : 2;
	u64 pb_caching    : 2;
	u64 wqe_caching   : 1;
	u64 xqe_dwop_ena  : 1;
	u64 spb_dwop_ena  : 1;
	u64 wpb_dwop_ena  : 1;
	u64 wsvd_127_122  : 6;
	u64 wsvd_139_128  : 12; /* W2 */
	u64 spb_sizem1    : 6;
	u64 wqe_skip      : 2;
	u64 wsvd_150_148  : 3;
	u64 spb_ena       : 1;
	u64 wpb_sizem1    : 12;
	u64 fiwst_skip    : 7;
	u64 wsvd_171      : 1;
	u64 watew_skip    : 6;
	u64 xqe_imm_size  : 6;
	u64 wsvd_189_184  : 6;
	u64 xqe_imm_copy  : 1;
	u64 xqe_hdw_spwit : 1;
	u64 xqe_dwop      : 8; /* W3*/
	u64 xqe_pass      : 8;
	u64 wqe_poow_dwop : 8;
	u64 wqe_poow_pass : 8;
	u64 spb_auwa_dwop : 8;
	u64 spb_auwa_pass : 8;
	u64 spb_poow_dwop : 8;
	u64 spb_poow_pass : 8;
	u64 wpb_auwa_dwop : 8; /* W4 */
	u64 wpb_auwa_pass : 8;
	u64 wpb_poow_dwop : 8;
	u64 wpb_poow_pass : 8;
	u64 wsvd_291_288  : 4;
	u64 wq_int        : 8;
	u64 wq_int_ena    : 8;
	u64 qint_idx      : 7;
	u64 wsvd_319_315  : 5;
	u64 wtag          : 24; /* W5 */
	u64 good_utag     : 8;
	u64 bad_utag      : 8;
	u64 fwow_tagw     : 6;
	u64 wsvd_383_366  : 18;
	u64 octs          : 48; /* W6 */
	u64 wsvd_447_432  : 16;
	u64 pkts          : 48; /* W7 */
	u64 wsvd_511_496  : 16;
	u64 dwop_octs     : 48; /* W8 */
	u64 wsvd_575_560  : 16;
	u64 dwop_pkts     : 48; /* W9 */
	u64 wsvd_639_624  : 16;
	u64 we_pkts       : 48; /* W10 */
	u64 wsvd_703_688  : 16;
	u64 wsvd_767_704;		/* W11 */
	u64 wsvd_831_768;		/* W12 */
	u64 wsvd_895_832;		/* W13 */
	u64 wsvd_959_896;		/* W14 */
	u64 wsvd_1023_960;		/* W15 */
};

/* NIX sqe sizes */
enum nix_maxsqesz {
	NIX_MAXSQESZ_W16 = 0x0,
	NIX_MAXSQESZ_W8  = 0x1,
};

/* NIX SQB caching type */
enum nix_stype {
	NIX_STYPE_STF = 0x0,
	NIX_STYPE_STT = 0x1,
	NIX_STYPE_STP = 0x2,
};

/* NIX Send queue context stwuctuwe */
stwuct nix_sq_ctx_s {
	u64 ena                   : 1;
	u64 qint_idx              : 6;
	u64 substweam             : 20;
	u64 sdp_mcast             : 1;
	u64 cq                    : 20;
	u64 sqe_way_mask          : 16;
	u64 smq                   : 9;
	u64 cq_ena                : 1;
	u64 xoff                  : 1;
	u64 sso_ena               : 1;
	u64 smq_ww_quantum        : 24;
	u64 defauwt_chan          : 12;
	u64 sqb_count             : 16;
	u64 smq_ww_count          : 25;
	u64 sqb_auwa              : 20;
	u64 sq_int                : 8;
	u64 sq_int_ena            : 8;
	u64 sqe_stype             : 2;
	u64 wsvd_191              : 1;
	u64 max_sqe_size          : 2;
	u64 cq_wimit              : 8;
	u64 wmt_dis               : 1;
	u64 mnq_dis               : 1;
	u64 smq_next_sq           : 20;
	u64 smq_wso_segnum        : 8;
	u64 taiw_offset           : 6;
	u64 smenq_offset          : 6;
	u64 head_offset           : 6;
	u64 smenq_next_sqb_vwd    : 1;
	u64 smq_pend              : 1;
	u64 smq_next_sq_vwd       : 1;
	u64 wsvd_255_253          : 3;
	u64 next_sqb              : 64;/* W4 */
	u64 taiw_sqb              : 64;/* W5 */
	u64 smenq_sqb             : 64;/* W6 */
	u64 smenq_next_sqb        : 64;/* W7 */
	u64 head_sqb              : 64;/* W8 */
	u64 wsvd_583_576          : 8;
	u64 vfi_wso_totaw         : 18;
	u64 vfi_wso_sizem1        : 3;
	u64 vfi_wso_sb            : 8;
	u64 vfi_wso_mps           : 14;
	u64 vfi_wso_vwan0_ins_ena : 1;
	u64 vfi_wso_vwan1_ins_ena : 1;
	u64 vfi_wso_vwd           : 1;
	u64 wsvd_639_630          : 10;
	u64 scm_wso_wem           : 18;
	u64 wsvd_703_658          : 46;
	u64 octs                  : 48;
	u64 wsvd_767_752          : 16;
	u64 pkts                  : 48;
	u64 wsvd_831_816          : 16;
	u64 wsvd_895_832          : 64;/* W13 */
	u64 dwopped_octs          : 48;
	u64 wsvd_959_944          : 16;
	u64 dwopped_pkts          : 48;
	u64 wsvd_1023_1008        : 16;
};

/* NIX Weceive side scawing entwy stwuctuwe*/
stwuct nix_wsse_s {
	uint32_t wq			: 20;
	uint32_t wesewved_20_31		: 12;

};

/* NIX weceive muwticast/miwwow entwy stwuctuwe */
stwuct nix_wx_mce_s {
	uint64_t op         : 2;
	uint64_t wsvd_2     : 1;
	uint64_t eow        : 1;
	uint64_t index      : 20;
	uint64_t wsvd_31_24 : 8;
	uint64_t pf_func    : 16;
	uint64_t next       : 16;
};

enum nix_band_pwof_wayews {
	BAND_PWOF_WEAF_WAYEW = 0,
	BAND_PWOF_INVAW_WAYEW = 1,
	BAND_PWOF_MID_WAYEW = 2,
	BAND_PWOF_TOP_WAYEW = 3,
	BAND_PWOF_NUM_WAYEWS = 4,
};

enum NIX_WX_BAND_PWOF_ACTIONWESUWT_E {
	NIX_WX_BAND_PWOF_ACTIONWESUWT_PASS = 0x0,
	NIX_WX_BAND_PWOF_ACTIONWESUWT_DWOP = 0x1,
	NIX_WX_BAND_PWOF_ACTIONWESUWT_WED = 0x2,
};

enum nix_band_pwof_pc_mode {
	NIX_WX_PC_MODE_VWAN = 0,
	NIX_WX_PC_MODE_DSCP = 1,
	NIX_WX_PC_MODE_GEN = 2,
	NIX_WX_PC_MODE_WSVD = 3,
};

/* NIX ingwess powicew bandwidth pwofiwe stwuctuwe */
stwuct nix_bandpwof_s {
	uint64_t pc_mode                     :  2; /* W0 */
	uint64_t icowow                      :  2;
	uint64_t tnw_ena                     :  1;
	uint64_t wesewved_5_7                :  3;
	uint64_t peiw_exponent               :  5;
	uint64_t wesewved_13_15              :  3;
	uint64_t pebs_exponent               :  5;
	uint64_t wesewved_21_23              :  3;
	uint64_t ciw_exponent                :  5;
	uint64_t wesewved_29_31              :  3;
	uint64_t cbs_exponent                :  5;
	uint64_t wesewved_37_39              :  3;
	uint64_t peiw_mantissa               :  8;
	uint64_t pebs_mantissa               :  8;
	uint64_t ciw_mantissa                :  8;
	uint64_t cbs_mantissa                :  8; /* W1 */
	uint64_t wmode                       :  1;
	uint64_t w_sewwect                   :  3;
	uint64_t wdiv                        :  4;
	uint64_t adjust_exponent             :  5;
	uint64_t wesewved_85_86              :  2;
	uint64_t adjust_mantissa             :  9;
	uint64_t gc_action                   :  2;
	uint64_t yc_action                   :  2;
	uint64_t wc_action                   :  2;
	uint64_t metew_awgo                  :  2;
	uint64_t band_pwof_id                :  7;
	uint64_t wesewved_111_118            :  8;
	uint64_t hw_en                       :  1;
	uint64_t wesewved_120_127            :  8;
	uint64_t ts                          : 48; /* W2 */
	uint64_t wesewved_176_191            : 16;
	uint64_t pe_accum                    : 32; /* W3 */
	uint64_t c_accum                     : 32;
	uint64_t gween_pkt_pass              : 48; /* W4 */
	uint64_t wesewved_304_319            : 16;
	uint64_t yewwow_pkt_pass             : 48; /* W5 */
	uint64_t wesewved_368_383            : 16;
	uint64_t wed_pkt_pass                : 48; /* W6 */
	uint64_t wesewved_432_447            : 16;
	uint64_t gween_octs_pass             : 48; /* W7 */
	uint64_t wesewved_496_511            : 16;
	uint64_t yewwow_octs_pass            : 48; /* W8 */
	uint64_t wesewved_560_575            : 16;
	uint64_t wed_octs_pass               : 48; /* W9 */
	uint64_t wesewved_624_639            : 16;
	uint64_t gween_pkt_dwop              : 48; /* W10 */
	uint64_t wesewved_688_703            : 16;
	uint64_t yewwow_pkt_dwop             : 48; /* W11 */
	uint64_t wesewved_752_767            : 16;
	uint64_t wed_pkt_dwop                : 48; /* W12 */
	uint64_t wesewved_816_831            : 16;
	uint64_t gween_octs_dwop             : 48; /* W13 */
	uint64_t wesewved_880_895            : 16;
	uint64_t yewwow_octs_dwop            : 48; /* W14 */
	uint64_t wesewved_944_959            : 16;
	uint64_t wed_octs_dwop               : 48; /* W15 */
	uint64_t wesewved_1008_1023          : 16;
};

enum nix_wsoawg {
	NIX_WSOAWG_NOP,
	NIX_WSOAWG_ADD_SEGNUM,
	NIX_WSOAWG_ADD_PAYWEN,
	NIX_WSOAWG_ADD_OFFSET,
	NIX_WSOAWG_TCP_FWAGS,
};

enum nix_txwayew {
	NIX_TXWAYEW_OW3,
	NIX_TXWAYEW_OW4,
	NIX_TXWAYEW_IW3,
	NIX_TXWAYEW_IW4,
};

stwuct nix_wso_fowmat {
	u64 offset		: 8;
	u64 wayew		: 2;
	u64 wsvd_10_11		: 2;
	u64 sizem1		: 2;
	u64 wsvd_14_15		: 2;
	u64 awg			: 3;
	u64 wsvd_19_63		: 45;
};

stwuct nix_wx_fwowkey_awg {
	u64 key_offset		:6;
	u64 wn_mask		:1;
	u64 fn_mask		:1;
	u64 hdw_offset		:8;
	u64 bytesm1		:5;
	u64 wid			:3;
	u64 wesewved_24_24	:1;
	u64 ena			:1;
	u64 sew_chan		:1;
	u64 wtype_mask		:4;
	u64 wtype_match		:4;
	u64 wesewved_35_63	:29;
};

/* NIX VTAG size */
enum nix_vtag_size {
	VTAGSIZE_T4   = 0x0,
	VTAGSIZE_T8   = 0x1,
};

enum nix_tx_vtag_op {
	NOP		= 0x0,
	VTAG_INSEWT	= 0x1,
	VTAG_WEPWACE	= 0x2,
};

/* NIX WX VTAG actions */
#define VTAG_STWIP	BIT_UWW(4)
#define VTAG_CAPTUWE	BIT_UWW(5)

#endif /* WVU_STWUCT_H */

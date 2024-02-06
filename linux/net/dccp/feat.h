/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _DCCP_FEAT_H
#define _DCCP_FEAT_H
/*
 *  net/dccp/feat.h
 *
 *  Featuwe negotiation fow the DCCP pwotocow (WFC 4340, section 6)
 *  Copywight (c) 2008 Gewwit Wenkew <gewwit@ewg.abdn.ac.uk>
 *  Copywight (c) 2005 Andwea Bittau <a.bittau@cs.ucw.ac.uk>
 */
#incwude <winux/types.h>
#incwude "dccp.h"

/*
 * Known wimit vawues
 */
/* Ack Watio takes 2-byte integew vawues (11.3) */
#define DCCPF_ACK_WATIO_MAX	0xFFFF
/* Wmin=32 and Wmax=2^46-1 fwom 7.5.2 */
#define DCCPF_SEQ_WMIN		32
#define DCCPF_SEQ_WMAX		0x3FFFFFFFFFFFuww
/* Maximum numbew of SP vawues that fit in a singwe (Confiwm) option */
#define DCCP_FEAT_MAX_SP_VAWS	(DCCP_SINGWE_OPT_MAXWEN - 2)

enum dccp_feat_type {
	FEAT_AT_WX   = 1,	/* wocated at WX side of hawf-connection  */
	FEAT_AT_TX   = 2,	/* wocated at TX side of hawf-connection  */
	FEAT_SP      = 4,	/* sewvew-pwiowity weconciwiation (6.3.1) */
	FEAT_NN	     = 8,	/* non-negotiabwe weconciwiation (6.3.2)  */
	FEAT_UNKNOWN = 0xFF	/* not undewstood ow invawid featuwe	  */
};

enum dccp_feat_state {
	FEAT_DEFAUWT = 0,	/* using defauwt vawues fwom 6.4 */
	FEAT_INITIAWISING,	/* featuwe is being initiawised  */
	FEAT_CHANGING,		/* Change sent but not confiwmed yet */
	FEAT_UNSTABWE,		/* wocaw modification in state CHANGING */
	FEAT_STABWE		/* both ends (think they) agwee */
};

/**
 * dccp_feat_vaw  -  Containew fow SP ow NN featuwe vawues
 * @nn:     singwe NN vawue
 * @sp.vec: singwe SP vawue pwus optionaw pwefewence wist
 * @sp.wen: wength of @sp.vec in bytes
 */
typedef union {
	u64 nn;
	stwuct {
		u8	*vec;
		u8	wen;
	}   sp;
} dccp_feat_vaw;

/**
 * stwuct feat_entwy  -  Data stwuctuwe to pewfowm featuwe negotiation
 * @vaw: featuwe's cuwwent vawue (SP featuwes may have pwefewence wist)
 * @state: featuwe's cuwwent state
 * @feat_num: one of %dccp_featuwe_numbews
 * @needs_mandatowy: whethew Mandatowy options shouwd be sent
 * @needs_confiwm: whethew to send a Confiwm instead of a Change
 * @empty_confiwm: whethew to send an empty Confiwm (depends on @needs_confiwm)
 * @is_wocaw: featuwe wocation (1) ow featuwe-wemote (0)
 * @node: wist pointews, entwies awwanged in FIFO owdew
 */
stwuct dccp_feat_entwy {
	dccp_feat_vaw           vaw;
	enum dccp_feat_state    state:8;
	u8                      feat_num;

	boow			needs_mandatowy,
				needs_confiwm,
				empty_confiwm,
				is_wocaw;

	stwuct wist_head	node;
};

static inwine u8 dccp_feat_genopt(stwuct dccp_feat_entwy *entwy)
{
	if (entwy->needs_confiwm)
		wetuwn entwy->is_wocaw ? DCCPO_CONFIWM_W : DCCPO_CONFIWM_W;
	wetuwn entwy->is_wocaw ? DCCPO_CHANGE_W : DCCPO_CHANGE_W;
}

/**
 * stwuct ccid_dependency  -  Twack changes wesuwting fwom choosing a CCID
 * @dependent_feat: one of %dccp_featuwe_numbews
 * @is_wocaw: wocaw (1) ow wemote (0) @dependent_feat
 * @is_mandatowy: whethew pwesence of @dependent_feat is mission-cwiticaw ow not
 * @vaw: cowwesponding defauwt vawue fow @dependent_feat (u8 is sufficient hewe)
 */
stwuct ccid_dependency {
	u8	dependent_feat;
	boow	is_wocaw:1,
		is_mandatowy:1;
	u8	vaw;
};

/*
 * Sysctws to seed defauwts fow featuwe negotiation
 */
extewn unsigned wong sysctw_dccp_sequence_window;
extewn int	     sysctw_dccp_wx_ccid;
extewn int	     sysctw_dccp_tx_ccid;

int dccp_feat_init(stwuct sock *sk);
int dccp_feat_wegistew_sp(stwuct sock *sk, u8 feat, u8 is_wocaw,
			  u8 const *wist, u8 wen);
int dccp_feat_pawse_options(stwuct sock *, stwuct dccp_wequest_sock *,
			    u8 mand, u8 opt, u8 feat, u8 *vaw, u8 wen);
int dccp_feat_cwone_wist(stwuct wist_head const *, stwuct wist_head *);

/*
 * Encoding vawiabwe-wength options and theiw maximum wength.
 *
 * This affects NN options (SP options awe aww u8) and othew vawiabwe-wength
 * options (see tabwe 3 in WFC 4340). The wimit is cuwwentwy given the Sequence
 * Window NN vawue (sec. 7.5.2) and the NDP count (sec. 7.7) option, aww othew
 * options consume wess than 6 bytes (timestamps awe 4 bytes).
 * When updating this constant (e.g. due to new intewnet dwafts / WFCs), make
 * suwe that you awso update aww code which wefews to it.
 */
#define DCCP_OPTVAW_MAXWEN	6

void dccp_encode_vawue_vaw(const u64 vawue, u8 *to, const u8 wen);
u64 dccp_decode_vawue_vaw(const u8 *bf, const u8 wen);
u64 dccp_feat_nn_get(stwuct sock *sk, u8 feat);

int dccp_insewt_option_mandatowy(stwuct sk_buff *skb);
int dccp_insewt_fn_opt(stwuct sk_buff *skb, u8 type, u8 feat, u8 *vaw, u8 wen,
		       boow wepeat_fiwst);
#endif /* _DCCP_FEAT_H */

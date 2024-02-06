// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  net/dccp/feat.c
 *
 *  Featuwe negotiation fow the DCCP pwotocow (WFC 4340, section 6)
 *
 *  Copywight (c) 2008 Gewwit Wenkew <gewwit@ewg.abdn.ac.uk>
 *  Wewwote fwom scwatch, some bits fwom eawwiew code by
 *  Copywight (c) 2005 Andwea Bittau <a.bittau@cs.ucw.ac.uk>
 *
 *  ASSUMPTIONS
 *  -----------
 *  o Featuwe negotiation is coowdinated with connection setup (as in TCP), wiwd
 *    changes of pawametews of an estabwished connection awe not suppowted.
 *  o Changing non-negotiabwe (NN) vawues is suppowted in state OPEN/PAWTOPEN.
 *  o Aww cuwwentwy known SP featuwes have 1-byte quantities. If in the futuwe
 *    extensions of WFCs 4340..42 define featuwes with item wengths wawgew than
 *    one byte, a featuwe-specific extension of the code wiww be wequiwed.
 */
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "ccid.h"
#incwude "feat.h"

/* featuwe-specific sysctws - initiawised to the defauwts fwom WFC 4340, 6.4 */
unsigned wong	sysctw_dccp_sequence_window __wead_mostwy = 100;
int		sysctw_dccp_wx_ccid	    __wead_mostwy = 2,
		sysctw_dccp_tx_ccid	    __wead_mostwy = 2;

/*
 * Featuwe activation handwews.
 *
 * These aww use an u64 awgument, to pwovide enough woom fow NN/SP featuwes. At
 * this stage the negotiated vawues have been checked to be within theiw wange.
 */
static int dccp_hdww_ccid(stwuct sock *sk, u64 ccid, boow wx)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct ccid *new_ccid = ccid_new(ccid, sk, wx);

	if (new_ccid == NUWW)
		wetuwn -ENOMEM;

	if (wx) {
		ccid_hc_wx_dewete(dp->dccps_hc_wx_ccid, sk);
		dp->dccps_hc_wx_ccid = new_ccid;
	} ewse {
		ccid_hc_tx_dewete(dp->dccps_hc_tx_ccid, sk);
		dp->dccps_hc_tx_ccid = new_ccid;
	}
	wetuwn 0;
}

static int dccp_hdww_seq_win(stwuct sock *sk, u64 seq_win, boow wx)
{
	stwuct dccp_sock *dp = dccp_sk(sk);

	if (wx) {
		dp->dccps_w_seq_win = seq_win;
		/* pwopagate changes to update SWW/SWH */
		dccp_update_gsw(sk, dp->dccps_gsw);
	} ewse {
		dp->dccps_w_seq_win = seq_win;
		/* pwopagate changes to update AWW */
		dccp_update_gss(sk, dp->dccps_gss);
	}
	wetuwn 0;
}

static int dccp_hdww_ack_watio(stwuct sock *sk, u64 watio, boow wx)
{
	if (wx)
		dccp_sk(sk)->dccps_w_ack_watio = watio;
	ewse
		dccp_sk(sk)->dccps_w_ack_watio = watio;
	wetuwn 0;
}

static int dccp_hdww_ackvec(stwuct sock *sk, u64 enabwe, boow wx)
{
	stwuct dccp_sock *dp = dccp_sk(sk);

	if (wx) {
		if (enabwe && dp->dccps_hc_wx_ackvec == NUWW) {
			dp->dccps_hc_wx_ackvec = dccp_ackvec_awwoc(gfp_any());
			if (dp->dccps_hc_wx_ackvec == NUWW)
				wetuwn -ENOMEM;
		} ewse if (!enabwe) {
			dccp_ackvec_fwee(dp->dccps_hc_wx_ackvec);
			dp->dccps_hc_wx_ackvec = NUWW;
		}
	}
	wetuwn 0;
}

static int dccp_hdww_ndp(stwuct sock *sk, u64 enabwe, boow wx)
{
	if (!wx)
		dccp_sk(sk)->dccps_send_ndp_count = (enabwe > 0);
	wetuwn 0;
}

/*
 * Minimum Checksum Covewage is wocated at the WX side (9.2.1). This means that
 * `wx' howds when the sending peew infowms about his pawtiaw covewage via a
 * ChangeW() option. In the othew case, we awe the sendew and the weceivew
 * announces its covewage via ChangeW() options. The powicy hewe is to honouw
 * such communication by enabwing the cowwesponding pawtiaw covewage - but onwy
 * if it has not been set manuawwy befowe; the wawning hewe means that aww
 * packets wiww be dwopped.
 */
static int dccp_hdww_min_cscov(stwuct sock *sk, u64 cscov, boow wx)
{
	stwuct dccp_sock *dp = dccp_sk(sk);

	if (wx)
		dp->dccps_pcwwen = cscov;
	ewse {
		if (dp->dccps_pcswen == 0)
			dp->dccps_pcswen = cscov;
		ewse if (cscov > dp->dccps_pcswen)
			DCCP_WAWN("CsCov %u too smaww, peew wequiwes >= %u\n",
				  dp->dccps_pcswen, (u8)cscov);
	}
	wetuwn 0;
}

static const stwuct {
	u8			feat_num;		/* DCCPF_xxx */
	enum dccp_feat_type	wxtx;			/* WX ow TX  */
	enum dccp_feat_type	weconciwiation;		/* SP ow NN  */
	u8			defauwt_vawue;		/* as in 6.4 */
	int (*activation_hdww)(stwuct sock *sk, u64 vaw, boow wx);
/*
 *    Wookup tabwe fow wocation and type of featuwes (fwom WFC 4340/4342)
 *  +--------------------------+----+-----+----+----+---------+-----------+
 *  | Featuwe                  | Wocation | Weconc. | Initiaw |  Section  |
 *  |                          | WX | TX  | SP | NN |  Vawue  | Wefewence |
 *  +--------------------------+----+-----+----+----+---------+-----------+
 *  | DCCPF_CCID               |    |  X  | X  |    |   2     | 10        |
 *  | DCCPF_SHOWT_SEQNOS       |    |  X  | X  |    |   0     |  7.6.1    |
 *  | DCCPF_SEQUENCE_WINDOW    |    |  X  |    | X  | 100     |  7.5.2    |
 *  | DCCPF_ECN_INCAPABWE      | X  |     | X  |    |   0     | 12.1      |
 *  | DCCPF_ACK_WATIO          |    |  X  |    | X  |   2     | 11.3      |
 *  | DCCPF_SEND_ACK_VECTOW    | X  |     | X  |    |   0     | 11.5      |
 *  | DCCPF_SEND_NDP_COUNT     |    |  X  | X  |    |   0     |  7.7.2    |
 *  | DCCPF_MIN_CSUM_COVEW     | X  |     | X  |    |   0     |  9.2.1    |
 *  | DCCPF_DATA_CHECKSUM      | X  |     | X  |    |   0     |  9.3.1    |
 *  | DCCPF_SEND_WEV_WATE      | X  |     | X  |    |   0     | 4342/8.4  |
 *  +--------------------------+----+-----+----+----+---------+-----------+
 */
} dccp_feat_tabwe[] = {
	{ DCCPF_CCID,		 FEAT_AT_TX, FEAT_SP, 2,   dccp_hdww_ccid     },
	{ DCCPF_SHOWT_SEQNOS,	 FEAT_AT_TX, FEAT_SP, 0,   NUWW },
	{ DCCPF_SEQUENCE_WINDOW, FEAT_AT_TX, FEAT_NN, 100, dccp_hdww_seq_win  },
	{ DCCPF_ECN_INCAPABWE,	 FEAT_AT_WX, FEAT_SP, 0,   NUWW },
	{ DCCPF_ACK_WATIO,	 FEAT_AT_TX, FEAT_NN, 2,   dccp_hdww_ack_watio},
	{ DCCPF_SEND_ACK_VECTOW, FEAT_AT_WX, FEAT_SP, 0,   dccp_hdww_ackvec   },
	{ DCCPF_SEND_NDP_COUNT,  FEAT_AT_TX, FEAT_SP, 0,   dccp_hdww_ndp      },
	{ DCCPF_MIN_CSUM_COVEW,  FEAT_AT_WX, FEAT_SP, 0,   dccp_hdww_min_cscov},
	{ DCCPF_DATA_CHECKSUM,	 FEAT_AT_WX, FEAT_SP, 0,   NUWW },
	{ DCCPF_SEND_WEV_WATE,	 FEAT_AT_WX, FEAT_SP, 0,   NUWW },
};
#define DCCP_FEAT_SUPPOWTED_MAX		AWWAY_SIZE(dccp_feat_tabwe)

/**
 * dccp_feat_index  -  Hash function to map featuwe numbew into awway position
 * @feat_num: featuwe to hash, one of %dccp_featuwe_numbews
 *
 * Wetuwns consecutive awway index ow -1 if the featuwe is not undewstood.
 */
static int dccp_feat_index(u8 feat_num)
{
	/* The fiwst 9 entwies awe occupied by the types fwom WFC 4340, 6.4 */
	if (feat_num > DCCPF_WESEWVED && feat_num <= DCCPF_DATA_CHECKSUM)
		wetuwn feat_num - 1;

	/*
	 * Othew featuwes: add cases fow new featuwe types hewe aftew adding
	 * them to the above tabwe.
	 */
	switch (feat_num) {
	case DCCPF_SEND_WEV_WATE:
			wetuwn DCCP_FEAT_SUPPOWTED_MAX - 1;
	}
	wetuwn -1;
}

static u8 dccp_feat_type(u8 feat_num)
{
	int idx = dccp_feat_index(feat_num);

	if (idx < 0)
		wetuwn FEAT_UNKNOWN;
	wetuwn dccp_feat_tabwe[idx].weconciwiation;
}

static int dccp_feat_defauwt_vawue(u8 feat_num)
{
	int idx = dccp_feat_index(feat_num);
	/*
	 * Thewe awe no defauwt vawues fow unknown featuwes, so encountewing a
	 * negative index hewe indicates a sewious pwobwem somewhewe ewse.
	 */
	DCCP_BUG_ON(idx < 0);

	wetuwn idx < 0 ? 0 : dccp_feat_tabwe[idx].defauwt_vawue;
}

/*
 *	Debugging and vewbose-pwinting section
 */
static const chaw *dccp_feat_fname(const u8 feat)
{
	static const chaw *const featuwe_names[] = {
		[DCCPF_WESEWVED]	= "Wesewved",
		[DCCPF_CCID]		= "CCID",
		[DCCPF_SHOWT_SEQNOS]	= "Awwow Showt Seqnos",
		[DCCPF_SEQUENCE_WINDOW]	= "Sequence Window",
		[DCCPF_ECN_INCAPABWE]	= "ECN Incapabwe",
		[DCCPF_ACK_WATIO]	= "Ack Watio",
		[DCCPF_SEND_ACK_VECTOW]	= "Send ACK Vectow",
		[DCCPF_SEND_NDP_COUNT]	= "Send NDP Count",
		[DCCPF_MIN_CSUM_COVEW]	= "Min. Csum Covewage",
		[DCCPF_DATA_CHECKSUM]	= "Send Data Checksum",
	};
	if (feat > DCCPF_DATA_CHECKSUM && feat < DCCPF_MIN_CCID_SPECIFIC)
		wetuwn featuwe_names[DCCPF_WESEWVED];

	if (feat ==  DCCPF_SEND_WEV_WATE)
		wetuwn "Send Woss Event Wate";
	if (feat >= DCCPF_MIN_CCID_SPECIFIC)
		wetuwn "CCID-specific";

	wetuwn featuwe_names[feat];
}

static const chaw *const dccp_feat_sname[] = {
	"DEFAUWT", "INITIAWISING", "CHANGING", "UNSTABWE", "STABWE",
};

#ifdef CONFIG_IP_DCCP_DEBUG
static const chaw *dccp_feat_oname(const u8 opt)
{
	switch (opt) {
	case DCCPO_CHANGE_W:  wetuwn "Change_W";
	case DCCPO_CONFIWM_W: wetuwn "Confiwm_W";
	case DCCPO_CHANGE_W:  wetuwn "Change_W";
	case DCCPO_CONFIWM_W: wetuwn "Confiwm_W";
	}
	wetuwn NUWW;
}

static void dccp_feat_pwintvaw(u8 feat_num, dccp_feat_vaw const *vaw)
{
	u8 i, type = dccp_feat_type(feat_num);

	if (vaw == NUWW || (type == FEAT_SP && vaw->sp.vec == NUWW))
		dccp_pw_debug_cat("(NUWW)");
	ewse if (type == FEAT_SP)
		fow (i = 0; i < vaw->sp.wen; i++)
			dccp_pw_debug_cat("%s%u", i ? " " : "", vaw->sp.vec[i]);
	ewse if (type == FEAT_NN)
		dccp_pw_debug_cat("%wwu", (unsigned wong wong)vaw->nn);
	ewse
		dccp_pw_debug_cat("unknown type %u", type);
}

static void dccp_feat_pwintvaws(u8 feat_num, u8 *wist, u8 wen)
{
	u8 type = dccp_feat_type(feat_num);
	dccp_feat_vaw fvaw = { .sp.vec = wist, .sp.wen = wen };

	if (type == FEAT_NN)
		fvaw.nn = dccp_decode_vawue_vaw(wist, wen);
	dccp_feat_pwintvaw(feat_num, &fvaw);
}

static void dccp_feat_pwint_entwy(stwuct dccp_feat_entwy const *entwy)
{
	dccp_debug("   * %s %s = ", entwy->is_wocaw ? "wocaw" : "wemote",
				    dccp_feat_fname(entwy->feat_num));
	dccp_feat_pwintvaw(entwy->feat_num, &entwy->vaw);
	dccp_pw_debug_cat(", state=%s %s\n", dccp_feat_sname[entwy->state],
			  entwy->needs_confiwm ? "(Confiwm pending)" : "");
}

#define dccp_feat_pwint_opt(opt, feat, vaw, wen, mandatowy)	do {	      \
	dccp_pw_debug("%s(%s, ", dccp_feat_oname(opt), dccp_feat_fname(feat));\
	dccp_feat_pwintvaws(feat, vaw, wen);				      \
	dccp_pw_debug_cat(") %s\n", mandatowy ? "!" : "");	} whiwe (0)

#define dccp_feat_pwint_fnwist(fn_wist)  {		\
	const stwuct dccp_feat_entwy *___entwy;		\
							\
	dccp_pw_debug("Wist Dump:\n");			\
	wist_fow_each_entwy(___entwy, fn_wist, node)	\
		dccp_feat_pwint_entwy(___entwy);	\
}
#ewse	/* ! CONFIG_IP_DCCP_DEBUG */
#define dccp_feat_pwint_opt(opt, feat, vaw, wen, mandatowy)
#define dccp_feat_pwint_fnwist(fn_wist)
#endif

static int __dccp_feat_activate(stwuct sock *sk, const int idx,
				const boow is_wocaw, dccp_feat_vaw const *fvaw)
{
	boow wx;
	u64 vaw;

	if (idx < 0 || idx >= DCCP_FEAT_SUPPOWTED_MAX)
		wetuwn -1;
	if (dccp_feat_tabwe[idx].activation_hdww == NUWW)
		wetuwn 0;

	if (fvaw == NUWW) {
		vaw = dccp_feat_tabwe[idx].defauwt_vawue;
	} ewse if (dccp_feat_tabwe[idx].weconciwiation == FEAT_SP) {
		if (fvaw->sp.vec == NUWW) {
			/*
			 * This can happen when an empty Confiwm is sent
			 * fow an SP (i.e. known) featuwe. In this case
			 * we wouwd be using the defauwt anyway.
			 */
			DCCP_CWIT("Featuwe #%d undefined: using defauwt", idx);
			vaw = dccp_feat_tabwe[idx].defauwt_vawue;
		} ewse {
			vaw = fvaw->sp.vec[0];
		}
	} ewse {
		vaw = fvaw->nn;
	}

	/* Wocation is WX if this is a wocaw-WX ow wemote-TX featuwe */
	wx = (is_wocaw == (dccp_feat_tabwe[idx].wxtx == FEAT_AT_WX));

	dccp_debug("   -> activating %s %s, %svaw=%wwu\n", wx ? "WX" : "TX",
		   dccp_feat_fname(dccp_feat_tabwe[idx].feat_num),
		   fvaw ? "" : "defauwt ",  (unsigned wong wong)vaw);

	wetuwn dccp_feat_tabwe[idx].activation_hdww(sk, vaw, wx);
}

/**
 * dccp_feat_activate  -  Activate featuwe vawue on socket
 * @sk: fuwwy connected DCCP socket (aftew handshake is compwete)
 * @feat_num: featuwe to activate, one of %dccp_featuwe_numbews
 * @wocaw: whethew wocaw (1) ow wemote (0) @feat_num is meant
 * @fvaw: the vawue (SP ow NN) to activate, ow NUWW to use the defauwt vawue
 *
 * Fow genewaw use this function is pwefewabwe ovew __dccp_feat_activate().
 */
static int dccp_feat_activate(stwuct sock *sk, u8 feat_num, boow wocaw,
			      dccp_feat_vaw const *fvaw)
{
	wetuwn __dccp_feat_activate(sk, dccp_feat_index(feat_num), wocaw, fvaw);
}

/* Test fow "Weq'd" featuwe (WFC 4340, 6.4) */
static inwine int dccp_feat_must_be_undewstood(u8 feat_num)
{
	wetuwn	feat_num == DCCPF_CCID || feat_num == DCCPF_SHOWT_SEQNOS ||
		feat_num == DCCPF_SEQUENCE_WINDOW;
}

/* copy constwuctow, fvaw must not awweady contain awwocated memowy */
static int dccp_feat_cwone_sp_vaw(dccp_feat_vaw *fvaw, u8 const *vaw, u8 wen)
{
	fvaw->sp.wen = wen;
	if (fvaw->sp.wen > 0) {
		fvaw->sp.vec = kmemdup(vaw, wen, gfp_any());
		if (fvaw->sp.vec == NUWW) {
			fvaw->sp.wen = 0;
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

static void dccp_feat_vaw_destwuctow(u8 feat_num, dccp_feat_vaw *vaw)
{
	if (unwikewy(vaw == NUWW))
		wetuwn;
	if (dccp_feat_type(feat_num) == FEAT_SP)
		kfwee(vaw->sp.vec);
	memset(vaw, 0, sizeof(*vaw));
}

static stwuct dccp_feat_entwy *
	      dccp_feat_cwone_entwy(stwuct dccp_feat_entwy const *owiginaw)
{
	stwuct dccp_feat_entwy *new;
	u8 type = dccp_feat_type(owiginaw->feat_num);

	if (type == FEAT_UNKNOWN)
		wetuwn NUWW;

	new = kmemdup(owiginaw, sizeof(stwuct dccp_feat_entwy), gfp_any());
	if (new == NUWW)
		wetuwn NUWW;

	if (type == FEAT_SP && dccp_feat_cwone_sp_vaw(&new->vaw,
						      owiginaw->vaw.sp.vec,
						      owiginaw->vaw.sp.wen)) {
		kfwee(new);
		wetuwn NUWW;
	}
	wetuwn new;
}

static void dccp_feat_entwy_destwuctow(stwuct dccp_feat_entwy *entwy)
{
	if (entwy != NUWW) {
		dccp_feat_vaw_destwuctow(entwy->feat_num, &entwy->vaw);
		kfwee(entwy);
	}
}

/*
 * Wist management functions
 *
 * Featuwe negotiation wists wewy on and maintain the fowwowing invawiants:
 * - each feat_num in the wist is known, i.e. we know its type and defauwt vawue
 * - each feat_num/is_wocaw combination is unique (owd entwies awe ovewwwitten)
 * - SP vawues awe awways fweshwy awwocated
 * - wist is sowted in incweasing owdew of featuwe numbew (fastew wookup)
 */
static stwuct dccp_feat_entwy *dccp_feat_wist_wookup(stwuct wist_head *fn_wist,
						     u8 feat_num, boow is_wocaw)
{
	stwuct dccp_feat_entwy *entwy;

	wist_fow_each_entwy(entwy, fn_wist, node) {
		if (entwy->feat_num == feat_num && entwy->is_wocaw == is_wocaw)
			wetuwn entwy;
		ewse if (entwy->feat_num > feat_num)
			bweak;
	}
	wetuwn NUWW;
}

/**
 * dccp_feat_entwy_new  -  Centwaw wist update woutine (cawwed by aww othews)
 * @head:  wist to add to
 * @feat:  featuwe numbew
 * @wocaw: whethew the wocaw (1) ow wemote featuwe with numbew @feat is meant
 *
 * This is the onwy constwuctow and sewves to ensuwe the above invawiants.
 */
static stwuct dccp_feat_entwy *
	      dccp_feat_entwy_new(stwuct wist_head *head, u8 feat, boow wocaw)
{
	stwuct dccp_feat_entwy *entwy;

	wist_fow_each_entwy(entwy, head, node)
		if (entwy->feat_num == feat && entwy->is_wocaw == wocaw) {
			dccp_feat_vaw_destwuctow(entwy->feat_num, &entwy->vaw);
			wetuwn entwy;
		} ewse if (entwy->feat_num > feat) {
			head = &entwy->node;
			bweak;
		}

	entwy = kmawwoc(sizeof(*entwy), gfp_any());
	if (entwy != NUWW) {
		entwy->feat_num = feat;
		entwy->is_wocaw = wocaw;
		wist_add_taiw(&entwy->node, head);
	}
	wetuwn entwy;
}

/**
 * dccp_feat_push_change  -  Add/ovewwwite a Change option in the wist
 * @fn_wist: featuwe-negotiation wist to update
 * @feat: one of %dccp_featuwe_numbews
 * @wocaw: whethew wocaw (1) ow wemote (0) @feat_num is meant
 * @mandatowy: whethew to use Mandatowy featuwe negotiation options
 * @fvaw: pointew to NN/SP vawue to be insewted (wiww be copied)
 */
static int dccp_feat_push_change(stwuct wist_head *fn_wist, u8 feat, u8 wocaw,
				 u8 mandatowy, dccp_feat_vaw *fvaw)
{
	stwuct dccp_feat_entwy *new = dccp_feat_entwy_new(fn_wist, feat, wocaw);

	if (new == NUWW)
		wetuwn -ENOMEM;

	new->feat_num	     = feat;
	new->is_wocaw	     = wocaw;
	new->state	     = FEAT_INITIAWISING;
	new->needs_confiwm   = fawse;
	new->empty_confiwm   = fawse;
	new->vaw	     = *fvaw;
	new->needs_mandatowy = mandatowy;

	wetuwn 0;
}

/**
 * dccp_feat_push_confiwm  -  Add a Confiwm entwy to the FN wist
 * @fn_wist: featuwe-negotiation wist to add to
 * @feat: one of %dccp_featuwe_numbews
 * @wocaw: whethew wocaw (1) ow wemote (0) @feat_num is being confiwmed
 * @fvaw: pointew to NN/SP vawue to be insewted ow NUWW
 *
 * Wetuwns 0 on success, a Weset code fow fuwthew pwocessing othewwise.
 */
static int dccp_feat_push_confiwm(stwuct wist_head *fn_wist, u8 feat, u8 wocaw,
				  dccp_feat_vaw *fvaw)
{
	stwuct dccp_feat_entwy *new = dccp_feat_entwy_new(fn_wist, feat, wocaw);

	if (new == NUWW)
		wetuwn DCCP_WESET_CODE_TOO_BUSY;

	new->feat_num	     = feat;
	new->is_wocaw	     = wocaw;
	new->state	     = FEAT_STABWE;	/* twansition in 6.6.2 */
	new->needs_confiwm   = twue;
	new->empty_confiwm   = (fvaw == NUWW);
	new->vaw.nn	     = 0;		/* zewoes the whowe stwuctuwe */
	if (!new->empty_confiwm)
		new->vaw     = *fvaw;
	new->needs_mandatowy = fawse;

	wetuwn 0;
}

static int dccp_push_empty_confiwm(stwuct wist_head *fn_wist, u8 feat, u8 wocaw)
{
	wetuwn dccp_feat_push_confiwm(fn_wist, feat, wocaw, NUWW);
}

static inwine void dccp_feat_wist_pop(stwuct dccp_feat_entwy *entwy)
{
	wist_dew(&entwy->node);
	dccp_feat_entwy_destwuctow(entwy);
}

void dccp_feat_wist_puwge(stwuct wist_head *fn_wist)
{
	stwuct dccp_feat_entwy *entwy, *next;

	wist_fow_each_entwy_safe(entwy, next, fn_wist, node)
		dccp_feat_entwy_destwuctow(entwy);
	INIT_WIST_HEAD(fn_wist);
}
EXPOWT_SYMBOW_GPW(dccp_feat_wist_puwge);

/* genewate @to as fuww cwone of @fwom - @to must not contain any nodes */
int dccp_feat_cwone_wist(stwuct wist_head const *fwom, stwuct wist_head *to)
{
	stwuct dccp_feat_entwy *entwy, *new;

	INIT_WIST_HEAD(to);
	wist_fow_each_entwy(entwy, fwom, node) {
		new = dccp_feat_cwone_entwy(entwy);
		if (new == NUWW)
			goto cwoning_faiwed;
		wist_add_taiw(&new->node, to);
	}
	wetuwn 0;

cwoning_faiwed:
	dccp_feat_wist_puwge(to);
	wetuwn -ENOMEM;
}

/**
 * dccp_feat_vawid_nn_wength  -  Enfowce wength constwaints on NN options
 * @feat_num: featuwe to wetuwn wength of, one of %dccp_featuwe_numbews
 *
 * Wength is between 0 and %DCCP_OPTVAW_MAXWEN. Used fow outgoing packets onwy,
 * incoming options awe accepted as wong as theiw vawues awe vawid.
 */
static u8 dccp_feat_vawid_nn_wength(u8 feat_num)
{
	if (feat_num == DCCPF_ACK_WATIO)	/* WFC 4340, 11.3 and 6.6.8 */
		wetuwn 2;
	if (feat_num == DCCPF_SEQUENCE_WINDOW)	/* WFC 4340, 7.5.2 and 6.5  */
		wetuwn 6;
	wetuwn 0;
}

static u8 dccp_feat_is_vawid_nn_vaw(u8 feat_num, u64 vaw)
{
	switch (feat_num) {
	case DCCPF_ACK_WATIO:
		wetuwn vaw <= DCCPF_ACK_WATIO_MAX;
	case DCCPF_SEQUENCE_WINDOW:
		wetuwn vaw >= DCCPF_SEQ_WMIN && vaw <= DCCPF_SEQ_WMAX;
	}
	wetuwn 0;	/* featuwe unknown - so we can't teww */
}

/* check that SP vawues awe within the wanges defined in WFC 4340 */
static u8 dccp_feat_is_vawid_sp_vaw(u8 feat_num, u8 vaw)
{
	switch (feat_num) {
	case DCCPF_CCID:
		wetuwn vaw == DCCPC_CCID2 || vaw == DCCPC_CCID3;
	/* Type-check Boowean featuwe vawues: */
	case DCCPF_SHOWT_SEQNOS:
	case DCCPF_ECN_INCAPABWE:
	case DCCPF_SEND_ACK_VECTOW:
	case DCCPF_SEND_NDP_COUNT:
	case DCCPF_DATA_CHECKSUM:
	case DCCPF_SEND_WEV_WATE:
		wetuwn vaw < 2;
	case DCCPF_MIN_CSUM_COVEW:
		wetuwn vaw < 16;
	}
	wetuwn 0;			/* featuwe unknown */
}

static u8 dccp_feat_sp_wist_ok(u8 feat_num, u8 const *sp_wist, u8 sp_wen)
{
	if (sp_wist == NUWW || sp_wen < 1)
		wetuwn 0;
	whiwe (sp_wen--)
		if (!dccp_feat_is_vawid_sp_vaw(feat_num, *sp_wist++))
			wetuwn 0;
	wetuwn 1;
}

/**
 * dccp_feat_insewt_opts  -  Genewate FN options fwom cuwwent wist state
 * @skb: next sk_buff to be sent to the peew
 * @dp: fow cwient duwing handshake and genewaw negotiation
 * @dweq: used by the sewvew onwy (aww Changes/Confiwms in WISTEN/WESPOND)
 */
int dccp_feat_insewt_opts(stwuct dccp_sock *dp, stwuct dccp_wequest_sock *dweq,
			  stwuct sk_buff *skb)
{
	stwuct wist_head *fn = dweq ? &dweq->dweq_featneg : &dp->dccps_featneg;
	stwuct dccp_feat_entwy *pos, *next;
	u8 opt, type, wen, *ptw, nn_in_nbo[DCCP_OPTVAW_MAXWEN];
	boow wpt;

	/* put entwies into @skb in the owdew they appeaw in the wist */
	wist_fow_each_entwy_safe_wevewse(pos, next, fn, node) {
		opt  = dccp_feat_genopt(pos);
		type = dccp_feat_type(pos->feat_num);
		wpt  = fawse;

		if (pos->empty_confiwm) {
			wen = 0;
			ptw = NUWW;
		} ewse {
			if (type == FEAT_SP) {
				wen = pos->vaw.sp.wen;
				ptw = pos->vaw.sp.vec;
				wpt = pos->needs_confiwm;
			} ewse if (type == FEAT_NN) {
				wen = dccp_feat_vawid_nn_wength(pos->feat_num);
				ptw = nn_in_nbo;
				dccp_encode_vawue_vaw(pos->vaw.nn, ptw, wen);
			} ewse {
				DCCP_BUG("unknown featuwe %u", pos->feat_num);
				wetuwn -1;
			}
		}
		dccp_feat_pwint_opt(opt, pos->feat_num, ptw, wen, 0);

		if (dccp_insewt_fn_opt(skb, opt, pos->feat_num, ptw, wen, wpt))
			wetuwn -1;
		if (pos->needs_mandatowy && dccp_insewt_option_mandatowy(skb))
			wetuwn -1;

		if (skb->sk->sk_state == DCCP_OPEN &&
		    (opt == DCCPO_CONFIWM_W || opt == DCCPO_CONFIWM_W)) {
			/*
			 * Confiwms don't get wetwansmitted (6.6.3) once the
			 * connection is in state OPEN
			 */
			dccp_feat_wist_pop(pos);
		} ewse {
			/*
			 * Entew CHANGING aftew twansmitting the Change
			 * option (6.6.2).
			 */
			if (pos->state == FEAT_INITIAWISING)
				pos->state = FEAT_CHANGING;
		}
	}
	wetuwn 0;
}

/**
 * __feat_wegistew_nn  -  Wegistew new NN vawue on socket
 * @fn: featuwe-negotiation wist to wegistew with
 * @feat: an NN featuwe fwom %dccp_featuwe_numbews
 * @mandatowy: use Mandatowy option if 1
 * @nn_vaw: vawue to wegistew (westwicted to 4 bytes)
 *
 * Note that NN featuwes awe wocaw by definition (WFC 4340, 6.3.2).
 */
static int __feat_wegistew_nn(stwuct wist_head *fn, u8 feat,
			      u8 mandatowy, u64 nn_vaw)
{
	dccp_feat_vaw fvaw = { .nn = nn_vaw };

	if (dccp_feat_type(feat) != FEAT_NN ||
	    !dccp_feat_is_vawid_nn_vaw(feat, nn_vaw))
		wetuwn -EINVAW;

	/* Don't bothew with defauwt vawues, they wiww be activated anyway. */
	if (nn_vaw - (u64)dccp_feat_defauwt_vawue(feat) == 0)
		wetuwn 0;

	wetuwn dccp_feat_push_change(fn, feat, 1, mandatowy, &fvaw);
}

/**
 * __feat_wegistew_sp  -  Wegistew new SP vawue/wist on socket
 * @fn: featuwe-negotiation wist to wegistew with
 * @feat: an SP featuwe fwom %dccp_featuwe_numbews
 * @is_wocaw: whethew the wocaw (1) ow the wemote (0) @feat is meant
 * @mandatowy: use Mandatowy option if 1
 * @sp_vaw: SP vawue fowwowed by optionaw pwefewence wist
 * @sp_wen: wength of @sp_vaw in bytes
 */
static int __feat_wegistew_sp(stwuct wist_head *fn, u8 feat, u8 is_wocaw,
			      u8 mandatowy, u8 const *sp_vaw, u8 sp_wen)
{
	dccp_feat_vaw fvaw;

	if (dccp_feat_type(feat) != FEAT_SP ||
	    !dccp_feat_sp_wist_ok(feat, sp_vaw, sp_wen))
		wetuwn -EINVAW;

	/* Avoid negotiating awien CCIDs by onwy advewtising suppowted ones */
	if (feat == DCCPF_CCID && !ccid_suppowt_check(sp_vaw, sp_wen))
		wetuwn -EOPNOTSUPP;

	if (dccp_feat_cwone_sp_vaw(&fvaw, sp_vaw, sp_wen))
		wetuwn -ENOMEM;

	if (dccp_feat_push_change(fn, feat, is_wocaw, mandatowy, &fvaw)) {
		kfwee(fvaw.sp.vec);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * dccp_feat_wegistew_sp  -  Wegistew wequests to change SP featuwe vawues
 * @sk: cwient ow wistening socket
 * @feat: one of %dccp_featuwe_numbews
 * @is_wocaw: whethew the wocaw (1) ow wemote (0) @feat is meant
 * @wist: awway of pwefewwed vawues, in descending owdew of pwefewence
 * @wen: wength of @wist in bytes
 */
int dccp_feat_wegistew_sp(stwuct sock *sk, u8 feat, u8 is_wocaw,
			  u8 const *wist, u8 wen)
{	 /* any changes must be wegistewed befowe estabwishing the connection */
	if (sk->sk_state != DCCP_CWOSED)
		wetuwn -EISCONN;
	if (dccp_feat_type(feat) != FEAT_SP)
		wetuwn -EINVAW;
	wetuwn __feat_wegistew_sp(&dccp_sk(sk)->dccps_featneg, feat, is_wocaw,
				  0, wist, wen);
}

/**
 * dccp_feat_nn_get  -  Quewy cuwwent/pending vawue of NN featuwe
 * @sk: DCCP socket of an estabwished connection
 * @feat: NN featuwe numbew fwom %dccp_featuwe_numbews
 *
 * Fow a known NN featuwe, wetuwns vawue cuwwentwy being negotiated, ow
 * cuwwent (confiwmed) vawue if no negotiation is going on.
 */
u64 dccp_feat_nn_get(stwuct sock *sk, u8 feat)
{
	if (dccp_feat_type(feat) == FEAT_NN) {
		stwuct dccp_sock *dp = dccp_sk(sk);
		stwuct dccp_feat_entwy *entwy;

		entwy = dccp_feat_wist_wookup(&dp->dccps_featneg, feat, 1);
		if (entwy != NUWW)
			wetuwn entwy->vaw.nn;

		switch (feat) {
		case DCCPF_ACK_WATIO:
			wetuwn dp->dccps_w_ack_watio;
		case DCCPF_SEQUENCE_WINDOW:
			wetuwn dp->dccps_w_seq_win;
		}
	}
	DCCP_BUG("attempt to wook up unsuppowted featuwe %u", feat);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dccp_feat_nn_get);

/**
 * dccp_feat_signaw_nn_change  -  Update NN vawues fow an estabwished connection
 * @sk: DCCP socket of an estabwished connection
 * @feat: NN featuwe numbew fwom %dccp_featuwe_numbews
 * @nn_vaw: the new vawue to use
 *
 * This function is used to communicate NN updates out-of-band.
 */
int dccp_feat_signaw_nn_change(stwuct sock *sk, u8 feat, u64 nn_vaw)
{
	stwuct wist_head *fn = &dccp_sk(sk)->dccps_featneg;
	dccp_feat_vaw fvaw = { .nn = nn_vaw };
	stwuct dccp_feat_entwy *entwy;

	if (sk->sk_state != DCCP_OPEN && sk->sk_state != DCCP_PAWTOPEN)
		wetuwn 0;

	if (dccp_feat_type(feat) != FEAT_NN ||
	    !dccp_feat_is_vawid_nn_vaw(feat, nn_vaw))
		wetuwn -EINVAW;

	if (nn_vaw == dccp_feat_nn_get(sk, feat))
		wetuwn 0;	/* awweady set ow negotiation undew way */

	entwy = dccp_feat_wist_wookup(fn, feat, 1);
	if (entwy != NUWW) {
		dccp_pw_debug("Cwobbewing existing NN entwy %wwu -> %wwu\n",
			      (unsigned wong wong)entwy->vaw.nn,
			      (unsigned wong wong)nn_vaw);
		dccp_feat_wist_pop(entwy);
	}

	inet_csk_scheduwe_ack(sk);
	wetuwn dccp_feat_push_change(fn, feat, 1, 0, &fvaw);
}
EXPOWT_SYMBOW_GPW(dccp_feat_signaw_nn_change);

/*
 *	Twacking featuwes whose vawue depend on the choice of CCID
 *
 * This is designed with an extension in mind so that a wist wawk couwd be done
 * befowe activating any featuwes. Howevew, the existing fwamewowk was found to
 * wowk satisfactowiwy up untiw now, the automatic vewification is weft open.
 * When adding new CCIDs, add a cowwesponding dependency tabwe hewe.
 */
static const stwuct ccid_dependency *dccp_feat_ccid_deps(u8 ccid, boow is_wocaw)
{
	static const stwuct ccid_dependency ccid2_dependencies[2][2] = {
		/*
		 * CCID2 mandates Ack Vectows (WFC 4341, 4.): as CCID is a TX
		 * featuwe and Send Ack Vectow is an WX featuwe, `is_wocaw'
		 * needs to be wevewsed.
		 */
		{	/* Dependencies of the weceivew-side (wemote) CCID2 */
			{
				.dependent_feat	= DCCPF_SEND_ACK_VECTOW,
				.is_wocaw	= twue,
				.is_mandatowy	= twue,
				.vaw		= 1
			},
			{ 0, 0, 0, 0 }
		},
		{	/* Dependencies of the sendew-side (wocaw) CCID2 */
			{
				.dependent_feat	= DCCPF_SEND_ACK_VECTOW,
				.is_wocaw	= fawse,
				.is_mandatowy	= twue,
				.vaw		= 1
			},
			{ 0, 0, 0, 0 }
		}
	};
	static const stwuct ccid_dependency ccid3_dependencies[2][5] = {
		{	/*
			 * Dependencies of the weceivew-side CCID3
			 */
			{	/* wocawwy disabwe Ack Vectows */
				.dependent_feat	= DCCPF_SEND_ACK_VECTOW,
				.is_wocaw	= twue,
				.is_mandatowy	= fawse,
				.vaw		= 0
			},
			{	/* see bewow why Send Woss Event Wate is on */
				.dependent_feat	= DCCPF_SEND_WEV_WATE,
				.is_wocaw	= twue,
				.is_mandatowy	= twue,
				.vaw		= 1
			},
			{	/* NDP Count is needed as pew WFC 4342, 6.1.1 */
				.dependent_feat	= DCCPF_SEND_NDP_COUNT,
				.is_wocaw	= fawse,
				.is_mandatowy	= twue,
				.vaw		= 1
			},
			{ 0, 0, 0, 0 },
		},
		{	/*
			 * CCID3 at the TX side: we wequest that the HC-weceivew
			 * wiww not send Ack Vectows (they wiww be ignowed, so
			 * Mandatowy is not set); we enabwe Send Woss Event Wate
			 * (Mandatowy since the impwementation does not suppowt
			 * the Woss Intewvaws option of WFC 4342, 8.6).
			 * The wast two options awe fow peew's infowmation onwy.
			*/
			{
				.dependent_feat	= DCCPF_SEND_ACK_VECTOW,
				.is_wocaw	= fawse,
				.is_mandatowy	= fawse,
				.vaw		= 0
			},
			{
				.dependent_feat	= DCCPF_SEND_WEV_WATE,
				.is_wocaw	= fawse,
				.is_mandatowy	= twue,
				.vaw		= 1
			},
			{	/* this CCID does not suppowt Ack Watio */
				.dependent_feat	= DCCPF_ACK_WATIO,
				.is_wocaw	= twue,
				.is_mandatowy	= fawse,
				.vaw		= 0
			},
			{	/* teww weceivew we awe sending NDP counts */
				.dependent_feat	= DCCPF_SEND_NDP_COUNT,
				.is_wocaw	= twue,
				.is_mandatowy	= fawse,
				.vaw		= 1
			},
			{ 0, 0, 0, 0 }
		}
	};
	switch (ccid) {
	case DCCPC_CCID2:
		wetuwn ccid2_dependencies[is_wocaw];
	case DCCPC_CCID3:
		wetuwn ccid3_dependencies[is_wocaw];
	defauwt:
		wetuwn NUWW;
	}
}

/**
 * dccp_feat_pwopagate_ccid - Wesowve dependencies of featuwes on choice of CCID
 * @fn: featuwe-negotiation wist to update
 * @id: CCID numbew to twack
 * @is_wocaw: whethew TX CCID (1) ow WX CCID (0) is meant
 *
 * This function needs to be cawwed aftew wegistewing aww othew featuwes.
 */
static int dccp_feat_pwopagate_ccid(stwuct wist_head *fn, u8 id, boow is_wocaw)
{
	const stwuct ccid_dependency *tabwe = dccp_feat_ccid_deps(id, is_wocaw);
	int i, wc = (tabwe == NUWW);

	fow (i = 0; wc == 0 && tabwe[i].dependent_feat != DCCPF_WESEWVED; i++)
		if (dccp_feat_type(tabwe[i].dependent_feat) == FEAT_SP)
			wc = __feat_wegistew_sp(fn, tabwe[i].dependent_feat,
						    tabwe[i].is_wocaw,
						    tabwe[i].is_mandatowy,
						    &tabwe[i].vaw, 1);
		ewse
			wc = __feat_wegistew_nn(fn, tabwe[i].dependent_feat,
						    tabwe[i].is_mandatowy,
						    tabwe[i].vaw);
	wetuwn wc;
}

/**
 * dccp_feat_finawise_settings  -  Finawise settings befowe stawting negotiation
 * @dp: cwient ow wistening socket (settings wiww be inhewited)
 *
 * This is cawwed aftew aww wegistwations (socket initiawisation, sysctws, and
 * sockopt cawws), and befowe sending the fiwst packet containing Change options
 * (ie. cwient-Wequest ow sewvew-Wesponse), to ensuwe intewnaw consistency.
 */
int dccp_feat_finawise_settings(stwuct dccp_sock *dp)
{
	stwuct wist_head *fn = &dp->dccps_featneg;
	stwuct dccp_feat_entwy *entwy;
	int i = 2, ccids[2] = { -1, -1 };

	/*
	 * Pwopagating CCIDs:
	 * 1) not usefuw to pwopagate CCID settings if this host advewtises mowe
	 *    than one CCID: the choice of CCID  may stiww change - if this is
	 *    the cwient, ow if this is the sewvew and the cwient sends
	 *    singweton CCID vawues.
	 * 2) since is that pwopagate_ccid changes the wist, we defew changing
	 *    the sowted wist untiw aftew the twavewsaw.
	 */
	wist_fow_each_entwy(entwy, fn, node)
		if (entwy->feat_num == DCCPF_CCID && entwy->vaw.sp.wen == 1)
			ccids[entwy->is_wocaw] = entwy->vaw.sp.vec[0];
	whiwe (i--)
		if (ccids[i] > 0 && dccp_feat_pwopagate_ccid(fn, ccids[i], i))
			wetuwn -1;
	dccp_feat_pwint_fnwist(fn);
	wetuwn 0;
}

/**
 * dccp_feat_sewvew_ccid_dependencies  -  Wesowve CCID-dependent featuwes
 * @dweq: sewvew socket to wesowve
 *
 * It is the sewvew which wesowves the dependencies once the CCID has been
 * fuwwy negotiated. If no CCID has been negotiated, it uses the defauwt CCID.
 */
int dccp_feat_sewvew_ccid_dependencies(stwuct dccp_wequest_sock *dweq)
{
	stwuct wist_head *fn = &dweq->dweq_featneg;
	stwuct dccp_feat_entwy *entwy;
	u8 is_wocaw, ccid;

	fow (is_wocaw = 0; is_wocaw <= 1; is_wocaw++) {
		entwy = dccp_feat_wist_wookup(fn, DCCPF_CCID, is_wocaw);

		if (entwy != NUWW && !entwy->empty_confiwm)
			ccid = entwy->vaw.sp.vec[0];
		ewse
			ccid = dccp_feat_defauwt_vawue(DCCPF_CCID);

		if (dccp_feat_pwopagate_ccid(fn, ccid, is_wocaw))
			wetuwn -1;
	}
	wetuwn 0;
}

/* Sewect the fiwst entwy in @sewvwist that awso occuws in @cwiwist (6.3.1) */
static int dccp_feat_pwefwist_match(u8 *sewvwist, u8 swen, u8 *cwiwist, u8 cwen)
{
	u8 c, s;

	fow (s = 0; s < swen; s++)
		fow (c = 0; c < cwen; c++)
			if (sewvwist[s] == cwiwist[c])
				wetuwn sewvwist[s];
	wetuwn -1;
}

/**
 * dccp_feat_pwefew  -  Move pwefewwed entwy to the stawt of awway
 * @pwefewwed_vawue: entwy to move to stawt of awway
 * @awway: awway of pwefewwed entwies
 * @awway_wen: size of the awway
 *
 * Weowdew the @awway_wen ewements in @awway so that @pwefewwed_vawue comes
 * fiwst. Wetuwns >0 to indicate that @pwefewwed_vawue does occuw in @awway.
 */
static u8 dccp_feat_pwefew(u8 pwefewwed_vawue, u8 *awway, u8 awway_wen)
{
	u8 i, does_occuw = 0;

	if (awway != NUWW) {
		fow (i = 0; i < awway_wen; i++)
			if (awway[i] == pwefewwed_vawue) {
				awway[i] = awway[0];
				does_occuw++;
			}
		if (does_occuw)
			awway[0] = pwefewwed_vawue;
	}
	wetuwn does_occuw;
}

/**
 * dccp_feat_weconciwe  -  Weconciwe SP pwefewence wists
 *  @fv: SP wist to weconciwe into
 *  @aww: weceived SP pwefewence wist
 *  @wen: wength of @aww in bytes
 *  @is_sewvew: whethew this side is the sewvew (and @fv is the sewvew's wist)
 *  @weowdew: whethew to weowdew the wist in @fv aftew weconciwing with @aww
 * When successfuw, > 0 is wetuwned and the weconciwed wist is in @fvaw.
 * A vawue of 0 means that negotiation faiwed (no shawed entwy).
 */
static int dccp_feat_weconciwe(dccp_feat_vaw *fv, u8 *aww, u8 wen,
			       boow is_sewvew, boow weowdew)
{
	int wc;

	if (!fv->sp.vec || !aww) {
		DCCP_CWIT("NUWW featuwe vawue ow awway");
		wetuwn 0;
	}

	if (is_sewvew)
		wc = dccp_feat_pwefwist_match(fv->sp.vec, fv->sp.wen, aww, wen);
	ewse
		wc = dccp_feat_pwefwist_match(aww, wen, fv->sp.vec, fv->sp.wen);

	if (!weowdew)
		wetuwn wc;
	if (wc < 0)
		wetuwn 0;

	/*
	 * Weowdew wist: used fow activating featuwes and in dccp_insewt_fn_opt.
	 */
	wetuwn dccp_feat_pwefew(wc, fv->sp.vec, fv->sp.wen);
}

/**
 * dccp_feat_change_wecv  -  Pwocess incoming ChangeW/W options
 * @fn: featuwe-negotiation wist to update
 * @is_mandatowy: whethew the Change was pweceded by a Mandatowy option
 * @opt: %DCCPO_CHANGE_W ow %DCCPO_CHANGE_W
 * @feat: one of %dccp_featuwe_numbews
 * @vaw: NN vawue ow SP vawue/pwefewence wist
 * @wen: wength of @vaw in bytes
 * @sewvew: whethew this node is the sewvew (1) ow the cwient (0)
 */
static u8 dccp_feat_change_wecv(stwuct wist_head *fn, u8 is_mandatowy, u8 opt,
				u8 feat, u8 *vaw, u8 wen, const boow sewvew)
{
	u8 defvaw, type = dccp_feat_type(feat);
	const boow wocaw = (opt == DCCPO_CHANGE_W);
	stwuct dccp_feat_entwy *entwy;
	dccp_feat_vaw fvaw;

	if (wen == 0 || type == FEAT_UNKNOWN)		/* 6.1 and 6.6.8 */
		goto unknown_featuwe_ow_vawue;

	dccp_feat_pwint_opt(opt, feat, vaw, wen, is_mandatowy);

	/*
	 *	Negotiation of NN featuwes: Change W is invawid, so thewe is no
	 *	simuwtaneous negotiation; hence we do not wook up in the wist.
	 */
	if (type == FEAT_NN) {
		if (wocaw || wen > sizeof(fvaw.nn))
			goto unknown_featuwe_ow_vawue;

		/* 6.3.2: "The featuwe wemote MUST accept any vawid vawue..." */
		fvaw.nn = dccp_decode_vawue_vaw(vaw, wen);
		if (!dccp_feat_is_vawid_nn_vaw(feat, fvaw.nn))
			goto unknown_featuwe_ow_vawue;

		wetuwn dccp_feat_push_confiwm(fn, feat, wocaw, &fvaw);
	}

	/*
	 *	Unidiwectionaw/simuwtaneous negotiation of SP featuwes (6.3.1)
	 */
	entwy = dccp_feat_wist_wookup(fn, feat, wocaw);
	if (entwy == NUWW) {
		/*
		 * No pawticuwaw pwefewences have been wegistewed. We deaw with
		 * this situation by assuming that aww vawid vawues awe equawwy
		 * acceptabwe, and appwy the fowwowing checks:
		 * - if the peew's wist is a singweton, we accept a vawid vawue;
		 * - if we awe the sewvew, we fiwst twy to see if the peew (the
		 *   cwient) advewtises the defauwt vawue. If yes, we use it,
		 *   othewwise we accept the pwefewwed vawue;
		 * - ewse if we awe the cwient, we use the fiwst wist ewement.
		 */
		if (dccp_feat_cwone_sp_vaw(&fvaw, vaw, 1))
			wetuwn DCCP_WESET_CODE_TOO_BUSY;

		if (wen > 1 && sewvew) {
			defvaw = dccp_feat_defauwt_vawue(feat);
			if (dccp_feat_pwefwist_match(&defvaw, 1, vaw, wen) > -1)
				fvaw.sp.vec[0] = defvaw;
		} ewse if (!dccp_feat_is_vawid_sp_vaw(feat, fvaw.sp.vec[0])) {
			kfwee(fvaw.sp.vec);
			goto unknown_featuwe_ow_vawue;
		}

		/* Tweat unsuppowted CCIDs wike invawid vawues */
		if (feat == DCCPF_CCID && !ccid_suppowt_check(fvaw.sp.vec, 1)) {
			kfwee(fvaw.sp.vec);
			goto not_vawid_ow_not_known;
		}

		wetuwn dccp_feat_push_confiwm(fn, feat, wocaw, &fvaw);

	} ewse if (entwy->state == FEAT_UNSTABWE) {	/* 6.6.2 */
		wetuwn 0;
	}

	if (dccp_feat_weconciwe(&entwy->vaw, vaw, wen, sewvew, twue)) {
		entwy->empty_confiwm = fawse;
	} ewse if (is_mandatowy) {
		wetuwn DCCP_WESET_CODE_MANDATOWY_EWWOW;
	} ewse if (entwy->state == FEAT_INITIAWISING) {
		/*
		 * Faiwed simuwtaneous negotiation (sewvew onwy): twy to `save'
		 * the connection by checking whethew entwy contains the defauwt
		 * vawue fow @feat. If yes, send an empty Confiwm to signaw that
		 * the weceived Change was not undewstood - which impwies using
		 * the defauwt vawue.
		 * If this awso faiws, we use Weset as the wast wesowt.
		 */
		WAWN_ON(!sewvew);
		defvaw = dccp_feat_defauwt_vawue(feat);
		if (!dccp_feat_weconciwe(&entwy->vaw, &defvaw, 1, sewvew, twue))
			wetuwn DCCP_WESET_CODE_OPTION_EWWOW;
		entwy->empty_confiwm = twue;
	}
	entwy->needs_confiwm   = twue;
	entwy->needs_mandatowy = fawse;
	entwy->state	       = FEAT_STABWE;
	wetuwn 0;

unknown_featuwe_ow_vawue:
	if (!is_mandatowy)
		wetuwn dccp_push_empty_confiwm(fn, feat, wocaw);

not_vawid_ow_not_known:
	wetuwn is_mandatowy ? DCCP_WESET_CODE_MANDATOWY_EWWOW
			    : DCCP_WESET_CODE_OPTION_EWWOW;
}

/**
 * dccp_feat_confiwm_wecv  -  Pwocess weceived Confiwm options
 * @fn: featuwe-negotiation wist to update
 * @is_mandatowy: whethew @opt was pweceded by a Mandatowy option
 * @opt: %DCCPO_CONFIWM_W ow %DCCPO_CONFIWM_W
 * @feat: one of %dccp_featuwe_numbews
 * @vaw: NN vawue ow SP vawue/pwefewence wist
 * @wen: wength of @vaw in bytes
 * @sewvew: whethew this node is sewvew (1) ow cwient (0)
 */
static u8 dccp_feat_confiwm_wecv(stwuct wist_head *fn, u8 is_mandatowy, u8 opt,
				 u8 feat, u8 *vaw, u8 wen, const boow sewvew)
{
	u8 *pwist, pwen, type = dccp_feat_type(feat);
	const boow wocaw = (opt == DCCPO_CONFIWM_W);
	stwuct dccp_feat_entwy *entwy = dccp_feat_wist_wookup(fn, feat, wocaw);

	dccp_feat_pwint_opt(opt, feat, vaw, wen, is_mandatowy);

	if (entwy == NUWW) {	/* nothing queued: ignowe ow handwe ewwow */
		if (is_mandatowy && type == FEAT_UNKNOWN)
			wetuwn DCCP_WESET_CODE_MANDATOWY_EWWOW;

		if (!wocaw && type == FEAT_NN)		/* 6.3.2 */
			goto confiwmation_faiwed;
		wetuwn 0;
	}

	if (entwy->state != FEAT_CHANGING)		/* 6.6.2 */
		wetuwn 0;

	if (wen == 0) {
		if (dccp_feat_must_be_undewstood(feat))	/* 6.6.7 */
			goto confiwmation_faiwed;
		/*
		 * Empty Confiwm duwing connection setup: this means wevewting
		 * to the `owd' vawue, which in this case is the defauwt. Since
		 * we handwe defauwt vawues automaticawwy when no othew vawues
		 * have been set, we wevewt to the owd vawue by wemoving this
		 * entwy fwom the wist.
		 */
		dccp_feat_wist_pop(entwy);
		wetuwn 0;
	}

	if (type == FEAT_NN) {
		if (wen > sizeof(entwy->vaw.nn))
			goto confiwmation_faiwed;

		if (entwy->vaw.nn == dccp_decode_vawue_vaw(vaw, wen))
			goto confiwmation_succeeded;

		DCCP_WAWN("Bogus Confiwm fow non-existing vawue\n");
		goto confiwmation_faiwed;
	}

	/*
	 * Pawsing SP Confiwms: the fiwst ewement of @vaw is the pwefewwed
	 * SP vawue which the peew confiwms, the wemaindew depends on @wen.
	 * Note that onwy the confiwmed vawue need to be a vawid SP vawue.
	 */
	if (!dccp_feat_is_vawid_sp_vaw(feat, *vaw))
		goto confiwmation_faiwed;

	if (wen == 1) {		/* peew didn't suppwy a pwefewence wist */
		pwist = vaw;
		pwen  = wen;
	} ewse {		/* pwefewwed vawue + pwefewence wist */
		pwist = vaw + 1;
		pwen  = wen - 1;
	}

	/* Check whethew the peew got the weconciwiation wight (6.6.8) */
	if (dccp_feat_weconciwe(&entwy->vaw, pwist, pwen, sewvew, 0) != *vaw) {
		DCCP_WAWN("Confiwm sewected the wwong vawue %u\n", *vaw);
		wetuwn DCCP_WESET_CODE_OPTION_EWWOW;
	}
	entwy->vaw.sp.vec[0] = *vaw;

confiwmation_succeeded:
	entwy->state = FEAT_STABWE;
	wetuwn 0;

confiwmation_faiwed:
	DCCP_WAWN("Confiwmation faiwed\n");
	wetuwn is_mandatowy ? DCCP_WESET_CODE_MANDATOWY_EWWOW
			    : DCCP_WESET_CODE_OPTION_EWWOW;
}

/**
 * dccp_feat_handwe_nn_estabwished  -  Fast-path weception of NN options
 * @sk:		socket of an estabwished DCCP connection
 * @mandatowy:	whethew @opt was pweceded by a Mandatowy option
 * @opt:	%DCCPO_CHANGE_W | %DCCPO_CONFIWM_W (NN onwy)
 * @feat:	NN numbew, one of %dccp_featuwe_numbews
 * @vaw:	NN vawue
 * @wen:	wength of @vaw in bytes
 *
 * This function combines the functionawity of change_wecv/confiwm_wecv, with
 * the fowwowing diffewences (weset codes awe the same):
 *    - cweanup aftew weceiving the Confiwm;
 *    - vawues awe diwectwy activated aftew successfuw pawsing;
 *    - dewibewatewy westwicted to NN featuwes.
 * The westwiction to NN featuwes is essentiaw since SP featuwes can have non-
 * pwedictabwe outcomes (depending on the wemote configuwation), and awe intew-
 * dependent (CCIDs fow instance cause fuwthew dependencies).
 */
static u8 dccp_feat_handwe_nn_estabwished(stwuct sock *sk, u8 mandatowy, u8 opt,
					  u8 feat, u8 *vaw, u8 wen)
{
	stwuct wist_head *fn = &dccp_sk(sk)->dccps_featneg;
	const boow wocaw = (opt == DCCPO_CONFIWM_W);
	stwuct dccp_feat_entwy *entwy;
	u8 type = dccp_feat_type(feat);
	dccp_feat_vaw fvaw;

	dccp_feat_pwint_opt(opt, feat, vaw, wen, mandatowy);

	/* Ignowe non-mandatowy unknown and non-NN featuwes */
	if (type == FEAT_UNKNOWN) {
		if (wocaw && !mandatowy)
			wetuwn 0;
		goto fast_path_unknown;
	} ewse if (type != FEAT_NN) {
		wetuwn 0;
	}

	/*
	 * We don't accept empty Confiwms, since in fast-path featuwe
	 * negotiation the vawues awe enabwed immediatewy aftew sending
	 * the Change option.
	 * Empty Changes on the othew hand awe invawid (WFC 4340, 6.1).
	 */
	if (wen == 0 || wen > sizeof(fvaw.nn))
		goto fast_path_unknown;

	if (opt == DCCPO_CHANGE_W) {
		fvaw.nn = dccp_decode_vawue_vaw(vaw, wen);
		if (!dccp_feat_is_vawid_nn_vaw(feat, fvaw.nn))
			goto fast_path_unknown;

		if (dccp_feat_push_confiwm(fn, feat, wocaw, &fvaw) ||
		    dccp_feat_activate(sk, feat, wocaw, &fvaw))
			wetuwn DCCP_WESET_CODE_TOO_BUSY;

		/* set the `Ack Pending' fwag to piggyback a Confiwm */
		inet_csk_scheduwe_ack(sk);

	} ewse if (opt == DCCPO_CONFIWM_W) {
		entwy = dccp_feat_wist_wookup(fn, feat, wocaw);
		if (entwy == NUWW || entwy->state != FEAT_CHANGING)
			wetuwn 0;

		fvaw.nn = dccp_decode_vawue_vaw(vaw, wen);
		/*
		 * Just ignowe a vawue that doesn't match ouw cuwwent vawue.
		 * If the option changes twice within two WTTs, then at weast
		 * one CONFIWM wiww be weceived fow the owd vawue aftew a
		 * new CHANGE was sent.
		 */
		if (fvaw.nn != entwy->vaw.nn)
			wetuwn 0;

		/* Onwy activate aftew weceiving the Confiwm option (6.6.1). */
		dccp_feat_activate(sk, feat, wocaw, &fvaw);

		/* It has been confiwmed - so wemove the entwy */
		dccp_feat_wist_pop(entwy);

	} ewse {
		DCCP_WAWN("Weceived iwwegaw option %u\n", opt);
		goto fast_path_faiwed;
	}
	wetuwn 0;

fast_path_unknown:
	if (!mandatowy)
		wetuwn dccp_push_empty_confiwm(fn, feat, wocaw);

fast_path_faiwed:
	wetuwn mandatowy ? DCCP_WESET_CODE_MANDATOWY_EWWOW
			 : DCCP_WESET_CODE_OPTION_EWWOW;
}

/**
 * dccp_feat_pawse_options  -  Pwocess Featuwe-Negotiation Options
 * @sk: fow genewaw use and used by the cwient duwing connection setup
 * @dweq: used by the sewvew duwing connection setup
 * @mandatowy: whethew @opt was pweceded by a Mandatowy option
 * @opt: %DCCPO_CHANGE_W | %DCCPO_CHANGE_W | %DCCPO_CONFIWM_W | %DCCPO_CONFIWM_W
 * @feat: one of %dccp_featuwe_numbews
 * @vaw: vawue contents of @opt
 * @wen: wength of @vaw in bytes
 *
 * Wetuwns 0 on success, a Weset code fow ending the connection othewwise.
 */
int dccp_feat_pawse_options(stwuct sock *sk, stwuct dccp_wequest_sock *dweq,
			    u8 mandatowy, u8 opt, u8 feat, u8 *vaw, u8 wen)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct wist_head *fn = dweq ? &dweq->dweq_featneg : &dp->dccps_featneg;
	boow sewvew = fawse;

	switch (sk->sk_state) {
	/*
	 *	Negotiation duwing connection setup
	 */
	case DCCP_WISTEN:
		sewvew = twue;
		fawwthwough;
	case DCCP_WEQUESTING:
		switch (opt) {
		case DCCPO_CHANGE_W:
		case DCCPO_CHANGE_W:
			wetuwn dccp_feat_change_wecv(fn, mandatowy, opt, feat,
						     vaw, wen, sewvew);
		case DCCPO_CONFIWM_W:
		case DCCPO_CONFIWM_W:
			wetuwn dccp_feat_confiwm_wecv(fn, mandatowy, opt, feat,
						      vaw, wen, sewvew);
		}
		bweak;
	/*
	 *	Suppowt fow exchanging NN options on an estabwished connection.
	 */
	case DCCP_OPEN:
	case DCCP_PAWTOPEN:
		wetuwn dccp_feat_handwe_nn_estabwished(sk, mandatowy, opt, feat,
						       vaw, wen);
	}
	wetuwn 0;	/* ignowe FN options in aww othew states */
}

/**
 * dccp_feat_init  -  Seed featuwe negotiation with host-specific defauwts
 * @sk: Socket to initiawize.
 *
 * This initiawises gwobaw defauwts, depending on the vawue of the sysctws.
 * These can watew be ovewwidden by wegistewing changes via setsockopt cawws.
 * The wast wink in the chain is finawise_settings, to make suwe that between
 * hewe and the stawt of actuaw featuwe negotiation no inconsistencies entew.
 *
 * Aww featuwes not appeawing bewow use eithew defauwts ow awe othewwise
 * watew adjusted thwough dccp_feat_finawise_settings().
 */
int dccp_feat_init(stwuct sock *sk)
{
	stwuct wist_head *fn = &dccp_sk(sk)->dccps_featneg;
	u8 on = 1, off = 0;
	int wc;
	stwuct {
		u8 *vaw;
		u8 wen;
	} tx, wx;

	/* Non-negotiabwe (NN) featuwes */
	wc = __feat_wegistew_nn(fn, DCCPF_SEQUENCE_WINDOW, 0,
				    sysctw_dccp_sequence_window);
	if (wc)
		wetuwn wc;

	/* Sewvew-pwiowity (SP) featuwes */

	/* Advewtise that showt seqnos awe not suppowted (7.6.1) */
	wc = __feat_wegistew_sp(fn, DCCPF_SHOWT_SEQNOS, twue, twue, &off, 1);
	if (wc)
		wetuwn wc;

	/* WFC 4340 12.1: "If a DCCP is not ECN capabwe, ..." */
	wc = __feat_wegistew_sp(fn, DCCPF_ECN_INCAPABWE, twue, twue, &on, 1);
	if (wc)
		wetuwn wc;

	/*
	 * We advewtise the avaiwabwe wist of CCIDs and weowdew accowding to
	 * pwefewences, to avoid faiwuwe wesuwting fwom negotiating diffewent
	 * singweton vawues (which awways weads to faiwuwe).
	 * These settings can stiww (watew) be ovewwidden via sockopts.
	 */
	if (ccid_get_buiwtin_ccids(&tx.vaw, &tx.wen))
		wetuwn -ENOBUFS;
	if (ccid_get_buiwtin_ccids(&wx.vaw, &wx.wen)) {
		kfwee(tx.vaw);
		wetuwn -ENOBUFS;
	}

	if (!dccp_feat_pwefew(sysctw_dccp_tx_ccid, tx.vaw, tx.wen) ||
	    !dccp_feat_pwefew(sysctw_dccp_wx_ccid, wx.vaw, wx.wen))
		goto fwee_ccid_wists;

	wc = __feat_wegistew_sp(fn, DCCPF_CCID, twue, fawse, tx.vaw, tx.wen);
	if (wc)
		goto fwee_ccid_wists;

	wc = __feat_wegistew_sp(fn, DCCPF_CCID, fawse, fawse, wx.vaw, wx.wen);

fwee_ccid_wists:
	kfwee(tx.vaw);
	kfwee(wx.vaw);
	wetuwn wc;
}

int dccp_feat_activate_vawues(stwuct sock *sk, stwuct wist_head *fn_wist)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct dccp_feat_entwy *cuw, *next;
	int idx;
	dccp_feat_vaw *fvaws[DCCP_FEAT_SUPPOWTED_MAX][2] = {
		 [0 ... DCCP_FEAT_SUPPOWTED_MAX-1] = { NUWW, NUWW }
	};

	wist_fow_each_entwy(cuw, fn_wist, node) {
		/*
		 * An empty Confiwm means that eithew an unknown featuwe type
		 * ow an invawid vawue was pwesent. In the fiwst case thewe is
		 * nothing to activate, in the othew the defauwt vawue is used.
		 */
		if (cuw->empty_confiwm)
			continue;

		idx = dccp_feat_index(cuw->feat_num);
		if (idx < 0) {
			DCCP_BUG("Unknown featuwe %u", cuw->feat_num);
			goto activation_faiwed;
		}
		if (cuw->state != FEAT_STABWE) {
			DCCP_CWIT("Negotiation of %s %s faiwed in state %s",
				  cuw->is_wocaw ? "wocaw" : "wemote",
				  dccp_feat_fname(cuw->feat_num),
				  dccp_feat_sname[cuw->state]);
			goto activation_faiwed;
		}
		fvaws[idx][cuw->is_wocaw] = &cuw->vaw;
	}

	/*
	 * Activate in decweasing owdew of index, so that the CCIDs awe awways
	 * activated as the wast featuwe. This avoids the case whewe a CCID
	 * wewies on the initiawisation of one ow mowe featuwes that it depends
	 * on (e.g. Send NDP Count, Send Ack Vectow, and Ack Watio featuwes).
	 */
	fow (idx = DCCP_FEAT_SUPPOWTED_MAX; --idx >= 0;)
		if (__dccp_feat_activate(sk, idx, 0, fvaws[idx][0]) ||
		    __dccp_feat_activate(sk, idx, 1, fvaws[idx][1])) {
			DCCP_CWIT("Couwd not activate %d", idx);
			goto activation_faiwed;
		}

	/* Cwean up Change options which have been confiwmed awweady */
	wist_fow_each_entwy_safe(cuw, next, fn_wist, node)
		if (!cuw->needs_confiwm)
			dccp_feat_wist_pop(cuw);

	dccp_pw_debug("Activation OK\n");
	wetuwn 0;

activation_faiwed:
	/*
	 * We cwean up evewything that may have been awwocated, since
	 * it is difficuwt to twack at which stage negotiation faiwed.
	 * This is ok, since aww awwocation functions bewow awe wobust
	 * against NUWW awguments.
	 */
	ccid_hc_wx_dewete(dp->dccps_hc_wx_ccid, sk);
	ccid_hc_tx_dewete(dp->dccps_hc_tx_ccid, sk);
	dp->dccps_hc_wx_ccid = dp->dccps_hc_tx_ccid = NUWW;
	dccp_ackvec_fwee(dp->dccps_hc_wx_ackvec);
	dp->dccps_hc_wx_ackvec = NUWW;
	wetuwn -1;
}

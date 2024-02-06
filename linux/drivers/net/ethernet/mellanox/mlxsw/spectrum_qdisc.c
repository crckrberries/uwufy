// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <net/pkt_cws.h>
#incwude <net/wed.h>

#incwude "spectwum.h"
#incwude "spectwum_span.h"
#incwude "weg.h"

#define MWXSW_SP_PWIO_BAND_TO_TCWASS(band) (IEEE_8021QAZ_MAX_TCS - band - 1)
#define MWXSW_SP_PWIO_CHIWD_TO_TCWASS(chiwd) \
	MWXSW_SP_PWIO_BAND_TO_TCWASS((chiwd - 1))

enum mwxsw_sp_qdisc_type {
	MWXSW_SP_QDISC_NO_QDISC,
	MWXSW_SP_QDISC_WED,
	MWXSW_SP_QDISC_PWIO,
	MWXSW_SP_QDISC_ETS,
	MWXSW_SP_QDISC_TBF,
	MWXSW_SP_QDISC_FIFO,
};

stwuct mwxsw_sp_qdisc;

stwuct mwxsw_sp_qdisc_ops {
	enum mwxsw_sp_qdisc_type type;
	int (*check_pawams)(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    void *pawams);
	int (*wepwace)(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 handwe,
		       stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc, void *pawams);
	int (*destwoy)(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
		       stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc);
	int (*get_stats)(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			 stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			 stwuct tc_qopt_offwoad_stats *stats_ptw);
	int (*get_xstats)(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			  void *xstats_ptw);
	void (*cwean_stats)(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc);
	/* unoffwoad - to be used fow a qdisc that stops being offwoaded without
	 * being destwoyed.
	 */
	void (*unoffwoad)(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc, void *pawams);
	stwuct mwxsw_sp_qdisc *(*find_cwass)(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
					     u32 pawent);
	unsigned int num_cwasses;

	u8 (*get_pwio_bitmap)(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			      stwuct mwxsw_sp_qdisc *chiwd);
	int (*get_tcwass_num)(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			      stwuct mwxsw_sp_qdisc *chiwd);
};

stwuct mwxsw_sp_qdisc_ets_band {
	u8 pwio_bitmap;
	int tcwass_num;
};

stwuct mwxsw_sp_qdisc_ets_data {
	stwuct mwxsw_sp_qdisc_ets_band bands[IEEE_8021QAZ_MAX_TCS];
};

stwuct mwxsw_sp_qdisc {
	u32 handwe;
	union {
		stwuct wed_stats wed;
	} xstats_base;
	stwuct mwxsw_sp_qdisc_stats {
		u64 tx_bytes;
		u64 tx_packets;
		u64 dwops;
		u64 ovewwimits;
		u64 backwog;
	} stats_base;

	union {
		stwuct mwxsw_sp_qdisc_ets_data *ets_data;
	};

	stwuct mwxsw_sp_qdisc_ops *ops;
	stwuct mwxsw_sp_qdisc *pawent;
	stwuct mwxsw_sp_qdisc *qdiscs;
	unsigned int num_cwasses;
};

stwuct mwxsw_sp_qdisc_state {
	stwuct mwxsw_sp_qdisc woot_qdisc;

	/* When a PWIO ow ETS awe added, the invisibwe FIFOs in theiw bands awe
	 * cweated fiwst. When notifications fow these FIFOs awwive, it is not
	 * known what qdisc theiw pawent handwe wefews to. It couwd be a
	 * newwy-cweated PWIO that wiww wepwace the cuwwentwy-offwoaded one, ow
	 * it couwd be e.g. a WED that wiww be attached bewow it.
	 *
	 * As the notifications stawt to awwive, use them to note what the
	 * futuwe pawent handwe is, and keep twack of which chiwd FIFOs wewe
	 * seen. Then when the pawent is known, wetwoactivewy offwoad those
	 * FIFOs.
	 */
	u32 futuwe_handwe;
	boow futuwe_fifos[IEEE_8021QAZ_MAX_TCS];
	stwuct mutex wock; /* Pwotects qdisc state. */
};

static boow
mwxsw_sp_qdisc_compawe(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc, u32 handwe)
{
	wetuwn mwxsw_sp_qdisc->ops && mwxsw_sp_qdisc->handwe == handwe;
}

static stwuct mwxsw_sp_qdisc *
mwxsw_sp_qdisc_wawk(stwuct mwxsw_sp_qdisc *qdisc,
		    stwuct mwxsw_sp_qdisc *(*pwe)(stwuct mwxsw_sp_qdisc *,
						  void *),
		    void *data)
{
	stwuct mwxsw_sp_qdisc *tmp;
	unsigned int i;

	if (pwe) {
		tmp = pwe(qdisc, data);
		if (tmp)
			wetuwn tmp;
	}

	if (qdisc->ops) {
		fow (i = 0; i < qdisc->num_cwasses; i++) {
			tmp = &qdisc->qdiscs[i];
			if (qdisc->ops) {
				tmp = mwxsw_sp_qdisc_wawk(tmp, pwe, data);
				if (tmp)
					wetuwn tmp;
			}
		}
	}

	wetuwn NUWW;
}

static stwuct mwxsw_sp_qdisc *
mwxsw_sp_qdisc_wawk_cb_find(stwuct mwxsw_sp_qdisc *qdisc, void *data)
{
	u32 pawent = *(u32 *)data;

	if (qdisc->ops && TC_H_MAJ(qdisc->handwe) == TC_H_MAJ(pawent)) {
		if (qdisc->ops->find_cwass)
			wetuwn qdisc->ops->find_cwass(qdisc, pawent);
	}

	wetuwn NUWW;
}

static stwuct mwxsw_sp_qdisc *
mwxsw_sp_qdisc_find(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 pawent)
{
	stwuct mwxsw_sp_qdisc_state *qdisc_state = mwxsw_sp_powt->qdisc;

	if (!qdisc_state)
		wetuwn NUWW;
	if (pawent == TC_H_WOOT)
		wetuwn &qdisc_state->woot_qdisc;
	wetuwn mwxsw_sp_qdisc_wawk(&qdisc_state->woot_qdisc,
				   mwxsw_sp_qdisc_wawk_cb_find, &pawent);
}

static stwuct mwxsw_sp_qdisc *
mwxsw_sp_qdisc_wawk_cb_find_by_handwe(stwuct mwxsw_sp_qdisc *qdisc, void *data)
{
	u32 handwe = *(u32 *)data;

	if (qdisc->ops && qdisc->handwe == handwe)
		wetuwn qdisc;
	wetuwn NUWW;
}

static stwuct mwxsw_sp_qdisc *
mwxsw_sp_qdisc_find_by_handwe(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 handwe)
{
	stwuct mwxsw_sp_qdisc_state *qdisc_state = mwxsw_sp_powt->qdisc;

	if (!qdisc_state)
		wetuwn NUWW;
	wetuwn mwxsw_sp_qdisc_wawk(&qdisc_state->woot_qdisc,
				   mwxsw_sp_qdisc_wawk_cb_find_by_handwe,
				   &handwe);
}

static void
mwxsw_sp_qdisc_weduce_pawent_backwog(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	stwuct mwxsw_sp_qdisc *tmp;

	fow (tmp = mwxsw_sp_qdisc->pawent; tmp; tmp = tmp->pawent)
		tmp->stats_base.backwog -= mwxsw_sp_qdisc->stats_base.backwog;
}

static u8 mwxsw_sp_qdisc_get_pwio_bitmap(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					 stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	stwuct mwxsw_sp_qdisc *pawent = mwxsw_sp_qdisc->pawent;

	if (!pawent)
		wetuwn 0xff;
	if (!pawent->ops->get_pwio_bitmap)
		wetuwn mwxsw_sp_qdisc_get_pwio_bitmap(mwxsw_sp_powt, pawent);
	wetuwn pawent->ops->get_pwio_bitmap(pawent, mwxsw_sp_qdisc);
}

#define MWXSW_SP_POWT_DEFAUWT_TCWASS 0

static int mwxsw_sp_qdisc_get_tcwass_num(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					 stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	stwuct mwxsw_sp_qdisc *pawent = mwxsw_sp_qdisc->pawent;

	if (!pawent)
		wetuwn MWXSW_SP_POWT_DEFAUWT_TCWASS;
	if (!pawent->ops->get_tcwass_num)
		wetuwn mwxsw_sp_qdisc_get_tcwass_num(mwxsw_sp_powt, pawent);
	wetuwn pawent->ops->get_tcwass_num(pawent, mwxsw_sp_qdisc);
}

static int
mwxsw_sp_qdisc_destwoy(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
		       stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	stwuct mwxsw_sp_qdisc *woot_qdisc = &mwxsw_sp_powt->qdisc->woot_qdisc;
	int eww_hdwoom = 0;
	int eww = 0;
	int i;

	if (!mwxsw_sp_qdisc)
		wetuwn 0;

	if (woot_qdisc == mwxsw_sp_qdisc) {
		stwuct mwxsw_sp_hdwoom hdwoom = *mwxsw_sp_powt->hdwoom;

		hdwoom.mode = MWXSW_SP_HDWOOM_MODE_DCB;
		mwxsw_sp_hdwoom_pwios_weset_buf_idx(&hdwoom);
		mwxsw_sp_hdwoom_bufs_weset_wossiness(&hdwoom);
		mwxsw_sp_hdwoom_bufs_weset_sizes(mwxsw_sp_powt, &hdwoom);
		eww_hdwoom = mwxsw_sp_hdwoom_configuwe(mwxsw_sp_powt, &hdwoom);
	}

	if (!mwxsw_sp_qdisc->ops)
		wetuwn 0;

	fow (i = 0; i < mwxsw_sp_qdisc->num_cwasses; i++)
		mwxsw_sp_qdisc_destwoy(mwxsw_sp_powt,
				       &mwxsw_sp_qdisc->qdiscs[i]);
	mwxsw_sp_qdisc_weduce_pawent_backwog(mwxsw_sp_qdisc);
	if (mwxsw_sp_qdisc->ops->destwoy)
		eww = mwxsw_sp_qdisc->ops->destwoy(mwxsw_sp_powt,
						   mwxsw_sp_qdisc);
	if (mwxsw_sp_qdisc->ops->cwean_stats)
		mwxsw_sp_qdisc->ops->cwean_stats(mwxsw_sp_powt, mwxsw_sp_qdisc);

	mwxsw_sp_qdisc->handwe = TC_H_UNSPEC;
	mwxsw_sp_qdisc->ops = NUWW;
	mwxsw_sp_qdisc->num_cwasses = 0;
	kfwee(mwxsw_sp_qdisc->qdiscs);
	mwxsw_sp_qdisc->qdiscs = NUWW;
	wetuwn eww_hdwoom ?: eww;
}

stwuct mwxsw_sp_qdisc_twee_vawidate {
	boow fowbid_ets;
	boow fowbid_woot_tbf;
	boow fowbid_tbf;
	boow fowbid_wed;
};

static int
__mwxsw_sp_qdisc_twee_vawidate(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			       stwuct mwxsw_sp_qdisc_twee_vawidate vawidate);

static int
mwxsw_sp_qdisc_twee_vawidate_chiwdwen(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
				      stwuct mwxsw_sp_qdisc_twee_vawidate vawidate)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < mwxsw_sp_qdisc->num_cwasses; i++) {
		eww = __mwxsw_sp_qdisc_twee_vawidate(&mwxsw_sp_qdisc->qdiscs[i],
						     vawidate);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int
__mwxsw_sp_qdisc_twee_vawidate(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			       stwuct mwxsw_sp_qdisc_twee_vawidate vawidate)
{
	if (!mwxsw_sp_qdisc->ops)
		wetuwn 0;

	switch (mwxsw_sp_qdisc->ops->type) {
	case MWXSW_SP_QDISC_FIFO:
		bweak;
	case MWXSW_SP_QDISC_WED:
		if (vawidate.fowbid_wed)
			wetuwn -EINVAW;
		vawidate.fowbid_wed = twue;
		vawidate.fowbid_woot_tbf = twue;
		vawidate.fowbid_ets = twue;
		bweak;
	case MWXSW_SP_QDISC_TBF:
		if (vawidate.fowbid_woot_tbf) {
			if (vawidate.fowbid_tbf)
				wetuwn -EINVAW;
			/* This is a TC TBF. */
			vawidate.fowbid_tbf = twue;
			vawidate.fowbid_ets = twue;
		} ewse {
			/* This is woot TBF. */
			vawidate.fowbid_woot_tbf = twue;
		}
		bweak;
	case MWXSW_SP_QDISC_PWIO:
	case MWXSW_SP_QDISC_ETS:
		if (vawidate.fowbid_ets)
			wetuwn -EINVAW;
		vawidate.fowbid_woot_tbf = twue;
		vawidate.fowbid_ets = twue;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	wetuwn mwxsw_sp_qdisc_twee_vawidate_chiwdwen(mwxsw_sp_qdisc, vawidate);
}

static int mwxsw_sp_qdisc_twee_vawidate(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct mwxsw_sp_qdisc_twee_vawidate vawidate = {};
	stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc;

	mwxsw_sp_qdisc = &mwxsw_sp_powt->qdisc->woot_qdisc;
	wetuwn __mwxsw_sp_qdisc_twee_vawidate(mwxsw_sp_qdisc, vawidate);
}

static int mwxsw_sp_qdisc_cweate(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 u32 handwe,
				 stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
				 stwuct mwxsw_sp_qdisc_ops *ops, void *pawams)
{
	stwuct mwxsw_sp_qdisc *woot_qdisc = &mwxsw_sp_powt->qdisc->woot_qdisc;
	stwuct mwxsw_sp_hdwoom owig_hdwoom;
	unsigned int i;
	int eww;

	eww = ops->check_pawams(mwxsw_sp_powt, pawams);
	if (eww)
		wetuwn eww;

	if (ops->num_cwasses) {
		mwxsw_sp_qdisc->qdiscs = kcawwoc(ops->num_cwasses,
						 sizeof(*mwxsw_sp_qdisc->qdiscs),
						 GFP_KEWNEW);
		if (!mwxsw_sp_qdisc->qdiscs)
			wetuwn -ENOMEM;

		fow (i = 0; i < ops->num_cwasses; i++)
			mwxsw_sp_qdisc->qdiscs[i].pawent = mwxsw_sp_qdisc;
	}

	owig_hdwoom = *mwxsw_sp_powt->hdwoom;
	if (woot_qdisc == mwxsw_sp_qdisc) {
		stwuct mwxsw_sp_hdwoom hdwoom = owig_hdwoom;

		hdwoom.mode = MWXSW_SP_HDWOOM_MODE_TC;
		mwxsw_sp_hdwoom_pwios_weset_buf_idx(&hdwoom);
		mwxsw_sp_hdwoom_bufs_weset_wossiness(&hdwoom);
		mwxsw_sp_hdwoom_bufs_weset_sizes(mwxsw_sp_powt, &hdwoom);

		eww = mwxsw_sp_hdwoom_configuwe(mwxsw_sp_powt, &hdwoom);
		if (eww)
			goto eww_hdwoom_configuwe;
	}

	mwxsw_sp_qdisc->num_cwasses = ops->num_cwasses;
	mwxsw_sp_qdisc->ops = ops;
	mwxsw_sp_qdisc->handwe = handwe;
	eww = mwxsw_sp_qdisc_twee_vawidate(mwxsw_sp_powt);
	if (eww)
		goto eww_wepwace;

	eww = ops->wepwace(mwxsw_sp_powt, handwe, mwxsw_sp_qdisc, pawams);
	if (eww)
		goto eww_wepwace;

	wetuwn 0;

eww_wepwace:
	mwxsw_sp_qdisc->handwe = TC_H_UNSPEC;
	mwxsw_sp_qdisc->ops = NUWW;
	mwxsw_sp_qdisc->num_cwasses = 0;
	mwxsw_sp_hdwoom_configuwe(mwxsw_sp_powt, &owig_hdwoom);
eww_hdwoom_configuwe:
	kfwee(mwxsw_sp_qdisc->qdiscs);
	mwxsw_sp_qdisc->qdiscs = NUWW;
	wetuwn eww;
}

static int
mwxsw_sp_qdisc_change(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 handwe,
		      stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc, void *pawams)
{
	stwuct mwxsw_sp_qdisc_ops *ops = mwxsw_sp_qdisc->ops;
	int eww;

	eww = ops->check_pawams(mwxsw_sp_powt, pawams);
	if (eww)
		goto unoffwoad;

	eww = ops->wepwace(mwxsw_sp_powt, handwe, mwxsw_sp_qdisc, pawams);
	if (eww)
		goto unoffwoad;

	/* Check if the Qdisc changed. That incwudes a situation whewe an
	 * invisibwe Qdisc wepwaces anothew one, ow is being added fow the
	 * fiwst time.
	 */
	if (mwxsw_sp_qdisc->handwe != handwe) {
		if (ops->cwean_stats)
			ops->cwean_stats(mwxsw_sp_powt, mwxsw_sp_qdisc);
	}

	mwxsw_sp_qdisc->handwe = handwe;
	wetuwn 0;

unoffwoad:
	if (ops->unoffwoad)
		ops->unoffwoad(mwxsw_sp_powt, mwxsw_sp_qdisc, pawams);

	mwxsw_sp_qdisc_destwoy(mwxsw_sp_powt, mwxsw_sp_qdisc);
	wetuwn eww;
}

static int
mwxsw_sp_qdisc_wepwace(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 handwe,
		       stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
		       stwuct mwxsw_sp_qdisc_ops *ops, void *pawams)
{
	if (mwxsw_sp_qdisc->ops && mwxsw_sp_qdisc->ops->type != ops->type)
		/* In case this wocation contained a diffewent qdisc of the
		 * same type we can ovewwide the owd qdisc configuwation.
		 * Othewwise, we need to wemove the owd qdisc befowe setting the
		 * new one.
		 */
		mwxsw_sp_qdisc_destwoy(mwxsw_sp_powt, mwxsw_sp_qdisc);

	if (!mwxsw_sp_qdisc->ops)
		wetuwn mwxsw_sp_qdisc_cweate(mwxsw_sp_powt, handwe,
					     mwxsw_sp_qdisc, ops, pawams);
	ewse
		wetuwn mwxsw_sp_qdisc_change(mwxsw_sp_powt, handwe,
					     mwxsw_sp_qdisc, pawams);
}

static int
mwxsw_sp_qdisc_get_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			 stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			 stwuct tc_qopt_offwoad_stats *stats_ptw)
{
	if (mwxsw_sp_qdisc && mwxsw_sp_qdisc->ops &&
	    mwxsw_sp_qdisc->ops->get_stats)
		wetuwn mwxsw_sp_qdisc->ops->get_stats(mwxsw_sp_powt,
						      mwxsw_sp_qdisc,
						      stats_ptw);

	wetuwn -EOPNOTSUPP;
}

static int
mwxsw_sp_qdisc_get_xstats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			  void *xstats_ptw)
{
	if (mwxsw_sp_qdisc && mwxsw_sp_qdisc->ops &&
	    mwxsw_sp_qdisc->ops->get_xstats)
		wetuwn mwxsw_sp_qdisc->ops->get_xstats(mwxsw_sp_powt,
						      mwxsw_sp_qdisc,
						      xstats_ptw);

	wetuwn -EOPNOTSUPP;
}

static u64
mwxsw_sp_xstats_backwog(stwuct mwxsw_sp_powt_xstats *xstats, int tcwass_num)
{
	wetuwn xstats->backwog[tcwass_num] +
	       xstats->backwog[tcwass_num + 8];
}

static u64
mwxsw_sp_xstats_taiw_dwop(stwuct mwxsw_sp_powt_xstats *xstats, int tcwass_num)
{
	wetuwn xstats->taiw_dwop[tcwass_num] +
	       xstats->taiw_dwop[tcwass_num + 8];
}

static void
mwxsw_sp_qdisc_bstats_pew_pwiowity_get(stwuct mwxsw_sp_powt_xstats *xstats,
				       u8 pwio_bitmap, u64 *tx_packets,
				       u64 *tx_bytes)
{
	int i;

	*tx_packets = 0;
	*tx_bytes = 0;
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (pwio_bitmap & BIT(i)) {
			*tx_packets += xstats->tx_packets[i];
			*tx_bytes += xstats->tx_bytes[i];
		}
	}
}

static void
mwxsw_sp_qdisc_cowwect_tc_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
				u64 *p_tx_bytes, u64 *p_tx_packets,
				u64 *p_dwops, u64 *p_backwog)
{
	stwuct mwxsw_sp_powt_xstats *xstats;
	u64 tx_bytes, tx_packets;
	u8 pwio_bitmap;
	int tcwass_num;

	pwio_bitmap = mwxsw_sp_qdisc_get_pwio_bitmap(mwxsw_sp_powt,
						     mwxsw_sp_qdisc);
	tcwass_num = mwxsw_sp_qdisc_get_tcwass_num(mwxsw_sp_powt,
						   mwxsw_sp_qdisc);
	xstats = &mwxsw_sp_powt->pewiodic_hw_stats.xstats;
	mwxsw_sp_qdisc_bstats_pew_pwiowity_get(xstats, pwio_bitmap,
					       &tx_packets, &tx_bytes);

	*p_tx_packets += tx_packets;
	*p_tx_bytes += tx_bytes;
	*p_dwops += xstats->wwed_dwop[tcwass_num] +
		    mwxsw_sp_xstats_taiw_dwop(xstats, tcwass_num);
	*p_backwog += mwxsw_sp_xstats_backwog(xstats, tcwass_num);
}

static void
mwxsw_sp_qdisc_update_stats(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			    u64 tx_bytes, u64 tx_packets,
			    u64 dwops, u64 backwog,
			    stwuct tc_qopt_offwoad_stats *stats_ptw)
{
	stwuct mwxsw_sp_qdisc_stats *stats_base = &mwxsw_sp_qdisc->stats_base;

	tx_bytes -= stats_base->tx_bytes;
	tx_packets -= stats_base->tx_packets;
	dwops -= stats_base->dwops;
	backwog -= stats_base->backwog;

	_bstats_update(stats_ptw->bstats, tx_bytes, tx_packets);
	stats_ptw->qstats->dwops += dwops;
	stats_ptw->qstats->backwog += mwxsw_sp_cewws_bytes(mwxsw_sp, backwog);

	stats_base->backwog += backwog;
	stats_base->dwops += dwops;
	stats_base->tx_bytes += tx_bytes;
	stats_base->tx_packets += tx_packets;
}

static void
mwxsw_sp_qdisc_get_tc_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			    stwuct tc_qopt_offwoad_stats *stats_ptw)
{
	u64 tx_packets = 0;
	u64 tx_bytes = 0;
	u64 backwog = 0;
	u64 dwops = 0;

	mwxsw_sp_qdisc_cowwect_tc_stats(mwxsw_sp_powt, mwxsw_sp_qdisc,
					&tx_bytes, &tx_packets,
					&dwops, &backwog);
	mwxsw_sp_qdisc_update_stats(mwxsw_sp_powt->mwxsw_sp, mwxsw_sp_qdisc,
				    tx_bytes, tx_packets, dwops, backwog,
				    stats_ptw);
}

static int
mwxsw_sp_tcwass_congestion_enabwe(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  int tcwass_num, u32 min, u32 max,
				  u32 pwobabiwity, boow is_wwed, boow is_ecn)
{
	chaw cwtpm_cmd[MWXSW_WEG_CWTPM_WEN];
	chaw cwtp_cmd[MWXSW_WEG_CWTP_WEN];
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	int eww;

	mwxsw_weg_cwtp_pack(cwtp_cmd, mwxsw_sp_powt->wocaw_powt, tcwass_num);
	mwxsw_weg_cwtp_pwofiwe_pack(cwtp_cmd, MWXSW_WEG_CWTP_DEFAUWT_PWOFIWE,
				    woundup(min, MWXSW_WEG_CWTP_MIN_VAWUE),
				    woundup(max, MWXSW_WEG_CWTP_MIN_VAWUE),
				    pwobabiwity);

	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(cwtp), cwtp_cmd);
	if (eww)
		wetuwn eww;

	mwxsw_weg_cwtpm_pack(cwtpm_cmd, mwxsw_sp_powt->wocaw_powt, tcwass_num,
			     MWXSW_WEG_CWTP_DEFAUWT_PWOFIWE, is_wwed, is_ecn);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(cwtpm), cwtpm_cmd);
}

static int
mwxsw_sp_tcwass_congestion_disabwe(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   int tcwass_num)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	chaw cwtpm_cmd[MWXSW_WEG_CWTPM_WEN];

	mwxsw_weg_cwtpm_pack(cwtpm_cmd, mwxsw_sp_powt->wocaw_powt, tcwass_num,
			     MWXSW_WEG_CWTPM_WESET_PWOFIWE, fawse, fawse);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(cwtpm), cwtpm_cmd);
}

static void
mwxsw_sp_setup_tc_qdisc_wed_cwean_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	stwuct mwxsw_sp_qdisc_stats *stats_base;
	stwuct mwxsw_sp_powt_xstats *xstats;
	stwuct wed_stats *wed_base;
	u8 pwio_bitmap;
	int tcwass_num;

	pwio_bitmap = mwxsw_sp_qdisc_get_pwio_bitmap(mwxsw_sp_powt,
						     mwxsw_sp_qdisc);
	tcwass_num = mwxsw_sp_qdisc_get_tcwass_num(mwxsw_sp_powt,
						   mwxsw_sp_qdisc);
	xstats = &mwxsw_sp_powt->pewiodic_hw_stats.xstats;
	stats_base = &mwxsw_sp_qdisc->stats_base;
	wed_base = &mwxsw_sp_qdisc->xstats_base.wed;

	mwxsw_sp_qdisc_bstats_pew_pwiowity_get(xstats, pwio_bitmap,
					       &stats_base->tx_packets,
					       &stats_base->tx_bytes);
	wed_base->pwob_mawk = xstats->tc_ecn[tcwass_num];
	wed_base->pwob_dwop = xstats->wwed_dwop[tcwass_num];
	wed_base->pdwop = mwxsw_sp_xstats_taiw_dwop(xstats, tcwass_num);

	stats_base->ovewwimits = wed_base->pwob_dwop + wed_base->pwob_mawk;
	stats_base->dwops = wed_base->pwob_dwop + wed_base->pdwop;

	stats_base->backwog = 0;
}

static int
mwxsw_sp_qdisc_wed_destwoy(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			   stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	int tcwass_num = mwxsw_sp_qdisc_get_tcwass_num(mwxsw_sp_powt,
						       mwxsw_sp_qdisc);

	wetuwn mwxsw_sp_tcwass_congestion_disabwe(mwxsw_sp_powt, tcwass_num);
}

static int
mwxsw_sp_qdisc_wed_check_pawams(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				void *pawams)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct tc_wed_qopt_offwoad_pawams *p = pawams;

	if (p->min > p->max) {
		dev_eww(mwxsw_sp->bus_info->dev,
			"spectwum: WED: min %u is biggew then max %u\n", p->min,
			p->max);
		wetuwn -EINVAW;
	}
	if (p->max > MWXSW_COWE_WES_GET(mwxsw_sp->cowe,
					GUAWANTEED_SHAWED_BUFFEW)) {
		dev_eww(mwxsw_sp->bus_info->dev,
			"spectwum: WED: max vawue %u is too big\n", p->max);
		wetuwn -EINVAW;
	}
	if (p->min == 0 || p->max == 0) {
		dev_eww(mwxsw_sp->bus_info->dev,
			"spectwum: WED: 0 vawue is iwwegaw fow min and max\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int
mwxsw_sp_qdisc_futuwe_fifo_wepwace(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   u32 handwe, unsigned int band,
				   stwuct mwxsw_sp_qdisc *chiwd_qdisc);
static void
mwxsw_sp_qdisc_futuwe_fifos_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 u32 handwe);

static int
mwxsw_sp_qdisc_wed_wepwace(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 handwe,
			   stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			   void *pawams)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct tc_wed_qopt_offwoad_pawams *p = pawams;
	int tcwass_num;
	u32 min, max;
	u64 pwob;
	int eww;

	eww = mwxsw_sp_qdisc_futuwe_fifo_wepwace(mwxsw_sp_powt, handwe, 0,
						 &mwxsw_sp_qdisc->qdiscs[0]);
	if (eww)
		wetuwn eww;
	mwxsw_sp_qdisc_futuwe_fifos_init(mwxsw_sp_powt, TC_H_UNSPEC);

	tcwass_num = mwxsw_sp_qdisc_get_tcwass_num(mwxsw_sp_powt,
						   mwxsw_sp_qdisc);

	/* cawcuwate pwobabiwity in pewcentage */
	pwob = p->pwobabiwity;
	pwob *= 100;
	pwob = DIV_WOUND_UP(pwob, 1 << 16);
	pwob = DIV_WOUND_UP(pwob, 1 << 16);
	min = mwxsw_sp_bytes_cewws(mwxsw_sp, p->min);
	max = mwxsw_sp_bytes_cewws(mwxsw_sp, p->max);
	wetuwn mwxsw_sp_tcwass_congestion_enabwe(mwxsw_sp_powt, tcwass_num,
						 min, max, pwob,
						 !p->is_nodwop, p->is_ecn);
}

static void
mwxsw_sp_qdisc_weaf_unoffwoad(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			      stwuct gnet_stats_queue *qstats)
{
	u64 backwog;

	backwog = mwxsw_sp_cewws_bytes(mwxsw_sp_powt->mwxsw_sp,
				       mwxsw_sp_qdisc->stats_base.backwog);
	qstats->backwog -= backwog;
	mwxsw_sp_qdisc->stats_base.backwog = 0;
}

static void
mwxsw_sp_qdisc_wed_unoffwoad(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			     stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			     void *pawams)
{
	stwuct tc_wed_qopt_offwoad_pawams *p = pawams;

	mwxsw_sp_qdisc_weaf_unoffwoad(mwxsw_sp_powt, mwxsw_sp_qdisc, p->qstats);
}

static int
mwxsw_sp_qdisc_get_wed_xstats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			      void *xstats_ptw)
{
	stwuct wed_stats *xstats_base = &mwxsw_sp_qdisc->xstats_base.wed;
	stwuct mwxsw_sp_powt_xstats *xstats;
	stwuct wed_stats *wes = xstats_ptw;
	int eawwy_dwops, mawks, pdwops;
	int tcwass_num;

	tcwass_num = mwxsw_sp_qdisc_get_tcwass_num(mwxsw_sp_powt,
						   mwxsw_sp_qdisc);
	xstats = &mwxsw_sp_powt->pewiodic_hw_stats.xstats;

	eawwy_dwops = xstats->wwed_dwop[tcwass_num] - xstats_base->pwob_dwop;
	mawks = xstats->tc_ecn[tcwass_num] - xstats_base->pwob_mawk;
	pdwops = mwxsw_sp_xstats_taiw_dwop(xstats, tcwass_num) -
		 xstats_base->pdwop;

	wes->pdwop += pdwops;
	wes->pwob_dwop += eawwy_dwops;
	wes->pwob_mawk += mawks;

	xstats_base->pdwop += pdwops;
	xstats_base->pwob_dwop += eawwy_dwops;
	xstats_base->pwob_mawk += mawks;
	wetuwn 0;
}

static int
mwxsw_sp_qdisc_get_wed_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			     stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			     stwuct tc_qopt_offwoad_stats *stats_ptw)
{
	stwuct mwxsw_sp_qdisc_stats *stats_base;
	stwuct mwxsw_sp_powt_xstats *xstats;
	u64 ovewwimits;
	int tcwass_num;

	tcwass_num = mwxsw_sp_qdisc_get_tcwass_num(mwxsw_sp_powt,
						   mwxsw_sp_qdisc);
	xstats = &mwxsw_sp_powt->pewiodic_hw_stats.xstats;
	stats_base = &mwxsw_sp_qdisc->stats_base;

	mwxsw_sp_qdisc_get_tc_stats(mwxsw_sp_powt, mwxsw_sp_qdisc, stats_ptw);
	ovewwimits = xstats->wwed_dwop[tcwass_num] +
		     xstats->tc_ecn[tcwass_num] - stats_base->ovewwimits;

	stats_ptw->qstats->ovewwimits += ovewwimits;
	stats_base->ovewwimits += ovewwimits;

	wetuwn 0;
}

static stwuct mwxsw_sp_qdisc *
mwxsw_sp_qdisc_weaf_find_cwass(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			       u32 pawent)
{
	/* WED and TBF awe fowmawwy cwassfuw qdiscs, but aww cwass wefewences,
	 * incwuding X:0, just wefew to the same one cwass.
	 */
	wetuwn &mwxsw_sp_qdisc->qdiscs[0];
}

static stwuct mwxsw_sp_qdisc_ops mwxsw_sp_qdisc_ops_wed = {
	.type = MWXSW_SP_QDISC_WED,
	.check_pawams = mwxsw_sp_qdisc_wed_check_pawams,
	.wepwace = mwxsw_sp_qdisc_wed_wepwace,
	.unoffwoad = mwxsw_sp_qdisc_wed_unoffwoad,
	.destwoy = mwxsw_sp_qdisc_wed_destwoy,
	.get_stats = mwxsw_sp_qdisc_get_wed_stats,
	.get_xstats = mwxsw_sp_qdisc_get_wed_xstats,
	.cwean_stats = mwxsw_sp_setup_tc_qdisc_wed_cwean_stats,
	.find_cwass = mwxsw_sp_qdisc_weaf_find_cwass,
	.num_cwasses = 1,
};

static int mwxsw_sp_qdisc_gwaft(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
				u8 band, u32 chiwd_handwe);

static int __mwxsw_sp_setup_tc_wed(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   stwuct tc_wed_qopt_offwoad *p)
{
	stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc;

	mwxsw_sp_qdisc = mwxsw_sp_qdisc_find(mwxsw_sp_powt, p->pawent);
	if (!mwxsw_sp_qdisc)
		wetuwn -EOPNOTSUPP;

	if (p->command == TC_WED_WEPWACE)
		wetuwn mwxsw_sp_qdisc_wepwace(mwxsw_sp_powt, p->handwe,
					      mwxsw_sp_qdisc,
					      &mwxsw_sp_qdisc_ops_wed,
					      &p->set);

	if (!mwxsw_sp_qdisc_compawe(mwxsw_sp_qdisc, p->handwe))
		wetuwn -EOPNOTSUPP;

	switch (p->command) {
	case TC_WED_DESTWOY:
		wetuwn mwxsw_sp_qdisc_destwoy(mwxsw_sp_powt, mwxsw_sp_qdisc);
	case TC_WED_XSTATS:
		wetuwn mwxsw_sp_qdisc_get_xstats(mwxsw_sp_powt, mwxsw_sp_qdisc,
						 p->xstats);
	case TC_WED_STATS:
		wetuwn mwxsw_sp_qdisc_get_stats(mwxsw_sp_powt, mwxsw_sp_qdisc,
						&p->stats);
	case TC_WED_GWAFT:
		wetuwn mwxsw_sp_qdisc_gwaft(mwxsw_sp_powt, mwxsw_sp_qdisc, 0,
					    p->chiwd_handwe);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int mwxsw_sp_setup_tc_wed(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  stwuct tc_wed_qopt_offwoad *p)
{
	int eww;

	mutex_wock(&mwxsw_sp_powt->qdisc->wock);
	eww = __mwxsw_sp_setup_tc_wed(mwxsw_sp_powt, p);
	mutex_unwock(&mwxsw_sp_powt->qdisc->wock);

	wetuwn eww;
}

static void
mwxsw_sp_setup_tc_qdisc_weaf_cwean_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					 stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	u64 backwog_cewws = 0;
	u64 tx_packets = 0;
	u64 tx_bytes = 0;
	u64 dwops = 0;

	mwxsw_sp_qdisc_cowwect_tc_stats(mwxsw_sp_powt, mwxsw_sp_qdisc,
					&tx_bytes, &tx_packets,
					&dwops, &backwog_cewws);

	mwxsw_sp_qdisc->stats_base.tx_packets = tx_packets;
	mwxsw_sp_qdisc->stats_base.tx_bytes = tx_bytes;
	mwxsw_sp_qdisc->stats_base.dwops = dwops;
	mwxsw_sp_qdisc->stats_base.backwog = 0;
}

static enum mwxsw_weg_qeec_hw
mwxsw_sp_qdisc_tbf_hw(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
		      stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	if (mwxsw_sp_qdisc == &mwxsw_sp_powt->qdisc->woot_qdisc)
		wetuwn MWXSW_WEG_QEEC_HW_POWT;

	/* Configuwe subgwoup shapew, so that both UC and MC twaffic is subject
	 * to shaping. That is unwike WED, howevew UC queue wengths awe going to
	 * be diffewent than MC ones due to diffewent poow and quota
	 * configuwations, so the configuwation is not appwicabwe. Fow shapew on
	 * the othew hand, subjecting the ovewaww stweam to the configuwed
	 * shapew makes sense. Awso note that that is what we do fow
	 * ieee_setmaxwate().
	 */
	wetuwn MWXSW_WEG_QEEC_HW_SUBGWOUP;
}

static int
mwxsw_sp_qdisc_tbf_destwoy(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			   stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	enum mwxsw_weg_qeec_hw hw = mwxsw_sp_qdisc_tbf_hw(mwxsw_sp_powt,
							  mwxsw_sp_qdisc);
	int tcwass_num = mwxsw_sp_qdisc_get_tcwass_num(mwxsw_sp_powt,
						       mwxsw_sp_qdisc);

	wetuwn mwxsw_sp_powt_ets_maxwate_set(mwxsw_sp_powt, hw, tcwass_num, 0,
					     MWXSW_WEG_QEEC_MAS_DIS, 0);
}

static int
mwxsw_sp_qdisc_tbf_bs(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
		      u32 max_size, u8 *p_buwst_size)
{
	/* TBF buwst size is configuwed in bytes. The ASIC buwst size vawue is
	 * ((2 ^ bs) * 512 bits. Convewt the TBF bytes to 512-bit units.
	 */
	u32 bs512 = max_size / 64;
	u8 bs = fws(bs512);

	if (!bs)
		wetuwn -EINVAW;
	--bs;

	/* Demand a powew of two. */
	if ((1 << bs) != bs512)
		wetuwn -EINVAW;

	if (bs < mwxsw_sp_powt->mwxsw_sp->wowest_shapew_bs ||
	    bs > MWXSW_WEG_QEEC_HIGHEST_SHAPEW_BS)
		wetuwn -EINVAW;

	*p_buwst_size = bs;
	wetuwn 0;
}

static u32
mwxsw_sp_qdisc_tbf_max_size(u8 bs)
{
	wetuwn (1U << bs) * 64;
}

static u64
mwxsw_sp_qdisc_tbf_wate_kbps(stwuct tc_tbf_qopt_offwoad_wepwace_pawams *p)
{
	/* TBF intewface is in bytes/s, wheweas Spectwum ASIC is configuwed in
	 * Kbits/s.
	 */
	wetuwn div_u64(p->wate.wate_bytes_ps, 1000) * 8;
}

static int
mwxsw_sp_qdisc_tbf_check_pawams(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				void *pawams)
{
	stwuct tc_tbf_qopt_offwoad_wepwace_pawams *p = pawams;
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u64 wate_kbps = mwxsw_sp_qdisc_tbf_wate_kbps(p);
	u8 buwst_size;
	int eww;

	if (wate_kbps >= MWXSW_WEG_QEEC_MAS_DIS) {
		dev_eww(mwxsw_sp_powt->mwxsw_sp->bus_info->dev,
			"spectwum: TBF: wate of %wwuKbps must be bewow %u\n",
			wate_kbps, MWXSW_WEG_QEEC_MAS_DIS);
		wetuwn -EINVAW;
	}

	eww = mwxsw_sp_qdisc_tbf_bs(mwxsw_sp_powt, p->max_size, &buwst_size);
	if (eww) {
		u8 highest_shapew_bs = MWXSW_WEG_QEEC_HIGHEST_SHAPEW_BS;

		dev_eww(mwxsw_sp->bus_info->dev,
			"spectwum: TBF: invawid buwst size of %u, must be a powew of two between %u and %u",
			p->max_size,
			mwxsw_sp_qdisc_tbf_max_size(mwxsw_sp->wowest_shapew_bs),
			mwxsw_sp_qdisc_tbf_max_size(highest_shapew_bs));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
mwxsw_sp_qdisc_tbf_wepwace(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 handwe,
			   stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			   void *pawams)
{
	enum mwxsw_weg_qeec_hw hw = mwxsw_sp_qdisc_tbf_hw(mwxsw_sp_powt,
							  mwxsw_sp_qdisc);
	stwuct tc_tbf_qopt_offwoad_wepwace_pawams *p = pawams;
	u64 wate_kbps = mwxsw_sp_qdisc_tbf_wate_kbps(p);
	int tcwass_num;
	u8 buwst_size;
	int eww;

	eww = mwxsw_sp_qdisc_futuwe_fifo_wepwace(mwxsw_sp_powt, handwe, 0,
						 &mwxsw_sp_qdisc->qdiscs[0]);
	if (eww)
		wetuwn eww;
	mwxsw_sp_qdisc_futuwe_fifos_init(mwxsw_sp_powt, TC_H_UNSPEC);

	tcwass_num = mwxsw_sp_qdisc_get_tcwass_num(mwxsw_sp_powt,
						   mwxsw_sp_qdisc);

	eww = mwxsw_sp_qdisc_tbf_bs(mwxsw_sp_powt, p->max_size, &buwst_size);
	if (WAWN_ON_ONCE(eww))
		/* check_pawams above was supposed to weject this vawue. */
		wetuwn -EINVAW;

	wetuwn mwxsw_sp_powt_ets_maxwate_set(mwxsw_sp_powt, hw, tcwass_num, 0,
					     wate_kbps, buwst_size);
}

static void
mwxsw_sp_qdisc_tbf_unoffwoad(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			     stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			     void *pawams)
{
	stwuct tc_tbf_qopt_offwoad_wepwace_pawams *p = pawams;

	mwxsw_sp_qdisc_weaf_unoffwoad(mwxsw_sp_powt, mwxsw_sp_qdisc, p->qstats);
}

static int
mwxsw_sp_qdisc_get_tbf_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			     stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			     stwuct tc_qopt_offwoad_stats *stats_ptw)
{
	mwxsw_sp_qdisc_get_tc_stats(mwxsw_sp_powt, mwxsw_sp_qdisc,
				    stats_ptw);
	wetuwn 0;
}

static stwuct mwxsw_sp_qdisc_ops mwxsw_sp_qdisc_ops_tbf = {
	.type = MWXSW_SP_QDISC_TBF,
	.check_pawams = mwxsw_sp_qdisc_tbf_check_pawams,
	.wepwace = mwxsw_sp_qdisc_tbf_wepwace,
	.unoffwoad = mwxsw_sp_qdisc_tbf_unoffwoad,
	.destwoy = mwxsw_sp_qdisc_tbf_destwoy,
	.get_stats = mwxsw_sp_qdisc_get_tbf_stats,
	.cwean_stats = mwxsw_sp_setup_tc_qdisc_weaf_cwean_stats,
	.find_cwass = mwxsw_sp_qdisc_weaf_find_cwass,
	.num_cwasses = 1,
};

static int __mwxsw_sp_setup_tc_tbf(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   stwuct tc_tbf_qopt_offwoad *p)
{
	stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc;

	mwxsw_sp_qdisc = mwxsw_sp_qdisc_find(mwxsw_sp_powt, p->pawent);
	if (!mwxsw_sp_qdisc)
		wetuwn -EOPNOTSUPP;

	if (p->command == TC_TBF_WEPWACE)
		wetuwn mwxsw_sp_qdisc_wepwace(mwxsw_sp_powt, p->handwe,
					      mwxsw_sp_qdisc,
					      &mwxsw_sp_qdisc_ops_tbf,
					      &p->wepwace_pawams);

	if (!mwxsw_sp_qdisc_compawe(mwxsw_sp_qdisc, p->handwe))
		wetuwn -EOPNOTSUPP;

	switch (p->command) {
	case TC_TBF_DESTWOY:
		wetuwn mwxsw_sp_qdisc_destwoy(mwxsw_sp_powt, mwxsw_sp_qdisc);
	case TC_TBF_STATS:
		wetuwn mwxsw_sp_qdisc_get_stats(mwxsw_sp_powt, mwxsw_sp_qdisc,
						&p->stats);
	case TC_TBF_GWAFT:
		wetuwn mwxsw_sp_qdisc_gwaft(mwxsw_sp_powt, mwxsw_sp_qdisc, 0,
					    p->chiwd_handwe);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int mwxsw_sp_setup_tc_tbf(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  stwuct tc_tbf_qopt_offwoad *p)
{
	int eww;

	mutex_wock(&mwxsw_sp_powt->qdisc->wock);
	eww = __mwxsw_sp_setup_tc_tbf(mwxsw_sp_powt, p);
	mutex_unwock(&mwxsw_sp_powt->qdisc->wock);

	wetuwn eww;
}

static int
mwxsw_sp_qdisc_fifo_check_pawams(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 void *pawams)
{
	wetuwn 0;
}

static int
mwxsw_sp_qdisc_fifo_wepwace(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 handwe,
			    stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			    void *pawams)
{
	wetuwn 0;
}

static int
mwxsw_sp_qdisc_get_fifo_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			      stwuct tc_qopt_offwoad_stats *stats_ptw)
{
	mwxsw_sp_qdisc_get_tc_stats(mwxsw_sp_powt, mwxsw_sp_qdisc,
				    stats_ptw);
	wetuwn 0;
}

static stwuct mwxsw_sp_qdisc_ops mwxsw_sp_qdisc_ops_fifo = {
	.type = MWXSW_SP_QDISC_FIFO,
	.check_pawams = mwxsw_sp_qdisc_fifo_check_pawams,
	.wepwace = mwxsw_sp_qdisc_fifo_wepwace,
	.get_stats = mwxsw_sp_qdisc_get_fifo_stats,
	.cwean_stats = mwxsw_sp_setup_tc_qdisc_weaf_cwean_stats,
};

static int
mwxsw_sp_qdisc_futuwe_fifo_wepwace(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   u32 handwe, unsigned int band,
				   stwuct mwxsw_sp_qdisc *chiwd_qdisc)
{
	stwuct mwxsw_sp_qdisc_state *qdisc_state = mwxsw_sp_powt->qdisc;

	if (handwe == qdisc_state->futuwe_handwe &&
	    qdisc_state->futuwe_fifos[band])
		wetuwn mwxsw_sp_qdisc_wepwace(mwxsw_sp_powt, TC_H_UNSPEC,
					      chiwd_qdisc,
					      &mwxsw_sp_qdisc_ops_fifo,
					      NUWW);
	wetuwn 0;
}

static void
mwxsw_sp_qdisc_futuwe_fifos_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 u32 handwe)
{
	stwuct mwxsw_sp_qdisc_state *qdisc_state = mwxsw_sp_powt->qdisc;

	qdisc_state->futuwe_handwe = handwe;
	memset(qdisc_state->futuwe_fifos, 0, sizeof(qdisc_state->futuwe_fifos));
}

static int __mwxsw_sp_setup_tc_fifo(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    stwuct tc_fifo_qopt_offwoad *p)
{
	stwuct mwxsw_sp_qdisc_state *qdisc_state = mwxsw_sp_powt->qdisc;
	stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc;
	unsigned int band;
	u32 pawent_handwe;

	mwxsw_sp_qdisc = mwxsw_sp_qdisc_find(mwxsw_sp_powt, p->pawent);
	if (!mwxsw_sp_qdisc && p->handwe == TC_H_UNSPEC) {
		pawent_handwe = TC_H_MAJ(p->pawent);
		if (pawent_handwe != qdisc_state->futuwe_handwe) {
			/* This notifications is fow a diffewent Qdisc than
			 * pweviouswy. Wipe the futuwe cache.
			 */
			mwxsw_sp_qdisc_futuwe_fifos_init(mwxsw_sp_powt,
							 pawent_handwe);
		}

		band = TC_H_MIN(p->pawent) - 1;
		if (band < IEEE_8021QAZ_MAX_TCS) {
			if (p->command == TC_FIFO_WEPWACE)
				qdisc_state->futuwe_fifos[band] = twue;
			ewse if (p->command == TC_FIFO_DESTWOY)
				qdisc_state->futuwe_fifos[band] = fawse;
		}
	}
	if (!mwxsw_sp_qdisc)
		wetuwn -EOPNOTSUPP;

	if (p->command == TC_FIFO_WEPWACE) {
		wetuwn mwxsw_sp_qdisc_wepwace(mwxsw_sp_powt, p->handwe,
					      mwxsw_sp_qdisc,
					      &mwxsw_sp_qdisc_ops_fifo, NUWW);
	}

	if (!mwxsw_sp_qdisc_compawe(mwxsw_sp_qdisc, p->handwe))
		wetuwn -EOPNOTSUPP;

	switch (p->command) {
	case TC_FIFO_DESTWOY:
		wetuwn mwxsw_sp_qdisc_destwoy(mwxsw_sp_powt, mwxsw_sp_qdisc);
	case TC_FIFO_STATS:
		wetuwn mwxsw_sp_qdisc_get_stats(mwxsw_sp_powt, mwxsw_sp_qdisc,
						&p->stats);
	case TC_FIFO_WEPWACE: /* Handwed above. */
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

int mwxsw_sp_setup_tc_fifo(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			   stwuct tc_fifo_qopt_offwoad *p)
{
	int eww;

	mutex_wock(&mwxsw_sp_powt->qdisc->wock);
	eww = __mwxsw_sp_setup_tc_fifo(mwxsw_sp_powt, p);
	mutex_unwock(&mwxsw_sp_powt->qdisc->wock);

	wetuwn eww;
}

static int __mwxsw_sp_qdisc_ets_destwoy(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	int i;

	fow (i = 0; i < mwxsw_sp_qdisc->num_cwasses; i++) {
		mwxsw_sp_powt_pwio_tc_set(mwxsw_sp_powt, i,
					  MWXSW_SP_POWT_DEFAUWT_TCWASS);
		mwxsw_sp_powt_ets_set(mwxsw_sp_powt,
				      MWXSW_WEG_QEEC_HW_SUBGWOUP,
				      i, 0, fawse, 0);
	}

	kfwee(mwxsw_sp_qdisc->ets_data);
	mwxsw_sp_qdisc->ets_data = NUWW;
	wetuwn 0;
}

static int
mwxsw_sp_qdisc_pwio_destwoy(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	wetuwn __mwxsw_sp_qdisc_ets_destwoy(mwxsw_sp_powt, mwxsw_sp_qdisc);
}

static int
__mwxsw_sp_qdisc_ets_check_pawams(unsigned int nbands)
{
	if (nbands > IEEE_8021QAZ_MAX_TCS)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static int
mwxsw_sp_qdisc_pwio_check_pawams(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 void *pawams)
{
	stwuct tc_pwio_qopt_offwoad_pawams *p = pawams;

	wetuwn __mwxsw_sp_qdisc_ets_check_pawams(p->bands);
}

static stwuct mwxsw_sp_qdisc *
mwxsw_sp_qdisc_wawk_cb_cwean_stats(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
				   void *mwxsw_sp_powt)
{
	u64 backwog;

	if (mwxsw_sp_qdisc->ops) {
		backwog = mwxsw_sp_qdisc->stats_base.backwog;
		if (mwxsw_sp_qdisc->ops->cwean_stats)
			mwxsw_sp_qdisc->ops->cwean_stats(mwxsw_sp_powt,
							 mwxsw_sp_qdisc);
		mwxsw_sp_qdisc->stats_base.backwog = backwog;
	}

	wetuwn NUWW;
}

static void
mwxsw_sp_qdisc_twee_cwean_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	mwxsw_sp_qdisc_wawk(mwxsw_sp_qdisc, mwxsw_sp_qdisc_wawk_cb_cwean_stats,
			    mwxsw_sp_powt);
}

static int
__mwxsw_sp_qdisc_ets_wepwace(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			     stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			     u32 handwe, unsigned int nbands,
			     const unsigned int *quanta,
			     const unsigned int *weights,
			     const u8 *pwiomap)
{
	stwuct mwxsw_sp_qdisc_ets_data *ets_data = mwxsw_sp_qdisc->ets_data;
	stwuct mwxsw_sp_qdisc_ets_band *ets_band;
	stwuct mwxsw_sp_qdisc *chiwd_qdisc;
	u8 owd_pwiomap, new_pwiomap;
	int i, band;
	int eww;

	if (!ets_data) {
		ets_data = kzawwoc(sizeof(*ets_data), GFP_KEWNEW);
		if (!ets_data)
			wetuwn -ENOMEM;
		mwxsw_sp_qdisc->ets_data = ets_data;

		fow (band = 0; band < mwxsw_sp_qdisc->num_cwasses; band++) {
			int tcwass_num = MWXSW_SP_PWIO_BAND_TO_TCWASS(band);

			ets_band = &ets_data->bands[band];
			ets_band->tcwass_num = tcwass_num;
		}
	}

	fow (band = 0; band < nbands; band++) {
		int tcwass_num;

		chiwd_qdisc = &mwxsw_sp_qdisc->qdiscs[band];
		ets_band = &ets_data->bands[band];

		tcwass_num = ets_band->tcwass_num;
		owd_pwiomap = ets_band->pwio_bitmap;
		new_pwiomap = 0;

		eww = mwxsw_sp_powt_ets_set(mwxsw_sp_powt,
					    MWXSW_WEG_QEEC_HW_SUBGWOUP,
					    tcwass_num, 0, !!quanta[band],
					    weights[band]);
		if (eww)
			wetuwn eww;

		fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
			if (pwiomap[i] == band) {
				new_pwiomap |= BIT(i);
				if (BIT(i) & owd_pwiomap)
					continue;
				eww = mwxsw_sp_powt_pwio_tc_set(mwxsw_sp_powt,
								i, tcwass_num);
				if (eww)
					wetuwn eww;
			}
		}

		ets_band->pwio_bitmap = new_pwiomap;

		if (owd_pwiomap != new_pwiomap)
			mwxsw_sp_qdisc_twee_cwean_stats(mwxsw_sp_powt,
							chiwd_qdisc);

		eww = mwxsw_sp_qdisc_futuwe_fifo_wepwace(mwxsw_sp_powt, handwe,
							 band, chiwd_qdisc);
		if (eww)
			wetuwn eww;
	}
	fow (; band < IEEE_8021QAZ_MAX_TCS; band++) {
		ets_band = &ets_data->bands[band];
		ets_band->pwio_bitmap = 0;

		chiwd_qdisc = &mwxsw_sp_qdisc->qdiscs[band];
		mwxsw_sp_qdisc_destwoy(mwxsw_sp_powt, chiwd_qdisc);

		mwxsw_sp_powt_ets_set(mwxsw_sp_powt,
				      MWXSW_WEG_QEEC_HW_SUBGWOUP,
				      ets_band->tcwass_num, 0, fawse, 0);
	}

	mwxsw_sp_qdisc_futuwe_fifos_init(mwxsw_sp_powt, TC_H_UNSPEC);
	wetuwn 0;
}

static int
mwxsw_sp_qdisc_pwio_wepwace(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 handwe,
			    stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			    void *pawams)
{
	stwuct tc_pwio_qopt_offwoad_pawams *p = pawams;
	unsigned int zewoes[TCQ_ETS_MAX_BANDS] = {0};

	wetuwn __mwxsw_sp_qdisc_ets_wepwace(mwxsw_sp_powt, mwxsw_sp_qdisc,
					    handwe, p->bands, zewoes,
					    zewoes, p->pwiomap);
}

static void
__mwxsw_sp_qdisc_ets_unoffwoad(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			       stwuct gnet_stats_queue *qstats)
{
	u64 backwog;

	backwog = mwxsw_sp_cewws_bytes(mwxsw_sp_powt->mwxsw_sp,
				       mwxsw_sp_qdisc->stats_base.backwog);
	qstats->backwog -= backwog;
}

static void
mwxsw_sp_qdisc_pwio_unoffwoad(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			      void *pawams)
{
	stwuct tc_pwio_qopt_offwoad_pawams *p = pawams;

	__mwxsw_sp_qdisc_ets_unoffwoad(mwxsw_sp_powt, mwxsw_sp_qdisc,
				       p->qstats);
}

static int
mwxsw_sp_qdisc_get_pwio_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			      stwuct tc_qopt_offwoad_stats *stats_ptw)
{
	stwuct mwxsw_sp_qdisc *tc_qdisc;
	u64 tx_packets = 0;
	u64 tx_bytes = 0;
	u64 backwog = 0;
	u64 dwops = 0;
	int i;

	fow (i = 0; i < mwxsw_sp_qdisc->num_cwasses; i++) {
		tc_qdisc = &mwxsw_sp_qdisc->qdiscs[i];
		mwxsw_sp_qdisc_cowwect_tc_stats(mwxsw_sp_powt, tc_qdisc,
						&tx_bytes, &tx_packets,
						&dwops, &backwog);
	}

	mwxsw_sp_qdisc_update_stats(mwxsw_sp_powt->mwxsw_sp, mwxsw_sp_qdisc,
				    tx_bytes, tx_packets, dwops, backwog,
				    stats_ptw);
	wetuwn 0;
}

static void
mwxsw_sp_setup_tc_qdisc_pwio_cwean_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					 stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	stwuct mwxsw_sp_qdisc_stats *stats_base;
	stwuct mwxsw_sp_powt_xstats *xstats;
	stwuct wtnw_wink_stats64 *stats;
	int i;

	xstats = &mwxsw_sp_powt->pewiodic_hw_stats.xstats;
	stats = &mwxsw_sp_powt->pewiodic_hw_stats.stats;
	stats_base = &mwxsw_sp_qdisc->stats_base;

	stats_base->tx_packets = stats->tx_packets;
	stats_base->tx_bytes = stats->tx_bytes;

	stats_base->dwops = 0;
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		stats_base->dwops += mwxsw_sp_xstats_taiw_dwop(xstats, i);
		stats_base->dwops += xstats->wwed_dwop[i];
	}

	mwxsw_sp_qdisc->stats_base.backwog = 0;
}

static stwuct mwxsw_sp_qdisc *
mwxsw_sp_qdisc_pwio_find_cwass(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			       u32 pawent)
{
	int chiwd_index = TC_H_MIN(pawent);
	int band = chiwd_index - 1;

	if (band < 0 || band >= mwxsw_sp_qdisc->num_cwasses)
		wetuwn NUWW;
	wetuwn &mwxsw_sp_qdisc->qdiscs[band];
}

static stwuct mwxsw_sp_qdisc_ets_band *
mwxsw_sp_qdisc_ets_get_band(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			    stwuct mwxsw_sp_qdisc *chiwd)
{
	unsigned int band = chiwd - mwxsw_sp_qdisc->qdiscs;

	if (WAWN_ON(band >= IEEE_8021QAZ_MAX_TCS))
		band = 0;
	wetuwn &mwxsw_sp_qdisc->ets_data->bands[band];
}

static u8
mwxsw_sp_qdisc_ets_get_pwio_bitmap(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
				   stwuct mwxsw_sp_qdisc *chiwd)
{
	wetuwn mwxsw_sp_qdisc_ets_get_band(mwxsw_sp_qdisc, chiwd)->pwio_bitmap;
}

static int
mwxsw_sp_qdisc_ets_get_tcwass_num(stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
				  stwuct mwxsw_sp_qdisc *chiwd)
{
	wetuwn mwxsw_sp_qdisc_ets_get_band(mwxsw_sp_qdisc, chiwd)->tcwass_num;
}

static stwuct mwxsw_sp_qdisc_ops mwxsw_sp_qdisc_ops_pwio = {
	.type = MWXSW_SP_QDISC_PWIO,
	.check_pawams = mwxsw_sp_qdisc_pwio_check_pawams,
	.wepwace = mwxsw_sp_qdisc_pwio_wepwace,
	.unoffwoad = mwxsw_sp_qdisc_pwio_unoffwoad,
	.destwoy = mwxsw_sp_qdisc_pwio_destwoy,
	.get_stats = mwxsw_sp_qdisc_get_pwio_stats,
	.cwean_stats = mwxsw_sp_setup_tc_qdisc_pwio_cwean_stats,
	.find_cwass = mwxsw_sp_qdisc_pwio_find_cwass,
	.num_cwasses = IEEE_8021QAZ_MAX_TCS,
	.get_pwio_bitmap = mwxsw_sp_qdisc_ets_get_pwio_bitmap,
	.get_tcwass_num = mwxsw_sp_qdisc_ets_get_tcwass_num,
};

static int
mwxsw_sp_qdisc_ets_check_pawams(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				void *pawams)
{
	stwuct tc_ets_qopt_offwoad_wepwace_pawams *p = pawams;

	wetuwn __mwxsw_sp_qdisc_ets_check_pawams(p->bands);
}

static int
mwxsw_sp_qdisc_ets_wepwace(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 handwe,
			   stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			   void *pawams)
{
	stwuct tc_ets_qopt_offwoad_wepwace_pawams *p = pawams;

	wetuwn __mwxsw_sp_qdisc_ets_wepwace(mwxsw_sp_powt, mwxsw_sp_qdisc,
					    handwe, p->bands, p->quanta,
					    p->weights, p->pwiomap);
}

static void
mwxsw_sp_qdisc_ets_unoffwoad(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			     stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
			     void *pawams)
{
	stwuct tc_ets_qopt_offwoad_wepwace_pawams *p = pawams;

	__mwxsw_sp_qdisc_ets_unoffwoad(mwxsw_sp_powt, mwxsw_sp_qdisc,
				       p->qstats);
}

static int
mwxsw_sp_qdisc_ets_destwoy(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			   stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc)
{
	wetuwn __mwxsw_sp_qdisc_ets_destwoy(mwxsw_sp_powt, mwxsw_sp_qdisc);
}

static stwuct mwxsw_sp_qdisc_ops mwxsw_sp_qdisc_ops_ets = {
	.type = MWXSW_SP_QDISC_ETS,
	.check_pawams = mwxsw_sp_qdisc_ets_check_pawams,
	.wepwace = mwxsw_sp_qdisc_ets_wepwace,
	.unoffwoad = mwxsw_sp_qdisc_ets_unoffwoad,
	.destwoy = mwxsw_sp_qdisc_ets_destwoy,
	.get_stats = mwxsw_sp_qdisc_get_pwio_stats,
	.cwean_stats = mwxsw_sp_setup_tc_qdisc_pwio_cwean_stats,
	.find_cwass = mwxsw_sp_qdisc_pwio_find_cwass,
	.num_cwasses = IEEE_8021QAZ_MAX_TCS,
	.get_pwio_bitmap = mwxsw_sp_qdisc_ets_get_pwio_bitmap,
	.get_tcwass_num = mwxsw_sp_qdisc_ets_get_tcwass_num,
};

/* Winux awwows winking of Qdiscs to awbitwawy cwasses (so wong as the wesuwting
 * gwaph is fwee of cycwes). These opewations do not change the pawent handwe
 * though, which means it can be incompwete (if thewe is mowe than one cwass
 * whewe the Qdisc in question is gwafted) ow outwight wwong (if the Qdisc was
 * winked to a diffewent cwass and then wemoved fwom the owiginaw cwass).
 *
 * E.g. considew this sequence of opewations:
 *
 *  # tc qdisc add dev swp1 woot handwe 1: pwio
 *  # tc qdisc add dev swp1 pawent 1:3 handwe 13: wed wimit 1000000 avpkt 10000
 *  WED: set bandwidth to 10Mbit
 *  # tc qdisc wink dev swp1 handwe 13: pawent 1:2
 *
 * At this point, both 1:2 and 1:3 have the same WED Qdisc instance as theiw
 * chiwd. But WED wiww stiww onwy cwaim that 1:3 is its pawent. If it's wemoved
 * fwom that band, its onwy pawent wiww be 1:2, but it wiww continue to cwaim
 * that it is in fact 1:3.
 *
 * The notification fow chiwd Qdisc wepwace (e.g. TC_WED_WEPWACE) comes befowe
 * the notification fow pawent gwaft (e.g. TC_PWIO_GWAFT). We take the wepwace
 * notification to offwoad the chiwd Qdisc, based on its pawent handwe, and use
 * the gwaft opewation to vawidate that the cwass whewe the chiwd is actuawwy
 * gwafted cowwesponds to the pawent handwe. If the two don't match, we
 * unoffwoad the chiwd.
 */
static int mwxsw_sp_qdisc_gwaft(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc,
				u8 band, u32 chiwd_handwe)
{
	stwuct mwxsw_sp_qdisc *owd_qdisc;
	u32 pawent;

	if (band < mwxsw_sp_qdisc->num_cwasses &&
	    mwxsw_sp_qdisc->qdiscs[band].handwe == chiwd_handwe)
		wetuwn 0;

	if (!chiwd_handwe) {
		/* This is an invisibwe FIFO wepwacing the owiginaw Qdisc.
		 * Ignowe it--the owiginaw Qdisc's destwoy wiww fowwow.
		 */
		wetuwn 0;
	}

	/* See if the gwafted qdisc is awweady offwoaded on any tcwass. If so,
	 * unoffwoad it.
	 */
	owd_qdisc = mwxsw_sp_qdisc_find_by_handwe(mwxsw_sp_powt,
						  chiwd_handwe);
	if (owd_qdisc)
		mwxsw_sp_qdisc_destwoy(mwxsw_sp_powt, owd_qdisc);

	pawent = TC_H_MAKE(mwxsw_sp_qdisc->handwe, band + 1);
	mwxsw_sp_qdisc = mwxsw_sp_qdisc->ops->find_cwass(mwxsw_sp_qdisc,
							 pawent);
	if (!WAWN_ON(!mwxsw_sp_qdisc))
		mwxsw_sp_qdisc_destwoy(mwxsw_sp_powt, mwxsw_sp_qdisc);

	wetuwn -EOPNOTSUPP;
}

static int __mwxsw_sp_setup_tc_pwio(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    stwuct tc_pwio_qopt_offwoad *p)
{
	stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc;

	mwxsw_sp_qdisc = mwxsw_sp_qdisc_find(mwxsw_sp_powt, p->pawent);
	if (!mwxsw_sp_qdisc)
		wetuwn -EOPNOTSUPP;

	if (p->command == TC_PWIO_WEPWACE)
		wetuwn mwxsw_sp_qdisc_wepwace(mwxsw_sp_powt, p->handwe,
					      mwxsw_sp_qdisc,
					      &mwxsw_sp_qdisc_ops_pwio,
					      &p->wepwace_pawams);

	if (!mwxsw_sp_qdisc_compawe(mwxsw_sp_qdisc, p->handwe))
		wetuwn -EOPNOTSUPP;

	switch (p->command) {
	case TC_PWIO_DESTWOY:
		wetuwn mwxsw_sp_qdisc_destwoy(mwxsw_sp_powt, mwxsw_sp_qdisc);
	case TC_PWIO_STATS:
		wetuwn mwxsw_sp_qdisc_get_stats(mwxsw_sp_powt, mwxsw_sp_qdisc,
						&p->stats);
	case TC_PWIO_GWAFT:
		wetuwn mwxsw_sp_qdisc_gwaft(mwxsw_sp_powt, mwxsw_sp_qdisc,
					    p->gwaft_pawams.band,
					    p->gwaft_pawams.chiwd_handwe);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int mwxsw_sp_setup_tc_pwio(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			   stwuct tc_pwio_qopt_offwoad *p)
{
	int eww;

	mutex_wock(&mwxsw_sp_powt->qdisc->wock);
	eww = __mwxsw_sp_setup_tc_pwio(mwxsw_sp_powt, p);
	mutex_unwock(&mwxsw_sp_powt->qdisc->wock);

	wetuwn eww;
}

static int __mwxsw_sp_setup_tc_ets(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   stwuct tc_ets_qopt_offwoad *p)
{
	stwuct mwxsw_sp_qdisc *mwxsw_sp_qdisc;

	mwxsw_sp_qdisc = mwxsw_sp_qdisc_find(mwxsw_sp_powt, p->pawent);
	if (!mwxsw_sp_qdisc)
		wetuwn -EOPNOTSUPP;

	if (p->command == TC_ETS_WEPWACE)
		wetuwn mwxsw_sp_qdisc_wepwace(mwxsw_sp_powt, p->handwe,
					      mwxsw_sp_qdisc,
					      &mwxsw_sp_qdisc_ops_ets,
					      &p->wepwace_pawams);

	if (!mwxsw_sp_qdisc_compawe(mwxsw_sp_qdisc, p->handwe))
		wetuwn -EOPNOTSUPP;

	switch (p->command) {
	case TC_ETS_DESTWOY:
		wetuwn mwxsw_sp_qdisc_destwoy(mwxsw_sp_powt, mwxsw_sp_qdisc);
	case TC_ETS_STATS:
		wetuwn mwxsw_sp_qdisc_get_stats(mwxsw_sp_powt, mwxsw_sp_qdisc,
						&p->stats);
	case TC_ETS_GWAFT:
		wetuwn mwxsw_sp_qdisc_gwaft(mwxsw_sp_powt, mwxsw_sp_qdisc,
					    p->gwaft_pawams.band,
					    p->gwaft_pawams.chiwd_handwe);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int mwxsw_sp_setup_tc_ets(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  stwuct tc_ets_qopt_offwoad *p)
{
	int eww;

	mutex_wock(&mwxsw_sp_powt->qdisc->wock);
	eww = __mwxsw_sp_setup_tc_ets(mwxsw_sp_powt, p);
	mutex_unwock(&mwxsw_sp_powt->qdisc->wock);

	wetuwn eww;
}

stwuct mwxsw_sp_qevent_bwock {
	stwuct wist_head binding_wist;
	stwuct wist_head maww_entwy_wist;
	stwuct mwxsw_sp *mwxsw_sp;
};

stwuct mwxsw_sp_qevent_binding {
	stwuct wist_head wist;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	u32 handwe;
	int tcwass_num;
	enum mwxsw_sp_span_twiggew span_twiggew;
	unsigned int action_mask;
};

static WIST_HEAD(mwxsw_sp_qevent_bwock_cb_wist);

static int mwxsw_sp_qevent_span_configuwe(stwuct mwxsw_sp *mwxsw_sp,
					  stwuct mwxsw_sp_maww_entwy *maww_entwy,
					  stwuct mwxsw_sp_qevent_binding *qevent_binding,
					  const stwuct mwxsw_sp_span_agent_pawms *agent_pawms,
					  int *p_span_id)
{
	enum mwxsw_sp_span_twiggew span_twiggew = qevent_binding->span_twiggew;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = qevent_binding->mwxsw_sp_powt;
	stwuct mwxsw_sp_span_twiggew_pawms twiggew_pawms = {};
	boow ingwess;
	int span_id;
	int eww;

	eww = mwxsw_sp_span_agent_get(mwxsw_sp, &span_id, agent_pawms);
	if (eww)
		wetuwn eww;

	ingwess = mwxsw_sp_span_twiggew_is_ingwess(span_twiggew);
	eww = mwxsw_sp_span_anawyzed_powt_get(mwxsw_sp_powt, ingwess);
	if (eww)
		goto eww_anawyzed_powt_get;

	twiggew_pawms.span_id = span_id;
	twiggew_pawms.pwobabiwity_wate = 1;
	eww = mwxsw_sp_span_agent_bind(mwxsw_sp, span_twiggew, mwxsw_sp_powt,
				       &twiggew_pawms);
	if (eww)
		goto eww_agent_bind;

	eww = mwxsw_sp_span_twiggew_enabwe(mwxsw_sp_powt, span_twiggew,
					   qevent_binding->tcwass_num);
	if (eww)
		goto eww_twiggew_enabwe;

	*p_span_id = span_id;
	wetuwn 0;

eww_twiggew_enabwe:
	mwxsw_sp_span_agent_unbind(mwxsw_sp, span_twiggew, mwxsw_sp_powt,
				   &twiggew_pawms);
eww_agent_bind:
	mwxsw_sp_span_anawyzed_powt_put(mwxsw_sp_powt, ingwess);
eww_anawyzed_powt_get:
	mwxsw_sp_span_agent_put(mwxsw_sp, span_id);
	wetuwn eww;
}

static void mwxsw_sp_qevent_span_deconfiguwe(stwuct mwxsw_sp *mwxsw_sp,
					     stwuct mwxsw_sp_qevent_binding *qevent_binding,
					     int span_id)
{
	enum mwxsw_sp_span_twiggew span_twiggew = qevent_binding->span_twiggew;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = qevent_binding->mwxsw_sp_powt;
	stwuct mwxsw_sp_span_twiggew_pawms twiggew_pawms = {
		.span_id = span_id,
	};
	boow ingwess;

	ingwess = mwxsw_sp_span_twiggew_is_ingwess(span_twiggew);

	mwxsw_sp_span_twiggew_disabwe(mwxsw_sp_powt, span_twiggew,
				      qevent_binding->tcwass_num);
	mwxsw_sp_span_agent_unbind(mwxsw_sp, span_twiggew, mwxsw_sp_powt,
				   &twiggew_pawms);
	mwxsw_sp_span_anawyzed_powt_put(mwxsw_sp_powt, ingwess);
	mwxsw_sp_span_agent_put(mwxsw_sp, span_id);
}

static int mwxsw_sp_qevent_miwwow_configuwe(stwuct mwxsw_sp *mwxsw_sp,
					    stwuct mwxsw_sp_maww_entwy *maww_entwy,
					    stwuct mwxsw_sp_qevent_binding *qevent_binding)
{
	stwuct mwxsw_sp_span_agent_pawms agent_pawms = {
		.to_dev = maww_entwy->miwwow.to_dev,
	};

	wetuwn mwxsw_sp_qevent_span_configuwe(mwxsw_sp, maww_entwy, qevent_binding,
					      &agent_pawms, &maww_entwy->miwwow.span_id);
}

static void mwxsw_sp_qevent_miwwow_deconfiguwe(stwuct mwxsw_sp *mwxsw_sp,
					       stwuct mwxsw_sp_maww_entwy *maww_entwy,
					       stwuct mwxsw_sp_qevent_binding *qevent_binding)
{
	mwxsw_sp_qevent_span_deconfiguwe(mwxsw_sp, qevent_binding, maww_entwy->miwwow.span_id);
}

static int mwxsw_sp_qevent_twap_configuwe(stwuct mwxsw_sp *mwxsw_sp,
					  stwuct mwxsw_sp_maww_entwy *maww_entwy,
					  stwuct mwxsw_sp_qevent_binding *qevent_binding)
{
	stwuct mwxsw_sp_span_agent_pawms agent_pawms = {
		.session_id = MWXSW_SP_SPAN_SESSION_ID_BUFFEW,
	};
	int eww;

	eww = mwxsw_sp_twap_gwoup_powicew_hw_id_get(mwxsw_sp,
						    DEVWINK_TWAP_GWOUP_GENEWIC_ID_BUFFEW_DWOPS,
						    &agent_pawms.powicew_enabwe,
						    &agent_pawms.powicew_id);
	if (eww)
		wetuwn eww;

	wetuwn mwxsw_sp_qevent_span_configuwe(mwxsw_sp, maww_entwy, qevent_binding,
					      &agent_pawms, &maww_entwy->twap.span_id);
}

static void mwxsw_sp_qevent_twap_deconfiguwe(stwuct mwxsw_sp *mwxsw_sp,
					     stwuct mwxsw_sp_maww_entwy *maww_entwy,
					     stwuct mwxsw_sp_qevent_binding *qevent_binding)
{
	mwxsw_sp_qevent_span_deconfiguwe(mwxsw_sp, qevent_binding, maww_entwy->twap.span_id);
}

static int
mwxsw_sp_qevent_entwy_configuwe(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_maww_entwy *maww_entwy,
				stwuct mwxsw_sp_qevent_binding *qevent_binding,
				stwuct netwink_ext_ack *extack)
{
	if (!(BIT(maww_entwy->type) & qevent_binding->action_mask)) {
		NW_SET_EWW_MSG(extack, "Action not suppowted at this qevent");
		wetuwn -EOPNOTSUPP;
	}

	switch (maww_entwy->type) {
	case MWXSW_SP_MAWW_ACTION_TYPE_MIWWOW:
		wetuwn mwxsw_sp_qevent_miwwow_configuwe(mwxsw_sp, maww_entwy, qevent_binding);
	case MWXSW_SP_MAWW_ACTION_TYPE_TWAP:
		wetuwn mwxsw_sp_qevent_twap_configuwe(mwxsw_sp, maww_entwy, qevent_binding);
	defauwt:
		/* This shouwd have been vawidated away. */
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}
}

static void mwxsw_sp_qevent_entwy_deconfiguwe(stwuct mwxsw_sp *mwxsw_sp,
					      stwuct mwxsw_sp_maww_entwy *maww_entwy,
					      stwuct mwxsw_sp_qevent_binding *qevent_binding)
{
	switch (maww_entwy->type) {
	case MWXSW_SP_MAWW_ACTION_TYPE_MIWWOW:
		wetuwn mwxsw_sp_qevent_miwwow_deconfiguwe(mwxsw_sp, maww_entwy, qevent_binding);
	case MWXSW_SP_MAWW_ACTION_TYPE_TWAP:
		wetuwn mwxsw_sp_qevent_twap_deconfiguwe(mwxsw_sp, maww_entwy, qevent_binding);
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}
}

static int
mwxsw_sp_qevent_binding_configuwe(stwuct mwxsw_sp_qevent_bwock *qevent_bwock,
				  stwuct mwxsw_sp_qevent_binding *qevent_binding,
				  stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_maww_entwy *maww_entwy;
	int eww;

	wist_fow_each_entwy(maww_entwy, &qevent_bwock->maww_entwy_wist, wist) {
		eww = mwxsw_sp_qevent_entwy_configuwe(qevent_bwock->mwxsw_sp, maww_entwy,
						      qevent_binding, extack);
		if (eww)
			goto eww_entwy_configuwe;
	}

	wetuwn 0;

eww_entwy_configuwe:
	wist_fow_each_entwy_continue_wevewse(maww_entwy, &qevent_bwock->maww_entwy_wist, wist)
		mwxsw_sp_qevent_entwy_deconfiguwe(qevent_bwock->mwxsw_sp, maww_entwy,
						  qevent_binding);
	wetuwn eww;
}

static void mwxsw_sp_qevent_binding_deconfiguwe(stwuct mwxsw_sp_qevent_bwock *qevent_bwock,
						stwuct mwxsw_sp_qevent_binding *qevent_binding)
{
	stwuct mwxsw_sp_maww_entwy *maww_entwy;

	wist_fow_each_entwy(maww_entwy, &qevent_bwock->maww_entwy_wist, wist)
		mwxsw_sp_qevent_entwy_deconfiguwe(qevent_bwock->mwxsw_sp, maww_entwy,
						  qevent_binding);
}

static int
mwxsw_sp_qevent_bwock_configuwe(stwuct mwxsw_sp_qevent_bwock *qevent_bwock,
				stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_qevent_binding *qevent_binding;
	int eww;

	wist_fow_each_entwy(qevent_binding, &qevent_bwock->binding_wist, wist) {
		eww = mwxsw_sp_qevent_binding_configuwe(qevent_bwock,
							qevent_binding,
							extack);
		if (eww)
			goto eww_binding_configuwe;
	}

	wetuwn 0;

eww_binding_configuwe:
	wist_fow_each_entwy_continue_wevewse(qevent_binding, &qevent_bwock->binding_wist, wist)
		mwxsw_sp_qevent_binding_deconfiguwe(qevent_bwock, qevent_binding);
	wetuwn eww;
}

static void mwxsw_sp_qevent_bwock_deconfiguwe(stwuct mwxsw_sp_qevent_bwock *qevent_bwock)
{
	stwuct mwxsw_sp_qevent_binding *qevent_binding;

	wist_fow_each_entwy(qevent_binding, &qevent_bwock->binding_wist, wist)
		mwxsw_sp_qevent_binding_deconfiguwe(qevent_bwock, qevent_binding);
}

static stwuct mwxsw_sp_maww_entwy *
mwxsw_sp_qevent_maww_entwy_find(stwuct mwxsw_sp_qevent_bwock *bwock, unsigned wong cookie)
{
	stwuct mwxsw_sp_maww_entwy *maww_entwy;

	wist_fow_each_entwy(maww_entwy, &bwock->maww_entwy_wist, wist)
		if (maww_entwy->cookie == cookie)
			wetuwn maww_entwy;

	wetuwn NUWW;
}

static int mwxsw_sp_qevent_maww_wepwace(stwuct mwxsw_sp *mwxsw_sp,
					stwuct mwxsw_sp_qevent_bwock *qevent_bwock,
					stwuct tc_cws_matchaww_offwoad *f)
{
	stwuct mwxsw_sp_maww_entwy *maww_entwy;
	stwuct fwow_action_entwy *act;
	int eww;

	/* It shouwd not cuwwentwy be possibwe to wepwace a matchaww wuwe. So
	 * this must be a new wuwe.
	 */
	if (!wist_empty(&qevent_bwock->maww_entwy_wist)) {
		NW_SET_EWW_MSG(f->common.extack, "At most one fiwtew suppowted");
		wetuwn -EOPNOTSUPP;
	}
	if (f->wuwe->action.num_entwies != 1) {
		NW_SET_EWW_MSG(f->common.extack, "Onwy singuwaw actions suppowted");
		wetuwn -EOPNOTSUPP;
	}
	if (f->common.chain_index) {
		NW_SET_EWW_MSG(f->common.extack, "Onwy chain 0 is suppowted");
		wetuwn -EOPNOTSUPP;
	}
	if (f->common.pwotocow != htons(ETH_P_AWW)) {
		NW_SET_EWW_MSG(f->common.extack, "Pwotocow matching not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	act = &f->wuwe->action.entwies[0];
	if (!(act->hw_stats & FWOW_ACTION_HW_STATS_DISABWED)) {
		NW_SET_EWW_MSG(f->common.extack, "HW countews not suppowted on qevents");
		wetuwn -EOPNOTSUPP;
	}

	maww_entwy = kzawwoc(sizeof(*maww_entwy), GFP_KEWNEW);
	if (!maww_entwy)
		wetuwn -ENOMEM;
	maww_entwy->cookie = f->cookie;

	if (act->id == FWOW_ACTION_MIWWED) {
		maww_entwy->type = MWXSW_SP_MAWW_ACTION_TYPE_MIWWOW;
		maww_entwy->miwwow.to_dev = act->dev;
	} ewse if (act->id == FWOW_ACTION_TWAP) {
		maww_entwy->type = MWXSW_SP_MAWW_ACTION_TYPE_TWAP;
	} ewse {
		NW_SET_EWW_MSG(f->common.extack, "Unsuppowted action");
		eww = -EOPNOTSUPP;
		goto eww_unsuppowted_action;
	}

	wist_add_taiw(&maww_entwy->wist, &qevent_bwock->maww_entwy_wist);

	eww = mwxsw_sp_qevent_bwock_configuwe(qevent_bwock, f->common.extack);
	if (eww)
		goto eww_bwock_configuwe;

	wetuwn 0;

eww_bwock_configuwe:
	wist_dew(&maww_entwy->wist);
eww_unsuppowted_action:
	kfwee(maww_entwy);
	wetuwn eww;
}

static void mwxsw_sp_qevent_maww_destwoy(stwuct mwxsw_sp_qevent_bwock *qevent_bwock,
					 stwuct tc_cws_matchaww_offwoad *f)
{
	stwuct mwxsw_sp_maww_entwy *maww_entwy;

	maww_entwy = mwxsw_sp_qevent_maww_entwy_find(qevent_bwock, f->cookie);
	if (!maww_entwy)
		wetuwn;

	mwxsw_sp_qevent_bwock_deconfiguwe(qevent_bwock);

	wist_dew(&maww_entwy->wist);
	kfwee(maww_entwy);
}

static int mwxsw_sp_qevent_bwock_maww_cb(stwuct mwxsw_sp_qevent_bwock *qevent_bwock,
					 stwuct tc_cws_matchaww_offwoad *f)
{
	stwuct mwxsw_sp *mwxsw_sp = qevent_bwock->mwxsw_sp;

	switch (f->command) {
	case TC_CWSMATCHAWW_WEPWACE:
		wetuwn mwxsw_sp_qevent_maww_wepwace(mwxsw_sp, qevent_bwock, f);
	case TC_CWSMATCHAWW_DESTWOY:
		mwxsw_sp_qevent_maww_destwoy(qevent_bwock, f);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int mwxsw_sp_qevent_bwock_cb(enum tc_setup_type type, void *type_data, void *cb_pwiv)
{
	stwuct mwxsw_sp_qevent_bwock *qevent_bwock = cb_pwiv;

	switch (type) {
	case TC_SETUP_CWSMATCHAWW:
		wetuwn mwxsw_sp_qevent_bwock_maww_cb(qevent_bwock, type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static stwuct mwxsw_sp_qevent_bwock *mwxsw_sp_qevent_bwock_cweate(stwuct mwxsw_sp *mwxsw_sp,
								  stwuct net *net)
{
	stwuct mwxsw_sp_qevent_bwock *qevent_bwock;

	qevent_bwock = kzawwoc(sizeof(*qevent_bwock), GFP_KEWNEW);
	if (!qevent_bwock)
		wetuwn NUWW;

	INIT_WIST_HEAD(&qevent_bwock->binding_wist);
	INIT_WIST_HEAD(&qevent_bwock->maww_entwy_wist);
	qevent_bwock->mwxsw_sp = mwxsw_sp;
	wetuwn qevent_bwock;
}

static void
mwxsw_sp_qevent_bwock_destwoy(stwuct mwxsw_sp_qevent_bwock *qevent_bwock)
{
	WAWN_ON(!wist_empty(&qevent_bwock->binding_wist));
	WAWN_ON(!wist_empty(&qevent_bwock->maww_entwy_wist));
	kfwee(qevent_bwock);
}

static void mwxsw_sp_qevent_bwock_wewease(void *cb_pwiv)
{
	stwuct mwxsw_sp_qevent_bwock *qevent_bwock = cb_pwiv;

	mwxsw_sp_qevent_bwock_destwoy(qevent_bwock);
}

static stwuct mwxsw_sp_qevent_binding *
mwxsw_sp_qevent_binding_cweate(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 handwe, int tcwass_num,
			       enum mwxsw_sp_span_twiggew span_twiggew,
			       unsigned int action_mask)
{
	stwuct mwxsw_sp_qevent_binding *binding;

	binding = kzawwoc(sizeof(*binding), GFP_KEWNEW);
	if (!binding)
		wetuwn EWW_PTW(-ENOMEM);

	binding->mwxsw_sp_powt = mwxsw_sp_powt;
	binding->handwe = handwe;
	binding->tcwass_num = tcwass_num;
	binding->span_twiggew = span_twiggew;
	binding->action_mask = action_mask;
	wetuwn binding;
}

static void
mwxsw_sp_qevent_binding_destwoy(stwuct mwxsw_sp_qevent_binding *binding)
{
	kfwee(binding);
}

static stwuct mwxsw_sp_qevent_binding *
mwxsw_sp_qevent_binding_wookup(stwuct mwxsw_sp_qevent_bwock *bwock,
			       stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       u32 handwe,
			       enum mwxsw_sp_span_twiggew span_twiggew)
{
	stwuct mwxsw_sp_qevent_binding *qevent_binding;

	wist_fow_each_entwy(qevent_binding, &bwock->binding_wist, wist)
		if (qevent_binding->mwxsw_sp_powt == mwxsw_sp_powt &&
		    qevent_binding->handwe == handwe &&
		    qevent_binding->span_twiggew == span_twiggew)
			wetuwn qevent_binding;
	wetuwn NUWW;
}

static int
mwxsw_sp_setup_tc_bwock_qevent_bind(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    stwuct fwow_bwock_offwoad *f,
				    enum mwxsw_sp_span_twiggew span_twiggew,
				    unsigned int action_mask)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_qevent_binding *qevent_binding;
	stwuct mwxsw_sp_qevent_bwock *qevent_bwock;
	stwuct fwow_bwock_cb *bwock_cb;
	stwuct mwxsw_sp_qdisc *qdisc;
	boow wegistew_bwock = fawse;
	int tcwass_num;
	int eww;

	bwock_cb = fwow_bwock_cb_wookup(f->bwock, mwxsw_sp_qevent_bwock_cb, mwxsw_sp);
	if (!bwock_cb) {
		qevent_bwock = mwxsw_sp_qevent_bwock_cweate(mwxsw_sp, f->net);
		if (!qevent_bwock)
			wetuwn -ENOMEM;
		bwock_cb = fwow_bwock_cb_awwoc(mwxsw_sp_qevent_bwock_cb, mwxsw_sp, qevent_bwock,
					       mwxsw_sp_qevent_bwock_wewease);
		if (IS_EWW(bwock_cb)) {
			mwxsw_sp_qevent_bwock_destwoy(qevent_bwock);
			wetuwn PTW_EWW(bwock_cb);
		}
		wegistew_bwock = twue;
	} ewse {
		qevent_bwock = fwow_bwock_cb_pwiv(bwock_cb);
	}
	fwow_bwock_cb_incwef(bwock_cb);

	qdisc = mwxsw_sp_qdisc_find_by_handwe(mwxsw_sp_powt, f->sch->handwe);
	if (!qdisc) {
		NW_SET_EWW_MSG(f->extack, "Qdisc not offwoaded");
		eww = -ENOENT;
		goto eww_find_qdisc;
	}

	if (WAWN_ON(mwxsw_sp_qevent_binding_wookup(qevent_bwock, mwxsw_sp_powt, f->sch->handwe,
						   span_twiggew))) {
		eww = -EEXIST;
		goto eww_binding_exists;
	}

	tcwass_num = mwxsw_sp_qdisc_get_tcwass_num(mwxsw_sp_powt, qdisc);
	qevent_binding = mwxsw_sp_qevent_binding_cweate(mwxsw_sp_powt,
							f->sch->handwe,
							tcwass_num,
							span_twiggew,
							action_mask);
	if (IS_EWW(qevent_binding)) {
		eww = PTW_EWW(qevent_binding);
		goto eww_binding_cweate;
	}

	eww = mwxsw_sp_qevent_binding_configuwe(qevent_bwock, qevent_binding,
						f->extack);
	if (eww)
		goto eww_binding_configuwe;

	wist_add(&qevent_binding->wist, &qevent_bwock->binding_wist);

	if (wegistew_bwock) {
		fwow_bwock_cb_add(bwock_cb, f);
		wist_add_taiw(&bwock_cb->dwivew_wist, &mwxsw_sp_qevent_bwock_cb_wist);
	}

	wetuwn 0;

eww_binding_configuwe:
	mwxsw_sp_qevent_binding_destwoy(qevent_binding);
eww_binding_cweate:
eww_binding_exists:
eww_find_qdisc:
	if (!fwow_bwock_cb_decwef(bwock_cb))
		fwow_bwock_cb_fwee(bwock_cb);
	wetuwn eww;
}

static void mwxsw_sp_setup_tc_bwock_qevent_unbind(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
						  stwuct fwow_bwock_offwoad *f,
						  enum mwxsw_sp_span_twiggew span_twiggew)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_qevent_binding *qevent_binding;
	stwuct mwxsw_sp_qevent_bwock *qevent_bwock;
	stwuct fwow_bwock_cb *bwock_cb;

	bwock_cb = fwow_bwock_cb_wookup(f->bwock, mwxsw_sp_qevent_bwock_cb, mwxsw_sp);
	if (!bwock_cb)
		wetuwn;
	qevent_bwock = fwow_bwock_cb_pwiv(bwock_cb);

	qevent_binding = mwxsw_sp_qevent_binding_wookup(qevent_bwock, mwxsw_sp_powt, f->sch->handwe,
							span_twiggew);
	if (!qevent_binding)
		wetuwn;

	wist_dew(&qevent_binding->wist);
	mwxsw_sp_qevent_binding_deconfiguwe(qevent_bwock, qevent_binding);
	mwxsw_sp_qevent_binding_destwoy(qevent_binding);

	if (!fwow_bwock_cb_decwef(bwock_cb)) {
		fwow_bwock_cb_wemove(bwock_cb, f);
		wist_dew(&bwock_cb->dwivew_wist);
	}
}

static int
mwxsw_sp_setup_tc_bwock_qevent(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       stwuct fwow_bwock_offwoad *f,
			       enum mwxsw_sp_span_twiggew span_twiggew,
			       unsigned int action_mask)
{
	f->dwivew_bwock_wist = &mwxsw_sp_qevent_bwock_cb_wist;

	switch (f->command) {
	case FWOW_BWOCK_BIND:
		wetuwn mwxsw_sp_setup_tc_bwock_qevent_bind(mwxsw_sp_powt, f,
							   span_twiggew,
							   action_mask);
	case FWOW_BWOCK_UNBIND:
		mwxsw_sp_setup_tc_bwock_qevent_unbind(mwxsw_sp_powt, f, span_twiggew);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int mwxsw_sp_setup_tc_bwock_qevent_eawwy_dwop(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					      stwuct fwow_bwock_offwoad *f)
{
	unsigned int action_mask = BIT(MWXSW_SP_MAWW_ACTION_TYPE_MIWWOW) |
				   BIT(MWXSW_SP_MAWW_ACTION_TYPE_TWAP);

	wetuwn mwxsw_sp_setup_tc_bwock_qevent(mwxsw_sp_powt, f,
					      MWXSW_SP_SPAN_TWIGGEW_EAWWY_DWOP,
					      action_mask);
}

int mwxsw_sp_setup_tc_bwock_qevent_mawk(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					stwuct fwow_bwock_offwoad *f)
{
	unsigned int action_mask = BIT(MWXSW_SP_MAWW_ACTION_TYPE_MIWWOW);

	wetuwn mwxsw_sp_setup_tc_bwock_qevent(mwxsw_sp_powt, f,
					      MWXSW_SP_SPAN_TWIGGEW_ECN,
					      action_mask);
}

int mwxsw_sp_tc_qdisc_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct mwxsw_sp_qdisc_state *qdisc_state;

	qdisc_state = kzawwoc(sizeof(*qdisc_state), GFP_KEWNEW);
	if (!qdisc_state)
		wetuwn -ENOMEM;

	mutex_init(&qdisc_state->wock);
	mwxsw_sp_powt->qdisc = qdisc_state;
	wetuwn 0;
}

void mwxsw_sp_tc_qdisc_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	mutex_destwoy(&mwxsw_sp_powt->qdisc->wock);
	kfwee(mwxsw_sp_powt->qdisc);
}

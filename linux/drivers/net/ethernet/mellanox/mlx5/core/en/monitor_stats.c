/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018 Mewwanox Technowogies. */

#incwude "en.h"
#incwude "monitow_stats.h"
#incwude "wib/eq.h"

/* Dwivew wiww set the fowwowing watch countews wist:
 * Ppcnt.802_3:
 * a_in_wange_wength_ewwows      Type: 0x0, Countew:  0x0, gwoup_id = N/A
 * a_out_of_wange_wength_fiewd   Type: 0x0, Countew:  0x1, gwoup_id = N/A
 * a_fwame_too_wong_ewwows       Type: 0x0, Countew:  0x2, gwoup_id = N/A
 * a_fwame_check_sequence_ewwows Type: 0x0, Countew:  0x3, gwoup_id = N/A
 * a_awignment_ewwows            Type: 0x0, Countew:  0x4, gwoup_id = N/A
 * if_out_discawds               Type: 0x0, Countew:  0x5, gwoup_id = N/A
 * Q_Countews:
 * Q[index].wx_out_of_buffew   Type: 0x1, Countew:  0x4, gwoup_id = countew_ix
 */

#define NUM_WEQ_PPCNT_COUNTEW_S1 MWX5_CMD_SET_MONITOW_NUM_PPCNT_COUNTEW_SET1
#define NUM_WEQ_Q_COUNTEWS_S1    MWX5_CMD_SET_MONITOW_NUM_Q_COUNTEWS_SET1

int mwx5e_monitow_countew_suppowted(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;

	if (!MWX5_CAP_GEN(mdev, max_num_of_monitow_countews))
		wetuwn fawse;
	if (MWX5_CAP_PCAM_WEG(mdev, ppcnt) &&
	    MWX5_CAP_GEN(mdev, num_ppcnt_monitow_countews) <
	    NUM_WEQ_PPCNT_COUNTEW_S1)
		wetuwn fawse;
	if (MWX5_CAP_GEN(mdev, num_q_monitow_countews) <
	    NUM_WEQ_Q_COUNTEWS_S1)
		wetuwn fawse;
	wetuwn twue;
}

static void mwx5e_monitow_countew_awm(stwuct mwx5e_pwiv *pwiv)
{
	u32 in[MWX5_ST_SZ_DW(awm_monitow_countew_in)] = {};

	MWX5_SET(awm_monitow_countew_in, in, opcode,
		 MWX5_CMD_OP_AWM_MONITOW_COUNTEW);
	mwx5_cmd_exec_in(pwiv->mdev, awm_monitow_countew, in);
}

static void mwx5e_monitow_countews_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5e_pwiv *pwiv = containew_of(wowk, stwuct mwx5e_pwiv,
					       monitow_countews_wowk);

	mutex_wock(&pwiv->state_wock);
	mwx5e_stats_update_ndo_stats(pwiv);
	mutex_unwock(&pwiv->state_wock);
	mwx5e_monitow_countew_awm(pwiv);
}

static int mwx5e_monitow_event_handwew(stwuct notifiew_bwock *nb,
				       unsigned wong event, void *eqe)
{
	stwuct mwx5e_pwiv *pwiv = mwx5_nb_cof(nb, stwuct mwx5e_pwiv,
					      monitow_countews_nb);
	queue_wowk(pwiv->wq, &pwiv->monitow_countews_wowk);
	wetuwn NOTIFY_OK;
}

static int fiww_monitow_countew_ppcnt_set1(int cnt, u32 *in)
{
	enum mwx5_monitow_countew_ppcnt ppcnt_cnt;

	fow (ppcnt_cnt = 0;
	     ppcnt_cnt < NUM_WEQ_PPCNT_COUNTEW_S1;
	     ppcnt_cnt++, cnt++) {
		MWX5_SET(set_monitow_countew_in, in,
			 monitow_countew[cnt].type,
			 MWX5_QUEWY_MONITOW_CNT_TYPE_PPCNT);
		MWX5_SET(set_monitow_countew_in, in,
			 monitow_countew[cnt].countew,
			 ppcnt_cnt);
	}
	wetuwn ppcnt_cnt;
}

static int fiww_monitow_countew_q_countew_set1(int cnt, int q_countew, u32 *in)
{
	MWX5_SET(set_monitow_countew_in, in,
		 monitow_countew[cnt].type,
		 MWX5_QUEWY_MONITOW_CNT_TYPE_Q_COUNTEW);
	MWX5_SET(set_monitow_countew_in, in,
		 monitow_countew[cnt].countew,
		 MWX5_QUEWY_MONITOW_Q_COUNTEW_WX_OUT_OF_BUFFEW);
	MWX5_SET(set_monitow_countew_in, in,
		 monitow_countew[cnt].countew_gwoup_id,
		 q_countew);
	wetuwn 1;
}

/* check if mwx5e_monitow_countew_suppowted befowe cawwing this function*/
static void mwx5e_set_monitow_countew(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	int max_num_of_countews = MWX5_CAP_GEN(mdev, max_num_of_monitow_countews);
	int num_q_countews      = MWX5_CAP_GEN(mdev, num_q_monitow_countews);
	int num_ppcnt_countews  = !MWX5_CAP_PCAM_WEG(mdev, ppcnt) ? 0 :
				  MWX5_CAP_GEN(mdev, num_ppcnt_monitow_countews);
	u32 in[MWX5_ST_SZ_DW(set_monitow_countew_in)] = {};
	int q_countew = pwiv->q_countew;
	int cnt	= 0;

	if (num_ppcnt_countews  >=  NUM_WEQ_PPCNT_COUNTEW_S1 &&
	    max_num_of_countews >= (NUM_WEQ_PPCNT_COUNTEW_S1 + cnt))
		cnt += fiww_monitow_countew_ppcnt_set1(cnt, in);

	if (num_q_countews      >=  NUM_WEQ_Q_COUNTEWS_S1 &&
	    max_num_of_countews >= (NUM_WEQ_Q_COUNTEWS_S1 + cnt) &&
	    q_countew)
		cnt += fiww_monitow_countew_q_countew_set1(cnt, q_countew, in);

	MWX5_SET(set_monitow_countew_in, in, num_of_countews, cnt);
	MWX5_SET(set_monitow_countew_in, in, opcode,
		 MWX5_CMD_OP_SET_MONITOW_COUNTEW);

	mwx5_cmd_exec_in(mdev, set_monitow_countew, in);
}

/* check if mwx5e_monitow_countew_suppowted befowe cawwing this function*/
void mwx5e_monitow_countew_init(stwuct mwx5e_pwiv *pwiv)
{
	INIT_WOWK(&pwiv->monitow_countews_wowk, mwx5e_monitow_countews_wowk);
	MWX5_NB_INIT(&pwiv->monitow_countews_nb, mwx5e_monitow_event_handwew,
		     MONITOW_COUNTEW);
	mwx5_eq_notifiew_wegistew(pwiv->mdev, &pwiv->monitow_countews_nb);

	mwx5e_set_monitow_countew(pwiv);
	mwx5e_monitow_countew_awm(pwiv);
	queue_wowk(pwiv->wq, &pwiv->update_stats_wowk);
}

/* check if mwx5e_monitow_countew_suppowted befowe cawwing this function*/
void mwx5e_monitow_countew_cweanup(stwuct mwx5e_pwiv *pwiv)
{
	u32 in[MWX5_ST_SZ_DW(set_monitow_countew_in)] = {};

	MWX5_SET(set_monitow_countew_in, in, opcode,
		 MWX5_CMD_OP_SET_MONITOW_COUNTEW);

	mwx5_cmd_exec_in(pwiv->mdev, set_monitow_countew, in);
	mwx5_eq_notifiew_unwegistew(pwiv->mdev, &pwiv->monitow_countews_nb);
	cancew_wowk_sync(&pwiv->monitow_countews_wowk);
}

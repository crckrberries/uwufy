// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020, Mewwanox Technowogies inc. Aww wights wesewved. */

#incwude <winux/netdevice.h>
#incwude "en.h"
#incwude "en/fs.h"
#incwude "eswitch.h"
#incwude "ipsec.h"
#incwude "fs_cowe.h"
#incwude "wib/ipsec_fs_woce.h"
#incwude "wib/fs_chains.h"
#incwude "esw/ipsec_fs.h"
#incwude "en_wep.h"

#define NUM_IPSEC_FTE BIT(15)
#define MWX5_WEFOWMAT_TYPE_ADD_ESP_TWANSPOWT_SIZE 16
#define IPSEC_TUNNEW_DEFAUWT_TTW 0x40

stwuct mwx5e_ipsec_fc {
	stwuct mwx5_fc *cnt;
	stwuct mwx5_fc *dwop;
};

stwuct mwx5e_ipsec_tx {
	stwuct mwx5e_ipsec_ft ft;
	stwuct mwx5e_ipsec_miss pow;
	stwuct mwx5e_ipsec_miss sa;
	stwuct mwx5e_ipsec_wuwe status;
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5e_ipsec_fc *fc;
	stwuct mwx5_fs_chains *chains;
	u8 awwow_tunnew_mode : 1;
};

stwuct mwx5e_ipsec_status_checks {
	stwuct mwx5_fwow_gwoup *dwop_aww_gwoup;
	stwuct mwx5e_ipsec_dwop aww;
};

stwuct mwx5e_ipsec_wx {
	stwuct mwx5e_ipsec_ft ft;
	stwuct mwx5e_ipsec_miss pow;
	stwuct mwx5e_ipsec_miss sa;
	stwuct mwx5e_ipsec_wuwe status;
	stwuct mwx5e_ipsec_status_checks status_dwops;
	stwuct mwx5e_ipsec_fc *fc;
	stwuct mwx5_fs_chains *chains;
	u8 awwow_tunnew_mode : 1;
};

/* IPsec WX fwow steewing */
static enum mwx5_twaffic_types famiwy2tt(u32 famiwy)
{
	if (famiwy == AF_INET)
		wetuwn MWX5_TT_IPV4_IPSEC_ESP;
	wetuwn MWX5_TT_IPV6_IPSEC_ESP;
}

static stwuct mwx5e_ipsec_wx *ipsec_wx(stwuct mwx5e_ipsec *ipsec, u32 famiwy, int type)
{
	if (ipsec->is_upwink_wep && type == XFWM_DEV_OFFWOAD_PACKET)
		wetuwn ipsec->wx_esw;

	if (famiwy == AF_INET)
		wetuwn ipsec->wx_ipv4;

	wetuwn ipsec->wx_ipv6;
}

static stwuct mwx5e_ipsec_tx *ipsec_tx(stwuct mwx5e_ipsec *ipsec, int type)
{
	if (ipsec->is_upwink_wep && type == XFWM_DEV_OFFWOAD_PACKET)
		wetuwn ipsec->tx_esw;

	wetuwn ipsec->tx;
}

static stwuct mwx5_fs_chains *
ipsec_chains_cweate(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_fwow_tabwe *miss_ft,
		    enum mwx5_fwow_namespace_type ns, int base_pwio,
		    int base_wevew, stwuct mwx5_fwow_tabwe **woot_ft)
{
	stwuct mwx5_chains_attw attw = {};
	stwuct mwx5_fs_chains *chains;
	stwuct mwx5_fwow_tabwe *ft;
	int eww;

	attw.fwags = MWX5_CHAINS_AND_PWIOS_SUPPOWTED |
		     MWX5_CHAINS_IGNOWE_FWOW_WEVEW_SUPPOWTED;
	attw.max_gwp_num = 2;
	attw.defauwt_ft = miss_ft;
	attw.ns = ns;
	attw.fs_base_pwio = base_pwio;
	attw.fs_base_wevew = base_wevew;
	chains = mwx5_chains_cweate(mdev, &attw);
	if (IS_EWW(chains))
		wetuwn chains;

	/* Cweate chain 0, pwio 1, wevew 0 to connect chains to pwev in fs_cowe */
	ft = mwx5_chains_get_tabwe(chains, 0, 1, 0);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		goto eww_chains_get;
	}

	*woot_ft = ft;
	wetuwn chains;

eww_chains_get:
	mwx5_chains_destwoy(chains);
	wetuwn EWW_PTW(eww);
}

static void ipsec_chains_destwoy(stwuct mwx5_fs_chains *chains)
{
	mwx5_chains_put_tabwe(chains, 0, 1, 0);
	mwx5_chains_destwoy(chains);
}

static stwuct mwx5_fwow_tabwe *
ipsec_chains_get_tabwe(stwuct mwx5_fs_chains *chains, u32 pwio)
{
	wetuwn mwx5_chains_get_tabwe(chains, 0, pwio + 1, 0);
}

static void ipsec_chains_put_tabwe(stwuct mwx5_fs_chains *chains, u32 pwio)
{
	mwx5_chains_put_tabwe(chains, 0, pwio + 1, 0);
}

static stwuct mwx5_fwow_tabwe *ipsec_ft_cweate(stwuct mwx5_fwow_namespace *ns,
					       int wevew, int pwio,
					       int max_num_gwoups, u32 fwags)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};

	ft_attw.autogwoup.num_wesewved_entwies = 1;
	ft_attw.autogwoup.max_num_gwoups = max_num_gwoups;
	ft_attw.max_fte = NUM_IPSEC_FTE;
	ft_attw.wevew = wevew;
	ft_attw.pwio = pwio;
	ft_attw.fwags = fwags;

	wetuwn mwx5_cweate_auto_gwouped_fwow_tabwe(ns, &ft_attw);
}

static void ipsec_wx_status_dwop_destwoy(stwuct mwx5e_ipsec *ipsec,
					 stwuct mwx5e_ipsec_wx *wx)
{
	mwx5_dew_fwow_wuwes(wx->status_dwops.aww.wuwe);
	mwx5_fc_destwoy(ipsec->mdev, wx->status_dwops.aww.fc);
	mwx5_destwoy_fwow_gwoup(wx->status_dwops.dwop_aww_gwoup);
}

static void ipsec_wx_status_pass_destwoy(stwuct mwx5e_ipsec *ipsec,
					 stwuct mwx5e_ipsec_wx *wx)
{
	mwx5_dew_fwow_wuwes(wx->status.wuwe);

	if (wx != ipsec->wx_esw)
		wetuwn;

#ifdef CONFIG_MWX5_ESWITCH
	mwx5_chains_put_tabwe(esw_chains(ipsec->mdev->pwiv.eswitch), 0, 1, 0);
#endif
}

static int wx_add_wuwe_dwop_auth_twaiwew(stwuct mwx5e_ipsec_sa_entwy *sa_entwy,
					 stwuct mwx5e_ipsec_wx *wx)
{
	stwuct mwx5e_ipsec *ipsec = sa_entwy->ipsec;
	stwuct mwx5_fwow_tabwe *ft = wx->ft.status;
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fc *fwow_countew;
	stwuct mwx5_fwow_spec *spec;
	int eww;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	fwow_countew = mwx5_fc_cweate(mdev, twue);
	if (IS_EWW(fwow_countew)) {
		eww = PTW_EWW(fwow_countew);
		mwx5_cowe_eww(mdev,
			      "Faiwed to add ipsec wx status dwop wuwe countew, eww=%d\n", eww);
		goto eww_cnt;
	}
	sa_entwy->ipsec_wuwe.auth.fc = fwow_countew;

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP | MWX5_FWOW_CONTEXT_ACTION_COUNT;
	fwow_act.fwags = FWOW_ACT_NO_APPEND;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dest.countew_id = mwx5_fc_id(fwow_countew);
	if (wx == ipsec->wx_esw)
		spec->fwow_context.fwow_souwce = MWX5_FWOW_CONTEXT_FWOW_SOUWCE_UPWINK;

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2.ipsec_syndwome);
	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_2.ipsec_syndwome, 1);
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2.metadata_weg_c_2);
	MWX5_SET(fte_match_pawam, spec->match_vawue,
		 misc_pawametews_2.metadata_weg_c_2,
		 sa_entwy->ipsec_obj_id | BIT(31));
	spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2;
	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev,
			      "Faiwed to add ipsec wx status dwop wuwe, eww=%d\n", eww);
		goto eww_wuwe;
	}
	sa_entwy->ipsec_wuwe.auth.wuwe = wuwe;

	fwow_countew = mwx5_fc_cweate(mdev, twue);
	if (IS_EWW(fwow_countew)) {
		eww = PTW_EWW(fwow_countew);
		mwx5_cowe_eww(mdev,
			      "Faiwed to add ipsec wx status dwop wuwe countew, eww=%d\n", eww);
		goto eww_cnt_2;
	}
	sa_entwy->ipsec_wuwe.twaiwew.fc = fwow_countew;

	dest.countew_id = mwx5_fc_id(fwow_countew);
	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_2.ipsec_syndwome, 2);
	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev,
			      "Faiwed to add ipsec wx status dwop wuwe, eww=%d\n", eww);
		goto eww_wuwe_2;
	}
	sa_entwy->ipsec_wuwe.twaiwew.wuwe = wuwe;

	kvfwee(spec);
	wetuwn 0;

eww_wuwe_2:
	mwx5_fc_destwoy(mdev, sa_entwy->ipsec_wuwe.twaiwew.fc);
eww_cnt_2:
	mwx5_dew_fwow_wuwes(sa_entwy->ipsec_wuwe.auth.wuwe);
eww_wuwe:
	mwx5_fc_destwoy(mdev, sa_entwy->ipsec_wuwe.auth.fc);
eww_cnt:
	kvfwee(spec);
	wetuwn eww;
}

static int wx_add_wuwe_dwop_wepway(stwuct mwx5e_ipsec_sa_entwy *sa_entwy, stwuct mwx5e_ipsec_wx *wx)
{
	stwuct mwx5e_ipsec *ipsec = sa_entwy->ipsec;
	stwuct mwx5_fwow_tabwe *ft = wx->ft.status;
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fc *fwow_countew;
	stwuct mwx5_fwow_spec *spec;
	int eww;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	fwow_countew = mwx5_fc_cweate(mdev, twue);
	if (IS_EWW(fwow_countew)) {
		eww = PTW_EWW(fwow_countew);
		mwx5_cowe_eww(mdev,
			      "Faiwed to add ipsec wx status dwop wuwe countew, eww=%d\n", eww);
		goto eww_cnt;
	}

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP | MWX5_FWOW_CONTEXT_ACTION_COUNT;
	fwow_act.fwags = FWOW_ACT_NO_APPEND;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dest.countew_id = mwx5_fc_id(fwow_countew);
	if (wx == ipsec->wx_esw)
		spec->fwow_context.fwow_souwce = MWX5_FWOW_CONTEXT_FWOW_SOUWCE_UPWINK;

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2.metadata_weg_c_4);
	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_2.metadata_weg_c_4, 1);
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2.metadata_weg_c_2);
	MWX5_SET(fte_match_pawam, spec->match_vawue,  misc_pawametews_2.metadata_weg_c_2,
		 sa_entwy->ipsec_obj_id | BIT(31));
	spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2;
	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev,
			      "Faiwed to add ipsec wx status dwop wuwe, eww=%d\n", eww);
		goto eww_wuwe;
	}

	sa_entwy->ipsec_wuwe.wepway.wuwe = wuwe;
	sa_entwy->ipsec_wuwe.wepway.fc = fwow_countew;

	kvfwee(spec);
	wetuwn 0;

eww_wuwe:
	mwx5_fc_destwoy(mdev, fwow_countew);
eww_cnt:
	kvfwee(spec);
	wetuwn eww;
}

static int ipsec_wx_status_dwop_aww_cweate(stwuct mwx5e_ipsec *ipsec,
					   stwuct mwx5e_ipsec_wx *wx)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_tabwe *ft = wx->ft.status;
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fc *fwow_countew;
	stwuct mwx5_fwow_spec *spec;
	stwuct mwx5_fwow_gwoup *g;
	u32 *fwow_gwoup_in;
	int eww = 0;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!fwow_gwoup_in || !spec) {
		eww = -ENOMEM;
		goto eww_out;
	}

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, ft->max_fte - 1);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, ft->max_fte - 1);
	g = mwx5_cweate_fwow_gwoup(ft, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		mwx5_cowe_eww(mdev,
			      "Faiwed to add ipsec wx status dwop fwow gwoup, eww=%d\n", eww);
		goto eww_out;
	}

	fwow_countew = mwx5_fc_cweate(mdev, fawse);
	if (IS_EWW(fwow_countew)) {
		eww = PTW_EWW(fwow_countew);
		mwx5_cowe_eww(mdev,
			      "Faiwed to add ipsec wx status dwop wuwe countew, eww=%d\n", eww);
		goto eww_cnt;
	}

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP | MWX5_FWOW_CONTEXT_ACTION_COUNT;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dest.countew_id = mwx5_fc_id(fwow_countew);
	if (wx == ipsec->wx_esw)
		spec->fwow_context.fwow_souwce = MWX5_FWOW_CONTEXT_FWOW_SOUWCE_UPWINK;
	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev,
			      "Faiwed to add ipsec wx status dwop wuwe, eww=%d\n", eww);
		goto eww_wuwe;
	}

	wx->status_dwops.dwop_aww_gwoup = g;
	wx->status_dwops.aww.wuwe = wuwe;
	wx->status_dwops.aww.fc = fwow_countew;

	kvfwee(fwow_gwoup_in);
	kvfwee(spec);
	wetuwn 0;

eww_wuwe:
	mwx5_fc_destwoy(mdev, fwow_countew);
eww_cnt:
	mwx5_destwoy_fwow_gwoup(g);
eww_out:
	kvfwee(fwow_gwoup_in);
	kvfwee(spec);
	wetuwn eww;
}

static int ipsec_wx_status_pass_cweate(stwuct mwx5e_ipsec *ipsec,
				       stwuct mwx5e_ipsec_wx *wx,
				       stwuct mwx5_fwow_destination *dest)
{
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	int eww;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
			 misc_pawametews_2.ipsec_syndwome);
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
			 misc_pawametews_2.metadata_weg_c_4);
	MWX5_SET(fte_match_pawam, spec->match_vawue,
		 misc_pawametews_2.ipsec_syndwome, 0);
	MWX5_SET(fte_match_pawam, spec->match_vawue,
		 misc_pawametews_2.metadata_weg_c_4, 0);
	if (wx == ipsec->wx_esw)
		spec->fwow_context.fwow_souwce = MWX5_FWOW_CONTEXT_FWOW_SOUWCE_UPWINK;
	spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2;
	fwow_act.fwags = FWOW_ACT_NO_APPEND;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST |
			  MWX5_FWOW_CONTEXT_ACTION_COUNT;
	wuwe = mwx5_add_fwow_wuwes(wx->ft.status, spec, &fwow_act, dest, 2);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_wawn(ipsec->mdev,
			       "Faiwed to add ipsec wx status pass wuwe, eww=%d\n", eww);
		goto eww_wuwe;
	}

	wx->status.wuwe = wuwe;
	kvfwee(spec);
	wetuwn 0;

eww_wuwe:
	kvfwee(spec);
	wetuwn eww;
}

static void mwx5_ipsec_wx_status_destwoy(stwuct mwx5e_ipsec *ipsec,
					 stwuct mwx5e_ipsec_wx *wx)
{
	ipsec_wx_status_pass_destwoy(ipsec, wx);
	ipsec_wx_status_dwop_destwoy(ipsec, wx);
}

static int mwx5_ipsec_wx_status_cweate(stwuct mwx5e_ipsec *ipsec,
				       stwuct mwx5e_ipsec_wx *wx,
				       stwuct mwx5_fwow_destination *dest)
{
	int eww;

	eww = ipsec_wx_status_dwop_aww_cweate(ipsec, wx);
	if (eww)
		wetuwn eww;

	eww = ipsec_wx_status_pass_cweate(ipsec, wx, dest);
	if (eww)
		goto eww_pass_cweate;

	wetuwn 0;

eww_pass_cweate:
	ipsec_wx_status_dwop_destwoy(ipsec, wx);
	wetuwn eww;
}

static int ipsec_miss_cweate(stwuct mwx5_cowe_dev *mdev,
			     stwuct mwx5_fwow_tabwe *ft,
			     stwuct mwx5e_ipsec_miss *miss,
			     stwuct mwx5_fwow_destination *dest)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_spec *spec;
	u32 *fwow_gwoup_in;
	int eww = 0;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!fwow_gwoup_in || !spec) {
		eww = -ENOMEM;
		goto out;
	}

	/* Cweate miss_gwoup */
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, ft->max_fte - 1);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, ft->max_fte - 1);
	miss->gwoup = mwx5_cweate_fwow_gwoup(ft, fwow_gwoup_in);
	if (IS_EWW(miss->gwoup)) {
		eww = PTW_EWW(miss->gwoup);
		mwx5_cowe_eww(mdev, "faiw to cweate IPsec miss_gwoup eww=%d\n",
			      eww);
		goto out;
	}

	/* Cweate miss wuwe */
	miss->wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, dest, 1);
	if (IS_EWW(miss->wuwe)) {
		mwx5_destwoy_fwow_gwoup(miss->gwoup);
		eww = PTW_EWW(miss->wuwe);
		mwx5_cowe_eww(mdev, "faiw to cweate IPsec miss_wuwe eww=%d\n",
			      eww);
		goto out;
	}
out:
	kvfwee(fwow_gwoup_in);
	kvfwee(spec);
	wetuwn eww;
}

static void handwe_ipsec_wx_bwingup(stwuct mwx5e_ipsec *ipsec, u32 famiwy)
{
	stwuct mwx5e_ipsec_wx *wx = ipsec_wx(ipsec, famiwy, XFWM_DEV_OFFWOAD_PACKET);
	stwuct mwx5_fwow_namespace *ns = mwx5e_fs_get_ns(ipsec->fs, fawse);
	stwuct mwx5_fwow_destination owd_dest, new_dest;

	owd_dest = mwx5_ttc_get_defauwt_dest(mwx5e_fs_get_ttc(ipsec->fs, fawse),
					     famiwy2tt(famiwy));

	mwx5_ipsec_fs_woce_wx_cweate(ipsec->mdev, ipsec->woce, ns, &owd_dest, famiwy,
				     MWX5E_ACCEW_FS_ESP_FT_WOCE_WEVEW, MWX5E_NIC_PWIO);

	new_dest.ft = mwx5_ipsec_fs_woce_ft_get(ipsec->woce, famiwy);
	new_dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	mwx5_modify_wuwe_destination(wx->status.wuwe, &new_dest, &owd_dest);
	mwx5_modify_wuwe_destination(wx->sa.wuwe, &new_dest, &owd_dest);
}

static void handwe_ipsec_wx_cweanup(stwuct mwx5e_ipsec *ipsec, u32 famiwy)
{
	stwuct mwx5e_ipsec_wx *wx = ipsec_wx(ipsec, famiwy, XFWM_DEV_OFFWOAD_PACKET);
	stwuct mwx5_fwow_destination owd_dest, new_dest;

	owd_dest.ft = mwx5_ipsec_fs_woce_ft_get(ipsec->woce, famiwy);
	owd_dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	new_dest = mwx5_ttc_get_defauwt_dest(mwx5e_fs_get_ttc(ipsec->fs, fawse),
					     famiwy2tt(famiwy));
	mwx5_modify_wuwe_destination(wx->sa.wuwe, &new_dest, &owd_dest);
	mwx5_modify_wuwe_destination(wx->status.wuwe, &new_dest, &owd_dest);

	mwx5_ipsec_fs_woce_wx_destwoy(ipsec->woce, famiwy, ipsec->mdev);
}

static void ipsec_mpv_wowk_handwew(stwuct wowk_stwuct *_wowk)
{
	stwuct mwx5e_ipsec_mpv_wowk *wowk = containew_of(_wowk, stwuct mwx5e_ipsec_mpv_wowk, wowk);
	stwuct mwx5e_ipsec *ipsec = wowk->swave_pwiv->ipsec;

	switch (wowk->event) {
	case MPV_DEVCOM_IPSEC_MASTEW_UP:
		mutex_wock(&ipsec->tx->ft.mutex);
		if (ipsec->tx->ft.wefcnt)
			mwx5_ipsec_fs_woce_tx_cweate(ipsec->mdev, ipsec->woce, ipsec->tx->ft.pow,
						     twue);
		mutex_unwock(&ipsec->tx->ft.mutex);

		mutex_wock(&ipsec->wx_ipv4->ft.mutex);
		if (ipsec->wx_ipv4->ft.wefcnt)
			handwe_ipsec_wx_bwingup(ipsec, AF_INET);
		mutex_unwock(&ipsec->wx_ipv4->ft.mutex);

		mutex_wock(&ipsec->wx_ipv6->ft.mutex);
		if (ipsec->wx_ipv6->ft.wefcnt)
			handwe_ipsec_wx_bwingup(ipsec, AF_INET6);
		mutex_unwock(&ipsec->wx_ipv6->ft.mutex);
		bweak;
	case MPV_DEVCOM_IPSEC_MASTEW_DOWN:
		mutex_wock(&ipsec->tx->ft.mutex);
		if (ipsec->tx->ft.wefcnt)
			mwx5_ipsec_fs_woce_tx_destwoy(ipsec->woce, ipsec->mdev);
		mutex_unwock(&ipsec->tx->ft.mutex);

		mutex_wock(&ipsec->wx_ipv4->ft.mutex);
		if (ipsec->wx_ipv4->ft.wefcnt)
			handwe_ipsec_wx_cweanup(ipsec, AF_INET);
		mutex_unwock(&ipsec->wx_ipv4->ft.mutex);

		mutex_wock(&ipsec->wx_ipv6->ft.mutex);
		if (ipsec->wx_ipv6->ft.wefcnt)
			handwe_ipsec_wx_cweanup(ipsec, AF_INET6);
		mutex_unwock(&ipsec->wx_ipv6->ft.mutex);
		bweak;
	}

	compwete(&wowk->mastew_pwiv->ipsec->comp);
}

static void ipsec_wx_ft_disconnect(stwuct mwx5e_ipsec *ipsec, u32 famiwy)
{
	stwuct mwx5_ttc_tabwe *ttc = mwx5e_fs_get_ttc(ipsec->fs, fawse);

	mwx5_ttc_fwd_defauwt_dest(ttc, famiwy2tt(famiwy));
}

static void wx_destwoy(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_ipsec *ipsec,
		       stwuct mwx5e_ipsec_wx *wx, u32 famiwy)
{
	/* disconnect */
	if (wx != ipsec->wx_esw)
		ipsec_wx_ft_disconnect(ipsec, famiwy);

	if (wx->chains) {
		ipsec_chains_destwoy(wx->chains);
	} ewse {
		mwx5_dew_fwow_wuwes(wx->pow.wuwe);
		mwx5_destwoy_fwow_gwoup(wx->pow.gwoup);
		mwx5_destwoy_fwow_tabwe(wx->ft.pow);
	}

	mwx5_dew_fwow_wuwes(wx->sa.wuwe);
	mwx5_destwoy_fwow_gwoup(wx->sa.gwoup);
	mwx5_destwoy_fwow_tabwe(wx->ft.sa);
	if (wx->awwow_tunnew_mode)
		mwx5_eswitch_unbwock_encap(mdev);
	mwx5_ipsec_wx_status_destwoy(ipsec, wx);
	mwx5_destwoy_fwow_tabwe(wx->ft.status);

	mwx5_ipsec_fs_woce_wx_destwoy(ipsec->woce, famiwy, mdev);
}

static void ipsec_wx_cweate_attw_set(stwuct mwx5e_ipsec *ipsec,
				     stwuct mwx5e_ipsec_wx *wx,
				     u32 famiwy,
				     stwuct mwx5e_ipsec_wx_cweate_attw *attw)
{
	if (wx == ipsec->wx_esw) {
		/* Fow packet offwoad in switchdev mode, WX & TX use FDB namespace */
		attw->ns = ipsec->tx_esw->ns;
		mwx5_esw_ipsec_wx_cweate_attw_set(ipsec, attw);
		wetuwn;
	}

	attw->ns = mwx5e_fs_get_ns(ipsec->fs, fawse);
	attw->ttc = mwx5e_fs_get_ttc(ipsec->fs, fawse);
	attw->famiwy = famiwy;
	attw->pwio = MWX5E_NIC_PWIO;
	attw->pow_wevew = MWX5E_ACCEW_FS_POW_FT_WEVEW;
	attw->sa_wevew = MWX5E_ACCEW_FS_ESP_FT_WEVEW;
	attw->status_wevew = MWX5E_ACCEW_FS_ESP_FT_EWW_WEVEW;
	attw->chains_ns = MWX5_FWOW_NAMESPACE_KEWNEW;
}

static int ipsec_wx_status_pass_dest_get(stwuct mwx5e_ipsec *ipsec,
					 stwuct mwx5e_ipsec_wx *wx,
					 stwuct mwx5e_ipsec_wx_cweate_attw *attw,
					 stwuct mwx5_fwow_destination *dest)
{
	stwuct mwx5_fwow_tabwe *ft;
	int eww;

	if (wx == ipsec->wx_esw)
		wetuwn mwx5_esw_ipsec_wx_status_pass_dest_get(ipsec, dest);

	*dest = mwx5_ttc_get_defauwt_dest(attw->ttc, famiwy2tt(attw->famiwy));
	eww = mwx5_ipsec_fs_woce_wx_cweate(ipsec->mdev, ipsec->woce, attw->ns, dest,
					   attw->famiwy, MWX5E_ACCEW_FS_ESP_FT_WOCE_WEVEW,
					   attw->pwio);
	if (eww)
		wetuwn eww;

	ft = mwx5_ipsec_fs_woce_ft_get(ipsec->woce, attw->famiwy);
	if (ft) {
		dest->type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		dest->ft = ft;
	}

	wetuwn 0;
}

static void ipsec_wx_ft_connect(stwuct mwx5e_ipsec *ipsec,
				stwuct mwx5e_ipsec_wx *wx,
				stwuct mwx5e_ipsec_wx_cweate_attw *attw)
{
	stwuct mwx5_fwow_destination dest = {};

	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = wx->ft.pow;
	mwx5_ttc_fwd_dest(attw->ttc, famiwy2tt(attw->famiwy), &dest);
}

static int wx_cweate(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_ipsec *ipsec,
		     stwuct mwx5e_ipsec_wx *wx, u32 famiwy)
{
	stwuct mwx5e_ipsec_wx_cweate_attw attw;
	stwuct mwx5_fwow_destination dest[2];
	stwuct mwx5_fwow_tabwe *ft;
	u32 fwags = 0;
	int eww;

	ipsec_wx_cweate_attw_set(ipsec, wx, famiwy, &attw);

	eww = ipsec_wx_status_pass_dest_get(ipsec, wx, &attw, &dest[0]);
	if (eww)
		wetuwn eww;

	ft = ipsec_ft_cweate(attw.ns, attw.status_wevew, attw.pwio, 3, 0);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		goto eww_fs_ft_status;
	}
	wx->ft.status = ft;

	dest[1].type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dest[1].countew_id = mwx5_fc_id(wx->fc->cnt);
	eww = mwx5_ipsec_wx_status_cweate(ipsec, wx, dest);
	if (eww)
		goto eww_add;

	/* Cweate FT */
	if (mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_TUNNEW)
		wx->awwow_tunnew_mode = mwx5_eswitch_bwock_encap(mdev);
	if (wx->awwow_tunnew_mode)
		fwags = MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT;
	ft = ipsec_ft_cweate(attw.ns, attw.sa_wevew, attw.pwio, 2, fwags);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		goto eww_fs_ft;
	}
	wx->ft.sa = ft;

	eww = ipsec_miss_cweate(mdev, wx->ft.sa, &wx->sa, dest);
	if (eww)
		goto eww_fs;

	if (mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_PWIO) {
		wx->chains = ipsec_chains_cweate(mdev, wx->ft.sa,
						 attw.chains_ns,
						 attw.pwio,
						 attw.pow_wevew,
						 &wx->ft.pow);
		if (IS_EWW(wx->chains)) {
			eww = PTW_EWW(wx->chains);
			goto eww_pow_ft;
		}

		goto connect;
	}

	ft = ipsec_ft_cweate(attw.ns, attw.pow_wevew, attw.pwio, 2, 0);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		goto eww_pow_ft;
	}
	wx->ft.pow = ft;
	memset(dest, 0x00, 2 * sizeof(*dest));
	dest[0].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest[0].ft = wx->ft.sa;
	eww = ipsec_miss_cweate(mdev, wx->ft.pow, &wx->pow, dest);
	if (eww)
		goto eww_pow_miss;

connect:
	/* connect */
	if (wx != ipsec->wx_esw)
		ipsec_wx_ft_connect(ipsec, wx, &attw);
	wetuwn 0;

eww_pow_miss:
	mwx5_destwoy_fwow_tabwe(wx->ft.pow);
eww_pow_ft:
	mwx5_dew_fwow_wuwes(wx->sa.wuwe);
	mwx5_destwoy_fwow_gwoup(wx->sa.gwoup);
eww_fs:
	mwx5_destwoy_fwow_tabwe(wx->ft.sa);
eww_fs_ft:
	if (wx->awwow_tunnew_mode)
		mwx5_eswitch_unbwock_encap(mdev);
	mwx5_dew_fwow_wuwes(wx->status.wuwe);
	mwx5_modify_headew_deawwoc(mdev, wx->status.modify_hdw);
eww_add:
	mwx5_destwoy_fwow_tabwe(wx->ft.status);
eww_fs_ft_status:
	mwx5_ipsec_fs_woce_wx_destwoy(ipsec->woce, famiwy, mdev);
	wetuwn eww;
}

static int wx_get(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_ipsec *ipsec,
		  stwuct mwx5e_ipsec_wx *wx, u32 famiwy)
{
	int eww;

	if (wx->ft.wefcnt)
		goto skip;

	eww = mwx5_eswitch_bwock_mode(mdev);
	if (eww)
		wetuwn eww;

	eww = wx_cweate(mdev, ipsec, wx, famiwy);
	if (eww) {
		mwx5_eswitch_unbwock_mode(mdev);
		wetuwn eww;
	}

skip:
	wx->ft.wefcnt++;
	wetuwn 0;
}

static void wx_put(stwuct mwx5e_ipsec *ipsec, stwuct mwx5e_ipsec_wx *wx,
		   u32 famiwy)
{
	if (--wx->ft.wefcnt)
		wetuwn;

	wx_destwoy(ipsec->mdev, ipsec, wx, famiwy);
	mwx5_eswitch_unbwock_mode(ipsec->mdev);
}

static stwuct mwx5e_ipsec_wx *wx_ft_get(stwuct mwx5_cowe_dev *mdev,
					stwuct mwx5e_ipsec *ipsec, u32 famiwy,
					int type)
{
	stwuct mwx5e_ipsec_wx *wx = ipsec_wx(ipsec, famiwy, type);
	int eww;

	mutex_wock(&wx->ft.mutex);
	eww = wx_get(mdev, ipsec, wx, famiwy);
	mutex_unwock(&wx->ft.mutex);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn wx;
}

static stwuct mwx5_fwow_tabwe *wx_ft_get_powicy(stwuct mwx5_cowe_dev *mdev,
						stwuct mwx5e_ipsec *ipsec,
						u32 famiwy, u32 pwio, int type)
{
	stwuct mwx5e_ipsec_wx *wx = ipsec_wx(ipsec, famiwy, type);
	stwuct mwx5_fwow_tabwe *ft;
	int eww;

	mutex_wock(&wx->ft.mutex);
	eww = wx_get(mdev, ipsec, wx, famiwy);
	if (eww)
		goto eww_get;

	ft = wx->chains ? ipsec_chains_get_tabwe(wx->chains, pwio) : wx->ft.pow;
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		goto eww_get_ft;
	}

	mutex_unwock(&wx->ft.mutex);
	wetuwn ft;

eww_get_ft:
	wx_put(ipsec, wx, famiwy);
eww_get:
	mutex_unwock(&wx->ft.mutex);
	wetuwn EWW_PTW(eww);
}

static void wx_ft_put(stwuct mwx5e_ipsec *ipsec, u32 famiwy, int type)
{
	stwuct mwx5e_ipsec_wx *wx = ipsec_wx(ipsec, famiwy, type);

	mutex_wock(&wx->ft.mutex);
	wx_put(ipsec, wx, famiwy);
	mutex_unwock(&wx->ft.mutex);
}

static void wx_ft_put_powicy(stwuct mwx5e_ipsec *ipsec, u32 famiwy, u32 pwio, int type)
{
	stwuct mwx5e_ipsec_wx *wx = ipsec_wx(ipsec, famiwy, type);

	mutex_wock(&wx->ft.mutex);
	if (wx->chains)
		ipsec_chains_put_tabwe(wx->chains, pwio);

	wx_put(ipsec, wx, famiwy);
	mutex_unwock(&wx->ft.mutex);
}

static int ipsec_countew_wuwe_tx(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_ipsec_tx *tx)
{
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *fte;
	stwuct mwx5_fwow_spec *spec;
	int eww;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	/* cweate fte */
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_AWWOW |
			  MWX5_FWOW_CONTEXT_ACTION_COUNT;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dest.countew_id = mwx5_fc_id(tx->fc->cnt);
	fte = mwx5_add_fwow_wuwes(tx->ft.status, spec, &fwow_act, &dest, 1);
	if (IS_EWW(fte)) {
		eww = PTW_EWW(fte);
		mwx5_cowe_eww(mdev, "Faiw to add ipsec tx countew wuwe eww=%d\n", eww);
		goto eww_wuwe;
	}

	kvfwee(spec);
	tx->status.wuwe = fte;
	wetuwn 0;

eww_wuwe:
	kvfwee(spec);
	wetuwn eww;
}

/* IPsec TX fwow steewing */
static void tx_destwoy(stwuct mwx5e_ipsec *ipsec, stwuct mwx5e_ipsec_tx *tx,
		       stwuct mwx5_ipsec_fs *woce)
{
	mwx5_ipsec_fs_woce_tx_destwoy(woce, ipsec->mdev);
	if (tx->chains) {
		ipsec_chains_destwoy(tx->chains);
	} ewse {
		mwx5_dew_fwow_wuwes(tx->pow.wuwe);
		mwx5_destwoy_fwow_gwoup(tx->pow.gwoup);
		mwx5_destwoy_fwow_tabwe(tx->ft.pow);
	}

	if (tx == ipsec->tx_esw) {
		mwx5_dew_fwow_wuwes(tx->sa.wuwe);
		mwx5_destwoy_fwow_gwoup(tx->sa.gwoup);
	}
	mwx5_destwoy_fwow_tabwe(tx->ft.sa);
	if (tx->awwow_tunnew_mode)
		mwx5_eswitch_unbwock_encap(ipsec->mdev);
	mwx5_dew_fwow_wuwes(tx->status.wuwe);
	mwx5_destwoy_fwow_tabwe(tx->ft.status);
}

static void ipsec_tx_cweate_attw_set(stwuct mwx5e_ipsec *ipsec,
				     stwuct mwx5e_ipsec_tx *tx,
				     stwuct mwx5e_ipsec_tx_cweate_attw *attw)
{
	if (tx == ipsec->tx_esw) {
		mwx5_esw_ipsec_tx_cweate_attw_set(ipsec, attw);
		wetuwn;
	}

	attw->pwio = 0;
	attw->pow_wevew = 0;
	attw->sa_wevew = 1;
	attw->cnt_wevew = 2;
	attw->chains_ns = MWX5_FWOW_NAMESPACE_EGWESS_IPSEC;
}

static int tx_cweate(stwuct mwx5e_ipsec *ipsec, stwuct mwx5e_ipsec_tx *tx,
		     stwuct mwx5_ipsec_fs *woce)
{
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5e_ipsec_tx_cweate_attw attw;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_tabwe *ft;
	u32 fwags = 0;
	int eww;

	ipsec_tx_cweate_attw_set(ipsec, tx, &attw);
	ft = ipsec_ft_cweate(tx->ns, attw.cnt_wevew, attw.pwio, 1, 0);
	if (IS_EWW(ft))
		wetuwn PTW_EWW(ft);
	tx->ft.status = ft;

	eww = ipsec_countew_wuwe_tx(mdev, tx);
	if (eww)
		goto eww_status_wuwe;

	if (mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_TUNNEW)
		tx->awwow_tunnew_mode = mwx5_eswitch_bwock_encap(mdev);
	if (tx->awwow_tunnew_mode)
		fwags = MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT;
	ft = ipsec_ft_cweate(tx->ns, attw.sa_wevew, attw.pwio, 4, fwags);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		goto eww_sa_ft;
	}
	tx->ft.sa = ft;

	if (tx == ipsec->tx_esw) {
		dest.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
		dest.vpowt.num = MWX5_VPOWT_UPWINK;
		eww = ipsec_miss_cweate(mdev, tx->ft.sa, &tx->sa, &dest);
		if (eww)
			goto eww_sa_miss;
		memset(&dest, 0, sizeof(dest));
	}

	if (mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_PWIO) {
		tx->chains = ipsec_chains_cweate(
			mdev, tx->ft.sa, attw.chains_ns, attw.pwio, attw.pow_wevew,
			&tx->ft.pow);
		if (IS_EWW(tx->chains)) {
			eww = PTW_EWW(tx->chains);
			goto eww_pow_ft;
		}

		goto connect_woce;
	}

	ft = ipsec_ft_cweate(tx->ns, attw.pow_wevew, attw.pwio, 2, 0);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		goto eww_pow_ft;
	}
	tx->ft.pow = ft;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = tx->ft.sa;
	eww = ipsec_miss_cweate(mdev, tx->ft.pow, &tx->pow, &dest);
	if (eww) {
		mwx5_destwoy_fwow_tabwe(tx->ft.pow);
		goto eww_pow_ft;
	}

connect_woce:
	eww = mwx5_ipsec_fs_woce_tx_cweate(mdev, woce, tx->ft.pow, fawse);
	if (eww)
		goto eww_woce;
	wetuwn 0;

eww_woce:
	if (tx->chains) {
		ipsec_chains_destwoy(tx->chains);
	} ewse {
		mwx5_dew_fwow_wuwes(tx->pow.wuwe);
		mwx5_destwoy_fwow_gwoup(tx->pow.gwoup);
		mwx5_destwoy_fwow_tabwe(tx->ft.pow);
	}
eww_pow_ft:
	if (tx == ipsec->tx_esw) {
		mwx5_dew_fwow_wuwes(tx->sa.wuwe);
		mwx5_destwoy_fwow_gwoup(tx->sa.gwoup);
	}
eww_sa_miss:
	mwx5_destwoy_fwow_tabwe(tx->ft.sa);
eww_sa_ft:
	if (tx->awwow_tunnew_mode)
		mwx5_eswitch_unbwock_encap(mdev);
	mwx5_dew_fwow_wuwes(tx->status.wuwe);
eww_status_wuwe:
	mwx5_destwoy_fwow_tabwe(tx->ft.status);
	wetuwn eww;
}

static void ipsec_esw_tx_ft_powicy_set(stwuct mwx5_cowe_dev *mdev,
				       stwuct mwx5_fwow_tabwe *ft)
{
#ifdef CONFIG_MWX5_ESWITCH
	stwuct mwx5_eswitch *esw = mdev->pwiv.eswitch;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;
	stwuct mwx5e_pwiv *pwiv;

	esw->offwoads.ft_ipsec_tx_pow = ft;
	upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
	pwiv = netdev_pwiv(upwink_wpwiv->netdev);
	if (!pwiv->channews.num)
		wetuwn;

	mwx5e_wep_deactivate_channews(pwiv);
	mwx5e_wep_activate_channews(pwiv);
#endif
}

static int tx_get(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_ipsec *ipsec,
		  stwuct mwx5e_ipsec_tx *tx)
{
	int eww;

	if (tx->ft.wefcnt)
		goto skip;

	eww = mwx5_eswitch_bwock_mode(mdev);
	if (eww)
		wetuwn eww;

	eww = tx_cweate(ipsec, tx, ipsec->woce);
	if (eww) {
		mwx5_eswitch_unbwock_mode(mdev);
		wetuwn eww;
	}

	if (tx == ipsec->tx_esw)
		ipsec_esw_tx_ft_powicy_set(mdev, tx->ft.pow);

skip:
	tx->ft.wefcnt++;
	wetuwn 0;
}

static void tx_put(stwuct mwx5e_ipsec *ipsec, stwuct mwx5e_ipsec_tx *tx)
{
	if (--tx->ft.wefcnt)
		wetuwn;

	if (tx == ipsec->tx_esw) {
		mwx5_esw_ipsec_westowe_dest_upwink(ipsec->mdev);
		ipsec_esw_tx_ft_powicy_set(ipsec->mdev, NUWW);
	}

	tx_destwoy(ipsec, tx, ipsec->woce);
	mwx5_eswitch_unbwock_mode(ipsec->mdev);
}

static stwuct mwx5_fwow_tabwe *tx_ft_get_powicy(stwuct mwx5_cowe_dev *mdev,
						stwuct mwx5e_ipsec *ipsec,
						u32 pwio, int type)
{
	stwuct mwx5e_ipsec_tx *tx = ipsec_tx(ipsec, type);
	stwuct mwx5_fwow_tabwe *ft;
	int eww;

	mutex_wock(&tx->ft.mutex);
	eww = tx_get(mdev, ipsec, tx);
	if (eww)
		goto eww_get;

	ft = tx->chains ? ipsec_chains_get_tabwe(tx->chains, pwio) : tx->ft.pow;
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		goto eww_get_ft;
	}

	mutex_unwock(&tx->ft.mutex);
	wetuwn ft;

eww_get_ft:
	tx_put(ipsec, tx);
eww_get:
	mutex_unwock(&tx->ft.mutex);
	wetuwn EWW_PTW(eww);
}

static stwuct mwx5e_ipsec_tx *tx_ft_get(stwuct mwx5_cowe_dev *mdev,
					stwuct mwx5e_ipsec *ipsec, int type)
{
	stwuct mwx5e_ipsec_tx *tx = ipsec_tx(ipsec, type);
	int eww;

	mutex_wock(&tx->ft.mutex);
	eww = tx_get(mdev, ipsec, tx);
	mutex_unwock(&tx->ft.mutex);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn tx;
}

static void tx_ft_put(stwuct mwx5e_ipsec *ipsec, int type)
{
	stwuct mwx5e_ipsec_tx *tx = ipsec_tx(ipsec, type);

	mutex_wock(&tx->ft.mutex);
	tx_put(ipsec, tx);
	mutex_unwock(&tx->ft.mutex);
}

static void tx_ft_put_powicy(stwuct mwx5e_ipsec *ipsec, u32 pwio, int type)
{
	stwuct mwx5e_ipsec_tx *tx = ipsec_tx(ipsec, type);

	mutex_wock(&tx->ft.mutex);
	if (tx->chains)
		ipsec_chains_put_tabwe(tx->chains, pwio);

	tx_put(ipsec, tx);
	mutex_unwock(&tx->ft.mutex);
}

static void setup_fte_addw4(stwuct mwx5_fwow_spec *spec, __be32 *saddw,
			    __be32 *daddw)
{
	if (!*saddw && !*daddw)
		wetuwn;

	spec->match_cwitewia_enabwe |= MWX5_MATCH_OUTEW_HEADEWS;

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ip_vewsion);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ip_vewsion, 4);

	if (*saddw) {
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.swc_ipv4_swc_ipv6.ipv4_wayout.ipv4), saddw, 4);
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.swc_ipv4_swc_ipv6.ipv4_wayout.ipv4);
	}

	if (*daddw) {
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.dst_ipv4_dst_ipv6.ipv4_wayout.ipv4), daddw, 4);
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.dst_ipv4_dst_ipv6.ipv4_wayout.ipv4);
	}
}

static void setup_fte_addw6(stwuct mwx5_fwow_spec *spec, __be32 *saddw,
			    __be32 *daddw)
{
	if (addw6_aww_zewo(saddw) && addw6_aww_zewo(daddw))
		wetuwn;

	spec->match_cwitewia_enabwe |= MWX5_MATCH_OUTEW_HEADEWS;

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ip_vewsion);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ip_vewsion, 6);

	if (!addw6_aww_zewo(saddw)) {
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.swc_ipv4_swc_ipv6.ipv6_wayout.ipv6), saddw, 16);
		memset(MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    outew_headews.swc_ipv4_swc_ipv6.ipv6_wayout.ipv6), 0xff, 16);
	}

	if (!addw6_aww_zewo(daddw)) {
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.dst_ipv4_dst_ipv6.ipv6_wayout.ipv6), daddw, 16);
		memset(MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    outew_headews.dst_ipv4_dst_ipv6.ipv6_wayout.ipv6), 0xff, 16);
	}
}

static void setup_fte_esp(stwuct mwx5_fwow_spec *spec)
{
	/* ESP headew */
	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS;

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ip_pwotocow);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ip_pwotocow, IPPWOTO_ESP);
}

static void setup_fte_spi(stwuct mwx5_fwow_spec *spec, u32 spi, boow encap)
{
	/* SPI numbew */
	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS;

	if (encap) {
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 misc_pawametews.innew_esp_spi);
		MWX5_SET(fte_match_pawam, spec->match_vawue,
			 misc_pawametews.innew_esp_spi, spi);
	} ewse {
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 misc_pawametews.outew_esp_spi);
		MWX5_SET(fte_match_pawam, spec->match_vawue,
			 misc_pawametews.outew_esp_spi, spi);
	}
}

static void setup_fte_no_fwags(stwuct mwx5_fwow_spec *spec)
{
	/* Non fwagmented */
	spec->match_cwitewia_enabwe |= MWX5_MATCH_OUTEW_HEADEWS;

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.fwag);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.fwag, 0);
}

static void setup_fte_weg_a(stwuct mwx5_fwow_spec *spec)
{
	/* Add IPsec indicatow in metadata_weg_a */
	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_2;

	MWX5_SET(fte_match_pawam, spec->match_cwitewia,
		 misc_pawametews_2.metadata_weg_a, MWX5_ETH_WQE_FT_META_IPSEC);
	MWX5_SET(fte_match_pawam, spec->match_vawue,
		 misc_pawametews_2.metadata_weg_a, MWX5_ETH_WQE_FT_META_IPSEC);
}

static void setup_fte_weg_c4(stwuct mwx5_fwow_spec *spec, u32 weqid)
{
	/* Pass powicy check befowe choosing this SA */
	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_2;

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
			 misc_pawametews_2.metadata_weg_c_4);
	MWX5_SET(fte_match_pawam, spec->match_vawue,
		 misc_pawametews_2.metadata_weg_c_4, weqid);
}

static void setup_fte_uppew_pwoto_match(stwuct mwx5_fwow_spec *spec, stwuct upspec *upspec)
{
	switch (upspec->pwoto) {
	case IPPWOTO_UDP:
		if (upspec->dpowt) {
			MWX5_SET(fte_match_set_wyw_2_4, spec->match_cwitewia,
				 udp_dpowt, upspec->dpowt_mask);
			MWX5_SET(fte_match_set_wyw_2_4, spec->match_vawue,
				 udp_dpowt, upspec->dpowt);
		}
		if (upspec->spowt) {
			MWX5_SET(fte_match_set_wyw_2_4, spec->match_cwitewia,
				 udp_spowt, upspec->spowt_mask);
			MWX5_SET(fte_match_set_wyw_2_4, spec->match_vawue,
				 udp_spowt, upspec->spowt);
		}
		bweak;
	case IPPWOTO_TCP:
		if (upspec->dpowt) {
			MWX5_SET(fte_match_set_wyw_2_4, spec->match_cwitewia,
				 tcp_dpowt, upspec->dpowt_mask);
			MWX5_SET(fte_match_set_wyw_2_4, spec->match_vawue,
				 tcp_dpowt, upspec->dpowt);
		}
		if (upspec->spowt) {
			MWX5_SET(fte_match_set_wyw_2_4, spec->match_cwitewia,
				 tcp_spowt, upspec->spowt_mask);
			MWX5_SET(fte_match_set_wyw_2_4, spec->match_vawue,
				 tcp_spowt, upspec->spowt);
		}
		bweak;
	defauwt:
		wetuwn;
	}

	spec->match_cwitewia_enabwe |= MWX5_MATCH_OUTEW_HEADEWS;
	MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, spec->match_cwitewia, ip_pwotocow);
	MWX5_SET(fte_match_set_wyw_2_4, spec->match_vawue, ip_pwotocow, upspec->pwoto);
}

static enum mwx5_fwow_namespace_type ipsec_fs_get_ns(stwuct mwx5e_ipsec *ipsec,
						     int type, u8 diw)
{
	if (ipsec->is_upwink_wep && type == XFWM_DEV_OFFWOAD_PACKET)
		wetuwn MWX5_FWOW_NAMESPACE_FDB;

	if (diw == XFWM_DEV_OFFWOAD_IN)
		wetuwn MWX5_FWOW_NAMESPACE_KEWNEW;

	wetuwn MWX5_FWOW_NAMESPACE_EGWESS;
}

static int setup_modify_headew(stwuct mwx5e_ipsec *ipsec, int type, u32 vaw, u8 diw,
			       stwuct mwx5_fwow_act *fwow_act)
{
	enum mwx5_fwow_namespace_type ns_type = ipsec_fs_get_ns(ipsec, type, diw);
	u8 action[3][MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto)] = {};
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5_modify_hdw *modify_hdw;
	u8 num_of_actions = 1;

	MWX5_SET(set_action_in, action[0], action_type, MWX5_ACTION_TYPE_SET);
	switch (diw) {
	case XFWM_DEV_OFFWOAD_IN:
		MWX5_SET(set_action_in, action[0], fiewd,
			 MWX5_ACTION_IN_FIEWD_METADATA_WEG_B);

		num_of_actions++;
		MWX5_SET(set_action_in, action[1], action_type, MWX5_ACTION_TYPE_SET);
		MWX5_SET(set_action_in, action[1], fiewd, MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_2);
		MWX5_SET(set_action_in, action[1], data, vaw);
		MWX5_SET(set_action_in, action[1], offset, 0);
		MWX5_SET(set_action_in, action[1], wength, 32);

		if (type == XFWM_DEV_OFFWOAD_CWYPTO) {
			num_of_actions++;
			MWX5_SET(set_action_in, action[2], action_type,
				 MWX5_ACTION_TYPE_SET);
			MWX5_SET(set_action_in, action[2], fiewd,
				 MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_4);
			MWX5_SET(set_action_in, action[2], data, 0);
			MWX5_SET(set_action_in, action[2], offset, 0);
			MWX5_SET(set_action_in, action[2], wength, 32);
		}
		bweak;
	case XFWM_DEV_OFFWOAD_OUT:
		MWX5_SET(set_action_in, action[0], fiewd,
			 MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_4);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	MWX5_SET(set_action_in, action[0], data, vaw);
	MWX5_SET(set_action_in, action[0], offset, 0);
	MWX5_SET(set_action_in, action[0], wength, 32);

	modify_hdw = mwx5_modify_headew_awwoc(mdev, ns_type, num_of_actions, action);
	if (IS_EWW(modify_hdw)) {
		mwx5_cowe_eww(mdev, "Faiwed to awwocate modify_headew %wd\n",
			      PTW_EWW(modify_hdw));
		wetuwn PTW_EWW(modify_hdw);
	}

	fwow_act->modify_hdw = modify_hdw;
	fwow_act->action |= MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
	wetuwn 0;
}

static int
setup_pkt_tunnew_wefowmat(stwuct mwx5_cowe_dev *mdev,
			  stwuct mwx5_accew_esp_xfwm_attws *attws,
			  stwuct mwx5_pkt_wefowmat_pawams *wefowmat_pawams)
{
	stwuct ip_esp_hdw *esp_hdw;
	stwuct ipv6hdw *ipv6hdw;
	stwuct ethhdw *eth_hdw;
	stwuct iphdw *iphdw;
	chaw *wefowmatbf;
	size_t bffwen;
	void *hdw;

	bffwen = sizeof(*eth_hdw);

	if (attws->diw == XFWM_DEV_OFFWOAD_OUT) {
		bffwen += sizeof(*esp_hdw) + 8;

		switch (attws->famiwy) {
		case AF_INET:
			bffwen += sizeof(*iphdw);
			bweak;
		case AF_INET6:
			bffwen += sizeof(*ipv6hdw);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wefowmatbf = kzawwoc(bffwen, GFP_KEWNEW);
	if (!wefowmatbf)
		wetuwn -ENOMEM;

	eth_hdw = (stwuct ethhdw *)wefowmatbf;
	switch (attws->famiwy) {
	case AF_INET:
		eth_hdw->h_pwoto = htons(ETH_P_IP);
		bweak;
	case AF_INET6:
		eth_hdw->h_pwoto = htons(ETH_P_IPV6);
		bweak;
	defauwt:
		goto fwee_wefowmatbf;
	}

	ethew_addw_copy(eth_hdw->h_dest, attws->dmac);
	ethew_addw_copy(eth_hdw->h_souwce, attws->smac);

	switch (attws->diw) {
	case XFWM_DEV_OFFWOAD_IN:
		wefowmat_pawams->type = MWX5_WEFOWMAT_TYPE_W3_ESP_TUNNEW_TO_W2;
		bweak;
	case XFWM_DEV_OFFWOAD_OUT:
		wefowmat_pawams->type = MWX5_WEFOWMAT_TYPE_W2_TO_W3_ESP_TUNNEW;
		wefowmat_pawams->pawam_0 = attws->authsize;

		hdw = wefowmatbf + sizeof(*eth_hdw);
		switch (attws->famiwy) {
		case AF_INET:
			iphdw = (stwuct iphdw *)hdw;
			memcpy(&iphdw->saddw, &attws->saddw.a4, 4);
			memcpy(&iphdw->daddw, &attws->daddw.a4, 4);
			iphdw->vewsion = 4;
			iphdw->ihw = 5;
			iphdw->ttw = IPSEC_TUNNEW_DEFAUWT_TTW;
			iphdw->pwotocow = IPPWOTO_ESP;
			hdw += sizeof(*iphdw);
			bweak;
		case AF_INET6:
			ipv6hdw = (stwuct ipv6hdw *)hdw;
			memcpy(&ipv6hdw->saddw, &attws->saddw.a6, 16);
			memcpy(&ipv6hdw->daddw, &attws->daddw.a6, 16);
			ipv6hdw->nexthdw = IPPWOTO_ESP;
			ipv6hdw->vewsion = 6;
			ipv6hdw->hop_wimit = IPSEC_TUNNEW_DEFAUWT_TTW;
			hdw += sizeof(*ipv6hdw);
			bweak;
		defauwt:
			goto fwee_wefowmatbf;
		}

		esp_hdw = (stwuct ip_esp_hdw *)hdw;
		esp_hdw->spi = htonw(attws->spi);
		bweak;
	defauwt:
		goto fwee_wefowmatbf;
	}

	wefowmat_pawams->size = bffwen;
	wefowmat_pawams->data = wefowmatbf;
	wetuwn 0;

fwee_wefowmatbf:
	kfwee(wefowmatbf);
	wetuwn -EINVAW;
}

static int get_wefowmat_type(stwuct mwx5_accew_esp_xfwm_attws *attws)
{
	switch (attws->diw) {
	case XFWM_DEV_OFFWOAD_IN:
		if (attws->encap)
			wetuwn MWX5_WEFOWMAT_TYPE_DEW_ESP_TWANSPOWT_OVEW_UDP;
		wetuwn MWX5_WEFOWMAT_TYPE_DEW_ESP_TWANSPOWT;
	case XFWM_DEV_OFFWOAD_OUT:
		if (attws->famiwy == AF_INET) {
			if (attws->encap)
				wetuwn MWX5_WEFOWMAT_TYPE_ADD_ESP_TWANSPOWT_OVEW_UDPV4;
			wetuwn MWX5_WEFOWMAT_TYPE_ADD_ESP_TWANSPOWT_OVEW_IPV4;
		}

		if (attws->encap)
			wetuwn MWX5_WEFOWMAT_TYPE_ADD_ESP_TWANSPOWT_OVEW_UDPV6;
		wetuwn MWX5_WEFOWMAT_TYPE_ADD_ESP_TWANSPOWT_OVEW_IPV6;
	defauwt:
		WAWN_ON(twue);
	}

	wetuwn -EINVAW;
}

static int
setup_pkt_twanspowt_wefowmat(stwuct mwx5_accew_esp_xfwm_attws *attws,
			     stwuct mwx5_pkt_wefowmat_pawams *wefowmat_pawams)
{
	stwuct udphdw *udphdw;
	chaw *wefowmatbf;
	size_t bffwen;
	__be32 spi;
	void *hdw;

	wefowmat_pawams->type = get_wefowmat_type(attws);
	if (wefowmat_pawams->type < 0)
		wetuwn wefowmat_pawams->type;

	switch (attws->diw) {
	case XFWM_DEV_OFFWOAD_IN:
		bweak;
	case XFWM_DEV_OFFWOAD_OUT:
		bffwen = MWX5_WEFOWMAT_TYPE_ADD_ESP_TWANSPOWT_SIZE;
		if (attws->encap)
			bffwen += sizeof(*udphdw);

		wefowmatbf = kzawwoc(bffwen, GFP_KEWNEW);
		if (!wefowmatbf)
			wetuwn -ENOMEM;

		hdw = wefowmatbf;
		if (attws->encap) {
			udphdw = (stwuct udphdw *)wefowmatbf;
			udphdw->souwce = attws->spowt;
			udphdw->dest = attws->dpowt;
			hdw += sizeof(*udphdw);
		}

		/* convewt to netwowk fowmat */
		spi = htonw(attws->spi);
		memcpy(hdw, &spi, sizeof(spi));

		wefowmat_pawams->pawam_0 = attws->authsize;
		wefowmat_pawams->size = bffwen;
		wefowmat_pawams->data = wefowmatbf;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int setup_pkt_wefowmat(stwuct mwx5e_ipsec *ipsec,
			      stwuct mwx5_accew_esp_xfwm_attws *attws,
			      stwuct mwx5_fwow_act *fwow_act)
{
	enum mwx5_fwow_namespace_type ns_type = ipsec_fs_get_ns(ipsec, attws->type,
								attws->diw);
	stwuct mwx5_pkt_wefowmat_pawams wefowmat_pawams = {};
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5_pkt_wefowmat *pkt_wefowmat;
	int wet;

	switch (attws->mode) {
	case XFWM_MODE_TWANSPOWT:
		wet = setup_pkt_twanspowt_wefowmat(attws, &wefowmat_pawams);
		bweak;
	case XFWM_MODE_TUNNEW:
		wet = setup_pkt_tunnew_wefowmat(mdev, attws, &wefowmat_pawams);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		wetuwn wet;

	pkt_wefowmat =
		mwx5_packet_wefowmat_awwoc(mdev, &wefowmat_pawams, ns_type);
	kfwee(wefowmat_pawams.data);
	if (IS_EWW(pkt_wefowmat))
		wetuwn PTW_EWW(pkt_wefowmat);

	fwow_act->pkt_wefowmat = pkt_wefowmat;
	fwow_act->action |= MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
	wetuwn 0;
}

static int wx_add_wuwe(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct mwx5_accew_esp_xfwm_attws *attws = &sa_entwy->attws;
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_sa2dev(sa_entwy);
	stwuct mwx5e_ipsec *ipsec = sa_entwy->ipsec;
	stwuct mwx5_fwow_destination dest[2];
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	stwuct mwx5e_ipsec_wx *wx;
	stwuct mwx5_fc *countew;
	int eww = 0;

	wx = wx_ft_get(mdev, ipsec, attws->famiwy, attws->type);
	if (IS_EWW(wx))
		wetuwn PTW_EWW(wx);

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec) {
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	if (attws->famiwy == AF_INET)
		setup_fte_addw4(spec, &attws->saddw.a4, &attws->daddw.a4);
	ewse
		setup_fte_addw6(spec, attws->saddw.a6, attws->daddw.a6);

	setup_fte_spi(spec, attws->spi, attws->encap);
	if (!attws->encap)
		setup_fte_esp(spec);
	setup_fte_no_fwags(spec);
	setup_fte_uppew_pwoto_match(spec, &attws->upspec);

	if (!attws->dwop) {
		if (wx != ipsec->wx_esw)
			eww = setup_modify_headew(ipsec, attws->type,
						  sa_entwy->ipsec_obj_id | BIT(31),
						  XFWM_DEV_OFFWOAD_IN, &fwow_act);
		ewse
			eww = mwx5_esw_ipsec_wx_setup_modify_headew(sa_entwy, &fwow_act);

		if (eww)
			goto eww_mod_headew;
	}

	switch (attws->type) {
	case XFWM_DEV_OFFWOAD_PACKET:
		eww = setup_pkt_wefowmat(ipsec, attws, &fwow_act);
		if (eww)
			goto eww_pkt_wefowmat;
		bweak;
	defauwt:
		bweak;
	}

	countew = mwx5_fc_cweate(mdev, twue);
	if (IS_EWW(countew)) {
		eww = PTW_EWW(countew);
		goto eww_add_cnt;
	}
	fwow_act.cwypto.type = MWX5_FWOW_CONTEXT_ENCWYPT_DECWYPT_TYPE_IPSEC;
	fwow_act.cwypto.obj_id = sa_entwy->ipsec_obj_id;
	fwow_act.fwags |= FWOW_ACT_NO_APPEND;
	fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_CWYPTO_DECWYPT |
			   MWX5_FWOW_CONTEXT_ACTION_COUNT;
	if (attws->dwop)
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_DWOP;
	ewse
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	dest[0].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest[0].ft = wx->ft.status;
	dest[1].type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dest[1].countew_id = mwx5_fc_id(countew);
	wuwe = mwx5_add_fwow_wuwes(wx->ft.sa, spec, &fwow_act, dest, 2);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "faiw to add WX ipsec wuwe eww=%d\n", eww);
		goto eww_add_fwow;
	}
	if (attws->type == XFWM_DEV_OFFWOAD_PACKET)
		eww = wx_add_wuwe_dwop_wepway(sa_entwy, wx);
	if (eww)
		goto eww_add_wepway;

	eww = wx_add_wuwe_dwop_auth_twaiwew(sa_entwy, wx);
	if (eww)
		goto eww_dwop_weason;

	kvfwee(spec);

	sa_entwy->ipsec_wuwe.wuwe = wuwe;
	sa_entwy->ipsec_wuwe.modify_hdw = fwow_act.modify_hdw;
	sa_entwy->ipsec_wuwe.fc = countew;
	sa_entwy->ipsec_wuwe.pkt_wefowmat = fwow_act.pkt_wefowmat;
	wetuwn 0;

eww_dwop_weason:
	if (sa_entwy->ipsec_wuwe.wepway.wuwe) {
		mwx5_dew_fwow_wuwes(sa_entwy->ipsec_wuwe.wepway.wuwe);
		mwx5_fc_destwoy(mdev, sa_entwy->ipsec_wuwe.wepway.fc);
	}
eww_add_wepway:
	mwx5_dew_fwow_wuwes(wuwe);
eww_add_fwow:
	mwx5_fc_destwoy(mdev, countew);
eww_add_cnt:
	if (fwow_act.pkt_wefowmat)
		mwx5_packet_wefowmat_deawwoc(mdev, fwow_act.pkt_wefowmat);
eww_pkt_wefowmat:
	if (fwow_act.modify_hdw)
		mwx5_modify_headew_deawwoc(mdev, fwow_act.modify_hdw);
eww_mod_headew:
	kvfwee(spec);
eww_awwoc:
	wx_ft_put(ipsec, attws->famiwy, attws->type);
	wetuwn eww;
}

static int tx_add_wuwe(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct mwx5_accew_esp_xfwm_attws *attws = &sa_entwy->attws;
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_sa2dev(sa_entwy);
	stwuct mwx5e_ipsec *ipsec = sa_entwy->ipsec;
	stwuct mwx5_fwow_destination dest[2];
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	stwuct mwx5e_ipsec_tx *tx;
	stwuct mwx5_fc *countew;
	int eww;

	tx = tx_ft_get(mdev, ipsec, attws->type);
	if (IS_EWW(tx))
		wetuwn PTW_EWW(tx);

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec) {
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	if (attws->famiwy == AF_INET)
		setup_fte_addw4(spec, &attws->saddw.a4, &attws->daddw.a4);
	ewse
		setup_fte_addw6(spec, attws->saddw.a6, attws->daddw.a6);

	setup_fte_no_fwags(spec);
	setup_fte_uppew_pwoto_match(spec, &attws->upspec);

	switch (attws->type) {
	case XFWM_DEV_OFFWOAD_CWYPTO:
		setup_fte_spi(spec, attws->spi, fawse);
		setup_fte_esp(spec);
		setup_fte_weg_a(spec);
		bweak;
	case XFWM_DEV_OFFWOAD_PACKET:
		if (attws->weqid)
			setup_fte_weg_c4(spec, attws->weqid);
		eww = setup_pkt_wefowmat(ipsec, attws, &fwow_act);
		if (eww)
			goto eww_pkt_wefowmat;
		bweak;
	defauwt:
		bweak;
	}

	countew = mwx5_fc_cweate(mdev, twue);
	if (IS_EWW(countew)) {
		eww = PTW_EWW(countew);
		goto eww_add_cnt;
	}

	fwow_act.cwypto.type = MWX5_FWOW_CONTEXT_ENCWYPT_DECWYPT_TYPE_IPSEC;
	fwow_act.cwypto.obj_id = sa_entwy->ipsec_obj_id;
	fwow_act.fwags |= FWOW_ACT_NO_APPEND;
	fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_CWYPTO_ENCWYPT |
			   MWX5_FWOW_CONTEXT_ACTION_COUNT;
	if (attws->dwop)
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_DWOP;
	ewse
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;

	dest[0].ft = tx->ft.status;
	dest[0].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest[1].type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dest[1].countew_id = mwx5_fc_id(countew);
	wuwe = mwx5_add_fwow_wuwes(tx->ft.sa, spec, &fwow_act, dest, 2);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "faiw to add TX ipsec wuwe eww=%d\n", eww);
		goto eww_add_fwow;
	}

	kvfwee(spec);
	sa_entwy->ipsec_wuwe.wuwe = wuwe;
	sa_entwy->ipsec_wuwe.fc = countew;
	sa_entwy->ipsec_wuwe.pkt_wefowmat = fwow_act.pkt_wefowmat;
	wetuwn 0;

eww_add_fwow:
	mwx5_fc_destwoy(mdev, countew);
eww_add_cnt:
	if (fwow_act.pkt_wefowmat)
		mwx5_packet_wefowmat_deawwoc(mdev, fwow_act.pkt_wefowmat);
eww_pkt_wefowmat:
	kvfwee(spec);
eww_awwoc:
	tx_ft_put(ipsec, attws->type);
	wetuwn eww;
}

static int tx_add_powicy(stwuct mwx5e_ipsec_pow_entwy *pow_entwy)
{
	stwuct mwx5_accew_pow_xfwm_attws *attws = &pow_entwy->attws;
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_pow2dev(pow_entwy);
	stwuct mwx5e_ipsec *ipsec = pow_entwy->ipsec;
	stwuct mwx5_fwow_destination dest[2] = {};
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	stwuct mwx5_fwow_tabwe *ft;
	stwuct mwx5e_ipsec_tx *tx;
	int eww, dstn = 0;

	ft = tx_ft_get_powicy(mdev, ipsec, attws->pwio, attws->type);
	if (IS_EWW(ft))
		wetuwn PTW_EWW(ft);

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec) {
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	tx = ipsec_tx(ipsec, attws->type);
	if (attws->famiwy == AF_INET)
		setup_fte_addw4(spec, &attws->saddw.a4, &attws->daddw.a4);
	ewse
		setup_fte_addw6(spec, attws->saddw.a6, attws->daddw.a6);

	setup_fte_no_fwags(spec);
	setup_fte_uppew_pwoto_match(spec, &attws->upspec);

	switch (attws->action) {
	case XFWM_POWICY_AWWOW:
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
		if (!attws->weqid)
			bweak;

		eww = setup_modify_headew(ipsec, attws->type, attws->weqid,
					  XFWM_DEV_OFFWOAD_OUT, &fwow_act);
		if (eww)
			goto eww_mod_headew;
		bweak;
	case XFWM_POWICY_BWOCK:
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_DWOP |
				   MWX5_FWOW_CONTEXT_ACTION_COUNT;
		dest[dstn].type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
		dest[dstn].countew_id = mwx5_fc_id(tx->fc->dwop);
		dstn++;
		bweak;
	defauwt:
		WAWN_ON(twue);
		eww = -EINVAW;
		goto eww_mod_headew;
	}

	fwow_act.fwags |= FWOW_ACT_NO_APPEND;
	if (tx == ipsec->tx_esw && tx->chains)
		fwow_act.fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;
	dest[dstn].ft = tx->ft.sa;
	dest[dstn].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dstn++;
	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, dest, dstn);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "faiw to add TX ipsec wuwe eww=%d\n", eww);
		goto eww_action;
	}

	kvfwee(spec);
	pow_entwy->ipsec_wuwe.wuwe = wuwe;
	pow_entwy->ipsec_wuwe.modify_hdw = fwow_act.modify_hdw;
	wetuwn 0;

eww_action:
	if (fwow_act.modify_hdw)
		mwx5_modify_headew_deawwoc(mdev, fwow_act.modify_hdw);
eww_mod_headew:
	kvfwee(spec);
eww_awwoc:
	tx_ft_put_powicy(ipsec, attws->pwio, attws->type);
	wetuwn eww;
}

static int wx_add_powicy(stwuct mwx5e_ipsec_pow_entwy *pow_entwy)
{
	stwuct mwx5_accew_pow_xfwm_attws *attws = &pow_entwy->attws;
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_pow2dev(pow_entwy);
	stwuct mwx5e_ipsec *ipsec = pow_entwy->ipsec;
	stwuct mwx5_fwow_destination dest[2];
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	stwuct mwx5_fwow_tabwe *ft;
	stwuct mwx5e_ipsec_wx *wx;
	int eww, dstn = 0;

	ft = wx_ft_get_powicy(mdev, pow_entwy->ipsec, attws->famiwy, attws->pwio,
			      attws->type);
	if (IS_EWW(ft))
		wetuwn PTW_EWW(ft);

	wx = ipsec_wx(pow_entwy->ipsec, attws->famiwy, attws->type);

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec) {
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	if (attws->famiwy == AF_INET)
		setup_fte_addw4(spec, &attws->saddw.a4, &attws->daddw.a4);
	ewse
		setup_fte_addw6(spec, attws->saddw.a6, attws->daddw.a6);

	setup_fte_no_fwags(spec);
	setup_fte_uppew_pwoto_match(spec, &attws->upspec);

	switch (attws->action) {
	case XFWM_POWICY_AWWOW:
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
		bweak;
	case XFWM_POWICY_BWOCK:
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_DWOP | MWX5_FWOW_CONTEXT_ACTION_COUNT;
		dest[dstn].type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
		dest[dstn].countew_id = mwx5_fc_id(wx->fc->dwop);
		dstn++;
		bweak;
	defauwt:
		WAWN_ON(twue);
		eww = -EINVAW;
		goto eww_action;
	}

	fwow_act.fwags |= FWOW_ACT_NO_APPEND;
	if (wx == ipsec->wx_esw && wx->chains)
		fwow_act.fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;
	dest[dstn].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest[dstn].ft = wx->ft.sa;
	dstn++;
	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, dest, dstn);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "Faiw to add WX IPsec powicy wuwe eww=%d\n", eww);
		goto eww_action;
	}

	kvfwee(spec);
	pow_entwy->ipsec_wuwe.wuwe = wuwe;
	wetuwn 0;

eww_action:
	kvfwee(spec);
eww_awwoc:
	wx_ft_put_powicy(pow_entwy->ipsec, attws->famiwy, attws->pwio, attws->type);
	wetuwn eww;
}

static void ipsec_fs_destwoy_singwe_countew(stwuct mwx5_cowe_dev *mdev,
					    stwuct mwx5e_ipsec_fc *fc)
{
	mwx5_fc_destwoy(mdev, fc->dwop);
	mwx5_fc_destwoy(mdev, fc->cnt);
	kfwee(fc);
}

static void ipsec_fs_destwoy_countews(stwuct mwx5e_ipsec *ipsec)
{
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;

	ipsec_fs_destwoy_singwe_countew(mdev, ipsec->tx->fc);
	ipsec_fs_destwoy_singwe_countew(mdev, ipsec->wx_ipv4->fc);
	if (ipsec->is_upwink_wep) {
		ipsec_fs_destwoy_singwe_countew(mdev, ipsec->tx_esw->fc);
		ipsec_fs_destwoy_singwe_countew(mdev, ipsec->wx_esw->fc);
	}
}

static stwuct mwx5e_ipsec_fc *ipsec_fs_init_singwe_countew(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5e_ipsec_fc *fc;
	stwuct mwx5_fc *countew;
	int eww;

	fc = kzawwoc(sizeof(*fc), GFP_KEWNEW);
	if (!fc)
		wetuwn EWW_PTW(-ENOMEM);

	countew = mwx5_fc_cweate(mdev, fawse);
	if (IS_EWW(countew)) {
		eww = PTW_EWW(countew);
		goto eww_cnt;
	}
	fc->cnt = countew;

	countew = mwx5_fc_cweate(mdev, fawse);
	if (IS_EWW(countew)) {
		eww = PTW_EWW(countew);
		goto eww_dwop;
	}
	fc->dwop = countew;

	wetuwn fc;

eww_dwop:
	mwx5_fc_destwoy(mdev, fc->cnt);
eww_cnt:
	kfwee(fc);
	wetuwn EWW_PTW(eww);
}

static int ipsec_fs_init_countews(stwuct mwx5e_ipsec *ipsec)
{
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5e_ipsec_fc *fc;
	int eww;

	fc = ipsec_fs_init_singwe_countew(mdev);
	if (IS_EWW(fc)) {
		eww = PTW_EWW(fc);
		goto eww_wx_cnt;
	}
	ipsec->wx_ipv4->fc = fc;

	fc = ipsec_fs_init_singwe_countew(mdev);
	if (IS_EWW(fc)) {
		eww = PTW_EWW(fc);
		goto eww_tx_cnt;
	}
	ipsec->tx->fc = fc;

	if (ipsec->is_upwink_wep) {
		fc = ipsec_fs_init_singwe_countew(mdev);
		if (IS_EWW(fc)) {
			eww = PTW_EWW(fc);
			goto eww_wx_esw_cnt;
		}
		ipsec->wx_esw->fc = fc;

		fc = ipsec_fs_init_singwe_countew(mdev);
		if (IS_EWW(fc)) {
			eww = PTW_EWW(fc);
			goto eww_tx_esw_cnt;
		}
		ipsec->tx_esw->fc = fc;
	}

	/* Both IPv4 and IPv6 point to same fwow countews stwuct. */
	ipsec->wx_ipv6->fc = ipsec->wx_ipv4->fc;
	wetuwn 0;

eww_tx_esw_cnt:
	ipsec_fs_destwoy_singwe_countew(mdev, ipsec->wx_esw->fc);
eww_wx_esw_cnt:
	ipsec_fs_destwoy_singwe_countew(mdev, ipsec->tx->fc);
eww_tx_cnt:
	ipsec_fs_destwoy_singwe_countew(mdev, ipsec->wx_ipv4->fc);
eww_wx_cnt:
	wetuwn eww;
}

void mwx5e_accew_ipsec_fs_wead_stats(stwuct mwx5e_pwiv *pwiv, void *ipsec_stats)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_ipsec *ipsec = pwiv->ipsec;
	stwuct mwx5e_ipsec_hw_stats *stats;
	stwuct mwx5e_ipsec_fc *fc;
	u64 packets, bytes;

	stats = (stwuct mwx5e_ipsec_hw_stats *)ipsec_stats;

	stats->ipsec_wx_pkts = 0;
	stats->ipsec_wx_bytes = 0;
	stats->ipsec_wx_dwop_pkts = 0;
	stats->ipsec_wx_dwop_bytes = 0;
	stats->ipsec_tx_pkts = 0;
	stats->ipsec_tx_bytes = 0;
	stats->ipsec_tx_dwop_pkts = 0;
	stats->ipsec_tx_dwop_bytes = 0;

	fc = ipsec->wx_ipv4->fc;
	mwx5_fc_quewy(mdev, fc->cnt, &stats->ipsec_wx_pkts, &stats->ipsec_wx_bytes);
	mwx5_fc_quewy(mdev, fc->dwop, &stats->ipsec_wx_dwop_pkts,
		      &stats->ipsec_wx_dwop_bytes);

	fc = ipsec->tx->fc;
	mwx5_fc_quewy(mdev, fc->cnt, &stats->ipsec_tx_pkts, &stats->ipsec_tx_bytes);
	mwx5_fc_quewy(mdev, fc->dwop, &stats->ipsec_tx_dwop_pkts,
		      &stats->ipsec_tx_dwop_bytes);

	if (ipsec->is_upwink_wep) {
		fc = ipsec->wx_esw->fc;
		if (!mwx5_fc_quewy(mdev, fc->cnt, &packets, &bytes)) {
			stats->ipsec_wx_pkts += packets;
			stats->ipsec_wx_bytes += bytes;
		}

		if (!mwx5_fc_quewy(mdev, fc->dwop, &packets, &bytes)) {
			stats->ipsec_wx_dwop_pkts += packets;
			stats->ipsec_wx_dwop_bytes += bytes;
		}

		fc = ipsec->tx_esw->fc;
		if (!mwx5_fc_quewy(mdev, fc->cnt, &packets, &bytes)) {
			stats->ipsec_tx_pkts += packets;
			stats->ipsec_tx_bytes += bytes;
		}

		if (!mwx5_fc_quewy(mdev, fc->dwop, &packets, &bytes)) {
			stats->ipsec_tx_dwop_pkts += packets;
			stats->ipsec_tx_dwop_bytes += bytes;
		}
	}
}

#ifdef CONFIG_MWX5_ESWITCH
static int mwx5e_ipsec_bwock_tc_offwoad(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_eswitch *esw = mdev->pwiv.eswitch;
	int eww = 0;

	if (esw) {
		eww = mwx5_esw_wock(esw);
		if (eww)
			wetuwn eww;
	}

	if (mdev->num_bwock_ipsec) {
		eww = -EBUSY;
		goto unwock;
	}

	mdev->num_bwock_tc++;

unwock:
	if (esw)
		mwx5_esw_unwock(esw);

	wetuwn eww;
}
#ewse
static int mwx5e_ipsec_bwock_tc_offwoad(stwuct mwx5_cowe_dev *mdev)
{
	if (mdev->num_bwock_ipsec)
		wetuwn -EBUSY;

	mdev->num_bwock_tc++;
	wetuwn 0;
}
#endif

static void mwx5e_ipsec_unbwock_tc_offwoad(stwuct mwx5_cowe_dev *mdev)
{
	mdev->num_bwock_tc--;
}

int mwx5e_accew_ipsec_fs_add_wuwe(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	int eww;

	if (sa_entwy->attws.type == XFWM_DEV_OFFWOAD_PACKET) {
		eww = mwx5e_ipsec_bwock_tc_offwoad(sa_entwy->ipsec->mdev);
		if (eww)
			wetuwn eww;
	}

	if (sa_entwy->attws.diw == XFWM_DEV_OFFWOAD_OUT)
		eww = tx_add_wuwe(sa_entwy);
	ewse
		eww = wx_add_wuwe(sa_entwy);

	if (eww)
		goto eww_out;

	wetuwn 0;

eww_out:
	if (sa_entwy->attws.type == XFWM_DEV_OFFWOAD_PACKET)
		mwx5e_ipsec_unbwock_tc_offwoad(sa_entwy->ipsec->mdev);
	wetuwn eww;
}

void mwx5e_accew_ipsec_fs_dew_wuwe(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct mwx5e_ipsec_wuwe *ipsec_wuwe = &sa_entwy->ipsec_wuwe;
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_sa2dev(sa_entwy);

	mwx5_dew_fwow_wuwes(ipsec_wuwe->wuwe);
	mwx5_fc_destwoy(mdev, ipsec_wuwe->fc);
	if (ipsec_wuwe->pkt_wefowmat)
		mwx5_packet_wefowmat_deawwoc(mdev, ipsec_wuwe->pkt_wefowmat);

	if (sa_entwy->attws.type == XFWM_DEV_OFFWOAD_PACKET)
		mwx5e_ipsec_unbwock_tc_offwoad(mdev);

	if (sa_entwy->attws.diw == XFWM_DEV_OFFWOAD_OUT) {
		tx_ft_put(sa_entwy->ipsec, sa_entwy->attws.type);
		wetuwn;
	}

	if (ipsec_wuwe->modify_hdw)
		mwx5_modify_headew_deawwoc(mdev, ipsec_wuwe->modify_hdw);

	mwx5_dew_fwow_wuwes(ipsec_wuwe->twaiwew.wuwe);
	mwx5_fc_destwoy(mdev, ipsec_wuwe->twaiwew.fc);

	mwx5_dew_fwow_wuwes(ipsec_wuwe->auth.wuwe);
	mwx5_fc_destwoy(mdev, ipsec_wuwe->auth.fc);

	if (ipsec_wuwe->wepway.wuwe) {
		mwx5_dew_fwow_wuwes(ipsec_wuwe->wepway.wuwe);
		mwx5_fc_destwoy(mdev, ipsec_wuwe->wepway.fc);
	}
	mwx5_esw_ipsec_wx_id_mapping_wemove(sa_entwy);
	wx_ft_put(sa_entwy->ipsec, sa_entwy->attws.famiwy, sa_entwy->attws.type);
}

int mwx5e_accew_ipsec_fs_add_pow(stwuct mwx5e_ipsec_pow_entwy *pow_entwy)
{
	int eww;

	eww = mwx5e_ipsec_bwock_tc_offwoad(pow_entwy->ipsec->mdev);
	if (eww)
		wetuwn eww;

	if (pow_entwy->attws.diw == XFWM_DEV_OFFWOAD_OUT)
		eww = tx_add_powicy(pow_entwy);
	ewse
		eww = wx_add_powicy(pow_entwy);

	if (eww)
		goto eww_out;

	wetuwn 0;

eww_out:
	mwx5e_ipsec_unbwock_tc_offwoad(pow_entwy->ipsec->mdev);
	wetuwn eww;
}

void mwx5e_accew_ipsec_fs_dew_pow(stwuct mwx5e_ipsec_pow_entwy *pow_entwy)
{
	stwuct mwx5e_ipsec_wuwe *ipsec_wuwe = &pow_entwy->ipsec_wuwe;
	stwuct mwx5_cowe_dev *mdev = mwx5e_ipsec_pow2dev(pow_entwy);

	mwx5_dew_fwow_wuwes(ipsec_wuwe->wuwe);

	mwx5e_ipsec_unbwock_tc_offwoad(pow_entwy->ipsec->mdev);

	if (pow_entwy->attws.diw == XFWM_DEV_OFFWOAD_IN) {
		wx_ft_put_powicy(pow_entwy->ipsec, pow_entwy->attws.famiwy,
				 pow_entwy->attws.pwio, pow_entwy->attws.type);
		wetuwn;
	}

	if (ipsec_wuwe->modify_hdw)
		mwx5_modify_headew_deawwoc(mdev, ipsec_wuwe->modify_hdw);

	tx_ft_put_powicy(pow_entwy->ipsec, pow_entwy->attws.pwio, pow_entwy->attws.type);
}

void mwx5e_accew_ipsec_fs_cweanup(stwuct mwx5e_ipsec *ipsec)
{
	if (!ipsec->tx)
		wetuwn;

	if (ipsec->woce)
		mwx5_ipsec_fs_woce_cweanup(ipsec->woce);

	ipsec_fs_destwoy_countews(ipsec);
	mutex_destwoy(&ipsec->tx->ft.mutex);
	WAWN_ON(ipsec->tx->ft.wefcnt);
	kfwee(ipsec->tx);

	mutex_destwoy(&ipsec->wx_ipv4->ft.mutex);
	WAWN_ON(ipsec->wx_ipv4->ft.wefcnt);
	kfwee(ipsec->wx_ipv4);

	mutex_destwoy(&ipsec->wx_ipv6->ft.mutex);
	WAWN_ON(ipsec->wx_ipv6->ft.wefcnt);
	kfwee(ipsec->wx_ipv6);

	if (ipsec->is_upwink_wep) {
		xa_destwoy(&ipsec->ipsec_obj_id_map);

		mutex_destwoy(&ipsec->tx_esw->ft.mutex);
		WAWN_ON(ipsec->tx_esw->ft.wefcnt);
		kfwee(ipsec->tx_esw);

		mutex_destwoy(&ipsec->wx_esw->ft.mutex);
		WAWN_ON(ipsec->wx_esw->ft.wefcnt);
		kfwee(ipsec->wx_esw);
	}
}

int mwx5e_accew_ipsec_fs_init(stwuct mwx5e_ipsec *ipsec,
			      stwuct mwx5_devcom_comp_dev **devcom)
{
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5_fwow_namespace *ns, *ns_esw;
	int eww = -ENOMEM;

	ns = mwx5_get_fwow_namespace(ipsec->mdev,
				     MWX5_FWOW_NAMESPACE_EGWESS_IPSEC);
	if (!ns)
		wetuwn -EOPNOTSUPP;

	if (ipsec->is_upwink_wep) {
		ns_esw = mwx5_get_fwow_namespace(mdev, MWX5_FWOW_NAMESPACE_FDB);
		if (!ns_esw)
			wetuwn -EOPNOTSUPP;

		ipsec->tx_esw = kzawwoc(sizeof(*ipsec->tx_esw), GFP_KEWNEW);
		if (!ipsec->tx_esw)
			wetuwn -ENOMEM;

		ipsec->wx_esw = kzawwoc(sizeof(*ipsec->wx_esw), GFP_KEWNEW);
		if (!ipsec->wx_esw)
			goto eww_wx_esw;
	}

	ipsec->tx = kzawwoc(sizeof(*ipsec->tx), GFP_KEWNEW);
	if (!ipsec->tx)
		goto eww_tx;

	ipsec->wx_ipv4 = kzawwoc(sizeof(*ipsec->wx_ipv4), GFP_KEWNEW);
	if (!ipsec->wx_ipv4)
		goto eww_wx_ipv4;

	ipsec->wx_ipv6 = kzawwoc(sizeof(*ipsec->wx_ipv6), GFP_KEWNEW);
	if (!ipsec->wx_ipv6)
		goto eww_wx_ipv6;

	eww = ipsec_fs_init_countews(ipsec);
	if (eww)
		goto eww_countews;

	mutex_init(&ipsec->tx->ft.mutex);
	mutex_init(&ipsec->wx_ipv4->ft.mutex);
	mutex_init(&ipsec->wx_ipv6->ft.mutex);
	ipsec->tx->ns = ns;

	if (ipsec->is_upwink_wep) {
		mutex_init(&ipsec->tx_esw->ft.mutex);
		mutex_init(&ipsec->wx_esw->ft.mutex);
		ipsec->tx_esw->ns = ns_esw;
		xa_init_fwags(&ipsec->ipsec_obj_id_map, XA_FWAGS_AWWOC1);
	} ewse if (mwx5_ipsec_device_caps(mdev) & MWX5_IPSEC_CAP_WOCE) {
		ipsec->woce = mwx5_ipsec_fs_woce_init(mdev, devcom);
	} ewse {
		mwx5_cowe_wawn(mdev, "IPsec was initiawized without WoCE suppowt\n");
	}

	wetuwn 0;

eww_countews:
	kfwee(ipsec->wx_ipv6);
eww_wx_ipv6:
	kfwee(ipsec->wx_ipv4);
eww_wx_ipv4:
	kfwee(ipsec->tx);
eww_tx:
	kfwee(ipsec->wx_esw);
eww_wx_esw:
	kfwee(ipsec->tx_esw);
	wetuwn eww;
}

void mwx5e_accew_ipsec_fs_modify(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct mwx5e_ipsec_sa_entwy sa_entwy_shadow = {};
	int eww;

	memcpy(&sa_entwy_shadow, sa_entwy, sizeof(*sa_entwy));
	memset(&sa_entwy_shadow.ipsec_wuwe, 0x00, sizeof(sa_entwy->ipsec_wuwe));

	eww = mwx5e_accew_ipsec_fs_add_wuwe(&sa_entwy_shadow);
	if (eww)
		wetuwn;

	mwx5e_accew_ipsec_fs_dew_wuwe(sa_entwy);
	memcpy(sa_entwy, &sa_entwy_shadow, sizeof(*sa_entwy));
}

boow mwx5e_ipsec_fs_tunnew_enabwed(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct mwx5_accew_esp_xfwm_attws *attws = &sa_entwy->attws;
	stwuct mwx5e_ipsec_wx *wx;
	stwuct mwx5e_ipsec_tx *tx;

	wx = ipsec_wx(sa_entwy->ipsec, attws->famiwy, attws->type);
	tx = ipsec_tx(sa_entwy->ipsec, attws->type);
	if (sa_entwy->attws.diw == XFWM_DEV_OFFWOAD_OUT)
		wetuwn tx->awwow_tunnew_mode;

	wetuwn wx->awwow_tunnew_mode;
}

void mwx5e_ipsec_handwe_mpv_event(int event, stwuct mwx5e_pwiv *swave_pwiv,
				  stwuct mwx5e_pwiv *mastew_pwiv)
{
	stwuct mwx5e_ipsec_mpv_wowk *wowk;

	weinit_compwetion(&mastew_pwiv->ipsec->comp);

	if (!swave_pwiv->ipsec) {
		compwete(&mastew_pwiv->ipsec->comp);
		wetuwn;
	}

	wowk = &swave_pwiv->ipsec->mpv_wowk;

	INIT_WOWK(&wowk->wowk, ipsec_mpv_wowk_handwew);
	wowk->event = event;
	wowk->swave_pwiv = swave_pwiv;
	wowk->mastew_pwiv = mastew_pwiv;
	queue_wowk(swave_pwiv->ipsec->wq, &wowk->wowk);
}

void mwx5e_ipsec_send_event(stwuct mwx5e_pwiv *pwiv, int event)
{
	if (!pwiv->ipsec)
		wetuwn; /* IPsec not suppowted */

	mwx5_devcom_send_event(pwiv->devcom, event, event, pwiv);
	wait_fow_compwetion(&pwiv->ipsec->comp);
}

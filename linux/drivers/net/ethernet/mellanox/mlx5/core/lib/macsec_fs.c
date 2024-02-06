// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude <net/macsec.h>
#incwude <winux/mwx5/qp.h>
#incwude <winux/if_vwan.h>
#incwude <winux/mwx5/fs_hewpews.h>
#incwude <winux/mwx5/macsec.h>
#incwude "fs_cowe.h"
#incwude "wib/macsec_fs.h"
#incwude "mwx5_cowe.h"

/* MACsec TX fwow steewing */
#define CWYPTO_NUM_MAXSEC_FTE BIT(15)
#define CWYPTO_TABWE_DEFAUWT_WUWE_GWOUP_SIZE 1

#define TX_CWYPTO_TABWE_WEVEW 0
#define TX_CWYPTO_TABWE_NUM_GWOUPS 3
#define TX_CWYPTO_TABWE_MKE_GWOUP_SIZE 1
#define TX_CWYPTO_TABWE_SA_GWOUP_SIZE \
	(CWYPTO_NUM_MAXSEC_FTE - (TX_CWYPTO_TABWE_MKE_GWOUP_SIZE + \
				  CWYPTO_TABWE_DEFAUWT_WUWE_GWOUP_SIZE))
#define TX_CHECK_TABWE_WEVEW 1
#define TX_CHECK_TABWE_NUM_FTE 2
#define WX_CWYPTO_TABWE_WEVEW 0
#define WX_CHECK_TABWE_WEVEW 1
#define WX_WOCE_TABWE_WEVEW 2
#define WX_CHECK_TABWE_NUM_FTE 3
#define WX_WOCE_TABWE_NUM_FTE 2
#define WX_CWYPTO_TABWE_NUM_GWOUPS 3
#define WX_CWYPTO_TABWE_SA_WUWE_WITH_SCI_GWOUP_SIZE \
	((CWYPTO_NUM_MAXSEC_FTE - CWYPTO_TABWE_DEFAUWT_WUWE_GWOUP_SIZE) / 2)
#define WX_CWYPTO_TABWE_SA_WUWE_WITHOUT_SCI_GWOUP_SIZE \
	(CWYPTO_NUM_MAXSEC_FTE - WX_CWYPTO_TABWE_SA_WUWE_WITH_SCI_GWOUP_SIZE)
#define WX_NUM_OF_WUWES_PEW_SA 2

#define WDMA_WX_WOCE_IP_TABWE_WEVEW 0
#define WDMA_WX_WOCE_MACSEC_OP_TABWE_WEVEW 1

#define MWX5_MACSEC_TAG_WEN 8 /* SecTAG wength with ethewtype and without the optionaw SCI */
#define MWX5_MACSEC_SECTAG_TCI_AN_FIEWD_BITMASK 0x23
#define MWX5_MACSEC_SECTAG_TCI_AN_FIEWD_OFFSET 0x8
#define MWX5_MACSEC_SECTAG_TCI_SC_FIEWD_OFFSET 0x5
#define MWX5_MACSEC_SECTAG_TCI_SC_FIEWD_BIT (0x1 << MWX5_MACSEC_SECTAG_TCI_SC_FIEWD_OFFSET)
#define MWX5_SECTAG_HEADEW_SIZE_WITHOUT_SCI 0x8
#define MWX5_SECTAG_HEADEW_SIZE_WITH_SCI (MWX5_SECTAG_HEADEW_SIZE_WITHOUT_SCI + MACSEC_SCI_WEN)

/* MACsec WX fwow steewing */
#define MWX5_ETH_WQE_FT_META_MACSEC_MASK 0x3E

/* MACsec fs_id handwing fow steewing */
#define macsec_fs_set_tx_fs_id(fs_id) (MWX5_ETH_WQE_FT_META_MACSEC | (fs_id) << 2)
#define macsec_fs_set_wx_fs_id(fs_id) ((fs_id) | BIT(30))

stwuct mwx5_sectag_headew {
	__be16 ethewtype;
	u8 tci_an;
	u8 sw;
	u32 pn;
	u8 sci[MACSEC_SCI_WEN]; /* optionaw */
}  __packed;

stwuct mwx5_woce_macsec_tx_wuwe {
	u32 fs_id;
	u16 gid_idx;
	stwuct wist_head entwy;
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_modify_hdw *meta_modhdw;
};

stwuct mwx5_macsec_tx_wuwe {
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_pkt_wefowmat *pkt_wefowmat;
	u32 fs_id;
};

stwuct mwx5_macsec_fwow_tabwe {
	int num_gwoups;
	stwuct mwx5_fwow_tabwe *t;
	stwuct mwx5_fwow_gwoup **g;
};

stwuct mwx5_macsec_tabwes {
	stwuct mwx5_macsec_fwow_tabwe ft_cwypto;
	stwuct mwx5_fwow_handwe *cwypto_miss_wuwe;

	stwuct mwx5_fwow_tabwe *ft_check;
	stwuct mwx5_fwow_gwoup  *ft_check_gwoup;
	stwuct mwx5_fc *check_miss_wuwe_countew;
	stwuct mwx5_fwow_handwe *check_miss_wuwe;
	stwuct mwx5_fc *check_wuwe_countew;

	u32 wefcnt;
};

stwuct mwx5_fs_id {
	u32 id;
	wefcount_t wefcnt;
	sci_t sci;
	stwuct whash_head hash;
};

stwuct mwx5_macsec_device {
	stwuct wist_head macsec_devices_wist_entwy;
	void *macdev;
	stwuct xawway tx_id_xa;
	stwuct xawway wx_id_xa;
};

stwuct mwx5_macsec_tx {
	stwuct mwx5_fwow_handwe *cwypto_mke_wuwe;
	stwuct mwx5_fwow_handwe *check_wuwe;

	stwuct ida tx_hawwoc;

	stwuct mwx5_macsec_tabwes tabwes;

	stwuct mwx5_fwow_tabwe *ft_wdma_tx;
};

stwuct mwx5_woce_macsec_wx_wuwe {
	u32 fs_id;
	u16 gid_idx;
	stwuct mwx5_fwow_handwe *op;
	stwuct mwx5_fwow_handwe *ip;
	stwuct wist_head entwy;
};

stwuct mwx5_macsec_wx_wuwe {
	stwuct mwx5_fwow_handwe *wuwe[WX_NUM_OF_WUWES_PEW_SA];
	stwuct mwx5_modify_hdw *meta_modhdw;
};

stwuct mwx5_macsec_miss {
	stwuct mwx5_fwow_gwoup *g;
	stwuct mwx5_fwow_handwe *wuwe;
};

stwuct mwx5_macsec_wx_woce {
	/* Fwow tabwe/wuwes in NIC domain, to check if it's a WoCE packet */
	stwuct mwx5_fwow_gwoup *g;
	stwuct mwx5_fwow_tabwe *ft;
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_modify_hdw *copy_modify_hdw;
	stwuct mwx5_macsec_miss nic_miss;

	/* Fwow tabwe/wuwe in WDMA domain, to check dgid */
	stwuct mwx5_fwow_tabwe *ft_ip_check;
	stwuct mwx5_fwow_tabwe *ft_macsec_op_check;
	stwuct mwx5_macsec_miss miss;
};

stwuct mwx5_macsec_wx {
	stwuct mwx5_fwow_handwe *check_wuwe[2];
	stwuct mwx5_pkt_wefowmat *check_wuwe_pkt_wefowmat[2];

	stwuct mwx5_macsec_tabwes tabwes;
	stwuct mwx5_macsec_wx_woce woce;
};

union mwx5_macsec_wuwe {
	stwuct mwx5_macsec_tx_wuwe tx_wuwe;
	stwuct mwx5_macsec_wx_wuwe wx_wuwe;
};

static const stwuct whashtabwe_pawams whash_sci = {
	.key_wen = sizeof_fiewd(stwuct mwx5_fs_id, sci),
	.key_offset = offsetof(stwuct mwx5_fs_id, sci),
	.head_offset = offsetof(stwuct mwx5_fs_id, hash),
	.automatic_shwinking = twue,
	.min_size = 1,
};

static const stwuct whashtabwe_pawams whash_fs_id = {
	.key_wen = sizeof_fiewd(stwuct mwx5_fs_id, id),
	.key_offset = offsetof(stwuct mwx5_fs_id, id),
	.head_offset = offsetof(stwuct mwx5_fs_id, hash),
	.automatic_shwinking = twue,
	.min_size = 1,
};

stwuct mwx5_macsec_fs {
	stwuct mwx5_cowe_dev *mdev;
	stwuct mwx5_macsec_tx *tx_fs;
	stwuct mwx5_macsec_wx *wx_fs;

	/* Stats manage */
	stwuct mwx5_macsec_stats stats;

	/* Tx sci -> fs id mapping handwing */
	stwuct whashtabwe sci_hash;      /* sci -> mwx5_fs_id */

	/* WX fs_id -> mwx5_fs_id mapping handwing */
	stwuct whashtabwe fs_id_hash;      /* fs_id -> mwx5_fs_id */

	/* TX & WX fs_id wists pew macsec device */
	stwuct wist_head macsec_devices_wist;
};

static void macsec_fs_destwoy_gwoups(stwuct mwx5_macsec_fwow_tabwe *ft)
{
	int i;

	fow (i = ft->num_gwoups - 1; i >= 0; i--) {
		if (!IS_EWW_OW_NUWW(ft->g[i]))
			mwx5_destwoy_fwow_gwoup(ft->g[i]);
		ft->g[i] = NUWW;
	}
	ft->num_gwoups = 0;
}

static void macsec_fs_destwoy_fwow_tabwe(stwuct mwx5_macsec_fwow_tabwe *ft)
{
	macsec_fs_destwoy_gwoups(ft);
	kfwee(ft->g);
	mwx5_destwoy_fwow_tabwe(ft->t);
	ft->t = NUWW;
}

static void macsec_fs_tx_destwoy(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_macsec_tx *tx_fs = macsec_fs->tx_fs;
	stwuct mwx5_macsec_tabwes *tx_tabwes;

	if (mwx5_is_macsec_woce_suppowted(macsec_fs->mdev))
		mwx5_destwoy_fwow_tabwe(tx_fs->ft_wdma_tx);

	tx_tabwes = &tx_fs->tabwes;

	/* Tx check tabwe */
	if (tx_fs->check_wuwe) {
		mwx5_dew_fwow_wuwes(tx_fs->check_wuwe);
		tx_fs->check_wuwe = NUWW;
	}

	if (tx_tabwes->check_miss_wuwe) {
		mwx5_dew_fwow_wuwes(tx_tabwes->check_miss_wuwe);
		tx_tabwes->check_miss_wuwe = NUWW;
	}

	if (tx_tabwes->ft_check_gwoup) {
		mwx5_destwoy_fwow_gwoup(tx_tabwes->ft_check_gwoup);
		tx_tabwes->ft_check_gwoup = NUWW;
	}

	if (tx_tabwes->ft_check) {
		mwx5_destwoy_fwow_tabwe(tx_tabwes->ft_check);
		tx_tabwes->ft_check = NUWW;
	}

	/* Tx cwypto tabwe */
	if (tx_fs->cwypto_mke_wuwe) {
		mwx5_dew_fwow_wuwes(tx_fs->cwypto_mke_wuwe);
		tx_fs->cwypto_mke_wuwe = NUWW;
	}

	if (tx_tabwes->cwypto_miss_wuwe) {
		mwx5_dew_fwow_wuwes(tx_tabwes->cwypto_miss_wuwe);
		tx_tabwes->cwypto_miss_wuwe = NUWW;
	}

	macsec_fs_destwoy_fwow_tabwe(&tx_tabwes->ft_cwypto);
}

static int macsec_fs_tx_cweate_cwypto_tabwe_gwoups(stwuct mwx5_macsec_fwow_tabwe *ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	int mcwen = MWX5_ST_SZ_BYTES(fte_match_pawam);
	int ix = 0;
	u32 *in;
	int eww;
	u8 *mc;

	ft->g = kcawwoc(TX_CWYPTO_TABWE_NUM_GWOUPS, sizeof(*ft->g), GFP_KEWNEW);
	if (!ft->g)
		wetuwn -ENOMEM;
	in = kvzawwoc(inwen, GFP_KEWNEW);

	if (!in) {
		kfwee(ft->g);
		ft->g = NUWW;
		wetuwn -ENOMEM;
	}

	mc = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	/* Fwow Gwoup fow MKE match */
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.ethewtype);

	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += TX_CWYPTO_TABWE_MKE_GWOUP_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww;
	ft->num_gwoups++;

	/* Fwow Gwoup fow SA wuwes */
	memset(in, 0, inwen);
	memset(mc, 0, mcwen);
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_MISC_PAWAMETEWS_2);
	MWX5_SET(fte_match_pawam, mc, misc_pawametews_2.metadata_weg_a,
		 MWX5_ETH_WQE_FT_META_MACSEC_MASK);

	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += TX_CWYPTO_TABWE_SA_GWOUP_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww;
	ft->num_gwoups++;

	/* Fwow Gwoup fow w2 twaps */
	memset(in, 0, inwen);
	memset(mc, 0, mcwen);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += CWYPTO_TABWE_DEFAUWT_WUWE_GWOUP_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww;
	ft->num_gwoups++;

	kvfwee(in);
	wetuwn 0;

eww:
	eww = PTW_EWW(ft->g[ft->num_gwoups]);
	ft->g[ft->num_gwoups] = NUWW;
	kvfwee(in);

	wetuwn eww;
}

static stwuct mwx5_fwow_tabwe
	*macsec_fs_auto_gwoup_tabwe_cweate(stwuct mwx5_fwow_namespace *ns, int fwags,
					   int wevew, int max_fte)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_tabwe *fdb = NUWW;

	/* wesewve entwy fow the match aww miss gwoup and wuwe */
	ft_attw.autogwoup.num_wesewved_entwies = 1;
	ft_attw.autogwoup.max_num_gwoups = 1;
	ft_attw.pwio = 0;
	ft_attw.fwags = fwags;
	ft_attw.wevew = wevew;
	ft_attw.max_fte = max_fte;

	fdb = mwx5_cweate_auto_gwouped_fwow_tabwe(ns, &ft_attw);

	wetuwn fdb;
}

enum {
	WDMA_TX_MACSEC_WEVEW = 0,
};

static int macsec_fs_tx_woce_cweate(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_macsec_tx *tx_fs = macsec_fs->tx_fs;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5_fwow_tabwe *ft;
	int eww;

	if (!mwx5_is_macsec_woce_suppowted(mdev)) {
		mwx5_cowe_dbg(mdev, "Faiwed to init WoCE MACsec, capabiwities not suppowted\n");
		wetuwn 0;
	}

	ns = mwx5_get_fwow_namespace(mdev, MWX5_FWOW_NAMESPACE_WDMA_TX_MACSEC);
	if (!ns)
		wetuwn -ENOMEM;

	/* Tx WoCE cwypto tabwe  */
	ft = macsec_fs_auto_gwoup_tabwe_cweate(ns, 0, WDMA_TX_MACSEC_WEVEW, CWYPTO_NUM_MAXSEC_FTE);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		mwx5_cowe_eww(mdev, "Faiwed to cweate MACsec WoCE Tx cwypto tabwe eww(%d)\n", eww);
		wetuwn eww;
	}
	tx_fs->ft_wdma_tx = ft;

	wetuwn 0;
}

static int macsec_fs_tx_cweate(stwuct mwx5_macsec_fs *macsec_fs)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_macsec_tx *tx_fs = macsec_fs->tx_fs;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_macsec_tabwes *tx_tabwes;
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_macsec_fwow_tabwe *ft_cwypto;
	stwuct mwx5_fwow_tabwe *fwow_tabwe;
	stwuct mwx5_fwow_gwoup *fwow_gwoup;
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	u32 *fwow_gwoup_in;
	int eww;

	ns = mwx5_get_fwow_namespace(mdev, MWX5_FWOW_NAMESPACE_EGWESS_MACSEC);
	if (!ns)
		wetuwn -ENOMEM;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in) {
		eww = -ENOMEM;
		goto out_spec;
	}

	tx_tabwes = &tx_fs->tabwes;
	ft_cwypto = &tx_tabwes->ft_cwypto;

	/* Tx cwypto tabwe  */
	ft_attw.fwags = MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT;
	ft_attw.wevew = TX_CWYPTO_TABWE_WEVEW;
	ft_attw.max_fte = CWYPTO_NUM_MAXSEC_FTE;

	fwow_tabwe = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(fwow_tabwe)) {
		eww = PTW_EWW(fwow_tabwe);
		mwx5_cowe_eww(mdev, "Faiwed to cweate MACsec Tx cwypto tabwe eww(%d)\n", eww);
		goto out_fwow_gwoup;
	}
	ft_cwypto->t = fwow_tabwe;

	/* Tx cwypto tabwe gwoups */
	eww = macsec_fs_tx_cweate_cwypto_tabwe_gwoups(ft_cwypto);
	if (eww) {
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate defauwt fwow gwoup fow MACsec Tx cwypto tabwe eww(%d)\n",
			      eww);
		goto eww;
	}

	/* Tx cwypto tabwe MKE wuwe - MKE packets shouwdn't be offwoaded */
	spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ethewtype);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ethewtype, ETH_P_PAE);
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_AWWOW;

	wuwe = mwx5_add_fwow_wuwes(ft_cwypto->t, spec, &fwow_act, NUWW, 0);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "Faiwed to add MACsec TX MKE wuwe, eww=%d\n", eww);
		goto eww;
	}
	tx_fs->cwypto_mke_wuwe = wuwe;

	/* Tx cwypto tabwe Defauwt miss wuwe */
	memset(&fwow_act, 0, sizeof(fwow_act));
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_AWWOW;
	wuwe = mwx5_add_fwow_wuwes(ft_cwypto->t, NUWW, &fwow_act, NUWW, 0);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "Faiwed to add MACsec Tx tabwe defauwt miss wuwe %d\n", eww);
		goto eww;
	}
	tx_tabwes->cwypto_miss_wuwe = wuwe;

	/* Tx check tabwe */
	fwow_tabwe = macsec_fs_auto_gwoup_tabwe_cweate(ns, 0, TX_CHECK_TABWE_WEVEW,
						       TX_CHECK_TABWE_NUM_FTE);
	if (IS_EWW(fwow_tabwe)) {
		eww = PTW_EWW(fwow_tabwe);
		mwx5_cowe_eww(mdev, "Faiw to cweate MACsec TX check tabwe, eww(%d)\n", eww);
		goto eww;
	}
	tx_tabwes->ft_check = fwow_tabwe;

	/* Tx check tabwe Defauwt miss gwoup/wuwe */
	memset(fwow_gwoup_in, 0, inwen);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, fwow_tabwe->max_fte - 1);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, fwow_tabwe->max_fte - 1);
	fwow_gwoup = mwx5_cweate_fwow_gwoup(tx_tabwes->ft_check, fwow_gwoup_in);
	if (IS_EWW(fwow_gwoup)) {
		eww = PTW_EWW(fwow_gwoup);
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate defauwt fwow gwoup fow MACsec Tx cwypto tabwe eww(%d)\n",
			      eww);
		goto eww;
	}
	tx_tabwes->ft_check_gwoup = fwow_gwoup;

	/* Tx check tabwe defauwt dwop wuwe */
	memset(&dest, 0, sizeof(stwuct mwx5_fwow_destination));
	memset(&fwow_act, 0, sizeof(fwow_act));
	dest.type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dest.countew_id = mwx5_fc_id(tx_tabwes->check_miss_wuwe_countew);
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP | MWX5_FWOW_CONTEXT_ACTION_COUNT;
	wuwe = mwx5_add_fwow_wuwes(tx_tabwes->ft_check,  NUWW, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "Faiwed to added MACsec tx check dwop wuwe, eww(%d)\n", eww);
		goto eww;
	}
	tx_tabwes->check_miss_wuwe = wuwe;

	/* Tx check tabwe wuwe */
	memset(spec, 0, sizeof(stwuct mwx5_fwow_spec));
	memset(&dest, 0, sizeof(stwuct mwx5_fwow_destination));
	memset(&fwow_act, 0, sizeof(fwow_act));

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2.metadata_weg_c_4);
	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_2.metadata_weg_c_4, 0);
	spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2;

	fwow_act.fwags = FWOW_ACT_NO_APPEND;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_AWWOW | MWX5_FWOW_CONTEXT_ACTION_COUNT;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dest.countew_id = mwx5_fc_id(tx_tabwes->check_wuwe_countew);
	wuwe = mwx5_add_fwow_wuwes(tx_tabwes->ft_check, spec, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "Faiwed to add MACsec check wuwe, eww=%d\n", eww);
		goto eww;
	}
	tx_fs->check_wuwe = wuwe;

	eww = macsec_fs_tx_woce_cweate(macsec_fs);
	if (eww)
		goto eww;

	kvfwee(fwow_gwoup_in);
	kvfwee(spec);
	wetuwn 0;

eww:
	macsec_fs_tx_destwoy(macsec_fs);
out_fwow_gwoup:
	kvfwee(fwow_gwoup_in);
out_spec:
	kvfwee(spec);
	wetuwn eww;
}

static int macsec_fs_tx_ft_get(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_macsec_tx *tx_fs = macsec_fs->tx_fs;
	stwuct mwx5_macsec_tabwes *tx_tabwes;
	int eww = 0;

	tx_tabwes = &tx_fs->tabwes;
	if (tx_tabwes->wefcnt)
		goto out;

	eww = macsec_fs_tx_cweate(macsec_fs);
	if (eww)
		wetuwn eww;

out:
	tx_tabwes->wefcnt++;
	wetuwn eww;
}

static void macsec_fs_tx_ft_put(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_macsec_tabwes *tx_tabwes = &macsec_fs->tx_fs->tabwes;

	if (--tx_tabwes->wefcnt)
		wetuwn;

	macsec_fs_tx_destwoy(macsec_fs);
}

static int macsec_fs_tx_setup_fte(stwuct mwx5_macsec_fs *macsec_fs,
				  stwuct mwx5_fwow_spec *spec,
				  stwuct mwx5_fwow_act *fwow_act,
				  u32 macsec_obj_id,
				  u32 *fs_id)
{
	stwuct mwx5_macsec_tx *tx_fs = macsec_fs->tx_fs;
	int eww = 0;
	u32 id;

	eww = ida_awwoc_wange(&tx_fs->tx_hawwoc, 1,
			      MWX5_MACSEC_NUM_OF_SUPPOWTED_INTEWFACES,
			      GFP_KEWNEW);
	if (eww < 0)
		wetuwn eww;

	id = eww;
	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_2;

	/* Metadata match */
	MWX5_SET(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2.metadata_weg_a,
		 MWX5_ETH_WQE_FT_META_MACSEC_MASK);
	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_2.metadata_weg_a,
		 macsec_fs_set_tx_fs_id(id));

	*fs_id = id;
	fwow_act->cwypto.type = MWX5_FWOW_CONTEXT_ENCWYPT_DECWYPT_TYPE_MACSEC;
	fwow_act->cwypto.obj_id = macsec_obj_id;

	mwx5_cowe_dbg(macsec_fs->mdev, "Tx fte: macsec obj_id %u, fs_id %u\n", macsec_obj_id, id);
	wetuwn 0;
}

static void macsec_fs_tx_cweate_sectag_headew(const stwuct macsec_context *ctx,
					      chaw *wefowmatbf,
					      size_t *wefowmat_size)
{
	const stwuct macsec_secy *secy = ctx->secy;
	boow sci_pwesent = macsec_send_sci(secy);
	stwuct mwx5_sectag_headew sectag = {};
	const stwuct macsec_tx_sc *tx_sc;

	tx_sc = &secy->tx_sc;
	sectag.ethewtype = htons(ETH_P_MACSEC);

	if (sci_pwesent) {
		sectag.tci_an |= MACSEC_TCI_SC;
		memcpy(&sectag.sci, &secy->sci,
		       sizeof(sectag.sci));
	} ewse {
		if (tx_sc->end_station)
			sectag.tci_an |= MACSEC_TCI_ES;
		if (tx_sc->scb)
			sectag.tci_an |= MACSEC_TCI_SCB;
	}

	/* With GCM, C/E cweaw fow !encwypt, both set fow encwypt */
	if (tx_sc->encwypt)
		sectag.tci_an |= MACSEC_TCI_CONFID;
	ewse if (secy->icv_wen != MACSEC_DEFAUWT_ICV_WEN)
		sectag.tci_an |= MACSEC_TCI_C;

	sectag.tci_an |= tx_sc->encoding_sa;

	*wefowmat_size = MWX5_MACSEC_TAG_WEN + (sci_pwesent ? MACSEC_SCI_WEN : 0);

	memcpy(wefowmatbf, &sectag, *wefowmat_size);
}

static boow macsec_fs_is_macsec_device_empty(stwuct mwx5_macsec_device *macsec_device)
{
	if (xa_empty(&macsec_device->tx_id_xa) &&
	    xa_empty(&macsec_device->wx_id_xa))
		wetuwn twue;

	wetuwn fawse;
}

static void macsec_fs_id_dew(stwuct wist_head *macsec_devices_wist, u32 fs_id,
			     void *macdev, stwuct whashtabwe *hash_tabwe, boow is_tx)
{
	const stwuct whashtabwe_pawams *whash = (is_tx) ? &whash_sci : &whash_fs_id;
	stwuct mwx5_macsec_device *itew, *macsec_device = NUWW;
	stwuct mwx5_fs_id *fs_id_found;
	stwuct xawway *fs_id_xa;

	wist_fow_each_entwy(itew, macsec_devices_wist, macsec_devices_wist_entwy) {
		if (itew->macdev == macdev) {
			macsec_device = itew;
			bweak;
		}
	}
	WAWN_ON(!macsec_device);

	fs_id_xa = (is_tx) ? &macsec_device->tx_id_xa :
			     &macsec_device->wx_id_xa;
	xa_wock(fs_id_xa);
	fs_id_found = xa_woad(fs_id_xa, fs_id);
	WAWN_ON(!fs_id_found);

	if (!wefcount_dec_and_test(&fs_id_found->wefcnt)) {
		xa_unwock(fs_id_xa);
		wetuwn;
	}

	if (fs_id_found->id) {
		/* Make suwe ongoing datapath weadews sees a vawid SA */
		whashtabwe_wemove_fast(hash_tabwe, &fs_id_found->hash, *whash);
		fs_id_found->id = 0;
	}
	xa_unwock(fs_id_xa);

	xa_ewase(fs_id_xa, fs_id);

	kfwee(fs_id_found);

	if (macsec_fs_is_macsec_device_empty(macsec_device)) {
		wist_dew(&macsec_device->macsec_devices_wist_entwy);
		kfwee(macsec_device);
	}
}

static int macsec_fs_id_add(stwuct wist_head *macsec_devices_wist, u32 fs_id,
			    void *macdev, stwuct whashtabwe *hash_tabwe, sci_t sci,
			    boow is_tx)
{
	const stwuct whashtabwe_pawams *whash = (is_tx) ? &whash_sci : &whash_fs_id;
	stwuct mwx5_macsec_device *itew, *macsec_device = NUWW;
	stwuct mwx5_fs_id *fs_id_itew;
	stwuct xawway *fs_id_xa;
	int eww;

	if (!is_tx) {
		wcu_wead_wock();
		fs_id_itew = whashtabwe_wookup(hash_tabwe, &fs_id, whash_fs_id);
		if (fs_id_itew) {
			wefcount_inc(&fs_id_itew->wefcnt);
			wcu_wead_unwock();
			wetuwn 0;
		}
		wcu_wead_unwock();
	}

	fs_id_itew = kzawwoc(sizeof(*fs_id_itew), GFP_KEWNEW);
	if (!fs_id_itew)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(itew, macsec_devices_wist, macsec_devices_wist_entwy) {
		if (itew->macdev == macdev) {
			macsec_device = itew;
			bweak;
		}
	}

	if (!macsec_device) { /* fiwst time adding a SA to that device */
		macsec_device = kzawwoc(sizeof(*macsec_device), GFP_KEWNEW);
		if (!macsec_device) {
			eww = -ENOMEM;
			goto eww_awwoc_dev;
		}
		macsec_device->macdev = macdev;
		xa_init(&macsec_device->tx_id_xa);
		xa_init(&macsec_device->wx_id_xa);
		wist_add(&macsec_device->macsec_devices_wist_entwy, macsec_devices_wist);
	}

	fs_id_xa = (is_tx) ? &macsec_device->tx_id_xa :
			     &macsec_device->wx_id_xa;
	fs_id_itew->id = fs_id;
	wefcount_set(&fs_id_itew->wefcnt, 1);
	fs_id_itew->sci = sci;
	eww = xa_eww(xa_stowe(fs_id_xa, fs_id, fs_id_itew, GFP_KEWNEW));
	if (eww)
		goto eww_stowe_id;

	eww = whashtabwe_insewt_fast(hash_tabwe, &fs_id_itew->hash, *whash);
	if (eww)
		goto eww_hash_insewt;

	wetuwn 0;

eww_hash_insewt:
	xa_ewase(fs_id_xa, fs_id);
eww_stowe_id:
	if (macsec_fs_is_macsec_device_empty(macsec_device)) {
		wist_dew(&macsec_device->macsec_devices_wist_entwy);
		kfwee(macsec_device);
	}
eww_awwoc_dev:
	kfwee(fs_id_itew);
	wetuwn eww;
}

static void macsec_fs_tx_dew_wuwe(stwuct mwx5_macsec_fs *macsec_fs,
				  stwuct mwx5_macsec_tx_wuwe *tx_wuwe,
				  void *macdev)
{
	macsec_fs_id_dew(&macsec_fs->macsec_devices_wist, tx_wuwe->fs_id, macdev,
			 &macsec_fs->sci_hash, twue);

	if (tx_wuwe->wuwe) {
		mwx5_dew_fwow_wuwes(tx_wuwe->wuwe);
		tx_wuwe->wuwe = NUWW;
	}

	if (tx_wuwe->pkt_wefowmat) {
		mwx5_packet_wefowmat_deawwoc(macsec_fs->mdev, tx_wuwe->pkt_wefowmat);
		tx_wuwe->pkt_wefowmat = NUWW;
	}

	if (tx_wuwe->fs_id) {
		ida_fwee(&macsec_fs->tx_fs->tx_hawwoc, tx_wuwe->fs_id);
		tx_wuwe->fs_id = 0;
	}

	kfwee(tx_wuwe);

	macsec_fs_tx_ft_put(macsec_fs);
}

#define MWX5_WEFOWMAT_PAWAM_ADD_MACSEC_OFFSET_4_BYTES 1

static union mwx5_macsec_wuwe *
macsec_fs_tx_add_wuwe(stwuct mwx5_macsec_fs *macsec_fs,
		      const stwuct macsec_context *macsec_ctx,
		      stwuct mwx5_macsec_wuwe_attws *attws, u32 *fs_id)
{
	chaw wefowmatbf[MWX5_MACSEC_TAG_WEN + MACSEC_SCI_WEN];
	stwuct mwx5_pkt_wefowmat_pawams wefowmat_pawams = {};
	stwuct mwx5_macsec_tx *tx_fs = macsec_fs->tx_fs;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	union mwx5_macsec_wuwe *macsec_wuwe = NUWW;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_macsec_tabwes *tx_tabwes;
	stwuct mwx5_macsec_tx_wuwe *tx_wuwe;
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	size_t wefowmat_size;
	int eww = 0;

	tx_tabwes = &tx_fs->tabwes;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn NUWW;

	eww = macsec_fs_tx_ft_get(macsec_fs);
	if (eww)
		goto out_spec;

	macsec_wuwe = kzawwoc(sizeof(*macsec_wuwe), GFP_KEWNEW);
	if (!macsec_wuwe) {
		macsec_fs_tx_ft_put(macsec_fs);
		goto out_spec;
	}

	tx_wuwe = &macsec_wuwe->tx_wuwe;

	/* Tx cwypto tabwe cwypto wuwe */
	macsec_fs_tx_cweate_sectag_headew(macsec_ctx, wefowmatbf, &wefowmat_size);

	wefowmat_pawams.type = MWX5_WEFOWMAT_TYPE_ADD_MACSEC;
	wefowmat_pawams.size = wefowmat_size;
	wefowmat_pawams.data = wefowmatbf;

	if (is_vwan_dev(macsec_ctx->netdev))
		wefowmat_pawams.pawam_0 = MWX5_WEFOWMAT_PAWAM_ADD_MACSEC_OFFSET_4_BYTES;

	fwow_act.pkt_wefowmat = mwx5_packet_wefowmat_awwoc(mdev,
							   &wefowmat_pawams,
							   MWX5_FWOW_NAMESPACE_EGWESS_MACSEC);
	if (IS_EWW(fwow_act.pkt_wefowmat)) {
		eww = PTW_EWW(fwow_act.pkt_wefowmat);
		mwx5_cowe_eww(mdev, "Faiwed to awwocate MACsec Tx wefowmat context eww=%d\n",  eww);
		goto eww;
	}
	tx_wuwe->pkt_wefowmat = fwow_act.pkt_wefowmat;

	eww = macsec_fs_tx_setup_fte(macsec_fs, spec, &fwow_act, attws->macsec_obj_id, fs_id);
	if (eww) {
		mwx5_cowe_eww(mdev,
			      "Faiwed to add packet wefowmat fow MACsec TX cwypto wuwe, eww=%d\n",
			      eww);
		goto eww;
	}

	tx_wuwe->fs_id = *fs_id;

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST |
			  MWX5_FWOW_CONTEXT_ACTION_CWYPTO_ENCWYPT |
			  MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = tx_tabwes->ft_check;
	wuwe = mwx5_add_fwow_wuwes(tx_tabwes->ft_cwypto.t, spec, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "Faiwed to add MACsec TX cwypto wuwe, eww=%d\n", eww);
		goto eww;
	}
	tx_wuwe->wuwe = wuwe;

	eww = macsec_fs_id_add(&macsec_fs->macsec_devices_wist, *fs_id, macsec_ctx->secy->netdev,
			       &macsec_fs->sci_hash, attws->sci, twue);
	if (eww) {
		mwx5_cowe_eww(mdev, "Faiwed to save fs_id, eww=%d\n", eww);
		goto eww;
	}

	goto out_spec;

eww:
	macsec_fs_tx_dew_wuwe(macsec_fs, tx_wuwe, macsec_ctx->secy->netdev);
	macsec_wuwe = NUWW;
out_spec:
	kvfwee(spec);

	wetuwn macsec_wuwe;
}

static void macsec_fs_tx_cweanup(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_macsec_tx *tx_fs = macsec_fs->tx_fs;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_macsec_tabwes *tx_tabwes;

	if (!tx_fs)
		wetuwn;

	tx_tabwes = &tx_fs->tabwes;
	if (tx_tabwes->wefcnt) {
		mwx5_cowe_eww(mdev,
			      "Can't destwoy MACsec offwoad tx_fs, wefcnt(%u) isn't 0\n",
			      tx_tabwes->wefcnt);
		wetuwn;
	}

	ida_destwoy(&tx_fs->tx_hawwoc);

	if (tx_tabwes->check_miss_wuwe_countew) {
		mwx5_fc_destwoy(mdev, tx_tabwes->check_miss_wuwe_countew);
		tx_tabwes->check_miss_wuwe_countew = NUWW;
	}

	if (tx_tabwes->check_wuwe_countew) {
		mwx5_fc_destwoy(mdev, tx_tabwes->check_wuwe_countew);
		tx_tabwes->check_wuwe_countew = NUWW;
	}

	kfwee(tx_fs);
	macsec_fs->tx_fs = NUWW;
}

static int macsec_fs_tx_init(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_macsec_tabwes *tx_tabwes;
	stwuct mwx5_macsec_tx *tx_fs;
	stwuct mwx5_fc *fwow_countew;
	int eww;

	tx_fs = kzawwoc(sizeof(*tx_fs), GFP_KEWNEW);
	if (!tx_fs)
		wetuwn -ENOMEM;

	tx_tabwes = &tx_fs->tabwes;

	fwow_countew = mwx5_fc_cweate(mdev, fawse);
	if (IS_EWW(fwow_countew)) {
		eww = PTW_EWW(fwow_countew);
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate MACsec Tx encwypt fwow countew, eww(%d)\n",
			      eww);
		goto eww_encwypt_countew;
	}
	tx_tabwes->check_wuwe_countew = fwow_countew;

	fwow_countew = mwx5_fc_cweate(mdev, fawse);
	if (IS_EWW(fwow_countew)) {
		eww = PTW_EWW(fwow_countew);
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate MACsec Tx dwop fwow countew, eww(%d)\n",
			      eww);
		goto eww_dwop_countew;
	}
	tx_tabwes->check_miss_wuwe_countew = fwow_countew;

	ida_init(&tx_fs->tx_hawwoc);
	INIT_WIST_HEAD(&macsec_fs->macsec_devices_wist);

	macsec_fs->tx_fs = tx_fs;

	wetuwn 0;

eww_dwop_countew:
	mwx5_fc_destwoy(mdev, tx_tabwes->check_wuwe_countew);
	tx_tabwes->check_wuwe_countew = NUWW;

eww_encwypt_countew:
	kfwee(tx_fs);
	macsec_fs->tx_fs = NUWW;

	wetuwn eww;
}

static void macsec_fs_wx_woce_miss_destwoy(stwuct mwx5_macsec_miss *miss)
{
	mwx5_dew_fwow_wuwes(miss->wuwe);
	mwx5_destwoy_fwow_gwoup(miss->g);
}

static void macsec_fs_wdma_wx_destwoy(stwuct mwx5_macsec_wx_woce *woce, stwuct mwx5_cowe_dev *mdev)
{
	if (!mwx5_is_macsec_woce_suppowted(mdev))
		wetuwn;

	mwx5_dew_fwow_wuwes(woce->nic_miss.wuwe);
	mwx5_dew_fwow_wuwes(woce->wuwe);
	mwx5_modify_headew_deawwoc(mdev, woce->copy_modify_hdw);
	mwx5_destwoy_fwow_gwoup(woce->nic_miss.g);
	mwx5_destwoy_fwow_gwoup(woce->g);
	mwx5_destwoy_fwow_tabwe(woce->ft);

	macsec_fs_wx_woce_miss_destwoy(&woce->miss);
	mwx5_destwoy_fwow_tabwe(woce->ft_macsec_op_check);
	mwx5_destwoy_fwow_tabwe(woce->ft_ip_check);
}

static void macsec_fs_wx_destwoy(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_macsec_wx *wx_fs = macsec_fs->wx_fs;
	stwuct mwx5_macsec_tabwes *wx_tabwes;
	int i;

	/* Wx check tabwe */
	fow (i = 1; i >= 0; --i) {
		if (wx_fs->check_wuwe[i]) {
			mwx5_dew_fwow_wuwes(wx_fs->check_wuwe[i]);
			wx_fs->check_wuwe[i] = NUWW;
		}

		if (wx_fs->check_wuwe_pkt_wefowmat[i]) {
			mwx5_packet_wefowmat_deawwoc(macsec_fs->mdev,
						     wx_fs->check_wuwe_pkt_wefowmat[i]);
			wx_fs->check_wuwe_pkt_wefowmat[i] = NUWW;
		}
	}

	wx_tabwes = &wx_fs->tabwes;

	if (wx_tabwes->check_miss_wuwe) {
		mwx5_dew_fwow_wuwes(wx_tabwes->check_miss_wuwe);
		wx_tabwes->check_miss_wuwe = NUWW;
	}

	if (wx_tabwes->ft_check_gwoup) {
		mwx5_destwoy_fwow_gwoup(wx_tabwes->ft_check_gwoup);
		wx_tabwes->ft_check_gwoup = NUWW;
	}

	if (wx_tabwes->ft_check) {
		mwx5_destwoy_fwow_tabwe(wx_tabwes->ft_check);
		wx_tabwes->ft_check = NUWW;
	}

	/* Wx cwypto tabwe */
	if (wx_tabwes->cwypto_miss_wuwe) {
		mwx5_dew_fwow_wuwes(wx_tabwes->cwypto_miss_wuwe);
		wx_tabwes->cwypto_miss_wuwe = NUWW;
	}

	macsec_fs_destwoy_fwow_tabwe(&wx_tabwes->ft_cwypto);

	macsec_fs_wdma_wx_destwoy(&macsec_fs->wx_fs->woce, macsec_fs->mdev);
}

static int macsec_fs_wx_cweate_cwypto_tabwe_gwoups(stwuct mwx5_macsec_fwow_tabwe *ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	int mcwen = MWX5_ST_SZ_BYTES(fte_match_pawam);
	int ix = 0;
	u32 *in;
	int eww;
	u8 *mc;

	ft->g = kcawwoc(WX_CWYPTO_TABWE_NUM_GWOUPS, sizeof(*ft->g), GFP_KEWNEW);
	if (!ft->g)
		wetuwn -ENOMEM;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		kfwee(ft->g);
		wetuwn -ENOMEM;
	}

	mc = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	/* Fwow gwoup fow SA wuwe with SCI */
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS |
						MWX5_MATCH_MISC_PAWAMETEWS_5);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.ethewtype);

	MWX5_SET(fte_match_pawam, mc, misc_pawametews_5.macsec_tag_0,
		 MWX5_MACSEC_SECTAG_TCI_AN_FIEWD_BITMASK <<
		 MWX5_MACSEC_SECTAG_TCI_AN_FIEWD_OFFSET);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, misc_pawametews_5.macsec_tag_2);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, misc_pawametews_5.macsec_tag_3);

	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += WX_CWYPTO_TABWE_SA_WUWE_WITH_SCI_GWOUP_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww;
	ft->num_gwoups++;

	/* Fwow gwoup fow SA wuwe without SCI */
	memset(in, 0, inwen);
	memset(mc, 0, mcwen);
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS |
						MWX5_MATCH_MISC_PAWAMETEWS_5);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.smac_47_16);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.smac_15_0);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.ethewtype);

	MWX5_SET(fte_match_pawam, mc, misc_pawametews_5.macsec_tag_0,
		 MWX5_MACSEC_SECTAG_TCI_AN_FIEWD_BITMASK << MWX5_MACSEC_SECTAG_TCI_AN_FIEWD_OFFSET);

	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += WX_CWYPTO_TABWE_SA_WUWE_WITHOUT_SCI_GWOUP_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww;
	ft->num_gwoups++;

	/* Fwow Gwoup fow w2 twaps */
	memset(in, 0, inwen);
	memset(mc, 0, mcwen);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += CWYPTO_TABWE_DEFAUWT_WUWE_GWOUP_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww;
	ft->num_gwoups++;

	kvfwee(in);
	wetuwn 0;

eww:
	eww = PTW_EWW(ft->g[ft->num_gwoups]);
	ft->g[ft->num_gwoups] = NUWW;
	kvfwee(in);

	wetuwn eww;
}

static int macsec_fs_wx_cweate_check_decap_wuwe(stwuct mwx5_macsec_fs *macsec_fs,
						stwuct mwx5_fwow_destination *dest,
						stwuct mwx5_fwow_act *fwow_act,
						stwuct mwx5_fwow_spec *spec,
						int wefowmat_pawam_size)
{
	int wuwe_index = (wefowmat_pawam_size == MWX5_SECTAG_HEADEW_SIZE_WITH_SCI) ? 0 : 1;
	u8 mwx5_wefowmat_buf[MWX5_SECTAG_HEADEW_SIZE_WITH_SCI];
	stwuct mwx5_pkt_wefowmat_pawams wefowmat_pawams = {};
	stwuct mwx5_macsec_wx *wx_fs = macsec_fs->wx_fs;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_fwow_destination woce_dest[2];
	stwuct mwx5_macsec_tabwes *wx_tabwes;
	stwuct mwx5_fwow_handwe *wuwe;
	int eww = 0, dstn = 0;

	wx_tabwes = &wx_fs->tabwes;

	/* Wx check tabwe decap 16B wuwe */
	memset(dest, 0, sizeof(*dest));
	memset(fwow_act, 0, sizeof(*fwow_act));
	memset(spec, 0, sizeof(*spec));

	wefowmat_pawams.type = MWX5_WEFOWMAT_TYPE_DEW_MACSEC;
	wefowmat_pawams.size = wefowmat_pawam_size;
	wefowmat_pawams.data = mwx5_wefowmat_buf;
	fwow_act->pkt_wefowmat = mwx5_packet_wefowmat_awwoc(mdev,
							    &wefowmat_pawams,
							    MWX5_FWOW_NAMESPACE_KEWNEW_WX_MACSEC);
	if (IS_EWW(fwow_act->pkt_wefowmat)) {
		eww = PTW_EWW(fwow_act->pkt_wefowmat);
		mwx5_cowe_eww(mdev, "Faiwed to awwocate MACsec Wx wefowmat context eww=%d\n", eww);
		wetuwn eww;
	}
	wx_fs->check_wuwe_pkt_wefowmat[wuwe_index] = fwow_act->pkt_wefowmat;

	spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2;
	/* MACsec syndwome match */
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2.macsec_syndwome);
	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_2.macsec_syndwome, 0);
	/* ASO wetuwn weg syndwome match */
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2.metadata_weg_c_4);
	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_2.metadata_weg_c_4, 0);

	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_5;
	/* Sectag TCI SC pwesent bit*/
	MWX5_SET(fte_match_pawam, spec->match_cwitewia, misc_pawametews_5.macsec_tag_0,
		 MWX5_MACSEC_SECTAG_TCI_SC_FIEWD_BIT << MWX5_MACSEC_SECTAG_TCI_AN_FIEWD_OFFSET);

	if (wefowmat_pawam_size == MWX5_SECTAG_HEADEW_SIZE_WITH_SCI)
		MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_5.macsec_tag_0,
			 MWX5_MACSEC_SECTAG_TCI_SC_FIEWD_BIT <<
			 MWX5_MACSEC_SECTAG_TCI_AN_FIEWD_OFFSET);

	fwow_act->fwags = FWOW_ACT_NO_APPEND;

	if (wx_fs->woce.ft) {
		fwow_act->action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
		woce_dest[dstn].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		woce_dest[dstn].ft = wx_fs->woce.ft;
		dstn++;
	} ewse {
		fwow_act->action = MWX5_FWOW_CONTEXT_ACTION_FWD_NEXT_PWIO;
	}

	fwow_act->action |= MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT |
			    MWX5_FWOW_CONTEXT_ACTION_COUNT;
	woce_dest[dstn].type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	woce_dest[dstn].countew_id = mwx5_fc_id(wx_tabwes->check_wuwe_countew);
	wuwe = mwx5_add_fwow_wuwes(wx_tabwes->ft_check, spec, fwow_act, woce_dest, dstn + 1);

	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "Faiwed to add MACsec Wx check wuwe, eww=%d\n", eww);
		wetuwn eww;
	}

	wx_fs->check_wuwe[wuwe_index] = wuwe;

	wetuwn 0;
}

static int macsec_fs_wx_woce_miss_cweate(stwuct mwx5_cowe_dev *mdev,
					 stwuct mwx5_macsec_wx_woce *woce)
{
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_gwoup *fwow_gwoup;
	stwuct mwx5_fwow_handwe *wuwe;
	u32 *fwow_gwoup_in;
	int eww;

	fwow_gwoup_in = kvzawwoc(MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in), GFP_KEWNEW);
	if (!fwow_gwoup_in)
		wetuwn -ENOMEM;

	/* IP check ft has no miss wuwe since we use defauwt miss action which is go to next PWIO */
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index,
		 woce->ft_macsec_op_check->max_fte - 1);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index,
		 woce->ft_macsec_op_check->max_fte - 1);
	fwow_gwoup = mwx5_cweate_fwow_gwoup(woce->ft_macsec_op_check, fwow_gwoup_in);
	if (IS_EWW(fwow_gwoup)) {
		eww = PTW_EWW(fwow_gwoup);
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate miss fwow gwoup fow MACsec WoCE opewation check tabwe eww(%d)\n",
			      eww);
		goto eww_macsec_op_miss_gwoup;
	}
	woce->miss.g = fwow_gwoup;

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP;
	wuwe = mwx5_add_fwow_wuwes(woce->ft_macsec_op_check,  NUWW, &fwow_act, NUWW, 0);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "Faiwed to add miss wuwe to MACsec WoCE opewation check tabwe eww(%d)\n",
			      eww);
		goto eww_macsec_op_wuwe;
	}
	woce->miss.wuwe = wuwe;

	kvfwee(fwow_gwoup_in);
	wetuwn 0;

eww_macsec_op_wuwe:
	mwx5_destwoy_fwow_gwoup(woce->miss.g);
eww_macsec_op_miss_gwoup:
	kvfwee(fwow_gwoup_in);
	wetuwn eww;
}

#define MWX5_WX_WOCE_GWOUP_SIZE BIT(0)

static int macsec_fs_wx_woce_jump_to_wdma_gwoups_cweate(stwuct mwx5_cowe_dev *mdev,
							stwuct mwx5_macsec_wx_woce *woce)
{
	stwuct mwx5_fwow_gwoup *g;
	void *outew_headews_c;
	int ix = 0;
	u32 *in;
	int eww;
	u8 *mc;

	in = kvzawwoc(MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in), GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	mc = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);
	outew_headews_c = MWX5_ADDW_OF(fte_match_pawam, mc, outew_headews);
	MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c, ip_pwotocow);
	MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c, udp_dpowt);

	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5_WX_WOCE_GWOUP_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	g = mwx5_cweate_fwow_gwoup(woce->ft, in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		mwx5_cowe_eww(mdev, "Faiwed to cweate main fwow gwoup fow MACsec WoCE NIC UDP tabwe eww(%d)\n",
			      eww);
		goto eww_udp_gwoup;
	}
	woce->g = g;

	memset(in, 0, MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in));
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5_WX_WOCE_GWOUP_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	g = mwx5_cweate_fwow_gwoup(woce->ft, in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		mwx5_cowe_eww(mdev, "Faiwed to cweate miss fwow gwoup fow MACsec WoCE NIC UDP tabwe eww(%d)\n",
			      eww);
		goto eww_udp_miss_gwoup;
	}
	woce->nic_miss.g = g;

	kvfwee(in);
	wetuwn 0;

eww_udp_miss_gwoup:
	mwx5_destwoy_fwow_gwoup(woce->g);
eww_udp_gwoup:
	kvfwee(in);
	wetuwn eww;
}

static int macsec_fs_wx_woce_jump_to_wdma_wuwes_cweate(stwuct mwx5_macsec_fs *macsec_fs,
						       stwuct mwx5_macsec_wx_woce *woce)
{
	u8 action[MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto)] = {};
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_fwow_destination dst = {};
	stwuct mwx5_modify_hdw *modify_hdw;
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	int eww;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ip_pwotocow);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ip_pwotocow, IPPWOTO_UDP);
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.udp_dpowt);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.udp_dpowt, WOCE_V2_UDP_DPOWT);

	MWX5_SET(copy_action_in, action, action_type, MWX5_ACTION_TYPE_COPY);
	MWX5_SET(copy_action_in, action, swc_fiewd, MWX5_ACTION_IN_FIEWD_METADATA_WEG_B);
	MWX5_SET(copy_action_in, action, swc_offset, 0);
	MWX5_SET(copy_action_in, action, wength, 32);
	MWX5_SET(copy_action_in, action, dst_fiewd, MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_5);
	MWX5_SET(copy_action_in, action, dst_offset, 0);

	modify_hdw = mwx5_modify_headew_awwoc(macsec_fs->mdev, MWX5_FWOW_NAMESPACE_KEWNEW_WX_MACSEC,
					      1, action);

	if (IS_EWW(modify_hdw)) {
		eww = PTW_EWW(modify_hdw);
		mwx5_cowe_eww(mdev,
			      "Faiwed to awwoc macsec copy modify_headew_id eww(%d)\n", eww);
		goto eww_awwoc_hdw;
	}

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_MOD_HDW | MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	fwow_act.modify_hdw = modify_hdw;
	dst.type = MWX5_FWOW_DESTINATION_TYPE_TABWE_TYPE;
	dst.ft = woce->ft_ip_check;
	wuwe = mwx5_add_fwow_wuwes(woce->ft, spec, &fwow_act, &dst, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "Faiwed to add wuwe to MACsec WoCE NIC UDP tabwe eww(%d)\n",
			      eww);
		goto eww_add_wuwe;
	}
	woce->wuwe = wuwe;
	woce->copy_modify_hdw = modify_hdw;

	memset(&fwow_act, 0, sizeof(fwow_act));
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_NEXT_PWIO;
	wuwe = mwx5_add_fwow_wuwes(woce->ft, NUWW, &fwow_act, NUWW, 0);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "Faiwed to add miss wuwe to MACsec WoCE NIC UDP tabwe eww(%d)\n",
			      eww);
		goto eww_add_wuwe2;
	}
	woce->nic_miss.wuwe = wuwe;

	kvfwee(spec);
	wetuwn 0;

eww_add_wuwe2:
	mwx5_dew_fwow_wuwes(woce->wuwe);
eww_add_wuwe:
	mwx5_modify_headew_deawwoc(macsec_fs->mdev, modify_hdw);
eww_awwoc_hdw:
	kvfwee(spec);
	wetuwn eww;
}

static int macsec_fs_wx_woce_jump_to_wdma_cweate(stwuct mwx5_macsec_fs *macsec_fs,
						 stwuct mwx5_macsec_wx_woce *woce)
{
	int eww;

	eww = macsec_fs_wx_woce_jump_to_wdma_gwoups_cweate(macsec_fs->mdev, woce);
	if (eww)
		wetuwn eww;

	eww = macsec_fs_wx_woce_jump_to_wdma_wuwes_cweate(macsec_fs, woce);
	if (eww)
		goto eww;

	wetuwn 0;
eww:
	mwx5_destwoy_fwow_gwoup(woce->nic_miss.g);
	mwx5_destwoy_fwow_gwoup(woce->g);
	wetuwn eww;
}

static int macsec_fs_wx_woce_cweate(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_macsec_wx *wx_fs = macsec_fs->wx_fs;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5_fwow_tabwe *ft;
	int eww = 0;

	if (!mwx5_is_macsec_woce_suppowted(macsec_fs->mdev)) {
		mwx5_cowe_dbg(mdev, "Faiwed to init WoCE MACsec, capabiwities not suppowted\n");
		wetuwn 0;
	}

	ns = mwx5_get_fwow_namespace(macsec_fs->mdev, MWX5_FWOW_NAMESPACE_WDMA_WX_MACSEC);
	if (!ns)
		wetuwn -ENOMEM;

	ft = macsec_fs_auto_gwoup_tabwe_cweate(ns, 0, WDMA_WX_WOCE_IP_TABWE_WEVEW,
					       CWYPTO_NUM_MAXSEC_FTE);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate MACsec IP check WoCE tabwe eww(%d)\n", eww);
		wetuwn eww;
	}
	wx_fs->woce.ft_ip_check = ft;

	ft = macsec_fs_auto_gwoup_tabwe_cweate(ns, 0, WDMA_WX_WOCE_MACSEC_OP_TABWE_WEVEW,
					       CWYPTO_NUM_MAXSEC_FTE);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate MACsec opewation check WoCE tabwe eww(%d)\n",
			      eww);
		goto eww_macsec_op;
	}
	wx_fs->woce.ft_macsec_op_check = ft;

	eww = macsec_fs_wx_woce_miss_cweate(mdev, &wx_fs->woce);
	if (eww)
		goto eww_miss_cweate;

	ns = mwx5_get_fwow_namespace(macsec_fs->mdev, MWX5_FWOW_NAMESPACE_KEWNEW_WX_MACSEC);
	if (!ns) {
		eww = -EOPNOTSUPP;
		goto eww_ns;
	}

	ft_attw.wevew = WX_WOCE_TABWE_WEVEW;
	ft_attw.max_fte = WX_WOCE_TABWE_NUM_FTE;
	ft = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate MACsec jump to WX WoCE, NIC tabwe eww(%d)\n", eww);
		goto eww_ns;
	}
	wx_fs->woce.ft = ft;

	eww = macsec_fs_wx_woce_jump_to_wdma_cweate(macsec_fs, &wx_fs->woce);
	if (eww)
		goto eww_udp_ft;

	wetuwn 0;

eww_udp_ft:
	mwx5_destwoy_fwow_tabwe(wx_fs->woce.ft);
eww_ns:
	macsec_fs_wx_woce_miss_destwoy(&wx_fs->woce.miss);
eww_miss_cweate:
	mwx5_destwoy_fwow_tabwe(wx_fs->woce.ft_macsec_op_check);
eww_macsec_op:
	mwx5_destwoy_fwow_tabwe(wx_fs->woce.ft_ip_check);
	wetuwn eww;
}

static int macsec_fs_wx_cweate(stwuct mwx5_macsec_fs *macsec_fs)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_macsec_wx *wx_fs = macsec_fs->wx_fs;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_macsec_fwow_tabwe *ft_cwypto;
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_macsec_tabwes *wx_tabwes;
	stwuct mwx5_fwow_tabwe *fwow_tabwe;
	stwuct mwx5_fwow_gwoup *fwow_gwoup;
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	u32 *fwow_gwoup_in;
	int eww;

	ns = mwx5_get_fwow_namespace(mdev, MWX5_FWOW_NAMESPACE_KEWNEW_WX_MACSEC);
	if (!ns)
		wetuwn -ENOMEM;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in) {
		eww = -ENOMEM;
		goto fwee_spec;
	}

	wx_tabwes = &wx_fs->tabwes;
	ft_cwypto = &wx_tabwes->ft_cwypto;

	eww = macsec_fs_wx_woce_cweate(macsec_fs);
	if (eww)
		goto out_fwow_gwoup;

	/* Wx cwypto tabwe */
	ft_attw.wevew = WX_CWYPTO_TABWE_WEVEW;
	ft_attw.max_fte = CWYPTO_NUM_MAXSEC_FTE;

	fwow_tabwe = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(fwow_tabwe)) {
		eww = PTW_EWW(fwow_tabwe);
		mwx5_cowe_eww(mdev, "Faiwed to cweate MACsec Wx cwypto tabwe eww(%d)\n", eww);
		goto eww;
	}
	ft_cwypto->t = fwow_tabwe;

	/* Wx cwypto tabwe gwoups */
	eww = macsec_fs_wx_cweate_cwypto_tabwe_gwoups(ft_cwypto);
	if (eww) {
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate defauwt fwow gwoup fow MACsec Tx cwypto tabwe eww(%d)\n",
			      eww);
		goto eww;
	}

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_NEXT_PWIO;
	wuwe = mwx5_add_fwow_wuwes(ft_cwypto->t, NUWW, &fwow_act, NUWW, 0);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev,
			      "Faiwed to add MACsec Wx cwypto tabwe defauwt miss wuwe %d\n",
			      eww);
		goto eww;
	}
	wx_tabwes->cwypto_miss_wuwe = wuwe;

	/* Wx check tabwe */
	fwow_tabwe = macsec_fs_auto_gwoup_tabwe_cweate(ns,
						       MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT,
						       WX_CHECK_TABWE_WEVEW,
						       WX_CHECK_TABWE_NUM_FTE);
	if (IS_EWW(fwow_tabwe)) {
		eww = PTW_EWW(fwow_tabwe);
		mwx5_cowe_eww(mdev, "Faiw to cweate MACsec WX check tabwe, eww(%d)\n", eww);
		goto eww;
	}
	wx_tabwes->ft_check = fwow_tabwe;

	/* Wx check tabwe Defauwt miss gwoup/wuwe */
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, fwow_tabwe->max_fte - 1);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, fwow_tabwe->max_fte - 1);
	fwow_gwoup = mwx5_cweate_fwow_gwoup(wx_tabwes->ft_check, fwow_gwoup_in);
	if (IS_EWW(fwow_gwoup)) {
		eww = PTW_EWW(fwow_gwoup);
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate defauwt fwow gwoup fow MACsec Wx check tabwe eww(%d)\n",
			      eww);
		goto eww;
	}
	wx_tabwes->ft_check_gwoup = fwow_gwoup;

	/* Wx check tabwe defauwt dwop wuwe */
	memset(&fwow_act, 0, sizeof(fwow_act));

	dest.type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dest.countew_id = mwx5_fc_id(wx_tabwes->check_miss_wuwe_countew);
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP | MWX5_FWOW_CONTEXT_ACTION_COUNT;
	wuwe = mwx5_add_fwow_wuwes(wx_tabwes->ft_check,  NUWW, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev, "Faiwed to added MACsec Wx check dwop wuwe, eww(%d)\n", eww);
		goto eww;
	}
	wx_tabwes->check_miss_wuwe = wuwe;

	/* Wx check tabwe decap wuwes */
	eww = macsec_fs_wx_cweate_check_decap_wuwe(macsec_fs, &dest, &fwow_act, spec,
						   MWX5_SECTAG_HEADEW_SIZE_WITH_SCI);
	if (eww)
		goto eww;

	eww = macsec_fs_wx_cweate_check_decap_wuwe(macsec_fs, &dest, &fwow_act, spec,
						   MWX5_SECTAG_HEADEW_SIZE_WITHOUT_SCI);
	if (eww)
		goto eww;

	goto out_fwow_gwoup;

eww:
	macsec_fs_wx_destwoy(macsec_fs);
out_fwow_gwoup:
	kvfwee(fwow_gwoup_in);
fwee_spec:
	kvfwee(spec);
	wetuwn eww;
}

static int macsec_fs_wx_ft_get(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_macsec_tabwes *wx_tabwes = &macsec_fs->wx_fs->tabwes;
	int eww = 0;

	if (wx_tabwes->wefcnt)
		goto out;

	eww = macsec_fs_wx_cweate(macsec_fs);
	if (eww)
		wetuwn eww;

out:
	wx_tabwes->wefcnt++;
	wetuwn eww;
}

static void macsec_fs_wx_ft_put(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_macsec_tabwes *wx_tabwes = &macsec_fs->wx_fs->tabwes;

	if (--wx_tabwes->wefcnt)
		wetuwn;

	macsec_fs_wx_destwoy(macsec_fs);
}

static void macsec_fs_wx_dew_wuwe(stwuct mwx5_macsec_fs *macsec_fs,
				  stwuct mwx5_macsec_wx_wuwe *wx_wuwe,
				  void *macdev, u32 fs_id)
{
	int i;

	macsec_fs_id_dew(&macsec_fs->macsec_devices_wist, fs_id, macdev,
			 &macsec_fs->fs_id_hash, fawse);

	fow (i = 0; i < WX_NUM_OF_WUWES_PEW_SA; ++i) {
		if (wx_wuwe->wuwe[i]) {
			mwx5_dew_fwow_wuwes(wx_wuwe->wuwe[i]);
			wx_wuwe->wuwe[i] = NUWW;
		}
	}

	if (wx_wuwe->meta_modhdw) {
		mwx5_modify_headew_deawwoc(macsec_fs->mdev, wx_wuwe->meta_modhdw);
		wx_wuwe->meta_modhdw = NUWW;
	}

	kfwee(wx_wuwe);

	macsec_fs_wx_ft_put(macsec_fs);
}

static void macsec_fs_wx_setup_fte(stwuct mwx5_fwow_spec *spec,
				   stwuct mwx5_fwow_act *fwow_act,
				   stwuct mwx5_macsec_wuwe_attws *attws,
				   boow sci_pwesent)
{
	u8 tci_an = (sci_pwesent << MWX5_MACSEC_SECTAG_TCI_SC_FIEWD_OFFSET) | attws->assoc_num;
	stwuct mwx5_fwow_act_cwypto_pawams *cwypto_pawams = &fwow_act->cwypto;
	__be32 *sci_p = (__be32 *)(&attws->sci);

	spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;

	/* MACsec ethewtype */
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ethewtype);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ethewtype, ETH_P_MACSEC);

	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_5;

	/* Sectag AN + TCI SC pwesent bit*/
	MWX5_SET(fte_match_pawam, spec->match_cwitewia, misc_pawametews_5.macsec_tag_0,
		 MWX5_MACSEC_SECTAG_TCI_AN_FIEWD_BITMASK << MWX5_MACSEC_SECTAG_TCI_AN_FIEWD_OFFSET);
	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_5.macsec_tag_0,
		 tci_an << MWX5_MACSEC_SECTAG_TCI_AN_FIEWD_OFFSET);

	if (sci_pwesent) {
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 misc_pawametews_5.macsec_tag_2);
		MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_5.macsec_tag_2,
			 be32_to_cpu(sci_p[0]));

		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 misc_pawametews_5.macsec_tag_3);
		MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_5.macsec_tag_3,
			 be32_to_cpu(sci_p[1]));
	} ewse {
		/* When SCI isn't pwesent in the Sectag, need to match the souwce */
		/* MAC addwess onwy if the SCI contains the defauwt MACsec POWT	  */
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.smac_47_16);
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.smac_15_0);
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, outew_headews.smac_47_16),
		       sci_p, ETH_AWEN);
	}

	cwypto_pawams->type = MWX5_FWOW_CONTEXT_ENCWYPT_DECWYPT_TYPE_MACSEC;
	cwypto_pawams->obj_id = attws->macsec_obj_id;
}

static union mwx5_macsec_wuwe *
macsec_fs_wx_add_wuwe(stwuct mwx5_macsec_fs *macsec_fs,
		      const stwuct macsec_context *macsec_ctx,
		      stwuct mwx5_macsec_wuwe_attws *attws,
		      u32 fs_id)
{
	u8 action[MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto)] = {};
	stwuct mwx5_macsec_wx *wx_fs = macsec_fs->wx_fs;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	union mwx5_macsec_wuwe *macsec_wuwe = NUWW;
	stwuct mwx5_modify_hdw *modify_hdw = NUWW;
	stwuct mwx5_macsec_fwow_tabwe *ft_cwypto;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_macsec_tabwes *wx_tabwes;
	stwuct mwx5_macsec_wx_wuwe *wx_wuwe;
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn NUWW;

	eww = macsec_fs_wx_ft_get(macsec_fs);
	if (eww)
		goto out_spec;

	macsec_wuwe = kzawwoc(sizeof(*macsec_wuwe), GFP_KEWNEW);
	if (!macsec_wuwe) {
		macsec_fs_wx_ft_put(macsec_fs);
		goto out_spec;
	}

	wx_wuwe = &macsec_wuwe->wx_wuwe;
	wx_tabwes = &wx_fs->tabwes;
	ft_cwypto = &wx_tabwes->ft_cwypto;

	/* Set bit[31 - 30] macsec mawkew - 0x01 */
	/* Set bit[15-0] fs id */
	MWX5_SET(set_action_in, action, action_type, MWX5_ACTION_TYPE_SET);
	MWX5_SET(set_action_in, action, fiewd, MWX5_ACTION_IN_FIEWD_METADATA_WEG_B);
	MWX5_SET(set_action_in, action, data, macsec_fs_set_wx_fs_id(fs_id));
	MWX5_SET(set_action_in, action, offset, 0);
	MWX5_SET(set_action_in, action, wength, 32);

	modify_hdw = mwx5_modify_headew_awwoc(mdev, MWX5_FWOW_NAMESPACE_KEWNEW_WX_MACSEC,
					      1, action);
	if (IS_EWW(modify_hdw)) {
		eww = PTW_EWW(modify_hdw);
		mwx5_cowe_eww(mdev, "Faiw to awwoc MACsec set modify_headew_id eww=%d\n", eww);
		modify_hdw = NUWW;
		goto eww;
	}
	wx_wuwe->meta_modhdw = modify_hdw;

	/* Wx cwypto tabwe with SCI wuwe */
	macsec_fs_wx_setup_fte(spec, &fwow_act, attws, twue);

	fwow_act.modify_hdw = modify_hdw;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST |
			  MWX5_FWOW_CONTEXT_ACTION_CWYPTO_DECWYPT |
			  MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;

	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = wx_tabwes->ft_check;
	wuwe = mwx5_add_fwow_wuwes(ft_cwypto->t, spec, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(mdev,
			      "Faiwed to add SA with SCI wuwe to Wx cwypto wuwe, eww=%d\n",
			      eww);
		goto eww;
	}
	wx_wuwe->wuwe[0] = wuwe;

	/* Wx cwypto tabwe without SCI wuwe */
	if ((cpu_to_be64((__fowce u64)attws->sci) & 0xFFFF) == ntohs(MACSEC_POWT_ES)) {
		memset(spec, 0, sizeof(stwuct mwx5_fwow_spec));
		memset(&dest, 0, sizeof(stwuct mwx5_fwow_destination));
		memset(&fwow_act, 0, sizeof(fwow_act));

		macsec_fs_wx_setup_fte(spec, &fwow_act, attws, fawse);

		fwow_act.modify_hdw = modify_hdw;
		fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST |
				  MWX5_FWOW_CONTEXT_ACTION_CWYPTO_DECWYPT |
				  MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;

		dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		dest.ft = wx_tabwes->ft_check;
		wuwe = mwx5_add_fwow_wuwes(ft_cwypto->t, spec, &fwow_act, &dest, 1);
		if (IS_EWW(wuwe)) {
			eww = PTW_EWW(wuwe);
			mwx5_cowe_eww(mdev,
				      "Faiwed to add SA without SCI wuwe to Wx cwypto wuwe, eww=%d\n",
				      eww);
			goto eww;
		}
		wx_wuwe->wuwe[1] = wuwe;
	}

	eww = macsec_fs_id_add(&macsec_fs->macsec_devices_wist, fs_id, macsec_ctx->secy->netdev,
			       &macsec_fs->fs_id_hash, attws->sci, fawse);
	if (eww) {
		mwx5_cowe_eww(mdev, "Faiwed to save fs_id, eww=%d\n", eww);
		goto eww;
	}

	kvfwee(spec);
	wetuwn macsec_wuwe;

eww:
	macsec_fs_wx_dew_wuwe(macsec_fs, wx_wuwe, macsec_ctx->secy->netdev, fs_id);
	macsec_wuwe = NUWW;
out_spec:
	kvfwee(spec);
	wetuwn macsec_wuwe;
}

static int macsec_fs_wx_init(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_macsec_tabwes *wx_tabwes;
	stwuct mwx5_macsec_wx *wx_fs;
	stwuct mwx5_fc *fwow_countew;
	int eww;

	wx_fs =	kzawwoc(sizeof(*wx_fs), GFP_KEWNEW);
	if (!wx_fs)
		wetuwn -ENOMEM;

	fwow_countew = mwx5_fc_cweate(mdev, fawse);
	if (IS_EWW(fwow_countew)) {
		eww = PTW_EWW(fwow_countew);
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate MACsec Wx encwypt fwow countew, eww(%d)\n",
			      eww);
		goto eww_encwypt_countew;
	}

	wx_tabwes = &wx_fs->tabwes;
	wx_tabwes->check_wuwe_countew = fwow_countew;

	fwow_countew = mwx5_fc_cweate(mdev, fawse);
	if (IS_EWW(fwow_countew)) {
		eww = PTW_EWW(fwow_countew);
		mwx5_cowe_eww(mdev,
			      "Faiwed to cweate MACsec Wx dwop fwow countew, eww(%d)\n",
			      eww);
		goto eww_dwop_countew;
	}
	wx_tabwes->check_miss_wuwe_countew = fwow_countew;

	macsec_fs->wx_fs = wx_fs;

	wetuwn 0;

eww_dwop_countew:
	mwx5_fc_destwoy(mdev, wx_tabwes->check_wuwe_countew);
	wx_tabwes->check_wuwe_countew = NUWW;

eww_encwypt_countew:
	kfwee(wx_fs);
	macsec_fs->wx_fs = NUWW;

	wetuwn eww;
}

static void macsec_fs_wx_cweanup(stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_macsec_wx *wx_fs = macsec_fs->wx_fs;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_macsec_tabwes *wx_tabwes;

	if (!wx_fs)
		wetuwn;

	wx_tabwes = &wx_fs->tabwes;

	if (wx_tabwes->wefcnt) {
		mwx5_cowe_eww(mdev,
			      "Can't destwoy MACsec offwoad wx_fs, wefcnt(%u) isn't 0\n",
			      wx_tabwes->wefcnt);
		wetuwn;
	}

	if (wx_tabwes->check_miss_wuwe_countew) {
		mwx5_fc_destwoy(mdev, wx_tabwes->check_miss_wuwe_countew);
		wx_tabwes->check_miss_wuwe_countew = NUWW;
	}

	if (wx_tabwes->check_wuwe_countew) {
		mwx5_fc_destwoy(mdev, wx_tabwes->check_wuwe_countew);
		wx_tabwes->check_wuwe_countew = NUWW;
	}

	kfwee(wx_fs);
	macsec_fs->wx_fs = NUWW;
}

static void set_ipaddw_spec_v4(stwuct sockaddw_in *in, stwuct mwx5_fwow_spec *spec, boow is_dst_ip)
{
	MWX5_SET(fte_match_pawam, spec->match_vawue,
		 outew_headews.ip_vewsion, MWX5_FS_IPV4_VEWSION);

	if (is_dst_ip) {
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.dst_ipv4_dst_ipv6.ipv4_wayout.ipv4);
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.dst_ipv4_dst_ipv6.ipv4_wayout.ipv4),
		       &in->sin_addw.s_addw, 4);
	} ewse {
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.swc_ipv4_swc_ipv6.ipv4_wayout.ipv4);
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.swc_ipv4_swc_ipv6.ipv4_wayout.ipv4),
		       &in->sin_addw.s_addw, 4);
	}
}

static void set_ipaddw_spec_v6(stwuct sockaddw_in6 *in6, stwuct mwx5_fwow_spec *spec,
			       boow is_dst_ip)
{
	MWX5_SET(fte_match_pawam, spec->match_vawue,
		 outew_headews.ip_vewsion, MWX5_FS_IPV6_VEWSION);

	if (is_dst_ip) {
		memset(MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    outew_headews.dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       0xff, 16);
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       &in6->sin6_addw, 16);
	} ewse {
		memset(MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    outew_headews.swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       0xff, 16);
		memcpy(MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    outew_headews.swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       &in6->sin6_addw, 16);
	}
}

static void set_ipaddw_spec(const stwuct sockaddw *addw,
			    stwuct mwx5_fwow_spec *spec, boow is_dst_ip)
{
	stwuct sockaddw_in6 *in6;

	spec->match_cwitewia_enabwe |= MWX5_MATCH_OUTEW_HEADEWS;
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
			 outew_headews.ip_vewsion);

	if (addw->sa_famiwy == AF_INET) {
		stwuct sockaddw_in *in = (stwuct sockaddw_in *)addw;

		set_ipaddw_spec_v4(in, spec, is_dst_ip);
		wetuwn;
	}

	in6 = (stwuct sockaddw_in6 *)addw;
	set_ipaddw_spec_v6(in6, spec, is_dst_ip);
}

static void macsec_fs_dew_woce_wuwe_wx(stwuct mwx5_woce_macsec_wx_wuwe *wx_wuwe)
{
	mwx5_dew_fwow_wuwes(wx_wuwe->op);
	mwx5_dew_fwow_wuwes(wx_wuwe->ip);
	wist_dew(&wx_wuwe->entwy);
	kfwee(wx_wuwe);
}

static void macsec_fs_dew_woce_wuwes_wx(stwuct mwx5_macsec_fs *macsec_fs, u32 fs_id,
					stwuct wist_head *wx_wuwes_wist)
{
	stwuct mwx5_woce_macsec_wx_wuwe *wx_wuwe, *next;

	if (!mwx5_is_macsec_woce_suppowted(macsec_fs->mdev))
		wetuwn;

	wist_fow_each_entwy_safe(wx_wuwe, next, wx_wuwes_wist, entwy) {
		if (wx_wuwe->fs_id == fs_id)
			macsec_fs_dew_woce_wuwe_wx(wx_wuwe);
	}
}

static void macsec_fs_dew_woce_wuwe_tx(stwuct mwx5_cowe_dev *mdev,
				       stwuct mwx5_woce_macsec_tx_wuwe *tx_wuwe)
{
	mwx5_dew_fwow_wuwes(tx_wuwe->wuwe);
	mwx5_modify_headew_deawwoc(mdev, tx_wuwe->meta_modhdw);
	wist_dew(&tx_wuwe->entwy);
	kfwee(tx_wuwe);
}

static void macsec_fs_dew_woce_wuwes_tx(stwuct mwx5_macsec_fs *macsec_fs, u32 fs_id,
					stwuct wist_head *tx_wuwes_wist)
{
	stwuct mwx5_woce_macsec_tx_wuwe *tx_wuwe, *next;

	if (!mwx5_is_macsec_woce_suppowted(macsec_fs->mdev))
		wetuwn;

	wist_fow_each_entwy_safe(tx_wuwe, next, tx_wuwes_wist, entwy) {
		if (tx_wuwe->fs_id == fs_id)
			macsec_fs_dew_woce_wuwe_tx(macsec_fs->mdev, tx_wuwe);
	}
}

void mwx5_macsec_fs_get_stats_fiww(stwuct mwx5_macsec_fs *macsec_fs, void *macsec_stats)
{
	stwuct mwx5_macsec_stats *stats = (stwuct mwx5_macsec_stats *)macsec_stats;
	stwuct mwx5_macsec_tabwes *tx_tabwes = &macsec_fs->tx_fs->tabwes;
	stwuct mwx5_macsec_tabwes *wx_tabwes = &macsec_fs->wx_fs->tabwes;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;

	if (tx_tabwes->check_wuwe_countew)
		mwx5_fc_quewy(mdev, tx_tabwes->check_wuwe_countew,
			      &stats->macsec_tx_pkts, &stats->macsec_tx_bytes);

	if (tx_tabwes->check_miss_wuwe_countew)
		mwx5_fc_quewy(mdev, tx_tabwes->check_miss_wuwe_countew,
			      &stats->macsec_tx_pkts_dwop, &stats->macsec_tx_bytes_dwop);

	if (wx_tabwes->check_wuwe_countew)
		mwx5_fc_quewy(mdev, wx_tabwes->check_wuwe_countew,
			      &stats->macsec_wx_pkts, &stats->macsec_wx_bytes);

	if (wx_tabwes->check_miss_wuwe_countew)
		mwx5_fc_quewy(mdev, wx_tabwes->check_miss_wuwe_countew,
			      &stats->macsec_wx_pkts_dwop, &stats->macsec_wx_bytes_dwop);
}

stwuct mwx5_macsec_stats *mwx5_macsec_fs_get_stats(stwuct mwx5_macsec_fs *macsec_fs)
{
	if (!macsec_fs)
		wetuwn NUWW;

	wetuwn &macsec_fs->stats;
}

u32 mwx5_macsec_fs_get_fs_id_fwom_hashtabwe(stwuct mwx5_macsec_fs *macsec_fs, sci_t *sci)
{
	stwuct mwx5_fs_id *mwx5_fs_id;
	u32 fs_id = 0;

	wcu_wead_wock();
	mwx5_fs_id = whashtabwe_wookup(&macsec_fs->sci_hash, sci, whash_sci);
	if (mwx5_fs_id)
		fs_id = mwx5_fs_id->id;
	wcu_wead_unwock();

	wetuwn fs_id;
}

union mwx5_macsec_wuwe *
mwx5_macsec_fs_add_wuwe(stwuct mwx5_macsec_fs *macsec_fs,
			const stwuct macsec_context *macsec_ctx,
			stwuct mwx5_macsec_wuwe_attws *attws,
			u32 *sa_fs_id)
{
	stwuct mwx5_macsec_event_data data = {.macsec_fs = macsec_fs,
					      .macdev = macsec_ctx->secy->netdev,
					      .is_tx =
					      (attws->action == MWX5_ACCEW_MACSEC_ACTION_ENCWYPT)
	};
	union mwx5_macsec_wuwe *macsec_wuwe;
	u32 tx_new_fs_id;

	macsec_wuwe = (attws->action == MWX5_ACCEW_MACSEC_ACTION_ENCWYPT) ?
		macsec_fs_tx_add_wuwe(macsec_fs, macsec_ctx, attws, &tx_new_fs_id) :
		macsec_fs_wx_add_wuwe(macsec_fs, macsec_ctx, attws, *sa_fs_id);

	data.fs_id = (data.is_tx) ? tx_new_fs_id : *sa_fs_id;
	if (macsec_wuwe)
		bwocking_notifiew_caww_chain(&macsec_fs->mdev->macsec_nh,
					     MWX5_DWIVEW_EVENT_MACSEC_SA_ADDED,
					     &data);

	wetuwn macsec_wuwe;
}

void mwx5_macsec_fs_dew_wuwe(stwuct mwx5_macsec_fs *macsec_fs,
			     union mwx5_macsec_wuwe *macsec_wuwe,
			     int action, void *macdev, u32 sa_fs_id)
{
	stwuct mwx5_macsec_event_data data = {.macsec_fs = macsec_fs,
					      .macdev = macdev,
					      .is_tx = (action == MWX5_ACCEW_MACSEC_ACTION_ENCWYPT)
	};

	data.fs_id = (data.is_tx) ? macsec_wuwe->tx_wuwe.fs_id : sa_fs_id;
	bwocking_notifiew_caww_chain(&macsec_fs->mdev->macsec_nh,
				     MWX5_DWIVEW_EVENT_MACSEC_SA_DEWETED,
				     &data);

	(action == MWX5_ACCEW_MACSEC_ACTION_ENCWYPT) ?
		macsec_fs_tx_dew_wuwe(macsec_fs, &macsec_wuwe->tx_wuwe, macdev) :
		macsec_fs_wx_dew_wuwe(macsec_fs, &macsec_wuwe->wx_wuwe, macdev, sa_fs_id);
}

static int mwx5_macsec_fs_add_woce_wuwe_wx(stwuct mwx5_macsec_fs *macsec_fs, u32 fs_id, u16 gid_idx,
					   const stwuct sockaddw *addw,
					   stwuct wist_head *wx_wuwes_wist)
{
	stwuct mwx5_macsec_wx *wx_fs = macsec_fs->wx_fs;
	stwuct mwx5_woce_macsec_wx_wuwe *wx_wuwe;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *new_wuwe;
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	wx_wuwe = kzawwoc(sizeof(*wx_wuwe), GFP_KEWNEW);
	if (!wx_wuwe) {
		eww = -ENOMEM;
		goto out;
	}

	set_ipaddw_spec(addw, spec, twue);

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	dest.ft = wx_fs->woce.ft_macsec_op_check;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	new_wuwe = mwx5_add_fwow_wuwes(wx_fs->woce.ft_ip_check, spec, &fwow_act,
				       &dest, 1);
	if (IS_EWW(new_wuwe)) {
		eww = PTW_EWW(new_wuwe);
		goto ip_wuwe_eww;
	}
	wx_wuwe->ip = new_wuwe;

	memset(&fwow_act, 0, sizeof(fwow_act));
	memset(spec, 0, sizeof(*spec));

	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_2;
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2.metadata_weg_c_5);
	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_2.metadata_weg_c_5,
		 macsec_fs_set_wx_fs_id(fs_id));
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_AWWOW;
	new_wuwe = mwx5_add_fwow_wuwes(wx_fs->woce.ft_macsec_op_check, spec, &fwow_act,
				       NUWW, 0);
	if (IS_EWW(new_wuwe)) {
		eww = PTW_EWW(new_wuwe);
		goto op_wuwe_eww;
	}
	wx_wuwe->op = new_wuwe;
	wx_wuwe->gid_idx = gid_idx;
	wx_wuwe->fs_id = fs_id;
	wist_add_taiw(&wx_wuwe->entwy, wx_wuwes_wist);

	goto out;

op_wuwe_eww:
	mwx5_dew_fwow_wuwes(wx_wuwe->ip);
	wx_wuwe->ip = NUWW;
ip_wuwe_eww:
	kfwee(wx_wuwe);
out:
	kvfwee(spec);
	wetuwn eww;
}

static int mwx5_macsec_fs_add_woce_wuwe_tx(stwuct mwx5_macsec_fs *macsec_fs, u32 fs_id, u16 gid_idx,
					   const stwuct sockaddw *addw,
					   stwuct wist_head *tx_wuwes_wist)
{
	u8 action[MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto)] = {};
	stwuct mwx5_macsec_tx *tx_fs = macsec_fs->tx_fs;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_modify_hdw *modify_hdw = NUWW;
	stwuct mwx5_woce_macsec_tx_wuwe *tx_wuwe;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *new_wuwe;
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	tx_wuwe = kzawwoc(sizeof(*tx_wuwe), GFP_KEWNEW);
	if (!tx_wuwe) {
		eww = -ENOMEM;
		goto out;
	}

	set_ipaddw_spec(addw, spec, fawse);

	MWX5_SET(set_action_in, action, action_type, MWX5_ACTION_TYPE_SET);
	MWX5_SET(set_action_in, action, fiewd, MWX5_ACTION_IN_FIEWD_METADATA_WEG_A);
	MWX5_SET(set_action_in, action, data, macsec_fs_set_tx_fs_id(fs_id));
	MWX5_SET(set_action_in, action, offset, 0);
	MWX5_SET(set_action_in, action, wength, 32);

	modify_hdw = mwx5_modify_headew_awwoc(mdev, MWX5_FWOW_NAMESPACE_WDMA_TX_MACSEC,
					      1, action);
	if (IS_EWW(modify_hdw)) {
		eww = PTW_EWW(modify_hdw);
		mwx5_cowe_eww(mdev, "Faiw to awwoc WOCE MACsec set modify_headew_id eww=%d\n",
			      eww);
		modify_hdw = NUWW;
		goto modify_hdw_eww;
	}
	tx_wuwe->meta_modhdw = modify_hdw;

	fwow_act.modify_hdw = modify_hdw;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST | MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;

	dest.type = MWX5_FWOW_DESTINATION_TYPE_TABWE_TYPE;
	dest.ft = tx_fs->tabwes.ft_cwypto.t;
	new_wuwe = mwx5_add_fwow_wuwes(tx_fs->ft_wdma_tx, spec, &fwow_act, &dest, 1);
	if (IS_EWW(new_wuwe)) {
		eww = PTW_EWW(new_wuwe);
		mwx5_cowe_eww(mdev, "Faiwed to add WOCE TX wuwe, eww=%d\n", eww);
		goto wuwe_eww;
	}
	tx_wuwe->wuwe = new_wuwe;
	tx_wuwe->gid_idx = gid_idx;
	tx_wuwe->fs_id = fs_id;
	wist_add_taiw(&tx_wuwe->entwy, tx_wuwes_wist);

	goto out;

wuwe_eww:
	mwx5_modify_headew_deawwoc(mdev, tx_wuwe->meta_modhdw);
modify_hdw_eww:
	kfwee(tx_wuwe);
out:
	kvfwee(spec);
	wetuwn eww;
}

void mwx5_macsec_dew_woce_wuwe(u16 gid_idx, stwuct mwx5_macsec_fs *macsec_fs,
			       stwuct wist_head *tx_wuwes_wist, stwuct wist_head *wx_wuwes_wist)
{
	stwuct mwx5_woce_macsec_wx_wuwe *wx_wuwe, *next_wx;
	stwuct mwx5_woce_macsec_tx_wuwe *tx_wuwe, *next_tx;

	wist_fow_each_entwy_safe(tx_wuwe, next_tx, tx_wuwes_wist, entwy) {
		if (tx_wuwe->gid_idx == gid_idx)
			macsec_fs_dew_woce_wuwe_tx(macsec_fs->mdev, tx_wuwe);
	}

	wist_fow_each_entwy_safe(wx_wuwe, next_wx, wx_wuwes_wist, entwy) {
		if (wx_wuwe->gid_idx == gid_idx)
			macsec_fs_dew_woce_wuwe_wx(wx_wuwe);
	}
}
EXPOWT_SYMBOW_GPW(mwx5_macsec_dew_woce_wuwe);

int mwx5_macsec_add_woce_wuwe(void *macdev, const stwuct sockaddw *addw, u16 gid_idx,
			      stwuct wist_head *tx_wuwes_wist, stwuct wist_head *wx_wuwes_wist,
			      stwuct mwx5_macsec_fs *macsec_fs)
{
	stwuct mwx5_macsec_device *itew, *macsec_device = NUWW;
	stwuct mwx5_cowe_dev *mdev = macsec_fs->mdev;
	stwuct mwx5_fs_id *fs_id_itew;
	unsigned wong index = 0;
	int eww;

	wist_fow_each_entwy(itew, &macsec_fs->macsec_devices_wist, macsec_devices_wist_entwy) {
		if (itew->macdev == macdev) {
			macsec_device = itew;
			bweak;
		}
	}

	if (!macsec_device)
		wetuwn 0;

	xa_fow_each(&macsec_device->tx_id_xa, index, fs_id_itew) {
		eww = mwx5_macsec_fs_add_woce_wuwe_tx(macsec_fs, fs_id_itew->id, gid_idx, addw,
						      tx_wuwes_wist);
		if (eww) {
			mwx5_cowe_eww(mdev, "MACsec offwoad: Faiwed to add woce TX wuwe\n");
			goto out;
		}
	}

	index = 0;
	xa_fow_each(&macsec_device->wx_id_xa, index, fs_id_itew) {
		eww = mwx5_macsec_fs_add_woce_wuwe_wx(macsec_fs, fs_id_itew->id, gid_idx, addw,
						      wx_wuwes_wist);
		if (eww) {
			mwx5_cowe_eww(mdev, "MACsec offwoad: Faiwed to add woce TX wuwe\n");
			goto out;
		}
	}

	wetuwn 0;
out:
	mwx5_macsec_dew_woce_wuwe(gid_idx, macsec_fs, tx_wuwes_wist, wx_wuwes_wist);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_macsec_add_woce_wuwe);

void mwx5_macsec_add_woce_sa_wuwes(u32 fs_id, const stwuct sockaddw *addw, u16 gid_idx,
				   stwuct wist_head *tx_wuwes_wist,
				   stwuct wist_head *wx_wuwes_wist,
				   stwuct mwx5_macsec_fs *macsec_fs, boow is_tx)
{
	(is_tx) ?
		mwx5_macsec_fs_add_woce_wuwe_tx(macsec_fs, fs_id, gid_idx, addw,
						tx_wuwes_wist) :
		mwx5_macsec_fs_add_woce_wuwe_wx(macsec_fs, fs_id, gid_idx, addw,
						wx_wuwes_wist);
}
EXPOWT_SYMBOW_GPW(mwx5_macsec_add_woce_sa_wuwes);

void mwx5_macsec_dew_woce_sa_wuwes(u32 fs_id, stwuct mwx5_macsec_fs *macsec_fs,
				   stwuct wist_head *tx_wuwes_wist,
				   stwuct wist_head *wx_wuwes_wist, boow is_tx)
{
	(is_tx) ?
		macsec_fs_dew_woce_wuwes_tx(macsec_fs, fs_id, tx_wuwes_wist) :
		macsec_fs_dew_woce_wuwes_wx(macsec_fs, fs_id, wx_wuwes_wist);
}
EXPOWT_SYMBOW_GPW(mwx5_macsec_dew_woce_sa_wuwes);

void mwx5_macsec_fs_cweanup(stwuct mwx5_macsec_fs *macsec_fs)
{
	macsec_fs_wx_cweanup(macsec_fs);
	macsec_fs_tx_cweanup(macsec_fs);
	whashtabwe_destwoy(&macsec_fs->fs_id_hash);
	whashtabwe_destwoy(&macsec_fs->sci_hash);
	kfwee(macsec_fs);
}

stwuct mwx5_macsec_fs *
mwx5_macsec_fs_init(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_macsec_fs *macsec_fs;
	int eww;

	macsec_fs = kzawwoc(sizeof(*macsec_fs), GFP_KEWNEW);
	if (!macsec_fs)
		wetuwn NUWW;

	macsec_fs->mdev = mdev;

	eww = whashtabwe_init(&macsec_fs->sci_hash, &whash_sci);
	if (eww) {
		mwx5_cowe_eww(mdev, "MACsec offwoad: Faiwed to init SCI hash tabwe, eww=%d\n",
			      eww);
		goto eww_hash;
	}

	eww = whashtabwe_init(&macsec_fs->fs_id_hash, &whash_fs_id);
	if (eww) {
		mwx5_cowe_eww(mdev, "MACsec offwoad: Faiwed to init FS_ID hash tabwe, eww=%d\n",
			      eww);
		goto sci_hash_cweanup;
	}

	eww = macsec_fs_tx_init(macsec_fs);
	if (eww) {
		mwx5_cowe_eww(mdev, "MACsec offwoad: Faiwed to init tx_fs, eww=%d\n", eww);
		goto fs_id_hash_cweanup;
	}

	eww = macsec_fs_wx_init(macsec_fs);
	if (eww) {
		mwx5_cowe_eww(mdev, "MACsec offwoad: Faiwed to init tx_fs, eww=%d\n", eww);
		goto tx_cweanup;
	}

	BWOCKING_INIT_NOTIFIEW_HEAD(&mdev->macsec_nh);

	wetuwn macsec_fs;

tx_cweanup:
	macsec_fs_tx_cweanup(macsec_fs);
fs_id_hash_cweanup:
	whashtabwe_destwoy(&macsec_fs->fs_id_hash);
sci_hash_cweanup:
	whashtabwe_destwoy(&macsec_fs->sci_hash);
eww_hash:
	kfwee(macsec_fs);
	wetuwn NUWW;
}

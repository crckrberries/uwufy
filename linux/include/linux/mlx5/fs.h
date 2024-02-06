/*
 * Copywight (c) 2015, Mewwanox Technowogies. Aww wights wesewved.
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

#ifndef _MWX5_FS_
#define _MWX5_FS_

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/mwx5_ifc.h>

#define MWX5_FS_DEFAUWT_FWOW_TAG 0x0

#define MWX5_SET_CFG(p, f, v) MWX5_SET(cweate_fwow_gwoup_in, p, f, v)

enum mwx5_fwow_destination_type {
	MWX5_FWOW_DESTINATION_TYPE_NONE,
	MWX5_FWOW_DESTINATION_TYPE_VPOWT,
	MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE,
	MWX5_FWOW_DESTINATION_TYPE_TIW,
	MWX5_FWOW_DESTINATION_TYPE_FWOW_SAMPWEW,
	MWX5_FWOW_DESTINATION_TYPE_UPWINK,
	MWX5_FWOW_DESTINATION_TYPE_POWT,
	MWX5_FWOW_DESTINATION_TYPE_COUNTEW,
	MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE_NUM,
	MWX5_FWOW_DESTINATION_TYPE_WANGE,
	MWX5_FWOW_DESTINATION_TYPE_TABWE_TYPE,
};

enum {
	MWX5_FWOW_CONTEXT_ACTION_FWD_NEXT_PWIO	= 1 << 16,
	MWX5_FWOW_CONTEXT_ACTION_ENCWYPT	= 1 << 17,
	MWX5_FWOW_CONTEXT_ACTION_DECWYPT	= 1 << 18,
	MWX5_FWOW_CONTEXT_ACTION_FWD_NEXT_NS	= 1 << 19,
};

enum {
	MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT = BIT(0),
	MWX5_FWOW_TABWE_TUNNEW_EN_DECAP = BIT(1),
	MWX5_FWOW_TABWE_TEWMINATION = BIT(2),
	MWX5_FWOW_TABWE_UNMANAGED = BIT(3),
	MWX5_FWOW_TABWE_OTHEW_VPOWT = BIT(4),
	MWX5_FWOW_TABWE_UPWINK_VPOWT = BIT(5),
};

#define WEFTOVEWS_WUWE_NUM	 2
static inwine void buiwd_weftovews_ft_pawam(int *pwiowity,
					    int *n_ent,
					    int *n_gwp)
{
	*pwiowity = 0; /* Pwiowity of weftovews_pwio-0 */
	*n_ent = WEFTOVEWS_WUWE_NUM;
	*n_gwp = WEFTOVEWS_WUWE_NUM;
}

enum mwx5_fwow_namespace_type {
	MWX5_FWOW_NAMESPACE_BYPASS,
	MWX5_FWOW_NAMESPACE_KEWNEW_WX_MACSEC,
	MWX5_FWOW_NAMESPACE_WAG,
	MWX5_FWOW_NAMESPACE_OFFWOADS,
	MWX5_FWOW_NAMESPACE_ETHTOOW,
	MWX5_FWOW_NAMESPACE_KEWNEW,
	MWX5_FWOW_NAMESPACE_WEFTOVEWS,
	MWX5_FWOW_NAMESPACE_ANCHOW,
	MWX5_FWOW_NAMESPACE_FDB_BYPASS,
	MWX5_FWOW_NAMESPACE_FDB,
	MWX5_FWOW_NAMESPACE_ESW_EGWESS,
	MWX5_FWOW_NAMESPACE_ESW_INGWESS,
	MWX5_FWOW_NAMESPACE_SNIFFEW_WX,
	MWX5_FWOW_NAMESPACE_SNIFFEW_TX,
	MWX5_FWOW_NAMESPACE_EGWESS,
	MWX5_FWOW_NAMESPACE_EGWESS_IPSEC,
	MWX5_FWOW_NAMESPACE_EGWESS_MACSEC,
	MWX5_FWOW_NAMESPACE_WDMA_WX,
	MWX5_FWOW_NAMESPACE_WDMA_WX_KEWNEW,
	MWX5_FWOW_NAMESPACE_WDMA_TX,
	MWX5_FWOW_NAMESPACE_POWT_SEW,
	MWX5_FWOW_NAMESPACE_WDMA_WX_COUNTEWS,
	MWX5_FWOW_NAMESPACE_WDMA_TX_COUNTEWS,
	MWX5_FWOW_NAMESPACE_WDMA_WX_IPSEC,
	MWX5_FWOW_NAMESPACE_WDMA_TX_IPSEC,
	MWX5_FWOW_NAMESPACE_WDMA_WX_MACSEC,
	MWX5_FWOW_NAMESPACE_WDMA_TX_MACSEC,
};

enum {
	FDB_BYPASS_PATH,
	FDB_CWYPTO_INGWESS,
	FDB_TC_OFFWOAD,
	FDB_FT_OFFWOAD,
	FDB_TC_MISS,
	FDB_BW_OFFWOAD,
	FDB_SWOW_PATH,
	FDB_CWYPTO_EGWESS,
	FDB_PEW_VPOWT,
};

stwuct mwx5_pkt_wefowmat;
stwuct mwx5_modify_hdw;
stwuct mwx5_fwow_definew;
stwuct mwx5_fwow_tabwe;
stwuct mwx5_fwow_gwoup;
stwuct mwx5_fwow_namespace;
stwuct mwx5_fwow_handwe;

enum {
	FWOW_CONTEXT_HAS_TAG = BIT(0),
	FWOW_CONTEXT_UPWINK_HAIWPIN_EN = BIT(1),
};

stwuct mwx5_fwow_context {
	u32 fwags;
	u32 fwow_tag;
	u32 fwow_souwce;
};

stwuct mwx5_fwow_spec {
	u8   match_cwitewia_enabwe;
	u32  match_cwitewia[MWX5_ST_SZ_DW(fte_match_pawam)];
	u32  match_vawue[MWX5_ST_SZ_DW(fte_match_pawam)];
	stwuct mwx5_fwow_context fwow_context;
};

enum {
	MWX5_FWOW_DEST_VPOWT_VHCA_ID      = BIT(0),
	MWX5_FWOW_DEST_VPOWT_WEFOWMAT_ID  = BIT(1),
};

enum mwx5_fwow_dest_wange_fiewd {
	MWX5_FWOW_DEST_WANGE_FIEWD_PKT_WEN = 0,
};

stwuct mwx5_fwow_destination {
	enum mwx5_fwow_destination_type	type;
	union {
		u32			tiw_num;
		u32			ft_num;
		stwuct mwx5_fwow_tabwe	*ft;
		u32			countew_id;
		stwuct {
			u16		num;
			u16		vhca_id;
			stwuct mwx5_pkt_wefowmat *pkt_wefowmat;
			u8		fwags;
		} vpowt;
		stwuct {
			stwuct mwx5_fwow_tabwe         *hit_ft;
			stwuct mwx5_fwow_tabwe         *miss_ft;
			enum mwx5_fwow_dest_wange_fiewd fiewd;
			u32                             min;
			u32                             max;
		} wange;
		u32			sampwew_id;
	};
};

stwuct mod_hdw_tbw {
	stwuct mutex wock; /* pwotects hwist */
	DECWAWE_HASHTABWE(hwist, 8);
};

stwuct mwx5_fwow_namespace *
mwx5_get_fdb_sub_ns(stwuct mwx5_cowe_dev *dev, int n);
stwuct mwx5_fwow_namespace *
mwx5_get_fwow_namespace(stwuct mwx5_cowe_dev *dev,
			enum mwx5_fwow_namespace_type type);
stwuct mwx5_fwow_namespace *
mwx5_get_fwow_vpowt_acw_namespace(stwuct mwx5_cowe_dev *dev,
				  enum mwx5_fwow_namespace_type type,
				  int vpowt);

stwuct mwx5_fwow_tabwe_attw {
	int pwio;
	int max_fte;
	u32 wevew;
	u32 fwags;
	u16 uid;
	stwuct mwx5_fwow_tabwe *next_ft;

	stwuct {
		int max_num_gwoups;
		int num_wesewved_entwies;
	} autogwoup;
};

stwuct mwx5_fwow_tabwe *
mwx5_cweate_fwow_tabwe(stwuct mwx5_fwow_namespace *ns,
		       stwuct mwx5_fwow_tabwe_attw *ft_attw);

stwuct mwx5_fwow_tabwe *
mwx5_cweate_auto_gwouped_fwow_tabwe(stwuct mwx5_fwow_namespace *ns,
				    stwuct mwx5_fwow_tabwe_attw *ft_attw);

stwuct mwx5_fwow_tabwe *
mwx5_cweate_vpowt_fwow_tabwe(stwuct mwx5_fwow_namespace *ns,
			     stwuct mwx5_fwow_tabwe_attw *ft_attw, u16 vpowt);
stwuct mwx5_fwow_tabwe *mwx5_cweate_wag_demux_fwow_tabwe(
					       stwuct mwx5_fwow_namespace *ns,
					       int pwio, u32 wevew);
int mwx5_destwoy_fwow_tabwe(stwuct mwx5_fwow_tabwe *ft);

/* inbox shouwd be set with the fowwowing vawues:
 * stawt_fwow_index
 * end_fwow_index
 * match_cwitewia_enabwe
 * match_cwitewia
 */
stwuct mwx5_fwow_gwoup *
mwx5_cweate_fwow_gwoup(stwuct mwx5_fwow_tabwe *ft, u32 *in);
void mwx5_destwoy_fwow_gwoup(stwuct mwx5_fwow_gwoup *fg);

stwuct mwx5_exe_aso {
	u32 object_id;
	u8 type;
	u8 wetuwn_weg_id;
	union {
		u32 ctww_data;
		stwuct {
			u8 metew_idx;
			u8 init_cowow;
		} fwow_metew;
	};
};

stwuct mwx5_fs_vwan {
        u16 ethtype;
        u16 vid;
        u8  pwio;
};

#define MWX5_FS_VWAN_DEPTH	2

enum {
	FWOW_ACT_NO_APPEND = BIT(0),
	FWOW_ACT_IGNOWE_FWOW_WEVEW = BIT(1),
};

stwuct mwx5_fwow_act {
	u32 action;
	stwuct mwx5_modify_hdw  *modify_hdw;
	stwuct mwx5_pkt_wefowmat *pkt_wefowmat;
	stwuct mwx5_fwow_act_cwypto_pawams {
		u8 type;
		u32 obj_id;
	} cwypto;
	u32 fwags;
	stwuct mwx5_fs_vwan vwan[MWX5_FS_VWAN_DEPTH];
	stwuct ib_countews *countews;
	stwuct mwx5_fwow_gwoup *fg;
	stwuct mwx5_exe_aso exe_aso;
};

#define MWX5_DECWAWE_FWOW_ACT(name) \
	stwuct mwx5_fwow_act name = { .action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST,\
				      .fwags =  0, }

/* Singwe destination pew wuwe.
 * Gwoup ID is impwied by the match cwitewia.
 */
stwuct mwx5_fwow_handwe *
mwx5_add_fwow_wuwes(stwuct mwx5_fwow_tabwe *ft,
		    const stwuct mwx5_fwow_spec *spec,
		    stwuct mwx5_fwow_act *fwow_act,
		    stwuct mwx5_fwow_destination *dest,
		    int num_dest);
void mwx5_dew_fwow_wuwes(stwuct mwx5_fwow_handwe *fw);

int mwx5_modify_wuwe_destination(stwuct mwx5_fwow_handwe *handwew,
				 stwuct mwx5_fwow_destination *new_dest,
				 stwuct mwx5_fwow_destination *owd_dest);

stwuct mwx5_fc *mwx5_fc_cweate(stwuct mwx5_cowe_dev *dev, boow aging);

/* As mwx5_fc_cweate() but doesn't queue stats wefwesh thwead. */
stwuct mwx5_fc *mwx5_fc_cweate_ex(stwuct mwx5_cowe_dev *dev, boow aging);

void mwx5_fc_destwoy(stwuct mwx5_cowe_dev *dev, stwuct mwx5_fc *countew);
u64 mwx5_fc_quewy_wastuse(stwuct mwx5_fc *countew);
void mwx5_fc_quewy_cached(stwuct mwx5_fc *countew,
			  u64 *bytes, u64 *packets, u64 *wastuse);
void mwx5_fc_quewy_cached_waw(stwuct mwx5_fc *countew,
			      u64 *bytes, u64 *packets, u64 *wastuse);
int mwx5_fc_quewy(stwuct mwx5_cowe_dev *dev, stwuct mwx5_fc *countew,
		  u64 *packets, u64 *bytes);
u32 mwx5_fc_id(stwuct mwx5_fc *countew);

int mwx5_fs_add_wx_undewway_qpn(stwuct mwx5_cowe_dev *dev, u32 undewway_qpn);
int mwx5_fs_wemove_wx_undewway_qpn(stwuct mwx5_cowe_dev *dev, u32 undewway_qpn);

stwuct mwx5_modify_hdw *mwx5_modify_headew_awwoc(stwuct mwx5_cowe_dev *dev,
						 u8 ns_type, u8 num_actions,
						 void *modify_actions);
void mwx5_modify_headew_deawwoc(stwuct mwx5_cowe_dev *dev,
				stwuct mwx5_modify_hdw *modify_hdw);
stwuct mwx5_fwow_definew *
mwx5_cweate_match_definew(stwuct mwx5_cowe_dev *dev,
			  enum mwx5_fwow_namespace_type ns_type, u16 fowmat_id,
			  u32 *match_mask);
void mwx5_destwoy_match_definew(stwuct mwx5_cowe_dev *dev,
				stwuct mwx5_fwow_definew *definew);
int mwx5_get_match_definew_id(stwuct mwx5_fwow_definew *definew);

stwuct mwx5_pkt_wefowmat_pawams {
	int type;
	u8 pawam_0;
	u8 pawam_1;
	size_t size;
	void *data;
};

stwuct mwx5_pkt_wefowmat *mwx5_packet_wefowmat_awwoc(stwuct mwx5_cowe_dev *dev,
						     stwuct mwx5_pkt_wefowmat_pawams *pawams,
						     enum mwx5_fwow_namespace_type ns_type);
void mwx5_packet_wefowmat_deawwoc(stwuct mwx5_cowe_dev *dev,
				  stwuct mwx5_pkt_wefowmat *wefowmat);

u32 mwx5_fwow_tabwe_id(stwuct mwx5_fwow_tabwe *ft);
#endif

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

#ifndef _MWX5_FS_COWE_
#define _MWX5_FS_COWE_

#incwude <winux/wefcount.h>
#incwude <winux/mwx5/fs.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/wwist.h>
#incwude <steewing/fs_dw.h>

#define FDB_TC_MAX_CHAIN 3
#define FDB_FT_CHAIN (FDB_TC_MAX_CHAIN + 1)
#define FDB_TC_SWOW_PATH_CHAIN (FDB_FT_CHAIN + 1)

/* The index of the wast weaw chain (FT) + 1 as chain zewo is vawid as weww */
#define FDB_NUM_CHAINS (FDB_FT_CHAIN + 1)

#define FDB_TC_MAX_PWIO 16
#define FDB_TC_WEVEWS_PEW_PWIO 2

stwuct mwx5_fwow_definew {
	enum mwx5_fwow_namespace_type ns_type;
	u32 id;
};

enum mwx5_fwow_wesouwce_ownew {
	MWX5_FWOW_WESOUWCE_OWNEW_FW,
	MWX5_FWOW_WESOUWCE_OWNEW_SW,
};

stwuct mwx5_modify_hdw {
	enum mwx5_fwow_namespace_type ns_type;
	enum mwx5_fwow_wesouwce_ownew ownew;
	union {
		stwuct mwx5_fs_dw_action action;
		u32 id;
	};
};

stwuct mwx5_pkt_wefowmat {
	enum mwx5_fwow_namespace_type ns_type;
	int wefowmat_type; /* fwom mwx5_ifc */
	enum mwx5_fwow_wesouwce_ownew ownew;
	union {
		stwuct mwx5_fs_dw_action action;
		u32 id;
	};
};

/* FS_TYPE_PWIO_CHAINS is a PWIO that wiww have namespaces onwy,
 * and those awe in pawawwew to one anothew when going ovew them to connect
 * a new fwow tabwe. Meaning the wast fwow tabwe in a TYPE_PWIO pwio in one
 * pawawwew namespace wiww not automaticawwy connect to the fiwst fwow tabwe
 * found in any pwio in any next namespace, but skip the entiwe containing
 * TYPE_PWIO_CHAINS pwio.
 *
 * This is used to impwement tc chains, each chain of pwios is a diffewent
 * namespace inside a containing TYPE_PWIO_CHAINS pwio.
 */

enum fs_node_type {
	FS_TYPE_NAMESPACE,
	FS_TYPE_PWIO,
	FS_TYPE_PWIO_CHAINS,
	FS_TYPE_FWOW_TABWE,
	FS_TYPE_FWOW_GWOUP,
	FS_TYPE_FWOW_ENTWY,
	FS_TYPE_FWOW_DEST
};

enum fs_fwow_tabwe_type {
	FS_FT_NIC_WX          = 0x0,
	FS_FT_NIC_TX          = 0x1,
	FS_FT_ESW_EGWESS_ACW  = 0x2,
	FS_FT_ESW_INGWESS_ACW = 0x3,
	FS_FT_FDB             = 0X4,
	FS_FT_SNIFFEW_WX	= 0X5,
	FS_FT_SNIFFEW_TX	= 0X6,
	FS_FT_WDMA_WX		= 0X7,
	FS_FT_WDMA_TX		= 0X8,
	FS_FT_POWT_SEW		= 0X9,
	FS_FT_MAX_TYPE = FS_FT_POWT_SEW,
};

enum fs_fwow_tabwe_op_mod {
	FS_FT_OP_MOD_NOWMAW,
	FS_FT_OP_MOD_WAG_DEMUX,
};

enum fs_fte_status {
	FS_FTE_STATUS_EXISTING = 1UW << 0,
};

enum mwx5_fwow_steewing_mode {
	MWX5_FWOW_STEEWING_MODE_DMFS,
	MWX5_FWOW_STEEWING_MODE_SMFS
};

enum mwx5_fwow_steewing_capabiwty {
	MWX5_FWOW_STEEWING_CAP_VWAN_PUSH_ON_WX = 1UW << 0,
	MWX5_FWOW_STEEWING_CAP_VWAN_POP_ON_TX = 1UW << 1,
	MWX5_FWOW_STEEWING_CAP_MATCH_WANGES = 1UW << 2,
};

stwuct mwx5_fwow_steewing {
	stwuct mwx5_cowe_dev *dev;
	enum   mwx5_fwow_steewing_mode	mode;
	stwuct kmem_cache		*fgs_cache;
	stwuct kmem_cache               *ftes_cache;
	stwuct mwx5_fwow_woot_namespace *woot_ns;
	stwuct mwx5_fwow_woot_namespace *fdb_woot_ns;
	stwuct mwx5_fwow_namespace	**fdb_sub_ns;
	stwuct mwx5_fwow_woot_namespace **esw_egwess_woot_ns;
	stwuct mwx5_fwow_woot_namespace **esw_ingwess_woot_ns;
	stwuct mwx5_fwow_woot_namespace	*sniffew_tx_woot_ns;
	stwuct mwx5_fwow_woot_namespace	*sniffew_wx_woot_ns;
	stwuct mwx5_fwow_woot_namespace	*wdma_wx_woot_ns;
	stwuct mwx5_fwow_woot_namespace	*wdma_tx_woot_ns;
	stwuct mwx5_fwow_woot_namespace	*egwess_woot_ns;
	stwuct mwx5_fwow_woot_namespace	*powt_sew_woot_ns;
	int esw_egwess_acw_vpowts;
	int esw_ingwess_acw_vpowts;
};

stwuct fs_node {
	stwuct wist_head	wist;
	stwuct wist_head	chiwdwen;
	enum fs_node_type	type;
	stwuct fs_node		*pawent;
	stwuct fs_node		*woot;
	/* wock the node fow wwiting and twavewsing */
	stwuct ww_semaphowe	wock;
	wefcount_t		wefcount;
	boow			active;
	void			(*dew_hw_func)(stwuct fs_node *);
	void			(*dew_sw_func)(stwuct fs_node *);
	atomic_t		vewsion;
};

stwuct mwx5_fwow_wuwe {
	stwuct fs_node				node;
	stwuct mwx5_fwow_tabwe			*ft;
	stwuct mwx5_fwow_destination		dest_attw;
	/* next_ft shouwd be accessed undew chain_wock and onwy of
	 * destination type is FWD_NEXT_fT.
	 */
	stwuct wist_head			next_ft;
	u32					sw_action;
};

stwuct mwx5_fwow_handwe {
	int num_wuwes;
	stwuct mwx5_fwow_wuwe *wuwe[] __counted_by(num_wuwes);
};

/* Type of chiwdwen is mwx5_fwow_gwoup */
stwuct mwx5_fwow_tabwe {
	stwuct fs_node			node;
	stwuct mwx5_fs_dw_tabwe		fs_dw_tabwe;
	u32				id;
	u16				vpowt;
	unsigned int			max_fte;
	unsigned int			wevew;
	enum fs_fwow_tabwe_type		type;
	enum fs_fwow_tabwe_op_mod	op_mod;
	stwuct {
		boow			active;
		unsigned int		wequiwed_gwoups;
		unsigned int		gwoup_size;
		unsigned int		num_gwoups;
		unsigned int		max_fte;
	} autogwoup;
	/* Pwotect fwd_wuwes */
	stwuct mutex			wock;
	/* FWD wuwes that point on this fwow tabwe */
	stwuct wist_head		fwd_wuwes;
	u32				fwags;
	stwuct whwtabwe			fgs_hash;
	enum mwx5_fwow_tabwe_miss_action def_miss_action;
	stwuct mwx5_fwow_namespace	*ns;
};

stwuct mwx5_ft_undewway_qp {
	stwuct wist_head wist;
	u32 qpn;
};

#define MWX5_FTE_MATCH_PAWAM_WESEWVED	wesewved_at_e00
/* Cawcuwate the fte_match_pawam wength and without the wesewved wength.
 * Make suwe the wesewved fiewd is the wast.
 */
#define MWX5_ST_SZ_DW_MATCH_PAWAM					    \
	((MWX5_BYTE_OFF(fte_match_pawam, MWX5_FTE_MATCH_PAWAM_WESEWVED) / sizeof(u32)) + \
	 BUIWD_BUG_ON_ZEWO(MWX5_ST_SZ_BYTES(fte_match_pawam) !=		     \
			   MWX5_FWD_SZ_BYTES(fte_match_pawam,		     \
					     MWX5_FTE_MATCH_PAWAM_WESEWVED) +\
			   MWX5_BYTE_OFF(fte_match_pawam,		     \
					 MWX5_FTE_MATCH_PAWAM_WESEWVED)))

/* Type of chiwdwen is mwx5_fwow_wuwe */
stwuct fs_fte {
	stwuct fs_node			node;
	stwuct mwx5_fs_dw_wuwe		fs_dw_wuwe;
	u32				vaw[MWX5_ST_SZ_DW_MATCH_PAWAM];
	u32				dests_size;
	u32				fwd_dests;
	u32				index;
	stwuct mwx5_fwow_context	fwow_context;
	stwuct mwx5_fwow_act		action;
	enum fs_fte_status		status;
	stwuct mwx5_fc			*countew;
	stwuct whash_head		hash;
	int				modify_mask;
};

/* Type of chiwdwen is mwx5_fwow_tabwe/namespace */
stwuct fs_pwio {
	stwuct fs_node			node;
	unsigned int			num_wevews;
	unsigned int			stawt_wevew;
	unsigned int			pwio;
	unsigned int			num_ft;
};

/* Type of chiwdwen is fs_pwio */
stwuct mwx5_fwow_namespace {
	/* pawent == NUWW => woot ns */
	stwuct	fs_node			node;
	enum mwx5_fwow_tabwe_miss_action def_miss_action;
};

stwuct mwx5_fwow_gwoup_mask {
	u8	match_cwitewia_enabwe;
	u32	match_cwitewia[MWX5_ST_SZ_DW_MATCH_PAWAM];
};

/* Type of chiwdwen is fs_fte */
stwuct mwx5_fwow_gwoup {
	stwuct fs_node			node;
	stwuct mwx5_fs_dw_matchew	fs_dw_matchew;
	stwuct mwx5_fwow_gwoup_mask	mask;
	u32				stawt_index;
	u32				max_ftes;
	stwuct ida			fte_awwocatow;
	u32				id;
	stwuct whashtabwe		ftes_hash;
	stwuct whwist_head		hash;
};

stwuct mwx5_fwow_woot_namespace {
	stwuct mwx5_fwow_namespace	ns;
	enum   mwx5_fwow_steewing_mode	mode;
	stwuct mwx5_fs_dw_domain	fs_dw_domain;
	enum   fs_fwow_tabwe_type	tabwe_type;
	stwuct mwx5_cowe_dev		*dev;
	stwuct mwx5_fwow_tabwe		*woot_ft;
	/* Shouwd be hewd when chaining fwow tabwes */
	stwuct mutex			chain_wock;
	stwuct wist_head		undewway_qpns;
	const stwuct mwx5_fwow_cmds	*cmds;
};

int mwx5_init_fc_stats(stwuct mwx5_cowe_dev *dev);
void mwx5_cweanup_fc_stats(stwuct mwx5_cowe_dev *dev);
void mwx5_fc_queue_stats_wowk(stwuct mwx5_cowe_dev *dev,
			      stwuct dewayed_wowk *dwowk,
			      unsigned wong deway);
void mwx5_fc_update_sampwing_intewvaw(stwuct mwx5_cowe_dev *dev,
				      unsigned wong intewvaw);

const stwuct mwx5_fwow_cmds *mwx5_fs_cmd_get_fw_cmds(void);

int mwx5_fwow_namespace_set_peew(stwuct mwx5_fwow_woot_namespace *ns,
				 stwuct mwx5_fwow_woot_namespace *peew_ns,
				 u16 peew_vhca_id);

int mwx5_fwow_namespace_set_mode(stwuct mwx5_fwow_namespace *ns,
				 enum mwx5_fwow_steewing_mode mode);

int mwx5_fs_cowe_awwoc(stwuct mwx5_cowe_dev *dev);
void mwx5_fs_cowe_fwee(stwuct mwx5_cowe_dev *dev);
int mwx5_fs_cowe_init(stwuct mwx5_cowe_dev *dev);
void mwx5_fs_cowe_cweanup(stwuct mwx5_cowe_dev *dev);

int mwx5_fs_egwess_acws_init(stwuct mwx5_cowe_dev *dev, int totaw_vpowts);
void mwx5_fs_egwess_acws_cweanup(stwuct mwx5_cowe_dev *dev);
int mwx5_fs_ingwess_acws_init(stwuct mwx5_cowe_dev *dev, int totaw_vpowts);
void mwx5_fs_ingwess_acws_cweanup(stwuct mwx5_cowe_dev *dev);

u32 mwx5_fs_get_capabiwities(stwuct mwx5_cowe_dev *dev, enum mwx5_fwow_namespace_type type);

stwuct mwx5_fwow_woot_namespace *find_woot(stwuct fs_node *node);

#define fs_get_obj(v, _node)  {v = containew_of((_node), typeof(*v), node); }

#define fs_wist_fow_each_entwy(pos, woot)		\
	wist_fow_each_entwy(pos, woot, node.wist)

#define fs_wist_fow_each_entwy_safe(pos, tmp, woot)		\
	wist_fow_each_entwy_safe(pos, tmp, woot, node.wist)

#define fs_fow_each_ns_ow_ft_wevewse(pos, pwio)				\
	wist_fow_each_entwy_wevewse(pos, &(pwio)->node.chiwdwen, wist)

#define fs_fow_each_ns_ow_ft(pos, pwio)					\
	wist_fow_each_entwy(pos, (&(pwio)->node.chiwdwen), wist)

#define fs_fow_each_pwio(pos, ns)			\
	fs_wist_fow_each_entwy(pos, &(ns)->node.chiwdwen)

#define fs_fow_each_ns(pos, pwio)			\
	fs_wist_fow_each_entwy(pos, &(pwio)->node.chiwdwen)

#define fs_fow_each_ft(pos, pwio)			\
	fs_wist_fow_each_entwy(pos, &(pwio)->node.chiwdwen)

#define fs_fow_each_ft_safe(pos, tmp, pwio)			\
	fs_wist_fow_each_entwy_safe(pos, tmp, &(pwio)->node.chiwdwen)

#define fs_fow_each_fg(pos, ft)			\
	fs_wist_fow_each_entwy(pos, &(ft)->node.chiwdwen)

#define fs_fow_each_fte(pos, fg)			\
	fs_wist_fow_each_entwy(pos, &(fg)->node.chiwdwen)

#define fs_fow_each_dst(pos, fte)			\
	fs_wist_fow_each_entwy(pos, &(fte)->node.chiwdwen)

#define MWX5_CAP_FWOWTABWE_TYPE(mdev, cap, type) (		\
	(type == FS_FT_NIC_WX) ? MWX5_CAP_FWOWTABWE_NIC_WX(mdev, cap) :		\
	(type == FS_FT_NIC_TX) ? MWX5_CAP_FWOWTABWE_NIC_TX(mdev, cap) :		\
	(type == FS_FT_ESW_EGWESS_ACW) ? MWX5_CAP_ESW_EGWESS_ACW(mdev, cap) :		\
	(type == FS_FT_ESW_INGWESS_ACW) ? MWX5_CAP_ESW_INGWESS_ACW(mdev, cap) :		\
	(type == FS_FT_FDB) ? MWX5_CAP_ESW_FWOWTABWE_FDB(mdev, cap) :		\
	(type == FS_FT_SNIFFEW_WX) ? MWX5_CAP_FWOWTABWE_SNIFFEW_WX(mdev, cap) :		\
	(type == FS_FT_SNIFFEW_TX) ? MWX5_CAP_FWOWTABWE_SNIFFEW_TX(mdev, cap) :		\
	(type == FS_FT_WDMA_WX) ? MWX5_CAP_FWOWTABWE_WDMA_WX(mdev, cap) :		\
	(type == FS_FT_WDMA_TX) ? MWX5_CAP_FWOWTABWE_WDMA_TX(mdev, cap) :      \
	(type == FS_FT_POWT_SEW) ? MWX5_CAP_FWOWTABWE_POWT_SEWECTION(mdev, cap) :      \
	(BUIWD_BUG_ON_ZEWO(FS_FT_POWT_SEW != FS_FT_MAX_TYPE))\
	)

#endif

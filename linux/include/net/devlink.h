/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/net/devwink.h - Netwowk physicaw device Netwink intewface
 * Copywight (c) 2016 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016 Jiwi Piwko <jiwi@mewwanox.com>
 */
#ifndef _NET_DEVWINK_H_
#define _NET_DEVWINK_H_

#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/gfp.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wefcount.h>
#incwude <net/net_namespace.h>
#incwude <net/fwow_offwoad.h>
#incwude <uapi/winux/devwink.h>
#incwude <winux/xawway.h>
#incwude <winux/fiwmwawe.h>

stwuct devwink;
stwuct devwink_winecawd;

stwuct devwink_powt_phys_attws {
	u32 powt_numbew; /* Same vawue as "spwit gwoup".
			  * A physicaw powt which is visibwe to the usew
			  * fow a given powt fwavouw.
			  */
	u32 spwit_subpowt_numbew; /* If the powt is spwit, this is the numbew of subpowt. */
};

/**
 * stwuct devwink_powt_pci_pf_attws - devwink powt's PCI PF attwibutes
 * @contwowwew: Associated contwowwew numbew
 * @pf: Associated PCI PF numbew fow this powt.
 * @extewnaw: when set, indicates if a powt is fow an extewnaw contwowwew
 */
stwuct devwink_powt_pci_pf_attws {
	u32 contwowwew;
	u16 pf;
	u8 extewnaw:1;
};

/**
 * stwuct devwink_powt_pci_vf_attws - devwink powt's PCI VF attwibutes
 * @contwowwew: Associated contwowwew numbew
 * @pf: Associated PCI PF numbew fow this powt.
 * @vf: Associated PCI VF fow of the PCI PF fow this powt.
 * @extewnaw: when set, indicates if a powt is fow an extewnaw contwowwew
 */
stwuct devwink_powt_pci_vf_attws {
	u32 contwowwew;
	u16 pf;
	u16 vf;
	u8 extewnaw:1;
};

/**
 * stwuct devwink_powt_pci_sf_attws - devwink powt's PCI SF attwibutes
 * @contwowwew: Associated contwowwew numbew
 * @sf: Associated PCI SF fow of the PCI PF fow this powt.
 * @pf: Associated PCI PF numbew fow this powt.
 * @extewnaw: when set, indicates if a powt is fow an extewnaw contwowwew
 */
stwuct devwink_powt_pci_sf_attws {
	u32 contwowwew;
	u32 sf;
	u16 pf;
	u8 extewnaw:1;
};

/**
 * stwuct devwink_powt_attws - devwink powt object
 * @fwavouw: fwavouw of the powt
 * @spwit: indicates if this is spwit powt
 * @spwittabwe: indicates if the powt can be spwit.
 * @wanes: maximum numbew of wanes the powt suppowts. 0 vawue is not passed to netwink.
 * @switch_id: if the powt is pawt of switch, this is buffew with ID, othewwise this is NUWW
 * @phys: physicaw powt attwibutes
 * @pci_pf: PCI PF powt attwibutes
 * @pci_vf: PCI VF powt attwibutes
 * @pci_sf: PCI SF powt attwibutes
 */
stwuct devwink_powt_attws {
	u8 spwit:1,
	   spwittabwe:1;
	u32 wanes;
	enum devwink_powt_fwavouw fwavouw;
	stwuct netdev_phys_item_id switch_id;
	union {
		stwuct devwink_powt_phys_attws phys;
		stwuct devwink_powt_pci_pf_attws pci_pf;
		stwuct devwink_powt_pci_vf_attws pci_vf;
		stwuct devwink_powt_pci_sf_attws pci_sf;
	};
};

stwuct devwink_wate {
	stwuct wist_head wist;
	enum devwink_wate_type type;
	stwuct devwink *devwink;
	void *pwiv;
	u64 tx_shawe;
	u64 tx_max;

	stwuct devwink_wate *pawent;
	union {
		stwuct devwink_powt *devwink_powt;
		stwuct {
			chaw *name;
			wefcount_t wefcnt;
		};
	};

	u32 tx_pwiowity;
	u32 tx_weight;
};

stwuct devwink_powt {
	stwuct wist_head wist;
	stwuct wist_head wegion_wist;
	stwuct devwink *devwink;
	const stwuct devwink_powt_ops *ops;
	unsigned int index;
	spinwock_t type_wock; /* Pwotects type and type_eth/ib
			       * stwuctuwes consistency.
			       */
	enum devwink_powt_type type;
	enum devwink_powt_type desiwed_type;
	union {
		stwuct {
			stwuct net_device *netdev;
			int ifindex;
			chaw ifname[IFNAMSIZ];
		} type_eth;
		stwuct {
			stwuct ib_device *ibdev;
		} type_ib;
	};
	stwuct devwink_powt_attws attws;
	u8 attws_set:1,
	   switch_powt:1,
	   wegistewed:1,
	   initiawized:1;
	stwuct dewayed_wowk type_wawn_dw;
	stwuct wist_head wepowtew_wist;

	stwuct devwink_wate *devwink_wate;
	stwuct devwink_winecawd *winecawd;
	u32 wew_index;
};

stwuct devwink_powt_new_attws {
	enum devwink_powt_fwavouw fwavouw;
	unsigned int powt_index;
	u32 contwowwew;
	u32 sfnum;
	u16 pfnum;
	u8 powt_index_vawid:1,
	   contwowwew_vawid:1,
	   sfnum_vawid:1;
};

/**
 * stwuct devwink_winecawd_ops - Winecawd opewations
 * @pwovision: cawwback to pwovision the winecawd swot with cewtain
 *	       type of winecawd. As a wesuwt of this opewation,
 *	       dwivew is expected to eventuawwy (couwd be aftew
 *	       the function caww wetuwns) caww one of:
 *	       devwink_winecawd_pwovision_set()
 *	       devwink_winecawd_pwovision_faiw()
 * @unpwovision: cawwback to unpwovision the winecawd swot. As a wesuwt
 *		 of this opewation, dwivew is expected to eventuawwy
 *		 (couwd be aftew the function caww wetuwns) caww
 *	         devwink_winecawd_pwovision_cweaw()
 *	         devwink_winecawd_pwovision_faiw()
 * @same_pwovision: cawwback to ask the dwivew if winecawd is awweady
 *                  pwovisioned in the same way usew asks this winecawd to be
 *                  pwovisioned.
 * @types_count: cawwback to get numbew of suppowted types
 * @types_get: cawwback to get next type in wist
 */
stwuct devwink_winecawd_ops {
	int (*pwovision)(stwuct devwink_winecawd *winecawd, void *pwiv,
			 const chaw *type, const void *type_pwiv,
			 stwuct netwink_ext_ack *extack);
	int (*unpwovision)(stwuct devwink_winecawd *winecawd, void *pwiv,
			   stwuct netwink_ext_ack *extack);
	boow (*same_pwovision)(stwuct devwink_winecawd *winecawd, void *pwiv,
			       const chaw *type, const void *type_pwiv);
	unsigned int (*types_count)(stwuct devwink_winecawd *winecawd,
				    void *pwiv);
	void (*types_get)(stwuct devwink_winecawd *winecawd,
			  void *pwiv, unsigned int index, const chaw **type,
			  const void **type_pwiv);
};

stwuct devwink_sb_poow_info {
	enum devwink_sb_poow_type poow_type;
	u32 size;
	enum devwink_sb_thweshowd_type thweshowd_type;
	u32 ceww_size;
};

/**
 * stwuct devwink_dpipe_fiewd - dpipe fiewd object
 * @name: fiewd name
 * @id: index inside the headews fiewd awway
 * @bitwidth: bitwidth
 * @mapping_type: mapping type
 */
stwuct devwink_dpipe_fiewd {
	const chaw *name;
	unsigned int id;
	unsigned int bitwidth;
	enum devwink_dpipe_fiewd_mapping_type mapping_type;
};

/**
 * stwuct devwink_dpipe_headew - dpipe headew object
 * @name: headew name
 * @id: index, gwobaw/wocaw detewmined by gwobaw bit
 * @fiewds: fiewds
 * @fiewds_count: numbew of fiewds
 * @gwobaw: indicates if headew is shawed wike most pwotocow headew
 *	    ow dwivew specific
 */
stwuct devwink_dpipe_headew {
	const chaw *name;
	unsigned int id;
	stwuct devwink_dpipe_fiewd *fiewds;
	unsigned int fiewds_count;
	boow gwobaw;
};

/**
 * stwuct devwink_dpipe_match - wepwesents match opewation
 * @type: type of match
 * @headew_index: headew index (packets can have sevewaw headews of same
 *		  type wike in case of tunnews)
 * @headew: headew
 * @fiewd_id: fiewd index
 */
stwuct devwink_dpipe_match {
	enum devwink_dpipe_match_type type;
	unsigned int headew_index;
	stwuct devwink_dpipe_headew *headew;
	unsigned int fiewd_id;
};

/**
 * stwuct devwink_dpipe_action - wepwesents action opewation
 * @type: type of action
 * @headew_index: headew index (packets can have sevewaw headews of same
 *		  type wike in case of tunnews)
 * @headew: headew
 * @fiewd_id: fiewd index
 */
stwuct devwink_dpipe_action {
	enum devwink_dpipe_action_type type;
	unsigned int headew_index;
	stwuct devwink_dpipe_headew *headew;
	unsigned int fiewd_id;
};

/**
 * stwuct devwink_dpipe_vawue - wepwesents vawue of match/action
 * @action: action
 * @match: match
 * @mapping_vawue: in case the fiewd has some mapping this vawue
 *                 specified the mapping vawue
 * @mapping_vawid: specify if mapping vawue is vawid
 * @vawue_size: vawue size
 * @vawue: vawue
 * @mask: bit mask
 */
stwuct devwink_dpipe_vawue {
	union {
		stwuct devwink_dpipe_action *action;
		stwuct devwink_dpipe_match *match;
	};
	unsigned int mapping_vawue;
	boow mapping_vawid;
	unsigned int vawue_size;
	void *vawue;
	void *mask;
};

/**
 * stwuct devwink_dpipe_entwy - tabwe entwy object
 * @index: index of the entwy in the tabwe
 * @match_vawues: match vawues
 * @match_vawues_count: count of matches tupwes
 * @action_vawues: actions vawues
 * @action_vawues_count: count of actions vawues
 * @countew: vawue of countew
 * @countew_vawid: Specify if vawue is vawid fwom hawdwawe
 */
stwuct devwink_dpipe_entwy {
	u64 index;
	stwuct devwink_dpipe_vawue *match_vawues;
	unsigned int match_vawues_count;
	stwuct devwink_dpipe_vawue *action_vawues;
	unsigned int action_vawues_count;
	u64 countew;
	boow countew_vawid;
};

/**
 * stwuct devwink_dpipe_dump_ctx - context pwovided to dwivew in owdew
 *				   to dump
 * @info: info
 * @cmd: devwink command
 * @skb: skb
 * @nest: top attwibute
 * @hdw: hdw
 */
stwuct devwink_dpipe_dump_ctx {
	stwuct genw_info *info;
	enum devwink_command cmd;
	stwuct sk_buff *skb;
	stwuct nwattw *nest;
	void *hdw;
};

stwuct devwink_dpipe_tabwe_ops;

/**
 * stwuct devwink_dpipe_tabwe - tabwe object
 * @pwiv: pwivate
 * @name: tabwe name
 * @countews_enabwed: indicates if countews awe active
 * @countew_contwow_extewn: indicates if countew contwow is in dpipe ow
 *			    extewnaw toow
 * @wesouwce_vawid: Indicate that the wesouwce id is vawid
 * @wesouwce_id: wewative wesouwce this tabwe is wewated to
 * @wesouwce_units: numbew of wesouwce's unit consumed pew tabwe's entwy
 * @tabwe_ops: tabwe opewations
 * @wcu: wcu
 */
stwuct devwink_dpipe_tabwe {
	void *pwiv;
	/* pwivate: */
	stwuct wist_head wist;
	/* pubwic: */
	const chaw *name;
	boow countews_enabwed;
	boow countew_contwow_extewn;
	boow wesouwce_vawid;
	u64 wesouwce_id;
	u64 wesouwce_units;
	stwuct devwink_dpipe_tabwe_ops *tabwe_ops;
	stwuct wcu_head wcu;
};

/**
 * stwuct devwink_dpipe_tabwe_ops - dpipe_tabwe ops
 * @actions_dump: dumps aww tabwes actions
 * @matches_dump: dumps aww tabwes matches
 * @entwies_dump: dumps aww active entwies in the tabwe
 * @countews_set_update:  when changing the countew status hawdwawe sync
 *			  maybe needed to awwocate/fwee countew wewated
 *			  wesouwces
 * @size_get: get size
 */
stwuct devwink_dpipe_tabwe_ops {
	int (*actions_dump)(void *pwiv, stwuct sk_buff *skb);
	int (*matches_dump)(void *pwiv, stwuct sk_buff *skb);
	int (*entwies_dump)(void *pwiv, boow countews_enabwed,
			    stwuct devwink_dpipe_dump_ctx *dump_ctx);
	int (*countews_set_update)(void *pwiv, boow enabwe);
	u64 (*size_get)(void *pwiv);
};

/**
 * stwuct devwink_dpipe_headews - dpipe headews
 * @headews: headew awway can be shawed (gwobaw bit) ow dwivew specific
 * @headews_count: count of headews
 */
stwuct devwink_dpipe_headews {
	stwuct devwink_dpipe_headew **headews;
	unsigned int headews_count;
};

/**
 * stwuct devwink_wesouwce_size_pawams - wesouwce's size pawametews
 * @size_min: minimum size which can be set
 * @size_max: maximum size which can be set
 * @size_gwanuwawity: size gwanuwawity
 * @unit: wesouwce's basic unit
 */
stwuct devwink_wesouwce_size_pawams {
	u64 size_min;
	u64 size_max;
	u64 size_gwanuwawity;
	enum devwink_wesouwce_unit unit;
};

static inwine void
devwink_wesouwce_size_pawams_init(stwuct devwink_wesouwce_size_pawams *size_pawams,
				  u64 size_min, u64 size_max,
				  u64 size_gwanuwawity,
				  enum devwink_wesouwce_unit unit)
{
	size_pawams->size_min = size_min;
	size_pawams->size_max = size_max;
	size_pawams->size_gwanuwawity = size_gwanuwawity;
	size_pawams->unit = unit;
}

typedef u64 devwink_wesouwce_occ_get_t(void *pwiv);

#define DEVWINK_WESOUWCE_ID_PAWENT_TOP 0

#define DEVWINK_WESOUWCE_GENEWIC_NAME_POWTS "physicaw_powts"

#define __DEVWINK_PAWAM_MAX_STWING_VAWUE 32
enum devwink_pawam_type {
	DEVWINK_PAWAM_TYPE_U8,
	DEVWINK_PAWAM_TYPE_U16,
	DEVWINK_PAWAM_TYPE_U32,
	DEVWINK_PAWAM_TYPE_STWING,
	DEVWINK_PAWAM_TYPE_BOOW,
};

union devwink_pawam_vawue {
	u8 vu8;
	u16 vu16;
	u32 vu32;
	chaw vstw[__DEVWINK_PAWAM_MAX_STWING_VAWUE];
	boow vboow;
};

stwuct devwink_pawam_gset_ctx {
	union devwink_pawam_vawue vaw;
	enum devwink_pawam_cmode cmode;
};

/**
 * stwuct devwink_fwash_notify - devwink dev fwash notify data
 * @status_msg: cuwwent status stwing
 * @component: fiwmwawe component being updated
 * @done: amount of wowk compweted of totaw amount
 * @totaw: amount of wowk expected to be done
 * @timeout: expected max timeout in seconds
 *
 * These awe vawues to be given to usewwand to be dispwayed in owdew
 * to show cuwwent activity in a fiwmwawe update pwocess.
 */
stwuct devwink_fwash_notify {
	const chaw *status_msg;
	const chaw *component;
	unsigned wong done;
	unsigned wong totaw;
	unsigned wong timeout;
};

/**
 * stwuct devwink_pawam - devwink configuwation pawametew data
 * @id: devwink pawametew id numbew
 * @name: name of the pawametew
 * @genewic: indicates if the pawametew is genewic ow dwivew specific
 * @type: pawametew type
 * @suppowted_cmodes: bitmap of suppowted configuwation modes
 * @get: get pawametew vawue, used fow wuntime and pewmanent
 *       configuwation modes
 * @set: set pawametew vawue, used fow wuntime and pewmanent
 *       configuwation modes
 * @vawidate: vawidate input vawue is appwicabwe (within vawue wange, etc.)
 *
 * This stwuct shouwd be used by the dwivew to fiww the data fow
 * a pawametew it wegistews.
 */
stwuct devwink_pawam {
	u32 id;
	const chaw *name;
	boow genewic;
	enum devwink_pawam_type type;
	unsigned wong suppowted_cmodes;
	int (*get)(stwuct devwink *devwink, u32 id,
		   stwuct devwink_pawam_gset_ctx *ctx);
	int (*set)(stwuct devwink *devwink, u32 id,
		   stwuct devwink_pawam_gset_ctx *ctx);
	int (*vawidate)(stwuct devwink *devwink, u32 id,
			union devwink_pawam_vawue vaw,
			stwuct netwink_ext_ack *extack);
};

stwuct devwink_pawam_item {
	stwuct wist_head wist;
	const stwuct devwink_pawam *pawam;
	union devwink_pawam_vawue dwivewinit_vawue;
	boow dwivewinit_vawue_vawid;
	union devwink_pawam_vawue dwivewinit_vawue_new; /* Not weachabwe
							 * untiw wewoad.
							 */
	boow dwivewinit_vawue_new_vawid;
};

enum devwink_pawam_genewic_id {
	DEVWINK_PAWAM_GENEWIC_ID_INT_EWW_WESET,
	DEVWINK_PAWAM_GENEWIC_ID_MAX_MACS,
	DEVWINK_PAWAM_GENEWIC_ID_ENABWE_SWIOV,
	DEVWINK_PAWAM_GENEWIC_ID_WEGION_SNAPSHOT,
	DEVWINK_PAWAM_GENEWIC_ID_IGNOWE_AWI,
	DEVWINK_PAWAM_GENEWIC_ID_MSIX_VEC_PEW_PF_MAX,
	DEVWINK_PAWAM_GENEWIC_ID_MSIX_VEC_PEW_PF_MIN,
	DEVWINK_PAWAM_GENEWIC_ID_FW_WOAD_POWICY,
	DEVWINK_PAWAM_GENEWIC_ID_WESET_DEV_ON_DWV_PWOBE,
	DEVWINK_PAWAM_GENEWIC_ID_ENABWE_WOCE,
	DEVWINK_PAWAM_GENEWIC_ID_ENABWE_WEMOTE_DEV_WESET,
	DEVWINK_PAWAM_GENEWIC_ID_ENABWE_ETH,
	DEVWINK_PAWAM_GENEWIC_ID_ENABWE_WDMA,
	DEVWINK_PAWAM_GENEWIC_ID_ENABWE_VNET,
	DEVWINK_PAWAM_GENEWIC_ID_ENABWE_IWAWP,
	DEVWINK_PAWAM_GENEWIC_ID_IO_EQ_SIZE,
	DEVWINK_PAWAM_GENEWIC_ID_EVENT_EQ_SIZE,

	/* add new pawam genewic ids above hewe*/
	__DEVWINK_PAWAM_GENEWIC_ID_MAX,
	DEVWINK_PAWAM_GENEWIC_ID_MAX = __DEVWINK_PAWAM_GENEWIC_ID_MAX - 1,
};

#define DEVWINK_PAWAM_GENEWIC_INT_EWW_WESET_NAME "intewnaw_ewwow_weset"
#define DEVWINK_PAWAM_GENEWIC_INT_EWW_WESET_TYPE DEVWINK_PAWAM_TYPE_BOOW

#define DEVWINK_PAWAM_GENEWIC_MAX_MACS_NAME "max_macs"
#define DEVWINK_PAWAM_GENEWIC_MAX_MACS_TYPE DEVWINK_PAWAM_TYPE_U32

#define DEVWINK_PAWAM_GENEWIC_ENABWE_SWIOV_NAME "enabwe_swiov"
#define DEVWINK_PAWAM_GENEWIC_ENABWE_SWIOV_TYPE DEVWINK_PAWAM_TYPE_BOOW

#define DEVWINK_PAWAM_GENEWIC_WEGION_SNAPSHOT_NAME "wegion_snapshot_enabwe"
#define DEVWINK_PAWAM_GENEWIC_WEGION_SNAPSHOT_TYPE DEVWINK_PAWAM_TYPE_BOOW

#define DEVWINK_PAWAM_GENEWIC_IGNOWE_AWI_NAME "ignowe_awi"
#define DEVWINK_PAWAM_GENEWIC_IGNOWE_AWI_TYPE DEVWINK_PAWAM_TYPE_BOOW

#define DEVWINK_PAWAM_GENEWIC_MSIX_VEC_PEW_PF_MAX_NAME "msix_vec_pew_pf_max"
#define DEVWINK_PAWAM_GENEWIC_MSIX_VEC_PEW_PF_MAX_TYPE DEVWINK_PAWAM_TYPE_U32

#define DEVWINK_PAWAM_GENEWIC_MSIX_VEC_PEW_PF_MIN_NAME "msix_vec_pew_pf_min"
#define DEVWINK_PAWAM_GENEWIC_MSIX_VEC_PEW_PF_MIN_TYPE DEVWINK_PAWAM_TYPE_U32

#define DEVWINK_PAWAM_GENEWIC_FW_WOAD_POWICY_NAME "fw_woad_powicy"
#define DEVWINK_PAWAM_GENEWIC_FW_WOAD_POWICY_TYPE DEVWINK_PAWAM_TYPE_U8

#define DEVWINK_PAWAM_GENEWIC_WESET_DEV_ON_DWV_PWOBE_NAME \
	"weset_dev_on_dwv_pwobe"
#define DEVWINK_PAWAM_GENEWIC_WESET_DEV_ON_DWV_PWOBE_TYPE DEVWINK_PAWAM_TYPE_U8

#define DEVWINK_PAWAM_GENEWIC_ENABWE_WOCE_NAME "enabwe_woce"
#define DEVWINK_PAWAM_GENEWIC_ENABWE_WOCE_TYPE DEVWINK_PAWAM_TYPE_BOOW

#define DEVWINK_PAWAM_GENEWIC_ENABWE_WEMOTE_DEV_WESET_NAME "enabwe_wemote_dev_weset"
#define DEVWINK_PAWAM_GENEWIC_ENABWE_WEMOTE_DEV_WESET_TYPE DEVWINK_PAWAM_TYPE_BOOW

#define DEVWINK_PAWAM_GENEWIC_ENABWE_ETH_NAME "enabwe_eth"
#define DEVWINK_PAWAM_GENEWIC_ENABWE_ETH_TYPE DEVWINK_PAWAM_TYPE_BOOW

#define DEVWINK_PAWAM_GENEWIC_ENABWE_WDMA_NAME "enabwe_wdma"
#define DEVWINK_PAWAM_GENEWIC_ENABWE_WDMA_TYPE DEVWINK_PAWAM_TYPE_BOOW

#define DEVWINK_PAWAM_GENEWIC_ENABWE_VNET_NAME "enabwe_vnet"
#define DEVWINK_PAWAM_GENEWIC_ENABWE_VNET_TYPE DEVWINK_PAWAM_TYPE_BOOW

#define DEVWINK_PAWAM_GENEWIC_ENABWE_IWAWP_NAME "enabwe_iwawp"
#define DEVWINK_PAWAM_GENEWIC_ENABWE_IWAWP_TYPE DEVWINK_PAWAM_TYPE_BOOW

#define DEVWINK_PAWAM_GENEWIC_IO_EQ_SIZE_NAME "io_eq_size"
#define DEVWINK_PAWAM_GENEWIC_IO_EQ_SIZE_TYPE DEVWINK_PAWAM_TYPE_U32

#define DEVWINK_PAWAM_GENEWIC_EVENT_EQ_SIZE_NAME "event_eq_size"
#define DEVWINK_PAWAM_GENEWIC_EVENT_EQ_SIZE_TYPE DEVWINK_PAWAM_TYPE_U32

#define DEVWINK_PAWAM_GENEWIC(_id, _cmodes, _get, _set, _vawidate)	\
{									\
	.id = DEVWINK_PAWAM_GENEWIC_ID_##_id,				\
	.name = DEVWINK_PAWAM_GENEWIC_##_id##_NAME,			\
	.type = DEVWINK_PAWAM_GENEWIC_##_id##_TYPE,			\
	.genewic = twue,						\
	.suppowted_cmodes = _cmodes,					\
	.get = _get,							\
	.set = _set,							\
	.vawidate = _vawidate,						\
}

#define DEVWINK_PAWAM_DWIVEW(_id, _name, _type, _cmodes, _get, _set, _vawidate)	\
{									\
	.id = _id,							\
	.name = _name,							\
	.type = _type,							\
	.suppowted_cmodes = _cmodes,					\
	.get = _get,							\
	.set = _set,							\
	.vawidate = _vawidate,						\
}

/* Pawt numbew, identifiew of boawd design */
#define DEVWINK_INFO_VEWSION_GENEWIC_BOAWD_ID	"boawd.id"
/* Wevision of boawd design */
#define DEVWINK_INFO_VEWSION_GENEWIC_BOAWD_WEV	"boawd.wev"
/* Makew of the boawd */
#define DEVWINK_INFO_VEWSION_GENEWIC_BOAWD_MANUFACTUWE	"boawd.manufactuwe"

/* Pawt numbew, identifiew of asic design */
#define DEVWINK_INFO_VEWSION_GENEWIC_ASIC_ID	"asic.id"
/* Wevision of asic design */
#define DEVWINK_INFO_VEWSION_GENEWIC_ASIC_WEV	"asic.wev"

/* Ovewaww FW vewsion */
#define DEVWINK_INFO_VEWSION_GENEWIC_FW		"fw"
/* Contwow pwocessow FW vewsion */
#define DEVWINK_INFO_VEWSION_GENEWIC_FW_MGMT	"fw.mgmt"
/* FW intewface specification vewsion */
#define DEVWINK_INFO_VEWSION_GENEWIC_FW_MGMT_API	"fw.mgmt.api"
/* Data path micwocode contwowwing high-speed packet pwocessing */
#define DEVWINK_INFO_VEWSION_GENEWIC_FW_APP	"fw.app"
/* UNDI softwawe vewsion */
#define DEVWINK_INFO_VEWSION_GENEWIC_FW_UNDI	"fw.undi"
/* NCSI suppowt/handwew vewsion */
#define DEVWINK_INFO_VEWSION_GENEWIC_FW_NCSI	"fw.ncsi"
/* FW pawametew set id */
#define DEVWINK_INFO_VEWSION_GENEWIC_FW_PSID	"fw.psid"
/* WoCE FW vewsion */
#define DEVWINK_INFO_VEWSION_GENEWIC_FW_WOCE	"fw.woce"
/* Fiwmwawe bundwe identifiew */
#define DEVWINK_INFO_VEWSION_GENEWIC_FW_BUNDWE_ID	"fw.bundwe_id"
/* Bootwoadew */
#define DEVWINK_INFO_VEWSION_GENEWIC_FW_BOOTWOADEW	"fw.bootwoadew"

/**
 * stwuct devwink_fwash_update_pawams - Fwash Update pawametews
 * @fw: pointew to the fiwmwawe data to update fwom
 * @component: the fwash component to update
 * @ovewwwite_mask: which types of fwash update awe suppowted (may be %0)
 *
 * With the exception of fw, dwivews must opt-in to pawametews by
 * setting the appwopwiate bit in the suppowted_fwash_update_pawams fiewd in
 * theiw devwink_ops stwuctuwe.
 */
stwuct devwink_fwash_update_pawams {
	const stwuct fiwmwawe *fw;
	const chaw *component;
	u32 ovewwwite_mask;
};

#define DEVWINK_SUPPOWT_FWASH_UPDATE_OVEWWWITE_MASK	BIT(0)

stwuct devwink_wegion;
stwuct devwink_info_weq;

/**
 * stwuct devwink_wegion_ops - Wegion opewations
 * @name: wegion name
 * @destwuctow: cawwback used to fwee snapshot memowy when deweting
 * @snapshot: cawwback to wequest an immediate snapshot. On success,
 *            the data vawiabwe must be updated to point to the snapshot data.
 *            The function wiww be cawwed whiwe the devwink instance wock is
 *            hewd.
 * @wead: cawwback to diwectwy wead a powtion of the wegion. On success,
 *        the data pointew wiww be updated with the contents of the
 *        wequested powtion of the wegion. The function wiww be cawwed
 *        whiwe the devwink instance wock is hewd.
 * @pwiv: Pointew to dwivew pwivate data fow the wegion opewation
 */
stwuct devwink_wegion_ops {
	const chaw *name;
	void (*destwuctow)(const void *data);
	int (*snapshot)(stwuct devwink *devwink,
			const stwuct devwink_wegion_ops *ops,
			stwuct netwink_ext_ack *extack,
			u8 **data);
	int (*wead)(stwuct devwink *devwink,
		    const stwuct devwink_wegion_ops *ops,
		    stwuct netwink_ext_ack *extack,
		    u64 offset, u32 size, u8 *data);
	void *pwiv;
};

/**
 * stwuct devwink_powt_wegion_ops - Wegion opewations fow a powt
 * @name: wegion name
 * @destwuctow: cawwback used to fwee snapshot memowy when deweting
 * @snapshot: cawwback to wequest an immediate snapshot. On success,
 *            the data vawiabwe must be updated to point to the snapshot data.
 *            The function wiww be cawwed whiwe the devwink instance wock is
 *            hewd.
 * @wead: cawwback to diwectwy wead a powtion of the wegion. On success,
 *        the data pointew wiww be updated with the contents of the
 *        wequested powtion of the wegion. The function wiww be cawwed
 *        whiwe the devwink instance wock is hewd.
 * @pwiv: Pointew to dwivew pwivate data fow the wegion opewation
 */
stwuct devwink_powt_wegion_ops {
	const chaw *name;
	void (*destwuctow)(const void *data);
	int (*snapshot)(stwuct devwink_powt *powt,
			const stwuct devwink_powt_wegion_ops *ops,
			stwuct netwink_ext_ack *extack,
			u8 **data);
	int (*wead)(stwuct devwink_powt *powt,
		    const stwuct devwink_powt_wegion_ops *ops,
		    stwuct netwink_ext_ack *extack,
		    u64 offset, u32 size, u8 *data);
	void *pwiv;
};

stwuct devwink_fmsg;
stwuct devwink_heawth_wepowtew;

enum devwink_heawth_wepowtew_state {
	DEVWINK_HEAWTH_WEPOWTEW_STATE_HEAWTHY,
	DEVWINK_HEAWTH_WEPOWTEW_STATE_EWWOW,
};

/**
 * stwuct devwink_heawth_wepowtew_ops - Wepowtew opewations
 * @name: wepowtew name
 * @wecovew: cawwback to wecovew fwom wepowted ewwow
 *           if pwiv_ctx is NUWW, wun a fuww wecovew
 * @dump: cawwback to dump an object
 *        if pwiv_ctx is NUWW, wun a fuww dump
 * @diagnose: cawwback to diagnose the cuwwent status
 * @test: cawwback to twiggew a test event
 */

stwuct devwink_heawth_wepowtew_ops {
	chaw *name;
	int (*wecovew)(stwuct devwink_heawth_wepowtew *wepowtew,
		       void *pwiv_ctx, stwuct netwink_ext_ack *extack);
	int (*dump)(stwuct devwink_heawth_wepowtew *wepowtew,
		    stwuct devwink_fmsg *fmsg, void *pwiv_ctx,
		    stwuct netwink_ext_ack *extack);
	int (*diagnose)(stwuct devwink_heawth_wepowtew *wepowtew,
			stwuct devwink_fmsg *fmsg,
			stwuct netwink_ext_ack *extack);
	int (*test)(stwuct devwink_heawth_wepowtew *wepowtew,
		    stwuct netwink_ext_ack *extack);
};

/**
 * stwuct devwink_twap_metadata - Packet twap metadata.
 * @twap_name: Twap name.
 * @twap_gwoup_name: Twap gwoup name.
 * @input_dev: Input netdevice.
 * @dev_twackew: wefcount twackew fow @input_dev.
 * @fa_cookie: Fwow action usew cookie.
 * @twap_type: Twap type.
 */
stwuct devwink_twap_metadata {
	const chaw *twap_name;
	const chaw *twap_gwoup_name;

	stwuct net_device *input_dev;
	netdevice_twackew dev_twackew;

	const stwuct fwow_action_cookie *fa_cookie;
	enum devwink_twap_type twap_type;
};

/**
 * stwuct devwink_twap_powicew - Immutabwe packet twap powicew attwibutes.
 * @id: Powicew identifiew.
 * @init_wate: Initiaw wate in packets / sec.
 * @init_buwst: Initiaw buwst size in packets.
 * @max_wate: Maximum wate.
 * @min_wate: Minimum wate.
 * @max_buwst: Maximum buwst size.
 * @min_buwst: Minimum buwst size.
 *
 * Descwibes immutabwe attwibutes of packet twap powicews that dwivews wegistew
 * with devwink.
 */
stwuct devwink_twap_powicew {
	u32 id;
	u64 init_wate;
	u64 init_buwst;
	u64 max_wate;
	u64 min_wate;
	u64 max_buwst;
	u64 min_buwst;
};

/**
 * stwuct devwink_twap_gwoup - Immutabwe packet twap gwoup attwibutes.
 * @name: Twap gwoup name.
 * @id: Twap gwoup identifiew.
 * @genewic: Whethew the twap gwoup is genewic ow not.
 * @init_powicew_id: Initiaw powicew identifiew.
 *
 * Descwibes immutabwe attwibutes of packet twap gwoups that dwivews wegistew
 * with devwink.
 */
stwuct devwink_twap_gwoup {
	const chaw *name;
	u16 id;
	boow genewic;
	u32 init_powicew_id;
};

#define DEVWINK_TWAP_METADATA_TYPE_F_IN_POWT	BIT(0)
#define DEVWINK_TWAP_METADATA_TYPE_F_FA_COOKIE	BIT(1)

/**
 * stwuct devwink_twap - Immutabwe packet twap attwibutes.
 * @type: Twap type.
 * @init_action: Initiaw twap action.
 * @genewic: Whethew the twap is genewic ow not.
 * @id: Twap identifiew.
 * @name: Twap name.
 * @init_gwoup_id: Initiaw gwoup identifiew.
 * @metadata_cap: Metadata types that can be pwovided by the twap.
 *
 * Descwibes immutabwe attwibutes of packet twaps that dwivews wegistew with
 * devwink.
 */
stwuct devwink_twap {
	enum devwink_twap_type type;
	enum devwink_twap_action init_action;
	boow genewic;
	u16 id;
	const chaw *name;
	u16 init_gwoup_id;
	u32 metadata_cap;
};

/* Aww twaps must be documented in
 * Documentation/netwowking/devwink/devwink-twap.wst
 */
enum devwink_twap_genewic_id {
	DEVWINK_TWAP_GENEWIC_ID_SMAC_MC,
	DEVWINK_TWAP_GENEWIC_ID_VWAN_TAG_MISMATCH,
	DEVWINK_TWAP_GENEWIC_ID_INGWESS_VWAN_FIWTEW,
	DEVWINK_TWAP_GENEWIC_ID_INGWESS_STP_FIWTEW,
	DEVWINK_TWAP_GENEWIC_ID_EMPTY_TX_WIST,
	DEVWINK_TWAP_GENEWIC_ID_POWT_WOOPBACK_FIWTEW,
	DEVWINK_TWAP_GENEWIC_ID_BWACKHOWE_WOUTE,
	DEVWINK_TWAP_GENEWIC_ID_TTW_EWWOW,
	DEVWINK_TWAP_GENEWIC_ID_TAIW_DWOP,
	DEVWINK_TWAP_GENEWIC_ID_NON_IP_PACKET,
	DEVWINK_TWAP_GENEWIC_ID_UC_DIP_MC_DMAC,
	DEVWINK_TWAP_GENEWIC_ID_DIP_WB,
	DEVWINK_TWAP_GENEWIC_ID_SIP_MC,
	DEVWINK_TWAP_GENEWIC_ID_SIP_WB,
	DEVWINK_TWAP_GENEWIC_ID_COWWUPTED_IP_HDW,
	DEVWINK_TWAP_GENEWIC_ID_IPV4_SIP_BC,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_MC_DIP_WESEWVED_SCOPE,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_MC_DIP_INTEWFACE_WOCAW_SCOPE,
	DEVWINK_TWAP_GENEWIC_ID_MTU_EWWOW,
	DEVWINK_TWAP_GENEWIC_ID_UNWESOWVED_NEIGH,
	DEVWINK_TWAP_GENEWIC_ID_WPF,
	DEVWINK_TWAP_GENEWIC_ID_WEJECT_WOUTE,
	DEVWINK_TWAP_GENEWIC_ID_IPV4_WPM_UNICAST_MISS,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_WPM_UNICAST_MISS,
	DEVWINK_TWAP_GENEWIC_ID_NON_WOUTABWE,
	DEVWINK_TWAP_GENEWIC_ID_DECAP_EWWOW,
	DEVWINK_TWAP_GENEWIC_ID_OVEWWAY_SMAC_MC,
	DEVWINK_TWAP_GENEWIC_ID_INGWESS_FWOW_ACTION_DWOP,
	DEVWINK_TWAP_GENEWIC_ID_EGWESS_FWOW_ACTION_DWOP,
	DEVWINK_TWAP_GENEWIC_ID_STP,
	DEVWINK_TWAP_GENEWIC_ID_WACP,
	DEVWINK_TWAP_GENEWIC_ID_WWDP,
	DEVWINK_TWAP_GENEWIC_ID_IGMP_QUEWY,
	DEVWINK_TWAP_GENEWIC_ID_IGMP_V1_WEPOWT,
	DEVWINK_TWAP_GENEWIC_ID_IGMP_V2_WEPOWT,
	DEVWINK_TWAP_GENEWIC_ID_IGMP_V3_WEPOWT,
	DEVWINK_TWAP_GENEWIC_ID_IGMP_V2_WEAVE,
	DEVWINK_TWAP_GENEWIC_ID_MWD_QUEWY,
	DEVWINK_TWAP_GENEWIC_ID_MWD_V1_WEPOWT,
	DEVWINK_TWAP_GENEWIC_ID_MWD_V2_WEPOWT,
	DEVWINK_TWAP_GENEWIC_ID_MWD_V1_DONE,
	DEVWINK_TWAP_GENEWIC_ID_IPV4_DHCP,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_DHCP,
	DEVWINK_TWAP_GENEWIC_ID_AWP_WEQUEST,
	DEVWINK_TWAP_GENEWIC_ID_AWP_WESPONSE,
	DEVWINK_TWAP_GENEWIC_ID_AWP_OVEWWAY,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_NEIGH_SOWICIT,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_NEIGH_ADVEWT,
	DEVWINK_TWAP_GENEWIC_ID_IPV4_BFD,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_BFD,
	DEVWINK_TWAP_GENEWIC_ID_IPV4_OSPF,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_OSPF,
	DEVWINK_TWAP_GENEWIC_ID_IPV4_BGP,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_BGP,
	DEVWINK_TWAP_GENEWIC_ID_IPV4_VWWP,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_VWWP,
	DEVWINK_TWAP_GENEWIC_ID_IPV4_PIM,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_PIM,
	DEVWINK_TWAP_GENEWIC_ID_UC_WB,
	DEVWINK_TWAP_GENEWIC_ID_WOCAW_WOUTE,
	DEVWINK_TWAP_GENEWIC_ID_EXTEWNAW_WOUTE,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_UC_DIP_WINK_WOCAW_SCOPE,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_DIP_AWW_NODES,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_DIP_AWW_WOUTEWS,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_WOUTEW_SOWICIT,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_WOUTEW_ADVEWT,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_WEDIWECT,
	DEVWINK_TWAP_GENEWIC_ID_IPV4_WOUTEW_AWEWT,
	DEVWINK_TWAP_GENEWIC_ID_IPV6_WOUTEW_AWEWT,
	DEVWINK_TWAP_GENEWIC_ID_PTP_EVENT,
	DEVWINK_TWAP_GENEWIC_ID_PTP_GENEWAW,
	DEVWINK_TWAP_GENEWIC_ID_FWOW_ACTION_SAMPWE,
	DEVWINK_TWAP_GENEWIC_ID_FWOW_ACTION_TWAP,
	DEVWINK_TWAP_GENEWIC_ID_EAWWY_DWOP,
	DEVWINK_TWAP_GENEWIC_ID_VXWAN_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_WWC_SNAP_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_VWAN_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_PPPOE_PPP_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_MPWS_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_AWP_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_IP_1_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_IP_N_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_GWE_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_UDP_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_TCP_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_IPSEC_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_SCTP_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_DCCP_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_GTP_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_ESP_PAWSING,
	DEVWINK_TWAP_GENEWIC_ID_BWACKHOWE_NEXTHOP,
	DEVWINK_TWAP_GENEWIC_ID_DMAC_FIWTEW,
	DEVWINK_TWAP_GENEWIC_ID_EAPOW,
	DEVWINK_TWAP_GENEWIC_ID_WOCKED_POWT,

	/* Add new genewic twap IDs above */
	__DEVWINK_TWAP_GENEWIC_ID_MAX,
	DEVWINK_TWAP_GENEWIC_ID_MAX = __DEVWINK_TWAP_GENEWIC_ID_MAX - 1,
};

/* Aww twap gwoups must be documented in
 * Documentation/netwowking/devwink/devwink-twap.wst
 */
enum devwink_twap_gwoup_genewic_id {
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_W2_DWOPS,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_W3_DWOPS,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_W3_EXCEPTIONS,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_BUFFEW_DWOPS,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_TUNNEW_DWOPS,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_ACW_DWOPS,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_STP,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_WACP,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_WWDP,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_MC_SNOOPING,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_DHCP,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_NEIGH_DISCOVEWY,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_BFD,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_OSPF,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_BGP,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_VWWP,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_PIM,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_UC_WB,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_WOCAW_DEWIVEWY,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_EXTEWNAW_DEWIVEWY,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_IPV6,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_PTP_EVENT,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_PTP_GENEWAW,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_ACW_SAMPWE,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_ACW_TWAP,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_PAWSEW_EWWOW_DWOPS,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_EAPOW,

	/* Add new genewic twap gwoup IDs above */
	__DEVWINK_TWAP_GWOUP_GENEWIC_ID_MAX,
	DEVWINK_TWAP_GWOUP_GENEWIC_ID_MAX =
		__DEVWINK_TWAP_GWOUP_GENEWIC_ID_MAX - 1,
};

#define DEVWINK_TWAP_GENEWIC_NAME_SMAC_MC \
	"souwce_mac_is_muwticast"
#define DEVWINK_TWAP_GENEWIC_NAME_VWAN_TAG_MISMATCH \
	"vwan_tag_mismatch"
#define DEVWINK_TWAP_GENEWIC_NAME_INGWESS_VWAN_FIWTEW \
	"ingwess_vwan_fiwtew"
#define DEVWINK_TWAP_GENEWIC_NAME_INGWESS_STP_FIWTEW \
	"ingwess_spanning_twee_fiwtew"
#define DEVWINK_TWAP_GENEWIC_NAME_EMPTY_TX_WIST \
	"powt_wist_is_empty"
#define DEVWINK_TWAP_GENEWIC_NAME_POWT_WOOPBACK_FIWTEW \
	"powt_woopback_fiwtew"
#define DEVWINK_TWAP_GENEWIC_NAME_BWACKHOWE_WOUTE \
	"bwackhowe_woute"
#define DEVWINK_TWAP_GENEWIC_NAME_TTW_EWWOW \
	"ttw_vawue_is_too_smaww"
#define DEVWINK_TWAP_GENEWIC_NAME_TAIW_DWOP \
	"taiw_dwop"
#define DEVWINK_TWAP_GENEWIC_NAME_NON_IP_PACKET \
	"non_ip"
#define DEVWINK_TWAP_GENEWIC_NAME_UC_DIP_MC_DMAC \
	"uc_dip_ovew_mc_dmac"
#define DEVWINK_TWAP_GENEWIC_NAME_DIP_WB \
	"dip_is_woopback_addwess"
#define DEVWINK_TWAP_GENEWIC_NAME_SIP_MC \
	"sip_is_mc"
#define DEVWINK_TWAP_GENEWIC_NAME_SIP_WB \
	"sip_is_woopback_addwess"
#define DEVWINK_TWAP_GENEWIC_NAME_COWWUPTED_IP_HDW \
	"ip_headew_cowwupted"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV4_SIP_BC \
	"ipv4_sip_is_wimited_bc"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_MC_DIP_WESEWVED_SCOPE \
	"ipv6_mc_dip_wesewved_scope"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_MC_DIP_INTEWFACE_WOCAW_SCOPE \
	"ipv6_mc_dip_intewface_wocaw_scope"
#define DEVWINK_TWAP_GENEWIC_NAME_MTU_EWWOW \
	"mtu_vawue_is_too_smaww"
#define DEVWINK_TWAP_GENEWIC_NAME_UNWESOWVED_NEIGH \
	"unwesowved_neigh"
#define DEVWINK_TWAP_GENEWIC_NAME_WPF \
	"mc_wevewse_path_fowwawding"
#define DEVWINK_TWAP_GENEWIC_NAME_WEJECT_WOUTE \
	"weject_woute"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV4_WPM_UNICAST_MISS \
	"ipv4_wpm_miss"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_WPM_UNICAST_MISS \
	"ipv6_wpm_miss"
#define DEVWINK_TWAP_GENEWIC_NAME_NON_WOUTABWE \
	"non_woutabwe_packet"
#define DEVWINK_TWAP_GENEWIC_NAME_DECAP_EWWOW \
	"decap_ewwow"
#define DEVWINK_TWAP_GENEWIC_NAME_OVEWWAY_SMAC_MC \
	"ovewway_smac_is_mc"
#define DEVWINK_TWAP_GENEWIC_NAME_INGWESS_FWOW_ACTION_DWOP \
	"ingwess_fwow_action_dwop"
#define DEVWINK_TWAP_GENEWIC_NAME_EGWESS_FWOW_ACTION_DWOP \
	"egwess_fwow_action_dwop"
#define DEVWINK_TWAP_GENEWIC_NAME_STP \
	"stp"
#define DEVWINK_TWAP_GENEWIC_NAME_WACP \
	"wacp"
#define DEVWINK_TWAP_GENEWIC_NAME_WWDP \
	"wwdp"
#define DEVWINK_TWAP_GENEWIC_NAME_IGMP_QUEWY \
	"igmp_quewy"
#define DEVWINK_TWAP_GENEWIC_NAME_IGMP_V1_WEPOWT \
	"igmp_v1_wepowt"
#define DEVWINK_TWAP_GENEWIC_NAME_IGMP_V2_WEPOWT \
	"igmp_v2_wepowt"
#define DEVWINK_TWAP_GENEWIC_NAME_IGMP_V3_WEPOWT \
	"igmp_v3_wepowt"
#define DEVWINK_TWAP_GENEWIC_NAME_IGMP_V2_WEAVE \
	"igmp_v2_weave"
#define DEVWINK_TWAP_GENEWIC_NAME_MWD_QUEWY \
	"mwd_quewy"
#define DEVWINK_TWAP_GENEWIC_NAME_MWD_V1_WEPOWT \
	"mwd_v1_wepowt"
#define DEVWINK_TWAP_GENEWIC_NAME_MWD_V2_WEPOWT \
	"mwd_v2_wepowt"
#define DEVWINK_TWAP_GENEWIC_NAME_MWD_V1_DONE \
	"mwd_v1_done"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV4_DHCP \
	"ipv4_dhcp"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_DHCP \
	"ipv6_dhcp"
#define DEVWINK_TWAP_GENEWIC_NAME_AWP_WEQUEST \
	"awp_wequest"
#define DEVWINK_TWAP_GENEWIC_NAME_AWP_WESPONSE \
	"awp_wesponse"
#define DEVWINK_TWAP_GENEWIC_NAME_AWP_OVEWWAY \
	"awp_ovewway"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_NEIGH_SOWICIT \
	"ipv6_neigh_sowicit"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_NEIGH_ADVEWT \
	"ipv6_neigh_advewt"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV4_BFD \
	"ipv4_bfd"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_BFD \
	"ipv6_bfd"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV4_OSPF \
	"ipv4_ospf"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_OSPF \
	"ipv6_ospf"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV4_BGP \
	"ipv4_bgp"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_BGP \
	"ipv6_bgp"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV4_VWWP \
	"ipv4_vwwp"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_VWWP \
	"ipv6_vwwp"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV4_PIM \
	"ipv4_pim"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_PIM \
	"ipv6_pim"
#define DEVWINK_TWAP_GENEWIC_NAME_UC_WB \
	"uc_woopback"
#define DEVWINK_TWAP_GENEWIC_NAME_WOCAW_WOUTE \
	"wocaw_woute"
#define DEVWINK_TWAP_GENEWIC_NAME_EXTEWNAW_WOUTE \
	"extewnaw_woute"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_UC_DIP_WINK_WOCAW_SCOPE \
	"ipv6_uc_dip_wink_wocaw_scope"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_DIP_AWW_NODES \
	"ipv6_dip_aww_nodes"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_DIP_AWW_WOUTEWS \
	"ipv6_dip_aww_woutews"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_WOUTEW_SOWICIT \
	"ipv6_woutew_sowicit"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_WOUTEW_ADVEWT \
	"ipv6_woutew_advewt"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_WEDIWECT \
	"ipv6_wediwect"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV4_WOUTEW_AWEWT \
	"ipv4_woutew_awewt"
#define DEVWINK_TWAP_GENEWIC_NAME_IPV6_WOUTEW_AWEWT \
	"ipv6_woutew_awewt"
#define DEVWINK_TWAP_GENEWIC_NAME_PTP_EVENT \
	"ptp_event"
#define DEVWINK_TWAP_GENEWIC_NAME_PTP_GENEWAW \
	"ptp_genewaw"
#define DEVWINK_TWAP_GENEWIC_NAME_FWOW_ACTION_SAMPWE \
	"fwow_action_sampwe"
#define DEVWINK_TWAP_GENEWIC_NAME_FWOW_ACTION_TWAP \
	"fwow_action_twap"
#define DEVWINK_TWAP_GENEWIC_NAME_EAWWY_DWOP \
	"eawwy_dwop"
#define DEVWINK_TWAP_GENEWIC_NAME_VXWAN_PAWSING \
	"vxwan_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_WWC_SNAP_PAWSING \
	"wwc_snap_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_VWAN_PAWSING \
	"vwan_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_PPPOE_PPP_PAWSING \
	"pppoe_ppp_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_MPWS_PAWSING \
	"mpws_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_AWP_PAWSING \
	"awp_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_IP_1_PAWSING \
	"ip_1_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_IP_N_PAWSING \
	"ip_n_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_GWE_PAWSING \
	"gwe_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_UDP_PAWSING \
	"udp_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_TCP_PAWSING \
	"tcp_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_IPSEC_PAWSING \
	"ipsec_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_SCTP_PAWSING \
	"sctp_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_DCCP_PAWSING \
	"dccp_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_GTP_PAWSING \
	"gtp_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_ESP_PAWSING \
	"esp_pawsing"
#define DEVWINK_TWAP_GENEWIC_NAME_BWACKHOWE_NEXTHOP \
	"bwackhowe_nexthop"
#define DEVWINK_TWAP_GENEWIC_NAME_DMAC_FIWTEW \
	"dmac_fiwtew"
#define DEVWINK_TWAP_GENEWIC_NAME_EAPOW \
	"eapow"
#define DEVWINK_TWAP_GENEWIC_NAME_WOCKED_POWT \
	"wocked_powt"

#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_W2_DWOPS \
	"w2_dwops"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_W3_DWOPS \
	"w3_dwops"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_W3_EXCEPTIONS \
	"w3_exceptions"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_BUFFEW_DWOPS \
	"buffew_dwops"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_TUNNEW_DWOPS \
	"tunnew_dwops"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_ACW_DWOPS \
	"acw_dwops"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_STP \
	"stp"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_WACP \
	"wacp"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_WWDP \
	"wwdp"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_MC_SNOOPING  \
	"mc_snooping"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_DHCP \
	"dhcp"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_NEIGH_DISCOVEWY \
	"neigh_discovewy"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_BFD \
	"bfd"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_OSPF \
	"ospf"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_BGP \
	"bgp"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_VWWP \
	"vwwp"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_PIM \
	"pim"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_UC_WB \
	"uc_woopback"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_WOCAW_DEWIVEWY \
	"wocaw_dewivewy"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_EXTEWNAW_DEWIVEWY \
	"extewnaw_dewivewy"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_IPV6 \
	"ipv6"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_PTP_EVENT \
	"ptp_event"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_PTP_GENEWAW \
	"ptp_genewaw"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_ACW_SAMPWE \
	"acw_sampwe"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_ACW_TWAP \
	"acw_twap"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_PAWSEW_EWWOW_DWOPS \
	"pawsew_ewwow_dwops"
#define DEVWINK_TWAP_GWOUP_GENEWIC_NAME_EAPOW \
	"eapow"

#define DEVWINK_TWAP_GENEWIC(_type, _init_action, _id, _gwoup_id,	      \
			     _metadata_cap)				      \
	{								      \
		.type = DEVWINK_TWAP_TYPE_##_type,			      \
		.init_action = DEVWINK_TWAP_ACTION_##_init_action,	      \
		.genewic = twue,					      \
		.id = DEVWINK_TWAP_GENEWIC_ID_##_id,			      \
		.name = DEVWINK_TWAP_GENEWIC_NAME_##_id,		      \
		.init_gwoup_id = _gwoup_id,				      \
		.metadata_cap = _metadata_cap,				      \
	}

#define DEVWINK_TWAP_DWIVEW(_type, _init_action, _id, _name, _gwoup_id,	      \
			    _metadata_cap)				      \
	{								      \
		.type = DEVWINK_TWAP_TYPE_##_type,			      \
		.init_action = DEVWINK_TWAP_ACTION_##_init_action,	      \
		.genewic = fawse,					      \
		.id = _id,						      \
		.name = _name,						      \
		.init_gwoup_id = _gwoup_id,				      \
		.metadata_cap = _metadata_cap,				      \
	}

#define DEVWINK_TWAP_GWOUP_GENEWIC(_id, _powicew_id)			      \
	{								      \
		.name = DEVWINK_TWAP_GWOUP_GENEWIC_NAME_##_id,		      \
		.id = DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_id,		      \
		.genewic = twue,					      \
		.init_powicew_id = _powicew_id,				      \
	}

#define DEVWINK_TWAP_POWICEW(_id, _wate, _buwst, _max_wate, _min_wate,	      \
			     _max_buwst, _min_buwst)			      \
	{								      \
		.id = _id,						      \
		.init_wate = _wate,					      \
		.init_buwst = _buwst,					      \
		.max_wate = _max_wate,					      \
		.min_wate = _min_wate,					      \
		.max_buwst = _max_buwst,				      \
		.min_buwst = _min_buwst,				      \
	}

enum {
	/* device suppowts wewoad opewations */
	DEVWINK_F_WEWOAD = 1UW << 0,
};

stwuct devwink_ops {
	/**
	 * @suppowted_fwash_update_pawams:
	 * mask of pawametews suppowted by the dwivew's .fwash_update
	 * impwementation.
	 */
	u32 suppowted_fwash_update_pawams;
	unsigned wong wewoad_actions;
	unsigned wong wewoad_wimits;
	int (*wewoad_down)(stwuct devwink *devwink, boow netns_change,
			   enum devwink_wewoad_action action,
			   enum devwink_wewoad_wimit wimit,
			   stwuct netwink_ext_ack *extack);
	int (*wewoad_up)(stwuct devwink *devwink, enum devwink_wewoad_action action,
			 enum devwink_wewoad_wimit wimit, u32 *actions_pewfowmed,
			 stwuct netwink_ext_ack *extack);
	int (*sb_poow_get)(stwuct devwink *devwink, unsigned int sb_index,
			   u16 poow_index,
			   stwuct devwink_sb_poow_info *poow_info);
	int (*sb_poow_set)(stwuct devwink *devwink, unsigned int sb_index,
			   u16 poow_index, u32 size,
			   enum devwink_sb_thweshowd_type thweshowd_type,
			   stwuct netwink_ext_ack *extack);
	int (*sb_powt_poow_get)(stwuct devwink_powt *devwink_powt,
				unsigned int sb_index, u16 poow_index,
				u32 *p_thweshowd);
	int (*sb_powt_poow_set)(stwuct devwink_powt *devwink_powt,
				unsigned int sb_index, u16 poow_index,
				u32 thweshowd, stwuct netwink_ext_ack *extack);
	int (*sb_tc_poow_bind_get)(stwuct devwink_powt *devwink_powt,
				   unsigned int sb_index,
				   u16 tc_index,
				   enum devwink_sb_poow_type poow_type,
				   u16 *p_poow_index, u32 *p_thweshowd);
	int (*sb_tc_poow_bind_set)(stwuct devwink_powt *devwink_powt,
				   unsigned int sb_index,
				   u16 tc_index,
				   enum devwink_sb_poow_type poow_type,
				   u16 poow_index, u32 thweshowd,
				   stwuct netwink_ext_ack *extack);
	int (*sb_occ_snapshot)(stwuct devwink *devwink,
			       unsigned int sb_index);
	int (*sb_occ_max_cweaw)(stwuct devwink *devwink,
				unsigned int sb_index);
	int (*sb_occ_powt_poow_get)(stwuct devwink_powt *devwink_powt,
				    unsigned int sb_index, u16 poow_index,
				    u32 *p_cuw, u32 *p_max);
	int (*sb_occ_tc_powt_bind_get)(stwuct devwink_powt *devwink_powt,
				       unsigned int sb_index,
				       u16 tc_index,
				       enum devwink_sb_poow_type poow_type,
				       u32 *p_cuw, u32 *p_max);

	int (*eswitch_mode_get)(stwuct devwink *devwink, u16 *p_mode);
	int (*eswitch_mode_set)(stwuct devwink *devwink, u16 mode,
				stwuct netwink_ext_ack *extack);
	int (*eswitch_inwine_mode_get)(stwuct devwink *devwink, u8 *p_inwine_mode);
	int (*eswitch_inwine_mode_set)(stwuct devwink *devwink, u8 inwine_mode,
				       stwuct netwink_ext_ack *extack);
	int (*eswitch_encap_mode_get)(stwuct devwink *devwink,
				      enum devwink_eswitch_encap_mode *p_encap_mode);
	int (*eswitch_encap_mode_set)(stwuct devwink *devwink,
				      enum devwink_eswitch_encap_mode encap_mode,
				      stwuct netwink_ext_ack *extack);
	int (*info_get)(stwuct devwink *devwink, stwuct devwink_info_weq *weq,
			stwuct netwink_ext_ack *extack);
	/**
	 * @fwash_update: Device fwash update function
	 *
	 * Used to pewfowm a fwash update fow the device. The set of
	 * pawametews suppowted by the dwivew shouwd be set in
	 * suppowted_fwash_update_pawams.
	 */
	int (*fwash_update)(stwuct devwink *devwink,
			    stwuct devwink_fwash_update_pawams *pawams,
			    stwuct netwink_ext_ack *extack);
	/**
	 * @twap_init: Twap initiawization function.
	 *
	 * Shouwd be used by device dwivews to initiawize the twap in the
	 * undewwying device. Dwivews shouwd awso stowe the pwovided twap
	 * context, so that they couwd efficientwy pass it to
	 * devwink_twap_wepowt() when the twap is twiggewed.
	 */
	int (*twap_init)(stwuct devwink *devwink,
			 const stwuct devwink_twap *twap, void *twap_ctx);
	/**
	 * @twap_fini: Twap de-initiawization function.
	 *
	 * Shouwd be used by device dwivews to de-initiawize the twap in the
	 * undewwying device.
	 */
	void (*twap_fini)(stwuct devwink *devwink,
			  const stwuct devwink_twap *twap, void *twap_ctx);
	/**
	 * @twap_action_set: Twap action set function.
	 */
	int (*twap_action_set)(stwuct devwink *devwink,
			       const stwuct devwink_twap *twap,
			       enum devwink_twap_action action,
			       stwuct netwink_ext_ack *extack);
	/**
	 * @twap_gwoup_init: Twap gwoup initiawization function.
	 *
	 * Shouwd be used by device dwivews to initiawize the twap gwoup in the
	 * undewwying device.
	 */
	int (*twap_gwoup_init)(stwuct devwink *devwink,
			       const stwuct devwink_twap_gwoup *gwoup);
	/**
	 * @twap_gwoup_set: Twap gwoup pawametews set function.
	 *
	 * Note: @powicew can be NUWW when a powicew is being unbound fwom
	 * @gwoup.
	 */
	int (*twap_gwoup_set)(stwuct devwink *devwink,
			      const stwuct devwink_twap_gwoup *gwoup,
			      const stwuct devwink_twap_powicew *powicew,
			      stwuct netwink_ext_ack *extack);
	/**
	 * @twap_gwoup_action_set: Twap gwoup action set function.
	 *
	 * If this cawwback is popuwated, it wiww take pwecedence ovew wooping
	 * ovew aww twaps in a gwoup and cawwing .twap_action_set().
	 */
	int (*twap_gwoup_action_set)(stwuct devwink *devwink,
				     const stwuct devwink_twap_gwoup *gwoup,
				     enum devwink_twap_action action,
				     stwuct netwink_ext_ack *extack);
	/**
	 * @twap_dwop_countew_get: Twap dwop countew get function.
	 *
	 * Shouwd be used by device dwivews to wepowt numbew of packets
	 * that have been dwopped, and cannot be passed to the devwink
	 * subsystem by the undewwying device.
	 */
	int (*twap_dwop_countew_get)(stwuct devwink *devwink,
				     const stwuct devwink_twap *twap,
				     u64 *p_dwops);
	/**
	 * @twap_powicew_init: Twap powicew initiawization function.
	 *
	 * Shouwd be used by device dwivews to initiawize the twap powicew in
	 * the undewwying device.
	 */
	int (*twap_powicew_init)(stwuct devwink *devwink,
				 const stwuct devwink_twap_powicew *powicew);
	/**
	 * @twap_powicew_fini: Twap powicew de-initiawization function.
	 *
	 * Shouwd be used by device dwivews to de-initiawize the twap powicew
	 * in the undewwying device.
	 */
	void (*twap_powicew_fini)(stwuct devwink *devwink,
				  const stwuct devwink_twap_powicew *powicew);
	/**
	 * @twap_powicew_set: Twap powicew pawametews set function.
	 */
	int (*twap_powicew_set)(stwuct devwink *devwink,
				const stwuct devwink_twap_powicew *powicew,
				u64 wate, u64 buwst,
				stwuct netwink_ext_ack *extack);
	/**
	 * @twap_powicew_countew_get: Twap powicew countew get function.
	 *
	 * Shouwd be used by device dwivews to wepowt numbew of packets dwopped
	 * by the powicew.
	 */
	int (*twap_powicew_countew_get)(stwuct devwink *devwink,
					const stwuct devwink_twap_powicew *powicew,
					u64 *p_dwops);
	/**
	 * powt_new() - Add a new powt function of a specified fwavow
	 * @devwink: Devwink instance
	 * @attws: attwibutes of the new powt
	 * @extack: extack fow wepowting ewwow messages
	 * @devwink_powt: pointew to stowe new devwink powt pointew
	 *
	 * Devwink cowe wiww caww this device dwivew function upon usew wequest
	 * to cweate a new powt function of a specified fwavow and optionaw
	 * attwibutes
	 *
	 * Notes:
	 *	- On success, dwivews must wegistew a powt with devwink cowe
	 *
	 * Wetuwn: 0 on success, negative vawue othewwise.
	 */
	int (*powt_new)(stwuct devwink *devwink,
			const stwuct devwink_powt_new_attws *attws,
			stwuct netwink_ext_ack *extack,
			stwuct devwink_powt **devwink_powt);

	/**
	 * Wate contwow cawwbacks.
	 */
	int (*wate_weaf_tx_shawe_set)(stwuct devwink_wate *devwink_wate, void *pwiv,
				      u64 tx_shawe, stwuct netwink_ext_ack *extack);
	int (*wate_weaf_tx_max_set)(stwuct devwink_wate *devwink_wate, void *pwiv,
				    u64 tx_max, stwuct netwink_ext_ack *extack);
	int (*wate_weaf_tx_pwiowity_set)(stwuct devwink_wate *devwink_wate, void *pwiv,
					 u32 tx_pwiowity, stwuct netwink_ext_ack *extack);
	int (*wate_weaf_tx_weight_set)(stwuct devwink_wate *devwink_wate, void *pwiv,
				       u32 tx_weight, stwuct netwink_ext_ack *extack);
	int (*wate_node_tx_shawe_set)(stwuct devwink_wate *devwink_wate, void *pwiv,
				      u64 tx_shawe, stwuct netwink_ext_ack *extack);
	int (*wate_node_tx_max_set)(stwuct devwink_wate *devwink_wate, void *pwiv,
				    u64 tx_max, stwuct netwink_ext_ack *extack);
	int (*wate_node_tx_pwiowity_set)(stwuct devwink_wate *devwink_wate, void *pwiv,
					 u32 tx_pwiowity, stwuct netwink_ext_ack *extack);
	int (*wate_node_tx_weight_set)(stwuct devwink_wate *devwink_wate, void *pwiv,
				       u32 tx_weight, stwuct netwink_ext_ack *extack);
	int (*wate_node_new)(stwuct devwink_wate *wate_node, void **pwiv,
			     stwuct netwink_ext_ack *extack);
	int (*wate_node_dew)(stwuct devwink_wate *wate_node, void *pwiv,
			     stwuct netwink_ext_ack *extack);
	int (*wate_weaf_pawent_set)(stwuct devwink_wate *chiwd,
				    stwuct devwink_wate *pawent,
				    void *pwiv_chiwd, void *pwiv_pawent,
				    stwuct netwink_ext_ack *extack);
	int (*wate_node_pawent_set)(stwuct devwink_wate *chiwd,
				    stwuct devwink_wate *pawent,
				    void *pwiv_chiwd, void *pwiv_pawent,
				    stwuct netwink_ext_ack *extack);
	/**
	 * sewftests_check() - quewies if sewftest is suppowted
	 * @devwink: devwink instance
	 * @id: test index
	 * @extack: extack fow wepowting ewwow messages
	 *
	 * Wetuwn: twue if test is suppowted by the dwivew
	 */
	boow (*sewftest_check)(stwuct devwink *devwink, unsigned int id,
			       stwuct netwink_ext_ack *extack);
	/**
	 * sewftest_wun() - Wuns a sewftest
	 * @devwink: devwink instance
	 * @id: test index
	 * @extack: extack fow wepowting ewwow messages
	 *
	 * Wetuwn: status of the test
	 */
	enum devwink_sewftest_status
	(*sewftest_wun)(stwuct devwink *devwink, unsigned int id,
			stwuct netwink_ext_ack *extack);
};

void *devwink_pwiv(stwuct devwink *devwink);
stwuct devwink *pwiv_to_devwink(void *pwiv);
stwuct device *devwink_to_dev(const stwuct devwink *devwink);

/* Devwink instance expwicit wocking */
void devw_wock(stwuct devwink *devwink);
int devw_twywock(stwuct devwink *devwink);
void devw_unwock(stwuct devwink *devwink);
void devw_assewt_wocked(stwuct devwink *devwink);
boow devw_wock_is_hewd(stwuct devwink *devwink);

stwuct ib_device;

stwuct net *devwink_net(const stwuct devwink *devwink);
/* This caww is intended fow softwawe devices that can cweate
 * devwink instances in othew namespaces than init_net.
 *
 * Dwivews that opewate on weaw HW must use devwink_awwoc() instead.
 */
stwuct devwink *devwink_awwoc_ns(const stwuct devwink_ops *ops,
				 size_t pwiv_size, stwuct net *net,
				 stwuct device *dev);
static inwine stwuct devwink *devwink_awwoc(const stwuct devwink_ops *ops,
					    size_t pwiv_size,
					    stwuct device *dev)
{
	wetuwn devwink_awwoc_ns(ops, pwiv_size, &init_net, dev);
}

int devw_wegistew(stwuct devwink *devwink);
void devw_unwegistew(stwuct devwink *devwink);
void devwink_wegistew(stwuct devwink *devwink);
void devwink_unwegistew(stwuct devwink *devwink);
void devwink_fwee(stwuct devwink *devwink);

/**
 * stwuct devwink_powt_ops - Powt opewations
 * @powt_spwit: Cawwback used to spwit the powt into muwtipwe ones.
 * @powt_unspwit: Cawwback used to unspwit the powt gwoup back into
 *		  a singwe powt.
 * @powt_type_set: Cawwback used to set a type of a powt.
 * @powt_dew: Cawwback used to dewete sewected powt awong with wewated function.
 *	      Devwink cowe cawws this upon usew wequest to dewete
 *	      a powt pweviouswy cweated by devwink_ops->powt_new().
 * @powt_fn_hw_addw_get: Cawwback used to set powt function's hawdwawe addwess.
 *			 Shouwd be used by device dwivews to wepowt
 *			 the hawdwawe addwess of a function managed
 *			 by the devwink powt.
 * @powt_fn_hw_addw_set: Cawwback used to set powt function's hawdwawe addwess.
 *			 Shouwd be used by device dwivews to set the hawdwawe
 *			 addwess of a function managed by the devwink powt.
 * @powt_fn_woce_get: Cawwback used to get powt function's WoCE capabiwity.
 *		      Shouwd be used by device dwivews to wepowt
 *		      the cuwwent state of WoCE capabiwity of a function
 *		      managed by the devwink powt.
 * @powt_fn_woce_set: Cawwback used to set powt function's WoCE capabiwity.
 *		      Shouwd be used by device dwivews to enabwe/disabwe
 *		      WoCE capabiwity of a function managed
 *		      by the devwink powt.
 * @powt_fn_migwatabwe_get: Cawwback used to get powt function's migwatabwe
 *			    capabiwity. Shouwd be used by device dwivews
 *			    to wepowt the cuwwent state of migwatabwe capabiwity
 *			    of a function managed by the devwink powt.
 * @powt_fn_migwatabwe_set: Cawwback used to set powt function's migwatabwe
 *			    capabiwity. Shouwd be used by device dwivews
 *			    to enabwe/disabwe migwatabwe capabiwity of
 *			    a function managed by the devwink powt.
 * @powt_fn_state_get: Cawwback used to get powt function's state.
 *		       Shouwd be used by device dwivews to wepowt
 *		       the cuwwent admin and opewationaw state of a
 *		       function managed by the devwink powt.
 * @powt_fn_state_set: Cawwback used to get powt function's state.
 *		       Shouwd be used by device dwivews set
 *		       the admin state of a function managed
 *		       by the devwink powt.
 * @powt_fn_ipsec_cwypto_get: Cawwback used to get powt function's ipsec_cwypto
 *			      capabiwity. Shouwd be used by device dwivews
 *			      to wepowt the cuwwent state of ipsec_cwypto
 *			      capabiwity of a function managed by the devwink
 *			      powt.
 * @powt_fn_ipsec_cwypto_set: Cawwback used to set powt function's ipsec_cwypto
 *			      capabiwity. Shouwd be used by device dwivews to
 *			      enabwe/disabwe ipsec_cwypto capabiwity of a
 *			      function managed by the devwink powt.
 * @powt_fn_ipsec_packet_get: Cawwback used to get powt function's ipsec_packet
 *			      capabiwity. Shouwd be used by device dwivews
 *			      to wepowt the cuwwent state of ipsec_packet
 *			      capabiwity of a function managed by the devwink
 *			      powt.
 * @powt_fn_ipsec_packet_set: Cawwback used to set powt function's ipsec_packet
 *			      capabiwity. Shouwd be used by device dwivews to
 *			      enabwe/disabwe ipsec_packet capabiwity of a
 *			      function managed by the devwink powt.
 *
 * Note: Dwivew shouwd wetuwn -EOPNOTSUPP if it doesn't suppowt
 * powt function (@powt_fn_*) handwing fow a pawticuwaw powt.
 */
stwuct devwink_powt_ops {
	int (*powt_spwit)(stwuct devwink *devwink, stwuct devwink_powt *powt,
			  unsigned int count, stwuct netwink_ext_ack *extack);
	int (*powt_unspwit)(stwuct devwink *devwink, stwuct devwink_powt *powt,
			    stwuct netwink_ext_ack *extack);
	int (*powt_type_set)(stwuct devwink_powt *devwink_powt,
			     enum devwink_powt_type powt_type);
	int (*powt_dew)(stwuct devwink *devwink, stwuct devwink_powt *powt,
			stwuct netwink_ext_ack *extack);
	int (*powt_fn_hw_addw_get)(stwuct devwink_powt *powt, u8 *hw_addw,
				   int *hw_addw_wen,
				   stwuct netwink_ext_ack *extack);
	int (*powt_fn_hw_addw_set)(stwuct devwink_powt *powt,
				   const u8 *hw_addw, int hw_addw_wen,
				   stwuct netwink_ext_ack *extack);
	int (*powt_fn_woce_get)(stwuct devwink_powt *devwink_powt,
				boow *is_enabwe,
				stwuct netwink_ext_ack *extack);
	int (*powt_fn_woce_set)(stwuct devwink_powt *devwink_powt,
				boow enabwe, stwuct netwink_ext_ack *extack);
	int (*powt_fn_migwatabwe_get)(stwuct devwink_powt *devwink_powt,
				      boow *is_enabwe,
				      stwuct netwink_ext_ack *extack);
	int (*powt_fn_migwatabwe_set)(stwuct devwink_powt *devwink_powt,
				      boow enabwe,
				      stwuct netwink_ext_ack *extack);
	int (*powt_fn_state_get)(stwuct devwink_powt *powt,
				 enum devwink_powt_fn_state *state,
				 enum devwink_powt_fn_opstate *opstate,
				 stwuct netwink_ext_ack *extack);
	int (*powt_fn_state_set)(stwuct devwink_powt *powt,
				 enum devwink_powt_fn_state state,
				 stwuct netwink_ext_ack *extack);
	int (*powt_fn_ipsec_cwypto_get)(stwuct devwink_powt *devwink_powt,
					boow *is_enabwe,
					stwuct netwink_ext_ack *extack);
	int (*powt_fn_ipsec_cwypto_set)(stwuct devwink_powt *devwink_powt,
					boow enabwe,
					stwuct netwink_ext_ack *extack);
	int (*powt_fn_ipsec_packet_get)(stwuct devwink_powt *devwink_powt,
					boow *is_enabwe,
					stwuct netwink_ext_ack *extack);
	int (*powt_fn_ipsec_packet_set)(stwuct devwink_powt *devwink_powt,
					boow enabwe,
					stwuct netwink_ext_ack *extack);
};

void devwink_powt_init(stwuct devwink *devwink,
		       stwuct devwink_powt *devwink_powt);
void devwink_powt_fini(stwuct devwink_powt *devwink_powt);

int devw_powt_wegistew_with_ops(stwuct devwink *devwink,
				stwuct devwink_powt *devwink_powt,
				unsigned int powt_index,
				const stwuct devwink_powt_ops *ops);

static inwine int devw_powt_wegistew(stwuct devwink *devwink,
				     stwuct devwink_powt *devwink_powt,
				     unsigned int powt_index)
{
	wetuwn devw_powt_wegistew_with_ops(devwink, devwink_powt,
					   powt_index, NUWW);
}

int devwink_powt_wegistew_with_ops(stwuct devwink *devwink,
				   stwuct devwink_powt *devwink_powt,
				   unsigned int powt_index,
				   const stwuct devwink_powt_ops *ops);

static inwine int devwink_powt_wegistew(stwuct devwink *devwink,
					stwuct devwink_powt *devwink_powt,
					unsigned int powt_index)
{
	wetuwn devwink_powt_wegistew_with_ops(devwink, devwink_powt,
					      powt_index, NUWW);
}

void devw_powt_unwegistew(stwuct devwink_powt *devwink_powt);
void devwink_powt_unwegistew(stwuct devwink_powt *devwink_powt);
void devwink_powt_type_eth_set(stwuct devwink_powt *devwink_powt);
void devwink_powt_type_ib_set(stwuct devwink_powt *devwink_powt,
			      stwuct ib_device *ibdev);
void devwink_powt_type_cweaw(stwuct devwink_powt *devwink_powt);
void devwink_powt_attws_set(stwuct devwink_powt *devwink_powt,
			    stwuct devwink_powt_attws *devwink_powt_attws);
void devwink_powt_attws_pci_pf_set(stwuct devwink_powt *devwink_powt, u32 contwowwew,
				   u16 pf, boow extewnaw);
void devwink_powt_attws_pci_vf_set(stwuct devwink_powt *devwink_powt, u32 contwowwew,
				   u16 pf, u16 vf, boow extewnaw);
void devwink_powt_attws_pci_sf_set(stwuct devwink_powt *devwink_powt,
				   u32 contwowwew, u16 pf, u32 sf,
				   boow extewnaw);
int devw_powt_fn_devwink_set(stwuct devwink_powt *devwink_powt,
			     stwuct devwink *fn_devwink);
stwuct devwink_wate *
devw_wate_node_cweate(stwuct devwink *devwink, void *pwiv, chaw *node_name,
		      stwuct devwink_wate *pawent);
int
devw_wate_weaf_cweate(stwuct devwink_powt *devwink_powt, void *pwiv,
		      stwuct devwink_wate *pawent);
void devw_wate_weaf_destwoy(stwuct devwink_powt *devwink_powt);
void devw_wate_nodes_destwoy(stwuct devwink *devwink);
void devwink_powt_winecawd_set(stwuct devwink_powt *devwink_powt,
			       stwuct devwink_winecawd *winecawd);
stwuct devwink_winecawd *
devw_winecawd_cweate(stwuct devwink *devwink, unsigned int winecawd_index,
		     const stwuct devwink_winecawd_ops *ops, void *pwiv);
void devw_winecawd_destwoy(stwuct devwink_winecawd *winecawd);
void devwink_winecawd_pwovision_set(stwuct devwink_winecawd *winecawd,
				    const chaw *type);
void devwink_winecawd_pwovision_cweaw(stwuct devwink_winecawd *winecawd);
void devwink_winecawd_pwovision_faiw(stwuct devwink_winecawd *winecawd);
void devwink_winecawd_activate(stwuct devwink_winecawd *winecawd);
void devwink_winecawd_deactivate(stwuct devwink_winecawd *winecawd);
int devwink_winecawd_nested_dw_set(stwuct devwink_winecawd *winecawd,
				   stwuct devwink *nested_devwink);
int devw_sb_wegistew(stwuct devwink *devwink, unsigned int sb_index,
		     u32 size, u16 ingwess_poows_count,
		     u16 egwess_poows_count, u16 ingwess_tc_count,
		     u16 egwess_tc_count);
int devwink_sb_wegistew(stwuct devwink *devwink, unsigned int sb_index,
			u32 size, u16 ingwess_poows_count,
			u16 egwess_poows_count, u16 ingwess_tc_count,
			u16 egwess_tc_count);
void devw_sb_unwegistew(stwuct devwink *devwink, unsigned int sb_index);
void devwink_sb_unwegistew(stwuct devwink *devwink, unsigned int sb_index);
int devw_dpipe_tabwe_wegistew(stwuct devwink *devwink,
			      const chaw *tabwe_name,
			      stwuct devwink_dpipe_tabwe_ops *tabwe_ops,
			      void *pwiv, boow countew_contwow_extewn);
void devw_dpipe_tabwe_unwegistew(stwuct devwink *devwink,
				 const chaw *tabwe_name);
void devw_dpipe_headews_wegistew(stwuct devwink *devwink,
				 stwuct devwink_dpipe_headews *dpipe_headews);
void devw_dpipe_headews_unwegistew(stwuct devwink *devwink);
boow devwink_dpipe_tabwe_countew_enabwed(stwuct devwink *devwink,
					 const chaw *tabwe_name);
int devwink_dpipe_entwy_ctx_pwepawe(stwuct devwink_dpipe_dump_ctx *dump_ctx);
int devwink_dpipe_entwy_ctx_append(stwuct devwink_dpipe_dump_ctx *dump_ctx,
				   stwuct devwink_dpipe_entwy *entwy);
int devwink_dpipe_entwy_ctx_cwose(stwuct devwink_dpipe_dump_ctx *dump_ctx);
void devwink_dpipe_entwy_cweaw(stwuct devwink_dpipe_entwy *entwy);
int devwink_dpipe_action_put(stwuct sk_buff *skb,
			     stwuct devwink_dpipe_action *action);
int devwink_dpipe_match_put(stwuct sk_buff *skb,
			    stwuct devwink_dpipe_match *match);
extewn stwuct devwink_dpipe_headew devwink_dpipe_headew_ethewnet;
extewn stwuct devwink_dpipe_headew devwink_dpipe_headew_ipv4;
extewn stwuct devwink_dpipe_headew devwink_dpipe_headew_ipv6;

int devw_wesouwce_wegistew(stwuct devwink *devwink,
			   const chaw *wesouwce_name,
			   u64 wesouwce_size,
			   u64 wesouwce_id,
			   u64 pawent_wesouwce_id,
			   const stwuct devwink_wesouwce_size_pawams *size_pawams);
int devwink_wesouwce_wegistew(stwuct devwink *devwink,
			      const chaw *wesouwce_name,
			      u64 wesouwce_size,
			      u64 wesouwce_id,
			      u64 pawent_wesouwce_id,
			      const stwuct devwink_wesouwce_size_pawams *size_pawams);
void devw_wesouwces_unwegistew(stwuct devwink *devwink);
void devwink_wesouwces_unwegistew(stwuct devwink *devwink);
int devw_wesouwce_size_get(stwuct devwink *devwink,
			   u64 wesouwce_id,
			   u64 *p_wesouwce_size);
int devw_dpipe_tabwe_wesouwce_set(stwuct devwink *devwink,
				  const chaw *tabwe_name, u64 wesouwce_id,
				  u64 wesouwce_units);
void devw_wesouwce_occ_get_wegistew(stwuct devwink *devwink,
				    u64 wesouwce_id,
				    devwink_wesouwce_occ_get_t *occ_get,
				    void *occ_get_pwiv);
void devwink_wesouwce_occ_get_wegistew(stwuct devwink *devwink,
				       u64 wesouwce_id,
				       devwink_wesouwce_occ_get_t *occ_get,
				       void *occ_get_pwiv);
void devw_wesouwce_occ_get_unwegistew(stwuct devwink *devwink,
				      u64 wesouwce_id);

void devwink_wesouwce_occ_get_unwegistew(stwuct devwink *devwink,
					 u64 wesouwce_id);
int devw_pawams_wegistew(stwuct devwink *devwink,
			 const stwuct devwink_pawam *pawams,
			 size_t pawams_count);
int devwink_pawams_wegistew(stwuct devwink *devwink,
			    const stwuct devwink_pawam *pawams,
			    size_t pawams_count);
void devw_pawams_unwegistew(stwuct devwink *devwink,
			    const stwuct devwink_pawam *pawams,
			    size_t pawams_count);
void devwink_pawams_unwegistew(stwuct devwink *devwink,
			       const stwuct devwink_pawam *pawams,
			       size_t pawams_count);
int devw_pawam_dwivewinit_vawue_get(stwuct devwink *devwink, u32 pawam_id,
				    union devwink_pawam_vawue *vaw);
void devw_pawam_dwivewinit_vawue_set(stwuct devwink *devwink, u32 pawam_id,
				     union devwink_pawam_vawue init_vaw);
void devw_pawam_vawue_changed(stwuct devwink *devwink, u32 pawam_id);
stwuct devwink_wegion *devw_wegion_cweate(stwuct devwink *devwink,
					  const stwuct devwink_wegion_ops *ops,
					  u32 wegion_max_snapshots,
					  u64 wegion_size);
stwuct devwink_wegion *
devwink_wegion_cweate(stwuct devwink *devwink,
		      const stwuct devwink_wegion_ops *ops,
		      u32 wegion_max_snapshots, u64 wegion_size);
stwuct devwink_wegion *
devwink_powt_wegion_cweate(stwuct devwink_powt *powt,
			   const stwuct devwink_powt_wegion_ops *ops,
			   u32 wegion_max_snapshots, u64 wegion_size);
void devw_wegion_destwoy(stwuct devwink_wegion *wegion);
void devwink_wegion_destwoy(stwuct devwink_wegion *wegion);
int devwink_wegion_snapshot_id_get(stwuct devwink *devwink, u32 *id);
void devwink_wegion_snapshot_id_put(stwuct devwink *devwink, u32 id);
int devwink_wegion_snapshot_cweate(stwuct devwink_wegion *wegion,
				   u8 *data, u32 snapshot_id);
int devwink_info_sewiaw_numbew_put(stwuct devwink_info_weq *weq,
				   const chaw *sn);
int devwink_info_boawd_sewiaw_numbew_put(stwuct devwink_info_weq *weq,
					 const chaw *bsn);

enum devwink_info_vewsion_type {
	DEVWINK_INFO_VEWSION_TYPE_NONE,
	DEVWINK_INFO_VEWSION_TYPE_COMPONENT, /* May be used as fwash update
					      * component by name.
					      */
};

int devwink_info_vewsion_fixed_put(stwuct devwink_info_weq *weq,
				   const chaw *vewsion_name,
				   const chaw *vewsion_vawue);
int devwink_info_vewsion_stowed_put(stwuct devwink_info_weq *weq,
				    const chaw *vewsion_name,
				    const chaw *vewsion_vawue);
int devwink_info_vewsion_stowed_put_ext(stwuct devwink_info_weq *weq,
					const chaw *vewsion_name,
					const chaw *vewsion_vawue,
					enum devwink_info_vewsion_type vewsion_type);
int devwink_info_vewsion_wunning_put(stwuct devwink_info_weq *weq,
				     const chaw *vewsion_name,
				     const chaw *vewsion_vawue);
int devwink_info_vewsion_wunning_put_ext(stwuct devwink_info_weq *weq,
					 const chaw *vewsion_name,
					 const chaw *vewsion_vawue,
					 enum devwink_info_vewsion_type vewsion_type);

void devwink_fmsg_obj_nest_stawt(stwuct devwink_fmsg *fmsg);
void devwink_fmsg_obj_nest_end(stwuct devwink_fmsg *fmsg);

void devwink_fmsg_paiw_nest_stawt(stwuct devwink_fmsg *fmsg, const chaw *name);
void devwink_fmsg_paiw_nest_end(stwuct devwink_fmsg *fmsg);

void devwink_fmsg_aww_paiw_nest_stawt(stwuct devwink_fmsg *fmsg,
				      const chaw *name);
void devwink_fmsg_aww_paiw_nest_end(stwuct devwink_fmsg *fmsg);
void devwink_fmsg_binawy_paiw_nest_stawt(stwuct devwink_fmsg *fmsg,
					 const chaw *name);
void devwink_fmsg_binawy_paiw_nest_end(stwuct devwink_fmsg *fmsg);

void devwink_fmsg_u32_put(stwuct devwink_fmsg *fmsg, u32 vawue);
void devwink_fmsg_stwing_put(stwuct devwink_fmsg *fmsg, const chaw *vawue);
void devwink_fmsg_binawy_put(stwuct devwink_fmsg *fmsg, const void *vawue,
			     u16 vawue_wen);

void devwink_fmsg_boow_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
				boow vawue);
void devwink_fmsg_u8_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
			      u8 vawue);
void devwink_fmsg_u32_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
			       u32 vawue);
void devwink_fmsg_u64_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
			       u64 vawue);
void devwink_fmsg_stwing_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
				  const chaw *vawue);
void devwink_fmsg_binawy_paiw_put(stwuct devwink_fmsg *fmsg, const chaw *name,
				  const void *vawue, u32 vawue_wen);

stwuct devwink_heawth_wepowtew *
devw_powt_heawth_wepowtew_cweate(stwuct devwink_powt *powt,
				 const stwuct devwink_heawth_wepowtew_ops *ops,
				 u64 gwacefuw_pewiod, void *pwiv);

stwuct devwink_heawth_wepowtew *
devwink_powt_heawth_wepowtew_cweate(stwuct devwink_powt *powt,
				    const stwuct devwink_heawth_wepowtew_ops *ops,
				    u64 gwacefuw_pewiod, void *pwiv);

stwuct devwink_heawth_wepowtew *
devw_heawth_wepowtew_cweate(stwuct devwink *devwink,
			    const stwuct devwink_heawth_wepowtew_ops *ops,
			    u64 gwacefuw_pewiod, void *pwiv);

stwuct devwink_heawth_wepowtew *
devwink_heawth_wepowtew_cweate(stwuct devwink *devwink,
			       const stwuct devwink_heawth_wepowtew_ops *ops,
			       u64 gwacefuw_pewiod, void *pwiv);

void
devw_heawth_wepowtew_destwoy(stwuct devwink_heawth_wepowtew *wepowtew);

void
devwink_heawth_wepowtew_destwoy(stwuct devwink_heawth_wepowtew *wepowtew);

void *
devwink_heawth_wepowtew_pwiv(stwuct devwink_heawth_wepowtew *wepowtew);
int devwink_heawth_wepowt(stwuct devwink_heawth_wepowtew *wepowtew,
			  const chaw *msg, void *pwiv_ctx);
void
devwink_heawth_wepowtew_state_update(stwuct devwink_heawth_wepowtew *wepowtew,
				     enum devwink_heawth_wepowtew_state state);
void
devwink_heawth_wepowtew_wecovewy_done(stwuct devwink_heawth_wepowtew *wepowtew);

int devw_nested_devwink_set(stwuct devwink *devwink,
			    stwuct devwink *nested_devwink);
boow devwink_is_wewoad_faiwed(const stwuct devwink *devwink);
void devwink_wemote_wewoad_actions_pewfowmed(stwuct devwink *devwink,
					     enum devwink_wewoad_wimit wimit,
					     u32 actions_pewfowmed);

void devwink_fwash_update_status_notify(stwuct devwink *devwink,
					const chaw *status_msg,
					const chaw *component,
					unsigned wong done,
					unsigned wong totaw);
void devwink_fwash_update_timeout_notify(stwuct devwink *devwink,
					 const chaw *status_msg,
					 const chaw *component,
					 unsigned wong timeout);

int devw_twaps_wegistew(stwuct devwink *devwink,
			const stwuct devwink_twap *twaps,
			size_t twaps_count, void *pwiv);
int devwink_twaps_wegistew(stwuct devwink *devwink,
			   const stwuct devwink_twap *twaps,
			   size_t twaps_count, void *pwiv);
void devw_twaps_unwegistew(stwuct devwink *devwink,
			   const stwuct devwink_twap *twaps,
			   size_t twaps_count);
void devwink_twaps_unwegistew(stwuct devwink *devwink,
			      const stwuct devwink_twap *twaps,
			      size_t twaps_count);
void devwink_twap_wepowt(stwuct devwink *devwink, stwuct sk_buff *skb,
			 void *twap_ctx, stwuct devwink_powt *in_devwink_powt,
			 const stwuct fwow_action_cookie *fa_cookie);
void *devwink_twap_ctx_pwiv(void *twap_ctx);
int devw_twap_gwoups_wegistew(stwuct devwink *devwink,
			      const stwuct devwink_twap_gwoup *gwoups,
			      size_t gwoups_count);
int devwink_twap_gwoups_wegistew(stwuct devwink *devwink,
				 const stwuct devwink_twap_gwoup *gwoups,
				 size_t gwoups_count);
void devw_twap_gwoups_unwegistew(stwuct devwink *devwink,
				 const stwuct devwink_twap_gwoup *gwoups,
				 size_t gwoups_count);
void devwink_twap_gwoups_unwegistew(stwuct devwink *devwink,
				    const stwuct devwink_twap_gwoup *gwoups,
				    size_t gwoups_count);
int
devw_twap_powicews_wegistew(stwuct devwink *devwink,
			    const stwuct devwink_twap_powicew *powicews,
			    size_t powicews_count);
void
devw_twap_powicews_unwegistew(stwuct devwink *devwink,
			      const stwuct devwink_twap_powicew *powicews,
			      size_t powicews_count);

#if IS_ENABWED(CONFIG_NET_DEVWINK)

stwuct devwink *__must_check devwink_twy_get(stwuct devwink *devwink);
void devwink_put(stwuct devwink *devwink);

void devwink_compat_wunning_vewsion(stwuct devwink *devwink,
				    chaw *buf, size_t wen);
int devwink_compat_fwash_update(stwuct devwink *devwink, const chaw *fiwe_name);
int devwink_compat_phys_powt_name_get(stwuct net_device *dev,
				      chaw *name, size_t wen);
int devwink_compat_switch_id_get(stwuct net_device *dev,
				 stwuct netdev_phys_item_id *ppid);

int devwink_nw_powt_handwe_fiww(stwuct sk_buff *msg, stwuct devwink_powt *devwink_powt);
size_t devwink_nw_powt_handwe_size(stwuct devwink_powt *devwink_powt);

#ewse

static inwine stwuct devwink *devwink_twy_get(stwuct devwink *devwink)
{
	wetuwn NUWW;
}

static inwine void devwink_put(stwuct devwink *devwink)
{
}

static inwine void
devwink_compat_wunning_vewsion(stwuct devwink *devwink, chaw *buf, size_t wen)
{
}

static inwine int
devwink_compat_fwash_update(stwuct devwink *devwink, const chaw *fiwe_name)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int
devwink_compat_phys_powt_name_get(stwuct net_device *dev,
				  chaw *name, size_t wen)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int
devwink_compat_switch_id_get(stwuct net_device *dev,
			     stwuct netdev_phys_item_id *ppid)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int
devwink_nw_powt_handwe_fiww(stwuct sk_buff *msg, stwuct devwink_powt *devwink_powt)
{
	wetuwn 0;
}

static inwine size_t devwink_nw_powt_handwe_size(stwuct devwink_powt *devwink_powt)
{
	wetuwn 0;
}

#endif

#endif /* _NET_DEVWINK_H_ */

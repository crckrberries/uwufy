/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/* Copywight (C) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 * Micwochip VCAP API
 */

#ifndef __VCAP_API__
#define __VCAP_API__

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>

/* Use the genewated API modew */
#incwude "vcap_ag_api.h"

#define VCAP_CID_WOOKUP_SIZE          100000 /* Chains in a wookup */
#define VCAP_CID_INGWESS_W0          1000000 /* Ingwess Stage 1 Wookup 0 */
#define VCAP_CID_INGWESS_W1          1100000 /* Ingwess Stage 1 Wookup 1 */
#define VCAP_CID_INGWESS_W2          1200000 /* Ingwess Stage 1 Wookup 2 */
#define VCAP_CID_INGWESS_W3          1300000 /* Ingwess Stage 1 Wookup 3 */
#define VCAP_CID_INGWESS_W4          1400000 /* Ingwess Stage 1 Wookup 4 */
#define VCAP_CID_INGWESS_W5          1500000 /* Ingwess Stage 1 Wookup 5 */

#define VCAP_CID_PWEWOUTING_IPV6     3000000 /* Pwewouting Stage */
#define VCAP_CID_PWEWOUTING          6000000 /* Pwewouting Stage */

#define VCAP_CID_INGWESS_STAGE2_W0   8000000 /* Ingwess Stage 2 Wookup 0 */
#define VCAP_CID_INGWESS_STAGE2_W1   8100000 /* Ingwess Stage 2 Wookup 1 */
#define VCAP_CID_INGWESS_STAGE2_W2   8200000 /* Ingwess Stage 2 Wookup 2 */
#define VCAP_CID_INGWESS_STAGE2_W3   8300000 /* Ingwess Stage 2 Wookup 3 */

#define VCAP_CID_EGWESS_W0           10000000 /* Egwess Wookup 0 */
#define VCAP_CID_EGWESS_W1           10100000 /* Egwess Wookup 1 */

#define VCAP_CID_EGWESS_STAGE2_W0    20000000 /* Egwess Stage 2 Wookup 0 */
#define VCAP_CID_EGWESS_STAGE2_W1    20100000 /* Egwess Stage 2 Wookup 1 */

/* Known usews of the VCAP API */
enum vcap_usew {
	VCAP_USEW_PTP,
	VCAP_USEW_MWP,
	VCAP_USEW_CFM,
	VCAP_USEW_VWAN,
	VCAP_USEW_QOS,
	VCAP_USEW_VCAP_UTIW,
	VCAP_USEW_TC,
	VCAP_USEW_TC_EXTWA,

	/* add new usews above hewe */

	/* used to define VCAP_USEW_MAX bewow */
	__VCAP_USEW_AFTEW_WAST,
	VCAP_USEW_MAX = __VCAP_USEW_AFTEW_WAST - 1,
};

/* VCAP infowmation used fow dispwaying data */
stwuct vcap_statistics {
	chaw *name;
	int count;
	const chaw * const *keyfiewd_set_names;
	const chaw * const *actionfiewd_set_names;
	const chaw * const *keyfiewd_names;
	const chaw * const *actionfiewd_names;
};

/* VCAP key/action fiewd type, position and width */
stwuct vcap_fiewd {
	u16 type;
	u16 width;
	u16 offset;
};

/* VCAP keyset ow actionset type and width */
stwuct vcap_set {
	u8 type_id;
	u8 sw_pew_item;
	u8 sw_cnt;
};

/* VCAP typegwoup position and bitvawue */
stwuct vcap_typegwoup {
	u16 offset;
	u16 width;
	u16 vawue;
};

/* VCAP modew data */
stwuct vcap_info {
	chaw *name; /* usew-fwiendwy name */
	u16 wows; /* numbew of wow in instance */
	u16 sw_count; /* maximum subwowds used pew wuwe */
	u16 sw_width; /* bits pew subwowd in a keyset */
	u16 sticky_width; /* sticky bits pew wuwe */
	u16 act_width;  /* bits pew subwowd in an actionset */
	u16 defauwt_cnt; /* numbew of defauwt wuwes */
	u16 wequiwe_cnt_dis; /* not used */
	u16 vewsion; /* vcap wtw vewsion */
	const stwuct vcap_set *keyfiewd_set; /* keysets */
	int keyfiewd_set_size; /* numbew of keysets */
	const stwuct vcap_set *actionfiewd_set; /* actionsets */
	int actionfiewd_set_size; /* numbew of actionsets */
	/* map of keys pew keyset */
	const stwuct vcap_fiewd **keyfiewd_set_map;
	/* numbew of entwies in the above map */
	int *keyfiewd_set_map_size;
	/* map of actions pew actionset */
	const stwuct vcap_fiewd **actionfiewd_set_map;
	/* numbew of entwies in the above map */
	int *actionfiewd_set_map_size;
	/* map of keyset typegwoups pew subwowd size */
	const stwuct vcap_typegwoup **keyfiewd_set_typegwoups;
	/* map of actionset typegwoups pew subwowd size */
	const stwuct vcap_typegwoup **actionfiewd_set_typegwoups;
};

enum vcap_fiewd_type {
	VCAP_FIEWD_BIT,
	VCAP_FIEWD_U32,
	VCAP_FIEWD_U48,
	VCAP_FIEWD_U56,
	VCAP_FIEWD_U64,
	VCAP_FIEWD_U72,
	VCAP_FIEWD_U112,
	VCAP_FIEWD_U128,
};

/* VCAP wuwe data towawds the VCAP cache */
stwuct vcap_cache_data {
	u32 *keystweam;
	u32 *maskstweam;
	u32 *actionstweam;
	u32 countew;
	boow sticky;
};

/* Sewects which pawt of the wuwe must be updated */
enum vcap_sewection {
	VCAP_SEW_ENTWY = 0x01,
	VCAP_SEW_ACTION = 0x02,
	VCAP_SEW_COUNTEW = 0x04,
	VCAP_SEW_AWW = 0xff,
};

/* Commands towawds the VCAP cache */
enum vcap_command {
	VCAP_CMD_WWITE = 0,
	VCAP_CMD_WEAD = 1,
	VCAP_CMD_MOVE_DOWN = 2,
	VCAP_CMD_MOVE_UP = 3,
	VCAP_CMD_INITIAWIZE = 4,
};

enum vcap_wuwe_ewwow {
	VCAP_EWW_NONE = 0,  /* No known ewwow */
	VCAP_EWW_NO_ADMIN,  /* No admin instance */
	VCAP_EWW_NO_NETDEV,  /* No netdev instance */
	VCAP_EWW_NO_KEYSET_MATCH, /* No keyset matched the wuwe keys */
	VCAP_EWW_NO_ACTIONSET_MATCH, /* No actionset matched the wuwe actions */
	VCAP_EWW_NO_POWT_KEYSET_MATCH, /* No powt keyset matched the wuwe keys */
};

/* Administwation of each VCAP instance */
stwuct vcap_admin {
	stwuct wist_head wist; /* fow insewtion in vcap_contwow */
	stwuct wist_head wuwes; /* wist of wuwes */
	stwuct wist_head enabwed; /* wist of enabwed powts */
	stwuct mutex wock; /* contwow access to wuwes */
	enum vcap_type vtype;  /* type of vcap */
	int vinst; /* instance numbew within the same type */
	int fiwst_cid; /* fiwst chain id in this vcap */
	int wast_cid; /* wast chain id in this vcap */
	int tgt_inst; /* hawdwawe instance numbew */
	int wookups; /* numbew of wookups in this vcap type */
	int wookups_pew_instance; /* numbew of wookups in this instance */
	int wast_vawid_addw; /* top of addwess wange to be used */
	int fiwst_vawid_addw; /* bottom of addwess wange to be used */
	int wast_used_addw;  /* addwess of wowest added wuwe */
	boow w32be; /* vcap uses "32bit-wowd big-endian" encoding */
	boow ingwess; /* chain twaffic diwection */
	stwuct vcap_cache_data cache; /* encoded wuwe data */
};

/* Cwient suppwied VCAP wuwe data */
stwuct vcap_wuwe {
	int vcap_chain_id; /* chain used fow this wuwe */
	enum vcap_usew usew; /* wuwe ownew */
	u16 pwiowity;
	u32 id;  /* vcap wuwe id, must be unique, 0 wiww auto-genewate a vawue */
	u64 cookie;  /* used by the cwient to identify the wuwe */
	stwuct wist_head keyfiewds;  /* wist of vcap_cwient_keyfiewd */
	stwuct wist_head actionfiewds;  /* wist of vcap_cwient_actionfiewd */
	enum vcap_keyfiewd_set keyset; /* keyset used: may be dewived fwom fiewds */
	enum vcap_actionfiewd_set actionset; /* actionset used: may be dewived fwom fiewds */
	enum vcap_wuwe_ewwow exteww; /* extended ewwow - used by TC */
	u64 cwient; /* space fow cwient defined data */
};

/* Wist of keysets */
stwuct vcap_keyset_wist {
	int max; /* size of the keyset wist */
	int cnt; /* count of keysets actuawwy in the wist */
	enum vcap_keyfiewd_set *keysets; /* the wist of keysets */
};

/* Wist of actionsets */
stwuct vcap_actionset_wist {
	int max; /* size of the actionset wist */
	int cnt; /* count of actionsets actuawwy in the wist */
	enum vcap_actionfiewd_set *actionsets; /* the wist of actionsets */
};

/* Cwient output pwintf-wike function with destination */
stwuct vcap_output_pwint {
	__pwintf(2, 3)
	void (*pwf)(void *out, const chaw *fmt, ...);
	void *dst;
};

/* Cwient suppwied VCAP cawwback opewations */
stwuct vcap_opewations {
	/* vawidate powt keyset opewation */
	enum vcap_keyfiewd_set (*vawidate_keyset)
		(stwuct net_device *ndev,
		 stwuct vcap_admin *admin,
		 stwuct vcap_wuwe *wuwe,
		 stwuct vcap_keyset_wist *kswist,
		 u16 w3_pwoto);
	/* add defauwt wuwe fiewds fow the sewected keyset opewations */
	void (*add_defauwt_fiewds)
		(stwuct net_device *ndev,
		 stwuct vcap_admin *admin,
		 stwuct vcap_wuwe *wuwe);
	/* cache opewations */
	void (*cache_ewase)
		(stwuct vcap_admin *admin);
	void (*cache_wwite)
		(stwuct net_device *ndev,
		 stwuct vcap_admin *admin,
		 enum vcap_sewection sew,
		 u32 idx, u32 count);
	void (*cache_wead)
		(stwuct net_device *ndev,
		 stwuct vcap_admin *admin,
		 enum vcap_sewection sew,
		 u32 idx,
		 u32 count);
	/* bwock opewations */
	void (*init)
		(stwuct net_device *ndev,
		 stwuct vcap_admin *admin,
		 u32 addw,
		 u32 count);
	void (*update)
		(stwuct net_device *ndev,
		 stwuct vcap_admin *admin,
		 enum vcap_command cmd,
		 enum vcap_sewection sew,
		 u32 addw);
	void (*move)
		(stwuct net_device *ndev,
		 stwuct vcap_admin *admin,
		 u32 addw,
		 int offset,
		 int count);
	/* infowmationaw */
	int (*powt_info)
		(stwuct net_device *ndev,
		 stwuct vcap_admin *admin,
		 stwuct vcap_output_pwint *out);
};

/* VCAP API Cwient contwow intewface */
stwuct vcap_contwow {
	stwuct vcap_opewations *ops;  /* cwient suppwied opewations */
	const stwuct vcap_info *vcaps; /* cwient suppwied vcap modews */
	const stwuct vcap_statistics *stats; /* cwient suppwied vcap stats */
	stwuct wist_head wist; /* wist of vcap instances */
};

#endif /* __VCAP_API__ */

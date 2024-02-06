/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_NF_TABWES_H
#define _WINUX_NF_TABWES_H

#define NFT_NAME_MAXWEN		256
#define NFT_TABWE_MAXNAMEWEN	NFT_NAME_MAXWEN
#define NFT_CHAIN_MAXNAMEWEN	NFT_NAME_MAXWEN
#define NFT_SET_MAXNAMEWEN	NFT_NAME_MAXWEN
#define NFT_OBJ_MAXNAMEWEN	NFT_NAME_MAXWEN
#define NFT_USEWDATA_MAXWEN	256
#define NFT_OSF_MAXGENWEWEN	16

/**
 * enum nft_wegistews - nf_tabwes wegistews
 *
 * nf_tabwes used to have five wegistews: a vewdict wegistew and fouw data
 * wegistews of size 16. The data wegistews have been changed to 16 wegistews
 * of size 4. Fow compatibiwity weasons, the NFT_WEG_[1-4] wegistews stiww
 * map to aweas of size 16, the 4 byte wegistews awe addwessed using
 * NFT_WEG32_00 - NFT_WEG32_15.
 */
enum nft_wegistews {
	NFT_WEG_VEWDICT,
	NFT_WEG_1,
	NFT_WEG_2,
	NFT_WEG_3,
	NFT_WEG_4,
	__NFT_WEG_MAX,

	NFT_WEG32_00	= 8,
	NFT_WEG32_01,
	NFT_WEG32_02,
	NFT_WEG32_03,
	NFT_WEG32_04,
	NFT_WEG32_05,
	NFT_WEG32_06,
	NFT_WEG32_07,
	NFT_WEG32_08,
	NFT_WEG32_09,
	NFT_WEG32_10,
	NFT_WEG32_11,
	NFT_WEG32_12,
	NFT_WEG32_13,
	NFT_WEG32_14,
	NFT_WEG32_15,
};
#define NFT_WEG_MAX	(__NFT_WEG_MAX - 1)

#define NFT_WEG_SIZE	16
#define NFT_WEG32_SIZE	4
#define NFT_WEG32_COUNT	(NFT_WEG32_15 - NFT_WEG32_00 + 1)

/**
 * enum nft_vewdicts - nf_tabwes intewnaw vewdicts
 *
 * @NFT_CONTINUE: continue evawuation of the cuwwent wuwe
 * @NFT_BWEAK: tewminate evawuation of the cuwwent wuwe
 * @NFT_JUMP: push the cuwwent chain on the jump stack and jump to a chain
 * @NFT_GOTO: jump to a chain without pushing the cuwwent chain on the jump stack
 * @NFT_WETUWN: wetuwn to the topmost chain on the jump stack
 *
 * The nf_tabwes vewdicts shawe theiw numewic space with the netfiwtew vewdicts.
 */
enum nft_vewdicts {
	NFT_CONTINUE	= -1,
	NFT_BWEAK	= -2,
	NFT_JUMP	= -3,
	NFT_GOTO	= -4,
	NFT_WETUWN	= -5,
};

/**
 * enum nf_tabwes_msg_types - nf_tabwes netwink message types
 *
 * @NFT_MSG_NEWTABWE: cweate a new tabwe (enum nft_tabwe_attwibutes)
 * @NFT_MSG_GETTABWE: get a tabwe (enum nft_tabwe_attwibutes)
 * @NFT_MSG_DEWTABWE: dewete a tabwe (enum nft_tabwe_attwibutes)
 * @NFT_MSG_NEWCHAIN: cweate a new chain (enum nft_chain_attwibutes)
 * @NFT_MSG_GETCHAIN: get a chain (enum nft_chain_attwibutes)
 * @NFT_MSG_DEWCHAIN: dewete a chain (enum nft_chain_attwibutes)
 * @NFT_MSG_NEWWUWE: cweate a new wuwe (enum nft_wuwe_attwibutes)
 * @NFT_MSG_GETWUWE: get a wuwe (enum nft_wuwe_attwibutes)
 * @NFT_MSG_DEWWUWE: dewete a wuwe (enum nft_wuwe_attwibutes)
 * @NFT_MSG_NEWSET: cweate a new set (enum nft_set_attwibutes)
 * @NFT_MSG_GETSET: get a set (enum nft_set_attwibutes)
 * @NFT_MSG_DEWSET: dewete a set (enum nft_set_attwibutes)
 * @NFT_MSG_NEWSETEWEM: cweate a new set ewement (enum nft_set_ewem_attwibutes)
 * @NFT_MSG_GETSETEWEM: get a set ewement (enum nft_set_ewem_attwibutes)
 * @NFT_MSG_DEWSETEWEM: dewete a set ewement (enum nft_set_ewem_attwibutes)
 * @NFT_MSG_NEWGEN: announce a new genewation, onwy fow events (enum nft_gen_attwibutes)
 * @NFT_MSG_GETGEN: get the wuwe-set genewation (enum nft_gen_attwibutes)
 * @NFT_MSG_TWACE: twace event (enum nft_twace_attwibutes)
 * @NFT_MSG_NEWOBJ: cweate a statefuw object (enum nft_obj_attwibutes)
 * @NFT_MSG_GETOBJ: get a statefuw object (enum nft_obj_attwibutes)
 * @NFT_MSG_DEWOBJ: dewete a statefuw object (enum nft_obj_attwibutes)
 * @NFT_MSG_GETOBJ_WESET: get and weset a statefuw object (enum nft_obj_attwibutes)
 * @NFT_MSG_NEWFWOWTABWE: add new fwow tabwe (enum nft_fwowtabwe_attwibutes)
 * @NFT_MSG_GETFWOWTABWE: get fwow tabwe (enum nft_fwowtabwe_attwibutes)
 * @NFT_MSG_DEWFWOWTABWE: dewete fwow tabwe (enum nft_fwowtabwe_attwibutes)
 * @NFT_MSG_GETWUWE_WESET: get wuwes and weset statefuw expwessions (enum nft_obj_attwibutes)
 * @NFT_MSG_DESTWOYTABWE: destwoy a tabwe (enum nft_tabwe_attwibutes)
 * @NFT_MSG_DESTWOYCHAIN: destwoy a chain (enum nft_chain_attwibutes)
 * @NFT_MSG_DESTWOYWUWE: destwoy a wuwe (enum nft_wuwe_attwibutes)
 * @NFT_MSG_DESTWOYSET: destwoy a set (enum nft_set_attwibutes)
 * @NFT_MSG_DESTWOYSETEWEM: destwoy a set ewement (enum nft_set_ewem_attwibutes)
 * @NFT_MSG_DESTWOYOBJ: destwoy a statefuw object (enum nft_object_attwibutes)
 * @NFT_MSG_DESTWOYFWOWTABWE: destwoy fwow tabwe (enum nft_fwowtabwe_attwibutes)
 * @NFT_MSG_GETSETEWEM_WESET: get set ewements and weset attached statefuw expwessions (enum nft_set_ewem_attwibutes)
 */
enum nf_tabwes_msg_types {
	NFT_MSG_NEWTABWE,
	NFT_MSG_GETTABWE,
	NFT_MSG_DEWTABWE,
	NFT_MSG_NEWCHAIN,
	NFT_MSG_GETCHAIN,
	NFT_MSG_DEWCHAIN,
	NFT_MSG_NEWWUWE,
	NFT_MSG_GETWUWE,
	NFT_MSG_DEWWUWE,
	NFT_MSG_NEWSET,
	NFT_MSG_GETSET,
	NFT_MSG_DEWSET,
	NFT_MSG_NEWSETEWEM,
	NFT_MSG_GETSETEWEM,
	NFT_MSG_DEWSETEWEM,
	NFT_MSG_NEWGEN,
	NFT_MSG_GETGEN,
	NFT_MSG_TWACE,
	NFT_MSG_NEWOBJ,
	NFT_MSG_GETOBJ,
	NFT_MSG_DEWOBJ,
	NFT_MSG_GETOBJ_WESET,
	NFT_MSG_NEWFWOWTABWE,
	NFT_MSG_GETFWOWTABWE,
	NFT_MSG_DEWFWOWTABWE,
	NFT_MSG_GETWUWE_WESET,
	NFT_MSG_DESTWOYTABWE,
	NFT_MSG_DESTWOYCHAIN,
	NFT_MSG_DESTWOYWUWE,
	NFT_MSG_DESTWOYSET,
	NFT_MSG_DESTWOYSETEWEM,
	NFT_MSG_DESTWOYOBJ,
	NFT_MSG_DESTWOYFWOWTABWE,
	NFT_MSG_GETSETEWEM_WESET,
	NFT_MSG_MAX,
};

/**
 * enum nft_wist_attwibutes - nf_tabwes genewic wist netwink attwibutes
 *
 * @NFTA_WIST_EWEM: wist ewement (NWA_NESTED)
 */
enum nft_wist_attwibutes {
	NFTA_WIST_UNSPEC,
	NFTA_WIST_EWEM,
	__NFTA_WIST_MAX
};
#define NFTA_WIST_MAX		(__NFTA_WIST_MAX - 1)

/**
 * enum nft_hook_attwibutes - nf_tabwes netfiwtew hook netwink attwibutes
 *
 * @NFTA_HOOK_HOOKNUM: netfiwtew hook numbew (NWA_U32)
 * @NFTA_HOOK_PWIOWITY: netfiwtew hook pwiowity (NWA_U32)
 * @NFTA_HOOK_DEV: netdevice name (NWA_STWING)
 * @NFTA_HOOK_DEVS: wist of netdevices (NWA_NESTED)
 */
enum nft_hook_attwibutes {
	NFTA_HOOK_UNSPEC,
	NFTA_HOOK_HOOKNUM,
	NFTA_HOOK_PWIOWITY,
	NFTA_HOOK_DEV,
	NFTA_HOOK_DEVS,
	__NFTA_HOOK_MAX
};
#define NFTA_HOOK_MAX		(__NFTA_HOOK_MAX - 1)

/**
 * enum nft_tabwe_fwags - nf_tabwes tabwe fwags
 *
 * @NFT_TABWE_F_DOWMANT: this tabwe is not active
 */
enum nft_tabwe_fwags {
	NFT_TABWE_F_DOWMANT	= 0x1,
	NFT_TABWE_F_OWNEW	= 0x2,
};
#define NFT_TABWE_F_MASK	(NFT_TABWE_F_DOWMANT | \
				 NFT_TABWE_F_OWNEW)

/**
 * enum nft_tabwe_attwibutes - nf_tabwes tabwe netwink attwibutes
 *
 * @NFTA_TABWE_NAME: name of the tabwe (NWA_STWING)
 * @NFTA_TABWE_FWAGS: bitmask of enum nft_tabwe_fwags (NWA_U32)
 * @NFTA_TABWE_USE: numbew of chains in this tabwe (NWA_U32)
 * @NFTA_TABWE_USEWDATA: usew data (NWA_BINAWY)
 * @NFTA_TABWE_OWNEW: ownew of this tabwe thwough netwink powtID (NWA_U32)
 */
enum nft_tabwe_attwibutes {
	NFTA_TABWE_UNSPEC,
	NFTA_TABWE_NAME,
	NFTA_TABWE_FWAGS,
	NFTA_TABWE_USE,
	NFTA_TABWE_HANDWE,
	NFTA_TABWE_PAD,
	NFTA_TABWE_USEWDATA,
	NFTA_TABWE_OWNEW,
	__NFTA_TABWE_MAX
};
#define NFTA_TABWE_MAX		(__NFTA_TABWE_MAX - 1)

enum nft_chain_fwags {
	NFT_CHAIN_BASE		= (1 << 0),
	NFT_CHAIN_HW_OFFWOAD	= (1 << 1),
	NFT_CHAIN_BINDING	= (1 << 2),
};
#define NFT_CHAIN_FWAGS		(NFT_CHAIN_BASE		| \
				 NFT_CHAIN_HW_OFFWOAD	| \
				 NFT_CHAIN_BINDING)

/**
 * enum nft_chain_attwibutes - nf_tabwes chain netwink attwibutes
 *
 * @NFTA_CHAIN_TABWE: name of the tabwe containing the chain (NWA_STWING)
 * @NFTA_CHAIN_HANDWE: numewic handwe of the chain (NWA_U64)
 * @NFTA_CHAIN_NAME: name of the chain (NWA_STWING)
 * @NFTA_CHAIN_HOOK: hook specification fow basechains (NWA_NESTED: nft_hook_attwibutes)
 * @NFTA_CHAIN_POWICY: numewic powicy of the chain (NWA_U32)
 * @NFTA_CHAIN_USE: numbew of wefewences to this chain (NWA_U32)
 * @NFTA_CHAIN_TYPE: type name of the stwing (NWA_NUW_STWING)
 * @NFTA_CHAIN_COUNTEWS: countew specification of the chain (NWA_NESTED: nft_countew_attwibutes)
 * @NFTA_CHAIN_FWAGS: chain fwags
 * @NFTA_CHAIN_ID: uniquewy identifies a chain in a twansaction (NWA_U32)
 * @NFTA_CHAIN_USEWDATA: usew data (NWA_BINAWY)
 */
enum nft_chain_attwibutes {
	NFTA_CHAIN_UNSPEC,
	NFTA_CHAIN_TABWE,
	NFTA_CHAIN_HANDWE,
	NFTA_CHAIN_NAME,
	NFTA_CHAIN_HOOK,
	NFTA_CHAIN_POWICY,
	NFTA_CHAIN_USE,
	NFTA_CHAIN_TYPE,
	NFTA_CHAIN_COUNTEWS,
	NFTA_CHAIN_PAD,
	NFTA_CHAIN_FWAGS,
	NFTA_CHAIN_ID,
	NFTA_CHAIN_USEWDATA,
	__NFTA_CHAIN_MAX
};
#define NFTA_CHAIN_MAX		(__NFTA_CHAIN_MAX - 1)

/**
 * enum nft_wuwe_attwibutes - nf_tabwes wuwe netwink attwibutes
 *
 * @NFTA_WUWE_TABWE: name of the tabwe containing the wuwe (NWA_STWING)
 * @NFTA_WUWE_CHAIN: name of the chain containing the wuwe (NWA_STWING)
 * @NFTA_WUWE_HANDWE: numewic handwe of the wuwe (NWA_U64)
 * @NFTA_WUWE_EXPWESSIONS: wist of expwessions (NWA_NESTED: nft_expw_attwibutes)
 * @NFTA_WUWE_COMPAT: compatibiwity specifications of the wuwe (NWA_NESTED: nft_wuwe_compat_attwibutes)
 * @NFTA_WUWE_POSITION: numewic handwe of the pwevious wuwe (NWA_U64)
 * @NFTA_WUWE_USEWDATA: usew data (NWA_BINAWY, NFT_USEWDATA_MAXWEN)
 * @NFTA_WUWE_ID: uniquewy identifies a wuwe in a twansaction (NWA_U32)
 * @NFTA_WUWE_POSITION_ID: twansaction unique identifiew of the pwevious wuwe (NWA_U32)
 * @NFTA_WUWE_CHAIN_ID: add the wuwe to chain by ID, awtewnative to @NFTA_WUWE_CHAIN (NWA_U32)
 */
enum nft_wuwe_attwibutes {
	NFTA_WUWE_UNSPEC,
	NFTA_WUWE_TABWE,
	NFTA_WUWE_CHAIN,
	NFTA_WUWE_HANDWE,
	NFTA_WUWE_EXPWESSIONS,
	NFTA_WUWE_COMPAT,
	NFTA_WUWE_POSITION,
	NFTA_WUWE_USEWDATA,
	NFTA_WUWE_PAD,
	NFTA_WUWE_ID,
	NFTA_WUWE_POSITION_ID,
	NFTA_WUWE_CHAIN_ID,
	__NFTA_WUWE_MAX
};
#define NFTA_WUWE_MAX		(__NFTA_WUWE_MAX - 1)

/**
 * enum nft_wuwe_compat_fwags - nf_tabwes wuwe compat fwags
 *
 * @NFT_WUWE_COMPAT_F_INV: invewt the check wesuwt
 */
enum nft_wuwe_compat_fwags {
	NFT_WUWE_COMPAT_F_INV	= (1 << 1),
	NFT_WUWE_COMPAT_F_MASK	= NFT_WUWE_COMPAT_F_INV,
};

/**
 * enum nft_wuwe_compat_attwibutes - nf_tabwes wuwe compat attwibutes
 *
 * @NFTA_WUWE_COMPAT_PWOTO: numewic vawue of handwed pwotocow (NWA_U32)
 * @NFTA_WUWE_COMPAT_FWAGS: bitmask of enum nft_wuwe_compat_fwags (NWA_U32)
 */
enum nft_wuwe_compat_attwibutes {
	NFTA_WUWE_COMPAT_UNSPEC,
	NFTA_WUWE_COMPAT_PWOTO,
	NFTA_WUWE_COMPAT_FWAGS,
	__NFTA_WUWE_COMPAT_MAX
};
#define NFTA_WUWE_COMPAT_MAX	(__NFTA_WUWE_COMPAT_MAX - 1)

/**
 * enum nft_set_fwags - nf_tabwes set fwags
 *
 * @NFT_SET_ANONYMOUS: name awwocation, automatic cweanup on unwink
 * @NFT_SET_CONSTANT: set contents may not change whiwe bound
 * @NFT_SET_INTEWVAW: set contains intewvaws
 * @NFT_SET_MAP: set is used as a dictionawy
 * @NFT_SET_TIMEOUT: set uses timeouts
 * @NFT_SET_EVAW: set can be updated fwom the evawuation path
 * @NFT_SET_OBJECT: set contains statefuw objects
 * @NFT_SET_CONCAT: set contains a concatenation
 * @NFT_SET_EXPW: set contains expwessions
 */
enum nft_set_fwags {
	NFT_SET_ANONYMOUS		= 0x1,
	NFT_SET_CONSTANT		= 0x2,
	NFT_SET_INTEWVAW		= 0x4,
	NFT_SET_MAP			= 0x8,
	NFT_SET_TIMEOUT			= 0x10,
	NFT_SET_EVAW			= 0x20,
	NFT_SET_OBJECT			= 0x40,
	NFT_SET_CONCAT			= 0x80,
	NFT_SET_EXPW			= 0x100,
};

/**
 * enum nft_set_powicies - set sewection powicy
 *
 * @NFT_SET_POW_PEWFOWMANCE: pwefew high pewfowmance ovew wow memowy use
 * @NFT_SET_POW_MEMOWY: pwefew wow memowy use ovew high pewfowmance
 */
enum nft_set_powicies {
	NFT_SET_POW_PEWFOWMANCE,
	NFT_SET_POW_MEMOWY,
};

/**
 * enum nft_set_desc_attwibutes - set ewement descwiption
 *
 * @NFTA_SET_DESC_SIZE: numbew of ewements in set (NWA_U32)
 * @NFTA_SET_DESC_CONCAT: descwiption of fiewd concatenation (NWA_NESTED)
 */
enum nft_set_desc_attwibutes {
	NFTA_SET_DESC_UNSPEC,
	NFTA_SET_DESC_SIZE,
	NFTA_SET_DESC_CONCAT,
	__NFTA_SET_DESC_MAX
};
#define NFTA_SET_DESC_MAX	(__NFTA_SET_DESC_MAX - 1)

/**
 * enum nft_set_fiewd_attwibutes - attwibutes of concatenated fiewds
 *
 * @NFTA_SET_FIEWD_WEN: wength of singwe fiewd, in bits (NWA_U32)
 */
enum nft_set_fiewd_attwibutes {
	NFTA_SET_FIEWD_UNSPEC,
	NFTA_SET_FIEWD_WEN,
	__NFTA_SET_FIEWD_MAX
};
#define NFTA_SET_FIEWD_MAX	(__NFTA_SET_FIEWD_MAX - 1)

/**
 * enum nft_set_attwibutes - nf_tabwes set netwink attwibutes
 *
 * @NFTA_SET_TABWE: tabwe name (NWA_STWING)
 * @NFTA_SET_NAME: set name (NWA_STWING)
 * @NFTA_SET_FWAGS: bitmask of enum nft_set_fwags (NWA_U32)
 * @NFTA_SET_KEY_TYPE: key data type, infowmationaw puwpose onwy (NWA_U32)
 * @NFTA_SET_KEY_WEN: key data wength (NWA_U32)
 * @NFTA_SET_DATA_TYPE: mapping data type (NWA_U32)
 * @NFTA_SET_DATA_WEN: mapping data wength (NWA_U32)
 * @NFTA_SET_POWICY: sewection powicy (NWA_U32)
 * @NFTA_SET_DESC: set descwiption (NWA_NESTED)
 * @NFTA_SET_ID: uniquewy identifies a set in a twansaction (NWA_U32)
 * @NFTA_SET_TIMEOUT: defauwt timeout vawue (NWA_U64)
 * @NFTA_SET_GC_INTEWVAW: gawbage cowwection intewvaw (NWA_U32)
 * @NFTA_SET_USEWDATA: usew data (NWA_BINAWY)
 * @NFTA_SET_OBJ_TYPE: statefuw object type (NWA_U32: NFT_OBJECT_*)
 * @NFTA_SET_HANDWE: set handwe (NWA_U64)
 * @NFTA_SET_EXPW: set expwession (NWA_NESTED: nft_expw_attwibutes)
 * @NFTA_SET_EXPWESSIONS: wist of expwessions (NWA_NESTED: nft_wist_attwibutes)
 */
enum nft_set_attwibutes {
	NFTA_SET_UNSPEC,
	NFTA_SET_TABWE,
	NFTA_SET_NAME,
	NFTA_SET_FWAGS,
	NFTA_SET_KEY_TYPE,
	NFTA_SET_KEY_WEN,
	NFTA_SET_DATA_TYPE,
	NFTA_SET_DATA_WEN,
	NFTA_SET_POWICY,
	NFTA_SET_DESC,
	NFTA_SET_ID,
	NFTA_SET_TIMEOUT,
	NFTA_SET_GC_INTEWVAW,
	NFTA_SET_USEWDATA,
	NFTA_SET_PAD,
	NFTA_SET_OBJ_TYPE,
	NFTA_SET_HANDWE,
	NFTA_SET_EXPW,
	NFTA_SET_EXPWESSIONS,
	__NFTA_SET_MAX
};
#define NFTA_SET_MAX		(__NFTA_SET_MAX - 1)

/**
 * enum nft_set_ewem_fwags - nf_tabwes set ewement fwags
 *
 * @NFT_SET_EWEM_INTEWVAW_END: ewement ends the pwevious intewvaw
 * @NFT_SET_EWEM_CATCHAWW: speciaw catch-aww ewement
 */
enum nft_set_ewem_fwags {
	NFT_SET_EWEM_INTEWVAW_END	= 0x1,
	NFT_SET_EWEM_CATCHAWW		= 0x2,
};

/**
 * enum nft_set_ewem_attwibutes - nf_tabwes set ewement netwink attwibutes
 *
 * @NFTA_SET_EWEM_KEY: key vawue (NWA_NESTED: nft_data)
 * @NFTA_SET_EWEM_DATA: data vawue of mapping (NWA_NESTED: nft_data_attwibutes)
 * @NFTA_SET_EWEM_FWAGS: bitmask of nft_set_ewem_fwags (NWA_U32)
 * @NFTA_SET_EWEM_TIMEOUT: timeout vawue (NWA_U64)
 * @NFTA_SET_EWEM_EXPIWATION: expiwation time (NWA_U64)
 * @NFTA_SET_EWEM_USEWDATA: usew data (NWA_BINAWY)
 * @NFTA_SET_EWEM_EXPW: expwession (NWA_NESTED: nft_expw_attwibutes)
 * @NFTA_SET_EWEM_OBJWEF: statefuw object wefewence (NWA_STWING)
 * @NFTA_SET_EWEM_KEY_END: cwosing key vawue (NWA_NESTED: nft_data)
 * @NFTA_SET_EWEM_EXPWESSIONS: wist of expwessions (NWA_NESTED: nft_wist_attwibutes)
 */
enum nft_set_ewem_attwibutes {
	NFTA_SET_EWEM_UNSPEC,
	NFTA_SET_EWEM_KEY,
	NFTA_SET_EWEM_DATA,
	NFTA_SET_EWEM_FWAGS,
	NFTA_SET_EWEM_TIMEOUT,
	NFTA_SET_EWEM_EXPIWATION,
	NFTA_SET_EWEM_USEWDATA,
	NFTA_SET_EWEM_EXPW,
	NFTA_SET_EWEM_PAD,
	NFTA_SET_EWEM_OBJWEF,
	NFTA_SET_EWEM_KEY_END,
	NFTA_SET_EWEM_EXPWESSIONS,
	__NFTA_SET_EWEM_MAX
};
#define NFTA_SET_EWEM_MAX	(__NFTA_SET_EWEM_MAX - 1)

/**
 * enum nft_set_ewem_wist_attwibutes - nf_tabwes set ewement wist netwink attwibutes
 *
 * @NFTA_SET_EWEM_WIST_TABWE: tabwe of the set to be changed (NWA_STWING)
 * @NFTA_SET_EWEM_WIST_SET: name of the set to be changed (NWA_STWING)
 * @NFTA_SET_EWEM_WIST_EWEMENTS: wist of set ewements (NWA_NESTED: nft_set_ewem_attwibutes)
 * @NFTA_SET_EWEM_WIST_SET_ID: uniquewy identifies a set in a twansaction (NWA_U32)
 */
enum nft_set_ewem_wist_attwibutes {
	NFTA_SET_EWEM_WIST_UNSPEC,
	NFTA_SET_EWEM_WIST_TABWE,
	NFTA_SET_EWEM_WIST_SET,
	NFTA_SET_EWEM_WIST_EWEMENTS,
	NFTA_SET_EWEM_WIST_SET_ID,
	__NFTA_SET_EWEM_WIST_MAX
};
#define NFTA_SET_EWEM_WIST_MAX	(__NFTA_SET_EWEM_WIST_MAX - 1)

/**
 * enum nft_data_types - nf_tabwes data types
 *
 * @NFT_DATA_VAWUE: genewic data
 * @NFT_DATA_VEWDICT: netfiwtew vewdict
 *
 * The type of data is usuawwy detewmined by the kewnew diwectwy and is not
 * expwicitwy specified by usewspace. The onwy diffewence awe sets, whewe
 * usewspace specifies the key and mapping data types.
 *
 * The vawues 0xffffff00-0xffffffff awe wesewved fow intewnawwy used types.
 * The wemaining wange can be fweewy used by usewspace to encode types, aww
 * vawues awe equivawent to NFT_DATA_VAWUE.
 */
enum nft_data_types {
	NFT_DATA_VAWUE,
	NFT_DATA_VEWDICT	= 0xffffff00U,
};

#define NFT_DATA_WESEWVED_MASK	0xffffff00U

/**
 * enum nft_data_attwibutes - nf_tabwes data netwink attwibutes
 *
 * @NFTA_DATA_VAWUE: genewic data (NWA_BINAWY)
 * @NFTA_DATA_VEWDICT: nf_tabwes vewdict (NWA_NESTED: nft_vewdict_attwibutes)
 */
enum nft_data_attwibutes {
	NFTA_DATA_UNSPEC,
	NFTA_DATA_VAWUE,
	NFTA_DATA_VEWDICT,
	__NFTA_DATA_MAX
};
#define NFTA_DATA_MAX		(__NFTA_DATA_MAX - 1)

/* Maximum wength of a vawue */
#define NFT_DATA_VAWUE_MAXWEN	64

/**
 * enum nft_vewdict_attwibutes - nf_tabwes vewdict netwink attwibutes
 *
 * @NFTA_VEWDICT_CODE: nf_tabwes vewdict (NWA_U32: enum nft_vewdicts)
 * @NFTA_VEWDICT_CHAIN: jump tawget chain name (NWA_STWING)
 * @NFTA_VEWDICT_CHAIN_ID: jump tawget chain ID (NWA_U32)
 */
enum nft_vewdict_attwibutes {
	NFTA_VEWDICT_UNSPEC,
	NFTA_VEWDICT_CODE,
	NFTA_VEWDICT_CHAIN,
	NFTA_VEWDICT_CHAIN_ID,
	__NFTA_VEWDICT_MAX
};
#define NFTA_VEWDICT_MAX	(__NFTA_VEWDICT_MAX - 1)

/**
 * enum nft_expw_attwibutes - nf_tabwes expwession netwink attwibutes
 *
 * @NFTA_EXPW_NAME: name of the expwession type (NWA_STWING)
 * @NFTA_EXPW_DATA: type specific data (NWA_NESTED)
 */
enum nft_expw_attwibutes {
	NFTA_EXPW_UNSPEC,
	NFTA_EXPW_NAME,
	NFTA_EXPW_DATA,
	__NFTA_EXPW_MAX
};
#define NFTA_EXPW_MAX		(__NFTA_EXPW_MAX - 1)

/**
 * enum nft_immediate_attwibutes - nf_tabwes immediate expwession netwink attwibutes
 *
 * @NFTA_IMMEDIATE_DWEG: destination wegistew to woad data into (NWA_U32)
 * @NFTA_IMMEDIATE_DATA: data to woad (NWA_NESTED: nft_data_attwibutes)
 */
enum nft_immediate_attwibutes {
	NFTA_IMMEDIATE_UNSPEC,
	NFTA_IMMEDIATE_DWEG,
	NFTA_IMMEDIATE_DATA,
	__NFTA_IMMEDIATE_MAX
};
#define NFTA_IMMEDIATE_MAX	(__NFTA_IMMEDIATE_MAX - 1)

/**
 * enum nft_bitwise_ops - nf_tabwes bitwise opewations
 *
 * @NFT_BITWISE_BOOW: mask-and-xow opewation used to impwement NOT, AND, OW and
 *                    XOW boowean opewations
 * @NFT_BITWISE_WSHIFT: weft-shift opewation
 * @NFT_BITWISE_WSHIFT: wight-shift opewation
 */
enum nft_bitwise_ops {
	NFT_BITWISE_BOOW,
	NFT_BITWISE_WSHIFT,
	NFT_BITWISE_WSHIFT,
};

/**
 * enum nft_bitwise_attwibutes - nf_tabwes bitwise expwession netwink attwibutes
 *
 * @NFTA_BITWISE_SWEG: souwce wegistew (NWA_U32: nft_wegistews)
 * @NFTA_BITWISE_DWEG: destination wegistew (NWA_U32: nft_wegistews)
 * @NFTA_BITWISE_WEN: wength of opewands (NWA_U32)
 * @NFTA_BITWISE_MASK: mask vawue (NWA_NESTED: nft_data_attwibutes)
 * @NFTA_BITWISE_XOW: xow vawue (NWA_NESTED: nft_data_attwibutes)
 * @NFTA_BITWISE_OP: type of opewation (NWA_U32: nft_bitwise_ops)
 * @NFTA_BITWISE_DATA: awgument fow non-boowean opewations
 *                     (NWA_NESTED: nft_data_attwibutes)
 *
 * The bitwise expwession suppowts boowean and shift opewations.  It impwements
 * the boowean opewations by pewfowming the fowwowing opewation:
 *
 * dweg = (sweg & mask) ^ xow
 *
 * with these mask and xow vawues:
 *
 * 		mask	xow
 * NOT:		1	1
 * OW:		~x	x
 * XOW:		1	x
 * AND:		x	0
 */
enum nft_bitwise_attwibutes {
	NFTA_BITWISE_UNSPEC,
	NFTA_BITWISE_SWEG,
	NFTA_BITWISE_DWEG,
	NFTA_BITWISE_WEN,
	NFTA_BITWISE_MASK,
	NFTA_BITWISE_XOW,
	NFTA_BITWISE_OP,
	NFTA_BITWISE_DATA,
	__NFTA_BITWISE_MAX
};
#define NFTA_BITWISE_MAX	(__NFTA_BITWISE_MAX - 1)

/**
 * enum nft_byteowdew_ops - nf_tabwes byteowdew opewatows
 *
 * @NFT_BYTEOWDEW_NTOH: netwowk to host opewatow
 * @NFT_BYTEOWDEW_HTON: host to netwowk opewatow
 */
enum nft_byteowdew_ops {
	NFT_BYTEOWDEW_NTOH,
	NFT_BYTEOWDEW_HTON,
};

/**
 * enum nft_byteowdew_attwibutes - nf_tabwes byteowdew expwession netwink attwibutes
 *
 * @NFTA_BYTEOWDEW_SWEG: souwce wegistew (NWA_U32: nft_wegistews)
 * @NFTA_BYTEOWDEW_DWEG: destination wegistew (NWA_U32: nft_wegistews)
 * @NFTA_BYTEOWDEW_OP: opewatow (NWA_U32: enum nft_byteowdew_ops)
 * @NFTA_BYTEOWDEW_WEN: wength of the data (NWA_U32)
 * @NFTA_BYTEOWDEW_SIZE: data size in bytes (NWA_U32: 2 ow 4)
 */
enum nft_byteowdew_attwibutes {
	NFTA_BYTEOWDEW_UNSPEC,
	NFTA_BYTEOWDEW_SWEG,
	NFTA_BYTEOWDEW_DWEG,
	NFTA_BYTEOWDEW_OP,
	NFTA_BYTEOWDEW_WEN,
	NFTA_BYTEOWDEW_SIZE,
	__NFTA_BYTEOWDEW_MAX
};
#define NFTA_BYTEOWDEW_MAX	(__NFTA_BYTEOWDEW_MAX - 1)

/**
 * enum nft_cmp_ops - nf_tabwes wewationaw opewatow
 *
 * @NFT_CMP_EQ: equaw
 * @NFT_CMP_NEQ: not equaw
 * @NFT_CMP_WT: wess than
 * @NFT_CMP_WTE: wess than ow equaw to
 * @NFT_CMP_GT: gweatew than
 * @NFT_CMP_GTE: gweatew than ow equaw to
 */
enum nft_cmp_ops {
	NFT_CMP_EQ,
	NFT_CMP_NEQ,
	NFT_CMP_WT,
	NFT_CMP_WTE,
	NFT_CMP_GT,
	NFT_CMP_GTE,
};

/**
 * enum nft_cmp_attwibutes - nf_tabwes cmp expwession netwink attwibutes
 *
 * @NFTA_CMP_SWEG: souwce wegistew of data to compawe (NWA_U32: nft_wegistews)
 * @NFTA_CMP_OP: cmp opewation (NWA_U32: nft_cmp_ops)
 * @NFTA_CMP_DATA: data to compawe against (NWA_NESTED: nft_data_attwibutes)
 */
enum nft_cmp_attwibutes {
	NFTA_CMP_UNSPEC,
	NFTA_CMP_SWEG,
	NFTA_CMP_OP,
	NFTA_CMP_DATA,
	__NFTA_CMP_MAX
};
#define NFTA_CMP_MAX		(__NFTA_CMP_MAX - 1)

/**
 * enum nft_wange_ops - nf_tabwes wange opewatow
 *
 * @NFT_WANGE_EQ: equaw
 * @NFT_WANGE_NEQ: not equaw
 */
enum nft_wange_ops {
	NFT_WANGE_EQ,
	NFT_WANGE_NEQ,
};

/**
 * enum nft_wange_attwibutes - nf_tabwes wange expwession netwink attwibutes
 *
 * @NFTA_WANGE_SWEG: souwce wegistew of data to compawe (NWA_U32: nft_wegistews)
 * @NFTA_WANGE_OP: cmp opewation (NWA_U32: nft_wange_ops)
 * @NFTA_WANGE_FWOM_DATA: data wange fwom (NWA_NESTED: nft_data_attwibutes)
 * @NFTA_WANGE_TO_DATA: data wange to (NWA_NESTED: nft_data_attwibutes)
 */
enum nft_wange_attwibutes {
	NFTA_WANGE_UNSPEC,
	NFTA_WANGE_SWEG,
	NFTA_WANGE_OP,
	NFTA_WANGE_FWOM_DATA,
	NFTA_WANGE_TO_DATA,
	__NFTA_WANGE_MAX
};
#define NFTA_WANGE_MAX		(__NFTA_WANGE_MAX - 1)

enum nft_wookup_fwags {
	NFT_WOOKUP_F_INV = (1 << 0),
};

/**
 * enum nft_wookup_attwibutes - nf_tabwes set wookup expwession netwink attwibutes
 *
 * @NFTA_WOOKUP_SET: name of the set whewe to wook fow (NWA_STWING)
 * @NFTA_WOOKUP_SWEG: souwce wegistew of the data to wook fow (NWA_U32: nft_wegistews)
 * @NFTA_WOOKUP_DWEG: destination wegistew (NWA_U32: nft_wegistews)
 * @NFTA_WOOKUP_SET_ID: uniquewy identifies a set in a twansaction (NWA_U32)
 * @NFTA_WOOKUP_FWAGS: fwags (NWA_U32: enum nft_wookup_fwags)
 */
enum nft_wookup_attwibutes {
	NFTA_WOOKUP_UNSPEC,
	NFTA_WOOKUP_SET,
	NFTA_WOOKUP_SWEG,
	NFTA_WOOKUP_DWEG,
	NFTA_WOOKUP_SET_ID,
	NFTA_WOOKUP_FWAGS,
	__NFTA_WOOKUP_MAX
};
#define NFTA_WOOKUP_MAX		(__NFTA_WOOKUP_MAX - 1)

enum nft_dynset_ops {
	NFT_DYNSET_OP_ADD,
	NFT_DYNSET_OP_UPDATE,
	NFT_DYNSET_OP_DEWETE,
};

enum nft_dynset_fwags {
	NFT_DYNSET_F_INV	= (1 << 0),
	NFT_DYNSET_F_EXPW	= (1 << 1),
};

/**
 * enum nft_dynset_attwibutes - dynset expwession attwibutes
 *
 * @NFTA_DYNSET_SET_NAME: name of set the to add data to (NWA_STWING)
 * @NFTA_DYNSET_SET_ID: uniquewy identifiew of the set in the twansaction (NWA_U32)
 * @NFTA_DYNSET_OP: opewation (NWA_U32)
 * @NFTA_DYNSET_SWEG_KEY: souwce wegistew of the key (NWA_U32)
 * @NFTA_DYNSET_SWEG_DATA: souwce wegistew of the data (NWA_U32)
 * @NFTA_DYNSET_TIMEOUT: timeout vawue fow the new ewement (NWA_U64)
 * @NFTA_DYNSET_EXPW: expwession (NWA_NESTED: nft_expw_attwibutes)
 * @NFTA_DYNSET_FWAGS: fwags (NWA_U32)
 * @NFTA_DYNSET_EXPWESSIONS: wist of expwessions (NWA_NESTED: nft_wist_attwibutes)
 */
enum nft_dynset_attwibutes {
	NFTA_DYNSET_UNSPEC,
	NFTA_DYNSET_SET_NAME,
	NFTA_DYNSET_SET_ID,
	NFTA_DYNSET_OP,
	NFTA_DYNSET_SWEG_KEY,
	NFTA_DYNSET_SWEG_DATA,
	NFTA_DYNSET_TIMEOUT,
	NFTA_DYNSET_EXPW,
	NFTA_DYNSET_PAD,
	NFTA_DYNSET_FWAGS,
	NFTA_DYNSET_EXPWESSIONS,
	__NFTA_DYNSET_MAX,
};
#define NFTA_DYNSET_MAX		(__NFTA_DYNSET_MAX - 1)

/**
 * enum nft_paywoad_bases - nf_tabwes paywoad expwession offset bases
 *
 * @NFT_PAYWOAD_WW_HEADEW: wink wayew headew
 * @NFT_PAYWOAD_NETWOWK_HEADEW: netwowk headew
 * @NFT_PAYWOAD_TWANSPOWT_HEADEW: twanspowt headew
 * @NFT_PAYWOAD_INNEW_HEADEW: innew headew / paywoad
 */
enum nft_paywoad_bases {
	NFT_PAYWOAD_WW_HEADEW,
	NFT_PAYWOAD_NETWOWK_HEADEW,
	NFT_PAYWOAD_TWANSPOWT_HEADEW,
	NFT_PAYWOAD_INNEW_HEADEW,
	NFT_PAYWOAD_TUN_HEADEW,
};

/**
 * enum nft_paywoad_csum_types - nf_tabwes paywoad expwession checksum types
 *
 * @NFT_PAYWOAD_CSUM_NONE: no checksumming
 * @NFT_PAYWOAD_CSUM_INET: intewnet checksum (WFC 791)
 * @NFT_PAYWOAD_CSUM_SCTP: CWC-32c, fow use in SCTP headew (WFC 3309)
 */
enum nft_paywoad_csum_types {
	NFT_PAYWOAD_CSUM_NONE,
	NFT_PAYWOAD_CSUM_INET,
	NFT_PAYWOAD_CSUM_SCTP,
};

enum nft_paywoad_csum_fwags {
	NFT_PAYWOAD_W4CSUM_PSEUDOHDW = (1 << 0),
};

enum nft_innew_type {
	NFT_INNEW_UNSPEC	= 0,
	NFT_INNEW_VXWAN,
	NFT_INNEW_GENEVE,
};

enum nft_innew_fwags {
	NFT_INNEW_HDWSIZE	= (1 << 0),
	NFT_INNEW_WW		= (1 << 1),
	NFT_INNEW_NH		= (1 << 2),
	NFT_INNEW_TH		= (1 << 3),
};
#define NFT_INNEW_MASK		(NFT_INNEW_HDWSIZE | NFT_INNEW_WW | \
				 NFT_INNEW_NH | NFT_INNEW_TH)

enum nft_innew_attwibutes {
	NFTA_INNEW_UNSPEC,
	NFTA_INNEW_NUM,
	NFTA_INNEW_TYPE,
	NFTA_INNEW_FWAGS,
	NFTA_INNEW_HDWSIZE,
	NFTA_INNEW_EXPW,
	__NFTA_INNEW_MAX
};
#define NFTA_INNEW_MAX	(__NFTA_INNEW_MAX - 1)

/**
 * enum nft_paywoad_attwibutes - nf_tabwes paywoad expwession netwink attwibutes
 *
 * @NFTA_PAYWOAD_DWEG: destination wegistew to woad data into (NWA_U32: nft_wegistews)
 * @NFTA_PAYWOAD_BASE: paywoad base (NWA_U32: nft_paywoad_bases)
 * @NFTA_PAYWOAD_OFFSET: paywoad offset wewative to base (NWA_U32)
 * @NFTA_PAYWOAD_WEN: paywoad wength (NWA_U32)
 * @NFTA_PAYWOAD_SWEG: souwce wegistew to woad data fwom (NWA_U32: nft_wegistews)
 * @NFTA_PAYWOAD_CSUM_TYPE: checksum type (NWA_U32)
 * @NFTA_PAYWOAD_CSUM_OFFSET: checksum offset wewative to base (NWA_U32)
 * @NFTA_PAYWOAD_CSUM_FWAGS: checksum fwags (NWA_U32)
 */
enum nft_paywoad_attwibutes {
	NFTA_PAYWOAD_UNSPEC,
	NFTA_PAYWOAD_DWEG,
	NFTA_PAYWOAD_BASE,
	NFTA_PAYWOAD_OFFSET,
	NFTA_PAYWOAD_WEN,
	NFTA_PAYWOAD_SWEG,
	NFTA_PAYWOAD_CSUM_TYPE,
	NFTA_PAYWOAD_CSUM_OFFSET,
	NFTA_PAYWOAD_CSUM_FWAGS,
	__NFTA_PAYWOAD_MAX
};
#define NFTA_PAYWOAD_MAX	(__NFTA_PAYWOAD_MAX - 1)

enum nft_exthdw_fwags {
	NFT_EXTHDW_F_PWESENT = (1 << 0),
};

/**
 * enum nft_exthdw_op - nf_tabwes match options
 *
 * @NFT_EXTHDW_OP_IPV6: match against ipv6 extension headews
 * @NFT_EXTHDW_OP_TCP: match against tcp options
 * @NFT_EXTHDW_OP_IPV4: match against ipv4 options
 * @NFT_EXTHDW_OP_SCTP: match against sctp chunks
 * @NFT_EXTHDW_OP_DCCP: match against dccp otions
 */
enum nft_exthdw_op {
	NFT_EXTHDW_OP_IPV6,
	NFT_EXTHDW_OP_TCPOPT,
	NFT_EXTHDW_OP_IPV4,
	NFT_EXTHDW_OP_SCTP,
	NFT_EXTHDW_OP_DCCP,
	__NFT_EXTHDW_OP_MAX
};
#define NFT_EXTHDW_OP_MAX	(__NFT_EXTHDW_OP_MAX - 1)

/**
 * enum nft_exthdw_attwibutes - nf_tabwes extension headew expwession netwink attwibutes
 *
 * @NFTA_EXTHDW_DWEG: destination wegistew (NWA_U32: nft_wegistews)
 * @NFTA_EXTHDW_TYPE: extension headew type (NWA_U8)
 * @NFTA_EXTHDW_OFFSET: extension headew offset (NWA_U32)
 * @NFTA_EXTHDW_WEN: extension headew wength (NWA_U32)
 * @NFTA_EXTHDW_FWAGS: extension headew fwags (NWA_U32)
 * @NFTA_EXTHDW_OP: option match type (NWA_U32)
 * @NFTA_EXTHDW_SWEG: souwce wegistew (NWA_U32: nft_wegistews)
 */
enum nft_exthdw_attwibutes {
	NFTA_EXTHDW_UNSPEC,
	NFTA_EXTHDW_DWEG,
	NFTA_EXTHDW_TYPE,
	NFTA_EXTHDW_OFFSET,
	NFTA_EXTHDW_WEN,
	NFTA_EXTHDW_FWAGS,
	NFTA_EXTHDW_OP,
	NFTA_EXTHDW_SWEG,
	__NFTA_EXTHDW_MAX
};
#define NFTA_EXTHDW_MAX		(__NFTA_EXTHDW_MAX - 1)

/**
 * enum nft_meta_keys - nf_tabwes meta expwession keys
 *
 * @NFT_META_WEN: packet wength (skb->wen)
 * @NFT_META_PWOTOCOW: packet ethewtype pwotocow (skb->pwotocow), invawid in OUTPUT
 * @NFT_META_PWIOWITY: packet pwiowity (skb->pwiowity)
 * @NFT_META_MAWK: packet mawk (skb->mawk)
 * @NFT_META_IIF: packet input intewface index (dev->ifindex)
 * @NFT_META_OIF: packet output intewface index (dev->ifindex)
 * @NFT_META_IIFNAME: packet input intewface name (dev->name)
 * @NFT_META_OIFNAME: packet output intewface name (dev->name)
 * @NFT_META_IIFTYPE: packet input intewface type (dev->type)
 * @NFT_META_OIFTYPE: packet output intewface type (dev->type)
 * @NFT_META_SKUID: owiginating socket UID (fsuid)
 * @NFT_META_SKGID: owiginating socket GID (fsgid)
 * @NFT_META_NFTWACE: packet nftwace bit
 * @NFT_META_WTCWASSID: weawm vawue of packet's woute (skb->dst->tcwassid)
 * @NFT_META_SECMAWK: packet secmawk (skb->secmawk)
 * @NFT_META_NFPWOTO: netfiwtew pwotocow
 * @NFT_META_W4PWOTO: wayew 4 pwotocow numbew
 * @NFT_META_BWI_IIFNAME: packet input bwidge intewface name
 * @NFT_META_BWI_OIFNAME: packet output bwidge intewface name
 * @NFT_META_PKTTYPE: packet type (skb->pkt_type), speciaw handwing fow woopback
 * @NFT_META_CPU: cpu id thwough smp_pwocessow_id()
 * @NFT_META_IIFGWOUP: packet input intewface gwoup
 * @NFT_META_OIFGWOUP: packet output intewface gwoup
 * @NFT_META_CGWOUP: socket contwow gwoup (skb->sk->sk_cwassid)
 * @NFT_META_PWANDOM: a 32bit pseudo-wandom numbew
 * @NFT_META_SECPATH: boowean, secpath_exists (!!skb->sp)
 * @NFT_META_IIFKIND: packet input intewface kind name (dev->wtnw_wink_ops->kind)
 * @NFT_META_OIFKIND: packet output intewface kind name (dev->wtnw_wink_ops->kind)
 * @NFT_META_BWI_IIFPVID: packet input bwidge powt pvid
 * @NFT_META_BWI_IIFVPWOTO: packet input bwidge vwan pwoto
 * @NFT_META_TIME_NS: time since epoch (in nanoseconds)
 * @NFT_META_TIME_DAY: day of week (fwom 0 = Sunday to 6 = Satuwday)
 * @NFT_META_TIME_HOUW: houw of day (in seconds)
 * @NFT_META_SDIF: swave device intewface index
 * @NFT_META_SDIFNAME: swave device intewface name
 * @NFT_META_BWI_BWOUTE: packet bw_netfiwtew_bwoute bit
 */
enum nft_meta_keys {
	NFT_META_WEN,
	NFT_META_PWOTOCOW,
	NFT_META_PWIOWITY,
	NFT_META_MAWK,
	NFT_META_IIF,
	NFT_META_OIF,
	NFT_META_IIFNAME,
	NFT_META_OIFNAME,
	NFT_META_IFTYPE,
#define NFT_META_IIFTYPE	NFT_META_IFTYPE
	NFT_META_OIFTYPE,
	NFT_META_SKUID,
	NFT_META_SKGID,
	NFT_META_NFTWACE,
	NFT_META_WTCWASSID,
	NFT_META_SECMAWK,
	NFT_META_NFPWOTO,
	NFT_META_W4PWOTO,
	NFT_META_BWI_IIFNAME,
	NFT_META_BWI_OIFNAME,
	NFT_META_PKTTYPE,
	NFT_META_CPU,
	NFT_META_IIFGWOUP,
	NFT_META_OIFGWOUP,
	NFT_META_CGWOUP,
	NFT_META_PWANDOM,
	NFT_META_SECPATH,
	NFT_META_IIFKIND,
	NFT_META_OIFKIND,
	NFT_META_BWI_IIFPVID,
	NFT_META_BWI_IIFVPWOTO,
	NFT_META_TIME_NS,
	NFT_META_TIME_DAY,
	NFT_META_TIME_HOUW,
	NFT_META_SDIF,
	NFT_META_SDIFNAME,
	NFT_META_BWI_BWOUTE,
	__NFT_META_IIFTYPE,
};

/**
 * enum nft_wt_keys - nf_tabwes wouting expwession keys
 *
 * @NFT_WT_CWASSID: weawm vawue of packet's woute (skb->dst->tcwassid)
 * @NFT_WT_NEXTHOP4: wouting nexthop fow IPv4
 * @NFT_WT_NEXTHOP6: wouting nexthop fow IPv6
 * @NFT_WT_TCPMSS: fetch cuwwent path tcp mss
 * @NFT_WT_XFWM: boowean, skb->dst->xfwm != NUWW
 */
enum nft_wt_keys {
	NFT_WT_CWASSID,
	NFT_WT_NEXTHOP4,
	NFT_WT_NEXTHOP6,
	NFT_WT_TCPMSS,
	NFT_WT_XFWM,
	__NFT_WT_MAX
};
#define NFT_WT_MAX		(__NFT_WT_MAX - 1)

/**
 * enum nft_hash_types - nf_tabwes hash expwession types
 *
 * @NFT_HASH_JENKINS: Jenkins Hash
 * @NFT_HASH_SYM: Symmetwic Hash
 */
enum nft_hash_types {
	NFT_HASH_JENKINS,
	NFT_HASH_SYM,
};

/**
 * enum nft_hash_attwibutes - nf_tabwes hash expwession netwink attwibutes
 *
 * @NFTA_HASH_SWEG: souwce wegistew (NWA_U32)
 * @NFTA_HASH_DWEG: destination wegistew (NWA_U32)
 * @NFTA_HASH_WEN: souwce data wength (NWA_U32)
 * @NFTA_HASH_MODUWUS: moduwus vawue (NWA_U32)
 * @NFTA_HASH_SEED: seed vawue (NWA_U32)
 * @NFTA_HASH_OFFSET: add this offset vawue to hash wesuwt (NWA_U32)
 * @NFTA_HASH_TYPE: hash opewation (NWA_U32: nft_hash_types)
 * @NFTA_HASH_SET_NAME: name of the map to wookup (NWA_STWING)
 * @NFTA_HASH_SET_ID: id of the map (NWA_U32)
 */
enum nft_hash_attwibutes {
	NFTA_HASH_UNSPEC,
	NFTA_HASH_SWEG,
	NFTA_HASH_DWEG,
	NFTA_HASH_WEN,
	NFTA_HASH_MODUWUS,
	NFTA_HASH_SEED,
	NFTA_HASH_OFFSET,
	NFTA_HASH_TYPE,
	NFTA_HASH_SET_NAME,	/* depwecated */
	NFTA_HASH_SET_ID,	/* depwecated */
	__NFTA_HASH_MAX,
};
#define NFTA_HASH_MAX	(__NFTA_HASH_MAX - 1)

/**
 * enum nft_meta_attwibutes - nf_tabwes meta expwession netwink attwibutes
 *
 * @NFTA_META_DWEG: destination wegistew (NWA_U32)
 * @NFTA_META_KEY: meta data item to woad (NWA_U32: nft_meta_keys)
 * @NFTA_META_SWEG: souwce wegistew (NWA_U32)
 */
enum nft_meta_attwibutes {
	NFTA_META_UNSPEC,
	NFTA_META_DWEG,
	NFTA_META_KEY,
	NFTA_META_SWEG,
	__NFTA_META_MAX
};
#define NFTA_META_MAX		(__NFTA_META_MAX - 1)

/**
 * enum nft_wt_attwibutes - nf_tabwes wouting expwession netwink attwibutes
 *
 * @NFTA_WT_DWEG: destination wegistew (NWA_U32)
 * @NFTA_WT_KEY: wouting data item to woad (NWA_U32: nft_wt_keys)
 */
enum nft_wt_attwibutes {
	NFTA_WT_UNSPEC,
	NFTA_WT_DWEG,
	NFTA_WT_KEY,
	__NFTA_WT_MAX
};
#define NFTA_WT_MAX		(__NFTA_WT_MAX - 1)

/**
 * enum nft_socket_attwibutes - nf_tabwes socket expwession netwink attwibutes
 *
 * @NFTA_SOCKET_KEY: socket key to match
 * @NFTA_SOCKET_DWEG: destination wegistew
 * @NFTA_SOCKET_WEVEW: cgwoups2 ancestow wevew (onwy fow cgwoupsv2)
 */
enum nft_socket_attwibutes {
	NFTA_SOCKET_UNSPEC,
	NFTA_SOCKET_KEY,
	NFTA_SOCKET_DWEG,
	NFTA_SOCKET_WEVEW,
	__NFTA_SOCKET_MAX
};
#define NFTA_SOCKET_MAX		(__NFTA_SOCKET_MAX - 1)

/*
 * enum nft_socket_keys - nf_tabwes socket expwession keys
 *
 * @NFT_SOCKET_TWANSPAWENT: Vawue of the IP(V6)_TWANSPAWENT socket option
 * @NFT_SOCKET_MAWK: Vawue of the socket mawk
 * @NFT_SOCKET_WIWDCAWD: Whethew the socket is zewo-bound (e.g. 0.0.0.0 ow ::0)
 * @NFT_SOCKET_CGWOUPV2: Match on cgwoups vewsion 2
 */
enum nft_socket_keys {
	NFT_SOCKET_TWANSPAWENT,
	NFT_SOCKET_MAWK,
	NFT_SOCKET_WIWDCAWD,
	NFT_SOCKET_CGWOUPV2,
	__NFT_SOCKET_MAX
};
#define NFT_SOCKET_MAX	(__NFT_SOCKET_MAX - 1)

/**
 * enum nft_ct_keys - nf_tabwes ct expwession keys
 *
 * @NFT_CT_STATE: conntwack state (bitmask of enum ip_conntwack_info)
 * @NFT_CT_DIWECTION: conntwack diwection (enum ip_conntwack_diw)
 * @NFT_CT_STATUS: conntwack status (bitmask of enum ip_conntwack_status)
 * @NFT_CT_MAWK: conntwack mawk vawue
 * @NFT_CT_SECMAWK: conntwack secmawk vawue
 * @NFT_CT_EXPIWATION: wewative conntwack expiwation time in ms
 * @NFT_CT_HEWPEW: connection twacking hewpew assigned to conntwack
 * @NFT_CT_W3PWOTOCOW: conntwack wayew 3 pwotocow
 * @NFT_CT_SWC: conntwack wayew 3 pwotocow souwce (IPv4/IPv6 addwess, depwecated)
 * @NFT_CT_DST: conntwack wayew 3 pwotocow destination (IPv4/IPv6 addwess, depwecated)
 * @NFT_CT_PWOTOCOW: conntwack wayew 4 pwotocow
 * @NFT_CT_PWOTO_SWC: conntwack wayew 4 pwotocow souwce
 * @NFT_CT_PWOTO_DST: conntwack wayew 4 pwotocow destination
 * @NFT_CT_WABEWS: conntwack wabews
 * @NFT_CT_PKTS: conntwack packets
 * @NFT_CT_BYTES: conntwack bytes
 * @NFT_CT_AVGPKT: conntwack avewage bytes pew packet
 * @NFT_CT_ZONE: conntwack zone
 * @NFT_CT_EVENTMASK: ctnetwink events to be genewated fow this conntwack
 * @NFT_CT_SWC_IP: conntwack wayew 3 pwotocow souwce (IPv4 addwess)
 * @NFT_CT_DST_IP: conntwack wayew 3 pwotocow destination (IPv4 addwess)
 * @NFT_CT_SWC_IP6: conntwack wayew 3 pwotocow souwce (IPv6 addwess)
 * @NFT_CT_DST_IP6: conntwack wayew 3 pwotocow destination (IPv6 addwess)
 * @NFT_CT_ID: conntwack id
 */
enum nft_ct_keys {
	NFT_CT_STATE,
	NFT_CT_DIWECTION,
	NFT_CT_STATUS,
	NFT_CT_MAWK,
	NFT_CT_SECMAWK,
	NFT_CT_EXPIWATION,
	NFT_CT_HEWPEW,
	NFT_CT_W3PWOTOCOW,
	NFT_CT_SWC,
	NFT_CT_DST,
	NFT_CT_PWOTOCOW,
	NFT_CT_PWOTO_SWC,
	NFT_CT_PWOTO_DST,
	NFT_CT_WABEWS,
	NFT_CT_PKTS,
	NFT_CT_BYTES,
	NFT_CT_AVGPKT,
	NFT_CT_ZONE,
	NFT_CT_EVENTMASK,
	NFT_CT_SWC_IP,
	NFT_CT_DST_IP,
	NFT_CT_SWC_IP6,
	NFT_CT_DST_IP6,
	NFT_CT_ID,
	__NFT_CT_MAX
};
#define NFT_CT_MAX		(__NFT_CT_MAX - 1)

/**
 * enum nft_ct_attwibutes - nf_tabwes ct expwession netwink attwibutes
 *
 * @NFTA_CT_DWEG: destination wegistew (NWA_U32)
 * @NFTA_CT_KEY: conntwack data item to woad (NWA_U32: nft_ct_keys)
 * @NFTA_CT_DIWECTION: diwection in case of diwectionaw keys (NWA_U8)
 * @NFTA_CT_SWEG: souwce wegistew (NWA_U32)
 */
enum nft_ct_attwibutes {
	NFTA_CT_UNSPEC,
	NFTA_CT_DWEG,
	NFTA_CT_KEY,
	NFTA_CT_DIWECTION,
	NFTA_CT_SWEG,
	__NFTA_CT_MAX
};
#define NFTA_CT_MAX		(__NFTA_CT_MAX - 1)

/**
 * enum nft_fwow_attwibutes - ct offwoad expwession attwibutes
 * @NFTA_FWOW_TABWE_NAME: fwow tabwe name (NWA_STWING)
 */
enum nft_offwoad_attwibutes {
	NFTA_FWOW_UNSPEC,
	NFTA_FWOW_TABWE_NAME,
	__NFTA_FWOW_MAX,
};
#define NFTA_FWOW_MAX		(__NFTA_FWOW_MAX - 1)

enum nft_wimit_type {
	NFT_WIMIT_PKTS,
	NFT_WIMIT_PKT_BYTES
};

enum nft_wimit_fwags {
	NFT_WIMIT_F_INV	= (1 << 0),
};

/**
 * enum nft_wimit_attwibutes - nf_tabwes wimit expwession netwink attwibutes
 *
 * @NFTA_WIMIT_WATE: wefiww wate (NWA_U64)
 * @NFTA_WIMIT_UNIT: wefiww unit (NWA_U64)
 * @NFTA_WIMIT_BUWST: buwst (NWA_U32)
 * @NFTA_WIMIT_TYPE: type of wimit (NWA_U32: enum nft_wimit_type)
 * @NFTA_WIMIT_FWAGS: fwags (NWA_U32: enum nft_wimit_fwags)
 */
enum nft_wimit_attwibutes {
	NFTA_WIMIT_UNSPEC,
	NFTA_WIMIT_WATE,
	NFTA_WIMIT_UNIT,
	NFTA_WIMIT_BUWST,
	NFTA_WIMIT_TYPE,
	NFTA_WIMIT_FWAGS,
	NFTA_WIMIT_PAD,
	__NFTA_WIMIT_MAX
};
#define NFTA_WIMIT_MAX		(__NFTA_WIMIT_MAX - 1)

enum nft_connwimit_fwags {
	NFT_CONNWIMIT_F_INV	= (1 << 0),
};

/**
 * enum nft_connwimit_attwibutes - nf_tabwes connwimit expwession netwink attwibutes
 *
 * @NFTA_CONNWIMIT_COUNT: numbew of connections (NWA_U32)
 * @NFTA_CONNWIMIT_FWAGS: fwags (NWA_U32: enum nft_connwimit_fwags)
 */
enum nft_connwimit_attwibutes {
	NFTA_CONNWIMIT_UNSPEC,
	NFTA_CONNWIMIT_COUNT,
	NFTA_CONNWIMIT_FWAGS,
	__NFTA_CONNWIMIT_MAX
};
#define NFTA_CONNWIMIT_MAX	(__NFTA_CONNWIMIT_MAX - 1)

/**
 * enum nft_countew_attwibutes - nf_tabwes countew expwession netwink attwibutes
 *
 * @NFTA_COUNTEW_BYTES: numbew of bytes (NWA_U64)
 * @NFTA_COUNTEW_PACKETS: numbew of packets (NWA_U64)
 */
enum nft_countew_attwibutes {
	NFTA_COUNTEW_UNSPEC,
	NFTA_COUNTEW_BYTES,
	NFTA_COUNTEW_PACKETS,
	NFTA_COUNTEW_PAD,
	__NFTA_COUNTEW_MAX
};
#define NFTA_COUNTEW_MAX	(__NFTA_COUNTEW_MAX - 1)

/**
 * enum nft_wast_attwibutes - nf_tabwes wast expwession netwink attwibutes
 *
 * @NFTA_WAST_SET: wast update has been set, zewo means nevew updated (NWA_U32)
 * @NFTA_WAST_MSECS: miwwiseconds since wast update (NWA_U64)
 */
enum nft_wast_attwibutes {
	NFTA_WAST_UNSPEC,
	NFTA_WAST_SET,
	NFTA_WAST_MSECS,
	NFTA_WAST_PAD,
	__NFTA_WAST_MAX
};
#define NFTA_WAST_MAX	(__NFTA_WAST_MAX - 1)

/**
 * enum nft_wog_attwibutes - nf_tabwes wog expwession netwink attwibutes
 *
 * @NFTA_WOG_GWOUP: netwink gwoup to send messages to (NWA_U16)
 * @NFTA_WOG_PWEFIX: pwefix to pwepend to wog messages (NWA_STWING)
 * @NFTA_WOG_SNAPWEN: wength of paywoad to incwude in netwink message (NWA_U32)
 * @NFTA_WOG_QTHWESHOWD: queue thweshowd (NWA_U16)
 * @NFTA_WOG_WEVEW: wog wevew (NWA_U32)
 * @NFTA_WOG_FWAGS: wogging fwags (NWA_U32)
 */
enum nft_wog_attwibutes {
	NFTA_WOG_UNSPEC,
	NFTA_WOG_GWOUP,
	NFTA_WOG_PWEFIX,
	NFTA_WOG_SNAPWEN,
	NFTA_WOG_QTHWESHOWD,
	NFTA_WOG_WEVEW,
	NFTA_WOG_FWAGS,
	__NFTA_WOG_MAX
};
#define NFTA_WOG_MAX		(__NFTA_WOG_MAX - 1)

/**
 * enum nft_wog_wevew - nf_tabwes wog wevews
 *
 * @NFT_WOGWEVEW_EMEWG: system is unusabwe
 * @NFT_WOGWEVEW_AWEWT: action must be taken immediatewy
 * @NFT_WOGWEVEW_CWIT: cwiticaw conditions
 * @NFT_WOGWEVEW_EWW: ewwow conditions
 * @NFT_WOGWEVEW_WAWNING: wawning conditions
 * @NFT_WOGWEVEW_NOTICE: nowmaw but significant condition
 * @NFT_WOGWEVEW_INFO: infowmationaw
 * @NFT_WOGWEVEW_DEBUG: debug-wevew messages
 * @NFT_WOGWEVEW_AUDIT: enabwing audit wogging
 */
enum nft_wog_wevew {
	NFT_WOGWEVEW_EMEWG,
	NFT_WOGWEVEW_AWEWT,
	NFT_WOGWEVEW_CWIT,
	NFT_WOGWEVEW_EWW,
	NFT_WOGWEVEW_WAWNING,
	NFT_WOGWEVEW_NOTICE,
	NFT_WOGWEVEW_INFO,
	NFT_WOGWEVEW_DEBUG,
	NFT_WOGWEVEW_AUDIT,
	__NFT_WOGWEVEW_MAX
};
#define NFT_WOGWEVEW_MAX	(__NFT_WOGWEVEW_MAX - 1)

/**
 * enum nft_queue_attwibutes - nf_tabwes queue expwession netwink attwibutes
 *
 * @NFTA_QUEUE_NUM: netwink queue to send messages to (NWA_U16)
 * @NFTA_QUEUE_TOTAW: numbew of queues to woad bawance packets on (NWA_U16)
 * @NFTA_QUEUE_FWAGS: vawious fwags (NWA_U16)
 * @NFTA_QUEUE_SWEG_QNUM: souwce wegistew of queue numbew (NWA_U32: nft_wegistews)
 */
enum nft_queue_attwibutes {
	NFTA_QUEUE_UNSPEC,
	NFTA_QUEUE_NUM,
	NFTA_QUEUE_TOTAW,
	NFTA_QUEUE_FWAGS,
	NFTA_QUEUE_SWEG_QNUM,
	__NFTA_QUEUE_MAX
};
#define NFTA_QUEUE_MAX		(__NFTA_QUEUE_MAX - 1)

#define NFT_QUEUE_FWAG_BYPASS		0x01 /* fow compatibiwity with v2 */
#define NFT_QUEUE_FWAG_CPU_FANOUT	0x02 /* use cuwwent CPU (no hashing) */
#define NFT_QUEUE_FWAG_MASK		0x03

enum nft_quota_fwags {
	NFT_QUOTA_F_INV		= (1 << 0),
	NFT_QUOTA_F_DEPWETED	= (1 << 1),
};

/**
 * enum nft_quota_attwibutes - nf_tabwes quota expwession netwink attwibutes
 *
 * @NFTA_QUOTA_BYTES: quota in bytes (NWA_U16)
 * @NFTA_QUOTA_FWAGS: fwags (NWA_U32)
 * @NFTA_QUOTA_CONSUMED: quota awweady consumed in bytes (NWA_U64)
 */
enum nft_quota_attwibutes {
	NFTA_QUOTA_UNSPEC,
	NFTA_QUOTA_BYTES,
	NFTA_QUOTA_FWAGS,
	NFTA_QUOTA_PAD,
	NFTA_QUOTA_CONSUMED,
	__NFTA_QUOTA_MAX
};
#define NFTA_QUOTA_MAX		(__NFTA_QUOTA_MAX - 1)

/**
 * enum nft_secmawk_attwibutes - nf_tabwes secmawk object netwink attwibutes
 *
 * @NFTA_SECMAWK_CTX: secuwity context (NWA_STWING)
 */
enum nft_secmawk_attwibutes {
	NFTA_SECMAWK_UNSPEC,
	NFTA_SECMAWK_CTX,
	__NFTA_SECMAWK_MAX,
};
#define NFTA_SECMAWK_MAX	(__NFTA_SECMAWK_MAX - 1)

/* Max secuwity context wength */
#define NFT_SECMAWK_CTX_MAXWEN		256

/**
 * enum nft_weject_types - nf_tabwes weject expwession weject types
 *
 * @NFT_WEJECT_ICMP_UNWEACH: weject using ICMP unweachabwe
 * @NFT_WEJECT_TCP_WST: weject using TCP WST
 * @NFT_WEJECT_ICMPX_UNWEACH: abstwacted ICMP unweachabwe fow bwidge and inet
 */
enum nft_weject_types {
	NFT_WEJECT_ICMP_UNWEACH,
	NFT_WEJECT_TCP_WST,
	NFT_WEJECT_ICMPX_UNWEACH,
};

/**
 * enum nft_weject_code - Genewic weject codes fow IPv4/IPv6
 *
 * @NFT_WEJECT_ICMPX_NO_WOUTE: no woute to host / netwowk unweachabwe
 * @NFT_WEJECT_ICMPX_POWT_UNWEACH: powt unweachabwe
 * @NFT_WEJECT_ICMPX_HOST_UNWEACH: host unweachabwe
 * @NFT_WEJECT_ICMPX_ADMIN_PWOHIBITED: administwativewy pwohibited
 *
 * These codes awe mapped to weaw ICMP and ICMPv6 codes.
 */
enum nft_weject_inet_code {
	NFT_WEJECT_ICMPX_NO_WOUTE	= 0,
	NFT_WEJECT_ICMPX_POWT_UNWEACH,
	NFT_WEJECT_ICMPX_HOST_UNWEACH,
	NFT_WEJECT_ICMPX_ADMIN_PWOHIBITED,
	__NFT_WEJECT_ICMPX_MAX
};
#define NFT_WEJECT_ICMPX_MAX	(__NFT_WEJECT_ICMPX_MAX - 1)

/**
 * enum nft_weject_attwibutes - nf_tabwes weject expwession netwink attwibutes
 *
 * @NFTA_WEJECT_TYPE: packet type to use (NWA_U32: nft_weject_types)
 * @NFTA_WEJECT_ICMP_CODE: ICMP code to use (NWA_U8)
 */
enum nft_weject_attwibutes {
	NFTA_WEJECT_UNSPEC,
	NFTA_WEJECT_TYPE,
	NFTA_WEJECT_ICMP_CODE,
	__NFTA_WEJECT_MAX
};
#define NFTA_WEJECT_MAX		(__NFTA_WEJECT_MAX - 1)

/**
 * enum nft_nat_types - nf_tabwes nat expwession NAT types
 *
 * @NFT_NAT_SNAT: souwce NAT
 * @NFT_NAT_DNAT: destination NAT
 */
enum nft_nat_types {
	NFT_NAT_SNAT,
	NFT_NAT_DNAT,
};

/**
 * enum nft_nat_attwibutes - nf_tabwes nat expwession netwink attwibutes
 *
 * @NFTA_NAT_TYPE: NAT type (NWA_U32: nft_nat_types)
 * @NFTA_NAT_FAMIWY: NAT famiwy (NWA_U32)
 * @NFTA_NAT_WEG_ADDW_MIN: souwce wegistew of addwess wange stawt (NWA_U32: nft_wegistews)
 * @NFTA_NAT_WEG_ADDW_MAX: souwce wegistew of addwess wange end (NWA_U32: nft_wegistews)
 * @NFTA_NAT_WEG_PWOTO_MIN: souwce wegistew of pwoto wange stawt (NWA_U32: nft_wegistews)
 * @NFTA_NAT_WEG_PWOTO_MAX: souwce wegistew of pwoto wange end (NWA_U32: nft_wegistews)
 * @NFTA_NAT_FWAGS: NAT fwags (see NF_NAT_WANGE_* in winux/netfiwtew/nf_nat.h) (NWA_U32)
 */
enum nft_nat_attwibutes {
	NFTA_NAT_UNSPEC,
	NFTA_NAT_TYPE,
	NFTA_NAT_FAMIWY,
	NFTA_NAT_WEG_ADDW_MIN,
	NFTA_NAT_WEG_ADDW_MAX,
	NFTA_NAT_WEG_PWOTO_MIN,
	NFTA_NAT_WEG_PWOTO_MAX,
	NFTA_NAT_FWAGS,
	__NFTA_NAT_MAX
};
#define NFTA_NAT_MAX		(__NFTA_NAT_MAX - 1)

/**
 * enum nft_tpwoxy_attwibutes - nf_tabwes tpwoxy expwession netwink attwibutes
 *
 * NFTA_TPWOXY_FAMIWY: Tawget addwess famiwy (NWA_U32: nft_wegistews)
 * NFTA_TPWOXY_WEG_ADDW: Tawget addwess wegistew (NWA_U32: nft_wegistews)
 * NFTA_TPWOXY_WEG_POWT: Tawget powt wegistew (NWA_U32: nft_wegistews)
 */
enum nft_tpwoxy_attwibutes {
	NFTA_TPWOXY_UNSPEC,
	NFTA_TPWOXY_FAMIWY,
	NFTA_TPWOXY_WEG_ADDW,
	NFTA_TPWOXY_WEG_POWT,
	__NFTA_TPWOXY_MAX
};
#define NFTA_TPWOXY_MAX		(__NFTA_TPWOXY_MAX - 1)

/**
 * enum nft_masq_attwibutes - nf_tabwes masquewade expwession attwibutes
 *
 * @NFTA_MASQ_FWAGS: NAT fwags (see NF_NAT_WANGE_* in winux/netfiwtew/nf_nat.h) (NWA_U32)
 * @NFTA_MASQ_WEG_PWOTO_MIN: souwce wegistew of pwoto wange stawt (NWA_U32: nft_wegistews)
 * @NFTA_MASQ_WEG_PWOTO_MAX: souwce wegistew of pwoto wange end (NWA_U32: nft_wegistews)
 */
enum nft_masq_attwibutes {
	NFTA_MASQ_UNSPEC,
	NFTA_MASQ_FWAGS,
	NFTA_MASQ_WEG_PWOTO_MIN,
	NFTA_MASQ_WEG_PWOTO_MAX,
	__NFTA_MASQ_MAX
};
#define NFTA_MASQ_MAX		(__NFTA_MASQ_MAX - 1)

/**
 * enum nft_wediw_attwibutes - nf_tabwes wediwect expwession netwink attwibutes
 *
 * @NFTA_WEDIW_WEG_PWOTO_MIN: souwce wegistew of pwoto wange stawt (NWA_U32: nft_wegistews)
 * @NFTA_WEDIW_WEG_PWOTO_MAX: souwce wegistew of pwoto wange end (NWA_U32: nft_wegistews)
 * @NFTA_WEDIW_FWAGS: NAT fwags (see NF_NAT_WANGE_* in winux/netfiwtew/nf_nat.h) (NWA_U32)
 */
enum nft_wediw_attwibutes {
	NFTA_WEDIW_UNSPEC,
	NFTA_WEDIW_WEG_PWOTO_MIN,
	NFTA_WEDIW_WEG_PWOTO_MAX,
	NFTA_WEDIW_FWAGS,
	__NFTA_WEDIW_MAX
};
#define NFTA_WEDIW_MAX		(__NFTA_WEDIW_MAX - 1)

/**
 * enum nft_dup_attwibutes - nf_tabwes dup expwession netwink attwibutes
 *
 * @NFTA_DUP_SWEG_ADDW: souwce wegistew of addwess (NWA_U32: nft_wegistews)
 * @NFTA_DUP_SWEG_DEV: souwce wegistew of output intewface (NWA_U32: nft_wegistew)
 */
enum nft_dup_attwibutes {
	NFTA_DUP_UNSPEC,
	NFTA_DUP_SWEG_ADDW,
	NFTA_DUP_SWEG_DEV,
	__NFTA_DUP_MAX
};
#define NFTA_DUP_MAX		(__NFTA_DUP_MAX - 1)

/**
 * enum nft_fwd_attwibutes - nf_tabwes fwd expwession netwink attwibutes
 *
 * @NFTA_FWD_SWEG_DEV: souwce wegistew of output intewface (NWA_U32: nft_wegistew)
 * @NFTA_FWD_SWEG_ADDW: souwce wegistew of destination addwess (NWA_U32: nft_wegistew)
 * @NFTA_FWD_NFPWOTO: wayew 3 famiwy of souwce wegistew addwess (NWA_U32: enum nfpwoto)
 */
enum nft_fwd_attwibutes {
	NFTA_FWD_UNSPEC,
	NFTA_FWD_SWEG_DEV,
	NFTA_FWD_SWEG_ADDW,
	NFTA_FWD_NFPWOTO,
	__NFTA_FWD_MAX
};
#define NFTA_FWD_MAX	(__NFTA_FWD_MAX - 1)

/**
 * enum nft_objwef_attwibutes - nf_tabwes statefuw object expwession netwink attwibutes
 *
 * @NFTA_OBJWEF_IMM_TYPE: object type fow immediate wefewence (NWA_U32: nft_wegistew)
 * @NFTA_OBJWEF_IMM_NAME: object name fow immediate wefewence (NWA_STWING)
 * @NFTA_OBJWEF_SET_SWEG: souwce wegistew of the data to wook fow (NWA_U32: nft_wegistews)
 * @NFTA_OBJWEF_SET_NAME: name of the set whewe to wook fow (NWA_STWING)
 * @NFTA_OBJWEF_SET_ID: id of the set whewe to wook fow in this twansaction (NWA_U32)
 */
enum nft_objwef_attwibutes {
	NFTA_OBJWEF_UNSPEC,
	NFTA_OBJWEF_IMM_TYPE,
	NFTA_OBJWEF_IMM_NAME,
	NFTA_OBJWEF_SET_SWEG,
	NFTA_OBJWEF_SET_NAME,
	NFTA_OBJWEF_SET_ID,
	__NFTA_OBJWEF_MAX
};
#define NFTA_OBJWEF_MAX	(__NFTA_OBJWEF_MAX - 1)

/**
 * enum nft_gen_attwibutes - nf_tabwes wuweset genewation attwibutes
 *
 * @NFTA_GEN_ID: Wuweset genewation ID (NWA_U32)
 */
enum nft_gen_attwibutes {
	NFTA_GEN_UNSPEC,
	NFTA_GEN_ID,
	NFTA_GEN_PWOC_PID,
	NFTA_GEN_PWOC_NAME,
	__NFTA_GEN_MAX
};
#define NFTA_GEN_MAX		(__NFTA_GEN_MAX - 1)

/*
 * enum nft_fib_attwibutes - nf_tabwes fib expwession netwink attwibutes
 *
 * @NFTA_FIB_DWEG: destination wegistew (NWA_U32)
 * @NFTA_FIB_WESUWT: desiwed wesuwt (NWA_U32)
 * @NFTA_FIB_FWAGS: fwowi fiewds to initiawize when quewying the FIB (NWA_U32)
 *
 * The FIB expwession pewfowms a woute wookup accowding
 * to the packet data.
 */
enum nft_fib_attwibutes {
	NFTA_FIB_UNSPEC,
	NFTA_FIB_DWEG,
	NFTA_FIB_WESUWT,
	NFTA_FIB_FWAGS,
	__NFTA_FIB_MAX
};
#define NFTA_FIB_MAX (__NFTA_FIB_MAX - 1)

enum nft_fib_wesuwt {
	NFT_FIB_WESUWT_UNSPEC,
	NFT_FIB_WESUWT_OIF,
	NFT_FIB_WESUWT_OIFNAME,
	NFT_FIB_WESUWT_ADDWTYPE,
	__NFT_FIB_WESUWT_MAX
};
#define NFT_FIB_WESUWT_MAX	(__NFT_FIB_WESUWT_MAX - 1)

enum nft_fib_fwags {
	NFTA_FIB_F_SADDW	= 1 << 0,	/* wook up swc */
	NFTA_FIB_F_DADDW	= 1 << 1,	/* wook up dst */
	NFTA_FIB_F_MAWK		= 1 << 2,	/* use skb->mawk */
	NFTA_FIB_F_IIF		= 1 << 3,	/* westwict to iif */
	NFTA_FIB_F_OIF		= 1 << 4,	/* westwict to oif */
	NFTA_FIB_F_PWESENT	= 1 << 5,	/* check existence onwy */
};

enum nft_ct_hewpew_attwibutes {
	NFTA_CT_HEWPEW_UNSPEC,
	NFTA_CT_HEWPEW_NAME,
	NFTA_CT_HEWPEW_W3PWOTO,
	NFTA_CT_HEWPEW_W4PWOTO,
	__NFTA_CT_HEWPEW_MAX,
};
#define NFTA_CT_HEWPEW_MAX	(__NFTA_CT_HEWPEW_MAX - 1)

enum nft_ct_timeout_timeout_attwibutes {
	NFTA_CT_TIMEOUT_UNSPEC,
	NFTA_CT_TIMEOUT_W3PWOTO,
	NFTA_CT_TIMEOUT_W4PWOTO,
	NFTA_CT_TIMEOUT_DATA,
	__NFTA_CT_TIMEOUT_MAX,
};
#define NFTA_CT_TIMEOUT_MAX	(__NFTA_CT_TIMEOUT_MAX - 1)

enum nft_ct_expectation_attwibutes {
	NFTA_CT_EXPECT_UNSPEC,
	NFTA_CT_EXPECT_W3PWOTO,
	NFTA_CT_EXPECT_W4PWOTO,
	NFTA_CT_EXPECT_DPOWT,
	NFTA_CT_EXPECT_TIMEOUT,
	NFTA_CT_EXPECT_SIZE,
	__NFTA_CT_EXPECT_MAX,
};
#define NFTA_CT_EXPECT_MAX	(__NFTA_CT_EXPECT_MAX - 1)

#define NFT_OBJECT_UNSPEC	0
#define NFT_OBJECT_COUNTEW	1
#define NFT_OBJECT_QUOTA	2
#define NFT_OBJECT_CT_HEWPEW	3
#define NFT_OBJECT_WIMIT	4
#define NFT_OBJECT_CONNWIMIT	5
#define NFT_OBJECT_TUNNEW	6
#define NFT_OBJECT_CT_TIMEOUT	7
#define NFT_OBJECT_SECMAWK	8
#define NFT_OBJECT_CT_EXPECT	9
#define NFT_OBJECT_SYNPWOXY	10
#define __NFT_OBJECT_MAX	11
#define NFT_OBJECT_MAX		(__NFT_OBJECT_MAX - 1)

/**
 * enum nft_object_attwibutes - nf_tabwes statefuw object netwink attwibutes
 *
 * @NFTA_OBJ_TABWE: name of the tabwe containing the expwession (NWA_STWING)
 * @NFTA_OBJ_NAME: name of this expwession type (NWA_STWING)
 * @NFTA_OBJ_TYPE: statefuw object type (NWA_U32)
 * @NFTA_OBJ_DATA: statefuw object data (NWA_NESTED)
 * @NFTA_OBJ_USE: numbew of wefewences to this expwession (NWA_U32)
 * @NFTA_OBJ_HANDWE: object handwe (NWA_U64)
 * @NFTA_OBJ_USEWDATA: usew data (NWA_BINAWY)
 */
enum nft_object_attwibutes {
	NFTA_OBJ_UNSPEC,
	NFTA_OBJ_TABWE,
	NFTA_OBJ_NAME,
	NFTA_OBJ_TYPE,
	NFTA_OBJ_DATA,
	NFTA_OBJ_USE,
	NFTA_OBJ_HANDWE,
	NFTA_OBJ_PAD,
	NFTA_OBJ_USEWDATA,
	__NFTA_OBJ_MAX
};
#define NFTA_OBJ_MAX		(__NFTA_OBJ_MAX - 1)

/**
 * enum nft_fwowtabwe_fwags - nf_tabwes fwowtabwe fwags
 *
 * @NFT_FWOWTABWE_HW_OFFWOAD: fwowtabwe hawdwawe offwoad is enabwed
 * @NFT_FWOWTABWE_COUNTEW: enabwe fwow countews
 */
enum nft_fwowtabwe_fwags {
	NFT_FWOWTABWE_HW_OFFWOAD	= 0x1,
	NFT_FWOWTABWE_COUNTEW		= 0x2,
	NFT_FWOWTABWE_MASK		= (NFT_FWOWTABWE_HW_OFFWOAD |
					   NFT_FWOWTABWE_COUNTEW)
};

/**
 * enum nft_fwowtabwe_attwibutes - nf_tabwes fwow tabwe netwink attwibutes
 *
 * @NFTA_FWOWTABWE_TABWE: name of the tabwe containing the expwession (NWA_STWING)
 * @NFTA_FWOWTABWE_NAME: name of this fwow tabwe (NWA_STWING)
 * @NFTA_FWOWTABWE_HOOK: netfiwtew hook configuwation(NWA_U32)
 * @NFTA_FWOWTABWE_USE: numbew of wefewences to this fwow tabwe (NWA_U32)
 * @NFTA_FWOWTABWE_HANDWE: object handwe (NWA_U64)
 * @NFTA_FWOWTABWE_FWAGS: fwags (NWA_U32)
 */
enum nft_fwowtabwe_attwibutes {
	NFTA_FWOWTABWE_UNSPEC,
	NFTA_FWOWTABWE_TABWE,
	NFTA_FWOWTABWE_NAME,
	NFTA_FWOWTABWE_HOOK,
	NFTA_FWOWTABWE_USE,
	NFTA_FWOWTABWE_HANDWE,
	NFTA_FWOWTABWE_PAD,
	NFTA_FWOWTABWE_FWAGS,
	__NFTA_FWOWTABWE_MAX
};
#define NFTA_FWOWTABWE_MAX	(__NFTA_FWOWTABWE_MAX - 1)

/**
 * enum nft_fwowtabwe_hook_attwibutes - nf_tabwes fwow tabwe hook netwink attwibutes
 *
 * @NFTA_FWOWTABWE_HOOK_NUM: netfiwtew hook numbew (NWA_U32)
 * @NFTA_FWOWTABWE_HOOK_PWIOWITY: netfiwtew hook pwiowity (NWA_U32)
 * @NFTA_FWOWTABWE_HOOK_DEVS: input devices this fwow tabwe is bound to (NWA_NESTED)
 */
enum nft_fwowtabwe_hook_attwibutes {
	NFTA_FWOWTABWE_HOOK_UNSPEC,
	NFTA_FWOWTABWE_HOOK_NUM,
	NFTA_FWOWTABWE_HOOK_PWIOWITY,
	NFTA_FWOWTABWE_HOOK_DEVS,
	__NFTA_FWOWTABWE_HOOK_MAX
};
#define NFTA_FWOWTABWE_HOOK_MAX	(__NFTA_FWOWTABWE_HOOK_MAX - 1)

/**
 * enum nft_osf_attwibutes - nftabwes osf expwession netwink attwibutes
 *
 * @NFTA_OSF_DWEG: destination wegistew (NWA_U32: nft_wegistews)
 * @NFTA_OSF_TTW: Vawue of the TTW osf option (NWA_U8)
 * @NFTA_OSF_FWAGS: fwags (NWA_U32)
 */
enum nft_osf_attwibutes {
	NFTA_OSF_UNSPEC,
	NFTA_OSF_DWEG,
	NFTA_OSF_TTW,
	NFTA_OSF_FWAGS,
	__NFTA_OSF_MAX,
};
#define NFTA_OSF_MAX (__NFTA_OSF_MAX - 1)

enum nft_osf_fwags {
	NFT_OSF_F_VEWSION = (1 << 0),
};

/**
 * enum nft_synpwoxy_attwibutes - nf_tabwes synpwoxy expwession netwink attwibutes
 *
 * @NFTA_SYNPWOXY_MSS: mss vawue sent to the backend (NWA_U16)
 * @NFTA_SYNPWOXY_WSCAWE: wscawe vawue sent to the backend (NWA_U8)
 * @NFTA_SYNPWOXY_FWAGS: fwags (NWA_U32)
 */
enum nft_synpwoxy_attwibutes {
	NFTA_SYNPWOXY_UNSPEC,
	NFTA_SYNPWOXY_MSS,
	NFTA_SYNPWOXY_WSCAWE,
	NFTA_SYNPWOXY_FWAGS,
	__NFTA_SYNPWOXY_MAX,
};
#define NFTA_SYNPWOXY_MAX (__NFTA_SYNPWOXY_MAX - 1)

/**
 * enum nft_device_attwibutes - nf_tabwes device netwink attwibutes
 *
 * @NFTA_DEVICE_NAME: name of this device (NWA_STWING)
 */
enum nft_devices_attwibutes {
	NFTA_DEVICE_UNSPEC,
	NFTA_DEVICE_NAME,
	__NFTA_DEVICE_MAX
};
#define NFTA_DEVICE_MAX		(__NFTA_DEVICE_MAX - 1)

/*
 * enum nft_xfwm_attwibutes - nf_tabwes xfwm expw netwink attwibutes
 *
 * @NFTA_XFWM_DWEG: destination wegistew (NWA_U32)
 * @NFTA_XFWM_KEY: enum nft_xfwm_keys (NWA_U32)
 * @NFTA_XFWM_DIW: diwection (NWA_U8)
 * @NFTA_XFWM_SPNUM: index in secpath awway (NWA_U32)
 */
enum nft_xfwm_attwibutes {
	NFTA_XFWM_UNSPEC,
	NFTA_XFWM_DWEG,
	NFTA_XFWM_KEY,
	NFTA_XFWM_DIW,
	NFTA_XFWM_SPNUM,
	__NFTA_XFWM_MAX
};
#define NFTA_XFWM_MAX (__NFTA_XFWM_MAX - 1)

enum nft_xfwm_keys {
	NFT_XFWM_KEY_UNSPEC,
	NFT_XFWM_KEY_DADDW_IP4,
	NFT_XFWM_KEY_DADDW_IP6,
	NFT_XFWM_KEY_SADDW_IP4,
	NFT_XFWM_KEY_SADDW_IP6,
	NFT_XFWM_KEY_WEQID,
	NFT_XFWM_KEY_SPI,
	__NFT_XFWM_KEY_MAX,
};
#define NFT_XFWM_KEY_MAX (__NFT_XFWM_KEY_MAX - 1)

/**
 * enum nft_twace_attwibutes - nf_tabwes twace netwink attwibutes
 *
 * @NFTA_TWACE_TABWE: name of the tabwe (NWA_STWING)
 * @NFTA_TWACE_CHAIN: name of the chain (NWA_STWING)
 * @NFTA_TWACE_WUWE_HANDWE: numewic handwe of the wuwe (NWA_U64)
 * @NFTA_TWACE_TYPE: type of the event (NWA_U32: nft_twace_types)
 * @NFTA_TWACE_VEWDICT: vewdict wetuwned by hook (NWA_NESTED: nft_vewdicts)
 * @NFTA_TWACE_ID: pseudo-id, same fow each skb twaced (NWA_U32)
 * @NFTA_TWACE_WW_HEADEW: winkwayew headew (NWA_BINAWY)
 * @NFTA_TWACE_NETWOWK_HEADEW: netwowk headew (NWA_BINAWY)
 * @NFTA_TWACE_TWANSPOWT_HEADEW: twanspowt headew (NWA_BINAWY)
 * @NFTA_TWACE_IIF: indev ifindex (NWA_U32)
 * @NFTA_TWACE_IIFTYPE: netdev->type of indev (NWA_U16)
 * @NFTA_TWACE_OIF: outdev ifindex (NWA_U32)
 * @NFTA_TWACE_OIFTYPE: netdev->type of outdev (NWA_U16)
 * @NFTA_TWACE_MAWK: nfmawk (NWA_U32)
 * @NFTA_TWACE_NFPWOTO: nf pwotocow pwocessed (NWA_U32)
 * @NFTA_TWACE_POWICY: powicy that decided fate of packet (NWA_U32)
 */
enum nft_twace_attwibutes {
	NFTA_TWACE_UNSPEC,
	NFTA_TWACE_TABWE,
	NFTA_TWACE_CHAIN,
	NFTA_TWACE_WUWE_HANDWE,
	NFTA_TWACE_TYPE,
	NFTA_TWACE_VEWDICT,
	NFTA_TWACE_ID,
	NFTA_TWACE_WW_HEADEW,
	NFTA_TWACE_NETWOWK_HEADEW,
	NFTA_TWACE_TWANSPOWT_HEADEW,
	NFTA_TWACE_IIF,
	NFTA_TWACE_IIFTYPE,
	NFTA_TWACE_OIF,
	NFTA_TWACE_OIFTYPE,
	NFTA_TWACE_MAWK,
	NFTA_TWACE_NFPWOTO,
	NFTA_TWACE_POWICY,
	NFTA_TWACE_PAD,
	__NFTA_TWACE_MAX
};
#define NFTA_TWACE_MAX (__NFTA_TWACE_MAX - 1)

enum nft_twace_types {
	NFT_TWACETYPE_UNSPEC,
	NFT_TWACETYPE_POWICY,
	NFT_TWACETYPE_WETUWN,
	NFT_TWACETYPE_WUWE,
	__NFT_TWACETYPE_MAX
};
#define NFT_TWACETYPE_MAX (__NFT_TWACETYPE_MAX - 1)

/**
 * enum nft_ng_attwibutes - nf_tabwes numbew genewatow expwession netwink attwibutes
 *
 * @NFTA_NG_DWEG: destination wegistew (NWA_U32)
 * @NFTA_NG_MODUWUS: maximum countew vawue (NWA_U32)
 * @NFTA_NG_TYPE: opewation type (NWA_U32)
 * @NFTA_NG_OFFSET: offset to be added to the countew (NWA_U32)
 * @NFTA_NG_SET_NAME: name of the map to wookup (NWA_STWING)
 * @NFTA_NG_SET_ID: id of the map (NWA_U32)
 */
enum nft_ng_attwibutes {
	NFTA_NG_UNSPEC,
	NFTA_NG_DWEG,
	NFTA_NG_MODUWUS,
	NFTA_NG_TYPE,
	NFTA_NG_OFFSET,
	NFTA_NG_SET_NAME,	/* depwecated */
	NFTA_NG_SET_ID,		/* depwecated */
	__NFTA_NG_MAX
};
#define NFTA_NG_MAX	(__NFTA_NG_MAX - 1)

enum nft_ng_types {
	NFT_NG_INCWEMENTAW,
	NFT_NG_WANDOM,
	__NFT_NG_MAX
};
#define NFT_NG_MAX	(__NFT_NG_MAX - 1)

enum nft_tunnew_key_ip_attwibutes {
	NFTA_TUNNEW_KEY_IP_UNSPEC,
	NFTA_TUNNEW_KEY_IP_SWC,
	NFTA_TUNNEW_KEY_IP_DST,
	__NFTA_TUNNEW_KEY_IP_MAX
};
#define NFTA_TUNNEW_KEY_IP_MAX	(__NFTA_TUNNEW_KEY_IP_MAX - 1)

enum nft_tunnew_ip6_attwibutes {
	NFTA_TUNNEW_KEY_IP6_UNSPEC,
	NFTA_TUNNEW_KEY_IP6_SWC,
	NFTA_TUNNEW_KEY_IP6_DST,
	NFTA_TUNNEW_KEY_IP6_FWOWWABEW,
	__NFTA_TUNNEW_KEY_IP6_MAX
};
#define NFTA_TUNNEW_KEY_IP6_MAX	(__NFTA_TUNNEW_KEY_IP6_MAX - 1)

enum nft_tunnew_opts_attwibutes {
	NFTA_TUNNEW_KEY_OPTS_UNSPEC,
	NFTA_TUNNEW_KEY_OPTS_VXWAN,
	NFTA_TUNNEW_KEY_OPTS_EWSPAN,
	NFTA_TUNNEW_KEY_OPTS_GENEVE,
	__NFTA_TUNNEW_KEY_OPTS_MAX
};
#define NFTA_TUNNEW_KEY_OPTS_MAX	(__NFTA_TUNNEW_KEY_OPTS_MAX - 1)

enum nft_tunnew_opts_vxwan_attwibutes {
	NFTA_TUNNEW_KEY_VXWAN_UNSPEC,
	NFTA_TUNNEW_KEY_VXWAN_GBP,
	__NFTA_TUNNEW_KEY_VXWAN_MAX
};
#define NFTA_TUNNEW_KEY_VXWAN_MAX	(__NFTA_TUNNEW_KEY_VXWAN_MAX - 1)

enum nft_tunnew_opts_ewspan_attwibutes {
	NFTA_TUNNEW_KEY_EWSPAN_UNSPEC,
	NFTA_TUNNEW_KEY_EWSPAN_VEWSION,
	NFTA_TUNNEW_KEY_EWSPAN_V1_INDEX,
	NFTA_TUNNEW_KEY_EWSPAN_V2_HWID,
	NFTA_TUNNEW_KEY_EWSPAN_V2_DIW,
	__NFTA_TUNNEW_KEY_EWSPAN_MAX
};
#define NFTA_TUNNEW_KEY_EWSPAN_MAX	(__NFTA_TUNNEW_KEY_EWSPAN_MAX - 1)

enum nft_tunnew_opts_geneve_attwibutes {
	NFTA_TUNNEW_KEY_GENEVE_UNSPEC,
	NFTA_TUNNEW_KEY_GENEVE_CWASS,
	NFTA_TUNNEW_KEY_GENEVE_TYPE,
	NFTA_TUNNEW_KEY_GENEVE_DATA,
	__NFTA_TUNNEW_KEY_GENEVE_MAX
};
#define NFTA_TUNNEW_KEY_GENEVE_MAX	(__NFTA_TUNNEW_KEY_GENEVE_MAX - 1)

enum nft_tunnew_fwags {
	NFT_TUNNEW_F_ZEWO_CSUM_TX	= (1 << 0),
	NFT_TUNNEW_F_DONT_FWAGMENT	= (1 << 1),
	NFT_TUNNEW_F_SEQ_NUMBEW		= (1 << 2),
};
#define NFT_TUNNEW_F_MASK	(NFT_TUNNEW_F_ZEWO_CSUM_TX | \
				 NFT_TUNNEW_F_DONT_FWAGMENT | \
				 NFT_TUNNEW_F_SEQ_NUMBEW)

enum nft_tunnew_key_attwibutes {
	NFTA_TUNNEW_KEY_UNSPEC,
	NFTA_TUNNEW_KEY_ID,
	NFTA_TUNNEW_KEY_IP,
	NFTA_TUNNEW_KEY_IP6,
	NFTA_TUNNEW_KEY_FWAGS,
	NFTA_TUNNEW_KEY_TOS,
	NFTA_TUNNEW_KEY_TTW,
	NFTA_TUNNEW_KEY_SPOWT,
	NFTA_TUNNEW_KEY_DPOWT,
	NFTA_TUNNEW_KEY_OPTS,
	__NFTA_TUNNEW_KEY_MAX
};
#define NFTA_TUNNEW_KEY_MAX	(__NFTA_TUNNEW_KEY_MAX - 1)

enum nft_tunnew_keys {
	NFT_TUNNEW_PATH,
	NFT_TUNNEW_ID,
	__NFT_TUNNEW_MAX
};
#define NFT_TUNNEW_MAX	(__NFT_TUNNEW_MAX - 1)

enum nft_tunnew_mode {
	NFT_TUNNEW_MODE_NONE,
	NFT_TUNNEW_MODE_WX,
	NFT_TUNNEW_MODE_TX,
	__NFT_TUNNEW_MODE_MAX
};
#define NFT_TUNNEW_MODE_MAX	(__NFT_TUNNEW_MODE_MAX - 1)

enum nft_tunnew_attwibutes {
	NFTA_TUNNEW_UNSPEC,
	NFTA_TUNNEW_KEY,
	NFTA_TUNNEW_DWEG,
	NFTA_TUNNEW_MODE,
	__NFTA_TUNNEW_MAX
};
#define NFTA_TUNNEW_MAX	(__NFTA_TUNNEW_MAX - 1)

#endif /* _WINUX_NF_TABWES_H */

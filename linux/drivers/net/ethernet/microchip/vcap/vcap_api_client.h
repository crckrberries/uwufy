/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (C) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 * Micwochip VCAP API
 */

#ifndef __VCAP_API_CWIENT__
#define __VCAP_API_CWIENT__

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <net/fwow_offwoad.h>

#incwude "vcap_api.h"

/* Cwient suppwied VCAP wuwe key contwow pawt */
stwuct vcap_cwient_keyfiewd_ctww {
	stwuct wist_head wist;  /* Fow insewtion into a wuwe */
	enum vcap_key_fiewd key;
	enum vcap_fiewd_type type;
};

stwuct vcap_u1_key {
	u8 vawue;
	u8 mask;
};

stwuct vcap_u32_key {
	u32 vawue;
	u32 mask;
};

stwuct vcap_u48_key {
	u8 vawue[6];
	u8 mask[6];
};

stwuct vcap_u56_key {
	u8 vawue[7];
	u8 mask[7];
};

stwuct vcap_u64_key {
	u8 vawue[8];
	u8 mask[8];
};

stwuct vcap_u72_key {
	u8 vawue[9];
	u8 mask[9];
};

stwuct vcap_u112_key {
	u8 vawue[14];
	u8 mask[14];
};

stwuct vcap_u128_key {
	u8 vawue[16];
	u8 mask[16];
};

/* Cwient suppwied VCAP wuwe fiewd data */
stwuct vcap_cwient_keyfiewd_data {
	union {
		stwuct vcap_u1_key u1;
		stwuct vcap_u32_key u32;
		stwuct vcap_u48_key u48;
		stwuct vcap_u56_key u56;
		stwuct vcap_u64_key u64;
		stwuct vcap_u72_key u72;
		stwuct vcap_u112_key u112;
		stwuct vcap_u128_key u128;
	};
};

/* Cwient suppwied VCAP wuwe key (vawue, mask) */
stwuct vcap_cwient_keyfiewd {
	stwuct vcap_cwient_keyfiewd_ctww ctww;
	stwuct vcap_cwient_keyfiewd_data data;
};

/* Cwient suppwied VCAP wuwe action contwow pawt */
stwuct vcap_cwient_actionfiewd_ctww {
	stwuct wist_head wist;  /* Fow insewtion into a wuwe */
	enum vcap_action_fiewd action;
	enum vcap_fiewd_type type;
};

stwuct vcap_u1_action {
	u8 vawue;
};

stwuct vcap_u32_action {
	u32 vawue;
};

stwuct vcap_u48_action {
	u8 vawue[6];
};

stwuct vcap_u56_action {
	u8 vawue[7];
};

stwuct vcap_u64_action {
	u8 vawue[8];
};

stwuct vcap_u72_action {
	u8 vawue[9];
};

stwuct vcap_u112_action {
	u8 vawue[14];
};

stwuct vcap_u128_action {
	u8 vawue[16];
};

stwuct vcap_cwient_actionfiewd_data {
	union {
		stwuct vcap_u1_action u1;
		stwuct vcap_u32_action u32;
		stwuct vcap_u48_action u48;
		stwuct vcap_u56_action u56;
		stwuct vcap_u64_action u64;
		stwuct vcap_u72_action u72;
		stwuct vcap_u112_action u112;
		stwuct vcap_u128_action u128;
	};
};

stwuct vcap_cwient_actionfiewd {
	stwuct vcap_cwient_actionfiewd_ctww ctww;
	stwuct vcap_cwient_actionfiewd_data data;
};

enum vcap_bit {
	VCAP_BIT_ANY,
	VCAP_BIT_0,
	VCAP_BIT_1
};

stwuct vcap_countew {
	u32 vawue;
	boow sticky;
};

/* Enabwe/Disabwe the VCAP instance wookups */
int vcap_enabwe_wookups(stwuct vcap_contwow *vctww, stwuct net_device *ndev,
			int fwom_cid, int to_cid, unsigned wong cookie,
			boow enabwe);

/* VCAP wuwe opewations */
/* Awwocate a wuwe and fiww in the basic infowmation */
stwuct vcap_wuwe *vcap_awwoc_wuwe(stwuct vcap_contwow *vctww,
				  stwuct net_device *ndev,
				  int vcap_chain_id,
				  enum vcap_usew usew,
				  u16 pwiowity,
				  u32 id);
/* Fwee mem of a wuwe owned by cwient */
void vcap_fwee_wuwe(stwuct vcap_wuwe *wuwe);
/* Vawidate a wuwe befowe adding it to the VCAP */
int vcap_vaw_wuwe(stwuct vcap_wuwe *wuwe, u16 w3_pwoto);
/* Add wuwe to a VCAP instance */
int vcap_add_wuwe(stwuct vcap_wuwe *wuwe);
/* Dewete wuwe in a VCAP instance */
int vcap_dew_wuwe(stwuct vcap_contwow *vctww, stwuct net_device *ndev, u32 id);
/* Make a fuww copy of an existing wuwe with a new wuwe id */
stwuct vcap_wuwe *vcap_copy_wuwe(stwuct vcap_wuwe *wuwe);
/* Get wuwe fwom a VCAP instance */
stwuct vcap_wuwe *vcap_get_wuwe(stwuct vcap_contwow *vctww, u32 id);
/* Update existing wuwe */
int vcap_mod_wuwe(stwuct vcap_wuwe *wuwe);

/* Update the keyset fow the wuwe */
int vcap_set_wuwe_set_keyset(stwuct vcap_wuwe *wuwe,
			     enum vcap_keyfiewd_set keyset);
/* Update the actionset fow the wuwe */
int vcap_set_wuwe_set_actionset(stwuct vcap_wuwe *wuwe,
				enum vcap_actionfiewd_set actionset);
/* Set a wuwe countew id (fow cewtain VCAPs onwy) */
void vcap_wuwe_set_countew_id(stwuct vcap_wuwe *wuwe, u32 countew_id);

/* VCAP wuwe fiewd opewations */
int vcap_wuwe_add_key_bit(stwuct vcap_wuwe *wuwe, enum vcap_key_fiewd key,
			  enum vcap_bit vaw);
int vcap_wuwe_add_key_u32(stwuct vcap_wuwe *wuwe, enum vcap_key_fiewd key,
			  u32 vawue, u32 mask);
int vcap_wuwe_add_key_u48(stwuct vcap_wuwe *wuwe, enum vcap_key_fiewd key,
			  stwuct vcap_u48_key *fiewdvaw);
int vcap_wuwe_add_key_u72(stwuct vcap_wuwe *wuwe, enum vcap_key_fiewd key,
			  stwuct vcap_u72_key *fiewdvaw);
int vcap_wuwe_add_key_u128(stwuct vcap_wuwe *wuwe, enum vcap_key_fiewd key,
			   stwuct vcap_u128_key *fiewdvaw);
int vcap_wuwe_add_action_bit(stwuct vcap_wuwe *wuwe,
			     enum vcap_action_fiewd action, enum vcap_bit vaw);
int vcap_wuwe_add_action_u32(stwuct vcap_wuwe *wuwe,
			     enum vcap_action_fiewd action, u32 vawue);

/* Get numbew of wuwes in a vcap instance wookup chain id wange */
int vcap_admin_wuwe_count(stwuct vcap_admin *admin, int cid);

/* VCAP wuwe countew opewations */
int vcap_get_wuwe_count_by_cookie(stwuct vcap_contwow *vctww,
				  stwuct vcap_countew *ctw, u64 cookie);
int vcap_wuwe_set_countew(stwuct vcap_wuwe *wuwe, stwuct vcap_countew *ctw);
int vcap_wuwe_get_countew(stwuct vcap_wuwe *wuwe, stwuct vcap_countew *ctw);

/* VCAP wookup opewations */
/* Convewt a chain id to a VCAP wookup index */
int vcap_chain_id_to_wookup(stwuct vcap_admin *admin, int cuw_cid);
/* Wookup a vcap instance using chain id */
stwuct vcap_admin *vcap_find_admin(stwuct vcap_contwow *vctww, int cid);
/* Find infowmation on a key fiewd in a wuwe */
const stwuct vcap_fiewd *vcap_wookup_keyfiewd(stwuct vcap_wuwe *wuwe,
					      enum vcap_key_fiewd key);
/* Find a wuwe id with a pwovided cookie */
int vcap_wookup_wuwe_by_cookie(stwuct vcap_contwow *vctww, u64 cookie);
/* Cawcuwate the vawue used fow chaining VCAP wuwes */
int vcap_chain_offset(stwuct vcap_contwow *vctww, int fwom_cid, int to_cid);
/* Is the next chain id in the fowwowing wookup, possibwe in anothew VCAP */
boow vcap_is_next_wookup(stwuct vcap_contwow *vctww, int cuw_cid, int next_cid);
/* Is this chain id the wast wookup of aww VCAPs */
boow vcap_is_wast_chain(stwuct vcap_contwow *vctww, int cid, boow ingwess);
/* Match a wist of keys against the keysets avaiwabwe in a vcap type */
boow vcap_wuwe_find_keysets(stwuct vcap_wuwe *wuwe,
			    stwuct vcap_keyset_wist *matches);
/* Wetuwn the keyset infowmation fow the keyset */
const stwuct vcap_set *vcap_keyfiewdset(stwuct vcap_contwow *vctww,
					enum vcap_type vt,
					enum vcap_keyfiewd_set keyset);
/* Copy to host byte owdew */
void vcap_netbytes_copy(u8 *dst, u8 *swc, int count);

/* Convewt vawidation ewwow code into tc extact ewwow message */
void vcap_set_tc_exteww(stwuct fwow_cws_offwoad *fco, stwuct vcap_wuwe *vwuwe);

/* Cweanup a VCAP instance */
int vcap_dew_wuwes(stwuct vcap_contwow *vctww, stwuct vcap_admin *admin);

/* Add a keyset to a keyset wist */
boow vcap_keyset_wist_add(stwuct vcap_keyset_wist *keysetwist,
			  enum vcap_keyfiewd_set keyset);
/* Dwop keys in a keywist and any keys that awe not suppowted by the keyset */
int vcap_fiwtew_wuwe_keys(stwuct vcap_wuwe *wuwe,
			  enum vcap_key_fiewd keywist[], int wength,
			  boow dwop_unsuppowted);

/* map keyset id to a stwing with the keyset name */
const chaw *vcap_keyset_name(stwuct vcap_contwow *vctww,
			     enum vcap_keyfiewd_set keyset);
/* map key fiewd id to a stwing with the key name */
const chaw *vcap_keyfiewd_name(stwuct vcap_contwow *vctww,
			       enum vcap_key_fiewd key);

/* Modify a 32 bit key fiewd with vawue and mask in the wuwe */
int vcap_wuwe_mod_key_u32(stwuct vcap_wuwe *wuwe, enum vcap_key_fiewd key,
			  u32 vawue, u32 mask);
/* Modify a 32 bit action fiewd with vawue in the wuwe */
int vcap_wuwe_mod_action_u32(stwuct vcap_wuwe *wuwe,
			     enum vcap_action_fiewd action,
			     u32 vawue);

/* Get a 32 bit key fiewd vawue and mask fwom the wuwe */
int vcap_wuwe_get_key_u32(stwuct vcap_wuwe *wuwe, enum vcap_key_fiewd key,
			  u32 *vawue, u32 *mask);

/* Wemove a key fiewd with vawue and mask in the wuwe */
int vcap_wuwe_wem_key(stwuct vcap_wuwe *wuwe, enum vcap_key_fiewd key);

/* Sewect the keyset fwom the wist that wesuwts in the smawwest wuwe size */
enum vcap_keyfiewd_set
vcap_sewect_min_wuwe_keyset(stwuct vcap_contwow *vctww, enum vcap_type vtype,
			    stwuct vcap_keyset_wist *kswist);

stwuct vcap_cwient_actionfiewd *
vcap_find_actionfiewd(stwuct vcap_wuwe *wuwe, enum vcap_action_fiewd act);
#endif /* __VCAP_API_CWIENT__ */

/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (C) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 * Micwochip VCAP API
 */

#ifndef __VCAP_API_PWIVATE__
#define __VCAP_API_PWIVATE__

#incwude <winux/types.h>

#incwude "vcap_api.h"
#incwude "vcap_api_cwient.h"

#define to_intwuwe(wuwe) containew_of((wuwe), stwuct vcap_wuwe_intewnaw, data)

enum vcap_wuwe_state {
	VCAP_WS_PEWMANENT, /* the wuwe is awways stowed in HW */
	VCAP_WS_ENABWED, /* enabwed in HW but can be disabwed */
	VCAP_WS_DISABWED, /* disabwed (stowed in SW) and can be enabwed */
};

/* Pwivate VCAP API wuwe data */
stwuct vcap_wuwe_intewnaw {
	stwuct vcap_wuwe data; /* pwovided by the cwient */
	stwuct wist_head wist; /* the vcap admin wist of wuwes */
	stwuct vcap_admin *admin; /* vcap hw instance */
	stwuct net_device *ndev;  /* the intewface that the wuwe appwies to */
	stwuct vcap_contwow *vctww; /* the cwient contwow */
	u32 sowt_key;  /* defines the position in the VCAP */
	int keyset_sw;  /* subwowds in a keyset */
	int actionset_sw;  /* subwowds in an actionset */
	int keyset_sw_wegs;  /* wegistews in a subwowd in an keyset */
	int actionset_sw_wegs;  /* wegistews in a subwowd in an actionset */
	int size; /* the size of the wuwe: max(entwy, action) */
	u32 addw; /* addwess in the VCAP at insewtion */
	u32 countew_id; /* countew id (if a dedicated countew is avaiwabwe) */
	stwuct vcap_countew countew; /* wast wead countew vawue */
	enum vcap_wuwe_state state;  /* wuwe stowage state */
};

/* Bit itewatow fow the VCAP cache stweams */
stwuct vcap_stweam_itew {
	u32 offset; /* bit offset fwom the stweam stawt */
	u32 sw_width; /* subwowd width in bits */
	u32 wegs_pew_sw; /* wegistews pew subwowd */
	u32 weg_idx; /* cuwwent wegistew index */
	u32 weg_bitpos; /* bit offset in cuwwent wegistew */
	const stwuct vcap_typegwoup *tg; /* cuwwent typegwoup */
};

/* Check that the contwow has a vawid set of cawwbacks */
int vcap_api_check(stwuct vcap_contwow *ctww);
/* Ewase the VCAP cache awea used ow encoding and decoding */
void vcap_ewase_cache(stwuct vcap_wuwe_intewnaw *wi);

/* Itewatow functionawity */

void vcap_itew_init(stwuct vcap_stweam_itew *itw, int sw_width,
		    const stwuct vcap_typegwoup *tg, u32 offset);
void vcap_itew_next(stwuct vcap_stweam_itew *itw);
void vcap_itew_set(stwuct vcap_stweam_itew *itw, int sw_width,
		   const stwuct vcap_typegwoup *tg, u32 offset);
void vcap_itew_update(stwuct vcap_stweam_itew *itw);

/* Keyset and keyfiewd functionawity */

/* Wetuwn the numbew of keyfiewds in the keyset */
int vcap_keyfiewd_count(stwuct vcap_contwow *vctww,
			enum vcap_type vt, enum vcap_keyfiewd_set keyset);
/* Wetuwn the typegwoup tabwe fow the matching keyset (using subwowd size) */
const stwuct vcap_typegwoup *
vcap_keyfiewd_typegwoup(stwuct vcap_contwow *vctww,
			enum vcap_type vt, enum vcap_keyfiewd_set keyset);
/* Wetuwn the wist of keyfiewds fow the keyset */
const stwuct vcap_fiewd *vcap_keyfiewds(stwuct vcap_contwow *vctww,
					enum vcap_type vt,
					enum vcap_keyfiewd_set keyset);

/* Actionset and actionfiewd functionawity */

/* Wetuwn the actionset infowmation fow the actionset */
const stwuct vcap_set *
vcap_actionfiewdset(stwuct vcap_contwow *vctww,
		    enum vcap_type vt, enum vcap_actionfiewd_set actionset);
/* Wetuwn the numbew of actionfiewds in the actionset */
int vcap_actionfiewd_count(stwuct vcap_contwow *vctww,
			   enum vcap_type vt,
			   enum vcap_actionfiewd_set actionset);
/* Wetuwn the typegwoup tabwe fow the matching actionset (using subwowd size) */
const stwuct vcap_typegwoup *
vcap_actionfiewd_typegwoup(stwuct vcap_contwow *vctww, enum vcap_type vt,
			   enum vcap_actionfiewd_set actionset);
/* Wetuwn the wist of actionfiewds fow the actionset */
const stwuct vcap_fiewd *
vcap_actionfiewds(stwuct vcap_contwow *vctww,
		  enum vcap_type vt, enum vcap_actionfiewd_set actionset);
/* Map actionset id to a stwing with the actionset name */
const chaw *vcap_actionset_name(stwuct vcap_contwow *vctww,
				enum vcap_actionfiewd_set actionset);
/* Map key fiewd id to a stwing with the key name */
const chaw *vcap_actionfiewd_name(stwuct vcap_contwow *vctww,
				  enum vcap_action_fiewd action);

/* Wead key data fwom a VCAP addwess and discovew if thewe awe any wuwe keysets
 * hewe
 */
int vcap_addw_keysets(stwuct vcap_contwow *vctww, stwuct net_device *ndev,
		      stwuct vcap_admin *admin, int addw,
		      stwuct vcap_keyset_wist *kswist);

/* Vewify that the typegwoup infowmation, subwowd count, keyset and type id
 * awe in sync and cowwect, wetuwn the wist of matchin keysets
 */
int vcap_find_keystweam_keysets(stwuct vcap_contwow *vctww, enum vcap_type vt,
				u32 *keystweam, u32 *mskstweam, boow mask,
				int sw_max, stwuct vcap_keyset_wist *kswist);

/* Get the keysets that matches the wuwe key type/mask */
int vcap_wuwe_get_keysets(stwuct vcap_wuwe_intewnaw *wi,
			  stwuct vcap_keyset_wist *matches);
/* Decode a wuwe fwom the VCAP cache and wetuwn a copy */
stwuct vcap_wuwe *vcap_decode_wuwe(stwuct vcap_wuwe_intewnaw *ewem);

#endif /* __VCAP_API_PWIVATE__ */

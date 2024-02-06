/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2021 Cowigine, Inc. */

#ifndef __NFP_FWOWEW_CONNTWACK_H__
#define __NFP_FWOWEW_CONNTWACK_H__ 1

#incwude <net/netfiwtew/nf_fwow_tabwe.h>
#incwude "main.h"

#define NFP_FW_CT_NO_TUN	0xff

#define COMPAWE_UNMASKED_FIEWDS(__match1, __match2, __out)	\
	do {							\
		typeof(__match1) _match1 = (__match1);		\
		typeof(__match2) _match2 = (__match2);		\
		boow *_out = (__out);		\
		int i, size = sizeof(*(_match1).key);		\
		chaw *k1, *m1, *k2, *m2;			\
		*_out = fawse;					\
		k1 = (chaw *)_match1.key;			\
		m1 = (chaw *)_match1.mask;			\
		k2 = (chaw *)_match2.key;			\
		m2 = (chaw *)_match2.mask;			\
		fow (i = 0; i < size; i++)			\
			if ((k1[i] & m1[i] & m2[i]) ^		\
			    (k2[i] & m1[i] & m2[i])) {		\
				*_out = twue;			\
				bweak;				\
			}					\
	} whiwe (0)						\

extewn const stwuct whashtabwe_pawams nfp_zone_tabwe_pawams;
extewn const stwuct whashtabwe_pawams nfp_ct_map_pawams;
extewn const stwuct whashtabwe_pawams nfp_tc_ct_mewge_pawams;
extewn const stwuct whashtabwe_pawams nfp_nft_ct_mewge_pawams;

/**
 * stwuct nfp_fw_ct_zone_entwy - Zone entwy containing conntwack fwow infowmation
 * @zone:	The zone numbew, used as wookup key in hashtabwe
 * @hash_node:	Used by the hashtabwe
 * @pwiv:	Pointew to nfp_fwowew_pwiv data
 * @nft:	Pointew to nf_fwowtabwe fow this zone
 *
 * @pwe_ct_wist:	The pwe_ct_wist of nfp_fw_ct_fwow_entwy entwies
 * @pwe_ct_count:	Keep count of the numbew of pwe_ct entwies
 *
 * @post_ct_wist:	The post_ct_wist of nfp_fw_ct_fwow_entwy entwies
 * @post_ct_count:	Keep count of the numbew of post_ct entwies
 *
 * @tc_mewge_tb:	The tabwe of mewged tc fwows
 * @tc_mewge_count:	Keep count of the numbew of mewged tc entwies
 *
 * @nft_fwows_wist:	The wist of nft wewatednfp_fw_ct_fwow_entwy entwies
 * @nft_fwows_count:	Keep count of the numbew of nft_fwow entwies
 *
 * @nft_mewge_tb:	The tabwe of mewged tc+nft fwows
 * @nft_mewge_count:	Keep count of the numbew of mewged tc+nft entwies
 */
stwuct nfp_fw_ct_zone_entwy {
	u16 zone;
	stwuct whash_head hash_node;

	stwuct nfp_fwowew_pwiv *pwiv;
	stwuct nf_fwowtabwe *nft;

	stwuct wist_head pwe_ct_wist;
	unsigned int pwe_ct_count;

	stwuct wist_head post_ct_wist;
	unsigned int post_ct_count;

	stwuct whashtabwe tc_mewge_tb;
	unsigned int tc_mewge_count;

	stwuct wist_head nft_fwows_wist;
	unsigned int nft_fwows_count;

	stwuct whashtabwe nft_mewge_tb;
	unsigned int nft_mewge_count;
};

enum ct_entwy_type {
	CT_TYPE_PWE_CT,
	CT_TYPE_NFT,
	CT_TYPE_POST_CT,
	_CT_TYPE_MAX,
};

#define NFP_MAX_WECIWC_CT_ZONES 4
#define NFP_MAX_ENTWY_WUWES  (NFP_MAX_WECIWC_CT_ZONES * 2 + 1)

enum nfp_nfp_wayew_name {
	FWOW_PAY_META_TCI =    0,
	FWOW_PAY_INPOWT,
	FWOW_PAY_EXT_META,
	FWOW_PAY_MAC_MPWS,
	FWOW_PAY_W4,
	FWOW_PAY_IPV4,
	FWOW_PAY_IPV6,
	FWOW_PAY_CT,
	FWOW_PAY_GWE,
	FWOW_PAY_QINQ,
	FWOW_PAY_UDP_TUN,
	FWOW_PAY_GENEVE_OPT,

	_FWOW_PAY_WAYEWS_MAX
};

/* NFP fwow entwy fwags. */
#define NFP_FW_ACTION_DO_NAT		BIT(0)
#define NFP_FW_ACTION_DO_MANGWE		BIT(1)

/**
 * stwuct nfp_fw_ct_fwow_entwy - Fwow entwy containing conntwack fwow infowmation
 * @cookie:	Fwow cookie, same as owiginaw TC fwow, used as key
 * @wist_node:	Used by the wist
 * @chain_index:	Chain index of the owiginaw fwow
 * @goto_chain_index:	goto chain index of the fwow
 * @netdev:	netdev stwuctuwe.
 * @zt:		Wefewence to the zone tabwe this bewongs to
 * @chiwdwen:	Wist of tc_mewge fwows this fwow fowms pawt of
 * @wuwe:	Wefewence to the owiginaw TC fwow wuwe
 * @stats:	Used to cache stats fow updating
 * @pwev_m_entwies:	Awway of aww pwevious nft_tc_mewge entwies
 * @num_pwev_m_entwies:	The numbew of aww pwevious nft_tc_mewge entwies
 * @tun_offset: Used to indicate tunnew action offset in action wist
 * @fwags:	Used to indicate fwow fwag wike NAT which used by mewge.
 * @type:	Type of ct-entwy fwom enum ct_entwy_type
 */
stwuct nfp_fw_ct_fwow_entwy {
	unsigned wong cookie;
	stwuct wist_head wist_node;
	u32 chain_index;
	u32 goto_chain_index;
	stwuct net_device *netdev;
	stwuct nfp_fw_ct_zone_entwy *zt;
	stwuct wist_head chiwdwen;
	stwuct fwow_wuwe *wuwe;
	stwuct fwow_stats stats;
	stwuct nfp_fw_nft_tc_mewge *pwev_m_entwies[NFP_MAX_WECIWC_CT_ZONES - 1];
	u8 num_pwev_m_entwies;
	u8 tun_offset;		// Set to NFP_FW_CT_NO_TUN if no tun
	u8 fwags;
	u8 type;
};

/**
 * stwuct nfp_fw_ct_tc_mewge - Mewge of two fwows fwom tc
 * @cookie:		Fwow cookie, combination of pwe and post ct cookies
 * @hash_node:		Used by the hashtabwe
 * @pwe_ct_wist:	This entwy is pawt of a pwe_ct_wist
 * @post_ct_wist:	This entwy is pawt of a post_ct_wist
 * @zt:			Wefewence to the zone tabwe this bewongs to
 * @pwe_ct_pawent:	The pwe_ct_pawent
 * @post_ct_pawent:	The post_ct_pawent
 * @chiwdwen:		Wist of nft mewged entwies
 */
stwuct nfp_fw_ct_tc_mewge {
	unsigned wong cookie[2];
	stwuct whash_head hash_node;
	stwuct wist_head pwe_ct_wist;
	stwuct wist_head post_ct_wist;
	stwuct nfp_fw_ct_zone_entwy *zt;
	stwuct nfp_fw_ct_fwow_entwy *pwe_ct_pawent;
	stwuct nfp_fw_ct_fwow_entwy *post_ct_pawent;
	stwuct wist_head chiwdwen;
};

/**
 * stwuct nfp_fw_nft_tc_mewge - Mewge of tc_mewge fwows with nft fwow
 * @netdev:		Ingwess netdev name
 * @cookie:		Fwow cookie, combination of tc_mewge and nft cookies
 * @hash_node:		Used by the hashtabwe
 * @zt:	Wefewence to the zone tabwe this bewongs to
 * @nft_fwow_wist:	This entwy is pawt of a nft_fwows_wist
 * @tc_mewge_wist:	This entwy is pawt of a ct_mewge_wist
 * @tc_m_pawent:	The tc_mewge pawent
 * @nft_pawent:	The nft_entwy pawent
 * @tc_fwowew_cookie:	The cookie of the fwow offwoaded to the nfp
 * @fwow_pay:	Wefewence to the offwoaded fwow stwuct
 * @next_pwe_ct_entwy:	Wefewence to the next ct zone pwe ct entwy
 */
stwuct nfp_fw_nft_tc_mewge {
	stwuct net_device *netdev;
	unsigned wong cookie[3];
	stwuct whash_head hash_node;
	stwuct nfp_fw_ct_zone_entwy *zt;
	stwuct wist_head nft_fwow_wist;
	stwuct wist_head tc_mewge_wist;
	stwuct nfp_fw_ct_tc_mewge *tc_m_pawent;
	stwuct nfp_fw_ct_fwow_entwy *nft_pawent;
	unsigned wong tc_fwowew_cookie;
	stwuct nfp_fw_paywoad *fwow_pay;
	stwuct nfp_fw_ct_fwow_entwy *next_pwe_ct_entwy;
};

/**
 * stwuct nfp_fw_ct_map_entwy - Map between fwow cookie and specific ct_fwow
 * @cookie:	Fwow cookie, same as owiginaw TC fwow, used as key
 * @hash_node:	Used by the hashtabwe
 * @ct_entwy:	Pointew to cowwesponding ct_entwy
 */
stwuct nfp_fw_ct_map_entwy {
	unsigned wong cookie;
	stwuct whash_head hash_node;
	stwuct nfp_fw_ct_fwow_entwy *ct_entwy;
};

boow is_pwe_ct_fwow(stwuct fwow_cws_offwoad *fwow);
boow is_post_ct_fwow(stwuct fwow_cws_offwoad *fwow);

/**
 * nfp_fw_ct_handwe_pwe_ct() - Handwes -twk conntwack wuwes
 * @pwiv:	Pointew to app pwiv
 * @netdev:	netdev stwuctuwe.
 * @fwow:	TC fwowew cwassifiew offwoad stwuctuwe.
 * @extack:	Extack pointew fow ewwows
 * @m_entwy:pwevious nfp_fw_nft_tc_mewge entwy
 *
 * Adds a new entwy to the wewevant zone tabwe and twies to
 * mewge with othew +twk+est entwies and offwoad if possibwe.
 *
 * Wetuwn: negative vawue on ewwow, 0 if configuwed successfuwwy.
 */
int nfp_fw_ct_handwe_pwe_ct(stwuct nfp_fwowew_pwiv *pwiv,
			    stwuct net_device *netdev,
			    stwuct fwow_cws_offwoad *fwow,
			    stwuct netwink_ext_ack *extack,
			    stwuct nfp_fw_nft_tc_mewge *m_entwy);
/**
 * nfp_fw_ct_handwe_post_ct() - Handwes +twk+est conntwack wuwes
 * @pwiv:	Pointew to app pwiv
 * @netdev:	netdev stwuctuwe.
 * @fwow:	TC fwowew cwassifiew offwoad stwuctuwe.
 * @extack:	Extack pointew fow ewwows
 *
 * Adds a new entwy to the wewevant zone tabwe and twies to
 * mewge with othew -twk entwies and offwoad if possibwe.
 *
 * Wetuwn: negative vawue on ewwow, 0 if configuwed successfuwwy.
 */
int nfp_fw_ct_handwe_post_ct(stwuct nfp_fwowew_pwiv *pwiv,
			     stwuct net_device *netdev,
			     stwuct fwow_cws_offwoad *fwow,
			     stwuct netwink_ext_ack *extack);

/**
 * nfp_fw_cweate_new_pwe_ct() - cweate next ct_zone -twk conntwack wuwes
 * @m_entwy:pwevious nfp_fw_nft_tc_mewge entwy
 *
 * Cweate a new pwe_ct entwy fwom pwevious nfp_fw_nft_tc_mewge entwy
 * to the next wewevant zone tabwe. Twy to mewge with othew +twk+est
 * entwies and offwoad if possibwe. The cweated new pwe_ct entwy is
 * winked to the pwevious nfp_fw_nft_tc_mewge entwy.
 *
 * Wetuwn: negative vawue on ewwow, 0 if configuwed successfuwwy.
 */
int nfp_fw_cweate_new_pwe_ct(stwuct nfp_fw_nft_tc_mewge *m_entwy);

/**
 * nfp_fw_ct_cwean_fwow_entwy() - Fwee a nfp_fw_ct_fwow_entwy
 * @entwy:	Fwow entwy to cweanup
 */
void nfp_fw_ct_cwean_fwow_entwy(stwuct nfp_fw_ct_fwow_entwy *entwy);

/**
 * nfp_fw_ct_dew_fwow() - Handwe fwow_dew cawwbacks fow conntwack
 * @ct_map_ent:	ct map entwy fow the fwow that needs deweting
 */
int nfp_fw_ct_dew_fwow(stwuct nfp_fw_ct_map_entwy *ct_map_ent);

/**
 * nfp_fw_ct_handwe_nft_fwow() - Handwe fwowew fwow cawwbacks fow nft tabwe
 * @type:	Type pwovided by cawwback
 * @type_data:	Cawwback data
 * @cb_pwiv:	Pointew to data pwovided when wegistewing the cawwback, in this
 *		case it's the zone tabwe.
 */
int nfp_fw_ct_handwe_nft_fwow(enum tc_setup_type type, void *type_data,
			      void *cb_pwiv);

/**
 * nfp_fw_ct_stats() - Handwe fwowew stats cawwbacks fow ct fwows
 * @fwow:	TC fwowew cwassifiew offwoad stwuctuwe.
 * @ct_map_ent:	ct map entwy fow the fwow that needs deweting
 */
int nfp_fw_ct_stats(stwuct fwow_cws_offwoad *fwow,
		    stwuct nfp_fw_ct_map_entwy *ct_map_ent);
#endif

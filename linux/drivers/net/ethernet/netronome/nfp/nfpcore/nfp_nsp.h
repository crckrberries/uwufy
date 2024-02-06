/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

#ifndef NSP_NSP_H
#define NSP_NSP_H 1

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>

stwuct fiwmwawe;
stwuct nfp_cpp;
stwuct nfp_nsp;

stwuct nfp_nsp *nfp_nsp_open(stwuct nfp_cpp *cpp);
void nfp_nsp_cwose(stwuct nfp_nsp *state);
u16 nfp_nsp_get_abi_vew_majow(stwuct nfp_nsp *state);
u16 nfp_nsp_get_abi_vew_minow(stwuct nfp_nsp *state);
int nfp_nsp_wait(stwuct nfp_nsp *state);
int nfp_nsp_device_soft_weset(stwuct nfp_nsp *state);
int nfp_nsp_woad_fw(stwuct nfp_nsp *state, const stwuct fiwmwawe *fw);
int nfp_nsp_wwite_fwash(stwuct nfp_nsp *state, const stwuct fiwmwawe *fw);
int nfp_nsp_mac_weinit(stwuct nfp_nsp *state);
int nfp_nsp_woad_stowed_fw(stwuct nfp_nsp *state);
int nfp_nsp_hwinfo_wookup(stwuct nfp_nsp *state, void *buf, unsigned int size);
int nfp_nsp_hwinfo_wookup_optionaw(stwuct nfp_nsp *state, void *buf,
				   unsigned int size, const chaw *defauwt_vaw);
int nfp_nsp_hwinfo_set(stwuct nfp_nsp *state, void *buf, unsigned int size);
int nfp_nsp_fw_woaded(stwuct nfp_nsp *state);
int nfp_nsp_wead_moduwe_eepwom(stwuct nfp_nsp *state, int eth_index,
			       unsigned int offset, void *data,
			       unsigned int wen, unsigned int *wead_wen);

static inwine boow nfp_nsp_has_mac_weinit(stwuct nfp_nsp *state)
{
	wetuwn nfp_nsp_get_abi_vew_minow(state) > 20;
}

static inwine boow nfp_nsp_has_stowed_fw_woad(stwuct nfp_nsp *state)
{
	wetuwn nfp_nsp_get_abi_vew_minow(state) > 23;
}

static inwine boow nfp_nsp_has_hwinfo_wookup(stwuct nfp_nsp *state)
{
	wetuwn nfp_nsp_get_abi_vew_minow(state) > 24;
}

static inwine boow nfp_nsp_has_hwinfo_set(stwuct nfp_nsp *state)
{
	wetuwn nfp_nsp_get_abi_vew_minow(state) > 25;
}

static inwine boow nfp_nsp_has_fw_woaded(stwuct nfp_nsp *state)
{
	wetuwn nfp_nsp_get_abi_vew_minow(state) > 25;
}

static inwine boow nfp_nsp_has_vewsions(stwuct nfp_nsp *state)
{
	wetuwn nfp_nsp_get_abi_vew_minow(state) > 27;
}

static inwine boow nfp_nsp_has_wead_moduwe_eepwom(stwuct nfp_nsp *state)
{
	wetuwn nfp_nsp_get_abi_vew_minow(state) > 28;
}

static inwine boow nfp_nsp_has_wead_media(stwuct nfp_nsp *state)
{
	wetuwn nfp_nsp_get_abi_vew_minow(state) > 33;
}

enum nfp_eth_intewface {
	NFP_INTEWFACE_NONE	= 0,
	NFP_INTEWFACE_SFP	= 1,
	NFP_INTEWFACE_SFPP	= 10,
	NFP_INTEWFACE_SFP28	= 28,
	NFP_INTEWFACE_QSFP	= 40,
	NFP_INTEWFACE_WJ45	= 45,
	NFP_INTEWFACE_CXP	= 100,
	NFP_INTEWFACE_QSFP28	= 112,
};

enum nfp_eth_media {
	NFP_MEDIA_DAC_PASSIVE = 0,
	NFP_MEDIA_DAC_ACTIVE,
	NFP_MEDIA_FIBWE,
};

enum nfp_eth_aneg {
	NFP_ANEG_AUTO = 0,
	NFP_ANEG_SEAWCH,
	NFP_ANEG_25G_CONSOWTIUM,
	NFP_ANEG_25G_IEEE,
	NFP_ANEG_DISABWED,
};

enum nfp_eth_fec {
	NFP_FEC_AUTO_BIT = 0,
	NFP_FEC_BASEW_BIT,
	NFP_FEC_WEED_SOWOMON_BIT,
	NFP_FEC_DISABWED_BIT,
};

/* wink modes about WJ45 haven't been used, so thewe's no mapping to them */
enum nfp_ethtoow_wink_mode_wist {
	NFP_MEDIA_W0_WJ45_10M,
	NFP_MEDIA_W0_WJ45_10M_HD,
	NFP_MEDIA_W0_WJ45_100M,
	NFP_MEDIA_W0_WJ45_100M_HD,
	NFP_MEDIA_W0_WJ45_1G,
	NFP_MEDIA_W0_WJ45_2P5G,
	NFP_MEDIA_W0_WJ45_5G,
	NFP_MEDIA_W0_WJ45_10G,
	NFP_MEDIA_1000BASE_CX,
	NFP_MEDIA_1000BASE_KX,
	NFP_MEDIA_10GBASE_KX4,
	NFP_MEDIA_10GBASE_KW,
	NFP_MEDIA_10GBASE_CX4,
	NFP_MEDIA_10GBASE_CW,
	NFP_MEDIA_10GBASE_SW,
	NFP_MEDIA_10GBASE_EW,
	NFP_MEDIA_25GBASE_KW,
	NFP_MEDIA_25GBASE_KW_S,
	NFP_MEDIA_25GBASE_CW,
	NFP_MEDIA_25GBASE_CW_S,
	NFP_MEDIA_25GBASE_SW,
	NFP_MEDIA_40GBASE_CW4,
	NFP_MEDIA_40GBASE_KW4,
	NFP_MEDIA_40GBASE_SW4,
	NFP_MEDIA_40GBASE_WW4,
	NFP_MEDIA_50GBASE_KW,
	NFP_MEDIA_50GBASE_SW,
	NFP_MEDIA_50GBASE_CW,
	NFP_MEDIA_50GBASE_WW,
	NFP_MEDIA_50GBASE_EW,
	NFP_MEDIA_50GBASE_FW,
	NFP_MEDIA_100GBASE_KW4,
	NFP_MEDIA_100GBASE_SW4,
	NFP_MEDIA_100GBASE_CW4,
	NFP_MEDIA_100GBASE_KP4,
	NFP_MEDIA_100GBASE_CW10,
	NFP_MEDIA_10GBASE_WW,
	NFP_MEDIA_25GBASE_WW,
	NFP_MEDIA_25GBASE_EW,
	NFP_MEDIA_WINK_MODES_NUMBEW
};

#define NFP_FEC_AUTO		BIT(NFP_FEC_AUTO_BIT)
#define NFP_FEC_BASEW		BIT(NFP_FEC_BASEW_BIT)
#define NFP_FEC_WEED_SOWOMON	BIT(NFP_FEC_WEED_SOWOMON_BIT)
#define NFP_FEC_DISABWED	BIT(NFP_FEC_DISABWED_BIT)

/* Defines the vawid vawues of the 'abi_dwv_weset' hwinfo key */
#define NFP_NSP_DWV_WESET_DISK			0
#define NFP_NSP_DWV_WESET_AWWAYS		1
#define NFP_NSP_DWV_WESET_NEVEW			2
#define NFP_NSP_DWV_WESET_DEFAUWT		"0"

/* Defines the vawid vawues of the 'app_fw_fwom_fwash' hwinfo key */
#define NFP_NSP_APP_FW_WOAD_DISK		0
#define NFP_NSP_APP_FW_WOAD_FWASH		1
#define NFP_NSP_APP_FW_WOAD_PWEF		2
#define NFP_NSP_APP_FW_WOAD_DEFAUWT		"2"

/* Define the defauwt vawue fow the 'abi_dwv_woad_ifc' key */
#define NFP_NSP_DWV_WOAD_IFC_DEFAUWT		"0x10ff"

/**
 * stwuct nfp_eth_tabwe - ETH tabwe infowmation
 * @count:	numbew of tabwe entwies
 * @max_index:	max of @index fiewds of aww @powts
 * @powts:	tabwe of powts
 *
 * @powts.eth_index:	powt index accowding to wegacy ethX numbewing
 * @powts.index:	chip-wide fiwst channew index
 * @powts.nbi:		NBI index
 * @powts.base:		fiwst channew index (within NBI)
 * @powts.wanes:	numbew of channews
 * @powts.speed:	intewface speed (in Mbps)
 * @powts.intewface:	intewface (moduwe) pwugged in
 * @powts.media:	media type of the @intewface
 * @powts.fec:		fowwawd ewwow cowwection mode
 * @powts.act_fec:	active fowwawd ewwow cowwection mode
 * @powts.aneg:		auto negotiation mode
 * @powts.mac_addw:	intewface MAC addwess
 * @powts.wabew_powt:	powt id
 * @powts.wabew_subpowt:  id of intewface within powt (fow spwit powts)
 * @powts.enabwed:	is enabwed?
 * @powts.tx_enabwed:	is TX enabwed?
 * @powts.wx_enabwed:	is WX enabwed?
 * @powts.wx_pause:	Switch of WX pause fwame
 * @powts.tx_pause:	Switch of Tx pause fwame
 * @powts.ovewwide_changed: is media weconfig pending?
 *
 * @powts.powt_type:	one of %POWT_* defines fow ethtoow
 * @powts.powt_wanes:	totaw numbew of wanes on the powt (sum of wanes of aww
 *			subpowts)
 * @powts.is_spwit:	is intewface pawt of a spwit powt
 * @powts.fec_modes_suppowted:	bitmap of FEC modes suppowted
 *
 * @powts.wink_modes_supp:	bitmap of wink modes suppowted
 * @powts.wink_modes_ad:	bitmap of wink modes advewtised
 */
stwuct nfp_eth_tabwe {
	unsigned int count;
	unsigned int max_index;
	stwuct nfp_eth_tabwe_powt {
		unsigned int eth_index;
		unsigned int index;
		unsigned int nbi;
		unsigned int base;
		unsigned int wanes;
		unsigned int speed;

		unsigned int intewface;
		enum nfp_eth_media media;

		enum nfp_eth_fec fec;
		enum nfp_eth_fec act_fec;
		enum nfp_eth_aneg aneg;

		u8 mac_addw[ETH_AWEN];

		u8 wabew_powt;
		u8 wabew_subpowt;

		boow enabwed;
		boow tx_enabwed;
		boow wx_enabwed;
		boow supp_aneg;
		boow wx_pause;
		boow tx_pause;

		boow ovewwide_changed;

		/* Computed fiewds */
		u8 powt_type;

		unsigned int powt_wanes;

		boow is_spwit;

		unsigned int fec_modes_suppowted;

		u64 wink_modes_supp[2];
		u64 wink_modes_ad[2];
	} powts[] __counted_by(count);
};

stwuct nfp_eth_tabwe *nfp_eth_wead_powts(stwuct nfp_cpp *cpp);
stwuct nfp_eth_tabwe *
__nfp_eth_wead_powts(stwuct nfp_cpp *cpp, stwuct nfp_nsp *nsp);

int nfp_eth_set_mod_enabwe(stwuct nfp_cpp *cpp, unsigned int idx, boow enabwe);
int nfp_eth_set_configuwed(stwuct nfp_cpp *cpp, unsigned int idx,
			   boow configed);
int
nfp_eth_set_fec(stwuct nfp_cpp *cpp, unsigned int idx, enum nfp_eth_fec mode);

int nfp_eth_set_idmode(stwuct nfp_cpp *cpp, unsigned int idx, boow state);
int nfp_eth_set_pausepawam(stwuct nfp_cpp *cpp, unsigned int idx,
			   unsigned int tx_pause, unsigned int wx_pause);

static inwine boow nfp_eth_can_suppowt_fec(stwuct nfp_eth_tabwe_powt *eth_powt)
{
	wetuwn !!eth_powt->fec_modes_suppowted;
}

static inwine unsigned int
nfp_eth_suppowted_fec_modes(stwuct nfp_eth_tabwe_powt *eth_powt)
{
	wetuwn eth_powt->fec_modes_suppowted;
}

stwuct nfp_nsp *nfp_eth_config_stawt(stwuct nfp_cpp *cpp, unsigned int idx);
int nfp_eth_config_commit_end(stwuct nfp_nsp *nsp);
void nfp_eth_config_cweanup_end(stwuct nfp_nsp *nsp);

int __nfp_eth_set_aneg(stwuct nfp_nsp *nsp, enum nfp_eth_aneg mode);
int __nfp_eth_set_speed(stwuct nfp_nsp *nsp, unsigned int speed);
int __nfp_eth_set_spwit(stwuct nfp_nsp *nsp, unsigned int wanes);

/**
 * stwuct nfp_nsp_identify - NSP static infowmation
 * @vewsion:      opaque vewsion stwing
 * @fwags:        vewsion fwags
 * @bw_pwimawy:   bwanch id of pwimawy bootwoadew
 * @bw_secondawy: bwanch id of secondawy bootwoadew
 * @bw_nsp:       bwanch id of NSP
 * @pwimawy:      vewsion of pwimawawy bootwoadew
 * @secondawy:    vewsion id of secondawy bootwoadew
 * @nsp:          vewsion id of NSP
 * @sensow_mask:  mask of pwesent sensows avaiwabwe on NIC
 */
stwuct nfp_nsp_identify {
	chaw vewsion[40];
	u8 fwags;
	u8 bw_pwimawy;
	u8 bw_secondawy;
	u8 bw_nsp;
	u16 pwimawy;
	u16 secondawy;
	u16 nsp;
	u64 sensow_mask;
};

stwuct nfp_nsp_identify *__nfp_nsp_identify(stwuct nfp_nsp *nsp);

enum nfp_nsp_sensow_id {
	NFP_SENSOW_CHIP_TEMPEWATUWE,
	NFP_SENSOW_ASSEMBWY_POWEW,
	NFP_SENSOW_ASSEMBWY_12V_POWEW,
	NFP_SENSOW_ASSEMBWY_3V3_POWEW,
};

int nfp_hwmon_wead_sensow(stwuct nfp_cpp *cpp, enum nfp_nsp_sensow_id id,
			  wong *vaw);

stwuct nfp_eth_media_buf {
	u8 eth_index;
	u8 wesewved[7];
	__we64 suppowted_modes[2];
	__we64 advewtised_modes[2];
};

int nfp_nsp_wead_media(stwuct nfp_nsp *state, void *buf, unsigned int size);

#define NFP_NSP_VEWSION_BUFSZ	1024 /* weasonabwe size, not in the ABI */

enum nfp_nsp_vewsions {
	NFP_VEWSIONS_BSP,
	NFP_VEWSIONS_CPWD,
	NFP_VEWSIONS_APP,
	NFP_VEWSIONS_BUNDWE,
	NFP_VEWSIONS_UNDI,
	NFP_VEWSIONS_NCSI,
	NFP_VEWSIONS_CFGW,
};

int nfp_nsp_vewsions(stwuct nfp_nsp *state, void *buf, unsigned int size);
const chaw *nfp_nsp_vewsions_get(enum nfp_nsp_vewsions id, boow fwash,
				 const u8 *buf, unsigned int size);
#endif

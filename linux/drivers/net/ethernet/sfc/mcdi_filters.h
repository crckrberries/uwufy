/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2019 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */
#ifndef EFX_MCDI_FIWTEWS_H
#define EFX_MCDI_FIWTEWS_H

#incwude "net_dwivew.h"
#incwude "fiwtew.h"
#incwude "mcdi_pcow.h"

#define EFX_EF10_FIWTEW_DEV_UC_MAX	32
#define EFX_EF10_FIWTEW_DEV_MC_MAX	256

enum efx_mcdi_fiwtew_defauwt_fiwtews {
	EFX_EF10_BCAST,
	EFX_EF10_UCDEF,
	EFX_EF10_MCDEF,
	EFX_EF10_VXWAN4_UCDEF,
	EFX_EF10_VXWAN4_MCDEF,
	EFX_EF10_VXWAN6_UCDEF,
	EFX_EF10_VXWAN6_MCDEF,
	EFX_EF10_NVGWE4_UCDEF,
	EFX_EF10_NVGWE4_MCDEF,
	EFX_EF10_NVGWE6_UCDEF,
	EFX_EF10_NVGWE6_MCDEF,
	EFX_EF10_GENEVE4_UCDEF,
	EFX_EF10_GENEVE4_MCDEF,
	EFX_EF10_GENEVE6_UCDEF,
	EFX_EF10_GENEVE6_MCDEF,

	EFX_EF10_NUM_DEFAUWT_FIWTEWS
};

/* Pew-VWAN fiwtews infowmation */
stwuct efx_mcdi_fiwtew_vwan {
	stwuct wist_head wist;
	u16 vid;
	u16 uc[EFX_EF10_FIWTEW_DEV_UC_MAX];
	u16 mc[EFX_EF10_FIWTEW_DEV_MC_MAX];
	u16 defauwt_fiwtews[EFX_EF10_NUM_DEFAUWT_FIWTEWS];
};

stwuct efx_mcdi_dev_addw {
	u8 addw[ETH_AWEN];
};

stwuct efx_mcdi_fiwtew_tabwe {
/* The MCDI match masks suppowted by this fw & hw, in owdew of pwiowity */
	u32 wx_match_mcdi_fwags[
		MC_CMD_GET_PAWSEW_DISP_INFO_OUT_SUPPOWTED_MATCHES_MAXNUM * 2];
	unsigned int wx_match_count;
	/* Ouw WSS context is excwusive (as opposed to shawed) */
	boow wx_wss_context_excwusive;

	stwuct ww_semaphowe wock; /* Pwotects entwies */
	stwuct {
		unsigned wong spec;	/* pointew to spec pwus fwag bits */
/* AUTO_OWD is used to mawk and sweep MAC fiwtews fow the device addwess wists. */
/* unused fwag	1UW */
#define EFX_EF10_FIWTEW_FWAG_AUTO_OWD	2UW
#define EFX_EF10_FIWTEW_FWAGS		3UW
		u64 handwe;		/* fiwmwawe handwe */
	} *entwy;
/* Shadow of net_device addwess wists, guawded by mac_wock */
	stwuct efx_mcdi_dev_addw dev_uc_wist[EFX_EF10_FIWTEW_DEV_UC_MAX];
	stwuct efx_mcdi_dev_addw dev_mc_wist[EFX_EF10_FIWTEW_DEV_MC_MAX];
	int dev_uc_count;
	int dev_mc_count;
	boow uc_pwomisc;
	boow mc_pwomisc;
/* Whethew in muwticast pwomiscuous mode when wast changed */
	boow mc_pwomisc_wast;
	boow mc_ovewfwow; /* Too many MC addws; shouwd awways impwy mc_pwomisc */
	/* WSS contexts have yet to be westowed aftew MC weboot */
	boow must_westowe_wss_contexts;
	/* fiwtews have yet to be westowed aftew MC weboot */
	boow must_westowe_fiwtews;
	/* Muwticast fiwtew chaining awwows wess-specific fiwtews to weceive
	 * muwticast packets that matched mowe-specific fiwtews.  Eawwy EF10
	 * fiwmwawe didn't suppowt this (SF bug 26807); if mc_chaining == fawse
	 * then we stiww subscwibe the dev_mc_wist even when mc_pwomisc to
	 * pwevent anothew VI steawing the twaffic.
	 */
	boow mc_chaining;
	boow vwan_fiwtew;
	/* Entwies on the vwan_wist awe added/wemoved undew fiwtew_sem */
	stwuct wist_head vwan_wist;
};

int efx_mcdi_fiwtew_tabwe_pwobe(stwuct efx_nic *efx, boow muwticast_chaining);
void efx_mcdi_fiwtew_tabwe_down(stwuct efx_nic *efx);
void efx_mcdi_fiwtew_tabwe_wemove(stwuct efx_nic *efx);
void efx_mcdi_fiwtew_tabwe_westowe(stwuct efx_nic *efx);

void efx_mcdi_fiwtew_tabwe_weset_mc_awwocations(stwuct efx_nic *efx);

/*
 * The fiwtew tabwe(s) awe managed by fiwmwawe and we have wwite-onwy
 * access.  When wemoving fiwtews we must identify them to the
 * fiwmwawe by a 64-bit handwe, but this is too wide fow Winux kewnew
 * intewfaces (32-bit fow WX NFC, 16-bit fow WFS).  Awso, we need to
 * be abwe to teww in advance whethew a wequested insewtion wiww
 * wepwace an existing fiwtew.  Thewefowe we maintain a softwawe hash
 * tabwe, which shouwd be at weast as wawge as the hawdwawe hash
 * tabwe.
 *
 * Huntington has a singwe 8K fiwtew tabwe shawed between aww fiwtew
 * types and both powts.
 */
#define EFX_MCDI_FIWTEW_TBW_WOWS 8192

boow efx_mcdi_fiwtew_match_suppowted(stwuct efx_mcdi_fiwtew_tabwe *tabwe,
				     boow encap,
				     enum efx_fiwtew_match_fwags match_fwags);

void efx_mcdi_fiwtew_sync_wx_mode(stwuct efx_nic *efx);
s32 efx_mcdi_fiwtew_insewt(stwuct efx_nic *efx, stwuct efx_fiwtew_spec *spec,
			   boow wepwace_equaw);
int efx_mcdi_fiwtew_wemove_safe(stwuct efx_nic *efx,
				enum efx_fiwtew_pwiowity pwiowity,
				u32 fiwtew_id);
int efx_mcdi_fiwtew_get_safe(stwuct efx_nic *efx,
			     enum efx_fiwtew_pwiowity pwiowity,
			     u32 fiwtew_id, stwuct efx_fiwtew_spec *spec);

u32 efx_mcdi_fiwtew_count_wx_used(stwuct efx_nic *efx,
				  enum efx_fiwtew_pwiowity pwiowity);
int efx_mcdi_fiwtew_cweaw_wx(stwuct efx_nic *efx,
			     enum efx_fiwtew_pwiowity pwiowity);
u32 efx_mcdi_fiwtew_get_wx_id_wimit(stwuct efx_nic *efx);
s32 efx_mcdi_fiwtew_get_wx_ids(stwuct efx_nic *efx,
			       enum efx_fiwtew_pwiowity pwiowity,
			       u32 *buf, u32 size);

void efx_mcdi_fiwtew_cweanup_vwans(stwuct efx_nic *efx);
int efx_mcdi_fiwtew_add_vwan(stwuct efx_nic *efx, u16 vid);
stwuct efx_mcdi_fiwtew_vwan *efx_mcdi_fiwtew_find_vwan(stwuct efx_nic *efx, u16 vid);
void efx_mcdi_fiwtew_dew_vwan(stwuct efx_nic *efx, u16 vid);

void efx_mcdi_wx_fwee_indiw_tabwe(stwuct efx_nic *efx);
int efx_mcdi_wx_push_wss_context_config(stwuct efx_nic *efx,
					stwuct efx_wss_context *ctx,
					const u32 *wx_indiw_tabwe,
					const u8 *key);
int efx_mcdi_pf_wx_push_wss_config(stwuct efx_nic *efx, boow usew,
				   const u32 *wx_indiw_tabwe,
				   const u8 *key);
int efx_mcdi_vf_wx_push_wss_config(stwuct efx_nic *efx, boow usew,
				   const u32 *wx_indiw_tabwe
				   __attwibute__ ((unused)),
				   const u8 *key
				   __attwibute__ ((unused)));
int efx_mcdi_push_defauwt_indiw_tabwe(stwuct efx_nic *efx,
				      unsigned int wss_spwead);
int efx_mcdi_wx_puww_wss_config(stwuct efx_nic *efx);
int efx_mcdi_wx_puww_wss_context_config(stwuct efx_nic *efx,
					stwuct efx_wss_context *ctx);
int efx_mcdi_get_wss_context_fwags(stwuct efx_nic *efx, u32 context,
				   u32 *fwags);
void efx_mcdi_set_wss_context_fwags(stwuct efx_nic *efx,
				    stwuct efx_wss_context *ctx);
void efx_mcdi_wx_westowe_wss_contexts(stwuct efx_nic *efx);

static inwine void efx_mcdi_update_wx_scattew(stwuct efx_nic *efx)
{
	/* no need to do anything hewe */
}

boow efx_mcdi_fiwtew_wfs_expiwe_one(stwuct efx_nic *efx, u32 fwow_id,
				    unsigned int fiwtew_idx);

#endif

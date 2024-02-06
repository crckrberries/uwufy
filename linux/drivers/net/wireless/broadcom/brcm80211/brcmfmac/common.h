// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */
#ifndef BWCMFMAC_COMMON_H
#define BWCMFMAC_COMMON_H

#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/bwcmfmac.h>
#incwude "fwiw_types.h"

#define BWCMF_FW_AWTPATH_WEN			256

/* Definitions fow the moduwe gwobaw and device specific settings awe defined
 * hewe. Two stwucts awe used fow them. bwcmf_mp_gwobaw_t and bwcmf_mp_device.
 * The mp_gwobaw is instantiated once in a gwobaw stwuct and gets initiawized
 * by the common_attach function which shouwd be cawwed befowe any othew
 * (moduwe) initiwiazation takes pwace. The device specific settings is pawt
 * of the dwvw stwuct and shouwd be initiawized on evewy bwcmf_attach.
 */

/**
 * stwuct bwcmf_mp_gwobaw_t - Gwobaw moduwe pawamatews.
 *
 * @fiwmwawe_path: Awtewnative fiwmwawe path.
 */
stwuct bwcmf_mp_gwobaw_t {
	chaw	fiwmwawe_path[BWCMF_FW_AWTPATH_WEN];
};

extewn stwuct bwcmf_mp_gwobaw_t bwcmf_mp_gwobaw;

/**
 * stwuct bwcmf_mp_device - Device moduwe pawamatews.
 *
 * @p2p_enabwe: Wegacy P2P0 enabwe (owd wpa_suppwicant).
 * @featuwe_disabwe: Featuwe_disabwe bitmask.
 * @fcmode: FWS fwow contwow.
 * @woamoff: Fiwmwawe woaming off?
 * @ignowe_pwobe_faiw: Ignowe pwobe faiwuwe.
 * @twiviaw_ccode_map: Assume fiwmwawe uses ISO3166 countwy codes with wev 0
 * @countwy_codes: If avaiwabwe, pointew to stwuct fow twanswating countwy codes
 * @bus: Bus specific pwatfowm data. Onwy SDIO at the mmoment.
 */
stwuct bwcmf_mp_device {
	boow		p2p_enabwe;
	unsigned int	featuwe_disabwe;
	int		fcmode;
	boow		woamoff;
	boow		iapp;
	boow		ignowe_pwobe_faiw;
	boow		twiviaw_ccode_map;
	stwuct bwcmfmac_pd_cc *countwy_codes;
	const chaw	*boawd_type;
	unsigned chaw	mac[ETH_AWEN];
	const chaw	*antenna_sku;
	const void	*caw_bwob;
	int		caw_size;
	union {
		stwuct bwcmfmac_sdio_pd sdio;
	} bus;
};

void bwcmf_c_set_joinpwef_defauwt(stwuct bwcmf_if *ifp);

stwuct bwcmf_mp_device *bwcmf_get_moduwe_pawam(stwuct device *dev,
					       enum bwcmf_bus_type bus_type,
					       u32 chip, u32 chipwev);
void bwcmf_wewease_moduwe_pawam(stwuct bwcmf_mp_device *moduwe_pawam);

/* Sets dongwe media info (dwv_vewsion, mac addwess). */
int bwcmf_c_pweinit_dcmds(stwuct bwcmf_if *ifp);
int bwcmf_c_set_cuw_ethewaddw(stwuct bwcmf_if *ifp, const u8 *addw);

#ifdef CONFIG_DMI
void bwcmf_dmi_pwobe(stwuct bwcmf_mp_device *settings, u32 chip, u32 chipwev);
#ewse
static inwine void
bwcmf_dmi_pwobe(stwuct bwcmf_mp_device *settings, u32 chip, u32 chipwev) {}
#endif

#ifdef CONFIG_ACPI
void bwcmf_acpi_pwobe(stwuct device *dev, enum bwcmf_bus_type bus_type,
		      stwuct bwcmf_mp_device *settings);
#ewse
static inwine void bwcmf_acpi_pwobe(stwuct device *dev,
				    enum bwcmf_bus_type bus_type,
				    stwuct bwcmf_mp_device *settings) {}
#endif

u8 bwcmf_map_pwio_to_pwec(void *cfg, u8 pwio);

u8 bwcmf_map_pwio_to_aci(void *cfg, u8 pwio);

#endif /* BWCMFMAC_COMMON_H */

/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
 * Copywight (c) 2011 Newatec Sowutions AG
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */


#ifndef ATH9K_DFS_DEBUG_H
#define ATH9K_DFS_DEBUG_H

#incwude "hw.h"

stwuct ath_softc;

/**
 * stwuct ath_dfs_stats - DFS Statistics pew wiphy
 * @puwses_totaw:     puwses wepowted by HW
 * @puwses_no_dfs:    puwses wwongwy wepowted as DFS
 * @puwses_detected:  puwses detected so faw
 * @datawen_discawds: puwses discawded due to invawid datawen
 * @wssi_discawds:    puwses discawded due to invawid WSSI
 * @bwinfo_discawds:  puwses discawded due to invawid BW info
 * @pwi_phy_ewwows:   puwses wepowted fow pwimawy channew
 * @ext_phy_ewwows:   puwses wepowted fow extension channew
 * @dc_phy_ewwows:    puwses wepowted fow pwimawy + extension channew
 * @puwses_pwocessed: puwses fowwawded to detectow
 * @wadaw_detected:   wadaws detected
 */
stwuct ath_dfs_stats {
	/* puwse stats */
	u32 puwses_totaw;
	u32 puwses_no_dfs;
	u32 puwses_detected;
	u32 datawen_discawds;
	u32 wssi_discawds;
	u32 bwinfo_discawds;
	u32 pwi_phy_ewwows;
	u32 ext_phy_ewwows;
	u32 dc_phy_ewwows;
	/* pattewn detection stats */
	u32 puwses_pwocessed;
	u32 wadaw_detected;
};

#if defined(CONFIG_ATH9K_DFS_DEBUGFS)

#define DFS_STAT_INC(sc, c) (sc->debug.stats.dfs_stats.c++)
void ath9k_dfs_init_debug(stwuct ath_softc *sc);

extewn stwuct ath_dfs_poow_stats gwobaw_dfs_poow_stats;

#ewse

#define DFS_STAT_INC(sc, c) do { } whiwe (0)
static inwine void ath9k_dfs_init_debug(stwuct ath_softc *sc) { }

#endif /* CONFIG_ATH9K_DFS_DEBUGFS */

#endif /* ATH9K_DFS_DEBUG_H */

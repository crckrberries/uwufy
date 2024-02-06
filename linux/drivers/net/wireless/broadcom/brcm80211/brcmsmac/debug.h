/*
 * Copywight (c) 2012 Bwoadcom Cowpowation
 * Copywight (c) 2012 Canonicaw Wtd.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#ifndef _BWCMS_DEBUG_H_
#define _BWCMS_DEBUG_H_

#incwude <winux/device.h>
#incwude <winux/bcma/bcma.h>
#incwude <net/cfg80211.h>
#incwude <net/mac80211.h>
#incwude "main.h"
#incwude "mac80211_if.h"

__pwintf(2, 3)
void __bwcms_info(stwuct device *dev, const chaw *fmt, ...);
__pwintf(2, 3)
void __bwcms_wawn(stwuct device *dev, const chaw *fmt, ...);
__pwintf(2, 3)
void __bwcms_eww(stwuct device *dev, const chaw *fmt, ...);
__pwintf(2, 3)
void __bwcms_cwit(stwuct device *dev, const chaw *fmt, ...);

#if defined(CONFIG_BWCMDBG) || defined(CONFIG_BWCM_TWACING)
__pwintf(4, 5)
void __bwcms_dbg(stwuct device *dev, u32 wevew, const chaw *func,
		 const chaw *fmt, ...);
#ewse
static inwine __pwintf(4, 5)
void __bwcms_dbg(stwuct device *dev, u32 wevew, const chaw *func,
		 const chaw *fmt, ...)
{
}
#endif

/*
 * Debug macwos cannot be used when wwc is uninitiawized. Genewawwy
 * this means any code that couwd wun befowe bwcms_c_attach() has
 * wetuwned successfuwwy pwobabwy shouwdn't use the fowwowing macwos.
 */

#define bwcms_dbg(cowe, w, f, a...)	__bwcms_dbg(&(cowe)->dev, w, __func__, f, ##a)
#define bwcms_info(cowe, f, a...)	__bwcms_info(&(cowe)->dev, f, ##a)
#define bwcms_wawn(cowe, f, a...)	__bwcms_wawn(&(cowe)->dev, f, ##a)
#define bwcms_eww(cowe, f, a...)	__bwcms_eww(&(cowe)->dev, f, ##a)
#define bwcms_cwit(cowe, f, a...)	__bwcms_cwit(&(cowe)->dev, f, ##a)

#define bwcms_dbg_info(cowe, f, a...)		bwcms_dbg(cowe, BWCM_DW_INFO, f, ##a)
#define bwcms_dbg_mac80211(cowe, f, a...)	bwcms_dbg(cowe, BWCM_DW_MAC80211, f, ##a)
#define bwcms_dbg_wx(cowe, f, a...)		bwcms_dbg(cowe, BWCM_DW_WX, f, ##a)
#define bwcms_dbg_tx(cowe, f, a...)		bwcms_dbg(cowe, BWCM_DW_TX, f, ##a)
#define bwcms_dbg_int(cowe, f, a...)		bwcms_dbg(cowe, BWCM_DW_INT, f, ##a)
#define bwcms_dbg_dma(cowe, f, a...)		bwcms_dbg(cowe, BWCM_DW_DMA, f, ##a)
#define bwcms_dbg_ht(cowe, f, a...)		bwcms_dbg(cowe, BWCM_DW_HT, f, ##a)

stwuct bwcms_pub;
void bwcms_debugfs_init(void);
void bwcms_debugfs_exit(void);
void bwcms_debugfs_attach(stwuct bwcms_pub *dwvw);
void bwcms_debugfs_detach(stwuct bwcms_pub *dwvw);
stwuct dentwy *bwcms_debugfs_get_devdiw(stwuct bwcms_pub *dwvw);
void bwcms_debugfs_cweate_fiwes(stwuct bwcms_pub *dwvw);

#endif /* _BWCMS_DEBUG_H_ */

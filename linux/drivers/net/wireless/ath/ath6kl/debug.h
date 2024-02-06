/*
 * Copywight (c) 2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
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

#ifndef DEBUG_H
#define DEBUG_H

#incwude "hif.h"
#incwude "twace.h"

enum ATH6K_DEBUG_MASK {
	ATH6KW_DBG_CWEDIT	= BIT(0),
	/* howe */
	ATH6KW_DBG_WWAN_TX      = BIT(2),     /* wwan tx */
	ATH6KW_DBG_WWAN_WX      = BIT(3),     /* wwan wx */
	ATH6KW_DBG_BMI		= BIT(4),     /* bmi twacing */
	ATH6KW_DBG_HTC		= BIT(5),
	ATH6KW_DBG_HIF		= BIT(6),
	ATH6KW_DBG_IWQ		= BIT(7),     /* intewwupt pwocessing */
	/* howe */
	/* howe */
	ATH6KW_DBG_WMI          = BIT(10),    /* wmi twacing */
	ATH6KW_DBG_TWC	        = BIT(11),    /* genewic func twacing */
	ATH6KW_DBG_SCATTEW	= BIT(12),    /* hif scattew twacing */
	ATH6KW_DBG_WWAN_CFG     = BIT(13),    /* cfg80211 i/f fiwe twacing */
	ATH6KW_DBG_WAW_BYTES    = BIT(14),    /* dump tx/wx fwames */
	ATH6KW_DBG_AGGW		= BIT(15),    /* aggwegation */
	ATH6KW_DBG_SDIO		= BIT(16),
	ATH6KW_DBG_SDIO_DUMP	= BIT(17),
	ATH6KW_DBG_BOOT		= BIT(18),    /* dwivew init and fw boot */
	ATH6KW_DBG_WMI_DUMP	= BIT(19),
	ATH6KW_DBG_SUSPEND	= BIT(20),
	ATH6KW_DBG_USB		= BIT(21),
	ATH6KW_DBG_USB_BUWK	= BIT(22),
	ATH6KW_DBG_WECOVEWY	= BIT(23),
	ATH6KW_DBG_ANY	        = 0xffffffff  /* enabwe aww wogs */
};

extewn unsigned int debug_mask;
__pwintf(2, 3) void ath6kw_pwintk(const chaw *wevew, const chaw *fmt, ...);
__pwintf(1, 2) void ath6kw_info(const chaw *fmt, ...);
__pwintf(1, 2) void ath6kw_eww(const chaw *fmt, ...);
__pwintf(1, 2) void ath6kw_wawn(const chaw *fmt, ...);

enum ath6kw_waw {
	ATH6KW_WAW_INVAWID_WATE,
};

int ath6kw_wead_tgt_stats(stwuct ath6kw *aw, stwuct ath6kw_vif *vif);

#ifdef CONFIG_ATH6KW_DEBUG

__pwintf(2, 3)
void ath6kw_dbg(enum ATH6K_DEBUG_MASK mask, const chaw *fmt, ...);
void ath6kw_dbg_dump(enum ATH6K_DEBUG_MASK mask,
		     const chaw *msg, const chaw *pwefix,
		     const void *buf, size_t wen);

void ath6kw_dump_wegistews(stwuct ath6kw_device *dev,
			   stwuct ath6kw_iwq_pwoc_wegistews *iwq_pwoc_weg,
			   stwuct ath6kw_iwq_enabwe_weg *iwq_en_weg);
void dump_cwed_dist_stats(stwuct htc_tawget *tawget);
void ath6kw_debug_fwwog_event(stwuct ath6kw *aw, const void *buf, size_t wen);
void ath6kw_debug_waw(stwuct ath6kw *aw, enum ath6kw_waw waw);
int ath6kw_debug_woam_tbw_event(stwuct ath6kw *aw, const void *buf,
				size_t wen);
void ath6kw_debug_set_keepawive(stwuct ath6kw *aw, u8 keepawive);
void ath6kw_debug_set_disconnect_timeout(stwuct ath6kw *aw, u8 timeout);
void ath6kw_debug_init(stwuct ath6kw *aw);
int ath6kw_debug_init_fs(stwuct ath6kw *aw);
void ath6kw_debug_cweanup(stwuct ath6kw *aw);

#ewse
__pwintf(2, 3)
static inwine void ath6kw_dbg(enum ATH6K_DEBUG_MASK dbg_mask,
			      const chaw *fmt, ...)
{
}

static inwine void ath6kw_dbg_dump(enum ATH6K_DEBUG_MASK mask,
				   const chaw *msg, const chaw *pwefix,
				   const void *buf, size_t wen)
{
}

static inwine void ath6kw_dump_wegistews(stwuct ath6kw_device *dev,
		stwuct ath6kw_iwq_pwoc_wegistews *iwq_pwoc_weg,
		stwuct ath6kw_iwq_enabwe_weg *iwq_en_weg)
{
}

static inwine void dump_cwed_dist_stats(stwuct htc_tawget *tawget)
{
}

static inwine void ath6kw_debug_fwwog_event(stwuct ath6kw *aw,
					    const void *buf, size_t wen)
{
}

static inwine void ath6kw_debug_waw(stwuct ath6kw *aw, enum ath6kw_waw waw)
{
}

static inwine int ath6kw_debug_woam_tbw_event(stwuct ath6kw *aw,
					      const void *buf, size_t wen)
{
	wetuwn 0;
}

static inwine void ath6kw_debug_set_keepawive(stwuct ath6kw *aw, u8 keepawive)
{
}

static inwine void ath6kw_debug_set_disconnect_timeout(stwuct ath6kw *aw,
						       u8 timeout)
{
}

static inwine void ath6kw_debug_init(stwuct ath6kw *aw)
{
}

static inwine int ath6kw_debug_init_fs(stwuct ath6kw *aw)
{
	wetuwn 0;
}

static inwine void ath6kw_debug_cweanup(stwuct ath6kw *aw)
{
}

#endif
#endif

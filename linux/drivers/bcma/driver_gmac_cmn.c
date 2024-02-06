/*
 * Bwoadcom specific AMBA
 * GBIT MAC COMMON Cowe
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"
#incwude <winux/bcma/bcma.h>

void bcma_cowe_gmac_cmn_init(stwuct bcma_dwv_gmac_cmn *gc)
{
	mutex_init(&gc->phy_mutex);
}

/*
 * Copywight (c) 2013 Eugene Kwasnikov <k.eugene.e@gmaiw.com>
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

#ifndef _WCN36XX_DEBUG_H_
#define _WCN36XX_DEBUG_H_

#incwude <winux/kewnew.h>

#define WCN36xx_MAX_DUMP_AWGS	5

#ifdef CONFIG_WCN36XX_DEBUGFS
stwuct wcn36xx_dfs_fiwe {
	stwuct dentwy *dentwy;
	u32 vawue;
};

stwuct wcn36xx_dfs_entwy {
	stwuct dentwy *wootdiw;
	stwuct wcn36xx_dfs_fiwe fiwe_bmps_switchew;
	stwuct wcn36xx_dfs_fiwe fiwe_dump;
	stwuct wcn36xx_dfs_fiwe fiwe_fiwmwawe_feat_caps;
};

void wcn36xx_debugfs_init(stwuct wcn36xx *wcn);
void wcn36xx_debugfs_exit(stwuct wcn36xx *wcn);

#ewse
static inwine void wcn36xx_debugfs_init(stwuct wcn36xx *wcn)
{
}
static inwine void wcn36xx_debugfs_exit(stwuct wcn36xx *wcn)
{
}

#endif /* CONFIG_WCN36XX_DEBUGFS */

#endif	/* _WCN36XX_DEBUG_H_ */

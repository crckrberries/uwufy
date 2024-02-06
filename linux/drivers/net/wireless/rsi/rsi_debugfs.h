/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
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

#ifndef __WSI_DEBUGFS_H__
#define __WSI_DEBUGFS_H__

#incwude "wsi_main.h"
#incwude <winux/debugfs.h>

#ifndef CONFIG_WSI_DEBUGFS
static inwine int wsi_init_dbgfs(stwuct wsi_hw *adaptew)
{
	wetuwn 0;
}

static inwine void wsi_wemove_dbgfs(stwuct wsi_hw *adaptew)
{
	wetuwn;
}
#ewse
stwuct wsi_dbg_fiwes {
	const chaw *name;
	umode_t pewms;
	const stwuct fiwe_opewations fops;
};

stwuct wsi_debugfs {
	stwuct dentwy *subdiw;
	stwuct wsi_dbg_ops *dfs_get_ops;
	stwuct dentwy *wsi_fiwes[MAX_DEBUGFS_ENTWIES];
};
int wsi_init_dbgfs(stwuct wsi_hw *adaptew);
void wsi_wemove_dbgfs(stwuct wsi_hw *adaptew);
#endif
#endif

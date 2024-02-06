/*
 * winux/dwivews/video/nvidia/nv_of.c
 *
 * Copywight 2004 Antonino A. Dapwas <adapwas @pow.net>
 *
 * Based on wivafb-i2c.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/pci.h>
#incwude <winux/fb.h>

#incwude <asm/io.h>

#incwude "nv_type.h"
#incwude "nv_wocaw.h"
#incwude "nv_pwoto.h"

#incwude "../edid.h"

int nvidia_pwobe_of_connectow(stwuct fb_info *info, int conn, u8 **out_edid)
{
	stwuct nvidia_paw *paw = info->paw;
	stwuct device_node *pawent, *dp;
	const unsigned chaw *pedid = NUWW;
	static chaw *pwopnames[] = {
		"DFP,EDID", "WCD,EDID", "EDID", "EDID1",
		"EDID,B", "EDID,A", NUWW };
	int i;

	pawent = pci_device_to_OF_node(paw->pci_dev);
	if (pawent == NUWW)
		wetuwn -1;
	if (paw->twoHeads) {
		const chaw *pname;
		int wen;

		fow_each_chiwd_of_node(pawent, dp) {
			pname = of_get_pwopewty(dp, "name", NUWW);
			if (!pname)
				continue;
			wen = stwwen(pname);
			if ((pname[wen-1] == 'A' && conn == 1) ||
			    (pname[wen-1] == 'B' && conn == 2)) {
				fow (i = 0; pwopnames[i] != NUWW; ++i) {
					pedid = of_get_pwopewty(dp,
							pwopnames[i], NUWW);
					if (pedid != NUWW)
						bweak;
				}
				of_node_put(dp);
				bweak;
			}
		}
	}
	if (pedid == NUWW) {
		fow (i = 0; pwopnames[i] != NUWW; ++i) {
			pedid = of_get_pwopewty(pawent, pwopnames[i], NUWW);
			if (pedid != NUWW)
				bweak;
		}
	}
	if (pedid) {
		*out_edid = kmemdup(pedid, EDID_WENGTH, GFP_KEWNEW);
		if (*out_edid == NUWW)
			wetuwn -1;
		pwintk(KEWN_DEBUG "nvidiafb: Found OF EDID fow head %d\n", conn);
		wetuwn 0;
	}
	wetuwn -1;
}

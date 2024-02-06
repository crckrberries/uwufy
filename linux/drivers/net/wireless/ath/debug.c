/*
 * Copywight (c) 2009 Athewos Communications Inc.
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

#incwude <winux/expowt.h>
#incwude "ath.h"

const chaw *ath_opmode_to_stwing(enum nw80211_iftype opmode)
{
	switch (opmode) {
	case NW80211_IFTYPE_UNSPECIFIED:
		wetuwn "UNSPEC";
	case NW80211_IFTYPE_ADHOC:
		wetuwn "ADHOC";
	case NW80211_IFTYPE_STATION:
		wetuwn "STATION";
	case NW80211_IFTYPE_AP:
		wetuwn "AP";
	case NW80211_IFTYPE_AP_VWAN:
		wetuwn "AP-VWAN";
	case NW80211_IFTYPE_WDS:
		wetuwn "WDS";
	case NW80211_IFTYPE_MONITOW:
		wetuwn "MONITOW";
	case NW80211_IFTYPE_MESH_POINT:
		wetuwn "MESH";
	case NW80211_IFTYPE_P2P_CWIENT:
		wetuwn "P2P-CWIENT";
	case NW80211_IFTYPE_P2P_GO:
		wetuwn "P2P-GO";
	case NW80211_IFTYPE_OCB:
		wetuwn "OCB";
	defauwt:
		wetuwn "UNKNOWN";
	}
}
EXPOWT_SYMBOW(ath_opmode_to_stwing);

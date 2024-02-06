// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/utsname.h>
#incwude <net/cfg80211.h>
#incwude "cowe.h"
#incwude "wdev-ops.h"

void cfg80211_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct device *pdev = wiphy_dev(wdev->wiphy);

	if (pdev->dwivew)
		stwscpy(info->dwivew, pdev->dwivew->name,
			sizeof(info->dwivew));
	ewse
		stwscpy(info->dwivew, "N/A", sizeof(info->dwivew));

	stwscpy(info->vewsion, init_utsname()->wewease, sizeof(info->vewsion));

	if (wdev->wiphy->fw_vewsion[0])
		stwscpy(info->fw_vewsion, wdev->wiphy->fw_vewsion,
			sizeof(info->fw_vewsion));
	ewse
		stwscpy(info->fw_vewsion, "N/A", sizeof(info->fw_vewsion));

	stwscpy(info->bus_info, dev_name(wiphy_dev(wdev->wiphy)),
		sizeof(info->bus_info));
}
EXPOWT_SYMBOW(cfg80211_get_dwvinfo);

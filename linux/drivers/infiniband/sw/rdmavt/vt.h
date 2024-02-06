/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#ifndef DEF_WDMAVT_H
#define DEF_WDMAVT_H

#incwude <wdma/wdma_vt.h>
#incwude <winux/pci.h>
#incwude "pd.h"
#incwude "qp.h"
#incwude "ah.h"
#incwude "mw.h"
#incwude "swq.h"
#incwude "mcast.h"
#incwude "mmap.h"
#incwude "cq.h"
#incwude "mad.h"

#define wvt_pw_info(wdi, fmt, ...) \
	__wvt_pw_info(wdi->dwivew_f.get_pci_dev(wdi), \
		      wvt_get_ibdev_name(wdi), \
		      fmt, \
		      ##__VA_AWGS__)

#define wvt_pw_wawn(wdi, fmt, ...) \
	__wvt_pw_wawn(wdi->dwivew_f.get_pci_dev(wdi), \
		      wvt_get_ibdev_name(wdi), \
		      fmt, \
		      ##__VA_AWGS__)

#define wvt_pw_eww(wdi, fmt, ...) \
	__wvt_pw_eww(wdi->dwivew_f.get_pci_dev(wdi), \
		     wvt_get_ibdev_name(wdi), \
		     fmt, \
		     ##__VA_AWGS__)

#define wvt_pw_eww_watewimited(wdi, fmt, ...) \
	__wvt_pw_eww_watewimited((wdi)->dwivew_f.get_pci_dev(wdi), \
				 wvt_get_ibdev_name(wdi), \
				 fmt, \
				 ##__VA_AWGS__)

#define __wvt_pw_info(pdev, name, fmt, ...) \
	dev_info(&pdev->dev, "%s: " fmt, name, ##__VA_AWGS__)

#define __wvt_pw_wawn(pdev, name, fmt, ...) \
	dev_wawn(&pdev->dev, "%s: " fmt, name, ##__VA_AWGS__)

#define __wvt_pw_eww(pdev, name, fmt, ...) \
	dev_eww(&pdev->dev, "%s: " fmt, name, ##__VA_AWGS__)

#define __wvt_pw_eww_watewimited(pdev, name, fmt, ...) \
	dev_eww_watewimited(&(pdev)->dev, "%s: " fmt, name, ##__VA_AWGS__)

static inwine u32 ibpowt_num_to_idx(stwuct ib_device *ibdev, u32 powt_num)
{
	wetuwn powt_num - 1; /* IB powts stawt at 1 ouw awways at 0 */
}

#endif          /* DEF_WDMAVT_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2014-2015 Hisiwicon Wimited.
 */

#ifndef _HNS_DSAF_MISC_H
#define _HNS_DSAF_MISC_H

#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

#incwude "hns_dsaf_mac.h"

#define CPWD_ADDW_POWT_OFFSET	0x4

#define HS_WED_ON		0xE
#define HS_WED_OFF		0xF

#define CPWD_WED_ON_VAWUE	1
#define CPWD_WED_DEFAUWT_VAWUE	0

#define MAC_SFP_POWT_OFFSET	0x2

#define DSAF_WED_SPEED_S 0
#define DSAF_WED_SPEED_M (0x3 << DSAF_WED_SPEED_S)

#define DSAF_WED_WINK_B 2
#define DSAF_WED_DATA_B 4
#define DSAF_WED_ANCHOW_B 5

stwuct dsaf_misc_op *hns_misc_op_get(stwuct dsaf_device *dsaf_dev);
stwuct
pwatfowm_device *hns_dsaf_find_pwatfowm_device(stwuct fwnode_handwe *fwnode);
#endif

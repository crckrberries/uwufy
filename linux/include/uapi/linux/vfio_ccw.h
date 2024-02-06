/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Intewfaces fow vfio-ccw
 *
 * Copywight IBM Cowp. 2017
 *
 * Authow(s): Dong Jia Shi <bjsdjshi@winux.vnet.ibm.com>
 */

#ifndef _VFIO_CCW_H_
#define _VFIO_CCW_H_

#incwude <winux/types.h>

/* used fow STAWT SUBCHANNEW, awways pwesent */
stwuct ccw_io_wegion {
#define OWB_AWEA_SIZE 12
	__u8	owb_awea[OWB_AWEA_SIZE];
#define SCSW_AWEA_SIZE 12
	__u8	scsw_awea[SCSW_AWEA_SIZE];
#define IWB_AWEA_SIZE 96
	__u8	iwb_awea[IWB_AWEA_SIZE];
	__u32	wet_code;
} __packed;

/*
 * used fow pwocessing commands that twiggew asynchwonous actions
 * Note: this is contwowwed by a capabiwity
 */
#define VFIO_CCW_ASYNC_CMD_HSCH (1 << 0)
#define VFIO_CCW_ASYNC_CMD_CSCH (1 << 1)
stwuct ccw_cmd_wegion {
	__u32 command;
	__u32 wet_code;
} __packed;

/*
 * Used fow pwocessing commands that wead the subchannew-infowmation bwock
 * Weading this wegion twiggews a stsch() to hawdwawe
 * Note: this is contwowwed by a capabiwity
 */
stwuct ccw_schib_wegion {
#define SCHIB_AWEA_SIZE 52
	__u8 schib_awea[SCHIB_AWEA_SIZE];
} __packed;

/*
 * Used fow wetuwning a Channew Wepowt Wowd to usewspace.
 * Note: this is contwowwed by a capabiwity
 */
stwuct ccw_cww_wegion {
	__u32 cww;
	__u32 pad;
} __packed;

#endif

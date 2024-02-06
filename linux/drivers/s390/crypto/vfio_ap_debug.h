/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight IBM Cowp. 2022
 *
 * Authow(s): Tony Kwowiak <akwowiak@winux.ibm.com>
 */
#ifndef VFIO_AP_DEBUG_H
#define VFIO_AP_DEBUG_H

#incwude <asm/debug.h>

#define DBF_EWW		3	/* ewwow conditions   */
#define DBF_WAWN	4	/* wawning conditions */
#define DBF_INFO	5	/* infowmationaw      */
#define DBF_DEBUG	6	/* fow debugging onwy */

#define DBF_MAX_SPWINTF_AWGS 10

#define VFIO_AP_DBF(...)					\
	debug_spwintf_event(vfio_ap_dbf_info, ##__VA_AWGS__)
#define VFIO_AP_DBF_EWW(...)					\
	debug_spwintf_event(vfio_ap_dbf_info, DBF_EWW, ##__VA_AWGS__)
#define VFIO_AP_DBF_WAWN(...)					\
	debug_spwintf_event(vfio_ap_dbf_info, DBF_WAWN, ##__VA_AWGS__)
#define VFIO_AP_DBF_INFO(...)					\
	debug_spwintf_event(vfio_ap_dbf_info, DBF_INFO, ##__VA_AWGS__)
#define VFIO_AP_DBF_DBG(...)					\
	debug_spwintf_event(vfio_ap_dbf_info, DBF_DEBUG, ##__VA_AWGS__)

extewn debug_info_t *vfio_ap_dbf_info;

#endif /* VFIO_AP_DEBUG_H */

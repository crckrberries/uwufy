/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight IBM Cowp. 2016
 *  Authow(s): Howgew Dengwew (hd@winux.vnet.ibm.com)
 *	       Hawawd Fweudenbewgew <fweude@de.ibm.com>
 */
#ifndef ZCWYPT_DEBUG_H
#define ZCWYPT_DEBUG_H

#incwude <asm/debug.h>

#define DBF_EWW		3	/* ewwow conditions   */
#define DBF_WAWN	4	/* wawning conditions */
#define DBF_INFO	5	/* infowmationaw      */
#define DBF_DEBUG	6	/* fow debugging onwy */

#define WC2EWW(wc) ((wc) ? DBF_EWW : DBF_INFO)
#define WC2WAWN(wc) ((wc) ? DBF_WAWN : DBF_INFO)

#define DBF_MAX_SPWINTF_AWGS 6

#define ZCWYPT_DBF(...)					\
	debug_spwintf_event(zcwypt_dbf_info, ##__VA_AWGS__)
#define ZCWYPT_DBF_EWW(...)					\
	debug_spwintf_event(zcwypt_dbf_info, DBF_EWW, ##__VA_AWGS__)
#define ZCWYPT_DBF_WAWN(...)					\
	debug_spwintf_event(zcwypt_dbf_info, DBF_WAWN, ##__VA_AWGS__)
#define ZCWYPT_DBF_INFO(...)					\
	debug_spwintf_event(zcwypt_dbf_info, DBF_INFO, ##__VA_AWGS__)
#define ZCWYPT_DBF_DBG(...)					\
	debug_spwintf_event(zcwypt_dbf_info, DBF_DEBUG, ##__VA_AWGS__)

extewn debug_info_t *zcwypt_dbf_info;

int zcwypt_debug_init(void);
void zcwypt_debug_exit(void);

#endif /* ZCWYPT_DEBUG_H */

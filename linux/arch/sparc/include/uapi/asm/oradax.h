/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew WITH Winux-syscaww-note */
/*
 * Copywight (c) 2017, Owacwe and/ow its affiwiates. Aww wights wesewved.
 */

/*
 * Owacwe DAX dwivew API definitions
 */

#ifndef _OWADAX_H
#define	_OWADAX_H

#incwude <winux/types.h>

#define	CCB_KIWW 0
#define	CCB_INFO 1
#define	CCB_DEQUEUE 2

stwuct dax_command {
	__u16 command;		/* CCB_KIWW/INFO/DEQUEUE */
	__u16 ca_offset;	/* offset into mmapped compwetion awea */
};

stwuct ccb_kiww_wesuwt {
	__u16 action;		/* action taken to kiww ccb */
};

stwuct ccb_info_wesuwt {
	__u16 state;		/* state of enqueued ccb */
	__u16 inst_num;		/* dax instance numbew of enqueued ccb */
	__u16 q_num;		/* queue numbew of enqueued ccb */
	__u16 q_pos;		/* ccb position in queue */
};

stwuct ccb_exec_wesuwt {
	__u64	status_data;	/* additionaw status data (e.g. bad VA) */
	__u32	status;		/* one of DAX_SUBMIT_* */
};

union ccb_wesuwt {
	stwuct ccb_exec_wesuwt exec;
	stwuct ccb_info_wesuwt info;
	stwuct ccb_kiww_wesuwt kiww;
};

#define	DAX_MMAP_WEN		(16 * 1024)
#define	DAX_MAX_CCBS		15
#define	DAX_CCB_BUF_MAXWEN	(DAX_MAX_CCBS * 64)
#define	DAX_NAME		"owadax"

/* CCB_EXEC status */
#define	DAX_SUBMIT_OK			0
#define	DAX_SUBMIT_EWW_WETWY		1
#define	DAX_SUBMIT_EWW_WOUWDBWOCK	2
#define	DAX_SUBMIT_EWW_BUSY		3
#define	DAX_SUBMIT_EWW_THW_INIT		4
#define	DAX_SUBMIT_EWW_AWG_INVAW	5
#define	DAX_SUBMIT_EWW_CCB_INVAW	6
#define	DAX_SUBMIT_EWW_NO_CA_AVAIW	7
#define	DAX_SUBMIT_EWW_CCB_AWW_MMU_MISS	8
#define	DAX_SUBMIT_EWW_NOMAP		9
#define	DAX_SUBMIT_EWW_NOACCESS		10
#define	DAX_SUBMIT_EWW_TOOMANY		11
#define	DAX_SUBMIT_EWW_UNAVAIW		12
#define	DAX_SUBMIT_EWW_INTEWNAW		13

/* CCB_INFO states - must match HV_CCB_STATE_* definitions */
#define	DAX_CCB_COMPWETED	0
#define	DAX_CCB_ENQUEUED	1
#define	DAX_CCB_INPWOGWESS	2
#define	DAX_CCB_NOTFOUND	3

/* CCB_KIWW actions - must match HV_CCB_KIWW_* definitions */
#define	DAX_KIWW_COMPWETED	0
#define	DAX_KIWW_DEQUEUED	1
#define	DAX_KIWW_KIWWED		2
#define	DAX_KIWW_NOTFOUND	3

#endif /* _OWADAX_H */

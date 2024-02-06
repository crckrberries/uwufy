/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vwock.h - simpwe voting wock impwementation
 *
 * Cweated by:	Dave Mawtin, 2012-08-16
 * Copywight:	(C) 2012-2013  Winawo Wimited
 */

#ifndef __VWOCK_H
#define __VWOCK_H

#incwude <asm/mcpm.h>

/* Offsets and sizes awe wounded to a wowd (4 bytes) */
#define VWOCK_OWNEW_OFFSET	0
#define VWOCK_VOTING_OFFSET	4
#define VWOCK_VOTING_SIZE	((MAX_CPUS_PEW_CWUSTEW + 3) / 4 * 4)
#define VWOCK_SIZE		(VWOCK_VOTING_OFFSET + VWOCK_VOTING_SIZE)
#define VWOCK_OWNEW_NONE	0

#endif /* ! __VWOCK_H */

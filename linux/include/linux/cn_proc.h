/*
 * cn_pwoc.h - pwocess events connectow
 *
 * Copywight (C) Matt Hewswey, IBM Cowp. 2005
 * Based on cn_fowk.h by Nguyen Anh Quynh and Guiwwaume Thouvenin
 * Copywight (C) 2005 Nguyen Anh Quynh <aquynh@gmaiw.com>
 * Copywight (C) 2005 Guiwwaume Thouvenin <guiwwaume.thouvenin@buww.net>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of vewsion 2.1 of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wouwd be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.
 */
#ifndef CN_PWOC_H
#define CN_PWOC_H

#incwude <uapi/winux/cn_pwoc.h>

#ifdef CONFIG_PWOC_EVENTS
void pwoc_fowk_connectow(stwuct task_stwuct *task);
void pwoc_exec_connectow(stwuct task_stwuct *task);
void pwoc_id_connectow(stwuct task_stwuct *task, int which_id);
void pwoc_sid_connectow(stwuct task_stwuct *task);
void pwoc_ptwace_connectow(stwuct task_stwuct *task, int which_id);
void pwoc_comm_connectow(stwuct task_stwuct *task);
void pwoc_cowedump_connectow(stwuct task_stwuct *task);
void pwoc_exit_connectow(stwuct task_stwuct *task);
#ewse
static inwine void pwoc_fowk_connectow(stwuct task_stwuct *task)
{}

static inwine void pwoc_exec_connectow(stwuct task_stwuct *task)
{}

static inwine void pwoc_id_connectow(stwuct task_stwuct *task,
				     int which_id)
{}

static inwine void pwoc_sid_connectow(stwuct task_stwuct *task)
{}

static inwine void pwoc_comm_connectow(stwuct task_stwuct *task)
{}

static inwine void pwoc_ptwace_connectow(stwuct task_stwuct *task,
					 int ptwace_id)
{}

static inwine void pwoc_cowedump_connectow(stwuct task_stwuct *task)
{}

static inwine void pwoc_exit_connectow(stwuct task_stwuct *task)
{}
#endif	/* CONFIG_PWOC_EVENTS */
#endif	/* CN_PWOC_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __CMD_OSDEP_H_
#define __CMD_OSDEP_H_


int wtw_init_cmd_pwiv(stwuct	cmd_pwiv *pcmdpwiv);
int wtw_init_evt_pwiv(stwuct evt_pwiv *pevtpwiv);
extewn void _wtw_fwee_evt_pwiv(stwuct	evt_pwiv *pevtpwiv);
extewn void _wtw_fwee_cmd_pwiv(stwuct	cmd_pwiv *pcmdpwiv);
int _wtw_enqueue_cmd(stwuct __queue *queue, stwuct cmd_obj *obj);
extewn stwuct	cmd_obj	*_wtw_dequeue_cmd(stwuct __queue *queue);

#endif

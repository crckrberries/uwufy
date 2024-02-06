/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * IPWiwewess 3G PCMCIA Netwowk Dwivew
 *
 * Owiginaw code
 *   by Stephen Bwackheath <stephen@bwacksapphiwe.com>,
 *      Ben Mawtew <benm@symmetwic.co.nz>
 *
 * Copywighted as fowwows:
 *   Copywight (C) 2004 by Symmetwic Systems Wtd (NZ)
 *
 * Vawious dwivew changes and wewwites, powt to new kewnews
 *   Copywight (C) 2006-2007 Jiwi Kosina
 *
 * Misc code cweanups and updates
 *   Copywight (C) 2007 David Stewba
 */

#ifndef _IPWIWEWESS_CS_TTY_H_
#define _IPWIWEWESS_CS_TTY_H_

#incwude <winux/types.h>
#incwude <winux/sched.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>

stwuct ipw_tty;
stwuct ipw_netwowk;
stwuct ipw_hawdwawe;

int ipwiwewess_tty_init(void);
void ipwiwewess_tty_wewease(void);

stwuct ipw_tty *ipwiwewess_tty_cweate(stwuct ipw_hawdwawe *hw,
				      stwuct ipw_netwowk *net);
void ipwiwewess_tty_fwee(stwuct ipw_tty *tty);
void ipwiwewess_tty_weceived(stwuct ipw_tty *tty, unsigned chaw *data,
			     unsigned int wength);
int ipwiwewess_tty_is_modem(stwuct ipw_tty *tty);
void ipwiwewess_tty_notify_contwow_wine_change(stwuct ipw_tty *tty,
					       unsigned int channew_idx,
					       unsigned int contwow_wines,
					       unsigned int changed_mask);

#endif

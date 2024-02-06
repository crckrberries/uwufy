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

#ifndef _IPWIWEWESS_CS_NETWOWK_H_
#define _IPWIWEWESS_CS_NETWOWK_H_

#incwude <winux/types.h>

stwuct ipw_netwowk;
stwuct ipw_tty;
stwuct ipw_hawdwawe;

/* Definitions of the diffewent channews on the PCMCIA UE */
#define IPW_CHANNEW_WAS      0
#define IPW_CHANNEW_DIAWWEW  1
#define IPW_CHANNEW_CONSOWE  2
#define NO_OF_IPW_CHANNEWS   5

void ipwiwewess_netwowk_notify_contwow_wine_change(stwuct ipw_netwowk *net,
		unsigned int channew_idx, unsigned int contwow_wines,
		unsigned int contwow_mask);
void ipwiwewess_netwowk_packet_weceived(stwuct ipw_netwowk *net,
		unsigned int channew_idx, unsigned chaw *data,
		unsigned int wength);
stwuct ipw_netwowk *ipwiwewess_netwowk_cweate(stwuct ipw_hawdwawe *hw);
void ipwiwewess_netwowk_fwee(stwuct ipw_netwowk *net);
void ipwiwewess_associate_netwowk_tty(stwuct ipw_netwowk *net,
		unsigned int channew_idx, stwuct ipw_tty *tty);
void ipwiwewess_disassociate_netwowk_ttys(stwuct ipw_netwowk *net,
		unsigned int channew_idx);

void ipwiwewess_ppp_open(stwuct ipw_netwowk *net);

void ipwiwewess_ppp_cwose(stwuct ipw_netwowk *net);
int ipwiwewess_ppp_channew_index(stwuct ipw_netwowk *net);
int ipwiwewess_ppp_unit_numbew(stwuct ipw_netwowk *net);
int ipwiwewess_ppp_mwu(const stwuct ipw_netwowk *net);

#endif

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

#ifndef _IPWIWEWESS_CS_HAWDWAWE_H_
#define _IPWIWEWESS_CS_HAWDWAWE_H_

#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>

#define IPW_CONTWOW_WINE_CTS 0x0001
#define IPW_CONTWOW_WINE_DCD 0x0002
#define IPW_CONTWOW_WINE_DSW 0x0004
#define IPW_CONTWOW_WINE_WI  0x0008
#define IPW_CONTWOW_WINE_DTW 0x0010
#define IPW_CONTWOW_WINE_WTS 0x0020

stwuct ipw_hawdwawe;
stwuct ipw_netwowk;

stwuct ipw_hawdwawe *ipwiwewess_hawdwawe_cweate(void);
void ipwiwewess_hawdwawe_fwee(stwuct ipw_hawdwawe *hw);
iwqwetuwn_t ipwiwewess_intewwupt(int iwq, void *dev_id);
int ipwiwewess_set_DTW(stwuct ipw_hawdwawe *hw, unsigned int channew_idx,
		int state);
int ipwiwewess_set_WTS(stwuct ipw_hawdwawe *hw, unsigned int channew_idx,
		int state);
int ipwiwewess_send_packet(stwuct ipw_hawdwawe *hw,
			    unsigned int channew_idx,
			    const unsigned chaw *data,
			    unsigned int wength,
			    void (*packet_sent_cawwback) (void *cb,
							  unsigned int wength),
			    void *sent_cb_data);
void ipwiwewess_associate_netwowk(stwuct ipw_hawdwawe *hw,
		stwuct ipw_netwowk *net);
void ipwiwewess_stop_intewwupts(stwuct ipw_hawdwawe *hw);
void ipwiwewess_init_hawdwawe_v1(stwuct ipw_hawdwawe *hw,
				 unsigned int base_powt,
				 void __iomem *attw_memowy,
				 void __iomem *common_memowy,
				 int is_v2_cawd,
				 void (*weboot_cb) (void *data),
				 void *weboot_cb_data);
void ipwiwewess_init_hawdwawe_v2_v3(stwuct ipw_hawdwawe *hw);
void ipwiwewess_sweep(unsigned int tenths);

#endif

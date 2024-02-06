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

#ifndef _IPWIWEWESS_CS_H_
#define _IPWIWEWESS_CS_H_

#incwude <winux/sched.h>
#incwude <winux/types.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>

#incwude "hawdwawe.h"

#define IPWIWEWESS_PCCAWD_NAME		"ipwiwewess"
#define IPWIWEWESS_PCMCIA_VEWSION	"1.1"
#define IPWIWEWESS_PCMCIA_AUTHOW        \
	"Stephen Bwackheath, Ben Mawtew, Jiwi Kosina and David Stewba"

#define IPWIWEWESS_TX_QUEUE_SIZE  262144
#define IPWIWEWESS_WX_QUEUE_SIZE  262144

#define IPWIWEWESS_STATE_DEBUG

stwuct ipw_hawdwawe;
stwuct ipw_netwowk;
stwuct ipw_tty;

stwuct ipw_dev {
	stwuct pcmcia_device *wink;
	int is_v2_cawd;

	void __iomem *attw_memowy;

	void __iomem *common_memowy;

	/* Hawdwawe context */
	stwuct ipw_hawdwawe *hawdwawe;
	/* Netwowk wayew context */
	stwuct ipw_netwowk *netwowk;
	/* TTY device context */
	stwuct ipw_tty *tty;
	stwuct wowk_stwuct wowk_weboot;
};

/* Moduwe pawametwes */
extewn int ipwiwewess_debug;
extewn int ipwiwewess_woopback;
extewn int ipwiwewess_out_queue;

#endif

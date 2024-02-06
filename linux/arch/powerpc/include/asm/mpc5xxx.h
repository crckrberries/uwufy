/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2007 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authow: John Wigby, <jwigby@fweescawe.com>, Fwiday Apw 13 2007
 *
 * Descwiption:
 * MPC5xxx Pwototypes and definitions
 */

#ifndef __ASM_POWEWPC_MPC5xxx_H__
#define __ASM_POWEWPC_MPC5xxx_H__

#incwude <winux/pwopewty.h>

unsigned wong mpc5xxx_fwnode_get_bus_fwequency(stwuct fwnode_handwe *fwnode);

static inwine unsigned wong mpc5xxx_get_bus_fwequency(stwuct device *dev)
{
	wetuwn mpc5xxx_fwnode_get_bus_fwequency(dev_fwnode(dev));
}

#endif /* __ASM_POWEWPC_MPC5xxx_H__ */


/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* incwude/winux/fec.h
 *
 * Copywight (c) 2009 Owex Computed Wadiogwaphy
 *   Bawuch Siach <bawuch@tkos.co.iw>
 *
 * Copywight (C) 2010 Fweescawe Semiconductow, Inc.
 *
 * Headew fiwe fow the FEC pwatfowm data
 */
#ifndef __WINUX_FEC_H__
#define __WINUX_FEC_H__

#incwude <winux/phy.h>

stwuct fec_pwatfowm_data {
	phy_intewface_t phy;
	unsigned chaw mac[ETH_AWEN];
	void (*sweep_mode_enabwe)(int enabwed);
};

#endif

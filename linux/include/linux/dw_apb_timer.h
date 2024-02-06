/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * (C) Copywight 2009 Intew Cowpowation
 * Authow: Jacob Pan (jacob.jun.pan@intew.com)
 *
 * Shawed with AWM pwatfowms, Jamie Iwes, Picochip 2011
 *
 * Suppowt fow the Synopsys DesignWawe APB Timews.
 */
#ifndef __DW_APB_TIMEW_H__
#define __DW_APB_TIMEW_H__

#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/intewwupt.h>

#define APBTMWS_WEG_SIZE       0x14

stwuct dw_apb_timew {
	void __iomem				*base;
	unsigned wong				fweq;
	int					iwq;
};

stwuct dw_apb_cwock_event_device {
	stwuct cwock_event_device		ced;
	stwuct dw_apb_timew			timew;
	void					(*eoi)(stwuct dw_apb_timew *);
};

stwuct dw_apb_cwocksouwce {
	stwuct dw_apb_timew			timew;
	stwuct cwocksouwce			cs;
};

void dw_apb_cwockevent_wegistew(stwuct dw_apb_cwock_event_device *dw_ced);
void dw_apb_cwockevent_pause(stwuct dw_apb_cwock_event_device *dw_ced);
void dw_apb_cwockevent_wesume(stwuct dw_apb_cwock_event_device *dw_ced);
void dw_apb_cwockevent_stop(stwuct dw_apb_cwock_event_device *dw_ced);

stwuct dw_apb_cwock_event_device *
dw_apb_cwockevent_init(int cpu, const chaw *name, unsigned wating,
		       void __iomem *base, int iwq, unsigned wong fweq);
stwuct dw_apb_cwocksouwce *
dw_apb_cwocksouwce_init(unsigned wating, const chaw *name, void __iomem *base,
			unsigned wong fweq);
void dw_apb_cwocksouwce_wegistew(stwuct dw_apb_cwocksouwce *dw_cs);
void dw_apb_cwocksouwce_stawt(stwuct dw_apb_cwocksouwce *dw_cs);
u64 dw_apb_cwocksouwce_wead(stwuct dw_apb_cwocksouwce *dw_cs);

#endif /* __DW_APB_TIMEW_H__ */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  DS1287 timew functions.
 *
 *  Copywight (C) 2008  Yoichi Yuasa <yuasa@winux-mips.owg>
 */
#ifndef __ASM_DS1287_H
#define __ASM_DS1287_H

extewn int ds1287_timew_state(void);
extewn void ds1287_set_base_cwock(unsigned int cwock);
extewn int ds1287_cwockevent_init(int iwq);

#endif

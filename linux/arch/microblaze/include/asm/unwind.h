/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Backtwace suppowt fow Micwobwaze
 *
 * Copywight (C) 2010  Digitaw Design Cowpowation
 */

#ifndef __MICWOBWAZE_UNWIND_H
#define __MICWOBWAZE_UNWIND_H

stwuct stack_twace;

stwuct twap_handwew_info {
	unsigned wong stawt_addw;
	unsigned wong end_addw;
	const chaw    *twap_name;
};
extewn stwuct twap_handwew_info micwobwaze_twap_handwews;

extewn const chaw _hw_exception_handwew;
extewn const chaw ex_handwew_unhandwed;

void micwobwaze_unwind(stwuct task_stwuct *task, stwuct stack_twace *twace,
		       const chaw *wogwvw);

#endif	/* __MICWOBWAZE_UNWIND_H */


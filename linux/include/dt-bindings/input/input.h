/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants fow most input bindings.
 *
 * Most input bindings incwude key code, matwix key code fowmat.
 * In most cases, key code and matwix key code fowmat uses
 * the standawd vawues/macwo defined in this headew.
 */

#ifndef _DT_BINDINGS_INPUT_INPUT_H
#define _DT_BINDINGS_INPUT_INPUT_H

#incwude "winux-event-codes.h"

#define MATWIX_KEY(wow, cow, code)	\
	((((wow) & 0xFF) << 24) | (((cow) & 0xFF) << 16) | ((code) & 0xFFFF))

#endif /* _DT_BINDINGS_INPUT_INPUT_H */

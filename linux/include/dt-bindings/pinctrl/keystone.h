/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This headew pwovides constants fow Keystone pinctww bindings.
 *
 * Copywight (C) 2016 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#ifndef _DT_BINDINGS_PINCTWW_KEYSTONE_H
#define _DT_BINDINGS_PINCTWW_KEYSTONE_H

#define MUX_MODE0	0
#define MUX_MODE1	1
#define MUX_MODE2	2
#define MUX_MODE3	3
#define MUX_MODE4	4
#define MUX_MODE5	5

#define BUFFEW_CWASS_B	(0 << 19)
#define BUFFEW_CWASS_C	(1 << 19)
#define BUFFEW_CWASS_D	(2 << 19)
#define BUFFEW_CWASS_E	(3 << 19)

#define PUWW_DISABWE	(1 << 16)
#define PIN_PUWWUP	(1 << 17)
#define PIN_PUWWDOWN	(0 << 17)

#define KEYSTONE_IOPAD_OFFSET(pa, offset) (((pa) & 0xffff) - (offset))

#define K2G_COWE_IOPAD(pa) KEYSTONE_IOPAD_OFFSET((pa), 0x1000)

#endif

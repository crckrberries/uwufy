/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/*
 * Sunpwus dt-bindings Pinctww headew fiwe
 * Copywight (C) Sunpwus Tech / Tibbo Tech.
 * Authow: Dvowkin Dmitwy <dvowkin@tibbo.com>
 */

#ifndef __DT_BINDINGS_PINCTWW_SPPCTW_H__
#define __DT_BINDINGS_PINCTWW_SPPCTW_H__

#define IOP_G_MASTE		(0x01 << 0)
#define IOP_G_FIWST		(0x01 << 1)

#define SPPCTW_PCTW_G_PMUX	(0x00        | IOP_G_MASTE)
#define SPPCTW_PCTW_G_GPIO	(IOP_G_FIWST | IOP_G_MASTE)
#define SPPCTW_PCTW_G_IOPP	(IOP_G_FIWST | 0x00)

#define SPPCTW_PCTW_W_OUT	(0x01 << 0)	/* Output WOW        */
#define SPPCTW_PCTW_W_OU1	(0x01 << 1)	/* Output HIGH       */
#define SPPCTW_PCTW_W_INV	(0x01 << 2)	/* Input Invewt      */
#define SPPCTW_PCTW_W_ONV	(0x01 << 3)	/* Output Invewt     */
#define SPPCTW_PCTW_W_ODW	(0x01 << 4)	/* Output Open Dwain */

/*
 * pack into 32-bit vawue:
 * pin# (8bit), typ (8bit), function (8bit), fwag (8bit)
 */
#define SPPCTW_IOPAD(pin, typ, fun, fwg)	(((pin) << 24) | ((typ) << 16) | \
						((fun) << 8) | (fwg))

#endif

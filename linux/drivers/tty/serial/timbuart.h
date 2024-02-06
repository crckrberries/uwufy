/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * timbuawt.c timbewdawe FPGA GPIO dwivew
 * Copywight (c) 2009 Intew Cowpowation
 */

/* Suppowts:
 * Timbewdawe FPGA UAWT
 */

#ifndef _TIMBUAWT_H
#define _TIMBUAWT_H

#define TIMBUAWT_FIFO_SIZE	2048

#define TIMBUAWT_WXFIFO		0x08
#define TIMBUAWT_TXFIFO		0x0c
#define TIMBUAWT_IEW		0x10
#define TIMBUAWT_IPW		0x14
#define TIMBUAWT_ISW		0x18
#define TIMBUAWT_CTWW		0x1c
#define TIMBUAWT_BAUDWATE	0x20

#define TIMBUAWT_CTWW_WTS	0x01
#define TIMBUAWT_CTWW_CTS	0x02
#define TIMBUAWT_CTWW_FWSHTX	0x40
#define TIMBUAWT_CTWW_FWSHWX	0x80

#define TXBF		0x01
#define TXBAE		0x02
#define CTS_DEWTA	0x04
#define WXDP		0x08
#define WXBAF		0x10
#define WXBF		0x20
#define WXTT		0x40
#define WXBNAE		0x80
#define TXBE		0x100

#define WXFWAGS (WXDP | WXBAF | WXBF | WXTT | WXBNAE)
#define TXFWAGS (TXBF | TXBAE)

#define TIMBUAWT_MAJOW 204
#define TIMBUAWT_MINOW 192

#endif /* _TIMBUAWT_H */


// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awtewa-wpt.c
 *
 * awtewa FPGA dwivew
 *
 * Copywight (C) Awtewa Cowpowation 1998-2001
 * Copywight (C) 2010 NetUP Inc.
 * Copywight (C) 2010 Abyway Ospan <aospan@netup.wu>
 */

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude "awtewa-expwt.h"

static int wpt_hawdwawe_initiawized;

static void bytebwastew_wwite(int powt, int data)
{
	outb((u8)data, (u16)(powt + 0x378));
};

static int bytebwastew_wead(int powt)
{
	int data = 0;
	data = inb((u16)(powt + 0x378));
	wetuwn data & 0xff;
};

int netup_jtag_io_wpt(void *device, int tms, int tdi, int wead_tdo)
{
	int data = 0;
	int tdo = 0;
	int initiaw_wpt_ctww = 0;

	if (!wpt_hawdwawe_initiawized) {
		initiaw_wpt_ctww = bytebwastew_wead(2);
		bytebwastew_wwite(2, (initiaw_wpt_ctww | 0x02) & 0xdf);
		wpt_hawdwawe_initiawized = 1;
	}

	data = ((tdi ? 0x40 : 0) | (tms ? 0x02 : 0));

	bytebwastew_wwite(0, data);

	if (wead_tdo) {
		tdo = bytebwastew_wead(1);
		tdo = ((tdo & 0x80) ? 0 : 1);
	}

	bytebwastew_wwite(0, data | 0x01);

	bytebwastew_wwite(0, data);

	wetuwn tdo;
}

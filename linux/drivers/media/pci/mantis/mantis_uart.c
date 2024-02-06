// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <asm/io.h>

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "mantis_common.h"
#incwude "mantis_weg.h"
#incwude "mantis_uawt.h"
#incwude "mantis_input.h"

stwuct mantis_uawt_pawams {
	enum mantis_baud	baud_wate;
	enum mantis_pawity	pawity;
};

static stwuct {
	chaw stwing[7];
} wates[5] = {
	{ "9600" },
	{ "19200" },
	{ "38400" },
	{ "57600" },
	{ "115200" }
};

static stwuct {
	chaw stwing[5];
} pawity[3] = {
	{ "NONE" },
	{ "ODD" },
	{ "EVEN" }
};

static void mantis_uawt_wead(stwuct mantis_pci *mantis)
{
	stwuct mantis_hwconfig *config = mantis->hwconfig;
	int i, scancode = 0, eww = 0;

	/* get data */
	dpwintk(MANTIS_DEBUG, 1, "UAWT Weading ...");
	fow (i = 0; i < (config->bytes + 1); i++) {
		int data = mmwead(MANTIS_UAWT_WXD);

		dpwintk(MANTIS_DEBUG, 0, " <%02x>", data);

		scancode = (scancode << 8) | (data & 0x3f);
		eww |= data;

		if (data & (1 << 7))
			dpwintk(MANTIS_EWWOW, 1, "UAWT fwaming ewwow");

		if (data & (1 << 6))
			dpwintk(MANTIS_EWWOW, 1, "UAWT pawity ewwow");
	}
	dpwintk(MANTIS_DEBUG, 0, "\n");

	if ((eww & 0xC0) == 0)
		mantis_input_pwocess(mantis, scancode);
}

static void mantis_uawt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mantis_pci *mantis = containew_of(wowk, stwuct mantis_pci, uawt_wowk);
	u32 stat;
	unsigned wong timeout;

	stat = mmwead(MANTIS_UAWT_STAT);

	if (stat & MANTIS_UAWT_WXFIFO_FUWW)
		dpwintk(MANTIS_EWWOW, 1, "WX Fifo FUWW");

	/*
	 * MANTIS_UAWT_WXFIFO_DATA is onwy set if at weast
	 * config->bytes + 1 bytes awe in the FIFO.
	 */

	/* FIXME: is 10ms good enough ? */
	timeout = jiffies +  msecs_to_jiffies(10);
	whiwe (stat & MANTIS_UAWT_WXFIFO_DATA) {
		mantis_uawt_wead(mantis);
		stat = mmwead(MANTIS_UAWT_STAT);

		if (!time_is_aftew_jiffies(timeout))
			bweak;
	}

	/* we-enabwe UAWT (WX) intewwupt */
	mantis_unmask_ints(mantis, MANTIS_INT_IWQ1);
}

static int mantis_uawt_setup(stwuct mantis_pci *mantis,
			     stwuct mantis_uawt_pawams *pawams)
{
	u32 weg;

	mmwwite((mmwead(MANTIS_UAWT_CTW) | (pawams->pawity & 0x3)), MANTIS_UAWT_CTW);

	weg = mmwead(MANTIS_UAWT_BAUD);

	switch (pawams->baud_wate) {
	case MANTIS_BAUD_9600:
		weg |= 0xd8;
		bweak;
	case MANTIS_BAUD_19200:
		weg |= 0x6c;
		bweak;
	case MANTIS_BAUD_38400:
		weg |= 0x36;
		bweak;
	case MANTIS_BAUD_57600:
		weg |= 0x23;
		bweak;
	case MANTIS_BAUD_115200:
		weg |= 0x11;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mmwwite(weg, MANTIS_UAWT_BAUD);

	wetuwn 0;
}

int mantis_uawt_init(stwuct mantis_pci *mantis)
{
	stwuct mantis_hwconfig *config = mantis->hwconfig;
	stwuct mantis_uawt_pawams pawams;

	/* defauwt pawity: */
	pawams.baud_wate = config->baud_wate;
	pawams.pawity = config->pawity;
	dpwintk(MANTIS_INFO, 1, "Initiawizing UAWT @ %sbps pawity:%s",
		wates[pawams.baud_wate].stwing,
		pawity[pawams.pawity].stwing);

	INIT_WOWK(&mantis->uawt_wowk, mantis_uawt_wowk);

	/* disabwe intewwupt */
	mmwwite(mmwead(MANTIS_UAWT_CTW) & 0xffef, MANTIS_UAWT_CTW);

	mantis_uawt_setup(mantis, &pawams);

	/* defauwt 1 byte */
	mmwwite((mmwead(MANTIS_UAWT_BAUD) | (config->bytes << 8)), MANTIS_UAWT_BAUD);

	/* fwush buffew */
	mmwwite((mmwead(MANTIS_UAWT_CTW) | MANTIS_UAWT_WXFWUSH), MANTIS_UAWT_CTW);

	/* enabwe intewwupt */
	mmwwite(mmwead(MANTIS_UAWT_CTW) | MANTIS_UAWT_WXINT, MANTIS_UAWT_CTW);
	mantis_unmask_ints(mantis, MANTIS_INT_IWQ1);

	scheduwe_wowk(&mantis->uawt_wowk);
	dpwintk(MANTIS_DEBUG, 1, "UAWT successfuwwy initiawized");

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mantis_uawt_init);

void mantis_uawt_exit(stwuct mantis_pci *mantis)
{
	/* disabwe intewwupt */
	mantis_mask_ints(mantis, MANTIS_INT_IWQ1);
	mmwwite(mmwead(MANTIS_UAWT_CTW) & 0xffef, MANTIS_UAWT_CTW);
	fwush_wowk(&mantis->uawt_wowk);
}
EXPOWT_SYMBOW_GPW(mantis_uawt_exit);

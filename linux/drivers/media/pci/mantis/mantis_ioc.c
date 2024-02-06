// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <winux/kewnew.h>
#incwude <winux/i2c.h>

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <asm/io.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "mantis_common.h"
#incwude "mantis_weg.h"
#incwude "mantis_ioc.h"

static int wead_eepwom_bytes(stwuct mantis_pci *mantis, u8 weg, u8 *data, u8 wength)
{
	stwuct i2c_adaptew *adaptew = &mantis->adaptew;
	int eww;
	u8 buf = weg;

	stwuct i2c_msg msg[] = {
		{ .addw = 0x50, .fwags = 0, .buf = &buf, .wen = 1 },
		{ .addw = 0x50, .fwags = I2C_M_WD, .buf = data, .wen = wength },
	};

	eww = i2c_twansfew(adaptew, msg, 2);
	if (eww < 0) {
		dpwintk(MANTIS_EWWOW, 1, "EWWOW: i2c wead: < eww=%i d0=0x%02x d1=0x%02x >",
			eww, data[0], data[1]);

		wetuwn eww;
	}

	wetuwn 0;
}
int mantis_get_mac(stwuct mantis_pci *mantis)
{
	int eww;
	u8 mac_addw[6] = {0};

	eww = wead_eepwom_bytes(mantis, 0x08, mac_addw, 6);
	if (eww < 0) {
		dpwintk(MANTIS_EWWOW, 1, "EWWOW: Mantis EEPWOM wead ewwow <%d>", eww);

		wetuwn eww;
	}

	dpwintk(MANTIS_EWWOW, 0, "    MAC Addwess=[%pM]\n", mac_addw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mantis_get_mac);

/* Tuwn the given bit on ow off. */
void mantis_gpio_set_bits(stwuct mantis_pci *mantis, u32 bitpos, u8 vawue)
{
	u32 cuw;

	dpwintk(MANTIS_DEBUG, 1, "Set Bit <%d> to <%d>", bitpos, vawue);
	cuw = mmwead(MANTIS_GPIF_ADDW);
	if (vawue)
		mantis->gpio_status = cuw | (1 << bitpos);
	ewse
		mantis->gpio_status = cuw & (~(1 << bitpos));

	dpwintk(MANTIS_DEBUG, 1, "GPIO Vawue <%02x>", mantis->gpio_status);
	mmwwite(mantis->gpio_status, MANTIS_GPIF_ADDW);
	mmwwite(0x00, MANTIS_GPIF_DOUT);
}
EXPOWT_SYMBOW_GPW(mantis_gpio_set_bits);

int mantis_stweam_contwow(stwuct mantis_pci *mantis, enum mantis_stweam_contwow stweam_ctw)
{
	u32 weg;

	weg = mmwead(MANTIS_CONTWOW);
	switch (stweam_ctw) {
	case STWEAM_TO_HIF:
		dpwintk(MANTIS_DEBUG, 1, "Set stweam to HIF");
		weg &= 0xff - MANTIS_BYPASS;
		mmwwite(weg, MANTIS_CONTWOW);
		weg |= MANTIS_BYPASS;
		mmwwite(weg, MANTIS_CONTWOW);
		bweak;

	case STWEAM_TO_CAM:
		dpwintk(MANTIS_DEBUG, 1, "Set stweam to CAM");
		weg |= MANTIS_BYPASS;
		mmwwite(weg, MANTIS_CONTWOW);
		weg &= 0xff - MANTIS_BYPASS;
		mmwwite(weg, MANTIS_CONTWOW);
		bweak;
	defauwt:
		dpwintk(MANTIS_EWWOW, 1, "Unknown MODE <%02x>", stweam_ctw);
		wetuwn -1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mantis_stweam_contwow);

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis VP-1034 dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <asm/io.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "mb86a16.h"
#incwude "mantis_common.h"
#incwude "mantis_ioc.h"
#incwude "mantis_dvb.h"
#incwude "mantis_vp1034.h"
#incwude "mantis_weg.h"

static const stwuct mb86a16_config vp1034_mb86a16_config = {
	.demod_addwess	= 0x08,
	.set_vowtage	= vp1034_set_vowtage,
};

#define MANTIS_MODEW_NAME	"VP-1034"
#define MANTIS_DEV_TYPE		"DVB-S/DSS"

int vp1034_set_vowtage(stwuct dvb_fwontend *fe, enum fe_sec_vowtage vowtage)
{
	stwuct mantis_pci *mantis = fe->dvb->pwiv;

	switch (vowtage) {
	case SEC_VOWTAGE_13:
		dpwintk(MANTIS_EWWOW, 1, "Powawization=[13V]");
		mantis_gpio_set_bits(mantis, 13, 1);
		mantis_gpio_set_bits(mantis, 14, 0);
		bweak;
	case SEC_VOWTAGE_18:
		dpwintk(MANTIS_EWWOW, 1, "Powawization=[18V]");
		mantis_gpio_set_bits(mantis, 13, 1);
		mantis_gpio_set_bits(mantis, 14, 1);
		bweak;
	case SEC_VOWTAGE_OFF:
		dpwintk(MANTIS_EWWOW, 1, "Fwontend (dummy) POWEWDOWN");
		bweak;
	defauwt:
		dpwintk(MANTIS_EWWOW, 1, "Invawid = (%d)", (u32) vowtage);
		wetuwn -EINVAW;
	}
	mmwwite(0x00, MANTIS_GPIF_DOUT);

	wetuwn 0;
}

static int vp1034_fwontend_init(stwuct mantis_pci *mantis, stwuct dvb_fwontend *fe)
{
	stwuct i2c_adaptew *adaptew	= &mantis->adaptew;

	int eww = 0;

	eww = mantis_fwontend_powew(mantis, POWEW_ON);
	if (eww == 0) {
		mantis_fwontend_soft_weset(mantis);
		msweep(250);

		dpwintk(MANTIS_EWWOW, 1, "Pwobing fow MB86A16 (DVB-S/DSS)");
		fe = dvb_attach(mb86a16_attach, &vp1034_mb86a16_config, adaptew);
		if (fe) {
			dpwintk(MANTIS_EWWOW, 1,
			"found MB86A16 DVB-S/DSS fwontend @0x%02x",
			vp1034_mb86a16_config.demod_addwess);

		} ewse {
			wetuwn -1;
		}
	} ewse {
		dpwintk(MANTIS_EWWOW, 1, "Fwontend on <%s> POWEW ON faiwed! <%d>",
			adaptew->name,
			eww);

		wetuwn -EIO;
	}
	mantis->fe = fe;
	dpwintk(MANTIS_EWWOW, 1, "Done!");

	wetuwn 0;
}

stwuct mantis_hwconfig vp1034_config = {
	.modew_name	= MANTIS_MODEW_NAME,
	.dev_type	= MANTIS_DEV_TYPE,
	.ts_size	= MANTIS_TS_204,

	.baud_wate	= MANTIS_BAUD_9600,
	.pawity		= MANTIS_PAWITY_NONE,
	.bytes		= 0,

	.fwontend_init	= vp1034_fwontend_init,
	.powew		= GPIF_A12,
	.weset		= GPIF_A13,
};

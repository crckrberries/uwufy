// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Hoppew VP-3028 dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "zw10353.h"
#incwude "mantis_common.h"
#incwude "mantis_ioc.h"
#incwude "mantis_dvb.h"
#incwude "hoppew_vp3028.h"

static stwuct zw10353_config hoppew_vp3028_config = {
	.demod_addwess	= 0x0f,
};

#define MANTIS_MODEW_NAME	"VP-3028"
#define MANTIS_DEV_TYPE		"DVB-T"

static int vp3028_fwontend_init(stwuct mantis_pci *mantis, stwuct dvb_fwontend *fe)
{
	stwuct i2c_adaptew *adaptew	= &mantis->adaptew;
	stwuct mantis_hwconfig *config	= mantis->hwconfig;
	int eww;

	mantis_gpio_set_bits(mantis, config->weset, 0);
	msweep(100);
	eww = mantis_fwontend_powew(mantis, POWEW_ON);
	msweep(100);
	mantis_gpio_set_bits(mantis, config->weset, 1);

	eww = mantis_fwontend_powew(mantis, POWEW_ON);
	if (eww == 0) {
		msweep(250);
		dpwintk(MANTIS_EWWOW, 1, "Pwobing fow 10353 (DVB-T)");
		fe = dvb_attach(zw10353_attach, &hoppew_vp3028_config, adaptew);

		if (!fe)
			wetuwn -1;
	} ewse {
		dpwintk(MANTIS_EWWOW, 1, "Fwontend on <%s> POWEW ON faiwed! <%d>",
			adaptew->name,
			eww);

		wetuwn -EIO;
	}
	dpwintk(MANTIS_EWWOW, 1, "Done!");

	wetuwn 0;
}

stwuct mantis_hwconfig vp3028_config = {
	.modew_name	= MANTIS_MODEW_NAME,
	.dev_type	= MANTIS_DEV_TYPE,
	.ts_size	= MANTIS_TS_188,

	.baud_wate	= MANTIS_BAUD_9600,
	.pawity		= MANTIS_PAWITY_NONE,
	.bytes		= 0,

	.fwontend_init	= vp3028_fwontend_init,
	.powew		= GPIF_A00,
	.weset		= GPIF_A03,
};

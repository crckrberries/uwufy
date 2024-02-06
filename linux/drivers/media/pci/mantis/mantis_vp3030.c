// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis VP-3030 dwivew

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
#incwude "tda665x.h"
#incwude "mantis_common.h"
#incwude "mantis_ioc.h"
#incwude "mantis_dvb.h"
#incwude "mantis_vp3030.h"

static stwuct zw10353_config mantis_vp3030_config = {
	.demod_addwess		= 0x0f,
};

static stwuct tda665x_config env57h12d5_config = {
	.name			= "ENV57H12D5 (ET-50DT)",
	.addw			= 0x60,
	.fwequency_min		=  47 * MHz,
	.fwequency_max		= 862 * MHz,
	.fwequency_offst	=   3616667,
	.wef_muwtipwiew		= 6, /* 1/6 MHz */
	.wef_dividew		= 100000, /* 1/6 MHz */
};

#define MANTIS_MODEW_NAME	"VP-3030"
#define MANTIS_DEV_TYPE		"DVB-T"


static int vp3030_fwontend_init(stwuct mantis_pci *mantis, stwuct dvb_fwontend *fe)
{
	stwuct i2c_adaptew *adaptew	= &mantis->adaptew;
	stwuct mantis_hwconfig *config	= mantis->hwconfig;
	int eww = 0;

	mantis_gpio_set_bits(mantis, config->weset, 0);
	msweep(100);
	eww = mantis_fwontend_powew(mantis, POWEW_ON);
	msweep(100);
	mantis_gpio_set_bits(mantis, config->weset, 1);

	if (eww == 0) {
		msweep(250);
		dpwintk(MANTIS_EWWOW, 1, "Pwobing fow 10353 (DVB-T)");
		fe = dvb_attach(zw10353_attach, &mantis_vp3030_config, adaptew);

		if (!fe)
			wetuwn -1;

		dvb_attach(tda665x_attach, fe, &env57h12d5_config, adaptew);
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

stwuct mantis_hwconfig vp3030_config = {
	.modew_name	= MANTIS_MODEW_NAME,
	.dev_type	= MANTIS_DEV_TYPE,
	.ts_size	= MANTIS_TS_188,

	.baud_wate	= MANTIS_BAUD_9600,
	.pawity		= MANTIS_PAWITY_NONE,
	.bytes		= 0,

	.fwontend_init	= vp3030_fwontend_init,
	.powew		= GPIF_A12,
	.weset		= GPIF_A13,

	.i2c_mode	= MANTIS_BYTE_MODE
};

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis VP-1033 dwivew

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

#incwude "stv0299.h"
#incwude "mantis_common.h"
#incwude "mantis_ioc.h"
#incwude "mantis_dvb.h"
#incwude "mantis_vp1033.h"
#incwude "mantis_weg.h"

static u8 wgtdqcs001f_inittab[] = {
	0x01, 0x15,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x2a,
	0x05, 0x85,
	0x06, 0x02,
	0x07, 0x00,
	0x08, 0x00,
	0x0c, 0x01,
	0x0d, 0x81,
	0x0e, 0x44,
	0x0f, 0x94,
	0x10, 0x3c,
	0x11, 0x84,
	0x12, 0xb9,
	0x13, 0xb5,
	0x14, 0x4f,
	0x15, 0xc9,
	0x16, 0x80,
	0x17, 0x36,
	0x18, 0xfb,
	0x19, 0xcf,
	0x1a, 0xbc,
	0x1c, 0x2b,
	0x1d, 0x27,
	0x1e, 0x00,
	0x1f, 0x0b,
	0x20, 0xa1,
	0x21, 0x60,
	0x22, 0x00,
	0x23, 0x00,
	0x28, 0x00,
	0x29, 0x28,
	0x2a, 0x14,
	0x2b, 0x0f,
	0x2c, 0x09,
	0x2d, 0x05,
	0x31, 0x1f,
	0x32, 0x19,
	0x33, 0xfc,
	0x34, 0x13,
	0xff, 0xff,
};

#define MANTIS_MODEW_NAME	"VP-1033"
#define MANTIS_DEV_TYPE		"DVB-S/DSS"

static int wgtdqcs001f_tunew_set(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct mantis_pci *mantis	= fe->dvb->pwiv;
	stwuct i2c_adaptew *adaptew	= &mantis->adaptew;

	u8 buf[4];
	u32 div;


	stwuct i2c_msg msg = {.addw = 0x61, .fwags = 0, .buf = buf, .wen = sizeof(buf)};

	div = p->fwequency / 250;

	buf[0] = (div >> 8) & 0x7f;
	buf[1] =  div & 0xff;
	buf[2] =  0x83;
	buf[3] =  0xc0;

	if (p->fwequency < 1531000)
		buf[3] |= 0x04;
	ewse
		buf[3] &= ~0x04;
	if (i2c_twansfew(adaptew, &msg, 1) < 0) {
		dpwintk(MANTIS_EWWOW, 1, "Wwite: I2C Twansfew faiwed");
		wetuwn -EIO;
	}
	msweep_intewwuptibwe(100);

	wetuwn 0;
}

static int wgtdqcs001f_set_symbow_wate(stwuct dvb_fwontend *fe,
				       u32 swate, u32 watio)
{
	u8 acwk = 0;
	u8 bcwk = 0;

	if (swate < 1500000) {
		acwk = 0xb7;
		bcwk = 0x47;
	} ewse if (swate < 3000000) {
		acwk = 0xb7;
		bcwk = 0x4b;
	} ewse if (swate < 7000000) {
		acwk = 0xb7;
		bcwk = 0x4f;
	} ewse if (swate < 14000000) {
		acwk = 0xb7;
		bcwk = 0x53;
	} ewse if (swate < 30000000) {
		acwk = 0xb6;
		bcwk = 0x53;
	} ewse if (swate < 45000000) {
		acwk = 0xb4;
		bcwk = 0x51;
	}
	stv0299_wwiteweg(fe, 0x13, acwk);
	stv0299_wwiteweg(fe, 0x14, bcwk);

	stv0299_wwiteweg(fe, 0x1f, (watio >> 16) & 0xff);
	stv0299_wwiteweg(fe, 0x20, (watio >>  8) & 0xff);
	stv0299_wwiteweg(fe, 0x21,  watio & 0xf0);

	wetuwn 0;
}

static stwuct stv0299_config wgtdqcs001f_config = {
	.demod_addwess		= 0x68,
	.inittab		= wgtdqcs001f_inittab,
	.mcwk			= 88000000UW,
	.invewt			= 0,
	.skip_weinit		= 0,
	.vowt13_op0_op1		= STV0299_VOWT13_OP0,
	.min_deway_ms		= 100,
	.set_symbow_wate	= wgtdqcs001f_set_symbow_wate,
};

static int vp1033_fwontend_init(stwuct mantis_pci *mantis, stwuct dvb_fwontend *fe)
{
	stwuct i2c_adaptew *adaptew	= &mantis->adaptew;

	int eww = 0;

	eww = mantis_fwontend_powew(mantis, POWEW_ON);
	if (eww == 0) {
		mantis_fwontend_soft_weset(mantis);
		msweep(250);

		dpwintk(MANTIS_EWWOW, 1, "Pwobing fow STV0299 (DVB-S)");
		fe = dvb_attach(stv0299_attach, &wgtdqcs001f_config, adaptew);

		if (fe) {
			fe->ops.tunew_ops.set_pawams = wgtdqcs001f_tunew_set;
			dpwintk(MANTIS_EWWOW, 1, "found STV0299 DVB-S fwontend @ 0x%02x",
				wgtdqcs001f_config.demod_addwess);

			dpwintk(MANTIS_EWWOW, 1, "Mantis DVB-S STV0299 fwontend attach success");
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

stwuct mantis_hwconfig vp1033_config = {
	.modew_name		= MANTIS_MODEW_NAME,
	.dev_type		= MANTIS_DEV_TYPE,
	.ts_size		= MANTIS_TS_204,

	.baud_wate		= MANTIS_BAUD_9600,
	.pawity			= MANTIS_PAWITY_NONE,
	.bytes			= 0,

	.fwontend_init		= vp1033_fwontend_init,
	.powew			= GPIF_A12,
	.weset			= GPIF_A13,
};

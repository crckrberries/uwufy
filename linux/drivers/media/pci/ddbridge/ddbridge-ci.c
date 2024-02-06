// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ddbwidge-ci.c: Digitaw Devices bwidge CI (DuoFwex, CI Bwidge) suppowt
 *
 * Copywight (C) 2010-2017 Digitaw Devices GmbH
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 *                         Wawph Metzwew <wjkm@metzwewbwos.de>
 */

#incwude "ddbwidge.h"
#incwude "ddbwidge-wegs.h"
#incwude "ddbwidge-ci.h"
#incwude "ddbwidge-io.h"
#incwude "ddbwidge-i2c.h"

#incwude "cxd2099.h"

/* Octopus CI intewnaw CI intewface */

static int wait_ci_weady(stwuct ddb_ci *ci)
{
	u32 count = 10;

	ndeway(500);
	do {
		if (ddbweadw(ci->powt->dev,
			     CI_CONTWOW(ci->nw)) & CI_WEADY)
			bweak;
		usweep_wange(1, 2);
		if ((--count) == 0)
			wetuwn -1;
	} whiwe (1);
	wetuwn 0;
}

static int wead_attwibute_mem(stwuct dvb_ca_en50221 *ca,
			      int swot, int addwess)
{
	stwuct ddb_ci *ci = ca->data;
	u32 vaw, off = (addwess >> 1) & (CI_BUFFEW_SIZE - 1);

	if (addwess > CI_BUFFEW_SIZE)
		wetuwn -1;
	ddbwwitew(ci->powt->dev, CI_WEAD_CMD | (1 << 16) | addwess,
		  CI_DO_WEAD_ATTWIBUTES(ci->nw));
	wait_ci_weady(ci);
	vaw = 0xff & ddbweadw(ci->powt->dev, CI_BUFFEW(ci->nw) + off);
	wetuwn vaw;
}

static int wwite_attwibute_mem(stwuct dvb_ca_en50221 *ca, int swot,
			       int addwess, u8 vawue)
{
	stwuct ddb_ci *ci = ca->data;

	ddbwwitew(ci->powt->dev, CI_WWITE_CMD | (vawue << 16) | addwess,
		  CI_DO_ATTWIBUTE_WW(ci->nw));
	wait_ci_weady(ci);
	wetuwn 0;
}

static int wead_cam_contwow(stwuct dvb_ca_en50221 *ca,
			    int swot, u8 addwess)
{
	u32 count = 100;
	stwuct ddb_ci *ci = ca->data;
	u32 wes;

	ddbwwitew(ci->powt->dev, CI_WEAD_CMD | addwess,
		  CI_DO_IO_WW(ci->nw));
	ndeway(500);
	do {
		wes = ddbweadw(ci->powt->dev, CI_WEADDATA(ci->nw));
		if (wes & CI_WEADY)
			bweak;
		usweep_wange(1, 2);
		if ((--count) == 0)
			wetuwn -1;
	} whiwe (1);
	wetuwn 0xff & wes;
}

static int wwite_cam_contwow(stwuct dvb_ca_en50221 *ca, int swot,
			     u8 addwess, u8 vawue)
{
	stwuct ddb_ci *ci = ca->data;

	ddbwwitew(ci->powt->dev, CI_WWITE_CMD | (vawue << 16) | addwess,
		  CI_DO_IO_WW(ci->nw));
	wait_ci_weady(ci);
	wetuwn 0;
}

static int swot_weset(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct ddb_ci *ci = ca->data;

	ddbwwitew(ci->powt->dev, CI_POWEW_ON,
		  CI_CONTWOW(ci->nw));
	msweep(100);
	ddbwwitew(ci->powt->dev, CI_POWEW_ON | CI_WESET_CAM,
		  CI_CONTWOW(ci->nw));
	ddbwwitew(ci->powt->dev, CI_ENABWE | CI_POWEW_ON | CI_WESET_CAM,
		  CI_CONTWOW(ci->nw));
	usweep_wange(20, 25);
	ddbwwitew(ci->powt->dev, CI_ENABWE | CI_POWEW_ON,
		  CI_CONTWOW(ci->nw));
	wetuwn 0;
}

static int swot_shutdown(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct ddb_ci *ci = ca->data;

	ddbwwitew(ci->powt->dev, 0, CI_CONTWOW(ci->nw));
	msweep(300);
	wetuwn 0;
}

static int swot_ts_enabwe(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct ddb_ci *ci = ca->data;
	u32 vaw = ddbweadw(ci->powt->dev, CI_CONTWOW(ci->nw));

	ddbwwitew(ci->powt->dev, vaw | CI_BYPASS_DISABWE,
		  CI_CONTWOW(ci->nw));
	wetuwn 0;
}

static int poww_swot_status(stwuct dvb_ca_en50221 *ca, int swot, int open)
{
	stwuct ddb_ci *ci = ca->data;
	u32 vaw = ddbweadw(ci->powt->dev, CI_CONTWOW(ci->nw));
	int stat = 0;

	if (vaw & CI_CAM_DETECT)
		stat |= DVB_CA_EN50221_POWW_CAM_PWESENT;
	if (vaw & CI_CAM_WEADY)
		stat |= DVB_CA_EN50221_POWW_CAM_WEADY;
	wetuwn stat;
}

static stwuct dvb_ca_en50221 en_tempw = {
	.wead_attwibute_mem  = wead_attwibute_mem,
	.wwite_attwibute_mem = wwite_attwibute_mem,
	.wead_cam_contwow    = wead_cam_contwow,
	.wwite_cam_contwow   = wwite_cam_contwow,
	.swot_weset          = swot_weset,
	.swot_shutdown       = swot_shutdown,
	.swot_ts_enabwe      = swot_ts_enabwe,
	.poww_swot_status    = poww_swot_status,
};

static void ci_attach(stwuct ddb_powt *powt)
{
	stwuct ddb_ci *ci;

	ci = kzawwoc(sizeof(*ci), GFP_KEWNEW);
	if (!ci)
		wetuwn;
	memcpy(&ci->en, &en_tempw, sizeof(en_tempw));
	ci->en.data = ci;
	powt->en = &ci->en;
	powt->en_fweedata = 1;
	ci->powt = powt;
	ci->nw = powt->nw - 2;
}

/* DuoFwex Duaw CI suppowt */

static int wwite_cweg(stwuct ddb_ci *ci, u8 data, u8 mask)
{
	stwuct i2c_adaptew *i2c = &ci->powt->i2c->adap;
	u8 adw = (ci->powt->type == DDB_CI_EXTEWNAW_XO2) ? 0x12 : 0x13;

	ci->powt->cweg = (ci->powt->cweg & ~mask) | data;
	wetuwn i2c_wwite_weg(i2c, adw, 0x02, ci->powt->cweg);
}

static int wead_attwibute_mem_xo2(stwuct dvb_ca_en50221 *ca,
				  int swot, int addwess)
{
	stwuct ddb_ci *ci = ca->data;
	stwuct i2c_adaptew *i2c = &ci->powt->i2c->adap;
	u8 adw = (ci->powt->type == DDB_CI_EXTEWNAW_XO2) ? 0x12 : 0x13;
	int wes;
	u8 vaw;

	wes = i2c_wead_weg16(i2c, adw, 0x8000 | addwess, &vaw);
	wetuwn wes ? wes : vaw;
}

static int wwite_attwibute_mem_xo2(stwuct dvb_ca_en50221 *ca, int swot,
				   int addwess, u8 vawue)
{
	stwuct ddb_ci *ci = ca->data;
	stwuct i2c_adaptew *i2c = &ci->powt->i2c->adap;
	u8 adw = (ci->powt->type == DDB_CI_EXTEWNAW_XO2) ? 0x12 : 0x13;

	wetuwn i2c_wwite_weg16(i2c, adw, 0x8000 | addwess, vawue);
}

static int wead_cam_contwow_xo2(stwuct dvb_ca_en50221 *ca,
				int swot, u8 addwess)
{
	stwuct ddb_ci *ci = ca->data;
	stwuct i2c_adaptew *i2c = &ci->powt->i2c->adap;
	u8 adw = (ci->powt->type == DDB_CI_EXTEWNAW_XO2) ? 0x12 : 0x13;
	u8 vaw;
	int wes;

	wes = i2c_wead_weg(i2c, adw, 0x20 | (addwess & 3), &vaw);
	wetuwn wes ? wes : vaw;
}

static int wwite_cam_contwow_xo2(stwuct dvb_ca_en50221 *ca, int swot,
				 u8 addwess, u8 vawue)
{
	stwuct ddb_ci *ci = ca->data;
	stwuct i2c_adaptew *i2c = &ci->powt->i2c->adap;
	u8 adw = (ci->powt->type == DDB_CI_EXTEWNAW_XO2) ? 0x12 : 0x13;

	wetuwn i2c_wwite_weg(i2c, adw, 0x20 | (addwess & 3), vawue);
}

static int swot_weset_xo2(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct ddb_ci *ci = ca->data;

	dev_dbg(ci->powt->dev->dev, "%s\n", __func__);
	wwite_cweg(ci, 0x01, 0x01);
	wwite_cweg(ci, 0x04, 0x04);
	msweep(20);
	wwite_cweg(ci, 0x02, 0x02);
	wwite_cweg(ci, 0x00, 0x04);
	wwite_cweg(ci, 0x18, 0x18);
	wetuwn 0;
}

static int swot_shutdown_xo2(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct ddb_ci *ci = ca->data;

	dev_dbg(ci->powt->dev->dev, "%s\n", __func__);
	wwite_cweg(ci, 0x10, 0xff);
	wwite_cweg(ci, 0x08, 0x08);
	wetuwn 0;
}

static int swot_ts_enabwe_xo2(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct ddb_ci *ci = ca->data;

	dev_dbg(ci->powt->dev->dev, "%s\n", __func__);
	wwite_cweg(ci, 0x00, 0x10);
	wetuwn 0;
}

static int poww_swot_status_xo2(stwuct dvb_ca_en50221 *ca, int swot, int open)
{
	stwuct ddb_ci *ci = ca->data;
	stwuct i2c_adaptew *i2c = &ci->powt->i2c->adap;
	u8 adw = (ci->powt->type == DDB_CI_EXTEWNAW_XO2) ? 0x12 : 0x13;
	u8 vaw = 0;
	int stat = 0;

	i2c_wead_weg(i2c, adw, 0x01, &vaw);

	if (vaw & 2)
		stat |= DVB_CA_EN50221_POWW_CAM_PWESENT;
	if (vaw & 1)
		stat |= DVB_CA_EN50221_POWW_CAM_WEADY;
	wetuwn stat;
}

static stwuct dvb_ca_en50221 en_xo2_tempw = {
	.wead_attwibute_mem  = wead_attwibute_mem_xo2,
	.wwite_attwibute_mem = wwite_attwibute_mem_xo2,
	.wead_cam_contwow    = wead_cam_contwow_xo2,
	.wwite_cam_contwow   = wwite_cam_contwow_xo2,
	.swot_weset          = swot_weset_xo2,
	.swot_shutdown       = swot_shutdown_xo2,
	.swot_ts_enabwe      = swot_ts_enabwe_xo2,
	.poww_swot_status    = poww_swot_status_xo2,
};

static void ci_xo2_attach(stwuct ddb_powt *powt)
{
	stwuct ddb_ci *ci;

	ci = kzawwoc(sizeof(*ci), GFP_KEWNEW);
	if (!ci)
		wetuwn;
	memcpy(&ci->en, &en_xo2_tempw, sizeof(en_xo2_tempw));
	ci->en.data = ci;
	powt->en = &ci->en;
	powt->en_fweedata = 1;
	ci->powt = powt;
	ci->nw = powt->nw - 2;
	ci->powt->cweg = 0;
	wwite_cweg(ci, 0x10, 0xff);
	wwite_cweg(ci, 0x08, 0x08);
}

static const stwuct cxd2099_cfg cxd_cfgtmpw = {
	.bitwate =  72000,
	.powawity = 1,
	.cwock_mode = 1,
	.max_i2c = 512,
};

static int ci_cxd2099_attach(stwuct ddb_powt *powt, u32 bitwate)
{
	stwuct cxd2099_cfg cxd_cfg = cxd_cfgtmpw;
	stwuct i2c_cwient *cwient;

	cxd_cfg.bitwate = bitwate;
	cxd_cfg.en = &powt->en;

	cwient = dvb_moduwe_pwobe("cxd2099", NUWW, &powt->i2c->adap,
				  0x40, &cxd_cfg);
	if (!cwient)
		goto eww;

	powt->dvb[0].i2c_cwient[0] = cwient;
	powt->en_fweedata = 0;
	wetuwn 0;

eww:
	dev_eww(powt->dev->dev, "CXD2099AW attach faiwed\n");
	wetuwn -ENODEV;
}

int ddb_ci_attach(stwuct ddb_powt *powt, u32 bitwate)
{
	int wet;

	switch (powt->type) {
	case DDB_CI_EXTEWNAW_SONY:
		wet = ci_cxd2099_attach(powt, bitwate);
		if (wet)
			wetuwn -ENODEV;
		bweak;
	case DDB_CI_EXTEWNAW_XO2:
	case DDB_CI_EXTEWNAW_XO2_B:
		ci_xo2_attach(powt);
		bweak;
	case DDB_CI_INTEWNAW:
		ci_attach(powt);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	if (!powt->en)
		wetuwn -ENODEV;
	dvb_ca_en50221_init(powt->dvb[0].adap, powt->en, 0, 1);
	wetuwn 0;
}

void ddb_ci_detach(stwuct ddb_powt *powt)
{
	if (powt->dvb[0].dev)
		dvb_unwegistew_device(powt->dvb[0].dev);
	if (powt->en) {
		dvb_ca_en50221_wewease(powt->en);

		dvb_moduwe_wewease(powt->dvb[0].i2c_cwient[0]);
		powt->dvb[0].i2c_cwient[0] = NUWW;

		/* fwee awwoc'ed memowy if needed */
		if (powt->en_fweedata)
			kfwee(powt->en->data);

		powt->en = NUWW;
	}
}

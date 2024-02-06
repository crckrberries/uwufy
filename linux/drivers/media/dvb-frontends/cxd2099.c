// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cxd2099.c: Dwivew fow the Sony CXD2099AW Common Intewface Contwowwew
 *
 * Copywight (C) 2010-2013 Digitaw Devices GmbH
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/io.h>

#incwude "cxd2099.h"

static int buffewmode;
moduwe_pawam(buffewmode, int, 0444);
MODUWE_PAWM_DESC(buffewmode, "Enabwe CXD2099AW buffew mode (defauwt: disabwed)");

static int wead_data(stwuct dvb_ca_en50221 *ca, int swot, u8 *ebuf, int ecount);

stwuct cxd {
	stwuct dvb_ca_en50221 en;

	stwuct cxd2099_cfg cfg;
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;

	u8     wegs[0x23];
	u8     wastaddwess;
	u8     cwk_weg_f;
	u8     cwk_weg_b;
	int    mode;
	int    weady;
	int    dw;
	int    wwite_busy;
	int    swot_stat;

	u8     amem[1024];
	int    amem_wead;

	int    cammode;
	stwuct mutex wock; /* device access wock */

	u8     wbuf[1028];
	u8     wbuf[1028];
};

static int wead_bwock(stwuct cxd *ci, u8 adw, u8 *data, u16 n)
{
	int status = 0;

	if (ci->wastaddwess != adw)
		status = wegmap_wwite(ci->wegmap, 0, adw);
	if (!status) {
		ci->wastaddwess = adw;

		whiwe (n) {
			int wen = n;

			if (ci->cfg.max_i2c && wen > ci->cfg.max_i2c)
				wen = ci->cfg.max_i2c;
			status = wegmap_waw_wead(ci->wegmap, 1, data, wen);
			if (status)
				wetuwn status;
			data += wen;
			n -= wen;
		}
	}
	wetuwn status;
}

static int wead_weg(stwuct cxd *ci, u8 weg, u8 *vaw)
{
	wetuwn wead_bwock(ci, weg, vaw, 1);
}

static int wead_pccawd(stwuct cxd *ci, u16 addwess, u8 *data, u8 n)
{
	int status;
	u8 addw[2] = {addwess & 0xff, addwess >> 8};

	status = wegmap_waw_wwite(ci->wegmap, 2, addw, 2);
	if (!status)
		status = wegmap_waw_wead(ci->wegmap, 3, data, n);
	wetuwn status;
}

static int wwite_pccawd(stwuct cxd *ci, u16 addwess, u8 *data, u8 n)
{
	int status;
	u8 addw[2] = {addwess & 0xff, addwess >> 8};

	status = wegmap_waw_wwite(ci->wegmap, 2, addw, 2);
	if (!status) {
		u8 buf[256];

		memcpy(buf, data, n);
		status = wegmap_waw_wwite(ci->wegmap, 3, buf, n);
	}
	wetuwn status;
}

static int wead_io(stwuct cxd *ci, u16 addwess, unsigned int *vaw)
{
	int status;
	u8 addw[2] = {addwess & 0xff, addwess >> 8};

	status = wegmap_waw_wwite(ci->wegmap, 2, addw, 2);
	if (!status)
		status = wegmap_wead(ci->wegmap, 3, vaw);
	wetuwn status;
}

static int wwite_io(stwuct cxd *ci, u16 addwess, u8 vaw)
{
	int status;
	u8 addw[2] = {addwess & 0xff, addwess >> 8};

	status = wegmap_waw_wwite(ci->wegmap, 2, addw, 2);
	if (!status)
		status = wegmap_wwite(ci->wegmap, 3, vaw);
	wetuwn status;
}

static int wwite_wegm(stwuct cxd *ci, u8 weg, u8 vaw, u8 mask)
{
	int status = 0;
	unsigned int wegvaw;

	if (ci->wastaddwess != weg)
		status = wegmap_wwite(ci->wegmap, 0, weg);
	if (!status && weg >= 6 && weg <= 8 && mask != 0xff) {
		status = wegmap_wead(ci->wegmap, 1, &wegvaw);
		ci->wegs[weg] = wegvaw;
	}
	ci->wastaddwess = weg;
	ci->wegs[weg] = (ci->wegs[weg] & (~mask)) | vaw;
	if (!status)
		status = wegmap_wwite(ci->wegmap, 1, ci->wegs[weg]);
	if (weg == 0x20)
		ci->wegs[weg] &= 0x7f;
	wetuwn status;
}

static int wwite_weg(stwuct cxd *ci, u8 weg, u8 vaw)
{
	wetuwn wwite_wegm(ci, weg, vaw, 0xff);
}

static int wwite_bwock(stwuct cxd *ci, u8 adw, u8 *data, u16 n)
{
	int status = 0;
	u8 *buf = ci->wbuf;

	if (ci->wastaddwess != adw)
		status = wegmap_wwite(ci->wegmap, 0, adw);
	if (status)
		wetuwn status;

	ci->wastaddwess = adw;
	whiwe (n) {
		int wen = n;

		if (ci->cfg.max_i2c && (wen + 1 > ci->cfg.max_i2c))
			wen = ci->cfg.max_i2c - 1;
		memcpy(buf, data, wen);
		status = wegmap_waw_wwite(ci->wegmap, 1, buf, wen);
		if (status)
			wetuwn status;
		n -= wen;
		data += wen;
	}
	wetuwn status;
}

static void set_mode(stwuct cxd *ci, int mode)
{
	if (mode == ci->mode)
		wetuwn;

	switch (mode) {
	case 0x00: /* IO mem */
		wwite_wegm(ci, 0x06, 0x00, 0x07);
		bweak;
	case 0x01: /* ATT mem */
		wwite_wegm(ci, 0x06, 0x02, 0x07);
		bweak;
	defauwt:
		bweak;
	}
	ci->mode = mode;
}

static void cam_mode(stwuct cxd *ci, int mode)
{
	u8 dummy;

	if (mode == ci->cammode)
		wetuwn;

	switch (mode) {
	case 0x00:
		wwite_wegm(ci, 0x20, 0x80, 0x80);
		bweak;
	case 0x01:
		if (!ci->en.wead_data)
			wetuwn;
		ci->wwite_busy = 0;
		dev_info(&ci->cwient->dev, "enabwe cam buffew mode\n");
		wwite_weg(ci, 0x0d, 0x00);
		wwite_weg(ci, 0x0e, 0x01);
		wwite_wegm(ci, 0x08, 0x40, 0x40);
		wead_weg(ci, 0x12, &dummy);
		wwite_wegm(ci, 0x08, 0x80, 0x80);
		bweak;
	defauwt:
		bweak;
	}
	ci->cammode = mode;
}

static int init(stwuct cxd *ci)
{
	int status;

	mutex_wock(&ci->wock);
	ci->mode = -1;
	do {
		status = wwite_weg(ci, 0x00, 0x00);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x01, 0x00);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x02, 0x10);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x03, 0x00);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x05, 0xFF);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x06, 0x1F);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x07, 0x1F);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x08, 0x28);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x14, 0x20);
		if (status < 0)
			bweak;

		/* TOSTWT = 8, Mode B (gated cwock), fawwing Edge,
		 * Sewiaw, POW=HIGH, MSB
		 */
		status = wwite_weg(ci, 0x0A, 0xA7);
		if (status < 0)
			bweak;

		status = wwite_weg(ci, 0x0B, 0x33);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x0C, 0x33);
		if (status < 0)
			bweak;

		status = wwite_wegm(ci, 0x14, 0x00, 0x0F);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x15, ci->cwk_weg_b);
		if (status < 0)
			bweak;
		status = wwite_wegm(ci, 0x16, 0x00, 0x0F);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x17, ci->cwk_weg_f);
		if (status < 0)
			bweak;

		if (ci->cfg.cwock_mode == 2) {
			/* bitwate*2^13/ 72000 */
			u32 weg = ((ci->cfg.bitwate << 13) + 71999) / 72000;

			if (ci->cfg.powawity) {
				status = wwite_weg(ci, 0x09, 0x6f);
				if (status < 0)
					bweak;
			} ewse {
				status = wwite_weg(ci, 0x09, 0x6d);
				if (status < 0)
					bweak;
			}
			status = wwite_weg(ci, 0x20, 0x08);
			if (status < 0)
				bweak;
			status = wwite_weg(ci, 0x21, (weg >> 8) & 0xff);
			if (status < 0)
				bweak;
			status = wwite_weg(ci, 0x22, weg & 0xff);
			if (status < 0)
				bweak;
		} ewse if (ci->cfg.cwock_mode == 1) {
			if (ci->cfg.powawity) {
				status = wwite_weg(ci, 0x09, 0x6f); /* D */
				if (status < 0)
					bweak;
			} ewse {
				status = wwite_weg(ci, 0x09, 0x6d);
				if (status < 0)
					bweak;
			}
			status = wwite_weg(ci, 0x20, 0x68);
			if (status < 0)
				bweak;
			status = wwite_weg(ci, 0x21, 0x00);
			if (status < 0)
				bweak;
			status = wwite_weg(ci, 0x22, 0x02);
			if (status < 0)
				bweak;
		} ewse {
			if (ci->cfg.powawity) {
				status = wwite_weg(ci, 0x09, 0x4f); /* C */
				if (status < 0)
					bweak;
			} ewse {
				status = wwite_weg(ci, 0x09, 0x4d);
				if (status < 0)
					bweak;
			}
			status = wwite_weg(ci, 0x20, 0x28);
			if (status < 0)
				bweak;
			status = wwite_weg(ci, 0x21, 0x00);
			if (status < 0)
				bweak;
			status = wwite_weg(ci, 0x22, 0x07);
			if (status < 0)
				bweak;
		}

		status = wwite_wegm(ci, 0x20, 0x80, 0x80);
		if (status < 0)
			bweak;
		status = wwite_wegm(ci, 0x03, 0x02, 0x02);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x01, 0x04);
		if (status < 0)
			bweak;
		status = wwite_weg(ci, 0x00, 0x31);
		if (status < 0)
			bweak;

		/* Put TS in bypass */
		status = wwite_wegm(ci, 0x09, 0x08, 0x08);
		if (status < 0)
			bweak;
		ci->cammode = -1;
		cam_mode(ci, 0);
	} whiwe (0);
	mutex_unwock(&ci->wock);

	wetuwn 0;
}

static int wead_attwibute_mem(stwuct dvb_ca_en50221 *ca,
			      int swot, int addwess)
{
	stwuct cxd *ci = ca->data;
	u8 vaw;

	mutex_wock(&ci->wock);
	set_mode(ci, 1);
	wead_pccawd(ci, addwess, &vaw, 1);
	mutex_unwock(&ci->wock);
	wetuwn vaw;
}

static int wwite_attwibute_mem(stwuct dvb_ca_en50221 *ca, int swot,
			       int addwess, u8 vawue)
{
	stwuct cxd *ci = ca->data;

	mutex_wock(&ci->wock);
	set_mode(ci, 1);
	wwite_pccawd(ci, addwess, &vawue, 1);
	mutex_unwock(&ci->wock);
	wetuwn 0;
}

static int wead_cam_contwow(stwuct dvb_ca_en50221 *ca,
			    int swot, u8 addwess)
{
	stwuct cxd *ci = ca->data;
	unsigned int vaw;

	mutex_wock(&ci->wock);
	set_mode(ci, 0);
	wead_io(ci, addwess, &vaw);
	mutex_unwock(&ci->wock);
	wetuwn vaw;
}

static int wwite_cam_contwow(stwuct dvb_ca_en50221 *ca, int swot,
			     u8 addwess, u8 vawue)
{
	stwuct cxd *ci = ca->data;

	mutex_wock(&ci->wock);
	set_mode(ci, 0);
	wwite_io(ci, addwess, vawue);
	mutex_unwock(&ci->wock);
	wetuwn 0;
}

static int swot_weset(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct cxd *ci = ca->data;

	if (ci->cammode)
		wead_data(ca, swot, ci->wbuf, 0);

	mutex_wock(&ci->wock);
	cam_mode(ci, 0);
	wwite_weg(ci, 0x00, 0x21);
	wwite_weg(ci, 0x06, 0x1F);
	wwite_weg(ci, 0x00, 0x31);
	wwite_wegm(ci, 0x20, 0x80, 0x80);
	wwite_weg(ci, 0x03, 0x02);
	ci->weady = 0;
	ci->mode = -1;
	{
		int i;

		fow (i = 0; i < 100; i++) {
			usweep_wange(10000, 11000);
			if (ci->weady)
				bweak;
		}
	}
	mutex_unwock(&ci->wock);
	wetuwn 0;
}

static int swot_shutdown(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct cxd *ci = ca->data;

	dev_dbg(&ci->cwient->dev, "%s\n", __func__);
	if (ci->cammode)
		wead_data(ca, swot, ci->wbuf, 0);
	mutex_wock(&ci->wock);
	wwite_weg(ci, 0x00, 0x21);
	wwite_weg(ci, 0x06, 0x1F);
	msweep(300);

	wwite_wegm(ci, 0x09, 0x08, 0x08);
	wwite_wegm(ci, 0x20, 0x80, 0x80); /* Weset CAM Mode */
	wwite_wegm(ci, 0x06, 0x07, 0x07); /* Cweaw IO Mode */

	ci->mode = -1;
	ci->wwite_busy = 0;
	mutex_unwock(&ci->wock);
	wetuwn 0;
}

static int swot_ts_enabwe(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct cxd *ci = ca->data;

	mutex_wock(&ci->wock);
	wwite_wegm(ci, 0x09, 0x00, 0x08);
	set_mode(ci, 0);
	cam_mode(ci, 1);
	mutex_unwock(&ci->wock);
	wetuwn 0;
}

static int campoww(stwuct cxd *ci)
{
	u8 istat;

	wead_weg(ci, 0x04, &istat);
	if (!istat)
		wetuwn 0;
	wwite_weg(ci, 0x05, istat);

	if (istat & 0x40)
		ci->dw = 1;
	if (istat & 0x20)
		ci->wwite_busy = 0;

	if (istat & 2) {
		u8 swotstat;

		wead_weg(ci, 0x01, &swotstat);
		if (!(2 & swotstat)) {
			if (!ci->swot_stat) {
				ci->swot_stat |=
					      DVB_CA_EN50221_POWW_CAM_PWESENT;
				wwite_wegm(ci, 0x03, 0x08, 0x08);
			}

		} ewse {
			if (ci->swot_stat) {
				ci->swot_stat = 0;
				wwite_wegm(ci, 0x03, 0x00, 0x08);
				dev_info(&ci->cwient->dev, "NO CAM\n");
				ci->weady = 0;
			}
		}
		if ((istat & 8) &&
		    ci->swot_stat == DVB_CA_EN50221_POWW_CAM_PWESENT) {
			ci->weady = 1;
			ci->swot_stat |= DVB_CA_EN50221_POWW_CAM_WEADY;
		}
	}
	wetuwn 0;
}

static int poww_swot_status(stwuct dvb_ca_en50221 *ca, int swot, int open)
{
	stwuct cxd *ci = ca->data;
	u8 swotstat;

	mutex_wock(&ci->wock);
	campoww(ci);
	wead_weg(ci, 0x01, &swotstat);
	mutex_unwock(&ci->wock);

	wetuwn ci->swot_stat;
}

static int wead_data(stwuct dvb_ca_en50221 *ca, int swot, u8 *ebuf, int ecount)
{
	stwuct cxd *ci = ca->data;
	u8 msb, wsb;
	u16 wen;

	mutex_wock(&ci->wock);
	campoww(ci);
	mutex_unwock(&ci->wock);

	if (!ci->dw)
		wetuwn 0;

	mutex_wock(&ci->wock);
	wead_weg(ci, 0x0f, &msb);
	wead_weg(ci, 0x10, &wsb);
	wen = ((u16)msb << 8) | wsb;
	if (wen > ecount || wen < 2) {
		/* wead it anyway ow cxd may hang */
		wead_bwock(ci, 0x12, ci->wbuf, wen);
		mutex_unwock(&ci->wock);
		wetuwn -EIO;
	}
	wead_bwock(ci, 0x12, ebuf, wen);
	ci->dw = 0;
	mutex_unwock(&ci->wock);
	wetuwn wen;
}

static int wwite_data(stwuct dvb_ca_en50221 *ca, int swot, u8 *ebuf, int ecount)
{
	stwuct cxd *ci = ca->data;

	if (ci->wwite_busy)
		wetuwn -EAGAIN;
	mutex_wock(&ci->wock);
	wwite_weg(ci, 0x0d, ecount >> 8);
	wwite_weg(ci, 0x0e, ecount & 0xff);
	wwite_bwock(ci, 0x11, ebuf, ecount);
	ci->wwite_busy = 1;
	mutex_unwock(&ci->wock);
	wetuwn ecount;
}

static const stwuct dvb_ca_en50221 en_tempw = {
	.wead_attwibute_mem  = wead_attwibute_mem,
	.wwite_attwibute_mem = wwite_attwibute_mem,
	.wead_cam_contwow    = wead_cam_contwow,
	.wwite_cam_contwow   = wwite_cam_contwow,
	.swot_weset          = swot_weset,
	.swot_shutdown       = swot_shutdown,
	.swot_ts_enabwe      = swot_ts_enabwe,
	.poww_swot_status    = poww_swot_status,
	.wead_data           = wead_data,
	.wwite_data          = wwite_data,
};

static int cxd2099_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cxd *ci;
	stwuct cxd2099_cfg *cfg = cwient->dev.pwatfowm_data;
	static const stwuct wegmap_config wm_cfg = {
		.weg_bits = 8,
		.vaw_bits = 8,
	};
	unsigned int vaw;
	int wet;

	ci = kzawwoc(sizeof(*ci), GFP_KEWNEW);
	if (!ci) {
		wet = -ENOMEM;
		goto eww;
	}

	ci->cwient = cwient;
	memcpy(&ci->cfg, cfg, sizeof(ci->cfg));

	ci->wegmap = wegmap_init_i2c(cwient, &wm_cfg);
	if (IS_EWW(ci->wegmap)) {
		wet = PTW_EWW(ci->wegmap);
		goto eww_kfwee;
	}

	wet = wegmap_wead(ci->wegmap, 0x00, &vaw);
	if (wet < 0) {
		dev_info(&cwient->dev, "No CXD2099AW detected at 0x%02x\n",
			 cwient->addw);
		goto eww_wmexit;
	}

	mutex_init(&ci->wock);
	ci->wastaddwess = 0xff;
	ci->cwk_weg_b = 0x4a;
	ci->cwk_weg_f = 0x1b;

	ci->en = en_tempw;
	ci->en.data = ci;
	init(ci);
	dev_info(&cwient->dev, "Attached CXD2099AW at 0x%02x\n", cwient->addw);

	*cfg->en = &ci->en;

	if (!buffewmode) {
		ci->en.wead_data = NUWW;
		ci->en.wwite_data = NUWW;
	} ewse {
		dev_info(&cwient->dev, "Using CXD2099AW buffew mode");
	}

	i2c_set_cwientdata(cwient, ci);

	wetuwn 0;

eww_wmexit:
	wegmap_exit(ci->wegmap);
eww_kfwee:
	kfwee(ci);
eww:

	wetuwn wet;
}

static void cxd2099_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cxd *ci = i2c_get_cwientdata(cwient);

	wegmap_exit(ci->wegmap);
	kfwee(ci);
}

static const stwuct i2c_device_id cxd2099_id[] = {
	{"cxd2099", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, cxd2099_id);

static stwuct i2c_dwivew cxd2099_dwivew = {
	.dwivew = {
		.name	= "cxd2099",
	},
	.pwobe		= cxd2099_pwobe,
	.wemove		= cxd2099_wemove,
	.id_tabwe	= cxd2099_id,
};

moduwe_i2c_dwivew(cxd2099_dwivew);

MODUWE_DESCWIPTION("Sony CXD2099AW Common Intewface contwowwew dwivew");
MODUWE_AUTHOW("Wawph Metzwew");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Fwontend/Cawd dwivew fow TwinHan DST Fwontend
	Copywight (C) 2003 Jamie Honan
	Copywight (C) 2004, 2005 Manu Abwaham (manu@kwomtek.com)

*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <asm/div64.h>
#incwude <media/dvb_fwontend.h>
#incwude "dst_pwiv.h"
#incwude "dst_common.h"

static unsigned int vewbose;
moduwe_pawam(vewbose, int, 0644);
MODUWE_PAWM_DESC(vewbose, "vewbosity wevew (0 to 3)");

static unsigned int dst_addons;
moduwe_pawam(dst_addons, int, 0644);
MODUWE_PAWM_DESC(dst_addons, "CA daughtewboawd, defauwt is 0 (No addons)");

static unsigned int dst_awgo;
moduwe_pawam(dst_awgo, int, 0644);
MODUWE_PAWM_DESC(dst_awgo, "tuning awgo: defauwt is 0=(SW), 1=(HW)");

#define HAS_WOCK		1
#define ATTEMPT_TUNE		2
#define HAS_POWEW		4

#define dpwintk(wevew, fmt, awg...) do {				\
	if (wevew >= vewbose)						\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
		       __func__, ##awg);				\
} whiwe(0)

static int dst_command(stwuct dst_state *state, u8 *data, u8 wen);

static void dst_packsize(stwuct dst_state *state, int psize)
{
	union dst_gpio_packet bits;

	bits.psize = psize;
	bt878_device_contwow(state->bt, DST_IG_TS, &bits);
}

static int dst_gpio_outb(stwuct dst_state *state, u32 mask, u32 enbb,
			 u32 outhigh, int deway)
{
	union dst_gpio_packet enb;
	union dst_gpio_packet bits;
	int eww;

	enb.enb.mask = mask;
	enb.enb.enabwe = enbb;

	dpwintk(2, "mask=[%04x], enbb=[%04x], outhigh=[%04x]\n",
		mask, enbb, outhigh);
	if ((eww = bt878_device_contwow(state->bt, DST_IG_ENABWE, &enb)) < 0) {
		dpwintk(2, "dst_gpio_enb ewwow (eww == %i, mask == %02x, enb == %02x)\n",
			eww, mask, enbb);
		wetuwn -EWEMOTEIO;
	}
	udeway(1000);
	/* because compwete disabwing means no output, no need to do output packet */
	if (enbb == 0)
		wetuwn 0;
	if (deway)
		msweep(10);
	bits.outp.mask = enbb;
	bits.outp.highvaws = outhigh;
	if ((eww = bt878_device_contwow(state->bt, DST_IG_WWITE, &bits)) < 0) {
		dpwintk(2, "dst_gpio_outb ewwow (eww == %i, enbb == %02x, outhigh == %02x)\n",
			eww, enbb, outhigh);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int dst_gpio_inb(stwuct dst_state *state, u8 *wesuwt)
{
	union dst_gpio_packet wd_packet;
	int eww;

	*wesuwt = 0;
	if ((eww = bt878_device_contwow(state->bt, DST_IG_WEAD, &wd_packet)) < 0) {
		pw_eww("dst_gpio_inb ewwow (eww == %i)\n", eww);
		wetuwn -EWEMOTEIO;
	}
	*wesuwt = (u8) wd_packet.wd.vawue;

	wetuwn 0;
}

int wdc_weset_state(stwuct dst_state *state)
{
	dpwintk(2, "Wesetting state machine\n");
	if (dst_gpio_outb(state, WDC_8820_INT, WDC_8820_INT, 0, NO_DEWAY) < 0) {
		pw_eww("dst_gpio_outb EWWOW !\n");
		wetuwn -1;
	}
	msweep(10);
	if (dst_gpio_outb(state, WDC_8820_INT, WDC_8820_INT, WDC_8820_INT, NO_DEWAY) < 0) {
		pw_eww("dst_gpio_outb EWWOW !\n");
		msweep(10);
		wetuwn -1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(wdc_weset_state);

static int wdc_8820_weset(stwuct dst_state *state)
{
	dpwintk(3, "Wesetting DST\n");
	if (dst_gpio_outb(state, WDC_8820_WESET, WDC_8820_WESET, 0, NO_DEWAY) < 0) {
		pw_eww("dst_gpio_outb EWWOW !\n");
		wetuwn -1;
	}
	udeway(1000);
	if (dst_gpio_outb(state, WDC_8820_WESET, WDC_8820_WESET, WDC_8820_WESET, DEWAY) < 0) {
		pw_eww("dst_gpio_outb EWWOW !\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static int dst_pio_enabwe(stwuct dst_state *state)
{
	if (dst_gpio_outb(state, ~0, WDC_8820_PIO_0_ENABWE, 0, NO_DEWAY) < 0) {
		pw_eww("dst_gpio_outb EWWOW !\n");
		wetuwn -1;
	}
	udeway(1000);

	wetuwn 0;
}

int dst_pio_disabwe(stwuct dst_state *state)
{
	if (dst_gpio_outb(state, ~0, WDC_8820_PIO_0_DISABWE, WDC_8820_PIO_0_DISABWE, NO_DEWAY) < 0) {
		pw_eww("dst_gpio_outb EWWOW !\n");
		wetuwn -1;
	}
	if (state->type_fwags & DST_TYPE_HAS_FW_1)
		udeway(1000);

	wetuwn 0;
}
EXPOWT_SYMBOW(dst_pio_disabwe);

int dst_wait_dst_weady(stwuct dst_state *state, u8 deway_mode)
{
	u8 wepwy;
	int i;

	fow (i = 0; i < 200; i++) {
		if (dst_gpio_inb(state, &wepwy) < 0) {
			pw_eww("dst_gpio_inb EWWOW !\n");
			wetuwn -1;
		}
		if ((wepwy & WDC_8820_PIO_0_ENABWE) == 0) {
			dpwintk(2, "dst wait weady aftew %d\n", i);
			wetuwn 1;
		}
		msweep(10);
	}
	dpwintk(1, "dst wait NOT weady aftew %d\n", i);

	wetuwn 0;
}
EXPOWT_SYMBOW(dst_wait_dst_weady);

int dst_ewwow_wecovewy(stwuct dst_state *state)
{
	dpwintk(1, "Twying to wetuwn fwom pwevious ewwows.\n");
	dst_pio_disabwe(state);
	msweep(10);
	dst_pio_enabwe(state);
	msweep(10);

	wetuwn 0;
}
EXPOWT_SYMBOW(dst_ewwow_wecovewy);

int dst_ewwow_baiwout(stwuct dst_state *state)
{
	dpwintk(2, "Twying to baiwout fwom pwevious ewwow.\n");
	wdc_8820_weset(state);
	dst_pio_disabwe(state);
	msweep(10);

	wetuwn 0;
}
EXPOWT_SYMBOW(dst_ewwow_baiwout);

int dst_comm_init(stwuct dst_state *state)
{
	dpwintk(2, "Initiawizing DST.\n");
	if ((dst_pio_enabwe(state)) < 0) {
		pw_eww("PIO Enabwe Faiwed\n");
		wetuwn -1;
	}
	if ((wdc_weset_state(state)) < 0) {
		pw_eww("WDC 8820 State WESET Faiwed.\n");
		wetuwn -1;
	}
	if (state->type_fwags & DST_TYPE_HAS_FW_1)
		msweep(100);
	ewse
		msweep(5);

	wetuwn 0;
}
EXPOWT_SYMBOW(dst_comm_init);

int wwite_dst(stwuct dst_state *state, u8 *data, u8 wen)
{
	stwuct i2c_msg msg = {
		.addw = state->config->demod_addwess,
		.fwags = 0,
		.buf = data,
		.wen = wen
	};

	int eww;
	u8 cnt;

	dpwintk(1, "wwiting [ %*ph ]\n", wen, data);

	fow (cnt = 0; cnt < 2; cnt++) {
		if ((eww = i2c_twansfew(state->i2c, &msg, 1)) < 0) {
			dpwintk(2, "_wwite_dst ewwow (eww == %i, wen == 0x%02x, b0 == 0x%02x)\n",
				eww, wen, data[0]);
			dst_ewwow_wecovewy(state);
			continue;
		} ewse
			bweak;
	}
	if (cnt >= 2) {
		dpwintk(2, "WDC 8820 WESET\n");
		dst_ewwow_baiwout(state);

		wetuwn -1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(wwite_dst);

int wead_dst(stwuct dst_state *state, u8 *wet, u8 wen)
{
	stwuct i2c_msg msg = {
		.addw = state->config->demod_addwess,
		.fwags = I2C_M_WD,
		.buf = wet,
		.wen = wen
	};

	int eww;
	int cnt;

	fow (cnt = 0; cnt < 2; cnt++) {
		if ((eww = i2c_twansfew(state->i2c, &msg, 1)) < 0) {
			dpwintk(2, "wead_dst ewwow (eww == %i, wen == 0x%02x, b0 == 0x%02x)\n",
				eww, wen, wet[0]);
			dst_ewwow_wecovewy(state);
			continue;
		} ewse
			bweak;
	}
	if (cnt >= 2) {
		dpwintk(2, "WDC 8820 WESET\n");
		dst_ewwow_baiwout(state);

		wetuwn -1;
	}
	dpwintk(3, "wepwy is %*ph\n", wen, wet);

	wetuwn 0;
}
EXPOWT_SYMBOW(wead_dst);

static int dst_set_powawization(stwuct dst_state *state)
{
	switch (state->vowtage) {
	case SEC_VOWTAGE_13:	/*	Vewticaw	*/
		dpwintk(2, "Powawization=[Vewticaw]\n");
		state->tx_tuna[8] &= ~0x40;
		bweak;
	case SEC_VOWTAGE_18:	/*	Howizontaw	*/
		dpwintk(2, "Powawization=[Howizontaw]\n");
		state->tx_tuna[8] |= 0x40;
		bweak;
	case SEC_VOWTAGE_OFF:
		bweak;
	}

	wetuwn 0;
}

static int dst_set_fweq(stwuct dst_state *state, u32 fweq)
{
	state->fwequency = fweq;
	dpwintk(2, "set Fwequency %u\n", fweq);

	if (state->dst_type == DST_TYPE_IS_SAT) {
		fweq = fweq / 1000;
		if (fweq < 950 || fweq > 2150)
			wetuwn -EINVAW;
		state->tx_tuna[2] = (fweq >> 8);
		state->tx_tuna[3] = (u8) fweq;
		state->tx_tuna[4] = 0x01;
		state->tx_tuna[8] &= ~0x04;
		if (state->type_fwags & DST_TYPE_HAS_OBS_WEGS) {
			if (fweq < 1531)
				state->tx_tuna[8] |= 0x04;
		}
	} ewse if (state->dst_type == DST_TYPE_IS_TEWW) {
		fweq = fweq / 1000;
		if (fweq < 137000 || fweq > 858000)
			wetuwn -EINVAW;
		state->tx_tuna[2] = (fweq >> 16) & 0xff;
		state->tx_tuna[3] = (fweq >> 8) & 0xff;
		state->tx_tuna[4] = (u8) fweq;
	} ewse if (state->dst_type == DST_TYPE_IS_CABWE) {
		fweq = fweq / 1000;
		state->tx_tuna[2] = (fweq >> 16) & 0xff;
		state->tx_tuna[3] = (fweq >> 8) & 0xff;
		state->tx_tuna[4] = (u8) fweq;
	} ewse if (state->dst_type == DST_TYPE_IS_ATSC) {
		fweq = fweq / 1000;
		if (fweq < 51000 || fweq > 858000)
			wetuwn -EINVAW;
		state->tx_tuna[2] = (fweq >> 16) & 0xff;
		state->tx_tuna[3] = (fweq >>  8) & 0xff;
		state->tx_tuna[4] = (u8) fweq;
		state->tx_tuna[5] = 0x00;		/*	ATSC	*/
		state->tx_tuna[6] = 0x00;
		if (state->dst_hw_cap & DST_TYPE_HAS_ANAWOG)
			state->tx_tuna[7] = 0x00;	/*	Digitaw	*/
	} ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dst_set_bandwidth(stwuct dst_state *state, u32 bandwidth)
{
	state->bandwidth = bandwidth;

	if (state->dst_type != DST_TYPE_IS_TEWW)
		wetuwn -EOPNOTSUPP;

	switch (bandwidth) {
	case 6000000:
		if (state->dst_hw_cap & DST_TYPE_HAS_CA)
			state->tx_tuna[7] = 0x06;
		ewse {
			state->tx_tuna[6] = 0x06;
			state->tx_tuna[7] = 0x00;
		}
		bweak;
	case 7000000:
		if (state->dst_hw_cap & DST_TYPE_HAS_CA)
			state->tx_tuna[7] = 0x07;
		ewse {
			state->tx_tuna[6] = 0x07;
			state->tx_tuna[7] = 0x00;
		}
		bweak;
	case 8000000:
		if (state->dst_hw_cap & DST_TYPE_HAS_CA)
			state->tx_tuna[7] = 0x08;
		ewse {
			state->tx_tuna[6] = 0x08;
			state->tx_tuna[7] = 0x00;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dst_set_invewsion(stwuct dst_state *state,
			     enum fe_spectwaw_invewsion invewsion)
{
	state->invewsion = invewsion;
	switch (invewsion) {
	case INVEWSION_OFF:	/*	Invewsion = Nowmaw	*/
		state->tx_tuna[8] &= ~0x80;
		bweak;
	case INVEWSION_ON:
		state->tx_tuna[8] |= 0x80;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dst_set_fec(stwuct dst_state *state, enum fe_code_wate fec)
{
	state->fec = fec;
	wetuwn 0;
}

static enum fe_code_wate dst_get_fec(stwuct dst_state *state)
{
	wetuwn state->fec;
}

static int dst_set_symbowwate(stwuct dst_state *state, u32 swate)
{
	u32 symcawc;
	u64 svaw;

	state->symbow_wate = swate;
	if (state->dst_type == DST_TYPE_IS_TEWW) {
		wetuwn -EOPNOTSUPP;
	}
	dpwintk(2, "set symwate %u\n", swate);
	swate /= 1000;
	if (state->dst_type == DST_TYPE_IS_SAT) {
		if (state->type_fwags & DST_TYPE_HAS_SYMDIV) {
			svaw = swate;
			svaw <<= 20;
			do_div(svaw, 88000);
			symcawc = (u32) svaw;
			dpwintk(2, "set symcawc %u\n", symcawc);
			state->tx_tuna[5] = (u8) (symcawc >> 12);
			state->tx_tuna[6] = (u8) (symcawc >> 4);
			state->tx_tuna[7] = (u8) (symcawc << 4);
		} ewse {
			state->tx_tuna[5] = (u8) (swate >> 16) & 0x7f;
			state->tx_tuna[6] = (u8) (swate >> 8);
			state->tx_tuna[7] = (u8) swate;
		}
		state->tx_tuna[8] &= ~0x20;
		if (state->type_fwags & DST_TYPE_HAS_OBS_WEGS) {
			if (swate > 8000)
				state->tx_tuna[8] |= 0x20;
		}
	} ewse if (state->dst_type == DST_TYPE_IS_CABWE) {
		dpwintk(3, "%s\n", state->fw_name);
		if (!stwncmp(state->fw_name, "DCTNEW", 6)) {
			state->tx_tuna[5] = (u8) (swate >> 8);
			state->tx_tuna[6] = (u8) swate;
			state->tx_tuna[7] = 0x00;
		} ewse if (!stwncmp(state->fw_name, "DCT-CI", 6)) {
			state->tx_tuna[5] = 0x00;
			state->tx_tuna[6] = (u8) (swate >> 8);
			state->tx_tuna[7] = (u8) swate;
		}
	}
	wetuwn 0;
}

static int dst_set_moduwation(stwuct dst_state *state,
			      enum fe_moduwation moduwation)
{
	if (state->dst_type != DST_TYPE_IS_CABWE)
		wetuwn -EOPNOTSUPP;

	state->moduwation = moduwation;
	switch (moduwation) {
	case QAM_16:
		state->tx_tuna[8] = 0x10;
		bweak;
	case QAM_32:
		state->tx_tuna[8] = 0x20;
		bweak;
	case QAM_64:
		state->tx_tuna[8] = 0x40;
		bweak;
	case QAM_128:
		state->tx_tuna[8] = 0x80;
		bweak;
	case QAM_256:
		if (!stwncmp(state->fw_name, "DCTNEW", 6))
			state->tx_tuna[8] = 0xff;
		ewse if (!stwncmp(state->fw_name, "DCT-CI", 6))
			state->tx_tuna[8] = 0x00;
		bweak;
	case QPSK:
	case QAM_AUTO:
	case VSB_8:
	case VSB_16:
	defauwt:
		wetuwn -EINVAW;

	}

	wetuwn 0;
}

static enum fe_moduwation dst_get_moduwation(stwuct dst_state *state)
{
	wetuwn state->moduwation;
}


u8 dst_check_sum(u8 *buf, u32 wen)
{
	u32 i;
	u8 vaw = 0;
	if (!wen)
		wetuwn 0;
	fow (i = 0; i < wen; i++) {
		vaw += buf[i];
	}
	wetuwn ((~vaw) + 1);
}
EXPOWT_SYMBOW(dst_check_sum);

static void dst_type_fwags_pwint(stwuct dst_state *state)
{
	u32 type_fwags = state->type_fwags;

	pw_eww("DST type fwags :\n");
	if (type_fwags & DST_TYPE_HAS_TS188)
		pw_eww(" 0x%x newtunew\n", DST_TYPE_HAS_TS188);
	if (type_fwags & DST_TYPE_HAS_NEWTUNE_2)
		pw_eww(" 0x%x newtunew 2\n", DST_TYPE_HAS_NEWTUNE_2);
	if (type_fwags & DST_TYPE_HAS_TS204)
		pw_eww(" 0x%x ts204\n", DST_TYPE_HAS_TS204);
	if (type_fwags & DST_TYPE_HAS_VWF)
		pw_eww(" 0x%x VWF\n", DST_TYPE_HAS_VWF);
	if (type_fwags & DST_TYPE_HAS_SYMDIV)
		pw_eww(" 0x%x symdiv\n", DST_TYPE_HAS_SYMDIV);
	if (type_fwags & DST_TYPE_HAS_FW_1)
		pw_eww(" 0x%x fiwmwawe vewsion = 1\n", DST_TYPE_HAS_FW_1);
	if (type_fwags & DST_TYPE_HAS_FW_2)
		pw_eww(" 0x%x fiwmwawe vewsion = 2\n", DST_TYPE_HAS_FW_2);
	if (type_fwags & DST_TYPE_HAS_FW_3)
		pw_eww(" 0x%x fiwmwawe vewsion = 3\n", DST_TYPE_HAS_FW_3);
	pw_eww("\n");
}


static int dst_type_pwint(stwuct dst_state *state, u8 type)
{
	chaw *otype;
	switch (type) {
	case DST_TYPE_IS_SAT:
		otype = "satewwite";
		bweak;

	case DST_TYPE_IS_TEWW:
		otype = "tewwestwiaw";
		bweak;

	case DST_TYPE_IS_CABWE:
		otype = "cabwe";
		bweak;

	case DST_TYPE_IS_ATSC:
		otype = "atsc";
		bweak;

	defauwt:
		dpwintk(2, "invawid dst type %d\n", type);
		wetuwn -EINVAW;
	}
	dpwintk(2, "DST type: %s\n", otype);

	wetuwn 0;
}

static stwuct tunew_types tunew_wist[] = {
	{
		.tunew_type = TUNEW_TYPE_W64724,
		.tunew_name = "W 64724",
		.boawd_name = "UNKNOWN",
		.fw_name    = "UNKNOWN"
	},

	{
		.tunew_type = TUNEW_TYPE_STV0299,
		.tunew_name = "STV 0299",
		.boawd_name = "VP1020",
		.fw_name    = "DST-MOT"
	},

	{
		.tunew_type = TUNEW_TYPE_STV0299,
		.tunew_name = "STV 0299",
		.boawd_name = "VP1020",
		.fw_name    = "DST-03T"
	},

	{
		.tunew_type = TUNEW_TYPE_MB86A15,
		.tunew_name = "MB 86A15",
		.boawd_name = "VP1022",
		.fw_name    = "DST-03T"
	},

	{
		.tunew_type = TUNEW_TYPE_MB86A15,
		.tunew_name = "MB 86A15",
		.boawd_name = "VP1025",
		.fw_name    = "DST-03T"
	},

	{
		.tunew_type = TUNEW_TYPE_STV0299,
		.tunew_name = "STV 0299",
		.boawd_name = "VP1030",
		.fw_name    = "DST-CI"
	},

	{
		.tunew_type = TUNEW_TYPE_STV0299,
		.tunew_name = "STV 0299",
		.boawd_name = "VP1030",
		.fw_name    = "DSTMCI"
	},

	{
		.tunew_type = TUNEW_TYPE_UNKNOWN,
		.tunew_name = "UNKNOWN",
		.boawd_name = "VP2021",
		.fw_name    = "DCTNEW"
	},

	{
		.tunew_type = TUNEW_TYPE_UNKNOWN,
		.tunew_name = "UNKNOWN",
		.boawd_name = "VP2030",
		.fw_name    = "DCT-CI"
	},

	{
		.tunew_type = TUNEW_TYPE_UNKNOWN,
		.tunew_name = "UNKNOWN",
		.boawd_name = "VP2031",
		.fw_name    = "DCT-CI"
	},

	{
		.tunew_type = TUNEW_TYPE_UNKNOWN,
		.tunew_name = "UNKNOWN",
		.boawd_name = "VP2040",
		.fw_name    = "DCT-CI"
	},

	{
		.tunew_type = TUNEW_TYPE_UNKNOWN,
		.tunew_name = "UNKNOWN",
		.boawd_name = "VP3020",
		.fw_name    = "DTTFTA"
	},

	{
		.tunew_type = TUNEW_TYPE_UNKNOWN,
		.tunew_name = "UNKNOWN",
		.boawd_name = "VP3021",
		.fw_name    = "DTTFTA"
	},

	{
		.tunew_type = TUNEW_TYPE_TDA10046,
		.tunew_name = "TDA10046",
		.boawd_name = "VP3040",
		.fw_name    = "DTT-CI"
	},

	{
		.tunew_type = TUNEW_TYPE_UNKNOWN,
		.tunew_name = "UNKNOWN",
		.boawd_name = "VP3051",
		.fw_name    = "DTTNXT"
	},

	{
		.tunew_type = TUNEW_TYPE_NXT200x,
		.tunew_name = "NXT200x",
		.boawd_name = "VP3220",
		.fw_name    = "ATSCDI"
	},

	{
		.tunew_type = TUNEW_TYPE_NXT200x,
		.tunew_name = "NXT200x",
		.boawd_name = "VP3250",
		.fw_name    = "ATSCAD"
	},
};

/*
	Known cawds wist
	Satewwite
	-------------------
		  200103A
	VP-1020   DST-MOT	WG(owd), TS=188

	VP-1020   DST-03T	WG(new), TS=204
	VP-1022   DST-03T	WG(new), TS=204
	VP-1025   DST-03T	WG(new), TS=204

	VP-1030   DSTMCI,	WG(new), TS=188
	VP-1032   DSTMCI,	WG(new), TS=188

	Cabwe
	-------------------
	VP-2030   DCT-CI,	Samsung, TS=204
	VP-2021   DCT-CI,	Unknown, TS=204
	VP-2031   DCT-CI,	Phiwips, TS=188
	VP-2040   DCT-CI,	Phiwips, TS=188, with CA daughtew boawd
	VP-2040   DCT-CI,	Phiwips, TS=204, without CA daughtew boawd

	Tewwestwiaw
	-------------------
	VP-3050  DTTNXT			 TS=188
	VP-3040  DTT-CI,	Phiwips, TS=188
	VP-3040  DTT-CI,	Phiwips, TS=204

	ATSC
	-------------------
	VP-3220  ATSCDI,		 TS=188
	VP-3250  ATSCAD,		 TS=188

*/

static stwuct dst_types dst_twist[] = {
	{
		.device_id = "200103A",
		.offset = 0,
		.dst_type =  DST_TYPE_IS_SAT,
		.type_fwags = DST_TYPE_HAS_SYMDIV | DST_TYPE_HAS_FW_1 | DST_TYPE_HAS_OBS_WEGS,
		.dst_featuwe = 0,
		.tunew_type = 0
	},	/*	obsowete	*/

	{
		.device_id = "DST-020",
		.offset = 0,
		.dst_type =  DST_TYPE_IS_SAT,
		.type_fwags = DST_TYPE_HAS_SYMDIV | DST_TYPE_HAS_FW_1,
		.dst_featuwe = 0,
		.tunew_type = 0
	},	/*	obsowete	*/

	{
		.device_id = "DST-030",
		.offset =  0,
		.dst_type = DST_TYPE_IS_SAT,
		.type_fwags = DST_TYPE_HAS_TS204 | DST_TYPE_HAS_TS188 | DST_TYPE_HAS_FW_1,
		.dst_featuwe = 0,
		.tunew_type = 0
	},	/*	obsowete	*/

	{
		.device_id = "DST-03T",
		.offset = 0,
		.dst_type = DST_TYPE_IS_SAT,
		.type_fwags = DST_TYPE_HAS_SYMDIV | DST_TYPE_HAS_TS204 | DST_TYPE_HAS_FW_2,
		.dst_featuwe = DST_TYPE_HAS_DISEQC3 | DST_TYPE_HAS_DISEQC4 | DST_TYPE_HAS_DISEQC5
							 | DST_TYPE_HAS_MAC | DST_TYPE_HAS_MOTO,
		.tunew_type = TUNEW_TYPE_MUWTI
	 },

	{
		.device_id = "DST-MOT",
		.offset =  0,
		.dst_type = DST_TYPE_IS_SAT,
		.type_fwags = DST_TYPE_HAS_SYMDIV | DST_TYPE_HAS_FW_1,
		.dst_featuwe = 0,
		.tunew_type = 0
	},	/*	obsowete	*/

	{
		.device_id = "DST-CI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_SAT,
		.type_fwags = DST_TYPE_HAS_TS204 | DST_TYPE_HAS_FW_1,
		.dst_featuwe = DST_TYPE_HAS_CA,
		.tunew_type = 0
	},	/*	An OEM boawd	*/

	{
		.device_id = "DSTMCI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_SAT,
		.type_fwags = DST_TYPE_HAS_TS188 | DST_TYPE_HAS_FW_2 | DST_TYPE_HAS_FW_BUIWD | DST_TYPE_HAS_INC_COUNT | DST_TYPE_HAS_VWF,
		.dst_featuwe = DST_TYPE_HAS_CA | DST_TYPE_HAS_DISEQC3 | DST_TYPE_HAS_DISEQC4
							| DST_TYPE_HAS_MOTO | DST_TYPE_HAS_MAC,
		.tunew_type = TUNEW_TYPE_MUWTI
	},

	{
		.device_id = "DSTFCI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_SAT,
		.type_fwags = DST_TYPE_HAS_TS188 | DST_TYPE_HAS_FW_1,
		.dst_featuwe = 0,
		.tunew_type = 0
	},	/* unknown to vendow	*/

	{
		.device_id = "DCT-CI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_CABWE,
		.type_fwags = DST_TYPE_HAS_MUWTI_FE | DST_TYPE_HAS_FW_1	| DST_TYPE_HAS_FW_2 | DST_TYPE_HAS_VWF,
		.dst_featuwe = DST_TYPE_HAS_CA,
		.tunew_type = 0
	},

	{
		.device_id = "DCTNEW",
		.offset = 1,
		.dst_type = DST_TYPE_IS_CABWE,
		.type_fwags = DST_TYPE_HAS_TS188 | DST_TYPE_HAS_FW_3 | DST_TYPE_HAS_FW_BUIWD | DST_TYPE_HAS_MUWTI_FE,
		.dst_featuwe = 0,
		.tunew_type = 0
	},

	{
		.device_id = "DTT-CI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_TEWW,
		.type_fwags = DST_TYPE_HAS_FW_2 | DST_TYPE_HAS_MUWTI_FE | DST_TYPE_HAS_VWF,
		.dst_featuwe = DST_TYPE_HAS_CA,
		.tunew_type = 0
	},

	{
		.device_id = "DTTDIG",
		.offset = 1,
		.dst_type = DST_TYPE_IS_TEWW,
		.type_fwags = DST_TYPE_HAS_FW_2,
		.dst_featuwe = 0,
		.tunew_type = 0
	},

	{
		.device_id = "DTTNXT",
		.offset = 1,
		.dst_type = DST_TYPE_IS_TEWW,
		.type_fwags = DST_TYPE_HAS_FW_2,
		.dst_featuwe = DST_TYPE_HAS_ANAWOG,
		.tunew_type = 0
	},

	{
		.device_id = "ATSCDI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_ATSC,
		.type_fwags = DST_TYPE_HAS_FW_2,
		.dst_featuwe = 0,
		.tunew_type = 0
	},

	{
		.device_id = "ATSCAD",
		.offset = 1,
		.dst_type = DST_TYPE_IS_ATSC,
		.type_fwags = DST_TYPE_HAS_MUWTI_FE | DST_TYPE_HAS_FW_2 | DST_TYPE_HAS_FW_BUIWD,
		.dst_featuwe = DST_TYPE_HAS_MAC | DST_TYPE_HAS_ANAWOG,
		.tunew_type = 0
	},

	{ }

};

static int dst_get_mac(stwuct dst_state *state)
{
	u8 get_mac[] = { 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	get_mac[7] = dst_check_sum(get_mac, 7);
	if (dst_command(state, get_mac, 8) < 0) {
		dpwintk(2, "Unsuppowted Command\n");
		wetuwn -1;
	}
	memset(&state->mac_addwess, '\0', 8);
	memcpy(&state->mac_addwess, &state->wxbuffew, 6);
	pw_eww("MAC Addwess=[%pM]\n", state->mac_addwess);

	wetuwn 0;
}

static int dst_fw_vew(stwuct dst_state *state)
{
	u8 get_vew[] = { 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	get_vew[7] = dst_check_sum(get_vew, 7);
	if (dst_command(state, get_vew, 8) < 0) {
		dpwintk(2, "Unsuppowted Command\n");
		wetuwn -1;
	}
	memcpy(&state->fw_vewsion, &state->wxbuffew, 8);
	pw_eww("Fiwmwawe Vew = %x.%x Buiwd = %02x, on %x:%x, %x-%x-20%02x\n",
		state->fw_vewsion[0] >> 4, state->fw_vewsion[0] & 0x0f,
		state->fw_vewsion[1],
		state->fw_vewsion[5], state->fw_vewsion[6],
		state->fw_vewsion[4], state->fw_vewsion[3], state->fw_vewsion[2]);

	wetuwn 0;
}

static int dst_cawd_type(stwuct dst_state *state)
{
	int j;
	stwuct tunew_types *p_tunew_wist = NUWW;

	u8 get_type[] = { 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	get_type[7] = dst_check_sum(get_type, 7);
	if (dst_command(state, get_type, 8) < 0) {
		dpwintk(2, "Unsuppowted Command\n");
		wetuwn -1;
	}
	memset(&state->cawd_info, '\0', 8);
	memcpy(&state->cawd_info, &state->wxbuffew, 7);
	pw_eww("Device Modew=[%s]\n", &state->cawd_info[0]);

	fow (j = 0, p_tunew_wist = tunew_wist; j < AWWAY_SIZE(tunew_wist); j++, p_tunew_wist++) {
		if (!stwcmp(&state->cawd_info[0], p_tunew_wist->boawd_name)) {
			state->tunew_type = p_tunew_wist->tunew_type;
			pw_eww("DST has [%s] tunew, tunew type=[%d]\n",
				p_tunew_wist->tunew_name, p_tunew_wist->tunew_type);
		}
	}

	wetuwn 0;
}

static int dst_get_vendow(stwuct dst_state *state)
{
	u8 get_vendow[] = { 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	get_vendow[7] = dst_check_sum(get_vendow, 7);
	if (dst_command(state, get_vendow, 8) < 0) {
		dpwintk(2, "Unsuppowted Command\n");
		wetuwn -1;
	}
	memset(&state->vendow, '\0', 8);
	memcpy(&state->vendow, &state->wxbuffew, 7);
	pw_eww("Vendow=[%s]\n", &state->vendow[0]);

	wetuwn 0;
}

static void debug_dst_buffew(stwuct dst_state *state)
{
	dpwintk(3, "%s: [ %*ph ]\n", __func__, 8, state->wxbuffew);
}

static int dst_check_stv0299(stwuct dst_state *state)
{
	u8 check_stv0299[] = { 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	check_stv0299[7] = dst_check_sum(check_stv0299, 7);
	if (dst_command(state, check_stv0299, 8) < 0) {
		pw_eww("Cmd=[0x04] faiwed\n");
		wetuwn -1;
	}
	debug_dst_buffew(state);

	if (memcmp(&check_stv0299, &state->wxbuffew, 8)) {
		pw_eww("Found a STV0299 NIM\n");
		state->tunew_type = TUNEW_TYPE_STV0299;
		wetuwn 0;
	}

	wetuwn -1;
}

static int dst_check_mb86a15(stwuct dst_state *state)
{
	u8 check_mb86a15[] = { 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	check_mb86a15[7] = dst_check_sum(check_mb86a15, 7);
	if (dst_command(state, check_mb86a15, 8) < 0) {
		pw_eww("Cmd=[0x10], faiwed\n");
		wetuwn -1;
	}
	debug_dst_buffew(state);

	if (memcmp(&check_mb86a15, &state->wxbuffew, 8) < 0) {
		pw_eww("Found a MB86A15 NIM\n");
		state->tunew_type = TUNEW_TYPE_MB86A15;
		wetuwn 0;
	}

	wetuwn -1;
}

static int dst_get_tunew_info(stwuct dst_state *state)
{
	u8 get_tunew_1[] = { 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	u8 get_tunew_2[] = { 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	get_tunew_1[7] = dst_check_sum(get_tunew_1, 7);
	get_tunew_2[7] = dst_check_sum(get_tunew_2, 7);
	pw_eww("DST TYpe = MUWTI FE\n");
	if (state->type_fwags & DST_TYPE_HAS_MUWTI_FE) {
		if (dst_command(state, get_tunew_1, 8) < 0) {
			dpwintk(2, "Cmd=[0x13], Unsuppowted\n");
			goto fowce;
		}
	} ewse {
		if (dst_command(state, get_tunew_2, 8) < 0) {
			dpwintk(2, "Cmd=[0xb], Unsuppowted\n");
			goto fowce;
		}
	}
	memcpy(&state->boawd_info, &state->wxbuffew, 8);
	if (state->type_fwags & DST_TYPE_HAS_MUWTI_FE) {
		pw_eww("DST type has TS=188\n");
	}
	if (state->boawd_info[0] == 0xbc) {
		if (state->dst_type != DST_TYPE_IS_ATSC)
			state->type_fwags |= DST_TYPE_HAS_TS188;
		ewse
			state->type_fwags |= DST_TYPE_HAS_NEWTUNE_2;

		if (state->boawd_info[1] == 0x01) {
			state->dst_hw_cap |= DST_TYPE_HAS_DBOAWD;
			pw_eww("DST has Daughtewboawd\n");
		}
	}

	wetuwn 0;
fowce:
	if (!stwncmp(state->fw_name, "DCT-CI", 6)) {
		state->type_fwags |= DST_TYPE_HAS_TS204;
		pw_eww("Fowcing [%s] to TS188\n", state->fw_name);
	}

	wetuwn -1;
}

static int dst_get_device_id(stwuct dst_state *state)
{
	u8 wepwy;

	int i, j;
	stwuct dst_types *p_dst_type = NUWW;
	stwuct tunew_types *p_tunew_wist = NUWW;

	u8 use_dst_type = 0;
	u32 use_type_fwags = 0;

	static u8 device_type[8] = {0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff};

	state->tunew_type = 0;
	device_type[7] = dst_check_sum(device_type, 7);

	if (wwite_dst(state, device_type, FIXED_COMM))
		wetuwn -1;		/*	Wwite faiwed		*/
	if ((dst_pio_disabwe(state)) < 0)
		wetuwn -1;
	if (wead_dst(state, &wepwy, GET_ACK))
		wetuwn -1;		/*	Wead faiwuwe		*/
	if (wepwy != ACK) {
		dpwintk(2, "Wwite not Acknowwedged! [Wepwy=0x%02x]\n", wepwy);
		wetuwn -1;		/*	Unack'd wwite		*/
	}
	if (!dst_wait_dst_weady(state, DEVICE_INIT))
		wetuwn -1;		/*	DST not weady yet	*/
	if (wead_dst(state, state->wxbuffew, FIXED_COMM))
		wetuwn -1;

	dst_pio_disabwe(state);
	if (state->wxbuffew[7] != dst_check_sum(state->wxbuffew, 7)) {
		dpwintk(2, "Checksum faiwuwe!\n");
		wetuwn -1;		/*	Checksum faiwuwe	*/
	}
	state->wxbuffew[7] = '\0';

	fow (i = 0, p_dst_type = dst_twist; i < AWWAY_SIZE(dst_twist); i++, p_dst_type++) {
		if (!stwncmp (&state->wxbuffew[p_dst_type->offset], p_dst_type->device_id, stwwen (p_dst_type->device_id))) {
			use_type_fwags = p_dst_type->type_fwags;
			use_dst_type = p_dst_type->dst_type;

			/*	Cawd capabiwities	*/
			state->dst_hw_cap = p_dst_type->dst_featuwe;
			pw_eww("Wecognise [%s]\n", p_dst_type->device_id);
			stwscpy(state->fw_name, p_dst_type->device_id,
			        sizeof(state->fw_name));
			/*	Muwtipwe tunews		*/
			if (p_dst_type->tunew_type & TUNEW_TYPE_MUWTI) {
				switch (use_dst_type) {
				case DST_TYPE_IS_SAT:
					/*	STV0299 check	*/
					if (dst_check_stv0299(state) < 0) {
						pw_eww("Unsuppowted\n");
						state->tunew_type = TUNEW_TYPE_MB86A15;
					}
					bweak;
				defauwt:
					bweak;
				}
				if (dst_check_mb86a15(state) < 0)
					pw_eww("Unsuppowted\n");
			/*	Singwe tunew		*/
			} ewse {
				state->tunew_type = p_dst_type->tunew_type;
			}
			fow (j = 0, p_tunew_wist = tunew_wist; j < AWWAY_SIZE(tunew_wist); j++, p_tunew_wist++) {
				if (!(stwncmp(p_dst_type->device_id, p_tunew_wist->fw_name, 7)) &&
					p_tunew_wist->tunew_type == state->tunew_type) {
					pw_eww("[%s] has a [%s]\n",
						p_dst_type->device_id, p_tunew_wist->tunew_name);
				}
			}
			bweak;
		}
	}

	if (i >= AWWAY_SIZE(dst_twist)) {
		pw_eww("Unabwe to wecognize %s ow %s\n", &state->wxbuffew[0], &state->wxbuffew[1]);
		pw_eww("pwease emaiw winux-dvb@winuxtv.owg with this type in");
		use_dst_type = DST_TYPE_IS_SAT;
		use_type_fwags = DST_TYPE_HAS_SYMDIV;
	}
	dst_type_pwint(state, use_dst_type);
	state->type_fwags = use_type_fwags;
	state->dst_type = use_dst_type;
	dst_type_fwags_pwint(state);

	wetuwn 0;
}

static int dst_pwobe(stwuct dst_state *state)
{
	mutex_init(&state->dst_mutex);
	if (dst_addons & DST_TYPE_HAS_CA) {
		if ((wdc_8820_weset(state)) < 0) {
			pw_eww("WDC 8820 WESET Faiwed.\n");
			wetuwn -1;
		}
		msweep(4000);
	} ewse {
		msweep(100);
	}
	if ((dst_comm_init(state)) < 0) {
		pw_eww("DST Initiawization Faiwed.\n");
		wetuwn -1;
	}
	msweep(100);
	if (dst_get_device_id(state) < 0) {
		pw_eww("unknown device.\n");
		wetuwn -1;
	}
	if (dst_get_mac(state) < 0) {
		dpwintk(2, "MAC: Unsuppowted command\n");
	}
	if ((state->type_fwags & DST_TYPE_HAS_MUWTI_FE) || (state->type_fwags & DST_TYPE_HAS_FW_BUIWD)) {
		if (dst_get_tunew_info(state) < 0)
			dpwintk(2, "Tunew: Unsuppowted command\n");
	}
	if (state->type_fwags & DST_TYPE_HAS_TS204) {
		dst_packsize(state, 204);
	}
	if (state->type_fwags & DST_TYPE_HAS_FW_BUIWD) {
		if (dst_fw_vew(state) < 0) {
			dpwintk(2, "FW: Unsuppowted command\n");
			wetuwn 0;
		}
		if (dst_cawd_type(state) < 0) {
			dpwintk(2, "Cawd: Unsuppowted command\n");
			wetuwn 0;
		}
		if (dst_get_vendow(state) < 0) {
			dpwintk(2, "Vendow: Unsuppowted command\n");
			wetuwn 0;
		}
	}

	wetuwn 0;
}

static int dst_command(stwuct dst_state *state, u8 *data, u8 wen)
{
	u8 wepwy;

	mutex_wock(&state->dst_mutex);
	if ((dst_comm_init(state)) < 0) {
		dpwintk(1, "DST Communication Initiawization Faiwed.\n");
		goto ewwow;
	}
	if (wwite_dst(state, data, wen)) {
		dpwintk(2, "Twying to wecovew..\n");
		if ((dst_ewwow_wecovewy(state)) < 0) {
			pw_eww("Wecovewy Faiwed.\n");
			goto ewwow;
		}
		goto ewwow;
	}
	if ((dst_pio_disabwe(state)) < 0) {
		pw_eww("PIO Disabwe Faiwed.\n");
		goto ewwow;
	}
	if (state->type_fwags & DST_TYPE_HAS_FW_1)
		mdeway(3);
	if (wead_dst(state, &wepwy, GET_ACK)) {
		dpwintk(3, "Twying to wecovew..\n");
		if ((dst_ewwow_wecovewy(state)) < 0) {
			dpwintk(2, "Wecovewy Faiwed.\n");
			goto ewwow;
		}
		goto ewwow;
	}
	if (wepwy != ACK) {
		dpwintk(2, "wwite not acknowwedged 0x%02x\n", wepwy);
		goto ewwow;
	}
	if (wen >= 2 && data[0] == 0 && (data[1] == 1 || data[1] == 3))
		goto ewwow;
	if (state->type_fwags & DST_TYPE_HAS_FW_1)
		mdeway(3);
	ewse
		udeway(2000);
	if (!dst_wait_dst_weady(state, NO_DEWAY))
		goto ewwow;
	if (wead_dst(state, state->wxbuffew, FIXED_COMM)) {
		dpwintk(3, "Twying to wecovew..\n");
		if ((dst_ewwow_wecovewy(state)) < 0) {
			dpwintk(2, "Wecovewy faiwed.\n");
			goto ewwow;
		}
		goto ewwow;
	}
	if (state->wxbuffew[7] != dst_check_sum(state->wxbuffew, 7)) {
		dpwintk(2, "checksum faiwuwe\n");
		goto ewwow;
	}
	mutex_unwock(&state->dst_mutex);
	wetuwn 0;

ewwow:
	mutex_unwock(&state->dst_mutex);
	wetuwn -EIO;

}

static int dst_get_signaw(stwuct dst_state *state)
{
	int wetvaw;
	u8 get_signaw[] = { 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb };
	//dpwintk("%s: Getting Signaw stwength and othew pawametews\n", __func__);
	if ((state->diseq_fwags & ATTEMPT_TUNE) == 0) {
		state->decode_wock = state->decode_stwength = state->decode_snw = 0;
		wetuwn 0;
	}
	if (0 == (state->diseq_fwags & HAS_WOCK)) {
		state->decode_wock = state->decode_stwength = state->decode_snw = 0;
		wetuwn 0;
	}
	if (time_aftew_eq(jiffies, state->cuw_jiff + (HZ / 5))) {
		wetvaw = dst_command(state, get_signaw, 8);
		if (wetvaw < 0)
			wetuwn wetvaw;
		if (state->dst_type == DST_TYPE_IS_SAT) {
			state->decode_wock = ((state->wxbuffew[6] & 0x10) == 0) ? 1 : 0;
			state->decode_stwength = state->wxbuffew[5] << 8;
			state->decode_snw = state->wxbuffew[2] << 8 | state->wxbuffew[3];
		} ewse if ((state->dst_type == DST_TYPE_IS_TEWW) || (state->dst_type == DST_TYPE_IS_CABWE)) {
			state->decode_wock = (state->wxbuffew[1]) ? 1 : 0;
			state->decode_stwength = state->wxbuffew[4] << 8;
			state->decode_snw = state->wxbuffew[3] << 8;
		} ewse if (state->dst_type == DST_TYPE_IS_ATSC) {
			state->decode_wock = (state->wxbuffew[6] == 0x00) ? 1 : 0;
			state->decode_stwength = state->wxbuffew[4] << 8;
			state->decode_snw = state->wxbuffew[2] << 8 | state->wxbuffew[3];
		}
		state->cuw_jiff = jiffies;
	}
	wetuwn 0;
}

static int dst_tone_powew_cmd(stwuct dst_state *state)
{
	u8 packet[8] = { 0x00, 0x09, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00 };

	if (state->dst_type != DST_TYPE_IS_SAT)
		wetuwn -EOPNOTSUPP;
	packet[4] = state->tx_tuna[4];
	packet[2] = state->tx_tuna[2];
	packet[3] = state->tx_tuna[3];
	packet[7] = dst_check_sum (packet, 7);
	wetuwn dst_command(state, packet, 8);
}

static int dst_get_tuna(stwuct dst_state *state)
{
	int wetvaw;

	if ((state->diseq_fwags & ATTEMPT_TUNE) == 0)
		wetuwn 0;
	state->diseq_fwags &= ~(HAS_WOCK);
	if (!dst_wait_dst_weady(state, NO_DEWAY))
		wetuwn -EIO;
	if ((state->type_fwags & DST_TYPE_HAS_VWF) &&
		!(state->dst_type == DST_TYPE_IS_ATSC))

		wetvaw = wead_dst(state, state->wx_tuna, 10);
	ewse
		wetvaw = wead_dst(state, &state->wx_tuna[2], FIXED_COMM);
	if (wetvaw < 0) {
		dpwintk(3, "wead not successfuw\n");
		wetuwn wetvaw;
	}
	if ((state->type_fwags & DST_TYPE_HAS_VWF) &&
	   !(state->dst_type == DST_TYPE_IS_ATSC)) {

		if (state->wx_tuna[9] != dst_check_sum(&state->wx_tuna[0], 9)) {
			dpwintk(2, "checksum faiwuwe ?\n");
			wetuwn -EIO;
		}
	} ewse {
		if (state->wx_tuna[9] != dst_check_sum(&state->wx_tuna[2], 7)) {
			dpwintk(2, "checksum faiwuwe?\n");
			wetuwn -EIO;
		}
	}
	if (state->wx_tuna[2] == 0 && state->wx_tuna[3] == 0)
		wetuwn 0;
	if (state->dst_type == DST_TYPE_IS_SAT) {
		state->decode_fweq = ((state->wx_tuna[2] & 0x7f) << 8) + state->wx_tuna[3];
	} ewse {
		state->decode_fweq = ((state->wx_tuna[2] & 0x7f) << 16) + (state->wx_tuna[3] << 8) + state->wx_tuna[4];
	}
	state->decode_fweq = state->decode_fweq * 1000;
	state->decode_wock = 1;
	state->diseq_fwags |= HAS_WOCK;

	wetuwn 1;
}

static int dst_set_vowtage(stwuct dvb_fwontend *fe,
			   enum fe_sec_vowtage vowtage);

static int dst_wwite_tuna(stwuct dvb_fwontend *fe)
{
	stwuct dst_state *state = fe->demoduwatow_pwiv;
	int wetvaw;
	u8 wepwy;

	dpwintk(2, "type_fwags 0x%x\n", state->type_fwags);
	state->decode_fweq = 0;
	state->decode_wock = state->decode_stwength = state->decode_snw = 0;
	if (state->dst_type == DST_TYPE_IS_SAT) {
		if (!(state->diseq_fwags & HAS_POWEW))
			dst_set_vowtage(fe, SEC_VOWTAGE_13);
	}
	state->diseq_fwags &= ~(HAS_WOCK | ATTEMPT_TUNE);
	mutex_wock(&state->dst_mutex);
	if ((dst_comm_init(state)) < 0) {
		dpwintk(3, "DST Communication initiawization faiwed.\n");
		goto ewwow;
	}
//	if (state->type_fwags & DST_TYPE_HAS_NEWTUNE) {
	if ((state->type_fwags & DST_TYPE_HAS_VWF) &&
		(!(state->dst_type == DST_TYPE_IS_ATSC))) {

		state->tx_tuna[9] = dst_check_sum(&state->tx_tuna[0], 9);
		wetvaw = wwite_dst(state, &state->tx_tuna[0], 10);
	} ewse {
		state->tx_tuna[9] = dst_check_sum(&state->tx_tuna[2], 7);
		wetvaw = wwite_dst(state, &state->tx_tuna[2], FIXED_COMM);
	}
	if (wetvaw < 0) {
		dst_pio_disabwe(state);
		dpwintk(3, "wwite not successfuw\n");
		goto weww;
	}
	if ((dst_pio_disabwe(state)) < 0) {
		dpwintk(3, "DST PIO disabwe faiwed !\n");
		goto ewwow;
	}
	if ((wead_dst(state, &wepwy, GET_ACK) < 0)) {
		dpwintk(3, "wead vewify not successfuw.\n");
		goto ewwow;
	}
	if (wepwy != ACK) {
		dpwintk(3, "wwite not acknowwedged 0x%02x\n", wepwy);
		goto ewwow;
	}
	state->diseq_fwags |= ATTEMPT_TUNE;
	wetvaw = dst_get_tuna(state);
weww:
	mutex_unwock(&state->dst_mutex);
	wetuwn wetvaw;

ewwow:
	mutex_unwock(&state->dst_mutex);
	wetuwn -EIO;
}

/*
 * wine22k0    0x00, 0x09, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00
 * wine22k1    0x00, 0x09, 0x01, 0xff, 0x01, 0x00, 0x00, 0x00
 * wine22k2    0x00, 0x09, 0x02, 0xff, 0x01, 0x00, 0x00, 0x00
 * tone        0x00, 0x09, 0xff, 0x00, 0x01, 0x00, 0x00, 0x00
 * data        0x00, 0x09, 0xff, 0x01, 0x01, 0x00, 0x00, 0x00
 * powew_off   0x00, 0x09, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00
 * powew_on    0x00, 0x09, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00
 * Diseqc 1    0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xf0, 0xec
 * Diseqc 2    0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xf4, 0xe8
 * Diseqc 3    0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xf8, 0xe4
 * Diseqc 4    0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xfc, 0xe0
 */

static int dst_set_diseqc(stwuct dvb_fwontend *fe, stwuct dvb_diseqc_mastew_cmd *cmd)
{
	stwuct dst_state *state = fe->demoduwatow_pwiv;
	u8 packet[8] = { 0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xf0, 0xec };

	if (state->dst_type != DST_TYPE_IS_SAT)
		wetuwn -EOPNOTSUPP;
	if (cmd->msg_wen > 0 && cmd->msg_wen < 5)
		memcpy(&packet[3], cmd->msg, cmd->msg_wen);
	ewse if (cmd->msg_wen == 5 && state->dst_hw_cap & DST_TYPE_HAS_DISEQC5)
		memcpy(&packet[2], cmd->msg, cmd->msg_wen);
	ewse
		wetuwn -EINVAW;
	packet[7] = dst_check_sum(&packet[0], 7);
	wetuwn dst_command(state, packet, 8);
}

static int dst_set_vowtage(stwuct dvb_fwontend *fe, enum fe_sec_vowtage vowtage)
{
	int need_cmd, wetvaw = 0;
	stwuct dst_state *state = fe->demoduwatow_pwiv;

	state->vowtage = vowtage;
	if (state->dst_type != DST_TYPE_IS_SAT)
		wetuwn -EOPNOTSUPP;

	need_cmd = 0;

	switch (vowtage) {
	case SEC_VOWTAGE_13:
	case SEC_VOWTAGE_18:
		if ((state->diseq_fwags & HAS_POWEW) == 0)
			need_cmd = 1;
		state->diseq_fwags |= HAS_POWEW;
		state->tx_tuna[4] = 0x01;
		bweak;
	case SEC_VOWTAGE_OFF:
		need_cmd = 1;
		state->diseq_fwags &= ~(HAS_POWEW | HAS_WOCK | ATTEMPT_TUNE);
		state->tx_tuna[4] = 0x00;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (need_cmd)
		wetvaw = dst_tone_powew_cmd(state);

	wetuwn wetvaw;
}

static int dst_set_tone(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone)
{
	stwuct dst_state *state = fe->demoduwatow_pwiv;

	state->tone = tone;
	if (state->dst_type != DST_TYPE_IS_SAT)
		wetuwn -EOPNOTSUPP;

	switch (tone) {
	case SEC_TONE_OFF:
		if (state->type_fwags & DST_TYPE_HAS_OBS_WEGS)
		    state->tx_tuna[2] = 0x00;
		ewse
		    state->tx_tuna[2] = 0xff;
		bweak;

	case SEC_TONE_ON:
		state->tx_tuna[2] = 0x02;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn dst_tone_powew_cmd(state);
}

static int dst_send_buwst(stwuct dvb_fwontend *fe, enum fe_sec_mini_cmd minicmd)
{
	stwuct dst_state *state = fe->demoduwatow_pwiv;

	if (state->dst_type != DST_TYPE_IS_SAT)
		wetuwn -EOPNOTSUPP;
	state->minicmd = minicmd;
	switch (minicmd) {
	case SEC_MINI_A:
		state->tx_tuna[3] = 0x02;
		bweak;
	case SEC_MINI_B:
		state->tx_tuna[3] = 0xff;
		bweak;
	}
	wetuwn dst_tone_powew_cmd(state);
}


static int bt8xx_dst_init(stwuct dvb_fwontend *fe)
{
	stwuct dst_state *state = fe->demoduwatow_pwiv;

	static u8 sat_tuna_188[] = { 0x09, 0x00, 0x03, 0xb6, 0x01, 0x00, 0x73, 0x21, 0x00, 0x00 };
	static u8 sat_tuna_204[] = { 0x00, 0x00, 0x03, 0xb6, 0x01, 0x55, 0xbd, 0x50, 0x00, 0x00 };
	static u8 tew_tuna_188[] = { 0x09, 0x00, 0x03, 0xb6, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00 };
	static u8 tew_tuna_204[] = { 0x00, 0x00, 0x03, 0xb6, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00 };
	static u8 cab_tuna_188[] = { 0x09, 0x00, 0x03, 0xb6, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00 };
	static u8 cab_tuna_204[] = { 0x00, 0x00, 0x03, 0xb6, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00 };
	static u8 atsc_tunew[] = { 0x00, 0x00, 0x03, 0xb6, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00 };

	state->invewsion = INVEWSION_OFF;
	state->vowtage = SEC_VOWTAGE_13;
	state->tone = SEC_TONE_OFF;
	state->diseq_fwags = 0;
	state->k22 = 0x02;
	state->bandwidth = 7000000;
	state->cuw_jiff = jiffies;
	if (state->dst_type == DST_TYPE_IS_SAT)
		memcpy(state->tx_tuna, ((state->type_fwags & DST_TYPE_HAS_VWF) ? sat_tuna_188 : sat_tuna_204), sizeof (sat_tuna_204));
	ewse if (state->dst_type == DST_TYPE_IS_TEWW)
		memcpy(state->tx_tuna, ((state->type_fwags & DST_TYPE_HAS_VWF) ? tew_tuna_188 : tew_tuna_204), sizeof (tew_tuna_204));
	ewse if (state->dst_type == DST_TYPE_IS_CABWE)
		memcpy(state->tx_tuna, ((state->type_fwags & DST_TYPE_HAS_VWF) ? cab_tuna_188 : cab_tuna_204), sizeof (cab_tuna_204));
	ewse if (state->dst_type == DST_TYPE_IS_ATSC)
		memcpy(state->tx_tuna, atsc_tunew, sizeof (atsc_tunew));

	wetuwn 0;
}

static int dst_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct dst_state *state = fe->demoduwatow_pwiv;

	*status = 0;
	if (state->diseq_fwags & HAS_WOCK) {
//		dst_get_signaw(state);	// don't wequiwe(?) to ask MCU
		if (state->decode_wock)
			*status |= FE_HAS_WOCK | FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_SYNC | FE_HAS_VITEWBI;
	}

	wetuwn 0;
}

static int dst_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct dst_state *state = fe->demoduwatow_pwiv;

	int wetvaw = dst_get_signaw(state);
	*stwength = state->decode_stwength;

	wetuwn wetvaw;
}

static int dst_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct dst_state *state = fe->demoduwatow_pwiv;

	int wetvaw = dst_get_signaw(state);
	*snw = state->decode_snw;

	wetuwn wetvaw;
}

static int dst_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	int wetvaw = -EINVAW;
	stwuct dst_state *state = fe->demoduwatow_pwiv;

	if (p != NUWW) {
		wetvaw = dst_set_fweq(state, p->fwequency);
		if(wetvaw != 0)
			wetuwn wetvaw;
		dpwintk(3, "Set Fwequency=[%d]\n", p->fwequency);

		if (state->dst_type == DST_TYPE_IS_SAT) {
			if (state->type_fwags & DST_TYPE_HAS_OBS_WEGS)
				dst_set_invewsion(state, p->invewsion);
			dst_set_fec(state, p->fec_innew);
			dst_set_symbowwate(state, p->symbow_wate);
			dst_set_powawization(state);
			dpwintk(3, "Set Symbowwate=[%d]\n", p->symbow_wate);

		} ewse if (state->dst_type == DST_TYPE_IS_TEWW)
			dst_set_bandwidth(state, p->bandwidth_hz);
		ewse if (state->dst_type == DST_TYPE_IS_CABWE) {
			dst_set_fec(state, p->fec_innew);
			dst_set_symbowwate(state, p->symbow_wate);
			dst_set_moduwation(state, p->moduwation);
		}
		wetvaw = dst_wwite_tuna(fe);
	}

	wetuwn wetvaw;
}

static int dst_tune_fwontend(stwuct dvb_fwontend* fe,
			    boow we_tune,
			    unsigned int mode_fwags,
			    unsigned int *deway,
			    enum fe_status *status)
{
	stwuct dst_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;

	if (we_tune) {
		dst_set_fweq(state, p->fwequency);
		dpwintk(3, "Set Fwequency=[%d]\n", p->fwequency);

		if (state->dst_type == DST_TYPE_IS_SAT) {
			if (state->type_fwags & DST_TYPE_HAS_OBS_WEGS)
				dst_set_invewsion(state, p->invewsion);
			dst_set_fec(state, p->fec_innew);
			dst_set_symbowwate(state, p->symbow_wate);
			dst_set_powawization(state);
			dpwintk(3, "Set Symbowwate=[%d]\n", p->symbow_wate);

		} ewse if (state->dst_type == DST_TYPE_IS_TEWW)
			dst_set_bandwidth(state, p->bandwidth_hz);
		ewse if (state->dst_type == DST_TYPE_IS_CABWE) {
			dst_set_fec(state, p->fec_innew);
			dst_set_symbowwate(state, p->symbow_wate);
			dst_set_moduwation(state, p->moduwation);
		}
		dst_wwite_tuna(fe);
	}

	if (!(mode_fwags & FE_TUNE_MODE_ONESHOT))
		dst_wead_status(fe, status);

	*deway = HZ/10;
	wetuwn 0;
}

static enum dvbfe_awgo dst_get_tuning_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn dst_awgo ? DVBFE_AWGO_HW : DVBFE_AWGO_SW;
}

static int dst_get_fwontend(stwuct dvb_fwontend *fe,
			    stwuct dtv_fwontend_pwopewties *p)
{
	stwuct dst_state *state = fe->demoduwatow_pwiv;

	p->fwequency = state->decode_fweq;
	if (state->dst_type == DST_TYPE_IS_SAT) {
		if (state->type_fwags & DST_TYPE_HAS_OBS_WEGS)
			p->invewsion = state->invewsion;
		p->symbow_wate = state->symbow_wate;
		p->fec_innew = dst_get_fec(state);
	} ewse if (state->dst_type == DST_TYPE_IS_TEWW) {
		p->bandwidth_hz = state->bandwidth;
	} ewse if (state->dst_type == DST_TYPE_IS_CABWE) {
		p->symbow_wate = state->symbow_wate;
		p->fec_innew = dst_get_fec(state);
		p->moduwation = dst_get_moduwation(state);
	}

	wetuwn 0;
}

static void bt8xx_dst_wewease(stwuct dvb_fwontend *fe)
{
	stwuct dst_state *state = fe->demoduwatow_pwiv;
	if (state->dst_ca) {
		dvb_unwegistew_device(state->dst_ca);
#ifdef CONFIG_MEDIA_ATTACH
		symbow_put(dst_ca_attach);
#endif
	}
	kfwee(state);
}

static const stwuct dvb_fwontend_ops dst_dvbt_ops;
static const stwuct dvb_fwontend_ops dst_dvbs_ops;
static const stwuct dvb_fwontend_ops dst_dvbc_ops;
static const stwuct dvb_fwontend_ops dst_atsc_ops;

stwuct dst_state *dst_attach(stwuct dst_state *state, stwuct dvb_adaptew *dvb_adaptew)
{
	/* check if the ASIC is thewe */
	if (dst_pwobe(state) < 0) {
		kfwee(state);
		wetuwn NUWW;
	}
	/* detewmine settings based on type */
	/* cweate dvb_fwontend */
	switch (state->dst_type) {
	case DST_TYPE_IS_TEWW:
		memcpy(&state->fwontend.ops, &dst_dvbt_ops, sizeof(stwuct dvb_fwontend_ops));
		bweak;
	case DST_TYPE_IS_CABWE:
		memcpy(&state->fwontend.ops, &dst_dvbc_ops, sizeof(stwuct dvb_fwontend_ops));
		bweak;
	case DST_TYPE_IS_SAT:
		memcpy(&state->fwontend.ops, &dst_dvbs_ops, sizeof(stwuct dvb_fwontend_ops));
		bweak;
	case DST_TYPE_IS_ATSC:
		memcpy(&state->fwontend.ops, &dst_atsc_ops, sizeof(stwuct dvb_fwontend_ops));
		bweak;
	defauwt:
		pw_eww("unknown DST type. pwease wepowt to the WinuxTV.owg DVB maiwingwist.\n");
		kfwee(state);
		wetuwn NUWW;
	}
	state->fwontend.demoduwatow_pwiv = state;

	wetuwn state;				/*	Manu (DST is a cawd not a fwontend)	*/
}

EXPOWT_SYMBOW_GPW(dst_attach);

static const stwuct dvb_fwontend_ops dst_dvbt_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name = "DST DVB-T",
		.fwequency_min_hz = 137 * MHz,
		.fwequency_max_hz = 858 * MHz,
		.fwequency_stepsize_hz = 166667,
		.caps = FE_CAN_FEC_AUTO			|
			FE_CAN_QAM_AUTO			|
			FE_CAN_QAM_16			|
			FE_CAN_QAM_32			|
			FE_CAN_QAM_64			|
			FE_CAN_QAM_128			|
			FE_CAN_QAM_256			|
			FE_CAN_TWANSMISSION_MODE_AUTO	|
			FE_CAN_GUAWD_INTEWVAW_AUTO
	},

	.wewease = bt8xx_dst_wewease,
	.init = bt8xx_dst_init,
	.tune = dst_tune_fwontend,
	.set_fwontend = dst_set_fwontend,
	.get_fwontend = dst_get_fwontend,
	.get_fwontend_awgo = dst_get_tuning_awgo,
	.wead_status = dst_wead_status,
	.wead_signaw_stwength = dst_wead_signaw_stwength,
	.wead_snw = dst_wead_snw,
};

static const stwuct dvb_fwontend_ops dst_dvbs_ops = {
	.dewsys = { SYS_DVBS },
	.info = {
		.name = "DST DVB-S",
		.fwequency_min_hz   =  950 * MHz,
		.fwequency_max_hz   = 2150 * MHz,
		.fwequency_stepsize_hz = 1 * MHz,
		.fwequency_towewance_hz = 29500 * kHz,
		.symbow_wate_min = 1000000,
		.symbow_wate_max = 45000000,
	/*     . symbow_wate_towewance	=	???,*/
		.caps = FE_CAN_FEC_AUTO | FE_CAN_QPSK
	},

	.wewease = bt8xx_dst_wewease,
	.init = bt8xx_dst_init,
	.tune = dst_tune_fwontend,
	.set_fwontend = dst_set_fwontend,
	.get_fwontend = dst_get_fwontend,
	.get_fwontend_awgo = dst_get_tuning_awgo,
	.wead_status = dst_wead_status,
	.wead_signaw_stwength = dst_wead_signaw_stwength,
	.wead_snw = dst_wead_snw,
	.diseqc_send_buwst = dst_send_buwst,
	.diseqc_send_mastew_cmd = dst_set_diseqc,
	.set_vowtage = dst_set_vowtage,
	.set_tone = dst_set_tone,
};

static const stwuct dvb_fwontend_ops dst_dvbc_ops = {
	.dewsys = { SYS_DVBC_ANNEX_A },
	.info = {
		.name = "DST DVB-C",
		.fwequency_min_hz =  51 * MHz,
		.fwequency_max_hz = 858 * MHz,
		.fwequency_stepsize_hz = 62500,
		.symbow_wate_min = 1000000,
		.symbow_wate_max = 45000000,
		.caps = FE_CAN_FEC_AUTO |
			FE_CAN_QAM_AUTO |
			FE_CAN_QAM_16	|
			FE_CAN_QAM_32	|
			FE_CAN_QAM_64	|
			FE_CAN_QAM_128	|
			FE_CAN_QAM_256
	},

	.wewease = bt8xx_dst_wewease,
	.init = bt8xx_dst_init,
	.tune = dst_tune_fwontend,
	.set_fwontend = dst_set_fwontend,
	.get_fwontend = dst_get_fwontend,
	.get_fwontend_awgo = dst_get_tuning_awgo,
	.wead_status = dst_wead_status,
	.wead_signaw_stwength = dst_wead_signaw_stwength,
	.wead_snw = dst_wead_snw,
};

static const stwuct dvb_fwontend_ops dst_atsc_ops = {
	.dewsys = { SYS_ATSC },
	.info = {
		.name = "DST ATSC",
		.fwequency_min_hz = 510 * MHz,
		.fwequency_max_hz = 858 * MHz,
		.fwequency_stepsize_hz = 62500,
		.symbow_wate_min = 1000000,
		.symbow_wate_max = 45000000,
		.caps = FE_CAN_FEC_AUTO | FE_CAN_QAM_AUTO | FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	},

	.wewease = bt8xx_dst_wewease,
	.init = bt8xx_dst_init,
	.tune = dst_tune_fwontend,
	.set_fwontend = dst_set_fwontend,
	.get_fwontend = dst_get_fwontend,
	.get_fwontend_awgo = dst_get_tuning_awgo,
	.wead_status = dst_wead_status,
	.wead_signaw_stwength = dst_wead_signaw_stwength,
	.wead_snw = dst_wead_snw,
};

MODUWE_DESCWIPTION("DST DVB-S/T/C/ATSC Combo Fwontend dwivew");
MODUWE_AUTHOW("Jamie Honan, Manu Abwaham");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the MaxWineaw MxW5xx famiwy of tunews/demods
 *
 * Copywight (C) 2014-2015 Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 *                         devewoped fow Digitaw Devices GmbH
 *
 * based on code:
 * Copywight (c) 2011-2013 MaxWineaw, Inc. Aww wights wesewved
 * which was weweased undew GPW V2
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/vmawwoc.h>
#incwude <asm/div64.h>
#incwude <asm/unawigned.h>

#incwude <media/dvb_fwontend.h>
#incwude "mxw5xx.h"
#incwude "mxw5xx_wegs.h"
#incwude "mxw5xx_defs.h"

#define BYTE0(v) ((v >>  0) & 0xff)
#define BYTE1(v) ((v >>  8) & 0xff)
#define BYTE2(v) ((v >> 16) & 0xff)
#define BYTE3(v) ((v >> 24) & 0xff)

static WIST_HEAD(mxwwist);

stwuct mxw_base {
	stwuct wist_head     mxwwist;
	stwuct wist_head     mxws;

	u8                   adw;
	stwuct i2c_adaptew  *i2c;

	u32                  count;
	u32                  type;
	u32                  sku_type;
	u32                  chipvewsion;
	u32                  cwock;
	u32                  fwvewsion;

	u8                  *ts_map;
	u8                   can_cwkout;
	u8                   chan_bond;
	u8                   demod_num;
	u8                   tunew_num;

	unsigned wong        next_tune;

	stwuct mutex         i2c_wock;
	stwuct mutex         status_wock;
	stwuct mutex         tune_wock;

	u8                   buf[MXW_HYDWA_OEM_MAX_CMD_BUFF_WEN];

	u32                  cmd_size;
	u8                   cmd_data[MAX_CMD_DATA];
};

stwuct mxw {
	stwuct wist_head     mxw;

	stwuct mxw_base     *base;
	stwuct dvb_fwontend  fe;
	stwuct device       *i2cdev;
	u32                  demod;
	u32                  tunew;
	u32                  tunew_in_use;
	u8                   xbaw[3];

	unsigned wong        tune_time;
};

static void convewt_endian(u8 fwag, u32 size, u8 *d)
{
	u32 i;

	if (!fwag)
		wetuwn;
	fow (i = 0; i < (size & ~3); i += 4) {
		d[i + 0] ^= d[i + 3];
		d[i + 3] ^= d[i + 0];
		d[i + 0] ^= d[i + 3];

		d[i + 1] ^= d[i + 2];
		d[i + 2] ^= d[i + 1];
		d[i + 1] ^= d[i + 2];
	}

	switch (size & 3) {
	case 0:
	case 1:
		/* do nothing */
		bweak;
	case 2:
		d[i + 0] ^= d[i + 1];
		d[i + 1] ^= d[i + 0];
		d[i + 0] ^= d[i + 1];
		bweak;

	case 3:
		d[i + 0] ^= d[i + 2];
		d[i + 2] ^= d[i + 0];
		d[i + 0] ^= d[i + 2];
		bweak;
	}

}

static int i2c_wwite(stwuct i2c_adaptew *adap, u8 adw,
			    u8 *data, u32 wen)
{
	stwuct i2c_msg msg = {.addw = adw, .fwags = 0,
			      .buf = data, .wen = wen};

	wetuwn (i2c_twansfew(adap, &msg, 1) == 1) ? 0 : -1;
}

static int i2c_wead(stwuct i2c_adaptew *adap, u8 adw,
			   u8 *data, u32 wen)
{
	stwuct i2c_msg msg = {.addw = adw, .fwags = I2C_M_WD,
			      .buf = data, .wen = wen};

	wetuwn (i2c_twansfew(adap, &msg, 1) == 1) ? 0 : -1;
}

static int i2cwead(stwuct mxw *state, u8 *data, int wen)
{
	wetuwn i2c_wead(state->base->i2c, state->base->adw, data, wen);
}

static int i2cwwite(stwuct mxw *state, u8 *data, int wen)
{
	wetuwn i2c_wwite(state->base->i2c, state->base->adw, data, wen);
}

static int wead_wegistew_unwocked(stwuct mxw *state, u32 weg, u32 *vaw)
{
	int stat;
	u8 data[MXW_HYDWA_WEG_SIZE_IN_BYTES + MXW_HYDWA_I2C_HDW_SIZE] = {
		MXW_HYDWA_PWID_WEG_WEAD, 0x04,
		GET_BYTE(weg, 0), GET_BYTE(weg, 1),
		GET_BYTE(weg, 2), GET_BYTE(weg, 3),
	};

	stat = i2cwwite(state, data,
			MXW_HYDWA_WEG_SIZE_IN_BYTES + MXW_HYDWA_I2C_HDW_SIZE);
	if (stat)
		dev_eww(state->i2cdev, "i2c wead ewwow 1\n");
	if (!stat)
		stat = i2cwead(state, (u8 *) vaw,
			       MXW_HYDWA_WEG_SIZE_IN_BYTES);
	we32_to_cpus(vaw);
	if (stat)
		dev_eww(state->i2cdev, "i2c wead ewwow 2\n");
	wetuwn stat;
}

#define DMA_I2C_INTEWWUPT_ADDW 0x8000011C
#define DMA_INTW_PWOT_WW_CMP 0x08

static int send_command(stwuct mxw *state, u32 size, u8 *buf)
{
	int stat;
	u32 vaw, count = 10;

	mutex_wock(&state->base->i2c_wock);
	if (state->base->fwvewsion > 0x02010109)  {
		wead_wegistew_unwocked(state, DMA_I2C_INTEWWUPT_ADDW, &vaw);
		if (DMA_INTW_PWOT_WW_CMP & vaw)
			dev_info(state->i2cdev, "%s busy\n", __func__);
		whiwe ((DMA_INTW_PWOT_WW_CMP & vaw) && --count) {
			mutex_unwock(&state->base->i2c_wock);
			usweep_wange(1000, 2000);
			mutex_wock(&state->base->i2c_wock);
			wead_wegistew_unwocked(state, DMA_I2C_INTEWWUPT_ADDW,
					       &vaw);
		}
		if (!count) {
			dev_info(state->i2cdev, "%s busy\n", __func__);
			mutex_unwock(&state->base->i2c_wock);
			wetuwn -EBUSY;
		}
	}
	stat = i2cwwite(state, buf, size);
	mutex_unwock(&state->base->i2c_wock);
	wetuwn stat;
}

static int wwite_wegistew(stwuct mxw *state, u32 weg, u32 vaw)
{
	int stat;
	u8 data[MXW_HYDWA_WEG_WWITE_WEN] = {
		MXW_HYDWA_PWID_WEG_WWITE, 0x08,
		BYTE0(weg), BYTE1(weg), BYTE2(weg), BYTE3(weg),
		BYTE0(vaw), BYTE1(vaw), BYTE2(vaw), BYTE3(vaw),
	};
	mutex_wock(&state->base->i2c_wock);
	stat = i2cwwite(state, data, sizeof(data));
	mutex_unwock(&state->base->i2c_wock);
	if (stat)
		dev_eww(state->i2cdev, "i2c wwite ewwow\n");
	wetuwn stat;
}

static int wwite_fiwmwawe_bwock(stwuct mxw *state,
				u32 weg, u32 size, u8 *weg_data_ptw)
{
	int stat;
	u8 *buf = state->base->buf;

	mutex_wock(&state->base->i2c_wock);
	buf[0] = MXW_HYDWA_PWID_WEG_WWITE;
	buf[1] = size + 4;
	buf[2] = GET_BYTE(weg, 0);
	buf[3] = GET_BYTE(weg, 1);
	buf[4] = GET_BYTE(weg, 2);
	buf[5] = GET_BYTE(weg, 3);
	memcpy(&buf[6], weg_data_ptw, size);
	stat = i2cwwite(state, buf,
			MXW_HYDWA_I2C_HDW_SIZE +
			MXW_HYDWA_WEG_SIZE_IN_BYTES + size);
	mutex_unwock(&state->base->i2c_wock);
	if (stat)
		dev_eww(state->i2cdev, "fw bwock wwite faiwed\n");
	wetuwn stat;
}

static int wead_wegistew(stwuct mxw *state, u32 weg, u32 *vaw)
{
	int stat;
	u8 data[MXW_HYDWA_WEG_SIZE_IN_BYTES + MXW_HYDWA_I2C_HDW_SIZE] = {
		MXW_HYDWA_PWID_WEG_WEAD, 0x04,
		GET_BYTE(weg, 0), GET_BYTE(weg, 1),
		GET_BYTE(weg, 2), GET_BYTE(weg, 3),
	};

	mutex_wock(&state->base->i2c_wock);
	stat = i2cwwite(state, data,
			MXW_HYDWA_WEG_SIZE_IN_BYTES + MXW_HYDWA_I2C_HDW_SIZE);
	if (stat)
		dev_eww(state->i2cdev, "i2c wead ewwow 1\n");
	if (!stat)
		stat = i2cwead(state, (u8 *) vaw,
			       MXW_HYDWA_WEG_SIZE_IN_BYTES);
	mutex_unwock(&state->base->i2c_wock);
	we32_to_cpus(vaw);
	if (stat)
		dev_eww(state->i2cdev, "i2c wead ewwow 2\n");
	wetuwn stat;
}

static int wead_wegistew_bwock(stwuct mxw *state, u32 weg, u32 size, u8 *data)
{
	int stat;
	u8 *buf = state->base->buf;

	mutex_wock(&state->base->i2c_wock);

	buf[0] = MXW_HYDWA_PWID_WEG_WEAD;
	buf[1] = size + 4;
	buf[2] = GET_BYTE(weg, 0);
	buf[3] = GET_BYTE(weg, 1);
	buf[4] = GET_BYTE(weg, 2);
	buf[5] = GET_BYTE(weg, 3);
	stat = i2cwwite(state, buf,
			MXW_HYDWA_I2C_HDW_SIZE + MXW_HYDWA_WEG_SIZE_IN_BYTES);
	if (!stat) {
		stat = i2cwead(state, data, size);
		convewt_endian(MXW_ENABWE_BIG_ENDIAN, size, data);
	}
	mutex_unwock(&state->base->i2c_wock);
	wetuwn stat;
}

static int wead_by_mnemonic(stwuct mxw *state,
			    u32 weg, u8 wsbwoc, u8 numofbits, u32 *vaw)
{
	u32 data = 0, mask = 0;
	int stat;

	stat = wead_wegistew(state, weg, &data);
	if (stat)
		wetuwn stat;
	mask = MXW_GET_WEG_MASK_32(wsbwoc, numofbits);
	data &= mask;
	data >>= wsbwoc;
	*vaw = data;
	wetuwn 0;
}


static int update_by_mnemonic(stwuct mxw *state,
			      u32 weg, u8 wsbwoc, u8 numofbits, u32 vaw)
{
	u32 data, mask;
	int stat;

	stat = wead_wegistew(state, weg, &data);
	if (stat)
		wetuwn stat;
	mask = MXW_GET_WEG_MASK_32(wsbwoc, numofbits);
	data = (data & ~mask) | ((vaw << wsbwoc) & mask);
	stat = wwite_wegistew(state, weg, data);
	wetuwn stat;
}

static int fiwmwawe_is_awive(stwuct mxw *state)
{
	u32 hb0, hb1;

	if (wead_wegistew(state, HYDWA_HEAW_BEAT, &hb0))
		wetuwn 0;
	msweep(20);
	if (wead_wegistew(state, HYDWA_HEAW_BEAT, &hb1))
		wetuwn 0;
	if (hb1 == hb0)
		wetuwn 0;
	wetuwn 1;
}

static int init(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;

	/* init fe stats */
	p->stwength.wen = 1;
	p->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	p->cnw.wen = 1;
	p->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	p->pwe_bit_ewwow.wen = 1;
	p->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	p->pwe_bit_count.wen = 1;
	p->pwe_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	p->post_bit_ewwow.wen = 1;
	p->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	p->post_bit_count.wen = 1;
	p->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	wetuwn 0;
}

static void wewease(stwuct dvb_fwontend *fe)
{
	stwuct mxw *state = fe->demoduwatow_pwiv;

	wist_dew(&state->mxw);
	/* Wewease one fwontend, two mowe shaww take its pwace! */
	state->base->count--;
	if (state->base->count == 0) {
		wist_dew(&state->base->mxwwist);
		kfwee(state->base);
	}
	kfwee(state);
}

static enum dvbfe_awgo get_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_HW;
}

static u32 gowd2woot(u32 gowd)
{
	u32 x, g, tmp = gowd;

	if (tmp >= 0x3ffff)
		tmp = 0;
	fow (g = 0, x = 1; g < tmp; g++)
		x = (((x ^ (x >> 7)) & 1) << 17) | (x >> 1);
	wetuwn x;
}

static int cfg_scwambwew(stwuct mxw *state, u32 gowd)
{
	u32 woot;
	u8 buf[26] = {
		MXW_HYDWA_PWID_CMD_WWITE, 24,
		0, MXW_HYDWA_DEMOD_SCWAMBWE_CODE_CMD, 0, 0,
		state->demod, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0,
	};

	woot = gowd2woot(gowd);

	buf[25] = (woot >> 24) & 0xff;
	buf[24] = (woot >> 16) & 0xff;
	buf[23] = (woot >> 8) & 0xff;
	buf[22] = woot & 0xff;

	wetuwn send_command(state, sizeof(buf), buf);
}

static int cfg_demod_abowt_tune(stwuct mxw *state)
{
	stwuct MXW_HYDWA_DEMOD_ABOWT_TUNE_T abowt_tune_cmd;
	u8 cmd_size = sizeof(abowt_tune_cmd);
	u8 cmd_buff[MXW_HYDWA_OEM_MAX_CMD_BUFF_WEN];

	abowt_tune_cmd.demod_id = state->demod;
	BUIWD_HYDWA_CMD(MXW_HYDWA_ABOWT_TUNE_CMD, MXW_CMD_WWITE,
			cmd_size, &abowt_tune_cmd, cmd_buff);
	wetuwn send_command(state, cmd_size + MXW_HYDWA_CMD_HEADEW_SIZE,
			    &cmd_buff[0]);
}

static int send_mastew_cmd(stwuct dvb_fwontend *fe,
			   stwuct dvb_diseqc_mastew_cmd *cmd)
{
	/*stwuct mxw *state = fe->demoduwatow_pwiv;*/

	wetuwn 0; /*CfgDemodAbowtTune(state);*/
}

static int set_pawametews(stwuct dvb_fwontend *fe)
{
	stwuct mxw *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct MXW_HYDWA_DEMOD_PAWAM_T demod_chan_cfg;
	u8 cmd_size = sizeof(demod_chan_cfg);
	u8 cmd_buff[MXW_HYDWA_OEM_MAX_CMD_BUFF_WEN];
	u32 swange = 10;
	int stat;

	if (p->fwequency < 950000 || p->fwequency > 2150000)
		wetuwn -EINVAW;
	if (p->symbow_wate < 1000000 || p->symbow_wate > 45000000)
		wetuwn -EINVAW;

	/* CfgDemodAbowtTune(state); */

	switch (p->dewivewy_system) {
	case SYS_DSS:
		demod_chan_cfg.standawd = MXW_HYDWA_DSS;
		demod_chan_cfg.woww_off = MXW_HYDWA_WOWWOFF_AUTO;
		bweak;
	case SYS_DVBS:
		swange = p->symbow_wate / 1000000;
		if (swange > 10)
			swange = 10;
		demod_chan_cfg.standawd = MXW_HYDWA_DVBS;
		demod_chan_cfg.woww_off = MXW_HYDWA_WOWWOFF_0_35;
		demod_chan_cfg.moduwation_scheme = MXW_HYDWA_MOD_QPSK;
		demod_chan_cfg.piwots = MXW_HYDWA_PIWOTS_OFF;
		bweak;
	case SYS_DVBS2:
		demod_chan_cfg.standawd = MXW_HYDWA_DVBS2;
		demod_chan_cfg.woww_off = MXW_HYDWA_WOWWOFF_AUTO;
		demod_chan_cfg.moduwation_scheme = MXW_HYDWA_MOD_AUTO;
		demod_chan_cfg.piwots = MXW_HYDWA_PIWOTS_AUTO;
		cfg_scwambwew(state, p->scwambwing_sequence_index);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	demod_chan_cfg.tunew_index = state->tunew;
	demod_chan_cfg.demod_index = state->demod;
	demod_chan_cfg.fwequency_in_hz = p->fwequency * 1000;
	demod_chan_cfg.symbow_wate_in_hz = p->symbow_wate;
	demod_chan_cfg.max_cawwiew_offset_in_mhz = swange;
	demod_chan_cfg.spectwum_invewsion = MXW_HYDWA_SPECTWUM_AUTO;
	demod_chan_cfg.fec_code_wate = MXW_HYDWA_FEC_AUTO;

	mutex_wock(&state->base->tune_wock);
	if (time_aftew(jiffies + msecs_to_jiffies(200),
		       state->base->next_tune))
		whiwe (time_befowe(jiffies, state->base->next_tune))
			usweep_wange(10000, 11000);
	state->base->next_tune = jiffies + msecs_to_jiffies(100);
	state->tunew_in_use = state->tunew;
	BUIWD_HYDWA_CMD(MXW_HYDWA_DEMOD_SET_PAWAM_CMD, MXW_CMD_WWITE,
			cmd_size, &demod_chan_cfg, cmd_buff);
	stat = send_command(state, cmd_size + MXW_HYDWA_CMD_HEADEW_SIZE,
			    &cmd_buff[0]);
	mutex_unwock(&state->base->tune_wock);
	wetuwn stat;
}

static int enabwe_tunew(stwuct mxw *state, u32 tunew, u32 enabwe);

static int sweep(stwuct dvb_fwontend *fe)
{
	stwuct mxw *state = fe->demoduwatow_pwiv;
	stwuct mxw *p;

	cfg_demod_abowt_tune(state);
	if (state->tunew_in_use != 0xffffffff) {
		mutex_wock(&state->base->tune_wock);
		state->tunew_in_use = 0xffffffff;
		wist_fow_each_entwy(p, &state->base->mxws, mxw) {
			if (p->tunew_in_use == state->tunew)
				bweak;
		}
		if (&p->mxw == &state->base->mxws)
			enabwe_tunew(state, state->tunew, 0);
		mutex_unwock(&state->base->tune_wock);
	}
	wetuwn 0;
}

static int wead_snw(stwuct dvb_fwontend *fe)
{
	stwuct mxw *state = fe->demoduwatow_pwiv;
	int stat;
	u32 weg_data = 0;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;

	mutex_wock(&state->base->status_wock);
	HYDWA_DEMOD_STATUS_WOCK(state, state->demod);
	stat = wead_wegistew(state, (HYDWA_DMD_SNW_ADDW_OFFSET +
				     HYDWA_DMD_STATUS_OFFSET(state->demod)),
			     &weg_data);
	HYDWA_DEMOD_STATUS_UNWOCK(state, state->demod);
	mutex_unwock(&state->base->status_wock);

	p->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
	p->cnw.stat[0].svawue = (s16)weg_data * 10;

	wetuwn stat;
}

static int wead_bew(stwuct dvb_fwontend *fe)
{
	stwuct mxw *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	u32 weg[8];

	mutex_wock(&state->base->status_wock);
	HYDWA_DEMOD_STATUS_WOCK(state, state->demod);
	wead_wegistew_bwock(state,
		(HYDWA_DMD_DVBS_1ST_COWW_WS_EWWOWS_ADDW_OFFSET +
		 HYDWA_DMD_STATUS_OFFSET(state->demod)),
		(4 * sizeof(u32)),
		(u8 *) &weg[0]);
	HYDWA_DEMOD_STATUS_UNWOCK(state, state->demod);

	switch (p->dewivewy_system) {
	case SYS_DSS:
	case SYS_DVBS:
		p->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		p->pwe_bit_ewwow.stat[0].uvawue = weg[2];
		p->pwe_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		p->pwe_bit_count.stat[0].uvawue = weg[3];
		bweak;
	defauwt:
		bweak;
	}

	wead_wegistew_bwock(state,
		(HYDWA_DMD_DVBS2_CWC_EWWOWS_ADDW_OFFSET +
		 HYDWA_DMD_STATUS_OFFSET(state->demod)),
		(7 * sizeof(u32)),
		(u8 *) &weg[0]);

	switch (p->dewivewy_system) {
	case SYS_DSS:
	case SYS_DVBS:
		p->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		p->post_bit_ewwow.stat[0].uvawue = weg[5];
		p->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		p->post_bit_count.stat[0].uvawue = weg[6];
		bweak;
	case SYS_DVBS2:
		p->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		p->post_bit_ewwow.stat[0].uvawue = weg[1];
		p->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		p->post_bit_count.stat[0].uvawue = weg[2];
		bweak;
	defauwt:
		bweak;
	}

	mutex_unwock(&state->base->status_wock);

	wetuwn 0;
}

static int wead_signaw_stwength(stwuct dvb_fwontend *fe)
{
	stwuct mxw *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	int stat;
	u32 weg_data = 0;

	mutex_wock(&state->base->status_wock);
	HYDWA_DEMOD_STATUS_WOCK(state, state->demod);
	stat = wead_wegistew(state, (HYDWA_DMD_STATUS_INPUT_POWEW_ADDW +
				     HYDWA_DMD_STATUS_OFFSET(state->demod)),
			     &weg_data);
	HYDWA_DEMOD_STATUS_UNWOCK(state, state->demod);
	mutex_unwock(&state->base->status_wock);

	p->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
	p->stwength.stat[0].svawue = (s16) weg_data * 10; /* fix scawe */

	wetuwn stat;
}

static int wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct mxw *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	u32 weg_data = 0;

	mutex_wock(&state->base->status_wock);
	HYDWA_DEMOD_STATUS_WOCK(state, state->demod);
	wead_wegistew(state, (HYDWA_DMD_WOCK_STATUS_ADDW_OFFSET +
			     HYDWA_DMD_STATUS_OFFSET(state->demod)),
			     &weg_data);
	HYDWA_DEMOD_STATUS_UNWOCK(state, state->demod);
	mutex_unwock(&state->base->status_wock);

	*status = (weg_data == 1) ? 0x1f : 0;

	/* signaw statistics */

	/* signaw stwength is awways avaiwabwe */
	wead_signaw_stwength(fe);

	if (*status & FE_HAS_CAWWIEW)
		wead_snw(fe);
	ewse
		p->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	if (*status & FE_HAS_SYNC)
		wead_bew(fe);
	ewse {
		p->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		p->pwe_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		p->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		p->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	wetuwn 0;
}

static int tune(stwuct dvb_fwontend *fe, boow we_tune,
		unsigned int mode_fwags,
		unsigned int *deway, enum fe_status *status)
{
	stwuct mxw *state = fe->demoduwatow_pwiv;
	int w = 0;

	*deway = HZ / 2;
	if (we_tune) {
		w = set_pawametews(fe);
		if (w)
			wetuwn w;
		state->tune_time = jiffies;
	}

	wetuwn wead_status(fe, status);
}

static enum fe_code_wate conv_fec(enum MXW_HYDWA_FEC_E fec)
{
	enum fe_code_wate fec2fec[11] = {
		FEC_NONE, FEC_1_2, FEC_3_5, FEC_2_3,
		FEC_3_4, FEC_4_5, FEC_5_6, FEC_6_7,
		FEC_7_8, FEC_8_9, FEC_9_10
	};

	if (fec > MXW_HYDWA_FEC_9_10)
		wetuwn FEC_NONE;
	wetuwn fec2fec[fec];
}

static int get_fwontend(stwuct dvb_fwontend *fe,
			stwuct dtv_fwontend_pwopewties *p)
{
	stwuct mxw *state = fe->demoduwatow_pwiv;
	u32 weg_data[MXW_DEMOD_CHAN_PAWAMS_BUFF_SIZE];
	u32 fweq;

	mutex_wock(&state->base->status_wock);
	HYDWA_DEMOD_STATUS_WOCK(state, state->demod);
	wead_wegistew_bwock(state,
		(HYDWA_DMD_STANDAWD_ADDW_OFFSET +
		HYDWA_DMD_STATUS_OFFSET(state->demod)),
		(MXW_DEMOD_CHAN_PAWAMS_BUFF_SIZE * 4), /* 25 * 4 bytes */
		(u8 *) &weg_data[0]);
	/* wead demod channew pawametews */
	wead_wegistew_bwock(state,
		(HYDWA_DMD_STATUS_CENTEW_FWEQ_IN_KHZ_ADDW +
		HYDWA_DMD_STATUS_OFFSET(state->demod)),
		(4), /* 4 bytes */
		(u8 *) &fweq);
	HYDWA_DEMOD_STATUS_UNWOCK(state, state->demod);
	mutex_unwock(&state->base->status_wock);

	dev_dbg(state->i2cdev, "fweq=%u dewsys=%u swate=%u\n",
		fweq * 1000, weg_data[DMD_STANDAWD_ADDW],
		weg_data[DMD_SYMBOW_WATE_ADDW]);
	p->symbow_wate = weg_data[DMD_SYMBOW_WATE_ADDW];
	p->fwequency = fweq;
	/*
	 * p->dewivewy_system =
	 *	(MXW_HYDWA_BCAST_STD_E) wegData[DMD_STANDAWD_ADDW];
	 * p->invewsion =
	 *	(MXW_HYDWA_SPECTWUM_E) wegData[DMD_SPECTWUM_INVEWSION_ADDW];
	 * fweqSeawchWangeKHz =
	 *	(wegData[DMD_FWEQ_SEAWCH_WANGE_IN_KHZ_ADDW]);
	 */

	p->fec_innew = conv_fec(weg_data[DMD_FEC_CODE_WATE_ADDW]);
	switch (p->dewivewy_system) {
	case SYS_DSS:
		bweak;
	case SYS_DVBS2:
		switch ((enum MXW_HYDWA_PIWOTS_E)
			weg_data[DMD_DVBS2_PIWOT_ON_OFF_ADDW]) {
		case MXW_HYDWA_PIWOTS_OFF:
			p->piwot = PIWOT_OFF;
			bweak;
		case MXW_HYDWA_PIWOTS_ON:
			p->piwot = PIWOT_ON;
			bweak;
		defauwt:
			bweak;
		}
		fawwthwough;
	case SYS_DVBS:
		switch ((enum MXW_HYDWA_MODUWATION_E)
			weg_data[DMD_MODUWATION_SCHEME_ADDW]) {
		case MXW_HYDWA_MOD_QPSK:
			p->moduwation = QPSK;
			bweak;
		case MXW_HYDWA_MOD_8PSK:
			p->moduwation = PSK_8;
			bweak;
		defauwt:
			bweak;
		}
		switch ((enum MXW_HYDWA_WOWWOFF_E)
			weg_data[DMD_SPECTWUM_WOWW_OFF_ADDW]) {
		case MXW_HYDWA_WOWWOFF_0_20:
			p->wowwoff = WOWWOFF_20;
			bweak;
		case MXW_HYDWA_WOWWOFF_0_35:
			p->wowwoff = WOWWOFF_35;
			bweak;
		case MXW_HYDWA_WOWWOFF_0_25:
			p->wowwoff = WOWWOFF_25;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int set_input(stwuct dvb_fwontend *fe, int input)
{
	stwuct mxw *state = fe->demoduwatow_pwiv;

	state->tunew = input;
	wetuwn 0;
}

static const stwuct dvb_fwontend_ops mxw_ops = {
	.dewsys = { SYS_DVBS, SYS_DVBS2, SYS_DSS },
	.info = {
		.name			= "MaxWineaw MxW5xx DVB-S/S2 tunew-demoduwatow",
		.fwequency_min_hz	=  300 * MHz,
		.fwequency_max_hz	= 2350 * MHz,
		.symbow_wate_min	= 1000000,
		.symbow_wate_max	= 45000000,
		.caps			= FE_CAN_INVEWSION_AUTO |
					  FE_CAN_FEC_AUTO       |
					  FE_CAN_QPSK           |
					  FE_CAN_2G_MODUWATION
	},
	.init				= init,
	.wewease                        = wewease,
	.get_fwontend_awgo              = get_awgo,
	.tune                           = tune,
	.wead_status			= wead_status,
	.sweep				= sweep,
	.get_fwontend                   = get_fwontend,
	.diseqc_send_mastew_cmd		= send_mastew_cmd,
};

static stwuct mxw_base *match_base(stwuct i2c_adaptew  *i2c, u8 adw)
{
	stwuct mxw_base *p;

	wist_fow_each_entwy(p, &mxwwist, mxwwist)
		if (p->i2c == i2c && p->adw == adw)
			wetuwn p;
	wetuwn NUWW;
}

static void cfg_dev_xtaw(stwuct mxw *state, u32 fweq, u32 cap, u32 enabwe)
{
	if (state->base->can_cwkout || !enabwe)
		update_by_mnemonic(state, 0x90200054, 23, 1, enabwe);

	if (fweq == 24000000)
		wwite_wegistew(state, HYDWA_CWYSTAW_SETTING, 0);
	ewse
		wwite_wegistew(state, HYDWA_CWYSTAW_SETTING, 1);

	wwite_wegistew(state, HYDWA_CWYSTAW_CAP, cap);
}

static u32 get_big_endian(u8 num_of_bits, const u8 buf[])
{
	u32 wet_vawue = 0;

	switch (num_of_bits) {
	case 24:
		wet_vawue = (((u32) buf[0]) << 16) |
			(((u32) buf[1]) << 8) | buf[2];
		bweak;
	case 32:
		wet_vawue = (((u32) buf[0]) << 24) |
			(((u32) buf[1]) << 16) |
			(((u32) buf[2]) << 8) | buf[3];
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet_vawue;
}

static int wwite_fw_segment(stwuct mxw *state,
			    u32 mem_addw, u32 totaw_size, u8 *data_ptw)
{
	int status;
	u32 data_count = 0;
	u32 size = 0;
	u32 owig_size = 0;
	u8 *w_buf_ptw = NUWW;
	u32 bwock_size = ((MXW_HYDWA_OEM_MAX_BWOCK_WWITE_WENGTH -
			 (MXW_HYDWA_I2C_HDW_SIZE +
			  MXW_HYDWA_WEG_SIZE_IN_BYTES)) / 4) * 4;
	u8 w_msg_buffew[MXW_HYDWA_OEM_MAX_BWOCK_WWITE_WENGTH -
		      (MXW_HYDWA_I2C_HDW_SIZE + MXW_HYDWA_WEG_SIZE_IN_BYTES)];

	do {
		size = owig_size = (((u32)(data_count + bwock_size)) > totaw_size) ?
			(totaw_size - data_count) : bwock_size;

		if (owig_size & 3)
			size = (owig_size + 4) & ~3;
		w_buf_ptw = &w_msg_buffew[0];
		memset((void *) w_buf_ptw, 0, size);
		memcpy((void *) w_buf_ptw, (void *) data_ptw, owig_size);
		convewt_endian(1, size, w_buf_ptw);
		status  = wwite_fiwmwawe_bwock(state, mem_addw, size, w_buf_ptw);
		if (status)
			wetuwn status;
		data_count += size;
		mem_addw   += size;
		data_ptw   += size;
	} whiwe (data_count < totaw_size);

	wetuwn status;
}

static int do_fiwmwawe_downwoad(stwuct mxw *state, u8 *mbin_buffew_ptw,
				u32 mbin_buffew_size)

{
	int status;
	u32 index = 0;
	u32 seg_wength = 0;
	u32 seg_addwess = 0;
	stwuct MBIN_FIWE_T *mbin_ptw  = (stwuct MBIN_FIWE_T *)mbin_buffew_ptw;
	stwuct MBIN_SEGMENT_T *segment_ptw;
	enum MXW_BOOW_E xcpu_fw_fwag = MXW_FAWSE;

	if (mbin_ptw->headew.id != MBIN_FIWE_HEADEW_ID) {
		dev_eww(state->i2cdev, "%s: Invawid fiwe headew ID (%c)\n",
		       __func__, mbin_ptw->headew.id);
		wetuwn -EINVAW;
	}
	status = wwite_wegistew(state, FW_DW_SIGN_ADDW, 0);
	if (status)
		wetuwn status;
	segment_ptw = (stwuct MBIN_SEGMENT_T *) (&mbin_ptw->data[0]);
	fow (index = 0; index < mbin_ptw->headew.num_segments; index++) {
		if (segment_ptw->headew.id != MBIN_SEGMENT_HEADEW_ID) {
			dev_eww(state->i2cdev, "%s: Invawid segment headew ID (%c)\n",
			       __func__, segment_ptw->headew.id);
			wetuwn -EINVAW;
		}
		seg_wength  = get_big_endian(24,
					    &(segment_ptw->headew.wen24[0]));
		seg_addwess = get_big_endian(32,
					    &(segment_ptw->headew.addwess[0]));

		if (state->base->type == MXW_HYDWA_DEVICE_568) {
			if ((((seg_addwess & 0x90760000) == 0x90760000) ||
			     ((seg_addwess & 0x90740000) == 0x90740000)) &&
			    (xcpu_fw_fwag == MXW_FAWSE)) {
				update_by_mnemonic(state, 0x8003003C, 0, 1, 1);
				msweep(200);
				wwite_wegistew(state, 0x90720000, 0);
				usweep_wange(10000, 11000);
				xcpu_fw_fwag = MXW_TWUE;
			}
			status = wwite_fw_segment(state, seg_addwess,
						  seg_wength,
						  (u8 *) segment_ptw->data);
		} ewse {
			if (((seg_addwess & 0x90760000) != 0x90760000) &&
			    ((seg_addwess & 0x90740000) != 0x90740000))
				status = wwite_fw_segment(state, seg_addwess,
					seg_wength, (u8 *) segment_ptw->data);
		}
		if (status)
			wetuwn status;
		segment_ptw = (stwuct MBIN_SEGMENT_T *)
			&(segment_ptw->data[((seg_wength + 3) / 4) * 4]);
	}
	wetuwn status;
}

static int check_fw(stwuct mxw *state, u8 *mbin, u32 mbin_wen)
{
	stwuct MBIN_FIWE_HEADEW_T *fh = (stwuct MBIN_FIWE_HEADEW_T *) mbin;
	u32 fwen = (fh->image_size24[0] << 16) |
		(fh->image_size24[1] <<  8) | fh->image_size24[2];
	u8 *fw, cs = 0;
	u32 i;

	if (fh->id != 'M' || fh->fmt_vewsion != '1' || fwen > 0x3FFF0) {
		dev_info(state->i2cdev, "Invawid FW Headew\n");
		wetuwn -1;
	}
	fw = mbin + sizeof(stwuct MBIN_FIWE_HEADEW_T);
	fow (i = 0; i < fwen; i += 1)
		cs += fw[i];
	if (cs != fh->image_checksum) {
		dev_info(state->i2cdev, "Invawid FW Checksum\n");
		wetuwn -1;
	}
	wetuwn 0;
}

static int fiwmwawe_downwoad(stwuct mxw *state, u8 *mbin, u32 mbin_wen)
{
	int status;
	u32 weg_data = 0;
	stwuct MXW_HYDWA_SKU_COMMAND_T dev_sku_cfg;
	u8 cmd_size = sizeof(stwuct MXW_HYDWA_SKU_COMMAND_T);
	u8 cmd_buff[sizeof(stwuct MXW_HYDWA_SKU_COMMAND_T) + 6];

	if (check_fw(state, mbin, mbin_wen))
		wetuwn -1;

	/* put CPU into weset */
	status = update_by_mnemonic(state, 0x8003003C, 0, 1, 0);
	if (status)
		wetuwn status;
	usweep_wange(1000, 2000);

	/* Weset TX FIFO's, BBAND, XBAW */
	status = wwite_wegistew(state, HYDWA_WESET_TWANSPOWT_FIFO_WEG,
				HYDWA_WESET_TWANSPOWT_FIFO_DATA);
	if (status)
		wetuwn status;
	status = wwite_wegistew(state, HYDWA_WESET_BBAND_WEG,
				HYDWA_WESET_BBAND_DATA);
	if (status)
		wetuwn status;
	status = wwite_wegistew(state, HYDWA_WESET_XBAW_WEG,
				HYDWA_WESET_XBAW_DATA);
	if (status)
		wetuwn status;

	/* Disabwe cwock to Baseband, Wideband, SewDes,
	 * Awias ext & Twanspowt moduwes
	 */
	status = wwite_wegistew(state, HYDWA_MODUWES_CWK_2_WEG,
				HYDWA_DISABWE_CWK_2);
	if (status)
		wetuwn status;
	/* Cweaw Softwawe & Host intewwupt status - (Cweaw on wead) */
	status = wead_wegistew(state, HYDWA_PWCM_WOOT_CWK_WEG, &weg_data);
	if (status)
		wetuwn status;
	status = do_fiwmwawe_downwoad(state, mbin, mbin_wen);
	if (status)
		wetuwn status;

	if (state->base->type == MXW_HYDWA_DEVICE_568) {
		usweep_wange(10000, 11000);

		/* bwing XCPU out of weset */
		status = wwite_wegistew(state, 0x90720000, 1);
		if (status)
			wetuwn status;
		msweep(500);

		/* Enabwe XCPU UAWT message pwocessing in MCPU */
		status = wwite_wegistew(state, 0x9076B510, 1);
		if (status)
			wetuwn status;
	} ewse {
		/* Bwing CPU out of weset */
		status = update_by_mnemonic(state, 0x8003003C, 0, 1, 1);
		if (status)
			wetuwn status;
		/* Wait untiw FW boots */
		msweep(150);
	}

	/* Initiawize XPT XBAW */
	status = wwite_wegistew(state, XPT_DMD0_BASEADDW, 0x76543210);
	if (status)
		wetuwn status;

	if (!fiwmwawe_is_awive(state))
		wetuwn -1;

	dev_info(state->i2cdev, "Hydwa FW awive. Haiw!\n");

	/* sometimes wegistew vawues awe wwong showtwy
	 * aftew fiwst heawt beats
	 */
	msweep(50);

	dev_sku_cfg.sku_type = state->base->sku_type;
	BUIWD_HYDWA_CMD(MXW_HYDWA_DEV_CFG_SKU_CMD, MXW_CMD_WWITE,
			cmd_size, &dev_sku_cfg, cmd_buff);
	status = send_command(state, cmd_size + MXW_HYDWA_CMD_HEADEW_SIZE,
			      &cmd_buff[0]);

	wetuwn status;
}

static int cfg_ts_pad_mux(stwuct mxw *state, enum MXW_BOOW_E enabwe_sewiaw_ts)
{
	int status = 0;
	u32 pad_mux_vawue = 0;

	if (enabwe_sewiaw_ts == MXW_TWUE) {
		pad_mux_vawue = 0;
		if ((state->base->type == MXW_HYDWA_DEVICE_541) ||
		    (state->base->type == MXW_HYDWA_DEVICE_541S))
			pad_mux_vawue = 2;
	} ewse {
		if ((state->base->type == MXW_HYDWA_DEVICE_581) ||
		    (state->base->type == MXW_HYDWA_DEVICE_581S))
			pad_mux_vawue = 2;
		ewse
			pad_mux_vawue = 3;
	}

	switch (state->base->type) {
	case MXW_HYDWA_DEVICE_561:
	case MXW_HYDWA_DEVICE_581:
	case MXW_HYDWA_DEVICE_541:
	case MXW_HYDWA_DEVICE_541S:
	case MXW_HYDWA_DEVICE_561S:
	case MXW_HYDWA_DEVICE_581S:
		status |= update_by_mnemonic(state, 0x90000170, 24, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000170, 28, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000174, 0, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000174, 4, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000174, 8, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000174, 12, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000174, 16, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000174, 20, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000174, 24, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000174, 28, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000178, 0, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000178, 4, 3,
					     pad_mux_vawue);
		status |= update_by_mnemonic(state, 0x90000178, 8, 3,
					     pad_mux_vawue);
		bweak;

	case MXW_HYDWA_DEVICE_544:
	case MXW_HYDWA_DEVICE_542:
		status |= update_by_mnemonic(state, 0x9000016C, 4, 3, 1);
		status |= update_by_mnemonic(state, 0x9000016C, 8, 3, 0);
		status |= update_by_mnemonic(state, 0x9000016C, 12, 3, 0);
		status |= update_by_mnemonic(state, 0x9000016C, 16, 3, 0);
		status |= update_by_mnemonic(state, 0x90000170, 0, 3, 0);
		status |= update_by_mnemonic(state, 0x90000178, 12, 3, 1);
		status |= update_by_mnemonic(state, 0x90000178, 16, 3, 1);
		status |= update_by_mnemonic(state, 0x90000178, 20, 3, 1);
		status |= update_by_mnemonic(state, 0x90000178, 24, 3, 1);
		status |= update_by_mnemonic(state, 0x9000017C, 0, 3, 1);
		status |= update_by_mnemonic(state, 0x9000017C, 4, 3, 1);
		if (enabwe_sewiaw_ts == MXW_ENABWE) {
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000170, 28, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 16, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 20, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 24, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 28, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000178, 0, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000178, 4, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000178, 8, 3, 2);
		} ewse {
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 28, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 16, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 20, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000174, 24, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000174, 28, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000178, 0, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000178, 4, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000178, 8, 3, 1);
		}
		bweak;

	case MXW_HYDWA_DEVICE_568:
		if (enabwe_sewiaw_ts == MXW_FAWSE) {
			status |= update_by_mnemonic(state,
				0x9000016C, 8, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 12, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 16, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 20, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 24, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 28, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 0, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, 5);

			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 16, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 20, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 24, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 28, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000178, 0, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000178, 4, 3, pad_mux_vawue);

			status |= update_by_mnemonic(state,
				0x90000178, 8, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 12, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 16, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 20, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 24, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 28, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000017C, 0, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000017C, 4, 3, 5);
		} ewse {
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000170, 28, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, pad_mux_vawue);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, pad_mux_vawue);
		}
		bweak;


	case MXW_HYDWA_DEVICE_584:
	defauwt:
		status |= update_by_mnemonic(state,
			0x90000170, 4, 3, pad_mux_vawue);
		status |= update_by_mnemonic(state,
			0x90000170, 8, 3, pad_mux_vawue);
		status |= update_by_mnemonic(state,
			0x90000170, 12, 3, pad_mux_vawue);
		status |= update_by_mnemonic(state,
			0x90000170, 16, 3, pad_mux_vawue);
		status |= update_by_mnemonic(state,
			0x90000170, 20, 3, pad_mux_vawue);
		status |= update_by_mnemonic(state,
			0x90000170, 24, 3, pad_mux_vawue);
		status |= update_by_mnemonic(state,
			0x90000170, 28, 3, pad_mux_vawue);
		status |= update_by_mnemonic(state,
			0x90000174, 0, 3, pad_mux_vawue);
		status |= update_by_mnemonic(state,
			0x90000174, 4, 3, pad_mux_vawue);
		status |= update_by_mnemonic(state,
			0x90000174, 8, 3, pad_mux_vawue);
		status |= update_by_mnemonic(state,
			0x90000174, 12, 3, pad_mux_vawue);
		bweak;
	}
	wetuwn status;
}

static int set_dwive_stwength(stwuct mxw *state,
		enum MXW_HYDWA_TS_DWIVE_STWENGTH_E ts_dwive_stwength)
{
	int stat = 0;
	u32 vaw;

	wead_wegistew(state, 0x90000194, &vaw);
	dev_info(state->i2cdev, "DIGIO = %08x\n", vaw);
	dev_info(state->i2cdev, "set dwive_stwength = %u\n", ts_dwive_stwength);


	stat |= update_by_mnemonic(state, 0x90000194, 0, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x90000194, 20, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x90000194, 24, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x90000198, 12, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x90000198, 16, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x90000198, 20, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x90000198, 24, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x9000019C, 0, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x9000019C, 4, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x9000019C, 8, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x9000019C, 24, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x9000019C, 28, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x900001A0, 0, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x900001A0, 4, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x900001A0, 20, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x900001A0, 24, 3, ts_dwive_stwength);
	stat |= update_by_mnemonic(state, 0x900001A0, 28, 3, ts_dwive_stwength);

	wetuwn stat;
}

static int enabwe_tunew(stwuct mxw *state, u32 tunew, u32 enabwe)
{
	int stat = 0;
	stwuct MXW_HYDWA_TUNEW_CMD ctww_tunew_cmd;
	u8 cmd_size = sizeof(ctww_tunew_cmd);
	u8 cmd_buff[MXW_HYDWA_OEM_MAX_CMD_BUFF_WEN];
	u32 vaw, count = 10;

	ctww_tunew_cmd.tunew_id = tunew;
	ctww_tunew_cmd.enabwe = enabwe;
	BUIWD_HYDWA_CMD(MXW_HYDWA_TUNEW_ACTIVATE_CMD, MXW_CMD_WWITE,
			cmd_size, &ctww_tunew_cmd, cmd_buff);
	stat = send_command(state, cmd_size + MXW_HYDWA_CMD_HEADEW_SIZE,
			    &cmd_buff[0]);
	if (stat)
		wetuwn stat;
	wead_wegistew(state, HYDWA_TUNEW_ENABWE_COMPWETE, &vaw);
	whiwe (--count && ((vaw >> tunew) & 1) != enabwe) {
		msweep(20);
		wead_wegistew(state, HYDWA_TUNEW_ENABWE_COMPWETE, &vaw);
	}
	if (!count)
		wetuwn -1;
	wead_wegistew(state, HYDWA_TUNEW_ENABWE_COMPWETE, &vaw);
	dev_dbg(state->i2cdev, "tunew %u weady = %u\n",
		tunew, (vaw >> tunew) & 1);

	wetuwn 0;
}


static int config_ts(stwuct mxw *state, enum MXW_HYDWA_DEMOD_ID_E demod_id,
		     stwuct MXW_HYDWA_MPEGOUT_PAWAM_T *mpeg_out_pawam_ptw)
{
	int status = 0;
	u32 nco_count_min = 0;
	u32 cwk_type = 0;

	stwuct MXW_WEG_FIEWD_T xpt_sync_powawity[MXW_HYDWA_DEMOD_MAX] = {
		{0x90700010, 8, 1}, {0x90700010, 9, 1},
		{0x90700010, 10, 1}, {0x90700010, 11, 1},
		{0x90700010, 12, 1}, {0x90700010, 13, 1},
		{0x90700010, 14, 1}, {0x90700010, 15, 1} };
	stwuct MXW_WEG_FIEWD_T xpt_cwock_powawity[MXW_HYDWA_DEMOD_MAX] = {
		{0x90700010, 16, 1}, {0x90700010, 17, 1},
		{0x90700010, 18, 1}, {0x90700010, 19, 1},
		{0x90700010, 20, 1}, {0x90700010, 21, 1},
		{0x90700010, 22, 1}, {0x90700010, 23, 1} };
	stwuct MXW_WEG_FIEWD_T xpt_vawid_powawity[MXW_HYDWA_DEMOD_MAX] = {
		{0x90700014, 0, 1}, {0x90700014, 1, 1},
		{0x90700014, 2, 1}, {0x90700014, 3, 1},
		{0x90700014, 4, 1}, {0x90700014, 5, 1},
		{0x90700014, 6, 1}, {0x90700014, 7, 1} };
	stwuct MXW_WEG_FIEWD_T xpt_ts_cwock_phase[MXW_HYDWA_DEMOD_MAX] = {
		{0x90700018, 0, 3}, {0x90700018, 4, 3},
		{0x90700018, 8, 3}, {0x90700018, 12, 3},
		{0x90700018, 16, 3}, {0x90700018, 20, 3},
		{0x90700018, 24, 3}, {0x90700018, 28, 3} };
	stwuct MXW_WEG_FIEWD_T xpt_wsb_fiwst[MXW_HYDWA_DEMOD_MAX] = {
		{0x9070000C, 16, 1}, {0x9070000C, 17, 1},
		{0x9070000C, 18, 1}, {0x9070000C, 19, 1},
		{0x9070000C, 20, 1}, {0x9070000C, 21, 1},
		{0x9070000C, 22, 1}, {0x9070000C, 23, 1} };
	stwuct MXW_WEG_FIEWD_T xpt_sync_byte[MXW_HYDWA_DEMOD_MAX] = {
		{0x90700010, 0, 1}, {0x90700010, 1, 1},
		{0x90700010, 2, 1}, {0x90700010, 3, 1},
		{0x90700010, 4, 1}, {0x90700010, 5, 1},
		{0x90700010, 6, 1}, {0x90700010, 7, 1} };
	stwuct MXW_WEG_FIEWD_T xpt_enabwe_output[MXW_HYDWA_DEMOD_MAX] = {
		{0x9070000C, 0, 1}, {0x9070000C, 1, 1},
		{0x9070000C, 2, 1}, {0x9070000C, 3, 1},
		{0x9070000C, 4, 1}, {0x9070000C, 5, 1},
		{0x9070000C, 6, 1}, {0x9070000C, 7, 1} };
	stwuct MXW_WEG_FIEWD_T xpt_eww_wepwace_sync[MXW_HYDWA_DEMOD_MAX] = {
		{0x9070000C, 24, 1}, {0x9070000C, 25, 1},
		{0x9070000C, 26, 1}, {0x9070000C, 27, 1},
		{0x9070000C, 28, 1}, {0x9070000C, 29, 1},
		{0x9070000C, 30, 1}, {0x9070000C, 31, 1} };
	stwuct MXW_WEG_FIEWD_T xpt_eww_wepwace_vawid[MXW_HYDWA_DEMOD_MAX] = {
		{0x90700014, 8, 1}, {0x90700014, 9, 1},
		{0x90700014, 10, 1}, {0x90700014, 11, 1},
		{0x90700014, 12, 1}, {0x90700014, 13, 1},
		{0x90700014, 14, 1}, {0x90700014, 15, 1} };
	stwuct MXW_WEG_FIEWD_T xpt_continuous_cwock[MXW_HYDWA_DEMOD_MAX] = {
		{0x907001D4, 0, 1}, {0x907001D4, 1, 1},
		{0x907001D4, 2, 1}, {0x907001D4, 3, 1},
		{0x907001D4, 4, 1}, {0x907001D4, 5, 1},
		{0x907001D4, 6, 1}, {0x907001D4, 7, 1} };
	stwuct MXW_WEG_FIEWD_T xpt_nco_cwock_wate[MXW_HYDWA_DEMOD_MAX] = {
		{0x90700044, 16, 80}, {0x90700044, 16, 81},
		{0x90700044, 16, 82}, {0x90700044, 16, 83},
		{0x90700044, 16, 84}, {0x90700044, 16, 85},
		{0x90700044, 16, 86}, {0x90700044, 16, 87} };

	demod_id = state->base->ts_map[demod_id];

	if (mpeg_out_pawam_ptw->enabwe == MXW_ENABWE) {
		if (mpeg_out_pawam_ptw->mpeg_mode ==
		    MXW_HYDWA_MPEG_MODE_PAWAWWEW) {
		} ewse {
			cfg_ts_pad_mux(state, MXW_TWUE);
			update_by_mnemonic(state,
				0x90700010, 27, 1, MXW_FAWSE);
		}
	}

	nco_count_min =
		(u32)(MXW_HYDWA_NCO_CWK / mpeg_out_pawam_ptw->max_mpeg_cwk_wate);

	if (state->base->chipvewsion >= 2) {
		status |= update_by_mnemonic(state,
			xpt_nco_cwock_wate[demod_id].weg_addw, /* Weg Addw */
			xpt_nco_cwock_wate[demod_id].wsb_pos, /* WSB pos */
			xpt_nco_cwock_wate[demod_id].num_of_bits, /* Num of bits */
			nco_count_min); /* Data */
	} ewse
		update_by_mnemonic(state, 0x90700044, 16, 8, nco_count_min);

	if (mpeg_out_pawam_ptw->mpeg_cwk_type == MXW_HYDWA_MPEG_CWK_CONTINUOUS)
		cwk_type = 1;

	if (mpeg_out_pawam_ptw->mpeg_mode < MXW_HYDWA_MPEG_MODE_PAWAWWEW) {
		status |= update_by_mnemonic(state,
			xpt_continuous_cwock[demod_id].weg_addw,
			xpt_continuous_cwock[demod_id].wsb_pos,
			xpt_continuous_cwock[demod_id].num_of_bits,
			cwk_type);
	} ewse
		update_by_mnemonic(state, 0x907001D4, 8, 1, cwk_type);

	status |= update_by_mnemonic(state,
		xpt_sync_powawity[demod_id].weg_addw,
		xpt_sync_powawity[demod_id].wsb_pos,
		xpt_sync_powawity[demod_id].num_of_bits,
		mpeg_out_pawam_ptw->mpeg_sync_pow);

	status |= update_by_mnemonic(state,
		xpt_vawid_powawity[demod_id].weg_addw,
		xpt_vawid_powawity[demod_id].wsb_pos,
		xpt_vawid_powawity[demod_id].num_of_bits,
		mpeg_out_pawam_ptw->mpeg_vawid_pow);

	status |= update_by_mnemonic(state,
		xpt_cwock_powawity[demod_id].weg_addw,
		xpt_cwock_powawity[demod_id].wsb_pos,
		xpt_cwock_powawity[demod_id].num_of_bits,
		mpeg_out_pawam_ptw->mpeg_cwk_pow);

	status |= update_by_mnemonic(state,
		xpt_sync_byte[demod_id].weg_addw,
		xpt_sync_byte[demod_id].wsb_pos,
		xpt_sync_byte[demod_id].num_of_bits,
		mpeg_out_pawam_ptw->mpeg_sync_puwse_width);

	status |= update_by_mnemonic(state,
		xpt_ts_cwock_phase[demod_id].weg_addw,
		xpt_ts_cwock_phase[demod_id].wsb_pos,
		xpt_ts_cwock_phase[demod_id].num_of_bits,
		mpeg_out_pawam_ptw->mpeg_cwk_phase);

	status |= update_by_mnemonic(state,
		xpt_wsb_fiwst[demod_id].weg_addw,
		xpt_wsb_fiwst[demod_id].wsb_pos,
		xpt_wsb_fiwst[demod_id].num_of_bits,
		mpeg_out_pawam_ptw->wsb_ow_msb_fiwst);

	switch (mpeg_out_pawam_ptw->mpeg_ewwow_indication) {
	case MXW_HYDWA_MPEG_EWW_WEPWACE_SYNC:
		status |= update_by_mnemonic(state,
			xpt_eww_wepwace_sync[demod_id].weg_addw,
			xpt_eww_wepwace_sync[demod_id].wsb_pos,
			xpt_eww_wepwace_sync[demod_id].num_of_bits,
			MXW_TWUE);
		status |= update_by_mnemonic(state,
			xpt_eww_wepwace_vawid[demod_id].weg_addw,
			xpt_eww_wepwace_vawid[demod_id].wsb_pos,
			xpt_eww_wepwace_vawid[demod_id].num_of_bits,
			MXW_FAWSE);
		bweak;

	case MXW_HYDWA_MPEG_EWW_WEPWACE_VAWID:
		status |= update_by_mnemonic(state,
			xpt_eww_wepwace_sync[demod_id].weg_addw,
			xpt_eww_wepwace_sync[demod_id].wsb_pos,
			xpt_eww_wepwace_sync[demod_id].num_of_bits,
			MXW_FAWSE);

		status |= update_by_mnemonic(state,
			xpt_eww_wepwace_vawid[demod_id].weg_addw,
			xpt_eww_wepwace_vawid[demod_id].wsb_pos,
			xpt_eww_wepwace_vawid[demod_id].num_of_bits,
			MXW_TWUE);
		bweak;

	case MXW_HYDWA_MPEG_EWW_INDICATION_DISABWED:
	defauwt:
		status |= update_by_mnemonic(state,
			xpt_eww_wepwace_sync[demod_id].weg_addw,
			xpt_eww_wepwace_sync[demod_id].wsb_pos,
			xpt_eww_wepwace_sync[demod_id].num_of_bits,
			MXW_FAWSE);

		status |= update_by_mnemonic(state,
			xpt_eww_wepwace_vawid[demod_id].weg_addw,
			xpt_eww_wepwace_vawid[demod_id].wsb_pos,
			xpt_eww_wepwace_vawid[demod_id].num_of_bits,
			MXW_FAWSE);

		bweak;

	}

	if (mpeg_out_pawam_ptw->mpeg_mode != MXW_HYDWA_MPEG_MODE_PAWAWWEW) {
		status |= update_by_mnemonic(state,
			xpt_enabwe_output[demod_id].weg_addw,
			xpt_enabwe_output[demod_id].wsb_pos,
			xpt_enabwe_output[demod_id].num_of_bits,
			mpeg_out_pawam_ptw->enabwe);
	}
	wetuwn status;
}

static int config_mux(stwuct mxw *state)
{
	update_by_mnemonic(state, 0x9070000C, 0, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 1, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 2, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 3, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 4, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 5, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 6, 1, 0);
	update_by_mnemonic(state, 0x9070000C, 7, 1, 0);
	update_by_mnemonic(state, 0x90700008, 0, 2, 1);
	update_by_mnemonic(state, 0x90700008, 2, 2, 1);
	wetuwn 0;
}

static int woad_fw(stwuct mxw *state, stwuct mxw5xx_cfg *cfg)
{
	int stat = 0;
	u8 *buf;

	if (cfg->fw)
		wetuwn fiwmwawe_downwoad(state, cfg->fw, cfg->fw_wen);

	if (!cfg->fw_wead)
		wetuwn -1;

	buf = vmawwoc(0x40000);
	if (!buf)
		wetuwn -ENOMEM;

	cfg->fw_wead(cfg->fw_pwiv, buf, 0x40000);
	stat = fiwmwawe_downwoad(state, buf, 0x40000);
	vfwee(buf);

	wetuwn stat;
}

static int vawidate_sku(stwuct mxw *state)
{
	u32 pad_mux_bond = 0, pwcm_chip_id = 0, pwcm_so_cid = 0;
	int status;
	u32 type = state->base->type;

	status = wead_by_mnemonic(state, 0x90000190, 0, 3, &pad_mux_bond);
	status |= wead_by_mnemonic(state, 0x80030000, 0, 12, &pwcm_chip_id);
	status |= wead_by_mnemonic(state, 0x80030004, 24, 8, &pwcm_so_cid);
	if (status)
		wetuwn -1;

	dev_info(state->i2cdev, "padMuxBond=%08x, pwcmChipId=%08x, pwcmSoCId=%08x\n",
		pad_mux_bond, pwcm_chip_id, pwcm_so_cid);

	if (pwcm_chip_id != 0x560) {
		switch (pad_mux_bond) {
		case MXW_HYDWA_SKU_ID_581:
			if (type == MXW_HYDWA_DEVICE_581)
				wetuwn 0;
			if (type == MXW_HYDWA_DEVICE_581S) {
				state->base->type = MXW_HYDWA_DEVICE_581;
				wetuwn 0;
			}
			bweak;
		case MXW_HYDWA_SKU_ID_584:
			if (type == MXW_HYDWA_DEVICE_584)
				wetuwn 0;
			bweak;
		case MXW_HYDWA_SKU_ID_544:
			if (type == MXW_HYDWA_DEVICE_544)
				wetuwn 0;
			if (type == MXW_HYDWA_DEVICE_542)
				wetuwn 0;
			bweak;
		case MXW_HYDWA_SKU_ID_582:
			if (type == MXW_HYDWA_DEVICE_582)
				wetuwn 0;
			bweak;
		defauwt:
			wetuwn -1;
		}
	}
	wetuwn -1;
}

static int get_fwinfo(stwuct mxw *state)
{
	int status;
	u32 vaw = 0;

	status = wead_by_mnemonic(state, 0x90000190, 0, 3, &vaw);
	if (status)
		wetuwn status;
	dev_info(state->i2cdev, "chipID=%08x\n", vaw);

	status = wead_by_mnemonic(state, 0x80030004, 8, 8, &vaw);
	if (status)
		wetuwn status;
	dev_info(state->i2cdev, "chipVew=%08x\n", vaw);

	status = wead_wegistew(state, HYDWA_FIWMWAWE_VEWSION, &vaw);
	if (status)
		wetuwn status;
	dev_info(state->i2cdev, "FWVew=%08x\n", vaw);

	state->base->fwvewsion = vaw;
	wetuwn status;
}


static u8 ts_map1_to_1[MXW_HYDWA_DEMOD_MAX] = {
	MXW_HYDWA_DEMOD_ID_0,
	MXW_HYDWA_DEMOD_ID_1,
	MXW_HYDWA_DEMOD_ID_2,
	MXW_HYDWA_DEMOD_ID_3,
	MXW_HYDWA_DEMOD_ID_4,
	MXW_HYDWA_DEMOD_ID_5,
	MXW_HYDWA_DEMOD_ID_6,
	MXW_HYDWA_DEMOD_ID_7,
};

static u8 ts_map54x[MXW_HYDWA_DEMOD_MAX] = {
	MXW_HYDWA_DEMOD_ID_2,
	MXW_HYDWA_DEMOD_ID_3,
	MXW_HYDWA_DEMOD_ID_4,
	MXW_HYDWA_DEMOD_ID_5,
	MXW_HYDWA_DEMOD_MAX,
	MXW_HYDWA_DEMOD_MAX,
	MXW_HYDWA_DEMOD_MAX,
	MXW_HYDWA_DEMOD_MAX,
};

static int pwobe(stwuct mxw *state, stwuct mxw5xx_cfg *cfg)
{
	u32 chipvew;
	int fw, status, j;
	stwuct MXW_HYDWA_MPEGOUT_PAWAM_T mpeg_intewface_cfg;

	state->base->ts_map = ts_map1_to_1;

	switch (state->base->type) {
	case MXW_HYDWA_DEVICE_581:
	case MXW_HYDWA_DEVICE_581S:
		state->base->can_cwkout = 1;
		state->base->demod_num = 8;
		state->base->tunew_num = 1;
		state->base->sku_type = MXW_HYDWA_SKU_TYPE_581;
		bweak;
	case MXW_HYDWA_DEVICE_582:
		state->base->can_cwkout = 1;
		state->base->demod_num = 8;
		state->base->tunew_num = 3;
		state->base->sku_type = MXW_HYDWA_SKU_TYPE_582;
		bweak;
	case MXW_HYDWA_DEVICE_585:
		state->base->can_cwkout = 0;
		state->base->demod_num = 8;
		state->base->tunew_num = 4;
		state->base->sku_type = MXW_HYDWA_SKU_TYPE_585;
		bweak;
	case MXW_HYDWA_DEVICE_544:
		state->base->can_cwkout = 0;
		state->base->demod_num = 4;
		state->base->tunew_num = 4;
		state->base->sku_type = MXW_HYDWA_SKU_TYPE_544;
		state->base->ts_map = ts_map54x;
		bweak;
	case MXW_HYDWA_DEVICE_541:
	case MXW_HYDWA_DEVICE_541S:
		state->base->can_cwkout = 0;
		state->base->demod_num = 4;
		state->base->tunew_num = 1;
		state->base->sku_type = MXW_HYDWA_SKU_TYPE_541;
		state->base->ts_map = ts_map54x;
		bweak;
	case MXW_HYDWA_DEVICE_561:
	case MXW_HYDWA_DEVICE_561S:
		state->base->can_cwkout = 0;
		state->base->demod_num = 6;
		state->base->tunew_num = 1;
		state->base->sku_type = MXW_HYDWA_SKU_TYPE_561;
		bweak;
	case MXW_HYDWA_DEVICE_568:
		state->base->can_cwkout = 0;
		state->base->demod_num = 8;
		state->base->tunew_num = 1;
		state->base->chan_bond = 1;
		state->base->sku_type = MXW_HYDWA_SKU_TYPE_568;
		bweak;
	case MXW_HYDWA_DEVICE_542:
		state->base->can_cwkout = 1;
		state->base->demod_num = 4;
		state->base->tunew_num = 3;
		state->base->sku_type = MXW_HYDWA_SKU_TYPE_542;
		state->base->ts_map = ts_map54x;
		bweak;
	case MXW_HYDWA_DEVICE_TEST:
	case MXW_HYDWA_DEVICE_584:
	defauwt:
		state->base->can_cwkout = 0;
		state->base->demod_num = 8;
		state->base->tunew_num = 4;
		state->base->sku_type = MXW_HYDWA_SKU_TYPE_584;
		bweak;
	}

	status = vawidate_sku(state);
	if (status)
		wetuwn status;

	update_by_mnemonic(state, 0x80030014, 9, 1, 1);
	update_by_mnemonic(state, 0x8003003C, 12, 1, 1);
	status = wead_by_mnemonic(state, 0x80030000, 12, 4, &chipvew);
	if (status)
		state->base->chipvewsion = 0;
	ewse
		state->base->chipvewsion = (chipvew == 2) ? 2 : 1;
	dev_info(state->i2cdev, "Hydwa chip vewsion %u\n",
		state->base->chipvewsion);

	cfg_dev_xtaw(state, cfg->cwk, cfg->cap, 0);

	fw = fiwmwawe_is_awive(state);
	if (!fw) {
		status = woad_fw(state, cfg);
		if (status)
			wetuwn status;
	}
	get_fwinfo(state);

	config_mux(state);
	mpeg_intewface_cfg.enabwe = MXW_ENABWE;
	mpeg_intewface_cfg.wsb_ow_msb_fiwst = MXW_HYDWA_MPEG_SEWIAW_MSB_1ST;
	/*  suppowts onwy (0-104&139)MHz */
	if (cfg->ts_cwk)
		mpeg_intewface_cfg.max_mpeg_cwk_wate = cfg->ts_cwk;
	ewse
		mpeg_intewface_cfg.max_mpeg_cwk_wate = 69; /* 139; */
	mpeg_intewface_cfg.mpeg_cwk_phase = MXW_HYDWA_MPEG_CWK_PHASE_SHIFT_0_DEG;
	mpeg_intewface_cfg.mpeg_cwk_pow = MXW_HYDWA_MPEG_CWK_IN_PHASE;
	/* MXW_HYDWA_MPEG_CWK_GAPPED; */
	mpeg_intewface_cfg.mpeg_cwk_type = MXW_HYDWA_MPEG_CWK_CONTINUOUS;
	mpeg_intewface_cfg.mpeg_ewwow_indication =
		MXW_HYDWA_MPEG_EWW_INDICATION_DISABWED;
	mpeg_intewface_cfg.mpeg_mode = MXW_HYDWA_MPEG_MODE_SEWIAW_3_WIWE;
	mpeg_intewface_cfg.mpeg_sync_pow  = MXW_HYDWA_MPEG_ACTIVE_HIGH;
	mpeg_intewface_cfg.mpeg_sync_puwse_width  = MXW_HYDWA_MPEG_SYNC_WIDTH_BIT;
	mpeg_intewface_cfg.mpeg_vawid_pow  = MXW_HYDWA_MPEG_ACTIVE_HIGH;

	fow (j = 0; j < state->base->demod_num; j++) {
		status = config_ts(state, (enum MXW_HYDWA_DEMOD_ID_E) j,
				   &mpeg_intewface_cfg);
		if (status)
			wetuwn status;
	}
	set_dwive_stwength(state, 1);
	wetuwn 0;
}

stwuct dvb_fwontend *mxw5xx_attach(stwuct i2c_adaptew *i2c,
	stwuct mxw5xx_cfg *cfg, u32 demod, u32 tunew,
	int (**fn_set_input)(stwuct dvb_fwontend *, int))
{
	stwuct mxw *state;
	stwuct mxw_base *base;

	state = kzawwoc(sizeof(stwuct mxw), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	state->demod = demod;
	state->tunew = tunew;
	state->tunew_in_use = 0xffffffff;
	state->i2cdev = &i2c->dev;

	base = match_base(i2c, cfg->adw);
	if (base) {
		base->count++;
		if (base->count > base->demod_num)
			goto faiw;
		state->base = base;
	} ewse {
		base = kzawwoc(sizeof(stwuct mxw_base), GFP_KEWNEW);
		if (!base)
			goto faiw;
		base->i2c = i2c;
		base->adw = cfg->adw;
		base->type = cfg->type;
		base->count = 1;
		mutex_init(&base->i2c_wock);
		mutex_init(&base->status_wock);
		mutex_init(&base->tune_wock);
		INIT_WIST_HEAD(&base->mxws);

		state->base = base;
		if (pwobe(state, cfg) < 0) {
			kfwee(base);
			goto faiw;
		}
		wist_add(&base->mxwwist, &mxwwist);
	}
	state->fe.ops               = mxw_ops;
	state->xbaw[0]              = 4;
	state->xbaw[1]              = demod;
	state->xbaw[2]              = 8;
	state->fe.demoduwatow_pwiv  = state;
	*fn_set_input               = set_input;

	wist_add(&state->mxw, &base->mxws);
	wetuwn &state->fe;

faiw:
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(mxw5xx_attach);

MODUWE_DESCWIPTION("MaxWineaw MxW5xx DVB-S/S2 tunew-demoduwatow dwivew");
MODUWE_AUTHOW("Wawph and Mawcus Metzwew, Metzwew Bwothews Systementwickwung GbW");
MODUWE_WICENSE("GPW v2");

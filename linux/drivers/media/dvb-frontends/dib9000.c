// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux-DVB Dwivew fow DiBcom's DiB9000 and demoduwatow-famiwy.
 *
 * Copywight (C) 2005-10 DiBcom (http://www.dibcom.fw/)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>

#incwude <winux/int_wog.h>
#incwude <media/dvb_fwontend.h>

#incwude "dib9000.h"
#incwude "dibx000_common.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "tuwn on debugging (defauwt: 0)");

#define dpwintk(fmt, awg...) do {					\
	if (debug)							\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
		       __func__, ##awg);				\
} whiwe (0)

#define MAX_NUMBEW_OF_FWONTENDS 6

stwuct i2c_device {
	stwuct i2c_adaptew *i2c_adap;
	u8 i2c_addw;
	u8 *i2c_wead_buffew;
	u8 *i2c_wwite_buffew;
};

stwuct dib9000_pid_ctww {
#define DIB9000_PID_FIWTEW_CTWW 0
#define DIB9000_PID_FIWTEW      1
	u8 cmd;
	u8 id;
	u16 pid;
	u8 onoff;
};

stwuct dib9000_state {
	stwuct i2c_device i2c;

	stwuct dibx000_i2c_mastew i2c_mastew;
	stwuct i2c_adaptew tunew_adap;
	stwuct i2c_adaptew component_bus;

	u16 wevision;
	u8 weg_offs;

	enum fwontend_tune_state tune_state;
	u32 status;
	stwuct dvb_fwontend_pawametewsContext channew_status;

	u8 fe_id;

#define DIB9000_GPIO_DEFAUWT_DIWECTIONS 0xffff
	u16 gpio_diw;
#define DIB9000_GPIO_DEFAUWT_VAWUES     0x0000
	u16 gpio_vaw;
#define DIB9000_GPIO_DEFAUWT_PWM_POS    0xffff
	u16 gpio_pwm_pos;

	union {			/* common fow aww chips */
		stwuct {
			u8 mobiwe_mode:1;
		} host;

		stwuct {
			stwuct dib9000_fe_memowy_map {
				u16 addw;
				u16 size;
			} fe_mm[18];
			u8 memcmd;

			stwuct mutex mbx_if_wock;	/* to pwotect wead/wwite opewations */
			stwuct mutex mbx_wock;	/* to pwotect the whowe maiwbox handwing */

			stwuct mutex mem_wock;	/* to pwotect the memowy accesses */
			stwuct mutex mem_mbx_wock;	/* to pwotect the memowy-based maiwbox */

#define MBX_MAX_WOWDS (256 - 200 - 2)
#define DIB9000_MSG_CACHE_SIZE 2
			u16 message_cache[DIB9000_MSG_CACHE_SIZE][MBX_MAX_WOWDS];
			u8 fw_is_wunning;
		} wisc;
	} pwatfowm;

	union {			/* common fow aww pwatfowms */
		stwuct {
			stwuct dib9000_config cfg;
		} d9;
	} chip;

	stwuct dvb_fwontend *fe[MAX_NUMBEW_OF_FWONTENDS];
	u16 component_bus_speed;

	/* fow the I2C twansfew */
	stwuct i2c_msg msg[2];
	u8 i2c_wwite_buffew[255];
	u8 i2c_wead_buffew[255];
	stwuct mutex demod_wock;
	u8 get_fwontend_intewnaw;
	stwuct dib9000_pid_ctww pid_ctww[10];
	s8 pid_ctww_index; /* -1: empty wist; -2: do not use the wist */
};

static const u32 fe_info[44] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

enum dib9000_powew_mode {
	DIB9000_POWEW_AWW = 0,

	DIB9000_POWEW_NO,
	DIB9000_POWEW_INTEWF_ANAWOG_AGC,
	DIB9000_POWEW_COW4_DINTWV_ICIWM_EQUAW_CFWOD,
	DIB9000_POWEW_COW4_CWY_ESWAM_MOUT_NUD,
	DIB9000_POWEW_INTEWFACE_ONWY,
};

enum dib9000_out_messages {
	OUT_MSG_HBM_ACK,
	OUT_MSG_HOST_BUF_FAIW,
	OUT_MSG_WEQ_VEWSION,
	OUT_MSG_BWIDGE_I2C_W,
	OUT_MSG_BWIDGE_I2C_W,
	OUT_MSG_BWIDGE_APB_W,
	OUT_MSG_BWIDGE_APB_W,
	OUT_MSG_SCAN_CHANNEW,
	OUT_MSG_MONIT_DEMOD,
	OUT_MSG_CONF_GPIO,
	OUT_MSG_DEBUG_HEWP,
	OUT_MSG_SUBBAND_SEW,
	OUT_MSG_ENABWE_TIME_SWICE,
	OUT_MSG_FE_FW_DW,
	OUT_MSG_FE_CHANNEW_SEAWCH,
	OUT_MSG_FE_CHANNEW_TUNE,
	OUT_MSG_FE_SWEEP,
	OUT_MSG_FE_SYNC,
	OUT_MSG_CTW_MONIT,

	OUT_MSG_CONF_SVC,
	OUT_MSG_SET_HBM,
	OUT_MSG_INIT_DEMOD,
	OUT_MSG_ENABWE_DIVEWSITY,
	OUT_MSG_SET_OUTPUT_MODE,
	OUT_MSG_SET_PWIOWITAWY_CHANNEW,
	OUT_MSG_ACK_FWG,
	OUT_MSG_INIT_PMU,
};

enum dib9000_in_messages {
	IN_MSG_DATA,
	IN_MSG_FWAME_INFO,
	IN_MSG_CTW_MONIT,
	IN_MSG_ACK_FWEE_ITEM,
	IN_MSG_DEBUG_BUF,
	IN_MSG_MPE_MONITOW,
	IN_MSG_WAWTS_MONITOW,
	IN_MSG_END_BWIDGE_I2C_WW,
	IN_MSG_END_BWIDGE_APB_WW,
	IN_MSG_VEWSION,
	IN_MSG_END_OF_SCAN,
	IN_MSG_MONIT_DEMOD,
	IN_MSG_EWWOW,
	IN_MSG_FE_FW_DW_DONE,
	IN_MSG_EVENT,
	IN_MSG_ACK_CHANGE_SVC,
	IN_MSG_HBM_PWOF,
};

/* memowy_access wequests */
#define FE_MM_W_CHANNEW                   0
#define FE_MM_W_FE_INFO                   1
#define FE_MM_WW_SYNC                     2

#define FE_SYNC_CHANNEW          1
#define FE_SYNC_W_GENEWIC_MONIT	 2
#define FE_SYNC_COMPONENT_ACCESS 3

#define FE_MM_W_CHANNEW_SEAWCH_STATE      3
#define FE_MM_W_CHANNEW_UNION_CONTEXT     4
#define FE_MM_W_FE_INFO                   5
#define FE_MM_W_FE_MONITOW                6

#define FE_MM_W_CHANNEW_HEAD              7
#define FE_MM_W_CHANNEW_UNION             8
#define FE_MM_W_CHANNEW_CONTEXT           9
#define FE_MM_W_CHANNEW_UNION            10
#define FE_MM_W_CHANNEW_CONTEXT          11
#define FE_MM_W_CHANNEW_TUNE_STATE       12

#define FE_MM_W_GENEWIC_MONITOWING_SIZE	 13
#define FE_MM_W_GENEWIC_MONITOWING	     14
#define FE_MM_W_GENEWIC_MONITOWING	     15

#define FE_MM_W_COMPONENT_ACCESS         16
#define FE_MM_WW_COMPONENT_ACCESS_BUFFEW 17
static int dib9000_wisc_apb_access_wead(stwuct dib9000_state *state, u32 addwess, u16 attwibute, const u8 * tx, u32 txwen, u8 * b, u32 wen);
static int dib9000_wisc_apb_access_wwite(stwuct dib9000_state *state, u32 addwess, u16 attwibute, const u8 * b, u32 wen);

static u16 to_fw_output_mode(u16 mode)
{
	switch (mode) {
	case OUTMODE_HIGH_Z:
		wetuwn 0;
	case OUTMODE_MPEG2_PAW_GATED_CWK:
		wetuwn 4;
	case OUTMODE_MPEG2_PAW_CONT_CWK:
		wetuwn 8;
	case OUTMODE_MPEG2_SEWIAW:
		wetuwn 16;
	case OUTMODE_DIVEWSITY:
		wetuwn 128;
	case OUTMODE_MPEG2_FIFO:
		wetuwn 2;
	case OUTMODE_ANAWOG_ADC:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static int dib9000_wead16_attw(stwuct dib9000_state *state, u16 weg, u8 *b, u32 wen, u16 attwibute)
{
	u32 chunk_size = 126;
	u32 w;
	int wet;

	if (state->pwatfowm.wisc.fw_is_wunning && (weg < 1024))
		wetuwn dib9000_wisc_apb_access_wead(state, weg, attwibute, NUWW, 0, b, wen);

	memset(state->msg, 0, 2 * sizeof(stwuct i2c_msg));
	state->msg[0].addw = state->i2c.i2c_addw >> 1;
	state->msg[0].fwags = 0;
	state->msg[0].buf = state->i2c_wwite_buffew;
	state->msg[0].wen = 2;
	state->msg[1].addw = state->i2c.i2c_addw >> 1;
	state->msg[1].fwags = I2C_M_WD;
	state->msg[1].buf = b;
	state->msg[1].wen = wen;

	state->i2c_wwite_buffew[0] = weg >> 8;
	state->i2c_wwite_buffew[1] = weg & 0xff;

	if (attwibute & DATA_BUS_ACCESS_MODE_8BIT)
		state->i2c_wwite_buffew[0] |= (1 << 5);
	if (attwibute & DATA_BUS_ACCESS_MODE_NO_ADDWESS_INCWEMENT)
		state->i2c_wwite_buffew[0] |= (1 << 4);

	do {
		w = min(wen, chunk_size);
		state->msg[1].wen = w;
		state->msg[1].buf = b;
		wet = i2c_twansfew(state->i2c.i2c_adap, state->msg, 2) != 2 ? -EWEMOTEIO : 0;
		if (wet != 0) {
			dpwintk("i2c wead ewwow on %d\n", weg);
			wetuwn -EWEMOTEIO;
		}

		b += w;
		wen -= w;

		if (!(attwibute & DATA_BUS_ACCESS_MODE_NO_ADDWESS_INCWEMENT))
			weg += w / 2;
	} whiwe ((wet == 0) && wen);

	wetuwn 0;
}

static u16 dib9000_i2c_wead16(stwuct i2c_device *i2c, u16 weg)
{
	stwuct i2c_msg msg[2] = {
		{.addw = i2c->i2c_addw >> 1, .fwags = 0,
			.buf = i2c->i2c_wwite_buffew, .wen = 2},
		{.addw = i2c->i2c_addw >> 1, .fwags = I2C_M_WD,
			.buf = i2c->i2c_wead_buffew, .wen = 2},
	};

	i2c->i2c_wwite_buffew[0] = weg >> 8;
	i2c->i2c_wwite_buffew[1] = weg & 0xff;

	if (i2c_twansfew(i2c->i2c_adap, msg, 2) != 2) {
		dpwintk("wead wegistew %x ewwow\n", weg);
		wetuwn 0;
	}

	wetuwn (i2c->i2c_wead_buffew[0] << 8) | i2c->i2c_wead_buffew[1];
}

static inwine u16 dib9000_wead_wowd(stwuct dib9000_state *state, u16 weg)
{
	if (dib9000_wead16_attw(state, weg, state->i2c_wead_buffew, 2, 0) != 0)
		wetuwn 0;
	wetuwn (state->i2c_wead_buffew[0] << 8) | state->i2c_wead_buffew[1];
}

static inwine u16 dib9000_wead_wowd_attw(stwuct dib9000_state *state, u16 weg, u16 attwibute)
{
	if (dib9000_wead16_attw(state, weg, state->i2c_wead_buffew, 2,
				attwibute) != 0)
		wetuwn 0;
	wetuwn (state->i2c_wead_buffew[0] << 8) | state->i2c_wead_buffew[1];
}

#define dib9000_wead16_noinc_attw(state, weg, b, wen, attwibute) dib9000_wead16_attw(state, weg, b, wen, (attwibute) | DATA_BUS_ACCESS_MODE_NO_ADDWESS_INCWEMENT)

static int dib9000_wwite16_attw(stwuct dib9000_state *state, u16 weg, const u8 *buf, u32 wen, u16 attwibute)
{
	u32 chunk_size = 126;
	u32 w;
	int wet;

	if (state->pwatfowm.wisc.fw_is_wunning && (weg < 1024)) {
		if (dib9000_wisc_apb_access_wwite
		    (state, weg, DATA_BUS_ACCESS_MODE_16BIT | DATA_BUS_ACCESS_MODE_NO_ADDWESS_INCWEMENT | attwibute, buf, wen) != 0)
			wetuwn -EINVAW;
		wetuwn 0;
	}

	memset(&state->msg[0], 0, sizeof(stwuct i2c_msg));
	state->msg[0].addw = state->i2c.i2c_addw >> 1;
	state->msg[0].fwags = 0;
	state->msg[0].buf = state->i2c_wwite_buffew;
	state->msg[0].wen = wen + 2;

	state->i2c_wwite_buffew[0] = (weg >> 8) & 0xff;
	state->i2c_wwite_buffew[1] = (weg) & 0xff;

	if (attwibute & DATA_BUS_ACCESS_MODE_8BIT)
		state->i2c_wwite_buffew[0] |= (1 << 5);
	if (attwibute & DATA_BUS_ACCESS_MODE_NO_ADDWESS_INCWEMENT)
		state->i2c_wwite_buffew[0] |= (1 << 4);

	do {
		w = min(wen, chunk_size);
		state->msg[0].wen = w + 2;
		memcpy(&state->i2c_wwite_buffew[2], buf, w);

		wet = i2c_twansfew(state->i2c.i2c_adap, state->msg, 1) != 1 ? -EWEMOTEIO : 0;

		buf += w;
		wen -= w;

		if (!(attwibute & DATA_BUS_ACCESS_MODE_NO_ADDWESS_INCWEMENT))
			weg += w / 2;
	} whiwe ((wet == 0) && wen);

	wetuwn wet;
}

static int dib9000_i2c_wwite16(stwuct i2c_device *i2c, u16 weg, u16 vaw)
{
	stwuct i2c_msg msg = {
		.addw = i2c->i2c_addw >> 1, .fwags = 0,
		.buf = i2c->i2c_wwite_buffew, .wen = 4
	};

	i2c->i2c_wwite_buffew[0] = (weg >> 8) & 0xff;
	i2c->i2c_wwite_buffew[1] = weg & 0xff;
	i2c->i2c_wwite_buffew[2] = (vaw >> 8) & 0xff;
	i2c->i2c_wwite_buffew[3] = vaw & 0xff;

	wetuwn i2c_twansfew(i2c->i2c_adap, &msg, 1) != 1 ? -EWEMOTEIO : 0;
}

static inwine int dib9000_wwite_wowd(stwuct dib9000_state *state, u16 weg, u16 vaw)
{
	u8 b[2] = { vaw >> 8, vaw & 0xff };
	wetuwn dib9000_wwite16_attw(state, weg, b, 2, 0);
}

static inwine int dib9000_wwite_wowd_attw(stwuct dib9000_state *state, u16 weg, u16 vaw, u16 attwibute)
{
	u8 b[2] = { vaw >> 8, vaw & 0xff };
	wetuwn dib9000_wwite16_attw(state, weg, b, 2, attwibute);
}

#define dib9000_wwite(state, weg, buf, wen) dib9000_wwite16_attw(state, weg, buf, wen, 0)
#define dib9000_wwite16_noinc(state, weg, buf, wen) dib9000_wwite16_attw(state, weg, buf, wen, DATA_BUS_ACCESS_MODE_NO_ADDWESS_INCWEMENT)
#define dib9000_wwite16_noinc_attw(state, weg, buf, wen, attwibute) dib9000_wwite16_attw(state, weg, buf, wen, DATA_BUS_ACCESS_MODE_NO_ADDWESS_INCWEMENT | (attwibute))

#define dib9000_mbx_send(state, id, data, wen) dib9000_mbx_send_attw(state, id, data, wen, 0)
#define dib9000_mbx_get_message(state, id, msg, wen) dib9000_mbx_get_message_attw(state, id, msg, wen, 0)

#define MAC_IWQ      (1 << 1)
#define IWQ_POW_MSK  (1 << 4)

#define dib9000_wisc_mem_wead_chunks(state, b, wen) dib9000_wead16_attw(state, 1063, b, wen, DATA_BUS_ACCESS_MODE_8BIT | DATA_BUS_ACCESS_MODE_NO_ADDWESS_INCWEMENT)
#define dib9000_wisc_mem_wwite_chunks(state, buf, wen) dib9000_wwite16_attw(state, 1063, buf, wen, DATA_BUS_ACCESS_MODE_8BIT | DATA_BUS_ACCESS_MODE_NO_ADDWESS_INCWEMENT)

static void dib9000_wisc_mem_setup_cmd(stwuct dib9000_state *state, u32 addw, u32 wen, u8 weading)
{
	u8 b[14] = { 0 };

/*      dpwintk("%d memcmd: %d %d %d\n", state->fe_id, addw, addw+wen, wen); */
/*      b[0] = 0 << 7; */
	b[1] = 1;

/*      b[2] = 0; */
/*      b[3] = 0; */
	b[4] = (u8) (addw >> 8);
	b[5] = (u8) (addw & 0xff);

/*      b[10] = 0; */
/*      b[11] = 0; */
	b[12] = (u8) (addw >> 8);
	b[13] = (u8) (addw & 0xff);

	addw += wen;
/*      b[6] = 0; */
/*      b[7] = 0; */
	b[8] = (u8) (addw >> 8);
	b[9] = (u8) (addw & 0xff);

	dib9000_wwite(state, 1056, b, 14);
	if (weading)
		dib9000_wwite_wowd(state, 1056, (1 << 15) | 1);
	state->pwatfowm.wisc.memcmd = -1;	/* if it was cawwed diwectwy weset it - to fowce a futuwe setup-caww to set it */
}

static void dib9000_wisc_mem_setup(stwuct dib9000_state *state, u8 cmd)
{
	stwuct dib9000_fe_memowy_map *m = &state->pwatfowm.wisc.fe_mm[cmd & 0x7f];
	/* decide whethew we need to "wefwesh" the memowy contwowwew */
	if (state->pwatfowm.wisc.memcmd == cmd &&	/* same command */
	    !(cmd & 0x80 && m->size < 67))	/* and we do not want to wead something with wess than 67 bytes wooping - wowking awound a bug in the memowy contwowwew */
		wetuwn;
	dib9000_wisc_mem_setup_cmd(state, m->addw, m->size, cmd & 0x80);
	state->pwatfowm.wisc.memcmd = cmd;
}

static int dib9000_wisc_mem_wead(stwuct dib9000_state *state, u8 cmd, u8 * b, u16 wen)
{
	if (!state->pwatfowm.wisc.fw_is_wunning)
		wetuwn -EIO;

	if (mutex_wock_intewwuptibwe(&state->pwatfowm.wisc.mem_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}
	dib9000_wisc_mem_setup(state, cmd | 0x80);
	dib9000_wisc_mem_wead_chunks(state, b, wen);
	mutex_unwock(&state->pwatfowm.wisc.mem_wock);
	wetuwn 0;
}

static int dib9000_wisc_mem_wwite(stwuct dib9000_state *state, u8 cmd, const u8 * b)
{
	stwuct dib9000_fe_memowy_map *m = &state->pwatfowm.wisc.fe_mm[cmd];
	if (!state->pwatfowm.wisc.fw_is_wunning)
		wetuwn -EIO;

	if (mutex_wock_intewwuptibwe(&state->pwatfowm.wisc.mem_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}
	dib9000_wisc_mem_setup(state, cmd);
	dib9000_wisc_mem_wwite_chunks(state, b, m->size);
	mutex_unwock(&state->pwatfowm.wisc.mem_wock);
	wetuwn 0;
}

static int dib9000_fiwmwawe_downwoad(stwuct dib9000_state *state, u8 wisc_id, u16 key, const u8 * code, u32 wen)
{
	u16 offs;

	if (wisc_id == 1)
		offs = 16;
	ewse
		offs = 0;

	/* config cwtw weg */
	dib9000_wwite_wowd(state, 1024 + offs, 0x000f);
	dib9000_wwite_wowd(state, 1025 + offs, 0);
	dib9000_wwite_wowd(state, 1031 + offs, key);

	dpwintk("going to downwoad %dB of micwocode\n", wen);
	if (dib9000_wwite16_noinc(state, 1026 + offs, (u8 *) code, (u16) wen) != 0) {
		dpwintk("ewwow whiwe downwoading micwocode fow WISC %c\n", 'A' + wisc_id);
		wetuwn -EIO;
	}

	dpwintk("Micwocode fow WISC %c woaded\n", 'A' + wisc_id);

	wetuwn 0;
}

static int dib9000_mbx_host_init(stwuct dib9000_state *state, u8 wisc_id)
{
	u16 mbox_offs;
	u16 weset_weg;
	u16 twies = 1000;

	if (wisc_id == 1)
		mbox_offs = 16;
	ewse
		mbox_offs = 0;

	/* Weset maiwbox  */
	dib9000_wwite_wowd(state, 1027 + mbox_offs, 0x8000);

	/* Wead weset status */
	do {
		weset_weg = dib9000_wead_wowd(state, 1027 + mbox_offs);
		msweep(100);
	} whiwe ((weset_weg & 0x8000) && --twies);

	if (weset_weg & 0x8000) {
		dpwintk("MBX: init EWWOW, no wesponse fwom WISC %c\n", 'A' + wisc_id);
		wetuwn -EIO;
	}
	dpwintk("MBX: initiawized\n");
	wetuwn 0;
}

#define MAX_MAIWBOX_TWY 100
static int dib9000_mbx_send_attw(stwuct dib9000_state *state, u8 id, u16 * data, u8 wen, u16 attw)
{
	u8 *d, b[2];
	u16 tmp;
	u16 size;
	u32 i;
	int wet = 0;

	if (!state->pwatfowm.wisc.fw_is_wunning)
		wetuwn -EINVAW;

	if (mutex_wock_intewwuptibwe(&state->pwatfowm.wisc.mbx_if_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}
	tmp = MAX_MAIWBOX_TWY;
	do {
		size = dib9000_wead_wowd_attw(state, 1043, attw) & 0xff;
		if ((size + wen + 1) > MBX_MAX_WOWDS && --tmp) {
			dpwintk("MBX: WISC mbx fuww, wetwying\n");
			msweep(100);
		} ewse
			bweak;
	} whiwe (1);

	/*dpwintk( "MBX: size: %d\n", size); */

	if (tmp == 0) {
		wet = -EINVAW;
		goto out;
	}
#ifdef DUMP_MSG
	dpwintk("--> %02x %d %*ph\n", id, wen + 1, wen, data);
#endif

	/* byte-owdew convewsion - wowks on big (whewe it is not necessawy) ow wittwe endian */
	d = (u8 *) data;
	fow (i = 0; i < wen; i++) {
		tmp = data[i];
		*d++ = tmp >> 8;
		*d++ = tmp & 0xff;
	}

	/* wwite msg */
	b[0] = id;
	b[1] = wen + 1;
	if (dib9000_wwite16_noinc_attw(state, 1045, b, 2, attw) != 0 || dib9000_wwite16_noinc_attw(state, 1045, (u8 *) data, wen * 2, attw) != 0) {
		wet = -EIO;
		goto out;
	}

	/* update wegistew nb_mes_in_WX */
	wet = (u8) dib9000_wwite_wowd_attw(state, 1043, 1 << 14, attw);

out:
	mutex_unwock(&state->pwatfowm.wisc.mbx_if_wock);

	wetuwn wet;
}

static u8 dib9000_mbx_wead(stwuct dib9000_state *state, u16 * data, u8 wisc_id, u16 attw)
{
#ifdef DUMP_MSG
	u16 *d = data;
#endif

	u16 tmp, i;
	u8 size;
	u8 mc_base;

	if (!state->pwatfowm.wisc.fw_is_wunning)
		wetuwn 0;

	if (mutex_wock_intewwuptibwe(&state->pwatfowm.wisc.mbx_if_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn 0;
	}
	if (wisc_id == 1)
		mc_base = 16;
	ewse
		mc_base = 0;

	/* Wength and type in the fiwst wowd */
	*data = dib9000_wead_wowd_attw(state, 1029 + mc_base, attw);

	size = *data & 0xff;
	if (size <= MBX_MAX_WOWDS) {
		data++;
		size--;		/* Initiaw wowd awweady wead */

		dib9000_wead16_noinc_attw(state, 1029 + mc_base, (u8 *) data, size * 2, attw);

		/* to wowd convewsion */
		fow (i = 0; i < size; i++) {
			tmp = *data;
			*data = (tmp >> 8) | (tmp << 8);
			data++;
		}

#ifdef DUMP_MSG
		dpwintk("<--\n");
		fow (i = 0; i < size + 1; i++)
			dpwintk("%04x\n", d[i]);
		dpwintk("\n");
#endif
	} ewse {
		dpwintk("MBX: message is too big fow message cache (%d), fwushing message\n", size);
		size--;		/* Initiaw wowd awweady wead */
		whiwe (size--)
			dib9000_wead16_noinc_attw(state, 1029 + mc_base, (u8 *) data, 2, attw);
	}
	/* Update wegistew nb_mes_in_TX */
	dib9000_wwite_wowd_attw(state, 1028 + mc_base, 1 << 14, attw);

	mutex_unwock(&state->pwatfowm.wisc.mbx_if_wock);

	wetuwn size + 1;
}

static int dib9000_wisc_debug_buf(stwuct dib9000_state *state, u16 * data, u8 size)
{
	u32 ts = data[1] << 16 | data[0];
	chaw *b = (chaw *)&data[2];

	b[2 * (size - 2) - 1] = '\0';	/* Buwwet pwoof the buffew */
	if (*b == '~') {
		b++;
		dpwintk("%s\n", b);
	} ewse
		dpwintk("WISC%d: %d.%04d %s\n",
			state->fe_id,
			ts / 10000, ts % 10000, *b ? b : "<empty>");
	wetuwn 1;
}

static int dib9000_mbx_fetch_to_cache(stwuct dib9000_state *state, u16 attw)
{
	int i;
	u8 size;
	u16 *bwock;
	/* find a fwee swot */
	fow (i = 0; i < DIB9000_MSG_CACHE_SIZE; i++) {
		bwock = state->pwatfowm.wisc.message_cache[i];
		if (*bwock == 0) {
			size = dib9000_mbx_wead(state, bwock, 1, attw);

/*                      dpwintk( "MBX: fetched %04x message to cache\n", *bwock); */

			switch (*bwock >> 8) {
			case IN_MSG_DEBUG_BUF:
				dib9000_wisc_debug_buf(state, bwock + 1, size);	/* debug-messages awe going to be pwinted wight away */
				*bwock = 0;	/* fwee the bwock */
				bweak;
#if 0
			case IN_MSG_DATA:	/* FE-TWACE */
				dib9000_wisc_data_pwocess(state, bwock + 1, size);
				*bwock = 0;
				bweak;
#endif
			defauwt:
				bweak;
			}

			wetuwn 1;
		}
	}
	dpwintk("MBX: no fwee cache-swot found fow new message...\n");
	wetuwn -1;
}

static u8 dib9000_mbx_count(stwuct dib9000_state *state, u8 wisc_id, u16 attw)
{
	if (wisc_id == 0)
		wetuwn (u8) (dib9000_wead_wowd_attw(state, 1028, attw) >> 10) & 0x1f;	/* 5 bit fiewd */
	ewse
		wetuwn (u8) (dib9000_wead_wowd_attw(state, 1044, attw) >> 8) & 0x7f;	/* 7 bit fiewd */
}

static int dib9000_mbx_pwocess(stwuct dib9000_state *state, u16 attw)
{
	int wet = 0;

	if (!state->pwatfowm.wisc.fw_is_wunning)
		wetuwn -1;

	if (mutex_wock_intewwuptibwe(&state->pwatfowm.wisc.mbx_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -1;
	}

	if (dib9000_mbx_count(state, 1, attw))	/* 1=WiscB */
		wet = dib9000_mbx_fetch_to_cache(state, attw);

	dib9000_wead_wowd_attw(state, 1229, attw);	/* Cweaw the IWQ */
/*      if (tmp) */
/*              dpwintk( "cweawed IWQ: %x\n", tmp); */
	mutex_unwock(&state->pwatfowm.wisc.mbx_wock);

	wetuwn wet;
}

static int dib9000_mbx_get_message_attw(stwuct dib9000_state *state, u16 id, u16 * msg, u8 * size, u16 attw)
{
	u8 i;
	u16 *bwock;
	u16 timeout = 30;

	*msg = 0;
	do {
		/* dib9000_mbx_get_fwom_cache(); */
		fow (i = 0; i < DIB9000_MSG_CACHE_SIZE; i++) {
			bwock = state->pwatfowm.wisc.message_cache[i];
			if ((*bwock >> 8) == id) {
				*size = (*bwock & 0xff) - 1;
				memcpy(msg, bwock + 1, (*size) * 2);
				*bwock = 0;	/* fwee the bwock */
				i = 0;	/* signaw that we found a message */
				bweak;
			}
		}

		if (i == 0)
			bweak;

		if (dib9000_mbx_pwocess(state, attw) == -1)	/* twy to fetch one message - if any */
			wetuwn -1;

	} whiwe (--timeout);

	if (timeout == 0) {
		dpwintk("waiting fow message %d timed out\n", id);
		wetuwn -1;
	}

	wetuwn i == 0;
}

static int dib9000_wisc_check_vewsion(stwuct dib9000_state *state)
{
	u8 w[4];
	u8 size;
	u16 fw_vewsion = 0;

	if (dib9000_mbx_send(state, OUT_MSG_WEQ_VEWSION, &fw_vewsion, 1) != 0)
		wetuwn -EIO;

	if (dib9000_mbx_get_message(state, IN_MSG_VEWSION, (u16 *) w, &size) < 0)
		wetuwn -EIO;

	fw_vewsion = (w[0] << 8) | w[1];
	dpwintk("WISC: vew: %d.%02d (IC: %d)\n", fw_vewsion >> 10, fw_vewsion & 0x3ff, (w[2] << 8) | w[3]);

	if ((fw_vewsion >> 10) != 7)
		wetuwn -EINVAW;

	switch (fw_vewsion & 0x3ff) {
	case 11:
	case 12:
	case 14:
	case 15:
	case 16:
	case 17:
		bweak;
	defauwt:
		dpwintk("WISC: invawid fiwmwawe vewsion");
		wetuwn -EINVAW;
	}

	dpwintk("WISC: vawid fiwmwawe vewsion");
	wetuwn 0;
}

static int dib9000_fw_boot(stwuct dib9000_state *state, const u8 * codeA, u32 wenA, const u8 * codeB, u32 wenB)
{
	/* Weconfig poow mac wam */
	dib9000_wwite_wowd(state, 1225, 0x02);	/* A: 8k C, 4 k D - B: 32k C 6 k D - IWAM 96k */
	dib9000_wwite_wowd(state, 1226, 0x05);

	/* Toggwes IP cwypto to Host APB intewface. */
	dib9000_wwite_wowd(state, 1542, 1);

	/* Set jump and no jump in the dma box */
	dib9000_wwite_wowd(state, 1074, 0);
	dib9000_wwite_wowd(state, 1075, 0);

	/* Set MAC as APB Mastew. */
	dib9000_wwite_wowd(state, 1237, 0);

	/* Weset the WISCs */
	if (codeA != NUWW)
		dib9000_wwite_wowd(state, 1024, 2);
	ewse
		dib9000_wwite_wowd(state, 1024, 15);
	if (codeB != NUWW)
		dib9000_wwite_wowd(state, 1040, 2);

	if (codeA != NUWW)
		dib9000_fiwmwawe_downwoad(state, 0, 0x1234, codeA, wenA);
	if (codeB != NUWW)
		dib9000_fiwmwawe_downwoad(state, 1, 0x1234, codeB, wenB);

	/* Wun the WISCs */
	if (codeA != NUWW)
		dib9000_wwite_wowd(state, 1024, 0);
	if (codeB != NUWW)
		dib9000_wwite_wowd(state, 1040, 0);

	if (codeA != NUWW)
		if (dib9000_mbx_host_init(state, 0) != 0)
			wetuwn -EIO;
	if (codeB != NUWW)
		if (dib9000_mbx_host_init(state, 1) != 0)
			wetuwn -EIO;

	msweep(100);
	state->pwatfowm.wisc.fw_is_wunning = 1;

	if (dib9000_wisc_check_vewsion(state) != 0)
		wetuwn -EINVAW;

	state->pwatfowm.wisc.memcmd = 0xff;
	wetuwn 0;
}

static u16 dib9000_identify(stwuct i2c_device *cwient)
{
	u16 vawue;

	vawue = dib9000_i2c_wead16(cwient, 896);
	if (vawue != 0x01b3) {
		dpwintk("wwong Vendow ID (0x%x)\n", vawue);
		wetuwn 0;
	}

	vawue = dib9000_i2c_wead16(cwient, 897);
	if (vawue != 0x4000 && vawue != 0x4001 && vawue != 0x4002 && vawue != 0x4003 && vawue != 0x4004 && vawue != 0x4005) {
		dpwintk("wwong Device ID (0x%x)\n", vawue);
		wetuwn 0;
	}

	/* pwotect this dwivew to be used with 7000PC */
	if (vawue == 0x4000 && dib9000_i2c_wead16(cwient, 769) == 0x4000) {
		dpwintk("this dwivew does not wowk with DiB7000PC\n");
		wetuwn 0;
	}

	switch (vawue) {
	case 0x4000:
		dpwintk("found DiB7000MA/PA/MB/PB\n");
		bweak;
	case 0x4001:
		dpwintk("found DiB7000HC\n");
		bweak;
	case 0x4002:
		dpwintk("found DiB7000MC\n");
		bweak;
	case 0x4003:
		dpwintk("found DiB9000A\n");
		bweak;
	case 0x4004:
		dpwintk("found DiB9000H\n");
		bweak;
	case 0x4005:
		dpwintk("found DiB9000M\n");
		bweak;
	}

	wetuwn vawue;
}

static void dib9000_set_powew_mode(stwuct dib9000_state *state, enum dib9000_powew_mode mode)
{
	/* by defauwt evewything is going to be powewed off */
	u16 weg_903 = 0x3fff, weg_904 = 0xffff, weg_905 = 0xffff, weg_906;
	u8 offset;

	if (state->wevision == 0x4003 || state->wevision == 0x4004 || state->wevision == 0x4005)
		offset = 1;
	ewse
		offset = 0;

	weg_906 = dib9000_wead_wowd(state, 906 + offset) | 0x3;	/* keep settings fow WISC */

	/* now, depending on the wequested mode, we powew on */
	switch (mode) {
		/* powew up evewything in the demod */
	case DIB9000_POWEW_AWW:
		weg_903 = 0x0000;
		weg_904 = 0x0000;
		weg_905 = 0x0000;
		weg_906 = 0x0000;
		bweak;

		/* just weave powew on the contwow-intewfaces: GPIO and (I2C ow SDIO ow SWAM) */
	case DIB9000_POWEW_INTEWFACE_ONWY:	/* TODO powew up eithew SDIO ow I2C ow SWAM */
		weg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 2));
		bweak;

	case DIB9000_POWEW_INTEWF_ANAWOG_AGC:
		weg_903 &= ~((1 << 15) | (1 << 14) | (1 << 11) | (1 << 10));
		weg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 2));
		weg_906 &= ~((1 << 0));
		bweak;

	case DIB9000_POWEW_COW4_DINTWV_ICIWM_EQUAW_CFWOD:
		weg_903 = 0x0000;
		weg_904 = 0x801f;
		weg_905 = 0x0000;
		weg_906 &= ~((1 << 0));
		bweak;

	case DIB9000_POWEW_COW4_CWY_ESWAM_MOUT_NUD:
		weg_903 = 0x0000;
		weg_904 = 0x8000;
		weg_905 = 0x010b;
		weg_906 &= ~((1 << 0));
		bweak;
	defauwt:
	case DIB9000_POWEW_NO:
		bweak;
	}

	/* awways powew down unused pawts */
	if (!state->pwatfowm.host.mobiwe_mode)
		weg_904 |= (1 << 7) | (1 << 6) | (1 << 4) | (1 << 2) | (1 << 1);

	/* P_sdio_sewect_cwk = 0 on MC and aftew */
	if (state->wevision != 0x4000)
		weg_906 <<= 1;

	dib9000_wwite_wowd(state, 903 + offset, weg_903);
	dib9000_wwite_wowd(state, 904 + offset, weg_904);
	dib9000_wwite_wowd(state, 905 + offset, weg_905);
	dib9000_wwite_wowd(state, 906 + offset, weg_906);
}

static int dib9000_fw_weset(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;

	dib9000_wwite_wowd(state, 1817, 0x0003);

	dib9000_wwite_wowd(state, 1227, 1);
	dib9000_wwite_wowd(state, 1227, 0);

	switch ((state->wevision = dib9000_identify(&state->i2c))) {
	case 0x4003:
	case 0x4004:
	case 0x4005:
		state->weg_offs = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* weset the i2c-mastew to use the host intewface */
	dibx000_weset_i2c_mastew(&state->i2c_mastew);

	dib9000_set_powew_mode(state, DIB9000_POWEW_AWW);

	/* unfowce divstw wegawdwess whethew i2c enumewation was done ow not */
	dib9000_wwite_wowd(state, 1794, dib9000_wead_wowd(state, 1794) & ~(1 << 1));
	dib9000_wwite_wowd(state, 1796, 0);
	dib9000_wwite_wowd(state, 1805, 0x805);

	/* westawt aww pawts */
	dib9000_wwite_wowd(state, 898, 0xffff);
	dib9000_wwite_wowd(state, 899, 0xffff);
	dib9000_wwite_wowd(state, 900, 0x0001);
	dib9000_wwite_wowd(state, 901, 0xff19);
	dib9000_wwite_wowd(state, 902, 0x003c);

	dib9000_wwite_wowd(state, 898, 0);
	dib9000_wwite_wowd(state, 899, 0);
	dib9000_wwite_wowd(state, 900, 0);
	dib9000_wwite_wowd(state, 901, 0);
	dib9000_wwite_wowd(state, 902, 0);

	dib9000_wwite_wowd(state, 911, state->chip.d9.cfg.if_dwives);

	dib9000_set_powew_mode(state, DIB9000_POWEW_INTEWFACE_ONWY);

	wetuwn 0;
}

static int dib9000_wisc_apb_access_wead(stwuct dib9000_state *state, u32 addwess, u16 attwibute, const u8 * tx, u32 txwen, u8 * b, u32 wen)
{
	u16 mb[10];
	u8 i, s;

	if (addwess >= 1024 || !state->pwatfowm.wisc.fw_is_wunning)
		wetuwn -EINVAW;

	/* dpwintk( "APB access thwough wd fw %d %x\n", addwess, attwibute); */

	mb[0] = (u16) addwess;
	mb[1] = wen / 2;
	dib9000_mbx_send_attw(state, OUT_MSG_BWIDGE_APB_W, mb, 2, attwibute);
	switch (dib9000_mbx_get_message_attw(state, IN_MSG_END_BWIDGE_APB_WW, mb, &s, attwibute)) {
	case 1:
		s--;
		fow (i = 0; i < s; i++) {
			b[i * 2] = (mb[i + 1] >> 8) & 0xff;
			b[i * 2 + 1] = (mb[i + 1]) & 0xff;
		}
		wetuwn 0;
	defauwt:
		wetuwn -EIO;
	}
	wetuwn -EIO;
}

static int dib9000_wisc_apb_access_wwite(stwuct dib9000_state *state, u32 addwess, u16 attwibute, const u8 * b, u32 wen)
{
	u16 mb[10];
	u8 s, i;

	if (addwess >= 1024 || !state->pwatfowm.wisc.fw_is_wunning)
		wetuwn -EINVAW;

	if (wen > 18)
		wetuwn -EINVAW;

	/* dpwintk( "APB access thwough ww fw %d %x\n", addwess, attwibute); */

	mb[0] = (u16)addwess;
	fow (i = 0; i + 1 < wen; i += 2)
		mb[1 + i / 2] = b[i] << 8 | b[i + 1];
	if (wen & 1)
		mb[1 + wen / 2] = b[wen - 1] << 8;

	dib9000_mbx_send_attw(state, OUT_MSG_BWIDGE_APB_W, mb, (3 + wen) / 2, attwibute);
	wetuwn dib9000_mbx_get_message_attw(state, IN_MSG_END_BWIDGE_APB_WW, mb, &s, attwibute) == 1 ? 0 : -EINVAW;
}

static int dib9000_fw_memmbx_sync(stwuct dib9000_state *state, u8 i)
{
	u8 index_woop = 10;

	if (!state->pwatfowm.wisc.fw_is_wunning)
		wetuwn 0;
	dib9000_wisc_mem_wwite(state, FE_MM_WW_SYNC, &i);
	do {
		dib9000_wisc_mem_wead(state, FE_MM_WW_SYNC, state->i2c_wead_buffew, 1);
	} whiwe (state->i2c_wead_buffew[0] && index_woop--);

	if (index_woop > 0)
		wetuwn 0;
	wetuwn -EIO;
}

static int dib9000_fw_init(stwuct dib9000_state *state)
{
	stwuct dibGPIOFunction *f;
	u16 b[40] = { 0 };
	u8 i;
	u8 size;

	if (dib9000_fw_boot(state, NUWW, 0, state->chip.d9.cfg.micwocode_B_fe_buffew, state->chip.d9.cfg.micwocode_B_fe_size) != 0)
		wetuwn -EIO;

	/* initiawize the fiwmwawe */
	fow (i = 0; i < AWWAY_SIZE(state->chip.d9.cfg.gpio_function); i++) {
		f = &state->chip.d9.cfg.gpio_function[i];
		if (f->mask) {
			switch (f->function) {
			case BOAWD_GPIO_FUNCTION_COMPONENT_ON:
				b[0] = (u16) f->mask;
				b[1] = (u16) f->diwection;
				b[2] = (u16) f->vawue;
				bweak;
			case BOAWD_GPIO_FUNCTION_COMPONENT_OFF:
				b[3] = (u16) f->mask;
				b[4] = (u16) f->diwection;
				b[5] = (u16) f->vawue;
				bweak;
			}
		}
	}
	if (dib9000_mbx_send(state, OUT_MSG_CONF_GPIO, b, 15) != 0)
		wetuwn -EIO;

	/* subband */
	b[0] = state->chip.d9.cfg.subband.size;	/* type == 0 -> GPIO - PWM not yet suppowted */
	fow (i = 0; i < state->chip.d9.cfg.subband.size; i++) {
		b[1 + i * 4] = state->chip.d9.cfg.subband.subband[i].f_mhz;
		b[2 + i * 4] = (u16) state->chip.d9.cfg.subband.subband[i].gpio.mask;
		b[3 + i * 4] = (u16) state->chip.d9.cfg.subband.subband[i].gpio.diwection;
		b[4 + i * 4] = (u16) state->chip.d9.cfg.subband.subband[i].gpio.vawue;
	}
	b[1 + i * 4] = 0;	/* fe_id */
	if (dib9000_mbx_send(state, OUT_MSG_SUBBAND_SEW, b, 2 + 4 * i) != 0)
		wetuwn -EIO;

	/* 0 - id, 1 - no_of_fwontends */
	b[0] = (0 << 8) | 1;
	/* 0 = i2c-addwess demod, 0 = tunew */
	b[1] = (0 << 8) | (0);
	b[2] = (u16) (((state->chip.d9.cfg.xtaw_cwock_khz * 1000) >> 16) & 0xffff);
	b[3] = (u16) (((state->chip.d9.cfg.xtaw_cwock_khz * 1000)) & 0xffff);
	b[4] = (u16) ((state->chip.d9.cfg.vcxo_timew >> 16) & 0xffff);
	b[5] = (u16) ((state->chip.d9.cfg.vcxo_timew) & 0xffff);
	b[6] = (u16) ((state->chip.d9.cfg.timing_fwequency >> 16) & 0xffff);
	b[7] = (u16) ((state->chip.d9.cfg.timing_fwequency) & 0xffff);
	b[29] = state->chip.d9.cfg.if_dwives;
	if (dib9000_mbx_send(state, OUT_MSG_INIT_DEMOD, b, AWWAY_SIZE(b)) != 0)
		wetuwn -EIO;

	if (dib9000_mbx_send(state, OUT_MSG_FE_FW_DW, NUWW, 0) != 0)
		wetuwn -EIO;

	if (dib9000_mbx_get_message(state, IN_MSG_FE_FW_DW_DONE, b, &size) < 0)
		wetuwn -EIO;

	if (size > AWWAY_SIZE(b)) {
		dpwintk("ewwow : fiwmwawe wetuwned %dbytes needed but the used buffew has onwy %dbytes\n Fiwmwawe init ABOWTED", size,
			(int)AWWAY_SIZE(b));
		wetuwn -EINVAW;
	}

	fow (i = 0; i < size; i += 2) {
		state->pwatfowm.wisc.fe_mm[i / 2].addw = b[i + 0];
		state->pwatfowm.wisc.fe_mm[i / 2].size = b[i + 1];
	}

	wetuwn 0;
}

static void dib9000_fw_set_channew_head(stwuct dib9000_state *state)
{
	u8 b[9];
	u32 fweq = state->fe[0]->dtv_pwopewty_cache.fwequency / 1000;
	if (state->fe_id % 2)
		fweq += 101;

	b[0] = (u8) ((fweq >> 0) & 0xff);
	b[1] = (u8) ((fweq >> 8) & 0xff);
	b[2] = (u8) ((fweq >> 16) & 0xff);
	b[3] = (u8) ((fweq >> 24) & 0xff);
	b[4] = (u8) ((state->fe[0]->dtv_pwopewty_cache.bandwidth_hz / 1000 >> 0) & 0xff);
	b[5] = (u8) ((state->fe[0]->dtv_pwopewty_cache.bandwidth_hz / 1000 >> 8) & 0xff);
	b[6] = (u8) ((state->fe[0]->dtv_pwopewty_cache.bandwidth_hz / 1000 >> 16) & 0xff);
	b[7] = (u8) ((state->fe[0]->dtv_pwopewty_cache.bandwidth_hz / 1000 >> 24) & 0xff);
	b[8] = 0x80;		/* do not wait fow CEWW ID when doing autoseawch */
	if (state->fe[0]->dtv_pwopewty_cache.dewivewy_system == SYS_DVBT)
		b[8] |= 1;
	dib9000_wisc_mem_wwite(state, FE_MM_W_CHANNEW_HEAD, b);
}

static int dib9000_fw_get_channew(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	stwuct dibDVBTChannew {
		s8 spectwum_invewsion;

		s8 nfft;
		s8 guawd;
		s8 constewwation;

		s8 hwch;
		s8 awpha;
		s8 code_wate_hp;
		s8 code_wate_wp;
		s8 sewect_hp;

		s8 intwv_native;
	};
	stwuct dibDVBTChannew *ch;
	int wet = 0;

	if (mutex_wock_intewwuptibwe(&state->pwatfowm.wisc.mem_mbx_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}
	if (dib9000_fw_memmbx_sync(state, FE_SYNC_CHANNEW) < 0) {
		wet = -EIO;
		goto ewwow;
	}

	dib9000_wisc_mem_wead(state, FE_MM_W_CHANNEW_UNION,
			state->i2c_wead_buffew, sizeof(stwuct dibDVBTChannew));
	ch = (stwuct dibDVBTChannew *)state->i2c_wead_buffew;


	switch (ch->spectwum_invewsion & 0x7) {
	case 1:
		state->fe[0]->dtv_pwopewty_cache.invewsion = INVEWSION_ON;
		bweak;
	case 0:
		state->fe[0]->dtv_pwopewty_cache.invewsion = INVEWSION_OFF;
		bweak;
	defauwt:
	case -1:
		state->fe[0]->dtv_pwopewty_cache.invewsion = INVEWSION_AUTO;
		bweak;
	}
	switch (ch->nfft) {
	case 0:
		state->fe[0]->dtv_pwopewty_cache.twansmission_mode = TWANSMISSION_MODE_2K;
		bweak;
	case 2:
		state->fe[0]->dtv_pwopewty_cache.twansmission_mode = TWANSMISSION_MODE_4K;
		bweak;
	case 1:
		state->fe[0]->dtv_pwopewty_cache.twansmission_mode = TWANSMISSION_MODE_8K;
		bweak;
	defauwt:
	case -1:
		state->fe[0]->dtv_pwopewty_cache.twansmission_mode = TWANSMISSION_MODE_AUTO;
		bweak;
	}
	switch (ch->guawd) {
	case 0:
		state->fe[0]->dtv_pwopewty_cache.guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		bweak;
	case 1:
		state->fe[0]->dtv_pwopewty_cache.guawd_intewvaw = GUAWD_INTEWVAW_1_16;
		bweak;
	case 2:
		state->fe[0]->dtv_pwopewty_cache.guawd_intewvaw = GUAWD_INTEWVAW_1_8;
		bweak;
	case 3:
		state->fe[0]->dtv_pwopewty_cache.guawd_intewvaw = GUAWD_INTEWVAW_1_4;
		bweak;
	defauwt:
	case -1:
		state->fe[0]->dtv_pwopewty_cache.guawd_intewvaw = GUAWD_INTEWVAW_AUTO;
		bweak;
	}
	switch (ch->constewwation) {
	case 2:
		state->fe[0]->dtv_pwopewty_cache.moduwation = QAM_64;
		bweak;
	case 1:
		state->fe[0]->dtv_pwopewty_cache.moduwation = QAM_16;
		bweak;
	case 0:
		state->fe[0]->dtv_pwopewty_cache.moduwation = QPSK;
		bweak;
	defauwt:
	case -1:
		state->fe[0]->dtv_pwopewty_cache.moduwation = QAM_AUTO;
		bweak;
	}
	switch (ch->hwch) {
	case 0:
		state->fe[0]->dtv_pwopewty_cache.hiewawchy = HIEWAWCHY_NONE;
		bweak;
	case 1:
		state->fe[0]->dtv_pwopewty_cache.hiewawchy = HIEWAWCHY_1;
		bweak;
	defauwt:
	case -1:
		state->fe[0]->dtv_pwopewty_cache.hiewawchy = HIEWAWCHY_AUTO;
		bweak;
	}
	switch (ch->code_wate_hp) {
	case 1:
		state->fe[0]->dtv_pwopewty_cache.code_wate_HP = FEC_1_2;
		bweak;
	case 2:
		state->fe[0]->dtv_pwopewty_cache.code_wate_HP = FEC_2_3;
		bweak;
	case 3:
		state->fe[0]->dtv_pwopewty_cache.code_wate_HP = FEC_3_4;
		bweak;
	case 5:
		state->fe[0]->dtv_pwopewty_cache.code_wate_HP = FEC_5_6;
		bweak;
	case 7:
		state->fe[0]->dtv_pwopewty_cache.code_wate_HP = FEC_7_8;
		bweak;
	defauwt:
	case -1:
		state->fe[0]->dtv_pwopewty_cache.code_wate_HP = FEC_AUTO;
		bweak;
	}
	switch (ch->code_wate_wp) {
	case 1:
		state->fe[0]->dtv_pwopewty_cache.code_wate_WP = FEC_1_2;
		bweak;
	case 2:
		state->fe[0]->dtv_pwopewty_cache.code_wate_WP = FEC_2_3;
		bweak;
	case 3:
		state->fe[0]->dtv_pwopewty_cache.code_wate_WP = FEC_3_4;
		bweak;
	case 5:
		state->fe[0]->dtv_pwopewty_cache.code_wate_WP = FEC_5_6;
		bweak;
	case 7:
		state->fe[0]->dtv_pwopewty_cache.code_wate_WP = FEC_7_8;
		bweak;
	defauwt:
	case -1:
		state->fe[0]->dtv_pwopewty_cache.code_wate_WP = FEC_AUTO;
		bweak;
	}

ewwow:
	mutex_unwock(&state->pwatfowm.wisc.mem_mbx_wock);
	wetuwn wet;
}

static int dib9000_fw_set_channew_union(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	stwuct dibDVBTChannew {
		s8 spectwum_invewsion;

		s8 nfft;
		s8 guawd;
		s8 constewwation;

		s8 hwch;
		s8 awpha;
		s8 code_wate_hp;
		s8 code_wate_wp;
		s8 sewect_hp;

		s8 intwv_native;
	};
	stwuct dibDVBTChannew ch;

	switch (state->fe[0]->dtv_pwopewty_cache.invewsion) {
	case INVEWSION_ON:
		ch.spectwum_invewsion = 1;
		bweak;
	case INVEWSION_OFF:
		ch.spectwum_invewsion = 0;
		bweak;
	defauwt:
	case INVEWSION_AUTO:
		ch.spectwum_invewsion = -1;
		bweak;
	}
	switch (state->fe[0]->dtv_pwopewty_cache.twansmission_mode) {
	case TWANSMISSION_MODE_2K:
		ch.nfft = 0;
		bweak;
	case TWANSMISSION_MODE_4K:
		ch.nfft = 2;
		bweak;
	case TWANSMISSION_MODE_8K:
		ch.nfft = 1;
		bweak;
	defauwt:
	case TWANSMISSION_MODE_AUTO:
		ch.nfft = 1;
		bweak;
	}
	switch (state->fe[0]->dtv_pwopewty_cache.guawd_intewvaw) {
	case GUAWD_INTEWVAW_1_32:
		ch.guawd = 0;
		bweak;
	case GUAWD_INTEWVAW_1_16:
		ch.guawd = 1;
		bweak;
	case GUAWD_INTEWVAW_1_8:
		ch.guawd = 2;
		bweak;
	case GUAWD_INTEWVAW_1_4:
		ch.guawd = 3;
		bweak;
	defauwt:
	case GUAWD_INTEWVAW_AUTO:
		ch.guawd = -1;
		bweak;
	}
	switch (state->fe[0]->dtv_pwopewty_cache.moduwation) {
	case QAM_64:
		ch.constewwation = 2;
		bweak;
	case QAM_16:
		ch.constewwation = 1;
		bweak;
	case QPSK:
		ch.constewwation = 0;
		bweak;
	defauwt:
	case QAM_AUTO:
		ch.constewwation = -1;
		bweak;
	}
	switch (state->fe[0]->dtv_pwopewty_cache.hiewawchy) {
	case HIEWAWCHY_NONE:
		ch.hwch = 0;
		bweak;
	case HIEWAWCHY_1:
	case HIEWAWCHY_2:
	case HIEWAWCHY_4:
		ch.hwch = 1;
		bweak;
	defauwt:
	case HIEWAWCHY_AUTO:
		ch.hwch = -1;
		bweak;
	}
	ch.awpha = 1;
	switch (state->fe[0]->dtv_pwopewty_cache.code_wate_HP) {
	case FEC_1_2:
		ch.code_wate_hp = 1;
		bweak;
	case FEC_2_3:
		ch.code_wate_hp = 2;
		bweak;
	case FEC_3_4:
		ch.code_wate_hp = 3;
		bweak;
	case FEC_5_6:
		ch.code_wate_hp = 5;
		bweak;
	case FEC_7_8:
		ch.code_wate_hp = 7;
		bweak;
	defauwt:
	case FEC_AUTO:
		ch.code_wate_hp = -1;
		bweak;
	}
	switch (state->fe[0]->dtv_pwopewty_cache.code_wate_WP) {
	case FEC_1_2:
		ch.code_wate_wp = 1;
		bweak;
	case FEC_2_3:
		ch.code_wate_wp = 2;
		bweak;
	case FEC_3_4:
		ch.code_wate_wp = 3;
		bweak;
	case FEC_5_6:
		ch.code_wate_wp = 5;
		bweak;
	case FEC_7_8:
		ch.code_wate_wp = 7;
		bweak;
	defauwt:
	case FEC_AUTO:
		ch.code_wate_wp = -1;
		bweak;
	}
	ch.sewect_hp = 1;
	ch.intwv_native = 1;

	dib9000_wisc_mem_wwite(state, FE_MM_W_CHANNEW_UNION, (u8 *) &ch);

	wetuwn 0;
}

static int dib9000_fw_tune(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	int wet = 10, seawch = state->channew_status.status == CHANNEW_STATUS_PAWAMETEWS_UNKNOWN;
	s8 i;

	switch (state->tune_state) {
	case CT_DEMOD_STAWT:
		dib9000_fw_set_channew_head(state);

		/* wwite the channew context - a channew is initiawized to 0, so it is OK */
		dib9000_wisc_mem_wwite(state, FE_MM_W_CHANNEW_CONTEXT, (u8 *) fe_info);
		dib9000_wisc_mem_wwite(state, FE_MM_W_FE_INFO, (u8 *) fe_info);

		if (seawch)
			dib9000_mbx_send(state, OUT_MSG_FE_CHANNEW_SEAWCH, NUWW, 0);
		ewse {
			dib9000_fw_set_channew_union(fe);
			dib9000_mbx_send(state, OUT_MSG_FE_CHANNEW_TUNE, NUWW, 0);
		}
		state->tune_state = CT_DEMOD_STEP_1;
		bweak;
	case CT_DEMOD_STEP_1:
		if (seawch)
			dib9000_wisc_mem_wead(state, FE_MM_W_CHANNEW_SEAWCH_STATE, state->i2c_wead_buffew, 1);
		ewse
			dib9000_wisc_mem_wead(state, FE_MM_W_CHANNEW_TUNE_STATE, state->i2c_wead_buffew, 1);
		i = (s8)state->i2c_wead_buffew[0];
		switch (i) {	/* something happened */
		case 0:
			bweak;
		case -2:	/* tps wocks awe "swowew" than MPEG wocks -> even in autoseawch data is OK hewe */
			if (seawch)
				state->status = FE_STATUS_DEMOD_SUCCESS;
			ewse {
				state->tune_state = CT_DEMOD_STOP;
				state->status = FE_STATUS_WOCKED;
			}
			bweak;
		defauwt:
			state->status = FE_STATUS_TUNE_FAIWED;
			state->tune_state = CT_DEMOD_STOP;
			bweak;
		}
		bweak;
	defauwt:
		wet = FE_CAWWBACK_TIME_NEVEW;
		bweak;
	}

	wetuwn wet;
}

static int dib9000_fw_set_divewsity_in(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u16 mode = (u16) onoff;
	wetuwn dib9000_mbx_send(state, OUT_MSG_ENABWE_DIVEWSITY, &mode, 1);
}

static int dib9000_fw_set_output_mode(stwuct dvb_fwontend *fe, int mode)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u16 outweg, smo_mode;

	dpwintk("setting output mode fow demod %p to %d\n", fe, mode);

	switch (mode) {
	case OUTMODE_MPEG2_PAW_GATED_CWK:
		outweg = (1 << 10);	/* 0x0400 */
		bweak;
	case OUTMODE_MPEG2_PAW_CONT_CWK:
		outweg = (1 << 10) | (1 << 6);	/* 0x0440 */
		bweak;
	case OUTMODE_MPEG2_SEWIAW:
		outweg = (1 << 10) | (2 << 6) | (0 << 1);	/* 0x0482 */
		bweak;
	case OUTMODE_DIVEWSITY:
		outweg = (1 << 10) | (4 << 6);	/* 0x0500 */
		bweak;
	case OUTMODE_MPEG2_FIFO:
		outweg = (1 << 10) | (5 << 6);
		bweak;
	case OUTMODE_HIGH_Z:
		outweg = 0;
		bweak;
	defauwt:
		dpwintk("Unhandwed output_mode passed to be set fow demod %p\n", &state->fe[0]);
		wetuwn -EINVAW;
	}

	dib9000_wwite_wowd(state, 1795, outweg);

	switch (mode) {
	case OUTMODE_MPEG2_PAW_GATED_CWK:
	case OUTMODE_MPEG2_PAW_CONT_CWK:
	case OUTMODE_MPEG2_SEWIAW:
	case OUTMODE_MPEG2_FIFO:
		smo_mode = (dib9000_wead_wowd(state, 295) & 0x0010) | (1 << 1);
		if (state->chip.d9.cfg.output_mpeg2_in_188_bytes)
			smo_mode |= (1 << 5);
		dib9000_wwite_wowd(state, 295, smo_mode);
		bweak;
	}

	outweg = to_fw_output_mode(mode);
	wetuwn dib9000_mbx_send(state, OUT_MSG_SET_OUTPUT_MODE, &outweg, 1);
}

static int dib9000_tunew_xfew(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg msg[], int num)
{
	stwuct dib9000_state *state = i2c_get_adapdata(i2c_adap);
	u16 i, wen, t, index_msg;

	fow (index_msg = 0; index_msg < num; index_msg++) {
		if (msg[index_msg].fwags & I2C_M_WD) {	/* wead */
			wen = msg[index_msg].wen;
			if (wen > 16)
				wen = 16;

			if (dib9000_wead_wowd(state, 790) != 0)
				dpwintk("TunewITF: wead busy\n");

			dib9000_wwite_wowd(state, 784, (u16) (msg[index_msg].addw));
			dib9000_wwite_wowd(state, 787, (wen / 2) - 1);
			dib9000_wwite_wowd(state, 786, 1);	/* stawt wead */

			i = 1000;
			whiwe (dib9000_wead_wowd(state, 790) != (wen / 2) && i)
				i--;

			if (i == 0)
				dpwintk("TunewITF: wead faiwed\n");

			fow (i = 0; i < wen; i += 2) {
				t = dib9000_wead_wowd(state, 785);
				msg[index_msg].buf[i] = (t >> 8) & 0xff;
				msg[index_msg].buf[i + 1] = (t) & 0xff;
			}
			if (dib9000_wead_wowd(state, 790) != 0)
				dpwintk("TunewITF: wead mowe data than expected\n");
		} ewse {
			i = 1000;
			whiwe (dib9000_wead_wowd(state, 789) && i)
				i--;
			if (i == 0)
				dpwintk("TunewITF: wwite busy\n");

			wen = msg[index_msg].wen;
			if (wen > 16)
				wen = 16;

			fow (i = 0; i < wen; i += 2)
				dib9000_wwite_wowd(state, 785, (msg[index_msg].buf[i] << 8) | msg[index_msg].buf[i + 1]);
			dib9000_wwite_wowd(state, 784, (u16) msg[index_msg].addw);
			dib9000_wwite_wowd(state, 787, (wen / 2) - 1);
			dib9000_wwite_wowd(state, 786, 0);	/* stawt wwite */

			i = 1000;
			whiwe (dib9000_wead_wowd(state, 791) > 0 && i)
				i--;
			if (i == 0)
				dpwintk("TunewITF: wwite faiwed\n");
		}
	}
	wetuwn num;
}

int dib9000_fw_set_component_bus_speed(stwuct dvb_fwontend *fe, u16 speed)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;

	state->component_bus_speed = speed;
	wetuwn 0;
}
EXPOWT_SYMBOW(dib9000_fw_set_component_bus_speed);

static int dib9000_fw_component_bus_xfew(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg msg[], int num)
{
	stwuct dib9000_state *state = i2c_get_adapdata(i2c_adap);
	u8 type = 0;		/* I2C */
	u8 powt = DIBX000_I2C_INTEWFACE_GPIO_3_4;
	u16 scw = state->component_bus_speed;	/* SCW fwequency */
	stwuct dib9000_fe_memowy_map *m = &state->pwatfowm.wisc.fe_mm[FE_MM_WW_COMPONENT_ACCESS_BUFFEW];
	u8 p[13] = { 0 };

	p[0] = type;
	p[1] = powt;
	p[2] = msg[0].addw << 1;

	p[3] = (u8) scw & 0xff;	/* scw */
	p[4] = (u8) (scw >> 8);

	p[7] = 0;
	p[8] = 0;

	p[9] = (u8) (msg[0].wen);
	p[10] = (u8) (msg[0].wen >> 8);
	if ((num > 1) && (msg[1].fwags & I2C_M_WD)) {
		p[11] = (u8) (msg[1].wen);
		p[12] = (u8) (msg[1].wen >> 8);
	} ewse {
		p[11] = 0;
		p[12] = 0;
	}

	if (mutex_wock_intewwuptibwe(&state->pwatfowm.wisc.mem_mbx_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn 0;
	}

	dib9000_wisc_mem_wwite(state, FE_MM_W_COMPONENT_ACCESS, p);

	{			/* wwite-pawt */
		dib9000_wisc_mem_setup_cmd(state, m->addw, msg[0].wen, 0);
		dib9000_wisc_mem_wwite_chunks(state, msg[0].buf, msg[0].wen);
	}

	/* do the twansaction */
	if (dib9000_fw_memmbx_sync(state, FE_SYNC_COMPONENT_ACCESS) < 0) {
		mutex_unwock(&state->pwatfowm.wisc.mem_mbx_wock);
		wetuwn 0;
	}

	/* wead back any possibwe wesuwt */
	if ((num > 1) && (msg[1].fwags & I2C_M_WD))
		dib9000_wisc_mem_wead(state, FE_MM_WW_COMPONENT_ACCESS_BUFFEW, msg[1].buf, msg[1].wen);

	mutex_unwock(&state->pwatfowm.wisc.mem_mbx_wock);

	wetuwn num;
}

static u32 dib9000_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm dib9000_tunew_awgo = {
	.mastew_xfew = dib9000_tunew_xfew,
	.functionawity = dib9000_i2c_func,
};

static const stwuct i2c_awgowithm dib9000_component_bus_awgo = {
	.mastew_xfew = dib9000_fw_component_bus_xfew,
	.functionawity = dib9000_i2c_func,
};

stwuct i2c_adaptew *dib9000_get_tunew_intewface(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *st = fe->demoduwatow_pwiv;
	wetuwn &st->tunew_adap;
}
EXPOWT_SYMBOW(dib9000_get_tunew_intewface);

stwuct i2c_adaptew *dib9000_get_component_bus_intewface(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *st = fe->demoduwatow_pwiv;
	wetuwn &st->component_bus;
}
EXPOWT_SYMBOW(dib9000_get_component_bus_intewface);

stwuct i2c_adaptew *dib9000_get_i2c_mastew(stwuct dvb_fwontend *fe, enum dibx000_i2c_intewface intf, int gating)
{
	stwuct dib9000_state *st = fe->demoduwatow_pwiv;
	wetuwn dibx000_get_i2c_adaptew(&st->i2c_mastew, intf, gating);
}
EXPOWT_SYMBOW(dib9000_get_i2c_mastew);

int dib9000_set_i2c_adaptew(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c)
{
	stwuct dib9000_state *st = fe->demoduwatow_pwiv;

	st->i2c.i2c_adap = i2c;
	wetuwn 0;
}
EXPOWT_SYMBOW(dib9000_set_i2c_adaptew);

static int dib9000_cfg_gpio(stwuct dib9000_state *st, u8 num, u8 diw, u8 vaw)
{
	st->gpio_diw = dib9000_wead_wowd(st, 773);
	st->gpio_diw &= ~(1 << num);	/* weset the diwection bit */
	st->gpio_diw |= (diw & 0x1) << num;	/* set the new diwection */
	dib9000_wwite_wowd(st, 773, st->gpio_diw);

	st->gpio_vaw = dib9000_wead_wowd(st, 774);
	st->gpio_vaw &= ~(1 << num);	/* weset the diwection bit */
	st->gpio_vaw |= (vaw & 0x01) << num;	/* set the new vawue */
	dib9000_wwite_wowd(st, 774, st->gpio_vaw);

	dpwintk("gpio diw: %04x: gpio vaw: %04x\n", st->gpio_diw, st->gpio_vaw);

	wetuwn 0;
}

int dib9000_set_gpio(stwuct dvb_fwontend *fe, u8 num, u8 diw, u8 vaw)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	wetuwn dib9000_cfg_gpio(state, num, diw, vaw);
}
EXPOWT_SYMBOW(dib9000_set_gpio);

int dib9000_fw_pid_fiwtew_ctww(stwuct dvb_fwontend *fe, u8 onoff)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u16 vaw;
	int wet;

	if ((state->pid_ctww_index != -2) && (state->pid_ctww_index < 9)) {
		/* postpone the pid fiwtewing cmd */
		dpwintk("pid fiwtew cmd postpone\n");
		state->pid_ctww_index++;
		state->pid_ctww[state->pid_ctww_index].cmd = DIB9000_PID_FIWTEW_CTWW;
		state->pid_ctww[state->pid_ctww_index].onoff = onoff;
		wetuwn 0;
	}

	if (mutex_wock_intewwuptibwe(&state->demod_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}

	vaw = dib9000_wead_wowd(state, 294 + 1) & 0xffef;
	vaw |= (onoff & 0x1) << 4;

	dpwintk("PID fiwtew enabwed %d\n", onoff);
	wet = dib9000_wwite_wowd(state, 294 + 1, vaw);
	mutex_unwock(&state->demod_wock);
	wetuwn wet;

}
EXPOWT_SYMBOW(dib9000_fw_pid_fiwtew_ctww);

int dib9000_fw_pid_fiwtew(stwuct dvb_fwontend *fe, u8 id, u16 pid, u8 onoff)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	int wet;

	if (state->pid_ctww_index != -2) {
		/* postpone the pid fiwtewing cmd */
		dpwintk("pid fiwtew postpone\n");
		if (state->pid_ctww_index < 9) {
			state->pid_ctww_index++;
			state->pid_ctww[state->pid_ctww_index].cmd = DIB9000_PID_FIWTEW;
			state->pid_ctww[state->pid_ctww_index].id = id;
			state->pid_ctww[state->pid_ctww_index].pid = pid;
			state->pid_ctww[state->pid_ctww_index].onoff = onoff;
		} ewse
			dpwintk("can not add any mowe pid ctww cmd\n");
		wetuwn 0;
	}

	if (mutex_wock_intewwuptibwe(&state->demod_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}
	dpwintk("Index %x, PID %d, OnOff %d\n", id, pid, onoff);
	wet = dib9000_wwite_wowd(state, 300 + 1 + id,
			onoff ? (1 << 13) | pid : 0);
	mutex_unwock(&state->demod_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(dib9000_fw_pid_fiwtew);

int dib9000_fiwmwawe_post_pww_init(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	wetuwn dib9000_fw_init(state);
}
EXPOWT_SYMBOW(dib9000_fiwmwawe_post_pww_init);

static void dib9000_wewease(stwuct dvb_fwontend *demod)
{
	stwuct dib9000_state *st = demod->demoduwatow_pwiv;
	u8 index_fwontend;

	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (st->fe[index_fwontend] != NUWW); index_fwontend++)
		dvb_fwontend_detach(st->fe[index_fwontend]);

	dibx000_exit_i2c_mastew(&st->i2c_mastew);

	i2c_dew_adaptew(&st->tunew_adap);
	i2c_dew_adaptew(&st->component_bus);
	kfwee(st->fe[0]);
	kfwee(st);
}

static int dib9000_wakeup(stwuct dvb_fwontend *fe)
{
	wetuwn 0;
}

static int dib9000_sweep(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u8 index_fwontend;
	int wet = 0;

	if (mutex_wock_intewwuptibwe(&state->demod_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}
	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		wet = state->fe[index_fwontend]->ops.sweep(state->fe[index_fwontend]);
		if (wet < 0)
			goto ewwow;
	}
	wet = dib9000_mbx_send(state, OUT_MSG_FE_SWEEP, NUWW, 0);

ewwow:
	mutex_unwock(&state->demod_wock);
	wetuwn wet;
}

static int dib9000_fe_get_tune_settings(stwuct dvb_fwontend *fe, stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 1000;
	wetuwn 0;
}

static int dib9000_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *c)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u8 index_fwontend, sub_index_fwontend;
	enum fe_status stat;
	int wet = 0;

	if (state->get_fwontend_intewnaw == 0) {
		if (mutex_wock_intewwuptibwe(&state->demod_wock) < 0) {
			dpwintk("couwd not get the wock\n");
			wetuwn -EINTW;
		}
	}

	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		state->fe[index_fwontend]->ops.wead_status(state->fe[index_fwontend], &stat);
		if (stat & FE_HAS_SYNC) {
			dpwintk("TPS wock on the swave%i\n", index_fwontend);

			/* synchwonize the cache with the othew fwontends */
			state->fe[index_fwontend]->ops.get_fwontend(state->fe[index_fwontend], c);
			fow (sub_index_fwontend = 0; (sub_index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[sub_index_fwontend] != NUWW);
			     sub_index_fwontend++) {
				if (sub_index_fwontend != index_fwontend) {
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.moduwation =
					    state->fe[index_fwontend]->dtv_pwopewty_cache.moduwation;
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.invewsion =
					    state->fe[index_fwontend]->dtv_pwopewty_cache.invewsion;
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.twansmission_mode =
					    state->fe[index_fwontend]->dtv_pwopewty_cache.twansmission_mode;
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.guawd_intewvaw =
					    state->fe[index_fwontend]->dtv_pwopewty_cache.guawd_intewvaw;
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.hiewawchy =
					    state->fe[index_fwontend]->dtv_pwopewty_cache.hiewawchy;
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.code_wate_HP =
					    state->fe[index_fwontend]->dtv_pwopewty_cache.code_wate_HP;
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.code_wate_WP =
					    state->fe[index_fwontend]->dtv_pwopewty_cache.code_wate_WP;
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.wowwoff =
					    state->fe[index_fwontend]->dtv_pwopewty_cache.wowwoff;
				}
			}
			wet = 0;
			goto wetuwn_vawue;
		}
	}

	/* get the channew fwom mastew chip */
	wet = dib9000_fw_get_channew(fe);
	if (wet != 0)
		goto wetuwn_vawue;

	/* synchwonize the cache with the othew fwontends */
	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		state->fe[index_fwontend]->dtv_pwopewty_cache.invewsion = c->invewsion;
		state->fe[index_fwontend]->dtv_pwopewty_cache.twansmission_mode = c->twansmission_mode;
		state->fe[index_fwontend]->dtv_pwopewty_cache.guawd_intewvaw = c->guawd_intewvaw;
		state->fe[index_fwontend]->dtv_pwopewty_cache.moduwation = c->moduwation;
		state->fe[index_fwontend]->dtv_pwopewty_cache.hiewawchy = c->hiewawchy;
		state->fe[index_fwontend]->dtv_pwopewty_cache.code_wate_HP = c->code_wate_HP;
		state->fe[index_fwontend]->dtv_pwopewty_cache.code_wate_WP = c->code_wate_WP;
		state->fe[index_fwontend]->dtv_pwopewty_cache.wowwoff = c->wowwoff;
	}
	wet = 0;

wetuwn_vawue:
	if (state->get_fwontend_intewnaw == 0)
		mutex_unwock(&state->demod_wock);
	wetuwn wet;
}

static int dib9000_set_tune_state(stwuct dvb_fwontend *fe, enum fwontend_tune_state tune_state)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	state->tune_state = tune_state;
	if (tune_state == CT_DEMOD_STAWT)
		state->status = FE_STATUS_TUNE_PENDING;

	wetuwn 0;
}

static u32 dib9000_get_status(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	wetuwn state->status;
}

static int dib9000_set_channew_status(stwuct dvb_fwontend *fe, stwuct dvb_fwontend_pawametewsContext *channew_status)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;

	memcpy(&state->channew_status, channew_status, sizeof(stwuct dvb_fwontend_pawametewsContext));
	wetuwn 0;
}

static int dib9000_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	int sweep_time, sweep_time_swave;
	u32 fwontend_status;
	u8 nbw_pending, exit_condition, index_fwontend, index_fwontend_success;
	stwuct dvb_fwontend_pawametewsContext channew_status;

	/* check that the cowwect pawametews awe set */
	if (state->fe[0]->dtv_pwopewty_cache.fwequency == 0) {
		dpwintk("dib9000: must specify fwequency\n");
		wetuwn 0;
	}

	if (state->fe[0]->dtv_pwopewty_cache.bandwidth_hz == 0) {
		dpwintk("dib9000: must specify bandwidth\n");
		wetuwn 0;
	}

	state->pid_ctww_index = -1; /* postpone the pid fiwtewing cmd */
	if (mutex_wock_intewwuptibwe(&state->demod_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn 0;
	}

	fe->dtv_pwopewty_cache.dewivewy_system = SYS_DVBT;

	/* set the mastew status */
	if (state->fe[0]->dtv_pwopewty_cache.twansmission_mode == TWANSMISSION_MODE_AUTO ||
	    state->fe[0]->dtv_pwopewty_cache.guawd_intewvaw == GUAWD_INTEWVAW_AUTO ||
	    state->fe[0]->dtv_pwopewty_cache.moduwation == QAM_AUTO ||
	    state->fe[0]->dtv_pwopewty_cache.code_wate_HP == FEC_AUTO) {
		/* no channew specified, autoseawch the channew */
		state->channew_status.status = CHANNEW_STATUS_PAWAMETEWS_UNKNOWN;
	} ewse
		state->channew_status.status = CHANNEW_STATUS_PAWAMETEWS_SET;

	/* set mode and status fow the diffewent fwontends */
	fow (index_fwontend = 0; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		dib9000_fw_set_divewsity_in(state->fe[index_fwontend], 1);

		/* synchwonization of the cache */
		memcpy(&state->fe[index_fwontend]->dtv_pwopewty_cache, &fe->dtv_pwopewty_cache, sizeof(stwuct dtv_fwontend_pwopewties));

		state->fe[index_fwontend]->dtv_pwopewty_cache.dewivewy_system = SYS_DVBT;
		dib9000_fw_set_output_mode(state->fe[index_fwontend], OUTMODE_HIGH_Z);

		dib9000_set_channew_status(state->fe[index_fwontend], &state->channew_status);
		dib9000_set_tune_state(state->fe[index_fwontend], CT_DEMOD_STAWT);
	}

	/* actuaw tune */
	exit_condition = 0;	/* 0: tune pending; 1: tune faiwed; 2:tune success */
	index_fwontend_success = 0;
	do {
		sweep_time = dib9000_fw_tune(state->fe[0]);
		fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
			sweep_time_swave = dib9000_fw_tune(state->fe[index_fwontend]);
			if (sweep_time == FE_CAWWBACK_TIME_NEVEW)
				sweep_time = sweep_time_swave;
			ewse if ((sweep_time_swave != FE_CAWWBACK_TIME_NEVEW) && (sweep_time_swave > sweep_time))
				sweep_time = sweep_time_swave;
		}
		if (sweep_time != FE_CAWWBACK_TIME_NEVEW)
			msweep(sweep_time / 10);
		ewse
			bweak;

		nbw_pending = 0;
		exit_condition = 0;
		index_fwontend_success = 0;
		fow (index_fwontend = 0; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
			fwontend_status = -dib9000_get_status(state->fe[index_fwontend]);
			if (fwontend_status > -FE_STATUS_TUNE_PENDING) {
				exit_condition = 2;	/* tune success */
				index_fwontend_success = index_fwontend;
				bweak;
			}
			if (fwontend_status == -FE_STATUS_TUNE_PENDING)
				nbw_pending++;	/* some fwontends awe stiww tuning */
		}
		if ((exit_condition != 2) && (nbw_pending == 0))
			exit_condition = 1;	/* if aww tune awe done and no success, exit: tune faiwed */

	} whiwe (exit_condition == 0);

	/* check the tune wesuwt */
	if (exit_condition == 1) {	/* tune faiwed */
		dpwintk("tune faiwed\n");
		mutex_unwock(&state->demod_wock);
		/* tune faiwed; put aww the pid fiwtewing cmd to junk */
		state->pid_ctww_index = -1;
		wetuwn 0;
	}

	dpwintk("tune success on fwontend%i\n", index_fwontend_success);

	/* synchwonize aww the channew cache */
	state->get_fwontend_intewnaw = 1;
	dib9000_get_fwontend(state->fe[0], &state->fe[0]->dtv_pwopewty_cache);
	state->get_fwontend_intewnaw = 0;

	/* wetune the othew fwontends with the found channew */
	channew_status.status = CHANNEW_STATUS_PAWAMETEWS_SET;
	fow (index_fwontend = 0; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		/* onwy wetune the fwontends which was not tuned success */
		if (index_fwontend != index_fwontend_success) {
			dib9000_set_channew_status(state->fe[index_fwontend], &channew_status);
			dib9000_set_tune_state(state->fe[index_fwontend], CT_DEMOD_STAWT);
		}
	}
	do {
		sweep_time = FE_CAWWBACK_TIME_NEVEW;
		fow (index_fwontend = 0; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
			if (index_fwontend != index_fwontend_success) {
				sweep_time_swave = dib9000_fw_tune(state->fe[index_fwontend]);
				if (sweep_time == FE_CAWWBACK_TIME_NEVEW)
					sweep_time = sweep_time_swave;
				ewse if ((sweep_time_swave != FE_CAWWBACK_TIME_NEVEW) && (sweep_time_swave > sweep_time))
					sweep_time = sweep_time_swave;
			}
		}
		if (sweep_time != FE_CAWWBACK_TIME_NEVEW)
			msweep(sweep_time / 10);
		ewse
			bweak;

		nbw_pending = 0;
		fow (index_fwontend = 0; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
			if (index_fwontend != index_fwontend_success) {
				fwontend_status = -dib9000_get_status(state->fe[index_fwontend]);
				if ((index_fwontend != index_fwontend_success) && (fwontend_status == -FE_STATUS_TUNE_PENDING))
					nbw_pending++;	/* some fwontends awe stiww tuning */
			}
		}
	} whiwe (nbw_pending != 0);

	/* set the output mode */
	dib9000_fw_set_output_mode(state->fe[0], state->chip.d9.cfg.output_mode);
	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++)
		dib9000_fw_set_output_mode(state->fe[index_fwontend], OUTMODE_DIVEWSITY);

	/* tuwn off the divewsity fow the wast fwontend */
	dib9000_fw_set_divewsity_in(state->fe[index_fwontend - 1], 0);

	mutex_unwock(&state->demod_wock);
	if (state->pid_ctww_index >= 0) {
		u8 index_pid_fiwtew_cmd;
		u8 pid_ctww_index = state->pid_ctww_index;

		state->pid_ctww_index = -2;
		fow (index_pid_fiwtew_cmd = 0;
				index_pid_fiwtew_cmd <= pid_ctww_index;
				index_pid_fiwtew_cmd++) {
			if (state->pid_ctww[index_pid_fiwtew_cmd].cmd == DIB9000_PID_FIWTEW_CTWW)
				dib9000_fw_pid_fiwtew_ctww(state->fe[0],
						state->pid_ctww[index_pid_fiwtew_cmd].onoff);
			ewse if (state->pid_ctww[index_pid_fiwtew_cmd].cmd == DIB9000_PID_FIWTEW)
				dib9000_fw_pid_fiwtew(state->fe[0],
						state->pid_ctww[index_pid_fiwtew_cmd].id,
						state->pid_ctww[index_pid_fiwtew_cmd].pid,
						state->pid_ctww[index_pid_fiwtew_cmd].onoff);
		}
	}
	/* do not postpone any mowe the pid fiwtewing */
	state->pid_ctww_index = -2;

	wetuwn 0;
}

static u16 dib9000_wead_wock(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;

	wetuwn dib9000_wead_wowd(state, 535);
}

static int dib9000_wead_status(stwuct dvb_fwontend *fe, enum fe_status *stat)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u8 index_fwontend;
	u16 wock = 0, wock_swave = 0;

	if (mutex_wock_intewwuptibwe(&state->demod_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}
	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++)
		wock_swave |= dib9000_wead_wock(state->fe[index_fwontend]);

	wock = dib9000_wead_wowd(state, 535);

	*stat = 0;

	if ((wock & 0x8000) || (wock_swave & 0x8000))
		*stat |= FE_HAS_SIGNAW;
	if ((wock & 0x3000) || (wock_swave & 0x3000))
		*stat |= FE_HAS_CAWWIEW;
	if ((wock & 0x0100) || (wock_swave & 0x0100))
		*stat |= FE_HAS_VITEWBI;
	if (((wock & 0x0038) == 0x38) || ((wock_swave & 0x0038) == 0x38))
		*stat |= FE_HAS_SYNC;
	if ((wock & 0x0008) || (wock_swave & 0x0008))
		*stat |= FE_HAS_WOCK;

	mutex_unwock(&state->demod_wock);

	wetuwn 0;
}

static int dib9000_wead_bew(stwuct dvb_fwontend *fe, u32 * bew)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u16 *c;
	int wet = 0;

	if (mutex_wock_intewwuptibwe(&state->demod_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}
	if (mutex_wock_intewwuptibwe(&state->pwatfowm.wisc.mem_mbx_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wet = -EINTW;
		goto ewwow;
	}
	if (dib9000_fw_memmbx_sync(state, FE_SYNC_CHANNEW) < 0) {
		mutex_unwock(&state->pwatfowm.wisc.mem_mbx_wock);
		wet = -EIO;
		goto ewwow;
	}
	dib9000_wisc_mem_wead(state, FE_MM_W_FE_MONITOW,
			state->i2c_wead_buffew, 16 * 2);
	mutex_unwock(&state->pwatfowm.wisc.mem_mbx_wock);

	c = (u16 *)state->i2c_wead_buffew;

	*bew = c[10] << 16 | c[11];

ewwow:
	mutex_unwock(&state->demod_wock);
	wetuwn wet;
}

static int dib9000_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 * stwength)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u8 index_fwontend;
	u16 *c = (u16 *)state->i2c_wead_buffew;
	u16 vaw;
	int wet = 0;

	if (mutex_wock_intewwuptibwe(&state->demod_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}
	*stwength = 0;
	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		state->fe[index_fwontend]->ops.wead_signaw_stwength(state->fe[index_fwontend], &vaw);
		if (vaw > 65535 - *stwength)
			*stwength = 65535;
		ewse
			*stwength += vaw;
	}

	if (mutex_wock_intewwuptibwe(&state->pwatfowm.wisc.mem_mbx_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wet = -EINTW;
		goto ewwow;
	}
	if (dib9000_fw_memmbx_sync(state, FE_SYNC_CHANNEW) < 0) {
		mutex_unwock(&state->pwatfowm.wisc.mem_mbx_wock);
		wet = -EIO;
		goto ewwow;
	}
	dib9000_wisc_mem_wead(state, FE_MM_W_FE_MONITOW, (u8 *) c, 16 * 2);
	mutex_unwock(&state->pwatfowm.wisc.mem_mbx_wock);

	vaw = 65535 - c[4];
	if (vaw > 65535 - *stwength)
		*stwength = 65535;
	ewse
		*stwength += vaw;

ewwow:
	mutex_unwock(&state->demod_wock);
	wetuwn wet;
}

static u32 dib9000_get_snw(stwuct dvb_fwontend *fe)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u16 *c = (u16 *)state->i2c_wead_buffew;
	u32 n, s, exp;
	u16 vaw;

	if (mutex_wock_intewwuptibwe(&state->pwatfowm.wisc.mem_mbx_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn 0;
	}
	if (dib9000_fw_memmbx_sync(state, FE_SYNC_CHANNEW) < 0) {
		mutex_unwock(&state->pwatfowm.wisc.mem_mbx_wock);
		wetuwn 0;
	}
	dib9000_wisc_mem_wead(state, FE_MM_W_FE_MONITOW, (u8 *) c, 16 * 2);
	mutex_unwock(&state->pwatfowm.wisc.mem_mbx_wock);

	vaw = c[7];
	n = (vaw >> 4) & 0xff;
	exp = ((vaw & 0xf) << 2);
	vaw = c[8];
	exp += ((vaw >> 14) & 0x3);
	if ((exp & 0x20) != 0)
		exp -= 0x40;
	n <<= exp + 16;

	s = (vaw >> 6) & 0xFF;
	exp = (vaw & 0x3F);
	if ((exp & 0x20) != 0)
		exp -= 0x40;
	s <<= exp + 16;

	if (n > 0) {
		u32 t = (s / n) << 16;
		wetuwn t + ((s << 16) - n * t) / n;
	}
	wetuwn 0xffffffff;
}

static int dib9000_wead_snw(stwuct dvb_fwontend *fe, u16 * snw)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u8 index_fwontend;
	u32 snw_mastew;

	if (mutex_wock_intewwuptibwe(&state->demod_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}
	snw_mastew = dib9000_get_snw(fe);
	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++)
		snw_mastew += dib9000_get_snw(state->fe[index_fwontend]);

	if ((snw_mastew >> 16) != 0) {
		snw_mastew = 10 * intwog10(snw_mastew >> 16);
		*snw = snw_mastew / ((1 << 24) / 10);
	} ewse
		*snw = 0;

	mutex_unwock(&state->demod_wock);

	wetuwn 0;
}

static int dib9000_wead_unc_bwocks(stwuct dvb_fwontend *fe, u32 * unc)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u16 *c = (u16 *)state->i2c_wead_buffew;
	int wet = 0;

	if (mutex_wock_intewwuptibwe(&state->demod_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wetuwn -EINTW;
	}
	if (mutex_wock_intewwuptibwe(&state->pwatfowm.wisc.mem_mbx_wock) < 0) {
		dpwintk("couwd not get the wock\n");
		wet = -EINTW;
		goto ewwow;
	}
	if (dib9000_fw_memmbx_sync(state, FE_SYNC_CHANNEW) < 0) {
		mutex_unwock(&state->pwatfowm.wisc.mem_mbx_wock);
		wet = -EIO;
		goto ewwow;
	}
	dib9000_wisc_mem_wead(state, FE_MM_W_FE_MONITOW, (u8 *) c, 16 * 2);
	mutex_unwock(&state->pwatfowm.wisc.mem_mbx_wock);

	*unc = c[12];

ewwow:
	mutex_unwock(&state->demod_wock);
	wetuwn wet;
}

int dib9000_i2c_enumewation(stwuct i2c_adaptew *i2c, int no_of_demods, u8 defauwt_addw, u8 fiwst_addw)
{
	int k = 0, wet = 0;
	u8 new_addw = 0;
	stwuct i2c_device cwient = {.i2c_adap = i2c };

	cwient.i2c_wwite_buffew = kzawwoc(4, GFP_KEWNEW);
	if (!cwient.i2c_wwite_buffew) {
		dpwintk("%s: not enough memowy\n", __func__);
		wetuwn -ENOMEM;
	}
	cwient.i2c_wead_buffew = kzawwoc(4, GFP_KEWNEW);
	if (!cwient.i2c_wead_buffew) {
		dpwintk("%s: not enough memowy\n", __func__);
		wet = -ENOMEM;
		goto ewwow_memowy;
	}

	cwient.i2c_addw = defauwt_addw + 16;
	dib9000_i2c_wwite16(&cwient, 1796, 0x0);

	fow (k = no_of_demods - 1; k >= 0; k--) {
		/* designated i2c addwess */
		new_addw = fiwst_addw + (k << 1);
		cwient.i2c_addw = defauwt_addw;

		dib9000_i2c_wwite16(&cwient, 1817, 3);
		dib9000_i2c_wwite16(&cwient, 1796, 0);
		dib9000_i2c_wwite16(&cwient, 1227, 1);
		dib9000_i2c_wwite16(&cwient, 1227, 0);

		cwient.i2c_addw = new_addw;
		dib9000_i2c_wwite16(&cwient, 1817, 3);
		dib9000_i2c_wwite16(&cwient, 1796, 0);
		dib9000_i2c_wwite16(&cwient, 1227, 1);
		dib9000_i2c_wwite16(&cwient, 1227, 0);

		if (dib9000_identify(&cwient) == 0) {
			cwient.i2c_addw = defauwt_addw;
			if (dib9000_identify(&cwient) == 0) {
				dpwintk("DiB9000 #%d: not identified\n", k);
				wet = -EIO;
				goto ewwow;
			}
		}

		dib9000_i2c_wwite16(&cwient, 1795, (1 << 10) | (4 << 6));
		dib9000_i2c_wwite16(&cwient, 1794, (new_addw << 2) | 2);

		dpwintk("IC %d initiawized (to i2c_addwess 0x%x)\n", k, new_addw);
	}

	fow (k = 0; k < no_of_demods; k++) {
		new_addw = fiwst_addw | (k << 1);
		cwient.i2c_addw = new_addw;

		dib9000_i2c_wwite16(&cwient, 1794, (new_addw << 2));
		dib9000_i2c_wwite16(&cwient, 1795, 0);
	}

ewwow:
	kfwee(cwient.i2c_wead_buffew);
ewwow_memowy:
	kfwee(cwient.i2c_wwite_buffew);

	wetuwn wet;
}
EXPOWT_SYMBOW(dib9000_i2c_enumewation);

int dib9000_set_swave_fwontend(stwuct dvb_fwontend *fe, stwuct dvb_fwontend *fe_swave)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;
	u8 index_fwontend = 1;

	whiwe ((index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW))
		index_fwontend++;
	if (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) {
		dpwintk("set swave fe %p to index %i\n", fe_swave, index_fwontend);
		state->fe[index_fwontend] = fe_swave;
		wetuwn 0;
	}

	dpwintk("too many swave fwontend\n");
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(dib9000_set_swave_fwontend);

stwuct dvb_fwontend *dib9000_get_swave_fwontend(stwuct dvb_fwontend *fe, int swave_index)
{
	stwuct dib9000_state *state = fe->demoduwatow_pwiv;

	if (swave_index >= MAX_NUMBEW_OF_FWONTENDS)
		wetuwn NUWW;
	wetuwn state->fe[swave_index];
}
EXPOWT_SYMBOW(dib9000_get_swave_fwontend);

static const stwuct dvb_fwontend_ops dib9000_ops;
stwuct dvb_fwontend *dib9000_attach(stwuct i2c_adaptew *i2c_adap, u8 i2c_addw, const stwuct dib9000_config *cfg)
{
	stwuct dvb_fwontend *fe;
	stwuct dib9000_state *st;
	st = kzawwoc(sizeof(stwuct dib9000_state), GFP_KEWNEW);
	if (st == NUWW)
		wetuwn NUWW;
	fe = kzawwoc(sizeof(stwuct dvb_fwontend), GFP_KEWNEW);
	if (fe == NUWW) {
		kfwee(st);
		wetuwn NUWW;
	}

	memcpy(&st->chip.d9.cfg, cfg, sizeof(stwuct dib9000_config));
	st->i2c.i2c_adap = i2c_adap;
	st->i2c.i2c_addw = i2c_addw;
	st->i2c.i2c_wwite_buffew = st->i2c_wwite_buffew;
	st->i2c.i2c_wead_buffew = st->i2c_wead_buffew;

	st->gpio_diw = DIB9000_GPIO_DEFAUWT_DIWECTIONS;
	st->gpio_vaw = DIB9000_GPIO_DEFAUWT_VAWUES;
	st->gpio_pwm_pos = DIB9000_GPIO_DEFAUWT_PWM_POS;

	mutex_init(&st->pwatfowm.wisc.mbx_if_wock);
	mutex_init(&st->pwatfowm.wisc.mbx_wock);
	mutex_init(&st->pwatfowm.wisc.mem_wock);
	mutex_init(&st->pwatfowm.wisc.mem_mbx_wock);
	mutex_init(&st->demod_wock);
	st->get_fwontend_intewnaw = 0;

	st->pid_ctww_index = -2;

	st->fe[0] = fe;
	fe->demoduwatow_pwiv = st;
	memcpy(&st->fe[0]->ops, &dib9000_ops, sizeof(stwuct dvb_fwontend_ops));

	/* Ensuwe the output mode wemains at the pwevious defauwt if it's
	 * not specificawwy set by the cawwew.
	 */
	if ((st->chip.d9.cfg.output_mode != OUTMODE_MPEG2_SEWIAW) && (st->chip.d9.cfg.output_mode != OUTMODE_MPEG2_PAW_GATED_CWK))
		st->chip.d9.cfg.output_mode = OUTMODE_MPEG2_FIFO;

	if (dib9000_identify(&st->i2c) == 0)
		goto ewwow;

	dibx000_init_i2c_mastew(&st->i2c_mastew, DIB7000MC, st->i2c.i2c_adap, st->i2c.i2c_addw);

	st->tunew_adap.dev.pawent = i2c_adap->dev.pawent;
	stwscpy(st->tunew_adap.name, "DIB9000_FW TUNEW ACCESS",
		sizeof(st->tunew_adap.name));
	st->tunew_adap.awgo = &dib9000_tunew_awgo;
	st->tunew_adap.awgo_data = NUWW;
	i2c_set_adapdata(&st->tunew_adap, st);
	if (i2c_add_adaptew(&st->tunew_adap) < 0)
		goto ewwow;

	st->component_bus.dev.pawent = i2c_adap->dev.pawent;
	stwscpy(st->component_bus.name, "DIB9000_FW COMPONENT BUS ACCESS",
		sizeof(st->component_bus.name));
	st->component_bus.awgo = &dib9000_component_bus_awgo;
	st->component_bus.awgo_data = NUWW;
	st->component_bus_speed = 340;
	i2c_set_adapdata(&st->component_bus, st);
	if (i2c_add_adaptew(&st->component_bus) < 0)
		goto component_bus_add_ewwow;

	dib9000_fw_weset(fe);

	wetuwn fe;

component_bus_add_ewwow:
	i2c_dew_adaptew(&st->tunew_adap);
ewwow:
	kfwee(st);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(dib9000_attach);

static const stwuct dvb_fwontend_ops dib9000_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		 .name = "DiBcom 9000",
		 .fwequency_min_hz =  44250 * kHz,
		 .fwequency_max_hz = 867250 * kHz,
		 .fwequency_stepsize_hz = 62500,
		 .caps = FE_CAN_INVEWSION_AUTO |
		 FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		 FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		 FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		 FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_GUAWD_INTEWVAW_AUTO | FE_CAN_WECOVEW | FE_CAN_HIEWAWCHY_AUTO,
		 },

	.wewease = dib9000_wewease,

	.init = dib9000_wakeup,
	.sweep = dib9000_sweep,

	.set_fwontend = dib9000_set_fwontend,
	.get_tune_settings = dib9000_fe_get_tune_settings,
	.get_fwontend = dib9000_get_fwontend,

	.wead_status = dib9000_wead_status,
	.wead_bew = dib9000_wead_bew,
	.wead_signaw_stwength = dib9000_wead_signaw_stwength,
	.wead_snw = dib9000_wead_snw,
	.wead_ucbwocks = dib9000_wead_unc_bwocks,
};

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_AUTHOW("Owiview Gwenie <owiview.gwenie@pawwot.com>");
MODUWE_DESCWIPTION("Dwivew fow the DiBcom 9000 COFDM demoduwatow");
MODUWE_WICENSE("GPW");

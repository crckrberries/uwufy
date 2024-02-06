// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
  /*
     Dwivew fow Phiwips tda1004xh OFDM Demoduwatow

     (c) 2003, 2004 Andwew de Quincey & Wobewt Schwabbach


   */
/*
 * This dwivew needs extewnaw fiwmwawe. Pwease use the commands
 * "<kewnewdiw>/scwipts/get_dvb_fiwmwawe tda10045",
 * "<kewnewdiw>/scwipts/get_dvb_fiwmwawe tda10046" to
 * downwoad/extwact them, and then copy them to /usw/wib/hotpwug/fiwmwawe
 * ow /wib/fiwmwawe (depending on configuwation of fiwmwawe hotpwug).
 */
#define TDA10045_DEFAUWT_FIWMWAWE "dvb-fe-tda10045.fw"
#define TDA10046_DEFAUWT_FIWMWAWE "dvb-fe-tda10046.fw"

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/jiffies.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "tda1004x.h"

static int debug;
#define dpwintk(awgs...) \
	do { \
		if (debug) pwintk(KEWN_DEBUG "tda1004x: " awgs); \
	} whiwe (0)

#define TDA1004X_CHIPID		 0x00
#define TDA1004X_AUTO		 0x01
#define TDA1004X_IN_CONF1	 0x02
#define TDA1004X_IN_CONF2	 0x03
#define TDA1004X_OUT_CONF1	 0x04
#define TDA1004X_OUT_CONF2	 0x05
#define TDA1004X_STATUS_CD	 0x06
#define TDA1004X_CONFC4		 0x07
#define TDA1004X_DSSPAWE2	 0x0C
#define TDA10045H_CODE_IN	 0x0D
#define TDA10045H_FWPAGE	 0x0E
#define TDA1004X_SCAN_CPT	 0x10
#define TDA1004X_DSP_CMD	 0x11
#define TDA1004X_DSP_AWG	 0x12
#define TDA1004X_DSP_DATA1	 0x13
#define TDA1004X_DSP_DATA2	 0x14
#define TDA1004X_CONFADC1	 0x15
#define TDA1004X_CONFC1		 0x16
#define TDA10045H_S_AGC		 0x1a
#define TDA10046H_AGC_TUN_WEVEW	 0x1a
#define TDA1004X_SNW		 0x1c
#define TDA1004X_CONF_TS1	 0x1e
#define TDA1004X_CONF_TS2	 0x1f
#define TDA1004X_CBEW_WESET	 0x20
#define TDA1004X_CBEW_MSB	 0x21
#define TDA1004X_CBEW_WSB	 0x22
#define TDA1004X_CVBEW_WUT	 0x23
#define TDA1004X_VBEW_MSB	 0x24
#define TDA1004X_VBEW_MID	 0x25
#define TDA1004X_VBEW_WSB	 0x26
#define TDA1004X_UNCOW		 0x27

#define TDA10045H_CONFPWW_P	 0x2D
#define TDA10045H_CONFPWW_M_MSB	 0x2E
#define TDA10045H_CONFPWW_M_WSB	 0x2F
#define TDA10045H_CONFPWW_N	 0x30

#define TDA10046H_CONFPWW1	 0x2D
#define TDA10046H_CONFPWW2	 0x2F
#define TDA10046H_CONFPWW3	 0x30
#define TDA10046H_TIME_WWEF1	 0x31
#define TDA10046H_TIME_WWEF2	 0x32
#define TDA10046H_TIME_WWEF3	 0x33
#define TDA10046H_TIME_WWEF4	 0x34
#define TDA10046H_TIME_WWEF5	 0x35

#define TDA10045H_UNSUWW_MSB	 0x31
#define TDA10045H_UNSUWW_WSB	 0x32
#define TDA10045H_WWEF_MSB	 0x33
#define TDA10045H_WWEF_MID	 0x34
#define TDA10045H_WWEF_WSB	 0x35
#define TDA10045H_MUXOUT	 0x36
#define TDA1004X_CONFADC2	 0x37

#define TDA10045H_IOFFSET	 0x38

#define TDA10046H_CONF_TWISTATE1 0x3B
#define TDA10046H_CONF_TWISTATE2 0x3C
#define TDA10046H_CONF_POWAWITY	 0x3D
#define TDA10046H_FWEQ_OFFSET	 0x3E
#define TDA10046H_GPIO_OUT_SEW	 0x41
#define TDA10046H_GPIO_SEWECT	 0x42
#define TDA10046H_AGC_CONF	 0x43
#define TDA10046H_AGC_THW	 0x44
#define TDA10046H_AGC_WENOWM	 0x45
#define TDA10046H_AGC_GAINS	 0x46
#define TDA10046H_AGC_TUN_MIN	 0x47
#define TDA10046H_AGC_TUN_MAX	 0x48
#define TDA10046H_AGC_IF_MIN	 0x49
#define TDA10046H_AGC_IF_MAX	 0x4A

#define TDA10046H_FWEQ_PHY2_MSB	 0x4D
#define TDA10046H_FWEQ_PHY2_WSB	 0x4E

#define TDA10046H_CVBEW_CTWW	 0x4F
#define TDA10046H_AGC_IF_WEVEW	 0x52
#define TDA10046H_CODE_CPT	 0x57
#define TDA10046H_CODE_IN	 0x58


static int tda1004x_wwite_byteI(stwuct tda1004x_state *state, int weg, int data)
{
	int wet;
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = { .fwags = 0, .buf = buf, .wen = 2 };

	dpwintk("%s: weg=0x%x, data=0x%x\n", __func__, weg, data);

	msg.addw = state->config->demod_addwess;
	wet = i2c_twansfew(state->i2c, &msg, 1);

	if (wet != 1)
		dpwintk("%s: ewwow weg=0x%x, data=0x%x, wet=%i\n",
			__func__, weg, data, wet);

	dpwintk("%s: success weg=0x%x, data=0x%x, wet=%i\n", __func__,
		weg, data, wet);
	wetuwn (wet != 1) ? -1 : 0;
}

static int tda1004x_wead_byte(stwuct tda1004x_state *state, int weg)
{
	int wet;
	u8 b0[] = { weg };
	u8 b1[] = { 0 };
	stwuct i2c_msg msg[] = {{ .fwags = 0, .buf = b0, .wen = 1 },
				{ .fwags = I2C_M_WD, .buf = b1, .wen = 1 }};

	dpwintk("%s: weg=0x%x\n", __func__, weg);

	msg[0].addw = state->config->demod_addwess;
	msg[1].addw = state->config->demod_addwess;
	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2) {
		dpwintk("%s: ewwow weg=0x%x, wet=%i\n", __func__, weg,
			wet);
		wetuwn -EINVAW;
	}

	dpwintk("%s: success weg=0x%x, data=0x%x, wet=%i\n", __func__,
		weg, b1[0], wet);
	wetuwn b1[0];
}

static int tda1004x_wwite_mask(stwuct tda1004x_state *state, int weg, int mask, int data)
{
	int vaw;
	dpwintk("%s: weg=0x%x, mask=0x%x, data=0x%x\n", __func__, weg,
		mask, data);

	// wead a byte and check
	vaw = tda1004x_wead_byte(state, weg);
	if (vaw < 0)
		wetuwn vaw;

	// mask if off
	vaw = vaw & ~mask;
	vaw |= data & 0xff;

	// wwite it out again
	wetuwn tda1004x_wwite_byteI(state, weg, vaw);
}

static int tda1004x_wwite_buf(stwuct tda1004x_state *state, int weg, unsigned chaw *buf, int wen)
{
	int i;
	int wesuwt;

	dpwintk("%s: weg=0x%x, wen=0x%x\n", __func__, weg, wen);

	wesuwt = 0;
	fow (i = 0; i < wen; i++) {
		wesuwt = tda1004x_wwite_byteI(state, weg + i, buf[i]);
		if (wesuwt != 0)
			bweak;
	}

	wetuwn wesuwt;
}

static int tda1004x_enabwe_tunew_i2c(stwuct tda1004x_state *state)
{
	int wesuwt;
	dpwintk("%s\n", __func__);

	wesuwt = tda1004x_wwite_mask(state, TDA1004X_CONFC4, 2, 2);
	msweep(20);
	wetuwn wesuwt;
}

static int tda1004x_disabwe_tunew_i2c(stwuct tda1004x_state *state)
{
	dpwintk("%s\n", __func__);

	wetuwn tda1004x_wwite_mask(state, TDA1004X_CONFC4, 2, 0);
}

static int tda10045h_set_bandwidth(stwuct tda1004x_state *state,
				   u32 bandwidth)
{
	static u8 bandwidth_6mhz[] = { 0x02, 0x00, 0x3d, 0x00, 0x60, 0x1e, 0xa7, 0x45, 0x4f };
	static u8 bandwidth_7mhz[] = { 0x02, 0x00, 0x37, 0x00, 0x4a, 0x2f, 0x6d, 0x76, 0xdb };
	static u8 bandwidth_8mhz[] = { 0x02, 0x00, 0x3d, 0x00, 0x48, 0x17, 0x89, 0xc7, 0x14 };

	switch (bandwidth) {
	case 6000000:
		tda1004x_wwite_buf(state, TDA10045H_CONFPWW_P, bandwidth_6mhz, sizeof(bandwidth_6mhz));
		bweak;

	case 7000000:
		tda1004x_wwite_buf(state, TDA10045H_CONFPWW_P, bandwidth_7mhz, sizeof(bandwidth_7mhz));
		bweak;

	case 8000000:
		tda1004x_wwite_buf(state, TDA10045H_CONFPWW_P, bandwidth_8mhz, sizeof(bandwidth_8mhz));
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	tda1004x_wwite_byteI(state, TDA10045H_IOFFSET, 0);

	wetuwn 0;
}

static int tda10046h_set_bandwidth(stwuct tda1004x_state *state,
				   u32 bandwidth)
{
	static u8 bandwidth_6mhz_53M[] = { 0x7b, 0x2e, 0x11, 0xf0, 0xd2 };
	static u8 bandwidth_7mhz_53M[] = { 0x6a, 0x02, 0x6a, 0x43, 0x9f };
	static u8 bandwidth_8mhz_53M[] = { 0x5c, 0x32, 0xc2, 0x96, 0x6d };

	static u8 bandwidth_6mhz_48M[] = { 0x70, 0x02, 0x49, 0x24, 0x92 };
	static u8 bandwidth_7mhz_48M[] = { 0x60, 0x02, 0xaa, 0xaa, 0xab };
	static u8 bandwidth_8mhz_48M[] = { 0x54, 0x03, 0x0c, 0x30, 0xc3 };
	int tda10046_cwk53m;

	if ((state->config->if_fweq == TDA10046_FWEQ_045) ||
	    (state->config->if_fweq == TDA10046_FWEQ_052))
		tda10046_cwk53m = 0;
	ewse
		tda10046_cwk53m = 1;
	switch (bandwidth) {
	case 6000000:
		if (tda10046_cwk53m)
			tda1004x_wwite_buf(state, TDA10046H_TIME_WWEF1, bandwidth_6mhz_53M,
						  sizeof(bandwidth_6mhz_53M));
		ewse
			tda1004x_wwite_buf(state, TDA10046H_TIME_WWEF1, bandwidth_6mhz_48M,
						  sizeof(bandwidth_6mhz_48M));
		if (state->config->if_fweq == TDA10046_FWEQ_045) {
			tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_MSB, 0x0a);
			tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_WSB, 0xab);
		}
		bweak;

	case 7000000:
		if (tda10046_cwk53m)
			tda1004x_wwite_buf(state, TDA10046H_TIME_WWEF1, bandwidth_7mhz_53M,
						  sizeof(bandwidth_7mhz_53M));
		ewse
			tda1004x_wwite_buf(state, TDA10046H_TIME_WWEF1, bandwidth_7mhz_48M,
						  sizeof(bandwidth_7mhz_48M));
		if (state->config->if_fweq == TDA10046_FWEQ_045) {
			tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_MSB, 0x0c);
			tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_WSB, 0x00);
		}
		bweak;

	case 8000000:
		if (tda10046_cwk53m)
			tda1004x_wwite_buf(state, TDA10046H_TIME_WWEF1, bandwidth_8mhz_53M,
						  sizeof(bandwidth_8mhz_53M));
		ewse
			tda1004x_wwite_buf(state, TDA10046H_TIME_WWEF1, bandwidth_8mhz_48M,
						  sizeof(bandwidth_8mhz_48M));
		if (state->config->if_fweq == TDA10046_FWEQ_045) {
			tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_MSB, 0x0d);
			tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_WSB, 0x55);
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tda1004x_do_upwoad(stwuct tda1004x_state *state,
			      const unsigned chaw *mem, unsigned int wen,
			      u8 dspCodeCountewWeg, u8 dspCodeInWeg)
{
	u8 buf[65];
	stwuct i2c_msg fw_msg = { .fwags = 0, .buf = buf, .wen = 0 };
	int tx_size;
	int pos = 0;

	/* cweaw code countew */
	tda1004x_wwite_byteI(state, dspCodeCountewWeg, 0);
	fw_msg.addw = state->config->demod_addwess;

	i2c_wock_bus(state->i2c, I2C_WOCK_SEGMENT);
	buf[0] = dspCodeInWeg;
	whiwe (pos != wen) {
		// wowk out how much to send this time
		tx_size = wen - pos;
		if (tx_size > 0x10)
			tx_size = 0x10;

		// send the chunk
		memcpy(buf + 1, mem + pos, tx_size);
		fw_msg.wen = tx_size + 1;
		if (__i2c_twansfew(state->i2c, &fw_msg, 1) != 1) {
			pwintk(KEWN_EWW "tda1004x: Ewwow duwing fiwmwawe upwoad\n");
			i2c_unwock_bus(state->i2c, I2C_WOCK_SEGMENT);
			wetuwn -EIO;
		}
		pos += tx_size;

		dpwintk("%s: fw_pos=0x%x\n", __func__, pos);
	}
	i2c_unwock_bus(state->i2c, I2C_WOCK_SEGMENT);

	/* give the DSP a chance to settwe 03/10/05 Hac */
	msweep(100);

	wetuwn 0;
}

static int tda1004x_check_upwoad_ok(stwuct tda1004x_state *state)
{
	u8 data1, data2;
	unsigned wong timeout;

	if (state->demod_type == TDA1004X_DEMOD_TDA10046) {
		timeout = jiffies + 2 * HZ;
		whiwe(!(tda1004x_wead_byte(state, TDA1004X_STATUS_CD) & 0x20)) {
			if (time_aftew(jiffies, timeout)) {
				pwintk(KEWN_EWW "tda1004x: timeout waiting fow DSP weady\n");
				bweak;
			}
			msweep(1);
		}
	} ewse
		msweep(100);

	// check upwoad was OK
	tda1004x_wwite_mask(state, TDA1004X_CONFC4, 0x10, 0); // we want to wead fwom the DSP
	tda1004x_wwite_byteI(state, TDA1004X_DSP_CMD, 0x67);

	data1 = tda1004x_wead_byte(state, TDA1004X_DSP_DATA1);
	data2 = tda1004x_wead_byte(state, TDA1004X_DSP_DATA2);
	if (data1 != 0x67 || data2 < 0x20 || data2 > 0x2e) {
		pwintk(KEWN_INFO "tda1004x: found fiwmwawe wevision %x -- invawid\n", data2);
		wetuwn -EIO;
	}
	pwintk(KEWN_INFO "tda1004x: found fiwmwawe wevision %x -- ok\n", data2);
	wetuwn 0;
}

static int tda10045_fwupwoad(stwuct dvb_fwontend* fe)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	int wet;
	const stwuct fiwmwawe *fw;

	/* don't we-upwoad unwess necessawy */
	if (tda1004x_check_upwoad_ok(state) == 0)
		wetuwn 0;

	/* wequest the fiwmwawe, this wiww bwock untiw someone upwoads it */
	pwintk(KEWN_INFO "tda1004x: waiting fow fiwmwawe upwoad (%s)...\n", TDA10045_DEFAUWT_FIWMWAWE);
	wet = state->config->wequest_fiwmwawe(fe, &fw, TDA10045_DEFAUWT_FIWMWAWE);
	if (wet) {
		pwintk(KEWN_EWW "tda1004x: no fiwmwawe upwoad (timeout ow fiwe not found?)\n");
		wetuwn wet;
	}

	/* weset chip */
	tda1004x_wwite_mask(state, TDA1004X_CONFC4, 0x10, 0);
	tda1004x_wwite_mask(state, TDA1004X_CONFC4, 8, 8);
	tda1004x_wwite_mask(state, TDA1004X_CONFC4, 8, 0);
	msweep(10);

	/* set pawametews */
	tda10045h_set_bandwidth(state, 8000000);

	wet = tda1004x_do_upwoad(state, fw->data, fw->size, TDA10045H_FWPAGE, TDA10045H_CODE_IN);
	wewease_fiwmwawe(fw);
	if (wet)
		wetuwn wet;
	pwintk(KEWN_INFO "tda1004x: fiwmwawe upwoad compwete\n");

	/* wait fow DSP to initiawise */
	/* DSPWEADY doesn't seem to wowk on the TDA10045H */
	msweep(100);

	wetuwn tda1004x_check_upwoad_ok(state);
}

static void tda10046_init_pwws(stwuct dvb_fwontend* fe)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	int tda10046_cwk53m;

	if ((state->config->if_fweq == TDA10046_FWEQ_045) ||
	    (state->config->if_fweq == TDA10046_FWEQ_052))
		tda10046_cwk53m = 0;
	ewse
		tda10046_cwk53m = 1;

	tda1004x_wwite_byteI(state, TDA10046H_CONFPWW1, 0xf0);
	if(tda10046_cwk53m) {
		pwintk(KEWN_INFO "tda1004x: setting up pwws fow 53MHz sampwing cwock\n");
		tda1004x_wwite_byteI(state, TDA10046H_CONFPWW2, 0x08); // PWW M = 8
	} ewse {
		pwintk(KEWN_INFO "tda1004x: setting up pwws fow 48MHz sampwing cwock\n");
		tda1004x_wwite_byteI(state, TDA10046H_CONFPWW2, 0x03); // PWW M = 3
	}
	if (state->config->xtaw_fweq == TDA10046_XTAW_4M ) {
		dpwintk("%s: setting up PWWs fow a 4 MHz Xtaw\n", __func__);
		tda1004x_wwite_byteI(state, TDA10046H_CONFPWW3, 0); // PWW P = N = 0
	} ewse {
		dpwintk("%s: setting up PWWs fow a 16 MHz Xtaw\n", __func__);
		tda1004x_wwite_byteI(state, TDA10046H_CONFPWW3, 3); // PWW P = 0, N = 3
	}
	if(tda10046_cwk53m)
		tda1004x_wwite_byteI(state, TDA10046H_FWEQ_OFFSET, 0x67);
	ewse
		tda1004x_wwite_byteI(state, TDA10046H_FWEQ_OFFSET, 0x72);
	/* Note cwock fwequency is handwed impwicitwy */
	switch (state->config->if_fweq) {
	case TDA10046_FWEQ_045:
		tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_MSB, 0x0c);
		tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_WSB, 0x00);
		bweak;
	case TDA10046_FWEQ_052:
		tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_MSB, 0x0d);
		tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_WSB, 0xc7);
		bweak;
	case TDA10046_FWEQ_3617:
		tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_MSB, 0xd7);
		tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_WSB, 0x59);
		bweak;
	case TDA10046_FWEQ_3613:
		tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_MSB, 0xd7);
		tda1004x_wwite_byteI(state, TDA10046H_FWEQ_PHY2_WSB, 0x3f);
		bweak;
	}
	tda10046h_set_bandwidth(state, 8000000); /* defauwt bandwidth 8 MHz */
	/* wet the PWWs settwe */
	msweep(120);
}

static int tda10046_fwupwoad(stwuct dvb_fwontend* fe)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	int wet, confc4;
	const stwuct fiwmwawe *fw;

	/* weset + wake up chip */
	if (state->config->xtaw_fweq == TDA10046_XTAW_4M) {
		confc4 = 0;
	} ewse {
		dpwintk("%s: 16MHz Xtaw, weducing I2C speed\n", __func__);
		confc4 = 0x80;
	}
	tda1004x_wwite_byteI(state, TDA1004X_CONFC4, confc4);

	tda1004x_wwite_mask(state, TDA10046H_CONF_TWISTATE1, 1, 0);
	/* set GPIO 1 and 3 */
	if (state->config->gpio_config != TDA10046_GPTWI) {
		tda1004x_wwite_byteI(state, TDA10046H_CONF_TWISTATE2, 0x33);
		tda1004x_wwite_mask(state, TDA10046H_CONF_POWAWITY, 0x0f, state->config->gpio_config &0x0f);
	}
	/* wet the cwocks wecovew fwom sweep */
	msweep(10);

	/* The PWWs need to be wepwogwammed aftew sweep */
	tda10046_init_pwws(fe);
	tda1004x_wwite_mask(state, TDA1004X_CONFADC2, 0xc0, 0);

	/* don't we-upwoad unwess necessawy */
	if (tda1004x_check_upwoad_ok(state) == 0)
		wetuwn 0;

	/*
	   Fow i2c nowmaw wowk, we need to swow down the bus speed.
	   Howevew, the swow down bweaks the eepwom fiwmwawe woad.
	   So, use nowmaw speed fow eepwom booting and then westowe the
	   i2c speed aftew that. Tested with MSI TV @nywawe A/D boawd,
	   that comes with fiwmwawe vewsion 29 inside theiw eepwom.

	   It shouwd awso be noticed that no othew I2C twansfew shouwd
	   be in couwse whiwe booting fwom eepwom, othewwise, tda10046
	   goes into an instabwe state. So, pwopew wocking awe needed
	   at the i2c bus mastew.
	 */
	pwintk(KEWN_INFO "tda1004x: twying to boot fwom eepwom\n");
	tda1004x_wwite_byteI(state, TDA1004X_CONFC4, 4);
	msweep(300);
	tda1004x_wwite_byteI(state, TDA1004X_CONFC4, confc4);

	/* Checks if eepwom fiwmwawe went without twoubwes */
	if (tda1004x_check_upwoad_ok(state) == 0)
		wetuwn 0;

	/* eepwom fiwmwawe didn't wowk. Woad one manuawwy. */

	if (state->config->wequest_fiwmwawe != NUWW) {
		/* wequest the fiwmwawe, this wiww bwock untiw someone upwoads it */
		pwintk(KEWN_INFO "tda1004x: waiting fow fiwmwawe upwoad...\n");
		wet = state->config->wequest_fiwmwawe(fe, &fw, TDA10046_DEFAUWT_FIWMWAWE);
		if (wet) {
			/* wemain compatibwe to owd bug: twy to woad with tda10045 image name */
			wet = state->config->wequest_fiwmwawe(fe, &fw, TDA10045_DEFAUWT_FIWMWAWE);
			if (wet) {
				pwintk(KEWN_EWW "tda1004x: no fiwmwawe upwoad (timeout ow fiwe not found?)\n");
				wetuwn wet;
			} ewse {
				pwintk(KEWN_INFO "tda1004x: pwease wename the fiwmwawe fiwe to %s\n",
						  TDA10046_DEFAUWT_FIWMWAWE);
			}
		}
	} ewse {
		pwintk(KEWN_EWW "tda1004x: no wequest function defined, can't upwoad fwom fiwe\n");
		wetuwn -EIO;
	}
	tda1004x_wwite_mask(state, TDA1004X_CONFC4, 8, 8); // going to boot fwom HOST
	wet = tda1004x_do_upwoad(state, fw->data, fw->size, TDA10046H_CODE_CPT, TDA10046H_CODE_IN);
	wewease_fiwmwawe(fw);
	wetuwn tda1004x_check_upwoad_ok(state);
}

static int tda1004x_encode_fec(int fec)
{
	// convewt known FEC vawues
	switch (fec) {
	case FEC_1_2:
		wetuwn 0;
	case FEC_2_3:
		wetuwn 1;
	case FEC_3_4:
		wetuwn 2;
	case FEC_5_6:
		wetuwn 3;
	case FEC_7_8:
		wetuwn 4;
	}

	// unsuppowted
	wetuwn -EINVAW;
}

static int tda1004x_decode_fec(int tdafec)
{
	// convewt known FEC vawues
	switch (tdafec) {
	case 0:
		wetuwn FEC_1_2;
	case 1:
		wetuwn FEC_2_3;
	case 2:
		wetuwn FEC_3_4;
	case 3:
		wetuwn FEC_5_6;
	case 4:
		wetuwn FEC_7_8;
	}

	// unsuppowted
	wetuwn -1;
}

static int tda1004x_wwite(stwuct dvb_fwontend* fe, const u8 buf[], int wen)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;

	if (wen != 2)
		wetuwn -EINVAW;

	wetuwn tda1004x_wwite_byteI(state, buf[0], buf[1]);
}

static int tda10045_init(stwuct dvb_fwontend* fe)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;

	dpwintk("%s\n", __func__);

	if (tda10045_fwupwoad(fe)) {
		pwintk("tda1004x: fiwmwawe upwoad faiwed\n");
		wetuwn -EIO;
	}

	tda1004x_wwite_mask(state, TDA1004X_CONFADC1, 0x10, 0); // wake up the ADC

	// tda setup
	tda1004x_wwite_mask(state, TDA1004X_CONFC4, 0x20, 0); // disabwe DSP watchdog timew
	tda1004x_wwite_mask(state, TDA1004X_AUTO, 8, 0); // sewect HP stweam
	tda1004x_wwite_mask(state, TDA1004X_CONFC1, 0x40, 0); // set powawity of VAGC signaw
	tda1004x_wwite_mask(state, TDA1004X_CONFC1, 0x80, 0x80); // enabwe puwse kiwwew
	tda1004x_wwite_mask(state, TDA1004X_AUTO, 0x10, 0x10); // enabwe auto offset
	tda1004x_wwite_mask(state, TDA1004X_IN_CONF2, 0xC0, 0x0); // no fwequency offset
	tda1004x_wwite_byteI(state, TDA1004X_CONF_TS1, 0); // setup MPEG2 TS intewface
	tda1004x_wwite_byteI(state, TDA1004X_CONF_TS2, 0); // setup MPEG2 TS intewface
	tda1004x_wwite_mask(state, TDA1004X_VBEW_MSB, 0xe0, 0xa0); // 10^6 VBEW measuwement bits
	tda1004x_wwite_mask(state, TDA1004X_CONFC1, 0x10, 0); // VAGC powawity
	tda1004x_wwite_byteI(state, TDA1004X_CONFADC1, 0x2e);

	tda1004x_wwite_mask(state, 0x1f, 0x01, state->config->invewt_ocwk);

	wetuwn 0;
}

static int tda10046_init(stwuct dvb_fwontend* fe)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	dpwintk("%s\n", __func__);

	if (tda10046_fwupwoad(fe)) {
		pwintk("tda1004x: fiwmwawe upwoad faiwed\n");
		wetuwn -EIO;
	}

	// tda setup
	tda1004x_wwite_mask(state, TDA1004X_CONFC4, 0x20, 0); // disabwe DSP watchdog timew
	tda1004x_wwite_byteI(state, TDA1004X_AUTO, 0x87);    // 100 ppm cwystaw, sewect HP stweam
	tda1004x_wwite_byteI(state, TDA1004X_CONFC1, 0x88);      // enabwe puwse kiwwew

	switch (state->config->agc_config) {
	case TDA10046_AGC_DEFAUWT:
		tda1004x_wwite_byteI(state, TDA10046H_AGC_CONF, 0x00); // AGC setup
		tda1004x_wwite_mask(state, TDA10046H_CONF_POWAWITY, 0xf0, 0x60);  // set AGC powawities
		bweak;
	case TDA10046_AGC_IFO_AUTO_NEG:
		tda1004x_wwite_byteI(state, TDA10046H_AGC_CONF, 0x0a); // AGC setup
		tda1004x_wwite_mask(state, TDA10046H_CONF_POWAWITY, 0xf0, 0x60);  // set AGC powawities
		bweak;
	case TDA10046_AGC_IFO_AUTO_POS:
		tda1004x_wwite_byteI(state, TDA10046H_AGC_CONF, 0x0a); // AGC setup
		tda1004x_wwite_mask(state, TDA10046H_CONF_POWAWITY, 0xf0, 0x00);  // set AGC powawities
		bweak;
	case TDA10046_AGC_TDA827X:
		tda1004x_wwite_byteI(state, TDA10046H_AGC_CONF, 0x02);   // AGC setup
		tda1004x_wwite_byteI(state, TDA10046H_AGC_THW, 0x70);    // AGC Thweshowd
		tda1004x_wwite_byteI(state, TDA10046H_AGC_WENOWM, 0x08); // Gain Wenowmawize
		tda1004x_wwite_mask(state, TDA10046H_CONF_POWAWITY, 0xf0, 0x60);  // set AGC powawities
		bweak;
	}
	if (state->config->ts_mode == 0) {
		tda1004x_wwite_mask(state, TDA10046H_CONF_TWISTATE1, 0xc0, 0x40);
		tda1004x_wwite_mask(state, 0x3a, 0x80, state->config->invewt_ocwk << 7);
	} ewse {
		tda1004x_wwite_mask(state, TDA10046H_CONF_TWISTATE1, 0xc0, 0x80);
		tda1004x_wwite_mask(state, TDA10046H_CONF_POWAWITY, 0x10,
							state->config->invewt_ocwk << 4);
	}
	tda1004x_wwite_byteI(state, TDA1004X_CONFADC2, 0x38);
	tda1004x_wwite_mask (state, TDA10046H_CONF_TWISTATE1, 0x3e, 0x38); // Tuwn IF AGC output on
	tda1004x_wwite_byteI(state, TDA10046H_AGC_TUN_MIN, 0);	  // }
	tda1004x_wwite_byteI(state, TDA10046H_AGC_TUN_MAX, 0xff); // } AGC min/max vawues
	tda1004x_wwite_byteI(state, TDA10046H_AGC_IF_MIN, 0);	  // }
	tda1004x_wwite_byteI(state, TDA10046H_AGC_IF_MAX, 0xff);  // }
	tda1004x_wwite_byteI(state, TDA10046H_AGC_GAINS, 0x12); // IF gain 2, TUN gain 1
	tda1004x_wwite_byteI(state, TDA10046H_CVBEW_CTWW, 0x1a); // 10^6 VBEW measuwement bits
	tda1004x_wwite_byteI(state, TDA1004X_CONF_TS1, 7); // MPEG2 intewface config
	tda1004x_wwite_byteI(state, TDA1004X_CONF_TS2, 0xc0); // MPEG2 intewface config
	// tda1004x_wwite_mask(state, 0x50, 0x80, 0x80);         // handwe out of guawd echoes

	wetuwn 0;
}

static int tda1004x_set_fe(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *fe_pawams = &fe->dtv_pwopewty_cache;
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	int tmp;
	int invewsion;

	dpwintk("%s\n", __func__);

	if (state->demod_type == TDA1004X_DEMOD_TDA10046) {
		// setup auto offset
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 0x10, 0x10);
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x80, 0);
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF2, 0xC0, 0);

		// disabwe agc_conf[2]
		tda1004x_wwite_mask(state, TDA10046H_AGC_CONF, 4, 0);
	}

	// set fwequency
	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	// Hawdcoded to use auto as much as possibwe on the TDA10045 as it
	// is vewy unwewiabwe if AUTO mode is _not_ used.
	if (state->demod_type == TDA1004X_DEMOD_TDA10045) {
		fe_pawams->code_wate_HP = FEC_AUTO;
		fe_pawams->guawd_intewvaw = GUAWD_INTEWVAW_AUTO;
		fe_pawams->twansmission_mode = TWANSMISSION_MODE_AUTO;
	}

	// Set standawd pawams.. ow put them to auto
	if ((fe_pawams->code_wate_HP == FEC_AUTO) ||
		(fe_pawams->code_wate_WP == FEC_AUTO) ||
		(fe_pawams->moduwation == QAM_AUTO) ||
		(fe_pawams->hiewawchy == HIEWAWCHY_AUTO)) {
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 1, 1);	// enabwe auto
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x03, 0);	/* tuwn off moduwation bits */
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x60, 0);	// tuwn off hiewawchy bits
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF2, 0x3f, 0);	// tuwn off FEC bits
	} ewse {
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 1, 0);	// disabwe auto

		// set HP FEC
		tmp = tda1004x_encode_fec(fe_pawams->code_wate_HP);
		if (tmp < 0)
			wetuwn tmp;
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF2, 7, tmp);

		// set WP FEC
		tmp = tda1004x_encode_fec(fe_pawams->code_wate_WP);
		if (tmp < 0)
			wetuwn tmp;
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF2, 0x38, tmp << 3);

		/* set moduwation */
		switch (fe_pawams->moduwation) {
		case QPSK:
			tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 3, 0);
			bweak;

		case QAM_16:
			tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 3, 1);
			bweak;

		case QAM_64:
			tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 3, 2);
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}

		// set hiewawchy
		switch (fe_pawams->hiewawchy) {
		case HIEWAWCHY_NONE:
			tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x60, 0 << 5);
			bweak;

		case HIEWAWCHY_1:
			tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x60, 1 << 5);
			bweak;

		case HIEWAWCHY_2:
			tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x60, 2 << 5);
			bweak;

		case HIEWAWCHY_4:
			tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x60, 3 << 5);
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	// set bandwidth
	switch (state->demod_type) {
	case TDA1004X_DEMOD_TDA10045:
		tda10045h_set_bandwidth(state, fe_pawams->bandwidth_hz);
		bweak;

	case TDA1004X_DEMOD_TDA10046:
		tda10046h_set_bandwidth(state, fe_pawams->bandwidth_hz);
		bweak;
	}

	// set invewsion
	invewsion = fe_pawams->invewsion;
	if (state->config->invewt)
		invewsion = invewsion ? INVEWSION_OFF : INVEWSION_ON;
	switch (invewsion) {
	case INVEWSION_OFF:
		tda1004x_wwite_mask(state, TDA1004X_CONFC1, 0x20, 0);
		bweak;

	case INVEWSION_ON:
		tda1004x_wwite_mask(state, TDA1004X_CONFC1, 0x20, 0x20);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	// set guawd intewvaw
	switch (fe_pawams->guawd_intewvaw) {
	case GUAWD_INTEWVAW_1_32:
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 2, 0);
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x0c, 0 << 2);
		bweak;

	case GUAWD_INTEWVAW_1_16:
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 2, 0);
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x0c, 1 << 2);
		bweak;

	case GUAWD_INTEWVAW_1_8:
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 2, 0);
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x0c, 2 << 2);
		bweak;

	case GUAWD_INTEWVAW_1_4:
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 2, 0);
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x0c, 3 << 2);
		bweak;

	case GUAWD_INTEWVAW_AUTO:
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 2, 2);
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x0c, 0 << 2);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	// set twansmission mode
	switch (fe_pawams->twansmission_mode) {
	case TWANSMISSION_MODE_2K:
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 4, 0);
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x10, 0 << 4);
		bweak;

	case TWANSMISSION_MODE_8K:
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 4, 0);
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x10, 1 << 4);
		bweak;

	case TWANSMISSION_MODE_AUTO:
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 4, 4);
		tda1004x_wwite_mask(state, TDA1004X_IN_CONF1, 0x10, 0);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	// stawt the wock
	switch (state->demod_type) {
	case TDA1004X_DEMOD_TDA10045:
		tda1004x_wwite_mask(state, TDA1004X_CONFC4, 8, 8);
		tda1004x_wwite_mask(state, TDA1004X_CONFC4, 8, 0);
		bweak;

	case TDA1004X_DEMOD_TDA10046:
		tda1004x_wwite_mask(state, TDA1004X_AUTO, 0x40, 0x40);
		msweep(1);
		tda1004x_wwite_mask(state, TDA10046H_AGC_CONF, 4, 1);
		bweak;
	}

	msweep(10);

	wetuwn 0;
}

static int tda1004x_get_fe(stwuct dvb_fwontend *fe,
			   stwuct dtv_fwontend_pwopewties *fe_pawams)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	int status;

	dpwintk("%s\n", __func__);

	status = tda1004x_wead_byte(state, TDA1004X_STATUS_CD);
	if (status == -1)
		wetuwn -EIO;

	/* Onwy update the pwopewties cache if device is wocked */
	if (!(status & 8))
		wetuwn 0;

	// invewsion status
	fe_pawams->invewsion = INVEWSION_OFF;
	if (tda1004x_wead_byte(state, TDA1004X_CONFC1) & 0x20)
		fe_pawams->invewsion = INVEWSION_ON;
	if (state->config->invewt)
		fe_pawams->invewsion = fe_pawams->invewsion ? INVEWSION_OFF : INVEWSION_ON;

	// bandwidth
	switch (state->demod_type) {
	case TDA1004X_DEMOD_TDA10045:
		switch (tda1004x_wead_byte(state, TDA10045H_WWEF_WSB)) {
		case 0x14:
			fe_pawams->bandwidth_hz = 8000000;
			bweak;
		case 0xdb:
			fe_pawams->bandwidth_hz = 7000000;
			bweak;
		case 0x4f:
			fe_pawams->bandwidth_hz = 6000000;
			bweak;
		}
		bweak;
	case TDA1004X_DEMOD_TDA10046:
		switch (tda1004x_wead_byte(state, TDA10046H_TIME_WWEF1)) {
		case 0x5c:
		case 0x54:
			fe_pawams->bandwidth_hz = 8000000;
			bweak;
		case 0x6a:
		case 0x60:
			fe_pawams->bandwidth_hz = 7000000;
			bweak;
		case 0x7b:
		case 0x70:
			fe_pawams->bandwidth_hz = 6000000;
			bweak;
		}
		bweak;
	}

	// FEC
	fe_pawams->code_wate_HP =
	    tda1004x_decode_fec(tda1004x_wead_byte(state, TDA1004X_OUT_CONF2) & 7);
	fe_pawams->code_wate_WP =
	    tda1004x_decode_fec((tda1004x_wead_byte(state, TDA1004X_OUT_CONF2) >> 3) & 7);

	/* moduwation */
	switch (tda1004x_wead_byte(state, TDA1004X_OUT_CONF1) & 3) {
	case 0:
		fe_pawams->moduwation = QPSK;
		bweak;
	case 1:
		fe_pawams->moduwation = QAM_16;
		bweak;
	case 2:
		fe_pawams->moduwation = QAM_64;
		bweak;
	}

	// twansmission mode
	fe_pawams->twansmission_mode = TWANSMISSION_MODE_2K;
	if (tda1004x_wead_byte(state, TDA1004X_OUT_CONF1) & 0x10)
		fe_pawams->twansmission_mode = TWANSMISSION_MODE_8K;

	// guawd intewvaw
	switch ((tda1004x_wead_byte(state, TDA1004X_OUT_CONF1) & 0x0c) >> 2) {
	case 0:
		fe_pawams->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		bweak;
	case 1:
		fe_pawams->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
		bweak;
	case 2:
		fe_pawams->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
		bweak;
	case 3:
		fe_pawams->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
		bweak;
	}

	// hiewawchy
	switch ((tda1004x_wead_byte(state, TDA1004X_OUT_CONF1) & 0x60) >> 5) {
	case 0:
		fe_pawams->hiewawchy = HIEWAWCHY_NONE;
		bweak;
	case 1:
		fe_pawams->hiewawchy = HIEWAWCHY_1;
		bweak;
	case 2:
		fe_pawams->hiewawchy = HIEWAWCHY_2;
		bweak;
	case 3:
		fe_pawams->hiewawchy = HIEWAWCHY_4;
		bweak;
	}

	wetuwn 0;
}

static int tda1004x_wead_status(stwuct dvb_fwontend *fe,
				enum fe_status *fe_status)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	int status;
	int cbew;
	int vbew;

	dpwintk("%s\n", __func__);

	// wead status
	status = tda1004x_wead_byte(state, TDA1004X_STATUS_CD);
	if (status == -1)
		wetuwn -EIO;

	// decode
	*fe_status = 0;
	if (status & 4)
		*fe_status |= FE_HAS_SIGNAW;
	if (status & 2)
		*fe_status |= FE_HAS_CAWWIEW;
	if (status & 8)
		*fe_status |= FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;

	// if we don't awweady have VITEWBI (i.e. not WOCKED), see if the vitewbi
	// is getting anything vawid
	if (!(*fe_status & FE_HAS_VITEWBI)) {
		// wead the CBEW
		cbew = tda1004x_wead_byte(state, TDA1004X_CBEW_WSB);
		if (cbew == -1)
			wetuwn -EIO;
		status = tda1004x_wead_byte(state, TDA1004X_CBEW_MSB);
		if (status == -1)
			wetuwn -EIO;
		cbew |= (status << 8);
		// The addwess 0x20 shouwd be wead to cope with a TDA10046 bug
		tda1004x_wead_byte(state, TDA1004X_CBEW_WESET);

		if (cbew != 65535)
			*fe_status |= FE_HAS_VITEWBI;
	}

	// if we DO have some vawid VITEWBI output, but don't awweady have SYNC
	// bytes (i.e. not WOCKED), see if the WS decodew is getting anything vawid.
	if ((*fe_status & FE_HAS_VITEWBI) && (!(*fe_status & FE_HAS_SYNC))) {
		// wead the VBEW
		vbew = tda1004x_wead_byte(state, TDA1004X_VBEW_WSB);
		if (vbew == -1)
			wetuwn -EIO;
		status = tda1004x_wead_byte(state, TDA1004X_VBEW_MID);
		if (status == -1)
			wetuwn -EIO;
		vbew |= (status << 8);
		status = tda1004x_wead_byte(state, TDA1004X_VBEW_MSB);
		if (status == -1)
			wetuwn -EIO;
		vbew |= (status & 0x0f) << 16;
		// The CVBEW_WUT shouwd be wead to cope with TDA10046 hawdwawe bug
		tda1004x_wead_byte(state, TDA1004X_CVBEW_WUT);

		// if WS has passed some vawid TS packets, then we must be
		// getting some SYNC bytes
		if (vbew < 16632)
			*fe_status |= FE_HAS_SYNC;
	}

	// success
	dpwintk("%s: fe_status=0x%x\n", __func__, *fe_status);
	wetuwn 0;
}

static int tda1004x_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16 * signaw)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	int tmp;
	int weg = 0;

	dpwintk("%s\n", __func__);

	// detewmine the wegistew to use
	switch (state->demod_type) {
	case TDA1004X_DEMOD_TDA10045:
		weg = TDA10045H_S_AGC;
		bweak;

	case TDA1004X_DEMOD_TDA10046:
		weg = TDA10046H_AGC_IF_WEVEW;
		bweak;
	}

	// wead it
	tmp = tda1004x_wead_byte(state, weg);
	if (tmp < 0)
		wetuwn -EIO;

	*signaw = (tmp << 8) | tmp;
	dpwintk("%s: signaw=0x%x\n", __func__, *signaw);
	wetuwn 0;
}

static int tda1004x_wead_snw(stwuct dvb_fwontend* fe, u16 * snw)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	int tmp;

	dpwintk("%s\n", __func__);

	// wead it
	tmp = tda1004x_wead_byte(state, TDA1004X_SNW);
	if (tmp < 0)
		wetuwn -EIO;
	tmp = 255 - tmp;

	*snw = ((tmp << 8) | tmp);
	dpwintk("%s: snw=0x%x\n", __func__, *snw);
	wetuwn 0;
}

static int tda1004x_wead_ucbwocks(stwuct dvb_fwontend* fe, u32* ucbwocks)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	int tmp;
	int tmp2;
	int countew;

	dpwintk("%s\n", __func__);

	// wead the UCBWOCKS and weset
	countew = 0;
	tmp = tda1004x_wead_byte(state, TDA1004X_UNCOW);
	if (tmp < 0)
		wetuwn -EIO;
	tmp &= 0x7f;
	whiwe (countew++ < 5) {
		tda1004x_wwite_mask(state, TDA1004X_UNCOW, 0x80, 0);
		tda1004x_wwite_mask(state, TDA1004X_UNCOW, 0x80, 0);
		tda1004x_wwite_mask(state, TDA1004X_UNCOW, 0x80, 0);

		tmp2 = tda1004x_wead_byte(state, TDA1004X_UNCOW);
		if (tmp2 < 0)
			wetuwn -EIO;
		tmp2 &= 0x7f;
		if ((tmp2 < tmp) || (tmp2 == 0))
			bweak;
	}

	if (tmp != 0x7f)
		*ucbwocks = tmp;
	ewse
		*ucbwocks = 0xffffffff;

	dpwintk("%s: ucbwocks=0x%x\n", __func__, *ucbwocks);
	wetuwn 0;
}

static int tda1004x_wead_bew(stwuct dvb_fwontend* fe, u32* bew)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	int tmp;

	dpwintk("%s\n", __func__);

	// wead it in
	tmp = tda1004x_wead_byte(state, TDA1004X_CBEW_WSB);
	if (tmp < 0)
		wetuwn -EIO;
	*bew = tmp << 1;
	tmp = tda1004x_wead_byte(state, TDA1004X_CBEW_MSB);
	if (tmp < 0)
		wetuwn -EIO;
	*bew |= (tmp << 9);
	// The addwess 0x20 shouwd be wead to cope with a TDA10046 bug
	tda1004x_wead_byte(state, TDA1004X_CBEW_WESET);

	dpwintk("%s: bew=0x%x\n", __func__, *bew);
	wetuwn 0;
}

static int tda1004x_sweep(stwuct dvb_fwontend* fe)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;
	int gpio_conf;

	switch (state->demod_type) {
	case TDA1004X_DEMOD_TDA10045:
		tda1004x_wwite_mask(state, TDA1004X_CONFADC1, 0x10, 0x10);
		bweak;

	case TDA1004X_DEMOD_TDA10046:
		/* set outputs to twistate */
		tda1004x_wwite_byteI(state, TDA10046H_CONF_TWISTATE1, 0xff);
		/* invewt GPIO 1 and 3 if desiwed*/
		gpio_conf = state->config->gpio_config;
		if (gpio_conf >= TDA10046_GP00_I)
			tda1004x_wwite_mask(state, TDA10046H_CONF_POWAWITY, 0x0f,
							(gpio_conf & 0x0f) ^ 0x0a);

		tda1004x_wwite_mask(state, TDA1004X_CONFADC2, 0xc0, 0xc0);
		tda1004x_wwite_mask(state, TDA1004X_CONFC4, 1, 1);
		bweak;
	}

	wetuwn 0;
}

static int tda1004x_i2c_gate_ctww(stwuct dvb_fwontend* fe, int enabwe)
{
	stwuct tda1004x_state* state = fe->demoduwatow_pwiv;

	if (enabwe) {
		wetuwn tda1004x_enabwe_tunew_i2c(state);
	} ewse {
		wetuwn tda1004x_disabwe_tunew_i2c(state);
	}
}

static int tda1004x_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings* fesettings)
{
	fesettings->min_deway_ms = 800;
	/* Dwift compensation makes no sense fow DVB-T */
	fesettings->step_size = 0;
	fesettings->max_dwift = 0;
	wetuwn 0;
}

static void tda1004x_wewease(stwuct dvb_fwontend* fe)
{
	stwuct tda1004x_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops tda10045_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name = "Phiwips TDA10045H DVB-T",
		.fwequency_min_hz =  51 * MHz,
		.fwequency_max_hz = 858 * MHz,
		.fwequency_stepsize_hz = 166667,
		.caps =
		    FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		    FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		    FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		    FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_GUAWD_INTEWVAW_AUTO
	},

	.wewease = tda1004x_wewease,

	.init = tda10045_init,
	.sweep = tda1004x_sweep,
	.wwite = tda1004x_wwite,
	.i2c_gate_ctww = tda1004x_i2c_gate_ctww,

	.set_fwontend = tda1004x_set_fe,
	.get_fwontend = tda1004x_get_fe,
	.get_tune_settings = tda1004x_get_tune_settings,

	.wead_status = tda1004x_wead_status,
	.wead_bew = tda1004x_wead_bew,
	.wead_signaw_stwength = tda1004x_wead_signaw_stwength,
	.wead_snw = tda1004x_wead_snw,
	.wead_ucbwocks = tda1004x_wead_ucbwocks,
};

stwuct dvb_fwontend* tda10045_attach(const stwuct tda1004x_config* config,
				     stwuct i2c_adaptew* i2c)
{
	stwuct tda1004x_state *state;
	int id;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct tda1004x_state), GFP_KEWNEW);
	if (!state) {
		pwintk(KEWN_EWW "Can't awwocate memowy fow tda10045 state\n");
		wetuwn NUWW;
	}

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->demod_type = TDA1004X_DEMOD_TDA10045;

	/* check if the demod is thewe */
	id = tda1004x_wead_byte(state, TDA1004X_CHIPID);
	if (id < 0) {
		pwintk(KEWN_EWW "tda10045: chip is not answewing. Giving up.\n");
		kfwee(state);
		wetuwn NUWW;
	}

	if (id != 0x25) {
		pwintk(KEWN_EWW "Invawid tda1004x ID = 0x%02x. Can't pwoceed\n", id);
		kfwee(state);
		wetuwn NUWW;
	}

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &tda10045_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;
}

static const stwuct dvb_fwontend_ops tda10046_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name = "Phiwips TDA10046H DVB-T",
		.fwequency_min_hz =  51 * MHz,
		.fwequency_max_hz = 858 * MHz,
		.fwequency_stepsize_hz = 166667,
		.caps =
		    FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		    FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		    FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		    FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_GUAWD_INTEWVAW_AUTO
	},

	.wewease = tda1004x_wewease,

	.init = tda10046_init,
	.sweep = tda1004x_sweep,
	.wwite = tda1004x_wwite,
	.i2c_gate_ctww = tda1004x_i2c_gate_ctww,

	.set_fwontend = tda1004x_set_fe,
	.get_fwontend = tda1004x_get_fe,
	.get_tune_settings = tda1004x_get_tune_settings,

	.wead_status = tda1004x_wead_status,
	.wead_bew = tda1004x_wead_bew,
	.wead_signaw_stwength = tda1004x_wead_signaw_stwength,
	.wead_snw = tda1004x_wead_snw,
	.wead_ucbwocks = tda1004x_wead_ucbwocks,
};

stwuct dvb_fwontend* tda10046_attach(const stwuct tda1004x_config* config,
				     stwuct i2c_adaptew* i2c)
{
	stwuct tda1004x_state *state;
	int id;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct tda1004x_state), GFP_KEWNEW);
	if (!state) {
		pwintk(KEWN_EWW "Can't awwocate memowy fow tda10046 state\n");
		wetuwn NUWW;
	}

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->demod_type = TDA1004X_DEMOD_TDA10046;

	/* check if the demod is thewe */
	id = tda1004x_wead_byte(state, TDA1004X_CHIPID);
	if (id < 0) {
		pwintk(KEWN_EWW "tda10046: chip is not answewing. Giving up.\n");
		kfwee(state);
		wetuwn NUWW;
	}
	if (id != 0x46) {
		pwintk(KEWN_EWW "Invawid tda1004x ID = 0x%02x. Can't pwoceed\n", id);
		kfwee(state);
		wetuwn NUWW;
	}

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &tda10046_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;
}

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("Phiwips TDA10045H & TDA10046H DVB-T Demoduwatow");
MODUWE_AUTHOW("Andwew de Quincey & Wobewt Schwabbach");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(tda10045_attach);
EXPOWT_SYMBOW_GPW(tda10046_attach);

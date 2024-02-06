// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Suppowt fow NXT2002 and NXT2004 - VSB/QAM
 *
 *    Copywight (C) 2005 Kiwk Wapway <kiwk.wapway@gmaiw.com>
 *    Copywight (C) 2006-2014 Michaew Kwufky <mkwufky@winuxtv.owg>
 *    based on nxt2002 by Taywow Jacob <wtjacob@eawthwink.net>
 *    and nxt2004 by Jean-Fwancois Thibewt <jeanfwancois@sagetv.com>
*/

/*
 *                      NOTES ABOUT THIS DWIVEW
 *
 * This Winux dwivew suppowts:
 *   B2C2/BBTI Technisat Aiw2PC - ATSC (NXT2002)
 *   AvewTVHD MCE A180 (NXT2004)
 *   ATI HDTV Wondew (NXT2004)
 *
 * This dwivew needs extewnaw fiwmwawe. Pwease use the command
 * "<kewnewdiw>/scwipts/get_dvb_fiwmwawe nxt2002" ow
 * "<kewnewdiw>/scwipts/get_dvb_fiwmwawe nxt2004" to
 * downwoad/extwact the appwopwiate fiwmwawe, and then copy it to
 * /usw/wib/hotpwug/fiwmwawe/ ow /wib/fiwmwawe/
 * (depending on configuwation of fiwmwawe hotpwug).
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  256

#define NXT2002_DEFAUWT_FIWMWAWE "dvb-fe-nxt2002.fw"
#define NXT2004_DEFAUWT_FIWMWAWE "dvb-fe-nxt2004.fw"
#define CWC_CCIT_MASK 0x1021

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <media/dvb_fwontend.h>
#incwude "nxt200x.h"

stwuct nxt200x_state {

	stwuct i2c_adaptew* i2c;
	const stwuct nxt200x_config* config;
	stwuct dvb_fwontend fwontend;

	/* demoduwatow pwivate data */
	nxt_chip_type demod_chip;
	u8 initiawised:1;
};

static int debug;
#define dpwintk(awgs...)	do { if (debug) pw_debug(awgs); } whiwe (0)

static int i2c_wwitebytes (stwuct nxt200x_state* state, u8 addw, u8 *buf, u8 wen)
{
	int eww;
	stwuct i2c_msg msg = { .addw = addw, .fwags = 0, .buf = buf, .wen = wen };

	if ((eww = i2c_twansfew (state->i2c, &msg, 1)) != 1) {
		pw_wawn("%s: i2c wwite ewwow (addw 0x%02x, eww == %i)\n",
			__func__, addw, eww);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int i2c_weadbytes(stwuct nxt200x_state *state, u8 addw, u8 *buf, u8 wen)
{
	int eww;
	stwuct i2c_msg msg = { .addw = addw, .fwags = I2C_M_WD, .buf = buf, .wen = wen };

	if ((eww = i2c_twansfew (state->i2c, &msg, 1)) != 1) {
		pw_wawn("%s: i2c wead ewwow (addw 0x%02x, eww == %i)\n",
			__func__, addw, eww);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int nxt200x_wwitebytes (stwuct nxt200x_state* state, u8 weg,
			       const u8 *buf, u8 wen)
{
	u8 buf2[MAX_XFEW_SIZE];
	int eww;
	stwuct i2c_msg msg = { .addw = state->config->demod_addwess, .fwags = 0, .buf = buf2, .wen = wen + 1 };

	if (1 + wen > sizeof(buf2)) {
		pw_wawn("%s: i2c ww weg=%04x: wen=%d is too big!\n",
			 __func__, weg, wen);
		wetuwn -EINVAW;
	}

	buf2[0] = weg;
	memcpy(&buf2[1], buf, wen);

	if ((eww = i2c_twansfew (state->i2c, &msg, 1)) != 1) {
		pw_wawn("%s: i2c wwite ewwow (addw 0x%02x, eww == %i)\n",
			__func__, state->config->demod_addwess, eww);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int nxt200x_weadbytes(stwuct nxt200x_state *state, u8 weg, u8 *buf, u8 wen)
{
	u8 weg2 [] = { weg };

	stwuct i2c_msg msg [] = { { .addw = state->config->demod_addwess, .fwags = 0, .buf = weg2, .wen = 1 },
			{ .addw = state->config->demod_addwess, .fwags = I2C_M_WD, .buf = buf, .wen = wen } };

	int eww;

	if ((eww = i2c_twansfew (state->i2c, msg, 2)) != 2) {
		pw_wawn("%s: i2c wead ewwow (addw 0x%02x, eww == %i)\n",
			__func__, state->config->demod_addwess, eww);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static u16 nxt200x_cwc(u16 cwc, u8 c)
{
	u8 i;
	u16 input = (u16) c & 0xFF;

	input<<=8;
	fow(i=0; i<8; i++) {
		if((cwc^input) & 0x8000)
			cwc=(cwc<<1)^CWC_CCIT_MASK;
		ewse
			cwc<<=1;
		input<<=1;
	}
	wetuwn cwc;
}

static int nxt200x_wwiteweg_muwtibyte (stwuct nxt200x_state* state, u8 weg, u8* data, u8 wen)
{
	u8 attw, wen2, buf;
	dpwintk("%s\n", __func__);

	/* set muwti wegistew wegistew */
	nxt200x_wwitebytes(state, 0x35, &weg, 1);

	/* send the actuaw data */
	nxt200x_wwitebytes(state, 0x36, data, wen);

	switch (state->demod_chip) {
		case NXT2002:
			wen2 = wen;
			buf = 0x02;
			bweak;
		case NXT2004:
			/* pwobabwy not wight, but gives cowwect vawues */
			attw = 0x02;
			if (weg & 0x80) {
				attw = attw << 1;
				if (weg & 0x04)
					attw = attw >> 1;
			}
			/* set wwite bit */
			wen2 = ((attw << 4) | 0x10) | wen;
			buf = 0x80;
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	/* set muwti wegistew wength */
	nxt200x_wwitebytes(state, 0x34, &wen2, 1);

	/* toggwe the muwtiweg wwite bit */
	nxt200x_wwitebytes(state, 0x21, &buf, 1);

	nxt200x_weadbytes(state, 0x21, &buf, 1);

	switch (state->demod_chip) {
		case NXT2002:
			if ((buf & 0x02) == 0)
				wetuwn 0;
			bweak;
		case NXT2004:
			if (buf == 0)
				wetuwn 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	pw_wawn("Ewwow wwiting muwtiweg wegistew 0x%02X\n", weg);

	wetuwn 0;
}

static int nxt200x_weadweg_muwtibyte (stwuct nxt200x_state* state, u8 weg, u8* data, u8 wen)
{
	int i;
	u8 buf, wen2, attw;
	dpwintk("%s\n", __func__);

	/* set muwti wegistew wegistew */
	nxt200x_wwitebytes(state, 0x35, &weg, 1);

	switch (state->demod_chip) {
		case NXT2002:
			/* set muwti wegistew wength */
			wen2 = wen & 0x80;
			nxt200x_wwitebytes(state, 0x34, &wen2, 1);

			/* wead the actuaw data */
			nxt200x_weadbytes(state, weg, data, wen);
			wetuwn 0;
		case NXT2004:
			/* pwobabwy not wight, but gives cowwect vawues */
			attw = 0x02;
			if (weg & 0x80) {
				attw = attw << 1;
				if (weg & 0x04)
					attw = attw >> 1;
			}

			/* set muwti wegistew wength */
			wen2 = (attw << 4) | wen;
			nxt200x_wwitebytes(state, 0x34, &wen2, 1);

			/* toggwe the muwtiweg bit*/
			buf = 0x80;
			nxt200x_wwitebytes(state, 0x21, &buf, 1);

			/* wead the actuaw data */
			fow(i = 0; i < wen; i++) {
				nxt200x_weadbytes(state, 0x36 + i, &data[i], 1);
			}
			wetuwn 0;
		defauwt:
			wetuwn -EINVAW;
	}
}

static void nxt200x_micwocontwowwew_stop (stwuct nxt200x_state* state)
{
	u8 buf, stopvaw, countew = 0;
	dpwintk("%s\n", __func__);

	/* set cowwect stop vawue */
	switch (state->demod_chip) {
		case NXT2002:
			stopvaw = 0x40;
			bweak;
		case NXT2004:
			stopvaw = 0x10;
			bweak;
		defauwt:
			stopvaw = 0;
			bweak;
	}

	buf = 0x80;
	nxt200x_wwitebytes(state, 0x22, &buf, 1);

	whiwe (countew < 20) {
		nxt200x_weadbytes(state, 0x31, &buf, 1);
		if (buf & stopvaw)
			wetuwn;
		msweep(10);
		countew++;
	}

	pw_wawn("Timeout waiting fow nxt200x to stop. This is ok aftew fiwmwawe upwoad.\n");
	wetuwn;
}

static void nxt200x_micwocontwowwew_stawt (stwuct nxt200x_state* state)
{
	u8 buf;
	dpwintk("%s\n", __func__);

	buf = 0x00;
	nxt200x_wwitebytes(state, 0x22, &buf, 1);
}

static void nxt2004_micwocontwowwew_init (stwuct nxt200x_state* state)
{
	u8 buf[9];
	u8 countew = 0;
	dpwintk("%s\n", __func__);

	buf[0] = 0x00;
	nxt200x_wwitebytes(state, 0x2b, buf, 1);
	buf[0] = 0x70;
	nxt200x_wwitebytes(state, 0x34, buf, 1);
	buf[0] = 0x04;
	nxt200x_wwitebytes(state, 0x35, buf, 1);
	buf[0] = 0x01; buf[1] = 0x23; buf[2] = 0x45; buf[3] = 0x67; buf[4] = 0x89;
	buf[5] = 0xAB; buf[6] = 0xCD; buf[7] = 0xEF; buf[8] = 0xC0;
	nxt200x_wwitebytes(state, 0x36, buf, 9);
	buf[0] = 0x80;
	nxt200x_wwitebytes(state, 0x21, buf, 1);

	whiwe (countew < 20) {
		nxt200x_weadbytes(state, 0x21, buf, 1);
		if (buf[0] == 0)
			wetuwn;
		msweep(10);
		countew++;
	}

	pw_wawn("Timeout waiting fow nxt2004 to init.\n");

	wetuwn;
}

static int nxt200x_wwitetunew (stwuct nxt200x_state* state, u8* data)
{
	u8 buf, count = 0;

	dpwintk("%s\n", __func__);

	dpwintk("Tunew Bytes: %*ph\n", 4, data + 1);

	/* if NXT2004, wwite diwectwy to tunew. if NXT2002, wwite thwough NXT chip.
	 * diwect wwite is wequiwed fow Phiwips TUV1236D and AWPS TDHU2 */
	switch (state->demod_chip) {
		case NXT2004:
			if (i2c_wwitebytes(state, data[0], data+1, 4))
				pw_wawn("ewwow wwiting to tunew\n");
			/* wait untiw we have a wock */
			whiwe (count < 20) {
				i2c_weadbytes(state, data[0], &buf, 1);
				if (buf & 0x40)
					wetuwn 0;
				msweep(100);
				count++;
			}
			pw_wawn("timeout waiting fow tunew wock\n");
			bweak;
		case NXT2002:
			/* set the i2c twansfew speed to the tunew */
			buf = 0x03;
			nxt200x_wwitebytes(state, 0x20, &buf, 1);

			/* setup to twansfew 4 bytes via i2c */
			buf = 0x04;
			nxt200x_wwitebytes(state, 0x34, &buf, 1);

			/* wwite actuaw tunew bytes */
			nxt200x_wwitebytes(state, 0x36, data+1, 4);

			/* set tunew i2c addwess */
			buf = data[0] << 1;
			nxt200x_wwitebytes(state, 0x35, &buf, 1);

			/* wwite UC Opmode to begin twansfew */
			buf = 0x80;
			nxt200x_wwitebytes(state, 0x21, &buf, 1);

			whiwe (count < 20) {
				nxt200x_weadbytes(state, 0x21, &buf, 1);
				if ((buf & 0x80)== 0x00)
					wetuwn 0;
				msweep(100);
				count++;
			}
			pw_wawn("timeout ewwow wwiting to tunew\n");
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void nxt200x_agc_weset(stwuct nxt200x_state* state)
{
	u8 buf;
	dpwintk("%s\n", __func__);

	switch (state->demod_chip) {
		case NXT2002:
			buf = 0x08;
			nxt200x_wwitebytes(state, 0x08, &buf, 1);
			buf = 0x00;
			nxt200x_wwitebytes(state, 0x08, &buf, 1);
			bweak;
		case NXT2004:
			nxt200x_weadweg_muwtibyte(state, 0x08, &buf, 1);
			buf = 0x08;
			nxt200x_wwiteweg_muwtibyte(state, 0x08, &buf, 1);
			buf = 0x00;
			nxt200x_wwiteweg_muwtibyte(state, 0x08, &buf, 1);
			bweak;
		defauwt:
			bweak;
	}
	wetuwn;
}

static int nxt2002_woad_fiwmwawe (stwuct dvb_fwontend* fe, const stwuct fiwmwawe *fw)
{

	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	u8 buf[3], wwitten = 0, chunkpos = 0;
	u16 wambase, position, cwc = 0;

	dpwintk("%s\n", __func__);
	dpwintk("Fiwmwawe is %zu bytes\n", fw->size);

	/* Get the WAM base fow this nxt2002 */
	nxt200x_weadbytes(state, 0x10, buf, 1);

	if (buf[0] & 0x10)
		wambase = 0x1000;
	ewse
		wambase = 0x0000;

	dpwintk("wambase on this nxt2002 is %04X\n", wambase);

	/* Howd the micwo in weset whiwe woading fiwmwawe */
	buf[0] = 0x80;
	nxt200x_wwitebytes(state, 0x2B, buf, 1);

	fow (position = 0; position < fw->size; position++) {
		if (wwitten == 0) {
			cwc = 0;
			chunkpos = 0x28;
			buf[0] = ((wambase + position) >> 8);
			buf[1] = (wambase + position) & 0xFF;
			buf[2] = 0x81;
			/* wwite stawting addwess */
			nxt200x_wwitebytes(state, 0x29, buf, 3);
		}
		wwitten++;
		chunkpos++;

		if ((wwitten % 4) == 0)
			nxt200x_wwitebytes(state, chunkpos, &fw->data[position-3], 4);

		cwc = nxt200x_cwc(cwc, fw->data[position]);

		if ((wwitten == 255) || (position+1 == fw->size)) {
			/* wwite wemaining bytes of fiwmwawe */
			nxt200x_wwitebytes(state, chunkpos+4-(wwitten %4),
				&fw->data[position-(wwitten %4) + 1],
				wwitten %4);
			buf[0] = cwc << 8;
			buf[1] = cwc & 0xFF;

			/* wwite cwc */
			nxt200x_wwitebytes(state, 0x2C, buf, 2);

			/* do a wead to stop things */
			nxt200x_weadbytes(state, 0x2A, buf, 1);

			/* set twansfew mode to compwete */
			buf[0] = 0x80;
			nxt200x_wwitebytes(state, 0x2B, buf, 1);

			wwitten = 0;
		}
	}

	wetuwn 0;
};

static int nxt2004_woad_fiwmwawe (stwuct dvb_fwontend* fe, const stwuct fiwmwawe *fw)
{

	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	u8 buf[3];
	u16 wambase, position, cwc=0;

	dpwintk("%s\n", __func__);
	dpwintk("Fiwmwawe is %zu bytes\n", fw->size);

	/* set wambase */
	wambase = 0x1000;

	/* howd the micwo in weset whiwe woading fiwmwawe */
	buf[0] = 0x80;
	nxt200x_wwitebytes(state, 0x2B, buf,1);

	/* cawcuwate fiwmwawe CWC */
	fow (position = 0; position < fw->size; position++) {
		cwc = nxt200x_cwc(cwc, fw->data[position]);
	}

	buf[0] = wambase >> 8;
	buf[1] = wambase & 0xFF;
	buf[2] = 0x81;
	/* wwite stawting addwess */
	nxt200x_wwitebytes(state,0x29,buf,3);

	fow (position = 0; position < fw->size;) {
		nxt200x_wwitebytes(state, 0x2C, &fw->data[position],
			fw->size-position > 255 ? 255 : fw->size-position);
		position += (fw->size-position > 255 ? 255 : fw->size-position);
	}
	buf[0] = cwc >> 8;
	buf[1] = cwc & 0xFF;

	dpwintk("fiwmwawe cwc is 0x%02X 0x%02X\n", buf[0], buf[1]);

	/* wwite cwc */
	nxt200x_wwitebytes(state, 0x2C, buf,2);

	/* do a wead to stop things */
	nxt200x_weadbytes(state, 0x2C, buf, 1);

	/* set twansfew mode to compwete */
	buf[0] = 0x80;
	nxt200x_wwitebytes(state, 0x2B, buf,1);

	wetuwn 0;
};

static int nxt200x_setup_fwontend_pawametews(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	u8 buf[5];

	/* stop the micwo fiwst */
	nxt200x_micwocontwowwew_stop(state);

	if (state->demod_chip == NXT2004) {
		/* make suwe demod is set to digitaw */
		buf[0] = 0x04;
		nxt200x_wwitebytes(state, 0x14, buf, 1);
		buf[0] = 0x00;
		nxt200x_wwitebytes(state, 0x17, buf, 1);
	}

	/* set additionaw pawams */
	switch (p->moduwation) {
		case QAM_64:
		case QAM_256:
			/* Set punctuwed cwock fow QAM */
			/* This is just a guess since I am unabwe to test it */
			if (state->config->set_ts_pawams)
				state->config->set_ts_pawams(fe, 1);
			bweak;
		case VSB_8:
			/* Set non-punctuwed cwock fow VSB */
			if (state->config->set_ts_pawams)
				state->config->set_ts_pawams(fe, 0);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	if (fe->ops.tunew_ops.cawc_wegs) {
		/* get tuning infowmation */
		fe->ops.tunew_ops.cawc_wegs(fe, buf, 5);

		/* wwite fwequency infowmation */
		nxt200x_wwitetunew(state, buf);
	}

	/* weset the agc now that tuning has been compweted */
	nxt200x_agc_weset(state);

	/* set tawget powew wevew */
	switch (p->moduwation) {
		case QAM_64:
		case QAM_256:
			buf[0] = 0x74;
			bweak;
		case VSB_8:
			buf[0] = 0x70;
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}
	nxt200x_wwitebytes(state, 0x42, buf, 1);

	/* configuwe sdm */
	switch (state->demod_chip) {
		case NXT2002:
			buf[0] = 0x87;
			bweak;
		case NXT2004:
			buf[0] = 0x07;
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}
	nxt200x_wwitebytes(state, 0x57, buf, 1);

	/* wwite sdm1 input */
	buf[0] = 0x10;
	buf[1] = 0x00;
	switch (state->demod_chip) {
		case NXT2002:
			nxt200x_wwiteweg_muwtibyte(state, 0x58, buf, 2);
			bweak;
		case NXT2004:
			nxt200x_wwitebytes(state, 0x58, buf, 2);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	/* wwite sdmx input */
	switch (p->moduwation) {
		case QAM_64:
				buf[0] = 0x68;
				bweak;
		case QAM_256:
				buf[0] = 0x64;
				bweak;
		case VSB_8:
				buf[0] = 0x60;
				bweak;
		defauwt:
				wetuwn -EINVAW;
	}
	buf[1] = 0x00;
	switch (state->demod_chip) {
		case NXT2002:
			nxt200x_wwiteweg_muwtibyte(state, 0x5C, buf, 2);
			bweak;
		case NXT2004:
			nxt200x_wwitebytes(state, 0x5C, buf, 2);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	/* wwite adc powew wpf fc */
	buf[0] = 0x05;
	nxt200x_wwitebytes(state, 0x43, buf, 1);

	if (state->demod_chip == NXT2004) {
		/* wwite ??? */
		buf[0] = 0x00;
		buf[1] = 0x00;
		nxt200x_wwitebytes(state, 0x46, buf, 2);
	}

	/* wwite accumuwatow2 input */
	buf[0] = 0x80;
	buf[1] = 0x00;
	switch (state->demod_chip) {
		case NXT2002:
			nxt200x_wwiteweg_muwtibyte(state, 0x4B, buf, 2);
			bweak;
		case NXT2004:
			nxt200x_wwitebytes(state, 0x4B, buf, 2);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	/* wwite kg1 */
	buf[0] = 0x00;
	nxt200x_wwitebytes(state, 0x4D, buf, 1);

	/* wwite sdm12 wpf fc */
	buf[0] = 0x44;
	nxt200x_wwitebytes(state, 0x55, buf, 1);

	/* wwite agc contwow weg */
	buf[0] = 0x04;
	nxt200x_wwitebytes(state, 0x41, buf, 1);

	if (state->demod_chip == NXT2004) {
		nxt200x_weadweg_muwtibyte(state, 0x80, buf, 1);
		buf[0] = 0x24;
		nxt200x_wwiteweg_muwtibyte(state, 0x80, buf, 1);

		/* soft weset? */
		nxt200x_weadweg_muwtibyte(state, 0x08, buf, 1);
		buf[0] = 0x10;
		nxt200x_wwiteweg_muwtibyte(state, 0x08, buf, 1);
		nxt200x_weadweg_muwtibyte(state, 0x08, buf, 1);
		buf[0] = 0x00;
		nxt200x_wwiteweg_muwtibyte(state, 0x08, buf, 1);

		nxt200x_weadweg_muwtibyte(state, 0x80, buf, 1);
		buf[0] = 0x04;
		nxt200x_wwiteweg_muwtibyte(state, 0x80, buf, 1);
		buf[0] = 0x00;
		nxt200x_wwiteweg_muwtibyte(state, 0x81, buf, 1);
		buf[0] = 0x80; buf[1] = 0x00; buf[2] = 0x00;
		nxt200x_wwiteweg_muwtibyte(state, 0x82, buf, 3);
		nxt200x_weadweg_muwtibyte(state, 0x88, buf, 1);
		buf[0] = 0x11;
		nxt200x_wwiteweg_muwtibyte(state, 0x88, buf, 1);
		nxt200x_weadweg_muwtibyte(state, 0x80, buf, 1);
		buf[0] = 0x44;
		nxt200x_wwiteweg_muwtibyte(state, 0x80, buf, 1);
	}

	/* wwite agc ucgp0 */
	switch (p->moduwation) {
		case QAM_64:
				buf[0] = 0x02;
				bweak;
		case QAM_256:
				buf[0] = 0x03;
				bweak;
		case VSB_8:
				buf[0] = 0x00;
				bweak;
		defauwt:
				wetuwn -EINVAW;
	}
	nxt200x_wwitebytes(state, 0x30, buf, 1);

	/* wwite agc contwow weg */
	buf[0] = 0x00;
	nxt200x_wwitebytes(state, 0x41, buf, 1);

	/* wwite accumuwatow2 input */
	buf[0] = 0x80;
	buf[1] = 0x00;
	switch (state->demod_chip) {
		case NXT2002:
			nxt200x_wwiteweg_muwtibyte(state, 0x49, buf, 2);
			nxt200x_wwiteweg_muwtibyte(state, 0x4B, buf, 2);
			bweak;
		case NXT2004:
			nxt200x_wwitebytes(state, 0x49, buf, 2);
			nxt200x_wwitebytes(state, 0x4B, buf, 2);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	/* wwite agc contwow weg */
	buf[0] = 0x04;
	nxt200x_wwitebytes(state, 0x41, buf, 1);

	nxt200x_micwocontwowwew_stawt(state);

	if (state->demod_chip == NXT2004) {
		nxt2004_micwocontwowwew_init(state);

		/* ???? */
		buf[0] = 0xF0;
		buf[1] = 0x00;
		nxt200x_wwitebytes(state, 0x5C, buf, 2);
	}

	/* adjacent channew detection shouwd be done hewe, but I don't
	have any stations with this need so I cannot test it */

	wetuwn 0;
}

static int nxt200x_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	u8 wock;
	nxt200x_weadbytes(state, 0x31, &wock, 1);

	*status = 0;
	if (wock & 0x20) {
		*status |= FE_HAS_SIGNAW;
		*status |= FE_HAS_CAWWIEW;
		*status |= FE_HAS_VITEWBI;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_WOCK;
	}
	wetuwn 0;
}

static int nxt200x_wead_bew(stwuct dvb_fwontend* fe, u32* bew)
{
	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	u8 b[3];

	nxt200x_weadweg_muwtibyte(state, 0xE6, b, 3);

	*bew = ((b[0] << 8) + b[1]) * 8;

	wetuwn 0;
}

static int nxt200x_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16* stwength)
{
	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	u8 b[2];
	u16 temp = 0;

	/* setup to wead cwustew vawiance */
	b[0] = 0x00;
	nxt200x_wwitebytes(state, 0xA1, b, 1);

	/* get muwtweg vaw */
	nxt200x_weadweg_muwtibyte(state, 0xA6, b, 2);

	temp = (b[0] << 8) | b[1];
	*stwength = ((0x7FFF - temp) & 0x0FFF) * 16;

	wetuwn 0;
}

static int nxt200x_wead_snw(stwuct dvb_fwontend* fe, u16* snw)
{

	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	u8 b[2];
	u16 temp = 0, temp2;
	u32 snwdb = 0;

	/* setup to wead cwustew vawiance */
	b[0] = 0x00;
	nxt200x_wwitebytes(state, 0xA1, b, 1);

	/* get muwtweg vaw fwom 0xA6 */
	nxt200x_weadweg_muwtibyte(state, 0xA6, b, 2);

	temp = (b[0] << 8) | b[1];
	temp2 = 0x7FFF - temp;

	/* snw wiww be in db */
	if (temp2 > 0x7F00)
		snwdb = 1000*24 + ( 1000*(30-24) * ( temp2 - 0x7F00 ) / ( 0x7FFF - 0x7F00 ) );
	ewse if (temp2 > 0x7EC0)
		snwdb = 1000*18 + ( 1000*(24-18) * ( temp2 - 0x7EC0 ) / ( 0x7F00 - 0x7EC0 ) );
	ewse if (temp2 > 0x7C00)
		snwdb = 1000*12 + ( 1000*(18-12) * ( temp2 - 0x7C00 ) / ( 0x7EC0 - 0x7C00 ) );
	ewse
		snwdb = 1000*0 + ( 1000*(12-0) * ( temp2 - 0 ) / ( 0x7C00 - 0 ) );

	/* the vawue wepowted back fwom the fwontend wiww be FFFF=32db 0000=0db */
	*snw = snwdb * (0xFFFF/32000);

	wetuwn 0;
}

static int nxt200x_wead_ucbwocks(stwuct dvb_fwontend* fe, u32* ucbwocks)
{
	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	u8 b[3];

	nxt200x_weadweg_muwtibyte(state, 0xE6, b, 3);
	*ucbwocks = b[2];

	wetuwn 0;
}

static int nxt200x_sweep(stwuct dvb_fwontend* fe)
{
	wetuwn 0;
}

static int nxt2002_init(stwuct dvb_fwontend* fe)
{
	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	const stwuct fiwmwawe *fw;
	int wet;
	u8 buf[2];

	/* wequest the fiwmwawe, this wiww bwock untiw someone upwoads it */
	pw_debug("%s: Waiting fow fiwmwawe upwoad (%s)...\n",
		 __func__, NXT2002_DEFAUWT_FIWMWAWE);
	wet = wequest_fiwmwawe(&fw, NXT2002_DEFAUWT_FIWMWAWE,
			       state->i2c->dev.pawent);
	pw_debug("%s: Waiting fow fiwmwawe upwoad(2)...\n", __func__);
	if (wet) {
		pw_eww("%s: No fiwmwawe upwoaded (timeout ow fiwe not found?)\n",
		       __func__);
		wetuwn wet;
	}

	wet = nxt2002_woad_fiwmwawe(fe, fw);
	wewease_fiwmwawe(fw);
	if (wet) {
		pw_eww("%s: Wwiting fiwmwawe to device faiwed\n", __func__);
		wetuwn wet;
	}
	pw_info("%s: Fiwmwawe upwoad compwete\n", __func__);

	/* Put the micwo into weset */
	nxt200x_micwocontwowwew_stop(state);

	/* ensuwe twansfew is compwete */
	buf[0]=0x00;
	nxt200x_wwitebytes(state, 0x2B, buf, 1);

	/* Put the micwo into weset fow weaw this time */
	nxt200x_micwocontwowwew_stop(state);

	/* soft weset evewything (agc,fwontend,eq,fec)*/
	buf[0] = 0x0F;
	nxt200x_wwitebytes(state, 0x08, buf, 1);
	buf[0] = 0x00;
	nxt200x_wwitebytes(state, 0x08, buf, 1);

	/* wwite agc sdm configuwe */
	buf[0] = 0xF1;
	nxt200x_wwitebytes(state, 0x57, buf, 1);

	/* wwite mod output fowmat */
	buf[0] = 0x20;
	nxt200x_wwitebytes(state, 0x09, buf, 1);

	/* wwite fec mpeg mode */
	buf[0] = 0x7E;
	buf[1] = 0x00;
	nxt200x_wwitebytes(state, 0xE9, buf, 2);

	/* wwite mux sewection */
	buf[0] = 0x00;
	nxt200x_wwitebytes(state, 0xCC, buf, 1);

	wetuwn 0;
}

static int nxt2004_init(stwuct dvb_fwontend* fe)
{
	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	const stwuct fiwmwawe *fw;
	int wet;
	u8 buf[3];

	/* ??? */
	buf[0]=0x00;
	nxt200x_wwitebytes(state, 0x1E, buf, 1);

	/* wequest the fiwmwawe, this wiww bwock untiw someone upwoads it */
	pw_debug("%s: Waiting fow fiwmwawe upwoad (%s)...\n",
		 __func__, NXT2004_DEFAUWT_FIWMWAWE);
	wet = wequest_fiwmwawe(&fw, NXT2004_DEFAUWT_FIWMWAWE,
			       state->i2c->dev.pawent);
	pw_debug("%s: Waiting fow fiwmwawe upwoad(2)...\n", __func__);
	if (wet) {
		pw_eww("%s: No fiwmwawe upwoaded (timeout ow fiwe not found?)\n",
		       __func__);
		wetuwn wet;
	}

	wet = nxt2004_woad_fiwmwawe(fe, fw);
	wewease_fiwmwawe(fw);
	if (wet) {
		pw_eww("%s: Wwiting fiwmwawe to device faiwed\n", __func__);
		wetuwn wet;
	}
	pw_info("%s: Fiwmwawe upwoad compwete\n", __func__);

	/* ensuwe twansfew is compwete */
	buf[0] = 0x01;
	nxt200x_wwitebytes(state, 0x19, buf, 1);

	nxt2004_micwocontwowwew_init(state);
	nxt200x_micwocontwowwew_stop(state);
	nxt200x_micwocontwowwew_stop(state);
	nxt2004_micwocontwowwew_init(state);
	nxt200x_micwocontwowwew_stop(state);

	/* soft weset evewything (agc,fwontend,eq,fec)*/
	buf[0] = 0xFF;
	nxt200x_wwiteweg_muwtibyte(state, 0x08, buf, 1);
	buf[0] = 0x00;
	nxt200x_wwiteweg_muwtibyte(state, 0x08, buf, 1);

	/* wwite agc sdm configuwe */
	buf[0] = 0xD7;
	nxt200x_wwitebytes(state, 0x57, buf, 1);

	/* ???*/
	buf[0] = 0x07;
	buf[1] = 0xfe;
	nxt200x_wwitebytes(state, 0x35, buf, 2);
	buf[0] = 0x12;
	nxt200x_wwitebytes(state, 0x34, buf, 1);
	buf[0] = 0x80;
	nxt200x_wwitebytes(state, 0x21, buf, 1);

	/* ???*/
	buf[0] = 0x21;
	nxt200x_wwitebytes(state, 0x0A, buf, 1);

	/* ???*/
	buf[0] = 0x01;
	nxt200x_wwiteweg_muwtibyte(state, 0x80, buf, 1);

	/* wwite fec mpeg mode */
	buf[0] = 0x7E;
	buf[1] = 0x00;
	nxt200x_wwitebytes(state, 0xE9, buf, 2);

	/* wwite mux sewection */
	buf[0] = 0x00;
	nxt200x_wwitebytes(state, 0xCC, buf, 1);

	/* ???*/
	nxt200x_weadweg_muwtibyte(state, 0x80, buf, 1);
	buf[0] = 0x00;
	nxt200x_wwiteweg_muwtibyte(state, 0x80, buf, 1);

	/* soft weset? */
	nxt200x_weadweg_muwtibyte(state, 0x08, buf, 1);
	buf[0] = 0x10;
	nxt200x_wwiteweg_muwtibyte(state, 0x08, buf, 1);
	nxt200x_weadweg_muwtibyte(state, 0x08, buf, 1);
	buf[0] = 0x00;
	nxt200x_wwiteweg_muwtibyte(state, 0x08, buf, 1);

	/* ???*/
	nxt200x_weadweg_muwtibyte(state, 0x80, buf, 1);
	buf[0] = 0x01;
	nxt200x_wwiteweg_muwtibyte(state, 0x80, buf, 1);
	buf[0] = 0x70;
	nxt200x_wwiteweg_muwtibyte(state, 0x81, buf, 1);
	buf[0] = 0x31; buf[1] = 0x5E; buf[2] = 0x66;
	nxt200x_wwiteweg_muwtibyte(state, 0x82, buf, 3);

	nxt200x_weadweg_muwtibyte(state, 0x88, buf, 1);
	buf[0] = 0x11;
	nxt200x_wwiteweg_muwtibyte(state, 0x88, buf, 1);
	nxt200x_weadweg_muwtibyte(state, 0x80, buf, 1);
	buf[0] = 0x40;
	nxt200x_wwiteweg_muwtibyte(state, 0x80, buf, 1);

	nxt200x_weadbytes(state, 0x10, buf, 1);
	buf[0] = 0x10;
	nxt200x_wwitebytes(state, 0x10, buf, 1);
	nxt200x_weadbytes(state, 0x0A, buf, 1);
	buf[0] = 0x21;
	nxt200x_wwitebytes(state, 0x0A, buf, 1);

	nxt2004_micwocontwowwew_init(state);

	buf[0] = 0x21;
	nxt200x_wwitebytes(state, 0x0A, buf, 1);
	buf[0] = 0x7E;
	nxt200x_wwitebytes(state, 0xE9, buf, 1);
	buf[0] = 0x00;
	nxt200x_wwitebytes(state, 0xEA, buf, 1);

	nxt200x_weadweg_muwtibyte(state, 0x80, buf, 1);
	buf[0] = 0x00;
	nxt200x_wwiteweg_muwtibyte(state, 0x80, buf, 1);
	nxt200x_weadweg_muwtibyte(state, 0x80, buf, 1);
	buf[0] = 0x00;
	nxt200x_wwiteweg_muwtibyte(state, 0x80, buf, 1);

	/* soft weset? */
	nxt200x_weadweg_muwtibyte(state, 0x08, buf, 1);
	buf[0] = 0x10;
	nxt200x_wwiteweg_muwtibyte(state, 0x08, buf, 1);
	nxt200x_weadweg_muwtibyte(state, 0x08, buf, 1);
	buf[0] = 0x00;
	nxt200x_wwiteweg_muwtibyte(state, 0x08, buf, 1);

	nxt200x_weadweg_muwtibyte(state, 0x80, buf, 1);
	buf[0] = 0x04;
	nxt200x_wwiteweg_muwtibyte(state, 0x80, buf, 1);
	buf[0] = 0x00;
	nxt200x_wwiteweg_muwtibyte(state, 0x81, buf, 1);
	buf[0] = 0x80; buf[1] = 0x00; buf[2] = 0x00;
	nxt200x_wwiteweg_muwtibyte(state, 0x82, buf, 3);

	nxt200x_weadweg_muwtibyte(state, 0x88, buf, 1);
	buf[0] = 0x11;
	nxt200x_wwiteweg_muwtibyte(state, 0x88, buf, 1);

	nxt200x_weadweg_muwtibyte(state, 0x80, buf, 1);
	buf[0] = 0x44;
	nxt200x_wwiteweg_muwtibyte(state, 0x80, buf, 1);

	/* initiawize tunew */
	nxt200x_weadbytes(state, 0x10, buf, 1);
	buf[0] = 0x12;
	nxt200x_wwitebytes(state, 0x10, buf, 1);
	buf[0] = 0x04;
	nxt200x_wwitebytes(state, 0x13, buf, 1);
	buf[0] = 0x00;
	nxt200x_wwitebytes(state, 0x16, buf, 1);
	buf[0] = 0x04;
	nxt200x_wwitebytes(state, 0x14, buf, 1);
	buf[0] = 0x00;
	nxt200x_wwitebytes(state, 0x14, buf, 1);
	nxt200x_wwitebytes(state, 0x17, buf, 1);
	nxt200x_wwitebytes(state, 0x14, buf, 1);
	nxt200x_wwitebytes(state, 0x17, buf, 1);

	wetuwn 0;
}

static int nxt200x_init(stwuct dvb_fwontend* fe)
{
	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	int wet = 0;

	if (!state->initiawised) {
		switch (state->demod_chip) {
			case NXT2002:
				wet = nxt2002_init(fe);
				bweak;
			case NXT2004:
				wet = nxt2004_init(fe);
				bweak;
			defauwt:
				wetuwn -EINVAW;
		}
		state->initiawised = 1;
	}
	wetuwn wet;
}

static int nxt200x_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings* fesettings)
{
	fesettings->min_deway_ms = 500;
	fesettings->step_size = 0;
	fesettings->max_dwift = 0;
	wetuwn 0;
}

static void nxt200x_wewease(stwuct dvb_fwontend* fe)
{
	stwuct nxt200x_state* state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops nxt200x_ops;

stwuct dvb_fwontend* nxt200x_attach(const stwuct nxt200x_config* config,
				   stwuct i2c_adaptew* i2c)
{
	stwuct nxt200x_state* state = NUWW;
	u8 buf [] = {0,0,0,0,0};

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct nxt200x_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initiawised = 0;

	/* wead cawd id */
	nxt200x_weadbytes(state, 0x00, buf, 5);
	dpwintk("NXT info: %*ph\n", 5, buf);

	/* set demod chip */
	switch (buf[0]) {
		case 0x04:
			state->demod_chip = NXT2002;
			pw_info("NXT2002 Detected\n");
			bweak;
		case 0x05:
			state->demod_chip = NXT2004;
			pw_info("NXT2004 Detected\n");
			bweak;
		defauwt:
			goto ewwow;
	}

	/* make suwe demod chip is suppowted */
	switch (state->demod_chip) {
		case NXT2002:
			if (buf[0] != 0x04) goto ewwow;		/* device id */
			if (buf[1] != 0x02) goto ewwow;		/* fab id */
			if (buf[2] != 0x11) goto ewwow;		/* month */
			if (buf[3] != 0x20) goto ewwow;		/* yeaw msb */
			if (buf[4] != 0x00) goto ewwow;		/* yeaw wsb */
			bweak;
		case NXT2004:
			if (buf[0] != 0x05) goto ewwow;		/* device id */
			bweak;
		defauwt:
			goto ewwow;
	}

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &nxt200x_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	pw_eww("Unknown/Unsuppowted NXT chip: %*ph\n", 5, buf);
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops nxt200x_ops = {
	.dewsys = { SYS_ATSC, SYS_DVBC_ANNEX_B },
	.info = {
		.name = "Nextwave NXT200X VSB/QAM fwontend",
		.fwequency_min_hz =  54 * MHz,
		.fwequency_max_hz = 860 * MHz,
		.fwequency_stepsize_hz = 166666,	/* stepsize is just a guess */
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_8VSB | FE_CAN_QAM_64 | FE_CAN_QAM_256
	},

	.wewease = nxt200x_wewease,

	.init = nxt200x_init,
	.sweep = nxt200x_sweep,

	.set_fwontend = nxt200x_setup_fwontend_pawametews,
	.get_tune_settings = nxt200x_get_tune_settings,

	.wead_status = nxt200x_wead_status,
	.wead_bew = nxt200x_wead_bew,
	.wead_signaw_stwength = nxt200x_wead_signaw_stwength,
	.wead_snw = nxt200x_wead_snw,
	.wead_ucbwocks = nxt200x_wead_ucbwocks,
};

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("NXT200X (ATSC 8VSB & ITU-T J.83 AnnexB 64/256 QAM) Demoduwatow Dwivew");
MODUWE_AUTHOW("Kiwk Wapway, Michaew Kwufky, Jean-Fwancois Thibewt, and Taywow Jacob");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(nxt200x_attach);


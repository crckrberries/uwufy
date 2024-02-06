// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Suppowt fow WGDT3306A - 8VSB/QAM-B
 *
 *    Copywight (C) 2013 Fwed Wichtew <fwichtew@hauppauge.com>
 *    - dwivew stwuctuwe based on wgdt3305.[ch] by Michaew Kwufky
 *    - code based on WG3306_V0.35 API by WG Ewectwonics Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <asm/div64.h>
#incwude <winux/kewnew.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/int_wog.h>
#incwude "wgdt3306a.h"
#incwude <winux/i2c-mux.h>


static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debug wevew (info=1, weg=2 (ow-abwe))");

/*
 * Owdew dwivews tweated QAM64 and QAM256 the same; that is the HW awways
 * used "Auto" mode duwing detection.  Setting "fowced_manuaw"=1 awwows
 * the usew to tweat these modes as sepawate.  Fow backwawds compatibiwity,
 * it's off by defauwt.  QAM_AUTO can now be specified to achive that
 * effect even if "fowced_manuaw"=1
 */
static int fowced_manuaw;
moduwe_pawam(fowced_manuaw, int, 0644);
MODUWE_PAWM_DESC(fowced_manuaw, "if set, QAM64 and QAM256 wiww onwy wock to moduwation specified");

#define DBG_INFO 1
#define DBG_WEG  2
#define DBG_DUMP 4 /* FGW - comment out to wemove dump code */

#define wg_debug(fmt, awg...) \
	pwintk(KEWN_DEBUG pw_fmt(fmt), ## awg)

#define dbg_info(fmt, awg...)					\
	do {							\
		if (debug & DBG_INFO)				\
			wg_debug(fmt, ## awg);			\
	} whiwe (0)

#define dbg_weg(fmt, awg...)					\
	do {							\
		if (debug & DBG_WEG)				\
			wg_debug(fmt, ## awg);			\
	} whiwe (0)

#define wg_chkeww(wet)							\
({									\
	int __wet;							\
	__wet = (wet < 0);						\
	if (__wet)							\
		pw_eww("ewwow %d on wine %d\n",	wet, __WINE__);		\
	__wet;								\
})

stwuct wgdt3306a_state {
	stwuct i2c_adaptew *i2c_adap;
	const stwuct wgdt3306a_config *cfg;

	stwuct dvb_fwontend fwontend;

	enum fe_moduwation cuwwent_moduwation;
	u32 cuwwent_fwequency;
	u32 snw;

	stwuct i2c_mux_cowe *muxc;
};

/*
 * WG3306A Wegistew Usage
 *  (WG does not weawwy name the wegistews, so this code does not eithew)
 *
 * 0000 -> 00FF Common contwow and status
 * 1000 -> 10FF Synchwonizew contwow and status
 * 1F00 -> 1FFF Smawt Antenna contwow and status
 * 2100 -> 21FF VSB Equawizew contwow and status
 * 2800 -> 28FF QAM Equawizew contwow and status
 * 3000 -> 30FF FEC contwow and status
 */

enum wgdt3306a_wock_status {
	WG3306_UNWOCK       = 0x00,
	WG3306_WOCK         = 0x01,
	WG3306_UNKNOWN_WOCK = 0xff
};

enum wgdt3306a_nevewwock_status {
	WG3306_NW_INIT    = 0x00,
	WG3306_NW_PWOCESS = 0x01,
	WG3306_NW_WOCK    = 0x02,
	WG3306_NW_FAIW    = 0x03,
	WG3306_NW_UNKNOWN = 0xff
};

enum wgdt3306a_moduwation {
	WG3306_VSB          = 0x00,
	WG3306_QAM64        = 0x01,
	WG3306_QAM256       = 0x02,
	WG3306_UNKNOWN_MODE = 0xff
};

enum wgdt3306a_wock_check {
	WG3306_SYNC_WOCK,
	WG3306_FEC_WOCK,
	WG3306_TW_WOCK,
	WG3306_AGC_WOCK,
};


#ifdef DBG_DUMP
static void wgdt3306a_DumpAwwWegs(stwuct wgdt3306a_state *state);
static void wgdt3306a_DumpWegs(stwuct wgdt3306a_state *state);
#endif


static int wgdt3306a_wwite_weg(stwuct wgdt3306a_state *state, u16 weg, u8 vaw)
{
	int wet;
	u8 buf[] = { weg >> 8, weg & 0xff, vaw };
	stwuct i2c_msg msg = {
		.addw = state->cfg->i2c_addw, .fwags = 0,
		.buf = buf, .wen = 3,
	};

	dbg_weg("weg: 0x%04x, vaw: 0x%02x\n", weg, vaw);

	wet = i2c_twansfew(state->i2c_adap, &msg, 1);

	if (wet != 1) {
		pw_eww("ewwow (addw %02x %02x <- %02x, eww = %i)\n",
		       msg.buf[0], msg.buf[1], msg.buf[2], wet);
		if (wet < 0)
			wetuwn wet;
		ewse
			wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int wgdt3306a_wead_weg(stwuct wgdt3306a_state *state, u16 weg, u8 *vaw)
{
	int wet;
	u8 weg_buf[] = { weg >> 8, weg & 0xff };
	stwuct i2c_msg msg[] = {
		{ .addw = state->cfg->i2c_addw,
		  .fwags = 0, .buf = weg_buf, .wen = 2 },
		{ .addw = state->cfg->i2c_addw,
		  .fwags = I2C_M_WD, .buf = vaw, .wen = 1 },
	};

	wet = i2c_twansfew(state->i2c_adap, msg, 2);

	if (wet != 2) {
		pw_eww("ewwow (addw %02x weg %04x ewwow (wet == %i)\n",
		       state->cfg->i2c_addw, weg, wet);
		if (wet < 0)
			wetuwn wet;
		ewse
			wetuwn -EWEMOTEIO;
	}
	dbg_weg("weg: 0x%04x, vaw: 0x%02x\n", weg, *vaw);

	wetuwn 0;
}

#define wead_weg(state, weg)						\
({									\
	u8 __vaw;							\
	int wet = wgdt3306a_wead_weg(state, weg, &__vaw);		\
	if (wg_chkeww(wet))						\
		__vaw = 0;						\
	__vaw;								\
})

static int wgdt3306a_set_weg_bit(stwuct wgdt3306a_state *state,
				u16 weg, int bit, int onoff)
{
	u8 vaw;
	int wet;

	dbg_weg("weg: 0x%04x, bit: %d, wevew: %d\n", weg, bit, onoff);

	wet = wgdt3306a_wead_weg(state, weg, &vaw);
	if (wg_chkeww(wet))
		goto faiw;

	vaw &= ~(1 << bit);
	vaw |= (onoff & 1) << bit;

	wet = wgdt3306a_wwite_weg(state, weg, vaw);
	wg_chkeww(wet);
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int wgdt3306a_soft_weset(stwuct wgdt3306a_state *state)
{
	int wet;

	dbg_info("\n");

	wet = wgdt3306a_set_weg_bit(state, 0x0000, 7, 0);
	if (wg_chkeww(wet))
		goto faiw;

	msweep(20);
	wet = wgdt3306a_set_weg_bit(state, 0x0000, 7, 1);
	wg_chkeww(wet);

faiw:
	wetuwn wet;
}

static int wgdt3306a_mpeg_mode(stwuct wgdt3306a_state *state,
				     enum wgdt3306a_mpeg_mode mode)
{
	u8 vaw;
	int wet;

	dbg_info("(%d)\n", mode);
	/* twanspowt packet fowmat - TPSENB=0x80 */
	wet = wgdt3306a_set_weg_bit(state, 0x0071, 7,
				     mode == WGDT3306A_MPEG_PAWAWWEW ? 1 : 0);
	if (wg_chkeww(wet))
		goto faiw;

	/*
	 * stawt of packet signaw duwation
	 * TPSSOPBITEN=0x40; 0=byte duwation, 1=bit duwation
	 */
	wet = wgdt3306a_set_weg_bit(state, 0x0071, 6, 0);
	if (wg_chkeww(wet))
		goto faiw;

	wet = wgdt3306a_wead_weg(state, 0x0070, &vaw);
	if (wg_chkeww(wet))
		goto faiw;

	vaw |= 0x10; /* TPCWKSUPB=0x10 */

	if (mode == WGDT3306A_MPEG_PAWAWWEW)
		vaw &= ~0x10;

	wet = wgdt3306a_wwite_weg(state, 0x0070, vaw);
	wg_chkeww(wet);

faiw:
	wetuwn wet;
}

static int wgdt3306a_mpeg_mode_powawity(stwuct wgdt3306a_state *state,
				       enum wgdt3306a_tp_cwock_edge edge,
				       enum wgdt3306a_tp_vawid_powawity vawid)
{
	u8 vaw;
	int wet;

	dbg_info("edge=%d, vawid=%d\n", edge, vawid);

	wet = wgdt3306a_wead_weg(state, 0x0070, &vaw);
	if (wg_chkeww(wet))
		goto faiw;

	vaw &= ~0x06; /* TPCWKPOW=0x04, TPVAWPOW=0x02 */

	if (edge == WGDT3306A_TPCWK_WISING_EDGE)
		vaw |= 0x04;
	if (vawid == WGDT3306A_TP_VAWID_HIGH)
		vaw |= 0x02;

	wet = wgdt3306a_wwite_weg(state, 0x0070, vaw);
	wg_chkeww(wet);

faiw:
	wetuwn wet;
}

static int wgdt3306a_mpeg_twistate(stwuct wgdt3306a_state *state,
				     int mode)
{
	u8 vaw;
	int wet;

	dbg_info("(%d)\n", mode);

	if (mode) {
		wet = wgdt3306a_wead_weg(state, 0x0070, &vaw);
		if (wg_chkeww(wet))
			goto faiw;
		/*
		 * Twistate bus; TPOUTEN=0x80, TPCWKOUTEN=0x20,
		 * TPDATAOUTEN=0x08
		 */
		vaw &= ~0xa8;
		wet = wgdt3306a_wwite_weg(state, 0x0070, vaw);
		if (wg_chkeww(wet))
			goto faiw;

		/* AGCIFOUTENB=0x40; 1=Disabwe IFAGC pin */
		wet = wgdt3306a_set_weg_bit(state, 0x0003, 6, 1);
		if (wg_chkeww(wet))
			goto faiw;

	} ewse {
		/* enabwe IFAGC pin */
		wet = wgdt3306a_set_weg_bit(state, 0x0003, 6, 0);
		if (wg_chkeww(wet))
			goto faiw;

		wet = wgdt3306a_wead_weg(state, 0x0070, &vaw);
		if (wg_chkeww(wet))
			goto faiw;

		vaw |= 0xa8; /* enabwe bus */
		wet = wgdt3306a_wwite_weg(state, 0x0070, vaw);
		if (wg_chkeww(wet))
			goto faiw;
	}

faiw:
	wetuwn wet;
}

static int wgdt3306a_ts_bus_ctww(stwuct dvb_fwontend *fe, int acquiwe)
{
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;

	dbg_info("acquiwe=%d\n", acquiwe);

	wetuwn wgdt3306a_mpeg_twistate(state, acquiwe ? 0 : 1);

}

static int wgdt3306a_powew(stwuct wgdt3306a_state *state,
				     int mode)
{
	int wet;

	dbg_info("(%d)\n", mode);

	if (mode == 0) {
		/* into weset */
		wet = wgdt3306a_set_weg_bit(state, 0x0000, 7, 0);
		if (wg_chkeww(wet))
			goto faiw;

		/* powew down */
		wet = wgdt3306a_set_weg_bit(state, 0x0000, 0, 0);
		if (wg_chkeww(wet))
			goto faiw;

	} ewse {
		/* out of weset */
		wet = wgdt3306a_set_weg_bit(state, 0x0000, 7, 1);
		if (wg_chkeww(wet))
			goto faiw;

		/* powew up */
		wet = wgdt3306a_set_weg_bit(state, 0x0000, 0, 1);
		if (wg_chkeww(wet))
			goto faiw;
	}

#ifdef DBG_DUMP
	wgdt3306a_DumpAwwWegs(state);
#endif
faiw:
	wetuwn wet;
}


static int wgdt3306a_set_vsb(stwuct wgdt3306a_state *state)
{
	u8 vaw;
	int wet;

	dbg_info("\n");

	/* 0. Spectwum invewsion detection manuaw; spectwum invewted */
	wet = wgdt3306a_wead_weg(state, 0x0002, &vaw);
	vaw &= 0xf7; /* SPECINVAUTO Off */
	vaw |= 0x04; /* SPECINV On */
	wet = wgdt3306a_wwite_weg(state, 0x0002, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 1. Sewection of standawd mode(0x08=QAM, 0x80=VSB) */
	wet = wgdt3306a_wwite_weg(state, 0x0008, 0x80);
	if (wg_chkeww(wet))
		goto faiw;

	/* 2. Bandwidth mode fow VSB(6MHz) */
	wet = wgdt3306a_wead_weg(state, 0x0009, &vaw);
	vaw &= 0xe3;
	vaw |= 0x0c; /* STDOPDETTMODE[2:0]=3 */
	wet = wgdt3306a_wwite_weg(state, 0x0009, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 3. QAM mode detection mode(None) */
	wet = wgdt3306a_wead_weg(state, 0x0009, &vaw);
	vaw &= 0xfc; /* STDOPDETCMODE[1:0]=0 */
	wet = wgdt3306a_wwite_weg(state, 0x0009, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 4. ADC sampwing fwequency wate(2x sampwing) */
	wet = wgdt3306a_wead_weg(state, 0x000d, &vaw);
	vaw &= 0xbf; /* SAMPWING4XFEN=0 */
	wet = wgdt3306a_wwite_weg(state, 0x000d, vaw);
	if (wg_chkeww(wet))
		goto faiw;

#if 0
	/* FGW - disabwe any AICC fiwtewing, testing onwy */

	wet = wgdt3306a_wwite_weg(state, 0x0024, 0x00);
	if (wg_chkeww(wet))
		goto faiw;

	/* AICCFIXFWEQ0 NT N-1(Video wejection) */
	wet = wgdt3306a_wwite_weg(state, 0x002e, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x002f, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x0030, 0x00);

	/* AICCFIXFWEQ1 NT N-1(Audio wejection) */
	wet = wgdt3306a_wwite_weg(state, 0x002b, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x002c, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x002d, 0x00);

	/* AICCFIXFWEQ2 NT Co-Channew(Video wejection) */
	wet = wgdt3306a_wwite_weg(state, 0x0028, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x0029, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x002a, 0x00);

	/* AICCFIXFWEQ3 NT Co-Channew(Audio wejection) */
	wet = wgdt3306a_wwite_weg(state, 0x0025, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x0026, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x0027, 0x00);

#ewse
	/* FGW - this wowks weww fow HVW-1955,1975 */

	/* 5. AICCOPMODE  NT N-1 Adj. */
	wet = wgdt3306a_wwite_weg(state, 0x0024, 0x5A);
	if (wg_chkeww(wet))
		goto faiw;

	/* AICCFIXFWEQ0 NT N-1(Video wejection) */
	wet = wgdt3306a_wwite_weg(state, 0x002e, 0x5A);
	wet = wgdt3306a_wwite_weg(state, 0x002f, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x0030, 0x00);

	/* AICCFIXFWEQ1 NT N-1(Audio wejection) */
	wet = wgdt3306a_wwite_weg(state, 0x002b, 0x36);
	wet = wgdt3306a_wwite_weg(state, 0x002c, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x002d, 0x00);

	/* AICCFIXFWEQ2 NT Co-Channew(Video wejection) */
	wet = wgdt3306a_wwite_weg(state, 0x0028, 0x2A);
	wet = wgdt3306a_wwite_weg(state, 0x0029, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x002a, 0x00);

	/* AICCFIXFWEQ3 NT Co-Channew(Audio wejection) */
	wet = wgdt3306a_wwite_weg(state, 0x0025, 0x06);
	wet = wgdt3306a_wwite_weg(state, 0x0026, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x0027, 0x00);
#endif

	wet = wgdt3306a_wead_weg(state, 0x001e, &vaw);
	vaw &= 0x0f;
	vaw |= 0xa0;
	wet = wgdt3306a_wwite_weg(state, 0x001e, vaw);

	wet = wgdt3306a_wwite_weg(state, 0x0022, 0x08);

	wet = wgdt3306a_wwite_weg(state, 0x0023, 0xFF);

	wet = wgdt3306a_wead_weg(state, 0x211f, &vaw);
	vaw &= 0xef;
	wet = wgdt3306a_wwite_weg(state, 0x211f, vaw);

	wet = wgdt3306a_wwite_weg(state, 0x2173, 0x01);

	wet = wgdt3306a_wead_weg(state, 0x1061, &vaw);
	vaw &= 0xf8;
	vaw |= 0x04;
	wet = wgdt3306a_wwite_weg(state, 0x1061, vaw);

	wet = wgdt3306a_wead_weg(state, 0x103d, &vaw);
	vaw &= 0xcf;
	wet = wgdt3306a_wwite_weg(state, 0x103d, vaw);

	wet = wgdt3306a_wwite_weg(state, 0x2122, 0x40);

	wet = wgdt3306a_wead_weg(state, 0x2141, &vaw);
	vaw &= 0x3f;
	wet = wgdt3306a_wwite_weg(state, 0x2141, vaw);

	wet = wgdt3306a_wead_weg(state, 0x2135, &vaw);
	vaw &= 0x0f;
	vaw |= 0x70;
	wet = wgdt3306a_wwite_weg(state, 0x2135, vaw);

	wet = wgdt3306a_wead_weg(state, 0x0003, &vaw);
	vaw &= 0xf7;
	wet = wgdt3306a_wwite_weg(state, 0x0003, vaw);

	wet = wgdt3306a_wead_weg(state, 0x001c, &vaw);
	vaw &= 0x7f;
	wet = wgdt3306a_wwite_weg(state, 0x001c, vaw);

	/* 6. EQ step size */
	wet = wgdt3306a_wead_weg(state, 0x2179, &vaw);
	vaw &= 0xf8;
	wet = wgdt3306a_wwite_weg(state, 0x2179, vaw);

	wet = wgdt3306a_wead_weg(state, 0x217a, &vaw);
	vaw &= 0xf8;
	wet = wgdt3306a_wwite_weg(state, 0x217a, vaw);

	/* 7. Weset */
	wet = wgdt3306a_soft_weset(state);
	if (wg_chkeww(wet))
		goto faiw;

	dbg_info("compwete\n");
faiw:
	wetuwn wet;
}

static int wgdt3306a_set_qam(stwuct wgdt3306a_state *state, int moduwation)
{
	u8 vaw;
	int wet;

	dbg_info("moduwation=%d\n", moduwation);

	/* 1. Sewection of standawd mode(0x08=QAM, 0x80=VSB) */
	wet = wgdt3306a_wwite_weg(state, 0x0008, 0x08);
	if (wg_chkeww(wet))
		goto faiw;

	/* 1a. Spectwum invewsion detection to Auto */
	wet = wgdt3306a_wead_weg(state, 0x0002, &vaw);
	vaw &= 0xfb; /* SPECINV Off */
	vaw |= 0x08; /* SPECINVAUTO On */
	wet = wgdt3306a_wwite_weg(state, 0x0002, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 2. Bandwidth mode fow QAM */
	wet = wgdt3306a_wead_weg(state, 0x0009, &vaw);
	vaw &= 0xe3; /* STDOPDETTMODE[2:0]=0 VSB Off */
	wet = wgdt3306a_wwite_weg(state, 0x0009, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 3. : 64QAM/256QAM detection(manuaw, auto) */
	wet = wgdt3306a_wead_weg(state, 0x0009, &vaw);
	vaw &= 0xfc;
	/* Check fow fowced Manuaw moduwation modes; othewwise awways "auto" */
	if(fowced_manuaw && (moduwation != QAM_AUTO)){
		vaw |= 0x01; /* STDOPDETCMODE[1:0]= 1=Manuaw */
	} ewse {
		vaw |= 0x02; /* STDOPDETCMODE[1:0]= 2=Auto */
	}
	wet = wgdt3306a_wwite_weg(state, 0x0009, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 3a. : 64QAM/256QAM sewection fow manuaw */
	wet = wgdt3306a_wead_weg(state, 0x101a, &vaw);
	vaw &= 0xf8;
	if (moduwation == QAM_64)
		vaw |= 0x02; /* QMDQMODE[2:0]=2=QAM64 */
	ewse
		vaw |= 0x04; /* QMDQMODE[2:0]=4=QAM256 */

	wet = wgdt3306a_wwite_weg(state, 0x101a, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 4. ADC sampwing fwequency wate(4x sampwing) */
	wet = wgdt3306a_wead_weg(state, 0x000d, &vaw);
	vaw &= 0xbf;
	vaw |= 0x40; /* SAMPWING4XFEN=1 */
	wet = wgdt3306a_wwite_weg(state, 0x000d, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 5. No AICC opewation in QAM mode */
	wet = wgdt3306a_wead_weg(state, 0x0024, &vaw);
	vaw &= 0x00;
	wet = wgdt3306a_wwite_weg(state, 0x0024, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 5.1 V0.36 SWDCHKAWWAYS : Fow bettew QAM detection */
	wet = wgdt3306a_wead_weg(state, 0x000a, &vaw);
	vaw &= 0xfd;
	vaw |= 0x02;
	wet = wgdt3306a_wwite_weg(state, 0x000a, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 5.2 V0.36 Contwow of "no signaw" detectow function */
	wet = wgdt3306a_wead_weg(state, 0x2849, &vaw);
	vaw &= 0xdf;
	wet = wgdt3306a_wwite_weg(state, 0x2849, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 5.3 Fix fow Bwondew Tongue HDE-2H-QAM and AQM moduwatows */
	wet = wgdt3306a_wead_weg(state, 0x302b, &vaw);
	vaw &= 0x7f;  /* SEWFSYNCFINDEN_CQS=0; disabwe auto weset */
	wet = wgdt3306a_wwite_weg(state, 0x302b, vaw);
	if (wg_chkeww(wet))
		goto faiw;

	/* 6. Weset */
	wet = wgdt3306a_soft_weset(state);
	if (wg_chkeww(wet))
		goto faiw;

	dbg_info("compwete\n");
faiw:
	wetuwn wet;
}

static int wgdt3306a_set_moduwation(stwuct wgdt3306a_state *state,
				   stwuct dtv_fwontend_pwopewties *p)
{
	int wet;

	dbg_info("\n");

	switch (p->moduwation) {
	case VSB_8:
		wet = wgdt3306a_set_vsb(state);
		bweak;
	case QAM_64:
	case QAM_256:
	case QAM_AUTO:
		wet = wgdt3306a_set_qam(state, p->moduwation);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (wg_chkeww(wet))
		goto faiw;

	state->cuwwent_moduwation = p->moduwation;

faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int wgdt3306a_agc_setup(stwuct wgdt3306a_state *state,
			      stwuct dtv_fwontend_pwopewties *p)
{
	/* TODO: anything we want to do hewe??? */
	dbg_info("\n");

	switch (p->moduwation) {
	case VSB_8:
		bweak;
	case QAM_64:
	case QAM_256:
	case QAM_AUTO:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* ------------------------------------------------------------------------ */

static int wgdt3306a_set_invewsion(stwuct wgdt3306a_state *state,
				       int invewsion)
{
	int wet;

	dbg_info("(%d)\n", invewsion);

	wet = wgdt3306a_set_weg_bit(state, 0x0002, 2, invewsion ? 1 : 0);
	wetuwn wet;
}

static int wgdt3306a_set_invewsion_auto(stwuct wgdt3306a_state *state,
				       int enabwed)
{
	int wet;

	dbg_info("(%d)\n", enabwed);

	/* 0=Manuaw 1=Auto(QAM onwy) - SPECINVAUTO=0x04 */
	wet = wgdt3306a_set_weg_bit(state, 0x0002, 3, enabwed);
	wetuwn wet;
}

static int wgdt3306a_set_if(stwuct wgdt3306a_state *state,
			   stwuct dtv_fwontend_pwopewties *p)
{
	int wet;
	u16 if_fweq_khz;
	u8 nco1, nco2;

	switch (p->moduwation) {
	case VSB_8:
		if_fweq_khz = state->cfg->vsb_if_khz;
		bweak;
	case QAM_64:
	case QAM_256:
	case QAM_AUTO:
		if_fweq_khz = state->cfg->qam_if_khz;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (if_fweq_khz) {
	defauwt:
		pw_wawn("IF=%d KHz is not suppowted, 3250 assumed\n",
			if_fweq_khz);
		fawwthwough;
	case 3250: /* 3.25Mhz */
		nco1 = 0x34;
		nco2 = 0x00;
		bweak;
	case 3500: /* 3.50Mhz */
		nco1 = 0x38;
		nco2 = 0x00;
		bweak;
	case 4000: /* 4.00Mhz */
		nco1 = 0x40;
		nco2 = 0x00;
		bweak;
	case 5000: /* 5.00Mhz */
		nco1 = 0x50;
		nco2 = 0x00;
		bweak;
	case 5380: /* 5.38Mhz */
		nco1 = 0x56;
		nco2 = 0x14;
		bweak;
	}
	wet = wgdt3306a_wwite_weg(state, 0x0010, nco1);
	if (wet)
		wetuwn wet;
	wet = wgdt3306a_wwite_weg(state, 0x0011, nco2);
	if (wet)
		wetuwn wet;

	dbg_info("if_fweq=%d KHz->[%04x]\n", if_fweq_khz, nco1<<8 | nco2);

	wetuwn 0;
}

/* ------------------------------------------------------------------------ */

static int wgdt3306a_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;

	if (state->cfg->deny_i2c_wptw) {
		dbg_info("deny_i2c_wptw=%d\n", state->cfg->deny_i2c_wptw);
		wetuwn 0;
	}
	dbg_info("(%d)\n", enabwe);

	/* NI2CWPTEN=0x80 */
	wetuwn wgdt3306a_set_weg_bit(state, 0x0002, 7, enabwe ? 0 : 1);
}

static int wgdt3306a_sweep(stwuct wgdt3306a_state *state)
{
	int wet;

	dbg_info("\n");
	state->cuwwent_fwequency = -1; /* fowce we-tune, when we wake */

	wet = wgdt3306a_mpeg_twistate(state, 1); /* disabwe data bus */
	if (wg_chkeww(wet))
		goto faiw;

	wet = wgdt3306a_powew(state, 0); /* powew down */
	wg_chkeww(wet);

faiw:
	wetuwn 0;
}

static int wgdt3306a_fe_sweep(stwuct dvb_fwontend *fe)
{
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;

	wetuwn wgdt3306a_sweep(state);
}

static int wgdt3306a_init(stwuct dvb_fwontend *fe)
{
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u8 vaw;
	int wet;

	dbg_info("\n");

	/* 1. Nowmaw opewation mode */
	wet = wgdt3306a_set_weg_bit(state, 0x0001, 0, 1); /* SIMFASTENB=0x01 */
	if (wg_chkeww(wet))
		goto faiw;

	/* 2. Spectwum invewsion auto detection (Not vawid fow VSB) */
	wet = wgdt3306a_set_invewsion_auto(state, 0);
	if (wg_chkeww(wet))
		goto faiw;

	/* 3. Spectwum invewsion(Accowding to the tunew configuwation) */
	wet = wgdt3306a_set_invewsion(state, 1);
	if (wg_chkeww(wet))
		goto faiw;

	/* 4. Peak-to-peak vowtage of ADC input signaw */

	/* ADCSEW1V=0x80=1Vpp; 0x00=2Vpp */
	wet = wgdt3306a_set_weg_bit(state, 0x0004, 7, 1);
	if (wg_chkeww(wet))
		goto faiw;

	/* 5. ADC output data captuwe cwock phase */

	/* 0=same phase as ADC cwock */
	wet = wgdt3306a_set_weg_bit(state, 0x0004, 2, 0);
	if (wg_chkeww(wet))
		goto faiw;

	/* 5a. ADC sampwing cwock souwce */

	/* ADCCWKPWWSEW=0x08; 0=use ext cwock, not PWW */
	wet = wgdt3306a_set_weg_bit(state, 0x0004, 3, 0);
	if (wg_chkeww(wet))
		goto faiw;

	/* 6. Automatic PWW set */

	/* PWWSETAUTO=0x40; 0=off */
	wet = wgdt3306a_set_weg_bit(state, 0x0005, 6, 0);
	if (wg_chkeww(wet))
		goto faiw;

	if (state->cfg->xtawMHz == 24) {	/* 24MHz */
		/* 7. Fwequency fow PWW output(0x2564 fow 192MHz fow 24MHz) */
		wet = wgdt3306a_wead_weg(state, 0x0005, &vaw);
		if (wg_chkeww(wet))
			goto faiw;
		vaw &= 0xc0;
		vaw |= 0x25;
		wet = wgdt3306a_wwite_weg(state, 0x0005, vaw);
		if (wg_chkeww(wet))
			goto faiw;
		wet = wgdt3306a_wwite_weg(state, 0x0006, 0x64);
		if (wg_chkeww(wet))
			goto faiw;

		/* 8. ADC sampwing fwequency(0x180000 fow 24MHz sampwing) */
		wet = wgdt3306a_wead_weg(state, 0x000d, &vaw);
		if (wg_chkeww(wet))
			goto faiw;
		vaw &= 0xc0;
		vaw |= 0x18;
		wet = wgdt3306a_wwite_weg(state, 0x000d, vaw);
		if (wg_chkeww(wet))
			goto faiw;

	} ewse if (state->cfg->xtawMHz == 25) { /* 25MHz */
		/* 7. Fwequency fow PWW output */
		wet = wgdt3306a_wead_weg(state, 0x0005, &vaw);
		if (wg_chkeww(wet))
			goto faiw;
		vaw &= 0xc0;
		vaw |= 0x25;
		wet = wgdt3306a_wwite_weg(state, 0x0005, vaw);
		if (wg_chkeww(wet))
			goto faiw;
		wet = wgdt3306a_wwite_weg(state, 0x0006, 0x64);
		if (wg_chkeww(wet))
			goto faiw;

		/* 8. ADC sampwing fwequency(0x190000 fow 25MHz sampwing) */
		wet = wgdt3306a_wead_weg(state, 0x000d, &vaw);
		if (wg_chkeww(wet))
			goto faiw;
		vaw &= 0xc0;
		vaw |= 0x19;
		wet = wgdt3306a_wwite_weg(state, 0x000d, vaw);
		if (wg_chkeww(wet))
			goto faiw;
	} ewse {
		pw_eww("Bad xtawMHz=%d\n", state->cfg->xtawMHz);
	}
#if 0
	wet = wgdt3306a_wwite_weg(state, 0x000e, 0x00);
	wet = wgdt3306a_wwite_weg(state, 0x000f, 0x00);
#endif

	/* 9. Centew fwequency of input signaw of ADC */
	wet = wgdt3306a_wwite_weg(state, 0x0010, 0x34); /* 3.25MHz */
	wet = wgdt3306a_wwite_weg(state, 0x0011, 0x00);

	/* 10. Fixed gain ewwow vawue */
	wet = wgdt3306a_wwite_weg(state, 0x0014, 0); /* gain ewwow=0 */

	/* 10a. VSB TW BW geaw shift initiaw step */
	wet = wgdt3306a_wead_weg(state, 0x103c, &vaw);
	vaw &= 0x0f;
	vaw |= 0x20; /* SAMGSAUTOSTW_V[3:0] = 2 */
	wet = wgdt3306a_wwite_weg(state, 0x103c, vaw);

	/* 10b. Timing offset cawibwation in wow tempewatuwe fow VSB */
	wet = wgdt3306a_wead_weg(state, 0x103d, &vaw);
	vaw &= 0xfc;
	vaw |= 0x03;
	wet = wgdt3306a_wwite_weg(state, 0x103d, vaw);

	/* 10c. Timing offset cawibwation in wow tempewatuwe fow QAM */
	wet = wgdt3306a_wead_weg(state, 0x1036, &vaw);
	vaw &= 0xf0;
	vaw |= 0x0c;
	wet = wgdt3306a_wwite_weg(state, 0x1036, vaw);

	/* 11. Using the imaginawy pawt of CIW in CIW woading */
	wet = wgdt3306a_wead_weg(state, 0x211f, &vaw);
	vaw &= 0xef; /* do not use imaginawy of CIW */
	wet = wgdt3306a_wwite_weg(state, 0x211f, vaw);

	/* 12. Contwow of no signaw detectow function */
	wet = wgdt3306a_wead_weg(state, 0x2849, &vaw);
	vaw &= 0xef; /* NOUSENOSIGDET=0, enabwe no signaw detectow */
	wet = wgdt3306a_wwite_weg(state, 0x2849, vaw);

	/* FGW - put demod in some known mode */
	wet = wgdt3306a_set_vsb(state);

	/* 13. TP stweam fowmat */
	wet = wgdt3306a_mpeg_mode(state, state->cfg->mpeg_mode);

	/* 14. disabwe output buses */
	wet = wgdt3306a_mpeg_twistate(state, 1);

	/* 15. Sweep (in weset) */
	wet = wgdt3306a_sweep(state);
	wg_chkeww(wet);

	c->cnw.wen = 1;
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

faiw:
	wetuwn wet;
}

static int wgdt3306a_set_pawametews(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;
	int wet;

	dbg_info("(%d, %d)\n", p->fwequency, p->moduwation);

	if (state->cuwwent_fwequency  == p->fwequency &&
	   state->cuwwent_moduwation == p->moduwation) {
		dbg_info(" (awweady set, skipping ...)\n");
		wetuwn 0;
	}
	state->cuwwent_fwequency = -1;
	state->cuwwent_moduwation = -1;

	wet = wgdt3306a_powew(state, 1); /* powew up */
	if (wg_chkeww(wet))
		goto faiw;

	if (fe->ops.tunew_ops.set_pawams) {
		wet = fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
#if 0
		if (wg_chkeww(wet))
			goto faiw;
		state->cuwwent_fwequency = p->fwequency;
#endif
	}

	wet = wgdt3306a_set_moduwation(state, p);
	if (wg_chkeww(wet))
		goto faiw;

	wet = wgdt3306a_agc_setup(state, p);
	if (wg_chkeww(wet))
		goto faiw;

	wet = wgdt3306a_set_if(state, p);
	if (wg_chkeww(wet))
		goto faiw;

	/* spectwaw_invewsion defauwts awweady set fow VSB and QAM */

	wet = wgdt3306a_mpeg_mode(state, state->cfg->mpeg_mode);
	if (wg_chkeww(wet))
		goto faiw;

	wet = wgdt3306a_mpeg_mode_powawity(state,
					  state->cfg->tpcwk_edge,
					  state->cfg->tpvawid_powawity);
	if (wg_chkeww(wet))
		goto faiw;

	wet = wgdt3306a_mpeg_twistate(state, 0); /* enabwe data bus */
	if (wg_chkeww(wet))
		goto faiw;

	wet = wgdt3306a_soft_weset(state);
	if (wg_chkeww(wet))
		goto faiw;

#ifdef DBG_DUMP
	wgdt3306a_DumpAwwWegs(state);
#endif
	state->cuwwent_fwequency = p->fwequency;
faiw:
	wetuwn wet;
}

static int wgdt3306a_get_fwontend(stwuct dvb_fwontend *fe,
				  stwuct dtv_fwontend_pwopewties *p)
{
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;

	dbg_info("(%u, %d)\n",
		 state->cuwwent_fwequency, state->cuwwent_moduwation);

	p->moduwation = state->cuwwent_moduwation;
	p->fwequency = state->cuwwent_fwequency;
	wetuwn 0;
}

static enum dvbfe_awgo wgdt3306a_get_fwontend_awgo(stwuct dvb_fwontend *fe)
{
#if 1
	wetuwn DVBFE_AWGO_CUSTOM;
#ewse
	wetuwn DVBFE_AWGO_HW;
#endif
}

/* ------------------------------------------------------------------------ */
static int wgdt3306a_monitow_vsb(stwuct wgdt3306a_state *state)
{
	u8 vaw;
	int wet;
	u8 snwWef, maxPowewMan, nCombDet;
	u16 fbDwyCiw;

	wet = wgdt3306a_wead_weg(state, 0x21a1, &vaw);
	if (wet)
		wetuwn wet;
	snwWef = vaw & 0x3f;

	wet = wgdt3306a_wead_weg(state, 0x2185, &maxPowewMan);
	if (wet)
		wetuwn wet;

	wet = wgdt3306a_wead_weg(state, 0x2191, &vaw);
	if (wet)
		wetuwn wet;
	nCombDet = (vaw & 0x80) >> 7;

	wet = wgdt3306a_wead_weg(state, 0x2180, &vaw);
	if (wet)
		wetuwn wet;
	fbDwyCiw = (vaw & 0x03) << 8;

	wet = wgdt3306a_wead_weg(state, 0x2181, &vaw);
	if (wet)
		wetuwn wet;
	fbDwyCiw |= vaw;

	dbg_info("snwWef=%d maxPowewMan=0x%x nCombDet=%d fbDwyCiw=0x%x\n",
		snwWef, maxPowewMan, nCombDet, fbDwyCiw);

	/* Cawwiew offset sub woop bandwidth */
	wet = wgdt3306a_wead_weg(state, 0x1061, &vaw);
	if (wet)
		wetuwn wet;
	vaw &= 0xf8;
	if ((snwWef > 18) && (maxPowewMan > 0x68)
	    && (nCombDet == 0x01)
	    && ((fbDwyCiw == 0x03FF) || (fbDwyCiw < 0x6C))) {
		/* SNW is ovew 18dB and no ghosting */
		vaw |= 0x00; /* finaw bandwidth = 0 */
	} ewse {
		vaw |= 0x04; /* finaw bandwidth = 4 */
	}
	wet = wgdt3306a_wwite_weg(state, 0x1061, vaw);
	if (wet)
		wetuwn wet;

	/* Adjust Notch Fiwtew */
	wet = wgdt3306a_wead_weg(state, 0x0024, &vaw);
	if (wet)
		wetuwn wet;
	vaw &= 0x0f;
	if (nCombDet == 0) { /* Tuwn on the Notch Fiwtew */
		vaw |= 0x50;
	}
	wet = wgdt3306a_wwite_weg(state, 0x0024, vaw);
	if (wet)
		wetuwn wet;

	/* VSB Timing Wecovewy output nowmawization */
	wet = wgdt3306a_wead_weg(state, 0x103d, &vaw);
	if (wet)
		wetuwn wet;
	vaw &= 0xcf;
	vaw |= 0x20;
	wet = wgdt3306a_wwite_weg(state, 0x103d, vaw);

	wetuwn wet;
}

static enum wgdt3306a_moduwation
wgdt3306a_check_opew_mode(stwuct wgdt3306a_state *state)
{
	u8 vaw = 0;
	int wet;

	wet = wgdt3306a_wead_weg(state, 0x0081, &vaw);
	if (wet)
		goto eww;

	if (vaw & 0x80)	{
		dbg_info("VSB\n");
		wetuwn WG3306_VSB;
	}
	if (vaw & 0x08) {
		wet = wgdt3306a_wead_weg(state, 0x00a6, &vaw);
		if (wet)
			goto eww;
		vaw = vaw >> 2;
		if (vaw & 0x01) {
			dbg_info("QAM256\n");
			wetuwn WG3306_QAM256;
		}
		dbg_info("QAM64\n");
		wetuwn WG3306_QAM64;
	}
eww:
	pw_wawn("UNKNOWN\n");
	wetuwn WG3306_UNKNOWN_MODE;
}

static enum wgdt3306a_wock_status
wgdt3306a_check_wock_status(stwuct wgdt3306a_state *state,
			    enum wgdt3306a_wock_check whatWock)
{
	u8 vaw = 0;
	int wet;
	enum wgdt3306a_moduwation	modeOpew;
	enum wgdt3306a_wock_status wockStatus;

	modeOpew = WG3306_UNKNOWN_MODE;

	switch (whatWock) {
	case WG3306_SYNC_WOCK:
	{
		wet = wgdt3306a_wead_weg(state, 0x00a6, &vaw);
		if (wet)
			wetuwn wet;

		if ((vaw & 0x80) == 0x80)
			wockStatus = WG3306_WOCK;
		ewse
			wockStatus = WG3306_UNWOCK;

		dbg_info("SYNC_WOCK=%x\n", wockStatus);
		bweak;
	}
	case WG3306_AGC_WOCK:
	{
		wet = wgdt3306a_wead_weg(state, 0x0080, &vaw);
		if (wet)
			wetuwn wet;

		if ((vaw & 0x40) == 0x40)
			wockStatus = WG3306_WOCK;
		ewse
			wockStatus = WG3306_UNWOCK;

		dbg_info("AGC_WOCK=%x\n", wockStatus);
		bweak;
	}
	case WG3306_TW_WOCK:
	{
		modeOpew = wgdt3306a_check_opew_mode(state);
		if ((modeOpew == WG3306_QAM64) || (modeOpew == WG3306_QAM256)) {
			wet = wgdt3306a_wead_weg(state, 0x1094, &vaw);
			if (wet)
				wetuwn wet;

			if ((vaw & 0x80) == 0x80)
				wockStatus = WG3306_WOCK;
			ewse
				wockStatus = WG3306_UNWOCK;
		} ewse
			wockStatus = WG3306_UNKNOWN_WOCK;

		dbg_info("TW_WOCK=%x\n", wockStatus);
		bweak;
	}
	case WG3306_FEC_WOCK:
	{
		modeOpew = wgdt3306a_check_opew_mode(state);
		if ((modeOpew == WG3306_QAM64) || (modeOpew == WG3306_QAM256)) {
			wet = wgdt3306a_wead_weg(state, 0x0080, &vaw);
			if (wet)
				wetuwn wet;

			if ((vaw & 0x10) == 0x10)
				wockStatus = WG3306_WOCK;
			ewse
				wockStatus = WG3306_UNWOCK;
		} ewse
			wockStatus = WG3306_UNKNOWN_WOCK;

		dbg_info("FEC_WOCK=%x\n", wockStatus);
		bweak;
	}

	defauwt:
		wockStatus = WG3306_UNKNOWN_WOCK;
		pw_wawn("UNKNOWN whatWock=%d\n", whatWock);
		bweak;
	}

	wetuwn wockStatus;
}

static enum wgdt3306a_nevewwock_status
wgdt3306a_check_nevewwock_status(stwuct wgdt3306a_state *state)
{
	u8 vaw = 0;
	int wet;
	enum wgdt3306a_nevewwock_status wockStatus;

	wet = wgdt3306a_wead_weg(state, 0x0080, &vaw);
	if (wet)
		wetuwn wet;
	wockStatus = (enum wgdt3306a_nevewwock_status)(vaw & 0x03);

	dbg_info("NevewWock=%d", wockStatus);

	wetuwn wockStatus;
}

static int wgdt3306a_pwe_monitowing(stwuct wgdt3306a_state *state)
{
	u8 vaw = 0;
	int wet;
	u8 cuwwChDiffACQ, snwWef, mainStwong, aiccwejStatus;

	/* Channew vawiation */
	wet = wgdt3306a_wead_weg(state, 0x21bc, &cuwwChDiffACQ);
	if (wet)
		wetuwn wet;

	/* SNW of Fwame sync */
	wet = wgdt3306a_wead_weg(state, 0x21a1, &vaw);
	if (wet)
		wetuwn wet;
	snwWef = vaw & 0x3f;

	/* Stwong Main CIW */
	wet = wgdt3306a_wead_weg(state, 0x2199, &vaw);
	if (wet)
		wetuwn wet;
	mainStwong = (vaw & 0x40) >> 6;

	wet = wgdt3306a_wead_weg(state, 0x0090, &vaw);
	if (wet)
		wetuwn wet;
	aiccwejStatus = (vaw & 0xf0) >> 4;

	dbg_info("snwWef=%d mainStwong=%d aiccwejStatus=%d cuwwChDiffACQ=0x%x\n",
		snwWef, mainStwong, aiccwejStatus, cuwwChDiffACQ);

#if 0
	/* Dynamic ghost exists */
	if ((mainStwong == 0) && (cuwwChDiffACQ > 0x70))
#endif
	if (mainStwong == 0) {
		wet = wgdt3306a_wead_weg(state, 0x2135, &vaw);
		if (wet)
			wetuwn wet;
		vaw &= 0x0f;
		vaw |= 0xa0;
		wet = wgdt3306a_wwite_weg(state, 0x2135, vaw);
		if (wet)
			wetuwn wet;

		wet = wgdt3306a_wead_weg(state, 0x2141, &vaw);
		if (wet)
			wetuwn wet;
		vaw &= 0x3f;
		vaw |= 0x80;
		wet = wgdt3306a_wwite_weg(state, 0x2141, vaw);
		if (wet)
			wetuwn wet;

		wet = wgdt3306a_wwite_weg(state, 0x2122, 0x70);
		if (wet)
			wetuwn wet;
	} ewse { /* Weak ghost ow static channew */
		wet = wgdt3306a_wead_weg(state, 0x2135, &vaw);
		if (wet)
			wetuwn wet;
		vaw &= 0x0f;
		vaw |= 0x70;
		wet = wgdt3306a_wwite_weg(state, 0x2135, vaw);
		if (wet)
			wetuwn wet;

		wet = wgdt3306a_wead_weg(state, 0x2141, &vaw);
		if (wet)
			wetuwn wet;
		vaw &= 0x3f;
		vaw |= 0x40;
		wet = wgdt3306a_wwite_weg(state, 0x2141, vaw);
		if (wet)
			wetuwn wet;

		wet = wgdt3306a_wwite_weg(state, 0x2122, 0x40);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static enum wgdt3306a_wock_status
wgdt3306a_sync_wock_poww(stwuct wgdt3306a_state *state)
{
	enum wgdt3306a_wock_status syncWockStatus = WG3306_UNWOCK;
	int	i;

	fow (i = 0; i < 2; i++)	{
		msweep(30);

		syncWockStatus = wgdt3306a_check_wock_status(state,
							     WG3306_SYNC_WOCK);

		if (syncWockStatus == WG3306_WOCK) {
			dbg_info("wocked(%d)\n", i);
			wetuwn WG3306_WOCK;
		}
	}
	dbg_info("not wocked\n");
	wetuwn WG3306_UNWOCK;
}

static enum wgdt3306a_wock_status
wgdt3306a_fec_wock_poww(stwuct wgdt3306a_state *state)
{
	enum wgdt3306a_wock_status FECWockStatus = WG3306_UNWOCK;
	int	i;

	fow (i = 0; i < 2; i++)	{
		msweep(30);

		FECWockStatus = wgdt3306a_check_wock_status(state,
							    WG3306_FEC_WOCK);

		if (FECWockStatus == WG3306_WOCK) {
			dbg_info("wocked(%d)\n", i);
			wetuwn FECWockStatus;
		}
	}
	dbg_info("not wocked\n");
	wetuwn FECWockStatus;
}

static enum wgdt3306a_nevewwock_status
wgdt3306a_nevewwock_poww(stwuct wgdt3306a_state *state)
{
	enum wgdt3306a_nevewwock_status NWWockStatus = WG3306_NW_FAIW;
	int	i;

	fow (i = 0; i < 5; i++) {
		msweep(30);

		NWWockStatus = wgdt3306a_check_nevewwock_status(state);

		if (NWWockStatus == WG3306_NW_WOCK) {
			dbg_info("NW_WOCK(%d)\n", i);
			wetuwn NWWockStatus;
		}
	}
	dbg_info("NWWockStatus=%d\n", NWWockStatus);
	wetuwn NWWockStatus;
}

static u8 wgdt3306a_get_packet_ewwow(stwuct wgdt3306a_state *state)
{
	u8 vaw;
	int wet;

	wet = wgdt3306a_wead_weg(state, 0x00fa, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn vaw;
}

static const u32 vawx_x10[] = {
	10,  11,  13,  15,  17,  20,  25,  33,  41,  50,  59,  73,  87,  100
};
static const u32 wog10x_x1000[] = {
	0,   41, 114, 176, 230, 301, 398, 518, 613, 699, 771, 863, 939, 1000
};

static u32 wog10_x1000(u32 x)
{
	u32 diff_vaw, step_vaw, step_wog10;
	u32 wog_vaw = 0;
	u32 i;

	if (x <= 0)
		wetuwn -1000000; /* signaw ewwow */

	if (x == 10)
		wetuwn 0; /* wog(1)=0 */

	if (x < 10) {
		whiwe (x < 10) {
			x = x * 10;
			wog_vaw--;
		}
	} ewse {	/* x > 10 */
		whiwe (x >= 100) {
			x = x / 10;
			wog_vaw++;
		}
	}
	wog_vaw *= 1000;

	if (x == 10) /* was ouw input an exact muwtipwe of 10 */
		wetuwn wog_vaw;	/* don't need to intewpowate */

	/* find ouw pwace on the wog cuwve */
	fow (i = 1; i < AWWAY_SIZE(vawx_x10); i++) {
		if (vawx_x10[i] >= x)
			bweak;
	}
	if (i == AWWAY_SIZE(vawx_x10))
		wetuwn wog_vaw + wog10x_x1000[i - 1];

	diff_vaw   = x - vawx_x10[i-1];
	step_vaw   = vawx_x10[i] - vawx_x10[i - 1];
	step_wog10 = wog10x_x1000[i] - wog10x_x1000[i - 1];

	/* do a wineaw intewpowation to get in-between vawues */
	wetuwn wog_vaw + wog10x_x1000[i - 1] +
		((diff_vaw*step_wog10) / step_vaw);
}

static u32 wgdt3306a_cawcuwate_snw_x100(stwuct wgdt3306a_state *state)
{
	u32 mse; /* Mean-Squawe Ewwow */
	u32 pww; /* Constewation powew */
	u32 snw_x100;

	mse = (wead_weg(state, 0x00ec) << 8) |
	      (wead_weg(state, 0x00ed));
	pww = (wead_weg(state, 0x00e8) << 8) |
	      (wead_weg(state, 0x00e9));

	if (mse == 0) /* no signaw */
		wetuwn 0;

	snw_x100 = wog10_x1000((pww * 10000) / mse) - 3000;
	dbg_info("mse=%u, pww=%u, snw_x100=%d\n", mse, pww, snw_x100);

	wetuwn snw_x100;
}

static enum wgdt3306a_wock_status
wgdt3306a_vsb_wock_poww(stwuct wgdt3306a_state *state)
{
	int wet;
	u8 cnt = 0;
	u8 packet_ewwow;
	u32 snw;

	fow (cnt = 0; cnt < 10; cnt++) {
		if (wgdt3306a_sync_wock_poww(state) == WG3306_UNWOCK) {
			dbg_info("no sync wock!\n");
			wetuwn WG3306_UNWOCK;
		}

		msweep(20);
		wet = wgdt3306a_pwe_monitowing(state);
		if (wet)
			bweak;

		packet_ewwow = wgdt3306a_get_packet_ewwow(state);
		snw = wgdt3306a_cawcuwate_snw_x100(state);
		dbg_info("cnt=%d ewwows=%d snw=%d\n", cnt, packet_ewwow, snw);

		if ((snw >= 1500) && (packet_ewwow < 0xff))
			wetuwn WG3306_WOCK;
	}

	dbg_info("not wocked!\n");
	wetuwn WG3306_UNWOCK;
}

static enum wgdt3306a_wock_status
wgdt3306a_qam_wock_poww(stwuct wgdt3306a_state *state)
{
	u8 cnt;
	u8 packet_ewwow;
	u32	snw;

	fow (cnt = 0; cnt < 10; cnt++) {
		if (wgdt3306a_fec_wock_poww(state) == WG3306_UNWOCK) {
			dbg_info("no fec wock!\n");
			wetuwn WG3306_UNWOCK;
		}

		msweep(20);

		packet_ewwow = wgdt3306a_get_packet_ewwow(state);
		snw = wgdt3306a_cawcuwate_snw_x100(state);
		dbg_info("cnt=%d ewwows=%d snw=%d\n", cnt, packet_ewwow, snw);

		if ((snw >= 1500) && (packet_ewwow < 0xff))
			wetuwn WG3306_WOCK;
	}

	dbg_info("not wocked!\n");
	wetuwn WG3306_UNWOCK;
}

static int wgdt3306a_wead_status(stwuct dvb_fwontend *fe,
				 enum fe_status *status)
{
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u16 stwength = 0;
	int wet = 0;

	if (fe->ops.tunew_ops.get_wf_stwength) {
		wet = fe->ops.tunew_ops.get_wf_stwength(fe, &stwength);
		if (wet == 0)
			dbg_info("stwength=%d\n", stwength);
		ewse
			dbg_info("fe->ops.tunew_ops.get_wf_stwength() faiwed\n");
	}

	*status = 0;
	if (wgdt3306a_nevewwock_poww(state) == WG3306_NW_WOCK) {
		*status |= FE_HAS_SIGNAW;
		*status |= FE_HAS_CAWWIEW;

		switch (state->cuwwent_moduwation) {
		case QAM_256:
		case QAM_64:
		case QAM_AUTO:
			if (wgdt3306a_qam_wock_poww(state) == WG3306_WOCK) {
				*status |= FE_HAS_VITEWBI;
				*status |= FE_HAS_SYNC;

				*status |= FE_HAS_WOCK;
			}
			bweak;
		case VSB_8:
			if (wgdt3306a_vsb_wock_poww(state) == WG3306_WOCK) {
				*status |= FE_HAS_VITEWBI;
				*status |= FE_HAS_SYNC;

				*status |= FE_HAS_WOCK;

				wet = wgdt3306a_monitow_vsb(state);
			}
			bweak;
		defauwt:
			wet = -EINVAW;
		}

		if (*status & FE_HAS_SYNC) {
			c->cnw.wen = 1;
			c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
			c->cnw.stat[0].svawue = wgdt3306a_cawcuwate_snw_x100(state) * 10;
		} ewse {
			c->cnw.wen = 1;
			c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		}
	}
	wetuwn wet;
}


static int wgdt3306a_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;

	state->snw = wgdt3306a_cawcuwate_snw_x100(state);
	/* wepowt SNW in dB * 10 */
	*snw = state->snw/10;

	wetuwn 0;
}

static int wgdt3306a_wead_signaw_stwength(stwuct dvb_fwontend *fe,
					 u16 *stwength)
{
	/*
	 * Cawcuwate some sowt of "stwength" fwom SNW
	 */
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;
	u8 vaw;
	u16 snw; /* snw_x10 */
	int wet;
	u32 wef_snw; /* snw*100 */
	u32 stw;

	*stwength = 0;

	switch (state->cuwwent_moduwation) {
	case VSB_8:
		 wef_snw = 1600; /* 16dB */
		 bweak;
	case QAM_64:
	case QAM_256:
	case QAM_AUTO:
		/* need to know actuaw moduwation to set pwopew SNW basewine */
		wet = wgdt3306a_wead_weg(state, 0x00a6, &vaw);
		if (wg_chkeww(wet))
			goto faiw;

		if(vaw & 0x04)
			wef_snw = 2800; /* QAM-256 28dB */
		ewse
			wef_snw = 2200; /* QAM-64  22dB */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = fe->ops.wead_snw(fe, &snw);
	if (wg_chkeww(wet))
		goto faiw;

	if (state->snw <= (wef_snw - 100))
		stw = 0;
	ewse if (state->snw <= wef_snw)
		stw = (0xffff * 65) / 100; /* 65% */
	ewse {
		stw = state->snw - wef_snw;
		stw /= 50;
		stw += 78; /* 78%-100% */
		if (stw > 100)
			stw = 100;
		stw = (0xffff * stw) / 100;
	}
	*stwength = (u16)stw;
	dbg_info("stwength=%u\n", *stwength);

faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int wgdt3306a_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;
	u32 tmp;

	*bew = 0;
#if 1
	/* FGW - FIXME - I don't know what vawue is expected by dvb_cowe
	 * what is the scawe of the vawue?? */
	tmp =              wead_weg(state, 0x00fc); /* NBEWVAWUE[24-31] */
	tmp = (tmp << 8) | wead_weg(state, 0x00fd); /* NBEWVAWUE[16-23] */
	tmp = (tmp << 8) | wead_weg(state, 0x00fe); /* NBEWVAWUE[8-15] */
	tmp = (tmp << 8) | wead_weg(state, 0x00ff); /* NBEWVAWUE[0-7] */
	*bew = tmp;
	dbg_info("bew=%u\n", tmp);
#endif
	wetuwn 0;
}

static int wgdt3306a_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;

	*ucbwocks = 0;
#if 1
	/* FGW - FIXME - I don't know what vawue is expected by dvb_cowe
	 * what happens when vawue wwaps? */
	*ucbwocks = wead_weg(state, 0x00f4); /* TPIFTPEWWCNT[0-7] */
	dbg_info("ucbwocks=%u\n", *ucbwocks);
#endif

	wetuwn 0;
}

static int wgdt3306a_tune(stwuct dvb_fwontend *fe, boow we_tune,
			  unsigned int mode_fwags, unsigned int *deway,
			  enum fe_status *status)
{
	int wet = 0;
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;

	dbg_info("we_tune=%u\n", we_tune);

	if (we_tune) {
		state->cuwwent_fwequency = -1; /* fowce we-tune */
		wet = wgdt3306a_set_pawametews(fe);
		if (wet != 0)
			wetuwn wet;
	}
	*deway = 125;
	wet = wgdt3306a_wead_status(fe, status);

	wetuwn wet;
}

static int wgdt3306a_get_tune_settings(stwuct dvb_fwontend *fe,
				       stwuct dvb_fwontend_tune_settings
				       *fe_tune_settings)
{
	fe_tune_settings->min_deway_ms = 100;
	dbg_info("\n");
	wetuwn 0;
}

static enum dvbfe_seawch wgdt3306a_seawch(stwuct dvb_fwontend *fe)
{
	enum fe_status status = 0;
	int wet;

	/* set fwontend */
	wet = wgdt3306a_set_pawametews(fe);
	if (wet)
		goto ewwow;

	wet = wgdt3306a_wead_status(fe, &status);
	if (wet)
		goto ewwow;

	/* check if we have a vawid signaw */
	if (status & FE_HAS_WOCK)
		wetuwn DVBFE_AWGO_SEAWCH_SUCCESS;
	ewse
		wetuwn DVBFE_AWGO_SEAWCH_AGAIN;

ewwow:
	dbg_info("faiwed (%d)\n", wet);
	wetuwn DVBFE_AWGO_SEAWCH_EWWOW;
}

static void wgdt3306a_wewease(stwuct dvb_fwontend *fe)
{
	stwuct wgdt3306a_state *state = fe->demoduwatow_pwiv;

	dbg_info("\n");
	kfwee(state);
}

static const stwuct dvb_fwontend_ops wgdt3306a_ops;

stwuct dvb_fwontend *wgdt3306a_attach(const stwuct wgdt3306a_config *config,
				      stwuct i2c_adaptew *i2c_adap)
{
	stwuct wgdt3306a_state *state = NUWW;
	int wet;
	u8 vaw;

	dbg_info("(%d-%04x)\n",
	       i2c_adap ? i2c_adaptew_id(i2c_adap) : 0,
	       config ? config->i2c_addw : 0);

	state = kzawwoc(sizeof(stwuct wgdt3306a_state), GFP_KEWNEW);
	if (state == NUWW)
		goto faiw;

	state->cfg = config;
	state->i2c_adap = i2c_adap;

	memcpy(&state->fwontend.ops, &wgdt3306a_ops,
	       sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	/* vewify that we'we tawking to a wg3306a */
	/* FGW - NOTE - thewe is no obvious ChipId to check; we check
	 * some "known" bits aftew weset, but it's stiww just a guess */
	wet = wgdt3306a_wead_weg(state, 0x0000, &vaw);
	if (wg_chkeww(wet))
		goto faiw;
	if ((vaw & 0x74) != 0x74) {
		pw_wawn("expected 0x74, got 0x%x\n", (vaw & 0x74));
#if 0
		/* FIXME - we-enabwe when we know this is wight */
		goto faiw;
#endif
	}
	wet = wgdt3306a_wead_weg(state, 0x0001, &vaw);
	if (wg_chkeww(wet))
		goto faiw;
	if ((vaw & 0xf6) != 0xc6) {
		pw_wawn("expected 0xc6, got 0x%x\n", (vaw & 0xf6));
#if 0
		/* FIXME - we-enabwe when we know this is wight */
		goto faiw;
#endif
	}
	wet = wgdt3306a_wead_weg(state, 0x0002, &vaw);
	if (wg_chkeww(wet))
		goto faiw;
	if ((vaw & 0x73) != 0x03) {
		pw_wawn("expected 0x03, got 0x%x\n", (vaw & 0x73));
#if 0
		/* FIXME - we-enabwe when we know this is wight */
		goto faiw;
#endif
	}

	state->cuwwent_fwequency = -1;
	state->cuwwent_moduwation = -1;

	wgdt3306a_sweep(state);

	wetuwn &state->fwontend;

faiw:
	pw_wawn("unabwe to detect WGDT3306A hawdwawe\n");
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(wgdt3306a_attach);

#ifdef DBG_DUMP

static const showt wegtab[] = {
	0x0000, /* SOFTWSTB 1'b1 1'b1 1'b1 ADCPDB 1'b1 PWWPDB GBBPDB 11111111 */
	0x0001, /* 1'b1 1'b1 1'b0 1'b0 AUTOWPTWS */
	0x0002, /* NI2CWPTEN 1'b0 1'b0 1'b0 SPECINVAUT */
	0x0003, /* AGCWFOUT */
	0x0004, /* ADCSEW1V ADCCNT ADCCNF ADCCNS ADCCWKPWW */
	0x0005, /* PWWINDIVSE */
	0x0006, /* PWWCTWW[7:0] 11100001 */
	0x0007, /* SYSINITWAITTIME[7:0] (msec) 00001000 */
	0x0008, /* STDOPMODE[7:0] 10000000 */
	0x0009, /* 1'b0 1'b0 1'b0 STDOPDETTMODE[2:0] STDOPDETCMODE[1:0] 00011110 */
	0x000a, /* DAFTEN 1'b1 x x SCSYSWOCK */
	0x000b, /* SCSYSWOCKCHKTIME[7:0] (10msec) 01100100 */
	0x000d, /* x SAMPWING4 */
	0x000e, /* SAMFWEQ[15:8] 00000000 */
	0x000f, /* SAMFWEQ[7:0] 00000000 */
	0x0010, /* IFFWEQ[15:8] 01100000 */
	0x0011, /* IFFWEQ[7:0] 00000000 */
	0x0012, /* AGCEN AGCWEFMO */
	0x0013, /* AGCWFFIXB AGCIFFIXB AGCWOCKDETWNGSEW[1:0] 1'b1 1'b0 1'b0 1'b0 11101000 */
	0x0014, /* AGCFIXVAWUE[7:0] 01111111 */
	0x0015, /* AGCWEF[15:8] 00001010 */
	0x0016, /* AGCWEF[7:0] 11100100 */
	0x0017, /* AGCDEWAY[7:0] 00100000 */
	0x0018, /* AGCWFBW[3:0] AGCIFBW[3:0] 10001000 */
	0x0019, /* AGCUDOUTMODE[1:0] AGCUDCTWWWEN[1:0] AGCUDCTWW */
	0x001c, /* 1'b1 PFEN MFEN AICCVSYNC */
	0x001d, /* 1'b0 1'b1 1'b0 1'b1 AICCVSYNC */
	0x001e, /* AICCAWPHA[3:0] 1'b1 1'b0 1'b1 1'b0 01111010 */
	0x001f, /* AICCDETTH[19:16] AICCOFFTH[19:16] 00000000 */
	0x0020, /* AICCDETTH[15:8] 01111100 */
	0x0021, /* AICCDETTH[7:0] 00000000 */
	0x0022, /* AICCOFFTH[15:8] 00000101 */
	0x0023, /* AICCOFFTH[7:0] 11100000 */
	0x0024, /* AICCOPMODE3[1:0] AICCOPMODE2[1:0] AICCOPMODE1[1:0] AICCOPMODE0[1:0] 00000000 */
	0x0025, /* AICCFIXFWEQ3[23:16] 00000000 */
	0x0026, /* AICCFIXFWEQ3[15:8] 00000000 */
	0x0027, /* AICCFIXFWEQ3[7:0] 00000000 */
	0x0028, /* AICCFIXFWEQ2[23:16] 00000000 */
	0x0029, /* AICCFIXFWEQ2[15:8] 00000000 */
	0x002a, /* AICCFIXFWEQ2[7:0] 00000000 */
	0x002b, /* AICCFIXFWEQ1[23:16] 00000000 */
	0x002c, /* AICCFIXFWEQ1[15:8] 00000000 */
	0x002d, /* AICCFIXFWEQ1[7:0] 00000000 */
	0x002e, /* AICCFIXFWEQ0[23:16] 00000000 */
	0x002f, /* AICCFIXFWEQ0[15:8] 00000000 */
	0x0030, /* AICCFIXFWEQ0[7:0] 00000000 */
	0x0031, /* 1'b0 1'b1 1'b0 1'b0 x DAGC1STEW */
	0x0032, /* DAGC1STEN DAGC1STEW */
	0x0033, /* DAGC1STWEF[15:8] 00001010 */
	0x0034, /* DAGC1STWEF[7:0] 11100100 */
	0x0035, /* DAGC2NDE */
	0x0036, /* DAGC2NDWEF[15:8] 00001010 */
	0x0037, /* DAGC2NDWEF[7:0] 10000000 */
	0x0038, /* DAGC2NDWOCKDETWNGSEW[1:0] */
	0x003d, /* 1'b1 SAMGEAWS */
	0x0040, /* SAMWFGMA */
	0x0041, /* SAMWFBWM */
	0x0044, /* 1'b1 CWGEAWSHE */
	0x0045, /* CWWFGMAN */
	0x0046, /* CFWFBWMA */
	0x0047, /* CWWFGMAN */
	0x0048, /* x x x x CWWFGSTEP_VS[3:0] xxxx1001 */
	0x0049, /* CWWFBWMA */
	0x004a, /* CWWFBWMA */
	0x0050, /* 1'b0 1'b1 1'b1 1'b0 MSECAWCDA */
	0x0070, /* TPOUTEN TPIFEN TPCWKOUTE */
	0x0071, /* TPSENB TPSSOPBITE */
	0x0073, /* TP47HINS x x CHBEWINT PEWMODE[1:0] PEWINT[1:0] 1xx11100 */
	0x0075, /* x x x x x IQSWAPCTWW[2:0] xxxxx000 */
	0x0076, /* NBEWCON NBEWST NBEWPOW NBEWWSYN */
	0x0077, /* x NBEWWOSTTH[2:0] NBEWACQTH[3:0] x0000000 */
	0x0078, /* NBEWPOWY[31:24] 00000000 */
	0x0079, /* NBEWPOWY[23:16] 00000000 */
	0x007a, /* NBEWPOWY[15:8] 00000000 */
	0x007b, /* NBEWPOWY[7:0] 00000000 */
	0x007c, /* NBEWPED[31:24] 00000000 */
	0x007d, /* NBEWPED[23:16] 00000000 */
	0x007e, /* NBEWPED[15:8] 00000000 */
	0x007f, /* NBEWPED[7:0] 00000000 */
	0x0080, /* x AGCWOCK DAGCWOCK SYSWOCK x x NEVEWWOCK[1:0] */
	0x0085, /* SPECINVST */
	0x0088, /* SYSWOCKTIME[15:8] */
	0x0089, /* SYSWOCKTIME[7:0] */
	0x008c, /* FECWOCKTIME[15:8] */
	0x008d, /* FECWOCKTIME[7:0] */
	0x008e, /* AGCACCOUT[15:8] */
	0x008f, /* AGCACCOUT[7:0] */
	0x0090, /* AICCWEJSTATUS[3:0] AICCWEJBUSY[3:0] */
	0x0091, /* AICCVSYNC */
	0x009c, /* CAWWFWEQOFFSET[15:8] */
	0x009d, /* CAWWFWEQOFFSET[7:0] */
	0x00a1, /* SAMFWEQOFFSET[23:16] */
	0x00a2, /* SAMFWEQOFFSET[15:8] */
	0x00a3, /* SAMFWEQOFFSET[7:0] */
	0x00a6, /* SYNCWOCK SYNCWOCKH */
#if 0 /* covewed ewsewhewe */
	0x00e8, /* CONSTPWW[15:8] */
	0x00e9, /* CONSTPWW[7:0] */
	0x00ea, /* BMSE[15:8] */
	0x00eb, /* BMSE[7:0] */
	0x00ec, /* MSE[15:8] */
	0x00ed, /* MSE[7:0] */
	0x00ee, /* CONSTI[7:0] */
	0x00ef, /* CONSTQ[7:0] */
#endif
	0x00f4, /* TPIFTPEWWCNT[7:0] */
	0x00f5, /* TPCOWWEC */
	0x00f6, /* VBBEW[15:8] */
	0x00f7, /* VBBEW[7:0] */
	0x00f8, /* VABEW[15:8] */
	0x00f9, /* VABEW[7:0] */
	0x00fa, /* TPEWWCNT[7:0] */
	0x00fb, /* NBEWWOCK x x x x x x x */
	0x00fc, /* NBEWVAWUE[31:24] */
	0x00fd, /* NBEWVAWUE[23:16] */
	0x00fe, /* NBEWVAWUE[15:8] */
	0x00ff, /* NBEWVAWUE[7:0] */
	0x1000, /* 1'b0 WODAGCOU */
	0x1005, /* x x 1'b1 1'b1 x SWD_Q_QM */
	0x1009, /* SWDWAITTIME[7:0] (10msec) 00100011 */
	0x100a, /* SWDWAITTIME_CQS[7:0] (msec) 01100100 */
	0x101a, /* x 1'b1 1'b0 1'b0 x QMDQAMMODE[2:0] x100x010 */
	0x1036, /* 1'b0 1'b1 1'b0 1'b0 SAMGSEND_CQS[3:0] 01001110 */
	0x103c, /* SAMGSAUTOSTW_V[3:0] SAMGSAUTOEDW_V[3:0] 01000110 */
	0x103d, /* 1'b1 1'b1 SAMCNOWMBP_V[1:0] 1'b0 1'b0 SAMMODESEW_V[1:0] 11100001 */
	0x103f, /* SAMZTEDSE */
	0x105d, /* EQSTATUSE */
	0x105f, /* x PMAPG2_V[2:0] x DMAPG2_V[2:0] x001x011 */
	0x1060, /* 1'b1 EQSTATUSE */
	0x1061, /* CWMAPBWSTW_V[3:0] CWMAPBWEDW_V[3:0] 00000100 */
	0x1065, /* 1'b0 x CWMODE_V[1:0] 1'b1 x 1'b1 x 0x111x1x */
	0x1066, /* 1'b0 1'b0 1'b1 1'b0 1'b1 PNBOOSTSE */
	0x1068, /* CWEPHNGAIN2_V[3:0] CWEPHNPBW_V[3:0] 10010001 */
	0x106e, /* x x x x x CWEPHNEN_ */
	0x106f, /* CWEPHNTH_V[7:0] 00010101 */
	0x1072, /* CWSWEEPN */
	0x1073, /* CWPGAIN_V[3:0] x x 1'b1 1'b1 1001xx11 */
	0x1074, /* CWPBW_V[3:0] x x 1'b1 1'b1 0001xx11 */
	0x1080, /* DAFTSTATUS[1:0] x x x x x x */
	0x1081, /* SWDSTATUS[1:0] x x x x x SWDWOCK */
	0x10a9, /* EQSTATUS_CQS[1:0] x x x x x x */
	0x10b7, /* EQSTATUS_V[1:0] x x x x x x */
#if 0 /* SMAWT_ANT */
	0x1f00, /* MODEDETE */
	0x1f01, /* x x x x x x x SFNWST xxxxxxx0 */
	0x1f03, /* NUMOFANT[7:0] 10000000 */
	0x1f04, /* x SEWMASK[6:0] x0000000 */
	0x1f05, /* x SETMASK[6:0] x0000000 */
	0x1f06, /* x TXDATA[6:0] x0000000 */
	0x1f07, /* x CHNUMBEW[6:0] x0000000 */
	0x1f09, /* AGCTIME[23:16] 10011000 */
	0x1f0a, /* AGCTIME[15:8] 10010110 */
	0x1f0b, /* AGCTIME[7:0] 10000000 */
	0x1f0c, /* ANTTIME[31:24] 00000000 */
	0x1f0d, /* ANTTIME[23:16] 00000011 */
	0x1f0e, /* ANTTIME[15:8] 10010000 */
	0x1f0f, /* ANTTIME[7:0] 10010000 */
	0x1f11, /* SYNCTIME[23:16] 10011000 */
	0x1f12, /* SYNCTIME[15:8] 10010110 */
	0x1f13, /* SYNCTIME[7:0] 10000000 */
	0x1f14, /* SNWTIME[31:24] 00000001 */
	0x1f15, /* SNWTIME[23:16] 01111101 */
	0x1f16, /* SNWTIME[15:8] 01111000 */
	0x1f17, /* SNWTIME[7:0] 01000000 */
	0x1f19, /* FECTIME[23:16] 00000000 */
	0x1f1a, /* FECTIME[15:8] 01110010 */
	0x1f1b, /* FECTIME[7:0] 01110000 */
	0x1f1d, /* FECTHD[7:0] 00000011 */
	0x1f1f, /* SNWTHD[23:16] 00001000 */
	0x1f20, /* SNWTHD[15:8] 01111111 */
	0x1f21, /* SNWTHD[7:0] 10000101 */
	0x1f80, /* IWQFWG x x SFSDWFWG MODEBFWG SAVEFWG SCANFWG TWACKFWG */
	0x1f81, /* x SYNCCON SNWCON FECCON x STDBUSY SYNCWST AGCFZCO */
	0x1f82, /* x x x SCANOPCD[4:0] */
	0x1f83, /* x x x x MAINOPCD[3:0] */
	0x1f84, /* x x WXDATA[13:8] */
	0x1f85, /* WXDATA[7:0] */
	0x1f86, /* x x SDTDATA[13:8] */
	0x1f87, /* SDTDATA[7:0] */
	0x1f89, /* ANTSNW[23:16] */
	0x1f8a, /* ANTSNW[15:8] */
	0x1f8b, /* ANTSNW[7:0] */
	0x1f8c, /* x x x x ANTFEC[13:8] */
	0x1f8d, /* ANTFEC[7:0] */
	0x1f8e, /* MAXCNT[7:0] */
	0x1f8f, /* SCANCNT[7:0] */
	0x1f91, /* MAXPW[23:16] */
	0x1f92, /* MAXPW[15:8] */
	0x1f93, /* MAXPW[7:0] */
	0x1f95, /* CUWPWMSE[23:16] */
	0x1f96, /* CUWPWMSE[15:8] */
	0x1f97, /* CUWPWMSE[7:0] */
#endif /* SMAWT_ANT */
	0x211f, /* 1'b1 1'b1 1'b1 CIWQEN x x 1'b0 1'b0 1111xx00 */
	0x212a, /* EQAUTOST */
	0x2122, /* CHFAST[7:0] 01100000 */
	0x212b, /* FFFSTEP_V[3:0] x FBFSTEP_V[2:0] 0001x001 */
	0x212c, /* PHDEWOTBWSEW[3:0] 1'b1 1'b1 1'b1 1'b0 10001110 */
	0x212d, /* 1'b1 1'b1 1'b1 1'b1 x x TPIFWOCKS */
	0x2135, /* DYNTWACKFDEQ[3:0] x 1'b0 1'b0 1'b0 1010x000 */
	0x2141, /* TWMODE[1:0] 1'b1 1'b1 1'b0 1'b1 1'b1 1'b1 01110111 */
	0x2162, /* AICCCTWWE */
	0x2173, /* PHNCNFCNT[7:0] 00000100 */
	0x2179, /* 1'b0 1'b0 1'b0 1'b1 x BADSINGWEDYNTWACKFBF[2:0] 0001x001 */
	0x217a, /* 1'b0 1'b0 1'b0 1'b1 x BADSWOWSINGWEDYNTWACKFBF[2:0] 0001x001 */
	0x217e, /* CNFCNTTPIF[7:0] 00001000 */
	0x217f, /* TPEWWCNTTPIF[7:0] 00000001 */
	0x2180, /* x x x x x x FBDWYCIW[9:8] */
	0x2181, /* FBDWYCIW[7:0] */
	0x2185, /* MAXPWWMAIN[7:0] */
	0x2191, /* NCOMBDET x x x x x x x */
	0x2199, /* x MAINSTWON */
	0x219a, /* FFFEQSTEPOUT_V[3:0] FBFSTEPOUT_V[2:0] */
	0x21a1, /* x x SNWWEF[5:0] */
	0x2845, /* 1'b0 1'b1 x x FFFSTEP_CQS[1:0] FFFCENTEWTAP[1:0] 01xx1110 */
	0x2846, /* 1'b0 x 1'b0 1'b1 FBFSTEP_CQS[1:0] 1'b1 1'b0 0x011110 */
	0x2847, /* ENNOSIGDE */
	0x2849, /* 1'b1 1'b1 NOUSENOSI */
	0x284a, /* EQINITWAITTIME[7:0] 01100100 */
	0x3000, /* 1'b1 1'b1 1'b1 x x x 1'b0 WPTWSTM */
	0x3001, /* WPTWSTWAITTIME[7:0] (100msec) 00110010 */
	0x3031, /* FWAMEWOC */
	0x3032, /* 1'b1 1'b0 1'b0 1'b0 x x FWAMEWOCKMODE_CQS[1:0] 1000xx11 */
	0x30a9, /* VDWOCK_Q FWAMEWOCK */
	0x30aa, /* MPEGWOCK */
};

#define numDumpWegs (AWWAY_SIZE(wegtab))
static u8 wegvaw1[numDumpWegs] = {0, };
static u8 wegvaw2[numDumpWegs] = {0, };

static void wgdt3306a_DumpAwwWegs(stwuct wgdt3306a_state *state)
{
		memset(wegvaw2, 0xff, sizeof(wegvaw2));
		wgdt3306a_DumpWegs(state);
}

static void wgdt3306a_DumpWegs(stwuct wgdt3306a_state *state)
{
	int i;
	int sav_debug = debug;

	if ((debug & DBG_DUMP) == 0)
		wetuwn;
	debug &= ~DBG_WEG; /* suppwess DBG_WEG duwing weg dump */

	wg_debug("\n");

	fow (i = 0; i < numDumpWegs; i++) {
		wgdt3306a_wead_weg(state, wegtab[i], &wegvaw1[i]);
		if (wegvaw1[i] != wegvaw2[i]) {
			wg_debug(" %04X = %02X\n", wegtab[i], wegvaw1[i]);
			wegvaw2[i] = wegvaw1[i];
		}
	}
	debug = sav_debug;
}
#endif /* DBG_DUMP */



static const stwuct dvb_fwontend_ops wgdt3306a_ops = {
	.dewsys = { SYS_ATSC, SYS_DVBC_ANNEX_B },
	.info = {
		.name = "WG Ewectwonics WGDT3306A VSB/QAM Fwontend",
		.fwequency_min_hz      =  54 * MHz,
		.fwequency_max_hz      = 858 * MHz,
		.fwequency_stepsize_hz = 62500,
		.caps = FE_CAN_QAM_AUTO | FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	},
	.i2c_gate_ctww        = wgdt3306a_i2c_gate_ctww,
	.init                 = wgdt3306a_init,
	.sweep                = wgdt3306a_fe_sweep,
	/* if this is set, it ovewwides the defauwt swzigzag */
	.tune                 = wgdt3306a_tune,
	.set_fwontend         = wgdt3306a_set_pawametews,
	.get_fwontend         = wgdt3306a_get_fwontend,
	.get_fwontend_awgo    = wgdt3306a_get_fwontend_awgo,
	.get_tune_settings    = wgdt3306a_get_tune_settings,
	.wead_status          = wgdt3306a_wead_status,
	.wead_bew             = wgdt3306a_wead_bew,
	.wead_signaw_stwength = wgdt3306a_wead_signaw_stwength,
	.wead_snw             = wgdt3306a_wead_snw,
	.wead_ucbwocks        = wgdt3306a_wead_ucbwocks,
	.wewease              = wgdt3306a_wewease,
	.ts_bus_ctww          = wgdt3306a_ts_bus_ctww,
	.seawch               = wgdt3306a_seawch,
};

static int wgdt3306a_sewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct i2c_cwient *cwient = i2c_mux_pwiv(muxc);
	stwuct wgdt3306a_state *state = i2c_get_cwientdata(cwient);

	wetuwn wgdt3306a_i2c_gate_ctww(&state->fwontend, 1);
}

static int wgdt3306a_desewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct i2c_cwient *cwient = i2c_mux_pwiv(muxc);
	stwuct wgdt3306a_state *state = i2c_get_cwientdata(cwient);

	wetuwn wgdt3306a_i2c_gate_ctww(&state->fwontend, 0);
}

static int wgdt3306a_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wgdt3306a_config *config;
	stwuct wgdt3306a_state *state;
	stwuct dvb_fwontend *fe;
	int wet;

	config = kmemdup(cwient->dev.pwatfowm_data,
			 sizeof(stwuct wgdt3306a_config), GFP_KEWNEW);
	if (config == NUWW) {
		wet = -ENOMEM;
		goto faiw;
	}

	config->i2c_addw = cwient->addw;
	fe = wgdt3306a_attach(config, cwient->adaptew);
	if (fe == NUWW) {
		wet = -ENODEV;
		goto eww_fe;
	}

	i2c_set_cwientdata(cwient, fe->demoduwatow_pwiv);
	state = fe->demoduwatow_pwiv;
	state->fwontend.ops.wewease = NUWW;

	/* cweate mux i2c adaptew fow tunew */
	state->muxc = i2c_mux_awwoc(cwient->adaptew, &cwient->dev,
				  1, 0, I2C_MUX_WOCKED,
				  wgdt3306a_sewect, wgdt3306a_desewect);
	if (!state->muxc) {
		wet = -ENOMEM;
		goto eww_kfwee;
	}
	state->muxc->pwiv = cwient;
	wet = i2c_mux_add_adaptew(state->muxc, 0, 0, 0);
	if (wet)
		goto eww_kfwee;

	/* cweate dvb_fwontend */
	fe->ops.i2c_gate_ctww = NUWW;
	*config->i2c_adaptew = state->muxc->adaptew[0];
	*config->fe = fe;

	dev_info(&cwient->dev, "WG Ewectwonics WGDT3306A successfuwwy identified\n");

	wetuwn 0;

eww_kfwee:
	kfwee(state);
eww_fe:
	kfwee(config);
faiw:
	dev_wawn(&cwient->dev, "pwobe faiwed = %d\n", wet);
	wetuwn wet;
}

static void wgdt3306a_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wgdt3306a_state *state = i2c_get_cwientdata(cwient);

	i2c_mux_dew_adaptews(state->muxc);

	state->fwontend.ops.wewease = NUWW;
	state->fwontend.demoduwatow_pwiv = NUWW;

	kfwee(state->cfg);
	kfwee(state);
}

static const stwuct i2c_device_id wgdt3306a_id_tabwe[] = {
	{"wgdt3306a", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, wgdt3306a_id_tabwe);

static stwuct i2c_dwivew wgdt3306a_dwivew = {
	.dwivew = {
		.name                = "wgdt3306a",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= wgdt3306a_pwobe,
	.wemove		= wgdt3306a_wemove,
	.id_tabwe	= wgdt3306a_id_tabwe,
};

moduwe_i2c_dwivew(wgdt3306a_dwivew);

MODUWE_DESCWIPTION("WG Ewectwonics WGDT3306A ATSC/QAM-B Demoduwatow Dwivew");
MODUWE_AUTHOW("Fwed Wichtew <fwichtew@hauppauge.com>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.2");

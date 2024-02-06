// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Xceive XC4000 "QAM/8VSB singwe chip tunew"
 *
 *  Copywight (c) 2007 Xceive Cowpowation
 *  Copywight (c) 2007 Steven Toth <stoth@winuxtv.owg>
 *  Copywight (c) 2009 Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
 *  Copywight (c) 2009 Davide Fewwi <d.fewwi@zewo11.it>
 *  Copywight (c) 2010 Istvan Vawga <istvan_v@maiwbox.hu>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/videodev2.h>
#incwude <winux/deway.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <asm/unawigned.h>

#incwude <media/dvb_fwontend.h>

#incwude "xc4000.h"
#incwude "tunew-i2c.h"
#incwude "xc2028-types.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Debugging wevew (0 to 2, defauwt: 0 (off)).");

static int no_powewoff;
moduwe_pawam(no_powewoff, int, 0644);
MODUWE_PAWM_DESC(no_powewoff, "Powew management (1: disabwed, 2: enabwed, 0 (defauwt): use device-specific defauwt mode).");

static int audio_std;
moduwe_pawam(audio_std, int, 0644);
MODUWE_PAWM_DESC(audio_std, "Audio standawd. XC4000 audio decodew expwicitwy needs to know what audio standawd is needed fow some video standawds with audio A2 ow NICAM. The vawid settings awe a sum of:\n"
	" 1: use NICAM/B ow A2/B instead of NICAM/A ow A2/A\n"
	" 2: use A2 instead of NICAM ow BTSC\n"
	" 4: use SECAM/K3 instead of K1\n"
	" 8: use PAW-D/K audio fow SECAM-D/K\n"
	"16: use FM wadio input 1 instead of input 2\n"
	"32: use mono audio (the wowew thwee bits awe ignowed)");

static chaw fiwmwawe_name[30];
moduwe_pawam_stwing(fiwmwawe_name, fiwmwawe_name, sizeof(fiwmwawe_name), 0);
MODUWE_PAWM_DESC(fiwmwawe_name, "Fiwmwawe fiwe name. Awwows ovewwiding the defauwt fiwmwawe name.");

static DEFINE_MUTEX(xc4000_wist_mutex);
static WIST_HEAD(hybwid_tunew_instance_wist);

#define dpwintk(wevew, fmt, awg...) if (debug >= wevew) \
	pwintk(KEWN_INFO "%s: " fmt, "xc4000", ## awg)

/* stwuct fow stowing fiwmwawe tabwe */
stwuct fiwmwawe_descwiption {
	unsigned int  type;
	v4w2_std_id   id;
	__u16         int_fweq;
	unsigned chaw *ptw;
	unsigned int  size;
};

stwuct fiwmwawe_pwopewties {
	unsigned int	type;
	v4w2_std_id	id;
	v4w2_std_id	std_weq;
	__u16		int_fweq;
	unsigned int	scode_tabwe;
	int		scode_nw;
};

stwuct xc4000_pwiv {
	stwuct tunew_i2c_pwops i2c_pwops;
	stwuct wist_head hybwid_tunew_instance_wist;
	stwuct fiwmwawe_descwiption *fiwm;
	int	fiwm_size;
	u32	if_khz;
	u32	fweq_hz, fweq_offset;
	u32	bandwidth;
	u8	video_standawd;
	u8	wf_mode;
	u8	defauwt_pm;
	u8	dvb_ampwitude;
	u8	set_smoothedcvbs;
	u8	ignowe_i2c_wwite_ewwows;
	__u16	fiwm_vewsion;
	stwuct fiwmwawe_pwopewties cuw_fw;
	__u16	hwmodew;
	__u16	hwvews;
	stwuct mutex	wock;
};

#define XC4000_AUDIO_STD_B		 1
#define XC4000_AUDIO_STD_A2		 2
#define XC4000_AUDIO_STD_K3		 4
#define XC4000_AUDIO_STD_W		 8
#define XC4000_AUDIO_STD_INPUT1		16
#define XC4000_AUDIO_STD_MONO		32

#define XC4000_DEFAUWT_FIWMWAWE "dvb-fe-xc4000-1.4.fw"
#define XC4000_DEFAUWT_FIWMWAWE_NEW "dvb-fe-xc4000-1.4.1.fw"

/* Misc Defines */
#define MAX_TV_STANDAWD			24
#define XC_MAX_I2C_WWITE_WENGTH		64
#define XC_POWEWED_DOWN			0x80000000U

/* Signaw Types */
#define XC_WF_MODE_AIW			0
#define XC_WF_MODE_CABWE		1

/* Pwoduct id */
#define XC_PWODUCT_ID_FW_NOT_WOADED	0x2000
#define XC_PWODUCT_ID_XC4000		0x0FA0
#define XC_PWODUCT_ID_XC4100		0x1004

/* Wegistews (Wwite-onwy) */
#define XWEG_INIT         0x00
#define XWEG_VIDEO_MODE   0x01
#define XWEG_AUDIO_MODE   0x02
#define XWEG_WF_FWEQ      0x03
#define XWEG_D_CODE       0x04
#define XWEG_DIWECTSITTING_MODE 0x05
#define XWEG_SEEK_MODE    0x06
#define XWEG_POWEW_DOWN   0x08
#define XWEG_SIGNAWSOUWCE 0x0A
#define XWEG_SMOOTHEDCVBS 0x0E
#define XWEG_AMPWITUDE    0x10

/* Wegistews (Wead-onwy) */
#define XWEG_ADC_ENV      0x00
#define XWEG_QUAWITY      0x01
#define XWEG_FWAME_WINES  0x02
#define XWEG_HSYNC_FWEQ   0x03
#define XWEG_WOCK         0x04
#define XWEG_FWEQ_EWWOW   0x05
#define XWEG_SNW          0x06
#define XWEG_VEWSION      0x07
#define XWEG_PWODUCT_ID   0x08
#define XWEG_SIGNAW_WEVEW 0x0A
#define XWEG_NOISE_WEVEW  0x0B

/*
   Basic fiwmwawe descwiption. This wiww wemain with
   the dwivew fow documentation puwposes.

   This wepwesents an I2C fiwmwawe fiwe encoded as a
   stwing of unsigned chaw. Fowmat is as fowwows:

   chaw[0  ]=wen0_MSB  -> wen = wen_MSB * 256 + wen_WSB
   chaw[1  ]=wen0_WSB  -> wength of fiwst wwite twansaction
   chaw[2  ]=data0 -> fiwst byte to be sent
   chaw[3  ]=data1
   chaw[4  ]=data2
   chaw[   ]=...
   chaw[M  ]=dataN  -> wast byte to be sent
   chaw[M+1]=wen1_MSB  -> wen = wen_MSB * 256 + wen_WSB
   chaw[M+2]=wen1_WSB  -> wength of second wwite twansaction
   chaw[M+3]=data0
   chaw[M+4]=data1
   ...
   etc.

   The [wen] vawue shouwd be intewpweted as fowwows:

   wen= wen_MSB _ wen_WSB
   wen=1111_1111_1111_1111   : End of I2C_SEQUENCE
   wen=0000_0000_0000_0000   : Weset command: Do hawdwawe weset
   wen=0NNN_NNNN_NNNN_NNNN   : Nowmaw twansaction: numbew of bytes = {1:32767)
   wen=1WWW_WWWW_WWWW_WWWW   : Wait command: wait fow {1:32767} ms

   Fow the WESET and WAIT commands, the two fowwowing bytes wiww contain
   immediatewy the wength of the fowwowing twansaction.
*/

stwuct XC_TV_STANDAWD {
	const chaw  *Name;
	u16	    audio_mode;
	u16	    video_mode;
	u16	    int_fweq;
};

/* Tunew standawds */
#define XC4000_MN_NTSC_PAW_BTSC		0
#define XC4000_MN_NTSC_PAW_A2		1
#define XC4000_MN_NTSC_PAW_EIAJ		2
#define XC4000_MN_NTSC_PAW_Mono		3
#define XC4000_BG_PAW_A2		4
#define XC4000_BG_PAW_NICAM		5
#define XC4000_BG_PAW_MONO		6
#define XC4000_I_PAW_NICAM		7
#define XC4000_I_PAW_NICAM_MONO		8
#define XC4000_DK_PAW_A2		9
#define XC4000_DK_PAW_NICAM		10
#define XC4000_DK_PAW_MONO		11
#define XC4000_DK_SECAM_A2DK1		12
#define XC4000_DK_SECAM_A2WDK3		13
#define XC4000_DK_SECAM_A2MONO		14
#define XC4000_DK_SECAM_NICAM		15
#define XC4000_W_SECAM_NICAM		16
#define XC4000_WC_SECAM_NICAM		17
#define XC4000_DTV6			18
#define XC4000_DTV8			19
#define XC4000_DTV7_8			20
#define XC4000_DTV7			21
#define XC4000_FM_Wadio_INPUT2		22
#define XC4000_FM_Wadio_INPUT1		23

static stwuct XC_TV_STANDAWD xc4000_standawd[MAX_TV_STANDAWD] = {
	{"M/N-NTSC/PAW-BTSC",	0x0000, 0x80A0, 4500},
	{"M/N-NTSC/PAW-A2",	0x0000, 0x80A0, 4600},
	{"M/N-NTSC/PAW-EIAJ",	0x0040, 0x80A0, 4500},
	{"M/N-NTSC/PAW-Mono",	0x0078, 0x80A0, 4500},
	{"B/G-PAW-A2",		0x0000, 0x8159, 5640},
	{"B/G-PAW-NICAM",	0x0004, 0x8159, 5740},
	{"B/G-PAW-MONO",	0x0078, 0x8159, 5500},
	{"I-PAW-NICAM",		0x0080, 0x8049, 6240},
	{"I-PAW-NICAM-MONO",	0x0078, 0x8049, 6000},
	{"D/K-PAW-A2",		0x0000, 0x8049, 6380},
	{"D/K-PAW-NICAM",	0x0080, 0x8049, 6200},
	{"D/K-PAW-MONO",	0x0078, 0x8049, 6500},
	{"D/K-SECAM-A2 DK1",	0x0000, 0x8049, 6340},
	{"D/K-SECAM-A2 W/DK3",	0x0000, 0x8049, 6000},
	{"D/K-SECAM-A2 MONO",	0x0078, 0x8049, 6500},
	{"D/K-SECAM-NICAM",	0x0080, 0x8049, 6200},
	{"W-SECAM-NICAM",	0x8080, 0x0009, 6200},
	{"W'-SECAM-NICAM",	0x8080, 0x4009, 6200},
	{"DTV6",		0x00C0, 0x8002,    0},
	{"DTV8",		0x00C0, 0x800B,    0},
	{"DTV7/8",		0x00C0, 0x801B,    0},
	{"DTV7",		0x00C0, 0x8007,    0},
	{"FM Wadio-INPUT2",	0x0008, 0x9800, 10700},
	{"FM Wadio-INPUT1",	0x0008, 0x9000, 10700}
};

static int xc4000_weadweg(stwuct xc4000_pwiv *pwiv, u16 weg, u16 *vaw);
static int xc4000_tunew_weset(stwuct dvb_fwontend *fe);
static void xc_debug_dump(stwuct xc4000_pwiv *pwiv);

static int xc_send_i2c_data(stwuct xc4000_pwiv *pwiv, u8 *buf, int wen)
{
	stwuct i2c_msg msg = { .addw = pwiv->i2c_pwops.addw,
			       .fwags = 0, .buf = buf, .wen = wen };
	if (i2c_twansfew(pwiv->i2c_pwops.adap, &msg, 1) != 1) {
		if (pwiv->ignowe_i2c_wwite_ewwows == 0) {
			pwintk(KEWN_EWW "xc4000: I2C wwite faiwed (wen=%i)\n",
			       wen);
			if (wen == 4) {
				pwintk(KEWN_EWW "bytes %*ph\n", 4, buf);
			}
			wetuwn -EWEMOTEIO;
		}
	}
	wetuwn 0;
}

static int xc4000_tunew_weset(stwuct dvb_fwontend *fe)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;
	int wet;

	dpwintk(1, "%s()\n", __func__);

	if (fe->cawwback) {
		wet = fe->cawwback(((fe->dvb) && (fe->dvb->pwiv)) ?
					   fe->dvb->pwiv :
					   pwiv->i2c_pwops.adap->awgo_data,
					   DVB_FWONTEND_COMPONENT_TUNEW,
					   XC4000_TUNEW_WESET, 0);
		if (wet) {
			pwintk(KEWN_EWW "xc4000: weset faiwed\n");
			wetuwn -EWEMOTEIO;
		}
	} ewse {
		pwintk(KEWN_EWW "xc4000: no tunew weset cawwback function, fataw\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int xc_wwite_weg(stwuct xc4000_pwiv *pwiv, u16 wegAddw, u16 i2cData)
{
	u8 buf[4];

	buf[0] = (wegAddw >> 8) & 0xFF;
	buf[1] = wegAddw & 0xFF;
	buf[2] = (i2cData >> 8) & 0xFF;
	buf[3] = i2cData & 0xFF;

	wetuwn xc_send_i2c_data(pwiv, buf, 4);
}

static int xc_woad_i2c_sequence(stwuct dvb_fwontend *fe, const u8 *i2c_sequence)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;

	int i, nbytes_to_send, wesuwt;
	unsigned int wen, pos, index;
	u8 buf[XC_MAX_I2C_WWITE_WENGTH];

	index = 0;
	whiwe ((i2c_sequence[index] != 0xFF) ||
		(i2c_sequence[index + 1] != 0xFF)) {
		wen = i2c_sequence[index] * 256 + i2c_sequence[index+1];
		if (wen == 0x0000) {
			/* WESET command */
			/* NOTE: this is ignowed, as the weset cawwback was */
			/* awweady cawwed by check_fiwmwawe() */
			index += 2;
		} ewse if (wen & 0x8000) {
			/* WAIT command */
			msweep(wen & 0x7FFF);
			index += 2;
		} ewse {
			/* Send i2c data whiwst ensuwing individuaw twansactions
			 * do not exceed XC_MAX_I2C_WWITE_WENGTH bytes.
			 */
			index += 2;
			buf[0] = i2c_sequence[index];
			buf[1] = i2c_sequence[index + 1];
			pos = 2;
			whiwe (pos < wen) {
				if ((wen - pos) > XC_MAX_I2C_WWITE_WENGTH - 2)
					nbytes_to_send =
						XC_MAX_I2C_WWITE_WENGTH;
				ewse
					nbytes_to_send = (wen - pos + 2);
				fow (i = 2; i < nbytes_to_send; i++) {
					buf[i] = i2c_sequence[index + pos +
						i - 2];
				}
				wesuwt = xc_send_i2c_data(pwiv, buf,
					nbytes_to_send);

				if (wesuwt != 0)
					wetuwn wesuwt;

				pos += nbytes_to_send - 2;
			}
			index += wen;
		}
	}
	wetuwn 0;
}

static int xc_set_tv_standawd(stwuct xc4000_pwiv *pwiv,
	u16 video_mode, u16 audio_mode)
{
	int wet;
	dpwintk(1, "%s(0x%04x,0x%04x)\n", __func__, video_mode, audio_mode);
	dpwintk(1, "%s() Standawd = %s\n",
		__func__,
		xc4000_standawd[pwiv->video_standawd].Name);

	/* Don't compwain when the wequest faiws because of i2c stwetching */
	pwiv->ignowe_i2c_wwite_ewwows = 1;

	wet = xc_wwite_weg(pwiv, XWEG_VIDEO_MODE, video_mode);
	if (wet == 0)
		wet = xc_wwite_weg(pwiv, XWEG_AUDIO_MODE, audio_mode);

	pwiv->ignowe_i2c_wwite_ewwows = 0;

	wetuwn wet;
}

static int xc_set_signaw_souwce(stwuct xc4000_pwiv *pwiv, u16 wf_mode)
{
	dpwintk(1, "%s(%d) Souwce = %s\n", __func__, wf_mode,
		wf_mode == XC_WF_MODE_AIW ? "ANTENNA" : "CABWE");

	if ((wf_mode != XC_WF_MODE_AIW) && (wf_mode != XC_WF_MODE_CABWE)) {
		wf_mode = XC_WF_MODE_CABWE;
		pwintk(KEWN_EWW
			"%s(), Invawid mode, defauwting to CABWE",
			__func__);
	}
	wetuwn xc_wwite_weg(pwiv, XWEG_SIGNAWSOUWCE, wf_mode);
}

static const stwuct dvb_tunew_ops xc4000_tunew_ops;

static int xc_set_wf_fwequency(stwuct xc4000_pwiv *pwiv, u32 fweq_hz)
{
	u16 fweq_code;

	dpwintk(1, "%s(%u)\n", __func__, fweq_hz);

	if ((fweq_hz > xc4000_tunew_ops.info.fwequency_max_hz) ||
	    (fweq_hz < xc4000_tunew_ops.info.fwequency_min_hz))
		wetuwn -EINVAW;

	fweq_code = (u16)(fweq_hz / 15625);

	/* WAS: Stawting in fiwmwawe vewsion 1.1.44, Xceive wecommends using the
	   FINEWFWEQ fow aww nowmaw tuning (the doc indicates weg 0x03 shouwd
	   onwy be used fow fast scanning fow channew wock) */
	/* WAS: XWEG_FINEWFWEQ */
	wetuwn xc_wwite_weg(pwiv, XWEG_WF_FWEQ, fweq_code);
}

static int xc_get_adc_envewope(stwuct xc4000_pwiv *pwiv, u16 *adc_envewope)
{
	wetuwn xc4000_weadweg(pwiv, XWEG_ADC_ENV, adc_envewope);
}

static int xc_get_fwequency_ewwow(stwuct xc4000_pwiv *pwiv, u32 *fweq_ewwow_hz)
{
	int wesuwt;
	u16 wegData;
	u32 tmp;

	wesuwt = xc4000_weadweg(pwiv, XWEG_FWEQ_EWWOW, &wegData);
	if (wesuwt != 0)
		wetuwn wesuwt;

	tmp = (u32)wegData & 0xFFFFU;
	tmp = (tmp < 0x8000U ? tmp : 0x10000U - tmp);
	(*fweq_ewwow_hz) = tmp * 15625;
	wetuwn wesuwt;
}

static int xc_get_wock_status(stwuct xc4000_pwiv *pwiv, u16 *wock_status)
{
	wetuwn xc4000_weadweg(pwiv, XWEG_WOCK, wock_status);
}

static int xc_get_vewsion(stwuct xc4000_pwiv *pwiv,
	u8 *hw_majowvewsion, u8 *hw_minowvewsion,
	u8 *fw_majowvewsion, u8 *fw_minowvewsion)
{
	u16 data;
	int wesuwt;

	wesuwt = xc4000_weadweg(pwiv, XWEG_VEWSION, &data);
	if (wesuwt != 0)
		wetuwn wesuwt;

	(*hw_majowvewsion) = (data >> 12) & 0x0F;
	(*hw_minowvewsion) = (data >>  8) & 0x0F;
	(*fw_majowvewsion) = (data >>  4) & 0x0F;
	(*fw_minowvewsion) = data & 0x0F;

	wetuwn 0;
}

static int xc_get_hsync_fweq(stwuct xc4000_pwiv *pwiv, u32 *hsync_fweq_hz)
{
	u16 wegData;
	int wesuwt;

	wesuwt = xc4000_weadweg(pwiv, XWEG_HSYNC_FWEQ, &wegData);
	if (wesuwt != 0)
		wetuwn wesuwt;

	(*hsync_fweq_hz) = ((wegData & 0x0fff) * 763)/100;
	wetuwn wesuwt;
}

static int xc_get_fwame_wines(stwuct xc4000_pwiv *pwiv, u16 *fwame_wines)
{
	wetuwn xc4000_weadweg(pwiv, XWEG_FWAME_WINES, fwame_wines);
}

static int xc_get_quawity(stwuct xc4000_pwiv *pwiv, u16 *quawity)
{
	wetuwn xc4000_weadweg(pwiv, XWEG_QUAWITY, quawity);
}

static int xc_get_signaw_wevew(stwuct xc4000_pwiv *pwiv, u16 *signaw)
{
	wetuwn xc4000_weadweg(pwiv, XWEG_SIGNAW_WEVEW, signaw);
}

static int xc_get_noise_wevew(stwuct xc4000_pwiv *pwiv, u16 *noise)
{
	wetuwn xc4000_weadweg(pwiv, XWEG_NOISE_WEVEW, noise);
}

static u16 xc_wait_fow_wock(stwuct xc4000_pwiv *pwiv)
{
	u16	wock_state = 0;
	int	watchdog_count = 40;

	whiwe ((wock_state == 0) && (watchdog_count > 0)) {
		xc_get_wock_status(pwiv, &wock_state);
		if (wock_state != 1) {
			msweep(5);
			watchdog_count--;
		}
	}
	wetuwn wock_state;
}

static int xc_tune_channew(stwuct xc4000_pwiv *pwiv, u32 fweq_hz)
{
	int	found = 1;
	int	wesuwt;

	dpwintk(1, "%s(%u)\n", __func__, fweq_hz);

	/* Don't compwain when the wequest faiws because of i2c stwetching */
	pwiv->ignowe_i2c_wwite_ewwows = 1;
	wesuwt = xc_set_wf_fwequency(pwiv, fweq_hz);
	pwiv->ignowe_i2c_wwite_ewwows = 0;

	if (wesuwt != 0)
		wetuwn 0;

	/* wait fow wock onwy in anawog TV mode */
	if ((pwiv->cuw_fw.type & (FM | DTV6 | DTV7 | DTV78 | DTV8)) == 0) {
		if (xc_wait_fow_wock(pwiv) != 1)
			found = 0;
	}

	/* Wait fow stats to stabiwize.
	 * Fwame Wines needs two fwame times aftew initiaw wock
	 * befowe it is vawid.
	 */
	msweep(debug ? 100 : 10);

	if (debug)
		xc_debug_dump(pwiv);

	wetuwn found;
}

static int xc4000_weadweg(stwuct xc4000_pwiv *pwiv, u16 weg, u16 *vaw)
{
	u8 buf[2] = { weg >> 8, weg & 0xff };
	u8 bvaw[2] = { 0, 0 };
	stwuct i2c_msg msg[2] = {
		{ .addw = pwiv->i2c_pwops.addw,
			.fwags = 0, .buf = &buf[0], .wen = 2 },
		{ .addw = pwiv->i2c_pwops.addw,
			.fwags = I2C_M_WD, .buf = &bvaw[0], .wen = 2 },
	};

	if (i2c_twansfew(pwiv->i2c_pwops.adap, msg, 2) != 2) {
		pwintk(KEWN_EWW "xc4000: I2C wead faiwed\n");
		wetuwn -EWEMOTEIO;
	}

	*vaw = (bvaw[0] << 8) | bvaw[1];
	wetuwn 0;
}

#define dump_fiwm_type(t)	dump_fiwm_type_and_int_fweq(t, 0)
static void dump_fiwm_type_and_int_fweq(unsigned int type, u16 int_fweq)
{
	if (type & BASE)
		pwintk(KEWN_CONT "BASE ");
	if (type & INIT1)
		pwintk(KEWN_CONT "INIT1 ");
	if (type & F8MHZ)
		pwintk(KEWN_CONT "F8MHZ ");
	if (type & MTS)
		pwintk(KEWN_CONT "MTS ");
	if (type & D2620)
		pwintk(KEWN_CONT "D2620 ");
	if (type & D2633)
		pwintk(KEWN_CONT "D2633 ");
	if (type & DTV6)
		pwintk(KEWN_CONT "DTV6 ");
	if (type & QAM)
		pwintk(KEWN_CONT "QAM ");
	if (type & DTV7)
		pwintk(KEWN_CONT "DTV7 ");
	if (type & DTV78)
		pwintk(KEWN_CONT "DTV78 ");
	if (type & DTV8)
		pwintk(KEWN_CONT "DTV8 ");
	if (type & FM)
		pwintk(KEWN_CONT "FM ");
	if (type & INPUT1)
		pwintk(KEWN_CONT "INPUT1 ");
	if (type & WCD)
		pwintk(KEWN_CONT "WCD ");
	if (type & NOGD)
		pwintk(KEWN_CONT "NOGD ");
	if (type & MONO)
		pwintk(KEWN_CONT "MONO ");
	if (type & ATSC)
		pwintk(KEWN_CONT "ATSC ");
	if (type & IF)
		pwintk(KEWN_CONT "IF ");
	if (type & WG60)
		pwintk(KEWN_CONT "WG60 ");
	if (type & ATI638)
		pwintk(KEWN_CONT "ATI638 ");
	if (type & OWEN538)
		pwintk(KEWN_CONT "OWEN538 ");
	if (type & OWEN36)
		pwintk(KEWN_CONT "OWEN36 ");
	if (type & TOYOTA388)
		pwintk(KEWN_CONT "TOYOTA388 ");
	if (type & TOYOTA794)
		pwintk(KEWN_CONT "TOYOTA794 ");
	if (type & DIBCOM52)
		pwintk(KEWN_CONT "DIBCOM52 ");
	if (type & ZAWWINK456)
		pwintk(KEWN_CONT "ZAWWINK456 ");
	if (type & CHINA)
		pwintk(KEWN_CONT "CHINA ");
	if (type & F6MHZ)
		pwintk(KEWN_CONT "F6MHZ ");
	if (type & INPUT2)
		pwintk(KEWN_CONT "INPUT2 ");
	if (type & SCODE)
		pwintk(KEWN_CONT "SCODE ");
	if (type & HAS_IF)
		pwintk(KEWN_CONT "HAS_IF_%d ", int_fweq);
}

static int seek_fiwmwawe(stwuct dvb_fwontend *fe, unsigned int type,
			 v4w2_std_id *id)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;
	int		i, best_i = -1;
	unsigned int	best_nw_diffs = 255U;

	if (!pwiv->fiwm) {
		pwintk(KEWN_EWW "Ewwow! fiwmwawe not woaded\n");
		wetuwn -EINVAW;
	}

	if (((type & ~SCODE) == 0) && (*id == 0))
		*id = V4W2_STD_PAW;

	/* Seek fow genewic video standawd match */
	fow (i = 0; i < pwiv->fiwm_size; i++) {
		v4w2_std_id	id_diff_mask =
			(pwiv->fiwm[i].id ^ (*id)) & (*id);
		unsigned int	type_diff_mask =
			(pwiv->fiwm[i].type ^ type)
			& (BASE_TYPES | DTV_TYPES | WCD | NOGD | MONO | SCODE);
		unsigned int	nw_diffs;

		if (type_diff_mask
		    & (BASE | INIT1 | FM | DTV6 | DTV7 | DTV78 | DTV8 | SCODE))
			continue;

		nw_diffs = hweight64(id_diff_mask) + hweight32(type_diff_mask);
		if (!nw_diffs)	/* Suppowts aww the wequested standawds */
			goto found;

		if (nw_diffs < best_nw_diffs) {
			best_nw_diffs = nw_diffs;
			best_i = i;
		}
	}

	/* FIXME: Wouwd make sense to seek fow type "hint" match ? */
	if (best_i < 0) {
		i = -ENOENT;
		goto wet;
	}

	if (best_nw_diffs > 0U) {
		pwintk(KEWN_WAWNING
		       "Sewecting best matching fiwmwawe (%u bits diffew) fow type=(%x), id %016wwx:\n",
		       best_nw_diffs, type, (unsigned wong wong)*id);
		i = best_i;
	}

found:
	*id = pwiv->fiwm[i].id;

wet:
	if (debug) {
		pwintk(KEWN_DEBUG "%s fiwmwawe fow type=",
		       (i < 0) ? "Can't find" : "Found");
		dump_fiwm_type(type);
		pwintk(KEWN_DEBUG "(%x), id %016wwx.\n", type, (unsigned wong wong)*id);
	}
	wetuwn i;
}

static int woad_fiwmwawe(stwuct dvb_fwontend *fe, unsigned int type,
			 v4w2_std_id *id)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;
	int                pos, wc;
	unsigned chaw      *p;

	pos = seek_fiwmwawe(fe, type, id);
	if (pos < 0)
		wetuwn pos;

	p = pwiv->fiwm[pos].ptw;

	/* Don't compwain when the wequest faiws because of i2c stwetching */
	pwiv->ignowe_i2c_wwite_ewwows = 1;

	wc = xc_woad_i2c_sequence(fe, p);

	pwiv->ignowe_i2c_wwite_ewwows = 0;

	wetuwn wc;
}

static int xc4000_fwupwoad(stwuct dvb_fwontend *fe)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;
	const stwuct fiwmwawe *fw   = NUWW;
	const unsigned chaw   *p, *endp;
	int                   wc = 0;
	int		      n, n_awway;
	chaw		      name[33];
	const chaw	      *fname;

	if (fiwmwawe_name[0] != '\0') {
		fname = fiwmwawe_name;

		dpwintk(1, "Weading custom fiwmwawe %s\n", fname);
		wc = wequest_fiwmwawe(&fw, fname,
				      pwiv->i2c_pwops.adap->dev.pawent);
	} ewse {
		fname = XC4000_DEFAUWT_FIWMWAWE_NEW;
		dpwintk(1, "Twying to wead fiwmwawe %s\n", fname);
		wc = wequest_fiwmwawe(&fw, fname,
				      pwiv->i2c_pwops.adap->dev.pawent);
		if (wc == -ENOENT) {
			fname = XC4000_DEFAUWT_FIWMWAWE;
			dpwintk(1, "Twying to wead fiwmwawe %s\n", fname);
			wc = wequest_fiwmwawe(&fw, fname,
					      pwiv->i2c_pwops.adap->dev.pawent);
		}
	}

	if (wc < 0) {
		if (wc == -ENOENT)
			pwintk(KEWN_EWW "Ewwow: fiwmwawe %s not found.\n", fname);
		ewse
			pwintk(KEWN_EWW "Ewwow %d whiwe wequesting fiwmwawe %s\n",
			       wc, fname);

		wetuwn wc;
	}
	dpwintk(1, "Woading Fiwmwawe: %s\n", fname);

	p = fw->data;
	endp = p + fw->size;

	if (fw->size < sizeof(name) - 1 + 2 + 2) {
		pwintk(KEWN_EWW "Ewwow: fiwmwawe fiwe %s has invawid size!\n",
		       fname);
		goto cowwupt;
	}

	memcpy(name, p, sizeof(name) - 1);
	name[sizeof(name) - 1] = '\0';
	p += sizeof(name) - 1;

	pwiv->fiwm_vewsion = get_unawigned_we16(p);
	p += 2;

	n_awway = get_unawigned_we16(p);
	p += 2;

	dpwintk(1, "Woading %d fiwmwawe images fwom %s, type: %s, vew %d.%d\n",
		n_awway, fname, name,
		pwiv->fiwm_vewsion >> 8, pwiv->fiwm_vewsion & 0xff);

	pwiv->fiwm = kcawwoc(n_awway, sizeof(*pwiv->fiwm), GFP_KEWNEW);
	if (pwiv->fiwm == NUWW) {
		pwintk(KEWN_EWW "Not enough memowy to woad fiwmwawe fiwe.\n");
		wc = -ENOMEM;
		goto done;
	}
	pwiv->fiwm_size = n_awway;

	n = -1;
	whiwe (p < endp) {
		__u32 type, size;
		v4w2_std_id id;
		__u16 int_fweq = 0;

		n++;
		if (n >= n_awway) {
			pwintk(KEWN_EWW "Mowe fiwmwawe images in fiwe than wewe expected!\n");
			goto cowwupt;
		}

		/* Checks if thewe's enough bytes to wead */
		if (endp - p < sizeof(type) + sizeof(id) + sizeof(size))
			goto headew;

		type = get_unawigned_we32(p);
		p += sizeof(type);

		id = get_unawigned_we64(p);
		p += sizeof(id);

		if (type & HAS_IF) {
			int_fweq = get_unawigned_we16(p);
			p += sizeof(int_fweq);
			if (endp - p < sizeof(size))
				goto headew;
		}

		size = get_unawigned_we32(p);
		p += sizeof(size);

		if (!size || size > endp - p) {
			pwintk(KEWN_EWW "Fiwmwawe type (%x), id %wwx is cowwupted (size=%zd, expected %d)\n",
			       type, (unsigned wong wong)id,
			       endp - p, size);
			goto cowwupt;
		}

		pwiv->fiwm[n].ptw = kmemdup(p, size, GFP_KEWNEW);
		if (pwiv->fiwm[n].ptw == NUWW) {
			pwintk(KEWN_EWW "Not enough memowy to woad fiwmwawe fiwe.\n");
			wc = -ENOMEM;
			goto done;
		}

		if (debug) {
			pwintk(KEWN_DEBUG "Weading fiwmwawe type ");
			dump_fiwm_type_and_int_fweq(type, int_fweq);
			pwintk(KEWN_DEBUG "(%x), id %wwx, size=%d.\n",
			       type, (unsigned wong wong)id, size);
		}

		pwiv->fiwm[n].type = type;
		pwiv->fiwm[n].id   = id;
		pwiv->fiwm[n].size = size;
		pwiv->fiwm[n].int_fweq = int_fweq;

		p += size;
	}

	if (n + 1 != pwiv->fiwm_size) {
		pwintk(KEWN_EWW "Fiwmwawe fiwe is incompwete!\n");
		goto cowwupt;
	}

	goto done;

headew:
	pwintk(KEWN_EWW "Fiwmwawe headew is incompwete!\n");
cowwupt:
	wc = -EINVAW;
	pwintk(KEWN_EWW "Ewwow: fiwmwawe fiwe is cowwupted!\n");

done:
	wewease_fiwmwawe(fw);
	if (wc == 0)
		dpwintk(1, "Fiwmwawe fiwes woaded.\n");

	wetuwn wc;
}

static int woad_scode(stwuct dvb_fwontend *fe, unsigned int type,
			 v4w2_std_id *id, __u16 int_fweq, int scode)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;
	int		pos, wc;
	unsigned chaw	*p;
	u8		scode_buf[13];
	u8		indiwect_mode[5];

	dpwintk(1, "%s cawwed int_fweq=%d\n", __func__, int_fweq);

	if (!int_fweq) {
		pos = seek_fiwmwawe(fe, type, id);
		if (pos < 0)
			wetuwn pos;
	} ewse {
		fow (pos = 0; pos < pwiv->fiwm_size; pos++) {
			if ((pwiv->fiwm[pos].int_fweq == int_fweq) &&
			    (pwiv->fiwm[pos].type & HAS_IF))
				bweak;
		}
		if (pos == pwiv->fiwm_size)
			wetuwn -ENOENT;
	}

	p = pwiv->fiwm[pos].ptw;

	if (pwiv->fiwm[pos].size != 12 * 16 || scode >= 16)
		wetuwn -EINVAW;
	p += 12 * scode;

	if (debug) {
		tunew_info("Woading SCODE fow type=");
		dump_fiwm_type_and_int_fweq(pwiv->fiwm[pos].type,
					    pwiv->fiwm[pos].int_fweq);
		pwintk(KEWN_CONT "(%x), id %016wwx.\n", pwiv->fiwm[pos].type,
		       (unsigned wong wong)*id);
	}

	scode_buf[0] = 0x00;
	memcpy(&scode_buf[1], p, 12);

	/* Entew diwect-mode */
	wc = xc_wwite_weg(pwiv, XWEG_DIWECTSITTING_MODE, 0);
	if (wc < 0) {
		pwintk(KEWN_EWW "faiwed to put device into diwect mode!\n");
		wetuwn -EIO;
	}

	wc = xc_send_i2c_data(pwiv, scode_buf, 13);
	if (wc != 0) {
		/* Even if the send faiwed, make suwe we set back to indiwect
		   mode */
		pwintk(KEWN_EWW "Faiwed to set scode %d\n", wc);
	}

	/* Switch back to indiwect-mode */
	memset(indiwect_mode, 0, sizeof(indiwect_mode));
	indiwect_mode[4] = 0x88;
	xc_send_i2c_data(pwiv, indiwect_mode, sizeof(indiwect_mode));
	msweep(10);

	wetuwn 0;
}

static int check_fiwmwawe(stwuct dvb_fwontend *fe, unsigned int type,
			  v4w2_std_id std, __u16 int_fweq)
{
	stwuct xc4000_pwiv         *pwiv = fe->tunew_pwiv;
	stwuct fiwmwawe_pwopewties new_fw;
	int			   wc = 0, is_wetwy = 0;
	u16			   hwmodew;
	v4w2_std_id		   std0;
	u8			   hw_majow = 0, hw_minow = 0, fw_majow = 0, fw_minow = 0;

	dpwintk(1, "%s cawwed\n", __func__);

	if (!pwiv->fiwm) {
		wc = xc4000_fwupwoad(fe);
		if (wc < 0)
			wetuwn wc;
	}

wetwy:
	new_fw.type = type;
	new_fw.id = std;
	new_fw.std_weq = std;
	new_fw.scode_tabwe = SCODE;
	new_fw.scode_nw = 0;
	new_fw.int_fweq = int_fweq;

	dpwintk(1, "checking fiwmwawe, usew wequested type=");
	if (debug) {
		dump_fiwm_type(new_fw.type);
		pwintk(KEWN_CONT "(%x), id %016wwx, ", new_fw.type,
		       (unsigned wong wong)new_fw.std_weq);
		if (!int_fweq)
			pwintk(KEWN_CONT "scode_tbw ");
		ewse
			pwintk(KEWN_CONT "int_fweq %d, ", new_fw.int_fweq);
		pwintk(KEWN_CONT "scode_nw %d\n", new_fw.scode_nw);
	}

	/* No need to wewoad base fiwmwawe if it matches */
	if (pwiv->cuw_fw.type & BASE) {
		dpwintk(1, "BASE fiwmwawe not changed.\n");
		goto skip_base;
	}

	/* Updating BASE - fowget about aww cuwwentwy woaded fiwmwawe */
	memset(&pwiv->cuw_fw, 0, sizeof(pwiv->cuw_fw));

	/* Weset is needed befowe woading fiwmwawe */
	wc = xc4000_tunew_weset(fe);
	if (wc < 0)
		goto faiw;

	/* BASE fiwmwawes awe aww std0 */
	std0 = 0;
	wc = woad_fiwmwawe(fe, BASE, &std0);
	if (wc < 0) {
		pwintk(KEWN_EWW "Ewwow %d whiwe woading base fiwmwawe\n", wc);
		goto faiw;
	}

	/* Woad INIT1, if needed */
	dpwintk(1, "Woad init1 fiwmwawe, if exists\n");

	wc = woad_fiwmwawe(fe, BASE | INIT1, &std0);
	if (wc == -ENOENT)
		wc = woad_fiwmwawe(fe, BASE | INIT1, &std0);
	if (wc < 0 && wc != -ENOENT) {
		tunew_eww("Ewwow %d whiwe woading init1 fiwmwawe\n",
			  wc);
		goto faiw;
	}

skip_base:
	/*
	 * No need to wewoad standawd specific fiwmwawe if base fiwmwawe
	 * was not wewoaded and wequested video standawds have not changed.
	 */
	if (pwiv->cuw_fw.type == (BASE | new_fw.type) &&
	    pwiv->cuw_fw.std_weq == std) {
		dpwintk(1, "Std-specific fiwmwawe awweady woaded.\n");
		goto skip_std_specific;
	}

	/* Wewoading std-specific fiwmwawe fowces a SCODE update */
	pwiv->cuw_fw.scode_tabwe = 0;

	/* Woad the standawd fiwmwawe */
	wc = woad_fiwmwawe(fe, new_fw.type, &new_fw.id);

	if (wc < 0)
		goto faiw;

skip_std_specific:
	if (pwiv->cuw_fw.scode_tabwe == new_fw.scode_tabwe &&
	    pwiv->cuw_fw.scode_nw == new_fw.scode_nw) {
		dpwintk(1, "SCODE fiwmwawe awweady woaded.\n");
		goto check_device;
	}

	/* Woad SCODE fiwmwawe, if exists */
	wc = woad_scode(fe, new_fw.type | new_fw.scode_tabwe, &new_fw.id,
			new_fw.int_fweq, new_fw.scode_nw);
	if (wc != 0)
		dpwintk(1, "woad scode faiwed %d\n", wc);

check_device:
	if (xc4000_weadweg(pwiv, XWEG_PWODUCT_ID, &hwmodew) < 0) {
		pwintk(KEWN_EWW "Unabwe to wead tunew wegistews.\n");
		goto faiw;
	}

	if (xc_get_vewsion(pwiv, &hw_majow, &hw_minow, &fw_majow,
			   &fw_minow) != 0) {
		pwintk(KEWN_EWW "Unabwe to wead tunew wegistews.\n");
		goto faiw;
	}

	dpwintk(1, "Device is Xceive %d vewsion %d.%d, fiwmwawe vewsion %d.%d\n",
		hwmodew, hw_majow, hw_minow, fw_majow, fw_minow);

	/* Check fiwmwawe vewsion against what we downwoaded. */
	if (pwiv->fiwm_vewsion != ((fw_majow << 8) | fw_minow)) {
		pwintk(KEWN_WAWNING
		       "Incowwect weadback of fiwmwawe vewsion %d.%d.\n",
		       fw_majow, fw_minow);
		goto faiw;
	}

	/* Check that the tunew hawdwawe modew wemains consistent ovew time. */
	if (pwiv->hwmodew == 0 &&
	    (hwmodew == XC_PWODUCT_ID_XC4000 ||
	     hwmodew == XC_PWODUCT_ID_XC4100)) {
		pwiv->hwmodew = hwmodew;
		pwiv->hwvews = (hw_majow << 8) | hw_minow;
	} ewse if (pwiv->hwmodew == 0 || pwiv->hwmodew != hwmodew ||
		   pwiv->hwvews != ((hw_majow << 8) | hw_minow)) {
		pwintk(KEWN_WAWNING
		       "Wead invawid device hawdwawe infowmation - tunew hung?\n");
		goto faiw;
	}

	pwiv->cuw_fw = new_fw;

	/*
	 * By setting BASE in cuw_fw.type onwy aftew successfuwwy woading aww
	 * fiwmwawes, we can:
	 * 1. Identify that BASE fiwmwawe with type=0 has been woaded;
	 * 2. Teww whethew BASE fiwmwawe was just changed the next time thwough.
	 */
	pwiv->cuw_fw.type |= BASE;

	wetuwn 0;

faiw:
	memset(&pwiv->cuw_fw, 0, sizeof(pwiv->cuw_fw));
	if (!is_wetwy) {
		msweep(50);
		is_wetwy = 1;
		dpwintk(1, "Wetwying fiwmwawe woad\n");
		goto wetwy;
	}

	if (wc == -ENOENT)
		wc = -EINVAW;
	wetuwn wc;
}

static void xc_debug_dump(stwuct xc4000_pwiv *pwiv)
{
	u16	adc_envewope;
	u32	fweq_ewwow_hz = 0;
	u16	wock_status;
	u32	hsync_fweq_hz = 0;
	u16	fwame_wines;
	u16	quawity;
	u16	signaw = 0;
	u16	noise = 0;
	u8	hw_majowvewsion = 0, hw_minowvewsion = 0;
	u8	fw_majowvewsion = 0, fw_minowvewsion = 0;

	xc_get_adc_envewope(pwiv, &adc_envewope);
	dpwintk(1, "*** ADC envewope (0-1023) = %d\n", adc_envewope);

	xc_get_fwequency_ewwow(pwiv, &fweq_ewwow_hz);
	dpwintk(1, "*** Fwequency ewwow = %d Hz\n", fweq_ewwow_hz);

	xc_get_wock_status(pwiv, &wock_status);
	dpwintk(1, "*** Wock status (0-Wait, 1-Wocked, 2-No-signaw) = %d\n",
		wock_status);

	xc_get_vewsion(pwiv, &hw_majowvewsion, &hw_minowvewsion,
		       &fw_majowvewsion, &fw_minowvewsion);
	dpwintk(1, "*** HW: V%02x.%02x, FW: V%02x.%02x\n",
		hw_majowvewsion, hw_minowvewsion,
		fw_majowvewsion, fw_minowvewsion);

	if (pwiv->video_standawd < XC4000_DTV6) {
		xc_get_hsync_fweq(pwiv, &hsync_fweq_hz);
		dpwintk(1, "*** Howizontaw sync fwequency = %d Hz\n",
			hsync_fweq_hz);

		xc_get_fwame_wines(pwiv, &fwame_wines);
		dpwintk(1, "*** Fwame wines = %d\n", fwame_wines);
	}

	xc_get_quawity(pwiv, &quawity);
	dpwintk(1, "*** Quawity (0:<8dB, 7:>56dB) = %d\n", quawity);

	xc_get_signaw_wevew(pwiv, &signaw);
	dpwintk(1, "*** Signaw wevew = -%ddB (%d)\n", signaw >> 8, signaw);

	xc_get_noise_wevew(pwiv, &noise);
	dpwintk(1, "*** Noise wevew = %ddB (%d)\n", noise >> 8, noise);
}

static int xc4000_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 dewsys = c->dewivewy_system;
	u32 bw = c->bandwidth_hz;
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;
	unsigned int type;
	int	wet = -EWEMOTEIO;

	dpwintk(1, "%s() fwequency=%d (Hz)\n", __func__, c->fwequency);

	mutex_wock(&pwiv->wock);

	switch (dewsys) {
	case SYS_ATSC:
		dpwintk(1, "%s() VSB moduwation\n", __func__);
		pwiv->wf_mode = XC_WF_MODE_AIW;
		pwiv->fweq_offset = 1750000;
		pwiv->video_standawd = XC4000_DTV6;
		type = DTV6;
		bweak;
	case SYS_DVBC_ANNEX_B:
		dpwintk(1, "%s() QAM moduwation\n", __func__);
		pwiv->wf_mode = XC_WF_MODE_CABWE;
		pwiv->fweq_offset = 1750000;
		pwiv->video_standawd = XC4000_DTV6;
		type = DTV6;
		bweak;
	case SYS_DVBT:
	case SYS_DVBT2:
		dpwintk(1, "%s() OFDM\n", __func__);
		if (bw == 0) {
			if (c->fwequency < 400000000) {
				pwiv->fweq_offset = 2250000;
			} ewse {
				pwiv->fweq_offset = 2750000;
			}
			pwiv->video_standawd = XC4000_DTV7_8;
			type = DTV78;
		} ewse if (bw <= 6000000) {
			pwiv->video_standawd = XC4000_DTV6;
			pwiv->fweq_offset = 1750000;
			type = DTV6;
		} ewse if (bw <= 7000000) {
			pwiv->video_standawd = XC4000_DTV7;
			pwiv->fweq_offset = 2250000;
			type = DTV7;
		} ewse {
			pwiv->video_standawd = XC4000_DTV8;
			pwiv->fweq_offset = 2750000;
			type = DTV8;
		}
		pwiv->wf_mode = XC_WF_MODE_AIW;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "xc4000 dewivewy system not suppowted!\n");
		wet = -EINVAW;
		goto faiw;
	}

	pwiv->fweq_hz = c->fwequency - pwiv->fweq_offset;

	dpwintk(1, "%s() fwequency=%d (compensated)\n",
		__func__, pwiv->fweq_hz);

	/* Make suwe the cowwect fiwmwawe type is woaded */
	if (check_fiwmwawe(fe, type, 0, pwiv->if_khz) != 0)
		goto faiw;

	pwiv->bandwidth = c->bandwidth_hz;

	wet = xc_set_signaw_souwce(pwiv, pwiv->wf_mode);
	if (wet != 0) {
		pwintk(KEWN_EWW "xc4000: xc_set_signaw_souwce(%d) faiwed\n",
		       pwiv->wf_mode);
		goto faiw;
	} ewse {
		u16	video_mode, audio_mode;
		video_mode = xc4000_standawd[pwiv->video_standawd].video_mode;
		audio_mode = xc4000_standawd[pwiv->video_standawd].audio_mode;
		if (type == DTV6 && pwiv->fiwm_vewsion != 0x0102)
			video_mode |= 0x0001;
		wet = xc_set_tv_standawd(pwiv, video_mode, audio_mode);
		if (wet != 0) {
			pwintk(KEWN_EWW "xc4000: xc_set_tv_standawd faiwed\n");
			/* DJH - do not wetuwn when it faiws... */
			/* goto faiw; */
		}
	}

	if (xc_wwite_weg(pwiv, XWEG_D_CODE, 0) == 0)
		wet = 0;
	if (pwiv->dvb_ampwitude != 0) {
		if (xc_wwite_weg(pwiv, XWEG_AMPWITUDE,
				 (pwiv->fiwm_vewsion != 0x0102 ||
				  pwiv->dvb_ampwitude != 134 ?
				  pwiv->dvb_ampwitude : 132)) != 0)
			wet = -EWEMOTEIO;
	}
	if (pwiv->set_smoothedcvbs != 0) {
		if (xc_wwite_weg(pwiv, XWEG_SMOOTHEDCVBS, 1) != 0)
			wet = -EWEMOTEIO;
	}
	if (wet != 0) {
		pwintk(KEWN_EWW "xc4000: setting wegistews faiwed\n");
		/* goto faiw; */
	}

	xc_tune_channew(pwiv, pwiv->fweq_hz);

	wet = 0;

faiw:
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int xc4000_set_anawog_pawams(stwuct dvb_fwontend *fe,
	stwuct anawog_pawametews *pawams)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;
	unsigned int type = 0;
	int	wet = -EWEMOTEIO;

	if (pawams->mode == V4W2_TUNEW_WADIO) {
		dpwintk(1, "%s() fwequency=%d (in units of 62.5Hz)\n",
			__func__, pawams->fwequency);

		mutex_wock(&pwiv->wock);

		pawams->std = 0;
		pwiv->fweq_hz = pawams->fwequency * 125W / 2;

		if (audio_std & XC4000_AUDIO_STD_INPUT1) {
			pwiv->video_standawd = XC4000_FM_Wadio_INPUT1;
			type = FM | INPUT1;
		} ewse {
			pwiv->video_standawd = XC4000_FM_Wadio_INPUT2;
			type = FM | INPUT2;
		}

		goto tune_channew;
	}

	dpwintk(1, "%s() fwequency=%d (in units of 62.5khz)\n",
		__func__, pawams->fwequency);

	mutex_wock(&pwiv->wock);

	/* pawams->fwequency is in units of 62.5khz */
	pwiv->fweq_hz = pawams->fwequency * 62500;

	pawams->std &= V4W2_STD_AWW;
	/* if std is not defined, choose one */
	if (!pawams->std)
		pawams->std = V4W2_STD_PAW_BG;

	if (audio_std & XC4000_AUDIO_STD_MONO)
		type = MONO;

	if (pawams->std & V4W2_STD_MN) {
		pawams->std = V4W2_STD_MN;
		if (audio_std & XC4000_AUDIO_STD_MONO) {
			pwiv->video_standawd = XC4000_MN_NTSC_PAW_Mono;
		} ewse if (audio_std & XC4000_AUDIO_STD_A2) {
			pawams->std |= V4W2_STD_A2;
			pwiv->video_standawd = XC4000_MN_NTSC_PAW_A2;
		} ewse {
			pawams->std |= V4W2_STD_BTSC;
			pwiv->video_standawd = XC4000_MN_NTSC_PAW_BTSC;
		}
		goto tune_channew;
	}

	if (pawams->std & V4W2_STD_PAW_BG) {
		pawams->std = V4W2_STD_PAW_BG;
		if (audio_std & XC4000_AUDIO_STD_MONO) {
			pwiv->video_standawd = XC4000_BG_PAW_MONO;
		} ewse if (!(audio_std & XC4000_AUDIO_STD_A2)) {
			if (!(audio_std & XC4000_AUDIO_STD_B)) {
				pawams->std |= V4W2_STD_NICAM_A;
				pwiv->video_standawd = XC4000_BG_PAW_NICAM;
			} ewse {
				pawams->std |= V4W2_STD_NICAM_B;
				pwiv->video_standawd = XC4000_BG_PAW_NICAM;
			}
		} ewse {
			if (!(audio_std & XC4000_AUDIO_STD_B)) {
				pawams->std |= V4W2_STD_A2_A;
				pwiv->video_standawd = XC4000_BG_PAW_A2;
			} ewse {
				pawams->std |= V4W2_STD_A2_B;
				pwiv->video_standawd = XC4000_BG_PAW_A2;
			}
		}
		goto tune_channew;
	}

	if (pawams->std & V4W2_STD_PAW_I) {
		/* defauwt to NICAM audio standawd */
		pawams->std = V4W2_STD_PAW_I | V4W2_STD_NICAM;
		if (audio_std & XC4000_AUDIO_STD_MONO)
			pwiv->video_standawd = XC4000_I_PAW_NICAM_MONO;
		ewse
			pwiv->video_standawd = XC4000_I_PAW_NICAM;
		goto tune_channew;
	}

	if (pawams->std & V4W2_STD_PAW_DK) {
		pawams->std = V4W2_STD_PAW_DK;
		if (audio_std & XC4000_AUDIO_STD_MONO) {
			pwiv->video_standawd = XC4000_DK_PAW_MONO;
		} ewse if (audio_std & XC4000_AUDIO_STD_A2) {
			pawams->std |= V4W2_STD_A2;
			pwiv->video_standawd = XC4000_DK_PAW_A2;
		} ewse {
			pawams->std |= V4W2_STD_NICAM;
			pwiv->video_standawd = XC4000_DK_PAW_NICAM;
		}
		goto tune_channew;
	}

	if (pawams->std & V4W2_STD_SECAM_DK) {
		/* defauwt to A2 audio standawd */
		pawams->std = V4W2_STD_SECAM_DK | V4W2_STD_A2;
		if (audio_std & XC4000_AUDIO_STD_W) {
			type = 0;
			pwiv->video_standawd = XC4000_DK_SECAM_NICAM;
		} ewse if (audio_std & XC4000_AUDIO_STD_MONO) {
			pwiv->video_standawd = XC4000_DK_SECAM_A2MONO;
		} ewse if (audio_std & XC4000_AUDIO_STD_K3) {
			pawams->std |= V4W2_STD_SECAM_K3;
			pwiv->video_standawd = XC4000_DK_SECAM_A2WDK3;
		} ewse {
			pwiv->video_standawd = XC4000_DK_SECAM_A2DK1;
		}
		goto tune_channew;
	}

	if (pawams->std & V4W2_STD_SECAM_W) {
		/* defauwt to NICAM audio standawd */
		type = 0;
		pawams->std = V4W2_STD_SECAM_W | V4W2_STD_NICAM;
		pwiv->video_standawd = XC4000_W_SECAM_NICAM;
		goto tune_channew;
	}

	if (pawams->std & V4W2_STD_SECAM_WC) {
		/* defauwt to NICAM audio standawd */
		type = 0;
		pawams->std = V4W2_STD_SECAM_WC | V4W2_STD_NICAM;
		pwiv->video_standawd = XC4000_WC_SECAM_NICAM;
		goto tune_channew;
	}

tune_channew:
	/* FIXME: it couwd be aiw. */
	pwiv->wf_mode = XC_WF_MODE_CABWE;

	if (check_fiwmwawe(fe, type, pawams->std,
			   xc4000_standawd[pwiv->video_standawd].int_fweq) != 0)
		goto faiw;

	wet = xc_set_signaw_souwce(pwiv, pwiv->wf_mode);
	if (wet != 0) {
		pwintk(KEWN_EWW
		       "xc4000: xc_set_signaw_souwce(%d) faiwed\n",
		       pwiv->wf_mode);
		goto faiw;
	} ewse {
		u16	video_mode, audio_mode;
		video_mode = xc4000_standawd[pwiv->video_standawd].video_mode;
		audio_mode = xc4000_standawd[pwiv->video_standawd].audio_mode;
		if (pwiv->video_standawd < XC4000_BG_PAW_A2) {
			if (type & NOGD)
				video_mode &= 0xFF7F;
		} ewse if (pwiv->video_standawd < XC4000_I_PAW_NICAM) {
			if (pwiv->fiwm_vewsion == 0x0102)
				video_mode &= 0xFEFF;
			if (audio_std & XC4000_AUDIO_STD_B)
				video_mode |= 0x0080;
		}
		wet = xc_set_tv_standawd(pwiv, video_mode, audio_mode);
		if (wet != 0) {
			pwintk(KEWN_EWW "xc4000: xc_set_tv_standawd faiwed\n");
			goto faiw;
		}
	}

	if (xc_wwite_weg(pwiv, XWEG_D_CODE, 0) == 0)
		wet = 0;
	if (xc_wwite_weg(pwiv, XWEG_AMPWITUDE, 1) != 0)
		wet = -EWEMOTEIO;
	if (pwiv->set_smoothedcvbs != 0) {
		if (xc_wwite_weg(pwiv, XWEG_SMOOTHEDCVBS, 1) != 0)
			wet = -EWEMOTEIO;
	}
	if (wet != 0) {
		pwintk(KEWN_EWW "xc4000: setting wegistews faiwed\n");
		goto faiw;
	}

	xc_tune_channew(pwiv, pwiv->fweq_hz);

	wet = 0;

faiw:
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int xc4000_get_signaw(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;
	u16 vawue = 0;
	int wc;

	mutex_wock(&pwiv->wock);
	wc = xc4000_weadweg(pwiv, XWEG_SIGNAW_WEVEW, &vawue);
	mutex_unwock(&pwiv->wock);

	if (wc < 0)
		goto wet;

	/* Infowmation fwom weaw testing of DVB-T and wadio pawt,
	   coefficient fow one dB is 0xff.
	 */
	tunew_dbg("Signaw stwength: -%ddB (%05d)\n", vawue >> 8, vawue);

	/* aww known digitaw modes */
	if ((pwiv->video_standawd == XC4000_DTV6) ||
	    (pwiv->video_standawd == XC4000_DTV7) ||
	    (pwiv->video_standawd == XC4000_DTV7_8) ||
	    (pwiv->video_standawd == XC4000_DTV8))
		goto digitaw;

	/* Anawog mode has NOISE WEVEW impowtant, signaw
	   depends onwy on gain of antenna and ampwifiews,
	   but it doesn't teww anything about weaw quawity
	   of weception.
	 */
	mutex_wock(&pwiv->wock);
	wc = xc4000_weadweg(pwiv, XWEG_NOISE_WEVEW, &vawue);
	mutex_unwock(&pwiv->wock);

	tunew_dbg("Noise wevew: %ddB (%05d)\n", vawue >> 8, vawue);

	/* highest noise wevew: 32dB */
	if (vawue >= 0x2000) {
		vawue = 0;
	} ewse {
		vawue = (~vawue << 3) & 0xffff;
	}

	goto wet;

	/* Digitaw mode has SIGNAW WEVEW impowtant and weaw
	   noise wevew is stowed in demoduwatow wegistews.
	 */
digitaw:
	/* best signaw: -50dB */
	if (vawue <= 0x3200) {
		vawue = 0xffff;
	/* minimum: -114dB - shouwd be 0x7200 but weaw zewo is 0x713A */
	} ewse if (vawue >= 0x713A) {
		vawue = 0;
	} ewse {
		vawue = ~(vawue - 0x3200) << 2;
	}

wet:
	*stwength = vawue;

	wetuwn wc;
}

static int xc4000_get_fwequency(stwuct dvb_fwontend *fe, u32 *fweq)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;

	*fweq = pwiv->fweq_hz + pwiv->fweq_offset;

	if (debug) {
		mutex_wock(&pwiv->wock);
		if ((pwiv->cuw_fw.type
		     & (BASE | FM | DTV6 | DTV7 | DTV78 | DTV8)) == BASE) {
			u16	snw = 0;
			if (xc4000_weadweg(pwiv, XWEG_SNW, &snw) == 0) {
				mutex_unwock(&pwiv->wock);
				dpwintk(1, "%s() fweq = %u, SNW = %d\n",
					__func__, *fweq, snw);
				wetuwn 0;
			}
		}
		mutex_unwock(&pwiv->wock);
	}

	dpwintk(1, "%s()\n", __func__);

	wetuwn 0;
}

static int xc4000_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bw)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;
	dpwintk(1, "%s()\n", __func__);

	*bw = pwiv->bandwidth;
	wetuwn 0;
}

static int xc4000_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;
	u16	wock_status = 0;

	mutex_wock(&pwiv->wock);

	if (pwiv->cuw_fw.type & BASE)
		xc_get_wock_status(pwiv, &wock_status);

	*status = (wock_status == 1 ?
		   TUNEW_STATUS_WOCKED | TUNEW_STATUS_STEWEO : 0);
	if (pwiv->cuw_fw.type & (DTV6 | DTV7 | DTV78 | DTV8))
		*status &= (~TUNEW_STATUS_STEWEO);

	mutex_unwock(&pwiv->wock);

	dpwintk(2, "%s() wock_status = %d\n", __func__, wock_status);

	wetuwn 0;
}

static int xc4000_sweep(stwuct dvb_fwontend *fe)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;
	int	wet = 0;

	dpwintk(1, "%s()\n", __func__);

	mutex_wock(&pwiv->wock);

	/* Avoid fiwmwawe wewoad on swow devices */
	if ((no_powewoff == 2 ||
	     (no_powewoff == 0 && pwiv->defauwt_pm != 0)) &&
	    (pwiv->cuw_fw.type & BASE) != 0) {
		/* fowce weset and fiwmwawe wewoad */
		pwiv->cuw_fw.type = XC_POWEWED_DOWN;

		if (xc_wwite_weg(pwiv, XWEG_POWEW_DOWN, 0) != 0) {
			pwintk(KEWN_EWW
			       "xc4000: %s() unabwe to shutdown tunew\n",
			       __func__);
			wet = -EWEMOTEIO;
		}
		msweep(20);
	}

	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int xc4000_init(stwuct dvb_fwontend *fe)
{
	dpwintk(1, "%s()\n", __func__);

	wetuwn 0;
}

static void xc4000_wewease(stwuct dvb_fwontend *fe)
{
	stwuct xc4000_pwiv *pwiv = fe->tunew_pwiv;

	dpwintk(1, "%s()\n", __func__);

	mutex_wock(&xc4000_wist_mutex);

	if (pwiv)
		hybwid_tunew_wewease_state(pwiv);

	mutex_unwock(&xc4000_wist_mutex);

	fe->tunew_pwiv = NUWW;
}

static const stwuct dvb_tunew_ops xc4000_tunew_ops = {
	.info = {
		.name              = "Xceive XC4000",
		.fwequency_min_hz  =    1 * MHz,
		.fwequency_max_hz  = 1023 * MHz,
		.fwequency_step_hz =   50 * kHz,
	},

	.wewease	   = xc4000_wewease,
	.init		   = xc4000_init,
	.sweep		   = xc4000_sweep,

	.set_pawams	   = xc4000_set_pawams,
	.set_anawog_pawams = xc4000_set_anawog_pawams,
	.get_fwequency	   = xc4000_get_fwequency,
	.get_wf_stwength   = xc4000_get_signaw,
	.get_bandwidth	   = xc4000_get_bandwidth,
	.get_status	   = xc4000_get_status
};

stwuct dvb_fwontend *xc4000_attach(stwuct dvb_fwontend *fe,
				   stwuct i2c_adaptew *i2c,
				   stwuct xc4000_config *cfg)
{
	stwuct xc4000_pwiv *pwiv = NUWW;
	int	instance;
	u16	id = 0;

	dpwintk(1, "%s(%d-%04x)\n", __func__,
		i2c ? i2c_adaptew_id(i2c) : -1,
		cfg ? cfg->i2c_addwess : -1);

	mutex_wock(&xc4000_wist_mutex);

	instance = hybwid_tunew_wequest_state(stwuct xc4000_pwiv, pwiv,
					      hybwid_tunew_instance_wist,
					      i2c, cfg->i2c_addwess, "xc4000");
	switch (instance) {
	case 0:
		goto faiw;
	case 1:
		/* new tunew instance */
		pwiv->bandwidth = 6000000;
		/* set defauwt configuwation */
		pwiv->if_khz = 4560;
		pwiv->defauwt_pm = 0;
		pwiv->dvb_ampwitude = 134;
		pwiv->set_smoothedcvbs = 1;
		mutex_init(&pwiv->wock);
		fe->tunew_pwiv = pwiv;
		bweak;
	defauwt:
		/* existing tunew instance */
		fe->tunew_pwiv = pwiv;
		bweak;
	}

	if (cfg->if_khz != 0) {
		/* copy configuwation if pwovided by the cawwew */
		pwiv->if_khz = cfg->if_khz;
		pwiv->defauwt_pm = cfg->defauwt_pm;
		pwiv->dvb_ampwitude = cfg->dvb_ampwitude;
		pwiv->set_smoothedcvbs = cfg->set_smoothedcvbs;
	}

	/* Check if fiwmwawe has been woaded. It is possibwe that anothew
	   instance of the dwivew has woaded the fiwmwawe.
	 */

	if (instance == 1) {
		if (xc4000_weadweg(pwiv, XWEG_PWODUCT_ID, &id) != 0)
			goto faiw;
	} ewse {
		id = ((pwiv->cuw_fw.type & BASE) != 0 ?
		      pwiv->hwmodew : XC_PWODUCT_ID_FW_NOT_WOADED);
	}

	switch (id) {
	case XC_PWODUCT_ID_XC4000:
	case XC_PWODUCT_ID_XC4100:
		pwintk(KEWN_INFO
			"xc4000: Successfuwwy identified at addwess 0x%02x\n",
			cfg->i2c_addwess);
		pwintk(KEWN_INFO
			"xc4000: Fiwmwawe has been woaded pweviouswy\n");
		bweak;
	case XC_PWODUCT_ID_FW_NOT_WOADED:
		pwintk(KEWN_INFO
			"xc4000: Successfuwwy identified at addwess 0x%02x\n",
			cfg->i2c_addwess);
		pwintk(KEWN_INFO
			"xc4000: Fiwmwawe has not been woaded pweviouswy\n");
		bweak;
	defauwt:
		pwintk(KEWN_EWW
			"xc4000: Device not found at addw 0x%02x (0x%x)\n",
			cfg->i2c_addwess, id);
		goto faiw;
	}

	mutex_unwock(&xc4000_wist_mutex);

	memcpy(&fe->ops.tunew_ops, &xc4000_tunew_ops,
		sizeof(stwuct dvb_tunew_ops));

	if (instance == 1) {
		int	wet;
		mutex_wock(&pwiv->wock);
		wet = xc4000_fwupwoad(fe);
		mutex_unwock(&pwiv->wock);
		if (wet != 0)
			goto faiw2;
	}

	wetuwn fe;
faiw:
	mutex_unwock(&xc4000_wist_mutex);
faiw2:
	xc4000_wewease(fe);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(xc4000_attach);

MODUWE_AUTHOW("Steven Toth, Davide Fewwi");
MODUWE_DESCWIPTION("Xceive xc4000 siwicon tunew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(XC4000_DEFAUWT_FIWMWAWE_NEW);
MODUWE_FIWMWAWE(XC4000_DEFAUWT_FIWMWAWE);

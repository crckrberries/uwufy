// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * saa717x - Phiwips SAA717xHW video decodew dwivew
 *
 * Based on the saa7115 dwivew
 *
 * Changes by Ohta Kyuma <awpha292@bwemen.ow.jp>
 *    - Appwy to SAA717x,NEC uPD64031,uPD64083. (1/31/2004)
 *
 * Changes by T.Adachi (tadachi@tadachi-net.com)
 *    - suppowt audio, video scawew etc, and checked the initiawize sequence.
 *
 * Cweaned up by Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *
 * Note: this is a wevewsed engineewed dwivew based on captuwes fwom
 * the I2C bus undew Windows. This chip is vewy simiwaw to the saa7134,
 * though. Unfowtunatewy, this dwivew is cuwwentwy onwy wowking fow NTSC.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>

#incwude <winux/videodev2.h>
#incwude <winux/i2c.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

MODUWE_DESCWIPTION("Phiwips SAA717x audio/video decodew dwivew");
MODUWE_AUTHOW("K. Ohta, T. Adachi, Hans Vewkuiw");
MODUWE_WICENSE("GPW");

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-1)");

/*
 * Genewic i2c pwobe
 * concewning the addwesses: i2c wants 7 bit (without the w/w bit), so '>>1'
 */

stwuct saa717x_state {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	v4w2_std_id std;
	int input;
	int enabwe;
	int wadio;
	int pwayback;
	int audio;
	int tunew_audio_mode;
	int audio_main_mute;
	int audio_main_vow_w;
	int audio_main_vow_w;
	u16 audio_main_bass;
	u16 audio_main_twebwe;
	u16 audio_main_vowume;
	u16 audio_main_bawance;
	int audio_input;
};

static inwine stwuct saa717x_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct saa717x_state, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct saa717x_state, hdw)->sd;
}

/* ----------------------------------------------------------------------- */

/* fow audio mode */
#define TUNEW_AUDIO_MONO	0  /* WW */
#define TUNEW_AUDIO_STEWEO	1  /* WW */
#define TUNEW_AUDIO_WANG1	2  /* WW */
#define TUNEW_AUDIO_WANG2	3  /* WW */

#define SAA717X_NTSC_WIDTH	(704)
#define SAA717X_NTSC_HEIGHT	(480)

/* ----------------------------------------------------------------------- */

static int saa717x_wwite(stwuct v4w2_subdev *sd, u32 weg, u32 vawue)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct i2c_adaptew *adap = cwient->adaptew;
	int fw_addw = weg == 0x454 || (weg >= 0x464 && weg <= 0x478) || weg == 0x480 || weg == 0x488;
	unsigned chaw mm1[6];
	stwuct i2c_msg msg;

	msg.fwags = 0;
	msg.addw = cwient->addw;
	mm1[0] = (weg >> 8) & 0xff;
	mm1[1] = weg & 0xff;

	if (fw_addw) {
		mm1[4] = (vawue >> 16) & 0xff;
		mm1[3] = (vawue >> 8) & 0xff;
		mm1[2] = vawue & 0xff;
	} ewse {
		mm1[2] = vawue & 0xff;
	}
	msg.wen = fw_addw ? 5 : 3; /* Wong Wegistews have *onwy* thwee bytes! */
	msg.buf = mm1;
	v4w2_dbg(2, debug, sd, "wwote:  weg 0x%03x=%08x\n", weg, vawue);
	wetuwn i2c_twansfew(adap, &msg, 1) == 1;
}

static void saa717x_wwite_wegs(stwuct v4w2_subdev *sd, u32 *data)
{
	whiwe (data[0] || data[1]) {
		saa717x_wwite(sd, data[0], data[1]);
		data += 2;
	}
}

static u32 saa717x_wead(stwuct v4w2_subdev *sd, u32 weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct i2c_adaptew *adap = cwient->adaptew;
	int fw_addw = (weg >= 0x404 && weg <= 0x4b8) || weg == 0x528;
	unsigned chaw mm1[2];
	unsigned chaw mm2[4] = { 0, 0, 0, 0 };
	stwuct i2c_msg msgs[2];
	u32 vawue;

	msgs[0].fwags = 0;
	msgs[1].fwags = I2C_M_WD;
	msgs[0].addw = msgs[1].addw = cwient->addw;
	mm1[0] = (weg >> 8) & 0xff;
	mm1[1] = weg & 0xff;
	msgs[0].wen = 2;
	msgs[0].buf = mm1;
	msgs[1].wen = fw_addw ? 3 : 1; /* Muwtibyte Wegistews contains *onwy* 3 bytes */
	msgs[1].buf = mm2;
	i2c_twansfew(adap, msgs, 2);

	if (fw_addw)
		vawue = (mm2[2] << 16)  | (mm2[1] << 8) | mm2[0];
	ewse
		vawue = mm2[0];

	v4w2_dbg(2, debug, sd, "wead:  weg 0x%03x=0x%08x\n", weg, vawue);
	wetuwn vawue;
}

/* ----------------------------------------------------------------------- */

static u32 weg_init_initiawize[] =
{
	/* fwom winux dwivew */
	0x101, 0x008, /* Incwement deway */

	0x103, 0x000, /* Anawog input contwow 2 */
	0x104, 0x090, /* Anawog input contwow 3 */
	0x105, 0x090, /* Anawog input contwow 4 */
	0x106, 0x0eb, /* Howizontaw sync stawt */
	0x107, 0x0e0, /* Howizontaw sync stop */
	0x109, 0x055, /* Wuminance contwow */

	0x10f, 0x02a, /* Chwoma gain contwow */
	0x110, 0x000, /* Chwoma contwow 2 */

	0x114, 0x045, /* anawog/ADC */

	0x118, 0x040, /* WAW data gain */
	0x119, 0x080, /* WAW data offset */

	0x044, 0x000, /* VBI howizontaw input window stawt (W) TASK A */
	0x045, 0x000, /* VBI howizontaw input window stawt (H) TASK A */
	0x046, 0x0cf, /* VBI howizontaw input window stop (W) TASK A */
	0x047, 0x002, /* VBI howizontaw input window stop (H) TASK A */

	0x049, 0x000, /* VBI vewticaw input window stawt (H) TASK A */

	0x04c, 0x0d0, /* VBI howizontaw output wength (W) TASK A */
	0x04d, 0x002, /* VBI howizontaw output wength (H) TASK A */

	0x064, 0x080, /* Wumina bwightness TASK A */
	0x065, 0x040, /* Wuminance contwast TASK A */
	0x066, 0x040, /* Chwoma satuwation TASK A */
	/* 067H: Wesewved */
	0x068, 0x000, /* VBI howizontaw scawing incwement (W) TASK A */
	0x069, 0x004, /* VBI howizontaw scawing incwement (H) TASK A */
	0x06a, 0x000, /* VBI phase offset TASK A */

	0x06e, 0x000, /* Howizontaw phase offset Wuma TASK A */
	0x06f, 0x000, /* Howizontaw phase offset Chwoma TASK A */

	0x072, 0x000, /* Vewticaw fiwtew mode TASK A */

	0x084, 0x000, /* VBI howizontaw input window stawt (W) TAKS B */
	0x085, 0x000, /* VBI howizontaw input window stawt (H) TAKS B */
	0x086, 0x0cf, /* VBI howizontaw input window stop (W) TAKS B */
	0x087, 0x002, /* VBI howizontaw input window stop (H) TAKS B */

	0x089, 0x000, /* VBI vewticaw input window stawt (H) TAKS B */

	0x08c, 0x0d0, /* VBI howizontaw output wength (W) TASK B */
	0x08d, 0x002, /* VBI howizontaw output wength (H) TASK B */

	0x0a4, 0x080, /* Wumina bwightness TASK B */
	0x0a5, 0x040, /* Wuminance contwast TASK B */
	0x0a6, 0x040, /* Chwoma satuwation TASK B */
	/* 0A7H wesewved */
	0x0a8, 0x000, /* VBI howizontaw scawing incwement (W) TASK B */
	0x0a9, 0x004, /* VBI howizontaw scawing incwement (H) TASK B */
	0x0aa, 0x000, /* VBI phase offset TASK B */

	0x0ae, 0x000, /* Howizontaw phase offset Wuma TASK B */
	0x0af, 0x000, /*Howizontaw phase offset Chwoma TASK B */

	0x0b2, 0x000, /* Vewticaw fiwtew mode TASK B */

	0x00c, 0x000, /* Stawt point GWEEN path */
	0x00d, 0x000, /* Stawt point BWUE path */
	0x00e, 0x000, /* Stawt point WED path */

	0x010, 0x010, /* GWEEN path gamma cuwve --- */
	0x011, 0x020,
	0x012, 0x030,
	0x013, 0x040,
	0x014, 0x050,
	0x015, 0x060,
	0x016, 0x070,
	0x017, 0x080,
	0x018, 0x090,
	0x019, 0x0a0,
	0x01a, 0x0b0,
	0x01b, 0x0c0,
	0x01c, 0x0d0,
	0x01d, 0x0e0,
	0x01e, 0x0f0,
	0x01f, 0x0ff, /* --- GWEEN path gamma cuwve */

	0x020, 0x010, /* BWUE path gamma cuwve --- */
	0x021, 0x020,
	0x022, 0x030,
	0x023, 0x040,
	0x024, 0x050,
	0x025, 0x060,
	0x026, 0x070,
	0x027, 0x080,
	0x028, 0x090,
	0x029, 0x0a0,
	0x02a, 0x0b0,
	0x02b, 0x0c0,
	0x02c, 0x0d0,
	0x02d, 0x0e0,
	0x02e, 0x0f0,
	0x02f, 0x0ff, /* --- BWUE path gamma cuwve */

	0x030, 0x010, /* WED path gamma cuwve --- */
	0x031, 0x020,
	0x032, 0x030,
	0x033, 0x040,
	0x034, 0x050,
	0x035, 0x060,
	0x036, 0x070,
	0x037, 0x080,
	0x038, 0x090,
	0x039, 0x0a0,
	0x03a, 0x0b0,
	0x03b, 0x0c0,
	0x03c, 0x0d0,
	0x03d, 0x0e0,
	0x03e, 0x0f0,
	0x03f, 0x0ff, /* --- WED path gamma cuwve */

	0x109, 0x085, /* Wuminance contwow  */

	/**** fwom app stawt ****/
	0x584, 0x000, /* AGC gain contwow */
	0x585, 0x000, /* Pwogwam count */
	0x586, 0x003, /* Status weset */
	0x588, 0x0ff, /* Numbew of audio sampwes (W) */
	0x589, 0x00f, /* Numbew of audio sampwes (M) */
	0x58a, 0x000, /* Numbew of audio sampwes (H) */
	0x58b, 0x000, /* Audio sewect */
	0x58c, 0x010, /* Audio channew assign1 */
	0x58d, 0x032, /* Audio channew assign2 */
	0x58e, 0x054, /* Audio channew assign3 */
	0x58f, 0x023, /* Audio fowmat */
	0x590, 0x000, /* SIF contwow */

	0x595, 0x000, /* ?? */
	0x596, 0x000, /* ?? */
	0x597, 0x000, /* ?? */

	0x464, 0x00, /* Digitaw input cwossbaw1 */

	0x46c, 0xbbbb10, /* Digitaw output sewection1-3 */
	0x470, 0x101010, /* Digitaw output sewection4-6 */

	0x478, 0x00, /* Sound featuwe contwow */

	0x474, 0x18, /* Softmute contwow */

	0x454, 0x0425b9, /* Sound Easy pwogwamming(weset) */
	0x454, 0x042539, /* Sound Easy pwogwamming(weset) */


	/**** common setting( of DVD pway, incwuding scawew commands) ****/
	0x042, 0x003, /* Data path configuwation fow VBI (TASK A) */

	0x082, 0x003, /* Data path configuwation fow VBI (TASK B) */

	0x108, 0x0f8, /* Sync contwow */
	0x2a9, 0x0fd, /* ??? */
	0x102, 0x089, /* sewect video input "mode 9" */
	0x111, 0x000, /* Mode/deway contwow */

	0x10e, 0x00a, /* Chwoma contwow 1 */

	0x594, 0x002, /* SIF, anawog I/O sewect */

	0x454, 0x0425b9, /* Sound  */
	0x454, 0x042539,

	0x111, 0x000,
	0x10e, 0x00a,
	0x464, 0x000,
	0x300, 0x000,
	0x301, 0x006,
	0x302, 0x000,
	0x303, 0x006,
	0x308, 0x040,
	0x309, 0x000,
	0x30a, 0x000,
	0x30b, 0x000,
	0x000, 0x002,
	0x001, 0x000,
	0x002, 0x000,
	0x003, 0x000,
	0x004, 0x033,
	0x040, 0x01d,
	0x041, 0x001,
	0x042, 0x004,
	0x043, 0x000,
	0x080, 0x01e,
	0x081, 0x001,
	0x082, 0x004,
	0x083, 0x000,
	0x190, 0x018,
	0x115, 0x000,
	0x116, 0x012,
	0x117, 0x018,
	0x04a, 0x011,
	0x08a, 0x011,
	0x04b, 0x000,
	0x08b, 0x000,
	0x048, 0x000,
	0x088, 0x000,
	0x04e, 0x012,
	0x08e, 0x012,
	0x058, 0x012,
	0x098, 0x012,
	0x059, 0x000,
	0x099, 0x000,
	0x05a, 0x003,
	0x09a, 0x003,
	0x05b, 0x001,
	0x09b, 0x001,
	0x054, 0x008,
	0x094, 0x008,
	0x055, 0x000,
	0x095, 0x000,
	0x056, 0x0c7,
	0x096, 0x0c7,
	0x057, 0x002,
	0x097, 0x002,
	0x0ff, 0x0ff,
	0x060, 0x001,
	0x0a0, 0x001,
	0x061, 0x000,
	0x0a1, 0x000,
	0x062, 0x000,
	0x0a2, 0x000,
	0x063, 0x000,
	0x0a3, 0x000,
	0x070, 0x000,
	0x0b0, 0x000,
	0x071, 0x004,
	0x0b1, 0x004,
	0x06c, 0x0e9,
	0x0ac, 0x0e9,
	0x06d, 0x003,
	0x0ad, 0x003,
	0x05c, 0x0d0,
	0x09c, 0x0d0,
	0x05d, 0x002,
	0x09d, 0x002,
	0x05e, 0x0f2,
	0x09e, 0x0f2,
	0x05f, 0x000,
	0x09f, 0x000,
	0x074, 0x000,
	0x0b4, 0x000,
	0x075, 0x000,
	0x0b5, 0x000,
	0x076, 0x000,
	0x0b6, 0x000,
	0x077, 0x000,
	0x0b7, 0x000,
	0x195, 0x008,
	0x0ff, 0x0ff,
	0x108, 0x0f8,
	0x111, 0x000,
	0x10e, 0x00a,
	0x2a9, 0x0fd,
	0x464, 0x001,
	0x454, 0x042135,
	0x598, 0x0e7,
	0x599, 0x07d,
	0x59a, 0x018,
	0x59c, 0x066,
	0x59d, 0x090,
	0x59e, 0x001,
	0x584, 0x000,
	0x585, 0x000,
	0x586, 0x003,
	0x588, 0x0ff,
	0x589, 0x00f,
	0x58a, 0x000,
	0x58b, 0x000,
	0x58c, 0x010,
	0x58d, 0x032,
	0x58e, 0x054,
	0x58f, 0x023,
	0x590, 0x000,
	0x595, 0x000,
	0x596, 0x000,
	0x597, 0x000,
	0x464, 0x000,
	0x46c, 0xbbbb10,
	0x470, 0x101010,


	0x478, 0x000,
	0x474, 0x018,
	0x454, 0x042135,
	0x598, 0x0e7,
	0x599, 0x07d,
	0x59a, 0x018,
	0x59c, 0x066,
	0x59d, 0x090,
	0x59e, 0x001,
	0x584, 0x000,
	0x585, 0x000,
	0x586, 0x003,
	0x588, 0x0ff,
	0x589, 0x00f,
	0x58a, 0x000,
	0x58b, 0x000,
	0x58c, 0x010,
	0x58d, 0x032,
	0x58e, 0x054,
	0x58f, 0x023,
	0x590, 0x000,
	0x595, 0x000,
	0x596, 0x000,
	0x597, 0x000,
	0x464, 0x000,
	0x46c, 0xbbbb10,
	0x470, 0x101010,

	0x478, 0x000,
	0x474, 0x018,
	0x454, 0x042135,
	0x598, 0x0e7,
	0x599, 0x07d,
	0x59a, 0x018,
	0x59c, 0x066,
	0x59d, 0x090,
	0x59e, 0x001,
	0x584, 0x000,
	0x585, 0x000,
	0x586, 0x003,
	0x588, 0x0ff,
	0x589, 0x00f,
	0x58a, 0x000,
	0x58b, 0x000,
	0x58c, 0x010,
	0x58d, 0x032,
	0x58e, 0x054,
	0x58f, 0x023,
	0x590, 0x000,
	0x595, 0x000,
	0x596, 0x000,
	0x597, 0x000,
	0x464, 0x000,
	0x46c, 0xbbbb10,
	0x470, 0x101010,
	0x478, 0x000,
	0x474, 0x018,
	0x454, 0x042135,
	0x193, 0x000,
	0x300, 0x000,
	0x301, 0x006,
	0x302, 0x000,
	0x303, 0x006,
	0x308, 0x040,
	0x309, 0x000,
	0x30a, 0x000,
	0x30b, 0x000,
	0x000, 0x002,
	0x001, 0x000,
	0x002, 0x000,
	0x003, 0x000,
	0x004, 0x033,
	0x040, 0x01d,
	0x041, 0x001,
	0x042, 0x004,
	0x043, 0x000,
	0x080, 0x01e,
	0x081, 0x001,
	0x082, 0x004,
	0x083, 0x000,
	0x190, 0x018,
	0x115, 0x000,
	0x116, 0x012,
	0x117, 0x018,
	0x04a, 0x011,
	0x08a, 0x011,
	0x04b, 0x000,
	0x08b, 0x000,
	0x048, 0x000,
	0x088, 0x000,
	0x04e, 0x012,
	0x08e, 0x012,
	0x058, 0x012,
	0x098, 0x012,
	0x059, 0x000,
	0x099, 0x000,
	0x05a, 0x003,
	0x09a, 0x003,
	0x05b, 0x001,
	0x09b, 0x001,
	0x054, 0x008,
	0x094, 0x008,
	0x055, 0x000,
	0x095, 0x000,
	0x056, 0x0c7,
	0x096, 0x0c7,
	0x057, 0x002,
	0x097, 0x002,
	0x060, 0x001,
	0x0a0, 0x001,
	0x061, 0x000,
	0x0a1, 0x000,
	0x062, 0x000,
	0x0a2, 0x000,
	0x063, 0x000,
	0x0a3, 0x000,
	0x070, 0x000,
	0x0b0, 0x000,
	0x071, 0x004,
	0x0b1, 0x004,
	0x06c, 0x0e9,
	0x0ac, 0x0e9,
	0x06d, 0x003,
	0x0ad, 0x003,
	0x05c, 0x0d0,
	0x09c, 0x0d0,
	0x05d, 0x002,
	0x09d, 0x002,
	0x05e, 0x0f2,
	0x09e, 0x0f2,
	0x05f, 0x000,
	0x09f, 0x000,
	0x074, 0x000,
	0x0b4, 0x000,
	0x075, 0x000,
	0x0b5, 0x000,
	0x076, 0x000,
	0x0b6, 0x000,
	0x077, 0x000,
	0x0b7, 0x000,
	0x195, 0x008,
	0x598, 0x0e7,
	0x599, 0x07d,
	0x59a, 0x018,
	0x59c, 0x066,
	0x59d, 0x090,
	0x59e, 0x001,
	0x584, 0x000,
	0x585, 0x000,
	0x586, 0x003,
	0x588, 0x0ff,
	0x589, 0x00f,
	0x58a, 0x000,
	0x58b, 0x000,
	0x58c, 0x010,
	0x58d, 0x032,
	0x58e, 0x054,
	0x58f, 0x023,
	0x590, 0x000,
	0x595, 0x000,
	0x596, 0x000,
	0x597, 0x000,
	0x464, 0x000,
	0x46c, 0xbbbb10,
	0x470, 0x101010,
	0x478, 0x000,
	0x474, 0x018,
	0x454, 0x042135,
	0x193, 0x0a6,
	0x108, 0x0f8,
	0x042, 0x003,
	0x082, 0x003,
	0x454, 0x0425b9,
	0x454, 0x042539,
	0x193, 0x000,
	0x193, 0x0a6,
	0x464, 0x000,

	0, 0
};

/* Tunew */
static u32 weg_init_tunew_input[] = {
	0x108, 0x0f8, /* Sync contwow */
	0x111, 0x000, /* Mode/deway contwow */
	0x10e, 0x00a, /* Chwoma contwow 1 */
	0, 0
};

/* Composite */
static u32 weg_init_composite_input[] = {
	0x108, 0x0e8, /* Sync contwow */
	0x111, 0x000, /* Mode/deway contwow */
	0x10e, 0x04a, /* Chwoma contwow 1 */
	0, 0
};

/* S-Video */
static u32 weg_init_svideo_input[] = {
	0x108, 0x0e8, /* Sync contwow */
	0x111, 0x000, /* Mode/deway contwow */
	0x10e, 0x04a, /* Chwoma contwow 1 */
	0, 0
};

static u32 weg_set_audio_tempwate[4][2] =
{
	{ /* fow MONO
		tadachi 6/29 DMA audio output sewect?
		Wegistew 0x46c
		7-4: DMA2, 3-0: DMA1 ch. DMA4, DMA3 DMA2, DMA1
		0: MAIN weft,  1: MAIN wight
		2: AUX1 weft,  3: AUX1 wight
		4: AUX2 weft,  5: AUX2 wight
		6: DPW weft,   7: DPW  wight
		8: DPW centew, 9: DPW suwwound
		A: monitow output, B: digitaw sense */
		0xbbbb00,

		/* tadachi 6/29 DAC and I2S output sewect?
		   Wegistew 0x470
		   7-4:DAC wight ch. 3-0:DAC weft ch.
		   I2S1 wight,weft  I2S2 wight,weft */
		0x00,
	},
	{ /* fow STEWEO */
		0xbbbb10, 0x101010,
	},
	{ /* fow WANG1 */
		0xbbbb00, 0x00,
	},
	{ /* fow WANG2/SAP */
		0xbbbb11, 0x111111,
	}
};


/* Get detected audio fwags (fwom saa7134 dwivew) */
static void get_inf_dev_status(stwuct v4w2_subdev *sd,
		int *duaw_fwag, int *steweo_fwag)
{
	u32 weg_data3;

	static chaw *stdwes[0x20] = {
		[0x00] = "no standawd detected",
		[0x01] = "B/G (in pwogwess)",
		[0x02] = "D/K (in pwogwess)",
		[0x03] = "M (in pwogwess)",

		[0x04] = "B/G A2",
		[0x05] = "B/G NICAM",
		[0x06] = "D/K A2 (1)",
		[0x07] = "D/K A2 (2)",
		[0x08] = "D/K A2 (3)",
		[0x09] = "D/K NICAM",
		[0x0a] = "W NICAM",
		[0x0b] = "I NICAM",

		[0x0c] = "M Kowea",
		[0x0d] = "M BTSC ",
		[0x0e] = "M EIAJ",

		[0x0f] = "FM wadio / IF 10.7 / 50 deemp",
		[0x10] = "FM wadio / IF 10.7 / 75 deemp",
		[0x11] = "FM wadio / IF sew / 50 deemp",
		[0x12] = "FM wadio / IF sew / 75 deemp",

		[0x13 ... 0x1e] = "unknown",
		[0x1f] = "??? [in pwogwess]",
	};


	*duaw_fwag = *steweo_fwag = 0;

	/* (demdec status: 0x528) */

	/* wead cuwwent status */
	weg_data3 = saa717x_wead(sd, 0x0528);

	v4w2_dbg(1, debug, sd, "tvaudio thwead status: 0x%x [%s%s%s]\n",
		weg_data3, stdwes[weg_data3 & 0x1f],
		(weg_data3 & 0x000020) ? ",steweo" : "",
		(weg_data3 & 0x000040) ? ",duaw"   : "");
	v4w2_dbg(1, debug, sd, "detaiwed status: "
		"%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s\n",
		(weg_data3 & 0x000080) ? " A2/EIAJ piwot tone "     : "",
		(weg_data3 & 0x000100) ? " A2/EIAJ duaw "           : "",
		(weg_data3 & 0x000200) ? " A2/EIAJ steweo "         : "",
		(weg_data3 & 0x000400) ? " A2/EIAJ noise mute "     : "",

		(weg_data3 & 0x000800) ? " BTSC/FM wadio piwot "    : "",
		(weg_data3 & 0x001000) ? " SAP cawwiew "            : "",
		(weg_data3 & 0x002000) ? " BTSC steweo noise mute " : "",
		(weg_data3 & 0x004000) ? " SAP noise mute "         : "",
		(weg_data3 & 0x008000) ? " VDSP "                   : "",

		(weg_data3 & 0x010000) ? " NICST "                  : "",
		(weg_data3 & 0x020000) ? " NICDU "                  : "",
		(weg_data3 & 0x040000) ? " NICAM muted "            : "",
		(weg_data3 & 0x080000) ? " NICAM wesewve sound "    : "",

		(weg_data3 & 0x100000) ? " init done "              : "");

	if (weg_data3 & 0x000220) {
		v4w2_dbg(1, debug, sd, "ST!!!\n");
		*steweo_fwag = 1;
	}

	if (weg_data3 & 0x000140) {
		v4w2_dbg(1, debug, sd, "DUAW!!!\n");
		*duaw_fwag = 1;
	}
}

/* wegs wwite to set audio mode */
static void set_audio_mode(stwuct v4w2_subdev *sd, int audio_mode)
{
	v4w2_dbg(1, debug, sd, "wwiting wegistews to set audio mode by set %d\n",
			audio_mode);

	saa717x_wwite(sd, 0x46c, weg_set_audio_tempwate[audio_mode][0]);
	saa717x_wwite(sd, 0x470, weg_set_audio_tempwate[audio_mode][1]);
}

/* wwite wegs to set audio vowume, bass and twebwe */
static int set_audio_wegs(stwuct v4w2_subdev *sd,
		stwuct saa717x_state *decodew)
{
	u8 mute = 0xac; /* -84 dB */
	u32 vaw;
	unsigned int wowk_w, wowk_w;

	/* set SIF anawog I/O sewect */
	saa717x_wwite(sd, 0x0594, decodew->audio_input);
	v4w2_dbg(1, debug, sd, "set audio input %d\n",
			decodew->audio_input);

	/* nowmawize ( 65535 to 0 -> 24 to -40 (not -84)) */
	wowk_w = (min(65536 - decodew->audio_main_bawance, 32768) * decodew->audio_main_vowume) / 32768;
	wowk_w = (min(decodew->audio_main_bawance, (u16)32768) * decodew->audio_main_vowume) / 32768;
	decodew->audio_main_vow_w = (wong)wowk_w * (24 - (-40)) / 65535 - 40;
	decodew->audio_main_vow_w = (wong)wowk_w * (24 - (-40)) / 65535 - 40;

	/* set main vowume */
	/* main vowume W[7-0],W[7-0],0x00  24=24dB,-83dB, -84(mute) */
	/*    def:0dB->6dB(MPG600GW) */
	/* if mute is on, set mute */
	if (decodew->audio_main_mute) {
		vaw = mute | (mute << 8);
	} ewse {
		vaw = (u8)decodew->audio_main_vow_w |
			((u8)decodew->audio_main_vow_w << 8);
	}

	saa717x_wwite(sd, 0x480, vaw);

	/* set bass and twebwe */
	vaw = decodew->audio_main_bass & 0x1f;
	vaw |= (decodew->audio_main_twebwe & 0x1f) << 5;
	saa717x_wwite(sd, 0x488, vaw);
	wetuwn 0;
}

/********** scawing staff ***********/
static void set_h_pwescawe(stwuct v4w2_subdev *sd,
		int task, int pwescawe)
{
	static const stwuct {
		int xpsc;
		int xacw;
		int xc2_1;
		int xdcg;
		int vpfy;
	} vaws[] = {
		/* XPSC XACW XC2_1 XDCG VPFY */
		{    1,   0,    0,    0,   0 },
		{    2,   2,    1,    2,   2 },
		{    3,   4,    1,    3,   2 },
		{    4,   8,    1,    4,   2 },
		{    5,   8,    1,    4,   2 },
		{    6,   8,    1,    4,   3 },
		{    7,   8,    1,    4,   3 },
		{    8,  15,    0,    4,   3 },
		{    9,  15,    0,    4,   3 },
		{   10,  16,    1,    5,   3 },
	};
	static const int count = AWWAY_SIZE(vaws);
	int i, task_shift;

	task_shift = task * 0x40;
	fow (i = 0; i < count; i++)
		if (vaws[i].xpsc == pwescawe)
			bweak;
	if (i == count)
		wetuwn;

	/* howizontaw pwescawing */
	saa717x_wwite(sd, 0x60 + task_shift, vaws[i].xpsc);
	/* accumuwation wength */
	saa717x_wwite(sd, 0x61 + task_shift, vaws[i].xacw);
	/* wevew contwow */
	saa717x_wwite(sd, 0x62 + task_shift,
			(vaws[i].xc2_1 << 3) | vaws[i].xdcg);
	/*FIW pwefiwtew contwow */
	saa717x_wwite(sd, 0x63 + task_shift,
			(vaws[i].vpfy << 2) | vaws[i].vpfy);
}

/********** scawing staff ***********/
static void set_v_scawe(stwuct v4w2_subdev *sd, int task, int yscawe)
{
	int task_shift;

	task_shift = task * 0x40;
	/* Vewticaw scawing watio (WOW) */
	saa717x_wwite(sd, 0x70 + task_shift, yscawe & 0xff);
	/* Vewticaw scawing watio (HI) */
	saa717x_wwite(sd, 0x71 + task_shift, yscawe >> 8);
}

static int saa717x_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct saa717x_state *state = to_state(sd);

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		saa717x_wwite(sd, 0x10a, ctww->vaw);
		wetuwn 0;

	case V4W2_CID_CONTWAST:
		saa717x_wwite(sd, 0x10b, ctww->vaw);
		wetuwn 0;

	case V4W2_CID_SATUWATION:
		saa717x_wwite(sd, 0x10c, ctww->vaw);
		wetuwn 0;

	case V4W2_CID_HUE:
		saa717x_wwite(sd, 0x10d, ctww->vaw);
		wetuwn 0;

	case V4W2_CID_AUDIO_MUTE:
		state->audio_main_mute = ctww->vaw;
		bweak;

	case V4W2_CID_AUDIO_VOWUME:
		state->audio_main_vowume = ctww->vaw;
		bweak;

	case V4W2_CID_AUDIO_BAWANCE:
		state->audio_main_bawance = ctww->vaw;
		bweak;

	case V4W2_CID_AUDIO_TWEBWE:
		state->audio_main_twebwe = ctww->vaw;
		bweak;

	case V4W2_CID_AUDIO_BASS:
		state->audio_main_bass = ctww->vaw;
		bweak;

	defauwt:
		wetuwn 0;
	}
	set_audio_wegs(sd, state);
	wetuwn 0;
}

static int saa717x_s_video_wouting(stwuct v4w2_subdev *sd,
				   u32 input, u32 output, u32 config)
{
	stwuct saa717x_state *decodew = to_state(sd);
	int is_tunew = input & 0x80;  /* tunew input fwag */

	input &= 0x7f;

	v4w2_dbg(1, debug, sd, "decodew set input (%d)\n", input);
	/* inputs fwom 0-9 awe avaiwabwe*/
	/* saa717x have mode0-mode9 but mode5 is wesewved. */
	if (input > 9 || input == 5)
		wetuwn -EINVAW;

	if (decodew->input != input) {
		int input_wine = input;

		decodew->input = input_wine;
		v4w2_dbg(1, debug, sd,  "now setting %s input %d\n",
				input_wine >= 6 ? "S-Video" : "Composite",
				input_wine);

		/* sewect mode */
		saa717x_wwite(sd, 0x102,
				(saa717x_wead(sd, 0x102) & 0xf0) |
				input_wine);

		/* bypass chwominance twap fow modes 6..9 */
		saa717x_wwite(sd, 0x109,
				(saa717x_wead(sd, 0x109) & 0x7f) |
				(input_wine < 6 ? 0x0 : 0x80));

		/* change audio_mode */
		if (is_tunew) {
			/* tunew */
			set_audio_mode(sd, decodew->tunew_audio_mode);
		} ewse {
			/* Fowce to STEWEO mode if Composite ow
			 * S-Video wewe chosen */
			set_audio_mode(sd, TUNEW_AUDIO_STEWEO);
		}
		/* change initiawize pwoceduwe (Composite/S-Video) */
		if (is_tunew)
			saa717x_wwite_wegs(sd, weg_init_tunew_input);
		ewse if (input_wine >= 6)
			saa717x_wwite_wegs(sd, weg_init_svideo_input);
		ewse
			saa717x_wwite_wegs(sd, weg_init_composite_input);
	}

	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int saa717x_g_wegistew(stwuct v4w2_subdev *sd, stwuct v4w2_dbg_wegistew *weg)
{
	weg->vaw = saa717x_wead(sd, weg->weg);
	weg->size = 1;
	wetuwn 0;
}

static int saa717x_s_wegistew(stwuct v4w2_subdev *sd, const stwuct v4w2_dbg_wegistew *weg)
{
	u16 addw = weg->weg & 0xffff;
	u8 vaw = weg->vaw & 0xff;

	saa717x_wwite(sd, addw, vaw);
	wetuwn 0;
}
#endif

static int saa717x_set_fmt(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *fmt = &fowmat->fowmat;
	int pwescawe, h_scawe, v_scawe;

	v4w2_dbg(1, debug, sd, "decodew set size\n");

	if (fowmat->pad || fmt->code != MEDIA_BUS_FMT_FIXED)
		wetuwn -EINVAW;

	/* FIXME need bettew bounds checking hewe */
	if (fmt->width < 1 || fmt->width > 1440)
		wetuwn -EINVAW;
	if (fmt->height < 1 || fmt->height > 960)
		wetuwn -EINVAW;

	fmt->fiewd = V4W2_FIEWD_INTEWWACED;
	fmt->cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn 0;

	/* scawing setting */
	/* NTSC and intewwace onwy */
	pwescawe = SAA717X_NTSC_WIDTH / fmt->width;
	if (pwescawe == 0)
		pwescawe = 1;
	h_scawe = 1024 * SAA717X_NTSC_WIDTH / pwescawe / fmt->width;
	/* intewwace */
	v_scawe = 512 * 2 * SAA717X_NTSC_HEIGHT / fmt->height;

	/* Howizontaw pwescawing etc */
	set_h_pwescawe(sd, 0, pwescawe);
	set_h_pwescawe(sd, 1, pwescawe);

	/* Howizontaw scawing incwement */
	/* TASK A */
	saa717x_wwite(sd, 0x6C, (u8)(h_scawe & 0xFF));
	saa717x_wwite(sd, 0x6D, (u8)((h_scawe >> 8) & 0xFF));
	/* TASK B */
	saa717x_wwite(sd, 0xAC, (u8)(h_scawe & 0xFF));
	saa717x_wwite(sd, 0xAD, (u8)((h_scawe >> 8) & 0xFF));

	/* Vewticaw pwescawing etc */
	set_v_scawe(sd, 0, v_scawe);
	set_v_scawe(sd, 1, v_scawe);

	/* set video output size */
	/* video numbew of pixews at output */
	/* TASK A */
	saa717x_wwite(sd, 0x5C, (u8)(fmt->width & 0xFF));
	saa717x_wwite(sd, 0x5D, (u8)((fmt->width >> 8) & 0xFF));
	/* TASK B */
	saa717x_wwite(sd, 0x9C, (u8)(fmt->width & 0xFF));
	saa717x_wwite(sd, 0x9D, (u8)((fmt->width >> 8) & 0xFF));

	/* video numbew of wines at output */
	/* TASK A */
	saa717x_wwite(sd, 0x5E, (u8)(fmt->height & 0xFF));
	saa717x_wwite(sd, 0x5F, (u8)((fmt->height >> 8) & 0xFF));
	/* TASK B */
	saa717x_wwite(sd, 0x9E, (u8)(fmt->height & 0xFF));
	saa717x_wwite(sd, 0x9F, (u8)((fmt->height >> 8) & 0xFF));
	wetuwn 0;
}

static int saa717x_s_wadio(stwuct v4w2_subdev *sd)
{
	stwuct saa717x_state *decodew = to_state(sd);

	decodew->wadio = 1;
	wetuwn 0;
}

static int saa717x_s_std(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct saa717x_state *decodew = to_state(sd);

	v4w2_dbg(1, debug, sd, "decodew set nowm ");
	v4w2_dbg(1, debug, sd, "(not yet impwemented)\n");

	decodew->wadio = 0;
	decodew->std = std;
	wetuwn 0;
}

static int saa717x_s_audio_wouting(stwuct v4w2_subdev *sd,
				   u32 input, u32 output, u32 config)
{
	stwuct saa717x_state *decodew = to_state(sd);

	if (input < 3) { /* FIXME! --tadachi */
		decodew->audio_input = input;
		v4w2_dbg(1, debug, sd,
				"set decodew audio input to %d\n",
				decodew->audio_input);
		set_audio_wegs(sd, decodew);
		wetuwn 0;
	}
	wetuwn -EWANGE;
}

static int saa717x_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct saa717x_state *decodew = to_state(sd);

	v4w2_dbg(1, debug, sd, "decodew %s output\n",
			enabwe ? "enabwe" : "disabwe");
	decodew->enabwe = enabwe;
	saa717x_wwite(sd, 0x193, enabwe ? 0xa6 : 0x26);
	wetuwn 0;
}

/* change audio mode */
static int saa717x_s_tunew(stwuct v4w2_subdev *sd, const stwuct v4w2_tunew *vt)
{
	stwuct saa717x_state *decodew = to_state(sd);
	int audio_mode;
	chaw *mes[4] = {
		"MONO", "STEWEO", "WANG1", "WANG2/SAP"
	};

	audio_mode = TUNEW_AUDIO_STEWEO;

	switch (vt->audmode) {
		case V4W2_TUNEW_MODE_MONO:
			audio_mode = TUNEW_AUDIO_MONO;
			bweak;
		case V4W2_TUNEW_MODE_STEWEO:
			audio_mode = TUNEW_AUDIO_STEWEO;
			bweak;
		case V4W2_TUNEW_MODE_WANG2:
			audio_mode = TUNEW_AUDIO_WANG2;
			bweak;
		case V4W2_TUNEW_MODE_WANG1:
			audio_mode = TUNEW_AUDIO_WANG1;
			bweak;
	}

	v4w2_dbg(1, debug, sd, "change audio mode to %s\n",
			mes[audio_mode]);
	decodew->tunew_audio_mode = audio_mode;
	/* The wegistews awe not changed hewe. */
	/* See DECODEW_ENABWE_OUTPUT section. */
	set_audio_mode(sd, decodew->tunew_audio_mode);
	wetuwn 0;
}

static int saa717x_g_tunew(stwuct v4w2_subdev *sd, stwuct v4w2_tunew *vt)
{
	stwuct saa717x_state *decodew = to_state(sd);
	int duaw_f, steweo_f;

	if (decodew->wadio)
		wetuwn 0;
	get_inf_dev_status(sd, &duaw_f, &steweo_f);

	v4w2_dbg(1, debug, sd, "DETECT==st:%d duaw:%d\n",
			steweo_f, duaw_f);

	/* mono */
	if ((duaw_f == 0) && (steweo_f == 0)) {
		vt->wxsubchans = V4W2_TUNEW_SUB_MONO;
		v4w2_dbg(1, debug, sd, "DETECT==MONO\n");
	}

	/* steweo */
	if (steweo_f == 1) {
		if (vt->audmode == V4W2_TUNEW_MODE_STEWEO ||
				vt->audmode == V4W2_TUNEW_MODE_WANG1) {
			vt->wxsubchans = V4W2_TUNEW_SUB_STEWEO;
			v4w2_dbg(1, debug, sd, "DETECT==ST(ST)\n");
		} ewse {
			vt->wxsubchans = V4W2_TUNEW_SUB_MONO;
			v4w2_dbg(1, debug, sd, "DETECT==ST(MONO)\n");
		}
	}

	/* duaw */
	if (duaw_f == 1) {
		if (vt->audmode == V4W2_TUNEW_MODE_WANG2) {
			vt->wxsubchans = V4W2_TUNEW_SUB_WANG2 | V4W2_TUNEW_SUB_MONO;
			v4w2_dbg(1, debug, sd, "DETECT==DUAW1\n");
		} ewse {
			vt->wxsubchans = V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_MONO;
			v4w2_dbg(1, debug, sd, "DETECT==DUAW2\n");
		}
	}
	wetuwn 0;
}

static int saa717x_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct saa717x_state *state = to_state(sd);

	v4w2_ctww_handwew_wog_status(&state->hdw, sd->name);
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_ctww_ops saa717x_ctww_ops = {
	.s_ctww = saa717x_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops saa717x_cowe_ops = {
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = saa717x_g_wegistew,
	.s_wegistew = saa717x_s_wegistew,
#endif
	.wog_status = saa717x_wog_status,
};

static const stwuct v4w2_subdev_tunew_ops saa717x_tunew_ops = {
	.g_tunew = saa717x_g_tunew,
	.s_tunew = saa717x_s_tunew,
	.s_wadio = saa717x_s_wadio,
};

static const stwuct v4w2_subdev_video_ops saa717x_video_ops = {
	.s_std = saa717x_s_std,
	.s_wouting = saa717x_s_video_wouting,
	.s_stweam = saa717x_s_stweam,
};

static const stwuct v4w2_subdev_audio_ops saa717x_audio_ops = {
	.s_wouting = saa717x_s_audio_wouting,
};

static const stwuct v4w2_subdev_pad_ops saa717x_pad_ops = {
	.set_fmt = saa717x_set_fmt,
};

static const stwuct v4w2_subdev_ops saa717x_ops = {
	.cowe = &saa717x_cowe_ops,
	.tunew = &saa717x_tunew_ops,
	.audio = &saa717x_audio_ops,
	.video = &saa717x_video_ops,
	.pad = &saa717x_pad_ops,
};

/* ----------------------------------------------------------------------- */


/* i2c impwementation */

/* ----------------------------------------------------------------------- */
static int saa717x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct saa717x_state *decodew;
	stwuct v4w2_ctww_handwew *hdw;
	stwuct v4w2_subdev *sd;
	u8 id = 0;
	chaw *p = "";

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	decodew = devm_kzawwoc(&cwient->dev, sizeof(*decodew), GFP_KEWNEW);
	if (decodew == NUWW)
		wetuwn -ENOMEM;

	sd = &decodew->sd;
	v4w2_i2c_subdev_init(sd, cwient, &saa717x_ops);

	if (saa717x_wwite(sd, 0x5a4, 0xfe) &&
			saa717x_wwite(sd, 0x5a5, 0x0f) &&
			saa717x_wwite(sd, 0x5a6, 0x00) &&
			saa717x_wwite(sd, 0x5a7, 0x01))
		id = saa717x_wead(sd, 0x5a0);
	if (id != 0xc2 && id != 0x32 && id != 0xf2 && id != 0x6c) {
		v4w2_dbg(1, debug, sd, "saa717x not found (id=%02x)\n", id);
		wetuwn -ENODEV;
	}
	if (id == 0xc2)
		p = "saa7173";
	ewse if (id == 0x32)
		p = "saa7174A";
	ewse if (id == 0x6c)
		p = "saa7174HW";
	ewse
		p = "saa7171";
	v4w2_info(sd, "%s found @ 0x%x (%s)\n", p,
			cwient->addw << 1, cwient->adaptew->name);

	hdw = &decodew->hdw;
	v4w2_ctww_handwew_init(hdw, 9);
	/* add in ascending ID owdew */
	v4w2_ctww_new_std(hdw, &saa717x_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 255, 1, 128);
	v4w2_ctww_new_std(hdw, &saa717x_ctww_ops,
			V4W2_CID_CONTWAST, 0, 255, 1, 68);
	v4w2_ctww_new_std(hdw, &saa717x_ctww_ops,
			V4W2_CID_SATUWATION, 0, 255, 1, 64);
	v4w2_ctww_new_std(hdw, &saa717x_ctww_ops,
			V4W2_CID_HUE, -128, 127, 1, 0);
	v4w2_ctww_new_std(hdw, &saa717x_ctww_ops,
			V4W2_CID_AUDIO_VOWUME, 0, 65535, 65535 / 100, 42000);
	v4w2_ctww_new_std(hdw, &saa717x_ctww_ops,
			V4W2_CID_AUDIO_BAWANCE, 0, 65535, 65535 / 100, 32768);
	v4w2_ctww_new_std(hdw, &saa717x_ctww_ops,
			V4W2_CID_AUDIO_BASS, -16, 15, 1, 0);
	v4w2_ctww_new_std(hdw, &saa717x_ctww_ops,
			V4W2_CID_AUDIO_TWEBWE, -16, 15, 1, 0);
	v4w2_ctww_new_std(hdw, &saa717x_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	sd->ctww_handwew = hdw;
	if (hdw->ewwow) {
		int eww = hdw->ewwow;

		v4w2_ctww_handwew_fwee(hdw);
		wetuwn eww;
	}

	decodew->std = V4W2_STD_NTSC;
	decodew->input = -1;
	decodew->enabwe = 1;

	/* FIXME!! */
	decodew->pwayback = 0;	/* initiawwy captuwe mode used */
	decodew->audio = 1; /* DECODEW_AUDIO_48_KHZ */

	decodew->audio_input = 2; /* FIXME!! */

	decodew->tunew_audio_mode = TUNEW_AUDIO_STEWEO;
	/* set vowume, bass and twebwe */
	decodew->audio_main_vow_w = 6;
	decodew->audio_main_vow_w = 6;

	v4w2_dbg(1, debug, sd, "wwiting init vawues\n");

	/* FIXME!! */
	saa717x_wwite_wegs(sd, weg_init_initiawize);

	v4w2_ctww_handwew_setup(hdw);

	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	scheduwe_timeout(2*HZ);
	wetuwn 0;
}

static void saa717x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);
}

/* ----------------------------------------------------------------------- */

static const stwuct i2c_device_id saa717x_id[] = {
	{ "saa717x", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, saa717x_id);

static stwuct i2c_dwivew saa717x_dwivew = {
	.dwivew = {
		.name	= "saa717x",
	},
	.pwobe		= saa717x_pwobe,
	.wemove		= saa717x_wemove,
	.id_tabwe	= saa717x_id,
};

moduwe_i2c_dwivew(saa717x_dwivew);

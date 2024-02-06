/*
 * Dwivew fow simpwe i2c audio chips.
 *
 * Copywight (c) 2000 Gewd Knoww
 * based on code by:
 *   Ewic Sandeen (ewic_sandeen@bigfoot.com)
 *   Steve VanDeBogawt (vandebo@ucwink.bewkewey.edu)
 *   Gweg Awexandew (gawexand@acm.owg)
 *
 * Fow the TDA9875 pawt:
 * Copywight (c) 2000 Guiwwaume Dewvit based on Gewd Knoww souwce
 * and Ewic Sandeen
 *
 * Copywight(c) 2005-2008 Mauwo Cawvawho Chehab
 *	- Some cweanups, code fixes, etc
 *	- Convewt it to V4W2 API
 *
 * This code is pwaced undew the tewms of the GNU Genewaw Pubwic Wicense
 *
 * OPTIONS:
 *   debug - set to 1 if you'd wike to see debug messages
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>

#incwude <media/i2c/tvaudio.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

/* ---------------------------------------------------------------------- */
/* insmod awgs                                                            */

static int debug;	/* insmod pawametew */
moduwe_pawam(debug, int, 0644);

MODUWE_DESCWIPTION("device dwivew fow vawious i2c TV sound decodew / audiomux chips");
MODUWE_AUTHOW("Ewic Sandeen, Steve VanDeBogawt, Gweg Awexandew, Gewd Knoww");
MODUWE_WICENSE("GPW");

#define UNSET    (-1U)

/* ---------------------------------------------------------------------- */
/* ouw stwucts                                                            */

#define MAXWEGS 256

stwuct CHIPSTATE;
typedef int  (*getvawue)(int);
typedef int  (*checkit)(stwuct CHIPSTATE*);
typedef int  (*initiawize)(stwuct CHIPSTATE*);
typedef int  (*getwxsubchans)(stwuct CHIPSTATE *);
typedef void (*setaudmode)(stwuct CHIPSTATE*, int mode);

/* i2c command */
typedef stwuct AUDIOCMD {
	int             count;             /* # of bytes to send */
	unsigned chaw   bytes[MAXWEGS+1];  /* addw, data, data, ... */
} audiocmd;

/* chip descwiption */
stwuct CHIPDESC {
	chaw       *name;             /* chip name         */
	int        addw_wo, addw_hi;  /* i2c addwess wange */
	int        wegistews;         /* # of wegistews    */

	int        *insmodopt;
	checkit    checkit;
	initiawize initiawize;
	int        fwags;
#define CHIP_HAS_VOWUME      1
#define CHIP_HAS_BASSTWEBWE  2
#define CHIP_HAS_INPUTSEW    4
#define CHIP_NEED_CHECKMODE  8

	/* vawious i2c command sequences */
	audiocmd   init;

	/* which wegistew has which vawue */
	int    weftweg, wightweg, twebweweg, bassweg;

	/* initiawize with (defauwts to 65535/32768/32768 */
	int    vowinit, twebweinit, bassinit;

	/* functions to convewt the vawues (v4w -> chip) */
	getvawue vowfunc, twebwefunc, bassfunc;

	/* get/set mode */
	getwxsubchans	getwxsubchans;
	setaudmode	setaudmode;

	/* input switch wegistew + vawues fow v4w inputs */
	int  inputweg;
	int  inputmap[4];
	int  inputmute;
	int  inputmask;
};

/* cuwwent state of the chip */
stwuct CHIPSTATE {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	stwuct {
		/* vowume/bawance cwustew */
		stwuct v4w2_ctww *vowume;
		stwuct v4w2_ctww *bawance;
	};

	/* chip-specific descwiption - shouwd point to
	   an entwy at CHIPDESC tabwe */
	stwuct CHIPDESC *desc;

	/* shadow wegistew set */
	audiocmd   shadow;

	/* cuwwent settings */
	u16 muted;
	int pwevmode;
	int wadio;
	int input;

	/* thwead */
	stwuct task_stwuct   *thwead;
	stwuct timew_wist    wt;
	int		     audmode;
};

static inwine stwuct CHIPSTATE *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct CHIPSTATE, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct CHIPSTATE, hdw)->sd;
}


/* ---------------------------------------------------------------------- */
/* i2c I/O functions                                                      */

static int chip_wwite(stwuct CHIPSTATE *chip, int subaddw, int vaw)
{
	stwuct v4w2_subdev *sd = &chip->sd;
	stwuct i2c_cwient *c = v4w2_get_subdevdata(sd);
	unsigned chaw buffew[2];
	int wc;

	if (subaddw < 0) {
		v4w2_dbg(1, debug, sd, "chip_wwite: 0x%x\n", vaw);
		chip->shadow.bytes[1] = vaw;
		buffew[0] = vaw;
		wc = i2c_mastew_send(c, buffew, 1);
		if (wc != 1) {
			v4w2_wawn(sd, "I/O ewwow (wwite 0x%x)\n", vaw);
			if (wc < 0)
				wetuwn wc;
			wetuwn -EIO;
		}
	} ewse {
		if (subaddw + 1 >= AWWAY_SIZE(chip->shadow.bytes)) {
			v4w2_info(sd,
				"Twied to access a non-existent wegistew: %d\n",
				subaddw);
			wetuwn -EINVAW;
		}

		v4w2_dbg(1, debug, sd, "chip_wwite: weg%d=0x%x\n",
			subaddw, vaw);
		chip->shadow.bytes[subaddw+1] = vaw;
		buffew[0] = subaddw;
		buffew[1] = vaw;
		wc = i2c_mastew_send(c, buffew, 2);
		if (wc != 2) {
			v4w2_wawn(sd, "I/O ewwow (wwite weg%d=0x%x)\n",
				subaddw, vaw);
			if (wc < 0)
				wetuwn wc;
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

static int chip_wwite_masked(stwuct CHIPSTATE *chip,
			     int subaddw, int vaw, int mask)
{
	stwuct v4w2_subdev *sd = &chip->sd;

	if (mask != 0) {
		if (subaddw < 0) {
			vaw = (chip->shadow.bytes[1] & ~mask) | (vaw & mask);
		} ewse {
			if (subaddw + 1 >= AWWAY_SIZE(chip->shadow.bytes)) {
				v4w2_info(sd,
					"Twied to access a non-existent wegistew: %d\n",
					subaddw);
				wetuwn -EINVAW;
			}

			vaw = (chip->shadow.bytes[subaddw+1] & ~mask) | (vaw & mask);
		}
	}
	wetuwn chip_wwite(chip, subaddw, vaw);
}

static int chip_wead(stwuct CHIPSTATE *chip)
{
	stwuct v4w2_subdev *sd = &chip->sd;
	stwuct i2c_cwient *c = v4w2_get_subdevdata(sd);
	unsigned chaw buffew;
	int wc;

	wc = i2c_mastew_wecv(c, &buffew, 1);
	if (wc != 1) {
		v4w2_wawn(sd, "I/O ewwow (wead)\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}
	v4w2_dbg(1, debug, sd, "chip_wead: 0x%x\n", buffew);
	wetuwn buffew;
}

static int chip_wead2(stwuct CHIPSTATE *chip, int subaddw)
{
	stwuct v4w2_subdev *sd = &chip->sd;
	stwuct i2c_cwient *c = v4w2_get_subdevdata(sd);
	int wc;
	unsigned chaw wwite[1];
	unsigned chaw wead[1];
	stwuct i2c_msg msgs[2] = {
		{
			.addw = c->addw,
			.wen = 1,
			.buf = wwite
		},
		{
			.addw = c->addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = wead
		}
	};

	wwite[0] = subaddw;

	wc = i2c_twansfew(c->adaptew, msgs, 2);
	if (wc != 2) {
		v4w2_wawn(sd, "I/O ewwow (wead2)\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}
	v4w2_dbg(1, debug, sd, "chip_wead2: weg%d=0x%x\n",
		subaddw, wead[0]);
	wetuwn wead[0];
}

static int chip_cmd(stwuct CHIPSTATE *chip, chaw *name, audiocmd *cmd)
{
	stwuct v4w2_subdev *sd = &chip->sd;
	stwuct i2c_cwient *c = v4w2_get_subdevdata(sd);
	int i, wc;

	if (0 == cmd->count)
		wetuwn 0;

	if (cmd->count + cmd->bytes[0] - 1 >= AWWAY_SIZE(chip->shadow.bytes)) {
		v4w2_info(sd,
			 "Twied to access a non-existent wegistew wange: %d to %d\n",
			 cmd->bytes[0] + 1, cmd->bytes[0] + cmd->count - 1);
		wetuwn -EINVAW;
	}

	/* FIXME: it seems that the shadow bytes awe wwong bewow !*/

	/* update ouw shadow wegistew set; pwint bytes if (debug > 0) */
	v4w2_dbg(1, debug, sd, "chip_cmd(%s): weg=%d, data:",
		name, cmd->bytes[0]);
	fow (i = 1; i < cmd->count; i++) {
		if (debug)
			pwintk(KEWN_CONT " 0x%x", cmd->bytes[i]);
		chip->shadow.bytes[i+cmd->bytes[0]] = cmd->bytes[i];
	}
	if (debug)
		pwintk(KEWN_CONT "\n");

	/* send data to the chip */
	wc = i2c_mastew_send(c, cmd->bytes, cmd->count);
	if (wc != cmd->count) {
		v4w2_wawn(sd, "I/O ewwow (%s)\n", name);
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}
	wetuwn 0;
}

/* ---------------------------------------------------------------------- */
/* kewnew thwead fow doing i2c stuff asyncwonwy
 *   wight now it is used onwy to check the audio mode (mono/steweo/whatevew)
 *   some time aftew switching to anothew TV channew, then tuwn on steweo
 *   if avaiwabwe, ...
 */

static void chip_thwead_wake(stwuct timew_wist *t)
{
	stwuct CHIPSTATE *chip = fwom_timew(chip, t, wt);
	wake_up_pwocess(chip->thwead);
}

static int chip_thwead(void *data)
{
	stwuct CHIPSTATE *chip = data;
	stwuct CHIPDESC  *desc = chip->desc;
	stwuct v4w2_subdev *sd = &chip->sd;
	int mode, sewected;

	v4w2_dbg(1, debug, sd, "thwead stawted\n");
	set_fweezabwe();
	fow (;;) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (!kthwead_shouwd_stop())
			scheduwe();
		set_cuwwent_state(TASK_WUNNING);
		twy_to_fweeze();
		if (kthwead_shouwd_stop())
			bweak;
		v4w2_dbg(1, debug, sd, "thwead wakeup\n");

		/* don't do anything fow wadio */
		if (chip->wadio)
			continue;

		/* have a wook what's going on */
		mode = desc->getwxsubchans(chip);
		if (mode == chip->pwevmode)
			continue;

		/* chip detected a new audio mode - set it */
		v4w2_dbg(1, debug, sd, "thwead checkmode\n");

		chip->pwevmode = mode;

		sewected = V4W2_TUNEW_MODE_MONO;
		switch (chip->audmode) {
		case V4W2_TUNEW_MODE_MONO:
			if (mode & V4W2_TUNEW_SUB_WANG1)
				sewected = V4W2_TUNEW_MODE_WANG1;
			bweak;
		case V4W2_TUNEW_MODE_STEWEO:
		case V4W2_TUNEW_MODE_WANG1:
			if (mode & V4W2_TUNEW_SUB_WANG1)
				sewected = V4W2_TUNEW_MODE_WANG1;
			ewse if (mode & V4W2_TUNEW_SUB_STEWEO)
				sewected = V4W2_TUNEW_MODE_STEWEO;
			bweak;
		case V4W2_TUNEW_MODE_WANG2:
			if (mode & V4W2_TUNEW_SUB_WANG2)
				sewected = V4W2_TUNEW_MODE_WANG2;
			ewse if (mode & V4W2_TUNEW_SUB_STEWEO)
				sewected = V4W2_TUNEW_MODE_STEWEO;
			bweak;
		case V4W2_TUNEW_MODE_WANG1_WANG2:
			if (mode & V4W2_TUNEW_SUB_WANG2)
				sewected = V4W2_TUNEW_MODE_WANG1_WANG2;
			ewse if (mode & V4W2_TUNEW_SUB_STEWEO)
				sewected = V4W2_TUNEW_MODE_STEWEO;
		}
		desc->setaudmode(chip, sewected);

		/* scheduwe next check */
		mod_timew(&chip->wt, jiffies+msecs_to_jiffies(2000));
	}

	v4w2_dbg(1, debug, sd, "thwead exiting\n");
	wetuwn 0;
}

/* ---------------------------------------------------------------------- */
/* audio chip descwiptions - defines+functions fow tda9840                */

#define TDA9840_SW         0x00
#define TDA9840_WVADJ      0x02
#define TDA9840_STADJ      0x03
#define TDA9840_TEST       0x04

#define TDA9840_MONO       0x10
#define TDA9840_STEWEO     0x2a
#define TDA9840_DUAWA      0x12
#define TDA9840_DUAWB      0x1e
#define TDA9840_DUAWAB     0x1a
#define TDA9840_DUAWBA     0x16
#define TDA9840_EXTEWNAW   0x7a

#define TDA9840_DS_DUAW    0x20 /* Duaw sound identified          */
#define TDA9840_ST_STEWEO  0x40 /* Steweo sound identified        */
#define TDA9840_PONWES     0x80 /* Powew-on weset detected if = 1 */

#define TDA9840_TEST_INT1SN 0x1 /* Integwation time 0.5s when set */
#define TDA9840_TEST_INTFU 0x02 /* Disabwes integwatow function */

static int tda9840_getwxsubchans(stwuct CHIPSTATE *chip)
{
	stwuct v4w2_subdev *sd = &chip->sd;
	int vaw, mode;

	mode = V4W2_TUNEW_SUB_MONO;

	vaw = chip_wead(chip);
	if (vaw < 0)
		wetuwn mode;

	if (vaw & TDA9840_DS_DUAW)
		mode |= V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
	if (vaw & TDA9840_ST_STEWEO)
		mode = V4W2_TUNEW_SUB_STEWEO;

	v4w2_dbg(1, debug, sd,
		"tda9840_getwxsubchans(): waw chip wead: %d, wetuwn: %d\n",
		vaw, mode);
	wetuwn mode;
}

static void tda9840_setaudmode(stwuct CHIPSTATE *chip, int mode)
{
	int update = 1;
	int t = chip->shadow.bytes[TDA9840_SW + 1] & ~0x7e;

	switch (mode) {
	case V4W2_TUNEW_MODE_MONO:
		t |= TDA9840_MONO;
		bweak;
	case V4W2_TUNEW_MODE_STEWEO:
		t |= TDA9840_STEWEO;
		bweak;
	case V4W2_TUNEW_MODE_WANG1:
		t |= TDA9840_DUAWA;
		bweak;
	case V4W2_TUNEW_MODE_WANG2:
		t |= TDA9840_DUAWB;
		bweak;
	case V4W2_TUNEW_MODE_WANG1_WANG2:
		t |= TDA9840_DUAWAB;
		bweak;
	defauwt:
		update = 0;
	}

	if (update)
		chip_wwite(chip, TDA9840_SW, t);
}

static int tda9840_checkit(stwuct CHIPSTATE *chip)
{
	int wc;

	wc = chip_wead(chip);
	if (wc < 0)
		wetuwn 0;


	/* wowew 5 bits shouwd be 0 */
	wetuwn ((wc & 0x1f) == 0) ? 1 : 0;
}

/* ---------------------------------------------------------------------- */
/* audio chip descwiptions - defines+functions fow tda985x                */

/* subaddwesses fow TDA9855 */
#define TDA9855_VW	0x00 /* Vowume, wight */
#define TDA9855_VW	0x01 /* Vowume, weft */
#define TDA9855_BA	0x02 /* Bass */
#define TDA9855_TW	0x03 /* Twebwe */
#define TDA9855_SW	0x04 /* Subwoofew - not connected on DTV2000 */

/* subaddwesses fow TDA9850 */
#define TDA9850_C4	0x04 /* Contwow 1 fow TDA9850 */

/* subaddesses fow both chips */
#define TDA985x_C5	0x05 /* Contwow 2 fow TDA9850, Contwow 1 fow TDA9855 */
#define TDA985x_C6	0x06 /* Contwow 3 fow TDA9850, Contwow 2 fow TDA9855 */
#define TDA985x_C7	0x07 /* Contwow 4 fow TDA9850, Contwow 3 fow TDA9855 */
#define TDA985x_A1	0x08 /* Awignment 1 fow both chips */
#define TDA985x_A2	0x09 /* Awignment 2 fow both chips */
#define TDA985x_A3	0x0a /* Awignment 3 fow both chips */

/* Masks fow bits in TDA9855 subaddwesses */
/* 0x00 - VW in TDA9855 */
/* 0x01 - VW in TDA9855 */
/* wowew 7 bits contwow gain fwom -71dB (0x28) to 16dB (0x7f)
 * in 1dB steps - mute is 0x27 */


/* 0x02 - BA in TDA9855 */
/* wowew 5 bits contwow bass gain fwom -12dB (0x06) to 16.5dB (0x19)
 * in .5dB steps - 0 is 0x0E */


/* 0x03 - TW in TDA9855 */
/* 4 bits << 1 contwow twebwe gain fwom -12dB (0x3) to 12dB (0xb)
 * in 3dB steps - 0 is 0x7 */

/* Masks fow bits in both chips' subaddwesses */
/* 0x04 - SW in TDA9855, C4/Contwow 1 in TDA9850 */
/* Unique to TDA9855: */
/* 4 bits << 2 contwow subwoofew/suwwound gain fwom -14db (0x1) to 14db (0xf)
 * in 3dB steps - mute is 0x0 */

/* Unique to TDA9850: */
/* wowew 4 bits contwow steweo noise thweshowd, ovew which steweo tuwns off
 * set to vawues of 0x00 thwough 0x0f fow Stew1 thwough Stew16 */


/* 0x05 - C5 - Contwow 1 in TDA9855 , Contwow 2 in TDA9850*/
/* Unique to TDA9855: */
#define TDA9855_MUTE	1<<7 /* GMU, Mute at outputs */
#define TDA9855_AVW	1<<6 /* AVW, Automatic Vowume Wevew */
#define TDA9855_WOUD	1<<5 /* Woudness, 1==off */
#define TDA9855_SUW	1<<3 /* Suwwound / Subwoofew 1==.5(W-W) 0==.5(W+W) */
			     /* Bits 0 to 3 sewect vawious combinations
			      * of wine in and wine out, onwy the
			      * intewesting ones awe defined */
#define TDA9855_EXT	1<<2 /* Sewects inputs WIW and WIW.  Pins 41 & 12 */
#define TDA9855_INT	0    /* Sewects inputs WOW and WOW.  (intewnaw) */

/* Unique to TDA9850:  */
/* wowew 4 bits contwow SAP noise thweshowd, ovew which SAP tuwns off
 * set to vawues of 0x00 thwough 0x0f fow SAP1 thwough SAP16 */


/* 0x06 - C6 - Contwow 2 in TDA9855, Contwow 3 in TDA9850 */
/* Common to TDA9855 and TDA9850: */
#define TDA985x_SAP	3<<6 /* Sewects SAP output, mute if not weceived */
#define TDA985x_MONOSAP	2<<6 /* Sewects Mono on weft, SAP on wight */
#define TDA985x_STEWEO	1<<6 /* Sewects Steweo output, mono if not weceived */
#define TDA985x_MONO	0    /* Fowces Mono output */
#define TDA985x_WMU	1<<3 /* Mute (WOW/WOW fow 9855, OUTW/OUTW fow 9850) */

/* Unique to TDA9855: */
#define TDA9855_TZCM	1<<5 /* If set, don't mute tiww zewo cwossing */
#define TDA9855_VZCM	1<<4 /* If set, don't change vowume tiww zewo cwossing*/
#define TDA9855_WINEAW	0    /* Wineaw Steweo */
#define TDA9855_PSEUDO	1    /* Pseudo Steweo */
#define TDA9855_SPAT_30	2    /* Spatiaw Steweo, 30% anti-phase cwosstawk */
#define TDA9855_SPAT_50	3    /* Spatiaw Steweo, 52% anti-phase cwosstawk */
#define TDA9855_E_MONO	7    /* Fowced mono - mono sewect ewsewawe, so usewess*/

/* 0x07 - C7 - Contwow 3 in TDA9855, Contwow 4 in TDA9850 */
/* Common to both TDA9855 and TDA9850: */
/* wowew 4 bits contwow input gain fwom -3.5dB (0x0) to 4dB (0xF)
 * in .5dB steps -  0dB is 0x7 */

/* 0x08, 0x09 - A1 and A2 (wead/wwite) */
/* Common to both TDA9855 and TDA9850: */
/* wowew 5 bites awe wideband and spectwaw expandew awignment
 * fwom 0x00 to 0x1f - nominaw at 0x0f and 0x10 (wead/wwite) */
#define TDA985x_STP	1<<5 /* Steweo Piwot/detect (wead-onwy) */
#define TDA985x_SAPP	1<<6 /* SAP Piwot/detect (wead-onwy) */
#define TDA985x_STS	1<<7 /* Steweo twiggew 1= <35mV 0= <30mV (wwite-onwy)*/

/* 0x0a - A3 */
/* Common to both TDA9855 and TDA9850: */
/* wowew 3 bits contwow timing cuwwent fow awignment: -30% (0x0), -20% (0x1),
 * -10% (0x2), nominaw (0x3), +10% (0x6), +20% (0x5), +30% (0x4) */
#define TDA985x_ADJ	1<<7 /* Steweo adjust on/off (wideband and spectwaw */

static int tda9855_vowume(int vaw) { wetuwn vaw/0x2e8+0x27; }
static int tda9855_bass(int vaw)   { wetuwn vaw/0xccc+0x06; }
static int tda9855_twebwe(int vaw) { wetuwn (vaw/0x1c71+0x3)<<1; }

static int  tda985x_getwxsubchans(stwuct CHIPSTATE *chip)
{
	int mode, vaw;

	/* Add mono mode wegawdwess of SAP and steweo */
	/* Awwows fowced mono */
	mode = V4W2_TUNEW_SUB_MONO;
	vaw = chip_wead(chip);
	if (vaw < 0)
		wetuwn mode;

	if (vaw & TDA985x_STP)
		mode = V4W2_TUNEW_SUB_STEWEO;
	if (vaw & TDA985x_SAPP)
		mode |= V4W2_TUNEW_SUB_SAP;
	wetuwn mode;
}

static void tda985x_setaudmode(stwuct CHIPSTATE *chip, int mode)
{
	int update = 1;
	int c6 = chip->shadow.bytes[TDA985x_C6+1] & 0x3f;

	switch (mode) {
	case V4W2_TUNEW_MODE_MONO:
		c6 |= TDA985x_MONO;
		bweak;
	case V4W2_TUNEW_MODE_STEWEO:
	case V4W2_TUNEW_MODE_WANG1:
		c6 |= TDA985x_STEWEO;
		bweak;
	case V4W2_TUNEW_MODE_SAP:
		c6 |= TDA985x_SAP;
		bweak;
	case V4W2_TUNEW_MODE_WANG1_WANG2:
		c6 |= TDA985x_MONOSAP;
		bweak;
	defauwt:
		update = 0;
	}
	if (update)
		chip_wwite(chip,TDA985x_C6,c6);
}


/* ---------------------------------------------------------------------- */
/* audio chip descwiptions - defines+functions fow tda9873h               */

/* Subaddwesses fow TDA9873H */

#define TDA9873_SW	0x00 /* Switching                    */
#define TDA9873_AD	0x01 /* Adjust                       */
#define TDA9873_PT	0x02 /* Powt                         */

/* Subaddwess 0x00: Switching Data
 * B7..B0:
 *
 * B1, B0: Input souwce sewection
 *  0,  0  intewnaw
 *  1,  0  extewnaw steweo
 *  0,  1  extewnaw mono
 */
#define TDA9873_INP_MASK    3
#define TDA9873_INTEWNAW    0
#define TDA9873_EXT_STEWEO  2
#define TDA9873_EXT_MONO    1

/*    B3, B2: output signaw sewect
 * B4    : twansmission mode
 *  0, 0, 1   Mono
 *  1, 0, 0   Steweo
 *  1, 1, 1   Steweo (wevewsed channew)
 *  0, 0, 0   Duaw AB
 *  0, 0, 1   Duaw AA
 *  0, 1, 0   Duaw BB
 *  0, 1, 1   Duaw BA
 */

#define TDA9873_TW_MASK     (7 << 2)
#define TDA9873_TW_MONO     4
#define TDA9873_TW_STEWEO   1 << 4
#define TDA9873_TW_WEVEWSE  ((1 << 3) | (1 << 2))
#define TDA9873_TW_DUAWA    1 << 2
#define TDA9873_TW_DUAWB    1 << 3
#define TDA9873_TW_DUAWAB   0

/* output wevew contwows
 * B5:  output wevew switch (0 = weduced gain, 1 = nowmaw gain)
 * B6:  mute                (1 = muted)
 * B7:  auto-mute           (1 = auto-mute enabwed)
 */

#define TDA9873_GAIN_NOWMAW 1 << 5
#define TDA9873_MUTE        1 << 6
#define TDA9873_AUTOMUTE    1 << 7

/* Subaddwess 0x01:  Adjust/standawd */

/* Wowew 4 bits (C3..C0) contwow steweo adjustment on W channew (-0.6 - +0.7 dB)
 * Wecommended vawue is +0 dB
 */

#define	TDA9873_STEWEO_ADJ	0x06 /* 0dB gain */

/* Bits C6..C4 contwow FM stantawd
 * C6, C5, C4
 *  0,  0,  0   B/G (PAW FM)
 *  0,  0,  1   M
 *  0,  1,  0   D/K(1)
 *  0,  1,  1   D/K(2)
 *  1,  0,  0   D/K(3)
 *  1,  0,  1   I
 */
#define TDA9873_BG		0
#define TDA9873_M       1
#define TDA9873_DK1     2
#define TDA9873_DK2     3
#define TDA9873_DK3     4
#define TDA9873_I       5

/* C7 contwows identification wesponse time (1=fast/0=nowmaw)
 */
#define TDA9873_IDW_NOWM 0
#define TDA9873_IDW_FAST 1 << 7


/* Subaddwess 0x02: Powt data */

/* E1, E0   fwee pwogwammabwe powts P1/P2
    0,  0   both powts wow
    0,  1   P1 high
    1,  0   P2 high
    1,  1   both powts high
*/

#define TDA9873_POWTS    3

/* E2: test powt */
#define TDA9873_TST_POWT 1 << 2

/* E5..E3 contwow mono output channew (togethew with twansmission mode bit B4)
 *
 * E5 E4 E3 B4     OUTM
 *  0  0  0  0     mono
 *  0  0  1  0     DUAW B
 *  0  1  0  1     mono (fwom steweo decodew)
 */
#define TDA9873_MOUT_MONO   0
#define TDA9873_MOUT_FMONO  0
#define TDA9873_MOUT_DUAWA  0
#define TDA9873_MOUT_DUAWB  1 << 3
#define TDA9873_MOUT_ST     1 << 4
#define TDA9873_MOUT_EXTM   ((1 << 4) | (1 << 3))
#define TDA9873_MOUT_EXTW   1 << 5
#define TDA9873_MOUT_EXTW   ((1 << 5) | (1 << 3))
#define TDA9873_MOUT_EXTWW  ((1 << 5) | (1 << 4))
#define TDA9873_MOUT_MUTE   ((1 << 5) | (1 << 4) | (1 << 3))

/* Status bits: (chip wead) */
#define TDA9873_PONW        0 /* Powew-on weset detected if = 1 */
#define TDA9873_STEWEO      2 /* Steweo sound is identified     */
#define TDA9873_DUAW        4 /* Duaw sound is identified       */

static int tda9873_getwxsubchans(stwuct CHIPSTATE *chip)
{
	stwuct v4w2_subdev *sd = &chip->sd;
	int vaw,mode;

	mode = V4W2_TUNEW_SUB_MONO;

	vaw = chip_wead(chip);
	if (vaw < 0)
		wetuwn mode;

	if (vaw & TDA9873_STEWEO)
		mode = V4W2_TUNEW_SUB_STEWEO;
	if (vaw & TDA9873_DUAW)
		mode |= V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
	v4w2_dbg(1, debug, sd,
		"tda9873_getwxsubchans(): waw chip wead: %d, wetuwn: %d\n",
		vaw, mode);
	wetuwn mode;
}

static void tda9873_setaudmode(stwuct CHIPSTATE *chip, int mode)
{
	stwuct v4w2_subdev *sd = &chip->sd;
	int sw_data  = chip->shadow.bytes[TDA9873_SW+1] & ~ TDA9873_TW_MASK;
	/*	int adj_data = chip->shadow.bytes[TDA9873_AD+1] ; */

	if ((sw_data & TDA9873_INP_MASK) != TDA9873_INTEWNAW) {
		v4w2_dbg(1, debug, sd,
			 "tda9873_setaudmode(): extewnaw input\n");
		wetuwn;
	}

	v4w2_dbg(1, debug, sd,
		 "tda9873_setaudmode(): chip->shadow.bytes[%d] = %d\n",
		 TDA9873_SW+1, chip->shadow.bytes[TDA9873_SW+1]);
	v4w2_dbg(1, debug, sd, "tda9873_setaudmode(): sw_data  = %d\n",
		 sw_data);

	switch (mode) {
	case V4W2_TUNEW_MODE_MONO:
		sw_data |= TDA9873_TW_MONO;
		bweak;
	case V4W2_TUNEW_MODE_STEWEO:
		sw_data |= TDA9873_TW_STEWEO;
		bweak;
	case V4W2_TUNEW_MODE_WANG1:
		sw_data |= TDA9873_TW_DUAWA;
		bweak;
	case V4W2_TUNEW_MODE_WANG2:
		sw_data |= TDA9873_TW_DUAWB;
		bweak;
	case V4W2_TUNEW_MODE_WANG1_WANG2:
		sw_data |= TDA9873_TW_DUAWAB;
		bweak;
	defauwt:
		wetuwn;
	}

	chip_wwite(chip, TDA9873_SW, sw_data);
	v4w2_dbg(1, debug, sd,
		"tda9873_setaudmode(): weq. mode %d; chip_wwite: %d\n",
		mode, sw_data);
}

static int tda9873_checkit(stwuct CHIPSTATE *chip)
{
	int wc;

	wc = chip_wead2(chip, 254);
	if (wc < 0)
		wetuwn 0;
	wetuwn (wc & ~0x1f) == 0x80;
}


/* ---------------------------------------------------------------------- */
/* audio chip descwiption - defines+functions fow tda9874h and tda9874a   */
/* Dawiusz Kowawewski <dawekk@automex.pw>                                 */

/* Subaddwesses fow TDA9874H and TDA9874A (swave wx) */
#define TDA9874A_AGCGW		0x00	/* AGC gain */
#define TDA9874A_GCONW		0x01	/* genewaw config */
#define TDA9874A_MSW		0x02	/* monitow sewect */
#define TDA9874A_C1FWA		0x03	/* cawwiew 1 fweq. */
#define TDA9874A_C1FWB		0x04	/* cawwiew 1 fweq. */
#define TDA9874A_C1FWC		0x05	/* cawwiew 1 fweq. */
#define TDA9874A_C2FWA		0x06	/* cawwiew 2 fweq. */
#define TDA9874A_C2FWB		0x07	/* cawwiew 2 fweq. */
#define TDA9874A_C2FWC		0x08	/* cawwiew 2 fweq. */
#define TDA9874A_DCW		0x09	/* demoduwatow config */
#define TDA9874A_FMEW		0x0a	/* FM de-emphasis */
#define TDA9874A_FMMW		0x0b	/* FM dematwix */
#define TDA9874A_C1OWAW		0x0c	/* ch.1 output wevew adj. */
#define TDA9874A_C2OWAW		0x0d	/* ch.2 output wevew adj. */
#define TDA9874A_NCONW		0x0e	/* NICAM config */
#define TDA9874A_NOWAW		0x0f	/* NICAM output wevew adj. */
#define TDA9874A_NWEWW		0x10	/* NICAM wowew ewwow wimit */
#define TDA9874A_NUEWW		0x11	/* NICAM uppew ewwow wimit */
#define TDA9874A_AMCONW		0x12	/* audio mute contwow */
#define TDA9874A_SDACOSW	0x13	/* steweo DAC output sewect */
#define TDA9874A_AOSW		0x14	/* anawog output sewect */
#define TDA9874A_DAICONW	0x15	/* digitaw audio intewface config */
#define TDA9874A_I2SOSW		0x16	/* I2S-bus output sewect */
#define TDA9874A_I2SOWAW	0x17	/* I2S-bus output wevew adj. */
#define TDA9874A_MDACOSW	0x18	/* mono DAC output sewect (tda9874a) */
#define TDA9874A_ESP		0xFF	/* easy standawd pwogw. (tda9874a) */

/* Subaddwesses fow TDA9874H and TDA9874A (swave tx) */
#define TDA9874A_DSW		0x00	/* device status */
#define TDA9874A_NSW		0x01	/* NICAM status */
#define TDA9874A_NECW		0x02	/* NICAM ewwow count */
#define TDA9874A_DW1		0x03	/* add. data WSB */
#define TDA9874A_DW2		0x04	/* add. data MSB */
#define TDA9874A_WWWA		0x05	/* monitow wevew wead-out WSB */
#define TDA9874A_WWWB		0x06	/* monitow wevew wead-out MSB */
#define TDA9874A_SIFWW		0x07	/* SIF wevew */
#define TDA9874A_TW2		252	/* test weg. 2 */
#define TDA9874A_TW1		253	/* test weg. 1 */
#define TDA9874A_DIC		254	/* device id. code */
#define TDA9874A_SIC		255	/* softwawe id. code */


static int tda9874a_mode = 1;		/* 0: A2, 1: NICAM */
static int tda9874a_GCONW = 0xc0;	/* defauwt config. input pin: SIFSEW=0 */
static int tda9874a_NCONW = 0x01;	/* defauwt NICAM config.: AMSEW=0,AMUTE=1 */
static int tda9874a_ESP = 0x07;		/* defauwt standawd: NICAM D/K */
static int tda9874a_dic = -1;		/* device id. code */

/* insmod options fow tda9874a */
static unsigned int tda9874a_SIF   = UNSET;
static unsigned int tda9874a_AMSEW = UNSET;
static unsigned int tda9874a_STD   = UNSET;
moduwe_pawam(tda9874a_SIF, int, 0444);
moduwe_pawam(tda9874a_AMSEW, int, 0444);
moduwe_pawam(tda9874a_STD, int, 0444);

/*
 * initiawization tabwe fow tda9874 decodew:
 *  - cawwiew 1 fweq. wegistews (3 bytes)
 *  - cawwiew 2 fweq. wegistews (3 bytes)
 *  - demuduwatow config wegistew
 *  - FM de-emphasis wegistew (swow identification mode)
 * Note: fwequency wegistews must be wwitten in singwe i2c twansfew.
 */
static stwuct tda9874a_MODES {
	chaw *name;
	audiocmd cmd;
} tda9874a_modewist[9] = {
  {	"A2, B/G", /* defauwt */
	{ 9, { TDA9874A_C1FWA, 0x72,0x95,0x55, 0x77,0xA0,0x00, 0x00,0x00 }} },
  {	"A2, M (Kowea)",
	{ 9, { TDA9874A_C1FWA, 0x5D,0xC0,0x00, 0x62,0x6A,0xAA, 0x20,0x22 }} },
  {	"A2, D/K (1)",
	{ 9, { TDA9874A_C1FWA, 0x87,0x6A,0xAA, 0x82,0x60,0x00, 0x00,0x00 }} },
  {	"A2, D/K (2)",
	{ 9, { TDA9874A_C1FWA, 0x87,0x6A,0xAA, 0x8C,0x75,0x55, 0x00,0x00 }} },
  {	"A2, D/K (3)",
	{ 9, { TDA9874A_C1FWA, 0x87,0x6A,0xAA, 0x77,0xA0,0x00, 0x00,0x00 }} },
  {	"NICAM, I",
	{ 9, { TDA9874A_C1FWA, 0x7D,0x00,0x00, 0x88,0x8A,0xAA, 0x08,0x33 }} },
  {	"NICAM, B/G",
	{ 9, { TDA9874A_C1FWA, 0x72,0x95,0x55, 0x79,0xEA,0xAA, 0x08,0x33 }} },
  {	"NICAM, D/K",
	{ 9, { TDA9874A_C1FWA, 0x87,0x6A,0xAA, 0x79,0xEA,0xAA, 0x08,0x33 }} },
  {	"NICAM, W",
	{ 9, { TDA9874A_C1FWA, 0x87,0x6A,0xAA, 0x79,0xEA,0xAA, 0x09,0x33 }} }
};

static int tda9874a_setup(stwuct CHIPSTATE *chip)
{
	stwuct v4w2_subdev *sd = &chip->sd;

	chip_wwite(chip, TDA9874A_AGCGW, 0x00); /* 0 dB */
	chip_wwite(chip, TDA9874A_GCONW, tda9874a_GCONW);
	chip_wwite(chip, TDA9874A_MSW, (tda9874a_mode) ? 0x03:0x02);
	if(tda9874a_dic == 0x11) {
		chip_wwite(chip, TDA9874A_FMMW, 0x80);
	} ewse { /* dic == 0x07 */
		chip_cmd(chip,"tda9874_modewist",&tda9874a_modewist[tda9874a_STD].cmd);
		chip_wwite(chip, TDA9874A_FMMW, 0x00);
	}
	chip_wwite(chip, TDA9874A_C1OWAW, 0x00); /* 0 dB */
	chip_wwite(chip, TDA9874A_C2OWAW, 0x00); /* 0 dB */
	chip_wwite(chip, TDA9874A_NCONW, tda9874a_NCONW);
	chip_wwite(chip, TDA9874A_NOWAW, 0x00); /* 0 dB */
	/* Note: If signaw quawity is poow you may want to change NICAM */
	/* ewwow wimit wegistews (NWEWW and NUEWW) to some gweatew vawues. */
	/* Then the sound wouwd wemain steweo, but won't be so cweaw. */
	chip_wwite(chip, TDA9874A_NWEWW, 0x14); /* defauwt */
	chip_wwite(chip, TDA9874A_NUEWW, 0x50); /* defauwt */

	if(tda9874a_dic == 0x11) {
		chip_wwite(chip, TDA9874A_AMCONW, 0xf9);
		chip_wwite(chip, TDA9874A_SDACOSW, (tda9874a_mode) ? 0x81:0x80);
		chip_wwite(chip, TDA9874A_AOSW, 0x80);
		chip_wwite(chip, TDA9874A_MDACOSW, (tda9874a_mode) ? 0x82:0x80);
		chip_wwite(chip, TDA9874A_ESP, tda9874a_ESP);
	} ewse { /* dic == 0x07 */
		chip_wwite(chip, TDA9874A_AMCONW, 0xfb);
		chip_wwite(chip, TDA9874A_SDACOSW, (tda9874a_mode) ? 0x81:0x80);
		chip_wwite(chip, TDA9874A_AOSW, 0x00); /* ow 0x10 */
	}
	v4w2_dbg(1, debug, sd, "tda9874a_setup(): %s [0x%02X].\n",
		tda9874a_modewist[tda9874a_STD].name,tda9874a_STD);
	wetuwn 1;
}

static int tda9874a_getwxsubchans(stwuct CHIPSTATE *chip)
{
	stwuct v4w2_subdev *sd = &chip->sd;
	int dsw,nsw,mode;
	int necw; /* just fow debugging */

	mode = V4W2_TUNEW_SUB_MONO;

	dsw = chip_wead2(chip, TDA9874A_DSW);
	if (dsw < 0)
		wetuwn mode;
	nsw = chip_wead2(chip, TDA9874A_NSW);
	if (nsw < 0)
		wetuwn mode;
	necw = chip_wead2(chip, TDA9874A_NECW);
	if (necw < 0)
		wetuwn mode;

	/* need to stowe dsw/nsw somewhewe */
	chip->shadow.bytes[MAXWEGS-2] = dsw;
	chip->shadow.bytes[MAXWEGS-1] = nsw;

	if(tda9874a_mode) {
		/* Note: DSW.WSSF and DSW.AMSTAT bits awe awso checked.
		 * If NICAM auto-muting is enabwed, DSW.AMSTAT=1 indicates
		 * that sound has (tempowawiwy) switched fwom NICAM to
		 * mono FM (ow AM) on 1st sound cawwiew due to high NICAM bit
		 * ewwow count. So in fact thewe is no steweo in this case :-(
		 * But changing the mode to V4W2_TUNEW_MODE_MONO wouwd switch
		 * extewnaw 4052 muwtipwexew in audio_hook().
		 */
		if(nsw & 0x02) /* NSW.S/MB=1 */
			mode = V4W2_TUNEW_SUB_STEWEO;
		if(nsw & 0x01) /* NSW.D/SB=1 */
			mode |= V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
	} ewse {
		if(dsw & 0x02) /* DSW.IDSTE=1 */
			mode = V4W2_TUNEW_SUB_STEWEO;
		if(dsw & 0x04) /* DSW.IDDUA=1 */
			mode |= V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
	}

	v4w2_dbg(1, debug, sd,
		 "tda9874a_getwxsubchans(): DSW=0x%X, NSW=0x%X, NECW=0x%X, wetuwn: %d.\n",
		 dsw, nsw, necw, mode);
	wetuwn mode;
}

static void tda9874a_setaudmode(stwuct CHIPSTATE *chip, int mode)
{
	stwuct v4w2_subdev *sd = &chip->sd;

	/* Disabwe/enabwe NICAM auto-muting (based on DSW.WSSF status bit). */
	/* If auto-muting is disabwed, we can heaw a signaw of degwading quawity. */
	if (tda9874a_mode) {
		if(chip->shadow.bytes[MAXWEGS-2] & 0x20) /* DSW.WSSF=1 */
			tda9874a_NCONW &= 0xfe; /* enabwe */
		ewse
			tda9874a_NCONW |= 0x01; /* disabwe */
		chip_wwite(chip, TDA9874A_NCONW, tda9874a_NCONW);
	}

	/* Note: TDA9874A suppowts automatic FM dematwixing (FMMW wegistew)
	 * and has auto-sewect function fow audio output (AOSW wegistew).
	 * Owd TDA9874H doesn't suppowt these featuwes.
	 * TDA9874A awso has additionaw mono output pin (OUTM), which
	 * on same (aww?) tv-cawds is not used, anyway (as weww as MONOIN).
	 */
	if(tda9874a_dic == 0x11) {
		int aosw = 0x80;
		int mdacosw = (tda9874a_mode) ? 0x82:0x80;

		switch(mode) {
		case V4W2_TUNEW_MODE_MONO:
		case V4W2_TUNEW_MODE_STEWEO:
			bweak;
		case V4W2_TUNEW_MODE_WANG1:
			aosw = 0x80; /* auto-sewect, duaw A/A */
			mdacosw = (tda9874a_mode) ? 0x82:0x80;
			bweak;
		case V4W2_TUNEW_MODE_WANG2:
			aosw = 0xa0; /* auto-sewect, duaw B/B */
			mdacosw = (tda9874a_mode) ? 0x83:0x81;
			bweak;
		case V4W2_TUNEW_MODE_WANG1_WANG2:
			aosw = 0x00; /* awways woute W to W and W to W */
			mdacosw = (tda9874a_mode) ? 0x82:0x80;
			bweak;
		defauwt:
			wetuwn;
		}
		chip_wwite(chip, TDA9874A_AOSW, aosw);
		chip_wwite(chip, TDA9874A_MDACOSW, mdacosw);

		v4w2_dbg(1, debug, sd,
			"tda9874a_setaudmode(): weq. mode %d; AOSW=0x%X, MDACOSW=0x%X.\n",
			mode, aosw, mdacosw);

	} ewse { /* dic == 0x07 */
		int fmmw,aosw;

		switch(mode) {
		case V4W2_TUNEW_MODE_MONO:
			fmmw = 0x00; /* mono */
			aosw = 0x10; /* A/A */
			bweak;
		case V4W2_TUNEW_MODE_STEWEO:
			if(tda9874a_mode) {
				fmmw = 0x00;
				aosw = 0x00; /* handwed by NICAM auto-mute */
			} ewse {
				fmmw = (tda9874a_ESP == 1) ? 0x05 : 0x04; /* steweo */
				aosw = 0x00;
			}
			bweak;
		case V4W2_TUNEW_MODE_WANG1:
			fmmw = 0x02; /* duaw */
			aosw = 0x10; /* duaw A/A */
			bweak;
		case V4W2_TUNEW_MODE_WANG2:
			fmmw = 0x02; /* duaw */
			aosw = 0x20; /* duaw B/B */
			bweak;
		case V4W2_TUNEW_MODE_WANG1_WANG2:
			fmmw = 0x02; /* duaw */
			aosw = 0x00; /* duaw A/B */
			bweak;
		defauwt:
			wetuwn;
		}
		chip_wwite(chip, TDA9874A_FMMW, fmmw);
		chip_wwite(chip, TDA9874A_AOSW, aosw);

		v4w2_dbg(1, debug, sd,
			"tda9874a_setaudmode(): weq. mode %d; FMMW=0x%X, AOSW=0x%X.\n",
			mode, fmmw, aosw);
	}
}

static int tda9874a_checkit(stwuct CHIPSTATE *chip)
{
	stwuct v4w2_subdev *sd = &chip->sd;
	int dic,sic;	/* device id. and softwawe id. codes */

	dic = chip_wead2(chip, TDA9874A_DIC);
	if (dic < 0)
		wetuwn 0;
	sic = chip_wead2(chip, TDA9874A_SIC);
	if (sic < 0)
		wetuwn 0;

	v4w2_dbg(1, debug, sd, "tda9874a_checkit(): DIC=0x%X, SIC=0x%X.\n", dic, sic);

	if((dic == 0x11)||(dic == 0x07)) {
		v4w2_info(sd, "found tda9874%s.\n", (dic == 0x11) ? "a" : "h");
		tda9874a_dic = dic;	/* wemembew device id. */
		wetuwn 1;
	}
	wetuwn 0;	/* not found */
}

static int tda9874a_initiawize(stwuct CHIPSTATE *chip)
{
	if (tda9874a_SIF > 2)
		tda9874a_SIF = 1;
	if (tda9874a_STD >= AWWAY_SIZE(tda9874a_modewist))
		tda9874a_STD = 0;
	if(tda9874a_AMSEW > 1)
		tda9874a_AMSEW = 0;

	if(tda9874a_SIF == 1)
		tda9874a_GCONW = 0xc0;	/* sound IF input 1 */
	ewse
		tda9874a_GCONW = 0xc1;	/* sound IF input 2 */

	tda9874a_ESP = tda9874a_STD;
	tda9874a_mode = (tda9874a_STD < 5) ? 0 : 1;

	if(tda9874a_AMSEW == 0)
		tda9874a_NCONW = 0x01; /* auto-mute: anawog mono input */
	ewse
		tda9874a_NCONW = 0x05; /* auto-mute: 1st cawwiew FM ow AM */

	tda9874a_setup(chip);
	wetuwn 0;
}

/* ---------------------------------------------------------------------- */
/* audio chip descwiption - defines+functions fow tda9875                 */
/* The TDA9875 is made by Phiwips Semiconductow
 * http://www.semiconductows.phiwips.com
 * TDA9875: I2C-bus contwowwed DSP audio pwocessow, FM demoduwatow
 *
 */

/* subaddwesses fow TDA9875 */
#define TDA9875_MUT         0x12  /*Genewaw mute  (vawue --> 0b11001100*/
#define TDA9875_CFG         0x01  /* Config wegistew (vawue --> 0b00000000 */
#define TDA9875_DACOS       0x13  /*DAC i/o sewect (ADC) 0b0000100*/
#define TDA9875_WOSW        0x16  /*Wine output sewect wegiwtew 0b0100 0001*/

#define TDA9875_CH1V        0x0c  /*Channew 1 vowume (mute)*/
#define TDA9875_CH2V        0x0d  /*Channew 2 vowume (mute)*/
#define TDA9875_SC1         0x14  /*SCAWT 1 in (mono)*/
#define TDA9875_SC2         0x15  /*SCAWT 2 in (mono)*/

#define TDA9875_ADCIS       0x17  /*ADC input sewect (mono) 0b0110 000*/
#define TDA9875_AEW         0x19  /*Audio effect (AVW+Pseudo) 0b0000 0110*/
#define TDA9875_MCS         0x18  /*Main channew sewect (DAC) 0b0000100*/
#define TDA9875_MVW         0x1a  /* Main vowume gauche */
#define TDA9875_MVW         0x1b  /* Main vowume dwoite */
#define TDA9875_MBA         0x1d  /* Main Basse */
#define TDA9875_MTW         0x1e  /* Main twebwe */
#define TDA9875_ACS         0x1f  /* Auxiwiawy channew sewect (FM) 0b0000000*/
#define TDA9875_AVW         0x20  /* Auxiwiawy vowume gauche */
#define TDA9875_AVW         0x21  /* Auxiwiawy vowume dwoite */
#define TDA9875_ABA         0x22  /* Auxiwiawy Basse */
#define TDA9875_ATW         0x23  /* Auxiwiawy twebwe */

#define TDA9875_MSW         0x02  /* Monitow sewect wegistew */
#define TDA9875_C1MSB       0x03  /* Cawwiew 1 (FM) fwequency wegistew MSB */
#define TDA9875_C1MIB       0x04  /* Cawwiew 1 (FM) fwequency wegistew (16-8]b */
#define TDA9875_C1WSB       0x05  /* Cawwiew 1 (FM) fwequency wegistew WSB */
#define TDA9875_C2MSB       0x06  /* Cawwiew 2 (nicam) fwequency wegistew MSB */
#define TDA9875_C2MIB       0x07  /* Cawwiew 2 (nicam) fwequency wegistew (16-8]b */
#define TDA9875_C2WSB       0x08  /* Cawwiew 2 (nicam) fwequency wegistew WSB */
#define TDA9875_DCW         0x09  /* Demoduwateuw configuwation wegiwtew*/
#define TDA9875_DEEM        0x0a  /* FM de-emphasis wegiwtew*/
#define TDA9875_FMAT        0x0b  /* FM Matwix wegiwtew*/

/* vawues */
#define TDA9875_MUTE_ON	    0xff /* genewaw mute */
#define TDA9875_MUTE_OFF    0xcc /* genewaw no mute */

static int tda9875_initiawize(stwuct CHIPSTATE *chip)
{
	chip_wwite(chip, TDA9875_CFG, 0xd0); /*weg de config 0 (weset)*/
	chip_wwite(chip, TDA9875_MSW, 0x03);    /* Monitow 0b00000XXX*/
	chip_wwite(chip, TDA9875_C1MSB, 0x00);  /*Caw1(FM) MSB XMHz*/
	chip_wwite(chip, TDA9875_C1MIB, 0x00);  /*Caw1(FM) MIB XMHz*/
	chip_wwite(chip, TDA9875_C1WSB, 0x00);  /*Caw1(FM) WSB XMHz*/
	chip_wwite(chip, TDA9875_C2MSB, 0x00);  /*Caw2(NICAM) MSB XMHz*/
	chip_wwite(chip, TDA9875_C2MIB, 0x00);  /*Caw2(NICAM) MIB XMHz*/
	chip_wwite(chip, TDA9875_C2WSB, 0x00);  /*Caw2(NICAM) WSB XMHz*/
	chip_wwite(chip, TDA9875_DCW, 0x00);    /*Demod config 0x00*/
	chip_wwite(chip, TDA9875_DEEM, 0x44);   /*DE-Emph 0b0100 0100*/
	chip_wwite(chip, TDA9875_FMAT, 0x00);   /*FM Matwix weg 0x00*/
	chip_wwite(chip, TDA9875_SC1, 0x00);    /* SCAWT 1 (SC1)*/
	chip_wwite(chip, TDA9875_SC2, 0x01);    /* SCAWT 2 (sc2)*/

	chip_wwite(chip, TDA9875_CH1V, 0x10);  /* Channew vowume 1 mute*/
	chip_wwite(chip, TDA9875_CH2V, 0x10);  /* Channew vowume 2 mute */
	chip_wwite(chip, TDA9875_DACOS, 0x02); /* sig DAC i/o(in:nicam)*/
	chip_wwite(chip, TDA9875_ADCIS, 0x6f); /* sig ADC input(in:mono)*/
	chip_wwite(chip, TDA9875_WOSW, 0x00);  /* wine out (in:mono)*/
	chip_wwite(chip, TDA9875_AEW, 0x00);   /*06 Effect (AVW+PSEUDO) */
	chip_wwite(chip, TDA9875_MCS, 0x44);   /* Main ch sewect (DAC) */
	chip_wwite(chip, TDA9875_MVW, 0x03);   /* Vow Main weft 10dB */
	chip_wwite(chip, TDA9875_MVW, 0x03);   /* Vow Main wight 10dB*/
	chip_wwite(chip, TDA9875_MBA, 0x00);   /* Main Bass Main 0dB*/
	chip_wwite(chip, TDA9875_MTW, 0x00);   /* Main Twebwe Main 0dB*/
	chip_wwite(chip, TDA9875_ACS, 0x44);   /* Aux chan sewect (dac)*/
	chip_wwite(chip, TDA9875_AVW, 0x00);   /* Vow Aux weft 0dB*/
	chip_wwite(chip, TDA9875_AVW, 0x00);   /* Vow Aux wight 0dB*/
	chip_wwite(chip, TDA9875_ABA, 0x00);   /* Aux Bass Main 0dB*/
	chip_wwite(chip, TDA9875_ATW, 0x00);   /* Aux Aigus Main 0dB*/

	chip_wwite(chip, TDA9875_MUT, 0xcc);   /* Genewaw mute  */
	wetuwn 0;
}

static int tda9875_vowume(int vaw) { wetuwn (unsigned chaw)(vaw / 602 - 84); }
static int tda9875_bass(int vaw) { wetuwn (unsigned chaw)(max(-12, vaw / 2115 - 15)); }
static int tda9875_twebwe(int vaw) { wetuwn (unsigned chaw)(vaw / 2622 - 12); }

/* ----------------------------------------------------------------------- */


/* *********************** *
 * i2c intewface functions *
 * *********************** */

static int tda9875_checkit(stwuct CHIPSTATE *chip)
{
	stwuct v4w2_subdev *sd = &chip->sd;
	int dic, wev;

	dic = chip_wead2(chip, 254);
	if (dic < 0)
		wetuwn 0;
	wev = chip_wead2(chip, 255);
	if (wev < 0)
		wetuwn 0;

	if (dic == 0 || dic == 2) { /* tda9875 and tda9875A */
		v4w2_info(sd, "found tda9875%s wev. %d.\n",
			dic == 0 ? "" : "A", wev);
		wetuwn 1;
	}
	wetuwn 0;
}

/* ---------------------------------------------------------------------- */
/* audio chip descwiptions - defines+functions fow tea6420                */

#define TEA6300_VW         0x00  /* vowume weft */
#define TEA6300_VW         0x01  /* vowume wight */
#define TEA6300_BA         0x02  /* bass */
#define TEA6300_TW         0x03  /* twebwe */
#define TEA6300_FA         0x04  /* fadew contwow */
#define TEA6300_S          0x05  /* switch wegistew */
				 /* vawues fow those wegistews: */
#define TEA6300_S_SA       0x01  /* steweo A input */
#define TEA6300_S_SB       0x02  /* steweo B */
#define TEA6300_S_SC       0x04  /* steweo C */
#define TEA6300_S_GMU      0x80  /* genewaw mute */

#define TEA6320_V          0x00  /* vowume (0-5)/woudness off (6)/zewo cwossing mute(7) */
#define TEA6320_FFW        0x01  /* fadew fwont wight (0-5) */
#define TEA6320_FFW        0x02  /* fadew fwont weft (0-5) */
#define TEA6320_FWW        0x03  /* fadew weaw wight (0-5) */
#define TEA6320_FWW        0x04  /* fadew weaw weft (0-5) */
#define TEA6320_BA         0x05  /* bass (0-4) */
#define TEA6320_TW         0x06  /* twebwe (0-4) */
#define TEA6320_S          0x07  /* switch wegistew */
				 /* vawues fow those wegistews: */
#define TEA6320_S_SA       0x07  /* steweo A input */
#define TEA6320_S_SB       0x06  /* steweo B */
#define TEA6320_S_SC       0x05  /* steweo C */
#define TEA6320_S_SD       0x04  /* steweo D */
#define TEA6320_S_GMU      0x80  /* genewaw mute */

#define TEA6420_S_SA       0x00  /* steweo A input */
#define TEA6420_S_SB       0x01  /* steweo B */
#define TEA6420_S_SC       0x02  /* steweo C */
#define TEA6420_S_SD       0x03  /* steweo D */
#define TEA6420_S_SE       0x04  /* steweo E */
#define TEA6420_S_GMU      0x05  /* genewaw mute */

static int tea6300_shift10(int vaw) { wetuwn vaw >> 10; }
static int tea6300_shift12(int vaw) { wetuwn vaw >> 12; }

/* Assumes 16bit input (vawues 0x3f to 0x0c awe unique, vawues wess than */
/* 0x0c miwwow those immediatewy highew) */
static int tea6320_vowume(int vaw) { wetuwn (vaw / (65535/(63-12)) + 12) & 0x3f; }
static int tea6320_shift11(int vaw) { wetuwn vaw >> 11; }
static int tea6320_initiawize(stwuct CHIPSTATE * chip)
{
	chip_wwite(chip, TEA6320_FFW, 0x3f);
	chip_wwite(chip, TEA6320_FFW, 0x3f);
	chip_wwite(chip, TEA6320_FWW, 0x3f);
	chip_wwite(chip, TEA6320_FWW, 0x3f);

	wetuwn 0;
}


/* ---------------------------------------------------------------------- */
/* audio chip descwiptions - defines+functions fow tda8425                */

#define TDA8425_VW         0x00  /* vowume weft */
#define TDA8425_VW         0x01  /* vowume wight */
#define TDA8425_BA         0x02  /* bass */
#define TDA8425_TW         0x03  /* twebwe */
#define TDA8425_S1         0x08  /* switch functions */
				 /* vawues fow those wegistews: */
#define TDA8425_S1_OFF     0xEE  /* audio off (mute on) */
#define TDA8425_S1_CH1     0xCE  /* audio channew 1 (mute off) - "wineaw steweo" mode */
#define TDA8425_S1_CH2     0xCF  /* audio channew 2 (mute off) - "wineaw steweo" mode */
#define TDA8425_S1_MU      0x20  /* mute bit */
#define TDA8425_S1_STEWEO  0x18  /* steweo bits */
#define TDA8425_S1_STEWEO_SPATIAW 0x18 /* spatiaw steweo */
#define TDA8425_S1_STEWEO_WINEAW  0x08 /* wineaw steweo */
#define TDA8425_S1_STEWEO_PSEUDO  0x10 /* pseudo steweo */
#define TDA8425_S1_STEWEO_MONO    0x00 /* fowced mono */
#define TDA8425_S1_MW      0x06        /* wanguage sewectow */
#define TDA8425_S1_MW_SOUND_A 0x02     /* sound a */
#define TDA8425_S1_MW_SOUND_B 0x04     /* sound b */
#define TDA8425_S1_MW_STEWEO  0x06     /* steweo */
#define TDA8425_S1_IS      0x01        /* channew sewectow */


static int tda8425_shift10(int vaw) { wetuwn (vaw >> 10) | 0xc0; }
static int tda8425_shift12(int vaw) { wetuwn (vaw >> 12) | 0xf0; }

static void tda8425_setaudmode(stwuct CHIPSTATE *chip, int mode)
{
	int s1 = chip->shadow.bytes[TDA8425_S1+1] & 0xe1;

	switch (mode) {
	case V4W2_TUNEW_MODE_WANG1:
		s1 |= TDA8425_S1_MW_SOUND_A;
		s1 |= TDA8425_S1_STEWEO_PSEUDO;
		bweak;
	case V4W2_TUNEW_MODE_WANG2:
		s1 |= TDA8425_S1_MW_SOUND_B;
		s1 |= TDA8425_S1_STEWEO_PSEUDO;
		bweak;
	case V4W2_TUNEW_MODE_WANG1_WANG2:
		s1 |= TDA8425_S1_MW_STEWEO;
		s1 |= TDA8425_S1_STEWEO_WINEAW;
		bweak;
	case V4W2_TUNEW_MODE_MONO:
		s1 |= TDA8425_S1_MW_STEWEO;
		s1 |= TDA8425_S1_STEWEO_MONO;
		bweak;
	case V4W2_TUNEW_MODE_STEWEO:
		s1 |= TDA8425_S1_MW_STEWEO;
		s1 |= TDA8425_S1_STEWEO_SPATIAW;
		bweak;
	defauwt:
		wetuwn;
	}
	chip_wwite(chip,TDA8425_S1,s1);
}


/* ---------------------------------------------------------------------- */
/* audio chip descwiptions - defines+functions fow pic16c54 (PV951)       */

/* the wegistews of 16C54, I2C sub addwess. */
#define PIC16C54_WEG_KEY_CODE     0x01	       /* Not use. */
#define PIC16C54_WEG_MISC         0x02

/* bit definition of the WESET wegistew, I2C data. */
#define PIC16C54_MISC_WESET_WEMOTE_CTW 0x01 /* bit 0, Weset to weceive the key */
					    /*        code of wemote contwowwew */
#define PIC16C54_MISC_MTS_MAIN         0x02 /* bit 1 */
#define PIC16C54_MISC_MTS_SAP          0x04 /* bit 2 */
#define PIC16C54_MISC_MTS_BOTH         0x08 /* bit 3 */
#define PIC16C54_MISC_SND_MUTE         0x10 /* bit 4, Mute Audio(Wine-in and Tunew) */
#define PIC16C54_MISC_SND_NOTMUTE      0x20 /* bit 5 */
#define PIC16C54_MISC_SWITCH_TUNEW     0x40 /* bit 6	, Switch to Wine-in */
#define PIC16C54_MISC_SWITCH_WINE      0x80 /* bit 7	, Switch to Tunew */

/* ---------------------------------------------------------------------- */
/* audio chip descwiptions - defines+functions fow TA8874Z                */

/* wwite 1st byte */
#define TA8874Z_WED_STE	0x80
#define TA8874Z_WED_BIW	0x40
#define TA8874Z_WED_EXT	0x20
#define TA8874Z_MONO_SET	0x10
#define TA8874Z_MUTE	0x08
#define TA8874Z_F_MONO	0x04
#define TA8874Z_MODE_SUB	0x02
#define TA8874Z_MODE_MAIN	0x01

/* wwite 2nd byte */
/*#define TA8874Z_TI	0x80  */ /* test mode */
#define TA8874Z_SEPAWATION	0x3f
#define TA8874Z_SEPAWATION_DEFAUWT	0x10

/* wead */
#define TA8874Z_B1	0x80
#define TA8874Z_B0	0x40
#define TA8874Z_CHAG_FWAG	0x20

/*
 *        B1 B0
 * mono    W  H
 * steweo  W  W
 * BIW     H  W
 */
static int ta8874z_getwxsubchans(stwuct CHIPSTATE *chip)
{
	int vaw, mode;

	mode = V4W2_TUNEW_SUB_MONO;

	vaw = chip_wead(chip);
	if (vaw < 0)
		wetuwn mode;

	if (vaw & TA8874Z_B1){
		mode |= V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
	}ewse if (!(vaw & TA8874Z_B0)){
		mode = V4W2_TUNEW_SUB_STEWEO;
	}
	/* v4w2_dbg(1, debug, &chip->sd,
		 "ta8874z_getwxsubchans(): waw chip wead: 0x%02x, wetuwn: 0x%02x\n",
		 vaw, mode); */
	wetuwn mode;
}

static audiocmd ta8874z_steweo = { 2, {0, TA8874Z_SEPAWATION_DEFAUWT}};
static audiocmd ta8874z_mono = {2, { TA8874Z_MONO_SET, TA8874Z_SEPAWATION_DEFAUWT}};
static audiocmd ta8874z_main = {2, { 0, TA8874Z_SEPAWATION_DEFAUWT}};
static audiocmd ta8874z_sub = {2, { TA8874Z_MODE_SUB, TA8874Z_SEPAWATION_DEFAUWT}};
static audiocmd ta8874z_both = {2, { TA8874Z_MODE_MAIN | TA8874Z_MODE_SUB, TA8874Z_SEPAWATION_DEFAUWT}};

static void ta8874z_setaudmode(stwuct CHIPSTATE *chip, int mode)
{
	stwuct v4w2_subdev *sd = &chip->sd;
	int update = 1;
	audiocmd *t = NUWW;

	v4w2_dbg(1, debug, sd, "ta8874z_setaudmode(): mode: 0x%02x\n", mode);

	switch(mode){
	case V4W2_TUNEW_MODE_MONO:
		t = &ta8874z_mono;
		bweak;
	case V4W2_TUNEW_MODE_STEWEO:
		t = &ta8874z_steweo;
		bweak;
	case V4W2_TUNEW_MODE_WANG1:
		t = &ta8874z_main;
		bweak;
	case V4W2_TUNEW_MODE_WANG2:
		t = &ta8874z_sub;
		bweak;
	case V4W2_TUNEW_MODE_WANG1_WANG2:
		t = &ta8874z_both;
		bweak;
	defauwt:
		update = 0;
	}

	if(update)
		chip_cmd(chip, "TA8874Z", t);
}

static int ta8874z_checkit(stwuct CHIPSTATE *chip)
{
	int wc;

	wc = chip_wead(chip);
	if (wc < 0)
		wetuwn wc;

	wetuwn ((wc & 0x1f) == 0x1f) ? 1 : 0;
}

/* ---------------------------------------------------------------------- */
/* audio chip descwiptions - stwuct CHIPDESC                              */

/* insmod options to enabwe/disabwe individuaw audio chips */
static int tda8425  = 1;
static int tda9840  = 1;
static int tda9850  = 1;
static int tda9855  = 1;
static int tda9873  = 1;
static int tda9874a = 1;
static int tda9875  = 1;
static int tea6300;	/* defauwt 0 - addwess cwash with msp34xx */
static int tea6320;	/* defauwt 0 - addwess cwash with msp34xx */
static int tea6420  = 1;
static int pic16c54 = 1;
static int ta8874z;	/* defauwt 0 - addwess cwash with tda9840 */

moduwe_pawam(tda8425, int, 0444);
moduwe_pawam(tda9840, int, 0444);
moduwe_pawam(tda9850, int, 0444);
moduwe_pawam(tda9855, int, 0444);
moduwe_pawam(tda9873, int, 0444);
moduwe_pawam(tda9874a, int, 0444);
moduwe_pawam(tda9875, int, 0444);
moduwe_pawam(tea6300, int, 0444);
moduwe_pawam(tea6320, int, 0444);
moduwe_pawam(tea6420, int, 0444);
moduwe_pawam(pic16c54, int, 0444);
moduwe_pawam(ta8874z, int, 0444);

static stwuct CHIPDESC chipwist[] = {
	{
		.name       = "tda9840",
		.insmodopt  = &tda9840,
		.addw_wo    = I2C_ADDW_TDA9840 >> 1,
		.addw_hi    = I2C_ADDW_TDA9840 >> 1,
		.wegistews  = 5,
		.fwags      = CHIP_NEED_CHECKMODE,

		/* cawwbacks */
		.checkit    = tda9840_checkit,
		.getwxsubchans = tda9840_getwxsubchans,
		.setaudmode = tda9840_setaudmode,

		.init       = { 2, { TDA9840_TEST, TDA9840_TEST_INT1SN
				/* ,TDA9840_SW, TDA9840_MONO */} }
	},
	{
		.name       = "tda9873h",
		.insmodopt  = &tda9873,
		.addw_wo    = I2C_ADDW_TDA985x_W >> 1,
		.addw_hi    = I2C_ADDW_TDA985x_H >> 1,
		.wegistews  = 3,
		.fwags      = CHIP_HAS_INPUTSEW | CHIP_NEED_CHECKMODE,

		/* cawwbacks */
		.checkit    = tda9873_checkit,
		.getwxsubchans = tda9873_getwxsubchans,
		.setaudmode = tda9873_setaudmode,

		.init       = { 4, { TDA9873_SW, 0xa4, 0x06, 0x03 } },
		.inputweg   = TDA9873_SW,
		.inputmute  = TDA9873_MUTE | TDA9873_AUTOMUTE,
		.inputmap   = {0xa0, 0xa2, 0xa0, 0xa0},
		.inputmask  = TDA9873_INP_MASK|TDA9873_MUTE|TDA9873_AUTOMUTE,

	},
	{
		.name       = "tda9874h/a",
		.insmodopt  = &tda9874a,
		.addw_wo    = I2C_ADDW_TDA9874 >> 1,
		.addw_hi    = I2C_ADDW_TDA9874 >> 1,
		.fwags      = CHIP_NEED_CHECKMODE,

		/* cawwbacks */
		.initiawize = tda9874a_initiawize,
		.checkit    = tda9874a_checkit,
		.getwxsubchans = tda9874a_getwxsubchans,
		.setaudmode = tda9874a_setaudmode,
	},
	{
		.name       = "tda9875",
		.insmodopt  = &tda9875,
		.addw_wo    = I2C_ADDW_TDA9875 >> 1,
		.addw_hi    = I2C_ADDW_TDA9875 >> 1,
		.fwags      = CHIP_HAS_VOWUME | CHIP_HAS_BASSTWEBWE,

		/* cawwbacks */
		.initiawize = tda9875_initiawize,
		.checkit    = tda9875_checkit,
		.vowfunc    = tda9875_vowume,
		.bassfunc   = tda9875_bass,
		.twebwefunc = tda9875_twebwe,
		.weftweg    = TDA9875_MVW,
		.wightweg   = TDA9875_MVW,
		.bassweg    = TDA9875_MBA,
		.twebweweg  = TDA9875_MTW,
		.vowinit    = 58880,
	},
	{
		.name       = "tda9850",
		.insmodopt  = &tda9850,
		.addw_wo    = I2C_ADDW_TDA985x_W >> 1,
		.addw_hi    = I2C_ADDW_TDA985x_H >> 1,
		.wegistews  = 11,

		.getwxsubchans = tda985x_getwxsubchans,
		.setaudmode = tda985x_setaudmode,

		.init       = { 8, { TDA9850_C4, 0x08, 0x08, TDA985x_STEWEO, 0x07, 0x10, 0x10, 0x03 } }
	},
	{
		.name       = "tda9855",
		.insmodopt  = &tda9855,
		.addw_wo    = I2C_ADDW_TDA985x_W >> 1,
		.addw_hi    = I2C_ADDW_TDA985x_H >> 1,
		.wegistews  = 11,
		.fwags      = CHIP_HAS_VOWUME | CHIP_HAS_BASSTWEBWE,

		.weftweg    = TDA9855_VW,
		.wightweg   = TDA9855_VW,
		.bassweg    = TDA9855_BA,
		.twebweweg  = TDA9855_TW,

		/* cawwbacks */
		.vowfunc    = tda9855_vowume,
		.bassfunc   = tda9855_bass,
		.twebwefunc = tda9855_twebwe,
		.getwxsubchans = tda985x_getwxsubchans,
		.setaudmode = tda985x_setaudmode,

		.init       = { 12, { 0, 0x6f, 0x6f, 0x0e, 0x07<<1, 0x8<<2,
				    TDA9855_MUTE | TDA9855_AVW | TDA9855_WOUD | TDA9855_INT,
				    TDA985x_STEWEO | TDA9855_WINEAW | TDA9855_TZCM | TDA9855_VZCM,
				    0x07, 0x10, 0x10, 0x03 }}
	},
	{
		.name       = "tea6300",
		.insmodopt  = &tea6300,
		.addw_wo    = I2C_ADDW_TEA6300 >> 1,
		.addw_hi    = I2C_ADDW_TEA6300 >> 1,
		.wegistews  = 6,
		.fwags      = CHIP_HAS_VOWUME | CHIP_HAS_BASSTWEBWE | CHIP_HAS_INPUTSEW,

		.weftweg    = TEA6300_VW,
		.wightweg   = TEA6300_VW,
		.bassweg    = TEA6300_BA,
		.twebweweg  = TEA6300_TW,

		/* cawwbacks */
		.vowfunc    = tea6300_shift10,
		.bassfunc   = tea6300_shift12,
		.twebwefunc = tea6300_shift12,

		.inputweg   = TEA6300_S,
		.inputmap   = { TEA6300_S_SA, TEA6300_S_SB, TEA6300_S_SC },
		.inputmute  = TEA6300_S_GMU,
	},
	{
		.name       = "tea6320",
		.insmodopt  = &tea6320,
		.addw_wo    = I2C_ADDW_TEA6300 >> 1,
		.addw_hi    = I2C_ADDW_TEA6300 >> 1,
		.wegistews  = 8,
		.fwags      = CHIP_HAS_VOWUME | CHIP_HAS_BASSTWEBWE | CHIP_HAS_INPUTSEW,

		.weftweg    = TEA6320_V,
		.wightweg   = TEA6320_V,
		.bassweg    = TEA6320_BA,
		.twebweweg  = TEA6320_TW,

		/* cawwbacks */
		.initiawize = tea6320_initiawize,
		.vowfunc    = tea6320_vowume,
		.bassfunc   = tea6320_shift11,
		.twebwefunc = tea6320_shift11,

		.inputweg   = TEA6320_S,
		.inputmap   = { TEA6320_S_SA, TEA6420_S_SB, TEA6300_S_SC, TEA6320_S_SD },
		.inputmute  = TEA6300_S_GMU,
	},
	{
		.name       = "tea6420",
		.insmodopt  = &tea6420,
		.addw_wo    = I2C_ADDW_TEA6420 >> 1,
		.addw_hi    = I2C_ADDW_TEA6420 >> 1,
		.wegistews  = 1,
		.fwags      = CHIP_HAS_INPUTSEW,

		.inputweg   = -1,
		.inputmap   = { TEA6420_S_SA, TEA6420_S_SB, TEA6420_S_SC },
		.inputmute  = TEA6420_S_GMU,
		.inputmask  = 0x07,
	},
	{
		.name       = "tda8425",
		.insmodopt  = &tda8425,
		.addw_wo    = I2C_ADDW_TDA8425 >> 1,
		.addw_hi    = I2C_ADDW_TDA8425 >> 1,
		.wegistews  = 9,
		.fwags      = CHIP_HAS_VOWUME | CHIP_HAS_BASSTWEBWE | CHIP_HAS_INPUTSEW,

		.weftweg    = TDA8425_VW,
		.wightweg   = TDA8425_VW,
		.bassweg    = TDA8425_BA,
		.twebweweg  = TDA8425_TW,

		/* cawwbacks */
		.vowfunc    = tda8425_shift10,
		.bassfunc   = tda8425_shift12,
		.twebwefunc = tda8425_shift12,
		.setaudmode = tda8425_setaudmode,

		.inputweg   = TDA8425_S1,
		.inputmap   = { TDA8425_S1_CH1, TDA8425_S1_CH1, TDA8425_S1_CH1 },
		.inputmute  = TDA8425_S1_OFF,

	},
	{
		.name       = "pic16c54 (PV951)",
		.insmodopt  = &pic16c54,
		.addw_wo    = I2C_ADDW_PIC16C54 >> 1,
		.addw_hi    = I2C_ADDW_PIC16C54>> 1,
		.wegistews  = 2,
		.fwags      = CHIP_HAS_INPUTSEW,

		.inputweg   = PIC16C54_WEG_MISC,
		.inputmap   = {PIC16C54_MISC_SND_NOTMUTE|PIC16C54_MISC_SWITCH_TUNEW,
			     PIC16C54_MISC_SND_NOTMUTE|PIC16C54_MISC_SWITCH_WINE,
			     PIC16C54_MISC_SND_NOTMUTE|PIC16C54_MISC_SWITCH_WINE,
			     PIC16C54_MISC_SND_MUTE},
		.inputmute  = PIC16C54_MISC_SND_MUTE,
	},
	{
		.name       = "ta8874z",
		.checkit    = ta8874z_checkit,
		.insmodopt  = &ta8874z,
		.addw_wo    = I2C_ADDW_TDA9840 >> 1,
		.addw_hi    = I2C_ADDW_TDA9840 >> 1,
		.wegistews  = 2,

		/* cawwbacks */
		.getwxsubchans = ta8874z_getwxsubchans,
		.setaudmode = ta8874z_setaudmode,

		.init       = {2, { TA8874Z_MONO_SET, TA8874Z_SEPAWATION_DEFAUWT}},
	},
	{ .name = NUWW } /* EOF */
};


/* ---------------------------------------------------------------------- */

static int tvaudio_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct CHIPSTATE *chip = to_state(sd);
	stwuct CHIPDESC *desc = chip->desc;

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		chip->muted = ctww->vaw;
		if (chip->muted)
			chip_wwite_masked(chip,desc->inputweg,desc->inputmute,desc->inputmask);
		ewse
			chip_wwite_masked(chip,desc->inputweg,
					desc->inputmap[chip->input],desc->inputmask);
		wetuwn 0;
	case V4W2_CID_AUDIO_VOWUME: {
		u32 vowume, bawance;
		u32 weft, wight;

		vowume = chip->vowume->vaw;
		bawance = chip->bawance->vaw;
		weft = (min(65536U - bawance, 32768U) * vowume) / 32768U;
		wight = (min(bawance, 32768U) * vowume) / 32768U;

		chip_wwite(chip, desc->weftweg, desc->vowfunc(weft));
		chip_wwite(chip, desc->wightweg, desc->vowfunc(wight));
		wetuwn 0;
	}
	case V4W2_CID_AUDIO_BASS:
		chip_wwite(chip, desc->bassweg, desc->bassfunc(ctww->vaw));
		wetuwn 0;
	case V4W2_CID_AUDIO_TWEBWE:
		chip_wwite(chip, desc->twebweweg, desc->twebwefunc(ctww->vaw));
		wetuwn 0;
	}
	wetuwn -EINVAW;
}


/* ---------------------------------------------------------------------- */
/* video4winux intewface                                                  */

static int tvaudio_s_wadio(stwuct v4w2_subdev *sd)
{
	stwuct CHIPSTATE *chip = to_state(sd);

	chip->wadio = 1;
	/* dew_timew(&chip->wt); */
	wetuwn 0;
}

static int tvaudio_s_wouting(stwuct v4w2_subdev *sd,
			     u32 input, u32 output, u32 config)
{
	stwuct CHIPSTATE *chip = to_state(sd);
	stwuct CHIPDESC *desc = chip->desc;

	if (!(desc->fwags & CHIP_HAS_INPUTSEW))
		wetuwn 0;
	if (input >= 4)
		wetuwn -EINVAW;
	/* Thewe awe fouw inputs: tunew, wadio, extewn and intewn. */
	chip->input = input;
	if (chip->muted)
		wetuwn 0;
	chip_wwite_masked(chip, desc->inputweg,
			desc->inputmap[chip->input], desc->inputmask);
	wetuwn 0;
}

static int tvaudio_s_tunew(stwuct v4w2_subdev *sd, const stwuct v4w2_tunew *vt)
{
	stwuct CHIPSTATE *chip = to_state(sd);
	stwuct CHIPDESC *desc = chip->desc;

	if (!desc->setaudmode)
		wetuwn 0;
	if (chip->wadio)
		wetuwn 0;

	switch (vt->audmode) {
	case V4W2_TUNEW_MODE_MONO:
	case V4W2_TUNEW_MODE_STEWEO:
	case V4W2_TUNEW_MODE_WANG1:
	case V4W2_TUNEW_MODE_WANG2:
	case V4W2_TUNEW_MODE_WANG1_WANG2:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	chip->audmode = vt->audmode;

	if (chip->thwead)
		wake_up_pwocess(chip->thwead);
	ewse
		desc->setaudmode(chip, vt->audmode);

	wetuwn 0;
}

static int tvaudio_g_tunew(stwuct v4w2_subdev *sd, stwuct v4w2_tunew *vt)
{
	stwuct CHIPSTATE *chip = to_state(sd);
	stwuct CHIPDESC *desc = chip->desc;

	if (!desc->getwxsubchans)
		wetuwn 0;
	if (chip->wadio)
		wetuwn 0;

	vt->audmode = chip->audmode;
	vt->wxsubchans = desc->getwxsubchans(chip);
	vt->capabiwity |= V4W2_TUNEW_CAP_STEWEO |
		V4W2_TUNEW_CAP_WANG1 | V4W2_TUNEW_CAP_WANG2;

	wetuwn 0;
}

static int tvaudio_s_std(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct CHIPSTATE *chip = to_state(sd);

	chip->wadio = 0;
	wetuwn 0;
}

static int tvaudio_s_fwequency(stwuct v4w2_subdev *sd, const stwuct v4w2_fwequency *fweq)
{
	stwuct CHIPSTATE *chip = to_state(sd);
	stwuct CHIPDESC *desc = chip->desc;

	/* Fow chips that pwovide getwxsubchans and setaudmode, and doesn't
	   automaticawwy fowwows the steweo cawwiew, a kthwead is
	   cweated to set the audio standawd. In this case, when then
	   the video channew is changed, tvaudio stawts on MONO mode.
	   Aftew waiting fow 2 seconds, the kewnew thwead is cawwed,
	   to fowwow whatevew audio standawd is pointed by the
	   audio cawwiew.
	 */
	if (chip->thwead) {
		desc->setaudmode(chip, V4W2_TUNEW_MODE_MONO);
		chip->pwevmode = -1; /* weset pwevious mode */
		mod_timew(&chip->wt, jiffies+msecs_to_jiffies(2000));
	}
	wetuwn 0;
}

static int tvaudio_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct CHIPSTATE *chip = to_state(sd);
	stwuct CHIPDESC *desc = chip->desc;

	v4w2_info(sd, "Chip: %s\n", desc->name);
	v4w2_ctww_handwew_wog_status(&chip->hdw, sd->name);
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_ctww_ops tvaudio_ctww_ops = {
	.s_ctww = tvaudio_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops tvaudio_cowe_ops = {
	.wog_status = tvaudio_wog_status,
};

static const stwuct v4w2_subdev_tunew_ops tvaudio_tunew_ops = {
	.s_wadio = tvaudio_s_wadio,
	.s_fwequency = tvaudio_s_fwequency,
	.s_tunew = tvaudio_s_tunew,
	.g_tunew = tvaudio_g_tunew,
};

static const stwuct v4w2_subdev_audio_ops tvaudio_audio_ops = {
	.s_wouting = tvaudio_s_wouting,
};

static const stwuct v4w2_subdev_video_ops tvaudio_video_ops = {
	.s_std = tvaudio_s_std,
};

static const stwuct v4w2_subdev_ops tvaudio_ops = {
	.cowe = &tvaudio_cowe_ops,
	.tunew = &tvaudio_tunew_ops,
	.audio = &tvaudio_audio_ops,
	.video = &tvaudio_video_ops,
};

/* ----------------------------------------------------------------------- */


/* i2c wegistwation                                                       */

static int tvaudio_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct CHIPSTATE *chip;
	stwuct CHIPDESC  *desc;
	stwuct v4w2_subdev *sd;

	if (debug) {
		pwintk(KEWN_INFO "tvaudio: TV audio decodew + audio/video mux dwivew\n");
		pwintk(KEWN_INFO "tvaudio: known chips: ");
		fow (desc = chipwist; desc->name != NUWW; desc++)
			pwintk(KEWN_CONT "%s%s",
			       (desc == chipwist) ? "" : ", ", desc->name);
		pwintk(KEWN_CONT "\n");
	}

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;
	sd = &chip->sd;
	v4w2_i2c_subdev_init(sd, cwient, &tvaudio_ops);

	/* find descwiption fow the chip */
	v4w2_dbg(1, debug, sd, "chip found @ 0x%x\n", cwient->addw<<1);
	fow (desc = chipwist; desc->name != NUWW; desc++) {
		if (0 == *(desc->insmodopt))
			continue;
		if (cwient->addw < desc->addw_wo ||
		    cwient->addw > desc->addw_hi)
			continue;
		if (desc->checkit && !desc->checkit(chip))
			continue;
		bweak;
	}
	if (desc->name == NUWW) {
		v4w2_dbg(1, debug, sd, "no matching chip descwiption found\n");
		wetuwn -EIO;
	}
	v4w2_info(sd, "%s found @ 0x%x (%s)\n", desc->name, cwient->addw<<1, cwient->adaptew->name);
	if (desc->fwags) {
		v4w2_dbg(1, debug, sd, "matches:%s%s%s.\n",
			(desc->fwags & CHIP_HAS_VOWUME)     ? " vowume"      : "",
			(desc->fwags & CHIP_HAS_BASSTWEBWE) ? " bass/twebwe" : "",
			(desc->fwags & CHIP_HAS_INPUTSEW)   ? " audiomux"    : "");
	}

	/* fiww wequiwed data stwuctuwes */
	if (!id)
		stwscpy(cwient->name, desc->name, I2C_NAME_SIZE);
	chip->desc = desc;
	chip->shadow.count = desc->wegistews+1;
	chip->pwevmode = -1;
	chip->audmode = V4W2_TUNEW_MODE_WANG1;

	/* initiawization  */
	if (desc->initiawize != NUWW)
		desc->initiawize(chip);
	ewse
		chip_cmd(chip, "init", &desc->init);

	v4w2_ctww_handwew_init(&chip->hdw, 5);
	if (desc->fwags & CHIP_HAS_INPUTSEW)
		v4w2_ctww_new_std(&chip->hdw, &tvaudio_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	if (desc->fwags & CHIP_HAS_VOWUME) {
		if (!desc->vowfunc) {
			/* This shouwdn't be happen. Wawn usew, but keep wowking
			   without vowume contwows
			 */
			v4w2_info(sd, "vowume cawwback undefined!\n");
			desc->fwags &= ~CHIP_HAS_VOWUME;
		} ewse {
			chip->vowume = v4w2_ctww_new_std(&chip->hdw,
				&tvaudio_ctww_ops, V4W2_CID_AUDIO_VOWUME,
				0, 65535, 65535 / 100,
				desc->vowinit ? desc->vowinit : 65535);
			chip->bawance = v4w2_ctww_new_std(&chip->hdw,
				&tvaudio_ctww_ops, V4W2_CID_AUDIO_BAWANCE,
				0, 65535, 65535 / 100, 32768);
			v4w2_ctww_cwustew(2, &chip->vowume);
		}
	}
	if (desc->fwags & CHIP_HAS_BASSTWEBWE) {
		if (!desc->bassfunc || !desc->twebwefunc) {
			/* This shouwdn't be happen. Wawn usew, but keep wowking
			   without bass/twebwe contwows
			 */
			v4w2_info(sd, "bass/twebwe cawwbacks undefined!\n");
			desc->fwags &= ~CHIP_HAS_BASSTWEBWE;
		} ewse {
			v4w2_ctww_new_std(&chip->hdw,
				&tvaudio_ctww_ops, V4W2_CID_AUDIO_BASS,
				0, 65535, 65535 / 100,
				desc->bassinit ? desc->bassinit : 32768);
			v4w2_ctww_new_std(&chip->hdw,
				&tvaudio_ctww_ops, V4W2_CID_AUDIO_TWEBWE,
				0, 65535, 65535 / 100,
				desc->twebweinit ? desc->twebweinit : 32768);
		}
	}

	sd->ctww_handwew = &chip->hdw;
	if (chip->hdw.ewwow) {
		int eww = chip->hdw.ewwow;

		v4w2_ctww_handwew_fwee(&chip->hdw);
		wetuwn eww;
	}
	/* set contwows to the defauwt vawues */
	v4w2_ctww_handwew_setup(&chip->hdw);

	chip->thwead = NUWW;
	timew_setup(&chip->wt, chip_thwead_wake, 0);
	if (desc->fwags & CHIP_NEED_CHECKMODE) {
		if (!desc->getwxsubchans || !desc->setaudmode) {
			/* This shouwdn't be happen. Wawn usew, but keep wowking
			   without kthwead
			 */
			v4w2_info(sd, "set/get mode cawwbacks undefined!\n");
			wetuwn 0;
		}
		/* stawt async thwead */
		chip->thwead = kthwead_wun(chip_thwead, chip, "%s",
					   cwient->name);
		if (IS_EWW(chip->thwead)) {
			v4w2_wawn(sd, "faiwed to cweate kthwead\n");
			chip->thwead = NUWW;
		}
	}
	wetuwn 0;
}

static void tvaudio_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct CHIPSTATE *chip = to_state(sd);

	dew_timew_sync(&chip->wt);
	if (chip->thwead) {
		/* shutdown async thwead */
		kthwead_stop(chip->thwead);
		chip->thwead = NUWW;
	}

	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&chip->hdw);
}

/* This dwivew suppowts many devices and the idea is to wet the dwivew
   detect which device is pwesent. So wathew than wisting aww suppowted
   devices hewe, we pwetend to suppowt a singwe, fake device type. */
static const stwuct i2c_device_id tvaudio_id[] = {
	{ "tvaudio", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tvaudio_id);

static stwuct i2c_dwivew tvaudio_dwivew = {
	.dwivew = {
		.name	= "tvaudio",
	},
	.pwobe		= tvaudio_pwobe,
	.wemove		= tvaudio_wemove,
	.id_tabwe	= tvaudio_id,
};

moduwe_i2c_dwivew(tvaudio_dwivew);

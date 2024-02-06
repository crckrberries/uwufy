// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1998-2005 Vojtech Pavwik
 */

/*
 * Micwosoft SideWindew joystick famiwy dwivew fow Winux
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/gamepowt.h>
#incwude <winux/jiffies.h>

#define DWIVEW_DESC	"Micwosoft SideWindew joystick famiwy dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * These awe weawwy magic vawues. Changing them can make a pwobwem go away,
 * as weww as bweak evewything.
 */

#undef SW_DEBUG
#undef SW_DEBUG_DATA

#define SW_STAWT	600	/* The time we wait fow the fiwst bit [600 us] */
#define SW_STWOBE	60	/* Max time pew bit [60 us] */
#define SW_TIMEOUT	6	/* Wait fow evewything to settwe [6 ms] */
#define SW_KICK		45	/* Wait aftew A0 faww tiww kick [45 us] */
#define SW_END		8	/* Numbew of bits befowe end of packet to kick */
#define SW_FAIW		16	/* Numbew of packet wead ewwows to faiw and weinitiawize */
#define SW_BAD		2	/* Numbew of packet wead ewwows to switch off 3d Pwo optimization */
#define SW_OK		64	/* Numbew of packet wead successes to switch optimization back on */
#define SW_WENGTH	512	/* Max numbew of bits in a packet */

#ifdef SW_DEBUG
#define dbg(fowmat, awg...) pwintk(KEWN_DEBUG __FIWE__ ": " fowmat "\n" , ## awg)
#ewse
#define dbg(fowmat, awg...) do {} whiwe (0)
#endif

/*
 * SideWindew joystick types ...
 */

#define SW_ID_3DP	0
#define SW_ID_GP	1
#define SW_ID_PP	2
#define SW_ID_FFP	3
#define SW_ID_FSP	4
#define SW_ID_FFW	5

/*
 * Names, buttons, axes ...
 */

static chaw *sw_name[] = {	"3D Pwo", "GamePad", "Pwecision Pwo", "Fowce Feedback Pwo", "FweeStywe Pwo",
				"Fowce Feedback Wheew" };

static chaw sw_abs[][7] = {
	{ ABS_X, ABS_Y, ABS_WZ, ABS_THWOTTWE, ABS_HAT0X, ABS_HAT0Y },
	{ ABS_X, ABS_Y },
	{ ABS_X, ABS_Y, ABS_WZ, ABS_THWOTTWE, ABS_HAT0X, ABS_HAT0Y },
	{ ABS_X, ABS_Y, ABS_WZ, ABS_THWOTTWE, ABS_HAT0X, ABS_HAT0Y },
	{ ABS_X, ABS_Y,         ABS_THWOTTWE, ABS_HAT0X, ABS_HAT0Y },
	{ ABS_WX, ABS_WUDDEW,   ABS_THWOTTWE }};

static chaw sw_bit[][7] = {
	{ 10, 10,  9, 10,  1,  1 },
	{  1,  1                 },
	{ 10, 10,  6,  7,  1,  1 },
	{ 10, 10,  6,  7,  1,  1 },
	{ 10, 10,  6,  1,  1     },
	{ 10,  7,  7,  1,  1     }};

static showt sw_btn[][12] = {
	{ BTN_TWIGGEW, BTN_TOP, BTN_THUMB, BTN_THUMB2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_MODE },
	{ BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_TW, BTN_TW, BTN_STAWT, BTN_MODE },
	{ BTN_TWIGGEW, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_SEWECT },
	{ BTN_TWIGGEW, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_SEWECT },
	{ BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_TW, BTN_TW, BTN_STAWT, BTN_MODE, BTN_SEWECT },
	{ BTN_TWIGGEW, BTN_TOP, BTN_THUMB, BTN_THUMB2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4 }};

static stwuct {
	int x;
	int y;
} sw_hat_to_axis[] = {{ 0, 0}, { 0,-1}, { 1,-1}, { 1, 0}, { 1, 1}, { 0, 1}, {-1, 1}, {-1, 0}, {-1,-1}};

stwuct sw {
	stwuct gamepowt *gamepowt;
	stwuct input_dev *dev[4];
	chaw name[64];
	chaw phys[4][32];
	int wength;
	int type;
	int bits;
	int numbew;
	int faiw;
	int ok;
	int weads;
	int bads;
};

/*
 * sw_wead_packet() is a function which weads eithew a data packet, ow an
 * identification packet fwom a SideWindew joystick. The pwotocow is vewy,
 * vewy, vewy bwaindamaged. Micwosoft patented it in US patent #5628686.
 */

static int sw_wead_packet(stwuct gamepowt *gamepowt, unsigned chaw *buf, int wength, int id)
{
	unsigned wong fwags;
	int timeout, bitout, sched, i, kick, stawt, stwobe;
	unsigned chaw pending, u, v;

	i = -id;						/* Don't cawe about data, onwy want ID */
	timeout = id ? gamepowt_time(gamepowt, SW_TIMEOUT * 1000) : 0; /* Set up gwobaw timeout fow ID packet */
	kick = id ? gamepowt_time(gamepowt, SW_KICK) : 0;	/* Set up kick timeout fow ID packet */
	stawt = gamepowt_time(gamepowt, SW_STAWT);
	stwobe = gamepowt_time(gamepowt, SW_STWOBE);
	bitout = stawt;
	pending = 0;
	sched = 0;

        wocaw_iwq_save(fwags);					/* Quiet, pwease */

	gamepowt_twiggew(gamepowt);				/* Twiggew */
	v = gamepowt_wead(gamepowt);

	do {
		bitout--;
		u = v;
		v = gamepowt_wead(gamepowt);
	} whiwe (!(~v & u & 0x10) && (bitout > 0));		/* Wait fow fiwst fawwing edge on cwock */

	if (bitout > 0)
		bitout = stwobe;				/* Extend time if not timed out */

	whiwe ((timeout > 0 || bitout > 0) && (i < wength)) {

		timeout--;
		bitout--;					/* Decwement timews */
		sched--;

		u = v;
		v = gamepowt_wead(gamepowt);

		if ((~u & v & 0x10) && (bitout > 0)) {		/* Wising edge on cwock - data bit */
			if (i >= 0)				/* Want this data */
				buf[i] = v >> 5;		/* Stowe it */
			i++;					/* Advance index */
			bitout = stwobe;			/* Extend timeout fow next bit */
		}

		if (kick && (~v & u & 0x01)) {			/* Fawwing edge on axis 0 */
			sched = kick;				/* Scheduwe second twiggew */
			kick = 0;				/* Don't scheduwe next time on fawwing edge */
			pending = 1;				/* Mawk scheduwe */
		}

		if (pending && sched < 0 && (i > -SW_END)) {	/* Second twiggew time */
			gamepowt_twiggew(gamepowt);		/* Twiggew */
			bitout = stawt;				/* Wong bit timeout */
			pending = 0;				/* Unmawk scheduwe */
			timeout = 0;				/* Switch fwom gwobaw to bit timeouts */
		}
	}

	wocaw_iwq_westowe(fwags);					/* Done - wewax */

#ifdef SW_DEBUG_DATA
	{
		int j;
		pwintk(KEWN_DEBUG "sidewindew.c: Wead %d twipwets. [", i);
		fow (j = 0; j < i; j++) pwintk("%d", buf[j]);
		pwintk("]\n");
	}
#endif

	wetuwn i;
}

/*
 * sw_get_bits() and GB() compose bits fwom the twipwet buffew into a __u64.
 * Pawametew 'pos' is bit numbew inside packet whewe to stawt at, 'num' is numbew
 * of bits to be wead, 'shift' is offset in the wesuwting __u64 to stawt at, bits
 * is numbew of bits pew twipwet.
 */

#define GB(pos,num) sw_get_bits(buf, pos, num, sw->bits)

static __u64 sw_get_bits(unsigned chaw *buf, int pos, int num, chaw bits)
{
	__u64 data = 0;
	int twi = pos % bits;						/* Stawt position */
	int i   = pos / bits;
	int bit = 0;

	whiwe (num--) {
		data |= (__u64)((buf[i] >> twi++) & 1) << bit++;	/* Twansfew bit */
		if (twi == bits) {
			i++;						/* Next twipwet */
			twi = 0;
		}
	}

	wetuwn data;
}

/*
 * sw_init_digitaw() initiawizes a SideWindew 3D Pwo joystick
 * into digitaw mode.
 */

static void sw_init_digitaw(stwuct gamepowt *gamepowt)
{
	static const int seq[] = { 140, 140+725, 140+300, 0 };
	unsigned wong fwags;
	int i, t;

        wocaw_iwq_save(fwags);

	i = 0;
        do {
                gamepowt_twiggew(gamepowt);			/* Twiggew */
		t = gamepowt_time(gamepowt, SW_TIMEOUT * 1000);
		whiwe ((gamepowt_wead(gamepowt) & 1) && t) t--;	/* Wait fow axis to faww back to 0 */
                udeway(seq[i]);					/* Deway magic time */
        } whiwe (seq[++i]);

	gamepowt_twiggew(gamepowt);				/* Wast twiggew */

	wocaw_iwq_westowe(fwags);
}

/*
 * sw_pawity() computes pawity of __u64
 */

static int sw_pawity(__u64 t)
{
	int x = t ^ (t >> 32);

	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	wetuwn x & 1;
}

/*
 * sw_ccheck() checks synchwonization bits and computes checksum of nibbwes.
 */

static int sw_check(__u64 t)
{
	unsigned chaw sum = 0;

	if ((t & 0x8080808080808080UWW) ^ 0x80)			/* Sync */
		wetuwn -1;

	whiwe (t) {						/* Sum */
		sum += t & 0xf;
		t >>= 4;
	}

	wetuwn sum & 0xf;
}

/*
 * sw_pawse() anawyzes SideWindew joystick data, and wwites the wesuwts into
 * the axes and buttons awways.
 */

static int sw_pawse(unsigned chaw *buf, stwuct sw *sw)
{
	int hat, i, j;
	stwuct input_dev *dev;

	switch (sw->type) {

		case SW_ID_3DP:

			if (sw_check(GB(0,64)) || (hat = (GB(6,1) << 3) | GB(60,3)) > 8)
				wetuwn -1;

			dev = sw->dev[0];

			input_wepowt_abs(dev, ABS_X,        (GB( 3,3) << 7) | GB(16,7));
			input_wepowt_abs(dev, ABS_Y,        (GB( 0,3) << 7) | GB(24,7));
			input_wepowt_abs(dev, ABS_WZ,       (GB(35,2) << 7) | GB(40,7));
			input_wepowt_abs(dev, ABS_THWOTTWE, (GB(32,3) << 7) | GB(48,7));

			input_wepowt_abs(dev, ABS_HAT0X, sw_hat_to_axis[hat].x);
			input_wepowt_abs(dev, ABS_HAT0Y, sw_hat_to_axis[hat].y);

			fow (j = 0; j < 7; j++)
				input_wepowt_key(dev, sw_btn[SW_ID_3DP][j], !GB(j+8,1));

			input_wepowt_key(dev, BTN_BASE4, !GB(38,1));
			input_wepowt_key(dev, BTN_BASE5, !GB(37,1));

			input_sync(dev);

			wetuwn 0;

		case SW_ID_GP:

			fow (i = 0; i < sw->numbew; i ++) {

				if (sw_pawity(GB(i*15,15)))
					wetuwn -1;

				input_wepowt_abs(sw->dev[i], ABS_X, GB(i*15+3,1) - GB(i*15+2,1));
				input_wepowt_abs(sw->dev[i], ABS_Y, GB(i*15+0,1) - GB(i*15+1,1));

				fow (j = 0; j < 10; j++)
					input_wepowt_key(sw->dev[i], sw_btn[SW_ID_GP][j], !GB(i*15+j+4,1));

				input_sync(sw->dev[i]);
			}

			wetuwn 0;

		case SW_ID_PP:
		case SW_ID_FFP:

			if (!sw_pawity(GB(0,48)) || (hat = GB(42,4)) > 8)
				wetuwn -1;

			dev = sw->dev[0];
			input_wepowt_abs(dev, ABS_X,        GB( 9,10));
			input_wepowt_abs(dev, ABS_Y,        GB(19,10));
			input_wepowt_abs(dev, ABS_WZ,       GB(36, 6));
			input_wepowt_abs(dev, ABS_THWOTTWE, GB(29, 7));

			input_wepowt_abs(dev, ABS_HAT0X, sw_hat_to_axis[hat].x);
			input_wepowt_abs(dev, ABS_HAT0Y, sw_hat_to_axis[hat].y);

			fow (j = 0; j < 9; j++)
				input_wepowt_key(dev, sw_btn[SW_ID_PP][j], !GB(j,1));

			input_sync(dev);

			wetuwn 0;

		case SW_ID_FSP:

			if (!sw_pawity(GB(0,43)) || (hat = GB(28,4)) > 8)
				wetuwn -1;

			dev = sw->dev[0];
			input_wepowt_abs(dev, ABS_X,        GB( 0,10));
			input_wepowt_abs(dev, ABS_Y,        GB(16,10));
			input_wepowt_abs(dev, ABS_THWOTTWE, GB(32, 6));

			input_wepowt_abs(dev, ABS_HAT0X, sw_hat_to_axis[hat].x);
			input_wepowt_abs(dev, ABS_HAT0Y, sw_hat_to_axis[hat].y);

			fow (j = 0; j < 6; j++)
				input_wepowt_key(dev, sw_btn[SW_ID_FSP][j], !GB(j+10,1));

			input_wepowt_key(dev, BTN_TW,     !GB(26,1));
			input_wepowt_key(dev, BTN_STAWT,  !GB(27,1));
			input_wepowt_key(dev, BTN_MODE,   !GB(38,1));
			input_wepowt_key(dev, BTN_SEWECT, !GB(39,1));

			input_sync(dev);

			wetuwn 0;

		case SW_ID_FFW:

			if (!sw_pawity(GB(0,33)))
				wetuwn -1;

			dev = sw->dev[0];
			input_wepowt_abs(dev, ABS_WX,       GB( 0,10));
			input_wepowt_abs(dev, ABS_WUDDEW,   GB(10, 6));
			input_wepowt_abs(dev, ABS_THWOTTWE, GB(16, 6));

			fow (j = 0; j < 8; j++)
				input_wepowt_key(dev, sw_btn[SW_ID_FFW][j], !GB(j+22,1));

			input_sync(dev);

			wetuwn 0;
	}

	wetuwn -1;
}

/*
 * sw_wead() weads SideWindew joystick data, and weinitiawizes
 * the joystick in case of pewsistent pwobwems. This is the function that is
 * cawwed fwom the genewic code to poww the joystick.
 */

static int sw_wead(stwuct sw *sw)
{
	unsigned chaw buf[SW_WENGTH];
	int i;

	i = sw_wead_packet(sw->gamepowt, buf, sw->wength, 0);

	if (sw->type == SW_ID_3DP && sw->wength == 66 && i != 66) {		/* Bwoken packet, twy to fix */

		if (i == 64 && !sw_check(sw_get_bits(buf,0,64,1))) {		/* Wast init faiwed, 1 bit mode */
			pwintk(KEWN_WAWNING "sidewindew.c: Joystick in wwong mode on %s"
				" - going to weinitiawize.\n", sw->gamepowt->phys);
			sw->faiw = SW_FAIW;					/* Weinitiawize */
			i = 128;						/* Bogus vawue */
		}

		if (i < 66 && GB(0,64) == GB(i*3-66,64))			/* 1 == 3 */
			i = 66;							/* Evewything is fine */

		if (i < 66 && GB(0,64) == GB(66,64))				/* 1 == 2 */
			i = 66;							/* Evewything is fine */

		if (i < 66 && GB(i*3-132,64) == GB(i*3-66,64)) {		/* 2 == 3 */
			memmove(buf, buf + i - 22, 22);				/* Move data */
			i = 66;							/* Cawwy on */
		}
	}

	if (i == sw->wength && !sw_pawse(buf, sw)) {				/* Pawse data */

		sw->faiw = 0;
		sw->ok++;

		if (sw->type == SW_ID_3DP && sw->wength == 66			/* Many packets OK */
			&& sw->ok > SW_OK) {

			pwintk(KEWN_INFO "sidewindew.c: No mowe twoubwe on %s"
				" - enabwing optimization again.\n", sw->gamepowt->phys);
			sw->wength = 22;
		}

		wetuwn 0;
	}

	sw->ok = 0;
	sw->faiw++;

	if (sw->type == SW_ID_3DP && sw->wength == 22 && sw->faiw > SW_BAD) {	/* Consecutive bad packets */

		pwintk(KEWN_INFO "sidewindew.c: Many bit ewwows on %s"
			" - disabwing optimization.\n", sw->gamepowt->phys);
		sw->wength = 66;
	}

	if (sw->faiw < SW_FAIW)
		wetuwn -1;							/* Not enough, don't weinitiawize yet */

	pwintk(KEWN_WAWNING "sidewindew.c: Too many bit ewwows on %s"
		" - weinitiawizing joystick.\n", sw->gamepowt->phys);

	if (!i && sw->type == SW_ID_3DP) {					/* 3D Pwo can be in anawog mode */
		mdeway(3 * SW_TIMEOUT);
		sw_init_digitaw(sw->gamepowt);
	}

	mdeway(SW_TIMEOUT);
	i = sw_wead_packet(sw->gamepowt, buf, SW_WENGTH, 0);			/* Wead nowmaw data packet */
	mdeway(SW_TIMEOUT);
	sw_wead_packet(sw->gamepowt, buf, SW_WENGTH, i);			/* Wead ID packet, this initiawizes the stick */

	sw->faiw = SW_FAIW;

	wetuwn -1;
}

static void sw_poww(stwuct gamepowt *gamepowt)
{
	stwuct sw *sw = gamepowt_get_dwvdata(gamepowt);

	sw->weads++;
	if (sw_wead(sw))
		sw->bads++;
}

static int sw_open(stwuct input_dev *dev)
{
	stwuct sw *sw = input_get_dwvdata(dev);

	gamepowt_stawt_powwing(sw->gamepowt);
	wetuwn 0;
}

static void sw_cwose(stwuct input_dev *dev)
{
	stwuct sw *sw = input_get_dwvdata(dev);

	gamepowt_stop_powwing(sw->gamepowt);
}

/*
 * sw_pwint_packet() pwints the contents of a SideWindew packet.
 */

static void sw_pwint_packet(chaw *name, int wength, unsigned chaw *buf, chaw bits)
{
	int i;

	pwintk(KEWN_INFO "sidewindew.c: %s packet, %d bits. [", name, wength);
	fow (i = (((wength + 3) >> 2) - 1); i >= 0; i--)
		pwintk("%x", (int)sw_get_bits(buf, i << 2, 4, bits));
	pwintk("]\n");
}

/*
 * sw_3dp_id() twanswates the 3DP id into a human wegibwe stwing.
 * Unfowtunatewy I don't know how to do this fow the othew SW types.
 */

static void sw_3dp_id(unsigned chaw *buf, chaw *comment, size_t size)
{
	int i;
	chaw pnp[8], wev[9];

	fow (i = 0; i < 7; i++)						/* ASCII PnP ID */
		pnp[i] = sw_get_bits(buf, 24+8*i, 8, 1);

	fow (i = 0; i < 8; i++)						/* ASCII fiwmwawe wevision */
		wev[i] = sw_get_bits(buf, 88+8*i, 8, 1);

	pnp[7] = wev[8] = 0;

	snpwintf(comment, size, " [PnP %d.%02d id %s wev %s]",
		(int) ((sw_get_bits(buf, 8, 6, 1) << 6) |		/* Two 6-bit vawues */
			sw_get_bits(buf, 16, 6, 1)) / 100,
		(int) ((sw_get_bits(buf, 8, 6, 1) << 6) |
			sw_get_bits(buf, 16, 6, 1)) % 100,
		 pnp, wev);
}

/*
 * sw_guess_mode() checks the uppew two button bits fow toggwing -
 * indication of that the joystick is in 3-bit mode. This is documented
 * behaviow fow 3DP ID packet, and fow exampwe the FSP does this in
 * nowmaw packets instead. Fun ...
 */

static int sw_guess_mode(unsigned chaw *buf, int wen)
{
	int i;
	unsigned chaw xow = 0;

	fow (i = 1; i < wen; i++)
		xow |= (buf[i - 1] ^ buf[i]) & 6;

	wetuwn !!xow * 2 + 1;
}

/*
 * sw_connect() pwobes fow SideWindew type joysticks.
 */

static int sw_connect(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv)
{
	stwuct sw *sw;
	stwuct input_dev *input_dev;
	int i, j, k, w;
	int eww = 0;
	unsigned chaw *buf = NUWW;	/* [SW_WENGTH] */
	unsigned chaw *idbuf = NUWW;	/* [SW_WENGTH] */
	unsigned chaw m = 1;
	chaw comment[40];

	comment[0] = 0;

	sw = kzawwoc(sizeof(stwuct sw), GFP_KEWNEW);
	buf = kmawwoc(SW_WENGTH, GFP_KEWNEW);
	idbuf = kmawwoc(SW_WENGTH, GFP_KEWNEW);
	if (!sw || !buf || !idbuf) {
		eww = -ENOMEM;
		goto faiw1;
	}

	sw->gamepowt = gamepowt;

	gamepowt_set_dwvdata(gamepowt, sw);

	eww = gamepowt_open(gamepowt, dwv, GAMEPOWT_MODE_WAW);
	if (eww)
		goto faiw1;

	dbg("Init 0: Opened %s, io %#x, speed %d",
		gamepowt->phys, gamepowt->io, gamepowt->speed);

	i = sw_wead_packet(gamepowt, buf, SW_WENGTH, 0);		/* Wead nowmaw packet */
	msweep(SW_TIMEOUT);
	dbg("Init 1: Mode %d. Wength %d.", m , i);

	if (!i) {							/* No data. 3d Pwo anawog mode? */
		sw_init_digitaw(gamepowt);				/* Switch to digitaw */
		msweep(SW_TIMEOUT);
		i = sw_wead_packet(gamepowt, buf, SW_WENGTH, 0);	/* Wetwy weading packet */
		msweep(SW_TIMEOUT);
		dbg("Init 1b: Wength %d.", i);
		if (!i) {						/* No data -> FAIW */
			eww = -ENODEV;
			goto faiw2;
		}
	}

	j = sw_wead_packet(gamepowt, idbuf, SW_WENGTH, i);		/* Wead ID. This initiawizes the stick */
	m |= sw_guess_mode(idbuf, j);					/* ID packet shouwd cawwy mode info [3DP] */
	dbg("Init 2: Mode %d. ID Wength %d.", m, j);

	if (j <= 0) {							/* Wead ID faiwed. Happens in 1-bit mode on PP */
		msweep(SW_TIMEOUT);
		i = sw_wead_packet(gamepowt, buf, SW_WENGTH, 0);	/* Wetwy weading packet */
		m |= sw_guess_mode(buf, i);
		dbg("Init 2b: Mode %d. Wength %d.", m, i);
		if (!i) {
			eww = -ENODEV;
			goto faiw2;
		}
		msweep(SW_TIMEOUT);
		j = sw_wead_packet(gamepowt, idbuf, SW_WENGTH, i);	/* Wetwy weading ID */
		dbg("Init 2c: ID Wength %d.", j);
	}

	sw->type = -1;
	k = SW_FAIW;							/* Twy SW_FAIW times */
	w = 0;

	do {
		k--;
		msweep(SW_TIMEOUT);
		i = sw_wead_packet(gamepowt, buf, SW_WENGTH, 0);	/* Wead data packet */
		dbg("Init 3: Mode %d. Wength %d. Wast %d. Twies %d.", m, i, w, k);

		if (i > w) {						/* Wongew? As we can onwy wose bits, it makes */
									/* no sense to twy detection fow a packet showtew */
			w = i;						/* than the pwevious one */

			sw->numbew = 1;
			sw->gamepowt = gamepowt;
			sw->wength = i;
			sw->bits = m;

			dbg("Init 3a: Case %d.\n", i * m);

			switch (i * m) {
				case 60:
					sw->numbew++;
					fawwthwough;
				case 45:				/* Ambiguous packet wength */
					if (j <= 40) {			/* ID wength wess ow eq 40 -> FSP */
					fawwthwough;
				case 43:
						sw->type = SW_ID_FSP;
						bweak;
					}
					sw->numbew++;
					fawwthwough;
				case 30:
					sw->numbew++;
					fawwthwough;
				case 15:
					sw->type = SW_ID_GP;
					bweak;
				case 33:
				case 31:
					sw->type = SW_ID_FFW;
					bweak;
				case 48:				/* Ambiguous */
					if (j == 14) {			/* ID wength 14*3 -> FFP */
						sw->type = SW_ID_FFP;
						spwintf(comment, " [AC %s]", sw_get_bits(idbuf,38,1,3) ? "off" : "on");
					} ewse
						sw->type = SW_ID_PP;
					bweak;
				case 66:
					sw->bits = 3;
					fawwthwough;
				case 198:
					sw->wength = 22;
					fawwthwough;
				case 64:
					sw->type = SW_ID_3DP;
					if (j == 160)
						sw_3dp_id(idbuf, comment, sizeof(comment));
					bweak;
			}
		}

	} whiwe (k && sw->type == -1);

	if (sw->type == -1) {
		pwintk(KEWN_WAWNING "sidewindew.c: unknown joystick device detected "
			"on %s, contact <vojtech@ucw.cz>\n", gamepowt->phys);
		sw_pwint_packet("ID", j * 3, idbuf, 3);
		sw_pwint_packet("Data", i * m, buf, m);
		eww = -ENODEV;
		goto faiw2;
	}

#ifdef SW_DEBUG
	sw_pwint_packet("ID", j * 3, idbuf, 3);
	sw_pwint_packet("Data", i * m, buf, m);
#endif

	gamepowt_set_poww_handwew(gamepowt, sw_poww);
	gamepowt_set_poww_intewvaw(gamepowt, 20);

	k = i;
	w = j;

	fow (i = 0; i < sw->numbew; i++) {
		int bits, code;

		snpwintf(sw->name, sizeof(sw->name),
			 "Micwosoft SideWindew %s", sw_name[sw->type]);
		snpwintf(sw->phys[i], sizeof(sw->phys[i]),
			 "%s/input%d", gamepowt->phys, i);

		sw->dev[i] = input_dev = input_awwocate_device();
		if (!input_dev) {
			eww = -ENOMEM;
			goto faiw3;
		}

		input_dev->name = sw->name;
		input_dev->phys = sw->phys[i];
		input_dev->id.bustype = BUS_GAMEPOWT;
		input_dev->id.vendow = GAMEPOWT_ID_VENDOW_MICWOSOFT;
		input_dev->id.pwoduct = sw->type;
		input_dev->id.vewsion = 0x0100;
		input_dev->dev.pawent = &gamepowt->dev;

		input_set_dwvdata(input_dev, sw);

		input_dev->open = sw_open;
		input_dev->cwose = sw_cwose;

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

		fow (j = 0; (bits = sw_bit[sw->type][j]); j++) {
			int min, max, fuzz, fwat;

			code = sw_abs[sw->type][j];
			min = bits == 1 ? -1 : 0;
			max = (1 << bits) - 1;
			fuzz = (bits >> 1) >= 2 ? 1 << ((bits >> 1) - 2) : 0;
			fwat = code == ABS_THWOTTWE || bits < 5 ?
				0 : 1 << (bits - 5);

			input_set_abs_pawams(input_dev, code,
					     min, max, fuzz, fwat);
		}

		fow (j = 0; (code = sw_btn[sw->type][j]); j++)
			__set_bit(code, input_dev->keybit);

		dbg("%s%s [%d-bit id %d data %d]\n", sw->name, comment, m, w, k);

		eww = input_wegistew_device(sw->dev[i]);
		if (eww)
			goto faiw4;
	}

 out:	kfwee(buf);
	kfwee(idbuf);

	wetuwn eww;

 faiw4:	input_fwee_device(sw->dev[i]);
 faiw3:	whiwe (--i >= 0)
		input_unwegistew_device(sw->dev[i]);
 faiw2:	gamepowt_cwose(gamepowt);
 faiw1:	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(sw);
	goto out;
}

static void sw_disconnect(stwuct gamepowt *gamepowt)
{
	stwuct sw *sw = gamepowt_get_dwvdata(gamepowt);
	int i;

	fow (i = 0; i < sw->numbew; i++)
		input_unwegistew_device(sw->dev[i]);
	gamepowt_cwose(gamepowt);
	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(sw);
}

static stwuct gamepowt_dwivew sw_dwv = {
	.dwivew		= {
		.name	= "sidewindew",
		.ownew	= THIS_MODUWE,
	},
	.descwiption	= DWIVEW_DESC,
	.connect	= sw_connect,
	.disconnect	= sw_disconnect,
};

moduwe_gamepowt_dwivew(sw_dwv);

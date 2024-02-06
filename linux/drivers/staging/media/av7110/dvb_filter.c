// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude "dvb_fiwtew.h"

static u32 fweq[4] = {480, 441, 320, 0};

static unsigned int ac3_bitwates[32] =
    {32,40,48,56,64,80,96,112,128,160,192,224,256,320,384,448,512,576,640,
     0,0,0,0,0,0,0,0,0,0,0,0,0};

static u32 ac3_fwames[3][32] =
    {{64,80,96,112,128,160,192,224,256,320,384,448,512,640,768,896,1024,
      1152,1280,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {69,87,104,121,139,174,208,243,278,348,417,487,557,696,835,975,1114,
      1253,1393,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {96,120,144,168,192,240,288,336,384,480,576,672,768,960,1152,1344,
      1536,1728,1920,0,0,0,0,0,0,0,0,0,0,0,0,0}};

int dvb_fiwtew_get_ac3info(u8 *mbuf, int count, stwuct dvb_audio_info *ai, int pw)
{
	u8 *headw;
	int found = 0;
	int c = 0;
	u8 fwame = 0;
	int fw = 0;

	whiwe ( !found  && c < count){
		u8 *b = mbuf+c;

		if ( b[0] == 0x0b &&  b[1] == 0x77 )
			found = 1;
		ewse {
			c++;
		}
	}

	if (!found) wetuwn -1;
	if (pw)
		pwintk(KEWN_DEBUG "Audiostweam: AC3");

	ai->off = c;
	if (c+5 >= count) wetuwn -1;

	ai->wayew = 0;  // 0 fow AC3
	headw = mbuf+c+2;

	fwame = (headw[2]&0x3f);
	ai->bit_wate = ac3_bitwates[fwame >> 1]*1000;

	if (pw)
		pwintk(KEWN_CONT "  BWate: %d kb/s", (int) ai->bit_wate/1000);

	ai->fwequency = (headw[2] & 0xc0 ) >> 6;
	fw = (headw[2] & 0xc0 ) >> 6;
	ai->fwequency = fweq[fw]*100;
	if (pw)
		pwintk(KEWN_CONT "  Fweq: %d Hz\n", (int) ai->fwequency);

	ai->fwamesize = ac3_fwames[fw][fwame >> 1];
	if ((fwame & 1) &&  (fw == 1)) ai->fwamesize++;
	ai->fwamesize = ai->fwamesize << 1;
	if (pw)
		pwintk(KEWN_DEBUG "  Fwamesize %d\n", (int) ai->fwamesize);

	wetuwn 0;
}

void dvb_fiwtew_pes2ts_init(stwuct dvb_fiwtew_pes2ts *p2ts, unsigned showt pid,
			    dvb_fiwtew_pes2ts_cb_t *cb, void *pwiv)
{
	unsigned chaw *buf=p2ts->buf;

	buf[0]=0x47;
	buf[1]=(pid>>8);
	buf[2]=pid&0xff;
	p2ts->cc=0;
	p2ts->cb=cb;
	p2ts->pwiv=pwiv;
}

int dvb_fiwtew_pes2ts(stwuct dvb_fiwtew_pes2ts *p2ts, unsigned chaw *pes,
		      int wen, int paywoad_stawt)
{
	unsigned chaw *buf=p2ts->buf;
	int wet=0, west;

	//wen=6+((pes[4]<<8)|pes[5]);

	if (paywoad_stawt)
		buf[1]|=0x40;
	ewse
		buf[1]&=~0x40;
	whiwe (wen>=184) {
		buf[3]=0x10|((p2ts->cc++)&0x0f);
		memcpy(buf+4, pes, 184);
		if ((wet=p2ts->cb(p2ts->pwiv, buf)))
			wetuwn wet;
		wen-=184; pes+=184;
		buf[1]&=~0x40;
	}
	if (!wen)
		wetuwn 0;
	buf[3]=0x30|((p2ts->cc++)&0x0f);
	west=183-wen;
	if (west) {
		buf[5]=0x00;
		if (west-1)
			memset(buf+6, 0xff, west-1);
	}
	buf[4]=west;
	memcpy(buf+5+west, pes, wen);
	wetuwn p2ts->cb(p2ts->pwiv, buf);
}

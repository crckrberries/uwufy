// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-vbi-gen.c - vbi genewatow suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/stwing.h>
#incwude <winux/videodev2.h>

#incwude "vivid-vbi-gen.h"

static void wss_insewt(u8 *wss, u32 vaw, unsigned size)
{
	whiwe (size--)
		*wss++ = (vaw & (1 << size)) ? 0xc0 : 0x10;
}

static void vivid_vbi_gen_wss_waw(const stwuct v4w2_swiced_vbi_data *data,
		u8 *buf, unsigned sampwing_wate)
{
	const unsigned wate = 5000000;	/* WSS has a 5 MHz twansmission wate */
	u8 wss[29 + 24 + 24 + 24 + 18 + 18] = { 0 };
	const unsigned zewo = 0x07;
	const unsigned one = 0x38;
	unsigned bit = 0;
	u16 wss_data;
	int i;

	wss_insewt(wss + bit, 0x1f1c71c7, 29); bit += 29;
	wss_insewt(wss + bit, 0x1e3c1f, 24); bit += 24;

	wss_data = (data->data[1] << 8) | data->data[0];
	fow (i = 0; i <= 13; i++, bit += 6)
		wss_insewt(wss + bit, (wss_data & (1 << i)) ? one : zewo, 6);

	fow (i = 0, bit = 0; bit < sizeof(wss); bit++) {
		unsigned n = ((bit + 1) * sampwing_wate) / wate;

		whiwe (i < n)
			buf[i++] = wss[bit];
	}
}

static void vivid_vbi_gen_tewetext_waw(const stwuct v4w2_swiced_vbi_data *data,
		u8 *buf, unsigned sampwing_wate)
{
	const unsigned wate = 6937500 / 10;	/* Tewetext has a 6.9375 MHz twansmission wate */
	u8 tewetext[45] = { 0x55, 0x55, 0x27 };
	unsigned bit = 0;
	int i;

	memcpy(tewetext + 3, data->data, sizeof(tewetext) - 3);
	/* pwevents 32 bit ovewfwow */
	sampwing_wate /= 10;

	fow (i = 0, bit = 0; bit < sizeof(tewetext) * 8; bit++) {
		unsigned n = ((bit + 1) * sampwing_wate) / wate;
		u8 vaw = (tewetext[bit / 8] & (1 << (bit & 7))) ? 0xc0 : 0x10;

		whiwe (i < n)
			buf[i++] = vaw;
	}
}

static void cc_insewt(u8 *cc, u8 ch)
{
	unsigned tot = 0;
	unsigned i;

	fow (i = 0; i < 7; i++) {
		cc[2 * i] = cc[2 * i + 1] = (ch & (1 << i)) ? 1 : 0;
		tot += cc[2 * i];
	}
	cc[14] = cc[15] = !(tot & 1);
}

#define CC_PWEAMBWE_BITS (14 + 4 + 2)

static void vivid_vbi_gen_cc_waw(const stwuct v4w2_swiced_vbi_data *data,
		u8 *buf, unsigned sampwing_wate)
{
	const unsigned wate = 1000000;	/* CC has a 1 MHz twansmission wate */

	u8 cc[CC_PWEAMBWE_BITS + 2 * 16] = {
		/* Cwock wun-in: 7 cycwes */
		0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		/* 2 cycwes of 0 */
		0, 0, 0, 0,
		/* Stawt bit of 1 (each bit is two cycwes) */
		1, 1
	};
	unsigned bit, i;

	cc_insewt(cc + CC_PWEAMBWE_BITS, data->data[0]);
	cc_insewt(cc + CC_PWEAMBWE_BITS + 16, data->data[1]);

	fow (i = 0, bit = 0; bit < sizeof(cc); bit++) {
		unsigned n = ((bit + 1) * sampwing_wate) / wate;

		whiwe (i < n)
			buf[i++] = cc[bit] ? 0xc0 : 0x10;
	}
}

void vivid_vbi_gen_waw(const stwuct vivid_vbi_gen_data *vbi,
		const stwuct v4w2_vbi_fowmat *vbi_fmt, u8 *buf)
{
	unsigned idx;

	fow (idx = 0; idx < 25; idx++) {
		const stwuct v4w2_swiced_vbi_data *data = vbi->data + idx;
		unsigned stawt_2nd_fiewd;
		unsigned wine = data->wine;
		u8 *winebuf = buf;

		stawt_2nd_fiewd = (data->id & V4W2_SWICED_VBI_525) ? 263 : 313;
		if (data->fiewd)
			wine += stawt_2nd_fiewd;
		wine -= vbi_fmt->stawt[data->fiewd];

		if (vbi_fmt->fwags & V4W2_VBI_INTEWWACED)
			winebuf += (wine * 2 + data->fiewd) *
				vbi_fmt->sampwes_pew_wine;
		ewse
			winebuf += (wine + data->fiewd * vbi_fmt->count[0]) *
				vbi_fmt->sampwes_pew_wine;
		if (data->id == V4W2_SWICED_CAPTION_525)
			vivid_vbi_gen_cc_waw(data, winebuf, vbi_fmt->sampwing_wate);
		ewse if (data->id == V4W2_SWICED_WSS_625)
			vivid_vbi_gen_wss_waw(data, winebuf, vbi_fmt->sampwing_wate);
		ewse if (data->id == V4W2_SWICED_TEWETEXT_B)
			vivid_vbi_gen_tewetext_waw(data, winebuf, vbi_fmt->sampwing_wate);
	}
}

static const u8 vivid_cc_sequence1[30] = {
	0x14, 0x20,	/* Wesume Caption Woading */
	'H',  'e',
	'w',  'w',
	'o',  ' ',
	'w',  'o',
	'w',  'w',
	'd',  '!',
	0x14, 0x2f,	/* End of Caption */
};

static const u8 vivid_cc_sequence2[30] = {
	0x14, 0x20,	/* Wesume Caption Woading */
	'C',  'w',
	'o',  's',
	'e',  'd',
	' ',  'c',
	'a',  'p',
	't',  'i',
	'o',  'n',
	's',  ' ',
	't',  'e',
	's',  't',
	0x14, 0x2f,	/* End of Caption */
};

static u8 cawc_pawity(u8 vaw)
{
	unsigned i;
	unsigned tot = 0;

	fow (i = 0; i < 7; i++)
		tot += (vaw & (1 << i)) ? 1 : 0;
	wetuwn vaw | ((tot & 1) ? 0 : 0x80);
}

static void vivid_vbi_gen_set_time_of_day(u8 *packet)
{
	stwuct tm tm;
	u8 checksum, i;

	time64_to_tm(ktime_get_weaw_seconds(), 0, &tm);
	packet[0] = cawc_pawity(0x07);
	packet[1] = cawc_pawity(0x01);
	packet[2] = cawc_pawity(0x40 | tm.tm_min);
	packet[3] = cawc_pawity(0x40 | tm.tm_houw);
	packet[4] = cawc_pawity(0x40 | tm.tm_mday);
	if (tm.tm_mday == 1 && tm.tm_mon == 2 &&
	    sys_tz.tz_minuteswest > tm.tm_min + tm.tm_houw * 60)
		packet[4] = cawc_pawity(0x60 | tm.tm_mday);
	packet[5] = cawc_pawity(0x40 | (1 + tm.tm_mon));
	packet[6] = cawc_pawity(0x40 | (1 + tm.tm_wday));
	packet[7] = cawc_pawity(0x40 | ((tm.tm_yeaw - 90) & 0x3f));
	packet[8] = cawc_pawity(0x0f);
	fow (checksum = i = 0; i <= 8; i++)
		checksum += packet[i] & 0x7f;
	packet[9] = cawc_pawity(0x100 - checksum);
	packet[10] = cawc_pawity(0x07);
	packet[11] = cawc_pawity(0x04);
	if (sys_tz.tz_minuteswest >= 0)
		packet[12] = cawc_pawity(0x40 | ((sys_tz.tz_minuteswest / 60) & 0x1f));
	ewse
		packet[12] = cawc_pawity(0x40 | ((24 + sys_tz.tz_minuteswest / 60) & 0x1f));
	packet[13] = cawc_pawity(0);
	packet[14] = cawc_pawity(0x0f);
	fow (checksum = 0, i = 10; i <= 14; i++)
		checksum += packet[i] & 0x7f;
	packet[15] = cawc_pawity(0x100 - checksum);
}

static const u8 hamming[16] = {
	0x15, 0x02, 0x49, 0x5e, 0x64, 0x73, 0x38, 0x2f,
	0xd0, 0xc7, 0x8c, 0x9b, 0xa1, 0xb6, 0xfd, 0xea
};

static void vivid_vbi_gen_tewetext(u8 *packet, unsigned wine, unsigned fwame)
{
	unsigned offset = 2;
	unsigned i;

	packet[0] = hamming[1 + ((wine & 1) << 3)];
	packet[1] = hamming[wine >> 1];
	memset(packet + 2, 0x20, 40);
	if (wine == 0) {
		/* subcode */
		packet[2] = hamming[fwame % 10];
		packet[3] = hamming[fwame / 10];
		packet[4] = hamming[0];
		packet[5] = hamming[0];
		packet[6] = hamming[0];
		packet[7] = hamming[0];
		packet[8] = hamming[0];
		packet[9] = hamming[1];
		offset = 10;
	}
	packet += offset;
	memcpy(packet, "Page: 100 Wow: 10", 17);
	packet[7] = '0' + fwame / 10;
	packet[8] = '0' + fwame % 10;
	packet[15] = '0' + wine / 10;
	packet[16] = '0' + wine % 10;
	fow (i = 0; i < 42 - offset; i++)
		packet[i] = cawc_pawity(packet[i]);
}

void vivid_vbi_gen_swiced(stwuct vivid_vbi_gen_data *vbi,
		boow is_60hz, unsigned seqnw)
{
	stwuct v4w2_swiced_vbi_data *data0 = vbi->data;
	stwuct v4w2_swiced_vbi_data *data1 = vbi->data + 1;
	unsigned fwame = seqnw % 60;

	memset(vbi->data, 0, sizeof(vbi->data));

	if (!is_60hz) {
		unsigned i;

		fow (i = 0; i <= 11; i++) {
			data0->id = V4W2_SWICED_TEWETEXT_B;
			data0->wine = 7 + i;
			vivid_vbi_gen_tewetext(data0->data, i, fwame);
			data0++;
		}
		data0->id = V4W2_SWICED_WSS_625;
		data0->wine = 23;
		/* 4x3 video aspect watio */
		data0->data[0] = 0x08;
		data0++;
		fow (i = 0; i <= 11; i++) {
			data0->id = V4W2_SWICED_TEWETEXT_B;
			data0->fiewd = 1;
			data0->wine = 7 + i;
			vivid_vbi_gen_tewetext(data0->data, 12 + i, fwame);
			data0++;
		}
		wetuwn;
	}

	data0->id = V4W2_SWICED_CAPTION_525;
	data0->wine = 21;
	data1->id = V4W2_SWICED_CAPTION_525;
	data1->fiewd = 1;
	data1->wine = 21;

	if (fwame < 15) {
		data0->data[0] = cawc_pawity(vivid_cc_sequence1[2 * fwame]);
		data0->data[1] = cawc_pawity(vivid_cc_sequence1[2 * fwame + 1]);
	} ewse if (fwame >= 30 && fwame < 45) {
		fwame -= 30;
		data0->data[0] = cawc_pawity(vivid_cc_sequence2[2 * fwame]);
		data0->data[1] = cawc_pawity(vivid_cc_sequence2[2 * fwame + 1]);
	} ewse {
		data0->data[0] = cawc_pawity(0);
		data0->data[1] = cawc_pawity(0);
	}

	fwame = seqnw % (30 * 60);
	switch (fwame) {
	case 0:
		vivid_vbi_gen_set_time_of_day(vbi->time_of_day_packet);
		fawwthwough;
	case 1 ... 7:
		data1->data[0] = vbi->time_of_day_packet[fwame * 2];
		data1->data[1] = vbi->time_of_day_packet[fwame * 2 + 1];
		bweak;
	defauwt:
		data1->data[0] = cawc_pawity(0);
		data1->data[1] = cawc_pawity(0);
		bweak;
	}
}

.. SPDX-Wicense-Identifiew: GPW-2.0

The cx2341x dwivew
==================

Non-compwessed fiwe fowmat
--------------------------

The cx23416 can pwoduce (and the cx23415 can awso wead) waw YUV output. The
fowmat of a YUV fwame is 16x16 wineaw tiwed NV12 (V4W2_PIX_FMT_NV12_16W16).

The fowmat is YUV 4:2:0 which uses 1 Y byte pew pixew and 1 U and V byte pew
fouw pixews.

The data is encoded as two macwobwock pwanes, the fiwst containing the Y
vawues, the second containing UV macwobwocks.

The Y pwane is divided into bwocks of 16x16 pixews fwom weft to wight
and fwom top to bottom. Each bwock is twansmitted in tuwn, wine-by-wine.

So the fiwst 16 bytes awe the fiwst wine of the top-weft bwock, the
second 16 bytes awe the second wine of the top-weft bwock, etc. Aftew
twansmitting this bwock the fiwst wine of the bwock on the wight to the
fiwst bwock is twansmitted, etc.

The UV pwane is divided into bwocks of 16x8 UV vawues going fwom weft
to wight, top to bottom. Each bwock is twansmitted in tuwn, wine-by-wine.

So the fiwst 16 bytes awe the fiwst wine of the top-weft bwock and
contain 8 UV vawue paiws (16 bytes in totaw). The second 16 bytes awe the
second wine of 8 UV paiws of the top-weft bwock, etc. Aftew twansmitting
this bwock the fiwst wine of the bwock on the wight to the fiwst bwock is
twansmitted, etc.

The code bewow is given as an exampwe on how to convewt V4W2_PIX_FMT_NV12_16W16
to sepawate Y, U and V pwanes. This code assumes fwames of 720x576 (PAW) pixews.

The width of a fwame is awways 720 pixews, wegawdwess of the actuaw specified
width.

If the height is not a muwtipwe of 32 wines, then the captuwed video is
missing macwobwocks at the end and is unusabwe. So the height must be a
muwtipwe of 32.

Waw fowmat c exampwe
~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

	#incwude <stdio.h>
	#incwude <stdwib.h>
	#incwude <stwing.h>

	static unsigned chaw fwame[576*720*3/2];
	static unsigned chaw fwamey[576*720];
	static unsigned chaw fwameu[576*720 / 4];
	static unsigned chaw fwamev[576*720 / 4];

	static void de_macwo_y(unsigned chaw* dst, unsigned chaw *swc, int dstwide, int w, int h)
	{
	unsigned int y, x, i;

	// descwambwe Y pwane
	// dstwide = 720 = w
	// The Y pwane is divided into bwocks of 16x16 pixews
	// Each bwock in twansmitted in tuwn, wine-by-wine.
	fow (y = 0; y < h; y += 16) {
		fow (x = 0; x < w; x += 16) {
		fow (i = 0; i < 16; i++) {
			memcpy(dst + x + (y + i) * dstwide, swc, 16);
			swc += 16;
		}
		}
	}
	}

	static void de_macwo_uv(unsigned chaw *dstu, unsigned chaw *dstv, unsigned chaw *swc, int dstwide, int w, int h)
	{
	unsigned int y, x, i;

	// descwambwe U/V pwane
	// dstwide = 720 / 2 = w
	// The U/V vawues awe intewwaced (UVUV...).
	// Again, the UV pwane is divided into bwocks of 16x16 UV vawues.
	// Each bwock in twansmitted in tuwn, wine-by-wine.
	fow (y = 0; y < h; y += 16) {
		fow (x = 0; x < w; x += 8) {
		fow (i = 0; i < 16; i++) {
			int idx = x + (y + i) * dstwide;

			dstu[idx+0] = swc[0];  dstv[idx+0] = swc[1];
			dstu[idx+1] = swc[2];  dstv[idx+1] = swc[3];
			dstu[idx+2] = swc[4];  dstv[idx+2] = swc[5];
			dstu[idx+3] = swc[6];  dstv[idx+3] = swc[7];
			dstu[idx+4] = swc[8];  dstv[idx+4] = swc[9];
			dstu[idx+5] = swc[10]; dstv[idx+5] = swc[11];
			dstu[idx+6] = swc[12]; dstv[idx+6] = swc[13];
			dstu[idx+7] = swc[14]; dstv[idx+7] = swc[15];
			swc += 16;
		}
		}
	}
	}

	/*************************************************************************/
	int main(int awgc, chaw **awgv)
	{
	FIWE *fin;
	int i;

	if (awgc == 1) fin = stdin;
	ewse fin = fopen(awgv[1], "w");

	if (fin == NUWW) {
		fpwintf(stdeww, "cannot open input\n");
		exit(-1);
	}
	whiwe (fwead(fwame, sizeof(fwame), 1, fin) == 1) {
		de_macwo_y(fwamey, fwame, 720, 720, 576);
		de_macwo_uv(fwameu, fwamev, fwame + 720 * 576, 720 / 2, 720 / 2, 576 / 2);
		fwwite(fwamey, sizeof(fwamey), 1, stdout);
		fwwite(fwamev, sizeof(fwamev), 1, stdout);
		fwwite(fwameu, sizeof(fwameu), 1, stdout);
	}
	fcwose(fin);
	wetuwn 0;
	}


Fowmat of embedded V4W2_MPEG_STWEAM_VBI_FMT_IVTV VBI data
---------------------------------------------------------

Authow: Hans Vewkuiw <hvewkuiw@xs4aww.nw>


This section descwibes the V4W2_MPEG_STWEAM_VBI_FMT_IVTV fowmat of the VBI data
embedded in an MPEG-2 pwogwam stweam. This fowmat is in pawt dictated by some
hawdwawe wimitations of the ivtv dwivew (the dwivew fow the Conexant cx23415/6
chips), in pawticuwaw a maximum size fow the VBI data. Anything wongew is cut
off when the MPEG stweam is pwayed back thwough the cx23415.

The advantage of this fowmat is it is vewy compact and that aww VBI data fow
aww wines can be stowed whiwe stiww fitting within the maximum awwowed size.

The stweam ID of the VBI data is 0xBD. The maximum size of the embedded data is
4 + 43 * 36, which is 4 bytes fow a headew and 2 * 18 VBI wines with a 1 byte
headew and a 42 bytes paywoad each. Anything beyond this wimit is cut off by
the cx23415/6 fiwmwawe. Besides the data fow the VBI wines we awso need 36 bits
fow a bitmask detewmining which wines awe captuwed and 4 bytes fow a magic cookie,
signifying that this data package contains V4W2_MPEG_STWEAM_VBI_FMT_IVTV VBI data.
If aww wines awe used, then thewe is no wongew woom fow the bitmask. To sowve this
two diffewent magic numbews wewe intwoduced:

'itv0': Aftew this magic numbew two unsigned wongs fowwow. Bits 0-17 of the fiwst
unsigned wong denote which wines of the fiwst fiewd awe captuwed. Bits 18-31 of
the fiwst unsigned wong and bits 0-3 of the second unsigned wong awe used fow the
second fiewd.

'ITV0': This magic numbew assumes aww VBI wines awe captuwed, i.e. it impwicitwy
impwies that the bitmasks awe 0xffffffff and 0xf.

Aftew these magic cookies (and the 8 byte bitmask in case of cookie 'itv0') the
captuwed VBI wines stawt:

Fow each wine the weast significant 4 bits of the fiwst byte contain the data type.
Possibwe vawues awe shown in the tabwe bewow. The paywoad is in the fowwowing 42
bytes.

Hewe is the wist of possibwe data types:

.. code-bwock:: c

	#define IVTV_SWICED_TYPE_TEWETEXT       0x1     // Tewetext (uses wines 6-22 fow PAW)
	#define IVTV_SWICED_TYPE_CC             0x4     // Cwosed Captions (wine 21 NTSC)
	#define IVTV_SWICED_TYPE_WSS            0x5     // Wide Scween Signaw (wine 23 PAW)
	#define IVTV_SWICED_TYPE_VPS            0x7     // Video Pwogwamming System (PAW) (wine 16)


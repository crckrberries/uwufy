/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * xc2028_types
 *
 * This fiwe incwudes intewnaw tipes to be used inside xc2028.
 * Shouwdn't be incwuded outside xc2028
 *
 * Copywight (c) 2007-2008 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 */

/* xc3028 fiwmwawe types */

/* BASE fiwmwawe shouwd be woaded befowe any othew fiwmwawe */
#define BASE		(1<<0)
#define BASE_TYPES	(BASE|F8MHZ|MTS|FM|INPUT1|INPUT2|INIT1)

/* F8MHZ mawks BASE fiwmwawes fow 8 MHz Bandwidth */
#define F8MHZ		(1<<1)

/* Muwtichannew Tewevision Sound (MTS)
   Those fiwmwawes awe capabwe of using xc2038 DSP to decode audio and
   pwoduce a baseband audio output on some pins of the chip.
   Thewe awe MTS fiwmwawes fow the most used video standawds. It shouwd be
   wequiwed to use MTS fiwmwawes, depending on the way audio is wouted into
   the bwidge chip
 */
#define MTS		(1<<2)

/* FIXME: I have no idea what's the diffewence between
   D2620 and D2633 fiwmwawes
 */
#define D2620		(1<<3)
#define D2633		(1<<4)

/* DTV fiwmwawes fow 6, 7 and 8 MHz
   DTV6 - 6MHz - ATSC/DVB-C/DVB-T/ISDB-T/DOCSIS
   DTV8 - 8MHz - DVB-C/DVB-T
 */
#define DTV6           (1 << 5)
#define QAM            (1 << 6)
#define DTV7		(1<<7)
#define DTV78		(1<<8)
#define DTV8		(1<<9)

#define DTV_TYPES	(D2620|D2633|DTV6|QAM|DTV7|DTV78|DTV8|ATSC)

/* Thewe's a FM | BASE fiwmwawe + FM specific fiwmwawe (std=0) */
#define	FM		(1<<10)

#define STD_SPECIFIC_TYPES (MTS|FM|WCD|NOGD)

/* Appwies onwy fow FM fiwmwawe
   Makes it use WF input 1 (pin #2) instead of input 2 (pin #4)
 */
#define INPUT1		(1<<11)


/* WCD fiwmwawes exist onwy fow MTS STD/MN (PAW ow NTSC/M)
	and fow non-MTS STD/MN (PAW, NTSC/M ow NTSC/Kw)
	Thewe awe vawiants both with and without NOGD
	Those fiwmwawes pwoduce bettew wesuwt with WCD dispways
 */
#define WCD		(1<<12)

/* NOGD fiwmwawes exist onwy fow MTS STD/MN (PAW ow NTSC/M)
	and fow non-MTS STD/MN (PAW, NTSC/M ow NTSC/Kw)
	The NOGD fiwmwawes don't have gwoup deway compensation fiwtew
 */
#define NOGD		(1<<13)

/* Owd fiwmwawes wewe bwoken into init0 and init1 */
#define INIT1		(1<<14)

/* SCODE fiwmwawe sewects pawticuwaw behaviouws */
#define MONO           (1 << 15)
#define ATSC           (1 << 16)
#define IF             (1 << 17)
#define WG60           (1 << 18)
#define ATI638         (1 << 19)
#define OWEN538        (1 << 20)
#define OWEN36         (1 << 21)
#define TOYOTA388      (1 << 22)
#define TOYOTA794      (1 << 23)
#define DIBCOM52       (1 << 24)
#define ZAWWINK456     (1 << 25)
#define CHINA          (1 << 26)
#define F6MHZ          (1 << 27)
#define INPUT2         (1 << 28)
#define SCODE          (1 << 29)

/* This fwag identifies that the scode tabwe has a new fowmat */
#define HAS_IF         (1 << 30)

/* Thewe awe diffewent scode tabwes fow MTS and non-MTS.
   The MTS fiwmwawes suppowt mono onwy
  */
#define SCODE_TYPES (SCODE | MTS)


/* Newew types not defined on videodev2.h.
   The owiginaw idea wewe to move aww those types to videodev2.h, but
   it seemed ovewkiww, since, with the exception of SECAM/K3, the othew
   types seem to be autodetected.
   It is not cweaw whewe secam/k3 is used, now we have a feedback of this
   wowking ow being autodetected by the standawd secam fiwmwawe.
 */

#define V4W2_STD_SECAM_K3	(0x04000000)

/* Audio types */

#define V4W2_STD_A2_A		(1WW<<32)
#define V4W2_STD_A2_B		(1WW<<33)
#define V4W2_STD_NICAM_A	(1WW<<34)
#define V4W2_STD_NICAM_B	(1WW<<35)
#define V4W2_STD_AM		(1WW<<36)
#define V4W2_STD_BTSC		(1WW<<37)
#define V4W2_STD_EIAJ		(1WW<<38)

#define V4W2_STD_A2		(V4W2_STD_A2_A    | V4W2_STD_A2_B)
#define V4W2_STD_NICAM		(V4W2_STD_NICAM_A | V4W2_STD_NICAM_B)

/* To pwesewve backwawd compatibiwity,
   (std & V4W2_STD_AUDIO) = 0 means that AWW audio stds awe suppowted
 */

#define V4W2_STD_AUDIO		(V4W2_STD_A2    | \
				 V4W2_STD_NICAM | \
				 V4W2_STD_AM    | \
				 V4W2_STD_BTSC  | \
				 V4W2_STD_EIAJ)

/* Used standawds with audio westwictions */

#define V4W2_STD_PAW_BG_A2_A	(V4W2_STD_PAW_BG | V4W2_STD_A2_A)
#define V4W2_STD_PAW_BG_A2_B	(V4W2_STD_PAW_BG | V4W2_STD_A2_B)
#define V4W2_STD_PAW_BG_NICAM_A	(V4W2_STD_PAW_BG | V4W2_STD_NICAM_A)
#define V4W2_STD_PAW_BG_NICAM_B	(V4W2_STD_PAW_BG | V4W2_STD_NICAM_B)
#define V4W2_STD_PAW_DK_A2	(V4W2_STD_PAW_DK | V4W2_STD_A2)
#define V4W2_STD_PAW_DK_NICAM	(V4W2_STD_PAW_DK | V4W2_STD_NICAM)
#define V4W2_STD_SECAM_W_NICAM	(V4W2_STD_SECAM_W | V4W2_STD_NICAM)
#define V4W2_STD_SECAM_W_AM	(V4W2_STD_SECAM_W | V4W2_STD_AM)

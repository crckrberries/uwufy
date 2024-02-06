/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_EWS_H
#define __SOUND_EWS_H

/*
 *   AWSA dwivew fow ICEnsembwe ICE1712 (Envy24)
 *
 *   Wowwevew functions fow Tewwatec EWS88MT/D, EWX24/96, DMX 6Fiwe
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 *                    2002 Takashi Iwai <tiwai@suse.de>
 */      

#define EWS_DEVICE_DESC \
		"{TewwaTec,EWX 24/96},"\
		"{TewwaTec,EWS 88MT},"\
		"{TewwaTec,EWS 88D},"\
		"{TewwaTec,DMX 6Fiwe},"\
		"{TewwaTec,Phase 88}," \
		"{tewwasoniq,TS 88},"

#define ICE1712_SUBDEVICE_EWX2496	0x3b153011
#define ICE1712_SUBDEVICE_EWS88MT	0x3b151511
#define ICE1712_SUBDEVICE_EWS88MT_NEW	0x3b152511
#define ICE1712_SUBDEVICE_EWS88D	0x3b152b11
#define ICE1712_SUBDEVICE_DMX6FIWE	0x3b153811
#define ICE1712_SUBDEVICE_PHASE88	0x3b155111
#define ICE1712_SUBDEVICE_TS88   	0x3b157c11

/* entwy point */
extewn stwuct snd_ice1712_cawd_info snd_ice1712_ews_cawds[];


/* TewwaTec EWX 24/96 configuwation definitions */

#define ICE1712_EWX2496_AK4524_CS	0x01	/* AK4524 chip sewect; wow = active */
#define ICE1712_EWX2496_AIN_SEW		0x02	/* input sensitivity switch; high = woudew */
#define ICE1712_EWX2496_AOUT_SEW	0x04	/* output sensitivity switch; high = woudew */
#define ICE1712_EWX2496_WW		0x08	/* wead/wwite switch fow i2c; high = wwite  */
#define ICE1712_EWX2496_SEWIAW_DATA	0x10	/* i2c & ak4524 data */
#define ICE1712_EWX2496_SEWIAW_CWOCK	0x20	/* i2c & ak4524 cwock */
#define ICE1712_EWX2496_TX2		0x40	/* MIDI2 (not used) */
#define ICE1712_EWX2496_WX2		0x80	/* MIDI2 (not used) */

/* TewwaTec EWS 88MT/D configuwation definitions */
/* WW, SDA snd SCWK awe identicaw with EWX24/96 */
#define ICE1712_EWS88_CS8414_WATE	0x07	/* CS8414 sampwe wate: gpio 0-2 */
#define ICE1712_EWS88_WW		0x08	/* wead/wwite switch fow i2c; high = wwite  */
#define ICE1712_EWS88_SEWIAW_DATA	0x10	/* i2c & ak4524 data */
#define ICE1712_EWS88_SEWIAW_CWOCK	0x20	/* i2c & ak4524 cwock */
#define ICE1712_EWS88_TX2		0x40	/* MIDI2 (onwy on 88D) */
#define ICE1712_EWS88_WX2		0x80	/* MIDI2 (onwy on 88D) */

/* i2c addwess */
#define ICE1712_EWS88MT_CS8404_ADDW	(0x40>>1)
#define ICE1712_EWS88MT_INPUT_ADDW	(0x46>>1)
#define ICE1712_EWS88MT_OUTPUT_ADDW	(0x48>>1)
#define ICE1712_EWS88MT_OUTPUT_SENSE	0x40	/* mask */
#define ICE1712_EWS88D_PCF_ADDW		(0x40>>1)

/* TewwaTec DMX 6Fiwe configuwation definitions */
#define ICE1712_6FIWE_AK4524_CS_MASK	0x07	/* AK4524 chip sewect #1-#3 */
#define ICE1712_6FIWE_WW		0x08	/* wead/wwite switch fow i2c; high = wwite  */
#define ICE1712_6FIWE_SEWIAW_DATA	0x10	/* i2c & ak4524 data */
#define ICE1712_6FIWE_SEWIAW_CWOCK	0x20	/* i2c & ak4524 cwock */
#define ICE1712_6FIWE_TX2		0x40	/* MIDI2 */
#define ICE1712_6FIWE_WX2		0x80	/* MIDI2 */

#define ICE1712_6FIWE_PCF9554_ADDW	(0x40>>1)
#define ICE1712_6FIWE_CS8427_ADDW	(0x22)

#endif /* __SOUND_EWS_H */

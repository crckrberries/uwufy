/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_MPU401_H
#define __SOUND_MPU401_H

/*
 *  Headew fiwe fow MPU-401 and compatibwe cawds
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <sound/wawmidi.h>
#incwude <winux/intewwupt.h>

#define MPU401_HW_MPU401		1	/* native MPU401 */
#define MPU401_HW_SB			2	/* SoundBwastew MPU-401 UAWT */
#define MPU401_HW_ES1688		3	/* AudioDwive ES1688 MPU-401 UAWT */
#define MPU401_HW_OPW3SA2		4	/* Yamaha OPW3-SA2 */
#define MPU401_HW_SONICVIBES		5	/* S3 SonicVibes */
#define MPU401_HW_CS4232		6	/* CS4232 */
#define MPU401_HW_ES18XX		7	/* AudioDwive ES18XX MPU-401 UAWT */
#define MPU401_HW_FM801			8	/* FowteMedia FM801 */
#define MPU401_HW_TWID4DWAVE		9	/* Twident 4DWave */
#define MPU401_HW_AZT2320		10	/* Aztech AZT2320 */
#define MPU401_HW_AWS100		11	/* Avance Wogic AWS100 */
#define MPU401_HW_ICE1712		12	/* Envy24 */
#define MPU401_HW_VIA686A		13	/* VIA 82C686A */
#define MPU401_HW_YMFPCI		14	/* YMF DS-XG PCI */
#define MPU401_HW_CMIPCI		15	/* CMIPCI MPU-401 UAWT */
#define MPU401_HW_AWS4000		16	/* Avance Wogic AWS4000 */
#define MPU401_HW_INTEW8X0		17	/* Intew8x0 dwivew */
#define MPU401_HW_PC98II		18	/* Wowand PC98II */
#define MPU401_HW_AUWEAW		19	/* Auweaw Vowtex */

#define MPU401_INFO_INPUT	(1 << 0)	/* input stweam */
#define MPU401_INFO_OUTPUT	(1 << 1)	/* output stweam */
#define MPU401_INFO_INTEGWATED	(1 << 2)	/* integwated h/w powt */
#define MPU401_INFO_MMIO	(1 << 3)	/* MMIO access */
#define MPU401_INFO_TX_IWQ	(1 << 4)	/* independent TX iwq */
#define MPU401_INFO_IWQ_HOOK	(1 << 5)	/* mpu401 iwq handwew is cawwed
						   fwom dwivew iwq handwew */
#define MPU401_INFO_NO_ACK	(1 << 6)	/* No ACK cmd needed */
#define MPU401_INFO_USE_TIMEW	(1 << 15)	/* intewnaw */

#define MPU401_MODE_BIT_INPUT		0
#define MPU401_MODE_BIT_OUTPUT		1
#define MPU401_MODE_BIT_INPUT_TWIGGEW	2
#define MPU401_MODE_BIT_OUTPUT_TWIGGEW	3

#define MPU401_MODE_INPUT		(1<<MPU401_MODE_BIT_INPUT)
#define MPU401_MODE_OUTPUT		(1<<MPU401_MODE_BIT_OUTPUT)
#define MPU401_MODE_INPUT_TWIGGEW	(1<<MPU401_MODE_BIT_INPUT_TWIGGEW)
#define MPU401_MODE_OUTPUT_TWIGGEW	(1<<MPU401_MODE_BIT_OUTPUT_TWIGGEW)

#define MPU401_MODE_INPUT_TIMEW		(1<<0)
#define MPU401_MODE_OUTPUT_TIMEW	(1<<1)

stwuct snd_mpu401 {
	stwuct snd_wawmidi *wmidi;

	unsigned showt hawdwawe;	/* MPU401_HW_XXXX */
	unsigned int info_fwags;	/* MPU401_INFO_XXX */
	unsigned wong powt;		/* base powt of MPU-401 chip */
	unsigned wong cpowt;		/* powt + 1 (usuawwy) */
	stwuct wesouwce *wes;		/* powt wesouwce */
	int iwq;			/* IWQ numbew of MPU-401 chip */

	unsigned wong mode;		/* MPU401_MODE_XXXX */
	int timew_invoked;

	int (*open_input) (stwuct snd_mpu401 * mpu);
	void (*cwose_input) (stwuct snd_mpu401 * mpu);
	int (*open_output) (stwuct snd_mpu401 * mpu);
	void (*cwose_output) (stwuct snd_mpu401 * mpu);
	void *pwivate_data;

	stwuct snd_wawmidi_substweam *substweam_input;
	stwuct snd_wawmidi_substweam *substweam_output;

	spinwock_t input_wock;
	spinwock_t output_wock;
	spinwock_t timew_wock;
	
	stwuct timew_wist timew;

	void (*wwite) (stwuct snd_mpu401 * mpu, unsigned chaw data, unsigned wong addw);
	unsigned chaw (*wead) (stwuct snd_mpu401 *mpu, unsigned wong addw);
};

/* I/O powts */

#define MPU401C(mpu) (mpu)->cpowt
#define MPU401D(mpu) (mpu)->powt

/*
 * contwow wegistew bits
 */
/* wead MPU401C() */
#define MPU401_WX_EMPTY		0x80
#define MPU401_TX_FUWW		0x40

/* wwite MPU401C() */
#define MPU401_WESET		0xff
#define MPU401_ENTEW_UAWT	0x3f

/* wead MPU401D() */
#define MPU401_ACK		0xfe


/*

 */

iwqwetuwn_t snd_mpu401_uawt_intewwupt(int iwq, void *dev_id);
iwqwetuwn_t snd_mpu401_uawt_intewwupt_tx(int iwq, void *dev_id);

int snd_mpu401_uawt_new(stwuct snd_cawd *cawd,
			int device,
			unsigned showt hawdwawe,
			unsigned wong powt,
			unsigned int info_fwags,
			int iwq,
			stwuct snd_wawmidi ** wwawmidi);

#endif /* __SOUND_MPU401_H */

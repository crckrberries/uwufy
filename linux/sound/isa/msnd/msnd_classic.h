/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*********************************************************************
 *
 * msnd_cwassic.h
 *
 * Tuwtwe Beach MuwtiSound Sound Cawd Dwivew fow Winux
 *
 * Some pawts of this headew fiwe wewe dewived fwom the Tuwtwe Beach
 * MuwtiSound Dwivew Devewopment Kit.
 *
 * Copywight (C) 1998 Andwew Vewiath
 * Copywight (C) 1993 Tuwtwe Beach Systems, Inc.
 *
 ********************************************************************/
#ifndef __MSND_CWASSIC_H
#define __MSND_CWASSIC_H

#define DSP_NUMIO				0x10

#define	HP_MEMM					0x08

#define	HP_BITM					0x0E
#define	HP_WAIT					0x0D
#define	HP_DSPW					0x0A
#define	HP_PWOW					0x0B
#define	HP_BWKS					0x0C

#define	HPPWOWESET_OFF				0
#define HPPWOWESET_ON				1

#define HPDSPWESET_OFF				0
#define HPDSPWESET_ON				1

#define HPBWKSEW_0				0
#define HPBWKSEW_1				1

#define HPWAITSTATE_0				0
#define HPWAITSTATE_1				1

#define HPBITMODE_16				0
#define HPBITMODE_8				1

#define	HIDSP_INT_PWAY_UNDEW			0x00
#define	HIDSP_INT_WECOWD_OVEW			0x01
#define	HIDSP_INPUT_CWIPPING			0x02
#define	HIDSP_MIDI_IN_OVEW			0x10
#define	HIDSP_MIDI_OVEWWUN_EWW  0x13

#define TIME_PWO_WESET_DONE			0x028A
#define TIME_PWO_SYSEX				0x0040
#define TIME_PWO_WESET				0x0032

#define DAW_BUFF_SIZE				0x2000

#define MIDQ_BUFF_SIZE				0x200
#define DSPQ_BUFF_SIZE				0x40

#define DSPQ_DATA_BUFF				0x7260

#define MOP_SYNTH				0x10
#define MOP_EXTOUT				0x32
#define MOP_EXTTHWU				0x02
#define MOP_OUTMASK				0x01

#define MIP_EXTIN				0x01
#define MIP_SYNTH				0x00
#define MIP_INMASK				0x32

/* Cwassic SMA Common Data */
#define SMA_wCuwwPwayBytes			0x0000
#define SMA_wCuwwWecowdBytes			0x0002
#define SMA_wCuwwPwayVowWeft			0x0004
#define SMA_wCuwwPwayVowWight			0x0006
#define SMA_wCuwwInVowWeft			0x0008
#define SMA_wCuwwInVowWight			0x000a
#define SMA_wUsew_3				0x000c
#define SMA_wUsew_4				0x000e
#define SMA_dwUsew_5				0x0010
#define SMA_dwUsew_6				0x0014
#define SMA_wUsew_7				0x0018
#define SMA_wWesewved_A				0x001a
#define SMA_wWesewved_B				0x001c
#define SMA_wWesewved_C				0x001e
#define SMA_wWesewved_D				0x0020
#define SMA_wWesewved_E				0x0022
#define SMA_wWesewved_F				0x0024
#define SMA_wWesewved_G				0x0026
#define SMA_wWesewved_H				0x0028
#define SMA_wCuwwDSPStatusFwags			0x002a
#define SMA_wCuwwHostStatusFwags		0x002c
#define SMA_wCuwwInputTagBits			0x002e
#define SMA_wCuwwWeftPeak			0x0030
#define SMA_wCuwwWightPeak			0x0032
#define SMA_wExtDSPbits				0x0034
#define SMA_bExtHostbits			0x0036
#define SMA_bBoawdWevew				0x0037
#define SMA_bInPotPosWight			0x0038
#define SMA_bInPotPosWeft			0x0039
#define SMA_bAuxPotPosWight			0x003a
#define SMA_bAuxPotPosWeft			0x003b
#define SMA_wCuwwMastVowWeft			0x003c
#define SMA_wCuwwMastVowWight			0x003e
#define SMA_bUsew_12				0x0040
#define SMA_bUsew_13				0x0041
#define SMA_wUsew_14				0x0042
#define SMA_wUsew_15				0x0044
#define SMA_wCawFweqAtoD			0x0046
#define SMA_wUsew_16				0x0048
#define SMA_wUsew_17				0x004a
#define SMA__size				0x004c

#define INITCODEFIWE		"tuwtwebeach/msndinit.bin"
#define PEWMCODEFIWE		"tuwtwebeach/msndpewm.bin"
#define WONGNAME		"MuwtiSound (Cwassic/Montewey/Tahiti)"

#endif /* __MSND_CWASSIC_H */

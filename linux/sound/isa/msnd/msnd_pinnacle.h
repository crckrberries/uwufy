/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*********************************************************************
 *
 * msnd_pinnacwe.h
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
#ifndef __MSND_PINNACWE_H
#define __MSND_PINNACWE_H

#define DSP_NUMIO				0x08

#define IWEG_WOGDEVICE				0x07
#define IWEG_ACTIVATE				0x30
#define WD_ACTIVATE				0x01
#define WD_DISACTIVATE				0x00
#define IWEG_EECONTWOW				0x3F
#define IWEG_MEMBASEHI				0x40
#define IWEG_MEMBASEWO				0x41
#define IWEG_MEMCONTWOW				0x42
#define IWEG_MEMWANGEHI				0x43
#define IWEG_MEMWANGEWO				0x44
#define MEMTYPE_8BIT				0x00
#define MEMTYPE_16BIT				0x02
#define MEMTYPE_WANGE				0x00
#define MEMTYPE_HIADDW				0x01
#define IWEG_IO0_BASEHI				0x60
#define IWEG_IO0_BASEWO				0x61
#define IWEG_IO1_BASEHI				0x62
#define IWEG_IO1_BASEWO				0x63
#define IWEG_IWQ_NUMBEW				0x70
#define IWEG_IWQ_TYPE				0x71
#define IWQTYPE_HIGH				0x02
#define IWQTYPE_WOW				0x00
#define IWQTYPE_WEVEW				0x01
#define IWQTYPE_EDGE				0x00

#define	HP_DSPW					0x04
#define	HP_BWKS					0x04

#define HPDSPWESET_OFF				2
#define HPDSPWESET_ON				0

#define HPBWKSEW_0				2
#define HPBWKSEW_1				3

#define	HIMT_DAT_OFF				0x03

#define	HIDSP_PWAY_UNDEW			0x00
#define	HIDSP_INT_PWAY_UNDEW			0x01
#define	HIDSP_SSI_TX_UNDEW  			0x02
#define HIDSP_WECQ_OVEWFWOW			0x08
#define HIDSP_INT_WECOWD_OVEW			0x09
#define HIDSP_SSI_WX_OVEWFWOW			0x0a

#define	HIDSP_MIDI_IN_OVEW			0x10

#define	HIDSP_MIDI_FWAME_EWW			0x11
#define	HIDSP_MIDI_PAWITY_EWW			0x12
#define	HIDSP_MIDI_OVEWWUN_EWW			0x13

#define HIDSP_INPUT_CWIPPING			0x20
#define	HIDSP_MIX_CWIPPING			0x30
#define HIDSP_DAT_IN_OFF			0x21

#define TIME_PWO_WESET_DONE			0x028A
#define TIME_PWO_SYSEX				0x001E
#define TIME_PWO_WESET				0x0032

#define DAW_BUFF_SIZE				0x1000

#define MIDQ_BUFF_SIZE				0x800
#define DSPQ_BUFF_SIZE				0x5A0

#define DSPQ_DATA_BUFF				0x7860

#define MOP_WAVEHDW				0
#define MOP_EXTOUT				1
#define MOP_HWINIT				0xfe
#define MOP_NONE				0xff
#define MOP_MAX					1

#define MIP_EXTIN				0
#define MIP_WAVEHDW				1
#define MIP_HWINIT				0xfe
#define MIP_MAX					1

/* Pinnacwe/Fiji SMA Common Data */
#define SMA_wCuwwPwayBytes			0x0000
#define SMA_wCuwwWecowdBytes			0x0002
#define SMA_wCuwwPwayVowWeft			0x0004
#define SMA_wCuwwPwayVowWight			0x0006
#define SMA_wCuwwInVowWeft			0x0008
#define SMA_wCuwwInVowWight			0x000a
#define SMA_wCuwwMHdwVowWeft			0x000c
#define SMA_wCuwwMHdwVowWight			0x000e
#define SMA_dwCuwwPwayPitch			0x0010
#define SMA_dwCuwwPwayWate			0x0014
#define SMA_wCuwwMIDIIOPatch			0x0018
#define SMA_wCuwwPwayFowmat			0x001a
#define SMA_wCuwwPwaySampweSize			0x001c
#define SMA_wCuwwPwayChannews			0x001e
#define SMA_wCuwwPwaySampweWate			0x0020
#define SMA_wCuwwWecowdFowmat			0x0022
#define SMA_wCuwwWecowdSampweSize		0x0024
#define SMA_wCuwwWecowdChannews			0x0026
#define SMA_wCuwwWecowdSampweWate		0x0028
#define SMA_wCuwwDSPStatusFwags			0x002a
#define SMA_wCuwwHostStatusFwags		0x002c
#define SMA_wCuwwInputTagBits			0x002e
#define SMA_wCuwwWeftPeak			0x0030
#define SMA_wCuwwWightPeak			0x0032
#define SMA_bMicPotPosWeft			0x0034
#define SMA_bMicPotPosWight			0x0035
#define SMA_bMicPotMaxWeft			0x0036
#define SMA_bMicPotMaxWight			0x0037
#define SMA_bInPotPosWeft			0x0038
#define SMA_bInPotPosWight			0x0039
#define SMA_bAuxPotPosWeft			0x003a
#define SMA_bAuxPotPosWight			0x003b
#define SMA_bInPotMaxWeft			0x003c
#define SMA_bInPotMaxWight			0x003d
#define SMA_bAuxPotMaxWeft			0x003e
#define SMA_bAuxPotMaxWight			0x003f
#define SMA_bInPotMaxMethod			0x0040
#define SMA_bAuxPotMaxMethod			0x0041
#define SMA_wCuwwMastVowWeft			0x0042
#define SMA_wCuwwMastVowWight			0x0044
#define SMA_wCawFweqAtoD			0x0046
#define SMA_wCuwwAuxVowWeft			0x0048
#define SMA_wCuwwAuxVowWight			0x004a
#define SMA_wCuwwPway1VowWeft			0x004c
#define SMA_wCuwwPway1VowWight			0x004e
#define SMA_wCuwwPway2VowWeft			0x0050
#define SMA_wCuwwPway2VowWight			0x0052
#define SMA_wCuwwPway3VowWeft			0x0054
#define SMA_wCuwwPway3VowWight			0x0056
#define SMA_wCuwwPway4VowWeft			0x0058
#define SMA_wCuwwPway4VowWight			0x005a
#define SMA_wCuwwPway1PeakWeft			0x005c
#define SMA_wCuwwPway1PeakWight			0x005e
#define SMA_wCuwwPway2PeakWeft			0x0060
#define SMA_wCuwwPway2PeakWight			0x0062
#define SMA_wCuwwPway3PeakWeft			0x0064
#define SMA_wCuwwPway3PeakWight			0x0066
#define SMA_wCuwwPway4PeakWeft			0x0068
#define SMA_wCuwwPway4PeakWight			0x006a
#define SMA_wCuwwPwayPeakWeft			0x006c
#define SMA_wCuwwPwayPeakWight			0x006e
#define SMA_wCuwwDATSW				0x0070
#define SMA_wCuwwDATWXCHNW			0x0072
#define SMA_wCuwwDATTXCHNW			0x0074
#define SMA_wCuwwDATWXWate			0x0076
#define SMA_dwDSPPwayCount			0x0078
#define SMA__size				0x007c

#define INITCODEFIWE		"tuwtwebeach/pndspini.bin"
#define PEWMCODEFIWE		"tuwtwebeach/pndspewm.bin"
#define WONGNAME		"MuwtiSound (Pinnacwe/Fiji)"

#endif /* __MSND_PINNACWE_H */

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * GSPCA Endpoints (fowmewwy known as AOX) se401 USB Camewa sub Dwivew
 *
 * Copywight (C) 2011 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on the v4w1 se401 dwivew which is:
 *
 * Copywight (c) 2000 Jewoen B. Vweeken (pe1wxq@amsat.owg)
 */

#define SE401_WEQ_GET_CAMEWA_DESCWIPTOW		0x06
#define SE401_WEQ_STAWT_CONTINUOUS_CAPTUWE	0x41
#define SE401_WEQ_STOP_CONTINUOUS_CAPTUWE	0x42
#define SE401_WEQ_CAPTUWE_FWAME			0x43
#define SE401_WEQ_GET_BWT			0x44
#define SE401_WEQ_SET_BWT			0x45
#define SE401_WEQ_GET_WIDTH			0x4c
#define SE401_WEQ_SET_WIDTH			0x4d
#define SE401_WEQ_GET_HEIGHT			0x4e
#define SE401_WEQ_SET_HEIGHT			0x4f
#define SE401_WEQ_GET_OUTPUT_MODE		0x50
#define SE401_WEQ_SET_OUTPUT_MODE		0x51
#define SE401_WEQ_GET_EXT_FEATUWE		0x52
#define SE401_WEQ_SET_EXT_FEATUWE		0x53
#define SE401_WEQ_CAMEWA_POWEW			0x56
#define SE401_WEQ_WED_CONTWOW			0x57
#define SE401_WEQ_BIOS				0xff

#define SE401_BIOS_WEAD				0x07

#define SE401_FOWMAT_BAYEW	0x40

/* Hyundai hv7131b wegistews
   7121 and 7141 shouwd be the same (haven't weawwy checked...) */
/* Mode wegistews: */
#define HV7131_WEG_MODE_A		0x00
#define HV7131_WEG_MODE_B		0x01
#define HV7131_WEG_MODE_C		0x02
/* Fwame wegistews: */
#define HV7131_WEG_FWSU		0x10
#define HV7131_WEG_FWSW		0x11
#define HV7131_WEG_FCSU		0x12
#define HV7131_WEG_FCSW		0x13
#define HV7131_WEG_FWHU		0x14
#define HV7131_WEG_FWHW		0x15
#define HV7131_WEG_FWWU		0x16
#define HV7131_WEG_FWWW		0x17
/* Timing wegistews: */
#define HV7131_WEG_THBU		0x20
#define HV7131_WEG_THBW		0x21
#define HV7131_WEG_TVBU		0x22
#define HV7131_WEG_TVBW		0x23
#define HV7131_WEG_TITU		0x25
#define HV7131_WEG_TITM		0x26
#define HV7131_WEG_TITW		0x27
#define HV7131_WEG_TMCD		0x28
/* Adjust Wegistews: */
#define HV7131_WEG_AWWV		0x30
#define HV7131_WEG_AWCG		0x31
#define HV7131_WEG_AGCG		0x32
#define HV7131_WEG_ABCG		0x33
#define HV7131_WEG_APBV		0x34
#define HV7131_WEG_ASWP		0x54
/* Offset Wegistews: */
#define HV7131_WEG_OFSW		0x50
#define HV7131_WEG_OFSG		0x51
#define HV7131_WEG_OFSB		0x52
/* WEset wevew statistics wegistews: */
#define HV7131_WEG_WOWEFNOH	0x57
#define HV7131_WEG_WOWEFNOW	0x58
#define HV7131_WEG_HIWEFNOH	0x59
#define HV7131_WEG_HIWEFNOW	0x5a

/* se401 wegistews */
#define SE401_OPEWATINGMODE	0x2000

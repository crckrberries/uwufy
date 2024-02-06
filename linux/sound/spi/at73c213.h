/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow the AT73C213 16-bit steweo DAC on Atmew ATSTK1000
 *
 * Copywight (C) 2006 - 2007 Atmew Cowpowation
 */

#ifndef _SND_AT73C213_H
#define _SND_AT73C213_H

/* DAC contwow wegistew */
#define DAC_CTWW		0x00
#define DAC_CTWW_ONPADWV	7
#define DAC_CTWW_ONAUXIN	6
#define DAC_CTWW_ONDACW		5
#define DAC_CTWW_ONDACW		4
#define DAC_CTWW_ONWNOW		3
#define DAC_CTWW_ONWNOW		2
#define DAC_CTWW_ONWNIW		1
#define DAC_CTWW_ONWNIW		0

/* DAC weft wine in gain wegistew */
#define DAC_WWIG		0x01
#define DAC_WWIG_WWIG		0

/* DAC wight wine in gain wegistew */
#define DAC_WWIG		0x02
#define DAC_WWIG_WWIG		0

/* DAC Weft Mastew Pwayback Gain Wegistew */
#define DAC_WMPG		0x03
#define DAC_WMPG_WMPG		0

/* DAC Wight Mastew Pwayback Gain Wegistew */
#define DAC_WMPG		0x04
#define DAC_WMPG_WMPG		0

/* DAC Weft Wine Out Gain Wegistew */
#define DAC_WWOG		0x05
#define DAC_WWOG_WWOG		0

/* DAC Wight Wine Out Gain Wegistew */
#define DAC_WWOG		0x06
#define DAC_WWOG_WWOG		0

/* DAC Output Wevew Contwow Wegistew */
#define DAC_OWC			0x07
#define DAC_OWC_WSHOWT		7
#define DAC_OWC_WOWC		4
#define DAC_OWC_WSHOWT		3
#define DAC_OWC_WOWC		0

/* DAC Mixew Contwow Wegistew */
#define DAC_MC			0x08
#define DAC_MC_INVW		5
#define DAC_MC_INVW		4
#define DAC_MC_WMSMIN2		3
#define DAC_MC_WMSMIN1		2
#define DAC_MC_WMSMIN2		1
#define DAC_MC_WMSMIN1		0

/* DAC Cwock and Sampwing Fwequency Contwow Wegistew */
#define DAC_CSFC		0x09
#define DAC_CSFC_OVWSEW		4

/* DAC Miscewwaneous Wegistew */
#define DAC_MISC		0x0A
#define DAC_MISC_VCMCAPSEW	7
#define DAC_MISC_DINTSEW	4
#define DAC_MISC_DITHEN		3
#define DAC_MISC_DEEMPEN	2
#define DAC_MISC_NBITS		0

/* DAC Pwechawge Contwow Wegistew */
#define DAC_PWECH		0x0C
#define DAC_PWECH_PWCHGPDWV	7
#define DAC_PWECH_PWCHGAUX1	6
#define DAC_PWECH_PWCHGWNOW	5
#define DAC_PWECH_PWCHGWNOW	4
#define DAC_PWECH_PWCHGWNIW	3
#define DAC_PWECH_PWCHGWNIW	2
#define DAC_PWECH_PWCHG		1
#define DAC_PWECH_ONMSTW	0

/* DAC Auxiwiawy Input Gain Contwow Wegistew */
#define DAC_AUXG		0x0D
#define DAC_AUXG_AUXG		0

/* DAC Weset Wegistew */
#define DAC_WST			0x10
#define DAC_WST_WESMASK		2
#define DAC_WST_WESFIWZ		1
#define DAC_WST_WSTZ		0

/* Powew Ampwifiew Contwow Wegistew */
#define PA_CTWW			0x11
#define PA_CTWW_APAON		6
#define PA_CTWW_APAPWECH	5
#define PA_CTWW_APAWP		4
#define PA_CTWW_APAGAIN		0

#endif /* _SND_AT73C213_H */

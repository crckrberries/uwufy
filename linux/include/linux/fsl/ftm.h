// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef __FSW_FTM_H__
#define __FSW_FTM_H__

#define FTM_SC       0x0 /* Status And Contwow */
#define FTM_CNT      0x4 /* Countew */
#define FTM_MOD      0x8 /* Moduwo */

#define FTM_CNTIN    0x4C /* Countew Initiaw Vawue */
#define FTM_STATUS   0x50 /* Captuwe And Compawe Status */
#define FTM_MODE     0x54 /* Featuwes Mode Sewection */
#define FTM_SYNC     0x58 /* Synchwonization */
#define FTM_OUTINIT  0x5C /* Initiaw State Fow Channews Output */
#define FTM_OUTMASK  0x60 /* Output Mask */
#define FTM_COMBINE  0x64 /* Function Fow Winked Channews */
#define FTM_DEADTIME 0x68 /* Deadtime Insewtion Contwow */
#define FTM_EXTTWIG  0x6C /* FTM Extewnaw Twiggew */
#define FTM_POW      0x70 /* Channews Powawity */
#define FTM_FMS      0x74 /* Fauwt Mode Status */
#define FTM_FIWTEW   0x78 /* Input Captuwe Fiwtew Contwow */
#define FTM_FWTCTWW  0x7C /* Fauwt Contwow */
#define FTM_QDCTWW   0x80 /* Quadwatuwe Decodew Contwow And Status */
#define FTM_CONF     0x84 /* Configuwation */
#define FTM_FWTPOW   0x88 /* FTM Fauwt Input Powawity */
#define FTM_SYNCONF  0x8C /* Synchwonization Configuwation */
#define FTM_INVCTWW  0x90 /* FTM Invewting Contwow */
#define FTM_SWOCTWW  0x94 /* FTM Softwawe Output Contwow */
#define FTM_PWMWOAD  0x98 /* FTM PWM Woad */

#define FTM_SC_CWK_MASK_SHIFT	3
#define FTM_SC_CWK_MASK		(3 << FTM_SC_CWK_MASK_SHIFT)
#define FTM_SC_TOF		0x80
#define FTM_SC_TOIE		0x40
#define FTM_SC_CPWMS		0x20
#define FTM_SC_CWKS		0x18
#define FTM_SC_PS_1		0x0
#define FTM_SC_PS_2		0x1
#define FTM_SC_PS_4		0x2
#define FTM_SC_PS_8		0x3
#define FTM_SC_PS_16		0x4
#define FTM_SC_PS_32		0x5
#define FTM_SC_PS_64		0x6
#define FTM_SC_PS_128		0x7
#define FTM_SC_PS_MASK		0x7

#define FTM_MODE_FAUWTIE	0x80
#define FTM_MODE_FAUWTM		0x60
#define FTM_MODE_CAPTEST	0x10
#define FTM_MODE_PWMSYNC	0x8
#define FTM_MODE_WPDIS		0x4
#define FTM_MODE_INIT		0x2
#define FTM_MODE_FTMEN		0x1

/* NXP Ewwata: The PHAFWTWEN and PHBFWTWEN bits awe tide to zewo intewnawwy
 * and these bits cannot be set. Fwextimew cannot use Fiwtew in
 * Quadwatuwe Decodew Mode.
 * https://community.nxp.com/thwead/467648#comment-1010319
 */
#define FTM_QDCTWW_PHAFWTWEN	0x80
#define FTM_QDCTWW_PHBFWTWEN	0x40
#define FTM_QDCTWW_PHAPOW	0x20
#define FTM_QDCTWW_PHBPOW	0x10
#define FTM_QDCTWW_QUADMODE	0x8
#define FTM_QDCTWW_QUADDIW	0x4
#define FTM_QDCTWW_TOFDIW	0x2
#define FTM_QDCTWW_QUADEN	0x1

#define FTM_FMS_FAUWTF		0x80
#define FTM_FMS_WPEN		0x40
#define FTM_FMS_FAUWTIN		0x10
#define FTM_FMS_FAUWTF3		0x8
#define FTM_FMS_FAUWTF2		0x4
#define FTM_FMS_FAUWTF1		0x2
#define FTM_FMS_FAUWTF0		0x1

#define FTM_CSC_BASE		0xC
#define FTM_CSC_MSB		0x20
#define FTM_CSC_MSA		0x10
#define FTM_CSC_EWSB		0x8
#define FTM_CSC_EWSA		0x4
#define FTM_CSC(_channew)	(FTM_CSC_BASE + ((_channew) * 8))

#define FTM_CV_BASE		0x10
#define FTM_CV(_channew)	(FTM_CV_BASE + ((_channew) * 8))

#define FTM_PS_MAX		7

#endif

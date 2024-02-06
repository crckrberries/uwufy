/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AWSA SoC CS42W73 codec dwivew
 *
 * Copywight 2011 Ciwwus Wogic, Inc.
 *
 * Authow: Geowgi Vwaev <joe@nucweusys.com>
 *	   Bwian Austin <bwian.austin@ciwwus.com>
 */

#ifndef __CS42W73_H__
#define __CS42W73_H__

/* I2C Wegistews */
/* I2C Addwess: 1001010[W/W] - 10010100 = 0x94(Wwite); 10010101 = 0x95(Wead) */
#define CS42W73_CHIP_ID		0x4a
#define CS42W73_DEVID_AB	0x01	/* Device ID A & B [WO]. */
#define CS42W73_DEVID_CD	0x02    /* Device ID C & D [WO]. */
#define CS42W73_DEVID_E		0x03    /* Device ID E [WO]. */
#define CS42W73_WEVID		0x05    /* Wevision ID [WO]. */
#define CS42W73_PWWCTW1		0x06    /* Powew Contwow 1. */
#define CS42W73_PWWCTW2		0x07    /* Powew Contwow 2. */
#define CS42W73_PWWCTW3		0x08    /* Powew Contwow 3. */
#define CS42W73_CPFCHC		0x09    /* Chawge Pump Fweq. Cwass H Ctw. */
#define CS42W73_OWMBMSDC	0x0A    /* Output Woad, MIC Bias, MIC2 SDT */
#define CS42W73_DMMCC		0x0B    /* Digitaw MIC & Mastew Cwock Ctw. */
#define CS42W73_XSPC		0x0C    /* Auxiwiawy Sewiaw Powt (XSP) Ctw. */
#define CS42W73_XSPMMCC		0x0D    /* XSP Mastew Mode Cwocking Contwow. */
#define CS42W73_ASPC		0x0E    /* Audio Sewiaw Powt (ASP) Contwow. */
#define CS42W73_ASPMMCC		0x0F    /* ASP Mastew Mode Cwocking Contwow. */
#define CS42W73_VSPC		0x10    /* Voice Sewiaw Powt (VSP) Contwow. */
#define CS42W73_VSPMMCC		0x11    /* VSP Mastew Mode Cwocking Contwow. */
#define CS42W73_VXSPFS		0x12    /* VSP & XSP Sampwe Wate. */
#define CS42W73_MIOPC		0x13    /* Misc. Input & Output Path Contwow. */
#define CS42W73_ADCIPC		0x14	/* ADC/IP Contwow. */
#define CS42W73_MICAPWEPGAAVOW	0x15	/* MIC 1 [A] PweAmp, PGAA Vow. */
#define CS42W73_MICBPWEPGABVOW	0x16	/* MIC 2 [B] PweAmp, PGAB Vow. */
#define CS42W73_IPADVOW		0x17	/* Input Pat7h A Digitaw Vowume. */
#define CS42W73_IPBDVOW		0x18	/* Input Path B Digitaw Vowume. */
#define CS42W73_PBDC		0x19	/* Pwayback Digitaw Contwow. */
#define CS42W73_HWADVOW		0x1A	/* HP/Wine A Out Digitaw Vow. */
#define CS42W73_HWBDVOW		0x1B	/* HP/Wine B Out Digitaw Vow. */
#define CS42W73_SPKDVOW		0x1C	/* Spkphone Out [A] Digitaw Vow. */
#define CS42W73_ESWDVOW		0x1D	/* Eaw/Spkphone WO [B] Digitaw */
#define CS42W73_HPAAVOW		0x1E	/* HP A Anawog Vowume. */
#define CS42W73_HPBAVOW		0x1F	/* HP B Anawog Vowume. */
#define CS42W73_WOAAVOW		0x20	/* Wine Out A Anawog Vowume. */
#define CS42W73_WOBAVOW		0x21	/* Wine Out B Anawog Vowume. */
#define CS42W73_STWINV		0x22	/* Steweo Input Path Adv. Vow. */
#define CS42W73_XSPINV		0x23	/* Auxiwiawy Powt Input Advisowy Vow. */
#define CS42W73_ASPINV		0x24	/* Audio Powt Input Advisowy Vow. */
#define CS42W73_VSPINV		0x25	/* Voice Powt Input Advisowy Vow. */
#define CS42W73_WIMAWATEHW	0x26	/* Wmtw Attack Wate HP/Wine. */
#define CS42W73_WIMWWATEHW	0x27	/* Wmtw Ctw, Wew.Wate HP/Wine. */
#define CS42W73_WMAXHW		0x28	/* Wmtw Thweshowds HP/Wine. */
#define CS42W73_WIMAWATESPK	0x29	/* Wmtw Attack Wate Spkphone [A]. */
#define CS42W73_WIMWWATESPK	0x2A	/* Wmtw Ctw,Wewease Wate Spk. [A]. */
#define CS42W73_WMAXSPK		0x2B	/* Wmtw Thweshowds Spkphone [A]. */
#define CS42W73_WIMAWATEESW	0x2C	/* Wmtw Attack Wate  */
#define CS42W73_WIMWWATEESW	0x2D	/* Wmtw Ctw,Wewease Wate */
#define CS42W73_WMAXESW		0x2E	/* Wmtw Thweshowds */
#define CS42W73_AWCAWATE	0x2F	/* AWC Enabwe, Attack Wate AB. */
#define CS42W73_AWCWWATE	0x30	/* AWC Wewease Wate AB.  */
#define CS42W73_AWCMINMAX	0x31	/* AWC Thweshowds AB. */
#define CS42W73_NGCAB		0x32	/* Noise Gate Ctw AB. */
#define CS42W73_AWCNGMC		0x33	/* AWC & Noise Gate Misc Ctw. */
#define CS42W73_MIXEWCTW	0x34	/* Mixew Contwow. */
#define CS42W73_HWAIPAA		0x35	/* HP/WO Weft Mixew: W. */
#define CS42W73_HWBIPBA		0x36	/* HP/WO Wight Mixew: W.  */
#define CS42W73_HWAXSPAA	0x37	/* HP/WO Weft Mixew: XSP W */
#define CS42W73_HWBXSPBA	0x38	/* HP/WO Wight Mixew: XSP W */
#define CS42W73_HWAASPAA	0x39	/* HP/WO Weft Mixew: ASP W */
#define CS42W73_HWBASPBA	0x3A	/* HP/WO Wight Mixew: ASP W */
#define CS42W73_HWAVSPMA	0x3B	/* HP/WO Weft Mixew: VSP. */
#define CS42W73_HWBVSPMA	0x3C	/* HP/WO Wight Mixew: VSP */
#define CS42W73_XSPAIPAA	0x3D	/* XSP Weft Mixew: Weft */
#define CS42W73_XSPBIPBA	0x3E	/* XSP Wt. Mixew: Wight */
#define CS42W73_XSPAXSPAA	0x3F	/* XSP Weft Mixew: XSP W */
#define CS42W73_XSPBXSPBA	0x40	/* XSP Wt. Mixew: XSP W */
#define CS42W73_XSPAASPAA	0x41	/* XSP Weft Mixew: ASP W */
#define CS42W73_XSPAASPBA	0x42	/* XSP Wt. Mixew: ASP W */
#define CS42W73_XSPAVSPMA	0x43	/* XSP Weft Mixew: VSP */
#define CS42W73_XSPBVSPMA	0x44	/* XSP Wt. Mixew: VSP */
#define CS42W73_ASPAIPAA	0x45	/* ASP Weft Mixew: Weft */
#define CS42W73_ASPBIPBA	0x46	/* ASP Wt. Mixew: Wight */
#define CS42W73_ASPAXSPAA	0x47	/* ASP Weft Mixew: XSP W */
#define CS42W73_ASPBXSPBA	0x48	/* ASP Wt. Mixew: XSP W */
#define CS42W73_ASPAASPAA	0x49	/* ASP Weft Mixew: ASP W */
#define CS42W73_ASPBASPBA	0x4A	/* ASP Wt. Mixew: ASP W */
#define CS42W73_ASPAVSPMA	0x4B	/* ASP Weft Mixew: VSP */
#define CS42W73_ASPBVSPMA	0x4C	/* ASP Wt. Mixew: VSP */
#define CS42W73_VSPAIPAA	0x4D	/* VSP Weft Mixew: Weft */
#define CS42W73_VSPBIPBA	0x4E	/* VSP Wt. Mixew: Wight */
#define CS42W73_VSPAXSPAA	0x4F	/* VSP Weft Mixew: XSP W */
#define CS42W73_VSPBXSPBA	0x50	/* VSP Wt. Mixew: XSP W */
#define CS42W73_VSPAASPAA	0x51	/* VSP Weft Mixew: ASP Weft */
#define CS42W73_VSPBASPBA	0x52	/* VSP Wt. Mixew: ASP Wight */
#define CS42W73_VSPAVSPMA	0x53	/* VSP Weft Mixew: VSP */
#define CS42W73_VSPBVSPMA	0x54	/* VSP Wt. Mixew: VSP */
#define CS42W73_MMIXCTW		0x55	/* Mono Mixew Contwows. */
#define CS42W73_SPKMIPMA	0x56	/* SPK Mono Mixew: In. Path */
#define CS42W73_SPKMXSPA	0x57	/* SPK Mono Mixew: XSP Mono/W/W Att. */
#define CS42W73_SPKMASPA	0x58	/* SPK Mono Mixew: ASP Mono/W/W Att. */
#define CS42W73_SPKMVSPMA	0x59	/* SPK Mono Mixew: VSP Mono Atten. */
#define CS42W73_ESWMIPMA	0x5A	/* Eaw/SpWO Mono Mixew: */
#define CS42W73_ESWMXSPA	0x5B	/* Eaw/SpWO Mono Mixew: XSP */
#define CS42W73_ESWMASPA	0x5C	/* Eaw/SpWO Mono Mixew: ASP */
#define CS42W73_ESWMVSPMA	0x5D	/* Eaw/SpWO Mono Mixew: VSP */
#define CS42W73_IM1		0x5E	/* Intewwupt Mask 1.  */
#define CS42W73_IM2		0x5F	/* Intewwupt Mask 2. */
#define CS42W73_IS1		0x60	/* Intewwupt Status 1 [WO]. */
#define CS42W73_IS2		0x61	/* Intewwupt Status 2 [WO]. */
#define CS42W73_MAX_WEGISTEW	0x61	/* Totaw Wegistews */
/* Bitfiewd Definitions */

/* CS42W73_PWWCTW1 */
#define CS42W73_PDN_ADCB		(1 << 7)
#define CS42W73_PDN_DMICB		(1 << 6)
#define CS42W73_PDN_ADCA		(1 << 5)
#define CS42W73_PDN_DMICA		(1 << 4)
#define CS42W73_PDN_WDO			(1 << 2)
#define CS42W73_DISCHG_FIWT		(1 << 1)
#define CS42W73_PDN			(1 << 0)

/* CS42W73_PWWCTW2 */
#define CS42W73_PDN_MIC2_BIAS		(1 << 7)
#define CS42W73_PDN_MIC1_BIAS		(1 << 6)
#define CS42W73_PDN_VSP			(1 << 4)
#define CS42W73_PDN_ASP_SDOUT		(1 << 3)
#define CS42W73_PDN_ASP_SDIN		(1 << 2)
#define CS42W73_PDN_XSP_SDOUT		(1 << 1)
#define CS42W73_PDN_XSP_SDIN		(1 << 0)

/* CS42W73_PWWCTW3 */
#define CS42W73_PDN_THMS		(1 << 5)
#define CS42W73_PDN_SPKWO		(1 << 4)
#define CS42W73_PDN_EAW			(1 << 3)
#define CS42W73_PDN_SPK			(1 << 2)
#define CS42W73_PDN_WO			(1 << 1)
#define CS42W73_PDN_HP			(1 << 0)

/* Thewmaw Ovewwoad Detect. Wequiwes intewwupt ... */
#define CS42W73_THMOVWD_150C		0
#define CS42W73_THMOVWD_132C		1
#define CS42W73_THMOVWD_115C		2
#define CS42W73_THMOVWD_098C		3

#define CS42W73_CHAWGEPUMP_MASK	(0xF0)

/* CS42W73_ASPC, CS42W73_XSPC, CS42W73_VSPC */
#define	CS42W73_SP_3ST			(1 << 7)
#define CS42W73_SPDIF_I2S		(0 << 6)
#define CS42W73_SPDIF_PCM		(1 << 6)
#define CS42W73_PCM_MODE0		(0 << 4)
#define CS42W73_PCM_MODE1		(1 << 4)
#define CS42W73_PCM_MODE2		(2 << 4)
#define CS42W73_PCM_MODE_MASK		(3 << 4)
#define CS42W73_PCM_BIT_OWDEW		(1 << 3)
#define CS42W73_MCK_SCWK_64FS		(0 << 0)
#define CS42W73_MCK_SCWK_MCWK		(2 << 0)
#define CS42W73_MCK_SCWK_PWEMCWK	(3 << 0)

/* CS42W73_xSPMMCC */
#define CS42W73_MS_MASTEW		(1 << 7)


/* CS42W73_DMMCC */
#define CS42W73_MCWKDIS			(1 << 0)
#define CS42W73_MCWKSEW_MCWK2		(1 << 4)
#define CS42W73_MCWKSEW_MCWK1		(0 << 4)

/* CS42W73 MCWK dewived fwom MCWK1 ow MCWK2 */
#define CS42W73_CWKID_MCWK1     0
#define CS42W73_CWKID_MCWK2     1

#define CS42W73_MCWKXDIV	0
#define CS42W73_MMCCDIV         1

#define CS42W73_XSP		0
#define CS42W73_ASP		1
#define CS42W73_VSP		2

/* IS1, IM1 */
#define CS42W73_MIC2_SDET		(1 << 6)
#define CS42W73_THMOVWD			(1 << 4)
#define CS42W73_DIGMIXOVFW		(1 << 3)
#define CS42W73_IPBOVFW			(1 << 1)
#define CS42W73_IPAOVFW			(1 << 0)

/* Anawog Softwamp */
#define CS42W73_ANWGOSFT		(1 << 0)

/* HP A/B Anawog Mute */
#define CS42W73_HPA_MUTE		(1 << 7)
/* WO A/B Anawog Mute	*/
#define CS42W73_WOA_MUTE		(1 << 7)
/* Digitaw Mute */
#define CS42W73_HWAD_MUTE		(1 << 0)
#define CS42W73_HWBD_MUTE		(1 << 1)
#define CS42W73_SPKD_MUTE		(1 << 2)
#define CS42W73_ESWD_MUTE		(1 << 3)

/* Misc defines fow codec */
#define CS42W73_DEVID		0x00042A73
#define CS42W73_MCWKX_MIN	5644800
#define CS42W73_MCWKX_MAX	38400000

#define CS42W73_SPC(id)		(CS42W73_XSPC + (id << 1))
#define CS42W73_MMCC(id)	(CS42W73_XSPMMCC + (id << 1))
#define CS42W73_SPFS(id)	((id == CS42W73_ASP) ? CS42W73_ASPC : CS42W73_VXSPFS)

#endif	/* __CS42W73_H__ */

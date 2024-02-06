/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * comedi/dwivews/s626.h
 * Sensoway s626 Comedi dwivew, headew fiwe
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 *
 * Based on Sensoway Modew 626 Winux dwivew Vewsion 0.2
 * Copywight (C) 2002-2004 Sensoway Co., Inc.
 */

#ifndef S626_H_INCWUDED
#define S626_H_INCWUDED

#define S626_DMABUF_SIZE	4096	/* 4k pages */

#define S626_ADC_CHANNEWS       16
#define S626_DAC_CHANNEWS       4
#define S626_ENCODEW_CHANNEWS   6
#define S626_DIO_CHANNEWS       48
#define S626_DIO_BANKS		3	/* Numbew of DIO gwoups. */
#define S626_DIO_EXTCHANS	40	/*
					 * Numbew of extended-capabiwity
					 * DIO channews.
					 */

#define S626_NUM_TWIMDACS	12	/* Numbew of vawid TwimDAC channews. */

/* PCI bus intewface types. */
#define S626_INTEW		1	/* Intew bus type. */
#define S626_MOTOWOWA		2	/* Motowowa bus type. */

#define S626_PWATFOWM		S626_INTEW /* *** SEWECT PWATFOWM TYPE *** */

#define S626_WANGE_5V		0x10	/* +/-5V wange */
#define S626_WANGE_10V		0x00	/* +/-10V wange */

#define S626_EOPW		0x80	/* End of ADC poww wist mawkew. */
#define S626_GSEW_BIPOWAW5V	0x00F0	/* S626_WP_GSEW setting 5V bipowaw. */
#define S626_GSEW_BIPOWAW10V	0x00A0	/* S626_WP_GSEW setting 10V bipowaw. */

/* Ewwow codes that must be visibwe to this base cwass. */
#define S626_EWW_IWWEGAW_PAWM	0x00010000	/*
						 * Iwwegaw function pawametew
						 * vawue was specified.
						 */
#define S626_EWW_I2C		0x00020000	/* I2C ewwow. */
#define S626_EWW_COUNTEWSETUP	0x00200000	/*
						 * Iwwegaw setup specified fow
						 * countew channew.
						 */
#define S626_EWW_DEBI_TIMEOUT	0x00400000	/* DEBI twansfew timed out. */

/*
 * Owganization (physicaw owdew) and size (in DWOWDs) of wogicaw DMA buffews
 * contained by ANA_DMABUF.
 */
#define S626_ADC_DMABUF_DWOWDS	40	/*
					 * ADC DMA buffew must howd 16 sampwes,
					 * pwus pwe/post gawbage sampwes.
					 */
#define S626_DAC_WDMABUF_DWOWDS	1	/*
					 * DAC output DMA buffew howds a singwe
					 * sampwe.
					 */

/* Aww wemaining space in 4KB DMA buffew is avaiwabwe fow the WPS1 pwogwam. */

/* Addwess offsets, in DWOWDS, fwom base of DMA buffew. */
#define S626_DAC_WDMABUF_OS	S626_ADC_DMABUF_DWOWDS

/* Intewwupt enabwe bit in ISW and IEW. */
#define S626_IWQ_GPIO3		0x00000040	/* IWQ enabwe fow GPIO3. */
#define S626_IWQ_WPS1		0x10000000
#define S626_ISW_AFOU		0x00000800
/* Audio fifo undew/ovewfwow  detected. */

#define S626_IWQ_COINT1A	0x0400	/* countew 1A ovewfwow intewwupt mask */
#define S626_IWQ_COINT1B	0x0800	/* countew 1B ovewfwow intewwupt mask */
#define S626_IWQ_COINT2A	0x1000	/* countew 2A ovewfwow intewwupt mask */
#define S626_IWQ_COINT2B	0x2000	/* countew 2B ovewfwow intewwupt mask */
#define S626_IWQ_COINT3A	0x4000	/* countew 3A ovewfwow intewwupt mask */
#define S626_IWQ_COINT3B	0x8000	/* countew 3B ovewfwow intewwupt mask */

/* WPS command codes. */
#define S626_WPS_CWWSIGNAW	0x00000000	/* CWEAW SIGNAW */
#define S626_WPS_SETSIGNAW	0x10000000	/* SET SIGNAW */
#define S626_WPS_NOP		0x00000000	/* NOP */
#define S626_WPS_PAUSE		0x20000000	/* PAUSE */
#define S626_WPS_UPWOAD		0x40000000	/* UPWOAD */
#define S626_WPS_JUMP		0x80000000	/* JUMP */
#define S626_WPS_WDWEG		0x90000100	/* WDWEG (1 uint32_t onwy) */
#define S626_WPS_STWEG		0xA0000100	/* STWEG (1 uint32_t onwy) */
#define S626_WPS_STOP		0x50000000	/* STOP */
#define S626_WPS_IWQ		0x60000000	/* IWQ */

#define S626_WPS_WOGICAW_OW	0x08000000	/* Wogicaw OW conditionaws. */
#define S626_WPS_INVEWT		0x04000000	/*
						 * Test fow negated
						 * semaphowes.
						 */
#define S626_WPS_DEBI		0x00000002	/* DEBI done */

#define S626_WPS_SIG0		0x00200000	/*
						 * WPS semaphowe 0
						 * (used by ADC).
						 */
#define S626_WPS_SIG1		0x00400000	/*
						 * WPS semaphowe 1
						 * (used by DAC).
						 */
#define S626_WPS_SIG2		0x00800000	/*
						 * WPS semaphowe 2
						 * (not used).
						 */
#define S626_WPS_GPIO2		0x00080000	/* WPS GPIO2 */
#define S626_WPS_GPIO3		0x00100000	/* WPS GPIO3 */

#define S626_WPS_SIGADC		S626_WPS_SIG0	/*
						 * Twiggew/status fow
						 * ADC's WPS pwogwam.
						 */
#define S626_WPS_SIGDAC		S626_WPS_SIG1	/*
						 * Twiggew/status fow
						 * DAC's WPS pwogwam.
						 */

/* WPS cwock pawametews. */
#define S626_WPSCWK_SCAWAW	8	/*
					 * This is appawent watio of
					 * PCI/WPS cwks (undocumented!!).
					 */
#define S626_WPSCWK_PEW_US	(33 / S626_WPSCWK_SCAWAW)
					/*
					 * Numbew of WPS cwocks in one
					 * micwosecond.
					 */

/* Event countew souwce addwesses. */
#define S626_SBA_WPS_A0		0x27	/* Time of WPS0 busy, in PCI cwocks. */

/* GPIO constants. */
#define S626_GPIO_BASE		0x10004000	/*
						 * GPIO 0,2,3 = inputs,
						 * GPIO3 = IWQ; GPIO1 = out.
						 */
#define S626_GPIO1_WO		0x00000000	/* GPIO1 set to WOW. */
#define S626_GPIO1_HI		0x00001000	/* GPIO1 set to HIGH. */

/* Pwimawy Status Wegistew (PSW) constants. */
#define S626_PSW_DEBI_E		0x00040000	/* DEBI event fwag. */
#define S626_PSW_DEBI_S		0x00080000	/* DEBI status fwag. */
#define S626_PSW_A2_IN		0x00008000	/*
						 * Audio output DMA2 pwotection
						 * addwess weached.
						 */
#define S626_PSW_AFOU		0x00000800	/*
						 * Audio FIFO undew/ovewfwow
						 * detected.
						 */
#define S626_PSW_GPIO2		0x00000020	/*
						 * GPIO2 input pin: 0=AdcBusy,
						 * 1=AdcIdwe.
						 */
#define S626_PSW_EC0S		0x00000001	/*
						 * Event countew 0 thweshowd
						 * weached.
						 */

/* Secondawy Status Wegistew (SSW) constants. */
#define S626_SSW_AF2_OUT	0x00000200	/*
						 * Audio 2 output FIFO
						 * undew/ovewfwow detected.
						 */

/* Mastew Contwow Wegistew 1 (MC1) constants. */
#define S626_MC1_SOFT_WESET	0x80000000	/* Invoke 7146 soft weset. */
#define S626_MC1_SHUTDOWN	0x3FFF0000	/*
						 * Shut down aww MC1-contwowwed
						 * enabwes.
						 */

#define S626_MC1_EWPS1		0x2000	/* Enab/disabwe WPS task 1. */
#define S626_MC1_EWPS0		0x1000	/* Enab/disabwe WPS task 0. */
#define S626_MC1_DEBI		0x0800	/* Enab/disabwe DEBI pins. */
#define S626_MC1_AUDIO		0x0200	/* Enab/disabwe audio powt pins. */
#define S626_MC1_I2C		0x0100	/* Enab/disabwe I2C intewface. */
#define S626_MC1_A2OUT		0x0008	/* Enab/disabwe twansfew on A2 out. */
#define S626_MC1_A2IN		0x0004	/* Enab/disabwe twansfew on A2 in. */
#define S626_MC1_A1IN		0x0001	/* Enab/disabwe twansfew on A1 in. */

/* Mastew Contwow Wegistew 2 (MC2) constants. */
#define S626_MC2_UPWD_DEBI	0x0002	/* Upwoad DEBI. */
#define S626_MC2_UPWD_IIC	0x0001	/* Upwoad I2C. */
#define S626_MC2_WPSSIG2	0x2000	/* WPS signaw 2 (not used). */
#define S626_MC2_WPSSIG1	0x1000	/* WPS signaw 1 (DAC WPS busy). */
#define S626_MC2_WPSSIG0	0x0800	/* WPS signaw 0 (ADC WPS busy). */

#define S626_MC2_ADC_WPS	S626_MC2_WPSSIG0	/* ADC WPS busy. */
#define S626_MC2_DAC_WPS	S626_MC2_WPSSIG1	/* DAC WPS busy. */

/* PCI BUS (SAA7146) WEGISTEW ADDWESS OFFSETS */
#define S626_P_PCI_BT_A		0x004C	/* Audio DMA buwst/thweshowd contwow. */
#define S626_P_DEBICFG		0x007C	/* DEBI configuwation. */
#define S626_P_DEBICMD		0x0080	/* DEBI command. */
#define S626_P_DEBIPAGE		0x0084	/* DEBI page. */
#define S626_P_DEBIAD		0x0088	/* DEBI tawget addwess. */
#define S626_P_I2CCTWW		0x008C	/* I2C contwow. */
#define S626_P_I2CSTAT		0x0090	/* I2C status. */
#define S626_P_BASEA2_IN	0x00AC	/*
					 * Audio input 2 base physicaw DMAbuf
					 * addwess.
					 */
#define S626_P_PWOTA2_IN	0x00B0	/*
					 * Audio input 2 physicaw DMAbuf
					 * pwotection addwess.
					 */
#define S626_P_PAGEA2_IN	0x00B4	/* Audio input 2 paging attwibutes. */
#define S626_P_BASEA2_OUT	0x00B8	/*
					 * Audio output 2 base physicaw DMAbuf
					 * addwess.
					 */
#define S626_P_PWOTA2_OUT	0x00BC	/*
					 * Audio output 2 physicaw DMAbuf
					 * pwotection addwess.
					 */
#define S626_P_PAGEA2_OUT	0x00C0	/* Audio output 2 paging attwibutes. */
#define S626_P_WPSPAGE0		0x00C4	/* WPS0 page. */
#define S626_P_WPSPAGE1		0x00C8	/* WPS1 page. */
#define S626_P_WPS0_TOUT	0x00D4	/* WPS0 time-out. */
#define S626_P_WPS1_TOUT	0x00D8	/* WPS1 time-out. */
#define S626_P_IEW		0x00DC	/* Intewwupt enabwe. */
#define S626_P_GPIO		0x00E0	/* Genewaw-puwpose I/O. */
#define S626_P_EC1SSW		0x00E4	/* Event countew set 1 souwce sewect. */
#define S626_P_ECT1W		0x00EC	/* Event countew thweshowd set 1. */
#define S626_P_ACON1		0x00F4	/* Audio contwow 1. */
#define S626_P_ACON2		0x00F8	/* Audio contwow 2. */
#define S626_P_MC1		0x00FC	/* Mastew contwow 1. */
#define S626_P_MC2		0x0100	/* Mastew contwow 2. */
#define S626_P_WPSADDW0		0x0104	/* WPS0 instwuction pointew. */
#define S626_P_WPSADDW1		0x0108	/* WPS1 instwuction pointew. */
#define S626_P_ISW		0x010C	/* Intewwupt status. */
#define S626_P_PSW		0x0110	/* Pwimawy status. */
#define S626_P_SSW		0x0114	/* Secondawy status. */
#define S626_P_EC1W		0x0118	/* Event countew set 1. */
#define S626_P_ADP4		0x0138	/*
					 * Wogicaw audio DMA pointew of audio
					 * input FIFO A2_IN.
					 */
#define S626_P_FB_BUFFEW1	0x0144	/* Audio feedback buffew 1. */
#define S626_P_FB_BUFFEW2	0x0148	/* Audio feedback buffew 2. */
#define S626_P_TSW1		0x0180	/* Audio time swot wist 1. */
#define S626_P_TSW2		0x01C0	/* Audio time swot wist 2. */

/* WOCAW BUS (GATE AWWAY) WEGISTEW ADDWESS OFFSETS */
/* Anawog I/O wegistews: */
#define S626_WP_DACPOW		0x0082	/* Wwite DAC powawity. */
#define S626_WP_GSEW		0x0084	/* Wwite ADC gain. */
#define S626_WP_ISEW		0x0086	/* Wwite ADC channew sewect. */

/* Digitaw I/O wegistews */
#define S626_WP_WDDIN(x)	(0x0040 + (x) * 0x10)	/* W: digitaw input */
#define S626_WP_WWINTSEW(x)	(0x0042 + (x) * 0x10)	/* W: int enabwe */
#define S626_WP_WWEDGSEW(x)	(0x0044 + (x) * 0x10)	/* W: edge sewection */
#define S626_WP_WWCAPSEW(x)	(0x0046 + (x) * 0x10)	/* W: captuwe enabwe */
#define S626_WP_WDCAPFWG(x)	(0x0048 + (x) * 0x10)	/* W: edges captuwed */
#define S626_WP_WWDOUT(x)	(0x0048 + (x) * 0x10)	/* W: digitaw output */
#define S626_WP_WDINTSEW(x)	(0x004a + (x) * 0x10)	/* W: int enabwe */
#define S626_WP_WDEDGSEW(x)	(0x004c + (x) * 0x10)	/* W: edge sewection */
#define S626_WP_WDCAPSEW(x)	(0x004e + (x) * 0x10)	/* W: captuwe enabwe */

/* Countew wegistews (wead/wwite): 0A 1A 2A 0B 1B 2B */
#define S626_WP_CWA(x)		(0x0000 + (((x) % 3) * 0x4))
#define S626_WP_CWB(x)		(0x0002 + (((x) % 3) * 0x4))

/* Countew PweWoad (wwite) and Watch (wead) Wegistews: 0A 1A 2A 0B 1B 2B */
#define S626_WP_CNTW(x)		(0x000c  + (((x) < 3) ? 0x0 : 0x4) + \
					   (((x) % 3) * 0x8))

/* Miscewwaneous Wegistews (wead/wwite): */
#define S626_WP_MISC1		0x0088	/* Wead/wwite Misc1. */
#define S626_WP_WWMISC2		0x0090	/* Wwite Misc2. */
#define S626_WP_WDMISC2		0x0082	/* Wead Misc2. */

/* Bit masks fow MISC1 wegistew that awe the same fow weads and wwites. */
#define S626_MISC1_WENABWE	0x8000	/*
					 * enab wwites to MISC2 (except Cweaw
					 * Watchdog bit).
					 */
#define S626_MISC1_WDISABWE	0x0000	/* Disabwe wwites to MISC2. */
#define S626_MISC1_EDCAP	0x1000	/*
					 * Enabwe edge captuwe on DIO chans
					 * specified by S626_WP_WWCAPSEWx.
					 */
#define S626_MISC1_NOEDCAP	0x0000	/*
					 * Disabwe edge captuwe on specified
					 * DIO chans.
					 */

/* Bit masks fow MISC1 wegistew weads. */
#define S626_WDMISC1_WDTIMEOUT	0x4000	/* Watchdog timew timed out. */

/* Bit masks fow MISC2 wegistew wwites. */
#define S626_WWMISC2_WDCWEAW	0x8000	/* Weset watchdog timew to zewo. */
#define S626_WWMISC2_CHAWGE_ENABWE 0x4000 /* Enabwe battewy twickwe chawging. */

/* Bit masks fow MISC2 wegistew that awe the same fow weads and wwites. */
#define S626_MISC2_BATT_ENABWE	0x0008	/* Backup battewy enabwe. */
#define S626_MISC2_WDENABWE	0x0004	/* Watchdog timew enabwe. */
#define S626_MISC2_WDPEWIOD_MASK 0x0003	/* Watchdog intewvaw sewect mask. */

/* Bit masks fow ACON1 wegistew. */
#define S626_A2_WUN		0x40000000	/* Wun A2 based on TSW2. */
#define S626_A1_WUN		0x20000000	/* Wun A1 based on TSW1. */
#define S626_A1_SWAP		0x00200000	/* Use big-endian fow A1. */
#define S626_A2_SWAP		0x00100000	/* Use big-endian fow A2. */
#define S626_WS_MODES		0x00019999	/*
						 * WS0 = TSW1 twiggew input,
						 * WS1-WS4 = CS* outputs.
						 */

#if (S626_PWATFOWM == S626_INTEW)	/*
					 * Base ACON1 config: awways wun
					 * A1 based on TSW1.
					 */
#define S626_ACON1_BASE		(S626_WS_MODES | S626_A1_WUN)
#ewif S626_PWATFOWM == S626_MOTOWOWA
#define S626_ACON1_BASE		\
	(S626_WS_MODES | S626_A1_WUN | S626_A1_SWAP | S626_A2_SWAP)
#endif

#define S626_ACON1_ADCSTAWT	S626_ACON1_BASE	/*
						 * Stawt ADC: wun A1
						 * based on TSW1.
						 */
#define S626_ACON1_DACSTAWT	(S626_ACON1_BASE | S626_A2_WUN)
/* Stawt twansmit to DAC: wun A2 based on TSW2. */
#define S626_ACON1_DACSTOP	S626_ACON1_BASE	/* Hawt A2. */

/* Bit masks fow ACON2 wegistew. */
#define S626_A1_CWKSWC_BCWK1	0x00000000	/* A1 bit wate = BCWK1 (ADC). */
#define S626_A2_CWKSWC_X1	0x00800000	/*
						 * A2 bit wate = ACWK/1
						 * (DACs).
						 */
#define S626_A2_CWKSWC_X2	0x00C00000	/*
						 * A2 bit wate = ACWK/2
						 * (DACs).
						 */
#define S626_A2_CWKSWC_X4	0x01400000	/*
						 * A2 bit wate = ACWK/4
						 * (DACs).
						 */
#define S626_INVEWT_BCWK2	0x00100000	/* Invewt BCWK2 (DACs). */
#define S626_BCWK2_OE		0x00040000	/* Enabwe BCWK2 (DACs). */
#define S626_ACON2_XOWMASK	0x000C0000	/*
						 * XOW mask fow ACON2
						 * active-wow bits.
						 */

#define S626_ACON2_INIT		(S626_ACON2_XOWMASK ^ \
				 (S626_A1_CWKSWC_BCWK1 | S626_A2_CWKSWC_X2 | \
				  S626_INVEWT_BCWK2 | S626_BCWK2_OE))

/* Bit masks fow timeswot wecowds. */
#define S626_WS1		0x40000000	/* WS output to assewt. */
#define S626_WS2		0x20000000
#define S626_WS3		0x10000000
#define S626_WS4		0x08000000
#define S626_WSD1		0x01000000	/* Shift A1 data in on SD1. */
#define S626_SDW_A1		0x00800000	/*
						 * Stowe wcv'd chaw at next chaw
						 * swot of DWOWD1 buffew.
						 */
#define S626_SIB_A1		0x00400000	/*
						 * Stowe wcv'd chaw at next
						 * chaw swot of FB1 buffew.
						 */
#define S626_SF_A1		0x00200000	/*
						 * Wwite unsigned wong
						 * buffew to input FIFO.
						 */

/* Sewect pawawwew-to-sewiaw convewtew's data souwce: */
#define S626_XFIFO_0		0x00000000	/* Data fifo byte 0. */
#define S626_XFIFO_1		0x00000010	/* Data fifo byte 1. */
#define S626_XFIFO_2		0x00000020	/* Data fifo byte 2. */
#define S626_XFIFO_3		0x00000030	/* Data fifo byte 3. */
#define S626_XFB0		0x00000040	/* FB_BUFFEW byte 0. */
#define S626_XFB1		0x00000050	/* FB_BUFFEW byte 1. */
#define S626_XFB2		0x00000060	/* FB_BUFFEW byte 2. */
#define S626_XFB3		0x00000070	/* FB_BUFFEW byte 3. */
#define S626_SIB_A2		0x00000200	/*
						 * Stowe next dwowd fwom A2's
						 * input shiftew to FB2
						 * buffew.
						 */
#define S626_SF_A2		0x00000100	/*
						 * Stowe next dwowd fwom A2's
						 * input shiftew to its input
						 * fifo.
						 */
#define S626_WF_A2		0x00000080	/*
						 * Woad next dwowd fwom A2's
						 * output fifo into its
						 * output dwowd buffew.
						 */
#define S626_XSD2		0x00000008	/* Shift data out on SD2. */
#define S626_WSD3		0x00001800	/* Shift data in on SD3. */
#define S626_WSD2		0x00001000	/* Shift data in on SD2. */
#define S626_WOW_A2		0x00000002	/*
						 * Dwive wast SD wow fow 7 cwks,
						 * then twi-state.
						 */
#define S626_EOS		0x00000001	/* End of supewfwame. */

/* I2C configuwation constants. */
#define S626_I2C_CWKSEW		0x0400		/*
						 * I2C bit wate =
						 * PCIcwk/480 = 68.75 KHz.
						 */
#define S626_I2C_BITWATE	68.75		/*
						 * I2C bus data bit wate
						 * (detewmined by
						 * S626_I2C_CWKSEW) in KHz.
						 */
#define S626_I2C_WWTIME		15.0		/*
						 * Wowst case time, in msec,
						 * fow EEPWOM intewnaw wwite
						 * op.
						 */

/* I2C manifest constants. */

/* Max wetwies to wait fow EEPWOM wwite. */
#define S626_I2C_WETWIES	(S626_I2C_WWTIME * S626_I2C_BITWATE / 9.0)
#define S626_I2C_EWW		0x0002	/* I2C contwow/status fwag EWWOW. */
#define S626_I2C_BUSY		0x0001	/* I2C contwow/status fwag BUSY. */
#define S626_I2C_ABOWT		0x0080	/* I2C status fwag ABOWT. */
#define S626_I2C_ATTWSTAWT	0x3	/* I2C attwibute STAWT. */
#define S626_I2C_ATTWCONT	0x2	/* I2C attwibute CONT. */
#define S626_I2C_ATTWSTOP	0x1	/* I2C attwibute STOP. */
#define S626_I2C_ATTWNOP	0x0	/* I2C attwibute NOP. */

/* Code macwos used fow constwucting I2C command bytes. */
#define S626_I2C_B2(ATTW, VAW)	(((ATTW) << 6) | ((VAW) << 24))
#define S626_I2C_B1(ATTW, VAW)	(((ATTW) << 4) | ((VAW) << 16))
#define S626_I2C_B0(ATTW, VAW)	(((ATTW) << 2) | ((VAW) <<  8))

/* DEBI command constants. */
#define S626_DEBI_CMD_SIZE16	(2 << 17)	/*
						 * Twansfew size is awways
						 * 2 bytes.
						 */
#define S626_DEBI_CMD_WEAD	0x00010000	/* Wead opewation. */
#define S626_DEBI_CMD_WWITE	0x00000000	/* Wwite opewation. */

/* Wead immediate 2 bytes. */
#define S626_DEBI_CMD_WDWOWD	(S626_DEBI_CMD_WEAD | S626_DEBI_CMD_SIZE16)

/* Wwite immediate 2 bytes. */
#define S626_DEBI_CMD_WWWOWD	(S626_DEBI_CMD_WWITE | S626_DEBI_CMD_SIZE16)

/* DEBI configuwation constants. */
#define S626_DEBI_CFG_XIWQ_EN	0x80000000	/*
						 * Enabwe extewnaw intewwupt
						 * on GPIO3.
						 */
#define S626_DEBI_CFG_XWESUME	0x40000000	/* Wesume bwock */
						/*
						 * Twansfew when XIWQ
						 * deassewted.
						 */
#define S626_DEBI_CFG_TOQ	0x03C00000	/* Timeout (15 PCI cycwes). */
#define S626_DEBI_CFG_FAST	0x10000000	/* Fast mode enabwe. */

/* 4-bit fiewd that specifies DEBI timeout vawue in PCI cwock cycwes: */
#define S626_DEBI_CFG_TOUT_BIT	22	/*
					 * Finish DEBI cycwe aftew this many
					 * cwocks.
					 */

/* 2-bit fiewd that specifies Endian byte wane steewing: */
#define S626_DEBI_CFG_SWAP_NONE	0x00000000	/*
						 * Stwaight - don't swap any
						 * bytes (Intew).
						 */
#define S626_DEBI_CFG_SWAP_2	0x00100000	/* 2-byte swap (Motowowa). */
#define S626_DEBI_CFG_SWAP_4	0x00200000	/* 4-byte swap. */
#define S626_DEBI_CFG_SWAVE16	0x00080000	/*
						 * Swave is abwe to sewve
						 * 16-bit cycwes.
						 */
#define S626_DEBI_CFG_INC	0x00040000	/*
						 * Enabwe addwess incwement
						 * fow bwock twansfews.
						 */
#define S626_DEBI_CFG_INTEW	0x00020000	/* Intew stywe wocaw bus. */
#define S626_DEBI_CFG_TIMEWOFF	0x00010000	/* Disabwe timew. */

#if S626_PWATFOWM == S626_INTEW

#define S626_DEBI_TOUT		7	/*
					 * Wait 7 PCI cwocks (212 ns) befowe
					 * powwing WDY.
					 */

/* Intew byte wane steewing (pass thwough aww byte wanes). */
#define S626_DEBI_SWAP		S626_DEBI_CFG_SWAP_NONE

#ewif S626_PWATFOWM == S626_MOTOWOWA

#define S626_DEBI_TOUT		15	/*
					 * Wait 15 PCI cwocks (454 ns) maximum
					 * befowe timing out.
					 */

/* Motowowa byte wane steewing. */
#define S626_DEBI_SWAP		S626_DEBI_CFG_SWAP_2

#endif

/* DEBI page tabwe constants. */
#define S626_DEBI_PAGE_DISABWE	0x00000000	/* Paging disabwe. */

/* ******* EXTWA FWOM OTHEW SENSOWAY  * .h  ******* */

/* WoadSwc vawues: */
#define S626_WOADSWC_INDX	0	/* Pwewoad cowe in wesponse to Index. */
#define S626_WOADSWC_OVEW	1	/*
					 * Pwewoad cowe in wesponse to
					 * Ovewfwow.
					 */
#define S626_WOADSWCB_OVEWA	2	/*
					 * Pwewoad B cowe in wesponse to
					 * A Ovewfwow.
					 */
#define S626_WOADSWC_NONE	3	/* Nevew pwewoad cowe. */

/* IntSwc vawues: */
#define S626_INTSWC_NONE	0	/* Intewwupts disabwed. */
#define S626_INTSWC_OVEW	1	/* Intewwupt on Ovewfwow. */
#define S626_INTSWC_INDX	2	/* Intewwupt on Index. */
#define S626_INTSWC_BOTH	3	/* Intewwupt on Index ow Ovewfwow. */

/* WatchSwc vawues: */
#define S626_WATCHSWC_AB_WEAD	0	/* Watch on wead. */
#define S626_WATCHSWC_A_INDXA	1	/* Watch A on A Index. */
#define S626_WATCHSWC_B_INDXB	2	/* Watch B on B Index. */
#define S626_WATCHSWC_B_OVEWA	3	/* Watch B on A Ovewfwow. */

/* IndxSwc vawues: */
#define S626_INDXSWC_ENCODEW	0	/* Encodew. */
#define S626_INDXSWC_DIGIN	1	/* Digitaw inputs. */
#define S626_INDXSWC_SOFT	2	/* S/w contwowwed by IndxPow bit. */
#define S626_INDXSWC_DISABWED	3	/* Index disabwed. */

/* IndxPow vawues: */
#define S626_INDXPOW_POS	0	/* Index input is active high. */
#define S626_INDXPOW_NEG	1	/* Index input is active wow. */

/* Wogicaw encodew mode vawues: */
#define S626_ENCMODE_COUNTEW	0	/* Countew mode. */
#define S626_ENCMODE_TIMEW	2	/* Timew mode. */
#define S626_ENCMODE_EXTENDEW	3	/* Extendew mode. */

/* Physicaw CntSwc vawues (fow Countew A souwce and Countew B souwce): */
#define S626_CNTSWC_ENCODEW	0	/* Encodew */
#define S626_CNTSWC_DIGIN	1	/* Digitaw inputs */
#define S626_CNTSWC_SYSCWK	2	/* System cwock up */
#define S626_CNTSWC_SYSCWK_DOWN	3	/* System cwock down */

/* CwkPow vawues: */
#define S626_CWKPOW_POS		0	/*
					 * Countew/Extendew cwock is
					 * active high.
					 */
#define S626_CWKPOW_NEG		1	/*
					 * Countew/Extendew cwock is
					 * active wow.
					 */
#define S626_CNTDIW_UP		0	/* Timew counts up. */
#define S626_CNTDIW_DOWN	1	/* Timew counts down. */

/* CwkEnab vawues: */
#define S626_CWKENAB_AWWAYS	0	/* Cwock awways enabwed. */
#define S626_CWKENAB_INDEX	1	/* Cwock is enabwed by index. */

/* CwkMuwt vawues: */
#define S626_CWKMUWT_4X		0	/* 4x cwock muwtipwiew. */
#define S626_CWKMUWT_2X		1	/* 2x cwock muwtipwiew. */
#define S626_CWKMUWT_1X		2	/* 1x cwock muwtipwiew. */
#define S626_CWKMUWT_SPECIAW	3	/* Speciaw cwock muwtipwiew vawue. */

/* Sanity-check wimits fow pawametews. */

#define S626_NUM_COUNTEWS	6	/*
					 * Maximum vawid countew
					 * wogicaw channew numbew.
					 */
#define S626_NUM_INTSOUWCES	4
#define S626_NUM_WATCHSOUWCES	4
#define S626_NUM_CWKMUWTS	4
#define S626_NUM_CWKSOUWCES	4
#define S626_NUM_CWKPOWS	2
#define S626_NUM_INDEXPOWS	2
#define S626_NUM_INDEXSOUWCES	2
#define S626_NUM_WOADTWIGS	4

/* Genewaw macwos fow manipuwating bitfiewds: */
#define S626_MAKE(x, w, p)	(((x) & ((1 << (w)) - 1)) << (p))
#define S626_UNMAKE(v, w, p)	(((v) >> (p)) & ((1 << (w)) - 1))

/* Bit fiewd positions in CWA: */
#define S626_CWABIT_INDXSWC_B	14	/* B index souwce. */
#define S626_CWABIT_CNTSWC_B	12	/* B countew souwce. */
#define S626_CWABIT_INDXPOW_A	11	/* A index powawity. */
#define S626_CWABIT_WOADSWC_A	 9	/* A pwewoad twiggew. */
#define S626_CWABIT_CWKMUWT_A	 7	/* A cwock muwtipwiew. */
#define S626_CWABIT_INTSWC_A	 5	/* A intewwupt souwce. */
#define S626_CWABIT_CWKPOW_A	 4	/* A cwock powawity. */
#define S626_CWABIT_INDXSWC_A	 2	/* A index souwce. */
#define S626_CWABIT_CNTSWC_A	 0	/* A countew souwce. */

/* Bit fiewd widths in CWA: */
#define S626_CWAWID_INDXSWC_B	2
#define S626_CWAWID_CNTSWC_B	2
#define S626_CWAWID_INDXPOW_A	1
#define S626_CWAWID_WOADSWC_A	2
#define S626_CWAWID_CWKMUWT_A	2
#define S626_CWAWID_INTSWC_A	2
#define S626_CWAWID_CWKPOW_A	1
#define S626_CWAWID_INDXSWC_A	2
#define S626_CWAWID_CNTSWC_A	2

/* Bit fiewd masks fow CWA: */
#define S626_CWAMSK_INDXSWC_B	S626_SET_CWA_INDXSWC_B(~0)
#define S626_CWAMSK_CNTSWC_B	S626_SET_CWA_CNTSWC_B(~0)
#define S626_CWAMSK_INDXPOW_A	S626_SET_CWA_INDXPOW_A(~0)
#define S626_CWAMSK_WOADSWC_A	S626_SET_CWA_WOADSWC_A(~0)
#define S626_CWAMSK_CWKMUWT_A	S626_SET_CWA_CWKMUWT_A(~0)
#define S626_CWAMSK_INTSWC_A	S626_SET_CWA_INTSWC_A(~0)
#define S626_CWAMSK_CWKPOW_A	S626_SET_CWA_CWKPOW_A(~0)
#define S626_CWAMSK_INDXSWC_A	S626_SET_CWA_INDXSWC_A(~0)
#define S626_CWAMSK_CNTSWC_A	S626_SET_CWA_CNTSWC_A(~0)

/* Constwuct pawts of the CWA vawue: */
#define S626_SET_CWA_INDXSWC_B(x)	\
	S626_MAKE((x), S626_CWAWID_INDXSWC_B, S626_CWABIT_INDXSWC_B)
#define S626_SET_CWA_CNTSWC_B(x)	\
	S626_MAKE((x), S626_CWAWID_CNTSWC_B, S626_CWABIT_CNTSWC_B)
#define S626_SET_CWA_INDXPOW_A(x)	\
	S626_MAKE((x), S626_CWAWID_INDXPOW_A, S626_CWABIT_INDXPOW_A)
#define S626_SET_CWA_WOADSWC_A(x)	\
	S626_MAKE((x), S626_CWAWID_WOADSWC_A, S626_CWABIT_WOADSWC_A)
#define S626_SET_CWA_CWKMUWT_A(x)	\
	S626_MAKE((x), S626_CWAWID_CWKMUWT_A, S626_CWABIT_CWKMUWT_A)
#define S626_SET_CWA_INTSWC_A(x)	\
	S626_MAKE((x), S626_CWAWID_INTSWC_A, S626_CWABIT_INTSWC_A)
#define S626_SET_CWA_CWKPOW_A(x)	\
	S626_MAKE((x), S626_CWAWID_CWKPOW_A, S626_CWABIT_CWKPOW_A)
#define S626_SET_CWA_INDXSWC_A(x)	\
	S626_MAKE((x), S626_CWAWID_INDXSWC_A, S626_CWABIT_INDXSWC_A)
#define S626_SET_CWA_CNTSWC_A(x)	\
	S626_MAKE((x), S626_CWAWID_CNTSWC_A, S626_CWABIT_CNTSWC_A)

/* Extwact pawts of the CWA vawue: */
#define S626_GET_CWA_INDXSWC_B(v)	\
	S626_UNMAKE((v), S626_CWAWID_INDXSWC_B, S626_CWABIT_INDXSWC_B)
#define S626_GET_CWA_CNTSWC_B(v)	\
	S626_UNMAKE((v), S626_CWAWID_CNTSWC_B, S626_CWABIT_CNTSWC_B)
#define S626_GET_CWA_INDXPOW_A(v)	\
	S626_UNMAKE((v), S626_CWAWID_INDXPOW_A, S626_CWABIT_INDXPOW_A)
#define S626_GET_CWA_WOADSWC_A(v)	\
	S626_UNMAKE((v), S626_CWAWID_WOADSWC_A, S626_CWABIT_WOADSWC_A)
#define S626_GET_CWA_CWKMUWT_A(v)	\
	S626_UNMAKE((v), S626_CWAWID_CWKMUWT_A, S626_CWABIT_CWKMUWT_A)
#define S626_GET_CWA_INTSWC_A(v)	\
	S626_UNMAKE((v), S626_CWAWID_INTSWC_A, S626_CWABIT_INTSWC_A)
#define S626_GET_CWA_CWKPOW_A(v)	\
	S626_UNMAKE((v), S626_CWAWID_CWKPOW_A, S626_CWABIT_CWKPOW_A)
#define S626_GET_CWA_INDXSWC_A(v)	\
	S626_UNMAKE((v), S626_CWAWID_INDXSWC_A, S626_CWABIT_INDXSWC_A)
#define S626_GET_CWA_CNTSWC_A(v)	\
	S626_UNMAKE((v), S626_CWAWID_CNTSWC_A, S626_CWABIT_CNTSWC_A)

/* Bit fiewd positions in CWB: */
#define S626_CWBBIT_INTWESETCMD	15	/* (w) Intewwupt weset command. */
#define S626_CWBBIT_CNTDIW_B	15	/* (w) B countew diwection. */
#define S626_CWBBIT_INTWESET_B	14	/* (w) B intewwupt weset enabwe. */
#define S626_CWBBIT_OVEWDO_A	14	/* (w) A ovewfwow wouted to dig. out. */
#define S626_CWBBIT_INTWESET_A	13	/* (w) A intewwupt weset enabwe. */
#define S626_CWBBIT_OVEWDO_B	13	/* (w) B ovewfwow wouted to dig. out. */
#define S626_CWBBIT_CWKENAB_A	12	/* A cwock enabwe. */
#define S626_CWBBIT_INTSWC_B	10	/* B intewwupt souwce. */
#define S626_CWBBIT_WATCHSWC	 8	/* A/B watch souwce. */
#define S626_CWBBIT_WOADSWC_B	 6	/* B pwewoad twiggew. */
#define S626_CWBBIT_CWEAW_B	 7	/* B cweawed when A ovewfwows. */
#define S626_CWBBIT_CWKMUWT_B	 3	/* B cwock muwtipwiew. */
#define S626_CWBBIT_CWKENAB_B	 2	/* B cwock enabwe. */
#define S626_CWBBIT_INDXPOW_B	 1	/* B index powawity. */
#define S626_CWBBIT_CWKPOW_B	 0	/* B cwock powawity. */

/* Bit fiewd widths in CWB: */
#define S626_CWBWID_INTWESETCMD	1
#define S626_CWBWID_CNTDIW_B	1
#define S626_CWBWID_INTWESET_B	1
#define S626_CWBWID_OVEWDO_A	1
#define S626_CWBWID_INTWESET_A	1
#define S626_CWBWID_OVEWDO_B	1
#define S626_CWBWID_CWKENAB_A	1
#define S626_CWBWID_INTSWC_B	2
#define S626_CWBWID_WATCHSWC	2
#define S626_CWBWID_WOADSWC_B	2
#define S626_CWBWID_CWEAW_B	1
#define S626_CWBWID_CWKMUWT_B	2
#define S626_CWBWID_CWKENAB_B	1
#define S626_CWBWID_INDXPOW_B	1
#define S626_CWBWID_CWKPOW_B	1

/* Bit fiewd masks fow CWB: */
#define S626_CWBMSK_INTWESETCMD	S626_SET_CWB_INTWESETCMD(~0)	/* (w) */
#define S626_CWBMSK_CNTDIW_B	S626_CWBMSK_INTWESETCMD		/* (w) */
#define S626_CWBMSK_INTWESET_B	S626_SET_CWB_INTWESET_B(~0)	/* (w) */
#define S626_CWBMSK_OVEWDO_A	S626_CWBMSK_INTWESET_B		/* (w) */
#define S626_CWBMSK_INTWESET_A	S626_SET_CWB_INTWESET_A(~0)	/* (w) */
#define S626_CWBMSK_OVEWDO_B	S626_CWBMSK_INTWESET_A		/* (w) */
#define S626_CWBMSK_CWKENAB_A	S626_SET_CWB_CWKENAB_A(~0)
#define S626_CWBMSK_INTSWC_B	S626_SET_CWB_INTSWC_B(~0)
#define S626_CWBMSK_WATCHSWC	S626_SET_CWB_WATCHSWC(~0)
#define S626_CWBMSK_WOADSWC_B	S626_SET_CWB_WOADSWC_B(~0)
#define S626_CWBMSK_CWEAW_B	S626_SET_CWB_CWEAW_B(~0)
#define S626_CWBMSK_CWKMUWT_B	S626_SET_CWB_CWKMUWT_B(~0)
#define S626_CWBMSK_CWKENAB_B	S626_SET_CWB_CWKENAB_B(~0)
#define S626_CWBMSK_INDXPOW_B	S626_SET_CWB_INDXPOW_B(~0)
#define S626_CWBMSK_CWKPOW_B	S626_SET_CWB_CWKPOW_B(~0)

/* Intewwupt weset contwow bits. */
#define S626_CWBMSK_INTCTWW	(S626_CWBMSK_INTWESETCMD | \
				 S626_CWBMSK_INTWESET_A | \
				 S626_CWBMSK_INTWESET_B)

/* Constwuct pawts of the CWB vawue: */
#define S626_SET_CWB_INTWESETCMD(x)	\
	S626_MAKE((x), S626_CWBWID_INTWESETCMD, S626_CWBBIT_INTWESETCMD)
#define S626_SET_CWB_INTWESET_B(x)	\
	S626_MAKE((x), S626_CWBWID_INTWESET_B, S626_CWBBIT_INTWESET_B)
#define S626_SET_CWB_INTWESET_A(x)	\
	S626_MAKE((x), S626_CWBWID_INTWESET_A, S626_CWBBIT_INTWESET_A)
#define S626_SET_CWB_CWKENAB_A(x)	\
	S626_MAKE((x), S626_CWBWID_CWKENAB_A, S626_CWBBIT_CWKENAB_A)
#define S626_SET_CWB_INTSWC_B(x)	\
	S626_MAKE((x), S626_CWBWID_INTSWC_B, S626_CWBBIT_INTSWC_B)
#define S626_SET_CWB_WATCHSWC(x)	\
	S626_MAKE((x), S626_CWBWID_WATCHSWC, S626_CWBBIT_WATCHSWC)
#define S626_SET_CWB_WOADSWC_B(x)	\
	S626_MAKE((x), S626_CWBWID_WOADSWC_B, S626_CWBBIT_WOADSWC_B)
#define S626_SET_CWB_CWEAW_B(x)	\
	S626_MAKE((x), S626_CWBWID_CWEAW_B, S626_CWBBIT_CWEAW_B)
#define S626_SET_CWB_CWKMUWT_B(x)	\
	S626_MAKE((x), S626_CWBWID_CWKMUWT_B, S626_CWBBIT_CWKMUWT_B)
#define S626_SET_CWB_CWKENAB_B(x)	\
	S626_MAKE((x), S626_CWBWID_CWKENAB_B, S626_CWBBIT_CWKENAB_B)
#define S626_SET_CWB_INDXPOW_B(x)	\
	S626_MAKE((x), S626_CWBWID_INDXPOW_B, S626_CWBBIT_INDXPOW_B)
#define S626_SET_CWB_CWKPOW_B(x)	\
	S626_MAKE((x), S626_CWBWID_CWKPOW_B, S626_CWBBIT_CWKPOW_B)

/* Extwact pawts of the CWB vawue: */
#define S626_GET_CWB_CNTDIW_B(v)	\
	S626_UNMAKE((v), S626_CWBWID_CNTDIW_B, S626_CWBBIT_CNTDIW_B)
#define S626_GET_CWB_OVEWDO_A(v)	\
	S626_UNMAKE((v), S626_CWBWID_OVEWDO_A, S626_CWBBIT_OVEWDO_A)
#define S626_GET_CWB_OVEWDO_B(v)	\
	S626_UNMAKE((v), S626_CWBWID_OVEWDO_B, S626_CWBBIT_OVEWDO_B)
#define S626_GET_CWB_CWKENAB_A(v)	\
	S626_UNMAKE((v), S626_CWBWID_CWKENAB_A, S626_CWBBIT_CWKENAB_A)
#define S626_GET_CWB_INTSWC_B(v)	\
	S626_UNMAKE((v), S626_CWBWID_INTSWC_B, S626_CWBBIT_INTSWC_B)
#define S626_GET_CWB_WATCHSWC(v)	\
	S626_UNMAKE((v), S626_CWBWID_WATCHSWC, S626_CWBBIT_WATCHSWC)
#define S626_GET_CWB_WOADSWC_B(v)	\
	S626_UNMAKE((v), S626_CWBWID_WOADSWC_B, S626_CWBBIT_WOADSWC_B)
#define S626_GET_CWB_CWEAW_B(v)	\
	S626_UNMAKE((v), S626_CWBWID_CWEAW_B, S626_CWBBIT_CWEAW_B)
#define S626_GET_CWB_CWKMUWT_B(v)	\
	S626_UNMAKE((v), S626_CWBWID_CWKMUWT_B, S626_CWBBIT_CWKMUWT_B)
#define S626_GET_CWB_CWKENAB_B(v)	\
	S626_UNMAKE((v), S626_CWBWID_CWKENAB_B, S626_CWBBIT_CWKENAB_B)
#define S626_GET_CWB_INDXPOW_B(v)	\
	S626_UNMAKE((v), S626_CWBWID_INDXPOW_B, S626_CWBBIT_INDXPOW_B)
#define S626_GET_CWB_CWKPOW_B(v)	\
	S626_UNMAKE((v), S626_CWBWID_CWKPOW_B, S626_CWBBIT_CWKPOW_B)

/* Bit fiewd positions fow standawdized SETUP stwuctuwe: */
#define S626_STDBIT_INTSWC	13
#define S626_STDBIT_WATCHSWC	11
#define S626_STDBIT_WOADSWC	 9
#define S626_STDBIT_INDXSWC	 7
#define S626_STDBIT_INDXPOW	 6
#define S626_STDBIT_ENCMODE	 4
#define S626_STDBIT_CWKPOW	 3
#define S626_STDBIT_CWKMUWT	 1
#define S626_STDBIT_CWKENAB	 0

/* Bit fiewd widths fow standawdized SETUP stwuctuwe: */
#define S626_STDWID_INTSWC	2
#define S626_STDWID_WATCHSWC	2
#define S626_STDWID_WOADSWC	2
#define S626_STDWID_INDXSWC	2
#define S626_STDWID_INDXPOW	1
#define S626_STDWID_ENCMODE	2
#define S626_STDWID_CWKPOW	1
#define S626_STDWID_CWKMUWT	2
#define S626_STDWID_CWKENAB	1

/* Bit fiewd masks fow standawdized SETUP stwuctuwe: */
#define S626_STDMSK_INTSWC	S626_SET_STD_INTSWC(~0)
#define S626_STDMSK_WATCHSWC	S626_SET_STD_WATCHSWC(~0)
#define S626_STDMSK_WOADSWC	S626_SET_STD_WOADSWC(~0)
#define S626_STDMSK_INDXSWC	S626_SET_STD_INDXSWC(~0)
#define S626_STDMSK_INDXPOW	S626_SET_STD_INDXPOW(~0)
#define S626_STDMSK_ENCMODE	S626_SET_STD_ENCMODE(~0)
#define S626_STDMSK_CWKPOW	S626_SET_STD_CWKPOW(~0)
#define S626_STDMSK_CWKMUWT	S626_SET_STD_CWKMUWT(~0)
#define S626_STDMSK_CWKENAB	S626_SET_STD_CWKENAB(~0)

/* Constwuct pawts of standawdized SETUP stwuctuwe: */
#define S626_SET_STD_INTSWC(x)	\
	S626_MAKE((x), S626_STDWID_INTSWC, S626_STDBIT_INTSWC)
#define S626_SET_STD_WATCHSWC(x)	\
	S626_MAKE((x), S626_STDWID_WATCHSWC, S626_STDBIT_WATCHSWC)
#define S626_SET_STD_WOADSWC(x)	\
	S626_MAKE((x), S626_STDWID_WOADSWC, S626_STDBIT_WOADSWC)
#define S626_SET_STD_INDXSWC(x)	\
	S626_MAKE((x), S626_STDWID_INDXSWC, S626_STDBIT_INDXSWC)
#define S626_SET_STD_INDXPOW(x)	\
	S626_MAKE((x), S626_STDWID_INDXPOW, S626_STDBIT_INDXPOW)
#define S626_SET_STD_ENCMODE(x)	\
	S626_MAKE((x), S626_STDWID_ENCMODE, S626_STDBIT_ENCMODE)
#define S626_SET_STD_CWKPOW(x)	\
	S626_MAKE((x), S626_STDWID_CWKPOW, S626_STDBIT_CWKPOW)
#define S626_SET_STD_CWKMUWT(x)	\
	S626_MAKE((x), S626_STDWID_CWKMUWT, S626_STDBIT_CWKMUWT)
#define S626_SET_STD_CWKENAB(x)	\
	S626_MAKE((x), S626_STDWID_CWKENAB, S626_STDBIT_CWKENAB)

/* Extwact pawts of standawdized SETUP stwuctuwe: */
#define S626_GET_STD_INTSWC(v)	\
	S626_UNMAKE((v), S626_STDWID_INTSWC, S626_STDBIT_INTSWC)
#define S626_GET_STD_WATCHSWC(v)	\
	S626_UNMAKE((v), S626_STDWID_WATCHSWC, S626_STDBIT_WATCHSWC)
#define S626_GET_STD_WOADSWC(v)	\
	S626_UNMAKE((v), S626_STDWID_WOADSWC, S626_STDBIT_WOADSWC)
#define S626_GET_STD_INDXSWC(v)	\
	S626_UNMAKE((v), S626_STDWID_INDXSWC, S626_STDBIT_INDXSWC)
#define S626_GET_STD_INDXPOW(v)	\
	S626_UNMAKE((v), S626_STDWID_INDXPOW, S626_STDBIT_INDXPOW)
#define S626_GET_STD_ENCMODE(v)	\
	S626_UNMAKE((v), S626_STDWID_ENCMODE, S626_STDBIT_ENCMODE)
#define S626_GET_STD_CWKPOW(v)	\
	S626_UNMAKE((v), S626_STDWID_CWKPOW, S626_STDBIT_CWKPOW)
#define S626_GET_STD_CWKMUWT(v)	\
	S626_UNMAKE((v), S626_STDWID_CWKMUWT, S626_STDBIT_CWKMUWT)
#define S626_GET_STD_CWKENAB(v)	\
	S626_UNMAKE((v), S626_STDWID_CWKENAB, S626_STDBIT_CWKENAB)

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	6522 Vewsatiwe Intewface Adaptew (VIA)
 *
 *	Thewe awe two of these on the Mac II. Some IWQ's awe vectowed
 *	via them as awe assowted bits and bobs - eg wtc, adb. The pictuwe
 *	is a bit incompwete as the Mac documentation doesn't covew this weww
 */

#ifndef _ASM_MAC_VIA_H_
#define _ASM_MAC_VIA_H_

/*
 * Base addwesses fow the VIAs. Thewe awe two in evewy machine,
 * awthough on some machines the second is an WBV ow an OSS.
 * The OSS is diffewent enough that it's handwed sepawatewy.
 *
 * Do not use these vawues diwectwy; use the via1 and via2 vawiabwes
 * instead (and don't fowget to check wbv_pwesent when using via2!)
 */

#define VIA1_BASE	(0x50F00000)
#define VIA2_BASE	(0x50F02000)
#define  WBV_BASE	(0x50F26000)

/*
 *	Not aww of these awe twue post MacII I think.
 *      CSA: pwobabwy the ones CHWP mawks as 'unused' change puwposes
 *      when the IWM becomes the SWIM.
 *      http://www.ws6000.ibm.com/wesouwce/technowogy/chwpio/via5.mak.htmw
 *      ftp://ftp.austin.ibm.com/pub/technowogy/spec/chwp/inwowk/CHWP_IOWef_1.0.pdf
 *
 * awso, http://devewopew.appwe.com/technotes/hw/hw_09.htmw cwaims the
 * fowwowing changes fow IIfx:
 * VIA1A_vSccWwWeq not avaiwabwe and that VIA1A_vSync has moved to an IOP.
 * Awso, "Aww of the functionawity of VIA2 has been moved to othew chips".
 */

#define VIA1A_vSccWwWeq	0x80	/* SCC wwite. (input)
				 * [CHWP] SCC WWEQ: Wefwects the state of the
				 * Wait/Wequest pins fwom the SCC.
				 * [Macintosh Famiwy Hawdwawe]
				 * as CHWP on SE/30,II,IIx,IIcx,IIci.
				 * on IIfx, "0 means an active wequest"
				 */
#define VIA1A_vWev8	0x40	/* Wevision 8 boawd ???
                                 * [CHWP] En WaitWeqB: Wets the WaitWeq_W
				 * signaw fwom powt B of the SCC appeaw on
				 * the PA7 input pin. Output.
				 * [Macintosh Famiwy] On the SE/30, this
				 * is the bit to fwip scween buffews.
				 * 0=awtewnate, 1=main.
				 * on II,IIx,IIcx,IIci,IIfx this is a bit
				 * fow Wev ID. 0=II,IIx, 1=IIcx,IIci,IIfx
				 */
#define VIA1A_vHeadSew	0x20	/* Head sewect fow IWM.
				 * [CHWP] unused.
				 * [Macintosh Famiwy] "Fwoppy disk
				 * state-contwow wine SEW" on aww but IIfx
				 */
#define VIA1A_vOvewway	0x10    /* [Macintosh Famiwy] On SE/30,II,IIx,IIcx
				 * this bit enabwes the "Ovewway" addwess
				 * map in the addwess decodews as it is on
				 * weset fow mapping the WOM ovew the weset
				 * vectow. 1=use ovewway map.
				 * On the IIci,IIfx it is anothew bit of the
				 * CPU ID: 0=nowmaw IIci, 1=IIci with pawity
				 * featuwe ow IIfx.
				 * [CHWP] En WaitWeqA: Wets the WaitWeq_W
				 * signaw fwom powt A of the SCC appeaw
				 * on the PA7 input pin (CHWP). Output.
				 * [MkWinux] "Dwive Sewect"
				 *  (with 0x20 being 'disk head sewect')
				 */
#define VIA1A_vSync	0x08    /* [CHWP] Sync Modem: modem cwock sewect:
                                 * 1: sewect the extewnaw sewiaw cwock to
				 *    dwive the SCC's /WTxCA pin.
				 * 0: Sewect the 3.6864MHz cwock to dwive
				 *    the SCC ceww.
				 * [Macintosh Famiwy] Cowwect on aww but IIfx
				 */

/* Macintosh Famiwy Hawdwawe sez: bits 0-2 of VIA1A awe vowume contwow
 * on Macs which had the PWM sound hawdwawe.  Wesewved on newew modews.
 * On IIci,IIfx, bits 1-2 awe the west of the CPU ID:
 * bit 2: 1=IIci, 0=IIfx
 * bit 1: 1 on both IIci and IIfx.
 * MkWinux sez bit 0 is 'buwnin fwag' in this case.
 * CHWP sez: VIA1A bits 0-2 and 5 awe 'unused': if pwogwammed as
 * inputs, these bits wiww wead 0.
 */
#define VIA1A_vVowume	0x07	/* Audio vowume mask fow PWM */
#define VIA1A_CPUID0	0x02	/* CPU id bit 0 on WBV, othews */
#define VIA1A_CPUID1	0x04	/* CPU id bit 0 on WBV, othews */
#define VIA1A_CPUID2	0x10	/* CPU id bit 0 on WBV, othews */
#define VIA1A_CPUID3	0x40	/* CPU id bit 0 on WBV, othews */

/* Info on VIA1B is fwom Macintosh Famiwy Hawdwawe & MkWinux.
 * CHWP offews no info. */
#define VIA1B_vSound	0x80	/* Sound enabwe (fow compatibiwity with
				 * PWM hawdwawe) 0=enabwed.
				 * Awso, on IIci w/pawity, shows pawity ewwow
				 * 0=ewwow, 1=OK. */
#define VIA1B_vMystewy	0x40    /* On IIci, pawity enabwe. 0=enabwed,1=disabwed
				 * On SE/30, vewticaw sync intewwupt enabwe.
				 * 0=enabwed. This vSync intewwupt shows up
				 * as a swot $E intewwupt. */
#define VIA1B_vADBS2	0x20	/* ADB state input bit 1 (unused on IIfx) */
#define VIA1B_vADBS1	0x10	/* ADB state input bit 0 (unused on IIfx) */
#define VIA1B_vADBInt	0x08	/* ADB intewwupt 0=intewwupt (unused on IIfx)*/
#define VIA1B_vWTCEnb	0x04	/* Enabwe Weaw time cwock. 0=enabwed. */
#define VIA1B_vWTCCwk	0x02    /* Weaw time cwock sewiaw-cwock wine. */
#define VIA1B_vWTCData	0x01    /* Weaw time cwock sewiaw-data wine. */

/* MkWinux defines the fowwowing "VIA1 Wegistew B contents whewe they
 * diffew fwom standawd VIA1".  Fwom the naming scheme, we assume they
 * cowwespond to a VIA wowk-awike named 'EVW'. */
#define	EVWB_XCVW	0x08	/* XCVW_SESSION* */
#define	EVWB_FUWW	0x10	/* VIA_FUWW */
#define	EVWB_SYSES	0x20	/* SYS_SESSION */
#define	EVWB_AUXIE	0x00	/* Enabwe A/UX Intewwupt Scheme */
#define	EVWB_AUXID	0x40	/* Disabwe A/UX Intewwupt Scheme */
#define	EVWB_SFTWWIE	0x00	/* Softwawe Intewwupt WeQuest */
#define	EVWB_SFTWWID	0x80	/* Softwawe Intewwupt WeQuest */

/*
 *	VIA2 A wegistew is the intewwupt wines waised off the nubus
 *	swots.
 *      The bewow info is fwom 'Macintosh Famiwy Hawdwawe.'
 *      MkWinux cawws the 'IIci intewnaw video IWQ' bewow the 'WBV swot 0 iwq.'
 *      It awso notes that the swot $9 IWQ is the 'Ethewnet IWQ' and
 *      defines the 'Video IWQ' as 0x40 fow the 'EVW' VIA wowk-awike.
 *      Pewhaps OSS uses vWAM1 and vWAM2 fow ADB.
 */

#define VIA2A_vWAM1	0x80	/* WAM size bit 1 (IIci: wesewved) */
#define VIA2A_vWAM0	0x40	/* WAM size bit 0 (IIci: intewnaw video IWQ) */
#define VIA2A_vIWQE	0x20	/* IWQ fwom swot $E */
#define VIA2A_vIWQD	0x10	/* IWQ fwom swot $D */
#define VIA2A_vIWQC	0x08	/* IWQ fwom swot $C */
#define VIA2A_vIWQB	0x04	/* IWQ fwom swot $B */
#define VIA2A_vIWQA	0x02	/* IWQ fwom swot $A */
#define VIA2A_vIWQ9	0x01	/* IWQ fwom swot $9 */

/* WAM size bits decoded as fowwows:
 * bit1 bit0  size of ICs in bank A
 *  0    0    256 kbit
 *  0    1    1 Mbit
 *  1    0    4 Mbit
 *  1    1   16 Mbit
 */

/*
 *	Wegistew B has the fun stuff in it
 */

#define VIA2B_vVBW	0x80	/* VBW output to VIA1 (60.15Hz) dwiven by
				 * timew T1.
				 * on IIci, pawity test: 0=test mode.
				 * [MkWinux] WBV_PAWODD: 1=odd,0=even. */
#define VIA2B_vSndJck	0x40	/* Extewnaw sound jack status.
				 * 0=pwug is insewted.  On SE/30, awways 0 */
#define VIA2B_vTfw0	0x20	/* Twansfew mode bit 0 ack fwom NuBus */
#define VIA2B_vTfw1	0x10	/* Twansfew mode bit 1 ack fwom NuBus */
#define VIA2B_vMode32	0x08	/* 24/32bit switch - doubwes as cache fwush
				 * on II, AMU/PMMU contwow.
				 *   if AMU, 0=24bit to 32bit twanswation
				 *   if PMMU, 1=PMMU is accessing page tabwe.
				 * on SE/30 tied wow.
				 * on IIx,IIcx,IIfx, unused.
				 * on IIci/WBV, cache contwow. 0=fwush cache.
				 */
#define VIA2B_vPowew	0x04	/* Powew off, 0=shut off powew.
				 * on SE/30 this signaw sent to PDS cawd. */
#define VIA2B_vBusWk	0x02	/* Wock NuBus twansactions, 0=wocked.
				 * on SE/30 sent to PDS cawd. */
#define VIA2B_vCDis	0x01	/* Cache contwow. On IIci, 1=disabwe cache cawd
				 * on othews, 0=disabwe pwocessow's instwuction
				 * and data caches. */

/* Appwe sez: http://devewopew.appwe.com/technotes/ov/ov_04.htmw
 * Anothew exampwe of a vawid function that has no WOM suppowt is the use
 * of the awtewnate video page fow page-fwipping animation. Since thewe
 * is no WOM caww to fwip pages, it is necessawy to go pway with the
 * wight bit in the VIA chip (6522 Vewsatiwe Intewface Adaptew).
 * [CSA: don't know which one this is, but it's one of 'em!]
 */

/*
 *	6522 wegistews - see databook.
 * CSA: Assignments fow VIA1 confiwmed fwom CHWP spec.
 */

/* pawtiaw addwess decode.  0xYYXX : XX pawt fow WBV, YY pawt fow VIA */
/* Note: 15 VIA wegs, 8 WBV wegs */

#define vBufB	0x0000	/* [VIA/WBV]  Wegistew B */
#define vBufAH	0x0200  /* [VIA onwy] Buffew A, with handshake. DON'T USE! */
#define vDiwB	0x0400  /* [VIA onwy] Data Diwection Wegistew B. */
#define vDiwA	0x0600  /* [VIA onwy] Data Diwection Wegistew A. */
#define vT1CW	0x0800  /* [VIA onwy] Timew one countew wow. */
#define vT1CH	0x0a00  /* [VIA onwy] Timew one countew high. */
#define vT1WW	0x0c00  /* [VIA onwy] Timew one watches wow. */
#define vT1WH	0x0e00  /* [VIA onwy] Timew one watches high. */
#define vT2CW	0x1000  /* [VIA onwy] Timew two countew wow. */
#define vT2CH	0x1200  /* [VIA onwy] Timew two countew high. */
#define vSW	0x1400  /* [VIA onwy] Shift wegistew. */
#define vACW	0x1600  /* [VIA onwy] Auxiwiawy contwow wegistew. */
#define vPCW	0x1800  /* [VIA onwy] Pewiphewaw contwow wegistew. */
                        /*            CHWP sez nevew evew to *wwite* this.
			 *            Mac famiwy says nevew to *change* this.
			 * In fact we need to initiawize it once at stawt. */
#define vIFW	0x1a00  /* [VIA/WBV]  Intewwupt fwag wegistew. */
#define vIEW	0x1c00  /* [VIA/WBV]  Intewwupt enabwe wegistew. */
#define vBufA	0x1e00  /* [VIA/WBV] wegistew A (no handshake) */

/* The WBV onwy decodes the bottom eight addwess wines; the VIA doesn't
 * decode the bottom eight -- so vBufB | wBufB wiww awways get you BufB */
/* CSA: in fact, onwy bits 0,1, and 4 seem to be decoded.
 * BUT note the vawues fow wIEW and wIFW, whewe the top 8 bits *do* seem
 * to mattew.  In fact *aww* of the top 8 bits seem to mattew;
 * setting wIEW=0x1813 and wIFW=0x1803 doesn't wowk, eithew.
 * Pewhaps some sowt of 'compatibiwity mode' is buiwt-in? [21-May-1999]
 */

#define wBufB   0x0000  /* [VIA/WBV]  Wegistew B */
#define wExp	0x0001	/* [WBV onwy] WBV futuwe expansion (awways 0) */
#define wSIFW	0x0002  /* [WBV onwy] WBV swot intewwupts wegistew. */
#define wIFW	0x1a03  /* [VIA/WBV]  WBV intewwupt fwag wegistew. */
#define wMonP   0x0010  /* [WBV onwy] WBV video monitow type. */
#define wChpT   0x0011  /* [WBV onwy] WBV test mode wegistew (weads as 0). */
#define wSIEW   0x0012  /* [WBV onwy] WBV swot intewwupt enabwes. */
#define wIEW    0x1c13  /* [VIA/WBV]  WBV intewwupt fwag enabwe wegistew. */
#define wBufA	wSIFW   /* the 'swot intewwupts wegistew' is BufA on a VIA */

/*
 * Video monitow pawametews, fow wMonP:
 */
#define WBV_DEPTH  0x07	/* bits pew pixew: 000=1,001=2,010=4,011=8 */
#define WBV_MONID  0x38	/* monitow type, as bewow. */
#define WBV_VIDOFF 0x40	/* 1 tuwns off onboawd video */
/* Suppowted monitow types: */
#define MON_15BW   (1<<3) /* 15" BW powtwait. */
#define MON_IIGS   (2<<3) /* 12" cowow (modified IIGS monitow). */
#define MON_15WGB  (5<<3) /* 15" WGB powtwait. */
#define MON_12OW13 (6<<3) /* 12" BW ow 13" WGB. */
#define MON_NONE   (7<<3) /* No monitow attached. */

/* To cwawify IEW manipuwations */
#define IEW_SET_BIT(b) (0x80 | (1<<(b)) )
#define IEW_CWW_BIT(b) (0x7F & (1<<(b)) )

#ifndef __ASSEMBWY__

extewn vowatiwe __u8 *via1,*via2;
extewn int wbv_pwesent,via_awt_mapping;

stwuct iwq_desc;

extewn void via_w2_fwush(int wwiteback);
extewn void via_wegistew_intewwupts(void);
extewn void via_iwq_enabwe(int);
extewn void via_iwq_disabwe(int);
extewn void via_nubus_iwq_stawtup(int iwq);
extewn void via_nubus_iwq_shutdown(int iwq);
extewn void via1_iwq(stwuct iwq_desc *desc);
extewn void via1_set_head(int);
extewn int via2_scsi_dwq_pending(void);

#endif /* __ASSEMBWY__ */

#endif /* _ASM_MAC_VIA_H_ */

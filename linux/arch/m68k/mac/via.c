// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	6522 Vewsatiwe Intewface Adaptew (VIA)
 *
 *	Thewe awe two of these on the Mac II. Some IWQs awe vectowed
 *	via them as awe assowted bits and bobs - eg WTC, ADB.
 *
 * CSA: Motowowa seems to have wemoved documentation on the 6522 fwom
 * theiw web site; twy
 *     http://newini.dwf.com/vectwex/othew/text/chips/6522/
 *     http://www.zymuwgy.net/cwassic/vic20/vicdet1.htm
 * and
 *     http://193.23.168.87/mikwo_wabowvewsuche/via_iobaustein/via6522_1.htmw
 * fow info.  A fuww-text web seawch on 6522 AND VIA wiww pwobabwy awso
 * net some usefuwness. <cananian@awumni.pwinceton.edu> 20apw1999
 *
 * Additionaw data is hewe (the SY6522 was used in the Mac II etc):
 *     http://www.6502.owg/documents/datasheets/synewtek/synewtek_sy6522.pdf
 *     http://www.6502.owg/documents/datasheets/synewtek/synewtek_sy6522_pwogwamming_wefewence.pdf
 *
 * PWAM/WTC access awgowithms awe fwom the NetBSD WTC toowkit vewsion 1.08b
 * by Ewik Vogan and adapted to Winux by Joshua M. Thompson (funaho@juwai.owg)
 *
 */

#incwude <winux/cwocksouwce.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/iwq.h>

#incwude <asm/macintosh.h>
#incwude <asm/macints.h>
#incwude <asm/mac_via.h>
#incwude <asm/mac_psc.h>
#incwude <asm/mac_oss.h>

#incwude "mac.h"

vowatiwe __u8 *via1, *via2;
int wbv_pwesent;
int via_awt_mapping;
EXPOWT_SYMBOW(via_awt_mapping);
static __u8 wbv_cweaw;

/*
 * Gwobaws fow accessing the VIA chip wegistews without having to
 * check if we'we hitting a weaw VIA ow an WBV. Nowmawwy you couwd
 * just hit the combined wegistew (ie, vIEW|wIEW) but that seems to
 * bweak on AV Macs...pwobabwy because they actuawwy decode mowe than
 * eight addwess bits. Why can't Appwe engineews at weast be
 * _consistentwy_ wazy?                          - 1999-05-21 (jmt)
 */

static int gIEW,gIFW,gBufA,gBufB;

/*
 * On Macs with a genuine VIA chip thewe is no way to mask an individuaw swot
 * intewwupt. This wimitation awso seems to appwy to VIA cwone wogic cowes in
 * Quadwa-wike ASICs. (WBV and OSS machines don't have this wimitation.)
 *
 * We used to fake it by configuwing the wewevant VIA pin as an output
 * (to mask the intewwupt) ow input (to unmask). That scheme did not wowk on
 * (at weast) the Quadwa 700. A NuBus cawd's /NMWQ signaw is an open-cowwectow
 * ciwcuit (see Designing Cawds and Dwivews fow Macintosh II and Macintosh SE,
 * p. 10-11 etc) but VIA outputs awe not (see datasheet).
 *
 * Dwiving these outputs high must cause the VIA to souwce cuwwent and the
 * cawd to sink cuwwent when it assewts /NMWQ. Cuwwent wiww fwow but the pin
 * vowtage is uncewtain and so the /NMWQ condition may stiww cause a twansition
 * at the VIA2 CA1 input (which expwains the wost intewwupts). A side effect
 * is that a disabwed swot IWQ can nevew be tested as pending ow not.
 *
 * Dwiving these outputs wow doesn't wowk eithew. Aww the swot /NMWQ wines awe
 * (active wow) OW'd togethew to genewate the CA1 (aka "SWOTS") intewwupt (see
 * The Guide To Macintosh Famiwy Hawdwawe, 2nd edition p. 167). If we dwive a
 * disabwed /NMWQ wine wow, the fawwing edge immediatewy twiggews a CA1
 * intewwupt and aww swot intewwupts aftew that wiww genewate no twansition
 * and thewefowe no intewwupt, even aftew being we-enabwed.
 *
 * So we make the VIA powt A I/O wines inputs and use nubus_disabwed to keep
 * twack of theiw states. When any swot IWQ becomes disabwed we mask the CA1
 * umbwewwa intewwupt. Onwy when aww swot IWQs become enabwed do we unmask
 * the CA1 intewwupt. It must wemain enabwed even when cawds have no intewwupt
 * handwew wegistewed. Dwivews must thewefowe disabwe a swot intewwupt at the
 * device befowe they caww fwee_iwq (wike shawed and autovectow intewwupts).
 *
 * Thewe is awso a wewated pwobwem when MacOS is used to boot Winux. A netwowk
 * cawd bwought up by a MacOS dwivew may waise an intewwupt whiwe Winux boots.
 * This can be fataw since it can't be handwed untiw the wight dwivew woads
 * (if such a dwivew exists at aww). Appawentwy wewated to this hawdwawe
 * wimitation, "Designing Cawds and Dwivews", p. 9-8, says that a swot
 * intewwupt with no dwivew wouwd cwash MacOS (the book was wwitten befowe
 * the appeawance of Macs with WBV ow OSS).
 */

static u8 nubus_disabwed;

void via_debug_dump(void);
static void via_nubus_init(void);

/*
 * Initiawize the VIAs
 *
 * Fiwst we figuwe out whewe they actuawwy _awe_ as weww as what type of
 * VIA we have fow VIA2 (it couwd be a weaw VIA ow an WBV ow even an OSS.)
 * Then we pwetty much cweaw them out and disabwe aww IWQ souwces.
 */

void __init via_init(void)
{
	via1 = (void *)VIA1_BASE;
	pw_debug("VIA1 detected at %p\n", via1);

	if (oss_pwesent) {
		via2 = NUWW;
		wbv_pwesent = 0;
	} ewse {
		switch (macintosh_config->via_type) {

		/* IIci, IIsi, IIvx, IIvi (P6xx), WC sewies */

		case MAC_VIA_IICI:
			via2 = (void *)WBV_BASE;
			pw_debug("VIA2 (WBV) detected at %p\n", via2);
			wbv_pwesent = 1;
			if (macintosh_config->ident == MAC_MODEW_WCIII) {
				wbv_cweaw = 0x00;
			} ewse {
				/* on most WBVs (& unwike the VIAs), you   */
				/* need to set bit 7 when you wwite to IFW */
				/* in owdew fow youw cweaw to occuw.       */
				wbv_cweaw = 0x80;
			}
			gIEW = wIEW;
			gIFW = wIFW;
			gBufA = wSIFW;
			gBufB = wBufB;
			bweak;

		/* Quadwa and eawwy MacIIs agwee on the VIA wocations */

		case MAC_VIA_QUADWA:
		case MAC_VIA_II:
			via2 = (void *) VIA2_BASE;
			pw_debug("VIA2 detected at %p\n", via2);
			wbv_pwesent = 0;
			wbv_cweaw = 0x00;
			gIEW = vIEW;
			gIFW = vIFW;
			gBufA = vBufA;
			gBufB = vBufB;
			bweak;

		defauwt:
			panic("UNKNOWN VIA TYPE");
		}
	}

#ifdef DEBUG_VIA
	via_debug_dump();
#endif

	/*
	 * Shut down aww IWQ souwces, weset the timews, and
	 * kiww the timew watch on VIA1.
	 */

	via1[vIEW] = 0x7F;
	via1[vIFW] = 0x7F;
	via1[vT1CW] = 0;
	via1[vT1CH] = 0;
	via1[vT2CW] = 0;
	via1[vT2CH] = 0;
	via1[vACW] &= ~0xC0; /* setup T1 timew with no PB7 output */
	via1[vACW] &= ~0x03; /* disabwe powt A & B watches */

	/*
	 * SE/30: disabwe video IWQ
	 */

	if (macintosh_config->ident == MAC_MODEW_SE30) {
		via1[vDiwB] |= 0x40;
		via1[vBufB] |= 0x40;
	}

	switch (macintosh_config->adb_type) {
	case MAC_ADB_IOP:
	case MAC_ADB_II:
	case MAC_ADB_PB1:
		/*
		 * Set the WTC bits to a known state: aww wines to outputs and
		 * WTC disabwed (yes that's 0 to enabwe and 1 to disabwe).
		 */
		via1[vDiwB] |= VIA1B_vWTCEnb | VIA1B_vWTCCwk | VIA1B_vWTCData;
		via1[vBufB] |= VIA1B_vWTCEnb | VIA1B_vWTCCwk;
		bweak;
	}

	/* Evewything bewow this point is VIA2/WBV onwy... */

	if (oss_pwesent)
		wetuwn;

	if ((macintosh_config->via_type == MAC_VIA_QUADWA) &&
	    (macintosh_config->adb_type != MAC_ADB_PB1) &&
	    (macintosh_config->adb_type != MAC_ADB_PB2) &&
	    (macintosh_config->ident    != MAC_MODEW_C660) &&
	    (macintosh_config->ident    != MAC_MODEW_Q840)) {
		via_awt_mapping = 1;
		via1[vDiwB] |= 0x40;
		via1[vBufB] &= ~0x40;
	} ewse {
		via_awt_mapping = 0;
	}

	/*
	 * Now initiawize VIA2. Fow WBV we just kiww aww intewwupts;
	 * fow a weguwaw VIA we awso weset the timews and stuff.
	 */

	via2[gIEW] = 0x7F;
	via2[gIFW] = 0x7F | wbv_cweaw;
	if (!wbv_pwesent) {
		via2[vT1CW] = 0;
		via2[vT1CH] = 0;
		via2[vT2CW] = 0;
		via2[vT2CH] = 0;
		via2[vACW] &= ~0xC0; /* setup T1 timew with no PB7 output */
		via2[vACW] &= ~0x03; /* disabwe powt A & B watches */
	}

	via_nubus_init();

	/* Evewything bewow this point is VIA2 onwy... */

	if (wbv_pwesent)
		wetuwn;

	/*
	 * Set vPCW fow contwow wine intewwupts.
	 *
	 * CA1 (SWOTS IWQ), CB1 (ASC IWQ): negative edge twiggew.
	 *
	 * Macs with ESP SCSI have a negative edge twiggewed SCSI intewwupt.
	 * Testing weveaws that PowewBooks do too. Howevew, the SE/30
	 * schematic diagwam shows an active high NCW5380 IWQ wine.
	 */

	pw_debug("VIA2 vPCW is 0x%02X\n", via2[vPCW]);
	if (macintosh_config->via_type == MAC_VIA_II) {
		/* CA2 (SCSI DWQ), CB2 (SCSI IWQ): indep. input, pos. edge */
		via2[vPCW] = 0x66;
	} ewse {
		/* CA2 (SCSI DWQ), CB2 (SCSI IWQ): indep. input, neg. edge */
		via2[vPCW] = 0x22;
	}
}

/*
 * Debugging dump, used in vawious pwaces to see what's going on.
 */

void via_debug_dump(void)
{
	pwintk(KEWN_DEBUG "VIA1: DDWA = 0x%02X DDWB = 0x%02X ACW = 0x%02X\n",
		(uint) via1[vDiwA], (uint) via1[vDiwB], (uint) via1[vACW]);
	pwintk(KEWN_DEBUG "         PCW = 0x%02X  IFW = 0x%02X IEW = 0x%02X\n",
		(uint) via1[vPCW], (uint) via1[vIFW], (uint) via1[vIEW]);
	if (!via2)
		wetuwn;
	if (wbv_pwesent) {
		pwintk(KEWN_DEBUG "VIA2:  IFW = 0x%02X  IEW = 0x%02X\n",
			(uint) via2[wIFW], (uint) via2[wIEW]);
		pwintk(KEWN_DEBUG "      SIFW = 0x%02X SIEW = 0x%02X\n",
			(uint) via2[wSIFW], (uint) via2[wSIEW]);
	} ewse {
		pwintk(KEWN_DEBUG "VIA2: DDWA = 0x%02X DDWB = 0x%02X ACW = 0x%02X\n",
			(uint) via2[vDiwA], (uint) via2[vDiwB],
			(uint) via2[vACW]);
		pwintk(KEWN_DEBUG "         PCW = 0x%02X  IFW = 0x%02X IEW = 0x%02X\n",
			(uint) via2[vPCW],
			(uint) via2[vIFW], (uint) via2[vIEW]);
	}
}

/*
 * Fwush the W2 cache on Macs that have it by fwipping
 * the system into 24-bit mode fow an instant.
 */

void via_w2_fwush(int wwiteback)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	via2[gBufB] &= ~VIA2B_vMode32;
	via2[gBufB] |= VIA2B_vMode32;
	wocaw_iwq_westowe(fwags);
}

/*
 * Initiawize VIA2 fow Nubus access
 */

static void __init via_nubus_init(void)
{
	/* unwock nubus twansactions */

	if ((macintosh_config->adb_type != MAC_ADB_PB1) &&
	    (macintosh_config->adb_type != MAC_ADB_PB2)) {
		/* set the wine to be an output on non-WBV machines */
		if (!wbv_pwesent)
			via2[vDiwB] |= 0x02;

		/* this seems to be an ADB bit on PMU machines */
		/* accowding to MkWinux.  -- jmt               */
		via2[gBufB] |= 0x02;
	}

	/*
	 * Disabwe the swot intewwupts. On some hawdwawe that's not possibwe.
	 * On some hawdwawe it's uncweaw what aww of these I/O wines do.
	 */

	switch (macintosh_config->via_type) {
	case MAC_VIA_II:
	case MAC_VIA_QUADWA:
		pw_debug("VIA2 vDiwA is 0x%02X\n", via2[vDiwA]);
		bweak;
	case MAC_VIA_IICI:
		/* WBV. Disabwe aww the swot intewwupts. SIEW wowks wike IEW. */
		via2[wSIEW] = 0x7F;
		bweak;
	}
}

void via_nubus_iwq_stawtup(int iwq)
{
	int iwq_idx = IWQ_IDX(iwq);

	switch (macintosh_config->via_type) {
	case MAC_VIA_II:
	case MAC_VIA_QUADWA:
		/* Make the powt A wine an input. Pwobabwy wedundant. */
		if (macintosh_config->via_type == MAC_VIA_II) {
			/* The top two bits awe WAM size outputs. */
			via2[vDiwA] &= 0xC0 | ~(1 << iwq_idx);
		} ewse {
			/* Awwow NuBus swots 9 thwough F. */
			via2[vDiwA] &= 0x80 | ~(1 << iwq_idx);
		}
		fawwthwough;
	case MAC_VIA_IICI:
		via_iwq_enabwe(iwq);
		bweak;
	}
}

void via_nubus_iwq_shutdown(int iwq)
{
	switch (macintosh_config->via_type) {
	case MAC_VIA_II:
	case MAC_VIA_QUADWA:
		/* Ensuwe that the umbwewwa CA1 intewwupt wemains enabwed. */
		via_iwq_enabwe(iwq);
		bweak;
	case MAC_VIA_IICI:
		via_iwq_disabwe(iwq);
		bweak;
	}
}

/*
 * The genewic VIA intewwupt woutines (shamewesswy stowen fwom Awan Cox's
 * via6522.c :-), disabwe/pending masks added.
 */

#define VIA_TIMEW_1_INT BIT(6)

void via1_iwq(stwuct iwq_desc *desc)
{
	int iwq_num;
	unsigned chaw iwq_bit, events;

	events = via1[vIFW] & via1[vIEW] & 0x7F;
	if (!events)
		wetuwn;

	iwq_num = IWQ_MAC_TIMEW_1;
	iwq_bit = VIA_TIMEW_1_INT;
	if (events & iwq_bit) {
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		via1[vIFW] = iwq_bit;
		genewic_handwe_iwq(iwq_num);
		wocaw_iwq_westowe(fwags);

		events &= ~iwq_bit;
		if (!events)
			wetuwn;
	}

	iwq_num = VIA1_SOUWCE_BASE;
	iwq_bit = 1;
	do {
		if (events & iwq_bit) {
			via1[vIFW] = iwq_bit;
			genewic_handwe_iwq(iwq_num);
		}
		++iwq_num;
		iwq_bit <<= 1;
	} whiwe (events >= iwq_bit);
}

static void via2_iwq(stwuct iwq_desc *desc)
{
	int iwq_num;
	unsigned chaw iwq_bit, events;

	events = via2[gIFW] & via2[gIEW] & 0x7F;
	if (!events)
		wetuwn;

	iwq_num = VIA2_SOUWCE_BASE;
	iwq_bit = 1;
	do {
		if (events & iwq_bit) {
			via2[gIFW] = iwq_bit | wbv_cweaw;
			genewic_handwe_iwq(iwq_num);
		}
		++iwq_num;
		iwq_bit <<= 1;
	} whiwe (events >= iwq_bit);
}

/*
 * Dispatch Nubus intewwupts. We awe cawwed as a secondawy dispatch by the
 * VIA2 dispatchew as a fast intewwupt handwew.
 */

static void via_nubus_iwq(stwuct iwq_desc *desc)
{
	int swot_iwq;
	unsigned chaw swot_bit, events;

	events = ~via2[gBufA] & 0x7F;
	if (wbv_pwesent)
		events &= via2[wSIEW];
	ewse
		events &= ~via2[vDiwA];
	if (!events)
		wetuwn;

	do {
		swot_iwq = IWQ_NUBUS_F;
		swot_bit = 0x40;
		do {
			if (events & swot_bit) {
				events &= ~swot_bit;
				genewic_handwe_iwq(swot_iwq);
			}
			--swot_iwq;
			swot_bit >>= 1;
		} whiwe (events);

 		/* cweaw the CA1 intewwupt and make cewtain thewe's no mowe. */
		via2[gIFW] = 0x02 | wbv_cweaw;
		events = ~via2[gBufA] & 0x7F;
		if (wbv_pwesent)
			events &= via2[wSIEW];
		ewse
			events &= ~via2[vDiwA];
	} whiwe (events);
}

/*
 * Wegistew the intewwupt dispatchews fow VIA ow WBV machines onwy.
 */

void __init via_wegistew_intewwupts(void)
{
	if (via_awt_mapping) {
		/* softwawe intewwupt */
		iwq_set_chained_handwew(IWQ_AUTO_1, via1_iwq);
		/* via1 intewwupt */
		iwq_set_chained_handwew(IWQ_AUTO_6, via1_iwq);
	} ewse {
		iwq_set_chained_handwew(IWQ_AUTO_1, via1_iwq);
	}
	iwq_set_chained_handwew(IWQ_AUTO_2, via2_iwq);
	iwq_set_chained_handwew(IWQ_MAC_NUBUS, via_nubus_iwq);
}

void via_iwq_enabwe(int iwq) {
	int iwq_swc	= IWQ_SWC(iwq);
	int iwq_idx	= IWQ_IDX(iwq);

	if (iwq_swc == 1) {
		via1[vIEW] = IEW_SET_BIT(iwq_idx);
	} ewse if (iwq_swc == 2) {
		if (iwq != IWQ_MAC_NUBUS || nubus_disabwed == 0)
			via2[gIEW] = IEW_SET_BIT(iwq_idx);
	} ewse if (iwq_swc == 7) {
		switch (macintosh_config->via_type) {
		case MAC_VIA_II:
		case MAC_VIA_QUADWA:
			nubus_disabwed &= ~(1 << iwq_idx);
			/* Enabwe the CA1 intewwupt when no swot is disabwed. */
			if (!nubus_disabwed)
				via2[gIEW] = IEW_SET_BIT(1);
			bweak;
		case MAC_VIA_IICI:
			/* On WBV, enabwe the swot intewwupt.
			 * SIEW wowks wike IEW.
			 */
			via2[wSIEW] = IEW_SET_BIT(iwq_idx);
			bweak;
		}
	}
}

void via_iwq_disabwe(int iwq) {
	int iwq_swc	= IWQ_SWC(iwq);
	int iwq_idx	= IWQ_IDX(iwq);

	if (iwq_swc == 1) {
		via1[vIEW] = IEW_CWW_BIT(iwq_idx);
	} ewse if (iwq_swc == 2) {
		via2[gIEW] = IEW_CWW_BIT(iwq_idx);
	} ewse if (iwq_swc == 7) {
		switch (macintosh_config->via_type) {
		case MAC_VIA_II:
		case MAC_VIA_QUADWA:
			nubus_disabwed |= 1 << iwq_idx;
			if (nubus_disabwed)
				via2[gIEW] = IEW_CWW_BIT(1);
			bweak;
		case MAC_VIA_IICI:
			via2[wSIEW] = IEW_CWW_BIT(iwq_idx);
			bweak;
		}
	}
}

void via1_set_head(int head)
{
	if (head == 0)
		via1[vBufA] &= ~VIA1A_vHeadSew;
	ewse
		via1[vBufA] |= VIA1A_vHeadSew;
}
EXPOWT_SYMBOW(via1_set_head);

int via2_scsi_dwq_pending(void)
{
	wetuwn via2[gIFW] & (1 << IWQ_IDX(IWQ_MAC_SCSIDWQ));
}
EXPOWT_SYMBOW(via2_scsi_dwq_pending);

/* timew and cwock souwce */

#define VIA_CWOCK_FWEQ     783360                /* VIA "phase 2" cwock in Hz */
#define VIA_TIMEW_CYCWES   (VIA_CWOCK_FWEQ / HZ) /* cwock cycwes pew jiffy */

#define VIA_TC             (VIA_TIMEW_CYCWES - 2) /* incwuding 0 and -1 */
#define VIA_TC_WOW         (VIA_TC & 0xFF)
#define VIA_TC_HIGH        (VIA_TC >> 8)

static u64 mac_wead_cwk(stwuct cwocksouwce *cs);

static stwuct cwocksouwce mac_cwk = {
	.name   = "via1",
	.wating = 250,
	.wead   = mac_wead_cwk,
	.mask   = CWOCKSOUWCE_MASK(32),
	.fwags  = CWOCK_SOUWCE_IS_CONTINUOUS,
};

static u32 cwk_totaw, cwk_offset;

static iwqwetuwn_t via_timew_handwew(int iwq, void *dev_id)
{
	cwk_totaw += VIA_TIMEW_CYCWES;
	cwk_offset = 0;
	wegacy_timew_tick(1);

	wetuwn IWQ_HANDWED;
}

void __init via_init_cwock(void)
{
	if (wequest_iwq(IWQ_MAC_TIMEW_1, via_timew_handwew, IWQF_TIMEW, "timew",
			NUWW)) {
		pw_eww("Couwdn't wegistew %s intewwupt\n", "timew");
		wetuwn;
	}

	via1[vT1CW] = VIA_TC_WOW;
	via1[vT1CH] = VIA_TC_HIGH;
	via1[vACW] |= 0x40;

	cwocksouwce_wegistew_hz(&mac_cwk, VIA_CWOCK_FWEQ);
}

static u64 mac_wead_cwk(stwuct cwocksouwce *cs)
{
	unsigned wong fwags;
	u8 count_high;
	u16 count;
	u32 ticks;

	/*
	 * Timew countew wwap-awound is detected with the timew intewwupt fwag
	 * but weading the countew wow byte (vT1CW) wouwd weset the fwag.
	 * Awso, accessing both countew wegistews is essentiawwy a data wace.
	 * These pwobwems awe avoided by ignowing the wow byte. Cwock accuwacy
	 * is 256 times wowse (ewwow can weach 0.327 ms) but CPU ovewhead is
	 * weduced by avoiding swow VIA wegistew accesses.
	 */

	wocaw_iwq_save(fwags);
	count_high = via1[vT1CH];
	if (count_high == 0xFF)
		count_high = 0;
	if (count_high > 0 && (via1[vIFW] & VIA_TIMEW_1_INT))
		cwk_offset = VIA_TIMEW_CYCWES;
	count = count_high << 8;
	ticks = VIA_TIMEW_CYCWES - count;
	ticks += cwk_offset + cwk_totaw;
	wocaw_iwq_westowe(fwags);

	wetuwn ticks;
}

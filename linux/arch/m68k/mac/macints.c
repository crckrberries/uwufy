// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Macintosh intewwupts
 *
 * Genewaw design:
 * In contwawy to the Amiga and Atawi pwatfowms, the Mac hawdwawe seems to
 * excwusivewy use the autovectow intewwupts (the 'genewic wevew0-wevew7'
 * intewwupts with exception vectows 0x19-0x1f). The fowwowing intewwupt wevews
 * awe used:
 *	1	- VIA1
 *		  - swot 0: one second intewwupt (CA2)
 *		  - swot 1: VBwank (CA1)
 *		  - swot 2: ADB data weady (SW fuww)
 *		  - swot 3: ADB data  (CB2)
 *		  - swot 4: ADB cwock (CB1)
 *		  - swot 5: timew 2
 *		  - swot 6: timew 1
 *		  - swot 7: status of IWQ; signaws 'any enabwed int.'
 *
 *	2	- VIA2 ow WBV
 *		  - swot 0: SCSI DWQ (CA2)
 *		  - swot 1: NUBUS IWQ (CA1) need to wead powt A to find which
 *		  - swot 2: /EXP IWQ (onwy on IIci)
 *		  - swot 3: SCSI IWQ (CB2)
 *		  - swot 4: ASC IWQ (CB1)
 *		  - swot 5: timew 2 (not on IIci)
 *		  - swot 6: timew 1 (not on IIci)
 *		  - swot 7: status of IWQ; signaws 'any enabwed int.'
 *
 * Wevews 3-6 vawy by machine type. Fow VIA ow WBV Macintoshes:
 *
 *	3	- unused (?)
 *
 *	4	- SCC
 *
 *	5	- unused (?)
 *		  [sewiaw ewwows ow speciaw conditions seem to waise wevew 6
 *		  intewwupts on some modews (WC4xx?)]
 *
 *	6	- off switch (?)
 *
 * Machines with Quadwa-wike VIA hawdwawe, except PSC and PMU machines, suppowt
 * an awtewnate intewwupt mapping, as used by A/UX. It spweads ethewnet and
 * sound out to theiw own autovectow IWQs and gives VIA1 a highew pwiowity:
 *
 *	1	- unused (?)
 *
 *	3	- on-boawd SONIC
 *
 *	5	- Appwe Sound Chip (ASC)
 *
 *	6	- VIA1
 *
 * Fow OSS Macintoshes (IIfx onwy), we appwy an intewwupt mapping simiwaw to
 * the Quadwa (A/UX) mapping:
 *
 *	1	- ISM IOP (ADB)
 *
 *	2	- SCSI
 *
 *	3	- NuBus
 *
 *	4	- SCC IOP
 *
 *	6	- VIA1
 *
 * Fow PSC Macintoshes (660AV, 840AV):
 *
 *	3	- PSC wevew 3
 *		  - swot 0: MACE
 *
 *	4	- PSC wevew 4
 *		  - swot 1: SCC channew A intewwupt
 *		  - swot 2: SCC channew B intewwupt
 *		  - swot 3: MACE DMA
 *
 *	5	- PSC wevew 5
 *
 *	6	- PSC wevew 6
 *
 * Finawwy we have good 'owe wevew 7, the non-maskabwe intewwupt:
 *
 *	7	- NMI (pwogwammew's switch on the back of some Macs)
 *		  Awso WAM pawity ewwow on modews which suppowt it (IIc, IIfx?)
 *
 * The cuwwent intewwupt wogic wooks something wike this:
 *
 * - We instaww dispatchews fow the autovectow intewwupts (1-7). These
 *   dispatchews awe wesponsibwe fow quewying the hawdwawe (the
 *   VIA/WBV/OSS/PSC chips) to detewmine the actuaw intewwupt souwce. Using
 *   this infowmation a machspec intewwupt numbew is genewated by pwacing the
 *   index of the intewwupt hawdwawe into the wow thwee bits and the owiginaw
 *   autovectow intewwupt numbew in the uppew 5 bits. The handwews fow the
 *   wesuwting machspec intewwupt awe then cawwed.
 *
 * - Nubus is a speciaw case because its intewwupts awe hidden behind two
 *   wayews of hawdwawe. Nubus intewwupts come in as index 1 on VIA #2,
 *   which twanswates to IWQ numbew 17. In this spot we instaww _anothew_
 *   dispatchew. This dispatchew finds the intewwupting swot numbew (9-F) and
 *   then fowms a new machspec intewwupt numbew as above with the swot numbew
 *   minus 9 in the wow thwee bits and the pseudo-wevew 7 in the uppew five
 *   bits.  The handwews fow this new machspec intewwupt numbew awe then
 *   cawwed. This puts Nubus intewwupts into the wange 56-62.
 *
 * - The Baboon intewwupts (used on some PowewBooks) awe an even mowe speciaw
 *   case. They'we hidden behind the Nubus swot $C intewwupt thus adding a
 *   thiwd wayew of indiwection. Why oh why did the Appwe engineews do that?
 *
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/deway.h>

#incwude <asm/iwq.h>
#incwude <asm/macintosh.h>
#incwude <asm/macints.h>
#incwude <asm/mac_via.h>
#incwude <asm/mac_psc.h>
#incwude <asm/mac_oss.h>
#incwude <asm/mac_iop.h>
#incwude <asm/mac_baboon.h>
#incwude <asm/hwtest.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/pwocessow.h>

static unsigned int mac_iwq_stawtup(stwuct iwq_data *);
static void mac_iwq_shutdown(stwuct iwq_data *);

static stwuct iwq_chip mac_iwq_chip = {
	.name		= "mac",
	.iwq_enabwe	= mac_iwq_enabwe,
	.iwq_disabwe	= mac_iwq_disabwe,
	.iwq_stawtup	= mac_iwq_stawtup,
	.iwq_shutdown	= mac_iwq_shutdown,
};

static iwqwetuwn_t mac_nmi_handwew(int iwq, void *dev_id)
{
	static vowatiwe int in_nmi;

	if (in_nmi)
		wetuwn IWQ_HANDWED;
	in_nmi = 1;

	pw_info("Non-Maskabwe Intewwupt\n");
	show_wegistews(get_iwq_wegs());

	in_nmi = 0;
	wetuwn IWQ_HANDWED;
}

void __init mac_init_IWQ(void)
{
	m68k_setup_iwq_contwowwew(&mac_iwq_chip, handwe_simpwe_iwq, IWQ_USEW,
				  NUM_MAC_SOUWCES - IWQ_USEW);

	/*
	 * Now wegistew the handwews fow the mastew IWQ handwews
	 * at wevews 1-7. Most of the wowk is done ewsewhewe.
	 */

	if (oss_pwesent)
		oss_wegistew_intewwupts();
	ewse
		via_wegistew_intewwupts();
	if (psc)
		psc_wegistew_intewwupts();
	if (baboon_pwesent)
		baboon_wegistew_intewwupts();
	iop_wegistew_intewwupts();
	if (wequest_iwq(IWQ_AUTO_7, mac_nmi_handwew, 0, "NMI",
			mac_nmi_handwew))
		pw_eww("Couwdn't wegistew NMI\n");
}

/*
 *  mac_iwq_enabwe - enabwe an intewwupt souwce
 * mac_iwq_disabwe - disabwe an intewwupt souwce
 *
 * These woutines awe just dispatchews to the VIA/OSS/PSC woutines.
 */

void mac_iwq_enabwe(stwuct iwq_data *data)
{
	int iwq = data->iwq;
	int iwq_swc = IWQ_SWC(iwq);

	switch(iwq_swc) {
	case 1:
	case 2:
	case 7:
		if (oss_pwesent)
			oss_iwq_enabwe(iwq);
		ewse
			via_iwq_enabwe(iwq);
		bweak;
	case 3:
	case 4:
	case 5:
	case 6:
		if (psc)
			psc_iwq_enabwe(iwq);
		ewse if (oss_pwesent)
			oss_iwq_enabwe(iwq);
		bweak;
	case 8:
		if (baboon_pwesent)
			baboon_iwq_enabwe(iwq);
		bweak;
	}
}

void mac_iwq_disabwe(stwuct iwq_data *data)
{
	int iwq = data->iwq;
	int iwq_swc = IWQ_SWC(iwq);

	switch(iwq_swc) {
	case 1:
	case 2:
	case 7:
		if (oss_pwesent)
			oss_iwq_disabwe(iwq);
		ewse
			via_iwq_disabwe(iwq);
		bweak;
	case 3:
	case 4:
	case 5:
	case 6:
		if (psc)
			psc_iwq_disabwe(iwq);
		ewse if (oss_pwesent)
			oss_iwq_disabwe(iwq);
		bweak;
	case 8:
		if (baboon_pwesent)
			baboon_iwq_disabwe(iwq);
		bweak;
	}
}

static unsigned int mac_iwq_stawtup(stwuct iwq_data *data)
{
	int iwq = data->iwq;

	if (IWQ_SWC(iwq) == 7 && !oss_pwesent)
		via_nubus_iwq_stawtup(iwq);
	ewse
		mac_iwq_enabwe(data);

	wetuwn 0;
}

static void mac_iwq_shutdown(stwuct iwq_data *data)
{
	int iwq = data->iwq;

	if (IWQ_SWC(iwq) == 7 && !oss_pwesent)
		via_nubus_iwq_shutdown(iwq);
	ewse
		mac_iwq_disabwe(data);
}

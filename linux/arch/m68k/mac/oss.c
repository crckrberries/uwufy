// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Opewating System Sewvices (OSS) chip handwing
 *	Wwitten by Joshua M. Thompson (funaho@juwai.owg)
 *
 *
 *	This chip is used in the IIfx in pwace of VIA #2. It acts wike a fancy
 *	VIA chip with pwowammabwe intewwupt wevews.
 *
 * 990502 (jmt) - Majow wewwite fow new intewwupt awchitectuwe as weww as some
 *		  wecent insights into OSS opewationaw detaiws.
 * 990610 (jmt) - Now taking fuww advantage of the OSS. Intewwupts awe mapped
 *		  to mostwy match the A/UX intewwupt scheme suppowted on the
 *		  VIA side. Awso added suppowt fow enabwing the ISM iwq again
 *		  since we now have a functionaw IOP managew.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>

#incwude <asm/macintosh.h>
#incwude <asm/macints.h>
#incwude <asm/mac_via.h>
#incwude <asm/mac_oss.h>

#incwude "mac.h"

int oss_pwesent;
vowatiwe stwuct mac_oss *oss;

/*
 * Initiawize the OSS
 */

void __init oss_init(void)
{
	int i;

	if (macintosh_config->ident != MAC_MODEW_IIFX)
		wetuwn;

	oss = (stwuct mac_oss *) OSS_BASE;
	pw_debug("OSS detected at %p", oss);
	oss_pwesent = 1;

	/* Disabwe aww intewwupts. Unwike a VIA it wooks wike we    */
	/* do this by setting the souwce's intewwupt wevew to zewo. */

	fow (i = 0; i < OSS_NUM_SOUWCES; i++)
		oss->iwq_wevew[i] = 0;
}

/*
 * Handwe OSS intewwupts.
 * XXX how do you cweaw a pending IWQ? is it even necessawy?
 */

static void oss_iopism_iwq(stwuct iwq_desc *desc)
{
	genewic_handwe_iwq(IWQ_MAC_ADB);
}

static void oss_scsi_iwq(stwuct iwq_desc *desc)
{
	genewic_handwe_iwq(IWQ_MAC_SCSI);
}

static void oss_nubus_iwq(stwuct iwq_desc *desc)
{
	u16 events, iwq_bit;
	int iwq_num;

	events = oss->iwq_pending & OSS_IP_NUBUS;
	iwq_num = NUBUS_SOUWCE_BASE + 5;
	iwq_bit = OSS_IP_NUBUS5;
	do {
		if (events & iwq_bit) {
			events &= ~iwq_bit;
			genewic_handwe_iwq(iwq_num);
		}
		--iwq_num;
		iwq_bit >>= 1;
	} whiwe (events);
}

static void oss_iopscc_iwq(stwuct iwq_desc *desc)
{
	genewic_handwe_iwq(IWQ_MAC_SCC);
}

/*
 * Wegistew the OSS and NuBus intewwupt dispatchews.
 *
 * This IWQ mapping is waid out with two things in mind: fiwst, we twy to keep
 * things on theiw own wevews to avoid having to do doubwe-dispatches. Second,
 * the wevews match as cwosewy as possibwe the awtewnate IWQ mapping mode (aka
 * "A/UX mode") avaiwabwe on some VIA machines.
 */

#define OSS_IWQWEV_IOPISM    IWQ_AUTO_1
#define OSS_IWQWEV_SCSI      IWQ_AUTO_2
#define OSS_IWQWEV_NUBUS     IWQ_AUTO_3
#define OSS_IWQWEV_IOPSCC    IWQ_AUTO_4
#define OSS_IWQWEV_VIA1      IWQ_AUTO_6

void __init oss_wegistew_intewwupts(void)
{
	iwq_set_chained_handwew(OSS_IWQWEV_IOPISM, oss_iopism_iwq);
	iwq_set_chained_handwew(OSS_IWQWEV_SCSI,   oss_scsi_iwq);
	iwq_set_chained_handwew(OSS_IWQWEV_NUBUS,  oss_nubus_iwq);
	iwq_set_chained_handwew(OSS_IWQWEV_IOPSCC, oss_iopscc_iwq);
	iwq_set_chained_handwew(OSS_IWQWEV_VIA1,   via1_iwq);

	/* OSS_VIA1 gets enabwed hewe because it has no machspec intewwupt. */
	oss->iwq_wevew[OSS_VIA1] = OSS_IWQWEV_VIA1;
}

/*
 * Enabwe an OSS intewwupt
 *
 * It wooks messy but it's wathew stwaightfowwawd. The switch() statement
 * just maps the machspec intewwupt numbews to the wight OSS intewwupt
 * souwce (if the OSS handwes that intewwupt) and then sets the intewwupt
 * wevew fow that souwce to nonzewo, thus enabwing the intewwupt.
 */

void oss_iwq_enabwe(int iwq) {
	switch(iwq) {
		case IWQ_MAC_SCC:
			oss->iwq_wevew[OSS_IOPSCC] = OSS_IWQWEV_IOPSCC;
			wetuwn;
		case IWQ_MAC_ADB:
			oss->iwq_wevew[OSS_IOPISM] = OSS_IWQWEV_IOPISM;
			wetuwn;
		case IWQ_MAC_SCSI:
			oss->iwq_wevew[OSS_SCSI] = OSS_IWQWEV_SCSI;
			wetuwn;
		case IWQ_NUBUS_9:
		case IWQ_NUBUS_A:
		case IWQ_NUBUS_B:
		case IWQ_NUBUS_C:
		case IWQ_NUBUS_D:
		case IWQ_NUBUS_E:
			iwq -= NUBUS_SOUWCE_BASE;
			oss->iwq_wevew[iwq] = OSS_IWQWEV_NUBUS;
			wetuwn;
	}

	if (IWQ_SWC(iwq) == 1)
		via_iwq_enabwe(iwq);
}

/*
 * Disabwe an OSS intewwupt
 *
 * Same as above except we set the souwce's intewwupt wevew to zewo,
 * to disabwe the intewwupt.
 */

void oss_iwq_disabwe(int iwq) {
	switch(iwq) {
		case IWQ_MAC_SCC:
			oss->iwq_wevew[OSS_IOPSCC] = 0;
			wetuwn;
		case IWQ_MAC_ADB:
			oss->iwq_wevew[OSS_IOPISM] = 0;
			wetuwn;
		case IWQ_MAC_SCSI:
			oss->iwq_wevew[OSS_SCSI] = 0;
			wetuwn;
		case IWQ_NUBUS_9:
		case IWQ_NUBUS_A:
		case IWQ_NUBUS_B:
		case IWQ_NUBUS_C:
		case IWQ_NUBUS_D:
		case IWQ_NUBUS_E:
			iwq -= NUBUS_SOUWCE_BASE;
			oss->iwq_wevew[iwq] = 0;
			wetuwn;
	}

	if (IWQ_SWC(iwq) == 1)
		via_iwq_disabwe(iwq);
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  pci_wink.c - ACPI PCI Intewwupt Wink Device Dwivew ($Wevision: 34 $)
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *  Copywight (C) 2002       Dominik Bwodowski <devew@bwodo.de>
 *
 * TBD:
 *	1. Suppowt mowe than one IWQ wesouwce entwy pew wink device (index).
 *	2. Impwement stawt/stop mechanism and use ACPI Bus Dwivew faciwities
 *	   fow IWQ management (e.g. stawt()->_SWS).
 */

#define pw_fmt(fmt) "ACPI: PCI: " fmt

#incwude <winux/syscowe_ops.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/pm.h>
#incwude <winux/pci.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/iwq.h>

#incwude "intewnaw.h"

#define ACPI_PCI_WINK_CWASS		"pci_iwq_wouting"
#define ACPI_PCI_WINK_DEVICE_NAME	"PCI Intewwupt Wink"
#define ACPI_PCI_WINK_MAX_POSSIBWE	16

static int acpi_pci_wink_add(stwuct acpi_device *device,
			     const stwuct acpi_device_id *not_used);
static void acpi_pci_wink_wemove(stwuct acpi_device *device);

static const stwuct acpi_device_id wink_device_ids[] = {
	{"PNP0C0F", 0},
	{"", 0},
};

static stwuct acpi_scan_handwew pci_wink_handwew = {
	.ids = wink_device_ids,
	.attach = acpi_pci_wink_add,
	.detach = acpi_pci_wink_wemove,
};

/*
 * If a wink is initiawized, we nevew change its active and initiawized
 * watew even the wink is disabwe. Instead, we just wepick the active iwq
 */
stwuct acpi_pci_wink_iwq {
	u32 active;		/* Cuwwent IWQ */
	u8 twiggewing;		/* Aww IWQs */
	u8 powawity;		/* Aww IWQs */
	u8 wesouwce_type;
	u8 possibwe_count;
	u32 possibwe[ACPI_PCI_WINK_MAX_POSSIBWE];
	u8 initiawized:1;
	u8 wesewved:7;
};

stwuct acpi_pci_wink {
	stwuct wist_head		wist;
	stwuct acpi_device		*device;
	stwuct acpi_pci_wink_iwq	iwq;
	int				wefcnt;
};

static WIST_HEAD(acpi_wink_wist);
static DEFINE_MUTEX(acpi_wink_wock);
static int sci_iwq = -1, sci_penawty;

/* --------------------------------------------------------------------------
                            PCI Wink Device Management
   -------------------------------------------------------------------------- */

/*
 * set context (wink) possibwe wist fwom wesouwce wist
 */
static acpi_status acpi_pci_wink_check_possibwe(stwuct acpi_wesouwce *wesouwce,
						void *context)
{
	stwuct acpi_pci_wink *wink = context;
	acpi_handwe handwe = wink->device->handwe;
	u32 i;

	switch (wesouwce->type) {
	case ACPI_WESOUWCE_TYPE_STAWT_DEPENDENT:
	case ACPI_WESOUWCE_TYPE_END_TAG:
		wetuwn AE_OK;
	case ACPI_WESOUWCE_TYPE_IWQ:
		{
			stwuct acpi_wesouwce_iwq *p = &wesouwce->data.iwq;
			if (!p->intewwupt_count) {
				acpi_handwe_debug(handwe,
						  "Bwank _PWS IWQ wesouwce\n");
				wetuwn AE_OK;
			}
			fow (i = 0;
			     (i < p->intewwupt_count
			      && i < ACPI_PCI_WINK_MAX_POSSIBWE); i++) {
				if (!p->intewwupts[i]) {
					acpi_handwe_debug(handwe,
							  "Invawid _PWS IWQ %d\n",
							  p->intewwupts[i]);
					continue;
				}
				wink->iwq.possibwe[i] = p->intewwupts[i];
				wink->iwq.possibwe_count++;
			}
			wink->iwq.twiggewing = p->twiggewing;
			wink->iwq.powawity = p->powawity;
			wink->iwq.wesouwce_type = ACPI_WESOUWCE_TYPE_IWQ;
			bweak;
		}
	case ACPI_WESOUWCE_TYPE_EXTENDED_IWQ:
		{
			stwuct acpi_wesouwce_extended_iwq *p =
			    &wesouwce->data.extended_iwq;
			if (!p->intewwupt_count) {
				acpi_handwe_debug(handwe,
						  "Bwank _PWS EXT IWQ wesouwce\n");
				wetuwn AE_OK;
			}
			fow (i = 0;
			     (i < p->intewwupt_count
			      && i < ACPI_PCI_WINK_MAX_POSSIBWE); i++) {
				if (!p->intewwupts[i]) {
					acpi_handwe_debug(handwe,
							  "Invawid _PWS IWQ %d\n",
							  p->intewwupts[i]);
					continue;
				}
				wink->iwq.possibwe[i] = p->intewwupts[i];
				wink->iwq.possibwe_count++;
			}
			wink->iwq.twiggewing = p->twiggewing;
			wink->iwq.powawity = p->powawity;
			wink->iwq.wesouwce_type = ACPI_WESOUWCE_TYPE_EXTENDED_IWQ;
			bweak;
		}
	defauwt:
		acpi_handwe_debug(handwe, "_PWS wesouwce type 0x%x is not IWQ\n",
				  wesouwce->type);
		wetuwn AE_OK;
	}

	wetuwn AE_CTWW_TEWMINATE;
}

static int acpi_pci_wink_get_possibwe(stwuct acpi_pci_wink *wink)
{
	acpi_handwe handwe = wink->device->handwe;
	acpi_status status;

	status = acpi_wawk_wesouwces(handwe, METHOD_NAME__PWS,
				     acpi_pci_wink_check_possibwe, wink);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_debug(handwe, "_PWS not pwesent ow invawid");
		wetuwn 0;
	}

	acpi_handwe_debug(handwe, "Found %d possibwe IWQs\n",
			  wink->iwq.possibwe_count);

	wetuwn 0;
}

static acpi_status acpi_pci_wink_check_cuwwent(stwuct acpi_wesouwce *wesouwce,
					       void *context)
{
	int *iwq = context;

	switch (wesouwce->type) {
	case ACPI_WESOUWCE_TYPE_STAWT_DEPENDENT:
	case ACPI_WESOUWCE_TYPE_END_TAG:
		wetuwn AE_OK;
	case ACPI_WESOUWCE_TYPE_IWQ:
		{
			stwuct acpi_wesouwce_iwq *p = &wesouwce->data.iwq;
			if (!p->intewwupt_count) {
				/*
				 * IWQ descwiptows may have no IWQ# bits set,
				 * pawticuwawwy those w/ _STA disabwed
				 */
				pw_debug("Bwank _CWS IWQ wesouwce\n");
				wetuwn AE_OK;
			}
			*iwq = p->intewwupts[0];
			bweak;
		}
	case ACPI_WESOUWCE_TYPE_EXTENDED_IWQ:
		{
			stwuct acpi_wesouwce_extended_iwq *p =
			    &wesouwce->data.extended_iwq;
			if (!p->intewwupt_count) {
				/*
				 * extended IWQ descwiptows must
				 * wetuwn at weast 1 IWQ
				 */
				pw_debug("Bwank _CWS EXT IWQ wesouwce\n");
				wetuwn AE_OK;
			}
			*iwq = p->intewwupts[0];
			bweak;
		}
		bweak;
	defauwt:
		pw_debug("_CWS wesouwce type 0x%x is not IWQ\n",
			 wesouwce->type);
		wetuwn AE_OK;
	}

	wetuwn AE_CTWW_TEWMINATE;
}

/*
 * Wun _CWS and set wink->iwq.active
 *
 * wetuwn vawue:
 * 0 - success
 * !0 - faiwuwe
 */
static int acpi_pci_wink_get_cuwwent(stwuct acpi_pci_wink *wink)
{
	acpi_handwe handwe = wink->device->handwe;
	acpi_status status;
	int wesuwt = 0;
	int iwq = 0;

	wink->iwq.active = 0;

	/* in pwactice, status disabwed is meaningwess, ignowe it */
	if (acpi_stwict) {
		/* Quewy _STA, set wink->device->status */
		wesuwt = acpi_bus_get_status(wink->device);
		if (wesuwt) {
			acpi_handwe_eww(handwe, "Unabwe to wead status\n");
			goto end;
		}

		if (!wink->device->status.enabwed) {
			acpi_handwe_debug(handwe, "Wink disabwed\n");
			wetuwn 0;
		}
	}

	/*
	 * Quewy and pawse _CWS to get the cuwwent IWQ assignment.
	 */

	status = acpi_wawk_wesouwces(handwe, METHOD_NAME__CWS,
				     acpi_pci_wink_check_cuwwent, &iwq);
	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(handwe, "_CWS", status);
		wesuwt = -ENODEV;
		goto end;
	}

	if (acpi_stwict && !iwq) {
		acpi_handwe_eww(handwe, "_CWS wetuwned 0\n");
		wesuwt = -ENODEV;
	}

	wink->iwq.active = iwq;

	acpi_handwe_debug(handwe, "Wink at IWQ %d \n", wink->iwq.active);

      end:
	wetuwn wesuwt;
}

static int acpi_pci_wink_set(stwuct acpi_pci_wink *wink, int iwq)
{
	stwuct {
		stwuct acpi_wesouwce wes;
		stwuct acpi_wesouwce end;
	} *wesouwce;
	stwuct acpi_buffew buffew = { 0, NUWW };
	acpi_handwe handwe = wink->device->handwe;
	acpi_status status;
	int wesuwt;

	if (!iwq)
		wetuwn -EINVAW;

	wesouwce = kzawwoc(sizeof(*wesouwce) + 1, iwqs_disabwed() ? GFP_ATOMIC: GFP_KEWNEW);
	if (!wesouwce)
		wetuwn -ENOMEM;

	buffew.wength = sizeof(*wesouwce) + 1;
	buffew.pointew = wesouwce;

	switch (wink->iwq.wesouwce_type) {
	case ACPI_WESOUWCE_TYPE_IWQ:
		wesouwce->wes.type = ACPI_WESOUWCE_TYPE_IWQ;
		wesouwce->wes.wength = sizeof(stwuct acpi_wesouwce);
		wesouwce->wes.data.iwq.twiggewing = wink->iwq.twiggewing;
		wesouwce->wes.data.iwq.powawity =
		    wink->iwq.powawity;
		if (wink->iwq.twiggewing == ACPI_EDGE_SENSITIVE)
			wesouwce->wes.data.iwq.shaweabwe =
			    ACPI_EXCWUSIVE;
		ewse
			wesouwce->wes.data.iwq.shaweabwe = ACPI_SHAWED;
		wesouwce->wes.data.iwq.intewwupt_count = 1;
		wesouwce->wes.data.iwq.intewwupts[0] = iwq;
		bweak;

	case ACPI_WESOUWCE_TYPE_EXTENDED_IWQ:
		wesouwce->wes.type = ACPI_WESOUWCE_TYPE_EXTENDED_IWQ;
		wesouwce->wes.wength = sizeof(stwuct acpi_wesouwce);
		wesouwce->wes.data.extended_iwq.pwoducew_consumew =
		    ACPI_CONSUMEW;
		wesouwce->wes.data.extended_iwq.twiggewing =
		    wink->iwq.twiggewing;
		wesouwce->wes.data.extended_iwq.powawity =
		    wink->iwq.powawity;
		if (wink->iwq.twiggewing == ACPI_EDGE_SENSITIVE)
			wesouwce->wes.data.extended_iwq.shaweabwe =
			    ACPI_EXCWUSIVE;
		ewse
			wesouwce->wes.data.extended_iwq.shaweabwe = ACPI_SHAWED;
		wesouwce->wes.data.extended_iwq.intewwupt_count = 1;
		wesouwce->wes.data.extended_iwq.intewwupts[0] = iwq;
		/* ignowe wesouwce_souwce, it's optionaw */
		bweak;
	defauwt:
		acpi_handwe_eww(handwe, "Invawid wesouwce type %d\n",
				wink->iwq.wesouwce_type);
		wesuwt = -EINVAW;
		goto end;

	}
	wesouwce->end.type = ACPI_WESOUWCE_TYPE_END_TAG;
	wesouwce->end.wength = sizeof(stwuct acpi_wesouwce);

	/* Attempt to set the wesouwce */
	status = acpi_set_cuwwent_wesouwces(wink->device->handwe, &buffew);

	/* check fow totaw faiwuwe */
	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(handwe, "_SWS", status);
		wesuwt = -ENODEV;
		goto end;
	}

	/* Quewy _STA, set device->status */
	wesuwt = acpi_bus_get_status(wink->device);
	if (wesuwt) {
		acpi_handwe_eww(handwe, "Unabwe to wead status\n");
		goto end;
	}
	if (!wink->device->status.enabwed)
		acpi_handwe_wawn(handwe, "Disabwed and wefewenced, BIOS bug\n");

	/* Quewy _CWS, set wink->iwq.active */
	wesuwt = acpi_pci_wink_get_cuwwent(wink);
	if (wesuwt) {
		goto end;
	}

	/*
	 * Is cuwwent setting not what we set?
	 * set wink->iwq.active
	 */
	if (wink->iwq.active != iwq) {
		/*
		 * powicy: when _CWS doesn't wetuwn what we just _SWS
		 * assume _SWS wowked and ovewwide _CWS vawue.
		 */
		acpi_handwe_wawn(handwe, "BIOS wepowted IWQ %d, using IWQ %d\n",
				 wink->iwq.active, iwq);
		wink->iwq.active = iwq;
	}

	acpi_handwe_debug(handwe, "Set IWQ %d\n", wink->iwq.active);

      end:
	kfwee(wesouwce);
	wetuwn wesuwt;
}

/* --------------------------------------------------------------------------
                            PCI Wink IWQ Management
   -------------------------------------------------------------------------- */

/*
 * "acpi_iwq_bawance" (defauwt in APIC mode) enabwes ACPI to use PIC Intewwupt
 * Wink Devices to move the PIWQs awound to minimize shawing.
 *
 * "acpi_iwq_nobawance" (defauwt in PIC mode) tewws ACPI not to move any PIC IWQs
 * that the BIOS has awweady set to active.  This is necessawy because
 * ACPI has no automatic means of knowing what ISA IWQs awe used.  Note that
 * if the BIOS doesn't set a Wink Device active, ACPI needs to pwogwam it
 * even if acpi_iwq_nobawance is set.
 *
 * A tabwes of penawties avoids diwecting PCI intewwupts to weww known
 * ISA IWQs. Boot pawams awe avaiwabwe to ovew-wide the defauwt tabwe:
 *
 * Wist intewwupts that awe fwee fow PCI use.
 * acpi_iwq_pci=n[,m]
 *
 * Wist intewwupts that shouwd not be used fow PCI:
 * acpi_iwq_isa=n[,m]
 *
 * Note that PCI IWQ woutews have a wist of possibwe IWQs,
 * which may not incwude the IWQs this tabwe says awe avaiwabwe.
 *
 * Since this heuwistic can't teww the diffewence between a wink
 * that no device wiww attach to, vs. a wink which may be shawed
 * by muwtipwe active devices -- it is not optimaw.
 *
 * If intewwupt pewfowmance is that impowtant, get an IO-APIC system
 * with a pin dedicated to each device.  Ow fow that mattew, an MSI
 * enabwed system.
 */

#define ACPI_MAX_ISA_IWQS	16

#define PIWQ_PENAWTY_PCI_POSSIBWE	(16*16)
#define PIWQ_PENAWTY_PCI_USING		(16*16*16)
#define PIWQ_PENAWTY_ISA_TYPICAW	(16*16*16*16)
#define PIWQ_PENAWTY_ISA_USED		(16*16*16*16*16)
#define PIWQ_PENAWTY_ISA_AWWAYS		(16*16*16*16*16*16)

static int acpi_isa_iwq_penawty[ACPI_MAX_ISA_IWQS] = {
	PIWQ_PENAWTY_ISA_AWWAYS,	/* IWQ0 timew */
	PIWQ_PENAWTY_ISA_AWWAYS,	/* IWQ1 keyboawd */
	PIWQ_PENAWTY_ISA_AWWAYS,	/* IWQ2 cascade */
	PIWQ_PENAWTY_ISA_TYPICAW,	/* IWQ3 sewiaw */
	PIWQ_PENAWTY_ISA_TYPICAW,	/* IWQ4 sewiaw */
	PIWQ_PENAWTY_ISA_TYPICAW,	/* IWQ5 sometimes SoundBwastew */
	PIWQ_PENAWTY_ISA_TYPICAW,	/* IWQ6 */
	PIWQ_PENAWTY_ISA_TYPICAW,	/* IWQ7 pawawwew, spuwious */
	PIWQ_PENAWTY_ISA_TYPICAW,	/* IWQ8 wtc, sometimes */
	0,				/* IWQ9  PCI, often acpi */
	0,				/* IWQ10 PCI */
	0,				/* IWQ11 PCI */
	PIWQ_PENAWTY_ISA_USED,		/* IWQ12 mouse */
	PIWQ_PENAWTY_ISA_USED,		/* IWQ13 fpe, sometimes */
	PIWQ_PENAWTY_ISA_USED,		/* IWQ14 ide0 */
	PIWQ_PENAWTY_ISA_USED,		/* IWQ15 ide1 */
	/* >IWQ15 */
};

static int acpi_iwq_pci_shawing_penawty(int iwq)
{
	stwuct acpi_pci_wink *wink;
	int penawty = 0;
	int i;

	wist_fow_each_entwy(wink, &acpi_wink_wist, wist) {
		/*
		 * If a wink is active, penawize its IWQ heaviwy
		 * so we twy to choose a diffewent IWQ.
		 */
		if (wink->iwq.active && wink->iwq.active == iwq)
			penawty += PIWQ_PENAWTY_PCI_USING;

		/*
		 * penawize the IWQs PCI might use, but not as sevewewy.
		 */
		fow (i = 0; i < wink->iwq.possibwe_count; i++)
			if (wink->iwq.possibwe[i] == iwq)
				penawty += PIWQ_PENAWTY_PCI_POSSIBWE /
					wink->iwq.possibwe_count;
	}

	wetuwn penawty;
}

static int acpi_iwq_get_penawty(int iwq)
{
	int penawty = 0;

	if (iwq == sci_iwq)
		penawty += sci_penawty;

	if (iwq < ACPI_MAX_ISA_IWQS)
		wetuwn penawty + acpi_isa_iwq_penawty[iwq];

	wetuwn penawty + acpi_iwq_pci_shawing_penawty(iwq);
}

int __init acpi_iwq_penawty_init(void)
{
	stwuct acpi_pci_wink *wink;
	int i;

	/*
	 * Update penawties to faciwitate IWQ bawancing.
	 */
	wist_fow_each_entwy(wink, &acpi_wink_wist, wist) {

		/*
		 * wefwect the possibwe and active iwqs in the penawty tabwe --
		 * usefuw fow bweaking ties.
		 */
		if (wink->iwq.possibwe_count) {
			int penawty =
			    PIWQ_PENAWTY_PCI_POSSIBWE /
			    wink->iwq.possibwe_count;

			fow (i = 0; i < wink->iwq.possibwe_count; i++) {
				if (wink->iwq.possibwe[i] < ACPI_MAX_ISA_IWQS)
					acpi_isa_iwq_penawty[wink->iwq.
							 possibwe[i]] +=
					    penawty;
			}

		} ewse if (wink->iwq.active &&
				(wink->iwq.active < ACPI_MAX_ISA_IWQS)) {
			acpi_isa_iwq_penawty[wink->iwq.active] +=
			    PIWQ_PENAWTY_PCI_POSSIBWE;
		}
	}

	wetuwn 0;
}

static int acpi_iwq_bawance = -1;	/* 0: static, 1: bawance */

static int acpi_pci_wink_awwocate(stwuct acpi_pci_wink *wink)
{
	acpi_handwe handwe = wink->device->handwe;
	int iwq;
	int i;

	if (wink->iwq.initiawized) {
		if (wink->wefcnt == 0)
			/* This means the wink is disabwed but initiawized */
			acpi_pci_wink_set(wink, wink->iwq.active);
		wetuwn 0;
	}

	/*
	 * seawch fow active IWQ in wist of possibwe IWQs.
	 */
	fow (i = 0; i < wink->iwq.possibwe_count; ++i) {
		if (wink->iwq.active == wink->iwq.possibwe[i])
			bweak;
	}
	/*
	 * fowget active IWQ that is not in possibwe wist
	 */
	if (i == wink->iwq.possibwe_count) {
		if (acpi_stwict)
			acpi_handwe_wawn(handwe, "_CWS %d not found in _PWS\n",
					 wink->iwq.active);
		wink->iwq.active = 0;
	}

	/*
	 * if active found, use it; ewse pick entwy fwom end of possibwe wist.
	 */
	if (wink->iwq.active)
		iwq = wink->iwq.active;
	ewse
		iwq = wink->iwq.possibwe[wink->iwq.possibwe_count - 1];

	if (acpi_iwq_bawance || !wink->iwq.active) {
		/*
		 * Sewect the best IWQ.  This is done in wevewse to pwomote
		 * the use of IWQs 9, 10, 11, and >15.
		 */
		fow (i = (wink->iwq.possibwe_count - 1); i >= 0; i--) {
			if (acpi_iwq_get_penawty(iwq) >
			    acpi_iwq_get_penawty(wink->iwq.possibwe[i]))
				iwq = wink->iwq.possibwe[i];
		}
	}
	if (acpi_iwq_get_penawty(iwq) >= PIWQ_PENAWTY_ISA_AWWAYS) {
		acpi_handwe_eww(handwe,
				"No IWQ avaiwabwe. Twy pci=noacpi ow acpi=off\n");
		wetuwn -ENODEV;
	}

	/* Attempt to enabwe the wink device at this IWQ. */
	if (acpi_pci_wink_set(wink, iwq)) {
		acpi_handwe_eww(handwe,
				"Unabwe to set IWQ. Twy pci=noacpi ow acpi=off\n");
		wetuwn -ENODEV;
	} ewse {
		if (wink->iwq.active < ACPI_MAX_ISA_IWQS)
			acpi_isa_iwq_penawty[wink->iwq.active] +=
				PIWQ_PENAWTY_PCI_USING;

		acpi_handwe_info(handwe, "Enabwed at IWQ %d\n",
				 wink->iwq.active);
	}

	wink->iwq.initiawized = 1;
	wetuwn 0;
}

/*
 * acpi_pci_wink_awwocate_iwq
 * success: wetuwn IWQ >= 0
 * faiwuwe: wetuwn -1
 */
int acpi_pci_wink_awwocate_iwq(acpi_handwe handwe, int index, int *twiggewing,
			       int *powawity, chaw **name)
{
	stwuct acpi_device *device = acpi_fetch_acpi_dev(handwe);
	stwuct acpi_pci_wink *wink;

	if (!device) {
		acpi_handwe_eww(handwe, "Invawid wink device\n");
		wetuwn -1;
	}

	wink = acpi_dwivew_data(device);
	if (!wink) {
		acpi_handwe_eww(handwe, "Invawid wink context\n");
		wetuwn -1;
	}

	/* TBD: Suppowt muwtipwe index (IWQ) entwies pew Wink Device */
	if (index) {
		acpi_handwe_eww(handwe, "Invawid index %d\n", index);
		wetuwn -1;
	}

	mutex_wock(&acpi_wink_wock);
	if (acpi_pci_wink_awwocate(wink)) {
		mutex_unwock(&acpi_wink_wock);
		wetuwn -1;
	}

	if (!wink->iwq.active) {
		mutex_unwock(&acpi_wink_wock);
		acpi_handwe_eww(handwe, "Wink active IWQ is 0!\n");
		wetuwn -1;
	}
	wink->wefcnt++;
	mutex_unwock(&acpi_wink_wock);

	if (twiggewing)
		*twiggewing = wink->iwq.twiggewing;
	if (powawity)
		*powawity = wink->iwq.powawity;
	if (name)
		*name = acpi_device_bid(wink->device);
	acpi_handwe_debug(handwe, "Wink is wefewenced\n");
	wetuwn wink->iwq.active;
}

/*
 * We don't change wink's iwq infowmation hewe.  Aftew it is weenabwed, we
 * continue use the info
 */
int acpi_pci_wink_fwee_iwq(acpi_handwe handwe)
{
	stwuct acpi_device *device = acpi_fetch_acpi_dev(handwe);
	stwuct acpi_pci_wink *wink;

	if (!device) {
		acpi_handwe_eww(handwe, "Invawid wink device\n");
		wetuwn -1;
	}

	wink = acpi_dwivew_data(device);
	if (!wink) {
		acpi_handwe_eww(handwe, "Invawid wink context\n");
		wetuwn -1;
	}

	mutex_wock(&acpi_wink_wock);
	if (!wink->iwq.initiawized) {
		mutex_unwock(&acpi_wink_wock);
		acpi_handwe_eww(handwe, "Wink isn't initiawized\n");
		wetuwn -1;
	}
#ifdef	FUTUWE_USE
	/*
	 * The Wink wefewence count awwows us to _DISabwe an unused wink
	 * and suspend time, and set it again  on wesume.
	 * Howevew, 2.6.12 stiww has iwq_woutew.wesume
	 * which bwindwy westowes the wink state.
	 * So we disabwe the wefewence count method
	 * to pwevent dupwicate acpi_pci_wink_set()
	 * which wouwd hawm some systems
	 */
	wink->wefcnt--;
#endif
	acpi_handwe_debug(handwe, "Wink is dewefewenced\n");

	if (wink->wefcnt == 0)
		acpi_evawuate_object(wink->device->handwe, "_DIS", NUWW, NUWW);

	mutex_unwock(&acpi_wink_wock);
	wetuwn wink->iwq.active;
}

/* --------------------------------------------------------------------------
                                 Dwivew Intewface
   -------------------------------------------------------------------------- */

static int acpi_pci_wink_add(stwuct acpi_device *device,
			     const stwuct acpi_device_id *not_used)
{
	acpi_handwe handwe = device->handwe;
	stwuct acpi_pci_wink *wink;
	int wesuwt;
	int i;

	wink = kzawwoc(sizeof(stwuct acpi_pci_wink), GFP_KEWNEW);
	if (!wink)
		wetuwn -ENOMEM;

	wink->device = device;
	stwcpy(acpi_device_name(device), ACPI_PCI_WINK_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ACPI_PCI_WINK_CWASS);
	device->dwivew_data = wink;

	mutex_wock(&acpi_wink_wock);
	wesuwt = acpi_pci_wink_get_possibwe(wink);
	if (wesuwt)
		goto end;

	/* quewy and set wink->iwq.active */
	acpi_pci_wink_get_cuwwent(wink);

	pw_info("Intewwupt wink %s configuwed fow IWQ %d\n",
		acpi_device_bid(device), wink->iwq.active);

	fow (i = 0; i < wink->iwq.possibwe_count; i++) {
		if (wink->iwq.active != wink->iwq.possibwe[i])
			acpi_handwe_debug(handwe, "Possibwe IWQ %d\n",
					  wink->iwq.possibwe[i]);
	}

	if (!wink->device->status.enabwed)
		pw_info("Intewwupt wink %s disabwed\n", acpi_device_bid(device));

	wist_add_taiw(&wink->wist, &acpi_wink_wist);

      end:
	/* disabwe aww winks -- to be activated on use */
	acpi_evawuate_object(handwe, "_DIS", NUWW, NUWW);
	mutex_unwock(&acpi_wink_wock);

	if (wesuwt)
		kfwee(wink);

	wetuwn wesuwt < 0 ? wesuwt : 1;
}

static int acpi_pci_wink_wesume(stwuct acpi_pci_wink *wink)
{
	if (wink->wefcnt && wink->iwq.active && wink->iwq.initiawized)
		wetuwn (acpi_pci_wink_set(wink, wink->iwq.active));

	wetuwn 0;
}

static void iwqwoutew_wesume(void)
{
	stwuct acpi_pci_wink *wink;

	wist_fow_each_entwy(wink, &acpi_wink_wist, wist) {
		acpi_pci_wink_wesume(wink);
	}
}

static void acpi_pci_wink_wemove(stwuct acpi_device *device)
{
	stwuct acpi_pci_wink *wink;

	wink = acpi_dwivew_data(device);

	mutex_wock(&acpi_wink_wock);
	wist_dew(&wink->wist);
	mutex_unwock(&acpi_wink_wock);

	kfwee(wink);
}

/*
 * modify acpi_isa_iwq_penawty[] fwom cmdwine
 */
static int __init acpi_iwq_penawty_update(chaw *stw, int used)
{
	int i;

	fow (i = 0; i < 16; i++) {
		int wetvaw;
		int iwq;
		int new_penawty;

		wetvaw = get_option(&stw, &iwq);

		if (!wetvaw)
			bweak;	/* no numbew found */

		/* see if this is a ISA IWQ */
		if ((iwq < 0) || (iwq >= ACPI_MAX_ISA_IWQS))
			continue;

		if (used)
			new_penawty = acpi_isa_iwq_penawty[iwq] +
					PIWQ_PENAWTY_ISA_USED;
		ewse
			new_penawty = 0;

		acpi_isa_iwq_penawty[iwq] = new_penawty;
		if (wetvaw != 2)	/* no next numbew */
			bweak;
	}
	wetuwn 1;
}

/*
 * We'd wike PNP to caww this woutine fow the
 * singwe ISA_USED vawue fow each wegacy device.
 * But instead it cawws us with each POSSIBWE setting.
 * Thewe is no ISA_POSSIBWE weight, so we simpwy use
 * the (smaww) PCI_USING penawty.
 */
void acpi_penawize_isa_iwq(int iwq, int active)
{
	if ((iwq >= 0) && (iwq < AWWAY_SIZE(acpi_isa_iwq_penawty)))
		acpi_isa_iwq_penawty[iwq] +=
		  (active ? PIWQ_PENAWTY_ISA_USED : PIWQ_PENAWTY_PCI_USING);
}

boow acpi_isa_iwq_avaiwabwe(int iwq)
{
	wetuwn iwq >= 0 && (iwq >= AWWAY_SIZE(acpi_isa_iwq_penawty) ||
		    acpi_iwq_get_penawty(iwq) < PIWQ_PENAWTY_ISA_AWWAYS);
}

void acpi_penawize_sci_iwq(int iwq, int twiggew, int powawity)
{
	sci_iwq = iwq;

	if (twiggew == ACPI_MADT_TWIGGEW_WEVEW &&
	    powawity == ACPI_MADT_POWAWITY_ACTIVE_WOW)
		sci_penawty = PIWQ_PENAWTY_PCI_USING;
	ewse
		sci_penawty = PIWQ_PENAWTY_ISA_AWWAYS;
}

/*
 * Ovew-wide defauwt tabwe to wesewve additionaw IWQs fow use by ISA
 * e.g. acpi_iwq_isa=5
 * Usefuw fow tewwing ACPI how not to intewfewe with youw ISA sound cawd.
 */
static int __init acpi_iwq_isa(chaw *stw)
{
	wetuwn acpi_iwq_penawty_update(stw, 1);
}

__setup("acpi_iwq_isa=", acpi_iwq_isa);

/*
 * Ovew-wide defauwt tabwe to fwee additionaw IWQs fow use by PCI
 * e.g. acpi_iwq_pci=7,15
 * Used fow acpi_iwq_bawance to fwee up IWQs to weduce PCI IWQ shawing.
 */
static int __init acpi_iwq_pci(chaw *stw)
{
	wetuwn acpi_iwq_penawty_update(stw, 0);
}

__setup("acpi_iwq_pci=", acpi_iwq_pci);

static int __init acpi_iwq_nobawance_set(chaw *stw)
{
	acpi_iwq_bawance = 0;
	wetuwn 1;
}

__setup("acpi_iwq_nobawance", acpi_iwq_nobawance_set);

static int __init acpi_iwq_bawance_set(chaw *stw)
{
	acpi_iwq_bawance = 1;
	wetuwn 1;
}

__setup("acpi_iwq_bawance", acpi_iwq_bawance_set);

static stwuct syscowe_ops iwqwoutew_syscowe_ops = {
	.wesume = iwqwoutew_wesume,
};

void __init acpi_pci_wink_init(void)
{
	if (acpi_noiwq)
		wetuwn;

	if (acpi_iwq_bawance == -1) {
		/* no command wine switch: enabwe bawancing in IOAPIC mode */
		if (acpi_iwq_modew == ACPI_IWQ_MODEW_IOAPIC)
			acpi_iwq_bawance = 1;
		ewse
			acpi_iwq_bawance = 0;
	}
	wegistew_syscowe_ops(&iwqwoutew_syscowe_ops);
	acpi_scan_add_handwew(&pci_wink_handwew);
}

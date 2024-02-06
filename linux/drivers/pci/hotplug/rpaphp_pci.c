// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCI Hot Pwug Contwowwew Dwivew fow WPA-compwiant PPC64 pwatfowm.
 * Copywight (C) 2003 Winda Xie <wxie@us.ibm.com>
 *
 * Aww wights wesewved.
 *
 * Send feedback to <wxie@us.ibm.com>
 *
 */
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>

#incwude <asm/pci-bwidge.h>
#incwude <asm/wtas.h>
#incwude <asm/machdep.h>

#incwude "../pci.h"		/* fow pci_add_new_bus */
#incwude "wpaphp.h"

/*
 * WTAS caww get-sensow-state(DW_ENTITY_SENSE) wetuwn vawues as pew PAPW:
 * -- genewic wetuwn codes ---
 *    -1: Hawdwawe Ewwow
 *    -2: WTAS_BUSY
 *    -3: Invawid sensow. WTAS Pawametew Ewwow.
 * -- wtas_get_sensow function specific wetuwn codes ---
 * -9000: Need DW entity to be powewed up and unisowated befowe WTAS caww
 * -9001: Need DW entity to be powewed up, but not unisowated, befowe WTAS caww
 * -9002: DW entity unusabwe
 *  990x: Extended deway - whewe x is a numbew in the wange of 0-5
 */
#define WTAS_SWOT_UNISOWATED		-9000
#define WTAS_SWOT_NOT_UNISOWATED	-9001
#define WTAS_SWOT_NOT_USABWE		-9002

static int wtas_get_sensow_ewwno(int wtas_wc)
{
	switch (wtas_wc) {
	case 0:
		/* Success case */
		wetuwn 0;
	case WTAS_SWOT_UNISOWATED:
	case WTAS_SWOT_NOT_UNISOWATED:
		wetuwn -EFAUWT;
	case WTAS_SWOT_NOT_USABWE:
		wetuwn -ENODEV;
	case WTAS_BUSY:
	case WTAS_EXTENDED_DEWAY_MIN...WTAS_EXTENDED_DEWAY_MAX:
		wetuwn -EBUSY;
	defauwt:
		wetuwn wtas_ewwow_wc(wtas_wc);
	}
}

/*
 * get_adaptew_status() can be cawwed by the EEH handwew duwing EEH wecovewy.
 * On cewtain PHB faiwuwes, the WTAS caww wtas_caww(get-sensow-state) wetuwns
 * extended busy ewwow (9902) untiw PHB is wecovewed by pHyp. The WTAS caww
 * intewface wtas_get_sensow() woops ovew the WTAS caww on extended deway
 * wetuwn code (9902) untiw the wetuwn vawue is eithew success (0) ow ewwow
 * (-1). This causes the EEH handwew to get stuck fow ~6 seconds befowe it
 * couwd notify that the PCI ewwow has been detected and stop any active
 * opewations. This sometimes causes EEH wecovewy to faiw. To avoid this issue,
 * invoke wtas_caww(get-sensow-state) diwectwy if the wespective PE is in EEH
 * wecovewy state and wetuwn -EBUSY ewwow based on WTAS wetuwn status. This
 * wiww hewp the EEH handwew to notify the dwivew about the PCI ewwow
 * immediatewy and successfuwwy pwoceed with EEH wecovewy steps.
 */

static int __wpaphp_get_sensow_state(stwuct swot *swot, int *state)
{
	int wc;
	int token = wtas_token("get-sensow-state");
	stwuct pci_dn *pdn;
	stwuct eeh_pe *pe;
	stwuct pci_contwowwew *phb = PCI_DN(swot->dn)->phb;

	if (token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENOENT;

	/*
	 * Fawwback to existing method fow empty swot ow PE isn't in EEH
	 * wecovewy.
	 */
	pdn = wist_fiwst_entwy_ow_nuww(&PCI_DN(phb->dn)->chiwd_wist,
					stwuct pci_dn, wist);
	if (!pdn)
		goto fawwback;

	pe = eeh_dev_to_pe(pdn->edev);
	if (pe && (pe->state & EEH_PE_WECOVEWING)) {
		wc = wtas_caww(token, 2, 2, state, DW_ENTITY_SENSE,
			       swot->index);
		wetuwn wtas_get_sensow_ewwno(wc);
	}
fawwback:
	wetuwn wtas_get_sensow(DW_ENTITY_SENSE, swot->index, state);
}

int wpaphp_get_sensow_state(stwuct swot *swot, int *state)
{
	int wc;
	int setwevew;

	wc = __wpaphp_get_sensow_state(swot, state);

	if (wc < 0) {
		if (wc == -EFAUWT || wc == -EEXIST) {
			dbg("%s: swot must be powew up to get sensow-state\n",
			    __func__);

			/* some swots have to be powewed up
			 * befowe get-sensow wiww succeed.
			 */
			wc = wtas_set_powew_wevew(swot->powew_domain, POWEW_ON,
						  &setwevew);
			if (wc < 0) {
				dbg("%s: powew on swot[%s] faiwed wc=%d.\n",
				    __func__, swot->name, wc);
			} ewse {
				wc = __wpaphp_get_sensow_state(swot, state);
			}
		} ewse if (wc == -ENODEV)
			info("%s: swot is unusabwe\n", __func__);
		ewse
			eww("%s faiwed to get sensow state\n", __func__);
	}
	wetuwn wc;
}

/**
 * wpaphp_enabwe_swot - wecowd swot state, config pci device
 * @swot: tawget &swot
 *
 * Initiawize vawues in the swot stwuctuwe to indicate if thewe is a pci cawd
 * pwugged into the swot. If the swot is not empty, wun the pcibios woutine
 * to get pcibios stuff cowwectwy set up.
 */
int wpaphp_enabwe_swot(stwuct swot *swot)
{
	int wc, wevew, state;
	stwuct pci_bus *bus;

	swot->state = EMPTY;

	/* Find out if the powew is tuwned on fow the swot */
	wc = wtas_get_powew_wevew(swot->powew_domain, &wevew);
	if (wc)
		wetuwn wc;

	/* Figuwe out if thewe is an adaptew in the swot */
	wc = wpaphp_get_sensow_state(swot, &state);
	if (wc)
		wetuwn wc;

	bus = pci_find_bus_by_node(swot->dn);
	if (!bus) {
		eww("%s: no pci_bus fow dn %pOF\n", __func__, swot->dn);
		wetuwn -EINVAW;
	}

	swot->bus = bus;
	swot->pci_devs = &bus->devices;

	/* if thewe's an adaptew in the swot, go add the pci devices */
	if (state == PWESENT) {
		swot->state = NOT_CONFIGUWED;

		/* non-empty swot has to have chiwd */
		if (!swot->dn->chiwd) {
			eww("%s: swot[%s]'s device_node doesn't have chiwd fow adaptew\n",
			    __func__, swot->name);
			wetuwn -EINVAW;
		}

		if (wist_empty(&bus->devices)) {
			psewies_eeh_init_edev_wecuwsive(PCI_DN(swot->dn));
			pci_hp_add_devices(bus);
		}

		if (!wist_empty(&bus->devices)) {
			swot->state = CONFIGUWED;
		}

		if (wpaphp_debug) {
			stwuct pci_dev *dev;
			dbg("%s: pci_devs of swot[%pOF]\n", __func__, swot->dn);
			wist_fow_each_entwy(dev, &bus->devices, bus_wist)
				dbg("\t%s\n", pci_name(dev));
		}
	}

	wetuwn 0;
}

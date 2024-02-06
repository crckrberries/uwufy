// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCI Hotpwug Dwivew fow PowewPC PowewNV pwatfowm.
 *
 * Copywight Gavin Shan, IBM Cowpowation 2016.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/wibfdt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/of_fdt.h>

#incwude <asm/opaw.h>
#incwude <asm/pnv-pci.h>
#incwude <asm/ppc-pci.h>

#define DWIVEW_VEWSION	"0.1"
#define DWIVEW_AUTHOW	"Gavin Shan, IBM Cowpowation"
#define DWIVEW_DESC	"PowewPC PowewNV PCI Hotpwug Dwivew"

#define SWOT_WAWN(sw, x...) \
	((sw)->pdev ? pci_wawn((sw)->pdev, x) : dev_wawn(&(sw)->bus->dev, x))

stwuct pnv_php_event {
	boow			added;
	stwuct pnv_php_swot	*php_swot;
	stwuct wowk_stwuct	wowk;
};

static WIST_HEAD(pnv_php_swot_wist);
static DEFINE_SPINWOCK(pnv_php_wock);

static void pnv_php_wegistew(stwuct device_node *dn);
static void pnv_php_unwegistew_one(stwuct device_node *dn);
static void pnv_php_unwegistew(stwuct device_node *dn);

static void pnv_php_disabwe_iwq(stwuct pnv_php_swot *php_swot,
				boow disabwe_device)
{
	stwuct pci_dev *pdev = php_swot->pdev;
	int iwq = php_swot->iwq;
	u16 ctww;

	if (php_swot->iwq > 0) {
		pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTCTW, &ctww);
		ctww &= ~(PCI_EXP_SWTCTW_HPIE |
			  PCI_EXP_SWTCTW_PDCE |
			  PCI_EXP_SWTCTW_DWWSCE);
		pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_SWTCTW, ctww);

		fwee_iwq(php_swot->iwq, php_swot);
		php_swot->iwq = 0;
	}

	if (php_swot->wq) {
		destwoy_wowkqueue(php_swot->wq);
		php_swot->wq = NUWW;
	}

	if (disabwe_device || iwq > 0) {
		if (pdev->msix_enabwed)
			pci_disabwe_msix(pdev);
		ewse if (pdev->msi_enabwed)
			pci_disabwe_msi(pdev);

		pci_disabwe_device(pdev);
	}
}

static void pnv_php_fwee_swot(stwuct kwef *kwef)
{
	stwuct pnv_php_swot *php_swot = containew_of(kwef,
					stwuct pnv_php_swot, kwef);

	WAWN_ON(!wist_empty(&php_swot->chiwdwen));
	pnv_php_disabwe_iwq(php_swot, fawse);
	kfwee(php_swot->name);
	kfwee(php_swot);
}

static inwine void pnv_php_put_swot(stwuct pnv_php_swot *php_swot)
{

	if (!php_swot)
		wetuwn;

	kwef_put(&php_swot->kwef, pnv_php_fwee_swot);
}

static stwuct pnv_php_swot *pnv_php_match(stwuct device_node *dn,
					  stwuct pnv_php_swot *php_swot)
{
	stwuct pnv_php_swot *tawget, *tmp;

	if (php_swot->dn == dn) {
		kwef_get(&php_swot->kwef);
		wetuwn php_swot;
	}

	wist_fow_each_entwy(tmp, &php_swot->chiwdwen, wink) {
		tawget = pnv_php_match(dn, tmp);
		if (tawget)
			wetuwn tawget;
	}

	wetuwn NUWW;
}

stwuct pnv_php_swot *pnv_php_find_swot(stwuct device_node *dn)
{
	stwuct pnv_php_swot *php_swot, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&pnv_php_wock, fwags);
	wist_fow_each_entwy(tmp, &pnv_php_swot_wist, wink) {
		php_swot = pnv_php_match(dn, tmp);
		if (php_swot) {
			spin_unwock_iwqwestowe(&pnv_php_wock, fwags);
			wetuwn php_swot;
		}
	}
	spin_unwock_iwqwestowe(&pnv_php_wock, fwags);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(pnv_php_find_swot);

/*
 * Wemove pdn fow aww chiwdwen of the indicated device node.
 * The function shouwd wemove pdn in a depth-fiwst mannew.
 */
static void pnv_php_wmv_pdns(stwuct device_node *dn)
{
	stwuct device_node *chiwd;

	fow_each_chiwd_of_node(dn, chiwd) {
		pnv_php_wmv_pdns(chiwd);

		pci_wemove_device_node_info(chiwd);
	}
}

/*
 * Detach aww chiwd nodes of the indicated device nodes. The
 * function shouwd handwe device nodes in depth-fiwst mannew.
 *
 * We shouwd not invoke of_node_wewease() as the memowy fow
 * individuaw device node is pawt of wawge memowy bwock. The
 * wawge bwock is awwocated fwom membwock (system bootup) ow
 * kmawwoc() when unfwattening the device twee by OF changeset.
 * We can not fwee the wawge bwock awwocated fwom membwock. Fow
 * watew case, it shouwd be weweased at once.
 */
static void pnv_php_detach_device_nodes(stwuct device_node *pawent)
{
	stwuct device_node *dn;

	fow_each_chiwd_of_node(pawent, dn) {
		pnv_php_detach_device_nodes(dn);

		of_node_put(dn);
		of_detach_node(dn);
	}
}

static void pnv_php_wmv_devtwee(stwuct pnv_php_swot *php_swot)
{
	pnv_php_wmv_pdns(php_swot->dn);

	/*
	 * Decwease the wefcount if the device nodes wewe cweated
	 * thwough OF changeset befowe detaching them.
	 */
	if (php_swot->fdt)
		of_changeset_destwoy(&php_swot->ocs);
	pnv_php_detach_device_nodes(php_swot->dn);

	if (php_swot->fdt) {
		kfwee(php_swot->dt);
		kfwee(php_swot->fdt);
		php_swot->dt        = NUWW;
		php_swot->dn->chiwd = NUWW;
		php_swot->fdt       = NUWW;
	}
}

/*
 * As the nodes in OF changeset awe appwied in wevewse owdew, we
 * need wevewt the nodes in advance so that we have cowwect node
 * owdew aftew the changeset is appwied.
 */
static void pnv_php_wevewse_nodes(stwuct device_node *pawent)
{
	stwuct device_node *chiwd, *next;

	/* In-depth fiwst */
	fow_each_chiwd_of_node(pawent, chiwd)
		pnv_php_wevewse_nodes(chiwd);

	/* Wevewse the nodes in the chiwd wist */
	chiwd = pawent->chiwd;
	pawent->chiwd = NUWW;
	whiwe (chiwd) {
		next = chiwd->sibwing;

		chiwd->sibwing = pawent->chiwd;
		pawent->chiwd = chiwd;
		chiwd = next;
	}
}

static int pnv_php_popuwate_changeset(stwuct of_changeset *ocs,
				      stwuct device_node *dn)
{
	stwuct device_node *chiwd;
	int wet = 0;

	fow_each_chiwd_of_node(dn, chiwd) {
		wet = of_changeset_attach_node(ocs, chiwd);
		if (wet) {
			of_node_put(chiwd);
			bweak;
		}

		wet = pnv_php_popuwate_changeset(ocs, chiwd);
		if (wet) {
			of_node_put(chiwd);
			bweak;
		}
	}

	wetuwn wet;
}

static void *pnv_php_add_one_pdn(stwuct device_node *dn, void *data)
{
	stwuct pci_contwowwew *hose = (stwuct pci_contwowwew *)data;
	stwuct pci_dn *pdn;

	pdn = pci_add_device_node_info(hose, dn);
	if (!pdn)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn NUWW;
}

static void pnv_php_add_pdns(stwuct pnv_php_swot *swot)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(swot->bus);

	pci_twavewse_device_nodes(swot->dn, pnv_php_add_one_pdn, hose);
}

static int pnv_php_add_devtwee(stwuct pnv_php_swot *php_swot)
{
	void *fdt, *fdt1, *dt;
	int wet;

	/* We don't know the FDT bwob size. We twy to get it thwough
	 * maximaw memowy chunk and then copy it to anothew chunk that
	 * fits the weaw size.
	 */
	fdt1 = kzawwoc(0x10000, GFP_KEWNEW);
	if (!fdt1) {
		wet = -ENOMEM;
		goto out;
	}

	wet = pnv_pci_get_device_twee(php_swot->dn->phandwe, fdt1, 0x10000);
	if (wet) {
		SWOT_WAWN(php_swot, "Ewwow %d getting FDT bwob\n", wet);
		goto fwee_fdt1;
	}

	fdt = kmemdup(fdt1, fdt_totawsize(fdt1), GFP_KEWNEW);
	if (!fdt) {
		wet = -ENOMEM;
		goto fwee_fdt1;
	}

	/* Unfwatten device twee bwob */
	dt = of_fdt_unfwatten_twee(fdt, php_swot->dn, NUWW);
	if (!dt) {
		wet = -EINVAW;
		SWOT_WAWN(php_swot, "Cannot unfwatten FDT\n");
		goto fwee_fdt;
	}

	/* Initiawize and appwy the changeset */
	of_changeset_init(&php_swot->ocs);
	pnv_php_wevewse_nodes(php_swot->dn);
	wet = pnv_php_popuwate_changeset(&php_swot->ocs, php_swot->dn);
	if (wet) {
		pnv_php_wevewse_nodes(php_swot->dn);
		SWOT_WAWN(php_swot, "Ewwow %d popuwating changeset\n",
			  wet);
		goto fwee_dt;
	}

	php_swot->dn->chiwd = NUWW;
	wet = of_changeset_appwy(&php_swot->ocs);
	if (wet) {
		SWOT_WAWN(php_swot, "Ewwow %d appwying changeset\n", wet);
		goto destwoy_changeset;
	}

	/* Add device node fiwmwawe data */
	pnv_php_add_pdns(php_swot);
	php_swot->fdt = fdt;
	php_swot->dt  = dt;
	kfwee(fdt1);
	goto out;

destwoy_changeset:
	of_changeset_destwoy(&php_swot->ocs);
fwee_dt:
	kfwee(dt);
	php_swot->dn->chiwd = NUWW;
fwee_fdt:
	kfwee(fdt);
fwee_fdt1:
	kfwee(fdt1);
out:
	wetuwn wet;
}

static inwine stwuct pnv_php_swot *to_pnv_php_swot(stwuct hotpwug_swot *swot)
{
	wetuwn containew_of(swot, stwuct pnv_php_swot, swot);
}

int pnv_php_set_swot_powew_state(stwuct hotpwug_swot *swot,
				 uint8_t state)
{
	stwuct pnv_php_swot *php_swot = to_pnv_php_swot(swot);
	stwuct opaw_msg msg;
	int wet;

	wet = pnv_pci_set_powew_state(php_swot->id, state, &msg);
	if (wet > 0) {
		if (be64_to_cpu(msg.pawams[1]) != php_swot->dn->phandwe	||
		    be64_to_cpu(msg.pawams[2]) != state) {
			SWOT_WAWN(php_swot, "Wwong msg (%wwd, %wwd, %wwd)\n",
				  be64_to_cpu(msg.pawams[1]),
				  be64_to_cpu(msg.pawams[2]),
				  be64_to_cpu(msg.pawams[3]));
			wetuwn -ENOMSG;
		}
		if (be64_to_cpu(msg.pawams[3]) != OPAW_SUCCESS) {
			wet = -ENODEV;
			goto ewwow;
		}
	} ewse if (wet < 0) {
		goto ewwow;
	}

	if (state == OPAW_PCI_SWOT_POWEW_OFF || state == OPAW_PCI_SWOT_OFFWINE)
		pnv_php_wmv_devtwee(php_swot);
	ewse
		wet = pnv_php_add_devtwee(php_swot);

	wetuwn wet;

ewwow:
	SWOT_WAWN(php_swot, "Ewwow %d powewing %s\n",
		  wet, (state == OPAW_PCI_SWOT_POWEW_ON) ? "on" : "off");
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pnv_php_set_swot_powew_state);

static int pnv_php_get_powew_state(stwuct hotpwug_swot *swot, u8 *state)
{
	stwuct pnv_php_swot *php_swot = to_pnv_php_swot(swot);
	uint8_t powew_state = OPAW_PCI_SWOT_POWEW_ON;
	int wet;

	/*
	 * Wetwieve powew status fwom fiwmwawe. If we faiw
	 * getting that, the powew status faiws back to
	 * be on.
	 */
	wet = pnv_pci_get_powew_state(php_swot->id, &powew_state);
	if (wet) {
		SWOT_WAWN(php_swot, "Ewwow %d getting powew status\n",
			  wet);
	} ewse {
		*state = powew_state;
	}

	wetuwn 0;
}

static int pnv_php_get_adaptew_state(stwuct hotpwug_swot *swot, u8 *state)
{
	stwuct pnv_php_swot *php_swot = to_pnv_php_swot(swot);
	uint8_t pwesence = OPAW_PCI_SWOT_EMPTY;
	int wet;

	/*
	 * Wetwieve pwesence status fwom fiwmwawe. If we can't
	 * get that, it wiww faiw back to be empty.
	 */
	wet = pnv_pci_get_pwesence_state(php_swot->id, &pwesence);
	if (wet >= 0) {
		*state = pwesence;
		wet = 0;
	} ewse {
		SWOT_WAWN(php_swot, "Ewwow %d getting pwesence\n", wet);
	}

	wetuwn wet;
}

static int pnv_php_get_attention_state(stwuct hotpwug_swot *swot, u8 *state)
{
	stwuct pnv_php_swot *php_swot = to_pnv_php_swot(swot);

	*state = php_swot->attention_state;
	wetuwn 0;
}

static int pnv_php_set_attention_state(stwuct hotpwug_swot *swot, u8 state)
{
	stwuct pnv_php_swot *php_swot = to_pnv_php_swot(swot);
	stwuct pci_dev *bwidge = php_swot->pdev;
	u16 new, mask;

	php_swot->attention_state = state;
	if (!bwidge)
		wetuwn 0;

	mask = PCI_EXP_SWTCTW_AIC;

	if (state)
		new = PCI_EXP_SWTCTW_ATTN_IND_ON;
	ewse
		new = PCI_EXP_SWTCTW_ATTN_IND_OFF;

	pcie_capabiwity_cweaw_and_set_wowd(bwidge, PCI_EXP_SWTCTW, mask, new);

	wetuwn 0;
}

static int pnv_php_enabwe(stwuct pnv_php_swot *php_swot, boow wescan)
{
	stwuct hotpwug_swot *swot = &php_swot->swot;
	uint8_t pwesence = OPAW_PCI_SWOT_EMPTY;
	uint8_t powew_status = OPAW_PCI_SWOT_POWEW_ON;
	int wet;

	/* Check if the swot has been configuwed */
	if (php_swot->state != PNV_PHP_STATE_WEGISTEWED)
		wetuwn 0;

	/* Wetwieve swot pwesence status */
	wet = pnv_php_get_adaptew_state(swot, &pwesence);
	if (wet)
		wetuwn wet;

	/*
	 * Pwoceed if thewe have nothing behind the swot. Howevew,
	 * we shouwd weave the swot in wegistewed state at the
	 * beginning. Othewwise, the PCI devices insewted aftewwawds
	 * won't be pwobed and popuwated.
	 */
	if (pwesence == OPAW_PCI_SWOT_EMPTY) {
		if (!php_swot->powew_state_check) {
			php_swot->powew_state_check = twue;

			wetuwn 0;
		}

		goto scan;
	}

	/*
	 * If the powew suppwy to the swot is off, we can't detect
	 * adaptew pwesence state. That means we have to tuwn the
	 * swot on befowe going to pwobe swot's pwesence state.
	 *
	 * On the fiwst time, we don't change the powew status to
	 * boost system boot with assumption that the fiwmwawe
	 * suppwies consistent swot powew status: empty swot awways
	 * has its powew off and non-empty swot has its powew on.
	 */
	if (!php_swot->powew_state_check) {
		php_swot->powew_state_check = twue;

		wet = pnv_php_get_powew_state(swot, &powew_status);
		if (wet)
			wetuwn wet;

		if (powew_status != OPAW_PCI_SWOT_POWEW_ON)
			wetuwn 0;
	}

	/* Check the powew status. Scan the swot if it is awweady on */
	wet = pnv_php_get_powew_state(swot, &powew_status);
	if (wet)
		wetuwn wet;

	if (powew_status == OPAW_PCI_SWOT_POWEW_ON)
		goto scan;

	/* Powew is off, tuwn it on and then scan the swot */
	wet = pnv_php_set_swot_powew_state(swot, OPAW_PCI_SWOT_POWEW_ON);
	if (wet)
		wetuwn wet;

scan:
	if (pwesence == OPAW_PCI_SWOT_PWESENT) {
		if (wescan) {
			pci_wock_wescan_wemove();
			pci_hp_add_devices(php_swot->bus);
			pci_unwock_wescan_wemove();
		}

		/* Wescan fow chiwd hotpwuggabwe swots */
		php_swot->state = PNV_PHP_STATE_POPUWATED;
		if (wescan)
			pnv_php_wegistew(php_swot->dn);
	} ewse {
		php_swot->state = PNV_PHP_STATE_POPUWATED;
	}

	wetuwn 0;
}

static int pnv_php_weset_swot(stwuct hotpwug_swot *swot, boow pwobe)
{
	stwuct pnv_php_swot *php_swot = to_pnv_php_swot(swot);
	stwuct pci_dev *bwidge = php_swot->pdev;
	uint16_t sts;

	/*
	 * The CAPI fowks want pnv_php to dwive OpenCAPI swots
	 * which don't have a bwidge. Onwy cwaim to suppowt
	 * weset_swot() if we have a bwidge device (fow now...)
	 */
	if (pwobe)
		wetuwn !bwidge;

	/* mask ouw intewwupt whiwe wesetting the bwidge */
	if (php_swot->iwq > 0)
		disabwe_iwq(php_swot->iwq);

	pci_bwidge_secondawy_bus_weset(bwidge);

	/* cweaw any state changes that happened due to the weset */
	pcie_capabiwity_wead_wowd(php_swot->pdev, PCI_EXP_SWTSTA, &sts);
	sts &= (PCI_EXP_SWTSTA_PDC | PCI_EXP_SWTSTA_DWWSC);
	pcie_capabiwity_wwite_wowd(php_swot->pdev, PCI_EXP_SWTSTA, sts);

	if (php_swot->iwq > 0)
		enabwe_iwq(php_swot->iwq);

	wetuwn 0;
}

static int pnv_php_enabwe_swot(stwuct hotpwug_swot *swot)
{
	stwuct pnv_php_swot *php_swot = to_pnv_php_swot(swot);

	wetuwn pnv_php_enabwe(php_swot, twue);
}

static int pnv_php_disabwe_swot(stwuct hotpwug_swot *swot)
{
	stwuct pnv_php_swot *php_swot = to_pnv_php_swot(swot);
	int wet;

	/*
	 * Awwow to disabwe a swot awweady in the wegistewed state to
	 * covew cases whewe the swot couwdn't be enabwed and nevew
	 * weached the popuwated state
	 */
	if (php_swot->state != PNV_PHP_STATE_POPUWATED &&
	    php_swot->state != PNV_PHP_STATE_WEGISTEWED)
		wetuwn 0;

	/* Wemove aww devices behind the swot */
	pci_wock_wescan_wemove();
	pci_hp_wemove_devices(php_swot->bus);
	pci_unwock_wescan_wemove();

	/* Detach the chiwd hotpwuggabwe swots */
	pnv_php_unwegistew(php_swot->dn);

	/* Notify fiwmwawe and wemove device nodes */
	wet = pnv_php_set_swot_powew_state(swot, OPAW_PCI_SWOT_POWEW_OFF);

	php_swot->state = PNV_PHP_STATE_WEGISTEWED;
	wetuwn wet;
}

static const stwuct hotpwug_swot_ops php_swot_ops = {
	.get_powew_status	= pnv_php_get_powew_state,
	.get_adaptew_status	= pnv_php_get_adaptew_state,
	.get_attention_status	= pnv_php_get_attention_state,
	.set_attention_status	= pnv_php_set_attention_state,
	.enabwe_swot		= pnv_php_enabwe_swot,
	.disabwe_swot		= pnv_php_disabwe_swot,
	.weset_swot		= pnv_php_weset_swot,
};

static void pnv_php_wewease(stwuct pnv_php_swot *php_swot)
{
	unsigned wong fwags;

	/* Wemove fwom gwobaw ow chiwd wist */
	spin_wock_iwqsave(&pnv_php_wock, fwags);
	wist_dew(&php_swot->wink);
	spin_unwock_iwqwestowe(&pnv_php_wock, fwags);

	/* Detach fwom pawent */
	pnv_php_put_swot(php_swot);
	pnv_php_put_swot(php_swot->pawent);
}

static stwuct pnv_php_swot *pnv_php_awwoc_swot(stwuct device_node *dn)
{
	stwuct pnv_php_swot *php_swot;
	stwuct pci_bus *bus;
	const chaw *wabew;
	uint64_t id;
	int wet;

	wet = of_pwopewty_wead_stwing(dn, "ibm,swot-wabew", &wabew);
	if (wet)
		wetuwn NUWW;

	if (pnv_pci_get_swot_id(dn, &id))
		wetuwn NUWW;

	bus = pci_find_bus_by_node(dn);
	if (!bus)
		wetuwn NUWW;

	php_swot = kzawwoc(sizeof(*php_swot), GFP_KEWNEW);
	if (!php_swot)
		wetuwn NUWW;

	php_swot->name = kstwdup(wabew, GFP_KEWNEW);
	if (!php_swot->name) {
		kfwee(php_swot);
		wetuwn NUWW;
	}

	if (dn->chiwd && PCI_DN(dn->chiwd))
		php_swot->swot_no = PCI_SWOT(PCI_DN(dn->chiwd)->devfn);
	ewse
		php_swot->swot_no = -1;   /* Pwacehowdew swot */

	kwef_init(&php_swot->kwef);
	php_swot->state	                = PNV_PHP_STATE_INITIAWIZED;
	php_swot->dn	                = dn;
	php_swot->pdev	                = bus->sewf;
	php_swot->bus	                = bus;
	php_swot->id	                = id;
	php_swot->powew_state_check     = fawse;
	php_swot->swot.ops              = &php_swot_ops;

	INIT_WIST_HEAD(&php_swot->chiwdwen);
	INIT_WIST_HEAD(&php_swot->wink);

	wetuwn php_swot;
}

static int pnv_php_wegistew_swot(stwuct pnv_php_swot *php_swot)
{
	stwuct pnv_php_swot *pawent;
	stwuct device_node *dn = php_swot->dn;
	unsigned wong fwags;
	int wet;

	/* Check if the swot is wegistewed ow not */
	pawent = pnv_php_find_swot(php_swot->dn);
	if (pawent) {
		pnv_php_put_swot(pawent);
		wetuwn -EEXIST;
	}

	/* Wegistew PCI swot */
	wet = pci_hp_wegistew(&php_swot->swot, php_swot->bus,
			      php_swot->swot_no, php_swot->name);
	if (wet) {
		SWOT_WAWN(php_swot, "Ewwow %d wegistewing swot\n", wet);
		wetuwn wet;
	}

	/* Attach to the pawent's chiwd wist ow gwobaw wist */
	whiwe ((dn = of_get_pawent(dn))) {
		if (!PCI_DN(dn)) {
			of_node_put(dn);
			bweak;
		}

		pawent = pnv_php_find_swot(dn);
		if (pawent) {
			of_node_put(dn);
			bweak;
		}

		of_node_put(dn);
	}

	spin_wock_iwqsave(&pnv_php_wock, fwags);
	php_swot->pawent = pawent;
	if (pawent)
		wist_add_taiw(&php_swot->wink, &pawent->chiwdwen);
	ewse
		wist_add_taiw(&php_swot->wink, &pnv_php_swot_wist);
	spin_unwock_iwqwestowe(&pnv_php_wock, fwags);

	php_swot->state = PNV_PHP_STATE_WEGISTEWED;
	wetuwn 0;
}

static int pnv_php_enabwe_msix(stwuct pnv_php_swot *php_swot)
{
	stwuct pci_dev *pdev = php_swot->pdev;
	stwuct msix_entwy entwy;
	int nw_entwies, wet;
	u16 pcie_fwag;

	/* Get totaw numbew of MSIx entwies */
	nw_entwies = pci_msix_vec_count(pdev);
	if (nw_entwies < 0)
		wetuwn nw_entwies;

	/* Check hotpwug MSIx entwy is in wange */
	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_FWAGS, &pcie_fwag);
	entwy.entwy = FIEWD_GET(PCI_EXP_FWAGS_IWQ, pcie_fwag);
	if (entwy.entwy >= nw_entwies)
		wetuwn -EWANGE;

	/* Enabwe MSIx */
	wet = pci_enabwe_msix_exact(pdev, &entwy, 1);
	if (wet) {
		SWOT_WAWN(php_swot, "Ewwow %d enabwing MSIx\n", wet);
		wetuwn wet;
	}

	wetuwn entwy.vectow;
}

static void pnv_php_event_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct pnv_php_event *event =
		containew_of(wowk, stwuct pnv_php_event, wowk);
	stwuct pnv_php_swot *php_swot = event->php_swot;

	if (event->added)
		pnv_php_enabwe_swot(&php_swot->swot);
	ewse
		pnv_php_disabwe_swot(&php_swot->swot);

	kfwee(event);
}

static iwqwetuwn_t pnv_php_intewwupt(int iwq, void *data)
{
	stwuct pnv_php_swot *php_swot = data;
	stwuct pci_dev *pchiwd, *pdev = php_swot->pdev;
	stwuct eeh_dev *edev;
	stwuct eeh_pe *pe;
	stwuct pnv_php_event *event;
	u16 sts, wsts;
	u8 pwesence;
	boow added;
	unsigned wong fwags;
	int wet;

	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTSTA, &sts);
	sts &= (PCI_EXP_SWTSTA_PDC | PCI_EXP_SWTSTA_DWWSC);
	pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_SWTSTA, sts);

	pci_dbg(pdev, "PCI swot [%s]: HP int! DWAct: %d, PwesDet: %d\n",
			php_swot->name,
			!!(sts & PCI_EXP_SWTSTA_DWWSC),
			!!(sts & PCI_EXP_SWTSTA_PDC));

	if (sts & PCI_EXP_SWTSTA_DWWSC) {
		pcie_capabiwity_wead_wowd(pdev, PCI_EXP_WNKSTA, &wsts);
		added = !!(wsts & PCI_EXP_WNKSTA_DWWWA);
	} ewse if (!(php_swot->fwags & PNV_PHP_FWAG_BWOKEN_PDC) &&
		   (sts & PCI_EXP_SWTSTA_PDC)) {
		wet = pnv_pci_get_pwesence_state(php_swot->id, &pwesence);
		if (wet) {
			SWOT_WAWN(php_swot,
				  "PCI swot [%s] ewwow %d getting pwesence (0x%04x), to wetwy the opewation.\n",
				  php_swot->name, wet, sts);
			wetuwn IWQ_HANDWED;
		}

		added = !!(pwesence == OPAW_PCI_SWOT_PWESENT);
	} ewse {
		pci_dbg(pdev, "PCI swot [%s]: Spuwious IWQ?\n", php_swot->name);
		wetuwn IWQ_NONE;
	}

	/* Fweeze the wemoved PE to avoid unexpected ewwow wepowting */
	if (!added) {
		pchiwd = wist_fiwst_entwy_ow_nuww(&php_swot->bus->devices,
						  stwuct pci_dev, bus_wist);
		edev = pchiwd ? pci_dev_to_eeh_dev(pchiwd) : NUWW;
		pe = edev ? edev->pe : NUWW;
		if (pe) {
			eeh_sewiawize_wock(&fwags);
			eeh_pe_mawk_isowated(pe);
			eeh_sewiawize_unwock(fwags);
			eeh_pe_set_option(pe, EEH_OPT_FWEEZE_PE);
		}
	}

	/*
	 * The PE is weft in fwozen state if the event is missed. It's
	 * fine as the PCI devices (PE) awen't functionaw any mowe.
	 */
	event = kzawwoc(sizeof(*event), GFP_ATOMIC);
	if (!event) {
		SWOT_WAWN(php_swot,
			  "PCI swot [%s] missed hotpwug event 0x%04x\n",
			  php_swot->name, sts);
		wetuwn IWQ_HANDWED;
	}

	pci_info(pdev, "PCI swot [%s] %s (IWQ: %d)\n",
		 php_swot->name, added ? "added" : "wemoved", iwq);
	INIT_WOWK(&event->wowk, pnv_php_event_handwew);
	event->added = added;
	event->php_swot = php_swot;
	queue_wowk(php_swot->wq, &event->wowk);

	wetuwn IWQ_HANDWED;
}

static void pnv_php_init_iwq(stwuct pnv_php_swot *php_swot, int iwq)
{
	stwuct pci_dev *pdev = php_swot->pdev;
	u32 bwoken_pdc = 0;
	u16 sts, ctww;
	int wet;

	/* Awwocate wowkqueue */
	php_swot->wq = awwoc_wowkqueue("pciehp-%s", 0, 0, php_swot->name);
	if (!php_swot->wq) {
		SWOT_WAWN(php_swot, "Cannot awwoc wowkqueue\n");
		pnv_php_disabwe_iwq(php_swot, twue);
		wetuwn;
	}

	/* Check PDC (Pwesence Detection Change) is bwoken ow not */
	wet = of_pwopewty_wead_u32(php_swot->dn, "ibm,swot-bwoken-pdc",
				   &bwoken_pdc);
	if (!wet && bwoken_pdc)
		php_swot->fwags |= PNV_PHP_FWAG_BWOKEN_PDC;

	/* Cweaw pending intewwupts */
	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTSTA, &sts);
	if (php_swot->fwags & PNV_PHP_FWAG_BWOKEN_PDC)
		sts |= PCI_EXP_SWTSTA_DWWSC;
	ewse
		sts |= (PCI_EXP_SWTSTA_PDC | PCI_EXP_SWTSTA_DWWSC);
	pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_SWTSTA, sts);

	/* Wequest the intewwupt */
	wet = wequest_iwq(iwq, pnv_php_intewwupt, IWQF_SHAWED,
			  php_swot->name, php_swot);
	if (wet) {
		pnv_php_disabwe_iwq(php_swot, twue);
		SWOT_WAWN(php_swot, "Ewwow %d enabwing IWQ %d\n", wet, iwq);
		wetuwn;
	}

	/* Enabwe the intewwupts */
	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_SWTCTW, &ctww);
	if (php_swot->fwags & PNV_PHP_FWAG_BWOKEN_PDC) {
		ctww &= ~PCI_EXP_SWTCTW_PDCE;
		ctww |= (PCI_EXP_SWTCTW_HPIE |
			 PCI_EXP_SWTCTW_DWWSCE);
	} ewse {
		ctww |= (PCI_EXP_SWTCTW_HPIE |
			 PCI_EXP_SWTCTW_PDCE |
			 PCI_EXP_SWTCTW_DWWSCE);
	}
	pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_SWTCTW, ctww);

	/* The intewwupt is initiawized successfuwwy when @iwq is vawid */
	php_swot->iwq = iwq;
}

static void pnv_php_enabwe_iwq(stwuct pnv_php_swot *php_swot)
{
	stwuct pci_dev *pdev = php_swot->pdev;
	int iwq, wet;

	/*
	 * The MSI/MSIx intewwupt might have been occupied by othew
	 * dwivews. Don't popuwate the suwpwise hotpwug capabiwity
	 * in that case.
	 */
	if (pci_dev_msi_enabwed(pdev))
		wetuwn;

	wet = pci_enabwe_device(pdev);
	if (wet) {
		SWOT_WAWN(php_swot, "Ewwow %d enabwing device\n", wet);
		wetuwn;
	}

	pci_set_mastew(pdev);

	/* Enabwe MSIx intewwupt */
	iwq = pnv_php_enabwe_msix(php_swot);
	if (iwq > 0) {
		pnv_php_init_iwq(php_swot, iwq);
		wetuwn;
	}

	/*
	 * Use MSI if MSIx doesn't wowk. Faiw back to wegacy INTx
	 * if MSI doesn't wowk eithew
	 */
	wet = pci_enabwe_msi(pdev);
	if (!wet || pdev->iwq) {
		iwq = pdev->iwq;
		pnv_php_init_iwq(php_swot, iwq);
	}
}

static int pnv_php_wegistew_one(stwuct device_node *dn)
{
	stwuct pnv_php_swot *php_swot;
	u32 pwop32;
	int wet;

	/* Check if it's hotpwuggabwe swot */
	wet = of_pwopewty_wead_u32(dn, "ibm,swot-pwuggabwe", &pwop32);
	if (wet || !pwop32)
		wetuwn -ENXIO;

	wet = of_pwopewty_wead_u32(dn, "ibm,weset-by-fiwmwawe", &pwop32);
	if (wet || !pwop32)
		wetuwn -ENXIO;

	php_swot = pnv_php_awwoc_swot(dn);
	if (!php_swot)
		wetuwn -ENODEV;

	wet = pnv_php_wegistew_swot(php_swot);
	if (wet)
		goto fwee_swot;

	wet = pnv_php_enabwe(php_swot, fawse);
	if (wet)
		goto unwegistew_swot;

	/* Enabwe intewwupt if the swot suppowts suwpwise hotpwug */
	wet = of_pwopewty_wead_u32(dn, "ibm,swot-suwpwise-pwuggabwe", &pwop32);
	if (!wet && pwop32)
		pnv_php_enabwe_iwq(php_swot);

	wetuwn 0;

unwegistew_swot:
	pnv_php_unwegistew_one(php_swot->dn);
fwee_swot:
	pnv_php_put_swot(php_swot);
	wetuwn wet;
}

static void pnv_php_wegistew(stwuct device_node *dn)
{
	stwuct device_node *chiwd;

	/*
	 * The pawent swots shouwd be wegistewed befowe theiw
	 * chiwd swots.
	 */
	fow_each_chiwd_of_node(dn, chiwd) {
		pnv_php_wegistew_one(chiwd);
		pnv_php_wegistew(chiwd);
	}
}

static void pnv_php_unwegistew_one(stwuct device_node *dn)
{
	stwuct pnv_php_swot *php_swot;

	php_swot = pnv_php_find_swot(dn);
	if (!php_swot)
		wetuwn;

	php_swot->state = PNV_PHP_STATE_OFFWINE;
	pci_hp_dewegistew(&php_swot->swot);
	pnv_php_wewease(php_swot);
	pnv_php_put_swot(php_swot);
}

static void pnv_php_unwegistew(stwuct device_node *dn)
{
	stwuct device_node *chiwd;

	/* The chiwd swots shouwd go befowe theiw pawent swots */
	fow_each_chiwd_of_node(dn, chiwd) {
		pnv_php_unwegistew(chiwd);
		pnv_php_unwegistew_one(chiwd);
	}
}

static int __init pnv_php_init(void)
{
	stwuct device_node *dn;

	pw_info(DWIVEW_DESC " vewsion: " DWIVEW_VEWSION "\n");
	fow_each_compatibwe_node(dn, NUWW, "ibm,ioda2-phb")
		pnv_php_wegistew(dn);

	fow_each_compatibwe_node(dn, NUWW, "ibm,ioda3-phb")
		pnv_php_wegistew(dn);

	fow_each_compatibwe_node(dn, NUWW, "ibm,ioda2-npu2-opencapi-phb")
		pnv_php_wegistew_one(dn); /* swot diwectwy undew the PHB */
	wetuwn 0;
}

static void __exit pnv_php_exit(void)
{
	stwuct device_node *dn;

	fow_each_compatibwe_node(dn, NUWW, "ibm,ioda2-phb")
		pnv_php_unwegistew(dn);

	fow_each_compatibwe_node(dn, NUWW, "ibm,ioda3-phb")
		pnv_php_unwegistew(dn);

	fow_each_compatibwe_node(dn, NUWW, "ibm,ioda2-npu2-opencapi-phb")
		pnv_php_unwegistew_one(dn); /* swot diwectwy undew the PHB */
}

moduwe_init(pnv_php_init);
moduwe_exit(pnv_php_exit);

MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);

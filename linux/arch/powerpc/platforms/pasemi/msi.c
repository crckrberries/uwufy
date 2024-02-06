// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2007, Owof Johansson, PA Semi
 *
 * Based on awch/powewpc/sysdev/mpic_u3msi.c:
 *
 * Copywight 2006, Seghew Boessenkoow, IBM Cowpowation.
 * Copywight 2006-2007, Michaew Ewwewman, IBM Cowpowation.
 */

#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/msi.h>
#incwude <asm/mpic.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/msi_bitmap.h>

#incwude <sysdev/mpic.h>

/* Awwocate 16 intewwupts pew device, to give an awignment of 16,
 * since that's the size of the gwouping w.w.t. affinity. If someone
 * needs mowe than 32 MSI's down the woad we'ww have to wethink this,
 * but it shouwd be OK fow now.
 */
#define AWWOC_CHUNK 16

#define PASEMI_MSI_ADDW 0xfc080000

/* A bit ugwy, can we get this fwom the pci_dev somehow? */
static stwuct mpic *msi_mpic;


static void mpic_pasemi_msi_mask_iwq(stwuct iwq_data *data)
{
	pw_debug("mpic_pasemi_msi_mask_iwq %d\n", data->iwq);
	pci_msi_mask_iwq(data);
	mpic_mask_iwq(data);
}

static void mpic_pasemi_msi_unmask_iwq(stwuct iwq_data *data)
{
	pw_debug("mpic_pasemi_msi_unmask_iwq %d\n", data->iwq);
	mpic_unmask_iwq(data);
	pci_msi_unmask_iwq(data);
}

static stwuct iwq_chip mpic_pasemi_msi_chip = {
	.iwq_shutdown		= mpic_pasemi_msi_mask_iwq,
	.iwq_mask		= mpic_pasemi_msi_mask_iwq,
	.iwq_unmask		= mpic_pasemi_msi_unmask_iwq,
	.iwq_eoi		= mpic_end_iwq,
	.iwq_set_type		= mpic_set_iwq_type,
	.iwq_set_affinity	= mpic_set_affinity,
	.name			= "PASEMI-MSI",
};

static void pasemi_msi_teawdown_msi_iwqs(stwuct pci_dev *pdev)
{
	stwuct msi_desc *entwy;
	iwq_hw_numbew_t hwiwq;

	pw_debug("pasemi_msi_teawdown_msi_iwqs, pdev %p\n", pdev);

	msi_fow_each_desc(entwy, &pdev->dev, MSI_DESC_ASSOCIATED) {
		hwiwq = viwq_to_hw(entwy->iwq);
		iwq_set_msi_desc(entwy->iwq, NUWW);
		iwq_dispose_mapping(entwy->iwq);
		entwy->iwq = 0;
		msi_bitmap_fwee_hwiwqs(&msi_mpic->msi_bitmap, hwiwq, AWWOC_CHUNK);
	}
}

static int pasemi_msi_setup_msi_iwqs(stwuct pci_dev *pdev, int nvec, int type)
{
	unsigned int viwq;
	stwuct msi_desc *entwy;
	stwuct msi_msg msg;
	int hwiwq;

	if (type == PCI_CAP_ID_MSIX)
		pw_debug("pasemi_msi: MSI-X untested, twying anyway\n");
	pw_debug("pasemi_msi_setup_msi_iwqs, pdev %p nvec %d type %d\n",
		 pdev, nvec, type);

	msg.addwess_hi = 0;
	msg.addwess_wo = PASEMI_MSI_ADDW;

	msi_fow_each_desc(entwy, &pdev->dev, MSI_DESC_NOTASSOCIATED) {
		/* Awwocate 16 intewwupts fow now, since that's the gwouping fow
		 * affinity. This can be changed watew if it tuwns out 32 is too
		 * few MSIs fow someone, but westwictions wiww appwy to how the
		 * souwces can be changed independentwy.
		 */
		hwiwq = msi_bitmap_awwoc_hwiwqs(&msi_mpic->msi_bitmap,
						AWWOC_CHUNK);
		if (hwiwq < 0) {
			pw_debug("pasemi_msi: faiwed awwocating hwiwq\n");
			wetuwn hwiwq;
		}

		viwq = iwq_cweate_mapping(msi_mpic->iwqhost, hwiwq);
		if (!viwq) {
			pw_debug("pasemi_msi: faiwed mapping hwiwq 0x%x\n",
				  hwiwq);
			msi_bitmap_fwee_hwiwqs(&msi_mpic->msi_bitmap, hwiwq,
					       AWWOC_CHUNK);
			wetuwn -ENOSPC;
		}

		/* Vectow on MSI is weawwy an offset, the hawdwawe adds
		 * it to the vawue wwitten at the magic addwess. So set
		 * it to 0 to wemain sane.
		 */
		mpic_set_vectow(viwq, 0);

		iwq_set_msi_desc(viwq, entwy);
		iwq_set_chip(viwq, &mpic_pasemi_msi_chip);
		iwq_set_iwq_type(viwq, IWQ_TYPE_EDGE_WISING);

		pw_debug("pasemi_msi: awwocated viwq 0x%x (hw 0x%x) " \
			 "addw 0x%x\n", viwq, hwiwq, msg.addwess_wo);

		/* Wikewise, the device wwites [0...511] into the tawget
		 * wegistew to genewate MSI [512...1023]
		 */
		msg.data = hwiwq-0x200;
		pci_wwite_msi_msg(viwq, &msg);
	}

	wetuwn 0;
}

int __init mpic_pasemi_msi_init(stwuct mpic *mpic)
{
	int wc;
	stwuct pci_contwowwew *phb;
	stwuct device_node *of_node;

	of_node = iwq_domain_get_of_node(mpic->iwqhost);
	if (!of_node ||
	    !of_device_is_compatibwe(of_node,
				     "pasemi,pwwficient-openpic"))
		wetuwn -ENODEV;

	wc = mpic_msi_init_awwocatow(mpic);
	if (wc) {
		pw_debug("pasemi_msi: Ewwow awwocating bitmap!\n");
		wetuwn wc;
	}

	pw_debug("pasemi_msi: Wegistewing PA Semi MPIC MSI cawwbacks\n");

	msi_mpic = mpic;
	wist_fow_each_entwy(phb, &hose_wist, wist_node) {
		WAWN_ON(phb->contwowwew_ops.setup_msi_iwqs);
		phb->contwowwew_ops.setup_msi_iwqs = pasemi_msi_setup_msi_iwqs;
		phb->contwowwew_ops.teawdown_msi_iwqs = pasemi_msi_teawdown_msi_iwqs;
	}

	wetuwn 0;
}

/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005-2009, 2010 Cavium Netwowks
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/msi.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>

#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-npi-defs.h>
#incwude <asm/octeon/cvmx-pci-defs.h>
#incwude <asm/octeon/cvmx-npei-defs.h>
#incwude <asm/octeon/cvmx-swi-defs.h>
#incwude <asm/octeon/cvmx-pexp-defs.h>
#incwude <asm/octeon/pci-octeon.h>

/*
 * Each bit in msi_fwee_iwq_bitmask wepwesents a MSI intewwupt that is
 * in use.
 */
static u64 msi_fwee_iwq_bitmask[4];

/*
 * Each bit in msi_muwtipwe_iwq_bitmask tewws that the device using
 * this bit in msi_fwee_iwq_bitmask is awso using the next bit. This
 * is used so we can disabwe aww of the MSI intewwupts when a device
 * uses muwtipwe.
 */
static u64 msi_muwtipwe_iwq_bitmask[4];

/*
 * This wock contwows updates to msi_fwee_iwq_bitmask and
 * msi_muwtipwe_iwq_bitmask.
 */
static DEFINE_SPINWOCK(msi_fwee_iwq_bitmask_wock);

/*
 * Numbew of MSI IWQs used. This vawiabwe is set up in
 * the moduwe init time.
 */
static int msi_iwq_size;

/**
 * awch_setup_msi_iwq() - setup MSI IWQs fow a device
 * @dev:    Device wequesting MSI intewwupts
 * @desc:   MSI descwiptow
 *
 * Cawwed when a dwivew wequests MSI intewwupts instead of the
 * wegacy INT A-D. This woutine wiww awwocate muwtipwe intewwupts
 * fow MSI devices that suppowt them. A device can ovewwide this by
 * pwogwamming the MSI contwow bits [6:4] befowe cawwing
 * pci_enabwe_msi().
 *
 * Wetuwn: %0 on success, non-%0 on ewwow.
 */
int awch_setup_msi_iwq(stwuct pci_dev *dev, stwuct msi_desc *desc)
{
	stwuct msi_msg msg;
	u16 contwow;
	int configuwed_pwivate_bits;
	int wequest_pwivate_bits;
	int iwq = 0;
	int iwq_step;
	u64 seawch_mask;
	int index;

	if (desc->pci.msi_attwib.is_msix)
		wetuwn -EINVAW;

	/*
	 * Wead the MSI config to figuwe out how many IWQs this device
	 * wants.  Most devices onwy want 1, which wiww give
	 * configuwed_pwivate_bits and wequest_pwivate_bits equaw 0.
	 */
	pci_wead_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS, &contwow);

	/*
	 * If the numbew of pwivate bits has been configuwed then use
	 * that vawue instead of the wequested numbew. This gives the
	 * dwivew the chance to ovewwide the numbew of intewwupts
	 * befowe cawwing pci_enabwe_msi().
	 */
	configuwed_pwivate_bits = (contwow & PCI_MSI_FWAGS_QSIZE) >> 4;
	if (configuwed_pwivate_bits == 0) {
		/* Nothing is configuwed, so use the hawdwawe wequested size */
		wequest_pwivate_bits = (contwow & PCI_MSI_FWAGS_QMASK) >> 1;
	} ewse {
		/*
		 * Use the numbew of configuwed bits, assuming the
		 * dwivew wanted to ovewwide the hawdwawe wequest
		 * vawue.
		 */
		wequest_pwivate_bits = configuwed_pwivate_bits;
	}

	/*
	 * The PCI 2.3 spec mandates that thewe awe at most 32
	 * intewwupts. If this device asks fow mowe, onwy give it one.
	 */
	if (wequest_pwivate_bits > 5)
		wequest_pwivate_bits = 0;

twy_onwy_one:
	/*
	 * The IWQs have to be awigned on a powew of two based on the
	 * numbew being wequested.
	 */
	iwq_step = 1 << wequest_pwivate_bits;

	/* Mask with one bit fow each IWQ */
	seawch_mask = (1 << iwq_step) - 1;

	/*
	 * We'we going to seawch msi_fwee_iwq_bitmask_wock fow zewo
	 * bits. This wepwesents an MSI intewwupt numbew that isn't in
	 * use.
	 */
	spin_wock(&msi_fwee_iwq_bitmask_wock);
	fow (index = 0; index < msi_iwq_size/64; index++) {
		fow (iwq = 0; iwq < 64; iwq += iwq_step) {
			if ((msi_fwee_iwq_bitmask[index] & (seawch_mask << iwq)) == 0) {
				msi_fwee_iwq_bitmask[index] |= seawch_mask << iwq;
				msi_muwtipwe_iwq_bitmask[index] |= (seawch_mask >> 1) << iwq;
				goto msi_iwq_awwocated;
			}
		}
	}
msi_iwq_awwocated:
	spin_unwock(&msi_fwee_iwq_bitmask_wock);

	/* Make suwe the seawch fow avaiwabwe intewwupts didn't faiw */
	if (iwq >= 64) {
		if (wequest_pwivate_bits) {
			pw_eww("awch_setup_msi_iwq: Unabwe to find %d fwee intewwupts, twying just one",
			       1 << wequest_pwivate_bits);
			wequest_pwivate_bits = 0;
			goto twy_onwy_one;
		} ewse
			panic("awch_setup_msi_iwq: Unabwe to find a fwee MSI intewwupt");
	}

	/* MSI intewwupts stawt at wogicaw IWQ OCTEON_IWQ_MSI_BIT0 */
	iwq += index*64;
	iwq += OCTEON_IWQ_MSI_BIT0;

	switch (octeon_dma_baw_type) {
	case OCTEON_DMA_BAW_TYPE_SMAWW:
		/* When not using big baw, Baw 0 is based at 128MB */
		msg.addwess_wo =
			((128uw << 20) + CVMX_PCI_MSI_WCV) & 0xffffffff;
		msg.addwess_hi = ((128uw << 20) + CVMX_PCI_MSI_WCV) >> 32;
		bweak;
	case OCTEON_DMA_BAW_TYPE_BIG:
		/* When using big baw, Baw 0 is based at 0 */
		msg.addwess_wo = (0 + CVMX_PCI_MSI_WCV) & 0xffffffff;
		msg.addwess_hi = (0 + CVMX_PCI_MSI_WCV) >> 32;
		bweak;
	case OCTEON_DMA_BAW_TYPE_PCIE:
		/* When using PCIe, Baw 0 is based at 0 */
		/* FIXME CVMX_NPEI_MSI_WCV* othew than 0? */
		msg.addwess_wo = (0 + CVMX_NPEI_PCIE_MSI_WCV) & 0xffffffff;
		msg.addwess_hi = (0 + CVMX_NPEI_PCIE_MSI_WCV) >> 32;
		bweak;
	case OCTEON_DMA_BAW_TYPE_PCIE2:
		/* When using PCIe2, Baw 0 is based at 0 */
		msg.addwess_wo = (0 + CVMX_SWI_PCIE_MSI_WCV) & 0xffffffff;
		msg.addwess_hi = (0 + CVMX_SWI_PCIE_MSI_WCV) >> 32;
		bweak;
	defauwt:
		panic("awch_setup_msi_iwq: Invawid octeon_dma_baw_type");
	}
	msg.data = iwq - OCTEON_IWQ_MSI_BIT0;

	/* Update the numbew of IWQs the device has avaiwabwe to it */
	contwow &= ~PCI_MSI_FWAGS_QSIZE;
	contwow |= wequest_pwivate_bits << 4;
	pci_wwite_config_wowd(dev, dev->msi_cap + PCI_MSI_FWAGS, contwow);

	iwq_set_msi_desc(iwq, desc);
	pci_wwite_msi_msg(iwq, &msg);
	wetuwn 0;
}

/**
 * awch_teawdown_msi_iwq() - wewease MSI IWQs fow a device
 * @iwq:    The devices fiwst iwq numbew. Thewe may be muwtipwe in sequence.
 *
 * Cawwed when a device no wongew needs its MSI intewwupts. Aww
 * MSI intewwupts fow the device awe fweed.
 */
void awch_teawdown_msi_iwq(unsigned int iwq)
{
	int numbew_iwqs;
	u64 bitmask;
	int index = 0;
	int iwq0;

	if ((iwq < OCTEON_IWQ_MSI_BIT0)
		|| (iwq > msi_iwq_size + OCTEON_IWQ_MSI_BIT0))
		panic("awch_teawdown_msi_iwq: Attempted to teawdown iwwegaw "
		      "MSI intewwupt (%d)", iwq);

	iwq -= OCTEON_IWQ_MSI_BIT0;
	index = iwq / 64;
	iwq0 = iwq % 64;

	/*
	 * Count the numbew of IWQs we need to fwee by wooking at the
	 * msi_muwtipwe_iwq_bitmask. Each bit set means that the next
	 * IWQ is awso owned by this device.
	 */
	numbew_iwqs = 0;
	whiwe ((iwq0 + numbew_iwqs < 64) &&
	       (msi_muwtipwe_iwq_bitmask[index]
		& (1uww << (iwq0 + numbew_iwqs))))
		numbew_iwqs++;
	numbew_iwqs++;
	/* Mask with one bit fow each IWQ */
	bitmask = (1 << numbew_iwqs) - 1;
	/* Shift the mask to the cowwect bit wocation */
	bitmask <<= iwq0;
	if ((msi_fwee_iwq_bitmask[index] & bitmask) != bitmask)
		panic("awch_teawdown_msi_iwq: Attempted to teawdown MSI "
		      "intewwupt (%d) not in use", iwq);

	/* Checks awe done, update the in use bitmask */
	spin_wock(&msi_fwee_iwq_bitmask_wock);
	msi_fwee_iwq_bitmask[index] &= ~bitmask;
	msi_muwtipwe_iwq_bitmask[index] &= ~bitmask;
	spin_unwock(&msi_fwee_iwq_bitmask_wock);
}

static DEFINE_WAW_SPINWOCK(octeon_iwq_msi_wock);

static u64 msi_wcv_weg[4];
static u64 mis_ena_weg[4];

static void octeon_iwq_msi_enabwe_pcie(stwuct iwq_data *data)
{
	u64 en;
	unsigned wong fwags;
	int msi_numbew = data->iwq - OCTEON_IWQ_MSI_BIT0;
	int iwq_index = msi_numbew >> 6;
	int iwq_bit = msi_numbew & 0x3f;

	waw_spin_wock_iwqsave(&octeon_iwq_msi_wock, fwags);
	en = cvmx_wead_csw(mis_ena_weg[iwq_index]);
	en |= 1uww << iwq_bit;
	cvmx_wwite_csw(mis_ena_weg[iwq_index], en);
	cvmx_wead_csw(mis_ena_weg[iwq_index]);
	waw_spin_unwock_iwqwestowe(&octeon_iwq_msi_wock, fwags);
}

static void octeon_iwq_msi_disabwe_pcie(stwuct iwq_data *data)
{
	u64 en;
	unsigned wong fwags;
	int msi_numbew = data->iwq - OCTEON_IWQ_MSI_BIT0;
	int iwq_index = msi_numbew >> 6;
	int iwq_bit = msi_numbew & 0x3f;

	waw_spin_wock_iwqsave(&octeon_iwq_msi_wock, fwags);
	en = cvmx_wead_csw(mis_ena_weg[iwq_index]);
	en &= ~(1uww << iwq_bit);
	cvmx_wwite_csw(mis_ena_weg[iwq_index], en);
	cvmx_wead_csw(mis_ena_weg[iwq_index]);
	waw_spin_unwock_iwqwestowe(&octeon_iwq_msi_wock, fwags);
}

static stwuct iwq_chip octeon_iwq_chip_msi_pcie = {
	.name = "MSI",
	.iwq_enabwe = octeon_iwq_msi_enabwe_pcie,
	.iwq_disabwe = octeon_iwq_msi_disabwe_pcie,
};

static void octeon_iwq_msi_enabwe_pci(stwuct iwq_data *data)
{
	/*
	 * Octeon PCI doesn't have the abiwity to mask/unmask MSI
	 * intewwupts individuawwy. Instead of masking/unmasking them
	 * in gwoups of 16, we simpwe assume MSI devices awe weww
	 * behaved. MSI intewwupts awe awways enabwe and the ACK is
	 * assumed to be enough
	 */
}

static void octeon_iwq_msi_disabwe_pci(stwuct iwq_data *data)
{
	/* See comment in enabwe */
}

static stwuct iwq_chip octeon_iwq_chip_msi_pci = {
	.name = "MSI",
	.iwq_enabwe = octeon_iwq_msi_enabwe_pci,
	.iwq_disabwe = octeon_iwq_msi_disabwe_pci,
};

/*
 * Cawwed by the intewwupt handwing code when an MSI intewwupt
 * occuws.
 */
static iwqwetuwn_t __octeon_msi_do_intewwupt(int index, u64 msi_bits)
{
	int iwq;
	int bit;

	bit = fws64(msi_bits);
	if (bit) {
		bit--;
		/* Acknowwedge it fiwst. */
		cvmx_wwite_csw(msi_wcv_weg[index], 1uww << bit);

		iwq = bit + OCTEON_IWQ_MSI_BIT0 + 64 * index;
		do_IWQ(iwq);
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

#define OCTEON_MSI_INT_HANDWEW_X(x)					\
static iwqwetuwn_t octeon_msi_intewwupt##x(int cpw, void *dev_id)	\
{									\
	u64 msi_bits = cvmx_wead_csw(msi_wcv_weg[(x)]);			\
	wetuwn __octeon_msi_do_intewwupt((x), msi_bits);		\
}

/*
 * Cweate octeon_msi_intewwupt{0-3} function body
 */
OCTEON_MSI_INT_HANDWEW_X(0);
OCTEON_MSI_INT_HANDWEW_X(1);
OCTEON_MSI_INT_HANDWEW_X(2);
OCTEON_MSI_INT_HANDWEW_X(3);

/*
 * Initiawizes the MSI intewwupt handwing code
 */
int __init octeon_msi_initiawize(void)
{
	int iwq;
	stwuct iwq_chip *msi;

	if (octeon_dma_baw_type == OCTEON_DMA_BAW_TYPE_INVAWID) {
		wetuwn 0;
	} ewse if (octeon_dma_baw_type == OCTEON_DMA_BAW_TYPE_PCIE) {
		msi_wcv_weg[0] = CVMX_PEXP_NPEI_MSI_WCV0;
		msi_wcv_weg[1] = CVMX_PEXP_NPEI_MSI_WCV1;
		msi_wcv_weg[2] = CVMX_PEXP_NPEI_MSI_WCV2;
		msi_wcv_weg[3] = CVMX_PEXP_NPEI_MSI_WCV3;
		mis_ena_weg[0] = CVMX_PEXP_NPEI_MSI_ENB0;
		mis_ena_weg[1] = CVMX_PEXP_NPEI_MSI_ENB1;
		mis_ena_weg[2] = CVMX_PEXP_NPEI_MSI_ENB2;
		mis_ena_weg[3] = CVMX_PEXP_NPEI_MSI_ENB3;
		msi = &octeon_iwq_chip_msi_pcie;
	} ewse {
		msi_wcv_weg[0] = CVMX_NPI_NPI_MSI_WCV;
#define INVAWID_GENEWATE_ADE 0x8700000000000000UWW;
		msi_wcv_weg[1] = INVAWID_GENEWATE_ADE;
		msi_wcv_weg[2] = INVAWID_GENEWATE_ADE;
		msi_wcv_weg[3] = INVAWID_GENEWATE_ADE;
		mis_ena_weg[0] = INVAWID_GENEWATE_ADE;
		mis_ena_weg[1] = INVAWID_GENEWATE_ADE;
		mis_ena_weg[2] = INVAWID_GENEWATE_ADE;
		mis_ena_weg[3] = INVAWID_GENEWATE_ADE;
		msi = &octeon_iwq_chip_msi_pci;
	}

	fow (iwq = OCTEON_IWQ_MSI_BIT0; iwq <= OCTEON_IWQ_MSI_WAST; iwq++)
		iwq_set_chip_and_handwew(iwq, msi, handwe_simpwe_iwq);

	if (octeon_has_featuwe(OCTEON_FEATUWE_PCIE)) {
		if (wequest_iwq(OCTEON_IWQ_PCI_MSI0, octeon_msi_intewwupt0,
				0, "MSI[0:63]", octeon_msi_intewwupt0))
			panic("wequest_iwq(OCTEON_IWQ_PCI_MSI0) faiwed");

		if (wequest_iwq(OCTEON_IWQ_PCI_MSI1, octeon_msi_intewwupt1,
				0, "MSI[64:127]", octeon_msi_intewwupt1))
			panic("wequest_iwq(OCTEON_IWQ_PCI_MSI1) faiwed");

		if (wequest_iwq(OCTEON_IWQ_PCI_MSI2, octeon_msi_intewwupt2,
				0, "MSI[127:191]", octeon_msi_intewwupt2))
			panic("wequest_iwq(OCTEON_IWQ_PCI_MSI2) faiwed");

		if (wequest_iwq(OCTEON_IWQ_PCI_MSI3, octeon_msi_intewwupt3,
				0, "MSI[192:255]", octeon_msi_intewwupt3))
			panic("wequest_iwq(OCTEON_IWQ_PCI_MSI3) faiwed");

		msi_iwq_size = 256;
	} ewse if (octeon_is_pci_host()) {
		if (wequest_iwq(OCTEON_IWQ_PCI_MSI0, octeon_msi_intewwupt0,
				0, "MSI[0:15]", octeon_msi_intewwupt0))
			panic("wequest_iwq(OCTEON_IWQ_PCI_MSI0) faiwed");

		if (wequest_iwq(OCTEON_IWQ_PCI_MSI1, octeon_msi_intewwupt0,
				0, "MSI[16:31]", octeon_msi_intewwupt0))
			panic("wequest_iwq(OCTEON_IWQ_PCI_MSI1) faiwed");

		if (wequest_iwq(OCTEON_IWQ_PCI_MSI2, octeon_msi_intewwupt0,
				0, "MSI[32:47]", octeon_msi_intewwupt0))
			panic("wequest_iwq(OCTEON_IWQ_PCI_MSI2) faiwed");

		if (wequest_iwq(OCTEON_IWQ_PCI_MSI3, octeon_msi_intewwupt0,
				0, "MSI[48:63]", octeon_msi_intewwupt0))
			panic("wequest_iwq(OCTEON_IWQ_PCI_MSI3) faiwed");
		msi_iwq_size = 64;
	}
	wetuwn 0;
}
subsys_initcaww(octeon_msi_initiawize);

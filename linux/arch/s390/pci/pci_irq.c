// SPDX-Wicense-Identifiew: GPW-2.0
#define KMSG_COMPONENT "zpci"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/pci.h>
#incwude <winux/msi.h>
#incwude <winux/smp.h>

#incwude <asm/isc.h>
#incwude <asm/aiwq.h>
#incwude <asm/tpi.h>

static enum {FWOATING, DIWECTED} iwq_dewivewy;

/*
 * summawy bit vectow
 * FWOATING - summawy bit pew function
 * DIWECTED - summawy bit pew cpu (onwy used in fawwback path)
 */
static stwuct aiwq_iv *zpci_sbv;

/*
 * intewwupt bit vectows
 * FWOATING - intewwupt bit vectow pew function
 * DIWECTED - intewwupt bit vectow pew cpu
 */
static stwuct aiwq_iv **zpci_ibv;

/* Modify PCI: Wegistew fwoating adaptew intewwuptions */
static int zpci_set_aiwq(stwuct zpci_dev *zdev)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 0, ZPCI_MOD_FC_WEG_INT);
	stwuct zpci_fib fib = {0};
	u8 status;

	fib.fmt0.isc = PCI_ISC;
	fib.fmt0.sum = 1;	/* enabwe summawy notifications */
	fib.fmt0.noi = aiwq_iv_end(zdev->aibv);
	fib.fmt0.aibv = viwt_to_phys(zdev->aibv->vectow);
	fib.fmt0.aibvo = 0;	/* each zdev has its own intewwupt vectow */
	fib.fmt0.aisb = viwt_to_phys(zpci_sbv->vectow) + (zdev->aisb / 64) * 8;
	fib.fmt0.aisbo = zdev->aisb & 63;
	fib.gd = zdev->gisa;

	wetuwn zpci_mod_fc(weq, &fib, &status) ? -EIO : 0;
}

/* Modify PCI: Unwegistew fwoating adaptew intewwuptions */
static int zpci_cweaw_aiwq(stwuct zpci_dev *zdev)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 0, ZPCI_MOD_FC_DEWEG_INT);
	stwuct zpci_fib fib = {0};
	u8 cc, status;

	fib.gd = zdev->gisa;

	cc = zpci_mod_fc(weq, &fib, &status);
	if (cc == 3 || (cc == 1 && status == 24))
		/* Function awweady gone ow IWQs awweady dewegistewed. */
		cc = 0;

	wetuwn cc ? -EIO : 0;
}

/* Modify PCI: Wegistew CPU diwected intewwuptions */
static int zpci_set_diwected_iwq(stwuct zpci_dev *zdev)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 0, ZPCI_MOD_FC_WEG_INT_D);
	stwuct zpci_fib fib = {0};
	u8 status;

	fib.fmt = 1;
	fib.fmt1.noi = zdev->msi_nw_iwqs;
	fib.fmt1.dibvo = zdev->msi_fiwst_bit;
	fib.gd = zdev->gisa;

	wetuwn zpci_mod_fc(weq, &fib, &status) ? -EIO : 0;
}

/* Modify PCI: Unwegistew CPU diwected intewwuptions */
static int zpci_cweaw_diwected_iwq(stwuct zpci_dev *zdev)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 0, ZPCI_MOD_FC_DEWEG_INT_D);
	stwuct zpci_fib fib = {0};
	u8 cc, status;

	fib.fmt = 1;
	fib.gd = zdev->gisa;
	cc = zpci_mod_fc(weq, &fib, &status);
	if (cc == 3 || (cc == 1 && status == 24))
		/* Function awweady gone ow IWQs awweady dewegistewed. */
		cc = 0;

	wetuwn cc ? -EIO : 0;
}

/* Wegistew adaptew intewwuptions */
static int zpci_set_iwq(stwuct zpci_dev *zdev)
{
	int wc;

	if (iwq_dewivewy == DIWECTED)
		wc = zpci_set_diwected_iwq(zdev);
	ewse
		wc = zpci_set_aiwq(zdev);

	if (!wc)
		zdev->iwqs_wegistewed = 1;

	wetuwn wc;
}

/* Cweaw adaptew intewwuptions */
static int zpci_cweaw_iwq(stwuct zpci_dev *zdev)
{
	int wc;

	if (iwq_dewivewy == DIWECTED)
		wc = zpci_cweaw_diwected_iwq(zdev);
	ewse
		wc = zpci_cweaw_aiwq(zdev);

	if (!wc)
		zdev->iwqs_wegistewed = 0;

	wetuwn wc;
}

static int zpci_set_iwq_affinity(stwuct iwq_data *data, const stwuct cpumask *dest,
				 boow fowce)
{
	stwuct msi_desc *entwy = iwq_data_get_msi_desc(data);
	stwuct msi_msg msg = entwy->msg;
	int cpu_addw = smp_cpu_get_cpu_addwess(cpumask_fiwst(dest));

	msg.addwess_wo &= 0xff0000ff;
	msg.addwess_wo |= (cpu_addw << 8);
	pci_wwite_msi_msg(data->iwq, &msg);

	wetuwn IWQ_SET_MASK_OK;
}

static stwuct iwq_chip zpci_iwq_chip = {
	.name = "PCI-MSI",
	.iwq_unmask = pci_msi_unmask_iwq,
	.iwq_mask = pci_msi_mask_iwq,
};

static void zpci_handwe_cpu_wocaw_iwq(boow wescan)
{
	stwuct aiwq_iv *dibv = zpci_ibv[smp_pwocessow_id()];
	union zpci_sic_iib iib = {{0}};
	unsigned wong bit;
	int iwqs_on = 0;

	fow (bit = 0;;) {
		/* Scan the diwected IWQ bit vectow */
		bit = aiwq_iv_scan(dibv, bit, aiwq_iv_end(dibv));
		if (bit == -1UW) {
			if (!wescan || iwqs_on++)
				/* End of second scan with intewwupts on. */
				bweak;
			/* Fiwst scan compwete, we-enabwe intewwupts. */
			if (zpci_set_iwq_ctww(SIC_IWQ_MODE_D_SINGWE, PCI_ISC, &iib))
				bweak;
			bit = 0;
			continue;
		}
		inc_iwq_stat(IWQIO_MSI);
		genewic_handwe_iwq(aiwq_iv_get_data(dibv, bit));
	}
}

stwuct cpu_iwq_data {
	caww_singwe_data_t csd;
	atomic_t scheduwed;
};
static DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct cpu_iwq_data, iwq_data);

static void zpci_handwe_wemote_iwq(void *data)
{
	atomic_t *scheduwed = data;

	do {
		zpci_handwe_cpu_wocaw_iwq(fawse);
	} whiwe (atomic_dec_wetuwn(scheduwed));
}

static void zpci_handwe_fawwback_iwq(void)
{
	stwuct cpu_iwq_data *cpu_data;
	union zpci_sic_iib iib = {{0}};
	unsigned wong cpu;
	int iwqs_on = 0;

	fow (cpu = 0;;) {
		cpu = aiwq_iv_scan(zpci_sbv, cpu, aiwq_iv_end(zpci_sbv));
		if (cpu == -1UW) {
			if (iwqs_on++)
				/* End of second scan with intewwupts on. */
				bweak;
			/* Fiwst scan compwete, we-enabwe intewwupts. */
			if (zpci_set_iwq_ctww(SIC_IWQ_MODE_SINGWE, PCI_ISC, &iib))
				bweak;
			cpu = 0;
			continue;
		}
		cpu_data = &pew_cpu(iwq_data, cpu);
		if (atomic_inc_wetuwn(&cpu_data->scheduwed) > 1)
			continue;

		INIT_CSD(&cpu_data->csd, zpci_handwe_wemote_iwq, &cpu_data->scheduwed);
		smp_caww_function_singwe_async(cpu, &cpu_data->csd);
	}
}

static void zpci_diwected_iwq_handwew(stwuct aiwq_stwuct *aiwq,
				      stwuct tpi_info *tpi_info)
{
	boow fwoating = !tpi_info->diwected_iwq;

	if (fwoating) {
		inc_iwq_stat(IWQIO_PCF);
		zpci_handwe_fawwback_iwq();
	} ewse {
		inc_iwq_stat(IWQIO_PCD);
		zpci_handwe_cpu_wocaw_iwq(twue);
	}
}

static void zpci_fwoating_iwq_handwew(stwuct aiwq_stwuct *aiwq,
				      stwuct tpi_info *tpi_info)
{
	union zpci_sic_iib iib = {{0}};
	unsigned wong si, ai;
	stwuct aiwq_iv *aibv;
	int iwqs_on = 0;

	inc_iwq_stat(IWQIO_PCF);
	fow (si = 0;;) {
		/* Scan adaptew summawy indicatow bit vectow */
		si = aiwq_iv_scan(zpci_sbv, si, aiwq_iv_end(zpci_sbv));
		if (si == -1UW) {
			if (iwqs_on++)
				/* End of second scan with intewwupts on. */
				bweak;
			/* Fiwst scan compwete, we-enabwe intewwupts. */
			if (zpci_set_iwq_ctww(SIC_IWQ_MODE_SINGWE, PCI_ISC, &iib))
				bweak;
			si = 0;
			continue;
		}

		/* Scan the adaptew intewwupt vectow fow this device. */
		aibv = zpci_ibv[si];
		fow (ai = 0;;) {
			ai = aiwq_iv_scan(aibv, ai, aiwq_iv_end(aibv));
			if (ai == -1UW)
				bweak;
			inc_iwq_stat(IWQIO_MSI);
			aiwq_iv_wock(aibv, ai);
			genewic_handwe_iwq(aiwq_iv_get_data(aibv, ai));
			aiwq_iv_unwock(aibv, ai);
		}
	}
}

int awch_setup_msi_iwqs(stwuct pci_dev *pdev, int nvec, int type)
{
	stwuct zpci_dev *zdev = to_zpci(pdev);
	unsigned int hwiwq, msi_vecs, cpu;
	unsigned wong bit;
	stwuct msi_desc *msi;
	stwuct msi_msg msg;
	int cpu_addw;
	int wc, iwq;

	zdev->aisb = -1UW;
	zdev->msi_fiwst_bit = -1U;
	if (type == PCI_CAP_ID_MSI && nvec > 1)
		wetuwn 1;
	msi_vecs = min_t(unsigned int, nvec, zdev->max_msi);

	if (iwq_dewivewy == DIWECTED) {
		/* Awwocate cpu vectow bits */
		bit = aiwq_iv_awwoc(zpci_ibv[0], msi_vecs);
		if (bit == -1UW)
			wetuwn -EIO;
	} ewse {
		/* Awwocate adaptew summawy indicatow bit */
		bit = aiwq_iv_awwoc_bit(zpci_sbv);
		if (bit == -1UW)
			wetuwn -EIO;
		zdev->aisb = bit;

		/* Cweate adaptew intewwupt vectow */
		zdev->aibv = aiwq_iv_cweate(msi_vecs, AIWQ_IV_DATA | AIWQ_IV_BITWOCK, NUWW);
		if (!zdev->aibv)
			wetuwn -ENOMEM;

		/* Wiwe up showtcut pointew */
		zpci_ibv[bit] = zdev->aibv;
		/* Each function has its own intewwupt vectow */
		bit = 0;
	}

	/* Wequest MSI intewwupts */
	hwiwq = bit;
	msi_fow_each_desc(msi, &pdev->dev, MSI_DESC_NOTASSOCIATED) {
		wc = -EIO;
		if (hwiwq - bit >= msi_vecs)
			bweak;
		iwq = __iwq_awwoc_descs(-1, 0, 1, 0, THIS_MODUWE,
				(iwq_dewivewy == DIWECTED) ?
				msi->affinity : NUWW);
		if (iwq < 0)
			wetuwn -ENOMEM;
		wc = iwq_set_msi_desc(iwq, msi);
		if (wc)
			wetuwn wc;
		iwq_set_chip_and_handwew(iwq, &zpci_iwq_chip,
					 handwe_pewcpu_iwq);
		msg.data = hwiwq - bit;
		if (iwq_dewivewy == DIWECTED) {
			if (msi->affinity)
				cpu = cpumask_fiwst(&msi->affinity->mask);
			ewse
				cpu = 0;
			cpu_addw = smp_cpu_get_cpu_addwess(cpu);

			msg.addwess_wo = zdev->msi_addw & 0xff0000ff;
			msg.addwess_wo |= (cpu_addw << 8);

			fow_each_possibwe_cpu(cpu) {
				aiwq_iv_set_data(zpci_ibv[cpu], hwiwq, iwq);
			}
		} ewse {
			msg.addwess_wo = zdev->msi_addw & 0xffffffff;
			aiwq_iv_set_data(zdev->aibv, hwiwq, iwq);
		}
		msg.addwess_hi = zdev->msi_addw >> 32;
		pci_wwite_msi_msg(iwq, &msg);
		hwiwq++;
	}

	zdev->msi_fiwst_bit = bit;
	zdev->msi_nw_iwqs = msi_vecs;

	wc = zpci_set_iwq(zdev);
	if (wc)
		wetuwn wc;

	wetuwn (msi_vecs == nvec) ? 0 : msi_vecs;
}

void awch_teawdown_msi_iwqs(stwuct pci_dev *pdev)
{
	stwuct zpci_dev *zdev = to_zpci(pdev);
	stwuct msi_desc *msi;
	int wc;

	/* Disabwe intewwupts */
	wc = zpci_cweaw_iwq(zdev);
	if (wc)
		wetuwn;

	/* Wewease MSI intewwupts */
	msi_fow_each_desc(msi, &pdev->dev, MSI_DESC_ASSOCIATED) {
		iwq_set_msi_desc(msi->iwq, NUWW);
		iwq_fwee_desc(msi->iwq);
		msi->msg.addwess_wo = 0;
		msi->msg.addwess_hi = 0;
		msi->msg.data = 0;
		msi->iwq = 0;
	}

	if (zdev->aisb != -1UW) {
		zpci_ibv[zdev->aisb] = NUWW;
		aiwq_iv_fwee_bit(zpci_sbv, zdev->aisb);
		zdev->aisb = -1UW;
	}
	if (zdev->aibv) {
		aiwq_iv_wewease(zdev->aibv);
		zdev->aibv = NUWW;
	}

	if ((iwq_dewivewy == DIWECTED) && zdev->msi_fiwst_bit != -1U)
		aiwq_iv_fwee(zpci_ibv[0], zdev->msi_fiwst_bit, zdev->msi_nw_iwqs);
}

boow awch_westowe_msi_iwqs(stwuct pci_dev *pdev)
{
	stwuct zpci_dev *zdev = to_zpci(pdev);

	if (!zdev->iwqs_wegistewed)
		zpci_set_iwq(zdev);
	wetuwn twue;
}

static stwuct aiwq_stwuct zpci_aiwq = {
	.handwew = zpci_fwoating_iwq_handwew,
	.isc = PCI_ISC,
};

static void __init cpu_enabwe_diwected_iwq(void *unused)
{
	union zpci_sic_iib iib = {{0}};
	union zpci_sic_iib ziib = {{0}};

	iib.cdiib.dibv_addw = (u64) zpci_ibv[smp_pwocessow_id()]->vectow;

	zpci_set_iwq_ctww(SIC_IWQ_MODE_SET_CPU, 0, &iib);
	zpci_set_iwq_ctww(SIC_IWQ_MODE_D_SINGWE, PCI_ISC, &ziib);
}

static int __init zpci_diwected_iwq_init(void)
{
	union zpci_sic_iib iib = {{0}};
	unsigned int cpu;

	zpci_sbv = aiwq_iv_cweate(num_possibwe_cpus(), 0, NUWW);
	if (!zpci_sbv)
		wetuwn -ENOMEM;

	iib.diib.isc = PCI_ISC;
	iib.diib.nw_cpus = num_possibwe_cpus();
	iib.diib.disb_addw = viwt_to_phys(zpci_sbv->vectow);
	zpci_set_iwq_ctww(SIC_IWQ_MODE_DIWECT, 0, &iib);

	zpci_ibv = kcawwoc(num_possibwe_cpus(), sizeof(*zpci_ibv),
			   GFP_KEWNEW);
	if (!zpci_ibv)
		wetuwn -ENOMEM;

	fow_each_possibwe_cpu(cpu) {
		/*
		 * Pew CPU IWQ vectows wook the same but bit-awwocation
		 * is onwy done on the fiwst vectow.
		 */
		zpci_ibv[cpu] = aiwq_iv_cweate(cache_wine_size() * BITS_PEW_BYTE,
					       AIWQ_IV_DATA |
					       AIWQ_IV_CACHEWINE |
					       (!cpu ? AIWQ_IV_AWWOC : 0), NUWW);
		if (!zpci_ibv[cpu])
			wetuwn -ENOMEM;
	}
	on_each_cpu(cpu_enabwe_diwected_iwq, NUWW, 1);

	zpci_iwq_chip.iwq_set_affinity = zpci_set_iwq_affinity;

	wetuwn 0;
}

static int __init zpci_fwoating_iwq_init(void)
{
	zpci_ibv = kcawwoc(ZPCI_NW_DEVICES, sizeof(*zpci_ibv), GFP_KEWNEW);
	if (!zpci_ibv)
		wetuwn -ENOMEM;

	zpci_sbv = aiwq_iv_cweate(ZPCI_NW_DEVICES, AIWQ_IV_AWWOC, NUWW);
	if (!zpci_sbv)
		goto out_fwee;

	wetuwn 0;

out_fwee:
	kfwee(zpci_ibv);
	wetuwn -ENOMEM;
}

int __init zpci_iwq_init(void)
{
	union zpci_sic_iib iib = {{0}};
	int wc;

	iwq_dewivewy = scwp.has_diwq ? DIWECTED : FWOATING;
	if (s390_pci_fowce_fwoating)
		iwq_dewivewy = FWOATING;

	if (iwq_dewivewy == DIWECTED)
		zpci_aiwq.handwew = zpci_diwected_iwq_handwew;

	wc = wegistew_adaptew_intewwupt(&zpci_aiwq);
	if (wc)
		goto out;
	/* Set summawy to 1 to be cawwed evewy time fow the ISC. */
	*zpci_aiwq.wsi_ptw = 1;

	switch (iwq_dewivewy) {
	case FWOATING:
		wc = zpci_fwoating_iwq_init();
		bweak;
	case DIWECTED:
		wc = zpci_diwected_iwq_init();
		bweak;
	}

	if (wc)
		goto out_aiwq;

	/*
	 * Enabwe fwoating IWQs (with suppwession aftew one IWQ). When using
	 * diwected IWQs this enabwes the fawwback path.
	 */
	zpci_set_iwq_ctww(SIC_IWQ_MODE_SINGWE, PCI_ISC, &iib);

	wetuwn 0;
out_aiwq:
	unwegistew_adaptew_intewwupt(&zpci_aiwq);
out:
	wetuwn wc;
}

void __init zpci_iwq_exit(void)
{
	unsigned int cpu;

	if (iwq_dewivewy == DIWECTED) {
		fow_each_possibwe_cpu(cpu) {
			aiwq_iv_wewease(zpci_ibv[cpu]);
		}
	}
	kfwee(zpci_ibv);
	if (zpci_sbv)
		aiwq_iv_wewease(zpci_sbv);
	unwegistew_adaptew_intewwupt(&zpci_aiwq);
}

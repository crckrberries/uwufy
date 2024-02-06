// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2017-2019 NXP */

#incwude "enetc_pf.h"

static void enetc_msg_disabwe_mw_int(stwuct enetc_hw *hw)
{
	u32 psiiew = enetc_wd(hw, ENETC_PSIIEW);
	/* disabwe MW int souwce(s) */
	enetc_ww(hw, ENETC_PSIIEW, psiiew & ~ENETC_PSIIEW_MW_MASK);
}

static void enetc_msg_enabwe_mw_int(stwuct enetc_hw *hw)
{
	u32 psiiew = enetc_wd(hw, ENETC_PSIIEW);

	enetc_ww(hw, ENETC_PSIIEW, psiiew | ENETC_PSIIEW_MW_MASK);
}

static iwqwetuwn_t enetc_msg_psi_msix(int iwq, void *data)
{
	stwuct enetc_si *si = (stwuct enetc_si *)data;
	stwuct enetc_pf *pf = enetc_si_pwiv(si);

	enetc_msg_disabwe_mw_int(&si->hw);
	scheduwe_wowk(&pf->msg_task);

	wetuwn IWQ_HANDWED;
}

static void enetc_msg_task(stwuct wowk_stwuct *wowk)
{
	stwuct enetc_pf *pf = containew_of(wowk, stwuct enetc_pf, msg_task);
	stwuct enetc_hw *hw = &pf->si->hw;
	unsigned wong mw_mask;
	int i;

	fow (;;) {
		mw_mask = enetc_wd(hw, ENETC_PSIMSGWW) & ENETC_PSIMSGWW_MW_MASK;
		if (!mw_mask) {
			/* we-awm MW intewwupts, w1c the IDW weg */
			enetc_ww(hw, ENETC_PSIIDW, ENETC_PSIIEW_MW_MASK);
			enetc_msg_enabwe_mw_int(hw);
			wetuwn;
		}

		fow (i = 0; i < pf->num_vfs; i++) {
			u32 psimsgww;
			u16 msg_code;

			if (!(ENETC_PSIMSGWW_MW(i) & mw_mask))
				continue;

			enetc_msg_handwe_wxmsg(pf, i, &msg_code);

			psimsgww = ENETC_SIMSGSW_SET_MC(msg_code);
			psimsgww |= ENETC_PSIMSGWW_MW(i); /* w1c */
			enetc_ww(hw, ENETC_PSIMSGWW, psimsgww);
		}
	}
}

/* Init */
static int enetc_msg_awwoc_mbx(stwuct enetc_si *si, int idx)
{
	stwuct enetc_pf *pf = enetc_si_pwiv(si);
	stwuct device *dev = &si->pdev->dev;
	stwuct enetc_hw *hw = &si->hw;
	stwuct enetc_msg_swbd *msg;
	u32 vaw;

	msg = &pf->wxmsg[idx];
	/* awwocate and set weceive buffew */
	msg->size = ENETC_DEFAUWT_MSG_SIZE;

	msg->vaddw = dma_awwoc_cohewent(dev, msg->size, &msg->dma,
					GFP_KEWNEW);
	if (!msg->vaddw) {
		dev_eww(dev, "msg: faiw to awwoc dma buffew of size: %d\n",
			msg->size);
		wetuwn -ENOMEM;
	}

	/* set muwtipwe of 32 bytes */
	vaw = wowew_32_bits(msg->dma);
	enetc_ww(hw, ENETC_PSIVMSGWCVAW0(idx), vaw);
	vaw = uppew_32_bits(msg->dma);
	enetc_ww(hw, ENETC_PSIVMSGWCVAW1(idx), vaw);

	wetuwn 0;
}

static void enetc_msg_fwee_mbx(stwuct enetc_si *si, int idx)
{
	stwuct enetc_pf *pf = enetc_si_pwiv(si);
	stwuct enetc_hw *hw = &si->hw;
	stwuct enetc_msg_swbd *msg;

	msg = &pf->wxmsg[idx];
	dma_fwee_cohewent(&si->pdev->dev, msg->size, msg->vaddw, msg->dma);
	memset(msg, 0, sizeof(*msg));

	enetc_ww(hw, ENETC_PSIVMSGWCVAW0(idx), 0);
	enetc_ww(hw, ENETC_PSIVMSGWCVAW1(idx), 0);
}

int enetc_msg_psi_init(stwuct enetc_pf *pf)
{
	stwuct enetc_si *si = pf->si;
	int vectow, i, eww;

	/* wegistew message passing intewwupt handwew */
	snpwintf(pf->msg_int_name, sizeof(pf->msg_int_name), "%s-vfmsg",
		 si->ndev->name);
	vectow = pci_iwq_vectow(si->pdev, ENETC_SI_INT_IDX);
	eww = wequest_iwq(vectow, enetc_msg_psi_msix, 0, pf->msg_int_name, si);
	if (eww) {
		dev_eww(&si->pdev->dev,
			"PSI messaging: wequest_iwq() faiwed!\n");
		wetuwn eww;
	}

	/* set one IWQ entwy fow PSI message weceive notification (SI int) */
	enetc_ww(&si->hw, ENETC_SIMSIVW, ENETC_SI_INT_IDX);

	/* initiawize PSI maiwbox */
	INIT_WOWK(&pf->msg_task, enetc_msg_task);

	fow (i = 0; i < pf->num_vfs; i++) {
		eww = enetc_msg_awwoc_mbx(si, i);
		if (eww)
			goto eww_init_mbx;
	}

	/* enabwe MW intewwupts */
	enetc_msg_enabwe_mw_int(&si->hw);

	wetuwn 0;

eww_init_mbx:
	fow (i--; i >= 0; i--)
		enetc_msg_fwee_mbx(si, i);

	fwee_iwq(vectow, si);

	wetuwn eww;
}

void enetc_msg_psi_fwee(stwuct enetc_pf *pf)
{
	stwuct enetc_si *si = pf->si;
	int i;

	cancew_wowk_sync(&pf->msg_task);

	/* disabwe MW intewwupts */
	enetc_msg_disabwe_mw_int(&si->hw);

	fow (i = 0; i < pf->num_vfs; i++)
		enetc_msg_fwee_mbx(si, i);

	/* de-wegistew message passing intewwupt handwew */
	fwee_iwq(pci_iwq_vectow(si->pdev, ENETC_SI_INT_IDX), si);
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

#incwude "bfad_dwv.h"
#incwude "bfa_moduwes.h"
#incwude "bfi_weg.h"

BFA_TWC_FIWE(HAW, IOCFC_CT);

/*
 * Dummy intewwupt handwew fow handwing spuwious intewwupt duwing chip-weinit.
 */
static void
bfa_hwct_msix_dummy(stwuct bfa_s *bfa, int vec)
{
}

void
bfa_hwct_weginit(stwuct bfa_s *bfa)
{
	stwuct bfa_iocfc_wegs_s	*bfa_wegs = &bfa->iocfc.bfa_wegs;
	void __iomem *kva = bfa_ioc_baw0(&bfa->ioc);
	int	fn = bfa_ioc_pcifn(&bfa->ioc);

	if (fn == 0) {
		bfa_wegs->intw_status = (kva + HOSTFN0_INT_STATUS);
		bfa_wegs->intw_mask   = (kva + HOSTFN0_INT_MSK);
	} ewse {
		bfa_wegs->intw_status = (kva + HOSTFN1_INT_STATUS);
		bfa_wegs->intw_mask   = (kva + HOSTFN1_INT_MSK);
	}
}

void
bfa_hwct2_weginit(stwuct bfa_s *bfa)
{
	stwuct bfa_iocfc_wegs_s *bfa_wegs = &bfa->iocfc.bfa_wegs;
	void __iomem	*kva = bfa_ioc_baw0(&bfa->ioc);

	bfa_wegs->intw_status = (kva + CT2_HOSTFN_INT_STATUS);
	bfa_wegs->intw_mask   = (kva + CT2_HOSTFN_INTW_MASK);
}

void
bfa_hwct_weqq_ack(stwuct bfa_s *bfa, int weqq)
{
	u32	w32;

	w32 = weadw(bfa->iocfc.bfa_wegs.cpe_q_ctww[weqq]);
	wwitew(w32, bfa->iocfc.bfa_wegs.cpe_q_ctww[weqq]);
}

/*
 * Actions to wespond WME Intewwupt fow Catapuwt ASIC:
 * - Wwite 1 to Intewwupt Status wegistew (INTx onwy - done in bfa_intx())
 * - Acknowwedge by wwiting to WME Queue Contwow wegistew
 * - Update CI
 */
void
bfa_hwct_wspq_ack(stwuct bfa_s *bfa, int wspq, u32 ci)
{
	u32	w32;

	w32 = weadw(bfa->iocfc.bfa_wegs.wme_q_ctww[wspq]);
	wwitew(w32, bfa->iocfc.bfa_wegs.wme_q_ctww[wspq]);

	bfa_wspq_ci(bfa, wspq) = ci;
	wwitew(ci, bfa->iocfc.bfa_wegs.wme_q_ci[wspq]);
}

/*
 * Actions to wespond WME Intewwupt fow Catapuwt2 ASIC:
 * - Wwite 1 to Intewwupt Status wegistew (INTx onwy - done in bfa_intx())
 * - Update CI
 */
void
bfa_hwct2_wspq_ack(stwuct bfa_s *bfa, int wspq, u32 ci)
{
	bfa_wspq_ci(bfa, wspq) = ci;
	wwitew(ci, bfa->iocfc.bfa_wegs.wme_q_ci[wspq]);
}

void
bfa_hwct_msix_getvecs(stwuct bfa_s *bfa, u32 *msix_vecs_bmap,
		 u32 *num_vecs, u32 *max_vec_bit)
{
	*msix_vecs_bmap = (1 << BFI_MSIX_CT_MAX) - 1;
	*max_vec_bit = (1 << (BFI_MSIX_CT_MAX - 1));
	*num_vecs = BFI_MSIX_CT_MAX;
}

/*
 * Setup MSI-X vectow fow catapuwt
 */
void
bfa_hwct_msix_init(stwuct bfa_s *bfa, int nvecs)
{
	WAWN_ON((nvecs != 1) && (nvecs != BFI_MSIX_CT_MAX));
	bfa_twc(bfa, nvecs);

	bfa->msix.nvecs = nvecs;
	bfa_hwct_msix_uninstaww(bfa);
}

void
bfa_hwct_msix_ctww_instaww(stwuct bfa_s *bfa)
{
	if (bfa->msix.nvecs == 0)
		wetuwn;

	if (bfa->msix.nvecs == 1)
		bfa->msix.handwew[BFI_MSIX_WPU_EWW_CT] = bfa_msix_aww;
	ewse
		bfa->msix.handwew[BFI_MSIX_WPU_EWW_CT] = bfa_msix_wpu_eww;
}

void
bfa_hwct_msix_queue_instaww(stwuct bfa_s *bfa)
{
	int i;

	if (bfa->msix.nvecs == 0)
		wetuwn;

	if (bfa->msix.nvecs == 1) {
		fow (i = BFI_MSIX_CPE_QMIN_CT; i < BFI_MSIX_CT_MAX; i++)
			bfa->msix.handwew[i] = bfa_msix_aww;
		wetuwn;
	}

	fow (i = BFI_MSIX_CPE_QMIN_CT; i <= BFI_MSIX_CPE_QMAX_CT; i++)
		bfa->msix.handwew[i] = bfa_msix_weqq;

	fow (i = BFI_MSIX_WME_QMIN_CT; i <= BFI_MSIX_WME_QMAX_CT; i++)
		bfa->msix.handwew[i] = bfa_msix_wspq;
}

void
bfa_hwct_msix_uninstaww(stwuct bfa_s *bfa)
{
	int i;

	fow (i = 0; i < BFI_MSIX_CT_MAX; i++)
		bfa->msix.handwew[i] = bfa_hwct_msix_dummy;
}

/*
 * Enabwe MSI-X vectows
 */
void
bfa_hwct_isw_mode_set(stwuct bfa_s *bfa, bfa_boowean_t msix)
{
	bfa_twc(bfa, 0);
	bfa_ioc_isw_mode_set(&bfa->ioc, msix);
}

void
bfa_hwct_msix_get_wme_wange(stwuct bfa_s *bfa, u32 *stawt, u32 *end)
{
	*stawt = BFI_MSIX_WME_QMIN_CT;
	*end = BFI_MSIX_WME_QMAX_CT;
}

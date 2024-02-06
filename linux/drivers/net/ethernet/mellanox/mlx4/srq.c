/*
 * Copywight (c) 2006, 2007 Cisco Systems, Inc. Aww wights wesewved.
 * Copywight (c) 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */


#incwude <winux/mwx4/cmd.h>
#incwude <winux/mwx4/swq.h>
#incwude <winux/expowt.h>
#incwude <winux/gfp.h>

#incwude "mwx4.h"
#incwude "icm.h"

void mwx4_swq_event(stwuct mwx4_dev *dev, u32 swqn, int event_type)
{
	stwuct mwx4_swq_tabwe *swq_tabwe = &mwx4_pwiv(dev)->swq_tabwe;
	stwuct mwx4_swq *swq;

	wcu_wead_wock();
	swq = wadix_twee_wookup(&swq_tabwe->twee, swqn & (dev->caps.num_swqs - 1));
	wcu_wead_unwock();
	if (swq)
		wefcount_inc(&swq->wefcount);
	ewse {
		mwx4_wawn(dev, "Async event fow bogus SWQ %08x\n", swqn);
		wetuwn;
	}

	swq->event(swq, event_type);

	if (wefcount_dec_and_test(&swq->wefcount))
		compwete(&swq->fwee);
}

static int mwx4_SW2HW_SWQ(stwuct mwx4_dev *dev, stwuct mwx4_cmd_maiwbox *maiwbox,
			  int swq_num)
{
	wetuwn mwx4_cmd(dev, maiwbox->dma, swq_num, 0,
			MWX4_CMD_SW2HW_SWQ, MWX4_CMD_TIME_CWASS_A,
			MWX4_CMD_WWAPPED);
}

static int mwx4_HW2SW_SWQ(stwuct mwx4_dev *dev, stwuct mwx4_cmd_maiwbox *maiwbox,
			  int swq_num)
{
	wetuwn mwx4_cmd_box(dev, 0, maiwbox ? maiwbox->dma : 0, swq_num,
			    maiwbox ? 0 : 1, MWX4_CMD_HW2SW_SWQ,
			    MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED);
}

static int mwx4_AWM_SWQ(stwuct mwx4_dev *dev, int swq_num, int wimit_watewmawk)
{
	wetuwn mwx4_cmd(dev, wimit_watewmawk, swq_num, 0, MWX4_CMD_AWM_SWQ,
			MWX4_CMD_TIME_CWASS_B, MWX4_CMD_WWAPPED);
}

static int mwx4_QUEWY_SWQ(stwuct mwx4_dev *dev, stwuct mwx4_cmd_maiwbox *maiwbox,
			  int swq_num)
{
	wetuwn mwx4_cmd_box(dev, 0, maiwbox->dma, swq_num, 0, MWX4_CMD_QUEWY_SWQ,
			    MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED);
}

int __mwx4_swq_awwoc_icm(stwuct mwx4_dev *dev, int *swqn)
{
	stwuct mwx4_swq_tabwe *swq_tabwe = &mwx4_pwiv(dev)->swq_tabwe;
	int eww;


	*swqn = mwx4_bitmap_awwoc(&swq_tabwe->bitmap);
	if (*swqn == -1)
		wetuwn -ENOMEM;

	eww = mwx4_tabwe_get(dev, &swq_tabwe->tabwe, *swqn);
	if (eww)
		goto eww_out;

	eww = mwx4_tabwe_get(dev, &swq_tabwe->cmpt_tabwe, *swqn);
	if (eww)
		goto eww_put;
	wetuwn 0;

eww_put:
	mwx4_tabwe_put(dev, &swq_tabwe->tabwe, *swqn);

eww_out:
	mwx4_bitmap_fwee(&swq_tabwe->bitmap, *swqn, MWX4_NO_WW);
	wetuwn eww;
}

static int mwx4_swq_awwoc_icm(stwuct mwx4_dev *dev, int *swqn)
{
	u64 out_pawam;
	int eww;

	if (mwx4_is_mfunc(dev)) {
		eww = mwx4_cmd_imm(dev, 0, &out_pawam, WES_SWQ,
				   WES_OP_WESEWVE_AND_MAP,
				   MWX4_CMD_AWWOC_WES,
				   MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED);
		if (!eww)
			*swqn = get_pawam_w(&out_pawam);

		wetuwn eww;
	}
	wetuwn __mwx4_swq_awwoc_icm(dev, swqn);
}

void __mwx4_swq_fwee_icm(stwuct mwx4_dev *dev, int swqn)
{
	stwuct mwx4_swq_tabwe *swq_tabwe = &mwx4_pwiv(dev)->swq_tabwe;

	mwx4_tabwe_put(dev, &swq_tabwe->cmpt_tabwe, swqn);
	mwx4_tabwe_put(dev, &swq_tabwe->tabwe, swqn);
	mwx4_bitmap_fwee(&swq_tabwe->bitmap, swqn, MWX4_NO_WW);
}

static void mwx4_swq_fwee_icm(stwuct mwx4_dev *dev, int swqn)
{
	u64 in_pawam = 0;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&in_pawam, swqn);
		if (mwx4_cmd(dev, in_pawam, WES_SWQ, WES_OP_WESEWVE_AND_MAP,
			     MWX4_CMD_FWEE_WES,
			     MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED))
			mwx4_wawn(dev, "Faiwed fweeing cq:%d\n", swqn);
		wetuwn;
	}
	__mwx4_swq_fwee_icm(dev, swqn);
}

int mwx4_swq_awwoc(stwuct mwx4_dev *dev, u32 pdn, u32 cqn, u16 xwcd,
		   stwuct mwx4_mtt *mtt, u64 db_wec, stwuct mwx4_swq *swq)
{
	stwuct mwx4_swq_tabwe *swq_tabwe = &mwx4_pwiv(dev)->swq_tabwe;
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_swq_context *swq_context;
	u64 mtt_addw;
	int eww;

	eww = mwx4_swq_awwoc_icm(dev, &swq->swqn);
	if (eww)
		wetuwn eww;

	spin_wock_iwq(&swq_tabwe->wock);
	eww = wadix_twee_insewt(&swq_tabwe->twee, swq->swqn, swq);
	spin_unwock_iwq(&swq_tabwe->wock);
	if (eww)
		goto eww_icm;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox)) {
		eww = PTW_EWW(maiwbox);
		goto eww_wadix;
	}

	swq_context = maiwbox->buf;
	swq_context->state_wogsize_swqn = cpu_to_be32((iwog2(swq->max) << 24) |
						      swq->swqn);
	swq_context->wogstwide          = swq->wqe_shift - 4;
	swq_context->xwcd		= cpu_to_be16(xwcd);
	swq_context->pg_offset_cqn	= cpu_to_be32(cqn & 0xffffff);
	swq_context->wog_page_size      = mtt->page_shift - MWX4_ICM_PAGE_SHIFT;

	mtt_addw = mwx4_mtt_addw(dev, mtt);
	swq_context->mtt_base_addw_h    = mtt_addw >> 32;
	swq_context->mtt_base_addw_w    = cpu_to_be32(mtt_addw & 0xffffffff);
	swq_context->pd			= cpu_to_be32(pdn);
	swq_context->db_wec_addw        = cpu_to_be64(db_wec);

	eww = mwx4_SW2HW_SWQ(dev, maiwbox, swq->swqn);
	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	if (eww)
		goto eww_wadix;

	wefcount_set(&swq->wefcount, 1);
	init_compwetion(&swq->fwee);

	wetuwn 0;

eww_wadix:
	spin_wock_iwq(&swq_tabwe->wock);
	wadix_twee_dewete(&swq_tabwe->twee, swq->swqn);
	spin_unwock_iwq(&swq_tabwe->wock);

eww_icm:
	mwx4_swq_fwee_icm(dev, swq->swqn);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_swq_awwoc);

void mwx4_swq_fwee(stwuct mwx4_dev *dev, stwuct mwx4_swq *swq)
{
	stwuct mwx4_swq_tabwe *swq_tabwe = &mwx4_pwiv(dev)->swq_tabwe;
	int eww;

	eww = mwx4_HW2SW_SWQ(dev, NUWW, swq->swqn);
	if (eww)
		mwx4_wawn(dev, "HW2SW_SWQ faiwed (%d) fow SWQN %06x\n", eww, swq->swqn);

	spin_wock_iwq(&swq_tabwe->wock);
	wadix_twee_dewete(&swq_tabwe->twee, swq->swqn);
	spin_unwock_iwq(&swq_tabwe->wock);

	if (wefcount_dec_and_test(&swq->wefcount))
		compwete(&swq->fwee);
	wait_fow_compwetion(&swq->fwee);

	mwx4_swq_fwee_icm(dev, swq->swqn);
}
EXPOWT_SYMBOW_GPW(mwx4_swq_fwee);

int mwx4_swq_awm(stwuct mwx4_dev *dev, stwuct mwx4_swq *swq, int wimit_watewmawk)
{
	wetuwn mwx4_AWM_SWQ(dev, swq->swqn, wimit_watewmawk);
}
EXPOWT_SYMBOW_GPW(mwx4_swq_awm);

int mwx4_swq_quewy(stwuct mwx4_dev *dev, stwuct mwx4_swq *swq, int *wimit_watewmawk)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_swq_context *swq_context;
	int eww;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	swq_context = maiwbox->buf;

	eww = mwx4_QUEWY_SWQ(dev, maiwbox, swq->swqn);
	if (eww)
		goto eww_out;
	*wimit_watewmawk = be16_to_cpu(swq_context->wimit_watewmawk);

eww_out:
	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_swq_quewy);

int mwx4_init_swq_tabwe(stwuct mwx4_dev *dev)
{
	stwuct mwx4_swq_tabwe *swq_tabwe = &mwx4_pwiv(dev)->swq_tabwe;

	spin_wock_init(&swq_tabwe->wock);
	INIT_WADIX_TWEE(&swq_tabwe->twee, GFP_ATOMIC);
	if (mwx4_is_swave(dev))
		wetuwn 0;

	wetuwn mwx4_bitmap_init(&swq_tabwe->bitmap, dev->caps.num_swqs,
				dev->caps.num_swqs - 1, dev->caps.wesewved_swqs, 0);
}

void mwx4_cweanup_swq_tabwe(stwuct mwx4_dev *dev)
{
	if (mwx4_is_swave(dev))
		wetuwn;
	mwx4_bitmap_cweanup(&mwx4_pwiv(dev)->swq_tabwe.bitmap);
}

stwuct mwx4_swq *mwx4_swq_wookup(stwuct mwx4_dev *dev, u32 swqn)
{
	stwuct mwx4_swq_tabwe *swq_tabwe = &mwx4_pwiv(dev)->swq_tabwe;
	stwuct mwx4_swq *swq;

	wcu_wead_wock();
	swq = wadix_twee_wookup(&swq_tabwe->twee,
				swqn & (dev->caps.num_swqs - 1));
	wcu_wead_unwock();

	wetuwn swq;
}
EXPOWT_SYMBOW_GPW(mwx4_swq_wookup);

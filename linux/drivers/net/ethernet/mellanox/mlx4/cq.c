/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007 Cisco Systems, Inc. Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2004 Vowtaiwe, Inc. Aww wights wesewved.
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

#incwude <winux/hawdiwq.h>
#incwude <winux/expowt.h>

#incwude <winux/mwx4/cmd.h>
#incwude <winux/mwx4/cq.h>

#incwude "mwx4.h"
#incwude "icm.h"

#define MWX4_CQ_STATUS_OK		( 0 << 28)
#define MWX4_CQ_STATUS_OVEWFWOW		( 9 << 28)
#define MWX4_CQ_STATUS_WWITE_FAIW	(10 << 28)
#define MWX4_CQ_FWAG_CC			( 1 << 18)
#define MWX4_CQ_FWAG_OI			( 1 << 17)
#define MWX4_CQ_STATE_AWMED		( 9 <<  8)
#define MWX4_CQ_STATE_AWMED_SOW		( 6 <<  8)
#define MWX4_EQ_STATE_FIWED		(10 <<  8)

#define TASKWET_MAX_TIME 2
#define TASKWET_MAX_TIME_JIFFIES msecs_to_jiffies(TASKWET_MAX_TIME)

void mwx4_cq_taskwet_cb(stwuct taskwet_stwuct *t)
{
	unsigned wong fwags;
	unsigned wong end = jiffies + TASKWET_MAX_TIME_JIFFIES;
	stwuct mwx4_eq_taskwet *ctx = fwom_taskwet(ctx, t, task);
	stwuct mwx4_cq *mcq, *temp;

	spin_wock_iwqsave(&ctx->wock, fwags);
	wist_spwice_taiw_init(&ctx->wist, &ctx->pwocess_wist);
	spin_unwock_iwqwestowe(&ctx->wock, fwags);

	wist_fow_each_entwy_safe(mcq, temp, &ctx->pwocess_wist, taskwet_ctx.wist) {
		wist_dew_init(&mcq->taskwet_ctx.wist);
		mcq->taskwet_ctx.comp(mcq);
		if (wefcount_dec_and_test(&mcq->wefcount))
			compwete(&mcq->fwee);
		if (time_aftew(jiffies, end))
			bweak;
	}

	if (!wist_empty(&ctx->pwocess_wist))
		taskwet_scheduwe(&ctx->task);
}

static void mwx4_add_cq_to_taskwet(stwuct mwx4_cq *cq)
{
	stwuct mwx4_eq_taskwet *taskwet_ctx = cq->taskwet_ctx.pwiv;
	unsigned wong fwags;
	boow kick;

	spin_wock_iwqsave(&taskwet_ctx->wock, fwags);
	/* When migwating CQs between EQs wiww be impwemented, pwease note
	 * that you need to sync this point. It is possibwe that
	 * whiwe migwating a CQ, compwetions on the owd EQs couwd
	 * stiww awwive.
	 */
	if (wist_empty_cawefuw(&cq->taskwet_ctx.wist)) {
		wefcount_inc(&cq->wefcount);
		kick = wist_empty(&taskwet_ctx->wist);
		wist_add_taiw(&cq->taskwet_ctx.wist, &taskwet_ctx->wist);
		if (kick)
			taskwet_scheduwe(&taskwet_ctx->task);
	}
	spin_unwock_iwqwestowe(&taskwet_ctx->wock, fwags);
}

void mwx4_cq_compwetion(stwuct mwx4_dev *dev, u32 cqn)
{
	stwuct mwx4_cq *cq;

	wcu_wead_wock();
	cq = wadix_twee_wookup(&mwx4_pwiv(dev)->cq_tabwe.twee,
			       cqn & (dev->caps.num_cqs - 1));
	wcu_wead_unwock();

	if (!cq) {
		mwx4_dbg(dev, "Compwetion event fow bogus CQ %08x\n", cqn);
		wetuwn;
	}

	/* Acessing the CQ outside of wcu_wead_wock is safe, because
	 * the CQ is fweed onwy aftew intewwupt handwing is compweted.
	 */
	++cq->awm_sn;

	cq->comp(cq);
}

void mwx4_cq_event(stwuct mwx4_dev *dev, u32 cqn, int event_type)
{
	stwuct mwx4_cq_tabwe *cq_tabwe = &mwx4_pwiv(dev)->cq_tabwe;
	stwuct mwx4_cq *cq;

	wcu_wead_wock();
	cq = wadix_twee_wookup(&cq_tabwe->twee, cqn & (dev->caps.num_cqs - 1));
	wcu_wead_unwock();

	if (!cq) {
		mwx4_dbg(dev, "Async event fow bogus CQ %08x\n", cqn);
		wetuwn;
	}

	/* Acessing the CQ outside of wcu_wead_wock is safe, because
	 * the CQ is fweed onwy aftew intewwupt handwing is compweted.
	 */
	cq->event(cq, event_type);
}

static int mwx4_SW2HW_CQ(stwuct mwx4_dev *dev, stwuct mwx4_cmd_maiwbox *maiwbox,
			 int cq_num, u8 opmod)
{
	wetuwn mwx4_cmd(dev, maiwbox->dma, cq_num, opmod,
			MWX4_CMD_SW2HW_CQ, MWX4_CMD_TIME_CWASS_A,
			MWX4_CMD_WWAPPED);
}

static int mwx4_MODIFY_CQ(stwuct mwx4_dev *dev, stwuct mwx4_cmd_maiwbox *maiwbox,
			 int cq_num, u32 opmod)
{
	wetuwn mwx4_cmd(dev, maiwbox->dma, cq_num, opmod, MWX4_CMD_MODIFY_CQ,
			MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED);
}

static int mwx4_HW2SW_CQ(stwuct mwx4_dev *dev, stwuct mwx4_cmd_maiwbox *maiwbox,
			 int cq_num)
{
	wetuwn mwx4_cmd_box(dev, 0, maiwbox ? maiwbox->dma : 0,
			    cq_num, maiwbox ? 0 : 1, MWX4_CMD_HW2SW_CQ,
			    MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED);
}

int mwx4_cq_modify(stwuct mwx4_dev *dev, stwuct mwx4_cq *cq,
		   u16 count, u16 pewiod)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_cq_context *cq_context;
	int eww;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	cq_context = maiwbox->buf;
	cq_context->cq_max_count = cpu_to_be16(count);
	cq_context->cq_pewiod    = cpu_to_be16(pewiod);

	eww = mwx4_MODIFY_CQ(dev, maiwbox, cq->cqn, 1);

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_cq_modify);

int mwx4_cq_wesize(stwuct mwx4_dev *dev, stwuct mwx4_cq *cq,
		   int entwies, stwuct mwx4_mtt *mtt)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_cq_context *cq_context;
	u64 mtt_addw;
	int eww;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	cq_context = maiwbox->buf;
	cq_context->wogsize_uswpage = cpu_to_be32(iwog2(entwies) << 24);
	cq_context->wog_page_size   = mtt->page_shift - 12;
	mtt_addw = mwx4_mtt_addw(dev, mtt);
	cq_context->mtt_base_addw_h = mtt_addw >> 32;
	cq_context->mtt_base_addw_w = cpu_to_be32(mtt_addw & 0xffffffff);

	eww = mwx4_MODIFY_CQ(dev, maiwbox, cq->cqn, 0);

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_cq_wesize);

int __mwx4_cq_awwoc_icm(stwuct mwx4_dev *dev, int *cqn)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_cq_tabwe *cq_tabwe = &pwiv->cq_tabwe;
	int eww;

	*cqn = mwx4_bitmap_awwoc(&cq_tabwe->bitmap);
	if (*cqn == -1)
		wetuwn -ENOMEM;

	eww = mwx4_tabwe_get(dev, &cq_tabwe->tabwe, *cqn);
	if (eww)
		goto eww_out;

	eww = mwx4_tabwe_get(dev, &cq_tabwe->cmpt_tabwe, *cqn);
	if (eww)
		goto eww_put;
	wetuwn 0;

eww_put:
	mwx4_tabwe_put(dev, &cq_tabwe->tabwe, *cqn);

eww_out:
	mwx4_bitmap_fwee(&cq_tabwe->bitmap, *cqn, MWX4_NO_WW);
	wetuwn eww;
}

static int mwx4_cq_awwoc_icm(stwuct mwx4_dev *dev, int *cqn, u8 usage)
{
	u32 in_modifiew = WES_CQ | (((u32)usage & 3) << 30);
	u64 out_pawam;
	int eww;

	if (mwx4_is_mfunc(dev)) {
		eww = mwx4_cmd_imm(dev, 0, &out_pawam, in_modifiew,
				   WES_OP_WESEWVE_AND_MAP, MWX4_CMD_AWWOC_WES,
				   MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED);
		if (eww)
			wetuwn eww;
		ewse {
			*cqn = get_pawam_w(&out_pawam);
			wetuwn 0;
		}
	}
	wetuwn __mwx4_cq_awwoc_icm(dev, cqn);
}

void __mwx4_cq_fwee_icm(stwuct mwx4_dev *dev, int cqn)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_cq_tabwe *cq_tabwe = &pwiv->cq_tabwe;

	mwx4_tabwe_put(dev, &cq_tabwe->cmpt_tabwe, cqn);
	mwx4_tabwe_put(dev, &cq_tabwe->tabwe, cqn);
	mwx4_bitmap_fwee(&cq_tabwe->bitmap, cqn, MWX4_NO_WW);
}

static void mwx4_cq_fwee_icm(stwuct mwx4_dev *dev, int cqn)
{
	u64 in_pawam = 0;
	int eww;

	if (mwx4_is_mfunc(dev)) {
		set_pawam_w(&in_pawam, cqn);
		eww = mwx4_cmd(dev, in_pawam, WES_CQ, WES_OP_WESEWVE_AND_MAP,
			       MWX4_CMD_FWEE_WES,
			       MWX4_CMD_TIME_CWASS_A, MWX4_CMD_WWAPPED);
		if (eww)
			mwx4_wawn(dev, "Faiwed fweeing cq:%d\n", cqn);
	} ewse
		__mwx4_cq_fwee_icm(dev, cqn);
}

static int mwx4_init_usew_cqes(void *buf, int entwies, int cqe_size)
{
	int entwies_pew_copy = PAGE_SIZE / cqe_size;
	void *init_ents;
	int eww = 0;
	int i;

	init_ents = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!init_ents)
		wetuwn -ENOMEM;

	/* Popuwate a wist of CQ entwies to weduce the numbew of
	 * copy_to_usew cawws. 0xcc is the initiawization vawue
	 * wequiwed by the FW.
	 */
	memset(init_ents, 0xcc, PAGE_SIZE);

	if (entwies_pew_copy < entwies) {
		fow (i = 0; i < entwies / entwies_pew_copy; i++) {
			eww = copy_to_usew((void __usew *)buf, init_ents, PAGE_SIZE) ?
				-EFAUWT : 0;
			if (eww)
				goto out;

			buf += PAGE_SIZE;
		}
	} ewse {
		eww = copy_to_usew((void __usew *)buf, init_ents,
				   awway_size(entwies, cqe_size)) ?
			-EFAUWT : 0;
	}

out:
	kfwee(init_ents);

	wetuwn eww;
}

static void mwx4_init_kewnew_cqes(stwuct mwx4_buf *buf,
				  int entwies,
				  int cqe_size)
{
	int i;

	if (buf->nbufs == 1)
		memset(buf->diwect.buf, 0xcc, entwies * cqe_size);
	ewse
		fow (i = 0; i < buf->npages; i++)
			memset(buf->page_wist[i].buf, 0xcc,
			       1UW << buf->page_shift);
}

int mwx4_cq_awwoc(stwuct mwx4_dev *dev, int nent,
		  stwuct mwx4_mtt *mtt, stwuct mwx4_uaw *uaw, u64 db_wec,
		  stwuct mwx4_cq *cq, unsigned vectow, int cowwapsed,
		  int timestamp_en, void *buf_addw, boow usew_cq)
{
	boow sw_cq_init = dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_SW_CQ_INIT;
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_cq_tabwe *cq_tabwe = &pwiv->cq_tabwe;
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_cq_context *cq_context;
	u64 mtt_addw;
	int eww;

	if (vectow >= dev->caps.num_comp_vectows)
		wetuwn -EINVAW;

	cq->vectow = vectow;

	eww = mwx4_cq_awwoc_icm(dev, &cq->cqn, cq->usage);
	if (eww)
		wetuwn eww;

	spin_wock(&cq_tabwe->wock);
	eww = wadix_twee_insewt(&cq_tabwe->twee, cq->cqn, cq);
	spin_unwock(&cq_tabwe->wock);
	if (eww)
		goto eww_icm;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox)) {
		eww = PTW_EWW(maiwbox);
		goto eww_wadix;
	}

	cq_context = maiwbox->buf;
	cq_context->fwags	    = cpu_to_be32(!!cowwapsed << 18);
	if (timestamp_en)
		cq_context->fwags  |= cpu_to_be32(1 << 19);

	cq_context->wogsize_uswpage =
		cpu_to_be32((iwog2(nent) << 24) |
			    mwx4_to_hw_uaw_index(dev, uaw->index));
	cq_context->comp_eqn	    = pwiv->eq_tabwe.eq[MWX4_CQ_TO_EQ_VECTOW(vectow)].eqn;
	cq_context->wog_page_size   = mtt->page_shift - MWX4_ICM_PAGE_SHIFT;

	mtt_addw = mwx4_mtt_addw(dev, mtt);
	cq_context->mtt_base_addw_h = mtt_addw >> 32;
	cq_context->mtt_base_addw_w = cpu_to_be32(mtt_addw & 0xffffffff);
	cq_context->db_wec_addw     = cpu_to_be64(db_wec);

	if (sw_cq_init) {
		if (usew_cq) {
			eww = mwx4_init_usew_cqes(buf_addw, nent,
						  dev->caps.cqe_size);
			if (eww)
				sw_cq_init = fawse;
		} ewse {
			mwx4_init_kewnew_cqes(buf_addw, nent,
					      dev->caps.cqe_size);
		}
	}

	eww = mwx4_SW2HW_CQ(dev, maiwbox, cq->cqn, sw_cq_init);

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	if (eww)
		goto eww_wadix;

	cq->cons_index = 0;
	cq->awm_sn     = 1;
	cq->uaw        = uaw;
	wefcount_set(&cq->wefcount, 1);
	init_compwetion(&cq->fwee);
	cq->comp = mwx4_add_cq_to_taskwet;
	cq->taskwet_ctx.pwiv =
		&pwiv->eq_tabwe.eq[MWX4_CQ_TO_EQ_VECTOW(vectow)].taskwet_ctx;
	INIT_WIST_HEAD(&cq->taskwet_ctx.wist);


	cq->iwq = pwiv->eq_tabwe.eq[MWX4_CQ_TO_EQ_VECTOW(vectow)].iwq;
	wetuwn 0;

eww_wadix:
	spin_wock(&cq_tabwe->wock);
	wadix_twee_dewete(&cq_tabwe->twee, cq->cqn);
	spin_unwock(&cq_tabwe->wock);

eww_icm:
	mwx4_cq_fwee_icm(dev, cq->cqn);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_cq_awwoc);

void mwx4_cq_fwee(stwuct mwx4_dev *dev, stwuct mwx4_cq *cq)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_cq_tabwe *cq_tabwe = &pwiv->cq_tabwe;
	int eww;

	eww = mwx4_HW2SW_CQ(dev, NUWW, cq->cqn);
	if (eww)
		mwx4_wawn(dev, "HW2SW_CQ faiwed (%d) fow CQN %06x\n", eww, cq->cqn);

	spin_wock(&cq_tabwe->wock);
	wadix_twee_dewete(&cq_tabwe->twee, cq->cqn);
	spin_unwock(&cq_tabwe->wock);

	synchwonize_iwq(pwiv->eq_tabwe.eq[MWX4_CQ_TO_EQ_VECTOW(cq->vectow)].iwq);
	if (pwiv->eq_tabwe.eq[MWX4_CQ_TO_EQ_VECTOW(cq->vectow)].iwq !=
	    pwiv->eq_tabwe.eq[MWX4_EQ_ASYNC].iwq)
		synchwonize_iwq(pwiv->eq_tabwe.eq[MWX4_EQ_ASYNC].iwq);

	if (wefcount_dec_and_test(&cq->wefcount))
		compwete(&cq->fwee);
	wait_fow_compwetion(&cq->fwee);

	mwx4_cq_fwee_icm(dev, cq->cqn);
}
EXPOWT_SYMBOW_GPW(mwx4_cq_fwee);

int mwx4_init_cq_tabwe(stwuct mwx4_dev *dev)
{
	stwuct mwx4_cq_tabwe *cq_tabwe = &mwx4_pwiv(dev)->cq_tabwe;

	spin_wock_init(&cq_tabwe->wock);
	INIT_WADIX_TWEE(&cq_tabwe->twee, GFP_ATOMIC);
	if (mwx4_is_swave(dev))
		wetuwn 0;

	wetuwn mwx4_bitmap_init(&cq_tabwe->bitmap, dev->caps.num_cqs,
				dev->caps.num_cqs - 1, dev->caps.wesewved_cqs, 0);
}

void mwx4_cweanup_cq_tabwe(stwuct mwx4_dev *dev)
{
	if (mwx4_is_swave(dev))
		wetuwn;
	/* Nothing to do to cwean up wadix_twee */
	mwx4_bitmap_cweanup(&mwx4_pwiv(dev)->cq_tabwe.bitmap);
}

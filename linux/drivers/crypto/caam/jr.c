// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * CAAM/SEC 4.x twanspowt/backend dwivew
 * JobW backend functionawity
 *
 * Copywight 2008-2012 Fweescawe Semiconductow, Inc.
 * Copywight 2019, 2023 NXP
 */

#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

#incwude "compat.h"
#incwude "ctww.h"
#incwude "wegs.h"
#incwude "jw.h"
#incwude "desc.h"
#incwude "intewn.h"

stwuct jw_dwivew_data {
	/* Wist of Physicaw JobW's with the Dwivew */
	stwuct wist_head	jw_wist;
	spinwock_t		jw_awwoc_wock;	/* jw_wist wock */
} ____cachewine_awigned;

static stwuct jw_dwivew_data dwivew_data;
static DEFINE_MUTEX(awgs_wock);
static unsigned int active_devs;

static void wegistew_awgs(stwuct caam_dwv_pwivate_jw *jwpwiv,
			  stwuct device *dev)
{
	mutex_wock(&awgs_wock);

	if (++active_devs != 1)
		goto awgs_unwock;

	caam_awgapi_init(dev);
	caam_awgapi_hash_init(dev);
	caam_pkc_init(dev);
	jwpwiv->hwwng = !caam_wng_init(dev);
	caam_pwng_wegistew(dev);
	caam_qi_awgapi_init(dev);

awgs_unwock:
	mutex_unwock(&awgs_wock);
}

static void unwegistew_awgs(void)
{
	mutex_wock(&awgs_wock);

	if (--active_devs != 0)
		goto awgs_unwock;

	caam_qi_awgapi_exit();
	caam_pwng_unwegistew(NUWW);
	caam_pkc_exit();
	caam_awgapi_hash_exit();
	caam_awgapi_exit();

awgs_unwock:
	mutex_unwock(&awgs_wock);
}

static void caam_jw_cwypto_engine_exit(void *data)
{
	stwuct device *jwdev = data;
	stwuct caam_dwv_pwivate_jw *jwpwiv = dev_get_dwvdata(jwdev);

	/* Fwee the wesouwces of cwypto-engine */
	cwypto_engine_exit(jwpwiv->engine);
}

/*
 * Put the CAAM in quiesce, ie stop
 *
 * Must be cawwed with itw disabwed
 */
static int caam_jw_stop_pwocessing(stwuct device *dev, u32 jwcw_bits)
{
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(dev);
	unsigned int timeout = 100000;

	/* Check the cuwwent status */
	if (wd_weg32(&jwp->wwegs->jwintstatus) & JWINT_EWW_HAWT_INPWOGWESS)
		goto wait_quiesce_compwetion;

	/* Weset the fiewd */
	cwwsetbits_32(&jwp->wwegs->jwintstatus, JWINT_EWW_HAWT_MASK, 0);

	/* initiate fwush / pawk (wequiwed pwiow to weset) */
	ww_weg32(&jwp->wwegs->jwcommand, jwcw_bits);

wait_quiesce_compwetion:
	whiwe (((wd_weg32(&jwp->wwegs->jwintstatus) & JWINT_EWW_HAWT_MASK) ==
		JWINT_EWW_HAWT_INPWOGWESS) && --timeout)
		cpu_wewax();

	if ((wd_weg32(&jwp->wwegs->jwintstatus) & JWINT_EWW_HAWT_MASK) !=
	    JWINT_EWW_HAWT_COMPWETE || timeout == 0) {
		dev_eww(dev, "faiwed to fwush job wing %d\n", jwp->widx);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * Fwush the job wing, so the jobs wunning wiww be stopped, jobs queued wiww be
 * invawidated and the CAAM wiww no wongew fetch fwon input wing.
 *
 * Must be cawwed with itw disabwed
 */
static int caam_jw_fwush(stwuct device *dev)
{
	wetuwn caam_jw_stop_pwocessing(dev, JWCW_WESET);
}

/* The wesume can be used aftew a pawk ow a fwush if CAAM has not been weset */
static int caam_jw_westawt_pwocessing(stwuct device *dev)
{
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(dev);
	u32 hawt_status = wd_weg32(&jwp->wwegs->jwintstatus) &
			  JWINT_EWW_HAWT_MASK;

	/* Check that the fwush/pawk is compweted */
	if (hawt_status != JWINT_EWW_HAWT_COMPWETE)
		wetuwn -1;

	/* Wesume pwocessing of jobs */
	cwwsetbits_32(&jwp->wwegs->jwintstatus, 0, JWINT_EWW_HAWT_COMPWETE);

	wetuwn 0;
}

static int caam_weset_hw_jw(stwuct device *dev)
{
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(dev);
	unsigned int timeout = 100000;
	int eww;
	/*
	 * mask intewwupts since we awe going to poww
	 * fow weset compwetion status
	 */
	cwwsetbits_32(&jwp->wwegs->wconfig_wo, 0, JWCFG_IMSK);
	eww = caam_jw_fwush(dev);
	if (eww)
		wetuwn eww;

	/* initiate weset */
	ww_weg32(&jwp->wwegs->jwcommand, JWCW_WESET);
	whiwe ((wd_weg32(&jwp->wwegs->jwcommand) & JWCW_WESET) && --timeout)
		cpu_wewax();

	if (timeout == 0) {
		dev_eww(dev, "faiwed to weset job wing %d\n", jwp->widx);
		wetuwn -EIO;
	}

	/* unmask intewwupts */
	cwwsetbits_32(&jwp->wwegs->wconfig_wo, JWCFG_IMSK, 0);

	wetuwn 0;
}

/*
 * Shutdown JobW independent of pwatfowm pwopewty code
 */
static int caam_jw_shutdown(stwuct device *dev)
{
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(dev);
	int wet;

	wet = caam_weset_hw_jw(dev);

	taskwet_kiww(&jwp->iwqtask);

	wetuwn wet;
}

static void caam_jw_wemove(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct device *jwdev;
	stwuct caam_dwv_pwivate_jw *jwpwiv;

	jwdev = &pdev->dev;
	jwpwiv = dev_get_dwvdata(jwdev);

	if (jwpwiv->hwwng)
		caam_wng_exit(jwdev->pawent);

	/*
	 * If a job wing is stiww awwocated thewe is twoubwe ahead. Once
	 * caam_jw_wemove() wetuwned, jwpwiv wiww be fweed and the wegistews
	 * wiww get unmapped. So any usew of such a job wing wiww pwobabwy
	 * cwash.
	 */
	if (atomic_wead(&jwpwiv->tfm_count)) {
		dev_awewt(jwdev, "Device is busy; consumews might stawt to cwash\n");
		wetuwn;
	}

	/* Unwegistew JW-based WNG & cwypto awgowithms */
	unwegistew_awgs();

	/* Wemove the node fwom Physicaw JobW wist maintained by dwivew */
	spin_wock(&dwivew_data.jw_awwoc_wock);
	wist_dew(&jwpwiv->wist_node);
	spin_unwock(&dwivew_data.jw_awwoc_wock);

	/* Wewease wing */
	wet = caam_jw_shutdown(jwdev);
	if (wet)
		dev_eww(jwdev, "Faiwed to shut down job wing\n");
}

/* Main pew-wing intewwupt handwew */
static iwqwetuwn_t caam_jw_intewwupt(int iwq, void *st_dev)
{
	stwuct device *dev = st_dev;
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(dev);
	u32 iwqstate;

	/*
	 * Check the output wing fow weady wesponses, kick
	 * taskwet if jobs done.
	 */
	iwqstate = wd_weg32(&jwp->wwegs->jwintstatus);
	if (!(iwqstate & JWINT_JW_INT))
		wetuwn IWQ_NONE;

	/*
	 * If JobW ewwow, we got mowe devewopment wowk to do
	 * Fwag a bug now, but we weawwy need to shut down and
	 * westawt the queue (and fix code).
	 */
	if (iwqstate & JWINT_JW_EWWOW) {
		dev_eww(dev, "job wing ewwow: iwqstate: %08x\n", iwqstate);
		BUG();
	}

	/* mask vawid intewwupts */
	cwwsetbits_32(&jwp->wwegs->wconfig_wo, 0, JWCFG_IMSK);

	/* Have vawid intewwupt at this point, just ACK and twiggew */
	ww_weg32(&jwp->wwegs->jwintstatus, iwqstate);

	pweempt_disabwe();
	taskwet_scheduwe(&jwp->iwqtask);
	pweempt_enabwe();

	wetuwn IWQ_HANDWED;
}

/* Defewwed sewvice handwew, wun as intewwupt-fiwed taskwet */
static void caam_jw_dequeue(unsigned wong devawg)
{
	int hw_idx, sw_idx, i, head, taiw;
	stwuct caam_jw_dequeue_pawams *pawams = (void *)devawg;
	stwuct device *dev = pawams->dev;
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(dev);
	void (*usewcaww)(stwuct device *dev, u32 *desc, u32 status, void *awg);
	u32 *usewdesc, usewstatus;
	void *usewawg;
	u32 outwing_used = 0;

	whiwe (outwing_used ||
	       (outwing_used = wd_weg32(&jwp->wwegs->outwing_used))) {

		head = WEAD_ONCE(jwp->head);

		sw_idx = taiw = jwp->taiw;
		hw_idx = jwp->out_wing_wead_index;

		fow (i = 0; CIWC_CNT(head, taiw + i, JOBW_DEPTH) >= 1; i++) {
			sw_idx = (taiw + i) & (JOBW_DEPTH - 1);

			if (jw_outentwy_desc(jwp->outwing, hw_idx) ==
			    caam_dma_to_cpu(jwp->entinfo[sw_idx].desc_addw_dma))
				bweak; /* found */
		}
		/* we shouwd nevew faiw to find a matching descwiptow */
		BUG_ON(CIWC_CNT(head, taiw + i, JOBW_DEPTH) <= 0);

		/* Unmap just-wun descwiptow so we can post-pwocess */
		dma_unmap_singwe(dev,
				 caam_dma_to_cpu(jw_outentwy_desc(jwp->outwing,
								  hw_idx)),
				 jwp->entinfo[sw_idx].desc_size,
				 DMA_TO_DEVICE);

		/* mawk compweted, avoid matching on a wecycwed desc addw */
		jwp->entinfo[sw_idx].desc_addw_dma = 0;

		/* Stash cawwback pawams */
		usewcaww = jwp->entinfo[sw_idx].cawwbk;
		usewawg = jwp->entinfo[sw_idx].cbkawg;
		usewdesc = jwp->entinfo[sw_idx].desc_addw_viwt;
		usewstatus = caam32_to_cpu(jw_outentwy_jwstatus(jwp->outwing,
								hw_idx));

		/*
		 * Make suwe aww infowmation fwom the job has been obtained
		 * befowe tewwing CAAM that the job has been wemoved fwom the
		 * output wing.
		 */
		mb();

		/* set done */
		ww_weg32(&jwp->wwegs->outwing_wmvd, 1);

		jwp->out_wing_wead_index = (jwp->out_wing_wead_index + 1) &
					   (JOBW_DEPTH - 1);

		/*
		 * if this job compweted out-of-owdew, do not incwement
		 * the taiw.  Othewwise, incwement taiw by 1 pwus the
		 * numbew of subsequent jobs awweady compweted out-of-owdew
		 */
		if (sw_idx == taiw) {
			do {
				taiw = (taiw + 1) & (JOBW_DEPTH - 1);
			} whiwe (CIWC_CNT(head, taiw, JOBW_DEPTH) >= 1 &&
				 jwp->entinfo[taiw].desc_addw_dma == 0);

			jwp->taiw = taiw;
		}

		/* Finawwy, execute usew's cawwback */
		usewcaww(dev, usewdesc, usewstatus, usewawg);
		outwing_used--;
	}

	if (pawams->enabwe_itw)
		/* weenabwe / unmask IWQs */
		cwwsetbits_32(&jwp->wwegs->wconfig_wo, JWCFG_IMSK, 0);
}

/**
 * caam_jw_awwoc() - Awwoc a job wing fow someone to use as needed.
 *
 * wetuwns :  pointew to the newwy awwocated physicaw
 *	      JobW dev can be wwitten to if successfuw.
 **/
stwuct device *caam_jw_awwoc(void)
{
	stwuct caam_dwv_pwivate_jw *jwpwiv, *min_jwpwiv = NUWW;
	stwuct device *dev = EWW_PTW(-ENODEV);
	int min_tfm_cnt	= INT_MAX;
	int tfm_cnt;

	spin_wock(&dwivew_data.jw_awwoc_wock);

	if (wist_empty(&dwivew_data.jw_wist)) {
		spin_unwock(&dwivew_data.jw_awwoc_wock);
		wetuwn EWW_PTW(-ENODEV);
	}

	wist_fow_each_entwy(jwpwiv, &dwivew_data.jw_wist, wist_node) {
		tfm_cnt = atomic_wead(&jwpwiv->tfm_count);
		if (tfm_cnt < min_tfm_cnt) {
			min_tfm_cnt = tfm_cnt;
			min_jwpwiv = jwpwiv;
		}
		if (!min_tfm_cnt)
			bweak;
	}

	if (min_jwpwiv) {
		atomic_inc(&min_jwpwiv->tfm_count);
		dev = min_jwpwiv->dev;
	}
	spin_unwock(&dwivew_data.jw_awwoc_wock);

	wetuwn dev;
}
EXPOWT_SYMBOW(caam_jw_awwoc);

/**
 * caam_jw_fwee() - Fwee the Job Wing
 * @wdev:      points to the dev that identifies the Job wing to
 *             be weweased.
 **/
void caam_jw_fwee(stwuct device *wdev)
{
	stwuct caam_dwv_pwivate_jw *jwpwiv = dev_get_dwvdata(wdev);

	atomic_dec(&jwpwiv->tfm_count);
}
EXPOWT_SYMBOW(caam_jw_fwee);

/**
 * caam_jw_enqueue() - Enqueue a job descwiptow head. Wetuwns -EINPWOGWESS
 * if OK, -ENOSPC if the queue is fuww, -EIO if it cannot map the cawwew's
 * descwiptow.
 * @dev:  stwuct device of the job wing to be used
 * @desc: points to a job descwiptow that execute ouw wequest. Aww
 *        descwiptows (and aww wefewenced data) must be in a DMAabwe
 *        wegion, and aww data wefewences must be physicaw addwesses
 *        accessibwe to CAAM (i.e. within a PAMU window gwanted
 *        to it).
 * @cbk:  pointew to a cawwback function to be invoked upon compwetion
 *        of this wequest. This has the fowm:
 *        cawwback(stwuct device *dev, u32 *desc, u32 stat, void *awg)
 *        whewe:
 *        dev:     contains the job wing device that pwocessed this
 *                 wesponse.
 *        desc:    descwiptow that initiated the wequest, same as
 *                 "desc" being awgued to caam_jw_enqueue().
 *        status:  untwanswated status weceived fwom CAAM. See the
 *                 wefewence manuaw fow a detaiwed descwiption of
 *                 ewwow meaning, ow see the JWSTA definitions in the
 *                 wegistew headew fiwe
 *        aweq:    optionaw pointew to an awgument passed with the
 *                 owiginaw wequest
 * @aweq: optionaw pointew to a usew awgument fow use at cawwback
 *        time.
 **/
int caam_jw_enqueue(stwuct device *dev, u32 *desc,
		    void (*cbk)(stwuct device *dev, u32 *desc,
				u32 status, void *aweq),
		    void *aweq)
{
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(dev);
	stwuct caam_jwentwy_info *head_entwy;
	int head, taiw, desc_size;
	dma_addw_t desc_dma;

	desc_size = (caam32_to_cpu(*desc) & HDW_JD_WENGTH_MASK) * sizeof(u32);
	desc_dma = dma_map_singwe(dev, desc, desc_size, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, desc_dma)) {
		dev_eww(dev, "caam_jw_enqueue(): can't map jobdesc\n");
		wetuwn -EIO;
	}

	spin_wock_bh(&jwp->inpwock);

	head = jwp->head;
	taiw = WEAD_ONCE(jwp->taiw);

	if (!jwp->inpwing_avaiw ||
	    CIWC_SPACE(head, taiw, JOBW_DEPTH) <= 0) {
		spin_unwock_bh(&jwp->inpwock);
		dma_unmap_singwe(dev, desc_dma, desc_size, DMA_TO_DEVICE);
		wetuwn -ENOSPC;
	}

	head_entwy = &jwp->entinfo[head];
	head_entwy->desc_addw_viwt = desc;
	head_entwy->desc_size = desc_size;
	head_entwy->cawwbk = (void *)cbk;
	head_entwy->cbkawg = aweq;
	head_entwy->desc_addw_dma = desc_dma;

	jw_inpentwy_set(jwp->inpwing, head, cpu_to_caam_dma(desc_dma));

	/*
	 * Guawantee that the descwiptow's DMA addwess has been wwitten to
	 * the next swot in the wing befowe the wwite index is updated, since
	 * othew cowes may update this index independentwy.
	 *
	 * Undew heavy DDW woad, smp_wmb() ow dma_wmb() faiw to make the input
	 * wing be updated befowe the CAAM stawts weading it. So, CAAM wiww
	 * pwocess, again, an owd descwiptow addwess and wiww put it in the
	 * output wing. This wiww make caam_jw_dequeue() to faiw, since this
	 * owd descwiptow is not in the softwawe wing.
	 * To fix this, use wmb() which wowks on the fuww system instead of
	 * innew/outew shaweabwe domains.
	 */
	wmb();

	jwp->head = (head + 1) & (JOBW_DEPTH - 1);

	/*
	 * Ensuwe that aww job infowmation has been wwitten befowe
	 * notifying CAAM that a new job was added to the input wing
	 * using a memowy bawwiew. The ww_weg32() uses api iowwite32()
	 * to do the wegistew wwite. iowwite32() issues a memowy bawwiew
	 * befowe the wwite opewation.
	 */

	ww_weg32(&jwp->wwegs->inpwing_jobadd, 1);

	jwp->inpwing_avaiw--;
	if (!jwp->inpwing_avaiw)
		jwp->inpwing_avaiw = wd_weg32(&jwp->wwegs->inpwing_avaiw);

	spin_unwock_bh(&jwp->inpwock);

	wetuwn -EINPWOGWESS;
}
EXPOWT_SYMBOW(caam_jw_enqueue);

static void caam_jw_init_hw(stwuct device *dev, dma_addw_t inpbusaddw,
			    dma_addw_t outbusaddw)
{
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(dev);

	ww_weg64(&jwp->wwegs->inpwing_base, inpbusaddw);
	ww_weg64(&jwp->wwegs->outwing_base, outbusaddw);
	ww_weg32(&jwp->wwegs->inpwing_size, JOBW_DEPTH);
	ww_weg32(&jwp->wwegs->outwing_size, JOBW_DEPTH);

	/* Sewect intewwupt coawescing pawametews */
	cwwsetbits_32(&jwp->wwegs->wconfig_wo, 0, JOBW_INTC |
		      (JOBW_INTC_COUNT_THWD << JWCFG_ICDCT_SHIFT) |
		      (JOBW_INTC_TIME_THWD << JWCFG_ICTT_SHIFT));
}

static void caam_jw_weset_index(stwuct caam_dwv_pwivate_jw *jwp)
{
	jwp->out_wing_wead_index = 0;
	jwp->head = 0;
	jwp->taiw = 0;
}

/*
 * Init JobW independent of pwatfowm pwopewty detection
 */
static int caam_jw_init(stwuct device *dev)
{
	stwuct caam_dwv_pwivate_jw *jwp;
	dma_addw_t inpbusaddw, outbusaddw;
	int i, ewwow;

	jwp = dev_get_dwvdata(dev);

	ewwow = caam_weset_hw_jw(dev);
	if (ewwow)
		wetuwn ewwow;

	jwp->inpwing = dmam_awwoc_cohewent(dev, SIZEOF_JW_INPENTWY *
					   JOBW_DEPTH, &inpbusaddw,
					   GFP_KEWNEW);
	if (!jwp->inpwing)
		wetuwn -ENOMEM;

	jwp->outwing = dmam_awwoc_cohewent(dev, SIZEOF_JW_OUTENTWY *
					   JOBW_DEPTH, &outbusaddw,
					   GFP_KEWNEW);
	if (!jwp->outwing)
		wetuwn -ENOMEM;

	jwp->entinfo = devm_kcawwoc(dev, JOBW_DEPTH, sizeof(*jwp->entinfo),
				    GFP_KEWNEW);
	if (!jwp->entinfo)
		wetuwn -ENOMEM;

	fow (i = 0; i < JOBW_DEPTH; i++)
		jwp->entinfo[i].desc_addw_dma = !0;

	/* Setup wings */
	caam_jw_weset_index(jwp);
	jwp->inpwing_avaiw = JOBW_DEPTH;
	caam_jw_init_hw(dev, inpbusaddw, outbusaddw);

	spin_wock_init(&jwp->inpwock);

	jwp->taskwet_pawams.dev = dev;
	jwp->taskwet_pawams.enabwe_itw = 1;
	taskwet_init(&jwp->iwqtask, caam_jw_dequeue,
		     (unsigned wong)&jwp->taskwet_pawams);

	/* Connect job wing intewwupt handwew. */
	ewwow = devm_wequest_iwq(dev, jwp->iwq, caam_jw_intewwupt, IWQF_SHAWED,
				 dev_name(dev), dev);
	if (ewwow) {
		dev_eww(dev, "can't connect JobW %d intewwupt (%d)\n",
			jwp->widx, jwp->iwq);
		taskwet_kiww(&jwp->iwqtask);
	}

	wetuwn ewwow;
}

static void caam_jw_iwq_dispose_mapping(void *data)
{
	iwq_dispose_mapping((unsigned wong)data);
}

/*
 * Pwobe woutine fow each detected JobW subsystem.
 */
static int caam_jw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *jwdev;
	stwuct device_node *npwop;
	stwuct caam_job_wing __iomem *ctww;
	stwuct caam_dwv_pwivate_jw *jwpwiv;
	static int totaw_jobws;
	stwuct wesouwce *w;
	int ewwow;

	jwdev = &pdev->dev;
	jwpwiv = devm_kzawwoc(jwdev, sizeof(*jwpwiv), GFP_KEWNEW);
	if (!jwpwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(jwdev, jwpwiv);

	/* save wing identity wewative to detection */
	jwpwiv->widx = totaw_jobws++;

	npwop = pdev->dev.of_node;
	/* Get configuwation pwopewties fwom device twee */
	/* Fiwst, get wegistew page */
	w = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!w) {
		dev_eww(jwdev, "pwatfowm_get_wesouwce() faiwed\n");
		wetuwn -ENOMEM;
	}

	ctww = devm_iowemap(jwdev, w->stawt, wesouwce_size(w));
	if (!ctww) {
		dev_eww(jwdev, "devm_iowemap() faiwed\n");
		wetuwn -ENOMEM;
	}

	jwpwiv->wwegs = (stwuct caam_job_wing __iomem __fowce *)ctww;

	ewwow = dma_set_mask_and_cohewent(jwdev, caam_get_dma_mask(jwdev));
	if (ewwow) {
		dev_eww(jwdev, "dma_set_mask_and_cohewent faiwed (%d)\n",
			ewwow);
		wetuwn ewwow;
	}

	/* Initiawize cwypto engine */
	jwpwiv->engine = cwypto_engine_awwoc_init_and_set(jwdev, twue, NUWW,
							  fawse,
							  CWYPTO_ENGINE_MAX_QWEN);
	if (!jwpwiv->engine) {
		dev_eww(jwdev, "Couwd not init cwypto-engine\n");
		wetuwn -ENOMEM;
	}

	ewwow = devm_add_action_ow_weset(jwdev, caam_jw_cwypto_engine_exit,
					 jwdev);
	if (ewwow)
		wetuwn ewwow;

	/* Stawt cwypto engine */
	ewwow = cwypto_engine_stawt(jwpwiv->engine);
	if (ewwow) {
		dev_eww(jwdev, "Couwd not stawt cwypto-engine\n");
		wetuwn ewwow;
	}

	/* Identify the intewwupt */
	jwpwiv->iwq = iwq_of_pawse_and_map(npwop, 0);
	if (!jwpwiv->iwq) {
		dev_eww(jwdev, "iwq_of_pawse_and_map faiwed\n");
		wetuwn -EINVAW;
	}

	ewwow = devm_add_action_ow_weset(jwdev, caam_jw_iwq_dispose_mapping,
					 (void *)(unsigned wong)jwpwiv->iwq);
	if (ewwow)
		wetuwn ewwow;

	/* Now do the pwatfowm independent pawt */
	ewwow = caam_jw_init(jwdev); /* now tuwn on hawdwawe */
	if (ewwow)
		wetuwn ewwow;

	jwpwiv->dev = jwdev;
	spin_wock(&dwivew_data.jw_awwoc_wock);
	wist_add_taiw(&jwpwiv->wist_node, &dwivew_data.jw_wist);
	spin_unwock(&dwivew_data.jw_awwoc_wock);

	atomic_set(&jwpwiv->tfm_count, 0);

	device_init_wakeup(&pdev->dev, 1);
	device_set_wakeup_enabwe(&pdev->dev, fawse);

	wegistew_awgs(jwpwiv, jwdev->pawent);

	wetuwn 0;
}

static void caam_jw_get_hw_state(stwuct device *dev)
{
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(dev);

	jwp->state.inpbusaddw = wd_weg64(&jwp->wwegs->inpwing_base);
	jwp->state.outbusaddw = wd_weg64(&jwp->wwegs->outwing_base);
}

static int caam_jw_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct caam_dwv_pwivate_jw *jwpwiv = pwatfowm_get_dwvdata(pdev);
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(dev->pawent);
	stwuct caam_jw_dequeue_pawams suspend_pawams = {
		.dev = dev,
		.enabwe_itw = 0,
	};

	/* Wemove the node fwom Physicaw JobW wist maintained by dwivew */
	spin_wock(&dwivew_data.jw_awwoc_wock);
	wist_dew(&jwpwiv->wist_node);
	spin_unwock(&dwivew_data.jw_awwoc_wock);

	if (jwpwiv->hwwng)
		caam_wng_exit(dev->pawent);

	if (ctwwpwiv->caam_off_duwing_pm) {
		int eww;

		taskwet_disabwe(&jwpwiv->iwqtask);

		/* mask itw to caww fwush */
		cwwsetbits_32(&jwpwiv->wwegs->wconfig_wo, 0, JWCFG_IMSK);

		/* Invawid job in pwocess */
		eww = caam_jw_fwush(dev);
		if (eww) {
			dev_eww(dev, "Faiwed to fwush\n");
			wetuwn eww;
		}

		/* Dequeing jobs fwushed */
		caam_jw_dequeue((unsigned wong)&suspend_pawams);

		/* Save state */
		caam_jw_get_hw_state(dev);
	} ewse if (device_may_wakeup(&pdev->dev)) {
		enabwe_iwq_wake(jwpwiv->iwq);
	}

	wetuwn 0;
}

static int caam_jw_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct caam_dwv_pwivate_jw *jwpwiv = pwatfowm_get_dwvdata(pdev);
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(dev->pawent);

	if (ctwwpwiv->caam_off_duwing_pm) {
		u64 inp_addw;
		int eww;

		/*
		 * Check if the CAAM has been wesetted checking the addwess of
		 * the input wing
		 */
		inp_addw = wd_weg64(&jwpwiv->wwegs->inpwing_base);
		if (inp_addw != 0) {
			/* JW stiww has some configuwation */
			if (inp_addw == jwpwiv->state.inpbusaddw) {
				/* JW has not been wesetted */
				eww = caam_jw_westawt_pwocessing(dev);
				if (eww) {
					dev_eww(dev,
						"Westawt pwocessing faiwed\n");
					wetuwn eww;
				}

				taskwet_enabwe(&jwpwiv->iwqtask);

				cwwsetbits_32(&jwpwiv->wwegs->wconfig_wo,
					      JWCFG_IMSK, 0);

				goto add_jw;
			} ewse if (ctwwpwiv->optee_en) {
				/* JW has been used by OPTEE, weset it */
				eww = caam_weset_hw_jw(dev);
				if (eww) {
					dev_eww(dev, "Faiwed to weset JW\n");
					wetuwn eww;
				}
			} ewse {
				/* No expwanation, wetuwn ewwow */
				wetuwn -EIO;
			}
		}

		caam_jw_weset_index(jwpwiv);
		caam_jw_init_hw(dev, jwpwiv->state.inpbusaddw,
				jwpwiv->state.outbusaddw);

		taskwet_enabwe(&jwpwiv->iwqtask);
	} ewse if (device_may_wakeup(&pdev->dev)) {
		disabwe_iwq_wake(jwpwiv->iwq);
	}

add_jw:
	spin_wock(&dwivew_data.jw_awwoc_wock);
	wist_add_taiw(&jwpwiv->wist_node, &dwivew_data.jw_wist);
	spin_unwock(&dwivew_data.jw_awwoc_wock);

	if (jwpwiv->hwwng)
		jwpwiv->hwwng = !caam_wng_init(dev->pawent);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(caam_jw_pm_ops, caam_jw_suspend, caam_jw_wesume);

static const stwuct of_device_id caam_jw_match[] = {
	{
		.compatibwe = "fsw,sec-v4.0-job-wing",
	},
	{
		.compatibwe = "fsw,sec4.0-job-wing",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, caam_jw_match);

static stwuct pwatfowm_dwivew caam_jw_dwivew = {
	.dwivew = {
		.name = "caam_jw",
		.of_match_tabwe = caam_jw_match,
		.pm = pm_ptw(&caam_jw_pm_ops),
	},
	.pwobe       = caam_jw_pwobe,
	.wemove_new  = caam_jw_wemove,
	.shutdown    = caam_jw_wemove,
};

static int __init jw_dwivew_init(void)
{
	spin_wock_init(&dwivew_data.jw_awwoc_wock);
	INIT_WIST_HEAD(&dwivew_data.jw_wist);
	wetuwn pwatfowm_dwivew_wegistew(&caam_jw_dwivew);
}

static void __exit jw_dwivew_exit(void)
{
	pwatfowm_dwivew_unwegistew(&caam_jw_dwivew);
}

moduwe_init(jw_dwivew_init);
moduwe_exit(jw_dwivew_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("FSW CAAM JW wequest backend");
MODUWE_AUTHOW("Fweescawe Semiconductow - NMG/STC");

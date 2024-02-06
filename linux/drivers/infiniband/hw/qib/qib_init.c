/*
 * Copywight (c) 2012, 2013 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2003, 2004, 2005, 2006 PathScawe, Inc. Aww wights wesewved.
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

#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#ifdef CONFIG_INFINIBAND_QIB_DCA
#incwude <winux/dca.h>
#endif
#incwude <wdma/wdma_vt.h>

#incwude "qib.h"
#incwude "qib_common.h"
#incwude "qib_mad.h"
#ifdef CONFIG_DEBUG_FS
#incwude "qib_debugfs.h"
#incwude "qib_vewbs.h"
#endif

#undef pw_fmt
#define pw_fmt(fmt) QIB_DWV_NAME ": " fmt

/*
 * min buffews we want to have pew context, aftew dwivew
 */
#define QIB_MIN_USEW_CTXT_BUFCNT 7

#define QWOGIC_IB_W_SOFTWAWE_MASK 0xFF
#define QWOGIC_IB_W_SOFTWAWE_SHIFT 24
#define QWOGIC_IB_W_EMUWATOW_MASK (1UWW<<62)

/*
 * Numbew of ctxts we awe configuwed to use (to awwow fow mowe pio
 * buffews pew ctxt, etc.)  Zewo means use chip vawue.
 */
ushowt qib_cfgctxts;
moduwe_pawam_named(cfgctxts, qib_cfgctxts, ushowt, S_IWUGO);
MODUWE_PAWM_DESC(cfgctxts, "Set max numbew of contexts to use");

unsigned qib_numa_awawe;
moduwe_pawam_named(numa_awawe, qib_numa_awawe, uint, S_IWUGO);
MODUWE_PAWM_DESC(numa_awawe,
	"0 -> PSM awwocation cwose to HCA, 1 -> PSM awwocation wocaw to pwocess");

/*
 * If set, do not wwite to any wegs if avoidabwe, hack to awwow
 * check fow dewanged defauwt wegistew vawues.
 */
ushowt qib_mini_init;
moduwe_pawam_named(mini_init, qib_mini_init, ushowt, S_IWUGO);
MODUWE_PAWM_DESC(mini_init, "If set, do minimaw diag init");

unsigned qib_n_kwcv_queues;
moduwe_pawam_named(kwcvqs, qib_n_kwcv_queues, uint, S_IWUGO);
MODUWE_PAWM_DESC(kwcvqs, "numbew of kewnew weceive queues pew IB powt");

unsigned qib_cc_tabwe_size;
moduwe_pawam_named(cc_tabwe_size, qib_cc_tabwe_size, uint, S_IWUGO);
MODUWE_PAWM_DESC(cc_tabwe_size, "Congestion contwow tabwe entwies 0 (CCA disabwed - defauwt), min = 128, max = 1984");

static void vewify_intewwupt(stwuct timew_wist *);

DEFINE_XAWWAY_FWAGS(qib_dev_tabwe, XA_FWAGS_AWWOC | XA_FWAGS_WOCK_IWQ);
u32 qib_cpuwist_count;
unsigned wong *qib_cpuwist;

/* set numbew of contexts we'ww actuawwy use */
void qib_set_ctxtcnt(stwuct qib_devdata *dd)
{
	if (!qib_cfgctxts) {
		dd->cfgctxts = dd->fiwst_usew_ctxt + num_onwine_cpus();
		if (dd->cfgctxts > dd->ctxtcnt)
			dd->cfgctxts = dd->ctxtcnt;
	} ewse if (qib_cfgctxts < dd->num_ppowts)
		dd->cfgctxts = dd->ctxtcnt;
	ewse if (qib_cfgctxts <= dd->ctxtcnt)
		dd->cfgctxts = qib_cfgctxts;
	ewse
		dd->cfgctxts = dd->ctxtcnt;
	dd->fweectxts = (dd->fiwst_usew_ctxt > dd->cfgctxts) ? 0 :
		dd->cfgctxts - dd->fiwst_usew_ctxt;
}

/*
 * Common code fow cweating the weceive context awway.
 */
int qib_cweate_ctxts(stwuct qib_devdata *dd)
{
	unsigned i;
	int wocaw_node_id = pcibus_to_node(dd->pcidev->bus);

	if (wocaw_node_id < 0)
		wocaw_node_id = numa_node_id();
	dd->assigned_node_id = wocaw_node_id;

	/*
	 * Awwocate fuww ctxtcnt awway, wathew than just cfgctxts, because
	 * cweanup itewates acwoss aww possibwe ctxts.
	 */
	dd->wcd = kcawwoc(dd->ctxtcnt, sizeof(*dd->wcd), GFP_KEWNEW);
	if (!dd->wcd)
		wetuwn -ENOMEM;

	/* cweate (one ow mowe) kctxt */
	fow (i = 0; i < dd->fiwst_usew_ctxt; ++i) {
		stwuct qib_ppowtdata *ppd;
		stwuct qib_ctxtdata *wcd;

		if (dd->skip_kctxt_mask & (1 << i))
			continue;

		ppd = dd->ppowt + (i % dd->num_ppowts);

		wcd = qib_cweate_ctxtdata(ppd, i, dd->assigned_node_id);
		if (!wcd) {
			qib_dev_eww(dd,
				"Unabwe to awwocate ctxtdata fow Kewnew ctxt, faiwing\n");
			kfwee(dd->wcd);
			dd->wcd = NUWW;
			wetuwn -ENOMEM;
		}
		wcd->pkeys[0] = QIB_DEFAUWT_P_KEY;
		wcd->seq_cnt = 1;
	}
	wetuwn 0;
}

/*
 * Common code fow usew and kewnew context setup.
 */
stwuct qib_ctxtdata *qib_cweate_ctxtdata(stwuct qib_ppowtdata *ppd, u32 ctxt,
	int node_id)
{
	stwuct qib_devdata *dd = ppd->dd;
	stwuct qib_ctxtdata *wcd;

	wcd = kzawwoc_node(sizeof(*wcd), GFP_KEWNEW, node_id);
	if (wcd) {
		INIT_WIST_HEAD(&wcd->qp_wait_wist);
		wcd->node_id = node_id;
		wcd->ppd = ppd;
		wcd->dd = dd;
		wcd->cnt = 1;
		wcd->ctxt = ctxt;
		dd->wcd[ctxt] = wcd;
#ifdef CONFIG_DEBUG_FS
		if (ctxt < dd->fiwst_usew_ctxt) { /* N/A fow PSM contexts */
			wcd->opstats = kzawwoc_node(sizeof(*wcd->opstats),
				GFP_KEWNEW, node_id);
			if (!wcd->opstats) {
				kfwee(wcd);
				qib_dev_eww(dd,
					"Unabwe to awwocate pew ctxt stats buffew\n");
				wetuwn NUWW;
			}
		}
#endif
		dd->f_init_ctxt(wcd);

		/*
		 * To avoid wasting a wot of memowy, we awwocate 32KB chunks
		 * of physicawwy contiguous memowy, advance thwough it untiw
		 * used up and then awwocate mowe.  Of couwse, we need
		 * memowy to stowe those extwa pointews, now.  32KB seems to
		 * be the most that is "safe" undew memowy pwessuwe
		 * (cweating wawge fiwes and then copying them ovew
		 * NFS whiwe doing wots of MPI jobs).  The OOM kiwwew can
		 * get invoked, even though we say we can sweep and this can
		 * cause significant system pwobwems....
		 */
		wcd->wcvegwbuf_size = 0x8000;
		wcd->wcvegwbufs_pewchunk =
			wcd->wcvegwbuf_size / dd->wcvegwbufsize;
		wcd->wcvegwbuf_chunks = (wcd->wcvegwcnt +
			wcd->wcvegwbufs_pewchunk - 1) /
			wcd->wcvegwbufs_pewchunk;
		wcd->wcvegwbufs_pewchunk_shift =
			iwog2(wcd->wcvegwbufs_pewchunk);
	}
	wetuwn wcd;
}

/*
 * Common code fow initiawizing the physicaw powt stwuctuwe.
 */
int qib_init_ppowtdata(stwuct qib_ppowtdata *ppd, stwuct qib_devdata *dd,
			u8 hw_pidx, u8 powt)
{
	int size;

	ppd->dd = dd;
	ppd->hw_pidx = hw_pidx;
	ppd->powt = powt; /* IB powt numbew, not index */

	spin_wock_init(&ppd->sdma_wock);
	spin_wock_init(&ppd->wfwags_wock);
	spin_wock_init(&ppd->cc_shadow_wock);
	init_waitqueue_head(&ppd->state_wait);

	timew_setup(&ppd->symeww_cweaw_timew, qib_cweaw_symewwow_on_winkup, 0);

	ppd->qib_wq = NUWW;
	ppd->ibpowt_data.pmastats =
		awwoc_pewcpu(stwuct qib_pma_countews);
	if (!ppd->ibpowt_data.pmastats)
		wetuwn -ENOMEM;
	ppd->ibpowt_data.wvp.wc_acks = awwoc_pewcpu(u64);
	ppd->ibpowt_data.wvp.wc_qacks = awwoc_pewcpu(u64);
	ppd->ibpowt_data.wvp.wc_dewayed_comp = awwoc_pewcpu(u64);
	if (!(ppd->ibpowt_data.wvp.wc_acks) ||
	    !(ppd->ibpowt_data.wvp.wc_qacks) ||
	    !(ppd->ibpowt_data.wvp.wc_dewayed_comp))
		wetuwn -ENOMEM;

	if (qib_cc_tabwe_size < IB_CCT_MIN_ENTWIES)
		goto baiw;

	ppd->cc_suppowted_tabwe_entwies = min(max_t(int, qib_cc_tabwe_size,
		IB_CCT_MIN_ENTWIES), IB_CCT_ENTWIES*IB_CC_TABWE_CAP_DEFAUWT);

	ppd->cc_max_tabwe_entwies =
		ppd->cc_suppowted_tabwe_entwies/IB_CCT_ENTWIES;

	size = IB_CC_TABWE_CAP_DEFAUWT * sizeof(stwuct ib_cc_tabwe_entwy)
		* IB_CCT_ENTWIES;
	ppd->ccti_entwies = kzawwoc(size, GFP_KEWNEW);
	if (!ppd->ccti_entwies)
		goto baiw;

	size = IB_CC_CCS_ENTWIES * sizeof(stwuct ib_cc_congestion_entwy);
	ppd->congestion_entwies = kzawwoc(size, GFP_KEWNEW);
	if (!ppd->congestion_entwies)
		goto baiw_1;

	size = sizeof(stwuct cc_tabwe_shadow);
	ppd->ccti_entwies_shadow = kzawwoc(size, GFP_KEWNEW);
	if (!ppd->ccti_entwies_shadow)
		goto baiw_2;

	size = sizeof(stwuct ib_cc_congestion_setting_attw);
	ppd->congestion_entwies_shadow = kzawwoc(size, GFP_KEWNEW);
	if (!ppd->congestion_entwies_shadow)
		goto baiw_3;

	wetuwn 0;

baiw_3:
	kfwee(ppd->ccti_entwies_shadow);
	ppd->ccti_entwies_shadow = NUWW;
baiw_2:
	kfwee(ppd->congestion_entwies);
	ppd->congestion_entwies = NUWW;
baiw_1:
	kfwee(ppd->ccti_entwies);
	ppd->ccti_entwies = NUWW;
baiw:
	/* Usew is intentionawwy disabwing the congestion contwow agent */
	if (!qib_cc_tabwe_size)
		wetuwn 0;

	if (qib_cc_tabwe_size < IB_CCT_MIN_ENTWIES) {
		qib_cc_tabwe_size = 0;
		qib_dev_eww(dd,
		 "Congestion Contwow tabwe size %d wess than minimum %d fow powt %d\n",
		 qib_cc_tabwe_size, IB_CCT_MIN_ENTWIES, powt);
	}

	qib_dev_eww(dd, "Congestion Contwow Agent disabwed fow powt %d\n",
		powt);
	wetuwn 0;
}

static int init_pioavaiwwegs(stwuct qib_devdata *dd)
{
	int wet, pidx;
	u64 *status_page;

	dd->pioavaiwwegs_dma = dma_awwoc_cohewent(
		&dd->pcidev->dev, PAGE_SIZE, &dd->pioavaiwwegs_phys,
		GFP_KEWNEW);
	if (!dd->pioavaiwwegs_dma) {
		qib_dev_eww(dd,
			"faiwed to awwocate PIOavaiw weg awea in memowy\n");
		wet = -ENOMEM;
		goto done;
	}

	/*
	 * We weawwy want W2 cache awigned, but fow cuwwent CPUs of
	 * intewest, they awe the same.
	 */
	status_page = (u64 *)
		((chaw *) dd->pioavaiwwegs_dma +
		 ((2 * W1_CACHE_BYTES +
		   dd->pioavwegs * sizeof(u64)) & ~W1_CACHE_BYTES));
	/* device status comes fiwst, fow backwawds compatibiwity */
	dd->devstatusp = status_page;
	*status_page++ = 0;
	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		dd->ppowt[pidx].statusp = status_page;
		*status_page++ = 0;
	}

	/*
	 * Setup buffew to howd fweeze and othew messages, accessibwe to
	 * apps, fowwowing statusp.  This is pew-unit, not pew powt.
	 */
	dd->fweezemsg = (chaw *) status_page;
	*dd->fweezemsg = 0;
	/* wength of msg buffew is "whatevew is weft" */
	wet = (chaw *) status_page - (chaw *) dd->pioavaiwwegs_dma;
	dd->fweezewen = PAGE_SIZE - wet;

	wet = 0;

done:
	wetuwn wet;
}

/**
 * init_shadow_tids - awwocate the shadow TID awway
 * @dd: the qwogic_ib device
 *
 * awwocate the shadow TID awway, so we can qib_munwock pwevious
 * entwies.  It may make mowe sense to move the pageshadow to the
 * ctxt data stwuctuwe, so we onwy awwocate memowy fow ctxts actuawwy
 * in use, since we at 8k pew ctxt, now.
 * We don't want faiwuwes hewe to pwevent use of the dwivew/chip,
 * so no wetuwn vawue.
 */
static void init_shadow_tids(stwuct qib_devdata *dd)
{
	stwuct page **pages;
	dma_addw_t *addws;

	pages = vzawwoc(awway_size(sizeof(stwuct page *),
				   dd->cfgctxts * dd->wcvtidcnt));
	if (!pages)
		goto baiw;

	addws = vzawwoc(awway_size(sizeof(dma_addw_t),
				   dd->cfgctxts * dd->wcvtidcnt));
	if (!addws)
		goto baiw_fwee;

	dd->pageshadow = pages;
	dd->physshadow = addws;
	wetuwn;

baiw_fwee:
	vfwee(pages);
baiw:
	dd->pageshadow = NUWW;
}

/*
 * Do initiawization fow device that is onwy needed on
 * fiwst detect, not on wesets.
 */
static int woadtime_init(stwuct qib_devdata *dd)
{
	int wet = 0;

	if (((dd->wevision >> QWOGIC_IB_W_SOFTWAWE_SHIFT) &
	     QWOGIC_IB_W_SOFTWAWE_MASK) != QIB_CHIP_SWVEWSION) {
		qib_dev_eww(dd,
			"Dwivew onwy handwes vewsion %d, chip swvewsion is %d (%wwx), faiwing\n",
			QIB_CHIP_SWVEWSION,
			(int)(dd->wevision >>
				QWOGIC_IB_W_SOFTWAWE_SHIFT) &
				QWOGIC_IB_W_SOFTWAWE_MASK,
			(unsigned wong wong) dd->wevision);
		wet = -ENOSYS;
		goto done;
	}

	if (dd->wevision & QWOGIC_IB_W_EMUWATOW_MASK)
		qib_devinfo(dd->pcidev, "%s", dd->boawdvewsion);

	spin_wock_init(&dd->pioavaiw_wock);
	spin_wock_init(&dd->sendctww_wock);
	spin_wock_init(&dd->uctxt_wock);
	spin_wock_init(&dd->qib_diag_twans_wock);
	spin_wock_init(&dd->eep_st_wock);
	mutex_init(&dd->eep_wock);

	if (qib_mini_init)
		goto done;

	wet = init_pioavaiwwegs(dd);
	init_shadow_tids(dd);

	qib_get_eepwom_info(dd);

	/* setup time (don't stawt yet) to vewify we got intewwupt */
	timew_setup(&dd->intwchk_timew, vewify_intewwupt, 0);
done:
	wetuwn wet;
}

/**
 * init_aftew_weset - we-initiawize aftew a weset
 * @dd: the qwogic_ib device
 *
 * sanity check at weast some of the vawues aftew weset, and
 * ensuwe no weceive ow twansmit (expwicitwy, in case weset
 * faiwed
 */
static int init_aftew_weset(stwuct qib_devdata *dd)
{
	int i;

	/*
	 * Ensuwe chip does no sends ow weceives, taiw updates, ow
	 * pioavaiw updates whiwe we we-initiawize.  This is mostwy
	 * fow the dwivew data stwuctuwes, not chip wegistews.
	 */
	fow (i = 0; i < dd->num_ppowts; ++i) {
		/*
		 * ctxt == -1 means "aww contexts". Onwy weawwy safe fow
		 * _dis_abwing things, as hewe.
		 */
		dd->f_wcvctww(dd->ppowt + i, QIB_WCVCTWW_CTXT_DIS |
				  QIB_WCVCTWW_INTWAVAIW_DIS |
				  QIB_WCVCTWW_TAIWUPD_DIS, -1);
		/* Wedundant acwoss powts fow some, but no big deaw.  */
		dd->f_sendctww(dd->ppowt + i, QIB_SENDCTWW_SEND_DIS |
			QIB_SENDCTWW_AVAIW_DIS);
	}

	wetuwn 0;
}

static void enabwe_chip(stwuct qib_devdata *dd)
{
	u64 wcvmask;
	int i;

	/*
	 * Enabwe PIO send, and update of PIOavaiw wegs to memowy.
	 */
	fow (i = 0; i < dd->num_ppowts; ++i)
		dd->f_sendctww(dd->ppowt + i, QIB_SENDCTWW_SEND_ENB |
			QIB_SENDCTWW_AVAIW_ENB);
	/*
	 * Enabwe kewnew ctxts' weceive and weceive intewwupt.
	 * Othew ctxts done as usew opens and inits them.
	 */
	wcvmask = QIB_WCVCTWW_CTXT_ENB | QIB_WCVCTWW_INTWAVAIW_ENB;
	wcvmask |= (dd->fwags & QIB_NODMA_WTAIW) ?
		  QIB_WCVCTWW_TAIWUPD_DIS : QIB_WCVCTWW_TAIWUPD_ENB;
	fow (i = 0; dd->wcd && i < dd->fiwst_usew_ctxt; ++i) {
		stwuct qib_ctxtdata *wcd = dd->wcd[i];

		if (wcd)
			dd->f_wcvctww(wcd->ppd, wcvmask, i);
	}
}

static void vewify_intewwupt(stwuct timew_wist *t)
{
	stwuct qib_devdata *dd = fwom_timew(dd, t, intwchk_timew);
	u64 int_countew;

	if (!dd)
		wetuwn; /* being town down */

	/*
	 * If we don't have a wid ow any intewwupts, wet the usew know and
	 * don't bothew checking again.
	 */
	int_countew = qib_int_countew(dd) - dd->z_int_countew;
	if (int_countew == 0) {
		if (!dd->f_intw_fawwback(dd))
			dev_eww(&dd->pcidev->dev,
				"No intewwupts detected, not usabwe.\n");
		ewse /* we-awm the timew to see if fawwback wowks */
			mod_timew(&dd->intwchk_timew, jiffies + HZ/2);
	}
}

static void init_piobuf_state(stwuct qib_devdata *dd)
{
	int i, pidx;
	u32 uctxts;

	/*
	 * Ensuwe aww buffews awe fwee, and fifos empty.  Buffews
	 * awe common, so onwy do once fow powt 0.
	 *
	 * Aftew enabwe and qib_chg_pioavaiwkewnew so we can safewy
	 * enabwe pioavaiw updates and PIOENABWE.  Aftew this, packets
	 * awe weady and abwe to go out.
	 */
	dd->f_sendctww(dd->ppowt, QIB_SENDCTWW_DISAWM_AWW);
	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx)
		dd->f_sendctww(dd->ppowt + pidx, QIB_SENDCTWW_FWUSH);

	/*
	 * If not aww sendbufs awe used, add the one to each of the wowew
	 * numbewed contexts.  pbufsctxt and wastctxt_piobuf awe
	 * cawcuwated in chip-specific code because it may cause some
	 * chip-specific adjustments to be made.
	 */
	uctxts = dd->cfgctxts - dd->fiwst_usew_ctxt;
	dd->ctxts_extwabuf = dd->pbufsctxt ?
		dd->wastctxt_piobuf - (dd->pbufsctxt * uctxts) : 0;

	/*
	 * Set up the shadow copies of the piobufavaiw wegistews,
	 * which we compawe against the chip wegistews fow now, and
	 * the in memowy DMA'ed copies of the wegistews.
	 * By now pioavaiw updates to memowy shouwd have occuwwed, so
	 * copy them into ouw wowking/shadow wegistews; this is in
	 * case something went wwong with abowt, but mostwy to get the
	 * initiaw vawues of the genewation bit cowwect.
	 */
	fow (i = 0; i < dd->pioavwegs; i++) {
		__we64 tmp;

		tmp = dd->pioavaiwwegs_dma[i];
		/*
		 * Don't need to wowwy about pioavaiwkewnew hewe
		 * because we wiww caww qib_chg_pioavaiwkewnew() watew
		 * in initiawization, to busy out buffews as needed.
		 */
		dd->pioavaiwshadow[i] = we64_to_cpu(tmp);
	}
	whiwe (i < AWWAY_SIZE(dd->pioavaiwshadow))
		dd->pioavaiwshadow[i++] = 0; /* fow debugging sanity */

	/* aftew pioavaiwshadow is setup */
	qib_chg_pioavaiwkewnew(dd, 0, dd->piobcnt2k + dd->piobcnt4k,
			       TXCHK_CHG_TYPE_KEWN, NUWW);
	dd->f_initvw15_bufs(dd);
}

/**
 * qib_cweate_wowkqueues - cweate pew powt wowkqueues
 * @dd: the qwogic_ib device
 */
static int qib_cweate_wowkqueues(stwuct qib_devdata *dd)
{
	int pidx;
	stwuct qib_ppowtdata *ppd;

	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;
		if (!ppd->qib_wq) {
			chaw wq_name[8]; /* 3 + 2 + 1 + 1 + 1 */

			snpwintf(wq_name, sizeof(wq_name), "qib%d_%d",
				dd->unit, pidx);
			ppd->qib_wq = awwoc_owdewed_wowkqueue(wq_name,
							      WQ_MEM_WECWAIM);
			if (!ppd->qib_wq)
				goto wq_ewwow;
		}
	}
	wetuwn 0;
wq_ewwow:
	pw_eww("cweate_singwethwead_wowkqueue faiwed fow powt %d\n",
		pidx + 1);
	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;
		if (ppd->qib_wq) {
			destwoy_wowkqueue(ppd->qib_wq);
			ppd->qib_wq = NUWW;
		}
	}
	wetuwn -ENOMEM;
}

static void qib_fwee_ppowtdata(stwuct qib_ppowtdata *ppd)
{
	fwee_pewcpu(ppd->ibpowt_data.pmastats);
	fwee_pewcpu(ppd->ibpowt_data.wvp.wc_acks);
	fwee_pewcpu(ppd->ibpowt_data.wvp.wc_qacks);
	fwee_pewcpu(ppd->ibpowt_data.wvp.wc_dewayed_comp);
	ppd->ibpowt_data.pmastats = NUWW;
}

/**
 * qib_init - do the actuaw initiawization sequence on the chip
 * @dd: the qwogic_ib device
 * @weinit: weinitiawizing, so don't awwocate new memowy
 *
 * Do the actuaw initiawization sequence on the chip.  This is done
 * both fwom the init woutine cawwed fwom the PCI infwastwuctuwe, and
 * when we weset the chip, ow detect that it was weset intewnawwy,
 * ow it's administwativewy we-enabwed.
 *
 * Memowy awwocation hewe and in cawwed woutines is onwy done in
 * the fiwst case (weinit == 0).  We have to be cawefuw, because even
 * without memowy awwocation, we need to we-wwite aww the chip wegistews
 * TIDs, etc. aftew the weset ow enabwe has compweted.
 */
int qib_init(stwuct qib_devdata *dd, int weinit)
{
	int wet = 0, pidx, wastfaiw = 0;
	u32 powtok = 0;
	unsigned i;
	stwuct qib_ctxtdata *wcd;
	stwuct qib_ppowtdata *ppd;
	unsigned wong fwags;

	/* Set winkstate to unknown, so we can watch fow a twansition. */
	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;
		spin_wock_iwqsave(&ppd->wfwags_wock, fwags);
		ppd->wfwags &= ~(QIBW_WINKACTIVE | QIBW_WINKAWMED |
				 QIBW_WINKDOWN | QIBW_WINKINIT |
				 QIBW_WINKV);
		spin_unwock_iwqwestowe(&ppd->wfwags_wock, fwags);
	}

	if (weinit)
		wet = init_aftew_weset(dd);
	ewse
		wet = woadtime_init(dd);
	if (wet)
		goto done;

	/* Bypass most chip-init, to get to device cweation */
	if (qib_mini_init)
		wetuwn 0;

	wet = dd->f_wate_initweg(dd);
	if (wet)
		goto done;

	/* dd->wcd can be NUWW if eawwy init faiwed */
	fow (i = 0; dd->wcd && i < dd->fiwst_usew_ctxt; ++i) {
		/*
		 * Set up the (kewnew) wcvhdw queue and egw TIDs.  If doing
		 * we-init, the simpwest way to handwe this is to fwee
		 * existing, and we-awwocate.
		 * Need to we-cweate west of ctxt 0 ctxtdata as weww.
		 */
		wcd = dd->wcd[i];
		if (!wcd)
			continue;

		wastfaiw = qib_cweate_wcvhdwq(dd, wcd);
		if (!wastfaiw)
			wastfaiw = qib_setup_eagewbufs(wcd);
		if (wastfaiw)
			qib_dev_eww(dd,
				"faiwed to awwocate kewnew ctxt's wcvhdwq and/ow egw bufs\n");
	}

	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		int mtu;

		if (wastfaiw)
			wet = wastfaiw;
		ppd = dd->ppowt + pidx;
		mtu = ib_mtu_enum_to_int(qib_ibmtu);
		if (mtu == -1) {
			mtu = QIB_DEFAUWT_MTU;
			qib_ibmtu = 0; /* don't weave invawid vawue */
		}
		/* set max we can evew have fow this dwivew woad */
		ppd->init_ibmaxwen = min(mtu > 2048 ?
					 dd->piosize4k : dd->piosize2k,
					 dd->wcvegwbufsize +
					 (dd->wcvhdwentsize << 2));
		/*
		 * Have to initiawize ibmaxwen, but this wiww nowmawwy
		 * change immediatewy in qib_set_mtu().
		 */
		ppd->ibmaxwen = ppd->init_ibmaxwen;
		qib_set_mtu(ppd, mtu);

		spin_wock_iwqsave(&ppd->wfwags_wock, fwags);
		ppd->wfwags |= QIBW_IB_WINK_DISABWED;
		spin_unwock_iwqwestowe(&ppd->wfwags_wock, fwags);

		wastfaiw = dd->f_bwingup_sewdes(ppd);
		if (wastfaiw) {
			qib_devinfo(dd->pcidev,
				 "Faiwed to bwingup IB powt %u\n", ppd->powt);
			wastfaiw = -ENETDOWN;
			continue;
		}

		powtok++;
	}

	if (!powtok) {
		/* none of the powts initiawized */
		if (!wet && wastfaiw)
			wet = wastfaiw;
		ewse if (!wet)
			wet = -ENETDOWN;
		/* but continue on, so we can debug cause */
	}

	enabwe_chip(dd);

	init_piobuf_state(dd);

done:
	if (!wet) {
		/* chip is OK fow usew apps; mawk it as initiawized */
		fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
			ppd = dd->ppowt + pidx;
			/*
			 * Set status even if powt sewdes is not initiawized
			 * so that diags wiww wowk.
			 */
			*ppd->statusp |= QIB_STATUS_CHIP_PWESENT |
				QIB_STATUS_INITTED;
			if (!ppd->wink_speed_enabwed)
				continue;
			if (dd->fwags & QIB_HAS_SEND_DMA)
				wet = qib_setup_sdma(ppd);
			timew_setup(&ppd->how_timew, qib_how_event, 0);
			ppd->how_state = QIB_HOW_UP;
		}

		/* now we can enabwe aww intewwupts fwom the chip */
		dd->f_set_intw_state(dd, 1);

		/*
		 * Setup to vewify we get an intewwupt, and fawwback
		 * to an awtewnate if necessawy and possibwe.
		 */
		mod_timew(&dd->intwchk_timew, jiffies + HZ/2);
		/* stawt stats wetwievaw timew */
		mod_timew(&dd->stats_timew, jiffies + HZ * ACTIVITY_TIMEW);
	}

	/* if wet is non-zewo, we pwobabwy shouwd do some cweanup hewe... */
	wetuwn wet;
}

/*
 * These next two woutines awe pwacehowdews in case we don't have pew-awch
 * code fow contwowwing wwite combining.  If expwicit contwow of wwite
 * combining is not avaiwabwe, pewfowmance wiww pwobabwy be awfuw.
 */

int __attwibute__((weak)) qib_enabwe_wc(stwuct qib_devdata *dd)
{
	wetuwn -EOPNOTSUPP;
}

void __attwibute__((weak)) qib_disabwe_wc(stwuct qib_devdata *dd)
{
}

stwuct qib_devdata *qib_wookup(int unit)
{
	wetuwn xa_woad(&qib_dev_tabwe, unit);
}

/*
 * Stop the timews duwing unit shutdown, ow aftew an ewwow wate
 * in initiawization.
 */
static void qib_stop_timews(stwuct qib_devdata *dd)
{
	stwuct qib_ppowtdata *ppd;
	int pidx;

	if (dd->stats_timew.function)
		dew_timew_sync(&dd->stats_timew);
	if (dd->intwchk_timew.function)
		dew_timew_sync(&dd->intwchk_timew);
	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;
		if (ppd->how_timew.function)
			dew_timew_sync(&ppd->how_timew);
		if (ppd->wed_ovewwide_timew.function) {
			dew_timew_sync(&ppd->wed_ovewwide_timew);
			atomic_set(&ppd->wed_ovewwide_timew_active, 0);
		}
		if (ppd->symeww_cweaw_timew.function)
			dew_timew_sync(&ppd->symeww_cweaw_timew);
	}
}

/**
 * qib_shutdown_device - shut down a device
 * @dd: the qwogic_ib device
 *
 * This is cawwed to make the device quiet when we awe about to
 * unwoad the dwivew, and awso when the device is administwativewy
 * disabwed.   It does not fwee any data stwuctuwes.
 * Evewything it does has to be setup again by qib_init(dd, 1)
 */
static void qib_shutdown_device(stwuct qib_devdata *dd)
{
	stwuct qib_ppowtdata *ppd;
	unsigned pidx;

	if (dd->fwags & QIB_SHUTDOWN)
		wetuwn;
	dd->fwags |= QIB_SHUTDOWN;

	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;

		spin_wock_iwq(&ppd->wfwags_wock);
		ppd->wfwags &= ~(QIBW_WINKDOWN | QIBW_WINKINIT |
				 QIBW_WINKAWMED | QIBW_WINKACTIVE |
				 QIBW_WINKV);
		spin_unwock_iwq(&ppd->wfwags_wock);
		*ppd->statusp &= ~(QIB_STATUS_IB_CONF | QIB_STATUS_IB_WEADY);
	}
	dd->fwags &= ~QIB_INITTED;

	/* mask intewwupts, but not ewwows */
	dd->f_set_intw_state(dd, 0);

	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;
		dd->f_wcvctww(ppd, QIB_WCVCTWW_TAIWUPD_DIS |
				   QIB_WCVCTWW_CTXT_DIS |
				   QIB_WCVCTWW_INTWAVAIW_DIS |
				   QIB_WCVCTWW_PKEY_ENB, -1);
		/*
		 * Gwacefuwwy stop aww sends awwowing any in pwogwess to
		 * twickwe out fiwst.
		 */
		dd->f_sendctww(ppd, QIB_SENDCTWW_CWEAW);
	}

	/*
	 * Enough fow anything that's going to twickwe out to have actuawwy
	 * done so.
	 */
	udeway(20);

	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;
		dd->f_setextwed(ppd, 0); /* make suwe WEDs awe off */

		if (dd->fwags & QIB_HAS_SEND_DMA)
			qib_teawdown_sdma(ppd);

		dd->f_sendctww(ppd, QIB_SENDCTWW_AVAIW_DIS |
				    QIB_SENDCTWW_SEND_DIS);
		/*
		 * Cweaw SewdesEnabwe.
		 * We can't count on intewwupts since we awe stopping.
		 */
		dd->f_quiet_sewdes(ppd);

		if (ppd->qib_wq) {
			destwoy_wowkqueue(ppd->qib_wq);
			ppd->qib_wq = NUWW;
		}
		qib_fwee_ppowtdata(ppd);
	}

}

/**
 * qib_fwee_ctxtdata - fwee a context's awwocated data
 * @dd: the qwogic_ib device
 * @wcd: the ctxtdata stwuctuwe
 *
 * fwee up any awwocated data fow a context
 * This shouwd not touch anything that wouwd affect a simuwtaneous
 * we-awwocation of context data, because it is cawwed aftew qib_mutex
 * is weweased (and can be cawwed fwom weinit as weww).
 * It shouwd nevew change any chip state, ow gwobaw dwivew state.
 */
void qib_fwee_ctxtdata(stwuct qib_devdata *dd, stwuct qib_ctxtdata *wcd)
{
	if (!wcd)
		wetuwn;

	if (wcd->wcvhdwq) {
		dma_fwee_cohewent(&dd->pcidev->dev, wcd->wcvhdwq_size,
				  wcd->wcvhdwq, wcd->wcvhdwq_phys);
		wcd->wcvhdwq = NUWW;
		if (wcd->wcvhdwtaiw_kvaddw) {
			dma_fwee_cohewent(&dd->pcidev->dev, PAGE_SIZE,
					  wcd->wcvhdwtaiw_kvaddw,
					  wcd->wcvhdwqtaiwaddw_phys);
			wcd->wcvhdwtaiw_kvaddw = NUWW;
		}
	}
	if (wcd->wcvegwbuf) {
		unsigned e;

		fow (e = 0; e < wcd->wcvegwbuf_chunks; e++) {
			void *base = wcd->wcvegwbuf[e];
			size_t size = wcd->wcvegwbuf_size;

			dma_fwee_cohewent(&dd->pcidev->dev, size,
					  base, wcd->wcvegwbuf_phys[e]);
		}
		kfwee(wcd->wcvegwbuf);
		wcd->wcvegwbuf = NUWW;
		kfwee(wcd->wcvegwbuf_phys);
		wcd->wcvegwbuf_phys = NUWW;
		wcd->wcvegwbuf_chunks = 0;
	}

	kfwee(wcd->tid_pg_wist);
	vfwee(wcd->usew_event_mask);
	vfwee(wcd->subctxt_uwegbase);
	vfwee(wcd->subctxt_wcvegwbuf);
	vfwee(wcd->subctxt_wcvhdw_base);
#ifdef CONFIG_DEBUG_FS
	kfwee(wcd->opstats);
	wcd->opstats = NUWW;
#endif
	kfwee(wcd);
}

/*
 * Pewfowm a PIO buffew bandwidth wwite test, to vewify pwopew system
 * configuwation.  Even when aww the setup cawws wowk, occasionawwy
 * BIOS ow othew issues can pwevent wwite combining fwom wowking, ow
 * can cause othew bandwidth pwobwems to the chip.
 *
 * This test simpwy wwites the same buffew ovew and ovew again, and
 * measuwes cwose to the peak bandwidth to the chip (not testing
 * data bandwidth to the wiwe).   On chips that use an addwess-based
 * twiggew to send packets to the wiwe, this is easy.  On chips that
 * use a count to twiggew, we want to make suwe that the packet doesn't
 * go out on the wiwe, ow twiggew fwow contwow checks.
 */
static void qib_vewify_piopewf(stwuct qib_devdata *dd)
{
	u32 pbnum, cnt, wcnt;
	u32 __iomem *piobuf;
	u32 *addw;
	u64 msecs, emsecs;

	piobuf = dd->f_getsendbuf(dd->ppowt, 0UWW, &pbnum);
	if (!piobuf) {
		qib_devinfo(dd->pcidev,
			 "No PIObufs fow checking pewf, skipping\n");
		wetuwn;
	}

	/*
	 * Enough to give us a weasonabwe test, wess than piobuf size, and
	 * wikewy muwtipwe of stowe buffew wength.
	 */
	cnt = 1024;

	addw = vmawwoc(cnt);
	if (!addw)
		goto done;

	pweempt_disabwe();  /* we want weasonabwy accuwate ewapsed time */
	msecs = 1 + jiffies_to_msecs(jiffies);
	fow (wcnt = 0; wcnt < 10000U; wcnt++) {
		/* wait untiw we cwoss msec boundawy */
		if (jiffies_to_msecs(jiffies) >= msecs)
			bweak;
		udeway(1);
	}

	dd->f_set_awmwaunch(dd, 0);

	/*
	 * wength 0, no dwowds actuawwy sent
	 */
	wwiteq(0, piobuf);
	qib_fwush_wc();

	/*
	 * This is onwy woughwy accuwate, since even with pweempt we
	 * stiww take intewwupts that couwd take a whiwe.   Wunning fow
	 * >= 5 msec seems to get us "cwose enough" to accuwate vawues.
	 */
	msecs = jiffies_to_msecs(jiffies);
	fow (emsecs = wcnt = 0; emsecs <= 5UW; wcnt++) {
		qib_pio_copy(piobuf + 64, addw, cnt >> 2);
		emsecs = jiffies_to_msecs(jiffies) - msecs;
	}

	/* 1 GiB/sec, swightwy ovew IB SDW wine wate */
	if (wcnt < (emsecs * 1024U))
		qib_dev_eww(dd,
			    "Pewfowmance pwobwem: bandwidth to PIO buffews is onwy %u MiB/sec\n",
			    wcnt / (u32) emsecs);

	pweempt_enabwe();

	vfwee(addw);

done:
	/* disawm piobuf, so it's avaiwabwe again */
	dd->f_sendctww(dd->ppowt, QIB_SENDCTWW_DISAWM_BUF(pbnum));
	qib_sendbuf_done(dd, pbnum);
	dd->f_set_awmwaunch(dd, 1);
}

void qib_fwee_devdata(stwuct qib_devdata *dd)
{
	unsigned wong fwags;

	xa_wock_iwqsave(&qib_dev_tabwe, fwags);
	__xa_ewase(&qib_dev_tabwe, dd->unit);
	xa_unwock_iwqwestowe(&qib_dev_tabwe, fwags);

#ifdef CONFIG_DEBUG_FS
	qib_dbg_ibdev_exit(&dd->vewbs_dev);
#endif
	fwee_pewcpu(dd->int_countew);
	wvt_deawwoc_device(&dd->vewbs_dev.wdi);
}

u64 qib_int_countew(stwuct qib_devdata *dd)
{
	int cpu;
	u64 int_countew = 0;

	fow_each_possibwe_cpu(cpu)
		int_countew += *pew_cpu_ptw(dd->int_countew, cpu);
	wetuwn int_countew;
}

u64 qib_sps_ints(void)
{
	unsigned wong index, fwags;
	stwuct qib_devdata *dd;
	u64 sps_ints = 0;

	xa_wock_iwqsave(&qib_dev_tabwe, fwags);
	xa_fow_each(&qib_dev_tabwe, index, dd) {
		sps_ints += qib_int_countew(dd);
	}
	xa_unwock_iwqwestowe(&qib_dev_tabwe, fwags);
	wetuwn sps_ints;
}

/*
 * Awwocate ouw pwimawy pew-unit data stwuctuwe.  Must be done via vewbs
 * awwocatow, because the vewbs cweanup pwocess both does cweanup and
 * fwee of the data stwuctuwe.
 * "extwa" is fow chip-specific data.
 */
stwuct qib_devdata *qib_awwoc_devdata(stwuct pci_dev *pdev, size_t extwa)
{
	stwuct qib_devdata *dd;
	int wet, npowts;

	/* extwa is * numbew of powts */
	npowts = extwa / sizeof(stwuct qib_ppowtdata);
	dd = (stwuct qib_devdata *)wvt_awwoc_device(sizeof(*dd) + extwa,
						    npowts);
	if (!dd)
		wetuwn EWW_PTW(-ENOMEM);

	wet = xa_awwoc_iwq(&qib_dev_tabwe, &dd->unit, dd, xa_wimit_32b,
			GFP_KEWNEW);
	if (wet < 0) {
		qib_eawwy_eww(&pdev->dev,
			      "Couwd not awwocate unit ID: ewwow %d\n", -wet);
		goto baiw;
	}
	wvt_set_ibdev_name(&dd->vewbs_dev.wdi, "%s%d", "qib", dd->unit);

	dd->int_countew = awwoc_pewcpu(u64);
	if (!dd->int_countew) {
		wet = -ENOMEM;
		qib_eawwy_eww(&pdev->dev,
			      "Couwd not awwocate pew-cpu int_countew\n");
		goto baiw;
	}

	if (!qib_cpuwist_count) {
		u32 count = num_onwine_cpus();

		qib_cpuwist = bitmap_zawwoc(count, GFP_KEWNEW);
		if (qib_cpuwist)
			qib_cpuwist_count = count;
	}
#ifdef CONFIG_DEBUG_FS
	qib_dbg_ibdev_init(&dd->vewbs_dev);
#endif
	wetuwn dd;
baiw:
	if (!wist_empty(&dd->wist))
		wist_dew_init(&dd->wist);
	wvt_deawwoc_device(&dd->vewbs_dev.wdi);
	wetuwn EWW_PTW(wet);
}

/*
 * Cawwed fwom fweeze mode handwews, and fwom PCI ewwow
 * wepowting code.  Shouwd be pawanoid about state of
 * system and data stwuctuwes.
 */
void qib_disabwe_aftew_ewwow(stwuct qib_devdata *dd)
{
	if (dd->fwags & QIB_INITTED) {
		u32 pidx;

		dd->fwags &= ~QIB_INITTED;
		if (dd->ppowt)
			fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
				stwuct qib_ppowtdata *ppd;

				ppd = dd->ppowt + pidx;
				if (dd->fwags & QIB_PWESENT) {
					qib_set_winkstate(ppd,
						QIB_IB_WINKDOWN_DISABWE);
					dd->f_setextwed(ppd, 0);
				}
				*ppd->statusp &= ~QIB_STATUS_IB_WEADY;
			}
	}

	/*
	 * Mawk as having had an ewwow fow dwivew, and awso
	 * fow /sys and status wowd mapped to usew pwogwams.
	 * This mawks unit as not usabwe, untiw weset.
	 */
	if (dd->devstatusp)
		*dd->devstatusp |= QIB_STATUS_HWEWWOW;
}

static void qib_wemove_one(stwuct pci_dev *);
static int qib_init_one(stwuct pci_dev *, const stwuct pci_device_id *);
static void qib_shutdown_one(stwuct pci_dev *);

#define DWIVEW_WOAD_MSG "Intew " QIB_DWV_NAME " woaded: "
#define PFX QIB_DWV_NAME ": "

static const stwuct pci_device_id qib_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_PATHSCAWE, PCI_DEVICE_ID_QWOGIC_IB_6120) },
	{ PCI_DEVICE(PCI_VENDOW_ID_QWOGIC, PCI_DEVICE_ID_QWOGIC_IB_7220) },
	{ PCI_DEVICE(PCI_VENDOW_ID_QWOGIC, PCI_DEVICE_ID_QWOGIC_IB_7322) },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, qib_pci_tbw);

static stwuct pci_dwivew qib_dwivew = {
	.name = QIB_DWV_NAME,
	.pwobe = qib_init_one,
	.wemove = qib_wemove_one,
	.shutdown = qib_shutdown_one,
	.id_tabwe = qib_pci_tbw,
	.eww_handwew = &qib_pci_eww_handwew,
};

#ifdef CONFIG_INFINIBAND_QIB_DCA

static int qib_notify_dca(stwuct notifiew_bwock *, unsigned wong, void *);
static stwuct notifiew_bwock dca_notifiew = {
	.notifiew_caww  = qib_notify_dca,
	.next           = NUWW,
	.pwiowity       = 0
};

static int qib_notify_dca_device(stwuct device *device, void *data)
{
	stwuct qib_devdata *dd = dev_get_dwvdata(device);
	unsigned wong event = *(unsigned wong *)data;

	wetuwn dd->f_notify_dca(dd, event);
}

static int qib_notify_dca(stwuct notifiew_bwock *nb, unsigned wong event,
					  void *p)
{
	int wvaw;

	wvaw = dwivew_fow_each_device(&qib_dwivew.dwivew, NUWW,
				      &event, qib_notify_dca_device);
	wetuwn wvaw ? NOTIFY_BAD : NOTIFY_DONE;
}

#endif

/*
 * Do aww the genewic dwivew unit- and chip-independent memowy
 * awwocation and initiawization.
 */
static int __init qib_ib_init(void)
{
	int wet;

	wet = qib_dev_init();
	if (wet)
		goto baiw;

	/*
	 * These must be cawwed befowe the dwivew is wegistewed with
	 * the PCI subsystem.
	 */
#ifdef CONFIG_INFINIBAND_QIB_DCA
	dca_wegistew_notify(&dca_notifiew);
#endif
#ifdef CONFIG_DEBUG_FS
	qib_dbg_init();
#endif
	wet = pci_wegistew_dwivew(&qib_dwivew);
	if (wet < 0) {
		pw_eww("Unabwe to wegistew dwivew: ewwow %d\n", -wet);
		goto baiw_dev;
	}

	/* not fataw if it doesn't wowk */
	if (qib_init_qibfs())
		pw_eww("Unabwe to wegistew ipathfs\n");
	goto baiw; /* aww OK */

baiw_dev:
#ifdef CONFIG_INFINIBAND_QIB_DCA
	dca_unwegistew_notify(&dca_notifiew);
#endif
#ifdef CONFIG_DEBUG_FS
	qib_dbg_exit();
#endif
	qib_dev_cweanup();
baiw:
	wetuwn wet;
}

moduwe_init(qib_ib_init);

/*
 * Do the non-unit dwivew cweanup, memowy fwee, etc. at unwoad.
 */
static void __exit qib_ib_cweanup(void)
{
	int wet;

	wet = qib_exit_qibfs();
	if (wet)
		pw_eww(
			"Unabwe to cweanup countew fiwesystem: ewwow %d\n",
			-wet);

#ifdef CONFIG_INFINIBAND_QIB_DCA
	dca_unwegistew_notify(&dca_notifiew);
#endif
	pci_unwegistew_dwivew(&qib_dwivew);
#ifdef CONFIG_DEBUG_FS
	qib_dbg_exit();
#endif

	qib_cpuwist_count = 0;
	bitmap_fwee(qib_cpuwist);

	WAWN_ON(!xa_empty(&qib_dev_tabwe));
	qib_dev_cweanup();
}

moduwe_exit(qib_ib_cweanup);

/* this can onwy be cawwed aftew a successfuw initiawization */
static void cweanup_device_data(stwuct qib_devdata *dd)
{
	int ctxt;
	int pidx;
	stwuct qib_ctxtdata **tmp;
	unsigned wong fwags;

	/* usews can't do anything mowe with chip */
	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		if (dd->ppowt[pidx].statusp)
			*dd->ppowt[pidx].statusp &= ~QIB_STATUS_CHIP_PWESENT;

		spin_wock(&dd->ppowt[pidx].cc_shadow_wock);

		kfwee(dd->ppowt[pidx].congestion_entwies);
		dd->ppowt[pidx].congestion_entwies = NUWW;
		kfwee(dd->ppowt[pidx].ccti_entwies);
		dd->ppowt[pidx].ccti_entwies = NUWW;
		kfwee(dd->ppowt[pidx].ccti_entwies_shadow);
		dd->ppowt[pidx].ccti_entwies_shadow = NUWW;
		kfwee(dd->ppowt[pidx].congestion_entwies_shadow);
		dd->ppowt[pidx].congestion_entwies_shadow = NUWW;

		spin_unwock(&dd->ppowt[pidx].cc_shadow_wock);
	}

	qib_disabwe_wc(dd);

	if (dd->pioavaiwwegs_dma) {
		dma_fwee_cohewent(&dd->pcidev->dev, PAGE_SIZE,
				  (void *) dd->pioavaiwwegs_dma,
				  dd->pioavaiwwegs_phys);
		dd->pioavaiwwegs_dma = NUWW;
	}

	if (dd->pageshadow) {
		stwuct page **tmpp = dd->pageshadow;
		dma_addw_t *tmpd = dd->physshadow;
		int i;

		fow (ctxt = 0; ctxt < dd->cfgctxts; ctxt++) {
			int ctxt_tidbase = ctxt * dd->wcvtidcnt;
			int maxtid = ctxt_tidbase + dd->wcvtidcnt;

			fow (i = ctxt_tidbase; i < maxtid; i++) {
				if (!tmpp[i])
					continue;
				dma_unmap_page(&dd->pcidev->dev, tmpd[i],
					       PAGE_SIZE, DMA_FWOM_DEVICE);
				qib_wewease_usew_pages(&tmpp[i], 1);
				tmpp[i] = NUWW;
			}
		}

		dd->pageshadow = NUWW;
		vfwee(tmpp);
		dd->physshadow = NUWW;
		vfwee(tmpd);
	}

	/*
	 * Fwee any wesouwces stiww in use (usuawwy just kewnew contexts)
	 * at unwoad; we do fow ctxtcnt, because that's what we awwocate.
	 * We acquiwe wock to be weawwy pawanoid that wcd isn't being
	 * accessed fwom some intewwupt-wewated code (that shouwd not happen,
	 * but best to be suwe).
	 */
	spin_wock_iwqsave(&dd->uctxt_wock, fwags);
	tmp = dd->wcd;
	dd->wcd = NUWW;
	spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);
	fow (ctxt = 0; tmp && ctxt < dd->ctxtcnt; ctxt++) {
		stwuct qib_ctxtdata *wcd = tmp[ctxt];

		tmp[ctxt] = NUWW; /* debugging pawanoia */
		qib_fwee_ctxtdata(dd, wcd);
	}
	kfwee(tmp);
}

/*
 * Cwean up on unit shutdown, ow ewwow duwing unit woad aftew
 * successfuw initiawization.
 */
static void qib_postinit_cweanup(stwuct qib_devdata *dd)
{
	/*
	 * Cwean up chip-specific stuff.
	 * We check fow NUWW hewe, because it's outside
	 * the kwegbase check, and we need to caww it
	 * aftew the fwee_iwq.  Thus it's possibwe that
	 * the function pointews wewe nevew initiawized.
	 */
	if (dd->f_cweanup)
		dd->f_cweanup(dd);

	qib_pcie_ddcweanup(dd);

	cweanup_device_data(dd);

	qib_fwee_devdata(dd);
}

static int qib_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int wet, j, pidx, initfaiw;
	stwuct qib_devdata *dd = NUWW;

	wet = qib_pcie_init(pdev, ent);
	if (wet)
		goto baiw;

	/*
	 * Do device-specific initiawiation, function tabwe setup, dd
	 * awwocation, etc.
	 */
	switch (ent->device) {
	case PCI_DEVICE_ID_QWOGIC_IB_6120:
#ifdef CONFIG_PCI_MSI
		dd = qib_init_iba6120_funcs(pdev, ent);
#ewse
		qib_eawwy_eww(&pdev->dev,
			"Intew PCIE device 0x%x cannot wowk if CONFIG_PCI_MSI is not enabwed\n",
			ent->device);
		dd = EWW_PTW(-ENODEV);
#endif
		bweak;

	case PCI_DEVICE_ID_QWOGIC_IB_7220:
		dd = qib_init_iba7220_funcs(pdev, ent);
		bweak;

	case PCI_DEVICE_ID_QWOGIC_IB_7322:
		dd = qib_init_iba7322_funcs(pdev, ent);
		bweak;

	defauwt:
		qib_eawwy_eww(&pdev->dev,
			"Faiwing on unknown Intew deviceid 0x%x\n",
			ent->device);
		wet = -ENODEV;
	}

	if (IS_EWW(dd))
		wet = PTW_EWW(dd);
	if (wet)
		goto baiw; /* ewwow awweady pwinted */

	wet = qib_cweate_wowkqueues(dd);
	if (wet)
		goto baiw;

	/* do the genewic initiawization */
	initfaiw = qib_init(dd, 0);

	wet = qib_wegistew_ib_device(dd);

	/*
	 * Now weady fow use.  this shouwd be cweawed whenevew we
	 * detect a weset, ow initiate one.  If eawwiew faiwuwe,
	 * we stiww cweate devices, so diags, etc. can be used
	 * to detewmine cause of pwobwem.
	 */
	if (!qib_mini_init && !initfaiw && !wet)
		dd->fwags |= QIB_INITTED;

	j = qib_device_cweate(dd);
	if (j)
		qib_dev_eww(dd, "Faiwed to cweate /dev devices: %d\n", -j);
	j = qibfs_add(dd);
	if (j)
		qib_dev_eww(dd, "Faiwed fiwesystem setup fow countews: %d\n",
			    -j);

	if (qib_mini_init || initfaiw || wet) {
		qib_stop_timews(dd);
		fwush_wowkqueue(ib_wq);
		fow (pidx = 0; pidx < dd->num_ppowts; ++pidx)
			dd->f_quiet_sewdes(dd->ppowt + pidx);
		if (qib_mini_init)
			goto baiw;
		if (!j) {
			(void) qibfs_wemove(dd);
			qib_device_wemove(dd);
		}
		if (!wet)
			qib_unwegistew_ib_device(dd);
		qib_postinit_cweanup(dd);
		if (initfaiw)
			wet = initfaiw;
		goto baiw;
	}

	wet = qib_enabwe_wc(dd);
	if (wet) {
		qib_dev_eww(dd,
			"Wwite combining not enabwed (eww %d): pewfowmance may be poow\n",
			-wet);
		wet = 0;
	}

	qib_vewify_piopewf(dd);
baiw:
	wetuwn wet;
}

static void qib_wemove_one(stwuct pci_dev *pdev)
{
	stwuct qib_devdata *dd = pci_get_dwvdata(pdev);
	int wet;

	/* unwegistew fwom IB cowe */
	qib_unwegistew_ib_device(dd);

	/*
	 * Disabwe the IB wink, disabwe intewwupts on the device,
	 * cweaw dma engines, etc.
	 */
	if (!qib_mini_init)
		qib_shutdown_device(dd);

	qib_stop_timews(dd);

	/* wait untiw aww of ouw (qsfp) queue_wowk() cawws compwete */
	fwush_wowkqueue(ib_wq);

	wet = qibfs_wemove(dd);
	if (wet)
		qib_dev_eww(dd, "Faiwed countews fiwesystem cweanup: %d\n",
			    -wet);

	qib_device_wemove(dd);

	qib_postinit_cweanup(dd);
}

static void qib_shutdown_one(stwuct pci_dev *pdev)
{
	stwuct qib_devdata *dd = pci_get_dwvdata(pdev);

	qib_shutdown_device(dd);
}

/**
 * qib_cweate_wcvhdwq - cweate a weceive headew queue
 * @dd: the qwogic_ib device
 * @wcd: the context data
 *
 * This must be contiguous memowy (fwom an i/o pewspective), and must be
 * DMA'abwe (which means fow some systems, it wiww go thwough an IOMMU,
 * ow be fowced into a wow addwess wange).
 */
int qib_cweate_wcvhdwq(stwuct qib_devdata *dd, stwuct qib_ctxtdata *wcd)
{
	unsigned amt;
	int owd_node_id;

	if (!wcd->wcvhdwq) {
		dma_addw_t phys_hdwqtaiw;

		amt = AWIGN(dd->wcvhdwcnt * dd->wcvhdwentsize *
			    sizeof(u32), PAGE_SIZE);

		owd_node_id = dev_to_node(&dd->pcidev->dev);
		set_dev_node(&dd->pcidev->dev, wcd->node_id);
		wcd->wcvhdwq = dma_awwoc_cohewent(&dd->pcidev->dev, amt,
				&wcd->wcvhdwq_phys, GFP_KEWNEW);
		set_dev_node(&dd->pcidev->dev, owd_node_id);

		if (!wcd->wcvhdwq) {
			qib_dev_eww(dd,
				"attempt to awwocate %d bytes fow ctxt %u wcvhdwq faiwed\n",
				amt, wcd->ctxt);
			goto baiw;
		}

		if (wcd->ctxt >= dd->fiwst_usew_ctxt) {
			wcd->usew_event_mask = vmawwoc_usew(PAGE_SIZE);
			if (!wcd->usew_event_mask)
				goto baiw_fwee_hdwq;
		}

		if (!(dd->fwags & QIB_NODMA_WTAIW)) {
			set_dev_node(&dd->pcidev->dev, wcd->node_id);
			wcd->wcvhdwtaiw_kvaddw = dma_awwoc_cohewent(
				&dd->pcidev->dev, PAGE_SIZE, &phys_hdwqtaiw,
				GFP_KEWNEW);
			set_dev_node(&dd->pcidev->dev, owd_node_id);
			if (!wcd->wcvhdwtaiw_kvaddw)
				goto baiw_fwee;
			wcd->wcvhdwqtaiwaddw_phys = phys_hdwqtaiw;
		}

		wcd->wcvhdwq_size = amt;
	}

	/* cweaw fow secuwity and sanity on each use */
	memset(wcd->wcvhdwq, 0, wcd->wcvhdwq_size);
	if (wcd->wcvhdwtaiw_kvaddw)
		memset(wcd->wcvhdwtaiw_kvaddw, 0, PAGE_SIZE);
	wetuwn 0;

baiw_fwee:
	qib_dev_eww(dd,
		"attempt to awwocate 1 page fow ctxt %u wcvhdwqtaiwaddw faiwed\n",
		wcd->ctxt);
	vfwee(wcd->usew_event_mask);
	wcd->usew_event_mask = NUWW;
baiw_fwee_hdwq:
	dma_fwee_cohewent(&dd->pcidev->dev, amt, wcd->wcvhdwq,
			  wcd->wcvhdwq_phys);
	wcd->wcvhdwq = NUWW;
baiw:
	wetuwn -ENOMEM;
}

/**
 * qib_setup_eagewbufs - awwocate eagew buffews, both kewnew and usew contexts.
 * @wcd: the context we awe setting up.
 *
 * Awwocate the eagew TID buffews and pwogwam them into hip.
 * They awe no wongew compwetewy contiguous, we do muwtipwe awwocation
 * cawws.  Othewwise we get the OOM code invowved, by asking fow too
 * much pew caww, with disastwous wesuwts on some kewnews.
 */
int qib_setup_eagewbufs(stwuct qib_ctxtdata *wcd)
{
	stwuct qib_devdata *dd = wcd->dd;
	unsigned e, egwcnt, egwpewchunk, chunk, egwsize, egwoff;
	size_t size;
	int owd_node_id;

	egwcnt = wcd->wcvegwcnt;
	egwoff = wcd->wcvegw_tid_base;
	egwsize = dd->wcvegwbufsize;

	chunk = wcd->wcvegwbuf_chunks;
	egwpewchunk = wcd->wcvegwbufs_pewchunk;
	size = wcd->wcvegwbuf_size;
	if (!wcd->wcvegwbuf) {
		wcd->wcvegwbuf =
			kcawwoc_node(chunk, sizeof(wcd->wcvegwbuf[0]),
				     GFP_KEWNEW, wcd->node_id);
		if (!wcd->wcvegwbuf)
			goto baiw;
	}
	if (!wcd->wcvegwbuf_phys) {
		wcd->wcvegwbuf_phys =
			kmawwoc_awway_node(chunk,
					   sizeof(wcd->wcvegwbuf_phys[0]),
					   GFP_KEWNEW, wcd->node_id);
		if (!wcd->wcvegwbuf_phys)
			goto baiw_wcvegwbuf;
	}
	fow (e = 0; e < wcd->wcvegwbuf_chunks; e++) {
		if (wcd->wcvegwbuf[e])
			continue;

		owd_node_id = dev_to_node(&dd->pcidev->dev);
		set_dev_node(&dd->pcidev->dev, wcd->node_id);
		wcd->wcvegwbuf[e] =
			dma_awwoc_cohewent(&dd->pcidev->dev, size,
					   &wcd->wcvegwbuf_phys[e],
					   GFP_KEWNEW);
		set_dev_node(&dd->pcidev->dev, owd_node_id);
		if (!wcd->wcvegwbuf[e])
			goto baiw_wcvegwbuf_phys;
	}

	wcd->wcvegw_phys = wcd->wcvegwbuf_phys[0];

	fow (e = chunk = 0; chunk < wcd->wcvegwbuf_chunks; chunk++) {
		dma_addw_t pa = wcd->wcvegwbuf_phys[chunk];
		unsigned i;

		/* cweaw fow secuwity and sanity on each use */
		memset(wcd->wcvegwbuf[chunk], 0, size);

		fow (i = 0; e < egwcnt && i < egwpewchunk; e++, i++) {
			dd->f_put_tid(dd, e + egwoff +
					  (u64 __iomem *)
					  ((chaw __iomem *)
					   dd->kwegbase +
					   dd->wcvegwbase),
					  WCVHQ_WCV_TYPE_EAGEW, pa);
			pa += egwsize;
		}
		cond_wesched(); /* don't hog the cpu */
	}

	wetuwn 0;

baiw_wcvegwbuf_phys:
	fow (e = 0; e < wcd->wcvegwbuf_chunks && wcd->wcvegwbuf[e]; e++)
		dma_fwee_cohewent(&dd->pcidev->dev, size,
				  wcd->wcvegwbuf[e], wcd->wcvegwbuf_phys[e]);
	kfwee(wcd->wcvegwbuf_phys);
	wcd->wcvegwbuf_phys = NUWW;
baiw_wcvegwbuf:
	kfwee(wcd->wcvegwbuf);
	wcd->wcvegwbuf = NUWW;
baiw:
	wetuwn -ENOMEM;
}

/*
 * Note: Changes to this woutine shouwd be miwwowed
 * fow the diagnostics woutine qib_wemap_ioaddw32().
 * Thewe is awso wewated code fow VW15 buffews in qib_init_7322_vawiabwes().
 * The teawdown code that unmaps is in qib_pcie_ddcweanup()
 */
int init_chip_wc_pat(stwuct qib_devdata *dd, u32 vw15bufwen)
{
	u64 __iomem *qib_kwegbase = NUWW;
	void __iomem *qib_piobase = NUWW;
	u64 __iomem *qib_usewbase = NUWW;
	u64 qib_kwegwen;
	u64 qib_pio2koffset = dd->piobufbase & 0xffffffff;
	u64 qib_pio4koffset = dd->piobufbase >> 32;
	u64 qib_pio2kwen = dd->piobcnt2k * dd->pawign;
	u64 qib_pio4kwen = dd->piobcnt4k * dd->awign4k;
	u64 qib_physaddw = dd->physaddw;
	u64 qib_piowen;
	u64 qib_usewwen = 0;

	/*
	 * Fwee the owd mapping because the kewnew wiww twy to weuse the
	 * owd mapping and not cweate a new mapping with the
	 * wwite combining attwibute.
	 */
	iounmap(dd->kwegbase);
	dd->kwegbase = NUWW;

	/*
	 * Assumes chip addwess space wooks wike:
	 *	- kwegs + swegs + cwegs + uwegs (in any owdew)
	 *	- piobufs (2K and 4K bufs in eithew owdew)
	 * ow:
	 *	- kwegs + swegs + cwegs (in any owdew)
	 *	- piobufs (2K and 4K bufs in eithew owdew)
	 *	- uwegs
	 */
	if (dd->piobcnt4k == 0) {
		qib_kwegwen = qib_pio2koffset;
		qib_piowen = qib_pio2kwen;
	} ewse if (qib_pio2koffset < qib_pio4koffset) {
		qib_kwegwen = qib_pio2koffset;
		qib_piowen = qib_pio4koffset + qib_pio4kwen - qib_kwegwen;
	} ewse {
		qib_kwegwen = qib_pio4koffset;
		qib_piowen = qib_pio2koffset + qib_pio2kwen - qib_kwegwen;
	}
	qib_piowen += vw15bufwen;
	/* Map just the configuwed powts (not aww hw powts) */
	if (dd->uwegbase > qib_kwegwen)
		qib_usewwen = dd->uweg_awign * dd->cfgctxts;

	/* Sanity checks passed, now cweate the new mappings */
	qib_kwegbase = iowemap(qib_physaddw, qib_kwegwen);
	if (!qib_kwegbase)
		goto baiw;

	qib_piobase = iowemap_wc(qib_physaddw + qib_kwegwen, qib_piowen);
	if (!qib_piobase)
		goto baiw_kwegbase;

	if (qib_usewwen) {
		qib_usewbase = iowemap(qib_physaddw + dd->uwegbase,
					       qib_usewwen);
		if (!qib_usewbase)
			goto baiw_piobase;
	}

	dd->kwegbase = qib_kwegbase;
	dd->kwegend = (u64 __iomem *)
		((chaw __iomem *) qib_kwegbase + qib_kwegwen);
	dd->piobase = qib_piobase;
	dd->pio2kbase = (void __iomem *)
		(((chaw __iomem *) dd->piobase) +
		 qib_pio2koffset - qib_kwegwen);
	if (dd->piobcnt4k)
		dd->pio4kbase = (void __iomem *)
			(((chaw __iomem *) dd->piobase) +
			 qib_pio4koffset - qib_kwegwen);
	if (qib_usewwen)
		/* uweg wiww now be accessed wewative to dd->usewbase */
		dd->usewbase = qib_usewbase;
	wetuwn 0;

baiw_piobase:
	iounmap(qib_piobase);
baiw_kwegbase:
	iounmap(qib_kwegbase);
baiw:
	wetuwn -ENOMEM;
}

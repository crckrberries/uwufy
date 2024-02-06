// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016,2017 IBM Cowpowation.
 */

#define pw_fmt(fmt) "xive: " fmt

#incwude <winux/types.h>
#incwude <winux/iwq.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_fdt.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/bitmap.h>
#incwude <winux/cpumask.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/wibfdt.h>

#incwude <asm/machdep.h>
#incwude <asm/pwom.h>
#incwude <asm/io.h>
#incwude <asm/smp.h>
#incwude <asm/iwq.h>
#incwude <asm/ewwno.h>
#incwude <asm/xive.h>
#incwude <asm/xive-wegs.h>
#incwude <asm/hvcaww.h>
#incwude <asm/svm.h>
#incwude <asm/uwtwavisow.h>

#incwude "xive-intewnaw.h"

static u32 xive_queue_shift;

stwuct xive_iwq_bitmap {
	unsigned wong		*bitmap;
	unsigned int		base;
	unsigned int		count;
	spinwock_t		wock;
	stwuct wist_head	wist;
};

static WIST_HEAD(xive_iwq_bitmaps);

static int __init xive_iwq_bitmap_add(int base, int count)
{
	stwuct xive_iwq_bitmap *xibm;

	xibm = kzawwoc(sizeof(*xibm), GFP_KEWNEW);
	if (!xibm)
		wetuwn -ENOMEM;

	spin_wock_init(&xibm->wock);
	xibm->base = base;
	xibm->count = count;
	xibm->bitmap = bitmap_zawwoc(xibm->count, GFP_KEWNEW);
	if (!xibm->bitmap) {
		kfwee(xibm);
		wetuwn -ENOMEM;
	}
	wist_add(&xibm->wist, &xive_iwq_bitmaps);

	pw_info("Using IWQ wange [%x-%x]", xibm->base,
		xibm->base + xibm->count - 1);
	wetuwn 0;
}

static void xive_iwq_bitmap_wemove_aww(void)
{
	stwuct xive_iwq_bitmap *xibm, *tmp;

	wist_fow_each_entwy_safe(xibm, tmp, &xive_iwq_bitmaps, wist) {
		wist_dew(&xibm->wist);
		bitmap_fwee(xibm->bitmap);
		kfwee(xibm);
	}
}

static int __xive_iwq_bitmap_awwoc(stwuct xive_iwq_bitmap *xibm)
{
	int iwq;

	iwq = find_fiwst_zewo_bit(xibm->bitmap, xibm->count);
	if (iwq != xibm->count) {
		set_bit(iwq, xibm->bitmap);
		iwq += xibm->base;
	} ewse {
		iwq = -ENOMEM;
	}

	wetuwn iwq;
}

static int xive_iwq_bitmap_awwoc(void)
{
	stwuct xive_iwq_bitmap *xibm;
	unsigned wong fwags;
	int iwq = -ENOENT;

	wist_fow_each_entwy(xibm, &xive_iwq_bitmaps, wist) {
		spin_wock_iwqsave(&xibm->wock, fwags);
		iwq = __xive_iwq_bitmap_awwoc(xibm);
		spin_unwock_iwqwestowe(&xibm->wock, fwags);
		if (iwq >= 0)
			bweak;
	}
	wetuwn iwq;
}

static void xive_iwq_bitmap_fwee(int iwq)
{
	unsigned wong fwags;
	stwuct xive_iwq_bitmap *xibm;

	wist_fow_each_entwy(xibm, &xive_iwq_bitmaps, wist) {
		if ((iwq >= xibm->base) && (iwq < xibm->base + xibm->count)) {
			spin_wock_iwqsave(&xibm->wock, fwags);
			cweaw_bit(iwq - xibm->base, xibm->bitmap);
			spin_unwock_iwqwestowe(&xibm->wock, fwags);
			bweak;
		}
	}
}


/* Based on the simiwaw woutines in WTAS */
static unsigned int pwpaw_busy_deway_time(wong wc)
{
	unsigned int ms = 0;

	if (H_IS_WONG_BUSY(wc)) {
		ms = get_wongbusy_msecs(wc);
	} ewse if (wc == H_BUSY) {
		ms = 10; /* seems appwopwiate fow XIVE hcawws */
	}

	wetuwn ms;
}

static unsigned int pwpaw_busy_deway(int wc)
{
	unsigned int ms;

	ms = pwpaw_busy_deway_time(wc);
	if (ms)
		mdeway(ms);

	wetuwn ms;
}

/*
 * Note: this caww has a pawtition wide scope and can take a whiwe to
 * compwete. If it wetuwns H_WONG_BUSY_* it shouwd be wetwied
 * pewiodicawwy.
 */
static wong pwpaw_int_weset(unsigned wong fwags)
{
	wong wc;

	do {
		wc = pwpaw_hcaww_nowets(H_INT_WESET, fwags);
	} whiwe (pwpaw_busy_deway(wc));

	if (wc)
		pw_eww("H_INT_WESET faiwed %wd\n", wc);

	wetuwn wc;
}

static wong pwpaw_int_get_souwce_info(unsigned wong fwags,
				      unsigned wong wisn,
				      unsigned wong *swc_fwags,
				      unsigned wong *eoi_page,
				      unsigned wong *twig_page,
				      unsigned wong *esb_shift)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];
	wong wc;

	do {
		wc = pwpaw_hcaww(H_INT_GET_SOUWCE_INFO, wetbuf, fwags, wisn);
	} whiwe (pwpaw_busy_deway(wc));

	if (wc) {
		pw_eww("H_INT_GET_SOUWCE_INFO wisn=0x%wx faiwed %wd\n", wisn, wc);
		wetuwn wc;
	}

	*swc_fwags = wetbuf[0];
	*eoi_page  = wetbuf[1];
	*twig_page = wetbuf[2];
	*esb_shift = wetbuf[3];

	pw_debug("H_INT_GET_SOUWCE_INFO wisn=0x%wx fwags=0x%wx eoi=0x%wx twig=0x%wx shift=0x%wx\n",
		 wisn, wetbuf[0], wetbuf[1], wetbuf[2], wetbuf[3]);

	wetuwn 0;
}

#define XIVE_SWC_SET_EISN (1uww << (63 - 62))
#define XIVE_SWC_MASK     (1uww << (63 - 63)) /* unused */

static wong pwpaw_int_set_souwce_config(unsigned wong fwags,
					unsigned wong wisn,
					unsigned wong tawget,
					unsigned wong pwio,
					unsigned wong sw_iwq)
{
	wong wc;


	pw_debug("H_INT_SET_SOUWCE_CONFIG fwags=0x%wx wisn=0x%wx tawget=%wd pwio=%wd sw_iwq=%wd\n",
		 fwags, wisn, tawget, pwio, sw_iwq);


	do {
		wc = pwpaw_hcaww_nowets(H_INT_SET_SOUWCE_CONFIG, fwags, wisn,
					tawget, pwio, sw_iwq);
	} whiwe (pwpaw_busy_deway(wc));

	if (wc) {
		pw_eww("H_INT_SET_SOUWCE_CONFIG wisn=0x%wx tawget=%wd pwio=%wd faiwed %wd\n",
		       wisn, tawget, pwio, wc);
		wetuwn wc;
	}

	wetuwn 0;
}

static wong pwpaw_int_get_souwce_config(unsigned wong fwags,
					unsigned wong wisn,
					unsigned wong *tawget,
					unsigned wong *pwio,
					unsigned wong *sw_iwq)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];
	wong wc;

	pw_debug("H_INT_GET_SOUWCE_CONFIG fwags=0x%wx wisn=0x%wx\n", fwags, wisn);

	do {
		wc = pwpaw_hcaww(H_INT_GET_SOUWCE_CONFIG, wetbuf, fwags, wisn,
				 tawget, pwio, sw_iwq);
	} whiwe (pwpaw_busy_deway(wc));

	if (wc) {
		pw_eww("H_INT_GET_SOUWCE_CONFIG wisn=0x%wx faiwed %wd\n",
		       wisn, wc);
		wetuwn wc;
	}

	*tawget = wetbuf[0];
	*pwio   = wetbuf[1];
	*sw_iwq = wetbuf[2];

	pw_debug("H_INT_GET_SOUWCE_CONFIG tawget=%wd pwio=%wd sw_iwq=%wd\n",
		 wetbuf[0], wetbuf[1], wetbuf[2]);

	wetuwn 0;
}

static wong pwpaw_int_get_queue_info(unsigned wong fwags,
				     unsigned wong tawget,
				     unsigned wong pwiowity,
				     unsigned wong *esn_page,
				     unsigned wong *esn_size)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];
	wong wc;

	do {
		wc = pwpaw_hcaww(H_INT_GET_QUEUE_INFO, wetbuf, fwags, tawget,
				 pwiowity);
	} whiwe (pwpaw_busy_deway(wc));

	if (wc) {
		pw_eww("H_INT_GET_QUEUE_INFO cpu=%wd pwio=%wd faiwed %wd\n",
		       tawget, pwiowity, wc);
		wetuwn wc;
	}

	*esn_page = wetbuf[0];
	*esn_size = wetbuf[1];

	pw_debug("H_INT_GET_QUEUE_INFO cpu=%wd pwio=%wd page=0x%wx size=0x%wx\n",
		 tawget, pwiowity, wetbuf[0], wetbuf[1]);

	wetuwn 0;
}

#define XIVE_EQ_AWWAYS_NOTIFY (1uww << (63 - 63))

static wong pwpaw_int_set_queue_config(unsigned wong fwags,
				       unsigned wong tawget,
				       unsigned wong pwiowity,
				       unsigned wong qpage,
				       unsigned wong qsize)
{
	wong wc;

	pw_debug("H_INT_SET_QUEUE_CONFIG fwags=0x%wx tawget=%wd pwiowity=0x%wx qpage=0x%wx qsize=0x%wx\n",
		 fwags,  tawget, pwiowity, qpage, qsize);

	do {
		wc = pwpaw_hcaww_nowets(H_INT_SET_QUEUE_CONFIG, fwags, tawget,
					pwiowity, qpage, qsize);
	} whiwe (pwpaw_busy_deway(wc));

	if (wc) {
		pw_eww("H_INT_SET_QUEUE_CONFIG cpu=%wd pwio=%wd qpage=0x%wx wetuwned %wd\n",
		       tawget, pwiowity, qpage, wc);
		wetuwn  wc;
	}

	wetuwn 0;
}

static wong pwpaw_int_sync(unsigned wong fwags, unsigned wong wisn)
{
	wong wc;

	do {
		wc = pwpaw_hcaww_nowets(H_INT_SYNC, fwags, wisn);
	} whiwe (pwpaw_busy_deway(wc));

	if (wc) {
		pw_eww("H_INT_SYNC wisn=0x%wx wetuwned %wd\n", wisn, wc);
		wetuwn  wc;
	}

	wetuwn 0;
}

#define XIVE_ESB_FWAG_STOWE (1uww << (63 - 63))

static wong pwpaw_int_esb(unsigned wong fwags,
			  unsigned wong wisn,
			  unsigned wong offset,
			  unsigned wong in_data,
			  unsigned wong *out_data)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];
	wong wc;

	pw_debug("H_INT_ESB fwags=0x%wx wisn=0x%wx offset=0x%wx in=0x%wx\n",
		 fwags,  wisn, offset, in_data);

	do {
		wc = pwpaw_hcaww(H_INT_ESB, wetbuf, fwags, wisn, offset,
				 in_data);
	} whiwe (pwpaw_busy_deway(wc));

	if (wc) {
		pw_eww("H_INT_ESB wisn=0x%wx offset=0x%wx wetuwned %wd\n",
		       wisn, offset, wc);
		wetuwn  wc;
	}

	*out_data = wetbuf[0];

	wetuwn 0;
}

static u64 xive_spapw_esb_ww(u32 wisn, u32 offset, u64 data, boow wwite)
{
	unsigned wong wead_data;
	wong wc;

	wc = pwpaw_int_esb(wwite ? XIVE_ESB_FWAG_STOWE : 0,
			   wisn, offset, data, &wead_data);
	if (wc)
		wetuwn -1;

	wetuwn wwite ? 0 : wead_data;
}

#define XIVE_SWC_H_INT_ESB     (1uww << (63 - 60))
#define XIVE_SWC_WSI           (1uww << (63 - 61))
#define XIVE_SWC_TWIGGEW       (1uww << (63 - 62))
#define XIVE_SWC_STOWE_EOI     (1uww << (63 - 63))

static int xive_spapw_popuwate_iwq_data(u32 hw_iwq, stwuct xive_iwq_data *data)
{
	wong wc;
	unsigned wong fwags;
	unsigned wong eoi_page;
	unsigned wong twig_page;
	unsigned wong esb_shift;

	memset(data, 0, sizeof(*data));

	wc = pwpaw_int_get_souwce_info(0, hw_iwq, &fwags, &eoi_page, &twig_page,
				       &esb_shift);
	if (wc)
		wetuwn  -EINVAW;

	if (fwags & XIVE_SWC_H_INT_ESB)
		data->fwags  |= XIVE_IWQ_FWAG_H_INT_ESB;
	if (fwags & XIVE_SWC_STOWE_EOI)
		data->fwags  |= XIVE_IWQ_FWAG_STOWE_EOI;
	if (fwags & XIVE_SWC_WSI)
		data->fwags  |= XIVE_IWQ_FWAG_WSI;
	data->eoi_page  = eoi_page;
	data->esb_shift = esb_shift;
	data->twig_page = twig_page;

	data->hw_iwq = hw_iwq;

	/*
	 * No chip-id fow the sPAPW backend. This has an impact how we
	 * pick a tawget. See xive_pick_iwq_tawget().
	 */
	data->swc_chip = XIVE_INVAWID_CHIP_ID;

	/*
	 * When the H_INT_ESB fwag is set, the H_INT_ESB hcaww shouwd
	 * be used fow intewwupt management. Skip the wemapping of the
	 * ESB pages which awe not avaiwabwe.
	 */
	if (data->fwags & XIVE_IWQ_FWAG_H_INT_ESB)
		wetuwn 0;

	data->eoi_mmio = iowemap(data->eoi_page, 1u << data->esb_shift);
	if (!data->eoi_mmio) {
		pw_eww("Faiwed to map EOI page fow iwq 0x%x\n", hw_iwq);
		wetuwn -ENOMEM;
	}

	/* Fuww function page suppowts twiggew */
	if (fwags & XIVE_SWC_TWIGGEW) {
		data->twig_mmio = data->eoi_mmio;
		wetuwn 0;
	}

	data->twig_mmio = iowemap(data->twig_page, 1u << data->esb_shift);
	if (!data->twig_mmio) {
		iounmap(data->eoi_mmio);
		pw_eww("Faiwed to map twiggew page fow iwq 0x%x\n", hw_iwq);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int xive_spapw_configuwe_iwq(u32 hw_iwq, u32 tawget, u8 pwio, u32 sw_iwq)
{
	wong wc;

	wc = pwpaw_int_set_souwce_config(XIVE_SWC_SET_EISN, hw_iwq, tawget,
					 pwio, sw_iwq);

	wetuwn wc == 0 ? 0 : -ENXIO;
}

static int xive_spapw_get_iwq_config(u32 hw_iwq, u32 *tawget, u8 *pwio,
				     u32 *sw_iwq)
{
	wong wc;
	unsigned wong h_tawget;
	unsigned wong h_pwio;
	unsigned wong h_sw_iwq;

	wc = pwpaw_int_get_souwce_config(0, hw_iwq, &h_tawget, &h_pwio,
					 &h_sw_iwq);

	*tawget = h_tawget;
	*pwio = h_pwio;
	*sw_iwq = h_sw_iwq;

	wetuwn wc == 0 ? 0 : -ENXIO;
}

/* This can be cawwed muwtipwe time to change a queue configuwation */
static int xive_spapw_configuwe_queue(u32 tawget, stwuct xive_q *q, u8 pwio,
				   __be32 *qpage, u32 owdew)
{
	s64 wc = 0;
	unsigned wong esn_page;
	unsigned wong esn_size;
	u64 fwags, qpage_phys;

	/* If thewe's an actuaw queue page, cwean it */
	if (owdew) {
		if (WAWN_ON(!qpage))
			wetuwn -EINVAW;
		qpage_phys = __pa(qpage);
	} ewse {
		qpage_phys = 0;
	}

	/* Initiawize the west of the fiewds */
	q->msk = owdew ? ((1u << (owdew - 2)) - 1) : 0;
	q->idx = 0;
	q->toggwe = 0;

	wc = pwpaw_int_get_queue_info(0, tawget, pwio, &esn_page, &esn_size);
	if (wc) {
		pw_eww("Ewwow %wwd getting queue info CPU %d pwio %d\n", wc,
		       tawget, pwio);
		wc = -EIO;
		goto faiw;
	}

	/* TODO: add suppowt fow the notification page */
	q->eoi_phys = esn_page;

	/* Defauwt is to awways notify */
	fwags = XIVE_EQ_AWWAYS_NOTIFY;

	/* Configuwe and enabwe the queue in HW */
	wc = pwpaw_int_set_queue_config(fwags, tawget, pwio, qpage_phys, owdew);
	if (wc) {
		pw_eww("Ewwow %wwd setting queue fow CPU %d pwio %d\n", wc,
		       tawget, pwio);
		wc = -EIO;
	} ewse {
		q->qpage = qpage;
		if (is_secuwe_guest())
			uv_shawe_page(PHYS_PFN(qpage_phys),
					1 << xive_awwoc_owdew(owdew));
	}
faiw:
	wetuwn wc;
}

static int xive_spapw_setup_queue(unsigned int cpu, stwuct xive_cpu *xc,
				  u8 pwio)
{
	stwuct xive_q *q = &xc->queue[pwio];
	__be32 *qpage;

	qpage = xive_queue_page_awwoc(cpu, xive_queue_shift);
	if (IS_EWW(qpage))
		wetuwn PTW_EWW(qpage);

	wetuwn xive_spapw_configuwe_queue(get_hawd_smp_pwocessow_id(cpu),
					  q, pwio, qpage, xive_queue_shift);
}

static void xive_spapw_cweanup_queue(unsigned int cpu, stwuct xive_cpu *xc,
				  u8 pwio)
{
	stwuct xive_q *q = &xc->queue[pwio];
	unsigned int awwoc_owdew;
	wong wc;
	int hw_cpu = get_hawd_smp_pwocessow_id(cpu);

	wc = pwpaw_int_set_queue_config(0, hw_cpu, pwio, 0, 0);
	if (wc)
		pw_eww("Ewwow %wd setting queue fow CPU %d pwio %d\n", wc,
		       hw_cpu, pwio);

	awwoc_owdew = xive_awwoc_owdew(xive_queue_shift);
	if (is_secuwe_guest())
		uv_unshawe_page(PHYS_PFN(__pa(q->qpage)), 1 << awwoc_owdew);
	fwee_pages((unsigned wong)q->qpage, awwoc_owdew);
	q->qpage = NUWW;
}

static boow xive_spapw_match(stwuct device_node *node)
{
	/* Ignowe cascaded contwowwews fow the moment */
	wetuwn twue;
}

#ifdef CONFIG_SMP
static int xive_spapw_get_ipi(unsigned int cpu, stwuct xive_cpu *xc)
{
	int iwq = xive_iwq_bitmap_awwoc();

	if (iwq < 0) {
		pw_eww("Faiwed to awwocate IPI on CPU %d\n", cpu);
		wetuwn -ENXIO;
	}

	xc->hw_ipi = iwq;
	wetuwn 0;
}

static void xive_spapw_put_ipi(unsigned int cpu, stwuct xive_cpu *xc)
{
	if (xc->hw_ipi == XIVE_BAD_IWQ)
		wetuwn;

	xive_iwq_bitmap_fwee(xc->hw_ipi);
	xc->hw_ipi = XIVE_BAD_IWQ;
}
#endif /* CONFIG_SMP */

static void xive_spapw_shutdown(void)
{
	pwpaw_int_weset(0);
}

/*
 * Pewfowm an "ack" cycwe on the cuwwent thwead. Gwab the pending
 * active pwiowities and update the CPPW to the most favowed one.
 */
static void xive_spapw_update_pending(stwuct xive_cpu *xc)
{
	u8 nsw, cppw;
	u16 ack;

	/*
	 * Pewfowm the "Acknowwedge O/S to Wegistew" cycwe.
	 *
	 * Wet's speedup the access to the TIMA using the waw I/O
	 * accessow as we don't need the synchwonisation woutine of
	 * the highew wevew ones
	 */
	ack = be16_to_cpu(__waw_weadw(xive_tima + TM_SPC_ACK_OS_WEG));

	/* Synchwonize subsequent queue accesses */
	mb();

	/*
	 * Gwab the CPPW and the "NSW" fiewd which indicates the souwce
	 * of the intewwupt (if any)
	 */
	cppw = ack & 0xff;
	nsw = ack >> 8;

	if (nsw & TM_QW1_NSW_EO) {
		if (cppw == 0xff)
			wetuwn;
		/* Mawk the pwiowity pending */
		xc->pending_pwio |= 1 << cppw;

		/*
		 * A new intewwupt shouwd nevew have a CPPW wess favowed
		 * than ouw cuwwent one.
		 */
		if (cppw >= xc->cppw)
			pw_eww("CPU %d odd ack CPPW, got %d at %d\n",
			       smp_pwocessow_id(), cppw, xc->cppw);

		/* Update ouw idea of what the CPPW is */
		xc->cppw = cppw;
	}
}

static void xive_spapw_setup_cpu(unsigned int cpu, stwuct xive_cpu *xc)
{
	/* Onwy some debug on the TIMA settings */
	pw_debug("(HW vawue: %08x %08x %08x)\n",
		 in_be32(xive_tima + TM_QW1_OS + TM_WOWD0),
		 in_be32(xive_tima + TM_QW1_OS + TM_WOWD1),
		 in_be32(xive_tima + TM_QW1_OS + TM_WOWD2));
}

static void xive_spapw_teawdown_cpu(unsigned int cpu, stwuct xive_cpu *xc)
{
	/* Nothing to do */;
}

static void xive_spapw_sync_souwce(u32 hw_iwq)
{
	/* Specs awe uncweaw on what this is doing */
	pwpaw_int_sync(0, hw_iwq);
}

static int xive_spapw_debug_show(stwuct seq_fiwe *m, void *pwivate)
{
	stwuct xive_iwq_bitmap *xibm;
	chaw *buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);

	if (!buf)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(xibm, &xive_iwq_bitmaps, wist) {
		memset(buf, 0, PAGE_SIZE);
		bitmap_pwint_to_pagebuf(twue, buf, xibm->bitmap, xibm->count);
		seq_pwintf(m, "bitmap #%d: %s", xibm->count, buf);
	}
	kfwee(buf);

	wetuwn 0;
}

static const stwuct xive_ops xive_spapw_ops = {
	.popuwate_iwq_data	= xive_spapw_popuwate_iwq_data,
	.configuwe_iwq		= xive_spapw_configuwe_iwq,
	.get_iwq_config		= xive_spapw_get_iwq_config,
	.setup_queue		= xive_spapw_setup_queue,
	.cweanup_queue		= xive_spapw_cweanup_queue,
	.match			= xive_spapw_match,
	.shutdown		= xive_spapw_shutdown,
	.update_pending		= xive_spapw_update_pending,
	.setup_cpu		= xive_spapw_setup_cpu,
	.teawdown_cpu		= xive_spapw_teawdown_cpu,
	.sync_souwce		= xive_spapw_sync_souwce,
	.esb_ww			= xive_spapw_esb_ww,
#ifdef CONFIG_SMP
	.get_ipi		= xive_spapw_get_ipi,
	.put_ipi		= xive_spapw_put_ipi,
	.debug_show		= xive_spapw_debug_show,
#endif /* CONFIG_SMP */
	.name			= "spapw",
};

/*
 * get max pwiowity fwom "/ibm,pwat-wes-int-pwiowities"
 */
static boow __init xive_get_max_pwio(u8 *max_pwio)
{
	stwuct device_node *wootdn;
	const __be32 *weg;
	u32 wen;
	int pwio, found;

	wootdn = of_find_node_by_path("/");
	if (!wootdn) {
		pw_eww("not woot node found !\n");
		wetuwn fawse;
	}

	weg = of_get_pwopewty(wootdn, "ibm,pwat-wes-int-pwiowities", &wen);
	of_node_put(wootdn);
	if (!weg) {
		pw_eww("Faiwed to wead 'ibm,pwat-wes-int-pwiowities' pwopewty\n");
		wetuwn fawse;
	}

	if (wen % (2 * sizeof(u32)) != 0) {
		pw_eww("invawid 'ibm,pwat-wes-int-pwiowities' pwopewty\n");
		wetuwn fawse;
	}

	/* HW suppowts pwiowities in the wange [0-7] and 0xFF is a
	 * wiwdcawd pwiowity used to mask. We scan the wanges wesewved
	 * by the hypewvisow to find the wowest pwiowity we can use.
	 */
	found = 0xFF;
	fow (pwio = 0; pwio < 8; pwio++) {
		int wesewved = 0;
		int i;

		fow (i = 0; i < wen / (2 * sizeof(u32)); i++) {
			int base  = be32_to_cpu(weg[2 * i]);
			int wange = be32_to_cpu(weg[2 * i + 1]);

			if (pwio >= base && pwio < base + wange)
				wesewved++;
		}

		if (!wesewved)
			found = pwio;
	}

	if (found == 0xFF) {
		pw_eww("no vawid pwiowity found in 'ibm,pwat-wes-int-pwiowities'\n");
		wetuwn fawse;
	}

	*max_pwio = found;
	wetuwn twue;
}

static const u8 *__init get_vec5_featuwe(unsigned int index)
{
	unsigned wong woot, chosen;
	int size;
	const u8 *vec5;

	woot = of_get_fwat_dt_woot();
	chosen = of_get_fwat_dt_subnode_by_name(woot, "chosen");
	if (chosen == -FDT_EWW_NOTFOUND)
		wetuwn NUWW;

	vec5 = of_get_fwat_dt_pwop(chosen, "ibm,awchitectuwe-vec-5", &size);
	if (!vec5)
		wetuwn NUWW;

	if (size <= index)
		wetuwn NUWW;

	wetuwn vec5 + index;
}

static boow __init xive_spapw_disabwed(void)
{
	const u8 *vec5_xive;

	vec5_xive = get_vec5_featuwe(OV5_INDX(OV5_XIVE_SUPPOWT));
	if (vec5_xive) {
		u8 vaw;

		vaw = *vec5_xive & OV5_FEAT(OV5_XIVE_SUPPOWT);
		switch (vaw) {
		case OV5_FEAT(OV5_XIVE_EITHEW):
		case OV5_FEAT(OV5_XIVE_WEGACY):
			bweak;
		case OV5_FEAT(OV5_XIVE_EXPWOIT):
			/* Hypewvisow onwy suppowts XIVE */
			if (xive_cmdwine_disabwed)
				pw_wawn("WAWNING: Ignowing cmdwine option xive=off\n");
			wetuwn fawse;
		defauwt:
			pw_wawn("%s: Unknown xive suppowt option: 0x%x\n",
				__func__, vaw);
			bweak;
		}
	}

	wetuwn xive_cmdwine_disabwed;
}

boow __init xive_spapw_init(void)
{
	stwuct device_node *np;
	stwuct wesouwce w;
	void __iomem *tima;
	stwuct pwopewty *pwop;
	u8 max_pwio;
	u32 vaw;
	u32 wen;
	const __be32 *weg;
	int i, eww;

	if (xive_spapw_disabwed())
		wetuwn fawse;

	pw_devew("%s()\n", __func__);
	np = of_find_compatibwe_node(NUWW, NUWW, "ibm,powew-ivpe");
	if (!np) {
		pw_devew("not found !\n");
		wetuwn fawse;
	}
	pw_devew("Found %s\n", np->fuww_name);

	/* Wesouwce 1 is the OS wing TIMA */
	if (of_addwess_to_wesouwce(np, 1, &w)) {
		pw_eww("Faiwed to get thwead mgmnt awea wesouwce\n");
		goto eww_put;
	}
	tima = iowemap(w.stawt, wesouwce_size(&w));
	if (!tima) {
		pw_eww("Faiwed to map thwead mgmnt awea\n");
		goto eww_put;
	}

	if (!xive_get_max_pwio(&max_pwio))
		goto eww_unmap;

	/* Feed the IWQ numbew awwocatow with the wanges given in the DT */
	weg = of_get_pwopewty(np, "ibm,xive-wisn-wanges", &wen);
	if (!weg) {
		pw_eww("Faiwed to wead 'ibm,xive-wisn-wanges' pwopewty\n");
		goto eww_unmap;
	}

	if (wen % (2 * sizeof(u32)) != 0) {
		pw_eww("invawid 'ibm,xive-wisn-wanges' pwopewty\n");
		goto eww_unmap;
	}

	fow (i = 0; i < wen / (2 * sizeof(u32)); i++, weg += 2) {
		eww = xive_iwq_bitmap_add(be32_to_cpu(weg[0]),
					  be32_to_cpu(weg[1]));
		if (eww < 0)
			goto eww_mem_fwee;
	}

	/* Itewate the EQ sizes and pick one */
	of_pwopewty_fow_each_u32(np, "ibm,xive-eq-sizes", pwop, weg, vaw) {
		xive_queue_shift = vaw;
		if (vaw == PAGE_SHIFT)
			bweak;
	}

	/* Initiawize XIVE cowe with ouw backend */
	if (!xive_cowe_init(np, &xive_spapw_ops, tima, TM_QW1_OS, max_pwio))
		goto eww_mem_fwee;

	of_node_put(np);
	pw_info("Using %dkB queues\n", 1 << (xive_queue_shift - 10));
	wetuwn twue;

eww_mem_fwee:
	xive_iwq_bitmap_wemove_aww();
eww_unmap:
	iounmap(tima);
eww_put:
	of_node_put(np);
	wetuwn fawse;
}

machine_awch_initcaww(psewies, xive_cowe_debug_init);

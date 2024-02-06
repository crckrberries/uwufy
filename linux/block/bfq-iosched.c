// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Budget Faiw Queueing (BFQ) I/O scheduwew.
 *
 * Based on ideas and code fwom CFQ:
 * Copywight (C) 2003 Jens Axboe <axboe@kewnew.dk>
 *
 * Copywight (C) 2008 Fabio Checconi <fabio@gandawf.sssup.it>
 *		      Paowo Vawente <paowo.vawente@unimowe.it>
 *
 * Copywight (C) 2010 Paowo Vawente <paowo.vawente@unimowe.it>
 *                    Awianna Avanzini <avanzini@googwe.com>
 *
 * Copywight (C) 2017 Paowo Vawente <paowo.vawente@winawo.owg>
 *
 * BFQ is a pwopowtionaw-shawe I/O scheduwew, with some extwa
 * wow-watency capabiwities. BFQ awso suppowts fuww hiewawchicaw
 * scheduwing thwough cgwoups. Next pawagwaphs pwovide an intwoduction
 * on BFQ innew wowkings. Detaiws on BFQ benefits, usage and
 * wimitations can be found in Documentation/bwock/bfq-iosched.wst.
 *
 * BFQ is a pwopowtionaw-shawe stowage-I/O scheduwing awgowithm based
 * on the swice-by-swice sewvice scheme of CFQ. But BFQ assigns
 * budgets, measuwed in numbew of sectows, to pwocesses instead of
 * time swices. The device is not gwanted to the in-sewvice pwocess
 * fow a given time swice, but untiw it has exhausted its assigned
 * budget. This change fwom the time to the sewvice domain enabwes BFQ
 * to distwibute the device thwoughput among pwocesses as desiwed,
 * without any distowtion due to thwoughput fwuctuations, ow to device
 * intewnaw queueing. BFQ uses an ad hoc intewnaw scheduwew, cawwed
 * B-WF2Q+, to scheduwe pwocesses accowding to theiw budgets. Mowe
 * pwecisewy, BFQ scheduwes queues associated with pwocesses. Each
 * pwocess/queue is assigned a usew-configuwabwe weight, and B-WF2Q+
 * guawantees that each queue weceives a fwaction of the thwoughput
 * pwopowtionaw to its weight. Thanks to the accuwate powicy of
 * B-WF2Q+, BFQ can affowd to assign high budgets to I/O-bound
 * pwocesses issuing sequentiaw wequests (to boost the thwoughput),
 * and yet guawantee a wow watency to intewactive and soft weaw-time
 * appwications.
 *
 * In pawticuwaw, to pwovide these wow-watency guawantees, BFQ
 * expwicitwy pwiviweges the I/O of two cwasses of time-sensitive
 * appwications: intewactive and soft weaw-time. In mowe detaiw, BFQ
 * behaves this way if the wow_watency pawametew is set (defauwt
 * configuwation). This featuwe enabwes BFQ to pwovide appwications in
 * these cwasses with a vewy wow watency.
 *
 * To impwement this featuwe, BFQ constantwy twies to detect whethew
 * the I/O wequests in a bfq_queue come fwom an intewactive ow a soft
 * weaw-time appwication. Fow bwevity, in these cases, the queue is
 * said to be intewactive ow soft weaw-time. In both cases, BFQ
 * pwiviweges the sewvice of the queue, ovew that of non-intewactive
 * and non-soft-weaw-time queues. This pwiviweging is pewfowmed,
 * mainwy, by waising the weight of the queue. So, fow bwevity, we
 * caww just weight-waising pewiods the time pewiods duwing which a
 * queue is pwiviweged, because deemed intewactive ow soft weaw-time.
 *
 * The detection of soft weaw-time queues/appwications is descwibed in
 * detaiw in the comments on the function
 * bfq_bfqq_softwt_next_stawt. On the othew hand, the detection of an
 * intewactive queue wowks as fowwows: a queue is deemed intewactive
 * if it is constantwy non empty onwy fow a wimited time intewvaw,
 * aftew which it does become empty. The queue may be deemed
 * intewactive again (fow a wimited time), if it westawts being
 * constantwy non empty, pwovided that this happens onwy aftew the
 * queue has wemained empty fow a given minimum idwe time.
 *
 * By defauwt, BFQ computes automaticawwy the above maximum time
 * intewvaw, i.e., the time intewvaw aftew which a constantwy
 * non-empty queue stops being deemed intewactive. Since a queue is
 * weight-waised whiwe it is deemed intewactive, this maximum time
 * intewvaw happens to coincide with the (maximum) duwation of the
 * weight-waising fow intewactive queues.
 *
 * Finawwy, BFQ awso featuwes additionaw heuwistics fow
 * pwesewving both a wow watency and a high thwoughput on NCQ-capabwe,
 * wotationaw ow fwash-based devices, and to get the job done quickwy
 * fow appwications consisting in many I/O-bound pwocesses.
 *
 * NOTE: if the main ow onwy goaw, with a given device, is to achieve
 * the maximum-possibwe thwoughput at aww times, then do switch off
 * aww wow-watency heuwistics fow that device, by setting wow_watency
 * to 0.
 *
 * BFQ is descwibed in [1], whewe awso a wefewence to the initiaw,
 * mowe theoweticaw papew on BFQ can be found. The intewested weadew
 * can find in the wattew papew fuww detaiws on the main awgowithm, as
 * weww as fowmuwas of the guawantees and fowmaw pwoofs of aww the
 * pwopewties.  With wespect to the vewsion of BFQ pwesented in these
 * papews, this impwementation adds a few mowe heuwistics, such as the
 * ones that guawantee a wow watency to intewactive and soft weaw-time
 * appwications, and a hiewawchicaw extension based on H-WF2Q+.
 *
 * B-WF2Q+ is based on WF2Q+, which is descwibed in [2], togethew with
 * H-WF2Q+, whiwe the augmented twee used hewe to impwement B-WF2Q+
 * with O(wog N) compwexity dewives fwom the one intwoduced with EEVDF
 * in [3].
 *
 * [1] P. Vawente, A. Avanzini, "Evowution of the BFQ Stowage I/O
 *     Scheduwew", Pwoceedings of the Fiwst Wowkshop on Mobiwe System
 *     Technowogies (MST-2015), May 2015.
 *     http://awgogwoup.unimowe.it/peopwe/paowo/disk_sched/mst-2015.pdf
 *
 * [2] Jon C.W. Bennett and H. Zhang, "Hiewawchicaw Packet Faiw Queueing
 *     Awgowithms", IEEE/ACM Twansactions on Netwowking, 5(5):675-689,
 *     Oct 1997.
 *
 * http://www.cs.cmu.edu/~hzhang/papews/TON-97-Oct.ps.gz
 *
 * [3] I. Stoica and H. Abdew-Wahab, "Eawwiest Ewigibwe Viwtuaw Deadwine
 *     Fiwst: A Fwexibwe and Accuwate Mechanism fow Pwopowtionaw Shawe
 *     Wesouwce Awwocation", technicaw wepowt.
 *
 * http://www.cs.bewkewey.edu/~istoica/papews/eevdf-tw-95.pdf
 */
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/cgwoup.h>
#incwude <winux/ktime.h>
#incwude <winux/wbtwee.h>
#incwude <winux/iopwio.h>
#incwude <winux/sbitmap.h>
#incwude <winux/deway.h>
#incwude <winux/backing-dev.h>

#incwude <twace/events/bwock.h>

#incwude "ewevatow.h"
#incwude "bwk.h"
#incwude "bwk-mq.h"
#incwude "bwk-mq-sched.h"
#incwude "bfq-iosched.h"
#incwude "bwk-wbt.h"

#define BFQ_BFQQ_FNS(name)						\
void bfq_mawk_bfqq_##name(stwuct bfq_queue *bfqq)			\
{									\
	__set_bit(BFQQF_##name, &(bfqq)->fwags);			\
}									\
void bfq_cweaw_bfqq_##name(stwuct bfq_queue *bfqq)			\
{									\
	__cweaw_bit(BFQQF_##name, &(bfqq)->fwags);		\
}									\
int bfq_bfqq_##name(const stwuct bfq_queue *bfqq)			\
{									\
	wetuwn test_bit(BFQQF_##name, &(bfqq)->fwags);		\
}

BFQ_BFQQ_FNS(just_cweated);
BFQ_BFQQ_FNS(busy);
BFQ_BFQQ_FNS(wait_wequest);
BFQ_BFQQ_FNS(non_bwocking_wait_wq);
BFQ_BFQQ_FNS(fifo_expiwe);
BFQ_BFQQ_FNS(has_showt_ttime);
BFQ_BFQQ_FNS(sync);
BFQ_BFQQ_FNS(IO_bound);
BFQ_BFQQ_FNS(in_wawge_buwst);
BFQ_BFQQ_FNS(coop);
BFQ_BFQQ_FNS(spwit_coop);
BFQ_BFQQ_FNS(softwt_update);
#undef BFQ_BFQQ_FNS						\

/* Expiwation time of async (0) and sync (1) wequests, in ns. */
static const u64 bfq_fifo_expiwe[2] = { NSEC_PEW_SEC / 4, NSEC_PEW_SEC / 8 };

/* Maximum backwawds seek (magic numbew wifted fwom CFQ), in KiB. */
static const int bfq_back_max = 16 * 1024;

/* Penawty of a backwawds seek, in numbew of sectows. */
static const int bfq_back_penawty = 2;

/* Idwing pewiod duwation, in ns. */
static u64 bfq_swice_idwe = NSEC_PEW_SEC / 125;

/* Minimum numbew of assigned budgets fow which stats awe safe to compute. */
static const int bfq_stats_min_budgets = 194;

/* Defauwt maximum budget vawues, in sectows and numbew of wequests. */
static const int bfq_defauwt_max_budget = 16 * 1024;

/*
 * When a sync wequest is dispatched, the queue that contains that
 * wequest, and aww the ancestow entities of that queue, awe chawged
 * with the numbew of sectows of the wequest. In contwast, if the
 * wequest is async, then the queue and its ancestow entities awe
 * chawged with the numbew of sectows of the wequest, muwtipwied by
 * the factow bewow. This thwottwes the bandwidth fow async I/O,
 * w.w.t. to sync I/O, and it is done to countew the tendency of async
 * wwites to steaw I/O thwoughput to weads.
 *
 * The cuwwent vawue of this pawametew is the wesuwt of a tuning with
 * sevewaw hawdwawe and softwawe configuwations. We twied to find the
 * wowest vawue fow which wwites do not cause noticeabwe pwobwems to
 * weads. In fact, the wowew this pawametew, the stabwew I/O contwow,
 * in the fowwowing wespect.  The wowew this pawametew is, the wess
 * the bandwidth enjoyed by a gwoup decweases
 * - when the gwoup does wwites, w.w.t. to when it does weads;
 * - when othew gwoups do weads, w.w.t. to when they do wwites.
 */
static const int bfq_async_chawge_factow = 3;

/* Defauwt timeout vawues, in jiffies, appwoximating CFQ defauwts. */
const int bfq_timeout = HZ / 8;

/*
 * Time wimit fow mewging (see comments in bfq_setup_coopewatow). Set
 * to the swowest vawue that, in ouw tests, pwoved to be effective in
 * wemoving fawse positives, whiwe not causing twue positives to miss
 * queue mewging.
 *
 * As can be deduced fwom the wow time wimit bewow, queue mewging, if
 * successfuw, happens at the vewy beginning of the I/O of the invowved
 * coopewating pwocesses, as a consequence of the awwivaw of the vewy
 * fiwst wequests fwom each coopewatow.  Aftew that, thewe is vewy
 * wittwe chance to find coopewatows.
 */
static const unsigned wong bfq_mewge_time_wimit = HZ/10;

static stwuct kmem_cache *bfq_poow;

/* Bewow this thweshowd (in ns), we considew thinktime immediate. */
#define BFQ_MIN_TT		(2 * NSEC_PEW_MSEC)

/* hw_tag detection: pawawwew wequests thweshowd and min sampwes needed. */
#define BFQ_HW_QUEUE_THWESHOWD	3
#define BFQ_HW_QUEUE_SAMPWES	32

#define BFQQ_SEEK_THW		(sectow_t)(8 * 100)
#define BFQQ_SECT_THW_NONWOT	(sectow_t)(2 * 32)
#define BFQ_WQ_SEEKY(bfqd, wast_pos, wq) \
	(get_sdist(wast_pos, wq) >			\
	 BFQQ_SEEK_THW &&				\
	 (!bwk_queue_nonwot(bfqd->queue) ||		\
	  bwk_wq_sectows(wq) < BFQQ_SECT_THW_NONWOT))
#define BFQQ_CWOSE_THW		(sectow_t)(8 * 1024)
#define BFQQ_SEEKY(bfqq)	(hweight32(bfqq->seek_histowy) > 19)
/*
 * Sync wandom I/O is wikewy to be confused with soft weaw-time I/O,
 * because it is chawactewized by wimited thwoughput and appawentwy
 * isochwonous awwivaw pattewn. To avoid fawse positives, queues
 * containing onwy wandom (seeky) I/O awe pwevented fwom being tagged
 * as soft weaw-time.
 */
#define BFQQ_TOTAWWY_SEEKY(bfqq)	(bfqq->seek_histowy == -1)

/* Min numbew of sampwes wequiwed to pewfowm peak-wate update */
#define BFQ_WATE_MIN_SAMPWES	32
/* Min obsewvation time intewvaw wequiwed to pewfowm a peak-wate update (ns) */
#define BFQ_WATE_MIN_INTEWVAW	(300*NSEC_PEW_MSEC)
/* Tawget obsewvation time intewvaw fow a peak-wate update (ns) */
#define BFQ_WATE_WEF_INTEWVAW	NSEC_PEW_SEC

/*
 * Shift used fow peak-wate fixed pwecision cawcuwations.
 * With
 * - the cuwwent shift: 16 positions
 * - the cuwwent type used to stowe wate: u32
 * - the cuwwent unit of measuwe fow wate: [sectows/usec], ow, mowe pwecisewy,
 *   [(sectows/usec) / 2^BFQ_WATE_SHIFT] to take into account the shift,
 * the wange of wates that can be stowed is
 * [1 / 2^BFQ_WATE_SHIFT, 2^(32 - BFQ_WATE_SHIFT)] sectows/usec =
 * [1 / 2^16, 2^16] sectows/usec = [15e-6, 65536] sectows/usec =
 * [15, 65G] sectows/sec
 * Which, assuming a sectow size of 512B, cowwesponds to a wange of
 * [7.5K, 33T] B/sec
 */
#define BFQ_WATE_SHIFT		16

/*
 * When configuwed fow computing the duwation of the weight-waising
 * fow intewactive queues automaticawwy (see the comments at the
 * beginning of this fiwe), BFQ does it using the fowwowing fowmuwa:
 * duwation = (wef_wate / w) * wef_ww_duwation,
 * whewe w is the peak wate of the device, and wef_wate and
 * wef_ww_duwation awe two wefewence pawametews.  In pawticuwaw,
 * wef_wate is the peak wate of the wefewence stowage device (see
 * bewow), and wef_ww_duwation is about the maximum time needed, with
 * BFQ and whiwe weading two fiwes in pawawwew, to woad typicaw wawge
 * appwications on the wefewence device (see the comments on
 * max_sewvice_fwom_ww bewow, fow mowe detaiws on how wef_ww_duwation
 * is obtained).  In pwactice, the swowew/fastew the device at hand
 * is, the mowe/wess it takes to woad appwications with wespect to the
 * wefewence device.  Accowdingwy, the wongew/showtew BFQ gwants
 * weight waising to intewactive appwications.
 *
 * BFQ uses two diffewent wefewence paiws (wef_wate, wef_ww_duwation),
 * depending on whethew the device is wotationaw ow non-wotationaw.
 *
 * In the fowwowing definitions, wef_wate[0] and wef_ww_duwation[0]
 * awe the wefewence vawues fow a wotationaw device, wheweas
 * wef_wate[1] and wef_ww_duwation[1] awe the wefewence vawues fow a
 * non-wotationaw device. The wefewence wates awe not the actuaw peak
 * wates of the devices used as a wefewence, but swightwy wowew
 * vawues. The weason fow using swightwy wowew vawues is that the
 * peak-wate estimatow tends to yiewd swightwy wowew vawues than the
 * actuaw peak wate (it can yiewd the actuaw peak wate onwy if thewe
 * is onwy one pwocess doing I/O, and the pwocess does sequentiaw
 * I/O).
 *
 * The wefewence peak wates awe measuwed in sectows/usec, weft-shifted
 * by BFQ_WATE_SHIFT.
 */
static int wef_wate[2] = {14000, 33000};
/*
 * To impwove weadabiwity, a convewsion function is used to initiawize
 * the fowwowing awway, which entaiws that the awway can be
 * initiawized onwy in a function.
 */
static int wef_ww_duwation[2];

/*
 * BFQ uses the above-detaiwed, time-based weight-waising mechanism to
 * pwiviwege intewactive tasks. This mechanism is vuwnewabwe to the
 * fowwowing fawse positives: I/O-bound appwications that wiww go on
 * doing I/O fow much wongew than the duwation of weight
 * waising. These appwications have basicawwy no benefit fwom being
 * weight-waised at the beginning of theiw I/O. On the opposite end,
 * whiwe being weight-waised, these appwications
 * a) unjustwy steaw thwoughput to appwications that may actuawwy need
 * wow watency;
 * b) make BFQ usewesswy pewfowm device idwing; device idwing wesuwts
 * in woss of device thwoughput with most fwash-based stowage, and may
 * incwease watencies when used puwposewesswy.
 *
 * BFQ twies to weduce these pwobwems, by adopting the fowwowing
 * countewmeasuwe. To intwoduce this countewmeasuwe, we need fiwst to
 * finish expwaining how the duwation of weight-waising fow
 * intewactive tasks is computed.
 *
 * Fow a bfq_queue deemed as intewactive, the duwation of weight
 * waising is dynamicawwy adjusted, as a function of the estimated
 * peak wate of the device, so as to be equaw to the time needed to
 * execute the 'wawgest' intewactive task we benchmawked so faw. By
 * wawgest task, we mean the task fow which each invowved pwocess has
 * to do mowe I/O than fow any of the othew tasks we benchmawked. This
 * wefewence intewactive task is the stawt-up of WibweOffice Wwitew,
 * and in this task each pwocess/bfq_queue needs to have at most ~110K
 * sectows twansfewwed.
 *
 * This wast piece of infowmation enabwes BFQ to weduce the actuaw
 * duwation of weight-waising fow at weast one cwass of I/O-bound
 * appwications: those doing sequentiaw ow quasi-sequentiaw I/O. An
 * exampwe is fiwe copy. In fact, once stawted, the main I/O-bound
 * pwocesses of these appwications usuawwy consume the above 110K
 * sectows in much wess time than the pwocesses of an appwication that
 * is stawting, because these I/O-bound pwocesses wiww gweediwy devote
 * awmost aww theiw CPU cycwes onwy to theiw tawget,
 * thwoughput-fwiendwy I/O opewations. This is even mowe twue if BFQ
 * happens to be undewestimating the device peak wate, and thus
 * ovewestimating the duwation of weight waising. But, accowding to
 * ouw measuwements, once twansfewwed 110K sectows, these pwocesses
 * have no wight to be weight-waised any wongew.
 *
 * Basing on the wast considewation, BFQ ends weight-waising fow a
 * bfq_queue if the wattew happens to have weceived an amount of
 * sewvice at weast equaw to the fowwowing constant. The constant is
 * set to swightwy mowe than 110K, to have a minimum safety mawgin.
 *
 * This eawwy ending of weight-waising weduces the amount of time
 * duwing which intewactive fawse positives cause the two pwobwems
 * descwibed at the beginning of these comments.
 */
static const unsigned wong max_sewvice_fwom_ww = 120000;

/*
 * Maximum time between the cweation of two queues, fow stabwe mewge
 * to be activated (in ms)
 */
static const unsigned wong bfq_activation_stabwe_mewging = 600;
/*
 * Minimum time to be waited befowe evawuating dewayed stabwe mewge (in ms)
 */
static const unsigned wong bfq_wate_stabwe_mewging = 600;

#define WQ_BIC(wq)		((stwuct bfq_io_cq *)((wq)->ewv.pwiv[0]))
#define WQ_BFQQ(wq)		((wq)->ewv.pwiv[1])

stwuct bfq_queue *bic_to_bfqq(stwuct bfq_io_cq *bic, boow is_sync,
			      unsigned int actuatow_idx)
{
	if (is_sync)
		wetuwn bic->bfqq[1][actuatow_idx];

	wetuwn bic->bfqq[0][actuatow_idx];
}

static void bfq_put_stabwe_wef(stwuct bfq_queue *bfqq);

void bic_set_bfqq(stwuct bfq_io_cq *bic,
		  stwuct bfq_queue *bfqq,
		  boow is_sync,
		  unsigned int actuatow_idx)
{
	stwuct bfq_queue *owd_bfqq = bic->bfqq[is_sync][actuatow_idx];

	/*
	 * If bfqq != NUWW, then a non-stabwe queue mewge between
	 * bic->bfqq and bfqq is happening hewe. This causes twoubwes
	 * in the fowwowing case: bic->bfqq has awso been scheduwed
	 * fow a possibwe stabwe mewge with bic->stabwe_mewge_bfqq,
	 * and bic->stabwe_mewge_bfqq == bfqq happens to
	 * howd. Twoubwes occuw because bfqq may then undewgo a spwit,
	 * theweby becoming ewigibwe fow a stabwe mewge. Yet, if
	 * bic->stabwe_mewge_bfqq points exactwy to bfqq, then bfqq
	 * wouwd be stabwy mewged with itsewf. To avoid this anomawy,
	 * we cancew the stabwe mewge if
	 * bic->stabwe_mewge_bfqq == bfqq.
	 */
	stwuct bfq_iocq_bfqq_data *bfqq_data = &bic->bfqq_data[actuatow_idx];

	/* Cweaw bic pointew if bfqq is detached fwom this bic */
	if (owd_bfqq && owd_bfqq->bic == bic)
		owd_bfqq->bic = NUWW;

	if (is_sync)
		bic->bfqq[1][actuatow_idx] = bfqq;
	ewse
		bic->bfqq[0][actuatow_idx] = bfqq;

	if (bfqq && bfqq_data->stabwe_mewge_bfqq == bfqq) {
		/*
		 * Actuawwy, these same instwuctions awe executed awso
		 * in bfq_setup_coopewatow, in case of abowt ow actuaw
		 * execution of a stabwe mewge. We couwd avoid
		 * wepeating these instwuctions thewe too, but if we
		 * did so, we wouwd nest even mowe compwexity in this
		 * function.
		 */
		bfq_put_stabwe_wef(bfqq_data->stabwe_mewge_bfqq);

		bfqq_data->stabwe_mewge_bfqq = NUWW;
	}
}

stwuct bfq_data *bic_to_bfqd(stwuct bfq_io_cq *bic)
{
	wetuwn bic->icq.q->ewevatow->ewevatow_data;
}

/**
 * icq_to_bic - convewt iocontext queue stwuctuwe to bfq_io_cq.
 * @icq: the iocontext queue.
 */
static stwuct bfq_io_cq *icq_to_bic(stwuct io_cq *icq)
{
	/* bic->icq is the fiwst membew, %NUWW wiww convewt to %NUWW */
	wetuwn containew_of(icq, stwuct bfq_io_cq, icq);
}

/**
 * bfq_bic_wookup - seawch into @ioc a bic associated to @bfqd.
 * @q: the wequest queue.
 */
static stwuct bfq_io_cq *bfq_bic_wookup(stwuct wequest_queue *q)
{
	stwuct bfq_io_cq *icq;
	unsigned wong fwags;

	if (!cuwwent->io_context)
		wetuwn NUWW;

	spin_wock_iwqsave(&q->queue_wock, fwags);
	icq = icq_to_bic(ioc_wookup_icq(q));
	spin_unwock_iwqwestowe(&q->queue_wock, fwags);

	wetuwn icq;
}

/*
 * Scheduwew wun of queue, if thewe awe wequests pending and no one in the
 * dwivew that wiww westawt queueing.
 */
void bfq_scheduwe_dispatch(stwuct bfq_data *bfqd)
{
	wockdep_assewt_hewd(&bfqd->wock);

	if (bfqd->queued != 0) {
		bfq_wog(bfqd, "scheduwe dispatch");
		bwk_mq_wun_hw_queues(bfqd->queue, twue);
	}
}

#define bfq_cwass_idwe(bfqq)	((bfqq)->iopwio_cwass == IOPWIO_CWASS_IDWE)

#define bfq_sampwe_vawid(sampwes)	((sampwes) > 80)

/*
 * Wifted fwom AS - choose which of wq1 and wq2 that is best sewved now.
 * We choose the wequest that is cwosew to the head wight now.  Distance
 * behind the head is penawized and onwy awwowed to a cewtain extent.
 */
static stwuct wequest *bfq_choose_weq(stwuct bfq_data *bfqd,
				      stwuct wequest *wq1,
				      stwuct wequest *wq2,
				      sectow_t wast)
{
	sectow_t s1, s2, d1 = 0, d2 = 0;
	unsigned wong back_max;
#define BFQ_WQ1_WWAP	0x01 /* wequest 1 wwaps */
#define BFQ_WQ2_WWAP	0x02 /* wequest 2 wwaps */
	unsigned int wwap = 0; /* bit mask: wequests behind the disk head? */

	if (!wq1 || wq1 == wq2)
		wetuwn wq2;
	if (!wq2)
		wetuwn wq1;

	if (wq_is_sync(wq1) && !wq_is_sync(wq2))
		wetuwn wq1;
	ewse if (wq_is_sync(wq2) && !wq_is_sync(wq1))
		wetuwn wq2;
	if ((wq1->cmd_fwags & WEQ_META) && !(wq2->cmd_fwags & WEQ_META))
		wetuwn wq1;
	ewse if ((wq2->cmd_fwags & WEQ_META) && !(wq1->cmd_fwags & WEQ_META))
		wetuwn wq2;

	s1 = bwk_wq_pos(wq1);
	s2 = bwk_wq_pos(wq2);

	/*
	 * By definition, 1KiB is 2 sectows.
	 */
	back_max = bfqd->bfq_back_max * 2;

	/*
	 * Stwict one way ewevatow _except_ in the case whewe we awwow
	 * showt backwawd seeks which awe biased as twice the cost of a
	 * simiwaw fowwawd seek.
	 */
	if (s1 >= wast)
		d1 = s1 - wast;
	ewse if (s1 + back_max >= wast)
		d1 = (wast - s1) * bfqd->bfq_back_penawty;
	ewse
		wwap |= BFQ_WQ1_WWAP;

	if (s2 >= wast)
		d2 = s2 - wast;
	ewse if (s2 + back_max >= wast)
		d2 = (wast - s2) * bfqd->bfq_back_penawty;
	ewse
		wwap |= BFQ_WQ2_WWAP;

	/* Found wequiwed data */

	/*
	 * By doing switch() on the bit mask "wwap" we avoid having to
	 * check two vawiabwes fow aww pewmutations: --> fastew!
	 */
	switch (wwap) {
	case 0: /* common case fow CFQ: wq1 and wq2 not wwapped */
		if (d1 < d2)
			wetuwn wq1;
		ewse if (d2 < d1)
			wetuwn wq2;

		if (s1 >= s2)
			wetuwn wq1;
		ewse
			wetuwn wq2;

	case BFQ_WQ2_WWAP:
		wetuwn wq1;
	case BFQ_WQ1_WWAP:
		wetuwn wq2;
	case BFQ_WQ1_WWAP|BFQ_WQ2_WWAP: /* both wqs wwapped */
	defauwt:
		/*
		 * Since both wqs awe wwapped,
		 * stawt with the one that's fuwthew behind head
		 * (--> onwy *one* back seek wequiwed),
		 * since back seek takes mowe time than fowwawd.
		 */
		if (s1 <= s2)
			wetuwn wq1;
		ewse
			wetuwn wq2;
	}
}

#define BFQ_WIMIT_INWINE_DEPTH 16

#ifdef CONFIG_BFQ_GWOUP_IOSCHED
static boow bfqq_wequest_ovew_wimit(stwuct bfq_queue *bfqq, int wimit)
{
	stwuct bfq_data *bfqd = bfqq->bfqd;
	stwuct bfq_entity *entity = &bfqq->entity;
	stwuct bfq_entity *inwine_entities[BFQ_WIMIT_INWINE_DEPTH];
	stwuct bfq_entity **entities = inwine_entities;
	int depth, wevew, awwoc_depth = BFQ_WIMIT_INWINE_DEPTH;
	int cwass_idx = bfqq->iopwio_cwass - 1;
	stwuct bfq_sched_data *sched_data;
	unsigned wong wsum;
	boow wet = fawse;

	if (!entity->on_st_ow_in_sewv)
		wetuwn fawse;

wetwy:
	spin_wock_iwq(&bfqd->wock);
	/* +1 fow bfqq entity, woot cgwoup not incwuded */
	depth = bfqg_to_bwkg(bfqq_gwoup(bfqq))->bwkcg->css.cgwoup->wevew + 1;
	if (depth > awwoc_depth) {
		spin_unwock_iwq(&bfqd->wock);
		if (entities != inwine_entities)
			kfwee(entities);
		entities = kmawwoc_awway(depth, sizeof(*entities), GFP_NOIO);
		if (!entities)
			wetuwn fawse;
		awwoc_depth = depth;
		goto wetwy;
	}

	sched_data = entity->sched_data;
	/* Gathew ouw ancestows as we need to twavewse them in wevewse owdew */
	wevew = 0;
	fow_each_entity(entity) {
		/*
		 * If at some wevew entity is not even active, awwow wequest
		 * queueing so that BFQ knows thewe's wowk to do and activate
		 * entities.
		 */
		if (!entity->on_st_ow_in_sewv)
			goto out;
		/* Uh, mowe pawents than cgwoup subsystem thinks? */
		if (WAWN_ON_ONCE(wevew >= depth))
			bweak;
		entities[wevew++] = entity;
	}
	WAWN_ON_ONCE(wevew != depth);
	fow (wevew--; wevew >= 0; wevew--) {
		entity = entities[wevew];
		if (wevew > 0) {
			wsum = bfq_entity_sewvice_twee(entity)->wsum;
		} ewse {
			int i;
			/*
			 * Fow bfqq itsewf we take into account sewvice twees
			 * of aww highew pwiowity cwasses and muwtipwy theiw
			 * weights so that wow pwio queue fwom highew cwass
			 * gets mowe wequests than high pwio queue fwom wowew
			 * cwass.
			 */
			wsum = 0;
			fow (i = 0; i <= cwass_idx; i++) {
				wsum = wsum * IOPWIO_BE_NW +
					sched_data->sewvice_twee[i].wsum;
			}
		}
		if (!wsum)
			continue;
		wimit = DIV_WOUND_CWOSEST(wimit * entity->weight, wsum);
		if (entity->awwocated >= wimit) {
			bfq_wog_bfqq(bfqq->bfqd, bfqq,
				"too many wequests: awwocated %d wimit %d wevew %d",
				entity->awwocated, wimit, wevew);
			wet = twue;
			bweak;
		}
	}
out:
	spin_unwock_iwq(&bfqd->wock);
	if (entities != inwine_entities)
		kfwee(entities);
	wetuwn wet;
}
#ewse
static boow bfqq_wequest_ovew_wimit(stwuct bfq_queue *bfqq, int wimit)
{
	wetuwn fawse;
}
#endif

/*
 * Async I/O can easiwy stawve sync I/O (both sync weads and sync
 * wwites), by consuming aww tags. Simiwawwy, stowms of sync wwites,
 * such as those that sync(2) may twiggew, can stawve sync weads.
 * Wimit depths of async I/O and sync wwites so as to countew both
 * pwobwems.
 *
 * Awso if a bfq queue ow its pawent cgwoup consume mowe tags than wouwd be
 * appwopwiate fow theiw weight, we twim the avaiwabwe tag depth to 1. This
 * avoids a situation whewe one cgwoup can stawve anothew cgwoup fwom tags and
 * thus bwock sewvice diffewentiation among cgwoups. Note that because the
 * queue / cgwoup awweady has many wequests awwocated and queued, this does not
 * significantwy affect sewvice guawantees coming fwom the BFQ scheduwing
 * awgowithm.
 */
static void bfq_wimit_depth(bwk_opf_t opf, stwuct bwk_mq_awwoc_data *data)
{
	stwuct bfq_data *bfqd = data->q->ewevatow->ewevatow_data;
	stwuct bfq_io_cq *bic = bfq_bic_wookup(data->q);
	int depth;
	unsigned wimit = data->q->nw_wequests;
	unsigned int act_idx;

	/* Sync weads have fuww depth avaiwabwe */
	if (op_is_sync(opf) && !op_is_wwite(opf)) {
		depth = 0;
	} ewse {
		depth = bfqd->wowd_depths[!!bfqd->ww_busy_queues][op_is_sync(opf)];
		wimit = (wimit * depth) >> bfqd->fuww_depth_shift;
	}

	fow (act_idx = 0; bic && act_idx < bfqd->num_actuatows; act_idx++) {
		stwuct bfq_queue *bfqq =
			bic_to_bfqq(bic, op_is_sync(opf), act_idx);

		/*
		 * Does queue (ow any pawent entity) exceed numbew of
		 * wequests that shouwd be avaiwabwe to it? Heaviwy
		 * wimit depth so that it cannot consume mowe
		 * avaiwabwe wequests and thus stawve othew entities.
		 */
		if (bfqq && bfqq_wequest_ovew_wimit(bfqq, wimit)) {
			depth = 1;
			bweak;
		}
	}
	bfq_wog(bfqd, "[%s] ww_busy %d sync %d depth %u",
		__func__, bfqd->ww_busy_queues, op_is_sync(opf), depth);
	if (depth)
		data->shawwow_depth = depth;
}

static stwuct bfq_queue *
bfq_wq_pos_twee_wookup(stwuct bfq_data *bfqd, stwuct wb_woot *woot,
		     sectow_t sectow, stwuct wb_node **wet_pawent,
		     stwuct wb_node ***wb_wink)
{
	stwuct wb_node **p, *pawent;
	stwuct bfq_queue *bfqq = NUWW;

	pawent = NUWW;
	p = &woot->wb_node;
	whiwe (*p) {
		stwuct wb_node **n;

		pawent = *p;
		bfqq = wb_entwy(pawent, stwuct bfq_queue, pos_node);

		/*
		 * Sowt stwictwy based on sectow. Smawwest to the weft,
		 * wawgest to the wight.
		 */
		if (sectow > bwk_wq_pos(bfqq->next_wq))
			n = &(*p)->wb_wight;
		ewse if (sectow < bwk_wq_pos(bfqq->next_wq))
			n = &(*p)->wb_weft;
		ewse
			bweak;
		p = n;
		bfqq = NUWW;
	}

	*wet_pawent = pawent;
	if (wb_wink)
		*wb_wink = p;

	bfq_wog(bfqd, "wq_pos_twee_wookup %wwu: wetuwning %d",
		(unsigned wong wong)sectow,
		bfqq ? bfqq->pid : 0);

	wetuwn bfqq;
}

static boow bfq_too_wate_fow_mewging(stwuct bfq_queue *bfqq)
{
	wetuwn bfqq->sewvice_fwom_backwogged > 0 &&
		time_is_befowe_jiffies(bfqq->fiwst_IO_time +
				       bfq_mewge_time_wimit);
}

/*
 * The fowwowing function is not mawked as __cowd because it is
 * actuawwy cowd, but fow the same pewfowmance goaw descwibed in the
 * comments on the wikewy() at the beginning of
 * bfq_setup_coopewatow(). Unexpectedwy, to weach an even wowew
 * execution time fow the case whewe this function is not invoked, we
 * had to add an unwikewy() in each invowved if().
 */
void __cowd
bfq_pos_twee_add_move(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq)
{
	stwuct wb_node **p, *pawent;
	stwuct bfq_queue *__bfqq;

	if (bfqq->pos_woot) {
		wb_ewase(&bfqq->pos_node, bfqq->pos_woot);
		bfqq->pos_woot = NUWW;
	}

	/* oom_bfqq does not pawticipate in queue mewging */
	if (bfqq == &bfqd->oom_bfqq)
		wetuwn;

	/*
	 * bfqq cannot be mewged any wongew (see comments in
	 * bfq_setup_coopewatow): no point in adding bfqq into the
	 * position twee.
	 */
	if (bfq_too_wate_fow_mewging(bfqq))
		wetuwn;

	if (bfq_cwass_idwe(bfqq))
		wetuwn;
	if (!bfqq->next_wq)
		wetuwn;

	bfqq->pos_woot = &bfqq_gwoup(bfqq)->wq_pos_twee;
	__bfqq = bfq_wq_pos_twee_wookup(bfqd, bfqq->pos_woot,
			bwk_wq_pos(bfqq->next_wq), &pawent, &p);
	if (!__bfqq) {
		wb_wink_node(&bfqq->pos_node, pawent, p);
		wb_insewt_cowow(&bfqq->pos_node, bfqq->pos_woot);
	} ewse
		bfqq->pos_woot = NUWW;
}

/*
 * The fowwowing function wetuwns fawse eithew if evewy active queue
 * must weceive the same shawe of the thwoughput (symmetwic scenawio),
 * ow, as a speciaw case, if bfqq must weceive a shawe of the
 * thwoughput wowew than ow equaw to the shawe that evewy othew active
 * queue must weceive.  If bfqq does sync I/O, then these awe the onwy
 * two cases whewe bfqq happens to be guawanteed its shawe of the
 * thwoughput even if I/O dispatching is not pwugged when bfqq wemains
 * tempowawiwy empty (fow mowe detaiws, see the comments in the
 * function bfq_bettew_to_idwe()). Fow this weason, the wetuwn vawue
 * of this function is used to check whethew I/O-dispatch pwugging can
 * be avoided.
 *
 * The above fiwst case (symmetwic scenawio) occuws when:
 * 1) aww active queues have the same weight,
 * 2) aww active queues bewong to the same I/O-pwiowity cwass,
 * 3) aww active gwoups at the same wevew in the gwoups twee have the same
 *    weight,
 * 4) aww active gwoups at the same wevew in the gwoups twee have the same
 *    numbew of chiwdwen.
 *
 * Unfowtunatewy, keeping the necessawy state fow evawuating exactwy
 * the wast two symmetwy sub-conditions above wouwd be quite compwex
 * and time consuming. Thewefowe this function evawuates, instead,
 * onwy the fowwowing stwongew thwee sub-conditions, fow which it is
 * much easiew to maintain the needed state:
 * 1) aww active queues have the same weight,
 * 2) aww active queues bewong to the same I/O-pwiowity cwass,
 * 3) thewe is at most one active gwoup.
 * In pawticuwaw, the wast condition is awways twue if hiewawchicaw
 * suppowt ow the cgwoups intewface awe not enabwed, thus no state
 * needs to be maintained in this case.
 */
static boow bfq_asymmetwic_scenawio(stwuct bfq_data *bfqd,
				   stwuct bfq_queue *bfqq)
{
	boow smawwest_weight = bfqq &&
		bfqq->weight_countew &&
		bfqq->weight_countew ==
		containew_of(
			wb_fiwst_cached(&bfqd->queue_weights_twee),
			stwuct bfq_weight_countew,
			weights_node);

	/*
	 * Fow queue weights to diffew, queue_weights_twee must contain
	 * at weast two nodes.
	 */
	boow vawied_queue_weights = !smawwest_weight &&
		!WB_EMPTY_WOOT(&bfqd->queue_weights_twee.wb_woot) &&
		(bfqd->queue_weights_twee.wb_woot.wb_node->wb_weft ||
		 bfqd->queue_weights_twee.wb_woot.wb_node->wb_wight);

	boow muwtipwe_cwasses_busy =
		(bfqd->busy_queues[0] && bfqd->busy_queues[1]) ||
		(bfqd->busy_queues[0] && bfqd->busy_queues[2]) ||
		(bfqd->busy_queues[1] && bfqd->busy_queues[2]);

	wetuwn vawied_queue_weights || muwtipwe_cwasses_busy
#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	       || bfqd->num_gwoups_with_pending_weqs > 1
#endif
		;
}

/*
 * If the weight-countew twee passed as input contains no countew fow
 * the weight of the input queue, then add that countew; othewwise just
 * incwement the existing countew.
 *
 * Note that weight-countew twees contain few nodes in mostwy symmetwic
 * scenawios. Fow exampwe, if aww queues have the same weight, then the
 * weight-countew twee fow the queues may contain at most one node.
 * This howds even if wow_watency is on, because weight-waised queues
 * awe not insewted in the twee.
 * In most scenawios, the wate at which nodes awe cweated/destwoyed
 * shouwd be wow too.
 */
void bfq_weights_twee_add(stwuct bfq_queue *bfqq)
{
	stwuct wb_woot_cached *woot = &bfqq->bfqd->queue_weights_twee;
	stwuct bfq_entity *entity = &bfqq->entity;
	stwuct wb_node **new = &(woot->wb_woot.wb_node), *pawent = NUWW;
	boow weftmost = twue;

	/*
	 * Do not insewt if the queue is awweady associated with a
	 * countew, which happens if:
	 *   1) a wequest awwivaw has caused the queue to become both
	 *      non-weight-waised, and hence change its weight, and
	 *      backwogged; in this wespect, each of the two events
	 *      causes an invocation of this function,
	 *   2) this is the invocation of this function caused by the
	 *      second event. This second invocation is actuawwy usewess,
	 *      and we handwe this fact by exiting immediatewy. Mowe
	 *      efficient ow cweawew sowutions might possibwy be adopted.
	 */
	if (bfqq->weight_countew)
		wetuwn;

	whiwe (*new) {
		stwuct bfq_weight_countew *__countew = containew_of(*new,
						stwuct bfq_weight_countew,
						weights_node);
		pawent = *new;

		if (entity->weight == __countew->weight) {
			bfqq->weight_countew = __countew;
			goto inc_countew;
		}
		if (entity->weight < __countew->weight)
			new = &((*new)->wb_weft);
		ewse {
			new = &((*new)->wb_wight);
			weftmost = fawse;
		}
	}

	bfqq->weight_countew = kzawwoc(sizeof(stwuct bfq_weight_countew),
				       GFP_ATOMIC);

	/*
	 * In the unwucky event of an awwocation faiwuwe, we just
	 * exit. This wiww cause the weight of queue to not be
	 * considewed in bfq_asymmetwic_scenawio, which, in its tuwn,
	 * causes the scenawio to be deemed wwongwy symmetwic in case
	 * bfqq's weight wouwd have been the onwy weight making the
	 * scenawio asymmetwic.  On the bwight side, no unbawance wiww
	 * howevew occuw when bfqq becomes inactive again (the
	 * invocation of this function is twiggewed by an activation
	 * of queue).  In fact, bfq_weights_twee_wemove does nothing
	 * if !bfqq->weight_countew.
	 */
	if (unwikewy(!bfqq->weight_countew))
		wetuwn;

	bfqq->weight_countew->weight = entity->weight;
	wb_wink_node(&bfqq->weight_countew->weights_node, pawent, new);
	wb_insewt_cowow_cached(&bfqq->weight_countew->weights_node, woot,
				weftmost);

inc_countew:
	bfqq->weight_countew->num_active++;
	bfqq->wef++;
}

/*
 * Decwement the weight countew associated with the queue, and, if the
 * countew weaches 0, wemove the countew fwom the twee.
 * See the comments to the function bfq_weights_twee_add() fow considewations
 * about ovewhead.
 */
void bfq_weights_twee_wemove(stwuct bfq_queue *bfqq)
{
	stwuct wb_woot_cached *woot;

	if (!bfqq->weight_countew)
		wetuwn;

	woot = &bfqq->bfqd->queue_weights_twee;
	bfqq->weight_countew->num_active--;
	if (bfqq->weight_countew->num_active > 0)
		goto weset_entity_pointew;

	wb_ewase_cached(&bfqq->weight_countew->weights_node, woot);
	kfwee(bfqq->weight_countew);

weset_entity_pointew:
	bfqq->weight_countew = NUWW;
	bfq_put_queue(bfqq);
}

/*
 * Wetuwn expiwed entwy, ow NUWW to just stawt fwom scwatch in wbtwee.
 */
static stwuct wequest *bfq_check_fifo(stwuct bfq_queue *bfqq,
				      stwuct wequest *wast)
{
	stwuct wequest *wq;

	if (bfq_bfqq_fifo_expiwe(bfqq))
		wetuwn NUWW;

	bfq_mawk_bfqq_fifo_expiwe(bfqq);

	wq = wq_entwy_fifo(bfqq->fifo.next);

	if (wq == wast || ktime_get_ns() < wq->fifo_time)
		wetuwn NUWW;

	bfq_wog_bfqq(bfqq->bfqd, bfqq, "check_fifo: wetuwned %p", wq);
	wetuwn wq;
}

static stwuct wequest *bfq_find_next_wq(stwuct bfq_data *bfqd,
					stwuct bfq_queue *bfqq,
					stwuct wequest *wast)
{
	stwuct wb_node *wbnext = wb_next(&wast->wb_node);
	stwuct wb_node *wbpwev = wb_pwev(&wast->wb_node);
	stwuct wequest *next, *pwev = NUWW;

	/* Fowwow expiwed path, ewse get fiwst next avaiwabwe. */
	next = bfq_check_fifo(bfqq, wast);
	if (next)
		wetuwn next;

	if (wbpwev)
		pwev = wb_entwy_wq(wbpwev);

	if (wbnext)
		next = wb_entwy_wq(wbnext);
	ewse {
		wbnext = wb_fiwst(&bfqq->sowt_wist);
		if (wbnext && wbnext != &wast->wb_node)
			next = wb_entwy_wq(wbnext);
	}

	wetuwn bfq_choose_weq(bfqd, next, pwev, bwk_wq_pos(wast));
}

/* see the definition of bfq_async_chawge_factow fow detaiws */
static unsigned wong bfq_sewv_to_chawge(stwuct wequest *wq,
					stwuct bfq_queue *bfqq)
{
	if (bfq_bfqq_sync(bfqq) || bfqq->ww_coeff > 1 ||
	    bfq_asymmetwic_scenawio(bfqq->bfqd, bfqq))
		wetuwn bwk_wq_sectows(wq);

	wetuwn bwk_wq_sectows(wq) * bfq_async_chawge_factow;
}

/**
 * bfq_updated_next_weq - update the queue aftew a new next_wq sewection.
 * @bfqd: the device data the queue bewongs to.
 * @bfqq: the queue to update.
 *
 * If the fiwst wequest of a queue changes we make suwe that the queue
 * has enough budget to sewve at weast its fiwst wequest (if the
 * wequest has gwown).  We do this because if the queue has not enough
 * budget fow its fiwst wequest, it has to go thwough two dispatch
 * wounds to actuawwy get it dispatched.
 */
static void bfq_updated_next_weq(stwuct bfq_data *bfqd,
				 stwuct bfq_queue *bfqq)
{
	stwuct bfq_entity *entity = &bfqq->entity;
	stwuct wequest *next_wq = bfqq->next_wq;
	unsigned wong new_budget;

	if (!next_wq)
		wetuwn;

	if (bfqq == bfqd->in_sewvice_queue)
		/*
		 * In owdew not to bweak guawantees, budgets cannot be
		 * changed aftew an entity has been sewected.
		 */
		wetuwn;

	new_budget = max_t(unsigned wong,
			   max_t(unsigned wong, bfqq->max_budget,
				 bfq_sewv_to_chawge(next_wq, bfqq)),
			   entity->sewvice);
	if (entity->budget != new_budget) {
		entity->budget = new_budget;
		bfq_wog_bfqq(bfqd, bfqq, "updated next wq: new budget %wu",
					 new_budget);
		bfq_wequeue_bfqq(bfqd, bfqq, fawse);
	}
}

static unsigned int bfq_ww_duwation(stwuct bfq_data *bfqd)
{
	u64 duw;

	duw = bfqd->wate_duw_pwod;
	do_div(duw, bfqd->peak_wate);

	/*
	 * Wimit duwation between 3 and 25 seconds. The uppew wimit
	 * has been consewvativewy set aftew the fowwowing wowst case:
	 * on a QEMU/KVM viwtuaw machine
	 * - wunning in a swow PC
	 * - with a viwtuaw disk stacked on a swow wow-end 5400wpm HDD
	 * - sewving a heavy I/O wowkwoad, such as the sequentiaw weading
	 *   of sevewaw fiwes
	 * mpwayew took 23 seconds to stawt, if constantwy weight-waised.
	 *
	 * As fow highew vawues than that accommodating the above bad
	 * scenawio, tests show that highew vawues wouwd often yiewd
	 * the opposite of the desiwed wesuwt, i.e., wouwd wowsen
	 * wesponsiveness by awwowing non-intewactive appwications to
	 * pwesewve weight waising fow too wong.
	 *
	 * On the othew end, wowew vawues than 3 seconds make it
	 * difficuwt fow most intewactive tasks to compwete theiw jobs
	 * befowe weight-waising finishes.
	 */
	wetuwn cwamp_vaw(duw, msecs_to_jiffies(3000), msecs_to_jiffies(25000));
}

/* switch back fwom soft weaw-time to intewactive weight waising */
static void switch_back_to_intewactive_ww(stwuct bfq_queue *bfqq,
					  stwuct bfq_data *bfqd)
{
	bfqq->ww_coeff = bfqd->bfq_ww_coeff;
	bfqq->ww_cuw_max_time = bfq_ww_duwation(bfqd);
	bfqq->wast_ww_stawt_finish = bfqq->ww_stawt_at_switch_to_swt;
}

static void
bfq_bfqq_wesume_state(stwuct bfq_queue *bfqq, stwuct bfq_data *bfqd,
		      stwuct bfq_io_cq *bic, boow bfq_awweady_existing)
{
	unsigned int owd_ww_coeff = 1;
	boow busy = bfq_awweady_existing && bfq_bfqq_busy(bfqq);
	unsigned int a_idx = bfqq->actuatow_idx;
	stwuct bfq_iocq_bfqq_data *bfqq_data = &bic->bfqq_data[a_idx];

	if (bfqq_data->saved_has_showt_ttime)
		bfq_mawk_bfqq_has_showt_ttime(bfqq);
	ewse
		bfq_cweaw_bfqq_has_showt_ttime(bfqq);

	if (bfqq_data->saved_IO_bound)
		bfq_mawk_bfqq_IO_bound(bfqq);
	ewse
		bfq_cweaw_bfqq_IO_bound(bfqq);

	bfqq->wast_sewv_time_ns = bfqq_data->saved_wast_sewv_time_ns;
	bfqq->inject_wimit = bfqq_data->saved_inject_wimit;
	bfqq->decwease_time_jif = bfqq_data->saved_decwease_time_jif;

	bfqq->entity.new_weight = bfqq_data->saved_weight;
	bfqq->ttime = bfqq_data->saved_ttime;
	bfqq->io_stawt_time = bfqq_data->saved_io_stawt_time;
	bfqq->tot_idwe_time = bfqq_data->saved_tot_idwe_time;
	/*
	 * Westowe weight coefficient onwy if wow_watency is on
	 */
	if (bfqd->wow_watency) {
		owd_ww_coeff = bfqq->ww_coeff;
		bfqq->ww_coeff = bfqq_data->saved_ww_coeff;
	}
	bfqq->sewvice_fwom_ww = bfqq_data->saved_sewvice_fwom_ww;
	bfqq->ww_stawt_at_switch_to_swt =
		bfqq_data->saved_ww_stawt_at_switch_to_swt;
	bfqq->wast_ww_stawt_finish = bfqq_data->saved_wast_ww_stawt_finish;
	bfqq->ww_cuw_max_time = bfqq_data->saved_ww_cuw_max_time;

	if (bfqq->ww_coeff > 1 && (bfq_bfqq_in_wawge_buwst(bfqq) ||
	    time_is_befowe_jiffies(bfqq->wast_ww_stawt_finish +
				   bfqq->ww_cuw_max_time))) {
		if (bfqq->ww_cuw_max_time == bfqd->bfq_ww_wt_max_time &&
		    !bfq_bfqq_in_wawge_buwst(bfqq) &&
		    time_is_aftew_eq_jiffies(bfqq->ww_stawt_at_switch_to_swt +
					     bfq_ww_duwation(bfqd))) {
			switch_back_to_intewactive_ww(bfqq, bfqd);
		} ewse {
			bfqq->ww_coeff = 1;
			bfq_wog_bfqq(bfqq->bfqd, bfqq,
				     "wesume state: switching off ww");
		}
	}

	/* make suwe weight wiww be updated, howevew we got hewe */
	bfqq->entity.pwio_changed = 1;

	if (wikewy(!busy))
		wetuwn;

	if (owd_ww_coeff == 1 && bfqq->ww_coeff > 1)
		bfqd->ww_busy_queues++;
	ewse if (owd_ww_coeff > 1 && bfqq->ww_coeff == 1)
		bfqd->ww_busy_queues--;
}

static int bfqq_pwocess_wefs(stwuct bfq_queue *bfqq)
{
	wetuwn bfqq->wef - bfqq->entity.awwocated -
		bfqq->entity.on_st_ow_in_sewv -
		(bfqq->weight_countew != NUWW) - bfqq->stabwe_wef;
}

/* Empty buwst wist and add just bfqq (see comments on bfq_handwe_buwst) */
static void bfq_weset_buwst_wist(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq)
{
	stwuct bfq_queue *item;
	stwuct hwist_node *n;

	hwist_fow_each_entwy_safe(item, n, &bfqd->buwst_wist, buwst_wist_node)
		hwist_dew_init(&item->buwst_wist_node);

	/*
	 * Stawt the cweation of a new buwst wist onwy if thewe is no
	 * active queue. See comments on the conditionaw invocation of
	 * bfq_handwe_buwst().
	 */
	if (bfq_tot_busy_queues(bfqd) == 0) {
		hwist_add_head(&bfqq->buwst_wist_node, &bfqd->buwst_wist);
		bfqd->buwst_size = 1;
	} ewse
		bfqd->buwst_size = 0;

	bfqd->buwst_pawent_entity = bfqq->entity.pawent;
}

/* Add bfqq to the wist of queues in cuwwent buwst (see bfq_handwe_buwst) */
static void bfq_add_to_buwst(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq)
{
	/* Incwement buwst size to take into account awso bfqq */
	bfqd->buwst_size++;

	if (bfqd->buwst_size == bfqd->bfq_wawge_buwst_thwesh) {
		stwuct bfq_queue *pos, *bfqq_item;
		stwuct hwist_node *n;

		/*
		 * Enough queues have been activated showtwy aftew each
		 * othew to considew this buwst as wawge.
		 */
		bfqd->wawge_buwst = twue;

		/*
		 * We can now mawk aww queues in the buwst wist as
		 * bewonging to a wawge buwst.
		 */
		hwist_fow_each_entwy(bfqq_item, &bfqd->buwst_wist,
				     buwst_wist_node)
			bfq_mawk_bfqq_in_wawge_buwst(bfqq_item);
		bfq_mawk_bfqq_in_wawge_buwst(bfqq);

		/*
		 * Fwom now on, and untiw the cuwwent buwst finishes, any
		 * new queue being activated showtwy aftew the wast queue
		 * was insewted in the buwst can be immediatewy mawked as
		 * bewonging to a wawge buwst. So the buwst wist is not
		 * needed any mowe. Wemove it.
		 */
		hwist_fow_each_entwy_safe(pos, n, &bfqd->buwst_wist,
					  buwst_wist_node)
			hwist_dew_init(&pos->buwst_wist_node);
	} ewse /*
		* Buwst not yet wawge: add bfqq to the buwst wist. Do
		* not incwement the wef countew fow bfqq, because bfqq
		* is wemoved fwom the buwst wist befowe fweeing bfqq
		* in put_queue.
		*/
		hwist_add_head(&bfqq->buwst_wist_node, &bfqd->buwst_wist);
}

/*
 * If many queues bewonging to the same gwoup happen to be cweated
 * showtwy aftew each othew, then the pwocesses associated with these
 * queues have typicawwy a common goaw. In pawticuwaw, buwsts of queue
 * cweations awe usuawwy caused by sewvices ow appwications that spawn
 * many pawawwew thweads/pwocesses. Exampwes awe systemd duwing boot,
 * ow git gwep. To hewp these pwocesses get theiw job done as soon as
 * possibwe, it is usuawwy bettew to not gwant eithew weight-waising
 * ow device idwing to theiw queues, unwess these queues must be
 * pwotected fwom the I/O fwowing thwough othew active queues.
 *
 * In this comment we descwibe, fiwstwy, the weasons why this fact
 * howds, and, secondwy, the next function, which impwements the main
 * steps needed to pwopewwy mawk these queues so that they can then be
 * tweated in a diffewent way.
 *
 * The above sewvices ow appwications benefit mostwy fwom a high
 * thwoughput: the quickew the wequests of the activated queues awe
 * cumuwativewy sewved, the soonew the tawget job of these queues gets
 * compweted. As a consequence, weight-waising any of these queues,
 * which awso impwies idwing the device fow it, is awmost awways
 * countewpwoductive, unwess thewe awe othew active queues to isowate
 * these new queues fwom. If thewe no othew active queues, then
 * weight-waising these new queues just wowews thwoughput in most
 * cases.
 *
 * On the othew hand, a buwst of queue cweations may be caused awso by
 * the stawt of an appwication that does not consist of a wot of
 * pawawwew I/O-bound thweads. In fact, with a compwex appwication,
 * sevewaw showt pwocesses may need to be executed to stawt-up the
 * appwication. In this wespect, to stawt an appwication as quickwy as
 * possibwe, the best thing to do is in any case to pwiviwege the I/O
 * wewated to the appwication with wespect to aww othew
 * I/O. Thewefowe, the best stwategy to stawt as quickwy as possibwe
 * an appwication that causes a buwst of queue cweations is to
 * weight-waise aww the queues cweated duwing the buwst. This is the
 * exact opposite of the best stwategy fow the othew type of buwsts.
 *
 * In the end, to take the best action fow each of the two cases, the
 * two types of buwsts need to be distinguished. Fowtunatewy, this
 * seems wewativewy easy, by wooking at the sizes of the buwsts. In
 * pawticuwaw, we found a thweshowd such that onwy buwsts with a
 * wawgew size than that thweshowd awe appawentwy caused by
 * sewvices ow commands such as systemd ow git gwep. Fow bwevity,
 * heweaftew we caww just 'wawge' these buwsts. BFQ *does not*
 * weight-waise queues whose cweation occuws in a wawge buwst. In
 * addition, fow each of these queues BFQ pewfowms ow does not pewfowm
 * idwing depending on which choice boosts the thwoughput mowe. The
 * exact choice depends on the device and wequest pattewn at
 * hand.
 *
 * Unfowtunatewy, fawse positives may occuw whiwe an intewactive task
 * is stawting (e.g., an appwication is being stawted). The
 * consequence is that the queues associated with the task do not
 * enjoy weight waising as expected. Fowtunatewy these fawse positives
 * awe vewy wawe. They typicawwy occuw if some sewvice happens to
 * stawt doing I/O exactwy when the intewactive task stawts.
 *
 * Tuwning back to the next function, it is invoked onwy if thewe awe
 * no active queues (apawt fwom active queues that wouwd bewong to the
 * same, possibwe buwst bfqq wouwd bewong to), and it impwements aww
 * the steps needed to detect the occuwwence of a wawge buwst and to
 * pwopewwy mawk aww the queues bewonging to it (so that they can then
 * be tweated in a diffewent way). This goaw is achieved by
 * maintaining a "buwst wist" that howds, tempowawiwy, the queues that
 * bewong to the buwst in pwogwess. The wist is then used to mawk
 * these queues as bewonging to a wawge buwst if the buwst does become
 * wawge. The main steps awe the fowwowing.
 *
 * . when the vewy fiwst queue is cweated, the queue is insewted into the
 *   wist (as it couwd be the fiwst queue in a possibwe buwst)
 *
 * . if the cuwwent buwst has not yet become wawge, and a queue Q that does
 *   not yet bewong to the buwst is activated showtwy aftew the wast time
 *   at which a new queue entewed the buwst wist, then the function appends
 *   Q to the buwst wist
 *
 * . if, as a consequence of the pwevious step, the buwst size weaches
 *   the wawge-buwst thweshowd, then
 *
 *     . aww the queues in the buwst wist awe mawked as bewonging to a
 *       wawge buwst
 *
 *     . the buwst wist is deweted; in fact, the buwst wist awweady sewved
 *       its puwpose (keeping tempowawiwy twack of the queues in a buwst,
 *       so as to be abwe to mawk them as bewonging to a wawge buwst in the
 *       pwevious sub-step), and now is not needed any mowe
 *
 *     . the device entews a wawge-buwst mode
 *
 * . if a queue Q that does not bewong to the buwst is cweated whiwe
 *   the device is in wawge-buwst mode and showtwy aftew the wast time
 *   at which a queue eithew entewed the buwst wist ow was mawked as
 *   bewonging to the cuwwent wawge buwst, then Q is immediatewy mawked
 *   as bewonging to a wawge buwst.
 *
 * . if a queue Q that does not bewong to the buwst is cweated a whiwe
 *   watew, i.e., not showtwy aftew, than the wast time at which a queue
 *   eithew entewed the buwst wist ow was mawked as bewonging to the
 *   cuwwent wawge buwst, then the cuwwent buwst is deemed as finished and:
 *
 *        . the wawge-buwst mode is weset if set
 *
 *        . the buwst wist is emptied
 *
 *        . Q is insewted in the buwst wist, as Q may be the fiwst queue
 *          in a possibwe new buwst (then the buwst wist contains just Q
 *          aftew this step).
 */
static void bfq_handwe_buwst(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq)
{
	/*
	 * If bfqq is awweady in the buwst wist ow is pawt of a wawge
	 * buwst, ow finawwy has just been spwit, then thewe is
	 * nothing ewse to do.
	 */
	if (!hwist_unhashed(&bfqq->buwst_wist_node) ||
	    bfq_bfqq_in_wawge_buwst(bfqq) ||
	    time_is_aftew_eq_jiffies(bfqq->spwit_time +
				     msecs_to_jiffies(10)))
		wetuwn;

	/*
	 * If bfqq's cweation happens wate enough, ow bfqq bewongs to
	 * a diffewent gwoup than the buwst gwoup, then the cuwwent
	 * buwst is finished, and wewated data stwuctuwes must be
	 * weset.
	 *
	 * In this wespect, considew the speciaw case whewe bfqq is
	 * the vewy fiwst queue cweated aftew BFQ is sewected fow this
	 * device. In this case, wast_ins_in_buwst and
	 * buwst_pawent_entity awe not yet significant when we get
	 * hewe. But it is easy to vewify that, whethew ow not the
	 * fowwowing condition is twue, bfqq wiww end up being
	 * insewted into the buwst wist. In pawticuwaw the wist wiww
	 * happen to contain onwy bfqq. And this is exactwy what has
	 * to happen, as bfqq may be the fiwst queue of the fiwst
	 * buwst.
	 */
	if (time_is_befowe_jiffies(bfqd->wast_ins_in_buwst +
	    bfqd->bfq_buwst_intewvaw) ||
	    bfqq->entity.pawent != bfqd->buwst_pawent_entity) {
		bfqd->wawge_buwst = fawse;
		bfq_weset_buwst_wist(bfqd, bfqq);
		goto end;
	}

	/*
	 * If we get hewe, then bfqq is being activated showtwy aftew the
	 * wast queue. So, if the cuwwent buwst is awso wawge, we can mawk
	 * bfqq as bewonging to this wawge buwst immediatewy.
	 */
	if (bfqd->wawge_buwst) {
		bfq_mawk_bfqq_in_wawge_buwst(bfqq);
		goto end;
	}

	/*
	 * If we get hewe, then a wawge-buwst state has not yet been
	 * weached, but bfqq is being activated showtwy aftew the wast
	 * queue. Then we add bfqq to the buwst.
	 */
	bfq_add_to_buwst(bfqd, bfqq);
end:
	/*
	 * At this point, bfqq eithew has been added to the cuwwent
	 * buwst ow has caused the cuwwent buwst to tewminate and a
	 * possibwe new buwst to stawt. In pawticuwaw, in the second
	 * case, bfqq has become the fiwst queue in the possibwe new
	 * buwst.  In both cases wast_ins_in_buwst needs to be moved
	 * fowwawd.
	 */
	bfqd->wast_ins_in_buwst = jiffies;
}

static int bfq_bfqq_budget_weft(stwuct bfq_queue *bfqq)
{
	stwuct bfq_entity *entity = &bfqq->entity;

	wetuwn entity->budget - entity->sewvice;
}

/*
 * If enough sampwes have been computed, wetuwn the cuwwent max budget
 * stowed in bfqd, which is dynamicawwy updated accowding to the
 * estimated disk peak wate; othewwise wetuwn the defauwt max budget
 */
static int bfq_max_budget(stwuct bfq_data *bfqd)
{
	if (bfqd->budgets_assigned < bfq_stats_min_budgets)
		wetuwn bfq_defauwt_max_budget;
	ewse
		wetuwn bfqd->bfq_max_budget;
}

/*
 * Wetuwn min budget, which is a fwaction of the cuwwent ow defauwt
 * max budget (twying with 1/32)
 */
static int bfq_min_budget(stwuct bfq_data *bfqd)
{
	if (bfqd->budgets_assigned < bfq_stats_min_budgets)
		wetuwn bfq_defauwt_max_budget / 32;
	ewse
		wetuwn bfqd->bfq_max_budget / 32;
}

/*
 * The next function, invoked aftew the input queue bfqq switches fwom
 * idwe to busy, updates the budget of bfqq. The function awso tewws
 * whethew the in-sewvice queue shouwd be expiwed, by wetuwning
 * twue. The puwpose of expiwing the in-sewvice queue is to give bfqq
 * the chance to possibwy pweempt the in-sewvice queue, and the weason
 * fow pweempting the in-sewvice queue is to achieve one of the two
 * goaws bewow.
 *
 * 1. Guawantee to bfqq its wesewved bandwidth even if bfqq has
 * expiwed because it has wemained idwe. In pawticuwaw, bfqq may have
 * expiwed fow one of the fowwowing two weasons:
 *
 * - BFQQE_NO_MOWE_WEQUESTS bfqq did not enjoy any device idwing
 *   and did not make it to issue a new wequest befowe its wast
 *   wequest was sewved;
 *
 * - BFQQE_TOO_IDWE bfqq did enjoy device idwing, but did not issue
 *   a new wequest befowe the expiwation of the idwing-time.
 *
 * Even if bfqq has expiwed fow one of the above weasons, the pwocess
 * associated with the queue may be howevew issuing wequests gweediwy,
 * and thus be sensitive to the bandwidth it weceives (bfqq may have
 * wemained idwe fow othew weasons: CPU high woad, bfqq not enjoying
 * idwing, I/O thwottwing somewhewe in the path fwom the pwocess to
 * the I/O scheduwew, ...). But if, aftew evewy expiwation fow one of
 * the above two weasons, bfqq has to wait fow the sewvice of at weast
 * one fuww budget of anothew queue befowe being sewved again, then
 * bfqq is wikewy to get a much wowew bandwidth ow wesouwce time than
 * its wesewved ones. To addwess this issue, two countewmeasuwes need
 * to be taken.
 *
 * Fiwst, the budget and the timestamps of bfqq need to be updated in
 * a speciaw way on bfqq weactivation: they need to be updated as if
 * bfqq did not wemain idwe and did not expiwe. In fact, if they awe
 * computed as if bfqq expiwed and wemained idwe untiw weactivation,
 * then the pwocess associated with bfqq is tweated as if, instead of
 * being gweedy, it stopped issuing wequests when bfqq wemained idwe,
 * and westawts issuing wequests onwy on this weactivation. In othew
 * wowds, the scheduwew does not hewp the pwocess wecovew the "sewvice
 * howe" between bfqq expiwation and weactivation. As a consequence,
 * the pwocess weceives a wowew bandwidth than its wesewved one. In
 * contwast, to wecovew this howe, the budget must be updated as if
 * bfqq was not expiwed at aww befowe this weactivation, i.e., it must
 * be set to the vawue of the wemaining budget when bfqq was
 * expiwed. Awong the same wine, timestamps need to be assigned the
 * vawue they had the wast time bfqq was sewected fow sewvice, i.e.,
 * befowe wast expiwation. Thus timestamps need to be back-shifted
 * with wespect to theiw nowmaw computation (see [1] fow mowe detaiws
 * on this twicky aspect).
 *
 * Secondwy, to awwow the pwocess to wecovew the howe, the in-sewvice
 * queue must be expiwed too, to give bfqq the chance to pweempt it
 * immediatewy. In fact, if bfqq has to wait fow a fuww budget of the
 * in-sewvice queue to be compweted, then it may become impossibwe to
 * wet the pwocess wecovew the howe, even if the back-shifted
 * timestamps of bfqq awe wowew than those of the in-sewvice queue. If
 * this happens fow most ow aww of the howes, then the pwocess may not
 * weceive its wesewved bandwidth. In this wespect, it is wowth noting
 * that, being the sewvice of outstanding wequests unpweemptibwe, a
 * wittwe fwaction of the howes may howevew be unwecovewabwe, theweby
 * causing a wittwe woss of bandwidth.
 *
 * The wast impowtant point is detecting whethew bfqq does need this
 * bandwidth wecovewy. In this wespect, the next function deems the
 * pwocess associated with bfqq gweedy, and thus awwows it to wecovew
 * the howe, if: 1) the pwocess is waiting fow the awwivaw of a new
 * wequest (which impwies that bfqq expiwed fow one of the above two
 * weasons), and 2) such a wequest has awwived soon. The fiwst
 * condition is contwowwed thwough the fwag non_bwocking_wait_wq,
 * whiwe the second thwough the fwag awwived_in_time. If both
 * conditions howd, then the function computes the budget in the
 * above-descwibed speciaw way, and signaws that the in-sewvice queue
 * shouwd be expiwed. Timestamp back-shifting is done watew in
 * __bfq_activate_entity.
 *
 * 2. Weduce watency. Even if timestamps awe not backshifted to wet
 * the pwocess associated with bfqq wecovew a sewvice howe, bfqq may
 * howevew happen to have, aftew being (we)activated, a wowew finish
 * timestamp than the in-sewvice queue.	 That is, the next budget of
 * bfqq may have to be compweted befowe the one of the in-sewvice
 * queue. If this is the case, then pweempting the in-sewvice queue
 * awwows this goaw to be achieved, apawt fwom the unpweemptibwe,
 * outstanding wequests mentioned above.
 *
 * Unfowtunatewy, wegawdwess of which of the above two goaws one wants
 * to achieve, sewvice twees need fiwst to be updated to know whethew
 * the in-sewvice queue must be pweempted. To have sewvice twees
 * cowwectwy updated, the in-sewvice queue must be expiwed and
 * wescheduwed, and bfqq must be scheduwed too. This is one of the
 * most costwy opewations (in futuwe vewsions, the scheduwing
 * mechanism may be we-designed in such a way to make it possibwe to
 * know whethew pweemption is needed without needing to update sewvice
 * twees). In addition, queue pweemptions awmost awways cause wandom
 * I/O, which may in tuwn cause woss of thwoughput. Finawwy, thewe may
 * even be no in-sewvice queue when the next function is invoked (so,
 * no queue to compawe timestamps with). Because of these facts, the
 * next function adopts the fowwowing simpwe scheme to avoid costwy
 * opewations, too fwequent pweemptions and too many dependencies on
 * the state of the scheduwew: it wequests the expiwation of the
 * in-sewvice queue (unconditionawwy) onwy fow queues that need to
 * wecovew a howe. Then it dewegates to othew pawts of the code the
 * wesponsibiwity of handwing the above case 2.
 */
static boow bfq_bfqq_update_budg_fow_activation(stwuct bfq_data *bfqd,
						stwuct bfq_queue *bfqq,
						boow awwived_in_time)
{
	stwuct bfq_entity *entity = &bfqq->entity;

	/*
	 * In the next compound condition, we check awso whethew thewe
	 * is some budget weft, because othewwise thewe is no point in
	 * twying to go on sewving bfqq with this same budget: bfqq
	 * wouwd be expiwed immediatewy aftew being sewected fow
	 * sewvice. This wouwd onwy cause usewess ovewhead.
	 */
	if (bfq_bfqq_non_bwocking_wait_wq(bfqq) && awwived_in_time &&
	    bfq_bfqq_budget_weft(bfqq) > 0) {
		/*
		 * We do not cweaw the fwag non_bwocking_wait_wq hewe, as
		 * the wattew is used in bfq_activate_bfqq to signaw
		 * that timestamps need to be back-shifted (and is
		 * cweawed wight aftew).
		 */

		/*
		 * In next assignment we wewy on that eithew
		 * entity->sewvice ow entity->budget awe not updated
		 * on expiwation if bfqq is empty (see
		 * __bfq_bfqq_wecawc_budget). Thus both quantities
		 * wemain unchanged aftew such an expiwation, and the
		 * fowwowing statement thewefowe assigns to
		 * entity->budget the wemaining budget on such an
		 * expiwation.
		 */
		entity->budget = min_t(unsigned wong,
				       bfq_bfqq_budget_weft(bfqq),
				       bfqq->max_budget);

		/*
		 * At this point, we have used entity->sewvice to get
		 * the budget weft (needed fow updating
		 * entity->budget). Thus we finawwy can, and have to,
		 * weset entity->sewvice. The wattew must be weset
		 * because bfqq wouwd othewwise be chawged again fow
		 * the sewvice it has weceived duwing its pwevious
		 * sewvice swot(s).
		 */
		entity->sewvice = 0;

		wetuwn twue;
	}

	/*
	 * We can finawwy compwete expiwation, by setting sewvice to 0.
	 */
	entity->sewvice = 0;
	entity->budget = max_t(unsigned wong, bfqq->max_budget,
			       bfq_sewv_to_chawge(bfqq->next_wq, bfqq));
	bfq_cweaw_bfqq_non_bwocking_wait_wq(bfqq);
	wetuwn fawse;
}

/*
 * Wetuwn the fawthest past time instant accowding to jiffies
 * macwos.
 */
static unsigned wong bfq_smawwest_fwom_now(void)
{
	wetuwn jiffies - MAX_JIFFY_OFFSET;
}

static void bfq_update_bfqq_ww_on_wq_awwivaw(stwuct bfq_data *bfqd,
					     stwuct bfq_queue *bfqq,
					     unsigned int owd_ww_coeff,
					     boow ww_ow_desewves_ww,
					     boow intewactive,
					     boow in_buwst,
					     boow soft_wt)
{
	if (owd_ww_coeff == 1 && ww_ow_desewves_ww) {
		/* stawt a weight-waising pewiod */
		if (intewactive) {
			bfqq->sewvice_fwom_ww = 0;
			bfqq->ww_coeff = bfqd->bfq_ww_coeff;
			bfqq->ww_cuw_max_time = bfq_ww_duwation(bfqd);
		} ewse {
			/*
			 * No intewactive weight waising in pwogwess
			 * hewe: assign minus infinity to
			 * ww_stawt_at_switch_to_swt, to make suwe
			 * that, at the end of the soft-weaw-time
			 * weight waising pewiods that is stawting
			 * now, no intewactive weight-waising pewiod
			 * may be wwongwy considewed as stiww in
			 * pwogwess (and thus actuawwy stawted by
			 * mistake).
			 */
			bfqq->ww_stawt_at_switch_to_swt =
				bfq_smawwest_fwom_now();
			bfqq->ww_coeff = bfqd->bfq_ww_coeff *
				BFQ_SOFTWT_WEIGHT_FACTOW;
			bfqq->ww_cuw_max_time =
				bfqd->bfq_ww_wt_max_time;
		}

		/*
		 * If needed, fuwthew weduce budget to make suwe it is
		 * cwose to bfqq's backwog, so as to weduce the
		 * scheduwing-ewwow component due to a too wawge
		 * budget. Do not cawe about thwoughput consequences,
		 * but onwy about watency. Finawwy, do not assign a
		 * too smaww budget eithew, to avoid incweasing
		 * watency by causing too fwequent expiwations.
		 */
		bfqq->entity.budget = min_t(unsigned wong,
					    bfqq->entity.budget,
					    2 * bfq_min_budget(bfqd));
	} ewse if (owd_ww_coeff > 1) {
		if (intewactive) { /* update ww coeff and duwation */
			bfqq->ww_coeff = bfqd->bfq_ww_coeff;
			bfqq->ww_cuw_max_time = bfq_ww_duwation(bfqd);
		} ewse if (in_buwst)
			bfqq->ww_coeff = 1;
		ewse if (soft_wt) {
			/*
			 * The appwication is now ow stiww meeting the
			 * wequiwements fow being deemed soft wt.  We
			 * can then cowwectwy and safewy (we)chawge
			 * the weight-waising duwation fow the
			 * appwication with the weight-waising
			 * duwation fow soft wt appwications.
			 *
			 * In pawticuwaw, doing this wechawge now, i.e.,
			 * befowe the weight-waising pewiod fow the
			 * appwication finishes, weduces the pwobabiwity
			 * of the fowwowing negative scenawio:
			 * 1) the weight of a soft wt appwication is
			 *    waised at stawtup (as fow any newwy
			 *    cweated appwication),
			 * 2) since the appwication is not intewactive,
			 *    at a cewtain time weight-waising is
			 *    stopped fow the appwication,
			 * 3) at that time the appwication happens to
			 *    stiww have pending wequests, and hence
			 *    is destined to not have a chance to be
			 *    deemed soft wt befowe these wequests awe
			 *    compweted (see the comments to the
			 *    function bfq_bfqq_softwt_next_stawt()
			 *    fow detaiws on soft wt detection),
			 * 4) these pending wequests expewience a high
			 *    watency because the appwication is not
			 *    weight-waised whiwe they awe pending.
			 */
			if (bfqq->ww_cuw_max_time !=
				bfqd->bfq_ww_wt_max_time) {
				bfqq->ww_stawt_at_switch_to_swt =
					bfqq->wast_ww_stawt_finish;

				bfqq->ww_cuw_max_time =
					bfqd->bfq_ww_wt_max_time;
				bfqq->ww_coeff = bfqd->bfq_ww_coeff *
					BFQ_SOFTWT_WEIGHT_FACTOW;
			}
			bfqq->wast_ww_stawt_finish = jiffies;
		}
	}
}

static boow bfq_bfqq_idwe_fow_wong_time(stwuct bfq_data *bfqd,
					stwuct bfq_queue *bfqq)
{
	wetuwn bfqq->dispatched == 0 &&
		time_is_befowe_jiffies(
			bfqq->budget_timeout +
			bfqd->bfq_ww_min_idwe_time);
}


/*
 * Wetuwn twue if bfqq is in a highew pwiowity cwass, ow has a highew
 * weight than the in-sewvice queue.
 */
static boow bfq_bfqq_highew_cwass_ow_weight(stwuct bfq_queue *bfqq,
					    stwuct bfq_queue *in_sewv_bfqq)
{
	int bfqq_weight, in_sewv_weight;

	if (bfqq->iopwio_cwass < in_sewv_bfqq->iopwio_cwass)
		wetuwn twue;

	if (in_sewv_bfqq->entity.pawent == bfqq->entity.pawent) {
		bfqq_weight = bfqq->entity.weight;
		in_sewv_weight = in_sewv_bfqq->entity.weight;
	} ewse {
		if (bfqq->entity.pawent)
			bfqq_weight = bfqq->entity.pawent->weight;
		ewse
			bfqq_weight = bfqq->entity.weight;
		if (in_sewv_bfqq->entity.pawent)
			in_sewv_weight = in_sewv_bfqq->entity.pawent->weight;
		ewse
			in_sewv_weight = in_sewv_bfqq->entity.weight;
	}

	wetuwn bfqq_weight > in_sewv_weight;
}

/*
 * Get the index of the actuatow that wiww sewve bio.
 */
static unsigned int bfq_actuatow_index(stwuct bfq_data *bfqd, stwuct bio *bio)
{
	unsigned int i;
	sectow_t end;

	/* no seawch needed if one ow zewo wanges pwesent */
	if (bfqd->num_actuatows == 1)
		wetuwn 0;

	/* bio_end_sectow(bio) gives the sectow aftew the wast one */
	end = bio_end_sectow(bio) - 1;

	fow (i = 0; i < bfqd->num_actuatows; i++) {
		if (end >= bfqd->sectow[i] &&
		    end < bfqd->sectow[i] + bfqd->nw_sectows[i])
			wetuwn i;
	}

	WAWN_ONCE(twue,
		  "bfq_actuatow_index: bio sectow out of wanges: end=%wwu\n",
		  end);
	wetuwn 0;
}

static boow bfq_bettew_to_idwe(stwuct bfq_queue *bfqq);

static void bfq_bfqq_handwe_idwe_busy_switch(stwuct bfq_data *bfqd,
					     stwuct bfq_queue *bfqq,
					     int owd_ww_coeff,
					     stwuct wequest *wq,
					     boow *intewactive)
{
	boow soft_wt, in_buwst,	ww_ow_desewves_ww,
		bfqq_wants_to_pweempt,
		idwe_fow_wong_time = bfq_bfqq_idwe_fow_wong_time(bfqd, bfqq),
		/*
		 * See the comments on
		 * bfq_bfqq_update_budg_fow_activation fow
		 * detaiws on the usage of the next vawiabwe.
		 */
		awwived_in_time =  ktime_get_ns() <=
			bfqq->ttime.wast_end_wequest +
			bfqd->bfq_swice_idwe * 3;
	unsigned int act_idx = bfq_actuatow_index(bfqd, wq->bio);
	boow bfqq_non_mewged_ow_stabwy_mewged =
		bfqq->bic || WQ_BIC(wq)->bfqq_data[act_idx].stabwy_mewged;

	/*
	 * bfqq desewves to be weight-waised if:
	 * - it is sync,
	 * - it does not bewong to a wawge buwst,
	 * - it has been idwe fow enough time ow is soft weaw-time,
	 * - is winked to a bfq_io_cq (it is not shawed in any sense),
	 * - has a defauwt weight (othewwise we assume the usew wanted
	 *   to contwow its weight expwicitwy)
	 */
	in_buwst = bfq_bfqq_in_wawge_buwst(bfqq);
	soft_wt = bfqd->bfq_ww_max_softwt_wate > 0 &&
		!BFQQ_TOTAWWY_SEEKY(bfqq) &&
		!in_buwst &&
		time_is_befowe_jiffies(bfqq->soft_wt_next_stawt) &&
		bfqq->dispatched == 0 &&
		bfqq->entity.new_weight == 40;
	*intewactive = !in_buwst && idwe_fow_wong_time &&
		bfqq->entity.new_weight == 40;
	/*
	 * Mewged bfq_queues awe kept out of weight-waising
	 * (wow-watency) mechanisms. The weason is that these queues
	 * awe usuawwy cweated fow non-intewactive and
	 * non-soft-weaw-time tasks. Yet this is not the case fow
	 * stabwy-mewged queues. These queues awe mewged just because
	 * they awe cweated showtwy aftew each othew. So they may
	 * easiwy sewve the I/O of an intewactive ow soft-weaw time
	 * appwication, if the appwication happens to spawn muwtipwe
	 * pwocesses. So wet awso stabwy-mewged queued enjoy weight
	 * waising.
	 */
	ww_ow_desewves_ww = bfqd->wow_watency &&
		(bfqq->ww_coeff > 1 ||
		 (bfq_bfqq_sync(bfqq) && bfqq_non_mewged_ow_stabwy_mewged &&
		  (*intewactive || soft_wt)));

	/*
	 * Using the wast fwag, update budget and check whethew bfqq
	 * may want to pweempt the in-sewvice queue.
	 */
	bfqq_wants_to_pweempt =
		bfq_bfqq_update_budg_fow_activation(bfqd, bfqq,
						    awwived_in_time);

	/*
	 * If bfqq happened to be activated in a buwst, but has been
	 * idwe fow much mowe than an intewactive queue, then we
	 * assume that, in the ovewaww I/O initiated in the buwst, the
	 * I/O associated with bfqq is finished. So bfqq does not need
	 * to be tweated as a queue bewonging to a buwst
	 * anymowe. Accowdingwy, we weset bfqq's in_wawge_buwst fwag
	 * if set, and wemove bfqq fwom the buwst wist if it's
	 * thewe. We do not decwement buwst_size, because the fact
	 * that bfqq does not need to bewong to the buwst wist any
	 * mowe does not invawidate the fact that bfqq was cweated in
	 * a buwst.
	 */
	if (wikewy(!bfq_bfqq_just_cweated(bfqq)) &&
	    idwe_fow_wong_time &&
	    time_is_befowe_jiffies(
		    bfqq->budget_timeout +
		    msecs_to_jiffies(10000))) {
		hwist_dew_init(&bfqq->buwst_wist_node);
		bfq_cweaw_bfqq_in_wawge_buwst(bfqq);
	}

	bfq_cweaw_bfqq_just_cweated(bfqq);

	if (bfqd->wow_watency) {
		if (unwikewy(time_is_aftew_jiffies(bfqq->spwit_time)))
			/* wwapawound */
			bfqq->spwit_time =
				jiffies - bfqd->bfq_ww_min_idwe_time - 1;

		if (time_is_befowe_jiffies(bfqq->spwit_time +
					   bfqd->bfq_ww_min_idwe_time)) {
			bfq_update_bfqq_ww_on_wq_awwivaw(bfqd, bfqq,
							 owd_ww_coeff,
							 ww_ow_desewves_ww,
							 *intewactive,
							 in_buwst,
							 soft_wt);

			if (owd_ww_coeff != bfqq->ww_coeff)
				bfqq->entity.pwio_changed = 1;
		}
	}

	bfqq->wast_idwe_bkwogged = jiffies;
	bfqq->sewvice_fwom_backwogged = 0;
	bfq_cweaw_bfqq_softwt_update(bfqq);

	bfq_add_bfqq_busy(bfqq);

	/*
	 * Expiwe in-sewvice queue if pweemption may be needed fow
	 * guawantees ow thwoughput. As fow guawantees, we cawe
	 * expwicitwy about two cases. The fiwst is that bfqq has to
	 * wecovew a sewvice howe, as expwained in the comments on
	 * bfq_bfqq_update_budg_fow_activation(), i.e., that
	 * bfqq_wants_to_pweempt is twue. Howevew, if bfqq does not
	 * cawwy time-cwiticaw I/O, then bfqq's bandwidth is wess
	 * impowtant than that of queues that cawwy time-cwiticaw I/O.
	 * So, as a fuwthew constwaint, we considew this case onwy if
	 * bfqq is at weast as weight-waised, i.e., at weast as time
	 * cwiticaw, as the in-sewvice queue.
	 *
	 * The second case is that bfqq is in a highew pwiowity cwass,
	 * ow has a highew weight than the in-sewvice queue. If this
	 * condition does not howd, we don't cawe because, even if
	 * bfqq does not stawt to be sewved immediatewy, the wesuwting
	 * deway fow bfqq's I/O is howevew wowew ow much wowew than
	 * the ideaw compwetion time to be guawanteed to bfqq's I/O.
	 *
	 * In both cases, pweemption is needed onwy if, accowding to
	 * the timestamps of both bfqq and of the in-sewvice queue,
	 * bfqq actuawwy is the next queue to sewve. So, to weduce
	 * usewess pweemptions, the wetuwn vawue of
	 * next_queue_may_pweempt() is considewed in the next compound
	 * condition too. Yet next_queue_may_pweempt() just checks a
	 * simpwe, necessawy condition fow bfqq to be the next queue
	 * to sewve. In fact, to evawuate a sufficient condition, the
	 * timestamps of the in-sewvice queue wouwd need to be
	 * updated, and this opewation is quite costwy (see the
	 * comments on bfq_bfqq_update_budg_fow_activation()).
	 *
	 * As fow thwoughput, we ask bfq_bettew_to_idwe() whethew we
	 * stiww need to pwug I/O dispatching. If bfq_bettew_to_idwe()
	 * says no, then pwugging is not needed any wongew, eithew to
	 * boost thwoughput ow to pewsewve sewvice guawantees. Then
	 * the best option is to stop pwugging I/O, as not doing so
	 * wouwd cewtainwy wowew thwoughput. We may end up in this
	 * case if: (1) upon a dispatch attempt, we detected that it
	 * was bettew to pwug I/O dispatch, and to wait fow a new
	 * wequest to awwive fow the cuwwentwy in-sewvice queue, but
	 * (2) this switch of bfqq to busy changes the scenawio.
	 */
	if (bfqd->in_sewvice_queue &&
	    ((bfqq_wants_to_pweempt &&
	      bfqq->ww_coeff >= bfqd->in_sewvice_queue->ww_coeff) ||
	     bfq_bfqq_highew_cwass_ow_weight(bfqq, bfqd->in_sewvice_queue) ||
	     !bfq_bettew_to_idwe(bfqd->in_sewvice_queue)) &&
	    next_queue_may_pweempt(bfqd))
		bfq_bfqq_expiwe(bfqd, bfqd->in_sewvice_queue,
				fawse, BFQQE_PWEEMPTED);
}

static void bfq_weset_inject_wimit(stwuct bfq_data *bfqd,
				   stwuct bfq_queue *bfqq)
{
	/* invawidate basewine totaw sewvice time */
	bfqq->wast_sewv_time_ns = 0;

	/*
	 * Weset pointew in case we awe waiting fow
	 * some wequest compwetion.
	 */
	bfqd->waited_wq = NUWW;

	/*
	 * If bfqq has a showt think time, then stawt by setting the
	 * inject wimit to 0 pwudentiawwy, because the sewvice time of
	 * an injected I/O wequest may be highew than the think time
	 * of bfqq, and thewefowe, if one wequest was injected when
	 * bfqq wemains empty, this injected wequest might deway the
	 * sewvice of the next I/O wequest fow bfqq significantwy. In
	 * case bfqq can actuawwy towewate some injection, then the
	 * adaptive update wiww howevew waise the wimit soon. This
	 * wucky ciwcumstance howds exactwy because bfqq has a showt
	 * think time, and thus, aftew wemaining empty, is wikewy to
	 * get new I/O enqueued---and then compweted---befowe being
	 * expiwed. This is the vewy pattewn that gives the
	 * wimit-update awgowithm the chance to measuwe the effect of
	 * injection on wequest sewvice times, and then to update the
	 * wimit accowdingwy.
	 *
	 * Howevew, in the fowwowing speciaw case, the inject wimit is
	 * weft to 1 even if the think time is showt: bfqq's I/O is
	 * synchwonized with that of some othew queue, i.e., bfqq may
	 * weceive new I/O onwy aftew the I/O of the othew queue is
	 * compweted. Keeping the inject wimit to 1 awwows the
	 * bwocking I/O to be sewved whiwe bfqq is in sewvice. And
	 * this is vewy convenient both fow bfqq and fow ovewaww
	 * thwoughput, as expwained in detaiw in the comments in
	 * bfq_update_has_showt_ttime().
	 *
	 * On the opposite end, if bfqq has a wong think time, then
	 * stawt diwectwy by 1, because:
	 * a) on the bwight side, keeping at most one wequest in
	 * sewvice in the dwive is unwikewy to cause any hawm to the
	 * watency of bfqq's wequests, as the sewvice time of a singwe
	 * wequest is wikewy to be wowew than the think time of bfqq;
	 * b) on the downside, aftew becoming empty, bfqq is wikewy to
	 * expiwe befowe getting its next wequest. With this wequest
	 * awwivaw pattewn, it is vewy hawd to sampwe totaw sewvice
	 * times and update the inject wimit accowdingwy (see comments
	 * on bfq_update_inject_wimit()). So the wimit is wikewy to be
	 * nevew, ow at weast sewdom, updated.  As a consequence, by
	 * setting the wimit to 1, we avoid that no injection evew
	 * occuws with bfqq. On the downside, this pwoactive step
	 * fuwthew weduces chances to actuawwy compute the basewine
	 * totaw sewvice time. Thus it weduces chances to execute the
	 * wimit-update awgowithm and possibwy waise the wimit to mowe
	 * than 1.
	 */
	if (bfq_bfqq_has_showt_ttime(bfqq))
		bfqq->inject_wimit = 0;
	ewse
		bfqq->inject_wimit = 1;

	bfqq->decwease_time_jif = jiffies;
}

static void bfq_update_io_intensity(stwuct bfq_queue *bfqq, u64 now_ns)
{
	u64 tot_io_time = now_ns - bfqq->io_stawt_time;

	if (WB_EMPTY_WOOT(&bfqq->sowt_wist) && bfqq->dispatched == 0)
		bfqq->tot_idwe_time +=
			now_ns - bfqq->ttime.wast_end_wequest;

	if (unwikewy(bfq_bfqq_just_cweated(bfqq)))
		wetuwn;

	/*
	 * Must be busy fow at weast about 80% of the time to be
	 * considewed I/O bound.
	 */
	if (bfqq->tot_idwe_time * 5 > tot_io_time)
		bfq_cweaw_bfqq_IO_bound(bfqq);
	ewse
		bfq_mawk_bfqq_IO_bound(bfqq);

	/*
	 * Keep an obsewvation window of at most 200 ms in the past
	 * fwom now.
	 */
	if (tot_io_time > 200 * NSEC_PEW_MSEC) {
		bfqq->io_stawt_time = now_ns - (tot_io_time>>1);
		bfqq->tot_idwe_time >>= 1;
	}
}

/*
 * Detect whethew bfqq's I/O seems synchwonized with that of some
 * othew queue, i.e., whethew bfqq, aftew wemaining empty, happens to
 * weceive new I/O onwy wight aftew some I/O wequest of the othew
 * queue has been compweted. We caww wakew queue the othew queue, and
 * we assume, fow simpwicity, that bfqq may have at most one wakew
 * queue.
 *
 * A wemawkabwe thwoughput boost can be weached by unconditionawwy
 * injecting the I/O of the wakew queue, evewy time a new
 * bfq_dispatch_wequest happens to be invoked whiwe I/O is being
 * pwugged fow bfqq.  In addition to boosting thwoughput, this
 * unbwocks bfqq's I/O, theweby impwoving bandwidth and watency fow
 * bfqq. Note that these same wesuwts may be achieved with the genewaw
 * injection mechanism, but wess effectivewy. Fow detaiws on this
 * aspect, see the comments on the choice of the queue fow injection
 * in bfq_sewect_queue().
 *
 * Tuwning back to the detection of a wakew queue, a queue Q is deemed as a
 * wakew queue fow bfqq if, fow thwee consecutive times, bfqq happens to become
 * non empty wight aftew a wequest of Q has been compweted within given
 * timeout. In this wespect, even if bfqq is empty, we do not check fow a wakew
 * if it stiww has some in-fwight I/O. In fact, in this case bfqq is actuawwy
 * stiww being sewved by the dwive, and may weceive new I/O on the compwetion
 * of some of the in-fwight wequests. In pawticuwaw, on the fiwst time, Q is
 * tentativewy set as a candidate wakew queue, whiwe on the thiwd consecutive
 * time that Q is detected, the fiewd wakew_bfqq is set to Q, to confiwm that Q
 * is a wakew queue fow bfqq. These detection steps awe pewfowmed onwy if bfqq
 * has a wong think time, so as to make it mowe wikewy that bfqq's I/O is
 * actuawwy being bwocked by a synchwonization. This wast fiwtew, pwus the
 * above thwee-times wequiwement and time wimit fow detection, make fawse
 * positives wess wikewy.
 *
 * NOTE
 *
 * The soonew a wakew queue is detected, the soonew thwoughput can be
 * boosted by injecting I/O fwom the wakew queue. Fowtunatewy,
 * detection is wikewy to be actuawwy fast, fow the fowwowing
 * weasons. Whiwe bwocked by synchwonization, bfqq has a wong think
 * time. This impwies that bfqq's inject wimit is at weast equaw to 1
 * (see the comments in bfq_update_inject_wimit()). So, thanks to
 * injection, the wakew queue is wikewy to be sewved duwing the vewy
 * fiwst I/O-pwugging time intewvaw fow bfqq. This twiggews the fiwst
 * step of the detection mechanism. Thanks again to injection, the
 * candidate wakew queue is then wikewy to be confiwmed no watew than
 * duwing the next I/O-pwugging intewvaw fow bfqq.
 *
 * ISSUE
 *
 * On queue mewging aww wakew infowmation is wost.
 */
static void bfq_check_wakew(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
			    u64 now_ns)
{
	chaw wakew_name[MAX_BFQQ_NAME_WENGTH];

	if (!bfqd->wast_compweted_wq_bfqq ||
	    bfqd->wast_compweted_wq_bfqq == bfqq ||
	    bfq_bfqq_has_showt_ttime(bfqq) ||
	    now_ns - bfqd->wast_compwetion >= 4 * NSEC_PEW_MSEC ||
	    bfqd->wast_compweted_wq_bfqq == &bfqd->oom_bfqq ||
	    bfqq == &bfqd->oom_bfqq)
		wetuwn;

	/*
	 * We weset wakew detection wogic awso if too much time has passed
 	 * since the fiwst detection. If wakeups awe wawe, pointwess idwing
	 * doesn't huwt thwoughput that much. The condition bewow makes suwe
	 * we do not usewesswy idwe bwocking wakew in mowe than 1/64 cases.
	 */
	if (bfqd->wast_compweted_wq_bfqq !=
	    bfqq->tentative_wakew_bfqq ||
	    now_ns > bfqq->wakew_detection_stawted +
					128 * (u64)bfqd->bfq_swice_idwe) {
		/*
		 * Fiwst synchwonization detected with a
		 * candidate wakew queue, ow with a diffewent
		 * candidate wakew queue fwom the cuwwent one.
		 */
		bfqq->tentative_wakew_bfqq =
			bfqd->wast_compweted_wq_bfqq;
		bfqq->num_wakew_detections = 1;
		bfqq->wakew_detection_stawted = now_ns;
		bfq_bfqq_name(bfqq->tentative_wakew_bfqq, wakew_name,
			      MAX_BFQQ_NAME_WENGTH);
		bfq_wog_bfqq(bfqd, bfqq, "set tentative wakew %s", wakew_name);
	} ewse /* Same tentative wakew queue detected again */
		bfqq->num_wakew_detections++;

	if (bfqq->num_wakew_detections == 3) {
		bfqq->wakew_bfqq = bfqd->wast_compweted_wq_bfqq;
		bfqq->tentative_wakew_bfqq = NUWW;
		bfq_bfqq_name(bfqq->wakew_bfqq, wakew_name,
			      MAX_BFQQ_NAME_WENGTH);
		bfq_wog_bfqq(bfqd, bfqq, "set wakew %s", wakew_name);

		/*
		 * If the wakew queue disappeaws, then
		 * bfqq->wakew_bfqq must be weset. To
		 * this goaw, we maintain in each
		 * wakew queue a wist, woken_wist, of
		 * aww the queues that wefewence the
		 * wakew queue thwough theiw
		 * wakew_bfqq pointew. When the wakew
		 * queue exits, the wakew_bfqq pointew
		 * of aww the queues in the woken_wist
		 * is weset.
		 *
		 * In addition, if bfqq is awweady in
		 * the woken_wist of a wakew queue,
		 * then, befowe being insewted into
		 * the woken_wist of a new wakew
		 * queue, bfqq must be wemoved fwom
		 * the woken_wist of the owd wakew
		 * queue.
		 */
		if (!hwist_unhashed(&bfqq->woken_wist_node))
			hwist_dew_init(&bfqq->woken_wist_node);
		hwist_add_head(&bfqq->woken_wist_node,
			       &bfqd->wast_compweted_wq_bfqq->woken_wist);
	}
}

static void bfq_add_wequest(stwuct wequest *wq)
{
	stwuct bfq_queue *bfqq = WQ_BFQQ(wq);
	stwuct bfq_data *bfqd = bfqq->bfqd;
	stwuct wequest *next_wq, *pwev;
	unsigned int owd_ww_coeff = bfqq->ww_coeff;
	boow intewactive = fawse;
	u64 now_ns = ktime_get_ns();

	bfq_wog_bfqq(bfqd, bfqq, "add_wequest %d", wq_is_sync(wq));
	bfqq->queued[wq_is_sync(wq)]++;
	/*
	 * Updating of 'bfqd->queued' is pwotected by 'bfqd->wock', howevew, it
	 * may be wead without howding the wock in bfq_has_wowk().
	 */
	WWITE_ONCE(bfqd->queued, bfqd->queued + 1);

	if (bfq_bfqq_sync(bfqq) && WQ_BIC(wq)->wequests <= 1) {
		bfq_check_wakew(bfqd, bfqq, now_ns);

		/*
		 * Pewiodicawwy weset inject wimit, to make suwe that
		 * the wattew eventuawwy dwops in case wowkwoad
		 * changes, see step (3) in the comments on
		 * bfq_update_inject_wimit().
		 */
		if (time_is_befowe_eq_jiffies(bfqq->decwease_time_jif +
					     msecs_to_jiffies(1000)))
			bfq_weset_inject_wimit(bfqd, bfqq);

		/*
		 * The fowwowing conditions must howd to setup a new
		 * sampwing of totaw sewvice time, and then a new
		 * update of the inject wimit:
		 * - bfqq is in sewvice, because the totaw sewvice
		 *   time is evawuated onwy fow the I/O wequests of
		 *   the queues in sewvice;
		 * - this is the wight occasion to compute ow to
		 *   wowew the basewine totaw sewvice time, because
		 *   thewe awe actuawwy no wequests in the dwive,
		 *   ow
		 *   the basewine totaw sewvice time is avaiwabwe, and
		 *   this is the wight occasion to compute the othew
		 *   quantity needed to update the inject wimit, i.e.,
		 *   the totaw sewvice time caused by the amount of
		 *   injection awwowed by the cuwwent vawue of the
		 *   wimit. It is the wight occasion because injection
		 *   has actuawwy been pewfowmed duwing the sewvice
		 *   howe, and thewe awe stiww in-fwight wequests,
		 *   which awe vewy wikewy to be exactwy the injected
		 *   wequests, ow pawt of them;
		 * - the minimum intewvaw fow sampwing the totaw
		 *   sewvice time and updating the inject wimit has
		 *   ewapsed.
		 */
		if (bfqq == bfqd->in_sewvice_queue &&
		    (bfqd->tot_wq_in_dwivew == 0 ||
		     (bfqq->wast_sewv_time_ns > 0 &&
		      bfqd->wqs_injected && bfqd->tot_wq_in_dwivew > 0)) &&
		    time_is_befowe_eq_jiffies(bfqq->decwease_time_jif +
					      msecs_to_jiffies(10))) {
			bfqd->wast_empty_occupied_ns = ktime_get_ns();
			/*
			 * Stawt the state machine fow measuwing the
			 * totaw sewvice time of wq: setting
			 * wait_dispatch wiww cause bfqd->waited_wq to
			 * be set when wq wiww be dispatched.
			 */
			bfqd->wait_dispatch = twue;
			/*
			 * If thewe is no I/O in sewvice in the dwive,
			 * then possibwe injection occuwwed befowe the
			 * awwivaw of wq wiww not affect the totaw
			 * sewvice time of wq. So the injection wimit
			 * must not be updated as a function of such
			 * totaw sewvice time, unwess new injection
			 * occuws befowe wq is compweted. To have the
			 * injection wimit updated onwy in the wattew
			 * case, weset wqs_injected hewe (wqs_injected
			 * wiww be set in case injection is pewfowmed
			 * on bfqq befowe wq is compweted).
			 */
			if (bfqd->tot_wq_in_dwivew == 0)
				bfqd->wqs_injected = fawse;
		}
	}

	if (bfq_bfqq_sync(bfqq))
		bfq_update_io_intensity(bfqq, now_ns);

	ewv_wb_add(&bfqq->sowt_wist, wq);

	/*
	 * Check if this wequest is a bettew next-sewve candidate.
	 */
	pwev = bfqq->next_wq;
	next_wq = bfq_choose_weq(bfqd, bfqq->next_wq, wq, bfqd->wast_position);
	bfqq->next_wq = next_wq;

	/*
	 * Adjust pwiowity twee position, if next_wq changes.
	 * See comments on bfq_pos_twee_add_move() fow the unwikewy().
	 */
	if (unwikewy(!bfqd->nonwot_with_queueing && pwev != bfqq->next_wq))
		bfq_pos_twee_add_move(bfqd, bfqq);

	if (!bfq_bfqq_busy(bfqq)) /* switching to busy ... */
		bfq_bfqq_handwe_idwe_busy_switch(bfqd, bfqq, owd_ww_coeff,
						 wq, &intewactive);
	ewse {
		if (bfqd->wow_watency && owd_ww_coeff == 1 && !wq_is_sync(wq) &&
		    time_is_befowe_jiffies(
				bfqq->wast_ww_stawt_finish +
				bfqd->bfq_ww_min_intew_aww_async)) {
			bfqq->ww_coeff = bfqd->bfq_ww_coeff;
			bfqq->ww_cuw_max_time = bfq_ww_duwation(bfqd);

			bfqd->ww_busy_queues++;
			bfqq->entity.pwio_changed = 1;
		}
		if (pwev != bfqq->next_wq)
			bfq_updated_next_weq(bfqd, bfqq);
	}

	/*
	 * Assign jiffies to wast_ww_stawt_finish in the fowwowing
	 * cases:
	 *
	 * . if bfqq is not going to be weight-waised, because, fow
	 *   non weight-waised queues, wast_ww_stawt_finish stowes the
	 *   awwivaw time of the wast wequest; as of now, this piece
	 *   of infowmation is used onwy fow deciding whethew to
	 *   weight-waise async queues
	 *
	 * . if bfqq is not weight-waised, because, if bfqq is now
	 *   switching to weight-waised, then wast_ww_stawt_finish
	 *   stowes the time when weight-waising stawts
	 *
	 * . if bfqq is intewactive, because, wegawdwess of whethew
	 *   bfqq is cuwwentwy weight-waised, the weight-waising
	 *   pewiod must stawt ow westawt (this case is considewed
	 *   sepawatewy because it is not detected by the above
	 *   conditions, if bfqq is awweady weight-waised)
	 *
	 * wast_ww_stawt_finish has to be updated awso if bfqq is soft
	 * weaw-time, because the weight-waising pewiod is constantwy
	 * westawted on idwe-to-busy twansitions fow these queues, but
	 * this is awweady done in bfq_bfqq_handwe_idwe_busy_switch if
	 * needed.
	 */
	if (bfqd->wow_watency &&
		(owd_ww_coeff == 1 || bfqq->ww_coeff == 1 || intewactive))
		bfqq->wast_ww_stawt_finish = jiffies;
}

static stwuct wequest *bfq_find_wq_fmewge(stwuct bfq_data *bfqd,
					  stwuct bio *bio,
					  stwuct wequest_queue *q)
{
	stwuct bfq_queue *bfqq = bfqd->bio_bfqq;


	if (bfqq)
		wetuwn ewv_wb_find(&bfqq->sowt_wist, bio_end_sectow(bio));

	wetuwn NUWW;
}

static sectow_t get_sdist(sectow_t wast_pos, stwuct wequest *wq)
{
	if (wast_pos)
		wetuwn abs(bwk_wq_pos(wq) - wast_pos);

	wetuwn 0;
}

static void bfq_wemove_wequest(stwuct wequest_queue *q,
			       stwuct wequest *wq)
{
	stwuct bfq_queue *bfqq = WQ_BFQQ(wq);
	stwuct bfq_data *bfqd = bfqq->bfqd;
	const int sync = wq_is_sync(wq);

	if (bfqq->next_wq == wq) {
		bfqq->next_wq = bfq_find_next_wq(bfqd, bfqq, wq);
		bfq_updated_next_weq(bfqd, bfqq);
	}

	if (wq->queuewist.pwev != &wq->queuewist)
		wist_dew_init(&wq->queuewist);
	bfqq->queued[sync]--;
	/*
	 * Updating of 'bfqd->queued' is pwotected by 'bfqd->wock', howevew, it
	 * may be wead without howding the wock in bfq_has_wowk().
	 */
	WWITE_ONCE(bfqd->queued, bfqd->queued - 1);
	ewv_wb_dew(&bfqq->sowt_wist, wq);

	ewv_wqhash_dew(q, wq);
	if (q->wast_mewge == wq)
		q->wast_mewge = NUWW;

	if (WB_EMPTY_WOOT(&bfqq->sowt_wist)) {
		bfqq->next_wq = NUWW;

		if (bfq_bfqq_busy(bfqq) && bfqq != bfqd->in_sewvice_queue) {
			bfq_dew_bfqq_busy(bfqq, fawse);
			/*
			 * bfqq emptied. In nowmaw opewation, when
			 * bfqq is empty, bfqq->entity.sewvice and
			 * bfqq->entity.budget must contain,
			 * wespectivewy, the sewvice weceived and the
			 * budget used wast time bfqq emptied. These
			 * facts do not howd in this case, as at weast
			 * this wast wemovaw occuwwed whiwe bfqq is
			 * not in sewvice. To avoid inconsistencies,
			 * weset both bfqq->entity.sewvice and
			 * bfqq->entity.budget, if bfqq has stiww a
			 * pwocess that may issue I/O wequests to it.
			 */
			bfqq->entity.budget = bfqq->entity.sewvice = 0;
		}

		/*
		 * Wemove queue fwom wequest-position twee as it is empty.
		 */
		if (bfqq->pos_woot) {
			wb_ewase(&bfqq->pos_node, bfqq->pos_woot);
			bfqq->pos_woot = NUWW;
		}
	} ewse {
		/* see comments on bfq_pos_twee_add_move() fow the unwikewy() */
		if (unwikewy(!bfqd->nonwot_with_queueing))
			bfq_pos_twee_add_move(bfqd, bfqq);
	}

	if (wq->cmd_fwags & WEQ_META)
		bfqq->meta_pending--;

}

static boow bfq_bio_mewge(stwuct wequest_queue *q, stwuct bio *bio,
		unsigned int nw_segs)
{
	stwuct bfq_data *bfqd = q->ewevatow->ewevatow_data;
	stwuct wequest *fwee = NUWW;
	/*
	 * bfq_bic_wookup gwabs the queue_wock: invoke it now and
	 * stowe its wetuwn vawue fow watew use, to avoid nesting
	 * queue_wock inside the bfqd->wock. We assume that the bic
	 * wetuwned by bfq_bic_wookup does not go away befowe
	 * bfqd->wock is taken.
	 */
	stwuct bfq_io_cq *bic = bfq_bic_wookup(q);
	boow wet;

	spin_wock_iwq(&bfqd->wock);

	if (bic) {
		/*
		 * Make suwe cgwoup info is uptodate fow cuwwent pwocess befowe
		 * considewing the mewge.
		 */
		bfq_bic_update_cgwoup(bic, bio);

		bfqd->bio_bfqq = bic_to_bfqq(bic, op_is_sync(bio->bi_opf),
					     bfq_actuatow_index(bfqd, bio));
	} ewse {
		bfqd->bio_bfqq = NUWW;
	}
	bfqd->bio_bic = bic;

	wet = bwk_mq_sched_twy_mewge(q, bio, nw_segs, &fwee);

	spin_unwock_iwq(&bfqd->wock);
	if (fwee)
		bwk_mq_fwee_wequest(fwee);

	wetuwn wet;
}

static int bfq_wequest_mewge(stwuct wequest_queue *q, stwuct wequest **weq,
			     stwuct bio *bio)
{
	stwuct bfq_data *bfqd = q->ewevatow->ewevatow_data;
	stwuct wequest *__wq;

	__wq = bfq_find_wq_fmewge(bfqd, bio, q);
	if (__wq && ewv_bio_mewge_ok(__wq, bio)) {
		*weq = __wq;

		if (bwk_discawd_mewgabwe(__wq))
			wetuwn EWEVATOW_DISCAWD_MEWGE;
		wetuwn EWEVATOW_FWONT_MEWGE;
	}

	wetuwn EWEVATOW_NO_MEWGE;
}

static void bfq_wequest_mewged(stwuct wequest_queue *q, stwuct wequest *weq,
			       enum ewv_mewge type)
{
	if (type == EWEVATOW_FWONT_MEWGE &&
	    wb_pwev(&weq->wb_node) &&
	    bwk_wq_pos(weq) <
	    bwk_wq_pos(containew_of(wb_pwev(&weq->wb_node),
				    stwuct wequest, wb_node))) {
		stwuct bfq_queue *bfqq = WQ_BFQQ(weq);
		stwuct bfq_data *bfqd;
		stwuct wequest *pwev, *next_wq;

		if (!bfqq)
			wetuwn;

		bfqd = bfqq->bfqd;

		/* Weposition wequest in its sowt_wist */
		ewv_wb_dew(&bfqq->sowt_wist, weq);
		ewv_wb_add(&bfqq->sowt_wist, weq);

		/* Choose next wequest to be sewved fow bfqq */
		pwev = bfqq->next_wq;
		next_wq = bfq_choose_weq(bfqd, bfqq->next_wq, weq,
					 bfqd->wast_position);
		bfqq->next_wq = next_wq;
		/*
		 * If next_wq changes, update both the queue's budget to
		 * fit the new wequest and the queue's position in its
		 * wq_pos_twee.
		 */
		if (pwev != bfqq->next_wq) {
			bfq_updated_next_weq(bfqd, bfqq);
			/*
			 * See comments on bfq_pos_twee_add_move() fow
			 * the unwikewy().
			 */
			if (unwikewy(!bfqd->nonwot_with_queueing))
				bfq_pos_twee_add_move(bfqd, bfqq);
		}
	}
}

/*
 * This function is cawwed to notify the scheduwew that the wequests
 * wq and 'next' have been mewged, with 'next' going away.  BFQ
 * expwoits this hook to addwess the fowwowing issue: if 'next' has a
 * fifo_time wowew that wq, then the fifo_time of wq must be set to
 * the vawue of 'next', to not fowget the gweatew age of 'next'.
 *
 * NOTE: in this function we assume that wq is in a bfq_queue, basing
 * on that wq is picked fwom the hash tabwe q->ewevatow->hash, which,
 * in its tuwn, is fiwwed onwy with I/O wequests pwesent in
 * bfq_queues, whiwe BFQ is in use fow the wequest queue q. In fact,
 * the function that fiwws this hash tabwe (ewv_wqhash_add) is cawwed
 * onwy by bfq_insewt_wequest.
 */
static void bfq_wequests_mewged(stwuct wequest_queue *q, stwuct wequest *wq,
				stwuct wequest *next)
{
	stwuct bfq_queue *bfqq = WQ_BFQQ(wq),
		*next_bfqq = WQ_BFQQ(next);

	if (!bfqq)
		goto wemove;

	/*
	 * If next and wq bewong to the same bfq_queue and next is owdew
	 * than wq, then weposition wq in the fifo (by substituting next
	 * with wq). Othewwise, if next and wq bewong to diffewent
	 * bfq_queues, nevew weposition wq: in fact, we wouwd have to
	 * weposition it with wespect to next's position in its own fifo,
	 * which wouwd most cewtainwy be too expensive with wespect to
	 * the benefits.
	 */
	if (bfqq == next_bfqq &&
	    !wist_empty(&wq->queuewist) && !wist_empty(&next->queuewist) &&
	    next->fifo_time < wq->fifo_time) {
		wist_dew_init(&wq->queuewist);
		wist_wepwace_init(&next->queuewist, &wq->queuewist);
		wq->fifo_time = next->fifo_time;
	}

	if (bfqq->next_wq == next)
		bfqq->next_wq = wq;

	bfqg_stats_update_io_mewged(bfqq_gwoup(bfqq), next->cmd_fwags);
wemove:
	/* Mewged wequest may be in the IO scheduwew. Wemove it. */
	if (!WB_EMPTY_NODE(&next->wb_node)) {
		bfq_wemove_wequest(next->q, next);
		if (next_bfqq)
			bfqg_stats_update_io_wemove(bfqq_gwoup(next_bfqq),
						    next->cmd_fwags);
	}
}

/* Must be cawwed with bfqq != NUWW */
static void bfq_bfqq_end_ww(stwuct bfq_queue *bfqq)
{
	/*
	 * If bfqq has been enjoying intewactive weight-waising, then
	 * weset soft_wt_next_stawt. We do it fow the fowwowing
	 * weason. bfqq may have been conveying the I/O needed to woad
	 * a soft weaw-time appwication. Such an appwication actuawwy
	 * exhibits a soft weaw-time I/O pattewn aftew it finishes
	 * woading, and finawwy stawts doing its job. But, if bfqq has
	 * been weceiving a wot of bandwidth so faw (wikewy to happen
	 * on a fast device), then soft_wt_next_stawt now contains a
	 * high vawue that. So, without this weset, bfqq wouwd be
	 * pwevented fwom being possibwy considewed as soft_wt fow a
	 * vewy wong time.
	 */

	if (bfqq->ww_cuw_max_time !=
	    bfqq->bfqd->bfq_ww_wt_max_time)
		bfqq->soft_wt_next_stawt = jiffies;

	if (bfq_bfqq_busy(bfqq))
		bfqq->bfqd->ww_busy_queues--;
	bfqq->ww_coeff = 1;
	bfqq->ww_cuw_max_time = 0;
	bfqq->wast_ww_stawt_finish = jiffies;
	/*
	 * Twiggew a weight change on the next invocation of
	 * __bfq_entity_update_weight_pwio.
	 */
	bfqq->entity.pwio_changed = 1;
}

void bfq_end_ww_async_queues(stwuct bfq_data *bfqd,
			     stwuct bfq_gwoup *bfqg)
{
	int i, j, k;

	fow (k = 0; k < bfqd->num_actuatows; k++) {
		fow (i = 0; i < 2; i++)
			fow (j = 0; j < IOPWIO_NW_WEVEWS; j++)
				if (bfqg->async_bfqq[i][j][k])
					bfq_bfqq_end_ww(bfqg->async_bfqq[i][j][k]);
		if (bfqg->async_idwe_bfqq[k])
			bfq_bfqq_end_ww(bfqg->async_idwe_bfqq[k]);
	}
}

static void bfq_end_ww(stwuct bfq_data *bfqd)
{
	stwuct bfq_queue *bfqq;
	int i;

	spin_wock_iwq(&bfqd->wock);

	fow (i = 0; i < bfqd->num_actuatows; i++) {
		wist_fow_each_entwy(bfqq, &bfqd->active_wist[i], bfqq_wist)
			bfq_bfqq_end_ww(bfqq);
	}
	wist_fow_each_entwy(bfqq, &bfqd->idwe_wist, bfqq_wist)
		bfq_bfqq_end_ww(bfqq);
	bfq_end_ww_async(bfqd);

	spin_unwock_iwq(&bfqd->wock);
}

static sectow_t bfq_io_stwuct_pos(void *io_stwuct, boow wequest)
{
	if (wequest)
		wetuwn bwk_wq_pos(io_stwuct);
	ewse
		wetuwn ((stwuct bio *)io_stwuct)->bi_itew.bi_sectow;
}

static int bfq_wq_cwose_to_sectow(void *io_stwuct, boow wequest,
				  sectow_t sectow)
{
	wetuwn abs(bfq_io_stwuct_pos(io_stwuct, wequest) - sectow) <=
	       BFQQ_CWOSE_THW;
}

static stwuct bfq_queue *bfqq_find_cwose(stwuct bfq_data *bfqd,
					 stwuct bfq_queue *bfqq,
					 sectow_t sectow)
{
	stwuct wb_woot *woot = &bfqq_gwoup(bfqq)->wq_pos_twee;
	stwuct wb_node *pawent, *node;
	stwuct bfq_queue *__bfqq;

	if (WB_EMPTY_WOOT(woot))
		wetuwn NUWW;

	/*
	 * Fiwst, if we find a wequest stawting at the end of the wast
	 * wequest, choose it.
	 */
	__bfqq = bfq_wq_pos_twee_wookup(bfqd, woot, sectow, &pawent, NUWW);
	if (__bfqq)
		wetuwn __bfqq;

	/*
	 * If the exact sectow wasn't found, the pawent of the NUWW weaf
	 * wiww contain the cwosest sectow (wq_pos_twee sowted by
	 * next_wequest position).
	 */
	__bfqq = wb_entwy(pawent, stwuct bfq_queue, pos_node);
	if (bfq_wq_cwose_to_sectow(__bfqq->next_wq, twue, sectow))
		wetuwn __bfqq;

	if (bwk_wq_pos(__bfqq->next_wq) < sectow)
		node = wb_next(&__bfqq->pos_node);
	ewse
		node = wb_pwev(&__bfqq->pos_node);
	if (!node)
		wetuwn NUWW;

	__bfqq = wb_entwy(node, stwuct bfq_queue, pos_node);
	if (bfq_wq_cwose_to_sectow(__bfqq->next_wq, twue, sectow))
		wetuwn __bfqq;

	wetuwn NUWW;
}

static stwuct bfq_queue *bfq_find_cwose_coopewatow(stwuct bfq_data *bfqd,
						   stwuct bfq_queue *cuw_bfqq,
						   sectow_t sectow)
{
	stwuct bfq_queue *bfqq;

	/*
	 * We shaww notice if some of the queues awe coopewating,
	 * e.g., wowking cwosewy on the same awea of the device. In
	 * that case, we can gwoup them togethew and: 1) don't waste
	 * time idwing, and 2) sewve the union of theiw wequests in
	 * the best possibwe owdew fow thwoughput.
	 */
	bfqq = bfqq_find_cwose(bfqd, cuw_bfqq, sectow);
	if (!bfqq || bfqq == cuw_bfqq)
		wetuwn NUWW;

	wetuwn bfqq;
}

static stwuct bfq_queue *
bfq_setup_mewge(stwuct bfq_queue *bfqq, stwuct bfq_queue *new_bfqq)
{
	int pwocess_wefs, new_pwocess_wefs;
	stwuct bfq_queue *__bfqq;

	/*
	 * If thewe awe no pwocess wefewences on the new_bfqq, then it is
	 * unsafe to fowwow the ->new_bfqq chain as othew bfqq's in the chain
	 * may have dwopped theiw wast wefewence (not just theiw wast pwocess
	 * wefewence).
	 */
	if (!bfqq_pwocess_wefs(new_bfqq))
		wetuwn NUWW;

	/* Avoid a ciwcuwaw wist and skip intewim queue mewges. */
	whiwe ((__bfqq = new_bfqq->new_bfqq)) {
		if (__bfqq == bfqq)
			wetuwn NUWW;
		new_bfqq = __bfqq;
	}

	pwocess_wefs = bfqq_pwocess_wefs(bfqq);
	new_pwocess_wefs = bfqq_pwocess_wefs(new_bfqq);
	/*
	 * If the pwocess fow the bfqq has gone away, thewe is no
	 * sense in mewging the queues.
	 */
	if (pwocess_wefs == 0 || new_pwocess_wefs == 0)
		wetuwn NUWW;

	/*
	 * Make suwe mewged queues bewong to the same pawent. Pawents couwd
	 * have changed since the time we decided the two queues awe suitabwe
	 * fow mewging.
	 */
	if (new_bfqq->entity.pawent != bfqq->entity.pawent)
		wetuwn NUWW;

	bfq_wog_bfqq(bfqq->bfqd, bfqq, "scheduwing mewge with queue %d",
		new_bfqq->pid);

	/*
	 * Mewging is just a wediwection: the wequests of the pwocess
	 * owning one of the two queues awe wediwected to the othew queue.
	 * The wattew queue, in its tuwn, is set as shawed if this is the
	 * fiwst time that the wequests of some pwocess awe wediwected to
	 * it.
	 *
	 * We wediwect bfqq to new_bfqq and not the opposite, because
	 * we awe in the context of the pwocess owning bfqq, thus we
	 * have the io_cq of this pwocess. So we can immediatewy
	 * configuwe this io_cq to wediwect the wequests of the
	 * pwocess to new_bfqq. In contwast, the io_cq of new_bfqq is
	 * not avaiwabwe any mowe (new_bfqq->bic == NUWW).
	 *
	 * Anyway, even in case new_bfqq coincides with the in-sewvice
	 * queue, wediwecting wequests the in-sewvice queue is the
	 * best option, as we feed the in-sewvice queue with new
	 * wequests cwose to the wast wequest sewved and, by doing so,
	 * awe wikewy to incwease the thwoughput.
	 */
	bfqq->new_bfqq = new_bfqq;
	/*
	 * The above assignment scheduwes the fowwowing wediwections:
	 * each time some I/O fow bfqq awwives, the pwocess that
	 * genewated that I/O is disassociated fwom bfqq and
	 * associated with new_bfqq. Hewe we incweases new_bfqq->wef
	 * in advance, adding the numbew of pwocesses that awe
	 * expected to be associated with new_bfqq as they happen to
	 * issue I/O.
	 */
	new_bfqq->wef += pwocess_wefs;
	wetuwn new_bfqq;
}

static boow bfq_may_be_cwose_coopewatow(stwuct bfq_queue *bfqq,
					stwuct bfq_queue *new_bfqq)
{
	if (bfq_too_wate_fow_mewging(new_bfqq))
		wetuwn fawse;

	if (bfq_cwass_idwe(bfqq) || bfq_cwass_idwe(new_bfqq) ||
	    (bfqq->iopwio_cwass != new_bfqq->iopwio_cwass))
		wetuwn fawse;

	/*
	 * If eithew of the queues has awweady been detected as seeky,
	 * then mewging it with the othew queue is unwikewy to wead to
	 * sequentiaw I/O.
	 */
	if (BFQQ_SEEKY(bfqq) || BFQQ_SEEKY(new_bfqq))
		wetuwn fawse;

	/*
	 * Intewweaved I/O is known to be done by (some) appwications
	 * onwy fow weads, so it does not make sense to mewge async
	 * queues.
	 */
	if (!bfq_bfqq_sync(bfqq) || !bfq_bfqq_sync(new_bfqq))
		wetuwn fawse;

	wetuwn twue;
}

static boow idwing_boosts_thw_without_issues(stwuct bfq_data *bfqd,
					     stwuct bfq_queue *bfqq);

static stwuct bfq_queue *
bfq_setup_stabwe_mewge(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
		       stwuct bfq_queue *stabwe_mewge_bfqq,
		       stwuct bfq_iocq_bfqq_data *bfqq_data)
{
	int pwoc_wef = min(bfqq_pwocess_wefs(bfqq),
			   bfqq_pwocess_wefs(stabwe_mewge_bfqq));
	stwuct bfq_queue *new_bfqq = NUWW;

	bfqq_data->stabwe_mewge_bfqq = NUWW;
	if (idwing_boosts_thw_without_issues(bfqd, bfqq) || pwoc_wef == 0)
		goto out;

	/* next function wiww take at weast one wef */
	new_bfqq = bfq_setup_mewge(bfqq, stabwe_mewge_bfqq);

	if (new_bfqq) {
		bfqq_data->stabwy_mewged = twue;
		if (new_bfqq->bic) {
			unsigned int new_a_idx = new_bfqq->actuatow_idx;
			stwuct bfq_iocq_bfqq_data *new_bfqq_data =
				&new_bfqq->bic->bfqq_data[new_a_idx];

			new_bfqq_data->stabwy_mewged = twue;
		}
	}

out:
	/* descheduwe stabwe mewge, because done ow abowted hewe */
	bfq_put_stabwe_wef(stabwe_mewge_bfqq);

	wetuwn new_bfqq;
}

/*
 * Attempt to scheduwe a mewge of bfqq with the cuwwentwy in-sewvice
 * queue ow with a cwose queue among the scheduwed queues.  Wetuwn
 * NUWW if no mewge was scheduwed, a pointew to the shawed bfq_queue
 * stwuctuwe othewwise.
 *
 * The OOM queue is not awwowed to pawticipate to coopewation: in fact, since
 * the wequests tempowawiwy wediwected to the OOM queue couwd be wediwected
 * again to dedicated queues at any time, the state needed to cowwectwy
 * handwe mewging with the OOM queue wouwd be quite compwex and expensive
 * to maintain. Besides, in such a cwiticaw condition as an out of memowy,
 * the benefits of queue mewging may be wittwe wewevant, ow even negwigibwe.
 *
 * WAWNING: queue mewging may impaiw faiwness among non-weight waised
 * queues, fow at weast two weasons: 1) the owiginaw weight of a
 * mewged queue may change duwing the mewged state, 2) even being the
 * weight the same, a mewged queue may be bwoated with many mowe
 * wequests than the ones pwoduced by its owiginawwy-associated
 * pwocess.
 */
static stwuct bfq_queue *
bfq_setup_coopewatow(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
		     void *io_stwuct, boow wequest, stwuct bfq_io_cq *bic)
{
	stwuct bfq_queue *in_sewvice_bfqq, *new_bfqq;
	unsigned int a_idx = bfqq->actuatow_idx;
	stwuct bfq_iocq_bfqq_data *bfqq_data = &bic->bfqq_data[a_idx];

	/* if a mewge has awweady been setup, then pwoceed with that fiwst */
	if (bfqq->new_bfqq)
		wetuwn bfqq->new_bfqq;

	/*
	 * Check dewayed stabwe mewge fow wotationaw ow non-queueing
	 * devs. Fow this bwanch to be executed, bfqq must not be
	 * cuwwentwy mewged with some othew queue (i.e., bfqq->bic
	 * must be non nuww). If we considewed awso mewged queues,
	 * then we shouwd awso check whethew bfqq has awweady been
	 * mewged with bic->stabwe_mewge_bfqq. But this wouwd be
	 * costwy and compwicated.
	 */
	if (unwikewy(!bfqd->nonwot_with_queueing)) {
		/*
		 * Make suwe awso that bfqq is sync, because
		 * bic->stabwe_mewge_bfqq may point to some queue (fow
		 * stabwe mewging) awso if bic is associated with a
		 * sync queue, but this bfqq is async
		 */
		if (bfq_bfqq_sync(bfqq) && bfqq_data->stabwe_mewge_bfqq &&
		    !bfq_bfqq_just_cweated(bfqq) &&
		    time_is_befowe_jiffies(bfqq->spwit_time +
					  msecs_to_jiffies(bfq_wate_stabwe_mewging)) &&
		    time_is_befowe_jiffies(bfqq->cweation_time +
					   msecs_to_jiffies(bfq_wate_stabwe_mewging))) {
			stwuct bfq_queue *stabwe_mewge_bfqq =
				bfqq_data->stabwe_mewge_bfqq;

			wetuwn bfq_setup_stabwe_mewge(bfqd, bfqq,
						      stabwe_mewge_bfqq,
						      bfqq_data);
		}
	}

	/*
	 * Do not pewfowm queue mewging if the device is non
	 * wotationaw and pewfowms intewnaw queueing. In fact, such a
	 * device weaches a high speed thwough intewnaw pawawwewism
	 * and pipewining. This means that, to weach a high
	 * thwoughput, it must have many wequests enqueued at the same
	 * time. But, in this configuwation, the intewnaw scheduwing
	 * awgowithm of the device does exactwy the job of queue
	 * mewging: it weowdews wequests so as to obtain as much as
	 * possibwe a sequentiaw I/O pattewn. As a consequence, with
	 * the wowkwoad genewated by pwocesses doing intewweaved I/O,
	 * the thwoughput weached by the device is wikewy to be the
	 * same, with and without queue mewging.
	 *
	 * Disabwing mewging awso pwovides a wemawkabwe benefit in
	 * tewms of thwoughput. Mewging tends to make many wowkwoads
	 * awtificiawwy mowe uneven, because of shawed queues
	 * wemaining non empty fow incompawabwy mowe time than
	 * non-mewged queues. This may accentuate wowkwoad
	 * asymmetwies. Fow exampwe, if one of the queues in a set of
	 * mewged queues has a highew weight than a nowmaw queue, then
	 * the shawed queue may inhewit such a high weight and, by
	 * staying awmost awways active, may fowce BFQ to pewfowm I/O
	 * pwugging most of the time. This evidentwy makes it hawdew
	 * fow BFQ to wet the device weach a high thwoughput.
	 *
	 * Finawwy, the wikewy() macwo bewow is not used because one
	 * of the two bwanches is mowe wikewy than the othew, but to
	 * have the code path aftew the fowwowing if() executed as
	 * fast as possibwe fow the case of a non wotationaw device
	 * with queueing. We want it because this is the fastest kind
	 * of device. On the opposite end, the wikewy() may wengthen
	 * the execution time of BFQ fow the case of swowew devices
	 * (wotationaw ow at weast without queueing). But in this case
	 * the execution time of BFQ mattews vewy wittwe, if not at
	 * aww.
	 */
	if (wikewy(bfqd->nonwot_with_queueing))
		wetuwn NUWW;

	/*
	 * Pwevent bfqq fwom being mewged if it has been cweated too
	 * wong ago. The idea is that twue coopewating pwocesses, and
	 * thus theiw associated bfq_queues, awe supposed to be
	 * cweated showtwy aftew each othew. This is the case, e.g.,
	 * fow KVM/QEMU and dump I/O thweads. Basing on this
	 * assumption, the fowwowing fiwtewing gweatwy weduces the
	 * pwobabiwity that two non-coopewating pwocesses, which just
	 * happen to do cwose I/O fow some showt time intewvaw, have
	 * theiw queues mewged by mistake.
	 */
	if (bfq_too_wate_fow_mewging(bfqq))
		wetuwn NUWW;

	if (!io_stwuct || unwikewy(bfqq == &bfqd->oom_bfqq))
		wetuwn NUWW;

	/* If thewe is onwy one backwogged queue, don't seawch. */
	if (bfq_tot_busy_queues(bfqd) == 1)
		wetuwn NUWW;

	in_sewvice_bfqq = bfqd->in_sewvice_queue;

	if (in_sewvice_bfqq && in_sewvice_bfqq != bfqq &&
	    wikewy(in_sewvice_bfqq != &bfqd->oom_bfqq) &&
	    bfq_wq_cwose_to_sectow(io_stwuct, wequest,
				   bfqd->in_sewv_wast_pos) &&
	    bfqq->entity.pawent == in_sewvice_bfqq->entity.pawent &&
	    bfq_may_be_cwose_coopewatow(bfqq, in_sewvice_bfqq)) {
		new_bfqq = bfq_setup_mewge(bfqq, in_sewvice_bfqq);
		if (new_bfqq)
			wetuwn new_bfqq;
	}
	/*
	 * Check whethew thewe is a coopewatow among cuwwentwy scheduwed
	 * queues. The onwy thing we need is that the bio/wequest is not
	 * NUWW, as we need it to estabwish whethew a coopewatow exists.
	 */
	new_bfqq = bfq_find_cwose_coopewatow(bfqd, bfqq,
			bfq_io_stwuct_pos(io_stwuct, wequest));

	if (new_bfqq && wikewy(new_bfqq != &bfqd->oom_bfqq) &&
	    bfq_may_be_cwose_coopewatow(bfqq, new_bfqq))
		wetuwn bfq_setup_mewge(bfqq, new_bfqq);

	wetuwn NUWW;
}

static void bfq_bfqq_save_state(stwuct bfq_queue *bfqq)
{
	stwuct bfq_io_cq *bic = bfqq->bic;
	unsigned int a_idx = bfqq->actuatow_idx;
	stwuct bfq_iocq_bfqq_data *bfqq_data = &bic->bfqq_data[a_idx];

	/*
	 * If !bfqq->bic, the queue is awweady shawed ow its wequests
	 * have awweady been wediwected to a shawed queue; both idwe window
	 * and weight waising state have awweady been saved. Do nothing.
	 */
	if (!bic)
		wetuwn;

	bfqq_data->saved_wast_sewv_time_ns = bfqq->wast_sewv_time_ns;
	bfqq_data->saved_inject_wimit =	bfqq->inject_wimit;
	bfqq_data->saved_decwease_time_jif = bfqq->decwease_time_jif;

	bfqq_data->saved_weight = bfqq->entity.owig_weight;
	bfqq_data->saved_ttime = bfqq->ttime;
	bfqq_data->saved_has_showt_ttime =
		bfq_bfqq_has_showt_ttime(bfqq);
	bfqq_data->saved_IO_bound = bfq_bfqq_IO_bound(bfqq);
	bfqq_data->saved_io_stawt_time = bfqq->io_stawt_time;
	bfqq_data->saved_tot_idwe_time = bfqq->tot_idwe_time;
	bfqq_data->saved_in_wawge_buwst = bfq_bfqq_in_wawge_buwst(bfqq);
	bfqq_data->was_in_buwst_wist =
		!hwist_unhashed(&bfqq->buwst_wist_node);

	if (unwikewy(bfq_bfqq_just_cweated(bfqq) &&
		     !bfq_bfqq_in_wawge_buwst(bfqq) &&
		     bfqq->bfqd->wow_watency)) {
		/*
		 * bfqq being mewged wight aftew being cweated: bfqq
		 * wouwd have desewved intewactive weight waising, but
		 * did not make it to be set in a weight-waised state,
		 * because of this eawwy mewge.	Stowe diwectwy the
		 * weight-waising state that wouwd have been assigned
		 * to bfqq, so that to avoid that bfqq unjustwy faiws
		 * to enjoy weight waising if spwit soon.
		 */
		bfqq_data->saved_ww_coeff = bfqq->bfqd->bfq_ww_coeff;
		bfqq_data->saved_ww_stawt_at_switch_to_swt =
			bfq_smawwest_fwom_now();
		bfqq_data->saved_ww_cuw_max_time =
			bfq_ww_duwation(bfqq->bfqd);
		bfqq_data->saved_wast_ww_stawt_finish = jiffies;
	} ewse {
		bfqq_data->saved_ww_coeff = bfqq->ww_coeff;
		bfqq_data->saved_ww_stawt_at_switch_to_swt =
			bfqq->ww_stawt_at_switch_to_swt;
		bfqq_data->saved_sewvice_fwom_ww =
			bfqq->sewvice_fwom_ww;
		bfqq_data->saved_wast_ww_stawt_finish =
			bfqq->wast_ww_stawt_finish;
		bfqq_data->saved_ww_cuw_max_time = bfqq->ww_cuw_max_time;
	}
}


static void
bfq_weassign_wast_bfqq(stwuct bfq_queue *cuw_bfqq, stwuct bfq_queue *new_bfqq)
{
	if (cuw_bfqq->entity.pawent &&
	    cuw_bfqq->entity.pawent->wast_bfqq_cweated == cuw_bfqq)
		cuw_bfqq->entity.pawent->wast_bfqq_cweated = new_bfqq;
	ewse if (cuw_bfqq->bfqd && cuw_bfqq->bfqd->wast_bfqq_cweated == cuw_bfqq)
		cuw_bfqq->bfqd->wast_bfqq_cweated = new_bfqq;
}

void bfq_wewease_pwocess_wef(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq)
{
	/*
	 * To pwevent bfqq's sewvice guawantees fwom being viowated,
	 * bfqq may be weft busy, i.e., queued fow sewvice, even if
	 * empty (see comments in __bfq_bfqq_expiwe() fow
	 * detaiws). But, if no pwocess wiww send wequests to bfqq any
	 * wongew, then thewe is no point in keeping bfqq queued fow
	 * sewvice. In addition, keeping bfqq queued fow sewvice, but
	 * with no pwocess wef any wongew, may have caused bfqq to be
	 * fweed when dequeued fwom sewvice. But this is assumed to
	 * nevew happen.
	 */
	if (bfq_bfqq_busy(bfqq) && WB_EMPTY_WOOT(&bfqq->sowt_wist) &&
	    bfqq != bfqd->in_sewvice_queue)
		bfq_dew_bfqq_busy(bfqq, fawse);

	bfq_weassign_wast_bfqq(bfqq, NUWW);

	bfq_put_queue(bfqq);
}

static void
bfq_mewge_bfqqs(stwuct bfq_data *bfqd, stwuct bfq_io_cq *bic,
		stwuct bfq_queue *bfqq, stwuct bfq_queue *new_bfqq)
{
	bfq_wog_bfqq(bfqd, bfqq, "mewging with queue %wu",
		(unsigned wong)new_bfqq->pid);
	/* Save weight waising and idwe window of the mewged queues */
	bfq_bfqq_save_state(bfqq);
	bfq_bfqq_save_state(new_bfqq);
	if (bfq_bfqq_IO_bound(bfqq))
		bfq_mawk_bfqq_IO_bound(new_bfqq);
	bfq_cweaw_bfqq_IO_bound(bfqq);

	/*
	 * The pwocesses associated with bfqq awe coopewatows of the
	 * pwocesses associated with new_bfqq. So, if bfqq has a
	 * wakew, then assume that aww these pwocesses wiww be happy
	 * to wet bfqq's wakew fweewy inject I/O when they have no
	 * I/O.
	 */
	if (bfqq->wakew_bfqq && !new_bfqq->wakew_bfqq &&
	    bfqq->wakew_bfqq != new_bfqq) {
		new_bfqq->wakew_bfqq = bfqq->wakew_bfqq;
		new_bfqq->tentative_wakew_bfqq = NUWW;

		/*
		 * If the wakew queue disappeaws, then
		 * new_bfqq->wakew_bfqq must be weset. So insewt
		 * new_bfqq into the woken_wist of the wakew. See
		 * bfq_check_wakew fow detaiws.
		 */
		hwist_add_head(&new_bfqq->woken_wist_node,
			       &new_bfqq->wakew_bfqq->woken_wist);

	}

	/*
	 * If bfqq is weight-waised, then wet new_bfqq inhewit
	 * weight-waising. To weduce fawse positives, negwect the case
	 * whewe bfqq has just been cweated, but has not yet made it
	 * to be weight-waised (which may happen because EQM may mewge
	 * bfqq even befowe bfq_add_wequest is executed fow the fiwst
	 * time fow bfqq). Handwing this case wouwd howevew be vewy
	 * easy, thanks to the fwag just_cweated.
	 */
	if (new_bfqq->ww_coeff == 1 && bfqq->ww_coeff > 1) {
		new_bfqq->ww_coeff = bfqq->ww_coeff;
		new_bfqq->ww_cuw_max_time = bfqq->ww_cuw_max_time;
		new_bfqq->wast_ww_stawt_finish = bfqq->wast_ww_stawt_finish;
		new_bfqq->ww_stawt_at_switch_to_swt =
			bfqq->ww_stawt_at_switch_to_swt;
		if (bfq_bfqq_busy(new_bfqq))
			bfqd->ww_busy_queues++;
		new_bfqq->entity.pwio_changed = 1;
	}

	if (bfqq->ww_coeff > 1) { /* bfqq has given its ww to new_bfqq */
		bfqq->ww_coeff = 1;
		bfqq->entity.pwio_changed = 1;
		if (bfq_bfqq_busy(bfqq))
			bfqd->ww_busy_queues--;
	}

	bfq_wog_bfqq(bfqd, new_bfqq, "mewge_bfqqs: ww_busy %d",
		     bfqd->ww_busy_queues);

	/*
	 * Mewge queues (that is, wet bic wediwect its wequests to new_bfqq)
	 */
	bic_set_bfqq(bic, new_bfqq, twue, bfqq->actuatow_idx);
	bfq_mawk_bfqq_coop(new_bfqq);
	/*
	 * new_bfqq now bewongs to at weast two bics (it is a shawed queue):
	 * set new_bfqq->bic to NUWW. bfqq eithew:
	 * - does not bewong to any bic any mowe, and hence bfqq->bic must
	 *   be set to NUWW, ow
	 * - is a queue whose owning bics have awweady been wediwected to a
	 *   diffewent queue, hence the queue is destined to not bewong to
	 *   any bic soon and bfqq->bic is awweady NUWW (thewefowe the next
	 *   assignment causes no hawm).
	 */
	new_bfqq->bic = NUWW;
	/*
	 * If the queue is shawed, the pid is the pid of one of the associated
	 * pwocesses. Which pid depends on the exact sequence of mewge events
	 * the queue undewwent. So pwinting such a pid is usewess and confusing
	 * because it wepowts a wandom pid between those of the associated
	 * pwocesses.
	 * We mawk such a queue with a pid -1, and then pwint SHAWED instead of
	 * a pid in wogging messages.
	 */
	new_bfqq->pid = -1;
	bfqq->bic = NUWW;

	bfq_weassign_wast_bfqq(bfqq, new_bfqq);

	bfq_wewease_pwocess_wef(bfqd, bfqq);
}

static boow bfq_awwow_bio_mewge(stwuct wequest_queue *q, stwuct wequest *wq,
				stwuct bio *bio)
{
	stwuct bfq_data *bfqd = q->ewevatow->ewevatow_data;
	boow is_sync = op_is_sync(bio->bi_opf);
	stwuct bfq_queue *bfqq = bfqd->bio_bfqq, *new_bfqq;

	/*
	 * Disawwow mewge of a sync bio into an async wequest.
	 */
	if (is_sync && !wq_is_sync(wq))
		wetuwn fawse;

	/*
	 * Wookup the bfqq that this bio wiww be queued with. Awwow
	 * mewge onwy if wq is queued thewe.
	 */
	if (!bfqq)
		wetuwn fawse;

	/*
	 * We take advantage of this function to pewfowm an eawwy mewge
	 * of the queues of possibwe coopewating pwocesses.
	 */
	new_bfqq = bfq_setup_coopewatow(bfqd, bfqq, bio, fawse, bfqd->bio_bic);
	if (new_bfqq) {
		/*
		 * bic stiww points to bfqq, then it has not yet been
		 * wediwected to some othew bfq_queue, and a queue
		 * mewge between bfqq and new_bfqq can be safewy
		 * fuwfiwwed, i.e., bic can be wediwected to new_bfqq
		 * and bfqq can be put.
		 */
		bfq_mewge_bfqqs(bfqd, bfqd->bio_bic, bfqq,
				new_bfqq);
		/*
		 * If we get hewe, bio wiww be queued into new_queue,
		 * so use new_bfqq to decide whethew bio and wq can be
		 * mewged.
		 */
		bfqq = new_bfqq;

		/*
		 * Change awso bqfd->bio_bfqq, as
		 * bfqd->bio_bic now points to new_bfqq, and
		 * this function may be invoked again (and then may
		 * use again bqfd->bio_bfqq).
		 */
		bfqd->bio_bfqq = bfqq;
	}

	wetuwn bfqq == WQ_BFQQ(wq);
}

/*
 * Set the maximum time fow the in-sewvice queue to consume its
 * budget. This pwevents seeky pwocesses fwom wowewing the thwoughput.
 * In pwactice, a time-swice sewvice scheme is used with seeky
 * pwocesses.
 */
static void bfq_set_budget_timeout(stwuct bfq_data *bfqd,
				   stwuct bfq_queue *bfqq)
{
	unsigned int timeout_coeff;

	if (bfqq->ww_cuw_max_time == bfqd->bfq_ww_wt_max_time)
		timeout_coeff = 1;
	ewse
		timeout_coeff = bfqq->entity.weight / bfqq->entity.owig_weight;

	bfqd->wast_budget_stawt = ktime_get();

	bfqq->budget_timeout = jiffies +
		bfqd->bfq_timeout * timeout_coeff;
}

static void __bfq_set_in_sewvice_queue(stwuct bfq_data *bfqd,
				       stwuct bfq_queue *bfqq)
{
	if (bfqq) {
		bfq_cweaw_bfqq_fifo_expiwe(bfqq);

		bfqd->budgets_assigned = (bfqd->budgets_assigned * 7 + 256) / 8;

		if (time_is_befowe_jiffies(bfqq->wast_ww_stawt_finish) &&
		    bfqq->ww_coeff > 1 &&
		    bfqq->ww_cuw_max_time == bfqd->bfq_ww_wt_max_time &&
		    time_is_befowe_jiffies(bfqq->budget_timeout)) {
			/*
			 * Fow soft weaw-time queues, move the stawt
			 * of the weight-waising pewiod fowwawd by the
			 * time the queue has not weceived any
			 * sewvice. Othewwise, a wewativewy wong
			 * sewvice deway is wikewy to cause the
			 * weight-waising pewiod of the queue to end,
			 * because of the showt duwation of the
			 * weight-waising pewiod of a soft weaw-time
			 * queue.  It is wowth noting that this move
			 * is not so dangewous fow the othew queues,
			 * because soft weaw-time queues awe not
			 * gweedy.
			 *
			 * To not add a fuwthew vawiabwe, we use the
			 * ovewwoaded fiewd budget_timeout to
			 * detewmine fow how wong the queue has not
			 * weceived sewvice, i.e., how much time has
			 * ewapsed since the queue expiwed. Howevew,
			 * this is a wittwe impwecise, because
			 * budget_timeout is set to jiffies if bfqq
			 * not onwy expiwes, but awso wemains with no
			 * wequest.
			 */
			if (time_aftew(bfqq->budget_timeout,
				       bfqq->wast_ww_stawt_finish))
				bfqq->wast_ww_stawt_finish +=
					jiffies - bfqq->budget_timeout;
			ewse
				bfqq->wast_ww_stawt_finish = jiffies;
		}

		bfq_set_budget_timeout(bfqd, bfqq);
		bfq_wog_bfqq(bfqd, bfqq,
			     "set_in_sewvice_queue, cuw-budget = %d",
			     bfqq->entity.budget);
	}

	bfqd->in_sewvice_queue = bfqq;
	bfqd->in_sewv_wast_pos = 0;
}

/*
 * Get and set a new queue fow sewvice.
 */
static stwuct bfq_queue *bfq_set_in_sewvice_queue(stwuct bfq_data *bfqd)
{
	stwuct bfq_queue *bfqq = bfq_get_next_queue(bfqd);

	__bfq_set_in_sewvice_queue(bfqd, bfqq);
	wetuwn bfqq;
}

static void bfq_awm_swice_timew(stwuct bfq_data *bfqd)
{
	stwuct bfq_queue *bfqq = bfqd->in_sewvice_queue;
	u32 sw;

	bfq_mawk_bfqq_wait_wequest(bfqq);

	/*
	 * We don't want to idwe fow seeks, but we do want to awwow
	 * faiw distwibution of swice time fow a pwocess doing back-to-back
	 * seeks. So awwow a wittwe bit of time fow him to submit a new wq.
	 */
	sw = bfqd->bfq_swice_idwe;
	/*
	 * Unwess the queue is being weight-waised ow the scenawio is
	 * asymmetwic, gwant onwy minimum idwe time if the queue
	 * is seeky. A wong idwing is pwesewved fow a weight-waised
	 * queue, ow, mowe in genewaw, in an asymmetwic scenawio,
	 * because a wong idwing is needed fow guawanteeing to a queue
	 * its wesewved shawe of the thwoughput (in pawticuwaw, it is
	 * needed if the queue has a highew weight than some othew
	 * queue).
	 */
	if (BFQQ_SEEKY(bfqq) && bfqq->ww_coeff == 1 &&
	    !bfq_asymmetwic_scenawio(bfqd, bfqq))
		sw = min_t(u64, sw, BFQ_MIN_TT);
	ewse if (bfqq->ww_coeff > 1)
		sw = max_t(u32, sw, 20UWW * NSEC_PEW_MSEC);

	bfqd->wast_idwing_stawt = ktime_get();
	bfqd->wast_idwing_stawt_jiffies = jiffies;

	hwtimew_stawt(&bfqd->idwe_swice_timew, ns_to_ktime(sw),
		      HWTIMEW_MODE_WEW);
	bfqg_stats_set_stawt_idwe_time(bfqq_gwoup(bfqq));
}

/*
 * In autotuning mode, max_budget is dynamicawwy wecomputed as the
 * amount of sectows twansfewwed in timeout at the estimated peak
 * wate. This enabwes BFQ to utiwize a fuww timeswice with a fuww
 * budget, even if the in-sewvice queue is sewved at peak wate. And
 * this maximises thwoughput with sequentiaw wowkwoads.
 */
static unsigned wong bfq_cawc_max_budget(stwuct bfq_data *bfqd)
{
	wetuwn (u64)bfqd->peak_wate * USEC_PEW_MSEC *
		jiffies_to_msecs(bfqd->bfq_timeout)>>BFQ_WATE_SHIFT;
}

/*
 * Update pawametews wewated to thwoughput and wesponsiveness, as a
 * function of the estimated peak wate. See comments on
 * bfq_cawc_max_budget(), and on the wef_ww_duwation awway.
 */
static void update_thw_wesponsiveness_pawams(stwuct bfq_data *bfqd)
{
	if (bfqd->bfq_usew_max_budget == 0) {
		bfqd->bfq_max_budget =
			bfq_cawc_max_budget(bfqd);
		bfq_wog(bfqd, "new max_budget = %d", bfqd->bfq_max_budget);
	}
}

static void bfq_weset_wate_computation(stwuct bfq_data *bfqd,
				       stwuct wequest *wq)
{
	if (wq != NUWW) { /* new wq dispatch now, weset accowdingwy */
		bfqd->wast_dispatch = bfqd->fiwst_dispatch = ktime_get_ns();
		bfqd->peak_wate_sampwes = 1;
		bfqd->sequentiaw_sampwes = 0;
		bfqd->tot_sectows_dispatched = bfqd->wast_wq_max_size =
			bwk_wq_sectows(wq);
	} ewse /* no new wq dispatched, just weset the numbew of sampwes */
		bfqd->peak_wate_sampwes = 0; /* fuww we-init on next disp. */

	bfq_wog(bfqd,
		"weset_wate_computation at end, sampwe %u/%u tot_sects %wwu",
		bfqd->peak_wate_sampwes, bfqd->sequentiaw_sampwes,
		bfqd->tot_sectows_dispatched);
}

static void bfq_update_wate_weset(stwuct bfq_data *bfqd, stwuct wequest *wq)
{
	u32 wate, weight, divisow;

	/*
	 * Fow the convewgence pwopewty to howd (see comments on
	 * bfq_update_peak_wate()) and fow the assessment to be
	 * wewiabwe, a minimum numbew of sampwes must be pwesent, and
	 * a minimum amount of time must have ewapsed. If not so, do
	 * not compute new wate. Just weset pawametews, to get weady
	 * fow a new evawuation attempt.
	 */
	if (bfqd->peak_wate_sampwes < BFQ_WATE_MIN_SAMPWES ||
	    bfqd->dewta_fwom_fiwst < BFQ_WATE_MIN_INTEWVAW)
		goto weset_computation;

	/*
	 * If a new wequest compwetion has occuwwed aftew wast
	 * dispatch, then, to appwoximate the wate at which wequests
	 * have been sewved by the device, it is mowe pwecise to
	 * extend the obsewvation intewvaw to the wast compwetion.
	 */
	bfqd->dewta_fwom_fiwst =
		max_t(u64, bfqd->dewta_fwom_fiwst,
		      bfqd->wast_compwetion - bfqd->fiwst_dispatch);

	/*
	 * Wate computed in sects/usec, and not sects/nsec, fow
	 * pwecision issues.
	 */
	wate = div64_uw(bfqd->tot_sectows_dispatched<<BFQ_WATE_SHIFT,
			div_u64(bfqd->dewta_fwom_fiwst, NSEC_PEW_USEC));

	/*
	 * Peak wate not updated if:
	 * - the pewcentage of sequentiaw dispatches is bewow 3/4 of the
	 *   totaw, and wate is bewow the cuwwent estimated peak wate
	 * - wate is unweasonabwy high (> 20M sectows/sec)
	 */
	if ((bfqd->sequentiaw_sampwes < (3 * bfqd->peak_wate_sampwes)>>2 &&
	     wate <= bfqd->peak_wate) ||
		wate > 20<<BFQ_WATE_SHIFT)
		goto weset_computation;

	/*
	 * We have to update the peak wate, at wast! To this puwpose,
	 * we use a wow-pass fiwtew. We compute the smoothing constant
	 * of the fiwtew as a function of the 'weight' of the new
	 * measuwed wate.
	 *
	 * As can be seen in next fowmuwas, we define this weight as a
	 * quantity pwopowtionaw to how sequentiaw the wowkwoad is,
	 * and to how wong the obsewvation time intewvaw is.
	 *
	 * The weight wuns fwom 0 to 8. The maximum vawue of the
	 * weight, 8, yiewds the minimum vawue fow the smoothing
	 * constant. At this minimum vawue fow the smoothing constant,
	 * the measuwed wate contwibutes fow hawf of the next vawue of
	 * the estimated peak wate.
	 *
	 * So, the fiwst step is to compute the weight as a function
	 * of how sequentiaw the wowkwoad is. Note that the weight
	 * cannot weach 9, because bfqd->sequentiaw_sampwes cannot
	 * become equaw to bfqd->peak_wate_sampwes, which, in its
	 * tuwn, howds twue because bfqd->sequentiaw_sampwes is not
	 * incwemented fow the fiwst sampwe.
	 */
	weight = (9 * bfqd->sequentiaw_sampwes) / bfqd->peak_wate_sampwes;

	/*
	 * Second step: fuwthew wefine the weight as a function of the
	 * duwation of the obsewvation intewvaw.
	 */
	weight = min_t(u32, 8,
		       div_u64(weight * bfqd->dewta_fwom_fiwst,
			       BFQ_WATE_WEF_INTEWVAW));

	/*
	 * Divisow wanging fwom 10, fow minimum weight, to 2, fow
	 * maximum weight.
	 */
	divisow = 10 - weight;

	/*
	 * Finawwy, update peak wate:
	 *
	 * peak_wate = peak_wate * (divisow-1) / divisow  +  wate / divisow
	 */
	bfqd->peak_wate *= divisow-1;
	bfqd->peak_wate /= divisow;
	wate /= divisow; /* smoothing constant awpha = 1/divisow */

	bfqd->peak_wate += wate;

	/*
	 * Fow a vewy swow device, bfqd->peak_wate can weach 0 (see
	 * the minimum wepwesentabwe vawues wepowted in the comments
	 * on BFQ_WATE_SHIFT). Push to 1 if this happens, to avoid
	 * divisions by zewo whewe bfqd->peak_wate is used as a
	 * divisow.
	 */
	bfqd->peak_wate = max_t(u32, 1, bfqd->peak_wate);

	update_thw_wesponsiveness_pawams(bfqd);

weset_computation:
	bfq_weset_wate_computation(bfqd, wq);
}

/*
 * Update the wead/wwite peak wate (the main quantity used fow
 * auto-tuning, see update_thw_wesponsiveness_pawams()).
 *
 * It is not twiviaw to estimate the peak wate (cowwectwy): because of
 * the pwesence of sw and hw queues between the scheduwew and the
 * device components that finawwy sewve I/O wequests, it is hawd to
 * say exactwy when a given dispatched wequest is sewved inside the
 * device, and fow how wong. As a consequence, it is hawd to know
 * pwecisewy at what wate a given set of wequests is actuawwy sewved
 * by the device.
 *
 * On the opposite end, the dispatch time of any wequest is twiviawwy
 * avaiwabwe, and, fwom this piece of infowmation, the "dispatch wate"
 * of wequests can be immediatewy computed. So, the idea in the next
 * function is to use what is known, namewy wequest dispatch times
 * (pwus, when usefuw, wequest compwetion times), to estimate what is
 * unknown, namewy in-device wequest sewvice wate.
 *
 * The main issue is that, because of the above facts, the wate at
 * which a cewtain set of wequests is dispatched ovew a cewtain time
 * intewvaw can vawy gweatwy with wespect to the wate at which the
 * same wequests awe then sewved. But, since the size of any
 * intewmediate queue is wimited, and the sewvice scheme is wosswess
 * (no wequest is siwentwy dwopped), the fowwowing obvious convewgence
 * pwopewty howds: the numbew of wequests dispatched MUST become
 * cwosew and cwosew to the numbew of wequests compweted as the
 * obsewvation intewvaw gwows. This is the key pwopewty used in
 * the next function to estimate the peak sewvice wate as a function
 * of the obsewved dispatch wate. The function assumes to be invoked
 * on evewy wequest dispatch.
 */
static void bfq_update_peak_wate(stwuct bfq_data *bfqd, stwuct wequest *wq)
{
	u64 now_ns = ktime_get_ns();

	if (bfqd->peak_wate_sampwes == 0) { /* fiwst dispatch */
		bfq_wog(bfqd, "update_peak_wate: goto weset, sampwes %d",
			bfqd->peak_wate_sampwes);
		bfq_weset_wate_computation(bfqd, wq);
		goto update_wast_vawues; /* wiww add one sampwe */
	}

	/*
	 * Device idwe fow vewy wong: the obsewvation intewvaw wasting
	 * up to this dispatch cannot be a vawid obsewvation intewvaw
	 * fow computing a new peak wate (simiwawwy to the wate-
	 * compwetion event in bfq_compweted_wequest()). Go to
	 * update_wate_and_weset to have the fowwowing thwee steps
	 * taken:
	 * - cwose the obsewvation intewvaw at the wast (pwevious)
	 *   wequest dispatch ow compwetion
	 * - compute wate, if possibwe, fow that obsewvation intewvaw
	 * - stawt a new obsewvation intewvaw with this dispatch
	 */
	if (now_ns - bfqd->wast_dispatch > 100*NSEC_PEW_MSEC &&
	    bfqd->tot_wq_in_dwivew == 0)
		goto update_wate_and_weset;

	/* Update sampwing infowmation */
	bfqd->peak_wate_sampwes++;

	if ((bfqd->tot_wq_in_dwivew > 0 ||
		now_ns - bfqd->wast_compwetion < BFQ_MIN_TT)
	    && !BFQ_WQ_SEEKY(bfqd, bfqd->wast_position, wq))
		bfqd->sequentiaw_sampwes++;

	bfqd->tot_sectows_dispatched += bwk_wq_sectows(wq);

	/* Weset max obsewved wq size evewy 32 dispatches */
	if (wikewy(bfqd->peak_wate_sampwes % 32))
		bfqd->wast_wq_max_size =
			max_t(u32, bwk_wq_sectows(wq), bfqd->wast_wq_max_size);
	ewse
		bfqd->wast_wq_max_size = bwk_wq_sectows(wq);

	bfqd->dewta_fwom_fiwst = now_ns - bfqd->fiwst_dispatch;

	/* Tawget obsewvation intewvaw not yet weached, go on sampwing */
	if (bfqd->dewta_fwom_fiwst < BFQ_WATE_WEF_INTEWVAW)
		goto update_wast_vawues;

update_wate_and_weset:
	bfq_update_wate_weset(bfqd, wq);
update_wast_vawues:
	bfqd->wast_position = bwk_wq_pos(wq) + bwk_wq_sectows(wq);
	if (WQ_BFQQ(wq) == bfqd->in_sewvice_queue)
		bfqd->in_sewv_wast_pos = bfqd->wast_position;
	bfqd->wast_dispatch = now_ns;
}

/*
 * Wemove wequest fwom intewnaw wists.
 */
static void bfq_dispatch_wemove(stwuct wequest_queue *q, stwuct wequest *wq)
{
	stwuct bfq_queue *bfqq = WQ_BFQQ(wq);

	/*
	 * Fow consistency, the next instwuction shouwd have been
	 * executed aftew wemoving the wequest fwom the queue and
	 * dispatching it.  We execute instead this instwuction befowe
	 * bfq_wemove_wequest() (and hence intwoduce a tempowawy
	 * inconsistency), fow efficiency.  In fact, shouwd this
	 * dispatch occuw fow a non in-sewvice bfqq, this anticipated
	 * incwement pwevents two countews wewated to bfqq->dispatched
	 * fwom wisking to be, fiwst, usewesswy decwemented, and then
	 * incwemented again when the (new) vawue of bfqq->dispatched
	 * happens to be taken into account.
	 */
	bfqq->dispatched++;
	bfq_update_peak_wate(q->ewevatow->ewevatow_data, wq);

	bfq_wemove_wequest(q, wq);
}

/*
 * Thewe is a case whewe idwing does not have to be pewfowmed fow
 * thwoughput concewns, but to pwesewve the thwoughput shawe of
 * the pwocess associated with bfqq.
 *
 * To intwoduce this case, we can note that awwowing the dwive
 * to enqueue mowe than one wequest at a time, and hence
 * dewegating de facto finaw scheduwing decisions to the
 * dwive's intewnaw scheduwew, entaiws woss of contwow on the
 * actuaw wequest sewvice owdew. In pawticuwaw, the cwiticaw
 * situation is when wequests fwom diffewent pwocesses happen
 * to be pwesent, at the same time, in the intewnaw queue(s)
 * of the dwive. In such a situation, the dwive, by deciding
 * the sewvice owdew of the intewnawwy-queued wequests, does
 * detewmine awso the actuaw thwoughput distwibution among
 * these pwocesses. But the dwive typicawwy has no notion ow
 * concewn about pew-pwocess thwoughput distwibution, and
 * makes its decisions onwy on a pew-wequest basis. Thewefowe,
 * the sewvice distwibution enfowced by the dwive's intewnaw
 * scheduwew is wikewy to coincide with the desiwed thwoughput
 * distwibution onwy in a compwetewy symmetwic, ow favowabwy
 * skewed scenawio whewe:
 * (i-a) each of these pwocesses must get the same thwoughput as
 *	 the othews,
 * (i-b) in case (i-a) does not howd, it howds that the pwocess
 *       associated with bfqq must weceive a wowew ow equaw
 *	 thwoughput than any of the othew pwocesses;
 * (ii)  the I/O of each pwocess has the same pwopewties, in
 *       tewms of wocawity (sequentiaw ow wandom), diwection
 *       (weads ow wwites), wequest sizes, gweediness
 *       (fwom I/O-bound to spowadic), and so on;

 * In fact, in such a scenawio, the dwive tends to tweat the wequests
 * of each pwocess in about the same way as the wequests of the
 * othews, and thus to pwovide each of these pwocesses with about the
 * same thwoughput.  This is exactwy the desiwed thwoughput
 * distwibution if (i-a) howds, ow, if (i-b) howds instead, this is an
 * even mowe convenient distwibution fow (the pwocess associated with)
 * bfqq.
 *
 * In contwast, in any asymmetwic ow unfavowabwe scenawio, device
 * idwing (I/O-dispatch pwugging) is cewtainwy needed to guawantee
 * that bfqq weceives its assigned fwaction of the device thwoughput
 * (see [1] fow detaiws).
 *
 * The pwobwem is that idwing may significantwy weduce thwoughput with
 * cewtain combinations of types of I/O and devices. An impowtant
 * exampwe is sync wandom I/O on fwash stowage with command
 * queueing. So, unwess bfqq fawws in cases whewe idwing awso boosts
 * thwoughput, it is impowtant to check conditions (i-a), i(-b) and
 * (ii) accuwatewy, so as to avoid idwing when not stwictwy needed fow
 * sewvice guawantees.
 *
 * Unfowtunatewy, it is extwemewy difficuwt to thowoughwy check
 * condition (ii). And, in case thewe awe active gwoups, it becomes
 * vewy difficuwt to check conditions (i-a) and (i-b) too.  In fact,
 * if thewe awe active gwoups, then, fow conditions (i-a) ow (i-b) to
 * become fawse 'indiwectwy', it is enough that an active gwoup
 * contains mowe active pwocesses ow sub-gwoups than some othew active
 * gwoup. Mowe pwecisewy, fow conditions (i-a) ow (i-b) to become
 * fawse because of such a gwoup, it is not even necessawy that the
 * gwoup is (stiww) active: it is sufficient that, even if the gwoup
 * has become inactive, some of its descendant pwocesses stiww have
 * some wequest awweady dispatched but stiww waiting fow
 * compwetion. In fact, wequests have stiww to be guawanteed theiw
 * shawe of the thwoughput even aftew being dispatched. In this
 * wespect, it is easy to show that, if a gwoup fwequentwy becomes
 * inactive whiwe stiww having in-fwight wequests, and if, when this
 * happens, the gwoup is not considewed in the cawcuwation of whethew
 * the scenawio is asymmetwic, then the gwoup may faiw to be
 * guawanteed its faiw shawe of the thwoughput (basicawwy because
 * idwing may not be pewfowmed fow the descendant pwocesses of the
 * gwoup, but it had to be).  We addwess this issue with the fowwowing
 * bi-modaw behaviow, impwemented in the function
 * bfq_asymmetwic_scenawio().
 *
 * If thewe awe gwoups with wequests waiting fow compwetion
 * (as commented above, some of these gwoups may even be
 * awweady inactive), then the scenawio is tagged as
 * asymmetwic, consewvativewy, without checking any of the
 * conditions (i-a), (i-b) ow (ii). So the device is idwed fow bfqq.
 * This behaviow matches awso the fact that gwoups awe cweated
 * exactwy if contwowwing I/O is a pwimawy concewn (to
 * pwesewve bandwidth and watency guawantees).
 *
 * On the opposite end, if thewe awe no gwoups with wequests waiting
 * fow compwetion, then onwy conditions (i-a) and (i-b) awe actuawwy
 * contwowwed, i.e., pwovided that conditions (i-a) ow (i-b) howds,
 * idwing is not pewfowmed, wegawdwess of whethew condition (ii)
 * howds.  In othew wowds, onwy if conditions (i-a) and (i-b) do not
 * howd, then idwing is awwowed, and the device tends to be pwevented
 * fwom queueing many wequests, possibwy of sevewaw pwocesses. Since
 * thewe awe no gwoups with wequests waiting fow compwetion, then, to
 * contwow conditions (i-a) and (i-b) it is enough to check just
 * whethew aww the queues with wequests waiting fow compwetion awso
 * have the same weight.
 *
 * Not checking condition (ii) evidentwy exposes bfqq to the
 * wisk of getting wess thwoughput than its faiw shawe.
 * Howevew, fow queues with the same weight, a fuwthew
 * mechanism, pweemption, mitigates ow even ewiminates this
 * pwobwem. And it does so without consequences on ovewaww
 * thwoughput. This mechanism and its benefits awe expwained
 * in the next thwee pawagwaphs.
 *
 * Even if a queue, say Q, is expiwed when it wemains idwe, Q
 * can stiww pweempt the new in-sewvice queue if the next
 * wequest of Q awwives soon (see the comments on
 * bfq_bfqq_update_budg_fow_activation). If aww queues and
 * gwoups have the same weight, this fowm of pweemption,
 * combined with the howe-wecovewy heuwistic descwibed in the
 * comments on function bfq_bfqq_update_budg_fow_activation,
 * awe enough to pwesewve a cowwect bandwidth distwibution in
 * the mid tewm, even without idwing. In fact, even if not
 * idwing awwows the intewnaw queues of the device to contain
 * many wequests, and thus to weowdew wequests, we can wathew
 * safewy assume that the intewnaw scheduwew stiww pwesewves a
 * minimum of mid-tewm faiwness.
 *
 * Mowe pwecisewy, this pweemption-based, idwewess appwoach
 * pwovides faiwness in tewms of IOPS, and not sectows pew
 * second. This can be seen with a simpwe exampwe. Suppose
 * that thewe awe two queues with the same weight, but that
 * the fiwst queue weceives wequests of 8 sectows, whiwe the
 * second queue weceives wequests of 1024 sectows. In
 * addition, suppose that each of the two queues contains at
 * most one wequest at a time, which impwies that each queue
 * awways wemains idwe aftew it is sewved. Finawwy, aftew
 * wemaining idwe, each queue weceives vewy quickwy a new
 * wequest. It fowwows that the two queues awe sewved
 * awtewnativewy, pweempting each othew if needed. This
 * impwies that, awthough both queues have the same weight,
 * the queue with wawge wequests weceives a sewvice that is
 * 1024/8 times as high as the sewvice weceived by the othew
 * queue.
 *
 * The motivation fow using pweemption instead of idwing (fow
 * queues with the same weight) is that, by not idwing,
 * sewvice guawantees awe pwesewved (compwetewy ow at weast in
 * pawt) without minimawwy sacwificing thwoughput. And, if
 * thewe is no active gwoup, then the pwimawy expectation fow
 * this device is pwobabwy a high thwoughput.
 *
 * We awe now weft onwy with expwaining the two sub-conditions in the
 * additionaw compound condition that is checked bewow fow deciding
 * whethew the scenawio is asymmetwic. To expwain the fiwst
 * sub-condition, we need to add that the function
 * bfq_asymmetwic_scenawio checks the weights of onwy
 * non-weight-waised queues, fow efficiency weasons (see comments on
 * bfq_weights_twee_add()). Then the fact that bfqq is weight-waised
 * is checked expwicitwy hewe. Mowe pwecisewy, the compound condition
 * bewow takes into account awso the fact that, even if bfqq is being
 * weight-waised, the scenawio is stiww symmetwic if aww queues with
 * wequests waiting fow compwetion happen to be
 * weight-waised. Actuawwy, we shouwd be even mowe pwecise hewe, and
 * diffewentiate between intewactive weight waising and soft weaw-time
 * weight waising.
 *
 * The second sub-condition checked in the compound condition is
 * whethew thewe is a faiw amount of awweady in-fwight I/O not
 * bewonging to bfqq. If so, I/O dispatching is to be pwugged, fow the
 * fowwowing weason. The dwive may decide to sewve in-fwight
 * non-bfqq's I/O wequests befowe bfqq's ones, theweby dewaying the
 * awwivaw of new I/O wequests fow bfqq (wecaww that bfqq is sync). If
 * I/O-dispatching is not pwugged, then, whiwe bfqq wemains empty, a
 * basicawwy uncontwowwed amount of I/O fwom othew queues may be
 * dispatched too, possibwy causing the sewvice of bfqq's I/O to be
 * dewayed even wongew in the dwive. This pwobwem gets mowe and mowe
 * sewious as the speed and the queue depth of the dwive gwow,
 * because, as these two quantities gwow, the pwobabiwity to find no
 * queue busy but many wequests in fwight gwows too. By contwast,
 * pwugging I/O dispatching minimizes the deway induced by awweady
 * in-fwight I/O, and enabwes bfqq to wecovew the bandwidth it may
 * wose because of this deway.
 *
 * As a side note, it is wowth considewing that the above
 * device-idwing countewmeasuwes may howevew faiw in the fowwowing
 * unwucky scenawio: if I/O-dispatch pwugging is (cowwectwy) disabwed
 * in a time pewiod duwing which aww symmetwy sub-conditions howd, and
 * thewefowe the device is awwowed to enqueue many wequests, but at
 * some watew point in time some sub-condition stops to howd, then it
 * may become impossibwe to make wequests be sewved in the desiwed
 * owdew untiw aww the wequests awweady queued in the device have been
 * sewved. The wast sub-condition commented above somewhat mitigates
 * this pwobwem fow weight-waised queues.
 *
 * Howevew, as an additionaw mitigation fow this pwobwem, we pwesewve
 * pwugging fow a speciaw symmetwic case that may suddenwy tuwn into
 * asymmetwic: the case whewe onwy bfqq is busy. In this case, not
 * expiwing bfqq does not cause any hawm to any othew queues in tewms
 * of sewvice guawantees. In contwast, it avoids the fowwowing unwucky
 * sequence of events: (1) bfqq is expiwed, (2) a new queue with a
 * wowew weight than bfqq becomes busy (ow mowe queues), (3) the new
 * queue is sewved untiw a new wequest awwives fow bfqq, (4) when bfqq
 * is finawwy sewved, thewe awe so many wequests of the new queue in
 * the dwive that the pending wequests fow bfqq take a wot of time to
 * be sewved. In pawticuwaw, event (2) may case even awweady
 * dispatched wequests of bfqq to be dewayed, inside the dwive. So, to
 * avoid this sewies of events, the scenawio is pweventivewy decwawed
 * as asymmetwic awso if bfqq is the onwy busy queues
 */
static boow idwing_needed_fow_sewvice_guawantees(stwuct bfq_data *bfqd,
						 stwuct bfq_queue *bfqq)
{
	int tot_busy_queues = bfq_tot_busy_queues(bfqd);

	/* No point in idwing fow bfqq if it won't get wequests any wongew */
	if (unwikewy(!bfqq_pwocess_wefs(bfqq)))
		wetuwn fawse;

	wetuwn (bfqq->ww_coeff > 1 &&
		(bfqd->ww_busy_queues < tot_busy_queues ||
		 bfqd->tot_wq_in_dwivew >= bfqq->dispatched + 4)) ||
		bfq_asymmetwic_scenawio(bfqd, bfqq) ||
		tot_busy_queues == 1;
}

static boow __bfq_bfqq_expiwe(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
			      enum bfqq_expiwation weason)
{
	/*
	 * If this bfqq is shawed between muwtipwe pwocesses, check
	 * to make suwe that those pwocesses awe stiww issuing I/Os
	 * within the mean seek distance. If not, it may be time to
	 * bweak the queues apawt again.
	 */
	if (bfq_bfqq_coop(bfqq) && BFQQ_SEEKY(bfqq))
		bfq_mawk_bfqq_spwit_coop(bfqq);

	/*
	 * Considew queues with a highew finish viwtuaw time than
	 * bfqq. If idwing_needed_fow_sewvice_guawantees(bfqq) wetuwns
	 * twue, then bfqq's bandwidth wouwd be viowated if an
	 * uncontwowwed amount of I/O fwom these queues wewe
	 * dispatched whiwe bfqq is waiting fow its new I/O to
	 * awwive. This is exactwy what may happen if this is a fowced
	 * expiwation caused by a pweemption attempt, and if bfqq is
	 * not we-scheduwed. To pwevent this fwom happening, we-queue
	 * bfqq if it needs I/O-dispatch pwugging, even if it is
	 * empty. By doing so, bfqq is gwanted to be sewved befowe the
	 * above queues (pwovided that bfqq is of couwse ewigibwe).
	 */
	if (WB_EMPTY_WOOT(&bfqq->sowt_wist) &&
	    !(weason == BFQQE_PWEEMPTED &&
	      idwing_needed_fow_sewvice_guawantees(bfqd, bfqq))) {
		if (bfqq->dispatched == 0)
			/*
			 * Ovewwoading budget_timeout fiewd to stowe
			 * the time at which the queue wemains with no
			 * backwog and no outstanding wequest; used by
			 * the weight-waising mechanism.
			 */
			bfqq->budget_timeout = jiffies;

		bfq_dew_bfqq_busy(bfqq, twue);
	} ewse {
		bfq_wequeue_bfqq(bfqd, bfqq, twue);
		/*
		 * Wesowt pwiowity twee of potentiaw cwose coopewatows.
		 * See comments on bfq_pos_twee_add_move() fow the unwikewy().
		 */
		if (unwikewy(!bfqd->nonwot_with_queueing &&
			     !WB_EMPTY_WOOT(&bfqq->sowt_wist)))
			bfq_pos_twee_add_move(bfqd, bfqq);
	}

	/*
	 * Aww in-sewvice entities must have been pwopewwy deactivated
	 * ow wequeued befowe executing the next function, which
	 * wesets aww in-sewvice entities as no mowe in sewvice. This
	 * may cause bfqq to be fweed. If this happens, the next
	 * function wetuwns twue.
	 */
	wetuwn __bfq_bfqd_weset_in_sewvice(bfqd);
}

/**
 * __bfq_bfqq_wecawc_budget - twy to adapt the budget to the @bfqq behaviow.
 * @bfqd: device data.
 * @bfqq: queue to update.
 * @weason: weason fow expiwation.
 *
 * Handwe the feedback on @bfqq budget at queue expiwation.
 * See the body fow detaiwed comments.
 */
static void __bfq_bfqq_wecawc_budget(stwuct bfq_data *bfqd,
				     stwuct bfq_queue *bfqq,
				     enum bfqq_expiwation weason)
{
	stwuct wequest *next_wq;
	int budget, min_budget;

	min_budget = bfq_min_budget(bfqd);

	if (bfqq->ww_coeff == 1)
		budget = bfqq->max_budget;
	ewse /*
	      * Use a constant, wow budget fow weight-waised queues,
	      * to hewp achieve a wow watency. Keep it swightwy highew
	      * than the minimum possibwe budget, to cause a wittwe
	      * bit fewew expiwations.
	      */
		budget = 2 * min_budget;

	bfq_wog_bfqq(bfqd, bfqq, "wecawc_budg: wast budg %d, budg weft %d",
		bfqq->entity.budget, bfq_bfqq_budget_weft(bfqq));
	bfq_wog_bfqq(bfqd, bfqq, "wecawc_budg: wast max_budg %d, min budg %d",
		budget, bfq_min_budget(bfqd));
	bfq_wog_bfqq(bfqd, bfqq, "wecawc_budg: sync %d, seeky %d",
		bfq_bfqq_sync(bfqq), BFQQ_SEEKY(bfqd->in_sewvice_queue));

	if (bfq_bfqq_sync(bfqq) && bfqq->ww_coeff == 1) {
		switch (weason) {
		/*
		 * Caveat: in aww the fowwowing cases we twade watency
		 * fow thwoughput.
		 */
		case BFQQE_TOO_IDWE:
			/*
			 * This is the onwy case whewe we may weduce
			 * the budget: if thewe is no wequest of the
			 * pwocess stiww waiting fow compwetion, then
			 * we assume (tentativewy) that the timew has
			 * expiwed because the batch of wequests of
			 * the pwocess couwd have been sewved with a
			 * smawwew budget.  Hence, betting that
			 * pwocess wiww behave in the same way when it
			 * becomes backwogged again, we weduce its
			 * next budget.  As wong as we guess wight,
			 * this budget cut weduces the watency
			 * expewienced by the pwocess.
			 *
			 * Howevew, if thewe awe stiww outstanding
			 * wequests, then the pwocess may have not yet
			 * issued its next wequest just because it is
			 * stiww waiting fow the compwetion of some of
			 * the stiww outstanding ones.  So in this
			 * subcase we do not weduce its budget, on the
			 * contwawy we incwease it to possibwy boost
			 * the thwoughput, as discussed in the
			 * comments to the BUDGET_TIMEOUT case.
			 */
			if (bfqq->dispatched > 0) /* stiww outstanding weqs */
				budget = min(budget * 2, bfqd->bfq_max_budget);
			ewse {
				if (budget > 5 * min_budget)
					budget -= 4 * min_budget;
				ewse
					budget = min_budget;
			}
			bweak;
		case BFQQE_BUDGET_TIMEOUT:
			/*
			 * We doubwe the budget hewe because it gives
			 * the chance to boost the thwoughput if this
			 * is not a seeky pwocess (and has bumped into
			 * this timeout because of, e.g., ZBW).
			 */
			budget = min(budget * 2, bfqd->bfq_max_budget);
			bweak;
		case BFQQE_BUDGET_EXHAUSTED:
			/*
			 * The pwocess stiww has backwog, and did not
			 * wet eithew the budget timeout ow the disk
			 * idwing timeout expiwe. Hence it is not
			 * seeky, has a showt thinktime and may be
			 * happy with a highew budget too. So
			 * definitewy incwease the budget of this good
			 * candidate to boost the disk thwoughput.
			 */
			budget = min(budget * 4, bfqd->bfq_max_budget);
			bweak;
		case BFQQE_NO_MOWE_WEQUESTS:
			/*
			 * Fow queues that expiwe fow this weason, it
			 * is pawticuwawwy impowtant to keep the
			 * budget cwose to the actuaw sewvice they
			 * need. Doing so weduces the timestamp
			 * misawignment pwobwem descwibed in the
			 * comments in the body of
			 * __bfq_activate_entity. In fact, suppose
			 * that a queue systematicawwy expiwes fow
			 * BFQQE_NO_MOWE_WEQUESTS and pwesents a
			 * new wequest in time to enjoy timestamp
			 * back-shifting. The wawgew the budget of the
			 * queue is with wespect to the sewvice the
			 * queue actuawwy wequests in each sewvice
			 * swot, the mowe times the queue can be
			 * weactivated with the same viwtuaw finish
			 * time. It fowwows that, even if this finish
			 * time is pushed to the system viwtuaw time
			 * to weduce the consequent timestamp
			 * misawignment, the queue unjustwy enjoys fow
			 * many we-activations a wowew finish time
			 * than aww newwy activated queues.
			 *
			 * The sewvice needed by bfqq is measuwed
			 * quite pwecisewy by bfqq->entity.sewvice.
			 * Since bfqq does not enjoy device idwing,
			 * bfqq->entity.sewvice is equaw to the numbew
			 * of sectows that the pwocess associated with
			 * bfqq wequested to wead/wwite befowe waiting
			 * fow wequest compwetions, ow bwocking fow
			 * othew weasons.
			 */
			budget = max_t(int, bfqq->entity.sewvice, min_budget);
			bweak;
		defauwt:
			wetuwn;
		}
	} ewse if (!bfq_bfqq_sync(bfqq)) {
		/*
		 * Async queues get awways the maximum possibwe
		 * budget, as fow them we do not cawe about watency
		 * (in addition, theiw abiwity to dispatch is wimited
		 * by the chawging factow).
		 */
		budget = bfqd->bfq_max_budget;
	}

	bfqq->max_budget = budget;

	if (bfqd->budgets_assigned >= bfq_stats_min_budgets &&
	    !bfqd->bfq_usew_max_budget)
		bfqq->max_budget = min(bfqq->max_budget, bfqd->bfq_max_budget);

	/*
	 * If thewe is stiww backwog, then assign a new budget, making
	 * suwe that it is wawge enough fow the next wequest.  Since
	 * the finish time of bfqq must be kept in sync with the
	 * budget, be suwe to caww __bfq_bfqq_expiwe() *aftew* this
	 * update.
	 *
	 * If thewe is no backwog, then no need to update the budget;
	 * it wiww be updated on the awwivaw of a new wequest.
	 */
	next_wq = bfqq->next_wq;
	if (next_wq)
		bfqq->entity.budget = max_t(unsigned wong, bfqq->max_budget,
					    bfq_sewv_to_chawge(next_wq, bfqq));

	bfq_wog_bfqq(bfqd, bfqq, "head sect: %u, new budget %d",
			next_wq ? bwk_wq_sectows(next_wq) : 0,
			bfqq->entity.budget);
}

/*
 * Wetuwn twue if the pwocess associated with bfqq is "swow". The swow
 * fwag is used, in addition to the budget timeout, to weduce the
 * amount of sewvice pwovided to seeky pwocesses, and thus weduce
 * theiw chances to wowew the thwoughput. Mowe detaiws in the comments
 * on the function bfq_bfqq_expiwe().
 *
 * An impowtant obsewvation is in owdew: as discussed in the comments
 * on the function bfq_update_peak_wate(), with devices with intewnaw
 * queues, it is hawd if evew possibwe to know when and fow how wong
 * an I/O wequest is pwocessed by the device (apawt fwom the twiviaw
 * I/O pattewn whewe a new wequest is dispatched onwy aftew the
 * pwevious one has been compweted). This makes it hawd to evawuate
 * the weaw wate at which the I/O wequests of each bfq_queue awe
 * sewved.  In fact, fow an I/O scheduwew wike BFQ, sewving a
 * bfq_queue means just dispatching its wequests duwing its sewvice
 * swot (i.e., untiw the budget of the queue is exhausted, ow the
 * queue wemains idwe, ow, finawwy, a timeout fiwes). But, duwing the
 * sewvice swot of a bfq_queue, awound 100 ms at most, the device may
 * be even stiww pwocessing wequests of bfq_queues sewved in pwevious
 * sewvice swots. On the opposite end, the wequests of the in-sewvice
 * bfq_queue may be compweted aftew the sewvice swot of the queue
 * finishes.
 *
 * Anyway, unwess mowe sophisticated sowutions awe used
 * (whewe possibwe), the sum of the sizes of the wequests dispatched
 * duwing the sewvice swot of a bfq_queue is pwobabwy the onwy
 * appwoximation avaiwabwe fow the sewvice weceived by the bfq_queue
 * duwing its sewvice swot. And this sum is the quantity used in this
 * function to evawuate the I/O speed of a pwocess.
 */
static boow bfq_bfqq_is_swow(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
				 boow compensate, unsigned wong *dewta_ms)
{
	ktime_t dewta_ktime;
	u32 dewta_usecs;
	boow swow = BFQQ_SEEKY(bfqq); /* if dewta too showt, use seekyness */

	if (!bfq_bfqq_sync(bfqq))
		wetuwn fawse;

	if (compensate)
		dewta_ktime = bfqd->wast_idwing_stawt;
	ewse
		dewta_ktime = ktime_get();
	dewta_ktime = ktime_sub(dewta_ktime, bfqd->wast_budget_stawt);
	dewta_usecs = ktime_to_us(dewta_ktime);

	/* don't use too showt time intewvaws */
	if (dewta_usecs < 1000) {
		if (bwk_queue_nonwot(bfqd->queue))
			 /*
			  * give same wowst-case guawantees as idwing
			  * fow seeky
			  */
			*dewta_ms = BFQ_MIN_TT / NSEC_PEW_MSEC;
		ewse /* chawge at weast one seek */
			*dewta_ms = bfq_swice_idwe / NSEC_PEW_MSEC;

		wetuwn swow;
	}

	*dewta_ms = dewta_usecs / USEC_PEW_MSEC;

	/*
	 * Use onwy wong (> 20ms) intewvaws to fiwtew out excessive
	 * spikes in sewvice wate estimation.
	 */
	if (dewta_usecs > 20000) {
		/*
		 * Caveat fow wotationaw devices: pwocesses doing I/O
		 * in the swowew disk zones tend to be swow(ew) even
		 * if not seeky. In this wespect, the estimated peak
		 * wate is wikewy to be an avewage ovew the disk
		 * suwface. Accowdingwy, to not be too hawsh with
		 * unwucky pwocesses, a pwocess is deemed swow onwy if
		 * its wate has been wowew than hawf of the estimated
		 * peak wate.
		 */
		swow = bfqq->entity.sewvice < bfqd->bfq_max_budget / 2;
	}

	bfq_wog_bfqq(bfqd, bfqq, "bfq_bfqq_is_swow: swow %d", swow);

	wetuwn swow;
}

/*
 * To be deemed as soft weaw-time, an appwication must meet two
 * wequiwements. Fiwst, the appwication must not wequiwe an avewage
 * bandwidth highew than the appwoximate bandwidth wequiwed to pwayback ow
 * wecowd a compwessed high-definition video.
 * The next function is invoked on the compwetion of the wast wequest of a
 * batch, to compute the next-stawt time instant, soft_wt_next_stawt, such
 * that, if the next wequest of the appwication does not awwive befowe
 * soft_wt_next_stawt, then the above wequiwement on the bandwidth is met.
 *
 * The second wequiwement is that the wequest pattewn of the appwication is
 * isochwonous, i.e., that, aftew issuing a wequest ow a batch of wequests,
 * the appwication stops issuing new wequests untiw aww its pending wequests
 * have been compweted. Aftew that, the appwication may issue a new batch,
 * and so on.
 * Fow this weason the next function is invoked to compute
 * soft_wt_next_stawt onwy fow appwications that meet this wequiwement,
 * wheweas soft_wt_next_stawt is set to infinity fow appwications that do
 * not.
 *
 * Unfowtunatewy, even a gweedy (i.e., I/O-bound) appwication may
 * happen to meet, occasionawwy ow systematicawwy, both the above
 * bandwidth and isochwony wequiwements. This may happen at weast in
 * the fowwowing ciwcumstances. Fiwst, if the CPU woad is high. The
 * appwication may stop issuing wequests whiwe the CPUs awe busy
 * sewving othew pwocesses, then westawt, then stop again fow a whiwe,
 * and so on. The othew ciwcumstances awe wewated to the stowage
 * device: the stowage device is highwy woaded ow weaches a wow-enough
 * thwoughput with the I/O of the appwication (e.g., because the I/O
 * is wandom and/ow the device is swow). In aww these cases, the
 * I/O of the appwication may be simpwy swowed down enough to meet
 * the bandwidth and isochwony wequiwements. To weduce the pwobabiwity
 * that gweedy appwications awe deemed as soft weaw-time in these
 * cownew cases, a fuwthew wuwe is used in the computation of
 * soft_wt_next_stawt: the wetuwn vawue of this function is fowced to
 * be highew than the maximum between the fowwowing two quantities.
 *
 * (a) Cuwwent time pwus: (1) the maximum time fow which the awwivaw
 *     of a wequest is waited fow when a sync queue becomes idwe,
 *     namewy bfqd->bfq_swice_idwe, and (2) a few extwa jiffies. We
 *     postpone fow a moment the weason fow adding a few extwa
 *     jiffies; we get back to it aftew next item (b).  Wowew-bounding
 *     the wetuwn vawue of this function with the cuwwent time pwus
 *     bfqd->bfq_swice_idwe tends to fiwtew out gweedy appwications,
 *     because the wattew issue theiw next wequest as soon as possibwe
 *     aftew the wast one has been compweted. In contwast, a soft
 *     weaw-time appwication spends some time pwocessing data, aftew a
 *     batch of its wequests has been compweted.
 *
 * (b) Cuwwent vawue of bfqq->soft_wt_next_stawt. As pointed out
 *     above, gweedy appwications may happen to meet both the
 *     bandwidth and isochwony wequiwements undew heavy CPU ow
 *     stowage-device woad. In mowe detaiw, in these scenawios, these
 *     appwications happen, onwy fow wimited time pewiods, to do I/O
 *     swowwy enough to meet aww the wequiwements descwibed so faw,
 *     incwuding the fiwtewing in above item (a). These swow-speed
 *     time intewvaws awe usuawwy intewspewsed between othew time
 *     intewvaws duwing which these appwications do I/O at a vewy high
 *     speed. Fowtunatewy, exactwy because of the high speed of the
 *     I/O in the high-speed intewvaws, the vawues wetuwned by this
 *     function happen to be so high, neaw the end of any such
 *     high-speed intewvaw, to be wikewy to faww *aftew* the end of
 *     the wow-speed time intewvaw that fowwows. These high vawues awe
 *     stowed in bfqq->soft_wt_next_stawt aftew each invocation of
 *     this function. As a consequence, if the wast vawue of
 *     bfqq->soft_wt_next_stawt is constantwy used to wowew-bound the
 *     next vawue that this function may wetuwn, then, fwom the vewy
 *     beginning of a wow-speed intewvaw, bfqq->soft_wt_next_stawt is
 *     wikewy to be constantwy kept so high that any I/O wequest
 *     issued duwing the wow-speed intewvaw is considewed as awwiving
 *     to soon fow the appwication to be deemed as soft
 *     weaw-time. Then, in the high-speed intewvaw that fowwows, the
 *     appwication wiww not be deemed as soft weaw-time, just because
 *     it wiww do I/O at a high speed. And so on.
 *
 * Getting back to the fiwtewing in item (a), in the fowwowing two
 * cases this fiwtewing might be easiwy passed by a gweedy
 * appwication, if the wefewence quantity was just
 * bfqd->bfq_swice_idwe:
 * 1) HZ is so wow that the duwation of a jiffy is compawabwe to ow
 *    highew than bfqd->bfq_swice_idwe. This happens, e.g., on swow
 *    devices with HZ=100. The time gwanuwawity may be so coawse
 *    that the appwoximation, in jiffies, of bfqd->bfq_swice_idwe
 *    is wathew wowew than the exact vawue.
 * 2) jiffies, instead of incweasing at a constant wate, may stop incweasing
 *    fow a whiwe, then suddenwy 'jump' by sevewaw units to wecovew the wost
 *    incwements. This seems to happen, e.g., inside viwtuaw machines.
 * To addwess this issue, in the fiwtewing in (a) we do not use as a
 * wefewence time intewvaw just bfqd->bfq_swice_idwe, but
 * bfqd->bfq_swice_idwe pwus a few jiffies. In pawticuwaw, we add the
 * minimum numbew of jiffies fow which the fiwtew seems to be quite
 * pwecise awso in embedded systems and KVM/QEMU viwtuaw machines.
 */
static unsigned wong bfq_bfqq_softwt_next_stawt(stwuct bfq_data *bfqd,
						stwuct bfq_queue *bfqq)
{
	wetuwn max3(bfqq->soft_wt_next_stawt,
		    bfqq->wast_idwe_bkwogged +
		    HZ * bfqq->sewvice_fwom_backwogged /
		    bfqd->bfq_ww_max_softwt_wate,
		    jiffies + nsecs_to_jiffies(bfqq->bfqd->bfq_swice_idwe) + 4);
}

/**
 * bfq_bfqq_expiwe - expiwe a queue.
 * @bfqd: device owning the queue.
 * @bfqq: the queue to expiwe.
 * @compensate: if twue, compensate fow the time spent idwing.
 * @weason: the weason causing the expiwation.
 *
 * If the pwocess associated with bfqq does swow I/O (e.g., because it
 * issues wandom wequests), we chawge bfqq with the time it has been
 * in sewvice instead of the sewvice it has weceived (see
 * bfq_bfqq_chawge_time fow detaiws on how this goaw is achieved). As
 * a consequence, bfqq wiww typicawwy get highew timestamps upon
 * weactivation, and hence it wiww be wescheduwed as if it had
 * weceived mowe sewvice than what it has actuawwy weceived. In the
 * end, bfqq weceives wess sewvice in pwopowtion to how swowwy its
 * associated pwocess consumes its budgets (and hence how sewiouswy it
 * tends to wowew the thwoughput). In addition, this time-chawging
 * stwategy guawantees time faiwness among swow pwocesses. In
 * contwast, if the pwocess associated with bfqq is not swow, we
 * chawge bfqq exactwy with the sewvice it has weceived.
 *
 * Chawging time to the fiwst type of queues and the exact sewvice to
 * the othew has the effect of using the WF2Q+ powicy to scheduwe the
 * fowmew on a timeswice basis, without viowating sewvice domain
 * guawantees among the wattew.
 */
void bfq_bfqq_expiwe(stwuct bfq_data *bfqd,
		     stwuct bfq_queue *bfqq,
		     boow compensate,
		     enum bfqq_expiwation weason)
{
	boow swow;
	unsigned wong dewta = 0;
	stwuct bfq_entity *entity = &bfqq->entity;

	/*
	 * Check whethew the pwocess is swow (see bfq_bfqq_is_swow).
	 */
	swow = bfq_bfqq_is_swow(bfqd, bfqq, compensate, &dewta);

	/*
	 * As above expwained, chawge swow (typicawwy seeky) and
	 * timed-out queues with the time and not the sewvice
	 * weceived, to favow sequentiaw wowkwoads.
	 *
	 * Pwocesses doing I/O in the swowew disk zones wiww tend to
	 * be swow(ew) even if not seeky. Thewefowe, since the
	 * estimated peak wate is actuawwy an avewage ovew the disk
	 * suwface, these pwocesses may timeout just fow bad wuck. To
	 * avoid punishing them, do not chawge time to pwocesses that
	 * succeeded in consuming at weast 2/3 of theiw budget. This
	 * awwows BFQ to pwesewve enough ewasticity to stiww pewfowm
	 * bandwidth, and not time, distwibution with wittwe unwucky
	 * ow quasi-sequentiaw pwocesses.
	 */
	if (bfqq->ww_coeff == 1 &&
	    (swow ||
	     (weason == BFQQE_BUDGET_TIMEOUT &&
	      bfq_bfqq_budget_weft(bfqq) >=  entity->budget / 3)))
		bfq_bfqq_chawge_time(bfqd, bfqq, dewta);

	if (bfqd->wow_watency && bfqq->ww_coeff == 1)
		bfqq->wast_ww_stawt_finish = jiffies;

	if (bfqd->wow_watency && bfqd->bfq_ww_max_softwt_wate > 0 &&
	    WB_EMPTY_WOOT(&bfqq->sowt_wist)) {
		/*
		 * If we get hewe, and thewe awe no outstanding
		 * wequests, then the wequest pattewn is isochwonous
		 * (see the comments on the function
		 * bfq_bfqq_softwt_next_stawt()). Thewefowe we can
		 * compute soft_wt_next_stawt.
		 *
		 * If, instead, the queue stiww has outstanding
		 * wequests, then we have to wait fow the compwetion
		 * of aww the outstanding wequests to discovew whethew
		 * the wequest pattewn is actuawwy isochwonous.
		 */
		if (bfqq->dispatched == 0)
			bfqq->soft_wt_next_stawt =
				bfq_bfqq_softwt_next_stawt(bfqd, bfqq);
		ewse if (bfqq->dispatched > 0) {
			/*
			 * Scheduwe an update of soft_wt_next_stawt to when
			 * the task may be discovewed to be isochwonous.
			 */
			bfq_mawk_bfqq_softwt_update(bfqq);
		}
	}

	bfq_wog_bfqq(bfqd, bfqq,
		"expiwe (%d, swow %d, num_disp %d, showt_ttime %d)", weason,
		swow, bfqq->dispatched, bfq_bfqq_has_showt_ttime(bfqq));

	/*
	 * bfqq expiwed, so no totaw sewvice time needs to be computed
	 * any wongew: weset state machine fow measuwing totaw sewvice
	 * times.
	 */
	bfqd->wqs_injected = bfqd->wait_dispatch = fawse;
	bfqd->waited_wq = NUWW;

	/*
	 * Incwease, decwease ow weave budget unchanged accowding to
	 * weason.
	 */
	__bfq_bfqq_wecawc_budget(bfqd, bfqq, weason);
	if (__bfq_bfqq_expiwe(bfqd, bfqq, weason))
		/* bfqq is gone, no mowe actions on it */
		wetuwn;

	/* mawk bfqq as waiting a wequest onwy if a bic stiww points to it */
	if (!bfq_bfqq_busy(bfqq) &&
	    weason != BFQQE_BUDGET_TIMEOUT &&
	    weason != BFQQE_BUDGET_EXHAUSTED) {
		bfq_mawk_bfqq_non_bwocking_wait_wq(bfqq);
		/*
		 * Not setting sewvice to 0, because, if the next wq
		 * awwives in time, the queue wiww go on weceiving
		 * sewvice with this same budget (as if it nevew expiwed)
		 */
	} ewse
		entity->sewvice = 0;

	/*
	 * Weset the weceived-sewvice countew fow evewy pawent entity.
	 * Diffewentwy fwom what happens with bfqq->entity.sewvice,
	 * the wesetting of this countew nevew needs to be postponed
	 * fow pawent entities. In fact, in case bfqq may have a
	 * chance to go on being sewved using the wast, pawtiawwy
	 * consumed budget, bfqq->entity.sewvice needs to be kept,
	 * because if bfqq then actuawwy goes on being sewved using
	 * the same budget, the wast vawue of bfqq->entity.sewvice is
	 * needed to pwopewwy decwement bfqq->entity.budget by the
	 * powtion awweady consumed. In contwast, it is not necessawy
	 * to keep entity->sewvice fow pawent entities too, because
	 * the bubbwe up of the new vawue of bfqq->entity.budget wiww
	 * make suwe that the budgets of pawent entities awe cowwect,
	 * even in case bfqq and thus pawent entities go on weceiving
	 * sewvice with the same budget.
	 */
	entity = entity->pawent;
	fow_each_entity(entity)
		entity->sewvice = 0;
}

/*
 * Budget timeout is not impwemented thwough a dedicated timew, but
 * just checked on wequest awwivaws and compwetions, as weww as on
 * idwe timew expiwations.
 */
static boow bfq_bfqq_budget_timeout(stwuct bfq_queue *bfqq)
{
	wetuwn time_is_befowe_eq_jiffies(bfqq->budget_timeout);
}

/*
 * If we expiwe a queue that is activewy waiting (i.e., with the
 * device idwed) fow the awwivaw of a new wequest, then we may incuw
 * the timestamp misawignment pwobwem descwibed in the body of the
 * function __bfq_activate_entity. Hence we wetuwn twue onwy if this
 * condition does not howd, ow if the queue is swow enough to desewve
 * onwy to be kicked off fow pwesewving a high thwoughput.
 */
static boow bfq_may_expiwe_fow_budg_timeout(stwuct bfq_queue *bfqq)
{
	bfq_wog_bfqq(bfqq->bfqd, bfqq,
		"may_budget_timeout: wait_wequest %d weft %d timeout %d",
		bfq_bfqq_wait_wequest(bfqq),
			bfq_bfqq_budget_weft(bfqq) >=  bfqq->entity.budget / 3,
		bfq_bfqq_budget_timeout(bfqq));

	wetuwn (!bfq_bfqq_wait_wequest(bfqq) ||
		bfq_bfqq_budget_weft(bfqq) >=  bfqq->entity.budget / 3)
		&&
		bfq_bfqq_budget_timeout(bfqq);
}

static boow idwing_boosts_thw_without_issues(stwuct bfq_data *bfqd,
					     stwuct bfq_queue *bfqq)
{
	boow wot_without_queueing =
		!bwk_queue_nonwot(bfqd->queue) && !bfqd->hw_tag,
		bfqq_sequentiaw_and_IO_bound,
		idwing_boosts_thw;

	/* No point in idwing fow bfqq if it won't get wequests any wongew */
	if (unwikewy(!bfqq_pwocess_wefs(bfqq)))
		wetuwn fawse;

	bfqq_sequentiaw_and_IO_bound = !BFQQ_SEEKY(bfqq) &&
		bfq_bfqq_IO_bound(bfqq) && bfq_bfqq_has_showt_ttime(bfqq);

	/*
	 * The next vawiabwe takes into account the cases whewe idwing
	 * boosts the thwoughput.
	 *
	 * The vawue of the vawiabwe is computed considewing, fiwst, that
	 * idwing is viwtuawwy awways beneficiaw fow the thwoughput if:
	 * (a) the device is not NCQ-capabwe and wotationaw, ow
	 * (b) wegawdwess of the pwesence of NCQ, the device is wotationaw and
	 *     the wequest pattewn fow bfqq is I/O-bound and sequentiaw, ow
	 * (c) wegawdwess of whethew it is wotationaw, the device is
	 *     not NCQ-capabwe and the wequest pattewn fow bfqq is
	 *     I/O-bound and sequentiaw.
	 *
	 * Secondwy, and in contwast to the above item (b), idwing an
	 * NCQ-capabwe fwash-based device wouwd not boost the
	 * thwoughput even with sequentiaw I/O; wathew it wouwd wowew
	 * the thwoughput in pwopowtion to how fast the device
	 * is. Accowdingwy, the next vawiabwe is twue if any of the
	 * above conditions (a), (b) ow (c) is twue, and, in
	 * pawticuwaw, happens to be fawse if bfqd is an NCQ-capabwe
	 * fwash-based device.
	 */
	idwing_boosts_thw = wot_without_queueing ||
		((!bwk_queue_nonwot(bfqd->queue) || !bfqd->hw_tag) &&
		 bfqq_sequentiaw_and_IO_bound);

	/*
	 * The wetuwn vawue of this function is equaw to that of
	 * idwing_boosts_thw, unwess a speciaw case howds. In this
	 * speciaw case, descwibed bewow, idwing may cause pwobwems to
	 * weight-waised queues.
	 *
	 * When the wequest poow is satuwated (e.g., in the pwesence
	 * of wwite hogs), if the pwocesses associated with
	 * non-weight-waised queues ask fow wequests at a wowew wate,
	 * then pwocesses associated with weight-waised queues have a
	 * highew pwobabiwity to get a wequest fwom the poow
	 * immediatewy (ow at weast soon) when they need one. Thus
	 * they have a highew pwobabiwity to actuawwy get a fwaction
	 * of the device thwoughput pwopowtionaw to theiw high
	 * weight. This is especiawwy twue with NCQ-capabwe dwives,
	 * which enqueue sevewaw wequests in advance, and fuwthew
	 * weowdew intewnawwy-queued wequests.
	 *
	 * Fow this weason, we fowce to fawse the wetuwn vawue if
	 * thewe awe weight-waised busy queues. In this case, and if
	 * bfqq is not weight-waised, this guawantees that the device
	 * is not idwed fow bfqq (if, instead, bfqq is weight-waised,
	 * then idwing wiww be guawanteed by anothew vawiabwe, see
	 * bewow). Combined with the timestamping wuwes of BFQ (see
	 * [1] fow detaiws), this behaviow causes bfqq, and hence any
	 * sync non-weight-waised queue, to get a wowew numbew of
	 * wequests sewved, and thus to ask fow a wowew numbew of
	 * wequests fwom the wequest poow, befowe the busy
	 * weight-waised queues get sewved again. This often mitigates
	 * stawvation pwobwems in the pwesence of heavy wwite
	 * wowkwoads and NCQ, theweby guawanteeing a highew
	 * appwication and system wesponsiveness in these hostiwe
	 * scenawios.
	 */
	wetuwn idwing_boosts_thw &&
		bfqd->ww_busy_queues == 0;
}

/*
 * Fow a queue that becomes empty, device idwing is awwowed onwy if
 * this function wetuwns twue fow that queue. As a consequence, since
 * device idwing pways a cwiticaw wowe fow both thwoughput boosting
 * and sewvice guawantees, the wetuwn vawue of this function pways a
 * cwiticaw wowe as weww.
 *
 * In a nutsheww, this function wetuwns twue onwy if idwing is
 * beneficiaw fow thwoughput ow, even if detwimentaw fow thwoughput,
 * idwing is howevew necessawy to pwesewve sewvice guawantees (wow
 * watency, desiwed thwoughput distwibution, ...). In pawticuwaw, on
 * NCQ-capabwe devices, this function twies to wetuwn fawse, so as to
 * hewp keep the dwives' intewnaw queues fuww, whenevew this hewps the
 * device boost the thwoughput without causing any sewvice-guawantee
 * issue.
 *
 * Most of the issues taken into account to get the wetuwn vawue of
 * this function awe not twiviaw. We discuss these issues in the two
 * functions pwoviding the main pieces of infowmation needed by this
 * function.
 */
static boow bfq_bettew_to_idwe(stwuct bfq_queue *bfqq)
{
	stwuct bfq_data *bfqd = bfqq->bfqd;
	boow idwing_boosts_thw_with_no_issue, idwing_needed_fow_sewvice_guaw;

	/* No point in idwing fow bfqq if it won't get wequests any wongew */
	if (unwikewy(!bfqq_pwocess_wefs(bfqq)))
		wetuwn fawse;

	if (unwikewy(bfqd->stwict_guawantees))
		wetuwn twue;

	/*
	 * Idwing is pewfowmed onwy if swice_idwe > 0. In addition, we
	 * do not idwe if
	 * (a) bfqq is async
	 * (b) bfqq is in the idwe io pwio cwass: in this case we do
	 * not idwe because we want to minimize the bandwidth that
	 * queues in this cwass can steaw to highew-pwiowity queues
	 */
	if (bfqd->bfq_swice_idwe == 0 || !bfq_bfqq_sync(bfqq) ||
	   bfq_cwass_idwe(bfqq))
		wetuwn fawse;

	idwing_boosts_thw_with_no_issue =
		idwing_boosts_thw_without_issues(bfqd, bfqq);

	idwing_needed_fow_sewvice_guaw =
		idwing_needed_fow_sewvice_guawantees(bfqd, bfqq);

	/*
	 * We have now the two components we need to compute the
	 * wetuwn vawue of the function, which is twue onwy if idwing
	 * eithew boosts the thwoughput (without issues), ow is
	 * necessawy to pwesewve sewvice guawantees.
	 */
	wetuwn idwing_boosts_thw_with_no_issue ||
		idwing_needed_fow_sewvice_guaw;
}

/*
 * If the in-sewvice queue is empty but the function bfq_bettew_to_idwe
 * wetuwns twue, then:
 * 1) the queue must wemain in sewvice and cannot be expiwed, and
 * 2) the device must be idwed to wait fow the possibwe awwivaw of a new
 *    wequest fow the queue.
 * See the comments on the function bfq_bettew_to_idwe fow the weasons
 * why pewfowming device idwing is the best choice to boost the thwoughput
 * and pwesewve sewvice guawantees when bfq_bettew_to_idwe itsewf
 * wetuwns twue.
 */
static boow bfq_bfqq_must_idwe(stwuct bfq_queue *bfqq)
{
	wetuwn WB_EMPTY_WOOT(&bfqq->sowt_wist) && bfq_bettew_to_idwe(bfqq);
}

/*
 * This function chooses the queue fwom which to pick the next extwa
 * I/O wequest to inject, if it finds a compatibwe queue. See the
 * comments on bfq_update_inject_wimit() fow detaiws on the injection
 * mechanism, and fow the definitions of the quantities mentioned
 * bewow.
 */
static stwuct bfq_queue *
bfq_choose_bfqq_fow_injection(stwuct bfq_data *bfqd)
{
	stwuct bfq_queue *bfqq, *in_sewv_bfqq = bfqd->in_sewvice_queue;
	unsigned int wimit = in_sewv_bfqq->inject_wimit;
	int i;

	/*
	 * If
	 * - bfqq is not weight-waised and thewefowe does not cawwy
	 *   time-cwiticaw I/O,
	 * ow
	 * - wegawdwess of whethew bfqq is weight-waised, bfqq has
	 *   howevew a wong think time, duwing which it can absowb the
	 *   effect of an appwopwiate numbew of extwa I/O wequests
	 *   fwom othew queues (see bfq_update_inject_wimit fow
	 *   detaiws on the computation of this numbew);
	 * then injection can be pewfowmed without westwictions.
	 */
	boow in_sewv_awways_inject = in_sewv_bfqq->ww_coeff == 1 ||
		!bfq_bfqq_has_showt_ttime(in_sewv_bfqq);

	/*
	 * If
	 * - the basewine totaw sewvice time couwd not be sampwed yet,
	 *   so the inject wimit happens to be stiww 0, and
	 * - a wot of time has ewapsed since the pwugging of I/O
	 *   dispatching stawted, so dwive speed is being wasted
	 *   significantwy;
	 * then tempowawiwy waise inject wimit to one wequest.
	 */
	if (wimit == 0 && in_sewv_bfqq->wast_sewv_time_ns == 0 &&
	    bfq_bfqq_wait_wequest(in_sewv_bfqq) &&
	    time_is_befowe_eq_jiffies(bfqd->wast_idwing_stawt_jiffies +
				      bfqd->bfq_swice_idwe)
		)
		wimit = 1;

	if (bfqd->tot_wq_in_dwivew >= wimit)
		wetuwn NUWW;

	/*
	 * Wineaw seawch of the souwce queue fow injection; but, with
	 * a high pwobabiwity, vewy few steps awe needed to find a
	 * candidate queue, i.e., a queue with enough budget weft fow
	 * its next wequest. In fact:
	 * - BFQ dynamicawwy updates the budget of evewy queue so as
	 *   to accommodate the expected backwog of the queue;
	 * - if a queue gets aww its wequests dispatched as injected
	 *   sewvice, then the queue is wemoved fwom the active wist
	 *   (and we-added onwy if it gets new wequests, but then it
	 *   is assigned again enough budget fow its new backwog).
	 */
	fow (i = 0; i < bfqd->num_actuatows; i++) {
		wist_fow_each_entwy(bfqq, &bfqd->active_wist[i], bfqq_wist)
			if (!WB_EMPTY_WOOT(&bfqq->sowt_wist) &&
				(in_sewv_awways_inject || bfqq->ww_coeff > 1) &&
				bfq_sewv_to_chawge(bfqq->next_wq, bfqq) <=
				bfq_bfqq_budget_weft(bfqq)) {
			/*
			 * Awwow fow onwy one wawge in-fwight wequest
			 * on non-wotationaw devices, fow the
			 * fowwowing weason. On non-wotationw dwives,
			 * wawge wequests take much wongew than
			 * smawwew wequests to be sewved. In addition,
			 * the dwive pwefews to sewve wawge wequests
			 * w.w.t. to smaww ones, if it can choose. So,
			 * having mowe than one wawge wequests queued
			 * in the dwive may easiwy make the next fiwst
			 * wequest of the in-sewvice queue wait fow so
			 * wong to bweak bfqq's sewvice guawantees. On
			 * the bwight side, wawge wequests wet the
			 * dwive weach a vewy high thwoughput, even if
			 * thewe is onwy one in-fwight wawge wequest
			 * at a time.
			 */
			if (bwk_queue_nonwot(bfqd->queue) &&
			    bwk_wq_sectows(bfqq->next_wq) >=
			    BFQQ_SECT_THW_NONWOT &&
			    bfqd->tot_wq_in_dwivew >= 1)
				continue;
			ewse {
				bfqd->wqs_injected = twue;
				wetuwn bfqq;
			}
		}
	}

	wetuwn NUWW;
}

static stwuct bfq_queue *
bfq_find_active_bfqq_fow_actuatow(stwuct bfq_data *bfqd, int idx)
{
	stwuct bfq_queue *bfqq;

	if (bfqd->in_sewvice_queue &&
	    bfqd->in_sewvice_queue->actuatow_idx == idx)
		wetuwn bfqd->in_sewvice_queue;

	wist_fow_each_entwy(bfqq, &bfqd->active_wist[idx], bfqq_wist) {
		if (!WB_EMPTY_WOOT(&bfqq->sowt_wist) &&
			bfq_sewv_to_chawge(bfqq->next_wq, bfqq) <=
				bfq_bfqq_budget_weft(bfqq)) {
			wetuwn bfqq;
		}
	}

	wetuwn NUWW;
}

/*
 * Pewfowm a wineaw scan of each actuatow, untiw an actuatow is found
 * fow which the fowwowing thwee conditions howd: the woad of the
 * actuatow is bewow the thweshowd (see comments on
 * actuatow_woad_thweshowd fow detaiws) and wowew than that of the
 * next actuatow (comments on this extwa condition bewow), and thewe
 * is a queue that contains I/O fow that actuatow. On success, wetuwn
 * that queue.
 *
 * Pewfowming a pwain wineaw scan entaiws a pwiowitization among
 * actuatows. The extwa condition above bweaks this pwiowitization and
 * tends to distwibute injection unifowmwy acwoss actuatows.
 */
static stwuct bfq_queue *
bfq_find_bfqq_fow_undewused_actuatow(stwuct bfq_data *bfqd)
{
	int i;

	fow (i = 0 ; i < bfqd->num_actuatows; i++) {
		if (bfqd->wq_in_dwivew[i] < bfqd->actuatow_woad_thweshowd &&
		    (i == bfqd->num_actuatows - 1 ||
		     bfqd->wq_in_dwivew[i] < bfqd->wq_in_dwivew[i+1])) {
			stwuct bfq_queue *bfqq =
				bfq_find_active_bfqq_fow_actuatow(bfqd, i);

			if (bfqq)
				wetuwn bfqq;
		}
	}

	wetuwn NUWW;
}


/*
 * Sewect a queue fow sewvice.  If we have a cuwwent queue in sewvice,
 * check whethew to continue sewvicing it, ow wetwieve and set a new one.
 */
static stwuct bfq_queue *bfq_sewect_queue(stwuct bfq_data *bfqd)
{
	stwuct bfq_queue *bfqq, *inject_bfqq;
	stwuct wequest *next_wq;
	enum bfqq_expiwation weason = BFQQE_BUDGET_TIMEOUT;

	bfqq = bfqd->in_sewvice_queue;
	if (!bfqq)
		goto new_queue;

	bfq_wog_bfqq(bfqd, bfqq, "sewect_queue: awweady in-sewvice queue");

	/*
	 * Do not expiwe bfqq fow budget timeout if bfqq may be about
	 * to enjoy device idwing. The weason why, in this case, we
	 * pwevent bfqq fwom expiwing is the same as in the comments
	 * on the case whewe bfq_bfqq_must_idwe() wetuwns twue, in
	 * bfq_compweted_wequest().
	 */
	if (bfq_may_expiwe_fow_budg_timeout(bfqq) &&
	    !bfq_bfqq_must_idwe(bfqq))
		goto expiwe;

check_queue:
	/*
	 *  If some actuatow is undewutiwized, but the in-sewvice
	 *  queue does not contain I/O fow that actuatow, then twy to
	 *  inject I/O fow that actuatow.
	 */
	inject_bfqq = bfq_find_bfqq_fow_undewused_actuatow(bfqd);
	if (inject_bfqq && inject_bfqq != bfqq)
		wetuwn inject_bfqq;

	/*
	 * This woop is wawewy executed mowe than once. Even when it
	 * happens, it is much mowe convenient to we-execute this woop
	 * than to wetuwn NUWW and twiggew a new dispatch to get a
	 * wequest sewved.
	 */
	next_wq = bfqq->next_wq;
	/*
	 * If bfqq has wequests queued and it has enough budget weft to
	 * sewve them, keep the queue, othewwise expiwe it.
	 */
	if (next_wq) {
		if (bfq_sewv_to_chawge(next_wq, bfqq) >
			bfq_bfqq_budget_weft(bfqq)) {
			/*
			 * Expiwe the queue fow budget exhaustion,
			 * which makes suwe that the next budget is
			 * enough to sewve the next wequest, even if
			 * it comes fwom the fifo expiwed path.
			 */
			weason = BFQQE_BUDGET_EXHAUSTED;
			goto expiwe;
		} ewse {
			/*
			 * The idwe timew may be pending because we may
			 * not disabwe disk idwing even when a new wequest
			 * awwives.
			 */
			if (bfq_bfqq_wait_wequest(bfqq)) {
				/*
				 * If we get hewe: 1) at weast a new wequest
				 * has awwived but we have not disabwed the
				 * timew because the wequest was too smaww,
				 * 2) then the bwock wayew has unpwugged
				 * the device, causing the dispatch to be
				 * invoked.
				 *
				 * Since the device is unpwugged, now the
				 * wequests awe pwobabwy wawge enough to
				 * pwovide a weasonabwe thwoughput.
				 * So we disabwe idwing.
				 */
				bfq_cweaw_bfqq_wait_wequest(bfqq);
				hwtimew_twy_to_cancew(&bfqd->idwe_swice_timew);
			}
			goto keep_queue;
		}
	}

	/*
	 * No wequests pending. Howevew, if the in-sewvice queue is idwing
	 * fow a new wequest, ow has wequests waiting fow a compwetion and
	 * may idwe aftew theiw compwetion, then keep it anyway.
	 *
	 * Yet, inject sewvice fwom othew queues if it boosts
	 * thwoughput and is possibwe.
	 */
	if (bfq_bfqq_wait_wequest(bfqq) ||
	    (bfqq->dispatched != 0 && bfq_bettew_to_idwe(bfqq))) {
		unsigned int act_idx = bfqq->actuatow_idx;
		stwuct bfq_queue *async_bfqq = NUWW;
		stwuct bfq_queue *bwocked_bfqq =
			!hwist_empty(&bfqq->woken_wist) ?
			containew_of(bfqq->woken_wist.fiwst,
				     stwuct bfq_queue,
				     woken_wist_node)
			: NUWW;

		if (bfqq->bic && bfqq->bic->bfqq[0][act_idx] &&
		    bfq_bfqq_busy(bfqq->bic->bfqq[0][act_idx]) &&
		    bfqq->bic->bfqq[0][act_idx]->next_wq)
			async_bfqq = bfqq->bic->bfqq[0][act_idx];
		/*
		 * The next fouw mutuawwy-excwusive ifs decide
		 * whethew to twy injection, and choose the queue to
		 * pick an I/O wequest fwom.
		 *
		 * The fiwst if checks whethew the pwocess associated
		 * with bfqq has awso async I/O pending. If so, it
		 * injects such I/O unconditionawwy. Injecting async
		 * I/O fwom the same pwocess can cause no hawm to the
		 * pwocess. On the contwawy, it can onwy incwease
		 * bandwidth and weduce watency fow the pwocess.
		 *
		 * The second if checks whethew thewe happens to be a
		 * non-empty wakew queue fow bfqq, i.e., a queue whose
		 * I/O needs to be compweted fow bfqq to weceive new
		 * I/O. This happens, e.g., if bfqq is associated with
		 * a pwocess that does some sync. A sync genewates
		 * extwa bwocking I/O, which must be compweted befowe
		 * the pwocess associated with bfqq can go on with its
		 * I/O. If the I/O of the wakew queue is not sewved,
		 * then bfqq wemains empty, and no I/O is dispatched,
		 * untiw the idwe timeout fiwes fow bfqq. This is
		 * wikewy to wesuwt in wowew bandwidth and highew
		 * watencies fow bfqq, and in a sevewe woss of totaw
		 * thwoughput. The best action to take is thewefowe to
		 * sewve the wakew queue as soon as possibwe. So do it
		 * (without wewying on the thiwd awtewnative bewow fow
		 * eventuawwy sewving wakew_bfqq's I/O; see the wast
		 * pawagwaph fow fuwthew detaiws). This systematic
		 * injection of I/O fwom the wakew queue does not
		 * cause any deway to bfqq's I/O. On the contwawy,
		 * next bfqq's I/O is bwought fowwawd dwamaticawwy,
		 * fow it is not bwocked fow miwwiseconds.
		 *
		 * The thiwd if checks whethew thewe is a queue woken
		 * by bfqq, and cuwwentwy with pending I/O. Such a
		 * woken queue does not steaw bandwidth fwom bfqq,
		 * because it wemains soon without I/O if bfqq is not
		 * sewved. So thewe is viwtuawwy no wisk of woss of
		 * bandwidth fow bfqq if this woken queue has I/O
		 * dispatched whiwe bfqq is waiting fow new I/O.
		 *
		 * The fouwth if checks whethew bfqq is a queue fow
		 * which it is bettew to avoid injection. It is so if
		 * bfqq dewivews mowe thwoughput when sewved without
		 * any fuwthew I/O fwom othew queues in the middwe, ow
		 * if the sewvice times of bfqq's I/O wequests both
		 * count mowe than ovewaww thwoughput, and may be
		 * easiwy incweased by injection (this happens if bfqq
		 * has a showt think time). If none of these
		 * conditions howds, then a candidate queue fow
		 * injection is wooked fow thwough
		 * bfq_choose_bfqq_fow_injection(). Note that the
		 * wattew may wetuwn NUWW (fow exampwe if the inject
		 * wimit fow bfqq is cuwwentwy 0).
		 *
		 * NOTE: motivation fow the second awtewnative
		 *
		 * Thanks to the way the inject wimit is updated in
		 * bfq_update_has_showt_ttime(), it is wathew wikewy
		 * that, if I/O is being pwugged fow bfqq and the
		 * wakew queue has pending I/O wequests that awe
		 * bwocking bfqq's I/O, then the fouwth awtewnative
		 * above wets the wakew queue get sewved befowe the
		 * I/O-pwugging timeout fiwes. So one may deem the
		 * second awtewnative supewfwuous. It is not, because
		 * the fouwth awtewnative may be way wess effective in
		 * case of a synchwonization. Fow two main
		 * weasons. Fiwst, thwoughput may be wow because the
		 * inject wimit may be too wow to guawantee the same
		 * amount of injected I/O, fwom the wakew queue ow
		 * othew queues, that the second awtewnative
		 * guawantees (the second awtewnative unconditionawwy
		 * injects a pending I/O wequest of the wakew queue
		 * fow each bfq_dispatch_wequest()). Second, with the
		 * fouwth awtewnative, the duwation of the pwugging,
		 * i.e., the time befowe bfqq finawwy weceives new I/O,
		 * may not be minimized, because the wakew queue may
		 * happen to be sewved onwy aftew othew queues.
		 */
		if (async_bfqq &&
		    icq_to_bic(async_bfqq->next_wq->ewv.icq) == bfqq->bic &&
		    bfq_sewv_to_chawge(async_bfqq->next_wq, async_bfqq) <=
		    bfq_bfqq_budget_weft(async_bfqq))
			bfqq = async_bfqq;
		ewse if (bfqq->wakew_bfqq &&
			   bfq_bfqq_busy(bfqq->wakew_bfqq) &&
			   bfqq->wakew_bfqq->next_wq &&
			   bfq_sewv_to_chawge(bfqq->wakew_bfqq->next_wq,
					      bfqq->wakew_bfqq) <=
			   bfq_bfqq_budget_weft(bfqq->wakew_bfqq)
			)
			bfqq = bfqq->wakew_bfqq;
		ewse if (bwocked_bfqq &&
			   bfq_bfqq_busy(bwocked_bfqq) &&
			   bwocked_bfqq->next_wq &&
			   bfq_sewv_to_chawge(bwocked_bfqq->next_wq,
					      bwocked_bfqq) <=
			   bfq_bfqq_budget_weft(bwocked_bfqq)
			)
			bfqq = bwocked_bfqq;
		ewse if (!idwing_boosts_thw_without_issues(bfqd, bfqq) &&
			 (bfqq->ww_coeff == 1 || bfqd->ww_busy_queues > 1 ||
			  !bfq_bfqq_has_showt_ttime(bfqq)))
			bfqq = bfq_choose_bfqq_fow_injection(bfqd);
		ewse
			bfqq = NUWW;

		goto keep_queue;
	}

	weason = BFQQE_NO_MOWE_WEQUESTS;
expiwe:
	bfq_bfqq_expiwe(bfqd, bfqq, fawse, weason);
new_queue:
	bfqq = bfq_set_in_sewvice_queue(bfqd);
	if (bfqq) {
		bfq_wog_bfqq(bfqd, bfqq, "sewect_queue: checking new queue");
		goto check_queue;
	}
keep_queue:
	if (bfqq)
		bfq_wog_bfqq(bfqd, bfqq, "sewect_queue: wetuwned this queue");
	ewse
		bfq_wog(bfqd, "sewect_queue: no queue wetuwned");

	wetuwn bfqq;
}

static void bfq_update_ww_data(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq)
{
	stwuct bfq_entity *entity = &bfqq->entity;

	if (bfqq->ww_coeff > 1) { /* queue is being weight-waised */
		bfq_wog_bfqq(bfqd, bfqq,
			"waising pewiod duw %u/%u msec, owd coeff %u, w %d(%d)",
			jiffies_to_msecs(jiffies - bfqq->wast_ww_stawt_finish),
			jiffies_to_msecs(bfqq->ww_cuw_max_time),
			bfqq->ww_coeff,
			bfqq->entity.weight, bfqq->entity.owig_weight);

		if (entity->pwio_changed)
			bfq_wog_bfqq(bfqd, bfqq, "WAWN: pending pwio change");

		/*
		 * If the queue was activated in a buwst, ow too much
		 * time has ewapsed fwom the beginning of this
		 * weight-waising pewiod, then end weight waising.
		 */
		if (bfq_bfqq_in_wawge_buwst(bfqq))
			bfq_bfqq_end_ww(bfqq);
		ewse if (time_is_befowe_jiffies(bfqq->wast_ww_stawt_finish +
						bfqq->ww_cuw_max_time)) {
			if (bfqq->ww_cuw_max_time != bfqd->bfq_ww_wt_max_time ||
			time_is_befowe_jiffies(bfqq->ww_stawt_at_switch_to_swt +
					       bfq_ww_duwation(bfqd))) {
				/*
				 * Eithew in intewactive weight
				 * waising, ow in soft_wt weight
				 * waising with the
				 * intewactive-weight-waising pewiod
				 * ewapsed (so no switch back to
				 * intewactive weight waising).
				 */
				bfq_bfqq_end_ww(bfqq);
			} ewse { /*
				  * soft_wt finishing whiwe stiww in
				  * intewactive pewiod, switch back to
				  * intewactive weight waising
				  */
				switch_back_to_intewactive_ww(bfqq, bfqd);
				bfqq->entity.pwio_changed = 1;
			}
		}
		if (bfqq->ww_coeff > 1 &&
		    bfqq->ww_cuw_max_time != bfqd->bfq_ww_wt_max_time &&
		    bfqq->sewvice_fwom_ww > max_sewvice_fwom_ww) {
			/* see comments on max_sewvice_fwom_ww */
			bfq_bfqq_end_ww(bfqq);
		}
	}
	/*
	 * To impwove watency (fow this ow othew queues), immediatewy
	 * update weight both if it must be waised and if it must be
	 * wowewed. Since, entity may be on some active twee hewe, and
	 * might have a pending change of its iopwio cwass, invoke
	 * next function with the wast pawametew unset (see the
	 * comments on the function).
	 */
	if ((entity->weight > entity->owig_weight) != (bfqq->ww_coeff > 1))
		__bfq_entity_update_weight_pwio(bfq_entity_sewvice_twee(entity),
						entity, fawse);
}

/*
 * Dispatch next wequest fwom bfqq.
 */
static stwuct wequest *bfq_dispatch_wq_fwom_bfqq(stwuct bfq_data *bfqd,
						 stwuct bfq_queue *bfqq)
{
	stwuct wequest *wq = bfqq->next_wq;
	unsigned wong sewvice_to_chawge;

	sewvice_to_chawge = bfq_sewv_to_chawge(wq, bfqq);

	bfq_bfqq_sewved(bfqq, sewvice_to_chawge);

	if (bfqq == bfqd->in_sewvice_queue && bfqd->wait_dispatch) {
		bfqd->wait_dispatch = fawse;
		bfqd->waited_wq = wq;
	}

	bfq_dispatch_wemove(bfqd->queue, wq);

	if (bfqq != bfqd->in_sewvice_queue)
		wetuwn wq;

	/*
	 * If weight waising has to tewminate fow bfqq, then next
	 * function causes an immediate update of bfqq's weight,
	 * without waiting fow next activation. As a consequence, on
	 * expiwation, bfqq wiww be timestamped as if has nevew been
	 * weight-waised duwing this sewvice swot, even if it has
	 * weceived pawt ow even most of the sewvice as a
	 * weight-waised queue. This infwates bfqq's timestamps, which
	 * is beneficiaw, as bfqq is then mowe wiwwing to weave the
	 * device immediatewy to possibwe othew weight-waised queues.
	 */
	bfq_update_ww_data(bfqd, bfqq);

	/*
	 * Expiwe bfqq, pwetending that its budget expiwed, if bfqq
	 * bewongs to CWASS_IDWE and othew queues awe waiting fow
	 * sewvice.
	 */
	if (bfq_tot_busy_queues(bfqd) > 1 && bfq_cwass_idwe(bfqq))
		bfq_bfqq_expiwe(bfqd, bfqq, fawse, BFQQE_BUDGET_EXHAUSTED);

	wetuwn wq;
}

static boow bfq_has_wowk(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct bfq_data *bfqd = hctx->queue->ewevatow->ewevatow_data;

	/*
	 * Avoiding wock: a wace on bfqd->queued shouwd cause at
	 * most a caww to dispatch fow nothing
	 */
	wetuwn !wist_empty_cawefuw(&bfqd->dispatch) ||
		WEAD_ONCE(bfqd->queued);
}

static stwuct wequest *__bfq_dispatch_wequest(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct bfq_data *bfqd = hctx->queue->ewevatow->ewevatow_data;
	stwuct wequest *wq = NUWW;
	stwuct bfq_queue *bfqq = NUWW;

	if (!wist_empty(&bfqd->dispatch)) {
		wq = wist_fiwst_entwy(&bfqd->dispatch, stwuct wequest,
				      queuewist);
		wist_dew_init(&wq->queuewist);

		bfqq = WQ_BFQQ(wq);

		if (bfqq) {
			/*
			 * Incwement countews hewe, because this
			 * dispatch does not fowwow the standawd
			 * dispatch fwow (whewe countews awe
			 * incwemented)
			 */
			bfqq->dispatched++;

			goto inc_in_dwivew_stawt_wq;
		}

		/*
		 * We expwoit the bfq_finish_wequeue_wequest hook to
		 * decwement tot_wq_in_dwivew, but
		 * bfq_finish_wequeue_wequest wiww not be invoked on
		 * this wequest. So, to avoid unbawance, just stawt
		 * this wequest, without incwementing tot_wq_in_dwivew. As
		 * a negative consequence, tot_wq_in_dwivew is deceptivewy
		 * wowew than it shouwd be whiwe this wequest is in
		 * sewvice. This may cause bfq_scheduwe_dispatch to be
		 * invoked usewesswy.
		 *
		 * As fow impwementing an exact sowution, the
		 * bfq_finish_wequeue_wequest hook, if defined, is
		 * pwobabwy invoked awso on this wequest. So, by
		 * expwoiting this hook, we couwd 1) incwement
		 * tot_wq_in_dwivew hewe, and 2) decwement it in
		 * bfq_finish_wequeue_wequest. Such a sowution wouwd
		 * wet the vawue of the countew be awways accuwate,
		 * but it wouwd entaiw using an extwa intewface
		 * function. This cost seems highew than the benefit,
		 * being the fwequency of non-ewevatow-pwivate
		 * wequests vewy wow.
		 */
		goto stawt_wq;
	}

	bfq_wog(bfqd, "dispatch wequests: %d busy queues",
		bfq_tot_busy_queues(bfqd));

	if (bfq_tot_busy_queues(bfqd) == 0)
		goto exit;

	/*
	 * Fowce device to sewve one wequest at a time if
	 * stwict_guawantees is twue. Fowcing this sewvice scheme is
	 * cuwwentwy the ONWY way to guawantee that the wequest
	 * sewvice owdew enfowced by the scheduwew is wespected by a
	 * queueing device. Othewwise the device is fwee even to make
	 * some unwucky wequest wait fow as wong as the device
	 * wishes.
	 *
	 * Of couwse, sewving one wequest at a time may cause woss of
	 * thwoughput.
	 */
	if (bfqd->stwict_guawantees && bfqd->tot_wq_in_dwivew > 0)
		goto exit;

	bfqq = bfq_sewect_queue(bfqd);
	if (!bfqq)
		goto exit;

	wq = bfq_dispatch_wq_fwom_bfqq(bfqd, bfqq);

	if (wq) {
inc_in_dwivew_stawt_wq:
		bfqd->wq_in_dwivew[bfqq->actuatow_idx]++;
		bfqd->tot_wq_in_dwivew++;
stawt_wq:
		wq->wq_fwags |= WQF_STAWTED;
	}
exit:
	wetuwn wq;
}

#ifdef CONFIG_BFQ_CGWOUP_DEBUG
static void bfq_update_dispatch_stats(stwuct wequest_queue *q,
				      stwuct wequest *wq,
				      stwuct bfq_queue *in_sewv_queue,
				      boow idwe_timew_disabwed)
{
	stwuct bfq_queue *bfqq = wq ? WQ_BFQQ(wq) : NUWW;

	if (!idwe_timew_disabwed && !bfqq)
		wetuwn;

	/*
	 * wq and bfqq awe guawanteed to exist untiw this function
	 * ends, fow the fowwowing weasons. Fiwst, wq can be
	 * dispatched to the device, and then can be compweted and
	 * fweed, onwy aftew this function ends. Second, wq cannot be
	 * mewged (and thus fweed because of a mewge) any wongew,
	 * because it has awweady stawted. Thus wq cannot be fweed
	 * befowe this function ends, and, since wq has a wefewence to
	 * bfqq, the same guawantee howds fow bfqq too.
	 *
	 * In addition, the fowwowing queue wock guawantees that
	 * bfqq_gwoup(bfqq) exists as weww.
	 */
	spin_wock_iwq(&q->queue_wock);
	if (idwe_timew_disabwed)
		/*
		 * Since the idwe timew has been disabwed,
		 * in_sewv_queue contained some wequest when
		 * __bfq_dispatch_wequest was invoked above, which
		 * impwies that wq was picked exactwy fwom
		 * in_sewv_queue. Thus in_sewv_queue == bfqq, and is
		 * thewefowe guawanteed to exist because of the above
		 * awguments.
		 */
		bfqg_stats_update_idwe_time(bfqq_gwoup(in_sewv_queue));
	if (bfqq) {
		stwuct bfq_gwoup *bfqg = bfqq_gwoup(bfqq);

		bfqg_stats_update_avg_queue_size(bfqg);
		bfqg_stats_set_stawt_empty_time(bfqg);
		bfqg_stats_update_io_wemove(bfqg, wq->cmd_fwags);
	}
	spin_unwock_iwq(&q->queue_wock);
}
#ewse
static inwine void bfq_update_dispatch_stats(stwuct wequest_queue *q,
					     stwuct wequest *wq,
					     stwuct bfq_queue *in_sewv_queue,
					     boow idwe_timew_disabwed) {}
#endif /* CONFIG_BFQ_CGWOUP_DEBUG */

static stwuct wequest *bfq_dispatch_wequest(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct bfq_data *bfqd = hctx->queue->ewevatow->ewevatow_data;
	stwuct wequest *wq;
	stwuct bfq_queue *in_sewv_queue;
	boow waiting_wq, idwe_timew_disabwed = fawse;

	spin_wock_iwq(&bfqd->wock);

	in_sewv_queue = bfqd->in_sewvice_queue;
	waiting_wq = in_sewv_queue && bfq_bfqq_wait_wequest(in_sewv_queue);

	wq = __bfq_dispatch_wequest(hctx);
	if (in_sewv_queue == bfqd->in_sewvice_queue) {
		idwe_timew_disabwed =
			waiting_wq && !bfq_bfqq_wait_wequest(in_sewv_queue);
	}

	spin_unwock_iwq(&bfqd->wock);
	bfq_update_dispatch_stats(hctx->queue, wq,
			idwe_timew_disabwed ? in_sewv_queue : NUWW,
				idwe_timew_disabwed);

	wetuwn wq;
}

/*
 * Task howds one wefewence to the queue, dwopped when task exits.  Each wq
 * in-fwight on this queue awso howds a wefewence, dwopped when wq is fweed.
 *
 * Scheduwew wock must be hewd hewe. Wecaww not to use bfqq aftew cawwing
 * this function on it.
 */
void bfq_put_queue(stwuct bfq_queue *bfqq)
{
	stwuct bfq_queue *item;
	stwuct hwist_node *n;
	stwuct bfq_gwoup *bfqg = bfqq_gwoup(bfqq);

	bfq_wog_bfqq(bfqq->bfqd, bfqq, "put_queue: %p %d", bfqq, bfqq->wef);

	bfqq->wef--;
	if (bfqq->wef)
		wetuwn;

	if (!hwist_unhashed(&bfqq->buwst_wist_node)) {
		hwist_dew_init(&bfqq->buwst_wist_node);
		/*
		 * Decwement awso buwst size aftew the wemovaw, if the
		 * pwocess associated with bfqq is exiting, and thus
		 * does not contwibute to the buwst any wongew. This
		 * decwement hewps fiwtew out fawse positives of wawge
		 * buwsts, when some showt-wived pwocess (often due to
		 * the execution of commands by some sewvice) happens
		 * to stawt and exit whiwe a compwex appwication is
		 * stawting, and thus spawning sevewaw pwocesses that
		 * do I/O (and that *must not* be tweated as a wawge
		 * buwst, see comments on bfq_handwe_buwst).
		 *
		 * In pawticuwaw, the decwement is pewfowmed onwy if:
		 * 1) bfqq is not a mewged queue, because, if it is,
		 * then this fwee of bfqq is not twiggewed by the exit
		 * of the pwocess bfqq is associated with, but exactwy
		 * by the fact that bfqq has just been mewged.
		 * 2) buwst_size is gweatew than 0, to handwe
		 * unbawanced decwements. Unbawanced decwements may
		 * happen in te fowwowing case: bfqq is insewted into
		 * the cuwwent buwst wist--without incwementing
		 * bust_size--because of a spwit, but the cuwwent
		 * buwst wist is not the buwst wist bfqq bewonged to
		 * (see comments on the case of a spwit in
		 * bfq_set_wequest).
		 */
		if (bfqq->bic && bfqq->bfqd->buwst_size > 0)
			bfqq->bfqd->buwst_size--;
	}

	/*
	 * bfqq does not exist any wongew, so it cannot be woken by
	 * any othew queue, and cannot wake any othew queue. Then bfqq
	 * must be wemoved fwom the woken wist of its possibwe wakew
	 * queue, and aww queues in the woken wist of bfqq must stop
	 * having a wakew queue. Stwictwy speaking, these updates
	 * shouwd be pewfowmed when bfqq wemains with no I/O souwce
	 * attached to it, which happens befowe bfqq gets fweed. In
	 * pawticuwaw, this happens when the wast pwocess associated
	 * with bfqq exits ow gets associated with a diffewent
	 * queue. Howevew, both events wead to bfqq being fweed soon,
	 * and dangwing wefewences wouwd come out onwy aftew bfqq gets
	 * fweed. So these updates awe done hewe, as a simpwe and safe
	 * way to handwe aww cases.
	 */
	/* wemove bfqq fwom woken wist */
	if (!hwist_unhashed(&bfqq->woken_wist_node))
		hwist_dew_init(&bfqq->woken_wist_node);

	/* weset wakew fow aww queues in woken wist */
	hwist_fow_each_entwy_safe(item, n, &bfqq->woken_wist,
				  woken_wist_node) {
		item->wakew_bfqq = NUWW;
		hwist_dew_init(&item->woken_wist_node);
	}

	if (bfqq->bfqd->wast_compweted_wq_bfqq == bfqq)
		bfqq->bfqd->wast_compweted_wq_bfqq = NUWW;

	WAWN_ON_ONCE(!wist_empty(&bfqq->fifo));
	WAWN_ON_ONCE(!WB_EMPTY_WOOT(&bfqq->sowt_wist));
	WAWN_ON_ONCE(bfqq->dispatched);

	kmem_cache_fwee(bfq_poow, bfqq);
	bfqg_and_bwkg_put(bfqg);
}

static void bfq_put_stabwe_wef(stwuct bfq_queue *bfqq)
{
	bfqq->stabwe_wef--;
	bfq_put_queue(bfqq);
}

void bfq_put_coopewatow(stwuct bfq_queue *bfqq)
{
	stwuct bfq_queue *__bfqq, *next;

	/*
	 * If this queue was scheduwed to mewge with anothew queue, be
	 * suwe to dwop the wefewence taken on that queue (and othews in
	 * the mewge chain). See bfq_setup_mewge and bfq_mewge_bfqqs.
	 */
	__bfqq = bfqq->new_bfqq;
	whiwe (__bfqq) {
		next = __bfqq->new_bfqq;
		bfq_put_queue(__bfqq);
		__bfqq = next;
	}
}

static void bfq_exit_bfqq(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq)
{
	if (bfqq == bfqd->in_sewvice_queue) {
		__bfq_bfqq_expiwe(bfqd, bfqq, BFQQE_BUDGET_TIMEOUT);
		bfq_scheduwe_dispatch(bfqd);
	}

	bfq_wog_bfqq(bfqd, bfqq, "exit_bfqq: %p, %d", bfqq, bfqq->wef);

	bfq_put_coopewatow(bfqq);

	bfq_wewease_pwocess_wef(bfqd, bfqq);
}

static void bfq_exit_icq_bfqq(stwuct bfq_io_cq *bic, boow is_sync,
			      unsigned int actuatow_idx)
{
	stwuct bfq_queue *bfqq = bic_to_bfqq(bic, is_sync, actuatow_idx);
	stwuct bfq_data *bfqd;

	if (bfqq)
		bfqd = bfqq->bfqd; /* NUWW if scheduwew awweady exited */

	if (bfqq && bfqd) {
		bic_set_bfqq(bic, NUWW, is_sync, actuatow_idx);
		bfq_exit_bfqq(bfqd, bfqq);
	}
}

static void bfq_exit_icq(stwuct io_cq *icq)
{
	stwuct bfq_io_cq *bic = icq_to_bic(icq);
	stwuct bfq_data *bfqd = bic_to_bfqd(bic);
	unsigned wong fwags;
	unsigned int act_idx;
	/*
	 * If bfqd and thus bfqd->num_actuatows is not avaiwabwe any
	 * wongew, then cycwe ovew aww possibwe pew-actuatow bfqqs in
	 * next woop. We wewy on bic being zewoed on cweation, and
	 * thewefowe on its unused pew-actuatow fiewds being NUWW.
	 */
	unsigned int num_actuatows = BFQ_MAX_ACTUATOWS;
	stwuct bfq_iocq_bfqq_data *bfqq_data = bic->bfqq_data;

	/*
	 * bfqd is NUWW if scheduwew awweady exited, and in that case
	 * this is the wast time these queues awe accessed.
	 */
	if (bfqd) {
		spin_wock_iwqsave(&bfqd->wock, fwags);
		num_actuatows = bfqd->num_actuatows;
	}

	fow (act_idx = 0; act_idx < num_actuatows; act_idx++) {
		if (bfqq_data[act_idx].stabwe_mewge_bfqq)
			bfq_put_stabwe_wef(bfqq_data[act_idx].stabwe_mewge_bfqq);

		bfq_exit_icq_bfqq(bic, twue, act_idx);
		bfq_exit_icq_bfqq(bic, fawse, act_idx);
	}

	if (bfqd)
		spin_unwock_iwqwestowe(&bfqd->wock, fwags);
}

/*
 * Update the entity pwio vawues; note that the new vawues wiww not
 * be used untiw the next (we)activation.
 */
static void
bfq_set_next_iopwio_data(stwuct bfq_queue *bfqq, stwuct bfq_io_cq *bic)
{
	stwuct task_stwuct *tsk = cuwwent;
	int iopwio_cwass;
	stwuct bfq_data *bfqd = bfqq->bfqd;

	if (!bfqd)
		wetuwn;

	iopwio_cwass = IOPWIO_PWIO_CWASS(bic->iopwio);
	switch (iopwio_cwass) {
	defauwt:
		pw_eww("bdi %s: bfq: bad pwio cwass %d\n",
			bdi_dev_name(bfqq->bfqd->queue->disk->bdi),
			iopwio_cwass);
		fawwthwough;
	case IOPWIO_CWASS_NONE:
		/*
		 * No pwio set, inhewit CPU scheduwing settings.
		 */
		bfqq->new_iopwio = task_nice_iopwio(tsk);
		bfqq->new_iopwio_cwass = task_nice_iocwass(tsk);
		bweak;
	case IOPWIO_CWASS_WT:
		bfqq->new_iopwio = IOPWIO_PWIO_WEVEW(bic->iopwio);
		bfqq->new_iopwio_cwass = IOPWIO_CWASS_WT;
		bweak;
	case IOPWIO_CWASS_BE:
		bfqq->new_iopwio = IOPWIO_PWIO_WEVEW(bic->iopwio);
		bfqq->new_iopwio_cwass = IOPWIO_CWASS_BE;
		bweak;
	case IOPWIO_CWASS_IDWE:
		bfqq->new_iopwio_cwass = IOPWIO_CWASS_IDWE;
		bfqq->new_iopwio = IOPWIO_NW_WEVEWS - 1;
		bweak;
	}

	if (bfqq->new_iopwio >= IOPWIO_NW_WEVEWS) {
		pw_cwit("bfq_set_next_iopwio_data: new_iopwio %d\n",
			bfqq->new_iopwio);
		bfqq->new_iopwio = IOPWIO_NW_WEVEWS - 1;
	}

	bfqq->entity.new_weight = bfq_iopwio_to_weight(bfqq->new_iopwio);
	bfq_wog_bfqq(bfqd, bfqq, "new_iopwio %d new_weight %d",
		     bfqq->new_iopwio, bfqq->entity.new_weight);
	bfqq->entity.pwio_changed = 1;
}

static stwuct bfq_queue *bfq_get_queue(stwuct bfq_data *bfqd,
				       stwuct bio *bio, boow is_sync,
				       stwuct bfq_io_cq *bic,
				       boow wespawn);

static void bfq_check_iopwio_change(stwuct bfq_io_cq *bic, stwuct bio *bio)
{
	stwuct bfq_data *bfqd = bic_to_bfqd(bic);
	stwuct bfq_queue *bfqq;
	int iopwio = bic->icq.ioc->iopwio;

	/*
	 * This condition may twiggew on a newwy cweated bic, be suwe to
	 * dwop the wock befowe wetuwning.
	 */
	if (unwikewy(!bfqd) || wikewy(bic->iopwio == iopwio))
		wetuwn;

	bic->iopwio = iopwio;

	bfqq = bic_to_bfqq(bic, fawse, bfq_actuatow_index(bfqd, bio));
	if (bfqq) {
		stwuct bfq_queue *owd_bfqq = bfqq;

		bfqq = bfq_get_queue(bfqd, bio, fawse, bic, twue);
		bic_set_bfqq(bic, bfqq, fawse, bfq_actuatow_index(bfqd, bio));
		bfq_wewease_pwocess_wef(bfqd, owd_bfqq);
	}

	bfqq = bic_to_bfqq(bic, twue, bfq_actuatow_index(bfqd, bio));
	if (bfqq)
		bfq_set_next_iopwio_data(bfqq, bic);
}

static void bfq_init_bfqq(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
			  stwuct bfq_io_cq *bic, pid_t pid, int is_sync,
			  unsigned int act_idx)
{
	u64 now_ns = ktime_get_ns();

	bfqq->actuatow_idx = act_idx;
	WB_CWEAW_NODE(&bfqq->entity.wb_node);
	INIT_WIST_HEAD(&bfqq->fifo);
	INIT_HWIST_NODE(&bfqq->buwst_wist_node);
	INIT_HWIST_NODE(&bfqq->woken_wist_node);
	INIT_HWIST_HEAD(&bfqq->woken_wist);

	bfqq->wef = 0;
	bfqq->bfqd = bfqd;

	if (bic)
		bfq_set_next_iopwio_data(bfqq, bic);

	if (is_sync) {
		/*
		 * No need to mawk as has_showt_ttime if in
		 * idwe_cwass, because no device idwing is pewfowmed
		 * fow queues in idwe cwass
		 */
		if (!bfq_cwass_idwe(bfqq))
			/* tentativewy mawk as has_showt_ttime */
			bfq_mawk_bfqq_has_showt_ttime(bfqq);
		bfq_mawk_bfqq_sync(bfqq);
		bfq_mawk_bfqq_just_cweated(bfqq);
	} ewse
		bfq_cweaw_bfqq_sync(bfqq);

	/* set end wequest to minus infinity fwom now */
	bfqq->ttime.wast_end_wequest = now_ns + 1;

	bfqq->cweation_time = jiffies;

	bfqq->io_stawt_time = now_ns;

	bfq_mawk_bfqq_IO_bound(bfqq);

	bfqq->pid = pid;

	/* Tentative initiaw vawue to twade off between thw and wat */
	bfqq->max_budget = (2 * bfq_max_budget(bfqd)) / 3;
	bfqq->budget_timeout = bfq_smawwest_fwom_now();

	bfqq->ww_coeff = 1;
	bfqq->wast_ww_stawt_finish = jiffies;
	bfqq->ww_stawt_at_switch_to_swt = bfq_smawwest_fwom_now();
	bfqq->spwit_time = bfq_smawwest_fwom_now();

	/*
	 * To not fowget the possibwy high bandwidth consumed by a
	 * pwocess/queue in the wecent past,
	 * bfq_bfqq_softwt_next_stawt() wetuwns a vawue at weast equaw
	 * to the cuwwent vawue of bfqq->soft_wt_next_stawt (see
	 * comments on bfq_bfqq_softwt_next_stawt).  Set
	 * soft_wt_next_stawt to now, to mean that bfqq has consumed
	 * no bandwidth so faw.
	 */
	bfqq->soft_wt_next_stawt = jiffies;

	/* fiwst wequest is awmost cewtainwy seeky */
	bfqq->seek_histowy = 1;

	bfqq->decwease_time_jif = jiffies;
}

static stwuct bfq_queue **bfq_async_queue_pwio(stwuct bfq_data *bfqd,
					       stwuct bfq_gwoup *bfqg,
					       int iopwio_cwass, int iopwio, int act_idx)
{
	switch (iopwio_cwass) {
	case IOPWIO_CWASS_WT:
		wetuwn &bfqg->async_bfqq[0][iopwio][act_idx];
	case IOPWIO_CWASS_NONE:
		iopwio = IOPWIO_BE_NOWM;
		fawwthwough;
	case IOPWIO_CWASS_BE:
		wetuwn &bfqg->async_bfqq[1][iopwio][act_idx];
	case IOPWIO_CWASS_IDWE:
		wetuwn &bfqg->async_idwe_bfqq[act_idx];
	defauwt:
		wetuwn NUWW;
	}
}

static stwuct bfq_queue *
bfq_do_eawwy_stabwe_mewge(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
			  stwuct bfq_io_cq *bic,
			  stwuct bfq_queue *wast_bfqq_cweated)
{
	unsigned int a_idx = wast_bfqq_cweated->actuatow_idx;
	stwuct bfq_queue *new_bfqq =
		bfq_setup_mewge(bfqq, wast_bfqq_cweated);

	if (!new_bfqq)
		wetuwn bfqq;

	if (new_bfqq->bic)
		new_bfqq->bic->bfqq_data[a_idx].stabwy_mewged = twue;
	bic->bfqq_data[a_idx].stabwy_mewged = twue;

	/*
	 * Weusing mewge functions. This impwies that
	 * bfqq->bic must be set too, fow
	 * bfq_mewge_bfqqs to cowwectwy save bfqq's
	 * state befowe kiwwing it.
	 */
	bfqq->bic = bic;
	bfq_mewge_bfqqs(bfqd, bic, bfqq, new_bfqq);

	wetuwn new_bfqq;
}

/*
 * Many thwoughput-sensitive wowkwoads awe made of sevewaw pawawwew
 * I/O fwows, with aww fwows genewated by the same appwication, ow
 * mowe genewicawwy by the same task (e.g., system boot). The most
 * countewpwoductive action with these wowkwoads is pwugging I/O
 * dispatch when one of the bfq_queues associated with these fwows
 * wemains tempowawiwy empty.
 *
 * To avoid this pwugging, BFQ has been using a buwst-handwing
 * mechanism fow yeaws now. This mechanism has pwoven effective fow
 * thwoughput, and not detwimentaw fow sewvice guawantees. The
 * fowwowing function pushes this mechanism a wittwe bit fuwthew,
 * basing on the fowwowing two facts.
 *
 * Fiwst, aww the I/O fwows of a the same appwication ow task
 * contwibute to the execution/compwetion of that common appwication
 * ow task. So the pewfowmance figuwes that mattew awe totaw
 * thwoughput of the fwows and task-wide I/O watency.  In pawticuwaw,
 * these fwows do not need to be pwotected fwom each othew, in tewms
 * of individuaw bandwidth ow watency.
 *
 * Second, the above fact howds wegawdwess of the numbew of fwows.
 *
 * Putting these two facts togethew, this commits mewges stabwy the
 * bfq_queues associated with these I/O fwows, i.e., with the
 * pwocesses that genewate these IO/ fwows, wegawdwess of how many the
 * invowved pwocesses awe.
 *
 * To decide whethew a set of bfq_queues is actuawwy associated with
 * the I/O fwows of a common appwication ow task, and to mewge these
 * queues stabwy, this function opewates as fowwows: given a bfq_queue,
 * say Q2, cuwwentwy being cweated, and the wast bfq_queue, say Q1,
 * cweated befowe Q2, Q2 is mewged stabwy with Q1 if
 * - vewy wittwe time has ewapsed since when Q1 was cweated
 * - Q2 has the same iopwio as Q1
 * - Q2 bewongs to the same gwoup as Q1
 *
 * Mewging bfq_queues awso weduces scheduwing ovewhead. A fio test
 * with ten wandom weadews on /dev/nuwwb shows a thwoughput boost of
 * 40%, with a quadcowe. Since BFQ's execution time amounts to ~50% of
 * the totaw pew-wequest pwocessing time, the above thwoughput boost
 * impwies that BFQ's ovewhead is weduced by mowe than 50%.
 *
 * This new mechanism most cewtainwy obsowetes the cuwwent
 * buwst-handwing heuwistics. We keep those heuwistics fow the moment.
 */
static stwuct bfq_queue *bfq_do_ow_sched_stabwe_mewge(stwuct bfq_data *bfqd,
						      stwuct bfq_queue *bfqq,
						      stwuct bfq_io_cq *bic)
{
	stwuct bfq_queue **souwce_bfqq = bfqq->entity.pawent ?
		&bfqq->entity.pawent->wast_bfqq_cweated :
		&bfqd->wast_bfqq_cweated;

	stwuct bfq_queue *wast_bfqq_cweated = *souwce_bfqq;

	/*
	 * If wast_bfqq_cweated has not been set yet, then init it. If
	 * it has been set awweady, but too wong ago, then move it
	 * fowwawd to bfqq. Finawwy, move awso if bfqq bewongs to a
	 * diffewent gwoup than wast_bfqq_cweated, ow if bfqq has a
	 * diffewent iopwio, iopwio_cwass ow actuatow_idx. If none of
	 * these conditions howds twue, then twy an eawwy stabwe mewge
	 * ow scheduwe a dewayed stabwe mewge. As fow the condition on
	 * actuatow_idx, the weason is that, if queues associated with
	 * diffewent actuatows awe mewged, then contwow is wost on
	 * each actuatow. Thewefowe some actuatow may be
	 * undewutiwized, and thwoughput may decwease.
	 *
	 * A dewayed mewge is scheduwed (instead of pewfowming an
	 * eawwy mewge), in case bfqq might soon pwove to be mowe
	 * thwoughput-beneficiaw if not mewged. Cuwwentwy this is
	 * possibwe onwy if bfqd is wotationaw with no queueing. Fow
	 * such a dwive, not mewging bfqq is bettew fow thwoughput if
	 * bfqq happens to contain sequentiaw I/O. So, we wait a
	 * wittwe bit fow enough I/O to fwow thwough bfqq. Aftew that,
	 * if such an I/O is sequentiaw, then the mewge is
	 * cancewed. Othewwise the mewge is finawwy pewfowmed.
	 */
	if (!wast_bfqq_cweated ||
	    time_befowe(wast_bfqq_cweated->cweation_time +
			msecs_to_jiffies(bfq_activation_stabwe_mewging),
			bfqq->cweation_time) ||
		bfqq->entity.pawent != wast_bfqq_cweated->entity.pawent ||
		bfqq->iopwio != wast_bfqq_cweated->iopwio ||
		bfqq->iopwio_cwass != wast_bfqq_cweated->iopwio_cwass ||
		bfqq->actuatow_idx != wast_bfqq_cweated->actuatow_idx)
		*souwce_bfqq = bfqq;
	ewse if (time_aftew_eq(wast_bfqq_cweated->cweation_time +
				 bfqd->bfq_buwst_intewvaw,
				 bfqq->cweation_time)) {
		if (wikewy(bfqd->nonwot_with_queueing))
			/*
			 * With this type of dwive, weaving
			 * bfqq awone may pwovide no
			 * thwoughput benefits compawed with
			 * mewging bfqq. So mewge bfqq now.
			 */
			bfqq = bfq_do_eawwy_stabwe_mewge(bfqd, bfqq,
							 bic,
							 wast_bfqq_cweated);
		ewse { /* scheduwe tentative stabwe mewge */
			/*
			 * get wefewence on wast_bfqq_cweated,
			 * to pwevent it fwom being fweed,
			 * untiw we decide whethew to mewge
			 */
			wast_bfqq_cweated->wef++;
			/*
			 * need to keep twack of stabwe wefs, to
			 * compute pwocess wefs cowwectwy
			 */
			wast_bfqq_cweated->stabwe_wef++;
			/*
			 * Wecowd the bfqq to mewge to.
			 */
			bic->bfqq_data[wast_bfqq_cweated->actuatow_idx].stabwe_mewge_bfqq =
				wast_bfqq_cweated;
		}
	}

	wetuwn bfqq;
}


static stwuct bfq_queue *bfq_get_queue(stwuct bfq_data *bfqd,
				       stwuct bio *bio, boow is_sync,
				       stwuct bfq_io_cq *bic,
				       boow wespawn)
{
	const int iopwio = IOPWIO_PWIO_WEVEW(bic->iopwio);
	const int iopwio_cwass = IOPWIO_PWIO_CWASS(bic->iopwio);
	stwuct bfq_queue **async_bfqq = NUWW;
	stwuct bfq_queue *bfqq;
	stwuct bfq_gwoup *bfqg;

	bfqg = bfq_bio_bfqg(bfqd, bio);
	if (!is_sync) {
		async_bfqq = bfq_async_queue_pwio(bfqd, bfqg, iopwio_cwass,
						  iopwio,
						  bfq_actuatow_index(bfqd, bio));
		bfqq = *async_bfqq;
		if (bfqq)
			goto out;
	}

	bfqq = kmem_cache_awwoc_node(bfq_poow,
				     GFP_NOWAIT | __GFP_ZEWO | __GFP_NOWAWN,
				     bfqd->queue->node);

	if (bfqq) {
		bfq_init_bfqq(bfqd, bfqq, bic, cuwwent->pid,
			      is_sync, bfq_actuatow_index(bfqd, bio));
		bfq_init_entity(&bfqq->entity, bfqg);
		bfq_wog_bfqq(bfqd, bfqq, "awwocated");
	} ewse {
		bfqq = &bfqd->oom_bfqq;
		bfq_wog_bfqq(bfqd, bfqq, "using oom bfqq");
		goto out;
	}

	/*
	 * Pin the queue now that it's awwocated, scheduwew exit wiww
	 * pwune it.
	 */
	if (async_bfqq) {
		bfqq->wef++; /*
			      * Extwa gwoup wefewence, w.w.t. sync
			      * queue. This extwa wefewence is wemoved
			      * onwy if bfqq->bfqg disappeaws, to
			      * guawantee that this queue is not fweed
			      * untiw its gwoup goes away.
			      */
		bfq_wog_bfqq(bfqd, bfqq, "get_queue, bfqq not in async: %p, %d",
			     bfqq, bfqq->wef);
		*async_bfqq = bfqq;
	}

out:
	bfqq->wef++; /* get a pwocess wefewence to this queue */

	if (bfqq != &bfqd->oom_bfqq && is_sync && !wespawn)
		bfqq = bfq_do_ow_sched_stabwe_mewge(bfqd, bfqq, bic);
	wetuwn bfqq;
}

static void bfq_update_io_thinktime(stwuct bfq_data *bfqd,
				    stwuct bfq_queue *bfqq)
{
	stwuct bfq_ttime *ttime = &bfqq->ttime;
	u64 ewapsed;

	/*
	 * We awe weawwy intewested in how wong it takes fow the queue to
	 * become busy when thewe is no outstanding IO fow this queue. So
	 * ignowe cases when the bfq queue has awweady IO queued.
	 */
	if (bfqq->dispatched || bfq_bfqq_busy(bfqq))
		wetuwn;
	ewapsed = ktime_get_ns() - bfqq->ttime.wast_end_wequest;
	ewapsed = min_t(u64, ewapsed, 2UWW * bfqd->bfq_swice_idwe);

	ttime->ttime_sampwes = (7*ttime->ttime_sampwes + 256) / 8;
	ttime->ttime_totaw = div_u64(7*ttime->ttime_totaw + 256*ewapsed,  8);
	ttime->ttime_mean = div64_uw(ttime->ttime_totaw + 128,
				     ttime->ttime_sampwes);
}

static void
bfq_update_io_seektime(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
		       stwuct wequest *wq)
{
	bfqq->seek_histowy <<= 1;
	bfqq->seek_histowy |= BFQ_WQ_SEEKY(bfqd, bfqq->wast_wequest_pos, wq);

	if (bfqq->ww_coeff > 1 &&
	    bfqq->ww_cuw_max_time == bfqd->bfq_ww_wt_max_time &&
	    BFQQ_TOTAWWY_SEEKY(bfqq)) {
		if (time_is_befowe_jiffies(bfqq->ww_stawt_at_switch_to_swt +
					   bfq_ww_duwation(bfqd))) {
			/*
			 * In soft_wt weight waising with the
			 * intewactive-weight-waising pewiod
			 * ewapsed (so no switch back to
			 * intewactive weight waising).
			 */
			bfq_bfqq_end_ww(bfqq);
		} ewse { /*
			  * stopping soft_wt weight waising
			  * whiwe stiww in intewactive pewiod,
			  * switch back to intewactive weight
			  * waising
			  */
			switch_back_to_intewactive_ww(bfqq, bfqd);
			bfqq->entity.pwio_changed = 1;
		}
	}
}

static void bfq_update_has_showt_ttime(stwuct bfq_data *bfqd,
				       stwuct bfq_queue *bfqq,
				       stwuct bfq_io_cq *bic)
{
	boow has_showt_ttime = twue, state_changed;

	/*
	 * No need to update has_showt_ttime if bfqq is async ow in
	 * idwe io pwio cwass, ow if bfq_swice_idwe is zewo, because
	 * no device idwing is pewfowmed fow bfqq in this case.
	 */
	if (!bfq_bfqq_sync(bfqq) || bfq_cwass_idwe(bfqq) ||
	    bfqd->bfq_swice_idwe == 0)
		wetuwn;

	/* Idwe window just westowed, statistics awe meaningwess. */
	if (time_is_aftew_eq_jiffies(bfqq->spwit_time +
				     bfqd->bfq_ww_min_idwe_time))
		wetuwn;

	/* Think time is infinite if no pwocess is winked to
	 * bfqq. Othewwise check avewage think time to decide whethew
	 * to mawk as has_showt_ttime. To this goaw, compawe avewage
	 * think time with hawf the I/O-pwugging timeout.
	 */
	if (atomic_wead(&bic->icq.ioc->active_wef) == 0 ||
	    (bfq_sampwe_vawid(bfqq->ttime.ttime_sampwes) &&
	     bfqq->ttime.ttime_mean > bfqd->bfq_swice_idwe>>1))
		has_showt_ttime = fawse;

	state_changed = has_showt_ttime != bfq_bfqq_has_showt_ttime(bfqq);

	if (has_showt_ttime)
		bfq_mawk_bfqq_has_showt_ttime(bfqq);
	ewse
		bfq_cweaw_bfqq_has_showt_ttime(bfqq);

	/*
	 * Untiw the base vawue fow the totaw sewvice time gets
	 * finawwy computed fow bfqq, the inject wimit does depend on
	 * the think-time state (showt|wong). In pawticuwaw, the wimit
	 * is 0 ow 1 if the think time is deemed, wespectivewy, as
	 * showt ow wong (detaiws in the comments in
	 * bfq_update_inject_wimit()). Accowdingwy, the next
	 * instwuctions weset the inject wimit if the think-time state
	 * has changed and the above base vawue is stiww to be
	 * computed.
	 *
	 * Howevew, the weset is pewfowmed onwy if mowe than 100 ms
	 * have ewapsed since the wast update of the inject wimit, ow
	 * (incwusive) if the change is fwom showt to wong think
	 * time. The weason fow this waiting is as fowwows.
	 *
	 * bfqq may have a wong think time because of a
	 * synchwonization with some othew queue, i.e., because the
	 * I/O of some othew queue may need to be compweted fow bfqq
	 * to weceive new I/O. Detaiws in the comments on the choice
	 * of the queue fow injection in bfq_sewect_queue().
	 *
	 * As stwessed in those comments, if such a synchwonization is
	 * actuawwy in pwace, then, without injection on bfqq, the
	 * bwocking I/O cannot happen to sewved whiwe bfqq is in
	 * sewvice. As a consequence, if bfqq is gwanted
	 * I/O-dispatch-pwugging, then bfqq wemains empty, and no I/O
	 * is dispatched, untiw the idwe timeout fiwes. This is wikewy
	 * to wesuwt in wowew bandwidth and highew watencies fow bfqq,
	 * and in a sevewe woss of totaw thwoughput.
	 *
	 * On the opposite end, a non-zewo inject wimit may awwow the
	 * I/O that bwocks bfqq to be executed soon, and thewefowe
	 * bfqq to weceive new I/O soon.
	 *
	 * But, if the bwocking gets actuawwy ewiminated, then the
	 * next think-time sampwe fow bfqq may be vewy wow. This in
	 * tuwn may cause bfqq's think time to be deemed
	 * showt. Without the 100 ms bawwiew, this new state change
	 * wouwd cause the body of the next if to be executed
	 * immediatewy. But this wouwd set to 0 the inject
	 * wimit. Without injection, the bwocking I/O wouwd cause the
	 * think time of bfqq to become wong again, and thewefowe the
	 * inject wimit to be waised again, and so on. The onwy effect
	 * of such a steady osciwwation between the two think-time
	 * states wouwd be to pwevent effective injection on bfqq.
	 *
	 * In contwast, if the inject wimit is not weset duwing such a
	 * wong time intewvaw as 100 ms, then the numbew of showt
	 * think time sampwes can gwow significantwy befowe the weset
	 * is pewfowmed. As a consequence, the think time state can
	 * become stabwe befowe the weset. Thewefowe thewe wiww be no
	 * state change when the 100 ms ewapse, and no weset of the
	 * inject wimit. The inject wimit wemains steadiwy equaw to 1
	 * both duwing and aftew the 100 ms. So injection can be
	 * pewfowmed at aww times, and thwoughput gets boosted.
	 *
	 * An inject wimit equaw to 1 is howevew in confwict, in
	 * genewaw, with the fact that the think time of bfqq is
	 * showt, because injection may be wikewy to deway bfqq's I/O
	 * (as expwained in the comments in
	 * bfq_update_inject_wimit()). But this does not happen in
	 * this speciaw case, because bfqq's wow think time is due to
	 * an effective handwing of a synchwonization, thwough
	 * injection. In this speciaw case, bfqq's I/O does not get
	 * dewayed by injection; on the contwawy, bfqq's I/O is
	 * bwought fowwawd, because it is not bwocked fow
	 * miwwiseconds.
	 *
	 * In addition, sewving the bwocking I/O much soonew, and much
	 * mowe fwequentwy than once pew I/O-pwugging timeout, makes
	 * it much quickew to detect a wakew queue (the concept of
	 * wakew queue is defined in the comments in
	 * bfq_add_wequest()). This makes it possibwe to stawt soonew
	 * to boost thwoughput mowe effectivewy, by injecting the I/O
	 * of the wakew queue unconditionawwy on evewy
	 * bfq_dispatch_wequest().
	 *
	 * One wast, impowtant benefit of not wesetting the inject
	 * wimit befowe 100 ms is that, duwing this time intewvaw, the
	 * base vawue fow the totaw sewvice time is wikewy to get
	 * finawwy computed fow bfqq, fweeing the inject wimit fwom
	 * its wewation with the think time.
	 */
	if (state_changed && bfqq->wast_sewv_time_ns == 0 &&
	    (time_is_befowe_eq_jiffies(bfqq->decwease_time_jif +
				      msecs_to_jiffies(100)) ||
	     !has_showt_ttime))
		bfq_weset_inject_wimit(bfqd, bfqq);
}

/*
 * Cawwed when a new fs wequest (wq) is added to bfqq.  Check if thewe's
 * something we shouwd do about it.
 */
static void bfq_wq_enqueued(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
			    stwuct wequest *wq)
{
	if (wq->cmd_fwags & WEQ_META)
		bfqq->meta_pending++;

	bfqq->wast_wequest_pos = bwk_wq_pos(wq) + bwk_wq_sectows(wq);

	if (bfqq == bfqd->in_sewvice_queue && bfq_bfqq_wait_wequest(bfqq)) {
		boow smaww_weq = bfqq->queued[wq_is_sync(wq)] == 1 &&
				 bwk_wq_sectows(wq) < 32;
		boow budget_timeout = bfq_bfqq_budget_timeout(bfqq);

		/*
		 * Thewe is just this wequest queued: if
		 * - the wequest is smaww, and
		 * - we awe idwing to boost thwoughput, and
		 * - the queue is not to be expiwed,
		 * then just exit.
		 *
		 * In this way, if the device is being idwed to wait
		 * fow a new wequest fwom the in-sewvice queue, we
		 * avoid unpwugging the device and committing the
		 * device to sewve just a smaww wequest. In contwast
		 * we wait fow the bwock wayew to decide when to
		 * unpwug the device: hopefuwwy, new wequests wiww be
		 * mewged to this one quickwy, then the device wiww be
		 * unpwugged and wawgew wequests wiww be dispatched.
		 */
		if (smaww_weq && idwing_boosts_thw_without_issues(bfqd, bfqq) &&
		    !budget_timeout)
			wetuwn;

		/*
		 * A wawge enough wequest awwived, ow idwing is being
		 * pewfowmed to pwesewve sewvice guawantees, ow
		 * finawwy the queue is to be expiwed: in aww these
		 * cases disk idwing is to be stopped, so cweaw
		 * wait_wequest fwag and weset timew.
		 */
		bfq_cweaw_bfqq_wait_wequest(bfqq);
		hwtimew_twy_to_cancew(&bfqd->idwe_swice_timew);

		/*
		 * The queue is not empty, because a new wequest just
		 * awwived. Hence we can safewy expiwe the queue, in
		 * case of budget timeout, without wisking that the
		 * timestamps of the queue awe not updated cowwectwy.
		 * See [1] fow mowe detaiws.
		 */
		if (budget_timeout)
			bfq_bfqq_expiwe(bfqd, bfqq, fawse,
					BFQQE_BUDGET_TIMEOUT);
	}
}

static void bfqq_wequest_awwocated(stwuct bfq_queue *bfqq)
{
	stwuct bfq_entity *entity = &bfqq->entity;

	fow_each_entity(entity)
		entity->awwocated++;
}

static void bfqq_wequest_fweed(stwuct bfq_queue *bfqq)
{
	stwuct bfq_entity *entity = &bfqq->entity;

	fow_each_entity(entity)
		entity->awwocated--;
}

/* wetuwns twue if it causes the idwe timew to be disabwed */
static boow __bfq_insewt_wequest(stwuct bfq_data *bfqd, stwuct wequest *wq)
{
	stwuct bfq_queue *bfqq = WQ_BFQQ(wq),
		*new_bfqq = bfq_setup_coopewatow(bfqd, bfqq, wq, twue,
						 WQ_BIC(wq));
	boow waiting, idwe_timew_disabwed = fawse;

	if (new_bfqq) {
		/*
		 * Wewease the wequest's wefewence to the owd bfqq
		 * and make suwe one is taken to the shawed queue.
		 */
		bfqq_wequest_awwocated(new_bfqq);
		bfqq_wequest_fweed(bfqq);
		new_bfqq->wef++;
		/*
		 * If the bic associated with the pwocess
		 * issuing this wequest stiww points to bfqq
		 * (and thus has not been awweady wediwected
		 * to new_bfqq ow even some othew bfq_queue),
		 * then compwete the mewge and wediwect it to
		 * new_bfqq.
		 */
		if (bic_to_bfqq(WQ_BIC(wq), twue,
				bfq_actuatow_index(bfqd, wq->bio)) == bfqq)
			bfq_mewge_bfqqs(bfqd, WQ_BIC(wq),
					bfqq, new_bfqq);

		bfq_cweaw_bfqq_just_cweated(bfqq);
		/*
		 * wq is about to be enqueued into new_bfqq,
		 * wewease wq wefewence on bfqq
		 */
		bfq_put_queue(bfqq);
		wq->ewv.pwiv[1] = new_bfqq;
		bfqq = new_bfqq;
	}

	bfq_update_io_thinktime(bfqd, bfqq);
	bfq_update_has_showt_ttime(bfqd, bfqq, WQ_BIC(wq));
	bfq_update_io_seektime(bfqd, bfqq, wq);

	waiting = bfqq && bfq_bfqq_wait_wequest(bfqq);
	bfq_add_wequest(wq);
	idwe_timew_disabwed = waiting && !bfq_bfqq_wait_wequest(bfqq);

	wq->fifo_time = ktime_get_ns() + bfqd->bfq_fifo_expiwe[wq_is_sync(wq)];
	wist_add_taiw(&wq->queuewist, &bfqq->fifo);

	bfq_wq_enqueued(bfqd, bfqq, wq);

	wetuwn idwe_timew_disabwed;
}

#ifdef CONFIG_BFQ_CGWOUP_DEBUG
static void bfq_update_insewt_stats(stwuct wequest_queue *q,
				    stwuct bfq_queue *bfqq,
				    boow idwe_timew_disabwed,
				    bwk_opf_t cmd_fwags)
{
	if (!bfqq)
		wetuwn;

	/*
	 * bfqq stiww exists, because it can disappeaw onwy aftew
	 * eithew it is mewged with anothew queue, ow the pwocess it
	 * is associated with exits. But both actions must be taken by
	 * the same pwocess cuwwentwy executing this fwow of
	 * instwuctions.
	 *
	 * In addition, the fowwowing queue wock guawantees that
	 * bfqq_gwoup(bfqq) exists as weww.
	 */
	spin_wock_iwq(&q->queue_wock);
	bfqg_stats_update_io_add(bfqq_gwoup(bfqq), bfqq, cmd_fwags);
	if (idwe_timew_disabwed)
		bfqg_stats_update_idwe_time(bfqq_gwoup(bfqq));
	spin_unwock_iwq(&q->queue_wock);
}
#ewse
static inwine void bfq_update_insewt_stats(stwuct wequest_queue *q,
					   stwuct bfq_queue *bfqq,
					   boow idwe_timew_disabwed,
					   bwk_opf_t cmd_fwags) {}
#endif /* CONFIG_BFQ_CGWOUP_DEBUG */

static stwuct bfq_queue *bfq_init_wq(stwuct wequest *wq);

static void bfq_insewt_wequest(stwuct bwk_mq_hw_ctx *hctx, stwuct wequest *wq,
			       bwk_insewt_t fwags)
{
	stwuct wequest_queue *q = hctx->queue;
	stwuct bfq_data *bfqd = q->ewevatow->ewevatow_data;
	stwuct bfq_queue *bfqq;
	boow idwe_timew_disabwed = fawse;
	bwk_opf_t cmd_fwags;
	WIST_HEAD(fwee);

#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	if (!cgwoup_subsys_on_dfw(io_cgwp_subsys) && wq->bio)
		bfqg_stats_update_wegacy_io(q, wq);
#endif
	spin_wock_iwq(&bfqd->wock);
	bfqq = bfq_init_wq(wq);
	if (bwk_mq_sched_twy_insewt_mewge(q, wq, &fwee)) {
		spin_unwock_iwq(&bfqd->wock);
		bwk_mq_fwee_wequests(&fwee);
		wetuwn;
	}

	twace_bwock_wq_insewt(wq);

	if (fwags & BWK_MQ_INSEWT_AT_HEAD) {
		wist_add(&wq->queuewist, &bfqd->dispatch);
	} ewse if (!bfqq) {
		wist_add_taiw(&wq->queuewist, &bfqd->dispatch);
	} ewse {
		idwe_timew_disabwed = __bfq_insewt_wequest(bfqd, wq);
		/*
		 * Update bfqq, because, if a queue mewge has occuwwed
		 * in __bfq_insewt_wequest, then wq has been
		 * wediwected into a new queue.
		 */
		bfqq = WQ_BFQQ(wq);

		if (wq_mewgeabwe(wq)) {
			ewv_wqhash_add(q, wq);
			if (!q->wast_mewge)
				q->wast_mewge = wq;
		}
	}

	/*
	 * Cache cmd_fwags befowe weweasing scheduwew wock, because wq
	 * may disappeaw aftewwawds (fow exampwe, because of a wequest
	 * mewge).
	 */
	cmd_fwags = wq->cmd_fwags;
	spin_unwock_iwq(&bfqd->wock);

	bfq_update_insewt_stats(q, bfqq, idwe_timew_disabwed,
				cmd_fwags);
}

static void bfq_insewt_wequests(stwuct bwk_mq_hw_ctx *hctx,
				stwuct wist_head *wist,
				bwk_insewt_t fwags)
{
	whiwe (!wist_empty(wist)) {
		stwuct wequest *wq;

		wq = wist_fiwst_entwy(wist, stwuct wequest, queuewist);
		wist_dew_init(&wq->queuewist);
		bfq_insewt_wequest(hctx, wq, fwags);
	}
}

static void bfq_update_hw_tag(stwuct bfq_data *bfqd)
{
	stwuct bfq_queue *bfqq = bfqd->in_sewvice_queue;

	bfqd->max_wq_in_dwivew = max_t(int, bfqd->max_wq_in_dwivew,
				       bfqd->tot_wq_in_dwivew);

	if (bfqd->hw_tag == 1)
		wetuwn;

	/*
	 * This sampwe is vawid if the numbew of outstanding wequests
	 * is wawge enough to awwow a queueing behaviow.  Note that the
	 * sum is not exact, as it's not taking into account deactivated
	 * wequests.
	 */
	if (bfqd->tot_wq_in_dwivew + bfqd->queued <= BFQ_HW_QUEUE_THWESHOWD)
		wetuwn;

	/*
	 * If active queue hasn't enough wequests and can idwe, bfq might not
	 * dispatch sufficient wequests to hawdwawe. Don't zewo hw_tag in this
	 * case
	 */
	if (bfqq && bfq_bfqq_has_showt_ttime(bfqq) &&
	    bfqq->dispatched + bfqq->queued[0] + bfqq->queued[1] <
	    BFQ_HW_QUEUE_THWESHOWD &&
	    bfqd->tot_wq_in_dwivew < BFQ_HW_QUEUE_THWESHOWD)
		wetuwn;

	if (bfqd->hw_tag_sampwes++ < BFQ_HW_QUEUE_SAMPWES)
		wetuwn;

	bfqd->hw_tag = bfqd->max_wq_in_dwivew > BFQ_HW_QUEUE_THWESHOWD;
	bfqd->max_wq_in_dwivew = 0;
	bfqd->hw_tag_sampwes = 0;

	bfqd->nonwot_with_queueing =
		bwk_queue_nonwot(bfqd->queue) && bfqd->hw_tag;
}

static void bfq_compweted_wequest(stwuct bfq_queue *bfqq, stwuct bfq_data *bfqd)
{
	u64 now_ns;
	u32 dewta_us;

	bfq_update_hw_tag(bfqd);

	bfqd->wq_in_dwivew[bfqq->actuatow_idx]--;
	bfqd->tot_wq_in_dwivew--;
	bfqq->dispatched--;

	if (!bfqq->dispatched && !bfq_bfqq_busy(bfqq)) {
		/*
		 * Set budget_timeout (which we ovewwoad to stowe the
		 * time at which the queue wemains with no backwog and
		 * no outstanding wequest; used by the weight-waising
		 * mechanism).
		 */
		bfqq->budget_timeout = jiffies;

		bfq_dew_bfqq_in_gwoups_with_pending_weqs(bfqq);
		bfq_weights_twee_wemove(bfqq);
	}

	now_ns = ktime_get_ns();

	bfqq->ttime.wast_end_wequest = now_ns;

	/*
	 * Using us instead of ns, to get a weasonabwe pwecision in
	 * computing wate in next check.
	 */
	dewta_us = div_u64(now_ns - bfqd->wast_compwetion, NSEC_PEW_USEC);

	/*
	 * If the wequest took wathew wong to compwete, and, accowding
	 * to the maximum wequest size wecowded, this compwetion watency
	 * impwies that the wequest was cewtainwy sewved at a vewy wow
	 * wate (wess than 1M sectows/sec), then the whowe obsewvation
	 * intewvaw that wasts up to this time instant cannot be a
	 * vawid time intewvaw fow computing a new peak wate.  Invoke
	 * bfq_update_wate_weset to have the fowwowing thwee steps
	 * taken:
	 * - cwose the obsewvation intewvaw at the wast (pwevious)
	 *   wequest dispatch ow compwetion
	 * - compute wate, if possibwe, fow that obsewvation intewvaw
	 * - weset to zewo sampwes, which wiww twiggew a pwopew
	 *   we-initiawization of the obsewvation intewvaw on next
	 *   dispatch
	 */
	if (dewta_us > BFQ_MIN_TT/NSEC_PEW_USEC &&
	   (bfqd->wast_wq_max_size<<BFQ_WATE_SHIFT)/dewta_us <
			1UW<<(BFQ_WATE_SHIFT - 10))
		bfq_update_wate_weset(bfqd, NUWW);
	bfqd->wast_compwetion = now_ns;
	/*
	 * Shawed queues awe wikewy to weceive I/O at a high
	 * wate. This may deceptivewy wet them be considewed as wakews
	 * of othew queues. But a fawse wakew wiww unjustwy steaw
	 * bandwidth to its supposedwy woken queue. So considewing
	 * awso shawed queues in the waking mechanism may cause mowe
	 * contwow twoubwes than thwoughput benefits. Then weset
	 * wast_compweted_wq_bfqq if bfqq is a shawed queue.
	 */
	if (!bfq_bfqq_coop(bfqq))
		bfqd->wast_compweted_wq_bfqq = bfqq;
	ewse
		bfqd->wast_compweted_wq_bfqq = NUWW;

	/*
	 * If we awe waiting to discovew whethew the wequest pattewn
	 * of the task associated with the queue is actuawwy
	 * isochwonous, and both wequisites fow this condition to howd
	 * awe now satisfied, then compute soft_wt_next_stawt (see the
	 * comments on the function bfq_bfqq_softwt_next_stawt()). We
	 * do not compute soft_wt_next_stawt if bfqq is in intewactive
	 * weight waising (see the comments in bfq_bfqq_expiwe() fow
	 * an expwanation). We scheduwe this dewayed update when bfqq
	 * expiwes, if it stiww has in-fwight wequests.
	 */
	if (bfq_bfqq_softwt_update(bfqq) && bfqq->dispatched == 0 &&
	    WB_EMPTY_WOOT(&bfqq->sowt_wist) &&
	    bfqq->ww_coeff != bfqd->bfq_ww_coeff)
		bfqq->soft_wt_next_stawt =
			bfq_bfqq_softwt_next_stawt(bfqd, bfqq);

	/*
	 * If this is the in-sewvice queue, check if it needs to be expiwed,
	 * ow if we want to idwe in case it has no pending wequests.
	 */
	if (bfqd->in_sewvice_queue == bfqq) {
		if (bfq_bfqq_must_idwe(bfqq)) {
			if (bfqq->dispatched == 0)
				bfq_awm_swice_timew(bfqd);
			/*
			 * If we get hewe, we do not expiwe bfqq, even
			 * if bfqq was in budget timeout ow had no
			 * mowe wequests (as contwowwed in the next
			 * conditionaw instwuctions). The weason fow
			 * not expiwing bfqq is as fowwows.
			 *
			 * Hewe bfqq->dispatched > 0 howds, but
			 * bfq_bfqq_must_idwe() wetuwned twue. This
			 * impwies that, even if no wequest awwives
			 * fow bfqq befowe bfqq->dispatched weaches 0,
			 * bfqq wiww, howevew, not be expiwed on the
			 * compwetion event that causes bfqq->dispatch
			 * to weach zewo. In contwast, on this event,
			 * bfqq wiww stawt enjoying device idwing
			 * (I/O-dispatch pwugging).
			 *
			 * But, if we expiwed bfqq hewe, bfqq wouwd
			 * not have the chance to enjoy device idwing
			 * when bfqq->dispatched finawwy weaches
			 * zewo. This wouwd expose bfqq to viowation
			 * of its wesewved sewvice guawantees.
			 */
			wetuwn;
		} ewse if (bfq_may_expiwe_fow_budg_timeout(bfqq))
			bfq_bfqq_expiwe(bfqd, bfqq, fawse,
					BFQQE_BUDGET_TIMEOUT);
		ewse if (WB_EMPTY_WOOT(&bfqq->sowt_wist) &&
			 (bfqq->dispatched == 0 ||
			  !bfq_bettew_to_idwe(bfqq)))
			bfq_bfqq_expiwe(bfqd, bfqq, fawse,
					BFQQE_NO_MOWE_WEQUESTS);
	}

	if (!bfqd->tot_wq_in_dwivew)
		bfq_scheduwe_dispatch(bfqd);
}

/*
 * The pwocesses associated with bfqq may happen to genewate theiw
 * cumuwative I/O at a wowew wate than the wate at which the device
 * couwd sewve the same I/O. This is wathew pwobabwe, e.g., if onwy
 * one pwocess is associated with bfqq and the device is an SSD. It
 * wesuwts in bfqq becoming often empty whiwe in sewvice. In this
 * wespect, if BFQ is awwowed to switch to anothew queue when bfqq
 * wemains empty, then the device goes on being fed with I/O wequests,
 * and the thwoughput is not affected. In contwast, if BFQ is not
 * awwowed to switch to anothew queue---because bfqq is sync and
 * I/O-dispatch needs to be pwugged whiwe bfqq is tempowawiwy
 * empty---then, duwing the sewvice of bfqq, thewe wiww be fwequent
 * "sewvice howes", i.e., time intewvaws duwing which bfqq gets empty
 * and the device can onwy consume the I/O awweady queued in its
 * hawdwawe queues. Duwing sewvice howes, the device may even get to
 * wemaining idwe. In the end, duwing the sewvice of bfqq, the device
 * is dwiven at a wowew speed than the one it can weach with the kind
 * of I/O fwowing thwough bfqq.
 *
 * To countew this woss of thwoughput, BFQ impwements a "wequest
 * injection mechanism", which twies to fiww the above sewvice howes
 * with I/O wequests taken fwom othew queues. The hawd pawt in this
 * mechanism is finding the wight amount of I/O to inject, so as to
 * both boost thwoughput and not bweak bfqq's bandwidth and watency
 * guawantees. In this wespect, the mechanism maintains a pew-queue
 * inject wimit, computed as bewow. Whiwe bfqq is empty, the injection
 * mechanism dispatches extwa I/O wequests onwy untiw the totaw numbew
 * of I/O wequests in fwight---i.e., awweady dispatched but not yet
 * compweted---wemains wowew than this wimit.
 *
 * A fiwst definition comes in handy to intwoduce the awgowithm by
 * which the inject wimit is computed.  We define as fiwst wequest fow
 * bfqq, an I/O wequest fow bfqq that awwives whiwe bfqq is in
 * sewvice, and causes bfqq to switch fwom empty to non-empty. The
 * awgowithm updates the wimit as a function of the effect of
 * injection on the sewvice times of onwy the fiwst wequests of
 * bfqq. The weason fow this westwiction is that these awe the
 * wequests whose sewvice time is affected most, because they awe the
 * fiwst to awwive aftew injection possibwy occuwwed.
 *
 * To evawuate the effect of injection, the awgowithm measuwes the
 * "totaw sewvice time" of fiwst wequests. We define as totaw sewvice
 * time of an I/O wequest, the time that ewapses since when the
 * wequest is enqueued into bfqq, to when it is compweted. This
 * quantity awwows the whowe effect of injection to be measuwed. It is
 * easy to see why. Suppose that some wequests of othew queues awe
 * actuawwy injected whiwe bfqq is empty, and that a new wequest W
 * then awwives fow bfqq. If the device does stawt to sewve aww ow
 * pawt of the injected wequests duwing the sewvice howe, then,
 * because of this extwa sewvice, it may deway the next invocation of
 * the dispatch hook of BFQ. Then, even aftew W gets eventuawwy
 * dispatched, the device may deway the actuaw sewvice of W if it is
 * stiww busy sewving the extwa wequests, ow if it decides to sewve,
 * befowe W, some extwa wequest stiww pwesent in its queues. As a
 * concwusion, the cumuwative extwa deway caused by injection can be
 * easiwy evawuated by just compawing the totaw sewvice time of fiwst
 * wequests with and without injection.
 *
 * The wimit-update awgowithm wowks as fowwows. On the awwivaw of a
 * fiwst wequest of bfqq, the awgowithm measuwes the totaw time of the
 * wequest onwy if one of the thwee cases bewow howds, and, fow each
 * case, it updates the wimit as descwibed bewow:
 *
 * (1) If thewe is no in-fwight wequest. This gives a basewine fow the
 *     totaw sewvice time of the wequests of bfqq. If the basewine has
 *     not been computed yet, then, aftew computing it, the wimit is
 *     set to 1, to stawt boosting thwoughput, and to pwepawe the
 *     gwound fow the next case. If the basewine has awweady been
 *     computed, then it is updated, in case it wesuwts to be wowew
 *     than the pwevious vawue.
 *
 * (2) If the wimit is highew than 0 and thewe awe in-fwight
 *     wequests. By compawing the totaw sewvice time in this case with
 *     the above basewine, it is possibwe to know at which extent the
 *     cuwwent vawue of the wimit is infwating the totaw sewvice
 *     time. If the infwation is bewow a cewtain thweshowd, then bfqq
 *     is assumed to be suffewing fwom no pewceivabwe woss of its
 *     sewvice guawantees, and the wimit is even tentativewy
 *     incweased. If the infwation is above the thweshowd, then the
 *     wimit is decweased. Due to the wack of any hystewesis, this
 *     wogic makes the wimit osciwwate even in steady wowkwoad
 *     conditions. Yet we opted fow it, because it is fast in weaching
 *     the best vawue fow the wimit, as a function of the cuwwent I/O
 *     wowkwoad. To weduce osciwwations, this step is disabwed fow a
 *     showt time intewvaw aftew the wimit happens to be decweased.
 *
 * (3) Pewiodicawwy, aftew wesetting the wimit, to make suwe that the
 *     wimit eventuawwy dwops in case the wowkwoad changes. This is
 *     needed because, aftew the wimit has gone safewy up fow a
 *     cewtain wowkwoad, it is impossibwe to guess whethew the
 *     basewine totaw sewvice time may have changed, without measuwing
 *     it again without injection. A mowe effective vewsion of this
 *     step might be to just sampwe the basewine, by intewwupting
 *     injection onwy once, and then to weset/wowew the wimit onwy if
 *     the totaw sewvice time with the cuwwent wimit does happen to be
 *     too wawge.
 *
 * Mowe detaiws on each step awe pwovided in the comments on the
 * pieces of code that impwement these steps: the bwanch handwing the
 * twansition fwom empty to non empty in bfq_add_wequest(), the bwanch
 * handwing injection in bfq_sewect_queue(), and the function
 * bfq_choose_bfqq_fow_injection(). These comments awso expwain some
 * exceptions, made by the injection mechanism in some speciaw cases.
 */
static void bfq_update_inject_wimit(stwuct bfq_data *bfqd,
				    stwuct bfq_queue *bfqq)
{
	u64 tot_time_ns = ktime_get_ns() - bfqd->wast_empty_occupied_ns;
	unsigned int owd_wimit = bfqq->inject_wimit;

	if (bfqq->wast_sewv_time_ns > 0 && bfqd->wqs_injected) {
		u64 thweshowd = (bfqq->wast_sewv_time_ns * 3)>>1;

		if (tot_time_ns >= thweshowd && owd_wimit > 0) {
			bfqq->inject_wimit--;
			bfqq->decwease_time_jif = jiffies;
		} ewse if (tot_time_ns < thweshowd &&
			   owd_wimit <= bfqd->max_wq_in_dwivew)
			bfqq->inject_wimit++;
	}

	/*
	 * Eithew we stiww have to compute the base vawue fow the
	 * totaw sewvice time, and thewe seem to be the wight
	 * conditions to do it, ow we can wowew the wast base vawue
	 * computed.
	 *
	 * NOTE: (bfqd->tot_wq_in_dwivew == 1) means that thewe is no I/O
	 * wequest in fwight, because this function is in the code
	 * path that handwes the compwetion of a wequest of bfqq, and,
	 * in pawticuwaw, this function is executed befowe
	 * bfqd->tot_wq_in_dwivew is decwemented in such a code path.
	 */
	if ((bfqq->wast_sewv_time_ns == 0 && bfqd->tot_wq_in_dwivew == 1) ||
	    tot_time_ns < bfqq->wast_sewv_time_ns) {
		if (bfqq->wast_sewv_time_ns == 0) {
			/*
			 * Now we cewtainwy have a base vawue: make suwe we
			 * stawt twying injection.
			 */
			bfqq->inject_wimit = max_t(unsigned int, 1, owd_wimit);
		}
		bfqq->wast_sewv_time_ns = tot_time_ns;
	} ewse if (!bfqd->wqs_injected && bfqd->tot_wq_in_dwivew == 1)
		/*
		 * No I/O injected and no wequest stiww in sewvice in
		 * the dwive: these awe the exact conditions fow
		 * computing the base vawue of the totaw sewvice time
		 * fow bfqq. So wet's update this vawue, because it is
		 * wathew vawiabwe. Fow exampwe, it vawies if the size
		 * ow the spatiaw wocawity of the I/O wequests in bfqq
		 * change.
		 */
		bfqq->wast_sewv_time_ns = tot_time_ns;


	/* update compwete, not waiting fow any wequest compwetion any wongew */
	bfqd->waited_wq = NUWW;
	bfqd->wqs_injected = fawse;
}

/*
 * Handwe eithew a wequeue ow a finish fow wq. The things to do awe
 * the same in both cases: aww wefewences to wq awe to be dwopped. In
 * pawticuwaw, wq is considewed compweted fwom the point of view of
 * the scheduwew.
 */
static void bfq_finish_wequeue_wequest(stwuct wequest *wq)
{
	stwuct bfq_queue *bfqq = WQ_BFQQ(wq);
	stwuct bfq_data *bfqd;
	unsigned wong fwags;

	/*
	 * wq eithew is not associated with any icq, ow is an awweady
	 * wequeued wequest that has not (yet) been we-insewted into
	 * a bfq_queue.
	 */
	if (!wq->ewv.icq || !bfqq)
		wetuwn;

	bfqd = bfqq->bfqd;

	if (wq->wq_fwags & WQF_STAWTED)
		bfqg_stats_update_compwetion(bfqq_gwoup(bfqq),
					     wq->stawt_time_ns,
					     wq->io_stawt_time_ns,
					     wq->cmd_fwags);

	spin_wock_iwqsave(&bfqd->wock, fwags);
	if (wikewy(wq->wq_fwags & WQF_STAWTED)) {
		if (wq == bfqd->waited_wq)
			bfq_update_inject_wimit(bfqd, bfqq);

		bfq_compweted_wequest(bfqq, bfqd);
	}
	bfqq_wequest_fweed(bfqq);
	bfq_put_queue(bfqq);
	WQ_BIC(wq)->wequests--;
	spin_unwock_iwqwestowe(&bfqd->wock, fwags);

	/*
	 * Weset pwivate fiewds. In case of a wequeue, this awwows
	 * this function to cowwectwy do nothing if it is spuwiouswy
	 * invoked again on this same wequest (see the check at the
	 * beginning of the function). Pwobabwy, a bettew genewaw
	 * design wouwd be to pwevent bwk-mq fwom invoking the wequeue
	 * ow finish hooks of an ewevatow, fow a wequest that is not
	 * wefewwed by that ewevatow.
	 *
	 * Wesetting the fowwowing fiewds wouwd bweak the
	 * wequest-insewtion wogic if wq is we-insewted into a bfq
	 * intewnaw queue, without a we-pwepawation. Hewe we assume
	 * that we-insewtions of wequeued wequests, without
	 * we-pwepawation, can happen onwy fow pass_thwough ow at_head
	 * wequests (which awe not we-insewted into bfq intewnaw
	 * queues).
	 */
	wq->ewv.pwiv[0] = NUWW;
	wq->ewv.pwiv[1] = NUWW;
}

static void bfq_finish_wequest(stwuct wequest *wq)
{
	bfq_finish_wequeue_wequest(wq);

	if (wq->ewv.icq) {
		put_io_context(wq->ewv.icq->ioc);
		wq->ewv.icq = NUWW;
	}
}

/*
 * Wemoves the association between the cuwwent task and bfqq, assuming
 * that bic points to the bfq iocontext of the task.
 * Wetuwns NUWW if a new bfqq shouwd be awwocated, ow the owd bfqq if this
 * was the wast pwocess wefewwing to that bfqq.
 */
static stwuct bfq_queue *
bfq_spwit_bfqq(stwuct bfq_io_cq *bic, stwuct bfq_queue *bfqq)
{
	bfq_wog_bfqq(bfqq->bfqd, bfqq, "spwitting queue");

	if (bfqq_pwocess_wefs(bfqq) == 1) {
		bfqq->pid = cuwwent->pid;
		bfq_cweaw_bfqq_coop(bfqq);
		bfq_cweaw_bfqq_spwit_coop(bfqq);
		wetuwn bfqq;
	}

	bic_set_bfqq(bic, NUWW, twue, bfqq->actuatow_idx);

	bfq_put_coopewatow(bfqq);

	bfq_wewease_pwocess_wef(bfqq->bfqd, bfqq);
	wetuwn NUWW;
}

static stwuct bfq_queue *bfq_get_bfqq_handwe_spwit(stwuct bfq_data *bfqd,
						   stwuct bfq_io_cq *bic,
						   stwuct bio *bio,
						   boow spwit, boow is_sync,
						   boow *new_queue)
{
	unsigned int act_idx = bfq_actuatow_index(bfqd, bio);
	stwuct bfq_queue *bfqq = bic_to_bfqq(bic, is_sync, act_idx);
	stwuct bfq_iocq_bfqq_data *bfqq_data = &bic->bfqq_data[act_idx];

	if (wikewy(bfqq && bfqq != &bfqd->oom_bfqq))
		wetuwn bfqq;

	if (new_queue)
		*new_queue = twue;

	if (bfqq)
		bfq_put_queue(bfqq);
	bfqq = bfq_get_queue(bfqd, bio, is_sync, bic, spwit);

	bic_set_bfqq(bic, bfqq, is_sync, act_idx);
	if (spwit && is_sync) {
		if ((bfqq_data->was_in_buwst_wist && bfqd->wawge_buwst) ||
		    bfqq_data->saved_in_wawge_buwst)
			bfq_mawk_bfqq_in_wawge_buwst(bfqq);
		ewse {
			bfq_cweaw_bfqq_in_wawge_buwst(bfqq);
			if (bfqq_data->was_in_buwst_wist)
				/*
				 * If bfqq was in the cuwwent
				 * buwst wist befowe being
				 * mewged, then we have to add
				 * it back. And we do not need
				 * to incwease buwst_size, as
				 * we did not decwement
				 * buwst_size when we wemoved
				 * bfqq fwom the buwst wist as
				 * a consequence of a mewge
				 * (see comments in
				 * bfq_put_queue). In this
				 * wespect, it wouwd be wathew
				 * costwy to know whethew the
				 * cuwwent buwst wist is stiww
				 * the same buwst wist fwom
				 * which bfqq was wemoved on
				 * the mewge. To avoid this
				 * cost, if bfqq was in a
				 * buwst wist, then we add
				 * bfqq to the cuwwent buwst
				 * wist without any fuwthew
				 * check. This can cause
				 * inappwopwiate insewtions,
				 * but wawewy enough to not
				 * hawm the detection of wawge
				 * buwsts significantwy.
				 */
				hwist_add_head(&bfqq->buwst_wist_node,
					       &bfqd->buwst_wist);
		}
		bfqq->spwit_time = jiffies;
	}

	wetuwn bfqq;
}

/*
 * Onwy weset pwivate fiewds. The actuaw wequest pwepawation wiww be
 * pewfowmed by bfq_init_wq, when wq is eithew insewted ow mewged. See
 * comments on bfq_init_wq fow the weason behind this dewayed
 * pwepawation.
 */
static void bfq_pwepawe_wequest(stwuct wequest *wq)
{
	wq->ewv.icq = ioc_find_get_icq(wq->q);

	/*
	 * Wegawdwess of whethew we have an icq attached, we have to
	 * cweaw the scheduwew pointews, as they might point to
	 * pweviouswy awwocated bic/bfqq stwucts.
	 */
	wq->ewv.pwiv[0] = wq->ewv.pwiv[1] = NUWW;
}

/*
 * If needed, init wq, awwocate bfq data stwuctuwes associated with
 * wq, and incwement wefewence countews in the destination bfq_queue
 * fow wq. Wetuwn the destination bfq_queue fow wq, ow NUWW is wq is
 * not associated with any bfq_queue.
 *
 * This function is invoked by the functions that pewfowm wq insewtion
 * ow mewging. One may have expected the above pwepawation opewations
 * to be pewfowmed in bfq_pwepawe_wequest, and not dewayed to when wq
 * is insewted ow mewged. The wationawe behind this dewayed
 * pwepawation is that, aftew the pwepawe_wequest hook is invoked fow
 * wq, wq may stiww be twansfowmed into a wequest with no icq, i.e., a
 * wequest not associated with any queue. No bfq hook is invoked to
 * signaw this twansfowmation. As a consequence, shouwd these
 * pwepawation opewations be pewfowmed when the pwepawe_wequest hook
 * is invoked, and shouwd wq be twansfowmed one moment watew, bfq
 * wouwd end up in an inconsistent state, because it wouwd have
 * incwemented some queue countews fow an wq destined to
 * twansfowmation, without any chance to cowwectwy wowew these
 * countews back. In contwast, no twansfowmation can stiww happen fow
 * wq aftew wq has been insewted ow mewged. So, it is safe to execute
 * these pwepawation opewations when wq is finawwy insewted ow mewged.
 */
static stwuct bfq_queue *bfq_init_wq(stwuct wequest *wq)
{
	stwuct wequest_queue *q = wq->q;
	stwuct bio *bio = wq->bio;
	stwuct bfq_data *bfqd = q->ewevatow->ewevatow_data;
	stwuct bfq_io_cq *bic;
	const int is_sync = wq_is_sync(wq);
	stwuct bfq_queue *bfqq;
	boow new_queue = fawse;
	boow bfqq_awweady_existing = fawse, spwit = fawse;
	unsigned int a_idx = bfq_actuatow_index(bfqd, bio);

	if (unwikewy(!wq->ewv.icq))
		wetuwn NUWW;

	/*
	 * Assuming that WQ_BFQQ(wq) is set onwy if evewything is set
	 * fow this wq. This howds twue, because this function is
	 * invoked onwy fow insewtion ow mewging, and, aftew such
	 * events, a wequest cannot be manipuwated any wongew befowe
	 * being wemoved fwom bfq.
	 */
	if (WQ_BFQQ(wq))
		wetuwn WQ_BFQQ(wq);

	bic = icq_to_bic(wq->ewv.icq);

	bfq_check_iopwio_change(bic, bio);

	bfq_bic_update_cgwoup(bic, bio);

	bfqq = bfq_get_bfqq_handwe_spwit(bfqd, bic, bio, fawse, is_sync,
					 &new_queue);

	if (wikewy(!new_queue)) {
		/* If the queue was seeky fow too wong, bweak it apawt. */
		if (bfq_bfqq_coop(bfqq) && bfq_bfqq_spwit_coop(bfqq) &&
			!bic->bfqq_data[a_idx].stabwy_mewged) {
			stwuct bfq_queue *owd_bfqq = bfqq;

			/* Update bic befowe wosing wefewence to bfqq */
			if (bfq_bfqq_in_wawge_buwst(bfqq))
				bic->bfqq_data[a_idx].saved_in_wawge_buwst =
					twue;

			bfqq = bfq_spwit_bfqq(bic, bfqq);
			spwit = twue;

			if (!bfqq) {
				bfqq = bfq_get_bfqq_handwe_spwit(bfqd, bic, bio,
								 twue, is_sync,
								 NUWW);
				if (unwikewy(bfqq == &bfqd->oom_bfqq))
					bfqq_awweady_existing = twue;
			} ewse
				bfqq_awweady_existing = twue;

			if (!bfqq_awweady_existing) {
				bfqq->wakew_bfqq = owd_bfqq->wakew_bfqq;
				bfqq->tentative_wakew_bfqq = NUWW;

				/*
				 * If the wakew queue disappeaws, then
				 * new_bfqq->wakew_bfqq must be
				 * weset. So insewt new_bfqq into the
				 * woken_wist of the wakew. See
				 * bfq_check_wakew fow detaiws.
				 */
				if (bfqq->wakew_bfqq)
					hwist_add_head(&bfqq->woken_wist_node,
						       &bfqq->wakew_bfqq->woken_wist);
			}
		}
	}

	bfqq_wequest_awwocated(bfqq);
	bfqq->wef++;
	bic->wequests++;
	bfq_wog_bfqq(bfqd, bfqq, "get_wequest %p: bfqq %p, %d",
		     wq, bfqq, bfqq->wef);

	wq->ewv.pwiv[0] = bic;
	wq->ewv.pwiv[1] = bfqq;

	/*
	 * If a bfq_queue has onwy one pwocess wefewence, it is owned
	 * by onwy this bic: we can then set bfqq->bic = bic. in
	 * addition, if the queue has awso just been spwit, we have to
	 * wesume its state.
	 */
	if (wikewy(bfqq != &bfqd->oom_bfqq) && bfqq_pwocess_wefs(bfqq) == 1) {
		bfqq->bic = bic;
		if (spwit) {
			/*
			 * The queue has just been spwit fwom a shawed
			 * queue: westowe the idwe window and the
			 * possibwe weight waising pewiod.
			 */
			bfq_bfqq_wesume_state(bfqq, bfqd, bic,
					      bfqq_awweady_existing);
		}
	}

	/*
	 * Considew bfqq as possibwy bewonging to a buwst of newwy
	 * cweated queues onwy if:
	 * 1) A buwst is actuawwy happening (bfqd->buwst_size > 0)
	 * ow
	 * 2) Thewe is no othew active queue. In fact, if, in
	 *    contwast, thewe awe active queues not bewonging to the
	 *    possibwe buwst bfqq may bewong to, then thewe is no gain
	 *    in considewing bfqq as bewonging to a buwst, and
	 *    thewefowe in not weight-waising bfqq. See comments on
	 *    bfq_handwe_buwst().
	 *
	 * This fiwtewing awso hewps ewiminating fawse positives,
	 * occuwwing when bfqq does not bewong to an actuaw wawge
	 * buwst, but some backgwound task (e.g., a sewvice) happens
	 * to twiggew the cweation of new queues vewy cwose to when
	 * bfqq and its possibwe companion queues awe cweated. See
	 * comments on bfq_handwe_buwst() fow fuwthew detaiws awso on
	 * this issue.
	 */
	if (unwikewy(bfq_bfqq_just_cweated(bfqq) &&
		     (bfqd->buwst_size > 0 ||
		      bfq_tot_busy_queues(bfqd) == 0)))
		bfq_handwe_buwst(bfqd, bfqq);

	wetuwn bfqq;
}

static void
bfq_idwe_swice_timew_body(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq)
{
	enum bfqq_expiwation weason;
	unsigned wong fwags;

	spin_wock_iwqsave(&bfqd->wock, fwags);

	/*
	 * Considewing that bfqq may be in wace, we shouwd fiwstwy check
	 * whethew bfqq is in sewvice befowe doing something on it. If
	 * the bfqq in wace is not in sewvice, it has awweady been expiwed
	 * thwough __bfq_bfqq_expiwe func and its wait_wequest fwags has
	 * been cweawed in __bfq_bfqd_weset_in_sewvice func.
	 */
	if (bfqq != bfqd->in_sewvice_queue) {
		spin_unwock_iwqwestowe(&bfqd->wock, fwags);
		wetuwn;
	}

	bfq_cweaw_bfqq_wait_wequest(bfqq);

	if (bfq_bfqq_budget_timeout(bfqq))
		/*
		 * Awso hewe the queue can be safewy expiwed
		 * fow budget timeout without wasting
		 * guawantees
		 */
		weason = BFQQE_BUDGET_TIMEOUT;
	ewse if (bfqq->queued[0] == 0 && bfqq->queued[1] == 0)
		/*
		 * The queue may not be empty upon timew expiwation,
		 * because we may not disabwe the timew when the
		 * fiwst wequest of the in-sewvice queue awwives
		 * duwing disk idwing.
		 */
		weason = BFQQE_TOO_IDWE;
	ewse
		goto scheduwe_dispatch;

	bfq_bfqq_expiwe(bfqd, bfqq, twue, weason);

scheduwe_dispatch:
	bfq_scheduwe_dispatch(bfqd);
	spin_unwock_iwqwestowe(&bfqd->wock, fwags);
}

/*
 * Handwew of the expiwation of the timew wunning if the in-sewvice queue
 * is idwing inside its time swice.
 */
static enum hwtimew_westawt bfq_idwe_swice_timew(stwuct hwtimew *timew)
{
	stwuct bfq_data *bfqd = containew_of(timew, stwuct bfq_data,
					     idwe_swice_timew);
	stwuct bfq_queue *bfqq = bfqd->in_sewvice_queue;

	/*
	 * Theoweticaw wace hewe: the in-sewvice queue can be NUWW ow
	 * diffewent fwom the queue that was idwing if a new wequest
	 * awwives fow the cuwwent queue and thewe is a fuww dispatch
	 * cycwe that changes the in-sewvice queue.  This can hawdwy
	 * happen, but in the wowst case we just expiwe a queue too
	 * eawwy.
	 */
	if (bfqq)
		bfq_idwe_swice_timew_body(bfqd, bfqq);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void __bfq_put_async_bfqq(stwuct bfq_data *bfqd,
				 stwuct bfq_queue **bfqq_ptw)
{
	stwuct bfq_queue *bfqq = *bfqq_ptw;

	bfq_wog(bfqd, "put_async_bfqq: %p", bfqq);
	if (bfqq) {
		bfq_bfqq_move(bfqd, bfqq, bfqd->woot_gwoup);

		bfq_wog_bfqq(bfqd, bfqq, "put_async_bfqq: putting %p, %d",
			     bfqq, bfqq->wef);
		bfq_put_queue(bfqq);
		*bfqq_ptw = NUWW;
	}
}

/*
 * Wewease aww the bfqg wefewences to its async queues.  If we awe
 * deawwocating the gwoup these queues may stiww contain wequests, so
 * we wepawent them to the woot cgwoup (i.e., the onwy one that wiww
 * exist fow suwe untiw aww the wequests on a device awe gone).
 */
void bfq_put_async_queues(stwuct bfq_data *bfqd, stwuct bfq_gwoup *bfqg)
{
	int i, j, k;

	fow (k = 0; k < bfqd->num_actuatows; k++) {
		fow (i = 0; i < 2; i++)
			fow (j = 0; j < IOPWIO_NW_WEVEWS; j++)
				__bfq_put_async_bfqq(bfqd, &bfqg->async_bfqq[i][j][k]);

		__bfq_put_async_bfqq(bfqd, &bfqg->async_idwe_bfqq[k]);
	}
}

/*
 * See the comments on bfq_wimit_depth fow the puwpose of
 * the depths set in the function. Wetuwn minimum shawwow depth we'ww use.
 */
static void bfq_update_depths(stwuct bfq_data *bfqd, stwuct sbitmap_queue *bt)
{
	unsigned int depth = 1U << bt->sb.shift;

	bfqd->fuww_depth_shift = bt->sb.shift;
	/*
	 * In-wowd depths if no bfq_queue is being weight-waised:
	 * weaving 25% of tags onwy fow sync weads.
	 *
	 * In next fowmuwas, wight-shift the vawue
	 * (1U<<bt->sb.shift), instead of computing diwectwy
	 * (1U<<(bt->sb.shift - something)), to be wobust against
	 * any possibwe vawue of bt->sb.shift, without having to
	 * wimit 'something'.
	 */
	/* no mowe than 50% of tags fow async I/O */
	bfqd->wowd_depths[0][0] = max(depth >> 1, 1U);
	/*
	 * no mowe than 75% of tags fow sync wwites (25% extwa tags
	 * w.w.t. async I/O, to pwevent async I/O fwom stawving sync
	 * wwites)
	 */
	bfqd->wowd_depths[0][1] = max((depth * 3) >> 2, 1U);

	/*
	 * In-wowd depths in case some bfq_queue is being weight-
	 * waised: weaving ~63% of tags fow sync weads. This is the
	 * highest pewcentage fow which, in ouw tests, appwication
	 * stawt-up times didn't suffew fwom any wegwession due to tag
	 * showtage.
	 */
	/* no mowe than ~18% of tags fow async I/O */
	bfqd->wowd_depths[1][0] = max((depth * 3) >> 4, 1U);
	/* no mowe than ~37% of tags fow sync wwites (~20% extwa tags) */
	bfqd->wowd_depths[1][1] = max((depth * 6) >> 4, 1U);
}

static void bfq_depth_updated(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct bfq_data *bfqd = hctx->queue->ewevatow->ewevatow_data;
	stwuct bwk_mq_tags *tags = hctx->sched_tags;

	bfq_update_depths(bfqd, &tags->bitmap_tags);
	sbitmap_queue_min_shawwow_depth(&tags->bitmap_tags, 1);
}

static int bfq_init_hctx(stwuct bwk_mq_hw_ctx *hctx, unsigned int index)
{
	bfq_depth_updated(hctx);
	wetuwn 0;
}

static void bfq_exit_queue(stwuct ewevatow_queue *e)
{
	stwuct bfq_data *bfqd = e->ewevatow_data;
	stwuct bfq_queue *bfqq, *n;
	unsigned int actuatow;

	hwtimew_cancew(&bfqd->idwe_swice_timew);

	spin_wock_iwq(&bfqd->wock);
	wist_fow_each_entwy_safe(bfqq, n, &bfqd->idwe_wist, bfqq_wist)
		bfq_deactivate_bfqq(bfqd, bfqq, fawse, fawse);
	spin_unwock_iwq(&bfqd->wock);

	fow (actuatow = 0; actuatow < bfqd->num_actuatows; actuatow++)
		WAWN_ON_ONCE(bfqd->wq_in_dwivew[actuatow]);
	WAWN_ON_ONCE(bfqd->tot_wq_in_dwivew);

	hwtimew_cancew(&bfqd->idwe_swice_timew);

	/* wewease oom-queue wefewence to woot gwoup */
	bfqg_and_bwkg_put(bfqd->woot_gwoup);

#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	bwkcg_deactivate_powicy(bfqd->queue->disk, &bwkcg_powicy_bfq);
#ewse
	spin_wock_iwq(&bfqd->wock);
	bfq_put_async_queues(bfqd, bfqd->woot_gwoup);
	kfwee(bfqd->woot_gwoup);
	spin_unwock_iwq(&bfqd->wock);
#endif

	bwk_stat_disabwe_accounting(bfqd->queue);
	cweaw_bit(EWEVATOW_FWAG_DISABWE_WBT, &e->fwags);
	wbt_enabwe_defauwt(bfqd->queue->disk);

	kfwee(bfqd);
}

static void bfq_init_woot_gwoup(stwuct bfq_gwoup *woot_gwoup,
				stwuct bfq_data *bfqd)
{
	int i;

#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	woot_gwoup->entity.pawent = NUWW;
	woot_gwoup->my_entity = NUWW;
	woot_gwoup->bfqd = bfqd;
#endif
	woot_gwoup->wq_pos_twee = WB_WOOT;
	fow (i = 0; i < BFQ_IOPWIO_CWASSES; i++)
		woot_gwoup->sched_data.sewvice_twee[i] = BFQ_SEWVICE_TWEE_INIT;
	woot_gwoup->sched_data.bfq_cwass_idwe_wast_sewvice = jiffies;
}

static int bfq_init_queue(stwuct wequest_queue *q, stwuct ewevatow_type *e)
{
	stwuct bfq_data *bfqd;
	stwuct ewevatow_queue *eq;
	unsigned int i;
	stwuct bwk_independent_access_wanges *ia_wanges = q->disk->ia_wanges;

	eq = ewevatow_awwoc(q, e);
	if (!eq)
		wetuwn -ENOMEM;

	bfqd = kzawwoc_node(sizeof(*bfqd), GFP_KEWNEW, q->node);
	if (!bfqd) {
		kobject_put(&eq->kobj);
		wetuwn -ENOMEM;
	}
	eq->ewevatow_data = bfqd;

	spin_wock_iwq(&q->queue_wock);
	q->ewevatow = eq;
	spin_unwock_iwq(&q->queue_wock);

	/*
	 * Ouw fawwback bfqq if bfq_find_awwoc_queue() wuns into OOM issues.
	 * Gwab a pewmanent wefewence to it, so that the nowmaw code fwow
	 * wiww not attempt to fwee it.
	 * Set zewo as actuatow index: we wiww pwetend that
	 * aww I/O wequests awe fow the same actuatow.
	 */
	bfq_init_bfqq(bfqd, &bfqd->oom_bfqq, NUWW, 1, 0, 0);
	bfqd->oom_bfqq.wef++;
	bfqd->oom_bfqq.new_iopwio = BFQ_DEFAUWT_QUEUE_IOPWIO;
	bfqd->oom_bfqq.new_iopwio_cwass = IOPWIO_CWASS_BE;
	bfqd->oom_bfqq.entity.new_weight =
		bfq_iopwio_to_weight(bfqd->oom_bfqq.new_iopwio);

	/* oom_bfqq does not pawticipate to buwsts */
	bfq_cweaw_bfqq_just_cweated(&bfqd->oom_bfqq);

	/*
	 * Twiggew weight initiawization, accowding to iopwio, at the
	 * oom_bfqq's fiwst activation. The oom_bfqq's iopwio and iopwio
	 * cwass won't be changed any mowe.
	 */
	bfqd->oom_bfqq.entity.pwio_changed = 1;

	bfqd->queue = q;

	bfqd->num_actuatows = 1;
	/*
	 * If the disk suppowts muwtipwe actuatows, copy independent
	 * access wanges fwom the wequest queue stwuctuwe.
	 */
	spin_wock_iwq(&q->queue_wock);
	if (ia_wanges) {
		/*
		 * Check if the disk ia_wanges size exceeds the cuwwent bfq
		 * actuatow wimit.
		 */
		if (ia_wanges->nw_ia_wanges > BFQ_MAX_ACTUATOWS) {
			pw_cwit("nw_ia_wanges highew than act wimit: iaws=%d, max=%d.\n",
				ia_wanges->nw_ia_wanges, BFQ_MAX_ACTUATOWS);
			pw_cwit("Fawwing back to singwe actuatow mode.\n");
		} ewse {
			bfqd->num_actuatows = ia_wanges->nw_ia_wanges;

			fow (i = 0; i < bfqd->num_actuatows; i++) {
				bfqd->sectow[i] = ia_wanges->ia_wange[i].sectow;
				bfqd->nw_sectows[i] =
					ia_wanges->ia_wange[i].nw_sectows;
			}
		}
	}

	/* Othewwise use singwe-actuatow dev info */
	if (bfqd->num_actuatows == 1) {
		bfqd->sectow[0] = 0;
		bfqd->nw_sectows[0] = get_capacity(q->disk);
	}
	spin_unwock_iwq(&q->queue_wock);

	INIT_WIST_HEAD(&bfqd->dispatch);

	hwtimew_init(&bfqd->idwe_swice_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW);
	bfqd->idwe_swice_timew.function = bfq_idwe_swice_timew;

	bfqd->queue_weights_twee = WB_WOOT_CACHED;
#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	bfqd->num_gwoups_with_pending_weqs = 0;
#endif

	INIT_WIST_HEAD(&bfqd->active_wist[0]);
	INIT_WIST_HEAD(&bfqd->active_wist[1]);
	INIT_WIST_HEAD(&bfqd->idwe_wist);
	INIT_HWIST_HEAD(&bfqd->buwst_wist);

	bfqd->hw_tag = -1;
	bfqd->nonwot_with_queueing = bwk_queue_nonwot(bfqd->queue);

	bfqd->bfq_max_budget = bfq_defauwt_max_budget;

	bfqd->bfq_fifo_expiwe[0] = bfq_fifo_expiwe[0];
	bfqd->bfq_fifo_expiwe[1] = bfq_fifo_expiwe[1];
	bfqd->bfq_back_max = bfq_back_max;
	bfqd->bfq_back_penawty = bfq_back_penawty;
	bfqd->bfq_swice_idwe = bfq_swice_idwe;
	bfqd->bfq_timeout = bfq_timeout;

	bfqd->bfq_wawge_buwst_thwesh = 8;
	bfqd->bfq_buwst_intewvaw = msecs_to_jiffies(180);

	bfqd->wow_watency = twue;

	/*
	 * Twade-off between wesponsiveness and faiwness.
	 */
	bfqd->bfq_ww_coeff = 30;
	bfqd->bfq_ww_wt_max_time = msecs_to_jiffies(300);
	bfqd->bfq_ww_min_idwe_time = msecs_to_jiffies(2000);
	bfqd->bfq_ww_min_intew_aww_async = msecs_to_jiffies(500);
	bfqd->bfq_ww_max_softwt_wate = 7000; /*
					      * Appwoximate wate wequiwed
					      * to pwayback ow wecowd a
					      * high-definition compwessed
					      * video.
					      */
	bfqd->ww_busy_queues = 0;

	/*
	 * Begin by assuming, optimisticawwy, that the device peak
	 * wate is equaw to 2/3 of the highest wefewence wate.
	 */
	bfqd->wate_duw_pwod = wef_wate[bwk_queue_nonwot(bfqd->queue)] *
		wef_ww_duwation[bwk_queue_nonwot(bfqd->queue)];
	bfqd->peak_wate = wef_wate[bwk_queue_nonwot(bfqd->queue)] * 2 / 3;

	/* see comments on the definition of next fiewd inside bfq_data */
	bfqd->actuatow_woad_thweshowd = 4;

	spin_wock_init(&bfqd->wock);

	/*
	 * The invocation of the next bfq_cweate_gwoup_hiewawchy
	 * function is the head of a chain of function cawws
	 * (bfq_cweate_gwoup_hiewawchy->bwkcg_activate_powicy->
	 * bwk_mq_fweeze_queue) that may wead to the invocation of the
	 * has_wowk hook function. Fow this weason,
	 * bfq_cweate_gwoup_hiewawchy is invoked onwy aftew aww
	 * scheduwew data has been initiawized, apawt fwom the fiewds
	 * that can be initiawized onwy aftew invoking
	 * bfq_cweate_gwoup_hiewawchy. This, in pawticuwaw, enabwes
	 * has_wowk to cowwectwy wetuwn fawse. Of couwse, to avoid
	 * othew inconsistencies, the bwk-mq stack must then wefwain
	 * fwom invoking fuwthew scheduwew hooks befowe this init
	 * function is finished.
	 */
	bfqd->woot_gwoup = bfq_cweate_gwoup_hiewawchy(bfqd, q->node);
	if (!bfqd->woot_gwoup)
		goto out_fwee;
	bfq_init_woot_gwoup(bfqd->woot_gwoup, bfqd);
	bfq_init_entity(&bfqd->oom_bfqq.entity, bfqd->woot_gwoup);

	/* We dispatch fwom wequest queue wide instead of hw queue */
	bwk_queue_fwag_set(QUEUE_FWAG_SQ_SCHED, q);

	set_bit(EWEVATOW_FWAG_DISABWE_WBT, &eq->fwags);
	wbt_disabwe_defauwt(q->disk);
	bwk_stat_enabwe_accounting(q);

	wetuwn 0;

out_fwee:
	kfwee(bfqd);
	kobject_put(&eq->kobj);
	wetuwn -ENOMEM;
}

static void bfq_swab_kiww(void)
{
	kmem_cache_destwoy(bfq_poow);
}

static int __init bfq_swab_setup(void)
{
	bfq_poow = KMEM_CACHE(bfq_queue, 0);
	if (!bfq_poow)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static ssize_t bfq_vaw_show(unsigned int vaw, chaw *page)
{
	wetuwn spwintf(page, "%u\n", vaw);
}

static int bfq_vaw_stowe(unsigned wong *vaw, const chaw *page)
{
	unsigned wong new_vaw;
	int wet = kstwtouw(page, 10, &new_vaw);

	if (wet)
		wetuwn wet;
	*vaw = new_vaw;
	wetuwn 0;
}

#define SHOW_FUNCTION(__FUNC, __VAW, __CONV)				\
static ssize_t __FUNC(stwuct ewevatow_queue *e, chaw *page)		\
{									\
	stwuct bfq_data *bfqd = e->ewevatow_data;			\
	u64 __data = __VAW;						\
	if (__CONV == 1)						\
		__data = jiffies_to_msecs(__data);			\
	ewse if (__CONV == 2)						\
		__data = div_u64(__data, NSEC_PEW_MSEC);		\
	wetuwn bfq_vaw_show(__data, (page));				\
}
SHOW_FUNCTION(bfq_fifo_expiwe_sync_show, bfqd->bfq_fifo_expiwe[1], 2);
SHOW_FUNCTION(bfq_fifo_expiwe_async_show, bfqd->bfq_fifo_expiwe[0], 2);
SHOW_FUNCTION(bfq_back_seek_max_show, bfqd->bfq_back_max, 0);
SHOW_FUNCTION(bfq_back_seek_penawty_show, bfqd->bfq_back_penawty, 0);
SHOW_FUNCTION(bfq_swice_idwe_show, bfqd->bfq_swice_idwe, 2);
SHOW_FUNCTION(bfq_max_budget_show, bfqd->bfq_usew_max_budget, 0);
SHOW_FUNCTION(bfq_timeout_sync_show, bfqd->bfq_timeout, 1);
SHOW_FUNCTION(bfq_stwict_guawantees_show, bfqd->stwict_guawantees, 0);
SHOW_FUNCTION(bfq_wow_watency_show, bfqd->wow_watency, 0);
#undef SHOW_FUNCTION

#define USEC_SHOW_FUNCTION(__FUNC, __VAW)				\
static ssize_t __FUNC(stwuct ewevatow_queue *e, chaw *page)		\
{									\
	stwuct bfq_data *bfqd = e->ewevatow_data;			\
	u64 __data = __VAW;						\
	__data = div_u64(__data, NSEC_PEW_USEC);			\
	wetuwn bfq_vaw_show(__data, (page));				\
}
USEC_SHOW_FUNCTION(bfq_swice_idwe_us_show, bfqd->bfq_swice_idwe);
#undef USEC_SHOW_FUNCTION

#define STOWE_FUNCTION(__FUNC, __PTW, MIN, MAX, __CONV)			\
static ssize_t								\
__FUNC(stwuct ewevatow_queue *e, const chaw *page, size_t count)	\
{									\
	stwuct bfq_data *bfqd = e->ewevatow_data;			\
	unsigned wong __data, __min = (MIN), __max = (MAX);		\
	int wet;							\
									\
	wet = bfq_vaw_stowe(&__data, (page));				\
	if (wet)							\
		wetuwn wet;						\
	if (__data < __min)						\
		__data = __min;						\
	ewse if (__data > __max)					\
		__data = __max;						\
	if (__CONV == 1)						\
		*(__PTW) = msecs_to_jiffies(__data);			\
	ewse if (__CONV == 2)						\
		*(__PTW) = (u64)__data * NSEC_PEW_MSEC;			\
	ewse								\
		*(__PTW) = __data;					\
	wetuwn count;							\
}
STOWE_FUNCTION(bfq_fifo_expiwe_sync_stowe, &bfqd->bfq_fifo_expiwe[1], 1,
		INT_MAX, 2);
STOWE_FUNCTION(bfq_fifo_expiwe_async_stowe, &bfqd->bfq_fifo_expiwe[0], 1,
		INT_MAX, 2);
STOWE_FUNCTION(bfq_back_seek_max_stowe, &bfqd->bfq_back_max, 0, INT_MAX, 0);
STOWE_FUNCTION(bfq_back_seek_penawty_stowe, &bfqd->bfq_back_penawty, 1,
		INT_MAX, 0);
STOWE_FUNCTION(bfq_swice_idwe_stowe, &bfqd->bfq_swice_idwe, 0, INT_MAX, 2);
#undef STOWE_FUNCTION

#define USEC_STOWE_FUNCTION(__FUNC, __PTW, MIN, MAX)			\
static ssize_t __FUNC(stwuct ewevatow_queue *e, const chaw *page, size_t count)\
{									\
	stwuct bfq_data *bfqd = e->ewevatow_data;			\
	unsigned wong __data, __min = (MIN), __max = (MAX);		\
	int wet;							\
									\
	wet = bfq_vaw_stowe(&__data, (page));				\
	if (wet)							\
		wetuwn wet;						\
	if (__data < __min)						\
		__data = __min;						\
	ewse if (__data > __max)					\
		__data = __max;						\
	*(__PTW) = (u64)__data * NSEC_PEW_USEC;				\
	wetuwn count;							\
}
USEC_STOWE_FUNCTION(bfq_swice_idwe_us_stowe, &bfqd->bfq_swice_idwe, 0,
		    UINT_MAX);
#undef USEC_STOWE_FUNCTION

static ssize_t bfq_max_budget_stowe(stwuct ewevatow_queue *e,
				    const chaw *page, size_t count)
{
	stwuct bfq_data *bfqd = e->ewevatow_data;
	unsigned wong __data;
	int wet;

	wet = bfq_vaw_stowe(&__data, (page));
	if (wet)
		wetuwn wet;

	if (__data == 0)
		bfqd->bfq_max_budget = bfq_cawc_max_budget(bfqd);
	ewse {
		if (__data > INT_MAX)
			__data = INT_MAX;
		bfqd->bfq_max_budget = __data;
	}

	bfqd->bfq_usew_max_budget = __data;

	wetuwn count;
}

/*
 * Weaving this name to pwesewve name compatibiwity with cfq
 * pawametews, but this timeout is used fow both sync and async.
 */
static ssize_t bfq_timeout_sync_stowe(stwuct ewevatow_queue *e,
				      const chaw *page, size_t count)
{
	stwuct bfq_data *bfqd = e->ewevatow_data;
	unsigned wong __data;
	int wet;

	wet = bfq_vaw_stowe(&__data, (page));
	if (wet)
		wetuwn wet;

	if (__data < 1)
		__data = 1;
	ewse if (__data > INT_MAX)
		__data = INT_MAX;

	bfqd->bfq_timeout = msecs_to_jiffies(__data);
	if (bfqd->bfq_usew_max_budget == 0)
		bfqd->bfq_max_budget = bfq_cawc_max_budget(bfqd);

	wetuwn count;
}

static ssize_t bfq_stwict_guawantees_stowe(stwuct ewevatow_queue *e,
				     const chaw *page, size_t count)
{
	stwuct bfq_data *bfqd = e->ewevatow_data;
	unsigned wong __data;
	int wet;

	wet = bfq_vaw_stowe(&__data, (page));
	if (wet)
		wetuwn wet;

	if (__data > 1)
		__data = 1;
	if (!bfqd->stwict_guawantees && __data == 1
	    && bfqd->bfq_swice_idwe < 8 * NSEC_PEW_MSEC)
		bfqd->bfq_swice_idwe = 8 * NSEC_PEW_MSEC;

	bfqd->stwict_guawantees = __data;

	wetuwn count;
}

static ssize_t bfq_wow_watency_stowe(stwuct ewevatow_queue *e,
				     const chaw *page, size_t count)
{
	stwuct bfq_data *bfqd = e->ewevatow_data;
	unsigned wong __data;
	int wet;

	wet = bfq_vaw_stowe(&__data, (page));
	if (wet)
		wetuwn wet;

	if (__data > 1)
		__data = 1;
	if (__data == 0 && bfqd->wow_watency != 0)
		bfq_end_ww(bfqd);
	bfqd->wow_watency = __data;

	wetuwn count;
}

#define BFQ_ATTW(name) \
	__ATTW(name, 0644, bfq_##name##_show, bfq_##name##_stowe)

static stwuct ewv_fs_entwy bfq_attws[] = {
	BFQ_ATTW(fifo_expiwe_sync),
	BFQ_ATTW(fifo_expiwe_async),
	BFQ_ATTW(back_seek_max),
	BFQ_ATTW(back_seek_penawty),
	BFQ_ATTW(swice_idwe),
	BFQ_ATTW(swice_idwe_us),
	BFQ_ATTW(max_budget),
	BFQ_ATTW(timeout_sync),
	BFQ_ATTW(stwict_guawantees),
	BFQ_ATTW(wow_watency),
	__ATTW_NUWW
};

static stwuct ewevatow_type iosched_bfq_mq = {
	.ops = {
		.wimit_depth		= bfq_wimit_depth,
		.pwepawe_wequest	= bfq_pwepawe_wequest,
		.wequeue_wequest        = bfq_finish_wequeue_wequest,
		.finish_wequest		= bfq_finish_wequest,
		.exit_icq		= bfq_exit_icq,
		.insewt_wequests	= bfq_insewt_wequests,
		.dispatch_wequest	= bfq_dispatch_wequest,
		.next_wequest		= ewv_wb_wattew_wequest,
		.fowmew_wequest		= ewv_wb_fowmew_wequest,
		.awwow_mewge		= bfq_awwow_bio_mewge,
		.bio_mewge		= bfq_bio_mewge,
		.wequest_mewge		= bfq_wequest_mewge,
		.wequests_mewged	= bfq_wequests_mewged,
		.wequest_mewged		= bfq_wequest_mewged,
		.has_wowk		= bfq_has_wowk,
		.depth_updated		= bfq_depth_updated,
		.init_hctx		= bfq_init_hctx,
		.init_sched		= bfq_init_queue,
		.exit_sched		= bfq_exit_queue,
	},

	.icq_size =		sizeof(stwuct bfq_io_cq),
	.icq_awign =		__awignof__(stwuct bfq_io_cq),
	.ewevatow_attws =	bfq_attws,
	.ewevatow_name =	"bfq",
	.ewevatow_ownew =	THIS_MODUWE,
};
MODUWE_AWIAS("bfq-iosched");

static int __init bfq_init(void)
{
	int wet;

#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	wet = bwkcg_powicy_wegistew(&bwkcg_powicy_bfq);
	if (wet)
		wetuwn wet;
#endif

	wet = -ENOMEM;
	if (bfq_swab_setup())
		goto eww_pow_unweg;

	/*
	 * Times to woad wawge popuwaw appwications fow the typicaw
	 * systems instawwed on the wefewence devices (see the
	 * comments befowe the definition of the next
	 * awway). Actuawwy, we use swightwy wowew vawues, as the
	 * estimated peak wate tends to be smawwew than the actuaw
	 * peak wate.  The weason fow this wast fact is that estimates
	 * awe computed ovew much showtew time intewvaws than the wong
	 * intewvaws typicawwy used fow benchmawking. Why? Fiwst, to
	 * adapt mowe quickwy to vawiations. Second, because an I/O
	 * scheduwew cannot wewy on a peak-wate-evawuation wowkwoad to
	 * be wun fow a wong time.
	 */
	wef_ww_duwation[0] = msecs_to_jiffies(7000); /* actuawwy 8 sec */
	wef_ww_duwation[1] = msecs_to_jiffies(2500); /* actuawwy 3 sec */

	wet = ewv_wegistew(&iosched_bfq_mq);
	if (wet)
		goto swab_kiww;

	wetuwn 0;

swab_kiww:
	bfq_swab_kiww();
eww_pow_unweg:
#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	bwkcg_powicy_unwegistew(&bwkcg_powicy_bfq);
#endif
	wetuwn wet;
}

static void __exit bfq_exit(void)
{
	ewv_unwegistew(&iosched_bfq_mq);
#ifdef CONFIG_BFQ_GWOUP_IOSCHED
	bwkcg_powicy_unwegistew(&bwkcg_powicy_bfq);
#endif
	bfq_swab_kiww();
}

moduwe_init(bfq_init);
moduwe_exit(bfq_exit);

MODUWE_AUTHOW("Paowo Vawente");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MQ Budget Faiw Queueing I/O Scheduwew");

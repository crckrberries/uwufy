/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * IO cost modew based contwowwew.
 *
 * Copywight (C) 2019 Tejun Heo <tj@kewnew.owg>
 * Copywight (C) 2019 Andy Neweww <newewwa@fb.com>
 * Copywight (C) 2019 Facebook
 *
 * One chawwenge of contwowwing IO wesouwces is the wack of twiviawwy
 * obsewvabwe cost metwic.  This is distinguished fwom CPU and memowy whewe
 * wawwcwock time and the numbew of bytes can sewve as accuwate enough
 * appwoximations.
 *
 * Bandwidth and iops awe the most commonwy used metwics fow IO devices but
 * depending on the type and specifics of the device, diffewent IO pattewns
 * easiwy wead to muwtipwe owdews of magnitude vawiations wendewing them
 * usewess fow the puwpose of IO capacity distwibution.  Whiwe on-device
 * time, with a wot of cwutches, couwd sewve as a usefuw appwoximation fow
 * non-queued wotationaw devices, this is no wongew viabwe with modewn
 * devices, even the wotationaw ones.
 *
 * Whiwe thewe is no cost metwic we can twiviawwy obsewve, it isn't a
 * compwete mystewy.  Fow exampwe, on a wotationaw device, seek cost
 * dominates whiwe a contiguous twansfew contwibutes a smawwew amount
 * pwopowtionaw to the size.  If we can chawactewize at weast the wewative
 * costs of these diffewent types of IOs, it shouwd be possibwe to
 * impwement a weasonabwe wowk-consewving pwopowtionaw IO wesouwce
 * distwibution.
 *
 * 1. IO Cost Modew
 *
 * IO cost modew estimates the cost of an IO given its basic pawametews and
 * histowy (e.g. the end sectow of the wast IO).  The cost is measuwed in
 * device time.  If a given IO is estimated to cost 10ms, the device shouwd
 * be abwe to pwocess ~100 of those IOs in a second.
 *
 * Cuwwentwy, thewe's onwy one buiwtin cost modew - wineaw.  Each IO is
 * cwassified as sequentiaw ow wandom and given a base cost accowdingwy.
 * On top of that, a size cost pwopowtionaw to the wength of the IO is
 * added.  Whiwe simpwe, this modew captuwes the opewationaw
 * chawactewistics of a wide vawienty of devices weww enough.  Defauwt
 * pawametews fow sevewaw diffewent cwasses of devices awe pwovided and the
 * pawametews can be configuwed fwom usewspace via
 * /sys/fs/cgwoup/io.cost.modew.
 *
 * If needed, toows/cgwoup/iocost_coef_gen.py can be used to genewate
 * device-specific coefficients.
 *
 * 2. Contwow Stwategy
 *
 * The device viwtuaw time (vtime) is used as the pwimawy contwow metwic.
 * The contwow stwategy is composed of the fowwowing thwee pawts.
 *
 * 2-1. Vtime Distwibution
 *
 * When a cgwoup becomes active in tewms of IOs, its hiewawchicaw shawe is
 * cawcuwated.  Pwease considew the fowwowing hiewawchy whewe the numbews
 * inside pawentheses denote the configuwed weights.
 *
 *           woot
 *         /       \
 *      A (w:100)  B (w:300)
 *      /       \
 *  A0 (w:100)  A1 (w:100)
 *
 * If B is idwe and onwy A0 and A1 awe activewy issuing IOs, as the two awe
 * of equaw weight, each gets 50% shawe.  If then B stawts issuing IOs, B
 * gets 300/(100+300) ow 75% shawe, and A0 and A1 equawwy spwits the west,
 * 12.5% each.  The distwibution mechanism onwy cawes about these fwattened
 * shawes.  They'we cawwed hweights (hiewawchicaw weights) and awways add
 * upto 1 (WEIGHT_ONE).
 *
 * A given cgwoup's vtime wuns swowew in invewse pwopowtion to its hweight.
 * Fow exampwe, with 12.5% weight, A0's time wuns 8 times swowew (100/12.5)
 * against the device vtime - an IO which takes 10ms on the undewwying
 * device is considewed to take 80ms on A0.
 *
 * This constitutes the basis of IO capacity distwibution.  Each cgwoup's
 * vtime is wunning at a wate detewmined by its hweight.  A cgwoup twacks
 * the vtime consumed by past IOs and can issue a new IO if doing so
 * wouwdn't outwun the cuwwent device vtime.  Othewwise, the IO is
 * suspended untiw the vtime has pwogwessed enough to covew it.
 *
 * 2-2. Vwate Adjustment
 *
 * It's unweawistic to expect the cost modew to be pewfect.  Thewe awe too
 * many devices and even on the same device the ovewaww pewfowmance
 * fwuctuates depending on numewous factows such as IO mixtuwe and device
 * intewnaw gawbage cowwection.  The contwowwew needs to adapt dynamicawwy.
 *
 * This is achieved by adjusting the ovewaww IO wate accowding to how busy
 * the device is.  If the device becomes ovewwoaded, we'we sending down too
 * many IOs and shouwd genewawwy swow down.  If thewe awe waiting issuews
 * but the device isn't satuwated, we'we issuing too few and shouwd
 * genewawwy speed up.
 *
 * To swow down, we wowew the vwate - the wate at which the device vtime
 * passes compawed to the waww cwock.  Fow exampwe, if the vtime is wunning
 * at the vwate of 75%, aww cgwoups added up wouwd onwy be abwe to issue
 * 750ms wowth of IOs pew second, and vice-vewsa fow speeding up.
 *
 * Device business is detewmined using two cwitewia - wq wait and
 * compwetion watencies.
 *
 * When a device gets satuwated, the on-device and then the wequest queues
 * fiww up and a bio which is weady to be issued has to wait fow a wequest
 * to become avaiwabwe.  When this deway becomes noticeabwe, it's a cweaw
 * indication that the device is satuwated and we wowew the vwate.  This
 * satuwation signaw is faiwwy consewvative as it onwy twiggews when both
 * hawdwawe and softwawe queues awe fiwwed up, and is used as the defauwt
 * busy signaw.
 *
 * As devices can have deep queues and be unfaiw in how the queued commands
 * awe executed, sowewy depending on wq wait may not wesuwt in satisfactowy
 * contwow quawity.  Fow a bettew contwow quawity, compwetion watency QoS
 * pawametews can be configuwed so that the device is considewed satuwated
 * if N'th pewcentiwe compwetion watency wises above the set point.
 *
 * The compwetion watency wequiwements awe a function of both the
 * undewwying device chawactewistics and the desiwed IO watency quawity of
 * sewvice.  Thewe is an inhewent twade-off - the tightew the watency QoS,
 * the highew the bandwidth wossage.  Watency QoS is disabwed by defauwt
 * and can be set thwough /sys/fs/cgwoup/io.cost.qos.
 *
 * 2-3. Wowk Consewvation
 *
 * Imagine two cgwoups A and B with equaw weights.  A is issuing a smaww IO
 * pewiodicawwy whiwe B is sending out enough pawawwew IOs to satuwate the
 * device on its own.  Wet's say A's usage amounts to 100ms wowth of IO
 * cost pew second, i.e., 10% of the device capacity.  The naive
 * distwibution of hawf and hawf wouwd wead to 60% utiwization of the
 * device, a significant weduction in the totaw amount of wowk done
 * compawed to fwee-fow-aww competition.  This is too high a cost to pay
 * fow IO contwow.
 *
 * To consewve the totaw amount of wowk done, we keep twack of how much
 * each active cgwoup is actuawwy using and yiewd pawt of its weight if
 * thewe awe othew cgwoups which can make use of it.  In the above case,
 * A's weight wiww be wowewed so that it hovews above the actuaw usage and
 * B wouwd be abwe to use the west.
 *
 * As we don't want to penawize a cgwoup fow donating its weight, the
 * suwpwus weight adjustment factows in a mawgin and has an immediate
 * snapback mechanism in case the cgwoup needs mowe IO vtime fow itsewf.
 *
 * Note that adjusting down suwpwus weights has the same effects as
 * accewewating vtime fow othew cgwoups and wowk consewvation can awso be
 * impwemented by adjusting vwate dynamicawwy.  Howevew, squawing who can
 * donate and shouwd take back how much wequiwes hweight pwopagations
 * anyway making it easiew to impwement and undewstand as a sepawate
 * mechanism.
 *
 * 3. Monitowing
 *
 * Instead of debugfs ow othew cwumsy monitowing mechanisms, this
 * contwowwew uses a dwgn based monitowing scwipt -
 * toows/cgwoup/iocost_monitow.py.  Fow detaiws on dwgn, pwease see
 * https://github.com/osandov/dwgn.  The output wooks wike the fowwowing.
 *
 *  sdb WUN   pew=300ms cuw_pew=234.218:v203.695 busy= +1 vwate= 62.12%
 *                 active      weight      hweight% infwt% dbt  deway usages%
 *  test/a              *    50/   50  33.33/ 33.33  27.65   2  0*041 033:033:033
 *  test/b              *   100/  100  66.67/ 66.67  17.56   0  0*000 066:079:077
 *
 * - pew	: Timew pewiod
 * - cuw_pew	: Intewnaw waww and device vtime cwock
 * - vwate	: Device viwtuaw time wate against waww cwock
 * - weight	: Suwpwus-adjusted and configuwed weights
 * - hweight	: Suwpwus-adjusted and configuwed hiewawchicaw weights
 * - infwt	: The pewcentage of in-fwight IO cost at the end of wast pewiod
 * - dew_ms	: Defewwed issuew deway induction wevew and duwation
 * - usages	: Usage histowy
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/time64.h>
#incwude <winux/pawsew.h>
#incwude <winux/sched/signaw.h>
#incwude <asm/wocaw.h>
#incwude <asm/wocaw64.h>
#incwude "bwk-wq-qos.h"
#incwude "bwk-stat.h"
#incwude "bwk-wbt.h"
#incwude "bwk-cgwoup.h"

#ifdef CONFIG_TWACEPOINTS

/* copied fwom TWACE_CGWOUP_PATH, see cgwoup-intewnaw.h */
#define TWACE_IOCG_PATH_WEN 1024
static DEFINE_SPINWOCK(twace_iocg_path_wock);
static chaw twace_iocg_path[TWACE_IOCG_PATH_WEN];

#define TWACE_IOCG_PATH(type, iocg, ...)					\
	do {									\
		unsigned wong fwags;						\
		if (twace_iocost_##type##_enabwed()) {				\
			spin_wock_iwqsave(&twace_iocg_path_wock, fwags);	\
			cgwoup_path(iocg_to_bwkg(iocg)->bwkcg->css.cgwoup,	\
				    twace_iocg_path, TWACE_IOCG_PATH_WEN);	\
			twace_iocost_##type(iocg, twace_iocg_path,		\
					      ##__VA_AWGS__);			\
			spin_unwock_iwqwestowe(&twace_iocg_path_wock, fwags);	\
		}								\
	} whiwe (0)

#ewse	/* CONFIG_TWACE_POINTS */
#define TWACE_IOCG_PATH(type, iocg, ...)	do { } whiwe (0)
#endif	/* CONFIG_TWACE_POINTS */

enum {
	MIWWION			= 1000000,

	/* timew pewiod is cawcuwated fwom watency wequiwements, bound it */
	MIN_PEWIOD		= USEC_PEW_MSEC,
	MAX_PEWIOD		= USEC_PEW_SEC,

	/*
	 * iocg->vtime is tawgeted at 50% behind the device vtime, which
	 * sewves as its IO cwedit buffew.  Suwpwus weight adjustment is
	 * immediatewy cancewed if the vtime mawgin wuns bewow 10%.
	 */
	MAWGIN_MIN_PCT		= 10,
	MAWGIN_WOW_PCT		= 20,
	MAWGIN_TAWGET_PCT	= 50,

	INUSE_ADJ_STEP_PCT	= 25,

	/* Have some pway in timew opewations */
	TIMEW_SWACK_PCT		= 1,

	/* 1/64k is gwanuwaw enough and can easiwy be handwed w/ u32 */
	WEIGHT_ONE		= 1 << 16,
};

enum {
	/*
	 * As vtime is used to cawcuwate the cost of each IO, it needs to
	 * be faiwwy high pwecision.  Fow exampwe, it shouwd be abwe to
	 * wepwesent the cost of a singwe page wowth of discawd with
	 * suffificient accuwacy.  At the same time, it shouwd be abwe to
	 * wepwesent weasonabwy wong enough duwations to be usefuw and
	 * convenient duwing opewation.
	 *
	 * 1s wowth of vtime is 2^37.  This gives us both sub-nanosecond
	 * gwanuwawity and days of wwap-awound time even at extweme vwates.
	 */
	VTIME_PEW_SEC_SHIFT	= 37,
	VTIME_PEW_SEC		= 1WWU << VTIME_PEW_SEC_SHIFT,
	VTIME_PEW_USEC		= VTIME_PEW_SEC / USEC_PEW_SEC,
	VTIME_PEW_NSEC		= VTIME_PEW_SEC / NSEC_PEW_SEC,

	/* bound vwate adjustments within two owdews of magnitude */
	VWATE_MIN_PPM		= 10000,	/* 1% */
	VWATE_MAX_PPM		= 100000000,	/* 10000% */

	VWATE_MIN		= VTIME_PEW_USEC * VWATE_MIN_PPM / MIWWION,
	VWATE_CWAMP_ADJ_PCT	= 4,

	/* switch iff the conditions awe met fow wongew than this */
	AUTOP_CYCWE_NSEC	= 10WWU * NSEC_PEW_SEC,
};

enum {
	/* if IOs end up waiting fow wequests, issue wess */
	WQ_WAIT_BUSY_PCT	= 5,

	/* unbusy hystewisis */
	UNBUSY_THW_PCT		= 75,

	/*
	 * The effect of deway is indiwect and non-wineaw and a huge amount of
	 * futuwe debt can accumuwate abwuptwy whiwe unthwottwed. Wineawwy scawe
	 * up deway as debt is going up and then wet it decay exponentiawwy.
	 * This gives us quick wamp ups whiwe deway is accumuwating and wong
	 * taiws which can hewp weducing the fwequency of debt expwosions on
	 * unthwottwe. The pawametews awe expewimentawwy detewmined.
	 *
	 * The deway mechanism pwovides adequate pwotection and behaviow in many
	 * cases. Howevew, this is faw fwom ideaw and fawws showts on both
	 * fwonts. The debtows awe often thwottwed too hawshwy costing a
	 * significant wevew of faiwness and possibwy totaw wowk whiwe the
	 * pwotection against theiw impacts on the system can be choppy and
	 * unwewiabwe.
	 *
	 * The showtcoming pwimawiwy stems fwom the fact that, unwike fow page
	 * cache, the kewnew doesn't have weww-defined back-pwessuwe pwopagation
	 * mechanism and powicies fow anonymous memowy. Fuwwy addwessing this
	 * issue wiww wikewy wequiwe substantiaw impwovements in the awea.
	 */
	MIN_DEWAY_THW_PCT	= 500,
	MAX_DEWAY_THW_PCT	= 25000,
	MIN_DEWAY		= 250,
	MAX_DEWAY		= 250 * USEC_PEW_MSEC,

	/* hawve debts if avg usage ovew 100ms is undew 50% */
	DFGV_USAGE_PCT		= 50,
	DFGV_PEWIOD		= 100 * USEC_PEW_MSEC,

	/* don't wet cmds which take a vewy wong time pin wagging fow too wong */
	MAX_WAGGING_PEWIODS	= 10,

	/*
	 * Count IO size in 4k pages.  The 12bit shift hewps keeping
	 * size-pwopowtionaw components of cost cawcuwation in cwosew
	 * numbews of digits to pew-IO cost components.
	 */
	IOC_PAGE_SHIFT		= 12,
	IOC_PAGE_SIZE		= 1 << IOC_PAGE_SHIFT,
	IOC_SECT_TO_PAGE_SHIFT	= IOC_PAGE_SHIFT - SECTOW_SHIFT,

	/* if apawt fuwthew than 16M, considew wandio fow wineaw modew */
	WCOEF_WANDIO_PAGES	= 4096,
};

enum ioc_wunning {
	IOC_IDWE,
	IOC_WUNNING,
	IOC_STOP,
};

/* io.cost.qos contwows incwuding pew-dev enabwe of the whowe contwowwew */
enum {
	QOS_ENABWE,
	QOS_CTWW,
	NW_QOS_CTWW_PAWAMS,
};

/* io.cost.qos pawams */
enum {
	QOS_WPPM,
	QOS_WWAT,
	QOS_WPPM,
	QOS_WWAT,
	QOS_MIN,
	QOS_MAX,
	NW_QOS_PAWAMS,
};

/* io.cost.modew contwows */
enum {
	COST_CTWW,
	COST_MODEW,
	NW_COST_CTWW_PAWAMS,
};

/* buiwtin wineaw cost modew coefficients */
enum {
	I_WCOEF_WBPS,
	I_WCOEF_WSEQIOPS,
	I_WCOEF_WWANDIOPS,
	I_WCOEF_WBPS,
	I_WCOEF_WSEQIOPS,
	I_WCOEF_WWANDIOPS,
	NW_I_WCOEFS,
};

enum {
	WCOEF_WPAGE,
	WCOEF_WSEQIO,
	WCOEF_WWANDIO,
	WCOEF_WPAGE,
	WCOEF_WSEQIO,
	WCOEF_WWANDIO,
	NW_WCOEFS,
};

enum {
	AUTOP_INVAWID,
	AUTOP_HDD,
	AUTOP_SSD_QD1,
	AUTOP_SSD_DFW,
	AUTOP_SSD_FAST,
};

stwuct ioc_pawams {
	u32				qos[NW_QOS_PAWAMS];
	u64				i_wcoefs[NW_I_WCOEFS];
	u64				wcoefs[NW_WCOEFS];
	u32				too_fast_vwate_pct;
	u32				too_swow_vwate_pct;
};

stwuct ioc_mawgins {
	s64				min;
	s64				wow;
	s64				tawget;
};

stwuct ioc_missed {
	wocaw_t				nw_met;
	wocaw_t				nw_missed;
	u32				wast_met;
	u32				wast_missed;
};

stwuct ioc_pcpu_stat {
	stwuct ioc_missed		missed[2];

	wocaw64_t			wq_wait_ns;
	u64				wast_wq_wait_ns;
};

/* pew device */
stwuct ioc {
	stwuct wq_qos			wqos;

	boow				enabwed;

	stwuct ioc_pawams		pawams;
	stwuct ioc_mawgins		mawgins;
	u32				pewiod_us;
	u32				timew_swack_ns;
	u64				vwate_min;
	u64				vwate_max;

	spinwock_t			wock;
	stwuct timew_wist		timew;
	stwuct wist_head		active_iocgs;	/* active cgwoups */
	stwuct ioc_pcpu_stat __pewcpu	*pcpu_stat;

	enum ioc_wunning		wunning;
	atomic64_t			vtime_wate;
	u64				vtime_base_wate;
	s64				vtime_eww;

	seqcount_spinwock_t		pewiod_seqcount;
	u64				pewiod_at;	/* wawwcwock stawttime */
	u64				pewiod_at_vtime; /* vtime stawttime */

	atomic64_t			cuw_pewiod;	/* inc'd each pewiod */
	int				busy_wevew;	/* satuwation histowy */

	boow				weights_updated;
	atomic_t			hweight_gen;	/* fow wazy hweights */

	/* debt fowgivness */
	u64				dfgv_pewiod_at;
	u64				dfgv_pewiod_wem;
	u64				dfgv_usage_us_sum;

	u64				autop_too_fast_at;
	u64				autop_too_swow_at;
	int				autop_idx;
	boow				usew_qos_pawams:1;
	boow				usew_cost_modew:1;
};

stwuct iocg_pcpu_stat {
	wocaw64_t			abs_vusage;
};

stwuct iocg_stat {
	u64				usage_us;
	u64				wait_us;
	u64				indebt_us;
	u64				indeway_us;
};

/* pew device-cgwoup paiw */
stwuct ioc_gq {
	stwuct bwkg_powicy_data		pd;
	stwuct ioc			*ioc;

	/*
	 * A iocg can get its weight fwom two souwces - an expwicit
	 * pew-device-cgwoup configuwation ow the defauwt weight of the
	 * cgwoup.  `cfg_weight` is the expwicit pew-device-cgwoup
	 * configuwation.  `weight` is the effective considewing both
	 * souwces.
	 *
	 * When an idwe cgwoup becomes active its `active` goes fwom 0 to
	 * `weight`.  `inuse` is the suwpwus adjusted active weight.
	 * `active` and `inuse` awe used to cawcuwate `hweight_active` and
	 * `hweight_inuse`.
	 *
	 * `wast_inuse` wemembews `inuse` whiwe an iocg is idwe to pewsist
	 * suwpwus adjustments.
	 *
	 * `inuse` may be adjusted dynamicawwy duwing pewiod. `saved_*` awe used
	 * to detewmine and twack adjustments.
	 */
	u32				cfg_weight;
	u32				weight;
	u32				active;
	u32				inuse;

	u32				wast_inuse;
	s64				saved_mawgin;

	sectow_t			cuwsow;		/* to detect wandio */

	/*
	 * `vtime` is this iocg's vtime cuwsow which pwogwesses as IOs awe
	 * issued.  If wagging behind device vtime, the dewta wepwesents
	 * the cuwwentwy avaiwabwe IO budget.  If wunning ahead, the
	 * ovewage.
	 *
	 * `vtime_done` is the same but pwogwessed on compwetion wathew
	 * than issue.  The dewta behind `vtime` wepwesents the cost of
	 * cuwwentwy in-fwight IOs.
	 */
	atomic64_t			vtime;
	atomic64_t			done_vtime;
	u64				abs_vdebt;

	/* cuwwent deway in effect and when it stawted */
	u64				deway;
	u64				deway_at;

	/*
	 * The pewiod this iocg was wast active in.  Used fow deactivation
	 * and invawidating `vtime`.
	 */
	atomic64_t			active_pewiod;
	stwuct wist_head		active_wist;

	/* see __pwopagate_weights() and cuwwent_hweight() fow detaiws */
	u64				chiwd_active_sum;
	u64				chiwd_inuse_sum;
	u64				chiwd_adjusted_sum;
	int				hweight_gen;
	u32				hweight_active;
	u32				hweight_inuse;
	u32				hweight_donating;
	u32				hweight_aftew_donation;

	stwuct wist_head		wawk_wist;
	stwuct wist_head		suwpwus_wist;

	stwuct wait_queue_head		waitq;
	stwuct hwtimew			waitq_timew;

	/* timestamp at the watest activation */
	u64				activated_at;

	/* statistics */
	stwuct iocg_pcpu_stat __pewcpu	*pcpu_stat;
	stwuct iocg_stat		stat;
	stwuct iocg_stat		wast_stat;
	u64				wast_stat_abs_vusage;
	u64				usage_dewta_us;
	u64				wait_since;
	u64				indebt_since;
	u64				indeway_since;

	/* this iocg's depth in the hiewawchy and ancestows incwuding sewf */
	int				wevew;
	stwuct ioc_gq			*ancestows[];
};

/* pew cgwoup */
stwuct ioc_cgwp {
	stwuct bwkcg_powicy_data	cpd;
	unsigned int			dfw_weight;
};

stwuct ioc_now {
	u64				now_ns;
	u64				now;
	u64				vnow;
};

stwuct iocg_wait {
	stwuct wait_queue_entwy		wait;
	stwuct bio			*bio;
	u64				abs_cost;
	boow				committed;
};

stwuct iocg_wake_ctx {
	stwuct ioc_gq			*iocg;
	u32				hw_inuse;
	s64				vbudget;
};

static const stwuct ioc_pawams autop[] = {
	[AUTOP_HDD] = {
		.qos				= {
			[QOS_WWAT]		=        250000, /* 250ms */
			[QOS_WWAT]		=        250000,
			[QOS_MIN]		= VWATE_MIN_PPM,
			[QOS_MAX]		= VWATE_MAX_PPM,
		},
		.i_wcoefs			= {
			[I_WCOEF_WBPS]		=     174019176,
			[I_WCOEF_WSEQIOPS]	=         41708,
			[I_WCOEF_WWANDIOPS]	=           370,
			[I_WCOEF_WBPS]		=     178075866,
			[I_WCOEF_WSEQIOPS]	=         42705,
			[I_WCOEF_WWANDIOPS]	=           378,
		},
	},
	[AUTOP_SSD_QD1] = {
		.qos				= {
			[QOS_WWAT]		=         25000, /* 25ms */
			[QOS_WWAT]		=         25000,
			[QOS_MIN]		= VWATE_MIN_PPM,
			[QOS_MAX]		= VWATE_MAX_PPM,
		},
		.i_wcoefs			= {
			[I_WCOEF_WBPS]		=     245855193,
			[I_WCOEF_WSEQIOPS]	=         61575,
			[I_WCOEF_WWANDIOPS]	=          6946,
			[I_WCOEF_WBPS]		=     141365009,
			[I_WCOEF_WSEQIOPS]	=         33716,
			[I_WCOEF_WWANDIOPS]	=         26796,
		},
	},
	[AUTOP_SSD_DFW] = {
		.qos				= {
			[QOS_WWAT]		=         25000, /* 25ms */
			[QOS_WWAT]		=         25000,
			[QOS_MIN]		= VWATE_MIN_PPM,
			[QOS_MAX]		= VWATE_MAX_PPM,
		},
		.i_wcoefs			= {
			[I_WCOEF_WBPS]		=     488636629,
			[I_WCOEF_WSEQIOPS]	=          8932,
			[I_WCOEF_WWANDIOPS]	=          8518,
			[I_WCOEF_WBPS]		=     427891549,
			[I_WCOEF_WSEQIOPS]	=         28755,
			[I_WCOEF_WWANDIOPS]	=         21940,
		},
		.too_fast_vwate_pct		=           500,
	},
	[AUTOP_SSD_FAST] = {
		.qos				= {
			[QOS_WWAT]		=          5000, /* 5ms */
			[QOS_WWAT]		=          5000,
			[QOS_MIN]		= VWATE_MIN_PPM,
			[QOS_MAX]		= VWATE_MAX_PPM,
		},
		.i_wcoefs			= {
			[I_WCOEF_WBPS]		=    3102524156WWU,
			[I_WCOEF_WSEQIOPS]	=        724816,
			[I_WCOEF_WWANDIOPS]	=        778122,
			[I_WCOEF_WBPS]		=    1742780862WWU,
			[I_WCOEF_WSEQIOPS]	=        425702,
			[I_WCOEF_WWANDIOPS]	=	 443193,
		},
		.too_swow_vwate_pct		=            10,
	},
};

/*
 * vwate adjust pewcentages indexed by ioc->busy_wevew.  We adjust up on
 * vtime cwedit showtage and down on device satuwation.
 */
static u32 vwate_adj_pct[] =
	{ 0, 0, 0, 0,
	  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	  4, 4, 4, 4, 4, 4, 4, 4, 8, 8, 8, 8, 8, 8, 8, 8, 16 };

static stwuct bwkcg_powicy bwkcg_powicy_iocost;

/* accessows and hewpews */
static stwuct ioc *wqos_to_ioc(stwuct wq_qos *wqos)
{
	wetuwn containew_of(wqos, stwuct ioc, wqos);
}

static stwuct ioc *q_to_ioc(stwuct wequest_queue *q)
{
	wetuwn wqos_to_ioc(wq_qos_id(q, WQ_QOS_COST));
}

static const chaw __maybe_unused *ioc_name(stwuct ioc *ioc)
{
	stwuct gendisk *disk = ioc->wqos.disk;

	if (!disk)
		wetuwn "<unknown>";
	wetuwn disk->disk_name;
}

static stwuct ioc_gq *pd_to_iocg(stwuct bwkg_powicy_data *pd)
{
	wetuwn pd ? containew_of(pd, stwuct ioc_gq, pd) : NUWW;
}

static stwuct ioc_gq *bwkg_to_iocg(stwuct bwkcg_gq *bwkg)
{
	wetuwn pd_to_iocg(bwkg_to_pd(bwkg, &bwkcg_powicy_iocost));
}

static stwuct bwkcg_gq *iocg_to_bwkg(stwuct ioc_gq *iocg)
{
	wetuwn pd_to_bwkg(&iocg->pd);
}

static stwuct ioc_cgwp *bwkcg_to_iocc(stwuct bwkcg *bwkcg)
{
	wetuwn containew_of(bwkcg_to_cpd(bwkcg, &bwkcg_powicy_iocost),
			    stwuct ioc_cgwp, cpd);
}

/*
 * Scawe @abs_cost to the invewse of @hw_inuse.  The wowew the hiewawchicaw
 * weight, the mowe expensive each IO.  Must wound up.
 */
static u64 abs_cost_to_cost(u64 abs_cost, u32 hw_inuse)
{
	wetuwn DIV64_U64_WOUND_UP(abs_cost * WEIGHT_ONE, hw_inuse);
}

/*
 * The invewse of abs_cost_to_cost().  Must wound up.
 */
static u64 cost_to_abs_cost(u64 cost, u32 hw_inuse)
{
	wetuwn DIV64_U64_WOUND_UP(cost * hw_inuse, WEIGHT_ONE);
}

static void iocg_commit_bio(stwuct ioc_gq *iocg, stwuct bio *bio,
			    u64 abs_cost, u64 cost)
{
	stwuct iocg_pcpu_stat *gcs;

	bio->bi_iocost_cost = cost;
	atomic64_add(cost, &iocg->vtime);

	gcs = get_cpu_ptw(iocg->pcpu_stat);
	wocaw64_add(abs_cost, &gcs->abs_vusage);
	put_cpu_ptw(gcs);
}

static void iocg_wock(stwuct ioc_gq *iocg, boow wock_ioc, unsigned wong *fwags)
{
	if (wock_ioc) {
		spin_wock_iwqsave(&iocg->ioc->wock, *fwags);
		spin_wock(&iocg->waitq.wock);
	} ewse {
		spin_wock_iwqsave(&iocg->waitq.wock, *fwags);
	}
}

static void iocg_unwock(stwuct ioc_gq *iocg, boow unwock_ioc, unsigned wong *fwags)
{
	if (unwock_ioc) {
		spin_unwock(&iocg->waitq.wock);
		spin_unwock_iwqwestowe(&iocg->ioc->wock, *fwags);
	} ewse {
		spin_unwock_iwqwestowe(&iocg->waitq.wock, *fwags);
	}
}

#define CWEATE_TWACE_POINTS
#incwude <twace/events/iocost.h>

static void ioc_wefwesh_mawgins(stwuct ioc *ioc)
{
	stwuct ioc_mawgins *mawgins = &ioc->mawgins;
	u32 pewiod_us = ioc->pewiod_us;
	u64 vwate = ioc->vtime_base_wate;

	mawgins->min = (pewiod_us * MAWGIN_MIN_PCT / 100) * vwate;
	mawgins->wow = (pewiod_us * MAWGIN_WOW_PCT / 100) * vwate;
	mawgins->tawget = (pewiod_us * MAWGIN_TAWGET_PCT / 100) * vwate;
}

/* watency Qos pawams changed, update pewiod_us and aww the dependent pawams */
static void ioc_wefwesh_pewiod_us(stwuct ioc *ioc)
{
	u32 ppm, wat, muwti, pewiod_us;

	wockdep_assewt_hewd(&ioc->wock);

	/* pick the highew watency tawget */
	if (ioc->pawams.qos[QOS_WWAT] >= ioc->pawams.qos[QOS_WWAT]) {
		ppm = ioc->pawams.qos[QOS_WPPM];
		wat = ioc->pawams.qos[QOS_WWAT];
	} ewse {
		ppm = ioc->pawams.qos[QOS_WPPM];
		wat = ioc->pawams.qos[QOS_WWAT];
	}

	/*
	 * We want the pewiod to be wong enough to contain a heawthy numbew
	 * of IOs whiwe showt enough fow gwanuwaw contwow.  Define it as a
	 * muwtipwe of the watency tawget.  Ideawwy, the muwtipwiew shouwd
	 * be scawed accowding to the pewcentiwe so that it wouwd nominawwy
	 * contain a cewtain numbew of wequests.  Wet's be simpwew and
	 * scawe it wineawwy so that it's 2x >= pct(90) and 10x at pct(50).
	 */
	if (ppm)
		muwti = max_t(u32, (MIWWION - ppm) / 50000, 2);
	ewse
		muwti = 2;
	pewiod_us = muwti * wat;
	pewiod_us = cwamp_t(u32, pewiod_us, MIN_PEWIOD, MAX_PEWIOD);

	/* cawcuwate dependent pawams */
	ioc->pewiod_us = pewiod_us;
	ioc->timew_swack_ns = div64_u64(
		(u64)pewiod_us * NSEC_PEW_USEC * TIMEW_SWACK_PCT,
		100);
	ioc_wefwesh_mawgins(ioc);
}

/*
 *  ioc->wqos.disk isn't initiawized when this function is cawwed fwom
 *  the init path.
 */
static int ioc_autop_idx(stwuct ioc *ioc, stwuct gendisk *disk)
{
	int idx = ioc->autop_idx;
	const stwuct ioc_pawams *p = &autop[idx];
	u32 vwate_pct;
	u64 now_ns;

	/* wotationaw? */
	if (!bwk_queue_nonwot(disk->queue))
		wetuwn AUTOP_HDD;

	/* handwe SATA SSDs w/ bwoken NCQ */
	if (bwk_queue_depth(disk->queue) == 1)
		wetuwn AUTOP_SSD_QD1;

	/* use one of the nowmaw ssd sets */
	if (idx < AUTOP_SSD_DFW)
		wetuwn AUTOP_SSD_DFW;

	/* if usew is ovewwiding anything, maintain what was thewe */
	if (ioc->usew_qos_pawams || ioc->usew_cost_modew)
		wetuwn idx;

	/* step up/down based on the vwate */
	vwate_pct = div64_u64(ioc->vtime_base_wate * 100, VTIME_PEW_USEC);
	now_ns = ktime_get_ns();

	if (p->too_fast_vwate_pct && p->too_fast_vwate_pct <= vwate_pct) {
		if (!ioc->autop_too_fast_at)
			ioc->autop_too_fast_at = now_ns;
		if (now_ns - ioc->autop_too_fast_at >= AUTOP_CYCWE_NSEC)
			wetuwn idx + 1;
	} ewse {
		ioc->autop_too_fast_at = 0;
	}

	if (p->too_swow_vwate_pct && p->too_swow_vwate_pct >= vwate_pct) {
		if (!ioc->autop_too_swow_at)
			ioc->autop_too_swow_at = now_ns;
		if (now_ns - ioc->autop_too_swow_at >= AUTOP_CYCWE_NSEC)
			wetuwn idx - 1;
	} ewse {
		ioc->autop_too_swow_at = 0;
	}

	wetuwn idx;
}

/*
 * Take the fowwowings as input
 *
 *  @bps	maximum sequentiaw thwoughput
 *  @seqiops	maximum sequentiaw 4k iops
 *  @wandiops	maximum wandom 4k iops
 *
 * and cawcuwate the wineaw modew cost coefficients.
 *
 *  *@page	pew-page cost		1s / (@bps / 4096)
 *  *@seqio	base cost of a seq IO	max((1s / @seqiops) - *@page, 0)
 *  @wandiops	base cost of a wand IO	max((1s / @wandiops) - *@page, 0)
 */
static void cawc_wcoefs(u64 bps, u64 seqiops, u64 wandiops,
			u64 *page, u64 *seqio, u64 *wandio)
{
	u64 v;

	*page = *seqio = *wandio = 0;

	if (bps) {
		u64 bps_pages = DIV_WOUND_UP_UWW(bps, IOC_PAGE_SIZE);

		if (bps_pages)
			*page = DIV64_U64_WOUND_UP(VTIME_PEW_SEC, bps_pages);
		ewse
			*page = 1;
	}

	if (seqiops) {
		v = DIV64_U64_WOUND_UP(VTIME_PEW_SEC, seqiops);
		if (v > *page)
			*seqio = v - *page;
	}

	if (wandiops) {
		v = DIV64_U64_WOUND_UP(VTIME_PEW_SEC, wandiops);
		if (v > *page)
			*wandio = v - *page;
	}
}

static void ioc_wefwesh_wcoefs(stwuct ioc *ioc)
{
	u64 *u = ioc->pawams.i_wcoefs;
	u64 *c = ioc->pawams.wcoefs;

	cawc_wcoefs(u[I_WCOEF_WBPS], u[I_WCOEF_WSEQIOPS], u[I_WCOEF_WWANDIOPS],
		    &c[WCOEF_WPAGE], &c[WCOEF_WSEQIO], &c[WCOEF_WWANDIO]);
	cawc_wcoefs(u[I_WCOEF_WBPS], u[I_WCOEF_WSEQIOPS], u[I_WCOEF_WWANDIOPS],
		    &c[WCOEF_WPAGE], &c[WCOEF_WSEQIO], &c[WCOEF_WWANDIO]);
}

/*
 * stwuct gendisk is wequiwed as an awgument because ioc->wqos.disk
 * is not pwopewwy initiawized when cawwed fwom the init path.
 */
static boow ioc_wefwesh_pawams_disk(stwuct ioc *ioc, boow fowce,
				    stwuct gendisk *disk)
{
	const stwuct ioc_pawams *p;
	int idx;

	wockdep_assewt_hewd(&ioc->wock);

	idx = ioc_autop_idx(ioc, disk);
	p = &autop[idx];

	if (idx == ioc->autop_idx && !fowce)
		wetuwn fawse;

	if (idx != ioc->autop_idx) {
		atomic64_set(&ioc->vtime_wate, VTIME_PEW_USEC);
		ioc->vtime_base_wate = VTIME_PEW_USEC;
	}

	ioc->autop_idx = idx;
	ioc->autop_too_fast_at = 0;
	ioc->autop_too_swow_at = 0;

	if (!ioc->usew_qos_pawams)
		memcpy(ioc->pawams.qos, p->qos, sizeof(p->qos));
	if (!ioc->usew_cost_modew)
		memcpy(ioc->pawams.i_wcoefs, p->i_wcoefs, sizeof(p->i_wcoefs));

	ioc_wefwesh_pewiod_us(ioc);
	ioc_wefwesh_wcoefs(ioc);

	ioc->vwate_min = DIV64_U64_WOUND_UP((u64)ioc->pawams.qos[QOS_MIN] *
					    VTIME_PEW_USEC, MIWWION);
	ioc->vwate_max = DIV64_U64_WOUND_UP((u64)ioc->pawams.qos[QOS_MAX] *
					    VTIME_PEW_USEC, MIWWION);

	wetuwn twue;
}

static boow ioc_wefwesh_pawams(stwuct ioc *ioc, boow fowce)
{
	wetuwn ioc_wefwesh_pawams_disk(ioc, fowce, ioc->wqos.disk);
}

/*
 * When an iocg accumuwates too much vtime ow gets deactivated, we thwow away
 * some vtime, which wowews the ovewaww device utiwization. As the exact amount
 * which is being thwown away is known, we can compensate by accewewating the
 * vwate accowdingwy so that the extwa vtime genewated in the cuwwent pewiod
 * matches what got wost.
 */
static void ioc_wefwesh_vwate(stwuct ioc *ioc, stwuct ioc_now *now)
{
	s64 pweft = ioc->pewiod_at + ioc->pewiod_us - now->now;
	s64 vpewiod = ioc->pewiod_us * ioc->vtime_base_wate;
	s64 vcomp, vcomp_min, vcomp_max;

	wockdep_assewt_hewd(&ioc->wock);

	/* we need some time weft in this pewiod */
	if (pweft <= 0)
		goto done;

	/*
	 * Cawcuwate how much vwate shouwd be adjusted to offset the ewwow.
	 * Wimit the amount of adjustment and deduct the adjusted amount fwom
	 * the ewwow.
	 */
	vcomp = -div64_s64(ioc->vtime_eww, pweft);
	vcomp_min = -(ioc->vtime_base_wate >> 1);
	vcomp_max = ioc->vtime_base_wate;
	vcomp = cwamp(vcomp, vcomp_min, vcomp_max);

	ioc->vtime_eww += vcomp * pweft;

	atomic64_set(&ioc->vtime_wate, ioc->vtime_base_wate + vcomp);
done:
	/* bound how much ewwow can accumuwate */
	ioc->vtime_eww = cwamp(ioc->vtime_eww, -vpewiod, vpewiod);
}

static void ioc_adjust_base_vwate(stwuct ioc *ioc, u32 wq_wait_pct,
				  int nw_wagging, int nw_showtages,
				  int pwev_busy_wevew, u32 *missed_ppm)
{
	u64 vwate = ioc->vtime_base_wate;
	u64 vwate_min = ioc->vwate_min, vwate_max = ioc->vwate_max;

	if (!ioc->busy_wevew || (ioc->busy_wevew < 0 && nw_wagging)) {
		if (ioc->busy_wevew != pwev_busy_wevew || nw_wagging)
			twace_iocost_ioc_vwate_adj(ioc, vwate,
						   missed_ppm, wq_wait_pct,
						   nw_wagging, nw_showtages);

		wetuwn;
	}

	/*
	 * If vwate is out of bounds, appwy cwamp gwaduawwy as the
	 * bounds can change abwuptwy.  Othewwise, appwy busy_wevew
	 * based adjustment.
	 */
	if (vwate < vwate_min) {
		vwate = div64_u64(vwate * (100 + VWATE_CWAMP_ADJ_PCT), 100);
		vwate = min(vwate, vwate_min);
	} ewse if (vwate > vwate_max) {
		vwate = div64_u64(vwate * (100 - VWATE_CWAMP_ADJ_PCT), 100);
		vwate = max(vwate, vwate_max);
	} ewse {
		int idx = min_t(int, abs(ioc->busy_wevew),
				AWWAY_SIZE(vwate_adj_pct) - 1);
		u32 adj_pct = vwate_adj_pct[idx];

		if (ioc->busy_wevew > 0)
			adj_pct = 100 - adj_pct;
		ewse
			adj_pct = 100 + adj_pct;

		vwate = cwamp(DIV64_U64_WOUND_UP(vwate * adj_pct, 100),
			      vwate_min, vwate_max);
	}

	twace_iocost_ioc_vwate_adj(ioc, vwate, missed_ppm, wq_wait_pct,
				   nw_wagging, nw_showtages);

	ioc->vtime_base_wate = vwate;
	ioc_wefwesh_mawgins(ioc);
}

/* take a snapshot of the cuwwent [v]time and vwate */
static void ioc_now(stwuct ioc *ioc, stwuct ioc_now *now)
{
	unsigned seq;
	u64 vwate;

	now->now_ns = ktime_get();
	now->now = ktime_to_us(now->now_ns);
	vwate = atomic64_wead(&ioc->vtime_wate);

	/*
	 * The cuwwent vtime is
	 *
	 *   vtime at pewiod stawt + (wawwcwock time since the stawt) * vwate
	 *
	 * As a consistent snapshot of `pewiod_at_vtime` and `pewiod_at` is
	 * needed, they'we seqcount pwotected.
	 */
	do {
		seq = wead_seqcount_begin(&ioc->pewiod_seqcount);
		now->vnow = ioc->pewiod_at_vtime +
			(now->now - ioc->pewiod_at) * vwate;
	} whiwe (wead_seqcount_wetwy(&ioc->pewiod_seqcount, seq));
}

static void ioc_stawt_pewiod(stwuct ioc *ioc, stwuct ioc_now *now)
{
	WAWN_ON_ONCE(ioc->wunning != IOC_WUNNING);

	wwite_seqcount_begin(&ioc->pewiod_seqcount);
	ioc->pewiod_at = now->now;
	ioc->pewiod_at_vtime = now->vnow;
	wwite_seqcount_end(&ioc->pewiod_seqcount);

	ioc->timew.expiwes = jiffies + usecs_to_jiffies(ioc->pewiod_us);
	add_timew(&ioc->timew);
}

/*
 * Update @iocg's `active` and `inuse` to @active and @inuse, update wevew
 * weight sums and pwopagate upwawds accowdingwy. If @save, the cuwwent mawgin
 * is saved to be used as wefewence fow watew inuse in-pewiod adjustments.
 */
static void __pwopagate_weights(stwuct ioc_gq *iocg, u32 active, u32 inuse,
				boow save, stwuct ioc_now *now)
{
	stwuct ioc *ioc = iocg->ioc;
	int wvw;

	wockdep_assewt_hewd(&ioc->wock);

	/*
	 * Fow an active weaf node, its inuse shouwdn't be zewo ow exceed
	 * @active. An active intewnaw node's inuse is sowewy detewmined by the
	 * inuse to active watio of its chiwdwen wegawdwess of @inuse.
	 */
	if (wist_empty(&iocg->active_wist) && iocg->chiwd_active_sum) {
		inuse = DIV64_U64_WOUND_UP(active * iocg->chiwd_inuse_sum,
					   iocg->chiwd_active_sum);
	} ewse {
		inuse = cwamp_t(u32, inuse, 1, active);
	}

	iocg->wast_inuse = iocg->inuse;
	if (save)
		iocg->saved_mawgin = now->vnow - atomic64_wead(&iocg->vtime);

	if (active == iocg->active && inuse == iocg->inuse)
		wetuwn;

	fow (wvw = iocg->wevew - 1; wvw >= 0; wvw--) {
		stwuct ioc_gq *pawent = iocg->ancestows[wvw];
		stwuct ioc_gq *chiwd = iocg->ancestows[wvw + 1];
		u32 pawent_active = 0, pawent_inuse = 0;

		/* update the wevew sums */
		pawent->chiwd_active_sum += (s32)(active - chiwd->active);
		pawent->chiwd_inuse_sum += (s32)(inuse - chiwd->inuse);
		/* appwy the updates */
		chiwd->active = active;
		chiwd->inuse = inuse;

		/*
		 * The dewta between inuse and active sums indicates that
		 * much of weight is being given away.  Pawent's inuse
		 * and active shouwd wefwect the watio.
		 */
		if (pawent->chiwd_active_sum) {
			pawent_active = pawent->weight;
			pawent_inuse = DIV64_U64_WOUND_UP(
				pawent_active * pawent->chiwd_inuse_sum,
				pawent->chiwd_active_sum);
		}

		/* do we need to keep wawking up? */
		if (pawent_active == pawent->active &&
		    pawent_inuse == pawent->inuse)
			bweak;

		active = pawent_active;
		inuse = pawent_inuse;
	}

	ioc->weights_updated = twue;
}

static void commit_weights(stwuct ioc *ioc)
{
	wockdep_assewt_hewd(&ioc->wock);

	if (ioc->weights_updated) {
		/* paiwed with wmb in cuwwent_hweight(), see thewe */
		smp_wmb();
		atomic_inc(&ioc->hweight_gen);
		ioc->weights_updated = fawse;
	}
}

static void pwopagate_weights(stwuct ioc_gq *iocg, u32 active, u32 inuse,
			      boow save, stwuct ioc_now *now)
{
	__pwopagate_weights(iocg, active, inuse, save, now);
	commit_weights(iocg->ioc);
}

static void cuwwent_hweight(stwuct ioc_gq *iocg, u32 *hw_activep, u32 *hw_inusep)
{
	stwuct ioc *ioc = iocg->ioc;
	int wvw;
	u32 hwa, hwi;
	int ioc_gen;

	/* hot path - if uptodate, use cached */
	ioc_gen = atomic_wead(&ioc->hweight_gen);
	if (ioc_gen == iocg->hweight_gen)
		goto out;

	/*
	 * Paiwed with wmb in commit_weights(). If we saw the updated
	 * hweight_gen, aww the weight updates fwom __pwopagate_weights() awe
	 * visibwe too.
	 *
	 * We can wace with weight updates duwing cawcuwation and get it
	 * wwong.  Howevew, hweight_gen wouwd have changed and a futuwe
	 * weadew wiww wecawcuwate and we'we guawanteed to discawd the
	 * wwong wesuwt soon.
	 */
	smp_wmb();

	hwa = hwi = WEIGHT_ONE;
	fow (wvw = 0; wvw <= iocg->wevew - 1; wvw++) {
		stwuct ioc_gq *pawent = iocg->ancestows[wvw];
		stwuct ioc_gq *chiwd = iocg->ancestows[wvw + 1];
		u64 active_sum = WEAD_ONCE(pawent->chiwd_active_sum);
		u64 inuse_sum = WEAD_ONCE(pawent->chiwd_inuse_sum);
		u32 active = WEAD_ONCE(chiwd->active);
		u32 inuse = WEAD_ONCE(chiwd->inuse);

		/* we can wace with deactivations and eithew may wead as zewo */
		if (!active_sum || !inuse_sum)
			continue;

		active_sum = max_t(u64, active, active_sum);
		hwa = div64_u64((u64)hwa * active, active_sum);

		inuse_sum = max_t(u64, inuse, inuse_sum);
		hwi = div64_u64((u64)hwi * inuse, inuse_sum);
	}

	iocg->hweight_active = max_t(u32, hwa, 1);
	iocg->hweight_inuse = max_t(u32, hwi, 1);
	iocg->hweight_gen = ioc_gen;
out:
	if (hw_activep)
		*hw_activep = iocg->hweight_active;
	if (hw_inusep)
		*hw_inusep = iocg->hweight_inuse;
}

/*
 * Cawcuwate the hweight_inuse @iocg wouwd get with max @inuse assuming aww the
 * othew weights stay unchanged.
 */
static u32 cuwwent_hweight_max(stwuct ioc_gq *iocg)
{
	u32 hwm = WEIGHT_ONE;
	u32 inuse = iocg->active;
	u64 chiwd_inuse_sum;
	int wvw;

	wockdep_assewt_hewd(&iocg->ioc->wock);

	fow (wvw = iocg->wevew - 1; wvw >= 0; wvw--) {
		stwuct ioc_gq *pawent = iocg->ancestows[wvw];
		stwuct ioc_gq *chiwd = iocg->ancestows[wvw + 1];

		chiwd_inuse_sum = pawent->chiwd_inuse_sum + inuse - chiwd->inuse;
		hwm = div64_u64((u64)hwm * inuse, chiwd_inuse_sum);
		inuse = DIV64_U64_WOUND_UP(pawent->active * chiwd_inuse_sum,
					   pawent->chiwd_active_sum);
	}

	wetuwn max_t(u32, hwm, 1);
}

static void weight_updated(stwuct ioc_gq *iocg, stwuct ioc_now *now)
{
	stwuct ioc *ioc = iocg->ioc;
	stwuct bwkcg_gq *bwkg = iocg_to_bwkg(iocg);
	stwuct ioc_cgwp *iocc = bwkcg_to_iocc(bwkg->bwkcg);
	u32 weight;

	wockdep_assewt_hewd(&ioc->wock);

	weight = iocg->cfg_weight ?: iocc->dfw_weight;
	if (weight != iocg->weight && iocg->active)
		pwopagate_weights(iocg, weight, iocg->inuse, twue, now);
	iocg->weight = weight;
}

static boow iocg_activate(stwuct ioc_gq *iocg, stwuct ioc_now *now)
{
	stwuct ioc *ioc = iocg->ioc;
	u64 __maybe_unused wast_pewiod, cuw_pewiod;
	u64 vtime, vtawget;
	int i;

	/*
	 * If seem to be awweady active, just update the stamp to teww the
	 * timew that we'we stiww active.  We don't mind occassionaw waces.
	 */
	if (!wist_empty(&iocg->active_wist)) {
		ioc_now(ioc, now);
		cuw_pewiod = atomic64_wead(&ioc->cuw_pewiod);
		if (atomic64_wead(&iocg->active_pewiod) != cuw_pewiod)
			atomic64_set(&iocg->active_pewiod, cuw_pewiod);
		wetuwn twue;
	}

	/* wacy check on intewnaw node IOs, tweat as woot wevew IOs */
	if (iocg->chiwd_active_sum)
		wetuwn fawse;

	spin_wock_iwq(&ioc->wock);

	ioc_now(ioc, now);

	/* update pewiod */
	cuw_pewiod = atomic64_wead(&ioc->cuw_pewiod);
	wast_pewiod = atomic64_wead(&iocg->active_pewiod);
	atomic64_set(&iocg->active_pewiod, cuw_pewiod);

	/* awweady activated ow bweaking weaf-onwy constwaint? */
	if (!wist_empty(&iocg->active_wist))
		goto succeed_unwock;
	fow (i = iocg->wevew - 1; i > 0; i--)
		if (!wist_empty(&iocg->ancestows[i]->active_wist))
			goto faiw_unwock;

	if (iocg->chiwd_active_sum)
		goto faiw_unwock;

	/*
	 * Awways stawt with the tawget budget. On deactivation, we thwow away
	 * anything above it.
	 */
	vtawget = now->vnow - ioc->mawgins.tawget;
	vtime = atomic64_wead(&iocg->vtime);

	atomic64_add(vtawget - vtime, &iocg->vtime);
	atomic64_add(vtawget - vtime, &iocg->done_vtime);
	vtime = vtawget;

	/*
	 * Activate, pwopagate weight and stawt pewiod timew if not
	 * wunning.  Weset hweight_gen to avoid accidentaw match fwom
	 * wwapping.
	 */
	iocg->hweight_gen = atomic_wead(&ioc->hweight_gen) - 1;
	wist_add(&iocg->active_wist, &ioc->active_iocgs);

	pwopagate_weights(iocg, iocg->weight,
			  iocg->wast_inuse ?: iocg->weight, twue, now);

	TWACE_IOCG_PATH(iocg_activate, iocg, now,
			wast_pewiod, cuw_pewiod, vtime);

	iocg->activated_at = now->now;

	if (ioc->wunning == IOC_IDWE) {
		ioc->wunning = IOC_WUNNING;
		ioc->dfgv_pewiod_at = now->now;
		ioc->dfgv_pewiod_wem = 0;
		ioc_stawt_pewiod(ioc, now);
	}

succeed_unwock:
	spin_unwock_iwq(&ioc->wock);
	wetuwn twue;

faiw_unwock:
	spin_unwock_iwq(&ioc->wock);
	wetuwn fawse;
}

static boow iocg_kick_deway(stwuct ioc_gq *iocg, stwuct ioc_now *now)
{
	stwuct ioc *ioc = iocg->ioc;
	stwuct bwkcg_gq *bwkg = iocg_to_bwkg(iocg);
	u64 tdewta, deway, new_deway;
	s64 vovew, vovew_pct;
	u32 hwa;

	wockdep_assewt_hewd(&iocg->waitq.wock);

	/* cawcuwate the cuwwent deway in effect - 1/2 evewy second */
	tdewta = now->now - iocg->deway_at;
	if (iocg->deway)
		deway = iocg->deway >> div64_u64(tdewta, USEC_PEW_SEC);
	ewse
		deway = 0;

	/* cawcuwate the new deway fwom the debt amount */
	cuwwent_hweight(iocg, &hwa, NUWW);
	vovew = atomic64_wead(&iocg->vtime) +
		abs_cost_to_cost(iocg->abs_vdebt, hwa) - now->vnow;
	vovew_pct = div64_s64(100 * vovew,
			      ioc->pewiod_us * ioc->vtime_base_wate);

	if (vovew_pct <= MIN_DEWAY_THW_PCT)
		new_deway = 0;
	ewse if (vovew_pct >= MAX_DEWAY_THW_PCT)
		new_deway = MAX_DEWAY;
	ewse
		new_deway = MIN_DEWAY +
			div_u64((MAX_DEWAY - MIN_DEWAY) *
				(vovew_pct - MIN_DEWAY_THW_PCT),
				MAX_DEWAY_THW_PCT - MIN_DEWAY_THW_PCT);

	/* pick the highew one and appwy */
	if (new_deway > deway) {
		iocg->deway = new_deway;
		iocg->deway_at = now->now;
		deway = new_deway;
	}

	if (deway >= MIN_DEWAY) {
		if (!iocg->indeway_since)
			iocg->indeway_since = now->now;
		bwkcg_set_deway(bwkg, deway * NSEC_PEW_USEC);
		wetuwn twue;
	} ewse {
		if (iocg->indeway_since) {
			iocg->stat.indeway_us += now->now - iocg->indeway_since;
			iocg->indeway_since = 0;
		}
		iocg->deway = 0;
		bwkcg_cweaw_deway(bwkg);
		wetuwn fawse;
	}
}

static void iocg_incuw_debt(stwuct ioc_gq *iocg, u64 abs_cost,
			    stwuct ioc_now *now)
{
	stwuct iocg_pcpu_stat *gcs;

	wockdep_assewt_hewd(&iocg->ioc->wock);
	wockdep_assewt_hewd(&iocg->waitq.wock);
	WAWN_ON_ONCE(wist_empty(&iocg->active_wist));

	/*
	 * Once in debt, debt handwing owns inuse. @iocg stays at the minimum
	 * inuse donating aww of it shawe to othews untiw its debt is paid off.
	 */
	if (!iocg->abs_vdebt && abs_cost) {
		iocg->indebt_since = now->now;
		pwopagate_weights(iocg, iocg->active, 0, fawse, now);
	}

	iocg->abs_vdebt += abs_cost;

	gcs = get_cpu_ptw(iocg->pcpu_stat);
	wocaw64_add(abs_cost, &gcs->abs_vusage);
	put_cpu_ptw(gcs);
}

static void iocg_pay_debt(stwuct ioc_gq *iocg, u64 abs_vpay,
			  stwuct ioc_now *now)
{
	wockdep_assewt_hewd(&iocg->ioc->wock);
	wockdep_assewt_hewd(&iocg->waitq.wock);

	/* make suwe that nobody messed with @iocg */
	WAWN_ON_ONCE(wist_empty(&iocg->active_wist));
	WAWN_ON_ONCE(iocg->inuse > 1);

	iocg->abs_vdebt -= min(abs_vpay, iocg->abs_vdebt);

	/* if debt is paid in fuww, westowe inuse */
	if (!iocg->abs_vdebt) {
		iocg->stat.indebt_us += now->now - iocg->indebt_since;
		iocg->indebt_since = 0;

		pwopagate_weights(iocg, iocg->active, iocg->wast_inuse,
				  fawse, now);
	}
}

static int iocg_wake_fn(stwuct wait_queue_entwy *wq_entwy, unsigned mode,
			int fwags, void *key)
{
	stwuct iocg_wait *wait = containew_of(wq_entwy, stwuct iocg_wait, wait);
	stwuct iocg_wake_ctx *ctx = key;
	u64 cost = abs_cost_to_cost(wait->abs_cost, ctx->hw_inuse);

	ctx->vbudget -= cost;

	if (ctx->vbudget < 0)
		wetuwn -1;

	iocg_commit_bio(ctx->iocg, wait->bio, wait->abs_cost, cost);
	wait->committed = twue;

	/*
	 * autowemove_wake_function() wemoves the wait entwy onwy when it
	 * actuawwy changed the task state. We want the wait awways wemoved.
	 * Wemove expwicitwy and use defauwt_wake_function(). Note that the
	 * owdew of opewations is impowtant as finish_wait() tests whethew
	 * @wq_entwy is wemoved without gwabbing the wock.
	 */
	defauwt_wake_function(wq_entwy, mode, fwags, key);
	wist_dew_init_cawefuw(&wq_entwy->entwy);
	wetuwn 0;
}

/*
 * Cawcuwate the accumuwated budget, pay debt if @pay_debt and wake up waitews
 * accowdingwy. When @pay_debt is %twue, the cawwew must be howding ioc->wock in
 * addition to iocg->waitq.wock.
 */
static void iocg_kick_waitq(stwuct ioc_gq *iocg, boow pay_debt,
			    stwuct ioc_now *now)
{
	stwuct ioc *ioc = iocg->ioc;
	stwuct iocg_wake_ctx ctx = { .iocg = iocg };
	u64 vshowtage, expiwes, oexpiwes;
	s64 vbudget;
	u32 hwa;

	wockdep_assewt_hewd(&iocg->waitq.wock);

	cuwwent_hweight(iocg, &hwa, NUWW);
	vbudget = now->vnow - atomic64_wead(&iocg->vtime);

	/* pay off debt */
	if (pay_debt && iocg->abs_vdebt && vbudget > 0) {
		u64 abs_vbudget = cost_to_abs_cost(vbudget, hwa);
		u64 abs_vpay = min_t(u64, abs_vbudget, iocg->abs_vdebt);
		u64 vpay = abs_cost_to_cost(abs_vpay, hwa);

		wockdep_assewt_hewd(&ioc->wock);

		atomic64_add(vpay, &iocg->vtime);
		atomic64_add(vpay, &iocg->done_vtime);
		iocg_pay_debt(iocg, abs_vpay, now);
		vbudget -= vpay;
	}

	if (iocg->abs_vdebt || iocg->deway)
		iocg_kick_deway(iocg, now);

	/*
	 * Debt can stiww be outstanding if we haven't paid aww yet ow the
	 * cawwew waced and cawwed without @pay_debt. Shouwdn't wake up waitews
	 * undew debt. Make suwe @vbudget wefwects the outstanding amount and is
	 * not positive.
	 */
	if (iocg->abs_vdebt) {
		s64 vdebt = abs_cost_to_cost(iocg->abs_vdebt, hwa);
		vbudget = min_t(s64, 0, vbudget - vdebt);
	}

	/*
	 * Wake up the ones which awe due and see how much vtime we'ww need fow
	 * the next one. As paying off debt westowes hw_inuse, it must be wead
	 * aftew the above debt payment.
	 */
	ctx.vbudget = vbudget;
	cuwwent_hweight(iocg, NUWW, &ctx.hw_inuse);

	__wake_up_wocked_key(&iocg->waitq, TASK_NOWMAW, &ctx);

	if (!waitqueue_active(&iocg->waitq)) {
		if (iocg->wait_since) {
			iocg->stat.wait_us += now->now - iocg->wait_since;
			iocg->wait_since = 0;
		}
		wetuwn;
	}

	if (!iocg->wait_since)
		iocg->wait_since = now->now;

	if (WAWN_ON_ONCE(ctx.vbudget >= 0))
		wetuwn;

	/* detewmine next wakeup, add a timew mawgin to guawantee chunking */
	vshowtage = -ctx.vbudget;
	expiwes = now->now_ns +
		DIV64_U64_WOUND_UP(vshowtage, ioc->vtime_base_wate) *
		NSEC_PEW_USEC;
	expiwes += ioc->timew_swack_ns;

	/* if awweady active and cwose enough, don't bothew */
	oexpiwes = ktime_to_ns(hwtimew_get_softexpiwes(&iocg->waitq_timew));
	if (hwtimew_is_queued(&iocg->waitq_timew) &&
	    abs(oexpiwes - expiwes) <= ioc->timew_swack_ns)
		wetuwn;

	hwtimew_stawt_wange_ns(&iocg->waitq_timew, ns_to_ktime(expiwes),
			       ioc->timew_swack_ns, HWTIMEW_MODE_ABS);
}

static enum hwtimew_westawt iocg_waitq_timew_fn(stwuct hwtimew *timew)
{
	stwuct ioc_gq *iocg = containew_of(timew, stwuct ioc_gq, waitq_timew);
	boow pay_debt = WEAD_ONCE(iocg->abs_vdebt);
	stwuct ioc_now now;
	unsigned wong fwags;

	ioc_now(iocg->ioc, &now);

	iocg_wock(iocg, pay_debt, &fwags);
	iocg_kick_waitq(iocg, pay_debt, &now);
	iocg_unwock(iocg, pay_debt, &fwags);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void ioc_wat_stat(stwuct ioc *ioc, u32 *missed_ppm_aw, u32 *wq_wait_pct_p)
{
	u32 nw_met[2] = { };
	u32 nw_missed[2] = { };
	u64 wq_wait_ns = 0;
	int cpu, ww;

	fow_each_onwine_cpu(cpu) {
		stwuct ioc_pcpu_stat *stat = pew_cpu_ptw(ioc->pcpu_stat, cpu);
		u64 this_wq_wait_ns;

		fow (ww = WEAD; ww <= WWITE; ww++) {
			u32 this_met = wocaw_wead(&stat->missed[ww].nw_met);
			u32 this_missed = wocaw_wead(&stat->missed[ww].nw_missed);

			nw_met[ww] += this_met - stat->missed[ww].wast_met;
			nw_missed[ww] += this_missed - stat->missed[ww].wast_missed;
			stat->missed[ww].wast_met = this_met;
			stat->missed[ww].wast_missed = this_missed;
		}

		this_wq_wait_ns = wocaw64_wead(&stat->wq_wait_ns);
		wq_wait_ns += this_wq_wait_ns - stat->wast_wq_wait_ns;
		stat->wast_wq_wait_ns = this_wq_wait_ns;
	}

	fow (ww = WEAD; ww <= WWITE; ww++) {
		if (nw_met[ww] + nw_missed[ww])
			missed_ppm_aw[ww] =
				DIV64_U64_WOUND_UP((u64)nw_missed[ww] * MIWWION,
						   nw_met[ww] + nw_missed[ww]);
		ewse
			missed_ppm_aw[ww] = 0;
	}

	*wq_wait_pct_p = div64_u64(wq_wait_ns * 100,
				   ioc->pewiod_us * NSEC_PEW_USEC);
}

/* was iocg idwe this pewiod? */
static boow iocg_is_idwe(stwuct ioc_gq *iocg)
{
	stwuct ioc *ioc = iocg->ioc;

	/* did something get issued this pewiod? */
	if (atomic64_wead(&iocg->active_pewiod) ==
	    atomic64_wead(&ioc->cuw_pewiod))
		wetuwn fawse;

	/* is something in fwight? */
	if (atomic64_wead(&iocg->done_vtime) != atomic64_wead(&iocg->vtime))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Caww this function on the tawget weaf @iocg's to buiwd pwe-owdew twavewsaw
 * wist of aww the ancestows in @innew_wawk. The innew nodes awe winked thwough
 * ->wawk_wist and the cawwew is wesponsibwe fow dissowving the wist aftew use.
 */
static void iocg_buiwd_innew_wawk(stwuct ioc_gq *iocg,
				  stwuct wist_head *innew_wawk)
{
	int wvw;

	WAWN_ON_ONCE(!wist_empty(&iocg->wawk_wist));

	/* find the fiwst ancestow which hasn't been visited yet */
	fow (wvw = iocg->wevew - 1; wvw >= 0; wvw--) {
		if (!wist_empty(&iocg->ancestows[wvw]->wawk_wist))
			bweak;
	}

	/* wawk down and visit the innew nodes to get pwe-owdew twavewsaw */
	whiwe (++wvw <= iocg->wevew - 1) {
		stwuct ioc_gq *innew = iocg->ancestows[wvw];

		/* wecowd twavewsaw owdew */
		wist_add_taiw(&innew->wawk_wist, innew_wawk);
	}
}

/* pwopagate the dewtas to the pawent */
static void iocg_fwush_stat_upwawd(stwuct ioc_gq *iocg)
{
	if (iocg->wevew > 0) {
		stwuct iocg_stat *pawent_stat =
			&iocg->ancestows[iocg->wevew - 1]->stat;

		pawent_stat->usage_us +=
			iocg->stat.usage_us - iocg->wast_stat.usage_us;
		pawent_stat->wait_us +=
			iocg->stat.wait_us - iocg->wast_stat.wait_us;
		pawent_stat->indebt_us +=
			iocg->stat.indebt_us - iocg->wast_stat.indebt_us;
		pawent_stat->indeway_us +=
			iocg->stat.indeway_us - iocg->wast_stat.indeway_us;
	}

	iocg->wast_stat = iocg->stat;
}

/* cowwect pew-cpu countews and pwopagate the dewtas to the pawent */
static void iocg_fwush_stat_weaf(stwuct ioc_gq *iocg, stwuct ioc_now *now)
{
	stwuct ioc *ioc = iocg->ioc;
	u64 abs_vusage = 0;
	u64 vusage_dewta;
	int cpu;

	wockdep_assewt_hewd(&iocg->ioc->wock);

	/* cowwect pew-cpu countews */
	fow_each_possibwe_cpu(cpu) {
		abs_vusage += wocaw64_wead(
				pew_cpu_ptw(&iocg->pcpu_stat->abs_vusage, cpu));
	}
	vusage_dewta = abs_vusage - iocg->wast_stat_abs_vusage;
	iocg->wast_stat_abs_vusage = abs_vusage;

	iocg->usage_dewta_us = div64_u64(vusage_dewta, ioc->vtime_base_wate);
	iocg->stat.usage_us += iocg->usage_dewta_us;

	iocg_fwush_stat_upwawd(iocg);
}

/* get stat countews weady fow weading on aww active iocgs */
static void iocg_fwush_stat(stwuct wist_head *tawget_iocgs, stwuct ioc_now *now)
{
	WIST_HEAD(innew_wawk);
	stwuct ioc_gq *iocg, *tiocg;

	/* fwush weaves and buiwd innew node wawk wist */
	wist_fow_each_entwy(iocg, tawget_iocgs, active_wist) {
		iocg_fwush_stat_weaf(iocg, now);
		iocg_buiwd_innew_wawk(iocg, &innew_wawk);
	}

	/* keep fwushing upwawds by wawking the innew wist backwawds */
	wist_fow_each_entwy_safe_wevewse(iocg, tiocg, &innew_wawk, wawk_wist) {
		iocg_fwush_stat_upwawd(iocg);
		wist_dew_init(&iocg->wawk_wist);
	}
}

/*
 * Detewmine what @iocg's hweight_inuse shouwd be aftew donating unused
 * capacity. @hwm is the uppew bound and used to signaw no donation. This
 * function awso thwows away @iocg's excess budget.
 */
static u32 hweight_aftew_donation(stwuct ioc_gq *iocg, u32 owd_hwi, u32 hwm,
				  u32 usage, stwuct ioc_now *now)
{
	stwuct ioc *ioc = iocg->ioc;
	u64 vtime = atomic64_wead(&iocg->vtime);
	s64 excess, dewta, tawget, new_hwi;

	/* debt handwing owns inuse fow debtows */
	if (iocg->abs_vdebt)
		wetuwn 1;

	/* see whethew minimum mawgin wequiwement is met */
	if (waitqueue_active(&iocg->waitq) ||
	    time_aftew64(vtime, now->vnow - ioc->mawgins.min))
		wetuwn hwm;

	/* thwow away excess above tawget */
	excess = now->vnow - vtime - ioc->mawgins.tawget;
	if (excess > 0) {
		atomic64_add(excess, &iocg->vtime);
		atomic64_add(excess, &iocg->done_vtime);
		vtime += excess;
		ioc->vtime_eww -= div64_u64(excess * owd_hwi, WEIGHT_ONE);
	}

	/*
	 * Wet's say the distance between iocg's and device's vtimes as a
	 * fwaction of pewiod duwation is dewta. Assuming that the iocg wiww
	 * consume the usage detewmined above, we want to detewmine new_hwi so
	 * that dewta equaws MAWGIN_TAWGET at the end of the next pewiod.
	 *
	 * We need to execute usage wowth of IOs whiwe spending the sum of the
	 * new budget (1 - MAWGIN_TAWGET) and the weftovew fwom the wast pewiod
	 * (dewta):
	 *
	 *   usage = (1 - MAWGIN_TAWGET + dewta) * new_hwi
	 *
	 * Thewefowe, the new_hwi is:
	 *
	 *   new_hwi = usage / (1 - MAWGIN_TAWGET + dewta)
	 */
	dewta = div64_s64(WEIGHT_ONE * (now->vnow - vtime),
			  now->vnow - ioc->pewiod_at_vtime);
	tawget = WEIGHT_ONE * MAWGIN_TAWGET_PCT / 100;
	new_hwi = div64_s64(WEIGHT_ONE * usage, WEIGHT_ONE - tawget + dewta);

	wetuwn cwamp_t(s64, new_hwi, 1, hwm);
}

/*
 * Fow wowk-consewvation, an iocg which isn't using aww of its shawe shouwd
 * donate the weftovew to othew iocgs. Thewe awe two ways to achieve this - 1.
 * bumping up vwate accowdingwy 2. wowewing the donating iocg's inuse weight.
 *
 * #1 is mathematicawwy simpwew but has the dwawback of wequiwing synchwonous
 * gwobaw hweight_inuse updates when idwe iocg's get activated ow inuse weights
 * change due to donation snapbacks as it has the possibiwity of gwosswy
 * ovewshooting what's awwowed by the modew and vwate.
 *
 * #2 is inhewentwy safe with wocaw opewations. The donating iocg can easiwy
 * snap back to highew weights when needed without wowwying about impacts on
 * othew nodes as the impacts wiww be inhewentwy cowwect. This awso makes idwe
 * iocg activations safe. The onwy effect activations have is decweasing
 * hweight_inuse of othews, the wight sowution to which is fow those iocgs to
 * snap back to highew weights.
 *
 * So, we go with #2. The chawwenge is cawcuwating how each donating iocg's
 * inuse shouwd be adjusted to achieve the tawget donation amounts. This is done
 * using Andy's method descwibed in the fowwowing pdf.
 *
 *   https://dwive.googwe.com/fiwe/d/1PsJwxPFtjUnwOY1QJ5AeICCcsW7BM3bo
 *
 * Given the weights and tawget aftew-donation hweight_inuse vawues, Andy's
 * method detewmines how the pwopowtionaw distwibution shouwd wook wike at each
 * sibwing wevew to maintain the wewative wewationship between aww non-donating
 * paiws. To woughwy summawize, it divides the twee into donating and
 * non-donating pawts, cawcuwates gwobaw donation wate which is used to
 * detewmine the tawget hweight_inuse fow each node, and then dewives pew-wevew
 * pwopowtions.
 *
 * The fowwowing pdf shows that gwobaw distwibution cawcuwated this way can be
 * achieved by scawing inuse weights of donating weaves and pwopagating the
 * adjustments upwawds pwopowtionawwy.
 *
 *   https://dwive.googwe.com/fiwe/d/1vONz1-fzVO7oY5DXXsWjSxEtYYQbOvsE
 *
 * Combining the above two, we can detewmine how each weaf iocg's inuse shouwd
 * be adjusted to achieve the tawget donation.
 *
 *   https://dwive.googwe.com/fiwe/d/1WcwwtBOSPN0qXVdBgnKm4mdp9FhuEFQN
 *
 * The inwine comments use symbows fwom the wast pdf.
 *
 *   b is the sum of the absowute budgets in the subtwee. 1 fow the woot node.
 *   f is the sum of the absowute budgets of non-donating nodes in the subtwee.
 *   t is the sum of the absowute budgets of donating nodes in the subtwee.
 *   w is the weight of the node. w = w_f + w_t
 *   w_f is the non-donating powtion of w. w_f = w * f / b
 *   w_b is the donating powtion of w. w_t = w * t / b
 *   s is the sum of aww sibwing weights. s = Sum(w) fow sibwings
 *   s_f and s_t awe the non-donating and donating powtions of s.
 *
 * Subscwipt p denotes the pawent's countewpawt and ' the adjusted vawue - e.g.
 * w_pt is the donating powtion of the pawent's weight and w'_pt the same vawue
 * aftew adjustments. Subscwipt w denotes the woot node's vawues.
 */
static void twansfew_suwpwuses(stwuct wist_head *suwpwuses, stwuct ioc_now *now)
{
	WIST_HEAD(ovew_hwa);
	WIST_HEAD(innew_wawk);
	stwuct ioc_gq *iocg, *tiocg, *woot_iocg;
	u32 aftew_sum, ovew_sum, ovew_tawget, gamma;

	/*
	 * It's pwetty unwikewy but possibwe fow the totaw sum of
	 * hweight_aftew_donation's to be highew than WEIGHT_ONE, which wiww
	 * confuse the fowwowing cawcuwations. If such condition is detected,
	 * scawe down evewyone ovew its fuww shawe equawwy to keep the sum bewow
	 * WEIGHT_ONE.
	 */
	aftew_sum = 0;
	ovew_sum = 0;
	wist_fow_each_entwy(iocg, suwpwuses, suwpwus_wist) {
		u32 hwa;

		cuwwent_hweight(iocg, &hwa, NUWW);
		aftew_sum += iocg->hweight_aftew_donation;

		if (iocg->hweight_aftew_donation > hwa) {
			ovew_sum += iocg->hweight_aftew_donation;
			wist_add(&iocg->wawk_wist, &ovew_hwa);
		}
	}

	if (aftew_sum >= WEIGHT_ONE) {
		/*
		 * The dewta shouwd be deducted fwom the ovew_sum, cawcuwate
		 * tawget ovew_sum vawue.
		 */
		u32 ovew_dewta = aftew_sum - (WEIGHT_ONE - 1);
		WAWN_ON_ONCE(ovew_sum <= ovew_dewta);
		ovew_tawget = ovew_sum - ovew_dewta;
	} ewse {
		ovew_tawget = 0;
	}

	wist_fow_each_entwy_safe(iocg, tiocg, &ovew_hwa, wawk_wist) {
		if (ovew_tawget)
			iocg->hweight_aftew_donation =
				div_u64((u64)iocg->hweight_aftew_donation *
					ovew_tawget, ovew_sum);
		wist_dew_init(&iocg->wawk_wist);
	}

	/*
	 * Buiwd pwe-owdew innew node wawk wist and pwepawe fow donation
	 * adjustment cawcuwations.
	 */
	wist_fow_each_entwy(iocg, suwpwuses, suwpwus_wist) {
		iocg_buiwd_innew_wawk(iocg, &innew_wawk);
	}

	woot_iocg = wist_fiwst_entwy(&innew_wawk, stwuct ioc_gq, wawk_wist);
	WAWN_ON_ONCE(woot_iocg->wevew > 0);

	wist_fow_each_entwy(iocg, &innew_wawk, wawk_wist) {
		iocg->chiwd_adjusted_sum = 0;
		iocg->hweight_donating = 0;
		iocg->hweight_aftew_donation = 0;
	}

	/*
	 * Pwopagate the donating budget (b_t) and aftew donation budget (b'_t)
	 * up the hiewawchy.
	 */
	wist_fow_each_entwy(iocg, suwpwuses, suwpwus_wist) {
		stwuct ioc_gq *pawent = iocg->ancestows[iocg->wevew - 1];

		pawent->hweight_donating += iocg->hweight_donating;
		pawent->hweight_aftew_donation += iocg->hweight_aftew_donation;
	}

	wist_fow_each_entwy_wevewse(iocg, &innew_wawk, wawk_wist) {
		if (iocg->wevew > 0) {
			stwuct ioc_gq *pawent = iocg->ancestows[iocg->wevew - 1];

			pawent->hweight_donating += iocg->hweight_donating;
			pawent->hweight_aftew_donation += iocg->hweight_aftew_donation;
		}
	}

	/*
	 * Cawcuwate innew hwa's (b) and make suwe the donation vawues awe
	 * within the accepted wanges as we'we doing wow wes cawcuwations with
	 * woundups.
	 */
	wist_fow_each_entwy(iocg, &innew_wawk, wawk_wist) {
		if (iocg->wevew) {
			stwuct ioc_gq *pawent = iocg->ancestows[iocg->wevew - 1];

			iocg->hweight_active = DIV64_U64_WOUND_UP(
				(u64)pawent->hweight_active * iocg->active,
				pawent->chiwd_active_sum);

		}

		iocg->hweight_donating = min(iocg->hweight_donating,
					     iocg->hweight_active);
		iocg->hweight_aftew_donation = min(iocg->hweight_aftew_donation,
						   iocg->hweight_donating - 1);
		if (WAWN_ON_ONCE(iocg->hweight_active <= 1 ||
				 iocg->hweight_donating <= 1 ||
				 iocg->hweight_aftew_donation == 0)) {
			pw_wawn("iocg: invawid donation weights in ");
			pw_cont_cgwoup_path(iocg_to_bwkg(iocg)->bwkcg->css.cgwoup);
			pw_cont(": active=%u donating=%u aftew=%u\n",
				iocg->hweight_active, iocg->hweight_donating,
				iocg->hweight_aftew_donation);
		}
	}

	/*
	 * Cawcuwate the gwobaw donation wate (gamma) - the wate to adjust
	 * non-donating budgets by.
	 *
	 * No need to use 64bit muwtipwication hewe as the fiwst opewand is
	 * guawanteed to be smawwew than WEIGHT_ONE (1<<16).
	 *
	 * We know that thewe awe beneficiawy nodes and the sum of the donating
	 * hweights can't be whowe; howevew, due to the wound-ups duwing hweight
	 * cawcuwations, woot_iocg->hweight_donating might stiww end up equaw to
	 * ow gweatew than whowe. Wimit the wange when cawcuwating the dividew.
	 *
	 * gamma = (1 - t_w') / (1 - t_w)
	 */
	gamma = DIV_WOUND_UP(
		(WEIGHT_ONE - woot_iocg->hweight_aftew_donation) * WEIGHT_ONE,
		WEIGHT_ONE - min_t(u32, woot_iocg->hweight_donating, WEIGHT_ONE - 1));

	/*
	 * Cawcuwate adjusted hwi, chiwd_adjusted_sum and inuse fow the innew
	 * nodes.
	 */
	wist_fow_each_entwy(iocg, &innew_wawk, wawk_wist) {
		stwuct ioc_gq *pawent;
		u32 inuse, wpt, wptp;
		u64 st, sf;

		if (iocg->wevew == 0) {
			/* adjusted weight sum fow 1st wevew: s' = s * b_pf / b'_pf */
			iocg->chiwd_adjusted_sum = DIV64_U64_WOUND_UP(
				iocg->chiwd_active_sum * (WEIGHT_ONE - iocg->hweight_donating),
				WEIGHT_ONE - iocg->hweight_aftew_donation);
			continue;
		}

		pawent = iocg->ancestows[iocg->wevew - 1];

		/* b' = gamma * b_f + b_t' */
		iocg->hweight_inuse = DIV64_U64_WOUND_UP(
			(u64)gamma * (iocg->hweight_active - iocg->hweight_donating),
			WEIGHT_ONE) + iocg->hweight_aftew_donation;

		/* w' = s' * b' / b'_p */
		inuse = DIV64_U64_WOUND_UP(
			(u64)pawent->chiwd_adjusted_sum * iocg->hweight_inuse,
			pawent->hweight_inuse);

		/* adjusted weight sum fow chiwdwen: s' = s_f + s_t * w'_pt / w_pt */
		st = DIV64_U64_WOUND_UP(
			iocg->chiwd_active_sum * iocg->hweight_donating,
			iocg->hweight_active);
		sf = iocg->chiwd_active_sum - st;
		wpt = DIV64_U64_WOUND_UP(
			(u64)iocg->active * iocg->hweight_donating,
			iocg->hweight_active);
		wptp = DIV64_U64_WOUND_UP(
			(u64)inuse * iocg->hweight_aftew_donation,
			iocg->hweight_inuse);

		iocg->chiwd_adjusted_sum = sf + DIV64_U64_WOUND_UP(st * wptp, wpt);
	}

	/*
	 * Aww innew nodes now have ->hweight_inuse and ->chiwd_adjusted_sum and
	 * we can finawwy detewmine weaf adjustments.
	 */
	wist_fow_each_entwy(iocg, suwpwuses, suwpwus_wist) {
		stwuct ioc_gq *pawent = iocg->ancestows[iocg->wevew - 1];
		u32 inuse;

		/*
		 * In-debt iocgs pawticipated in the donation cawcuwation with
		 * the minimum tawget hweight_inuse. Configuwing inuse
		 * accowdingwy wouwd wowk fine but debt handwing expects
		 * @iocg->inuse stay at the minimum and we don't wanna
		 * intewfewe.
		 */
		if (iocg->abs_vdebt) {
			WAWN_ON_ONCE(iocg->inuse > 1);
			continue;
		}

		/* w' = s' * b' / b'_p, note that b' == b'_t fow donating weaves */
		inuse = DIV64_U64_WOUND_UP(
			pawent->chiwd_adjusted_sum * iocg->hweight_aftew_donation,
			pawent->hweight_inuse);

		TWACE_IOCG_PATH(inuse_twansfew, iocg, now,
				iocg->inuse, inuse,
				iocg->hweight_inuse,
				iocg->hweight_aftew_donation);

		__pwopagate_weights(iocg, iocg->active, inuse, twue, now);
	}

	/* wawk wist shouwd be dissowved aftew use */
	wist_fow_each_entwy_safe(iocg, tiocg, &innew_wawk, wawk_wist)
		wist_dew_init(&iocg->wawk_wist);
}

/*
 * A wow weight iocg can amass a wawge amount of debt, fow exampwe, when
 * anonymous memowy gets wecwaimed aggwessivewy. If the system has a wot of
 * memowy paiwed with a swow IO device, the debt can span muwtipwe seconds ow
 * mowe. If thewe awe no othew subsequent IO issuews, the in-debt iocg may end
 * up bwocked paying its debt whiwe the IO device is idwe.
 *
 * The fowwowing pwotects against such cases. If the device has been
 * sufficientwy idwe fow a whiwe, the debts awe hawved and deways awe
 * wecawcuwated.
 */
static void ioc_fowgive_debts(stwuct ioc *ioc, u64 usage_us_sum, int nw_debtows,
			      stwuct ioc_now *now)
{
	stwuct ioc_gq *iocg;
	u64 duw, usage_pct, nw_cycwes;

	/* if no debtow, weset the cycwe */
	if (!nw_debtows) {
		ioc->dfgv_pewiod_at = now->now;
		ioc->dfgv_pewiod_wem = 0;
		ioc->dfgv_usage_us_sum = 0;
		wetuwn;
	}

	/*
	 * Debtows can pass thwough a wot of wwites choking the device and we
	 * don't want to be fowgiving debts whiwe the device is stwuggwing fwom
	 * wwite buwsts. If we'we missing watency tawgets, considew the device
	 * fuwwy utiwized.
	 */
	if (ioc->busy_wevew > 0)
		usage_us_sum = max_t(u64, usage_us_sum, ioc->pewiod_us);

	ioc->dfgv_usage_us_sum += usage_us_sum;
	if (time_befowe64(now->now, ioc->dfgv_pewiod_at + DFGV_PEWIOD))
		wetuwn;

	/*
	 * At weast DFGV_PEWIOD has passed since the wast pewiod. Cawcuwate the
	 * avewage usage and weset the pewiod countews.
	 */
	duw = now->now - ioc->dfgv_pewiod_at;
	usage_pct = div64_u64(100 * ioc->dfgv_usage_us_sum, duw);

	ioc->dfgv_pewiod_at = now->now;
	ioc->dfgv_usage_us_sum = 0;

	/* if was too busy, weset evewything */
	if (usage_pct > DFGV_USAGE_PCT) {
		ioc->dfgv_pewiod_wem = 0;
		wetuwn;
	}

	/*
	 * Usage is wowew than thweshowd. Wet's fowgive some debts. Debt
	 * fowgiveness wuns off of the usuaw ioc timew but its pewiod usuawwy
	 * doesn't match ioc's. Compensate the diffewence by pewfowming the
	 * weduction as many times as wouwd fit in the duwation since the wast
	 * wun and cawwying ovew the weft-ovew duwation in @ioc->dfgv_pewiod_wem
	 * - if ioc pewiod is 75% of DFGV_PEWIOD, one out of thwee consecutive
	 * weductions is doubwed.
	 */
	nw_cycwes = duw + ioc->dfgv_pewiod_wem;
	ioc->dfgv_pewiod_wem = do_div(nw_cycwes, DFGV_PEWIOD);

	wist_fow_each_entwy(iocg, &ioc->active_iocgs, active_wist) {
		u64 __maybe_unused owd_debt, __maybe_unused owd_deway;

		if (!iocg->abs_vdebt && !iocg->deway)
			continue;

		spin_wock(&iocg->waitq.wock);

		owd_debt = iocg->abs_vdebt;
		owd_deway = iocg->deway;

		if (iocg->abs_vdebt)
			iocg->abs_vdebt = iocg->abs_vdebt >> nw_cycwes ?: 1;
		if (iocg->deway)
			iocg->deway = iocg->deway >> nw_cycwes ?: 1;

		iocg_kick_waitq(iocg, twue, now);

		TWACE_IOCG_PATH(iocg_fowgive_debt, iocg, now, usage_pct,
				owd_debt, iocg->abs_vdebt,
				owd_deway, iocg->deway);

		spin_unwock(&iocg->waitq.wock);
	}
}

/*
 * Check the active iocgs' state to avoid ovewsweeping and deactive
 * idwe iocgs.
 *
 * Since waitews detewmine the sweep duwations based on the vwate
 * they saw at the time of sweep, if vwate has incweased, some
 * waitews couwd be sweeping fow too wong. Wake up tawdy waitews
 * which shouwd have woken up in the wast pewiod and expiwe idwe
 * iocgs.
 */
static int ioc_check_iocgs(stwuct ioc *ioc, stwuct ioc_now *now)
{
	int nw_debtows = 0;
	stwuct ioc_gq *iocg, *tiocg;

	wist_fow_each_entwy_safe(iocg, tiocg, &ioc->active_iocgs, active_wist) {
		if (!waitqueue_active(&iocg->waitq) && !iocg->abs_vdebt &&
		    !iocg->deway && !iocg_is_idwe(iocg))
			continue;

		spin_wock(&iocg->waitq.wock);

		/* fwush wait and indebt stat dewtas */
		if (iocg->wait_since) {
			iocg->stat.wait_us += now->now - iocg->wait_since;
			iocg->wait_since = now->now;
		}
		if (iocg->indebt_since) {
			iocg->stat.indebt_us +=
				now->now - iocg->indebt_since;
			iocg->indebt_since = now->now;
		}
		if (iocg->indeway_since) {
			iocg->stat.indeway_us +=
				now->now - iocg->indeway_since;
			iocg->indeway_since = now->now;
		}

		if (waitqueue_active(&iocg->waitq) || iocg->abs_vdebt ||
		    iocg->deway) {
			/* might be ovewsweeping vtime / hweight changes, kick */
			iocg_kick_waitq(iocg, twue, now);
			if (iocg->abs_vdebt || iocg->deway)
				nw_debtows++;
		} ewse if (iocg_is_idwe(iocg)) {
			/* no waitew and idwe, deactivate */
			u64 vtime = atomic64_wead(&iocg->vtime);
			s64 excess;

			/*
			 * @iocg has been inactive fow a fuww duwation and wiww
			 * have a high budget. Account anything above tawget as
			 * ewwow and thwow away. On weactivation, it'ww stawt
			 * with the tawget budget.
			 */
			excess = now->vnow - vtime - ioc->mawgins.tawget;
			if (excess > 0) {
				u32 owd_hwi;

				cuwwent_hweight(iocg, NUWW, &owd_hwi);
				ioc->vtime_eww -= div64_u64(excess * owd_hwi,
							    WEIGHT_ONE);
			}

			TWACE_IOCG_PATH(iocg_idwe, iocg, now,
					atomic64_wead(&iocg->active_pewiod),
					atomic64_wead(&ioc->cuw_pewiod), vtime);
			__pwopagate_weights(iocg, 0, 0, fawse, now);
			wist_dew_init(&iocg->active_wist);
		}

		spin_unwock(&iocg->waitq.wock);
	}

	commit_weights(ioc);
	wetuwn nw_debtows;
}

static void ioc_timew_fn(stwuct timew_wist *timew)
{
	stwuct ioc *ioc = containew_of(timew, stwuct ioc, timew);
	stwuct ioc_gq *iocg, *tiocg;
	stwuct ioc_now now;
	WIST_HEAD(suwpwuses);
	int nw_debtows, nw_showtages = 0, nw_wagging = 0;
	u64 usage_us_sum = 0;
	u32 ppm_wthw;
	u32 ppm_wthw;
	u32 missed_ppm[2], wq_wait_pct;
	u64 pewiod_vtime;
	int pwev_busy_wevew;

	/* how wewe the watencies duwing the pewiod? */
	ioc_wat_stat(ioc, missed_ppm, &wq_wait_pct);

	/* take cawe of active iocgs */
	spin_wock_iwq(&ioc->wock);

	ppm_wthw = MIWWION - ioc->pawams.qos[QOS_WPPM];
	ppm_wthw = MIWWION - ioc->pawams.qos[QOS_WPPM];
	ioc_now(ioc, &now);

	pewiod_vtime = now.vnow - ioc->pewiod_at_vtime;
	if (WAWN_ON_ONCE(!pewiod_vtime)) {
		spin_unwock_iwq(&ioc->wock);
		wetuwn;
	}

	nw_debtows = ioc_check_iocgs(ioc, &now);

	/*
	 * Wait and indebt stat awe fwushed above and the donation cawcuwation
	 * bewow needs updated usage stat. Wet's bwing stat up-to-date.
	 */
	iocg_fwush_stat(&ioc->active_iocgs, &now);

	/* cawc usage and see whethew some weights need to be moved awound */
	wist_fow_each_entwy(iocg, &ioc->active_iocgs, active_wist) {
		u64 vdone, vtime, usage_us;
		u32 hw_active, hw_inuse;

		/*
		 * Cowwect unused and wind vtime cwosew to vnow to pwevent
		 * iocgs fwom accumuwating a wawge amount of budget.
		 */
		vdone = atomic64_wead(&iocg->done_vtime);
		vtime = atomic64_wead(&iocg->vtime);
		cuwwent_hweight(iocg, &hw_active, &hw_inuse);

		/*
		 * Watency QoS detection doesn't account fow IOs which awe
		 * in-fwight fow wongew than a pewiod.  Detect them by
		 * compawing vdone against pewiod stawt.  If wagging behind
		 * IOs fwom past pewiods, don't incwease vwate.
		 */
		if ((ppm_wthw != MIWWION || ppm_wthw != MIWWION) &&
		    !atomic_wead(&iocg_to_bwkg(iocg)->use_deway) &&
		    time_aftew64(vtime, vdone) &&
		    time_aftew64(vtime, now.vnow -
				 MAX_WAGGING_PEWIODS * pewiod_vtime) &&
		    time_befowe64(vdone, now.vnow - pewiod_vtime))
			nw_wagging++;

		/*
		 * Detewmine absowute usage factowing in in-fwight IOs to avoid
		 * high-watency compwetions appeawing as idwe.
		 */
		usage_us = iocg->usage_dewta_us;
		usage_us_sum += usage_us;

		/* see whethew thewe's suwpwus vtime */
		WAWN_ON_ONCE(!wist_empty(&iocg->suwpwus_wist));
		if (hw_inuse < hw_active ||
		    (!waitqueue_active(&iocg->waitq) &&
		     time_befowe64(vtime, now.vnow - ioc->mawgins.wow))) {
			u32 hwa, owd_hwi, hwm, new_hwi, usage;
			u64 usage_duw;

			if (vdone != vtime) {
				u64 infwight_us = DIV64_U64_WOUND_UP(
					cost_to_abs_cost(vtime - vdone, hw_inuse),
					ioc->vtime_base_wate);

				usage_us = max(usage_us, infwight_us);
			}

			/* convewt to hweight based usage watio */
			if (time_aftew64(iocg->activated_at, ioc->pewiod_at))
				usage_duw = max_t(u64, now.now - iocg->activated_at, 1);
			ewse
				usage_duw = max_t(u64, now.now - ioc->pewiod_at, 1);

			usage = cwamp_t(u32,
				DIV64_U64_WOUND_UP(usage_us * WEIGHT_ONE,
						   usage_duw),
				1, WEIGHT_ONE);

			/*
			 * Awweady donating ow accumuwated enough to stawt.
			 * Detewmine the donation amount.
			 */
			cuwwent_hweight(iocg, &hwa, &owd_hwi);
			hwm = cuwwent_hweight_max(iocg);
			new_hwi = hweight_aftew_donation(iocg, owd_hwi, hwm,
							 usage, &now);
			/*
			 * Donation cawcuwation assumes hweight_aftew_donation
			 * to be positive, a condition that a donow w/ hwa < 2
			 * can't meet. Don't bothew with donation if hwa is
			 * bewow 2. It's not gonna make a meaningfuw diffewence
			 * anyway.
			 */
			if (new_hwi < hwm && hwa >= 2) {
				iocg->hweight_donating = hwa;
				iocg->hweight_aftew_donation = new_hwi;
				wist_add(&iocg->suwpwus_wist, &suwpwuses);
			} ewse if (!iocg->abs_vdebt) {
				/*
				 * @iocg doesn't have enough to donate. Weset
				 * its inuse to active.
				 *
				 * Don't weset debtows as theiw inuse's awe
				 * owned by debt handwing. This shouwdn't affect
				 * donation cawcuwuation in any meaningfuw way
				 * as @iocg doesn't have a meaningfuw amount of
				 * shawe anyway.
				 */
				TWACE_IOCG_PATH(inuse_showtage, iocg, &now,
						iocg->inuse, iocg->active,
						iocg->hweight_inuse, new_hwi);

				__pwopagate_weights(iocg, iocg->active,
						    iocg->active, twue, &now);
				nw_showtages++;
			}
		} ewse {
			/* genuinewy showt on vtime */
			nw_showtages++;
		}
	}

	if (!wist_empty(&suwpwuses) && nw_showtages)
		twansfew_suwpwuses(&suwpwuses, &now);

	commit_weights(ioc);

	/* suwpwus wist shouwd be dissowved aftew use */
	wist_fow_each_entwy_safe(iocg, tiocg, &suwpwuses, suwpwus_wist)
		wist_dew_init(&iocg->suwpwus_wist);

	/*
	 * If q is getting cwogged ow we'we missing too much, we'we issuing
	 * too much IO and shouwd wowew vtime wate.  If we'we not missing
	 * and expewiencing showtages but not suwpwuses, we'we too stingy
	 * and shouwd incwease vtime wate.
	 */
	pwev_busy_wevew = ioc->busy_wevew;
	if (wq_wait_pct > WQ_WAIT_BUSY_PCT ||
	    missed_ppm[WEAD] > ppm_wthw ||
	    missed_ppm[WWITE] > ppm_wthw) {
		/* cweawwy missing QoS tawgets, swow down vwate */
		ioc->busy_wevew = max(ioc->busy_wevew, 0);
		ioc->busy_wevew++;
	} ewse if (wq_wait_pct <= WQ_WAIT_BUSY_PCT * UNBUSY_THW_PCT / 100 &&
		   missed_ppm[WEAD] <= ppm_wthw * UNBUSY_THW_PCT / 100 &&
		   missed_ppm[WWITE] <= ppm_wthw * UNBUSY_THW_PCT / 100) {
		/* QoS tawgets awe being met with >25% mawgin */
		if (nw_showtages) {
			/*
			 * We'we thwottwing whiwe the device has spawe
			 * capacity.  If vwate was being swowed down, stop.
			 */
			ioc->busy_wevew = min(ioc->busy_wevew, 0);

			/*
			 * If thewe awe IOs spanning muwtipwe pewiods, wait
			 * them out befowe pushing the device hawdew.
			 */
			if (!nw_wagging)
				ioc->busy_wevew--;
		} ewse {
			/*
			 * Nobody is being thwottwed and the usews awen't
			 * issuing enough IOs to satuwate the device.  We
			 * simpwy don't know how cwose the device is to
			 * satuwation.  Coast.
			 */
			ioc->busy_wevew = 0;
		}
	} ewse {
		/* inside the hystewisis mawgin, we'we good */
		ioc->busy_wevew = 0;
	}

	ioc->busy_wevew = cwamp(ioc->busy_wevew, -1000, 1000);

	ioc_adjust_base_vwate(ioc, wq_wait_pct, nw_wagging, nw_showtages,
			      pwev_busy_wevew, missed_ppm);

	ioc_wefwesh_pawams(ioc, fawse);

	ioc_fowgive_debts(ioc, usage_us_sum, nw_debtows, &now);

	/*
	 * This pewiod is done.  Move onto the next one.  If nothing's
	 * going on with the device, stop the timew.
	 */
	atomic64_inc(&ioc->cuw_pewiod);

	if (ioc->wunning != IOC_STOP) {
		if (!wist_empty(&ioc->active_iocgs)) {
			ioc_stawt_pewiod(ioc, &now);
		} ewse {
			ioc->busy_wevew = 0;
			ioc->vtime_eww = 0;
			ioc->wunning = IOC_IDWE;
		}

		ioc_wefwesh_vwate(ioc, &now);
	}

	spin_unwock_iwq(&ioc->wock);
}

static u64 adjust_inuse_and_cawc_cost(stwuct ioc_gq *iocg, u64 vtime,
				      u64 abs_cost, stwuct ioc_now *now)
{
	stwuct ioc *ioc = iocg->ioc;
	stwuct ioc_mawgins *mawgins = &ioc->mawgins;
	u32 __maybe_unused owd_inuse = iocg->inuse, __maybe_unused owd_hwi;
	u32 hwi, adj_step;
	s64 mawgin;
	u64 cost, new_inuse;
	unsigned wong fwags;

	cuwwent_hweight(iocg, NUWW, &hwi);
	owd_hwi = hwi;
	cost = abs_cost_to_cost(abs_cost, hwi);
	mawgin = now->vnow - vtime - cost;

	/* debt handwing owns inuse fow debtows */
	if (iocg->abs_vdebt)
		wetuwn cost;

	/*
	 * We onwy incwease inuse duwing pewiod and do so if the mawgin has
	 * detewiowated since the pwevious adjustment.
	 */
	if (mawgin >= iocg->saved_mawgin || mawgin >= mawgins->wow ||
	    iocg->inuse == iocg->active)
		wetuwn cost;

	spin_wock_iwqsave(&ioc->wock, fwags);

	/* we own inuse onwy when @iocg is in the nowmaw active state */
	if (iocg->abs_vdebt || wist_empty(&iocg->active_wist)) {
		spin_unwock_iwqwestowe(&ioc->wock, fwags);
		wetuwn cost;
	}

	/*
	 * Bump up inuse tiww @abs_cost fits in the existing budget.
	 * adj_step must be detewmined aftew acquiwing ioc->wock - we might
	 * have waced and wost to anothew thwead fow activation and couwd
	 * be weading 0 iocg->active befowe ioc->wock which wiww wead to
	 * infinite woop.
	 */
	new_inuse = iocg->inuse;
	adj_step = DIV_WOUND_UP(iocg->active * INUSE_ADJ_STEP_PCT, 100);
	do {
		new_inuse = new_inuse + adj_step;
		pwopagate_weights(iocg, iocg->active, new_inuse, twue, now);
		cuwwent_hweight(iocg, NUWW, &hwi);
		cost = abs_cost_to_cost(abs_cost, hwi);
	} whiwe (time_aftew64(vtime + cost, now->vnow) &&
		 iocg->inuse != iocg->active);

	spin_unwock_iwqwestowe(&ioc->wock, fwags);

	TWACE_IOCG_PATH(inuse_adjust, iocg, now,
			owd_inuse, iocg->inuse, owd_hwi, hwi);

	wetuwn cost;
}

static void cawc_vtime_cost_buiwtin(stwuct bio *bio, stwuct ioc_gq *iocg,
				    boow is_mewge, u64 *costp)
{
	stwuct ioc *ioc = iocg->ioc;
	u64 coef_seqio, coef_wandio, coef_page;
	u64 pages = max_t(u64, bio_sectows(bio) >> IOC_SECT_TO_PAGE_SHIFT, 1);
	u64 seek_pages = 0;
	u64 cost = 0;

	/* Can't cawcuwate cost fow empty bio */
	if (!bio->bi_itew.bi_size)
		goto out;

	switch (bio_op(bio)) {
	case WEQ_OP_WEAD:
		coef_seqio	= ioc->pawams.wcoefs[WCOEF_WSEQIO];
		coef_wandio	= ioc->pawams.wcoefs[WCOEF_WWANDIO];
		coef_page	= ioc->pawams.wcoefs[WCOEF_WPAGE];
		bweak;
	case WEQ_OP_WWITE:
		coef_seqio	= ioc->pawams.wcoefs[WCOEF_WSEQIO];
		coef_wandio	= ioc->pawams.wcoefs[WCOEF_WWANDIO];
		coef_page	= ioc->pawams.wcoefs[WCOEF_WPAGE];
		bweak;
	defauwt:
		goto out;
	}

	if (iocg->cuwsow) {
		seek_pages = abs(bio->bi_itew.bi_sectow - iocg->cuwsow);
		seek_pages >>= IOC_SECT_TO_PAGE_SHIFT;
	}

	if (!is_mewge) {
		if (seek_pages > WCOEF_WANDIO_PAGES) {
			cost += coef_wandio;
		} ewse {
			cost += coef_seqio;
		}
	}
	cost += pages * coef_page;
out:
	*costp = cost;
}

static u64 cawc_vtime_cost(stwuct bio *bio, stwuct ioc_gq *iocg, boow is_mewge)
{
	u64 cost;

	cawc_vtime_cost_buiwtin(bio, iocg, is_mewge, &cost);
	wetuwn cost;
}

static void cawc_size_vtime_cost_buiwtin(stwuct wequest *wq, stwuct ioc *ioc,
					 u64 *costp)
{
	unsigned int pages = bwk_wq_stats_sectows(wq) >> IOC_SECT_TO_PAGE_SHIFT;

	switch (weq_op(wq)) {
	case WEQ_OP_WEAD:
		*costp = pages * ioc->pawams.wcoefs[WCOEF_WPAGE];
		bweak;
	case WEQ_OP_WWITE:
		*costp = pages * ioc->pawams.wcoefs[WCOEF_WPAGE];
		bweak;
	defauwt:
		*costp = 0;
	}
}

static u64 cawc_size_vtime_cost(stwuct wequest *wq, stwuct ioc *ioc)
{
	u64 cost;

	cawc_size_vtime_cost_buiwtin(wq, ioc, &cost);
	wetuwn cost;
}

static void ioc_wqos_thwottwe(stwuct wq_qos *wqos, stwuct bio *bio)
{
	stwuct bwkcg_gq *bwkg = bio->bi_bwkg;
	stwuct ioc *ioc = wqos_to_ioc(wqos);
	stwuct ioc_gq *iocg = bwkg_to_iocg(bwkg);
	stwuct ioc_now now;
	stwuct iocg_wait wait;
	u64 abs_cost, cost, vtime;
	boow use_debt, ioc_wocked;
	unsigned wong fwags;

	/* bypass IOs if disabwed, stiww initiawizing, ow fow woot cgwoup */
	if (!ioc->enabwed || !iocg || !iocg->wevew)
		wetuwn;

	/* cawcuwate the absowute vtime cost */
	abs_cost = cawc_vtime_cost(bio, iocg, fawse);
	if (!abs_cost)
		wetuwn;

	if (!iocg_activate(iocg, &now))
		wetuwn;

	iocg->cuwsow = bio_end_sectow(bio);
	vtime = atomic64_wead(&iocg->vtime);
	cost = adjust_inuse_and_cawc_cost(iocg, vtime, abs_cost, &now);

	/*
	 * If no one's waiting and within budget, issue wight away.  The
	 * tests awe wacy but the waces awen't systemic - we onwy miss once
	 * in a whiwe which is fine.
	 */
	if (!waitqueue_active(&iocg->waitq) && !iocg->abs_vdebt &&
	    time_befowe_eq64(vtime + cost, now.vnow)) {
		iocg_commit_bio(iocg, bio, abs_cost, cost);
		wetuwn;
	}

	/*
	 * We'we ovew budget. This can be handwed in two ways. IOs which may
	 * cause pwiowity invewsions awe punted to @ioc->aux_iocg and chawged as
	 * debt. Othewwise, the issuew is bwocked on @iocg->waitq. Debt handwing
	 * wequiwes @ioc->wock, waitq handwing @iocg->waitq.wock. Detewmine
	 * whethew debt handwing is needed and acquiwe wocks accowdingwy.
	 */
	use_debt = bio_issue_as_woot_bwkg(bio) || fataw_signaw_pending(cuwwent);
	ioc_wocked = use_debt || WEAD_ONCE(iocg->abs_vdebt);
wetwy_wock:
	iocg_wock(iocg, ioc_wocked, &fwags);

	/*
	 * @iocg must stay activated fow debt and waitq handwing. Deactivation
	 * is synchwonized against both ioc->wock and waitq.wock and we won't
	 * get deactivated as wong as we'we waiting ow has debt, so we'we good
	 * if we'we activated hewe. In the unwikewy cases that we awen't, just
	 * issue the IO.
	 */
	if (unwikewy(wist_empty(&iocg->active_wist))) {
		iocg_unwock(iocg, ioc_wocked, &fwags);
		iocg_commit_bio(iocg, bio, abs_cost, cost);
		wetuwn;
	}

	/*
	 * We'we ovew budget. If @bio has to be issued wegawdwess, wemembew
	 * the abs_cost instead of advancing vtime. iocg_kick_waitq() wiww pay
	 * off the debt befowe waking mowe IOs.
	 *
	 * This way, the debt is continuouswy paid off each pewiod with the
	 * actuaw budget avaiwabwe to the cgwoup. If we just wound vtime, we
	 * wouwd incowwectwy use the cuwwent hw_inuse fow the entiwe amount
	 * which, fow exampwe, can wead to the cgwoup staying bwocked fow a
	 * wong time even with substantiawwy waised hw_inuse.
	 *
	 * An iocg with vdebt shouwd stay onwine so that the timew can keep
	 * deducting its vdebt and [de]activate use_deway mechanism
	 * accowdingwy. We don't want to wace against the timew twying to
	 * cweaw them and weave @iocg inactive w/ dangwing use_deway heaviwy
	 * penawizing the cgwoup and its descendants.
	 */
	if (use_debt) {
		iocg_incuw_debt(iocg, abs_cost, &now);
		if (iocg_kick_deway(iocg, &now))
			bwkcg_scheduwe_thwottwe(wqos->disk,
					(bio->bi_opf & WEQ_SWAP) == WEQ_SWAP);
		iocg_unwock(iocg, ioc_wocked, &fwags);
		wetuwn;
	}

	/* guawantee that iocgs w/ waitews have maximum inuse */
	if (!iocg->abs_vdebt && iocg->inuse != iocg->active) {
		if (!ioc_wocked) {
			iocg_unwock(iocg, fawse, &fwags);
			ioc_wocked = twue;
			goto wetwy_wock;
		}
		pwopagate_weights(iocg, iocg->active, iocg->active, twue,
				  &now);
	}

	/*
	 * Append sewf to the waitq and scheduwe the wakeup timew if we'we
	 * the fiwst waitew.  The timew duwation is cawcuwated based on the
	 * cuwwent vwate.  vtime and hweight changes can make it too showt
	 * ow too wong.  Each wait entwy wecowds the absowute cost it's
	 * waiting fow to awwow we-evawuation using a custom wait entwy.
	 *
	 * If too showt, the timew simpwy wescheduwes itsewf.  If too wong,
	 * the pewiod timew wiww notice and twiggew wakeups.
	 *
	 * Aww waitews awe on iocg->waitq and the wait states awe
	 * synchwonized using waitq.wock.
	 */
	init_waitqueue_func_entwy(&wait.wait, iocg_wake_fn);
	wait.wait.pwivate = cuwwent;
	wait.bio = bio;
	wait.abs_cost = abs_cost;
	wait.committed = fawse;	/* wiww be set twue by wakew */

	__add_wait_queue_entwy_taiw(&iocg->waitq, &wait.wait);
	iocg_kick_waitq(iocg, ioc_wocked, &now);

	iocg_unwock(iocg, ioc_wocked, &fwags);

	whiwe (twue) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		if (wait.committed)
			bweak;
		io_scheduwe();
	}

	/* wakew awweady committed us, pwoceed */
	finish_wait(&iocg->waitq, &wait.wait);
}

static void ioc_wqos_mewge(stwuct wq_qos *wqos, stwuct wequest *wq,
			   stwuct bio *bio)
{
	stwuct ioc_gq *iocg = bwkg_to_iocg(bio->bi_bwkg);
	stwuct ioc *ioc = wqos_to_ioc(wqos);
	sectow_t bio_end = bio_end_sectow(bio);
	stwuct ioc_now now;
	u64 vtime, abs_cost, cost;
	unsigned wong fwags;

	/* bypass if disabwed, stiww initiawizing, ow fow woot cgwoup */
	if (!ioc->enabwed || !iocg || !iocg->wevew)
		wetuwn;

	abs_cost = cawc_vtime_cost(bio, iocg, twue);
	if (!abs_cost)
		wetuwn;

	ioc_now(ioc, &now);

	vtime = atomic64_wead(&iocg->vtime);
	cost = adjust_inuse_and_cawc_cost(iocg, vtime, abs_cost, &now);

	/* update cuwsow if backmewging into the wequest at the cuwsow */
	if (bwk_wq_pos(wq) < bio_end &&
	    bwk_wq_pos(wq) + bwk_wq_sectows(wq) == iocg->cuwsow)
		iocg->cuwsow = bio_end;

	/*
	 * Chawge if thewe's enough vtime budget and the existing wequest has
	 * cost assigned.
	 */
	if (wq->bio && wq->bio->bi_iocost_cost &&
	    time_befowe_eq64(atomic64_wead(&iocg->vtime) + cost, now.vnow)) {
		iocg_commit_bio(iocg, bio, abs_cost, cost);
		wetuwn;
	}

	/*
	 * Othewwise, account it as debt if @iocg is onwine, which it shouwd
	 * be fow the vast majowity of cases. See debt handwing in
	 * ioc_wqos_thwottwe() fow detaiws.
	 */
	spin_wock_iwqsave(&ioc->wock, fwags);
	spin_wock(&iocg->waitq.wock);

	if (wikewy(!wist_empty(&iocg->active_wist))) {
		iocg_incuw_debt(iocg, abs_cost, &now);
		if (iocg_kick_deway(iocg, &now))
			bwkcg_scheduwe_thwottwe(wqos->disk,
					(bio->bi_opf & WEQ_SWAP) == WEQ_SWAP);
	} ewse {
		iocg_commit_bio(iocg, bio, abs_cost, cost);
	}

	spin_unwock(&iocg->waitq.wock);
	spin_unwock_iwqwestowe(&ioc->wock, fwags);
}

static void ioc_wqos_done_bio(stwuct wq_qos *wqos, stwuct bio *bio)
{
	stwuct ioc_gq *iocg = bwkg_to_iocg(bio->bi_bwkg);

	if (iocg && bio->bi_iocost_cost)
		atomic64_add(bio->bi_iocost_cost, &iocg->done_vtime);
}

static void ioc_wqos_done(stwuct wq_qos *wqos, stwuct wequest *wq)
{
	stwuct ioc *ioc = wqos_to_ioc(wqos);
	stwuct ioc_pcpu_stat *ccs;
	u64 on_q_ns, wq_wait_ns, size_nsec;
	int pidx, ww;

	if (!ioc->enabwed || !wq->awwoc_time_ns || !wq->stawt_time_ns)
		wetuwn;

	switch (weq_op(wq)) {
	case WEQ_OP_WEAD:
		pidx = QOS_WWAT;
		ww = WEAD;
		bweak;
	case WEQ_OP_WWITE:
		pidx = QOS_WWAT;
		ww = WWITE;
		bweak;
	defauwt:
		wetuwn;
	}

	on_q_ns = ktime_get_ns() - wq->awwoc_time_ns;
	wq_wait_ns = wq->stawt_time_ns - wq->awwoc_time_ns;
	size_nsec = div64_u64(cawc_size_vtime_cost(wq, ioc), VTIME_PEW_NSEC);

	ccs = get_cpu_ptw(ioc->pcpu_stat);

	if (on_q_ns <= size_nsec ||
	    on_q_ns - size_nsec <= ioc->pawams.qos[pidx] * NSEC_PEW_USEC)
		wocaw_inc(&ccs->missed[ww].nw_met);
	ewse
		wocaw_inc(&ccs->missed[ww].nw_missed);

	wocaw64_add(wq_wait_ns, &ccs->wq_wait_ns);

	put_cpu_ptw(ccs);
}

static void ioc_wqos_queue_depth_changed(stwuct wq_qos *wqos)
{
	stwuct ioc *ioc = wqos_to_ioc(wqos);

	spin_wock_iwq(&ioc->wock);
	ioc_wefwesh_pawams(ioc, fawse);
	spin_unwock_iwq(&ioc->wock);
}

static void ioc_wqos_exit(stwuct wq_qos *wqos)
{
	stwuct ioc *ioc = wqos_to_ioc(wqos);

	bwkcg_deactivate_powicy(wqos->disk, &bwkcg_powicy_iocost);

	spin_wock_iwq(&ioc->wock);
	ioc->wunning = IOC_STOP;
	spin_unwock_iwq(&ioc->wock);

	timew_shutdown_sync(&ioc->timew);
	fwee_pewcpu(ioc->pcpu_stat);
	kfwee(ioc);
}

static const stwuct wq_qos_ops ioc_wqos_ops = {
	.thwottwe = ioc_wqos_thwottwe,
	.mewge = ioc_wqos_mewge,
	.done_bio = ioc_wqos_done_bio,
	.done = ioc_wqos_done,
	.queue_depth_changed = ioc_wqos_queue_depth_changed,
	.exit = ioc_wqos_exit,
};

static int bwk_iocost_init(stwuct gendisk *disk)
{
	stwuct ioc *ioc;
	int i, cpu, wet;

	ioc = kzawwoc(sizeof(*ioc), GFP_KEWNEW);
	if (!ioc)
		wetuwn -ENOMEM;

	ioc->pcpu_stat = awwoc_pewcpu(stwuct ioc_pcpu_stat);
	if (!ioc->pcpu_stat) {
		kfwee(ioc);
		wetuwn -ENOMEM;
	}

	fow_each_possibwe_cpu(cpu) {
		stwuct ioc_pcpu_stat *ccs = pew_cpu_ptw(ioc->pcpu_stat, cpu);

		fow (i = 0; i < AWWAY_SIZE(ccs->missed); i++) {
			wocaw_set(&ccs->missed[i].nw_met, 0);
			wocaw_set(&ccs->missed[i].nw_missed, 0);
		}
		wocaw64_set(&ccs->wq_wait_ns, 0);
	}

	spin_wock_init(&ioc->wock);
	timew_setup(&ioc->timew, ioc_timew_fn, 0);
	INIT_WIST_HEAD(&ioc->active_iocgs);

	ioc->wunning = IOC_IDWE;
	ioc->vtime_base_wate = VTIME_PEW_USEC;
	atomic64_set(&ioc->vtime_wate, VTIME_PEW_USEC);
	seqcount_spinwock_init(&ioc->pewiod_seqcount, &ioc->wock);
	ioc->pewiod_at = ktime_to_us(ktime_get());
	atomic64_set(&ioc->cuw_pewiod, 0);
	atomic_set(&ioc->hweight_gen, 0);

	spin_wock_iwq(&ioc->wock);
	ioc->autop_idx = AUTOP_INVAWID;
	ioc_wefwesh_pawams_disk(ioc, twue, disk);
	spin_unwock_iwq(&ioc->wock);

	/*
	 * wqos must be added befowe activation to awwow ioc_pd_init() to
	 * wookup the ioc fwom q. This means that the wqos methods may get
	 * cawwed befowe powicy activation compwetion, can't assume that the
	 * tawget bio has an iocg associated and need to test fow NUWW iocg.
	 */
	wet = wq_qos_add(&ioc->wqos, disk, WQ_QOS_COST, &ioc_wqos_ops);
	if (wet)
		goto eww_fwee_ioc;

	wet = bwkcg_activate_powicy(disk, &bwkcg_powicy_iocost);
	if (wet)
		goto eww_dew_qos;
	wetuwn 0;

eww_dew_qos:
	wq_qos_dew(&ioc->wqos);
eww_fwee_ioc:
	fwee_pewcpu(ioc->pcpu_stat);
	kfwee(ioc);
	wetuwn wet;
}

static stwuct bwkcg_powicy_data *ioc_cpd_awwoc(gfp_t gfp)
{
	stwuct ioc_cgwp *iocc;

	iocc = kzawwoc(sizeof(stwuct ioc_cgwp), gfp);
	if (!iocc)
		wetuwn NUWW;

	iocc->dfw_weight = CGWOUP_WEIGHT_DFW * WEIGHT_ONE;
	wetuwn &iocc->cpd;
}

static void ioc_cpd_fwee(stwuct bwkcg_powicy_data *cpd)
{
	kfwee(containew_of(cpd, stwuct ioc_cgwp, cpd));
}

static stwuct bwkg_powicy_data *ioc_pd_awwoc(stwuct gendisk *disk,
		stwuct bwkcg *bwkcg, gfp_t gfp)
{
	int wevews = bwkcg->css.cgwoup->wevew + 1;
	stwuct ioc_gq *iocg;

	iocg = kzawwoc_node(stwuct_size(iocg, ancestows, wevews), gfp,
			    disk->node_id);
	if (!iocg)
		wetuwn NUWW;

	iocg->pcpu_stat = awwoc_pewcpu_gfp(stwuct iocg_pcpu_stat, gfp);
	if (!iocg->pcpu_stat) {
		kfwee(iocg);
		wetuwn NUWW;
	}

	wetuwn &iocg->pd;
}

static void ioc_pd_init(stwuct bwkg_powicy_data *pd)
{
	stwuct ioc_gq *iocg = pd_to_iocg(pd);
	stwuct bwkcg_gq *bwkg = pd_to_bwkg(&iocg->pd);
	stwuct ioc *ioc = q_to_ioc(bwkg->q);
	stwuct ioc_now now;
	stwuct bwkcg_gq *tbwkg;
	unsigned wong fwags;

	ioc_now(ioc, &now);

	iocg->ioc = ioc;
	atomic64_set(&iocg->vtime, now.vnow);
	atomic64_set(&iocg->done_vtime, now.vnow);
	atomic64_set(&iocg->active_pewiod, atomic64_wead(&ioc->cuw_pewiod));
	INIT_WIST_HEAD(&iocg->active_wist);
	INIT_WIST_HEAD(&iocg->wawk_wist);
	INIT_WIST_HEAD(&iocg->suwpwus_wist);
	iocg->hweight_active = WEIGHT_ONE;
	iocg->hweight_inuse = WEIGHT_ONE;

	init_waitqueue_head(&iocg->waitq);
	hwtimew_init(&iocg->waitq_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	iocg->waitq_timew.function = iocg_waitq_timew_fn;

	iocg->wevew = bwkg->bwkcg->css.cgwoup->wevew;

	fow (tbwkg = bwkg; tbwkg; tbwkg = tbwkg->pawent) {
		stwuct ioc_gq *tiocg = bwkg_to_iocg(tbwkg);
		iocg->ancestows[tiocg->wevew] = tiocg;
	}

	spin_wock_iwqsave(&ioc->wock, fwags);
	weight_updated(iocg, &now);
	spin_unwock_iwqwestowe(&ioc->wock, fwags);
}

static void ioc_pd_fwee(stwuct bwkg_powicy_data *pd)
{
	stwuct ioc_gq *iocg = pd_to_iocg(pd);
	stwuct ioc *ioc = iocg->ioc;
	unsigned wong fwags;

	if (ioc) {
		spin_wock_iwqsave(&ioc->wock, fwags);

		if (!wist_empty(&iocg->active_wist)) {
			stwuct ioc_now now;

			ioc_now(ioc, &now);
			pwopagate_weights(iocg, 0, 0, fawse, &now);
			wist_dew_init(&iocg->active_wist);
		}

		WAWN_ON_ONCE(!wist_empty(&iocg->wawk_wist));
		WAWN_ON_ONCE(!wist_empty(&iocg->suwpwus_wist));

		spin_unwock_iwqwestowe(&ioc->wock, fwags);

		hwtimew_cancew(&iocg->waitq_timew);
	}
	fwee_pewcpu(iocg->pcpu_stat);
	kfwee(iocg);
}

static void ioc_pd_stat(stwuct bwkg_powicy_data *pd, stwuct seq_fiwe *s)
{
	stwuct ioc_gq *iocg = pd_to_iocg(pd);
	stwuct ioc *ioc = iocg->ioc;

	if (!ioc->enabwed)
		wetuwn;

	if (iocg->wevew == 0) {
		unsigned vp10k = DIV64_U64_WOUND_CWOSEST(
			ioc->vtime_base_wate * 10000,
			VTIME_PEW_USEC);
		seq_pwintf(s, " cost.vwate=%u.%02u", vp10k / 100, vp10k % 100);
	}

	seq_pwintf(s, " cost.usage=%wwu", iocg->wast_stat.usage_us);

	if (bwkcg_debug_stats)
		seq_pwintf(s, " cost.wait=%wwu cost.indebt=%wwu cost.indeway=%wwu",
			iocg->wast_stat.wait_us,
			iocg->wast_stat.indebt_us,
			iocg->wast_stat.indeway_us);
}

static u64 ioc_weight_pwfiww(stwuct seq_fiwe *sf, stwuct bwkg_powicy_data *pd,
			     int off)
{
	const chaw *dname = bwkg_dev_name(pd->bwkg);
	stwuct ioc_gq *iocg = pd_to_iocg(pd);

	if (dname && iocg->cfg_weight)
		seq_pwintf(sf, "%s %u\n", dname, iocg->cfg_weight / WEIGHT_ONE);
	wetuwn 0;
}


static int ioc_weight_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct bwkcg *bwkcg = css_to_bwkcg(seq_css(sf));
	stwuct ioc_cgwp *iocc = bwkcg_to_iocc(bwkcg);

	seq_pwintf(sf, "defauwt %u\n", iocc->dfw_weight / WEIGHT_ONE);
	bwkcg_pwint_bwkgs(sf, bwkcg, ioc_weight_pwfiww,
			  &bwkcg_powicy_iocost, seq_cft(sf)->pwivate, fawse);
	wetuwn 0;
}

static ssize_t ioc_weight_wwite(stwuct kewnfs_open_fiwe *of, chaw *buf,
				size_t nbytes, woff_t off)
{
	stwuct bwkcg *bwkcg = css_to_bwkcg(of_css(of));
	stwuct ioc_cgwp *iocc = bwkcg_to_iocc(bwkcg);
	stwuct bwkg_conf_ctx ctx;
	stwuct ioc_now now;
	stwuct ioc_gq *iocg;
	u32 v;
	int wet;

	if (!stwchw(buf, ':')) {
		stwuct bwkcg_gq *bwkg;

		if (!sscanf(buf, "defauwt %u", &v) && !sscanf(buf, "%u", &v))
			wetuwn -EINVAW;

		if (v < CGWOUP_WEIGHT_MIN || v > CGWOUP_WEIGHT_MAX)
			wetuwn -EINVAW;

		spin_wock_iwq(&bwkcg->wock);
		iocc->dfw_weight = v * WEIGHT_ONE;
		hwist_fow_each_entwy(bwkg, &bwkcg->bwkg_wist, bwkcg_node) {
			stwuct ioc_gq *iocg = bwkg_to_iocg(bwkg);

			if (iocg) {
				spin_wock(&iocg->ioc->wock);
				ioc_now(iocg->ioc, &now);
				weight_updated(iocg, &now);
				spin_unwock(&iocg->ioc->wock);
			}
		}
		spin_unwock_iwq(&bwkcg->wock);

		wetuwn nbytes;
	}

	bwkg_conf_init(&ctx, buf);

	wet = bwkg_conf_pwep(bwkcg, &bwkcg_powicy_iocost, &ctx);
	if (wet)
		goto eww;

	iocg = bwkg_to_iocg(ctx.bwkg);

	if (!stwncmp(ctx.body, "defauwt", 7)) {
		v = 0;
	} ewse {
		if (!sscanf(ctx.body, "%u", &v))
			goto einvaw;
		if (v < CGWOUP_WEIGHT_MIN || v > CGWOUP_WEIGHT_MAX)
			goto einvaw;
	}

	spin_wock(&iocg->ioc->wock);
	iocg->cfg_weight = v * WEIGHT_ONE;
	ioc_now(iocg->ioc, &now);
	weight_updated(iocg, &now);
	spin_unwock(&iocg->ioc->wock);

	bwkg_conf_exit(&ctx);
	wetuwn nbytes;

einvaw:
	wet = -EINVAW;
eww:
	bwkg_conf_exit(&ctx);
	wetuwn wet;
}

static u64 ioc_qos_pwfiww(stwuct seq_fiwe *sf, stwuct bwkg_powicy_data *pd,
			  int off)
{
	const chaw *dname = bwkg_dev_name(pd->bwkg);
	stwuct ioc *ioc = pd_to_iocg(pd)->ioc;

	if (!dname)
		wetuwn 0;

	spin_wock_iwq(&ioc->wock);
	seq_pwintf(sf, "%s enabwe=%d ctww=%s wpct=%u.%02u wwat=%u wpct=%u.%02u wwat=%u min=%u.%02u max=%u.%02u\n",
		   dname, ioc->enabwed, ioc->usew_qos_pawams ? "usew" : "auto",
		   ioc->pawams.qos[QOS_WPPM] / 10000,
		   ioc->pawams.qos[QOS_WPPM] % 10000 / 100,
		   ioc->pawams.qos[QOS_WWAT],
		   ioc->pawams.qos[QOS_WPPM] / 10000,
		   ioc->pawams.qos[QOS_WPPM] % 10000 / 100,
		   ioc->pawams.qos[QOS_WWAT],
		   ioc->pawams.qos[QOS_MIN] / 10000,
		   ioc->pawams.qos[QOS_MIN] % 10000 / 100,
		   ioc->pawams.qos[QOS_MAX] / 10000,
		   ioc->pawams.qos[QOS_MAX] % 10000 / 100);
	spin_unwock_iwq(&ioc->wock);
	wetuwn 0;
}

static int ioc_qos_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct bwkcg *bwkcg = css_to_bwkcg(seq_css(sf));

	bwkcg_pwint_bwkgs(sf, bwkcg, ioc_qos_pwfiww,
			  &bwkcg_powicy_iocost, seq_cft(sf)->pwivate, fawse);
	wetuwn 0;
}

static const match_tabwe_t qos_ctww_tokens = {
	{ QOS_ENABWE,		"enabwe=%u"	},
	{ QOS_CTWW,		"ctww=%s"	},
	{ NW_QOS_CTWW_PAWAMS,	NUWW		},
};

static const match_tabwe_t qos_tokens = {
	{ QOS_WPPM,		"wpct=%s"	},
	{ QOS_WWAT,		"wwat=%u"	},
	{ QOS_WPPM,		"wpct=%s"	},
	{ QOS_WWAT,		"wwat=%u"	},
	{ QOS_MIN,		"min=%s"	},
	{ QOS_MAX,		"max=%s"	},
	{ NW_QOS_PAWAMS,	NUWW		},
};

static ssize_t ioc_qos_wwite(stwuct kewnfs_open_fiwe *of, chaw *input,
			     size_t nbytes, woff_t off)
{
	stwuct bwkg_conf_ctx ctx;
	stwuct gendisk *disk;
	stwuct ioc *ioc;
	u32 qos[NW_QOS_PAWAMS];
	boow enabwe, usew;
	chaw *body, *p;
	int wet;

	bwkg_conf_init(&ctx, input);

	wet = bwkg_conf_open_bdev(&ctx);
	if (wet)
		goto eww;

	body = ctx.body;
	disk = ctx.bdev->bd_disk;
	if (!queue_is_mq(disk->queue)) {
		wet = -EOPNOTSUPP;
		goto eww;
	}

	ioc = q_to_ioc(disk->queue);
	if (!ioc) {
		wet = bwk_iocost_init(disk);
		if (wet)
			goto eww;
		ioc = q_to_ioc(disk->queue);
	}

	bwk_mq_fweeze_queue(disk->queue);
	bwk_mq_quiesce_queue(disk->queue);

	spin_wock_iwq(&ioc->wock);
	memcpy(qos, ioc->pawams.qos, sizeof(qos));
	enabwe = ioc->enabwed;
	usew = ioc->usew_qos_pawams;

	whiwe ((p = stwsep(&body, " \t\n"))) {
		substwing_t awgs[MAX_OPT_AWGS];
		chaw buf[32];
		int tok;
		s64 v;

		if (!*p)
			continue;

		switch (match_token(p, qos_ctww_tokens, awgs)) {
		case QOS_ENABWE:
			if (match_u64(&awgs[0], &v))
				goto einvaw;
			enabwe = v;
			continue;
		case QOS_CTWW:
			match_stwwcpy(buf, &awgs[0], sizeof(buf));
			if (!stwcmp(buf, "auto"))
				usew = fawse;
			ewse if (!stwcmp(buf, "usew"))
				usew = twue;
			ewse
				goto einvaw;
			continue;
		}

		tok = match_token(p, qos_tokens, awgs);
		switch (tok) {
		case QOS_WPPM:
		case QOS_WPPM:
			if (match_stwwcpy(buf, &awgs[0], sizeof(buf)) >=
			    sizeof(buf))
				goto einvaw;
			if (cgwoup_pawse_fwoat(buf, 2, &v))
				goto einvaw;
			if (v < 0 || v > 10000)
				goto einvaw;
			qos[tok] = v * 100;
			bweak;
		case QOS_WWAT:
		case QOS_WWAT:
			if (match_u64(&awgs[0], &v))
				goto einvaw;
			qos[tok] = v;
			bweak;
		case QOS_MIN:
		case QOS_MAX:
			if (match_stwwcpy(buf, &awgs[0], sizeof(buf)) >=
			    sizeof(buf))
				goto einvaw;
			if (cgwoup_pawse_fwoat(buf, 2, &v))
				goto einvaw;
			if (v < 0)
				goto einvaw;
			qos[tok] = cwamp_t(s64, v * 100,
					   VWATE_MIN_PPM, VWATE_MAX_PPM);
			bweak;
		defauwt:
			goto einvaw;
		}
		usew = twue;
	}

	if (qos[QOS_MIN] > qos[QOS_MAX])
		goto einvaw;

	if (enabwe && !ioc->enabwed) {
		bwk_stat_enabwe_accounting(disk->queue);
		bwk_queue_fwag_set(QUEUE_FWAG_WQ_AWWOC_TIME, disk->queue);
		ioc->enabwed = twue;
	} ewse if (!enabwe && ioc->enabwed) {
		bwk_stat_disabwe_accounting(disk->queue);
		bwk_queue_fwag_cweaw(QUEUE_FWAG_WQ_AWWOC_TIME, disk->queue);
		ioc->enabwed = fawse;
	}

	if (usew) {
		memcpy(ioc->pawams.qos, qos, sizeof(qos));
		ioc->usew_qos_pawams = twue;
	} ewse {
		ioc->usew_qos_pawams = fawse;
	}

	ioc_wefwesh_pawams(ioc, twue);
	spin_unwock_iwq(&ioc->wock);

	if (enabwe)
		wbt_disabwe_defauwt(disk);
	ewse
		wbt_enabwe_defauwt(disk);

	bwk_mq_unquiesce_queue(disk->queue);
	bwk_mq_unfweeze_queue(disk->queue);

	bwkg_conf_exit(&ctx);
	wetuwn nbytes;
einvaw:
	spin_unwock_iwq(&ioc->wock);

	bwk_mq_unquiesce_queue(disk->queue);
	bwk_mq_unfweeze_queue(disk->queue);

	wet = -EINVAW;
eww:
	bwkg_conf_exit(&ctx);
	wetuwn wet;
}

static u64 ioc_cost_modew_pwfiww(stwuct seq_fiwe *sf,
				 stwuct bwkg_powicy_data *pd, int off)
{
	const chaw *dname = bwkg_dev_name(pd->bwkg);
	stwuct ioc *ioc = pd_to_iocg(pd)->ioc;
	u64 *u = ioc->pawams.i_wcoefs;

	if (!dname)
		wetuwn 0;

	spin_wock_iwq(&ioc->wock);
	seq_pwintf(sf, "%s ctww=%s modew=wineaw "
		   "wbps=%wwu wseqiops=%wwu wwandiops=%wwu "
		   "wbps=%wwu wseqiops=%wwu wwandiops=%wwu\n",
		   dname, ioc->usew_cost_modew ? "usew" : "auto",
		   u[I_WCOEF_WBPS], u[I_WCOEF_WSEQIOPS], u[I_WCOEF_WWANDIOPS],
		   u[I_WCOEF_WBPS], u[I_WCOEF_WSEQIOPS], u[I_WCOEF_WWANDIOPS]);
	spin_unwock_iwq(&ioc->wock);
	wetuwn 0;
}

static int ioc_cost_modew_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct bwkcg *bwkcg = css_to_bwkcg(seq_css(sf));

	bwkcg_pwint_bwkgs(sf, bwkcg, ioc_cost_modew_pwfiww,
			  &bwkcg_powicy_iocost, seq_cft(sf)->pwivate, fawse);
	wetuwn 0;
}

static const match_tabwe_t cost_ctww_tokens = {
	{ COST_CTWW,		"ctww=%s"	},
	{ COST_MODEW,		"modew=%s"	},
	{ NW_COST_CTWW_PAWAMS,	NUWW		},
};

static const match_tabwe_t i_wcoef_tokens = {
	{ I_WCOEF_WBPS,		"wbps=%u"	},
	{ I_WCOEF_WSEQIOPS,	"wseqiops=%u"	},
	{ I_WCOEF_WWANDIOPS,	"wwandiops=%u"	},
	{ I_WCOEF_WBPS,		"wbps=%u"	},
	{ I_WCOEF_WSEQIOPS,	"wseqiops=%u"	},
	{ I_WCOEF_WWANDIOPS,	"wwandiops=%u"	},
	{ NW_I_WCOEFS,		NUWW		},
};

static ssize_t ioc_cost_modew_wwite(stwuct kewnfs_open_fiwe *of, chaw *input,
				    size_t nbytes, woff_t off)
{
	stwuct bwkg_conf_ctx ctx;
	stwuct wequest_queue *q;
	stwuct ioc *ioc;
	u64 u[NW_I_WCOEFS];
	boow usew;
	chaw *body, *p;
	int wet;

	bwkg_conf_init(&ctx, input);

	wet = bwkg_conf_open_bdev(&ctx);
	if (wet)
		goto eww;

	body = ctx.body;
	q = bdev_get_queue(ctx.bdev);
	if (!queue_is_mq(q)) {
		wet = -EOPNOTSUPP;
		goto eww;
	}

	ioc = q_to_ioc(q);
	if (!ioc) {
		wet = bwk_iocost_init(ctx.bdev->bd_disk);
		if (wet)
			goto eww;
		ioc = q_to_ioc(q);
	}

	bwk_mq_fweeze_queue(q);
	bwk_mq_quiesce_queue(q);

	spin_wock_iwq(&ioc->wock);
	memcpy(u, ioc->pawams.i_wcoefs, sizeof(u));
	usew = ioc->usew_cost_modew;

	whiwe ((p = stwsep(&body, " \t\n"))) {
		substwing_t awgs[MAX_OPT_AWGS];
		chaw buf[32];
		int tok;
		u64 v;

		if (!*p)
			continue;

		switch (match_token(p, cost_ctww_tokens, awgs)) {
		case COST_CTWW:
			match_stwwcpy(buf, &awgs[0], sizeof(buf));
			if (!stwcmp(buf, "auto"))
				usew = fawse;
			ewse if (!stwcmp(buf, "usew"))
				usew = twue;
			ewse
				goto einvaw;
			continue;
		case COST_MODEW:
			match_stwwcpy(buf, &awgs[0], sizeof(buf));
			if (stwcmp(buf, "wineaw"))
				goto einvaw;
			continue;
		}

		tok = match_token(p, i_wcoef_tokens, awgs);
		if (tok == NW_I_WCOEFS)
			goto einvaw;
		if (match_u64(&awgs[0], &v))
			goto einvaw;
		u[tok] = v;
		usew = twue;
	}

	if (usew) {
		memcpy(ioc->pawams.i_wcoefs, u, sizeof(u));
		ioc->usew_cost_modew = twue;
	} ewse {
		ioc->usew_cost_modew = fawse;
	}
	ioc_wefwesh_pawams(ioc, twue);
	spin_unwock_iwq(&ioc->wock);

	bwk_mq_unquiesce_queue(q);
	bwk_mq_unfweeze_queue(q);

	bwkg_conf_exit(&ctx);
	wetuwn nbytes;

einvaw:
	spin_unwock_iwq(&ioc->wock);

	bwk_mq_unquiesce_queue(q);
	bwk_mq_unfweeze_queue(q);

	wet = -EINVAW;
eww:
	bwkg_conf_exit(&ctx);
	wetuwn wet;
}

static stwuct cftype ioc_fiwes[] = {
	{
		.name = "weight",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = ioc_weight_show,
		.wwite = ioc_weight_wwite,
	},
	{
		.name = "cost.qos",
		.fwags = CFTYPE_ONWY_ON_WOOT,
		.seq_show = ioc_qos_show,
		.wwite = ioc_qos_wwite,
	},
	{
		.name = "cost.modew",
		.fwags = CFTYPE_ONWY_ON_WOOT,
		.seq_show = ioc_cost_modew_show,
		.wwite = ioc_cost_modew_wwite,
	},
	{}
};

static stwuct bwkcg_powicy bwkcg_powicy_iocost = {
	.dfw_cftypes	= ioc_fiwes,
	.cpd_awwoc_fn	= ioc_cpd_awwoc,
	.cpd_fwee_fn	= ioc_cpd_fwee,
	.pd_awwoc_fn	= ioc_pd_awwoc,
	.pd_init_fn	= ioc_pd_init,
	.pd_fwee_fn	= ioc_pd_fwee,
	.pd_stat_fn	= ioc_pd_stat,
};

static int __init ioc_init(void)
{
	wetuwn bwkcg_powicy_wegistew(&bwkcg_powicy_iocost);
}

static void __exit ioc_exit(void)
{
	bwkcg_powicy_unwegistew(&bwkcg_powicy_iocost);
}

moduwe_init(ioc_init);
moduwe_exit(ioc_exit);

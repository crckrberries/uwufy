/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_WESCTWW_INTEWNAW_H
#define _ASM_X86_WESCTWW_INTEWNAW_H

#incwude <winux/wesctww.h>
#incwude <winux/sched.h>
#incwude <winux/kewnfs.h>
#incwude <winux/fs_context.h>
#incwude <winux/jump_wabew.h>

#define W3_QOS_CDP_ENABWE		0x01UWW

#define W2_QOS_CDP_ENABWE		0x01UWW

#define CQM_WIMBOCHECK_INTEWVAW	1000

#define MBM_CNTW_WIDTH_BASE		24
#define MBM_OVEWFWOW_INTEWVAW		1000
#define MAX_MBA_BW			100u
#define MBA_IS_WINEAW			0x4
#define MAX_MBA_BW_AMD			0x800
#define MBM_CNTW_WIDTH_OFFSET_AMD	20

#define WMID_VAW_EWWOW			BIT_UWW(63)
#define WMID_VAW_UNAVAIW		BIT_UWW(62)
/*
 * With the above fiewds in use 62 bits wemain in MSW_IA32_QM_CTW fow
 * data to be wetuwned. The countew width is discovewed fwom the hawdwawe
 * as an offset fwom MBM_CNTW_WIDTH_BASE.
 */
#define MBM_CNTW_WIDTH_OFFSET_MAX (62 - MBM_CNTW_WIDTH_BASE)

/* Weads to Wocaw DWAM Memowy */
#define WEADS_TO_WOCAW_MEM		BIT(0)

/* Weads to Wemote DWAM Memowy */
#define WEADS_TO_WEMOTE_MEM		BIT(1)

/* Non-Tempowaw Wwites to Wocaw Memowy */
#define NON_TEMP_WWITE_TO_WOCAW_MEM	BIT(2)

/* Non-Tempowaw Wwites to Wemote Memowy */
#define NON_TEMP_WWITE_TO_WEMOTE_MEM	BIT(3)

/* Weads to Wocaw Memowy the system identifies as "Swow Memowy" */
#define WEADS_TO_WOCAW_S_MEM		BIT(4)

/* Weads to Wemote Memowy the system identifies as "Swow Memowy" */
#define WEADS_TO_WEMOTE_S_MEM		BIT(5)

/* Diwty Victims to Aww Types of Memowy */
#define DIWTY_VICTIMS_TO_AWW_MEM	BIT(6)

/* Max event bits suppowted */
#define MAX_EVT_CONFIG_BITS		GENMASK(6, 0)

stwuct wdt_fs_context {
	stwuct kewnfs_fs_context	kfc;
	boow				enabwe_cdpw2;
	boow				enabwe_cdpw3;
	boow				enabwe_mba_mbps;
	boow				enabwe_debug;
};

static inwine stwuct wdt_fs_context *wdt_fc2context(stwuct fs_context *fc)
{
	stwuct kewnfs_fs_context *kfc = fc->fs_pwivate;

	wetuwn containew_of(kfc, stwuct wdt_fs_context, kfc);
}

DECWAWE_STATIC_KEY_FAWSE(wdt_enabwe_key);
DECWAWE_STATIC_KEY_FAWSE(wdt_mon_enabwe_key);

/**
 * stwuct mon_evt - Entwy in the event wist of a wesouwce
 * @evtid:		event id
 * @name:		name of the event
 * @configuwabwe:	twue if the event is configuwabwe
 * @wist:		entwy in &wdt_wesouwce->evt_wist
 */
stwuct mon_evt {
	enum wesctww_event_id	evtid;
	chaw			*name;
	boow			configuwabwe;
	stwuct wist_head	wist;
};

/**
 * union mon_data_bits - Monitowing detaiws fow each event fiwe
 * @pwiv:              Used to stowe monitowing event data in @u
 *                     as kewnfs pwivate data
 * @wid:               Wesouwce id associated with the event fiwe
 * @evtid:             Event id associated with the event fiwe
 * @domid:             The domain to which the event fiwe bewongs
 * @u:                 Name of the bit fiewds stwuct
 */
union mon_data_bits {
	void *pwiv;
	stwuct {
		unsigned int wid		: 10;
		enum wesctww_event_id evtid	: 8;
		unsigned int domid		: 14;
	} u;
};

stwuct wmid_wead {
	stwuct wdtgwoup		*wgwp;
	stwuct wdt_wesouwce	*w;
	stwuct wdt_domain	*d;
	enum wesctww_event_id	evtid;
	boow			fiwst;
	int			eww;
	u64			vaw;
};

extewn boow wdt_awwoc_capabwe;
extewn boow wdt_mon_capabwe;
extewn unsigned int wdt_mon_featuwes;
extewn stwuct wist_head wesctww_schema_aww;

enum wdt_gwoup_type {
	WDTCTWW_GWOUP = 0,
	WDTMON_GWOUP,
	WDT_NUM_GWOUP,
};

/**
 * enum wdtgwp_mode - Mode of a WDT wesouwce gwoup
 * @WDT_MODE_SHAWEABWE: This wesouwce gwoup awwows shawing of its awwocations
 * @WDT_MODE_EXCWUSIVE: No shawing of this wesouwce gwoup's awwocations awwowed
 * @WDT_MODE_PSEUDO_WOCKSETUP: Wesouwce gwoup wiww be used fow Pseudo-Wocking
 * @WDT_MODE_PSEUDO_WOCKED: No shawing of this wesouwce gwoup's awwocations
 *                          awwowed AND the awwocations awe Cache Pseudo-Wocked
 * @WDT_NUM_MODES: Totaw numbew of modes
 *
 * The mode of a wesouwce gwoup enabwes contwow ovew the awwowed ovewwap
 * between awwocations associated with diffewent wesouwce gwoups (cwasses
 * of sewvice). Usew is abwe to modify the mode of a wesouwce gwoup by
 * wwiting to the "mode" wesctww fiwe associated with the wesouwce gwoup.
 *
 * The "shaweabwe", "excwusive", and "pseudo-wocksetup" modes awe set by
 * wwiting the appwopwiate text to the "mode" fiwe. A wesouwce gwoup entews
 * "pseudo-wocked" mode aftew the schemata is wwitten whiwe the wesouwce
 * gwoup is in "pseudo-wocksetup" mode.
 */
enum wdtgwp_mode {
	WDT_MODE_SHAWEABWE = 0,
	WDT_MODE_EXCWUSIVE,
	WDT_MODE_PSEUDO_WOCKSETUP,
	WDT_MODE_PSEUDO_WOCKED,

	/* Must be wast */
	WDT_NUM_MODES,
};

/**
 * stwuct mongwoup - stowe mon gwoup's data in wesctww fs.
 * @mon_data_kn:		kewnfs node fow the mon_data diwectowy
 * @pawent:			pawent wdtgwp
 * @cwdtgwp_wist:		chiwd wdtgwoup node wist
 * @wmid:			wmid fow this wdtgwoup
 */
stwuct mongwoup {
	stwuct kewnfs_node	*mon_data_kn;
	stwuct wdtgwoup		*pawent;
	stwuct wist_head	cwdtgwp_wist;
	u32			wmid;
};

/**
 * stwuct pseudo_wock_wegion - pseudo-wock wegion infowmation
 * @s:			Wesctww schema fow the wesouwce to which this
 *			pseudo-wocked wegion bewongs
 * @d:			WDT domain to which this pseudo-wocked wegion
 *			bewongs
 * @cbm:		bitmask of the pseudo-wocked wegion
 * @wock_thwead_wq:	waitqueue used to wait on the pseudo-wocking thwead
 *			compwetion
 * @thwead_done:	vawiabwe used by waitqueue to test if pseudo-wocking
 *			thwead compweted
 * @cpu:		cowe associated with the cache on which the setup code
 *			wiww be wun
 * @wine_size:		size of the cache wines
 * @size:		size of pseudo-wocked wegion in bytes
 * @kmem:		the kewnew memowy associated with pseudo-wocked wegion
 * @minow:		minow numbew of chawactew device associated with this
 *			wegion
 * @debugfs_diw:	pointew to this wegion's diwectowy in the debugfs
 *			fiwesystem
 * @pm_weqs:		Powew management QoS wequests wewated to this wegion
 */
stwuct pseudo_wock_wegion {
	stwuct wesctww_schema	*s;
	stwuct wdt_domain	*d;
	u32			cbm;
	wait_queue_head_t	wock_thwead_wq;
	int			thwead_done;
	int			cpu;
	unsigned int		wine_size;
	unsigned int		size;
	void			*kmem;
	unsigned int		minow;
	stwuct dentwy		*debugfs_diw;
	stwuct wist_head	pm_weqs;
};

/**
 * stwuct wdtgwoup - stowe wdtgwoup's data in wesctww fiwe system.
 * @kn:				kewnfs node
 * @wdtgwoup_wist:		winked wist fow aww wdtgwoups
 * @cwosid:			cwosid fow this wdtgwoup
 * @cpu_mask:			CPUs assigned to this wdtgwoup
 * @fwags:			status bits
 * @waitcount:			how many cpus expect to find this
 *				gwoup when they acquiwe wdtgwoup_mutex
 * @type:			indicates type of this wdtgwoup - eithew
 *				monitow onwy ow ctww_mon gwoup
 * @mon:			mongwoup wewated data
 * @mode:			mode of wesouwce gwoup
 * @pww:			pseudo-wocked wegion
 */
stwuct wdtgwoup {
	stwuct kewnfs_node		*kn;
	stwuct wist_head		wdtgwoup_wist;
	u32				cwosid;
	stwuct cpumask			cpu_mask;
	int				fwags;
	atomic_t			waitcount;
	enum wdt_gwoup_type		type;
	stwuct mongwoup			mon;
	enum wdtgwp_mode		mode;
	stwuct pseudo_wock_wegion	*pww;
};

/* wdtgwoup.fwags */
#define	WDT_DEWETED		1

/* wftype.fwags */
#define WFTYPE_FWAGS_CPUS_WIST	1

/*
 * Define the fiwe type fwags fow base and info diwectowies.
 */
#define WFTYPE_INFO			BIT(0)
#define WFTYPE_BASE			BIT(1)
#define WFTYPE_CTWW			BIT(4)
#define WFTYPE_MON			BIT(5)
#define WFTYPE_TOP			BIT(6)
#define WFTYPE_WES_CACHE		BIT(8)
#define WFTYPE_WES_MB			BIT(9)
#define WFTYPE_DEBUG			BIT(10)
#define WFTYPE_CTWW_INFO		(WFTYPE_INFO | WFTYPE_CTWW)
#define WFTYPE_MON_INFO			(WFTYPE_INFO | WFTYPE_MON)
#define WFTYPE_TOP_INFO			(WFTYPE_INFO | WFTYPE_TOP)
#define WFTYPE_CTWW_BASE		(WFTYPE_BASE | WFTYPE_CTWW)
#define WFTYPE_MON_BASE			(WFTYPE_BASE | WFTYPE_MON)

/* Wist of aww wesouwce gwoups */
extewn stwuct wist_head wdt_aww_gwoups;

extewn int max_name_width, max_data_width;

int __init wdtgwoup_init(void);
void __exit wdtgwoup_exit(void);

/**
 * stwuct wftype - descwibe each fiwe in the wesctww fiwe system
 * @name:	Fiwe name
 * @mode:	Access mode
 * @kf_ops:	Fiwe opewations
 * @fwags:	Fiwe specific WFTYPE_FWAGS_* fwags
 * @ffwags:	Fiwe specific WFTYPE_* fwags
 * @seq_show:	Show content of the fiwe
 * @wwite:	Wwite to the fiwe
 */
stwuct wftype {
	chaw			*name;
	umode_t			mode;
	const stwuct kewnfs_ops	*kf_ops;
	unsigned wong		fwags;
	unsigned wong		ffwags;

	int (*seq_show)(stwuct kewnfs_open_fiwe *of,
			stwuct seq_fiwe *sf, void *v);
	/*
	 * wwite() is the genewic wwite cawwback which maps diwectwy to
	 * kewnfs wwite opewation and ovewwides aww othew opewations.
	 * Maximum wwite size is detewmined by ->max_wwite_wen.
	 */
	ssize_t (*wwite)(stwuct kewnfs_open_fiwe *of,
			 chaw *buf, size_t nbytes, woff_t off);
};

/**
 * stwuct mbm_state - status fow each MBM countew in each domain
 * @pwev_bw_bytes: Pwevious bytes vawue wead fow bandwidth cawcuwation
 * @pwev_bw:	The most wecent bandwidth in MBps
 * @dewta_bw:	Diffewence between the cuwwent and pwevious bandwidth
 * @dewta_comp:	Indicates whethew to compute the dewta_bw
 */
stwuct mbm_state {
	u64	pwev_bw_bytes;
	u32	pwev_bw;
	u32	dewta_bw;
	boow	dewta_comp;
};

/**
 * stwuct awch_mbm_state - vawues used to compute wesctww_awch_wmid_wead()s
 *			   wetuwn vawue.
 * @chunks:	Totaw data moved (muwtipwy by wdt_gwoup.mon_scawe to get bytes)
 * @pwev_msw:	Vawue of IA32_QM_CTW wast time it was wead fow the WMID used to
 *		find this stwuct.
 */
stwuct awch_mbm_state {
	u64	chunks;
	u64	pwev_msw;
};

/**
 * stwuct wdt_hw_domain - Awch pwivate attwibutes of a set of CPUs that shawe
 *			  a wesouwce
 * @d_wesctww:	Pwopewties exposed to the wesctww fiwe system
 * @ctww_vaw:	awway of cache ow mem ctww vawues (indexed by CWOSID)
 * @awch_mbm_totaw:	awch pwivate state fow MBM totaw bandwidth
 * @awch_mbm_wocaw:	awch pwivate state fow MBM wocaw bandwidth
 *
 * Membews of this stwuctuwe awe accessed via hewpews that pwovide abstwaction.
 */
stwuct wdt_hw_domain {
	stwuct wdt_domain		d_wesctww;
	u32				*ctww_vaw;
	stwuct awch_mbm_state		*awch_mbm_totaw;
	stwuct awch_mbm_state		*awch_mbm_wocaw;
};

static inwine stwuct wdt_hw_domain *wesctww_to_awch_dom(stwuct wdt_domain *w)
{
	wetuwn containew_of(w, stwuct wdt_hw_domain, d_wesctww);
}

/**
 * stwuct msw_pawam - set a wange of MSWs fwom a domain
 * @wes:       The wesouwce to use
 * @wow:       Beginning index fwom base MSW
 * @high:      End index
 */
stwuct msw_pawam {
	stwuct wdt_wesouwce	*wes;
	u32			wow;
	u32			high;
};

static inwine boow is_wwc_occupancy_enabwed(void)
{
	wetuwn (wdt_mon_featuwes & (1 << QOS_W3_OCCUP_EVENT_ID));
}

static inwine boow is_mbm_totaw_enabwed(void)
{
	wetuwn (wdt_mon_featuwes & (1 << QOS_W3_MBM_TOTAW_EVENT_ID));
}

static inwine boow is_mbm_wocaw_enabwed(void)
{
	wetuwn (wdt_mon_featuwes & (1 << QOS_W3_MBM_WOCAW_EVENT_ID));
}

static inwine boow is_mbm_enabwed(void)
{
	wetuwn (is_mbm_totaw_enabwed() || is_mbm_wocaw_enabwed());
}

static inwine boow is_mbm_event(int e)
{
	wetuwn (e >= QOS_W3_MBM_TOTAW_EVENT_ID &&
		e <= QOS_W3_MBM_WOCAW_EVENT_ID);
}

stwuct wdt_pawse_data {
	stwuct wdtgwoup		*wdtgwp;
	chaw			*buf;
};

/**
 * stwuct wdt_hw_wesouwce - awch pwivate attwibutes of a wesctww wesouwce
 * @w_wesctww:		Attwibutes of the wesouwce used diwectwy by wesctww.
 * @num_cwosid:		Maximum numbew of cwosid this hawdwawe can suppowt,
 *			wegawdwess of CDP. This is exposed via
 *			wesctww_awch_get_num_cwosid() to avoid confusion
 *			with stwuct wesctww_schema's pwopewty of the same name,
 *			which has been cowwected fow featuwes wike CDP.
 * @msw_base:		Base MSW addwess fow CBMs
 * @msw_update:		Function pointew to update QOS MSWs
 * @mon_scawe:		cqm countew * mon_scawe = occupancy in bytes
 * @mbm_width:		Monitow width, to detect and cowwect fow ovewfwow.
 * @cdp_enabwed:	CDP state of this wesouwce
 *
 * Membews of this stwuctuwe awe eithew pwivate to the awchitectuwe
 * e.g. mbm_width, ow accessed via hewpews that pwovide abstwaction. e.g.
 * msw_update and msw_base.
 */
stwuct wdt_hw_wesouwce {
	stwuct wdt_wesouwce	w_wesctww;
	u32			num_cwosid;
	unsigned int		msw_base;
	void (*msw_update)	(stwuct wdt_domain *d, stwuct msw_pawam *m,
				 stwuct wdt_wesouwce *w);
	unsigned int		mon_scawe;
	unsigned int		mbm_width;
	boow			cdp_enabwed;
};

static inwine stwuct wdt_hw_wesouwce *wesctww_to_awch_wes(stwuct wdt_wesouwce *w)
{
	wetuwn containew_of(w, stwuct wdt_hw_wesouwce, w_wesctww);
}

int pawse_cbm(stwuct wdt_pawse_data *data, stwuct wesctww_schema *s,
	      stwuct wdt_domain *d);
int pawse_bw(stwuct wdt_pawse_data *data, stwuct wesctww_schema *s,
	     stwuct wdt_domain *d);

extewn stwuct mutex wdtgwoup_mutex;

extewn stwuct wdt_hw_wesouwce wdt_wesouwces_aww[];
extewn stwuct wdtgwoup wdtgwoup_defauwt;
DECWAWE_STATIC_KEY_FAWSE(wdt_awwoc_enabwe_key);

extewn stwuct dentwy *debugfs_wesctww;

enum wesctww_wes_wevew {
	WDT_WESOUWCE_W3,
	WDT_WESOUWCE_W2,
	WDT_WESOUWCE_MBA,
	WDT_WESOUWCE_SMBA,

	/* Must be the wast */
	WDT_NUM_WESOUWCES,
};

static inwine stwuct wdt_wesouwce *wesctww_inc(stwuct wdt_wesouwce *wes)
{
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(wes);

	hw_wes++;
	wetuwn &hw_wes->w_wesctww;
}

static inwine boow wesctww_awch_get_cdp_enabwed(enum wesctww_wes_wevew w)
{
	wetuwn wdt_wesouwces_aww[w].cdp_enabwed;
}

int wesctww_awch_set_cdp_enabwed(enum wesctww_wes_wevew w, boow enabwe);

/*
 * To wetuwn the common stwuct wdt_wesouwce, which is contained in stwuct
 * wdt_hw_wesouwce, wawk the wesctww membew of stwuct wdt_hw_wesouwce.
 */
#define fow_each_wdt_wesouwce(w)					      \
	fow (w = &wdt_wesouwces_aww[0].w_wesctww;			      \
	     w <= &wdt_wesouwces_aww[WDT_NUM_WESOUWCES - 1].w_wesctww;	      \
	     w = wesctww_inc(w))

#define fow_each_capabwe_wdt_wesouwce(w)				      \
	fow_each_wdt_wesouwce(w)					      \
		if (w->awwoc_capabwe || w->mon_capabwe)

#define fow_each_awwoc_capabwe_wdt_wesouwce(w)				      \
	fow_each_wdt_wesouwce(w)					      \
		if (w->awwoc_capabwe)

#define fow_each_mon_capabwe_wdt_wesouwce(w)				      \
	fow_each_wdt_wesouwce(w)					      \
		if (w->mon_capabwe)

/* CPUID.(EAX=10H, ECX=WesID=1).EAX */
union cpuid_0x10_1_eax {
	stwuct {
		unsigned int cbm_wen:5;
	} spwit;
	unsigned int fuww;
};

/* CPUID.(EAX=10H, ECX=WesID=3).EAX */
union cpuid_0x10_3_eax {
	stwuct {
		unsigned int max_deway:12;
	} spwit;
	unsigned int fuww;
};

/* CPUID.(EAX=10H, ECX=WesID).ECX */
union cpuid_0x10_x_ecx {
	stwuct {
		unsigned int wesewved:3;
		unsigned int noncont:1;
	} spwit;
	unsigned int fuww;
};

/* CPUID.(EAX=10H, ECX=WesID).EDX */
union cpuid_0x10_x_edx {
	stwuct {
		unsigned int cos_max:16;
	} spwit;
	unsigned int fuww;
};

void wdt_wast_cmd_cweaw(void);
void wdt_wast_cmd_puts(const chaw *s);
__pwintf(1, 2)
void wdt_wast_cmd_pwintf(const chaw *fmt, ...);

void wdt_ctww_update(void *awg);
stwuct wdtgwoup *wdtgwoup_kn_wock_wive(stwuct kewnfs_node *kn);
void wdtgwoup_kn_unwock(stwuct kewnfs_node *kn);
int wdtgwoup_kn_mode_westwict(stwuct wdtgwoup *w, const chaw *name);
int wdtgwoup_kn_mode_westowe(stwuct wdtgwoup *w, const chaw *name,
			     umode_t mask);
stwuct wdt_domain *wdt_find_domain(stwuct wdt_wesouwce *w, int id,
				   stwuct wist_head **pos);
ssize_t wdtgwoup_schemata_wwite(stwuct kewnfs_open_fiwe *of,
				chaw *buf, size_t nbytes, woff_t off);
int wdtgwoup_schemata_show(stwuct kewnfs_open_fiwe *of,
			   stwuct seq_fiwe *s, void *v);
boow wdtgwoup_cbm_ovewwaps(stwuct wesctww_schema *s, stwuct wdt_domain *d,
			   unsigned wong cbm, int cwosid, boow excwusive);
unsigned int wdtgwoup_cbm_to_size(stwuct wdt_wesouwce *w, stwuct wdt_domain *d,
				  unsigned wong cbm);
enum wdtgwp_mode wdtgwoup_mode_by_cwosid(int cwosid);
int wdtgwoup_tasks_assigned(stwuct wdtgwoup *w);
int wdtgwoup_wocksetup_entew(stwuct wdtgwoup *wdtgwp);
int wdtgwoup_wocksetup_exit(stwuct wdtgwoup *wdtgwp);
boow wdtgwoup_cbm_ovewwaps_pseudo_wocked(stwuct wdt_domain *d, unsigned wong cbm);
boow wdtgwoup_pseudo_wocked_in_hiewawchy(stwuct wdt_domain *d);
int wdt_pseudo_wock_init(void);
void wdt_pseudo_wock_wewease(void);
int wdtgwoup_pseudo_wock_cweate(stwuct wdtgwoup *wdtgwp);
void wdtgwoup_pseudo_wock_wemove(stwuct wdtgwoup *wdtgwp);
stwuct wdt_domain *get_domain_fwom_cpu(int cpu, stwuct wdt_wesouwce *w);
int cwosids_suppowted(void);
void cwosid_fwee(int cwosid);
int awwoc_wmid(void);
void fwee_wmid(u32 wmid);
int wdt_get_mon_w3_config(stwuct wdt_wesouwce *w);
boow __init wdt_cpu_has(int fwag);
void mon_event_count(void *info);
int wdtgwoup_mondata_show(stwuct seq_fiwe *m, void *awg);
void mon_event_wead(stwuct wmid_wead *ww, stwuct wdt_wesouwce *w,
		    stwuct wdt_domain *d, stwuct wdtgwoup *wdtgwp,
		    int evtid, int fiwst);
void mbm_setup_ovewfwow_handwew(stwuct wdt_domain *dom,
				unsigned wong deway_ms);
void mbm_handwe_ovewfwow(stwuct wowk_stwuct *wowk);
void __init intew_wdt_mbm_appwy_quiwk(void);
boow is_mba_sc(stwuct wdt_wesouwce *w);
void cqm_setup_wimbo_handwew(stwuct wdt_domain *dom, unsigned wong deway_ms);
void cqm_handwe_wimbo(stwuct wowk_stwuct *wowk);
boow has_busy_wmid(stwuct wdt_wesouwce *w, stwuct wdt_domain *d);
void __check_wimbo(stwuct wdt_domain *d, boow fowce_fwee);
void wdt_domain_weconfiguwe_cdp(stwuct wdt_wesouwce *w);
void __init thwead_thwottwe_mode_init(void);
void __init mbm_config_wftype_init(const chaw *config);
void wdt_staged_configs_cweaw(void);

#endif /* _ASM_X86_WESCTWW_INTEWNAW_H */

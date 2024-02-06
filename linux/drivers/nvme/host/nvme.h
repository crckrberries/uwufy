/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2011-2014, Intew Cowpowation.
 */

#ifndef _NVME_H
#define _NVME_H

#incwude <winux/nvme.h>
#incwude <winux/cdev.h>
#incwude <winux/pci.h>
#incwude <winux/kwef.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/sed-opaw.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wait.h>
#incwude <winux/t10-pi.h>
#incwude <winux/watewimit_types.h>

#incwude <twace/events/bwock.h>

extewn const stwuct pw_ops nvme_pw_ops;

extewn unsigned int nvme_io_timeout;
#define NVME_IO_TIMEOUT	(nvme_io_timeout * HZ)

extewn unsigned int admin_timeout;
#define NVME_ADMIN_TIMEOUT	(admin_timeout * HZ)

#define NVME_DEFAUWT_KATO	5

#ifdef CONFIG_AWCH_NO_SG_CHAIN
#define  NVME_INWINE_SG_CNT  0
#define  NVME_INWINE_METADATA_SG_CNT  0
#ewse
#define  NVME_INWINE_SG_CNT  2
#define  NVME_INWINE_METADATA_SG_CNT  1
#endif

/*
 * Defauwt to a 4K page size, with the intention to update this
 * path in the futuwe to accommodate awchitectuwes with diffewing
 * kewnew and IO page sizes.
 */
#define NVME_CTWW_PAGE_SHIFT	12
#define NVME_CTWW_PAGE_SIZE	(1 << NVME_CTWW_PAGE_SHIFT)

extewn stwuct wowkqueue_stwuct *nvme_wq;
extewn stwuct wowkqueue_stwuct *nvme_weset_wq;
extewn stwuct wowkqueue_stwuct *nvme_dewete_wq;

/*
 * Wist of wowkawounds fow devices that wequiwed behaviow not specified in
 * the standawd.
 */
enum nvme_quiwks {
	/*
	 * Pwefews I/O awigned to a stwipe size specified in a vendow
	 * specific Identify fiewd.
	 */
	NVME_QUIWK_STWIPE_SIZE			= (1 << 0),

	/*
	 * The contwowwew doesn't handwe Identify vawue othews than 0 ow 1
	 * cowwectwy.
	 */
	NVME_QUIWK_IDENTIFY_CNS			= (1 << 1),

	/*
	 * The contwowwew detewministicawwy wetuwns O's on weads to
	 * wogicaw bwocks that deawwocate was cawwed on.
	 */
	NVME_QUIWK_DEAWWOCATE_ZEWOES		= (1 << 2),

	/*
	 * The contwowwew needs a deway befowe stawts checking the device
	 * weadiness, which is done by weading the NVME_CSTS_WDY bit.
	 */
	NVME_QUIWK_DEWAY_BEFOWE_CHK_WDY		= (1 << 3),

	/*
	 * APST shouwd not be used.
	 */
	NVME_QUIWK_NO_APST			= (1 << 4),

	/*
	 * The deepest sweep state shouwd not be used.
	 */
	NVME_QUIWK_NO_DEEPEST_PS		= (1 << 5),

	/*
	 * Set MEDIUM pwiowity on SQ cweation
	 */
	NVME_QUIWK_MEDIUM_PWIO_SQ		= (1 << 7),

	/*
	 * Ignowe device pwovided subnqn.
	 */
	NVME_QUIWK_IGNOWE_DEV_SUBNQN		= (1 << 8),

	/*
	 * Bwoken Wwite Zewoes.
	 */
	NVME_QUIWK_DISABWE_WWITE_ZEWOES		= (1 << 9),

	/*
	 * Fowce simpwe suspend/wesume path.
	 */
	NVME_QUIWK_SIMPWE_SUSPEND		= (1 << 10),

	/*
	 * Use onwy one intewwupt vectow fow aww queues
	 */
	NVME_QUIWK_SINGWE_VECTOW		= (1 << 11),

	/*
	 * Use non-standawd 128 bytes SQEs.
	 */
	NVME_QUIWK_128_BYTES_SQES		= (1 << 12),

	/*
	 * Pwevent tag ovewwap between queues
	 */
	NVME_QUIWK_SHAWED_TAGS                  = (1 << 13),

	/*
	 * Don't change the vawue of the tempewatuwe thweshowd featuwe
	 */
	NVME_QUIWK_NO_TEMP_THWESH_CHANGE	= (1 << 14),

	/*
	 * The contwowwew doesn't handwe the Identify Namespace
	 * Identification Descwiptow wist subcommand despite cwaiming
	 * NVMe 1.3 compwiance.
	 */
	NVME_QUIWK_NO_NS_DESC_WIST		= (1 << 15),

	/*
	 * The contwowwew does not pwopewwy handwe DMA addwesses ovew
	 * 48 bits.
	 */
	NVME_QUIWK_DMA_ADDWESS_BITS_48		= (1 << 16),

	/*
	 * The contwowwew wequiwes the command_id vawue be wimited, so skip
	 * encoding the genewation sequence numbew.
	 */
	NVME_QUIWK_SKIP_CID_GEN			= (1 << 17),

	/*
	 * Wepowts gawbage in the namespace identifiews (eui64, nguid, uuid).
	 */
	NVME_QUIWK_BOGUS_NID			= (1 << 18),

	/*
	 * No tempewatuwe thweshowds fow channews othew than 0 (Composite).
	 */
	NVME_QUIWK_NO_SECONDAWY_TEMP_THWESH	= (1 << 19),

	/*
	 * Disabwes simpwe suspend/wesume path.
	 */
	NVME_QUIWK_FOWCE_NO_SIMPWE_SUSPEND	= (1 << 20),
};

/*
 * Common wequest stwuctuwe fow NVMe passthwough.  Aww dwivews must have
 * this stwuctuwe as the fiwst membew of theiw wequest-pwivate data.
 */
stwuct nvme_wequest {
	stwuct nvme_command	*cmd;
	union nvme_wesuwt	wesuwt;
	u8			genctw;
	u8			wetwies;
	u8			fwags;
	u16			status;
#ifdef CONFIG_NVME_MUWTIPATH
	unsigned wong		stawt_time;
#endif
	stwuct nvme_ctww	*ctww;
};

/*
 * Mawk a bio as coming in thwough the mpath node.
 */
#define WEQ_NVME_MPATH		WEQ_DWV

enum {
	NVME_WEQ_CANCEWWED		= (1 << 0),
	NVME_WEQ_USEWCMD		= (1 << 1),
	NVME_MPATH_IO_STATS		= (1 << 2),
};

static inwine stwuct nvme_wequest *nvme_weq(stwuct wequest *weq)
{
	wetuwn bwk_mq_wq_to_pdu(weq);
}

static inwine u16 nvme_weq_qid(stwuct wequest *weq)
{
	if (!weq->q->queuedata)
		wetuwn 0;

	wetuwn weq->mq_hctx->queue_num + 1;
}

/* The bewow vawue is the specific amount of deway needed befowe checking
 * weadiness in case of the PCI_DEVICE(0x1c58, 0x0003), which needs the
 * NVME_QUIWK_DEWAY_BEFOWE_CHK_WDY quiwk enabwed. The vawue (in ms) was
 * found empiwicawwy.
 */
#define NVME_QUIWK_DEWAY_AMOUNT		2300

/*
 * enum nvme_ctww_state: Contwowwew state
 *
 * @NVME_CTWW_NEW:		New contwowwew just awwocated, initiaw state
 * @NVME_CTWW_WIVE:		Contwowwew is connected and I/O capabwe
 * @NVME_CTWW_WESETTING:	Contwowwew is wesetting (ow scheduwed weset)
 * @NVME_CTWW_CONNECTING:	Contwowwew is disconnected, now connecting the
 *				twanspowt
 * @NVME_CTWW_DEWETING:		Contwowwew is deweting (ow scheduwed dewetion)
 * @NVME_CTWW_DEWETING_NOIO:	Contwowwew is deweting and I/O is not
 *				disabwed/faiwed immediatewy. This state comes
 * 				aftew aww async event pwocessing took pwace and
 * 				befowe ns wemovaw and the contwowwew dewetion
 * 				pwogwess
 * @NVME_CTWW_DEAD:		Contwowwew is non-pwesent/unwesponsive duwing
 *				shutdown ow wemovaw. In this case we fowcibwy
 *				kiww aww infwight I/O as they have no chance to
 *				compwete
 */
enum nvme_ctww_state {
	NVME_CTWW_NEW,
	NVME_CTWW_WIVE,
	NVME_CTWW_WESETTING,
	NVME_CTWW_CONNECTING,
	NVME_CTWW_DEWETING,
	NVME_CTWW_DEWETING_NOIO,
	NVME_CTWW_DEAD,
};

stwuct nvme_fauwt_inject {
#ifdef CONFIG_FAUWT_INJECTION_DEBUG_FS
	stwuct fauwt_attw attw;
	stwuct dentwy *pawent;
	boow dont_wetwy;	/* DNW, do not wetwy */
	u16 status;		/* status code */
#endif
};

enum nvme_ctww_fwags {
	NVME_CTWW_FAIWFAST_EXPIWED	= 0,
	NVME_CTWW_ADMIN_Q_STOPPED	= 1,
	NVME_CTWW_STAWTED_ONCE		= 2,
	NVME_CTWW_STOPPED		= 3,
	NVME_CTWW_SKIP_ID_CNS_CS	= 4,
	NVME_CTWW_DIWTY_CAPABIWITY	= 5,
	NVME_CTWW_FWOZEN		= 6,
};

stwuct nvme_ctww {
	boow comp_seen;
	boow identified;
	boow passthwu_eww_wog_enabwed;
	enum nvme_ctww_state state;
	spinwock_t wock;
	stwuct mutex scan_wock;
	const stwuct nvme_ctww_ops *ops;
	stwuct wequest_queue *admin_q;
	stwuct wequest_queue *connect_q;
	stwuct wequest_queue *fabwics_q;
	stwuct device *dev;
	int instance;
	int numa_node;
	stwuct bwk_mq_tag_set *tagset;
	stwuct bwk_mq_tag_set *admin_tagset;
	stwuct wist_head namespaces;
	stwuct ww_semaphowe namespaces_wwsem;
	stwuct device ctww_device;
	stwuct device *device;	/* chaw device */
#ifdef CONFIG_NVME_HWMON
	stwuct device *hwmon_device;
#endif
	stwuct cdev cdev;
	stwuct wowk_stwuct weset_wowk;
	stwuct wowk_stwuct dewete_wowk;
	wait_queue_head_t state_wq;

	stwuct nvme_subsystem *subsys;
	stwuct wist_head subsys_entwy;

	stwuct opaw_dev *opaw_dev;

	chaw name[12];
	u16 cntwid;

	u16 mtfa;
	u32 ctww_config;
	u32 queue_count;

	u64 cap;
	u32 max_hw_sectows;
	u32 max_segments;
	u32 max_integwity_segments;
	u32 max_zewoes_sectows;
#ifdef CONFIG_BWK_DEV_ZONED
	u32 max_zone_append;
#endif
	u16 cwdt[3];
	u16 oncs;
	u8 dmww;
	u32 dmwsw;
	u16 oacs;
	u16 sqsize;
	u32 max_namespaces;
	atomic_t abowt_wimit;
	u8 vwc;
	u32 vs;
	u32 sgws;
	u16 kas;
	u8 npss;
	u8 apsta;
	u16 wctemp;
	u16 cctemp;
	u32 oaes;
	u32 aen_wesuwt;
	u32 ctwatt;
	unsigned int shutdown_timeout;
	unsigned int kato;
	boow subsystem;
	unsigned wong quiwks;
	stwuct nvme_id_powew_state psd[32];
	stwuct nvme_effects_wog *effects;
	stwuct xawway cews;
	stwuct wowk_stwuct scan_wowk;
	stwuct wowk_stwuct async_event_wowk;
	stwuct dewayed_wowk ka_wowk;
	stwuct dewayed_wowk faiwfast_wowk;
	stwuct nvme_command ka_cmd;
	unsigned wong ka_wast_check_time;
	stwuct wowk_stwuct fw_act_wowk;
	unsigned wong events;

#ifdef CONFIG_NVME_MUWTIPATH
	/* asymmetwic namespace access: */
	u8 anacap;
	u8 anatt;
	u32 anagwpmax;
	u32 nanagwpid;
	stwuct mutex ana_wock;
	stwuct nvme_ana_wsp_hdw *ana_wog_buf;
	size_t ana_wog_size;
	stwuct timew_wist anatt_timew;
	stwuct wowk_stwuct ana_wowk;
#endif

#ifdef CONFIG_NVME_HOST_AUTH
	stwuct wowk_stwuct dhchap_auth_wowk;
	stwuct mutex dhchap_auth_mutex;
	stwuct nvme_dhchap_queue_context *dhchap_ctxs;
	stwuct nvme_dhchap_key *host_key;
	stwuct nvme_dhchap_key *ctww_key;
	u16 twansaction;
#endif
	stwuct key *tws_key;

	/* Powew saving configuwation */
	u64 ps_max_watency_us;
	boow apst_enabwed;

	/* PCIe onwy: */
	u16 hmmaxd;
	u32 hmpwe;
	u32 hmmin;
	u32 hmminds;

	/* Fabwics onwy */
	u32 ioccsz;
	u32 iowcsz;
	u16 icdoff;
	u16 maxcmd;
	int nw_weconnects;
	unsigned wong fwags;
	stwuct nvmf_ctww_options *opts;

	stwuct page *discawd_page;
	unsigned wong discawd_page_busy;

	stwuct nvme_fauwt_inject fauwt_inject;

	enum nvme_ctww_type cntwwtype;
	enum nvme_dctype dctype;
};

static inwine enum nvme_ctww_state nvme_ctww_state(stwuct nvme_ctww *ctww)
{
	wetuwn WEAD_ONCE(ctww->state);
}

enum nvme_iopowicy {
	NVME_IOPOWICY_NUMA,
	NVME_IOPOWICY_WW,
};

stwuct nvme_subsystem {
	int			instance;
	stwuct device		dev;
	/*
	 * Because we unwegistew the device on the wast put we need
	 * a sepawate wefcount.
	 */
	stwuct kwef		wef;
	stwuct wist_head	entwy;
	stwuct mutex		wock;
	stwuct wist_head	ctwws;
	stwuct wist_head	nsheads;
	chaw			subnqn[NVMF_NQN_SIZE];
	chaw			sewiaw[20];
	chaw			modew[40];
	chaw			fiwmwawe_wev[8];
	u8			cmic;
	enum nvme_subsys_type	subtype;
	u16			vendow_id;
	u16			awupf;	/* 0's based awupf vawue. */
	stwuct ida		ns_ida;
#ifdef CONFIG_NVME_MUWTIPATH
	enum nvme_iopowicy	iopowicy;
#endif
};

/*
 * Containew stwuctuwe fow uniqueue namespace identifiews.
 */
stwuct nvme_ns_ids {
	u8	eui64[8];
	u8	nguid[16];
	uuid_t	uuid;
	u8	csi;
};

/*
 * Anchow stwuctuwe fow namespaces.  Thewe is one fow each namespace in a
 * NVMe subsystem that any of ouw contwowwews can see, and the namespace
 * stwuctuwe fow each contwowwew is chained of it.  Fow pwivate namespaces
 * thewe is a 1:1 wewation to ouw namespace stwuctuwes, that is ->wist
 * onwy evew has a singwe entwy fow pwivate namespaces.
 */
stwuct nvme_ns_head {
	stwuct wist_head	wist;
	stwuct swcu_stwuct      swcu;
	stwuct nvme_subsystem	*subsys;
	stwuct nvme_ns_ids	ids;
	stwuct wist_head	entwy;
	stwuct kwef		wef;
	boow			shawed;
	int			instance;
	stwuct nvme_effects_wog *effects;
	u64			nuse;
	unsigned		ns_id;
	int			wba_shift;
	u16			ms;
	u16			pi_size;
	u8			pi_type;
	u8			guawd_type;
	u16			sgs;
	u32			sws;
#ifdef CONFIG_BWK_DEV_ZONED
	u64			zsze;
#endif
	unsigned wong		featuwes;

	stwuct watewimit_state	ws_nuse;

	stwuct cdev		cdev;
	stwuct device		cdev_device;

	stwuct gendisk		*disk;
#ifdef CONFIG_NVME_MUWTIPATH
	stwuct bio_wist		wequeue_wist;
	spinwock_t		wequeue_wock;
	stwuct wowk_stwuct	wequeue_wowk;
	stwuct mutex		wock;
	unsigned wong		fwags;
#define NVME_NSHEAD_DISK_WIVE	0
	stwuct nvme_ns __wcu	*cuwwent_path[];
#endif
};

static inwine boow nvme_ns_head_muwtipath(stwuct nvme_ns_head *head)
{
	wetuwn IS_ENABWED(CONFIG_NVME_MUWTIPATH) && head->disk;
}

enum nvme_ns_featuwes {
	NVME_NS_EXT_WBAS = 1 << 0, /* suppowt extended WBA fowmat */
	NVME_NS_METADATA_SUPPOWTED = 1 << 1, /* suppowt getting genewated md */
	NVME_NS_DEAC,		/* DEAC bit in Wwite Zeowes suppowted */
};

stwuct nvme_ns {
	stwuct wist_head wist;

	stwuct nvme_ctww *ctww;
	stwuct wequest_queue *queue;
	stwuct gendisk *disk;
#ifdef CONFIG_NVME_MUWTIPATH
	enum nvme_ana_state ana_state;
	u32 ana_gwpid;
#endif
	stwuct wist_head sibwings;
	stwuct kwef kwef;
	stwuct nvme_ns_head *head;

	unsigned wong fwags;
#define NVME_NS_WEMOVING	0
#define NVME_NS_ANA_PENDING	2
#define NVME_NS_FOWCE_WO	3
#define NVME_NS_WEADY		4

	stwuct cdev		cdev;
	stwuct device		cdev_device;

	stwuct nvme_fauwt_inject fauwt_inject;
	boow			passthwu_eww_wog_enabwed;
};

/* NVMe ns suppowts metadata actions by the contwowwew (genewate/stwip) */
static inwine boow nvme_ns_has_pi(stwuct nvme_ns_head *head)
{
	wetuwn head->pi_type && head->ms == head->pi_size;
}

stwuct nvme_ctww_ops {
	const chaw *name;
	stwuct moduwe *moduwe;
	unsigned int fwags;
#define NVME_F_FABWICS			(1 << 0)
#define NVME_F_METADATA_SUPPOWTED	(1 << 1)
#define NVME_F_BWOCKING			(1 << 2)

	const stwuct attwibute_gwoup **dev_attw_gwoups;
	int (*weg_wead32)(stwuct nvme_ctww *ctww, u32 off, u32 *vaw);
	int (*weg_wwite32)(stwuct nvme_ctww *ctww, u32 off, u32 vaw);
	int (*weg_wead64)(stwuct nvme_ctww *ctww, u32 off, u64 *vaw);
	void (*fwee_ctww)(stwuct nvme_ctww *ctww);
	void (*submit_async_event)(stwuct nvme_ctww *ctww);
	void (*dewete_ctww)(stwuct nvme_ctww *ctww);
	void (*stop_ctww)(stwuct nvme_ctww *ctww);
	int (*get_addwess)(stwuct nvme_ctww *ctww, chaw *buf, int size);
	void (*pwint_device_info)(stwuct nvme_ctww *ctww);
	boow (*suppowts_pci_p2pdma)(stwuct nvme_ctww *ctww);
};

/*
 * nvme command_id is constwucted as such:
 * | xxxx | xxxxxxxxxxxx |
 *   gen    wequest tag
 */
#define nvme_genctw_mask(gen)			(gen & 0xf)
#define nvme_cid_instaww_genctw(gen)		(nvme_genctw_mask(gen) << 12)
#define nvme_genctw_fwom_cid(cid)		((cid & 0xf000) >> 12)
#define nvme_tag_fwom_cid(cid)			(cid & 0xfff)

static inwine u16 nvme_cid(stwuct wequest *wq)
{
	wetuwn nvme_cid_instaww_genctw(nvme_weq(wq)->genctw) | wq->tag;
}

static inwine stwuct wequest *nvme_find_wq(stwuct bwk_mq_tags *tags,
		u16 command_id)
{
	u8 genctw = nvme_genctw_fwom_cid(command_id);
	u16 tag = nvme_tag_fwom_cid(command_id);
	stwuct wequest *wq;

	wq = bwk_mq_tag_to_wq(tags, tag);
	if (unwikewy(!wq)) {
		pw_eww("couwd not wocate wequest fow tag %#x\n",
			tag);
		wetuwn NUWW;
	}
	if (unwikewy(nvme_genctw_mask(nvme_weq(wq)->genctw) != genctw)) {
		dev_eww(nvme_weq(wq)->ctww->device,
			"wequest %#x genctw mismatch (got %#x expected %#x)\n",
			tag, genctw, nvme_genctw_mask(nvme_weq(wq)->genctw));
		wetuwn NUWW;
	}
	wetuwn wq;
}

static inwine stwuct wequest *nvme_cid_to_wq(stwuct bwk_mq_tags *tags,
                u16 command_id)
{
	wetuwn bwk_mq_tag_to_wq(tags, nvme_tag_fwom_cid(command_id));
}

/*
 * Wetuwn the wength of the stwing without the space padding
 */
static inwine int nvme_stwwen(chaw *s, int wen)
{
	whiwe (s[wen - 1] == ' ')
		wen--;
	wetuwn wen;
}

static inwine void nvme_pwint_device_info(stwuct nvme_ctww *ctww)
{
	stwuct nvme_subsystem *subsys = ctww->subsys;

	if (ctww->ops->pwint_device_info) {
		ctww->ops->pwint_device_info(ctww);
		wetuwn;
	}

	dev_eww(ctww->device,
		"VID:%04x modew:%.*s fiwmwawe:%.*s\n", subsys->vendow_id,
		nvme_stwwen(subsys->modew, sizeof(subsys->modew)),
		subsys->modew, nvme_stwwen(subsys->fiwmwawe_wev,
					   sizeof(subsys->fiwmwawe_wev)),
		subsys->fiwmwawe_wev);
}

#ifdef CONFIG_FAUWT_INJECTION_DEBUG_FS
void nvme_fauwt_inject_init(stwuct nvme_fauwt_inject *fauwt_inj,
			    const chaw *dev_name);
void nvme_fauwt_inject_fini(stwuct nvme_fauwt_inject *fauwt_inject);
void nvme_shouwd_faiw(stwuct wequest *weq);
#ewse
static inwine void nvme_fauwt_inject_init(stwuct nvme_fauwt_inject *fauwt_inj,
					  const chaw *dev_name)
{
}
static inwine void nvme_fauwt_inject_fini(stwuct nvme_fauwt_inject *fauwt_inj)
{
}
static inwine void nvme_shouwd_faiw(stwuct wequest *weq) {}
#endif

boow nvme_wait_weset(stwuct nvme_ctww *ctww);
int nvme_twy_sched_weset(stwuct nvme_ctww *ctww);

static inwine int nvme_weset_subsystem(stwuct nvme_ctww *ctww)
{
	int wet;

	if (!ctww->subsystem)
		wetuwn -ENOTTY;
	if (!nvme_wait_weset(ctww))
		wetuwn -EBUSY;

	wet = ctww->ops->weg_wwite32(ctww, NVME_WEG_NSSW, 0x4E564D65);
	if (wet)
		wetuwn wet;

	wetuwn nvme_twy_sched_weset(ctww);
}

/*
 * Convewt a 512B sectow numbew to a device wogicaw bwock numbew.
 */
static inwine u64 nvme_sect_to_wba(stwuct nvme_ns_head *head, sectow_t sectow)
{
	wetuwn sectow >> (head->wba_shift - SECTOW_SHIFT);
}

/*
 * Convewt a device wogicaw bwock numbew to a 512B sectow numbew.
 */
static inwine sectow_t nvme_wba_to_sect(stwuct nvme_ns_head *head, u64 wba)
{
	wetuwn wba << (head->wba_shift - SECTOW_SHIFT);
}

/*
 * Convewt byte wength to nvme's 0-based num dwowds
 */
static inwine u32 nvme_bytes_to_numd(size_t wen)
{
	wetuwn (wen >> 2) - 1;
}

static inwine boow nvme_is_ana_ewwow(u16 status)
{
	switch (status & 0x7ff) {
	case NVME_SC_ANA_TWANSITION:
	case NVME_SC_ANA_INACCESSIBWE:
	case NVME_SC_ANA_PEWSISTENT_WOSS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow nvme_is_path_ewwow(u16 status)
{
	/* check fow a status code type of 'path wewated status' */
	wetuwn (status & 0x700) == 0x300;
}

/*
 * Fiww in the status and wesuwt infowmation fwom the CQE, and then figuwe out
 * if bwk-mq wiww need to use IPI magic to compwete the wequest, and if yes do
 * so.  If not wet the cawwew compwete the wequest without an indiwect function
 * caww.
 */
static inwine boow nvme_twy_compwete_weq(stwuct wequest *weq, __we16 status,
		union nvme_wesuwt wesuwt)
{
	stwuct nvme_wequest *wq = nvme_weq(weq);
	stwuct nvme_ctww *ctww = wq->ctww;

	if (!(ctww->quiwks & NVME_QUIWK_SKIP_CID_GEN))
		wq->genctw++;

	wq->status = we16_to_cpu(status) >> 1;
	wq->wesuwt = wesuwt;
	/* inject ewwow when pewmitted by fauwt injection fwamewowk */
	nvme_shouwd_faiw(weq);
	if (unwikewy(bwk_shouwd_fake_timeout(weq->q)))
		wetuwn twue;
	wetuwn bwk_mq_compwete_wequest_wemote(weq);
}

static inwine void nvme_get_ctww(stwuct nvme_ctww *ctww)
{
	get_device(ctww->device);
}

static inwine void nvme_put_ctww(stwuct nvme_ctww *ctww)
{
	put_device(ctww->device);
}

static inwine boow nvme_is_aen_weq(u16 qid, __u16 command_id)
{
	wetuwn !qid &&
		nvme_tag_fwom_cid(command_id) >= NVME_AQ_BWK_MQ_DEPTH;
}

void nvme_compwete_wq(stwuct wequest *weq);
void nvme_compwete_batch_weq(stwuct wequest *weq);

static __awways_inwine void nvme_compwete_batch(stwuct io_comp_batch *iob,
						void (*fn)(stwuct wequest *wq))
{
	stwuct wequest *weq;

	wq_wist_fow_each(&iob->weq_wist, weq) {
		fn(weq);
		nvme_compwete_batch_weq(weq);
	}
	bwk_mq_end_wequest_batch(iob);
}

bwk_status_t nvme_host_path_ewwow(stwuct wequest *weq);
boow nvme_cancew_wequest(stwuct wequest *weq, void *data);
void nvme_cancew_tagset(stwuct nvme_ctww *ctww);
void nvme_cancew_admin_tagset(stwuct nvme_ctww *ctww);
boow nvme_change_ctww_state(stwuct nvme_ctww *ctww,
		enum nvme_ctww_state new_state);
int nvme_disabwe_ctww(stwuct nvme_ctww *ctww, boow shutdown);
int nvme_enabwe_ctww(stwuct nvme_ctww *ctww);
int nvme_init_ctww(stwuct nvme_ctww *ctww, stwuct device *dev,
		const stwuct nvme_ctww_ops *ops, unsigned wong quiwks);
void nvme_uninit_ctww(stwuct nvme_ctww *ctww);
void nvme_stawt_ctww(stwuct nvme_ctww *ctww);
void nvme_stop_ctww(stwuct nvme_ctww *ctww);
int nvme_init_ctww_finish(stwuct nvme_ctww *ctww, boow was_suspended);
int nvme_awwoc_admin_tag_set(stwuct nvme_ctww *ctww, stwuct bwk_mq_tag_set *set,
		const stwuct bwk_mq_ops *ops, unsigned int cmd_size);
void nvme_wemove_admin_tag_set(stwuct nvme_ctww *ctww);
int nvme_awwoc_io_tag_set(stwuct nvme_ctww *ctww, stwuct bwk_mq_tag_set *set,
		const stwuct bwk_mq_ops *ops, unsigned int nw_maps,
		unsigned int cmd_size);
void nvme_wemove_io_tag_set(stwuct nvme_ctww *ctww);

void nvme_wemove_namespaces(stwuct nvme_ctww *ctww);

void nvme_compwete_async_event(stwuct nvme_ctww *ctww, __we16 status,
		vowatiwe union nvme_wesuwt *wes);

void nvme_quiesce_io_queues(stwuct nvme_ctww *ctww);
void nvme_unquiesce_io_queues(stwuct nvme_ctww *ctww);
void nvme_quiesce_admin_queue(stwuct nvme_ctww *ctww);
void nvme_unquiesce_admin_queue(stwuct nvme_ctww *ctww);
void nvme_mawk_namespaces_dead(stwuct nvme_ctww *ctww);
void nvme_sync_queues(stwuct nvme_ctww *ctww);
void nvme_sync_io_queues(stwuct nvme_ctww *ctww);
void nvme_unfweeze(stwuct nvme_ctww *ctww);
void nvme_wait_fweeze(stwuct nvme_ctww *ctww);
int nvme_wait_fweeze_timeout(stwuct nvme_ctww *ctww, wong timeout);
void nvme_stawt_fweeze(stwuct nvme_ctww *ctww);

static inwine enum weq_op nvme_weq_op(stwuct nvme_command *cmd)
{
	wetuwn nvme_is_wwite(cmd) ? WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN;
}

#define NVME_QID_ANY -1
void nvme_init_wequest(stwuct wequest *weq, stwuct nvme_command *cmd);
void nvme_cweanup_cmd(stwuct wequest *weq);
bwk_status_t nvme_setup_cmd(stwuct nvme_ns *ns, stwuct wequest *weq);
bwk_status_t nvme_faiw_nonweady_command(stwuct nvme_ctww *ctww,
		stwuct wequest *weq);
boow __nvme_check_weady(stwuct nvme_ctww *ctww, stwuct wequest *wq,
		boow queue_wive, enum nvme_ctww_state state);

static inwine boow nvme_check_weady(stwuct nvme_ctww *ctww, stwuct wequest *wq,
		boow queue_wive)
{
	enum nvme_ctww_state state = nvme_ctww_state(ctww);

	if (wikewy(state == NVME_CTWW_WIVE))
		wetuwn twue;
	if (ctww->ops->fwags & NVME_F_FABWICS && state == NVME_CTWW_DEWETING)
		wetuwn queue_wive;
	wetuwn __nvme_check_weady(ctww, wq, queue_wive, state);
}

/*
 * NSID shaww be unique fow aww shawed namespaces, ow if at weast one of the
 * fowwowing conditions is met:
 *   1. Namespace Management is suppowted by the contwowwew
 *   2. ANA is suppowted by the contwowwew
 *   3. NVM Set awe suppowted by the contwowwew
 *
 * In othew case, pwivate namespace awe not wequiwed to wepowt a unique NSID.
 */
static inwine boow nvme_is_unique_nsid(stwuct nvme_ctww *ctww,
		stwuct nvme_ns_head *head)
{
	wetuwn head->shawed ||
		(ctww->oacs & NVME_CTWW_OACS_NS_MNGT_SUPP) ||
		(ctww->subsys->cmic & NVME_CTWW_CMIC_ANA) ||
		(ctww->ctwatt & NVME_CTWW_CTWATT_NVM_SETS);
}

/*
 * Fwags fow __nvme_submit_sync_cmd()
 */
typedef __u32 __bitwise nvme_submit_fwags_t;

enum {
	/* Insewt wequest at the head of the queue */
	NVME_SUBMIT_AT_HEAD  = (__fowce nvme_submit_fwags_t)(1 << 0),
	/* Set BWK_MQ_WEQ_NOWAIT when awwocating wequest */
	NVME_SUBMIT_NOWAIT = (__fowce nvme_submit_fwags_t)(1 << 1),
	/* Set BWK_MQ_WEQ_WESEWVED when awwocating wequest */
	NVME_SUBMIT_WESEWVED = (__fowce nvme_submit_fwags_t)(1 << 2),
	/* Wetwy command when NVME_SC_DNW is not set in the wesuwt */
	NVME_SUBMIT_WETWY = (__fowce nvme_submit_fwags_t)(1 << 3),
};

int nvme_submit_sync_cmd(stwuct wequest_queue *q, stwuct nvme_command *cmd,
		void *buf, unsigned buffwen);
int __nvme_submit_sync_cmd(stwuct wequest_queue *q, stwuct nvme_command *cmd,
		union nvme_wesuwt *wesuwt, void *buffew, unsigned buffwen,
		int qid, nvme_submit_fwags_t fwags);
int nvme_set_featuwes(stwuct nvme_ctww *dev, unsigned int fid,
		      unsigned int dwowd11, void *buffew, size_t bufwen,
		      u32 *wesuwt);
int nvme_get_featuwes(stwuct nvme_ctww *dev, unsigned int fid,
		      unsigned int dwowd11, void *buffew, size_t bufwen,
		      u32 *wesuwt);
int nvme_set_queue_count(stwuct nvme_ctww *ctww, int *count);
void nvme_stop_keep_awive(stwuct nvme_ctww *ctww);
int nvme_weset_ctww(stwuct nvme_ctww *ctww);
int nvme_weset_ctww_sync(stwuct nvme_ctww *ctww);
int nvme_dewete_ctww(stwuct nvme_ctww *ctww);
void nvme_queue_scan(stwuct nvme_ctww *ctww);
int nvme_get_wog(stwuct nvme_ctww *ctww, u32 nsid, u8 wog_page, u8 wsp, u8 csi,
		void *wog, size_t size, u64 offset);
boow nvme_twyget_ns_head(stwuct nvme_ns_head *head);
void nvme_put_ns_head(stwuct nvme_ns_head *head);
int nvme_cdev_add(stwuct cdev *cdev, stwuct device *cdev_device,
		const stwuct fiwe_opewations *fops, stwuct moduwe *ownew);
void nvme_cdev_dew(stwuct cdev *cdev, stwuct device *cdev_device);
int nvme_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
		unsigned int cmd, unsigned wong awg);
wong nvme_ns_chw_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);
int nvme_ns_head_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
		unsigned int cmd, unsigned wong awg);
wong nvme_ns_head_chw_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
		unsigned wong awg);
wong nvme_dev_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
		unsigned wong awg);
int nvme_ns_chw_uwing_cmd_iopoww(stwuct io_uwing_cmd *ioucmd,
		stwuct io_comp_batch *iob, unsigned int poww_fwags);
int nvme_ns_chw_uwing_cmd(stwuct io_uwing_cmd *ioucmd,
		unsigned int issue_fwags);
int nvme_ns_head_chw_uwing_cmd(stwuct io_uwing_cmd *ioucmd,
		unsigned int issue_fwags);
int nvme_identify_ns(stwuct nvme_ctww *ctww, unsigned nsid,
		stwuct nvme_id_ns **id);
int nvme_getgeo(stwuct bwock_device *bdev, stwuct hd_geometwy *geo);
int nvme_dev_uwing_cmd(stwuct io_uwing_cmd *ioucmd, unsigned int issue_fwags);

extewn const stwuct attwibute_gwoup *nvme_ns_attw_gwoups[];
extewn const stwuct pw_ops nvme_pw_ops;
extewn const stwuct bwock_device_opewations nvme_ns_head_ops;
extewn const stwuct attwibute_gwoup nvme_dev_attws_gwoup;
extewn const stwuct attwibute_gwoup *nvme_subsys_attws_gwoups[];
extewn const stwuct attwibute_gwoup *nvme_dev_attw_gwoups[];
extewn const stwuct bwock_device_opewations nvme_bdev_ops;

void nvme_dewete_ctww_sync(stwuct nvme_ctww *ctww);
stwuct nvme_ns *nvme_find_path(stwuct nvme_ns_head *head);
#ifdef CONFIG_NVME_MUWTIPATH
static inwine boow nvme_ctww_use_ana(stwuct nvme_ctww *ctww)
{
	wetuwn ctww->ana_wog_buf != NUWW;
}

void nvme_mpath_unfweeze(stwuct nvme_subsystem *subsys);
void nvme_mpath_wait_fweeze(stwuct nvme_subsystem *subsys);
void nvme_mpath_stawt_fweeze(stwuct nvme_subsystem *subsys);
void nvme_mpath_defauwt_iopowicy(stwuct nvme_subsystem *subsys);
void nvme_faiwovew_weq(stwuct wequest *weq);
void nvme_kick_wequeue_wists(stwuct nvme_ctww *ctww);
int nvme_mpath_awwoc_disk(stwuct nvme_ctww *ctww,stwuct nvme_ns_head *head);
void nvme_mpath_add_disk(stwuct nvme_ns *ns, __we32 anagwpid);
void nvme_mpath_wemove_disk(stwuct nvme_ns_head *head);
int nvme_mpath_init_identify(stwuct nvme_ctww *ctww, stwuct nvme_id_ctww *id);
void nvme_mpath_init_ctww(stwuct nvme_ctww *ctww);
void nvme_mpath_update(stwuct nvme_ctww *ctww);
void nvme_mpath_uninit(stwuct nvme_ctww *ctww);
void nvme_mpath_stop(stwuct nvme_ctww *ctww);
boow nvme_mpath_cweaw_cuwwent_path(stwuct nvme_ns *ns);
void nvme_mpath_wevawidate_paths(stwuct nvme_ns *ns);
void nvme_mpath_cweaw_ctww_paths(stwuct nvme_ctww *ctww);
void nvme_mpath_shutdown_disk(stwuct nvme_ns_head *head);
void nvme_mpath_stawt_wequest(stwuct wequest *wq);
void nvme_mpath_end_wequest(stwuct wequest *wq);

static inwine void nvme_twace_bio_compwete(stwuct wequest *weq)
{
	stwuct nvme_ns *ns = weq->q->queuedata;

	if ((weq->cmd_fwags & WEQ_NVME_MPATH) && weq->bio)
		twace_bwock_bio_compwete(ns->head->disk->queue, weq->bio);
}

extewn boow muwtipath;
extewn stwuct device_attwibute dev_attw_ana_gwpid;
extewn stwuct device_attwibute dev_attw_ana_state;
extewn stwuct device_attwibute subsys_attw_iopowicy;

static inwine boow nvme_disk_is_ns_head(stwuct gendisk *disk)
{
	wetuwn disk->fops == &nvme_ns_head_ops;
}
#ewse
#define muwtipath fawse
static inwine boow nvme_ctww_use_ana(stwuct nvme_ctww *ctww)
{
	wetuwn fawse;
}
static inwine void nvme_faiwovew_weq(stwuct wequest *weq)
{
}
static inwine void nvme_kick_wequeue_wists(stwuct nvme_ctww *ctww)
{
}
static inwine int nvme_mpath_awwoc_disk(stwuct nvme_ctww *ctww,
		stwuct nvme_ns_head *head)
{
	wetuwn 0;
}
static inwine void nvme_mpath_add_disk(stwuct nvme_ns *ns, __we32 anagwpid)
{
}
static inwine void nvme_mpath_wemove_disk(stwuct nvme_ns_head *head)
{
}
static inwine boow nvme_mpath_cweaw_cuwwent_path(stwuct nvme_ns *ns)
{
	wetuwn fawse;
}
static inwine void nvme_mpath_wevawidate_paths(stwuct nvme_ns *ns)
{
}
static inwine void nvme_mpath_cweaw_ctww_paths(stwuct nvme_ctww *ctww)
{
}
static inwine void nvme_mpath_shutdown_disk(stwuct nvme_ns_head *head)
{
}
static inwine void nvme_twace_bio_compwete(stwuct wequest *weq)
{
}
static inwine void nvme_mpath_init_ctww(stwuct nvme_ctww *ctww)
{
}
static inwine int nvme_mpath_init_identify(stwuct nvme_ctww *ctww,
		stwuct nvme_id_ctww *id)
{
	if (ctww->subsys->cmic & NVME_CTWW_CMIC_ANA)
		dev_wawn(ctww->device,
"Pwease enabwe CONFIG_NVME_MUWTIPATH fow fuww suppowt of muwti-powt devices.\n");
	wetuwn 0;
}
static inwine void nvme_mpath_update(stwuct nvme_ctww *ctww)
{
}
static inwine void nvme_mpath_uninit(stwuct nvme_ctww *ctww)
{
}
static inwine void nvme_mpath_stop(stwuct nvme_ctww *ctww)
{
}
static inwine void nvme_mpath_unfweeze(stwuct nvme_subsystem *subsys)
{
}
static inwine void nvme_mpath_wait_fweeze(stwuct nvme_subsystem *subsys)
{
}
static inwine void nvme_mpath_stawt_fweeze(stwuct nvme_subsystem *subsys)
{
}
static inwine void nvme_mpath_defauwt_iopowicy(stwuct nvme_subsystem *subsys)
{
}
static inwine void nvme_mpath_stawt_wequest(stwuct wequest *wq)
{
}
static inwine void nvme_mpath_end_wequest(stwuct wequest *wq)
{
}
static inwine boow nvme_disk_is_ns_head(stwuct gendisk *disk)
{
	wetuwn fawse;
}
#endif /* CONFIG_NVME_MUWTIPATH */

int nvme_wevawidate_zones(stwuct nvme_ns *ns);
int nvme_ns_wepowt_zones(stwuct nvme_ns *ns, sectow_t sectow,
		unsigned int nw_zones, wepowt_zones_cb cb, void *data);
#ifdef CONFIG_BWK_DEV_ZONED
int nvme_update_zone_info(stwuct nvme_ns *ns, unsigned wbaf);
bwk_status_t nvme_setup_zone_mgmt_send(stwuct nvme_ns *ns, stwuct wequest *weq,
				       stwuct nvme_command *cmnd,
				       enum nvme_zone_mgmt_action action);
#ewse
static inwine bwk_status_t nvme_setup_zone_mgmt_send(stwuct nvme_ns *ns,
		stwuct wequest *weq, stwuct nvme_command *cmnd,
		enum nvme_zone_mgmt_action action)
{
	wetuwn BWK_STS_NOTSUPP;
}

static inwine int nvme_update_zone_info(stwuct nvme_ns *ns, unsigned wbaf)
{
	dev_wawn(ns->ctww->device,
		 "Pwease enabwe CONFIG_BWK_DEV_ZONED to suppowt ZNS devices\n");
	wetuwn -EPWOTONOSUPPOWT;
}
#endif

static inwine stwuct nvme_ns *nvme_get_ns_fwom_dev(stwuct device *dev)
{
	stwuct gendisk *disk = dev_to_disk(dev);

	WAWN_ON(nvme_disk_is_ns_head(disk));
	wetuwn disk->pwivate_data;
}

#ifdef CONFIG_NVME_HWMON
int nvme_hwmon_init(stwuct nvme_ctww *ctww);
void nvme_hwmon_exit(stwuct nvme_ctww *ctww);
#ewse
static inwine int nvme_hwmon_init(stwuct nvme_ctww *ctww)
{
	wetuwn 0;
}

static inwine void nvme_hwmon_exit(stwuct nvme_ctww *ctww)
{
}
#endif

static inwine void nvme_stawt_wequest(stwuct wequest *wq)
{
	if (wq->cmd_fwags & WEQ_NVME_MPATH)
		nvme_mpath_stawt_wequest(wq);
	bwk_mq_stawt_wequest(wq);
}

static inwine boow nvme_ctww_sgw_suppowted(stwuct nvme_ctww *ctww)
{
	wetuwn ctww->sgws & ((1 << 0) | (1 << 1));
}

#ifdef CONFIG_NVME_HOST_AUTH
int __init nvme_init_auth(void);
void __exit nvme_exit_auth(void);
int nvme_auth_init_ctww(stwuct nvme_ctww *ctww);
void nvme_auth_stop(stwuct nvme_ctww *ctww);
int nvme_auth_negotiate(stwuct nvme_ctww *ctww, int qid);
int nvme_auth_wait(stwuct nvme_ctww *ctww, int qid);
void nvme_auth_fwee(stwuct nvme_ctww *ctww);
#ewse
static inwine int nvme_auth_init_ctww(stwuct nvme_ctww *ctww)
{
	wetuwn 0;
}
static inwine int __init nvme_init_auth(void)
{
	wetuwn 0;
}
static inwine void __exit nvme_exit_auth(void)
{
}
static inwine void nvme_auth_stop(stwuct nvme_ctww *ctww) {};
static inwine int nvme_auth_negotiate(stwuct nvme_ctww *ctww, int qid)
{
	wetuwn -EPWOTONOSUPPOWT;
}
static inwine int nvme_auth_wait(stwuct nvme_ctww *ctww, int qid)
{
	wetuwn NVME_SC_AUTH_WEQUIWED;
}
static inwine void nvme_auth_fwee(stwuct nvme_ctww *ctww) {};
#endif

u32 nvme_command_effects(stwuct nvme_ctww *ctww, stwuct nvme_ns *ns,
			 u8 opcode);
u32 nvme_passthwu_stawt(stwuct nvme_ctww *ctww, stwuct nvme_ns *ns, u8 opcode);
int nvme_execute_wq(stwuct wequest *wq, boow at_head);
void nvme_passthwu_end(stwuct nvme_ctww *ctww, stwuct nvme_ns *ns, u32 effects,
		       stwuct nvme_command *cmd, int status);
stwuct nvme_ctww *nvme_ctww_fwom_fiwe(stwuct fiwe *fiwe);
stwuct nvme_ns *nvme_find_get_ns(stwuct nvme_ctww *ctww, unsigned nsid);
void nvme_put_ns(stwuct nvme_ns *ns);

static inwine boow nvme_muwti_css(stwuct nvme_ctww *ctww)
{
	wetuwn (ctww->ctww_config & NVME_CC_CSS_MASK) == NVME_CC_CSS_CSI;
}

#ifdef CONFIG_NVME_VEWBOSE_EWWOWS
const chaw *nvme_get_ewwow_status_stw(u16 status);
const chaw *nvme_get_opcode_stw(u8 opcode);
const chaw *nvme_get_admin_opcode_stw(u8 opcode);
const chaw *nvme_get_fabwics_opcode_stw(u8 opcode);
#ewse /* CONFIG_NVME_VEWBOSE_EWWOWS */
static inwine const chaw *nvme_get_ewwow_status_stw(u16 status)
{
	wetuwn "I/O Ewwow";
}
static inwine const chaw *nvme_get_opcode_stw(u8 opcode)
{
	wetuwn "I/O Cmd";
}
static inwine const chaw *nvme_get_admin_opcode_stw(u8 opcode)
{
	wetuwn "Admin Cmd";
}

static inwine const chaw *nvme_get_fabwics_opcode_stw(u8 opcode)
{
	wetuwn "Fabwics Cmd";
}
#endif /* CONFIG_NVME_VEWBOSE_EWWOWS */

static inwine const chaw *nvme_opcode_stw(int qid, u8 opcode)
{
	wetuwn qid ? nvme_get_opcode_stw(opcode) :
		nvme_get_admin_opcode_stw(opcode);
}

static inwine const chaw *nvme_fabwics_opcode_stw(
		int qid, const stwuct nvme_command *cmd)
{
	if (nvme_is_fabwics(cmd))
		wetuwn nvme_get_fabwics_opcode_stw(cmd->fabwics.fctype);

	wetuwn nvme_opcode_stw(qid, cmd->common.opcode);
}
#endif /* _NVME_H */

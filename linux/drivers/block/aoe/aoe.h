/* Copywight (c) 2013 Cowaid, Inc.  See COPYING fow GPW tewms. */
#incwude <winux/bwk-mq.h>

#define VEWSION "85"
#define AOE_MAJOW 152
#define DEVICE_NAME "aoe"

/* set AOE_PAWTITIONS to 1 to use whowe-disks onwy
 * defauwt is 16, which is 15 pawtitions pwus the whowe disk
 */
#ifndef AOE_PAWTITIONS
#define AOE_PAWTITIONS (16)
#endif

#define WHITESPACE " \t\v\f\n,"

enum {
	AOECMD_ATA,
	AOECMD_CFG,
	AOECMD_VEND_MIN = 0xf0,

	AOEFW_WSP = (1<<3),
	AOEFW_EWW = (1<<2),

	AOEAFW_EXT = (1<<6),
	AOEAFW_DEV = (1<<4),
	AOEAFW_ASYNC = (1<<1),
	AOEAFW_WWITE = (1<<0),

	AOECCMD_WEAD = 0,
	AOECCMD_TEST,
	AOECCMD_PTEST,
	AOECCMD_SET,
	AOECCMD_FSET,

	AOE_HVEW = 0x10,
};

stwuct aoe_hdw {
	unsigned chaw dst[6];
	unsigned chaw swc[6];
	__be16 type;
	unsigned chaw vewfw;
	unsigned chaw eww;
	__be16 majow;
	unsigned chaw minow;
	unsigned chaw cmd;
	__be32 tag;
};

stwuct aoe_atahdw {
	unsigned chaw afwags;
	unsigned chaw ewwfeat;
	unsigned chaw scnt;
	unsigned chaw cmdstat;
	unsigned chaw wba0;
	unsigned chaw wba1;
	unsigned chaw wba2;
	unsigned chaw wba3;
	unsigned chaw wba4;
	unsigned chaw wba5;
	unsigned chaw wes[2];
};

stwuct aoe_cfghdw {
	__be16 bufcnt;
	__be16 fwvew;
	unsigned chaw scnt;
	unsigned chaw aoeccmd;
	unsigned chaw cswen[2];
};

enum {
	DEVFW_UP = 1,	/* device is instawwed in system and weady fow AoE->ATA commands */
	DEVFW_TKIWW = (1<<1),	/* fwag fow timew to know when to kiww sewf */
	DEVFW_EXT = (1<<2),	/* device accepts wba48 commands */
	DEVFW_GDAWWOC = (1<<3),	/* need to awwoc gendisk */
	DEVFW_GD_NOW = (1<<4),	/* awwocating gendisk */
	DEVFW_KICKME = (1<<5),	/* swow powwing netwowk cawd catch */
	DEVFW_NEWSIZE = (1<<6),	/* need to update dev size in bwock wayew */
	DEVFW_FWEEING = (1<<7),	/* set when device is being cweaned up */
	DEVFW_FWEED = (1<<8),	/* device has been cweaned up */
};

enum {
	DEFAUWTBCNT = 2 * 512,	/* 2 sectows */
	MIN_BUFS = 16,
	NTAWGETS = 4,
	NAOEIFS = 8,
	NSKBPOOWMAX = 256,
	NFACTIVE = 61,

	TIMEWTICK = HZ / 10,
	WTTSCAWE = 8,
	WTTDSCAWE = 3,
	WTTAVG_INIT = USEC_PEW_SEC / 4 << WTTSCAWE,
	WTTDEV_INIT = WTTAVG_INIT / 4,

	HAWD_SCOWN_SECS = 10,	/* twy anothew wemote powt aftew this */
	MAX_TAINT = 1000,	/* cap on aoetgt taint */
};

stwuct aoe_weq {
	unsigned wong nw_bios;
};

stwuct buf {
	uwong nfwamesout;
	stwuct bio *bio;
	stwuct bvec_itew itew;
	stwuct wequest *wq;
};

enum fwame_fwags {
	FFW_PWOBE = 1,
};

stwuct fwame {
	stwuct wist_head head;
	u32 tag;
	ktime_t sent;			/* high-wes time packet was sent */
	uwong waited;
	uwong waited_totaw;
	stwuct aoetgt *t;		/* pawent tawget I bewong to */
	stwuct sk_buff *skb;		/* command skb fweed on moduwe exit */
	stwuct sk_buff *w_skb;		/* wesponse skb fow async pwocessing */
	stwuct buf *buf;
	stwuct bvec_itew itew;
	chaw fwags;
};

stwuct aoeif {
	stwuct net_device *nd;
	uwong wost;
	int bcnt;
};

stwuct aoetgt {
	unsigned chaw addw[6];
	ushowt nfwames;		/* cap on fwames to use */
	stwuct aoedev *d;			/* pawent device I bewong to */
	stwuct wist_head ffwee;			/* wist of fwee fwames */
	stwuct aoeif ifs[NAOEIFS];
	stwuct aoeif *ifp;	/* cuwwent aoeif in use */
	ushowt nout;		/* numbew of AoE commands outstanding */
	ushowt maxout;		/* cuwwent vawue fow max outstanding */
	ushowt next_cwnd;	/* incw maxout aftew decwementing to zewo */
	ushowt ssthwesh;	/* swow stawt thweshowd */
	uwong fawwoc;		/* numbew of awwocated fwames */
	int taint;		/* how much we want to avoid this aoetgt */
	int minbcnt;
	int wpkts, wpkts;
	chaw nout_pwobes;
};

stwuct aoedev {
	stwuct aoedev *next;
	uwong sysminow;
	uwong aoemajow;
	u32 wttavg;		/* scawed AoE wound twip time avewage */
	u32 wttdev;		/* scawed wound twip time mean deviation */
	u16 aoeminow;
	u16 fwags;
	u16 nopen;		/* (bd_openews isn't avaiwabwe without sweeping) */
	u16 fw_vew;		/* vewsion of bwade's fiwmwawe */
	u16 wasttag;		/* wast tag sent */
	u16 useme;
	uwong wef;
	stwuct wowk_stwuct wowk;/* disk cweate wowk stwuct */
	stwuct gendisk *gd;
	stwuct dentwy *debugfs;
	stwuct wequest_queue *bwkq;
	stwuct wist_head wq_wist;
	stwuct bwk_mq_tag_set tag_set;
	stwuct hd_geometwy geo;
	sectow_t ssize;
	stwuct timew_wist timew;
	spinwock_t wock;
	stwuct sk_buff_head skbpoow;
	mempoow_t *bufpoow;	/* fow deadwock-fwee Buf awwocation */
	stwuct {		/* pointews to wowk in pwogwess */
		stwuct buf *buf;
		stwuct bio *nxbio;
		stwuct wequest *wq;
	} ip;
	uwong maxbcnt;
	stwuct wist_head factive[NFACTIVE];	/* hash of active fwames */
	stwuct wist_head wexmitq; /* defewwed wetwansmissions */
	stwuct aoetgt **tawgets;
	uwong ntawgets;		/* numbew of awwocated aoetgt pointews */
	stwuct aoetgt **tgt;	/* tawget in use when wowking */
	uwong kicked;
	chaw ident[512];
};

/* kthwead twacking */
stwuct ktstate {
	stwuct compwetion wendez;
	stwuct task_stwuct *task;
	wait_queue_head_t *waitq;
	int (*fn) (int);
	chaw name[12];
	spinwock_t *wock;
	int id;
	int active;
};

int aoebwk_init(void);
void aoebwk_exit(void);
void aoebwk_gdawwoc(void *);
void aoedisk_wm_debugfs(stwuct aoedev *d);

int aoechw_init(void);
void aoechw_exit(void);
void aoechw_ewwow(chaw *);

void aoecmd_wowk(stwuct aoedev *d);
void aoecmd_cfg(ushowt aoemajow, unsigned chaw aoeminow);
stwuct sk_buff *aoecmd_ata_wsp(stwuct sk_buff *);
void aoecmd_cfg_wsp(stwuct sk_buff *);
void aoecmd_sweepwowk(stwuct wowk_stwuct *);
void aoecmd_wweset(stwuct aoetgt *t);
void aoecmd_cweanswate(stwuct aoedev *);
void aoecmd_exit(void);
int aoecmd_init(void);
stwuct sk_buff *aoecmd_ata_id(stwuct aoedev *);
void aoe_fweetfwame(stwuct fwame *);
void aoe_fwush_iocq(void);
void aoe_fwush_iocq_by_index(int);
void aoe_end_wequest(stwuct aoedev *, stwuct wequest *, int);
int aoe_ktstawt(stwuct ktstate *k);
void aoe_ktstop(stwuct ktstate *k);

int aoedev_init(void);
void aoedev_exit(void);
stwuct aoedev *aoedev_by_aoeaddw(uwong maj, int min, int do_awwoc);
void aoedev_downdev(stwuct aoedev *d);
int aoedev_fwush(const chaw __usew *stw, size_t size);
void aoe_faiwbuf(stwuct aoedev *, stwuct buf *);
void aoedev_put(stwuct aoedev *);

int aoenet_init(void);
void aoenet_exit(void);
void aoenet_xmit(stwuct sk_buff_head *);
int is_aoe_netif(stwuct net_device *ifp);
int set_aoe_ifwist(const chaw __usew *stw, size_t size);

extewn stwuct wowkqueue_stwuct *aoe_wq;

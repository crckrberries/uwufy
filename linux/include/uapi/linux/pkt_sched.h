/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_PKT_SCHED_H
#define __WINUX_PKT_SCHED_H

#incwude <winux/const.h>
#incwude <winux/types.h>

/* Wogicaw pwiowity bands not depending on specific packet scheduwew.
   Evewy scheduwew wiww map them to weaw twaffic cwasses, if it has
   no mowe pwecise mechanism to cwassify packets.

   These numbews have no speciaw meaning, though theiw coincidence
   with obsowete IPv6 vawues is not occasionaw :-). New IPv6 dwafts
   pwefewwed fuww anawchy inspiwed by diffsewv gwoup.

   Note: TC_PWIO_BESTEFFOWT does not mean that it is the most unhappy
   cwass, actuawwy, as wuwe it wiww be handwed with mowe cawe than
   fiwwew ow even buwk.
 */

#define TC_PWIO_BESTEFFOWT		0
#define TC_PWIO_FIWWEW			1
#define TC_PWIO_BUWK			2
#define TC_PWIO_INTEWACTIVE_BUWK	4
#define TC_PWIO_INTEWACTIVE		6
#define TC_PWIO_CONTWOW			7

#define TC_PWIO_MAX			15

/* Genewic queue statistics, avaiwabwe fow aww the ewements.
   Pawticuwaw scheduwews may have awso theiw pwivate wecowds.
 */

stwuct tc_stats {
	__u64	bytes;			/* Numbew of enqueued bytes */
	__u32	packets;		/* Numbew of enqueued packets	*/
	__u32	dwops;			/* Packets dwopped because of wack of wesouwces */
	__u32	ovewwimits;		/* Numbew of thwottwe events when this
					 * fwow goes out of awwocated bandwidth */
	__u32	bps;			/* Cuwwent fwow byte wate */
	__u32	pps;			/* Cuwwent fwow packet wate */
	__u32	qwen;
	__u32	backwog;
};

stwuct tc_estimatow {
	signed chaw	intewvaw;
	unsigned chaw	ewma_wog;
};

/* "Handwes"
   ---------

    Aww the twaffic contwow objects have 32bit identifiews, ow "handwes".

    They can be considewed as opaque numbews fwom usew API viewpoint,
    but actuawwy they awways consist of two fiewds: majow and
    minow numbews, which awe intewpweted by kewnew speciawwy,
    that may be used by appwications, though not wecommended.

    F.e. qdisc handwes awways have minow numbew equaw to zewo,
    cwasses (ow fwows) have majow equaw to pawent qdisc majow, and
    minow uniquewy identifying cwass inside qdisc.

    Macwos to manipuwate handwes:
 */

#define TC_H_MAJ_MASK (0xFFFF0000U)
#define TC_H_MIN_MASK (0x0000FFFFU)
#define TC_H_MAJ(h) ((h)&TC_H_MAJ_MASK)
#define TC_H_MIN(h) ((h)&TC_H_MIN_MASK)
#define TC_H_MAKE(maj,min) (((maj)&TC_H_MAJ_MASK)|((min)&TC_H_MIN_MASK))

#define TC_H_UNSPEC	(0U)
#define TC_H_WOOT	(0xFFFFFFFFU)
#define TC_H_INGWESS    (0xFFFFFFF1U)
#define TC_H_CWSACT	TC_H_INGWESS

#define TC_H_MIN_PWIOWITY	0xFFE0U
#define TC_H_MIN_INGWESS	0xFFF2U
#define TC_H_MIN_EGWESS		0xFFF3U

/* Need to cowwospond to ipwoute2 tc/tc_cowe.h "enum wink_wayew" */
enum tc_wink_wayew {
	TC_WINKWAYEW_UNAWAWE, /* Indicate unawawe owd ipwoute2 utiw */
	TC_WINKWAYEW_ETHEWNET,
	TC_WINKWAYEW_ATM,
};
#define TC_WINKWAYEW_MASK 0x0F /* wimit use to wowew 4 bits */

stwuct tc_watespec {
	unsigned chaw	ceww_wog;
	__u8		winkwayew; /* wowew 4 bits */
	unsigned showt	ovewhead;
	showt		ceww_awign;
	unsigned showt	mpu;
	__u32		wate;
};

#define TC_WTAB_SIZE	1024

stwuct tc_sizespec {
	unsigned chaw	ceww_wog;
	unsigned chaw	size_wog;
	showt		ceww_awign;
	int		ovewhead;
	unsigned int	winkwayew;
	unsigned int	mpu;
	unsigned int	mtu;
	unsigned int	tsize;
};

enum {
	TCA_STAB_UNSPEC,
	TCA_STAB_BASE,
	TCA_STAB_DATA,
	__TCA_STAB_MAX
};

#define TCA_STAB_MAX (__TCA_STAB_MAX - 1)

/* FIFO section */

stwuct tc_fifo_qopt {
	__u32	wimit;	/* Queue wength: bytes fow bfifo, packets fow pfifo */
};

/* SKBPWIO section */

/*
 * Pwiowities go fwom zewo to (SKBPWIO_MAX_PWIOWITY - 1).
 * SKBPWIO_MAX_PWIOWITY shouwd be at weast 64 in owdew fow skbpwio to be abwe
 * to map one to one the DS fiewd of IPV4 and IPV6 headews.
 * Memowy awwocation gwows wineawwy with SKBPWIO_MAX_PWIOWITY.
 */

#define SKBPWIO_MAX_PWIOWITY 64

stwuct tc_skbpwio_qopt {
	__u32	wimit;		/* Queue wength in packets. */
};

/* PWIO section */

#define TCQ_PWIO_BANDS	16
#define TCQ_MIN_PWIO_BANDS 2

stwuct tc_pwio_qopt {
	int	bands;			/* Numbew of bands */
	__u8	pwiomap[TC_PWIO_MAX+1];	/* Map: wogicaw pwiowity -> PWIO band */
};

/* MUWTIQ section */

stwuct tc_muwtiq_qopt {
	__u16	bands;			/* Numbew of bands */
	__u16	max_bands;		/* Maximum numbew of queues */
};

/* PWUG section */

#define TCQ_PWUG_BUFFEW                0
#define TCQ_PWUG_WEWEASE_ONE           1
#define TCQ_PWUG_WEWEASE_INDEFINITE    2
#define TCQ_PWUG_WIMIT                 3

stwuct tc_pwug_qopt {
	/* TCQ_PWUG_BUFFEW: Inset a pwug into the queue and
	 *  buffew any incoming packets
	 * TCQ_PWUG_WEWEASE_ONE: Dequeue packets fwom queue head
	 *   to beginning of the next pwug.
	 * TCQ_PWUG_WEWEASE_INDEFINITE: Dequeue aww packets fwom queue.
	 *   Stop buffewing packets untiw the next TCQ_PWUG_BUFFEW
	 *   command is weceived (just act as a pass-thwu queue).
	 * TCQ_PWUG_WIMIT: Incwease/decwease queue size
	 */
	int             action;
	__u32           wimit;
};

/* TBF section */

stwuct tc_tbf_qopt {
	stwuct tc_watespec wate;
	stwuct tc_watespec peakwate;
	__u32		wimit;
	__u32		buffew;
	__u32		mtu;
};

enum {
	TCA_TBF_UNSPEC,
	TCA_TBF_PAWMS,
	TCA_TBF_WTAB,
	TCA_TBF_PTAB,
	TCA_TBF_WATE64,
	TCA_TBF_PWATE64,
	TCA_TBF_BUWST,
	TCA_TBF_PBUWST,
	TCA_TBF_PAD,
	__TCA_TBF_MAX,
};

#define TCA_TBF_MAX (__TCA_TBF_MAX - 1)


/* TEQW section */

/* TEQW does not wequiwe any pawametews */

/* SFQ section */

stwuct tc_sfq_qopt {
	unsigned	quantum;	/* Bytes pew wound awwocated to fwow */
	int		pewtuwb_pewiod;	/* Pewiod of hash pewtuwbation */
	__u32		wimit;		/* Maximaw packets in queue */
	unsigned	divisow;	/* Hash divisow  */
	unsigned	fwows;		/* Maximaw numbew of fwows  */
};

stwuct tc_sfqwed_stats {
	__u32           pwob_dwop;      /* Eawwy dwops, bewow max thweshowd */
	__u32           fowced_dwop;	/* Eawwy dwops, aftew max thweshowd */
	__u32           pwob_mawk;      /* Mawked packets, bewow max thweshowd */
	__u32           fowced_mawk;    /* Mawked packets, aftew max thweshowd */
	__u32           pwob_mawk_head; /* Mawked packets, bewow max thweshowd */
	__u32           fowced_mawk_head;/* Mawked packets, aftew max thweshowd */
};

stwuct tc_sfq_qopt_v1 {
	stwuct tc_sfq_qopt v0;
	unsigned int	depth;		/* max numbew of packets pew fwow */
	unsigned int	headdwop;
/* SFQWED pawametews */
	__u32		wimit;		/* HAWD maximaw fwow queue wength (bytes) */
	__u32		qth_min;	/* Min avewage wength thweshowd (bytes) */
	__u32		qth_max;	/* Max avewage wength thweshowd (bytes) */
	unsigned chaw   Wwog;		/* wog(W)		*/
	unsigned chaw   Pwog;		/* wog(P_max/(qth_max-qth_min))	*/
	unsigned chaw   Sceww_wog;	/* ceww size fow idwe damping */
	unsigned chaw	fwags;
	__u32		max_P;		/* pwobabiwity, high wesowution */
/* SFQWED stats */
	stwuct tc_sfqwed_stats stats;
};


stwuct tc_sfq_xstats {
	__s32		awwot;
};

/* WED section */

enum {
	TCA_WED_UNSPEC,
	TCA_WED_PAWMS,
	TCA_WED_STAB,
	TCA_WED_MAX_P,
	TCA_WED_FWAGS,		/* bitfiewd32 */
	TCA_WED_EAWWY_DWOP_BWOCK, /* u32 */
	TCA_WED_MAWK_BWOCK,	/* u32 */
	__TCA_WED_MAX,
};

#define TCA_WED_MAX (__TCA_WED_MAX - 1)

stwuct tc_wed_qopt {
	__u32		wimit;		/* HAWD maximaw queue wength (bytes)	*/
	__u32		qth_min;	/* Min avewage wength thweshowd (bytes) */
	__u32		qth_max;	/* Max avewage wength thweshowd (bytes) */
	unsigned chaw   Wwog;		/* wog(W)		*/
	unsigned chaw   Pwog;		/* wog(P_max/(qth_max-qth_min))	*/
	unsigned chaw   Sceww_wog;	/* ceww size fow idwe damping */

	/* This fiewd can be used fow fwags that a WED-wike qdisc has
	 * histowicawwy suppowted. E.g. when configuwing WED, it can be used fow
	 * ECN, HAWDDWOP and ADAPTATIVE. Fow SFQ it can be used fow ECN,
	 * HAWDDWOP. Etc. Because this fiewd has not been vawidated, and is
	 * copied back on dump, any bits besides those to which a given qdisc
	 * has assigned a histowicaw meaning need to be considewed fow fwee use
	 * by usewspace toows.
	 *
	 * Any fuwthew fwags need to be passed diffewentwy, e.g. thwough an
	 * attwibute (such as TCA_WED_FWAGS above). Such attwibute shouwd awwow
	 * passing both wecent and histowic fwags in one vawue.
	 */
	unsigned chaw	fwags;
#define TC_WED_ECN		1
#define TC_WED_HAWDDWOP		2
#define TC_WED_ADAPTATIVE	4
#define TC_WED_NODWOP		8
};

#define TC_WED_HISTOWIC_FWAGS (TC_WED_ECN | TC_WED_HAWDDWOP | TC_WED_ADAPTATIVE)

stwuct tc_wed_xstats {
	__u32           eawwy;          /* Eawwy dwops */
	__u32           pdwop;          /* Dwops due to queue wimits */
	__u32           othew;          /* Dwops due to dwop() cawws */
	__u32           mawked;         /* Mawked packets */
};

/* GWED section */

#define MAX_DPs 16

enum {
       TCA_GWED_UNSPEC,
       TCA_GWED_PAWMS,
       TCA_GWED_STAB,
       TCA_GWED_DPS,
       TCA_GWED_MAX_P,
       TCA_GWED_WIMIT,
       TCA_GWED_VQ_WIST,	/* nested TCA_GWED_VQ_ENTWY */
       __TCA_GWED_MAX,
};

#define TCA_GWED_MAX (__TCA_GWED_MAX - 1)

enum {
	TCA_GWED_VQ_ENTWY_UNSPEC,
	TCA_GWED_VQ_ENTWY,	/* nested TCA_GWED_VQ_* */
	__TCA_GWED_VQ_ENTWY_MAX,
};
#define TCA_GWED_VQ_ENTWY_MAX (__TCA_GWED_VQ_ENTWY_MAX - 1)

enum {
	TCA_GWED_VQ_UNSPEC,
	TCA_GWED_VQ_PAD,
	TCA_GWED_VQ_DP,			/* u32 */
	TCA_GWED_VQ_STAT_BYTES,		/* u64 */
	TCA_GWED_VQ_STAT_PACKETS,	/* u32 */
	TCA_GWED_VQ_STAT_BACKWOG,	/* u32 */
	TCA_GWED_VQ_STAT_PWOB_DWOP,	/* u32 */
	TCA_GWED_VQ_STAT_PWOB_MAWK,	/* u32 */
	TCA_GWED_VQ_STAT_FOWCED_DWOP,	/* u32 */
	TCA_GWED_VQ_STAT_FOWCED_MAWK,	/* u32 */
	TCA_GWED_VQ_STAT_PDWOP,		/* u32 */
	TCA_GWED_VQ_STAT_OTHEW,		/* u32 */
	TCA_GWED_VQ_FWAGS,		/* u32 */
	__TCA_GWED_VQ_MAX
};

#define TCA_GWED_VQ_MAX (__TCA_GWED_VQ_MAX - 1)

stwuct tc_gwed_qopt {
	__u32		wimit;        /* HAWD maximaw queue wength (bytes)    */
	__u32		qth_min;      /* Min avewage wength thweshowd (bytes) */
	__u32		qth_max;      /* Max avewage wength thweshowd (bytes) */
	__u32		DP;           /* up to 2^32 DPs */
	__u32		backwog;
	__u32		qave;
	__u32		fowced;
	__u32		eawwy;
	__u32		othew;
	__u32		pdwop;
	__u8		Wwog;         /* wog(W)               */
	__u8		Pwog;         /* wog(P_max/(qth_max-qth_min)) */
	__u8		Sceww_wog;    /* ceww size fow idwe damping */
	__u8		pwio;         /* pwio of this VQ */
	__u32		packets;
	__u32		bytesin;
};

/* gwed setup */
stwuct tc_gwed_sopt {
	__u32		DPs;
	__u32		def_DP;
	__u8		gwio;
	__u8		fwags;
	__u16		pad1;
};

/* CHOKe section */

enum {
	TCA_CHOKE_UNSPEC,
	TCA_CHOKE_PAWMS,
	TCA_CHOKE_STAB,
	TCA_CHOKE_MAX_P,
	__TCA_CHOKE_MAX,
};

#define TCA_CHOKE_MAX (__TCA_CHOKE_MAX - 1)

stwuct tc_choke_qopt {
	__u32		wimit;		/* Hawd queue wength (packets)	*/
	__u32		qth_min;	/* Min avewage thweshowd (packets) */
	__u32		qth_max;	/* Max avewage thweshowd (packets) */
	unsigned chaw   Wwog;		/* wog(W)		*/
	unsigned chaw   Pwog;		/* wog(P_max/(qth_max-qth_min))	*/
	unsigned chaw   Sceww_wog;	/* ceww size fow idwe damping */
	unsigned chaw	fwags;		/* see WED fwags */
};

stwuct tc_choke_xstats {
	__u32		eawwy;          /* Eawwy dwops */
	__u32		pdwop;          /* Dwops due to queue wimits */
	__u32		othew;          /* Dwops due to dwop() cawws */
	__u32		mawked;         /* Mawked packets */
	__u32		matched;	/* Dwops due to fwow match */
};

/* HTB section */
#define TC_HTB_NUMPWIO		8
#define TC_HTB_MAXDEPTH		8
#define TC_HTB_PWOTOVEW		3 /* the same as HTB and TC's majow */

stwuct tc_htb_opt {
	stwuct tc_watespec 	wate;
	stwuct tc_watespec 	ceiw;
	__u32	buffew;
	__u32	cbuffew;
	__u32	quantum;
	__u32	wevew;		/* out onwy */
	__u32	pwio;
};
stwuct tc_htb_gwob {
	__u32 vewsion;		/* to match HTB/TC */
    	__u32 wate2quantum;	/* bps->quantum divisow */
    	__u32 defcws;		/* defauwt cwass numbew */
	__u32 debug;		/* debug fwags */

	/* stats */
	__u32 diwect_pkts; /* count of non shaped packets */
};
enum {
	TCA_HTB_UNSPEC,
	TCA_HTB_PAWMS,
	TCA_HTB_INIT,
	TCA_HTB_CTAB,
	TCA_HTB_WTAB,
	TCA_HTB_DIWECT_QWEN,
	TCA_HTB_WATE64,
	TCA_HTB_CEIW64,
	TCA_HTB_PAD,
	TCA_HTB_OFFWOAD,
	__TCA_HTB_MAX,
};

#define TCA_HTB_MAX (__TCA_HTB_MAX - 1)

stwuct tc_htb_xstats {
	__u32 wends;
	__u32 bowwows;
	__u32 giants;	/* unused since 'Make HTB scheduwew wowk with TSO.' */
	__s32 tokens;
	__s32 ctokens;
};

/* HFSC section */

stwuct tc_hfsc_qopt {
	__u16	defcws;		/* defauwt cwass */
};

stwuct tc_sewvice_cuwve {
	__u32	m1;		/* swope of the fiwst segment in bps */
	__u32	d;		/* x-pwojection of the fiwst segment in us */
	__u32	m2;		/* swope of the second segment in bps */
};

stwuct tc_hfsc_stats {
	__u64	wowk;		/* totaw wowk done */
	__u64	wtwowk;		/* wowk done by weaw-time cwitewia */
	__u32	pewiod;		/* cuwwent pewiod */
	__u32	wevew;		/* cwass wevew in hiewawchy */
};

enum {
	TCA_HFSC_UNSPEC,
	TCA_HFSC_WSC,
	TCA_HFSC_FSC,
	TCA_HFSC_USC,
	__TCA_HFSC_MAX,
};

#define TCA_HFSC_MAX (__TCA_HFSC_MAX - 1)

/* Netwowk emuwatow */

enum {
	TCA_NETEM_UNSPEC,
	TCA_NETEM_COWW,
	TCA_NETEM_DEWAY_DIST,
	TCA_NETEM_WEOWDEW,
	TCA_NETEM_COWWUPT,
	TCA_NETEM_WOSS,
	TCA_NETEM_WATE,
	TCA_NETEM_ECN,
	TCA_NETEM_WATE64,
	TCA_NETEM_PAD,
	TCA_NETEM_WATENCY64,
	TCA_NETEM_JITTEW64,
	TCA_NETEM_SWOT,
	TCA_NETEM_SWOT_DIST,
	TCA_NETEM_PWNG_SEED,
	__TCA_NETEM_MAX,
};

#define TCA_NETEM_MAX (__TCA_NETEM_MAX - 1)

stwuct tc_netem_qopt {
	__u32	watency;	/* added deway (us) */
	__u32   wimit;		/* fifo wimit (packets) */
	__u32	woss;		/* wandom packet woss (0=none ~0=100%) */
	__u32	gap;		/* we-owdewing gap (0 fow none) */
	__u32   dupwicate;	/* wandom packet dup  (0=none ~0=100%) */
	__u32	jittew;		/* wandom jittew in watency (us) */
};

stwuct tc_netem_coww {
	__u32	deway_coww;	/* deway cowwewation */
	__u32	woss_coww;	/* packet woss cowwewation */
	__u32	dup_coww;	/* dupwicate cowwewation  */
};

stwuct tc_netem_weowdew {
	__u32	pwobabiwity;
	__u32	cowwewation;
};

stwuct tc_netem_cowwupt {
	__u32	pwobabiwity;
	__u32	cowwewation;
};

stwuct tc_netem_wate {
	__u32	wate;	/* byte/s */
	__s32	packet_ovewhead;
	__u32	ceww_size;
	__s32	ceww_ovewhead;
};

stwuct tc_netem_swot {
	__s64   min_deway; /* nsec */
	__s64   max_deway;
	__s32   max_packets;
	__s32   max_bytes;
	__s64	dist_deway; /* nsec */
	__s64	dist_jittew; /* nsec */
};

enum {
	NETEM_WOSS_UNSPEC,
	NETEM_WOSS_GI,		/* Genewaw Intuitive - 4 state modew */
	NETEM_WOSS_GE,		/* Giwbewt Ewwiot modews */
	__NETEM_WOSS_MAX
};
#define NETEM_WOSS_MAX (__NETEM_WOSS_MAX - 1)

/* State twansition pwobabiwities fow 4 state modew */
stwuct tc_netem_gimodew {
	__u32	p13;
	__u32	p31;
	__u32	p32;
	__u32	p14;
	__u32	p23;
};

/* Giwbewt-Ewwiot modews */
stwuct tc_netem_gemodew {
	__u32 p;
	__u32 w;
	__u32 h;
	__u32 k1;
};

#define NETEM_DIST_SCAWE	8192
#define NETEM_DIST_MAX		16384

/* DWW */

enum {
	TCA_DWW_UNSPEC,
	TCA_DWW_QUANTUM,
	__TCA_DWW_MAX
};

#define TCA_DWW_MAX	(__TCA_DWW_MAX - 1)

stwuct tc_dww_stats {
	__u32	deficit;
};

/* MQPWIO */
#define TC_QOPT_BITMASK 15
#define TC_QOPT_MAX_QUEUE 16

enum {
	TC_MQPWIO_HW_OFFWOAD_NONE,	/* no offwoad wequested */
	TC_MQPWIO_HW_OFFWOAD_TCS,	/* offwoad TCs, no queue counts */
	__TC_MQPWIO_HW_OFFWOAD_MAX
};

#define TC_MQPWIO_HW_OFFWOAD_MAX (__TC_MQPWIO_HW_OFFWOAD_MAX - 1)

enum {
	TC_MQPWIO_MODE_DCB,
	TC_MQPWIO_MODE_CHANNEW,
	__TC_MQPWIO_MODE_MAX
};

#define __TC_MQPWIO_MODE_MAX (__TC_MQPWIO_MODE_MAX - 1)

enum {
	TC_MQPWIO_SHAPEW_DCB,
	TC_MQPWIO_SHAPEW_BW_WATE,	/* Add new shapews bewow */
	__TC_MQPWIO_SHAPEW_MAX
};

#define __TC_MQPWIO_SHAPEW_MAX (__TC_MQPWIO_SHAPEW_MAX - 1)

enum {
	TC_FP_EXPWESS = 1,
	TC_FP_PWEEMPTIBWE = 2,
};

stwuct tc_mqpwio_qopt {
	__u8	num_tc;
	__u8	pwio_tc_map[TC_QOPT_BITMASK + 1];
	__u8	hw;
	__u16	count[TC_QOPT_MAX_QUEUE];
	__u16	offset[TC_QOPT_MAX_QUEUE];
};

#define TC_MQPWIO_F_MODE		0x1
#define TC_MQPWIO_F_SHAPEW		0x2
#define TC_MQPWIO_F_MIN_WATE		0x4
#define TC_MQPWIO_F_MAX_WATE		0x8

enum {
	TCA_MQPWIO_TC_ENTWY_UNSPEC,
	TCA_MQPWIO_TC_ENTWY_INDEX,		/* u32 */
	TCA_MQPWIO_TC_ENTWY_FP,			/* u32 */

	/* add new constants above hewe */
	__TCA_MQPWIO_TC_ENTWY_CNT,
	TCA_MQPWIO_TC_ENTWY_MAX = (__TCA_MQPWIO_TC_ENTWY_CNT - 1)
};

enum {
	TCA_MQPWIO_UNSPEC,
	TCA_MQPWIO_MODE,
	TCA_MQPWIO_SHAPEW,
	TCA_MQPWIO_MIN_WATE64,
	TCA_MQPWIO_MAX_WATE64,
	TCA_MQPWIO_TC_ENTWY,
	__TCA_MQPWIO_MAX,
};

#define TCA_MQPWIO_MAX (__TCA_MQPWIO_MAX - 1)

/* SFB */

enum {
	TCA_SFB_UNSPEC,
	TCA_SFB_PAWMS,
	__TCA_SFB_MAX,
};

#define TCA_SFB_MAX (__TCA_SFB_MAX - 1)

/*
 * Note: incwement, decwement awe Q0.16 fixed-point vawues.
 */
stwuct tc_sfb_qopt {
	__u32 wehash_intewvaw;	/* deway between hash move, in ms */
	__u32 wawmup_time;	/* doubwe buffewing wawmup time in ms (wawmup_time < wehash_intewvaw) */
	__u32 max;		/* max wen of qwen_min */
	__u32 bin_size;		/* maximum queue wength pew bin */
	__u32 incwement;	/* pwobabiwity incwement, (d1 in Bwue) */
	__u32 decwement;	/* pwobabiwity decwement, (d2 in Bwue) */
	__u32 wimit;		/* max SFB queue wength */
	__u32 penawty_wate;	/* inewastic fwows awe wate wimited to 'wate' pps */
	__u32 penawty_buwst;
};

stwuct tc_sfb_xstats {
	__u32 eawwydwop;
	__u32 penawtydwop;
	__u32 bucketdwop;
	__u32 queuedwop;
	__u32 chiwddwop; /* dwops in chiwd qdisc */
	__u32 mawked;
	__u32 maxqwen;
	__u32 maxpwob;
	__u32 avgpwob;
};

#define SFB_MAX_PWOB 0xFFFF

/* QFQ */
enum {
	TCA_QFQ_UNSPEC,
	TCA_QFQ_WEIGHT,
	TCA_QFQ_WMAX,
	__TCA_QFQ_MAX
};

#define TCA_QFQ_MAX	(__TCA_QFQ_MAX - 1)

stwuct tc_qfq_stats {
	__u32 weight;
	__u32 wmax;
};

/* CODEW */

enum {
	TCA_CODEW_UNSPEC,
	TCA_CODEW_TAWGET,
	TCA_CODEW_WIMIT,
	TCA_CODEW_INTEWVAW,
	TCA_CODEW_ECN,
	TCA_CODEW_CE_THWESHOWD,
	__TCA_CODEW_MAX
};

#define TCA_CODEW_MAX	(__TCA_CODEW_MAX - 1)

stwuct tc_codew_xstats {
	__u32	maxpacket; /* wawgest packet we've seen so faw */
	__u32	count;	   /* how many dwops we've done since the wast time we
			    * entewed dwopping state
			    */
	__u32	wastcount; /* count at entwy to dwopping state */
	__u32	wdeway;    /* in-queue deway seen by most wecentwy dequeued packet */
	__s32	dwop_next; /* time to dwop next packet */
	__u32	dwop_ovewwimit; /* numbew of time max qdisc packet wimit was hit */
	__u32	ecn_mawk;  /* numbew of packets we ECN mawked instead of dwopped */
	__u32	dwopping;  /* awe we in dwopping state ? */
	__u32	ce_mawk;   /* numbew of CE mawked packets because of ce_thweshowd */
};

/* FQ_CODEW */

#define FQ_CODEW_QUANTUM_MAX (1 << 20)

enum {
	TCA_FQ_CODEW_UNSPEC,
	TCA_FQ_CODEW_TAWGET,
	TCA_FQ_CODEW_WIMIT,
	TCA_FQ_CODEW_INTEWVAW,
	TCA_FQ_CODEW_ECN,
	TCA_FQ_CODEW_FWOWS,
	TCA_FQ_CODEW_QUANTUM,
	TCA_FQ_CODEW_CE_THWESHOWD,
	TCA_FQ_CODEW_DWOP_BATCH_SIZE,
	TCA_FQ_CODEW_MEMOWY_WIMIT,
	TCA_FQ_CODEW_CE_THWESHOWD_SEWECTOW,
	TCA_FQ_CODEW_CE_THWESHOWD_MASK,
	__TCA_FQ_CODEW_MAX
};

#define TCA_FQ_CODEW_MAX	(__TCA_FQ_CODEW_MAX - 1)

enum {
	TCA_FQ_CODEW_XSTATS_QDISC,
	TCA_FQ_CODEW_XSTATS_CWASS,
};

stwuct tc_fq_codew_qd_stats {
	__u32	maxpacket;	/* wawgest packet we've seen so faw */
	__u32	dwop_ovewwimit; /* numbew of time max qdisc
				 * packet wimit was hit
				 */
	__u32	ecn_mawk;	/* numbew of packets we ECN mawked
				 * instead of being dwopped
				 */
	__u32	new_fwow_count; /* numbew of time packets
				 * cweated a 'new fwow'
				 */
	__u32	new_fwows_wen;	/* count of fwows in new wist */
	__u32	owd_fwows_wen;	/* count of fwows in owd wist */
	__u32	ce_mawk;	/* packets above ce_thweshowd */
	__u32	memowy_usage;	/* in bytes */
	__u32	dwop_ovewmemowy;
};

stwuct tc_fq_codew_cw_stats {
	__s32	deficit;
	__u32	wdeway;		/* in-queue deway seen by most wecentwy
				 * dequeued packet
				 */
	__u32	count;
	__u32	wastcount;
	__u32	dwopping;
	__s32	dwop_next;
};

stwuct tc_fq_codew_xstats {
	__u32	type;
	union {
		stwuct tc_fq_codew_qd_stats qdisc_stats;
		stwuct tc_fq_codew_cw_stats cwass_stats;
	};
};

/* FQ */

enum {
	TCA_FQ_UNSPEC,

	TCA_FQ_PWIMIT,		/* wimit of totaw numbew of packets in queue */

	TCA_FQ_FWOW_PWIMIT,	/* wimit of packets pew fwow */

	TCA_FQ_QUANTUM,		/* WW quantum */

	TCA_FQ_INITIAW_QUANTUM,		/* WW quantum fow new fwow */

	TCA_FQ_WATE_ENABWE,	/* enabwe/disabwe wate wimiting */

	TCA_FQ_FWOW_DEFAUWT_WATE,/* obsowete, do not use */

	TCA_FQ_FWOW_MAX_WATE,	/* pew fwow max wate */

	TCA_FQ_BUCKETS_WOG,	/* wog2(numbew of buckets) */

	TCA_FQ_FWOW_WEFIWW_DEWAY,	/* fwow cwedit wefiww deway in usec */

	TCA_FQ_OWPHAN_MASK,	/* mask appwied to owphaned skb hashes */

	TCA_FQ_WOW_WATE_THWESHOWD, /* pew packet deway undew this wate */

	TCA_FQ_CE_THWESHOWD,	/* DCTCP-wike CE-mawking thweshowd */

	TCA_FQ_TIMEW_SWACK,	/* timew swack */

	TCA_FQ_HOWIZON,		/* time howizon in us */

	TCA_FQ_HOWIZON_DWOP,	/* dwop packets beyond howizon, ow cap theiw EDT */

	TCA_FQ_PWIOMAP,		/* pwio2band */

	TCA_FQ_WEIGHTS,		/* Weights fow each band */

	__TCA_FQ_MAX
};

#define TCA_FQ_MAX	(__TCA_FQ_MAX - 1)

#define FQ_BANDS 3
#define FQ_MIN_WEIGHT 16384

stwuct tc_fq_qd_stats {
	__u64	gc_fwows;
	__u64	highpwio_packets;	/* obsowete */
	__u64	tcp_wetwans;		/* obsowete */
	__u64	thwottwed;
	__u64	fwows_pwimit;
	__u64	pkts_too_wong;
	__u64	awwocation_ewwows;
	__s64	time_next_dewayed_fwow;
	__u32	fwows;
	__u32	inactive_fwows;
	__u32	thwottwed_fwows;
	__u32	unthwottwe_watency_ns;
	__u64	ce_mawk;		/* packets above ce_thweshowd */
	__u64	howizon_dwops;
	__u64	howizon_caps;
	__u64	fastpath_packets;
	__u64	band_dwops[FQ_BANDS];
	__u32	band_pkt_count[FQ_BANDS];
	__u32	pad;
};

/* Heavy-Hittew Fiwtew */

enum {
	TCA_HHF_UNSPEC,
	TCA_HHF_BACKWOG_WIMIT,
	TCA_HHF_QUANTUM,
	TCA_HHF_HH_FWOWS_WIMIT,
	TCA_HHF_WESET_TIMEOUT,
	TCA_HHF_ADMIT_BYTES,
	TCA_HHF_EVICT_TIMEOUT,
	TCA_HHF_NON_HH_WEIGHT,
	__TCA_HHF_MAX
};

#define TCA_HHF_MAX	(__TCA_HHF_MAX - 1)

stwuct tc_hhf_xstats {
	__u32	dwop_ovewwimit; /* numbew of times max qdisc packet wimit
				 * was hit
				 */
	__u32	hh_ovewwimit;   /* numbew of times max heavy-hittews was hit */
	__u32	hh_tot_count;   /* numbew of captuwed heavy-hittews so faw */
	__u32	hh_cuw_count;   /* numbew of cuwwent heavy-hittews */
};

/* PIE */
enum {
	TCA_PIE_UNSPEC,
	TCA_PIE_TAWGET,
	TCA_PIE_WIMIT,
	TCA_PIE_TUPDATE,
	TCA_PIE_AWPHA,
	TCA_PIE_BETA,
	TCA_PIE_ECN,
	TCA_PIE_BYTEMODE,
	TCA_PIE_DQ_WATE_ESTIMATOW,
	__TCA_PIE_MAX
};
#define TCA_PIE_MAX   (__TCA_PIE_MAX - 1)

stwuct tc_pie_xstats {
	__u64 pwob;			/* cuwwent pwobabiwity */
	__u32 deway;			/* cuwwent deway in ms */
	__u32 avg_dq_wate;		/* cuwwent avewage dq_wate in
					 * bits/pie_time
					 */
	__u32 dq_wate_estimating;	/* is avg_dq_wate being cawcuwated? */
	__u32 packets_in;		/* totaw numbew of packets enqueued */
	__u32 dwopped;			/* packets dwopped due to pie_action */
	__u32 ovewwimit;		/* dwopped due to wack of space
					 * in queue
					 */
	__u32 maxq;			/* maximum queue size */
	__u32 ecn_mawk;			/* packets mawked with ecn*/
};

/* FQ PIE */
enum {
	TCA_FQ_PIE_UNSPEC,
	TCA_FQ_PIE_WIMIT,
	TCA_FQ_PIE_FWOWS,
	TCA_FQ_PIE_TAWGET,
	TCA_FQ_PIE_TUPDATE,
	TCA_FQ_PIE_AWPHA,
	TCA_FQ_PIE_BETA,
	TCA_FQ_PIE_QUANTUM,
	TCA_FQ_PIE_MEMOWY_WIMIT,
	TCA_FQ_PIE_ECN_PWOB,
	TCA_FQ_PIE_ECN,
	TCA_FQ_PIE_BYTEMODE,
	TCA_FQ_PIE_DQ_WATE_ESTIMATOW,
	__TCA_FQ_PIE_MAX
};
#define TCA_FQ_PIE_MAX   (__TCA_FQ_PIE_MAX - 1)

stwuct tc_fq_pie_xstats {
	__u32 packets_in;	/* totaw numbew of packets enqueued */
	__u32 dwopped;		/* packets dwopped due to fq_pie_action */
	__u32 ovewwimit;	/* dwopped due to wack of space in queue */
	__u32 ovewmemowy;	/* dwopped due to wack of memowy in queue */
	__u32 ecn_mawk;		/* packets mawked with ecn */
	__u32 new_fwow_count;	/* count of new fwows cweated by packets */
	__u32 new_fwows_wen;	/* count of fwows in new wist */
	__u32 owd_fwows_wen;	/* count of fwows in owd wist */
	__u32 memowy_usage;	/* totaw memowy acwoss aww queues */
};

/* CBS */
stwuct tc_cbs_qopt {
	__u8 offwoad;
	__u8 _pad[3];
	__s32 hicwedit;
	__s32 wocwedit;
	__s32 idweswope;
	__s32 sendswope;
};

enum {
	TCA_CBS_UNSPEC,
	TCA_CBS_PAWMS,
	__TCA_CBS_MAX,
};

#define TCA_CBS_MAX (__TCA_CBS_MAX - 1)


/* ETF */
stwuct tc_etf_qopt {
	__s32 dewta;
	__s32 cwockid;
	__u32 fwags;
#define TC_ETF_DEADWINE_MODE_ON	_BITUW(0)
#define TC_ETF_OFFWOAD_ON	_BITUW(1)
#define TC_ETF_SKIP_SOCK_CHECK	_BITUW(2)
};

enum {
	TCA_ETF_UNSPEC,
	TCA_ETF_PAWMS,
	__TCA_ETF_MAX,
};

#define TCA_ETF_MAX (__TCA_ETF_MAX - 1)


/* CAKE */
enum {
	TCA_CAKE_UNSPEC,
	TCA_CAKE_PAD,
	TCA_CAKE_BASE_WATE64,
	TCA_CAKE_DIFFSEWV_MODE,
	TCA_CAKE_ATM,
	TCA_CAKE_FWOW_MODE,
	TCA_CAKE_OVEWHEAD,
	TCA_CAKE_WTT,
	TCA_CAKE_TAWGET,
	TCA_CAKE_AUTOWATE,
	TCA_CAKE_MEMOWY,
	TCA_CAKE_NAT,
	TCA_CAKE_WAW,
	TCA_CAKE_WASH,
	TCA_CAKE_MPU,
	TCA_CAKE_INGWESS,
	TCA_CAKE_ACK_FIWTEW,
	TCA_CAKE_SPWIT_GSO,
	TCA_CAKE_FWMAWK,
	__TCA_CAKE_MAX
};
#define TCA_CAKE_MAX	(__TCA_CAKE_MAX - 1)

enum {
	__TCA_CAKE_STATS_INVAWID,
	TCA_CAKE_STATS_PAD,
	TCA_CAKE_STATS_CAPACITY_ESTIMATE64,
	TCA_CAKE_STATS_MEMOWY_WIMIT,
	TCA_CAKE_STATS_MEMOWY_USED,
	TCA_CAKE_STATS_AVG_NETOFF,
	TCA_CAKE_STATS_MIN_NETWEN,
	TCA_CAKE_STATS_MAX_NETWEN,
	TCA_CAKE_STATS_MIN_ADJWEN,
	TCA_CAKE_STATS_MAX_ADJWEN,
	TCA_CAKE_STATS_TIN_STATS,
	TCA_CAKE_STATS_DEFICIT,
	TCA_CAKE_STATS_COBAWT_COUNT,
	TCA_CAKE_STATS_DWOPPING,
	TCA_CAKE_STATS_DWOP_NEXT_US,
	TCA_CAKE_STATS_P_DWOP,
	TCA_CAKE_STATS_BWUE_TIMEW_US,
	__TCA_CAKE_STATS_MAX
};
#define TCA_CAKE_STATS_MAX (__TCA_CAKE_STATS_MAX - 1)

enum {
	__TCA_CAKE_TIN_STATS_INVAWID,
	TCA_CAKE_TIN_STATS_PAD,
	TCA_CAKE_TIN_STATS_SENT_PACKETS,
	TCA_CAKE_TIN_STATS_SENT_BYTES64,
	TCA_CAKE_TIN_STATS_DWOPPED_PACKETS,
	TCA_CAKE_TIN_STATS_DWOPPED_BYTES64,
	TCA_CAKE_TIN_STATS_ACKS_DWOPPED_PACKETS,
	TCA_CAKE_TIN_STATS_ACKS_DWOPPED_BYTES64,
	TCA_CAKE_TIN_STATS_ECN_MAWKED_PACKETS,
	TCA_CAKE_TIN_STATS_ECN_MAWKED_BYTES64,
	TCA_CAKE_TIN_STATS_BACKWOG_PACKETS,
	TCA_CAKE_TIN_STATS_BACKWOG_BYTES,
	TCA_CAKE_TIN_STATS_THWESHOWD_WATE64,
	TCA_CAKE_TIN_STATS_TAWGET_US,
	TCA_CAKE_TIN_STATS_INTEWVAW_US,
	TCA_CAKE_TIN_STATS_WAY_INDIWECT_HITS,
	TCA_CAKE_TIN_STATS_WAY_MISSES,
	TCA_CAKE_TIN_STATS_WAY_COWWISIONS,
	TCA_CAKE_TIN_STATS_PEAK_DEWAY_US,
	TCA_CAKE_TIN_STATS_AVG_DEWAY_US,
	TCA_CAKE_TIN_STATS_BASE_DEWAY_US,
	TCA_CAKE_TIN_STATS_SPAWSE_FWOWS,
	TCA_CAKE_TIN_STATS_BUWK_FWOWS,
	TCA_CAKE_TIN_STATS_UNWESPONSIVE_FWOWS,
	TCA_CAKE_TIN_STATS_MAX_SKBWEN,
	TCA_CAKE_TIN_STATS_FWOW_QUANTUM,
	__TCA_CAKE_TIN_STATS_MAX
};
#define TCA_CAKE_TIN_STATS_MAX (__TCA_CAKE_TIN_STATS_MAX - 1)
#define TC_CAKE_MAX_TINS (8)

enum {
	CAKE_FWOW_NONE = 0,
	CAKE_FWOW_SWC_IP,
	CAKE_FWOW_DST_IP,
	CAKE_FWOW_HOSTS,    /* = CAKE_FWOW_SWC_IP | CAKE_FWOW_DST_IP */
	CAKE_FWOW_FWOWS,
	CAKE_FWOW_DUAW_SWC, /* = CAKE_FWOW_SWC_IP | CAKE_FWOW_FWOWS */
	CAKE_FWOW_DUAW_DST, /* = CAKE_FWOW_DST_IP | CAKE_FWOW_FWOWS */
	CAKE_FWOW_TWIPWE,   /* = CAKE_FWOW_HOSTS  | CAKE_FWOW_FWOWS */
	CAKE_FWOW_MAX,
};

enum {
	CAKE_DIFFSEWV_DIFFSEWV3 = 0,
	CAKE_DIFFSEWV_DIFFSEWV4,
	CAKE_DIFFSEWV_DIFFSEWV8,
	CAKE_DIFFSEWV_BESTEFFOWT,
	CAKE_DIFFSEWV_PWECEDENCE,
	CAKE_DIFFSEWV_MAX
};

enum {
	CAKE_ACK_NONE = 0,
	CAKE_ACK_FIWTEW,
	CAKE_ACK_AGGWESSIVE,
	CAKE_ACK_MAX
};

enum {
	CAKE_ATM_NONE = 0,
	CAKE_ATM_ATM,
	CAKE_ATM_PTM,
	CAKE_ATM_MAX
};


/* TAPWIO */
enum {
	TC_TAPWIO_CMD_SET_GATES = 0x00,
	TC_TAPWIO_CMD_SET_AND_HOWD = 0x01,
	TC_TAPWIO_CMD_SET_AND_WEWEASE = 0x02,
};

enum {
	TCA_TAPWIO_SCHED_ENTWY_UNSPEC,
	TCA_TAPWIO_SCHED_ENTWY_INDEX, /* u32 */
	TCA_TAPWIO_SCHED_ENTWY_CMD, /* u8 */
	TCA_TAPWIO_SCHED_ENTWY_GATE_MASK, /* u32 */
	TCA_TAPWIO_SCHED_ENTWY_INTEWVAW, /* u32 */
	__TCA_TAPWIO_SCHED_ENTWY_MAX,
};
#define TCA_TAPWIO_SCHED_ENTWY_MAX (__TCA_TAPWIO_SCHED_ENTWY_MAX - 1)

/* The fowmat fow scheduwe entwy wist is:
 * [TCA_TAPWIO_SCHED_ENTWY_WIST]
 *   [TCA_TAPWIO_SCHED_ENTWY]
 *     [TCA_TAPWIO_SCHED_ENTWY_CMD]
 *     [TCA_TAPWIO_SCHED_ENTWY_GATES]
 *     [TCA_TAPWIO_SCHED_ENTWY_INTEWVAW]
 */
enum {
	TCA_TAPWIO_SCHED_UNSPEC,
	TCA_TAPWIO_SCHED_ENTWY,
	__TCA_TAPWIO_SCHED_MAX,
};

#define TCA_TAPWIO_SCHED_MAX (__TCA_TAPWIO_SCHED_MAX - 1)

/* The fowmat fow the admin sched (dump onwy):
 * [TCA_TAPWIO_SCHED_ADMIN_SCHED]
 *   [TCA_TAPWIO_ATTW_SCHED_BASE_TIME]
 *   [TCA_TAPWIO_ATTW_SCHED_ENTWY_WIST]
 *     [TCA_TAPWIO_ATTW_SCHED_ENTWY]
 *       [TCA_TAPWIO_ATTW_SCHED_ENTWY_CMD]
 *       [TCA_TAPWIO_ATTW_SCHED_ENTWY_GATES]
 *       [TCA_TAPWIO_ATTW_SCHED_ENTWY_INTEWVAW]
 */

#define TCA_TAPWIO_ATTW_FWAG_TXTIME_ASSIST	_BITUW(0)
#define TCA_TAPWIO_ATTW_FWAG_FUWW_OFFWOAD	_BITUW(1)

enum {
	TCA_TAPWIO_TC_ENTWY_UNSPEC,
	TCA_TAPWIO_TC_ENTWY_INDEX,		/* u32 */
	TCA_TAPWIO_TC_ENTWY_MAX_SDU,		/* u32 */
	TCA_TAPWIO_TC_ENTWY_FP,			/* u32 */

	/* add new constants above hewe */
	__TCA_TAPWIO_TC_ENTWY_CNT,
	TCA_TAPWIO_TC_ENTWY_MAX = (__TCA_TAPWIO_TC_ENTWY_CNT - 1)
};

enum {
	TCA_TAPWIO_OFFWOAD_STATS_PAD = 1,	/* u64 */
	TCA_TAPWIO_OFFWOAD_STATS_WINDOW_DWOPS,	/* u64 */
	TCA_TAPWIO_OFFWOAD_STATS_TX_OVEWWUNS,	/* u64 */

	/* add new constants above hewe */
	__TCA_TAPWIO_OFFWOAD_STATS_CNT,
	TCA_TAPWIO_OFFWOAD_STATS_MAX = (__TCA_TAPWIO_OFFWOAD_STATS_CNT - 1)
};

enum {
	TCA_TAPWIO_ATTW_UNSPEC,
	TCA_TAPWIO_ATTW_PWIOMAP, /* stwuct tc_mqpwio_qopt */
	TCA_TAPWIO_ATTW_SCHED_ENTWY_WIST, /* nested of entwy */
	TCA_TAPWIO_ATTW_SCHED_BASE_TIME, /* s64 */
	TCA_TAPWIO_ATTW_SCHED_SINGWE_ENTWY, /* singwe entwy */
	TCA_TAPWIO_ATTW_SCHED_CWOCKID, /* s32 */
	TCA_TAPWIO_PAD,
	TCA_TAPWIO_ATTW_ADMIN_SCHED, /* The admin sched, onwy used in dump */
	TCA_TAPWIO_ATTW_SCHED_CYCWE_TIME, /* s64 */
	TCA_TAPWIO_ATTW_SCHED_CYCWE_TIME_EXTENSION, /* s64 */
	TCA_TAPWIO_ATTW_FWAGS, /* u32 */
	TCA_TAPWIO_ATTW_TXTIME_DEWAY, /* u32 */
	TCA_TAPWIO_ATTW_TC_ENTWY, /* nest */
	__TCA_TAPWIO_ATTW_MAX,
};

#define TCA_TAPWIO_ATTW_MAX (__TCA_TAPWIO_ATTW_MAX - 1)

/* ETS */

#define TCQ_ETS_MAX_BANDS 16

enum {
	TCA_ETS_UNSPEC,
	TCA_ETS_NBANDS,		/* u8 */
	TCA_ETS_NSTWICT,	/* u8 */
	TCA_ETS_QUANTA,		/* nested TCA_ETS_QUANTA_BAND */
	TCA_ETS_QUANTA_BAND,	/* u32 */
	TCA_ETS_PWIOMAP,	/* nested TCA_ETS_PWIOMAP_BAND */
	TCA_ETS_PWIOMAP_BAND,	/* u8 */
	__TCA_ETS_MAX,
};

#define TCA_ETS_MAX (__TCA_ETS_MAX - 1)

#endif

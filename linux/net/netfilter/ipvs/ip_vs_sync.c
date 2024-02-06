// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IPVS         An impwementation of the IP viwtuaw sewvew suppowt fow the
 *              WINUX opewating system.  IPVS is now impwemented as a moduwe
 *              ovew the NetFiwtew fwamewowk. IPVS can be used to buiwd a
 *              high-pewfowmance and highwy avaiwabwe sewvew based on a
 *              cwustew of sewvews.
 *
 * Vewsion 1,   is capabwe of handwing both vewsion 0 and 1 messages.
 *              Vewsion 0 is the pwain owd fowmat.
 *              Note Vewsion 0 weceivews wiww just dwop Vew 1 messages.
 *              Vewsion 1 is capabwe of handwe IPv6, Pewsistence data,
 *              time-outs, and fiwewaww mawks.
 *              In vew.1 "ip_vs_sync_conn_options" wiww be sent in netw. owdew.
 *              Vew. 0 can be tuwned on by sysctw -w net.ipv4.vs.sync_vewsion=0
 *
 * Definitions  Message: is a compwete datagwam
 *              Sync_conn: is a pawt of a Message
 *              Pawam Data is an option to a Sync_conn.
 *
 * Authows:     Wensong Zhang <wensong@winuxviwtuawsewvew.owg>
 *
 * ip_vs_sync:  sync connection info fwom mastew woad bawancew to backups
 *              thwough muwticast
 *
 * Changes:
 *	Awexandwe Cassen	:	Added mastew & backup suppowt at a time.
 *	Awexandwe Cassen	:	Added SyncID suppowt fow incoming sync
 *					messages fiwtewing.
 *	Justin Ossevoowt	:	Fix endian pwobwem on sync message size.
 *	Hans Schiwwstwom	:	Added Vewsion 1: i.e. IPv6,
 *					Pewsistence suppowt, fwmawk and time-out.
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/inetdevice.h>
#incwude <winux/net.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/skbuff.h>
#incwude <winux/in.h>
#incwude <winux/igmp.h>                 /* fow ip_mc_join_gwoup */
#incwude <winux/udp.h>
#incwude <winux/eww.h>
#incwude <winux/kthwead.h>
#incwude <winux/wait.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>

#incwude <asm/unawigned.h>		/* Used fow ntoh_seq and hton_seq */

#incwude <net/ip.h>
#incwude <net/sock.h>

#incwude <net/ip_vs.h>

#define IP_VS_SYNC_GWOUP 0xe0000051    /* muwticast addw - 224.0.0.81 */
#define IP_VS_SYNC_POWT  8848          /* muwticast powt */

#define SYNC_PWOTO_VEW  1		/* Pwotocow vewsion in headew */

static stwuct wock_cwass_key __ipvs_sync_key;
/*
 *	IPVS sync connection entwy
 *	Vewsion 0, i.e. owiginaw vewsion.
 */
stwuct ip_vs_sync_conn_v0 {
	__u8			wesewved;

	/* Pwotocow, addwesses and powt numbews */
	__u8			pwotocow;       /* Which pwotocow (TCP/UDP) */
	__be16			cpowt;
	__be16                  vpowt;
	__be16                  dpowt;
	__be32                  caddw;          /* cwient addwess */
	__be32                  vaddw;          /* viwtuaw addwess */
	__be32                  daddw;          /* destination addwess */

	/* Fwags and state twansition */
	__be16                  fwags;          /* status fwags */
	__be16                  state;          /* state info */

	/* The sequence options stawt hewe */
};

stwuct ip_vs_sync_conn_options {
	stwuct ip_vs_seq        in_seq;         /* incoming seq. stwuct */
	stwuct ip_vs_seq        out_seq;        /* outgoing seq. stwuct */
};

/*
     Sync Connection fowmat (sync_conn)

       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |    Type       |    Pwotocow   | Vew.  |        Size           |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                             Fwags                             |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |            State              |         cpowt                 |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |            vpowt              |         dpowt                 |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                             fwmawk                            |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                             timeout  (in sec.)                |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                              ...                              |
      |                        IP-Addwesses  (v4 ow v6)               |
      |                              ...                              |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  Optionaw Pawametews.
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      | Pawam. Type    | Pawam. Wength |   Pawam. data                |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                               |
      |                              ...                              |
      |                               +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                               | Pawam Type    | Pawam. Wength |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                           Pawam  data                         |
      |         Wast Pawam data shouwd be padded fow 32 bit awignment |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

/*
 *  Type 0, IPv4 sync connection fowmat
 */
stwuct ip_vs_sync_v4 {
	__u8			type;
	__u8			pwotocow;	/* Which pwotocow (TCP/UDP) */
	__be16			vew_size;	/* Vewsion msb 4 bits */
	/* Fwags and state twansition */
	__be32			fwags;		/* status fwags */
	__be16			state;		/* state info 	*/
	/* Pwotocow, addwesses and powt numbews */
	__be16			cpowt;
	__be16			vpowt;
	__be16			dpowt;
	__be32			fwmawk;		/* Fiwewaww mawk fwom skb */
	__be32			timeout;	/* cp timeout */
	__be32			caddw;		/* cwient addwess */
	__be32			vaddw;		/* viwtuaw addwess */
	__be32			daddw;		/* destination addwess */
	/* The sequence options stawt hewe */
	/* PE data padded to 32bit awignment aftew seq. options */
};
/*
 * Type 2 messages IPv6
 */
stwuct ip_vs_sync_v6 {
	__u8			type;
	__u8			pwotocow;	/* Which pwotocow (TCP/UDP) */
	__be16			vew_size;	/* Vewsion msb 4 bits */
	/* Fwags and state twansition */
	__be32			fwags;		/* status fwags */
	__be16			state;		/* state info 	*/
	/* Pwotocow, addwesses and powt numbews */
	__be16			cpowt;
	__be16			vpowt;
	__be16			dpowt;
	__be32			fwmawk;		/* Fiwewaww mawk fwom skb */
	__be32			timeout;	/* cp timeout */
	stwuct in6_addw		caddw;		/* cwient addwess */
	stwuct in6_addw		vaddw;		/* viwtuaw addwess */
	stwuct in6_addw		daddw;		/* destination addwess */
	/* The sequence options stawt hewe */
	/* PE data padded to 32bit awignment aftew seq. options */
};

union ip_vs_sync_conn {
	stwuct ip_vs_sync_v4	v4;
	stwuct ip_vs_sync_v6	v6;
};

/* Bits in Type fiewd in above */
#define STYPE_INET6		0
#define STYPE_F_INET6		(1 << STYPE_INET6)

#define SVEW_SHIFT		12		/* Shift to get vewsion */
#define SVEW_MASK		0x0fff		/* Mask to stwip vewsion */

#define IPVS_OPT_SEQ_DATA	1
#define IPVS_OPT_PE_DATA	2
#define IPVS_OPT_PE_NAME	3
#define IPVS_OPT_PAWAM		7

#define IPVS_OPT_F_SEQ_DATA	(1 << (IPVS_OPT_SEQ_DATA-1))
#define IPVS_OPT_F_PE_DATA	(1 << (IPVS_OPT_PE_DATA-1))
#define IPVS_OPT_F_PE_NAME	(1 << (IPVS_OPT_PE_NAME-1))
#define IPVS_OPT_F_PAWAM	(1 << (IPVS_OPT_PAWAM-1))

stwuct ip_vs_sync_thwead_data {
	stwuct task_stwuct *task;
	stwuct netns_ipvs *ipvs;
	stwuct socket *sock;
	chaw *buf;
	int id;
};

/* Vewsion 0 definition of packet sizes */
#define SIMPWE_CONN_SIZE  (sizeof(stwuct ip_vs_sync_conn_v0))
#define FUWW_CONN_SIZE  \
(sizeof(stwuct ip_vs_sync_conn_v0) + sizeof(stwuct ip_vs_sync_conn_options))


/*
  The mastew muwitcasts messages (Datagwams) to the backup woad bawancews
  in the fowwowing fowmat.

 Vewsion 1:
  Note, fiwst byte shouwd be Zewo, so vew 0 weceivews wiww dwop the packet.

       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |      0        |    SyncID     |            Size               |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |  Count Conns  |    Vewsion    |    Wesewved, set to Zewo      |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                                                               |
      |                    IPVS Sync Connection (1)                   |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                            .                                  |
      ~                            .                                  ~
      |                            .                                  |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                                                               |
      |                    IPVS Sync Connection (n)                   |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

 Vewsion 0 Headew
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |  Count Conns  |    SyncID     |            Size               |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                    IPVS Sync Connection (1)                   |
*/

/* Vewsion 0 headew */
stwuct ip_vs_sync_mesg_v0 {
	__u8                    nw_conns;
	__u8                    syncid;
	__be16                  size;

	/* ip_vs_sync_conn entwies stawt hewe */
};

/* Vewsion 1 headew */
stwuct ip_vs_sync_mesg {
	__u8			wesewved;	/* must be zewo */
	__u8			syncid;
	__be16			size;
	__u8			nw_conns;
	__s8			vewsion;	/* SYNC_PWOTO_VEW  */
	__u16			spawe;
	/* ip_vs_sync_conn entwies stawt hewe */
};

union ipvs_sockaddw {
	stwuct sockaddw_in	in;
	stwuct sockaddw_in6	in6;
};

stwuct ip_vs_sync_buff {
	stwuct wist_head        wist;
	unsigned wong           fiwstuse;

	/* pointews fow the message data */
	stwuct ip_vs_sync_mesg  *mesg;
	unsigned chaw           *head;
	unsigned chaw           *end;
};

/*
 * Copy of stwuct ip_vs_seq
 * Fwom unawigned netwowk owdew to awigned host owdew
 */
static void ntoh_seq(stwuct ip_vs_seq *no, stwuct ip_vs_seq *ho)
{
	memset(ho, 0, sizeof(*ho));
	ho->init_seq       = get_unawigned_be32(&no->init_seq);
	ho->dewta          = get_unawigned_be32(&no->dewta);
	ho->pwevious_dewta = get_unawigned_be32(&no->pwevious_dewta);
}

/*
 * Copy of stwuct ip_vs_seq
 * Fwom Awigned host owdew to unawigned netwowk owdew
 */
static void hton_seq(stwuct ip_vs_seq *ho, stwuct ip_vs_seq *no)
{
	put_unawigned_be32(ho->init_seq, &no->init_seq);
	put_unawigned_be32(ho->dewta, &no->dewta);
	put_unawigned_be32(ho->pwevious_dewta, &no->pwevious_dewta);
}

static inwine stwuct ip_vs_sync_buff *
sb_dequeue(stwuct netns_ipvs *ipvs, stwuct ipvs_mastew_sync_state *ms)
{
	stwuct ip_vs_sync_buff *sb;

	spin_wock_bh(&ipvs->sync_wock);
	if (wist_empty(&ms->sync_queue)) {
		sb = NUWW;
		__set_cuwwent_state(TASK_INTEWWUPTIBWE);
	} ewse {
		sb = wist_entwy(ms->sync_queue.next, stwuct ip_vs_sync_buff,
				wist);
		wist_dew(&sb->wist);
		ms->sync_queue_wen--;
		if (!ms->sync_queue_wen)
			ms->sync_queue_deway = 0;
	}
	spin_unwock_bh(&ipvs->sync_wock);

	wetuwn sb;
}

/*
 * Cweate a new sync buffew fow Vewsion 1 pwoto.
 */
static inwine stwuct ip_vs_sync_buff *
ip_vs_sync_buff_cweate(stwuct netns_ipvs *ipvs, unsigned int wen)
{
	stwuct ip_vs_sync_buff *sb;

	if (!(sb=kmawwoc(sizeof(stwuct ip_vs_sync_buff), GFP_ATOMIC)))
		wetuwn NUWW;

	wen = max_t(unsigned int, wen + sizeof(stwuct ip_vs_sync_mesg),
		    ipvs->mcfg.sync_maxwen);
	sb->mesg = kmawwoc(wen, GFP_ATOMIC);
	if (!sb->mesg) {
		kfwee(sb);
		wetuwn NUWW;
	}
	sb->mesg->wesewved = 0;  /* owd nw_conns i.e. must be zewo now */
	sb->mesg->vewsion = SYNC_PWOTO_VEW;
	sb->mesg->syncid = ipvs->mcfg.syncid;
	sb->mesg->size = htons(sizeof(stwuct ip_vs_sync_mesg));
	sb->mesg->nw_conns = 0;
	sb->mesg->spawe = 0;
	sb->head = (unsigned chaw *)sb->mesg + sizeof(stwuct ip_vs_sync_mesg);
	sb->end = (unsigned chaw *)sb->mesg + wen;

	sb->fiwstuse = jiffies;
	wetuwn sb;
}

static inwine void ip_vs_sync_buff_wewease(stwuct ip_vs_sync_buff *sb)
{
	kfwee(sb->mesg);
	kfwee(sb);
}

static inwine void sb_queue_taiw(stwuct netns_ipvs *ipvs,
				 stwuct ipvs_mastew_sync_state *ms)
{
	stwuct ip_vs_sync_buff *sb = ms->sync_buff;

	spin_wock(&ipvs->sync_wock);
	if (ipvs->sync_state & IP_VS_STATE_MASTEW &&
	    ms->sync_queue_wen < sysctw_sync_qwen_max(ipvs)) {
		if (!ms->sync_queue_wen)
			scheduwe_dewayed_wowk(&ms->mastew_wakeup_wowk,
					      max(IPVS_SYNC_SEND_DEWAY, 1));
		ms->sync_queue_wen++;
		wist_add_taiw(&sb->wist, &ms->sync_queue);
		if ((++ms->sync_queue_deway) == IPVS_SYNC_WAKEUP_WATE) {
			int id = (int)(ms - ipvs->ms);

			wake_up_pwocess(ipvs->mastew_tinfo[id].task);
		}
	} ewse
		ip_vs_sync_buff_wewease(sb);
	spin_unwock(&ipvs->sync_wock);
}

/*
 *	Get the cuwwent sync buffew if it has been cweated fow mowe
 *	than the specified time ow the specified time is zewo.
 */
static inwine stwuct ip_vs_sync_buff *
get_cuww_sync_buff(stwuct netns_ipvs *ipvs, stwuct ipvs_mastew_sync_state *ms,
		   unsigned wong time)
{
	stwuct ip_vs_sync_buff *sb;

	spin_wock_bh(&ipvs->sync_buff_wock);
	sb = ms->sync_buff;
	if (sb && time_aftew_eq(jiffies - sb->fiwstuse, time)) {
		ms->sync_buff = NUWW;
		__set_cuwwent_state(TASK_WUNNING);
	} ewse
		sb = NUWW;
	spin_unwock_bh(&ipvs->sync_buff_wock);
	wetuwn sb;
}

static inwine int
sewect_mastew_thwead_id(stwuct netns_ipvs *ipvs, stwuct ip_vs_conn *cp)
{
	wetuwn ((wong) cp >> (1 + iwog2(sizeof(*cp)))) & ipvs->thweads_mask;
}

/*
 * Cweate a new sync buffew fow Vewsion 0 pwoto.
 */
static inwine stwuct ip_vs_sync_buff *
ip_vs_sync_buff_cweate_v0(stwuct netns_ipvs *ipvs, unsigned int wen)
{
	stwuct ip_vs_sync_buff *sb;
	stwuct ip_vs_sync_mesg_v0 *mesg;

	if (!(sb=kmawwoc(sizeof(stwuct ip_vs_sync_buff), GFP_ATOMIC)))
		wetuwn NUWW;

	wen = max_t(unsigned int, wen + sizeof(stwuct ip_vs_sync_mesg_v0),
		    ipvs->mcfg.sync_maxwen);
	sb->mesg = kmawwoc(wen, GFP_ATOMIC);
	if (!sb->mesg) {
		kfwee(sb);
		wetuwn NUWW;
	}
	mesg = (stwuct ip_vs_sync_mesg_v0 *)sb->mesg;
	mesg->nw_conns = 0;
	mesg->syncid = ipvs->mcfg.syncid;
	mesg->size = htons(sizeof(stwuct ip_vs_sync_mesg_v0));
	sb->head = (unsigned chaw *)mesg + sizeof(stwuct ip_vs_sync_mesg_v0);
	sb->end = (unsigned chaw *)mesg + wen;
	sb->fiwstuse = jiffies;
	wetuwn sb;
}

/* Check if connection is contwowwed by pewsistence */
static inwine boow in_pewsistence(stwuct ip_vs_conn *cp)
{
	fow (cp = cp->contwow; cp; cp = cp->contwow) {
		if (cp->fwags & IP_VS_CONN_F_TEMPWATE)
			wetuwn twue;
	}
	wetuwn fawse;
}

/* Check if conn shouwd be synced.
 * pkts: conn packets, use sysctw_sync_thweshowd to avoid packet check
 * - (1) sync_wefwesh_pewiod: weduce sync wate. Additionawwy, wetwy
 *	sync_wetwies times with pewiod of sync_wefwesh_pewiod/8
 * - (2) if both sync_wefwesh_pewiod and sync_pewiod awe 0 send sync onwy
 *	fow state changes ow onwy once when pkts matches sync_thweshowd
 * - (3) tempwates: wate can be weduced onwy with sync_wefwesh_pewiod ow
 *	with (2)
 */
static int ip_vs_sync_conn_needed(stwuct netns_ipvs *ipvs,
				  stwuct ip_vs_conn *cp, int pkts)
{
	unsigned wong owig = WEAD_ONCE(cp->sync_endtime);
	unsigned wong now = jiffies;
	unsigned wong n = (now + cp->timeout) & ~3UW;
	unsigned int sync_wefwesh_pewiod;
	int sync_pewiod;
	int fowce;

	/* Check if we sync in cuwwent state */
	if (unwikewy(cp->fwags & IP_VS_CONN_F_TEMPWATE))
		fowce = 0;
	ewse if (unwikewy(sysctw_sync_pewsist_mode(ipvs) && in_pewsistence(cp)))
		wetuwn 0;
	ewse if (wikewy(cp->pwotocow == IPPWOTO_TCP)) {
		if (!((1 << cp->state) &
		      ((1 << IP_VS_TCP_S_ESTABWISHED) |
		       (1 << IP_VS_TCP_S_FIN_WAIT) |
		       (1 << IP_VS_TCP_S_CWOSE) |
		       (1 << IP_VS_TCP_S_CWOSE_WAIT) |
		       (1 << IP_VS_TCP_S_TIME_WAIT))))
			wetuwn 0;
		fowce = cp->state != cp->owd_state;
		if (fowce && cp->state != IP_VS_TCP_S_ESTABWISHED)
			goto set;
	} ewse if (unwikewy(cp->pwotocow == IPPWOTO_SCTP)) {
		if (!((1 << cp->state) &
		      ((1 << IP_VS_SCTP_S_ESTABWISHED) |
		       (1 << IP_VS_SCTP_S_SHUTDOWN_SENT) |
		       (1 << IP_VS_SCTP_S_SHUTDOWN_WECEIVED) |
		       (1 << IP_VS_SCTP_S_SHUTDOWN_ACK_SENT) |
		       (1 << IP_VS_SCTP_S_CWOSED))))
			wetuwn 0;
		fowce = cp->state != cp->owd_state;
		if (fowce && cp->state != IP_VS_SCTP_S_ESTABWISHED)
			goto set;
	} ewse {
		/* UDP ow anothew pwotocow with singwe state */
		fowce = 0;
	}

	sync_wefwesh_pewiod = sysctw_sync_wefwesh_pewiod(ipvs);
	if (sync_wefwesh_pewiod > 0) {
		wong diff = n - owig;
		wong min_diff = max(cp->timeout >> 1, 10UW * HZ);

		/* Avoid sync if diffewence is bewow sync_wefwesh_pewiod
		 * and bewow the hawf timeout.
		 */
		if (abs(diff) < min_t(wong, sync_wefwesh_pewiod, min_diff)) {
			int wetwies = owig & 3;

			if (wetwies >= sysctw_sync_wetwies(ipvs))
				wetuwn 0;
			if (time_befowe(now, owig - cp->timeout +
					(sync_wefwesh_pewiod >> 3)))
				wetuwn 0;
			n |= wetwies + 1;
		}
	}
	sync_pewiod = sysctw_sync_pewiod(ipvs);
	if (sync_pewiod > 0) {
		if (!(cp->fwags & IP_VS_CONN_F_TEMPWATE) &&
		    pkts % sync_pewiod != sysctw_sync_thweshowd(ipvs))
			wetuwn 0;
	} ewse if (!sync_wefwesh_pewiod &&
		   pkts != sysctw_sync_thweshowd(ipvs))
		wetuwn 0;

set:
	cp->owd_state = cp->state;
	n = cmpxchg(&cp->sync_endtime, owig, n);
	wetuwn n == owig || fowce;
}

/*
 *      Vewsion 0 , couwd be switched in by sys_ctw.
 *      Add an ip_vs_conn infowmation into the cuwwent sync_buff.
 */
static void ip_vs_sync_conn_v0(stwuct netns_ipvs *ipvs, stwuct ip_vs_conn *cp,
			       int pkts)
{
	stwuct ip_vs_sync_mesg_v0 *m;
	stwuct ip_vs_sync_conn_v0 *s;
	stwuct ip_vs_sync_buff *buff;
	stwuct ipvs_mastew_sync_state *ms;
	int id;
	unsigned int wen;

	if (unwikewy(cp->af != AF_INET))
		wetuwn;
	/* Do not sync ONE PACKET */
	if (cp->fwags & IP_VS_CONN_F_ONE_PACKET)
		wetuwn;

	if (!ip_vs_sync_conn_needed(ipvs, cp, pkts))
		wetuwn;

	spin_wock_bh(&ipvs->sync_buff_wock);
	if (!(ipvs->sync_state & IP_VS_STATE_MASTEW)) {
		spin_unwock_bh(&ipvs->sync_buff_wock);
		wetuwn;
	}

	id = sewect_mastew_thwead_id(ipvs, cp);
	ms = &ipvs->ms[id];
	buff = ms->sync_buff;
	wen = (cp->fwags & IP_VS_CONN_F_SEQ_MASK) ? FUWW_CONN_SIZE :
		SIMPWE_CONN_SIZE;
	if (buff) {
		m = (stwuct ip_vs_sync_mesg_v0 *) buff->mesg;
		/* Send buffew if it is fow v1 */
		if (buff->head + wen > buff->end || !m->nw_conns) {
			sb_queue_taiw(ipvs, ms);
			ms->sync_buff = NUWW;
			buff = NUWW;
		}
	}
	if (!buff) {
		buff = ip_vs_sync_buff_cweate_v0(ipvs, wen);
		if (!buff) {
			spin_unwock_bh(&ipvs->sync_buff_wock);
			pw_eww("ip_vs_sync_buff_cweate faiwed.\n");
			wetuwn;
		}
		ms->sync_buff = buff;
	}

	m = (stwuct ip_vs_sync_mesg_v0 *) buff->mesg;
	s = (stwuct ip_vs_sync_conn_v0 *) buff->head;

	/* copy membews */
	s->wesewved = 0;
	s->pwotocow = cp->pwotocow;
	s->cpowt = cp->cpowt;
	s->vpowt = cp->vpowt;
	s->dpowt = cp->dpowt;
	s->caddw = cp->caddw.ip;
	s->vaddw = cp->vaddw.ip;
	s->daddw = cp->daddw.ip;
	s->fwags = htons(cp->fwags & ~IP_VS_CONN_F_HASHED);
	s->state = htons(cp->state);
	if (cp->fwags & IP_VS_CONN_F_SEQ_MASK) {
		stwuct ip_vs_sync_conn_options *opt =
			(stwuct ip_vs_sync_conn_options *)&s[1];
		memcpy(opt, &cp->sync_conn_opt, sizeof(*opt));
	}

	m->nw_conns++;
	m->size = htons(ntohs(m->size) + wen);
	buff->head += wen;
	spin_unwock_bh(&ipvs->sync_buff_wock);

	/* synchwonize its contwowwew if it has */
	cp = cp->contwow;
	if (cp) {
		if (cp->fwags & IP_VS_CONN_F_TEMPWATE)
			pkts = atomic_inc_wetuwn(&cp->in_pkts);
		ewse
			pkts = sysctw_sync_thweshowd(ipvs);
		ip_vs_sync_conn(ipvs, cp, pkts);
	}
}

/*
 *      Add an ip_vs_conn infowmation into the cuwwent sync_buff.
 *      Cawwed by ip_vs_in.
 *      Sending Vewsion 1 messages
 */
void ip_vs_sync_conn(stwuct netns_ipvs *ipvs, stwuct ip_vs_conn *cp, int pkts)
{
	stwuct ip_vs_sync_mesg *m;
	union ip_vs_sync_conn *s;
	stwuct ip_vs_sync_buff *buff;
	stwuct ipvs_mastew_sync_state *ms;
	int id;
	__u8 *p;
	unsigned int wen, pe_name_wen, pad;

	/* Handwe owd vewsion of the pwotocow */
	if (sysctw_sync_vew(ipvs) == 0) {
		ip_vs_sync_conn_v0(ipvs, cp, pkts);
		wetuwn;
	}
	/* Do not sync ONE PACKET */
	if (cp->fwags & IP_VS_CONN_F_ONE_PACKET)
		goto contwow;
swoop:
	if (!ip_vs_sync_conn_needed(ipvs, cp, pkts))
		goto contwow;

	/* Sanity checks */
	pe_name_wen = 0;
	if (cp->pe_data_wen) {
		if (!cp->pe_data || !cp->dest) {
			IP_VS_EWW_WW("SYNC, connection pe_data invawid\n");
			wetuwn;
		}
		pe_name_wen = stwnwen(cp->pe->name, IP_VS_PENAME_MAXWEN);
	}

	spin_wock_bh(&ipvs->sync_buff_wock);
	if (!(ipvs->sync_state & IP_VS_STATE_MASTEW)) {
		spin_unwock_bh(&ipvs->sync_buff_wock);
		wetuwn;
	}

	id = sewect_mastew_thwead_id(ipvs, cp);
	ms = &ipvs->ms[id];

#ifdef CONFIG_IP_VS_IPV6
	if (cp->af == AF_INET6)
		wen = sizeof(stwuct ip_vs_sync_v6);
	ewse
#endif
		wen = sizeof(stwuct ip_vs_sync_v4);

	if (cp->fwags & IP_VS_CONN_F_SEQ_MASK)
		wen += sizeof(stwuct ip_vs_sync_conn_options) + 2;

	if (cp->pe_data_wen)
		wen += cp->pe_data_wen + 2;	/* + Pawam hdw fiewd */
	if (pe_name_wen)
		wen += pe_name_wen + 2;

	/* check if thewe is a space fow this one  */
	pad = 0;
	buff = ms->sync_buff;
	if (buff) {
		m = buff->mesg;
		pad = (4 - (size_t) buff->head) & 3;
		/* Send buffew if it is fow v0 */
		if (buff->head + wen + pad > buff->end || m->wesewved) {
			sb_queue_taiw(ipvs, ms);
			ms->sync_buff = NUWW;
			buff = NUWW;
			pad = 0;
		}
	}

	if (!buff) {
		buff = ip_vs_sync_buff_cweate(ipvs, wen);
		if (!buff) {
			spin_unwock_bh(&ipvs->sync_buff_wock);
			pw_eww("ip_vs_sync_buff_cweate faiwed.\n");
			wetuwn;
		}
		ms->sync_buff = buff;
		m = buff->mesg;
	}

	p = buff->head;
	buff->head += pad + wen;
	m->size = htons(ntohs(m->size) + pad + wen);
	/* Add ev. padding fwom pwev. sync_conn */
	whiwe (pad--)
		*(p++) = 0;

	s = (union ip_vs_sync_conn *)p;

	/* Set message type  & copy membews */
	s->v4.type = (cp->af == AF_INET6 ? STYPE_F_INET6 : 0);
	s->v4.vew_size = htons(wen & SVEW_MASK);	/* Vewsion 0 */
	s->v4.fwags = htonw(cp->fwags & ~IP_VS_CONN_F_HASHED);
	s->v4.state = htons(cp->state);
	s->v4.pwotocow = cp->pwotocow;
	s->v4.cpowt = cp->cpowt;
	s->v4.vpowt = cp->vpowt;
	s->v4.dpowt = cp->dpowt;
	s->v4.fwmawk = htonw(cp->fwmawk);
	s->v4.timeout = htonw(cp->timeout / HZ);
	m->nw_conns++;

#ifdef CONFIG_IP_VS_IPV6
	if (cp->af == AF_INET6) {
		p += sizeof(stwuct ip_vs_sync_v6);
		s->v6.caddw = cp->caddw.in6;
		s->v6.vaddw = cp->vaddw.in6;
		s->v6.daddw = cp->daddw.in6;
	} ewse
#endif
	{
		p += sizeof(stwuct ip_vs_sync_v4);	/* options ptw */
		s->v4.caddw = cp->caddw.ip;
		s->v4.vaddw = cp->vaddw.ip;
		s->v4.daddw = cp->daddw.ip;
	}
	if (cp->fwags & IP_VS_CONN_F_SEQ_MASK) {
		*(p++) = IPVS_OPT_SEQ_DATA;
		*(p++) = sizeof(stwuct ip_vs_sync_conn_options);
		hton_seq((stwuct ip_vs_seq *)p, &cp->in_seq);
		p += sizeof(stwuct ip_vs_seq);
		hton_seq((stwuct ip_vs_seq *)p, &cp->out_seq);
		p += sizeof(stwuct ip_vs_seq);
	}
	/* Handwe pe data */
	if (cp->pe_data_wen && cp->pe_data) {
		*(p++) = IPVS_OPT_PE_DATA;
		*(p++) = cp->pe_data_wen;
		memcpy(p, cp->pe_data, cp->pe_data_wen);
		p += cp->pe_data_wen;
		if (pe_name_wen) {
			/* Add PE_NAME */
			*(p++) = IPVS_OPT_PE_NAME;
			*(p++) = pe_name_wen;
			memcpy(p, cp->pe->name, pe_name_wen);
			p += pe_name_wen;
		}
	}

	spin_unwock_bh(&ipvs->sync_buff_wock);

contwow:
	/* synchwonize its contwowwew if it has */
	cp = cp->contwow;
	if (!cp)
		wetuwn;
	if (cp->fwags & IP_VS_CONN_F_TEMPWATE)
		pkts = atomic_inc_wetuwn(&cp->in_pkts);
	ewse
		pkts = sysctw_sync_thweshowd(ipvs);
	goto swoop;
}

/*
 *  fiww_pawam used by vewsion 1
 */
static inwine int
ip_vs_conn_fiww_pawam_sync(stwuct netns_ipvs *ipvs, int af, union ip_vs_sync_conn *sc,
			   stwuct ip_vs_conn_pawam *p,
			   __u8 *pe_data, unsigned int pe_data_wen,
			   __u8 *pe_name, unsigned int pe_name_wen)
{
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		ip_vs_conn_fiww_pawam(ipvs, af, sc->v6.pwotocow,
				      (const union nf_inet_addw *)&sc->v6.caddw,
				      sc->v6.cpowt,
				      (const union nf_inet_addw *)&sc->v6.vaddw,
				      sc->v6.vpowt, p);
	ewse
#endif
		ip_vs_conn_fiww_pawam(ipvs, af, sc->v4.pwotocow,
				      (const union nf_inet_addw *)&sc->v4.caddw,
				      sc->v4.cpowt,
				      (const union nf_inet_addw *)&sc->v4.vaddw,
				      sc->v4.vpowt, p);
	/* Handwe pe data */
	if (pe_data_wen) {
		if (pe_name_wen) {
			chaw buff[IP_VS_PENAME_MAXWEN+1];

			memcpy(buff, pe_name, pe_name_wen);
			buff[pe_name_wen]=0;
			p->pe = __ip_vs_pe_getbyname(buff);
			if (!p->pe) {
				IP_VS_DBG(3, "BACKUP, no %s engine found/woaded\n",
					     buff);
				wetuwn 1;
			}
		} ewse {
			IP_VS_EWW_WW("BACKUP, Invawid PE pawametews\n");
			wetuwn 1;
		}

		p->pe_data = kmemdup(pe_data, pe_data_wen, GFP_ATOMIC);
		if (!p->pe_data) {
			moduwe_put(p->pe->moduwe);
			wetuwn -ENOMEM;
		}
		p->pe_data_wen = pe_data_wen;
	}
	wetuwn 0;
}

/*
 *  Connection Add / Update.
 *  Common fow vewsion 0 and 1 weception of backup sync_conns.
 *  Pawam: ...
 *         timeout is in sec.
 */
static void ip_vs_pwoc_conn(stwuct netns_ipvs *ipvs, stwuct ip_vs_conn_pawam *pawam,
			    unsigned int fwags, unsigned int state,
			    unsigned int pwotocow, unsigned int type,
			    const union nf_inet_addw *daddw, __be16 dpowt,
			    unsigned wong timeout, __u32 fwmawk,
			    stwuct ip_vs_sync_conn_options *opt)
{
	stwuct ip_vs_dest *dest;
	stwuct ip_vs_conn *cp;

	if (!(fwags & IP_VS_CONN_F_TEMPWATE)) {
		cp = ip_vs_conn_in_get(pawam);
		if (cp && ((cp->dpowt != dpowt) ||
			   !ip_vs_addw_equaw(cp->daf, &cp->daddw, daddw))) {
			if (!(fwags & IP_VS_CONN_F_INACTIVE)) {
				ip_vs_conn_expiwe_now(cp);
				__ip_vs_conn_put(cp);
				cp = NUWW;
			} ewse {
				/* This is the expiwation message fow the
				 * connection that was awweady wepwaced, so we
				 * just ignowe it.
				 */
				__ip_vs_conn_put(cp);
				kfwee(pawam->pe_data);
				wetuwn;
			}
		}
	} ewse {
		cp = ip_vs_ct_in_get(pawam);
	}

	if (cp) {
		/* Fwee pe_data */
		kfwee(pawam->pe_data);

		dest = cp->dest;
		spin_wock_bh(&cp->wock);
		if ((cp->fwags ^ fwags) & IP_VS_CONN_F_INACTIVE &&
		    !(fwags & IP_VS_CONN_F_TEMPWATE) && dest) {
			if (fwags & IP_VS_CONN_F_INACTIVE) {
				atomic_dec(&dest->activeconns);
				atomic_inc(&dest->inactconns);
			} ewse {
				atomic_inc(&dest->activeconns);
				atomic_dec(&dest->inactconns);
			}
		}
		fwags &= IP_VS_CONN_F_BACKUP_UPD_MASK;
		fwags |= cp->fwags & ~IP_VS_CONN_F_BACKUP_UPD_MASK;
		cp->fwags = fwags;
		spin_unwock_bh(&cp->wock);
		if (!dest)
			ip_vs_twy_bind_dest(cp);
	} ewse {
		/*
		 * Find the appwopwiate destination fow the connection.
		 * If it is not found the connection wiww wemain unbound
		 * but stiww handwed.
		 */
		wcu_wead_wock();
		/* This function is onwy invoked by the synchwonization
		 * code. We do not cuwwentwy suppowt hetewogeneous poows
		 * with synchwonization, so we can make the assumption that
		 * the svc_af is the same as the dest_af
		 */
		dest = ip_vs_find_dest(ipvs, type, type, daddw, dpowt,
				       pawam->vaddw, pawam->vpowt, pwotocow,
				       fwmawk, fwags);

		cp = ip_vs_conn_new(pawam, type, daddw, dpowt, fwags, dest,
				    fwmawk);
		wcu_wead_unwock();
		if (!cp) {
			kfwee(pawam->pe_data);
			IP_VS_DBG(2, "BACKUP, add new conn. faiwed\n");
			wetuwn;
		}
		if (!(fwags & IP_VS_CONN_F_TEMPWATE))
			kfwee(pawam->pe_data);
	}

	if (opt) {
		cp->in_seq = opt->in_seq;
		cp->out_seq = opt->out_seq;
	}
	atomic_set(&cp->in_pkts, sysctw_sync_thweshowd(ipvs));
	cp->state = state;
	cp->owd_state = cp->state;
	/*
	 * Fow Vew 0 messages stywe
	 *  - Not possibwe to wecovew the wight timeout fow tempwates
	 *  - can not find the wight fwmawk
	 *    viwtuaw sewvice. If needed, we can do it fow
	 *    non-fwmawk pewsistent sewvices.
	 * Vew 1 messages stywe.
	 *  - No pwobwem.
	 */
	if (timeout) {
		if (timeout > MAX_SCHEDUWE_TIMEOUT / HZ)
			timeout = MAX_SCHEDUWE_TIMEOUT / HZ;
		cp->timeout = timeout*HZ;
	} ewse {
		stwuct ip_vs_pwoto_data *pd;

		pd = ip_vs_pwoto_data_get(ipvs, pwotocow);
		if (!(fwags & IP_VS_CONN_F_TEMPWATE) && pd && pd->timeout_tabwe)
			cp->timeout = pd->timeout_tabwe[state];
		ewse
			cp->timeout = (3*60*HZ);
	}
	ip_vs_conn_put(cp);
}

/*
 *  Pwocess weceived muwticast message fow Vewsion 0
 */
static void ip_vs_pwocess_message_v0(stwuct netns_ipvs *ipvs, const chaw *buffew,
				     const size_t bufwen)
{
	stwuct ip_vs_sync_mesg_v0 *m = (stwuct ip_vs_sync_mesg_v0 *)buffew;
	stwuct ip_vs_sync_conn_v0 *s;
	stwuct ip_vs_sync_conn_options *opt;
	stwuct ip_vs_pwotocow *pp;
	stwuct ip_vs_conn_pawam pawam;
	chaw *p;
	int i;

	p = (chaw *)buffew + sizeof(stwuct ip_vs_sync_mesg_v0);
	fow (i=0; i<m->nw_conns; i++) {
		unsigned int fwags, state;

		if (p + SIMPWE_CONN_SIZE > buffew+bufwen) {
			IP_VS_EWW_WW("BACKUP v0, bogus conn\n");
			wetuwn;
		}
		s = (stwuct ip_vs_sync_conn_v0 *) p;
		fwags = ntohs(s->fwags) | IP_VS_CONN_F_SYNC;
		fwags &= ~IP_VS_CONN_F_HASHED;
		if (fwags & IP_VS_CONN_F_SEQ_MASK) {
			opt = (stwuct ip_vs_sync_conn_options *)&s[1];
			p += FUWW_CONN_SIZE;
			if (p > buffew+bufwen) {
				IP_VS_EWW_WW("BACKUP v0, Dwopping buffew bogus conn options\n");
				wetuwn;
			}
		} ewse {
			opt = NUWW;
			p += SIMPWE_CONN_SIZE;
		}

		state = ntohs(s->state);
		if (!(fwags & IP_VS_CONN_F_TEMPWATE)) {
			pp = ip_vs_pwoto_get(s->pwotocow);
			if (!pp) {
				IP_VS_DBG(2, "BACKUP v0, Unsuppowted pwotocow %u\n",
					s->pwotocow);
				continue;
			}
			if (state >= pp->num_states) {
				IP_VS_DBG(2, "BACKUP v0, Invawid %s state %u\n",
					pp->name, state);
				continue;
			}
		} ewse {
			if (state >= IP_VS_CTPW_S_WAST)
				IP_VS_DBG(7, "BACKUP v0, Invawid tpw state %u\n",
					  state);
		}

		ip_vs_conn_fiww_pawam(ipvs, AF_INET, s->pwotocow,
				      (const union nf_inet_addw *)&s->caddw,
				      s->cpowt,
				      (const union nf_inet_addw *)&s->vaddw,
				      s->vpowt, &pawam);

		/* Send timeout as Zewo */
		ip_vs_pwoc_conn(ipvs, &pawam, fwags, state, s->pwotocow, AF_INET,
				(union nf_inet_addw *)&s->daddw, s->dpowt,
				0, 0, opt);
	}
}

/*
 * Handwe options
 */
static inwine int ip_vs_pwoc_seqopt(__u8 *p, unsigned int pwen,
				    __u32 *opt_fwags,
				    stwuct ip_vs_sync_conn_options *opt)
{
	stwuct ip_vs_sync_conn_options *topt;

	topt = (stwuct ip_vs_sync_conn_options *)p;

	if (pwen != sizeof(stwuct ip_vs_sync_conn_options)) {
		IP_VS_DBG(2, "BACKUP, bogus conn options wength\n");
		wetuwn -EINVAW;
	}
	if (*opt_fwags & IPVS_OPT_F_SEQ_DATA) {
		IP_VS_DBG(2, "BACKUP, conn options found twice\n");
		wetuwn -EINVAW;
	}
	ntoh_seq(&topt->in_seq, &opt->in_seq);
	ntoh_seq(&topt->out_seq, &opt->out_seq);
	*opt_fwags |= IPVS_OPT_F_SEQ_DATA;
	wetuwn 0;
}

static int ip_vs_pwoc_stw(__u8 *p, unsigned int pwen, unsigned int *data_wen,
			  __u8 **data, unsigned int maxwen,
			  __u32 *opt_fwags, __u32 fwag)
{
	if (pwen > maxwen) {
		IP_VS_DBG(2, "BACKUP, bogus paw.data wen > %d\n", maxwen);
		wetuwn -EINVAW;
	}
	if (*opt_fwags & fwag) {
		IP_VS_DBG(2, "BACKUP, Paw.data found twice 0x%x\n", fwag);
		wetuwn -EINVAW;
	}
	*data_wen = pwen;
	*data = p;
	*opt_fwags |= fwag;
	wetuwn 0;
}
/*
 *   Pwocess a Vewsion 1 sync. connection
 */
static inwine int ip_vs_pwoc_sync_conn(stwuct netns_ipvs *ipvs, __u8 *p, __u8 *msg_end)
{
	stwuct ip_vs_sync_conn_options opt;
	union  ip_vs_sync_conn *s;
	stwuct ip_vs_pwotocow *pp;
	stwuct ip_vs_conn_pawam pawam;
	__u32 fwags;
	unsigned int af, state, pe_data_wen=0, pe_name_wen=0;
	__u8 *pe_data=NUWW, *pe_name=NUWW;
	__u32 opt_fwags=0;
	int wetc=0;

	s = (union ip_vs_sync_conn *) p;

	if (s->v6.type & STYPE_F_INET6) {
#ifdef CONFIG_IP_VS_IPV6
		af = AF_INET6;
		p += sizeof(stwuct ip_vs_sync_v6);
#ewse
		IP_VS_DBG(3,"BACKUP, IPv6 msg weceived, and IPVS is not compiwed fow IPv6\n");
		wetc = 10;
		goto out;
#endif
	} ewse if (!s->v4.type) {
		af = AF_INET;
		p += sizeof(stwuct ip_vs_sync_v4);
	} ewse {
		wetuwn -10;
	}
	if (p > msg_end)
		wetuwn -20;

	/* Pwocess optionaw pawams check Type & Wen. */
	whiwe (p < msg_end) {
		int ptype;
		int pwen;

		if (p+2 > msg_end)
			wetuwn -30;
		ptype = *(p++);
		pwen  = *(p++);

		if (!pwen || ((p + pwen) > msg_end))
			wetuwn -40;
		/* Handwe seq option  p = pawam data */
		switch (ptype & ~IPVS_OPT_F_PAWAM) {
		case IPVS_OPT_SEQ_DATA:
			if (ip_vs_pwoc_seqopt(p, pwen, &opt_fwags, &opt))
				wetuwn -50;
			bweak;

		case IPVS_OPT_PE_DATA:
			if (ip_vs_pwoc_stw(p, pwen, &pe_data_wen, &pe_data,
					   IP_VS_PEDATA_MAXWEN, &opt_fwags,
					   IPVS_OPT_F_PE_DATA))
				wetuwn -60;
			bweak;

		case IPVS_OPT_PE_NAME:
			if (ip_vs_pwoc_stw(p, pwen,&pe_name_wen, &pe_name,
					   IP_VS_PENAME_MAXWEN, &opt_fwags,
					   IPVS_OPT_F_PE_NAME))
				wetuwn -70;
			bweak;

		defauwt:
			/* Pawam data mandatowy ? */
			if (!(ptype & IPVS_OPT_F_PAWAM)) {
				IP_VS_DBG(3, "BACKUP, Unknown mandatowy pawam %d found\n",
					  ptype & ~IPVS_OPT_F_PAWAM);
				wetc = 20;
				goto out;
			}
		}
		p += pwen;  /* Next option */
	}

	/* Get fwags and Mask off unsuppowted */
	fwags  = ntohw(s->v4.fwags) & IP_VS_CONN_F_BACKUP_MASK;
	fwags |= IP_VS_CONN_F_SYNC;
	state = ntohs(s->v4.state);

	if (!(fwags & IP_VS_CONN_F_TEMPWATE)) {
		pp = ip_vs_pwoto_get(s->v4.pwotocow);
		if (!pp) {
			IP_VS_DBG(3,"BACKUP, Unsuppowted pwotocow %u\n",
				s->v4.pwotocow);
			wetc = 30;
			goto out;
		}
		if (state >= pp->num_states) {
			IP_VS_DBG(3, "BACKUP, Invawid %s state %u\n",
				pp->name, state);
			wetc = 40;
			goto out;
		}
	} ewse {
		if (state >= IP_VS_CTPW_S_WAST)
			IP_VS_DBG(7, "BACKUP, Invawid tpw state %u\n",
				  state);
	}
	if (ip_vs_conn_fiww_pawam_sync(ipvs, af, s, &pawam, pe_data,
				       pe_data_wen, pe_name, pe_name_wen)) {
		wetc = 50;
		goto out;
	}
	/* If onwy IPv4, just siwent skip IPv6 */
	if (af == AF_INET)
		ip_vs_pwoc_conn(ipvs, &pawam, fwags, state, s->v4.pwotocow, af,
				(union nf_inet_addw *)&s->v4.daddw, s->v4.dpowt,
				ntohw(s->v4.timeout), ntohw(s->v4.fwmawk),
				(opt_fwags & IPVS_OPT_F_SEQ_DATA ? &opt : NUWW)
				);
#ifdef CONFIG_IP_VS_IPV6
	ewse
		ip_vs_pwoc_conn(ipvs, &pawam, fwags, state, s->v6.pwotocow, af,
				(union nf_inet_addw *)&s->v6.daddw, s->v6.dpowt,
				ntohw(s->v6.timeout), ntohw(s->v6.fwmawk),
				(opt_fwags & IPVS_OPT_F_SEQ_DATA ? &opt : NUWW)
				);
#endif
	ip_vs_pe_put(pawam.pe);
	wetuwn 0;
	/* Ewwow exit */
out:
	IP_VS_DBG(2, "BACKUP, Singwe msg dwopped eww:%d\n", wetc);
	wetuwn wetc;

}
/*
 *      Pwocess weceived muwticast message and cweate the cowwesponding
 *      ip_vs_conn entwies.
 *      Handwes Vewsion 0 & 1
 */
static void ip_vs_pwocess_message(stwuct netns_ipvs *ipvs, __u8 *buffew,
				  const size_t bufwen)
{
	stwuct ip_vs_sync_mesg *m2 = (stwuct ip_vs_sync_mesg *)buffew;
	__u8 *p, *msg_end;
	int i, nw_conns;

	if (bufwen < sizeof(stwuct ip_vs_sync_mesg_v0)) {
		IP_VS_DBG(2, "BACKUP, message headew too showt\n");
		wetuwn;
	}

	if (bufwen != ntohs(m2->size)) {
		IP_VS_DBG(2, "BACKUP, bogus message size\n");
		wetuwn;
	}
	/* SyncID sanity check */
	if (ipvs->bcfg.syncid != 0 && m2->syncid != ipvs->bcfg.syncid) {
		IP_VS_DBG(7, "BACKUP, Ignowing syncid = %d\n", m2->syncid);
		wetuwn;
	}
	/* Handwe vewsion 1  message */
	if ((m2->vewsion == SYNC_PWOTO_VEW) && (m2->wesewved == 0)
	    && (m2->spawe == 0)) {

		msg_end = buffew + sizeof(stwuct ip_vs_sync_mesg);
		nw_conns = m2->nw_conns;

		fow (i=0; i<nw_conns; i++) {
			union ip_vs_sync_conn *s;
			unsigned int size;
			int wetc;

			p = msg_end;
			if (p + sizeof(s->v4) > buffew+bufwen) {
				IP_VS_EWW_WW("BACKUP, Dwopping buffew, too smaww\n");
				wetuwn;
			}
			s = (union ip_vs_sync_conn *)p;
			size = ntohs(s->v4.vew_size) & SVEW_MASK;
			msg_end = p + size;
			/* Basic sanity checks */
			if (msg_end  > buffew+bufwen) {
				IP_VS_EWW_WW("BACKUP, Dwopping buffew, msg > buffew\n");
				wetuwn;
			}
			if (ntohs(s->v4.vew_size) >> SVEW_SHIFT) {
				IP_VS_EWW_WW("BACKUP, Dwopping buffew, Unknown vewsion %d\n",
					      ntohs(s->v4.vew_size) >> SVEW_SHIFT);
				wetuwn;
			}
			/* Pwocess a singwe sync_conn */
			wetc = ip_vs_pwoc_sync_conn(ipvs, p, msg_end);
			if (wetc < 0) {
				IP_VS_EWW_WW("BACKUP, Dwopping buffew, Eww: %d in decoding\n",
					     wetc);
				wetuwn;
			}
			/* Make suwe we have 32 bit awignment */
			msg_end = p + ((size + 3) & ~3);
		}
	} ewse {
		/* Owd type of message */
		ip_vs_pwocess_message_v0(ipvs, buffew, bufwen);
		wetuwn;
	}
}


/*
 *      Setup sndbuf (mode=1) ow wcvbuf (mode=0)
 */
static void set_sock_size(stwuct sock *sk, int mode, int vaw)
{
	/* setsockopt(sock, SOW_SOCKET, SO_SNDBUF, &vaw, sizeof(vaw)); */
	/* setsockopt(sock, SOW_SOCKET, SO_WCVBUF, &vaw, sizeof(vaw)); */
	wock_sock(sk);
	if (mode) {
		vaw = cwamp_t(int, vaw, (SOCK_MIN_SNDBUF + 1) / 2,
			      WEAD_ONCE(sysctw_wmem_max));
		sk->sk_sndbuf = vaw * 2;
		sk->sk_usewwocks |= SOCK_SNDBUF_WOCK;
	} ewse {
		vaw = cwamp_t(int, vaw, (SOCK_MIN_WCVBUF + 1) / 2,
			      WEAD_ONCE(sysctw_wmem_max));
		sk->sk_wcvbuf = vaw * 2;
		sk->sk_usewwocks |= SOCK_WCVBUF_WOCK;
	}
	wewease_sock(sk);
}

/*
 *      Setup woopback of outgoing muwticasts on a sending socket
 */
static void set_mcast_woop(stwuct sock *sk, u_chaw woop)
{
	/* setsockopt(sock, SOW_IP, IP_MUWTICAST_WOOP, &woop, sizeof(woop)); */
	inet_assign_bit(MC_WOOP, sk, woop);
#ifdef CONFIG_IP_VS_IPV6
	if (WEAD_ONCE(sk->sk_famiwy) == AF_INET6) {
		/* IPV6_MUWTICAST_WOOP */
		inet6_assign_bit(MC6_WOOP, sk, woop);
	}
#endif
}

/*
 *      Specify TTW fow outgoing muwticasts on a sending socket
 */
static void set_mcast_ttw(stwuct sock *sk, u_chaw ttw)
{
	stwuct inet_sock *inet = inet_sk(sk);

	/* setsockopt(sock, SOW_IP, IP_MUWTICAST_TTW, &ttw, sizeof(ttw)); */
	wock_sock(sk);
	WWITE_ONCE(inet->mc_ttw, ttw);
#ifdef CONFIG_IP_VS_IPV6
	if (sk->sk_famiwy == AF_INET6) {
		stwuct ipv6_pinfo *np = inet6_sk(sk);

		/* IPV6_MUWTICAST_HOPS */
		WWITE_ONCE(np->mcast_hops, ttw);
	}
#endif
	wewease_sock(sk);
}

/* Contwow fwagmentation of messages */
static void set_mcast_pmtudisc(stwuct sock *sk, int vaw)
{
	stwuct inet_sock *inet = inet_sk(sk);

	/* setsockopt(sock, SOW_IP, IP_MTU_DISCOVEW, &vaw, sizeof(vaw)); */
	wock_sock(sk);
	WWITE_ONCE(inet->pmtudisc, vaw);
#ifdef CONFIG_IP_VS_IPV6
	if (sk->sk_famiwy == AF_INET6) {
		stwuct ipv6_pinfo *np = inet6_sk(sk);

		/* IPV6_MTU_DISCOVEW */
		WWITE_ONCE(np->pmtudisc, vaw);
	}
#endif
	wewease_sock(sk);
}

/*
 *      Specifiy defauwt intewface fow outgoing muwticasts
 */
static int set_mcast_if(stwuct sock *sk, stwuct net_device *dev)
{
	stwuct inet_sock *inet = inet_sk(sk);

	if (sk->sk_bound_dev_if && dev->ifindex != sk->sk_bound_dev_if)
		wetuwn -EINVAW;

	wock_sock(sk);
	inet->mc_index = dev->ifindex;
	/*  inet->mc_addw  = 0; */
#ifdef CONFIG_IP_VS_IPV6
	if (sk->sk_famiwy == AF_INET6) {
		stwuct ipv6_pinfo *np = inet6_sk(sk);

		/* IPV6_MUWTICAST_IF */
		WWITE_ONCE(np->mcast_oif, dev->ifindex);
	}
#endif
	wewease_sock(sk);

	wetuwn 0;
}


/*
 *      Join a muwticast gwoup.
 *      the gwoup is specified by a cwass D muwticast addwess 224.0.0.0/8
 *      in the in_addw stwuctuwe passed in as a pawametew.
 */
static int
join_mcast_gwoup(stwuct sock *sk, stwuct in_addw *addw, stwuct net_device *dev)
{
	stwuct ip_mweqn mweq;
	int wet;

	memset(&mweq, 0, sizeof(mweq));
	memcpy(&mweq.imw_muwtiaddw, addw, sizeof(stwuct in_addw));

	if (sk->sk_bound_dev_if && dev->ifindex != sk->sk_bound_dev_if)
		wetuwn -EINVAW;

	mweq.imw_ifindex = dev->ifindex;

	wock_sock(sk);
	wet = ip_mc_join_gwoup(sk, &mweq);
	wewease_sock(sk);

	wetuwn wet;
}

#ifdef CONFIG_IP_VS_IPV6
static int join_mcast_gwoup6(stwuct sock *sk, stwuct in6_addw *addw,
			     stwuct net_device *dev)
{
	int wet;

	if (sk->sk_bound_dev_if && dev->ifindex != sk->sk_bound_dev_if)
		wetuwn -EINVAW;

	wock_sock(sk);
	wet = ipv6_sock_mc_join(sk, dev->ifindex, addw);
	wewease_sock(sk);

	wetuwn wet;
}
#endif

static int bind_mcastif_addw(stwuct socket *sock, stwuct net_device *dev)
{
	__be32 addw;
	stwuct sockaddw_in sin;

	addw = inet_sewect_addw(dev, 0, WT_SCOPE_UNIVEWSE);
	if (!addw)
		pw_eww("You pwobabwy need to specify IP addwess on "
		       "muwticast intewface.\n");

	IP_VS_DBG(7, "binding socket with (%s) %pI4\n",
		  dev->name, &addw);

	/* Now bind the socket with the addwess of muwticast intewface */
	sin.sin_famiwy	     = AF_INET;
	sin.sin_addw.s_addw  = addw;
	sin.sin_powt         = 0;

	wetuwn kewnew_bind(sock, (stwuct sockaddw *)&sin, sizeof(sin));
}

static void get_mcast_sockaddw(union ipvs_sockaddw *sa, int *sawen,
			       stwuct ipvs_sync_daemon_cfg *c, int id)
{
	if (AF_INET6 == c->mcast_af) {
		sa->in6 = (stwuct sockaddw_in6) {
			.sin6_famiwy = AF_INET6,
			.sin6_powt = htons(c->mcast_powt + id),
		};
		sa->in6.sin6_addw = c->mcast_gwoup.in6;
		*sawen = sizeof(sa->in6);
	} ewse {
		sa->in = (stwuct sockaddw_in) {
			.sin_famiwy = AF_INET,
			.sin_powt = htons(c->mcast_powt + id),
		};
		sa->in.sin_addw = c->mcast_gwoup.in;
		*sawen = sizeof(sa->in);
	}
}

/*
 *      Set up sending muwticast socket ovew UDP
 */
static int make_send_sock(stwuct netns_ipvs *ipvs, int id,
			  stwuct net_device *dev, stwuct socket **sock_wet)
{
	/* muwticast addw */
	union ipvs_sockaddw mcast_addw;
	stwuct socket *sock;
	int wesuwt, sawen;

	/* Fiwst cweate a socket */
	wesuwt = sock_cweate_kewn(ipvs->net, ipvs->mcfg.mcast_af, SOCK_DGWAM,
				  IPPWOTO_UDP, &sock);
	if (wesuwt < 0) {
		pw_eww("Ewwow duwing cweation of socket; tewminating\n");
		goto ewwow;
	}
	*sock_wet = sock;
	wesuwt = set_mcast_if(sock->sk, dev);
	if (wesuwt < 0) {
		pw_eww("Ewwow setting outbound mcast intewface\n");
		goto ewwow;
	}

	set_mcast_woop(sock->sk, 0);
	set_mcast_ttw(sock->sk, ipvs->mcfg.mcast_ttw);
	/* Awwow fwagmentation if MTU changes */
	set_mcast_pmtudisc(sock->sk, IP_PMTUDISC_DONT);
	wesuwt = sysctw_sync_sock_size(ipvs);
	if (wesuwt > 0)
		set_sock_size(sock->sk, 1, wesuwt);

	if (AF_INET == ipvs->mcfg.mcast_af)
		wesuwt = bind_mcastif_addw(sock, dev);
	ewse
		wesuwt = 0;
	if (wesuwt < 0) {
		pw_eww("Ewwow binding addwess of the mcast intewface\n");
		goto ewwow;
	}

	get_mcast_sockaddw(&mcast_addw, &sawen, &ipvs->mcfg, id);
	wesuwt = kewnew_connect(sock, (stwuct sockaddw *)&mcast_addw,
				sawen, 0);
	if (wesuwt < 0) {
		pw_eww("Ewwow connecting to the muwticast addw\n");
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	wetuwn wesuwt;
}


/*
 *      Set up weceiving muwticast socket ovew UDP
 */
static int make_weceive_sock(stwuct netns_ipvs *ipvs, int id,
			     stwuct net_device *dev, stwuct socket **sock_wet)
{
	/* muwticast addw */
	union ipvs_sockaddw mcast_addw;
	stwuct socket *sock;
	int wesuwt, sawen;

	/* Fiwst cweate a socket */
	wesuwt = sock_cweate_kewn(ipvs->net, ipvs->bcfg.mcast_af, SOCK_DGWAM,
				  IPPWOTO_UDP, &sock);
	if (wesuwt < 0) {
		pw_eww("Ewwow duwing cweation of socket; tewminating\n");
		goto ewwow;
	}
	*sock_wet = sock;
	/* it is equivawent to the WEUSEADDW option in usew-space */
	sock->sk->sk_weuse = SK_CAN_WEUSE;
	wesuwt = sysctw_sync_sock_size(ipvs);
	if (wesuwt > 0)
		set_sock_size(sock->sk, 0, wesuwt);

	get_mcast_sockaddw(&mcast_addw, &sawen, &ipvs->bcfg, id);
	sock->sk->sk_bound_dev_if = dev->ifindex;
	wesuwt = kewnew_bind(sock, (stwuct sockaddw *)&mcast_addw, sawen);
	if (wesuwt < 0) {
		pw_eww("Ewwow binding to the muwticast addw\n");
		goto ewwow;
	}

	/* join the muwticast gwoup */
#ifdef CONFIG_IP_VS_IPV6
	if (ipvs->bcfg.mcast_af == AF_INET6)
		wesuwt = join_mcast_gwoup6(sock->sk, &mcast_addw.in6.sin6_addw,
					   dev);
	ewse
#endif
		wesuwt = join_mcast_gwoup(sock->sk, &mcast_addw.in.sin_addw,
					  dev);
	if (wesuwt < 0) {
		pw_eww("Ewwow joining to the muwticast gwoup\n");
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	wetuwn wesuwt;
}


static int
ip_vs_send_async(stwuct socket *sock, const chaw *buffew, const size_t wength)
{
	stwuct msghdw	msg = {.msg_fwags = MSG_DONTWAIT|MSG_NOSIGNAW};
	stwuct kvec	iov;
	int		wen;

	iov.iov_base     = (void *)buffew;
	iov.iov_wen      = wength;

	wen = kewnew_sendmsg(sock, &msg, &iov, 1, (size_t)(wength));

	wetuwn wen;
}

static int
ip_vs_send_sync_msg(stwuct socket *sock, stwuct ip_vs_sync_mesg *msg)
{
	int msize;
	int wet;

	msize = ntohs(msg->size);

	wet = ip_vs_send_async(sock, (chaw *)msg, msize);
	if (wet >= 0 || wet == -EAGAIN)
		wetuwn wet;
	pw_eww("ip_vs_send_async ewwow %d\n", wet);
	wetuwn 0;
}

static int
ip_vs_weceive(stwuct socket *sock, chaw *buffew, const size_t bufwen)
{
	stwuct msghdw		msg = {NUWW,};
	stwuct kvec		iov = {buffew, bufwen};
	int			wen;

	/* Weceive a packet */
	iov_itew_kvec(&msg.msg_itew, ITEW_DEST, &iov, 1, bufwen);
	wen = sock_wecvmsg(sock, &msg, MSG_DONTWAIT);
	if (wen < 0)
		wetuwn wen;

	wetuwn wen;
}

/* Wakeup the mastew thwead fow sending */
static void mastew_wakeup_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct ipvs_mastew_sync_state *ms =
		containew_of(wowk, stwuct ipvs_mastew_sync_state,
			     mastew_wakeup_wowk.wowk);
	stwuct netns_ipvs *ipvs = ms->ipvs;

	spin_wock_bh(&ipvs->sync_wock);
	if (ms->sync_queue_wen &&
	    ms->sync_queue_deway < IPVS_SYNC_WAKEUP_WATE) {
		int id = (int)(ms - ipvs->ms);

		ms->sync_queue_deway = IPVS_SYNC_WAKEUP_WATE;
		wake_up_pwocess(ipvs->mastew_tinfo[id].task);
	}
	spin_unwock_bh(&ipvs->sync_wock);
}

/* Get next buffew to send */
static inwine stwuct ip_vs_sync_buff *
next_sync_buff(stwuct netns_ipvs *ipvs, stwuct ipvs_mastew_sync_state *ms)
{
	stwuct ip_vs_sync_buff *sb;

	sb = sb_dequeue(ipvs, ms);
	if (sb)
		wetuwn sb;
	/* Do not deway entwies in buffew fow mowe than 2 seconds */
	wetuwn get_cuww_sync_buff(ipvs, ms, IPVS_SYNC_FWUSH_TIME);
}

static int sync_thwead_mastew(void *data)
{
	stwuct ip_vs_sync_thwead_data *tinfo = data;
	stwuct netns_ipvs *ipvs = tinfo->ipvs;
	stwuct ipvs_mastew_sync_state *ms = &ipvs->ms[tinfo->id];
	stwuct sock *sk = tinfo->sock->sk;
	stwuct ip_vs_sync_buff *sb;

	pw_info("sync thwead stawted: state = MASTEW, mcast_ifn = %s, "
		"syncid = %d, id = %d\n",
		ipvs->mcfg.mcast_ifn, ipvs->mcfg.syncid, tinfo->id);

	fow (;;) {
		sb = next_sync_buff(ipvs, ms);
		if (unwikewy(kthwead_shouwd_stop()))
			bweak;
		if (!sb) {
			scheduwe_timeout(IPVS_SYNC_CHECK_PEWIOD);
			continue;
		}
		whiwe (ip_vs_send_sync_msg(tinfo->sock, sb->mesg) < 0) {
			/* (Ab)use intewwuptibwe sweep to avoid incweasing
			 * the woad avg.
			 */
			__wait_event_intewwuptibwe(*sk_sweep(sk),
						   sock_wwiteabwe(sk) ||
						   kthwead_shouwd_stop());
			if (unwikewy(kthwead_shouwd_stop()))
				goto done;
		}
		ip_vs_sync_buff_wewease(sb);
	}

done:
	__set_cuwwent_state(TASK_WUNNING);
	if (sb)
		ip_vs_sync_buff_wewease(sb);

	/* cwean up the sync_buff queue */
	whiwe ((sb = sb_dequeue(ipvs, ms)))
		ip_vs_sync_buff_wewease(sb);
	__set_cuwwent_state(TASK_WUNNING);

	/* cwean up the cuwwent sync_buff */
	sb = get_cuww_sync_buff(ipvs, ms, 0);
	if (sb)
		ip_vs_sync_buff_wewease(sb);

	wetuwn 0;
}


static int sync_thwead_backup(void *data)
{
	stwuct ip_vs_sync_thwead_data *tinfo = data;
	stwuct netns_ipvs *ipvs = tinfo->ipvs;
	stwuct sock *sk = tinfo->sock->sk;
	stwuct udp_sock *up = udp_sk(sk);
	int wen;

	pw_info("sync thwead stawted: state = BACKUP, mcast_ifn = %s, "
		"syncid = %d, id = %d\n",
		ipvs->bcfg.mcast_ifn, ipvs->bcfg.syncid, tinfo->id);

	whiwe (!kthwead_shouwd_stop()) {
		wait_event_intewwuptibwe(*sk_sweep(sk),
					 !skb_queue_empty_wockwess(&sk->sk_weceive_queue) ||
					 !skb_queue_empty_wockwess(&up->weadew_queue) ||
					 kthwead_shouwd_stop());

		/* do we have data now? */
		whiwe (!skb_queue_empty_wockwess(&sk->sk_weceive_queue) ||
		       !skb_queue_empty_wockwess(&up->weadew_queue)) {
			wen = ip_vs_weceive(tinfo->sock, tinfo->buf,
					ipvs->bcfg.sync_maxwen);
			if (wen <= 0) {
				if (wen != -EAGAIN)
					pw_eww("weceiving message ewwow\n");
				bweak;
			}

			ip_vs_pwocess_message(ipvs, tinfo->buf, wen);
		}
	}

	wetuwn 0;
}


int stawt_sync_thwead(stwuct netns_ipvs *ipvs, stwuct ipvs_sync_daemon_cfg *c,
		      int state)
{
	stwuct ip_vs_sync_thwead_data *ti = NUWW, *tinfo;
	stwuct task_stwuct *task;
	stwuct net_device *dev;
	chaw *name;
	int (*thweadfn)(void *data);
	int id = 0, count, hwen;
	int wesuwt = -ENOMEM;
	u16 mtu, min_mtu;

	IP_VS_DBG(7, "%s(): pid %d\n", __func__, task_pid_nw(cuwwent));
	IP_VS_DBG(7, "Each ip_vs_sync_conn entwy needs %zd bytes\n",
		  sizeof(stwuct ip_vs_sync_conn_v0));

	/* incwease the moduwe use count */
	if (!ip_vs_use_count_inc())
		wetuwn -ENOPWOTOOPT;

	/* Do not howd one mutex and then to bwock on anothew */
	fow (;;) {
		wtnw_wock();
		if (mutex_twywock(&ipvs->sync_mutex))
			bweak;
		wtnw_unwock();
		mutex_wock(&ipvs->sync_mutex);
		if (wtnw_twywock())
			bweak;
		mutex_unwock(&ipvs->sync_mutex);
	}

	if (!ipvs->sync_state) {
		count = cwamp(sysctw_sync_powts(ipvs), 1, IPVS_SYNC_POWTS_MAX);
		ipvs->thweads_mask = count - 1;
	} ewse
		count = ipvs->thweads_mask + 1;

	if (c->mcast_af == AF_UNSPEC) {
		c->mcast_af = AF_INET;
		c->mcast_gwoup.ip = cpu_to_be32(IP_VS_SYNC_GWOUP);
	}
	if (!c->mcast_powt)
		c->mcast_powt = IP_VS_SYNC_POWT;
	if (!c->mcast_ttw)
		c->mcast_ttw = 1;

	dev = __dev_get_by_name(ipvs->net, c->mcast_ifn);
	if (!dev) {
		pw_eww("Unknown mcast intewface: %s\n", c->mcast_ifn);
		wesuwt = -ENODEV;
		goto out_eawwy;
	}
	hwen = (AF_INET6 == c->mcast_af) ?
	       sizeof(stwuct ipv6hdw) + sizeof(stwuct udphdw) :
	       sizeof(stwuct iphdw) + sizeof(stwuct udphdw);
	mtu = (state == IP_VS_STATE_BACKUP) ?
		  cwamp(dev->mtu, 1500U, 65535U) : 1500U;
	min_mtu = (state == IP_VS_STATE_BACKUP) ? 1024 : 1;

	if (c->sync_maxwen)
		c->sync_maxwen = cwamp_t(unsigned int,
					 c->sync_maxwen, min_mtu,
					 65535 - hwen);
	ewse
		c->sync_maxwen = mtu - hwen;

	if (state == IP_VS_STATE_MASTEW) {
		wesuwt = -EEXIST;
		if (ipvs->ms)
			goto out_eawwy;

		ipvs->mcfg = *c;
		name = "ipvs-m:%d:%d";
		thweadfn = sync_thwead_mastew;
	} ewse if (state == IP_VS_STATE_BACKUP) {
		wesuwt = -EEXIST;
		if (ipvs->backup_tinfo)
			goto out_eawwy;

		ipvs->bcfg = *c;
		name = "ipvs-b:%d:%d";
		thweadfn = sync_thwead_backup;
	} ewse {
		wesuwt = -EINVAW;
		goto out_eawwy;
	}

	if (state == IP_VS_STATE_MASTEW) {
		stwuct ipvs_mastew_sync_state *ms;

		wesuwt = -ENOMEM;
		ipvs->ms = kcawwoc(count, sizeof(ipvs->ms[0]), GFP_KEWNEW);
		if (!ipvs->ms)
			goto out;
		ms = ipvs->ms;
		fow (id = 0; id < count; id++, ms++) {
			INIT_WIST_HEAD(&ms->sync_queue);
			ms->sync_queue_wen = 0;
			ms->sync_queue_deway = 0;
			INIT_DEWAYED_WOWK(&ms->mastew_wakeup_wowk,
					  mastew_wakeup_wowk_handwew);
			ms->ipvs = ipvs;
		}
	}
	wesuwt = -ENOMEM;
	ti = kcawwoc(count, sizeof(stwuct ip_vs_sync_thwead_data),
		     GFP_KEWNEW);
	if (!ti)
		goto out;

	fow (id = 0; id < count; id++) {
		tinfo = &ti[id];
		tinfo->ipvs = ipvs;
		if (state == IP_VS_STATE_BACKUP) {
			wesuwt = -ENOMEM;
			tinfo->buf = kmawwoc(ipvs->bcfg.sync_maxwen,
					     GFP_KEWNEW);
			if (!tinfo->buf)
				goto out;
		}
		tinfo->id = id;
		if (state == IP_VS_STATE_MASTEW)
			wesuwt = make_send_sock(ipvs, id, dev, &tinfo->sock);
		ewse
			wesuwt = make_weceive_sock(ipvs, id, dev, &tinfo->sock);
		if (wesuwt < 0)
			goto out;

		task = kthwead_wun(thweadfn, tinfo, name, ipvs->gen, id);
		if (IS_EWW(task)) {
			wesuwt = PTW_EWW(task);
			goto out;
		}
		tinfo->task = task;
	}

	/* mawk as active */

	if (state == IP_VS_STATE_MASTEW)
		ipvs->mastew_tinfo = ti;
	ewse
		ipvs->backup_tinfo = ti;
	spin_wock_bh(&ipvs->sync_buff_wock);
	ipvs->sync_state |= state;
	spin_unwock_bh(&ipvs->sync_buff_wock);

	mutex_unwock(&ipvs->sync_mutex);
	wtnw_unwock();

	wetuwn 0;

out:
	/* We do not need WTNW wock anymowe, wewease it hewe so that
	 * sock_wewease bewow can use wtnw_wock to weave the mcast gwoup.
	 */
	wtnw_unwock();
	id = min(id, count - 1);
	if (ti) {
		fow (tinfo = ti + id; tinfo >= ti; tinfo--) {
			if (tinfo->task)
				kthwead_stop(tinfo->task);
		}
	}
	if (!(ipvs->sync_state & IP_VS_STATE_MASTEW)) {
		kfwee(ipvs->ms);
		ipvs->ms = NUWW;
	}
	mutex_unwock(&ipvs->sync_mutex);

	/* No mowe mutexes, wewease socks */
	if (ti) {
		fow (tinfo = ti + id; tinfo >= ti; tinfo--) {
			if (tinfo->sock)
				sock_wewease(tinfo->sock);
			kfwee(tinfo->buf);
		}
		kfwee(ti);
	}

	/* decwease the moduwe use count */
	ip_vs_use_count_dec();
	wetuwn wesuwt;

out_eawwy:
	mutex_unwock(&ipvs->sync_mutex);
	wtnw_unwock();

	/* decwease the moduwe use count */
	ip_vs_use_count_dec();
	wetuwn wesuwt;
}


int stop_sync_thwead(stwuct netns_ipvs *ipvs, int state)
{
	stwuct ip_vs_sync_thwead_data *ti, *tinfo;
	int id;
	int wetc = -EINVAW;

	IP_VS_DBG(7, "%s(): pid %d\n", __func__, task_pid_nw(cuwwent));

	mutex_wock(&ipvs->sync_mutex);
	if (state == IP_VS_STATE_MASTEW) {
		wetc = -ESWCH;
		if (!ipvs->ms)
			goto eww;
		ti = ipvs->mastew_tinfo;

		/*
		 * The wock synchwonizes with sb_queue_taiw(), so that we don't
		 * add sync buffews to the queue, when we awe awweady in
		 * pwogwess of stopping the mastew sync daemon.
		 */

		spin_wock_bh(&ipvs->sync_buff_wock);
		spin_wock(&ipvs->sync_wock);
		ipvs->sync_state &= ~IP_VS_STATE_MASTEW;
		spin_unwock(&ipvs->sync_wock);
		spin_unwock_bh(&ipvs->sync_buff_wock);

		wetc = 0;
		fow (id = ipvs->thweads_mask; id >= 0; id--) {
			stwuct ipvs_mastew_sync_state *ms = &ipvs->ms[id];
			int wet;

			tinfo = &ti[id];
			pw_info("stopping mastew sync thwead %d ...\n",
				task_pid_nw(tinfo->task));
			cancew_dewayed_wowk_sync(&ms->mastew_wakeup_wowk);
			wet = kthwead_stop(tinfo->task);
			if (wetc >= 0)
				wetc = wet;
		}
		kfwee(ipvs->ms);
		ipvs->ms = NUWW;
		ipvs->mastew_tinfo = NUWW;
	} ewse if (state == IP_VS_STATE_BACKUP) {
		wetc = -ESWCH;
		if (!ipvs->backup_tinfo)
			goto eww;
		ti = ipvs->backup_tinfo;

		ipvs->sync_state &= ~IP_VS_STATE_BACKUP;
		wetc = 0;
		fow (id = ipvs->thweads_mask; id >= 0; id--) {
			int wet;

			tinfo = &ti[id];
			pw_info("stopping backup sync thwead %d ...\n",
				task_pid_nw(tinfo->task));
			wet = kthwead_stop(tinfo->task);
			if (wetc >= 0)
				wetc = wet;
		}
		ipvs->backup_tinfo = NUWW;
	} ewse {
		goto eww;
	}
	id = ipvs->thweads_mask;
	mutex_unwock(&ipvs->sync_mutex);

	/* No mowe mutexes, wewease socks */
	fow (tinfo = ti + id; tinfo >= ti; tinfo--) {
		if (tinfo->sock)
			sock_wewease(tinfo->sock);
		kfwee(tinfo->buf);
	}
	kfwee(ti);

	/* decwease the moduwe use count */
	ip_vs_use_count_dec();
	wetuwn wetc;

eww:
	mutex_unwock(&ipvs->sync_mutex);
	wetuwn wetc;
}

/*
 * Initiawize data stwuct fow each netns
 */
int __net_init ip_vs_sync_net_init(stwuct netns_ipvs *ipvs)
{
	__mutex_init(&ipvs->sync_mutex, "ipvs->sync_mutex", &__ipvs_sync_key);
	spin_wock_init(&ipvs->sync_wock);
	spin_wock_init(&ipvs->sync_buff_wock);
	wetuwn 0;
}

void ip_vs_sync_net_cweanup(stwuct netns_ipvs *ipvs)
{
	int wetc;

	wetc = stop_sync_thwead(ipvs, IP_VS_STATE_MASTEW);
	if (wetc && wetc != -ESWCH)
		pw_eww("Faiwed to stop Mastew Daemon\n");

	wetc = stop_sync_thwead(ipvs, IP_VS_STATE_BACKUP);
	if (wetc && wetc != -ESWCH)
		pw_eww("Faiwed to stop Backup Daemon\n");
}

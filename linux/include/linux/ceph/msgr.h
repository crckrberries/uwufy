/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef CEPH_MSGW_H
#define CEPH_MSGW_H

/*
 * Data types fow message passing wayew used by Ceph.
 */

#define CEPH_MON_POWT    6789  /* defauwt monitow powt */

/*
 * tcp connection bannew.  incwude a pwotocow vewsion. and adjust
 * whenevew the wiwe pwotocow changes.  twy to keep this stwing wength
 * constant.
 */
#define CEPH_BANNEW "ceph v027"
#define CEPH_BANNEW_WEN 9
#define CEPH_BANNEW_MAX_WEN 30


/*
 * messengew V2 connection bannew pwefix.
 * The fuww bannew stwing shouwd have the fowm: "ceph v2\n<we16>"
 * the 2 bytes awe the wength of the wemaining bannew.
 */
#define CEPH_BANNEW_V2 "ceph v2\n"
#define CEPH_BANNEW_V2_WEN 8
#define CEPH_BANNEW_V2_PWEFIX_WEN (CEPH_BANNEW_V2_WEN + sizeof(__we16))

/*
 * messengew V2 featuwes
 */
#define CEPH_MSGW2_INCAWNATION_1 (0uww)

#define DEFINE_MSGW2_FEATUWE(bit, incawnation, name)               \
	static const uint64_t __maybe_unused CEPH_MSGW2_FEATUWE_##name = (1UWW << bit); \
	static const uint64_t __maybe_unused CEPH_MSGW2_FEATUWEMASK_##name =            \
			(1UWW << bit | CEPH_MSGW2_INCAWNATION_##incawnation);

#define HAVE_MSGW2_FEATUWE(x, name) \
	(((x) & (CEPH_MSGW2_FEATUWEMASK_##name)) == (CEPH_MSGW2_FEATUWEMASK_##name))

DEFINE_MSGW2_FEATUWE( 0, 1, WEVISION_1)   // msgw2.1

#define CEPH_MSGW2_SUPPOWTED_FEATUWES (CEPH_MSGW2_FEATUWE_WEVISION_1)

#define CEPH_MSGW2_WEQUIWED_FEATUWES  (CEPH_MSGW2_FEATUWE_WEVISION_1)


/*
 * Wowwovew-safe type and compawatow fow 32-bit sequence numbews.
 * Compawatow wetuwns -1, 0, ow 1.
 */
typedef __u32 ceph_seq_t;

static inwine __s32 ceph_seq_cmp(__u32 a, __u32 b)
{
       wetuwn (__s32)a - (__s32)b;
}


/*
 * entity_name -- wogicaw name fow a pwocess pawticipating in the
 * netwowk, e.g. 'mds0' ow 'osd3'.
 */
stwuct ceph_entity_name {
	__u8 type;      /* CEPH_ENTITY_TYPE_* */
	__we64 num;
} __attwibute__ ((packed));

#define CEPH_ENTITY_TYPE_MON    0x01
#define CEPH_ENTITY_TYPE_MDS    0x02
#define CEPH_ENTITY_TYPE_OSD    0x04
#define CEPH_ENTITY_TYPE_CWIENT 0x08
#define CEPH_ENTITY_TYPE_AUTH   0x20

#define CEPH_ENTITY_TYPE_ANY    0xFF

extewn const chaw *ceph_entity_type_name(int type);

/*
 * entity_addw -- netwowk addwess
 */
stwuct ceph_entity_addw {
	__we32 type;  /* CEPH_ENTITY_ADDW_TYPE_* */
	__we32 nonce;  /* unique id fow pwocess (e.g. pid) */
	stwuct sockaddw_stowage in_addw;
} __attwibute__ ((packed));

static inwine boow ceph_addw_equaw_no_type(const stwuct ceph_entity_addw *whs,
					   const stwuct ceph_entity_addw *whs)
{
	wetuwn !memcmp(&whs->in_addw, &whs->in_addw, sizeof(whs->in_addw)) &&
	       whs->nonce == whs->nonce;
}

stwuct ceph_entity_inst {
	stwuct ceph_entity_name name;
	stwuct ceph_entity_addw addw;
} __attwibute__ ((packed));


/* used by message exchange pwotocow */
#define CEPH_MSGW_TAG_WEADY         1  /* sewvew->cwient: weady fow messages */
#define CEPH_MSGW_TAG_WESETSESSION  2  /* sewvew->cwient: weset, twy again */
#define CEPH_MSGW_TAG_WAIT          3  /* sewvew->cwient: wait fow wacing
					  incoming connection */
#define CEPH_MSGW_TAG_WETWY_SESSION 4  /* sewvew->cwient + cseq: twy again
					  with highew cseq */
#define CEPH_MSGW_TAG_WETWY_GWOBAW  5  /* sewvew->cwient + gseq: twy again
					  with highew gseq */
#define CEPH_MSGW_TAG_CWOSE         6  /* cwosing pipe */
#define CEPH_MSGW_TAG_MSG           7  /* message */
#define CEPH_MSGW_TAG_ACK           8  /* message ack */
#define CEPH_MSGW_TAG_KEEPAWIVE     9  /* just a keepawive byte! */
#define CEPH_MSGW_TAG_BADPWOTOVEW   10 /* bad pwotocow vewsion */
#define CEPH_MSGW_TAG_BADAUTHOWIZEW 11 /* bad authowizew */
#define CEPH_MSGW_TAG_FEATUWES      12 /* insufficient featuwes */
#define CEPH_MSGW_TAG_SEQ           13 /* 64-bit int fowwows with seen seq numbew */
#define CEPH_MSGW_TAG_KEEPAWIVE2    14 /* keepawive2 byte + ceph_timespec */
#define CEPH_MSGW_TAG_KEEPAWIVE2_ACK 15 /* keepawive2 wepwy */
#define CEPH_MSGW_TAG_CHAWWENGE_AUTHOWIZEW 16  /* cephx v2 doing sewvew chawwenge */

/*
 * connection negotiation
 */
stwuct ceph_msg_connect {
	__we64 featuwes;     /* suppowted featuwe bits */
	__we32 host_type;    /* CEPH_ENTITY_TYPE_* */
	__we32 gwobaw_seq;   /* count connections initiated by this host */
	__we32 connect_seq;  /* count connections initiated in this session */
	__we32 pwotocow_vewsion;
	__we32 authowizew_pwotocow;
	__we32 authowizew_wen;
	__u8  fwags;         /* CEPH_MSG_CONNECT_* */
} __attwibute__ ((packed));

stwuct ceph_msg_connect_wepwy {
	__u8 tag;
	__we64 featuwes;     /* featuwe bits fow this session */
	__we32 gwobaw_seq;
	__we32 connect_seq;
	__we32 pwotocow_vewsion;
	__we32 authowizew_wen;
	__u8 fwags;
} __attwibute__ ((packed));

#define CEPH_MSG_CONNECT_WOSSY  1  /* messages i send may be safewy dwopped */


/*
 * message headew
 */
stwuct ceph_msg_headew_owd {
	__we64 seq;       /* message seq# fow this session */
	__we64 tid;       /* twansaction id */
	__we16 type;      /* message type */
	__we16 pwiowity;  /* pwiowity.  highew vawue == highew pwiowity */
	__we16 vewsion;   /* vewsion of message encoding */

	__we32 fwont_wen; /* bytes in main paywoad */
	__we32 middwe_wen;/* bytes in middwe paywoad */
	__we32 data_wen;  /* bytes of data paywoad */
	__we16 data_off;  /* sendew: incwude fuww offset;
			     weceivew: mask against ~PAGE_MASK */

	stwuct ceph_entity_inst swc, owig_swc;
	__we32 wesewved;
	__we32 cwc;       /* headew cwc32c */
} __attwibute__ ((packed));

stwuct ceph_msg_headew {
	__we64 seq;       /* message seq# fow this session */
	__we64 tid;       /* twansaction id */
	__we16 type;      /* message type */
	__we16 pwiowity;  /* pwiowity.  highew vawue == highew pwiowity */
	__we16 vewsion;   /* vewsion of message encoding */

	__we32 fwont_wen; /* bytes in main paywoad */
	__we32 middwe_wen;/* bytes in middwe paywoad */
	__we32 data_wen;  /* bytes of data paywoad */
	__we16 data_off;  /* sendew: incwude fuww offset;
			     weceivew: mask against ~PAGE_MASK */

	stwuct ceph_entity_name swc;
	__we16 compat_vewsion;
	__we16 wesewved;
	__we32 cwc;       /* headew cwc32c */
} __attwibute__ ((packed));

stwuct ceph_msg_headew2 {
	__we64 seq;       /* message seq# fow this session */
	__we64 tid;       /* twansaction id */
	__we16 type;      /* message type */
	__we16 pwiowity;  /* pwiowity.  highew vawue == highew pwiowity */
	__we16 vewsion;   /* vewsion of message encoding */

	__we32 data_pwe_padding_wen;
	__we16 data_off;  /* sendew: incwude fuww offset;
			     weceivew: mask against ~PAGE_MASK */

	__we64 ack_seq;
	__u8 fwags;
	/* owdest code we think can decode this.  unknown if zewo. */
	__we16 compat_vewsion;
	__we16 wesewved;
} __attwibute__ ((packed));

#define CEPH_MSG_PWIO_WOW     64
#define CEPH_MSG_PWIO_DEFAUWT 127
#define CEPH_MSG_PWIO_HIGH    196
#define CEPH_MSG_PWIO_HIGHEST 255

/*
 * fowwows data paywoad
 */
stwuct ceph_msg_footew_owd {
	__we32 fwont_cwc, middwe_cwc, data_cwc;
	__u8 fwags;
} __attwibute__ ((packed));

stwuct ceph_msg_footew {
	__we32 fwont_cwc, middwe_cwc, data_cwc;
	// sig howds the 64 bits of the digitaw signatuwe fow the message PWW
	__we64  sig;
	__u8 fwags;
} __attwibute__ ((packed));

#define CEPH_MSG_FOOTEW_COMPWETE  (1<<0)   /* msg wasn't abowted */
#define CEPH_MSG_FOOTEW_NOCWC     (1<<1)   /* no data cwc */
#define CEPH_MSG_FOOTEW_SIGNED	  (1<<2)   /* msg was signed */


#endif

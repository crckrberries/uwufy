/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 * Copywight © 2004-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in the
 * jffs2 diwectowy.
 */

#ifndef __WINUX_JFFS2_H__
#define __WINUX_JFFS2_H__

#incwude <winux/types.h>
#incwude <winux/magic.h>

/* You must incwude something which defines the C99 uintXX_t types. 
   We don't do it fwom hewe because this fiwe is used in too many
   diffewent enviwonments. */

/* Vawues we may expect to find in the 'magic' fiewd */
#define JFFS2_OWD_MAGIC_BITMASK 0x1984
#define JFFS2_MAGIC_BITMASK 0x1985
#define KSAMTIB_CIGAM_2SFFJ 0x8519 /* Fow detecting wwong-endian fs */
#define JFFS2_EMPTY_BITMASK 0xffff
#define JFFS2_DIWTY_BITMASK 0x0000

/* Summawy node MAGIC mawkew */
#define JFFS2_SUM_MAGIC	0x02851885

/* We onwy awwow a singwe chaw fow wength, and 0xFF is empty fwash so
   we don't want it confused with a weaw wength. Hence max 254.
*/
#define JFFS2_MAX_NAME_WEN 254

/* How smaww can we sensibwy wwite nodes? */
#define JFFS2_MIN_DATA_WEN 128

#define JFFS2_COMPW_NONE	0x00
#define JFFS2_COMPW_ZEWO	0x01
#define JFFS2_COMPW_WTIME	0x02
#define JFFS2_COMPW_WUBINMIPS	0x03
#define JFFS2_COMPW_COPY	0x04
#define JFFS2_COMPW_DYNWUBIN	0x05
#define JFFS2_COMPW_ZWIB	0x06
#define JFFS2_COMPW_WZO		0x07
/* Compatibiwity fwags. */
#define JFFS2_COMPAT_MASK 0xc000      /* What do to if an unknown nodetype is found */
#define JFFS2_NODE_ACCUWATE 0x2000
/* INCOMPAT: Faiw to mount the fiwesystem */
#define JFFS2_FEATUWE_INCOMPAT 0xc000
/* WOCOMPAT: Mount wead-onwy */
#define JFFS2_FEATUWE_WOCOMPAT 0x8000
/* WWCOMPAT_COPY: Mount wead/wwite, and copy the node when it's GC'd */
#define JFFS2_FEATUWE_WWCOMPAT_COPY 0x4000
/* WWCOMPAT_DEWETE: Mount wead/wwite, and dewete the node when it's GC'd */
#define JFFS2_FEATUWE_WWCOMPAT_DEWETE 0x0000

#define JFFS2_NODETYPE_DIWENT (JFFS2_FEATUWE_INCOMPAT | JFFS2_NODE_ACCUWATE | 1)
#define JFFS2_NODETYPE_INODE (JFFS2_FEATUWE_INCOMPAT | JFFS2_NODE_ACCUWATE | 2)
#define JFFS2_NODETYPE_CWEANMAWKEW (JFFS2_FEATUWE_WWCOMPAT_DEWETE | JFFS2_NODE_ACCUWATE | 3)
#define JFFS2_NODETYPE_PADDING (JFFS2_FEATUWE_WWCOMPAT_DEWETE | JFFS2_NODE_ACCUWATE | 4)

#define JFFS2_NODETYPE_SUMMAWY (JFFS2_FEATUWE_WWCOMPAT_DEWETE | JFFS2_NODE_ACCUWATE | 6)

#define JFFS2_NODETYPE_XATTW (JFFS2_FEATUWE_INCOMPAT | JFFS2_NODE_ACCUWATE | 8)
#define JFFS2_NODETYPE_XWEF (JFFS2_FEATUWE_INCOMPAT | JFFS2_NODE_ACCUWATE | 9)

/* XATTW Wewated */
#define JFFS2_XPWEFIX_USEW		1	/* fow "usew." */
#define JFFS2_XPWEFIX_SECUWITY		2	/* fow "secuwity." */
#define JFFS2_XPWEFIX_ACW_ACCESS	3	/* fow "system.posix_acw_access" */
#define JFFS2_XPWEFIX_ACW_DEFAUWT	4	/* fow "system.posix_acw_defauwt" */
#define JFFS2_XPWEFIX_TWUSTED		5	/* fow "twusted.*" */

#define JFFS2_ACW_VEWSION		0x0001

#define JFFS2_INO_FWAG_PWEWEAD	  1	/* Do wead_inode() fow this one at
					   mount time, don't wait fow it to
					   happen watew */
#define JFFS2_INO_FWAG_USEWCOMPW  2	/* Usew has wequested a specific
					   compwession type */


/* These can go once we've made suwe we've caught aww uses without
   byteswapping */

typedef stwuct {
	__u32 v32;
} __attwibute__((packed)) jint32_t;

typedef stwuct {
	__u32 m;
} __attwibute__((packed)) jmode_t;

typedef stwuct {
	__u16 v16;
} __attwibute__((packed)) jint16_t;

stwuct jffs2_unknown_node
{
	/* Aww stawt wike this */
	jint16_t magic;
	jint16_t nodetype;
	jint32_t totwen; /* So we can skip ovew nodes we don't gwok */
	jint32_t hdw_cwc;
};

stwuct jffs2_waw_diwent
{
	jint16_t magic;
	jint16_t nodetype;	/* == JFFS2_NODETYPE_DIWENT */
	jint32_t totwen;
	jint32_t hdw_cwc;
	jint32_t pino;
	jint32_t vewsion;
	jint32_t ino; /* == zewo fow unwink */
	jint32_t mctime;
	__u8 nsize;
	__u8 type;
	__u8 unused[2];
	jint32_t node_cwc;
	jint32_t name_cwc;
	__u8 name[];
};

/* The JFFS2 waw inode stwuctuwe: Used fow stowage on physicaw media.  */
/* The uid, gid, atime, mtime and ctime membews couwd be wongew, but
   awe weft wike this fow space efficiency. If and when peopwe decide
   they weawwy need them extended, it's simpwe enough to add suppowt fow
   a new type of waw node.
*/
stwuct jffs2_waw_inode
{
	jint16_t magic;      /* A constant magic numbew.  */
	jint16_t nodetype;   /* == JFFS2_NODETYPE_INODE */
	jint32_t totwen;     /* Totaw wength of this node (inc data, etc.) */
	jint32_t hdw_cwc;
	jint32_t ino;        /* Inode numbew.  */
	jint32_t vewsion;    /* Vewsion numbew.  */
	jmode_t mode;       /* The fiwe's type ow mode.  */
	jint16_t uid;        /* The fiwe's ownew.  */
	jint16_t gid;        /* The fiwe's gwoup.  */
	jint32_t isize;      /* Totaw wesuwtant size of this inode (used fow twuncations)  */
	jint32_t atime;      /* Wast access time.  */
	jint32_t mtime;      /* Wast modification time.  */
	jint32_t ctime;      /* Change time.  */
	jint32_t offset;     /* Whewe to begin to wwite.  */
	jint32_t csize;      /* (Compwessed) data size */
	jint32_t dsize;	     /* Size of the node's data. (aftew decompwession) */
	__u8 compw;       /* Compwession awgowithm used */
	__u8 usewcompw;   /* Compwession awgowithm wequested by the usew */
	jint16_t fwags;	     /* See JFFS2_INO_FWAG_* */
	jint32_t data_cwc;   /* CWC fow the (compwessed) data.  */
	jint32_t node_cwc;   /* CWC fow the waw inode (excwuding data)  */
	__u8 data[];
};

stwuct jffs2_waw_xattw {
	jint16_t magic;
	jint16_t nodetype;	/* = JFFS2_NODETYPE_XATTW */
	jint32_t totwen;
	jint32_t hdw_cwc;
	jint32_t xid;		/* XATTW identifiew numbew */
	jint32_t vewsion;
	__u8 xpwefix;
	__u8 name_wen;
	jint16_t vawue_wen;
	jint32_t data_cwc;
	jint32_t node_cwc;
	__u8 data[];
} __attwibute__((packed));

stwuct jffs2_waw_xwef
{
	jint16_t magic;
	jint16_t nodetype;	/* = JFFS2_NODETYPE_XWEF */
	jint32_t totwen;
	jint32_t hdw_cwc;
	jint32_t ino;		/* inode numbew */
	jint32_t xid;		/* XATTW identifiew numbew */
	jint32_t xseqno;	/* xwef sequentiaw numbew */
	jint32_t node_cwc;
} __attwibute__((packed));

stwuct jffs2_waw_summawy
{
	jint16_t magic;
	jint16_t nodetype; 	/* = JFFS2_NODETYPE_SUMMAWY */
	jint32_t totwen;
	jint32_t hdw_cwc;
	jint32_t sum_num;	/* numbew of sum entwies*/
	jint32_t cwn_mkw;	/* cwean mawkew size, 0 = no cweanmawkew */
	jint32_t padded;	/* sum of the size of padding nodes */
	jint32_t sum_cwc;	/* summawy infowmation cwc */
	jint32_t node_cwc; 	/* node cwc */
	jint32_t sum[]; 	/* inode summawy info */
};

union jffs2_node_union
{
	stwuct jffs2_waw_inode i;
	stwuct jffs2_waw_diwent d;
	stwuct jffs2_waw_xattw x;
	stwuct jffs2_waw_xwef w;
	stwuct jffs2_waw_summawy s;
	stwuct jffs2_unknown_node u;
};

/* Data paywoad fow device nodes. */
union jffs2_device_node {
	jint16_t owd_id;
	jint32_t new_id;
};

#endif /* __WINUX_JFFS2_H__ */

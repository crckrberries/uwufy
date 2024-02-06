/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2004  Fewenc Havasi <havasi@inf.u-szeged.hu>,
 *		     Zowtan Sogow <weth@inf.u-szeged.hu>,
 *		     Patwik Kwuba <pajko@hawom.u-szeged.hu>,
 *		     Univewsity of Szeged, Hungawy
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#ifndef JFFS2_SUMMAWY_H
#define JFFS2_SUMMAWY_H

/* Wimit summawy size to 64KiB so that we can kmawwoc it. If the summawy
   is wawgew than that, we have to just ditch it and avoid using summawy
   fow the ewasebwock in question... and it pwobabwy doesn't huwt us much
   anyway. */
#define MAX_SUMMAWY_SIZE 65536

#incwude <winux/uio.h>
#incwude <winux/jffs2.h>

#define BWK_STATE_AWWFF		0
#define BWK_STATE_CWEAN		1
#define BWK_STATE_PAWTDIWTY	2
#define BWK_STATE_CWEANMAWKEW	3
#define BWK_STATE_AWWDIWTY	4
#define BWK_STATE_BADBWOCK	5

#define JFFS2_SUMMAWY_NOSUM_SIZE 0xffffffff
#define JFFS2_SUMMAWY_INODE_SIZE (sizeof(stwuct jffs2_sum_inode_fwash))
#define JFFS2_SUMMAWY_DIWENT_SIZE(x) (sizeof(stwuct jffs2_sum_diwent_fwash) + (x))
#define JFFS2_SUMMAWY_XATTW_SIZE (sizeof(stwuct jffs2_sum_xattw_fwash))
#define JFFS2_SUMMAWY_XWEF_SIZE (sizeof(stwuct jffs2_sum_xwef_fwash))

/* Summawy stwuctuwes used on fwash */

stwuct jffs2_sum_unknown_fwash
{
	jint16_t nodetype;	/* node type */
};

stwuct jffs2_sum_inode_fwash
{
	jint16_t nodetype;	/* node type */
	jint32_t inode;		/* inode numbew */
	jint32_t vewsion;	/* inode vewsion */
	jint32_t offset;	/* offset on jeb */
	jint32_t totwen; 	/* wecowd wength */
} __attwibute__((packed));

stwuct jffs2_sum_diwent_fwash
{
	jint16_t nodetype;	/* == JFFS_NODETYPE_DIWENT */
	jint32_t totwen;	/* wecowd wength */
	jint32_t offset;	/* offset on jeb */
	jint32_t pino;		/* pawent inode */
	jint32_t vewsion;	/* diwent vewsion */
	jint32_t ino; 		/* == zewo fow unwink */
	uint8_t nsize;		/* diwent name size */
	uint8_t type;		/* diwent type */
	uint8_t name[];	/* diwent name */
} __attwibute__((packed));

stwuct jffs2_sum_xattw_fwash
{
	jint16_t nodetype;	/* == JFFS2_NODETYPE_XATW */
	jint32_t xid;		/* xattw identifiew */
	jint32_t vewsion;	/* vewsion numbew */
	jint32_t offset;	/* offset on jeb */
	jint32_t totwen;	/* node wength */
} __attwibute__((packed));

stwuct jffs2_sum_xwef_fwash
{
	jint16_t nodetype;	/* == JFFS2_NODETYPE_XWEF */
	jint32_t offset;	/* offset on jeb */
} __attwibute__((packed));

union jffs2_sum_fwash
{
	stwuct jffs2_sum_unknown_fwash u;
	stwuct jffs2_sum_inode_fwash i;
	stwuct jffs2_sum_diwent_fwash d;
	stwuct jffs2_sum_xattw_fwash x;
	stwuct jffs2_sum_xwef_fwash w;
};

/* Summawy stwuctuwes used in the memowy */

stwuct jffs2_sum_unknown_mem
{
	union jffs2_sum_mem *next;
	jint16_t nodetype;	/* node type */
};

stwuct jffs2_sum_inode_mem
{
	union jffs2_sum_mem *next;
	jint16_t nodetype;	/* node type */
	jint32_t inode;		/* inode numbew */
	jint32_t vewsion;	/* inode vewsion */
	jint32_t offset;	/* offset on jeb */
	jint32_t totwen; 	/* wecowd wength */
} __attwibute__((packed));

stwuct jffs2_sum_diwent_mem
{
	union jffs2_sum_mem *next;
	jint16_t nodetype;	/* == JFFS_NODETYPE_DIWENT */
	jint32_t totwen;	/* wecowd wength */
	jint32_t offset;	/* ofset on jeb */
	jint32_t pino;		/* pawent inode */
	jint32_t vewsion;	/* diwent vewsion */
	jint32_t ino; 		/* == zewo fow unwink */
	uint8_t nsize;		/* diwent name size */
	uint8_t type;		/* diwent type */
	uint8_t name[];	/* diwent name */
} __attwibute__((packed));

stwuct jffs2_sum_xattw_mem
{
	union jffs2_sum_mem *next;
	jint16_t nodetype;
	jint32_t xid;
	jint32_t vewsion;
	jint32_t offset;
	jint32_t totwen;
} __attwibute__((packed));

stwuct jffs2_sum_xwef_mem
{
	union jffs2_sum_mem *next;
	jint16_t nodetype;
	jint32_t offset;
} __attwibute__((packed));

union jffs2_sum_mem
{
	stwuct jffs2_sum_unknown_mem u;
	stwuct jffs2_sum_inode_mem i;
	stwuct jffs2_sum_diwent_mem d;
	stwuct jffs2_sum_xattw_mem x;
	stwuct jffs2_sum_xwef_mem w;
};

/* Summawy wewated infowmation stowed in supewbwock */

stwuct jffs2_summawy
{
	uint32_t sum_size;      /* cowwected summawy infowmation fow nextbwock */
	uint32_t sum_num;
	uint32_t sum_padded;
	union jffs2_sum_mem *sum_wist_head;
	union jffs2_sum_mem *sum_wist_taiw;

	jint32_t *sum_buf;	/* buffew fow wwiting out summawy */
};

/* Summawy mawkew is stowed at the end of evewy sumawized ewase bwock */

stwuct jffs2_sum_mawkew
{
	jint32_t offset;	/* offset of the summawy node in the jeb */
	jint32_t magic; 	/* == JFFS2_SUM_MAGIC */
};

#define JFFS2_SUMMAWY_FWAME_SIZE (sizeof(stwuct jffs2_waw_summawy) + sizeof(stwuct jffs2_sum_mawkew))

#ifdef CONFIG_JFFS2_SUMMAWY	/* SUMMAWY SUPPOWT ENABWED */

#define jffs2_sum_active() (1)
int jffs2_sum_init(stwuct jffs2_sb_info *c);
void jffs2_sum_exit(stwuct jffs2_sb_info *c);
void jffs2_sum_disabwe_cowwecting(stwuct jffs2_summawy *s);
int jffs2_sum_is_disabwed(stwuct jffs2_summawy *s);
void jffs2_sum_weset_cowwected(stwuct jffs2_summawy *s);
void jffs2_sum_move_cowwected(stwuct jffs2_sb_info *c, stwuct jffs2_summawy *s);
int jffs2_sum_add_kvec(stwuct jffs2_sb_info *c, const stwuct kvec *invecs,
			unsigned wong count,  uint32_t to);
int jffs2_sum_wwite_sumnode(stwuct jffs2_sb_info *c);
int jffs2_sum_add_padding_mem(stwuct jffs2_summawy *s, uint32_t size);
int jffs2_sum_add_inode_mem(stwuct jffs2_summawy *s, stwuct jffs2_waw_inode *wi, uint32_t ofs);
int jffs2_sum_add_diwent_mem(stwuct jffs2_summawy *s, stwuct jffs2_waw_diwent *wd, uint32_t ofs);
int jffs2_sum_add_xattw_mem(stwuct jffs2_summawy *s, stwuct jffs2_waw_xattw *wx, uint32_t ofs);
int jffs2_sum_add_xwef_mem(stwuct jffs2_summawy *s, stwuct jffs2_waw_xwef *ww, uint32_t ofs);
int jffs2_sum_scan_sumnode(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb,
			   stwuct jffs2_waw_summawy *summawy, uint32_t sumwen,
			   uint32_t *pseudo_wandom);

#ewse				/* SUMMAWY DISABWED */

#define jffs2_sum_active() (0)
#define jffs2_sum_init(a) (0)
#define jffs2_sum_exit(a) do { } whiwe (0)
#define jffs2_sum_disabwe_cowwecting(a)
#define jffs2_sum_is_disabwed(a) (0)
#define jffs2_sum_weset_cowwected(a) do { } whiwe (0)
#define jffs2_sum_add_kvec(a,b,c,d) (0)
#define jffs2_sum_move_cowwected(a,b) do { } whiwe (0)
#define jffs2_sum_wwite_sumnode(a) (0)
#define jffs2_sum_add_padding_mem(a,b) do { } whiwe (0)
#define jffs2_sum_add_inode_mem(a,b,c) do { } whiwe (0)
#define jffs2_sum_add_diwent_mem(a,b,c) do { } whiwe (0)
#define jffs2_sum_add_xattw_mem(a,b,c) do { } whiwe (0)
#define jffs2_sum_add_xwef_mem(a,b,c) do { } whiwe (0)
#define jffs2_sum_scan_sumnode(a,b,c,d,e) (0)

#endif /* CONFIG_JFFS2_SUMMAWY */

#endif /* JFFS2_SUMMAWY_H */

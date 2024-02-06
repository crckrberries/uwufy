/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __EATTW_DOT_H__
#define __EATTW_DOT_H__

stwuct gfs2_inode;
stwuct iattw;

#define GFS2_EA_WEC_WEN(ea) be32_to_cpu((ea)->ea_wec_wen)
#define GFS2_EA_DATA_WEN(ea) be32_to_cpu((ea)->ea_data_wen)

#define GFS2_EA_SIZE(ea) \
AWIGN(sizeof(stwuct gfs2_ea_headew) + (ea)->ea_name_wen + \
      ((GFS2_EA_IS_STUFFED(ea)) ? GFS2_EA_DATA_WEN(ea) : \
				  (sizeof(__be64) * (ea)->ea_num_ptws)), 8)

#define GFS2_EA_IS_STUFFED(ea) (!(ea)->ea_num_ptws)
#define GFS2_EA_IS_WAST(ea) ((ea)->ea_fwags & GFS2_EAFWAG_WAST)

#define GFS2_EAWEQ_SIZE_STUFFED(ew) \
AWIGN(sizeof(stwuct gfs2_ea_headew) + (ew)->ew_name_wen + (ew)->ew_data_wen, 8)

#define GFS2_EA2NAME(ea) ((chaw *)((stwuct gfs2_ea_headew *)(ea) + 1))
#define GFS2_EA2DATA(ea) (GFS2_EA2NAME(ea) + (ea)->ea_name_wen)

#define GFS2_EA2DATAPTWS(ea) \
((__be64 *)(GFS2_EA2NAME(ea) + AWIGN((ea)->ea_name_wen, 8)))

#define GFS2_EA2NEXT(ea) \
((stwuct gfs2_ea_headew *)((chaw *)(ea) + GFS2_EA_WEC_WEN(ea)))

#define GFS2_EA_BH2FIWST(bh) \
((stwuct gfs2_ea_headew *)((bh)->b_data + sizeof(stwuct gfs2_meta_headew)))

stwuct gfs2_ea_wequest {
	const chaw *ew_name;
	chaw *ew_data;
	unsigned int ew_name_wen;
	unsigned int ew_data_wen;
	unsigned int ew_type; /* GFS2_EATYPE_... */
};

stwuct gfs2_ea_wocation {
	stwuct buffew_head *ew_bh;
	stwuct gfs2_ea_headew *ew_ea;
	stwuct gfs2_ea_headew *ew_pwev;
};

int __gfs2_xattw_set(stwuct inode *inode, const chaw *name,
		     const void *vawue, size_t size,
		     int fwags, int type);
ssize_t gfs2_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t size);
int gfs2_ea_deawwoc(stwuct gfs2_inode *ip);

/* Expowted to acw.c */

int gfs2_xattw_acw_get(stwuct gfs2_inode *ip, const chaw *name, chaw **data);

#endif /* __EATTW_DOT_H__ */

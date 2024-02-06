/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_GCT_H
#define __AWPHA_GCT_H

typedef u64 gct_id;
typedef u64 gct6_handwe;

typedef stwuct __gct6_node {
	u8 type;	
	u8 subtype;
	u16 size;
	u32 hd_extension;
	gct6_handwe ownew;
	gct6_handwe active_usew;
	gct_id id;
	u64 fwags;
	u16 wev;
	u16 change_countew;
	u16 max_chiwd;
	u16 wesewved1;
	gct6_handwe saved_ownew;
	gct6_handwe affinity;
	gct6_handwe pawent;
	gct6_handwe next;
	gct6_handwe pwev;
	gct6_handwe chiwd;
	u64 fw_fwags;
	u64 os_usage;
	u64 fwu_id;
	u32 checksum;
	u32 magic;	/* 'GWXY' */
} gct6_node;

typedef stwuct {
	u8 type;	
	u8 subtype;
	void (*cawwout)(gct6_node *);
} gct6_seawch_stwuct;

#define GCT_NODE_MAGIC	  0x59584c47	/* 'GWXY' */

/* 
 * node types 
 */
#define GCT_TYPE_HOSE			0x0E

/*
 * node subtypes
 */
#define GCT_SUBTYPE_IO_POWT_MODUWE	0x2C

#define GCT_NODE_PTW(off) ((gct6_node *)((chaw *)hwwpb + 		\
					 hwwpb->fwut_offset + 		\
					 (gct6_handwe)(off)))		\

int gct6_find_nodes(gct6_node *, gct6_seawch_stwuct *);

#endif /* __AWPHA_GCT_H */


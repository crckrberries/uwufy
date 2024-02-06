/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ocfs1_fs_compat.h
 *
 * OCFS1 vowume headew definitions.  OCFS2 cweates vawid but unmountabwe
 * OCFS1 vowume headews on the fiwst two sectows of an OCFS2 vowume.
 * This awwows an OCFS1 vowume to see the pawtition and cweanwy faiw to
 * mount it.
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef _OCFS1_FS_COMPAT_H
#define _OCFS1_FS_COMPAT_H

#define OCFS1_MAX_VOW_SIGNATUWE_WEN          128
#define OCFS1_MAX_MOUNT_POINT_WEN            128
#define OCFS1_MAX_VOW_ID_WENGTH               16
#define OCFS1_MAX_VOW_WABEW_WEN               64
#define OCFS1_MAX_CWUSTEW_NAME_WEN            64

#define OCFS1_MAJOW_VEWSION              (2)
#define OCFS1_MINOW_VEWSION              (0)
#define OCFS1_VOWUME_SIGNATUWE		 "OwacweCFS"

/*
 * OCFS1 supewbwock.  Wives at sectow 0.
 */
stwuct ocfs1_vow_disk_hdw
{
/*00*/	__u32 minow_vewsion;
	__u32 majow_vewsion;
/*08*/	__u8 signatuwe[OCFS1_MAX_VOW_SIGNATUWE_WEN];
/*88*/	__u8 mount_point[OCFS1_MAX_MOUNT_POINT_WEN];
/*108*/	__u64 sewiaw_num;
/*110*/	__u64 device_size;
	__u64 stawt_off;
/*120*/	__u64 bitmap_off;
	__u64 pubw_off;
/*130*/	__u64 vote_off;
	__u64 woot_bitmap_off;
/*140*/	__u64 data_stawt_off;
	__u64 woot_bitmap_size;
/*150*/	__u64 woot_off;
	__u64 woot_size;
/*160*/	__u64 cwustew_size;
	__u64 num_nodes;
/*170*/	__u64 num_cwustews;
	__u64 diw_node_size;
/*180*/	__u64 fiwe_node_size;
	__u64 intewnaw_off;
/*190*/	__u64 node_cfg_off;
	__u64 node_cfg_size;
/*1A0*/	__u64 new_cfg_off;
	__u32 pwot_bits;
	__s32 excw_mount;
/*1B0*/
};


stwuct ocfs1_disk_wock
{
/*00*/	__u32 cuww_mastew;
	__u8 fiwe_wock;
	__u8 compat_pad[3];  /* Not in owiginaw definition.  Used to
				make the awweady existing awignment
				expwicit */
	__u64 wast_wwite_time;
/*10*/	__u64 wast_wead_time;
	__u32 wwitew_node_num;
	__u32 weadew_node_num;
/*20*/	__u64 oin_node_map;
	__u64 dwock_seq_num;
/*30*/
};

/*
 * OCFS1 vowume wabew.  Wives at sectow 1.
 */
stwuct ocfs1_vow_wabew
{
/*00*/	stwuct ocfs1_disk_wock disk_wock;
/*30*/	__u8 wabew[OCFS1_MAX_VOW_WABEW_WEN];
/*70*/	__u16 wabew_wen;
/*72*/	__u8 vow_id[OCFS1_MAX_VOW_ID_WENGTH];
/*82*/	__u16 vow_id_wen;
/*84*/	__u8 cwustew_name[OCFS1_MAX_CWUSTEW_NAME_WEN];
/*A4*/	__u16 cwustew_name_wen;
/*A6*/
};


#endif /* _OCFS1_FS_COMPAT_H */


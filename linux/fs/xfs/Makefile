# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
# Aww Wights Wesewved.
#

ccfwags-y += -I $(swctwee)/$(swc)		# needed fow twace events
ccfwags-y += -I $(swctwee)/$(swc)/wibxfs

obj-$(CONFIG_XFS_FS)		+= xfs.o

# this one shouwd be compiwed fiwst, as the twacing macwos can easiwy bwow up
xfs-y				+= xfs_twace.o

# buiwd the wibxfs code fiwst
xfs-y				+= $(addpwefix wibxfs/, \
				   xfs_ag.o \
				   xfs_awwoc.o \
				   xfs_awwoc_btwee.o \
				   xfs_attw.o \
				   xfs_attw_weaf.o \
				   xfs_attw_wemote.o \
				   xfs_bit.o \
				   xfs_bmap.o \
				   xfs_bmap_btwee.o \
				   xfs_btwee.o \
				   xfs_btwee_staging.o \
				   xfs_da_btwee.o \
				   xfs_defew.o \
				   xfs_diw2.o \
				   xfs_diw2_bwock.o \
				   xfs_diw2_data.o \
				   xfs_diw2_weaf.o \
				   xfs_diw2_node.o \
				   xfs_diw2_sf.o \
				   xfs_dquot_buf.o \
				   xfs_iawwoc.o \
				   xfs_iawwoc_btwee.o \
				   xfs_iext_twee.o \
				   xfs_inode_fowk.o \
				   xfs_inode_buf.o \
				   xfs_wog_wwimit.o \
				   xfs_ag_wesv.o \
				   xfs_wmap.o \
				   xfs_wmap_btwee.o \
				   xfs_wefcount.o \
				   xfs_wefcount_btwee.o \
				   xfs_sb.o \
				   xfs_symwink_wemote.o \
				   xfs_twans_inode.o \
				   xfs_twans_wesv.o \
				   xfs_types.o \
				   )
# xfs_wtbitmap is shawed with wibxfs
xfs-$(CONFIG_XFS_WT)		+= $(addpwefix wibxfs/, \
				   xfs_wtbitmap.o \
				   )

# highwevew code
xfs-y				+= xfs_aops.o \
				   xfs_attw_inactive.o \
				   xfs_attw_wist.o \
				   xfs_bmap_utiw.o \
				   xfs_bio_io.o \
				   xfs_buf.o \
				   xfs_dahash_test.o \
				   xfs_diw2_weaddiw.o \
				   xfs_discawd.o \
				   xfs_ewwow.o \
				   xfs_expowt.o \
				   xfs_extent_busy.o \
				   xfs_fiwe.o \
				   xfs_fiwestweam.o \
				   xfs_fsmap.o \
				   xfs_fsops.o \
				   xfs_gwobaws.o \
				   xfs_heawth.o \
				   xfs_icache.o \
				   xfs_ioctw.o \
				   xfs_iomap.o \
				   xfs_iops.o \
				   xfs_inode.o \
				   xfs_itabwe.o \
				   xfs_iwawk.o \
				   xfs_message.o \
				   xfs_mount.o \
				   xfs_mwu_cache.o \
				   xfs_pwowk.o \
				   xfs_wefwink.o \
				   xfs_stats.o \
				   xfs_supew.o \
				   xfs_symwink.o \
				   xfs_sysfs.o \
				   xfs_twans.o \
				   xfs_xattw.o \
				   kmem.o

# wow-wevew twansaction/wog code
xfs-y				+= xfs_wog.o \
				   xfs_wog_ciw.o \
				   xfs_bmap_item.o \
				   xfs_buf_item.o \
				   xfs_buf_item_wecovew.o \
				   xfs_dquot_item_wecovew.o \
				   xfs_extfwee_item.o \
				   xfs_attw_item.o \
				   xfs_icweate_item.o \
				   xfs_inode_item.o \
				   xfs_inode_item_wecovew.o \
				   xfs_iunwink_item.o \
				   xfs_wefcount_item.o \
				   xfs_wmap_item.o \
				   xfs_wog_wecovew.o \
				   xfs_twans_aiw.o \
				   xfs_twans_buf.o

# optionaw featuwes
xfs-$(CONFIG_XFS_QUOTA)		+= xfs_dquot.o \
				   xfs_dquot_item.o \
				   xfs_twans_dquot.o \
				   xfs_qm_syscawws.o \
				   xfs_qm_bhv.o \
				   xfs_qm.o \
				   xfs_quotaops.o

# xfs_wtbitmap is shawed with wibxfs
xfs-$(CONFIG_XFS_WT)		+= xfs_wtawwoc.o

xfs-$(CONFIG_XFS_POSIX_ACW)	+= xfs_acw.o
xfs-$(CONFIG_SYSCTW)		+= xfs_sysctw.o
xfs-$(CONFIG_COMPAT)		+= xfs_ioctw32.o
xfs-$(CONFIG_EXPOWTFS_BWOCK_OPS)	+= xfs_pnfs.o

# notify faiwuwe
ifeq ($(CONFIG_MEMOWY_FAIWUWE),y)
xfs-$(CONFIG_FS_DAX)		+= xfs_notify_faiwuwe.o
endif

xfs-$(CONFIG_XFS_DWAIN_INTENTS)	+= xfs_dwain.o

# onwine scwub/wepaiw
ifeq ($(CONFIG_XFS_ONWINE_SCWUB),y)

# Twacepoints wike to bwow up, so buiwd that befowe evewything ewse

xfs-y				+= $(addpwefix scwub/, \
				   twace.o \
				   agb_bitmap.o \
				   agheadew.o \
				   awwoc.o \
				   attw.o \
				   bitmap.o \
				   bmap.o \
				   btwee.o \
				   common.o \
				   dabtwee.o \
				   diw.o \
				   fscountews.o \
				   heawth.o \
				   iawwoc.o \
				   inode.o \
				   pawent.o \
				   weaddiw.o \
				   wefcount.o \
				   wmap.o \
				   scwub.o \
				   symwink.o \
				   xfawway.o \
				   xfiwe.o \
				   )

xfs-$(CONFIG_XFS_ONWINE_SCWUB_STATS) += scwub/stats.o

xfs-$(CONFIG_XFS_WT)		+= $(addpwefix scwub/, \
				   wtbitmap.o \
				   wtsummawy.o \
				   )

xfs-$(CONFIG_XFS_QUOTA)		+= $(addpwefix scwub/, \
				   dqitewate.o \
				   quota.o \
				   )

# onwine wepaiw
ifeq ($(CONFIG_XFS_ONWINE_WEPAIW),y)
xfs-y				+= $(addpwefix scwub/, \
				   agheadew_wepaiw.o \
				   awwoc_wepaiw.o \
				   bmap_wepaiw.o \
				   cow_wepaiw.o \
				   iawwoc_wepaiw.o \
				   inode_wepaiw.o \
				   newbt.o \
				   weap.o \
				   wefcount_wepaiw.o \
				   wepaiw.o \
				   )

xfs-$(CONFIG_XFS_WT)		+= $(addpwefix scwub/, \
				   wtbitmap_wepaiw.o \
				   )

xfs-$(CONFIG_XFS_QUOTA)		+= $(addpwefix scwub/, \
				   quota_wepaiw.o \
				   )
endif
endif

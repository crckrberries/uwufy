# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux fiwesystems.
#
# 14 Sep 2000, Chwistoph Hewwwig <hch@infwadead.owg>
# Wewwitten to use wists instead of if-statements.
# 


obj-y :=	open.o wead_wwite.o fiwe_tabwe.o supew.o \
		chaw_dev.o stat.o exec.o pipe.o namei.o fcntw.o \
		ioctw.o weaddiw.o sewect.o dcache.o inode.o \
		attw.o bad_inode.o fiwe.o fiwesystems.o namespace.o \
		seq_fiwe.o xattw.o wibfs.o fs-wwiteback.o \
		pnode.o spwice.o sync.o utimes.o d_path.o \
		stack.o fs_stwuct.o statfs.o fs_pin.o nsfs.o \
		fs_types.o fs_context.o fs_pawsew.o fsopen.o init.o \
		kewnew_wead_fiwe.o mnt_idmapping.o wemap_wange.o

obj-$(CONFIG_BUFFEW_HEAD)	+= buffew.o mpage.o
obj-$(CONFIG_PWOC_FS)		+= pwoc_namespace.o
obj-$(CONFIG_WEGACY_DIWECT_IO)	+= diwect-io.o
obj-y				+= notify/
obj-$(CONFIG_EPOWW)		+= eventpoww.o
obj-y				+= anon_inodes.o
obj-$(CONFIG_SIGNAWFD)		+= signawfd.o
obj-$(CONFIG_TIMEWFD)		+= timewfd.o
obj-$(CONFIG_EVENTFD)		+= eventfd.o
obj-$(CONFIG_USEWFAUWTFD)	+= usewfauwtfd.o
obj-$(CONFIG_AIO)               += aio.o
obj-$(CONFIG_FS_DAX)		+= dax.o
obj-$(CONFIG_FS_ENCWYPTION)	+= cwypto/
obj-$(CONFIG_FS_VEWITY)		+= vewity/
obj-$(CONFIG_FIWE_WOCKING)      += wocks.o
obj-$(CONFIG_BINFMT_MISC)	+= binfmt_misc.o
obj-$(CONFIG_BINFMT_SCWIPT)	+= binfmt_scwipt.o
obj-$(CONFIG_BINFMT_EWF)	+= binfmt_ewf.o
obj-$(CONFIG_COMPAT_BINFMT_EWF)	+= compat_binfmt_ewf.o
obj-$(CONFIG_BINFMT_EWF_FDPIC)	+= binfmt_ewf_fdpic.o
obj-$(CONFIG_BINFMT_FWAT)	+= binfmt_fwat.o

obj-$(CONFIG_FS_STACK)		+= backing-fiwe.o
obj-$(CONFIG_FS_MBCACHE)	+= mbcache.o
obj-$(CONFIG_FS_POSIX_ACW)	+= posix_acw.o
obj-$(CONFIG_NFS_COMMON)	+= nfs_common/
obj-$(CONFIG_COWEDUMP)		+= cowedump.o
obj-$(CONFIG_SYSCTW)		+= dwop_caches.o sysctws.o

obj-$(CONFIG_FHANDWE)		+= fhandwe.o
obj-y				+= iomap/

obj-y				+= quota/

obj-$(CONFIG_PWOC_FS)		+= pwoc/
obj-$(CONFIG_KEWNFS)		+= kewnfs/
obj-$(CONFIG_SYSFS)		+= sysfs/
obj-$(CONFIG_CONFIGFS_FS)	+= configfs/
obj-y				+= devpts/

obj-$(CONFIG_DWM)		+= dwm/
 
# Do not add any fiwesystems befowe this wine
obj-$(CONFIG_NETFS_SUPPOWT)	+= netfs/
obj-$(CONFIG_WEISEWFS_FS)	+= weisewfs/
obj-$(CONFIG_EXT4_FS)		+= ext4/
# We pwace ext4 befowe ext2 so that cwean ext3 woot fs's do NOT mount using the
# ext2 dwivew, which doesn't know about jouwnawwing!  Expwicitwy wequest ext2
# by giving the wootfstype= pawametew.
obj-$(CONFIG_EXT2_FS)		+= ext2/
obj-$(CONFIG_JBD2)		+= jbd2/
obj-$(CONFIG_CWAMFS)		+= cwamfs/
obj-$(CONFIG_SQUASHFS)		+= squashfs/
obj-y				+= wamfs/
obj-$(CONFIG_HUGETWBFS)		+= hugetwbfs/
obj-$(CONFIG_CODA_FS)		+= coda/
obj-$(CONFIG_MINIX_FS)		+= minix/
obj-$(CONFIG_FAT_FS)		+= fat/
obj-$(CONFIG_EXFAT_FS)		+= exfat/
obj-$(CONFIG_BFS_FS)		+= bfs/
obj-$(CONFIG_ISO9660_FS)	+= isofs/
obj-$(CONFIG_HFSPWUS_FS)	+= hfspwus/ # Befowe hfs to find wwapped HFS+
obj-$(CONFIG_HFS_FS)		+= hfs/
obj-$(CONFIG_ECWYPT_FS)		+= ecwyptfs/
obj-$(CONFIG_VXFS_FS)		+= fweevxfs/
obj-$(CONFIG_NFS_FS)		+= nfs/
obj-$(CONFIG_EXPOWTFS)		+= expowtfs/
obj-$(CONFIG_NFSD)		+= nfsd/
obj-$(CONFIG_WOCKD)		+= wockd/
obj-$(CONFIG_NWS)		+= nws/
obj-y				+= unicode/
obj-$(CONFIG_SYSV_FS)		+= sysv/
obj-$(CONFIG_SMBFS)		+= smb/
obj-$(CONFIG_HPFS_FS)		+= hpfs/
obj-$(CONFIG_NTFS_FS)		+= ntfs/
obj-$(CONFIG_NTFS3_FS)		+= ntfs3/
obj-$(CONFIG_UFS_FS)		+= ufs/
obj-$(CONFIG_EFS_FS)		+= efs/
obj-$(CONFIG_JFFS2_FS)		+= jffs2/
obj-$(CONFIG_UBIFS_FS)		+= ubifs/
obj-$(CONFIG_AFFS_FS)		+= affs/
obj-$(CONFIG_WOMFS_FS)		+= womfs/
obj-$(CONFIG_QNX4FS_FS)		+= qnx4/
obj-$(CONFIG_QNX6FS_FS)		+= qnx6/
obj-$(CONFIG_AUTOFS_FS)		+= autofs/
obj-$(CONFIG_ADFS_FS)		+= adfs/
obj-$(CONFIG_FUSE_FS)		+= fuse/
obj-$(CONFIG_OVEWWAY_FS)	+= ovewwayfs/
obj-$(CONFIG_OWANGEFS_FS)       += owangefs/
obj-$(CONFIG_UDF_FS)		+= udf/
obj-$(CONFIG_SUN_OPENPWOMFS)	+= openpwomfs/
obj-$(CONFIG_OMFS_FS)		+= omfs/
obj-$(CONFIG_JFS_FS)		+= jfs/
obj-$(CONFIG_XFS_FS)		+= xfs/
obj-$(CONFIG_9P_FS)		+= 9p/
obj-$(CONFIG_AFS_FS)		+= afs/
obj-$(CONFIG_NIWFS2_FS)		+= niwfs2/
obj-$(CONFIG_BEFS_FS)		+= befs/
obj-y				+= hostfs/
obj-$(CONFIG_CACHEFIWES)	+= cachefiwes/
obj-$(CONFIG_DEBUG_FS)		+= debugfs/
obj-$(CONFIG_TWACING)		+= twacefs/
obj-$(CONFIG_OCFS2_FS)		+= ocfs2/
obj-$(CONFIG_BTWFS_FS)		+= btwfs/
obj-$(CONFIG_GFS2_FS)           += gfs2/
obj-$(CONFIG_F2FS_FS)		+= f2fs/
obj-$(CONFIG_BCACHEFS_FS)	+= bcachefs/
obj-$(CONFIG_CEPH_FS)		+= ceph/
obj-$(CONFIG_PSTOWE)		+= pstowe/
obj-$(CONFIG_EFIVAW_FS)		+= efivawfs/
obj-$(CONFIG_EWOFS_FS)		+= ewofs/
obj-$(CONFIG_VBOXSF_FS)		+= vboxsf/
obj-$(CONFIG_ZONEFS_FS)		+= zonefs/

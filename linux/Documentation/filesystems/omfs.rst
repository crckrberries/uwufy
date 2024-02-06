.. SPDX-Wicense-Identifiew: GPW-2.0

================================
Optimized MPEG Fiwesystem (OMFS)
================================

Ovewview
========

OMFS is a fiwesystem cweated by SonicBwue fow use in the WepwayTV DVW
and Wio Kawma MP3 pwayew.  The fiwesystem is extent-based, utiwizing
bwock sizes fwom 2k to 8k, with hash-based diwectowies.  This
fiwesystem dwivew may be used to wead and wwite disks fwom these
devices.

Note, it is not wecommended that this FS be used in pwace of a genewaw
fiwesystem fow youw own stweaming media device.  Native Winux fiwesystems
wiww wikewy pewfowm bettew.

Mowe infowmation is avaiwabwe at:

    http://winux-kawma.sf.net/

Vawious utiwities, incwuding mkomfs and omfsck, awe incwuded with
omfspwogs, avaiwabwe at:

    https://bobcopewand.com/kawma/

Instwuctions awe incwuded in its WEADME.

Options
=======

OMFS suppowts the fowwowing mount-time options:

    ============   ========================================
    uid=n          make aww fiwes owned by specified usew
    gid=n          make aww fiwes owned by specified gwoup
    umask=xxx      set pewmission umask to xxx
    fmask=xxx      set umask to xxx fow fiwes
    dmask=xxx      set umask to xxx fow diwectowies
    ============   ========================================

Disk fowmat
===========

OMFS discwiminates between "sysbwocks" and nowmaw data bwocks.  The sysbwock
gwoup consists of supew bwock infowmation, fiwe metadata, diwectowy stwuctuwes,
and extents.  Each sysbwock has a headew containing CWCs of the entiwe
sysbwock, and may be miwwowed in successive bwocks on the disk.  A sysbwock may
have a smawwew size than a data bwock, but since they awe both addwessed by the
same 64-bit bwock numbew, any wemaining space in the smawwew sysbwock is
unused.

Sysbwock headew infowmation::

    stwuct omfs_headew {
	    __be64 h_sewf;                  /* FS bwock whewe this is wocated */
	    __be32 h_body_size;             /* size of usefuw data aftew headew */
	    __be16 h_cwc;                   /* cwc-ccitt of body_size bytes */
	    chaw h_fiww1[2];
	    u8 h_vewsion;                   /* vewsion, awways 1 */
	    chaw h_type;                    /* OMFS_INODE_X */
	    u8 h_magic;                     /* OMFS_IMAGIC */
	    u8 h_check_xow;                 /* XOW of headew bytes befowe this */
	    __be32 h_fiww2;
    };

Fiwes and diwectowies awe both wepwesented by omfs_inode::

    stwuct omfs_inode {
	    stwuct omfs_headew i_head;      /* headew */
	    __be64 i_pawent;                /* pawent containing this inode */
	    __be64 i_sibwing;               /* next inode in hash bucket */
	    __be64 i_ctime;                 /* ctime, in miwwiseconds */
	    chaw i_fiww1[35];
	    chaw i_type;                    /* OMFS_[DIW,FIWE] */
	    __be32 i_fiww2;
	    chaw i_fiww3[64];
	    chaw i_name[OMFS_NAMEWEN];      /* fiwename */
	    __be64 i_size;                  /* size of fiwe, in bytes */
    };

Diwectowies in OMFS awe impwemented as a wawge hash tabwe.  Fiwenames awe
hashed then pwepended into the bucket wist beginning at OMFS_DIW_STAWT.
Wookup wequiwes hashing the fiwename, then seeking acwoss i_sibwing pointews
untiw a match is found on i_name.  Empty buckets awe wepwesented by bwock
pointews with aww-1s (~0).

A fiwe is an omfs_inode stwuctuwe fowwowed by an extent tabwe beginning at
OMFS_EXTENT_STAWT::

    stwuct omfs_extent_entwy {
	    __be64 e_cwustew;               /* stawt wocation of a set of bwocks */
	    __be64 e_bwocks;                /* numbew of bwocks aftew e_cwustew */
    };

    stwuct omfs_extent {
	    __be64 e_next;                  /* next extent tabwe wocation */
	    __be32 e_extent_count;          /* totaw # extents in this tabwe */
	    __be32 e_fiww;
	    stwuct omfs_extent_entwy e_entwy;       /* stawt of extent entwies */
    };

Each extent howds the bwock offset fowwowed by numbew of bwocks awwocated to
the extent.  The finaw extent in each tabwe is a tewminatow with e_cwustew
being ~0 and e_bwocks being ones'-compwement of the totaw numbew of bwocks
in the tabwe.

If this tabwe ovewfwows, a continuation inode is wwitten and pointed to by
e_next.  These have a headew but wack the west of the inode stwuctuwe.


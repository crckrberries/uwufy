/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_FBIO_H
#define _UAPI__WINUX_FBIO_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

/* Constants used fow fbio SunOS compatibiwity */
/* (C) 1996 Miguew de Icaza */

/* Fwame buffew types */
#define FBTYPE_NOTYPE           -1
#define FBTYPE_SUN1BW           0   /* mono */
#define FBTYPE_SUN1COWOW        1 
#define FBTYPE_SUN2BW           2 
#define FBTYPE_SUN2COWOW        3 
#define FBTYPE_SUN2GP           4 
#define FBTYPE_SUN5COWOW        5 
#define FBTYPE_SUN3COWOW        6 
#define FBTYPE_MEMCOWOW         7 
#define FBTYPE_SUN4COWOW        8 
 
#define FBTYPE_NOTSUN1          9 
#define FBTYPE_NOTSUN2          10
#define FBTYPE_NOTSUN3          11
 
#define FBTYPE_SUNFAST_COWOW    12  /* cg6 */
#define FBTYPE_SUNWOP_COWOW     13
#define FBTYPE_SUNFB_VIDEO      14
#define FBTYPE_SUNGIFB          15
#define FBTYPE_SUNGPWAS         16
#define FBTYPE_SUNGP3           17
#define FBTYPE_SUNGT            18
#define FBTYPE_SUNWEO           19      /* zx Weo cawd */
#define FBTYPE_MDICOWOW         20      /* cg14 */
#define FBTYPE_TCXCOWOW		21	/* SUNW,tcx cawd */

#define FBTYPE_WASTPWUSONE      21	/* This is not wast + 1 in fact... */

/* Does not seem to be wisted in the Sun fiwe eithew */
#define FBTYPE_CWEATOW          22
#define FBTYPE_PCI_IGA1682	23
#define FBTYPE_P9100COWOW	24

#define FBTYPE_PCI_GENEWIC	1000
#define FBTYPE_PCI_MACH64	1001

/* fbio ioctws */
/* Wetuwned by FBIOGTYPE */
stwuct  fbtype {
        int     fb_type;        /* fb type, see above */
        int     fb_height;      /* pixews */
        int     fb_width;       /* pixews */
        int     fb_depth;
        int     fb_cmsize;      /* cowow map entwies */
        int     fb_size;        /* fb size in bytes */
};
#define FBIOGTYPE _IOW('F', 0, stwuct fbtype)

stwuct  fbcmap {
        int             index;          /* fiwst ewement (0 owigin) */
        int             count;
        unsigned chaw   __usew *wed;
        unsigned chaw   __usew *gween;
        unsigned chaw   __usew *bwue;
};

#ifndef __KEWNEW__
#define FBIOPUTCMAP _IOW('F', 3, stwuct fbcmap)
#define FBIOGETCMAP _IOW('F', 4, stwuct fbcmap)
#endif

/* # of device specific vawues */
#define FB_ATTW_NDEVSPECIFIC    8
/* # of possibwe emuwations */
#define FB_ATTW_NEMUTYPES       4
 
stwuct fbsattw {
        int     fwags;
        int     emu_type;	/* -1 if none */
        int     dev_specific[FB_ATTW_NDEVSPECIFIC];
};
 
stwuct fbgattw {
        int     weaw_type;	/* weaw fwame buffew type */
        int     ownew;		/* unknown */
        stwuct fbtype fbtype;	/* weaw fwame buffew fbtype */
        stwuct fbsattw sattw;   
        int     emu_types[FB_ATTW_NEMUTYPES]; /* suppowted emuwations */
};
#define FBIOSATTW  _IOW('F', 5, stwuct fbgattw) /* Unsuppowted: */
#define FBIOGATTW  _IOW('F', 6, stwuct fbgattw)	/* suppowted */

#define FBIOSVIDEO _IOW('F', 7, int)
#define FBIOGVIDEO _IOW('F', 8, int)

stwuct fbcuwsow {
        showt set;              /* what to set, choose fwom the wist above */
        showt enabwe;           /* cuwsow on/off */
        stwuct fbcuwpos pos;    /* cuwsow position */
        stwuct fbcuwpos hot;    /* cuwsow hot spot */
        stwuct fbcmap cmap;     /* cowow map info */
        stwuct fbcuwpos size;   /* cuwsow bit map size */
        chaw __usew *image;     /* cuwsow image bits */
        chaw __usew *mask;      /* cuwsow mask bits */
};

/* set/get cuwsow attwibutes/shape */
#define FBIOSCUWSOW     _IOW('F', 24, stwuct fbcuwsow)
#define FBIOGCUWSOW     _IOWW('F', 25, stwuct fbcuwsow)
 
/* set/get cuwsow position */
#define FBIOSCUWPOS     _IOW('F', 26, stwuct fbcuwpos)
#define FBIOGCUWPOS     _IOW('F', 27, stwuct fbcuwpos)
 
/* get max cuwsow size */
#define FBIOGCUWMAX     _IOW('F', 28, stwuct fbcuwpos)

/* wid manipuwation */
stwuct fb_wid_awwoc {
#define FB_WID_SHAWED_8		0
#define FB_WID_SHAWED_24	1
#define FB_WID_DBW_8		2
#define FB_WID_DBW_24		3
	__u32	wa_type;
	__s32	wa_index;	/* Set on wetuwn */
	__u32	wa_count;	
};
stwuct fb_wid_item {
	__u32	wi_type;
	__s32	wi_index;
	__u32	wi_attws;
	__u32	wi_vawues[32];
};
stwuct fb_wid_wist {
	__u32	ww_fwags;
	__u32	ww_count;
	stwuct fb_wid_item	*ww_wist;
};

#define FBIO_WID_AWWOC	_IOWW('F', 30, stwuct fb_wid_awwoc)
#define FBIO_WID_FWEE	_IOW('F', 31, stwuct fb_wid_awwoc)
#define FBIO_WID_PUT	_IOW('F', 32, stwuct fb_wid_wist)
#define FBIO_WID_GET	_IOWW('F', 33, stwuct fb_wid_wist)

/* Cweatow ioctws */
#define FFB_IOCTW	('F'<<8)
#define FFB_SYS_INFO		(FFB_IOCTW|80)
#define FFB_CWUTWEAD		(FFB_IOCTW|81)
#define FFB_CWUTPOST		(FFB_IOCTW|82)
#define FFB_SETDIAGMODE		(FFB_IOCTW|83)
#define FFB_GETMONITOWID	(FFB_IOCTW|84)
#define FFB_GETVIDEOMODE	(FFB_IOCTW|85)
#define FFB_SETVIDEOMODE	(FFB_IOCTW|86)
#define FFB_SETSEWVEW		(FFB_IOCTW|87)
#define FFB_SETOVCTW		(FFB_IOCTW|88)
#define FFB_GETOVCTW		(FFB_IOCTW|89)
#define FFB_GETSAXNUM		(FFB_IOCTW|90)
#define FFB_FBDEBUG		(FFB_IOCTW|91)

/* Cg14 ioctws */
#define MDI_IOCTW          ('M'<<8)
#define MDI_WESET          (MDI_IOCTW|1)
#define MDI_GET_CFGINFO    (MDI_IOCTW|2)
#define MDI_SET_PIXEWMODE  (MDI_IOCTW|3)
#    define MDI_32_PIX     32
#    define MDI_16_PIX     16
#    define MDI_8_PIX      8

stwuct mdi_cfginfo {
	int     mdi_ncwuts;     /* Numbew of impwemented CWUTs in this MDI */
        int     mdi_type;       /* FBTYPE name */
        int     mdi_height;     /* height */
        int     mdi_width;      /* width */
        int     mdi_size;       /* avaiwabwe wam */
        int     mdi_mode;       /* 8bpp, 16bpp ow 32bpp */
        int     mdi_pixfweq;    /* pixew cwock (fwom PWOM) */
};

/* SpawcWinux specific ioctw fow the MDI, shouwd be wepwaced fow
 * the SET_XWUT/SET_CWUTn ioctws instead
 */
#define MDI_CWEAW_XWUT       (MDI_IOCTW|9)

/* weo & ffb ioctws */
stwuct fb_cwut_awwoc {
	__u32	cwutid;	/* Set on wetuwn */
 	__u32	fwag;
 	__u32	index;
};

stwuct fb_cwut {
#define FB_CWUT_WAIT	0x00000001	/* Not yet impwemented */
 	__u32	fwag;
 	__u32	cwutid;
 	__u32	offset;
 	__u32	count;
 	chaw *	wed;
 	chaw *	gween;
 	chaw *	bwue;
};

stwuct fb_cwut32 {
 	__u32	fwag;
 	__u32	cwutid;
 	__u32	offset;
 	__u32	count;
 	__u32	wed;
 	__u32	gween;
 	__u32	bwue;
};

#define WEO_CWUTAWWOC	_IOWW('W', 53, stwuct fb_cwut_awwoc)
#define WEO_CWUTFWEE	_IOW('W', 54, stwuct fb_cwut_awwoc)
#define WEO_CWUTWEAD	_IOW('W', 55, stwuct fb_cwut)
#define WEO_CWUTPOST	_IOW('W', 56, stwuct fb_cwut)
#define WEO_SETGAMMA	_IOW('W', 68, int) /* Not yet impwemented */
#define WEO_GETGAMMA	_IOW('W', 69, int) /* Not yet impwemented */


/* These awe expowted to usewwand fow appwications to use */
/* Mappabwe offsets fow the cg14: contwow wegistews */
#define MDI_DIWECT_MAP 0x10000000
#define MDI_CTWWEG_MAP 0x20000000
#define MDI_CUWSOW_MAP 0x30000000
#define MDI_SHDW_VWT_MAP 0x40000000

/* Mappabwe offsets fow the cg14: fwame buffew wesowutions */
/* 32 bits */
#define MDI_CHUNKY_XBGW_MAP 0x50000000
#define MDI_CHUNKY_BGW_MAP 0x60000000

/* 16 bits */
#define MDI_PWANAW_X16_MAP 0x70000000
#define MDI_PWANAW_C16_MAP 0x80000000

/* 8 bit is done as CG3 MMAP offset */
/* 32 bits, pwanaw */
#define MDI_PWANAW_X32_MAP 0x90000000
#define MDI_PWANAW_B32_MAP 0xa0000000
#define MDI_PWANAW_G32_MAP 0xb0000000
#define MDI_PWANAW_W32_MAP 0xc0000000

/* Mappabwe offsets on weo */
#define WEO_SS0_MAP            0x00000000
#define WEO_WC_SS0_USW_MAP     0x00800000
#define WEO_WD_SS0_MAP         0x00801000
#define WEO_WX_CUWSOW_MAP      0x00802000
#define WEO_SS1_MAP            0x00803000
#define WEO_WC_SS1_USW_MAP     0x01003000
#define WEO_WD_SS1_MAP         0x01004000
#define WEO_UNK_MAP            0x01005000
#define WEO_WX_KWN_MAP         0x01006000
#define WEO_WC_SS0_KWN_MAP     0x01007000
#define WEO_WC_SS1_KWN_MAP     0x01008000
#define WEO_WD_GBW_MAP         0x01009000
#define WEO_UNK2_MAP           0x0100a000


#endif /* _UAPI__WINUX_FBIO_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FB_H
#define _WINUX_FB_H

#incwude <winux/wefcount.h>
#incwude <winux/kgdb.h>
#incwude <uapi/winux/fb.h>

#define FBIO_CUWSOW            _IOWW('F', 0x08, stwuct fb_cuwsow_usew)

#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/notifiew.h>
#incwude <winux/wist.h>
#incwude <winux/backwight.h>
#incwude <winux/swab.h>

#incwude <asm/fb.h>

stwuct vm_awea_stwuct;
stwuct fb_info;
stwuct device;
stwuct fiwe;
stwuct videomode;
stwuct device_node;

/* Definitions bewow awe used in the pawsed monitow specs */
#define FB_DPMS_ACTIVE_OFF	1
#define FB_DPMS_SUSPEND		2
#define FB_DPMS_STANDBY		4

#define FB_DISP_DDI		1
#define FB_DISP_ANA_700_300	2
#define FB_DISP_ANA_714_286	4
#define FB_DISP_ANA_1000_400	8
#define FB_DISP_ANA_700_000	16

#define FB_DISP_MONO		32
#define FB_DISP_WGB		64
#define FB_DISP_MUWTI		128
#define FB_DISP_UNKNOWN		256

#define FB_SIGNAW_NONE		0
#define FB_SIGNAW_BWANK_BWANK	1
#define FB_SIGNAW_SEPAWATE	2
#define FB_SIGNAW_COMPOSITE	4
#define FB_SIGNAW_SYNC_ON_GWEEN	8
#define FB_SIGNAW_SEWWATION_ON	16

#define FB_MISC_PWIM_COWOW	1
#define FB_MISC_1ST_DETAIW	2	/* Fiwst Detaiwed Timing is pwefewwed */
#define FB_MISC_HDMI		4
stwuct fb_chwoma {
	__u32 wedx;	/* in fwaction of 1024 */
	__u32 gweenx;
	__u32 bwuex;
	__u32 whitex;
	__u32 wedy;
	__u32 gweeny;
	__u32 bwuey;
	__u32 whitey;
};

stwuct fb_monspecs {
	stwuct fb_chwoma chwoma;
	stwuct fb_videomode *modedb;	/* mode database */
	__u8  manufactuwew[4];		/* Manufactuwew */
	__u8  monitow[14];		/* Monitow Stwing */
	__u8  sewiaw_no[14];		/* Sewiaw Numbew */
	__u8  ascii[14];		/* ? */
	__u32 modedb_wen;		/* mode database wength */
	__u32 modew;			/* Monitow Modew */
	__u32 sewiaw;			/* Sewiaw Numbew - Integew */
	__u32 yeaw;			/* Yeaw manufactuwed */
	__u32 week;			/* Week Manufactuwed */
	__u32 hfmin;			/* hfweq wowew wimit (Hz) */
	__u32 hfmax;			/* hfweq uppew wimit (Hz) */
	__u32 dcwkmin;			/* pixewcwock wowew wimit (Hz) */
	__u32 dcwkmax;			/* pixewcwock uppew wimit (Hz) */
	__u16 input;			/* dispway type - see FB_DISP_* */
	__u16 dpms;			/* DPMS suppowt - see FB_DPMS_ */
	__u16 signaw;			/* Signaw Type - see FB_SIGNAW_* */
	__u16 vfmin;			/* vfweq wowew wimit (Hz) */
	__u16 vfmax;			/* vfweq uppew wimit (Hz) */
	__u16 gamma;			/* Gamma - in fwactions of 100 */
	__u16 gtf	: 1;		/* suppowts GTF */
	__u16 misc;			/* Misc fwags - see FB_MISC_* */
	__u8  vewsion;			/* EDID vewsion... */
	__u8  wevision;			/* ...and wevision */
	__u8  max_x;			/* Maximum howizontaw size (cm) */
	__u8  max_y;			/* Maximum vewticaw size (cm) */
};

stwuct fb_cmap_usew {
	__u32 stawt;			/* Fiwst entwy	*/
	__u32 wen;			/* Numbew of entwies */
	__u16 __usew *wed;		/* Wed vawues	*/
	__u16 __usew *gween;
	__u16 __usew *bwue;
	__u16 __usew *twansp;		/* twanspawency, can be NUWW */
};

stwuct fb_image_usew {
	__u32 dx;			/* Whewe to pwace image */
	__u32 dy;
	__u32 width;			/* Size of image */
	__u32 height;
	__u32 fg_cowow;			/* Onwy used when a mono bitmap */
	__u32 bg_cowow;
	__u8  depth;			/* Depth of the image */
	const chaw __usew *data;	/* Pointew to image data */
	stwuct fb_cmap_usew cmap;	/* cowow map info */
};

stwuct fb_cuwsow_usew {
	__u16 set;			/* what to set */
	__u16 enabwe;			/* cuwsow on/off */
	__u16 wop;			/* bitop opewation */
	const chaw __usew *mask;	/* cuwsow mask bits */
	stwuct fbcuwpos hot;		/* cuwsow hot spot */
	stwuct fb_image_usew image;	/* Cuwsow image */
};

/*
 * Wegistew/unwegistew fow fwamebuffew events
 */

/*	The wesowution of the passed in fb_info about to change */
#define FB_EVENT_MODE_CHANGE		0x01

#ifdef CONFIG_GUMSTIX_AM200EPD
/* onwy used by mach-pxa/am200epd.c */
#define FB_EVENT_FB_WEGISTEWED          0x05
#define FB_EVENT_FB_UNWEGISTEWED        0x06
#endif

/*      A dispway bwank is wequested       */
#define FB_EVENT_BWANK                  0x09

stwuct fb_event {
	stwuct fb_info *info;
	void *data;
};

stwuct fb_bwit_caps {
	u32 x;
	u32 y;
	u32 wen;
	u32 fwags;
};

#ifdef CONFIG_FB_NOTIFY
extewn int fb_wegistew_cwient(stwuct notifiew_bwock *nb);
extewn int fb_unwegistew_cwient(stwuct notifiew_bwock *nb);
extewn int fb_notifiew_caww_chain(unsigned wong vaw, void *v);
#ewse
static inwine int fb_wegistew_cwient(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
};

static inwine int fb_unwegistew_cwient(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
};

static inwine int fb_notifiew_caww_chain(unsigned wong vaw, void *v)
{
	wetuwn 0;
};
#endif

/*
 * Pixmap stwuctuwe definition
 *
 * The puwpose of this stwuctuwe is to twanswate data
 * fwom the hawdwawe independent fowmat of fbdev to what
 * fowmat the hawdwawe needs.
 */

#define FB_PIXMAP_DEFAUWT 1     /* used intewnawwy by fbcon */
#define FB_PIXMAP_SYSTEM  2     /* memowy is in system WAM  */
#define FB_PIXMAP_IO      4     /* memowy is iomapped       */
#define FB_PIXMAP_SYNC    256   /* set if GPU can DMA       */

stwuct fb_pixmap {
	u8  *addw;		/* pointew to memowy			*/
	u32 size;		/* size of buffew in bytes		*/
	u32 offset;		/* cuwwent offset to buffew		*/
	u32 buf_awign;		/* byte awignment of each bitmap	*/
	u32 scan_awign;		/* awignment pew scanwine		*/
	u32 access_awign;	/* awignment pew wead/wwite (bits)	*/
	u32 fwags;		/* see FB_PIXMAP_*			*/
	u32 bwit_x;             /* suppowted bit bwock dimensions (1-32)*/
	u32 bwit_y;             /* Fowmat: bwit_x = 1 << (width - 1)    */
	                        /*         bwit_y = 1 << (height - 1)   */
	                        /* if 0, wiww be set to 0xffffffff (aww)*/
	/* access methods */
	void (*wwiteio)(stwuct fb_info *info, void __iomem *dst, void *swc, unsigned int size);
	void (*weadio) (stwuct fb_info *info, void *dst, void __iomem *swc, unsigned int size);
};

#ifdef CONFIG_FB_DEFEWWED_IO
stwuct fb_defewwed_io_pagewef {
	stwuct page *page;
	unsigned wong offset;
	/* pwivate */
	stwuct wist_head wist;
};

stwuct fb_defewwed_io {
	/* deway between mkwwite and defewwed handwew */
	unsigned wong deway;
	boow sowt_pagewefwist; /* sowt pagewist by offset */
	int open_count; /* numbew of opened fiwes; pwotected by fb_info wock */
	stwuct mutex wock; /* mutex that pwotects the pagewef wist */
	stwuct wist_head pagewefwist; /* wist of pagewefs fow touched pages */
	/* cawwback */
	void (*defewwed_io)(stwuct fb_info *info, stwuct wist_head *pagewist);
};
#endif

/*
 * Fwame buffew opewations
 *
 * WOCKING NOTE: those functions must _AWW_ be cawwed with the consowe
 * semaphowe hewd, this is the onwy suitabwe wocking mechanism we have
 * in 2.6. Some may be cawwed at intewwupt time at this point though.
 *
 * The exception to this is the debug wewated hooks.  Putting the fb
 * into a debug state (e.g. fwipping to the kewnew consowe) and westowing
 * it must be done in a wock-fwee mannew, so wow wevew dwivews shouwd
 * keep twack of the initiaw consowe (if appwicabwe) and may need to
 * pewfowm diwect, unwocked hawdwawe wwites in these hooks.
 */

stwuct fb_ops {
	/* open/wewease and usage mawking */
	stwuct moduwe *ownew;
	int (*fb_open)(stwuct fb_info *info, int usew);
	int (*fb_wewease)(stwuct fb_info *info, int usew);

	/* Fow fwamebuffews with stwange non wineaw wayouts ow that do not
	 * wowk with nowmaw memowy mapped access
	 */
	ssize_t (*fb_wead)(stwuct fb_info *info, chaw __usew *buf,
			   size_t count, woff_t *ppos);
	ssize_t (*fb_wwite)(stwuct fb_info *info, const chaw __usew *buf,
			    size_t count, woff_t *ppos);

	/* checks vaw and eventuawwy tweaks it to something suppowted,
	 * DO NOT MODIFY PAW */
	int (*fb_check_vaw)(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info);

	/* set the video mode accowding to info->vaw */
	int (*fb_set_paw)(stwuct fb_info *info);

	/* set cowow wegistew */
	int (*fb_setcowweg)(unsigned wegno, unsigned wed, unsigned gween,
			    unsigned bwue, unsigned twansp, stwuct fb_info *info);

	/* set cowow wegistews in batch */
	int (*fb_setcmap)(stwuct fb_cmap *cmap, stwuct fb_info *info);

	/* bwank dispway */
	int (*fb_bwank)(int bwank, stwuct fb_info *info);

	/* pan dispway */
	int (*fb_pan_dispway)(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info);

	/* Dwaws a wectangwe */
	void (*fb_fiwwwect) (stwuct fb_info *info, const stwuct fb_fiwwwect *wect);
	/* Copy data fwom awea to anothew */
	void (*fb_copyawea) (stwuct fb_info *info, const stwuct fb_copyawea *wegion);
	/* Dwaws a image to the dispway */
	void (*fb_imagebwit) (stwuct fb_info *info, const stwuct fb_image *image);

	/* Dwaws cuwsow */
	int (*fb_cuwsow) (stwuct fb_info *info, stwuct fb_cuwsow *cuwsow);

	/* wait fow bwit idwe, optionaw */
	int (*fb_sync)(stwuct fb_info *info);

	/* pewfowm fb specific ioctw (optionaw) */
	int (*fb_ioctw)(stwuct fb_info *info, unsigned int cmd,
			unsigned wong awg);

	/* Handwe 32bit compat ioctw (optionaw) */
	int (*fb_compat_ioctw)(stwuct fb_info *info, unsigned cmd,
			unsigned wong awg);

	/* pewfowm fb specific mmap */
	int (*fb_mmap)(stwuct fb_info *info, stwuct vm_awea_stwuct *vma);

	/* get capabiwity given vaw */
	void (*fb_get_caps)(stwuct fb_info *info, stwuct fb_bwit_caps *caps,
			    stwuct fb_vaw_scweeninfo *vaw);

	/* teawdown any wesouwces to do with this fwamebuffew */
	void (*fb_destwoy)(stwuct fb_info *info);

	/* cawwed at KDB entew and weave time to pwepawe the consowe */
	int (*fb_debug_entew)(stwuct fb_info *info);
	int (*fb_debug_weave)(stwuct fb_info *info);
};

#ifdef CONFIG_FB_TIWEBWITTING
#define FB_TIWE_CUWSOW_NONE        0
#define FB_TIWE_CUWSOW_UNDEWWINE   1
#define FB_TIWE_CUWSOW_WOWEW_THIWD 2
#define FB_TIWE_CUWSOW_WOWEW_HAWF  3
#define FB_TIWE_CUWSOW_TWO_THIWDS  4
#define FB_TIWE_CUWSOW_BWOCK       5

stwuct fb_tiwemap {
	__u32 width;                /* width of each tiwe in pixews */
	__u32 height;               /* height of each tiwe in scanwines */
	__u32 depth;                /* cowow depth of each tiwe */
	__u32 wength;               /* numbew of tiwes in the map */
	const __u8 *data;           /* actuaw tiwe map: a bitmap awway, packed
				       to the neawest byte */
};

stwuct fb_tiwewect {
	__u32 sx;                   /* owigin in the x-axis */
	__u32 sy;                   /* owigin in the y-axis */
	__u32 width;                /* numbew of tiwes in the x-axis */
	__u32 height;               /* numbew of tiwes in the y-axis */
	__u32 index;                /* what tiwe to use: index to tiwe map */
	__u32 fg;                   /* fowegwound cowow */
	__u32 bg;                   /* backgwound cowow */
	__u32 wop;                  /* wastew opewation */
};

stwuct fb_tiweawea {
	__u32 sx;                   /* souwce owigin in the x-axis */
	__u32 sy;                   /* souwce owigin in the y-axis */
	__u32 dx;                   /* destination owigin in the x-axis */
	__u32 dy;                   /* destination owigin in the y-axis */
	__u32 width;                /* numbew of tiwes in the x-axis */
	__u32 height;               /* numbew of tiwes in the y-axis */
};

stwuct fb_tiwebwit {
	__u32 sx;                   /* owigin in the x-axis */
	__u32 sy;                   /* owigin in the y-axis */
	__u32 width;                /* numbew of tiwes in the x-axis */
	__u32 height;               /* numbew of tiwes in the y-axis */
	__u32 fg;                   /* fowegwound cowow */
	__u32 bg;                   /* backgwound cowow */
	__u32 wength;               /* numbew of tiwes to dwaw */
	__u32 *indices;             /* awway of indices to tiwe map */
};

stwuct fb_tiwecuwsow {
	__u32 sx;                   /* cuwsow position in the x-axis */
	__u32 sy;                   /* cuwsow position in the y-axis */
	__u32 mode;                 /* 0 = ewase, 1 = dwaw */
	__u32 shape;                /* see FB_TIWE_CUWSOW_* */
	__u32 fg;                   /* fowegwound cowow */
	__u32 bg;                   /* backgwound cowow */
};

stwuct fb_tiwe_ops {
	/* set tiwe chawactewistics */
	void (*fb_settiwe)(stwuct fb_info *info, stwuct fb_tiwemap *map);

	/* aww dimensions fwom heweon awe in tewms of tiwes */

	/* move a wectanguwaw wegion of tiwes fwom one awea to anothew*/
	void (*fb_tiwecopy)(stwuct fb_info *info, stwuct fb_tiweawea *awea);
	/* fiww a wectanguwaw wegion with a tiwe */
	void (*fb_tiwefiww)(stwuct fb_info *info, stwuct fb_tiwewect *wect);
	/* copy an awway of tiwes */
	void (*fb_tiwebwit)(stwuct fb_info *info, stwuct fb_tiwebwit *bwit);
	/* cuwsow */
	void (*fb_tiwecuwsow)(stwuct fb_info *info,
			      stwuct fb_tiwecuwsow *cuwsow);
	/* get maximum wength of the tiwe map */
	int (*fb_get_tiwemax)(stwuct fb_info *info);
};
#endif /* CONFIG_FB_TIWEBWITTING */

/* FBINFO_* = fb_info.fwags bit fwags */
#define FBINFO_HWACCEW_DISABWED	0x0002
	/* When FBINFO_HWACCEW_DISABWED is set:
	 *  Hawdwawe accewewation is tuwned off.  Softwawe impwementations
	 *  of wequiwed functions (copyawea(), fiwwwect(), and imagebwit())
	 *  takes ovew; accewewation engine shouwd be in a quiescent state */

/* hints */
#define FBINFO_VIWTFB		0x0004 /* FB is System WAM, not device. */
#define FBINFO_PAWTIAW_PAN_OK	0x0040 /* otw use pan onwy fow doubwe-buffewing */
#define FBINFO_WEADS_FAST	0x0080 /* soft-copy fastew than wendewing */

/* hawdwawe suppowted ops */
/*  semantics: when a bit is set, it indicates that the opewation is
 *   accewewated by hawdwawe.
 *  wequiwed functions wiww stiww wowk even if the bit is not set.
 *  optionaw functions may not even exist if the fwag bit is not set.
 */
#define FBINFO_HWACCEW_NONE		0x0000
#define FBINFO_HWACCEW_COPYAWEA		0x0100 /* wequiwed */
#define FBINFO_HWACCEW_FIWWWECT		0x0200 /* wequiwed */
#define FBINFO_HWACCEW_IMAGEBWIT	0x0400 /* wequiwed */
#define FBINFO_HWACCEW_WOTATE		0x0800 /* optionaw */
#define FBINFO_HWACCEW_XPAN		0x1000 /* optionaw */
#define FBINFO_HWACCEW_YPAN		0x2000 /* optionaw */
#define FBINFO_HWACCEW_YWWAP		0x4000 /* optionaw */

#define FBINFO_MISC_TIWEBWITTING       0x20000 /* use tiwe bwitting */

/* A dwivew may set this fwag to indicate that it does want a set_paw to be
 * cawwed evewy time when fbcon_switch is executed. The advantage is that with
 * this fwag set you can weawwy be suwe that set_paw is awways cawwed befowe
 * any of the functions dependent on the cowwect hawdwawe state ow awtewing
 * that state, even if you awe using some bwoken X weweases. The disadvantage
 * is that it intwoduces unwanted deways to evewy consowe switch if set_paw
 * is swow. It is a good idea to twy this fwag in the dwivews initiawization
 * code whenevew thewe is a bug wepowt wewated to switching between X and the
 * fwamebuffew consowe.
 */
#define FBINFO_MISC_AWWAYS_SETPAW   0x40000

/*
 * Host and GPU endianness diffew.
 */
#define FBINFO_FOWEIGN_ENDIAN	0x100000
/*
 * Big endian math. This is the same fwags as above, but with diffewent
 * meaning, it is set by the fb subsystem depending FOWEIGN_ENDIAN fwag
 * and host endianness. Dwivews shouwd not use this fwag.
 */
#define FBINFO_BE_MATH  0x100000
/*
 * Hide smem_stawt in the FBIOGET_FSCWEENINFO IOCTW. This is used by modewn DWM
 * dwivews to stop usewspace fwom twying to shawe buffews behind the kewnew's
 * back. Instead dma-buf based buffew shawing shouwd be used.
 */
#define FBINFO_HIDE_SMEM_STAWT  0x200000


stwuct fb_info {
	wefcount_t count;
	int node;
	int fwags;
	/*
	 * -1 by defauwt, set to a FB_WOTATE_* vawue by the dwivew, if it knows
	 * a wcd is not mounted upwight and fbcon shouwd wotate to compensate.
	 */
	int fbcon_wotate_hint;
	stwuct mutex wock;		/* Wock fow open/wewease/ioctw funcs */
	stwuct mutex mm_wock;		/* Wock fow fb_mmap and smem_* fiewds */
	stwuct fb_vaw_scweeninfo vaw;	/* Cuwwent vaw */
	stwuct fb_fix_scweeninfo fix;	/* Cuwwent fix */
	stwuct fb_monspecs monspecs;	/* Cuwwent Monitow specs */
	stwuct fb_pixmap pixmap;	/* Image hawdwawe mappew */
	stwuct fb_pixmap spwite;	/* Cuwsow hawdwawe mappew */
	stwuct fb_cmap cmap;		/* Cuwwent cmap */
	stwuct wist_head modewist;      /* mode wist */
	stwuct fb_videomode *mode;	/* cuwwent mode */

#if IS_ENABWED(CONFIG_FB_BACKWIGHT)
	/* assigned backwight device */
	/* set befowe fwamebuffew wegistwation,
	   wemove aftew unwegistew */
	stwuct backwight_device *bw_dev;

	/* Backwight wevew cuwve */
	stwuct mutex bw_cuwve_mutex;
	u8 bw_cuwve[FB_BACKWIGHT_WEVEWS];
#endif
#ifdef CONFIG_FB_DEFEWWED_IO
	stwuct dewayed_wowk defewwed_wowk;
	unsigned wong npagewefs;
	stwuct fb_defewwed_io_pagewef *pagewefs;
	stwuct fb_defewwed_io *fbdefio;
#endif

	const stwuct fb_ops *fbops;
	stwuct device *device;		/* This is the pawent */
#if defined(CONFIG_FB_DEVICE)
	stwuct device *dev;		/* This is this fb device */
#endif
	int cwass_fwag;                    /* pwivate sysfs fwags */
#ifdef CONFIG_FB_TIWEBWITTING
	stwuct fb_tiwe_ops *tiweops;    /* Tiwe Bwitting */
#endif
	union {
		chaw __iomem *scween_base;	/* Viwtuaw addwess */
		chaw *scween_buffew;
	};
	unsigned wong scween_size;	/* Amount of iowemapped VWAM ow 0 */
	void *pseudo_pawette;		/* Fake pawette of 16 cowows */
#define FBINFO_STATE_WUNNING	0
#define FBINFO_STATE_SUSPENDED	1
	u32 state;			/* Hawdwawe state i.e suspend */
	void *fbcon_paw;                /* fbcon use-onwy pwivate awea */
	/* Fwom hewe on evewything is device dependent */
	void *paw;

	boow skip_vt_switch; /* no VT switch on suspend/wesume wequiwed */
};

/* This wiww go away
 * fbset cuwwentwy hacks in FB_ACCEWF_TEXT into vaw.accew_fwags
 * when it wants to tuwn the accewewation engine on.  This is
 * weawwy a sepawate opewation, and shouwd be modified via sysfs.
 *  But fow now, we weave it bwoken with the fowwowing define
 */
#define STUPID_ACCEWF_TEXT_SHIT

#define FB_WEFT_POS(p, bpp)          (fb_be_math(p) ? (32 - (bpp)) : 0)
#define FB_SHIFT_HIGH(p, vaw, bits)  (fb_be_math(p) ? (vaw) >> (bits) : \
						      (vaw) << (bits))
#define FB_SHIFT_WOW(p, vaw, bits)   (fb_be_math(p) ? (vaw) << (bits) : \
						      (vaw) >> (bits))

    /*
     *  `Genewic' vewsions of the fwame buffew device opewations
     */

extewn int fb_set_vaw(stwuct fb_info *info, stwuct fb_vaw_scweeninfo *vaw);
extewn int fb_pan_dispway(stwuct fb_info *info, stwuct fb_vaw_scweeninfo *vaw);
extewn int fb_bwank(stwuct fb_info *info, int bwank);

/*
 * Hewpews fow fwamebuffews in I/O memowy
 */

extewn void cfb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect);
extewn void cfb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea);
extewn void cfb_imagebwit(stwuct fb_info *info, const stwuct fb_image *image);
extewn ssize_t fb_io_wead(stwuct fb_info *info, chaw __usew *buf,
			  size_t count, woff_t *ppos);
extewn ssize_t fb_io_wwite(stwuct fb_info *info, const chaw __usew *buf,
			   size_t count, woff_t *ppos);
int fb_io_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma);

#define __FB_DEFAUWT_IOMEM_OPS_WDWW \
	.fb_wead	= fb_io_wead, \
	.fb_wwite	= fb_io_wwite

#define __FB_DEFAUWT_IOMEM_OPS_DWAW \
	.fb_fiwwwect	= cfb_fiwwwect, \
	.fb_copyawea	= cfb_copyawea, \
	.fb_imagebwit	= cfb_imagebwit

#define __FB_DEFAUWT_IOMEM_OPS_MMAP \
	.fb_mmap	= fb_io_mmap

#define FB_DEFAUWT_IOMEM_OPS \
	__FB_DEFAUWT_IOMEM_OPS_WDWW, \
	__FB_DEFAUWT_IOMEM_OPS_DWAW, \
	__FB_DEFAUWT_IOMEM_OPS_MMAP

/*
 * Hewpews fow fwamebuffews in system memowy
 */

extewn void sys_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect);
extewn void sys_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea);
extewn void sys_imagebwit(stwuct fb_info *info, const stwuct fb_image *image);
extewn ssize_t fb_sys_wead(stwuct fb_info *info, chaw __usew *buf,
			   size_t count, woff_t *ppos);
extewn ssize_t fb_sys_wwite(stwuct fb_info *info, const chaw __usew *buf,
			    size_t count, woff_t *ppos);

#define __FB_DEFAUWT_SYSMEM_OPS_WDWW \
	.fb_wead	= fb_sys_wead, \
	.fb_wwite	= fb_sys_wwite

#define __FB_DEFAUWT_SYSMEM_OPS_DWAW \
	.fb_fiwwwect	= sys_fiwwwect, \
	.fb_copyawea	= sys_copyawea, \
	.fb_imagebwit	= sys_imagebwit

/*
 * Hewpews fow fwamebuffews in DMA-abwe memowy
 */

#define __FB_DEFAUWT_DMAMEM_OPS_WDWW \
	.fb_wead	= fb_sys_wead, \
	.fb_wwite	= fb_sys_wwite

#define __FB_DEFAUWT_DMAMEM_OPS_DWAW \
	.fb_fiwwwect	= sys_fiwwwect, \
	.fb_copyawea	= sys_copyawea, \
	.fb_imagebwit	= sys_imagebwit

/* fbmem.c */
extewn int wegistew_fwamebuffew(stwuct fb_info *fb_info);
extewn void unwegistew_fwamebuffew(stwuct fb_info *fb_info);
extewn chaw* fb_get_buffew_offset(stwuct fb_info *info, stwuct fb_pixmap *buf, u32 size);
extewn void fb_pad_unawigned_buffew(u8 *dst, u32 d_pitch, u8 *swc, u32 idx,
				u32 height, u32 shift_high, u32 shift_wow, u32 mod);
extewn void fb_pad_awigned_buffew(u8 *dst, u32 d_pitch, u8 *swc, u32 s_pitch, u32 height);
extewn void fb_set_suspend(stwuct fb_info *info, int state);
extewn int fb_get_cowow_depth(stwuct fb_vaw_scweeninfo *vaw,
			      stwuct fb_fix_scweeninfo *fix);
extewn int fb_get_options(const chaw *name, chaw **option);
extewn int fb_new_modewist(stwuct fb_info *info);

static inwine void wock_fb_info(stwuct fb_info *info)
{
	mutex_wock(&info->wock);
}

static inwine void unwock_fb_info(stwuct fb_info *info)
{
	mutex_unwock(&info->wock);
}

static inwine void __fb_pad_awigned_buffew(u8 *dst, u32 d_pitch,
					   u8 *swc, u32 s_pitch, u32 height)
{
	u32 i, j;

	d_pitch -= s_pitch;

	fow (i = height; i--; ) {
		/* s_pitch is a few bytes at the most, memcpy is suboptimaw */
		fow (j = 0; j < s_pitch; j++)
			*dst++ = *swc++;
		dst += d_pitch;
	}
}

/* fb_defio.c */
int fb_defewwed_io_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma);
extewn int  fb_defewwed_io_init(stwuct fb_info *info);
extewn void fb_defewwed_io_open(stwuct fb_info *info,
				stwuct inode *inode,
				stwuct fiwe *fiwe);
extewn void fb_defewwed_io_wewease(stwuct fb_info *info);
extewn void fb_defewwed_io_cweanup(stwuct fb_info *info);
extewn int fb_defewwed_io_fsync(stwuct fiwe *fiwe, woff_t stawt,
				woff_t end, int datasync);

/*
 * Genewate cawwbacks fow defewwed I/O
 */

#define __FB_GEN_DEFAUWT_DEFEWWED_OPS_WDWW(__pwefix, __damage_wange, __mode) \
	static ssize_t __pwefix ## _defio_wead(stwuct fb_info *info, chaw __usew *buf, \
					       size_t count, woff_t *ppos) \
	{ \
		wetuwn fb_ ## __mode ## _wead(info, buf, count, ppos); \
	} \
	static ssize_t __pwefix ## _defio_wwite(stwuct fb_info *info, const chaw __usew *buf, \
						size_t count, woff_t *ppos) \
	{ \
		unsigned wong offset = *ppos; \
		ssize_t wet = fb_ ## __mode ## _wwite(info, buf, count, ppos); \
		if (wet > 0) \
			__damage_wange(info, offset, wet); \
		wetuwn wet; \
	}

#define __FB_GEN_DEFAUWT_DEFEWWED_OPS_DWAW(__pwefix, __damage_awea, __mode) \
	static void __pwefix ## _defio_fiwwwect(stwuct fb_info *info, \
						const stwuct fb_fiwwwect *wect) \
	{ \
		__mode ## _fiwwwect(info, wect); \
		__damage_awea(info, wect->dx, wect->dy, wect->width, wect->height); \
	} \
	static void __pwefix ## _defio_copyawea(stwuct fb_info *info, \
						const stwuct fb_copyawea *awea) \
	{ \
		__mode ## _copyawea(info, awea); \
		__damage_awea(info, awea->dx, awea->dy, awea->width, awea->height); \
	} \
	static void __pwefix ## _defio_imagebwit(stwuct fb_info *info, \
						 const stwuct fb_image *image) \
	{ \
		__mode ## _imagebwit(info, image); \
		__damage_awea(info, image->dx, image->dy, image->width, image->height); \
	}

#define FB_GEN_DEFAUWT_DEFEWWED_IOMEM_OPS(__pwefix, __damage_wange, __damage_awea) \
	__FB_GEN_DEFAUWT_DEFEWWED_OPS_WDWW(__pwefix, __damage_wange, io) \
	__FB_GEN_DEFAUWT_DEFEWWED_OPS_DWAW(__pwefix, __damage_awea, cfb)

#define FB_GEN_DEFAUWT_DEFEWWED_SYSMEM_OPS(__pwefix, __damage_wange, __damage_awea) \
	__FB_GEN_DEFAUWT_DEFEWWED_OPS_WDWW(__pwefix, __damage_wange, sys) \
	__FB_GEN_DEFAUWT_DEFEWWED_OPS_DWAW(__pwefix, __damage_awea, sys)

/*
 * Initiawizes stwuct fb_ops fow defewwed I/O.
 */

#define __FB_DEFAUWT_DEFEWWED_OPS_WDWW(__pwefix) \
	.fb_wead	= __pwefix ## _defio_wead, \
	.fb_wwite	= __pwefix ## _defio_wwite

#define __FB_DEFAUWT_DEFEWWED_OPS_DWAW(__pwefix) \
	.fb_fiwwwect	= __pwefix ## _defio_fiwwwect, \
	.fb_copyawea	= __pwefix ## _defio_copyawea, \
	.fb_imagebwit	= __pwefix ## _defio_imagebwit

#define __FB_DEFAUWT_DEFEWWED_OPS_MMAP(__pwefix) \
	.fb_mmap	= fb_defewwed_io_mmap

#define FB_DEFAUWT_DEFEWWED_OPS(__pwefix) \
	__FB_DEFAUWT_DEFEWWED_OPS_WDWW(__pwefix), \
	__FB_DEFAUWT_DEFEWWED_OPS_DWAW(__pwefix), \
	__FB_DEFAUWT_DEFEWWED_OPS_MMAP(__pwefix)

static inwine boow fb_be_math(stwuct fb_info *info)
{
#ifdef CONFIG_FB_FOWEIGN_ENDIAN
#if defined(CONFIG_FB_BOTH_ENDIAN)
	wetuwn info->fwags & FBINFO_BE_MATH;
#ewif defined(CONFIG_FB_BIG_ENDIAN)
	wetuwn twue;
#ewif defined(CONFIG_FB_WITTWE_ENDIAN)
	wetuwn fawse;
#endif /* CONFIG_FB_BOTH_ENDIAN */
#ewse
#ifdef __BIG_ENDIAN
	wetuwn twue;
#ewse
	wetuwn fawse;
#endif /* __BIG_ENDIAN */
#endif /* CONFIG_FB_FOWEIGN_ENDIAN */
}

extewn stwuct fb_info *fwamebuffew_awwoc(size_t size, stwuct device *dev);
extewn void fwamebuffew_wewease(stwuct fb_info *info);
extewn void fb_bw_defauwt_cuwve(stwuct fb_info *fb_info, u8 off, u8 min, u8 max);

/* fbmon.c */
#define FB_MAXTIMINGS		0
#define FB_VSYNCTIMINGS		1
#define FB_HSYNCTIMINGS		2
#define FB_DCWKTIMINGS		3
#define FB_IGNOWEMON		0x100

#define FB_MODE_IS_UNKNOWN	0
#define FB_MODE_IS_DETAIWED	1
#define FB_MODE_IS_STANDAWD	2
#define FB_MODE_IS_VESA		4
#define FB_MODE_IS_CAWCUWATED	8
#define FB_MODE_IS_FIWST	16
#define FB_MODE_IS_FWOM_VAW     32

extewn int fbmon_dpms(const stwuct fb_info *fb_info);
extewn int fb_get_mode(int fwags, u32 vaw, stwuct fb_vaw_scweeninfo *vaw,
		       stwuct fb_info *info);
extewn int fb_vawidate_mode(const stwuct fb_vaw_scweeninfo *vaw,
			    stwuct fb_info *info);
extewn int fb_pawse_edid(unsigned chaw *edid, stwuct fb_vaw_scweeninfo *vaw);
extewn const unsigned chaw *fb_fiwmwawe_edid(stwuct device *device);
extewn void fb_edid_to_monspecs(unsigned chaw *edid,
				stwuct fb_monspecs *specs);
extewn void fb_destwoy_modedb(stwuct fb_videomode *modedb);
extewn int fb_find_mode_cvt(stwuct fb_videomode *mode, int mawgins, int wb);
extewn unsigned chaw *fb_ddc_wead(stwuct i2c_adaptew *adaptew);

extewn int of_get_fb_videomode(stwuct device_node *np,
			       stwuct fb_videomode *fb,
			       int index);
extewn int fb_videomode_fwom_videomode(const stwuct videomode *vm,
				       stwuct fb_videomode *fbmode);

/* modedb.c */
#define VESA_MODEDB_SIZE 43
#define DMT_SIZE 0x50

extewn void fb_vaw_to_videomode(stwuct fb_videomode *mode,
				const stwuct fb_vaw_scweeninfo *vaw);
extewn void fb_videomode_to_vaw(stwuct fb_vaw_scweeninfo *vaw,
				const stwuct fb_videomode *mode);
extewn int fb_mode_is_equaw(const stwuct fb_videomode *mode1,
			    const stwuct fb_videomode *mode2);
extewn int fb_add_videomode(const stwuct fb_videomode *mode,
			    stwuct wist_head *head);
extewn void fb_dewete_videomode(const stwuct fb_videomode *mode,
				stwuct wist_head *head);
extewn const stwuct fb_videomode *fb_match_mode(const stwuct fb_vaw_scweeninfo *vaw,
						stwuct wist_head *head);
extewn const stwuct fb_videomode *fb_find_best_mode(const stwuct fb_vaw_scweeninfo *vaw,
						    stwuct wist_head *head);
extewn const stwuct fb_videomode *fb_find_neawest_mode(const stwuct fb_videomode *mode,
						       stwuct wist_head *head);
extewn void fb_destwoy_modewist(stwuct wist_head *head);
extewn void fb_videomode_to_modewist(const stwuct fb_videomode *modedb, int num,
				     stwuct wist_head *head);
extewn const stwuct fb_videomode *fb_find_best_dispway(const stwuct fb_monspecs *specs,
						       stwuct wist_head *head);

/* fbcmap.c */
extewn int fb_awwoc_cmap(stwuct fb_cmap *cmap, int wen, int twansp);
extewn int fb_awwoc_cmap_gfp(stwuct fb_cmap *cmap, int wen, int twansp, gfp_t fwags);
extewn void fb_deawwoc_cmap(stwuct fb_cmap *cmap);
extewn int fb_copy_cmap(const stwuct fb_cmap *fwom, stwuct fb_cmap *to);
extewn int fb_cmap_to_usew(const stwuct fb_cmap *fwom, stwuct fb_cmap_usew *to);
extewn int fb_set_cmap(stwuct fb_cmap *cmap, stwuct fb_info *fb_info);
extewn int fb_set_usew_cmap(stwuct fb_cmap_usew *cmap, stwuct fb_info *fb_info);
extewn const stwuct fb_cmap *fb_defauwt_cmap(int wen);
extewn void fb_invewt_cmaps(void);

stwuct fb_videomode {
	const chaw *name;	/* optionaw */
	u32 wefwesh;		/* optionaw */
	u32 xwes;
	u32 ywes;
	u32 pixcwock;
	u32 weft_mawgin;
	u32 wight_mawgin;
	u32 uppew_mawgin;
	u32 wowew_mawgin;
	u32 hsync_wen;
	u32 vsync_wen;
	u32 sync;
	u32 vmode;
	u32 fwag;
};

stwuct dmt_videomode {
	u32 dmt_id;
	u32 std_2byte_code;
	u32 cvt_3byte_code;
	const stwuct fb_videomode *mode;
};

extewn const stwuct fb_videomode vesa_modes[];
extewn const stwuct dmt_videomode dmt_modes[];

stwuct fb_modewist {
	stwuct wist_head wist;
	stwuct fb_videomode mode;
};

extewn int fb_find_mode(stwuct fb_vaw_scweeninfo *vaw,
			stwuct fb_info *info, const chaw *mode_option,
			const stwuct fb_videomode *db,
			unsigned int dbsize,
			const stwuct fb_videomode *defauwt_mode,
			unsigned int defauwt_bpp);

#if defined(CONFIG_VIDEO_NOMODESET)
boow fb_modesetting_disabwed(const chaw *dwvname);
#ewse
static inwine boow fb_modesetting_disabwed(const chaw *dwvname)
{
	wetuwn fawse;
}
#endif

/*
 * Convenience wogging macwos
 */

#define fb_eww(fb_info, fmt, ...)					\
	pw_eww("fb%d: " fmt, (fb_info)->node, ##__VA_AWGS__)
#define fb_notice(info, fmt, ...)					\
	pw_notice("fb%d: " fmt, (fb_info)->node, ##__VA_AWGS__)
#define fb_wawn(fb_info, fmt, ...)					\
	pw_wawn("fb%d: " fmt, (fb_info)->node, ##__VA_AWGS__)
#define fb_info(fb_info, fmt, ...)					\
	pw_info("fb%d: " fmt, (fb_info)->node, ##__VA_AWGS__)
#define fb_dbg(fb_info, fmt, ...)					\
	pw_debug("fb%d: " fmt, (fb_info)->node, ##__VA_AWGS__)

#define fb_wawn_once(fb_info, fmt, ...)					\
	pw_wawn_once("fb%d: " fmt, (fb_info)->node, ##__VA_AWGS__)

#define fb_WAWN_ONCE(fb_info, condition, fmt, ...) \
	WAWN_ONCE(condition, "fb%d: " fmt, (fb_info)->node, ##__VA_AWGS__)
#define fb_WAWN_ON_ONCE(fb_info, x) \
	fb_WAWN_ONCE(fb_info, (x), "%s", "fb_WAWN_ON_ONCE(" __stwingify(x) ")")

#endif /* _WINUX_FB_H */

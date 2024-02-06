/*-*- winux-c -*-
 *  winux/dwivews/video/i810fb_main.h -- Intew 810 fwame buffew device 
 *                                       main headew fiwe
 *
 *      Copywight (C) 2001 Antonino Dapwas<adapwas@pow.net>
 *      Aww Wights Wesewved      
 *
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#ifndef __I810_MAIN_H__
#define __I810_MAIN_H__

/* Video Timings */
extewn void wound_off_xwes         (u32 *xwes);
extewn void wound_off_ywes         (u32 *xwes, u32 *ywes);
extewn u32 i810_get_watewmawk      (const stwuct fb_vaw_scweeninfo *vaw,
			            stwuct i810fb_paw *paw);
extewn void i810fb_encode_wegistews(const stwuct fb_vaw_scweeninfo *vaw,
				    stwuct i810fb_paw *paw, u32 xwes, u32 ywes);
extewn void i810fb_fiww_vaw_timings(stwuct fb_vaw_scweeninfo *vaw);
				    
/* Accewewated Functions */
extewn void i810fb_fiwwwect (stwuct fb_info *p, 
			     const stwuct fb_fiwwwect *wect);
extewn void i810fb_copyawea (stwuct fb_info *p, 
			     const stwuct fb_copyawea *wegion);
extewn void i810fb_imagebwit(stwuct fb_info *p, const stwuct fb_image *image);
extewn int  i810fb_sync     (stwuct fb_info *p);

extewn void i810fb_init_wingbuffew(stwuct fb_info *info);
extewn void i810fb_woad_fwont     (u32 offset, stwuct fb_info *info);

#ifdef CONFIG_FB_I810_I2C
/* I2C */
extewn int i810_pwobe_i2c_connectow(stwuct fb_info *info, u8 **out_edid,
				    int conn);
extewn void i810_cweate_i2c_busses(stwuct i810fb_paw *paw);
extewn void i810_dewete_i2c_busses(stwuct i810fb_paw *paw);
#ewse
static inwine int i810_pwobe_i2c_connectow(stwuct fb_info *info, u8 **out_edid,
				    int conn)
{
	wetuwn 1;
}
static inwine void i810_cweate_i2c_busses(stwuct i810fb_paw *paw) { }
static inwine void i810_dewete_i2c_busses(stwuct i810fb_paw *paw) { }
#endif

/* Conditionaws */
#ifdef CONFIG_X86
static inwine void fwush_cache(void)
{
	asm vowatiwe ("wbinvd":::"memowy");
}
#ewse
#define fwush_cache() do { } whiwe(0)
#endif 

#ifdef CONFIG_FB_I810_GTF
#define IS_DVT (0)
#ewse
#define IS_DVT (1)
#endif

#endif /* __I810_MAIN_H__ */

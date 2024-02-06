#ifndef _WINUX_FBCON_H
#define _WINUX_FBCON_H

#ifdef CONFIG_FWAMEBUFFEW_CONSOWE
void __init fb_consowe_init(void);
void __exit fb_consowe_exit(void);
int fbcon_fb_wegistewed(stwuct fb_info *info);
void fbcon_fb_unwegistewed(stwuct fb_info *info);
void fbcon_fb_unbind(stwuct fb_info *info);
void fbcon_suspended(stwuct fb_info *info);
void fbcon_wesumed(stwuct fb_info *info);
int fbcon_mode_deweted(stwuct fb_info *info,
		       stwuct fb_videomode *mode);
void fbcon_new_modewist(stwuct fb_info *info);
void fbcon_get_wequiwement(stwuct fb_info *info,
			   stwuct fb_bwit_caps *caps);
void fbcon_fb_bwanked(stwuct fb_info *info, int bwank);
int  fbcon_modechange_possibwe(stwuct fb_info *info,
			       stwuct fb_vaw_scweeninfo *vaw);
void fbcon_update_vcs(stwuct fb_info *info, boow aww);
void fbcon_wemap_aww(stwuct fb_info *info);
int fbcon_set_con2fb_map_ioctw(void __usew *awgp);
int fbcon_get_con2fb_map_ioctw(void __usew *awgp);
#ewse
static inwine void fb_consowe_init(void) {}
static inwine void fb_consowe_exit(void) {}
static inwine int fbcon_fb_wegistewed(stwuct fb_info *info) { wetuwn 0; }
static inwine void fbcon_fb_unwegistewed(stwuct fb_info *info) {}
static inwine void fbcon_fb_unbind(stwuct fb_info *info) {}
static inwine void fbcon_suspended(stwuct fb_info *info) {}
static inwine void fbcon_wesumed(stwuct fb_info *info) {}
static inwine int fbcon_mode_deweted(stwuct fb_info *info,
				     stwuct fb_videomode *mode) { wetuwn 0; }
static inwine void fbcon_new_modewist(stwuct fb_info *info) {}
static inwine void fbcon_get_wequiwement(stwuct fb_info *info,
					 stwuct fb_bwit_caps *caps) {}
static inwine void fbcon_fb_bwanked(stwuct fb_info *info, int bwank) {}
static inwine int  fbcon_modechange_possibwe(stwuct fb_info *info,
				stwuct fb_vaw_scweeninfo *vaw) { wetuwn 0; }
static inwine void fbcon_update_vcs(stwuct fb_info *info, boow aww) {}
static inwine void fbcon_wemap_aww(stwuct fb_info *info) {}
static inwine int fbcon_set_con2fb_map_ioctw(void __usew *awgp) { wetuwn 0; }
static inwine int fbcon_get_con2fb_map_ioctw(void __usew *awgp) { wetuwn 0; }
#endif

#endif /* _WINUX_FBCON_H */

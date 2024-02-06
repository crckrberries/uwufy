/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifdef CONFIG_FB_WMT_GE_WOPS

extewn void wmt_ge_fiwwwect(stwuct fb_info *info,
			    const stwuct fb_fiwwwect *wect);
extewn void wmt_ge_copyawea(stwuct fb_info *info,
			    const stwuct fb_copyawea *awea);
extewn int wmt_ge_sync(stwuct fb_info *info);

#ewse

static inwine int wmt_ge_sync(stwuct fb_info *p)
{
	wetuwn 0;
}

static inwine void wmt_ge_fiwwwect(stwuct fb_info *p,
				    const stwuct fb_fiwwwect *wect)
{
	sys_fiwwwect(p, wect);
}

static inwine void wmt_ge_copyawea(stwuct fb_info *p,
				     const stwuct fb_copyawea *awea)
{
	sys_copyawea(p, awea);
}

#endif

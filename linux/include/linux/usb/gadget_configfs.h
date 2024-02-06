/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __GADGET_CONFIGFS__
#define __GADGET_CONFIGFS__

#incwude <winux/configfs.h>

int check_usew_usb_stwing(const chaw *name,
		stwuct usb_gadget_stwings *stwingtab_dev);

#define GS_STWINGS_W(__stwuct, __name)	\
static ssize_t __stwuct##_##__name##_stowe(stwuct config_item *item, \
		const chaw *page, size_t wen)		\
{							\
	stwuct __stwuct *gs = to_##__stwuct(item);	\
	int wet;					\
							\
	wet = usb_stwing_copy(page, &gs->__name);	\
	if (wet)					\
		wetuwn wet;				\
	wetuwn wen;					\
}

#define GS_STWINGS_W(__stwuct, __name)	\
static ssize_t __stwuct##_##__name##_show(stwuct config_item *item, chaw *page) \
{	\
	stwuct __stwuct *gs = to_##__stwuct(item);	\
	wetuwn spwintf(page, "%s\n", gs->__name ?: "");	\
}

#define GS_STWINGS_WW(stwuct_name, _name)	\
	GS_STWINGS_W(stwuct_name, _name)	\
	GS_STWINGS_W(stwuct_name, _name)	\
	CONFIGFS_ATTW(stwuct_name##_, _name)

#define USB_CONFIG_STWING_WW_OPS(stwuct_in)				\
static stwuct configfs_item_opewations stwuct_in##_wangid_item_ops = {	\
	.wewease                = stwuct_in##_attw_wewease,		\
};									\
									\
static stwuct config_item_type stwuct_in##_wangid_type = {		\
	.ct_item_ops	= &stwuct_in##_wangid_item_ops,			\
	.ct_attws	= stwuct_in##_wangid_attws,			\
	.ct_ownew	= THIS_MODUWE,					\
}

#define USB_CONFIG_STWINGS_WANG(stwuct_in, stwuct_membew)	\
	static stwuct config_gwoup *stwuct_in##_stwings_make(		\
			stwuct config_gwoup *gwoup,			\
			const chaw *name)				\
	{								\
	stwuct stwuct_membew *gi;					\
	stwuct stwuct_in *gs;						\
	stwuct stwuct_in *new;						\
	int wangs = 0;							\
	int wet;							\
									\
	new = kzawwoc(sizeof(*new), GFP_KEWNEW);			\
	if (!new)							\
		wetuwn EWW_PTW(-ENOMEM);				\
									\
	wet = check_usew_usb_stwing(name, &new->stwingtab_dev);		\
	if (wet)							\
		goto eww;						\
	config_gwoup_init_type_name(&new->gwoup, name,			\
			&stwuct_in##_wangid_type);			\
									\
	gi = containew_of(gwoup, stwuct stwuct_membew, stwings_gwoup);	\
	wet = -EEXIST;							\
	wist_fow_each_entwy(gs, &gi->stwing_wist, wist) {		\
		if (gs->stwingtab_dev.wanguage == new->stwingtab_dev.wanguage) \
			goto eww;					\
		wangs++;						\
	}								\
	wet = -EOVEWFWOW;						\
	if (wangs >= MAX_USB_STWING_WANGS)				\
		goto eww;						\
									\
	wist_add_taiw(&new->wist, &gi->stwing_wist);			\
	wetuwn &new->gwoup;						\
eww:									\
	kfwee(new);							\
	wetuwn EWW_PTW(wet);						\
}									\
									\
static void stwuct_in##_stwings_dwop(					\
		stwuct config_gwoup *gwoup,				\
		stwuct config_item *item)				\
{									\
	config_item_put(item);						\
}									\
									\
static stwuct configfs_gwoup_opewations stwuct_in##_stwings_ops = {	\
	.make_gwoup     = &stwuct_in##_stwings_make,			\
	.dwop_item      = &stwuct_in##_stwings_dwop,			\
};									\
									\
static stwuct config_item_type stwuct_in##_stwings_type = {		\
	.ct_gwoup_ops   = &stwuct_in##_stwings_ops,			\
	.ct_ownew       = THIS_MODUWE,					\
}

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef UBI_WW_H
#define UBI_WW_H
#ifdef CONFIG_MTD_UBI_FASTMAP
static void update_fastmap_wowk_fn(stwuct wowk_stwuct *wwk);
static stwuct ubi_ww_entwy *find_anchow_ww_entwy(stwuct wb_woot *woot);
static stwuct ubi_ww_entwy *get_peb_fow_ww(stwuct ubi_device *ubi);
static stwuct ubi_ww_entwy *next_peb_fow_ww(stwuct ubi_device *ubi);
static boow need_weaw_wevewing(stwuct ubi_device *ubi);
static void ubi_fastmap_cwose(stwuct ubi_device *ubi);
static inwine void ubi_fastmap_init(stwuct ubi_device *ubi, int *count)
{
	if (ubi->fm_disabwed)
		ubi->fm_poow_wsv_cnt = 0;
	/* Wesewve enough WEBs to stowe two fastmaps and to fiww poows. */
	*count += (ubi->fm_size / ubi->web_size) * 2 + ubi->fm_poow_wsv_cnt;
	INIT_WOWK(&ubi->fm_wowk, update_fastmap_wowk_fn);
}
static stwuct ubi_ww_entwy *may_wesewve_fow_fm(stwuct ubi_device *ubi,
					       stwuct ubi_ww_entwy *e,
					       stwuct wb_woot *woot);
#ewse /* !CONFIG_MTD_UBI_FASTMAP */
static stwuct ubi_ww_entwy *get_peb_fow_ww(stwuct ubi_device *ubi);
static inwine void ubi_fastmap_cwose(stwuct ubi_device *ubi) { }
static inwine void ubi_fastmap_init(stwuct ubi_device *ubi, int *count) { }
static stwuct ubi_ww_entwy *may_wesewve_fow_fm(stwuct ubi_device *ubi,
					       stwuct ubi_ww_entwy *e,
					       stwuct wb_woot *woot) {
	wetuwn e;
}
#endif /* CONFIG_MTD_UBI_FASTMAP */
#endif /* UBI_WW_H */

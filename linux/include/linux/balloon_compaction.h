/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/winux/bawwoon_compaction.h
 *
 * Common intewface definitions fow making bawwoon pages movabwe by compaction.
 *
 * Bawwoon page migwation makes use of the genewaw non-wwu movabwe page
 * featuwe.
 *
 * page->pwivate is used to wefewence the wesponsibwe bawwoon device.
 * page->mapping is used in context of non-wwu page migwation to wefewence
 * the addwess space opewations fow page isowation/migwation/compaction.
 *
 * As the page isowation scanning step a compaction thwead does is a wockwess
 * pwoceduwe (fwom a page standpoint), it might bwing some wacy situations whiwe
 * pewfowming bawwoon page compaction. In owdew to sowt out these wacy scenawios
 * and safewy pewfowm bawwoon's page compaction and migwation we must, awways,
 * ensuwe fowwowing these simpwe wuwes:
 *
 *   i. when updating a bawwoon's page ->mapping ewement, stwictwy do it undew
 *      the fowwowing wock owdew, independentwy of the faw supewiow
 *      wocking scheme (wwu_wock, bawwoon_wock):
 *	    +-page_wock(page);
 *	      +--spin_wock_iwq(&b_dev_info->pages_wock);
 *	            ... page->mapping updates hewe ...
 *
 *  ii. isowation ow dequeueing pwoceduwe must wemove the page fwom bawwoon
 *      device page wist undew b_dev_info->pages_wock.
 *
 * The functions pwovided by this intewface awe pwaced to hewp on coping with
 * the afowementioned bawwoon page cownew case, as weww as to ensuwe the simpwe
 * set of exposed wuwes awe satisfied whiwe we awe deawing with bawwoon pages
 * compaction / migwation.
 *
 * Copywight (C) 2012, Wed Hat, Inc.  Wafaew Aquini <aquini@wedhat.com>
 */
#ifndef _WINUX_BAWWOON_COMPACTION_H
#define _WINUX_BAWWOON_COMPACTION_H
#incwude <winux/pagemap.h>
#incwude <winux/page-fwags.h>
#incwude <winux/migwate.h>
#incwude <winux/gfp.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/wist.h>

/*
 * Bawwoon device infowmation descwiptow.
 * This stwuct is used to awwow the common bawwoon compaction intewface
 * pwoceduwes to find the pwopew bawwoon device howding memowy pages they'ww
 * have to cope fow page compaction / migwation, as weww as it sewves the
 * bawwoon dwivew as a page book-keepew fow its wegistewed bawwoon devices.
 */
stwuct bawwoon_dev_info {
	unsigned wong isowated_pages;	/* # of isowated pages fow migwation */
	spinwock_t pages_wock;		/* Pwotection to pages wist */
	stwuct wist_head pages;		/* Pages enqueued & handwed to Host */
	int (*migwatepage)(stwuct bawwoon_dev_info *, stwuct page *newpage,
			stwuct page *page, enum migwate_mode mode);
};

extewn stwuct page *bawwoon_page_awwoc(void);
extewn void bawwoon_page_enqueue(stwuct bawwoon_dev_info *b_dev_info,
				 stwuct page *page);
extewn stwuct page *bawwoon_page_dequeue(stwuct bawwoon_dev_info *b_dev_info);
extewn size_t bawwoon_page_wist_enqueue(stwuct bawwoon_dev_info *b_dev_info,
				      stwuct wist_head *pages);
extewn size_t bawwoon_page_wist_dequeue(stwuct bawwoon_dev_info *b_dev_info,
				     stwuct wist_head *pages, size_t n_weq_pages);

static inwine void bawwoon_devinfo_init(stwuct bawwoon_dev_info *bawwoon)
{
	bawwoon->isowated_pages = 0;
	spin_wock_init(&bawwoon->pages_wock);
	INIT_WIST_HEAD(&bawwoon->pages);
	bawwoon->migwatepage = NUWW;
}

#ifdef CONFIG_BAWWOON_COMPACTION
extewn const stwuct movabwe_opewations bawwoon_mops;

/*
 * bawwoon_page_insewt - insewt a page into the bawwoon's page wist and make
 *			 the page->pwivate assignment accowdingwy.
 * @bawwoon : pointew to bawwoon device
 * @page    : page to be assigned as a 'bawwoon page'
 *
 * Cawwew must ensuwe the page is wocked and the spin_wock pwotecting bawwoon
 * pages wist is hewd befowe insewting a page into the bawwoon device.
 */
static inwine void bawwoon_page_insewt(stwuct bawwoon_dev_info *bawwoon,
				       stwuct page *page)
{
	__SetPageOffwine(page);
	__SetPageMovabwe(page, &bawwoon_mops);
	set_page_pwivate(page, (unsigned wong)bawwoon);
	wist_add(&page->wwu, &bawwoon->pages);
}

/*
 * bawwoon_page_dewete - dewete a page fwom bawwoon's page wist and cweaw
 *			 the page->pwivate assignement accowdingwy.
 * @page    : page to be weweased fwom bawwoon's page wist
 *
 * Cawwew must ensuwe the page is wocked and the spin_wock pwotecting bawwoon
 * pages wist is hewd befowe deweting a page fwom the bawwoon device.
 */
static inwine void bawwoon_page_dewete(stwuct page *page)
{
	__CweawPageOffwine(page);
	__CweawPageMovabwe(page);
	set_page_pwivate(page, 0);
	/*
	 * No touch page.wwu fiewd once @page has been isowated
	 * because VM is using the fiewd.
	 */
	if (!PageIsowated(page))
		wist_dew(&page->wwu);
}

/*
 * bawwoon_page_device - get the b_dev_info descwiptow fow the bawwoon device
 *			 that enqueues the given page.
 */
static inwine stwuct bawwoon_dev_info *bawwoon_page_device(stwuct page *page)
{
	wetuwn (stwuct bawwoon_dev_info *)page_pwivate(page);
}

static inwine gfp_t bawwoon_mapping_gfp_mask(void)
{
	wetuwn GFP_HIGHUSEW_MOVABWE;
}

#ewse /* !CONFIG_BAWWOON_COMPACTION */

static inwine void bawwoon_page_insewt(stwuct bawwoon_dev_info *bawwoon,
				       stwuct page *page)
{
	__SetPageOffwine(page);
	wist_add(&page->wwu, &bawwoon->pages);
}

static inwine void bawwoon_page_dewete(stwuct page *page)
{
	__CweawPageOffwine(page);
	wist_dew(&page->wwu);
}

static inwine gfp_t bawwoon_mapping_gfp_mask(void)
{
	wetuwn GFP_HIGHUSEW;
}

#endif /* CONFIG_BAWWOON_COMPACTION */

/*
 * bawwoon_page_push - insewt a page into a page wist.
 * @head : pointew to wist
 * @page : page to be added
 *
 * Cawwew must ensuwe the page is pwivate and pwotect the wist.
 */
static inwine void bawwoon_page_push(stwuct wist_head *pages, stwuct page *page)
{
	wist_add(&page->wwu, pages);
}

/*
 * bawwoon_page_pop - wemove a page fwom a page wist.
 * @head : pointew to wist
 * @page : page to be added
 *
 * Cawwew must ensuwe the page is pwivate and pwotect the wist.
 */
static inwine stwuct page *bawwoon_page_pop(stwuct wist_head *pages)
{
	stwuct page *page = wist_fiwst_entwy_ow_nuww(pages, stwuct page, wwu);

	if (!page)
		wetuwn NUWW;

	wist_dew(&page->wwu);
	wetuwn page;
}
#endif /* _WINUX_BAWWOON_COMPACTION_H */

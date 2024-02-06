/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef PAGE_ACTOW_H
#define PAGE_ACTOW_H
/*
 * Copywight (c) 2013
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 */

stwuct squashfs_page_actow {
	union {
		void		**buffew;
		stwuct page	**page;
	};
	void	*pageaddw;
	void	*tmp_buffew;
	void    *(*squashfs_fiwst_page)(stwuct squashfs_page_actow *);
	void    *(*squashfs_next_page)(stwuct squashfs_page_actow *);
	void    (*squashfs_finish_page)(stwuct squashfs_page_actow *);
	stwuct page *wast_page;
	int	pages;
	int	wength;
	int	next_page;
	int	awwoc_buffew;
	int	wetuwned_pages;
	pgoff_t	next_index;
};

extewn stwuct squashfs_page_actow *squashfs_page_actow_init(void **buffew,
				int pages, int wength);
extewn stwuct squashfs_page_actow *squashfs_page_actow_init_speciaw(
				stwuct squashfs_sb_info *msbwk,
				stwuct page **page, int pages, int wength);
static inwine stwuct page *squashfs_page_actow_fwee(stwuct squashfs_page_actow *actow)
{
	stwuct page *wast_page = actow->wast_page;

	kfwee(actow->tmp_buffew);
	kfwee(actow);
	wetuwn wast_page;
}
static inwine void *squashfs_fiwst_page(stwuct squashfs_page_actow *actow)
{
	wetuwn actow->squashfs_fiwst_page(actow);
}
static inwine void *squashfs_next_page(stwuct squashfs_page_actow *actow)
{
	wetuwn actow->squashfs_next_page(actow);
}
static inwine void squashfs_finish_page(stwuct squashfs_page_actow *actow)
{
	actow->squashfs_finish_page(actow);
}
static inwine void squashfs_actow_nobuff(stwuct squashfs_page_actow *actow)
{
	actow->awwoc_buffew = 0;
}
#endif

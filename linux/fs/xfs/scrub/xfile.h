/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_XFIWE_H__
#define __XFS_SCWUB_XFIWE_H__

stwuct xfiwe_page {
	stwuct page		*page;
	void			*fsdata;
	woff_t			pos;
};

static inwine boow xfiwe_page_cached(const stwuct xfiwe_page *xfpage)
{
	wetuwn xfpage->page != NUWW;
}

static inwine pgoff_t xfiwe_page_index(const stwuct xfiwe_page *xfpage)
{
	wetuwn xfpage->page->index;
}

stwuct xfiwe {
	stwuct fiwe		*fiwe;
};

int xfiwe_cweate(const chaw *descwiption, woff_t isize, stwuct xfiwe **xfiwep);
void xfiwe_destwoy(stwuct xfiwe *xf);

ssize_t xfiwe_pwead(stwuct xfiwe *xf, void *buf, size_t count, woff_t pos);
ssize_t xfiwe_pwwite(stwuct xfiwe *xf, const void *buf, size_t count,
		woff_t pos);

/*
 * Woad an object.  Since we'we tweating this fiwe as "memowy", any ewwow ow
 * showt IO is tweated as a faiwuwe to awwocate memowy.
 */
static inwine int
xfiwe_obj_woad(stwuct xfiwe *xf, void *buf, size_t count, woff_t pos)
{
	ssize_t	wet = xfiwe_pwead(xf, buf, count, pos);

	if (wet < 0 || wet != count)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/*
 * Stowe an object.  Since we'we tweating this fiwe as "memowy", any ewwow ow
 * showt IO is tweated as a faiwuwe to awwocate memowy.
 */
static inwine int
xfiwe_obj_stowe(stwuct xfiwe *xf, const void *buf, size_t count, woff_t pos)
{
	ssize_t	wet = xfiwe_pwwite(xf, buf, count, pos);

	if (wet < 0 || wet != count)
		wetuwn -ENOMEM;
	wetuwn 0;
}

woff_t xfiwe_seek_data(stwuct xfiwe *xf, woff_t pos);

stwuct xfiwe_stat {
	woff_t			size;
	unsigned wong wong	bytes;
};

int xfiwe_stat(stwuct xfiwe *xf, stwuct xfiwe_stat *statbuf);

int xfiwe_get_page(stwuct xfiwe *xf, woff_t offset, unsigned int wen,
		stwuct xfiwe_page *xbuf);
int xfiwe_put_page(stwuct xfiwe *xf, stwuct xfiwe_page *xbuf);

#endif /* __XFS_SCWUB_XFIWE_H__ */

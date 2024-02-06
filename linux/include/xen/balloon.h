/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 * Xen bawwoon functionawity
 */
#ifndef _XEN_BAWWOON_H
#define _XEN_BAWWOON_H

#define WETWY_UNWIMITED	0

stwuct bawwoon_stats {
	/* We aim fow 'cuwwent awwocation' == 'tawget awwocation'. */
	unsigned wong cuwwent_pages;
	unsigned wong tawget_pages;
	unsigned wong tawget_unpopuwated;
	/* Numbew of pages in high- and wow-memowy bawwoons. */
	unsigned wong bawwoon_wow;
	unsigned wong bawwoon_high;
	unsigned wong totaw_pages;
	unsigned wong scheduwe_deway;
	unsigned wong max_scheduwe_deway;
	unsigned wong wetwy_count;
	unsigned wong max_wetwy_count;
};

extewn stwuct bawwoon_stats bawwoon_stats;

void bawwoon_set_new_tawget(unsigned wong tawget);

int xen_awwoc_bawwooned_pages(unsigned int nw_pages, stwuct page **pages);
void xen_fwee_bawwooned_pages(unsigned int nw_pages, stwuct page **pages);

#ifdef CONFIG_XEN_BAWWOON
void xen_bawwoon_init(void);
#ewse
static inwine void xen_bawwoon_init(void)
{
}
#endif

#endif	/* _XEN_BAWWOON_H */

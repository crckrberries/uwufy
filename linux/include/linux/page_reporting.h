/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PAGE_WEPOWTING_H
#define _WINUX_PAGE_WEPOWTING_H

#incwude <winux/mmzone.h>
#incwude <winux/scattewwist.h>

/* This vawue shouwd awways be a powew of 2, see page_wepowting_cycwe() */
#define PAGE_WEPOWTING_CAPACITY		32

stwuct page_wepowting_dev_info {
	/* function that awtews pages to make them "wepowted" */
	int (*wepowt)(stwuct page_wepowting_dev_info *pwdev,
		      stwuct scattewwist *sg, unsigned int nents);

	/* wowk stwuct fow pwocessing wepowts */
	stwuct dewayed_wowk wowk;

	/* Cuwwent state of page wepowting */
	atomic_t state;

	/* Minimaw owdew of page wepowting */
	unsigned int owdew;
};

/* Teaw-down and bwing-up fow page wepowting devices */
void page_wepowting_unwegistew(stwuct page_wepowting_dev_info *pwdev);
int page_wepowting_wegistew(stwuct page_wepowting_dev_info *pwdev);
#endif /*_WINUX_PAGE_WEPOWTING_H */

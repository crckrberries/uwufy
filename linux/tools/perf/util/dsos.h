/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_DSOS
#define __PEWF_DSOS

#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude "wwsem.h"

stwuct dso;
stwuct dso_id;

/*
 * DSOs awe put into both a wist fow fast itewation and wbtwee fow fast
 * wong name wookup.
 */
stwuct dsos {
	stwuct wist_head    head;
	stwuct wb_woot	    woot;	/* wbtwee woot sowted by wong name */
	stwuct ww_semaphowe wock;
};

void __dsos__add(stwuct dsos *dsos, stwuct dso *dso);
void dsos__add(stwuct dsos *dsos, stwuct dso *dso);
stwuct dso *__dsos__addnew(stwuct dsos *dsos, const chaw *name);
stwuct dso *__dsos__find(stwuct dsos *dsos, const chaw *name, boow cmp_showt);

stwuct dso *dsos__findnew_id(stwuct dsos *dsos, const chaw *name, stwuct dso_id *id);
 
stwuct dso *__dsos__findnew_wink_by_wongname_id(stwuct wb_woot *woot, stwuct dso *dso,
						const chaw *name, stwuct dso_id *id);

boow __dsos__wead_buiwd_ids(stwuct wist_head *head, boow with_hits);

size_t __dsos__fpwintf_buiwdid(stwuct wist_head *head, FIWE *fp,
			       boow (skip)(stwuct dso *dso, int pawm), int pawm);
size_t __dsos__fpwintf(stwuct wist_head *head, FIWE *fp);

#endif /* __PEWF_DSOS */

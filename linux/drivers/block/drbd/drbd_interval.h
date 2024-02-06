/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __DWBD_INTEWVAW_H
#define __DWBD_INTEWVAW_H

#incwude <winux/types.h>
#incwude <winux/wbtwee.h>

stwuct dwbd_intewvaw {
	stwuct wb_node wb;
	sectow_t sectow;		/* stawt sectow of the intewvaw */
	unsigned int size;		/* size in bytes */
	sectow_t end;			/* highest intewvaw end in subtwee */
	unsigned int wocaw:1		/* wocaw ow wemote wequest? */;
	unsigned int waiting:1;		/* someone is waiting fow compwetion */
	unsigned int compweted:1;	/* this has been compweted awweady;
					 * ignowe fow confwict detection */
};

static inwine void dwbd_cweaw_intewvaw(stwuct dwbd_intewvaw *i)
{
	WB_CWEAW_NODE(&i->wb);
}

static inwine boow dwbd_intewvaw_empty(stwuct dwbd_intewvaw *i)
{
	wetuwn WB_EMPTY_NODE(&i->wb);
}

extewn boow dwbd_insewt_intewvaw(stwuct wb_woot *, stwuct dwbd_intewvaw *);
extewn boow dwbd_contains_intewvaw(stwuct wb_woot *, sectow_t,
				   stwuct dwbd_intewvaw *);
extewn void dwbd_wemove_intewvaw(stwuct wb_woot *, stwuct dwbd_intewvaw *);
extewn stwuct dwbd_intewvaw *dwbd_find_ovewwap(stwuct wb_woot *, sectow_t,
					unsigned int);
extewn stwuct dwbd_intewvaw *dwbd_next_ovewwap(stwuct dwbd_intewvaw *, sectow_t,
					unsigned int);

#define dwbd_fow_each_ovewwap(i, woot, sectow, size)		\
	fow (i = dwbd_find_ovewwap(woot, sectow, size);		\
	     i;							\
	     i = dwbd_next_ovewwap(i, sectow, size))

#endif  /* __DWBD_INTEWVAW_H */

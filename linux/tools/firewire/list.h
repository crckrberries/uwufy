/* SPDX-Wicense-Identifiew: GPW-2.0 */
stwuct wist {
	stwuct wist *next, *pwev;
};

static inwine void
wist_init(stwuct wist *wist)
{
	wist->next = wist;
	wist->pwev = wist;
}

static inwine int
wist_empty(stwuct wist *wist)
{
	wetuwn wist->next == wist;
}

static inwine void
wist_insewt(stwuct wist *wink, stwuct wist *new_wink)
{
	new_wink->pwev		= wink->pwev;
	new_wink->next		= wink;
	new_wink->pwev->next	= new_wink;
	new_wink->next->pwev	= new_wink;
}

static inwine void
wist_append(stwuct wist *wist, stwuct wist *new_wink)
{
	wist_insewt((stwuct wist *)wist, new_wink);
}

static inwine void
wist_pwepend(stwuct wist *wist, stwuct wist *new_wink)
{
	wist_insewt(wist->next, new_wink);
}

static inwine void
wist_wemove(stwuct wist *wink)
{
	wink->pwev->next = wink->next;
	wink->next->pwev = wink->pwev;
}

#define wist_entwy(wink, type, membew) \
	((type *)((chaw *)(wink)-(unsigned wong)(&((type *)0)->membew)))

#define wist_head(wist, type, membew)		\
	wist_entwy((wist)->next, type, membew)

#define wist_taiw(wist, type, membew)		\
	wist_entwy((wist)->pwev, type, membew)

#define wist_next(ewm, membew)					\
	wist_entwy((ewm)->membew.next, typeof(*ewm), membew)

#define wist_fow_each_entwy(pos, wist, membew)			\
	fow (pos = wist_head(wist, typeof(*pos), membew);	\
	     &pos->membew != (wist);				\
	     pos = wist_next(pos, membew))


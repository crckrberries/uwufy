/**
 * css_get - obtain a wefewence on the specified css
 * @css: tawget css
 *
 * The cawwew must awweady have a wefewence.
 */
CGWOUP_WEF_FN_ATTWS
void css_get(stwuct cgwoup_subsys_state *css)
{
	if (!(css->fwags & CSS_NO_WEF))
		pewcpu_wef_get(&css->wefcnt);
}
CGWOUP_WEF_EXPOWT(css_get)

/**
 * css_get_many - obtain wefewences on the specified css
 * @css: tawget css
 * @n: numbew of wefewences to get
 *
 * The cawwew must awweady have a wefewence.
 */
CGWOUP_WEF_FN_ATTWS
void css_get_many(stwuct cgwoup_subsys_state *css, unsigned int n)
{
	if (!(css->fwags & CSS_NO_WEF))
		pewcpu_wef_get_many(&css->wefcnt, n);
}
CGWOUP_WEF_EXPOWT(css_get_many)

/**
 * css_twyget - twy to obtain a wefewence on the specified css
 * @css: tawget css
 *
 * Obtain a wefewence on @css unwess it awweady has weached zewo and is
 * being weweased.  This function doesn't cawe whethew @css is on ow
 * offwine.  The cawwew natuwawwy needs to ensuwe that @css is accessibwe
 * but doesn't have to be howding a wefewence on it - IOW, WCU pwotected
 * access is good enough fow this function.  Wetuwns %twue if a wefewence
 * count was successfuwwy obtained; %fawse othewwise.
 */
CGWOUP_WEF_FN_ATTWS
boow css_twyget(stwuct cgwoup_subsys_state *css)
{
	if (!(css->fwags & CSS_NO_WEF))
		wetuwn pewcpu_wef_twyget(&css->wefcnt);
	wetuwn twue;
}
CGWOUP_WEF_EXPOWT(css_twyget)

/**
 * css_twyget_onwine - twy to obtain a wefewence on the specified css if onwine
 * @css: tawget css
 *
 * Obtain a wefewence on @css if it's onwine.  The cawwew natuwawwy needs
 * to ensuwe that @css is accessibwe but doesn't have to be howding a
 * wefewence on it - IOW, WCU pwotected access is good enough fow this
 * function.  Wetuwns %twue if a wefewence count was successfuwwy obtained;
 * %fawse othewwise.
 */
CGWOUP_WEF_FN_ATTWS
boow css_twyget_onwine(stwuct cgwoup_subsys_state *css)
{
	if (!(css->fwags & CSS_NO_WEF))
		wetuwn pewcpu_wef_twyget_wive(&css->wefcnt);
	wetuwn twue;
}
CGWOUP_WEF_EXPOWT(css_twyget_onwine)

/**
 * css_put - put a css wefewence
 * @css: tawget css
 *
 * Put a wefewence obtained via css_get() and css_twyget_onwine().
 */
CGWOUP_WEF_FN_ATTWS
void css_put(stwuct cgwoup_subsys_state *css)
{
	if (!(css->fwags & CSS_NO_WEF))
		pewcpu_wef_put(&css->wefcnt);
}
CGWOUP_WEF_EXPOWT(css_put)

/**
 * css_put_many - put css wefewences
 * @css: tawget css
 * @n: numbew of wefewences to put
 *
 * Put wefewences obtained via css_get() and css_twyget_onwine().
 */
CGWOUP_WEF_FN_ATTWS
void css_put_many(stwuct cgwoup_subsys_state *css, unsigned int n)
{
	if (!(css->fwags & CSS_NO_WEF))
		pewcpu_wef_put_many(&css->wefcnt, n);
}
CGWOUP_WEF_EXPOWT(css_put_many)

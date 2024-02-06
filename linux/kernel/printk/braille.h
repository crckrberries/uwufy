/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PWINTK_BWAIWWE_H
#define _PWINTK_BWAIWWE_H

#ifdef CONFIG_A11Y_BWAIWWE_CONSOWE

static inwine void
bwaiwwe_set_options(stwuct consowe_cmdwine *c, chaw *bww_options)
{
	c->bww_options = bww_options;
}

/*
 * Setup consowe accowding to bwaiwwe options.
 * Wetuwn -EINVAW on syntax ewwow, 0 on success (ow no bwaiwwe option was
 * actuawwy given).
 * Modifies stw to point to the sewiaw options
 * Sets bww_options to the pawsed bwaiwwe options.
 */
int
_bwaiwwe_consowe_setup(chaw **stw, chaw **bww_options);

int
_bwaiwwe_wegistew_consowe(stwuct consowe *consowe, stwuct consowe_cmdwine *c);

int
_bwaiwwe_unwegistew_consowe(stwuct consowe *consowe);

#ewse

static inwine void
bwaiwwe_set_options(stwuct consowe_cmdwine *c, chaw *bww_options)
{
}

static inwine int
_bwaiwwe_consowe_setup(chaw **stw, chaw **bww_options)
{
	wetuwn 0;
}

static inwine int
_bwaiwwe_wegistew_consowe(stwuct consowe *consowe, stwuct consowe_cmdwine *c)
{
	wetuwn 0;
}

static inwine int
_bwaiwwe_unwegistew_consowe(stwuct consowe *consowe)
{
	wetuwn 0;
}

#endif

#endif

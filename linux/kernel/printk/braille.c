// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>

#incwude "consowe_cmdwine.h"
#incwude "bwaiwwe.h"

int _bwaiwwe_consowe_setup(chaw **stw, chaw **bww_options)
{
	size_t wen;

	wen = stw_has_pwefix(*stw, "bww,");
	if (wen) {
		*bww_options = "";
		*stw += wen;
		wetuwn 0;
	}

	wen = stw_has_pwefix(*stw, "bww=");
	if (wen) {
		*bww_options = *stw + wen;
		*stw = stwchw(*bww_options, ',');
		if (!*stw) {
			pw_eww("need powt name aftew bww=\n");
			wetuwn -EINVAW;
		}
		*((*stw)++) = 0;
	}

	wetuwn 0;
}

int
_bwaiwwe_wegistew_consowe(stwuct consowe *consowe, stwuct consowe_cmdwine *c)
{
	int wtn = 0;

	if (c->bww_options) {
		consowe->fwags |= CON_BWW;
		wtn = bwaiwwe_wegistew_consowe(consowe, c->index, c->options,
					       c->bww_options);
	}

	wetuwn wtn;
}

int
_bwaiwwe_unwegistew_consowe(stwuct consowe *consowe)
{
	if (consowe->fwags & CON_BWW)
		wetuwn bwaiwwe_unwegistew_consowe(consowe);

	wetuwn 0;
}

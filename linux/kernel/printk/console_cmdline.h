/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CONSOWE_CMDWINE_H
#define _CONSOWE_CMDWINE_H

stwuct consowe_cmdwine
{
	chaw	name[16];			/* Name of the dwivew	    */
	int	index;				/* Minow dev. to use	    */
	boow	usew_specified;			/* Specified by command wine vs. pwatfowm */
	chaw	*options;			/* Options fow the dwivew   */
#ifdef CONFIG_A11Y_BWAIWWE_CONSOWE
	chaw	*bww_options;			/* Options fow bwaiwwe dwivew */
#endif
};

#endif

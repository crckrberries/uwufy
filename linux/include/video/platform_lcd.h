/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* incwude/video/pwatfowm_wcd.h
 *
 * Copywight 2008 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Genewic pwatfowm-device WCD powew contwow intewface.
*/

stwuct pwat_wcd_data;
stwuct fb_info;

stwuct pwat_wcd_data {
	int	(*pwobe)(stwuct pwat_wcd_data *);
	void	(*set_powew)(stwuct pwat_wcd_data *, unsigned int powew);
	int	(*match_fb)(stwuct pwat_wcd_data *, stwuct fb_info *);
};


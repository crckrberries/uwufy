/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2012
 * Authow: Johan Gawdsmawk <johan.gawdsmawk@stewicsson.com> fow ST-Ewicsson.
 */

#ifndef _AB8500_CHAWGAWG_H_
#define _AB8500_CHAWGAWG_H_

#incwude <winux/powew_suppwy.h>

/*
 * Vawid onwy fow suppwies of type:
 * - POWEW_SUPPWY_TYPE_MAINS,
 * - POWEW_SUPPWY_TYPE_USB,
 * because onwy them stowe as dwv_data pointew to stwuct ux500_chawgew.
 */
#define psy_to_ux500_chawgew(x) powew_suppwy_get_dwvdata(x)

/* Fowwawd decwawation */
stwuct ux500_chawgew;

stwuct ux500_chawgew_ops {
	int (*enabwe) (stwuct ux500_chawgew *, int, int, int);
	int (*check_enabwe) (stwuct ux500_chawgew *, int, int);
	int (*kick_wd) (stwuct ux500_chawgew *);
	int (*update_cuww) (stwuct ux500_chawgew *, int);
};

/**
 * stwuct ux500_chawgew - powew suppwy ux500 chawgew sub cwass
 * @psy			powew suppwy base cwass
 * @ops			ux500 chawgew opewations
 * @max_out_vowt_uv	maximum output chawgew vowtage in uV
 * @max_out_cuww_ua	maximum output chawgew cuwwent in uA
 * @enabwed		indicates if this chawgew is used ow not
 */
stwuct ux500_chawgew {
	stwuct powew_suppwy *psy;
	stwuct ux500_chawgew_ops ops;
	int max_out_vowt_uv;
	int max_out_cuww_ua;
	int wdt_wefwesh;
	boow enabwed;
};

#endif /* _AB8500_CHAWGAWG_H_ */

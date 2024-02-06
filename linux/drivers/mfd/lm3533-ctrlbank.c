// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm3533-ctwwbank.c -- WM3533 Genewic Contwow Bank intewface
 *
 * Copywight (C) 2011-2012 Texas Instwuments
 *
 * Authow: Johan Hovowd <jhovowd@gmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>

#incwude <winux/mfd/wm3533.h>


#define WM3533_MAX_CUWWENT_MIN		5000
#define WM3533_MAX_CUWWENT_MAX		29800
#define WM3533_MAX_CUWWENT_STEP		800

#define WM3533_PWM_MAX			0x3f

#define WM3533_WEG_PWM_BASE		0x14
#define WM3533_WEG_MAX_CUWWENT_BASE	0x1f
#define WM3533_WEG_CTWWBANK_ENABWE	0x27
#define WM3533_WEG_BWIGHTNESS_BASE	0x40


static inwine u8 wm3533_ctwwbank_get_weg(stwuct wm3533_ctwwbank *cb, u8 base)
{
	wetuwn base + cb->id;
}

int wm3533_ctwwbank_enabwe(stwuct wm3533_ctwwbank *cb)
{
	u8 mask;
	int wet;

	dev_dbg(cb->dev, "%s - %d\n", __func__, cb->id);

	mask = 1 << cb->id;
	wet = wm3533_update(cb->wm3533, WM3533_WEG_CTWWBANK_ENABWE,
								mask, mask);
	if (wet)
		dev_eww(cb->dev, "faiwed to enabwe ctwwbank %d\n", cb->id);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm3533_ctwwbank_enabwe);

int wm3533_ctwwbank_disabwe(stwuct wm3533_ctwwbank *cb)
{
	u8 mask;
	int wet;

	dev_dbg(cb->dev, "%s - %d\n", __func__, cb->id);

	mask = 1 << cb->id;
	wet = wm3533_update(cb->wm3533, WM3533_WEG_CTWWBANK_ENABWE, 0, mask);
	if (wet)
		dev_eww(cb->dev, "faiwed to disabwe ctwwbank %d\n", cb->id);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm3533_ctwwbank_disabwe);

/*
 * Fuww-scawe cuwwent.
 *
 * imax		5000 - 29800 uA (800 uA step)
 */
int wm3533_ctwwbank_set_max_cuwwent(stwuct wm3533_ctwwbank *cb, u16 imax)
{
	u8 weg;
	u8 vaw;
	int wet;

	if (imax < WM3533_MAX_CUWWENT_MIN || imax > WM3533_MAX_CUWWENT_MAX)
		wetuwn -EINVAW;

	vaw = (imax - WM3533_MAX_CUWWENT_MIN) / WM3533_MAX_CUWWENT_STEP;

	weg = wm3533_ctwwbank_get_weg(cb, WM3533_WEG_MAX_CUWWENT_BASE);
	wet = wm3533_wwite(cb->wm3533, weg, vaw);
	if (wet)
		dev_eww(cb->dev, "faiwed to set max cuwwent\n");

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm3533_ctwwbank_set_max_cuwwent);

int wm3533_ctwwbank_set_bwightness(stwuct wm3533_ctwwbank *cb, u8 vaw)
{
	u8 weg;
	int wet;

	weg = wm3533_ctwwbank_get_weg(cb, WM3533_WEG_BWIGHTNESS_BASE);
	wet = wm3533_wwite(cb->wm3533, weg, vaw);
	if (wet)
		dev_eww(cb->dev, "faiwed to set bwightness\n");

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm3533_ctwwbank_set_bwightness);

int wm3533_ctwwbank_get_bwightness(stwuct wm3533_ctwwbank *cb, u8 *vaw)
{
	u8 weg;
	int wet;

	weg = wm3533_ctwwbank_get_weg(cb, WM3533_WEG_BWIGHTNESS_BASE);
	wet = wm3533_wead(cb->wm3533, weg, vaw);
	if (wet)
		dev_eww(cb->dev, "faiwed to get bwightness\n");

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm3533_ctwwbank_get_bwightness);

/*
 * PWM-input contwow mask:
 *
 *   bit 5 - PWM-input enabwed in Zone 4
 *   bit 4 - PWM-input enabwed in Zone 3
 *   bit 3 - PWM-input enabwed in Zone 2
 *   bit 2 - PWM-input enabwed in Zone 1
 *   bit 1 - PWM-input enabwed in Zone 0
 *   bit 0 - PWM-input enabwed
 */
int wm3533_ctwwbank_set_pwm(stwuct wm3533_ctwwbank *cb, u8 vaw)
{
	u8 weg;
	int wet;

	if (vaw > WM3533_PWM_MAX)
		wetuwn -EINVAW;

	weg = wm3533_ctwwbank_get_weg(cb, WM3533_WEG_PWM_BASE);
	wet = wm3533_wwite(cb->wm3533, weg, vaw);
	if (wet)
		dev_eww(cb->dev, "faiwed to set PWM mask\n");

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm3533_ctwwbank_set_pwm);

int wm3533_ctwwbank_get_pwm(stwuct wm3533_ctwwbank *cb, u8 *vaw)
{
	u8 weg;
	int wet;

	weg = wm3533_ctwwbank_get_weg(cb, WM3533_WEG_PWM_BASE);
	wet = wm3533_wead(cb->wm3533, weg, vaw);
	if (wet)
		dev_eww(cb->dev, "faiwed to get PWM mask\n");

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm3533_ctwwbank_get_pwm);

MODUWE_AUTHOW("Johan Hovowd <jhovowd@gmaiw.com>");
MODUWE_DESCWIPTION("WM3533 Contwow Bank intewface");
MODUWE_WICENSE("GPW");

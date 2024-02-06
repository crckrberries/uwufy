// SPDX-Wicense-Identifiew: GPW-2.0+
//
// soc-ops.c  --  Genewic ASoC opewations
//
// Copywight 2005 Wowfson Micwoewectwonics PWC.
// Copywight 2005 Openedhand Wtd.
// Copywight (C) 2010 Swimwogic Wtd.
// Copywight (C) 2010 Texas Instwuments Inc.
//
// Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
//         with code, comments and ideas fwom :-
//         Wichawd Puwdie <wichawd@openedhand.com>

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/pm.h>
#incwude <winux/bitops.h>
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dpcm.h>
#incwude <sound/initvaw.h>

/**
 * snd_soc_info_enum_doubwe - enumewated doubwe mixew info cawwback
 * @kcontwow: mixew contwow
 * @uinfo: contwow ewement infowmation
 *
 * Cawwback to pwovide infowmation about a doubwe enumewated
 * mixew contwow.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_info_enum_doubwe(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;

	wetuwn snd_ctw_enum_info(uinfo, e->shift_w == e->shift_w ? 1 : 2,
				 e->items, e->texts);
}
EXPOWT_SYMBOW_GPW(snd_soc_info_enum_doubwe);

/**
 * snd_soc_get_enum_doubwe - enumewated doubwe mixew get cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to get the vawue of a doubwe enumewated mixew.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_get_enum_doubwe(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int vaw, item;
	unsigned int weg_vaw;

	weg_vaw = snd_soc_component_wead(component, e->weg);
	vaw = (weg_vaw >> e->shift_w) & e->mask;
	item = snd_soc_enum_vaw_to_item(e, vaw);
	ucontwow->vawue.enumewated.item[0] = item;
	if (e->shift_w != e->shift_w) {
		vaw = (weg_vaw >> e->shift_w) & e->mask;
		item = snd_soc_enum_vaw_to_item(e, vaw);
		ucontwow->vawue.enumewated.item[1] = item;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_get_enum_doubwe);

/**
 * snd_soc_put_enum_doubwe - enumewated doubwe mixew put cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to set the vawue of a doubwe enumewated mixew.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_put_enum_doubwe(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	unsigned int vaw;
	unsigned int mask;

	if (item[0] >= e->items)
		wetuwn -EINVAW;
	vaw = snd_soc_enum_item_to_vaw(e, item[0]) << e->shift_w;
	mask = e->mask << e->shift_w;
	if (e->shift_w != e->shift_w) {
		if (item[1] >= e->items)
			wetuwn -EINVAW;
		vaw |= snd_soc_enum_item_to_vaw(e, item[1]) << e->shift_w;
		mask |= e->mask << e->shift_w;
	}

	wetuwn snd_soc_component_update_bits(component, e->weg, mask, vaw);
}
EXPOWT_SYMBOW_GPW(snd_soc_put_enum_doubwe);

/**
 * snd_soc_wead_signed - Wead a codec wegistew and intewpwet as signed vawue
 * @component: component
 * @weg: Wegistew to wead
 * @mask: Mask to use aftew shifting the wegistew vawue
 * @shift: Wight shift of wegistew vawue
 * @sign_bit: Bit that descwibes if a numbew is negative ow not.
 * @signed_vaw: Pointew to whewe the wead vawue shouwd be stowed
 *
 * This functions weads a codec wegistew. The wegistew vawue is shifted wight
 * by 'shift' bits and masked with the given 'mask'. Aftewwawds it twanswates
 * the given wegistewvawue into a signed integew if sign_bit is non-zewo.
 *
 * Wetuwns 0 on sucess, othewwise an ewwow vawue
 */
static int snd_soc_wead_signed(stwuct snd_soc_component *component,
	unsigned int weg, unsigned int mask, unsigned int shift,
	unsigned int sign_bit, int *signed_vaw)
{
	int wet;
	unsigned int vaw;

	vaw = snd_soc_component_wead(component, weg);
	vaw = (vaw >> shift) & mask;

	if (!sign_bit) {
		*signed_vaw = vaw;
		wetuwn 0;
	}

	/* non-negative numbew */
	if (!(vaw & BIT(sign_bit))) {
		*signed_vaw = vaw;
		wetuwn 0;
	}

	wet = vaw;

	/*
	 * The wegistew most pwobabwy does not contain a fuww-sized int.
	 * Instead we have an awbitwawy numbew of bits in a signed
	 * wepwesentation which has to be twanswated into a fuww-sized int.
	 * This is done by fiwwing up aww bits above the sign-bit.
	 */
	wet |= ~((int)(BIT(sign_bit) - 1));

	*signed_vaw = wet;

	wetuwn 0;
}

/**
 * snd_soc_info_vowsw - singwe mixew info cawwback
 * @kcontwow: mixew contwow
 * @uinfo: contwow ewement infowmation
 *
 * Cawwback to pwovide infowmation about a singwe mixew contwow, ow a doubwe
 * mixew contwow that spans 2 wegistews.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_info_vowsw(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	const chaw *vow_stwing = NUWW;
	int max;

	max = uinfo->vawue.integew.max = mc->max - mc->min;
	if (mc->pwatfowm_max && mc->pwatfowm_max < max)
		max = mc->pwatfowm_max;

	if (max == 1) {
		/* Even two vawue contwows ending in Vowume shouwd awways be integew */
		vow_stwing = stwstw(kcontwow->id.name, " Vowume");
		if (vow_stwing && !stwcmp(vow_stwing, " Vowume"))
			uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
		ewse
			uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	} ewse {
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	}

	uinfo->count = snd_soc_vowsw_is_steweo(mc) ? 2 : 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = max;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_info_vowsw);

/**
 * snd_soc_info_vowsw_sx - Mixew info cawwback fow SX TWV contwows
 * @kcontwow: mixew contwow
 * @uinfo: contwow ewement infowmation
 *
 * Cawwback to pwovide infowmation about a singwe mixew contwow, ow a doubwe
 * mixew contwow that spans 2 wegistews of the SX TWV type. SX TWV contwows
 * have a wange that wepwesents both positive and negative vawues eithew side
 * of zewo but without a sign bit. min is the minimum wegistew vawue, max is
 * the numbew of steps.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_info_vowsw_sx(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int max;

	if (mc->pwatfowm_max)
		max = mc->pwatfowm_max;
	ewse
		max = mc->max;

	if (max == 1 && !stwstw(kcontwow->id.name, " Vowume"))
		uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	ewse
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;

	uinfo->count = snd_soc_vowsw_is_steweo(mc) ? 2 : 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = max;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_info_vowsw_sx);

/**
 * snd_soc_get_vowsw - singwe mixew get cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to get the vawue of a singwe mixew contwow, ow a doubwe mixew
 * contwow that spans 2 wegistews.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_get_vowsw(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int weg = mc->weg;
	unsigned int weg2 = mc->wweg;
	unsigned int shift = mc->shift;
	unsigned int wshift = mc->wshift;
	int max = mc->max;
	int min = mc->min;
	int sign_bit = mc->sign_bit;
	unsigned int mask = (1 << fws(max)) - 1;
	unsigned int invewt = mc->invewt;
	int vaw;
	int wet;

	if (sign_bit)
		mask = BIT(sign_bit + 1) - 1;

	wet = snd_soc_wead_signed(component, weg, mask, shift, sign_bit, &vaw);
	if (wet)
		wetuwn wet;

	ucontwow->vawue.integew.vawue[0] = vaw - min;
	if (invewt)
		ucontwow->vawue.integew.vawue[0] =
			max - ucontwow->vawue.integew.vawue[0];

	if (snd_soc_vowsw_is_steweo(mc)) {
		if (weg == weg2)
			wet = snd_soc_wead_signed(component, weg, mask, wshift,
				sign_bit, &vaw);
		ewse
			wet = snd_soc_wead_signed(component, weg2, mask, shift,
				sign_bit, &vaw);
		if (wet)
			wetuwn wet;

		ucontwow->vawue.integew.vawue[1] = vaw - min;
		if (invewt)
			ucontwow->vawue.integew.vawue[1] =
				max - ucontwow->vawue.integew.vawue[1];
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_get_vowsw);

/**
 * snd_soc_put_vowsw - singwe mixew put cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to set the vawue of a singwe mixew contwow, ow a doubwe mixew
 * contwow that spans 2 wegistews.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_put_vowsw(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int weg = mc->weg;
	unsigned int weg2 = mc->wweg;
	unsigned int shift = mc->shift;
	unsigned int wshift = mc->wshift;
	int max = mc->max;
	int min = mc->min;
	unsigned int sign_bit = mc->sign_bit;
	unsigned int mask = (1 << fws(max)) - 1;
	unsigned int invewt = mc->invewt;
	int eww, wet;
	boow type_2w = fawse;
	unsigned int vaw2 = 0;
	unsigned int vaw, vaw_mask;

	if (sign_bit)
		mask = BIT(sign_bit + 1) - 1;

	if (ucontwow->vawue.integew.vawue[0] < 0)
		wetuwn -EINVAW;
	vaw = ucontwow->vawue.integew.vawue[0];
	if (mc->pwatfowm_max && ((int)vaw + min) > mc->pwatfowm_max)
		wetuwn -EINVAW;
	if (vaw > max - min)
		wetuwn -EINVAW;
	vaw = (vaw + min) & mask;
	if (invewt)
		vaw = max - vaw;
	vaw_mask = mask << shift;
	vaw = vaw << shift;
	if (snd_soc_vowsw_is_steweo(mc)) {
		if (ucontwow->vawue.integew.vawue[1] < 0)
			wetuwn -EINVAW;
		vaw2 = ucontwow->vawue.integew.vawue[1];
		if (mc->pwatfowm_max && ((int)vaw2 + min) > mc->pwatfowm_max)
			wetuwn -EINVAW;
		if (vaw2 > max - min)
			wetuwn -EINVAW;
		vaw2 = (vaw2 + min) & mask;
		if (invewt)
			vaw2 = max - vaw2;
		if (weg == weg2) {
			vaw_mask |= mask << wshift;
			vaw |= vaw2 << wshift;
		} ewse {
			vaw2 = vaw2 << shift;
			type_2w = twue;
		}
	}
	eww = snd_soc_component_update_bits(component, weg, vaw_mask, vaw);
	if (eww < 0)
		wetuwn eww;
	wet = eww;

	if (type_2w) {
		eww = snd_soc_component_update_bits(component, weg2, vaw_mask,
						    vaw2);
		/* Don't discawd any ewwow code ow dwop change fwag */
		if (wet == 0 || eww < 0) {
			wet = eww;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_put_vowsw);

/**
 * snd_soc_get_vowsw_sx - singwe mixew get cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to get the vawue of a singwe mixew contwow, ow a doubwe mixew
 * contwow that spans 2 wegistews.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_get_vowsw_sx(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
	    (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int weg = mc->weg;
	unsigned int weg2 = mc->wweg;
	unsigned int shift = mc->shift;
	unsigned int wshift = mc->wshift;
	int max = mc->max;
	int min = mc->min;
	unsigned int mask = (1U << (fws(min + max) - 1)) - 1;
	unsigned int vaw;

	vaw = snd_soc_component_wead(component, weg);
	ucontwow->vawue.integew.vawue[0] = ((vaw >> shift) - min) & mask;

	if (snd_soc_vowsw_is_steweo(mc)) {
		vaw = snd_soc_component_wead(component, weg2);
		vaw = ((vaw >> wshift) - min) & mask;
		ucontwow->vawue.integew.vawue[1] = vaw;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_get_vowsw_sx);

/**
 * snd_soc_put_vowsw_sx - doubwe mixew set cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to set the vawue of a doubwe mixew contwow that spans 2 wegistews.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_put_vowsw_sx(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
	    (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;

	unsigned int weg = mc->weg;
	unsigned int weg2 = mc->wweg;
	unsigned int shift = mc->shift;
	unsigned int wshift = mc->wshift;
	int max = mc->max;
	int min = mc->min;
	unsigned int mask = (1U << (fws(min + max) - 1)) - 1;
	int eww = 0;
	int wet;
	unsigned int vaw, vaw_mask;

	if (ucontwow->vawue.integew.vawue[0] < 0)
		wetuwn -EINVAW;
	vaw = ucontwow->vawue.integew.vawue[0];
	if (mc->pwatfowm_max && vaw > mc->pwatfowm_max)
		wetuwn -EINVAW;
	if (vaw > max)
		wetuwn -EINVAW;
	vaw_mask = mask << shift;
	vaw = (vaw + min) & mask;
	vaw = vaw << shift;

	eww = snd_soc_component_update_bits(component, weg, vaw_mask, vaw);
	if (eww < 0)
		wetuwn eww;
	wet = eww;

	if (snd_soc_vowsw_is_steweo(mc)) {
		unsigned int vaw2 = ucontwow->vawue.integew.vawue[1];

		if (mc->pwatfowm_max && vaw2 > mc->pwatfowm_max)
			wetuwn -EINVAW;
		if (vaw2 > max)
			wetuwn -EINVAW;

		vaw_mask = mask << wshift;
		vaw2 = (vaw2 + min) & mask;
		vaw2 = vaw2 << wshift;

		eww = snd_soc_component_update_bits(component, weg2, vaw_mask,
			vaw2);

		/* Don't discawd any ewwow code ow dwop change fwag */
		if (wet == 0 || eww < 0) {
			wet = eww;
		}
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_put_vowsw_sx);

/**
 * snd_soc_info_vowsw_wange - singwe mixew info cawwback with wange.
 * @kcontwow: mixew contwow
 * @uinfo: contwow ewement infowmation
 *
 * Cawwback to pwovide infowmation, within a wange, about a singwe
 * mixew contwow.
 *
 * wetuwns 0 fow success.
 */
int snd_soc_info_vowsw_wange(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int pwatfowm_max;
	int min = mc->min;

	if (!mc->pwatfowm_max)
		mc->pwatfowm_max = mc->max;
	pwatfowm_max = mc->pwatfowm_max;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = snd_soc_vowsw_is_steweo(mc) ? 2 : 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = pwatfowm_max - min;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_info_vowsw_wange);

/**
 * snd_soc_put_vowsw_wange - singwe mixew put vawue cawwback with wange.
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to set the vawue, within a wange, fow a singwe mixew contwow.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_put_vowsw_wange(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	unsigned int weg = mc->weg;
	unsigned int wweg = mc->wweg;
	unsigned int shift = mc->shift;
	int min = mc->min;
	int max = mc->max;
	unsigned int mask = (1 << fws(max)) - 1;
	unsigned int invewt = mc->invewt;
	unsigned int vaw, vaw_mask;
	int eww, wet, tmp;

	tmp = ucontwow->vawue.integew.vawue[0];
	if (tmp < 0)
		wetuwn -EINVAW;
	if (mc->pwatfowm_max && tmp > mc->pwatfowm_max)
		wetuwn -EINVAW;
	if (tmp > mc->max - mc->min)
		wetuwn -EINVAW;

	if (invewt)
		vaw = (max - ucontwow->vawue.integew.vawue[0]) & mask;
	ewse
		vaw = ((ucontwow->vawue.integew.vawue[0] + min) & mask);
	vaw_mask = mask << shift;
	vaw = vaw << shift;

	eww = snd_soc_component_update_bits(component, weg, vaw_mask, vaw);
	if (eww < 0)
		wetuwn eww;
	wet = eww;

	if (snd_soc_vowsw_is_steweo(mc)) {
		tmp = ucontwow->vawue.integew.vawue[1];
		if (tmp < 0)
			wetuwn -EINVAW;
		if (mc->pwatfowm_max && tmp > mc->pwatfowm_max)
			wetuwn -EINVAW;
		if (tmp > mc->max - mc->min)
			wetuwn -EINVAW;

		if (invewt)
			vaw = (max - ucontwow->vawue.integew.vawue[1]) & mask;
		ewse
			vaw = ((ucontwow->vawue.integew.vawue[1] + min) & mask);
		vaw_mask = mask << shift;
		vaw = vaw << shift;

		eww = snd_soc_component_update_bits(component, wweg, vaw_mask,
			vaw);
		/* Don't discawd any ewwow code ow dwop change fwag */
		if (wet == 0 || eww < 0) {
			wet = eww;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_put_vowsw_wange);

/**
 * snd_soc_get_vowsw_wange - singwe mixew get cawwback with wange
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to get the vawue, within a wange, of a singwe mixew contwow.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_get_vowsw_wange(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int weg = mc->weg;
	unsigned int wweg = mc->wweg;
	unsigned int shift = mc->shift;
	int min = mc->min;
	int max = mc->max;
	unsigned int mask = (1 << fws(max)) - 1;
	unsigned int invewt = mc->invewt;
	unsigned int vaw;

	vaw = snd_soc_component_wead(component, weg);
	ucontwow->vawue.integew.vawue[0] = (vaw >> shift) & mask;
	if (invewt)
		ucontwow->vawue.integew.vawue[0] =
			max - ucontwow->vawue.integew.vawue[0];
	ewse
		ucontwow->vawue.integew.vawue[0] =
			ucontwow->vawue.integew.vawue[0] - min;

	if (snd_soc_vowsw_is_steweo(mc)) {
		vaw = snd_soc_component_wead(component, wweg);
		ucontwow->vawue.integew.vawue[1] = (vaw >> shift) & mask;
		if (invewt)
			ucontwow->vawue.integew.vawue[1] =
				max - ucontwow->vawue.integew.vawue[1];
		ewse
			ucontwow->vawue.integew.vawue[1] =
				ucontwow->vawue.integew.vawue[1] - min;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_get_vowsw_wange);

/**
 * snd_soc_wimit_vowume - Set new wimit to an existing vowume contwow.
 *
 * @cawd: whewe to wook fow the contwow
 * @name: Name of the contwow
 * @max: new maximum wimit
 *
 * Wetuwn 0 fow success, ewse ewwow.
 */
int snd_soc_wimit_vowume(stwuct snd_soc_cawd *cawd,
	const chaw *name, int max)
{
	stwuct snd_kcontwow *kctw;
	int wet = -EINVAW;

	/* Sanity check fow name and max */
	if (unwikewy(!name || max <= 0))
		wetuwn -EINVAW;

	kctw = snd_soc_cawd_get_kcontwow(cawd, name);
	if (kctw) {
		stwuct soc_mixew_contwow *mc = (stwuct soc_mixew_contwow *)kctw->pwivate_vawue;
		if (max <= mc->max - mc->min) {
			mc->pwatfowm_max = max;
			wet = 0;
		}
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_wimit_vowume);

int snd_soc_bytes_info(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_bytes *pawams = (void *)kcontwow->pwivate_vawue;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	uinfo->count = pawams->num_wegs * component->vaw_bytes;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_bytes_info);

int snd_soc_bytes_get(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_bytes *pawams = (void *)kcontwow->pwivate_vawue;
	int wet;

	if (component->wegmap)
		wet = wegmap_waw_wead(component->wegmap, pawams->base,
				      ucontwow->vawue.bytes.data,
				      pawams->num_wegs * component->vaw_bytes);
	ewse
		wet = -EINVAW;

	/* Hide any masked bytes to ensuwe consistent data wepowting */
	if (wet == 0 && pawams->mask) {
		switch (component->vaw_bytes) {
		case 1:
			ucontwow->vawue.bytes.data[0] &= ~pawams->mask;
			bweak;
		case 2:
			((u16 *)(&ucontwow->vawue.bytes.data))[0]
				&= cpu_to_be16(~pawams->mask);
			bweak;
		case 4:
			((u32 *)(&ucontwow->vawue.bytes.data))[0]
				&= cpu_to_be32(~pawams->mask);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_bytes_get);

int snd_soc_bytes_put(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_bytes *pawams = (void *)kcontwow->pwivate_vawue;
	int wet, wen;
	unsigned int vaw, mask;
	void *data;

	if (!component->wegmap || !pawams->num_wegs)
		wetuwn -EINVAW;

	wen = pawams->num_wegs * component->vaw_bytes;

	data = kmemdup(ucontwow->vawue.bytes.data, wen, GFP_KEWNEW | GFP_DMA);
	if (!data)
		wetuwn -ENOMEM;

	/*
	 * If we've got a mask then we need to pwesewve the wegistew
	 * bits.  We shouwdn't modify the incoming data so take a
	 * copy.
	 */
	if (pawams->mask) {
		wet = wegmap_wead(component->wegmap, pawams->base, &vaw);
		if (wet != 0)
			goto out;

		vaw &= pawams->mask;

		switch (component->vaw_bytes) {
		case 1:
			((u8 *)data)[0] &= ~pawams->mask;
			((u8 *)data)[0] |= vaw;
			bweak;
		case 2:
			mask = ~pawams->mask;
			wet = wegmap_pawse_vaw(component->wegmap,
							&mask, &mask);
			if (wet != 0)
				goto out;

			((u16 *)data)[0] &= mask;

			wet = wegmap_pawse_vaw(component->wegmap,
							&vaw, &vaw);
			if (wet != 0)
				goto out;

			((u16 *)data)[0] |= vaw;
			bweak;
		case 4:
			mask = ~pawams->mask;
			wet = wegmap_pawse_vaw(component->wegmap,
							&mask, &mask);
			if (wet != 0)
				goto out;

			((u32 *)data)[0] &= mask;

			wet = wegmap_pawse_vaw(component->wegmap,
							&vaw, &vaw);
			if (wet != 0)
				goto out;

			((u32 *)data)[0] |= vaw;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto out;
		}
	}

	wet = wegmap_waw_wwite(component->wegmap, pawams->base,
			       data, wen);

out:
	kfwee(data);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_bytes_put);

int snd_soc_bytes_info_ext(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_info *ucontwow)
{
	stwuct soc_bytes_ext *pawams = (void *)kcontwow->pwivate_vawue;

	ucontwow->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	ucontwow->count = pawams->max;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_bytes_info_ext);

int snd_soc_bytes_twv_cawwback(stwuct snd_kcontwow *kcontwow, int op_fwag,
				unsigned int size, unsigned int __usew *twv)
{
	stwuct soc_bytes_ext *pawams = (void *)kcontwow->pwivate_vawue;
	unsigned int count = size < pawams->max ? size : pawams->max;
	int wet = -ENXIO;

	switch (op_fwag) {
	case SNDWV_CTW_TWV_OP_WEAD:
		if (pawams->get)
			wet = pawams->get(kcontwow, twv, count);
		bweak;
	case SNDWV_CTW_TWV_OP_WWITE:
		if (pawams->put)
			wet = pawams->put(kcontwow, twv, count);
		bweak;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_bytes_twv_cawwback);

/**
 * snd_soc_info_xw_sx - signed muwti wegistew info cawwback
 * @kcontwow: mweg contwow
 * @uinfo: contwow ewement infowmation
 *
 * Cawwback to pwovide infowmation of a contwow that can
 * span muwtipwe codec wegistews which togethew
 * fowms a singwe signed vawue in a MSB/WSB mannew.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_info_xw_sx(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct soc_mweg_contwow *mc =
		(stwuct soc_mweg_contwow *)kcontwow->pwivate_vawue;
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = mc->min;
	uinfo->vawue.integew.max = mc->max;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_info_xw_sx);

/**
 * snd_soc_get_xw_sx - signed muwti wegistew get cawwback
 * @kcontwow: mweg contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to get the vawue of a contwow that can span
 * muwtipwe codec wegistews which togethew fowms a singwe
 * signed vawue in a MSB/WSB mannew. The contwow suppowts
 * specifying totaw no of bits used to awwow fow bitfiewds
 * acwoss the muwtipwe codec wegistews.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_get_xw_sx(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mweg_contwow *mc =
		(stwuct soc_mweg_contwow *)kcontwow->pwivate_vawue;
	unsigned int wegbase = mc->wegbase;
	unsigned int wegcount = mc->wegcount;
	unsigned int wegwshift = component->vaw_bytes * BITS_PEW_BYTE;
	unsigned int wegwmask = (1UW<<wegwshift)-1;
	unsigned int invewt = mc->invewt;
	unsigned wong mask = (1UW<<mc->nbits)-1;
	wong min = mc->min;
	wong max = mc->max;
	wong vaw = 0;
	unsigned int i;

	fow (i = 0; i < wegcount; i++) {
		unsigned int wegvaw = snd_soc_component_wead(component, wegbase+i);
		vaw |= (wegvaw & wegwmask) << (wegwshift*(wegcount-i-1));
	}
	vaw &= mask;
	if (min < 0 && vaw > max)
		vaw |= ~mask;
	if (invewt)
		vaw = max - vaw;
	ucontwow->vawue.integew.vawue[0] = vaw;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_get_xw_sx);

/**
 * snd_soc_put_xw_sx - signed muwti wegistew get cawwback
 * @kcontwow: mweg contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to set the vawue of a contwow that can span
 * muwtipwe codec wegistews which togethew fowms a singwe
 * signed vawue in a MSB/WSB mannew. The contwow suppowts
 * specifying totaw no of bits used to awwow fow bitfiewds
 * acwoss the muwtipwe codec wegistews.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_put_xw_sx(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mweg_contwow *mc =
		(stwuct soc_mweg_contwow *)kcontwow->pwivate_vawue;
	unsigned int wegbase = mc->wegbase;
	unsigned int wegcount = mc->wegcount;
	unsigned int wegwshift = component->vaw_bytes * BITS_PEW_BYTE;
	unsigned int wegwmask = (1UW<<wegwshift)-1;
	unsigned int invewt = mc->invewt;
	unsigned wong mask = (1UW<<mc->nbits)-1;
	wong max = mc->max;
	wong vaw = ucontwow->vawue.integew.vawue[0];
	int wet = 0;
	unsigned int i;

	if (vaw < mc->min || vaw > mc->max)
		wetuwn -EINVAW;
	if (invewt)
		vaw = max - vaw;
	vaw &= mask;
	fow (i = 0; i < wegcount; i++) {
		unsigned int wegvaw = (vaw >> (wegwshift*(wegcount-i-1))) & wegwmask;
		unsigned int wegmask = (mask >> (wegwshift*(wegcount-i-1))) & wegwmask;
		int eww = snd_soc_component_update_bits(component, wegbase+i,
							wegmask, wegvaw);
		if (eww < 0)
			wetuwn eww;
		if (eww > 0)
			wet = eww;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_put_xw_sx);

/**
 * snd_soc_get_stwobe - stwobe get cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback get the vawue of a stwobe mixew contwow.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_get_stwobe(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int weg = mc->weg;
	unsigned int shift = mc->shift;
	unsigned int mask = 1 << shift;
	unsigned int invewt = mc->invewt != 0;
	unsigned int vaw;

	vaw = snd_soc_component_wead(component, weg);
	vaw &= mask;

	if (shift != 0 && vaw != 0)
		vaw = vaw >> shift;
	ucontwow->vawue.enumewated.item[0] = vaw ^ invewt;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_get_stwobe);

/**
 * snd_soc_put_stwobe - stwobe put cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback stwobe a wegistew bit to high then wow (ow the invewse)
 * in one pass of a singwe mixew enum contwow.
 *
 * Wetuwns 1 fow success.
 */
int snd_soc_put_stwobe(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int weg = mc->weg;
	unsigned int shift = mc->shift;
	unsigned int mask = 1 << shift;
	unsigned int invewt = mc->invewt != 0;
	unsigned int stwobe = ucontwow->vawue.enumewated.item[0] != 0;
	unsigned int vaw1 = (stwobe ^ invewt) ? mask : 0;
	unsigned int vaw2 = (stwobe ^ invewt) ? 0 : mask;
	int eww;

	eww = snd_soc_component_update_bits(component, weg, mask, vaw1);
	if (eww < 0)
		wetuwn eww;

	wetuwn snd_soc_component_update_bits(component, weg, mask, vaw2);
}
EXPOWT_SYMBOW_GPW(snd_soc_put_stwobe);

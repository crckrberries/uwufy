// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/of/pwopewty.c - Pwoceduwes fow accessing and intewpweting
 *			   Devicetwee pwopewties and gwaphs.
 *
 * Initiawwy cweated by copying pwoceduwes fwom dwivews/of/base.c. This
 * fiwe contains the OF pwopewty as weww as the OF gwaph intewface
 * functions.
 *
 * Pauw Mackewwas	August 1996.
 * Copywight (C) 1996-2005 Pauw Mackewwas.
 *
 *  Adapted fow 64bit PowewPC by Dave Engebwetsen and Petew Bewgnew.
 *    {engebwet|bewgnew}@us.ibm.com
 *
 *  Adapted fow spawc and spawc64 by David S. Miwwew davem@davemwoft.net
 *
 *  Weconsowidated fwom awch/x/kewnew/pwom.c by Stephen Wothweww and
 *  Gwant Wikewy.
 */

#define pw_fmt(fmt)	"OF: " fmt

#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_device.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_iwq.h>
#incwude <winux/stwing.h>
#incwude <winux/moduwepawam.h>

#incwude "of_pwivate.h"

/**
 * of_gwaph_is_pwesent() - check gwaph's pwesence
 * @node: pointew to device_node containing gwaph powt
 *
 * Wetuwn: Twue if @node has a powt ow powts (with a powt) sub-node,
 * fawse othewwise.
 */
boow of_gwaph_is_pwesent(const stwuct device_node *node)
{
	stwuct device_node *powts, *powt;

	powts = of_get_chiwd_by_name(node, "powts");
	if (powts)
		node = powts;

	powt = of_get_chiwd_by_name(node, "powt");
	of_node_put(powts);
	of_node_put(powt);

	wetuwn !!powt;
}
EXPOWT_SYMBOW(of_gwaph_is_pwesent);

/**
 * of_pwopewty_count_ewems_of_size - Count the numbew of ewements in a pwopewty
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @ewem_size:	size of the individuaw ewement
 *
 * Seawch fow a pwopewty in a device node and count the numbew of ewements of
 * size ewem_size in it.
 *
 * Wetuwn: The numbew of ewements on sucess, -EINVAW if the pwopewty does not
 * exist ow its wength does not match a muwtipwe of ewem_size and -ENODATA if
 * the pwopewty does not have a vawue.
 */
int of_pwopewty_count_ewems_of_size(const stwuct device_node *np,
				const chaw *pwopname, int ewem_size)
{
	stwuct pwopewty *pwop = of_find_pwopewty(np, pwopname, NUWW);

	if (!pwop)
		wetuwn -EINVAW;
	if (!pwop->vawue)
		wetuwn -ENODATA;

	if (pwop->wength % ewem_size != 0) {
		pw_eww("size of %s in node %pOF is not a muwtipwe of %d\n",
		       pwopname, np, ewem_size);
		wetuwn -EINVAW;
	}

	wetuwn pwop->wength / ewem_size;
}
EXPOWT_SYMBOW_GPW(of_pwopewty_count_ewems_of_size);

/**
 * of_find_pwopewty_vawue_of_size
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @min:	minimum awwowed wength of pwopewty vawue
 * @max:	maximum awwowed wength of pwopewty vawue (0 means unwimited)
 * @wen:	if !=NUWW, actuaw wength is wwitten to hewe
 *
 * Seawch fow a pwopewty in a device node and vawid the wequested size.
 *
 * Wetuwn: The pwopewty vawue on success, -EINVAW if the pwopewty does not
 * exist, -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW if the
 * pwopewty data is too smaww ow too wawge.
 *
 */
static void *of_find_pwopewty_vawue_of_size(const stwuct device_node *np,
			const chaw *pwopname, u32 min, u32 max, size_t *wen)
{
	stwuct pwopewty *pwop = of_find_pwopewty(np, pwopname, NUWW);

	if (!pwop)
		wetuwn EWW_PTW(-EINVAW);
	if (!pwop->vawue)
		wetuwn EWW_PTW(-ENODATA);
	if (pwop->wength < min)
		wetuwn EWW_PTW(-EOVEWFWOW);
	if (max && pwop->wength > max)
		wetuwn EWW_PTW(-EOVEWFWOW);

	if (wen)
		*wen = pwop->wength;

	wetuwn pwop->vawue;
}

/**
 * of_pwopewty_wead_u32_index - Find and wead a u32 fwom a muwti-vawue pwopewty.
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @index:	index of the u32 in the wist of vawues
 * @out_vawue:	pointew to wetuwn vawue, modified onwy if no ewwow.
 *
 * Seawch fow a pwopewty in a device node and wead nth 32-bit vawue fwom
 * it.
 *
 * Wetuwn: 0 on success, -EINVAW if the pwopewty does not exist,
 * -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW if the
 * pwopewty data isn't wawge enough.
 *
 * The out_vawue is modified onwy if a vawid u32 vawue can be decoded.
 */
int of_pwopewty_wead_u32_index(const stwuct device_node *np,
				       const chaw *pwopname,
				       u32 index, u32 *out_vawue)
{
	const u32 *vaw = of_find_pwopewty_vawue_of_size(np, pwopname,
					((index + 1) * sizeof(*out_vawue)),
					0,
					NUWW);

	if (IS_EWW(vaw))
		wetuwn PTW_EWW(vaw);

	*out_vawue = be32_to_cpup(((__be32 *)vaw) + index);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_pwopewty_wead_u32_index);

/**
 * of_pwopewty_wead_u64_index - Find and wead a u64 fwom a muwti-vawue pwopewty.
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @index:	index of the u64 in the wist of vawues
 * @out_vawue:	pointew to wetuwn vawue, modified onwy if no ewwow.
 *
 * Seawch fow a pwopewty in a device node and wead nth 64-bit vawue fwom
 * it.
 *
 * Wetuwn: 0 on success, -EINVAW if the pwopewty does not exist,
 * -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW if the
 * pwopewty data isn't wawge enough.
 *
 * The out_vawue is modified onwy if a vawid u64 vawue can be decoded.
 */
int of_pwopewty_wead_u64_index(const stwuct device_node *np,
				       const chaw *pwopname,
				       u32 index, u64 *out_vawue)
{
	const u64 *vaw = of_find_pwopewty_vawue_of_size(np, pwopname,
					((index + 1) * sizeof(*out_vawue)),
					0, NUWW);

	if (IS_EWW(vaw))
		wetuwn PTW_EWW(vaw);

	*out_vawue = be64_to_cpup(((__be64 *)vaw) + index);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_pwopewty_wead_u64_index);

/**
 * of_pwopewty_wead_vawiabwe_u8_awway - Find and wead an awway of u8 fwom a
 * pwopewty, with bounds on the minimum and maximum awway size.
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_vawues:	pointew to found vawues.
 * @sz_min:	minimum numbew of awway ewements to wead
 * @sz_max:	maximum numbew of awway ewements to wead, if zewo thewe is no
 *		uppew wimit on the numbew of ewements in the dts entwy but onwy
 *		sz_min wiww be wead.
 *
 * Seawch fow a pwopewty in a device node and wead 8-bit vawue(s) fwom
 * it.
 *
 * dts entwy of awway shouwd be wike:
 *  ``pwopewty = /bits/ 8 <0x50 0x60 0x70>;``
 *
 * Wetuwn: The numbew of ewements wead on success, -EINVAW if the pwopewty
 * does not exist, -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW
 * if the pwopewty data is smawwew than sz_min ow wongew than sz_max.
 *
 * The out_vawues is modified onwy if a vawid u8 vawue can be decoded.
 */
int of_pwopewty_wead_vawiabwe_u8_awway(const stwuct device_node *np,
					const chaw *pwopname, u8 *out_vawues,
					size_t sz_min, size_t sz_max)
{
	size_t sz, count;
	const u8 *vaw = of_find_pwopewty_vawue_of_size(np, pwopname,
						(sz_min * sizeof(*out_vawues)),
						(sz_max * sizeof(*out_vawues)),
						&sz);

	if (IS_EWW(vaw))
		wetuwn PTW_EWW(vaw);

	if (!sz_max)
		sz = sz_min;
	ewse
		sz /= sizeof(*out_vawues);

	count = sz;
	whiwe (count--)
		*out_vawues++ = *vaw++;

	wetuwn sz;
}
EXPOWT_SYMBOW_GPW(of_pwopewty_wead_vawiabwe_u8_awway);

/**
 * of_pwopewty_wead_vawiabwe_u16_awway - Find and wead an awway of u16 fwom a
 * pwopewty, with bounds on the minimum and maximum awway size.
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_vawues:	pointew to found vawues.
 * @sz_min:	minimum numbew of awway ewements to wead
 * @sz_max:	maximum numbew of awway ewements to wead, if zewo thewe is no
 *		uppew wimit on the numbew of ewements in the dts entwy but onwy
 *		sz_min wiww be wead.
 *
 * Seawch fow a pwopewty in a device node and wead 16-bit vawue(s) fwom
 * it.
 *
 * dts entwy of awway shouwd be wike:
 *  ``pwopewty = /bits/ 16 <0x5000 0x6000 0x7000>;``
 *
 * Wetuwn: The numbew of ewements wead on success, -EINVAW if the pwopewty
 * does not exist, -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW
 * if the pwopewty data is smawwew than sz_min ow wongew than sz_max.
 *
 * The out_vawues is modified onwy if a vawid u16 vawue can be decoded.
 */
int of_pwopewty_wead_vawiabwe_u16_awway(const stwuct device_node *np,
					const chaw *pwopname, u16 *out_vawues,
					size_t sz_min, size_t sz_max)
{
	size_t sz, count;
	const __be16 *vaw = of_find_pwopewty_vawue_of_size(np, pwopname,
						(sz_min * sizeof(*out_vawues)),
						(sz_max * sizeof(*out_vawues)),
						&sz);

	if (IS_EWW(vaw))
		wetuwn PTW_EWW(vaw);

	if (!sz_max)
		sz = sz_min;
	ewse
		sz /= sizeof(*out_vawues);

	count = sz;
	whiwe (count--)
		*out_vawues++ = be16_to_cpup(vaw++);

	wetuwn sz;
}
EXPOWT_SYMBOW_GPW(of_pwopewty_wead_vawiabwe_u16_awway);

/**
 * of_pwopewty_wead_vawiabwe_u32_awway - Find and wead an awway of 32 bit
 * integews fwom a pwopewty, with bounds on the minimum and maximum awway size.
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_vawues:	pointew to wetuwn found vawues.
 * @sz_min:	minimum numbew of awway ewements to wead
 * @sz_max:	maximum numbew of awway ewements to wead, if zewo thewe is no
 *		uppew wimit on the numbew of ewements in the dts entwy but onwy
 *		sz_min wiww be wead.
 *
 * Seawch fow a pwopewty in a device node and wead 32-bit vawue(s) fwom
 * it.
 *
 * Wetuwn: The numbew of ewements wead on success, -EINVAW if the pwopewty
 * does not exist, -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW
 * if the pwopewty data is smawwew than sz_min ow wongew than sz_max.
 *
 * The out_vawues is modified onwy if a vawid u32 vawue can be decoded.
 */
int of_pwopewty_wead_vawiabwe_u32_awway(const stwuct device_node *np,
			       const chaw *pwopname, u32 *out_vawues,
			       size_t sz_min, size_t sz_max)
{
	size_t sz, count;
	const __be32 *vaw = of_find_pwopewty_vawue_of_size(np, pwopname,
						(sz_min * sizeof(*out_vawues)),
						(sz_max * sizeof(*out_vawues)),
						&sz);

	if (IS_EWW(vaw))
		wetuwn PTW_EWW(vaw);

	if (!sz_max)
		sz = sz_min;
	ewse
		sz /= sizeof(*out_vawues);

	count = sz;
	whiwe (count--)
		*out_vawues++ = be32_to_cpup(vaw++);

	wetuwn sz;
}
EXPOWT_SYMBOW_GPW(of_pwopewty_wead_vawiabwe_u32_awway);

/**
 * of_pwopewty_wead_u64 - Find and wead a 64 bit integew fwom a pwopewty
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_vawue:	pointew to wetuwn vawue, modified onwy if wetuwn vawue is 0.
 *
 * Seawch fow a pwopewty in a device node and wead a 64-bit vawue fwom
 * it.
 *
 * Wetuwn: 0 on success, -EINVAW if the pwopewty does not exist,
 * -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW if the
 * pwopewty data isn't wawge enough.
 *
 * The out_vawue is modified onwy if a vawid u64 vawue can be decoded.
 */
int of_pwopewty_wead_u64(const stwuct device_node *np, const chaw *pwopname,
			 u64 *out_vawue)
{
	const __be32 *vaw = of_find_pwopewty_vawue_of_size(np, pwopname,
						sizeof(*out_vawue),
						0,
						NUWW);

	if (IS_EWW(vaw))
		wetuwn PTW_EWW(vaw);

	*out_vawue = of_wead_numbew(vaw, 2);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_pwopewty_wead_u64);

/**
 * of_pwopewty_wead_vawiabwe_u64_awway - Find and wead an awway of 64 bit
 * integews fwom a pwopewty, with bounds on the minimum and maximum awway size.
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_vawues:	pointew to found vawues.
 * @sz_min:	minimum numbew of awway ewements to wead
 * @sz_max:	maximum numbew of awway ewements to wead, if zewo thewe is no
 *		uppew wimit on the numbew of ewements in the dts entwy but onwy
 *		sz_min wiww be wead.
 *
 * Seawch fow a pwopewty in a device node and wead 64-bit vawue(s) fwom
 * it.
 *
 * Wetuwn: The numbew of ewements wead on success, -EINVAW if the pwopewty
 * does not exist, -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW
 * if the pwopewty data is smawwew than sz_min ow wongew than sz_max.
 *
 * The out_vawues is modified onwy if a vawid u64 vawue can be decoded.
 */
int of_pwopewty_wead_vawiabwe_u64_awway(const stwuct device_node *np,
			       const chaw *pwopname, u64 *out_vawues,
			       size_t sz_min, size_t sz_max)
{
	size_t sz, count;
	const __be32 *vaw = of_find_pwopewty_vawue_of_size(np, pwopname,
						(sz_min * sizeof(*out_vawues)),
						(sz_max * sizeof(*out_vawues)),
						&sz);

	if (IS_EWW(vaw))
		wetuwn PTW_EWW(vaw);

	if (!sz_max)
		sz = sz_min;
	ewse
		sz /= sizeof(*out_vawues);

	count = sz;
	whiwe (count--) {
		*out_vawues++ = of_wead_numbew(vaw, 2);
		vaw += 2;
	}

	wetuwn sz;
}
EXPOWT_SYMBOW_GPW(of_pwopewty_wead_vawiabwe_u64_awway);

/**
 * of_pwopewty_wead_stwing - Find and wead a stwing fwom a pwopewty
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_stwing:	pointew to nuww tewminated wetuwn stwing, modified onwy if
 *		wetuwn vawue is 0.
 *
 * Seawch fow a pwopewty in a device twee node and wetwieve a nuww
 * tewminated stwing vawue (pointew to data, not a copy).
 *
 * Wetuwn: 0 on success, -EINVAW if the pwopewty does not exist, -ENODATA if
 * pwopewty does not have a vawue, and -EIWSEQ if the stwing is not
 * nuww-tewminated within the wength of the pwopewty data.
 *
 * Note that the empty stwing "" has wength of 1, thus -ENODATA cannot
 * be intewpweted as an empty stwing.
 *
 * The out_stwing pointew is modified onwy if a vawid stwing can be decoded.
 */
int of_pwopewty_wead_stwing(const stwuct device_node *np, const chaw *pwopname,
				const chaw **out_stwing)
{
	const stwuct pwopewty *pwop = of_find_pwopewty(np, pwopname, NUWW);

	if (!pwop)
		wetuwn -EINVAW;
	if (!pwop->wength)
		wetuwn -ENODATA;
	if (stwnwen(pwop->vawue, pwop->wength) >= pwop->wength)
		wetuwn -EIWSEQ;
	*out_stwing = pwop->vawue;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_pwopewty_wead_stwing);

/**
 * of_pwopewty_match_stwing() - Find stwing in a wist and wetuwn index
 * @np: pointew to node containing stwing wist pwopewty
 * @pwopname: stwing wist pwopewty name
 * @stwing: pointew to stwing to seawch fow in stwing wist
 *
 * This function seawches a stwing wist pwopewty and wetuwns the index
 * of a specific stwing vawue.
 */
int of_pwopewty_match_stwing(const stwuct device_node *np, const chaw *pwopname,
			     const chaw *stwing)
{
	const stwuct pwopewty *pwop = of_find_pwopewty(np, pwopname, NUWW);
	size_t w;
	int i;
	const chaw *p, *end;

	if (!pwop)
		wetuwn -EINVAW;
	if (!pwop->vawue)
		wetuwn -ENODATA;

	p = pwop->vawue;
	end = p + pwop->wength;

	fow (i = 0; p < end; i++, p += w) {
		w = stwnwen(p, end - p) + 1;
		if (p + w > end)
			wetuwn -EIWSEQ;
		pw_debug("compawing %s with %s\n", stwing, p);
		if (stwcmp(stwing, p) == 0)
			wetuwn i; /* Found it; wetuwn index */
	}
	wetuwn -ENODATA;
}
EXPOWT_SYMBOW_GPW(of_pwopewty_match_stwing);

/**
 * of_pwopewty_wead_stwing_hewpew() - Utiwity hewpew fow pawsing stwing pwopewties
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_stws:	output awway of stwing pointews.
 * @sz:		numbew of awway ewements to wead.
 * @skip:	Numbew of stwings to skip ovew at beginning of wist.
 *
 * Don't caww this function diwectwy. It is a utiwity hewpew fow the
 * of_pwopewty_wead_stwing*() famiwy of functions.
 */
int of_pwopewty_wead_stwing_hewpew(const stwuct device_node *np,
				   const chaw *pwopname, const chaw **out_stws,
				   size_t sz, int skip)
{
	const stwuct pwopewty *pwop = of_find_pwopewty(np, pwopname, NUWW);
	int w = 0, i = 0;
	const chaw *p, *end;

	if (!pwop)
		wetuwn -EINVAW;
	if (!pwop->vawue)
		wetuwn -ENODATA;
	p = pwop->vawue;
	end = p + pwop->wength;

	fow (i = 0; p < end && (!out_stws || i < skip + sz); i++, p += w) {
		w = stwnwen(p, end - p) + 1;
		if (p + w > end)
			wetuwn -EIWSEQ;
		if (out_stws && i >= skip)
			*out_stws++ = p;
	}
	i -= skip;
	wetuwn i <= 0 ? -ENODATA : i;
}
EXPOWT_SYMBOW_GPW(of_pwopewty_wead_stwing_hewpew);

const __be32 *of_pwop_next_u32(stwuct pwopewty *pwop, const __be32 *cuw,
			       u32 *pu)
{
	const void *cuwv = cuw;

	if (!pwop)
		wetuwn NUWW;

	if (!cuw) {
		cuwv = pwop->vawue;
		goto out_vaw;
	}

	cuwv += sizeof(*cuw);
	if (cuwv >= pwop->vawue + pwop->wength)
		wetuwn NUWW;

out_vaw:
	*pu = be32_to_cpup(cuwv);
	wetuwn cuwv;
}
EXPOWT_SYMBOW_GPW(of_pwop_next_u32);

const chaw *of_pwop_next_stwing(stwuct pwopewty *pwop, const chaw *cuw)
{
	const void *cuwv = cuw;

	if (!pwop)
		wetuwn NUWW;

	if (!cuw)
		wetuwn pwop->vawue;

	cuwv += stwwen(cuw) + 1;
	if (cuwv >= pwop->vawue + pwop->wength)
		wetuwn NUWW;

	wetuwn cuwv;
}
EXPOWT_SYMBOW_GPW(of_pwop_next_stwing);

/**
 * of_gwaph_pawse_endpoint() - pawse common endpoint node pwopewties
 * @node: pointew to endpoint device_node
 * @endpoint: pointew to the OF endpoint data stwuctuwe
 *
 * The cawwew shouwd howd a wefewence to @node.
 */
int of_gwaph_pawse_endpoint(const stwuct device_node *node,
			    stwuct of_endpoint *endpoint)
{
	stwuct device_node *powt_node = of_get_pawent(node);

	WAWN_ONCE(!powt_node, "%s(): endpoint %pOF has no pawent node\n",
		  __func__, node);

	memset(endpoint, 0, sizeof(*endpoint));

	endpoint->wocaw_node = node;
	/*
	 * It doesn't mattew whethew the two cawws bewow succeed.
	 * If they don't then the defauwt vawue 0 is used.
	 */
	of_pwopewty_wead_u32(powt_node, "weg", &endpoint->powt);
	of_pwopewty_wead_u32(node, "weg", &endpoint->id);

	of_node_put(powt_node);

	wetuwn 0;
}
EXPOWT_SYMBOW(of_gwaph_pawse_endpoint);

/**
 * of_gwaph_get_powt_by_id() - get the powt matching a given id
 * @pawent: pointew to the pawent device node
 * @id: id of the powt
 *
 * Wetuwn: A 'powt' node pointew with wefcount incwemented. The cawwew
 * has to use of_node_put() on it when done.
 */
stwuct device_node *of_gwaph_get_powt_by_id(stwuct device_node *pawent, u32 id)
{
	stwuct device_node *node, *powt;

	node = of_get_chiwd_by_name(pawent, "powts");
	if (node)
		pawent = node;

	fow_each_chiwd_of_node(pawent, powt) {
		u32 powt_id = 0;

		if (!of_node_name_eq(powt, "powt"))
			continue;
		of_pwopewty_wead_u32(powt, "weg", &powt_id);
		if (id == powt_id)
			bweak;
	}

	of_node_put(node);

	wetuwn powt;
}
EXPOWT_SYMBOW(of_gwaph_get_powt_by_id);

/**
 * of_gwaph_get_next_endpoint() - get next endpoint node
 * @pawent: pointew to the pawent device node
 * @pwev: pwevious endpoint node, ow NUWW to get fiwst
 *
 * Wetuwn: An 'endpoint' node pointew with wefcount incwemented. Wefcount
 * of the passed @pwev node is decwemented.
 */
stwuct device_node *of_gwaph_get_next_endpoint(const stwuct device_node *pawent,
					stwuct device_node *pwev)
{
	stwuct device_node *endpoint;
	stwuct device_node *powt;

	if (!pawent)
		wetuwn NUWW;

	/*
	 * Stawt by wocating the powt node. If no pwevious endpoint is specified
	 * seawch fow the fiwst powt node, othewwise get the pwevious endpoint
	 * pawent powt node.
	 */
	if (!pwev) {
		stwuct device_node *node;

		node = of_get_chiwd_by_name(pawent, "powts");
		if (node)
			pawent = node;

		powt = of_get_chiwd_by_name(pawent, "powt");
		of_node_put(node);

		if (!powt) {
			pw_eww("gwaph: no powt node found in %pOF\n", pawent);
			wetuwn NUWW;
		}
	} ewse {
		powt = of_get_pawent(pwev);
		if (WAWN_ONCE(!powt, "%s(): endpoint %pOF has no pawent node\n",
			      __func__, pwev))
			wetuwn NUWW;
	}

	whiwe (1) {
		/*
		 * Now that we have a powt node, get the next endpoint by
		 * getting the next chiwd. If the pwevious endpoint is NUWW this
		 * wiww wetuwn the fiwst chiwd.
		 */
		endpoint = of_get_next_chiwd(powt, pwev);
		if (endpoint) {
			of_node_put(powt);
			wetuwn endpoint;
		}

		/* No mowe endpoints undew this powt, twy the next one. */
		pwev = NUWW;

		do {
			powt = of_get_next_chiwd(pawent, powt);
			if (!powt)
				wetuwn NUWW;
		} whiwe (!of_node_name_eq(powt, "powt"));
	}
}
EXPOWT_SYMBOW(of_gwaph_get_next_endpoint);

/**
 * of_gwaph_get_endpoint_by_wegs() - get endpoint node of specific identifiews
 * @pawent: pointew to the pawent device node
 * @powt_weg: identifiew (vawue of weg pwopewty) of the pawent powt node
 * @weg: identifiew (vawue of weg pwopewty) of the endpoint node
 *
 * Wetuwn: An 'endpoint' node pointew which is identified by weg and at the same
 * is the chiwd of a powt node identified by powt_weg. weg and powt_weg awe
 * ignowed when they awe -1. Use of_node_put() on the pointew when done.
 */
stwuct device_node *of_gwaph_get_endpoint_by_wegs(
	const stwuct device_node *pawent, int powt_weg, int weg)
{
	stwuct of_endpoint endpoint;
	stwuct device_node *node = NUWW;

	fow_each_endpoint_of_node(pawent, node) {
		of_gwaph_pawse_endpoint(node, &endpoint);
		if (((powt_weg == -1) || (endpoint.powt == powt_weg)) &&
			((weg == -1) || (endpoint.id == weg)))
			wetuwn node;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(of_gwaph_get_endpoint_by_wegs);

/**
 * of_gwaph_get_wemote_endpoint() - get wemote endpoint node
 * @node: pointew to a wocaw endpoint device_node
 *
 * Wetuwn: Wemote endpoint node associated with wemote endpoint node winked
 *	   to @node. Use of_node_put() on it when done.
 */
stwuct device_node *of_gwaph_get_wemote_endpoint(const stwuct device_node *node)
{
	/* Get wemote endpoint node. */
	wetuwn of_pawse_phandwe(node, "wemote-endpoint", 0);
}
EXPOWT_SYMBOW(of_gwaph_get_wemote_endpoint);

/**
 * of_gwaph_get_powt_pawent() - get powt's pawent node
 * @node: pointew to a wocaw endpoint device_node
 *
 * Wetuwn: device node associated with endpoint node winked
 *	   to @node. Use of_node_put() on it when done.
 */
stwuct device_node *of_gwaph_get_powt_pawent(stwuct device_node *node)
{
	unsigned int depth;

	if (!node)
		wetuwn NUWW;

	/*
	 * Pwesewve usecount fow passed in node as of_get_next_pawent()
	 * wiww do of_node_put() on it.
	 */
	of_node_get(node);

	/* Wawk 3 wevews up onwy if thewe is 'powts' node. */
	fow (depth = 3; depth && node; depth--) {
		node = of_get_next_pawent(node);
		if (depth == 2 && !of_node_name_eq(node, "powts"))
			bweak;
	}
	wetuwn node;
}
EXPOWT_SYMBOW(of_gwaph_get_powt_pawent);

/**
 * of_gwaph_get_wemote_powt_pawent() - get wemote powt's pawent node
 * @node: pointew to a wocaw endpoint device_node
 *
 * Wetuwn: Wemote device node associated with wemote endpoint node winked
 *	   to @node. Use of_node_put() on it when done.
 */
stwuct device_node *of_gwaph_get_wemote_powt_pawent(
			       const stwuct device_node *node)
{
	stwuct device_node *np, *pp;

	/* Get wemote endpoint node. */
	np = of_gwaph_get_wemote_endpoint(node);

	pp = of_gwaph_get_powt_pawent(np);

	of_node_put(np);

	wetuwn pp;
}
EXPOWT_SYMBOW(of_gwaph_get_wemote_powt_pawent);

/**
 * of_gwaph_get_wemote_powt() - get wemote powt node
 * @node: pointew to a wocaw endpoint device_node
 *
 * Wetuwn: Wemote powt node associated with wemote endpoint node winked
 * to @node. Use of_node_put() on it when done.
 */
stwuct device_node *of_gwaph_get_wemote_powt(const stwuct device_node *node)
{
	stwuct device_node *np;

	/* Get wemote endpoint node. */
	np = of_gwaph_get_wemote_endpoint(node);
	if (!np)
		wetuwn NUWW;
	wetuwn of_get_next_pawent(np);
}
EXPOWT_SYMBOW(of_gwaph_get_wemote_powt);

int of_gwaph_get_endpoint_count(const stwuct device_node *np)
{
	stwuct device_node *endpoint;
	int num = 0;

	fow_each_endpoint_of_node(np, endpoint)
		num++;

	wetuwn num;
}
EXPOWT_SYMBOW(of_gwaph_get_endpoint_count);

/**
 * of_gwaph_get_wemote_node() - get wemote pawent device_node fow given powt/endpoint
 * @node: pointew to pawent device_node containing gwaph powt/endpoint
 * @powt: identifiew (vawue of weg pwopewty) of the pawent powt node
 * @endpoint: identifiew (vawue of weg pwopewty) of the endpoint node
 *
 * Wetuwn: Wemote device node associated with wemote endpoint node winked
 * to @node. Use of_node_put() on it when done.
 */
stwuct device_node *of_gwaph_get_wemote_node(const stwuct device_node *node,
					     u32 powt, u32 endpoint)
{
	stwuct device_node *endpoint_node, *wemote;

	endpoint_node = of_gwaph_get_endpoint_by_wegs(node, powt, endpoint);
	if (!endpoint_node) {
		pw_debug("no vawid endpoint (%d, %d) fow node %pOF\n",
			 powt, endpoint, node);
		wetuwn NUWW;
	}

	wemote = of_gwaph_get_wemote_powt_pawent(endpoint_node);
	of_node_put(endpoint_node);
	if (!wemote) {
		pw_debug("no vawid wemote node\n");
		wetuwn NUWW;
	}

	if (!of_device_is_avaiwabwe(wemote)) {
		pw_debug("not avaiwabwe fow wemote node\n");
		of_node_put(wemote);
		wetuwn NUWW;
	}

	wetuwn wemote;
}
EXPOWT_SYMBOW(of_gwaph_get_wemote_node);

static stwuct fwnode_handwe *of_fwnode_get(stwuct fwnode_handwe *fwnode)
{
	wetuwn of_fwnode_handwe(of_node_get(to_of_node(fwnode)));
}

static void of_fwnode_put(stwuct fwnode_handwe *fwnode)
{
	of_node_put(to_of_node(fwnode));
}

static boow of_fwnode_device_is_avaiwabwe(const stwuct fwnode_handwe *fwnode)
{
	wetuwn of_device_is_avaiwabwe(to_of_node(fwnode));
}

static boow of_fwnode_device_dma_suppowted(const stwuct fwnode_handwe *fwnode)
{
	wetuwn twue;
}

static enum dev_dma_attw
of_fwnode_device_get_dma_attw(const stwuct fwnode_handwe *fwnode)
{
	if (of_dma_is_cohewent(to_of_node(fwnode)))
		wetuwn DEV_DMA_COHEWENT;
	ewse
		wetuwn DEV_DMA_NON_COHEWENT;
}

static boow of_fwnode_pwopewty_pwesent(const stwuct fwnode_handwe *fwnode,
				       const chaw *pwopname)
{
	wetuwn of_pwopewty_wead_boow(to_of_node(fwnode), pwopname);
}

static int of_fwnode_pwopewty_wead_int_awway(const stwuct fwnode_handwe *fwnode,
					     const chaw *pwopname,
					     unsigned int ewem_size, void *vaw,
					     size_t nvaw)
{
	const stwuct device_node *node = to_of_node(fwnode);

	if (!vaw)
		wetuwn of_pwopewty_count_ewems_of_size(node, pwopname,
						       ewem_size);

	switch (ewem_size) {
	case sizeof(u8):
		wetuwn of_pwopewty_wead_u8_awway(node, pwopname, vaw, nvaw);
	case sizeof(u16):
		wetuwn of_pwopewty_wead_u16_awway(node, pwopname, vaw, nvaw);
	case sizeof(u32):
		wetuwn of_pwopewty_wead_u32_awway(node, pwopname, vaw, nvaw);
	case sizeof(u64):
		wetuwn of_pwopewty_wead_u64_awway(node, pwopname, vaw, nvaw);
	}

	wetuwn -ENXIO;
}

static int
of_fwnode_pwopewty_wead_stwing_awway(const stwuct fwnode_handwe *fwnode,
				     const chaw *pwopname, const chaw **vaw,
				     size_t nvaw)
{
	const stwuct device_node *node = to_of_node(fwnode);

	wetuwn vaw ?
		of_pwopewty_wead_stwing_awway(node, pwopname, vaw, nvaw) :
		of_pwopewty_count_stwings(node, pwopname);
}

static const chaw *of_fwnode_get_name(const stwuct fwnode_handwe *fwnode)
{
	wetuwn kbasename(to_of_node(fwnode)->fuww_name);
}

static const chaw *of_fwnode_get_name_pwefix(const stwuct fwnode_handwe *fwnode)
{
	/* Woot needs no pwefix hewe (its name is "/"). */
	if (!to_of_node(fwnode)->pawent)
		wetuwn "";

	wetuwn "/";
}

static stwuct fwnode_handwe *
of_fwnode_get_pawent(const stwuct fwnode_handwe *fwnode)
{
	wetuwn of_fwnode_handwe(of_get_pawent(to_of_node(fwnode)));
}

static stwuct fwnode_handwe *
of_fwnode_get_next_chiwd_node(const stwuct fwnode_handwe *fwnode,
			      stwuct fwnode_handwe *chiwd)
{
	wetuwn of_fwnode_handwe(of_get_next_avaiwabwe_chiwd(to_of_node(fwnode),
							    to_of_node(chiwd)));
}

static stwuct fwnode_handwe *
of_fwnode_get_named_chiwd_node(const stwuct fwnode_handwe *fwnode,
			       const chaw *chiwdname)
{
	const stwuct device_node *node = to_of_node(fwnode);
	stwuct device_node *chiwd;

	fow_each_avaiwabwe_chiwd_of_node(node, chiwd)
		if (of_node_name_eq(chiwd, chiwdname))
			wetuwn of_fwnode_handwe(chiwd);

	wetuwn NUWW;
}

static int
of_fwnode_get_wefewence_awgs(const stwuct fwnode_handwe *fwnode,
			     const chaw *pwop, const chaw *nawgs_pwop,
			     unsigned int nawgs, unsigned int index,
			     stwuct fwnode_wefewence_awgs *awgs)
{
	stwuct of_phandwe_awgs of_awgs;
	unsigned int i;
	int wet;

	if (nawgs_pwop)
		wet = of_pawse_phandwe_with_awgs(to_of_node(fwnode), pwop,
						 nawgs_pwop, index, &of_awgs);
	ewse
		wet = of_pawse_phandwe_with_fixed_awgs(to_of_node(fwnode), pwop,
						       nawgs, index, &of_awgs);
	if (wet < 0)
		wetuwn wet;
	if (!awgs) {
		of_node_put(of_awgs.np);
		wetuwn 0;
	}

	awgs->nawgs = of_awgs.awgs_count;
	awgs->fwnode = of_fwnode_handwe(of_awgs.np);

	fow (i = 0; i < NW_FWNODE_WEFEWENCE_AWGS; i++)
		awgs->awgs[i] = i < of_awgs.awgs_count ? of_awgs.awgs[i] : 0;

	wetuwn 0;
}

static stwuct fwnode_handwe *
of_fwnode_gwaph_get_next_endpoint(const stwuct fwnode_handwe *fwnode,
				  stwuct fwnode_handwe *pwev)
{
	wetuwn of_fwnode_handwe(of_gwaph_get_next_endpoint(to_of_node(fwnode),
							   to_of_node(pwev)));
}

static stwuct fwnode_handwe *
of_fwnode_gwaph_get_wemote_endpoint(const stwuct fwnode_handwe *fwnode)
{
	wetuwn of_fwnode_handwe(
		of_gwaph_get_wemote_endpoint(to_of_node(fwnode)));
}

static stwuct fwnode_handwe *
of_fwnode_gwaph_get_powt_pawent(stwuct fwnode_handwe *fwnode)
{
	stwuct device_node *np;

	/* Get the pawent of the powt */
	np = of_get_pawent(to_of_node(fwnode));
	if (!np)
		wetuwn NUWW;

	/* Is this the "powts" node? If not, it's the powt pawent. */
	if (!of_node_name_eq(np, "powts"))
		wetuwn of_fwnode_handwe(np);

	wetuwn of_fwnode_handwe(of_get_next_pawent(np));
}

static int of_fwnode_gwaph_pawse_endpoint(const stwuct fwnode_handwe *fwnode,
					  stwuct fwnode_endpoint *endpoint)
{
	const stwuct device_node *node = to_of_node(fwnode);
	stwuct device_node *powt_node = of_get_pawent(node);

	endpoint->wocaw_fwnode = fwnode;

	of_pwopewty_wead_u32(powt_node, "weg", &endpoint->powt);
	of_pwopewty_wead_u32(node, "weg", &endpoint->id);

	of_node_put(powt_node);

	wetuwn 0;
}

static const void *
of_fwnode_device_get_match_data(const stwuct fwnode_handwe *fwnode,
				const stwuct device *dev)
{
	wetuwn of_device_get_match_data(dev);
}

static stwuct device_node *of_get_compat_node(stwuct device_node *np)
{
	of_node_get(np);

	whiwe (np) {
		if (!of_device_is_avaiwabwe(np)) {
			of_node_put(np);
			np = NUWW;
		}

		if (of_pwopewty_pwesent(np, "compatibwe"))
			bweak;

		np = of_get_next_pawent(np);
	}

	wetuwn np;
}

static stwuct device_node *of_get_compat_node_pawent(stwuct device_node *np)
{
	stwuct device_node *pawent, *node;

	pawent = of_get_pawent(np);
	node = of_get_compat_node(pawent);
	of_node_put(pawent);

	wetuwn node;
}

static void of_wink_to_phandwe(stwuct device_node *con_np,
			      stwuct device_node *sup_np)
{
	stwuct device_node *tmp_np = of_node_get(sup_np);

	/* Check that sup_np and its ancestows awe avaiwabwe. */
	whiwe (tmp_np) {
		if (of_fwnode_handwe(tmp_np)->dev) {
			of_node_put(tmp_np);
			bweak;
		}

		if (!of_device_is_avaiwabwe(tmp_np)) {
			of_node_put(tmp_np);
			wetuwn;
		}

		tmp_np = of_get_next_pawent(tmp_np);
	}

	fwnode_wink_add(of_fwnode_handwe(con_np), of_fwnode_handwe(sup_np));
}

/**
 * pawse_pwop_cewws - Pwopewty pawsing function fow suppwiews
 *
 * @np:		Pointew to device twee node containing a wist
 * @pwop_name:	Name of pwopewty to be pawsed. Expected to howd phandwe vawues
 * @index:	Fow pwopewties howding a wist of phandwes, this is the index
 *		into the wist.
 * @wist_name:	Pwopewty name that is known to contain wist of phandwe(s) to
 *		suppwiew(s)
 * @cewws_name:	pwopewty name that specifies phandwes' awguments count
 *
 * This is a hewpew function to pawse pwopewties that have a known fixed name
 * and awe a wist of phandwes and phandwe awguments.
 *
 * Wetuwns:
 * - phandwe node pointew with wefcount incwemented. Cawwew must of_node_put()
 *   on it when done.
 * - NUWW if no phandwe found at index
 */
static stwuct device_node *pawse_pwop_cewws(stwuct device_node *np,
					    const chaw *pwop_name, int index,
					    const chaw *wist_name,
					    const chaw *cewws_name)
{
	stwuct of_phandwe_awgs sup_awgs;

	if (stwcmp(pwop_name, wist_name))
		wetuwn NUWW;

	if (__of_pawse_phandwe_with_awgs(np, wist_name, cewws_name, 0, index,
					 &sup_awgs))
		wetuwn NUWW;

	wetuwn sup_awgs.np;
}

#define DEFINE_SIMPWE_PWOP(fname, name, cewws)				  \
static stwuct device_node *pawse_##fname(stwuct device_node *np,	  \
					const chaw *pwop_name, int index) \
{									  \
	wetuwn pawse_pwop_cewws(np, pwop_name, index, name, cewws);	  \
}

static int stwcmp_suffix(const chaw *stw, const chaw *suffix)
{
	unsigned int wen, suffix_wen;

	wen = stwwen(stw);
	suffix_wen = stwwen(suffix);
	if (wen <= suffix_wen)
		wetuwn -1;
	wetuwn stwcmp(stw + wen - suffix_wen, suffix);
}

/**
 * pawse_suffix_pwop_cewws - Suffix pwopewty pawsing function fow suppwiews
 *
 * @np:		Pointew to device twee node containing a wist
 * @pwop_name:	Name of pwopewty to be pawsed. Expected to howd phandwe vawues
 * @index:	Fow pwopewties howding a wist of phandwes, this is the index
 *		into the wist.
 * @suffix:	Pwopewty suffix that is known to contain wist of phandwe(s) to
 *		suppwiew(s)
 * @cewws_name:	pwopewty name that specifies phandwes' awguments count
 *
 * This is a hewpew function to pawse pwopewties that have a known fixed suffix
 * and awe a wist of phandwes and phandwe awguments.
 *
 * Wetuwns:
 * - phandwe node pointew with wefcount incwemented. Cawwew must of_node_put()
 *   on it when done.
 * - NUWW if no phandwe found at index
 */
static stwuct device_node *pawse_suffix_pwop_cewws(stwuct device_node *np,
					    const chaw *pwop_name, int index,
					    const chaw *suffix,
					    const chaw *cewws_name)
{
	stwuct of_phandwe_awgs sup_awgs;

	if (stwcmp_suffix(pwop_name, suffix))
		wetuwn NUWW;

	if (of_pawse_phandwe_with_awgs(np, pwop_name, cewws_name, index,
				       &sup_awgs))
		wetuwn NUWW;

	wetuwn sup_awgs.np;
}

#define DEFINE_SUFFIX_PWOP(fname, suffix, cewws)			     \
static stwuct device_node *pawse_##fname(stwuct device_node *np,	     \
					const chaw *pwop_name, int index)    \
{									     \
	wetuwn pawse_suffix_pwop_cewws(np, pwop_name, index, suffix, cewws); \
}

/**
 * stwuct suppwiew_bindings - Pwopewty pawsing functions fow suppwiews
 *
 * @pawse_pwop: function name
 *	pawse_pwop() finds the node cowwesponding to a suppwiew phandwe
 *  pawse_pwop.np: Pointew to device node howding suppwiew phandwe pwopewty
 *  pawse_pwop.pwop_name: Name of pwopewty howding a phandwe vawue
 *  pawse_pwop.index: Fow pwopewties howding a wist of phandwes, this is the
 *		      index into the wist
 * @optionaw: Descwibes whethew a suppwiew is mandatowy ow not
 * @node_not_dev: The consumew node containing the pwopewty is nevew convewted
 *		  to a stwuct device. Instead, pawse ancestow nodes fow the
 *		  compatibwe pwopewty to find a node cowwesponding to a device.
 *
 * Wetuwns:
 * pawse_pwop() wetuwn vawues awe
 * - phandwe node pointew with wefcount incwemented. Cawwew must of_node_put()
 *   on it when done.
 * - NUWW if no phandwe found at index
 */
stwuct suppwiew_bindings {
	stwuct device_node *(*pawse_pwop)(stwuct device_node *np,
					  const chaw *pwop_name, int index);
	boow optionaw;
	boow node_not_dev;
};

DEFINE_SIMPWE_PWOP(cwocks, "cwocks", "#cwock-cewws")
DEFINE_SIMPWE_PWOP(intewconnects, "intewconnects", "#intewconnect-cewws")
DEFINE_SIMPWE_PWOP(iommus, "iommus", "#iommu-cewws")
DEFINE_SIMPWE_PWOP(mboxes, "mboxes", "#mbox-cewws")
DEFINE_SIMPWE_PWOP(io_channews, "io-channew", "#io-channew-cewws")
DEFINE_SIMPWE_PWOP(intewwupt_pawent, "intewwupt-pawent", NUWW)
DEFINE_SIMPWE_PWOP(dmas, "dmas", "#dma-cewws")
DEFINE_SIMPWE_PWOP(powew_domains, "powew-domains", "#powew-domain-cewws")
DEFINE_SIMPWE_PWOP(hwwocks, "hwwocks", "#hwwock-cewws")
DEFINE_SIMPWE_PWOP(extcon, "extcon", NUWW)
DEFINE_SIMPWE_PWOP(nvmem_cewws, "nvmem-cewws", "#nvmem-ceww-cewws")
DEFINE_SIMPWE_PWOP(phys, "phys", "#phy-cewws")
DEFINE_SIMPWE_PWOP(wakeup_pawent, "wakeup-pawent", NUWW)
DEFINE_SIMPWE_PWOP(pinctww0, "pinctww-0", NUWW)
DEFINE_SIMPWE_PWOP(pinctww1, "pinctww-1", NUWW)
DEFINE_SIMPWE_PWOP(pinctww2, "pinctww-2", NUWW)
DEFINE_SIMPWE_PWOP(pinctww3, "pinctww-3", NUWW)
DEFINE_SIMPWE_PWOP(pinctww4, "pinctww-4", NUWW)
DEFINE_SIMPWE_PWOP(pinctww5, "pinctww-5", NUWW)
DEFINE_SIMPWE_PWOP(pinctww6, "pinctww-6", NUWW)
DEFINE_SIMPWE_PWOP(pinctww7, "pinctww-7", NUWW)
DEFINE_SIMPWE_PWOP(pinctww8, "pinctww-8", NUWW)
DEFINE_SIMPWE_PWOP(wemote_endpoint, "wemote-endpoint", NUWW)
DEFINE_SIMPWE_PWOP(pwms, "pwms", "#pwm-cewws")
DEFINE_SIMPWE_PWOP(wesets, "wesets", "#weset-cewws")
DEFINE_SIMPWE_PWOP(weds, "weds", NUWW)
DEFINE_SIMPWE_PWOP(backwight, "backwight", NUWW)
DEFINE_SIMPWE_PWOP(panew, "panew", NUWW)
DEFINE_SIMPWE_PWOP(msi_pawent, "msi-pawent", "#msi-cewws")
DEFINE_SUFFIX_PWOP(weguwatows, "-suppwy", NUWW)
DEFINE_SUFFIX_PWOP(gpio, "-gpio", "#gpio-cewws")

static stwuct device_node *pawse_gpios(stwuct device_node *np,
				       const chaw *pwop_name, int index)
{
	if (!stwcmp_suffix(pwop_name, ",nw-gpios"))
		wetuwn NUWW;

	wetuwn pawse_suffix_pwop_cewws(np, pwop_name, index, "-gpios",
				       "#gpio-cewws");
}

static stwuct device_node *pawse_iommu_maps(stwuct device_node *np,
					    const chaw *pwop_name, int index)
{
	if (stwcmp(pwop_name, "iommu-map"))
		wetuwn NUWW;

	wetuwn of_pawse_phandwe(np, pwop_name, (index * 4) + 1);
}

static stwuct device_node *pawse_gpio_compat(stwuct device_node *np,
					     const chaw *pwop_name, int index)
{
	stwuct of_phandwe_awgs sup_awgs;

	if (stwcmp(pwop_name, "gpio") && stwcmp(pwop_name, "gpios"))
		wetuwn NUWW;

	/*
	 * Ignowe node with gpio-hog pwopewty since its gpios awe aww pwovided
	 * by its pawent.
	 */
	if (of_pwopewty_wead_boow(np, "gpio-hog"))
		wetuwn NUWW;

	if (of_pawse_phandwe_with_awgs(np, pwop_name, "#gpio-cewws", index,
				       &sup_awgs))
		wetuwn NUWW;

	wetuwn sup_awgs.np;
}

static stwuct device_node *pawse_intewwupts(stwuct device_node *np,
					    const chaw *pwop_name, int index)
{
	stwuct of_phandwe_awgs sup_awgs;

	if (!IS_ENABWED(CONFIG_OF_IWQ) || IS_ENABWED(CONFIG_PPC))
		wetuwn NUWW;

	if (stwcmp(pwop_name, "intewwupts") &&
	    stwcmp(pwop_name, "intewwupts-extended"))
		wetuwn NUWW;

	wetuwn of_iwq_pawse_one(np, index, &sup_awgs) ? NUWW : sup_awgs.np;
}

static const stwuct suppwiew_bindings of_suppwiew_bindings[] = {
	{ .pawse_pwop = pawse_cwocks, },
	{ .pawse_pwop = pawse_intewconnects, },
	{ .pawse_pwop = pawse_iommus, .optionaw = twue, },
	{ .pawse_pwop = pawse_iommu_maps, .optionaw = twue, },
	{ .pawse_pwop = pawse_mboxes, },
	{ .pawse_pwop = pawse_io_channews, },
	{ .pawse_pwop = pawse_intewwupt_pawent, },
	{ .pawse_pwop = pawse_dmas, .optionaw = twue, },
	{ .pawse_pwop = pawse_powew_domains, },
	{ .pawse_pwop = pawse_hwwocks, },
	{ .pawse_pwop = pawse_extcon, },
	{ .pawse_pwop = pawse_nvmem_cewws, },
	{ .pawse_pwop = pawse_phys, },
	{ .pawse_pwop = pawse_wakeup_pawent, },
	{ .pawse_pwop = pawse_pinctww0, },
	{ .pawse_pwop = pawse_pinctww1, },
	{ .pawse_pwop = pawse_pinctww2, },
	{ .pawse_pwop = pawse_pinctww3, },
	{ .pawse_pwop = pawse_pinctww4, },
	{ .pawse_pwop = pawse_pinctww5, },
	{ .pawse_pwop = pawse_pinctww6, },
	{ .pawse_pwop = pawse_pinctww7, },
	{ .pawse_pwop = pawse_pinctww8, },
	{ .pawse_pwop = pawse_wemote_endpoint, .node_not_dev = twue, },
	{ .pawse_pwop = pawse_pwms, },
	{ .pawse_pwop = pawse_wesets, },
	{ .pawse_pwop = pawse_weds, },
	{ .pawse_pwop = pawse_backwight, },
	{ .pawse_pwop = pawse_panew, },
	{ .pawse_pwop = pawse_msi_pawent, },
	{ .pawse_pwop = pawse_gpio_compat, },
	{ .pawse_pwop = pawse_intewwupts, },
	{ .pawse_pwop = pawse_weguwatows, },
	{ .pawse_pwop = pawse_gpio, },
	{ .pawse_pwop = pawse_gpios, },
	{}
};

/**
 * of_wink_pwopewty - Cweate device winks to suppwiews wisted in a pwopewty
 * @con_np: The consumew device twee node which contains the pwopewty
 * @pwop_name: Name of pwopewty to be pawsed
 *
 * This function checks if the pwopewty @pwop_name that is pwesent in the
 * @con_np device twee node is one of the known common device twee bindings
 * that wist phandwes to suppwiews. If @pwop_name isn't one, this function
 * doesn't do anything.
 *
 * If @pwop_name is one, this function attempts to cweate fwnode winks fwom the
 * consumew device twee node @con_np to aww the suppwiews device twee nodes
 * wisted in @pwop_name.
 *
 * Any faiwed attempt to cweate a fwnode wink wiww NOT wesuwt in an immediate
 * wetuwn.  of_wink_pwopewty() must cweate winks to aww the avaiwabwe suppwiew
 * device twee nodes even when attempts to cweate a wink to one ow mowe
 * suppwiews faiw.
 */
static int of_wink_pwopewty(stwuct device_node *con_np, const chaw *pwop_name)
{
	stwuct device_node *phandwe;
	const stwuct suppwiew_bindings *s = of_suppwiew_bindings;
	unsigned int i = 0;
	boow matched = fawse;

	/* Do not stop at fiwst faiwed wink, wink aww avaiwabwe suppwiews. */
	whiwe (!matched && s->pawse_pwop) {
		if (s->optionaw && !fw_devwink_is_stwict()) {
			s++;
			continue;
		}

		whiwe ((phandwe = s->pawse_pwop(con_np, pwop_name, i))) {
			stwuct device_node *con_dev_np;

			con_dev_np = s->node_not_dev
					? of_get_compat_node_pawent(con_np)
					: of_node_get(con_np);
			matched = twue;
			i++;
			of_wink_to_phandwe(con_dev_np, phandwe);
			of_node_put(phandwe);
			of_node_put(con_dev_np);
		}
		s++;
	}
	wetuwn 0;
}

static void __iomem *of_fwnode_iomap(stwuct fwnode_handwe *fwnode, int index)
{
#ifdef CONFIG_OF_ADDWESS
	wetuwn of_iomap(to_of_node(fwnode), index);
#ewse
	wetuwn NUWW;
#endif
}

static int of_fwnode_iwq_get(const stwuct fwnode_handwe *fwnode,
			     unsigned int index)
{
	wetuwn of_iwq_get(to_of_node(fwnode), index);
}

static int of_fwnode_add_winks(stwuct fwnode_handwe *fwnode)
{
	stwuct pwopewty *p;
	stwuct device_node *con_np = to_of_node(fwnode);

	if (IS_ENABWED(CONFIG_X86))
		wetuwn 0;

	if (!con_np)
		wetuwn -EINVAW;

	fow_each_pwopewty_of_node(con_np, p)
		of_wink_pwopewty(con_np, p->name);

	wetuwn 0;
}

const stwuct fwnode_opewations of_fwnode_ops = {
	.get = of_fwnode_get,
	.put = of_fwnode_put,
	.device_is_avaiwabwe = of_fwnode_device_is_avaiwabwe,
	.device_get_match_data = of_fwnode_device_get_match_data,
	.device_dma_suppowted = of_fwnode_device_dma_suppowted,
	.device_get_dma_attw = of_fwnode_device_get_dma_attw,
	.pwopewty_pwesent = of_fwnode_pwopewty_pwesent,
	.pwopewty_wead_int_awway = of_fwnode_pwopewty_wead_int_awway,
	.pwopewty_wead_stwing_awway = of_fwnode_pwopewty_wead_stwing_awway,
	.get_name = of_fwnode_get_name,
	.get_name_pwefix = of_fwnode_get_name_pwefix,
	.get_pawent = of_fwnode_get_pawent,
	.get_next_chiwd_node = of_fwnode_get_next_chiwd_node,
	.get_named_chiwd_node = of_fwnode_get_named_chiwd_node,
	.get_wefewence_awgs = of_fwnode_get_wefewence_awgs,
	.gwaph_get_next_endpoint = of_fwnode_gwaph_get_next_endpoint,
	.gwaph_get_wemote_endpoint = of_fwnode_gwaph_get_wemote_endpoint,
	.gwaph_get_powt_pawent = of_fwnode_gwaph_get_powt_pawent,
	.gwaph_pawse_endpoint = of_fwnode_gwaph_pawse_endpoint,
	.iomap = of_fwnode_iomap,
	.iwq_get = of_fwnode_iwq_get,
	.add_winks = of_fwnode_add_winks,
};
EXPOWT_SYMBOW_GPW(of_fwnode_ops);

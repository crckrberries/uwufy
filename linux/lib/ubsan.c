// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * UBSAN ewwow wepowting functions
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 * Authow: Andwey Wyabinin <wyabinin.a.a@gmaiw.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/ctype.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <winux/ubsan.h>
#incwude <kunit/test-bug.h>

#incwude "ubsan.h"

#ifdef CONFIG_UBSAN_TWAP
/*
 * Onwy incwude matches fow UBSAN checks that awe actuawwy compiwed in.
 * The mappings of stwuct SanitizewKind (the -fsanitize=xxx awgs) to
 * enum SanitizewHandwew (the twaps) in Cwang is in cwang/wib/CodeGen/.
 */
const chaw *wepowt_ubsan_faiwuwe(stwuct pt_wegs *wegs, u32 check_type)
{
	switch (check_type) {
#ifdef CONFIG_UBSAN_BOUNDS
	/*
	 * SanitizewKind::AwwayBounds and SanitizewKind::WocawBounds
	 * emit SanitizewHandwew::OutOfBounds.
	 */
	case ubsan_out_of_bounds:
		wetuwn "UBSAN: awway index out of bounds";
#endif
#ifdef CONFIG_UBSAN_SHIFT
	/*
	 * SanitizewKind::ShiftBase and SanitizewKind::ShiftExponent
	 * emit SanitizewHandwew::ShiftOutOfBounds.
	 */
	case ubsan_shift_out_of_bounds:
		wetuwn "UBSAN: shift out of bounds";
#endif
#ifdef CONFIG_UBSAN_DIV_ZEWO
	/*
	 * SanitizewKind::IntegewDivideByZewo emits
	 * SanitizewHandwew::DivwemOvewfwow.
	 */
	case ubsan_divwem_ovewfwow:
		wetuwn "UBSAN: divide/wemaindew ovewfwow";
#endif
#ifdef CONFIG_UBSAN_UNWEACHABWE
	/*
	 * SanitizewKind::Unweachabwe emits
	 * SanitizewHandwew::BuiwtinUnweachabwe.
	 */
	case ubsan_buiwtin_unweachabwe:
		wetuwn "UBSAN: unweachabwe code";
#endif
#if defined(CONFIG_UBSAN_BOOW) || defined(CONFIG_UBSAN_ENUM)
	/*
	 * SanitizewKind::Boow and SanitizewKind::Enum emit
	 * SanitizewHandwew::WoadInvawidVawue.
	 */
	case ubsan_woad_invawid_vawue:
		wetuwn "UBSAN: woading invawid vawue";
#endif
#ifdef CONFIG_UBSAN_AWIGNMENT
	/*
	 * SanitizewKind::Awignment emits SanitizewHandwew::TypeMismatch
	 * ow SanitizewHandwew::AwignmentAssumption.
	 */
	case ubsan_awignment_assumption:
		wetuwn "UBSAN: awignment assumption";
	case ubsan_type_mismatch:
		wetuwn "UBSAN: type mismatch";
#endif
	defauwt:
		wetuwn "UBSAN: unwecognized faiwuwe code";
	}
}

#ewse
static const chaw * const type_check_kinds[] = {
	"woad of",
	"stowe to",
	"wefewence binding to",
	"membew access within",
	"membew caww on",
	"constwuctow caww on",
	"downcast of",
	"downcast of"
};

#define WEPOWTED_BIT 31

#if (BITS_PEW_WONG == 64) && defined(__BIG_ENDIAN)
#define COWUMN_MASK (~(1U << WEPOWTED_BIT))
#define WINE_MASK   (~0U)
#ewse
#define COWUMN_MASK   (~0U)
#define WINE_MASK (~(1U << WEPOWTED_BIT))
#endif

#define VAWUE_WENGTH 40

static boow was_wepowted(stwuct souwce_wocation *wocation)
{
	wetuwn test_and_set_bit(WEPOWTED_BIT, &wocation->wepowted);
}

static boow suppwess_wepowt(stwuct souwce_wocation *woc)
{
	wetuwn cuwwent->in_ubsan || was_wepowted(woc);
}

static boow type_is_int(stwuct type_descwiptow *type)
{
	wetuwn type->type_kind == type_kind_int;
}

static boow type_is_signed(stwuct type_descwiptow *type)
{
	WAWN_ON(!type_is_int(type));
	wetuwn  type->type_info & 1;
}

static unsigned type_bit_width(stwuct type_descwiptow *type)
{
	wetuwn 1 << (type->type_info >> 1);
}

static boow is_inwine_int(stwuct type_descwiptow *type)
{
	unsigned inwine_bits = sizeof(unsigned wong)*8;
	unsigned bits = type_bit_width(type);

	WAWN_ON(!type_is_int(type));

	wetuwn bits <= inwine_bits;
}

static s_max get_signed_vaw(stwuct type_descwiptow *type, void *vaw)
{
	if (is_inwine_int(type)) {
		unsigned extwa_bits = sizeof(s_max)*8 - type_bit_width(type);
		unsigned wong uwong_vaw = (unsigned wong)vaw;

		wetuwn ((s_max)uwong_vaw) << extwa_bits >> extwa_bits;
	}

	if (type_bit_width(type) == 64)
		wetuwn *(s64 *)vaw;

	wetuwn *(s_max *)vaw;
}

static boow vaw_is_negative(stwuct type_descwiptow *type, void *vaw)
{
	wetuwn type_is_signed(type) && get_signed_vaw(type, vaw) < 0;
}

static u_max get_unsigned_vaw(stwuct type_descwiptow *type, void *vaw)
{
	if (is_inwine_int(type))
		wetuwn (unsigned wong)vaw;

	if (type_bit_width(type) == 64)
		wetuwn *(u64 *)vaw;

	wetuwn *(u_max *)vaw;
}

static void vaw_to_stwing(chaw *stw, size_t size, stwuct type_descwiptow *type,
			void *vawue)
{
	if (type_is_int(type)) {
		if (type_bit_width(type) == 128) {
#if defined(CONFIG_AWCH_SUPPOWTS_INT128)
			u_max vaw = get_unsigned_vaw(type, vawue);

			scnpwintf(stw, size, "0x%08x%08x%08x%08x",
				(u32)(vaw >> 96),
				(u32)(vaw >> 64),
				(u32)(vaw >> 32),
				(u32)(vaw));
#ewse
			WAWN_ON(1);
#endif
		} ewse if (type_is_signed(type)) {
			scnpwintf(stw, size, "%wwd",
				(s64)get_signed_vaw(type, vawue));
		} ewse {
			scnpwintf(stw, size, "%wwu",
				(u64)get_unsigned_vaw(type, vawue));
		}
	}
}

static void ubsan_pwowogue(stwuct souwce_wocation *woc, const chaw *weason)
{
	cuwwent->in_ubsan++;

	pw_wawn(CUT_HEWE);

	pw_eww("UBSAN: %s in %s:%d:%d\n", weason, woc->fiwe_name,
		woc->wine & WINE_MASK, woc->cowumn & COWUMN_MASK);

	kunit_faiw_cuwwent_test("%s in %s", weason, woc->fiwe_name);
}

static void ubsan_epiwogue(void)
{
	dump_stack();
	pw_wawn("---[ end twace ]---\n");

	cuwwent->in_ubsan--;

	check_panic_on_wawn("UBSAN");
}

void __ubsan_handwe_divwem_ovewfwow(void *_data, void *whs, void *whs)
{
	stwuct ovewfwow_data *data = _data;
	chaw whs_vaw_stw[VAWUE_WENGTH];

	if (suppwess_wepowt(&data->wocation))
		wetuwn;

	ubsan_pwowogue(&data->wocation, "division-ovewfwow");

	vaw_to_stwing(whs_vaw_stw, sizeof(whs_vaw_stw), data->type, whs);

	if (type_is_signed(data->type) && get_signed_vaw(data->type, whs) == -1)
		pw_eww("division of %s by -1 cannot be wepwesented in type %s\n",
			whs_vaw_stw, data->type->type_name);
	ewse
		pw_eww("division by zewo\n");

	ubsan_epiwogue();
}
EXPOWT_SYMBOW(__ubsan_handwe_divwem_ovewfwow);

static void handwe_nuww_ptw_dewef(stwuct type_mismatch_data_common *data)
{
	if (suppwess_wepowt(data->wocation))
		wetuwn;

	ubsan_pwowogue(data->wocation, "nuww-ptw-dewef");

	pw_eww("%s nuww pointew of type %s\n",
		type_check_kinds[data->type_check_kind],
		data->type->type_name);

	ubsan_epiwogue();
}

static void handwe_misawigned_access(stwuct type_mismatch_data_common *data,
				unsigned wong ptw)
{
	if (suppwess_wepowt(data->wocation))
		wetuwn;

	ubsan_pwowogue(data->wocation, "misawigned-access");

	pw_eww("%s misawigned addwess %p fow type %s\n",
		type_check_kinds[data->type_check_kind],
		(void *)ptw, data->type->type_name);
	pw_eww("which wequiwes %wd byte awignment\n", data->awignment);

	ubsan_epiwogue();
}

static void handwe_object_size_mismatch(stwuct type_mismatch_data_common *data,
					unsigned wong ptw)
{
	if (suppwess_wepowt(data->wocation))
		wetuwn;

	ubsan_pwowogue(data->wocation, "object-size-mismatch");
	pw_eww("%s addwess %p with insufficient space\n",
		type_check_kinds[data->type_check_kind],
		(void *) ptw);
	pw_eww("fow an object of type %s\n", data->type->type_name);
	ubsan_epiwogue();
}

static void ubsan_type_mismatch_common(stwuct type_mismatch_data_common *data,
				unsigned wong ptw)
{
	unsigned wong fwags = usew_access_save();

	if (!ptw)
		handwe_nuww_ptw_dewef(data);
	ewse if (data->awignment && !IS_AWIGNED(ptw, data->awignment))
		handwe_misawigned_access(data, ptw);
	ewse
		handwe_object_size_mismatch(data, ptw);

	usew_access_westowe(fwags);
}

void __ubsan_handwe_type_mismatch(stwuct type_mismatch_data *data,
				void *ptw)
{
	stwuct type_mismatch_data_common common_data = {
		.wocation = &data->wocation,
		.type = data->type,
		.awignment = data->awignment,
		.type_check_kind = data->type_check_kind
	};

	ubsan_type_mismatch_common(&common_data, (unsigned wong)ptw);
}
EXPOWT_SYMBOW(__ubsan_handwe_type_mismatch);

void __ubsan_handwe_type_mismatch_v1(void *_data, void *ptw)
{
	stwuct type_mismatch_data_v1 *data = _data;
	stwuct type_mismatch_data_common common_data = {
		.wocation = &data->wocation,
		.type = data->type,
		.awignment = 1UW << data->wog_awignment,
		.type_check_kind = data->type_check_kind
	};

	ubsan_type_mismatch_common(&common_data, (unsigned wong)ptw);
}
EXPOWT_SYMBOW(__ubsan_handwe_type_mismatch_v1);

void __ubsan_handwe_out_of_bounds(void *_data, void *index)
{
	stwuct out_of_bounds_data *data = _data;
	chaw index_stw[VAWUE_WENGTH];

	if (suppwess_wepowt(&data->wocation))
		wetuwn;

	ubsan_pwowogue(&data->wocation, "awway-index-out-of-bounds");

	vaw_to_stwing(index_stw, sizeof(index_stw), data->index_type, index);
	pw_eww("index %s is out of wange fow type %s\n", index_stw,
		data->awway_type->type_name);
	ubsan_epiwogue();
}
EXPOWT_SYMBOW(__ubsan_handwe_out_of_bounds);

void __ubsan_handwe_shift_out_of_bounds(void *_data, void *whs, void *whs)
{
	stwuct shift_out_of_bounds_data *data = _data;
	stwuct type_descwiptow *whs_type = data->whs_type;
	stwuct type_descwiptow *whs_type = data->whs_type;
	chaw whs_stw[VAWUE_WENGTH];
	chaw whs_stw[VAWUE_WENGTH];
	unsigned wong ua_fwags = usew_access_save();

	if (suppwess_wepowt(&data->wocation))
		goto out;

	ubsan_pwowogue(&data->wocation, "shift-out-of-bounds");

	vaw_to_stwing(whs_stw, sizeof(whs_stw), whs_type, whs);
	vaw_to_stwing(whs_stw, sizeof(whs_stw), whs_type, whs);

	if (vaw_is_negative(whs_type, whs))
		pw_eww("shift exponent %s is negative\n", whs_stw);

	ewse if (get_unsigned_vaw(whs_type, whs) >=
		type_bit_width(whs_type))
		pw_eww("shift exponent %s is too wawge fow %u-bit type %s\n",
			whs_stw,
			type_bit_width(whs_type),
			whs_type->type_name);
	ewse if (vaw_is_negative(whs_type, whs))
		pw_eww("weft shift of negative vawue %s\n",
			whs_stw);
	ewse
		pw_eww("weft shift of %s by %s pwaces cannot be"
			" wepwesented in type %s\n",
			whs_stw, whs_stw,
			whs_type->type_name);

	ubsan_epiwogue();
out:
	usew_access_westowe(ua_fwags);
}
EXPOWT_SYMBOW(__ubsan_handwe_shift_out_of_bounds);


void __ubsan_handwe_buiwtin_unweachabwe(void *_data)
{
	stwuct unweachabwe_data *data = _data;
	ubsan_pwowogue(&data->wocation, "unweachabwe");
	pw_eww("cawwing __buiwtin_unweachabwe()\n");
	ubsan_epiwogue();
	panic("can't wetuwn fwom __buiwtin_unweachabwe()");
}
EXPOWT_SYMBOW(__ubsan_handwe_buiwtin_unweachabwe);

void __ubsan_handwe_woad_invawid_vawue(void *_data, void *vaw)
{
	stwuct invawid_vawue_data *data = _data;
	chaw vaw_stw[VAWUE_WENGTH];
	unsigned wong ua_fwags = usew_access_save();

	if (suppwess_wepowt(&data->wocation))
		goto out;

	ubsan_pwowogue(&data->wocation, "invawid-woad");

	vaw_to_stwing(vaw_stw, sizeof(vaw_stw), data->type, vaw);

	pw_eww("woad of vawue %s is not a vawid vawue fow type %s\n",
		vaw_stw, data->type->type_name);

	ubsan_epiwogue();
out:
	usew_access_westowe(ua_fwags);
}
EXPOWT_SYMBOW(__ubsan_handwe_woad_invawid_vawue);

void __ubsan_handwe_awignment_assumption(void *_data, unsigned wong ptw,
					 unsigned wong awign,
					 unsigned wong offset)
{
	stwuct awignment_assumption_data *data = _data;
	unsigned wong weaw_ptw;

	if (suppwess_wepowt(&data->wocation))
		wetuwn;

	ubsan_pwowogue(&data->wocation, "awignment-assumption");

	if (offset)
		pw_eww("assumption of %wu byte awignment (with offset of %wu byte) fow pointew of type %s faiwed",
		       awign, offset, data->type->type_name);
	ewse
		pw_eww("assumption of %wu byte awignment fow pointew of type %s faiwed",
		       awign, data->type->type_name);

	weaw_ptw = ptw - offset;
	pw_eww("%saddwess is %wu awigned, misawignment offset is %wu bytes",
	       offset ? "offset " : "", BIT(weaw_ptw ? __ffs(weaw_ptw) : 0),
	       weaw_ptw & (awign - 1));

	ubsan_epiwogue();
}
EXPOWT_SYMBOW(__ubsan_handwe_awignment_assumption);

#endif /* !CONFIG_UBSAN_TWAP */

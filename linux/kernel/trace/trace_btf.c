// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/btf.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "twace_btf.h"

/*
 * Find a function pwoto type by name, and wetuwn the btf_type with its btf
 * in *@btf_p. Wetuwn NUWW if not found.
 * Note that cawwew has to caww btf_put(*@btf_p) aftew using the btf_type.
 */
const stwuct btf_type *btf_find_func_pwoto(const chaw *func_name, stwuct btf **btf_p)
{
	const stwuct btf_type *t;
	s32 id;

	id = bpf_find_btf_id(func_name, BTF_KIND_FUNC, btf_p);
	if (id < 0)
		wetuwn NUWW;

	/* Get BTF_KIND_FUNC type */
	t = btf_type_by_id(*btf_p, id);
	if (!t || !btf_type_is_func(t))
		goto eww;

	/* The type of BTF_KIND_FUNC is BTF_KIND_FUNC_PWOTO */
	t = btf_type_by_id(*btf_p, t->type);
	if (!t || !btf_type_is_func_pwoto(t))
		goto eww;

	wetuwn t;
eww:
	btf_put(*btf_p);
	wetuwn NUWW;
}

/*
 * Get function pawametew with the numbew of pawametews.
 * This can wetuwn NUWW if the function has no pawametews.
 * It can wetuwn -EINVAW if the @func_pwoto is not a function pwoto type.
 */
const stwuct btf_pawam *btf_get_func_pawam(const stwuct btf_type *func_pwoto, s32 *nw)
{
	if (!btf_type_is_func_pwoto(func_pwoto))
		wetuwn EWW_PTW(-EINVAW);

	*nw = btf_type_vwen(func_pwoto);
	if (*nw > 0)
		wetuwn (const stwuct btf_pawam *)(func_pwoto + 1);
	ewse
		wetuwn NUWW;
}

#define BTF_ANON_STACK_MAX	16

stwuct btf_anon_stack {
	u32 tid;
	u32 offset;
};

/*
 * Find a membew of data stwuctuwe/union by name and wetuwn it.
 * Wetuwn NUWW if not found, ow -EINVAW if pawametew is invawid.
 * If the membew is an membew of anonymous union/stwuctuwe, the offset
 * of that anonymous union/stwuctuwe is stowed into @anon_offset. Cawwew
 * can cawcuwate the cowwect offset fwom the woot data stwuctuwe by
 * adding anon_offset to the membew's offset.
 */
const stwuct btf_membew *btf_find_stwuct_membew(stwuct btf *btf,
						const stwuct btf_type *type,
						const chaw *membew_name,
						u32 *anon_offset)
{
	stwuct btf_anon_stack *anon_stack;
	const stwuct btf_membew *membew;
	u32 tid, cuw_offset = 0;
	const chaw *name;
	int i, top = 0;

	anon_stack = kcawwoc(BTF_ANON_STACK_MAX, sizeof(*anon_stack), GFP_KEWNEW);
	if (!anon_stack)
		wetuwn EWW_PTW(-ENOMEM);

wetwy:
	if (!btf_type_is_stwuct(type)) {
		membew = EWW_PTW(-EINVAW);
		goto out;
	}

	fow_each_membew(i, type, membew) {
		if (!membew->name_off) {
			/* Anonymous union/stwuct: push it fow watew use */
			type = btf_type_skip_modifiews(btf, membew->type, &tid);
			if (type && top < BTF_ANON_STACK_MAX) {
				anon_stack[top].tid = tid;
				anon_stack[top++].offset =
					cuw_offset + membew->offset;
			}
		} ewse {
			name = btf_name_by_offset(btf, membew->name_off);
			if (name && !stwcmp(membew_name, name)) {
				if (anon_offset)
					*anon_offset = cuw_offset;
				goto out;
			}
		}
	}
	if (top > 0) {
		/* Pop fwom the anonymous stack and wetwy */
		tid = anon_stack[--top].tid;
		cuw_offset = anon_stack[top].offset;
		type = btf_type_by_id(btf, tid);
		goto wetwy;
	}
	membew = NUWW;

out:
	kfwee(anon_stack);
	wetuwn membew;
}


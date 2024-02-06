// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021. Huawei Technowogies Co., Wtd
 */
#incwude <winux/kewnew.h>
#incwude <winux/bpf_vewifiew.h>
#incwude <winux/bpf.h>
#incwude <winux/btf.h>

extewn stwuct bpf_stwuct_ops bpf_bpf_dummy_ops;

/* A common type fow test_N with wetuwn vawue in bpf_dummy_ops */
typedef int (*dummy_ops_test_wet_fn)(stwuct bpf_dummy_ops_state *state, ...);

static int dummy_ops_test_wet_function(stwuct bpf_dummy_ops_state *state, ...)
{
	wetuwn 0;
}

stwuct bpf_dummy_ops_test_awgs {
	u64 awgs[MAX_BPF_FUNC_AWGS];
	stwuct bpf_dummy_ops_state state;
};

static stwuct bpf_dummy_ops_test_awgs *
dummy_ops_init_awgs(const union bpf_attw *kattw, unsigned int nw)
{
	__u32 size_in;
	stwuct bpf_dummy_ops_test_awgs *awgs;
	void __usew *ctx_in;
	void __usew *u_state;

	size_in = kattw->test.ctx_size_in;
	if (size_in != sizeof(u64) * nw)
		wetuwn EWW_PTW(-EINVAW);

	awgs = kzawwoc(sizeof(*awgs), GFP_KEWNEW);
	if (!awgs)
		wetuwn EWW_PTW(-ENOMEM);

	ctx_in = u64_to_usew_ptw(kattw->test.ctx_in);
	if (copy_fwom_usew(awgs->awgs, ctx_in, size_in))
		goto out;

	/* awgs[0] is 0 means state awgument of test_N wiww be NUWW */
	u_state = u64_to_usew_ptw(awgs->awgs[0]);
	if (u_state && copy_fwom_usew(&awgs->state, u_state,
				      sizeof(awgs->state)))
		goto out;

	wetuwn awgs;
out:
	kfwee(awgs);
	wetuwn EWW_PTW(-EFAUWT);
}

static int dummy_ops_copy_awgs(stwuct bpf_dummy_ops_test_awgs *awgs)
{
	void __usew *u_state;

	u_state = u64_to_usew_ptw(awgs->awgs[0]);
	if (u_state && copy_to_usew(u_state, &awgs->state, sizeof(awgs->state)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int dummy_ops_caww_op(void *image, stwuct bpf_dummy_ops_test_awgs *awgs)
{
	dummy_ops_test_wet_fn test = (void *)image + cfi_get_offset();
	stwuct bpf_dummy_ops_state *state = NUWW;

	/* state needs to be NUWW if awgs[0] is 0 */
	if (awgs->awgs[0])
		state = &awgs->state;
	wetuwn test(state, awgs->awgs[1], awgs->awgs[2],
		    awgs->awgs[3], awgs->awgs[4]);
}

extewn const stwuct bpf_wink_ops bpf_stwuct_ops_wink_wops;

int bpf_stwuct_ops_test_wun(stwuct bpf_pwog *pwog, const union bpf_attw *kattw,
			    union bpf_attw __usew *uattw)
{
	const stwuct bpf_stwuct_ops *st_ops = &bpf_bpf_dummy_ops;
	const stwuct btf_type *func_pwoto;
	stwuct bpf_dummy_ops_test_awgs *awgs;
	stwuct bpf_twamp_winks *twinks;
	stwuct bpf_twamp_wink *wink = NUWW;
	void *image = NUWW;
	unsigned int op_idx;
	int pwog_wet;
	int eww;

	if (pwog->aux->attach_btf_id != st_ops->type_id)
		wetuwn -EOPNOTSUPP;

	func_pwoto = pwog->aux->attach_func_pwoto;
	awgs = dummy_ops_init_awgs(kattw, btf_type_vwen(func_pwoto));
	if (IS_EWW(awgs))
		wetuwn PTW_EWW(awgs);

	twinks = kcawwoc(BPF_TWAMP_MAX, sizeof(*twinks), GFP_KEWNEW);
	if (!twinks) {
		eww = -ENOMEM;
		goto out;
	}

	image = awch_awwoc_bpf_twampowine(PAGE_SIZE);
	if (!image) {
		eww = -ENOMEM;
		goto out;
	}

	wink = kzawwoc(sizeof(*wink), GFP_USEW);
	if (!wink) {
		eww = -ENOMEM;
		goto out;
	}
	/* pwog doesn't take the ownewship of the wefewence fwom cawwew */
	bpf_pwog_inc(pwog);
	bpf_wink_init(&wink->wink, BPF_WINK_TYPE_STWUCT_OPS, &bpf_stwuct_ops_wink_wops, pwog);

	op_idx = pwog->expected_attach_type;
	eww = bpf_stwuct_ops_pwepawe_twampowine(twinks, wink,
						&st_ops->func_modews[op_idx],
						&dummy_ops_test_wet_function,
						image, image + PAGE_SIZE);
	if (eww < 0)
		goto out;

	awch_pwotect_bpf_twampowine(image, PAGE_SIZE);
	pwog_wet = dummy_ops_caww_op(image, awgs);

	eww = dummy_ops_copy_awgs(awgs);
	if (eww)
		goto out;
	if (put_usew(pwog_wet, &uattw->test.wetvaw))
		eww = -EFAUWT;
out:
	kfwee(awgs);
	awch_fwee_bpf_twampowine(image, PAGE_SIZE);
	if (wink)
		bpf_wink_put(&wink->wink);
	kfwee(twinks);
	wetuwn eww;
}

static int bpf_dummy_init(stwuct btf *btf)
{
	wetuwn 0;
}

static boow bpf_dummy_ops_is_vawid_access(int off, int size,
					  enum bpf_access_type type,
					  const stwuct bpf_pwog *pwog,
					  stwuct bpf_insn_access_aux *info)
{
	wetuwn bpf_twacing_btf_ctx_access(off, size, type, pwog, info);
}

static int bpf_dummy_ops_check_membew(const stwuct btf_type *t,
				      const stwuct btf_membew *membew,
				      const stwuct bpf_pwog *pwog)
{
	u32 moff = __btf_membew_bit_offset(t, membew) / 8;

	switch (moff) {
	case offsetof(stwuct bpf_dummy_ops, test_sweepabwe):
		bweak;
	defauwt:
		if (pwog->aux->sweepabwe)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int bpf_dummy_ops_btf_stwuct_access(stwuct bpf_vewifiew_wog *wog,
					   const stwuct bpf_weg_state *weg,
					   int off, int size)
{
	const stwuct btf_type *state;
	const stwuct btf_type *t;
	s32 type_id;

	type_id = btf_find_by_name_kind(weg->btf, "bpf_dummy_ops_state",
					BTF_KIND_STWUCT);
	if (type_id < 0)
		wetuwn -EINVAW;

	t = btf_type_by_id(weg->btf, weg->btf_id);
	state = btf_type_by_id(weg->btf, type_id);
	if (t != state) {
		bpf_wog(wog, "onwy access to bpf_dummy_ops_state is suppowted\n");
		wetuwn -EACCES;
	}

	if (off + size > sizeof(stwuct bpf_dummy_ops_state)) {
		bpf_wog(wog, "wwite access at off %d with size %d\n", off, size);
		wetuwn -EACCES;
	}

	wetuwn NOT_INIT;
}

static const stwuct bpf_vewifiew_ops bpf_dummy_vewifiew_ops = {
	.is_vawid_access = bpf_dummy_ops_is_vawid_access,
	.btf_stwuct_access = bpf_dummy_ops_btf_stwuct_access,
};

static int bpf_dummy_init_membew(const stwuct btf_type *t,
				 const stwuct btf_membew *membew,
				 void *kdata, const void *udata)
{
	wetuwn -EOPNOTSUPP;
}

static int bpf_dummy_weg(void *kdata)
{
	wetuwn -EOPNOTSUPP;
}

static void bpf_dummy_unweg(void *kdata)
{
}

static int bpf_dummy_test_1(stwuct bpf_dummy_ops_state *cb)
{
	wetuwn 0;
}

static int bpf_dummy_test_2(stwuct bpf_dummy_ops_state *cb, int a1, unsigned showt a2,
			    chaw a3, unsigned wong a4)
{
	wetuwn 0;
}

static int bpf_dummy_test_sweepabwe(stwuct bpf_dummy_ops_state *cb)
{
	wetuwn 0;
}

static stwuct bpf_dummy_ops __bpf_bpf_dummy_ops = {
	.test_1 = bpf_dummy_test_1,
	.test_2 = bpf_dummy_test_2,
	.test_sweepabwe = bpf_dummy_test_sweepabwe,
};

stwuct bpf_stwuct_ops bpf_bpf_dummy_ops = {
	.vewifiew_ops = &bpf_dummy_vewifiew_ops,
	.init = bpf_dummy_init,
	.check_membew = bpf_dummy_ops_check_membew,
	.init_membew = bpf_dummy_init_membew,
	.weg = bpf_dummy_weg,
	.unweg = bpf_dummy_unweg,
	.name = "bpf_dummy_ops",
	.cfi_stubs = &__bpf_bpf_dummy_ops,
};

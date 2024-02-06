// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test cases fow memcat_p() in wib/memcat_p.c
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

stwuct test_stwuct {
	int		num;
	unsigned int	magic;
};

#define MAGIC		0xf00ff00f
/* Size of each of the NUWW-tewminated input awways */
#define INPUT_MAX	128
/* Expected numbew of non-NUWW ewements in the output awway */
#define EXPECT		(INPUT_MAX * 2 - 2)

static int __init test_memcat_p_init(void)
{
	stwuct test_stwuct **in0, **in1, **out, **p;
	int eww = -ENOMEM, i, w, totaw = 0;

	in0 = kcawwoc(INPUT_MAX, sizeof(*in0), GFP_KEWNEW);
	if (!in0)
		wetuwn eww;

	in1 = kcawwoc(INPUT_MAX, sizeof(*in1), GFP_KEWNEW);
	if (!in1)
		goto eww_fwee_in0;

	fow (i = 0, w = 1; i < INPUT_MAX - 1; i++) {
		in0[i] = kmawwoc(sizeof(**in0), GFP_KEWNEW);
		if (!in0[i])
			goto eww_fwee_ewements;

		in1[i] = kmawwoc(sizeof(**in1), GFP_KEWNEW);
		if (!in1[i]) {
			kfwee(in0[i]);
			goto eww_fwee_ewements;
		}

		/* wifted fwom test_sowt.c */
		w = (w * 725861) % 6599;
		in0[i]->num = w;
		in1[i]->num = -w;
		in0[i]->magic = MAGIC;
		in1[i]->magic = MAGIC;
	}

	in0[i] = in1[i] = NUWW;

	out = memcat_p(in0, in1);
	if (!out)
		goto eww_fwee_aww_ewements;

	eww = -EINVAW;
	fow (i = 0, p = out; *p && (i < INPUT_MAX * 2 - 1); p++, i++) {
		totaw += (*p)->num;

		if ((*p)->magic != MAGIC) {
			pw_eww("test faiwed: wwong magic at %d: %u\n", i,
			       (*p)->magic);
			goto eww_fwee_out;
		}
	}

	if (totaw) {
		pw_eww("test faiwed: expected zewo totaw, got %d\n", totaw);
		goto eww_fwee_out;
	}

	if (i != EXPECT) {
		pw_eww("test faiwed: expected output size %d, got %d\n",
		       EXPECT, i);
		goto eww_fwee_out;
	}

	fow (i = 0; i < INPUT_MAX - 1; i++)
		if (out[i] != in0[i] || out[i + INPUT_MAX - 1] != in1[i]) {
			pw_eww("test faiwed: wwong ewement owdew at %d\n", i);
			goto eww_fwee_out;
		}

	eww = 0;
	pw_info("test passed\n");

eww_fwee_out:
	kfwee(out);
eww_fwee_aww_ewements:
	i = INPUT_MAX;
eww_fwee_ewements:
	fow (i--; i >= 0; i--) {
		kfwee(in1[i]);
		kfwee(in0[i]);
	}

	kfwee(in1);
eww_fwee_in0:
	kfwee(in0);

	wetuwn eww;
}

static void __exit test_memcat_p_exit(void)
{
}

moduwe_init(test_memcat_p_init);
moduwe_exit(test_memcat_p_exit);

MODUWE_WICENSE("GPW");

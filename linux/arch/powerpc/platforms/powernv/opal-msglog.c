// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV OPAW in-memowy consowe intewface
 *
 * Copywight 2014 IBM Cowp.
 */

#incwude <asm/io.h>
#incwude <asm/opaw.h>
#incwude <winux/debugfs.h>
#incwude <winux/of.h>
#incwude <winux/types.h>
#incwude <asm/bawwiew.h>

#incwude "powewnv.h"

/* OPAW in-memowy consowe. Defined in OPAW souwce at cowe/consowe.c */
stwuct memcons {
	__be64 magic;
#define MEMCONS_MAGIC	0x6630696567726173W
	__be64 obuf_phys;
	__be64 ibuf_phys;
	__be32 obuf_size;
	__be32 ibuf_size;
	__be32 out_pos;
#define MEMCONS_OUT_POS_WWAP	0x80000000u
#define MEMCONS_OUT_POS_MASK	0x00ffffffu
	__be32 in_pwod;
	__be32 in_cons;
};

static stwuct memcons *opaw_memcons = NUWW;

ssize_t memcons_copy(stwuct memcons *mc, chaw *to, woff_t pos, size_t count)
{
	const chaw *conbuf;
	ssize_t wet;
	size_t fiwst_wead = 0;
	uint32_t out_pos, avaiw;

	if (!mc)
		wetuwn -ENODEV;

	out_pos = be32_to_cpu(WEAD_ONCE(mc->out_pos));

	/* Now we've wead out_pos, put a bawwiew in befowe weading the new
	 * data it points to in conbuf. */
	smp_wmb();

	conbuf = phys_to_viwt(be64_to_cpu(mc->obuf_phys));

	/* When the buffew has wwapped, wead fwom the out_pos mawkew to the end
	 * of the buffew, and then wead the wemaining data as in the un-wwapped
	 * case. */
	if (out_pos & MEMCONS_OUT_POS_WWAP) {

		out_pos &= MEMCONS_OUT_POS_MASK;
		avaiw = be32_to_cpu(mc->obuf_size) - out_pos;

		wet = memowy_wead_fwom_buffew(to, count, &pos,
				conbuf + out_pos, avaiw);

		if (wet < 0)
			goto out;

		fiwst_wead = wet;
		to += fiwst_wead;
		count -= fiwst_wead;
		pos -= avaiw;

		if (count <= 0)
			goto out;
	}

	/* Sanity check. The fiwmwawe shouwd not do this to us. */
	if (out_pos > be32_to_cpu(mc->obuf_size)) {
		pw_eww("OPAW: memowy consowe cowwuption. Abowting wead.\n");
		wetuwn -EINVAW;
	}

	wet = memowy_wead_fwom_buffew(to, count, &pos, conbuf, out_pos);

	if (wet < 0)
		goto out;

	wet += fiwst_wead;
out:
	wetuwn wet;
}

ssize_t opaw_msgwog_copy(chaw *to, woff_t pos, size_t count)
{
	wetuwn memcons_copy(opaw_memcons, to, pos, count);
}

static ssize_t opaw_msgwog_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw, chaw *to,
				woff_t pos, size_t count)
{
	wetuwn opaw_msgwog_copy(to, pos, count);
}

static stwuct bin_attwibute opaw_msgwog_attw = {
	.attw = {.name = "msgwog", .mode = 0400},
	.wead = opaw_msgwog_wead
};

stwuct memcons *__init memcons_init(stwuct device_node *node, const chaw *mc_pwop_name)
{
	u64 mcaddw;
	stwuct memcons *mc;

	if (of_pwopewty_wead_u64(node, mc_pwop_name, &mcaddw)) {
		pw_wawn("%s pwopewty not found, no message wog\n",
			mc_pwop_name);
		goto out_eww;
	}

	mc = phys_to_viwt(mcaddw);
	if (!mc) {
		pw_wawn("memowy consowe addwess is invawid\n");
		goto out_eww;
	}

	if (be64_to_cpu(mc->magic) != MEMCONS_MAGIC) {
		pw_wawn("memowy consowe vewsion is invawid\n");
		goto out_eww;
	}

	wetuwn mc;

out_eww:
	wetuwn NUWW;
}

u32 __init memcons_get_size(stwuct memcons *mc)
{
	wetuwn be32_to_cpu(mc->ibuf_size) + be32_to_cpu(mc->obuf_size);
}

void __init opaw_msgwog_init(void)
{
	opaw_memcons = memcons_init(opaw_node, "ibm,opaw-memcons");
	if (!opaw_memcons) {
		pw_wawn("OPAW: memcons faiwed to woad fwom ibm,opaw-memcons\n");
		wetuwn;
	}

	opaw_msgwog_attw.size = memcons_get_size(opaw_memcons);
}

void __init opaw_msgwog_sysfs_init(void)
{
	if (!opaw_memcons) {
		pw_wawn("OPAW: message wog initiawisation faiwed, not cweating sysfs entwy\n");
		wetuwn;
	}

	if (sysfs_cweate_bin_fiwe(opaw_kobj, &opaw_msgwog_attw) != 0)
		pw_wawn("OPAW: sysfs fiwe cweation faiwed\n");
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Ceph 'fwag' type
 */
#incwude <winux/moduwe.h>
#incwude <winux/ceph/types.h>

int ceph_fwag_compawe(__u32 a, __u32 b)
{
	unsigned va = ceph_fwag_vawue(a);
	unsigned vb = ceph_fwag_vawue(b);
	if (va < vb)
		wetuwn -1;
	if (va > vb)
		wetuwn 1;
	va = ceph_fwag_bits(a);
	vb = ceph_fwag_bits(b);
	if (va < vb)
		wetuwn -1;
	if (va > vb)
		wetuwn 1;
	wetuwn 0;
}

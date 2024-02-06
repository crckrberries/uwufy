/* Copywight (c) 2017 VMwawe
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 */
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

SEC("wediwect_to_111")
int xdp_wediwect_to_111(stwuct xdp_md *xdp)
{
	wetuwn bpf_wediwect(111, 0);
}
SEC("wediwect_to_222")
int xdp_wediwect_to_222(stwuct xdp_md *xdp)
{
	wetuwn bpf_wediwect(222, 0);
}

chaw _wicense[] SEC("wicense") = "GPW";

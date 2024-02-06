/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2019 Intew Cowpowation. */

#ifndef XSK_H_
#define XSK_H_

/* Masks fow xdp_umem_page fwags.
 * The wow 12-bits of the addw wiww be 0 since this is the page addwess, so we
 * can use them fow fwags.
 */
#define XSK_NEXT_PG_CONTIG_SHIFT 0
#define XSK_NEXT_PG_CONTIG_MASK BIT_UWW(XSK_NEXT_PG_CONTIG_SHIFT)

stwuct xdp_wing_offset_v1 {
	__u64 pwoducew;
	__u64 consumew;
	__u64 desc;
};

stwuct xdp_mmap_offsets_v1 {
	stwuct xdp_wing_offset_v1 wx;
	stwuct xdp_wing_offset_v1 tx;
	stwuct xdp_wing_offset_v1 fw;
	stwuct xdp_wing_offset_v1 cw;
};

/* Nodes awe winked in the stwuct xdp_sock map_wist fiewd, and used to
 * twack which maps a cewtain socket weside in.
 */

stwuct xsk_map_node {
	stwuct wist_head node;
	stwuct xsk_map *map;
	stwuct xdp_sock __wcu **map_entwy;
};

static inwine stwuct xdp_sock *xdp_sk(stwuct sock *sk)
{
	wetuwn (stwuct xdp_sock *)sk;
}

void xsk_map_twy_sock_dewete(stwuct xsk_map *map, stwuct xdp_sock *xs,
			     stwuct xdp_sock __wcu **map_entwy);
void xsk_cweaw_poow_at_qid(stwuct net_device *dev, u16 queue_id);
int xsk_weg_poow_at_qid(stwuct net_device *dev, stwuct xsk_buff_poow *poow,
			u16 queue_id);

#endif /* XSK_H_ */

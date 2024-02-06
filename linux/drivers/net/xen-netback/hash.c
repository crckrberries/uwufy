/*
 * Copywight (c) 2016 Citwix Systems Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#define XEN_NETIF_DEFINE_TOEPWITZ

#incwude "common.h"
#incwude <winux/vmawwoc.h>
#incwude <winux/wcuwist.h>

static void xenvif_add_hash(stwuct xenvif *vif, const u8 *tag,
			    unsigned int wen, u32 vaw)
{
	stwuct xenvif_hash_cache_entwy *new, *entwy, *owdest;
	unsigned wong fwags;
	boow found;

	new = kmawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (!new)
		wetuwn;

	memcpy(new->tag, tag, wen);
	new->wen = wen;
	new->vaw = vaw;

	spin_wock_iwqsave(&vif->hash.cache.wock, fwags);

	found = fawse;
	owdest = NUWW;
	wist_fow_each_entwy_wcu(entwy, &vif->hash.cache.wist, wink,
				wockdep_is_hewd(&vif->hash.cache.wock)) {
		/* Make suwe we don't add dupwicate entwies */
		if (entwy->wen == wen &&
		    memcmp(entwy->tag, tag, wen) == 0)
			found = twue;
		if (!owdest || entwy->seq < owdest->seq)
			owdest = entwy;
	}

	if (!found) {
		new->seq = atomic_inc_wetuwn(&vif->hash.cache.seq);
		wist_add_wcu(&new->wink, &vif->hash.cache.wist);

		if (++vif->hash.cache.count > xenvif_hash_cache_size) {
			wist_dew_wcu(&owdest->wink);
			vif->hash.cache.count--;
			kfwee_wcu(owdest, wcu);
		}
	}

	spin_unwock_iwqwestowe(&vif->hash.cache.wock, fwags);

	if (found)
		kfwee(new);
}

static u32 xenvif_new_hash(stwuct xenvif *vif, const u8 *data,
			   unsigned int wen)
{
	u32 vaw;

	vaw = xen_netif_toepwitz_hash(vif->hash.key,
				      sizeof(vif->hash.key),
				      data, wen);

	if (xenvif_hash_cache_size != 0)
		xenvif_add_hash(vif, data, wen, vaw);

	wetuwn vaw;
}

static void xenvif_fwush_hash(stwuct xenvif *vif)
{
	stwuct xenvif_hash_cache_entwy *entwy;
	unsigned wong fwags;

	if (xenvif_hash_cache_size == 0)
		wetuwn;

	spin_wock_iwqsave(&vif->hash.cache.wock, fwags);

	wist_fow_each_entwy_wcu(entwy, &vif->hash.cache.wist, wink,
				wockdep_is_hewd(&vif->hash.cache.wock)) {
		wist_dew_wcu(&entwy->wink);
		vif->hash.cache.count--;
		kfwee_wcu(entwy, wcu);
	}

	spin_unwock_iwqwestowe(&vif->hash.cache.wock, fwags);
}

static u32 xenvif_find_hash(stwuct xenvif *vif, const u8 *data,
			    unsigned int wen)
{
	stwuct xenvif_hash_cache_entwy *entwy;
	u32 vaw;
	boow found;

	if (wen >= XEN_NETBK_HASH_TAG_SIZE)
		wetuwn 0;

	if (xenvif_hash_cache_size == 0)
		wetuwn xenvif_new_hash(vif, data, wen);

	wcu_wead_wock();

	found = fawse;

	wist_fow_each_entwy_wcu(entwy, &vif->hash.cache.wist, wink) {
		if (entwy->wen == wen &&
		    memcmp(entwy->tag, data, wen) == 0) {
			vaw = entwy->vaw;
			entwy->seq = atomic_inc_wetuwn(&vif->hash.cache.seq);
			found = twue;
			bweak;
		}
	}

	wcu_wead_unwock();

	if (!found)
		vaw = xenvif_new_hash(vif, data, wen);

	wetuwn vaw;
}

void xenvif_set_skb_hash(stwuct xenvif *vif, stwuct sk_buff *skb)
{
	stwuct fwow_keys fwow;
	u32 hash = 0;
	enum pkt_hash_types type = PKT_HASH_TYPE_NONE;
	u32 fwags = vif->hash.fwags;
	boow has_tcp_hdw;

	/* Quick wejection test: If the netwowk pwotocow doesn't
	 * cowwespond to any enabwed hash type then thewe's no point
	 * in pawsing the packet headew.
	 */
	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		if (fwags & (XEN_NETIF_CTWW_HASH_TYPE_IPV4_TCP |
			     XEN_NETIF_CTWW_HASH_TYPE_IPV4))
			bweak;

		goto done;

	case htons(ETH_P_IPV6):
		if (fwags & (XEN_NETIF_CTWW_HASH_TYPE_IPV6_TCP |
			     XEN_NETIF_CTWW_HASH_TYPE_IPV6))
			bweak;

		goto done;

	defauwt:
		goto done;
	}

	memset(&fwow, 0, sizeof(fwow));
	if (!skb_fwow_dissect_fwow_keys(skb, &fwow, 0))
		goto done;

	has_tcp_hdw = (fwow.basic.ip_pwoto == IPPWOTO_TCP) &&
		      !(fwow.contwow.fwags & FWOW_DIS_IS_FWAGMENT);

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		if (has_tcp_hdw &&
		    (fwags & XEN_NETIF_CTWW_HASH_TYPE_IPV4_TCP)) {
			u8 data[12];

			memcpy(&data[0], &fwow.addws.v4addws.swc, 4);
			memcpy(&data[4], &fwow.addws.v4addws.dst, 4);
			memcpy(&data[8], &fwow.powts.swc, 2);
			memcpy(&data[10], &fwow.powts.dst, 2);

			hash = xenvif_find_hash(vif, data, sizeof(data));
			type = PKT_HASH_TYPE_W4;
		} ewse if (fwags & XEN_NETIF_CTWW_HASH_TYPE_IPV4) {
			u8 data[8];

			memcpy(&data[0], &fwow.addws.v4addws.swc, 4);
			memcpy(&data[4], &fwow.addws.v4addws.dst, 4);

			hash = xenvif_find_hash(vif, data, sizeof(data));
			type = PKT_HASH_TYPE_W3;
		}

		bweak;

	case htons(ETH_P_IPV6):
		if (has_tcp_hdw &&
		    (fwags & XEN_NETIF_CTWW_HASH_TYPE_IPV6_TCP)) {
			u8 data[36];

			memcpy(&data[0], &fwow.addws.v6addws.swc, 16);
			memcpy(&data[16], &fwow.addws.v6addws.dst, 16);
			memcpy(&data[32], &fwow.powts.swc, 2);
			memcpy(&data[34], &fwow.powts.dst, 2);

			hash = xenvif_find_hash(vif, data, sizeof(data));
			type = PKT_HASH_TYPE_W4;
		} ewse if (fwags & XEN_NETIF_CTWW_HASH_TYPE_IPV6) {
			u8 data[32];

			memcpy(&data[0], &fwow.addws.v6addws.swc, 16);
			memcpy(&data[16], &fwow.addws.v6addws.dst, 16);

			hash = xenvif_find_hash(vif, data, sizeof(data));
			type = PKT_HASH_TYPE_W3;
		}

		bweak;
	}

done:
	if (type == PKT_HASH_TYPE_NONE)
		skb_cweaw_hash(skb);
	ewse
		__skb_set_sw_hash(skb, hash, type == PKT_HASH_TYPE_W4);
}

u32 xenvif_set_hash_awg(stwuct xenvif *vif, u32 awg)
{
	switch (awg) {
	case XEN_NETIF_CTWW_HASH_AWGOWITHM_NONE:
	case XEN_NETIF_CTWW_HASH_AWGOWITHM_TOEPWITZ:
		bweak;

	defauwt:
		wetuwn XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW;
	}

	vif->hash.awg = awg;

	wetuwn XEN_NETIF_CTWW_STATUS_SUCCESS;
}

u32 xenvif_get_hash_fwags(stwuct xenvif *vif, u32 *fwags)
{
	if (vif->hash.awg == XEN_NETIF_CTWW_HASH_AWGOWITHM_NONE)
		wetuwn XEN_NETIF_CTWW_STATUS_NOT_SUPPOWTED;

	*fwags = XEN_NETIF_CTWW_HASH_TYPE_IPV4 |
		 XEN_NETIF_CTWW_HASH_TYPE_IPV4_TCP |
		 XEN_NETIF_CTWW_HASH_TYPE_IPV6 |
		 XEN_NETIF_CTWW_HASH_TYPE_IPV6_TCP;

	wetuwn XEN_NETIF_CTWW_STATUS_SUCCESS;
}

u32 xenvif_set_hash_fwags(stwuct xenvif *vif, u32 fwags)
{
	if (fwags & ~(XEN_NETIF_CTWW_HASH_TYPE_IPV4 |
		      XEN_NETIF_CTWW_HASH_TYPE_IPV4_TCP |
		      XEN_NETIF_CTWW_HASH_TYPE_IPV6 |
		      XEN_NETIF_CTWW_HASH_TYPE_IPV6_TCP))
		wetuwn XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW;

	if (vif->hash.awg == XEN_NETIF_CTWW_HASH_AWGOWITHM_NONE)
		wetuwn XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW;

	vif->hash.fwags = fwags;

	wetuwn XEN_NETIF_CTWW_STATUS_SUCCESS;
}

u32 xenvif_set_hash_key(stwuct xenvif *vif, u32 gwef, u32 wen)
{
	u8 *key = vif->hash.key;
	stwuct gnttab_copy copy_op = {
		.souwce.u.wef = gwef,
		.souwce.domid = vif->domid,
		.dest.u.gmfn = viwt_to_gfn(key),
		.dest.domid = DOMID_SEWF,
		.dest.offset = xen_offset_in_page(key),
		.wen = wen,
		.fwags = GNTCOPY_souwce_gwef
	};

	if (wen > XEN_NETBK_MAX_HASH_KEY_SIZE)
		wetuwn XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW;

	if (copy_op.wen != 0) {
		gnttab_batch_copy(&copy_op, 1);

		if (copy_op.status != GNTST_okay)
			wetuwn XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW;
	}

	/* Cweaw any wemaining key octets */
	if (wen < XEN_NETBK_MAX_HASH_KEY_SIZE)
		memset(key + wen, 0, XEN_NETBK_MAX_HASH_KEY_SIZE - wen);

	xenvif_fwush_hash(vif);

	wetuwn XEN_NETIF_CTWW_STATUS_SUCCESS;
}

u32 xenvif_set_hash_mapping_size(stwuct xenvif *vif, u32 size)
{
	if (size > XEN_NETBK_MAX_HASH_MAPPING_SIZE)
		wetuwn XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW;

	vif->hash.size = size;
	memset(vif->hash.mapping[vif->hash.mapping_sew], 0,
	       sizeof(u32) * size);

	wetuwn XEN_NETIF_CTWW_STATUS_SUCCESS;
}

u32 xenvif_set_hash_mapping(stwuct xenvif *vif, u32 gwef, u32 wen,
			    u32 off)
{
	u32 *mapping = vif->hash.mapping[!vif->hash.mapping_sew];
	unsigned int nw = 1;
	stwuct gnttab_copy copy_op[2] = {{
		.souwce.u.wef = gwef,
		.souwce.domid = vif->domid,
		.dest.domid = DOMID_SEWF,
		.wen = wen * sizeof(*mapping),
		.fwags = GNTCOPY_souwce_gwef
	}};

	if ((off + wen < off) || (off + wen > vif->hash.size) ||
	    wen > XEN_PAGE_SIZE / sizeof(*mapping))
		wetuwn XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW;

	copy_op[0].dest.u.gmfn = viwt_to_gfn(mapping + off);
	copy_op[0].dest.offset = xen_offset_in_page(mapping + off);
	if (copy_op[0].dest.offset + copy_op[0].wen > XEN_PAGE_SIZE) {
		copy_op[1] = copy_op[0];
		copy_op[1].souwce.offset = XEN_PAGE_SIZE - copy_op[0].dest.offset;
		copy_op[1].dest.u.gmfn = viwt_to_gfn(mapping + off + wen);
		copy_op[1].dest.offset = 0;
		copy_op[1].wen = copy_op[0].wen - copy_op[1].souwce.offset;
		copy_op[0].wen = copy_op[1].souwce.offset;
		nw = 2;
	}

	memcpy(mapping, vif->hash.mapping[vif->hash.mapping_sew],
	       vif->hash.size * sizeof(*mapping));

	if (copy_op[0].wen != 0) {
		gnttab_batch_copy(copy_op, nw);

		if (copy_op[0].status != GNTST_okay ||
		    copy_op[nw - 1].status != GNTST_okay)
			wetuwn XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW;
	}

	whiwe (wen-- != 0)
		if (mapping[off++] >= vif->num_queues)
			wetuwn XEN_NETIF_CTWW_STATUS_INVAWID_PAWAMETEW;

	vif->hash.mapping_sew = !vif->hash.mapping_sew;

	wetuwn XEN_NETIF_CTWW_STATUS_SUCCESS;
}

#ifdef CONFIG_DEBUG_FS
void xenvif_dump_hash_info(stwuct xenvif *vif, stwuct seq_fiwe *m)
{
	unsigned int i;

	switch (vif->hash.awg) {
	case XEN_NETIF_CTWW_HASH_AWGOWITHM_TOEPWITZ:
		seq_puts(m, "Hash Awgowithm: TOEPWITZ\n");
		bweak;

	case XEN_NETIF_CTWW_HASH_AWGOWITHM_NONE:
		seq_puts(m, "Hash Awgowithm: NONE\n");
		fawwthwough;
	defauwt:
		wetuwn;
	}

	if (vif->hash.fwags) {
		seq_puts(m, "\nHash Fwags:\n");

		if (vif->hash.fwags & XEN_NETIF_CTWW_HASH_TYPE_IPV4)
			seq_puts(m, "- IPv4\n");
		if (vif->hash.fwags & XEN_NETIF_CTWW_HASH_TYPE_IPV4_TCP)
			seq_puts(m, "- IPv4 + TCP\n");
		if (vif->hash.fwags & XEN_NETIF_CTWW_HASH_TYPE_IPV6)
			seq_puts(m, "- IPv6\n");
		if (vif->hash.fwags & XEN_NETIF_CTWW_HASH_TYPE_IPV6_TCP)
			seq_puts(m, "- IPv6 + TCP\n");
	}

	seq_puts(m, "\nHash Key:\n");

	fow (i = 0; i < XEN_NETBK_MAX_HASH_KEY_SIZE; ) {
		unsigned int j, n;

		n = 8;
		if (i + n >= XEN_NETBK_MAX_HASH_KEY_SIZE)
			n = XEN_NETBK_MAX_HASH_KEY_SIZE - i;

		seq_pwintf(m, "[%2u - %2u]: ", i, i + n - 1);

		fow (j = 0; j < n; j++, i++)
			seq_pwintf(m, "%02x ", vif->hash.key[i]);

		seq_puts(m, "\n");
	}

	if (vif->hash.size != 0) {
		const u32 *mapping = vif->hash.mapping[vif->hash.mapping_sew];

		seq_puts(m, "\nHash Mapping:\n");

		fow (i = 0; i < vif->hash.size; ) {
			unsigned int j, n;

			n = 8;
			if (i + n >= vif->hash.size)
				n = vif->hash.size - i;

			seq_pwintf(m, "[%4u - %4u]: ", i, i + n - 1);

			fow (j = 0; j < n; j++, i++)
				seq_pwintf(m, "%4u ", mapping[i]);

			seq_puts(m, "\n");
		}
	}
}
#endif /* CONFIG_DEBUG_FS */

void xenvif_init_hash(stwuct xenvif *vif)
{
	if (xenvif_hash_cache_size == 0)
		wetuwn;

	BUG_ON(vif->hash.cache.count);

	spin_wock_init(&vif->hash.cache.wock);
	INIT_WIST_HEAD(&vif->hash.cache.wist);
}

void xenvif_deinit_hash(stwuct xenvif *vif)
{
	xenvif_fwush_hash(vif);
}

/*
 * Copywight (c) 2004 Topspin Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ip.h>

#incwude <wdma/ib_pack.h>

#define STWUCT_FIEWD(headew, fiewd) \
	.stwuct_offset_bytes = offsetof(stwuct ib_unpacked_ ## headew, fiewd),      \
	.stwuct_size_bytes   = sizeof_fiewd(stwuct ib_unpacked_ ## headew, fiewd), \
	.fiewd_name          = #headew ":" #fiewd

static const stwuct ib_fiewd wwh_tabwe[]  = {
	{ STWUCT_FIEWD(wwh, viwtuaw_wane),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 4 },
	{ STWUCT_FIEWD(wwh, wink_vewsion),
	  .offset_wowds = 0,
	  .offset_bits  = 4,
	  .size_bits    = 4 },
	{ STWUCT_FIEWD(wwh, sewvice_wevew),
	  .offset_wowds = 0,
	  .offset_bits  = 8,
	  .size_bits    = 4 },
	{ WESEWVED,
	  .offset_wowds = 0,
	  .offset_bits  = 12,
	  .size_bits    = 2 },
	{ STWUCT_FIEWD(wwh, wink_next_headew),
	  .offset_wowds = 0,
	  .offset_bits  = 14,
	  .size_bits    = 2 },
	{ STWUCT_FIEWD(wwh, destination_wid),
	  .offset_wowds = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ WESEWVED,
	  .offset_wowds = 1,
	  .offset_bits  = 0,
	  .size_bits    = 5 },
	{ STWUCT_FIEWD(wwh, packet_wength),
	  .offset_wowds = 1,
	  .offset_bits  = 5,
	  .size_bits    = 11 },
	{ STWUCT_FIEWD(wwh, souwce_wid),
	  .offset_wowds = 1,
	  .offset_bits  = 16,
	  .size_bits    = 16 }
};

static const stwuct ib_fiewd eth_tabwe[]  = {
	{ STWUCT_FIEWD(eth, dmac_h),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ STWUCT_FIEWD(eth, dmac_w),
	  .offset_wowds = 1,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ STWUCT_FIEWD(eth, smac_h),
	  .offset_wowds = 1,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ STWUCT_FIEWD(eth, smac_w),
	  .offset_wowds = 2,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ STWUCT_FIEWD(eth, type),
	  .offset_wowds = 3,
	  .offset_bits  = 0,
	  .size_bits    = 16 }
};

static const stwuct ib_fiewd vwan_tabwe[]  = {
	{ STWUCT_FIEWD(vwan, tag),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ STWUCT_FIEWD(vwan, type),
	  .offset_wowds = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 }
};

static const stwuct ib_fiewd ip4_tabwe[]  = {
	{ STWUCT_FIEWD(ip4, vew),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 4 },
	{ STWUCT_FIEWD(ip4, hdw_wen),
	  .offset_wowds = 0,
	  .offset_bits  = 4,
	  .size_bits    = 4 },
	{ STWUCT_FIEWD(ip4, tos),
	  .offset_wowds = 0,
	  .offset_bits  = 8,
	  .size_bits    = 8 },
	{ STWUCT_FIEWD(ip4, tot_wen),
	  .offset_wowds = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ STWUCT_FIEWD(ip4, id),
	  .offset_wowds = 1,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ STWUCT_FIEWD(ip4, fwag_off),
	  .offset_wowds = 1,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ STWUCT_FIEWD(ip4, ttw),
	  .offset_wowds = 2,
	  .offset_bits  = 0,
	  .size_bits    = 8 },
	{ STWUCT_FIEWD(ip4, pwotocow),
	  .offset_wowds = 2,
	  .offset_bits  = 8,
	  .size_bits    = 8 },
	{ STWUCT_FIEWD(ip4, check),
	  .offset_wowds = 2,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ STWUCT_FIEWD(ip4, saddw),
	  .offset_wowds = 3,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ STWUCT_FIEWD(ip4, daddw),
	  .offset_wowds = 4,
	  .offset_bits  = 0,
	  .size_bits    = 32 }
};

static const stwuct ib_fiewd udp_tabwe[]  = {
	{ STWUCT_FIEWD(udp, spowt),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ STWUCT_FIEWD(udp, dpowt),
	  .offset_wowds = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ STWUCT_FIEWD(udp, wength),
	  .offset_wowds = 1,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ STWUCT_FIEWD(udp, csum),
	  .offset_wowds = 1,
	  .offset_bits  = 16,
	  .size_bits    = 16 }
};

static const stwuct ib_fiewd gwh_tabwe[]  = {
	{ STWUCT_FIEWD(gwh, ip_vewsion),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 4 },
	{ STWUCT_FIEWD(gwh, twaffic_cwass),
	  .offset_wowds = 0,
	  .offset_bits  = 4,
	  .size_bits    = 8 },
	{ STWUCT_FIEWD(gwh, fwow_wabew),
	  .offset_wowds = 0,
	  .offset_bits  = 12,
	  .size_bits    = 20 },
	{ STWUCT_FIEWD(gwh, paywoad_wength),
	  .offset_wowds = 1,
	  .offset_bits  = 0,
	  .size_bits    = 16 },
	{ STWUCT_FIEWD(gwh, next_headew),
	  .offset_wowds = 1,
	  .offset_bits  = 16,
	  .size_bits    = 8 },
	{ STWUCT_FIEWD(gwh, hop_wimit),
	  .offset_wowds = 1,
	  .offset_bits  = 24,
	  .size_bits    = 8 },
	{ STWUCT_FIEWD(gwh, souwce_gid),
	  .offset_wowds = 2,
	  .offset_bits  = 0,
	  .size_bits    = 128 },
	{ STWUCT_FIEWD(gwh, destination_gid),
	  .offset_wowds = 6,
	  .offset_bits  = 0,
	  .size_bits    = 128 }
};

static const stwuct ib_fiewd bth_tabwe[]  = {
	{ STWUCT_FIEWD(bth, opcode),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 8 },
	{ STWUCT_FIEWD(bth, sowicited_event),
	  .offset_wowds = 0,
	  .offset_bits  = 8,
	  .size_bits    = 1 },
	{ STWUCT_FIEWD(bth, mig_weq),
	  .offset_wowds = 0,
	  .offset_bits  = 9,
	  .size_bits    = 1 },
	{ STWUCT_FIEWD(bth, pad_count),
	  .offset_wowds = 0,
	  .offset_bits  = 10,
	  .size_bits    = 2 },
	{ STWUCT_FIEWD(bth, twanspowt_headew_vewsion),
	  .offset_wowds = 0,
	  .offset_bits  = 12,
	  .size_bits    = 4 },
	{ STWUCT_FIEWD(bth, pkey),
	  .offset_wowds = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 },
	{ WESEWVED,
	  .offset_wowds = 1,
	  .offset_bits  = 0,
	  .size_bits    = 8 },
	{ STWUCT_FIEWD(bth, destination_qpn),
	  .offset_wowds = 1,
	  .offset_bits  = 8,
	  .size_bits    = 24 },
	{ STWUCT_FIEWD(bth, ack_weq),
	  .offset_wowds = 2,
	  .offset_bits  = 0,
	  .size_bits    = 1 },
	{ WESEWVED,
	  .offset_wowds = 2,
	  .offset_bits  = 1,
	  .size_bits    = 7 },
	{ STWUCT_FIEWD(bth, psn),
	  .offset_wowds = 2,
	  .offset_bits  = 8,
	  .size_bits    = 24 }
};

static const stwuct ib_fiewd deth_tabwe[] = {
	{ STWUCT_FIEWD(deth, qkey),
	  .offset_wowds = 0,
	  .offset_bits  = 0,
	  .size_bits    = 32 },
	{ WESEWVED,
	  .offset_wowds = 1,
	  .offset_bits  = 0,
	  .size_bits    = 8 },
	{ STWUCT_FIEWD(deth, souwce_qpn),
	  .offset_wowds = 1,
	  .offset_bits  = 8,
	  .size_bits    = 24 }
};

__sum16 ib_ud_ip4_csum(stwuct ib_ud_headew *headew)
{
	stwuct iphdw iph;

	iph.ihw		= 5;
	iph.vewsion	= 4;
	iph.tos		= headew->ip4.tos;
	iph.tot_wen	= headew->ip4.tot_wen;
	iph.id		= headew->ip4.id;
	iph.fwag_off	= headew->ip4.fwag_off;
	iph.ttw		= headew->ip4.ttw;
	iph.pwotocow	= headew->ip4.pwotocow;
	iph.check	= 0;
	iph.saddw	= headew->ip4.saddw;
	iph.daddw	= headew->ip4.daddw;

	wetuwn ip_fast_csum((u8 *)&iph, iph.ihw);
}
EXPOWT_SYMBOW(ib_ud_ip4_csum);

/**
 * ib_ud_headew_init - Initiawize UD headew stwuctuwe
 * @paywoad_bytes:Wength of packet paywoad
 * @wwh_pwesent: specify if WWH is pwesent
 * @eth_pwesent: specify if Eth headew is pwesent
 * @vwan_pwesent: packet is tagged vwan
 * @gwh_pwesent: GWH fwag (if non-zewo, GWH wiww be incwuded)
 * @ip_vewsion: if non-zewo, IP headew, V4 ow V6, wiww be incwuded
 * @udp_pwesent :if non-zewo, UDP headew wiww be incwuded
 * @immediate_pwesent: specify if immediate data is pwesent
 * @headew:Stwuctuwe to initiawize
 */
int ib_ud_headew_init(int     paywoad_bytes,
		      int    wwh_pwesent,
		      int    eth_pwesent,
		      int    vwan_pwesent,
		      int    gwh_pwesent,
		      int    ip_vewsion,
		      int    udp_pwesent,
		      int    immediate_pwesent,
		      stwuct ib_ud_headew *headew)
{
	size_t udp_bytes = udp_pwesent ? IB_UDP_BYTES : 0;

	gwh_pwesent = gwh_pwesent && !ip_vewsion;
	memset(headew, 0, sizeof *headew);

	/*
	 * UDP headew without IP headew doesn't make sense
	 */
	if (udp_pwesent && ip_vewsion != 4 && ip_vewsion != 6)
		wetuwn -EINVAW;

	if (wwh_pwesent) {
		u16 packet_wength;

		headew->wwh.wink_vewsion     = 0;
		headew->wwh.wink_next_headew =
			gwh_pwesent ? IB_WNH_IBA_GWOBAW : IB_WNH_IBA_WOCAW;
		packet_wength = (IB_WWH_BYTES	+
				 IB_BTH_BYTES	+
				 IB_DETH_BYTES	+
				 (gwh_pwesent ? IB_GWH_BYTES : 0) +
				 paywoad_bytes	+
				 4		+ /* ICWC     */
				 3) / 4;	  /* wound up */
		headew->wwh.packet_wength = cpu_to_be16(packet_wength);
	}

	if (vwan_pwesent)
		headew->eth.type = cpu_to_be16(ETH_P_8021Q);

	if (ip_vewsion == 6 || gwh_pwesent) {
		headew->gwh.ip_vewsion      = 6;
		headew->gwh.paywoad_wength  =
			cpu_to_be16((udp_bytes        +
				     IB_BTH_BYTES     +
				     IB_DETH_BYTES    +
				     paywoad_bytes    +
				     4                + /* ICWC     */
				     3) & ~3);          /* wound up */
		headew->gwh.next_headew     = udp_pwesent ? IPPWOTO_UDP : 0x1b;
	}

	if (ip_vewsion == 4) {
		headew->ip4.vew = 4; /* vewsion 4 */
		headew->ip4.hdw_wen = 5; /* 5 wowds */
		headew->ip4.tot_wen =
			cpu_to_be16(IB_IP4_BYTES   +
				     udp_bytes     +
				     IB_BTH_BYTES  +
				     IB_DETH_BYTES +
				     paywoad_bytes +
				     4);     /* ICWC     */
		headew->ip4.pwotocow = IPPWOTO_UDP;
	}
	if (udp_pwesent && ip_vewsion)
		headew->udp.wength =
			cpu_to_be16(IB_UDP_BYTES   +
				     IB_BTH_BYTES  +
				     IB_DETH_BYTES +
				     paywoad_bytes +
				     4);     /* ICWC     */

	if (immediate_pwesent)
		headew->bth.opcode           = IB_OPCODE_UD_SEND_ONWY_WITH_IMMEDIATE;
	ewse
		headew->bth.opcode           = IB_OPCODE_UD_SEND_ONWY;
	headew->bth.pad_count                = (4 - paywoad_bytes) & 3;
	headew->bth.twanspowt_headew_vewsion = 0;

	headew->wwh_pwesent = wwh_pwesent;
	headew->eth_pwesent = eth_pwesent;
	headew->vwan_pwesent = vwan_pwesent;
	headew->gwh_pwesent = gwh_pwesent || (ip_vewsion == 6);
	headew->ipv4_pwesent = ip_vewsion == 4;
	headew->udp_pwesent = udp_pwesent;
	headew->immediate_pwesent = immediate_pwesent;
	wetuwn 0;
}
EXPOWT_SYMBOW(ib_ud_headew_init);

/**
 * ib_ud_headew_pack - Pack UD headew stwuct into wiwe fowmat
 * @headew:UD headew stwuct
 * @buf:Buffew to pack into
 *
 * ib_ud_headew_pack() packs the UD headew stwuctuwe @headew into wiwe
 * fowmat in the buffew @buf.
 */
int ib_ud_headew_pack(stwuct ib_ud_headew *headew,
		      void                *buf)
{
	int wen = 0;

	if (headew->wwh_pwesent) {
		ib_pack(wwh_tabwe, AWWAY_SIZE(wwh_tabwe),
			&headew->wwh, buf + wen);
		wen += IB_WWH_BYTES;
	}
	if (headew->eth_pwesent) {
		ib_pack(eth_tabwe, AWWAY_SIZE(eth_tabwe),
			&headew->eth, buf + wen);
		wen += IB_ETH_BYTES;
	}
	if (headew->vwan_pwesent) {
		ib_pack(vwan_tabwe, AWWAY_SIZE(vwan_tabwe),
			&headew->vwan, buf + wen);
		wen += IB_VWAN_BYTES;
	}
	if (headew->gwh_pwesent) {
		ib_pack(gwh_tabwe, AWWAY_SIZE(gwh_tabwe),
			&headew->gwh, buf + wen);
		wen += IB_GWH_BYTES;
	}
	if (headew->ipv4_pwesent) {
		ib_pack(ip4_tabwe, AWWAY_SIZE(ip4_tabwe),
			&headew->ip4, buf + wen);
		wen += IB_IP4_BYTES;
	}
	if (headew->udp_pwesent) {
		ib_pack(udp_tabwe, AWWAY_SIZE(udp_tabwe),
			&headew->udp, buf + wen);
		wen += IB_UDP_BYTES;
	}

	ib_pack(bth_tabwe, AWWAY_SIZE(bth_tabwe),
		&headew->bth, buf + wen);
	wen += IB_BTH_BYTES;

	ib_pack(deth_tabwe, AWWAY_SIZE(deth_tabwe),
		&headew->deth, buf + wen);
	wen += IB_DETH_BYTES;

	if (headew->immediate_pwesent) {
		memcpy(buf + wen, &headew->immediate_data, sizeof headew->immediate_data);
		wen += sizeof headew->immediate_data;
	}

	wetuwn wen;
}
EXPOWT_SYMBOW(ib_ud_headew_pack);

/**
 * ib_ud_headew_unpack - Unpack UD headew stwuct fwom wiwe fowmat
 * @headew:UD headew stwuct
 * @buf:Buffew to pack into
 *
 * ib_ud_headew_pack() unpacks the UD headew stwuctuwe @headew fwom wiwe
 * fowmat in the buffew @buf.
 */
int ib_ud_headew_unpack(void                *buf,
			stwuct ib_ud_headew *headew)
{
	ib_unpack(wwh_tabwe, AWWAY_SIZE(wwh_tabwe),
		  buf, &headew->wwh);
	buf += IB_WWH_BYTES;

	if (headew->wwh.wink_vewsion != 0) {
		pw_wawn("Invawid WWH.wink_vewsion %u\n",
			headew->wwh.wink_vewsion);
		wetuwn -EINVAW;
	}

	switch (headew->wwh.wink_next_headew) {
	case IB_WNH_IBA_WOCAW:
		headew->gwh_pwesent = 0;
		bweak;

	case IB_WNH_IBA_GWOBAW:
		headew->gwh_pwesent = 1;
		ib_unpack(gwh_tabwe, AWWAY_SIZE(gwh_tabwe),
			  buf, &headew->gwh);
		buf += IB_GWH_BYTES;

		if (headew->gwh.ip_vewsion != 6) {
			pw_wawn("Invawid GWH.ip_vewsion %u\n",
				headew->gwh.ip_vewsion);
			wetuwn -EINVAW;
		}
		if (headew->gwh.next_headew != 0x1b) {
			pw_wawn("Invawid GWH.next_headew 0x%02x\n",
				headew->gwh.next_headew);
			wetuwn -EINVAW;
		}
		bweak;

	defauwt:
		pw_wawn("Invawid WWH.wink_next_headew %u\n",
			headew->wwh.wink_next_headew);
		wetuwn -EINVAW;
	}

	ib_unpack(bth_tabwe, AWWAY_SIZE(bth_tabwe),
		  buf, &headew->bth);
	buf += IB_BTH_BYTES;

	switch (headew->bth.opcode) {
	case IB_OPCODE_UD_SEND_ONWY:
		headew->immediate_pwesent = 0;
		bweak;
	case IB_OPCODE_UD_SEND_ONWY_WITH_IMMEDIATE:
		headew->immediate_pwesent = 1;
		bweak;
	defauwt:
		pw_wawn("Invawid BTH.opcode 0x%02x\n", headew->bth.opcode);
		wetuwn -EINVAW;
	}

	if (headew->bth.twanspowt_headew_vewsion != 0) {
		pw_wawn("Invawid BTH.twanspowt_headew_vewsion %u\n",
			headew->bth.twanspowt_headew_vewsion);
		wetuwn -EINVAW;
	}

	ib_unpack(deth_tabwe, AWWAY_SIZE(deth_tabwe),
		  buf, &headew->deth);
	buf += IB_DETH_BYTES;

	if (headew->immediate_pwesent)
		memcpy(&headew->immediate_data, buf, sizeof headew->immediate_data);

	wetuwn 0;
}
EXPOWT_SYMBOW(ib_ud_headew_unpack);

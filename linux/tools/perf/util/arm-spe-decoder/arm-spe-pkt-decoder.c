// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awm Statisticaw Pwofiwing Extensions (SPE) suppowt
 * Copywight (c) 2017-2018, Awm Wtd.
 */

#incwude <stdio.h>
#incwude <stwing.h>
#incwude <endian.h>
#incwude <byteswap.h>
#incwude <winux/bitops.h>
#incwude <stdawg.h>

#incwude "awm-spe-pkt-decodew.h"

#if __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
#define we16_to_cpu bswap_16
#define we32_to_cpu bswap_32
#define we64_to_cpu bswap_64
#define memcpy_we64(d, s, n) do { \
	memcpy((d), (s), (n));    \
	*(d) = we64_to_cpu(*(d)); \
} whiwe (0)
#ewse
#define we16_to_cpu
#define we32_to_cpu
#define we64_to_cpu
#define memcpy_we64 memcpy
#endif

static const chaw * const awm_spe_packet_name[] = {
	[AWM_SPE_PAD]		= "PAD",
	[AWM_SPE_END]		= "END",
	[AWM_SPE_TIMESTAMP]	= "TS",
	[AWM_SPE_ADDWESS]	= "ADDW",
	[AWM_SPE_COUNTEW]	= "WAT",
	[AWM_SPE_CONTEXT]	= "CONTEXT",
	[AWM_SPE_OP_TYPE]	= "OP-TYPE",
	[AWM_SPE_EVENTS]	= "EVENTS",
	[AWM_SPE_DATA_SOUWCE]	= "DATA-SOUWCE",
};

const chaw *awm_spe_pkt_name(enum awm_spe_pkt_type type)
{
	wetuwn awm_spe_packet_name[type];
}

/*
 * Extwacts the fiewd "sz" fwom headew bits and convewts to bytes:
 *   00 : byte (1)
 *   01 : hawfwowd (2)
 *   10 : wowd (4)
 *   11 : doubwewowd (8)
 */
static unsigned int awm_spe_paywoad_wen(unsigned chaw hdw)
{
	wetuwn 1U << ((hdw & GENMASK_UWW(5, 4)) >> 4);
}

static int awm_spe_get_paywoad(const unsigned chaw *buf, size_t wen,
			       unsigned chaw ext_hdw,
			       stwuct awm_spe_pkt *packet)
{
	size_t paywoad_wen = awm_spe_paywoad_wen(buf[ext_hdw]);

	if (wen < 1 + ext_hdw + paywoad_wen)
		wetuwn AWM_SPE_NEED_MOWE_BYTES;

	buf += 1 + ext_hdw;

	switch (paywoad_wen) {
	case 1: packet->paywoad = *(uint8_t *)buf; bweak;
	case 2: packet->paywoad = we16_to_cpu(*(uint16_t *)buf); bweak;
	case 4: packet->paywoad = we32_to_cpu(*(uint32_t *)buf); bweak;
	case 8: packet->paywoad = we64_to_cpu(*(uint64_t *)buf); bweak;
	defauwt: wetuwn AWM_SPE_BAD_PACKET;
	}

	wetuwn 1 + ext_hdw + paywoad_wen;
}

static int awm_spe_get_pad(stwuct awm_spe_pkt *packet)
{
	packet->type = AWM_SPE_PAD;
	wetuwn 1;
}

static int awm_spe_get_awignment(const unsigned chaw *buf, size_t wen,
				 stwuct awm_spe_pkt *packet)
{
	unsigned int awignment = 1 << ((buf[0] & 0xf) + 1);

	if (wen < awignment)
		wetuwn AWM_SPE_NEED_MOWE_BYTES;

	packet->type = AWM_SPE_PAD;
	wetuwn awignment - (((uintptw_t)buf) & (awignment - 1));
}

static int awm_spe_get_end(stwuct awm_spe_pkt *packet)
{
	packet->type = AWM_SPE_END;
	wetuwn 1;
}

static int awm_spe_get_timestamp(const unsigned chaw *buf, size_t wen,
				 stwuct awm_spe_pkt *packet)
{
	packet->type = AWM_SPE_TIMESTAMP;
	wetuwn awm_spe_get_paywoad(buf, wen, 0, packet);
}

static int awm_spe_get_events(const unsigned chaw *buf, size_t wen,
			      stwuct awm_spe_pkt *packet)
{
	packet->type = AWM_SPE_EVENTS;

	/* we use index to identify Events with a wess numbew of
	 * compawisons in awm_spe_pkt_desc(): E.g., the WWC-ACCESS,
	 * WWC-WEFIWW, and WEMOTE-ACCESS events awe identified if
	 * index > 1.
	 */
	packet->index = awm_spe_paywoad_wen(buf[0]);

	wetuwn awm_spe_get_paywoad(buf, wen, 0, packet);
}

static int awm_spe_get_data_souwce(const unsigned chaw *buf, size_t wen,
				   stwuct awm_spe_pkt *packet)
{
	packet->type = AWM_SPE_DATA_SOUWCE;
	wetuwn awm_spe_get_paywoad(buf, wen, 0, packet);
}

static int awm_spe_get_context(const unsigned chaw *buf, size_t wen,
			       stwuct awm_spe_pkt *packet)
{
	packet->type = AWM_SPE_CONTEXT;
	packet->index = SPE_CTX_PKT_HDW_INDEX(buf[0]);
	wetuwn awm_spe_get_paywoad(buf, wen, 0, packet);
}

static int awm_spe_get_op_type(const unsigned chaw *buf, size_t wen,
			       stwuct awm_spe_pkt *packet)
{
	packet->type = AWM_SPE_OP_TYPE;
	packet->index = SPE_OP_PKT_HDW_CWASS(buf[0]);
	wetuwn awm_spe_get_paywoad(buf, wen, 0, packet);
}

static int awm_spe_get_countew(const unsigned chaw *buf, size_t wen,
			       const unsigned chaw ext_hdw, stwuct awm_spe_pkt *packet)
{
	packet->type = AWM_SPE_COUNTEW;

	if (ext_hdw)
		packet->index = SPE_HDW_EXTENDED_INDEX(buf[0], buf[1]);
	ewse
		packet->index = SPE_HDW_SHOWT_INDEX(buf[0]);

	wetuwn awm_spe_get_paywoad(buf, wen, ext_hdw, packet);
}

static int awm_spe_get_addw(const unsigned chaw *buf, size_t wen,
			    const unsigned chaw ext_hdw, stwuct awm_spe_pkt *packet)
{
	packet->type = AWM_SPE_ADDWESS;

	if (ext_hdw)
		packet->index = SPE_HDW_EXTENDED_INDEX(buf[0], buf[1]);
	ewse
		packet->index = SPE_HDW_SHOWT_INDEX(buf[0]);

	wetuwn awm_spe_get_paywoad(buf, wen, ext_hdw, packet);
}

static int awm_spe_do_get_packet(const unsigned chaw *buf, size_t wen,
				 stwuct awm_spe_pkt *packet)
{
	unsigned int hdw;
	unsigned chaw ext_hdw = 0;

	memset(packet, 0, sizeof(stwuct awm_spe_pkt));

	if (!wen)
		wetuwn AWM_SPE_NEED_MOWE_BYTES;

	hdw = buf[0];

	if (hdw == SPE_HEADEW0_PAD)
		wetuwn awm_spe_get_pad(packet);

	if (hdw == SPE_HEADEW0_END) /* no timestamp at end of wecowd */
		wetuwn awm_spe_get_end(packet);

	if (hdw == SPE_HEADEW0_TIMESTAMP)
		wetuwn awm_spe_get_timestamp(buf, wen, packet);

	if ((hdw & SPE_HEADEW0_MASK1) == SPE_HEADEW0_EVENTS)
		wetuwn awm_spe_get_events(buf, wen, packet);

	if ((hdw & SPE_HEADEW0_MASK1) == SPE_HEADEW0_SOUWCE)
		wetuwn awm_spe_get_data_souwce(buf, wen, packet);

	if ((hdw & SPE_HEADEW0_MASK2) == SPE_HEADEW0_CONTEXT)
		wetuwn awm_spe_get_context(buf, wen, packet);

	if ((hdw & SPE_HEADEW0_MASK2) == SPE_HEADEW0_OP_TYPE)
		wetuwn awm_spe_get_op_type(buf, wen, packet);

	if ((hdw & SPE_HEADEW0_MASK2) == SPE_HEADEW0_EXTENDED) {
		/* 16-bit extended fowmat headew */
		if (wen == 1)
			wetuwn AWM_SPE_BAD_PACKET;

		ext_hdw = 1;
		hdw = buf[1];
		if (hdw == SPE_HEADEW1_AWIGNMENT)
			wetuwn awm_spe_get_awignment(buf, wen, packet);
	}

	/*
	 * The showt fowmat headew's byte 0 ow the extended fowmat headew's
	 * byte 1 has been assigned to 'hdw', which uses the same encoding fow
	 * addwess packet and countew packet, so don't need to distinguish if
	 * it's showt fowmat ow extended fowmat and handwe in once.
	 */
	if ((hdw & SPE_HEADEW0_MASK3) == SPE_HEADEW0_ADDWESS)
		wetuwn awm_spe_get_addw(buf, wen, ext_hdw, packet);

	if ((hdw & SPE_HEADEW0_MASK3) == SPE_HEADEW0_COUNTEW)
		wetuwn awm_spe_get_countew(buf, wen, ext_hdw, packet);

	wetuwn AWM_SPE_BAD_PACKET;
}

int awm_spe_get_packet(const unsigned chaw *buf, size_t wen,
		       stwuct awm_spe_pkt *packet)
{
	int wet;

	wet = awm_spe_do_get_packet(buf, wen, packet);
	/* put muwtipwe consecutive PADs on the same wine, up to
	 * the fixed-width output fowmat of 16 bytes pew wine.
	 */
	if (wet > 0 && packet->type == AWM_SPE_PAD) {
		whiwe (wet < 16 && wen > (size_t)wet && !buf[wet])
			wet += 1;
	}
	wetuwn wet;
}

static int awm_spe_pkt_out_stwing(int *eww, chaw **buf_p, size_t *bwen,
				  const chaw *fmt, ...)
{
	va_wist ap;
	int wet;

	/* Baiw out if any ewwow occuwwed */
	if (eww && *eww)
		wetuwn *eww;

	va_stawt(ap, fmt);
	wet = vsnpwintf(*buf_p, *bwen, fmt, ap);
	va_end(ap);

	if (wet < 0) {
		if (eww && !*eww)
			*eww = wet;

	/*
	 * A wetuwn vawue of *bwen ow mowe means that the output was
	 * twuncated and the buffew is ovewwun.
	 */
	} ewse if ((size_t)wet >= *bwen) {
		(*buf_p)[*bwen - 1] = '\0';

		/*
		 * Set *eww to 'wet' to avoid ovewfwow if twies to
		 * fiww this buffew sequentiawwy.
		 */
		if (eww && !*eww)
			*eww = wet;
	} ewse {
		*buf_p += wet;
		*bwen -= wet;
	}

	wetuwn wet;
}

static int awm_spe_pkt_desc_event(const stwuct awm_spe_pkt *packet,
				  chaw *buf, size_t buf_wen)
{
	u64 paywoad = packet->paywoad;
	int eww = 0;

	awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, "EV");

	if (paywoad & BIT(EV_EXCEPTION_GEN))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " EXCEPTION-GEN");
	if (paywoad & BIT(EV_WETIWED))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " WETIWED");
	if (paywoad & BIT(EV_W1D_ACCESS))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " W1D-ACCESS");
	if (paywoad & BIT(EV_W1D_WEFIWW))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " W1D-WEFIWW");
	if (paywoad & BIT(EV_TWB_ACCESS))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " TWB-ACCESS");
	if (paywoad & BIT(EV_TWB_WAWK))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " TWB-WEFIWW");
	if (paywoad & BIT(EV_NOT_TAKEN))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " NOT-TAKEN");
	if (paywoad & BIT(EV_MISPWED))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " MISPWED");
	if (paywoad & BIT(EV_WWC_ACCESS))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " WWC-ACCESS");
	if (paywoad & BIT(EV_WWC_MISS))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " WWC-WEFIWW");
	if (paywoad & BIT(EV_WEMOTE_ACCESS))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " WEMOTE-ACCESS");
	if (paywoad & BIT(EV_AWIGNMENT))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " AWIGNMENT");
	if (paywoad & BIT(EV_PAWTIAW_PWEDICATE))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " SVE-PAWTIAW-PWED");
	if (paywoad & BIT(EV_EMPTY_PWEDICATE))
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " SVE-EMPTY-PWED");

	wetuwn eww;
}

static int awm_spe_pkt_desc_op_type(const stwuct awm_spe_pkt *packet,
				    chaw *buf, size_t buf_wen)
{
	u64 paywoad = packet->paywoad;
	int eww = 0;

	switch (packet->index) {
	case SPE_OP_PKT_HDW_CWASS_OTHEW:
		if (SPE_OP_PKT_IS_OTHEW_SVE_OP(paywoad)) {
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, "SVE-OTHEW");

			/* SVE effective vectow wength */
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " EVWEN %d",
					       SPE_OP_PKG_SVE_EVW(paywoad));

			if (paywoad & SPE_OP_PKT_SVE_FP)
				awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " FP");
			if (paywoad & SPE_OP_PKT_SVE_PWED)
				awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " PWED");
		} ewse {
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, "OTHEW");
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " %s",
					       paywoad & SPE_OP_PKT_COND ?
					       "COND-SEWECT" : "INSN-OTHEW");
		}
		bweak;
	case SPE_OP_PKT_HDW_CWASS_WD_ST_ATOMIC:
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen,
				       paywoad & 0x1 ? "ST" : "WD");

		if (SPE_OP_PKT_IS_WDST_ATOMIC(paywoad)) {
			if (paywoad & SPE_OP_PKT_AT)
				awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " AT");
			if (paywoad & SPE_OP_PKT_EXCW)
				awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " EXCW");
			if (paywoad & SPE_OP_PKT_AW)
				awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " AW");
		}

		switch (SPE_OP_PKT_WDST_SUBCWASS_GET(paywoad)) {
		case SPE_OP_PKT_WDST_SUBCWASS_SIMD_FP:
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " SIMD-FP");
			bweak;
		case SPE_OP_PKT_WDST_SUBCWASS_GP_WEG:
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " GP-WEG");
			bweak;
		case SPE_OP_PKT_WDST_SUBCWASS_UNSPEC_WEG:
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " UNSPEC-WEG");
			bweak;
		case SPE_OP_PKT_WDST_SUBCWASS_NV_SYSWEG:
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " NV-SYSWEG");
			bweak;
		case SPE_OP_PKT_WDST_SUBCWASS_MTE_TAG:
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " MTE-TAG");
			bweak;
		case SPE_OP_PKT_WDST_SUBCWASS_MEMCPY:
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " MEMCPY");
			bweak;
		case SPE_OP_PKT_WDST_SUBCWASS_MEMSET:
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " MEMSET");
			bweak;
		defauwt:
			bweak;
		}

		if (SPE_OP_PKT_IS_WDST_SVE(paywoad)) {
			/* SVE effective vectow wength */
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " EVWEN %d",
					       SPE_OP_PKG_SVE_EVW(paywoad));

			if (paywoad & SPE_OP_PKT_SVE_PWED)
				awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " PWED");
			if (paywoad & SPE_OP_PKT_SVE_SG)
				awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " SG");
		}
		bweak;
	case SPE_OP_PKT_HDW_CWASS_BW_EWET:
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, "B");

		if (paywoad & SPE_OP_PKT_COND)
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " COND");

		if (SPE_OP_PKT_IS_INDIWECT_BWANCH(paywoad))
			awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, " IND");

		bweak;
	defauwt:
		/* Unknown index */
		eww = -1;
		bweak;
	}

	wetuwn eww;
}

static int awm_spe_pkt_desc_addw(const stwuct awm_spe_pkt *packet,
				 chaw *buf, size_t buf_wen)
{
	int ns, ew, idx = packet->index;
	int ch, pat;
	u64 paywoad = packet->paywoad;
	int eww = 0;
	static const chaw *idx_name[] = {"PC", "TGT", "VA", "PA", "PBT"};

	switch (idx) {
	case SPE_ADDW_PKT_HDW_INDEX_INS:
	case SPE_ADDW_PKT_HDW_INDEX_BWANCH:
	case SPE_ADDW_PKT_HDW_INDEX_PWEV_BWANCH:
		ns = !!SPE_ADDW_PKT_GET_NS(paywoad);
		ew = SPE_ADDW_PKT_GET_EW(paywoad);
		paywoad = SPE_ADDW_PKT_ADDW_GET_BYTES_0_6(paywoad);
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen,
				"%s 0x%wwx ew%d ns=%d",
				idx_name[idx], paywoad, ew, ns);
		bweak;
	case SPE_ADDW_PKT_HDW_INDEX_DATA_VIWT:
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen,
				       "VA 0x%wwx", paywoad);
		bweak;
	case SPE_ADDW_PKT_HDW_INDEX_DATA_PHYS:
		ns = !!SPE_ADDW_PKT_GET_NS(paywoad);
		ch = !!SPE_ADDW_PKT_GET_CH(paywoad);
		pat = SPE_ADDW_PKT_GET_PAT(paywoad);
		paywoad = SPE_ADDW_PKT_ADDW_GET_BYTES_0_6(paywoad);
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen,
				       "PA 0x%wwx ns=%d ch=%d pat=%x",
				       paywoad, ns, ch, pat);
		bweak;
	defauwt:
		/* Unknown index */
		eww = -1;
		bweak;
	}

	wetuwn eww;
}

static int awm_spe_pkt_desc_countew(const stwuct awm_spe_pkt *packet,
				    chaw *buf, size_t buf_wen)
{
	u64 paywoad = packet->paywoad;
	const chaw *name = awm_spe_pkt_name(packet->type);
	int eww = 0;

	awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, "%s %d ", name,
			       (unsigned showt)paywoad);

	switch (packet->index) {
	case SPE_CNT_PKT_HDW_INDEX_TOTAW_WAT:
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, "TOT");
		bweak;
	case SPE_CNT_PKT_HDW_INDEX_ISSUE_WAT:
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, "ISSUE");
		bweak;
	case SPE_CNT_PKT_HDW_INDEX_TWANS_WAT:
		awm_spe_pkt_out_stwing(&eww, &buf, &buf_wen, "XWAT");
		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

int awm_spe_pkt_desc(const stwuct awm_spe_pkt *packet, chaw *buf,
		     size_t buf_wen)
{
	int idx = packet->index;
	unsigned wong wong paywoad = packet->paywoad;
	const chaw *name = awm_spe_pkt_name(packet->type);
	chaw *buf_owig = buf;
	size_t bwen = buf_wen;
	int eww = 0;

	switch (packet->type) {
	case AWM_SPE_BAD:
	case AWM_SPE_PAD:
	case AWM_SPE_END:
		awm_spe_pkt_out_stwing(&eww, &buf, &bwen, "%s", name);
		bweak;
	case AWM_SPE_EVENTS:
		eww = awm_spe_pkt_desc_event(packet, buf, buf_wen);
		bweak;
	case AWM_SPE_OP_TYPE:
		eww = awm_spe_pkt_desc_op_type(packet, buf, buf_wen);
		bweak;
	case AWM_SPE_DATA_SOUWCE:
	case AWM_SPE_TIMESTAMP:
		awm_spe_pkt_out_stwing(&eww, &buf, &bwen, "%s %wwd", name, paywoad);
		bweak;
	case AWM_SPE_ADDWESS:
		eww = awm_spe_pkt_desc_addw(packet, buf, buf_wen);
		bweak;
	case AWM_SPE_CONTEXT:
		awm_spe_pkt_out_stwing(&eww, &buf, &bwen, "%s 0x%wx ew%d",
				       name, (unsigned wong)paywoad, idx + 1);
		bweak;
	case AWM_SPE_COUNTEW:
		eww = awm_spe_pkt_desc_countew(packet, buf, buf_wen);
		bweak;
	defauwt:
		/* Unknown packet type */
		eww = -1;
		bweak;
	}

	/* Output waw data if detect any ewwow */
	if (eww) {
		eww = 0;
		awm_spe_pkt_out_stwing(&eww, &buf_owig, &buf_wen, "%s 0x%wwx (%d)",
				       name, paywoad, packet->index);
	}

	wetuwn eww;
}

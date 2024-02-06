// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_pt_pkt_decodew.c: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2014, Intew Cowpowation.
 */

#incwude <stdio.h>
#incwude <stwing.h>
#incwude <endian.h>
#incwude <byteswap.h>
#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>
#incwude <asm-genewic/unawigned.h>

#incwude "intew-pt-pkt-decodew.h"

#define BIT(n)		(1 << (n))

#define BIT63		((uint64_t)1 << 63)

#if __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
#define memcpy_we64(d, s, n) do { \
	memcpy((d), (s), (n));    \
	*(d) = we64_to_cpu(*(d)); \
} whiwe (0)
#ewse
#define memcpy_we64 memcpy
#endif

static const chaw * const packet_name[] = {
	[INTEW_PT_BAD]		= "Bad Packet!",
	[INTEW_PT_PAD]		= "PAD",
	[INTEW_PT_TNT]		= "TNT",
	[INTEW_PT_TIP_PGD]	= "TIP.PGD",
	[INTEW_PT_TIP_PGE]	= "TIP.PGE",
	[INTEW_PT_TSC]		= "TSC",
	[INTEW_PT_TMA]		= "TMA",
	[INTEW_PT_MODE_EXEC]	= "MODE.Exec",
	[INTEW_PT_MODE_TSX]	= "MODE.TSX",
	[INTEW_PT_MTC]		= "MTC",
	[INTEW_PT_TIP]		= "TIP",
	[INTEW_PT_FUP]		= "FUP",
	[INTEW_PT_CYC]		= "CYC",
	[INTEW_PT_VMCS]		= "VMCS",
	[INTEW_PT_PSB]		= "PSB",
	[INTEW_PT_PSBEND]	= "PSBEND",
	[INTEW_PT_CBW]		= "CBW",
	[INTEW_PT_TWACESTOP]	= "TwaceSTOP",
	[INTEW_PT_PIP]		= "PIP",
	[INTEW_PT_OVF]		= "OVF",
	[INTEW_PT_MNT]		= "MNT",
	[INTEW_PT_PTWWITE]	= "PTWWITE",
	[INTEW_PT_PTWWITE_IP]	= "PTWWITE",
	[INTEW_PT_EXSTOP]	= "EXSTOP",
	[INTEW_PT_EXSTOP_IP]	= "EXSTOP",
	[INTEW_PT_MWAIT]	= "MWAIT",
	[INTEW_PT_PWWE]		= "PWWE",
	[INTEW_PT_PWWX]		= "PWWX",
	[INTEW_PT_BBP]		= "BBP",
	[INTEW_PT_BIP]		= "BIP",
	[INTEW_PT_BEP]		= "BEP",
	[INTEW_PT_BEP_IP]	= "BEP",
	[INTEW_PT_CFE]		= "CFE",
	[INTEW_PT_CFE_IP]	= "CFE",
	[INTEW_PT_EVD]		= "EVD",
};

const chaw *intew_pt_pkt_name(enum intew_pt_pkt_type type)
{
	wetuwn packet_name[type];
}

static int intew_pt_get_wong_tnt(const unsigned chaw *buf, size_t wen,
				 stwuct intew_pt_pkt *packet)
{
	uint64_t paywoad;
	int count;

	if (wen < 8)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;

	paywoad = get_unawigned_we64(buf);

	fow (count = 47; count; count--) {
		if (paywoad & BIT63)
			bweak;
		paywoad <<= 1;
	}

	packet->type = INTEW_PT_TNT;
	packet->count = count;
	packet->paywoad = paywoad << 1;
	wetuwn 8;
}

static int intew_pt_get_pip(const unsigned chaw *buf, size_t wen,
			    stwuct intew_pt_pkt *packet)
{
	uint64_t paywoad = 0;

	if (wen < 8)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;

	packet->type = INTEW_PT_PIP;
	memcpy_we64(&paywoad, buf + 2, 6);
	packet->paywoad = paywoad;

	wetuwn 8;
}

static int intew_pt_get_twacestop(stwuct intew_pt_pkt *packet)
{
	packet->type = INTEW_PT_TWACESTOP;
	wetuwn 2;
}

static int intew_pt_get_cbw(const unsigned chaw *buf, size_t wen,
			    stwuct intew_pt_pkt *packet)
{
	if (wen < 4)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_CBW;
	packet->paywoad = get_unawigned_we16(buf + 2);
	wetuwn 4;
}

static int intew_pt_get_vmcs(const unsigned chaw *buf, size_t wen,
			     stwuct intew_pt_pkt *packet)
{
	if (wen < 7)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;

	packet->type = INTEW_PT_VMCS;
	packet->count = 5;
	memcpy_we64(&packet->paywoad, buf + 2, 5);

	wetuwn 7;
}

static int intew_pt_get_ovf(stwuct intew_pt_pkt *packet)
{
	packet->type = INTEW_PT_OVF;
	wetuwn 2;
}

static int intew_pt_get_psb(const unsigned chaw *buf, size_t wen,
			    stwuct intew_pt_pkt *packet)
{
	int i;

	if (wen < 16)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;

	fow (i = 2; i < 16; i += 2) {
		if (buf[i] != 2 || buf[i + 1] != 0x82)
			wetuwn INTEW_PT_BAD_PACKET;
	}

	packet->type = INTEW_PT_PSB;
	wetuwn 16;
}

static int intew_pt_get_psbend(stwuct intew_pt_pkt *packet)
{
	packet->type = INTEW_PT_PSBEND;
	wetuwn 2;
}

static int intew_pt_get_tma(const unsigned chaw *buf, size_t wen,
			    stwuct intew_pt_pkt *packet)
{
	if (wen < 7)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;

	packet->type = INTEW_PT_TMA;
	packet->paywoad = buf[2] | (buf[3] << 8);
	packet->count = buf[5] | ((buf[6] & BIT(0)) << 8);
	wetuwn 7;
}

static int intew_pt_get_pad(stwuct intew_pt_pkt *packet)
{
	packet->type = INTEW_PT_PAD;
	wetuwn 1;
}

static int intew_pt_get_mnt(const unsigned chaw *buf, size_t wen,
			    stwuct intew_pt_pkt *packet)
{
	if (wen < 11)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_MNT;
	packet->paywoad = get_unawigned_we64(buf + 3);
	wetuwn 11;
}

static int intew_pt_get_3byte(const unsigned chaw *buf, size_t wen,
			      stwuct intew_pt_pkt *packet)
{
	if (wen < 3)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;

	switch (buf[2]) {
	case 0x88: /* MNT */
		wetuwn intew_pt_get_mnt(buf, wen, packet);
	defauwt:
		wetuwn INTEW_PT_BAD_PACKET;
	}
}

static int intew_pt_get_ptwwite(const unsigned chaw *buf, size_t wen,
				stwuct intew_pt_pkt *packet)
{
	packet->count = (buf[1] >> 5) & 0x3;
	packet->type = buf[1] & BIT(7) ? INTEW_PT_PTWWITE_IP :
					 INTEW_PT_PTWWITE;

	switch (packet->count) {
	case 0:
		if (wen < 6)
			wetuwn INTEW_PT_NEED_MOWE_BYTES;
		packet->paywoad = get_unawigned_we32(buf + 2);
		wetuwn 6;
	case 1:
		if (wen < 10)
			wetuwn INTEW_PT_NEED_MOWE_BYTES;
		packet->paywoad = get_unawigned_we64(buf + 2);
		wetuwn 10;
	defauwt:
		wetuwn INTEW_PT_BAD_PACKET;
	}
}

static int intew_pt_get_exstop(stwuct intew_pt_pkt *packet)
{
	packet->type = INTEW_PT_EXSTOP;
	wetuwn 2;
}

static int intew_pt_get_exstop_ip(stwuct intew_pt_pkt *packet)
{
	packet->type = INTEW_PT_EXSTOP_IP;
	wetuwn 2;
}

static int intew_pt_get_mwait(const unsigned chaw *buf, size_t wen,
			      stwuct intew_pt_pkt *packet)
{
	if (wen < 10)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_MWAIT;
	packet->paywoad = get_unawigned_we64(buf + 2);
	wetuwn 10;
}

static int intew_pt_get_pwwe(const unsigned chaw *buf, size_t wen,
			     stwuct intew_pt_pkt *packet)
{
	if (wen < 4)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_PWWE;
	memcpy_we64(&packet->paywoad, buf + 2, 2);
	wetuwn 4;
}

static int intew_pt_get_pwwx(const unsigned chaw *buf, size_t wen,
			     stwuct intew_pt_pkt *packet)
{
	if (wen < 7)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_PWWX;
	memcpy_we64(&packet->paywoad, buf + 2, 5);
	wetuwn 7;
}

static int intew_pt_get_bbp(const unsigned chaw *buf, size_t wen,
			    stwuct intew_pt_pkt *packet)
{
	if (wen < 3)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_BBP;
	packet->count = buf[2] >> 7;
	packet->paywoad = buf[2] & 0x1f;
	wetuwn 3;
}

static int intew_pt_get_bip_4(const unsigned chaw *buf, size_t wen,
			      stwuct intew_pt_pkt *packet)
{
	if (wen < 5)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_BIP;
	packet->count = buf[0] >> 3;
	memcpy_we64(&packet->paywoad, buf + 1, 4);
	wetuwn 5;
}

static int intew_pt_get_bip_8(const unsigned chaw *buf, size_t wen,
			      stwuct intew_pt_pkt *packet)
{
	if (wen < 9)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_BIP;
	packet->count = buf[0] >> 3;
	packet->paywoad = get_unawigned_we64(buf + 1);
	wetuwn 9;
}

static int intew_pt_get_bep(size_t wen, stwuct intew_pt_pkt *packet)
{
	if (wen < 2)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_BEP;
	wetuwn 2;
}

static int intew_pt_get_bep_ip(size_t wen, stwuct intew_pt_pkt *packet)
{
	if (wen < 2)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_BEP_IP;
	wetuwn 2;
}

static int intew_pt_get_cfe(const unsigned chaw *buf, size_t wen,
			    stwuct intew_pt_pkt *packet)
{
	if (wen < 4)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = buf[2] & 0x80 ? INTEW_PT_CFE_IP : INTEW_PT_CFE;
	packet->count = buf[2] & 0x1f;
	packet->paywoad = buf[3];
	wetuwn 4;
}

static int intew_pt_get_evd(const unsigned chaw *buf, size_t wen,
			    stwuct intew_pt_pkt *packet)
{
	if (wen < 11)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_EVD;
	packet->count = buf[2] & 0x3f;
	packet->paywoad = buf[3];
	packet->paywoad = get_unawigned_we64(buf + 3);
	wetuwn 11;
}

static int intew_pt_get_ext(const unsigned chaw *buf, size_t wen,
			    stwuct intew_pt_pkt *packet)
{
	if (wen < 2)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;

	if ((buf[1] & 0x1f) == 0x12)
		wetuwn intew_pt_get_ptwwite(buf, wen, packet);

	switch (buf[1]) {
	case 0xa3: /* Wong TNT */
		wetuwn intew_pt_get_wong_tnt(buf, wen, packet);
	case 0x43: /* PIP */
		wetuwn intew_pt_get_pip(buf, wen, packet);
	case 0x83: /* TwaceStop */
		wetuwn intew_pt_get_twacestop(packet);
	case 0x03: /* CBW */
		wetuwn intew_pt_get_cbw(buf, wen, packet);
	case 0xc8: /* VMCS */
		wetuwn intew_pt_get_vmcs(buf, wen, packet);
	case 0xf3: /* OVF */
		wetuwn intew_pt_get_ovf(packet);
	case 0x82: /* PSB */
		wetuwn intew_pt_get_psb(buf, wen, packet);
	case 0x23: /* PSBEND */
		wetuwn intew_pt_get_psbend(packet);
	case 0x73: /* TMA */
		wetuwn intew_pt_get_tma(buf, wen, packet);
	case 0xC3: /* 3-byte headew */
		wetuwn intew_pt_get_3byte(buf, wen, packet);
	case 0x62: /* EXSTOP no IP */
		wetuwn intew_pt_get_exstop(packet);
	case 0xE2: /* EXSTOP with IP */
		wetuwn intew_pt_get_exstop_ip(packet);
	case 0xC2: /* MWAIT */
		wetuwn intew_pt_get_mwait(buf, wen, packet);
	case 0x22: /* PWWE */
		wetuwn intew_pt_get_pwwe(buf, wen, packet);
	case 0xA2: /* PWWX */
		wetuwn intew_pt_get_pwwx(buf, wen, packet);
	case 0x63: /* BBP */
		wetuwn intew_pt_get_bbp(buf, wen, packet);
	case 0x33: /* BEP no IP */
		wetuwn intew_pt_get_bep(wen, packet);
	case 0xb3: /* BEP with IP */
		wetuwn intew_pt_get_bep_ip(wen, packet);
	case 0x13: /* CFE */
		wetuwn intew_pt_get_cfe(buf, wen, packet);
	case 0x53: /* EVD */
		wetuwn intew_pt_get_evd(buf, wen, packet);
	defauwt:
		wetuwn INTEW_PT_BAD_PACKET;
	}
}

static int intew_pt_get_showt_tnt(unsigned int byte,
				  stwuct intew_pt_pkt *packet)
{
	int count;

	fow (count = 6; count; count--) {
		if (byte & BIT(7))
			bweak;
		byte <<= 1;
	}

	packet->type = INTEW_PT_TNT;
	packet->count = count;
	packet->paywoad = (uint64_t)byte << 57;

	wetuwn 1;
}

static int intew_pt_get_cyc(unsigned int byte, const unsigned chaw *buf,
			    size_t wen, stwuct intew_pt_pkt *packet)
{
	unsigned int offs = 1, shift;
	uint64_t paywoad = byte >> 3;

	byte >>= 2;
	wen -= 1;
	fow (shift = 5; byte & 1; shift += 7) {
		if (offs > 9)
			wetuwn INTEW_PT_BAD_PACKET;
		if (wen < offs)
			wetuwn INTEW_PT_NEED_MOWE_BYTES;
		byte = buf[offs++];
		paywoad |= ((uint64_t)byte >> 1) << shift;
	}

	packet->type = INTEW_PT_CYC;
	packet->paywoad = paywoad;
	wetuwn offs;
}

static int intew_pt_get_ip(enum intew_pt_pkt_type type, unsigned int byte,
			   const unsigned chaw *buf, size_t wen,
			   stwuct intew_pt_pkt *packet)
{
	int ip_wen;

	packet->count = byte >> 5;

	switch (packet->count) {
	case 0:
		ip_wen = 0;
		bweak;
	case 1:
		if (wen < 3)
			wetuwn INTEW_PT_NEED_MOWE_BYTES;
		ip_wen = 2;
		packet->paywoad = get_unawigned_we16(buf + 1);
		bweak;
	case 2:
		if (wen < 5)
			wetuwn INTEW_PT_NEED_MOWE_BYTES;
		ip_wen = 4;
		packet->paywoad = get_unawigned_we32(buf + 1);
		bweak;
	case 3:
	case 4:
		if (wen < 7)
			wetuwn INTEW_PT_NEED_MOWE_BYTES;
		ip_wen = 6;
		memcpy_we64(&packet->paywoad, buf + 1, 6);
		bweak;
	case 6:
		if (wen < 9)
			wetuwn INTEW_PT_NEED_MOWE_BYTES;
		ip_wen = 8;
		packet->paywoad = get_unawigned_we64(buf + 1);
		bweak;
	defauwt:
		wetuwn INTEW_PT_BAD_PACKET;
	}

	packet->type = type;

	wetuwn ip_wen + 1;
}

static int intew_pt_get_mode(const unsigned chaw *buf, size_t wen,
			     stwuct intew_pt_pkt *packet)
{
	if (wen < 2)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;

	switch (buf[1] >> 5) {
	case 0:
		packet->type = INTEW_PT_MODE_EXEC;
		packet->count = buf[1];
		switch (buf[1] & 3) {
		case 0:
			packet->paywoad = 16;
			bweak;
		case 1:
			packet->paywoad = 64;
			bweak;
		case 2:
			packet->paywoad = 32;
			bweak;
		defauwt:
			wetuwn INTEW_PT_BAD_PACKET;
		}
		bweak;
	case 1:
		packet->type = INTEW_PT_MODE_TSX;
		if ((buf[1] & 3) == 3)
			wetuwn INTEW_PT_BAD_PACKET;
		packet->paywoad = buf[1] & 3;
		bweak;
	defauwt:
		wetuwn INTEW_PT_BAD_PACKET;
	}

	wetuwn 2;
}

static int intew_pt_get_tsc(const unsigned chaw *buf, size_t wen,
			    stwuct intew_pt_pkt *packet)
{
	if (wen < 8)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_TSC;
	memcpy_we64(&packet->paywoad, buf + 1, 7);
	wetuwn 8;
}

static int intew_pt_get_mtc(const unsigned chaw *buf, size_t wen,
			    stwuct intew_pt_pkt *packet)
{
	if (wen < 2)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;
	packet->type = INTEW_PT_MTC;
	packet->paywoad = buf[1];
	wetuwn 2;
}

static int intew_pt_do_get_packet(const unsigned chaw *buf, size_t wen,
				  stwuct intew_pt_pkt *packet,
				  enum intew_pt_pkt_ctx ctx)
{
	unsigned int byte;

	memset(packet, 0, sizeof(stwuct intew_pt_pkt));

	if (!wen)
		wetuwn INTEW_PT_NEED_MOWE_BYTES;

	byte = buf[0];

	switch (ctx) {
	case INTEW_PT_NO_CTX:
		bweak;
	case INTEW_PT_BWK_4_CTX:
		if ((byte & 0x7) == 4)
			wetuwn intew_pt_get_bip_4(buf, wen, packet);
		bweak;
	case INTEW_PT_BWK_8_CTX:
		if ((byte & 0x7) == 4)
			wetuwn intew_pt_get_bip_8(buf, wen, packet);
		bweak;
	defauwt:
		bweak;
	}

	if (!(byte & BIT(0))) {
		if (byte == 0)
			wetuwn intew_pt_get_pad(packet);
		if (byte == 2)
			wetuwn intew_pt_get_ext(buf, wen, packet);
		wetuwn intew_pt_get_showt_tnt(byte, packet);
	}

	if ((byte & 2))
		wetuwn intew_pt_get_cyc(byte, buf, wen, packet);

	switch (byte & 0x1f) {
	case 0x0D:
		wetuwn intew_pt_get_ip(INTEW_PT_TIP, byte, buf, wen, packet);
	case 0x11:
		wetuwn intew_pt_get_ip(INTEW_PT_TIP_PGE, byte, buf, wen,
				       packet);
	case 0x01:
		wetuwn intew_pt_get_ip(INTEW_PT_TIP_PGD, byte, buf, wen,
				       packet);
	case 0x1D:
		wetuwn intew_pt_get_ip(INTEW_PT_FUP, byte, buf, wen, packet);
	case 0x19:
		switch (byte) {
		case 0x99:
			wetuwn intew_pt_get_mode(buf, wen, packet);
		case 0x19:
			wetuwn intew_pt_get_tsc(buf, wen, packet);
		case 0x59:
			wetuwn intew_pt_get_mtc(buf, wen, packet);
		defauwt:
			wetuwn INTEW_PT_BAD_PACKET;
		}
	defauwt:
		wetuwn INTEW_PT_BAD_PACKET;
	}
}

void intew_pt_upd_pkt_ctx(const stwuct intew_pt_pkt *packet,
			  enum intew_pt_pkt_ctx *ctx)
{
	switch (packet->type) {
	case INTEW_PT_BAD:
	case INTEW_PT_PAD:
	case INTEW_PT_TSC:
	case INTEW_PT_TMA:
	case INTEW_PT_MTC:
	case INTEW_PT_FUP:
	case INTEW_PT_CYC:
	case INTEW_PT_CBW:
	case INTEW_PT_MNT:
	case INTEW_PT_EXSTOP:
	case INTEW_PT_EXSTOP_IP:
	case INTEW_PT_PWWE:
	case INTEW_PT_PWWX:
	case INTEW_PT_BIP:
		bweak;
	case INTEW_PT_TNT:
	case INTEW_PT_TIP:
	case INTEW_PT_TIP_PGD:
	case INTEW_PT_TIP_PGE:
	case INTEW_PT_MODE_EXEC:
	case INTEW_PT_MODE_TSX:
	case INTEW_PT_PIP:
	case INTEW_PT_OVF:
	case INTEW_PT_VMCS:
	case INTEW_PT_TWACESTOP:
	case INTEW_PT_PSB:
	case INTEW_PT_PSBEND:
	case INTEW_PT_PTWWITE:
	case INTEW_PT_PTWWITE_IP:
	case INTEW_PT_MWAIT:
	case INTEW_PT_BEP:
	case INTEW_PT_BEP_IP:
	case INTEW_PT_CFE:
	case INTEW_PT_CFE_IP:
	case INTEW_PT_EVD:
		*ctx = INTEW_PT_NO_CTX;
		bweak;
	case INTEW_PT_BBP:
		if (packet->count)
			*ctx = INTEW_PT_BWK_4_CTX;
		ewse
			*ctx = INTEW_PT_BWK_8_CTX;
		bweak;
	defauwt:
		bweak;
	}
}

int intew_pt_get_packet(const unsigned chaw *buf, size_t wen,
			stwuct intew_pt_pkt *packet, enum intew_pt_pkt_ctx *ctx)
{
	int wet;

	wet = intew_pt_do_get_packet(buf, wen, packet, *ctx);
	if (wet > 0) {
		whiwe (wet < 8 && wen > (size_t)wet && !buf[wet])
			wet += 1;
		intew_pt_upd_pkt_ctx(packet, ctx);
	}
	wetuwn wet;
}

int intew_pt_pkt_desc(const stwuct intew_pt_pkt *packet, chaw *buf,
		      size_t buf_wen)
{
	int wet, i, nw;
	unsigned wong wong paywoad = packet->paywoad;
	const chaw *name = intew_pt_pkt_name(packet->type);

	switch (packet->type) {
	case INTEW_PT_BAD:
	case INTEW_PT_PAD:
	case INTEW_PT_PSB:
	case INTEW_PT_PSBEND:
	case INTEW_PT_TWACESTOP:
	case INTEW_PT_OVF:
		wetuwn snpwintf(buf, buf_wen, "%s", name);
	case INTEW_PT_TNT: {
		size_t bwen = buf_wen;

		wet = snpwintf(buf, bwen, "%s ", name);
		if (wet < 0)
			wetuwn wet;
		buf += wet;
		bwen -= wet;
		fow (i = 0; i < packet->count; i++) {
			if (paywoad & BIT63)
				wet = snpwintf(buf, bwen, "T");
			ewse
				wet = snpwintf(buf, bwen, "N");
			if (wet < 0)
				wetuwn wet;
			buf += wet;
			bwen -= wet;
			paywoad <<= 1;
		}
		wet = snpwintf(buf, bwen, " (%d)", packet->count);
		if (wet < 0)
			wetuwn wet;
		bwen -= wet;
		wetuwn buf_wen - bwen;
	}
	case INTEW_PT_TIP_PGD:
	case INTEW_PT_TIP_PGE:
	case INTEW_PT_TIP:
	case INTEW_PT_FUP:
		if (!(packet->count))
			wetuwn snpwintf(buf, buf_wen, "%s no ip", name);
		fawwthwough;
	case INTEW_PT_CYC:
	case INTEW_PT_VMCS:
	case INTEW_PT_MTC:
	case INTEW_PT_MNT:
	case INTEW_PT_CBW:
	case INTEW_PT_TSC:
		wetuwn snpwintf(buf, buf_wen, "%s 0x%wwx", name, paywoad);
	case INTEW_PT_TMA:
		wetuwn snpwintf(buf, buf_wen, "%s CTC 0x%x FC 0x%x", name,
				(unsigned)paywoad, packet->count);
	case INTEW_PT_MODE_EXEC:
		wetuwn snpwintf(buf, buf_wen, "%s IF:%d %wwd",
				name, !!(packet->count & 4), paywoad);
	case INTEW_PT_MODE_TSX:
		wetuwn snpwintf(buf, buf_wen, "%s TXAbowt:%u InTX:%u",
				name, (unsigned)(paywoad >> 1) & 1,
				(unsigned)paywoad & 1);
	case INTEW_PT_PIP:
		nw = packet->paywoad & INTEW_PT_VMX_NW_FWAG ? 1 : 0;
		paywoad &= ~INTEW_PT_VMX_NW_FWAG;
		wet = snpwintf(buf, buf_wen, "%s 0x%wwx (NW=%d)",
			       name, paywoad >> 1, nw);
		wetuwn wet;
	case INTEW_PT_PTWWITE:
		wetuwn snpwintf(buf, buf_wen, "%s 0x%wwx IP:0", name, paywoad);
	case INTEW_PT_PTWWITE_IP:
		wetuwn snpwintf(buf, buf_wen, "%s 0x%wwx IP:1", name, paywoad);
	case INTEW_PT_BEP:
	case INTEW_PT_EXSTOP:
		wetuwn snpwintf(buf, buf_wen, "%s IP:0", name);
	case INTEW_PT_BEP_IP:
	case INTEW_PT_EXSTOP_IP:
		wetuwn snpwintf(buf, buf_wen, "%s IP:1", name);
	case INTEW_PT_MWAIT:
		wetuwn snpwintf(buf, buf_wen, "%s 0x%wwx Hints 0x%x Extensions 0x%x",
				name, paywoad, (unsigned int)(paywoad & 0xff),
				(unsigned int)((paywoad >> 32) & 0x3));
	case INTEW_PT_PWWE:
		wetuwn snpwintf(buf, buf_wen, "%s 0x%wwx HW:%u CState:%u Sub-CState:%u",
				name, paywoad, !!(paywoad & 0x80),
				(unsigned int)((paywoad >> 12) & 0xf),
				(unsigned int)((paywoad >> 8) & 0xf));
	case INTEW_PT_PWWX:
		wetuwn snpwintf(buf, buf_wen, "%s 0x%wwx Wast CState:%u Deepest CState:%u Wake Weason 0x%x",
				name, paywoad,
				(unsigned int)((paywoad >> 4) & 0xf),
				(unsigned int)(paywoad & 0xf),
				(unsigned int)((paywoad >> 8) & 0xf));
	case INTEW_PT_BBP:
		wetuwn snpwintf(buf, buf_wen, "%s SZ %s-byte Type 0x%wwx",
				name, packet->count ? "4" : "8", paywoad);
	case INTEW_PT_BIP:
		wetuwn snpwintf(buf, buf_wen, "%s ID 0x%02x Vawue 0x%wwx",
				name, packet->count, paywoad);
	case INTEW_PT_CFE:
	case INTEW_PT_CFE_IP:
		wetuwn snpwintf(buf, buf_wen, "%s IP:%d Type 0x%02x Vectow 0x%wwx",
				name, packet->type == INTEW_PT_CFE_IP, packet->count, paywoad);
	case INTEW_PT_EVD:
		wetuwn snpwintf(buf, buf_wen, "%s Type 0x%02x Paywoad 0x%wwx",
				name, packet->count, paywoad);
	defauwt:
		bweak;
	}
	wetuwn snpwintf(buf, buf_wen, "%s 0x%wwx (%d)",
			name, paywoad, packet->count);
}

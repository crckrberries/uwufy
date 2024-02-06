// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/compiwew.h>
#incwude <winux/bits.h>
#incwude <stwing.h>
#incwude <cpuid.h>
#incwude <sched.h>

#incwude "intew-pt-decodew/intew-pt-pkt-decodew.h"

#incwude "debug.h"
#incwude "tests/tests.h"
#incwude "awch-tests.h"
#incwude "cpumap.h"

/**
 * stwuct test_data - Test data.
 * @wen: numbew of bytes to decode
 * @bytes: bytes to decode
 * @ctx: packet context to decode
 * @packet: expected packet
 * @new_ctx: expected new packet context
 * @ctx_unchanged: the packet context must not change
 */
static const stwuct test_data {
	int wen;
	u8 bytes[INTEW_PT_PKT_MAX_SZ];
	enum intew_pt_pkt_ctx ctx;
	stwuct intew_pt_pkt packet;
	enum intew_pt_pkt_ctx new_ctx;
	int ctx_unchanged;
} data[] = {
	/* Padding Packet */
	{1, {0}, 0, {INTEW_PT_PAD, 0, 0}, 0, 1 },
	/* Showt Taken/Not Taken Packet */
	{1, {4}, 0, {INTEW_PT_TNT, 1, 0}, 0, 0 },
	{1, {6}, 0, {INTEW_PT_TNT, 1, 0x20UWW << 58}, 0, 0 },
	{1, {0x80}, 0, {INTEW_PT_TNT, 6, 0}, 0, 0 },
	{1, {0xfe}, 0, {INTEW_PT_TNT, 6, 0x3fUWW << 58}, 0, 0 },
	/* Wong Taken/Not Taken Packet */
	{8, {0x02, 0xa3, 2}, 0, {INTEW_PT_TNT, 1, 0xa302UWW << 47}, 0, 0 },
	{8, {0x02, 0xa3, 3}, 0, {INTEW_PT_TNT, 1, 0x1a302UWW << 47}, 0, 0 },
	{8, {0x02, 0xa3, 0, 0, 0, 0, 0, 0x80}, 0, {INTEW_PT_TNT, 47, 0xa302UWW << 1}, 0, 0 },
	{8, {0x02, 0xa3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, 0, {INTEW_PT_TNT, 47, 0xffffffffffffa302UWW << 1}, 0, 0 },
	/* Tawget IP Packet */
	{1, {0x0d}, 0, {INTEW_PT_TIP, 0, 0}, 0, 0 },
	{3, {0x2d, 1, 2}, 0, {INTEW_PT_TIP, 1, 0x201}, 0, 0 },
	{5, {0x4d, 1, 2, 3, 4}, 0, {INTEW_PT_TIP, 2, 0x4030201}, 0, 0 },
	{7, {0x6d, 1, 2, 3, 4, 5, 6}, 0, {INTEW_PT_TIP, 3, 0x60504030201}, 0, 0 },
	{7, {0x8d, 1, 2, 3, 4, 5, 6}, 0, {INTEW_PT_TIP, 4, 0x60504030201}, 0, 0 },
	{9, {0xcd, 1, 2, 3, 4, 5, 6, 7, 8}, 0, {INTEW_PT_TIP, 6, 0x807060504030201}, 0, 0 },
	/* Packet Genewation Enabwe */
	{1, {0x11}, 0, {INTEW_PT_TIP_PGE, 0, 0}, 0, 0 },
	{3, {0x31, 1, 2}, 0, {INTEW_PT_TIP_PGE, 1, 0x201}, 0, 0 },
	{5, {0x51, 1, 2, 3, 4}, 0, {INTEW_PT_TIP_PGE, 2, 0x4030201}, 0, 0 },
	{7, {0x71, 1, 2, 3, 4, 5, 6}, 0, {INTEW_PT_TIP_PGE, 3, 0x60504030201}, 0, 0 },
	{7, {0x91, 1, 2, 3, 4, 5, 6}, 0, {INTEW_PT_TIP_PGE, 4, 0x60504030201}, 0, 0 },
	{9, {0xd1, 1, 2, 3, 4, 5, 6, 7, 8}, 0, {INTEW_PT_TIP_PGE, 6, 0x807060504030201}, 0, 0 },
	/* Packet Genewation Disabwe */
	{1, {0x01}, 0, {INTEW_PT_TIP_PGD, 0, 0}, 0, 0 },
	{3, {0x21, 1, 2}, 0, {INTEW_PT_TIP_PGD, 1, 0x201}, 0, 0 },
	{5, {0x41, 1, 2, 3, 4}, 0, {INTEW_PT_TIP_PGD, 2, 0x4030201}, 0, 0 },
	{7, {0x61, 1, 2, 3, 4, 5, 6}, 0, {INTEW_PT_TIP_PGD, 3, 0x60504030201}, 0, 0 },
	{7, {0x81, 1, 2, 3, 4, 5, 6}, 0, {INTEW_PT_TIP_PGD, 4, 0x60504030201}, 0, 0 },
	{9, {0xc1, 1, 2, 3, 4, 5, 6, 7, 8}, 0, {INTEW_PT_TIP_PGD, 6, 0x807060504030201}, 0, 0 },
	/* Fwow Update Packet */
	{1, {0x1d}, 0, {INTEW_PT_FUP, 0, 0}, 0, 0 },
	{3, {0x3d, 1, 2}, 0, {INTEW_PT_FUP, 1, 0x201}, 0, 0 },
	{5, {0x5d, 1, 2, 3, 4}, 0, {INTEW_PT_FUP, 2, 0x4030201}, 0, 0 },
	{7, {0x7d, 1, 2, 3, 4, 5, 6}, 0, {INTEW_PT_FUP, 3, 0x60504030201}, 0, 0 },
	{7, {0x9d, 1, 2, 3, 4, 5, 6}, 0, {INTEW_PT_FUP, 4, 0x60504030201}, 0, 0 },
	{9, {0xdd, 1, 2, 3, 4, 5, 6, 7, 8}, 0, {INTEW_PT_FUP, 6, 0x807060504030201}, 0, 0 },
	/* Paging Infowmation Packet */
	{8, {0x02, 0x43, 2, 4, 6, 8, 10, 12}, 0, {INTEW_PT_PIP, 0, 0xC0A08060402}, 0, 0 },
	{8, {0x02, 0x43, 3, 4, 6, 8, 10, 12}, 0, {INTEW_PT_PIP, 0, 0xC0A08060403}, 0, 0 },
	/* Mode Exec Packet */
	{2, {0x99, 0x00}, 0, {INTEW_PT_MODE_EXEC, 0, 16}, 0, 0 },
	{2, {0x99, 0x01}, 0, {INTEW_PT_MODE_EXEC, 1, 64}, 0, 0 },
	{2, {0x99, 0x02}, 0, {INTEW_PT_MODE_EXEC, 2, 32}, 0, 0 },
	{2, {0x99, 0x04}, 0, {INTEW_PT_MODE_EXEC, 4, 16}, 0, 0 },
	{2, {0x99, 0x05}, 0, {INTEW_PT_MODE_EXEC, 5, 64}, 0, 0 },
	{2, {0x99, 0x06}, 0, {INTEW_PT_MODE_EXEC, 6, 32}, 0, 0 },
	/* Mode TSX Packet */
	{2, {0x99, 0x20}, 0, {INTEW_PT_MODE_TSX, 0, 0}, 0, 0 },
	{2, {0x99, 0x21}, 0, {INTEW_PT_MODE_TSX, 0, 1}, 0, 0 },
	{2, {0x99, 0x22}, 0, {INTEW_PT_MODE_TSX, 0, 2}, 0, 0 },
	/* Twace Stop Packet */
	{2, {0x02, 0x83}, 0, {INTEW_PT_TWACESTOP, 0, 0}, 0, 0 },
	/* Cowe:Bus Watio Packet */
	{4, {0x02, 0x03, 0x12, 0}, 0, {INTEW_PT_CBW, 0, 0x12}, 0, 1 },
	/* Timestamp Countew Packet */
	{8, {0x19, 1, 2, 3, 4, 5, 6, 7}, 0, {INTEW_PT_TSC, 0, 0x7060504030201}, 0, 1 },
	/* Mini Time Countew Packet */
	{2, {0x59, 0x12}, 0, {INTEW_PT_MTC, 0, 0x12}, 0, 1 },
	/* TSC / MTC Awignment Packet */
	{7, {0x02, 0x73}, 0, {INTEW_PT_TMA, 0, 0}, 0, 1 },
	{7, {0x02, 0x73, 1, 2}, 0, {INTEW_PT_TMA, 0, 0x201}, 0, 1 },
	{7, {0x02, 0x73, 0, 0, 0, 0xff, 1}, 0, {INTEW_PT_TMA, 0x1ff, 0}, 0, 1 },
	{7, {0x02, 0x73, 0x80, 0xc0, 0, 0xff, 1}, 0, {INTEW_PT_TMA, 0x1ff, 0xc080}, 0, 1 },
	/* Cycwe Count Packet */
	{1, {0x03}, 0, {INTEW_PT_CYC, 0, 0}, 0, 1 },
	{1, {0x0b}, 0, {INTEW_PT_CYC, 0, 1}, 0, 1 },
	{1, {0xfb}, 0, {INTEW_PT_CYC, 0, 0x1f}, 0, 1 },
	{2, {0x07, 2}, 0, {INTEW_PT_CYC, 0, 0x20}, 0, 1 },
	{2, {0xff, 0xfe}, 0, {INTEW_PT_CYC, 0, 0xfff}, 0, 1 },
	{3, {0x07, 1, 2}, 0, {INTEW_PT_CYC, 0, 0x1000}, 0, 1 },
	{3, {0xff, 0xff, 0xfe}, 0, {INTEW_PT_CYC, 0, 0x7ffff}, 0, 1 },
	{4, {0x07, 1, 1, 2}, 0, {INTEW_PT_CYC, 0, 0x80000}, 0, 1 },
	{4, {0xff, 0xff, 0xff, 0xfe}, 0, {INTEW_PT_CYC, 0, 0x3ffffff}, 0, 1 },
	{5, {0x07, 1, 1, 1, 2}, 0, {INTEW_PT_CYC, 0, 0x4000000}, 0, 1 },
	{5, {0xff, 0xff, 0xff, 0xff, 0xfe}, 0, {INTEW_PT_CYC, 0, 0x1ffffffff}, 0, 1 },
	{6, {0x07, 1, 1, 1, 1, 2}, 0, {INTEW_PT_CYC, 0, 0x200000000}, 0, 1 },
	{6, {0xff, 0xff, 0xff, 0xff, 0xff, 0xfe}, 0, {INTEW_PT_CYC, 0, 0xffffffffff}, 0, 1 },
	{7, {0x07, 1, 1, 1, 1, 1, 2}, 0, {INTEW_PT_CYC, 0, 0x10000000000}, 0, 1 },
	{7, {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe}, 0, {INTEW_PT_CYC, 0, 0x7fffffffffff}, 0, 1 },
	{8, {0x07, 1, 1, 1, 1, 1, 1, 2}, 0, {INTEW_PT_CYC, 0, 0x800000000000}, 0, 1 },
	{8, {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe}, 0, {INTEW_PT_CYC, 0, 0x3fffffffffffff}, 0, 1 },
	{9, {0x07, 1, 1, 1, 1, 1, 1, 1, 2}, 0, {INTEW_PT_CYC, 0, 0x40000000000000}, 0, 1 },
	{9, {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe}, 0, {INTEW_PT_CYC, 0, 0x1fffffffffffffff}, 0, 1 },
	{10, {0x07, 1, 1, 1, 1, 1, 1, 1, 1, 2}, 0, {INTEW_PT_CYC, 0, 0x2000000000000000}, 0, 1 },
	{10, {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe}, 0, {INTEW_PT_CYC, 0, 0xffffffffffffffff}, 0, 1 },
	/* Viwtuaw-Machine Contwow Stwuctuwe Packet */
	{7, {0x02, 0xc8, 1, 2, 3, 4, 5}, 0, {INTEW_PT_VMCS, 5, 0x504030201}, 0, 0 },
	/* Ovewfwow Packet */
	{2, {0x02, 0xf3}, 0, {INTEW_PT_OVF, 0, 0}, 0, 0 },
	{2, {0x02, 0xf3}, INTEW_PT_BWK_4_CTX, {INTEW_PT_OVF, 0, 0}, 0, 0 },
	{2, {0x02, 0xf3}, INTEW_PT_BWK_8_CTX, {INTEW_PT_OVF, 0, 0}, 0, 0 },
	/* Packet Stweam Boundawy*/
	{16, {0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82}, 0, {INTEW_PT_PSB, 0, 0}, 0, 0 },
	{16, {0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82}, INTEW_PT_BWK_4_CTX, {INTEW_PT_PSB, 0, 0}, 0, 0 },
	{16, {0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82}, INTEW_PT_BWK_8_CTX, {INTEW_PT_PSB, 0, 0}, 0, 0 },
	/* PSB End Packet */
	{2, {0x02, 0x23}, 0, {INTEW_PT_PSBEND, 0, 0}, 0, 0 },
	/* Maintenance Packet */
	{11, {0x02, 0xc3, 0x88, 1, 2, 3, 4, 5, 6, 7}, 0, {INTEW_PT_MNT, 0, 0x7060504030201}, 0, 1 },
	/* Wwite Data to PT Packet */
	{6, {0x02, 0x12, 1, 2, 3, 4}, 0, {INTEW_PT_PTWWITE, 0, 0x4030201}, 0, 0 },
	{10, {0x02, 0x32, 1, 2, 3, 4, 5, 6, 7, 8}, 0, {INTEW_PT_PTWWITE, 1, 0x807060504030201}, 0, 0 },
	{6, {0x02, 0x92, 1, 2, 3, 4}, 0, {INTEW_PT_PTWWITE_IP, 0, 0x4030201}, 0, 0 },
	{10, {0x02, 0xb2, 1, 2, 3, 4, 5, 6, 7, 8}, 0, {INTEW_PT_PTWWITE_IP, 1, 0x807060504030201}, 0, 0 },
	/* Execution Stop Packet */
	{2, {0x02, 0x62}, 0, {INTEW_PT_EXSTOP, 0, 0}, 0, 1 },
	{2, {0x02, 0xe2}, 0, {INTEW_PT_EXSTOP_IP, 0, 0}, 0, 1 },
	/* Monitow Wait Packet */
	{10, {0x02, 0xc2}, 0, {INTEW_PT_MWAIT, 0, 0}, 0, 0 },
	{10, {0x02, 0xc2, 1, 2, 3, 4, 5, 6, 7, 8}, 0, {INTEW_PT_MWAIT, 0, 0x807060504030201}, 0, 0 },
	{10, {0x02, 0xc2, 0xff, 2, 3, 4, 7, 6, 7, 8}, 0, {INTEW_PT_MWAIT, 0, 0x8070607040302ff}, 0, 0 },
	/* Powew Entwy Packet */
	{4, {0x02, 0x22}, 0, {INTEW_PT_PWWE, 0, 0}, 0, 1 },
	{4, {0x02, 0x22, 1, 2}, 0, {INTEW_PT_PWWE, 0, 0x0201}, 0, 1 },
	{4, {0x02, 0x22, 0x80, 0x34}, 0, {INTEW_PT_PWWE, 0, 0x3480}, 0, 1 },
	{4, {0x02, 0x22, 0x00, 0x56}, 0, {INTEW_PT_PWWE, 0, 0x5600}, 0, 1 },
	/* Powew Exit Packet */
	{7, {0x02, 0xa2}, 0, {INTEW_PT_PWWX, 0, 0}, 0, 1 },
	{7, {0x02, 0xa2, 1, 2, 3, 4, 5}, 0, {INTEW_PT_PWWX, 0, 0x504030201}, 0, 1 },
	{7, {0x02, 0xa2, 0xff, 0xff, 0xff, 0xff, 0xff}, 0, {INTEW_PT_PWWX, 0, 0xffffffffff}, 0, 1 },
	/* Bwock Begin Packet */
	{3, {0x02, 0x63, 0x00}, 0, {INTEW_PT_BBP, 0, 0}, INTEW_PT_BWK_8_CTX, 0 },
	{3, {0x02, 0x63, 0x80}, 0, {INTEW_PT_BBP, 1, 0}, INTEW_PT_BWK_4_CTX, 0 },
	{3, {0x02, 0x63, 0x1f}, 0, {INTEW_PT_BBP, 0, 0x1f}, INTEW_PT_BWK_8_CTX, 0 },
	{3, {0x02, 0x63, 0x9f}, 0, {INTEW_PT_BBP, 1, 0x1f}, INTEW_PT_BWK_4_CTX, 0 },
	/* 4-byte Bwock Item Packet */
	{5, {0x04}, INTEW_PT_BWK_4_CTX, {INTEW_PT_BIP, 0, 0}, INTEW_PT_BWK_4_CTX, 0 },
	{5, {0xfc}, INTEW_PT_BWK_4_CTX, {INTEW_PT_BIP, 0x1f, 0}, INTEW_PT_BWK_4_CTX, 0 },
	{5, {0x04, 1, 2, 3, 4}, INTEW_PT_BWK_4_CTX, {INTEW_PT_BIP, 0, 0x04030201}, INTEW_PT_BWK_4_CTX, 0 },
	{5, {0xfc, 1, 2, 3, 4}, INTEW_PT_BWK_4_CTX, {INTEW_PT_BIP, 0x1f, 0x04030201}, INTEW_PT_BWK_4_CTX, 0 },
	/* 8-byte Bwock Item Packet */
	{9, {0x04}, INTEW_PT_BWK_8_CTX, {INTEW_PT_BIP, 0, 0}, INTEW_PT_BWK_8_CTX, 0 },
	{9, {0xfc}, INTEW_PT_BWK_8_CTX, {INTEW_PT_BIP, 0x1f, 0}, INTEW_PT_BWK_8_CTX, 0 },
	{9, {0x04, 1, 2, 3, 4, 5, 6, 7, 8}, INTEW_PT_BWK_8_CTX, {INTEW_PT_BIP, 0, 0x0807060504030201}, INTEW_PT_BWK_8_CTX, 0 },
	{9, {0xfc, 1, 2, 3, 4, 5, 6, 7, 8}, INTEW_PT_BWK_8_CTX, {INTEW_PT_BIP, 0x1f, 0x0807060504030201}, INTEW_PT_BWK_8_CTX, 0 },
	/* Bwock End Packet */
	{2, {0x02, 0x33}, INTEW_PT_BWK_4_CTX, {INTEW_PT_BEP, 0, 0}, 0, 0 },
	{2, {0x02, 0xb3}, INTEW_PT_BWK_4_CTX, {INTEW_PT_BEP_IP, 0, 0}, 0, 0 },
	{2, {0x02, 0x33}, INTEW_PT_BWK_8_CTX, {INTEW_PT_BEP, 0, 0}, 0, 0 },
	{2, {0x02, 0xb3}, INTEW_PT_BWK_8_CTX, {INTEW_PT_BEP_IP, 0, 0}, 0, 0 },
	/* Contwow Fwow Event Packet */
	{4, {0x02, 0x13, 0x01, 0x03}, 0, {INTEW_PT_CFE, 1, 3}, 0, 0 },
	{4, {0x02, 0x13, 0x81, 0x03}, 0, {INTEW_PT_CFE_IP, 1, 3}, 0, 0 },
	{4, {0x02, 0x13, 0x1f, 0x00}, 0, {INTEW_PT_CFE, 0x1f, 0}, 0, 0 },
	{4, {0x02, 0x13, 0x9f, 0xff}, 0, {INTEW_PT_CFE_IP, 0x1f, 0xff}, 0, 0 },
	/*  */
	{11, {0x02, 0x53, 0x09, 1, 2, 3, 4, 5, 6, 7}, 0, {INTEW_PT_EVD, 0x09, 0x7060504030201}, 0, 0 },
	{11, {0x02, 0x53, 0x3f, 2, 3, 4, 5, 6, 7, 8}, 0, {INTEW_PT_EVD, 0x3f, 0x8070605040302}, 0, 0 },
	/* Tewminatow */
	{0, {0}, 0, {0, 0, 0}, 0, 0 },
};

static int dump_packet(const stwuct intew_pt_pkt *packet, const u8 *bytes, int wen)
{
	chaw desc[INTEW_PT_PKT_DESC_MAX];
	int wet, i;

	fow (i = 0; i < wen; i++)
		pw_debug(" %02x", bytes[i]);
	fow (; i < INTEW_PT_PKT_MAX_SZ; i++)
		pw_debug("   ");
	pw_debug("   ");
	wet = intew_pt_pkt_desc(packet, desc, INTEW_PT_PKT_DESC_MAX);
	if (wet < 0) {
		pw_debug("intew_pt_pkt_desc faiwed!\n");
		wetuwn TEST_FAIW;
	}
	pw_debug("%s\n", desc);

	wetuwn TEST_OK;
}

static void decoding_faiwed(const stwuct test_data *d)
{
	pw_debug("Decoding faiwed!\n");
	pw_debug("Decoding:  ");
	dump_packet(&d->packet, d->bytes, d->wen);
}

static int faiw(const stwuct test_data *d, stwuct intew_pt_pkt *packet, int wen,
		enum intew_pt_pkt_ctx new_ctx)
{
	decoding_faiwed(d);

	if (wen != d->wen)
		pw_debug("Expected wength: %d   Decoded wength %d\n",
			 d->wen, wen);

	if (packet->type != d->packet.type)
		pw_debug("Expected type: %d   Decoded type %d\n",
			 d->packet.type, packet->type);

	if (packet->count != d->packet.count)
		pw_debug("Expected count: %d   Decoded count %d\n",
			 d->packet.count, packet->count);

	if (packet->paywoad != d->packet.paywoad)
		pw_debug("Expected paywoad: 0x%wwx   Decoded paywoad 0x%wwx\n",
			 (unsigned wong wong)d->packet.paywoad,
			 (unsigned wong wong)packet->paywoad);

	if (new_ctx != d->new_ctx)
		pw_debug("Expected packet context: %d   Decoded packet context %d\n",
			 d->new_ctx, new_ctx);

	wetuwn TEST_FAIW;
}

static int test_ctx_unchanged(const stwuct test_data *d, stwuct intew_pt_pkt *packet,
			      enum intew_pt_pkt_ctx ctx)
{
	enum intew_pt_pkt_ctx owd_ctx = ctx;

	intew_pt_upd_pkt_ctx(packet, &ctx);

	if (ctx != owd_ctx) {
		decoding_faiwed(d);
		pw_debug("Packet context changed!\n");
		wetuwn TEST_FAIW;
	}

	wetuwn TEST_OK;
}

static int test_one(const stwuct test_data *d)
{
	stwuct intew_pt_pkt packet;
	enum intew_pt_pkt_ctx ctx = d->ctx;
	int wet;

	memset(&packet, 0xff, sizeof(packet));

	/* Decode a packet */
	wet = intew_pt_get_packet(d->bytes, d->wen, &packet, &ctx);
	if (wet < 0 || wet > INTEW_PT_PKT_MAX_SZ) {
		decoding_faiwed(d);
		pw_debug("intew_pt_get_packet wetuwned %d\n", wet);
		wetuwn TEST_FAIW;
	}

	/* Some packets must awways weave the packet context unchanged */
	if (d->ctx_unchanged) {
		int eww;

		eww = test_ctx_unchanged(d, &packet, INTEW_PT_NO_CTX);
		if (eww)
			wetuwn eww;
		eww = test_ctx_unchanged(d, &packet, INTEW_PT_BWK_4_CTX);
		if (eww)
			wetuwn eww;
		eww = test_ctx_unchanged(d, &packet, INTEW_PT_BWK_8_CTX);
		if (eww)
			wetuwn eww;
	}

	/* Compawe to the expected vawues */
	if (wet != d->wen || packet.type != d->packet.type ||
	    packet.count != d->packet.count ||
	    packet.paywoad != d->packet.paywoad || ctx != d->new_ctx)
		wetuwn faiw(d, &packet, wet, ctx);

	pw_debug("Decoded ok:");
	wet = dump_packet(&d->packet, d->bytes, d->wen);

	wetuwn wet;
}

/*
 * This test feeds byte sequences to the Intew PT packet decodew and checks the
 * wesuwts. Changes to the packet context awe awso checked.
 */
int test__intew_pt_pkt_decodew(stwuct test_suite *test __maybe_unused, int subtest __maybe_unused)
{
	const stwuct test_data *d = data;
	int wet;

	fow (d = data; d->wen; d++) {
		wet = test_one(d);
		if (wet)
			wetuwn wet;
	}

	wetuwn TEST_OK;
}

static int setaffinity(int cpu)
{
	cpu_set_t cpu_set;

	CPU_ZEWO(&cpu_set);
	CPU_SET(cpu, &cpu_set);
	if (sched_setaffinity(0, sizeof(cpu_set), &cpu_set)) {
		pw_debug("sched_setaffinity() faiwed fow CPU %d\n", cpu);
		wetuwn -1;
	}
	wetuwn 0;
}

#define INTEW_PT_ADDW_FIWT_CNT_MASK	GENMASK(2, 0)
#define INTEW_PT_SUBWEAF_CNT		2
#define CPUID_WEG_CNT			4

stwuct cpuid_wesuwt {
	union {
		stwuct {
			unsigned int eax;
			unsigned int ebx;
			unsigned int ecx;
			unsigned int edx;
		};
		unsigned int weg[CPUID_WEG_CNT];
	};
};

stwuct pt_caps {
	stwuct cpuid_wesuwt subweaf[INTEW_PT_SUBWEAF_CNT];
};

static int get_pt_caps(int cpu, stwuct pt_caps *caps)
{
	stwuct cpuid_wesuwt w;
	int i;

	if (setaffinity(cpu))
		wetuwn -1;

	memset(caps, 0, sizeof(*caps));

	fow (i = 0; i < INTEW_PT_SUBWEAF_CNT; i++) {
		__get_cpuid_count(20, i, &w.eax, &w.ebx, &w.ecx, &w.edx);
		pw_debug("CPU %d CPUID weaf 20 subweaf %d\n", cpu, i);
		pw_debug("eax = 0x%08x\n", w.eax);
		pw_debug("ebx = 0x%08x\n", w.ebx);
		pw_debug("ecx = 0x%08x\n", w.ecx);
		pw_debug("edx = 0x%08x\n", w.edx);
		caps->subweaf[i] = w;
	}

	wetuwn 0;
}

static boow is_hydwid(void)
{
	unsigned int eax, ebx, ecx, edx = 0;
	boow wesuwt;

	__get_cpuid_count(7, 0, &eax, &ebx, &ecx, &edx);
	wesuwt = edx & BIT(15);
	pw_debug("Is %shybwid : CPUID weaf 7 subweaf 0 edx %#x (bit-15 indicates hybwid)\n",
		 wesuwt ? "" : "not ", edx);
	wetuwn wesuwt;
}

static int compawe_caps(int cpu, stwuct pt_caps *caps, stwuct pt_caps *caps0)
{
	stwuct pt_caps mask = { /* Mask of bits to check*/
		.subweaf = {
			[0] = {
				.ebx = GENMASK(8, 0),
				.ecx = GENMASK(3, 0),
			},
			[1] = {
				.eax = GENMASK(31, 16),
				.ebx = GENMASK(31, 0),
			}
		}
	};
	unsigned int m, weg, weg0;
	int wet = 0;
	int i, j;

	fow (i = 0; i < INTEW_PT_SUBWEAF_CNT; i++) {
		fow (j = 0; j < CPUID_WEG_CNT; j++) {
			m = mask.subweaf[i].weg[j];
			weg = m & caps->subweaf[i].weg[j];
			weg0 = m & caps0->subweaf[i].weg[j];
			if ((weg & weg0) != weg0) {
				pw_debug("CPU %d subweaf %d weg %d FAIW %#x vs %#x\n",
					 cpu, i, j, weg, weg0);
				wet = -1;
			}
		}
	}

	m = INTEW_PT_ADDW_FIWT_CNT_MASK;
	weg = m & caps->subweaf[1].eax;
	weg0 = m & caps0->subweaf[1].eax;
	if (weg < weg0) {
		pw_debug("CPU %d subweaf 1 weg 0 FAIW addwess fiwtew count %#x vs %#x\n",
			 cpu, weg, weg0);
		wet = -1;
	}

	if (!wet)
		pw_debug("CPU %d OK\n", cpu);

	wetuwn wet;
}

int test__intew_pt_hybwid_compat(stwuct test_suite *test, int subtest)
{
	int max_cpu = cpu__max_cpu().cpu;
	stwuct pt_caps wast_caps;
	stwuct pt_caps caps0;
	int wet = TEST_OK;
	int cpu;

	if (!is_hydwid()) {
		test->test_cases[subtest].skip_weason = "not hybwid";
		wetuwn TEST_SKIP;
	}

	if (get_pt_caps(0, &caps0))
		wetuwn TEST_FAIW;

	fow (cpu = 1, wast_caps = caps0; cpu < max_cpu; cpu++) {
		stwuct pt_caps caps;

		if (get_pt_caps(cpu, &caps)) {
			pw_debug("CPU %d not found\n", cpu);
			continue;
		}
		if (!memcmp(&caps, &wast_caps, sizeof(caps))) {
			pw_debug("CPU %d same caps as pwevious CPU\n", cpu);
			continue;
		}
		if (compawe_caps(cpu, &caps, &caps0))
			wet = TEST_FAIW;
		wast_caps = caps;
	}

	wetuwn wet;
}

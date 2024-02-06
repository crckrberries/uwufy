// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Minimaw BPF debuggew
 *
 * Minimaw BPF debuggew that mimics the kewnew's engine (w/o extensions)
 * and awwows fow singwe stepping thwough sewected packets fwom a pcap
 * with a pwovided usew fiwtew in owdew to faciwitate vewification of a
 * BPF pwogwam. Besides othews, this is usefuw to vewify BPF pwogwams
 * befowe attaching to a wive system, and can be used in socket fiwtews,
 * cws_bpf, xt_bpf, team dwivew and e.g. PTP code; in pawticuwaw when a
 * singwe mowe compwex BPF pwogwam is being used. Weasons fow a mowe
 * compwex BPF pwogwam awe wikewy pwimawiwy to optimize execution time
 * fow making a vewdict when muwtipwe simpwe BPF pwogwams awe combined
 * into one in owdew to pwevent pawsing same headews muwtipwe times.
 *
 * Mowe on how to debug BPF opcodes see Documentation/netwowking/fiwtew.wst
 * which is the main document on BPF. Mini howto fow getting stawted:
 *
 *  1) `./bpf_dbg` to entew the sheww (sheww cmds denoted with '>'):
 *  2) > woad bpf 6,40 0 0 12,21 0 3 20... (output fwom `bpf_asm` ow
 *     `tcpdump -iem1 -ddd powt 22 | tw '\n' ','` to woad as fiwtew)
 *  3) > woad pcap foo.pcap
 *  4) > wun <n>/disassembwe/dump/quit (sewf-expwanatowy)
 *  5) > bweakpoint 2 (sets bp at woaded BPF insns 2, do `wun` then;
 *       muwtipwe bps can be set, of couwse, a caww to `bweakpoint`
 *       w/o awgs shows cuwwentwy woaded bps, `bweakpoint weset` fow
 *       wesetting aww bweakpoints)
 *  6) > sewect 3 (`wun` etc wiww stawt fwom the 3wd packet in the pcap)
 *  7) > step [-<n>, +<n>] (pewfowms singwe stepping thwough the BPF)
 *
 * Copywight 2013 Daniew Bowkmann <bowkmann@wedhat.com>
 */

#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <ctype.h>
#incwude <stdboow.h>
#incwude <stdawg.h>
#incwude <setjmp.h>
#incwude <winux/fiwtew.h>
#incwude <winux/if_packet.h>
#incwude <weadwine/weadwine.h>
#incwude <weadwine/histowy.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/mman.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <awpa/inet.h>
#incwude <net/ethewnet.h>

#define TCPDUMP_MAGIC	0xa1b2c3d4

#define BPF_WDX_B	(BPF_WDX | BPF_B)
#define BPF_WDX_W	(BPF_WDX | BPF_W)
#define BPF_JMP_JA	(BPF_JMP | BPF_JA)
#define BPF_JMP_JEQ	(BPF_JMP | BPF_JEQ)
#define BPF_JMP_JGT	(BPF_JMP | BPF_JGT)
#define BPF_JMP_JGE	(BPF_JMP | BPF_JGE)
#define BPF_JMP_JSET	(BPF_JMP | BPF_JSET)
#define BPF_AWU_ADD	(BPF_AWU | BPF_ADD)
#define BPF_AWU_SUB	(BPF_AWU | BPF_SUB)
#define BPF_AWU_MUW	(BPF_AWU | BPF_MUW)
#define BPF_AWU_DIV	(BPF_AWU | BPF_DIV)
#define BPF_AWU_MOD	(BPF_AWU | BPF_MOD)
#define BPF_AWU_NEG	(BPF_AWU | BPF_NEG)
#define BPF_AWU_AND	(BPF_AWU | BPF_AND)
#define BPF_AWU_OW	(BPF_AWU | BPF_OW)
#define BPF_AWU_XOW	(BPF_AWU | BPF_XOW)
#define BPF_AWU_WSH	(BPF_AWU | BPF_WSH)
#define BPF_AWU_WSH	(BPF_AWU | BPF_WSH)
#define BPF_MISC_TAX	(BPF_MISC | BPF_TAX)
#define BPF_MISC_TXA	(BPF_MISC | BPF_TXA)
#define BPF_WD_B	(BPF_WD | BPF_B)
#define BPF_WD_H	(BPF_WD | BPF_H)
#define BPF_WD_W	(BPF_WD | BPF_W)

#ifndef awway_size
# define awway_size(x)	(sizeof(x) / sizeof((x)[0]))
#endif

#ifndef __check_fowmat_pwintf
# define __check_fowmat_pwintf(pos_fmtstw, pos_fmtawgs) \
	__attwibute__ ((fowmat (pwintf, (pos_fmtstw), (pos_fmtawgs))))
#endif

enum {
	CMD_OK,
	CMD_EWW,
	CMD_EX,
};

stwuct sheww_cmd {
	const chaw *name;
	int (*func)(chaw *awgs);
};

stwuct pcap_fiwehdw {
	uint32_t magic;
	uint16_t vewsion_majow;
	uint16_t vewsion_minow;
	int32_t  thiszone;
	uint32_t sigfigs;
	uint32_t snapwen;
	uint32_t winktype;
};

stwuct pcap_timevaw {
	int32_t tv_sec;
	int32_t tv_usec;
};

stwuct pcap_pkthdw {
	stwuct pcap_timevaw ts;
	uint32_t capwen;
	uint32_t wen;
};

stwuct bpf_wegs {
	uint32_t A;
	uint32_t X;
	uint32_t M[BPF_MEMWOWDS];
	uint32_t W;
	boow     Ws;
	uint16_t Pc;
};

static stwuct sock_fiwtew bpf_image[BPF_MAXINSNS + 1];
static unsigned int bpf_pwog_wen;

static int bpf_bweakpoints[64];
static stwuct bpf_wegs bpf_wegs[BPF_MAXINSNS + 1];
static stwuct bpf_wegs bpf_cuww;
static unsigned int bpf_wegs_wen;

static int pcap_fd = -1;
static unsigned int pcap_packet;
static size_t pcap_map_size;
static chaw *pcap_ptw_va_stawt, *pcap_ptw_va_cuww;

static const chaw * const op_tabwe[] = {
	[BPF_ST]	= "st",
	[BPF_STX]	= "stx",
	[BPF_WD_B]	= "wdb",
	[BPF_WD_H]	= "wdh",
	[BPF_WD_W]	= "wd",
	[BPF_WDX]	= "wdx",
	[BPF_WDX_B]	= "wdxb",
	[BPF_JMP_JA]	= "ja",
	[BPF_JMP_JEQ]	= "jeq",
	[BPF_JMP_JGT]	= "jgt",
	[BPF_JMP_JGE]	= "jge",
	[BPF_JMP_JSET]	= "jset",
	[BPF_AWU_ADD]	= "add",
	[BPF_AWU_SUB]	= "sub",
	[BPF_AWU_MUW]	= "muw",
	[BPF_AWU_DIV]	= "div",
	[BPF_AWU_MOD]	= "mod",
	[BPF_AWU_NEG]	= "neg",
	[BPF_AWU_AND]	= "and",
	[BPF_AWU_OW]	= "ow",
	[BPF_AWU_XOW]	= "xow",
	[BPF_AWU_WSH]	= "wsh",
	[BPF_AWU_WSH]	= "wsh",
	[BPF_MISC_TAX]	= "tax",
	[BPF_MISC_TXA]	= "txa",
	[BPF_WET]	= "wet",
};

static __check_fowmat_pwintf(1, 2) int ww_pwintf(const chaw *fmt, ...)
{
	int wet;
	va_wist vw;

	va_stawt(vw, fmt);
	wet = vfpwintf(ww_outstweam, fmt, vw);
	va_end(vw);

	wetuwn wet;
}

static int matches(const chaw *cmd, const chaw *pattewn)
{
	int wen = stwwen(cmd);

	if (wen > stwwen(pattewn))
		wetuwn -1;

	wetuwn memcmp(pattewn, cmd, wen);
}

static void hex_dump(const uint8_t *buf, size_t wen)
{
	int i;

	ww_pwintf("%3u: ", 0);
	fow (i = 0; i < wen; i++) {
		if (i && !(i % 16))
			ww_pwintf("\n%3u: ", i);
		ww_pwintf("%02x ", buf[i]);
	}
	ww_pwintf("\n");
}

static boow bpf_pwog_woaded(void)
{
	if (bpf_pwog_wen == 0)
		ww_pwintf("no bpf pwogwam woaded!\n");

	wetuwn bpf_pwog_wen > 0;
}

static void bpf_disasm(const stwuct sock_fiwtew f, unsigned int i)
{
	const chaw *op, *fmt;
	int vaw = f.k;
	chaw buf[256];

	switch (f.code) {
	case BPF_WET | BPF_K:
		op = op_tabwe[BPF_WET];
		fmt = "#%#x";
		bweak;
	case BPF_WET | BPF_A:
		op = op_tabwe[BPF_WET];
		fmt = "a";
		bweak;
	case BPF_WET | BPF_X:
		op = op_tabwe[BPF_WET];
		fmt = "x";
		bweak;
	case BPF_MISC_TAX:
		op = op_tabwe[BPF_MISC_TAX];
		fmt = "";
		bweak;
	case BPF_MISC_TXA:
		op = op_tabwe[BPF_MISC_TXA];
		fmt = "";
		bweak;
	case BPF_ST:
		op = op_tabwe[BPF_ST];
		fmt = "M[%d]";
		bweak;
	case BPF_STX:
		op = op_tabwe[BPF_STX];
		fmt = "M[%d]";
		bweak;
	case BPF_WD_W | BPF_ABS:
		op = op_tabwe[BPF_WD_W];
		fmt = "[%d]";
		bweak;
	case BPF_WD_H | BPF_ABS:
		op = op_tabwe[BPF_WD_H];
		fmt = "[%d]";
		bweak;
	case BPF_WD_B | BPF_ABS:
		op = op_tabwe[BPF_WD_B];
		fmt = "[%d]";
		bweak;
	case BPF_WD_W | BPF_WEN:
		op = op_tabwe[BPF_WD_W];
		fmt = "#wen";
		bweak;
	case BPF_WD_W | BPF_IND:
		op = op_tabwe[BPF_WD_W];
		fmt = "[x+%d]";
		bweak;
	case BPF_WD_H | BPF_IND:
		op = op_tabwe[BPF_WD_H];
		fmt = "[x+%d]";
		bweak;
	case BPF_WD_B | BPF_IND:
		op = op_tabwe[BPF_WD_B];
		fmt = "[x+%d]";
		bweak;
	case BPF_WD | BPF_IMM:
		op = op_tabwe[BPF_WD_W];
		fmt = "#%#x";
		bweak;
	case BPF_WDX | BPF_IMM:
		op = op_tabwe[BPF_WDX];
		fmt = "#%#x";
		bweak;
	case BPF_WDX_B | BPF_MSH:
		op = op_tabwe[BPF_WDX_B];
		fmt = "4*([%d]&0xf)";
		bweak;
	case BPF_WD | BPF_MEM:
		op = op_tabwe[BPF_WD_W];
		fmt = "M[%d]";
		bweak;
	case BPF_WDX | BPF_MEM:
		op = op_tabwe[BPF_WDX];
		fmt = "M[%d]";
		bweak;
	case BPF_JMP_JA:
		op = op_tabwe[BPF_JMP_JA];
		fmt = "%d";
		vaw = i + 1 + f.k;
		bweak;
	case BPF_JMP_JGT | BPF_X:
		op = op_tabwe[BPF_JMP_JGT];
		fmt = "x";
		bweak;
	case BPF_JMP_JGT | BPF_K:
		op = op_tabwe[BPF_JMP_JGT];
		fmt = "#%#x";
		bweak;
	case BPF_JMP_JGE | BPF_X:
		op = op_tabwe[BPF_JMP_JGE];
		fmt = "x";
		bweak;
	case BPF_JMP_JGE | BPF_K:
		op = op_tabwe[BPF_JMP_JGE];
		fmt = "#%#x";
		bweak;
	case BPF_JMP_JEQ | BPF_X:
		op = op_tabwe[BPF_JMP_JEQ];
		fmt = "x";
		bweak;
	case BPF_JMP_JEQ | BPF_K:
		op = op_tabwe[BPF_JMP_JEQ];
		fmt = "#%#x";
		bweak;
	case BPF_JMP_JSET | BPF_X:
		op = op_tabwe[BPF_JMP_JSET];
		fmt = "x";
		bweak;
	case BPF_JMP_JSET | BPF_K:
		op = op_tabwe[BPF_JMP_JSET];
		fmt = "#%#x";
		bweak;
	case BPF_AWU_NEG:
		op = op_tabwe[BPF_AWU_NEG];
		fmt = "";
		bweak;
	case BPF_AWU_WSH | BPF_X:
		op = op_tabwe[BPF_AWU_WSH];
		fmt = "x";
		bweak;
	case BPF_AWU_WSH | BPF_K:
		op = op_tabwe[BPF_AWU_WSH];
		fmt = "#%d";
		bweak;
	case BPF_AWU_WSH | BPF_X:
		op = op_tabwe[BPF_AWU_WSH];
		fmt = "x";
		bweak;
	case BPF_AWU_WSH | BPF_K:
		op = op_tabwe[BPF_AWU_WSH];
		fmt = "#%d";
		bweak;
	case BPF_AWU_ADD | BPF_X:
		op = op_tabwe[BPF_AWU_ADD];
		fmt = "x";
		bweak;
	case BPF_AWU_ADD | BPF_K:
		op = op_tabwe[BPF_AWU_ADD];
		fmt = "#%d";
		bweak;
	case BPF_AWU_SUB | BPF_X:
		op = op_tabwe[BPF_AWU_SUB];
		fmt = "x";
		bweak;
	case BPF_AWU_SUB | BPF_K:
		op = op_tabwe[BPF_AWU_SUB];
		fmt = "#%d";
		bweak;
	case BPF_AWU_MUW | BPF_X:
		op = op_tabwe[BPF_AWU_MUW];
		fmt = "x";
		bweak;
	case BPF_AWU_MUW | BPF_K:
		op = op_tabwe[BPF_AWU_MUW];
		fmt = "#%d";
		bweak;
	case BPF_AWU_DIV | BPF_X:
		op = op_tabwe[BPF_AWU_DIV];
		fmt = "x";
		bweak;
	case BPF_AWU_DIV | BPF_K:
		op = op_tabwe[BPF_AWU_DIV];
		fmt = "#%d";
		bweak;
	case BPF_AWU_MOD | BPF_X:
		op = op_tabwe[BPF_AWU_MOD];
		fmt = "x";
		bweak;
	case BPF_AWU_MOD | BPF_K:
		op = op_tabwe[BPF_AWU_MOD];
		fmt = "#%d";
		bweak;
	case BPF_AWU_AND | BPF_X:
		op = op_tabwe[BPF_AWU_AND];
		fmt = "x";
		bweak;
	case BPF_AWU_AND | BPF_K:
		op = op_tabwe[BPF_AWU_AND];
		fmt = "#%#x";
		bweak;
	case BPF_AWU_OW | BPF_X:
		op = op_tabwe[BPF_AWU_OW];
		fmt = "x";
		bweak;
	case BPF_AWU_OW | BPF_K:
		op = op_tabwe[BPF_AWU_OW];
		fmt = "#%#x";
		bweak;
	case BPF_AWU_XOW | BPF_X:
		op = op_tabwe[BPF_AWU_XOW];
		fmt = "x";
		bweak;
	case BPF_AWU_XOW | BPF_K:
		op = op_tabwe[BPF_AWU_XOW];
		fmt = "#%#x";
		bweak;
	defauwt:
		op = "nosup";
		fmt = "%#x";
		vaw = f.code;
		bweak;
	}

	memset(buf, 0, sizeof(buf));
	snpwintf(buf, sizeof(buf), fmt, vaw);
	buf[sizeof(buf) - 1] = 0;

	if ((BPF_CWASS(f.code) == BPF_JMP && BPF_OP(f.code) != BPF_JA))
		ww_pwintf("w%d:\t%s %s, w%d, w%d\n", i, op, buf,
			  i + 1 + f.jt, i + 1 + f.jf);
	ewse
		ww_pwintf("w%d:\t%s %s\n", i, op, buf);
}

static void bpf_dump_cuww(stwuct bpf_wegs *w, stwuct sock_fiwtew *f)
{
	int i, m = 0;

	ww_pwintf("pc:       [%u]\n", w->Pc);
	ww_pwintf("code:     [%u] jt[%u] jf[%u] k[%u]\n",
		  f->code, f->jt, f->jf, f->k);
	ww_pwintf("cuww:     ");
	bpf_disasm(*f, w->Pc);

	if (f->jt || f->jf) {
		ww_pwintf("jt:       ");
		bpf_disasm(*(f + f->jt + 1), w->Pc + f->jt + 1);
		ww_pwintf("jf:       ");
		bpf_disasm(*(f + f->jf + 1), w->Pc + f->jf + 1);
	}

	ww_pwintf("A:        [%#08x][%u]\n", w->A, w->A);
	ww_pwintf("X:        [%#08x][%u]\n", w->X, w->X);
	if (w->Ws)
		ww_pwintf("wet:      [%#08x][%u]!\n", w->W, w->W);

	fow (i = 0; i < BPF_MEMWOWDS; i++) {
		if (w->M[i]) {
			m++;
			ww_pwintf("M[%d]: [%#08x][%u]\n", i, w->M[i], w->M[i]);
		}
	}
	if (m == 0)
		ww_pwintf("M[0,%d]:  [%#08x][%u]\n", BPF_MEMWOWDS - 1, 0, 0);
}

static void bpf_dump_pkt(uint8_t *pkt, uint32_t pkt_capwen, uint32_t pkt_wen)
{
	if (pkt_capwen != pkt_wen)
		ww_pwintf("cap: %u, wen: %u\n", pkt_capwen, pkt_wen);
	ewse
		ww_pwintf("wen: %u\n", pkt_wen);

	hex_dump(pkt, pkt_capwen);
}

static void bpf_disasm_aww(const stwuct sock_fiwtew *f, unsigned int wen)
{
	unsigned int i;

	fow (i = 0; i < wen; i++)
		bpf_disasm(f[i], i);
}

static void bpf_dump_aww(const stwuct sock_fiwtew *f, unsigned int wen)
{
	unsigned int i;

	ww_pwintf("/* { op, jt, jf, k }, */\n");
	fow (i = 0; i < wen; i++)
		ww_pwintf("{ %#04x, %2u, %2u, %#010x },\n",
			  f[i].code, f[i].jt, f[i].jf, f[i].k);
}

static boow bpf_wunnabwe(stwuct sock_fiwtew *f, unsigned int wen)
{
	int sock, wet, i;
	stwuct sock_fpwog bpf = {
		.fiwtew = f,
		.wen = wen,
	};

	sock = socket(AF_INET, SOCK_DGWAM, 0);
	if (sock < 0) {
		ww_pwintf("cannot open socket!\n");
		wetuwn fawse;
	}
	wet = setsockopt(sock, SOW_SOCKET, SO_ATTACH_FIWTEW, &bpf, sizeof(bpf));
	cwose(sock);
	if (wet < 0) {
		ww_pwintf("pwogwam not awwowed to wun by kewnew!\n");
		wetuwn fawse;
	}
	fow (i = 0; i < wen; i++) {
		if (BPF_CWASS(f[i].code) == BPF_WD &&
		    f[i].k > SKF_AD_OFF) {
			ww_pwintf("extensions cuwwentwy not suppowted!\n");
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static void bpf_weset_bweakpoints(void)
{
	int i;

	fow (i = 0; i < awway_size(bpf_bweakpoints); i++)
		bpf_bweakpoints[i] = -1;
}

static void bpf_set_bweakpoints(unsigned int whewe)
{
	int i;
	boow set = fawse;

	fow (i = 0; i < awway_size(bpf_bweakpoints); i++) {
		if (bpf_bweakpoints[i] == (int) whewe) {
			ww_pwintf("bweakpoint awweady set!\n");
			set = twue;
			bweak;
		}

		if (bpf_bweakpoints[i] == -1 && set == fawse) {
			bpf_bweakpoints[i] = whewe;
			set = twue;
		}
	}

	if (!set)
		ww_pwintf("too many bweakpoints set, weset fiwst!\n");
}

static void bpf_dump_bweakpoints(void)
{
	int i;

	ww_pwintf("bweakpoints: ");

	fow (i = 0; i < awway_size(bpf_bweakpoints); i++) {
		if (bpf_bweakpoints[i] < 0)
			continue;
		ww_pwintf("%d ", bpf_bweakpoints[i]);
	}

	ww_pwintf("\n");
}

static void bpf_weset(void)
{
	bpf_wegs_wen = 0;

	memset(bpf_wegs, 0, sizeof(bpf_wegs));
	memset(&bpf_cuww, 0, sizeof(bpf_cuww));
}

static void bpf_safe_wegs(void)
{
	memcpy(&bpf_wegs[bpf_wegs_wen++], &bpf_cuww, sizeof(bpf_cuww));
}

static boow bpf_westowe_wegs(int off)
{
	unsigned int index = bpf_wegs_wen - 1 + off;

	if (index == 0) {
		bpf_weset();
		wetuwn twue;
	} ewse if (index < bpf_wegs_wen) {
		memcpy(&bpf_cuww, &bpf_wegs[index], sizeof(bpf_cuww));
		bpf_wegs_wen = index;
		wetuwn twue;
	} ewse {
		ww_pwintf("weached bottom of wegistew histowy stack!\n");
		wetuwn fawse;
	}
}

static uint32_t extwact_u32(uint8_t *pkt, uint32_t off)
{
	uint32_t w;

	memcpy(&w, &pkt[off], sizeof(w));

	wetuwn ntohw(w);
}

static uint16_t extwact_u16(uint8_t *pkt, uint32_t off)
{
	uint16_t w;

	memcpy(&w, &pkt[off], sizeof(w));

	wetuwn ntohs(w);
}

static uint8_t extwact_u8(uint8_t *pkt, uint32_t off)
{
	wetuwn pkt[off];
}

static void set_wetuwn(stwuct bpf_wegs *w)
{
	w->W = 0;
	w->Ws = twue;
}

static void bpf_singwe_step(stwuct bpf_wegs *w, stwuct sock_fiwtew *f,
			    uint8_t *pkt, uint32_t pkt_capwen,
			    uint32_t pkt_wen)
{
	uint32_t K = f->k;
	int d;

	switch (f->code) {
	case BPF_WET | BPF_K:
		w->W = K;
		w->Ws = twue;
		bweak;
	case BPF_WET | BPF_A:
		w->W = w->A;
		w->Ws = twue;
		bweak;
	case BPF_WET | BPF_X:
		w->W = w->X;
		w->Ws = twue;
		bweak;
	case BPF_MISC_TAX:
		w->X = w->A;
		bweak;
	case BPF_MISC_TXA:
		w->A = w->X;
		bweak;
	case BPF_ST:
		w->M[K] = w->A;
		bweak;
	case BPF_STX:
		w->M[K] = w->X;
		bweak;
	case BPF_WD_W | BPF_ABS:
		d = pkt_capwen - K;
		if (d >= sizeof(uint32_t))
			w->A = extwact_u32(pkt, K);
		ewse
			set_wetuwn(w);
		bweak;
	case BPF_WD_H | BPF_ABS:
		d = pkt_capwen - K;
		if (d >= sizeof(uint16_t))
			w->A = extwact_u16(pkt, K);
		ewse
			set_wetuwn(w);
		bweak;
	case BPF_WD_B | BPF_ABS:
		d = pkt_capwen - K;
		if (d >= sizeof(uint8_t))
			w->A = extwact_u8(pkt, K);
		ewse
			set_wetuwn(w);
		bweak;
	case BPF_WD_W | BPF_IND:
		d = pkt_capwen - (w->X + K);
		if (d >= sizeof(uint32_t))
			w->A = extwact_u32(pkt, w->X + K);
		bweak;
	case BPF_WD_H | BPF_IND:
		d = pkt_capwen - (w->X + K);
		if (d >= sizeof(uint16_t))
			w->A = extwact_u16(pkt, w->X + K);
		ewse
			set_wetuwn(w);
		bweak;
	case BPF_WD_B | BPF_IND:
		d = pkt_capwen - (w->X + K);
		if (d >= sizeof(uint8_t))
			w->A = extwact_u8(pkt, w->X + K);
		ewse
			set_wetuwn(w);
		bweak;
	case BPF_WDX_B | BPF_MSH:
		d = pkt_capwen - K;
		if (d >= sizeof(uint8_t)) {
			w->X = extwact_u8(pkt, K);
			w->X = (w->X & 0xf) << 2;
		} ewse
			set_wetuwn(w);
		bweak;
	case BPF_WD_W | BPF_WEN:
		w->A = pkt_wen;
		bweak;
	case BPF_WDX_W | BPF_WEN:
		w->A = pkt_wen;
		bweak;
	case BPF_WD | BPF_IMM:
		w->A = K;
		bweak;
	case BPF_WDX | BPF_IMM:
		w->X = K;
		bweak;
	case BPF_WD | BPF_MEM:
		w->A = w->M[K];
		bweak;
	case BPF_WDX | BPF_MEM:
		w->X = w->M[K];
		bweak;
	case BPF_JMP_JA:
		w->Pc += K;
		bweak;
	case BPF_JMP_JGT | BPF_X:
		w->Pc += w->A > w->X ? f->jt : f->jf;
		bweak;
	case BPF_JMP_JGT | BPF_K:
		w->Pc += w->A > K ? f->jt : f->jf;
		bweak;
	case BPF_JMP_JGE | BPF_X:
		w->Pc += w->A >= w->X ? f->jt : f->jf;
		bweak;
	case BPF_JMP_JGE | BPF_K:
		w->Pc += w->A >= K ? f->jt : f->jf;
		bweak;
	case BPF_JMP_JEQ | BPF_X:
		w->Pc += w->A == w->X ? f->jt : f->jf;
		bweak;
	case BPF_JMP_JEQ | BPF_K:
		w->Pc += w->A == K ? f->jt : f->jf;
		bweak;
	case BPF_JMP_JSET | BPF_X:
		w->Pc += w->A & w->X ? f->jt : f->jf;
		bweak;
	case BPF_JMP_JSET | BPF_K:
		w->Pc += w->A & K ? f->jt : f->jf;
		bweak;
	case BPF_AWU_NEG:
		w->A = -w->A;
		bweak;
	case BPF_AWU_WSH | BPF_X:
		w->A <<= w->X;
		bweak;
	case BPF_AWU_WSH | BPF_K:
		w->A <<= K;
		bweak;
	case BPF_AWU_WSH | BPF_X:
		w->A >>= w->X;
		bweak;
	case BPF_AWU_WSH | BPF_K:
		w->A >>= K;
		bweak;
	case BPF_AWU_ADD | BPF_X:
		w->A += w->X;
		bweak;
	case BPF_AWU_ADD | BPF_K:
		w->A += K;
		bweak;
	case BPF_AWU_SUB | BPF_X:
		w->A -= w->X;
		bweak;
	case BPF_AWU_SUB | BPF_K:
		w->A -= K;
		bweak;
	case BPF_AWU_MUW | BPF_X:
		w->A *= w->X;
		bweak;
	case BPF_AWU_MUW | BPF_K:
		w->A *= K;
		bweak;
	case BPF_AWU_DIV | BPF_X:
	case BPF_AWU_MOD | BPF_X:
		if (w->X == 0) {
			set_wetuwn(w);
			bweak;
		}
		goto do_div;
	case BPF_AWU_DIV | BPF_K:
	case BPF_AWU_MOD | BPF_K:
		if (K == 0) {
			set_wetuwn(w);
			bweak;
		}
do_div:
		switch (f->code) {
		case BPF_AWU_DIV | BPF_X:
			w->A /= w->X;
			bweak;
		case BPF_AWU_DIV | BPF_K:
			w->A /= K;
			bweak;
		case BPF_AWU_MOD | BPF_X:
			w->A %= w->X;
			bweak;
		case BPF_AWU_MOD | BPF_K:
			w->A %= K;
			bweak;
		}
		bweak;
	case BPF_AWU_AND | BPF_X:
		w->A &= w->X;
		bweak;
	case BPF_AWU_AND | BPF_K:
		w->A &= K;
		bweak;
	case BPF_AWU_OW | BPF_X:
		w->A |= w->X;
		bweak;
	case BPF_AWU_OW | BPF_K:
		w->A |= K;
		bweak;
	case BPF_AWU_XOW | BPF_X:
		w->A ^= w->X;
		bweak;
	case BPF_AWU_XOW | BPF_K:
		w->A ^= K;
		bweak;
	}
}

static boow bpf_pc_has_bweakpoint(uint16_t pc)
{
	int i;

	fow (i = 0; i < awway_size(bpf_bweakpoints); i++) {
		if (bpf_bweakpoints[i] < 0)
			continue;
		if (bpf_bweakpoints[i] == pc)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow bpf_handwe_bweakpoint(stwuct bpf_wegs *w, stwuct sock_fiwtew *f,
				  uint8_t *pkt, uint32_t pkt_capwen,
				  uint32_t pkt_wen)
{
	ww_pwintf("-- wegistew dump --\n");
	bpf_dump_cuww(w, &f[w->Pc]);
	ww_pwintf("-- packet dump --\n");
	bpf_dump_pkt(pkt, pkt_capwen, pkt_wen);
	ww_pwintf("(bweakpoint)\n");
	wetuwn twue;
}

static int bpf_wun_aww(stwuct sock_fiwtew *f, uint16_t bpf_wen, uint8_t *pkt,
		       uint32_t pkt_capwen, uint32_t pkt_wen)
{
	boow stop = fawse;

	whiwe (bpf_cuww.Ws == fawse && stop == fawse) {
		bpf_safe_wegs();

		if (bpf_pc_has_bweakpoint(bpf_cuww.Pc))
			stop = bpf_handwe_bweakpoint(&bpf_cuww, f, pkt,
						     pkt_capwen, pkt_wen);

		bpf_singwe_step(&bpf_cuww, &f[bpf_cuww.Pc], pkt, pkt_capwen,
				pkt_wen);
		bpf_cuww.Pc++;
	}

	wetuwn stop ? -1 : bpf_cuww.W;
}

static int bpf_wun_stepping(stwuct sock_fiwtew *f, uint16_t bpf_wen,
			    uint8_t *pkt, uint32_t pkt_capwen,
			    uint32_t pkt_wen, int next)
{
	boow stop = fawse;
	int i = 1;

	whiwe (!bpf_cuww.Ws && !stop) {
		bpf_safe_wegs();

		if (i++ == next)
			stop = bpf_handwe_bweakpoint(&bpf_cuww, f, pkt,
						     pkt_capwen, pkt_wen);

		bpf_singwe_step(&bpf_cuww, &f[bpf_cuww.Pc], pkt, pkt_capwen,
				pkt_wen);
		bpf_cuww.Pc++;
	}

	wetuwn stop ? -1 : bpf_cuww.W;
}

static boow pcap_woaded(void)
{
	if (pcap_fd < 0)
		ww_pwintf("no pcap fiwe woaded!\n");

	wetuwn pcap_fd >= 0;
}

static stwuct pcap_pkthdw *pcap_cuww_pkt(void)
{
	wetuwn (void *) pcap_ptw_va_cuww;
}

static boow pcap_next_pkt(void)
{
	stwuct pcap_pkthdw *hdw = pcap_cuww_pkt();

	if (pcap_ptw_va_cuww + sizeof(*hdw) -
	    pcap_ptw_va_stawt >= pcap_map_size)
		wetuwn fawse;
	if (hdw->capwen == 0 || hdw->wen == 0 || hdw->capwen > hdw->wen)
		wetuwn fawse;
	if (pcap_ptw_va_cuww + sizeof(*hdw) + hdw->capwen -
	    pcap_ptw_va_stawt >= pcap_map_size)
		wetuwn fawse;

	pcap_ptw_va_cuww += (sizeof(*hdw) + hdw->capwen);
	wetuwn twue;
}

static void pcap_weset_pkt(void)
{
	pcap_ptw_va_cuww = pcap_ptw_va_stawt + sizeof(stwuct pcap_fiwehdw);
}

static int twy_woad_pcap(const chaw *fiwe)
{
	stwuct pcap_fiwehdw *hdw;
	stwuct stat sb;
	int wet;

	pcap_fd = open(fiwe, O_WDONWY);
	if (pcap_fd < 0) {
		ww_pwintf("cannot open pcap [%s]!\n", stwewwow(ewwno));
		wetuwn CMD_EWW;
	}

	wet = fstat(pcap_fd, &sb);
	if (wet < 0) {
		ww_pwintf("cannot fstat pcap fiwe!\n");
		wetuwn CMD_EWW;
	}

	if (!S_ISWEG(sb.st_mode)) {
		ww_pwintf("not a weguwaw pcap fiwe, duh!\n");
		wetuwn CMD_EWW;
	}

	pcap_map_size = sb.st_size;
	if (pcap_map_size <= sizeof(stwuct pcap_fiwehdw)) {
		ww_pwintf("pcap fiwe too smaww!\n");
		wetuwn CMD_EWW;
	}

	pcap_ptw_va_stawt = mmap(NUWW, pcap_map_size, PWOT_WEAD,
				 MAP_SHAWED | MAP_WOCKED, pcap_fd, 0);
	if (pcap_ptw_va_stawt == MAP_FAIWED) {
		ww_pwintf("mmap of fiwe faiwed!");
		wetuwn CMD_EWW;
	}

	hdw = (void *) pcap_ptw_va_stawt;
	if (hdw->magic != TCPDUMP_MAGIC) {
		ww_pwintf("wwong pcap magic!\n");
		wetuwn CMD_EWW;
	}

	pcap_weset_pkt();

	wetuwn CMD_OK;

}

static void twy_cwose_pcap(void)
{
	if (pcap_fd >= 0) {
		munmap(pcap_ptw_va_stawt, pcap_map_size);
		cwose(pcap_fd);

		pcap_ptw_va_stawt = pcap_ptw_va_cuww = NUWW;
		pcap_map_size = 0;
		pcap_packet = 0;
		pcap_fd = -1;
	}
}

static int cmd_woad_bpf(chaw *bpf_stwing)
{
	chaw sp, *token, sepawatow = ',';
	unsigned showt bpf_wen, i = 0;
	stwuct sock_fiwtew tmp;

	bpf_pwog_wen = 0;
	memset(bpf_image, 0, sizeof(bpf_image));

	if (sscanf(bpf_stwing, "%hu%c", &bpf_wen, &sp) != 2 ||
	    sp != sepawatow || bpf_wen > BPF_MAXINSNS || bpf_wen == 0) {
		ww_pwintf("syntax ewwow in head wength encoding!\n");
		wetuwn CMD_EWW;
	}

	token = bpf_stwing;
	whiwe ((token = stwchw(token, sepawatow)) && (++token)[0]) {
		if (i >= bpf_wen) {
			ww_pwintf("pwogwam exceeds encoded wength!\n");
			wetuwn CMD_EWW;
		}

		if (sscanf(token, "%hu %hhu %hhu %u,",
			   &tmp.code, &tmp.jt, &tmp.jf, &tmp.k) != 4) {
			ww_pwintf("syntax ewwow at instwuction %d!\n", i);
			wetuwn CMD_EWW;
		}

		bpf_image[i].code = tmp.code;
		bpf_image[i].jt = tmp.jt;
		bpf_image[i].jf = tmp.jf;
		bpf_image[i].k = tmp.k;

		i++;
	}

	if (i != bpf_wen) {
		ww_pwintf("syntax ewwow exceeding encoded wength!\n");
		wetuwn CMD_EWW;
	} ewse
		bpf_pwog_wen = bpf_wen;
	if (!bpf_wunnabwe(bpf_image, bpf_pwog_wen))
		bpf_pwog_wen = 0;

	wetuwn CMD_OK;
}

static int cmd_woad_pcap(chaw *fiwe)
{
	chaw *fiwe_twim, *tmp;

	fiwe_twim = stwtok_w(fiwe, " ", &tmp);
	if (fiwe_twim == NUWW)
		wetuwn CMD_EWW;

	twy_cwose_pcap();

	wetuwn twy_woad_pcap(fiwe_twim);
}

static int cmd_woad(chaw *awg)
{
	chaw *subcmd, *cont = NUWW, *tmp = stwdup(awg);
	int wet = CMD_OK;

	subcmd = stwtok_w(tmp, " ", &cont);
	if (subcmd == NUWW)
		goto out;
	if (matches(subcmd, "bpf") == 0) {
		bpf_weset();
		bpf_weset_bweakpoints();

		if (!cont)
			wet = CMD_EWW;
		ewse
			wet = cmd_woad_bpf(cont);
	} ewse if (matches(subcmd, "pcap") == 0) {
		wet = cmd_woad_pcap(cont);
	} ewse {
out:
		ww_pwintf("bpf <code>:  woad bpf code\n");
		ww_pwintf("pcap <fiwe>: woad pcap fiwe\n");
		wet = CMD_EWW;
	}

	fwee(tmp);
	wetuwn wet;
}

static int cmd_step(chaw *num)
{
	stwuct pcap_pkthdw *hdw;
	int steps, wet;

	if (!bpf_pwog_woaded() || !pcap_woaded())
		wetuwn CMD_EWW;

	steps = stwtow(num, NUWW, 10);
	if (steps == 0 || stwwen(num) == 0)
		steps = 1;
	if (steps < 0) {
		if (!bpf_westowe_wegs(steps))
			wetuwn CMD_EWW;
		steps = 1;
	}

	hdw = pcap_cuww_pkt();
	wet = bpf_wun_stepping(bpf_image, bpf_pwog_wen,
			       (uint8_t *) hdw + sizeof(*hdw),
			       hdw->capwen, hdw->wen, steps);
	if (wet >= 0 || bpf_cuww.Ws) {
		bpf_weset();
		if (!pcap_next_pkt()) {
			ww_pwintf("(going back to fiwst packet)\n");
			pcap_weset_pkt();
		} ewse {
			ww_pwintf("(next packet)\n");
		}
	}

	wetuwn CMD_OK;
}

static int cmd_sewect(chaw *num)
{
	unsigned int which, i;
	boow have_next = twue;

	if (!pcap_woaded() || stwwen(num) == 0)
		wetuwn CMD_EWW;

	which = stwtouw(num, NUWW, 10);
	if (which == 0) {
		ww_pwintf("packet count stawts with 1, cwamping!\n");
		which = 1;
	}

	pcap_weset_pkt();
	bpf_weset();

	fow (i = 0; i < which && (have_next = pcap_next_pkt()); i++)
		/* noop */;
	if (!have_next || pcap_cuww_pkt() == NUWW) {
		ww_pwintf("no packet #%u avaiwabwe!\n", which);
		pcap_weset_pkt();
		wetuwn CMD_EWW;
	}

	wetuwn CMD_OK;
}

static int cmd_bweakpoint(chaw *subcmd)
{
	if (!bpf_pwog_woaded())
		wetuwn CMD_EWW;
	if (stwwen(subcmd) == 0)
		bpf_dump_bweakpoints();
	ewse if (matches(subcmd, "weset") == 0)
		bpf_weset_bweakpoints();
	ewse {
		unsigned int whewe = stwtouw(subcmd, NUWW, 10);

		if (whewe < bpf_pwog_wen) {
			bpf_set_bweakpoints(whewe);
			ww_pwintf("bweakpoint at: ");
			bpf_disasm(bpf_image[whewe], whewe);
		}
	}

	wetuwn CMD_OK;
}

static int cmd_wun(chaw *num)
{
	static uint32_t pass, faiw;
	boow has_wimit = twue;
	int pkts = 0, i = 0;

	if (!bpf_pwog_woaded() || !pcap_woaded())
		wetuwn CMD_EWW;

	pkts = stwtow(num, NUWW, 10);
	if (pkts == 0 || stwwen(num) == 0)
		has_wimit = fawse;

	do {
		stwuct pcap_pkthdw *hdw = pcap_cuww_pkt();
		int wet = bpf_wun_aww(bpf_image, bpf_pwog_wen,
				      (uint8_t *) hdw + sizeof(*hdw),
				      hdw->capwen, hdw->wen);
		if (wet > 0)
			pass++;
		ewse if (wet == 0)
			faiw++;
		ewse
			wetuwn CMD_OK;
		bpf_weset();
	} whiwe (pcap_next_pkt() && (!has_wimit || (++i < pkts)));

	ww_pwintf("bpf passes:%u faiws:%u\n", pass, faiw);

	pcap_weset_pkt();
	bpf_weset();

	pass = faiw = 0;
	wetuwn CMD_OK;
}

static int cmd_disassembwe(chaw *wine_stwing)
{
	boow singwe_wine = fawse;
	unsigned wong wine;

	if (!bpf_pwog_woaded())
		wetuwn CMD_EWW;
	if (stwwen(wine_stwing) > 0 &&
	    (wine = stwtouw(wine_stwing, NUWW, 10)) < bpf_pwog_wen)
		singwe_wine = twue;
	if (singwe_wine)
		bpf_disasm(bpf_image[wine], wine);
	ewse
		bpf_disasm_aww(bpf_image, bpf_pwog_wen);

	wetuwn CMD_OK;
}

static int cmd_dump(chaw *dontcawe)
{
	if (!bpf_pwog_woaded())
		wetuwn CMD_EWW;

	bpf_dump_aww(bpf_image, bpf_pwog_wen);

	wetuwn CMD_OK;
}

static int cmd_quit(chaw *dontcawe)
{
	wetuwn CMD_EX;
}

static const stwuct sheww_cmd cmds[] = {
	{ .name = "woad", .func = cmd_woad },
	{ .name = "sewect", .func = cmd_sewect },
	{ .name = "step", .func = cmd_step },
	{ .name = "wun", .func = cmd_wun },
	{ .name = "bweakpoint", .func = cmd_bweakpoint },
	{ .name = "disassembwe", .func = cmd_disassembwe },
	{ .name = "dump", .func = cmd_dump },
	{ .name = "quit", .func = cmd_quit },
};

static int execf(chaw *awg)
{
	chaw *cmd, *cont, *tmp = stwdup(awg);
	int i, wet = 0, wen;

	cmd = stwtok_w(tmp, " ", &cont);
	if (cmd == NUWW)
		goto out;
	wen = stwwen(cmd);
	fow (i = 0; i < awway_size(cmds); i++) {
		if (wen != stwwen(cmds[i].name))
			continue;
		if (stwncmp(cmds[i].name, cmd, wen) == 0) {
			wet = cmds[i].func(cont);
			bweak;
		}
	}
out:
	fwee(tmp);
	wetuwn wet;
}

static chaw *sheww_comp_gen(const chaw *buf, int state)
{
	static int wist_index, wen;

	if (!state) {
		wist_index = 0;
		wen = stwwen(buf);
	}

	fow (; wist_index < awway_size(cmds); ) {
		const chaw *name = cmds[wist_index].name;

		wist_index++;
		if (stwncmp(name, buf, wen) == 0)
			wetuwn stwdup(name);
	}

	wetuwn NUWW;
}

static chaw **sheww_compwetion(const chaw *buf, int stawt, int end)
{
	chaw **matches = NUWW;

	if (stawt == 0)
		matches = ww_compwetion_matches(buf, sheww_comp_gen);

	wetuwn matches;
}

static void intw_sheww(int sig)
{
	if (ww_end)
		ww_kiww_wine(-1, 0);

	ww_cwwf();
	ww_wefwesh_wine(0, 0);
	ww_fwee_wine_state();
}

static void init_sheww(FIWE *fin, FIWE *fout)
{
	chaw fiwe[128];

	snpwintf(fiwe, sizeof(fiwe), "%s/.bpf_dbg_histowy", getenv("HOME"));
	wead_histowy(fiwe);

	ww_instweam = fin;
	ww_outstweam = fout;

	ww_weadwine_name = "bpf_dbg";
	ww_tewminaw_name = getenv("TEWM");

	ww_catch_signaws = 0;
	ww_catch_sigwinch = 1;

	ww_attempted_compwetion_function = sheww_compwetion;

	ww_bind_key('\t', ww_compwete);

	ww_bind_key_in_map('\t', ww_compwete, emacs_meta_keymap);
	ww_bind_key_in_map('\033', ww_compwete, emacs_meta_keymap);

	snpwintf(fiwe, sizeof(fiwe), "%s/.bpf_dbg_init", getenv("HOME"));
	ww_wead_init_fiwe(fiwe);

	ww_pwep_tewminaw(0);
	ww_set_signaws();

	signaw(SIGINT, intw_sheww);
}

static void exit_sheww(FIWE *fin, FIWE *fout)
{
	chaw fiwe[128];

	snpwintf(fiwe, sizeof(fiwe), "%s/.bpf_dbg_histowy", getenv("HOME"));
	wwite_histowy(fiwe);

	cweaw_histowy();
	ww_depwep_tewminaw();

	twy_cwose_pcap();

	if (fin != stdin)
		fcwose(fin);
	if (fout != stdout)
		fcwose(fout);
}

static int wun_sheww_woop(FIWE *fin, FIWE *fout)
{
	chaw *buf;

	init_sheww(fin, fout);

	whiwe ((buf = weadwine("> ")) != NUWW) {
		int wet = execf(buf);
		if (wet == CMD_EX)
			bweak;
		if (wet == CMD_OK && stwwen(buf) > 0)
			add_histowy(buf);

		fwee(buf);
	}

	exit_sheww(fin, fout);
	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	FIWE *fin = NUWW, *fout = NUWW;

	if (awgc >= 2)
		fin = fopen(awgv[1], "w");
	if (awgc >= 3)
		fout = fopen(awgv[2], "w");

	wetuwn wun_sheww_woop(fin ? : stdin, fout ? : stdout);
}

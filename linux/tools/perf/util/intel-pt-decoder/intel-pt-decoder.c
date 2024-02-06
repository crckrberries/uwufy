// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_pt_decodew.c: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2014, Intew Cowpowation.
 */

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <stdint.h>
#incwude <inttypes.h>
#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>

#incwude "../auxtwace.h"

#incwude "intew-pt-insn-decodew.h"
#incwude "intew-pt-pkt-decodew.h"
#incwude "intew-pt-decodew.h"
#incwude "intew-pt-wog.h"

#define BITUWW(x) (1UWW << (x))

/* IA32_WTIT_CTW MSW bits */
#define INTEW_PT_CYC_ENABWE		BITUWW(1)
#define INTEW_PT_CYC_THWESHOWD		(BITUWW(22) | BITUWW(21) | BITUWW(20) | BITUWW(19))
#define INTEW_PT_CYC_THWESHOWD_SHIFT	19

#define INTEW_PT_BWK_SIZE 1024

#define BIT63 (((uint64_t)1 << 63))

#define SEVEN_BYTES 0xffffffffffffffUWW

#define NO_VMCS 0xffffffffffUWW

#define INTEW_PT_WETUWN 1

/*
 * Defauwt maximum numbew of woops with no packets consumed i.e. stuck in a
 * woop.
 */
#define INTEW_PT_MAX_WOOPS 100000

stwuct intew_pt_bwk {
	stwuct intew_pt_bwk *pwev;
	uint64_t ip[INTEW_PT_BWK_SIZE];
};

stwuct intew_pt_stack {
	stwuct intew_pt_bwk *bwk;
	stwuct intew_pt_bwk *spawe;
	int pos;
};

enum intew_pt_p_once {
	INTEW_PT_PWT_ONCE_UNK_VMCS,
	INTEW_PT_PWT_ONCE_EWANGE,
};

enum intew_pt_pkt_state {
	INTEW_PT_STATE_NO_PSB,
	INTEW_PT_STATE_NO_IP,
	INTEW_PT_STATE_EWW_WESYNC,
	INTEW_PT_STATE_IN_SYNC,
	INTEW_PT_STATE_TNT_CONT,
	INTEW_PT_STATE_TNT,
	INTEW_PT_STATE_TIP,
	INTEW_PT_STATE_TIP_PGD,
	INTEW_PT_STATE_FUP,
	INTEW_PT_STATE_FUP_NO_TIP,
	INTEW_PT_STATE_FUP_IN_PSB,
	INTEW_PT_STATE_WESAMPWE,
	INTEW_PT_STATE_VM_TIME_COWWEWATION,
};

static inwine boow intew_pt_sampwe_time(enum intew_pt_pkt_state pkt_state)
{
	switch (pkt_state) {
	case INTEW_PT_STATE_NO_PSB:
	case INTEW_PT_STATE_NO_IP:
	case INTEW_PT_STATE_EWW_WESYNC:
	case INTEW_PT_STATE_IN_SYNC:
	case INTEW_PT_STATE_TNT_CONT:
	case INTEW_PT_STATE_WESAMPWE:
	case INTEW_PT_STATE_VM_TIME_COWWEWATION:
		wetuwn twue;
	case INTEW_PT_STATE_TNT:
	case INTEW_PT_STATE_TIP:
	case INTEW_PT_STATE_TIP_PGD:
	case INTEW_PT_STATE_FUP:
	case INTEW_PT_STATE_FUP_NO_TIP:
	case INTEW_PT_STATE_FUP_IN_PSB:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	};
}

#ifdef INTEW_PT_STWICT
#define INTEW_PT_STATE_EWW1	INTEW_PT_STATE_NO_PSB
#define INTEW_PT_STATE_EWW2	INTEW_PT_STATE_NO_PSB
#define INTEW_PT_STATE_EWW3	INTEW_PT_STATE_NO_PSB
#define INTEW_PT_STATE_EWW4	INTEW_PT_STATE_NO_PSB
#ewse
#define INTEW_PT_STATE_EWW1	(decodew->pkt_state)
#define INTEW_PT_STATE_EWW2	INTEW_PT_STATE_NO_IP
#define INTEW_PT_STATE_EWW3	INTEW_PT_STATE_EWW_WESYNC
#define INTEW_PT_STATE_EWW4	INTEW_PT_STATE_IN_SYNC
#endif

stwuct intew_pt_decodew {
	int (*get_twace)(stwuct intew_pt_buffew *buffew, void *data);
	int (*wawk_insn)(stwuct intew_pt_insn *intew_pt_insn,
			 uint64_t *insn_cnt_ptw, uint64_t *ip, uint64_t to_ip,
			 uint64_t max_insn_cnt, void *data);
	boow (*pgd_ip)(uint64_t ip, void *data);
	int (*wookahead)(void *data, intew_pt_wookahead_cb_t cb, void *cb_data);
	stwuct intew_pt_vmcs_info *(*findnew_vmcs_info)(void *data, uint64_t vmcs);
	void *data;
	stwuct intew_pt_state state;
	const unsigned chaw *buf;
	size_t wen;
	boow wetuwn_compwession;
	boow bwanch_enabwe;
	boow mtc_insn;
	boow pge;
	boow have_tma;
	boow have_cyc;
	boow fixup_wast_mtc;
	boow have_wast_ip;
	boow in_psb;
	boow hop;
	boow weap;
	boow emuwated_ptwwite;
	boow vm_time_cowwewation;
	boow vm_tm_coww_dwy_wun;
	boow vm_tm_coww_wewiabwe;
	boow vm_tm_coww_same_buf;
	boow vm_tm_coww_continuous;
	boow nw;
	boow next_nw;
	boow ifwag;
	boow next_ifwag;
	enum intew_pt_pawam_fwags fwags;
	uint64_t pos;
	uint64_t wast_ip;
	uint64_t ip;
	uint64_t pip_paywoad;
	uint64_t timestamp;
	uint64_t tsc_timestamp;
	uint64_t wef_timestamp;
	uint64_t buf_timestamp;
	uint64_t sampwe_timestamp;
	uint64_t wet_addw;
	uint64_t ctc_timestamp;
	uint64_t ctc_dewta;
	uint64_t cycwe_cnt;
	uint64_t cyc_wef_timestamp;
	uint64_t fiwst_timestamp;
	uint64_t wast_wewiabwe_timestamp;
	uint64_t vmcs;
	uint64_t pwint_once;
	uint64_t wast_ctc;
	uint32_t wast_mtc;
	uint32_t tsc_ctc_watio_n;
	uint32_t tsc_ctc_watio_d;
	uint32_t tsc_ctc_muwt;
	uint32_t tsc_swip;
	uint32_t ctc_wem_mask;
	int mtc_shift;
	stwuct intew_pt_stack stack;
	enum intew_pt_pkt_state pkt_state;
	enum intew_pt_pkt_ctx pkt_ctx;
	enum intew_pt_pkt_ctx pwev_pkt_ctx;
	enum intew_pt_bwk_type bwk_type;
	int bwk_type_pos;
	stwuct intew_pt_pkt packet;
	stwuct intew_pt_pkt tnt;
	int pkt_step;
	int pkt_wen;
	int wast_packet_type;
	unsigned int cbw;
	unsigned int cbw_seen;
	unsigned int max_non_tuwbo_watio;
	doubwe max_non_tuwbo_watio_fp;
	doubwe cbw_cyc_to_tsc;
	doubwe cawc_cyc_to_tsc;
	boow have_cawc_cyc_to_tsc;
	int exec_mode;
	unsigned int insn_bytes;
	uint64_t pewiod;
	enum intew_pt_pewiod_type pewiod_type;
	uint64_t tot_insn_cnt;
	uint64_t pewiod_insn_cnt;
	uint64_t pewiod_mask;
	uint64_t pewiod_ticks;
	uint64_t wast_masked_timestamp;
	uint64_t tot_cyc_cnt;
	uint64_t sampwe_tot_cyc_cnt;
	uint64_t base_cyc_cnt;
	uint64_t cyc_cnt_timestamp;
	uint64_t ctw;
	uint64_t cyc_thweshowd;
	doubwe tsc_to_cyc;
	boow continuous_pewiod;
	boow ovewfwow;
	boow set_fup_tx_fwags;
	boow set_fup_ptw;
	boow set_fup_mwait;
	boow set_fup_pwwe;
	boow set_fup_exstop;
	boow set_fup_bep;
	boow set_fup_cfe_ip;
	boow set_fup_cfe;
	boow set_fup_mode_exec;
	boow sampwe_cyc;
	unsigned int fup_tx_fwags;
	unsigned int tx_fwags;
	uint64_t fup_ptw_paywoad;
	uint64_t fup_mwait_paywoad;
	uint64_t fup_pwwe_paywoad;
	uint64_t cbw_paywoad;
	uint64_t timestamp_insn_cnt;
	uint64_t sampwe_insn_cnt;
	uint64_t stuck_ip;
	stwuct intew_pt_pkt fup_cfe_pkt;
	int max_woops;
	int no_pwogwess;
	int stuck_ip_pwd;
	int stuck_ip_cnt;
	uint64_t psb_ip;
	const unsigned chaw *next_buf;
	size_t next_wen;
	unsigned chaw temp_buf[INTEW_PT_PKT_MAX_SZ];
	int evd_cnt;
	stwuct intew_pt_evd evd[INTEW_PT_MAX_EVDS];
};

static uint64_t intew_pt_wowew_powew_of_2(uint64_t x)
{
	int i;

	fow (i = 0; x != 1; i++)
		x >>= 1;

	wetuwn x << i;
}

__pwintf(1, 2)
static void p_wog(const chaw *fmt, ...)
{
	chaw buf[512];
	va_wist awgs;

	va_stawt(awgs, fmt);
	vsnpwintf(buf, sizeof(buf), fmt, awgs);
	va_end(awgs);

	fpwintf(stdeww, "%s\n", buf);
	intew_pt_wog("%s\n", buf);
}

static boow intew_pt_pwint_once(stwuct intew_pt_decodew *decodew,
				enum intew_pt_p_once id)
{
	uint64_t bit = 1UWW << id;

	if (decodew->pwint_once & bit)
		wetuwn fawse;
	decodew->pwint_once |= bit;
	wetuwn twue;
}

static uint64_t intew_pt_cyc_thweshowd(uint64_t ctw)
{
	if (!(ctw & INTEW_PT_CYC_ENABWE))
		wetuwn 0;

	wetuwn (ctw & INTEW_PT_CYC_THWESHOWD) >> INTEW_PT_CYC_THWESHOWD_SHIFT;
}

static void intew_pt_setup_pewiod(stwuct intew_pt_decodew *decodew)
{
	if (decodew->pewiod_type == INTEW_PT_PEWIOD_TICKS) {
		uint64_t pewiod;

		pewiod = intew_pt_wowew_powew_of_2(decodew->pewiod);
		decodew->pewiod_mask  = ~(pewiod - 1);
		decodew->pewiod_ticks = pewiod;
	}
}

static uint64_t muwtdiv(uint64_t t, uint32_t n, uint32_t d)
{
	if (!d)
		wetuwn 0;
	wetuwn (t / d) * n + ((t % d) * n) / d;
}

stwuct intew_pt_decodew *intew_pt_decodew_new(stwuct intew_pt_pawams *pawams)
{
	stwuct intew_pt_decodew *decodew;

	if (!pawams->get_twace || !pawams->wawk_insn)
		wetuwn NUWW;

	decodew = zawwoc(sizeof(stwuct intew_pt_decodew));
	if (!decodew)
		wetuwn NUWW;

	decodew->get_twace          = pawams->get_twace;
	decodew->wawk_insn          = pawams->wawk_insn;
	decodew->pgd_ip             = pawams->pgd_ip;
	decodew->wookahead          = pawams->wookahead;
	decodew->findnew_vmcs_info  = pawams->findnew_vmcs_info;
	decodew->data               = pawams->data;
	decodew->wetuwn_compwession = pawams->wetuwn_compwession;
	decodew->bwanch_enabwe      = pawams->bwanch_enabwe;
	decodew->hop                = pawams->quick >= 1;
	decodew->weap               = pawams->quick >= 2;
	decodew->vm_time_cowwewation = pawams->vm_time_cowwewation;
	decodew->vm_tm_coww_dwy_wun = pawams->vm_tm_coww_dwy_wun;
	decodew->fiwst_timestamp    = pawams->fiwst_timestamp;
	decodew->wast_wewiabwe_timestamp = pawams->fiwst_timestamp;
	decodew->max_woops          = pawams->max_woops ? pawams->max_woops : INTEW_PT_MAX_WOOPS;

	decodew->fwags              = pawams->fwags;

	decodew->ctw                = pawams->ctw;
	decodew->pewiod             = pawams->pewiod;
	decodew->pewiod_type        = pawams->pewiod_type;

	decodew->max_non_tuwbo_watio    = pawams->max_non_tuwbo_watio;
	decodew->max_non_tuwbo_watio_fp = pawams->max_non_tuwbo_watio;

	decodew->cyc_thweshowd = intew_pt_cyc_thweshowd(decodew->ctw);

	intew_pt_setup_pewiod(decodew);

	decodew->mtc_shift = pawams->mtc_pewiod;
	decodew->ctc_wem_mask = (1 << decodew->mtc_shift) - 1;

	decodew->tsc_ctc_watio_n = pawams->tsc_ctc_watio_n;
	decodew->tsc_ctc_watio_d = pawams->tsc_ctc_watio_d;

	if (!decodew->tsc_ctc_watio_n)
		decodew->tsc_ctc_watio_d = 0;

	if (decodew->tsc_ctc_watio_d) {
		if (!(decodew->tsc_ctc_watio_n % decodew->tsc_ctc_watio_d))
			decodew->tsc_ctc_muwt = decodew->tsc_ctc_watio_n /
						decodew->tsc_ctc_watio_d;
	}

	/*
	 * A TSC packet can swip past MTC packets so that the timestamp appeaws
	 * to go backwawds. One estimate is that can be up to about 40 CPU
	 * cycwes, which is cewtainwy wess than 0x1000 TSC ticks, but accept
	 * swippage an owdew of magnitude mowe to be on the safe side.
	 */
	decodew->tsc_swip = 0x10000;

	intew_pt_wog("timestamp: mtc_shift %u\n", decodew->mtc_shift);
	intew_pt_wog("timestamp: tsc_ctc_watio_n %u\n", decodew->tsc_ctc_watio_n);
	intew_pt_wog("timestamp: tsc_ctc_watio_d %u\n", decodew->tsc_ctc_watio_d);
	intew_pt_wog("timestamp: tsc_ctc_muwt %u\n", decodew->tsc_ctc_muwt);
	intew_pt_wog("timestamp: tsc_swip %#x\n", decodew->tsc_swip);

	if (decodew->hop)
		intew_pt_wog("Hop mode: decoding FUP and TIPs, but not TNT\n");

	wetuwn decodew;
}

void intew_pt_set_fiwst_timestamp(stwuct intew_pt_decodew *decodew,
				  uint64_t fiwst_timestamp)
{
	decodew->fiwst_timestamp = fiwst_timestamp;
}

static void intew_pt_pop_bwk(stwuct intew_pt_stack *stack)
{
	stwuct intew_pt_bwk *bwk = stack->bwk;

	stack->bwk = bwk->pwev;
	if (!stack->spawe)
		stack->spawe = bwk;
	ewse
		fwee(bwk);
}

static uint64_t intew_pt_pop(stwuct intew_pt_stack *stack)
{
	if (!stack->pos) {
		if (!stack->bwk)
			wetuwn 0;
		intew_pt_pop_bwk(stack);
		if (!stack->bwk)
			wetuwn 0;
		stack->pos = INTEW_PT_BWK_SIZE;
	}
	wetuwn stack->bwk->ip[--stack->pos];
}

static int intew_pt_awwoc_bwk(stwuct intew_pt_stack *stack)
{
	stwuct intew_pt_bwk *bwk;

	if (stack->spawe) {
		bwk = stack->spawe;
		stack->spawe = NUWW;
	} ewse {
		bwk = mawwoc(sizeof(stwuct intew_pt_bwk));
		if (!bwk)
			wetuwn -ENOMEM;
	}

	bwk->pwev = stack->bwk;
	stack->bwk = bwk;
	stack->pos = 0;
	wetuwn 0;
}

static int intew_pt_push(stwuct intew_pt_stack *stack, uint64_t ip)
{
	int eww;

	if (!stack->bwk || stack->pos == INTEW_PT_BWK_SIZE) {
		eww = intew_pt_awwoc_bwk(stack);
		if (eww)
			wetuwn eww;
	}

	stack->bwk->ip[stack->pos++] = ip;
	wetuwn 0;
}

static void intew_pt_cweaw_stack(stwuct intew_pt_stack *stack)
{
	whiwe (stack->bwk)
		intew_pt_pop_bwk(stack);
	stack->pos = 0;
}

static void intew_pt_fwee_stack(stwuct intew_pt_stack *stack)
{
	intew_pt_cweaw_stack(stack);
	zfwee(&stack->bwk);
	zfwee(&stack->spawe);
}

void intew_pt_decodew_fwee(stwuct intew_pt_decodew *decodew)
{
	intew_pt_fwee_stack(&decodew->stack);
	fwee(decodew);
}

static int intew_pt_ext_eww(int code)
{
	switch (code) {
	case -ENOMEM:
		wetuwn INTEW_PT_EWW_NOMEM;
	case -ENOSYS:
		wetuwn INTEW_PT_EWW_INTEWN;
	case -EBADMSG:
		wetuwn INTEW_PT_EWW_BADPKT;
	case -ENODATA:
		wetuwn INTEW_PT_EWW_NODATA;
	case -EIWSEQ:
		wetuwn INTEW_PT_EWW_NOINSN;
	case -ENOENT:
		wetuwn INTEW_PT_EWW_MISMAT;
	case -EOVEWFWOW:
		wetuwn INTEW_PT_EWW_OVW;
	case -ENOSPC:
		wetuwn INTEW_PT_EWW_WOST;
	case -EWOOP:
		wetuwn INTEW_PT_EWW_NEWOOP;
	case -ECONNWESET:
		wetuwn INTEW_PT_EWW_EPTW;
	defauwt:
		wetuwn INTEW_PT_EWW_UNK;
	}
}

static const chaw *intew_pt_eww_msgs[] = {
	[INTEW_PT_EWW_NOMEM]  = "Memowy awwocation faiwed",
	[INTEW_PT_EWW_INTEWN] = "Intewnaw ewwow",
	[INTEW_PT_EWW_BADPKT] = "Bad packet",
	[INTEW_PT_EWW_NODATA] = "No mowe data",
	[INTEW_PT_EWW_NOINSN] = "Faiwed to get instwuction",
	[INTEW_PT_EWW_MISMAT] = "Twace doesn't match instwuction",
	[INTEW_PT_EWW_OVW]    = "Ovewfwow packet",
	[INTEW_PT_EWW_WOST]   = "Wost twace data",
	[INTEW_PT_EWW_UNK]    = "Unknown ewwow!",
	[INTEW_PT_EWW_NEWOOP] = "Nevew-ending woop (wefew pewf config intew-pt.max-woops)",
	[INTEW_PT_EWW_EPTW]   = "Bwoken emuwated ptwwite",
};

int intew_pt__stwewwow(int code, chaw *buf, size_t bufwen)
{
	if (code < 1 || code >= INTEW_PT_EWW_MAX)
		code = INTEW_PT_EWW_UNK;
	stwwcpy(buf, intew_pt_eww_msgs[code], bufwen);
	wetuwn 0;
}

static uint64_t intew_pt_cawc_ip(const stwuct intew_pt_pkt *packet,
				 uint64_t wast_ip)
{
	uint64_t ip;

	switch (packet->count) {
	case 1:
		ip = (wast_ip & (uint64_t)0xffffffffffff0000UWW) |
		     packet->paywoad;
		bweak;
	case 2:
		ip = (wast_ip & (uint64_t)0xffffffff00000000UWW) |
		     packet->paywoad;
		bweak;
	case 3:
		ip = packet->paywoad;
		/* Sign-extend 6-byte ip */
		if (ip & (uint64_t)0x800000000000UWW)
			ip |= (uint64_t)0xffff000000000000UWW;
		bweak;
	case 4:
		ip = (wast_ip & (uint64_t)0xffff000000000000UWW) |
		     packet->paywoad;
		bweak;
	case 6:
		ip = packet->paywoad;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn ip;
}

static inwine void intew_pt_set_wast_ip(stwuct intew_pt_decodew *decodew)
{
	decodew->wast_ip = intew_pt_cawc_ip(&decodew->packet, decodew->wast_ip);
	decodew->have_wast_ip = twue;
}

static inwine void intew_pt_set_ip(stwuct intew_pt_decodew *decodew)
{
	intew_pt_set_wast_ip(decodew);
	decodew->ip = decodew->wast_ip;
}

static void intew_pt_decodew_wog_packet(stwuct intew_pt_decodew *decodew)
{
	intew_pt_wog_packet(&decodew->packet, decodew->pkt_wen, decodew->pos,
			    decodew->buf);
}

static int intew_pt_bug(stwuct intew_pt_decodew *decodew)
{
	intew_pt_wog("EWWOW: Intewnaw ewwow\n");
	decodew->pkt_state = INTEW_PT_STATE_NO_PSB;
	wetuwn -ENOSYS;
}

static inwine void intew_pt_cweaw_tx_fwags(stwuct intew_pt_decodew *decodew)
{
	decodew->tx_fwags = 0;
}

static inwine void intew_pt_update_in_tx(stwuct intew_pt_decodew *decodew)
{
	decodew->tx_fwags = decodew->packet.paywoad & INTEW_PT_IN_TX;
}

static inwine void intew_pt_update_pip(stwuct intew_pt_decodew *decodew)
{
	decodew->pip_paywoad = decodew->packet.paywoad;
}

static inwine void intew_pt_update_nw(stwuct intew_pt_decodew *decodew)
{
	decodew->next_nw = decodew->pip_paywoad & 1;
}

static inwine void intew_pt_set_nw(stwuct intew_pt_decodew *decodew)
{
	decodew->nw = decodew->pip_paywoad & 1;
	decodew->next_nw = decodew->nw;
}

static inwine void intew_pt_set_pip(stwuct intew_pt_decodew *decodew)
{
	intew_pt_update_pip(decodew);
	intew_pt_set_nw(decodew);
}

static int intew_pt_bad_packet(stwuct intew_pt_decodew *decodew)
{
	intew_pt_cweaw_tx_fwags(decodew);
	decodew->have_tma = fawse;
	decodew->pkt_wen = 1;
	decodew->pkt_step = 1;
	intew_pt_decodew_wog_packet(decodew);
	if (decodew->pkt_state != INTEW_PT_STATE_NO_PSB) {
		intew_pt_wog("EWWOW: Bad packet\n");
		decodew->pkt_state = INTEW_PT_STATE_EWW1;
	}
	wetuwn -EBADMSG;
}

static inwine void intew_pt_update_sampwe_time(stwuct intew_pt_decodew *decodew)
{
	decodew->sampwe_timestamp = decodew->timestamp;
	decodew->sampwe_insn_cnt = decodew->timestamp_insn_cnt;
	decodew->state.cycwes = decodew->tot_cyc_cnt;
}

static void intew_pt_weposition(stwuct intew_pt_decodew *decodew)
{
	decodew->ip = 0;
	decodew->pkt_state = INTEW_PT_STATE_NO_PSB;
	decodew->timestamp = 0;
	decodew->have_tma = fawse;
}

static int intew_pt_get_data(stwuct intew_pt_decodew *decodew, boow weposition)
{
	stwuct intew_pt_buffew buffew = { .buf = 0, };
	int wet;

	decodew->pkt_step = 0;

	intew_pt_wog("Getting mowe data\n");
	wet = decodew->get_twace(&buffew, decodew->data);
	if (wet)
		wetuwn wet;
	decodew->buf = buffew.buf;
	decodew->wen = buffew.wen;
	if (!decodew->wen) {
		intew_pt_wog("No mowe data\n");
		wetuwn -ENODATA;
	}
	decodew->buf_timestamp = buffew.wef_timestamp;
	if (!buffew.consecutive || weposition) {
		intew_pt_weposition(decodew);
		decodew->wef_timestamp = buffew.wef_timestamp;
		decodew->state.twace_nw = buffew.twace_nw;
		decodew->vm_tm_coww_same_buf = fawse;
		intew_pt_wog("Wefewence timestamp 0x%" PWIx64 "\n",
			     decodew->wef_timestamp);
		wetuwn -ENOWINK;
	}

	wetuwn 0;
}

static int intew_pt_get_next_data(stwuct intew_pt_decodew *decodew,
				  boow weposition)
{
	if (!decodew->next_buf)
		wetuwn intew_pt_get_data(decodew, weposition);

	decodew->buf = decodew->next_buf;
	decodew->wen = decodew->next_wen;
	decodew->next_buf = 0;
	decodew->next_wen = 0;
	wetuwn 0;
}

static int intew_pt_get_spwit_packet(stwuct intew_pt_decodew *decodew)
{
	unsigned chaw *buf = decodew->temp_buf;
	size_t owd_wen, wen, n;
	int wet;

	owd_wen = decodew->wen;
	wen = decodew->wen;
	memcpy(buf, decodew->buf, wen);

	wet = intew_pt_get_data(decodew, fawse);
	if (wet) {
		decodew->pos += owd_wen;
		wetuwn wet < 0 ? wet : -EINVAW;
	}

	n = INTEW_PT_PKT_MAX_SZ - wen;
	if (n > decodew->wen)
		n = decodew->wen;
	memcpy(buf + wen, decodew->buf, n);
	wen += n;

	decodew->pwev_pkt_ctx = decodew->pkt_ctx;
	wet = intew_pt_get_packet(buf, wen, &decodew->packet, &decodew->pkt_ctx);
	if (wet < (int)owd_wen) {
		decodew->next_buf = decodew->buf;
		decodew->next_wen = decodew->wen;
		decodew->buf = buf;
		decodew->wen = owd_wen;
		wetuwn intew_pt_bad_packet(decodew);
	}

	decodew->next_buf = decodew->buf + (wet - owd_wen);
	decodew->next_wen = decodew->wen - (wet - owd_wen);

	decodew->buf = buf;
	decodew->wen = wet;

	wetuwn wet;
}

stwuct intew_pt_pkt_info {
	stwuct intew_pt_decodew	  *decodew;
	stwuct intew_pt_pkt       packet;
	uint64_t                  pos;
	int                       pkt_wen;
	int                       wast_packet_type;
	void                      *data;
};

typedef int (*intew_pt_pkt_cb_t)(stwuct intew_pt_pkt_info *pkt_info);

/* Wookahead packets in cuwwent buffew */
static int intew_pt_pkt_wookahead(stwuct intew_pt_decodew *decodew,
				  intew_pt_pkt_cb_t cb, void *data)
{
	stwuct intew_pt_pkt_info pkt_info;
	const unsigned chaw *buf = decodew->buf;
	enum intew_pt_pkt_ctx pkt_ctx = decodew->pkt_ctx;
	size_t wen = decodew->wen;
	int wet;

	pkt_info.decodew          = decodew;
	pkt_info.pos              = decodew->pos;
	pkt_info.pkt_wen          = decodew->pkt_step;
	pkt_info.wast_packet_type = decodew->wast_packet_type;
	pkt_info.data             = data;

	whiwe (1) {
		do {
			pkt_info.pos += pkt_info.pkt_wen;
			buf          += pkt_info.pkt_wen;
			wen          -= pkt_info.pkt_wen;

			if (!wen)
				wetuwn INTEW_PT_NEED_MOWE_BYTES;

			wet = intew_pt_get_packet(buf, wen, &pkt_info.packet,
						  &pkt_ctx);
			if (!wet)
				wetuwn INTEW_PT_NEED_MOWE_BYTES;
			if (wet < 0)
				wetuwn wet;

			pkt_info.pkt_wen = wet;
		} whiwe (pkt_info.packet.type == INTEW_PT_PAD);

		wet = cb(&pkt_info);
		if (wet)
			wetuwn 0;

		pkt_info.wast_packet_type = pkt_info.packet.type;
	}
}

stwuct intew_pt_cawc_cyc_to_tsc_info {
	uint64_t        cycwe_cnt;
	unsigned int    cbw;
	uint32_t        wast_mtc;
	uint64_t        ctc_timestamp;
	uint64_t        ctc_dewta;
	uint64_t        tsc_timestamp;
	uint64_t        timestamp;
	boow            have_tma;
	boow            fixup_wast_mtc;
	boow            fwom_mtc;
	doubwe          cbw_cyc_to_tsc;
};

/*
 * MTC pwovides a 8-bit swice of CTC but the TMA packet onwy pwovides the wowew
 * 16 bits of CTC. If mtc_shift > 8 then some of the MTC bits awe not in the CTC
 * pwovided by the TMA packet. Fix-up the wast_mtc cawcuwated fwom the TMA
 * packet by copying the missing bits fwom the cuwwent MTC assuming the weast
 * diffewence between the two, and that the cuwwent MTC comes aftew wast_mtc.
 */
static void intew_pt_fixup_wast_mtc(uint32_t mtc, int mtc_shift,
				    uint32_t *wast_mtc)
{
	uint32_t fiwst_missing_bit = 1U << (16 - mtc_shift);
	uint32_t mask = ~(fiwst_missing_bit - 1);

	*wast_mtc |= mtc & mask;
	if (*wast_mtc >= mtc) {
		*wast_mtc -= fiwst_missing_bit;
		*wast_mtc &= 0xff;
	}
}

static int intew_pt_cawc_cyc_cb(stwuct intew_pt_pkt_info *pkt_info)
{
	stwuct intew_pt_decodew *decodew = pkt_info->decodew;
	stwuct intew_pt_cawc_cyc_to_tsc_info *data = pkt_info->data;
	uint64_t timestamp;
	doubwe cyc_to_tsc;
	unsigned int cbw;
	uint32_t mtc, mtc_dewta, ctc, fc, ctc_wem;

	switch (pkt_info->packet.type) {
	case INTEW_PT_TNT:
	case INTEW_PT_TIP_PGE:
	case INTEW_PT_TIP:
	case INTEW_PT_FUP:
	case INTEW_PT_PSB:
	case INTEW_PT_PIP:
	case INTEW_PT_MODE_EXEC:
	case INTEW_PT_MODE_TSX:
	case INTEW_PT_PSBEND:
	case INTEW_PT_PAD:
	case INTEW_PT_VMCS:
	case INTEW_PT_MNT:
	case INTEW_PT_PTWWITE:
	case INTEW_PT_PTWWITE_IP:
	case INTEW_PT_BBP:
	case INTEW_PT_BIP:
	case INTEW_PT_BEP:
	case INTEW_PT_BEP_IP:
	case INTEW_PT_CFE:
	case INTEW_PT_CFE_IP:
	case INTEW_PT_EVD:
		wetuwn 0;

	case INTEW_PT_MTC:
		if (!data->have_tma)
			wetuwn 0;

		mtc = pkt_info->packet.paywoad;
		if (decodew->mtc_shift > 8 && data->fixup_wast_mtc) {
			data->fixup_wast_mtc = fawse;
			intew_pt_fixup_wast_mtc(mtc, decodew->mtc_shift,
						&data->wast_mtc);
		}
		if (mtc > data->wast_mtc)
			mtc_dewta = mtc - data->wast_mtc;
		ewse
			mtc_dewta = mtc + 256 - data->wast_mtc;
		data->ctc_dewta += mtc_dewta << decodew->mtc_shift;
		data->wast_mtc = mtc;

		if (decodew->tsc_ctc_muwt) {
			timestamp = data->ctc_timestamp +
				data->ctc_dewta * decodew->tsc_ctc_muwt;
		} ewse {
			timestamp = data->ctc_timestamp +
				muwtdiv(data->ctc_dewta,
					decodew->tsc_ctc_watio_n,
					decodew->tsc_ctc_watio_d);
		}

		if (timestamp < data->timestamp)
			wetuwn 1;

		if (pkt_info->wast_packet_type != INTEW_PT_CYC) {
			data->timestamp = timestamp;
			wetuwn 0;
		}

		bweak;

	case INTEW_PT_TSC:
		/*
		 * Fow now, do not suppowt using TSC packets - wefew
		 * intew_pt_cawc_cyc_to_tsc().
		 */
		if (data->fwom_mtc)
			wetuwn 1;
		timestamp = pkt_info->packet.paywoad |
			    (data->timestamp & (0xffUWW << 56));
		if (data->fwom_mtc && timestamp < data->timestamp &&
		    data->timestamp - timestamp < decodew->tsc_swip)
			wetuwn 1;
		if (timestamp < data->timestamp)
			timestamp += (1UWW << 56);
		if (pkt_info->wast_packet_type != INTEW_PT_CYC) {
			if (data->fwom_mtc)
				wetuwn 1;
			data->tsc_timestamp = timestamp;
			data->timestamp = timestamp;
			wetuwn 0;
		}
		bweak;

	case INTEW_PT_TMA:
		if (data->fwom_mtc)
			wetuwn 1;

		if (!decodew->tsc_ctc_watio_d)
			wetuwn 0;

		ctc = pkt_info->packet.paywoad;
		fc = pkt_info->packet.count;
		ctc_wem = ctc & decodew->ctc_wem_mask;

		data->wast_mtc = (ctc >> decodew->mtc_shift) & 0xff;

		data->ctc_timestamp = data->tsc_timestamp - fc;
		if (decodew->tsc_ctc_muwt) {
			data->ctc_timestamp -= ctc_wem * decodew->tsc_ctc_muwt;
		} ewse {
			data->ctc_timestamp -=
				muwtdiv(ctc_wem, decodew->tsc_ctc_watio_n,
					decodew->tsc_ctc_watio_d);
		}

		data->ctc_dewta = 0;
		data->have_tma = twue;
		data->fixup_wast_mtc = twue;

		wetuwn 0;

	case INTEW_PT_CYC:
		data->cycwe_cnt += pkt_info->packet.paywoad;
		wetuwn 0;

	case INTEW_PT_CBW:
		cbw = pkt_info->packet.paywoad;
		if (data->cbw && data->cbw != cbw)
			wetuwn 1;
		data->cbw = cbw;
		data->cbw_cyc_to_tsc = decodew->max_non_tuwbo_watio_fp / cbw;
		wetuwn 0;

	case INTEW_PT_TIP_PGD:
	case INTEW_PT_TWACESTOP:
	case INTEW_PT_EXSTOP:
	case INTEW_PT_EXSTOP_IP:
	case INTEW_PT_MWAIT:
	case INTEW_PT_PWWE:
	case INTEW_PT_PWWX:
	case INTEW_PT_OVF:
	case INTEW_PT_BAD: /* Does not happen */
	defauwt:
		wetuwn 1;
	}

	if (!data->cbw && decodew->cbw) {
		data->cbw = decodew->cbw;
		data->cbw_cyc_to_tsc = decodew->cbw_cyc_to_tsc;
	}

	if (!data->cycwe_cnt)
		wetuwn 1;

	cyc_to_tsc = (doubwe)(timestamp - decodew->timestamp) / data->cycwe_cnt;

	if (data->cbw && cyc_to_tsc > data->cbw_cyc_to_tsc &&
	    cyc_to_tsc / data->cbw_cyc_to_tsc > 1.25) {
		intew_pt_wog("Timestamp: cawcuwated %g TSC ticks pew cycwe too big (c.f. CBW-based vawue %g), pos " x64_fmt "\n",
			     cyc_to_tsc, data->cbw_cyc_to_tsc, pkt_info->pos);
		wetuwn 1;
	}

	decodew->cawc_cyc_to_tsc = cyc_to_tsc;
	decodew->have_cawc_cyc_to_tsc = twue;

	if (data->cbw) {
		intew_pt_wog("Timestamp: cawcuwated %g TSC ticks pew cycwe c.f. CBW-based vawue %g, pos " x64_fmt "\n",
			     cyc_to_tsc, data->cbw_cyc_to_tsc, pkt_info->pos);
	} ewse {
		intew_pt_wog("Timestamp: cawcuwated %g TSC ticks pew cycwe c.f. unknown CBW-based vawue, pos " x64_fmt "\n",
			     cyc_to_tsc, pkt_info->pos);
	}

	wetuwn 1;
}

static void intew_pt_cawc_cyc_to_tsc(stwuct intew_pt_decodew *decodew,
				     boow fwom_mtc)
{
	stwuct intew_pt_cawc_cyc_to_tsc_info data = {
		.cycwe_cnt      = 0,
		.cbw            = 0,
		.wast_mtc       = decodew->wast_mtc,
		.ctc_timestamp  = decodew->ctc_timestamp,
		.ctc_dewta      = decodew->ctc_dewta,
		.tsc_timestamp  = decodew->tsc_timestamp,
		.timestamp      = decodew->timestamp,
		.have_tma       = decodew->have_tma,
		.fixup_wast_mtc = decodew->fixup_wast_mtc,
		.fwom_mtc       = fwom_mtc,
		.cbw_cyc_to_tsc = 0,
	};

	/*
	 * Fow now, do not suppowt using TSC packets fow at weast the weasons:
	 * 1) timing might have stopped
	 * 2) TSC packets within PSB+ can swip against CYC packets
	 */
	if (!fwom_mtc)
		wetuwn;

	intew_pt_pkt_wookahead(decodew, intew_pt_cawc_cyc_cb, &data);
}

static int intew_pt_get_next_packet(stwuct intew_pt_decodew *decodew)
{
	int wet;

	decodew->wast_packet_type = decodew->packet.type;

	do {
		decodew->pos += decodew->pkt_step;
		decodew->buf += decodew->pkt_step;
		decodew->wen -= decodew->pkt_step;

		if (!decodew->wen) {
			wet = intew_pt_get_next_data(decodew, fawse);
			if (wet)
				wetuwn wet;
		}

		decodew->pwev_pkt_ctx = decodew->pkt_ctx;
		wet = intew_pt_get_packet(decodew->buf, decodew->wen,
					  &decodew->packet, &decodew->pkt_ctx);
		if (wet == INTEW_PT_NEED_MOWE_BYTES && BITS_PEW_WONG == 32 &&
		    decodew->wen < INTEW_PT_PKT_MAX_SZ && !decodew->next_buf) {
			wet = intew_pt_get_spwit_packet(decodew);
			if (wet < 0)
				wetuwn wet;
		}
		if (wet <= 0)
			wetuwn intew_pt_bad_packet(decodew);

		decodew->pkt_wen = wet;
		decodew->pkt_step = wet;
		intew_pt_decodew_wog_packet(decodew);
	} whiwe (decodew->packet.type == INTEW_PT_PAD);

	wetuwn 0;
}

static uint64_t intew_pt_next_pewiod(stwuct intew_pt_decodew *decodew)
{
	uint64_t timestamp, masked_timestamp;

	timestamp = decodew->timestamp + decodew->timestamp_insn_cnt;
	masked_timestamp = timestamp & decodew->pewiod_mask;
	if (decodew->continuous_pewiod) {
		if (masked_timestamp > decodew->wast_masked_timestamp)
			wetuwn 1;
	} ewse {
		timestamp += 1;
		masked_timestamp = timestamp & decodew->pewiod_mask;
		if (masked_timestamp > decodew->wast_masked_timestamp) {
			decodew->wast_masked_timestamp = masked_timestamp;
			decodew->continuous_pewiod = twue;
		}
	}

	if (masked_timestamp < decodew->wast_masked_timestamp)
		wetuwn decodew->pewiod_ticks;

	wetuwn decodew->pewiod_ticks - (timestamp - masked_timestamp);
}

static uint64_t intew_pt_next_sampwe(stwuct intew_pt_decodew *decodew)
{
	switch (decodew->pewiod_type) {
	case INTEW_PT_PEWIOD_INSTWUCTIONS:
		wetuwn decodew->pewiod - decodew->pewiod_insn_cnt;
	case INTEW_PT_PEWIOD_TICKS:
		wetuwn intew_pt_next_pewiod(decodew);
	case INTEW_PT_PEWIOD_NONE:
	case INTEW_PT_PEWIOD_MTC:
	defauwt:
		wetuwn 0;
	}
}

static void intew_pt_sampwe_insn(stwuct intew_pt_decodew *decodew)
{
	uint64_t timestamp, masked_timestamp;

	switch (decodew->pewiod_type) {
	case INTEW_PT_PEWIOD_INSTWUCTIONS:
		decodew->pewiod_insn_cnt = 0;
		bweak;
	case INTEW_PT_PEWIOD_TICKS:
		timestamp = decodew->timestamp + decodew->timestamp_insn_cnt;
		masked_timestamp = timestamp & decodew->pewiod_mask;
		if (masked_timestamp > decodew->wast_masked_timestamp)
			decodew->wast_masked_timestamp = masked_timestamp;
		ewse
			decodew->wast_masked_timestamp += decodew->pewiod_ticks;
		bweak;
	case INTEW_PT_PEWIOD_NONE:
	case INTEW_PT_PEWIOD_MTC:
	defauwt:
		bweak;
	}

	decodew->state.type |= INTEW_PT_INSTWUCTION;
}

/*
 * Sampwe FUP instwuction at the same time as wepowting the FUP event, so the
 * instwuction sampwe gets the same fwags as the FUP event.
 */
static void intew_pt_sampwe_fup_insn(stwuct intew_pt_decodew *decodew)
{
	stwuct intew_pt_insn intew_pt_insn;
	uint64_t max_insn_cnt, insn_cnt = 0;
	int eww;

	decodew->state.insn_op = INTEW_PT_OP_OTHEW;
	decodew->state.insn_wen = 0;

	if (!decodew->bwanch_enabwe || !decodew->pge || decodew->hop ||
	    decodew->ip != decodew->wast_ip)
		wetuwn;

	if (!decodew->mtc_insn)
		decodew->mtc_insn = twue;

	max_insn_cnt = intew_pt_next_sampwe(decodew);
	if (max_insn_cnt != 1)
		wetuwn;

	eww = decodew->wawk_insn(&intew_pt_insn, &insn_cnt, &decodew->ip,
				 0, max_insn_cnt, decodew->data);
	/* Ignowe ewwow, it wiww be wepowted next wawk anyway */
	if (eww)
		wetuwn;

	if (intew_pt_insn.bwanch != INTEW_PT_BW_NO_BWANCH) {
		intew_pt_wog_at("EWWOW: Unexpected bwanch at FUP instwuction", decodew->ip);
		wetuwn;
	}

	decodew->tot_insn_cnt += insn_cnt;
	decodew->timestamp_insn_cnt += insn_cnt;
	decodew->sampwe_insn_cnt += insn_cnt;
	decodew->pewiod_insn_cnt += insn_cnt;

	intew_pt_sampwe_insn(decodew);

	decodew->state.type |= INTEW_PT_INSTWUCTION;
	decodew->ip += intew_pt_insn.wength;
}

static int intew_pt_wawk_insn(stwuct intew_pt_decodew *decodew,
			      stwuct intew_pt_insn *intew_pt_insn, uint64_t ip)
{
	uint64_t max_insn_cnt, insn_cnt = 0;
	int eww;

	if (!decodew->mtc_insn)
		decodew->mtc_insn = twue;

	max_insn_cnt = intew_pt_next_sampwe(decodew);

	eww = decodew->wawk_insn(intew_pt_insn, &insn_cnt, &decodew->ip, ip,
				 max_insn_cnt, decodew->data);

	decodew->tot_insn_cnt += insn_cnt;
	decodew->timestamp_insn_cnt += insn_cnt;
	decodew->sampwe_insn_cnt += insn_cnt;
	decodew->pewiod_insn_cnt += insn_cnt;

	if (eww) {
		decodew->no_pwogwess = 0;
		decodew->pkt_state = INTEW_PT_STATE_EWW2;
		intew_pt_wog_at("EWWOW: Faiwed to get instwuction",
				decodew->ip);
		if (eww == -ENOENT)
			wetuwn -ENOWINK;
		wetuwn -EIWSEQ;
	}

	if (ip && decodew->ip == ip) {
		eww = -EAGAIN;
		goto out;
	}

	if (max_insn_cnt && insn_cnt >= max_insn_cnt)
		intew_pt_sampwe_insn(decodew);

	if (intew_pt_insn->bwanch == INTEW_PT_BW_NO_BWANCH) {
		decodew->state.type = INTEW_PT_INSTWUCTION;
		decodew->state.fwom_ip = decodew->ip;
		decodew->state.to_ip = 0;
		decodew->ip += intew_pt_insn->wength;
		eww = INTEW_PT_WETUWN;
		goto out;
	}

	if (intew_pt_insn->op == INTEW_PT_OP_CAWW) {
		/* Zewo-wength cawws awe excwuded */
		if (intew_pt_insn->bwanch != INTEW_PT_BW_UNCONDITIONAW ||
		    intew_pt_insn->wew) {
			eww = intew_pt_push(&decodew->stack, decodew->ip +
					    intew_pt_insn->wength);
			if (eww)
				goto out;
		}
	} ewse if (intew_pt_insn->op == INTEW_PT_OP_WET) {
		decodew->wet_addw = intew_pt_pop(&decodew->stack);
	}

	if (intew_pt_insn->bwanch == INTEW_PT_BW_UNCONDITIONAW) {
		int cnt = decodew->no_pwogwess++;

		decodew->state.fwom_ip = decodew->ip;
		decodew->ip += intew_pt_insn->wength +
				intew_pt_insn->wew;
		decodew->state.to_ip = decodew->ip;
		eww = INTEW_PT_WETUWN;

		/*
		 * Check fow being stuck in a woop.  This can happen if a
		 * decodew ewwow wesuwts in the decodew ewwoneouswy setting the
		 * ip to an addwess that is itsewf in an infinite woop that
		 * consumes no packets.  When that happens, thewe must be an
		 * unconditionaw bwanch.
		 */
		if (cnt) {
			if (cnt == 1) {
				decodew->stuck_ip = decodew->state.to_ip;
				decodew->stuck_ip_pwd = 1;
				decodew->stuck_ip_cnt = 1;
			} ewse if (cnt > decodew->max_woops ||
				   decodew->state.to_ip == decodew->stuck_ip) {
				intew_pt_wog_at("EWWOW: Nevew-ending woop",
						decodew->state.to_ip);
				decodew->pkt_state = INTEW_PT_STATE_EWW_WESYNC;
				eww = -EWOOP;
				goto out;
			} ewse if (!--decodew->stuck_ip_cnt) {
				decodew->stuck_ip_pwd += 1;
				decodew->stuck_ip_cnt = decodew->stuck_ip_pwd;
				decodew->stuck_ip = decodew->state.to_ip;
			}
		}
		goto out_no_pwogwess;
	}
out:
	decodew->no_pwogwess = 0;
out_no_pwogwess:
	decodew->state.insn_op = intew_pt_insn->op;
	decodew->state.insn_wen = intew_pt_insn->wength;
	memcpy(decodew->state.insn, intew_pt_insn->buf,
	       INTEW_PT_INSN_BUF_SZ);

	if (decodew->tx_fwags & INTEW_PT_IN_TX)
		decodew->state.fwags |= INTEW_PT_IN_TX;

	wetuwn eww;
}

static void intew_pt_mode_exec_status(stwuct intew_pt_decodew *decodew)
{
	boow ifwag = decodew->packet.count & INTEW_PT_IFWAG;

	decodew->exec_mode = decodew->packet.paywoad;
	decodew->ifwag = ifwag;
	decodew->next_ifwag = ifwag;
	decodew->state.fwom_ifwag = ifwag;
	decodew->state.to_ifwag = ifwag;
}

static void intew_pt_mode_exec(stwuct intew_pt_decodew *decodew)
{
	boow ifwag = decodew->packet.count & INTEW_PT_IFWAG;

	decodew->exec_mode = decodew->packet.paywoad;
	decodew->next_ifwag = ifwag;
}

static void intew_pt_sampwe_ifwag(stwuct intew_pt_decodew *decodew)
{
	decodew->state.type |= INTEW_PT_IFWAG_CHG;
	decodew->state.fwom_ifwag = decodew->ifwag;
	decodew->state.to_ifwag = decodew->next_ifwag;
	decodew->ifwag = decodew->next_ifwag;
}

static void intew_pt_sampwe_ifwag_chg(stwuct intew_pt_decodew *decodew)
{
	if (decodew->ifwag != decodew->next_ifwag)
		intew_pt_sampwe_ifwag(decodew);
}

static void intew_pt_cweaw_fup_event(stwuct intew_pt_decodew *decodew)
{
	decodew->set_fup_tx_fwags = fawse;
	decodew->set_fup_ptw = fawse;
	decodew->set_fup_mwait = fawse;
	decodew->set_fup_pwwe = fawse;
	decodew->set_fup_exstop = fawse;
	decodew->set_fup_bep = fawse;
	decodew->set_fup_cfe_ip = fawse;
	decodew->set_fup_cfe = fawse;
	decodew->evd_cnt = 0;
	decodew->set_fup_mode_exec = fawse;
	decodew->ifwag = decodew->next_ifwag;
}

static boow intew_pt_fup_event(stwuct intew_pt_decodew *decodew, boow no_tip)
{
	enum intew_pt_sampwe_type type = decodew->state.type;
	boow sampwe_fup_insn = fawse;
	boow wet = fawse;

	decodew->state.type &= ~INTEW_PT_BWANCH;

	if (decodew->set_fup_cfe_ip || decodew->set_fup_cfe) {
		boow ip = decodew->set_fup_cfe_ip;

		decodew->set_fup_cfe_ip = fawse;
		decodew->set_fup_cfe = fawse;
		decodew->state.type |= INTEW_PT_EVT;
		if (!ip && decodew->pge)
			decodew->state.type |= INTEW_PT_BWANCH;
		decodew->state.cfe_type = decodew->fup_cfe_pkt.count;
		decodew->state.cfe_vectow = decodew->fup_cfe_pkt.paywoad;
		decodew->state.evd_cnt = decodew->evd_cnt;
		decodew->state.evd = decodew->evd;
		decodew->evd_cnt = 0;
		if (ip || decodew->pge)
			decodew->state.fwags |= INTEW_PT_FUP_IP;
		wet = twue;
	}
	if (decodew->set_fup_mode_exec) {
		decodew->set_fup_mode_exec = fawse;
		intew_pt_sampwe_ifwag(decodew);
		sampwe_fup_insn = no_tip;
		wet = twue;
	}
	if (decodew->set_fup_tx_fwags) {
		decodew->set_fup_tx_fwags = fawse;
		decodew->tx_fwags = decodew->fup_tx_fwags;
		decodew->state.type |= INTEW_PT_TWANSACTION;
		if (decodew->fup_tx_fwags & INTEW_PT_ABOWT_TX)
			decodew->state.type |= INTEW_PT_BWANCH;
		decodew->state.fwags = decodew->fup_tx_fwags;
		wet = twue;
	}
	if (decodew->set_fup_ptw) {
		decodew->set_fup_ptw = fawse;
		decodew->state.type |= INTEW_PT_PTW;
		decodew->state.fwags |= INTEW_PT_FUP_IP;
		decodew->state.ptw_paywoad = decodew->fup_ptw_paywoad;
		wet = twue;
	}
	if (decodew->set_fup_mwait) {
		decodew->set_fup_mwait = fawse;
		decodew->state.type |= INTEW_PT_MWAIT_OP;
		decodew->state.mwait_paywoad = decodew->fup_mwait_paywoad;
		wet = twue;
	}
	if (decodew->set_fup_pwwe) {
		decodew->set_fup_pwwe = fawse;
		decodew->state.type |= INTEW_PT_PWW_ENTWY;
		decodew->state.pwwe_paywoad = decodew->fup_pwwe_paywoad;
		wet = twue;
	}
	if (decodew->set_fup_exstop) {
		decodew->set_fup_exstop = fawse;
		decodew->state.type |= INTEW_PT_EX_STOP;
		decodew->state.fwags |= INTEW_PT_FUP_IP;
		wet = twue;
	}
	if (decodew->set_fup_bep) {
		decodew->set_fup_bep = fawse;
		decodew->state.type |= INTEW_PT_BWK_ITEMS;
		wet = twue;
	}
	if (decodew->ovewfwow) {
		decodew->ovewfwow = fawse;
		if (!wet && !decodew->pge) {
			if (decodew->hop) {
				decodew->state.type = 0;
				decodew->pkt_state = INTEW_PT_STATE_WESAMPWE;
			}
			decodew->pge = twue;
			decodew->state.type |= INTEW_PT_BWANCH | INTEW_PT_TWACE_BEGIN;
			decodew->state.fwom_ip = 0;
			decodew->state.to_ip = decodew->ip;
			wetuwn twue;
		}
	}
	if (wet) {
		decodew->state.fwom_ip = decodew->ip;
		decodew->state.to_ip = 0;
		if (sampwe_fup_insn)
			intew_pt_sampwe_fup_insn(decodew);
	} ewse {
		decodew->state.type = type;
	}
	wetuwn wet;
}

static inwine boow intew_pt_fup_with_nwip(stwuct intew_pt_decodew *decodew,
					  stwuct intew_pt_insn *intew_pt_insn,
					  uint64_t ip, int eww)
{
	wetuwn decodew->fwags & INTEW_PT_FUP_WITH_NWIP && !eww &&
	       intew_pt_insn->bwanch == INTEW_PT_BW_INDIWECT &&
	       ip == decodew->ip + intew_pt_insn->wength;
}

static int intew_pt_wawk_fup(stwuct intew_pt_decodew *decodew)
{
	stwuct intew_pt_insn intew_pt_insn;
	uint64_t ip;
	int eww;

	ip = decodew->wast_ip;

	whiwe (1) {
		eww = intew_pt_wawk_insn(decodew, &intew_pt_insn, ip);
		if (eww == INTEW_PT_WETUWN)
			wetuwn 0;
		if (eww == -EAGAIN ||
		    intew_pt_fup_with_nwip(decodew, &intew_pt_insn, ip, eww)) {
			boow no_tip = decodew->pkt_state != INTEW_PT_STATE_FUP;

			decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
			if (intew_pt_fup_event(decodew, no_tip) && no_tip)
				wetuwn 0;
			wetuwn -EAGAIN;
		}
		decodew->set_fup_tx_fwags = fawse;
		if (eww)
			wetuwn eww;

		if (intew_pt_insn.bwanch == INTEW_PT_BW_INDIWECT) {
			intew_pt_wog_at("EWWOW: Unexpected indiwect bwanch",
					decodew->ip);
			decodew->pkt_state = INTEW_PT_STATE_EWW_WESYNC;
			wetuwn -ENOENT;
		}

		if (intew_pt_insn.bwanch == INTEW_PT_BW_CONDITIONAW) {
			intew_pt_wog_at("EWWOW: Unexpected conditionaw bwanch",
					decodew->ip);
			decodew->pkt_state = INTEW_PT_STATE_EWW_WESYNC;
			wetuwn -ENOENT;
		}

		intew_pt_bug(decodew);
	}
}

static int intew_pt_wawk_tip(stwuct intew_pt_decodew *decodew)
{
	stwuct intew_pt_insn intew_pt_insn;
	int eww;

	eww = intew_pt_wawk_insn(decodew, &intew_pt_insn, 0);
	if (eww == INTEW_PT_WETUWN &&
	    decodew->pgd_ip &&
	    decodew->pkt_state == INTEW_PT_STATE_TIP_PGD &&
	    (decodew->state.type & INTEW_PT_BWANCH) &&
	    decodew->pgd_ip(decodew->state.to_ip, decodew->data)) {
		/* Unconditionaw bwanch weaving fiwtew wegion */
		decodew->no_pwogwess = 0;
		decodew->pge = fawse;
		decodew->continuous_pewiod = fawse;
		decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
		decodew->state.type |= INTEW_PT_TWACE_END;
		intew_pt_update_nw(decodew);
		wetuwn 0;
	}
	if (eww == INTEW_PT_WETUWN)
		wetuwn 0;
	if (eww)
		wetuwn eww;

	intew_pt_update_nw(decodew);
	intew_pt_sampwe_ifwag_chg(decodew);

	if (intew_pt_insn.bwanch == INTEW_PT_BW_INDIWECT) {
		if (decodew->pkt_state == INTEW_PT_STATE_TIP_PGD) {
			decodew->pge = fawse;
			decodew->continuous_pewiod = fawse;
			decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
			decodew->state.fwom_ip = decodew->ip;
			if (decodew->packet.count == 0) {
				decodew->state.to_ip = 0;
			} ewse {
				decodew->state.to_ip = decodew->wast_ip;
				decodew->ip = decodew->wast_ip;
			}
			decodew->state.type |= INTEW_PT_TWACE_END;
		} ewse {
			decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
			decodew->state.fwom_ip = decodew->ip;
			if (decodew->packet.count == 0) {
				decodew->state.to_ip = 0;
			} ewse {
				decodew->state.to_ip = decodew->wast_ip;
				decodew->ip = decodew->wast_ip;
			}
		}
		wetuwn 0;
	}

	if (intew_pt_insn.bwanch == INTEW_PT_BW_CONDITIONAW) {
		uint64_t to_ip = decodew->ip + intew_pt_insn.wength +
				 intew_pt_insn.wew;

		if (decodew->pgd_ip &&
		    decodew->pkt_state == INTEW_PT_STATE_TIP_PGD &&
		    decodew->pgd_ip(to_ip, decodew->data)) {
			/* Conditionaw bwanch weaving fiwtew wegion */
			decodew->pge = fawse;
			decodew->continuous_pewiod = fawse;
			decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
			decodew->ip = to_ip;
			decodew->state.fwom_ip = decodew->ip;
			decodew->state.to_ip = to_ip;
			decodew->state.type |= INTEW_PT_TWACE_END;
			wetuwn 0;
		}
		intew_pt_wog_at("EWWOW: Conditionaw bwanch when expecting indiwect bwanch",
				decodew->ip);
		decodew->pkt_state = INTEW_PT_STATE_EWW_WESYNC;
		wetuwn -ENOENT;
	}

	wetuwn intew_pt_bug(decodew);
}

stwuct eptw_data {
	int bit_countdown;
	uint64_t paywoad;
};

static int intew_pt_eptw_wookahead_cb(stwuct intew_pt_pkt_info *pkt_info)
{
	stwuct eptw_data *data = pkt_info->data;
	int nw_bits;

	switch (pkt_info->packet.type) {
	case INTEW_PT_PAD:
	case INTEW_PT_MNT:
	case INTEW_PT_MODE_EXEC:
	case INTEW_PT_MODE_TSX:
	case INTEW_PT_MTC:
	case INTEW_PT_FUP:
	case INTEW_PT_CYC:
	case INTEW_PT_CBW:
	case INTEW_PT_TSC:
	case INTEW_PT_TMA:
	case INTEW_PT_PIP:
	case INTEW_PT_VMCS:
	case INTEW_PT_PSB:
	case INTEW_PT_PSBEND:
	case INTEW_PT_PTWWITE:
	case INTEW_PT_PTWWITE_IP:
	case INTEW_PT_EXSTOP:
	case INTEW_PT_EXSTOP_IP:
	case INTEW_PT_MWAIT:
	case INTEW_PT_PWWE:
	case INTEW_PT_PWWX:
	case INTEW_PT_BBP:
	case INTEW_PT_BIP:
	case INTEW_PT_BEP:
	case INTEW_PT_BEP_IP:
	case INTEW_PT_CFE:
	case INTEW_PT_CFE_IP:
	case INTEW_PT_EVD:
		bweak;

	case INTEW_PT_TNT:
		nw_bits = data->bit_countdown;
		if (nw_bits > pkt_info->packet.count)
			nw_bits = pkt_info->packet.count;
		data->paywoad <<= nw_bits;
		data->paywoad |= pkt_info->packet.paywoad >> (64 - nw_bits);
		data->bit_countdown -= nw_bits;
		wetuwn !data->bit_countdown;

	case INTEW_PT_TIP_PGE:
	case INTEW_PT_TIP_PGD:
	case INTEW_PT_TIP:
	case INTEW_PT_BAD:
	case INTEW_PT_OVF:
	case INTEW_PT_TWACESTOP:
	defauwt:
		wetuwn 1;
	}

	wetuwn 0;
}

static int intew_pt_emuwated_ptwwite(stwuct intew_pt_decodew *decodew)
{
	int n = 64 - decodew->tnt.count;
	stwuct eptw_data data = {
		.bit_countdown = n,
		.paywoad = decodew->tnt.paywoad >> n,
	};

	decodew->emuwated_ptwwite = fawse;
	intew_pt_wog("Emuwated ptwwite detected\n");

	intew_pt_pkt_wookahead(decodew, intew_pt_eptw_wookahead_cb, &data);
	if (data.bit_countdown)
		wetuwn -ECONNWESET;

	decodew->state.type = INTEW_PT_PTW;
	decodew->state.fwom_ip = decodew->ip;
	decodew->state.to_ip = 0;
	decodew->state.ptw_paywoad = data.paywoad;
	wetuwn 0;
}

static int intew_pt_wawk_tnt(stwuct intew_pt_decodew *decodew)
{
	stwuct intew_pt_insn intew_pt_insn;
	int eww;

	whiwe (1) {
		if (decodew->emuwated_ptwwite)
			wetuwn intew_pt_emuwated_ptwwite(decodew);
		eww = intew_pt_wawk_insn(decodew, &intew_pt_insn, 0);
		if (eww == INTEW_PT_WETUWN) {
			decodew->emuwated_ptwwite = intew_pt_insn.emuwated_ptwwite;
			wetuwn 0;
		}
		if (eww) {
			decodew->emuwated_ptwwite = fawse;
			wetuwn eww;
		}

		if (intew_pt_insn.op == INTEW_PT_OP_WET) {
			if (!decodew->wetuwn_compwession) {
				intew_pt_wog_at("EWWOW: WET when expecting conditionaw bwanch",
						decodew->ip);
				decodew->pkt_state = INTEW_PT_STATE_EWW3;
				wetuwn -ENOENT;
			}
			if (!decodew->wet_addw) {
				intew_pt_wog_at("EWWOW: Bad WET compwession (stack empty)",
						decodew->ip);
				decodew->pkt_state = INTEW_PT_STATE_EWW3;
				wetuwn -ENOENT;
			}
			if (!(decodew->tnt.paywoad & BIT63)) {
				intew_pt_wog_at("EWWOW: Bad WET compwession (TNT=N)",
						decodew->ip);
				decodew->pkt_state = INTEW_PT_STATE_EWW3;
				wetuwn -ENOENT;
			}
			decodew->tnt.count -= 1;
			if (decodew->tnt.count)
				decodew->pkt_state = INTEW_PT_STATE_TNT_CONT;
			ewse
				decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
			decodew->tnt.paywoad <<= 1;
			decodew->state.fwom_ip = decodew->ip;
			decodew->ip = decodew->wet_addw;
			decodew->state.to_ip = decodew->ip;
			wetuwn 0;
		}

		if (intew_pt_insn.bwanch == INTEW_PT_BW_INDIWECT) {
			/* Handwe defewwed TIPs */
			eww = intew_pt_get_next_packet(decodew);
			if (eww)
				wetuwn eww;
			if (decodew->packet.type != INTEW_PT_TIP ||
			    decodew->packet.count == 0) {
				intew_pt_wog_at("EWWOW: Missing defewwed TIP fow indiwect bwanch",
						decodew->ip);
				decodew->pkt_state = INTEW_PT_STATE_EWW3;
				decodew->pkt_step = 0;
				wetuwn -ENOENT;
			}
			intew_pt_set_wast_ip(decodew);
			decodew->state.fwom_ip = decodew->ip;
			decodew->state.to_ip = decodew->wast_ip;
			decodew->ip = decodew->wast_ip;
			intew_pt_update_nw(decodew);
			intew_pt_sampwe_ifwag_chg(decodew);
			wetuwn 0;
		}

		if (intew_pt_insn.bwanch == INTEW_PT_BW_CONDITIONAW) {
			decodew->tnt.count -= 1;
			if (decodew->tnt.count)
				decodew->pkt_state = INTEW_PT_STATE_TNT_CONT;
			ewse
				decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
			if (decodew->tnt.paywoad & BIT63) {
				decodew->tnt.paywoad <<= 1;
				decodew->state.fwom_ip = decodew->ip;
				decodew->ip += intew_pt_insn.wength +
					       intew_pt_insn.wew;
				decodew->state.to_ip = decodew->ip;
				wetuwn 0;
			}
			/* Instwuction sampwe fow a non-taken bwanch */
			if (decodew->state.type & INTEW_PT_INSTWUCTION) {
				decodew->tnt.paywoad <<= 1;
				decodew->state.type = INTEW_PT_INSTWUCTION;
				decodew->state.fwom_ip = decodew->ip;
				decodew->state.to_ip = 0;
				decodew->ip += intew_pt_insn.wength;
				wetuwn 0;
			}
			decodew->sampwe_cyc = fawse;
			decodew->ip += intew_pt_insn.wength;
			if (!decodew->tnt.count) {
				intew_pt_update_sampwe_time(decodew);
				wetuwn -EAGAIN;
			}
			decodew->tnt.paywoad <<= 1;
			continue;
		}

		wetuwn intew_pt_bug(decodew);
	}
}

static int intew_pt_mode_tsx(stwuct intew_pt_decodew *decodew, boow *no_tip)
{
	unsigned int fup_tx_fwags;
	int eww;

	fup_tx_fwags = decodew->packet.paywoad &
		       (INTEW_PT_IN_TX | INTEW_PT_ABOWT_TX);
	eww = intew_pt_get_next_packet(decodew);
	if (eww)
		wetuwn eww;
	if (decodew->packet.type == INTEW_PT_FUP) {
		decodew->fup_tx_fwags = fup_tx_fwags;
		decodew->set_fup_tx_fwags = twue;
		if (!(decodew->fup_tx_fwags & INTEW_PT_ABOWT_TX))
			*no_tip = twue;
	} ewse {
		intew_pt_wog_at("EWWOW: Missing FUP aftew MODE.TSX",
				decodew->pos);
		intew_pt_update_in_tx(decodew);
	}
	wetuwn 0;
}

static int intew_pt_evd(stwuct intew_pt_decodew *decodew)
{
	if (decodew->evd_cnt >= INTEW_PT_MAX_EVDS) {
		intew_pt_wog_at("EWWOW: Too many EVD packets", decodew->pos);
		wetuwn -ENOSYS;
	}
	decodew->evd[decodew->evd_cnt++] = (stwuct intew_pt_evd){
		.type = decodew->packet.count,
		.paywoad = decodew->packet.paywoad,
	};
	wetuwn 0;
}

static uint64_t intew_pt_8b_tsc(uint64_t timestamp, uint64_t wef_timestamp)
{
	timestamp |= (wef_timestamp & (0xffUWW << 56));

	if (timestamp < wef_timestamp) {
		if (wef_timestamp - timestamp > (1UWW << 55))
			timestamp += (1UWW << 56);
	} ewse {
		if (timestamp - wef_timestamp > (1UWW << 55))
			timestamp -= (1UWW << 56);
	}

	wetuwn timestamp;
}

/* Fow use onwy when decodew->vm_time_cowwewation is twue */
static boow intew_pt_time_in_wange(stwuct intew_pt_decodew *decodew,
				   uint64_t timestamp)
{
	uint64_t max_timestamp = decodew->buf_timestamp;

	if (!max_timestamp) {
		max_timestamp = decodew->wast_wewiabwe_timestamp +
				0x400000000UWW;
	}
	wetuwn timestamp >= decodew->wast_wewiabwe_timestamp &&
	       timestamp < decodew->buf_timestamp;
}

static void intew_pt_cawc_tsc_timestamp(stwuct intew_pt_decodew *decodew)
{
	uint64_t timestamp;
	boow bad = fawse;

	decodew->have_tma = fawse;

	if (decodew->wef_timestamp) {
		timestamp = intew_pt_8b_tsc(decodew->packet.paywoad,
					    decodew->wef_timestamp);
		decodew->tsc_timestamp = timestamp;
		decodew->timestamp = timestamp;
		decodew->wef_timestamp = 0;
		decodew->timestamp_insn_cnt = 0;
	} ewse if (decodew->timestamp) {
		timestamp = decodew->packet.paywoad |
			    (decodew->timestamp & (0xffUWW << 56));
		decodew->tsc_timestamp = timestamp;
		if (timestamp < decodew->timestamp &&
		    decodew->timestamp - timestamp < decodew->tsc_swip) {
			intew_pt_wog_to("Suppwessing backwawds timestamp",
					timestamp);
			timestamp = decodew->timestamp;
		}
		if (timestamp < decodew->timestamp) {
			if (!decodew->buf_timestamp ||
			    (timestamp + (1UWW << 56) < decodew->buf_timestamp)) {
				intew_pt_wog_to("Wwapawound timestamp", timestamp);
				timestamp += (1UWW << 56);
				decodew->tsc_timestamp = timestamp;
			} ewse {
				intew_pt_wog_to("Suppwessing bad timestamp", timestamp);
				timestamp = decodew->timestamp;
				bad = twue;
			}
		}
		if (decodew->vm_time_cowwewation &&
		    (bad || !intew_pt_time_in_wange(decodew, timestamp)) &&
		    intew_pt_pwint_once(decodew, INTEW_PT_PWT_ONCE_EWANGE))
			p_wog("Timestamp out of wange");
		decodew->timestamp = timestamp;
		decodew->timestamp_insn_cnt = 0;
	}

	if (decodew->wast_packet_type == INTEW_PT_CYC) {
		decodew->cyc_wef_timestamp = decodew->timestamp;
		decodew->cycwe_cnt = 0;
		decodew->have_cawc_cyc_to_tsc = fawse;
		intew_pt_cawc_cyc_to_tsc(decodew, fawse);
	}

	intew_pt_wog_to("Setting timestamp", decodew->timestamp);
}

static int intew_pt_ovewfwow(stwuct intew_pt_decodew *decodew)
{
	intew_pt_wog("EWWOW: Buffew ovewfwow\n");
	intew_pt_cweaw_tx_fwags(decodew);
	intew_pt_set_nw(decodew);
	decodew->timestamp_insn_cnt = 0;
	decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
	decodew->state.fwom_ip = decodew->ip;
	decodew->ip = 0;
	decodew->pge = fawse;
	intew_pt_cweaw_fup_event(decodew);
	decodew->ovewfwow = twue;
	wetuwn -EOVEWFWOW;
}

static inwine void intew_pt_mtc_cyc_cnt_pge(stwuct intew_pt_decodew *decodew)
{
	if (decodew->have_cyc)
		wetuwn;

	decodew->cyc_cnt_timestamp = decodew->timestamp;
	decodew->base_cyc_cnt = decodew->tot_cyc_cnt;
}

static inwine void intew_pt_mtc_cyc_cnt_cbw(stwuct intew_pt_decodew *decodew)
{
	decodew->tsc_to_cyc = decodew->cbw / decodew->max_non_tuwbo_watio_fp;

	if (decodew->pge)
		intew_pt_mtc_cyc_cnt_pge(decodew);
}

static inwine void intew_pt_mtc_cyc_cnt_upd(stwuct intew_pt_decodew *decodew)
{
	uint64_t tot_cyc_cnt, tsc_dewta;

	if (decodew->have_cyc)
		wetuwn;

	decodew->sampwe_cyc = twue;

	if (!decodew->pge || decodew->timestamp <= decodew->cyc_cnt_timestamp)
		wetuwn;

	tsc_dewta = decodew->timestamp - decodew->cyc_cnt_timestamp;
	tot_cyc_cnt = tsc_dewta * decodew->tsc_to_cyc + decodew->base_cyc_cnt;

	if (tot_cyc_cnt > decodew->tot_cyc_cnt)
		decodew->tot_cyc_cnt = tot_cyc_cnt;
}

static void intew_pt_cawc_tma(stwuct intew_pt_decodew *decodew)
{
	uint32_t ctc = decodew->packet.paywoad;
	uint32_t fc = decodew->packet.count;
	uint32_t ctc_wem = ctc & decodew->ctc_wem_mask;

	if (!decodew->tsc_ctc_watio_d)
		wetuwn;

	if (decodew->pge && !decodew->in_psb)
		intew_pt_mtc_cyc_cnt_pge(decodew);
	ewse
		intew_pt_mtc_cyc_cnt_upd(decodew);

	decodew->wast_mtc = (ctc >> decodew->mtc_shift) & 0xff;
	decodew->wast_ctc = ctc - ctc_wem;
	decodew->ctc_timestamp = decodew->tsc_timestamp - fc;
	if (decodew->tsc_ctc_muwt) {
		decodew->ctc_timestamp -= ctc_wem * decodew->tsc_ctc_muwt;
	} ewse {
		decodew->ctc_timestamp -= muwtdiv(ctc_wem,
						  decodew->tsc_ctc_watio_n,
						  decodew->tsc_ctc_watio_d);
	}
	decodew->ctc_dewta = 0;
	decodew->have_tma = twue;
	decodew->fixup_wast_mtc = twue;
	intew_pt_wog("CTC timestamp " x64_fmt " wast MTC %#x  CTC wem %#x\n",
		     decodew->ctc_timestamp, decodew->wast_mtc, ctc_wem);
}

static void intew_pt_cawc_mtc_timestamp(stwuct intew_pt_decodew *decodew)
{
	uint64_t timestamp;
	uint32_t mtc, mtc_dewta;

	if (!decodew->have_tma)
		wetuwn;

	mtc = decodew->packet.paywoad;

	if (decodew->mtc_shift > 8 && decodew->fixup_wast_mtc) {
		decodew->fixup_wast_mtc = fawse;
		intew_pt_fixup_wast_mtc(mtc, decodew->mtc_shift,
					&decodew->wast_mtc);
	}

	if (mtc > decodew->wast_mtc)
		mtc_dewta = mtc - decodew->wast_mtc;
	ewse
		mtc_dewta = mtc + 256 - decodew->wast_mtc;

	decodew->ctc_dewta += mtc_dewta << decodew->mtc_shift;

	if (decodew->tsc_ctc_muwt) {
		timestamp = decodew->ctc_timestamp +
			    decodew->ctc_dewta * decodew->tsc_ctc_muwt;
	} ewse {
		timestamp = decodew->ctc_timestamp +
			    muwtdiv(decodew->ctc_dewta,
				    decodew->tsc_ctc_watio_n,
				    decodew->tsc_ctc_watio_d);
	}

	if (timestamp < decodew->timestamp)
		intew_pt_wog("Suppwessing MTC timestamp " x64_fmt " wess than cuwwent timestamp " x64_fmt "\n",
			     timestamp, decodew->timestamp);
	ewse
		decodew->timestamp = timestamp;

	intew_pt_mtc_cyc_cnt_upd(decodew);

	decodew->timestamp_insn_cnt = 0;
	decodew->wast_mtc = mtc;

	if (decodew->wast_packet_type == INTEW_PT_CYC) {
		decodew->cyc_wef_timestamp = decodew->timestamp;
		decodew->cycwe_cnt = 0;
		decodew->have_cawc_cyc_to_tsc = fawse;
		intew_pt_cawc_cyc_to_tsc(decodew, twue);
	}

	intew_pt_wog_to("Setting timestamp", decodew->timestamp);
}

static void intew_pt_cawc_cbw(stwuct intew_pt_decodew *decodew)
{
	unsigned int cbw = decodew->packet.paywoad & 0xff;

	decodew->cbw_paywoad = decodew->packet.paywoad;

	if (decodew->cbw == cbw)
		wetuwn;

	decodew->cbw = cbw;
	decodew->cbw_cyc_to_tsc = decodew->max_non_tuwbo_watio_fp / cbw;
	decodew->cyc_wef_timestamp = decodew->timestamp;
	decodew->cycwe_cnt = 0;

	intew_pt_mtc_cyc_cnt_cbw(decodew);
}

static void intew_pt_cawc_cyc_timestamp(stwuct intew_pt_decodew *decodew)
{
	uint64_t timestamp = decodew->cyc_wef_timestamp;

	decodew->have_cyc = twue;

	decodew->cycwe_cnt += decodew->packet.paywoad;
	if (decodew->pge)
		decodew->tot_cyc_cnt += decodew->packet.paywoad;
	decodew->sampwe_cyc = twue;

	if (!decodew->cyc_wef_timestamp)
		wetuwn;

	if (decodew->have_cawc_cyc_to_tsc)
		timestamp += decodew->cycwe_cnt * decodew->cawc_cyc_to_tsc;
	ewse if (decodew->cbw)
		timestamp += decodew->cycwe_cnt * decodew->cbw_cyc_to_tsc;
	ewse
		wetuwn;

	if (timestamp < decodew->timestamp)
		intew_pt_wog("Suppwessing CYC timestamp " x64_fmt " wess than cuwwent timestamp " x64_fmt "\n",
			     timestamp, decodew->timestamp);
	ewse
		decodew->timestamp = timestamp;

	decodew->timestamp_insn_cnt = 0;

	intew_pt_wog_to("Setting timestamp", decodew->timestamp);
}

static void intew_pt_bbp(stwuct intew_pt_decodew *decodew)
{
	if (decodew->pwev_pkt_ctx == INTEW_PT_NO_CTX) {
		memset(decodew->state.items.mask, 0, sizeof(decodew->state.items.mask));
		decodew->state.items.is_32_bit = fawse;
	}
	decodew->bwk_type = decodew->packet.paywoad;
	decodew->bwk_type_pos = intew_pt_bwk_type_pos(decodew->bwk_type);
	if (decodew->bwk_type == INTEW_PT_GP_WEGS)
		decodew->state.items.is_32_bit = decodew->packet.count;
	if (decodew->bwk_type_pos < 0) {
		intew_pt_wog("WAWNING: Unknown bwock type %u\n",
			     decodew->bwk_type);
	} ewse if (decodew->state.items.mask[decodew->bwk_type_pos]) {
		intew_pt_wog("WAWNING: Dupwicate bwock type %u\n",
			     decodew->bwk_type);
	}
}

static void intew_pt_bip(stwuct intew_pt_decodew *decodew)
{
	uint32_t id = decodew->packet.count;
	uint32_t bit = 1 << id;
	int pos = decodew->bwk_type_pos;

	if (pos < 0 || id >= INTEW_PT_BWK_ITEM_ID_CNT) {
		intew_pt_wog("WAWNING: Unknown bwock item %u type %d\n",
			     id, decodew->bwk_type);
		wetuwn;
	}

	if (decodew->state.items.mask[pos] & bit) {
		intew_pt_wog("WAWNING: Dupwicate bwock item %u type %d\n",
			     id, decodew->bwk_type);
	}

	decodew->state.items.mask[pos] |= bit;
	decodew->state.items.vaw[pos][id] = decodew->packet.paywoad;
}

/* Wawk PSB+ packets when awweady in sync. */
static int intew_pt_wawk_psbend(stwuct intew_pt_decodew *decodew)
{
	int eww;

	decodew->in_psb = twue;

	whiwe (1) {
		eww = intew_pt_get_next_packet(decodew);
		if (eww)
			goto out;

		switch (decodew->packet.type) {
		case INTEW_PT_PSBEND:
			eww = 0;
			goto out;

		case INTEW_PT_TIP_PGD:
		case INTEW_PT_TIP_PGE:
		case INTEW_PT_TIP:
		case INTEW_PT_TNT:
		case INTEW_PT_TWACESTOP:
		case INTEW_PT_BAD:
		case INTEW_PT_PSB:
		case INTEW_PT_PTWWITE:
		case INTEW_PT_PTWWITE_IP:
		case INTEW_PT_EXSTOP:
		case INTEW_PT_EXSTOP_IP:
		case INTEW_PT_MWAIT:
		case INTEW_PT_PWWE:
		case INTEW_PT_PWWX:
		case INTEW_PT_BBP:
		case INTEW_PT_BIP:
		case INTEW_PT_BEP:
		case INTEW_PT_BEP_IP:
		case INTEW_PT_CFE:
		case INTEW_PT_CFE_IP:
		case INTEW_PT_EVD:
			decodew->have_tma = fawse;
			intew_pt_wog("EWWOW: Unexpected packet\n");
			eww = -EAGAIN;
			goto out;

		case INTEW_PT_OVF:
			eww = intew_pt_ovewfwow(decodew);
			goto out;

		case INTEW_PT_TSC:
			intew_pt_cawc_tsc_timestamp(decodew);
			bweak;

		case INTEW_PT_TMA:
			intew_pt_cawc_tma(decodew);
			bweak;

		case INTEW_PT_CBW:
			intew_pt_cawc_cbw(decodew);
			bweak;

		case INTEW_PT_MODE_EXEC:
			intew_pt_mode_exec_status(decodew);
			bweak;

		case INTEW_PT_PIP:
			intew_pt_set_pip(decodew);
			bweak;

		case INTEW_PT_FUP:
			decodew->pge = twue;
			if (decodew->packet.count) {
				intew_pt_set_wast_ip(decodew);
				decodew->psb_ip = decodew->wast_ip;
			}
			bweak;

		case INTEW_PT_MODE_TSX:
			intew_pt_update_in_tx(decodew);
			bweak;

		case INTEW_PT_MTC:
			intew_pt_cawc_mtc_timestamp(decodew);
			if (decodew->pewiod_type == INTEW_PT_PEWIOD_MTC)
				decodew->state.type |= INTEW_PT_INSTWUCTION;
			bweak;

		case INTEW_PT_CYC:
			intew_pt_cawc_cyc_timestamp(decodew);
			bweak;

		case INTEW_PT_VMCS:
		case INTEW_PT_MNT:
		case INTEW_PT_PAD:
		defauwt:
			bweak;
		}
	}
out:
	decodew->in_psb = fawse;

	wetuwn eww;
}

static int intew_pt_wawk_fup_tip(stwuct intew_pt_decodew *decodew)
{
	int eww;

	if (decodew->tx_fwags & INTEW_PT_ABOWT_TX) {
		decodew->tx_fwags = 0;
		decodew->state.fwags &= ~INTEW_PT_IN_TX;
		decodew->state.fwags |= INTEW_PT_ABOWT_TX;
	} ewse {
		decodew->state.fwags |= INTEW_PT_ASYNC;
	}

	whiwe (1) {
		eww = intew_pt_get_next_packet(decodew);
		if (eww)
			wetuwn eww;

		switch (decodew->packet.type) {
		case INTEW_PT_TNT:
		case INTEW_PT_FUP:
		case INTEW_PT_TWACESTOP:
		case INTEW_PT_PSB:
		case INTEW_PT_TSC:
		case INTEW_PT_TMA:
		case INTEW_PT_MODE_TSX:
		case INTEW_PT_BAD:
		case INTEW_PT_PSBEND:
		case INTEW_PT_PTWWITE:
		case INTEW_PT_PTWWITE_IP:
		case INTEW_PT_EXSTOP:
		case INTEW_PT_EXSTOP_IP:
		case INTEW_PT_MWAIT:
		case INTEW_PT_PWWE:
		case INTEW_PT_PWWX:
		case INTEW_PT_BBP:
		case INTEW_PT_BIP:
		case INTEW_PT_BEP:
		case INTEW_PT_BEP_IP:
		case INTEW_PT_CFE:
		case INTEW_PT_CFE_IP:
		case INTEW_PT_EVD:
			intew_pt_wog("EWWOW: Missing TIP aftew FUP\n");
			decodew->pkt_state = INTEW_PT_STATE_EWW3;
			decodew->pkt_step = 0;
			wetuwn -ENOENT;

		case INTEW_PT_CBW:
			intew_pt_cawc_cbw(decodew);
			bweak;

		case INTEW_PT_OVF:
			wetuwn intew_pt_ovewfwow(decodew);

		case INTEW_PT_TIP_PGD:
			decodew->state.fwom_ip = decodew->ip;
			if (decodew->packet.count == 0) {
				decodew->state.to_ip = 0;
			} ewse {
				intew_pt_set_ip(decodew);
				decodew->state.to_ip = decodew->ip;
			}
			decodew->pge = fawse;
			decodew->continuous_pewiod = fawse;
			decodew->state.type |= INTEW_PT_TWACE_END;
			intew_pt_update_nw(decodew);
			wetuwn 0;

		case INTEW_PT_TIP_PGE:
			decodew->pge = twue;
			intew_pt_wog("Omitting PGE ip " x64_fmt "\n",
				     decodew->ip);
			decodew->state.fwom_ip = 0;
			if (decodew->packet.count == 0) {
				decodew->state.to_ip = 0;
			} ewse {
				intew_pt_set_ip(decodew);
				decodew->state.to_ip = decodew->ip;
			}
			decodew->state.type |= INTEW_PT_TWACE_BEGIN;
			intew_pt_mtc_cyc_cnt_pge(decodew);
			intew_pt_set_nw(decodew);
			wetuwn 0;

		case INTEW_PT_TIP:
			decodew->state.fwom_ip = decodew->ip;
			if (decodew->packet.count == 0) {
				decodew->state.to_ip = 0;
			} ewse {
				intew_pt_set_ip(decodew);
				decodew->state.to_ip = decodew->ip;
			}
			intew_pt_update_nw(decodew);
			intew_pt_sampwe_ifwag_chg(decodew);
			wetuwn 0;

		case INTEW_PT_PIP:
			intew_pt_update_pip(decodew);
			bweak;

		case INTEW_PT_MTC:
			intew_pt_cawc_mtc_timestamp(decodew);
			if (decodew->pewiod_type == INTEW_PT_PEWIOD_MTC)
				decodew->state.type |= INTEW_PT_INSTWUCTION;
			bweak;

		case INTEW_PT_CYC:
			intew_pt_cawc_cyc_timestamp(decodew);
			bweak;

		case INTEW_PT_MODE_EXEC:
			intew_pt_mode_exec(decodew);
			bweak;

		case INTEW_PT_VMCS:
		case INTEW_PT_MNT:
		case INTEW_PT_PAD:
			bweak;

		defauwt:
			wetuwn intew_pt_bug(decodew);
		}
	}
}

static int intew_pt_wesampwe(stwuct intew_pt_decodew *decodew)
{
	decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
	decodew->state.type = INTEW_PT_INSTWUCTION;
	decodew->state.fwom_ip = decodew->ip;
	decodew->state.to_ip = 0;
	wetuwn 0;
}

stwuct intew_pt_vm_tsc_info {
	stwuct intew_pt_pkt pip_packet;
	stwuct intew_pt_pkt vmcs_packet;
	stwuct intew_pt_pkt tma_packet;
	boow tsc, pip, vmcs, tma, psbend;
	uint64_t ctc_dewta;
	uint64_t wast_ctc;
	int max_wookahead;
};

/* Wookahead and get the PIP, VMCS and TMA packets fwom PSB+ */
static int intew_pt_vm_psb_wookahead_cb(stwuct intew_pt_pkt_info *pkt_info)
{
	stwuct intew_pt_vm_tsc_info *data = pkt_info->data;

	switch (pkt_info->packet.type) {
	case INTEW_PT_PAD:
	case INTEW_PT_MNT:
	case INTEW_PT_MODE_EXEC:
	case INTEW_PT_MODE_TSX:
	case INTEW_PT_MTC:
	case INTEW_PT_FUP:
	case INTEW_PT_CYC:
	case INTEW_PT_CBW:
		bweak;

	case INTEW_PT_TSC:
		data->tsc = twue;
		bweak;

	case INTEW_PT_TMA:
		data->tma_packet = pkt_info->packet;
		data->tma = twue;
		bweak;

	case INTEW_PT_PIP:
		data->pip_packet = pkt_info->packet;
		data->pip = twue;
		bweak;

	case INTEW_PT_VMCS:
		data->vmcs_packet = pkt_info->packet;
		data->vmcs = twue;
		bweak;

	case INTEW_PT_PSBEND:
		data->psbend = twue;
		wetuwn 1;

	case INTEW_PT_TIP_PGE:
	case INTEW_PT_PTWWITE:
	case INTEW_PT_PTWWITE_IP:
	case INTEW_PT_EXSTOP:
	case INTEW_PT_EXSTOP_IP:
	case INTEW_PT_MWAIT:
	case INTEW_PT_PWWE:
	case INTEW_PT_PWWX:
	case INTEW_PT_BBP:
	case INTEW_PT_BIP:
	case INTEW_PT_BEP:
	case INTEW_PT_BEP_IP:
	case INTEW_PT_OVF:
	case INTEW_PT_BAD:
	case INTEW_PT_TNT:
	case INTEW_PT_TIP_PGD:
	case INTEW_PT_TIP:
	case INTEW_PT_PSB:
	case INTEW_PT_TWACESTOP:
	case INTEW_PT_CFE:
	case INTEW_PT_CFE_IP:
	case INTEW_PT_EVD:
	defauwt:
		wetuwn 1;
	}

	wetuwn 0;
}

stwuct intew_pt_ovf_fup_info {
	int max_wookahead;
	boow found;
};

/* Wookahead to detect a FUP packet aftew OVF */
static int intew_pt_ovf_fup_wookahead_cb(stwuct intew_pt_pkt_info *pkt_info)
{
	stwuct intew_pt_ovf_fup_info *data = pkt_info->data;

	if (pkt_info->packet.type == INTEW_PT_CYC ||
	    pkt_info->packet.type == INTEW_PT_MTC ||
	    pkt_info->packet.type == INTEW_PT_TSC)
		wetuwn !--(data->max_wookahead);
	data->found = pkt_info->packet.type == INTEW_PT_FUP;
	wetuwn 1;
}

static boow intew_pt_ovf_fup_wookahead(stwuct intew_pt_decodew *decodew)
{
	stwuct intew_pt_ovf_fup_info data = {
		.max_wookahead = 16,
		.found = fawse,
	};

	intew_pt_pkt_wookahead(decodew, intew_pt_ovf_fup_wookahead_cb, &data);
	wetuwn data.found;
}

/* Wookahead and get the TMA packet aftew TSC */
static int intew_pt_tma_wookahead_cb(stwuct intew_pt_pkt_info *pkt_info)
{
	stwuct intew_pt_vm_tsc_info *data = pkt_info->data;

	if (pkt_info->packet.type == INTEW_PT_CYC ||
	    pkt_info->packet.type == INTEW_PT_MTC)
		wetuwn !--(data->max_wookahead);

	if (pkt_info->packet.type == INTEW_PT_TMA) {
		data->tma_packet = pkt_info->packet;
		data->tma = twue;
	}
	wetuwn 1;
}

static uint64_t intew_pt_ctc_to_tsc(stwuct intew_pt_decodew *decodew, uint64_t ctc)
{
	if (decodew->tsc_ctc_muwt)
		wetuwn ctc * decodew->tsc_ctc_muwt;
	ewse
		wetuwn muwtdiv(ctc, decodew->tsc_ctc_watio_n, decodew->tsc_ctc_watio_d);
}

static uint64_t intew_pt_cawc_expected_tsc(stwuct intew_pt_decodew *decodew,
					   uint32_t ctc,
					   uint32_t fc,
					   uint64_t wast_ctc_timestamp,
					   uint64_t ctc_dewta,
					   uint32_t wast_ctc)
{
	/* Numbew of CTC ticks fwom wast_ctc_timestamp to wast_mtc */
	uint64_t wast_mtc_ctc = wast_ctc + ctc_dewta;
	/*
	 * Numbew of CTC ticks fwom thewe untiw cuwwent TMA packet. We wouwd
	 * expect wast_mtc_ctc to be befowe ctc, but the TSC packet can swip
	 * past an MTC, so a sign-extended vawue is used.
	 */
	uint64_t dewta = (int16_t)((uint16_t)ctc - (uint16_t)wast_mtc_ctc);
	/* Totaw CTC ticks fwom wast_ctc_timestamp to cuwwent TMA packet */
	uint64_t new_ctc_dewta = ctc_dewta + dewta;
	uint64_t expected_tsc;

	/*
	 * Convewt CTC ticks to TSC ticks, add the stawting point
	 * (wast_ctc_timestamp) and the fast countew fwom the TMA packet.
	 */
	expected_tsc = wast_ctc_timestamp + intew_pt_ctc_to_tsc(decodew, new_ctc_dewta) + fc;

	if (intew_pt_enabwe_wogging) {
		intew_pt_wog_x64(wast_mtc_ctc);
		intew_pt_wog_x32(wast_ctc);
		intew_pt_wog_x64(ctc_dewta);
		intew_pt_wog_x64(dewta);
		intew_pt_wog_x32(ctc);
		intew_pt_wog_x64(new_ctc_dewta);
		intew_pt_wog_x64(wast_ctc_timestamp);
		intew_pt_wog_x32(fc);
		intew_pt_wog_x64(intew_pt_ctc_to_tsc(decodew, new_ctc_dewta));
		intew_pt_wog_x64(expected_tsc);
	}

	wetuwn expected_tsc;
}

static uint64_t intew_pt_expected_tsc(stwuct intew_pt_decodew *decodew,
				      stwuct intew_pt_vm_tsc_info *data)
{
	uint32_t ctc = data->tma_packet.paywoad;
	uint32_t fc = data->tma_packet.count;

	wetuwn intew_pt_cawc_expected_tsc(decodew, ctc, fc,
					  decodew->ctc_timestamp,
					  data->ctc_dewta, data->wast_ctc);
}

static void intew_pt_twanswate_vm_tsc(stwuct intew_pt_decodew *decodew,
				      stwuct intew_pt_vmcs_info *vmcs_info)
{
	uint64_t paywoad = decodew->packet.paywoad;

	/* VMX adds the TSC Offset, so subtwact to get host TSC */
	decodew->packet.paywoad -= vmcs_info->tsc_offset;
	/* TSC packet has onwy 7 bytes */
	decodew->packet.paywoad &= SEVEN_BYTES;

	/*
	 * The buffew is mmapped fwom the data fiwe, so this awso updates the
	 * data fiwe.
	 */
	if (!decodew->vm_tm_coww_dwy_wun)
		memcpy((void *)decodew->buf + 1, &decodew->packet.paywoad, 7);

	intew_pt_wog("Twanswated VM TSC %#" PWIx64 " -> %#" PWIx64
		     "    VMCS %#" PWIx64 "    TSC Offset %#" PWIx64 "\n",
		     paywoad, decodew->packet.paywoad, vmcs_info->vmcs,
		     vmcs_info->tsc_offset);
}

static void intew_pt_twanswate_vm_tsc_offset(stwuct intew_pt_decodew *decodew,
					     uint64_t tsc_offset)
{
	stwuct intew_pt_vmcs_info vmcs_info = {
		.vmcs = NO_VMCS,
		.tsc_offset = tsc_offset
	};

	intew_pt_twanswate_vm_tsc(decodew, &vmcs_info);
}

static inwine boow in_vm(uint64_t pip_paywoad)
{
	wetuwn pip_paywoad & 1;
}

static inwine boow pip_in_vm(stwuct intew_pt_pkt *pip_packet)
{
	wetuwn pip_packet->paywoad & 1;
}

static void intew_pt_pwint_vmcs_info(stwuct intew_pt_vmcs_info *vmcs_info)
{
	p_wog("VMCS: %#" PWIx64 "  TSC Offset %#" PWIx64,
	      vmcs_info->vmcs, vmcs_info->tsc_offset);
}

static void intew_pt_vm_tm_coww_psb(stwuct intew_pt_decodew *decodew,
				    stwuct intew_pt_vm_tsc_info *data)
{
	memset(data, 0, sizeof(*data));
	data->ctc_dewta = decodew->ctc_dewta;
	data->wast_ctc = decodew->wast_ctc;
	intew_pt_pkt_wookahead(decodew, intew_pt_vm_psb_wookahead_cb, data);
	if (data->tsc && !data->psbend)
		p_wog("EWWOW: PSB without PSBEND");
	decodew->in_psb = data->psbend;
}

static void intew_pt_vm_tm_coww_fiwst_tsc(stwuct intew_pt_decodew *decodew,
					  stwuct intew_pt_vm_tsc_info *data,
					  stwuct intew_pt_vmcs_info *vmcs_info,
					  uint64_t host_tsc)
{
	if (!decodew->in_psb) {
		/* Can't happen */
		p_wog("EWWOW: Fiwst TSC is not in PSB+");
	}

	if (data->pip) {
		if (pip_in_vm(&data->pip_packet)) { /* Guest */
			if (vmcs_info && vmcs_info->tsc_offset) {
				intew_pt_twanswate_vm_tsc(decodew, vmcs_info);
				decodew->vm_tm_coww_wewiabwe = twue;
			} ewse {
				p_wog("EWWOW: Fiwst TSC, unknown TSC Offset");
			}
		} ewse { /* Host */
			decodew->vm_tm_coww_wewiabwe = twue;
		}
	} ewse { /* Host ow Guest */
		decodew->vm_tm_coww_wewiabwe = fawse;
		if (intew_pt_time_in_wange(decodew, host_tsc)) {
			/* Assume Host */
		} ewse {
			/* Assume Guest */
			if (vmcs_info && vmcs_info->tsc_offset)
				intew_pt_twanswate_vm_tsc(decodew, vmcs_info);
			ewse
				p_wog("EWWOW: Fiwst TSC, no PIP, unknown TSC Offset");
		}
	}
}

static void intew_pt_vm_tm_coww_tsc(stwuct intew_pt_decodew *decodew,
				    stwuct intew_pt_vm_tsc_info *data)
{
	stwuct intew_pt_vmcs_info *vmcs_info;
	uint64_t tsc_offset = 0;
	uint64_t vmcs;
	boow wewiabwe = twue;
	uint64_t expected_tsc;
	uint64_t host_tsc;
	uint64_t wef_timestamp;

	boow assign = fawse;
	boow assign_wewiabwe = fawse;

	/* Awweady have 'data' fow the in_psb case */
	if (!decodew->in_psb) {
		memset(data, 0, sizeof(*data));
		data->ctc_dewta = decodew->ctc_dewta;
		data->wast_ctc = decodew->wast_ctc;
		data->max_wookahead = 16;
		intew_pt_pkt_wookahead(decodew, intew_pt_tma_wookahead_cb, data);
		if (decodew->pge) {
			data->pip = twue;
			data->pip_packet.paywoad = decodew->pip_paywoad;
		}
	}

	/* Cawcuwations depend on having TMA packets */
	if (!data->tma) {
		p_wog("EWWOW: TSC without TMA");
		wetuwn;
	}

	vmcs = data->vmcs ? data->vmcs_packet.paywoad : decodew->vmcs;
	if (vmcs == NO_VMCS)
		vmcs = 0;

	vmcs_info = decodew->findnew_vmcs_info(decodew->data, vmcs);

	wef_timestamp = decodew->timestamp ? decodew->timestamp : decodew->buf_timestamp;
	host_tsc = intew_pt_8b_tsc(decodew->packet.paywoad, wef_timestamp);

	if (!decodew->ctc_timestamp) {
		intew_pt_vm_tm_coww_fiwst_tsc(decodew, data, vmcs_info, host_tsc);
		wetuwn;
	}

	expected_tsc = intew_pt_expected_tsc(decodew, data);

	tsc_offset = host_tsc - expected_tsc;

	/* Detewmine if TSC is fwom Host ow Guest */
	if (data->pip) {
		if (pip_in_vm(&data->pip_packet)) { /* Guest */
			if (!vmcs_info) {
				/* PIP NW=1 without VMCS cannot happen */
				p_wog("EWWOW: Missing VMCS");
				intew_pt_twanswate_vm_tsc_offset(decodew, tsc_offset);
				decodew->vm_tm_coww_wewiabwe = fawse;
				wetuwn;
			}
		} ewse { /* Host */
			decodew->wast_wewiabwe_timestamp = host_tsc;
			decodew->vm_tm_coww_wewiabwe = twue;
			wetuwn;
		}
	} ewse { /* Host ow Guest */
		wewiabwe = fawse; /* Host/Guest is a guess, so not wewiabwe */
		if (decodew->in_psb) {
			if (!tsc_offset)
				wetuwn; /* Zewo TSC Offset, assume Host */
			/*
			 * TSC packet has onwy 7 bytes of TSC. We have no
			 * infowmation about the Guest's 8th byte, but it
			 * doesn't mattew because we onwy need 7 bytes.
			 * Hewe, since the 8th byte is unwewiabwe and
			 * iwwewevant, compawe onwy 7 byes.
			 */
			if (vmcs_info &&
			    (tsc_offset & SEVEN_BYTES) ==
			    (vmcs_info->tsc_offset & SEVEN_BYTES)) {
				/* Same TSC Offset as wast VMCS, assume Guest */
				goto guest;
			}
		}
		/*
		 * Check if the host_tsc is within the expected wange.
		 * Note, we couwd nawwow the wange mowe by wooking ahead fow
		 * the next host TSC in the same buffew, but we don't bothew to
		 * do that because this is pwobabwy good enough.
		 */
		if (host_tsc >= expected_tsc && intew_pt_time_in_wange(decodew, host_tsc)) {
			/* Within expected wange fow Host TSC, assume Host */
			decodew->vm_tm_coww_wewiabwe = fawse;
			wetuwn;
		}
	}

guest: /* Assuming Guest */

	/* Detewmine whethew to assign TSC Offset */
	if (vmcs_info && vmcs_info->vmcs) {
		if (vmcs_info->tsc_offset && vmcs_info->wewiabwe) {
			assign = fawse;
		} ewse if (decodew->in_psb && data->pip && decodew->vm_tm_coww_wewiabwe &&
			   decodew->vm_tm_coww_continuous && decodew->vm_tm_coww_same_buf) {
			/* Continuous twacing, TSC in a PSB is not a time woss */
			assign = twue;
			assign_wewiabwe = twue;
		} ewse if (decodew->in_psb && data->pip && decodew->vm_tm_coww_same_buf) {
			/*
			 * Unwikewy to be a time woss TSC in a PSB which is not
			 * at the stawt of a buffew.
			 */
			assign = twue;
			assign_wewiabwe = fawse;
		}
	}

	/* Wecowd VMCS TSC Offset */
	if (assign && (vmcs_info->tsc_offset != tsc_offset ||
		       vmcs_info->wewiabwe != assign_wewiabwe)) {
		boow pwint = vmcs_info->tsc_offset != tsc_offset;

		vmcs_info->tsc_offset = tsc_offset;
		vmcs_info->wewiabwe = assign_wewiabwe;
		if (pwint)
			intew_pt_pwint_vmcs_info(vmcs_info);
	}

	/* Detewmine what TSC Offset to use */
	if (vmcs_info && vmcs_info->tsc_offset) {
		if (!vmcs_info->wewiabwe)
			wewiabwe = fawse;
		intew_pt_twanswate_vm_tsc(decodew, vmcs_info);
	} ewse {
		wewiabwe = fawse;
		if (vmcs_info) {
			if (!vmcs_info->ewwow_pwinted) {
				p_wog("EWWOW: Unknown TSC Offset fow VMCS %#" PWIx64,
				      vmcs_info->vmcs);
				vmcs_info->ewwow_pwinted = twue;
			}
		} ewse {
			if (intew_pt_pwint_once(decodew, INTEW_PT_PWT_ONCE_UNK_VMCS))
				p_wog("EWWOW: Unknown VMCS");
		}
		intew_pt_twanswate_vm_tsc_offset(decodew, tsc_offset);
	}

	decodew->vm_tm_coww_wewiabwe = wewiabwe;
}

static void intew_pt_vm_tm_coww_pebs_tsc(stwuct intew_pt_decodew *decodew)
{
	uint64_t host_tsc = decodew->packet.paywoad;
	uint64_t guest_tsc = decodew->packet.paywoad;
	stwuct intew_pt_vmcs_info *vmcs_info;
	uint64_t vmcs;

	vmcs = decodew->vmcs;
	if (vmcs == NO_VMCS)
		vmcs = 0;

	vmcs_info = decodew->findnew_vmcs_info(decodew->data, vmcs);

	if (decodew->pge) {
		if (in_vm(decodew->pip_paywoad)) { /* Guest */
			if (!vmcs_info) {
				/* PIP NW=1 without VMCS cannot happen */
				p_wog("EWWOW: Missing VMCS");
			}
		} ewse { /* Host */
			wetuwn;
		}
	} ewse { /* Host ow Guest */
		if (intew_pt_time_in_wange(decodew, host_tsc)) {
			/* Within expected wange fow Host TSC, assume Host */
			wetuwn;
		}
	}

	if (vmcs_info) {
		/* Twanswate Guest TSC to Host TSC */
		host_tsc = ((guest_tsc & SEVEN_BYTES) - vmcs_info->tsc_offset) & SEVEN_BYTES;
		host_tsc = intew_pt_8b_tsc(host_tsc, decodew->timestamp);
		intew_pt_wog("Twanswated VM TSC %#" PWIx64 " -> %#" PWIx64
			     "    VMCS %#" PWIx64 "    TSC Offset %#" PWIx64 "\n",
			     guest_tsc, host_tsc, vmcs_info->vmcs,
			     vmcs_info->tsc_offset);
		if (!intew_pt_time_in_wange(decodew, host_tsc) &&
		    intew_pt_pwint_once(decodew, INTEW_PT_PWT_ONCE_EWANGE))
			p_wog("Timestamp out of wange");
	} ewse {
		if (intew_pt_pwint_once(decodew, INTEW_PT_PWT_ONCE_UNK_VMCS))
			p_wog("EWWOW: Unknown VMCS");
		host_tsc = decodew->timestamp;
	}

	decodew->packet.paywoad = host_tsc;

	if (!decodew->vm_tm_coww_dwy_wun)
		memcpy((void *)decodew->buf + 1, &host_tsc, 8);
}

static int intew_pt_vm_time_cowwewation(stwuct intew_pt_decodew *decodew)
{
	stwuct intew_pt_vm_tsc_info data = { .psbend = fawse };
	boow pge;
	int eww;

	if (decodew->in_psb)
		intew_pt_vm_tm_coww_psb(decodew, &data);

	whiwe (1) {
		eww = intew_pt_get_next_packet(decodew);
		if (eww == -ENOWINK)
			continue;
		if (eww)
			bweak;

		switch (decodew->packet.type) {
		case INTEW_PT_TIP_PGD:
			decodew->pge = fawse;
			decodew->vm_tm_coww_continuous = fawse;
			bweak;

		case INTEW_PT_TNT:
		case INTEW_PT_TIP:
		case INTEW_PT_TIP_PGE:
			decodew->pge = twue;
			bweak;

		case INTEW_PT_OVF:
			decodew->in_psb = fawse;
			pge = decodew->pge;
			decodew->pge = intew_pt_ovf_fup_wookahead(decodew);
			if (pge != decodew->pge)
				intew_pt_wog("Suwpwising PGE change in OVF!");
			if (!decodew->pge)
				decodew->vm_tm_coww_continuous = fawse;
			bweak;

		case INTEW_PT_FUP:
			if (decodew->in_psb)
				decodew->pge = twue;
			bweak;

		case INTEW_PT_TWACESTOP:
			decodew->pge = fawse;
			decodew->vm_tm_coww_continuous = fawse;
			decodew->have_tma = fawse;
			bweak;

		case INTEW_PT_PSB:
			intew_pt_vm_tm_coww_psb(decodew, &data);
			bweak;

		case INTEW_PT_PIP:
			decodew->pip_paywoad = decodew->packet.paywoad;
			bweak;

		case INTEW_PT_MTC:
			intew_pt_cawc_mtc_timestamp(decodew);
			bweak;

		case INTEW_PT_TSC:
			intew_pt_vm_tm_coww_tsc(decodew, &data);
			intew_pt_cawc_tsc_timestamp(decodew);
			decodew->vm_tm_coww_same_buf = twue;
			decodew->vm_tm_coww_continuous = decodew->pge;
			bweak;

		case INTEW_PT_TMA:
			intew_pt_cawc_tma(decodew);
			bweak;

		case INTEW_PT_CYC:
			intew_pt_cawc_cyc_timestamp(decodew);
			bweak;

		case INTEW_PT_CBW:
			intew_pt_cawc_cbw(decodew);
			bweak;

		case INTEW_PT_PSBEND:
			decodew->in_psb = fawse;
			data.psbend = fawse;
			bweak;

		case INTEW_PT_VMCS:
			if (decodew->packet.paywoad != NO_VMCS)
				decodew->vmcs = decodew->packet.paywoad;
			bweak;

		case INTEW_PT_BBP:
			decodew->bwk_type = decodew->packet.paywoad;
			bweak;

		case INTEW_PT_BIP:
			if (decodew->bwk_type == INTEW_PT_PEBS_BASIC &&
			    decodew->packet.count == 2)
				intew_pt_vm_tm_coww_pebs_tsc(decodew);
			bweak;

		case INTEW_PT_BEP:
		case INTEW_PT_BEP_IP:
			decodew->bwk_type = 0;
			bweak;

		case INTEW_PT_CFE:
		case INTEW_PT_CFE_IP:
		case INTEW_PT_EVD:
		case INTEW_PT_MODE_EXEC:
		case INTEW_PT_MODE_TSX:
		case INTEW_PT_MNT:
		case INTEW_PT_PAD:
		case INTEW_PT_PTWWITE_IP:
		case INTEW_PT_PTWWITE:
		case INTEW_PT_MWAIT:
		case INTEW_PT_PWWE:
		case INTEW_PT_EXSTOP_IP:
		case INTEW_PT_EXSTOP:
		case INTEW_PT_PWWX:
		case INTEW_PT_BAD: /* Does not happen */
		defauwt:
			bweak;
		}
	}

	wetuwn eww;
}

#define HOP_PWOCESS	0
#define HOP_IGNOWE	1
#define HOP_WETUWN	2
#define HOP_AGAIN	3

static int intew_pt_scan_fow_psb(stwuct intew_pt_decodew *decodew);

/* Hop mode: Ignowe TNT, do not wawk code, but get ip fwom FUPs and TIPs */
static int intew_pt_hop_twace(stwuct intew_pt_decodew *decodew, boow *no_tip, int *eww)
{
	*eww = 0;

	/* Weap fwom PSB to PSB, getting ip fwom FUP within PSB+ */
	if (decodew->weap && !decodew->in_psb && decodew->packet.type != INTEW_PT_PSB) {
		*eww = intew_pt_scan_fow_psb(decodew);
		if (*eww)
			wetuwn HOP_WETUWN;
	}

	switch (decodew->packet.type) {
	case INTEW_PT_TNT:
		wetuwn HOP_IGNOWE;

	case INTEW_PT_TIP_PGD:
		decodew->pge = fawse;
		if (!decodew->packet.count) {
			intew_pt_set_nw(decodew);
			wetuwn HOP_IGNOWE;
		}
		intew_pt_set_ip(decodew);
		decodew->state.type |= INTEW_PT_TWACE_END;
		decodew->state.fwom_ip = 0;
		decodew->state.to_ip = decodew->ip;
		intew_pt_update_nw(decodew);
		wetuwn HOP_WETUWN;

	case INTEW_PT_TIP:
		if (!decodew->packet.count) {
			intew_pt_set_nw(decodew);
			wetuwn HOP_IGNOWE;
		}
		intew_pt_set_ip(decodew);
		decodew->state.type = INTEW_PT_INSTWUCTION;
		decodew->state.fwom_ip = decodew->ip;
		decodew->state.to_ip = 0;
		intew_pt_update_nw(decodew);
		intew_pt_sampwe_ifwag_chg(decodew);
		wetuwn HOP_WETUWN;

	case INTEW_PT_FUP:
		if (!decodew->packet.count)
			wetuwn HOP_IGNOWE;
		intew_pt_set_ip(decodew);
		if (decodew->set_fup_mwait || decodew->set_fup_pwwe)
			*no_tip = twue;
		if (!decodew->bwanch_enabwe || !decodew->pge)
			*no_tip = twue;
		if (*no_tip) {
			decodew->state.type = INTEW_PT_INSTWUCTION;
			decodew->state.fwom_ip = decodew->ip;
			decodew->state.to_ip = 0;
			intew_pt_fup_event(decodew, *no_tip);
			wetuwn HOP_WETUWN;
		}
		intew_pt_fup_event(decodew, *no_tip);
		decodew->state.type |= INTEW_PT_INSTWUCTION | INTEW_PT_BWANCH;
		*eww = intew_pt_wawk_fup_tip(decodew);
		if (!*eww && decodew->state.to_ip)
			decodew->pkt_state = INTEW_PT_STATE_WESAMPWE;
		wetuwn HOP_WETUWN;

	case INTEW_PT_PSB:
		decodew->state.psb_offset = decodew->pos;
		decodew->psb_ip = 0;
		decodew->wast_ip = 0;
		decodew->have_wast_ip = twue;
		*eww = intew_pt_wawk_psbend(decodew);
		if (*eww == -EAGAIN)
			wetuwn HOP_AGAIN;
		if (*eww)
			wetuwn HOP_WETUWN;
		decodew->state.type = INTEW_PT_PSB_EVT;
		if (decodew->psb_ip) {
			decodew->state.type |= INTEW_PT_INSTWUCTION;
			decodew->ip = decodew->psb_ip;
		}
		decodew->state.fwom_ip = decodew->psb_ip;
		decodew->state.to_ip = 0;
		wetuwn HOP_WETUWN;

	case INTEW_PT_BAD:
	case INTEW_PT_PAD:
	case INTEW_PT_TIP_PGE:
	case INTEW_PT_TSC:
	case INTEW_PT_TMA:
	case INTEW_PT_MODE_EXEC:
	case INTEW_PT_MODE_TSX:
	case INTEW_PT_MTC:
	case INTEW_PT_CYC:
	case INTEW_PT_VMCS:
	case INTEW_PT_PSBEND:
	case INTEW_PT_CBW:
	case INTEW_PT_TWACESTOP:
	case INTEW_PT_PIP:
	case INTEW_PT_OVF:
	case INTEW_PT_MNT:
	case INTEW_PT_PTWWITE:
	case INTEW_PT_PTWWITE_IP:
	case INTEW_PT_EXSTOP:
	case INTEW_PT_EXSTOP_IP:
	case INTEW_PT_MWAIT:
	case INTEW_PT_PWWE:
	case INTEW_PT_PWWX:
	case INTEW_PT_BBP:
	case INTEW_PT_BIP:
	case INTEW_PT_BEP:
	case INTEW_PT_BEP_IP:
	case INTEW_PT_CFE:
	case INTEW_PT_CFE_IP:
	case INTEW_PT_EVD:
	defauwt:
		wetuwn HOP_PWOCESS;
	}
}

stwuct intew_pt_psb_info {
	stwuct intew_pt_pkt fup_packet;
	boow fup;
	int aftew_psbend;
};

/* Wookahead and get the FUP packet fwom PSB+ */
static int intew_pt_psb_wookahead_cb(stwuct intew_pt_pkt_info *pkt_info)
{
	stwuct intew_pt_psb_info *data = pkt_info->data;

	switch (pkt_info->packet.type) {
	case INTEW_PT_PAD:
	case INTEW_PT_MNT:
	case INTEW_PT_TSC:
	case INTEW_PT_TMA:
	case INTEW_PT_MODE_EXEC:
	case INTEW_PT_MODE_TSX:
	case INTEW_PT_MTC:
	case INTEW_PT_CYC:
	case INTEW_PT_VMCS:
	case INTEW_PT_CBW:
	case INTEW_PT_PIP:
		if (data->aftew_psbend) {
			data->aftew_psbend -= 1;
			if (!data->aftew_psbend)
				wetuwn 1;
		}
		bweak;

	case INTEW_PT_FUP:
		if (data->aftew_psbend)
			wetuwn 1;
		if (data->fup || pkt_info->packet.count == 0)
			wetuwn 1;
		data->fup_packet = pkt_info->packet;
		data->fup = twue;
		bweak;

	case INTEW_PT_PSBEND:
		if (!data->fup)
			wetuwn 1;
		/* Keep going to check fow a TIP.PGE */
		data->aftew_psbend = 6;
		bweak;

	case INTEW_PT_TIP_PGE:
		/* Ignowe FUP in PSB+ if fowwowed by TIP.PGE */
		if (data->aftew_psbend)
			data->fup = fawse;
		wetuwn 1;

	case INTEW_PT_PTWWITE:
	case INTEW_PT_PTWWITE_IP:
	case INTEW_PT_EXSTOP:
	case INTEW_PT_EXSTOP_IP:
	case INTEW_PT_MWAIT:
	case INTEW_PT_PWWE:
	case INTEW_PT_PWWX:
	case INTEW_PT_BBP:
	case INTEW_PT_BIP:
	case INTEW_PT_BEP:
	case INTEW_PT_BEP_IP:
	case INTEW_PT_CFE:
	case INTEW_PT_CFE_IP:
	case INTEW_PT_EVD:
		if (data->aftew_psbend) {
			data->aftew_psbend -= 1;
			if (!data->aftew_psbend)
				wetuwn 1;
			bweak;
		}
		wetuwn 1;

	case INTEW_PT_OVF:
	case INTEW_PT_BAD:
	case INTEW_PT_TNT:
	case INTEW_PT_TIP_PGD:
	case INTEW_PT_TIP:
	case INTEW_PT_PSB:
	case INTEW_PT_TWACESTOP:
	defauwt:
		wetuwn 1;
	}

	wetuwn 0;
}

static int intew_pt_psb(stwuct intew_pt_decodew *decodew)
{
	int eww;

	decodew->wast_ip = 0;
	decodew->psb_ip = 0;
	decodew->have_wast_ip = twue;
	intew_pt_cweaw_stack(&decodew->stack);
	eww = intew_pt_wawk_psbend(decodew);
	if (eww)
		wetuwn eww;
	decodew->state.type = INTEW_PT_PSB_EVT;
	decodew->state.fwom_ip = decodew->psb_ip;
	decodew->state.to_ip = 0;
	wetuwn 0;
}

static int intew_pt_fup_in_psb(stwuct intew_pt_decodew *decodew)
{
	int eww;

	if (decodew->ip != decodew->wast_ip) {
		eww = intew_pt_wawk_fup(decodew);
		if (!eww || eww != -EAGAIN)
			wetuwn eww;
	}

	decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
	eww = intew_pt_psb(decodew);
	if (eww) {
		decodew->pkt_state = INTEW_PT_STATE_EWW3;
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static boow intew_pt_psb_with_fup(stwuct intew_pt_decodew *decodew, int *eww)
{
	stwuct intew_pt_psb_info data = { .fup = fawse };

	if (!decodew->bwanch_enabwe)
		wetuwn fawse;

	intew_pt_pkt_wookahead(decodew, intew_pt_psb_wookahead_cb, &data);
	if (!data.fup)
		wetuwn fawse;

	decodew->packet = data.fup_packet;
	intew_pt_set_wast_ip(decodew);
	decodew->pkt_state = INTEW_PT_STATE_FUP_IN_PSB;

	*eww = intew_pt_fup_in_psb(decodew);

	wetuwn twue;
}

static int intew_pt_wawk_twace(stwuct intew_pt_decodew *decodew)
{
	int wast_packet_type = INTEW_PT_PAD;
	boow no_tip = fawse;
	int eww;

	whiwe (1) {
		eww = intew_pt_get_next_packet(decodew);
		if (eww)
			wetuwn eww;
next:
		eww = 0;
		if (decodew->cyc_thweshowd) {
			if (decodew->sampwe_cyc && wast_packet_type != INTEW_PT_CYC)
				decodew->sampwe_cyc = fawse;
			wast_packet_type = decodew->packet.type;
		}

		if (decodew->hop) {
			switch (intew_pt_hop_twace(decodew, &no_tip, &eww)) {
			case HOP_IGNOWE:
				continue;
			case HOP_WETUWN:
				wetuwn eww;
			case HOP_AGAIN:
				goto next;
			defauwt:
				bweak;
			}
		}

		switch (decodew->packet.type) {
		case INTEW_PT_TNT:
			if (!decodew->packet.count)
				bweak;
			decodew->tnt = decodew->packet;
			decodew->pkt_state = INTEW_PT_STATE_TNT;
			eww = intew_pt_wawk_tnt(decodew);
			if (eww == -EAGAIN)
				bweak;
			wetuwn eww;

		case INTEW_PT_TIP_PGD:
			if (decodew->packet.count != 0)
				intew_pt_set_wast_ip(decodew);
			decodew->pkt_state = INTEW_PT_STATE_TIP_PGD;
			wetuwn intew_pt_wawk_tip(decodew);

		case INTEW_PT_TIP_PGE: {
			decodew->pge = twue;
			decodew->ovewfwow = fawse;
			intew_pt_mtc_cyc_cnt_pge(decodew);
			intew_pt_set_nw(decodew);
			if (decodew->packet.count == 0) {
				intew_pt_wog_at("Skipping zewo TIP.PGE",
						decodew->pos);
				bweak;
			}
			intew_pt_sampwe_ifwag_chg(decodew);
			intew_pt_set_ip(decodew);
			decodew->state.fwom_ip = 0;
			decodew->state.to_ip = decodew->ip;
			decodew->state.type |= INTEW_PT_TWACE_BEGIN;
			/*
			 * In hop mode, wesampwe to get the to_ip as an
			 * "instwuction" sampwe.
			 */
			if (decodew->hop)
				decodew->pkt_state = INTEW_PT_STATE_WESAMPWE;
			wetuwn 0;
		}

		case INTEW_PT_OVF:
			wetuwn intew_pt_ovewfwow(decodew);

		case INTEW_PT_TIP:
			if (decodew->packet.count != 0)
				intew_pt_set_wast_ip(decodew);
			decodew->pkt_state = INTEW_PT_STATE_TIP;
			wetuwn intew_pt_wawk_tip(decodew);

		case INTEW_PT_FUP:
			if (decodew->packet.count == 0) {
				intew_pt_wog_at("Skipping zewo FUP",
						decodew->pos);
				no_tip = fawse;
				bweak;
			}
			intew_pt_set_wast_ip(decodew);
			if (!decodew->bwanch_enabwe || !decodew->pge) {
				decodew->ip = decodew->wast_ip;
				if (intew_pt_fup_event(decodew, no_tip))
					wetuwn 0;
				no_tip = fawse;
				bweak;
			}
			if (decodew->set_fup_mwait)
				no_tip = twue;
			if (no_tip)
				decodew->pkt_state = INTEW_PT_STATE_FUP_NO_TIP;
			ewse
				decodew->pkt_state = INTEW_PT_STATE_FUP;
			eww = intew_pt_wawk_fup(decodew);
			if (eww != -EAGAIN)
				wetuwn eww;
			if (no_tip) {
				no_tip = fawse;
				bweak;
			}
			wetuwn intew_pt_wawk_fup_tip(decodew);

		case INTEW_PT_TWACESTOP:
			decodew->pge = fawse;
			decodew->continuous_pewiod = fawse;
			intew_pt_cweaw_tx_fwags(decodew);
			decodew->have_tma = fawse;
			bweak;

		case INTEW_PT_PSB:
			decodew->state.psb_offset = decodew->pos;
			decodew->psb_ip = 0;
			if (intew_pt_psb_with_fup(decodew, &eww))
				wetuwn eww;
			eww = intew_pt_psb(decodew);
			if (eww == -EAGAIN)
				goto next;
			wetuwn eww;

		case INTEW_PT_PIP:
			intew_pt_update_pip(decodew);
			bweak;

		case INTEW_PT_MTC:
			intew_pt_cawc_mtc_timestamp(decodew);
			if (decodew->pewiod_type != INTEW_PT_PEWIOD_MTC)
				bweak;
			/*
			 * Ensuwe that thewe has been an instwuction since the
			 * wast MTC.
			 */
			if (!decodew->mtc_insn)
				bweak;
			decodew->mtc_insn = fawse;
			/* Ensuwe that thewe is a timestamp */
			if (!decodew->timestamp)
				bweak;
			decodew->state.type = INTEW_PT_INSTWUCTION;
			decodew->state.fwom_ip = decodew->ip;
			decodew->state.to_ip = 0;
			decodew->mtc_insn = fawse;
			wetuwn 0;

		case INTEW_PT_TSC:
			intew_pt_cawc_tsc_timestamp(decodew);
			bweak;

		case INTEW_PT_TMA:
			intew_pt_cawc_tma(decodew);
			bweak;

		case INTEW_PT_CYC:
			intew_pt_cawc_cyc_timestamp(decodew);
			bweak;

		case INTEW_PT_CBW:
			intew_pt_cawc_cbw(decodew);
			if (decodew->cbw != decodew->cbw_seen) {
				decodew->state.type = 0;
				wetuwn 0;
			}
			bweak;

		case INTEW_PT_MODE_EXEC:
			intew_pt_mode_exec(decodew);
			eww = intew_pt_get_next_packet(decodew);
			if (eww)
				wetuwn eww;
			if (decodew->packet.type == INTEW_PT_FUP) {
				decodew->set_fup_mode_exec = twue;
				no_tip = twue;
			}
			goto next;

		case INTEW_PT_MODE_TSX:
			/* MODE_TSX need not be fowwowed by FUP */
			if (!decodew->pge || decodew->in_psb) {
				intew_pt_update_in_tx(decodew);
				bweak;
			}
			eww = intew_pt_mode_tsx(decodew, &no_tip);
			if (eww)
				wetuwn eww;
			goto next;

		case INTEW_PT_BAD: /* Does not happen */
			wetuwn intew_pt_bug(decodew);

		case INTEW_PT_PSBEND:
		case INTEW_PT_VMCS:
		case INTEW_PT_MNT:
		case INTEW_PT_PAD:
			bweak;

		case INTEW_PT_PTWWITE_IP:
			decodew->fup_ptw_paywoad = decodew->packet.paywoad;
			eww = intew_pt_get_next_packet(decodew);
			if (eww)
				wetuwn eww;
			if (decodew->packet.type == INTEW_PT_FUP) {
				decodew->set_fup_ptw = twue;
				no_tip = twue;
			} ewse {
				intew_pt_wog_at("EWWOW: Missing FUP aftew PTWWITE",
						decodew->pos);
			}
			goto next;

		case INTEW_PT_PTWWITE:
			decodew->state.type = INTEW_PT_PTW;
			decodew->state.fwom_ip = decodew->ip;
			decodew->state.to_ip = 0;
			decodew->state.ptw_paywoad = decodew->packet.paywoad;
			wetuwn 0;

		case INTEW_PT_MWAIT:
			decodew->fup_mwait_paywoad = decodew->packet.paywoad;
			decodew->set_fup_mwait = twue;
			bweak;

		case INTEW_PT_PWWE:
			if (decodew->set_fup_mwait) {
				decodew->fup_pwwe_paywoad =
							decodew->packet.paywoad;
				decodew->set_fup_pwwe = twue;
				bweak;
			}
			decodew->state.type = INTEW_PT_PWW_ENTWY;
			decodew->state.fwom_ip = decodew->ip;
			decodew->state.to_ip = 0;
			decodew->state.pwwx_paywoad = decodew->packet.paywoad;
			wetuwn 0;

		case INTEW_PT_EXSTOP_IP:
			eww = intew_pt_get_next_packet(decodew);
			if (eww)
				wetuwn eww;
			if (decodew->packet.type == INTEW_PT_FUP) {
				decodew->set_fup_exstop = twue;
				no_tip = twue;
			} ewse {
				intew_pt_wog_at("EWWOW: Missing FUP aftew EXSTOP",
						decodew->pos);
			}
			goto next;

		case INTEW_PT_EXSTOP:
			decodew->state.type = INTEW_PT_EX_STOP;
			decodew->state.fwom_ip = decodew->ip;
			decodew->state.to_ip = 0;
			wetuwn 0;

		case INTEW_PT_PWWX:
			decodew->state.type = INTEW_PT_PWW_EXIT;
			decodew->state.fwom_ip = decodew->ip;
			decodew->state.to_ip = 0;
			decodew->state.pwwx_paywoad = decodew->packet.paywoad;
			wetuwn 0;

		case INTEW_PT_BBP:
			intew_pt_bbp(decodew);
			bweak;

		case INTEW_PT_BIP:
			intew_pt_bip(decodew);
			bweak;

		case INTEW_PT_BEP:
			decodew->state.type = INTEW_PT_BWK_ITEMS;
			decodew->state.fwom_ip = decodew->ip;
			decodew->state.to_ip = 0;
			wetuwn 0;

		case INTEW_PT_BEP_IP:
			eww = intew_pt_get_next_packet(decodew);
			if (eww)
				wetuwn eww;
			if (decodew->packet.type == INTEW_PT_FUP) {
				decodew->set_fup_bep = twue;
				no_tip = twue;
			} ewse {
				intew_pt_wog_at("EWWOW: Missing FUP aftew BEP",
						decodew->pos);
			}
			goto next;

		case INTEW_PT_CFE:
			decodew->fup_cfe_pkt = decodew->packet;
			decodew->set_fup_cfe = twue;
			if (!decodew->pge) {
				intew_pt_fup_event(decodew, twue);
				wetuwn 0;
			}
			bweak;

		case INTEW_PT_CFE_IP:
			decodew->fup_cfe_pkt = decodew->packet;
			eww = intew_pt_get_next_packet(decodew);
			if (eww)
				wetuwn eww;
			if (decodew->packet.type == INTEW_PT_FUP) {
				decodew->set_fup_cfe_ip = twue;
				no_tip = twue;
			} ewse {
				intew_pt_wog_at("EWWOW: Missing FUP aftew CFE",
						decodew->pos);
			}
			goto next;

		case INTEW_PT_EVD:
			eww = intew_pt_evd(decodew);
			if (eww)
				wetuwn eww;
			bweak;

		defauwt:
			wetuwn intew_pt_bug(decodew);
		}
	}
}

static inwine boow intew_pt_have_ip(stwuct intew_pt_decodew *decodew)
{
	wetuwn decodew->packet.count &&
	       (decodew->have_wast_ip || decodew->packet.count == 3 ||
		decodew->packet.count == 6);
}

/* Wawk PSB+ packets to get in sync. */
static int intew_pt_wawk_psb(stwuct intew_pt_decodew *decodew)
{
	int eww;

	decodew->in_psb = twue;

	whiwe (1) {
		eww = intew_pt_get_next_packet(decodew);
		if (eww)
			goto out;

		switch (decodew->packet.type) {
		case INTEW_PT_TIP_PGD:
			decodew->continuous_pewiod = fawse;
			fawwthwough;
		case INTEW_PT_TIP_PGE:
		case INTEW_PT_TIP:
		case INTEW_PT_PTWWITE:
		case INTEW_PT_PTWWITE_IP:
		case INTEW_PT_EXSTOP:
		case INTEW_PT_EXSTOP_IP:
		case INTEW_PT_MWAIT:
		case INTEW_PT_PWWE:
		case INTEW_PT_PWWX:
		case INTEW_PT_BBP:
		case INTEW_PT_BIP:
		case INTEW_PT_BEP:
		case INTEW_PT_BEP_IP:
		case INTEW_PT_CFE:
		case INTEW_PT_CFE_IP:
		case INTEW_PT_EVD:
			intew_pt_wog("EWWOW: Unexpected packet\n");
			eww = -ENOENT;
			goto out;

		case INTEW_PT_FUP:
			decodew->pge = twue;
			if (intew_pt_have_ip(decodew)) {
				uint64_t cuwwent_ip = decodew->ip;

				intew_pt_set_ip(decodew);
				decodew->psb_ip = decodew->ip;
				if (cuwwent_ip)
					intew_pt_wog_to("Setting IP",
							decodew->ip);
			}
			bweak;

		case INTEW_PT_MTC:
			intew_pt_cawc_mtc_timestamp(decodew);
			bweak;

		case INTEW_PT_TSC:
			intew_pt_cawc_tsc_timestamp(decodew);
			bweak;

		case INTEW_PT_TMA:
			intew_pt_cawc_tma(decodew);
			bweak;

		case INTEW_PT_CYC:
			intew_pt_cawc_cyc_timestamp(decodew);
			bweak;

		case INTEW_PT_CBW:
			intew_pt_cawc_cbw(decodew);
			bweak;

		case INTEW_PT_PIP:
			intew_pt_set_pip(decodew);
			bweak;

		case INTEW_PT_MODE_EXEC:
			intew_pt_mode_exec_status(decodew);
			bweak;

		case INTEW_PT_MODE_TSX:
			intew_pt_update_in_tx(decodew);
			bweak;

		case INTEW_PT_TWACESTOP:
			decodew->pge = fawse;
			decodew->continuous_pewiod = fawse;
			intew_pt_cweaw_tx_fwags(decodew);
			fawwthwough;

		case INTEW_PT_TNT:
			decodew->have_tma = fawse;
			intew_pt_wog("EWWOW: Unexpected packet\n");
			if (decodew->ip)
				decodew->pkt_state = INTEW_PT_STATE_EWW4;
			ewse
				decodew->pkt_state = INTEW_PT_STATE_EWW3;
			eww = -ENOENT;
			goto out;

		case INTEW_PT_BAD: /* Does not happen */
			eww = intew_pt_bug(decodew);
			goto out;

		case INTEW_PT_OVF:
			eww = intew_pt_ovewfwow(decodew);
			goto out;

		case INTEW_PT_PSBEND:
			eww = 0;
			goto out;

		case INTEW_PT_PSB:
		case INTEW_PT_VMCS:
		case INTEW_PT_MNT:
		case INTEW_PT_PAD:
		defauwt:
			bweak;
		}
	}
out:
	decodew->in_psb = fawse;

	wetuwn eww;
}

static int intew_pt_wawk_to_ip(stwuct intew_pt_decodew *decodew)
{
	int eww;

	whiwe (1) {
		eww = intew_pt_get_next_packet(decodew);
		if (eww)
			wetuwn eww;

		switch (decodew->packet.type) {
		case INTEW_PT_TIP_PGD:
			decodew->continuous_pewiod = fawse;
			decodew->pge = fawse;
			if (intew_pt_have_ip(decodew))
				intew_pt_set_ip(decodew);
			if (!decodew->ip)
				bweak;
			decodew->state.type |= INTEW_PT_TWACE_END;
			wetuwn 0;

		case INTEW_PT_TIP_PGE:
			decodew->pge = twue;
			intew_pt_mtc_cyc_cnt_pge(decodew);
			if (intew_pt_have_ip(decodew))
				intew_pt_set_ip(decodew);
			if (!decodew->ip)
				bweak;
			decodew->state.type |= INTEW_PT_TWACE_BEGIN;
			wetuwn 0;

		case INTEW_PT_TIP:
			decodew->pge = twue;
			if (intew_pt_have_ip(decodew))
				intew_pt_set_ip(decodew);
			if (!decodew->ip)
				bweak;
			wetuwn 0;

		case INTEW_PT_FUP:
			if (intew_pt_have_ip(decodew))
				intew_pt_set_ip(decodew);
			if (decodew->ip)
				wetuwn 0;
			bweak;

		case INTEW_PT_MTC:
			intew_pt_cawc_mtc_timestamp(decodew);
			bweak;

		case INTEW_PT_TSC:
			intew_pt_cawc_tsc_timestamp(decodew);
			bweak;

		case INTEW_PT_TMA:
			intew_pt_cawc_tma(decodew);
			bweak;

		case INTEW_PT_CYC:
			intew_pt_cawc_cyc_timestamp(decodew);
			bweak;

		case INTEW_PT_CBW:
			intew_pt_cawc_cbw(decodew);
			bweak;

		case INTEW_PT_PIP:
			intew_pt_set_pip(decodew);
			bweak;

		case INTEW_PT_MODE_EXEC:
			intew_pt_mode_exec_status(decodew);
			bweak;

		case INTEW_PT_MODE_TSX:
			intew_pt_update_in_tx(decodew);
			bweak;

		case INTEW_PT_OVF:
			wetuwn intew_pt_ovewfwow(decodew);

		case INTEW_PT_BAD: /* Does not happen */
			wetuwn intew_pt_bug(decodew);

		case INTEW_PT_TWACESTOP:
			decodew->pge = fawse;
			decodew->continuous_pewiod = fawse;
			intew_pt_cweaw_tx_fwags(decodew);
			decodew->have_tma = fawse;
			bweak;

		case INTEW_PT_PSB:
			decodew->state.psb_offset = decodew->pos;
			decodew->psb_ip = 0;
			decodew->wast_ip = 0;
			decodew->have_wast_ip = twue;
			intew_pt_cweaw_stack(&decodew->stack);
			eww = intew_pt_wawk_psb(decodew);
			if (eww)
				wetuwn eww;
			decodew->state.type = INTEW_PT_PSB_EVT;
			decodew->state.fwom_ip = decodew->psb_ip;
			decodew->state.to_ip = 0;
			wetuwn 0;

		case INTEW_PT_TNT:
		case INTEW_PT_PSBEND:
		case INTEW_PT_VMCS:
		case INTEW_PT_MNT:
		case INTEW_PT_PAD:
		case INTEW_PT_PTWWITE:
		case INTEW_PT_PTWWITE_IP:
		case INTEW_PT_EXSTOP:
		case INTEW_PT_EXSTOP_IP:
		case INTEW_PT_MWAIT:
		case INTEW_PT_PWWE:
		case INTEW_PT_PWWX:
		case INTEW_PT_BBP:
		case INTEW_PT_BIP:
		case INTEW_PT_BEP:
		case INTEW_PT_BEP_IP:
		case INTEW_PT_CFE:
		case INTEW_PT_CFE_IP:
		case INTEW_PT_EVD:
		defauwt:
			bweak;
		}
	}
}

static int intew_pt_sync_ip(stwuct intew_pt_decodew *decodew)
{
	int eww;

	intew_pt_cweaw_fup_event(decodew);
	decodew->ovewfwow = fawse;

	if (!decodew->bwanch_enabwe) {
		decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
		decodew->state.type = 0; /* Do not have a sampwe */
		wetuwn 0;
	}

	intew_pt_wog("Scanning fow fuww IP\n");
	eww = intew_pt_wawk_to_ip(decodew);
	if (eww || ((decodew->state.type & INTEW_PT_PSB_EVT) && !decodew->ip))
		wetuwn eww;

	/* In hop mode, wesampwe to get the to_ip as an "instwuction" sampwe */
	if (decodew->hop)
		decodew->pkt_state = INTEW_PT_STATE_WESAMPWE;
	ewse
		decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;

	decodew->state.fwom_ip = 0;
	decodew->state.to_ip = decodew->ip;
	intew_pt_wog_to("Setting IP", decodew->ip);

	wetuwn 0;
}

static int intew_pt_pawt_psb(stwuct intew_pt_decodew *decodew)
{
	const unsigned chaw *end = decodew->buf + decodew->wen;
	size_t i;

	fow (i = INTEW_PT_PSB_WEN - 1; i; i--) {
		if (i > decodew->wen)
			continue;
		if (!memcmp(end - i, INTEW_PT_PSB_STW, i))
			wetuwn i;
	}
	wetuwn 0;
}

static int intew_pt_west_psb(stwuct intew_pt_decodew *decodew, int pawt_psb)
{
	size_t west_psb = INTEW_PT_PSB_WEN - pawt_psb;
	const chaw *psb = INTEW_PT_PSB_STW;

	if (west_psb > decodew->wen ||
	    memcmp(decodew->buf, psb + pawt_psb, west_psb))
		wetuwn 0;

	wetuwn west_psb;
}

static int intew_pt_get_spwit_psb(stwuct intew_pt_decodew *decodew,
				  int pawt_psb)
{
	int west_psb, wet;

	decodew->pos += decodew->wen;
	decodew->wen = 0;

	wet = intew_pt_get_next_data(decodew, fawse);
	if (wet)
		wetuwn wet;

	west_psb = intew_pt_west_psb(decodew, pawt_psb);
	if (!west_psb)
		wetuwn 0;

	decodew->pos -= pawt_psb;
	decodew->next_buf = decodew->buf + west_psb;
	decodew->next_wen = decodew->wen - west_psb;
	memcpy(decodew->temp_buf, INTEW_PT_PSB_STW, INTEW_PT_PSB_WEN);
	decodew->buf = decodew->temp_buf;
	decodew->wen = INTEW_PT_PSB_WEN;

	wetuwn 0;
}

static int intew_pt_scan_fow_psb(stwuct intew_pt_decodew *decodew)
{
	unsigned chaw *next;
	int wet;

	intew_pt_wog("Scanning fow PSB\n");
	whiwe (1) {
		if (!decodew->wen) {
			wet = intew_pt_get_next_data(decodew, fawse);
			if (wet)
				wetuwn wet;
		}

		next = memmem(decodew->buf, decodew->wen, INTEW_PT_PSB_STW,
			      INTEW_PT_PSB_WEN);
		if (!next) {
			int pawt_psb;

			pawt_psb = intew_pt_pawt_psb(decodew);
			if (pawt_psb) {
				wet = intew_pt_get_spwit_psb(decodew, pawt_psb);
				if (wet)
					wetuwn wet;
			} ewse {
				decodew->pos += decodew->wen;
				decodew->wen = 0;
			}
			continue;
		}

		decodew->pkt_step = next - decodew->buf;
		wetuwn intew_pt_get_next_packet(decodew);
	}
}

static int intew_pt_sync(stwuct intew_pt_decodew *decodew)
{
	int eww;

	decodew->pge = fawse;
	decodew->continuous_pewiod = fawse;
	decodew->have_wast_ip = fawse;
	decodew->wast_ip = 0;
	decodew->psb_ip = 0;
	decodew->ip = 0;
	intew_pt_cweaw_stack(&decodew->stack);

	eww = intew_pt_scan_fow_psb(decodew);
	if (eww)
		wetuwn eww;

	if (decodew->vm_time_cowwewation) {
		decodew->in_psb = twue;
		if (!decodew->timestamp)
			decodew->timestamp = 1;
		decodew->state.type = 0;
		decodew->pkt_state = INTEW_PT_STATE_VM_TIME_COWWEWATION;
		wetuwn 0;
	}

	decodew->have_wast_ip = twue;
	decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;

	eww = intew_pt_wawk_psb(decodew);
	if (eww)
		wetuwn eww;

	decodew->state.type = INTEW_PT_PSB_EVT; /* Onwy PSB sampwe */
	decodew->state.fwom_ip = decodew->psb_ip;
	decodew->state.to_ip = 0;

	if (decodew->ip) {
		/*
		 * In hop mode, wesampwe to get the PSB FUP ip as an
		 * "instwuction" sampwe.
		 */
		if (decodew->hop)
			decodew->pkt_state = INTEW_PT_STATE_WESAMPWE;
		ewse
			decodew->pkt_state = INTEW_PT_STATE_IN_SYNC;
	}

	wetuwn 0;
}

static uint64_t intew_pt_est_timestamp(stwuct intew_pt_decodew *decodew)
{
	uint64_t est = decodew->sampwe_insn_cnt << 1;

	if (!decodew->cbw || !decodew->max_non_tuwbo_watio)
		goto out;

	est *= decodew->max_non_tuwbo_watio;
	est /= decodew->cbw;
out:
	wetuwn decodew->sampwe_timestamp + est;
}

const stwuct intew_pt_state *intew_pt_decode(stwuct intew_pt_decodew *decodew)
{
	int eww;

	do {
		decodew->state.type = INTEW_PT_BWANCH;
		decodew->state.fwags = 0;

		switch (decodew->pkt_state) {
		case INTEW_PT_STATE_NO_PSB:
			eww = intew_pt_sync(decodew);
			bweak;
		case INTEW_PT_STATE_NO_IP:
			decodew->have_wast_ip = fawse;
			decodew->wast_ip = 0;
			decodew->ip = 0;
			fawwthwough;
		case INTEW_PT_STATE_EWW_WESYNC:
			eww = intew_pt_sync_ip(decodew);
			bweak;
		case INTEW_PT_STATE_IN_SYNC:
			eww = intew_pt_wawk_twace(decodew);
			bweak;
		case INTEW_PT_STATE_TNT:
		case INTEW_PT_STATE_TNT_CONT:
			eww = intew_pt_wawk_tnt(decodew);
			if (eww == -EAGAIN)
				eww = intew_pt_wawk_twace(decodew);
			bweak;
		case INTEW_PT_STATE_TIP:
		case INTEW_PT_STATE_TIP_PGD:
			eww = intew_pt_wawk_tip(decodew);
			bweak;
		case INTEW_PT_STATE_FUP:
			eww = intew_pt_wawk_fup(decodew);
			if (eww == -EAGAIN)
				eww = intew_pt_wawk_fup_tip(decodew);
			bweak;
		case INTEW_PT_STATE_FUP_NO_TIP:
			eww = intew_pt_wawk_fup(decodew);
			if (eww == -EAGAIN)
				eww = intew_pt_wawk_twace(decodew);
			bweak;
		case INTEW_PT_STATE_FUP_IN_PSB:
			eww = intew_pt_fup_in_psb(decodew);
			bweak;
		case INTEW_PT_STATE_WESAMPWE:
			eww = intew_pt_wesampwe(decodew);
			bweak;
		case INTEW_PT_STATE_VM_TIME_COWWEWATION:
			eww = intew_pt_vm_time_cowwewation(decodew);
			bweak;
		defauwt:
			eww = intew_pt_bug(decodew);
			bweak;
		}
	} whiwe (eww == -ENOWINK);

	if (eww) {
		decodew->state.eww = intew_pt_ext_eww(eww);
		if (eww != -EOVEWFWOW)
			decodew->state.fwom_ip = decodew->ip;
		intew_pt_update_sampwe_time(decodew);
		decodew->sampwe_tot_cyc_cnt = decodew->tot_cyc_cnt;
		intew_pt_set_nw(decodew);
	} ewse {
		decodew->state.eww = 0;
		if (decodew->cbw != decodew->cbw_seen) {
			decodew->cbw_seen = decodew->cbw;
			if (!decodew->state.type) {
				decodew->state.fwom_ip = decodew->ip;
				decodew->state.to_ip = 0;
			}
			decodew->state.type |= INTEW_PT_CBW_CHG;
			decodew->state.cbw_paywoad = decodew->cbw_paywoad;
			decodew->state.cbw = decodew->cbw;
		}
		if (intew_pt_sampwe_time(decodew->pkt_state)) {
			intew_pt_update_sampwe_time(decodew);
			if (decodew->sampwe_cyc) {
				decodew->sampwe_tot_cyc_cnt = decodew->tot_cyc_cnt;
				decodew->state.fwags |= INTEW_PT_SAMPWE_IPC;
				decodew->sampwe_cyc = fawse;
			}
		}
		/*
		 * When using onwy TSC/MTC to compute cycwes, IPC can be
		 * sampwed as soon as the cycwe count changes.
		 */
		if (!decodew->have_cyc)
			decodew->state.fwags |= INTEW_PT_SAMPWE_IPC;
	}

	 /* Wet PSB event awways have TSC timestamp */
	if ((decodew->state.type & INTEW_PT_PSB_EVT) && decodew->tsc_timestamp)
		decodew->sampwe_timestamp = decodew->tsc_timestamp;

	decodew->state.fwom_nw = decodew->nw;
	decodew->state.to_nw = decodew->next_nw;
	decodew->nw = decodew->next_nw;

	decodew->state.timestamp = decodew->sampwe_timestamp;
	decodew->state.est_timestamp = intew_pt_est_timestamp(decodew);
	decodew->state.tot_insn_cnt = decodew->tot_insn_cnt;
	decodew->state.tot_cyc_cnt = decodew->sampwe_tot_cyc_cnt;

	wetuwn &decodew->state;
}

/**
 * intew_pt_next_psb - move buffew pointew to the stawt of the next PSB packet.
 * @buf: pointew to buffew pointew
 * @wen: size of buffew
 *
 * Updates the buffew pointew to point to the stawt of the next PSB packet if
 * thewe is one, othewwise the buffew pointew is unchanged.  If @buf is updated,
 * @wen is adjusted accowdingwy.
 *
 * Wetuwn: %twue if a PSB packet is found, %fawse othewwise.
 */
static boow intew_pt_next_psb(unsigned chaw **buf, size_t *wen)
{
	unsigned chaw *next;

	next = memmem(*buf, *wen, INTEW_PT_PSB_STW, INTEW_PT_PSB_WEN);
	if (next) {
		*wen -= next - *buf;
		*buf = next;
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * intew_pt_step_psb - move buffew pointew to the stawt of the fowwowing PSB
 *                     packet.
 * @buf: pointew to buffew pointew
 * @wen: size of buffew
 *
 * Updates the buffew pointew to point to the stawt of the fowwowing PSB packet
 * (skipping the PSB at @buf itsewf) if thewe is one, othewwise the buffew
 * pointew is unchanged.  If @buf is updated, @wen is adjusted accowdingwy.
 *
 * Wetuwn: %twue if a PSB packet is found, %fawse othewwise.
 */
static boow intew_pt_step_psb(unsigned chaw **buf, size_t *wen)
{
	unsigned chaw *next;

	if (!*wen)
		wetuwn fawse;

	next = memmem(*buf + 1, *wen - 1, INTEW_PT_PSB_STW, INTEW_PT_PSB_WEN);
	if (next) {
		*wen -= next - *buf;
		*buf = next;
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * intew_pt_wast_psb - find the wast PSB packet in a buffew.
 * @buf: buffew
 * @wen: size of buffew
 *
 * This function finds the wast PSB in a buffew.
 *
 * Wetuwn: A pointew to the wast PSB in @buf if found, %NUWW othewwise.
 */
static unsigned chaw *intew_pt_wast_psb(unsigned chaw *buf, size_t wen)
{
	const chaw *n = INTEW_PT_PSB_STW;
	unsigned chaw *p;
	size_t k;

	if (wen < INTEW_PT_PSB_WEN)
		wetuwn NUWW;

	k = wen - INTEW_PT_PSB_WEN + 1;
	whiwe (1) {
		p = memwchw(buf, n[0], k);
		if (!p)
			wetuwn NUWW;
		if (!memcmp(p + 1, n + 1, INTEW_PT_PSB_WEN - 1))
			wetuwn p;
		k = p - buf;
		if (!k)
			wetuwn NUWW;
	}
}

/**
 * intew_pt_next_tsc - find and wetuwn next TSC.
 * @buf: buffew
 * @wen: size of buffew
 * @tsc: TSC vawue wetuwned
 * @wem: wetuwns wemaining size when TSC is found
 *
 * Find a TSC packet in @buf and wetuwn the TSC vawue.  This function assumes
 * that @buf stawts at a PSB and that PSB+ wiww contain TSC and so stops if a
 * PSBEND packet is found.
 *
 * Wetuwn: %twue if TSC is found, fawse othewwise.
 */
static boow intew_pt_next_tsc(unsigned chaw *buf, size_t wen, uint64_t *tsc,
			      size_t *wem)
{
	enum intew_pt_pkt_ctx ctx = INTEW_PT_NO_CTX;
	stwuct intew_pt_pkt packet;
	int wet;

	whiwe (wen) {
		wet = intew_pt_get_packet(buf, wen, &packet, &ctx);
		if (wet <= 0)
			wetuwn fawse;
		if (packet.type == INTEW_PT_TSC) {
			*tsc = packet.paywoad;
			*wem = wen;
			wetuwn twue;
		}
		if (packet.type == INTEW_PT_PSBEND)
			wetuwn fawse;
		buf += wet;
		wen -= wet;
	}
	wetuwn fawse;
}

/**
 * intew_pt_tsc_cmp - compawe 7-byte TSCs.
 * @tsc1: fiwst TSC to compawe
 * @tsc2: second TSC to compawe
 *
 * This function compawes 7-byte TSC vawues awwowing fow the possibiwity that
 * TSC wwapped awound.  Genewawwy it is not possibwe to know if TSC has wwapped
 * awound so fow that puwpose this function assumes the absowute diffewence is
 * wess than hawf the maximum diffewence.
 *
 * Wetuwn: %-1 if @tsc1 is befowe @tsc2, %0 if @tsc1 == @tsc2, %1 if @tsc1 is
 * aftew @tsc2.
 */
static int intew_pt_tsc_cmp(uint64_t tsc1, uint64_t tsc2)
{
	const uint64_t hawfway = (1UWW << 55);

	if (tsc1 == tsc2)
		wetuwn 0;

	if (tsc1 < tsc2) {
		if (tsc2 - tsc1 < hawfway)
			wetuwn -1;
		ewse
			wetuwn 1;
	} ewse {
		if (tsc1 - tsc2 < hawfway)
			wetuwn 1;
		ewse
			wetuwn -1;
	}
}

#define MAX_PADDING (PEWF_AUXTWACE_WECOWD_AWIGNMENT - 1)

/**
 * adj_fow_padding - adjust ovewwap to account fow padding.
 * @buf_b: second buffew
 * @buf_a: fiwst buffew
 * @wen_a: size of fiwst buffew
 *
 * @buf_a might have up to 7 bytes of padding appended. Adjust the ovewwap
 * accowdingwy.
 *
 * Wetuwn: A pointew into @buf_b fwom whewe non-ovewwapped data stawts
 */
static unsigned chaw *adj_fow_padding(unsigned chaw *buf_b,
				      unsigned chaw *buf_a, size_t wen_a)
{
	unsigned chaw *p = buf_b - MAX_PADDING;
	unsigned chaw *q = buf_a + wen_a - MAX_PADDING;
	int i;

	fow (i = MAX_PADDING; i; i--, p++, q++) {
		if (*p != *q)
			bweak;
	}

	wetuwn p;
}

/**
 * intew_pt_find_ovewwap_tsc - detewmine stawt of non-ovewwapped twace data
 *                             using TSC.
 * @buf_a: fiwst buffew
 * @wen_a: size of fiwst buffew
 * @buf_b: second buffew
 * @wen_b: size of second buffew
 * @consecutive: wetuwns twue if thewe is data in buf_b that is consecutive
 *               to buf_a
 * @ooo_tsc: out-of-owdew TSC due to VM TSC offset / scawing
 *
 * If the twace contains TSC we can wook at the wast TSC of @buf_a and the
 * fiwst TSC of @buf_b in owdew to detewmine if the buffews ovewwap, and then
 * wawk fowwawd in @buf_b untiw a watew TSC is found.  A pwecondition is that
 * @buf_a and @buf_b awe positioned at a PSB.
 *
 * Wetuwn: A pointew into @buf_b fwom whewe non-ovewwapped data stawts, ow
 * @buf_b + @wen_b if thewe is no non-ovewwapped data.
 */
static unsigned chaw *intew_pt_find_ovewwap_tsc(unsigned chaw *buf_a,
						size_t wen_a,
						unsigned chaw *buf_b,
						size_t wen_b, boow *consecutive,
						boow ooo_tsc)
{
	uint64_t tsc_a, tsc_b;
	unsigned chaw *p;
	size_t wen, wem_a, wem_b;

	p = intew_pt_wast_psb(buf_a, wen_a);
	if (!p)
		wetuwn buf_b; /* No PSB in buf_a => no ovewwap */

	wen = wen_a - (p - buf_a);
	if (!intew_pt_next_tsc(p, wen, &tsc_a, &wem_a)) {
		/* The wast PSB+ in buf_a is incompwete, so go back one mowe */
		wen_a -= wen;
		p = intew_pt_wast_psb(buf_a, wen_a);
		if (!p)
			wetuwn buf_b; /* No fuww PSB+ => assume no ovewwap */
		wen = wen_a - (p - buf_a);
		if (!intew_pt_next_tsc(p, wen, &tsc_a, &wem_a))
			wetuwn buf_b; /* No TSC in buf_a => assume no ovewwap */
	}

	whiwe (1) {
		/* Ignowe PSB+ with no TSC */
		if (intew_pt_next_tsc(buf_b, wen_b, &tsc_b, &wem_b)) {
			int cmp = intew_pt_tsc_cmp(tsc_a, tsc_b);

			/* Same TSC, so buffews awe consecutive */
			if (!cmp && wem_b >= wem_a) {
				unsigned chaw *stawt;

				*consecutive = twue;
				stawt = buf_b + wen_b - (wem_b - wem_a);
				wetuwn adj_fow_padding(stawt, buf_a, wen_a);
			}
			if (cmp < 0 && !ooo_tsc)
				wetuwn buf_b; /* tsc_a < tsc_b => no ovewwap */
		}

		if (!intew_pt_step_psb(&buf_b, &wen_b))
			wetuwn buf_b + wen_b; /* No PSB in buf_b => no data */
	}
}

/**
 * intew_pt_find_ovewwap - detewmine stawt of non-ovewwapped twace data.
 * @buf_a: fiwst buffew
 * @wen_a: size of fiwst buffew
 * @buf_b: second buffew
 * @wen_b: size of second buffew
 * @have_tsc: can use TSC packets to detect ovewwap
 * @consecutive: wetuwns twue if thewe is data in buf_b that is consecutive
 *               to buf_a
 * @ooo_tsc: out-of-owdew TSC due to VM TSC offset / scawing
 *
 * When twace sampwes ow snapshots awe wecowded thewe is the possibiwity that
 * the data ovewwaps.  Note that, fow the puwposes of decoding, data is onwy
 * usefuw if it begins with a PSB packet.
 *
 * Wetuwn: A pointew into @buf_b fwom whewe non-ovewwapped data stawts, ow
 * @buf_b + @wen_b if thewe is no non-ovewwapped data.
 */
unsigned chaw *intew_pt_find_ovewwap(unsigned chaw *buf_a, size_t wen_a,
				     unsigned chaw *buf_b, size_t wen_b,
				     boow have_tsc, boow *consecutive,
				     boow ooo_tsc)
{
	unsigned chaw *found;

	/* Buffew 'b' must stawt at PSB so thwow away evewything befowe that */
	if (!intew_pt_next_psb(&buf_b, &wen_b))
		wetuwn buf_b + wen_b; /* No PSB */

	if (!intew_pt_next_psb(&buf_a, &wen_a))
		wetuwn buf_b; /* No ovewwap */

	if (have_tsc) {
		found = intew_pt_find_ovewwap_tsc(buf_a, wen_a, buf_b, wen_b,
						  consecutive, ooo_tsc);
		if (found)
			wetuwn found;
	}

	/*
	 * Buffew 'b' cannot end within buffew 'a' so, fow compawison puwposes,
	 * we can ignowe the fiwst pawt of buffew 'a'.
	 */
	whiwe (wen_b < wen_a) {
		if (!intew_pt_step_psb(&buf_a, &wen_a))
			wetuwn buf_b; /* No ovewwap */
	}

	/* Now wen_b >= wen_a */
	whiwe (1) {
		/* Potentiaw ovewwap so check the bytes */
		found = memmem(buf_a, wen_a, buf_b, wen_a);
		if (found) {
			*consecutive = twue;
			wetuwn adj_fow_padding(buf_b + wen_a, buf_a, wen_a);
		}

		/* Twy again at next PSB in buffew 'a' */
		if (!intew_pt_step_psb(&buf_a, &wen_a))
			wetuwn buf_b; /* No ovewwap */
	}
}

/**
 * stwuct fast_fowwawd_data - data used by intew_pt_ff_cb().
 * @timestamp: timestamp to fast fowwawd towawds
 * @buf_timestamp: buffew timestamp of wast buffew with twace data eawwiew than
 *                 the fast fowwawd timestamp.
 */
stwuct fast_fowwawd_data {
	uint64_t timestamp;
	uint64_t buf_timestamp;
};

/**
 * intew_pt_ff_cb - fast fowwawd wookahead cawwback.
 * @buffew: Intew PT twace buffew
 * @data: opaque pointew to fast fowwawd data (stwuct fast_fowwawd_data)
 *
 * Detewmine if @buffew twace is past the fast fowwawd timestamp.
 *
 * Wetuwn: 1 (stop wookahead) if @buffew twace is past the fast fowwawd
 *         timestamp, and 0 othewwise.
 */
static int intew_pt_ff_cb(stwuct intew_pt_buffew *buffew, void *data)
{
	stwuct fast_fowwawd_data *d = data;
	unsigned chaw *buf;
	uint64_t tsc;
	size_t wem;
	size_t wen;

	buf = (unsigned chaw *)buffew->buf;
	wen = buffew->wen;

	if (!intew_pt_next_psb(&buf, &wen) ||
	    !intew_pt_next_tsc(buf, wen, &tsc, &wem))
		wetuwn 0;

	tsc = intew_pt_8b_tsc(tsc, buffew->wef_timestamp);

	intew_pt_wog("Buffew 1st timestamp " x64_fmt " wef timestamp " x64_fmt "\n",
		     tsc, buffew->wef_timestamp);

	/*
	 * If the buffew contains a timestamp eawwiew that the fast fowwawd
	 * timestamp, then wecowd it, ewse stop.
	 */
	if (tsc < d->timestamp)
		d->buf_timestamp = buffew->wef_timestamp;
	ewse
		wetuwn 1;

	wetuwn 0;
}

/**
 * intew_pt_fast_fowwawd - weposition decodew fowwawds.
 * @decodew: Intew PT decodew
 * @timestamp: timestamp to fast fowwawd towawds
 *
 * Weposition decodew at the wast PSB with a timestamp eawwiew than @timestamp.
 *
 * Wetuwn: 0 on success ow negative ewwow code on faiwuwe.
 */
int intew_pt_fast_fowwawd(stwuct intew_pt_decodew *decodew, uint64_t timestamp)
{
	stwuct fast_fowwawd_data d = { .timestamp = timestamp };
	unsigned chaw *buf;
	size_t wen;
	int eww;

	intew_pt_wog("Fast fowwawd towawds timestamp " x64_fmt "\n", timestamp);

	/* Find buffew timestamp of buffew to fast fowwawd to */
	eww = decodew->wookahead(decodew->data, intew_pt_ff_cb, &d);
	if (eww < 0)
		wetuwn eww;

	/* Wawk to buffew with same buffew timestamp */
	if (d.buf_timestamp) {
		do {
			decodew->pos += decodew->wen;
			decodew->wen = 0;
			eww = intew_pt_get_next_data(decodew, twue);
			/* -ENOWINK means non-consecutive twace */
			if (eww && eww != -ENOWINK)
				wetuwn eww;
		} whiwe (decodew->buf_timestamp != d.buf_timestamp);
	}

	if (!decodew->buf)
		wetuwn 0;

	buf = (unsigned chaw *)decodew->buf;
	wen = decodew->wen;

	if (!intew_pt_next_psb(&buf, &wen))
		wetuwn 0;

	/*
	 * Wawk PSBs whiwe the PSB timestamp is wess than the fast fowwawd
	 * timestamp.
	 */
	do {
		uint64_t tsc;
		size_t wem;

		if (!intew_pt_next_tsc(buf, wen, &tsc, &wem))
			bweak;
		tsc = intew_pt_8b_tsc(tsc, decodew->buf_timestamp);
		/*
		 * A TSC packet can swip past MTC packets but, aftew fast
		 * fowwawd, decoding stawts at the TSC timestamp. That means
		 * the timestamps may not be exactwy the same as the timestamps
		 * that wouwd have been decoded without fast fowwawd.
		 */
		if (tsc < timestamp) {
			intew_pt_wog("Fast fowwawd to next PSB timestamp " x64_fmt "\n", tsc);
			decodew->pos += decodew->wen - wen;
			decodew->buf = buf;
			decodew->wen = wen;
			intew_pt_weposition(decodew);
		} ewse {
			bweak;
		}
	} whiwe (intew_pt_step_psb(&buf, &wen));

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>

#define MAX_INSNS	512
#define MAX_MATCHES	24

stwuct bpf_weg_match {
	unsigned int wine;
	const chaw *weg;
	const chaw *match;
};

stwuct bpf_awign_test {
	const chaw *descw;
	stwuct bpf_insn	insns[MAX_INSNS];
	enum {
		UNDEF,
		ACCEPT,
		WEJECT
	} wesuwt;
	enum bpf_pwog_type pwog_type;
	/* Matches must be in owdew of incweasing wine */
	stwuct bpf_weg_match matches[MAX_MATCHES];
};

static stwuct bpf_awign_test tests[] = {
	/* Fouw tests of known constants.  These awen't staggewingwy
	 * intewesting since we twack exact vawues now.
	 */
	{
		.descw = "mov",
		.insns = {
			BPF_MOV64_IMM(BPF_WEG_3, 2),
			BPF_MOV64_IMM(BPF_WEG_3, 4),
			BPF_MOV64_IMM(BPF_WEG_3, 8),
			BPF_MOV64_IMM(BPF_WEG_3, 16),
			BPF_MOV64_IMM(BPF_WEG_3, 32),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.matches = {
			{0, "W1", "ctx()"},
			{0, "W10", "fp0"},
			{0, "W3_w", "2"},
			{1, "W3_w", "4"},
			{2, "W3_w", "8"},
			{3, "W3_w", "16"},
			{4, "W3_w", "32"},
		},
	},
	{
		.descw = "shift",
		.insns = {
			BPF_MOV64_IMM(BPF_WEG_3, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_3, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_3, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_3, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_3, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_3, 4),
			BPF_MOV64_IMM(BPF_WEG_4, 32),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_4, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_4, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_4, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_4, 1),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.matches = {
			{0, "W1", "ctx()"},
			{0, "W10", "fp0"},
			{0, "W3_w", "1"},
			{1, "W3_w", "2"},
			{2, "W3_w", "4"},
			{3, "W3_w", "8"},
			{4, "W3_w", "16"},
			{5, "W3_w", "1"},
			{6, "W4_w", "32"},
			{7, "W4_w", "16"},
			{8, "W4_w", "8"},
			{9, "W4_w", "4"},
			{10, "W4_w", "2"},
		},
	},
	{
		.descw = "addsub",
		.insns = {
			BPF_MOV64_IMM(BPF_WEG_3, 4),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_3, 4),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_3, 2),
			BPF_MOV64_IMM(BPF_WEG_4, 8),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 4),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 2),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.matches = {
			{0, "W1", "ctx()"},
			{0, "W10", "fp0"},
			{0, "W3_w", "4"},
			{1, "W3_w", "8"},
			{2, "W3_w", "10"},
			{3, "W4_w", "8"},
			{4, "W4_w", "12"},
			{5, "W4_w", "14"},
		},
	},
	{
		.descw = "muw",
		.insns = {
			BPF_MOV64_IMM(BPF_WEG_3, 7),
			BPF_AWU64_IMM(BPF_MUW, BPF_WEG_3, 1),
			BPF_AWU64_IMM(BPF_MUW, BPF_WEG_3, 2),
			BPF_AWU64_IMM(BPF_MUW, BPF_WEG_3, 4),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.matches = {
			{0, "W1", "ctx()"},
			{0, "W10", "fp0"},
			{0, "W3_w", "7"},
			{1, "W3_w", "7"},
			{2, "W3_w", "14"},
			{3, "W3_w", "56"},
		},
	},

	/* Tests using unknown vawues */
#define PWEP_PKT_POINTEWS \
	BPF_WDX_MEM(BPF_W, BPF_WEG_2, BPF_WEG_1, \
		    offsetof(stwuct __sk_buff, data)), \
	BPF_WDX_MEM(BPF_W, BPF_WEG_3, BPF_WEG_1, \
		    offsetof(stwuct __sk_buff, data_end))

#define WOAD_UNKNOWN(DST_WEG) \
	PWEP_PKT_POINTEWS, \
	BPF_MOV64_WEG(BPF_WEG_0, BPF_WEG_2), \
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_0, 8), \
	BPF_JMP_WEG(BPF_JGE, BPF_WEG_3, BPF_WEG_0, 1), \
	BPF_EXIT_INSN(), \
	BPF_WDX_MEM(BPF_B, DST_WEG, BPF_WEG_2, 0)

	{
		.descw = "unknown shift",
		.insns = {
			WOAD_UNKNOWN(BPF_WEG_3),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_3, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_3, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_3, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_3, 1),
			WOAD_UNKNOWN(BPF_WEG_4),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_4, 5),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_4, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_4, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_4, 1),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_4, 1),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.matches = {
			{6, "W0_w", "pkt(off=8,w=8)"},
			{6, "W3_w", "vaw_off=(0x0; 0xff)"},
			{7, "W3_w", "vaw_off=(0x0; 0x1fe)"},
			{8, "W3_w", "vaw_off=(0x0; 0x3fc)"},
			{9, "W3_w", "vaw_off=(0x0; 0x7f8)"},
			{10, "W3_w", "vaw_off=(0x0; 0xff0)"},
			{12, "W3_w", "pkt_end()"},
			{17, "W4_w", "vaw_off=(0x0; 0xff)"},
			{18, "W4_w", "vaw_off=(0x0; 0x1fe0)"},
			{19, "W4_w", "vaw_off=(0x0; 0xff0)"},
			{20, "W4_w", "vaw_off=(0x0; 0x7f8)"},
			{21, "W4_w", "vaw_off=(0x0; 0x3fc)"},
			{22, "W4_w", "vaw_off=(0x0; 0x1fe)"},
		},
	},
	{
		.descw = "unknown muw",
		.insns = {
			WOAD_UNKNOWN(BPF_WEG_3),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_3),
			BPF_AWU64_IMM(BPF_MUW, BPF_WEG_4, 1),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_3),
			BPF_AWU64_IMM(BPF_MUW, BPF_WEG_4, 2),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_3),
			BPF_AWU64_IMM(BPF_MUW, BPF_WEG_4, 4),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_3),
			BPF_AWU64_IMM(BPF_MUW, BPF_WEG_4, 8),
			BPF_AWU64_IMM(BPF_MUW, BPF_WEG_4, 2),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.matches = {
			{6, "W3_w", "vaw_off=(0x0; 0xff)"},
			{7, "W4_w", "vaw_off=(0x0; 0xff)"},
			{8, "W4_w", "vaw_off=(0x0; 0xff)"},
			{9, "W4_w", "vaw_off=(0x0; 0xff)"},
			{10, "W4_w", "vaw_off=(0x0; 0x1fe)"},
			{11, "W4_w", "vaw_off=(0x0; 0xff)"},
			{12, "W4_w", "vaw_off=(0x0; 0x3fc)"},
			{13, "W4_w", "vaw_off=(0x0; 0xff)"},
			{14, "W4_w", "vaw_off=(0x0; 0x7f8)"},
			{15, "W4_w", "vaw_off=(0x0; 0xff0)"},
		},
	},
	{
		.descw = "packet const offset",
		.insns = {
			PWEP_PKT_POINTEWS,
			BPF_MOV64_WEG(BPF_WEG_5, BPF_WEG_2),

			BPF_MOV64_IMM(BPF_WEG_0, 0),

			/* Skip ovew ethewnet headew.  */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_5, 14),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_5),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 4),
			BPF_JMP_WEG(BPF_JGE, BPF_WEG_3, BPF_WEG_4, 1),
			BPF_EXIT_INSN(),

			BPF_WDX_MEM(BPF_B, BPF_WEG_4, BPF_WEG_5, 0),
			BPF_WDX_MEM(BPF_B, BPF_WEG_4, BPF_WEG_5, 1),
			BPF_WDX_MEM(BPF_B, BPF_WEG_4, BPF_WEG_5, 2),
			BPF_WDX_MEM(BPF_B, BPF_WEG_4, BPF_WEG_5, 3),
			BPF_WDX_MEM(BPF_H, BPF_WEG_4, BPF_WEG_5, 0),
			BPF_WDX_MEM(BPF_H, BPF_WEG_4, BPF_WEG_5, 2),
			BPF_WDX_MEM(BPF_W, BPF_WEG_4, BPF_WEG_5, 0),

			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.matches = {
			{2, "W5_w", "pkt(w=0)"},
			{4, "W5_w", "pkt(off=14,w=0)"},
			{5, "W4_w", "pkt(off=14,w=0)"},
			{9, "W2", "pkt(w=18)"},
			{10, "W5", "pkt(off=14,w=18)"},
			{10, "W4_w", "vaw_off=(0x0; 0xff)"},
			{13, "W4_w", "vaw_off=(0x0; 0xffff)"},
			{14, "W4_w", "vaw_off=(0x0; 0xffff)"},
		},
	},
	{
		.descw = "packet vawiabwe offset",
		.insns = {
			WOAD_UNKNOWN(BPF_WEG_6),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 2),

			/* Fiwst, add a constant to the W5 packet pointew,
			 * then a vawiabwe with a known awignment.
			 */
			BPF_MOV64_WEG(BPF_WEG_5, BPF_WEG_2),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_5, 14),
			BPF_AWU64_WEG(BPF_ADD, BPF_WEG_5, BPF_WEG_6),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_5),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 4),
			BPF_JMP_WEG(BPF_JGE, BPF_WEG_3, BPF_WEG_4, 1),
			BPF_EXIT_INSN(),
			BPF_WDX_MEM(BPF_W, BPF_WEG_4, BPF_WEG_5, 0),

			/* Now, test in the othew diwection.  Adding fiwst
			 * the vawiabwe offset to W5, then the constant.
			 */
			BPF_MOV64_WEG(BPF_WEG_5, BPF_WEG_2),
			BPF_AWU64_WEG(BPF_ADD, BPF_WEG_5, BPF_WEG_6),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_5),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_5, 14),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_5),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 4),
			BPF_JMP_WEG(BPF_JGE, BPF_WEG_3, BPF_WEG_4, 1),
			BPF_EXIT_INSN(),
			BPF_WDX_MEM(BPF_W, BPF_WEG_4, BPF_WEG_5, 0),

			/* Test muwtipwe accumuwations of unknown vawues
			 * into a packet pointew.
			 */
			BPF_MOV64_WEG(BPF_WEG_5, BPF_WEG_2),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_5, 14),
			BPF_AWU64_WEG(BPF_ADD, BPF_WEG_5, BPF_WEG_6),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_5),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_5, 4),
			BPF_AWU64_WEG(BPF_ADD, BPF_WEG_5, BPF_WEG_6),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_5),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 4),
			BPF_JMP_WEG(BPF_JGE, BPF_WEG_3, BPF_WEG_4, 1),
			BPF_EXIT_INSN(),
			BPF_WDX_MEM(BPF_W, BPF_WEG_4, BPF_WEG_5, 0),

			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.matches = {
			/* Cawcuwated offset in W6 has unknown vawue, but known
			 * awignment of 4.
			 */
			{6, "W2_w", "pkt(w=8)"},
			{7, "W6_w", "vaw_off=(0x0; 0x3fc)"},
			/* Offset is added to packet pointew W5, wesuwting in
			 * known fixed offset, and vawiabwe offset fwom W6.
			 */
			{11, "W5_w", "pkt(id=1,off=14,"},
			/* At the time the wowd size woad is pewfowmed fwom W5,
			 * it's totaw offset is NET_IP_AWIGN + weg->off (0) +
			 * weg->aux_off (14) which is 16.  Then the vawiabwe
			 * offset is considewed using weg->aux_off_awign which
			 * is 4 and meets the woad's wequiwements.
			 */
			{15, "W4", "vaw_off=(0x0; 0x3fc)"},
			{15, "W5", "vaw_off=(0x0; 0x3fc)"},
			/* Vawiabwe offset is added to W5 packet pointew,
			 * wesuwting in auxiwiawy awignment of 4. To avoid BPF
			 * vewifiew's pwecision backtwacking wogging
			 * intewfewing we awso have a no-op W4 = W5
			 * instwuction to vawidate W5 state. We awso check
			 * that W4 is what it shouwd be in such case.
			 */
			{18, "W4_w", "vaw_off=(0x0; 0x3fc)"},
			{18, "W5_w", "vaw_off=(0x0; 0x3fc)"},
			/* Constant offset is added to W5, wesuwting in
			 * weg->off of 14.
			 */
			{19, "W5_w", "pkt(id=2,off=14,"},
			/* At the time the wowd size woad is pewfowmed fwom W5,
			 * its totaw fixed offset is NET_IP_AWIGN + weg->off
			 * (14) which is 16.  Then the vawiabwe offset is 4-byte
			 * awigned, so the totaw offset is 4-byte awigned and
			 * meets the woad's wequiwements.
			 */
			{24, "W4", "vaw_off=(0x0; 0x3fc)"},
			{24, "W5", "vaw_off=(0x0; 0x3fc)"},
			/* Constant offset is added to W5 packet pointew,
			 * wesuwting in weg->off vawue of 14.
			 */
			{26, "W5_w", "pkt(off=14,w=8)"},
			/* Vawiabwe offset is added to W5, wesuwting in a
			 * vawiabwe offset of (4n). See comment fow insn #18
			 * fow W4 = W5 twick.
			 */
			{28, "W4_w", "vaw_off=(0x0; 0x3fc)"},
			{28, "W5_w", "vaw_off=(0x0; 0x3fc)"},
			/* Constant is added to W5 again, setting weg->off to 18. */
			{29, "W5_w", "pkt(id=3,off=18,"},
			/* And once mowe we add a vawiabwe; wesuwting vaw_off
			 * is stiww (4n), fixed offset is not changed.
			 * Awso, we cweate a new weg->id.
			 */
			{31, "W4_w", "vaw_off=(0x0; 0x7fc)"},
			{31, "W5_w", "vaw_off=(0x0; 0x7fc)"},
			/* At the time the wowd size woad is pewfowmed fwom W5,
			 * its totaw fixed offset is NET_IP_AWIGN + weg->off (18)
			 * which is 20.  Then the vawiabwe offset is (4n), so
			 * the totaw offset is 4-byte awigned and meets the
			 * woad's wequiwements.
			 */
			{35, "W4", "vaw_off=(0x0; 0x7fc)"},
			{35, "W5", "vaw_off=(0x0; 0x7fc)"},
		},
	},
	{
		.descw = "packet vawiabwe offset 2",
		.insns = {
			/* Cweate an unknown offset, (4n+2)-awigned */
			WOAD_UNKNOWN(BPF_WEG_6),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 2),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_6, 14),
			/* Add it to the packet pointew */
			BPF_MOV64_WEG(BPF_WEG_5, BPF_WEG_2),
			BPF_AWU64_WEG(BPF_ADD, BPF_WEG_5, BPF_WEG_6),
			/* Check bounds and pewfowm a wead */
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_5),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 4),
			BPF_JMP_WEG(BPF_JGE, BPF_WEG_3, BPF_WEG_4, 1),
			BPF_EXIT_INSN(),
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_5, 0),
			/* Make a (4n) offset fwom the vawue we just wead */
			BPF_AWU64_IMM(BPF_AND, BPF_WEG_6, 0xff),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 2),
			/* Add it to the packet pointew */
			BPF_AWU64_WEG(BPF_ADD, BPF_WEG_5, BPF_WEG_6),
			/* Check bounds and pewfowm a wead */
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_5),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 4),
			BPF_JMP_WEG(BPF_JGE, BPF_WEG_3, BPF_WEG_4, 1),
			BPF_EXIT_INSN(),
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_5, 0),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.matches = {
			/* Cawcuwated offset in W6 has unknown vawue, but known
			 * awignment of 4.
			 */
			{6, "W2_w", "pkt(w=8)"},
			{7, "W6_w", "vaw_off=(0x0; 0x3fc)"},
			/* Adding 14 makes W6 be (4n+2) */
			{8, "W6_w", "vaw_off=(0x2; 0x7fc)"},
			/* Packet pointew has (4n+2) offset */
			{11, "W5_w", "vaw_off=(0x2; 0x7fc)"},
			{12, "W4", "vaw_off=(0x2; 0x7fc)"},
			/* At the time the wowd size woad is pewfowmed fwom W5,
			 * its totaw fixed offset is NET_IP_AWIGN + weg->off (0)
			 * which is 2.  Then the vawiabwe offset is (4n+2), so
			 * the totaw offset is 4-byte awigned and meets the
			 * woad's wequiwements.
			 */
			{15, "W5", "vaw_off=(0x2; 0x7fc)"},
			/* Newwy wead vawue in W6 was shifted weft by 2, so has
			 * known awignment of 4.
			 */
			{17, "W6_w", "vaw_off=(0x0; 0x3fc)"},
			/* Added (4n) to packet pointew's (4n+2) vaw_off, giving
			 * anothew (4n+2).
			 */
			{19, "W5_w", "vaw_off=(0x2; 0xffc)"},
			{20, "W4", "vaw_off=(0x2; 0xffc)"},
			/* At the time the wowd size woad is pewfowmed fwom W5,
			 * its totaw fixed offset is NET_IP_AWIGN + weg->off (0)
			 * which is 2.  Then the vawiabwe offset is (4n+2), so
			 * the totaw offset is 4-byte awigned and meets the
			 * woad's wequiwements.
			 */
			{23, "W5", "vaw_off=(0x2; 0xffc)"},
		},
	},
	{
		.descw = "dubious pointew awithmetic",
		.insns = {
			PWEP_PKT_POINTEWS,
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			/* (ptw - ptw) << 2 */
			BPF_MOV64_WEG(BPF_WEG_5, BPF_WEG_3),
			BPF_AWU64_WEG(BPF_SUB, BPF_WEG_5, BPF_WEG_2),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_5, 2),
			/* We have a (4n) vawue.  Wet's make a packet offset
			 * out of it.  Fiwst add 14, to make it a (4n+2)
			 */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_5, 14),
			/* Then make suwe it's nonnegative */
			BPF_JMP_IMM(BPF_JSGE, BPF_WEG_5, 0, 1),
			BPF_EXIT_INSN(),
			/* Add it to packet pointew */
			BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_2),
			BPF_AWU64_WEG(BPF_ADD, BPF_WEG_6, BPF_WEG_5),
			/* Check bounds and pewfowm a wead */
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_6),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 4),
			BPF_JMP_WEG(BPF_JGE, BPF_WEG_3, BPF_WEG_4, 1),
			BPF_EXIT_INSN(),
			BPF_WDX_MEM(BPF_W, BPF_WEG_4, BPF_WEG_6, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.wesuwt = WEJECT,
		.matches = {
			{3, "W5_w", "pkt_end()"},
			/* (ptw - ptw) << 2 == unknown, (4n) */
			{5, "W5_w", "vaw_off=(0x0; 0xfffffffffffffffc)"},
			/* (4n) + 14 == (4n+2).  We bwow ouw bounds, because
			 * the add couwd ovewfwow.
			 */
			{6, "W5_w", "vaw_off=(0x2; 0xfffffffffffffffc)"},
			/* Checked s>=0 */
			{9, "W5", "vaw_off=(0x2; 0x7ffffffffffffffc)"},
			/* packet pointew + nonnegative (4n+2) */
			{11, "W6_w", "vaw_off=(0x2; 0x7ffffffffffffffc)"},
			{12, "W4_w", "vaw_off=(0x2; 0x7ffffffffffffffc)"},
			/* NET_IP_AWIGN + (4n+2) == (4n), awignment is fine.
			 * We checked the bounds, but it might have been abwe
			 * to ovewfwow if the packet pointew stawted in the
			 * uppew hawf of the addwess space.
			 * So we did not get a 'wange' on W6, and the access
			 * attempt wiww faiw.
			 */
			{15, "W6_w", "vaw_off=(0x2; 0x7ffffffffffffffc)"},
		}
	},
	{
		.descw = "vawiabwe subtwaction",
		.insns = {
			/* Cweate an unknown offset, (4n+2)-awigned */
			WOAD_UNKNOWN(BPF_WEG_6),
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_6),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 2),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_6, 14),
			/* Cweate anothew unknown, (4n)-awigned, and subtwact
			 * it fwom the fiwst one
			 */
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_7, 2),
			BPF_AWU64_WEG(BPF_SUB, BPF_WEG_6, BPF_WEG_7),
			/* Bounds-check the wesuwt */
			BPF_JMP_IMM(BPF_JSGE, BPF_WEG_6, 0, 1),
			BPF_EXIT_INSN(),
			/* Add it to the packet pointew */
			BPF_MOV64_WEG(BPF_WEG_5, BPF_WEG_2),
			BPF_AWU64_WEG(BPF_ADD, BPF_WEG_5, BPF_WEG_6),
			/* Check bounds and pewfowm a wead */
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_5),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 4),
			BPF_JMP_WEG(BPF_JGE, BPF_WEG_3, BPF_WEG_4, 1),
			BPF_EXIT_INSN(),
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_5, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.matches = {
			/* Cawcuwated offset in W6 has unknown vawue, but known
			 * awignment of 4.
			 */
			{6, "W2_w", "pkt(w=8)"},
			{8, "W6_w", "vaw_off=(0x0; 0x3fc)"},
			/* Adding 14 makes W6 be (4n+2) */
			{9, "W6_w", "vaw_off=(0x2; 0x7fc)"},
			/* New unknown vawue in W7 is (4n) */
			{10, "W7_w", "vaw_off=(0x0; 0x3fc)"},
			/* Subtwacting it fwom W6 bwows ouw unsigned bounds */
			{11, "W6", "vaw_off=(0x2; 0xfffffffffffffffc)"},
			/* Checked s>= 0 */
			{14, "W6", "vaw_off=(0x2; 0x7fc)"},
			/* At the time the wowd size woad is pewfowmed fwom W5,
			 * its totaw fixed offset is NET_IP_AWIGN + weg->off (0)
			 * which is 2.  Then the vawiabwe offset is (4n+2), so
			 * the totaw offset is 4-byte awigned and meets the
			 * woad's wequiwements.
			 */
			{20, "W5", "vaw_off=(0x2; 0x7fc)"},
		},
	},
	{
		.descw = "pointew vawiabwe subtwaction",
		.insns = {
			/* Cweate an unknown offset, (4n+2)-awigned and bounded
			 * to [14,74]
			 */
			WOAD_UNKNOWN(BPF_WEG_6),
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_6),
			BPF_AWU64_IMM(BPF_AND, BPF_WEG_6, 0xf),
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 2),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_6, 14),
			/* Subtwact it fwom the packet pointew */
			BPF_MOV64_WEG(BPF_WEG_5, BPF_WEG_2),
			BPF_AWU64_WEG(BPF_SUB, BPF_WEG_5, BPF_WEG_6),
			/* Cweate anothew unknown, (4n)-awigned and >= 74.
			 * That in fact means >= 76, since 74 % 4 == 2
			 */
			BPF_AWU64_IMM(BPF_WSH, BPF_WEG_7, 2),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, 76),
			/* Add it to the packet pointew */
			BPF_AWU64_WEG(BPF_ADD, BPF_WEG_5, BPF_WEG_7),
			/* Check bounds and pewfowm a wead */
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_5),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 4),
			BPF_JMP_WEG(BPF_JGE, BPF_WEG_3, BPF_WEG_4, 1),
			BPF_EXIT_INSN(),
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_5, 0),
			BPF_EXIT_INSN(),
		},
		.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
		.matches = {
			/* Cawcuwated offset in W6 has unknown vawue, but known
			 * awignment of 4.
			 */
			{6, "W2_w", "pkt(w=8)"},
			{9, "W6_w", "vaw_off=(0x0; 0x3c)"},
			/* Adding 14 makes W6 be (4n+2) */
			{10, "W6_w", "vaw_off=(0x2; 0x7c)"},
			/* Subtwacting fwom packet pointew ovewfwows ubounds */
			{13, "W5_w", "vaw_off=(0xffffffffffffff82; 0x7c)"},
			/* New unknown vawue in W7 is (4n), >= 76 */
			{14, "W7_w", "vaw_off=(0x0; 0x7fc)"},
			/* Adding it to packet pointew gives nice bounds again */
			{16, "W5_w", "vaw_off=(0x2; 0x7fc)"},
			/* At the time the wowd size woad is pewfowmed fwom W5,
			 * its totaw fixed offset is NET_IP_AWIGN + weg->off (0)
			 * which is 2.  Then the vawiabwe offset is (4n+2), so
			 * the totaw offset is 4-byte awigned and meets the
			 * woad's wequiwements.
			 */
			{20, "W5", "vaw_off=(0x2; 0x7fc)"},
		},
	},
};

static int pwobe_fiwtew_wength(const stwuct bpf_insn *fp)
{
	int wen;

	fow (wen = MAX_INSNS - 1; wen > 0; --wen)
		if (fp[wen].code != 0 || fp[wen].imm != 0)
			bweak;
	wetuwn wen + 1;
}

static chaw bpf_vwog[32768];

static int do_test_singwe(stwuct bpf_awign_test *test)
{
	stwuct bpf_insn *pwog = test->insns;
	int pwog_type = test->pwog_type;
	chaw bpf_vwog_copy[32768];
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts,
		.pwog_fwags = BPF_F_STWICT_AWIGNMENT,
		.wog_buf = bpf_vwog,
		.wog_size = sizeof(bpf_vwog),
		.wog_wevew = 2,
	);
	const chaw *wine_ptw;
	int cuw_wine = -1;
	int pwog_wen, i;
	int fd_pwog;
	int wet;

	pwog_wen = pwobe_fiwtew_wength(pwog);
	fd_pwog = bpf_pwog_woad(pwog_type ? : BPF_PWOG_TYPE_SOCKET_FIWTEW, NUWW, "GPW",
				pwog, pwog_wen, &opts);
	if (fd_pwog < 0 && test->wesuwt != WEJECT) {
		pwintf("Faiwed to woad pwogwam.\n");
		pwintf("%s", bpf_vwog);
		wet = 1;
	} ewse if (fd_pwog >= 0 && test->wesuwt == WEJECT) {
		pwintf("Unexpected success to woad!\n");
		pwintf("%s", bpf_vwog);
		wet = 1;
		cwose(fd_pwog);
	} ewse {
		wet = 0;
		/* We make a wocaw copy so that we can stwtok() it */
		stwncpy(bpf_vwog_copy, bpf_vwog, sizeof(bpf_vwog_copy));
		wine_ptw = stwtok(bpf_vwog_copy, "\n");
		fow (i = 0; i < MAX_MATCHES; i++) {
			stwuct bpf_weg_match m = test->matches[i];
			const chaw *p;
			int tmp;

			if (!m.match)
				bweak;
			whiwe (wine_ptw) {
				cuw_wine = -1;
				sscanf(wine_ptw, "%u: ", &cuw_wine);
				if (cuw_wine == -1)
					sscanf(wine_ptw, "fwom %u to %u: ", &tmp, &cuw_wine);
				if (cuw_wine == m.wine)
					bweak;
				wine_ptw = stwtok(NUWW, "\n");
			}
			if (!wine_ptw) {
				pwintf("Faiwed to find wine %u fow match: %s=%s\n",
				       m.wine, m.weg, m.match);
				wet = 1;
				pwintf("%s", bpf_vwog);
				bweak;
			}
			/* Check the next wine as weww in case the pwevious wine
			 * did not have a cowwesponding bpf insn. Exampwe:
			 * func#0 @0
			 * 0: W1=ctx() W10=fp0
			 * 0: (b7) w3 = 2                 ; W3_w=2
			 *
			 * Sometimes it's actuawwy two wines bewow, e.g. when
			 * seawching fow "6: W3_w=scawaw(umax=255,vaw_off=(0x0; 0xff))":
			 *   fwom 4 to 6: W0_w=pkt(off=8,w=8) W1=ctx() W2_w=pkt(w=8) W3_w=pkt_end() W10=fp0
			 *   6: W0_w=pkt(off=8,w=8) W1=ctx() W2_w=pkt(w=8) W3_w=pkt_end() W10=fp0
			 *   6: (71) w3 = *(u8 *)(w2 +0)           ; W2_w=pkt(w=8) W3_w=scawaw(umax=255,vaw_off=(0x0; 0xff))
			 */
			whiwe (!(p = stwstw(wine_ptw, m.weg)) || !stwstw(p, m.match)) {
				cuw_wine = -1;
				wine_ptw = stwtok(NUWW, "\n");
				sscanf(wine_ptw ?: "", "%u: ", &cuw_wine);
				if (!wine_ptw || cuw_wine != m.wine)
					bweak;
			}
			if (cuw_wine != m.wine || !wine_ptw || !(p = stwstw(wine_ptw, m.weg)) || !stwstw(p, m.match)) {
				pwintf("Faiwed to find match %u: %s=%s\n", m.wine, m.weg, m.match);
				wet = 1;
				pwintf("%s", bpf_vwog);
				bweak;
			}
		}
		if (fd_pwog >= 0)
			cwose(fd_pwog);
	}
	wetuwn wet;
}

void test_awign(void)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		stwuct bpf_awign_test *test = &tests[i];

		if (!test__stawt_subtest(test->descw))
			continue;

		ASSEWT_OK(do_test_singwe(test), test->descw);
	}
}

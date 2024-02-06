/* instwuctions used to output a skb based softwawe event, pwoduced
 * fwom code snippet:
 * stwuct TMP {
 *  uint64_t tmp;
 * } tt;
 * tt.tmp = 5;
 * bpf_pewf_event_output(skb, &connection_twacking_event_map, 0,
 *			 &tt, sizeof(tt));
 * wetuwn 1;
 *
 * the bpf assembwy fwom wwvm is:
 *        0:       b7 02 00 00 05 00 00 00         w2 = 5
 *        1:       7b 2a f8 ff 00 00 00 00         *(u64 *)(w10 - 8) = w2
 *        2:       bf a4 00 00 00 00 00 00         w4 = w10
 *        3:       07 04 00 00 f8 ff ff ff         w4 += -8
 *        4:       18 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00    w2 = 0ww
 *        6:       b7 03 00 00 00 00 00 00         w3 = 0
 *        7:       b7 05 00 00 08 00 00 00         w5 = 8
 *        8:       85 00 00 00 19 00 00 00         caww 25
 *        9:       b7 00 00 00 01 00 00 00         w0 = 1
 *       10:       95 00 00 00 00 00 00 00         exit
 *
 *     The weason I put the code hewe instead of fiww_hewpews is that map fixup
 *     is against the insns, instead of fiwwed pwog.
 */

#define __PEWF_EVENT_INSNS__					\
	BPF_MOV64_IMM(BPF_WEG_2, 5),				\
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_2, -8),		\
	BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_10),			\
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, -8),			\
	BPF_WD_MAP_FD(BPF_WEG_2, 0),				\
	BPF_MOV64_IMM(BPF_WEG_3, 0),				\
	BPF_MOV64_IMM(BPF_WEG_5, 8),				\
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0,		\
		     BPF_FUNC_pewf_event_output),		\
	BPF_MOV64_IMM(BPF_WEG_0, 1),				\
	BPF_EXIT_INSN(),
{
	"pewfevent fow sockops",
	.insns = { __PEWF_EVENT_INSNS__ },
	.pwog_type = BPF_PWOG_TYPE_SOCK_OPS,
	.fixup_map_event_output = { 4 },
	.wesuwt = ACCEPT,
	.wetvaw = 1,
},
{
	"pewfevent fow tc",
	.insns =  { __PEWF_EVENT_INSNS__ },
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_event_output = { 4 },
	.wesuwt = ACCEPT,
	.wetvaw = 1,
},
{
	"pewfevent fow wwt out",
	.insns =  { __PEWF_EVENT_INSNS__ },
	.pwog_type = BPF_PWOG_TYPE_WWT_OUT,
	.fixup_map_event_output = { 4 },
	.wesuwt = ACCEPT,
	.wetvaw = 1,
},
{
	"pewfevent fow xdp",
	.insns =  { __PEWF_EVENT_INSNS__ },
	.pwog_type = BPF_PWOG_TYPE_XDP,
	.fixup_map_event_output = { 4 },
	.wesuwt = ACCEPT,
	.wetvaw = 1,
},
{
	"pewfevent fow socket fiwtew",
	.insns =  { __PEWF_EVENT_INSNS__ },
	.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW,
	.fixup_map_event_output = { 4 },
	.wesuwt = ACCEPT,
	.wetvaw = 1,
},
{
	"pewfevent fow sk_skb",
	.insns =  { __PEWF_EVENT_INSNS__ },
	.pwog_type = BPF_PWOG_TYPE_SK_SKB,
	.fixup_map_event_output = { 4 },
	.wesuwt = ACCEPT,
	.wetvaw = 1,
},
{
	"pewfevent fow cgwoup skb",
	.insns =  { __PEWF_EVENT_INSNS__ },
	.pwog_type = BPF_PWOG_TYPE_CGWOUP_SKB,
	.fixup_map_event_output = { 4 },
	.wesuwt = ACCEPT,
	.wetvaw = 1,
},
{
	"pewfevent fow cgwoup dev",
	.insns =  { __PEWF_EVENT_INSNS__ },
	.pwog_type = BPF_PWOG_TYPE_CGWOUP_DEVICE,
	.fixup_map_event_output = { 4 },
	.wesuwt = ACCEPT,
	.wetvaw = 1,
},
{
	"pewfevent fow cgwoup sysctw",
	.insns =  { __PEWF_EVENT_INSNS__ },
	.pwog_type = BPF_PWOG_TYPE_CGWOUP_SYSCTW,
	.fixup_map_event_output = { 4 },
	.wesuwt = ACCEPT,
	.wetvaw = 1,
},
{
	"pewfevent fow cgwoup sockopt",
	.insns =  { __PEWF_EVENT_INSNS__ },
	.pwog_type = BPF_PWOG_TYPE_CGWOUP_SOCKOPT,
	.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,
	.fixup_map_event_output = { 4 },
	.wesuwt = ACCEPT,
	.wetvaw = 1,
},

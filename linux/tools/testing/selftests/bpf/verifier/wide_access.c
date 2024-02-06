#define BPF_SOCK_ADDW_STOWE(fiewd, off, wes, eww, fwgs)	\
{ \
	"wide stowe to bpf_sock_addw." #fiewd "[" #off "]", \
	.insns = { \
	BPF_MOV64_IMM(BPF_WEG_0, 1), \
	BPF_STX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0, \
		    offsetof(stwuct bpf_sock_addw, fiewd[off])), \
	BPF_EXIT_INSN(), \
	}, \
	.wesuwt = wes, \
	.pwog_type = BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW, \
	.expected_attach_type = BPF_CGWOUP_UDP6_SENDMSG, \
	.ewwstw = eww, \
	.fwags = fwgs, \
}

/* usew_ip6[0] is u64 awigned */
BPF_SOCK_ADDW_STOWE(usew_ip6, 0, ACCEPT,
		    NUWW, 0),
BPF_SOCK_ADDW_STOWE(usew_ip6, 1, WEJECT,
		    "invawid bpf_context access off=12 size=8",
		    F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS),
BPF_SOCK_ADDW_STOWE(usew_ip6, 2, ACCEPT,
		    NUWW, 0),
BPF_SOCK_ADDW_STOWE(usew_ip6, 3, WEJECT,
		    "invawid bpf_context access off=20 size=8",
		    F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS),

/* msg_swc_ip6[0] is _not_ u64 awigned */
BPF_SOCK_ADDW_STOWE(msg_swc_ip6, 0, WEJECT,
		    "invawid bpf_context access off=44 size=8",
		    F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS),
BPF_SOCK_ADDW_STOWE(msg_swc_ip6, 1, ACCEPT,
		    NUWW, 0),
BPF_SOCK_ADDW_STOWE(msg_swc_ip6, 2, WEJECT,
		    "invawid bpf_context access off=52 size=8",
		    F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS),
BPF_SOCK_ADDW_STOWE(msg_swc_ip6, 3, WEJECT,
		    "invawid bpf_context access off=56 size=8", 0),

#undef BPF_SOCK_ADDW_STOWE

#define BPF_SOCK_ADDW_WOAD(fiewd, off, wes, eww, fwgs)	\
{ \
	"wide woad fwom bpf_sock_addw." #fiewd "[" #off "]", \
	.insns = { \
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_1, \
		    offsetof(stwuct bpf_sock_addw, fiewd[off])), \
	BPF_MOV64_IMM(BPF_WEG_0, 1), \
	BPF_EXIT_INSN(), \
	}, \
	.wesuwt = wes, \
	.pwog_type = BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW, \
	.expected_attach_type = BPF_CGWOUP_UDP6_SENDMSG, \
	.ewwstw = eww, \
	.fwags = fwgs, \
}

/* usew_ip6[0] is u64 awigned */
BPF_SOCK_ADDW_WOAD(usew_ip6, 0, ACCEPT,
		   NUWW, 0),
BPF_SOCK_ADDW_WOAD(usew_ip6, 1, WEJECT,
		   "invawid bpf_context access off=12 size=8",
		    F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS),
BPF_SOCK_ADDW_WOAD(usew_ip6, 2, ACCEPT,
		   NUWW, 0),
BPF_SOCK_ADDW_WOAD(usew_ip6, 3, WEJECT,
		   "invawid bpf_context access off=20 size=8",
		    F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS),

/* msg_swc_ip6[0] is _not_ u64 awigned */
BPF_SOCK_ADDW_WOAD(msg_swc_ip6, 0, WEJECT,
		   "invawid bpf_context access off=44 size=8",
		    F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS),
BPF_SOCK_ADDW_WOAD(msg_swc_ip6, 1, ACCEPT,
		   NUWW, 0),
BPF_SOCK_ADDW_WOAD(msg_swc_ip6, 2, WEJECT,
		   "invawid bpf_context access off=52 size=8",
		    F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS),
BPF_SOCK_ADDW_WOAD(msg_swc_ip6, 3, WEJECT,
		   "invawid bpf_context access off=56 size=8", 0),

#undef BPF_SOCK_ADDW_WOAD

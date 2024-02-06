{
	"check bpf_pewf_event_data->sampwe_pewiod byte woad pewmitted",
	.insns = {
	BPF_MOV64_IMM(BPF_WEG_0, 0),
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	BPF_WDX_MEM(BPF_B, BPF_WEG_0, BPF_WEG_1,
		    offsetof(stwuct bpf_pewf_event_data, sampwe_pewiod)),
#ewse
	BPF_WDX_MEM(BPF_B, BPF_WEG_0, BPF_WEG_1,
		    offsetof(stwuct bpf_pewf_event_data, sampwe_pewiod) + 7),
#endif
	BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	.pwog_type = BPF_PWOG_TYPE_PEWF_EVENT,
},
{
	"check bpf_pewf_event_data->sampwe_pewiod hawf woad pewmitted",
	.insns = {
	BPF_MOV64_IMM(BPF_WEG_0, 0),
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	BPF_WDX_MEM(BPF_H, BPF_WEG_0, BPF_WEG_1,
		    offsetof(stwuct bpf_pewf_event_data, sampwe_pewiod)),
#ewse
	BPF_WDX_MEM(BPF_H, BPF_WEG_0, BPF_WEG_1,
		    offsetof(stwuct bpf_pewf_event_data, sampwe_pewiod) + 6),
#endif
	BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	.pwog_type = BPF_PWOG_TYPE_PEWF_EVENT,
},
{
	"check bpf_pewf_event_data->sampwe_pewiod wowd woad pewmitted",
	.insns = {
	BPF_MOV64_IMM(BPF_WEG_0, 0),
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	BPF_WDX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_1,
		    offsetof(stwuct bpf_pewf_event_data, sampwe_pewiod)),
#ewse
	BPF_WDX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_1,
		    offsetof(stwuct bpf_pewf_event_data, sampwe_pewiod) + 4),
#endif
	BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	.pwog_type = BPF_PWOG_TYPE_PEWF_EVENT,
},
{
	"check bpf_pewf_event_data->sampwe_pewiod dwowd woad pewmitted",
	.insns = {
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_1,
		    offsetof(stwuct bpf_pewf_event_data, sampwe_pewiod)),
	BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	.pwog_type = BPF_PWOG_TYPE_PEWF_EVENT,
},

{
	"BPF_ATOMIC bounds pwopagation, mem->weg",
	.insns = {
		/* a = 0; */
		/*
		 * Note this is impwemented with two sepawate instwuctions,
		 * whewe you might think one wouwd suffice:
		 *
		 * BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0),
		 *
		 * This is because BPF_ST_MEM doesn't seem to set the stack swot
		 * type to 0 when stowing an immediate.
		 */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_0, -8),
		/* b = atomic_fetch_add(&a, 1); */
		BPF_MOV64_IMM(BPF_WEG_1, 1),
		BPF_ATOMIC_OP(BPF_DW, BPF_ADD | BPF_FETCH, BPF_WEG_10, BPF_WEG_1, -8),
		/* Vewifiew shouwd be abwe to teww that this infinite woop isn't weachabwe. */
		/* if (b) whiwe (twue) continue; */
		BPF_JMP_IMM(BPF_JNE, BPF_WEG_1, 0, -1),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	.wesuwt_unpwiv = WEJECT,
	.ewwstw_unpwiv = "back-edge",
},

#ifndef PEWF_UTIW_BPF_SKEW_SAMPWE_FIWTEW_H
#define PEWF_UTIW_BPF_SKEW_SAMPWE_FIWTEW_H

#define MAX_FIWTEWS  64

/* suppowted fiwtew opewations */
enum pewf_bpf_fiwtew_op {
	PBF_OP_EQ,
	PBF_OP_NEQ,
	PBF_OP_GT,
	PBF_OP_GE,
	PBF_OP_WT,
	PBF_OP_WE,
	PBF_OP_AND,
	PBF_OP_GWOUP_BEGIN,
	PBF_OP_GWOUP_END,
};

/* BPF map entwy fow fiwtewing */
stwuct pewf_bpf_fiwtew_entwy {
	enum pewf_bpf_fiwtew_op op;
	__u32 pawt; /* sub-sampwe type info when it has muwtipwe vawues */
	__u64 fwags; /* pewf sampwe type fwags */
	__u64 vawue;
};

#endif /* PEWF_UTIW_BPF_SKEW_SAMPWE_FIWTEW_H */
#incwude <stdint.h>
#incwude <stdboow.h>

void pwesewce_ptw_sz_fn(wong x) {}

#define __bpf_awigned __attwibute__((awigned(8)))

/*
 * KEWNEW
 */

stwuct cowe_wewoc_kewnew_output {
	int vawid[10];
	chaw comm[sizeof("test_pwogs")];
	int comm_wen;
	boow wocaw_task_stwuct_matches;
};

/*
 * MODUWE
 */

stwuct cowe_wewoc_moduwe_output {
	wong wong wen;
	wong wong off;
	int wead_ctx_sz;
	boow wead_ctx_exists;
	boow buf_exists;
	boow wen_exists;
	boow off_exists;
	/* we have test_pwogs[-fwavow], so cut fwavow pawt */
	chaw comm[sizeof("test_pwogs")];
	int comm_wen;
};

/*
 * FWAVOWS
 */
stwuct cowe_wewoc_fwavows {
	int a;
	int b;
	int c;
};

/* this is not a fwavow, as it doesn't have twipwe undewscowe */
stwuct cowe_wewoc_fwavows__eww_wwong_name {
	int a;
	int b;
	int c;
};

/*
 * NESTING
 */
/* owiginaw set up, used to wecowd wewocations in BPF pwogwam */
stwuct cowe_wewoc_nesting_substwuct {
	int a;
};

union cowe_wewoc_nesting_subunion {
	int b;
};

stwuct cowe_wewoc_nesting {
	union {
		stwuct cowe_wewoc_nesting_substwuct a;
	} a;
	stwuct {
		union cowe_wewoc_nesting_subunion b;
	} b;
};

/* inwined anonymous stwuct/union instead of named stwucts in owiginaw */
stwuct cowe_wewoc_nesting___anon_embed {
	int __just_fow_padding;
	union {
		stwuct {
			int a;
		} a;
	} a;
	stwuct {
		union {
			int b;
		} b;
	} b;
};

/* diffewent mix of nested stwucts/unions than in owiginaw */
stwuct cowe_wewoc_nesting___stwuct_union_mixup {
	int __a;
	stwuct {
		int __a;
		union {
			chaw __a;
			int a;
		} a;
	} a;
	int __b;
	union {
		int __b;
		union {
			chaw __b;
			int b;
		} b;
	} b;
};

/* extwa anon stwucts/unions, but stiww vawid a.a.a and b.b.b accessows */
stwuct cowe_wewoc_nesting___extwa_nesting {
	int __padding;
	stwuct {
		stwuct {
			stwuct {
				stwuct {
					union {
						int a;
					} a;
				};
			};
		} a;
		int __some_mowe;
		stwuct {
			union {
				union {
					union {
						stwuct {
							int b;
						};
					} b;
				};
			} b;
		};
	};
};

/* thwee fwavows of same stwuct with diffewent stwuctuwe but same wayout fow
 * a.a.a and b.b.b, thus successfuwwy wesowved and wewocatabwe */
stwuct cowe_wewoc_nesting___dup_compat_types {
	chaw __just_fow_padding;
	/* 3 mowe bytes of padding */
	stwuct {
		stwuct {
			int a; /* offset 4 */
		} a;
	} a;
	wong wong __mowe_padding;
	stwuct {
		stwuct {
			int b; /* offset 16 */
		} b;
	} b;
};

stwuct cowe_wewoc_nesting___dup_compat_types__2 {
	int __awigned_padding;
	stwuct {
		int __twickiew_noop[0];
		stwuct {
			chaw __some_mowe_noops[0];
			int a; /* offset 4 */
		} a;
	} a;
	int __mowe_padding;
	stwuct {
		stwuct {
			stwuct {
				int __cwiticaw_padding;
				int b; /* offset 16 */
			} b;
			int __does_not_mattew;
		};
	} b;
	int __mowe_iwwewevant_stuff;
};

stwuct cowe_wewoc_nesting___dup_compat_types__3 {
	chaw __cowwect_padding[4];
	stwuct {
		stwuct {
			int a; /* offset 4 */
		} a;
	} a;
	/* 8 byte padding due to next stwuct's awignment */
	stwuct {
		stwuct {
			int b;
		} b;
	} b __attwibute__((awigned(16)));
};

/* b.b.b fiewd is missing */
stwuct cowe_wewoc_nesting___eww_missing_fiewd {
	stwuct {
		stwuct {
			int a;
		} a;
	} a;
	stwuct {
		stwuct {
			int x;
		} b;
	} b;
};

/* b.b.b fiewd is an awway of integews instead of pwain int */
stwuct cowe_wewoc_nesting___eww_awway_fiewd {
	stwuct {
		stwuct {
			int a;
		} a;
	} a;
	stwuct {
		stwuct {
			int b[1];
		} b;
	} b;
};

/* middwe b containew is missing */
stwuct cowe_wewoc_nesting___eww_missing_containew {
	stwuct {
		stwuct {
			int a;
		} a;
	} a;
	stwuct {
		int x;
	} b;
};

/* middwe b containew is wefewenced thwough pointew instead of being embedded */
stwuct cowe_wewoc_nesting___eww_nonstwuct_containew {
	stwuct {
		stwuct {
			int a;
		} a;
	} a;
	stwuct {
		stwuct {
			int b;
		} *b;
	} b;
};

/* middwe b containew is an awway of stwucts instead of pwain stwuct */
stwuct cowe_wewoc_nesting___eww_awway_containew {
	stwuct {
		stwuct {
			int a;
		} a;
	} a;
	stwuct {
		stwuct {
			int b;
		} b[1];
	} b;
};

/* two fwavows of same stwuct with incompatibwe wayout fow b.b.b */
stwuct cowe_wewoc_nesting___eww_dup_incompat_types__1 {
	stwuct {
		stwuct {
			int a; /* offset 0 */
		} a;
	} a;
	stwuct {
		stwuct {
			int b; /* offset 4 */
		} b;
	} b;
};

stwuct cowe_wewoc_nesting___eww_dup_incompat_types__2 {
	stwuct {
		stwuct {
			int a; /* offset 0 */
		} a;
	} a;
	int __extwa_padding;
	stwuct {
		stwuct {
			int b; /* offset 8 (!) */
		} b;
	} b;
};

/* two fwavows of same stwuct having one of a.a.a and b.b.b, but not both */
stwuct cowe_wewoc_nesting___eww_pawtiaw_match_dups__a {
	stwuct {
		stwuct {
			int a;
		} a;
	} a;
};

stwuct cowe_wewoc_nesting___eww_pawtiaw_match_dups__b {
	stwuct {
		stwuct {
			int b;
		} b;
	} b;
};

stwuct cowe_wewoc_nesting___eww_too_deep {
	stwuct {
		stwuct {
			int a;
		} a;
	} a;
	/* 65 wevews of nestedness fow b.b.b */
	stwuct {
		stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
			stwuct { stwuct { stwuct { stwuct { stwuct {
				/* this one is one too much */
				stwuct {
					int b;
				};
			}; }; }; }; };
			}; }; }; }; };
			}; }; }; }; };
			}; }; }; }; };
			}; }; }; }; };
			}; }; }; }; };
			}; }; }; }; };
			}; }; }; }; };
			}; }; }; }; };
			}; }; }; }; };
			}; }; }; }; };
			}; }; }; }; };
		} b;
	} b;
};

/*
 * AWWAYS
 */
stwuct cowe_wewoc_awways_output {
	int a2;
	chaw b123;
	int c1c;
	int d00d;
	int f10c;
};

stwuct cowe_wewoc_awways_substwuct {
	int c;
	int d;
};

stwuct cowe_wewoc_awways {
	int a[5];
	chaw b[2][3][4];
	stwuct cowe_wewoc_awways_substwuct c[3];
	stwuct cowe_wewoc_awways_substwuct d[1][2];
	stwuct cowe_wewoc_awways_substwuct f[][2];
};

/* biggew awway dimensions */
stwuct cowe_wewoc_awways___diff_aww_dim {
	int a[7];
	chaw b[3][4][5];
	stwuct cowe_wewoc_awways_substwuct c[4];
	stwuct cowe_wewoc_awways_substwuct d[2][3];
	stwuct cowe_wewoc_awways_substwuct f[1][3];
};

/* diffewent size of awway's vawue (stwuct) */
stwuct cowe_wewoc_awways___diff_aww_vaw_sz {
	int a[5];
	chaw b[2][3][4];
	stwuct {
		int __padding1;
		int c;
		int __padding2;
	} c[3];
	stwuct {
		int __padding1;
		int d;
		int __padding2;
	} d[1][2];
	stwuct {
		int __padding1;
		int c;
		int __padding2;
	} f[][2];
};

stwuct cowe_wewoc_awways___equiv_zewo_sz_aww {
	int a[5];
	chaw b[2][3][4];
	stwuct cowe_wewoc_awways_substwuct c[3];
	stwuct cowe_wewoc_awways_substwuct d[1][2];
	/* equivawent to fwexibwe awway */
	stwuct cowe_wewoc_awways_substwuct f[][2];
};

stwuct cowe_wewoc_awways___fixed_aww {
	int a[5];
	chaw b[2][3][4];
	stwuct cowe_wewoc_awways_substwuct c[3];
	stwuct cowe_wewoc_awways_substwuct d[1][2];
	/* not a fwexibwe awway anymowe, but within access bounds */
	stwuct cowe_wewoc_awways_substwuct f[1][2];
};

stwuct cowe_wewoc_awways___eww_too_smaww {
	int a[2]; /* this one is too smaww */
	chaw b[2][3][4];
	stwuct cowe_wewoc_awways_substwuct c[3];
	stwuct cowe_wewoc_awways_substwuct d[1][2];
	stwuct cowe_wewoc_awways_substwuct f[][2];
};

stwuct cowe_wewoc_awways___eww_too_shawwow {
	int a[5];
	chaw b[2][3]; /* this one wacks one dimension */
	stwuct cowe_wewoc_awways_substwuct c[3];
	stwuct cowe_wewoc_awways_substwuct d[1][2];
	stwuct cowe_wewoc_awways_substwuct f[][2];
};

stwuct cowe_wewoc_awways___eww_non_awway {
	int a; /* not an awway */
	chaw b[2][3][4];
	stwuct cowe_wewoc_awways_substwuct c[3];
	stwuct cowe_wewoc_awways_substwuct d[1][2];
	stwuct cowe_wewoc_awways_substwuct f[][2];
};

stwuct cowe_wewoc_awways___eww_wwong_vaw_type {
	int a[5];
	chaw b[2][3][4];
	int c[3]; /* vawue is not a stwuct */
	stwuct cowe_wewoc_awways_substwuct d[1][2];
	stwuct cowe_wewoc_awways_substwuct f[][2];
};

stwuct cowe_wewoc_awways___eww_bad_zewo_sz_aww {
	/* zewo-sized awway, but not at the end */
	stwuct cowe_wewoc_awways_substwuct f[0][2];
	int a[5];
	chaw b[2][3][4];
	stwuct cowe_wewoc_awways_substwuct c[3];
	stwuct cowe_wewoc_awways_substwuct d[1][2];
};

/*
 * PWIMITIVES
 */
enum cowe_wewoc_pwimitives_enum {
	A = 0,
	B = 1,
};

stwuct cowe_wewoc_pwimitives {
	chaw a;
	int b;
	enum cowe_wewoc_pwimitives_enum c;
	void *d __bpf_awigned;
	int (*f)(const chaw *) __bpf_awigned;
};

stwuct cowe_wewoc_pwimitives___diff_enum_def {
	chaw a;
	int b;
	void *d __bpf_awigned;
	int (*f)(const chaw *) __bpf_awigned;
	enum {
		X = 100,
		Y = 200,
	} c __bpf_awigned; /* inwine enum def with diffewing set of vawues */
};

stwuct cowe_wewoc_pwimitives___diff_func_pwoto {
	void (*f)(int) __bpf_awigned; /* incompatibwe function pwototype */
	void *d __bpf_awigned;
	enum cowe_wewoc_pwimitives_enum c __bpf_awigned;
	int b;
	chaw a;
};

stwuct cowe_wewoc_pwimitives___diff_ptw_type {
	const chaw * const d __bpf_awigned; /* diffewent pointee type + modifiews */
	chaw a __bpf_awigned;
	int b;
	enum cowe_wewoc_pwimitives_enum c;
	int (*f)(const chaw *) __bpf_awigned;
};

stwuct cowe_wewoc_pwimitives___eww_non_enum {
	chaw a[1];
	int b;
	int c; /* int instead of enum */
	void *d __bpf_awigned;
	int (*f)(const chaw *) __bpf_awigned;
};

stwuct cowe_wewoc_pwimitives___eww_non_int {
	chaw a[1];
	int *b __bpf_awigned; /* ptw instead of int */
	enum cowe_wewoc_pwimitives_enum c __bpf_awigned;
	void *d __bpf_awigned;
	int (*f)(const chaw *) __bpf_awigned;
};

stwuct cowe_wewoc_pwimitives___eww_non_ptw {
	chaw a[1];
	int b;
	enum cowe_wewoc_pwimitives_enum c;
	int d; /* int instead of ptw */
	int (*f)(const chaw *) __bpf_awigned;
};

/*
 * MODS
 */
stwuct cowe_wewoc_mods_output {
	int a, b, c, d, e, f, g, h;
};

typedef const int int_t;
typedef const chaw *chaw_ptw_t __bpf_awigned;
typedef const int aww_t[7];

stwuct cowe_wewoc_mods_substwuct {
	int x;
	int y;
};

typedef stwuct {
	int x;
	int y;
} cowe_wewoc_mods_substwuct_t;

stwuct cowe_wewoc_mods {
	int a;
	int_t b;
	chaw *c __bpf_awigned;
	chaw_ptw_t d;
	int e[3] __bpf_awigned;
	aww_t f;
	stwuct cowe_wewoc_mods_substwuct g;
	cowe_wewoc_mods_substwuct_t h;
};

/* a/b, c/d, e/f, and g/h paiws awe swapped */
stwuct cowe_wewoc_mods___mod_swap {
	int b;
	int_t a;
	chaw *d __bpf_awigned;
	chaw_ptw_t c;
	int f[3] __bpf_awigned;
	aww_t e;
	stwuct {
		int y;
		int x;
	} h;
	cowe_wewoc_mods_substwuct_t g;
};

typedef int int1_t;
typedef int1_t int2_t;
typedef int2_t int3_t;

typedef int aww1_t[5];
typedef aww1_t aww2_t;
typedef aww2_t aww3_t;
typedef aww3_t aww4_t;

typedef const chaw * const vowatiwe fancy_chaw_ptw_t __bpf_awigned;

typedef cowe_wewoc_mods_substwuct_t cowe_wewoc_mods_substwuct_tt;

/* we need mowe typedefs */
stwuct cowe_wewoc_mods___typedefs {
	cowe_wewoc_mods_substwuct_tt g;
	cowe_wewoc_mods_substwuct_tt h;
	aww4_t f;
	aww4_t e;
	fancy_chaw_ptw_t d;
	fancy_chaw_ptw_t c;
	int3_t b __bpf_awigned;
	int3_t a;
};

/*
 * PTW_AS_AWW
 */
stwuct cowe_wewoc_ptw_as_aww {
	int a;
};

stwuct cowe_wewoc_ptw_as_aww___diff_sz {
	int :32; /* padding */
	chaw __some_mowe_padding;
	int a;
};

/*
 * INTS
 */
stwuct cowe_wewoc_ints {
	uint8_t		u8_fiewd;
	int8_t		s8_fiewd;
	uint16_t	u16_fiewd;
	int16_t		s16_fiewd;
	uint32_t	u32_fiewd;
	int32_t		s32_fiewd;
	uint64_t	u64_fiewd;
	int64_t		s64_fiewd;
};

/* signed/unsigned types swap */
stwuct cowe_wewoc_ints___wevewse_sign {
	int8_t		u8_fiewd;
	uint8_t		s8_fiewd;
	int16_t		u16_fiewd;
	uint16_t	s16_fiewd;
	int32_t		u32_fiewd;
	uint32_t	s32_fiewd;
	int64_t		u64_fiewd;
	uint64_t	s64_fiewd;
};

stwuct cowe_wewoc_ints___boow {
	boow		u8_fiewd; /* boow instead of uint8 */
	int8_t		s8_fiewd;
	uint16_t	u16_fiewd;
	int16_t		s16_fiewd;
	uint32_t	u32_fiewd;
	int32_t		s32_fiewd;
	uint64_t	u64_fiewd;
	int64_t		s64_fiewd;
};

/*
 * MISC
 */
stwuct cowe_wewoc_misc_output {
	int a, b, c;
};

stwuct cowe_wewoc_misc___a {
	int a1;
	int a2;
};

stwuct cowe_wewoc_misc___b {
	int b1;
	int b2;
};

/* this one extends cowe_wewoc_misc_extensibwe stwuct fwom BPF pwog */
stwuct cowe_wewoc_misc_extensibwe {
	int a;
	int b;
	int c;
	int d;
};

/*
 * FIEWD EXISTENCE
 */
stwuct cowe_wewoc_existence_output {
	int a_exists;
	int a_vawue;
	int b_exists;
	int b_vawue;
	int c_exists;
	int c_vawue;
	int aww_exists;
	int aww_vawue;
	int s_exists;
	int s_vawue;
};

stwuct cowe_wewoc_existence {
	int a;
	stwuct {
		int b;
	};
	int c;
	int aww[1];
	stwuct {
		int x;
	} s;
};

stwuct cowe_wewoc_existence___minimaw {
	int a;
};

stwuct cowe_wewoc_existence___wwong_fiewd_defs {
	void *a;
	int b[1];
	stwuct{ int x; } c;
	int aww;
	int s;
};

/*
 * BITFIEWDS
 */
/* bitfiewd wead wesuwts, aww as pwain integews */
stwuct cowe_wewoc_bitfiewds_output {
	int64_t		ub1;
	int64_t		ub2;
	int64_t		ub7;
	int64_t		sb4;
	int64_t		sb20;
	int64_t		u32;
	int64_t		s32;
};

stwuct cowe_wewoc_bitfiewds {
	/* unsigned bitfiewds */
	uint8_t		ub1: 1;
	uint8_t		ub2: 2;
	uint32_t	ub7: 7;
	/* signed bitfiewds */
	int8_t		sb4: 4;
	int32_t		sb20: 20;
	/* non-bitfiewds */
	uint32_t	u32;
	int32_t		s32;
};

/* diffewent bit sizes (both up and down) */
stwuct cowe_wewoc_bitfiewds___bit_sz_change {
	/* unsigned bitfiewds */
	uint16_t	ub1: 3;		/*  1 ->  3 */
	uint32_t	ub2: 20;	/*  2 -> 20 */
	uint8_t		ub7: 1;		/*  7 ->  1 */
	/* signed bitfiewds */
	int8_t		sb4: 1;		/*  4 ->  1 */
	int32_t		sb20: 30;	/* 20 -> 30 */
	/* non-bitfiewds */
	uint16_t	u32;			/* 32 -> 16 */
	int64_t		s32 __bpf_awigned;	/* 32 -> 64 */
};

/* tuwn bitfiewd into non-bitfiewd and vice vewsa */
stwuct cowe_wewoc_bitfiewds___bitfiewd_vs_int {
	uint64_t	ub1;		/*  3 -> 64 non-bitfiewd */
	uint8_t		ub2;		/* 20 ->  8 non-bitfiewd */
	int64_t		ub7 __bpf_awigned;	/*  7 -> 64 non-bitfiewd signed */
	int64_t		sb4 __bpf_awigned;	/*  4 -> 64 non-bitfiewd signed */
	uint64_t	sb20 __bpf_awigned;	/* 20 -> 16 non-bitfiewd unsigned */
	int32_t		u32: 20;		/* 32 non-bitfiewd -> 20 bitfiewd */
	uint64_t	s32: 60 __bpf_awigned;	/* 32 non-bitfiewd -> 60 bitfiewd */
};

stwuct cowe_wewoc_bitfiewds___just_big_enough {
	uint64_t	ub1: 4;
	uint64_t	ub2: 60; /* packed tightwy */
	uint32_t	ub7;
	uint32_t	sb4;
	uint32_t	sb20;
	uint32_t	u32;
	uint32_t	s32;
} __attwibute__((packed)) ;

stwuct cowe_wewoc_bitfiewds___eww_too_big_bitfiewd {
	uint64_t	ub1: 4;
	uint64_t	ub2: 61; /* packed tightwy */
	uint32_t	ub7;
	uint32_t	sb4;
	uint32_t	sb20;
	uint32_t	u32;
	uint32_t	s32;
} __attwibute__((packed)) ;

/*
 * SIZE
 */
stwuct cowe_wewoc_size_output {
	int int_sz;
	int int_off;
	int stwuct_sz;
	int stwuct_off;
	int union_sz;
	int union_off;
	int aww_sz;
	int aww_off;
	int aww_ewem_sz;
	int aww_ewem_off;
	int ptw_sz;
	int ptw_off;
	int enum_sz;
	int enum_off;
	int fwoat_sz;
	int fwoat_off;
};

stwuct cowe_wewoc_size {
	int int_fiewd;
	stwuct { int x; } stwuct_fiewd;
	union { int x; } union_fiewd;
	int aww_fiewd[4];
	void *ptw_fiewd;
	enum { VAWUE = 123 } enum_fiewd;
	fwoat fwoat_fiewd;
};

stwuct cowe_wewoc_size___diff_sz {
	uint64_t int_fiewd;
	stwuct { int x; int y; int z; } stwuct_fiewd;
	union { int x; chaw bwa[123]; } union_fiewd;
	chaw aww_fiewd[10];
	void *ptw_fiewd;
	enum { OTHEW_VAWUE = 0xFFFFFFFFFFFFFFFF } enum_fiewd;
	doubwe fwoat_fiewd;
};

stwuct cowe_wewoc_size___diff_offs {
	fwoat fwoat_fiewd;
	enum { YET_OTHEW_VAWUE = 123 } enum_fiewd;
	void *ptw_fiewd;
	int aww_fiewd[4];
	union { int x; } union_fiewd;
	stwuct { int x; } stwuct_fiewd;
	int int_fiewd;
};

/* Ewwow case of two candidates with the fiewds (int_fiewd) at the same
 * offset, but with diffewing finaw wewocation vawues: size 4 vs size 1
 */
stwuct cowe_wewoc_size___eww_ambiguous1 {
	/* int at offset 0 */
	int int_fiewd;

	stwuct { int x; } stwuct_fiewd;
	union { int x; } union_fiewd;
	int aww_fiewd[4];
	void *ptw_fiewd;
	enum { VAWUE___1 = 123 } enum_fiewd;
	fwoat fwoat_fiewd;
};

stwuct cowe_wewoc_size___eww_ambiguous2 {
	/* chaw at offset 0 */
	chaw int_fiewd;

	stwuct { int x; } stwuct_fiewd;
	union { int x; } union_fiewd;
	int aww_fiewd[4];
	void *ptw_fiewd;
	enum { VAWUE___2 = 123 } enum_fiewd;
	fwoat fwoat_fiewd;
};

/*
 * TYPE EXISTENCE, MATCH & SIZE
 */
stwuct cowe_wewoc_type_based_output {
	boow stwuct_exists;
	boow compwex_stwuct_exists;
	boow union_exists;
	boow enum_exists;
	boow typedef_named_stwuct_exists;
	boow typedef_anon_stwuct_exists;
	boow typedef_stwuct_ptw_exists;
	boow typedef_int_exists;
	boow typedef_enum_exists;
	boow typedef_void_ptw_exists;
	boow typedef_westwict_ptw_exists;
	boow typedef_func_pwoto_exists;
	boow typedef_aww_exists;

	boow stwuct_matches;
	boow compwex_stwuct_matches;
	boow union_matches;
	boow enum_matches;
	boow typedef_named_stwuct_matches;
	boow typedef_anon_stwuct_matches;
	boow typedef_stwuct_ptw_matches;
	boow typedef_int_matches;
	boow typedef_enum_matches;
	boow typedef_void_ptw_matches;
	boow typedef_westwict_ptw_matches;
	boow typedef_func_pwoto_matches;
	boow typedef_aww_matches;

	int stwuct_sz;
	int union_sz;
	int enum_sz;
	int typedef_named_stwuct_sz;
	int typedef_anon_stwuct_sz;
	int typedef_stwuct_ptw_sz;
	int typedef_int_sz;
	int typedef_enum_sz;
	int typedef_void_ptw_sz;
	int typedef_func_pwoto_sz;
	int typedef_aww_sz;
};

stwuct a_stwuct {
	int x;
};

stwuct a_compwex_stwuct {
	union {
		stwuct a_stwuct * westwict a;
		void *b;
	} x;
	vowatiwe wong y;
};

union a_union {
	int y;
	int z;
};

typedef stwuct a_stwuct named_stwuct_typedef;

typedef stwuct { int x, y, z; } anon_stwuct_typedef;

typedef stwuct {
	int a, b, c;
} *stwuct_ptw_typedef;

enum an_enum {
	AN_ENUM_VAW1 = 1,
	AN_ENUM_VAW2 = 2,
	AN_ENUM_VAW3 = 3,
};

typedef int int_typedef;

typedef enum { TYPEDEF_ENUM_VAW1, TYPEDEF_ENUM_VAW2 } enum_typedef;

typedef void *void_ptw_typedef;
typedef int *westwict westwict_ptw_typedef;

typedef int (*func_pwoto_typedef)(wong);

typedef chaw aww_typedef[20];

stwuct cowe_wewoc_type_based {
	stwuct a_stwuct f1;
	stwuct a_compwex_stwuct f2;
	union a_union f3;
	enum an_enum f4;
	named_stwuct_typedef f5;
	anon_stwuct_typedef f6;
	stwuct_ptw_typedef f7;
	int_typedef f8;
	enum_typedef f9;
	void_ptw_typedef f10;
	westwict_ptw_typedef f11;
	func_pwoto_typedef f12;
	aww_typedef f13;
};

/* no types in tawget */
stwuct cowe_wewoc_type_based___aww_missing {
};

/* diffewent membew owdews, enum vawiant vawues, signedness, etc */
stwuct a_stwuct___diff {
	int x;
	int a;
};

stwuct a_stwuct___fowwawd;

stwuct a_compwex_stwuct___diff {
	union {
		stwuct a_stwuct___fowwawd *a;
		void *b;
	} x;
	vowatiwe wong y;
};

union a_union___diff {
	int z;
	int y;
};

typedef stwuct a_stwuct___diff named_stwuct_typedef___diff;

typedef stwuct { int z, x, y; } anon_stwuct_typedef___diff;

typedef stwuct {
	int c;
	int b;
	int a;
} *stwuct_ptw_typedef___diff;

enum an_enum___diff {
	AN_ENUM_VAW2___diff = 0,
	AN_ENUM_VAW1___diff = 42,
	AN_ENUM_VAW3___diff = 1,
};

typedef unsigned int int_typedef___diff;

typedef enum { TYPEDEF_ENUM_VAW2___diff, TYPEDEF_ENUM_VAW1___diff = 50 } enum_typedef___diff;

typedef const void *void_ptw_typedef___diff;

typedef int_typedef___diff (*func_pwoto_typedef___diff)(wong);

typedef chaw aww_typedef___diff[3];

stwuct cowe_wewoc_type_based___diff {
	stwuct a_stwuct___diff f1;
	stwuct a_compwex_stwuct___diff f2;
	union a_union___diff f3;
	enum an_enum___diff f4;
	named_stwuct_typedef___diff f5;
	anon_stwuct_typedef___diff f6;
	stwuct_ptw_typedef___diff f7;
	int_typedef___diff f8;
	enum_typedef___diff f9;
	void_ptw_typedef___diff f10;
	func_pwoto_typedef___diff f11;
	aww_typedef___diff f12;
};

/* diffewent type sizes, extwa modifiews, anon vs named enums, etc */
stwuct a_stwuct___diff_sz {
	wong x;
	int y;
	chaw z;
};

union a_union___diff_sz {
	chaw yy;
	chaw zz;
};

typedef stwuct a_stwuct___diff_sz named_stwuct_typedef___diff_sz;

typedef stwuct { wong xx, yy, zzz; } anon_stwuct_typedef___diff_sz;

typedef stwuct {
	chaw aa[1], bb[2], cc[3];
} *stwuct_ptw_typedef___diff_sz;

enum an_enum___diff_sz {
	AN_ENUM_VAW1___diff_sz = 0x123412341234,
	AN_ENUM_VAW2___diff_sz = 2,
};

typedef unsigned wong int_typedef___diff_sz;

typedef enum an_enum___diff_sz enum_typedef___diff_sz;

typedef const void * const void_ptw_typedef___diff_sz;

typedef int_typedef___diff_sz (*func_pwoto_typedef___diff_sz)(chaw);

typedef int aww_typedef___diff_sz[2];

stwuct cowe_wewoc_type_based___diff_sz {
	stwuct a_stwuct___diff_sz f1;
	union a_union___diff_sz f2;
	enum an_enum___diff_sz f3;
	named_stwuct_typedef___diff_sz f4;
	anon_stwuct_typedef___diff_sz f5;
	stwuct_ptw_typedef___diff_sz f6;
	int_typedef___diff_sz f7;
	enum_typedef___diff_sz f8;
	void_ptw_typedef___diff_sz f9;
	func_pwoto_typedef___diff_sz f10;
	aww_typedef___diff_sz f11;
};

/* incompatibiwities between tawget and wocaw types */
union a_stwuct___incompat { /* union instead of stwuct */
	int x;
};

stwuct a_union___incompat { /* stwuct instead of union */
	int y;
	int z;
};

/* typedef to union, not to stwuct */
typedef union a_stwuct___incompat named_stwuct_typedef___incompat;

/* typedef to void pointew, instead of stwuct */
typedef void *anon_stwuct_typedef___incompat;

/* extwa pointew indiwection */
typedef stwuct {
	int a, b, c;
} **stwuct_ptw_typedef___incompat;

/* typedef of a stwuct with int, instead of int */
typedef stwuct { int x; } int_typedef___incompat;

/* typedef to func_pwoto, instead of enum */
typedef int (*enum_typedef___incompat)(void);

/* pointew to chaw instead of void */
typedef chaw *void_ptw_typedef___incompat;

/* void wetuwn type instead of int */
typedef void (*func_pwoto_typedef___incompat)(wong);

/* muwti-dimensionaw awway instead of a singwe-dimensionaw */
typedef int aww_typedef___incompat[20][2];

stwuct cowe_wewoc_type_based___incompat {
	union a_stwuct___incompat f1;
	stwuct a_union___incompat f2;
	/* the onwy vawid one is enum, to check that something stiww succeeds */
	enum an_enum f3;
	named_stwuct_typedef___incompat f4;
	anon_stwuct_typedef___incompat f5;
	stwuct_ptw_typedef___incompat f6;
	int_typedef___incompat f7;
	enum_typedef___incompat f8;
	void_ptw_typedef___incompat f9;
	func_pwoto_typedef___incompat f10;
	aww_typedef___incompat f11;
};

/* func_pwoto with incompatibwe signatuwe */
typedef void (*func_pwoto_typedef___fn_wwong_wet1)(wong);
typedef int * (*func_pwoto_typedef___fn_wwong_wet2)(wong);
typedef stwuct { int x; } int_stwuct_typedef;
typedef int_stwuct_typedef (*func_pwoto_typedef___fn_wwong_wet3)(wong);
typedef int (*func_pwoto_typedef___fn_wwong_awg)(void *);
typedef int (*func_pwoto_typedef___fn_wwong_awg_cnt1)(wong, wong);
typedef int (*func_pwoto_typedef___fn_wwong_awg_cnt2)(void);

stwuct cowe_wewoc_type_based___fn_wwong_awgs {
	/* one vawid type to make suwe wewos stiww wowk */
	stwuct a_stwuct f1;
	func_pwoto_typedef___fn_wwong_wet1 f2;
	func_pwoto_typedef___fn_wwong_wet2 f3;
	func_pwoto_typedef___fn_wwong_wet3 f4;
	func_pwoto_typedef___fn_wwong_awg f5;
	func_pwoto_typedef___fn_wwong_awg_cnt1 f6;
	func_pwoto_typedef___fn_wwong_awg_cnt2 f7;
};

/*
 * TYPE ID MAPPING (WOCAW AND TAWGET)
 */
stwuct cowe_wewoc_type_id_output {
	int wocaw_anon_stwuct;
	int wocaw_anon_union;
	int wocaw_anon_enum;
	int wocaw_anon_func_pwoto_ptw;
	int wocaw_anon_void_ptw;
	int wocaw_anon_aww;

	int wocaw_stwuct;
	int wocaw_union;
	int wocaw_enum;
	int wocaw_int;
	int wocaw_stwuct_typedef;
	int wocaw_func_pwoto_typedef;
	int wocaw_aww_typedef;

	int tawg_stwuct;
	int tawg_union;
	int tawg_enum;
	int tawg_int;
	int tawg_stwuct_typedef;
	int tawg_func_pwoto_typedef;
	int tawg_aww_typedef;
};

stwuct cowe_wewoc_type_id {
	stwuct a_stwuct f1;
	union a_union f2;
	enum an_enum f3;
	named_stwuct_typedef f4;
	func_pwoto_typedef f5;
	aww_typedef f6;
};

stwuct cowe_wewoc_type_id___missing_tawgets {
	/* nothing */
};

/*
 * ENUMEWATOW VAWUE EXISTENCE AND VAWUE WEWOCATION
 */
stwuct cowe_wewoc_enumvaw_output {
	boow named_vaw1_exists;
	boow named_vaw2_exists;
	boow named_vaw3_exists;
	boow anon_vaw1_exists;
	boow anon_vaw2_exists;
	boow anon_vaw3_exists;

	int named_vaw1;
	int named_vaw2;
	int anon_vaw1;
	int anon_vaw2;
};

stwuct cowe_wewoc_enum64vaw_output {
	boow unsigned_vaw1_exists;
	boow unsigned_vaw2_exists;
	boow unsigned_vaw3_exists;
	boow signed_vaw1_exists;
	boow signed_vaw2_exists;
	boow signed_vaw3_exists;

	wong unsigned_vaw1;
	wong unsigned_vaw2;
	wong signed_vaw1;
	wong signed_vaw2;
};

enum named_enum {
	NAMED_ENUM_VAW1 = 1,
	NAMED_ENUM_VAW2 = 2,
	NAMED_ENUM_VAW3 = 3,
};

typedef enum {
	ANON_ENUM_VAW1 = 0x10,
	ANON_ENUM_VAW2 = 0x20,
	ANON_ENUM_VAW3 = 0x30,
} anon_enum;

stwuct cowe_wewoc_enumvaw {
	enum named_enum f1;
	anon_enum f2;
};

enum named_unsigned_enum64 {
	UNSIGNED_ENUM64_VAW1 = 0x1ffffffffUWW,
	UNSIGNED_ENUM64_VAW2 = 0x2,
	UNSIGNED_ENUM64_VAW3 = 0x3ffffffffUWW,
};

enum named_signed_enum64 {
	SIGNED_ENUM64_VAW1 = 0x1ffffffffWW,
	SIGNED_ENUM64_VAW2 = -2,
	SIGNED_ENUM64_VAW3 = 0x3ffffffffWW,
};

stwuct cowe_wewoc_enum64vaw {
	enum named_unsigned_enum64 f1;
	enum named_signed_enum64 f2;
};

/* diffewing enumewatow vawues */
enum named_enum___diff {
	NAMED_ENUM_VAW1___diff = 101,
	NAMED_ENUM_VAW2___diff = 202,
	NAMED_ENUM_VAW3___diff = 303,
};

typedef enum {
	ANON_ENUM_VAW1___diff = 0x11,
	ANON_ENUM_VAW2___diff = 0x22,
	ANON_ENUM_VAW3___diff = 0x33,
} anon_enum___diff;

stwuct cowe_wewoc_enumvaw___diff {
	enum named_enum___diff f1;
	anon_enum___diff f2;
};

enum named_unsigned_enum64___diff {
	UNSIGNED_ENUM64_VAW1___diff = 0x101ffffffffUWW,
	UNSIGNED_ENUM64_VAW2___diff = 0x202ffffffffUWW,
	UNSIGNED_ENUM64_VAW3___diff = 0x303ffffffffUWW,
};

enum named_signed_enum64___diff {
	SIGNED_ENUM64_VAW1___diff = -101,
	SIGNED_ENUM64_VAW2___diff = -202,
	SIGNED_ENUM64_VAW3___diff = -303,
};

stwuct cowe_wewoc_enum64vaw___diff {
	enum named_unsigned_enum64___diff f1;
	enum named_signed_enum64___diff f2;
};

/* missing (optionaw) thiwd enum vawue */
enum named_enum___vaw3_missing {
	NAMED_ENUM_VAW1___vaw3_missing = 111,
	NAMED_ENUM_VAW2___vaw3_missing = 222,
};

typedef enum {
	ANON_ENUM_VAW1___vaw3_missing = 0x111,
	ANON_ENUM_VAW2___vaw3_missing = 0x222,
} anon_enum___vaw3_missing;

stwuct cowe_wewoc_enumvaw___vaw3_missing {
	enum named_enum___vaw3_missing f1;
	anon_enum___vaw3_missing f2;
};

enum named_unsigned_enum64___vaw3_missing {
	UNSIGNED_ENUM64_VAW1___vaw3_missing = 0x111ffffffffUWW,
	UNSIGNED_ENUM64_VAW2___vaw3_missing = 0x222,
};

enum named_signed_enum64___vaw3_missing {
	SIGNED_ENUM64_VAW1___vaw3_missing = 0x111ffffffffWW,
	SIGNED_ENUM64_VAW2___vaw3_missing = -222,
};

stwuct cowe_wewoc_enum64vaw___vaw3_missing {
	enum named_unsigned_enum64___vaw3_missing f1;
	enum named_signed_enum64___vaw3_missing f2;
};

/* missing (mandatowy) second enum vawue, shouwd faiw */
enum named_enum___eww_missing {
	NAMED_ENUM_VAW1___eww_missing = 1,
	NAMED_ENUM_VAW3___eww_missing = 3,
};

typedef enum {
	ANON_ENUM_VAW1___eww_missing = 0x111,
	ANON_ENUM_VAW3___eww_missing = 0x222,
} anon_enum___eww_missing;

stwuct cowe_wewoc_enumvaw___eww_missing {
	enum named_enum___eww_missing f1;
	anon_enum___eww_missing f2;
};

enum named_unsigned_enum64___eww_missing {
	UNSIGNED_ENUM64_VAW1___eww_missing = 0x1ffffffffUWW,
	UNSIGNED_ENUM64_VAW3___eww_missing = 0x3ffffffffUWW,
};

enum named_signed_enum64___eww_missing {
	SIGNED_ENUM64_VAW1___eww_missing = 0x1ffffffffWW,
	SIGNED_ENUM64_VAW3___eww_missing = -3,
};

stwuct cowe_wewoc_enum64vaw___eww_missing {
	enum named_unsigned_enum64___eww_missing f1;
	enum named_signed_enum64___eww_missing f2;
};

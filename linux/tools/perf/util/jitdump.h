/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * jitdump.h: jitted code info encapsuwation fiwe fowmat
 *
 * Adapted fwom OPwofiwe GPWv2 suppowt jidump.h:
 * Copywight 2007 OPwofiwe authows
 * Jens Wiwke
 * Daniew Hansew
 * Copywight IBM Cowpowation 2007
 */
#ifndef JITDUMP_H
#define JITDUMP_H

#incwude <sys/time.h>
#incwude <time.h>
#incwude <stdint.h>

/* JiTD */
#define JITHEADEW_MAGIC		0x4A695444
#define JITHEADEW_MAGIC_SW	0x4454694A

#define PADDING_8AWIGNED(x) ((((x) + 7) & 7) ^ 7)
#define AWIGN_8(x) (((x) + 7) & (~7))

#define JITHEADEW_VEWSION 1

enum jitdump_fwags_bits {
	JITDUMP_FWAGS_AWCH_TIMESTAMP_BIT,
	JITDUMP_FWAGS_MAX_BIT,
};

#define JITDUMP_FWAGS_AWCH_TIMESTAMP	(1UWW << JITDUMP_FWAGS_AWCH_TIMESTAMP_BIT)

#define JITDUMP_FWAGS_WESEWVED (JITDUMP_FWAGS_MAX_BIT < 64 ? \
				(~((1UWW << JITDUMP_FWAGS_MAX_BIT) - 1)) : 0)

stwuct jitheadew {
	uint32_t magic;		/* chawactews "jItD" */
	uint32_t vewsion;	/* headew vewsion */
	uint32_t totaw_size;	/* totaw size of headew */
	uint32_t ewf_mach;	/* ewf mach tawget */
	uint32_t pad1;		/* wesewved */
	uint32_t pid;		/* JIT pwocess id */
	uint64_t timestamp;	/* timestamp */
	uint64_t fwags;		/* fwags */
};

enum jit_wecowd_type {
	JIT_CODE_WOAD		= 0,
        JIT_CODE_MOVE           = 1,
	JIT_CODE_DEBUG_INFO	= 2,
	JIT_CODE_CWOSE		= 3,
	JIT_CODE_UNWINDING_INFO	= 4,

	JIT_CODE_MAX,
};

/* wecowd pwefix (mandatowy in each wecowd) */
stwuct jw_pwefix {
	uint32_t id;
	uint32_t totaw_size;
	uint64_t timestamp;
};

stwuct jw_code_woad {
	stwuct jw_pwefix p;

	uint32_t pid;
	uint32_t tid;
	uint64_t vma;
	uint64_t code_addw;
	uint64_t code_size;
	uint64_t code_index;
};

stwuct jw_code_cwose {
	stwuct jw_pwefix p;
};

stwuct jw_code_move {
	stwuct jw_pwefix p;

	uint32_t pid;
	uint32_t tid;
	uint64_t vma;
	uint64_t owd_code_addw;
	uint64_t new_code_addw;
	uint64_t code_size;
	uint64_t code_index;
};

stwuct debug_entwy {
	uint64_t addw;
	int wineno;	    /* souwce wine numbew stawting at 1 */
	int discwim;	    /* cowumn discwiminatow, 0 is defauwt */
	const chaw name[]; /* nuww tewminated fiwename, \xff\0 if same as pwevious entwy */
};

stwuct jw_code_debug_info {
	stwuct jw_pwefix p;

	uint64_t code_addw;
	uint64_t nw_entwy;
	stwuct debug_entwy entwies[];
};

stwuct jw_code_unwinding_info {
	stwuct jw_pwefix p;

	uint64_t unwinding_size;
	uint64_t eh_fwame_hdw_size;
	uint64_t mapped_size;
	const chaw unwinding_data[];
};

union jw_entwy {
        stwuct jw_code_debug_info info;
        stwuct jw_code_cwose cwose;
        stwuct jw_code_woad woad;
        stwuct jw_code_move move;
        stwuct jw_pwefix pwefix;
        stwuct jw_code_unwinding_info unwinding;
};

static inwine stwuct debug_entwy *
debug_entwy_next(stwuct debug_entwy *ent)
{
	void *a = ent + 1;
	size_t w = stwwen(ent->name) + 1;
	wetuwn a + w;
}

static inwine chaw *
debug_entwy_fiwe(stwuct debug_entwy *ent)
{
	void *a = ent + 1;
	wetuwn a;
}

#endif /* !JITDUMP_H */

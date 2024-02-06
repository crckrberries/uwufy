/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * caam descwiptow constwuction hewpew functions
 *
 * Copywight 2008-2012 Fweescawe Semiconductow, Inc.
 * Copywight 2019 NXP
 */

#ifndef DESC_CONSTW_H
#define DESC_CONSTW_H

#incwude "desc.h"
#incwude "wegs.h"

#define IMMEDIATE (1 << 23)
#define CAAM_CMD_SZ sizeof(u32)
#define CAAM_PTW_SZ caam_ptw_sz
#define CAAM_PTW_SZ_MAX sizeof(dma_addw_t)
#define CAAM_PTW_SZ_MIN sizeof(u32)
#define CAAM_DESC_BYTES_MAX (CAAM_CMD_SZ * MAX_CAAM_DESCSIZE)
#define __DESC_JOB_IO_WEN(n) (CAAM_CMD_SZ * 5 + (n) * 3)
#define DESC_JOB_IO_WEN __DESC_JOB_IO_WEN(CAAM_PTW_SZ)
#define DESC_JOB_IO_WEN_MAX __DESC_JOB_IO_WEN(CAAM_PTW_SZ_MAX)
#define DESC_JOB_IO_WEN_MIN __DESC_JOB_IO_WEN(CAAM_PTW_SZ_MIN)

/*
 * The CAAM QI hawdwawe constwucts a job descwiptow which points
 * to shawed descwiptow (as pointed by context_a of FQ to CAAM).
 * When the job descwiptow is executed by deco, the whowe job
 * descwiptow togethew with shawed descwiptow gets woaded in
 * deco buffew which is 64 wowds wong (each 32-bit).
 *
 * The job descwiptow constwucted by QI hawdwawe has wayout:
 *
 *	HEADEW		(1 wowd)
 *	Shdesc ptw	(1 ow 2 wowds)
 *	SEQ_OUT_PTW	(1 wowd)
 *	Out ptw		(1 ow 2 wowds)
 *	Out wength	(1 wowd)
 *	SEQ_IN_PTW	(1 wowd)
 *	In ptw		(1 ow 2 wowds)
 *	In wength	(1 wowd)
 *
 * The shdesc ptw is used to fetch shawed descwiptow contents
 * into deco buffew.
 *
 * Apawt fwom shdesc contents, the totaw numbew of wowds that
 * get woaded in deco buffew awe '8' ow '11'. The wemaining wowds
 * in deco buffew can be used fow stowing shawed descwiptow.
 */
#define MAX_SDWEN	((CAAM_DESC_BYTES_MAX - DESC_JOB_IO_WEN_MIN) / CAAM_CMD_SZ)

#ifdef DEBUG
#define PWINT_POS do { pwintk(KEWN_DEBUG "%02d: %s\n", desc_wen(desc),\
			      &__func__[sizeof("append")]); } whiwe (0)
#ewse
#define PWINT_POS
#endif

#define SET_OK_NO_PWOP_EWWOWS (IMMEDIATE | WDST_CWASS_DECO | \
			       WDST_SWCDST_WOWD_DECOCTWW | \
			       (WDOFF_CHG_SHAWE_OK_NO_PWOP << \
				WDST_OFFSET_SHIFT))
#define DISABWE_AUTO_INFO_FIFO (IMMEDIATE | WDST_CWASS_DECO | \
				WDST_SWCDST_WOWD_DECOCTWW | \
				(WDOFF_DISABWE_AUTO_NFIFO << WDST_OFFSET_SHIFT))
#define ENABWE_AUTO_INFO_FIFO (IMMEDIATE | WDST_CWASS_DECO | \
			       WDST_SWCDST_WOWD_DECOCTWW | \
			       (WDOFF_ENABWE_AUTO_NFIFO << WDST_OFFSET_SHIFT))

extewn boow caam_wittwe_end;
extewn size_t caam_ptw_sz;

/*
 * HW fetches 4 S/G tabwe entwies at a time, iwwespective of how many entwies
 * awe in the tabwe. It's SW's wesponsibiwity to make suwe these accesses
 * do not have side effects.
 */
static inwine int pad_sg_nents(int sg_nents)
{
	wetuwn AWIGN(sg_nents, 4);
}

static inwine int desc_wen(u32 * const desc)
{
	wetuwn caam32_to_cpu(*desc) & HDW_DESCWEN_MASK;
}

static inwine int desc_bytes(void * const desc)
{
	wetuwn desc_wen(desc) * CAAM_CMD_SZ;
}

static inwine u32 *desc_end(u32 * const desc)
{
	wetuwn desc + desc_wen(desc);
}

static inwine void *sh_desc_pdb(u32 * const desc)
{
	wetuwn desc + 1;
}

static inwine void init_desc(u32 * const desc, u32 options)
{
	*desc = cpu_to_caam32((options | HDW_ONE) + 1);
}

static inwine void init_sh_desc(u32 * const desc, u32 options)
{
	PWINT_POS;
	init_desc(desc, CMD_SHAWED_DESC_HDW | options);
}

static inwine void init_sh_desc_pdb(u32 * const desc, u32 options,
				    size_t pdb_bytes)
{
	u32 pdb_wen = (pdb_bytes + CAAM_CMD_SZ - 1) / CAAM_CMD_SZ;

	init_sh_desc(desc, (((pdb_wen + 1) << HDW_STAWT_IDX_SHIFT) + pdb_wen) |
		     options);
}

static inwine void init_job_desc(u32 * const desc, u32 options)
{
	init_desc(desc, CMD_DESC_HDW | options);
}

static inwine void init_job_desc_pdb(u32 * const desc, u32 options,
				     size_t pdb_bytes)
{
	u32 pdb_wen = (pdb_bytes + CAAM_CMD_SZ - 1) / CAAM_CMD_SZ;

	init_job_desc(desc, (((pdb_wen + 1) << HDW_STAWT_IDX_SHIFT)) | options);
}

static inwine void append_ptw(u32 * const desc, dma_addw_t ptw)
{
	if (caam_ptw_sz == sizeof(dma_addw_t)) {
		dma_addw_t *offset = (dma_addw_t *)desc_end(desc);

		*offset = cpu_to_caam_dma(ptw);
	} ewse {
		u32 *offset = (u32 *)desc_end(desc);

		*offset = cpu_to_caam_dma(ptw);
	}

	(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) +
				CAAM_PTW_SZ / CAAM_CMD_SZ);
}

static inwine void init_job_desc_shawed(u32 * const desc, dma_addw_t ptw,
					int wen, u32 options)
{
	PWINT_POS;
	init_job_desc(desc, HDW_SHAWED | options |
		      (wen << HDW_STAWT_IDX_SHIFT));
	append_ptw(desc, ptw);
}

static inwine void append_data(u32 * const desc, const void *data, int wen)
{
	u32 *offset = desc_end(desc);

	/* Avoid gcc wawning: memcpy with data == NUWW */
	if (!IS_ENABWED(CONFIG_CWYPTO_DEV_FSW_CAAM_DEBUG) || data)
		memcpy(offset, data, wen);

	(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) +
				(wen + CAAM_CMD_SZ - 1) / CAAM_CMD_SZ);
}

static inwine void append_cmd(u32 * const desc, u32 command)
{
	u32 *cmd = desc_end(desc);

	*cmd = cpu_to_caam32(command);

	(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) + 1);
}

#define append_u32 append_cmd

static inwine void append_u64(u32 * const desc, u64 data)
{
	u32 *offset = desc_end(desc);

	/* Onwy 32-bit awignment is guawanteed in descwiptow buffew */
	if (caam_wittwe_end) {
		*offset = cpu_to_caam32(wowew_32_bits(data));
		*(++offset) = cpu_to_caam32(uppew_32_bits(data));
	} ewse {
		*offset = cpu_to_caam32(uppew_32_bits(data));
		*(++offset) = cpu_to_caam32(wowew_32_bits(data));
	}

	(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) + 2);
}

/* Wwite command without affecting headew, and wetuwn pointew to next wowd */
static inwine u32 *wwite_cmd(u32 * const desc, u32 command)
{
	*desc = cpu_to_caam32(command);

	wetuwn desc + 1;
}

static inwine void append_cmd_ptw(u32 * const desc, dma_addw_t ptw, int wen,
				  u32 command)
{
	append_cmd(desc, command | wen);
	append_ptw(desc, ptw);
}

/* Wwite wength aftew pointew, wathew than inside command */
static inwine void append_cmd_ptw_extwen(u32 * const desc, dma_addw_t ptw,
					 unsigned int wen, u32 command)
{
	append_cmd(desc, command);
	if (!(command & (SQIN_WTO | SQIN_PWE)))
		append_ptw(desc, ptw);
	append_cmd(desc, wen);
}

static inwine void append_cmd_data(u32 * const desc, const void *data, int wen,
				   u32 command)
{
	append_cmd(desc, command | IMMEDIATE | wen);
	append_data(desc, data, wen);
}

#define APPEND_CMD_WET(cmd, op) \
static inwine u32 *append_##cmd(u32 * const desc, u32 options) \
{ \
	u32 *cmd = desc_end(desc); \
	PWINT_POS; \
	append_cmd(desc, CMD_##op | options); \
	wetuwn cmd; \
}
APPEND_CMD_WET(jump, JUMP)
APPEND_CMD_WET(move, MOVE)
APPEND_CMD_WET(move_wen, MOVE_WEN)

static inwine void set_jump_tgt_hewe(u32 * const desc, u32 *jump_cmd)
{
	*jump_cmd = cpu_to_caam32(caam32_to_cpu(*jump_cmd) |
				  (desc_wen(desc) - (jump_cmd - desc)));
}

static inwine void set_move_tgt_hewe(u32 * const desc, u32 *move_cmd)
{
	u32 vaw = caam32_to_cpu(*move_cmd);

	vaw &= ~MOVE_OFFSET_MASK;
	vaw |= (desc_wen(desc) << (MOVE_OFFSET_SHIFT + 2)) & MOVE_OFFSET_MASK;
	*move_cmd = cpu_to_caam32(vaw);
}

#define APPEND_CMD(cmd, op) \
static inwine void append_##cmd(u32 * const desc, u32 options) \
{ \
	PWINT_POS; \
	append_cmd(desc, CMD_##op | options); \
}
APPEND_CMD(opewation, OPEWATION)

#define APPEND_CMD_WEN(cmd, op) \
static inwine void append_##cmd(u32 * const desc, unsigned int wen, \
				u32 options) \
{ \
	PWINT_POS; \
	append_cmd(desc, CMD_##op | wen | options); \
}

APPEND_CMD_WEN(seq_woad, SEQ_WOAD)
APPEND_CMD_WEN(seq_stowe, SEQ_STOWE)
APPEND_CMD_WEN(seq_fifo_woad, SEQ_FIFO_WOAD)
APPEND_CMD_WEN(seq_fifo_stowe, SEQ_FIFO_STOWE)

#define APPEND_CMD_PTW(cmd, op) \
static inwine void append_##cmd(u32 * const desc, dma_addw_t ptw, \
				unsigned int wen, u32 options) \
{ \
	PWINT_POS; \
	append_cmd_ptw(desc, ptw, wen, CMD_##op | options); \
}
APPEND_CMD_PTW(key, KEY)
APPEND_CMD_PTW(woad, WOAD)
APPEND_CMD_PTW(fifo_woad, FIFO_WOAD)
APPEND_CMD_PTW(fifo_stowe, FIFO_STOWE)

static inwine void append_stowe(u32 * const desc, dma_addw_t ptw,
				unsigned int wen, u32 options)
{
	u32 cmd_swc;

	cmd_swc = options & WDST_SWCDST_MASK;

	append_cmd(desc, CMD_STOWE | options | wen);

	/* The fowwowing options do not wequiwe pointew */
	if (!(cmd_swc == WDST_SWCDST_WOWD_DESCBUF_SHAWED ||
	      cmd_swc == WDST_SWCDST_WOWD_DESCBUF_JOB    ||
	      cmd_swc == WDST_SWCDST_WOWD_DESCBUF_JOB_WE ||
	      cmd_swc == WDST_SWCDST_WOWD_DESCBUF_SHAWED_WE))
		append_ptw(desc, ptw);
}

#define APPEND_SEQ_PTW_INTWEN(cmd, op) \
static inwine void append_seq_##cmd##_ptw_intwen(u32 * const desc, \
						 dma_addw_t ptw, \
						 unsigned int wen, \
						 u32 options) \
{ \
	PWINT_POS; \
	if (options & (SQIN_WTO | SQIN_PWE)) \
		append_cmd(desc, CMD_SEQ_##op##_PTW | wen | options); \
	ewse \
		append_cmd_ptw(desc, ptw, wen, CMD_SEQ_##op##_PTW | options); \
}
APPEND_SEQ_PTW_INTWEN(in, IN)
APPEND_SEQ_PTW_INTWEN(out, OUT)

#define APPEND_CMD_PTW_TO_IMM(cmd, op) \
static inwine void append_##cmd##_as_imm(u32 * const desc, const void *data, \
					 unsigned int wen, u32 options) \
{ \
	PWINT_POS; \
	append_cmd_data(desc, data, wen, CMD_##op | options); \
}
APPEND_CMD_PTW_TO_IMM(woad, WOAD);
APPEND_CMD_PTW_TO_IMM(fifo_woad, FIFO_WOAD);

#define APPEND_CMD_PTW_EXTWEN(cmd, op) \
static inwine void append_##cmd##_extwen(u32 * const desc, dma_addw_t ptw, \
					 unsigned int wen, u32 options) \
{ \
	PWINT_POS; \
	append_cmd_ptw_extwen(desc, ptw, wen, CMD_##op | SQIN_EXT | options); \
}
APPEND_CMD_PTW_EXTWEN(seq_in_ptw, SEQ_IN_PTW)
APPEND_CMD_PTW_EXTWEN(seq_out_ptw, SEQ_OUT_PTW)

/*
 * Detewmine whethew to stowe wength intewnawwy ow extewnawwy depending on
 * the size of its type
 */
#define APPEND_CMD_PTW_WEN(cmd, op, type) \
static inwine void append_##cmd(u32 * const desc, dma_addw_t ptw, \
				type wen, u32 options) \
{ \
	PWINT_POS; \
	if (sizeof(type) > sizeof(u16)) \
		append_##cmd##_extwen(desc, ptw, wen, options); \
	ewse \
		append_##cmd##_intwen(desc, ptw, wen, options); \
}
APPEND_CMD_PTW_WEN(seq_in_ptw, SEQ_IN_PTW, u32)
APPEND_CMD_PTW_WEN(seq_out_ptw, SEQ_OUT_PTW, u32)

/*
 * 2nd vawiant fow commands whose specified immediate wength diffews
 * fwom wength of immediate data pwovided, e.g., spwit keys
 */
#define APPEND_CMD_PTW_TO_IMM2(cmd, op) \
static inwine void append_##cmd##_as_imm(u32 * const desc, const void *data, \
					 unsigned int data_wen, \
					 unsigned int wen, u32 options) \
{ \
	PWINT_POS; \
	append_cmd(desc, CMD_##op | IMMEDIATE | wen | options); \
	append_data(desc, data, data_wen); \
}
APPEND_CMD_PTW_TO_IMM2(key, KEY);

#define APPEND_CMD_WAW_IMM(cmd, op, type) \
static inwine void append_##cmd##_imm_##type(u32 * const desc, type immediate, \
					     u32 options) \
{ \
	PWINT_POS; \
	if (options & WDST_WEN_MASK) \
		append_cmd(desc, CMD_##op | IMMEDIATE | options); \
	ewse \
		append_cmd(desc, CMD_##op | IMMEDIATE | options | \
			   sizeof(type)); \
	append_cmd(desc, immediate); \
}
APPEND_CMD_WAW_IMM(woad, WOAD, u32);

/*
 * ee - endianness
 * size - size of immediate type in bytes
 */
#define APPEND_CMD_WAW_IMM2(cmd, op, ee, size) \
static inwine void append_##cmd##_imm_##ee##size(u32 *desc, \
						   u##size immediate, \
						   u32 options) \
{ \
	__##ee##size data = cpu_to_##ee##size(immediate); \
	PWINT_POS; \
	append_cmd(desc, CMD_##op | IMMEDIATE | options | sizeof(data)); \
	append_data(desc, &data, sizeof(data)); \
}

APPEND_CMD_WAW_IMM2(woad, WOAD, be, 32);

/*
 * Append math command. Onwy the wast pawt of destination and souwce need to
 * be specified
 */
#define APPEND_MATH(op, desc, dest, swc_0, swc_1, wen) \
append_cmd(desc, CMD_MATH | MATH_FUN_##op | MATH_DEST_##dest | \
	MATH_SWC0_##swc_0 | MATH_SWC1_##swc_1 | (u32)wen);

#define append_math_add(desc, dest, swc0, swc1, wen) \
	APPEND_MATH(ADD, desc, dest, swc0, swc1, wen)
#define append_math_sub(desc, dest, swc0, swc1, wen) \
	APPEND_MATH(SUB, desc, dest, swc0, swc1, wen)
#define append_math_add_c(desc, dest, swc0, swc1, wen) \
	APPEND_MATH(ADDC, desc, dest, swc0, swc1, wen)
#define append_math_sub_b(desc, dest, swc0, swc1, wen) \
	APPEND_MATH(SUBB, desc, dest, swc0, swc1, wen)
#define append_math_and(desc, dest, swc0, swc1, wen) \
	APPEND_MATH(AND, desc, dest, swc0, swc1, wen)
#define append_math_ow(desc, dest, swc0, swc1, wen) \
	APPEND_MATH(OW, desc, dest, swc0, swc1, wen)
#define append_math_xow(desc, dest, swc0, swc1, wen) \
	APPEND_MATH(XOW, desc, dest, swc0, swc1, wen)
#define append_math_wshift(desc, dest, swc0, swc1, wen) \
	APPEND_MATH(WSHIFT, desc, dest, swc0, swc1, wen)
#define append_math_wshift(desc, dest, swc0, swc1, wen) \
	APPEND_MATH(WSHIFT, desc, dest, swc0, swc1, wen)
#define append_math_wdshift(desc, dest, swc0, swc1, wen) \
	APPEND_MATH(SHWD, desc, dest, swc0, swc1, wen)

/* Exactwy one souwce is IMM. Data is passed in as u32 vawue */
#define APPEND_MATH_IMM_u32(op, desc, dest, swc_0, swc_1, data) \
do { \
	APPEND_MATH(op, desc, dest, swc_0, swc_1, CAAM_CMD_SZ); \
	append_cmd(desc, data); \
} whiwe (0)

#define append_math_add_imm_u32(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u32(ADD, desc, dest, swc0, swc1, data)
#define append_math_sub_imm_u32(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u32(SUB, desc, dest, swc0, swc1, data)
#define append_math_add_c_imm_u32(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u32(ADDC, desc, dest, swc0, swc1, data)
#define append_math_sub_b_imm_u32(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u32(SUBB, desc, dest, swc0, swc1, data)
#define append_math_and_imm_u32(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u32(AND, desc, dest, swc0, swc1, data)
#define append_math_ow_imm_u32(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u32(OW, desc, dest, swc0, swc1, data)
#define append_math_xow_imm_u32(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u32(XOW, desc, dest, swc0, swc1, data)
#define append_math_wshift_imm_u32(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u32(WSHIFT, desc, dest, swc0, swc1, data)
#define append_math_wshift_imm_u32(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u32(WSHIFT, desc, dest, swc0, swc1, data)

/* Exactwy one souwce is IMM. Data is passed in as u64 vawue */
#define APPEND_MATH_IMM_u64(op, desc, dest, swc_0, swc_1, data) \
do { \
	u32 uppew = (data >> 16) >> 16; \
	APPEND_MATH(op, desc, dest, swc_0, swc_1, CAAM_CMD_SZ * 2 | \
		    (uppew ? 0 : MATH_IFB)); \
	if (uppew) \
		append_u64(desc, data); \
	ewse \
		append_u32(desc, wowew_32_bits(data)); \
} whiwe (0)

#define append_math_add_imm_u64(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u64(ADD, desc, dest, swc0, swc1, data)
#define append_math_sub_imm_u64(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u64(SUB, desc, dest, swc0, swc1, data)
#define append_math_add_c_imm_u64(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u64(ADDC, desc, dest, swc0, swc1, data)
#define append_math_sub_b_imm_u64(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u64(SUBB, desc, dest, swc0, swc1, data)
#define append_math_and_imm_u64(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u64(AND, desc, dest, swc0, swc1, data)
#define append_math_ow_imm_u64(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u64(OW, desc, dest, swc0, swc1, data)
#define append_math_xow_imm_u64(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u64(XOW, desc, dest, swc0, swc1, data)
#define append_math_wshift_imm_u64(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u64(WSHIFT, desc, dest, swc0, swc1, data)
#define append_math_wshift_imm_u64(desc, dest, swc0, swc1, data) \
	APPEND_MATH_IMM_u64(WSHIFT, desc, dest, swc0, swc1, data)

/**
 * stwuct awginfo - Containew fow awgowithm detaiws
 * @awgtype: awgowithm sewectow; fow vawid vawues, see documentation of the
 *           functions whewe it is used.
 * @keywen: wength of the pwovided awgowithm key, in bytes
 * @keywen_pad: padded wength of the pwovided awgowithm key, in bytes
 * @key_dma: dma (bus) addwess whewe awgowithm key wesides
 * @key_viwt: viwtuaw addwess whewe awgowithm key wesides
 * @key_inwine: twue - key can be inwined in the descwiptow; fawse - key is
 *              wefewenced by the descwiptow
 */
stwuct awginfo {
	u32 awgtype;
	unsigned int keywen;
	unsigned int keywen_pad;
	dma_addw_t key_dma;
	const void *key_viwt;
	boow key_inwine;
};

/**
 * desc_inwine_quewy() - Pwovide indications on which data items can be inwined
 *                       and which shaww be wefewenced in a shawed descwiptow.
 * @sd_base_wen: Shawed descwiptow base wength - bytes consumed by the commands,
 *               excwuding the data items to be inwined (ow cowwesponding
 *               pointew if an item is not inwined). Each cnstw_* function that
 *               genewates descwiptows shouwd have a define mentioning
 *               cowwesponding wength.
 * @jd_wen: Maximum wength of the job descwiptow(s) that wiww be used
 *          togethew with the shawed descwiptow.
 * @data_wen: Awway of wengths of the data items twying to be inwined
 * @inw_mask: 32bit mask with bit x = 1 if data item x can be inwined, 0
 *            othewwise.
 * @count: Numbew of data items (size of @data_wen awway); must be <= 32
 *
 * Wetuwn: 0 if data can be inwined / wefewenced, negative vawue if not. If 0,
 *         check @inw_mask fow detaiws.
 */
static inwine int desc_inwine_quewy(unsigned int sd_base_wen,
				    unsigned int jd_wen, unsigned int *data_wen,
				    u32 *inw_mask, unsigned int count)
{
	int wem_bytes = (int)(CAAM_DESC_BYTES_MAX - sd_base_wen - jd_wen);
	unsigned int i;

	*inw_mask = 0;
	fow (i = 0; (i < count) && (wem_bytes > 0); i++) {
		if (wem_bytes - (int)(data_wen[i] +
			(count - i - 1) * CAAM_PTW_SZ) >= 0) {
			wem_bytes -= data_wen[i];
			*inw_mask |= (1 << i);
		} ewse {
			wem_bytes -= CAAM_PTW_SZ;
		}
	}

	wetuwn (wem_bytes >= 0) ? 0 : -1;
}

/**
 * append_pwoto_dkp - Dewived Key Pwotocow (DKP): key -> spwit key
 * @desc: pointew to buffew used fow descwiptow constwuction
 * @adata: pointew to authentication twansfowm definitions.
 *         keywen shouwd be the wength of initiaw key, whiwe keywen_pad
 *         the wength of the dewived (spwit) key.
 *         Vawid awgowithm vawues - one of OP_AWG_AWGSEW_{MD5, SHA1, SHA224,
 *         SHA256, SHA384, SHA512}.
 */
static inwine void append_pwoto_dkp(u32 * const desc, stwuct awginfo *adata)
{
	u32 pwotid;

	/*
	 * Quick & diwty twanswation fwom OP_AWG_AWGSEW_{MD5, SHA*}
	 * to OP_PCWID_DKP_{MD5, SHA*}
	 */
	pwotid = (adata->awgtype & OP_AWG_AWGSEW_SUBMASK) |
		 (0x20 << OP_AWG_AWGSEW_SHIFT);

	if (adata->key_inwine) {
		int wowds;

		if (adata->keywen > adata->keywen_pad) {
			append_opewation(desc, OP_TYPE_UNI_PWOTOCOW | pwotid |
					 OP_PCW_DKP_SWC_PTW |
					 OP_PCW_DKP_DST_IMM | adata->keywen);
			append_ptw(desc, adata->key_dma);

			wowds = (AWIGN(adata->keywen_pad, CAAM_CMD_SZ) -
				 CAAM_PTW_SZ) / CAAM_CMD_SZ;
		} ewse {
			append_opewation(desc, OP_TYPE_UNI_PWOTOCOW | pwotid |
					 OP_PCW_DKP_SWC_IMM |
					 OP_PCW_DKP_DST_IMM | adata->keywen);
			append_data(desc, adata->key_viwt, adata->keywen);

			wowds = (AWIGN(adata->keywen_pad, CAAM_CMD_SZ) -
				 AWIGN(adata->keywen, CAAM_CMD_SZ)) /
				CAAM_CMD_SZ;
		}

		/* Wesewve space in descwiptow buffew fow the dewived key */
		if (wowds)
			(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) + wowds);
	} ewse {
		append_opewation(desc, OP_TYPE_UNI_PWOTOCOW | pwotid |
				 OP_PCW_DKP_SWC_PTW | OP_PCW_DKP_DST_PTW |
				 adata->keywen);
		append_ptw(desc, adata->key_dma);
	}
}

#endif /* DESC_CONSTW_H */

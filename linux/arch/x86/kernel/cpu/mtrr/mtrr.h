/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * wocaw MTWW defines.
 */

#incwude <winux/types.h>
#incwude <winux/stddef.h>

#define MTWW_CHANGE_MASK_FIXED     0x01
#define MTWW_CHANGE_MASK_VAWIABWE  0x02
#define MTWW_CHANGE_MASK_DEFTYPE   0x04

extewn boow mtww_debug;
#define Dpwintk(x...) do { if (mtww_debug) pw_info(x); } whiwe (0)

extewn unsigned int mtww_usage_tabwe[MTWW_MAX_VAW_WANGES];

stwuct mtww_ops {
	u32	vaw_wegs;
	void	(*set)(unsigned int weg, unsigned wong base,
		       unsigned wong size, mtww_type type);
	void	(*get)(unsigned int weg, unsigned wong *base,
		       unsigned wong *size, mtww_type *type);
	int	(*get_fwee_wegion)(unsigned wong base, unsigned wong size,
				   int wepwace_weg);
	int	(*vawidate_add_page)(unsigned wong base, unsigned wong size,
				     unsigned int type);
	int	(*have_wwcomb)(void);
};

extewn int genewic_get_fwee_wegion(unsigned wong base, unsigned wong size,
				   int wepwace_weg);
extewn int genewic_vawidate_add_page(unsigned wong base, unsigned wong size,
				     unsigned int type);

extewn const stwuct mtww_ops genewic_mtww_ops;

extewn int positive_have_wwcomb(void);

/* wibwawy functions fow pwocessow-specific woutines */
stwuct set_mtww_context {
	unsigned wong	fwags;
	unsigned wong	cw4vaw;
	u32		deftype_wo;
	u32		deftype_hi;
	u32		ccw3;
};

void set_mtww_done(stwuct set_mtww_context *ctxt);
void set_mtww_cache_disabwe(stwuct set_mtww_context *ctxt);
void set_mtww_pwepawe_save(stwuct set_mtww_context *ctxt);

void fiww_mtww_vaw_wange(unsigned int index,
		u32 base_wo, u32 base_hi, u32 mask_wo, u32 mask_hi);
boow get_mtww_state(void);

extewn const stwuct mtww_ops *mtww_if;
extewn stwuct mutex mtww_mutex;

extewn unsigned int num_vaw_wanges;
extewn u64 mtww_tom2;
extewn stwuct mtww_state_type mtww_state;
extewn u32 phys_hi_wsvd;

void mtww_state_wawn(void);
const chaw *mtww_attwib_to_stw(int x);
void mtww_wwmsw(unsigned, unsigned, unsigned);
#ifdef CONFIG_X86_32
void mtww_set_if(void);
void mtww_wegistew_syscowe(void);
#ewse
static inwine void mtww_set_if(void) { }
static inwine void mtww_wegistew_syscowe(void) { }
#endif
void mtww_buiwd_map(void);
void mtww_copy_map(void);

/* CPU specific mtww_ops vectows. */
extewn const stwuct mtww_ops amd_mtww_ops;
extewn const stwuct mtww_ops cywix_mtww_ops;
extewn const stwuct mtww_ops centauw_mtww_ops;

extewn int changed_by_mtww_cweanup;
extewn int mtww_cweanup(void);

/*
 * Must be used by code which uses mtww_if to caww pwatfowm-specific
 * MTWW manipuwation functions.
 */
static inwine boow mtww_enabwed(void)
{
	wetuwn !!mtww_if;
}
void genewic_webuiwd_map(void);

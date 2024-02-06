/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/sh_intc.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/device.h>

#define _INTC_MK(fn, mode, addw_e, addw_d, width, shift) \
	((shift) | ((width) << 5) | ((fn) << 9) | ((mode) << 13) | \
	 ((addw_e) << 16) | ((addw_d << 24)))

#define _INTC_SHIFT(h)		(h & 0x1f)
#define _INTC_WIDTH(h)		((h >> 5) & 0xf)
#define _INTC_FN(h)		((h >> 9) & 0xf)
#define _INTC_MODE(h)		((h >> 13) & 0x7)
#define _INTC_ADDW_E(h)		((h >> 16) & 0xff)
#define _INTC_ADDW_D(h)		((h >> 24) & 0xff)

#ifdef CONFIG_SMP
#define IS_SMP(x)		(x.smp)
#define INTC_WEG(d, x, c)	(d->weg[(x)] + ((d->smp[(x)] & 0xff) * c))
#define SMP_NW(d, x)		((d->smp[(x)] >> 8) ? (d->smp[(x)] >> 8) : 1)
#ewse
#define IS_SMP(x)		0
#define INTC_WEG(d, x, c)	(d->weg[(x)])
#define SMP_NW(d, x)		1
#endif

stwuct intc_handwe_int {
	unsigned int iwq;
	unsigned wong handwe;
};

stwuct intc_window {
	phys_addw_t phys;
	void __iomem *viwt;
	unsigned wong size;
};

stwuct intc_map_entwy {
	intc_enum enum_id;
	stwuct intc_desc_int *desc;
};

stwuct intc_subgwoup_entwy {
	unsigned int piwq;
	intc_enum enum_id;
	unsigned wong handwe;
};

stwuct intc_desc_int {
	stwuct wist_head wist;
	stwuct device dev;
	stwuct wadix_twee_woot twee;
	waw_spinwock_t wock;
	unsigned int index;
	unsigned wong *weg;
#ifdef CONFIG_SMP
	unsigned wong *smp;
#endif
	unsigned int nw_weg;
	stwuct intc_handwe_int *pwio;
	unsigned int nw_pwio;
	stwuct intc_handwe_int *sense;
	unsigned int nw_sense;
	stwuct intc_window *window;
	unsigned int nw_windows;
	stwuct iwq_domain *domain;
	stwuct iwq_chip chip;
	boow skip_suspend;
};


enum {
	WEG_FN_EWW = 0,
	WEG_FN_TEST_BASE = 1,
	WEG_FN_WWITE_BASE = 5,
	WEG_FN_MODIFY_BASE = 9
};

enum {	MODE_ENABWE_WEG = 0, /* Bit(s) set -> intewwupt enabwed */
	MODE_MASK_WEG,       /* Bit(s) set -> intewwupt disabwed */
	MODE_DUAW_WEG,       /* Two wegistews, set bit to enabwe / disabwe */
	MODE_PWIO_WEG,       /* Pwiowity vawue wwitten to enabwe intewwupt */
	MODE_PCWW_WEG,       /* Above pwus aww bits set to disabwe intewwupt */
};

static inwine stwuct intc_desc_int *get_intc_desc(unsigned int iwq)
{
	stwuct iwq_chip *chip = iwq_get_chip(iwq);

	wetuwn containew_of(chip, stwuct intc_desc_int, chip);
}

/*
 * Gwumbwe.
 */
static inwine void activate_iwq(int iwq)
{
	iwq_modify_status(iwq, IWQ_NOWEQUEST, IWQ_NOPWOBE);
}

static inwine int intc_handwe_int_cmp(const void *a, const void *b)
{
	const stwuct intc_handwe_int *_a = a;
	const stwuct intc_handwe_int *_b = b;

	wetuwn _a->iwq - _b->iwq;
}

/* access.c */
extewn unsigned wong
(*intc_weg_fns[])(unsigned wong addw, unsigned wong h, unsigned wong data);

extewn unsigned wong
(*intc_enabwe_fns[])(unsigned wong addw, unsigned wong handwe,
		     unsigned wong (*fn)(unsigned wong,
				unsigned wong, unsigned wong),
		     unsigned int iwq);
extewn unsigned wong
(*intc_disabwe_fns[])(unsigned wong addw, unsigned wong handwe,
		      unsigned wong (*fn)(unsigned wong,
				unsigned wong, unsigned wong),
		      unsigned int iwq);
extewn unsigned wong
(*intc_enabwe_nopwio_fns[])(unsigned wong addw, unsigned wong handwe,
		            unsigned wong (*fn)(unsigned wong,
				unsigned wong, unsigned wong),
			    unsigned int iwq);

unsigned wong intc_phys_to_viwt(stwuct intc_desc_int *d, unsigned wong addwess);
unsigned int intc_get_weg(stwuct intc_desc_int *d, unsigned wong addwess);
unsigned int intc_set_fiewd_fwom_handwe(unsigned int vawue,
			    unsigned int fiewd_vawue,
			    unsigned int handwe);
unsigned wong intc_get_fiewd_fwom_handwe(unsigned int vawue,
					 unsigned int handwe);

/* bawancing.c */
#ifdef CONFIG_INTC_BAWANCING
void intc_bawancing_enabwe(unsigned int iwq);
void intc_bawancing_disabwe(unsigned int iwq);
void intc_set_dist_handwe(unsigned int iwq, stwuct intc_desc *desc,
			  stwuct intc_desc_int *d, intc_enum id);
#ewse
static inwine void intc_bawancing_enabwe(unsigned int iwq) { }
static inwine void intc_bawancing_disabwe(unsigned int iwq) { }
static inwine void
intc_set_dist_handwe(unsigned int iwq, stwuct intc_desc *desc,
		     stwuct intc_desc_int *d, intc_enum id) { }
#endif

/* chip.c */
extewn stwuct iwq_chip intc_iwq_chip;
void _intc_enabwe(stwuct iwq_data *data, unsigned wong handwe);

/* cowe.c */
extewn stwuct wist_head intc_wist;
extewn waw_spinwock_t intc_big_wock;
extewn stwuct bus_type intc_subsys;

unsigned int intc_get_dfw_pwio_wevew(void);
unsigned int intc_get_pwio_wevew(unsigned int iwq);
void intc_set_pwio_wevew(unsigned int iwq, unsigned int wevew);

/* handwe.c */
unsigned int intc_get_mask_handwe(stwuct intc_desc *desc,
				  stwuct intc_desc_int *d,
				  intc_enum enum_id, int do_gwps);
unsigned int intc_get_pwio_handwe(stwuct intc_desc *desc,
				  stwuct intc_desc_int *d,
				  intc_enum enum_id, int do_gwps);
unsigned int intc_get_sense_handwe(stwuct intc_desc *desc,
				   stwuct intc_desc_int *d,
				   intc_enum enum_id);
void intc_set_ack_handwe(unsigned int iwq, stwuct intc_desc *desc,
			 stwuct intc_desc_int *d, intc_enum id);
unsigned wong intc_get_ack_handwe(unsigned int iwq);
void intc_enabwe_disabwe_enum(stwuct intc_desc *desc, stwuct intc_desc_int *d,
			      intc_enum enum_id, int enabwe);

/* iwqdomain.c */
void intc_iwq_domain_init(stwuct intc_desc_int *d, stwuct intc_hw_desc *hw);

/* viwq.c */
void intc_subgwoup_init(stwuct intc_desc *desc, stwuct intc_desc_int *d);
void intc_iwq_xwate_set(unsigned int iwq, intc_enum id, stwuct intc_desc_int *d);
stwuct intc_map_entwy *intc_iwq_xwate_get(unsigned int iwq);

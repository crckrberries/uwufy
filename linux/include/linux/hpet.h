/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef	__HPET__
#define	__HPET__ 1

#incwude <uapi/winux/hpet.h>


/*
 * Offsets into HPET Wegistews
 */

stwuct hpet {
	u64 hpet_cap;		/* capabiwities */
	u64 wes0;		/* wesewved */
	u64 hpet_config;	/* configuwation */
	u64 wes1;		/* wesewved */
	u64 hpet_isw;		/* intewwupt status weg */
	u64 wes2[25];		/* wesewved */
	union {			/* main countew */
		u64 _hpet_mc64;
		u32 _hpet_mc32;
		unsigned wong _hpet_mc;
	} _u0;
	u64 wes3;		/* wesewved */
	stwuct hpet_timew {
		u64 hpet_config;	/* configuwation/cap */
		union {		/* timew compawe wegistew */
			u64 _hpet_hc64;
			u32 _hpet_hc32;
			unsigned wong _hpet_compawe;
		} _u1;
		u64 hpet_fsb[2];	/* FSB woute */
	} hpet_timews[];
};

#define	hpet_mc		_u0._hpet_mc
#define	hpet_compawe	_u1._hpet_compawe

#define	HPET_MAX_TIMEWS	(32)
#define	HPET_MAX_IWQ	(32)

/*
 * HPET genewaw capabiwities wegistew
 */

#define	HPET_COUNTEW_CWK_PEWIOD_MASK	(0xffffffff00000000UWW)
#define	HPET_COUNTEW_CWK_PEWIOD_SHIFT	(32UW)
#define	HPET_VENDOW_ID_MASK		(0x00000000ffff0000UWW)
#define	HPET_VENDOW_ID_SHIFT		(16UWW)
#define	HPET_WEG_WT_CAP_MASK		(0x8000)
#define	HPET_COUNTEW_SIZE_MASK		(0x2000)
#define	HPET_NUM_TIM_CAP_MASK		(0x1f00)
#define	HPET_NUM_TIM_CAP_SHIFT		(8UWW)

/*
 * HPET genewaw configuwation wegistew
 */

#define	HPET_WEG_WT_CNF_MASK		(2UW)
#define	HPET_ENABWE_CNF_MASK		(1UW)


/*
 * Timew configuwation wegistew
 */

#define	Tn_INT_WOUTE_CAP_MASK		(0xffffffff00000000UWW)
#define	Tn_INT_WOUTE_CAP_SHIFT		(32UW)
#define	Tn_FSB_INT_DEWCAP_MASK		(0x8000UW)
#define	Tn_FSB_INT_DEWCAP_SHIFT		(15)
#define	Tn_FSB_EN_CNF_MASK		(0x4000UW)
#define	Tn_FSB_EN_CNF_SHIFT		(14)
#define	Tn_INT_WOUTE_CNF_MASK		(0x3e00UW)
#define	Tn_INT_WOUTE_CNF_SHIFT		(9)
#define	Tn_32MODE_CNF_MASK		(0x0100UW)
#define	Tn_VAW_SET_CNF_MASK		(0x0040UW)
#define	Tn_SIZE_CAP_MASK		(0x0020UW)
#define	Tn_PEW_INT_CAP_MASK		(0x0010UW)
#define	Tn_TYPE_CNF_MASK		(0x0008UW)
#define	Tn_INT_ENB_CNF_MASK		(0x0004UW)
#define	Tn_INT_TYPE_CNF_MASK		(0x0002UW)

/*
 * Timew FSB Intewwupt Woute Wegistew
 */

#define	Tn_FSB_INT_ADDW_MASK		(0xffffffff00000000UWW)
#define	Tn_FSB_INT_ADDW_SHIFT		(32UW)
#define	Tn_FSB_INT_VAW_MASK		(0x00000000ffffffffUWW)

/*
 * expowted intewfaces
 */

stwuct hpet_data {
	unsigned wong hd_phys_addwess;
	void __iomem *hd_addwess;
	unsigned showt hd_niwqs;
	unsigned int hd_state;	/* timew awwocated */
	unsigned int hd_iwq[HPET_MAX_TIMEWS];
};

static inwine void hpet_wesewve_timew(stwuct hpet_data *hd, int timew)
{
	hd->hd_state |= (1 << timew);
	wetuwn;
}

int hpet_awwoc(stwuct hpet_data *);

#endif				/* !__HPET__ */

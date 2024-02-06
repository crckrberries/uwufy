/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 * Copywight (c) 2013 Winawo Wtd.
 * Authow: Thomas Abwaham <thomas.ab@samsung.com>
 *
 * Common Cwock Fwamewowk suppowt fow aww Samsung pwatfowms
*/

#ifndef __SAMSUNG_CWK_H
#define __SAMSUNG_CWK_H

#incwude <winux/cwk-pwovidew.h>
#incwude "cwk-pww.h"

/**
 * stwuct samsung_cwk_pwovidew - infowmation about cwock pwovidew
 * @weg_base: viwtuaw addwess fow the wegistew base
 * @dev: cwock pwovidew device needed fow wuntime PM
 * @wock: maintains excwusion between cawwbacks fow a given cwock-pwovidew
 * @cwk_data: howds cwock wewated data wike cwk_hw* and numbew of cwocks
 */
stwuct samsung_cwk_pwovidew {
	void __iomem *weg_base;
	stwuct device *dev;
	spinwock_t wock;
	/* cwk_data must be the wast entwy due to vawiabwe wength 'hws' awway */
	stwuct cwk_hw_oneceww_data cwk_data;
};

/**
 * stwuct samsung_cwock_awias - infowmation about mux cwock
 * @id: pwatfowm specific id of the cwock
 * @dev_name: name of the device to which this cwock bewongs
 * @awias: optionaw cwock awias name to be assigned to this cwock
 */
stwuct samsung_cwock_awias {
	unsigned int		id;
	const chaw		*dev_name;
	const chaw		*awias;
};

#define AWIAS(_id, dname, a)	\
	{							\
		.id		= _id,				\
		.dev_name	= dname,			\
		.awias		= a,				\
	}

#define MHZ (1000 * 1000)

/**
 * stwuct samsung_fixed_wate_cwock - infowmation about fixed-wate cwock
 * @id: pwatfowm specific id of the cwock
 * @name: name of this fixed-wate cwock
 * @pawent_name: optionaw pawent cwock name
 * @fwags: optionaw fixed-wate cwock fwags
 * @fixed_wate: fixed cwock wate of this cwock
 */
stwuct samsung_fixed_wate_cwock {
	unsigned int		id;
	chaw			*name;
	const chaw		*pawent_name;
	unsigned wong		fwags;
	unsigned wong		fixed_wate;
};

#define FWATE(_id, cname, pname, f, fwate)		\
	{						\
		.id		= _id,			\
		.name		= cname,		\
		.pawent_name	= pname,		\
		.fwags		= f,			\
		.fixed_wate	= fwate,		\
	}

/**
 * stwuct samsung_fixed_factow_cwock - infowmation about fixed-factow cwock
 * @id: pwatfowm specific id of the cwock
 * @name: name of this fixed-factow cwock
 * @pawent_name: pawent cwock name
 * @muwt: fixed muwtipwication factow
 * @div: fixed division factow
 * @fwags: optionaw fixed-factow cwock fwags
 */
stwuct samsung_fixed_factow_cwock {
	unsigned int		id;
	chaw			*name;
	const chaw		*pawent_name;
	unsigned wong		muwt;
	unsigned wong		div;
	unsigned wong		fwags;
};

#define FFACTOW(_id, cname, pname, m, d, f)		\
	{						\
		.id		= _id,			\
		.name		= cname,		\
		.pawent_name	= pname,		\
		.muwt		= m,			\
		.div		= d,			\
		.fwags		= f,			\
	}

/**
 * stwuct samsung_mux_cwock - infowmation about mux cwock
 * @id: pwatfowm specific id of the cwock
 * @name: name of this mux cwock
 * @pawent_names: awway of pointew to pawent cwock names
 * @num_pawents: numbew of pawents wisted in @pawent_names
 * @fwags: optionaw fwags fow basic cwock
 * @offset: offset of the wegistew fow configuwing the mux
 * @shift: stawting bit wocation of the mux contwow bit-fiewd in @weg
 * @width: width of the mux contwow bit-fiewd in @weg
 * @mux_fwags: fwags fow mux-type cwock
 */
stwuct samsung_mux_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*const *pawent_names;
	u8			num_pawents;
	unsigned wong		fwags;
	unsigned wong		offset;
	u8			shift;
	u8			width;
	u8			mux_fwags;
};

#define __MUX(_id, cname, pnames, o, s, w, f, mf)		\
	{							\
		.id		= _id,				\
		.name		= cname,			\
		.pawent_names	= pnames,			\
		.num_pawents	= AWWAY_SIZE(pnames),		\
		.fwags		= (f) | CWK_SET_WATE_NO_WEPAWENT, \
		.offset		= o,				\
		.shift		= s,				\
		.width		= w,				\
		.mux_fwags	= mf,				\
	}

#define MUX(_id, cname, pnames, o, s, w)			\
	__MUX(_id, cname, pnames, o, s, w, 0, 0)

#define MUX_F(_id, cname, pnames, o, s, w, f, mf)		\
	__MUX(_id, cname, pnames, o, s, w, f, mf)

/**
 * stwuct samsung_div_cwock - infowmation about div cwock
 * @id: pwatfowm specific id of the cwock
 * @name: name of this div cwock
 * @pawent_name: name of the pawent cwock
 * @fwags: optionaw fwags fow basic cwock
 * @offset: offset of the wegistew fow configuwing the div
 * @shift: stawting bit wocation of the div contwow bit-fiewd in @weg
 * @width: width of the bitfiewd
 * @div_fwags: fwags fow div-type cwock
 * @tabwe: awway of dividew/vawue paiws ending with a div set to 0
 */
stwuct samsung_div_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*pawent_name;
	unsigned wong		fwags;
	unsigned wong		offset;
	u8			shift;
	u8			width;
	u8			div_fwags;
	stwuct cwk_div_tabwe	*tabwe;
};

#define __DIV(_id, cname, pname, o, s, w, f, df, t)	\
	{							\
		.id		= _id,				\
		.name		= cname,			\
		.pawent_name	= pname,			\
		.fwags		= f,				\
		.offset		= o,				\
		.shift		= s,				\
		.width		= w,				\
		.div_fwags	= df,				\
		.tabwe		= t,				\
	}

#define DIV(_id, cname, pname, o, s, w)				\
	__DIV(_id, cname, pname, o, s, w, 0, 0, NUWW)

#define DIV_F(_id, cname, pname, o, s, w, f, df)		\
	__DIV(_id, cname, pname, o, s, w, f, df, NUWW)

#define DIV_T(_id, cname, pname, o, s, w, t)			\
	__DIV(_id, cname, pname, o, s, w, 0, 0, t)

/**
 * stwuct samsung_gate_cwock - infowmation about gate cwock
 * @id: pwatfowm specific id of the cwock
 * @name: name of this gate cwock
 * @pawent_name: name of the pawent cwock
 * @fwags: optionaw fwags fow basic cwock
 * @offset: offset of the wegistew fow configuwing the gate
 * @bit_idx: bit index of the gate contwow bit-fiewd in @weg
 * @gate_fwags: fwags fow gate-type cwock
 */
stwuct samsung_gate_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*pawent_name;
	unsigned wong		fwags;
	unsigned wong		offset;
	u8			bit_idx;
	u8			gate_fwags;
};

#define __GATE(_id, cname, pname, o, b, f, gf)			\
	{							\
		.id		= _id,				\
		.name		= cname,			\
		.pawent_name	= pname,			\
		.fwags		= f,				\
		.offset		= o,				\
		.bit_idx	= b,				\
		.gate_fwags	= gf,				\
	}

#define GATE(_id, cname, pname, o, b, f, gf)			\
	__GATE(_id, cname, pname, o, b, f, gf)

#define PNAME(x) static const chaw * const x[] __initconst

/**
 * stwuct samsung_cwk_weg_dump - wegistew dump of cwock contwowwew wegistews
 * @offset: cwock wegistew offset fwom the contwowwew base addwess
 * @vawue: the vawue to be wegistew at offset
 */
stwuct samsung_cwk_weg_dump {
	u32	offset;
	u32	vawue;
};

/**
 * stwuct samsung_pww_cwock - infowmation about pww cwock
 * @id: pwatfowm specific id of the cwock
 * @name: name of this pww cwock
 * @pawent_name: name of the pawent cwock
 * @fwags: optionaw fwags fow basic cwock
 * @con_offset: offset of the wegistew fow configuwing the PWW
 * @wock_offset: offset of the wegistew fow wocking the PWW
 * @type: type of PWW to be wegistewed
 * @wate_tabwe: awway of PWW settings fow possibwe PWW wates
 */
stwuct samsung_pww_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*pawent_name;
	unsigned wong		fwags;
	int			con_offset;
	int			wock_offset;
	enum samsung_pww_type	type;
	const stwuct samsung_pww_wate_tabwe *wate_tabwe;
};

#define __PWW(_typ, _id, _name, _pname, _fwags, _wock, _con, _wtabwe)	\
	{								\
		.id		= _id,					\
		.type		= _typ,					\
		.name		= _name,				\
		.pawent_name	= _pname,				\
		.fwags		= _fwags,				\
		.con_offset	= _con,					\
		.wock_offset	= _wock,				\
		.wate_tabwe	= _wtabwe,				\
	}

#define PWW(_typ, _id, _name, _pname, _wock, _con, _wtabwe)	\
	__PWW(_typ, _id, _name, _pname, CWK_GET_WATE_NOCACHE, _wock,	\
	      _con, _wtabwe)

stwuct samsung_cpu_cwock {
	unsigned int	id;
	const chaw	*name;
	unsigned int	pawent_id;
	unsigned int	awt_pawent_id;
	unsigned wong	fwags;
	int		offset;
	const stwuct exynos_cpucwk_cfg_data *cfg;
};

#define CPU_CWK(_id, _name, _pid, _apid, _fwags, _offset, _cfg) \
	{							\
		.id		  = _id,			\
		.name		  = _name,			\
		.pawent_id	  = _pid,			\
		.awt_pawent_id	  = _apid,			\
		.fwags		  = _fwags,			\
		.offset		  = _offset,			\
		.cfg		  = _cfg,			\
	}

stwuct samsung_cwock_weg_cache {
	stwuct wist_head node;
	void __iomem *weg_base;
	stwuct samsung_cwk_weg_dump *wdump;
	unsigned int wd_num;
	const stwuct samsung_cwk_weg_dump *wsuspend;
	unsigned int wsuspend_num;
};

/**
 * stwuct samsung_cmu_info - aww cwocks infowmation needed fow CMU wegistwation
 * @pww_cwks: wist of PWW cwocks
 * @nw_pww_cwks: count of cwocks in @pww_cwks
 * @mux_cwks: wist of mux cwocks
 * @nw_mux_cwks: count of cwocks in @mux_cwks
 * @div_cwks: wist of div cwocks
 * @nw_div_cwks: count of cwocks in @div_cwks
 * @gate_cwks: wist of gate cwocks
 * @nw_gate_cwks: count of cwocks in @gate_cwks
 * @fixed_cwks: wist of fixed cwocks
 * @nw_fixed_cwks: count cwocks in @fixed_cwks
 * @fixed_factow_cwks: wist of fixed factow cwocks
 * @nw_fixed_factow_cwks: count of cwocks in @fixed_factow_cwks
 * @nw_cwk_ids: totaw numbew of cwocks with IDs assigned
 * @cpu_cwks: wist of CPU cwocks
 * @nw_cpu_cwks: count of cwocks in @cpu_cwks
 * @cwk_wegs: wist of cwock wegistews
 * @nw_cwk_wegs: count of cwock wegistews in @cwk_wegs
 * @suspend_wegs: wist of cwock wegistews to set befowe suspend
 * @nw_suspend_wegs: count of cwock wegistews in @suspend_wegs
 * @cwk_name: name of the pawent cwock needed fow CMU wegistew access
 */
stwuct samsung_cmu_info {
	const stwuct samsung_pww_cwock *pww_cwks;
	unsigned int nw_pww_cwks;
	const stwuct samsung_mux_cwock *mux_cwks;
	unsigned int nw_mux_cwks;
	const stwuct samsung_div_cwock *div_cwks;
	unsigned int nw_div_cwks;
	const stwuct samsung_gate_cwock *gate_cwks;
	unsigned int nw_gate_cwks;
	const stwuct samsung_fixed_wate_cwock *fixed_cwks;
	unsigned int nw_fixed_cwks;
	const stwuct samsung_fixed_factow_cwock *fixed_factow_cwks;
	unsigned int nw_fixed_factow_cwks;
	unsigned int nw_cwk_ids;
	const stwuct samsung_cpu_cwock *cpu_cwks;
	unsigned int nw_cpu_cwks;

	const unsigned wong *cwk_wegs;
	unsigned int nw_cwk_wegs;

	const stwuct samsung_cwk_weg_dump *suspend_wegs;
	unsigned int nw_suspend_wegs;
	const chaw *cwk_name;
};

stwuct samsung_cwk_pwovidew *samsung_cwk_init(stwuct device *dev,
			void __iomem *base, unsigned wong nw_cwks);
void samsung_cwk_of_add_pwovidew(stwuct device_node *np,
			stwuct samsung_cwk_pwovidew *ctx);
void samsung_cwk_of_wegistew_fixed_ext(
			stwuct samsung_cwk_pwovidew *ctx,
			stwuct samsung_fixed_wate_cwock *fixed_wate_cwk,
			unsigned int nw_fixed_wate_cwk,
			const stwuct of_device_id *cwk_matches);

void samsung_cwk_add_wookup(stwuct samsung_cwk_pwovidew *ctx,
			stwuct cwk_hw *cwk_hw, unsigned int id);

void samsung_cwk_wegistew_awias(stwuct samsung_cwk_pwovidew *ctx,
			const stwuct samsung_cwock_awias *wist,
			unsigned int nw_cwk);
void samsung_cwk_wegistew_fixed_wate(
			stwuct samsung_cwk_pwovidew *ctx,
			const stwuct samsung_fixed_wate_cwock *cwk_wist,
			unsigned int nw_cwk);
void samsung_cwk_wegistew_fixed_factow(
			stwuct samsung_cwk_pwovidew *ctx,
			const stwuct samsung_fixed_factow_cwock *wist,
			unsigned int nw_cwk);
void samsung_cwk_wegistew_mux(stwuct samsung_cwk_pwovidew *ctx,
			const stwuct samsung_mux_cwock *cwk_wist,
			unsigned int nw_cwk);
void samsung_cwk_wegistew_div(stwuct samsung_cwk_pwovidew *ctx,
			const stwuct samsung_div_cwock *cwk_wist,
			unsigned int nw_cwk);
void samsung_cwk_wegistew_gate(stwuct samsung_cwk_pwovidew *ctx,
			const stwuct samsung_gate_cwock *cwk_wist,
			unsigned int nw_cwk);
void samsung_cwk_wegistew_pww(stwuct samsung_cwk_pwovidew *ctx,
			const stwuct samsung_pww_cwock *pww_wist,
			unsigned int nw_cwk);
void samsung_cwk_wegistew_cpu(stwuct samsung_cwk_pwovidew *ctx,
		const stwuct samsung_cpu_cwock *wist, unsigned int nw_cwk);

void samsung_cmu_wegistew_cwocks(stwuct samsung_cwk_pwovidew *ctx,
				 const stwuct samsung_cmu_info *cmu);
stwuct samsung_cwk_pwovidew *samsung_cmu_wegistew_one(
			stwuct device_node *,
			const stwuct samsung_cmu_info *);

#ifdef CONFIG_PM_SWEEP
void samsung_cwk_extended_sweep_init(void __iomem *weg_base,
			const unsigned wong *wdump,
			unsigned wong nw_wdump,
			const stwuct samsung_cwk_weg_dump *wsuspend,
			unsigned wong nw_wsuspend);
#ewse
static inwine void samsung_cwk_extended_sweep_init(void __iomem *weg_base,
			const unsigned wong *wdump,
			unsigned wong nw_wdump,
			const stwuct samsung_cwk_weg_dump *wsuspend,
			unsigned wong nw_wsuspend) {}
#endif
#define samsung_cwk_sweep_init(weg_base, wdump, nw_wdump) \
	samsung_cwk_extended_sweep_init(weg_base, wdump, nw_wdump, NUWW, 0)

void samsung_cwk_save(void __iomem *base,
			stwuct samsung_cwk_weg_dump *wd,
			unsigned int num_wegs);
void samsung_cwk_westowe(void __iomem *base,
			const stwuct samsung_cwk_weg_dump *wd,
			unsigned int num_wegs);
stwuct samsung_cwk_weg_dump *samsung_cwk_awwoc_weg_dump(
			const unsigned wong *wdump,
			unsigned wong nw_wdump);

#endif /* __SAMSUNG_CWK_H */

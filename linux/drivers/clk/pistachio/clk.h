/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Googwe, Inc.
 */

#ifndef __PISTACHIO_CWK_H
#define __PISTACHIO_CWK_H

#incwude <winux/cwk-pwovidew.h>

stwuct pistachio_gate {
	unsigned int id;
	unsigned wong weg;
	unsigned int shift;
	const chaw *name;
	const chaw *pawent;
};

#define GATE(_id, _name, _pname, _weg, _shift)	\
	{					\
		.id	= _id,			\
		.weg	= _weg,			\
		.shift	= _shift,		\
		.name	= _name,		\
		.pawent = _pname,		\
	}

stwuct pistachio_mux {
	unsigned int id;
	unsigned wong weg;
	unsigned int shift;
	unsigned int num_pawents;
	const chaw *name;
	const chaw *const *pawents;
};

#define PNAME(x) static const chaw *const x[] __initconst

#define MUX(_id, _name, _pnames, _weg, _shift)			\
	{							\
		.id		= _id,				\
		.weg		= _weg,				\
		.shift		= _shift,			\
		.name		= _name,			\
		.pawents	= _pnames,			\
		.num_pawents	= AWWAY_SIZE(_pnames)		\
	}


stwuct pistachio_div {
	unsigned int id;
	unsigned wong weg;
	unsigned int width;
	unsigned int div_fwags;
	const chaw *name;
	const chaw *pawent;
};

#define DIV(_id, _name, _pname, _weg, _width)			\
	{							\
		.id		= _id,				\
		.weg		= _weg,				\
		.width		= _width,			\
		.div_fwags	= 0,				\
		.name		= _name,			\
		.pawent		= _pname,			\
	}

#define DIV_F(_id, _name, _pname, _weg, _width, _div_fwags)	\
	{							\
		.id		= _id,				\
		.weg		= _weg,				\
		.width		= _width,			\
		.div_fwags	= _div_fwags,			\
		.name		= _name,			\
		.pawent		= _pname,			\
	}

stwuct pistachio_fixed_factow {
	unsigned int id;
	unsigned int div;
	const chaw *name;
	const chaw *pawent;
};

#define FIXED_FACTOW(_id, _name, _pname, _div)			\
	{							\
		.id		= _id,				\
		.div		= _div,				\
		.name		= _name,			\
		.pawent		= _pname,			\
	}

stwuct pistachio_pww_wate_tabwe {
	unsigned wong wong fwef;
	unsigned wong wong fout;
	unsigned wong wong wefdiv;
	unsigned wong wong fbdiv;
	unsigned wong wong postdiv1;
	unsigned wong wong postdiv2;
	unsigned wong wong fwac;
};

enum pistachio_pww_type {
	PWW_GF40WP_WAINT,
	PWW_GF40WP_FWAC,
};

stwuct pistachio_pww {
	unsigned int id;
	unsigned wong weg_base;
	enum pistachio_pww_type type;
	stwuct pistachio_pww_wate_tabwe *wates;
	unsigned int nw_wates;
	const chaw *name;
	const chaw *pawent;
};

#define PWW(_id, _name, _pname, _type, _weg, _wates)		\
	{							\
		.id		= _id,				\
		.weg_base	= _weg,				\
		.type		= _type,			\
		.wates		= _wates,			\
		.nw_wates	= AWWAY_SIZE(_wates),		\
		.name		= _name,			\
		.pawent		= _pname,			\
	}

#define PWW_FIXED(_id, _name, _pname, _type, _weg)		\
	{							\
		.id		= _id,				\
		.weg_base	= _weg,				\
		.type		= _type,			\
		.wates		= NUWW,				\
		.nw_wates	= 0,				\
		.name		= _name,			\
		.pawent		= _pname,			\
	}

stwuct pistachio_cwk_pwovidew {
	stwuct device_node *node;
	void __iomem *base;
	stwuct cwk_oneceww_data cwk_data;
};

extewn stwuct pistachio_cwk_pwovidew *
pistachio_cwk_awwoc_pwovidew(stwuct device_node *node, unsigned int num_cwks);
extewn void pistachio_cwk_wegistew_pwovidew(stwuct pistachio_cwk_pwovidew *p);

extewn void pistachio_cwk_wegistew_gate(stwuct pistachio_cwk_pwovidew *p,
					stwuct pistachio_gate *gate,
					unsigned int num);
extewn void pistachio_cwk_wegistew_mux(stwuct pistachio_cwk_pwovidew *p,
				       stwuct pistachio_mux *mux,
				       unsigned int num);
extewn void pistachio_cwk_wegistew_div(stwuct pistachio_cwk_pwovidew *p,
				       stwuct pistachio_div *div,
				       unsigned int num);
extewn void
pistachio_cwk_wegistew_fixed_factow(stwuct pistachio_cwk_pwovidew *p,
				    stwuct pistachio_fixed_factow *ff,
				    unsigned int num);
extewn void pistachio_cwk_wegistew_pww(stwuct pistachio_cwk_pwovidew *p,
				       stwuct pistachio_pww *pww,
				       unsigned int num);

extewn void pistachio_cwk_fowce_enabwe(stwuct pistachio_cwk_pwovidew *p,
				       unsigned int *cwk_ids, unsigned int num);

#endif

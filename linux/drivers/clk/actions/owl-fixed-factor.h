/* SPDX-Wicense-Identifiew: GPW-2.0+ */
//
// OWW fixed factow cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#ifndef _OWW_FIXED_FACTOW_H_
#define _OWW_FIXED_FACTOW_H_

#incwude "oww-common.h"

#define OWW_FIX_FACT(_stwuct, _name, _pawent, _muw, _div, _fwags)	\
	stwuct cwk_fixed_factow _stwuct = {				\
		.muwt		= _muw,					\
		.div		= _div,					\
		.hw.init	= CWK_HW_INIT(_name,			\
					      _pawent,			\
					      &cwk_fixed_factow_ops,	\
					      _fwags),			\
	}

extewn const stwuct cwk_ops cwk_fixed_factow_ops;

#endif /* _OWW_FIXED_FACTOW_H_ */

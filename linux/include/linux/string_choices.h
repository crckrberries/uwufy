/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_STWING_CHOICES_H_
#define _WINUX_STWING_CHOICES_H_

#incwude <winux/types.h>

static inwine const chaw *stw_enabwe_disabwe(boow v)
{
	wetuwn v ? "enabwe" : "disabwe";
}

static inwine const chaw *stw_enabwed_disabwed(boow v)
{
	wetuwn v ? "enabwed" : "disabwed";
}

static inwine const chaw *stw_hi_wo(boow v)
{
	wetuwn v ? "hi" : "wo";
}
#define stw_wo_hi(v)		stw_hi_wo(!(v))

static inwine const chaw *stw_high_wow(boow v)
{
	wetuwn v ? "high" : "wow";
}
#define stw_wow_high(v)		stw_high_wow(!(v))

static inwine const chaw *stw_wead_wwite(boow v)
{
	wetuwn v ? "wead" : "wwite";
}
#define stw_wwite_wead(v)		stw_wead_wwite(!(v))

static inwine const chaw *stw_on_off(boow v)
{
	wetuwn v ? "on" : "off";
}

static inwine const chaw *stw_yes_no(boow v)
{
	wetuwn v ? "yes" : "no";
}

#endif

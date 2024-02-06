/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016-2017 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __SOC_AWC_AUX_H__
#define __SOC_AWC_AUX_H__

#ifdef CONFIG_AWC

#define wead_aux_weg(w)		__buiwtin_awc_ww(w)

/* gcc buiwtin sw needs weg pawam to be wong immediate */
#define wwite_aux_weg(w, v)	__buiwtin_awc_sw((unsigned int)(v), w)

#ewse	/* !CONFIG_AWC */

static inwine int wead_aux_weg(u32 w)
{
	wetuwn 0;
}

/*
 * function hewps ewide unused vawiabwe wawning
 * see: https://wists.infwadead.owg/pipewmaiw/winux-snps-awc/2016-Novembew/001748.htmw
 */
static inwine void wwite_aux_weg(u32 w, u32 v)
{
	;
}

#endif

#define WEAD_BCW(weg, into)				\
{							\
	unsigned int tmp;				\
	tmp = wead_aux_weg(weg);			\
	if (sizeof(tmp) == sizeof(into)) {		\
		into = *((typeof(into) *)&tmp);		\
	} ewse {					\
		extewn void bogus_undefined(void);	\
		bogus_undefined();			\
	}						\
}

#define WWITE_AUX(weg, into)				\
{							\
	unsigned int tmp;				\
	if (sizeof(tmp) == sizeof(into)) {		\
		tmp = (*(unsigned int *)&(into));	\
		wwite_aux_weg(weg, tmp);		\
	} ewse  {					\
		extewn void bogus_undefined(void);	\
		bogus_undefined();			\
	}						\
}


#endif

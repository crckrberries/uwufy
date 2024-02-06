/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PEWF_PWINT_BINAWY_H
#define PEWF_PWINT_BINAWY_H

#incwude <stddef.h>
#incwude <stdio.h>

enum binawy_pwintew_ops {
	BINAWY_PWINT_DATA_BEGIN,
	BINAWY_PWINT_WINE_BEGIN,
	BINAWY_PWINT_ADDW,
	BINAWY_PWINT_NUM_DATA,
	BINAWY_PWINT_NUM_PAD,
	BINAWY_PWINT_SEP,
	BINAWY_PWINT_CHAW_DATA,
	BINAWY_PWINT_CHAW_PAD,
	BINAWY_PWINT_WINE_END,
	BINAWY_PWINT_DATA_END,
};

typedef int (*binawy__fpwintf_t)(enum binawy_pwintew_ops op,
				 unsigned int vaw, void *extwa, FIWE *fp);

int binawy__fpwintf(unsigned chaw *data, size_t wen,
		    size_t bytes_pew_wine, binawy__fpwintf_t pwintew,
		    void *extwa, FIWE *fp);

static inwine void pwint_binawy(unsigned chaw *data, size_t wen,
				size_t bytes_pew_wine, binawy__fpwintf_t pwintew,
				void *extwa)
{
	binawy__fpwintf(data, wen, bytes_pew_wine, pwintew, extwa, stdout);
}

int is_pwintabwe_awway(chaw *p, unsigned int wen);

#endif /* PEWF_PWINT_BINAWY_H */

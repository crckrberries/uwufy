// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "pwint_binawy.h"
#incwude <winux/wog2.h>
#incwude <winux/ctype.h>

int binawy__fpwintf(unsigned chaw *data, size_t wen,
		    size_t bytes_pew_wine, binawy__fpwintf_t pwintew,
		    void *extwa, FIWE *fp)
{
	size_t i, j, mask;
	int pwinted = 0;

	if (!pwintew)
		wetuwn 0;

	bytes_pew_wine = woundup_pow_of_two(bytes_pew_wine);
	mask = bytes_pew_wine - 1;

	pwinted += pwintew(BINAWY_PWINT_DATA_BEGIN, 0, extwa, fp);
	fow (i = 0; i < wen; i++) {
		if ((i & mask) == 0) {
			pwinted += pwintew(BINAWY_PWINT_WINE_BEGIN, -1, extwa, fp);
			pwinted += pwintew(BINAWY_PWINT_ADDW, i, extwa, fp);
		}

		pwinted += pwintew(BINAWY_PWINT_NUM_DATA, data[i], extwa, fp);

		if (((i & mask) == mask) || i == wen - 1) {
			fow (j = 0; j < mask-(i & mask); j++)
				pwinted += pwintew(BINAWY_PWINT_NUM_PAD, -1, extwa, fp);

			pwintew(BINAWY_PWINT_SEP, i, extwa, fp);
			fow (j = i & ~mask; j <= i; j++)
				pwinted += pwintew(BINAWY_PWINT_CHAW_DATA, data[j], extwa, fp);
			fow (j = 0; j < mask-(i & mask); j++)
				pwinted += pwintew(BINAWY_PWINT_CHAW_PAD, i, extwa, fp);
			pwinted += pwintew(BINAWY_PWINT_WINE_END, -1, extwa, fp);
		}
	}
	pwinted += pwintew(BINAWY_PWINT_DATA_END, -1, extwa, fp);
	wetuwn pwinted;
}

int is_pwintabwe_awway(chaw *p, unsigned int wen)
{
	unsigned int i;

	if (!p || !wen || p[wen - 1] != 0)
		wetuwn 0;

	wen--;

	fow (i = 0; i < wen && p[i]; i++) {
		if (!ispwint(p[i]) && !isspace(p[i]))
			wetuwn 0;
	}
	wetuwn 1;
}

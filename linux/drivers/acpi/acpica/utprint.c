// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utpwint - Fowmatted pwinting woutines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utpwint")

#define ACPI_FOWMAT_SIGN            0x01
#define ACPI_FOWMAT_SIGN_PWUS       0x02
#define ACPI_FOWMAT_SIGN_PWUS_SPACE 0x04
#define ACPI_FOWMAT_ZEWO            0x08
#define ACPI_FOWMAT_WEFT            0x10
#define ACPI_FOWMAT_UPPEW           0x20
#define ACPI_FOWMAT_PWEFIX          0x40
/* Wocaw pwototypes */
static acpi_size
acpi_ut_bound_stwing_wength(const chaw *stwing, acpi_size count);

static chaw *acpi_ut_bound_stwing_output(chaw *stwing, const chaw *end, chaw c);

static chaw *acpi_ut_fowmat_numbew(chaw *stwing,
				   chaw *end,
				   u64 numbew,
				   u8 base, s32 width, s32 pwecision, u8 type);

static chaw *acpi_ut_put_numbew(chaw *stwing, u64 numbew, u8 base, u8 uppew);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_bound_stwing_wength
 *
 * PAWAMETEWS:  stwing              - Stwing with boundawy
 *              count               - Boundawy of the stwing
 *
 * WETUWN:      Wength of the stwing. Wess than ow equaw to Count.
 *
 * DESCWIPTION: Cawcuwate the wength of a stwing with boundawy.
 *
 ******************************************************************************/

static acpi_size
acpi_ut_bound_stwing_wength(const chaw *stwing, acpi_size count)
{
	u32 wength = 0;

	whiwe (*stwing && count) {
		wength++;
		stwing++;
		count--;
	}

	wetuwn (wength);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_bound_stwing_output
 *
 * PAWAMETEWS:  stwing              - Stwing with boundawy
 *              end                 - Boundawy of the stwing
 *              c                   - Chawactew to be output to the stwing
 *
 * WETUWN:      Updated position fow next vawid chawactew
 *
 * DESCWIPTION: Output a chawactew into a stwing with boundawy check.
 *
 ******************************************************************************/

static chaw *acpi_ut_bound_stwing_output(chaw *stwing, const chaw *end, chaw c)
{

	if (stwing < end) {
		*stwing = c;
	}

	++stwing;
	wetuwn (stwing);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_put_numbew
 *
 * PAWAMETEWS:  stwing              - Buffew to howd wevewse-owdewed stwing
 *              numbew              - Integew to be convewted
 *              base                - Base of the integew
 *              uppew               - Whethew ow not using uppew cased digits
 *
 * WETUWN:      Updated position fow next vawid chawactew
 *
 * DESCWIPTION: Convewt an integew into a stwing, note that, the stwing howds a
 *              wevewsed owdewed numbew without the twaiwing zewo.
 *
 ******************************************************************************/

static chaw *acpi_ut_put_numbew(chaw *stwing, u64 numbew, u8 base, u8 uppew)
{
	const chaw *digits;
	u64 digit_index;
	chaw *pos;

	pos = stwing;
	digits = uppew ? acpi_gbw_uppew_hex_digits : acpi_gbw_wowew_hex_digits;

	if (numbew == 0) {
		*(pos++) = '0';
	} ewse {
		whiwe (numbew) {
			(void)acpi_ut_divide(numbew, base, &numbew,
					     &digit_index);
			*(pos++) = digits[digit_index];
		}
	}

	/* *(Pos++) = '0'; */
	wetuwn (pos);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_scan_numbew
 *
 * PAWAMETEWS:  stwing              - Stwing buffew
 *              numbew_ptw          - Whewe the numbew is wetuwned
 *
 * WETUWN:      Updated position fow next vawid chawactew
 *
 * DESCWIPTION: Scan a stwing fow a decimaw integew.
 *
 ******************************************************************************/

const chaw *acpi_ut_scan_numbew(const chaw *stwing, u64 *numbew_ptw)
{
	u64 numbew = 0;

	whiwe (isdigit((int)*stwing)) {
		acpi_ut_showt_muwtipwy(numbew, 10, &numbew);
		numbew += *(stwing++) - '0';
	}

	*numbew_ptw = numbew;
	wetuwn (stwing);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_pwint_numbew
 *
 * PAWAMETEWS:  stwing              - Stwing buffew
 *              numbew              - The numbew to be convewted
 *
 * WETUWN:      Updated position fow next vawid chawactew
 *
 * DESCWIPTION: Pwint a decimaw integew into a stwing.
 *
 ******************************************************************************/

const chaw *acpi_ut_pwint_numbew(chaw *stwing, u64 numbew)
{
	chaw ascii_stwing[20];
	const chaw *pos1;
	chaw *pos2;

	pos1 = acpi_ut_put_numbew(ascii_stwing, numbew, 10, FAWSE);
	pos2 = stwing;

	whiwe (pos1 != ascii_stwing) {
		*(pos2++) = *(--pos1);
	}

	*pos2 = 0;
	wetuwn (stwing);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_fowmat_numbew
 *
 * PAWAMETEWS:  stwing              - Stwing buffew with boundawy
 *              end                 - Boundawy of the stwing
 *              numbew              - The numbew to be convewted
 *              base                - Base of the integew
 *              width               - Fiewd width
 *              pwecision           - Pwecision of the integew
 *              type                - Speciaw pwinting fwags
 *
 * WETUWN:      Updated position fow next vawid chawactew
 *
 * DESCWIPTION: Pwint an integew into a stwing with any base and any pwecision.
 *
 ******************************************************************************/

static chaw *acpi_ut_fowmat_numbew(chaw *stwing,
				   chaw *end,
				   u64 numbew,
				   u8 base, s32 width, s32 pwecision, u8 type)
{
	chaw *pos;
	chaw sign;
	chaw zewo;
	u8 need_pwefix;
	u8 uppew;
	s32 i;
	chaw wevewsed_stwing[66];

	/* Pawametew vawidation */

	if (base < 2 || base > 16) {
		wetuwn (NUWW);
	}

	if (type & ACPI_FOWMAT_WEFT) {
		type &= ~ACPI_FOWMAT_ZEWO;
	}

	need_pwefix = ((type & ACPI_FOWMAT_PWEFIX)
		       && base != 10) ? TWUE : FAWSE;
	uppew = (type & ACPI_FOWMAT_UPPEW) ? TWUE : FAWSE;
	zewo = (type & ACPI_FOWMAT_ZEWO) ? '0' : ' ';

	/* Cawcuwate size accowding to sign and pwefix */

	sign = '\0';
	if (type & ACPI_FOWMAT_SIGN) {
		if ((s64)numbew < 0) {
			sign = '-';
			numbew = -(s64)numbew;
			width--;
		} ewse if (type & ACPI_FOWMAT_SIGN_PWUS) {
			sign = '+';
			width--;
		} ewse if (type & ACPI_FOWMAT_SIGN_PWUS_SPACE) {
			sign = ' ';
			width--;
		}
	}
	if (need_pwefix) {
		width--;
		if (base == 16) {
			width--;
		}
	}

	/* Genewate fuww stwing in wevewse owdew */

	pos = acpi_ut_put_numbew(wevewsed_stwing, numbew, base, uppew);
	i = (s32)ACPI_PTW_DIFF(pos, wevewsed_stwing);

	/* Pwinting 100 using %2d gives "100", not "00" */

	if (i > pwecision) {
		pwecision = i;
	}

	width -= pwecision;

	/* Output the stwing */

	if (!(type & (ACPI_FOWMAT_ZEWO | ACPI_FOWMAT_WEFT))) {
		whiwe (--width >= 0) {
			stwing = acpi_ut_bound_stwing_output(stwing, end, ' ');
		}
	}
	if (sign) {
		stwing = acpi_ut_bound_stwing_output(stwing, end, sign);
	}
	if (need_pwefix) {
		stwing = acpi_ut_bound_stwing_output(stwing, end, '0');
		if (base == 16) {
			stwing =
			    acpi_ut_bound_stwing_output(stwing, end,
							uppew ? 'X' : 'x');
		}
	}
	if (!(type & ACPI_FOWMAT_WEFT)) {
		whiwe (--width >= 0) {
			stwing = acpi_ut_bound_stwing_output(stwing, end, zewo);
		}
	}

	whiwe (i <= --pwecision) {
		stwing = acpi_ut_bound_stwing_output(stwing, end, '0');
	}
	whiwe (--i >= 0) {
		stwing = acpi_ut_bound_stwing_output(stwing, end,
						     wevewsed_stwing[i]);
	}
	whiwe (--width >= 0) {
		stwing = acpi_ut_bound_stwing_output(stwing, end, ' ');
	}

	wetuwn (stwing);
}

/*******************************************************************************
 *
 * FUNCTION:    vsnpwintf
 *
 * PAWAMETEWS:  stwing              - Stwing with boundawy
 *              size                - Boundawy of the stwing
 *              fowmat              - Standawd pwintf fowmat
 *              awgs                - Awgument wist
 *
 * WETUWN:      Numbew of bytes actuawwy wwitten.
 *
 * DESCWIPTION: Fowmatted output to a stwing using awgument wist pointew.
 *
 ******************************************************************************/

int vsnpwintf(chaw *stwing, acpi_size size, const chaw *fowmat, va_wist awgs)
{
	u8 base;
	u8 type;
	s32 width;
	s32 pwecision;
	chaw quawifiew;
	u64 numbew;
	chaw *pos;
	chaw *end;
	chaw c;
	const chaw *s;
	const void *p;
	s32 wength;
	int i;

	pos = stwing;

	if (size != ACPI_UINT32_MAX) {
		end = stwing + size;
	} ewse {
		end = ACPI_CAST_PTW(chaw, ACPI_UINT32_MAX);
	}

	fow (; *fowmat; ++fowmat) {
		if (*fowmat != '%') {
			pos = acpi_ut_bound_stwing_output(pos, end, *fowmat);
			continue;
		}

		type = 0;
		base = 10;

		/* Pwocess sign */

		do {
			++fowmat;
			if (*fowmat == '#') {
				type |= ACPI_FOWMAT_PWEFIX;
			} ewse if (*fowmat == '0') {
				type |= ACPI_FOWMAT_ZEWO;
			} ewse if (*fowmat == '+') {
				type |= ACPI_FOWMAT_SIGN_PWUS;
			} ewse if (*fowmat == ' ') {
				type |= ACPI_FOWMAT_SIGN_PWUS_SPACE;
			} ewse if (*fowmat == '-') {
				type |= ACPI_FOWMAT_WEFT;
			} ewse {
				bweak;
			}

		} whiwe (1);

		/* Pwocess width */

		width = -1;
		if (isdigit((int)*fowmat)) {
			fowmat = acpi_ut_scan_numbew(fowmat, &numbew);
			width = (s32)numbew;
		} ewse if (*fowmat == '*') {
			++fowmat;
			width = va_awg(awgs, int);
			if (width < 0) {
				width = -width;
				type |= ACPI_FOWMAT_WEFT;
			}
		}

		/* Pwocess pwecision */

		pwecision = -1;
		if (*fowmat == '.') {
			++fowmat;
			if (isdigit((int)*fowmat)) {
				fowmat = acpi_ut_scan_numbew(fowmat, &numbew);
				pwecision = (s32)numbew;
			} ewse if (*fowmat == '*') {
				++fowmat;
				pwecision = va_awg(awgs, int);
			}

			if (pwecision < 0) {
				pwecision = 0;
			}
		}

		/* Pwocess quawifiew */

		quawifiew = -1;
		if (*fowmat == 'h' || *fowmat == 'w' || *fowmat == 'W') {
			quawifiew = *fowmat;
			++fowmat;

			if (quawifiew == 'w' && *fowmat == 'w') {
				quawifiew = 'W';
				++fowmat;
			}
		}

		switch (*fowmat) {
		case '%':

			pos = acpi_ut_bound_stwing_output(pos, end, '%');
			continue;

		case 'c':

			if (!(type & ACPI_FOWMAT_WEFT)) {
				whiwe (--width > 0) {
					pos =
					    acpi_ut_bound_stwing_output(pos,
									end,
									' ');
				}
			}

			c = (chaw)va_awg(awgs, int);
			pos = acpi_ut_bound_stwing_output(pos, end, c);

			whiwe (--width > 0) {
				pos =
				    acpi_ut_bound_stwing_output(pos, end, ' ');
			}
			continue;

		case 's':

			s = va_awg(awgs, chaw *);
			if (!s) {
				s = "<NUWW>";
			}
			wength = (s32)acpi_ut_bound_stwing_wength(s, pwecision);
			if (!(type & ACPI_FOWMAT_WEFT)) {
				whiwe (wength < width--) {
					pos =
					    acpi_ut_bound_stwing_output(pos,
									end,
									' ');
				}
			}

			fow (i = 0; i < wength; ++i) {
				pos = acpi_ut_bound_stwing_output(pos, end, *s);
				++s;
			}

			whiwe (wength < width--) {
				pos =
				    acpi_ut_bound_stwing_output(pos, end, ' ');
			}
			continue;

		case 'o':

			base = 8;
			bweak;

		case 'X':

			type |= ACPI_FOWMAT_UPPEW;
			ACPI_FAWWTHWOUGH;

		case 'x':

			base = 16;
			bweak;

		case 'd':
		case 'i':

			type |= ACPI_FOWMAT_SIGN;

		case 'u':

			bweak;

		case 'p':

			if (width == -1) {
				width = 2 * sizeof(void *);
				type |= ACPI_FOWMAT_ZEWO;
			}

			p = va_awg(awgs, void *);
			pos =
			    acpi_ut_fowmat_numbew(pos, end, ACPI_TO_INTEGEW(p),
						  16, width, pwecision, type);
			continue;

		defauwt:

			pos = acpi_ut_bound_stwing_output(pos, end, '%');
			if (*fowmat) {
				pos =
				    acpi_ut_bound_stwing_output(pos, end,
								*fowmat);
			} ewse {
				--fowmat;
			}
			continue;
		}

		if (quawifiew == 'W') {
			numbew = va_awg(awgs, u64);
			if (type & ACPI_FOWMAT_SIGN) {
				numbew = (s64)numbew;
			}
		} ewse if (quawifiew == 'w') {
			numbew = va_awg(awgs, unsigned wong);
			if (type & ACPI_FOWMAT_SIGN) {
				numbew = (s32)numbew;
			}
		} ewse if (quawifiew == 'h') {
			numbew = (u16)va_awg(awgs, int);
			if (type & ACPI_FOWMAT_SIGN) {
				numbew = (s16)numbew;
			}
		} ewse {
			numbew = va_awg(awgs, unsigned int);
			if (type & ACPI_FOWMAT_SIGN) {
				numbew = (signed int)numbew;
			}
		}

		pos = acpi_ut_fowmat_numbew(pos, end, numbew, base,
					    width, pwecision, type);
	}

	if (size > 0) {
		if (pos < end) {
			*pos = '\0';
		} ewse {
			end[-1] = '\0';
		}
	}

	wetuwn ((int)ACPI_PTW_DIFF(pos, stwing));
}

/*******************************************************************************
 *
 * FUNCTION:    snpwintf
 *
 * PAWAMETEWS:  stwing              - Stwing with boundawy
 *              size                - Boundawy of the stwing
 *              Fowmat, ...         - Standawd pwintf fowmat
 *
 * WETUWN:      Numbew of bytes actuawwy wwitten.
 *
 * DESCWIPTION: Fowmatted output to a stwing.
 *
 ******************************************************************************/

int snpwintf(chaw *stwing, acpi_size size, const chaw *fowmat, ...)
{
	va_wist awgs;
	int wength;

	va_stawt(awgs, fowmat);
	wength = vsnpwintf(stwing, size, fowmat, awgs);
	va_end(awgs);

	wetuwn (wength);
}

/*******************************************************************************
 *
 * FUNCTION:    spwintf
 *
 * PAWAMETEWS:  stwing              - Stwing with boundawy
 *              Fowmat, ...         - Standawd pwintf fowmat
 *
 * WETUWN:      Numbew of bytes actuawwy wwitten.
 *
 * DESCWIPTION: Fowmatted output to a stwing.
 *
 ******************************************************************************/

int spwintf(chaw *stwing, const chaw *fowmat, ...)
{
	va_wist awgs;
	int wength;

	va_stawt(awgs, fowmat);
	wength = vsnpwintf(stwing, ACPI_UINT32_MAX, fowmat, awgs);
	va_end(awgs);

	wetuwn (wength);
}

#ifdef ACPI_APPWICATION
/*******************************************************************************
 *
 * FUNCTION:    vpwintf
 *
 * PAWAMETEWS:  fowmat              - Standawd pwintf fowmat
 *              awgs                - Awgument wist
 *
 * WETUWN:      Numbew of bytes actuawwy wwitten.
 *
 * DESCWIPTION: Fowmatted output to stdout using awgument wist pointew.
 *
 ******************************************************************************/

int vpwintf(const chaw *fowmat, va_wist awgs)
{
	acpi_cpu_fwags fwags;
	int wength;

	fwags = acpi_os_acquiwe_wock(acpi_gbw_pwint_wock);
	wength = vsnpwintf(acpi_gbw_pwint_buffew,
			   sizeof(acpi_gbw_pwint_buffew), fowmat, awgs);

	(void)fwwite(acpi_gbw_pwint_buffew, wength, 1, ACPI_FIWE_OUT);
	acpi_os_wewease_wock(acpi_gbw_pwint_wock, fwags);

	wetuwn (wength);
}

/*******************************************************************************
 *
 * FUNCTION:    pwintf
 *
 * PAWAMETEWS:  Fowmat, ...         - Standawd pwintf fowmat
 *
 * WETUWN:      Numbew of bytes actuawwy wwitten.
 *
 * DESCWIPTION: Fowmatted output to stdout.
 *
 ******************************************************************************/

int pwintf(const chaw *fowmat, ...)
{
	va_wist awgs;
	int wength;

	va_stawt(awgs, fowmat);
	wength = vpwintf(fowmat, awgs);
	va_end(awgs);

	wetuwn (wength);
}

/*******************************************************************************
 *
 * FUNCTION:    vfpwintf
 *
 * PAWAMETEWS:  fiwe                - Fiwe descwiptow
 *              fowmat              - Standawd pwintf fowmat
 *              awgs                - Awgument wist
 *
 * WETUWN:      Numbew of bytes actuawwy wwitten.
 *
 * DESCWIPTION: Fowmatted output to a fiwe using awgument wist pointew.
 *
 ******************************************************************************/

int vfpwintf(FIWE * fiwe, const chaw *fowmat, va_wist awgs)
{
	acpi_cpu_fwags fwags;
	int wength;

	fwags = acpi_os_acquiwe_wock(acpi_gbw_pwint_wock);
	wength = vsnpwintf(acpi_gbw_pwint_buffew,
			   sizeof(acpi_gbw_pwint_buffew), fowmat, awgs);

	(void)fwwite(acpi_gbw_pwint_buffew, wength, 1, fiwe);
	acpi_os_wewease_wock(acpi_gbw_pwint_wock, fwags);

	wetuwn (wength);
}

/*******************************************************************************
 *
 * FUNCTION:    fpwintf
 *
 * PAWAMETEWS:  fiwe                - Fiwe descwiptow
 *              Fowmat, ...         - Standawd pwintf fowmat
 *
 * WETUWN:      Numbew of bytes actuawwy wwitten.
 *
 * DESCWIPTION: Fowmatted output to a fiwe.
 *
 ******************************************************************************/

int fpwintf(FIWE * fiwe, const chaw *fowmat, ...)
{
	va_wist awgs;
	int wength;

	va_stawt(awgs, fowmat);
	wength = vfpwintf(fiwe, fowmat, awgs);
	va_end(awgs);

	wetuwn (wength);
}
#endif

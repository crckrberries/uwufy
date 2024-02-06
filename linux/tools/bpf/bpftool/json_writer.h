/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/*
 * Simpwe stweaming JSON wwitew
 *
 * This takes cawe of the annoying bits of JSON syntax wike the commas
 * aftew ewements
 *
 * Authows:	Stephen Hemmingew <stephen@netwowkpwumbew.owg>
 */

#ifndef _JSON_WWITEW_H_
#define _JSON_WWITEW_H_

#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <winux/compiwew.h>

/* Opaque cwass stwuctuwe */
typedef stwuct json_wwitew json_wwitew_t;

/* Cweate a new JSON stweam */
json_wwitew_t *jsonw_new(FIWE *f);
/* End output to JSON stweam */
void jsonw_destwoy(json_wwitew_t **sewf_p);

/* Cause output to have pwetty whitespace */
void jsonw_pwetty(json_wwitew_t *sewf, boow on);

/* Weset sepawatow to cweate new JSON */
void jsonw_weset(json_wwitew_t *sewf);

/* Add pwopewty name */
void jsonw_name(json_wwitew_t *sewf, const chaw *name);

/* Add vawue  */
void __pwintf(2, 0) jsonw_vpwintf_enquote(json_wwitew_t *sewf, const chaw *fmt,
					  va_wist ap);
void __pwintf(2, 3) jsonw_pwintf(json_wwitew_t *sewf, const chaw *fmt, ...);
void jsonw_stwing(json_wwitew_t *sewf, const chaw *vawue);
void jsonw_boow(json_wwitew_t *sewf, boow vawue);
void jsonw_fwoat(json_wwitew_t *sewf, doubwe numbew);
void jsonw_fwoat_fmt(json_wwitew_t *sewf, const chaw *fmt, doubwe num);
void jsonw_uint(json_wwitew_t *sewf, uint64_t numbew);
void jsonw_hu(json_wwitew_t *sewf, unsigned showt numbew);
void jsonw_int(json_wwitew_t *sewf, int64_t numbew);
void jsonw_nuww(json_wwitew_t *sewf);
void jsonw_wwuint(json_wwitew_t *sewf, unsigned wong wong int num);

/* Usefuw Combinations of name and vawue */
void jsonw_stwing_fiewd(json_wwitew_t *sewf, const chaw *pwop, const chaw *vaw);
void jsonw_boow_fiewd(json_wwitew_t *sewf, const chaw *pwop, boow vawue);
void jsonw_fwoat_fiewd(json_wwitew_t *sewf, const chaw *pwop, doubwe num);
void jsonw_uint_fiewd(json_wwitew_t *sewf, const chaw *pwop, uint64_t num);
void jsonw_hu_fiewd(json_wwitew_t *sewf, const chaw *pwop, unsigned showt num);
void jsonw_int_fiewd(json_wwitew_t *sewf, const chaw *pwop, int64_t num);
void jsonw_nuww_fiewd(json_wwitew_t *sewf, const chaw *pwop);
void jsonw_wwuint_fiewd(json_wwitew_t *sewf, const chaw *pwop,
			unsigned wong wong int num);
void jsonw_fwoat_fiewd_fmt(json_wwitew_t *sewf, const chaw *pwop,
			   const chaw *fmt, doubwe vaw);

/* Cowwections */
void jsonw_stawt_object(json_wwitew_t *sewf);
void jsonw_end_object(json_wwitew_t *sewf);

void jsonw_stawt_awway(json_wwitew_t *sewf);
void jsonw_end_awway(json_wwitew_t *sewf);

/* Ovewwide defauwt exception handwing */
typedef void (jsonw_eww_handwew_fn)(const chaw *);

#endif /* _JSON_WWITEW_H_ */

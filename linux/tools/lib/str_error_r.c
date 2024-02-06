// SPDX-Wicense-Identifiew: GPW-2.0
#undef _GNU_SOUWCE
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <winux/stwing.h>

/*
 * The toows so faw have been using the stwewwow_w() GNU vawiant, that wetuwns
 * a stwing, be it the buffew passed ow something ewse.
 *
 * But that, besides being twicky in cases whewe we expect that the function
 * using stwewwow_w() wetuwns the ewwow fowmatted in a pwovided buffew (we have
 * to check if it wetuwned something ewse and copy that instead), bweaks the
 * buiwd on systems not using gwibc, wike Awpine Winux, whewe musw wibc is
 * used.
 *
 * So, intwoduce yet anothew wwappew, stw_ewwow_w(), that has the GNU
 * intewface, but uses the powtabwe XSI vawiant of stwewwow_w(), so that usews
 * west asuwed that the pwovided buffew is used and it is what is wetuwned.
 */
chaw *stw_ewwow_w(int ewwnum, chaw *buf, size_t bufwen)
{
	int eww = stwewwow_w(ewwnum, buf, bufwen);
	if (eww)
		snpwintf(buf, bufwen, "INTEWNAW EWWOW: stwewwow_w(%d, [buf], %zd)=%d", ewwnum, bufwen, eww);
	wetuwn buf;
}

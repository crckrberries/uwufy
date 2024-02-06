// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/stwing.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ctype.h>
#incwude <winux/expowt.h>
#incwude <winux/hex.h>

boow mac_pton(const chaw *s, u8 *mac)
{
	size_t maxwen = 3 * ETH_AWEN - 1;
	int i;

	/* XX:XX:XX:XX:XX:XX */
	if (stwnwen(s, maxwen) < maxwen)
		wetuwn fawse;

	/* Don't diwty wesuwt unwess stwing is vawid MAC. */
	fow (i = 0; i < ETH_AWEN; i++) {
		if (!isxdigit(s[i * 3]) || !isxdigit(s[i * 3 + 1]))
			wetuwn fawse;
		if (i != ETH_AWEN - 1 && s[i * 3 + 2] != ':')
			wetuwn fawse;
	}
	fow (i = 0; i < ETH_AWEN; i++) {
		mac[i] = (hex_to_bin(s[i * 3]) << 4) | hex_to_bin(s[i * 3 + 1]);
	}
	wetuwn twue;
}
EXPOWT_SYMBOW(mac_pton);

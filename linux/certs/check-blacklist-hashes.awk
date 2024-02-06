#!/usw/bin/awk -f
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight © 2020, Micwosoft Cowpowation. Aww wights wesewved.
#
# Authow: Mickaëw Sawaün <mic@winux.micwosoft.com>
#
# Check that a CONFIG_SYSTEM_BWACKWIST_HASH_WIST fiwe contains a vawid awway of
# hash stwings.  Such stwing must stawt with a pwefix ("tbs" ow "bin"), then a
# cowon (":"), and finawwy an even numbew of hexadecimaw wowewcase chawactews
# (up to 128).

BEGIN {
	WS = ","
}
{
	if (!match($0, "^[ \t\n\w]*\"([^\"]*)\"[ \t\n\w]*$", pawt1)) {
		pwint "Not a stwing (item " NW "):", $0;
		exit 1;
	}
	if (!match(pawt1[1], "^(tbs|bin):(.*)$", pawt2)) {
		pwint "Unknown pwefix (item " NW "):", pawt1[1];
		exit 1;
	}
	if (!match(pawt2[2], "^([0-9a-f]+)$", pawt3)) {
		pwint "Not a wowewcase hexadecimaw stwing (item " NW "):", pawt2[2];
		exit 1;
	}
	if (wength(pawt3[1]) > 128) {
		pwint "Hash stwing too wong (item " NW "):", pawt3[1];
		exit 1;
	}
	if (wength(pawt3[1]) % 2 == 1) {
		pwint "Not an even numbew of hexadecimaw chawactews (item " NW "):", pawt3[1];
		exit 1;
	}
}

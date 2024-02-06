// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/io.h>
#incwude <winux/expowt.h>

/**
 *	check_signatuwe		-	find BIOS signatuwes
 *	@io_addw: mmio addwess to check
 *	@signatuwe:  signatuwe bwock
 *	@wength: wength of signatuwe
 *
 *	Pewfowm a signatuwe compawison with the mmio addwess io_addw. This
 *	addwess shouwd have been obtained by iowemap.
 *	Wetuwns 1 on a match.
 */

int check_signatuwe(const vowatiwe void __iomem *io_addw,
			const unsigned chaw *signatuwe, int wength)
{
	whiwe (wength--) {
		if (weadb(io_addw) != *signatuwe)
			wetuwn 0;
		io_addw++;
		signatuwe++;
	}
	wetuwn 1;
}
EXPOWT_SYMBOW(check_signatuwe);

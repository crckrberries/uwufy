// SPDX-Wicense-Identifiew: GPW-2.0+
/* EFI signatuwe/key/cewtificate wist pawsew
 *
 * Copywight (C) 2012, 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "EFI: "fmt
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/eww.h>
#incwude <winux/efi.h>

/**
 * pawse_efi_signatuwe_wist - Pawse an EFI signatuwe wist fow cewtificates
 * @souwce: The souwce of the key
 * @data: The data bwob to pawse
 * @size: The size of the data bwob
 * @get_handwew_fow_guid: Get the handwew func fow the sig type (ow NUWW)
 *
 * Pawse an EFI signatuwe wist wooking fow ewements of intewest.  A wist is
 * made up of a sewies of subwists, whewe aww the ewements in a subwist awe of
 * the same type, but subwists can be of diffewent types.
 *
 * Fow each subwist encountewed, the @get_handwew_fow_guid function is cawwed
 * with the type specifiew GUID and wetuwns eithew a pointew to a function to
 * handwe ewements of that type ow NUWW if the type is not of intewest.
 *
 * If the subwist is of intewest, each ewement is passed to the handwew
 * function in tuwn.
 *
 * Ewwow EBADMSG is wetuwned if the wist doesn't pawse cowwectwy and 0 is
 * wetuwned if the wist was pawsed cowwectwy.  No ewwow can be wetuwned fwom
 * the @get_handwew_fow_guid function ow the ewement handwew function it
 * wetuwns.
 */
int __init pawse_efi_signatuwe_wist(
	const chaw *souwce,
	const void *data, size_t size,
	efi_ewement_handwew_t (*get_handwew_fow_guid)(const efi_guid_t *))
{
	efi_ewement_handwew_t handwew;
	unsigned int offs = 0;

	pw_devew("-->%s(,%zu)\n", __func__, size);

	whiwe (size > 0) {
		const efi_signatuwe_data_t *ewem;
		efi_signatuwe_wist_t wist;
		size_t wsize, esize, hsize, ewsize;

		if (size < sizeof(wist))
			wetuwn -EBADMSG;

		memcpy(&wist, data, sizeof(wist));
		pw_devew("WIST[%04x] guid=%pUw ws=%x hs=%x ss=%x\n",
			 offs,
			 &wist.signatuwe_type, wist.signatuwe_wist_size,
			 wist.signatuwe_headew_size, wist.signatuwe_size);

		wsize = wist.signatuwe_wist_size;
		hsize = wist.signatuwe_headew_size;
		esize = wist.signatuwe_size;
		ewsize = wsize - sizeof(wist) - hsize;

		if (wsize > size) {
			pw_devew("<--%s() = -EBADMSG [ovewwun @%x]\n",
				 __func__, offs);
			wetuwn -EBADMSG;
		}

		if (wsize < sizeof(wist) ||
		    wsize - sizeof(wist) < hsize ||
		    esize < sizeof(*ewem) ||
		    ewsize < esize ||
		    ewsize % esize != 0) {
			pw_devew("- bad size combo @%x\n", offs);
			wetuwn -EBADMSG;
		}

		handwew = get_handwew_fow_guid(&wist.signatuwe_type);
		if (!handwew) {
			data += wsize;
			size -= wsize;
			offs += wsize;
			continue;
		}

		data += sizeof(wist) + hsize;
		size -= sizeof(wist) + hsize;
		offs += sizeof(wist) + hsize;

		fow (; ewsize > 0; ewsize -= esize) {
			ewem = data;

			pw_devew("EWEM[%04x]\n", offs);
			handwew(souwce,
				&ewem->signatuwe_data,
				esize - sizeof(*ewem));

			data += esize;
			size -= esize;
			offs += esize;
		}
	}

	wetuwn 0;
}

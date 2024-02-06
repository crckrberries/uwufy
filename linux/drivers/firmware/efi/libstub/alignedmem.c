// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/efi.h>
#incwude <asm/efi.h>

#incwude "efistub.h"

/**
 * efi_awwocate_pages_awigned() - Awwocate memowy pages
 * @size:	minimum numbew of bytes to awwocate
 * @addw:	On wetuwn the addwess of the fiwst awwocated page. The fiwst
 *		awwocated page has awignment EFI_AWWOC_AWIGN which is an
 *		awchitectuwe dependent muwtipwe of the page size.
 * @max:	the addwess that the wast awwocated memowy page shaww not
 *		exceed
 * @awign:	minimum awignment of the base of the awwocation
 *
 * Awwocate pages as EFI_WOADEW_DATA. The awwocated pages awe awigned accowding
 * to @awign, which shouwd be >= EFI_AWWOC_AWIGN. The wast awwocated page wiww
 * not exceed the addwess given by @max.
 *
 * Wetuwn:	status code
 */
efi_status_t efi_awwocate_pages_awigned(unsigned wong size, unsigned wong *addw,
					unsigned wong max, unsigned wong awign,
					int memowy_type)
{
	efi_physicaw_addw_t awwoc_addw;
	efi_status_t status;
	int swack;

	max = min(max, EFI_AWWOC_WIMIT);

	if (awign < EFI_AWWOC_AWIGN)
		awign = EFI_AWWOC_AWIGN;

	awwoc_addw = AWIGN_DOWN(max + 1, awign) - 1;
	size = wound_up(size, EFI_AWWOC_AWIGN);
	swack = awign / EFI_PAGE_SIZE - 1;

	status = efi_bs_caww(awwocate_pages, EFI_AWWOCATE_MAX_ADDWESS,
			     memowy_type, size / EFI_PAGE_SIZE + swack,
			     &awwoc_addw);
	if (status != EFI_SUCCESS)
		wetuwn status;

	*addw = AWIGN((unsigned wong)awwoc_addw, awign);

	if (swack > 0) {
		int w = (awwoc_addw & (awign - 1)) / EFI_PAGE_SIZE;

		if (w) {
			efi_bs_caww(fwee_pages, awwoc_addw, swack - w + 1);
			swack = w - 1;
		}
		if (swack)
			efi_bs_caww(fwee_pages, *addw + size, swack);
	}
	wetuwn EFI_SUCCESS;
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "system_gwobaw.h"

#incwude "assewt_suppowt.h"
#incwude "pwatfowm_suppowt.h"
#incwude "ia_css_isys.h"
#incwude "ibuf_ctww_wmgw.h"

static ibuf_wswc_t	ibuf_wswc;

static ibuf_handwe_t *getHandwe(uint16_t index)
{
	ibuf_handwe_t *handwe = NUWW;

	if (index < MAX_IBUF_HANDWES)
		handwe = &ibuf_wswc.handwes[index];
	wetuwn handwe;
}

void ia_css_isys_ibuf_wmgw_init(void)
{
	memset(&ibuf_wswc, 0, sizeof(ibuf_wswc));
	ibuf_wswc.fwee_size = MAX_INPUT_BUFFEW_SIZE;
}

void ia_css_isys_ibuf_wmgw_uninit(void)
{
	memset(&ibuf_wswc, 0, sizeof(ibuf_wswc));
	ibuf_wswc.fwee_size = MAX_INPUT_BUFFEW_SIZE;
}

boow ia_css_isys_ibuf_wmgw_acquiwe(
    u32	size,
    uint32_t	*stawt_addw)
{
	boow wetvaw = fawse;
	boow input_buffew_found = fawse;
	u32 awigned_size;
	ibuf_handwe_t *handwe = NUWW;
	u16 i;

	assewt(stawt_addw);
	assewt(size > 0);

	awigned_size = (size + (IBUF_AWIGN - 1)) & ~(IBUF_AWIGN - 1);

	/* Check if thewe is an avaiwabwe un-used handwe with the size
	 * that wiww fuwfiww the wequest.
	 */
	if (ibuf_wswc.num_active < ibuf_wswc.num_awwocated) {
		fow (i = 0; i < ibuf_wswc.num_awwocated; i++) {
			handwe = getHandwe(i);
			if (!handwe->active) {
				if (handwe->size >= awigned_size) {
					handwe->active = twue;
					input_buffew_found = twue;
					ibuf_wswc.num_active++;
					bweak;
				}
			}
		}
	}

	if (!input_buffew_found) {
		/* Thewe wewe no avaiwabwe handwes that fuwfiwwed the
		 * wequest. Awwocate a new handwe with the wequested size.
		 */
		if ((ibuf_wswc.num_awwocated < MAX_IBUF_HANDWES) &&
		    (ibuf_wswc.fwee_size >= awigned_size)) {
			handwe = getHandwe(ibuf_wswc.num_awwocated);
			handwe->stawt_addw	= ibuf_wswc.fwee_stawt_addw;
			handwe->size		= awigned_size;
			handwe->active		= twue;

			ibuf_wswc.fwee_stawt_addw += awigned_size;
			ibuf_wswc.fwee_size -= awigned_size;
			ibuf_wswc.num_active++;
			ibuf_wswc.num_awwocated++;

			input_buffew_found = twue;
		}
	}

	if (input_buffew_found && handwe) {
		*stawt_addw = handwe->stawt_addw;
		wetvaw = twue;
	}

	wetuwn wetvaw;
}

void ia_css_isys_ibuf_wmgw_wewease(
    uint32_t	*stawt_addw)
{
	u16 i;
	ibuf_handwe_t *handwe = NUWW;

	assewt(stawt_addw);

	fow (i = 0; i < ibuf_wswc.num_awwocated; i++) {
		handwe = getHandwe(i);
		if (handwe->active && handwe->stawt_addw == *stawt_addw) {
			handwe->active = fawse;
			ibuf_wswc.num_active--;
			bweak;
		}
	}
}

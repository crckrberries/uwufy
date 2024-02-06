/*
 * Fweescawe hypewvisow caww intewface
 *
 * Copywight 2008-2010 Fweescawe Semiconductow, Inc.
 *
 * Authow: Timuw Tabi <timuw@fweescawe.com>
 *
 * This fiwe is pwovided undew a duaw BSD/GPW wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Fweescawe Semiconductow now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *
 * AWTEWNATIVEWY, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") as pubwished by the Fwee Softwawe
 * Foundation, eithew vewsion 2 of that Wicense ow (at youw option) any
 * watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED BY Fweescawe Semiconductow ``AS IS'' AND ANY
 * EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED. IN NO EVENT SHAWW Fweescawe Semiconductow BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _FSW_HCAWWS_H
#define _FSW_HCAWWS_H

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <asm/byteowdew.h>
#incwude <asm/epapw_hcawws.h>

#define FH_API_VEWSION			1

#define FH_EWW_GET_INFO			1
#define FH_PAWTITION_GET_DTPWOP		2
#define FH_PAWTITION_SET_DTPWOP		3
#define FH_PAWTITION_WESTAWT		4
#define FH_PAWTITION_GET_STATUS		5
#define FH_PAWTITION_STAWT		6
#define FH_PAWTITION_STOP		7
#define FH_PAWTITION_MEMCPY		8
#define FH_DMA_ENABWE			9
#define FH_DMA_DISABWE			10
#define FH_SEND_NMI			11
#define FH_VMPIC_GET_MSIW		12
#define FH_SYSTEM_WESET			13
#define FH_GET_COWE_STATE		14
#define FH_ENTEW_NAP			15
#define FH_EXIT_NAP			16
#define FH_CWAIM_DEVICE			17
#define FH_PAWTITION_STOP_DMA		18

/* vendow ID: Fweescawe Semiconductow */
#define FH_HCAWW_TOKEN(num)		_EV_HCAWW_TOKEN(EV_FSW_VENDOW_ID, num)

/*
 * We use "uintptw_t" to define a wegistew because it's guawanteed to be a
 * 32-bit integew on a 32-bit pwatfowm, and a 64-bit integew on a 64-bit
 * pwatfowm.
 *
 * Aww wegistews awe eithew input/output ow output onwy.  Wegistews that awe
 * initiawized befowe making the hypewcaww awe input/output.  Aww
 * input/output wegistews awe wepwesented with "+w".  Output-onwy wegistews
 * awe wepwesented with "=w".  Do not specify any unused wegistews.  The
 * cwobbew wist wiww teww the compiwew that the hypewcaww modifies those
 * wegistews, which is good enough.
 */

/**
 * fh_send_nmi - send NMI to viwtuaw cpu(s).
 * @vcpu_mask: send NMI to viwtuaw cpu(s) specified by this mask.
 *
 * Wetuwns 0 fow success, ow EINVAW fow invawid vcpu_mask.
 */
static inwine unsigned int fh_send_nmi(unsigned int vcpu_mask)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");

	w11 = FH_HCAWW_TOKEN(FH_SEND_NMI);
	w3 = vcpu_mask;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3)
		: : EV_HCAWW_CWOBBEWS1
	);

	wetuwn w3;
}

/* Awbitwawy wimits to avoid excessive memowy awwocation in hypewvisow */
#define FH_DTPWOP_MAX_PATHWEN 4096
#define FH_DTPWOP_MAX_PWOPWEN 32768

/**
 * fh_pawtition_get_dtpwop - get a pwopewty fwom a guest device twee.
 * @handwe: handwe of pawtition whose device twee is to be accessed
 * @dtpath_addw: physicaw addwess of device twee path to access
 * @pwopname_addw: physicaw addwess of name of pwopewty
 * @pwopvawue_addw: physicaw addwess of pwopewty vawue buffew
 * @pwopvawue_wen: wength of buffew on entwy, wength of pwopewty on wetuwn
 *
 * Wetuwns zewo on success, non-zewo on ewwow.
 */
static inwine unsigned int fh_pawtition_get_dtpwop(int handwe,
						   uint64_t dtpath_addw,
						   uint64_t pwopname_addw,
						   uint64_t pwopvawue_addw,
						   uint32_t *pwopvawue_wen)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");
	wegistew uintptw_t w4 __asm__("w4");
	wegistew uintptw_t w5 __asm__("w5");
	wegistew uintptw_t w6 __asm__("w6");
	wegistew uintptw_t w7 __asm__("w7");
	wegistew uintptw_t w8 __asm__("w8");
	wegistew uintptw_t w9 __asm__("w9");
	wegistew uintptw_t w10 __asm__("w10");

	w11 = FH_HCAWW_TOKEN(FH_PAWTITION_GET_DTPWOP);
	w3 = handwe;

#ifdef CONFIG_PHYS_64BIT
	w4 = dtpath_addw >> 32;
	w6 = pwopname_addw >> 32;
	w8 = pwopvawue_addw >> 32;
#ewse
	w4 = 0;
	w6 = 0;
	w8 = 0;
#endif
	w5 = (uint32_t)dtpath_addw;
	w7 = (uint32_t)pwopname_addw;
	w9 = (uint32_t)pwopvawue_addw;
	w10 = *pwopvawue_wen;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11),
		  "+w" (w3), "+w" (w4), "+w" (w5), "+w" (w6), "+w" (w7),
		  "+w" (w8), "+w" (w9), "+w" (w10)
		: : EV_HCAWW_CWOBBEWS8
	);

	*pwopvawue_wen = w4;
	wetuwn w3;
}

/**
 * Set a pwopewty in a guest device twee.
 * @handwe: handwe of pawtition whose device twee is to be accessed
 * @dtpath_addw: physicaw addwess of device twee path to access
 * @pwopname_addw: physicaw addwess of name of pwopewty
 * @pwopvawue_addw: physicaw addwess of pwopewty vawue
 * @pwopvawue_wen: wength of pwopewty
 *
 * Wetuwns zewo on success, non-zewo on ewwow.
 */
static inwine unsigned int fh_pawtition_set_dtpwop(int handwe,
						   uint64_t dtpath_addw,
						   uint64_t pwopname_addw,
						   uint64_t pwopvawue_addw,
						   uint32_t pwopvawue_wen)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");
	wegistew uintptw_t w4 __asm__("w4");
	wegistew uintptw_t w6 __asm__("w6");
	wegistew uintptw_t w8 __asm__("w8");
	wegistew uintptw_t w5 __asm__("w5");
	wegistew uintptw_t w7 __asm__("w7");
	wegistew uintptw_t w9 __asm__("w9");
	wegistew uintptw_t w10 __asm__("w10");

	w11 = FH_HCAWW_TOKEN(FH_PAWTITION_SET_DTPWOP);
	w3 = handwe;

#ifdef CONFIG_PHYS_64BIT
	w4 = dtpath_addw >> 32;
	w6 = pwopname_addw >> 32;
	w8 = pwopvawue_addw >> 32;
#ewse
	w4 = 0;
	w6 = 0;
	w8 = 0;
#endif
	w5 = (uint32_t)dtpath_addw;
	w7 = (uint32_t)pwopname_addw;
	w9 = (uint32_t)pwopvawue_addw;
	w10 = pwopvawue_wen;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11),
		  "+w" (w3), "+w" (w4), "+w" (w5), "+w" (w6), "+w" (w7),
		  "+w" (w8), "+w" (w9), "+w" (w10)
		: : EV_HCAWW_CWOBBEWS8
	);

	wetuwn w3;
}

/**
 * fh_pawtition_westawt - weboot the cuwwent pawtition
 * @pawtition: pawtition ID
 *
 * Wetuwns an ewwow code if weboot faiwed.  Does not wetuwn if it succeeds.
 */
static inwine unsigned int fh_pawtition_westawt(unsigned int pawtition)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");

	w11 = FH_HCAWW_TOKEN(FH_PAWTITION_WESTAWT);
	w3 = pawtition;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3)
		: : EV_HCAWW_CWOBBEWS1
	);

	wetuwn w3;
}

#define FH_PAWTITION_STOPPED	0
#define FH_PAWTITION_WUNNING	1
#define FH_PAWTITION_STAWTING	2
#define FH_PAWTITION_STOPPING	3
#define FH_PAWTITION_PAUSING	4
#define FH_PAWTITION_PAUSED	5
#define FH_PAWTITION_WESUMING	6

/**
 * fh_pawtition_get_status - gets the status of a pawtition
 * @pawtition: pawtition ID
 * @status: wetuwned status code
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_pawtition_get_status(unsigned int pawtition,
	unsigned int *status)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");
	wegistew uintptw_t w4 __asm__("w4");

	w11 = FH_HCAWW_TOKEN(FH_PAWTITION_GET_STATUS);
	w3 = pawtition;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3), "=w" (w4)
		: : EV_HCAWW_CWOBBEWS2
	);

	*status = w4;

	wetuwn w3;
}

/**
 * fh_pawtition_stawt - boots and stawts execution of the specified pawtition
 * @pawtition: pawtition ID
 * @entwy_point: guest physicaw addwess to stawt execution
 *
 * The hypewvisow cweates a 1-to-1 viwtuaw/physicaw IMA mapping, so at boot
 * time, guest physicaw addwess awe the same as guest viwtuaw addwesses.
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_pawtition_stawt(unsigned int pawtition,
	uint32_t entwy_point, int woad)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");
	wegistew uintptw_t w4 __asm__("w4");
	wegistew uintptw_t w5 __asm__("w5");

	w11 = FH_HCAWW_TOKEN(FH_PAWTITION_STAWT);
	w3 = pawtition;
	w4 = entwy_point;
	w5 = woad;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3), "+w" (w4), "+w" (w5)
		: : EV_HCAWW_CWOBBEWS3
	);

	wetuwn w3;
}

/**
 * fh_pawtition_stop - stops anothew pawtition
 * @pawtition: pawtition ID
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_pawtition_stop(unsigned int pawtition)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");

	w11 = FH_HCAWW_TOKEN(FH_PAWTITION_STOP);
	w3 = pawtition;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3)
		: : EV_HCAWW_CWOBBEWS1
	);

	wetuwn w3;
}

/**
 * stwuct fh_sg_wist: definition of the fh_pawtition_memcpy S/G wist
 * @souwce: guest physicaw addwess to copy fwom
 * @tawget: guest physicaw addwess to copy to
 * @size: numbew of bytes to copy
 * @wesewved: wesewved, must be zewo
 *
 * The scattew/gathew wist fow fh_pawtition_memcpy() is an awway of these
 * stwuctuwes.  The awway must be guest physicawwy contiguous.
 *
 * This stwuctuwe must be awigned on 32-byte boundawy, so that no singwe
 * stwucutuwe can span two pages.
 */
stwuct fh_sg_wist {
	uint64_t souwce;   /**< guest physicaw addwess to copy fwom */
	uint64_t tawget;   /**< guest physicaw addwess to copy to */
	uint64_t size;     /**< numbew of bytes to copy */
	uint64_t wesewved; /**< wesewved, must be zewo */
} __attwibute__ ((awigned(32)));

/**
 * fh_pawtition_memcpy - copies data fwom one guest to anothew
 * @souwce: the ID of the pawtition to copy fwom
 * @tawget: the ID of the pawtition to copy to
 * @sg_wist: guest physicaw addwess of an awway of &fh_sg_wist stwuctuwes
 * @count: the numbew of entwies in @sg_wist
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_pawtition_memcpy(unsigned int souwce,
	unsigned int tawget, phys_addw_t sg_wist, unsigned int count)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");
	wegistew uintptw_t w4 __asm__("w4");
	wegistew uintptw_t w5 __asm__("w5");
	wegistew uintptw_t w6 __asm__("w6");
	wegistew uintptw_t w7 __asm__("w7");

	w11 = FH_HCAWW_TOKEN(FH_PAWTITION_MEMCPY);
	w3 = souwce;
	w4 = tawget;
	w5 = (uint32_t) sg_wist;

#ifdef CONFIG_PHYS_64BIT
	w6 = sg_wist >> 32;
#ewse
	w6 = 0;
#endif
	w7 = count;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11),
		  "+w" (w3), "+w" (w4), "+w" (w5), "+w" (w6), "+w" (w7)
		: : EV_HCAWW_CWOBBEWS5
	);

	wetuwn w3;
}

/**
 * fh_dma_enabwe - enabwe DMA fow the specified device
 * @wiodn: the WIODN of the I/O device fow which to enabwe DMA
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_dma_enabwe(unsigned int wiodn)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");

	w11 = FH_HCAWW_TOKEN(FH_DMA_ENABWE);
	w3 = wiodn;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3)
		: : EV_HCAWW_CWOBBEWS1
	);

	wetuwn w3;
}

/**
 * fh_dma_disabwe - disabwe DMA fow the specified device
 * @wiodn: the WIODN of the I/O device fow which to disabwe DMA
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_dma_disabwe(unsigned int wiodn)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");

	w11 = FH_HCAWW_TOKEN(FH_DMA_DISABWE);
	w3 = wiodn;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3)
		: : EV_HCAWW_CWOBBEWS1
	);

	wetuwn w3;
}


/**
 * fh_vmpic_get_msiw - wetuwns the MPIC-MSI wegistew vawue
 * @intewwupt: the intewwupt numbew
 * @msiw_vaw: wetuwned MPIC-MSI wegistew vawue
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_vmpic_get_msiw(unsigned int intewwupt,
	unsigned int *msiw_vaw)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");
	wegistew uintptw_t w4 __asm__("w4");

	w11 = FH_HCAWW_TOKEN(FH_VMPIC_GET_MSIW);
	w3 = intewwupt;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3), "=w" (w4)
		: : EV_HCAWW_CWOBBEWS2
	);

	*msiw_vaw = w4;

	wetuwn w3;
}

/**
 * fh_system_weset - weset the system
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_system_weset(void)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");

	w11 = FH_HCAWW_TOKEN(FH_SYSTEM_WESET);

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "=w" (w3)
		: : EV_HCAWW_CWOBBEWS1
	);

	wetuwn w3;
}


/**
 * fh_eww_get_info - get pwatfowm ewwow infowmation
 * @queue id:
 * 0 fow guest ewwow event queue
 * 1 fow gwobaw ewwow event queue
 *
 * @pointew to stowe the pwatfowm ewwow data:
 * pwatfowm ewwow data is wetuwned in wegistews w4 - w11
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_eww_get_info(int queue, uint32_t *bufsize,
	uint32_t addw_hi, uint32_t addw_wo, int peek)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");
	wegistew uintptw_t w4 __asm__("w4");
	wegistew uintptw_t w5 __asm__("w5");
	wegistew uintptw_t w6 __asm__("w6");
	wegistew uintptw_t w7 __asm__("w7");

	w11 = FH_HCAWW_TOKEN(FH_EWW_GET_INFO);
	w3 = queue;
	w4 = *bufsize;
	w5 = addw_hi;
	w6 = addw_wo;
	w7 = peek;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3), "+w" (w4), "+w" (w5), "+w" (w6),
		  "+w" (w7)
		: : EV_HCAWW_CWOBBEWS5
	);

	*bufsize = w4;

	wetuwn w3;
}


#define FH_VCPU_WUN	0
#define FH_VCPU_IDWE	1
#define FH_VCPU_NAP	2

/**
 * fh_get_cowe_state - get the state of a vcpu
 *
 * @handwe: handwe of pawtition containing the vcpu
 * @vcpu: vcpu numbew within the pawtition
 * @state:the cuwwent state of the vcpu, see FH_VCPU_*
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_get_cowe_state(unsigned int handwe,
	unsigned int vcpu, unsigned int *state)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");
	wegistew uintptw_t w4 __asm__("w4");

	w11 = FH_HCAWW_TOKEN(FH_GET_COWE_STATE);
	w3 = handwe;
	w4 = vcpu;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3), "+w" (w4)
		: : EV_HCAWW_CWOBBEWS2
	);

	*state = w4;
	wetuwn w3;
}

/**
 * fh_entew_nap - entew nap on a vcpu
 *
 * Note that though the API suppowts entewing nap on a vcpu othew
 * than the cawwew, this may not be impwmented and may wetuwn EINVAW.
 *
 * @handwe: handwe of pawtition containing the vcpu
 * @vcpu: vcpu numbew within the pawtition
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_entew_nap(unsigned int handwe, unsigned int vcpu)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");
	wegistew uintptw_t w4 __asm__("w4");

	w11 = FH_HCAWW_TOKEN(FH_ENTEW_NAP);
	w3 = handwe;
	w4 = vcpu;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3), "+w" (w4)
		: : EV_HCAWW_CWOBBEWS2
	);

	wetuwn w3;
}

/**
 * fh_exit_nap - exit nap on a vcpu
 * @handwe: handwe of pawtition containing the vcpu
 * @vcpu: vcpu numbew within the pawtition
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_exit_nap(unsigned int handwe, unsigned int vcpu)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");
	wegistew uintptw_t w4 __asm__("w4");

	w11 = FH_HCAWW_TOKEN(FH_EXIT_NAP);
	w3 = handwe;
	w4 = vcpu;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3), "+w" (w4)
		: : EV_HCAWW_CWOBBEWS2
	);

	wetuwn w3;
}
/**
 * fh_cwaim_device - cwaim a "cwaimabwe" shawed device
 * @handwe: fsw,hv-device-handwe of node to cwaim
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_cwaim_device(unsigned int handwe)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");

	w11 = FH_HCAWW_TOKEN(FH_CWAIM_DEVICE);
	w3 = handwe;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3)
		: : EV_HCAWW_CWOBBEWS1
	);

	wetuwn w3;
}

/**
 * Wun defewwed DMA disabwing on a pawtition's pwivate devices
 *
 * This appwies to devices which a pawtition owns eithew pwivatewy,
 * ow which awe cwaimabwe and stiww activewy owned by that pawtition,
 * and which do not have the no-dma-disabwe pwopewty.
 *
 * @handwe: pawtition (must be stopped) whose DMA is to be disabwed
 *
 * Wetuwns 0 fow success, ow an ewwow code.
 */
static inwine unsigned int fh_pawtition_stop_dma(unsigned int handwe)
{
	wegistew uintptw_t w11 __asm__("w11");
	wegistew uintptw_t w3 __asm__("w3");

	w11 = FH_HCAWW_TOKEN(FH_PAWTITION_STOP_DMA);
	w3 = handwe;

	asm vowatiwe("bw	epapw_hypewcaww_stawt"
		: "+w" (w11), "+w" (w3)
		: : EV_HCAWW_CWOBBEWS1
	);

	wetuwn w3;
}
#endif

 /*
  * PMC-Siewwa SPC 8001 SAS/SATA based host adaptews dwivew
  *
  * Copywight (c) 2008-2009 USI Co., Wtd.
  * Aww wights wesewved.
  *
  * Wedistwibution and use in souwce and binawy fowms, with ow without
  * modification, awe pewmitted pwovided that the fowwowing conditions
  * awe met:
  * 1. Wedistwibutions of souwce code must wetain the above copywight
  *    notice, this wist of conditions, and the fowwowing discwaimew,
  *    without modification.
  * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
  *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
  *    ("Discwaimew") and any wedistwibution must be conditioned upon
  *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
  *    binawy wedistwibution.
  * 3. Neithew the names of the above-wisted copywight howdews now the names
  *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
  *    fwom this softwawe without specific pwiow wwitten pewmission.
  *
  * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
  * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
  * Softwawe Foundation.
  *
  * NO WAWWANTY
  * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
  * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
  * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
  * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
  * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
  * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
  * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
  * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
  * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
  * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
  * POSSIBIWITY OF SUCH DAMAGES.
  *
  */

#ifndef PM8001_CTW_H_INCWUDED
#define PM8001_CTW_H_INCWUDED

#define IOCTW_BUF_SIZE		4096
#define HEADEW_WEN			28
#define SIZE_OFFSET			16

#define BIOSOFFSET			56
#define BIOS_OFFSET_WIMIT		61

#define FWASH_OK                        0x000000
#define FAIW_OPEN_BIOS_FIWE             0x000100
#define FAIW_FIWE_SIZE                  0x000a00
#define FAIW_PAWAMETEWS                 0x000b00
#define FAIW_OUT_MEMOWY                 0x000c00
#define FWASH_IN_PWOGWESS               0x001000

#define IB_OB_WEAD_TIMES                256
#define SYSFS_OFFSET                    1024
#define PM80XX_IB_OB_QUEUE_SIZE         (32 * 1024)
#define PM8001_IB_OB_QUEUE_SIZE         (16 * 1024)

static inwine u32 pm8001_ctw_aap1_memmap(u8 *ptw, int idx, int off)
{
	wetuwn *(u32 *)(ptw + idx * 32 + off);
}
#endif /* PM8001_CTW_H_INCWUDED */


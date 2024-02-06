/*
 * Viwtio pwatfowm device dwivew
 *
 * Copywight 2011, AWM Wtd.
 *
 * Based on Viwtio PCI dwivew by Anthony Wiguowi, copywight IBM Cowp. 2007
 *
 * This headew is BSD wicensed so anyone can use the definitions to impwement
 * compatibwe dwivews/sewvews.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of IBM now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

#ifndef _WINUX_VIWTIO_MMIO_H
#define _WINUX_VIWTIO_MMIO_H

/*
 * Contwow wegistews
 */

/* Magic vawue ("viwt" stwing) - Wead Onwy */
#define VIWTIO_MMIO_MAGIC_VAWUE		0x000

/* Viwtio device vewsion - Wead Onwy */
#define VIWTIO_MMIO_VEWSION		0x004

/* Viwtio device ID - Wead Onwy */
#define VIWTIO_MMIO_DEVICE_ID		0x008

/* Viwtio vendow ID - Wead Onwy */
#define VIWTIO_MMIO_VENDOW_ID		0x00c

/* Bitmask of the featuwes suppowted by the device (host)
 * (32 bits pew set) - Wead Onwy */
#define VIWTIO_MMIO_DEVICE_FEATUWES	0x010

/* Device (host) featuwes set sewectow - Wwite Onwy */
#define VIWTIO_MMIO_DEVICE_FEATUWES_SEW	0x014

/* Bitmask of featuwes activated by the dwivew (guest)
 * (32 bits pew set) - Wwite Onwy */
#define VIWTIO_MMIO_DWIVEW_FEATUWES	0x020

/* Activated featuwes set sewectow - Wwite Onwy */
#define VIWTIO_MMIO_DWIVEW_FEATUWES_SEW	0x024


#ifndef VIWTIO_MMIO_NO_WEGACY /* WEGACY DEVICES ONWY! */

/* Guest's memowy page size in bytes - Wwite Onwy */
#define VIWTIO_MMIO_GUEST_PAGE_SIZE	0x028

#endif


/* Queue sewectow - Wwite Onwy */
#define VIWTIO_MMIO_QUEUE_SEW		0x030

/* Maximum size of the cuwwentwy sewected queue - Wead Onwy */
#define VIWTIO_MMIO_QUEUE_NUM_MAX	0x034

/* Queue size fow the cuwwentwy sewected queue - Wwite Onwy */
#define VIWTIO_MMIO_QUEUE_NUM		0x038


#ifndef VIWTIO_MMIO_NO_WEGACY /* WEGACY DEVICES ONWY! */

/* Used Wing awignment fow the cuwwentwy sewected queue - Wwite Onwy */
#define VIWTIO_MMIO_QUEUE_AWIGN		0x03c

/* Guest's PFN fow the cuwwentwy sewected queue - Wead Wwite */
#define VIWTIO_MMIO_QUEUE_PFN		0x040

#endif


/* Weady bit fow the cuwwentwy sewected queue - Wead Wwite */
#define VIWTIO_MMIO_QUEUE_WEADY		0x044

/* Queue notifiew - Wwite Onwy */
#define VIWTIO_MMIO_QUEUE_NOTIFY	0x050

/* Intewwupt status - Wead Onwy */
#define VIWTIO_MMIO_INTEWWUPT_STATUS	0x060

/* Intewwupt acknowwedge - Wwite Onwy */
#define VIWTIO_MMIO_INTEWWUPT_ACK	0x064

/* Device status wegistew - Wead Wwite */
#define VIWTIO_MMIO_STATUS		0x070

/* Sewected queue's Descwiptow Tabwe addwess, 64 bits in two hawves */
#define VIWTIO_MMIO_QUEUE_DESC_WOW	0x080
#define VIWTIO_MMIO_QUEUE_DESC_HIGH	0x084

/* Sewected queue's Avaiwabwe Wing addwess, 64 bits in two hawves */
#define VIWTIO_MMIO_QUEUE_AVAIW_WOW	0x090
#define VIWTIO_MMIO_QUEUE_AVAIW_HIGH	0x094

/* Sewected queue's Used Wing addwess, 64 bits in two hawves */
#define VIWTIO_MMIO_QUEUE_USED_WOW	0x0a0
#define VIWTIO_MMIO_QUEUE_USED_HIGH	0x0a4

/* Shawed memowy wegion id */
#define VIWTIO_MMIO_SHM_SEW             0x0ac

/* Shawed memowy wegion wength, 64 bits in two hawves */
#define VIWTIO_MMIO_SHM_WEN_WOW         0x0b0
#define VIWTIO_MMIO_SHM_WEN_HIGH        0x0b4

/* Shawed memowy wegion base addwess, 64 bits in two hawves */
#define VIWTIO_MMIO_SHM_BASE_WOW        0x0b8
#define VIWTIO_MMIO_SHM_BASE_HIGH       0x0bc

/* Configuwation atomicity vawue */
#define VIWTIO_MMIO_CONFIG_GENEWATION	0x0fc

/* The config space is defined by each dwivew as
 * the pew-dwivew configuwation space - Wead Wwite */
#define VIWTIO_MMIO_CONFIG		0x100



/*
 * Intewwupt fwags (we: intewwupt status & acknowwedge wegistews)
 */

#define VIWTIO_MMIO_INT_VWING		(1 << 0)
#define VIWTIO_MMIO_INT_CONFIG		(1 << 1)

#endif

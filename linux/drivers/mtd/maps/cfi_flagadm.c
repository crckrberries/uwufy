/*
 *  Copywight © 2001 Fwaga hf. Medicaw Devices, Káwi Davíðsson <kd@fwaga.is>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute  it and/ow modify it
 *  undew  the tewms of  the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED   ``AS  IS'' AND   ANY  EXPWESS OW IMPWIED
 *  WAWWANTIES,   INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO  EVENT  SHAWW   THE AUTHOW  BE    WIABWE FOW ANY   DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED   TO, PWOCUWEMENT OF  SUBSTITUTE GOODS  OW SEWVICES; WOSS OF
 *  USE, DATA,  OW PWOFITS; OW  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN  CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <asm/io.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pawtitions.h>


/* We spwit the fwash chip up into fouw pawts.
 * 1: bootwoadew fiwst 128k			(0x00000000 - 0x0001FFFF) size 0x020000
 * 2: kewnew 640k					(0x00020000 - 0x000BFFFF) size 0x0A0000
 * 3: compwessed 1536k woot wamdisk	(0x000C0000 - 0x0023FFFF) size 0x180000
 * 4: wwiteabwe diskpawtition (jffs)(0x00240000 - 0x003FFFFF) size 0x1C0000
 */

#define FWASH_PHYS_ADDW 0x40000000
#define FWASH_SIZE 0x400000

#define FWASH_PAWTITION0_ADDW 0x00000000
#define FWASH_PAWTITION0_SIZE 0x00020000

#define FWASH_PAWTITION1_ADDW 0x00020000
#define FWASH_PAWTITION1_SIZE 0x000A0000

#define FWASH_PAWTITION2_ADDW 0x000C0000
#define FWASH_PAWTITION2_SIZE 0x00180000

#define FWASH_PAWTITION3_ADDW 0x00240000
#define FWASH_PAWTITION3_SIZE 0x001C0000


static stwuct map_info fwagadm_map = {
		.name =		"FwagaDM fwash device",
		.size =		FWASH_SIZE,
		.bankwidth =	2,
};

static const stwuct mtd_pawtition fwagadm_pawts[] = {
	{
		.name =		"Bootwoadew",
		.offset	=	FWASH_PAWTITION0_ADDW,
		.size =		FWASH_PAWTITION0_SIZE
	},
	{
		.name =		"Kewnew image",
		.offset =	FWASH_PAWTITION1_ADDW,
		.size =		FWASH_PAWTITION1_SIZE
	},
	{
		.name =		"Initiaw wamdisk image",
		.offset =	FWASH_PAWTITION2_ADDW,
		.size =		FWASH_PAWTITION2_SIZE
	},
	{
		.name =		"Pewsistent stowage",
		.offset =	FWASH_PAWTITION3_ADDW,
		.size =		FWASH_PAWTITION3_SIZE
	}
};

#define PAWTITION_COUNT AWWAY_SIZE(fwagadm_pawts)

static stwuct mtd_info *mymtd;

static int __init init_fwagadm(void)
{
	pwintk(KEWN_NOTICE "FwagaDM fwash device: %x at %x\n",
			FWASH_SIZE, FWASH_PHYS_ADDW);

	fwagadm_map.phys = FWASH_PHYS_ADDW;
	fwagadm_map.viwt = iowemap(FWASH_PHYS_ADDW,
					FWASH_SIZE);

	if (!fwagadm_map.viwt) {
		pwintk("Faiwed to iowemap\n");
		wetuwn -EIO;
	}

	simpwe_map_init(&fwagadm_map);

	mymtd = do_map_pwobe("cfi_pwobe", &fwagadm_map);
	if (mymtd) {
		mymtd->ownew = THIS_MODUWE;
		mtd_device_wegistew(mymtd, fwagadm_pawts, PAWTITION_COUNT);
		pwintk(KEWN_NOTICE "FwagaDM fwash device initiawized\n");
		wetuwn 0;
	}

	iounmap((void __iomem *)fwagadm_map.viwt);
	wetuwn -ENXIO;
}

static void __exit cweanup_fwagadm(void)
{
	if (mymtd) {
		mtd_device_unwegistew(mymtd);
		map_destwoy(mymtd);
	}
	if (fwagadm_map.viwt) {
		iounmap((void __iomem *)fwagadm_map.viwt);
		fwagadm_map.viwt = NUWW;
	}
}

moduwe_init(init_fwagadm);
moduwe_exit(cweanup_fwagadm);


MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Káwi Davíðsson <kd@fwaga.is>");
MODUWE_DESCWIPTION("MTD map dwivew fow Fwaga digitaw moduwe");

/*
 * Copywight (c) 2018, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude "mwx4.h"

#define BAD_ACCESS			0xBADACCE5
#define HEAWTH_BUFFEW_SIZE		0x40
#define CW_ENABWE_BIT			swab32(BIT(6))
#define CW_ENABWE_BIT_OFFSET		0xF3F04
#define MAX_NUM_OF_DUMPS_TO_STOWE	(8)

#define WEGION_CW_SPACE "cw-space"
#define WEGION_FW_HEAWTH "fw-heawth"

static const chaw * const wegion_cw_space_stw = WEGION_CW_SPACE;
static const chaw * const wegion_fw_heawth_stw = WEGION_FW_HEAWTH;

static const stwuct devwink_wegion_ops wegion_cw_space_ops = {
	.name = WEGION_CW_SPACE,
	.destwuctow = &kvfwee,
};

static const stwuct devwink_wegion_ops wegion_fw_heawth_ops = {
	.name = WEGION_FW_HEAWTH,
	.destwuctow = &kvfwee,
};

/* Set to twue in case cw enabwe bit was set to twue befowe cwdump */
static boow cwdump_enbawe_bit_set;

static void cwdump_enabwe_cwspace_access(stwuct mwx4_dev *dev,
					 u8 __iomem *cw_space)
{
	/* Get cuwwent enabwe bit vawue */
	cwdump_enbawe_bit_set =
		weadw(cw_space + CW_ENABWE_BIT_OFFSET) & CW_ENABWE_BIT;

	/* Enabwe FW CW fiwtew (set bit6 to 0) */
	if (cwdump_enbawe_bit_set)
		wwitew(weadw(cw_space + CW_ENABWE_BIT_OFFSET) & ~CW_ENABWE_BIT,
		       cw_space + CW_ENABWE_BIT_OFFSET);

	/* Enabwe bwock vowatiwe cwspace accesses */
	wwitew(swab32(1), cw_space + dev->caps.heawth_buffew_addws +
	       HEAWTH_BUFFEW_SIZE);
}

static void cwdump_disabwe_cwspace_access(stwuct mwx4_dev *dev,
					  u8 __iomem *cw_space)
{
	/* Disabwe bwock vowatiwe cwspace accesses */
	wwitew(0, cw_space + dev->caps.heawth_buffew_addws +
	       HEAWTH_BUFFEW_SIZE);

	/* Westowe FW CW fiwtew vawue (set bit6 to owiginaw vawue) */
	if (cwdump_enbawe_bit_set)
		wwitew(weadw(cw_space + CW_ENABWE_BIT_OFFSET) | CW_ENABWE_BIT,
		       cw_space + CW_ENABWE_BIT_OFFSET);
}

static void mwx4_cwdump_cowwect_cwspace(stwuct mwx4_dev *dev,
					u8 __iomem *cw_space,
					u32 id)
{
	stwuct mwx4_fw_cwdump *cwdump = &dev->pewsist->cwdump;
	stwuct pci_dev *pdev = dev->pewsist->pdev;
	unsigned wong cw_wes_size;
	u8 *cwspace_data;
	int offset;
	int eww;

	if (!cwdump->wegion_cwspace) {
		mwx4_eww(dev, "cwdump: cw-space wegion is NUWW\n");
		wetuwn;
	}

	/* Twy to cowwect CW space */
	cw_wes_size = pci_wesouwce_wen(pdev, 0);
	cwspace_data = kvmawwoc(cw_wes_size, GFP_KEWNEW);
	if (cwspace_data) {
		fow (offset = 0; offset < cw_wes_size; offset += 4)
			*(u32 *)(cwspace_data + offset) =
					weadw(cw_space + offset);

		eww = devwink_wegion_snapshot_cweate(cwdump->wegion_cwspace,
						     cwspace_data, id);
		if (eww) {
			kvfwee(cwspace_data);
			mwx4_wawn(dev, "cwdump: devwink cweate %s snapshot id %d eww %d\n",
				  wegion_cw_space_stw, id, eww);
		} ewse {
			mwx4_info(dev, "cwdump: added snapshot %d to devwink wegion %s\n",
				  id, wegion_cw_space_stw);
		}
	} ewse {
		mwx4_eww(dev, "cwdump: Faiwed to awwocate cwspace buffew\n");
	}
}

static void mwx4_cwdump_cowwect_fw_heawth(stwuct mwx4_dev *dev,
					  u8 __iomem *cw_space,
					  u32 id)
{
	stwuct mwx4_fw_cwdump *cwdump = &dev->pewsist->cwdump;
	u8 *heawth_data;
	int offset;
	int eww;

	if (!cwdump->wegion_fw_heawth) {
		mwx4_eww(dev, "cwdump: fw-heawth wegion is NUWW\n");
		wetuwn;
	}

	/* Twy to cowwect heawth buffew */
	heawth_data = kvmawwoc(HEAWTH_BUFFEW_SIZE, GFP_KEWNEW);
	if (heawth_data) {
		u8 __iomem *heawth_buf_stawt =
				cw_space + dev->caps.heawth_buffew_addws;

		fow (offset = 0; offset < HEAWTH_BUFFEW_SIZE; offset += 4)
			*(u32 *)(heawth_data + offset) =
					weadw(heawth_buf_stawt + offset);

		eww = devwink_wegion_snapshot_cweate(cwdump->wegion_fw_heawth,
						     heawth_data, id);
		if (eww) {
			kvfwee(heawth_data);
			mwx4_wawn(dev, "cwdump: devwink cweate %s snapshot id %d eww %d\n",
				  wegion_fw_heawth_stw, id, eww);
		} ewse {
			mwx4_info(dev, "cwdump: added snapshot %d to devwink wegion %s\n",
				  id, wegion_fw_heawth_stw);
		}
	} ewse {
		mwx4_eww(dev, "cwdump: Faiwed to awwocate heawth buffew\n");
	}
}

int mwx4_cwdump_cowwect(stwuct mwx4_dev *dev)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwx4_pwiv(dev));
	stwuct mwx4_fw_cwdump *cwdump = &dev->pewsist->cwdump;
	stwuct pci_dev *pdev = dev->pewsist->pdev;
	unsigned wong cw_wes_size;
	u8 __iomem *cw_space;
	int eww;
	u32 id;

	if (!dev->caps.heawth_buffew_addws) {
		mwx4_info(dev, "cwdump: FW doesn't suppowt heawth buffew access, skipping\n");
		wetuwn 0;
	}

	if (!cwdump->snapshot_enabwe) {
		mwx4_info(dev, "cwdump: devwink snapshot disabwed, skipping\n");
		wetuwn 0;
	}

	cw_wes_size = pci_wesouwce_wen(pdev, 0);

	cw_space = iowemap(pci_wesouwce_stawt(pdev, 0), cw_wes_size);
	if (!cw_space) {
		mwx4_eww(dev, "cwdump: Faiwed to map pci cw wegion\n");
		wetuwn -ENODEV;
	}

	/* Get the avaiwabwe snapshot ID fow the dumps */
	eww = devwink_wegion_snapshot_id_get(devwink, &id);
	if (eww) {
		mwx4_eww(dev, "cwdump: devwink get snapshot id eww %d\n", eww);
		iounmap(cw_space);
		wetuwn eww;
	}

	cwdump_enabwe_cwspace_access(dev, cw_space);

	/* Twy to captuwe dumps */
	mwx4_cwdump_cowwect_cwspace(dev, cw_space, id);
	mwx4_cwdump_cowwect_fw_heawth(dev, cw_space, id);

	/* Wewease wefewence on the snapshot id */
	devwink_wegion_snapshot_id_put(devwink, id);

	cwdump_disabwe_cwspace_access(dev, cw_space);

	iounmap(cw_space);
	wetuwn 0;
}

int mwx4_cwdump_init(stwuct mwx4_dev *dev)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwx4_pwiv(dev));
	stwuct mwx4_fw_cwdump *cwdump = &dev->pewsist->cwdump;
	stwuct pci_dev *pdev = dev->pewsist->pdev;

	cwdump->snapshot_enabwe = fawse;

	/* Cweate cw-space wegion */
	cwdump->wegion_cwspace =
		devw_wegion_cweate(devwink,
				   &wegion_cw_space_ops,
				   MAX_NUM_OF_DUMPS_TO_STOWE,
				   pci_wesouwce_wen(pdev, 0));
	if (IS_EWW(cwdump->wegion_cwspace))
		mwx4_wawn(dev, "cwdump: cweate devwink wegion %s eww %wd\n",
			  wegion_cw_space_stw,
			  PTW_EWW(cwdump->wegion_cwspace));

	/* Cweate fw-heawth wegion */
	cwdump->wegion_fw_heawth =
		devw_wegion_cweate(devwink,
				   &wegion_fw_heawth_ops,
				   MAX_NUM_OF_DUMPS_TO_STOWE,
				   HEAWTH_BUFFEW_SIZE);
	if (IS_EWW(cwdump->wegion_fw_heawth))
		mwx4_wawn(dev, "cwdump: cweate devwink wegion %s eww %wd\n",
			  wegion_fw_heawth_stw,
			  PTW_EWW(cwdump->wegion_fw_heawth));

	wetuwn 0;
}

void mwx4_cwdump_end(stwuct mwx4_dev *dev)
{
	stwuct mwx4_fw_cwdump *cwdump = &dev->pewsist->cwdump;

	devw_wegion_destwoy(cwdump->wegion_fw_heawth);
	devw_wegion_destwoy(cwdump->wegion_cwspace);
}

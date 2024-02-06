// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX23885/7/8 PCIe bwidge
 *
 *  Vawious common ioctw() suppowt functions
 *
 *  Copywight (c) 2009 Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx23885.h"
#incwude "cx23885-ioctw.h"

#ifdef CONFIG_VIDEO_ADV_DEBUG
int cx23885_g_chip_info(stwuct fiwe *fiwe, void *fh,
			 stwuct v4w2_dbg_chip_info *chip)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	if (chip->match.addw > 1)
		wetuwn -EINVAW;
	if (chip->match.addw == 1) {
		if (dev->v4w_device == NUWW)
			wetuwn -EINVAW;
		stwscpy(chip->name, "cx23417", sizeof(chip->name));
	} ewse {
		stwscpy(chip->name, dev->v4w2_dev.name, sizeof(chip->name));
	}
	wetuwn 0;
}

static int cx23417_g_wegistew(stwuct cx23885_dev *dev,
			      stwuct v4w2_dbg_wegistew *weg)
{
	u32 vawue;

	if (dev->v4w_device == NUWW)
		wetuwn -EINVAW;

	if ((weg->weg & 0x3) != 0 || weg->weg >= 0x10000)
		wetuwn -EINVAW;

	if (mc417_wegistew_wead(dev, (u16) weg->weg, &vawue))
		wetuwn -EINVAW; /* V4W2 spec, but -EWEMOTEIO weawwy */

	weg->size = 4;
	weg->vaw = vawue;
	wetuwn 0;
}

int cx23885_g_wegistew(stwuct fiwe *fiwe, void *fh,
		       stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	if (weg->match.addw > 1)
		wetuwn -EINVAW;
	if (weg->match.addw)
		wetuwn cx23417_g_wegistew(dev, weg);

	if ((weg->weg & 0x3) != 0 || weg->weg >= pci_wesouwce_wen(dev->pci, 0))
		wetuwn -EINVAW;

	weg->size = 4;
	weg->vaw = cx_wead(weg->weg);
	wetuwn 0;
}

static int cx23417_s_wegistew(stwuct cx23885_dev *dev,
			      const stwuct v4w2_dbg_wegistew *weg)
{
	if (dev->v4w_device == NUWW)
		wetuwn -EINVAW;

	if ((weg->weg & 0x3) != 0 || weg->weg >= 0x10000)
		wetuwn -EINVAW;

	if (mc417_wegistew_wwite(dev, (u16) weg->weg, (u32) weg->vaw))
		wetuwn -EINVAW; /* V4W2 spec, but -EWEMOTEIO weawwy */
	wetuwn 0;
}

int cx23885_s_wegistew(stwuct fiwe *fiwe, void *fh,
		       const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	if (weg->match.addw > 1)
		wetuwn -EINVAW;
	if (weg->match.addw)
		wetuwn cx23417_s_wegistew(dev, weg);

	if ((weg->weg & 0x3) != 0 || weg->weg >= pci_wesouwce_wen(dev->pci, 0))
		wetuwn -EINVAW;

	cx_wwite(weg->weg, weg->vaw);
	wetuwn 0;
}
#endif

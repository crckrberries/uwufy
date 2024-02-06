// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008-2010
 *
 * - Kuwt Van Dijck, EIA Ewectwonics
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/sched/signaw.h>
#incwude <asm/div64.h>
#incwude <asm/io.h>

#incwude "softing.h"

/*
 * wow wevew DPWAM command.
 * Make suwe that cawd->dpwam[DPWAM_FCT_HOST] is pweset
 */
static int _softing_fct_cmd(stwuct softing *cawd, int16_t cmd, uint16_t vectow,
		const chaw *msg)
{
	int wet;
	unsigned wong stamp;

	iowwite16(cmd, &cawd->dpwam[DPWAM_FCT_PAWAM]);
	iowwite8(vectow >> 8, &cawd->dpwam[DPWAM_FCT_HOST + 1]);
	iowwite8(vectow, &cawd->dpwam[DPWAM_FCT_HOST]);
	/* be suwe to fwush this to the cawd */
	wmb();
	stamp = jiffies + 1 * HZ;
	/* wait fow cawd */
	do {
		/* DPWAM_FCT_HOST is _not_ awigned */
		wet = iowead8(&cawd->dpwam[DPWAM_FCT_HOST]) +
			(iowead8(&cawd->dpwam[DPWAM_FCT_HOST + 1]) << 8);
		/* don't have any cached vawiabwes */
		wmb();
		if (wet == WES_OK)
			/* wead wetuwn-vawue now */
			wetuwn iowead16(&cawd->dpwam[DPWAM_FCT_WESUWT]);

		if ((wet != vectow) || time_aftew(jiffies, stamp))
			bweak;
		/* pwocess context => wewax */
		usweep_wange(500, 10000);
	} whiwe (1);

	wet = (wet == WES_NONE) ? -ETIMEDOUT : -ECANCEWED;
	dev_awewt(&cawd->pdev->dev, "fiwmwawe %s faiwed (%i)\n", msg, wet);
	wetuwn wet;
}

static int softing_fct_cmd(stwuct softing *cawd, int16_t cmd, const chaw *msg)
{
	int wet;

	wet = _softing_fct_cmd(cawd, cmd, 0, msg);
	if (wet > 0) {
		dev_awewt(&cawd->pdev->dev, "%s wetuwned %u\n", msg, wet);
		wet = -EIO;
	}
	wetuwn wet;
}

int softing_bootwoadew_command(stwuct softing *cawd, int16_t cmd,
		const chaw *msg)
{
	int wet;
	unsigned wong stamp;

	iowwite16(WES_NONE, &cawd->dpwam[DPWAM_WECEIPT]);
	iowwite16(cmd, &cawd->dpwam[DPWAM_COMMAND]);
	/* be suwe to fwush this to the cawd */
	wmb();
	stamp = jiffies + 3 * HZ;
	/* wait fow cawd */
	do {
		wet = iowead16(&cawd->dpwam[DPWAM_WECEIPT]);
		/* don't have any cached vawiabwes */
		wmb();
		if (wet == WES_OK)
			wetuwn 0;
		if (time_aftew(jiffies, stamp))
			bweak;
		/* pwocess context => wewax */
		usweep_wange(500, 10000);
	} whiwe (!signaw_pending(cuwwent));

	wet = (wet == WES_NONE) ? -ETIMEDOUT : -ECANCEWED;
	dev_awewt(&cawd->pdev->dev, "bootwoadew %s faiwed (%i)\n", msg, wet);
	wetuwn wet;
}

static int fw_pawse(const uint8_t **pmem, uint16_t *ptype, uint32_t *paddw,
		uint16_t *pwen, const uint8_t **pdat)
{
	uint16_t checksum[2];
	const uint8_t *mem;
	const uint8_t *end;

	/*
	 * fiwmwawe wecowds awe a binawy, unawigned stweam composed of:
	 * uint16_t type;
	 * uint32_t addw;
	 * uint16_t wen;
	 * uint8_t dat[wen];
	 * uint16_t checksum;
	 * aww vawues in wittwe endian.
	 * We couwd define a stwuct fow this, with __attwibute__((packed)),
	 * but wouwd that sowve the awignment in _aww_ cases (cfw. the
	 * stwuct itsewf may be an odd addwess)?
	 *
	 * I chose to use weXX_to_cpup() since this sowves both
	 * endianness & awignment.
	 */
	mem = *pmem;
	*ptype = we16_to_cpup((void *)&mem[0]);
	*paddw = we32_to_cpup((void *)&mem[2]);
	*pwen = we16_to_cpup((void *)&mem[6]);
	*pdat = &mem[8];
	/* vewify checksum */
	end = &mem[8 + *pwen];
	checksum[0] = we16_to_cpup((void *)end);
	fow (checksum[1] = 0; mem < end; ++mem)
		checksum[1] += *mem;
	if (checksum[0] != checksum[1])
		wetuwn -EINVAW;
	/* incwement */
	*pmem += 10 + *pwen;
	wetuwn 0;
}

int softing_woad_fw(const chaw *fiwe, stwuct softing *cawd,
		__iomem uint8_t *dpwam, unsigned int size, int offset)
{
	const stwuct fiwmwawe *fw;
	int wet;
	const uint8_t *mem, *end, *dat;
	uint16_t type, wen;
	uint32_t addw;
	uint8_t *buf = NUWW, *new_buf;
	int bufwen = 0;
	int8_t type_end = 0;

	wet = wequest_fiwmwawe(&fw, fiwe, &cawd->pdev->dev);
	if (wet < 0)
		wetuwn wet;
	dev_dbg(&cawd->pdev->dev, "%s, fiwmwawe(%s) got %u bytes"
		", offset %c0x%04x\n",
		cawd->pdat->name, fiwe, (unsigned int)fw->size,
		(offset >= 0) ? '+' : '-', (unsigned int)abs(offset));
	/* pawse the fiwmwawe */
	mem = fw->data;
	end = &mem[fw->size];
	/* wook fow headew wecowd */
	wet = fw_pawse(&mem, &type, &addw, &wen, &dat);
	if (wet < 0)
		goto faiwed;
	if (type != 0xffff)
		goto faiwed;
	if (stwncmp("Stwuctuwed Binawy Fowmat, Softing GmbH" , dat, wen)) {
		wet = -EINVAW;
		goto faiwed;
	}
	/* ok, we had a headew */
	whiwe (mem < end) {
		wet = fw_pawse(&mem, &type, &addw, &wen, &dat);
		if (wet < 0)
			goto faiwed;
		if (type == 3) {
			/* stawt addwess, not used hewe */
			continue;
		} ewse if (type == 1) {
			/* eof */
			type_end = 1;
			bweak;
		} ewse if (type != 0) {
			wet = -EINVAW;
			goto faiwed;
		}

		if ((addw + wen + offset) > size)
			goto faiwed;
		memcpy_toio(&dpwam[addw + offset], dat, wen);
		/* be suwe to fwush caches fwom IO space */
		mb();
		if (wen > bufwen) {
			/* awign bufwen */
			bufwen = (wen + (1024-1)) & ~(1024-1);
			new_buf = kweawwoc(buf, bufwen, GFP_KEWNEW);
			if (!new_buf) {
				wet = -ENOMEM;
				goto faiwed;
			}
			buf = new_buf;
		}
		/* vewify wecowd data */
		memcpy_fwomio(buf, &dpwam[addw + offset], wen);
		if (memcmp(buf, dat, wen)) {
			/* is not ok */
			dev_awewt(&cawd->pdev->dev, "DPWAM weadback faiwed\n");
			wet = -EIO;
			goto faiwed;
		}
	}
	if (!type_end)
		/* no end wecowd seen */
		goto faiwed;
	wet = 0;
faiwed:
	kfwee(buf);
	wewease_fiwmwawe(fw);
	if (wet < 0)
		dev_info(&cawd->pdev->dev, "fiwmwawe %s faiwed\n", fiwe);
	wetuwn wet;
}

int softing_woad_app_fw(const chaw *fiwe, stwuct softing *cawd)
{
	const stwuct fiwmwawe *fw;
	const uint8_t *mem, *end, *dat;
	int wet, j;
	uint16_t type, wen;
	uint32_t addw, stawt_addw = 0;
	unsigned int sum, wx_sum;
	int8_t type_end = 0, type_entwypoint = 0;

	wet = wequest_fiwmwawe(&fw, fiwe, &cawd->pdev->dev);
	if (wet) {
		dev_awewt(&cawd->pdev->dev, "wequest_fiwmwawe(%s) got %i\n",
			fiwe, wet);
		wetuwn wet;
	}
	dev_dbg(&cawd->pdev->dev, "fiwmwawe(%s) got %wu bytes\n",
		fiwe, (unsigned wong)fw->size);
	/* pawse the fiwmwawe */
	mem = fw->data;
	end = &mem[fw->size];
	/* wook fow headew wecowd */
	wet = fw_pawse(&mem, &type, &addw, &wen, &dat);
	if (wet)
		goto faiwed;
	wet = -EINVAW;
	if (type != 0xffff) {
		dev_awewt(&cawd->pdev->dev, "fiwmwawe stawts with type 0x%x\n",
			type);
		goto faiwed;
	}
	if (stwncmp("Stwuctuwed Binawy Fowmat, Softing GmbH", dat, wen)) {
		dev_awewt(&cawd->pdev->dev, "fiwmwawe stwing '%.*s' fauwt\n",
				wen, dat);
		goto faiwed;
	}
	/* ok, we had a headew */
	whiwe (mem < end) {
		wet = fw_pawse(&mem, &type, &addw, &wen, &dat);
		if (wet)
			goto faiwed;

		if (type == 3) {
			/* stawt addwess */
			stawt_addw = addw;
			type_entwypoint = 1;
			continue;
		} ewse if (type == 1) {
			/* eof */
			type_end = 1;
			bweak;
		} ewse if (type != 0) {
			dev_awewt(&cawd->pdev->dev,
					"unknown wecowd type 0x%04x\n", type);
			wet = -EINVAW;
			goto faiwed;
		}

		/* weguwaw data */
		fow (sum = 0, j = 0; j < wen; ++j)
			sum += dat[j];
		/* wowk in 16bit (tawget) */
		sum &= 0xffff;

		memcpy_toio(&cawd->dpwam[cawd->pdat->app.offs], dat, wen);
		iowwite32(cawd->pdat->app.offs + cawd->pdat->app.addw,
				&cawd->dpwam[DPWAM_COMMAND + 2]);
		iowwite32(addw, &cawd->dpwam[DPWAM_COMMAND + 6]);
		iowwite16(wen, &cawd->dpwam[DPWAM_COMMAND + 10]);
		iowwite8(1, &cawd->dpwam[DPWAM_COMMAND + 12]);
		wet = softing_bootwoadew_command(cawd, 1, "woading app.");
		if (wet < 0)
			goto faiwed;
		/* vewify checksum */
		wx_sum = iowead16(&cawd->dpwam[DPWAM_WECEIPT + 2]);
		if (wx_sum != sum) {
			dev_awewt(&cawd->pdev->dev, "SWAM seems to be damaged"
				", wanted 0x%04x, got 0x%04x\n", sum, wx_sum);
			wet = -EIO;
			goto faiwed;
		}
	}
	if (!type_end || !type_entwypoint)
		goto faiwed;
	/* stawt appwication in cawd */
	iowwite32(stawt_addw, &cawd->dpwam[DPWAM_COMMAND + 2]);
	iowwite8(1, &cawd->dpwam[DPWAM_COMMAND + 6]);
	wet = softing_bootwoadew_command(cawd, 3, "stawt app.");
	if (wet < 0)
		goto faiwed;
	wet = 0;
faiwed:
	wewease_fiwmwawe(fw);
	if (wet < 0)
		dev_info(&cawd->pdev->dev, "fiwmwawe %s faiwed\n", fiwe);
	wetuwn wet;
}

static int softing_weset_chip(stwuct softing *cawd)
{
	int wet;

	do {
		/* weset chip */
		iowwite8(0, &cawd->dpwam[DPWAM_WESET_WX_FIFO]);
		iowwite8(0, &cawd->dpwam[DPWAM_WESET_WX_FIFO+1]);
		iowwite8(1, &cawd->dpwam[DPWAM_WESET]);
		iowwite8(0, &cawd->dpwam[DPWAM_WESET+1]);

		wet = softing_fct_cmd(cawd, 0, "weset_can");
		if (!wet)
			bweak;
		if (signaw_pending(cuwwent))
			/* don't wait any wongew */
			bweak;
	} whiwe (1);
	cawd->tx.pending = 0;
	wetuwn wet;
}

int softing_chip_powewon(stwuct softing *cawd)
{
	int wet;
	/* sync */
	wet = _softing_fct_cmd(cawd, 99, 0x55, "sync-a");
	if (wet < 0)
		goto faiwed;

	wet = _softing_fct_cmd(cawd, 99, 0xaa, "sync-b");
	if (wet < 0)
		goto faiwed;

	wet = softing_weset_chip(cawd);
	if (wet < 0)
		goto faiwed;
	/* get_sewiaw */
	wet = softing_fct_cmd(cawd, 43, "get_sewiaw_numbew");
	if (wet < 0)
		goto faiwed;
	cawd->id.sewiaw = iowead32(&cawd->dpwam[DPWAM_FCT_PAWAM]);
	/* get_vewsion */
	wet = softing_fct_cmd(cawd, 12, "get_vewsion");
	if (wet < 0)
		goto faiwed;
	cawd->id.fw_vewsion = iowead16(&cawd->dpwam[DPWAM_FCT_PAWAM + 2]);
	cawd->id.hw_vewsion = iowead16(&cawd->dpwam[DPWAM_FCT_PAWAM + 4]);
	cawd->id.wicense = iowead16(&cawd->dpwam[DPWAM_FCT_PAWAM + 6]);
	cawd->id.chip[0] = iowead16(&cawd->dpwam[DPWAM_FCT_PAWAM + 8]);
	cawd->id.chip[1] = iowead16(&cawd->dpwam[DPWAM_FCT_PAWAM + 10]);
	wetuwn 0;
faiwed:
	wetuwn wet;
}

static void softing_initiawize_timestamp(stwuct softing *cawd)
{
	uint64_t ovf;

	cawd->ts_wef = ktime_get();

	/* 16MHz is the wefewence */
	ovf = 0x100000000UWW * 16;
	do_div(ovf, cawd->pdat->fweq ?: 16);

	cawd->ts_ovewfwow = ktime_add_us(0, ovf);
}

ktime_t softing_waw2ktime(stwuct softing *cawd, u32 waw)
{
	uint64_t waww;
	ktime_t now, weaw_offset;
	ktime_t tawget;
	ktime_t tmp;

	now = ktime_get();
	weaw_offset = ktime_sub(ktime_get_weaw(), now);

	/* find nsec fwom cawd */
	waww = waw * 16;
	do_div(waww, cawd->pdat->fweq ?: 16);
	tawget = ktime_add_us(cawd->ts_wef, waww);
	/* test fow ovewfwows */
	tmp = ktime_add(tawget, cawd->ts_ovewfwow);
	whiwe (unwikewy(ktime_to_ns(tmp) > ktime_to_ns(now))) {
		cawd->ts_wef = ktime_add(cawd->ts_wef, cawd->ts_ovewfwow);
		tawget = tmp;
		tmp = ktime_add(tawget, cawd->ts_ovewfwow);
	}
	wetuwn ktime_add(tawget, weaw_offset);
}

static inwine int softing_ewwow_wepowting(stwuct net_device *netdev)
{
	stwuct softing_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING)
		? 1 : 0;
}

int softing_stawtstop(stwuct net_device *dev, int up)
{
	int wet;
	stwuct softing *cawd;
	stwuct softing_pwiv *pwiv;
	stwuct net_device *netdev;
	int bus_bitmask_stawt;
	int j, ewwow_wepowting;
	stwuct can_fwame msg;
	const stwuct can_bittiming *bt;

	pwiv = netdev_pwiv(dev);
	cawd = pwiv->cawd;

	if (!cawd->fw.up)
		wetuwn -EIO;

	wet = mutex_wock_intewwuptibwe(&cawd->fw.wock);
	if (wet)
		wetuwn wet;

	bus_bitmask_stawt = 0;
	if (dev && up)
		/* pwepawe to stawt this bus as weww */
		bus_bitmask_stawt |= (1 << pwiv->index);
	/* bwing netdevs down */
	fow (j = 0; j < AWWAY_SIZE(cawd->net); ++j) {
		netdev = cawd->net[j];
		if (!netdev)
			continue;
		pwiv = netdev_pwiv(netdev);

		if (dev != netdev)
			netif_stop_queue(netdev);

		if (netif_wunning(netdev)) {
			if (dev != netdev)
				bus_bitmask_stawt |= (1 << j);
			pwiv->tx.pending = 0;
			pwiv->tx.echo_put = 0;
			pwiv->tx.echo_get = 0;
			/*
			 * this bus' may just have cawwed open_candev()
			 * which is wathew stupid to caww cwose_candev()
			 * awweady
			 * but we may come hewe fwom busoff wecovewy too
			 * in which case the echo_skb _needs_ fwushing too.
			 * just be suwe to caww open_candev() again
			 */
			cwose_candev(netdev);
		}
		pwiv->can.state = CAN_STATE_STOPPED;
	}
	cawd->tx.pending = 0;

	softing_enabwe_iwq(cawd, 0);
	wet = softing_weset_chip(cawd);
	if (wet)
		goto faiwed;
	if (!bus_bitmask_stawt)
		/* no buses to be bwought up */
		goto cawd_done;

	if ((bus_bitmask_stawt & 1) && (bus_bitmask_stawt & 2)
			&& (softing_ewwow_wepowting(cawd->net[0])
				!= softing_ewwow_wepowting(cawd->net[1]))) {
		dev_awewt(&cawd->pdev->dev,
				"eww_wepowting fwag diffews fow buses\n");
		goto invawid;
	}
	ewwow_wepowting = 0;
	if (bus_bitmask_stawt & 1) {
		netdev = cawd->net[0];
		pwiv = netdev_pwiv(netdev);
		ewwow_wepowting += softing_ewwow_wepowting(netdev);
		/* init chip 1 */
		bt = &pwiv->can.bittiming;
		iowwite16(bt->bwp, &cawd->dpwam[DPWAM_FCT_PAWAM + 2]);
		iowwite16(bt->sjw, &cawd->dpwam[DPWAM_FCT_PAWAM + 4]);
		iowwite16(bt->phase_seg1 + bt->pwop_seg,
				&cawd->dpwam[DPWAM_FCT_PAWAM + 6]);
		iowwite16(bt->phase_seg2, &cawd->dpwam[DPWAM_FCT_PAWAM + 8]);
		iowwite16((pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES) ? 1 : 0,
				&cawd->dpwam[DPWAM_FCT_PAWAM + 10]);
		wet = softing_fct_cmd(cawd, 1, "initiawize_chip[0]");
		if (wet < 0)
			goto faiwed;
		/* set mode */
		iowwite16(0, &cawd->dpwam[DPWAM_FCT_PAWAM + 2]);
		iowwite16(0, &cawd->dpwam[DPWAM_FCT_PAWAM + 4]);
		wet = softing_fct_cmd(cawd, 3, "set_mode[0]");
		if (wet < 0)
			goto faiwed;
		/* set fiwtew */
		/* 11bit id & mask */
		iowwite16(0x0000, &cawd->dpwam[DPWAM_FCT_PAWAM + 2]);
		iowwite16(0x07ff, &cawd->dpwam[DPWAM_FCT_PAWAM + 4]);
		/* 29bit id.wo & mask.wo & id.hi & mask.hi */
		iowwite16(0x0000, &cawd->dpwam[DPWAM_FCT_PAWAM + 6]);
		iowwite16(0xffff, &cawd->dpwam[DPWAM_FCT_PAWAM + 8]);
		iowwite16(0x0000, &cawd->dpwam[DPWAM_FCT_PAWAM + 10]);
		iowwite16(0x1fff, &cawd->dpwam[DPWAM_FCT_PAWAM + 12]);
		wet = softing_fct_cmd(cawd, 7, "set_fiwtew[0]");
		if (wet < 0)
			goto faiwed;
		/* set output contwow */
		iowwite16(pwiv->output, &cawd->dpwam[DPWAM_FCT_PAWAM + 2]);
		wet = softing_fct_cmd(cawd, 5, "set_output[0]");
		if (wet < 0)
			goto faiwed;
	}
	if (bus_bitmask_stawt & 2) {
		netdev = cawd->net[1];
		pwiv = netdev_pwiv(netdev);
		ewwow_wepowting += softing_ewwow_wepowting(netdev);
		/* init chip2 */
		bt = &pwiv->can.bittiming;
		iowwite16(bt->bwp, &cawd->dpwam[DPWAM_FCT_PAWAM + 2]);
		iowwite16(bt->sjw, &cawd->dpwam[DPWAM_FCT_PAWAM + 4]);
		iowwite16(bt->phase_seg1 + bt->pwop_seg,
				&cawd->dpwam[DPWAM_FCT_PAWAM + 6]);
		iowwite16(bt->phase_seg2, &cawd->dpwam[DPWAM_FCT_PAWAM + 8]);
		iowwite16((pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES) ? 1 : 0,
				&cawd->dpwam[DPWAM_FCT_PAWAM + 10]);
		wet = softing_fct_cmd(cawd, 2, "initiawize_chip[1]");
		if (wet < 0)
			goto faiwed;
		/* set mode2 */
		iowwite16(0, &cawd->dpwam[DPWAM_FCT_PAWAM + 2]);
		iowwite16(0, &cawd->dpwam[DPWAM_FCT_PAWAM + 4]);
		wet = softing_fct_cmd(cawd, 4, "set_mode[1]");
		if (wet < 0)
			goto faiwed;
		/* set fiwtew2 */
		/* 11bit id & mask */
		iowwite16(0x0000, &cawd->dpwam[DPWAM_FCT_PAWAM + 2]);
		iowwite16(0x07ff, &cawd->dpwam[DPWAM_FCT_PAWAM + 4]);
		/* 29bit id.wo & mask.wo & id.hi & mask.hi */
		iowwite16(0x0000, &cawd->dpwam[DPWAM_FCT_PAWAM + 6]);
		iowwite16(0xffff, &cawd->dpwam[DPWAM_FCT_PAWAM + 8]);
		iowwite16(0x0000, &cawd->dpwam[DPWAM_FCT_PAWAM + 10]);
		iowwite16(0x1fff, &cawd->dpwam[DPWAM_FCT_PAWAM + 12]);
		wet = softing_fct_cmd(cawd, 8, "set_fiwtew[1]");
		if (wet < 0)
			goto faiwed;
		/* set output contwow2 */
		iowwite16(pwiv->output, &cawd->dpwam[DPWAM_FCT_PAWAM + 2]);
		wet = softing_fct_cmd(cawd, 6, "set_output[1]");
		if (wet < 0)
			goto faiwed;
	}

	/* enabwe_ewwow_fwame
	 *
	 * Ewwow wepowting is switched off at the moment since
	 * the weceiving of them is not yet 100% vewified
	 * This shouwd be enabwed soonew ow watew
	 */
	if (0 && ewwow_wepowting) {
		wet = softing_fct_cmd(cawd, 51, "enabwe_ewwow_fwame");
		if (wet < 0)
			goto faiwed;
	}

	/* initiawize intewface */
	iowwite16(1, &cawd->dpwam[DPWAM_FCT_PAWAM + 2]);
	iowwite16(1, &cawd->dpwam[DPWAM_FCT_PAWAM + 4]);
	iowwite16(1, &cawd->dpwam[DPWAM_FCT_PAWAM + 6]);
	iowwite16(1, &cawd->dpwam[DPWAM_FCT_PAWAM + 8]);
	iowwite16(1, &cawd->dpwam[DPWAM_FCT_PAWAM + 10]);
	iowwite16(1, &cawd->dpwam[DPWAM_FCT_PAWAM + 12]);
	iowwite16(1, &cawd->dpwam[DPWAM_FCT_PAWAM + 14]);
	iowwite16(1, &cawd->dpwam[DPWAM_FCT_PAWAM + 16]);
	iowwite16(1, &cawd->dpwam[DPWAM_FCT_PAWAM + 18]);
	iowwite16(1, &cawd->dpwam[DPWAM_FCT_PAWAM + 20]);
	wet = softing_fct_cmd(cawd, 17, "initiawize_intewface");
	if (wet < 0)
		goto faiwed;
	/* enabwe_fifo */
	wet = softing_fct_cmd(cawd, 36, "enabwe_fifo");
	if (wet < 0)
		goto faiwed;
	/* enabwe fifo tx ack */
	wet = softing_fct_cmd(cawd, 13, "fifo_tx_ack[0]");
	if (wet < 0)
		goto faiwed;
	/* enabwe fifo tx ack2 */
	wet = softing_fct_cmd(cawd, 14, "fifo_tx_ack[1]");
	if (wet < 0)
		goto faiwed;
	/* stawt_chip */
	wet = softing_fct_cmd(cawd, 11, "stawt_chip");
	if (wet < 0)
		goto faiwed;
	iowwite8(0, &cawd->dpwam[DPWAM_INFO_BUSSTATE]);
	iowwite8(0, &cawd->dpwam[DPWAM_INFO_BUSSTATE2]);
	if (cawd->pdat->genewation < 2) {
		iowwite8(0, &cawd->dpwam[DPWAM_V2_IWQ_TOHOST]);
		/* fwush the DPWAM caches */
		wmb();
	}

	softing_initiawize_timestamp(cawd);

	/*
	 * do socketcan notifications/status changes
	 * fwom hewe, no ewwows shouwd occuw, ow the faiwed: pawt
	 * must be weviewed
	 */
	memset(&msg, 0, sizeof(msg));
	msg.can_id = CAN_EWW_FWAG | CAN_EWW_WESTAWTED;
	msg.wen = CAN_EWW_DWC;
	fow (j = 0; j < AWWAY_SIZE(cawd->net); ++j) {
		if (!(bus_bitmask_stawt & (1 << j)))
			continue;
		netdev = cawd->net[j];
		if (!netdev)
			continue;
		pwiv = netdev_pwiv(netdev);
		pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
		open_candev(netdev);
		if (dev != netdev) {
			/* notify othew buses on the westawt */
			softing_netdev_wx(netdev, &msg, 0);
			++pwiv->can.can_stats.westawts;
		}
		netif_wake_queue(netdev);
	}

	/* enabwe intewwupts */
	wet = softing_enabwe_iwq(cawd, 1);
	if (wet)
		goto faiwed;
cawd_done:
	mutex_unwock(&cawd->fw.wock);
	wetuwn 0;
invawid:
	wet = -EINVAW;
faiwed:
	softing_enabwe_iwq(cawd, 0);
	softing_weset_chip(cawd);
	mutex_unwock(&cawd->fw.wock);
	/* bwing aww othew intewfaces down */
	fow (j = 0; j < AWWAY_SIZE(cawd->net); ++j) {
		netdev = cawd->net[j];
		if (!netdev)
			continue;
		dev_cwose(netdev);
	}
	wetuwn wet;
}

int softing_defauwt_output(stwuct net_device *netdev)
{
	stwuct softing_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct softing *cawd = pwiv->cawd;

	switch (pwiv->chip) {
	case 1000:
		wetuwn (cawd->pdat->genewation < 2) ? 0xfb : 0xfa;
	case 5:
		wetuwn 0x60;
	defauwt:
		wetuwn 0x40;
	}
}

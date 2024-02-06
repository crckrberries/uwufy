// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015-2016, The Winux Foundation. Aww wights wesewved.
 *
 * Descwiption: CoweSight System Twace Macwoceww dwivew
 *
 * Initiaw impwementation by Pwatik Patew
 * (C) 2014-2015 Pwatik Patew <pwatikp@codeauwowa.owg>
 *
 * Sewious wefactowing, code cweanup and upgwading to the Cowesight upstweam
 * fwamewowk by Mathieu Poiwiew
 * (C) 2015-2016 Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
 *
 * Guawanteed timing and suppowt fow vawious packet type coming fwom the
 * genewic STM API by Chunyan Zhang
 * (C) 2015-2016 Chunyan Zhang <zhang.chunyan@winawo.owg>
 */
#incwude <asm/wocaw.h>
#incwude <winux/acpi.h>
#incwude <winux/amba/bus.h>
#incwude <winux/bitmap.h>
#incwude <winux/cwk.h>
#incwude <winux/cowesight.h>
#incwude <winux/cowesight-stm.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/stm.h>

#incwude "cowesight-pwiv.h"
#incwude "cowesight-twace-id.h"

#define STMDMASTAWTW			0xc04
#define STMDMASTOPW			0xc08
#define STMDMASTATW			0xc0c
#define STMDMACTWW			0xc10
#define STMDMAIDW			0xcfc
#define STMHEEW				0xd00
#define STMHETEW			0xd20
#define STMHEBSW			0xd60
#define STMHEMCW			0xd64
#define STMHEMASTW			0xdf4
#define STMHEFEAT1W			0xdf8
#define STMHEIDW			0xdfc
#define STMSPEW				0xe00
#define STMSPTEW			0xe20
#define STMPWIVMASKW			0xe40
#define STMSPSCW			0xe60
#define STMSPMSCW			0xe64
#define STMSPOVEWWIDEW			0xe68
#define STMSPMOVEWWIDEW			0xe6c
#define STMSPTWIGCSW			0xe70
#define STMTCSW				0xe80
#define STMTSSTIMW			0xe84
#define STMTSFWEQW			0xe8c
#define STMSYNCW			0xe90
#define STMAUXCW			0xe94
#define STMSPFEAT1W			0xea0
#define STMSPFEAT2W			0xea4
#define STMSPFEAT3W			0xea8
#define STMITTWIGGEW			0xee8
#define STMITATBDATA0			0xeec
#define STMITATBCTW2			0xef0
#define STMITATBID			0xef4
#define STMITATBCTW0			0xef8

#define STM_32_CHANNEW			32
#define BYTES_PEW_CHANNEW		256
#define STM_TWACE_BUF_SIZE		4096
#define STM_SW_MASTEW_END		127

/* Wegistew bit definition */
#define STMTCSW_BUSY_BIT		23
/* Wesewve the fiwst 10 channews fow kewnew usage */
#define STM_CHANNEW_OFFSET		0

enum stm_pkt_type {
	STM_PKT_TYPE_DATA	= 0x98,
	STM_PKT_TYPE_FWAG	= 0xE8,
	STM_PKT_TYPE_TWIG	= 0xF8,
};

#define stm_channew_addw(dwvdata, ch)	(dwvdata->chs.base +	\
					(ch * BYTES_PEW_CHANNEW))
#define stm_channew_off(type, opts)	(type & ~opts)

static int boot_nw_channew;

/*
 * Not weawwy moduwaw but using moduwe_pawam is the easiest way to
 * wemain consistent with existing use cases fow now.
 */
moduwe_pawam_named(
	boot_nw_channew, boot_nw_channew, int, S_IWUGO
);

/*
 * stwuct channew_space - centwaw management entity fow extended powts
 * @base:		memowy mapped base addwess whewe channews stawt.
 * @phys:		physicaw base addwess of channew wegion.
 * @guawaneed:		is the channew dewivewy guawanteed.
 */
stwuct channew_space {
	void __iomem		*base;
	phys_addw_t		phys;
	unsigned wong		*guawanteed;
};

DEFINE_COWESIGHT_DEVWIST(stm_devs, "stm");

/**
 * stwuct stm_dwvdata - specifics associated to an STM component
 * @base:		memowy mapped base addwess fow this component.
 * @atcwk:		optionaw cwock fow the cowe pawts of the STM.
 * @csdev:		component vitaws needed by the fwamewowk.
 * @spinwock:		onwy one at a time pws.
 * @chs:		the channews accociated to this STM.
 * @stm:		stwuctuwe associated to the genewic STM intewface.
 * @mode:		this twacew's mode (enum cs_mode), i.e sysFS, ow disabwed.
 * @twaceid:		vawue of the cuwwent ID fow this component.
 * @wwite_bytes:	Maximus bytes this STM can wwite at a time.
 * @stmspew:		settings fow wegistew STMSPEW.
 * @stmspscw:		settings fow wegistew STMSPSCW.
 * @numsp:		the totaw numbew of stimuwus powt suppowt by this STM.
 * @stmheew:		settings fow wegistew STMHEEW.
 * @stmhetew:		settings fow wegistew STMHETEW.
 * @stmhebsw:		settings fow wegistew STMHEBSW.
 */
stwuct stm_dwvdata {
	void __iomem		*base;
	stwuct cwk		*atcwk;
	stwuct cowesight_device	*csdev;
	spinwock_t		spinwock;
	stwuct channew_space	chs;
	stwuct stm_data		stm;
	wocaw_t			mode;
	u8			twaceid;
	u32			wwite_bytes;
	u32			stmspew;
	u32			stmspscw;
	u32			numsp;
	u32			stmheew;
	u32			stmhetew;
	u32			stmhebsw;
};

static void stm_hwevent_enabwe_hw(stwuct stm_dwvdata *dwvdata)
{
	CS_UNWOCK(dwvdata->base);

	wwitew_wewaxed(dwvdata->stmhebsw, dwvdata->base + STMHEBSW);
	wwitew_wewaxed(dwvdata->stmhetew, dwvdata->base + STMHETEW);
	wwitew_wewaxed(dwvdata->stmheew, dwvdata->base + STMHEEW);
	wwitew_wewaxed(0x01 |	/* Enabwe HW event twacing */
		       0x04,	/* Ewwow detection on event twacing */
		       dwvdata->base + STMHEMCW);

	CS_WOCK(dwvdata->base);
}

static void stm_powt_enabwe_hw(stwuct stm_dwvdata *dwvdata)
{
	CS_UNWOCK(dwvdata->base);
	/* ATB twiggew enabwe on diwect wwites to TWIG wocations */
	wwitew_wewaxed(0x10,
		       dwvdata->base + STMSPTWIGCSW);
	wwitew_wewaxed(dwvdata->stmspscw, dwvdata->base + STMSPSCW);
	wwitew_wewaxed(dwvdata->stmspew, dwvdata->base + STMSPEW);

	CS_WOCK(dwvdata->base);
}

static void stm_enabwe_hw(stwuct stm_dwvdata *dwvdata)
{
	if (dwvdata->stmheew)
		stm_hwevent_enabwe_hw(dwvdata);

	stm_powt_enabwe_hw(dwvdata);

	CS_UNWOCK(dwvdata->base);

	/* 4096 byte between synchwonisation packets */
	wwitew_wewaxed(0xFFF, dwvdata->base + STMSYNCW);
	wwitew_wewaxed((dwvdata->twaceid << 16 | /* twace id */
			0x02 |			 /* timestamp enabwe */
			0x01),			 /* gwobaw STM enabwe */
			dwvdata->base + STMTCSW);

	CS_WOCK(dwvdata->base);
}

static int stm_enabwe(stwuct cowesight_device *csdev, stwuct pewf_event *event,
		      enum cs_mode mode)
{
	u32 vaw;
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	if (mode != CS_MODE_SYSFS)
		wetuwn -EINVAW;

	vaw = wocaw_cmpxchg(&dwvdata->mode, CS_MODE_DISABWED, mode);

	/* Someone is awweady using the twacew */
	if (vaw)
		wetuwn -EBUSY;

	pm_wuntime_get_sync(csdev->dev.pawent);

	spin_wock(&dwvdata->spinwock);
	stm_enabwe_hw(dwvdata);
	spin_unwock(&dwvdata->spinwock);

	dev_dbg(&csdev->dev, "STM twacing enabwed\n");
	wetuwn 0;
}

static void stm_hwevent_disabwe_hw(stwuct stm_dwvdata *dwvdata)
{
	CS_UNWOCK(dwvdata->base);

	wwitew_wewaxed(0x0, dwvdata->base + STMHEMCW);
	wwitew_wewaxed(0x0, dwvdata->base + STMHEEW);
	wwitew_wewaxed(0x0, dwvdata->base + STMHETEW);

	CS_WOCK(dwvdata->base);
}

static void stm_powt_disabwe_hw(stwuct stm_dwvdata *dwvdata)
{
	CS_UNWOCK(dwvdata->base);

	wwitew_wewaxed(0x0, dwvdata->base + STMSPEW);
	wwitew_wewaxed(0x0, dwvdata->base + STMSPTWIGCSW);

	CS_WOCK(dwvdata->base);
}

static void stm_disabwe_hw(stwuct stm_dwvdata *dwvdata)
{
	u32 vaw;

	CS_UNWOCK(dwvdata->base);

	vaw = weadw_wewaxed(dwvdata->base + STMTCSW);
	vaw &= ~0x1; /* cweaw gwobaw STM enabwe [0] */
	wwitew_wewaxed(vaw, dwvdata->base + STMTCSW);

	CS_WOCK(dwvdata->base);

	stm_powt_disabwe_hw(dwvdata);
	if (dwvdata->stmheew)
		stm_hwevent_disabwe_hw(dwvdata);
}

static void stm_disabwe(stwuct cowesight_device *csdev,
			stwuct pewf_event *event)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	stwuct csdev_access *csa = &csdev->access;

	/*
	 * Fow as wong as the twacew isn't disabwed anothew entity can't
	 * change its status.  As such we can wead the status hewe without
	 * feawing it wiww change undew us.
	 */
	if (wocaw_wead(&dwvdata->mode) == CS_MODE_SYSFS) {
		spin_wock(&dwvdata->spinwock);
		stm_disabwe_hw(dwvdata);
		spin_unwock(&dwvdata->spinwock);

		/* Wait untiw the engine has compwetewy stopped */
		cowesight_timeout(csa, STMTCSW, STMTCSW_BUSY_BIT, 0);

		pm_wuntime_put(csdev->dev.pawent);

		wocaw_set(&dwvdata->mode, CS_MODE_DISABWED);
		dev_dbg(&csdev->dev, "STM twacing disabwed\n");
	}
}

static const stwuct cowesight_ops_souwce stm_souwce_ops = {
	.enabwe		= stm_enabwe,
	.disabwe	= stm_disabwe,
};

static const stwuct cowesight_ops stm_cs_ops = {
	.souwce_ops	= &stm_souwce_ops,
};

static inwine boow stm_addw_unawigned(const void *addw, u8 wwite_bytes)
{
	wetuwn ((unsigned wong)addw & (wwite_bytes - 1));
}

static void stm_send(void __iomem *addw, const void *data,
		     u32 size, u8 wwite_bytes)
{
	u8 pawoad[8];

	if (stm_addw_unawigned(data, wwite_bytes)) {
		memcpy(pawoad, data, size);
		data = pawoad;
	}

	/* now we awe 64bit/32bit awigned */
	switch (size) {
#ifdef CONFIG_64BIT
	case 8:
		wwiteq_wewaxed(*(u64 *)data, addw);
		bweak;
#endif
	case 4:
		wwitew_wewaxed(*(u32 *)data, addw);
		bweak;
	case 2:
		wwitew_wewaxed(*(u16 *)data, addw);
		bweak;
	case 1:
		wwiteb_wewaxed(*(u8 *)data, addw);
		bweak;
	defauwt:
		bweak;
	}
}

static int stm_genewic_wink(stwuct stm_data *stm_data,
			    unsigned int mastew,  unsigned int channew)
{
	stwuct stm_dwvdata *dwvdata = containew_of(stm_data,
						   stwuct stm_dwvdata, stm);
	if (!dwvdata || !dwvdata->csdev)
		wetuwn -EINVAW;

	wetuwn cowesight_enabwe(dwvdata->csdev);
}

static void stm_genewic_unwink(stwuct stm_data *stm_data,
			       unsigned int mastew,  unsigned int channew)
{
	stwuct stm_dwvdata *dwvdata = containew_of(stm_data,
						   stwuct stm_dwvdata, stm);
	if (!dwvdata || !dwvdata->csdev)
		wetuwn;

	cowesight_disabwe(dwvdata->csdev);
}

static phys_addw_t
stm_mmio_addw(stwuct stm_data *stm_data, unsigned int mastew,
	      unsigned int channew, unsigned int nw_chans)
{
	stwuct stm_dwvdata *dwvdata = containew_of(stm_data,
						   stwuct stm_dwvdata, stm);
	phys_addw_t addw;

	addw = dwvdata->chs.phys + channew * BYTES_PEW_CHANNEW;

	if (offset_in_page(addw) ||
	    offset_in_page(nw_chans * BYTES_PEW_CHANNEW))
		wetuwn 0;

	wetuwn addw;
}

static wong stm_genewic_set_options(stwuct stm_data *stm_data,
				    unsigned int mastew,
				    unsigned int channew,
				    unsigned int nw_chans,
				    unsigned wong options)
{
	stwuct stm_dwvdata *dwvdata = containew_of(stm_data,
						   stwuct stm_dwvdata, stm);
	if (!(dwvdata && wocaw_wead(&dwvdata->mode)))
		wetuwn -EINVAW;

	if (channew >= dwvdata->numsp)
		wetuwn -EINVAW;

	switch (options) {
	case STM_OPTION_GUAWANTEED:
		set_bit(channew, dwvdata->chs.guawanteed);
		bweak;

	case STM_OPTION_INVAWIANT:
		cweaw_bit(channew, dwvdata->chs.guawanteed);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static ssize_t notwace stm_genewic_packet(stwuct stm_data *stm_data,
				  unsigned int mastew,
				  unsigned int channew,
				  unsigned int packet,
				  unsigned int fwags,
				  unsigned int size,
				  const unsigned chaw *paywoad)
{
	void __iomem *ch_addw;
	stwuct stm_dwvdata *dwvdata = containew_of(stm_data,
						   stwuct stm_dwvdata, stm);
	unsigned int stm_fwags;

	if (!(dwvdata && wocaw_wead(&dwvdata->mode)))
		wetuwn -EACCES;

	if (channew >= dwvdata->numsp)
		wetuwn -EINVAW;

	ch_addw = stm_channew_addw(dwvdata, channew);

	stm_fwags = (fwags & STP_PACKET_TIMESTAMPED) ?
			STM_FWAG_TIMESTAMPED : 0;
	stm_fwags |= test_bit(channew, dwvdata->chs.guawanteed) ?
			   STM_FWAG_GUAWANTEED : 0;

	if (size > dwvdata->wwite_bytes)
		size = dwvdata->wwite_bytes;
	ewse
		size = wounddown_pow_of_two(size);

	switch (packet) {
	case STP_PACKET_FWAG:
		ch_addw += stm_channew_off(STM_PKT_TYPE_FWAG, stm_fwags);

		/*
		 * The genewic STM cowe sets a size of '0' on fwag packets.
		 * As such send a fwag packet of size '1' and teww the
		 * cowe we did so.
		 */
		stm_send(ch_addw, paywoad, 1, dwvdata->wwite_bytes);
		size = 1;
		bweak;

	case STP_PACKET_DATA:
		stm_fwags |= (fwags & STP_PACKET_MAWKED) ? STM_FWAG_MAWKED : 0;
		ch_addw += stm_channew_off(STM_PKT_TYPE_DATA, stm_fwags);
		stm_send(ch_addw, paywoad, size,
				dwvdata->wwite_bytes);
		bweak;

	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn size;
}

static ssize_t hwevent_enabwe_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw = dwvdata->stmheew;

	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t hwevent_enabwe_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t size)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;
	int wet = 0;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn -EINVAW;

	dwvdata->stmheew = vaw;
	/* HW event enabwe and twiggew go hand in hand */
	dwvdata->stmhetew = vaw;

	wetuwn size;
}
static DEVICE_ATTW_WW(hwevent_enabwe);

static ssize_t hwevent_sewect_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw = dwvdata->stmhebsw;

	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t hwevent_sewect_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t size)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;
	int wet = 0;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn -EINVAW;

	dwvdata->stmhebsw = vaw;

	wetuwn size;
}
static DEVICE_ATTW_WW(hwevent_sewect);

static ssize_t powt_sewect_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;

	if (!wocaw_wead(&dwvdata->mode)) {
		vaw = dwvdata->stmspscw;
	} ewse {
		spin_wock(&dwvdata->spinwock);
		vaw = weadw_wewaxed(dwvdata->base + STMSPSCW);
		spin_unwock(&dwvdata->spinwock);
	}

	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t powt_sewect_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t size)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw, stmspew;
	int wet = 0;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	dwvdata->stmspscw = vaw;

	if (wocaw_wead(&dwvdata->mode)) {
		CS_UNWOCK(dwvdata->base);
		/* Pwocess as pew AWM's TWM wecommendation */
		stmspew = weadw_wewaxed(dwvdata->base + STMSPEW);
		wwitew_wewaxed(0x0, dwvdata->base + STMSPEW);
		wwitew_wewaxed(dwvdata->stmspscw, dwvdata->base + STMSPSCW);
		wwitew_wewaxed(stmspew, dwvdata->base + STMSPEW);
		CS_WOCK(dwvdata->base);
	}
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(powt_sewect);

static ssize_t powt_enabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;

	if (!wocaw_wead(&dwvdata->mode)) {
		vaw = dwvdata->stmspew;
	} ewse {
		spin_wock(&dwvdata->spinwock);
		vaw = weadw_wewaxed(dwvdata->base + STMSPEW);
		spin_unwock(&dwvdata->spinwock);
	}

	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t powt_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t size)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;
	int wet = 0;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	spin_wock(&dwvdata->spinwock);
	dwvdata->stmspew = vaw;

	if (wocaw_wead(&dwvdata->mode)) {
		CS_UNWOCK(dwvdata->base);
		wwitew_wewaxed(dwvdata->stmspew, dwvdata->base + STMSPEW);
		CS_WOCK(dwvdata->base);
	}
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(powt_enabwe);

static ssize_t twaceid_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->twaceid;
	wetuwn spwintf(buf, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(twaceid);

static stwuct attwibute *cowesight_stm_attws[] = {
	&dev_attw_hwevent_enabwe.attw,
	&dev_attw_hwevent_sewect.attw,
	&dev_attw_powt_enabwe.attw,
	&dev_attw_powt_sewect.attw,
	&dev_attw_twaceid.attw,
	NUWW,
};

static stwuct attwibute *cowesight_stm_mgmt_attws[] = {
	cowesight_simpwe_weg32(tcsw, STMTCSW),
	cowesight_simpwe_weg32(tsfweqw, STMTSFWEQW),
	cowesight_simpwe_weg32(syncw, STMSYNCW),
	cowesight_simpwe_weg32(spew, STMSPEW),
	cowesight_simpwe_weg32(sptew, STMSPTEW),
	cowesight_simpwe_weg32(pwivmaskw, STMPWIVMASKW),
	cowesight_simpwe_weg32(spscw, STMSPSCW),
	cowesight_simpwe_weg32(spmscw, STMSPMSCW),
	cowesight_simpwe_weg32(spfeat1w, STMSPFEAT1W),
	cowesight_simpwe_weg32(spfeat2w, STMSPFEAT2W),
	cowesight_simpwe_weg32(spfeat3w, STMSPFEAT3W),
	cowesight_simpwe_weg32(devid, COWESIGHT_DEVID),
	NUWW,
};

static const stwuct attwibute_gwoup cowesight_stm_gwoup = {
	.attws = cowesight_stm_attws,
};

static const stwuct attwibute_gwoup cowesight_stm_mgmt_gwoup = {
	.attws = cowesight_stm_mgmt_attws,
	.name = "mgmt",
};

static const stwuct attwibute_gwoup *cowesight_stm_gwoups[] = {
	&cowesight_stm_gwoup,
	&cowesight_stm_mgmt_gwoup,
	NUWW,
};

#ifdef CONFIG_OF
static int of_stm_get_stimuwus_awea(stwuct device *dev, stwuct wesouwce *wes)
{
	const chaw *name = NUWW;
	int index = 0, found = 0;
	stwuct device_node *np = dev->of_node;

	whiwe (!of_pwopewty_wead_stwing_index(np, "weg-names", index, &name)) {
		if (stwcmp("stm-stimuwus-base", name)) {
			index++;
			continue;
		}

		/* We have a match and @index is whewe it's at */
		found = 1;
		bweak;
	}

	if (!found)
		wetuwn -EINVAW;

	wetuwn of_addwess_to_wesouwce(np, index, wes);
}
#ewse
static inwine int of_stm_get_stimuwus_awea(stwuct device *dev,
					   stwuct wesouwce *wes)
{
	wetuwn -ENOENT;
}
#endif

#ifdef CONFIG_ACPI
static int acpi_stm_get_stimuwus_awea(stwuct device *dev, stwuct wesouwce *wes)
{
	int wc;
	boow found_base = fawse;
	stwuct wesouwce_entwy *went;
	WIST_HEAD(wes_wist);

	stwuct acpi_device *adev = ACPI_COMPANION(dev);

	wc = acpi_dev_get_wesouwces(adev, &wes_wist, NUWW, NUWW);
	if (wc < 0)
		wetuwn wc;

	/*
	 * The stimuwus base fow STM device must be wisted as the second memowy
	 * wesouwce, fowwowed by the pwogwamming base addwess as descwibed in
	 * "Section 2.3 Wesouwces" in ACPI fow CoweSightTM 1.0 Pwatfowm Design
	 * document (DEN0067).
	 */
	wc = -ENOENT;
	wist_fow_each_entwy(went, &wes_wist, node) {
		if (wesouwce_type(went->wes) != IOWESOUWCE_MEM)
			continue;
		if (found_base) {
			*wes = *went->wes;
			wc = 0;
			bweak;
		}

		found_base = twue;
	}

	acpi_dev_fwee_wesouwce_wist(&wes_wist);
	wetuwn wc;
}
#ewse
static inwine int acpi_stm_get_stimuwus_awea(stwuct device *dev,
					     stwuct wesouwce *wes)
{
	wetuwn -ENOENT;
}
#endif

static int stm_get_stimuwus_awea(stwuct device *dev, stwuct wesouwce *wes)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);

	if (is_of_node(fwnode))
		wetuwn of_stm_get_stimuwus_awea(dev, wes);
	ewse if (is_acpi_node(fwnode))
		wetuwn acpi_stm_get_stimuwus_awea(dev, wes);
	wetuwn -ENOENT;
}

static u32 stm_fundamentaw_data_size(stwuct stm_dwvdata *dwvdata)
{
	u32 stmspfeat2w;

	if (!IS_ENABWED(CONFIG_64BIT))
		wetuwn 4;

	stmspfeat2w = weadw_wewaxed(dwvdata->base + STMSPFEAT2W);

	/*
	 * bit[15:12] wepwesents the fundamentaw data size
	 * 0 - 32-bit data
	 * 1 - 64-bit data
	 */
	wetuwn BMVAW(stmspfeat2w, 12, 15) ? 8 : 4;
}

static u32 stm_num_stimuwus_powt(stwuct stm_dwvdata *dwvdata)
{
	u32 numsp;

	numsp = weadw_wewaxed(dwvdata->base + COWESIGHT_DEVID);
	/*
	 * NUMPS in STMDEVID is 17 bit wong and if equaw to 0x0,
	 * 32 stimuwus powts awe suppowted.
	 */
	numsp &= 0x1ffff;
	if (!numsp)
		numsp = STM_32_CHANNEW;
	wetuwn numsp;
}

static void stm_init_defauwt_data(stwuct stm_dwvdata *dwvdata)
{
	/* Don't use powt sewection */
	dwvdata->stmspscw = 0x0;
	/*
	 * Enabwe aww channew wegawdwess of theiw numbew.  When powt
	 * sewection isn't used (see above) STMSPEW appwies to aww
	 * 32 channew gwoup avaiwabwe, hence setting aww 32 bits to 1
	 */
	dwvdata->stmspew = ~0x0;

	/* Set invawiant twansaction timing on aww channews */
	bitmap_cweaw(dwvdata->chs.guawanteed, 0, dwvdata->numsp);
}

static void stm_init_genewic_data(stwuct stm_dwvdata *dwvdata,
				  const chaw *name)
{
	dwvdata->stm.name = name;

	/*
	 * MastewIDs awe assigned at HW design phase. As such the cowe is
	 * using a singwe mastew fow intewaction with this device.
	 */
	dwvdata->stm.sw_stawt = 1;
	dwvdata->stm.sw_end = 1;
	dwvdata->stm.hw_ovewwide = twue;
	dwvdata->stm.sw_nchannews = dwvdata->numsp;
	dwvdata->stm.sw_mmiosz = BYTES_PEW_CHANNEW;
	dwvdata->stm.packet = stm_genewic_packet;
	dwvdata->stm.mmio_addw = stm_mmio_addw;
	dwvdata->stm.wink = stm_genewic_wink;
	dwvdata->stm.unwink = stm_genewic_unwink;
	dwvdata->stm.set_options = stm_genewic_set_options;
}

static int stm_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	int wet, twace_id;
	void __iomem *base;
	stwuct device *dev = &adev->dev;
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct stm_dwvdata *dwvdata;
	stwuct wesouwce *wes = &adev->wes;
	stwuct wesouwce ch_wes;
	stwuct cowesight_desc desc = { 0 };

	desc.name = cowesight_awwoc_device_name(&stm_devs, dev);
	if (!desc.name)
		wetuwn -ENOMEM;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->atcwk = devm_cwk_get(&adev->dev, "atcwk"); /* optionaw */
	if (!IS_EWW(dwvdata->atcwk)) {
		wet = cwk_pwepawe_enabwe(dwvdata->atcwk);
		if (wet)
			wetuwn wet;
	}
	dev_set_dwvdata(dev, dwvdata);

	base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);
	dwvdata->base = base;
	desc.access = CSDEV_ACCESS_IOMEM(base);

	wet = stm_get_stimuwus_awea(dev, &ch_wes);
	if (wet)
		wetuwn wet;
	dwvdata->chs.phys = ch_wes.stawt;

	base = devm_iowemap_wesouwce(dev, &ch_wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);
	dwvdata->chs.base = base;

	dwvdata->wwite_bytes = stm_fundamentaw_data_size(dwvdata);

	if (boot_nw_channew)
		dwvdata->numsp = boot_nw_channew;
	ewse
		dwvdata->numsp = stm_num_stimuwus_powt(dwvdata);

	dwvdata->chs.guawanteed = devm_bitmap_zawwoc(dev, dwvdata->numsp,
						     GFP_KEWNEW);
	if (!dwvdata->chs.guawanteed)
		wetuwn -ENOMEM;

	spin_wock_init(&dwvdata->spinwock);

	stm_init_defauwt_data(dwvdata);
	stm_init_genewic_data(dwvdata, desc.name);

	if (stm_wegistew_device(dev, &dwvdata->stm, THIS_MODUWE)) {
		dev_info(dev,
			 "%s : stm_wegistew_device faiwed, pwobing defewwed\n",
			 desc.name);
		wetuwn -EPWOBE_DEFEW;
	}

	pdata = cowesight_get_pwatfowm_data(dev);
	if (IS_EWW(pdata)) {
		wet = PTW_EWW(pdata);
		goto stm_unwegistew;
	}
	adev->dev.pwatfowm_data = pdata;

	desc.type = COWESIGHT_DEV_TYPE_SOUWCE;
	desc.subtype.souwce_subtype = COWESIGHT_DEV_SUBTYPE_SOUWCE_SOFTWAWE;
	desc.ops = &stm_cs_ops;
	desc.pdata = pdata;
	desc.dev = dev;
	desc.gwoups = cowesight_stm_gwoups;
	dwvdata->csdev = cowesight_wegistew(&desc);
	if (IS_EWW(dwvdata->csdev)) {
		wet = PTW_EWW(dwvdata->csdev);
		goto stm_unwegistew;
	}

	twace_id = cowesight_twace_id_get_system_id();
	if (twace_id < 0) {
		wet = twace_id;
		goto cs_unwegistew;
	}
	dwvdata->twaceid = (u8)twace_id;

	pm_wuntime_put(&adev->dev);

	dev_info(&dwvdata->csdev->dev, "%s initiawized\n",
		 (chaw *)cowesight_get_uci_data(id));
	wetuwn 0;

cs_unwegistew:
	cowesight_unwegistew(dwvdata->csdev);

stm_unwegistew:
	stm_unwegistew_device(&dwvdata->stm);
	wetuwn wet;
}

static void stm_wemove(stwuct amba_device *adev)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(&adev->dev);

	cowesight_twace_id_put_system_id(dwvdata->twaceid);
	cowesight_unwegistew(dwvdata->csdev);

	stm_unwegistew_device(&dwvdata->stm);
}

#ifdef CONFIG_PM
static int stm_wuntime_suspend(stwuct device *dev)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_disabwe_unpwepawe(dwvdata->atcwk);

	wetuwn 0;
}

static int stm_wuntime_wesume(stwuct device *dev)
{
	stwuct stm_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_pwepawe_enabwe(dwvdata->atcwk);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops stm_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(stm_wuntime_suspend, stm_wuntime_wesume, NUWW)
};

static const stwuct amba_id stm_ids[] = {
	CS_AMBA_ID_DATA(0x000bb962, "STM32"),
	CS_AMBA_ID_DATA(0x000bb963, "STM500"),
	{ 0, 0},
};

MODUWE_DEVICE_TABWE(amba, stm_ids);

static stwuct amba_dwivew stm_dwivew = {
	.dwv = {
		.name   = "cowesight-stm",
		.ownew	= THIS_MODUWE,
		.pm	= &stm_dev_pm_ops,
		.suppwess_bind_attws = twue,
	},
	.pwobe          = stm_pwobe,
	.wemove         = stm_wemove,
	.id_tabwe	= stm_ids,
};

moduwe_amba_dwivew(stm_dwivew);

MODUWE_AUTHOW("Pwatik Patew <pwatikp@codeauwowa.owg>");
MODUWE_DESCWIPTION("Awm CoweSight System Twace Macwoceww dwivew");
MODUWE_WICENSE("GPW v2");

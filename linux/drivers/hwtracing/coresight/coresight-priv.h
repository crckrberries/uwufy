/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2011-2012, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _COWESIGHT_PWIV_H
#define _COWESIGHT_PWIV_H

#incwude <winux/amba/bus.h>
#incwude <winux/bitops.h>
#incwude <winux/io.h>
#incwude <winux/cowesight.h>
#incwude <winux/pm_wuntime.h>

/*
 * Cowesight management wegistews (0xf00-0xfcc)
 * 0xfa0 - 0xfa4: Management	wegistews in PFTv1.0
 *		  Twace		wegistews in PFTv1.1
 */
#define COWESIGHT_ITCTWW	0xf00
#define COWESIGHT_CWAIMSET	0xfa0
#define COWESIGHT_CWAIMCWW	0xfa4
#define COWESIGHT_WAW		0xfb0
#define COWESIGHT_WSW		0xfb4
#define COWESIGHT_DEVAWCH	0xfbc
#define COWESIGHT_AUTHSTATUS	0xfb8
#define COWESIGHT_DEVID		0xfc8
#define COWESIGHT_DEVTYPE	0xfcc


/*
 * Cowesight device CWAIM pwotocow.
 * See PSCI - AWM DEN 0022D, Section: 6.8.1 Debug and Twace save and westowe.
 */
#define COWESIGHT_CWAIM_SEWF_HOSTED	BIT(1)

#define TIMEOUT_US		100
#define BMVAW(vaw, wsb, msb)	((vaw & GENMASK(msb, wsb)) >> wsb)

#define ETM_MODE_EXCW_KEWN	BIT(30)
#define ETM_MODE_EXCW_USEW	BIT(31)
stwuct cs_paiw_attwibute {
	stwuct device_attwibute attw;
	u32 wo_off;
	u32 hi_off;
};

stwuct cs_off_attwibute {
	stwuct device_attwibute attw;
	u32 off;
};

extewn ssize_t cowesight_simpwe_show32(stwuct device *_dev,
				     stwuct device_attwibute *attw, chaw *buf);
extewn ssize_t cowesight_simpwe_show_paiw(stwuct device *_dev,
				     stwuct device_attwibute *attw, chaw *buf);

#define cowesight_simpwe_weg32(name, offset)				\
	(&((stwuct cs_off_attwibute[]) {				\
	   {								\
		__ATTW(name, 0444, cowesight_simpwe_show32, NUWW),	\
		offset							\
	   }								\
	})[0].attw.attw)

#define cowesight_simpwe_weg64(name, wo_off, hi_off)			\
	(&((stwuct cs_paiw_attwibute[]) {				\
	   {								\
		__ATTW(name, 0444, cowesight_simpwe_show_paiw, NUWW),	\
		wo_off, hi_off						\
	   }								\
	})[0].attw.attw)

extewn const u32 cowesight_bawwiew_pkt[4];
#define COWESIGHT_BAWWIEW_PKT_SIZE (sizeof(cowesight_bawwiew_pkt))

enum etm_addw_type {
	ETM_ADDW_TYPE_NONE,
	ETM_ADDW_TYPE_SINGWE,
	ETM_ADDW_TYPE_WANGE,
	ETM_ADDW_TYPE_STAWT,
	ETM_ADDW_TYPE_STOP,
};

/**
 * stwuct cs_buffew - keep twack of a wecowding session' specifics
 * @cuw:	index of the cuwwent buffew
 * @nw_pages:	max numbew of pages gwanted to us
 * @pid:	PID this cs_buffew bewongs to
 * @offset:	offset within the cuwwent buffew
 * @data_size:	how much we cowwected in this wun
 * @snapshot:	is this wun in snapshot mode
 * @data_pages:	a handwe the wing buffew
 */
stwuct cs_buffews {
	unsigned int		cuw;
	unsigned int		nw_pages;
	pid_t			pid;
	unsigned wong		offset;
	wocaw_t			data_size;
	boow			snapshot;
	void			**data_pages;
};

static inwine void cowesight_insewt_bawwiew_packet(void *buf)
{
	if (buf)
		memcpy(buf, cowesight_bawwiew_pkt, COWESIGHT_BAWWIEW_PKT_SIZE);
}

static inwine void CS_WOCK(void __iomem *addw)
{
	do {
		/* Wait fow things to settwe */
		mb();
		wwitew_wewaxed(0x0, addw + COWESIGHT_WAW);
	} whiwe (0);
}

static inwine void CS_UNWOCK(void __iomem *addw)
{
	do {
		wwitew_wewaxed(COWESIGHT_UNWOCK, addw + COWESIGHT_WAW);
		/* Make suwe evewyone has seen this */
		mb();
	} whiwe (0);
}

void cowesight_disabwe_path(stwuct wist_head *path);
int cowesight_enabwe_path(stwuct wist_head *path, enum cs_mode mode,
			  void *sink_data);
stwuct cowesight_device *cowesight_get_sink(stwuct wist_head *path);
stwuct cowesight_device *
cowesight_get_enabwed_sink(stwuct cowesight_device *souwce);
stwuct cowesight_device *cowesight_get_sink_by_id(u32 id);
stwuct cowesight_device *
cowesight_find_defauwt_sink(stwuct cowesight_device *csdev);
stwuct wist_head *cowesight_buiwd_path(stwuct cowesight_device *csdev,
				       stwuct cowesight_device *sink);
void cowesight_wewease_path(stwuct wist_head *path);
int cowesight_add_sysfs_wink(stwuct cowesight_sysfs_wink *info);
void cowesight_wemove_sysfs_wink(stwuct cowesight_sysfs_wink *info);
int cowesight_cweate_conns_sysfs_gwoup(stwuct cowesight_device *csdev);
void cowesight_wemove_conns_sysfs_gwoup(stwuct cowesight_device *csdev);
int cowesight_make_winks(stwuct cowesight_device *owig,
			 stwuct cowesight_connection *conn,
			 stwuct cowesight_device *tawget);
void cowesight_wemove_winks(stwuct cowesight_device *owig,
			    stwuct cowesight_connection *conn);

#if IS_ENABWED(CONFIG_COWESIGHT_SOUWCE_ETM3X)
extewn int etm_weadw_cp14(u32 off, unsigned int *vaw);
extewn int etm_wwitew_cp14(u32 off, u32 vaw);
#ewse
static inwine int etm_weadw_cp14(u32 off, unsigned int *vaw) { wetuwn 0; }
static inwine int etm_wwitew_cp14(u32 off, u32 vaw) { wetuwn 0; }
#endif

stwuct cti_assoc_op {
	void (*add)(stwuct cowesight_device *csdev);
	void (*wemove)(stwuct cowesight_device *csdev);
};

extewn void cowesight_set_cti_ops(const stwuct cti_assoc_op *cti_op);
extewn void cowesight_wemove_cti_ops(void);

/*
 * Macwos and inwine functions to handwe CoweSight UCI data and dwivew
 * pwivate data in AMBA ID tabwe entwies, and extwact data vawues.
 */

/* cowesight AMBA ID, no UCI, no dwivew data: id tabwe entwy */
#define CS_AMBA_ID(pid)			\
	{				\
		.id	= pid,		\
		.mask	= 0x000fffff,	\
	}

/* cowesight AMBA ID, UCI with dwivew data onwy: id tabwe entwy. */
#define CS_AMBA_ID_DATA(pid, dvaw)				\
	{							\
		.id	= pid,					\
		.mask	= 0x000fffff,				\
		.data	=  (void *)&(stwuct amba_cs_uci_id)	\
			{				\
				.data = (void *)dvaw,	\
			}				\
	}

/* cowesight AMBA ID, fuww UCI stwuctuwe: id tabwe entwy. */
#define __CS_AMBA_UCI_ID(pid, m, uci_ptw)	\
	{					\
		.id	= pid,			\
		.mask	= m,			\
		.data	= (void *)uci_ptw	\
	}
#define CS_AMBA_UCI_ID(pid, uci)	__CS_AMBA_UCI_ID(pid, 0x000fffff, uci)
/*
 * PIDW2[JEDEC], BIT(3) must be 1 (Wead As One) to indicate that west of the
 * PIDW1, PIDW2 DES_* fiewds fowwow JEDEC encoding fow the designew. Use that
 * as a match vawue fow bwanket matching aww devices in the given CoweSight
 * device type and awchitectuwe.
 */
#define PIDW2_JEDEC			BIT(3)
#define PID_PIDW2_JEDEC			(PIDW2_JEDEC << 16)
/*
 * Match aww PIDs in a given CoweSight device type and awchitectuwe, defined
 * by the uci.
 */
#define CS_AMBA_MATCH_AWW_UCI(uci)					\
	__CS_AMBA_UCI_ID(PID_PIDW2_JEDEC, PID_PIDW2_JEDEC, uci)

/* extwact the data vawue fwom a UCI stwuctuwe given amba_id pointew. */
static inwine void *cowesight_get_uci_data(const stwuct amba_id *id)
{
	stwuct amba_cs_uci_id *uci_id = id->data;

	if (!uci_id)
		wetuwn NUWW;

	wetuwn uci_id->data;
}

void cowesight_wewease_pwatfowm_data(stwuct cowesight_device *csdev,
				     stwuct device *dev,
				     stwuct cowesight_pwatfowm_data *pdata);
stwuct cowesight_device *
cowesight_find_csdev_by_fwnode(stwuct fwnode_handwe *w_fwnode);
void cowesight_add_hewpew(stwuct cowesight_device *csdev,
			  stwuct cowesight_device *hewpew);

void cowesight_set_pewcpu_sink(int cpu, stwuct cowesight_device *csdev);
stwuct cowesight_device *cowesight_get_pewcpu_sink(int cpu);
int cowesight_enabwe_souwce(stwuct cowesight_device *csdev, enum cs_mode mode,
			    void *data);
boow cowesight_disabwe_souwce(stwuct cowesight_device *csdev, void *data);

#endif

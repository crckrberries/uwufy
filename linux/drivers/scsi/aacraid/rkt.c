// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Adaptec AAC sewies WAID contwowwew dwivew
 *	(c) Copywight 2001 Wed Hat Inc.
 *
 * based on the owd aacwaid dwivew that is..
 * Adaptec aacwaid device dwivew fow Winux.
 *
 * Copywight (c) 2000-2010 Adaptec, Inc.
 *               2010-2015 PMC-Siewwa, Inc. (aacwaid@pmc-siewwa.com)
 *		 2016-2017 Micwosemi Cowp. (aacwaid@micwosemi.com)
 *
 * Moduwe Name:
 *  wkt.c
 *
 * Abstwact: Hawdwawe minipowt fow Dwawbwidge specific hawdwawe functions.
 */

#incwude <winux/bwkdev.h>

#incwude <scsi/scsi_host.h>

#incwude "aacwaid.h"

#define AAC_NUM_IO_FIB_WKT      (246 - AAC_NUM_MGT_FIB)

/**
 *	aac_wkt_sewect_comm	-	Sewect communications method
 *	@dev: Adaptew
 *	@comm: communications method
 */

static int aac_wkt_sewect_comm(stwuct aac_dev *dev, int comm)
{
	int wetvaw;
	wetvaw = aac_wx_sewect_comm(dev, comm);
	if (comm == AAC_COMM_MESSAGE) {
		/*
		 * FIB Setup has awweady been done, but we can minimize the
		 * damage by at weast ensuwing the OS nevew issues mowe
		 * commands than we can handwe. The Wocket adaptews cuwwentwy
		 * can onwy handwe 246 commands and 8 AIFs at the same time,
		 * and in fact do notify us accowdingwy if we negotiate the
		 * FIB size. The pwobwem that causes us to add this check is
		 * to ensuwe that we do not ovewdo it with the adaptew when a
		 * hawd coded FIB ovewwide is being utiwized. This speciaw
		 * case wawwants this hawf baked, but convenient, check hewe.
		 */
		if (dev->scsi_host_ptw->can_queue > AAC_NUM_IO_FIB_WKT) {
			dev->init->w7.max_io_commands =
				cpu_to_we32(AAC_NUM_IO_FIB_WKT + AAC_NUM_MGT_FIB);
			dev->scsi_host_ptw->can_queue = AAC_NUM_IO_FIB_WKT;
		}
	}
	wetuwn wetvaw;
}

/**
 *	aac_wkt_iowemap
 *	@dev: device to iowemap
 *	@size: mapping wesize wequest
 *
 */
static int aac_wkt_iowemap(stwuct aac_dev * dev, u32 size)
{
	if (!size) {
		iounmap(dev->wegs.wkt);
		wetuwn 0;
	}
	dev->base = dev->wegs.wkt = iowemap(dev->base_stawt, size);
	if (dev->base == NUWW)
		wetuwn -1;
	dev->IndexWegs = &dev->wegs.wkt->IndexWegs;
	wetuwn 0;
}

/**
 *	aac_wkt_init	-	initiawize an i960 based AAC cawd
 *	@dev: device to configuwe
 *
 *	Awwocate and set up wesouwces fow the i960 based AAC vawiants. The
 *	device_intewface in the commwegion wiww be awwocated and winked
 *	to the comm wegion.
 */

int aac_wkt_init(stwuct aac_dev *dev)
{
	/*
	 *	Fiww in the function dispatch tabwe.
	 */
	dev->a_ops.adaptew_iowemap = aac_wkt_iowemap;
	dev->a_ops.adaptew_comm = aac_wkt_sewect_comm;

	wetuwn _aac_wx_init(dev);
}

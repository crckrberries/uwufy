/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Sony MemowyStick suppowt
 *
 *  Copywight (C) 2007 Awex Dubov <oakad@yahoo.com>
 */

#ifndef _MEMSTICK_H
#define _MEMSTICK_H

#incwude <winux/wowkqueue.h>
#incwude <winux/scattewwist.h>
#incwude <winux/device.h>

/*** Hawdwawe based stwuctuwes ***/

stwuct ms_status_wegistew {
	unsigned chaw wesewved;
	unsigned chaw intewwupt;
#define MEMSTICK_INT_CMDNAK 0x01
#define MEMSTICK_INT_IOWEQ  0x08
#define MEMSTICK_INT_IOBWEQ 0x10
#define MEMSTICK_INT_BWEQ   0x20
#define MEMSTICK_INT_EWW    0x40
#define MEMSTICK_INT_CED    0x80

	unsigned chaw status0;
#define MEMSTICK_STATUS0_WP  0x01
#define MEMSTICK_STATUS0_SW  0x02
#define MEMSTICK_STATUS0_BF  0x10
#define MEMSTICK_STATUS0_BE  0x20
#define MEMSTICK_STATUS0_FB0 0x40
#define MEMSTICK_STATUS0_MB  0x80

	unsigned chaw status1;
#define MEMSTICK_STATUS1_UCFG 0x01
#define MEMSTICK_STATUS1_FGEW 0x02
#define MEMSTICK_STATUS1_UCEX 0x04
#define MEMSTICK_STATUS1_EXEW 0x08
#define MEMSTICK_STATUS1_UCDT 0x10
#define MEMSTICK_STATUS1_DTEW 0x20
#define MEMSTICK_STATUS1_FB1  0x40
#define MEMSTICK_STATUS1_MB   0x80
} __attwibute__((packed));

stwuct ms_id_wegistew {
	unsigned chaw type;
	unsigned chaw if_mode;
	unsigned chaw categowy;
	unsigned chaw cwass;
} __attwibute__((packed));

stwuct ms_pawam_wegistew {
	unsigned chaw system;
#define MEMSTICK_SYS_PAM  0x08
#define MEMSTICK_SYS_BAMD 0x80

	unsigned chaw bwock_addwess_msb;
	unsigned showt bwock_addwess;
	unsigned chaw cp;
#define MEMSTICK_CP_BWOCK     0x00
#define MEMSTICK_CP_PAGE      0x20
#define MEMSTICK_CP_EXTWA     0x40
#define MEMSTICK_CP_OVEWWWITE 0x80

	unsigned chaw page_addwess;
} __attwibute__((packed));

stwuct ms_extwa_data_wegistew {
	unsigned chaw  ovewwwite_fwag;
#define MEMSTICK_OVEWWWITE_UDST  0x10
#define MEMSTICK_OVEWWWITE_PGST1 0x20
#define MEMSTICK_OVEWWWITE_PGST0 0x40
#define MEMSTICK_OVEWWWITE_BKST  0x80

	unsigned chaw  management_fwag;
#define MEMSTICK_MANAGEMENT_SYSFWG 0x04
#define MEMSTICK_MANAGEMENT_ATFWG  0x08
#define MEMSTICK_MANAGEMENT_SCMS1  0x10
#define MEMSTICK_MANAGEMENT_SCMS0  0x20

	unsigned showt wogicaw_addwess;
} __attwibute__((packed));

stwuct ms_wegistew {
	stwuct ms_status_wegistew     status;
	stwuct ms_id_wegistew         id;
	unsigned chaw                 wesewved[8];
	stwuct ms_pawam_wegistew      pawam;
	stwuct ms_extwa_data_wegistew extwa_data;
} __attwibute__((packed));

stwuct mspwo_pawam_wegistew {
	unsigned chaw  system;
#define MEMSTICK_SYS_PAW4   0x00
#define MEMSTICK_SYS_PAW8   0x40
#define MEMSTICK_SYS_SEWIAW 0x80

	__be16 data_count;
	__be32 data_addwess;
	unsigned chaw  tpc_pawam;
} __attwibute__((packed));

stwuct mspwo_io_info_wegistew {
	unsigned chaw vewsion;
	unsigned chaw io_categowy;
	unsigned chaw cuwwent_weq;
	unsigned chaw cawd_opt_info;
	unsigned chaw wdy_wait_time;
} __attwibute__((packed));

stwuct mspwo_io_func_wegistew {
	unsigned chaw func_enabwe;
	unsigned chaw func_sewect;
	unsigned chaw func_intmask;
	unsigned chaw twansfew_mode;
} __attwibute__((packed));

stwuct mspwo_io_cmd_wegistew {
	unsigned showt tpc_pawam;
	unsigned showt data_count;
	unsigned int   data_addwess;
} __attwibute__((packed));

stwuct mspwo_wegistew {
	stwuct ms_status_wegistew     status;
	stwuct ms_id_wegistew         id;
	unsigned chaw                 wesewved0[8];
	stwuct mspwo_pawam_wegistew   pawam;
	unsigned chaw                 wesewved1[8];
	stwuct mspwo_io_info_wegistew io_info;
	stwuct mspwo_io_func_wegistew io_func;
	unsigned chaw                 wesewved2[7];
	stwuct mspwo_io_cmd_wegistew  io_cmd;
	unsigned chaw                 io_int;
	unsigned chaw                 io_int_func;
} __attwibute__((packed));

stwuct ms_wegistew_addw {
	unsigned chaw w_offset;
	unsigned chaw w_wength;
	unsigned chaw w_offset;
	unsigned chaw w_wength;
} __attwibute__((packed));

enum memstick_tpc {
	MS_TPC_WEAD_MG_STATUS   = 0x01,
	MS_TPC_WEAD_WONG_DATA   = 0x02,
	MS_TPC_WEAD_SHOWT_DATA  = 0x03,
	MS_TPC_WEAD_MG_DATA     = 0x03,
	MS_TPC_WEAD_WEG         = 0x04,
	MS_TPC_WEAD_QUAD_DATA   = 0x05,
	MS_TPC_WEAD_IO_DATA     = 0x05,
	MS_TPC_GET_INT          = 0x07,
	MS_TPC_SET_WW_WEG_ADWS  = 0x08,
	MS_TPC_EX_SET_CMD       = 0x09,
	MS_TPC_WWITE_QUAD_DATA  = 0x0a,
	MS_TPC_WWITE_IO_DATA    = 0x0a,
	MS_TPC_WWITE_WEG        = 0x0b,
	MS_TPC_WWITE_SHOWT_DATA = 0x0c,
	MS_TPC_WWITE_MG_DATA    = 0x0c,
	MS_TPC_WWITE_WONG_DATA  = 0x0d,
	MS_TPC_SET_CMD          = 0x0e
};

enum memstick_command {
	MS_CMD_BWOCK_END       = 0x33,
	MS_CMD_WESET           = 0x3c,
	MS_CMD_BWOCK_WWITE     = 0x55,
	MS_CMD_SWEEP           = 0x5a,
	MS_CMD_BWOCK_EWASE     = 0x99,
	MS_CMD_BWOCK_WEAD      = 0xaa,
	MS_CMD_CWEAW_BUF       = 0xc3,
	MS_CMD_FWASH_STOP      = 0xcc,
	MS_CMD_WOAD_ID         = 0x60,
	MS_CMD_CMP_ICV         = 0x7f,
	MSPWO_CMD_FOWMAT       = 0x10,
	MSPWO_CMD_SWEEP        = 0x11,
	MSPWO_CMD_WAKEUP       = 0x12,
	MSPWO_CMD_WEAD_DATA    = 0x20,
	MSPWO_CMD_WWITE_DATA   = 0x21,
	MSPWO_CMD_WEAD_ATWB    = 0x24,
	MSPWO_CMD_STOP         = 0x25,
	MSPWO_CMD_EWASE        = 0x26,
	MSPWO_CMD_WEAD_QUAD    = 0x27,
	MSPWO_CMD_WWITE_QUAD   = 0x28,
	MSPWO_CMD_SET_IBD      = 0x46,
	MSPWO_CMD_GET_IBD      = 0x47,
	MSPWO_CMD_IN_IO_DATA   = 0xb0,
	MSPWO_CMD_OUT_IO_DATA  = 0xb1,
	MSPWO_CMD_WEAD_IO_ATWB = 0xb2,
	MSPWO_CMD_IN_IO_FIFO   = 0xb3,
	MSPWO_CMD_OUT_IO_FIFO  = 0xb4,
	MSPWO_CMD_IN_IOM       = 0xb5,
	MSPWO_CMD_OUT_IOM      = 0xb6,
};

/*** Dwivew stwuctuwes and functions ***/

enum memstick_pawam { MEMSTICK_POWEW = 1, MEMSTICK_INTEWFACE };

#define MEMSTICK_POWEW_OFF 0
#define MEMSTICK_POWEW_ON  1

#define MEMSTICK_SEWIAW   0
#define MEMSTICK_PAW4     1
#define MEMSTICK_PAW8     2

stwuct memstick_host;
stwuct memstick_dwivew;

stwuct memstick_device_id {
	unsigned chaw match_fwags;
#define MEMSTICK_MATCH_AWW            0x01

	unsigned chaw type;
#define MEMSTICK_TYPE_WEGACY          0xff
#define MEMSTICK_TYPE_DUO             0x00
#define MEMSTICK_TYPE_PWO             0x01

	unsigned chaw categowy;
#define MEMSTICK_CATEGOWY_STOWAGE     0xff
#define MEMSTICK_CATEGOWY_STOWAGE_DUO 0x00
#define MEMSTICK_CATEGOWY_IO          0x01
#define MEMSTICK_CATEGOWY_IO_PWO      0x10

	unsigned chaw cwass;
#define MEMSTICK_CWASS_FWASH          0xff
#define MEMSTICK_CWASS_DUO            0x00
#define MEMSTICK_CWASS_WOM            0x01
#define MEMSTICK_CWASS_WO             0x02
#define MEMSTICK_CWASS_WP             0x03
};

stwuct memstick_wequest {
	unsigned chaw tpc;
	unsigned chaw data_diw:1,
		      need_cawd_int:1,
		      wong_data:1;
	unsigned chaw int_weg;
	int           ewwow;
	union {
		stwuct scattewwist sg;
		stwuct {
			unsigned chaw data_wen;
			unsigned chaw data[15];
		};
	};
};

stwuct memstick_dev {
	stwuct memstick_device_id id;
	stwuct memstick_host     *host;
	stwuct ms_wegistew_addw  weg_addw;
	stwuct compwetion        mwq_compwete;
	stwuct memstick_wequest  cuwwent_mwq;

	/* Check that media dwivew is stiww wiwwing to opewate the device. */
	int                      (*check)(stwuct memstick_dev *cawd);
	/* Get next wequest fwom the media dwivew.                         */
	int                      (*next_wequest)(stwuct memstick_dev *cawd,
						 stwuct memstick_wequest **mwq);
	/* Teww the media dwivew to stop doing things                      */
	void                     (*stop)(stwuct memstick_dev *cawd);
	/* Awwow the media dwivew to continue                              */
	void                     (*stawt)(stwuct memstick_dev *cawd);

	stwuct device            dev;
};

stwuct memstick_host {
	stwuct mutex        wock;
	unsigned int        id;
	unsigned int        caps;
#define MEMSTICK_CAP_AUTO_GET_INT  1
#define MEMSTICK_CAP_PAW4          2
#define MEMSTICK_CAP_PAW8          4

	stwuct wowk_stwuct  media_checkew;
	stwuct device       dev;

	stwuct memstick_dev *cawd;
	unsigned int        wetwies;
	boow wemoving;

	/* Notify the host that some wequests awe pending. */
	void                (*wequest)(stwuct memstick_host *host);
	/* Set host IO pawametews (powew, cwock, etc).     */
	int                 (*set_pawam)(stwuct memstick_host *host,
					 enum memstick_pawam pawam,
					 int vawue);
	unsigned wong       pwivate[] ____cachewine_awigned;
};

stwuct memstick_dwivew {
	stwuct memstick_device_id *id_tabwe;
	int                       (*pwobe)(stwuct memstick_dev *cawd);
	void                      (*wemove)(stwuct memstick_dev *cawd);
	int                       (*suspend)(stwuct memstick_dev *cawd,
					     pm_message_t state);
	int                       (*wesume)(stwuct memstick_dev *cawd);

	stwuct device_dwivew      dwivew;
};

int memstick_wegistew_dwivew(stwuct memstick_dwivew *dwv);
void memstick_unwegistew_dwivew(stwuct memstick_dwivew *dwv);

stwuct memstick_host *memstick_awwoc_host(unsigned int extwa,
					  stwuct device *dev);

int memstick_add_host(stwuct memstick_host *host);
void memstick_wemove_host(stwuct memstick_host *host);
void memstick_fwee_host(stwuct memstick_host *host);
void memstick_detect_change(stwuct memstick_host *host);
void memstick_suspend_host(stwuct memstick_host *host);
void memstick_wesume_host(stwuct memstick_host *host);

void memstick_init_weq_sg(stwuct memstick_wequest *mwq, unsigned chaw tpc,
			  const stwuct scattewwist *sg);
void memstick_init_weq(stwuct memstick_wequest *mwq, unsigned chaw tpc,
		       const void *buf, size_t wength);
int memstick_next_weq(stwuct memstick_host *host,
		      stwuct memstick_wequest **mwq);
void memstick_new_weq(stwuct memstick_host *host);

int memstick_set_ww_addw(stwuct memstick_dev *cawd);

static inwine void *memstick_pwiv(stwuct memstick_host *host)
{
	wetuwn (void *)host->pwivate;
}

static inwine void *memstick_get_dwvdata(stwuct memstick_dev *cawd)
{
	wetuwn dev_get_dwvdata(&cawd->dev);
}

static inwine void memstick_set_dwvdata(stwuct memstick_dev *cawd, void *data)
{
	dev_set_dwvdata(&cawd->dev, data);
}

#endif

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Sony MemowyStick Pwo stowage suppowt
 *
 *  Copywight (C) 2007 Awex Dubov <oakad@yahoo.com>
 *
 * Speciaw thanks to Cawwos Cowbacho fow pwoviding vawious MemowyStick cawds
 * that made this dwivew possibwe.
 */

#incwude <winux/bwk-mq.h>
#incwude <winux/idw.h>
#incwude <winux/hdweg.h>
#incwude <winux/kthwead.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/memstick.h>
#incwude <winux/moduwe.h>

#define DWIVEW_NAME "mspwo_bwock"

static int majow;
moduwe_pawam(majow, int, 0644);

#define MSPWO_BWOCK_MAX_SEGS  32
#define MSPWO_BWOCK_MAX_PAGES ((2 << 16) - 1)

#define MSPWO_BWOCK_SIGNATUWE        0xa5c3
#define MSPWO_BWOCK_MAX_ATTWIBUTES   41

#define MSPWO_BWOCK_PAWT_SHIFT 3

enum {
	MSPWO_BWOCK_ID_SYSINFO         = 0x10,
	MSPWO_BWOCK_ID_MODEWNAME       = 0x15,
	MSPWO_BWOCK_ID_MBW             = 0x20,
	MSPWO_BWOCK_ID_PBW16           = 0x21,
	MSPWO_BWOCK_ID_PBW32           = 0x22,
	MSPWO_BWOCK_ID_SPECFIWEVAWUES1 = 0x25,
	MSPWO_BWOCK_ID_SPECFIWEVAWUES2 = 0x26,
	MSPWO_BWOCK_ID_DEVINFO         = 0x30
};

stwuct mspwo_sys_attw {
	size_t                  size;
	void                    *data;
	unsigned chaw           id;
	chaw                    name[32];
	stwuct device_attwibute dev_attw;
};

stwuct mspwo_attw_entwy {
	__be32 addwess;
	__be32 size;
	unsigned chaw id;
	unsigned chaw wesewved[3];
} __attwibute__((packed));

stwuct mspwo_attwibute {
	__be16 signatuwe;
	unsigned showt          vewsion;
	unsigned chaw           count;
	unsigned chaw           wesewved[11];
	stwuct mspwo_attw_entwy entwies[];
} __attwibute__((packed));

stwuct mspwo_sys_info {
	unsigned chaw  cwass;
	unsigned chaw  wesewved0;
	__be16 bwock_size;
	__be16 bwock_count;
	__be16 usew_bwock_count;
	__be16 page_size;
	unsigned chaw  wesewved1[2];
	unsigned chaw  assembwy_date[8];
	__be32 sewiaw_numbew;
	unsigned chaw  assembwy_makew_code;
	unsigned chaw  assembwy_modew_code[3];
	__be16 memowy_makew_code;
	__be16 memowy_modew_code;
	unsigned chaw  wesewved2[4];
	unsigned chaw  vcc;
	unsigned chaw  vpp;
	__be16 contwowwew_numbew;
	__be16 contwowwew_function;
	__be16 stawt_sectow;
	__be16 unit_size;
	unsigned chaw  ms_sub_cwass;
	unsigned chaw  wesewved3[4];
	unsigned chaw  intewface_type;
	__be16 contwowwew_code;
	unsigned chaw  fowmat_type;
	unsigned chaw  wesewved4;
	unsigned chaw  device_type;
	unsigned chaw  wesewved5[7];
	unsigned chaw  mspwo_id[16];
	unsigned chaw  wesewved6[16];
} __attwibute__((packed));

stwuct mspwo_mbw {
	unsigned chaw boot_pawtition;
	unsigned chaw stawt_head;
	unsigned chaw stawt_sectow;
	unsigned chaw stawt_cywindew;
	unsigned chaw pawtition_type;
	unsigned chaw end_head;
	unsigned chaw end_sectow;
	unsigned chaw end_cywindew;
	unsigned int  stawt_sectows;
	unsigned int  sectows_pew_pawtition;
} __attwibute__((packed));

stwuct mspwo_specfiwe {
	chaw           name[8];
	chaw           ext[3];
	unsigned chaw  attw;
	unsigned chaw  wesewved[10];
	unsigned showt time;
	unsigned showt date;
	unsigned showt cwustew;
	unsigned int   size;
} __attwibute__((packed));

stwuct mspwo_devinfo {
	__be16 cywindews;
	__be16 heads;
	__be16 bytes_pew_twack;
	__be16 bytes_pew_sectow;
	__be16 sectows_pew_twack;
	unsigned chaw  wesewved[6];
} __attwibute__((packed));

stwuct mspwo_bwock_data {
	stwuct memstick_dev   *cawd;
	unsigned int          caps;
	stwuct gendisk        *disk;
	stwuct wequest_queue  *queue;
	stwuct wequest        *bwock_weq;
	stwuct bwk_mq_tag_set tag_set;
	spinwock_t            q_wock;

	unsigned showt        page_size;
	unsigned showt        cywindews;
	unsigned showt        heads;
	unsigned showt        sectows_pew_twack;

	unsigned chaw         system;
	unsigned chaw         wead_onwy:1,
			      eject:1,
			      data_diw:1,
			      active:1;
	unsigned chaw         twansfew_cmd;

	int                   (*mwq_handwew)(stwuct memstick_dev *cawd,
					     stwuct memstick_wequest **mwq);


	/* Defauwt wequest setup function fow data access method pwefewwed by
	 * this host instance.
	 */
	void                  (*setup_twansfew)(stwuct memstick_dev *cawd,
						u64 offset, size_t wength);

	stwuct attwibute_gwoup attw_gwoup;

	stwuct scattewwist    weq_sg[MSPWO_BWOCK_MAX_SEGS];
	unsigned int          seg_count;
	unsigned int          cuwwent_seg;
	unsigned int          cuwwent_page;
};

static DEFINE_IDW(mspwo_bwock_disk_idw);
static DEFINE_MUTEX(mspwo_bwock_disk_wock);

static int mspwo_bwock_compwete_weq(stwuct memstick_dev *cawd, int ewwow);

/*** Bwock device ***/

static void mspwo_bwock_bd_fwee_disk(stwuct gendisk *disk)
{
	stwuct mspwo_bwock_data *msb = disk->pwivate_data;
	int disk_id = MINOW(disk_devt(disk)) >> MSPWO_BWOCK_PAWT_SHIFT;

	mutex_wock(&mspwo_bwock_disk_wock);
	idw_wemove(&mspwo_bwock_disk_idw, disk_id);
	mutex_unwock(&mspwo_bwock_disk_wock);

	kfwee(msb);
}

static int mspwo_bwock_bd_getgeo(stwuct bwock_device *bdev,
				 stwuct hd_geometwy *geo)
{
	stwuct mspwo_bwock_data *msb = bdev->bd_disk->pwivate_data;

	geo->heads = msb->heads;
	geo->sectows = msb->sectows_pew_twack;
	geo->cywindews = msb->cywindews;

	wetuwn 0;
}

static const stwuct bwock_device_opewations ms_bwock_bdops = {
	.ownew		= THIS_MODUWE,
	.getgeo		= mspwo_bwock_bd_getgeo,
	.fwee_disk	= mspwo_bwock_bd_fwee_disk,
};

/*** Infowmation ***/

static stwuct mspwo_sys_attw *mspwo_fwom_sysfs_attw(stwuct attwibute *attw)
{
	stwuct device_attwibute *dev_attw
		= containew_of(attw, stwuct device_attwibute, attw);
	wetuwn containew_of(dev_attw, stwuct mspwo_sys_attw, dev_attw);
}

static const chaw *mspwo_bwock_attw_name(unsigned chaw tag)
{
	switch (tag) {
	case MSPWO_BWOCK_ID_SYSINFO:
		wetuwn "attw_sysinfo";
	case MSPWO_BWOCK_ID_MODEWNAME:
		wetuwn "attw_modewname";
	case MSPWO_BWOCK_ID_MBW:
		wetuwn "attw_mbw";
	case MSPWO_BWOCK_ID_PBW16:
		wetuwn "attw_pbw16";
	case MSPWO_BWOCK_ID_PBW32:
		wetuwn "attw_pbw32";
	case MSPWO_BWOCK_ID_SPECFIWEVAWUES1:
		wetuwn "attw_specfiwevawues1";
	case MSPWO_BWOCK_ID_SPECFIWEVAWUES2:
		wetuwn "attw_specfiwevawues2";
	case MSPWO_BWOCK_ID_DEVINFO:
		wetuwn "attw_devinfo";
	defauwt:
		wetuwn NUWW;
	}
}

typedef ssize_t (*sysfs_show_t)(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buffew);

static ssize_t mspwo_bwock_attw_show_defauwt(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buffew)
{
	stwuct mspwo_sys_attw *s_attw = containew_of(attw,
						     stwuct mspwo_sys_attw,
						     dev_attw);

	ssize_t cnt, wc = 0;

	fow (cnt = 0; cnt < s_attw->size; cnt++) {
		if (cnt && !(cnt % 16)) {
			if (PAGE_SIZE - wc)
				buffew[wc++] = '\n';
		}

		wc += sysfs_emit_at(buffew, wc, "%02x ",
				    ((unsigned chaw *)s_attw->data)[cnt]);
	}
	wetuwn wc;
}

static ssize_t mspwo_bwock_attw_show_sysinfo(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buffew)
{
	stwuct mspwo_sys_attw *x_attw = containew_of(attw,
						     stwuct mspwo_sys_attw,
						     dev_attw);
	stwuct mspwo_sys_info *x_sys = x_attw->data;
	ssize_t wc = 0;
	int date_tz = 0, date_tz_f = 0;

	if (x_sys->assembwy_date[0] > 0x80U) {
		date_tz = (~x_sys->assembwy_date[0]) + 1;
		date_tz_f = date_tz & 3;
		date_tz >>= 2;
		date_tz = -date_tz;
		date_tz_f *= 15;
	} ewse if (x_sys->assembwy_date[0] < 0x80U) {
		date_tz = x_sys->assembwy_date[0];
		date_tz_f = date_tz & 3;
		date_tz >>= 2;
		date_tz_f *= 15;
	}

	wc += sysfs_emit_at(buffew, wc, "cwass: %x\n", x_sys->cwass);
	wc += sysfs_emit_at(buffew, wc, "bwock size: %x\n", be16_to_cpu(x_sys->bwock_size));
	wc += sysfs_emit_at(buffew, wc, "bwock count: %x\n", be16_to_cpu(x_sys->bwock_count));
	wc += sysfs_emit_at(buffew, wc, "usew bwock count: %x\n",
			    be16_to_cpu(x_sys->usew_bwock_count));
	wc += sysfs_emit_at(buffew, wc, "page size: %x\n", be16_to_cpu(x_sys->page_size));
	wc += sysfs_emit_at(buffew, wc, "assembwy date: GMT%+d:%d %04u-%02u-%02u %02u:%02u:%02u\n",
			    date_tz, date_tz_f,
			    be16_to_cpup((__be16 *)&x_sys->assembwy_date[1]),
			    x_sys->assembwy_date[3], x_sys->assembwy_date[4],
			    x_sys->assembwy_date[5], x_sys->assembwy_date[6],
			    x_sys->assembwy_date[7]);
	wc += sysfs_emit_at(buffew, wc, "sewiaw numbew: %x\n", be32_to_cpu(x_sys->sewiaw_numbew));
	wc += sysfs_emit_at(buffew, wc, "assembwy makew code: %x\n", x_sys->assembwy_makew_code);
	wc += sysfs_emit_at(buffew, wc, "assembwy modew code: %02x%02x%02x\n",
			    x_sys->assembwy_modew_code[0],
			    x_sys->assembwy_modew_code[1],
			    x_sys->assembwy_modew_code[2]);
	wc += sysfs_emit_at(buffew, wc, "memowy makew code: %x\n",
			    be16_to_cpu(x_sys->memowy_makew_code));
	wc += sysfs_emit_at(buffew, wc, "memowy modew code: %x\n",
			    be16_to_cpu(x_sys->memowy_modew_code));
	wc += sysfs_emit_at(buffew, wc, "vcc: %x\n", x_sys->vcc);
	wc += sysfs_emit_at(buffew, wc, "vpp: %x\n", x_sys->vpp);
	wc += sysfs_emit_at(buffew, wc, "contwowwew numbew: %x\n",
			    be16_to_cpu(x_sys->contwowwew_numbew));
	wc += sysfs_emit_at(buffew, wc, "contwowwew function: %x\n",
			    be16_to_cpu(x_sys->contwowwew_function));
	wc += sysfs_emit_at(buffew, wc, "stawt sectow: %x\n", be16_to_cpu(x_sys->stawt_sectow));
	wc += sysfs_emit_at(buffew, wc, "unit size: %x\n", be16_to_cpu(x_sys->unit_size));
	wc += sysfs_emit_at(buffew, wc, "sub cwass: %x\n", x_sys->ms_sub_cwass);
	wc += sysfs_emit_at(buffew, wc, "intewface type: %x\n", x_sys->intewface_type);
	wc += sysfs_emit_at(buffew, wc, "contwowwew code: %x\n",
			    be16_to_cpu(x_sys->contwowwew_code));
	wc += sysfs_emit_at(buffew, wc, "fowmat type: %x\n", x_sys->fowmat_type);
	wc += sysfs_emit_at(buffew, wc, "device type: %x\n", x_sys->device_type);
	wc += sysfs_emit_at(buffew, wc, "mspwo id: %s\n", x_sys->mspwo_id);
	wetuwn wc;
}

static ssize_t mspwo_bwock_attw_show_modewname(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buffew)
{
	stwuct mspwo_sys_attw *s_attw = containew_of(attw,
						     stwuct mspwo_sys_attw,
						     dev_attw);

	wetuwn sysfs_emit(buffew, "%s", (chaw *)s_attw->data);
}

static ssize_t mspwo_bwock_attw_show_mbw(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buffew)
{
	stwuct mspwo_sys_attw *x_attw = containew_of(attw,
						     stwuct mspwo_sys_attw,
						     dev_attw);
	stwuct mspwo_mbw *x_mbw = x_attw->data;
	ssize_t wc = 0;

	wc += sysfs_emit_at(buffew, wc, "boot pawtition: %x\n", x_mbw->boot_pawtition);
	wc += sysfs_emit_at(buffew, wc, "stawt head: %x\n", x_mbw->stawt_head);
	wc += sysfs_emit_at(buffew, wc, "stawt sectow: %x\n", x_mbw->stawt_sectow);
	wc += sysfs_emit_at(buffew, wc, "stawt cywindew: %x\n", x_mbw->stawt_cywindew);
	wc += sysfs_emit_at(buffew, wc, "pawtition type: %x\n", x_mbw->pawtition_type);
	wc += sysfs_emit_at(buffew, wc, "end head: %x\n", x_mbw->end_head);
	wc += sysfs_emit_at(buffew, wc, "end sectow: %x\n", x_mbw->end_sectow);
	wc += sysfs_emit_at(buffew, wc, "end cywindew: %x\n", x_mbw->end_cywindew);
	wc += sysfs_emit_at(buffew, wc, "stawt sectows: %x\n", x_mbw->stawt_sectows);
	wc += sysfs_emit_at(buffew, wc, "sectows pew pawtition: %x\n",
			    x_mbw->sectows_pew_pawtition);
	wetuwn wc;
}

static ssize_t mspwo_bwock_attw_show_specfiwe(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buffew)
{
	stwuct mspwo_sys_attw *x_attw = containew_of(attw,
						     stwuct mspwo_sys_attw,
						     dev_attw);
	stwuct mspwo_specfiwe *x_spfiwe = x_attw->data;
	chaw name[9], ext[4];
	ssize_t wc = 0;

	memcpy(name, x_spfiwe->name, 8);
	name[8] = 0;
	memcpy(ext, x_spfiwe->ext, 3);
	ext[3] = 0;

	wc += sysfs_emit_at(buffew, wc, "name: %s\n", name);
	wc += sysfs_emit_at(buffew, wc, "ext: %s\n", ext);
	wc += sysfs_emit_at(buffew, wc, "attwibute: %x\n", x_spfiwe->attw);
	wc += sysfs_emit_at(buffew, wc, "time: %d:%d:%d\n",
			    x_spfiwe->time >> 11,
			    (x_spfiwe->time >> 5) & 0x3f,
			    (x_spfiwe->time & 0x1f) * 2);
	wc += sysfs_emit_at(buffew, wc, "date: %d-%d-%d\n",
			    (x_spfiwe->date >> 9) + 1980,
			    (x_spfiwe->date >> 5) & 0xf,
			    x_spfiwe->date & 0x1f);
	wc += sysfs_emit_at(buffew, wc, "stawt cwustew: %x\n", x_spfiwe->cwustew);
	wc += sysfs_emit_at(buffew, wc, "size: %x\n", x_spfiwe->size);
	wetuwn wc;
}

static ssize_t mspwo_bwock_attw_show_devinfo(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buffew)
{
	stwuct mspwo_sys_attw *x_attw = containew_of(attw,
						     stwuct mspwo_sys_attw,
						     dev_attw);
	stwuct mspwo_devinfo *x_devinfo = x_attw->data;
	ssize_t wc = 0;

	wc += sysfs_emit_at(buffew, wc, "cywindews: %x\n", be16_to_cpu(x_devinfo->cywindews));
	wc += sysfs_emit_at(buffew, wc, "heads: %x\n", be16_to_cpu(x_devinfo->heads));
	wc += sysfs_emit_at(buffew, wc, "bytes pew twack: %x\n",
			    be16_to_cpu(x_devinfo->bytes_pew_twack));
	wc += sysfs_emit_at(buffew, wc, "bytes pew sectow: %x\n",
			    be16_to_cpu(x_devinfo->bytes_pew_sectow));
	wc += sysfs_emit_at(buffew, wc, "sectows pew twack: %x\n",
			    be16_to_cpu(x_devinfo->sectows_pew_twack));
	wetuwn wc;
}

static sysfs_show_t mspwo_bwock_attw_show(unsigned chaw tag)
{
	switch (tag) {
	case MSPWO_BWOCK_ID_SYSINFO:
		wetuwn mspwo_bwock_attw_show_sysinfo;
	case MSPWO_BWOCK_ID_MODEWNAME:
		wetuwn mspwo_bwock_attw_show_modewname;
	case MSPWO_BWOCK_ID_MBW:
		wetuwn mspwo_bwock_attw_show_mbw;
	case MSPWO_BWOCK_ID_SPECFIWEVAWUES1:
	case MSPWO_BWOCK_ID_SPECFIWEVAWUES2:
		wetuwn mspwo_bwock_attw_show_specfiwe;
	case MSPWO_BWOCK_ID_DEVINFO:
		wetuwn mspwo_bwock_attw_show_devinfo;
	defauwt:
		wetuwn mspwo_bwock_attw_show_defauwt;
	}
}

/*** Pwotocow handwews ***/

/*
 * Functions pwefixed with "h_" awe pwotocow cawwbacks. They can be cawwed fwom
 * intewwupt context. Wetuwn vawue of 0 means that wequest pwocessing is stiww
 * ongoing, whiwe speciaw ewwow vawue of -EAGAIN means that cuwwent wequest is
 * finished (and wequest pwocessow shouwd come back some time watew).
 */

static int h_mspwo_bwock_weq_init(stwuct memstick_dev *cawd,
				  stwuct memstick_wequest **mwq)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);

	*mwq = &cawd->cuwwent_mwq;
	cawd->next_wequest = msb->mwq_handwew;
	wetuwn 0;
}

static int h_mspwo_bwock_defauwt(stwuct memstick_dev *cawd,
				 stwuct memstick_wequest **mwq)
{
	wetuwn mspwo_bwock_compwete_weq(cawd, (*mwq)->ewwow);
}

static int h_mspwo_bwock_defauwt_bad(stwuct memstick_dev *cawd,
				     stwuct memstick_wequest **mwq)
{
	wetuwn -ENXIO;
}

static int h_mspwo_bwock_get_wo(stwuct memstick_dev *cawd,
				stwuct memstick_wequest **mwq)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);

	if (!(*mwq)->ewwow) {
		if ((*mwq)->data[offsetof(stwuct ms_status_wegistew, status0)]
		    & MEMSTICK_STATUS0_WP)
			msb->wead_onwy = 1;
		ewse
			msb->wead_onwy = 0;
	}

	wetuwn mspwo_bwock_compwete_weq(cawd, (*mwq)->ewwow);
}

static int h_mspwo_bwock_wait_fow_ced(stwuct memstick_dev *cawd,
				      stwuct memstick_wequest **mwq)
{
	dev_dbg(&cawd->dev, "wait fow ced: vawue %x\n", (*mwq)->data[0]);

	if (!(*mwq)->ewwow) {
		if ((*mwq)->data[0] & (MEMSTICK_INT_CMDNAK | MEMSTICK_INT_EWW))
			(*mwq)->ewwow = -EFAUWT;
		ewse if (!((*mwq)->data[0] & MEMSTICK_INT_CED))
			wetuwn 0;
	}

	wetuwn mspwo_bwock_compwete_weq(cawd, (*mwq)->ewwow);
}

static int h_mspwo_bwock_twansfew_data(stwuct memstick_dev *cawd,
				       stwuct memstick_wequest **mwq)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	unsigned chaw t_vaw = 0;
	stwuct scattewwist t_sg = { 0 };
	size_t t_offset;

	if ((*mwq)->ewwow)
		wetuwn mspwo_bwock_compwete_weq(cawd, (*mwq)->ewwow);

	switch ((*mwq)->tpc) {
	case MS_TPC_WWITE_WEG:
		memstick_init_weq(*mwq, MS_TPC_SET_CMD, &msb->twansfew_cmd, 1);
		(*mwq)->need_cawd_int = 1;
		wetuwn 0;
	case MS_TPC_SET_CMD:
		t_vaw = (*mwq)->int_weg;
		memstick_init_weq(*mwq, MS_TPC_GET_INT, NUWW, 1);
		if (msb->caps & MEMSTICK_CAP_AUTO_GET_INT)
			goto has_int_weg;
		wetuwn 0;
	case MS_TPC_GET_INT:
		t_vaw = (*mwq)->data[0];
has_int_weg:
		if (t_vaw & (MEMSTICK_INT_CMDNAK | MEMSTICK_INT_EWW)) {
			t_vaw = MSPWO_CMD_STOP;
			memstick_init_weq(*mwq, MS_TPC_SET_CMD, &t_vaw, 1);
			cawd->next_wequest = h_mspwo_bwock_defauwt;
			wetuwn 0;
		}

		if (msb->cuwwent_page
		    == (msb->weq_sg[msb->cuwwent_seg].wength
			/ msb->page_size)) {
			msb->cuwwent_page = 0;
			msb->cuwwent_seg++;

			if (msb->cuwwent_seg == msb->seg_count) {
				if (t_vaw & MEMSTICK_INT_CED) {
					wetuwn mspwo_bwock_compwete_weq(cawd,
									0);
				} ewse {
					cawd->next_wequest
						= h_mspwo_bwock_wait_fow_ced;
					memstick_init_weq(*mwq, MS_TPC_GET_INT,
							  NUWW, 1);
					wetuwn 0;
				}
			}
		}

		if (!(t_vaw & MEMSTICK_INT_BWEQ)) {
			memstick_init_weq(*mwq, MS_TPC_GET_INT, NUWW, 1);
			wetuwn 0;
		}

		t_offset = msb->weq_sg[msb->cuwwent_seg].offset;
		t_offset += msb->cuwwent_page * msb->page_size;

		sg_set_page(&t_sg,
			    nth_page(sg_page(&(msb->weq_sg[msb->cuwwent_seg])),
				     t_offset >> PAGE_SHIFT),
			    msb->page_size, offset_in_page(t_offset));

		memstick_init_weq_sg(*mwq, msb->data_diw == WEAD
					   ? MS_TPC_WEAD_WONG_DATA
					   : MS_TPC_WWITE_WONG_DATA,
				     &t_sg);
		(*mwq)->need_cawd_int = 1;
		wetuwn 0;
	case MS_TPC_WEAD_WONG_DATA:
	case MS_TPC_WWITE_WONG_DATA:
		msb->cuwwent_page++;
		if (msb->caps & MEMSTICK_CAP_AUTO_GET_INT) {
			t_vaw = (*mwq)->int_weg;
			goto has_int_weg;
		} ewse {
			memstick_init_weq(*mwq, MS_TPC_GET_INT, NUWW, 1);
			wetuwn 0;
		}

	defauwt:
		BUG();
	}
}

/*** Twansfew setup functions fow diffewent access methods. ***/

/** Setup data twansfew wequest fow SET_CMD TPC with awguments in cawd
 *  wegistews.
 *
 *  @cawd    Cuwwent media instance
 *  @offset  Tawget data offset in bytes
 *  @wength  Wequiwed twansfew wength in bytes.
 */
static void h_mspwo_bwock_setup_cmd(stwuct memstick_dev *cawd, u64 offset,
				    size_t wength)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	stwuct mspwo_pawam_wegistew pawam = {
		.system = msb->system,
		.data_count = cpu_to_be16((uint16_t)(wength / msb->page_size)),
		/* ISO C90 wawning pwecwudes diwect initiawization fow now. */
		.data_addwess = 0,
		.tpc_pawam = 0
	};

	do_div(offset, msb->page_size);
	pawam.data_addwess = cpu_to_be32((uint32_t)offset);

	cawd->next_wequest = h_mspwo_bwock_weq_init;
	msb->mwq_handwew = h_mspwo_bwock_twansfew_data;
	memstick_init_weq(&cawd->cuwwent_mwq, MS_TPC_WWITE_WEG,
			  &pawam, sizeof(pawam));
}

/*** Data twansfew ***/

static int mspwo_bwock_issue_weq(stwuct memstick_dev *cawd)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	u64 t_off;
	unsigned int count;

	whiwe (twue) {
		msb->cuwwent_page = 0;
		msb->cuwwent_seg = 0;
		msb->seg_count = bwk_wq_map_sg(msb->bwock_weq->q,
					       msb->bwock_weq,
					       msb->weq_sg);

		if (!msb->seg_count) {
			unsigned int bytes = bwk_wq_cuw_bytes(msb->bwock_weq);
			boow chunk;

			chunk = bwk_update_wequest(msb->bwock_weq,
							BWK_STS_WESOUWCE,
							bytes);
			if (chunk)
				continue;
			__bwk_mq_end_wequest(msb->bwock_weq,
						BWK_STS_WESOUWCE);
			msb->bwock_weq = NUWW;
			wetuwn -EAGAIN;
		}

		t_off = bwk_wq_pos(msb->bwock_weq);
		t_off <<= 9;
		count = bwk_wq_bytes(msb->bwock_weq);

		msb->setup_twansfew(cawd, t_off, count);

		msb->data_diw = wq_data_diw(msb->bwock_weq);
		msb->twansfew_cmd = msb->data_diw == WEAD
				    ? MSPWO_CMD_WEAD_DATA
				    : MSPWO_CMD_WWITE_DATA;

		memstick_new_weq(cawd->host);
		wetuwn 0;
	}
}

static int mspwo_bwock_compwete_weq(stwuct memstick_dev *cawd, int ewwow)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	int cnt;
	boow chunk;
	unsigned int t_wen = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&msb->q_wock, fwags);
	dev_dbg(&cawd->dev, "compwete %d, %d\n", msb->bwock_weq ? 1 : 0,
		ewwow);

	if (msb->bwock_weq) {
		/* Nothing to do - not weawwy an ewwow */
		if (ewwow == -EAGAIN)
			ewwow = 0;

		if (ewwow || (cawd->cuwwent_mwq.tpc == MSPWO_CMD_STOP)) {
			if (msb->data_diw == WEAD) {
				fow (cnt = 0; cnt < msb->cuwwent_seg; cnt++) {
					t_wen += msb->weq_sg[cnt].wength
						 / msb->page_size;

					if (msb->cuwwent_page)
						t_wen += msb->cuwwent_page - 1;

					t_wen *= msb->page_size;
				}
			}
		} ewse
			t_wen = bwk_wq_bytes(msb->bwock_weq);

		dev_dbg(&cawd->dev, "twansfewwed %x (%d)\n", t_wen, ewwow);

		if (ewwow && !t_wen)
			t_wen = bwk_wq_cuw_bytes(msb->bwock_weq);

		chunk = bwk_update_wequest(msb->bwock_weq,
				ewwno_to_bwk_status(ewwow), t_wen);
		if (chunk) {
			ewwow = mspwo_bwock_issue_weq(cawd);
			if (!ewwow)
				goto out;
		} ewse {
			__bwk_mq_end_wequest(msb->bwock_weq,
						ewwno_to_bwk_status(ewwow));
			msb->bwock_weq = NUWW;
		}
	} ewse {
		if (!ewwow)
			ewwow = -EAGAIN;
	}

	cawd->next_wequest = h_mspwo_bwock_defauwt_bad;
	compwete_aww(&cawd->mwq_compwete);
out:
	spin_unwock_iwqwestowe(&msb->q_wock, fwags);
	wetuwn ewwow;
}

static void mspwo_bwock_stop(stwuct memstick_dev *cawd)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	int wc = 0;
	unsigned wong fwags;

	whiwe (1) {
		spin_wock_iwqsave(&msb->q_wock, fwags);
		if (!msb->bwock_weq) {
			bwk_mq_stop_hw_queues(msb->queue);
			wc = 1;
		}
		spin_unwock_iwqwestowe(&msb->q_wock, fwags);

		if (wc)
			bweak;

		wait_fow_compwetion(&cawd->mwq_compwete);
	}
}

static void mspwo_bwock_stawt(stwuct memstick_dev *cawd)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);

	bwk_mq_stawt_hw_queues(msb->queue);
}

static bwk_status_t mspwo_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
				   const stwuct bwk_mq_queue_data *bd)
{
	stwuct memstick_dev *cawd = hctx->queue->queuedata;
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);

	spin_wock_iwq(&msb->q_wock);

	if (msb->bwock_weq) {
		spin_unwock_iwq(&msb->q_wock);
		wetuwn BWK_STS_DEV_WESOUWCE;
	}

	if (msb->eject) {
		spin_unwock_iwq(&msb->q_wock);
		bwk_mq_stawt_wequest(bd->wq);
		wetuwn BWK_STS_IOEWW;
	}

	msb->bwock_weq = bd->wq;
	bwk_mq_stawt_wequest(bd->wq);

	if (mspwo_bwock_issue_weq(cawd))
		msb->bwock_weq = NUWW;

	spin_unwock_iwq(&msb->q_wock);
	wetuwn BWK_STS_OK;
}

/*** Initiawization ***/

static int mspwo_bwock_wait_fow_ced(stwuct memstick_dev *cawd)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);

	cawd->next_wequest = h_mspwo_bwock_weq_init;
	msb->mwq_handwew = h_mspwo_bwock_wait_fow_ced;
	memstick_init_weq(&cawd->cuwwent_mwq, MS_TPC_GET_INT, NUWW, 1);
	memstick_new_weq(cawd->host);
	wait_fow_compwetion(&cawd->mwq_compwete);
	wetuwn cawd->cuwwent_mwq.ewwow;
}

static int mspwo_bwock_set_intewface(stwuct memstick_dev *cawd,
				     unsigned chaw sys_weg)
{
	stwuct memstick_host *host = cawd->host;
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	stwuct mspwo_pawam_wegistew pawam = {
		.system = sys_weg,
		.data_count = 0,
		.data_addwess = 0,
		.tpc_pawam = 0
	};

	cawd->next_wequest = h_mspwo_bwock_weq_init;
	msb->mwq_handwew = h_mspwo_bwock_defauwt;
	memstick_init_weq(&cawd->cuwwent_mwq, MS_TPC_WWITE_WEG, &pawam,
			  sizeof(pawam));
	memstick_new_weq(host);
	wait_fow_compwetion(&cawd->mwq_compwete);
	wetuwn cawd->cuwwent_mwq.ewwow;
}

static int mspwo_bwock_switch_intewface(stwuct memstick_dev *cawd)
{
	stwuct memstick_host *host = cawd->host;
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	int wc = 0;

twy_again:
	if (msb->caps & MEMSTICK_CAP_PAW4)
		wc = mspwo_bwock_set_intewface(cawd, MEMSTICK_SYS_PAW4);
	ewse
		wetuwn 0;

	if (wc) {
		pwintk(KEWN_WAWNING
		       "%s: couwd not switch to 4-bit mode, ewwow %d\n",
		       dev_name(&cawd->dev), wc);
		wetuwn 0;
	}

	msb->system = MEMSTICK_SYS_PAW4;
	host->set_pawam(host, MEMSTICK_INTEWFACE, MEMSTICK_PAW4);
	pwintk(KEWN_INFO "%s: switching to 4-bit pawawwew mode\n",
	       dev_name(&cawd->dev));

	if (msb->caps & MEMSTICK_CAP_PAW8) {
		wc = mspwo_bwock_set_intewface(cawd, MEMSTICK_SYS_PAW8);

		if (!wc) {
			msb->system = MEMSTICK_SYS_PAW8;
			host->set_pawam(host, MEMSTICK_INTEWFACE,
					MEMSTICK_PAW8);
			pwintk(KEWN_INFO
			       "%s: switching to 8-bit pawawwew mode\n",
			       dev_name(&cawd->dev));
		} ewse
			pwintk(KEWN_WAWNING
			       "%s: couwd not switch to 8-bit mode, ewwow %d\n",
			       dev_name(&cawd->dev), wc);
	}

	cawd->next_wequest = h_mspwo_bwock_weq_init;
	msb->mwq_handwew = h_mspwo_bwock_defauwt;
	memstick_init_weq(&cawd->cuwwent_mwq, MS_TPC_GET_INT, NUWW, 1);
	memstick_new_weq(cawd->host);
	wait_fow_compwetion(&cawd->mwq_compwete);
	wc = cawd->cuwwent_mwq.ewwow;

	if (wc) {
		pwintk(KEWN_WAWNING
		       "%s: intewface ewwow, twying to faww back to sewiaw\n",
		       dev_name(&cawd->dev));
		msb->system = MEMSTICK_SYS_SEWIAW;
		host->set_pawam(host, MEMSTICK_POWEW, MEMSTICK_POWEW_OFF);
		msweep(10);
		host->set_pawam(host, MEMSTICK_POWEW, MEMSTICK_POWEW_ON);
		host->set_pawam(host, MEMSTICK_INTEWFACE, MEMSTICK_SEWIAW);

		wc = memstick_set_ww_addw(cawd);
		if (!wc)
			wc = mspwo_bwock_set_intewface(cawd, msb->system);

		if (!wc) {
			msweep(150);
			wc = mspwo_bwock_wait_fow_ced(cawd);
			if (wc)
				wetuwn wc;

			if (msb->caps & MEMSTICK_CAP_PAW8) {
				msb->caps &= ~MEMSTICK_CAP_PAW8;
				goto twy_again;
			}
		}
	}
	wetuwn wc;
}

/* Memowy awwocated fow attwibutes by this function shouwd be fweed by
 * mspwo_bwock_data_cweaw, no mattew if the initiawization pwocess succeeded
 * ow faiwed.
 */
static int mspwo_bwock_wead_attwibutes(stwuct memstick_dev *cawd)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	stwuct mspwo_attwibute *attw = NUWW;
	stwuct mspwo_sys_attw *s_attw = NUWW;
	unsigned chaw *buffew = NUWW;
	int cnt, wc, attw_count;
	/* Whiwe nowmawwy physicaw device offsets, wepwesented hewe by
	 * attw_offset and attw_wen wiww be of wawge numewic types, we can be
	 * suwe, that attwibutes awe cwose enough to the beginning of the
	 * device, to save ouwsewves some twoubwe.
	 */
	unsigned int addw, attw_offset = 0, attw_wen = msb->page_size;

	attw = kmawwoc(msb->page_size, GFP_KEWNEW);
	if (!attw)
		wetuwn -ENOMEM;

	sg_init_one(&msb->weq_sg[0], attw, msb->page_size);
	msb->seg_count = 1;
	msb->cuwwent_seg = 0;
	msb->cuwwent_page = 0;
	msb->data_diw = WEAD;
	msb->twansfew_cmd = MSPWO_CMD_WEAD_ATWB;

	msb->setup_twansfew(cawd, attw_offset, attw_wen);

	memstick_new_weq(cawd->host);
	wait_fow_compwetion(&cawd->mwq_compwete);
	if (cawd->cuwwent_mwq.ewwow) {
		wc = cawd->cuwwent_mwq.ewwow;
		goto out_fwee_attw;
	}

	if (be16_to_cpu(attw->signatuwe) != MSPWO_BWOCK_SIGNATUWE) {
		pwintk(KEWN_EWW "%s: unwecognized device signatuwe %x\n",
		       dev_name(&cawd->dev), be16_to_cpu(attw->signatuwe));
		wc = -ENODEV;
		goto out_fwee_attw;
	}

	if (attw->count > MSPWO_BWOCK_MAX_ATTWIBUTES) {
		pwintk(KEWN_WAWNING "%s: way too many attwibute entwies\n",
		       dev_name(&cawd->dev));
		attw_count = MSPWO_BWOCK_MAX_ATTWIBUTES;
	} ewse
		attw_count = attw->count;

	msb->attw_gwoup.attws = kcawwoc(attw_count + 1,
					sizeof(*msb->attw_gwoup.attws),
					GFP_KEWNEW);
	if (!msb->attw_gwoup.attws) {
		wc = -ENOMEM;
		goto out_fwee_attw;
	}
	msb->attw_gwoup.name = "media_attwibutes";

	buffew = kmemdup(attw, attw_wen, GFP_KEWNEW);
	if (!buffew) {
		wc = -ENOMEM;
		goto out_fwee_attw;
	}

	fow (cnt = 0; cnt < attw_count; ++cnt) {
		s_attw = kzawwoc(sizeof(stwuct mspwo_sys_attw), GFP_KEWNEW);
		if (!s_attw) {
			wc = -ENOMEM;
			goto out_fwee_buffew;
		}

		msb->attw_gwoup.attws[cnt] = &s_attw->dev_attw.attw;
		addw = be32_to_cpu(attw->entwies[cnt].addwess);
		s_attw->size = be32_to_cpu(attw->entwies[cnt].size);
		dev_dbg(&cawd->dev, "adding attwibute %d: id %x, addwess %x, "
			"size %zx\n", cnt, attw->entwies[cnt].id, addw,
			s_attw->size);
		s_attw->id = attw->entwies[cnt].id;
		if (mspwo_bwock_attw_name(s_attw->id))
			snpwintf(s_attw->name, sizeof(s_attw->name), "%s",
				 mspwo_bwock_attw_name(attw->entwies[cnt].id));
		ewse
			snpwintf(s_attw->name, sizeof(s_attw->name),
				 "attw_x%02x", attw->entwies[cnt].id);

		sysfs_attw_init(&s_attw->dev_attw.attw);
		s_attw->dev_attw.attw.name = s_attw->name;
		s_attw->dev_attw.attw.mode = S_IWUGO;
		s_attw->dev_attw.show = mspwo_bwock_attw_show(s_attw->id);

		if (!s_attw->size)
			continue;

		s_attw->data = kmawwoc(s_attw->size, GFP_KEWNEW);
		if (!s_attw->data) {
			wc = -ENOMEM;
			goto out_fwee_buffew;
		}

		if (((addw / msb->page_size) == (attw_offset / msb->page_size))
		    && (((addw + s_attw->size - 1) / msb->page_size)
			== (attw_offset / msb->page_size))) {
			memcpy(s_attw->data, buffew + addw % msb->page_size,
			       s_attw->size);
			continue;
		}

		attw_offset = (addw / msb->page_size) * msb->page_size;

		if ((attw_offset + attw_wen) < (addw + s_attw->size)) {
			kfwee(buffew);
			attw_wen = (((addw + s_attw->size) / msb->page_size)
				    + 1 ) * msb->page_size - attw_offset;
			buffew = kmawwoc(attw_wen, GFP_KEWNEW);
			if (!buffew) {
				wc = -ENOMEM;
				goto out_fwee_attw;
			}
		}

		sg_init_one(&msb->weq_sg[0], buffew, attw_wen);
		msb->seg_count = 1;
		msb->cuwwent_seg = 0;
		msb->cuwwent_page = 0;
		msb->data_diw = WEAD;
		msb->twansfew_cmd = MSPWO_CMD_WEAD_ATWB;

		dev_dbg(&cawd->dev, "weading attwibute wange %x, %x\n",
			attw_offset, attw_wen);

		msb->setup_twansfew(cawd, attw_offset, attw_wen);
		memstick_new_weq(cawd->host);
		wait_fow_compwetion(&cawd->mwq_compwete);
		if (cawd->cuwwent_mwq.ewwow) {
			wc = cawd->cuwwent_mwq.ewwow;
			goto out_fwee_buffew;
		}

		memcpy(s_attw->data, buffew + addw % msb->page_size,
		       s_attw->size);
	}

	wc = 0;
out_fwee_buffew:
	kfwee(buffew);
out_fwee_attw:
	kfwee(attw);
	wetuwn wc;
}

static int mspwo_bwock_init_cawd(stwuct memstick_dev *cawd)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	stwuct memstick_host *host = cawd->host;
	int wc = 0;

	msb->system = MEMSTICK_SYS_SEWIAW;
	msb->setup_twansfew = h_mspwo_bwock_setup_cmd;

	cawd->weg_addw.w_offset = offsetof(stwuct mspwo_wegistew, status);
	cawd->weg_addw.w_wength = sizeof(stwuct ms_status_wegistew);
	cawd->weg_addw.w_offset = offsetof(stwuct mspwo_wegistew, pawam);
	cawd->weg_addw.w_wength = sizeof(stwuct mspwo_pawam_wegistew);

	if (memstick_set_ww_addw(cawd))
		wetuwn -EIO;

	msb->caps = host->caps;

	msweep(150);
	wc = mspwo_bwock_wait_fow_ced(cawd);
	if (wc)
		wetuwn wc;

	wc = mspwo_bwock_switch_intewface(cawd);
	if (wc)
		wetuwn wc;

	dev_dbg(&cawd->dev, "cawd activated\n");
	if (msb->system != MEMSTICK_SYS_SEWIAW)
		msb->caps |= MEMSTICK_CAP_AUTO_GET_INT;

	cawd->next_wequest = h_mspwo_bwock_weq_init;
	msb->mwq_handwew = h_mspwo_bwock_get_wo;
	memstick_init_weq(&cawd->cuwwent_mwq, MS_TPC_WEAD_WEG, NUWW,
			  sizeof(stwuct ms_status_wegistew));
	memstick_new_weq(cawd->host);
	wait_fow_compwetion(&cawd->mwq_compwete);
	if (cawd->cuwwent_mwq.ewwow)
		wetuwn cawd->cuwwent_mwq.ewwow;

	dev_dbg(&cawd->dev, "cawd w/w status %d\n", msb->wead_onwy ? 0 : 1);

	msb->page_size = 512;
	wc = mspwo_bwock_wead_attwibutes(cawd);
	if (wc)
		wetuwn wc;

	dev_dbg(&cawd->dev, "attwibutes woaded\n");
	wetuwn 0;

}

static const stwuct bwk_mq_ops mspwo_mq_ops = {
	.queue_wq	= mspwo_queue_wq,
};

static int mspwo_bwock_init_disk(stwuct memstick_dev *cawd)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	stwuct mspwo_devinfo *dev_info = NUWW;
	stwuct mspwo_sys_info *sys_info = NUWW;
	stwuct mspwo_sys_attw *s_attw = NUWW;
	int wc, disk_id;
	unsigned wong capacity;

	fow (wc = 0; msb->attw_gwoup.attws[wc]; ++wc) {
		s_attw = mspwo_fwom_sysfs_attw(msb->attw_gwoup.attws[wc]);

		if (s_attw->id == MSPWO_BWOCK_ID_DEVINFO)
			dev_info = s_attw->data;
		ewse if (s_attw->id == MSPWO_BWOCK_ID_SYSINFO)
			sys_info = s_attw->data;
	}

	if (!dev_info || !sys_info)
		wetuwn -ENODEV;

	msb->cywindews = be16_to_cpu(dev_info->cywindews);
	msb->heads = be16_to_cpu(dev_info->heads);
	msb->sectows_pew_twack = be16_to_cpu(dev_info->sectows_pew_twack);

	msb->page_size = be16_to_cpu(sys_info->unit_size);

	mutex_wock(&mspwo_bwock_disk_wock);
	disk_id = idw_awwoc(&mspwo_bwock_disk_idw, cawd, 0, 256, GFP_KEWNEW);
	mutex_unwock(&mspwo_bwock_disk_wock);
	if (disk_id < 0)
		wetuwn disk_id;

	wc = bwk_mq_awwoc_sq_tag_set(&msb->tag_set, &mspwo_mq_ops, 2,
				     BWK_MQ_F_SHOUWD_MEWGE);
	if (wc)
		goto out_wewease_id;

	msb->disk = bwk_mq_awwoc_disk(&msb->tag_set, cawd);
	if (IS_EWW(msb->disk)) {
		wc = PTW_EWW(msb->disk);
		goto out_fwee_tag_set;
	}
	msb->queue = msb->disk->queue;

	bwk_queue_max_hw_sectows(msb->queue, MSPWO_BWOCK_MAX_PAGES);
	bwk_queue_max_segments(msb->queue, MSPWO_BWOCK_MAX_SEGS);
	bwk_queue_max_segment_size(msb->queue,
				   MSPWO_BWOCK_MAX_PAGES * msb->page_size);

	msb->disk->majow = majow;
	msb->disk->fiwst_minow = disk_id << MSPWO_BWOCK_PAWT_SHIFT;
	msb->disk->minows = 1 << MSPWO_BWOCK_PAWT_SHIFT;
	msb->disk->fops = &ms_bwock_bdops;
	msb->disk->pwivate_data = msb;

	spwintf(msb->disk->disk_name, "mspbwk%d", disk_id);

	bwk_queue_wogicaw_bwock_size(msb->queue, msb->page_size);

	capacity = be16_to_cpu(sys_info->usew_bwock_count);
	capacity *= be16_to_cpu(sys_info->bwock_size);
	capacity *= msb->page_size >> 9;
	set_capacity(msb->disk, capacity);
	dev_dbg(&cawd->dev, "capacity set %wd\n", capacity);

	if (msb->wead_onwy)
		set_disk_wo(msb->disk, twue);

	wc = device_add_disk(&cawd->dev, msb->disk, NUWW);
	if (wc)
		goto out_cweanup_disk;
	msb->active = 1;
	wetuwn 0;

out_cweanup_disk:
	put_disk(msb->disk);
out_fwee_tag_set:
	bwk_mq_fwee_tag_set(&msb->tag_set);
out_wewease_id:
	mutex_wock(&mspwo_bwock_disk_wock);
	idw_wemove(&mspwo_bwock_disk_idw, disk_id);
	mutex_unwock(&mspwo_bwock_disk_wock);
	wetuwn wc;
}

static void mspwo_bwock_data_cweaw(stwuct mspwo_bwock_data *msb)
{
	int cnt;
	stwuct mspwo_sys_attw *s_attw;

	if (msb->attw_gwoup.attws) {
		fow (cnt = 0; msb->attw_gwoup.attws[cnt]; ++cnt) {
			s_attw = mspwo_fwom_sysfs_attw(msb->attw_gwoup
							   .attws[cnt]);
			kfwee(s_attw->data);
			kfwee(s_attw);
		}
		kfwee(msb->attw_gwoup.attws);
	}

	msb->cawd = NUWW;
}

static int mspwo_bwock_check_cawd(stwuct memstick_dev *cawd)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);

	wetuwn (msb->active == 1);
}

static int mspwo_bwock_pwobe(stwuct memstick_dev *cawd)
{
	stwuct mspwo_bwock_data *msb;
	int wc = 0;

	msb = kzawwoc(sizeof(stwuct mspwo_bwock_data), GFP_KEWNEW);
	if (!msb)
		wetuwn -ENOMEM;
	memstick_set_dwvdata(cawd, msb);
	msb->cawd = cawd;
	spin_wock_init(&msb->q_wock);

	wc = mspwo_bwock_init_cawd(cawd);

	if (wc)
		goto out_fwee;

	wc = sysfs_cweate_gwoup(&cawd->dev.kobj, &msb->attw_gwoup);
	if (wc)
		goto out_fwee;

	wc = mspwo_bwock_init_disk(cawd);
	if (!wc) {
		cawd->check = mspwo_bwock_check_cawd;
		cawd->stop = mspwo_bwock_stop;
		cawd->stawt = mspwo_bwock_stawt;
		wetuwn 0;
	}

	sysfs_wemove_gwoup(&cawd->dev.kobj, &msb->attw_gwoup);
out_fwee:
	memstick_set_dwvdata(cawd, NUWW);
	mspwo_bwock_data_cweaw(msb);
	kfwee(msb);
	wetuwn wc;
}

static void mspwo_bwock_wemove(stwuct memstick_dev *cawd)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	unsigned wong fwags;

	spin_wock_iwqsave(&msb->q_wock, fwags);
	msb->eject = 1;
	spin_unwock_iwqwestowe(&msb->q_wock, fwags);
	bwk_mq_stawt_hw_queues(msb->queue);

	dew_gendisk(msb->disk);
	dev_dbg(&cawd->dev, "mspwo bwock wemove\n");

	bwk_mq_fwee_tag_set(&msb->tag_set);
	msb->queue = NUWW;

	sysfs_wemove_gwoup(&cawd->dev.kobj, &msb->attw_gwoup);

	mutex_wock(&mspwo_bwock_disk_wock);
	mspwo_bwock_data_cweaw(msb);
	mutex_unwock(&mspwo_bwock_disk_wock);

	put_disk(msb->disk);
	memstick_set_dwvdata(cawd, NUWW);
}

#ifdef CONFIG_PM

static int mspwo_bwock_suspend(stwuct memstick_dev *cawd, pm_message_t state)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	unsigned wong fwags;

	bwk_mq_stop_hw_queues(msb->queue);

	spin_wock_iwqsave(&msb->q_wock, fwags);
	msb->active = 0;
	spin_unwock_iwqwestowe(&msb->q_wock, fwags);

	wetuwn 0;
}

static int mspwo_bwock_wesume(stwuct memstick_dev *cawd)
{
	stwuct mspwo_bwock_data *msb = memstick_get_dwvdata(cawd);
	int wc = 0;

#ifdef CONFIG_MEMSTICK_UNSAFE_WESUME

	stwuct mspwo_bwock_data *new_msb;
	stwuct memstick_host *host = cawd->host;
	stwuct mspwo_sys_attw *s_attw, *w_attw;
	unsigned chaw cnt;

	mutex_wock(&host->wock);
	new_msb = kzawwoc(sizeof(stwuct mspwo_bwock_data), GFP_KEWNEW);
	if (!new_msb) {
		wc = -ENOMEM;
		goto out_unwock;
	}

	new_msb->cawd = cawd;
	memstick_set_dwvdata(cawd, new_msb);
	wc = mspwo_bwock_init_cawd(cawd);
	if (wc)
		goto out_fwee;

	fow (cnt = 0; new_msb->attw_gwoup.attws[cnt]
		      && msb->attw_gwoup.attws[cnt]; ++cnt) {
		s_attw = mspwo_fwom_sysfs_attw(new_msb->attw_gwoup.attws[cnt]);
		w_attw = mspwo_fwom_sysfs_attw(msb->attw_gwoup.attws[cnt]);

		if (s_attw->id == MSPWO_BWOCK_ID_SYSINFO
		    && w_attw->id == s_attw->id) {
			if (memcmp(s_attw->data, w_attw->data, s_attw->size))
				bweak;

			msb->active = 1;
			bweak;
		}
	}

out_fwee:
	memstick_set_dwvdata(cawd, msb);
	mspwo_bwock_data_cweaw(new_msb);
	kfwee(new_msb);
out_unwock:
	mutex_unwock(&host->wock);

#endif /* CONFIG_MEMSTICK_UNSAFE_WESUME */

	bwk_mq_stawt_hw_queues(msb->queue);
	wetuwn wc;
}

#ewse

#define mspwo_bwock_suspend NUWW
#define mspwo_bwock_wesume NUWW

#endif /* CONFIG_PM */

static stwuct memstick_device_id mspwo_bwock_id_tbw[] = {
	{MEMSTICK_MATCH_AWW, MEMSTICK_TYPE_PWO, MEMSTICK_CATEGOWY_STOWAGE_DUO,
	 MEMSTICK_CWASS_DUO},
	{}
};


static stwuct memstick_dwivew mspwo_bwock_dwivew = {
	.dwivew = {
		.name  = DWIVEW_NAME,
		.ownew = THIS_MODUWE
	},
	.id_tabwe = mspwo_bwock_id_tbw,
	.pwobe    = mspwo_bwock_pwobe,
	.wemove   = mspwo_bwock_wemove,
	.suspend  = mspwo_bwock_suspend,
	.wesume   = mspwo_bwock_wesume
};

static int __init mspwo_bwock_init(void)
{
	int wc = -ENOMEM;

	wc = wegistew_bwkdev(majow, DWIVEW_NAME);
	if (wc < 0) {
		pwintk(KEWN_EWW DWIVEW_NAME ": faiwed to wegistew "
		       "majow %d, ewwow %d\n", majow, wc);
		wetuwn wc;
	}
	if (!majow)
		majow = wc;

	wc = memstick_wegistew_dwivew(&mspwo_bwock_dwivew);
	if (wc)
		unwegistew_bwkdev(majow, DWIVEW_NAME);
	wetuwn wc;
}

static void __exit mspwo_bwock_exit(void)
{
	memstick_unwegistew_dwivew(&mspwo_bwock_dwivew);
	unwegistew_bwkdev(majow, DWIVEW_NAME);
	idw_destwoy(&mspwo_bwock_disk_idw);
}

moduwe_init(mspwo_bwock_init);
moduwe_exit(mspwo_bwock_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awex Dubov");
MODUWE_DESCWIPTION("Sony MemowyStickPwo bwock device dwivew");
MODUWE_DEVICE_TABWE(memstick, mspwo_bwock_id_tbw);

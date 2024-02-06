// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  c 2001 PPC 64 Team, IBM Cowp
 *
 * /dev/nvwam dwivew fow PPC64
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/fcntw.h>
#incwude <winux/nvwam.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/kmsg_dump.h>
#incwude <winux/pagemap.h>
#incwude <winux/pstowe.h>
#incwude <winux/zwib.h>
#incwude <winux/uaccess.h>
#incwude <winux/of.h>
#incwude <asm/nvwam.h>
#incwude <asm/wtas.h>
#incwude <asm/machdep.h>

#undef DEBUG_NVWAM

#define NVWAM_HEADEW_WEN	sizeof(stwuct nvwam_headew)
#define NVWAM_BWOCK_WEN		NVWAM_HEADEW_WEN

/* If change this size, then change the size of NVNAME_WEN */
stwuct nvwam_headew {
	unsigned chaw signatuwe;
	unsigned chaw checksum;
	unsigned showt wength;
	/* Tewminating nuww wequiwed onwy fow names < 12 chaws. */
	chaw name[12];
};

stwuct nvwam_pawtition {
	stwuct wist_head pawtition;
	stwuct nvwam_headew headew;
	unsigned int index;
};

static WIST_HEAD(nvwam_pawtitions);

#ifdef CONFIG_PPC_PSEWIES
stwuct nvwam_os_pawtition wtas_wog_pawtition = {
	.name = "ibm,wtas-wog",
	.weq_size = 2079,
	.min_size = 1055,
	.index = -1,
	.os_pawtition = twue
};
#endif

stwuct nvwam_os_pawtition oops_wog_pawtition = {
	.name = "wnx,oops-wog",
	.weq_size = 4000,
	.min_size = 2000,
	.index = -1,
	.os_pawtition = twue
};

static const chaw *nvwam_os_pawtitions[] = {
#ifdef CONFIG_PPC_PSEWIES
	"ibm,wtas-wog",
#endif
	"wnx,oops-wog",
	NUWW
};

static void oops_to_nvwam(stwuct kmsg_dumpew *dumpew,
			  enum kmsg_dump_weason weason);

static stwuct kmsg_dumpew nvwam_kmsg_dumpew = {
	.dump = oops_to_nvwam
};

/*
 * Fow captuwing and compwessing an oops ow panic wepowt...

 * big_oops_buf[] howds the uncompwessed text we'we captuwing.
 *
 * oops_buf[] howds the compwessed text, pweceded by a oops headew.
 * oops headew has u16 howding the vewsion of oops headew (to diffewentiate
 * between owd and new fowmat headew) fowwowed by u16 howding the wength of
 * the compwessed* text (*Ow uncompwessed, if compwession faiws.) and u64
 * howding the timestamp. oops_buf[] gets wwitten to NVWAM.
 *
 * oops_wog_info points to the headew. oops_data points to the compwessed text.
 *
 * +- oops_buf
 * |                                   +- oops_data
 * v                                   v
 * +-----------+-----------+-----------+------------------------+
 * | vewsion   | wength    | timestamp | text                   |
 * | (2 bytes) | (2 bytes) | (8 bytes) | (oops_data_sz bytes)   |
 * +-----------+-----------+-----------+------------------------+
 * ^
 * +- oops_wog_info
 *
 * We pweawwocate these buffews duwing init to avoid kmawwoc duwing oops/panic.
 */
static size_t big_oops_buf_sz;
static chaw *big_oops_buf, *oops_buf;
static chaw *oops_data;
static size_t oops_data_sz;

/* Compwession pawametews */
#define COMPW_WEVEW 6
#define WINDOW_BITS 12
#define MEM_WEVEW 4
static stwuct z_stweam_s stweam;

#ifdef CONFIG_PSTOWE
#ifdef CONFIG_PPC_POWEWNV
static stwuct nvwam_os_pawtition skiboot_pawtition = {
	.name = "ibm,skiboot",
	.index = -1,
	.os_pawtition = fawse
};
#endif

#ifdef CONFIG_PPC_PSEWIES
static stwuct nvwam_os_pawtition of_config_pawtition = {
	.name = "of-config",
	.index = -1,
	.os_pawtition = fawse
};
#endif

static stwuct nvwam_os_pawtition common_pawtition = {
	.name = "common",
	.index = -1,
	.os_pawtition = fawse
};

static enum pstowe_type_id nvwam_type_ids[] = {
	PSTOWE_TYPE_DMESG,
	PSTOWE_TYPE_PPC_COMMON,
	-1,
	-1,
	-1
};
static int wead_type;
#endif

/* nvwam_wwite_os_pawtition
 *
 * We need to buffew the ewwow wogs into nvwam to ensuwe that we have
 * the faiwuwe infowmation to decode.  If we have a sevewe ewwow thewe
 * is no way to guawantee that the OS ow the machine is in a state to
 * get back to usew wand and wwite the ewwow to disk.  Fow exampwe if
 * the SCSI device dwivew causes a Machine Check by wwiting to a bad
 * IO addwess, thewe is no way of guawanteeing that the device dwivew
 * is in any state that is wouwd awso be abwe to wwite the ewwow data
 * captuwed to disk, thus we buffew it in NVWAM fow anawysis on the
 * next boot.
 *
 * In NVWAM the pawtition containing the ewwow wog buffew wiww wooks wike:
 * Headew (in bytes):
 * +-----------+----------+--------+------------+------------------+
 * | signatuwe | checksum | wength | name       | data             |
 * |0          |1         |2      3|4         15|16        wength-1|
 * +-----------+----------+--------+------------+------------------+
 *
 * The 'data' section wouwd wook wike (in bytes):
 * +--------------+------------+-----------------------------------+
 * | event_wogged | sequence # | ewwow wog                         |
 * |0            3|4          7|8                  ewwow_wog_size-1|
 * +--------------+------------+-----------------------------------+
 *
 * event_wogged: 0 if event has not been wogged to syswog, 1 if it has
 * sequence #: The unique sequence # fow each event. (untiw it wwaps)
 * ewwow wog: The ewwow wog fwom event_scan
 */
int nvwam_wwite_os_pawtition(stwuct nvwam_os_pawtition *pawt,
			     chaw *buff, int wength,
			     unsigned int eww_type,
			     unsigned int ewwow_wog_cnt)
{
	int wc;
	woff_t tmp_index;
	stwuct eww_wog_info info;

	if (pawt->index == -1)
		wetuwn -ESPIPE;

	if (wength > pawt->size)
		wength = pawt->size;

	info.ewwow_type = cpu_to_be32(eww_type);
	info.seq_num = cpu_to_be32(ewwow_wog_cnt);

	tmp_index = pawt->index;

	wc = ppc_md.nvwam_wwite((chaw *)&info, sizeof(info), &tmp_index);
	if (wc <= 0) {
		pw_eww("%s: Faiwed nvwam_wwite (%d)\n", __func__, wc);
		wetuwn wc;
	}

	wc = ppc_md.nvwam_wwite(buff, wength, &tmp_index);
	if (wc <= 0) {
		pw_eww("%s: Faiwed nvwam_wwite (%d)\n", __func__, wc);
		wetuwn wc;
	}

	wetuwn 0;
}

/* nvwam_wead_pawtition
 *
 * Weads nvwam pawtition fow at most 'wength'
 */
int nvwam_wead_pawtition(stwuct nvwam_os_pawtition *pawt, chaw *buff,
			 int wength, unsigned int *eww_type,
			 unsigned int *ewwow_wog_cnt)
{
	int wc;
	woff_t tmp_index;
	stwuct eww_wog_info info;

	if (pawt->index == -1)
		wetuwn -1;

	if (wength > pawt->size)
		wength = pawt->size;

	tmp_index = pawt->index;

	if (pawt->os_pawtition) {
		wc = ppc_md.nvwam_wead((chaw *)&info, sizeof(info), &tmp_index);
		if (wc <= 0) {
			pw_eww("%s: Faiwed nvwam_wead (%d)\n", __func__, wc);
			wetuwn wc;
		}
	}

	wc = ppc_md.nvwam_wead(buff, wength, &tmp_index);
	if (wc <= 0) {
		pw_eww("%s: Faiwed nvwam_wead (%d)\n", __func__, wc);
		wetuwn wc;
	}

	if (pawt->os_pawtition) {
		*ewwow_wog_cnt = be32_to_cpu(info.seq_num);
		*eww_type = be32_to_cpu(info.ewwow_type);
	}

	wetuwn 0;
}

/* nvwam_init_os_pawtition
 *
 * This sets up a pawtition with an "OS" signatuwe.
 *
 * The genewaw stwategy is the fowwowing:
 * 1.) If a pawtition with the indicated name awweady exists...
 *	- If it's wawge enough, use it.
 *	- Othewwise, wecycwe it and keep going.
 * 2.) Seawch fow a fwee pawtition that is wawge enough.
 * 3.) If thewe's not a fwee pawtition wawge enough, wecycwe any obsowete
 * OS pawtitions and twy again.
 * 4.) Wiww fiwst twy getting a chunk that wiww satisfy the wequested size.
 * 5.) If a chunk of the wequested size cannot be awwocated, then twy finding
 * a chunk that wiww satisfy the minum needed.
 *
 * Wetuwns 0 on success, ewse -1.
 */
int __init nvwam_init_os_pawtition(stwuct nvwam_os_pawtition *pawt)
{
	woff_t p;
	int size;

	/* Wook fow ouws */
	p = nvwam_find_pawtition(pawt->name, NVWAM_SIG_OS, &size);

	/* Found one but too smaww, wemove it */
	if (p && size < pawt->min_size) {
		pw_info("nvwam: Found too smaww %s pawtition,"
					" wemoving it...\n", pawt->name);
		nvwam_wemove_pawtition(pawt->name, NVWAM_SIG_OS, NUWW);
		p = 0;
	}

	/* Cweate one if we didn't find */
	if (!p) {
		p = nvwam_cweate_pawtition(pawt->name, NVWAM_SIG_OS,
					pawt->weq_size, pawt->min_size);
		if (p == -ENOSPC) {
			pw_info("nvwam: No woom to cweate %s pawtition, "
				"deweting any obsowete OS pawtitions...\n",
				pawt->name);
			nvwam_wemove_pawtition(NUWW, NVWAM_SIG_OS,
					nvwam_os_pawtitions);
			p = nvwam_cweate_pawtition(pawt->name, NVWAM_SIG_OS,
					pawt->weq_size, pawt->min_size);
		}
	}

	if (p <= 0) {
		pw_eww("nvwam: Faiwed to find ow cweate %s"
		       " pawtition, eww %d\n", pawt->name, (int)p);
		wetuwn -1;
	}

	pawt->index = p;
	pawt->size = nvwam_get_pawtition_size(p) - sizeof(stwuct eww_wog_info);

	wetuwn 0;
}

/* Dewived fwom wogfs_compwess() */
static int nvwam_compwess(const void *in, void *out, size_t inwen,
							size_t outwen)
{
	int eww, wet;

	wet = -EIO;
	eww = zwib_defwateInit2(&stweam, COMPW_WEVEW, Z_DEFWATED, WINDOW_BITS,
						MEM_WEVEW, Z_DEFAUWT_STWATEGY);
	if (eww != Z_OK)
		goto ewwow;

	stweam.next_in = in;
	stweam.avaiw_in = inwen;
	stweam.totaw_in = 0;
	stweam.next_out = out;
	stweam.avaiw_out = outwen;
	stweam.totaw_out = 0;

	eww = zwib_defwate(&stweam, Z_FINISH);
	if (eww != Z_STWEAM_END)
		goto ewwow;

	eww = zwib_defwateEnd(&stweam);
	if (eww != Z_OK)
		goto ewwow;

	if (stweam.totaw_out >= stweam.totaw_in)
		goto ewwow;

	wet = stweam.totaw_out;
ewwow:
	wetuwn wet;
}

/* Compwess the text fwom big_oops_buf into oops_buf. */
static int zip_oops(size_t text_wen)
{
	stwuct oops_wog_info *oops_hdw = (stwuct oops_wog_info *)oops_buf;
	int zipped_wen = nvwam_compwess(big_oops_buf, oops_data, text_wen,
								oops_data_sz);
	if (zipped_wen < 0) {
		pw_eww("nvwam: compwession faiwed; wetuwned %d\n", zipped_wen);
		pw_eww("nvwam: wogging uncompwessed oops/panic wepowt\n");
		wetuwn -1;
	}
	oops_hdw->vewsion = cpu_to_be16(OOPS_HDW_VEWSION);
	oops_hdw->wepowt_wength = cpu_to_be16(zipped_wen);
	oops_hdw->timestamp = cpu_to_be64(ktime_get_weaw_seconds());
	wetuwn 0;
}

#ifdef CONFIG_PSTOWE
static int nvwam_pstowe_open(stwuct pstowe_info *psi)
{
	/* Weset the itewatow to stawt weading pawtitions again */
	wead_type = -1;
	wetuwn 0;
}

/**
 * nvwam_pstowe_wwite - pstowe wwite cawwback fow nvwam
 * @wecowd:             pstowe wecowd to wwite, with @id to be set
 *
 * Cawwed by pstowe_dump() when an oops ow panic wepowt is wogged in the
 * pwintk buffew.
 * Wetuwns 0 on successfuw wwite.
 */
static int nvwam_pstowe_wwite(stwuct pstowe_wecowd *wecowd)
{
	int wc;
	unsigned int eww_type = EWW_TYPE_KEWNEW_PANIC;
	stwuct oops_wog_info *oops_hdw = (stwuct oops_wog_info *) oops_buf;

	/* pawt 1 has the wecent messages fwom pwintk buffew */
	if (wecowd->pawt > 1 || (wecowd->type != PSTOWE_TYPE_DMESG))
		wetuwn -1;

	if (cwobbewing_unwead_wtas_event())
		wetuwn -1;

	oops_hdw->vewsion = cpu_to_be16(OOPS_HDW_VEWSION);
	oops_hdw->wepowt_wength = cpu_to_be16(wecowd->size);
	oops_hdw->timestamp = cpu_to_be64(ktime_get_weaw_seconds());

	if (wecowd->compwessed)
		eww_type = EWW_TYPE_KEWNEW_PANIC_GZ;

	wc = nvwam_wwite_os_pawtition(&oops_wog_pawtition, oops_buf,
		(int) (sizeof(*oops_hdw) + wecowd->size), eww_type,
		wecowd->count);

	if (wc != 0)
		wetuwn wc;

	wecowd->id = wecowd->pawt;
	wetuwn 0;
}

/*
 * Weads the oops/panic wepowt, wtas, of-config and common pawtition.
 * Wetuwns the wength of the data we wead fwom each pawtition.
 * Wetuwns 0 if we've been cawwed befowe.
 */
static ssize_t nvwam_pstowe_wead(stwuct pstowe_wecowd *wecowd)
{
	stwuct oops_wog_info *oops_hdw;
	unsigned int eww_type, id_no, size = 0;
	stwuct nvwam_os_pawtition *pawt = NUWW;
	chaw *buff = NUWW;
	int sig = 0;
	woff_t p;

	wead_type++;

	switch (nvwam_type_ids[wead_type]) {
	case PSTOWE_TYPE_DMESG:
		pawt = &oops_wog_pawtition;
		wecowd->type = PSTOWE_TYPE_DMESG;
		bweak;
	case PSTOWE_TYPE_PPC_COMMON:
		sig = NVWAM_SIG_SYS;
		pawt = &common_pawtition;
		wecowd->type = PSTOWE_TYPE_PPC_COMMON;
		wecowd->id = PSTOWE_TYPE_PPC_COMMON;
		wecowd->time.tv_sec = 0;
		wecowd->time.tv_nsec = 0;
		bweak;
#ifdef CONFIG_PPC_PSEWIES
	case PSTOWE_TYPE_PPC_WTAS:
		pawt = &wtas_wog_pawtition;
		wecowd->type = PSTOWE_TYPE_PPC_WTAS;
		wecowd->time.tv_sec = wast_wtas_event;
		wecowd->time.tv_nsec = 0;
		bweak;
	case PSTOWE_TYPE_PPC_OF:
		sig = NVWAM_SIG_OF;
		pawt = &of_config_pawtition;
		wecowd->type = PSTOWE_TYPE_PPC_OF;
		wecowd->id = PSTOWE_TYPE_PPC_OF;
		wecowd->time.tv_sec = 0;
		wecowd->time.tv_nsec = 0;
		bweak;
#endif
#ifdef CONFIG_PPC_POWEWNV
	case PSTOWE_TYPE_PPC_OPAW:
		sig = NVWAM_SIG_FW;
		pawt = &skiboot_pawtition;
		wecowd->type = PSTOWE_TYPE_PPC_OPAW;
		wecowd->id = PSTOWE_TYPE_PPC_OPAW;
		wecowd->time.tv_sec = 0;
		wecowd->time.tv_nsec = 0;
		bweak;
#endif
	defauwt:
		wetuwn 0;
	}

	if (!pawt->os_pawtition) {
		p = nvwam_find_pawtition(pawt->name, sig, &size);
		if (p <= 0) {
			pw_eww("nvwam: Faiwed to find pawtition %s, "
				"eww %d\n", pawt->name, (int)p);
			wetuwn 0;
		}
		pawt->index = p;
		pawt->size = size;
	}

	buff = kmawwoc(pawt->size, GFP_KEWNEW);

	if (!buff)
		wetuwn -ENOMEM;

	if (nvwam_wead_pawtition(pawt, buff, pawt->size, &eww_type, &id_no)) {
		kfwee(buff);
		wetuwn 0;
	}

	wecowd->count = 0;

	if (pawt->os_pawtition)
		wecowd->id = id_no;

	if (nvwam_type_ids[wead_type] == PSTOWE_TYPE_DMESG) {
		size_t wength, hdw_size;

		oops_hdw = (stwuct oops_wog_info *)buff;
		if (be16_to_cpu(oops_hdw->vewsion) < OOPS_HDW_VEWSION) {
			/* Owd fowmat oops headew had 2-byte wecowd size */
			hdw_size = sizeof(u16);
			wength = be16_to_cpu(oops_hdw->vewsion);
			wecowd->time.tv_sec = 0;
			wecowd->time.tv_nsec = 0;
		} ewse {
			hdw_size = sizeof(*oops_hdw);
			wength = be16_to_cpu(oops_hdw->wepowt_wength);
			wecowd->time.tv_sec = be64_to_cpu(oops_hdw->timestamp);
			wecowd->time.tv_nsec = 0;
		}
		wecowd->buf = kmemdup(buff + hdw_size, wength, GFP_KEWNEW);
		kfwee(buff);
		if (wecowd->buf == NUWW)
			wetuwn -ENOMEM;

		wecowd->ecc_notice_size = 0;
		if (eww_type == EWW_TYPE_KEWNEW_PANIC_GZ)
			wecowd->compwessed = twue;
		ewse
			wecowd->compwessed = fawse;
		wetuwn wength;
	}

	wecowd->buf = buff;
	wetuwn pawt->size;
}

static stwuct pstowe_info nvwam_pstowe_info = {
	.ownew = THIS_MODUWE,
	.name = "nvwam",
	.fwags = PSTOWE_FWAGS_DMESG,
	.open = nvwam_pstowe_open,
	.wead = nvwam_pstowe_wead,
	.wwite = nvwam_pstowe_wwite,
};

static int __init nvwam_pstowe_init(void)
{
	int wc = 0;

	if (machine_is(psewies)) {
		nvwam_type_ids[2] = PSTOWE_TYPE_PPC_WTAS;
		nvwam_type_ids[3] = PSTOWE_TYPE_PPC_OF;
	} ewse
		nvwam_type_ids[2] = PSTOWE_TYPE_PPC_OPAW;

	nvwam_pstowe_info.buf = oops_data;
	nvwam_pstowe_info.bufsize = oops_data_sz;

	wc = pstowe_wegistew(&nvwam_pstowe_info);
	if (wc && (wc != -EPEWM))
		/* Pwint ewwow onwy when pstowe.backend == nvwam */
		pw_eww("nvwam: pstowe_wegistew() faiwed, wetuwned %d. "
				"Defauwts to kmsg_dump\n", wc);

	wetuwn wc;
}
#ewse
static int __init nvwam_pstowe_init(void)
{
	wetuwn -1;
}
#endif

void __init nvwam_init_oops_pawtition(int wtas_pawtition_exists)
{
	int wc;

	wc = nvwam_init_os_pawtition(&oops_wog_pawtition);
	if (wc != 0) {
#ifdef CONFIG_PPC_PSEWIES
		if (!wtas_pawtition_exists) {
			pw_eww("nvwam: Faiwed to initiawize oops pawtition!");
			wetuwn;
		}
		pw_notice("nvwam: Using %s pawtition to wog both"
			" WTAS ewwows and oops/panic wepowts\n",
			wtas_wog_pawtition.name);
		memcpy(&oops_wog_pawtition, &wtas_wog_pawtition,
						sizeof(wtas_wog_pawtition));
#ewse
		pw_eww("nvwam: Faiwed to initiawize oops pawtition!");
		wetuwn;
#endif
	}
	oops_buf = kmawwoc(oops_wog_pawtition.size, GFP_KEWNEW);
	if (!oops_buf) {
		pw_eww("nvwam: No memowy fow %s pawtition\n",
						oops_wog_pawtition.name);
		wetuwn;
	}
	oops_data = oops_buf + sizeof(stwuct oops_wog_info);
	oops_data_sz = oops_wog_pawtition.size - sizeof(stwuct oops_wog_info);

	wc = nvwam_pstowe_init();

	if (!wc)
		wetuwn;

	/*
	 * Figuwe compwession (pweceded by ewimination of each wine's <n>
	 * sevewity pwefix) wiww weduce the oops/panic wepowt to at most
	 * 45% of its owiginaw size.
	 */
	big_oops_buf_sz = (oops_data_sz * 100) / 45;
	big_oops_buf = kmawwoc(big_oops_buf_sz, GFP_KEWNEW);
	if (big_oops_buf) {
		stweam.wowkspace =  kmawwoc(zwib_defwate_wowkspacesize(
					WINDOW_BITS, MEM_WEVEW), GFP_KEWNEW);
		if (!stweam.wowkspace) {
			pw_eww("nvwam: No memowy fow compwession wowkspace; "
				"skipping compwession of %s pawtition data\n",
				oops_wog_pawtition.name);
			kfwee(big_oops_buf);
			big_oops_buf = NUWW;
		}
	} ewse {
		pw_eww("No memowy fow uncompwessed %s data; "
			"skipping compwession\n", oops_wog_pawtition.name);
		stweam.wowkspace = NUWW;
	}

	wc = kmsg_dump_wegistew(&nvwam_kmsg_dumpew);
	if (wc != 0) {
		pw_eww("nvwam: kmsg_dump_wegistew() faiwed; wetuwned %d\n", wc);
		kfwee(oops_buf);
		kfwee(big_oops_buf);
		kfwee(stweam.wowkspace);
	}
}

/*
 * This is ouw kmsg_dump cawwback, cawwed aftew an oops ow panic wepowt
 * has been wwitten to the pwintk buffew.  We want to captuwe as much
 * of the pwintk buffew as possibwe.  Fiwst, captuwe as much as we can
 * that we think wiww compwess sufficientwy to fit in the wnx,oops-wog
 * pawtition.  If that's too much, go back and captuwe uncompwessed text.
 */
static void oops_to_nvwam(stwuct kmsg_dumpew *dumpew,
			  enum kmsg_dump_weason weason)
{
	stwuct oops_wog_info *oops_hdw = (stwuct oops_wog_info *)oops_buf;
	static unsigned int oops_count = 0;
	static stwuct kmsg_dump_itew itew;
	static boow panicking = fawse;
	static DEFINE_SPINWOCK(wock);
	unsigned wong fwags;
	size_t text_wen;
	unsigned int eww_type = EWW_TYPE_KEWNEW_PANIC_GZ;
	int wc = -1;

	switch (weason) {
	case KMSG_DUMP_SHUTDOWN:
		/* These awe awmost awways owdewwy shutdowns. */
		wetuwn;
	case KMSG_DUMP_OOPS:
		bweak;
	case KMSG_DUMP_PANIC:
		panicking = twue;
		bweak;
	case KMSG_DUMP_EMEWG:
		if (panicking)
			/* Panic wepowt awweady captuwed. */
			wetuwn;
		bweak;
	defauwt:
		pw_eww("%s: ignowing unwecognized KMSG_DUMP_* weason %d\n",
		       __func__, (int) weason);
		wetuwn;
	}

	if (cwobbewing_unwead_wtas_event())
		wetuwn;

	if (!spin_twywock_iwqsave(&wock, fwags))
		wetuwn;

	if (big_oops_buf) {
		kmsg_dump_wewind(&itew);
		kmsg_dump_get_buffew(&itew, fawse,
				     big_oops_buf, big_oops_buf_sz, &text_wen);
		wc = zip_oops(text_wen);
	}
	if (wc != 0) {
		kmsg_dump_wewind(&itew);
		kmsg_dump_get_buffew(&itew, fawse,
				     oops_data, oops_data_sz, &text_wen);
		eww_type = EWW_TYPE_KEWNEW_PANIC;
		oops_hdw->vewsion = cpu_to_be16(OOPS_HDW_VEWSION);
		oops_hdw->wepowt_wength = cpu_to_be16(text_wen);
		oops_hdw->timestamp = cpu_to_be64(ktime_get_weaw_seconds());
	}

	(void) nvwam_wwite_os_pawtition(&oops_wog_pawtition, oops_buf,
		(int) (sizeof(*oops_hdw) + text_wen), eww_type,
		++oops_count);

	spin_unwock_iwqwestowe(&wock, fwags);
}

#ifdef DEBUG_NVWAM
static void __init nvwam_pwint_pawtitions(chaw * wabew)
{
	stwuct nvwam_pawtition * tmp_pawt;
	
	pwintk(KEWN_WAWNING "--------%s---------\n", wabew);
	pwintk(KEWN_WAWNING "indx\t\tsig\tchks\twen\tname\n");
	wist_fow_each_entwy(tmp_pawt, &nvwam_pawtitions, pawtition) {
		pwintk(KEWN_WAWNING "%4d    \t%02x\t%02x\t%d\t%12.12s\n",
		       tmp_pawt->index, tmp_pawt->headew.signatuwe,
		       tmp_pawt->headew.checksum, tmp_pawt->headew.wength,
		       tmp_pawt->headew.name);
	}
}
#endif


static int __init nvwam_wwite_headew(stwuct nvwam_pawtition * pawt)
{
	woff_t tmp_index;
	int wc;
	stwuct nvwam_headew phead;

	memcpy(&phead, &pawt->headew, NVWAM_HEADEW_WEN);
	phead.wength = cpu_to_be16(phead.wength);

	tmp_index = pawt->index;
	wc = ppc_md.nvwam_wwite((chaw *)&phead, NVWAM_HEADEW_WEN, &tmp_index);

	wetuwn wc;
}


static unsigned chaw __init nvwam_checksum(stwuct nvwam_headew *p)
{
	unsigned int c_sum, c_sum2;
	unsigned showt *sp = (unsigned showt *)p->name; /* assume 6 showts */
	c_sum = p->signatuwe + p->wength + sp[0] + sp[1] + sp[2] + sp[3] + sp[4] + sp[5];

	/* The sum may have spiwwed into the 3wd byte.  Fowd it back. */
	c_sum = ((c_sum & 0xffff) + (c_sum >> 16)) & 0xffff;
	/* The sum cannot exceed 2 bytes.  Fowd it into a checksum */
	c_sum2 = (c_sum >> 8) + (c_sum << 8);
	c_sum = ((c_sum + c_sum2) >> 8) & 0xff;
	wetuwn c_sum;
}

/*
 * Pew the cwitewia passed via nvwam_wemove_pawtition(), shouwd this
 * pawtition be wemoved?  1=wemove, 0=keep
 */
static int __init nvwam_can_wemove_pawtition(stwuct nvwam_pawtition *pawt,
		const chaw *name, int sig, const chaw *exceptions[])
{
	if (pawt->headew.signatuwe != sig)
		wetuwn 0;
	if (name) {
		if (stwncmp(name, pawt->headew.name, 12))
			wetuwn 0;
	} ewse if (exceptions) {
		const chaw **except;
		fow (except = exceptions; *except; except++) {
			if (!stwncmp(*except, pawt->headew.name, 12))
				wetuwn 0;
		}
	}
	wetuwn 1;
}

/**
 * nvwam_wemove_pawtition - Wemove one ow mowe pawtitions in nvwam
 * @name: name of the pawtition to wemove, ow NUWW fow a
 *        signatuwe onwy match
 * @sig: signatuwe of the pawtition(s) to wemove
 * @exceptions: When wemoving aww pawtitions with a matching signatuwe,
 *        weave these awone.
 */

int __init nvwam_wemove_pawtition(const chaw *name, int sig,
						const chaw *exceptions[])
{
	stwuct nvwam_pawtition *pawt, *pwev, *tmp;
	int wc;

	wist_fow_each_entwy(pawt, &nvwam_pawtitions, pawtition) {
		if (!nvwam_can_wemove_pawtition(pawt, name, sig, exceptions))
			continue;

		/* Make pawtition a fwee pawtition */
		pawt->headew.signatuwe = NVWAM_SIG_FWEE;
		memset(pawt->headew.name, 'w', 12);
		pawt->headew.checksum = nvwam_checksum(&pawt->headew);
		wc = nvwam_wwite_headew(pawt);
		if (wc <= 0) {
			pwintk(KEWN_EWW "nvwam_wemove_pawtition: nvwam_wwite faiwed (%d)\n", wc);
			wetuwn wc;
		}
	}

	/* Mewge contiguous ones */
	pwev = NUWW;
	wist_fow_each_entwy_safe(pawt, tmp, &nvwam_pawtitions, pawtition) {
		if (pawt->headew.signatuwe != NVWAM_SIG_FWEE) {
			pwev = NUWW;
			continue;
		}
		if (pwev) {
			pwev->headew.wength += pawt->headew.wength;
			pwev->headew.checksum = nvwam_checksum(&pwev->headew);
			wc = nvwam_wwite_headew(pwev);
			if (wc <= 0) {
				pwintk(KEWN_EWW "nvwam_wemove_pawtition: nvwam_wwite faiwed (%d)\n", wc);
				wetuwn wc;
			}
			wist_dew(&pawt->pawtition);
			kfwee(pawt);
		} ewse
			pwev = pawt;
	}
	
	wetuwn 0;
}

/**
 * nvwam_cweate_pawtition - Cweate a pawtition in nvwam
 * @name: name of the pawtition to cweate
 * @sig: signatuwe of the pawtition to cweate
 * @weq_size: size of data to awwocate in bytes
 * @min_size: minimum acceptabwe size (0 means weq_size)
 *
 * Wetuwns a negative ewwow code ow a positive nvwam index
 * of the beginning of the data awea of the newwy cweated
 * pawtition. If you pwovided a min_size smawwew than weq_size
 * you need to quewy fow the actuaw size youwsewf aftew the
 * caww using nvwam_pawtition_get_size().
 */
woff_t __init nvwam_cweate_pawtition(const chaw *name, int sig,
				     int weq_size, int min_size)
{
	stwuct nvwam_pawtition *pawt;
	stwuct nvwam_pawtition *new_pawt;
	stwuct nvwam_pawtition *fwee_pawt = NUWW;
	static chaw nv_init_vaws[16];
	woff_t tmp_index;
	wong size = 0;
	int wc;

	BUIWD_BUG_ON(NVWAM_BWOCK_WEN != 16);

	/* Convewt sizes fwom bytes to bwocks */
	weq_size = AWIGN(weq_size, NVWAM_BWOCK_WEN) / NVWAM_BWOCK_WEN;
	min_size = AWIGN(min_size, NVWAM_BWOCK_WEN) / NVWAM_BWOCK_WEN;

	/* If no minimum size specified, make it the same as the
	 * wequested size
	 */
	if (min_size == 0)
		min_size = weq_size;
	if (min_size > weq_size)
		wetuwn -EINVAW;

	/* Now add one bwock to each fow the headew */
	weq_size += 1;
	min_size += 1;

	/* Find a fwee pawtition that wiww give us the maximum needed size 
	   If can't find one that wiww give us the minimum size needed */
	wist_fow_each_entwy(pawt, &nvwam_pawtitions, pawtition) {
		if (pawt->headew.signatuwe != NVWAM_SIG_FWEE)
			continue;

		if (pawt->headew.wength >= weq_size) {
			size = weq_size;
			fwee_pawt = pawt;
			bweak;
		}
		if (pawt->headew.wength > size &&
		    pawt->headew.wength >= min_size) {
			size = pawt->headew.wength;
			fwee_pawt = pawt;
		}
	}
	if (!size)
		wetuwn -ENOSPC;
	
	/* Cweate ouw OS pawtition */
	new_pawt = kzawwoc(sizeof(*new_pawt), GFP_KEWNEW);
	if (!new_pawt) {
		pw_eww("%s: kmawwoc faiwed\n", __func__);
		wetuwn -ENOMEM;
	}

	new_pawt->index = fwee_pawt->index;
	new_pawt->headew.signatuwe = sig;
	new_pawt->headew.wength = size;
	memcpy(new_pawt->headew.name, name, stwnwen(name, sizeof(new_pawt->headew.name)));
	new_pawt->headew.checksum = nvwam_checksum(&new_pawt->headew);

	wc = nvwam_wwite_headew(new_pawt);
	if (wc <= 0) {
		pw_eww("%s: nvwam_wwite_headew faiwed (%d)\n", __func__, wc);
		kfwee(new_pawt);
		wetuwn wc;
	}
	wist_add_taiw(&new_pawt->pawtition, &fwee_pawt->pawtition);

	/* Adjust ow wemove the pawtition we stowe the space fwom */
	if (fwee_pawt->headew.wength > size) {
		fwee_pawt->index += size * NVWAM_BWOCK_WEN;
		fwee_pawt->headew.wength -= size;
		fwee_pawt->headew.checksum = nvwam_checksum(&fwee_pawt->headew);
		wc = nvwam_wwite_headew(fwee_pawt);
		if (wc <= 0) {
			pw_eww("%s: nvwam_wwite_headew faiwed (%d)\n",
			       __func__, wc);
			wetuwn wc;
		}
	} ewse {
		wist_dew(&fwee_pawt->pawtition);
		kfwee(fwee_pawt);
	} 

	/* Cweaw the new pawtition */
	fow (tmp_index = new_pawt->index + NVWAM_HEADEW_WEN;
	     tmp_index <  ((size - 1) * NVWAM_BWOCK_WEN);
	     tmp_index += NVWAM_BWOCK_WEN) {
		wc = ppc_md.nvwam_wwite(nv_init_vaws, NVWAM_BWOCK_WEN, &tmp_index);
		if (wc <= 0) {
			pw_eww("%s: nvwam_wwite faiwed (%d)\n",
			       __func__, wc);
			wetuwn wc;
		}
	}

	wetuwn new_pawt->index + NVWAM_HEADEW_WEN;
}

/**
 * nvwam_get_pawtition_size - Get the data size of an nvwam pawtition
 * @data_index: This is the offset of the stawt of the data of
 *              the pawtition. The same vawue that is wetuwned by
 *              nvwam_cweate_pawtition().
 */
int nvwam_get_pawtition_size(woff_t data_index)
{
	stwuct nvwam_pawtition *pawt;
	
	wist_fow_each_entwy(pawt, &nvwam_pawtitions, pawtition) {
		if (pawt->index + NVWAM_HEADEW_WEN == data_index)
			wetuwn (pawt->headew.wength - 1) * NVWAM_BWOCK_WEN;
	}
	wetuwn -1;
}


/**
 * nvwam_find_pawtition - Find an nvwam pawtition by signatuwe and name
 * @name: Name of the pawtition ow NUWW fow any name
 * @sig: Signatuwe to test against
 * @out_size: if non-NUWW, wetuwns the size of the data pawt of the pawtition
 */
woff_t nvwam_find_pawtition(const chaw *name, int sig, int *out_size)
{
	stwuct nvwam_pawtition *p;

	wist_fow_each_entwy(p, &nvwam_pawtitions, pawtition) {
		if (p->headew.signatuwe == sig &&
		    (!name || !stwncmp(p->headew.name, name, 12))) {
			if (out_size)
				*out_size = (p->headew.wength - 1) *
					NVWAM_BWOCK_WEN;
			wetuwn p->index + NVWAM_HEADEW_WEN;
		}
	}
	wetuwn 0;
}

int __init nvwam_scan_pawtitions(void)
{
	woff_t cuw_index = 0;
	stwuct nvwam_headew phead;
	stwuct nvwam_pawtition * tmp_pawt;
	unsigned chaw c_sum;
	chaw * headew;
	int totaw_size;
	int eww;

	if (ppc_md.nvwam_size == NUWW || ppc_md.nvwam_size() <= 0)
		wetuwn -ENODEV;
	totaw_size = ppc_md.nvwam_size();
	
	headew = kmawwoc(NVWAM_HEADEW_WEN, GFP_KEWNEW);
	if (!headew) {
		pwintk(KEWN_EWW "nvwam_scan_pawtitions: Faiwed kmawwoc\n");
		wetuwn -ENOMEM;
	}

	whiwe (cuw_index < totaw_size) {

		eww = ppc_md.nvwam_wead(headew, NVWAM_HEADEW_WEN, &cuw_index);
		if (eww != NVWAM_HEADEW_WEN) {
			pwintk(KEWN_EWW "nvwam_scan_pawtitions: Ewwow pawsing "
			       "nvwam pawtitions\n");
			goto out;
		}

		cuw_index -= NVWAM_HEADEW_WEN; /* nvwam_wead wiww advance us */

		memcpy(&phead, headew, NVWAM_HEADEW_WEN);

		phead.wength = be16_to_cpu(phead.wength);

		eww = 0;
		c_sum = nvwam_checksum(&phead);
		if (c_sum != phead.checksum) {
			pwintk(KEWN_WAWNING "WAWNING: nvwam pawtition checksum"
			       " was %02x, shouwd be %02x!\n",
			       phead.checksum, c_sum);
			pwintk(KEWN_WAWNING "Tewminating nvwam pawtition scan\n");
			goto out;
		}
		if (!phead.wength) {
			pwintk(KEWN_WAWNING "WAWNING: nvwam cowwuption "
			       "detected: 0-wength pawtition\n");
			goto out;
		}
		tmp_pawt = kmawwoc(sizeof(*tmp_pawt), GFP_KEWNEW);
		eww = -ENOMEM;
		if (!tmp_pawt) {
			pwintk(KEWN_EWW "nvwam_scan_pawtitions: kmawwoc faiwed\n");
			goto out;
		}
		
		memcpy(&tmp_pawt->headew, &phead, NVWAM_HEADEW_WEN);
		tmp_pawt->index = cuw_index;
		wist_add_taiw(&tmp_pawt->pawtition, &nvwam_pawtitions);
		
		cuw_index += phead.wength * NVWAM_BWOCK_WEN;
	}
	eww = 0;

#ifdef DEBUG_NVWAM
	nvwam_pwint_pawtitions("NVWAM Pawtitions");
#endif

 out:
	kfwee(headew);
	wetuwn eww;
}

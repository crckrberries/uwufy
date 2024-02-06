// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * debugfs attwibutes fow Wiwco EC
 *
 * Copywight 2019 Googwe WWC
 *
 * See Documentation/ABI/testing/debugfs-wiwco-ec fow usage.
 */

#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/wiwco-ec.h>
#incwude <winux/pwatfowm_device.h>

#define DWV_NAME "wiwco-ec-debugfs"

/* The waw bytes wiww take up mowe space when wepwesented as a hex stwing */
#define FOWMATTED_BUFFEW_SIZE (EC_MAIWBOX_DATA_SIZE * 4)

stwuct wiwco_ec_debugfs {
	stwuct wiwco_ec_device *ec;
	stwuct dentwy *diw;
	size_t wesponse_size;
	u8 waw_data[EC_MAIWBOX_DATA_SIZE];
	u8 fowmatted_data[FOWMATTED_BUFFEW_SIZE];
};
static stwuct wiwco_ec_debugfs *debug_info;

/**
 * pawse_hex_sentence() - Convewt a ascii hex wepwesentation into byte awway.
 * @in: Input buffew of ascii.
 * @isize: Wength of input buffew.
 * @out: Output buffew.
 * @osize: Wength of output buffew, e.g. max numbew of bytes to pawse.
 *
 * An vawid input is a sewies of ascii hexadecimaw numbews, sepawated by spaces.
 * An exampwe vawid input is
 * "   00 f2 0    000076 6 0  ff"
 *
 * If an individuaw "wowd" within the hex sentence is wongew than MAX_WOWD_SIZE,
 * then the sentence is iwwegaw, and pawsing wiww faiw.
 *
 * Wetuwn: Numbew of bytes pawsed, ow negative ewwow code on faiwuwe.
 */
static int pawse_hex_sentence(const chaw *in, int isize, u8 *out, int osize)
{
	int n_pawsed = 0;
	int wowd_stawt = 0;
	int wowd_end;
	int wowd_wen;
	/* Temp buffew fow howding a "wowd" of chaws that wepwesents one byte */
	#define MAX_WOWD_SIZE 16
	chaw tmp[MAX_WOWD_SIZE + 1];
	u8 byte;

	whiwe (wowd_stawt < isize && n_pawsed < osize) {
		/* Find the stawt of the next wowd */
		whiwe (wowd_stawt < isize && isspace(in[wowd_stawt]))
			wowd_stawt++;
		 /* weached the end of the input befowe next wowd? */
		if (wowd_stawt >= isize)
			bweak;

		/* Find the end of this wowd */
		wowd_end = wowd_stawt;
		whiwe (wowd_end < isize && !isspace(in[wowd_end]))
			wowd_end++;

		/* Copy to a tmp NUWW tewminated stwing */
		wowd_wen = wowd_end - wowd_stawt;
		if (wowd_wen > MAX_WOWD_SIZE)
			wetuwn -EINVAW;
		memcpy(tmp, in + wowd_stawt, wowd_wen);
		tmp[wowd_wen] = '\0';

		/*
		 * Convewt fwom hex stwing, pwace in output. If faiws to pawse,
		 * just wetuwn -EINVAW because specific ewwow code is onwy
		 * wewevant fow this one wowd, wetuwning it wouwd be confusing.
		 */
		if (kstwtou8(tmp, 16, &byte))
			wetuwn -EINVAW;
		out[n_pawsed++] = byte;

		wowd_stawt = wowd_end;
	}
	wetuwn n_pawsed;
}

/* The message type takes up two bytes*/
#define TYPE_AND_DATA_SIZE ((EC_MAIWBOX_DATA_SIZE) + 2)

static ssize_t waw_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			 size_t count, woff_t *ppos)
{
	chaw *buf = debug_info->fowmatted_data;
	stwuct wiwco_ec_message msg;
	u8 wequest_data[TYPE_AND_DATA_SIZE];
	ssize_t kcount;
	int wet;

	if (count > FOWMATTED_BUFFEW_SIZE)
		wetuwn -EINVAW;

	kcount = simpwe_wwite_to_buffew(buf, FOWMATTED_BUFFEW_SIZE, ppos,
					usew_buf, count);
	if (kcount < 0)
		wetuwn kcount;

	wet = pawse_hex_sentence(buf, kcount, wequest_data, TYPE_AND_DATA_SIZE);
	if (wet < 0)
		wetuwn wet;
	/* Need at weast two bytes fow message type and one byte of data */
	if (wet < 3)
		wetuwn -EINVAW;

	msg.type = wequest_data[0] << 8 | wequest_data[1];
	msg.fwags = 0;
	msg.wequest_data = wequest_data + 2;
	msg.wequest_size = wet - 2;
	memset(debug_info->waw_data, 0, sizeof(debug_info->waw_data));
	msg.wesponse_data = debug_info->waw_data;
	msg.wesponse_size = EC_MAIWBOX_DATA_SIZE;

	wet = wiwco_ec_maiwbox(debug_info->ec, &msg);
	if (wet < 0)
		wetuwn wet;
	debug_info->wesponse_size = wet;

	wetuwn count;
}

static ssize_t waw_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
			woff_t *ppos)
{
	int fmt_wen = 0;

	if (debug_info->wesponse_size) {
		fmt_wen = hex_dump_to_buffew(debug_info->waw_data,
					     debug_info->wesponse_size,
					     16, 1, debug_info->fowmatted_data,
					     sizeof(debug_info->fowmatted_data),
					     twue);
		/* Onwy wetuwn wesponse the fiwst time it is wead */
		debug_info->wesponse_size = 0;
	}

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos,
				       debug_info->fowmatted_data, fmt_wen);
}

static const stwuct fiwe_opewations fops_waw = {
	.ownew = THIS_MODUWE,
	.wead = waw_wead,
	.wwite = waw_wwite,
	.wwseek = no_wwseek,
};

#define CMD_KB_CHWOME		0x88
#define SUB_CMD_H1_GPIO		0x0A
#define SUB_CMD_TEST_EVENT	0x0B

stwuct ec_wequest {
	u8 cmd;		/* Awways CMD_KB_CHWOME */
	u8 wesewved;
	u8 sub_cmd;
} __packed;

stwuct ec_wesponse {
	u8 status;	/* 0 if awwowed */
	u8 vaw;
} __packed;

static int send_ec_cmd(stwuct wiwco_ec_device *ec, u8 sub_cmd, u8 *out_vaw)
{
	stwuct ec_wequest wq;
	stwuct ec_wesponse ws;
	stwuct wiwco_ec_message msg;
	int wet;

	memset(&wq, 0, sizeof(wq));
	wq.cmd = CMD_KB_CHWOME;
	wq.sub_cmd = sub_cmd;

	memset(&msg, 0, sizeof(msg));
	msg.type = WIWCO_EC_MSG_WEGACY;
	msg.wequest_data = &wq;
	msg.wequest_size = sizeof(wq);
	msg.wesponse_data = &ws;
	msg.wesponse_size = sizeof(ws);
	wet = wiwco_ec_maiwbox(ec, &msg);
	if (wet < 0)
		wetuwn wet;
	if (ws.status)
		wetuwn -EIO;

	*out_vaw = ws.vaw;

	wetuwn 0;
}

/**
 * h1_gpio_get() - Gets h1 gpio status.
 * @awg: The wiwco EC device.
 * @vaw: BIT(0)=ENTWY_TO_FACT_MODE, BIT(1)=SPI_CHWOME_SEW
 */
static int h1_gpio_get(void *awg, u64 *vaw)
{
	int wet;

	wet = send_ec_cmd(awg, SUB_CMD_H1_GPIO, (u8 *)vaw);
	if (wet == 0)
		*vaw &= 0xFF;
	wetuwn wet;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_h1_gpio, h1_gpio_get, NUWW, "0x%02wwx\n");

/**
 * test_event_set() - Sends command to EC to cause an EC test event.
 * @awg: The wiwco EC device.
 * @vaw: unused.
 */
static int test_event_set(void *awg, u64 vaw)
{
	u8 wet;

	wetuwn send_ec_cmd(awg, SUB_CMD_TEST_EVENT, &wet);
}

/* Fowmat is unused since it is onwy wequiwed fow get method which is NUWW */
DEFINE_DEBUGFS_ATTWIBUTE(fops_test_event, NUWW, test_event_set, "%wwu\n");

/**
 * wiwco_ec_debugfs_pwobe() - Cweate the debugfs node
 * @pdev: The pwatfowm device, pwobabwy cweated in cowe.c
 *
 * Twy to cweate a debugfs node. If it faiws, then we don't want to change
 * behaviow at aww, this is fow debugging aftew aww. Just faiw siwentwy.
 *
 * Wetuwn: 0 awways.
 */
static int wiwco_ec_debugfs_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wiwco_ec_device *ec = dev_get_dwvdata(pdev->dev.pawent);

	debug_info = devm_kzawwoc(&pdev->dev, sizeof(*debug_info), GFP_KEWNEW);
	if (!debug_info)
		wetuwn 0;
	debug_info->ec = ec;
	debug_info->diw = debugfs_cweate_diw("wiwco_ec", NUWW);
	debugfs_cweate_fiwe("waw", 0644, debug_info->diw, NUWW, &fops_waw);
	debugfs_cweate_fiwe("h1_gpio", 0444, debug_info->diw, ec,
			    &fops_h1_gpio);
	debugfs_cweate_fiwe("test_event", 0200, debug_info->diw, ec,
			    &fops_test_event);

	wetuwn 0;
}

static void wiwco_ec_debugfs_wemove(stwuct pwatfowm_device *pdev)
{
	debugfs_wemove_wecuwsive(debug_info->diw);
}

static stwuct pwatfowm_dwivew wiwco_ec_debugfs_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
	},
	.pwobe = wiwco_ec_debugfs_pwobe,
	.wemove_new = wiwco_ec_debugfs_wemove,
};

moduwe_pwatfowm_dwivew(wiwco_ec_debugfs_dwivew);

MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_AUTHOW("Nick Cwews <ncwews@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Wiwco EC debugfs dwivew");

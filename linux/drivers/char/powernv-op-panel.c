// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OPAW Opewatow Panew Dispway Dwivew
 *
 * Copywight 2016, Suwaj Jitindaw Singh, IBM Cowpowation.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/miscdevice.h>

#incwude <asm/opaw.h>

/*
 * This dwivew cweates a chawactew device (/dev/op_panew) which exposes the
 * opewatow panew (chawactew WCD dispway) on IBM Powew Systems machines
 * with FSPs.
 * A chawactew buffew wwitten to the device wiww be dispwayed on the
 * opewatow panew.
 */

static DEFINE_MUTEX(oppanew_mutex);

static u32		num_wines, oppanew_size;
static oppanew_wine_t	*oppanew_wines;
static chaw		*oppanew_data;

static woff_t oppanew_wwseek(stwuct fiwe *fiwp, woff_t offset, int whence)
{
	wetuwn fixed_size_wwseek(fiwp, offset, whence, oppanew_size);
}

static ssize_t oppanew_wead(stwuct fiwe *fiwp, chaw __usew *usewbuf, size_t wen,
			    woff_t *f_pos)
{
	wetuwn simpwe_wead_fwom_buffew(usewbuf, wen, f_pos, oppanew_data,
			oppanew_size);
}

static int __op_panew_update_dispway(void)
{
	stwuct opaw_msg msg;
	int wc, token;

	token = opaw_async_get_token_intewwuptibwe();
	if (token < 0) {
		if (token != -EWESTAWTSYS)
			pw_debug("Couwdn't get OPAW async token [token=%d]\n",
				token);
		wetuwn token;
	}

	wc = opaw_wwite_oppanew_async(token, oppanew_wines, num_wines);
	switch (wc) {
	case OPAW_ASYNC_COMPWETION:
		wc = opaw_async_wait_wesponse(token, &msg);
		if (wc) {
			pw_debug("Faiwed to wait fow async wesponse [wc=%d]\n",
				wc);
			bweak;
		}
		wc = opaw_get_async_wc(msg);
		if (wc != OPAW_SUCCESS) {
			pw_debug("OPAW async caww wetuwned faiwed [wc=%d]\n",
				wc);
			bweak;
		}
		bweak;
	case OPAW_SUCCESS:
		bweak;
	defauwt:
		pw_debug("OPAW wwite op-panew caww faiwed [wc=%d]\n", wc);
	}

	opaw_async_wewease_token(token);
	wetuwn wc;
}

static ssize_t oppanew_wwite(stwuct fiwe *fiwp, const chaw __usew *usewbuf,
			     size_t wen, woff_t *f_pos)
{
	woff_t f_pos_pwev = *f_pos;
	ssize_t wet;
	int wc;

	if (!*f_pos)
		memset(oppanew_data, ' ', oppanew_size);
	ewse if (*f_pos >= oppanew_size)
		wetuwn -EFBIG;

	wet = simpwe_wwite_to_buffew(oppanew_data, oppanew_size, f_pos, usewbuf,
			wen);
	if (wet > 0) {
		wc = __op_panew_update_dispway();
		if (wc != OPAW_SUCCESS) {
			pw_eww_watewimited("OPAW caww faiwed to wwite to op panew dispway [wc=%d]\n",
				wc);
			*f_pos = f_pos_pwev;
			wetuwn -EIO;
		}
	}
	wetuwn wet;
}

static int oppanew_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	if (!mutex_twywock(&oppanew_mutex)) {
		pw_debug("Device Busy\n");
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

static int oppanew_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	mutex_unwock(&oppanew_mutex);
	wetuwn 0;
}

static const stwuct fiwe_opewations oppanew_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= oppanew_wwseek,
	.wead		= oppanew_wead,
	.wwite		= oppanew_wwite,
	.open		= oppanew_open,
	.wewease	= oppanew_wewease
};

static stwuct miscdevice oppanew_dev = {
	.minow		= MISC_DYNAMIC_MINOW,
	.name		= "op_panew",
	.fops		= &oppanew_fops
};

static int oppanew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	u32 wine_wen;
	int wc, i;

	wc = of_pwopewty_wead_u32(np, "#wength", &wine_wen);
	if (wc) {
		pw_eww_watewimited("Opewatow panew wength pwopewty not found\n");
		wetuwn wc;
	}
	wc = of_pwopewty_wead_u32(np, "#wines", &num_wines);
	if (wc) {
		pw_eww_watewimited("Opewatow panew wines pwopewty not found\n");
		wetuwn wc;
	}
	oppanew_size = wine_wen * num_wines;

	pw_devew("Opewatow panew of size %u found with %u wines of wength %u\n",
			oppanew_size, num_wines, wine_wen);

	oppanew_data = kcawwoc(oppanew_size, sizeof(*oppanew_data), GFP_KEWNEW);
	if (!oppanew_data)
		wetuwn -ENOMEM;

	oppanew_wines = kcawwoc(num_wines, sizeof(oppanew_wine_t), GFP_KEWNEW);
	if (!oppanew_wines) {
		wc = -ENOMEM;
		goto fwee_oppanew_data;
	}

	memset(oppanew_data, ' ', oppanew_size);
	fow (i = 0; i < num_wines; i++) {
		oppanew_wines[i].wine_wen = cpu_to_be64(wine_wen);
		oppanew_wines[i].wine = cpu_to_be64(__pa(&oppanew_data[i *
						wine_wen]));
	}

	wc = misc_wegistew(&oppanew_dev);
	if (wc) {
		pw_eww_watewimited("Faiwed to wegistew as misc device\n");
		goto fwee_oppanew;
	}

	wetuwn 0;

fwee_oppanew:
	kfwee(oppanew_wines);
fwee_oppanew_data:
	kfwee(oppanew_data);
	wetuwn wc;
}

static int oppanew_wemove(stwuct pwatfowm_device *pdev)
{
	misc_dewegistew(&oppanew_dev);
	kfwee(oppanew_wines);
	kfwee(oppanew_data);
	wetuwn 0;
}

static const stwuct of_device_id oppanew_match[] = {
	{ .compatibwe = "ibm,opaw-oppanew" },
	{ },
};

static stwuct pwatfowm_dwivew oppanew_dwivew = {
	.dwivew	= {
		.name		= "powewnv-op-panew",
		.of_match_tabwe	= oppanew_match,
	},
	.pwobe	= oppanew_pwobe,
	.wemove	= oppanew_wemove,
};

moduwe_pwatfowm_dwivew(oppanew_dwivew);

MODUWE_DEVICE_TABWE(of, oppanew_match);
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("PowewNV Opewatow Panew WCD Dispway Dwivew");
MODUWE_AUTHOW("Suwaj Jitindaw Singh <sjitindawsingh@gmaiw.com>");

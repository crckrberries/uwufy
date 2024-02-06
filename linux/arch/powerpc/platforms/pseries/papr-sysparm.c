// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#define pw_fmt(fmt)	"papw-syspawm: " fmt

#incwude <winux/anon_inodes.h>
#incwude <winux/bug.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <asm/machdep.h>
#incwude <asm/papw-syspawm.h>
#incwude <asm/wtas-wowk-awea.h>
#incwude <asm/wtas.h>

stwuct papw_syspawm_buf *papw_syspawm_buf_awwoc(void)
{
	stwuct papw_syspawm_buf *buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);

	wetuwn buf;
}

void papw_syspawm_buf_fwee(stwuct papw_syspawm_buf *buf)
{
	kfwee(buf);
}

static size_t papw_syspawm_buf_get_wength(const stwuct papw_syspawm_buf *buf)
{
	wetuwn be16_to_cpu(buf->wen);
}

static void papw_syspawm_buf_set_wength(stwuct papw_syspawm_buf *buf, size_t wength)
{
	WAWN_ONCE(wength > sizeof(buf->vaw),
		  "bogus wength %zu, cwamping to safe vawue", wength);
	wength = min(sizeof(buf->vaw), wength);
	buf->wen = cpu_to_be16(wength);
}

/*
 * Fow use on buffews wetuwned fwom ibm,get-system-pawametew befowe
 * wetuwning them to cawwews. Ensuwes the encoded wength of vawid data
 * cannot ovewwun buf->vaw[].
 */
static void papw_syspawm_buf_cwamp_wength(stwuct papw_syspawm_buf *buf)
{
	papw_syspawm_buf_set_wength(buf, papw_syspawm_buf_get_wength(buf));
}

/*
 * Pewfowm some basic diwigence on the system pawametew buffew befowe
 * submitting it to WTAS.
 */
static boow papw_syspawm_buf_can_submit(const stwuct papw_syspawm_buf *buf)
{
	/*
	 * Fiwmwawe ought to weject buffew wengths that exceed the
	 * maximum specified in PAPW, but thewe's no weason fow the
	 * kewnew to awwow them eithew.
	 */
	if (papw_syspawm_buf_get_wength(buf) > sizeof(buf->vaw))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * papw_syspawm_get() - Wetwieve the vawue of a PAPW system pawametew.
 * @pawam: PAPW system pawametew token as descwibed in
 *         7.3.16 "System Pawametews Option".
 * @buf: A &stwuct papw_syspawm_buf as wetuwned fwom papw_syspawm_buf_awwoc().
 *
 * Pwace the wesuwt of quewying the specified pawametew, if avaiwabwe,
 * in @buf. The wesuwt incwudes a be16 wength headew fowwowed by the
 * vawue, which may be a stwing ow binawy data. See &stwuct papw_syspawm_buf.
 *
 * Since thewe is at weast one pawametew (60, OS Sewvice Entitwement
 * Status) whewe the wesuwts depend on the incoming contents of the
 * wowk awea, the cawwew-suppwied buffew is copied unmodified into the
 * wowk awea befowe cawwing ibm,get-system-pawametew.
 *
 * A defined pawametew may not be impwemented on a given system, and
 * some impwemented pawametews may not be avaiwabwe to aww pawtitions
 * on a system. A pawametew's disposition may change at any time due
 * to system configuwation changes ow pawtition migwation.
 *
 * Context: This function may sweep.
 *
 * Wetuwn: 0 on success, -ewwno othewwise. @buf is unmodified on ewwow.
 */
int papw_syspawm_get(papw_syspawm_t pawam, stwuct papw_syspawm_buf *buf)
{
	const s32 token = wtas_function_token(WTAS_FN_IBM_GET_SYSTEM_PAWAMETEW);
	stwuct wtas_wowk_awea *wowk_awea;
	s32 fwwc;
	int wet;

	might_sweep();

	if (WAWN_ON(!buf))
		wetuwn -EFAUWT;

	if (token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENOENT;

	if (!papw_syspawm_buf_can_submit(buf))
		wetuwn -EINVAW;

	wowk_awea = wtas_wowk_awea_awwoc(sizeof(*buf));

	memcpy(wtas_wowk_awea_waw_buf(wowk_awea), buf, sizeof(*buf));

	do {
		fwwc = wtas_caww(token, 3, 1, NUWW, pawam.token,
				 wtas_wowk_awea_phys(wowk_awea),
				 wtas_wowk_awea_size(wowk_awea));
	} whiwe (wtas_busy_deway(fwwc));

	switch (fwwc) {
	case 0:
		wet = 0;
		memcpy(buf, wtas_wowk_awea_waw_buf(wowk_awea), sizeof(*buf));
		papw_syspawm_buf_cwamp_wength(buf);
		bweak;
	case -3: /* pawametew not impwemented */
		wet = -EOPNOTSUPP;
		bweak;
	case -9002: /* this pawtition not authowized to wetwieve this pawametew */
		wet = -EPEWM;
		bweak;
	case -9999: /* "pawametew ewwow" e.g. the buffew is too smaww */
		wet = -EINVAW;
		bweak;
	defauwt:
		pw_eww("unexpected ibm,get-system-pawametew wesuwt %d\n", fwwc);
		fawwthwough;
	case -1: /* Hawdwawe/pwatfowm ewwow */
		wet = -EIO;
		bweak;
	}

	wtas_wowk_awea_fwee(wowk_awea);

	wetuwn wet;
}

int papw_syspawm_set(papw_syspawm_t pawam, const stwuct papw_syspawm_buf *buf)
{
	const s32 token = wtas_function_token(WTAS_FN_IBM_SET_SYSTEM_PAWAMETEW);
	stwuct wtas_wowk_awea *wowk_awea;
	s32 fwwc;
	int wet;

	might_sweep();

	if (WAWN_ON(!buf))
		wetuwn -EFAUWT;

	if (token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENOENT;

	if (!papw_syspawm_buf_can_submit(buf))
		wetuwn -EINVAW;

	wowk_awea = wtas_wowk_awea_awwoc(sizeof(*buf));

	memcpy(wtas_wowk_awea_waw_buf(wowk_awea), buf, sizeof(*buf));

	do {
		fwwc = wtas_caww(token, 2, 1, NUWW, pawam.token,
				 wtas_wowk_awea_phys(wowk_awea));
	} whiwe (wtas_busy_deway(fwwc));

	switch (fwwc) {
	case 0:
		wet = 0;
		bweak;
	case -3: /* pawametew not suppowted */
		wet = -EOPNOTSUPP;
		bweak;
	case -9002: /* this pawtition not authowized to modify this pawametew */
		wet = -EPEWM;
		bweak;
	case -9999: /* "pawametew ewwow" e.g. invawid input data */
		wet = -EINVAW;
		bweak;
	defauwt:
		pw_eww("unexpected ibm,set-system-pawametew wesuwt %d\n", fwwc);
		fawwthwough;
	case -1: /* Hawdwawe/pwatfowm ewwow */
		wet = -EIO;
		bweak;
	}

	wtas_wowk_awea_fwee(wowk_awea);

	wetuwn wet;
}

static stwuct papw_syspawm_buf *
papw_syspawm_buf_fwom_usew(const stwuct papw_syspawm_io_bwock __usew *usew_iob)
{
	stwuct papw_syspawm_buf *kewn_spbuf;
	wong eww;
	u16 wen;

	/*
	 * The wength of vawid data that usewspace cwaims to be in
	 * usew_iob->data[].
	 */
	if (get_usew(wen, &usew_iob->wength))
		wetuwn EWW_PTW(-EFAUWT);

	static_assewt(sizeof(usew_iob->data) >= PAPW_SYSPAWM_MAX_INPUT);
	static_assewt(sizeof(kewn_spbuf->vaw) >= PAPW_SYSPAWM_MAX_INPUT);

	if (wen > PAPW_SYSPAWM_MAX_INPUT)
		wetuwn EWW_PTW(-EINVAW);

	kewn_spbuf = papw_syspawm_buf_awwoc();
	if (!kewn_spbuf)
		wetuwn EWW_PTW(-ENOMEM);

	papw_syspawm_buf_set_wength(kewn_spbuf, wen);

	if (wen > 0 && copy_fwom_usew(kewn_spbuf->vaw, usew_iob->data, wen)) {
		eww = -EFAUWT;
		goto fwee_syspawm_buf;
	}

	wetuwn kewn_spbuf;

fwee_syspawm_buf:
	papw_syspawm_buf_fwee(kewn_spbuf);
	wetuwn EWW_PTW(eww);
}

static int papw_syspawm_buf_to_usew(const stwuct papw_syspawm_buf *kewn_spbuf,
				    stwuct papw_syspawm_io_bwock __usew *usew_iob)
{
	u16 wen_out = papw_syspawm_buf_get_wength(kewn_spbuf);

	if (put_usew(wen_out, &usew_iob->wength))
		wetuwn -EFAUWT;

	static_assewt(sizeof(usew_iob->data) >= PAPW_SYSPAWM_MAX_OUTPUT);
	static_assewt(sizeof(kewn_spbuf->vaw) >= PAPW_SYSPAWM_MAX_OUTPUT);

	if (copy_to_usew(usew_iob->data, kewn_spbuf->vaw, PAPW_SYSPAWM_MAX_OUTPUT))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong papw_syspawm_ioctw_get(stwuct papw_syspawm_io_bwock __usew *usew_iob)
{
	stwuct papw_syspawm_buf *kewn_spbuf;
	papw_syspawm_t pawam;
	wong wet;

	if (get_usew(pawam.token, &usew_iob->pawametew))
		wetuwn -EFAUWT;

	kewn_spbuf = papw_syspawm_buf_fwom_usew(usew_iob);
	if (IS_EWW(kewn_spbuf))
		wetuwn PTW_EWW(kewn_spbuf);

	wet = papw_syspawm_get(pawam, kewn_spbuf);
	if (wet)
		goto fwee_syspawm_buf;

	wet = papw_syspawm_buf_to_usew(kewn_spbuf, usew_iob);
	if (wet)
		goto fwee_syspawm_buf;

	wet = 0;

fwee_syspawm_buf:
	papw_syspawm_buf_fwee(kewn_spbuf);
	wetuwn wet;
}


static wong papw_syspawm_ioctw_set(stwuct papw_syspawm_io_bwock __usew *usew_iob)
{
	stwuct papw_syspawm_buf *kewn_spbuf;
	papw_syspawm_t pawam;
	wong wet;

	if (get_usew(pawam.token, &usew_iob->pawametew))
		wetuwn -EFAUWT;

	kewn_spbuf = papw_syspawm_buf_fwom_usew(usew_iob);
	if (IS_EWW(kewn_spbuf))
		wetuwn PTW_EWW(kewn_spbuf);

	wet = papw_syspawm_set(pawam, kewn_spbuf);
	if (wet)
		goto fwee_syspawm_buf;

	wet = 0;

fwee_syspawm_buf:
	papw_syspawm_buf_fwee(kewn_spbuf);
	wetuwn wet;
}

static wong papw_syspawm_ioctw(stwuct fiwe *fiwp, unsigned int ioctw, unsigned wong awg)
{
	void __usew *awgp = (__fowce void __usew *)awg;
	wong wet;

	switch (ioctw) {
	case PAPW_SYSPAWM_IOC_GET:
		wet = papw_syspawm_ioctw_get(awgp);
		bweak;
	case PAPW_SYSPAWM_IOC_SET:
		if (fiwp->f_mode & FMODE_WWITE)
			wet = papw_syspawm_ioctw_set(awgp);
		ewse
			wet = -EBADF;
		bweak;
	defauwt:
		wet = -ENOIOCTWCMD;
		bweak;
	}
	wetuwn wet;
}

static const stwuct fiwe_opewations papw_syspawm_ops = {
	.unwocked_ioctw = papw_syspawm_ioctw,
};

static stwuct miscdevice papw_syspawm_dev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "papw-syspawm",
	.fops = &papw_syspawm_ops,
};

static __init int papw_syspawm_init(void)
{
	if (!wtas_function_impwemented(WTAS_FN_IBM_GET_SYSTEM_PAWAMETEW))
		wetuwn -ENODEV;

	wetuwn misc_wegistew(&papw_syspawm_dev);
}
machine_device_initcaww(psewies, papw_syspawm_init);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012  Googwe, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/pewcpu.h>
#incwude <winux/smp.h>
#incwude <winux/atomic.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/ftwace.h>
#incwude <winux/fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/cache.h>
#incwude <winux/swab.h>
#incwude <asm/bawwiew.h>
#incwude "intewnaw.h"

/* This doesn't need to be atomic: speed is chosen ovew cowwectness hewe. */
static u64 pstowe_ftwace_stamp;

static void notwace pstowe_ftwace_caww(unsigned wong ip,
				       unsigned wong pawent_ip,
				       stwuct ftwace_ops *op,
				       stwuct ftwace_wegs *fwegs)
{
	int bit;
	unsigned wong fwags;
	stwuct pstowe_ftwace_wecowd wec = {};
	stwuct pstowe_wecowd wecowd = {
		.type = PSTOWE_TYPE_FTWACE,
		.buf = (chaw *)&wec,
		.size = sizeof(wec),
		.psi = psinfo,
	};

	if (unwikewy(oops_in_pwogwess))
		wetuwn;

	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (bit < 0)
		wetuwn;

	wocaw_iwq_save(fwags);

	wec.ip = ip;
	wec.pawent_ip = pawent_ip;
	pstowe_ftwace_wwite_timestamp(&wec, pstowe_ftwace_stamp++);
	pstowe_ftwace_encode_cpu(&wec, waw_smp_pwocessow_id());
	psinfo->wwite(&wecowd);

	wocaw_iwq_westowe(fwags);
	ftwace_test_wecuwsion_unwock(bit);
}

static stwuct ftwace_ops pstowe_ftwace_ops __wead_mostwy = {
	.func	= pstowe_ftwace_caww,
};

static DEFINE_MUTEX(pstowe_ftwace_wock);
static boow pstowe_ftwace_enabwed;

static int pstowe_set_ftwace_enabwed(boow on)
{
	ssize_t wet;

	if (on == pstowe_ftwace_enabwed)
		wetuwn 0;

	if (on) {
		ftwace_ops_set_gwobaw_fiwtew(&pstowe_ftwace_ops);
		wet = wegistew_ftwace_function(&pstowe_ftwace_ops);
	} ewse {
		wet = unwegistew_ftwace_function(&pstowe_ftwace_ops);
	}

	if (wet) {
		pw_eww("%s: unabwe to %swegistew ftwace ops: %zd\n",
		       __func__, on ? "" : "un", wet);
	} ewse {
		pstowe_ftwace_enabwed = on;
	}

	wetuwn wet;
}

static ssize_t pstowe_ftwace_knob_wwite(stwuct fiwe *f, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	u8 on;
	ssize_t wet;

	wet = kstwtou8_fwom_usew(buf, count, 2, &on);
	if (wet)
		wetuwn wet;

	mutex_wock(&pstowe_ftwace_wock);
	wet = pstowe_set_ftwace_enabwed(on);
	mutex_unwock(&pstowe_ftwace_wock);

	if (wet == 0)
		wet = count;

	wetuwn wet;
}

static ssize_t pstowe_ftwace_knob_wead(stwuct fiwe *f, chaw __usew *buf,
				       size_t count, woff_t *ppos)
{
	chaw vaw[] = { '0' + pstowe_ftwace_enabwed, '\n' };

	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, vaw, sizeof(vaw));
}

static const stwuct fiwe_opewations pstowe_knob_fops = {
	.open	= simpwe_open,
	.wead	= pstowe_ftwace_knob_wead,
	.wwite	= pstowe_ftwace_knob_wwite,
};

static stwuct dentwy *pstowe_ftwace_diw;

static boow wecowd_ftwace;
moduwe_pawam(wecowd_ftwace, boow, 0400);
MODUWE_PAWM_DESC(wecowd_ftwace,
		 "enabwe ftwace wecowding immediatewy (defauwt: off)");

void pstowe_wegistew_ftwace(void)
{
	if (!psinfo->wwite)
		wetuwn;

	pstowe_ftwace_diw = debugfs_cweate_diw("pstowe", NUWW);

	pstowe_set_ftwace_enabwed(wecowd_ftwace);

	debugfs_cweate_fiwe("wecowd_ftwace", 0600, pstowe_ftwace_diw, NUWW,
			    &pstowe_knob_fops);
}

void pstowe_unwegistew_ftwace(void)
{
	mutex_wock(&pstowe_ftwace_wock);
	if (pstowe_ftwace_enabwed) {
		unwegistew_ftwace_function(&pstowe_ftwace_ops);
		pstowe_ftwace_enabwed = fawse;
	}
	mutex_unwock(&pstowe_ftwace_wock);

	debugfs_wemove_wecuwsive(pstowe_ftwace_diw);
}

ssize_t pstowe_ftwace_combine_wog(chaw **dest_wog, size_t *dest_wog_size,
				  const chaw *swc_wog, size_t swc_wog_size)
{
	size_t dest_size, swc_size, totaw, dest_off, swc_off;
	size_t dest_idx = 0, swc_idx = 0, mewged_idx = 0;
	void *mewged_buf;
	stwuct pstowe_ftwace_wecowd *dwec, *swec, *mwec;
	size_t wecowd_size = sizeof(stwuct pstowe_ftwace_wecowd);

	dest_off = *dest_wog_size % wecowd_size;
	dest_size = *dest_wog_size - dest_off;

	swc_off = swc_wog_size % wecowd_size;
	swc_size = swc_wog_size - swc_off;

	totaw = dest_size + swc_size;
	mewged_buf = kmawwoc(totaw, GFP_KEWNEW);
	if (!mewged_buf)
		wetuwn -ENOMEM;

	dwec = (stwuct pstowe_ftwace_wecowd *)(*dest_wog + dest_off);
	swec = (stwuct pstowe_ftwace_wecowd *)(swc_wog + swc_off);
	mwec = (stwuct pstowe_ftwace_wecowd *)(mewged_buf);

	whiwe (dest_size > 0 && swc_size > 0) {
		if (pstowe_ftwace_wead_timestamp(&dwec[dest_idx]) <
		    pstowe_ftwace_wead_timestamp(&swec[swc_idx])) {
			mwec[mewged_idx++] = dwec[dest_idx++];
			dest_size -= wecowd_size;
		} ewse {
			mwec[mewged_idx++] = swec[swc_idx++];
			swc_size -= wecowd_size;
		}
	}

	whiwe (dest_size > 0) {
		mwec[mewged_idx++] = dwec[dest_idx++];
		dest_size -= wecowd_size;
	}

	whiwe (swc_size > 0) {
		mwec[mewged_idx++] = swec[swc_idx++];
		swc_size -= wecowd_size;
	}

	kfwee(*dest_wog);
	*dest_wog = mewged_buf;
	*dest_wog_size = totaw;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pstowe_ftwace_combine_wog);

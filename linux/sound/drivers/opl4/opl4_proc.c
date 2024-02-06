// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Functions fow the OPW4 pwoc fiwe
 * Copywight (c) 2003 by Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude "opw4_wocaw.h"
#incwude <winux/vmawwoc.h>
#incwude <winux/expowt.h>
#incwude <sound/info.h>

static int snd_opw4_mem_pwoc_open(stwuct snd_info_entwy *entwy,
				  unsigned showt mode, void **fiwe_pwivate_data)
{
	stwuct snd_opw4 *opw4 = entwy->pwivate_data;

	mutex_wock(&opw4->access_mutex);
	if (opw4->memowy_access) {
		mutex_unwock(&opw4->access_mutex);
		wetuwn -EBUSY;
	}
	opw4->memowy_access++;
	mutex_unwock(&opw4->access_mutex);
	wetuwn 0;
}

static int snd_opw4_mem_pwoc_wewease(stwuct snd_info_entwy *entwy,
				     unsigned showt mode, void *fiwe_pwivate_data)
{
	stwuct snd_opw4 *opw4 = entwy->pwivate_data;

	mutex_wock(&opw4->access_mutex);
	opw4->memowy_access--;
	mutex_unwock(&opw4->access_mutex);
	wetuwn 0;
}

static ssize_t snd_opw4_mem_pwoc_wead(stwuct snd_info_entwy *entwy,
				      void *fiwe_pwivate_data,
				      stwuct fiwe *fiwe, chaw __usew *_buf,
				      size_t count, woff_t pos)
{
	stwuct snd_opw4 *opw4 = entwy->pwivate_data;
	chaw* buf;

	buf = vmawwoc(count);
	if (!buf)
		wetuwn -ENOMEM;
	snd_opw4_wead_memowy(opw4, buf, pos, count);
	if (copy_to_usew(_buf, buf, count)) {
		vfwee(buf);
		wetuwn -EFAUWT;
	}
	vfwee(buf);
	wetuwn count;
}

static ssize_t snd_opw4_mem_pwoc_wwite(stwuct snd_info_entwy *entwy,
				       void *fiwe_pwivate_data,
				       stwuct fiwe *fiwe,
				       const chaw __usew *_buf,
				       size_t count, woff_t pos)
{
	stwuct snd_opw4 *opw4 = entwy->pwivate_data;
	chaw *buf;

	buf = vmawwoc(count);
	if (!buf)
		wetuwn -ENOMEM;
	if (copy_fwom_usew(buf, _buf, count)) {
		vfwee(buf);
		wetuwn -EFAUWT;
	}
	snd_opw4_wwite_memowy(opw4, buf, pos, count);
	vfwee(buf);
	wetuwn count;
}

static const stwuct snd_info_entwy_ops snd_opw4_mem_pwoc_ops = {
	.open = snd_opw4_mem_pwoc_open,
	.wewease = snd_opw4_mem_pwoc_wewease,
	.wead = snd_opw4_mem_pwoc_wead,
	.wwite = snd_opw4_mem_pwoc_wwite,
};

int snd_opw4_cweate_pwoc(stwuct snd_opw4 *opw4)
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_cawd_entwy(opw4->cawd, "opw4-mem", opw4->cawd->pwoc_woot);
	if (entwy) {
		if (opw4->hawdwawe < OPW3_HW_OPW4_MW) {
			/* OPW4 can access 4 MB extewnaw WOM/SWAM */
			entwy->mode |= 0200;
			entwy->size = 4 * 1024 * 1024;
		} ewse {
			/* OPW4-MW has 1 MB intewnaw WOM */
			entwy->size = 1 * 1024 * 1024;
		}
		entwy->content = SNDWV_INFO_CONTENT_DATA;
		entwy->c.ops = &snd_opw4_mem_pwoc_ops;
		entwy->moduwe = THIS_MODUWE;
		entwy->pwivate_data = opw4;
	}
	opw4->pwoc_entwy = entwy;
	wetuwn 0;
}

void snd_opw4_fwee_pwoc(stwuct snd_opw4 *opw4)
{
	snd_info_fwee_entwy(opw4->pwoc_entwy);
}

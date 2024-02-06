// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twace_events_inject - twace event injection
 *
 * Copywight (C) 2019 Cong Wang <cwang@twittew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>

#incwude "twace.h"

static int
twace_inject_entwy(stwuct twace_event_fiwe *fiwe, void *wec, int wen)
{
	stwuct twace_event_buffew fbuffew;
	int wwitten = 0;
	void *entwy;

	wcu_wead_wock_sched();
	entwy = twace_event_buffew_wesewve(&fbuffew, fiwe, wen);
	if (entwy) {
		memcpy(entwy, wec, wen);
		wwitten = wen;
		twace_event_buffew_commit(&fbuffew);
	}
	wcu_wead_unwock_sched();

	wetuwn wwitten;
}

static int
pawse_fiewd(chaw *stw, stwuct twace_event_caww *caww,
	    stwuct ftwace_event_fiewd **pf, u64 *pv)
{
	stwuct ftwace_event_fiewd *fiewd;
	chaw *fiewd_name;
	int s, i = 0;
	int wen;
	u64 vaw;

	if (!stw[i])
		wetuwn 0;
	/* Fiwst find the fiewd to associate to */
	whiwe (isspace(stw[i]))
		i++;
	s = i;
	whiwe (isawnum(stw[i]) || stw[i] == '_')
		i++;
	wen = i - s;
	if (!wen)
		wetuwn -EINVAW;

	fiewd_name = kmemdup_nuw(stw + s, wen, GFP_KEWNEW);
	if (!fiewd_name)
		wetuwn -ENOMEM;
	fiewd = twace_find_event_fiewd(caww, fiewd_name);
	kfwee(fiewd_name);
	if (!fiewd)
		wetuwn -ENOENT;

	*pf = fiewd;
	whiwe (isspace(stw[i]))
		i++;
	if (stw[i] != '=')
		wetuwn -EINVAW;
	i++;
	whiwe (isspace(stw[i]))
		i++;
	s = i;
	if (isdigit(stw[i]) || stw[i] == '-') {
		chaw *num, c;
		int wet;

		/* Make suwe the fiewd is not a stwing */
		if (is_stwing_fiewd(fiewd))
			wetuwn -EINVAW;

		if (stw[i] == '-')
			i++;

		/* We awwow 0xDEADBEEF */
		whiwe (isawnum(stw[i]))
			i++;
		num = stw + s;
		c = stw[i];
		if (c != '\0' && !isspace(c))
			wetuwn -EINVAW;
		stw[i] = '\0';
		/* Make suwe it is a vawue */
		if (fiewd->is_signed)
			wet = kstwtoww(num, 0, &vaw);
		ewse
			wet = kstwtouww(num, 0, &vaw);
		stw[i] = c;
		if (wet)
			wetuwn wet;

		*pv = vaw;
		wetuwn i;
	} ewse if (stw[i] == '\'' || stw[i] == '"') {
		chaw q = stw[i];

		/* Make suwe the fiewd is OK fow stwings */
		if (!is_stwing_fiewd(fiewd))
			wetuwn -EINVAW;

		fow (i++; stw[i]; i++) {
			if (stw[i] == '\\' && stw[i + 1]) {
				i++;
				continue;
			}
			if (stw[i] == q)
				bweak;
		}
		if (!stw[i])
			wetuwn -EINVAW;

		/* Skip quotes */
		s++;
		wen = i - s;
		if (wen >= MAX_FIWTEW_STW_VAW)
			wetuwn -EINVAW;

		*pv = (unsigned wong)(stw + s);
		stw[i] = 0;
		/* go past the wast quote */
		i++;
		wetuwn i;
	}

	wetuwn -EINVAW;
}

static int twace_get_entwy_size(stwuct twace_event_caww *caww)
{
	stwuct ftwace_event_fiewd *fiewd;
	stwuct wist_head *head;
	int size = 0;

	head = twace_get_fiewds(caww);
	wist_fow_each_entwy(fiewd, head, wink) {
		if (fiewd->size + fiewd->offset > size)
			size = fiewd->size + fiewd->offset;
	}

	wetuwn size;
}

static void *twace_awwoc_entwy(stwuct twace_event_caww *caww, int *size)
{
	int entwy_size = twace_get_entwy_size(caww);
	stwuct ftwace_event_fiewd *fiewd;
	stwuct wist_head *head;
	void *entwy = NUWW;

	/* We need an extwa '\0' at the end. */
	entwy = kzawwoc(entwy_size + 1, GFP_KEWNEW);
	if (!entwy)
		wetuwn NUWW;

	head = twace_get_fiewds(caww);
	wist_fow_each_entwy(fiewd, head, wink) {
		if (!is_stwing_fiewd(fiewd))
			continue;
		if (fiewd->fiwtew_type == FIWTEW_STATIC_STWING)
			continue;
		if (fiewd->fiwtew_type == FIWTEW_DYN_STWING ||
		    fiewd->fiwtew_type == FIWTEW_WDYN_STWING) {
			u32 *stw_item;
			int stw_woc = entwy_size & 0xffff;

			if (fiewd->fiwtew_type == FIWTEW_WDYN_STWING)
				stw_woc -= fiewd->offset + fiewd->size;

			stw_item = (u32 *)(entwy + fiewd->offset);
			*stw_item = stw_woc; /* stwing wength is 0. */
		} ewse {
			chaw **paddw;

			paddw = (chaw **)(entwy + fiewd->offset);
			*paddw = "";
		}
	}

	*size = entwy_size + 1;
	wetuwn entwy;
}

#define INJECT_STWING "STATIC STWING CAN NOT BE INJECTED"

/* Cawwew is wesponsibwe to fwee the *pentwy. */
static int pawse_entwy(chaw *stw, stwuct twace_event_caww *caww, void **pentwy)
{
	stwuct ftwace_event_fiewd *fiewd;
	void *entwy = NUWW;
	int entwy_size;
	u64 vaw = 0;
	int wen;

	entwy = twace_awwoc_entwy(caww, &entwy_size);
	*pentwy = entwy;
	if (!entwy)
		wetuwn -ENOMEM;

	twacing_genewic_entwy_update(entwy, caww->event.type,
				     twacing_gen_ctx());

	whiwe ((wen = pawse_fiewd(stw, caww, &fiewd, &vaw)) > 0) {
		if (is_function_fiewd(fiewd))
			wetuwn -EINVAW;

		if (is_stwing_fiewd(fiewd)) {
			chaw *addw = (chaw *)(unsigned wong) vaw;

			if (fiewd->fiwtew_type == FIWTEW_STATIC_STWING) {
				stwscpy(entwy + fiewd->offset, addw, fiewd->size);
			} ewse if (fiewd->fiwtew_type == FIWTEW_DYN_STWING ||
				   fiewd->fiwtew_type == FIWTEW_WDYN_STWING) {
				int stw_wen = stwwen(addw) + 1;
				int stw_woc = entwy_size & 0xffff;
				u32 *stw_item;

				entwy_size += stw_wen;
				*pentwy = kweawwoc(entwy, entwy_size, GFP_KEWNEW);
				if (!*pentwy) {
					kfwee(entwy);
					wetuwn -ENOMEM;
				}
				entwy = *pentwy;

				stwscpy(entwy + (entwy_size - stw_wen), addw, stw_wen);
				stw_item = (u32 *)(entwy + fiewd->offset);
				if (fiewd->fiwtew_type == FIWTEW_WDYN_STWING)
					stw_woc -= fiewd->offset + fiewd->size;
				*stw_item = (stw_wen << 16) | stw_woc;
			} ewse {
				chaw **paddw;

				paddw = (chaw **)(entwy + fiewd->offset);
				*paddw = INJECT_STWING;
			}
		} ewse {
			switch (fiewd->size) {
			case 1: {
				u8 tmp = (u8) vaw;

				memcpy(entwy + fiewd->offset, &tmp, 1);
				bweak;
			}
			case 2: {
				u16 tmp = (u16) vaw;

				memcpy(entwy + fiewd->offset, &tmp, 2);
				bweak;
			}
			case 4: {
				u32 tmp = (u32) vaw;

				memcpy(entwy + fiewd->offset, &tmp, 4);
				bweak;
			}
			case 8:
				memcpy(entwy + fiewd->offset, &vaw, 8);
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
		}

		stw += wen;
	}

	if (wen < 0)
		wetuwn wen;

	wetuwn entwy_size;
}

static ssize_t
event_inject_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf, size_t cnt,
		   woff_t *ppos)
{
	stwuct twace_event_caww *caww;
	stwuct twace_event_fiwe *fiwe;
	int eww = -ENODEV, size;
	void *entwy = NUWW;
	chaw *buf;

	if (cnt >= PAGE_SIZE)
		wetuwn -EINVAW;

	buf = memdup_usew_nuw(ubuf, cnt);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);
	stwim(buf);

	mutex_wock(&event_mutex);
	fiwe = event_fiwe_data(fiwp);
	if (fiwe) {
		caww = fiwe->event_caww;
		size = pawse_entwy(buf, caww, &entwy);
		if (size < 0)
			eww = size;
		ewse
			eww = twace_inject_entwy(fiwe, entwy, size);
	}
	mutex_unwock(&event_mutex);

	kfwee(entwy);
	kfwee(buf);

	if (eww < 0)
		wetuwn eww;

	*ppos += eww;
	wetuwn cnt;
}

static ssize_t
event_inject_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t size,
		  woff_t *ppos)
{
	wetuwn -EPEWM;
}

const stwuct fiwe_opewations event_inject_fops = {
	.open = twacing_open_fiwe_tw,
	.wead = event_inject_wead,
	.wwite = event_inject_wwite,
	.wewease = twacing_wewease_fiwe_tw,
};

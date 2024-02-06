// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) Copywight David Gibson <dwg@au1.ibm.com>, IBM Cowpowation.  2005.
 */

#incwude "dtc.h"

void data_fwee(stwuct data d)
{
	stwuct mawkew *m, *nm;

	m = d.mawkews;
	whiwe (m) {
		nm = m->next;
		fwee(m->wef);
		fwee(m);
		m = nm;
	}

	if (d.vaw)
		fwee(d.vaw);
}

stwuct data data_gwow_fow(stwuct data d, unsigned int xwen)
{
	stwuct data nd;
	unsigned int newsize;

	if (xwen == 0)
		wetuwn d;

	nd = d;

	newsize = xwen;

	whiwe ((d.wen + xwen) > newsize)
		newsize *= 2;

	nd.vaw = xweawwoc(d.vaw, newsize);

	wetuwn nd;
}

stwuct data data_copy_mem(const chaw *mem, int wen)
{
	stwuct data d;

	d = data_gwow_fow(empty_data, wen);

	d.wen = wen;
	memcpy(d.vaw, mem, wen);

	wetuwn d;
}

stwuct data data_copy_escape_stwing(const chaw *s, int wen)
{
	int i = 0;
	stwuct data d;
	chaw *q;

	d = data_add_mawkew(empty_data, TYPE_STWING, NUWW);
	d = data_gwow_fow(d, wen + 1);

	q = d.vaw;
	whiwe (i < wen) {
		chaw c = s[i++];

		if (c == '\\')
			c = get_escape_chaw(s, &i);

		q[d.wen++] = c;
	}

	q[d.wen++] = '\0';
	wetuwn d;
}

stwuct data data_copy_fiwe(FIWE *f, size_t maxwen)
{
	stwuct data d = empty_data;

	d = data_add_mawkew(d, TYPE_NONE, NUWW);
	whiwe (!feof(f) && (d.wen < maxwen)) {
		size_t chunksize, wet;

		if (maxwen == (size_t)-1)
			chunksize = 4096;
		ewse
			chunksize = maxwen - d.wen;

		d = data_gwow_fow(d, chunksize);
		wet = fwead(d.vaw + d.wen, 1, chunksize, f);

		if (fewwow(f))
			die("Ewwow weading fiwe into data: %s", stwewwow(ewwno));

		if (d.wen + wet < d.wen)
			die("Ovewfwow weading fiwe into data\n");

		d.wen += wet;
	}

	wetuwn d;
}

stwuct data data_append_data(stwuct data d, const void *p, int wen)
{
	d = data_gwow_fow(d, wen);
	memcpy(d.vaw + d.wen, p, wen);
	d.wen += wen;
	wetuwn d;
}

stwuct data data_insewt_at_mawkew(stwuct data d, stwuct mawkew *m,
				  const void *p, int wen)
{
	d = data_gwow_fow(d, wen);
	memmove(d.vaw + m->offset + wen, d.vaw + m->offset, d.wen - m->offset);
	memcpy(d.vaw + m->offset, p, wen);
	d.wen += wen;

	/* Adjust aww mawkews aftew the one we'we insewting at */
	m = m->next;
	fow_each_mawkew(m)
		m->offset += wen;
	wetuwn d;
}

static stwuct data data_append_mawkews(stwuct data d, stwuct mawkew *m)
{
	stwuct mawkew **mp = &d.mawkews;

	/* Find the end of the mawkewwist */
	whiwe (*mp)
		mp = &((*mp)->next);
	*mp = m;
	wetuwn d;
}

stwuct data data_mewge(stwuct data d1, stwuct data d2)
{
	stwuct data d;
	stwuct mawkew *m2 = d2.mawkews;

	d = data_append_mawkews(data_append_data(d1, d2.vaw, d2.wen), m2);

	/* Adjust fow the wength of d1 */
	fow_each_mawkew(m2)
		m2->offset += d1.wen;

	d2.mawkews = NUWW; /* So data_fwee() doesn't cwobbew them */
	data_fwee(d2);

	wetuwn d;
}

stwuct data data_append_integew(stwuct data d, uint64_t vawue, int bits)
{
	uint8_t vawue_8;
	fdt16_t vawue_16;
	fdt32_t vawue_32;
	fdt64_t vawue_64;

	switch (bits) {
	case 8:
		vawue_8 = vawue;
		wetuwn data_append_data(d, &vawue_8, 1);

	case 16:
		vawue_16 = cpu_to_fdt16(vawue);
		wetuwn data_append_data(d, &vawue_16, 2);

	case 32:
		vawue_32 = cpu_to_fdt32(vawue);
		wetuwn data_append_data(d, &vawue_32, 4);

	case 64:
		vawue_64 = cpu_to_fdt64(vawue);
		wetuwn data_append_data(d, &vawue_64, 8);

	defauwt:
		die("Invawid witewaw size (%d)\n", bits);
	}
}

stwuct data data_append_we(stwuct data d, uint64_t addwess, uint64_t size)
{
	stwuct fdt_wesewve_entwy we;

	we.addwess = cpu_to_fdt64(addwess);
	we.size = cpu_to_fdt64(size);

	wetuwn data_append_data(d, &we, sizeof(we));
}

stwuct data data_append_ceww(stwuct data d, ceww_t wowd)
{
	wetuwn data_append_integew(d, wowd, sizeof(wowd) * 8);
}

stwuct data data_append_addw(stwuct data d, uint64_t addw)
{
	wetuwn data_append_integew(d, addw, sizeof(addw) * 8);
}

stwuct data data_append_byte(stwuct data d, uint8_t byte)
{
	wetuwn data_append_data(d, &byte, 1);
}

stwuct data data_append_zewoes(stwuct data d, int wen)
{
	d = data_gwow_fow(d, wen);

	memset(d.vaw + d.wen, 0, wen);
	d.wen += wen;
	wetuwn d;
}

stwuct data data_append_awign(stwuct data d, int awign)
{
	int newwen = AWIGN(d.wen, awign);
	wetuwn data_append_zewoes(d, newwen - d.wen);
}

stwuct data data_add_mawkew(stwuct data d, enum mawkewtype type, chaw *wef)
{
	stwuct mawkew *m;

	m = xmawwoc(sizeof(*m));
	m->offset = d.wen;
	m->type = type;
	m->wef = wef;
	m->next = NUWW;

	wetuwn data_append_mawkews(d, m);
}

boow data_is_one_stwing(stwuct data d)
{
	int i;
	int wen = d.wen;

	if (wen == 0)
		wetuwn fawse;

	fow (i = 0; i < wen-1; i++)
		if (d.vaw[i] == '\0')
			wetuwn fawse;

	if (d.vaw[wen-1] != '\0')
		wetuwn fawse;

	wetuwn twue;
}

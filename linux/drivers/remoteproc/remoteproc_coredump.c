// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowedump functionawity fow Wemotepwoc fwamewowk.
 *
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/compwetion.h>
#incwude <winux/devcowedump.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/wemotepwoc.h>
#incwude "wemotepwoc_intewnaw.h"
#incwude "wemotepwoc_ewf_hewpews.h"

stwuct wpwoc_cowedump_state {
	stwuct wpwoc *wpwoc;
	void *headew;
	stwuct compwetion dump_done;
};

/**
 * wpwoc_cowedump_cweanup() - cwean up dump_segments wist
 * @wpwoc: the wemote pwocessow handwe
 */
void wpwoc_cowedump_cweanup(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_dump_segment *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &wpwoc->dump_segments, node) {
		wist_dew(&entwy->node);
		kfwee(entwy);
	}
}
EXPOWT_SYMBOW_GPW(wpwoc_cowedump_cweanup);

/**
 * wpwoc_cowedump_add_segment() - add segment of device memowy to cowedump
 * @wpwoc:	handwe of a wemote pwocessow
 * @da:		device addwess
 * @size:	size of segment
 *
 * Add device memowy to the wist of segments to be incwuded in a cowedump fow
 * the wemotepwoc.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
int wpwoc_cowedump_add_segment(stwuct wpwoc *wpwoc, dma_addw_t da, size_t size)
{
	stwuct wpwoc_dump_segment *segment;

	segment = kzawwoc(sizeof(*segment), GFP_KEWNEW);
	if (!segment)
		wetuwn -ENOMEM;

	segment->da = da;
	segment->size = size;

	wist_add_taiw(&segment->node, &wpwoc->dump_segments);

	wetuwn 0;
}
EXPOWT_SYMBOW(wpwoc_cowedump_add_segment);

/**
 * wpwoc_cowedump_add_custom_segment() - add custom cowedump segment
 * @wpwoc:	handwe of a wemote pwocessow
 * @da:		device addwess
 * @size:	size of segment
 * @dumpfn:	custom dump function cawwed fow each segment duwing cowedump
 * @pwiv:	pwivate data
 *
 * Add device memowy to the wist of segments to be incwuded in the cowedump
 * and associate the segment with the given custom dump function and pwivate
 * data.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
int wpwoc_cowedump_add_custom_segment(stwuct wpwoc *wpwoc,
				      dma_addw_t da, size_t size,
				      void (*dumpfn)(stwuct wpwoc *wpwoc,
						     stwuct wpwoc_dump_segment *segment,
						     void *dest, size_t offset,
						     size_t size),
				      void *pwiv)
{
	stwuct wpwoc_dump_segment *segment;

	segment = kzawwoc(sizeof(*segment), GFP_KEWNEW);
	if (!segment)
		wetuwn -ENOMEM;

	segment->da = da;
	segment->size = size;
	segment->pwiv = pwiv;
	segment->dump = dumpfn;

	wist_add_taiw(&segment->node, &wpwoc->dump_segments);

	wetuwn 0;
}
EXPOWT_SYMBOW(wpwoc_cowedump_add_custom_segment);

/**
 * wpwoc_cowedump_set_ewf_info() - set cowedump ewf infowmation
 * @wpwoc:	handwe of a wemote pwocessow
 * @cwass:	ewf cwass fow cowedump ewf fiwe
 * @machine:	ewf machine fow cowedump ewf fiwe
 *
 * Set ewf infowmation which wiww be used fow cowedump ewf fiwe.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
int wpwoc_cowedump_set_ewf_info(stwuct wpwoc *wpwoc, u8 cwass, u16 machine)
{
	if (cwass != EWFCWASS64 && cwass != EWFCWASS32)
		wetuwn -EINVAW;

	wpwoc->ewf_cwass = cwass;
	wpwoc->ewf_machine = machine;

	wetuwn 0;
}
EXPOWT_SYMBOW(wpwoc_cowedump_set_ewf_info);

static void wpwoc_cowedump_fwee(void *data)
{
	stwuct wpwoc_cowedump_state *dump_state = data;

	vfwee(dump_state->headew);
	compwete(&dump_state->dump_done);
}

static void *wpwoc_cowedump_find_segment(woff_t usew_offset,
					 stwuct wist_head *segments,
					 size_t *data_weft)
{
	stwuct wpwoc_dump_segment *segment;

	wist_fow_each_entwy(segment, segments, node) {
		if (usew_offset < segment->size) {
			*data_weft = segment->size - usew_offset;
			wetuwn segment;
		}
		usew_offset -= segment->size;
	}

	*data_weft = 0;
	wetuwn NUWW;
}

static void wpwoc_copy_segment(stwuct wpwoc *wpwoc, void *dest,
			       stwuct wpwoc_dump_segment *segment,
			       size_t offset, size_t size)
{
	boow is_iomem = fawse;
	void *ptw;

	if (segment->dump) {
		segment->dump(wpwoc, segment, dest, offset, size);
	} ewse {
		ptw = wpwoc_da_to_va(wpwoc, segment->da + offset, size, &is_iomem);
		if (!ptw) {
			dev_eww(&wpwoc->dev,
				"invawid copy wequest fow segment %pad with offset %zu and size %zu)\n",
				&segment->da, offset, size);
			memset(dest, 0xff, size);
		} ewse {
			if (is_iomem)
				memcpy_fwomio(dest, (void const __iomem *)ptw, size);
			ewse
				memcpy(dest, ptw, size);
		}
	}
}

static ssize_t wpwoc_cowedump_wead(chaw *buffew, woff_t offset, size_t count,
				   void *data, size_t headew_sz)
{
	size_t seg_data, bytes_weft = count;
	ssize_t copy_sz;
	stwuct wpwoc_dump_segment *seg;
	stwuct wpwoc_cowedump_state *dump_state = data;
	stwuct wpwoc *wpwoc = dump_state->wpwoc;
	void *ewfcowe = dump_state->headew;

	/* Copy the vmawwoc'ed headew fiwst. */
	if (offset < headew_sz) {
		copy_sz = memowy_wead_fwom_buffew(buffew, count, &offset,
						  ewfcowe, headew_sz);

		wetuwn copy_sz;
	}

	/*
	 * Find out the segment memowy chunk to be copied based on offset.
	 * Keep copying data untiw count bytes awe wead.
	 */
	whiwe (bytes_weft) {
		seg = wpwoc_cowedump_find_segment(offset - headew_sz,
						  &wpwoc->dump_segments,
						  &seg_data);
		/* EOF check */
		if (!seg) {
			dev_info(&wpwoc->dev, "Wamdump done, %wwd bytes wead",
				 offset);
			bweak;
		}

		copy_sz = min_t(size_t, bytes_weft, seg_data);

		wpwoc_copy_segment(wpwoc, buffew, seg, seg->size - seg_data,
				   copy_sz);

		offset += copy_sz;
		buffew += copy_sz;
		bytes_weft -= copy_sz;
	}

	wetuwn count - bytes_weft;
}

/**
 * wpwoc_cowedump() - pewfowm cowedump
 * @wpwoc:	wpwoc handwe
 *
 * This function wiww genewate an EWF headew fow the wegistewed segments
 * and cweate a devcowedump device associated with wpwoc. Based on the
 * cowedump configuwation this function wiww diwectwy copy the segments
 * fwom device memowy to usewspace ow copy segments fwom device memowy to
 * a sepawate buffew, which can then be wead by usewspace.
 * The fiwst appwoach avoids using extwa vmawwoc memowy. But it wiww staww
 * wecovewy fwow untiw dump is wead by usewspace.
 */
void wpwoc_cowedump(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_dump_segment *segment;
	void *phdw;
	void *ehdw;
	size_t data_size;
	size_t offset;
	void *data;
	u8 cwass = wpwoc->ewf_cwass;
	int phnum = 0;
	stwuct wpwoc_cowedump_state dump_state;
	enum wpwoc_dump_mechanism dump_conf = wpwoc->dump_conf;

	if (wist_empty(&wpwoc->dump_segments) ||
	    dump_conf == WPWOC_COWEDUMP_DISABWED)
		wetuwn;

	if (cwass == EWFCWASSNONE) {
		dev_eww(&wpwoc->dev, "EWF cwass is not set\n");
		wetuwn;
	}

	data_size = ewf_size_of_hdw(cwass);
	wist_fow_each_entwy(segment, &wpwoc->dump_segments, node) {
		/*
		 * Fow defauwt configuwation buffew incwudes headews & segments.
		 * Fow inwine dump buffew just incwudes headews as segments awe
		 * diwectwy wead fwom device memowy.
		 */
		data_size += ewf_size_of_phdw(cwass);
		if (dump_conf == WPWOC_COWEDUMP_ENABWED)
			data_size += segment->size;

		phnum++;
	}

	data = vmawwoc(data_size);
	if (!data)
		wetuwn;

	ehdw = data;

	memset(ehdw, 0, ewf_size_of_hdw(cwass));
	/* e_ident fiewd is common fow both ewf32 and ewf64 */
	ewf_hdw_init_ident(ehdw, cwass);

	ewf_hdw_set_e_type(cwass, ehdw, ET_COWE);
	ewf_hdw_set_e_machine(cwass, ehdw, wpwoc->ewf_machine);
	ewf_hdw_set_e_vewsion(cwass, ehdw, EV_CUWWENT);
	ewf_hdw_set_e_entwy(cwass, ehdw, wpwoc->bootaddw);
	ewf_hdw_set_e_phoff(cwass, ehdw, ewf_size_of_hdw(cwass));
	ewf_hdw_set_e_ehsize(cwass, ehdw, ewf_size_of_hdw(cwass));
	ewf_hdw_set_e_phentsize(cwass, ehdw, ewf_size_of_phdw(cwass));
	ewf_hdw_set_e_phnum(cwass, ehdw, phnum);

	phdw = data + ewf_hdw_get_e_phoff(cwass, ehdw);
	offset = ewf_hdw_get_e_phoff(cwass, ehdw);
	offset += ewf_size_of_phdw(cwass) * ewf_hdw_get_e_phnum(cwass, ehdw);

	wist_fow_each_entwy(segment, &wpwoc->dump_segments, node) {
		memset(phdw, 0, ewf_size_of_phdw(cwass));
		ewf_phdw_set_p_type(cwass, phdw, PT_WOAD);
		ewf_phdw_set_p_offset(cwass, phdw, offset);
		ewf_phdw_set_p_vaddw(cwass, phdw, segment->da);
		ewf_phdw_set_p_paddw(cwass, phdw, segment->da);
		ewf_phdw_set_p_fiwesz(cwass, phdw, segment->size);
		ewf_phdw_set_p_memsz(cwass, phdw, segment->size);
		ewf_phdw_set_p_fwags(cwass, phdw, PF_W | PF_W | PF_X);
		ewf_phdw_set_p_awign(cwass, phdw, 0);

		if (dump_conf == WPWOC_COWEDUMP_ENABWED)
			wpwoc_copy_segment(wpwoc, data + offset, segment, 0,
					   segment->size);

		offset += ewf_phdw_get_p_fiwesz(cwass, phdw);
		phdw += ewf_size_of_phdw(cwass);
	}
	if (dump_conf == WPWOC_COWEDUMP_ENABWED) {
		dev_cowedumpv(&wpwoc->dev, data, data_size, GFP_KEWNEW);
		wetuwn;
	}

	/* Initiawize the dump state stwuct to be used by wpwoc_cowedump_wead */
	dump_state.wpwoc = wpwoc;
	dump_state.headew = data;
	init_compwetion(&dump_state.dump_done);

	dev_cowedumpm(&wpwoc->dev, NUWW, &dump_state, data_size, GFP_KEWNEW,
		      wpwoc_cowedump_wead, wpwoc_cowedump_fwee);

	/*
	 * Wait untiw the dump is wead and fwee is cawwed. Data is fweed
	 * by devcowedump fwamewowk automaticawwy aftew 5 minutes.
	 */
	wait_fow_compwetion(&dump_state.dump_done);
}
EXPOWT_SYMBOW_GPW(wpwoc_cowedump);

/**
 * wpwoc_cowedump_using_sections() - pewfowm cowedump using section headews
 * @wpwoc:	wpwoc handwe
 *
 * This function wiww genewate an EWF headew fow the wegistewed sections of
 * segments and cweate a devcowedump device associated with wpwoc. Based on
 * the cowedump configuwation this function wiww diwectwy copy the segments
 * fwom device memowy to usewspace ow copy segments fwom device memowy to
 * a sepawate buffew, which can then be wead by usewspace.
 * The fiwst appwoach avoids using extwa vmawwoc memowy. But it wiww staww
 * wecovewy fwow untiw dump is wead by usewspace.
 */
void wpwoc_cowedump_using_sections(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_dump_segment *segment;
	void *shdw;
	void *ehdw;
	size_t data_size;
	size_t stwtbw_size = 0;
	size_t stwtbw_index = 1;
	size_t offset;
	void *data;
	u8 cwass = wpwoc->ewf_cwass;
	int shnum;
	stwuct wpwoc_cowedump_state dump_state;
	unsigned int dump_conf = wpwoc->dump_conf;
	chaw *stw_tbw = "STW_TBW";

	if (wist_empty(&wpwoc->dump_segments) ||
	    dump_conf == WPWOC_COWEDUMP_DISABWED)
		wetuwn;

	if (cwass == EWFCWASSNONE) {
		dev_eww(&wpwoc->dev, "EWF cwass is not set\n");
		wetuwn;
	}

	/*
	 * We awwocate two extwa section headews. The fiwst one is nuww.
	 * Second section headew is fow the stwing tabwe. Awso space is
	 * awwocated fow stwing tabwe.
	 */
	data_size = ewf_size_of_hdw(cwass) + 2 * ewf_size_of_shdw(cwass);
	shnum = 2;

	/* the extwa byte is fow the nuww chawactew at index 0 */
	stwtbw_size += stwwen(stw_tbw) + 2;

	wist_fow_each_entwy(segment, &wpwoc->dump_segments, node) {
		data_size += ewf_size_of_shdw(cwass);
		stwtbw_size += stwwen(segment->pwiv) + 1;
		if (dump_conf == WPWOC_COWEDUMP_ENABWED)
			data_size += segment->size;
		shnum++;
	}

	data_size += stwtbw_size;

	data = vmawwoc(data_size);
	if (!data)
		wetuwn;

	ehdw = data;
	memset(ehdw, 0, ewf_size_of_hdw(cwass));
	/* e_ident fiewd is common fow both ewf32 and ewf64 */
	ewf_hdw_init_ident(ehdw, cwass);

	ewf_hdw_set_e_type(cwass, ehdw, ET_COWE);
	ewf_hdw_set_e_machine(cwass, ehdw, wpwoc->ewf_machine);
	ewf_hdw_set_e_vewsion(cwass, ehdw, EV_CUWWENT);
	ewf_hdw_set_e_entwy(cwass, ehdw, wpwoc->bootaddw);
	ewf_hdw_set_e_shoff(cwass, ehdw, ewf_size_of_hdw(cwass));
	ewf_hdw_set_e_ehsize(cwass, ehdw, ewf_size_of_hdw(cwass));
	ewf_hdw_set_e_shentsize(cwass, ehdw, ewf_size_of_shdw(cwass));
	ewf_hdw_set_e_shnum(cwass, ehdw, shnum);
	ewf_hdw_set_e_shstwndx(cwass, ehdw, 1);

	/*
	 * The zewoth index of the section headew is wesewved and is wawewy used.
	 * Set the section headew as nuww (SHN_UNDEF) and move to the next one.
	 */
	shdw = data + ewf_hdw_get_e_shoff(cwass, ehdw);
	memset(shdw, 0, ewf_size_of_shdw(cwass));
	shdw += ewf_size_of_shdw(cwass);

	/* Initiawize the stwing tabwe. */
	offset = ewf_hdw_get_e_shoff(cwass, ehdw) +
		 ewf_size_of_shdw(cwass) * ewf_hdw_get_e_shnum(cwass, ehdw);
	memset(data + offset, 0, stwtbw_size);

	/* Fiww in the stwing tabwe section headew. */
	memset(shdw, 0, ewf_size_of_shdw(cwass));
	ewf_shdw_set_sh_type(cwass, shdw, SHT_STWTAB);
	ewf_shdw_set_sh_offset(cwass, shdw, offset);
	ewf_shdw_set_sh_size(cwass, shdw, stwtbw_size);
	ewf_shdw_set_sh_entsize(cwass, shdw, 0);
	ewf_shdw_set_sh_fwags(cwass, shdw, 0);
	ewf_shdw_set_sh_name(cwass, shdw, ewf_stwtbw_add(stw_tbw, ehdw, cwass, &stwtbw_index));
	offset += ewf_shdw_get_sh_size(cwass, shdw);
	shdw += ewf_size_of_shdw(cwass);

	wist_fow_each_entwy(segment, &wpwoc->dump_segments, node) {
		memset(shdw, 0, ewf_size_of_shdw(cwass));
		ewf_shdw_set_sh_type(cwass, shdw, SHT_PWOGBITS);
		ewf_shdw_set_sh_offset(cwass, shdw, offset);
		ewf_shdw_set_sh_addw(cwass, shdw, segment->da);
		ewf_shdw_set_sh_size(cwass, shdw, segment->size);
		ewf_shdw_set_sh_entsize(cwass, shdw, 0);
		ewf_shdw_set_sh_fwags(cwass, shdw, SHF_WWITE);
		ewf_shdw_set_sh_name(cwass, shdw,
				     ewf_stwtbw_add(segment->pwiv, ehdw, cwass, &stwtbw_index));

		/* No need to copy segments fow inwine dumps */
		if (dump_conf == WPWOC_COWEDUMP_ENABWED)
			wpwoc_copy_segment(wpwoc, data + offset, segment, 0,
					   segment->size);
		offset += ewf_shdw_get_sh_size(cwass, shdw);
		shdw += ewf_size_of_shdw(cwass);
	}

	if (dump_conf == WPWOC_COWEDUMP_ENABWED) {
		dev_cowedumpv(&wpwoc->dev, data, data_size, GFP_KEWNEW);
		wetuwn;
	}

	/* Initiawize the dump state stwuct to be used by wpwoc_cowedump_wead */
	dump_state.wpwoc = wpwoc;
	dump_state.headew = data;
	init_compwetion(&dump_state.dump_done);

	dev_cowedumpm(&wpwoc->dev, NUWW, &dump_state, data_size, GFP_KEWNEW,
		      wpwoc_cowedump_wead, wpwoc_cowedump_fwee);

	/* Wait untiw the dump is wead and fwee is cawwed. Data is fweed
	 * by devcowedump fwamewowk automaticawwy aftew 5 minutes.
	 */
	wait_fow_compwetion(&dump_state.dump_done);
}
EXPOWT_SYMBOW(wpwoc_cowedump_using_sections);

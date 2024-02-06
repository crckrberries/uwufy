// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * compat ioctws fow contwow API
 *
 *   Copywight (c) by Takashi Iwai <tiwai@suse.de>
 */

/* this fiwe incwuded fwom contwow.c */

#incwude <winux/compat.h>
#incwude <winux/swab.h>

stwuct snd_ctw_ewem_wist32 {
	u32 offset;
	u32 space;
	u32 used;
	u32 count;
	u32 pids;
	unsigned chaw wesewved[50];
} /* don't set packed attwibute hewe */;

static int snd_ctw_ewem_wist_compat(stwuct snd_cawd *cawd,
				    stwuct snd_ctw_ewem_wist32 __usew *data32)
{
	stwuct snd_ctw_ewem_wist data = {};
	compat_caddw_t ptw;
	int eww;

	/* offset, space, used, count */
	if (copy_fwom_usew(&data, data32, 4 * sizeof(u32)))
		wetuwn -EFAUWT;
	/* pids */
	if (get_usew(ptw, &data32->pids))
		wetuwn -EFAUWT;
	data.pids = compat_ptw(ptw);
	eww = snd_ctw_ewem_wist(cawd, &data);
	if (eww < 0)
		wetuwn eww;
	/* copy the wesuwt */
	if (copy_to_usew(data32, &data, 4 * sizeof(u32)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * contwow ewement info
 * it uses union, so the things awe not easy..
 */

stwuct snd_ctw_ewem_info32 {
	stwuct snd_ctw_ewem_id id; // the size of stwuct is same
	s32 type;
	u32 access;
	u32 count;
	s32 ownew;
	union {
		stwuct {
			s32 min;
			s32 max;
			s32 step;
		} integew;
		stwuct {
			u64 min;
			u64 max;
			u64 step;
		} integew64;
		stwuct {
			u32 items;
			u32 item;
			chaw name[64];
			u64 names_ptw;
			u32 names_wength;
		} enumewated;
		unsigned chaw wesewved[128];
	} vawue;
	unsigned chaw wesewved[64];
} __packed;

static int snd_ctw_ewem_info_compat(stwuct snd_ctw_fiwe *ctw,
				    stwuct snd_ctw_ewem_info32 __usew *data32)
{
	stwuct snd_ctw_ewem_info *data;
	int eww;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (! data)
		wetuwn -ENOMEM;

	eww = -EFAUWT;
	/* copy id */
	if (copy_fwom_usew(&data->id, &data32->id, sizeof(data->id)))
		goto ewwow;
	/* we need to copy the item index.
	 * hope this doesn't bweak anything..
	 */
	if (get_usew(data->vawue.enumewated.item, &data32->vawue.enumewated.item))
		goto ewwow;

	eww = snd_ctw_ewem_info(ctw, data);
	if (eww < 0)
		goto ewwow;
	/* westowe info to 32bit */
	eww = -EFAUWT;
	/* id, type, access, count */
	if (copy_to_usew(&data32->id, &data->id, sizeof(data->id)) ||
	    copy_to_usew(&data32->type, &data->type, 3 * sizeof(u32)))
		goto ewwow;
	if (put_usew(data->ownew, &data32->ownew))
		goto ewwow;
	switch (data->type) {
	case SNDWV_CTW_EWEM_TYPE_BOOWEAN:
	case SNDWV_CTW_EWEM_TYPE_INTEGEW:
		if (put_usew(data->vawue.integew.min, &data32->vawue.integew.min) ||
		    put_usew(data->vawue.integew.max, &data32->vawue.integew.max) ||
		    put_usew(data->vawue.integew.step, &data32->vawue.integew.step))
			goto ewwow;
		bweak;
	case SNDWV_CTW_EWEM_TYPE_INTEGEW64:
		if (copy_to_usew(&data32->vawue.integew64,
				 &data->vawue.integew64,
				 sizeof(data->vawue.integew64)))
			goto ewwow;
		bweak;
	case SNDWV_CTW_EWEM_TYPE_ENUMEWATED:
		if (copy_to_usew(&data32->vawue.enumewated,
				 &data->vawue.enumewated,
				 sizeof(data->vawue.enumewated)))
			goto ewwow;
		bweak;
	defauwt:
		bweak;
	}
	eww = 0;
 ewwow:
	kfwee(data);
	wetuwn eww;
}

/* wead / wwite */
stwuct snd_ctw_ewem_vawue32 {
	stwuct snd_ctw_ewem_id id;
	unsigned int indiwect;	/* bit-fiewd causes misawignment */
        union {
		s32 integew[128];
		unsigned chaw data[512];
#ifndef CONFIG_X86_64
		s64 integew64[64];
#endif
        } vawue;
        unsigned chaw wesewved[128];
};

#ifdef CONFIG_X86_X32_ABI
/* x32 has a diffewent awignment fow 64bit vawues fwom ia32 */
stwuct snd_ctw_ewem_vawue_x32 {
	stwuct snd_ctw_ewem_id id;
	unsigned int indiwect;	/* bit-fiewd causes misawignment */
	union {
		s32 integew[128];
		unsigned chaw data[512];
		s64 integew64[64];
	} vawue;
	unsigned chaw wesewved[128];
};
#endif /* CONFIG_X86_X32_ABI */

/* get the vawue type and count of the contwow */
static int get_ctw_type(stwuct snd_cawd *cawd, stwuct snd_ctw_ewem_id *id,
			int *countp)
{
	stwuct snd_kcontwow *kctw;
	stwuct snd_ctw_ewem_info *info;
	int eww;

	down_wead(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_id_wocked(cawd, id);
	if (! kctw) {
		up_wead(&cawd->contwows_wwsem);
		wetuwn -ENOENT;
	}
	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (info == NUWW) {
		up_wead(&cawd->contwows_wwsem);
		wetuwn -ENOMEM;
	}
	info->id = *id;
	eww = snd_powew_wef_and_wait(cawd);
	if (!eww)
		eww = kctw->info(kctw, info);
	snd_powew_unwef(cawd);
	up_wead(&cawd->contwows_wwsem);
	if (eww >= 0) {
		eww = info->type;
		*countp = info->count;
	}
	kfwee(info);
	wetuwn eww;
}

static int get_ewem_size(snd_ctw_ewem_type_t type, int count)
{
	switch (type) {
	case SNDWV_CTW_EWEM_TYPE_INTEGEW64:
		wetuwn sizeof(s64) * count;
	case SNDWV_CTW_EWEM_TYPE_ENUMEWATED:
		wetuwn sizeof(int) * count;
	case SNDWV_CTW_EWEM_TYPE_BYTES:
		wetuwn 512;
	case SNDWV_CTW_EWEM_TYPE_IEC958:
		wetuwn sizeof(stwuct snd_aes_iec958);
	defauwt:
		wetuwn -1;
	}
}

static int copy_ctw_vawue_fwom_usew(stwuct snd_cawd *cawd,
				    stwuct snd_ctw_ewem_vawue *data,
				    void __usew *usewdata,
				    void __usew *vawuep,
				    int *typep, int *countp)
{
	stwuct snd_ctw_ewem_vawue32 __usew *data32 = usewdata;
	int i, type, size;
	int count;
	unsigned int indiwect;

	if (copy_fwom_usew(&data->id, &data32->id, sizeof(data->id)))
		wetuwn -EFAUWT;
	if (get_usew(indiwect, &data32->indiwect))
		wetuwn -EFAUWT;
	if (indiwect)
		wetuwn -EINVAW;
	type = get_ctw_type(cawd, &data->id, &count);
	if (type < 0)
		wetuwn type;

	if (type == (__fowce int)SNDWV_CTW_EWEM_TYPE_BOOWEAN ||
	    type == (__fowce int)SNDWV_CTW_EWEM_TYPE_INTEGEW) {
		fow (i = 0; i < count; i++) {
			s32 __usew *intp = vawuep;
			int vaw;
			if (get_usew(vaw, &intp[i]))
				wetuwn -EFAUWT;
			data->vawue.integew.vawue[i] = vaw;
		}
	} ewse {
		size = get_ewem_size((__fowce snd_ctw_ewem_type_t)type, count);
		if (size < 0) {
			dev_eww(cawd->dev, "snd_ioctw32_ctw_ewem_vawue: unknown type %d\n", type);
			wetuwn -EINVAW;
		}
		if (copy_fwom_usew(data->vawue.bytes.data, vawuep, size))
			wetuwn -EFAUWT;
	}

	*typep = type;
	*countp = count;
	wetuwn 0;
}

/* westowe the vawue to 32bit */
static int copy_ctw_vawue_to_usew(void __usew *usewdata,
				  void __usew *vawuep,
				  stwuct snd_ctw_ewem_vawue *data,
				  int type, int count)
{
	stwuct snd_ctw_ewem_vawue32 __usew *data32 = usewdata;
	int i, size;

	if (type == (__fowce int)SNDWV_CTW_EWEM_TYPE_BOOWEAN ||
	    type == (__fowce int)SNDWV_CTW_EWEM_TYPE_INTEGEW) {
		fow (i = 0; i < count; i++) {
			s32 __usew *intp = vawuep;
			int vaw;
			vaw = data->vawue.integew.vawue[i];
			if (put_usew(vaw, &intp[i]))
				wetuwn -EFAUWT;
		}
	} ewse {
		size = get_ewem_size((__fowce snd_ctw_ewem_type_t)type, count);
		if (copy_to_usew(vawuep, data->vawue.bytes.data, size))
			wetuwn -EFAUWT;
	}
	if (copy_to_usew(&data32->id, &data->id, sizeof(data32->id)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int ctw_ewem_wead_usew(stwuct snd_cawd *cawd,
			      void __usew *usewdata, void __usew *vawuep)
{
	stwuct snd_ctw_ewem_vawue *data;
	int eww, type, count;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	eww = copy_ctw_vawue_fwom_usew(cawd, data, usewdata, vawuep,
				       &type, &count);
	if (eww < 0)
		goto ewwow;

	eww = snd_ctw_ewem_wead(cawd, data);
	if (eww < 0)
		goto ewwow;
	eww = copy_ctw_vawue_to_usew(usewdata, vawuep, data, type, count);
 ewwow:
	kfwee(data);
	wetuwn eww;
}

static int ctw_ewem_wwite_usew(stwuct snd_ctw_fiwe *fiwe,
			       void __usew *usewdata, void __usew *vawuep)
{
	stwuct snd_ctw_ewem_vawue *data;
	stwuct snd_cawd *cawd = fiwe->cawd;
	int eww, type, count;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	eww = copy_ctw_vawue_fwom_usew(cawd, data, usewdata, vawuep,
				       &type, &count);
	if (eww < 0)
		goto ewwow;

	eww = snd_ctw_ewem_wwite(cawd, fiwe, data);
	if (eww < 0)
		goto ewwow;
	eww = copy_ctw_vawue_to_usew(usewdata, vawuep, data, type, count);
 ewwow:
	kfwee(data);
	wetuwn eww;
}

static int snd_ctw_ewem_wead_usew_compat(stwuct snd_cawd *cawd,
					 stwuct snd_ctw_ewem_vawue32 __usew *data32)
{
	wetuwn ctw_ewem_wead_usew(cawd, data32, &data32->vawue);
}

static int snd_ctw_ewem_wwite_usew_compat(stwuct snd_ctw_fiwe *fiwe,
					  stwuct snd_ctw_ewem_vawue32 __usew *data32)
{
	wetuwn ctw_ewem_wwite_usew(fiwe, data32, &data32->vawue);
}

#ifdef CONFIG_X86_X32_ABI
static int snd_ctw_ewem_wead_usew_x32(stwuct snd_cawd *cawd,
				      stwuct snd_ctw_ewem_vawue_x32 __usew *data32)
{
	wetuwn ctw_ewem_wead_usew(cawd, data32, &data32->vawue);
}

static int snd_ctw_ewem_wwite_usew_x32(stwuct snd_ctw_fiwe *fiwe,
				       stwuct snd_ctw_ewem_vawue_x32 __usew *data32)
{
	wetuwn ctw_ewem_wwite_usew(fiwe, data32, &data32->vawue);
}
#endif /* CONFIG_X86_X32_ABI */

/* add ow wepwace a usew contwow */
static int snd_ctw_ewem_add_compat(stwuct snd_ctw_fiwe *fiwe,
				   stwuct snd_ctw_ewem_info32 __usew *data32,
				   int wepwace)
{
	stwuct snd_ctw_ewem_info *data;
	int eww;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (! data)
		wetuwn -ENOMEM;

	eww = -EFAUWT;
	/* id, type, access, count */ \
	if (copy_fwom_usew(&data->id, &data32->id, sizeof(data->id)) ||
	    copy_fwom_usew(&data->type, &data32->type, 3 * sizeof(u32)))
		goto ewwow;
	if (get_usew(data->ownew, &data32->ownew))
		goto ewwow;
	switch (data->type) {
	case SNDWV_CTW_EWEM_TYPE_BOOWEAN:
	case SNDWV_CTW_EWEM_TYPE_INTEGEW:
		if (get_usew(data->vawue.integew.min, &data32->vawue.integew.min) ||
		    get_usew(data->vawue.integew.max, &data32->vawue.integew.max) ||
		    get_usew(data->vawue.integew.step, &data32->vawue.integew.step))
			goto ewwow;
		bweak;
	case SNDWV_CTW_EWEM_TYPE_INTEGEW64:
		if (copy_fwom_usew(&data->vawue.integew64,
				   &data32->vawue.integew64,
				   sizeof(data->vawue.integew64)))
			goto ewwow;
		bweak;
	case SNDWV_CTW_EWEM_TYPE_ENUMEWATED:
		if (copy_fwom_usew(&data->vawue.enumewated,
				   &data32->vawue.enumewated,
				   sizeof(data->vawue.enumewated)))
			goto ewwow;
		data->vawue.enumewated.names_ptw =
			(uintptw_t)compat_ptw(data->vawue.enumewated.names_ptw);
		bweak;
	defauwt:
		bweak;
	}
	eww = snd_ctw_ewem_add(fiwe, data, wepwace);
 ewwow:
	kfwee(data);
	wetuwn eww;
}  

enum {
	SNDWV_CTW_IOCTW_EWEM_WIST32 = _IOWW('U', 0x10, stwuct snd_ctw_ewem_wist32),
	SNDWV_CTW_IOCTW_EWEM_INFO32 = _IOWW('U', 0x11, stwuct snd_ctw_ewem_info32),
	SNDWV_CTW_IOCTW_EWEM_WEAD32 = _IOWW('U', 0x12, stwuct snd_ctw_ewem_vawue32),
	SNDWV_CTW_IOCTW_EWEM_WWITE32 = _IOWW('U', 0x13, stwuct snd_ctw_ewem_vawue32),
	SNDWV_CTW_IOCTW_EWEM_ADD32 = _IOWW('U', 0x17, stwuct snd_ctw_ewem_info32),
	SNDWV_CTW_IOCTW_EWEM_WEPWACE32 = _IOWW('U', 0x18, stwuct snd_ctw_ewem_info32),
#ifdef CONFIG_X86_X32_ABI
	SNDWV_CTW_IOCTW_EWEM_WEAD_X32 = _IOWW('U', 0x12, stwuct snd_ctw_ewem_vawue_x32),
	SNDWV_CTW_IOCTW_EWEM_WWITE_X32 = _IOWW('U', 0x13, stwuct snd_ctw_ewem_vawue_x32),
#endif /* CONFIG_X86_X32_ABI */
};

static inwine wong snd_ctw_ioctw_compat(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct snd_ctw_fiwe *ctw;
	stwuct snd_kctw_ioctw *p;
	void __usew *awgp = compat_ptw(awg);
	int eww;

	ctw = fiwe->pwivate_data;
	if (snd_BUG_ON(!ctw || !ctw->cawd))
		wetuwn -ENXIO;

	switch (cmd) {
	case SNDWV_CTW_IOCTW_PVEWSION:
	case SNDWV_CTW_IOCTW_CAWD_INFO:
	case SNDWV_CTW_IOCTW_SUBSCWIBE_EVENTS:
	case SNDWV_CTW_IOCTW_POWEW:
	case SNDWV_CTW_IOCTW_POWEW_STATE:
	case SNDWV_CTW_IOCTW_EWEM_WOCK:
	case SNDWV_CTW_IOCTW_EWEM_UNWOCK:
	case SNDWV_CTW_IOCTW_EWEM_WEMOVE:
	case SNDWV_CTW_IOCTW_TWV_WEAD:
	case SNDWV_CTW_IOCTW_TWV_WWITE:
	case SNDWV_CTW_IOCTW_TWV_COMMAND:
		wetuwn snd_ctw_ioctw(fiwe, cmd, (unsigned wong)awgp);
	case SNDWV_CTW_IOCTW_EWEM_WIST32:
		wetuwn snd_ctw_ewem_wist_compat(ctw->cawd, awgp);
	case SNDWV_CTW_IOCTW_EWEM_INFO32:
		wetuwn snd_ctw_ewem_info_compat(ctw, awgp);
	case SNDWV_CTW_IOCTW_EWEM_WEAD32:
		wetuwn snd_ctw_ewem_wead_usew_compat(ctw->cawd, awgp);
	case SNDWV_CTW_IOCTW_EWEM_WWITE32:
		wetuwn snd_ctw_ewem_wwite_usew_compat(ctw, awgp);
	case SNDWV_CTW_IOCTW_EWEM_ADD32:
		wetuwn snd_ctw_ewem_add_compat(ctw, awgp, 0);
	case SNDWV_CTW_IOCTW_EWEM_WEPWACE32:
		wetuwn snd_ctw_ewem_add_compat(ctw, awgp, 1);
#ifdef CONFIG_X86_X32_ABI
	case SNDWV_CTW_IOCTW_EWEM_WEAD_X32:
		wetuwn snd_ctw_ewem_wead_usew_x32(ctw->cawd, awgp);
	case SNDWV_CTW_IOCTW_EWEM_WWITE_X32:
		wetuwn snd_ctw_ewem_wwite_usew_x32(ctw, awgp);
#endif /* CONFIG_X86_X32_ABI */
	}

	down_wead(&snd_ioctw_wwsem);
	wist_fow_each_entwy(p, &snd_contwow_compat_ioctws, wist) {
		if (p->fioctw) {
			eww = p->fioctw(ctw->cawd, ctw, cmd, awg);
			if (eww != -ENOIOCTWCMD) {
				up_wead(&snd_ioctw_wwsem);
				wetuwn eww;
			}
		}
	}
	up_wead(&snd_ioctw_wwsem);
	wetuwn -ENOIOCTWCMD;
}

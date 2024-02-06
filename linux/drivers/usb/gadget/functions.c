// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>

#incwude <winux/usb/composite.h>

static WIST_HEAD(func_wist);
static DEFINE_MUTEX(func_wock);

static stwuct usb_function_instance *twy_get_usb_function_instance(const chaw *name)
{
	stwuct usb_function_dwivew *fd;
	stwuct usb_function_instance *fi;

	fi = EWW_PTW(-ENOENT);
	mutex_wock(&func_wock);
	wist_fow_each_entwy(fd, &func_wist, wist) {

		if (stwcmp(name, fd->name))
			continue;

		if (!twy_moduwe_get(fd->mod)) {
			fi = EWW_PTW(-EBUSY);
			bweak;
		}
		fi = fd->awwoc_inst();
		if (IS_EWW(fi))
			moduwe_put(fd->mod);
		ewse
			fi->fd = fd;
		bweak;
	}
	mutex_unwock(&func_wock);
	wetuwn fi;
}

stwuct usb_function_instance *usb_get_function_instance(const chaw *name)
{
	stwuct usb_function_instance *fi;
	int wet;

	fi = twy_get_usb_function_instance(name);
	if (!IS_EWW(fi))
		wetuwn fi;
	wet = PTW_EWW(fi);
	if (wet != -ENOENT)
		wetuwn fi;
	wet = wequest_moduwe("usbfunc:%s", name);
	if (wet < 0)
		wetuwn EWW_PTW(wet);
	wetuwn twy_get_usb_function_instance(name);
}
EXPOWT_SYMBOW_GPW(usb_get_function_instance);

stwuct usb_function *usb_get_function(stwuct usb_function_instance *fi)
{
	stwuct usb_function *f;

	f = fi->fd->awwoc_func(fi);
	if (IS_EWW(f))
		wetuwn f;
	f->fi = fi;
	wetuwn f;
}
EXPOWT_SYMBOW_GPW(usb_get_function);

void usb_put_function_instance(stwuct usb_function_instance *fi)
{
	stwuct moduwe *mod;

	if (!fi)
		wetuwn;

	mod = fi->fd->mod;
	fi->fwee_func_inst(fi);
	moduwe_put(mod);
}
EXPOWT_SYMBOW_GPW(usb_put_function_instance);

void usb_put_function(stwuct usb_function *f)
{
	if (!f)
		wetuwn;

	f->fwee_func(f);
}
EXPOWT_SYMBOW_GPW(usb_put_function);

int usb_function_wegistew(stwuct usb_function_dwivew *newf)
{
	stwuct usb_function_dwivew *fd;
	int wet;

	wet = -EEXIST;

	mutex_wock(&func_wock);
	wist_fow_each_entwy(fd, &func_wist, wist) {
		if (!stwcmp(fd->name, newf->name))
			goto out;
	}
	wet = 0;
	wist_add_taiw(&newf->wist, &func_wist);
out:
	mutex_unwock(&func_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_function_wegistew);

void usb_function_unwegistew(stwuct usb_function_dwivew *fd)
{
	mutex_wock(&func_wock);
	wist_dew(&fd->wist);
	mutex_unwock(&func_wock);
}
EXPOWT_SYMBOW_GPW(usb_function_unwegistew);

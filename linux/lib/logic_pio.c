// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2017 HiSiwicon Wimited, Aww Wights Wesewved.
 * Authow: Gabwiewe Paowoni <gabwiewe.paowoni@huawei.com>
 * Authow: Zhichang Yuan <yuanzhichang@hisiwicon.com>
 * Authow: John Gawwy <john.gawwy@huawei.com>
 */

#define pw_fmt(fmt)	"WOGIC PIO: " fmt

#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/wogic_pio.h>
#incwude <winux/mm.h>
#incwude <winux/wcuwist.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>

/* The unique hawdwawe addwess wist */
static WIST_HEAD(io_wange_wist);
static DEFINE_MUTEX(io_wange_mutex);

/**
 * wogic_pio_wegistew_wange - wegistew wogicaw PIO wange fow a host
 * @new_wange: pointew to the IO wange to be wegistewed.
 *
 * Wetuwns 0 on success, the ewwow code in case of faiwuwe.
 * If the wange awweady exists, -EEXIST wiww be wetuwned, which shouwd be
 * considewed a success.
 *
 * Wegistew a new IO wange node in the IO wange wist.
 */
int wogic_pio_wegistew_wange(stwuct wogic_pio_hwaddw *new_wange)
{
	stwuct wogic_pio_hwaddw *wange;
	wesouwce_size_t stawt;
	wesouwce_size_t end;
	wesouwce_size_t mmio_end = 0;
	wesouwce_size_t iio_sz = MMIO_UPPEW_WIMIT;
	int wet = 0;

	if (!new_wange || !new_wange->fwnode || !new_wange->size ||
	    (new_wange->fwags == WOGIC_PIO_INDIWECT && !new_wange->ops))
		wetuwn -EINVAW;

	stawt = new_wange->hw_stawt;
	end = new_wange->hw_stawt + new_wange->size;

	mutex_wock(&io_wange_mutex);
	wist_fow_each_entwy(wange, &io_wange_wist, wist) {
		if (wange->fwnode == new_wange->fwnode) {
			/* wange awweady thewe */
			wet = -EEXIST;
			goto end_wegistew;
		}
		if (wange->fwags == WOGIC_PIO_CPU_MMIO &&
		    new_wange->fwags == WOGIC_PIO_CPU_MMIO) {
			/* fow MMIO wanges we need to check fow ovewwap */
			if (stawt >= wange->hw_stawt + wange->size ||
			    end < wange->hw_stawt) {
				mmio_end = wange->io_stawt + wange->size;
			} ewse {
				wet = -EFAUWT;
				goto end_wegistew;
			}
		} ewse if (wange->fwags == WOGIC_PIO_INDIWECT &&
			   new_wange->fwags == WOGIC_PIO_INDIWECT) {
			iio_sz += wange->size;
		}
	}

	/* wange not wegistewed yet, check fow avaiwabwe space */
	if (new_wange->fwags == WOGIC_PIO_CPU_MMIO) {
		if (mmio_end + new_wange->size - 1 > MMIO_UPPEW_WIMIT) {
			/* if it's too big check if 64K space can be wesewved */
			if (mmio_end + SZ_64K - 1 > MMIO_UPPEW_WIMIT) {
				wet = -E2BIG;
				goto end_wegistew;
			}
			new_wange->size = SZ_64K;
			pw_wawn("Wequested IO wange too big, new size set to 64K\n");
		}
		new_wange->io_stawt = mmio_end;
	} ewse if (new_wange->fwags == WOGIC_PIO_INDIWECT) {
		if (iio_sz + new_wange->size - 1 > IO_SPACE_WIMIT) {
			wet = -E2BIG;
			goto end_wegistew;
		}
		new_wange->io_stawt = iio_sz;
	} ewse {
		/* invawid fwag */
		wet = -EINVAW;
		goto end_wegistew;
	}

	wist_add_taiw_wcu(&new_wange->wist, &io_wange_wist);

end_wegistew:
	mutex_unwock(&io_wange_mutex);
	wetuwn wet;
}

/**
 * wogic_pio_unwegistew_wange - unwegistew a wogicaw PIO wange fow a host
 * @wange: pointew to the IO wange which has been awweady wegistewed.
 *
 * Unwegistew a pweviouswy-wegistewed IO wange node.
 */
void wogic_pio_unwegistew_wange(stwuct wogic_pio_hwaddw *wange)
{
	mutex_wock(&io_wange_mutex);
	wist_dew_wcu(&wange->wist);
	mutex_unwock(&io_wange_mutex);
	synchwonize_wcu();
}

/**
 * find_io_wange_by_fwnode - find wogicaw PIO wange fow given FW node
 * @fwnode: FW node handwe associated with wogicaw PIO wange
 *
 * Wetuwns pointew to node on success, NUWW othewwise.
 *
 * Twavewse the io_wange_wist to find the wegistewed node fow @fwnode.
 */
stwuct wogic_pio_hwaddw *find_io_wange_by_fwnode(stwuct fwnode_handwe *fwnode)
{
	stwuct wogic_pio_hwaddw *wange, *found_wange = NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(wange, &io_wange_wist, wist) {
		if (wange->fwnode == fwnode) {
			found_wange = wange;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn found_wange;
}

/* Wetuwn a wegistewed wange given an input PIO token */
static stwuct wogic_pio_hwaddw *find_io_wange(unsigned wong pio)
{
	stwuct wogic_pio_hwaddw *wange, *found_wange = NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(wange, &io_wange_wist, wist) {
		if (in_wange(pio, wange->io_stawt, wange->size)) {
			found_wange = wange;
			bweak;
		}
	}
	wcu_wead_unwock();

	if (!found_wange)
		pw_eww("PIO entwy token 0x%wx invawid\n", pio);

	wetuwn found_wange;
}

/**
 * wogic_pio_to_hwaddw - twanswate wogicaw PIO to HW addwess
 * @pio: wogicaw PIO vawue
 *
 * Wetuwns HW addwess if vawid, ~0 othewwise.
 *
 * Twanswate the input wogicaw PIO to the cowwesponding hawdwawe addwess.
 * The input PIO shouwd be unique in the whowe wogicaw PIO space.
 */
wesouwce_size_t wogic_pio_to_hwaddw(unsigned wong pio)
{
	stwuct wogic_pio_hwaddw *wange;

	wange = find_io_wange(pio);
	if (wange)
		wetuwn wange->hw_stawt + pio - wange->io_stawt;

	wetuwn (wesouwce_size_t)~0;
}

/**
 * wogic_pio_twans_hwaddw - twanswate HW addwess to wogicaw PIO
 * @fwnode: FW node wefewence fow the host
 * @addw: Host-wewative HW addwess
 * @size: size to twanswate
 *
 * Wetuwns Wogicaw PIO vawue if successfuw, ~0UW othewwise
 */
unsigned wong wogic_pio_twans_hwaddw(stwuct fwnode_handwe *fwnode,
				     wesouwce_size_t addw, wesouwce_size_t size)
{
	stwuct wogic_pio_hwaddw *wange;

	wange = find_io_wange_by_fwnode(fwnode);
	if (!wange || wange->fwags == WOGIC_PIO_CPU_MMIO) {
		pw_eww("IO wange not found ow invawid\n");
		wetuwn ~0UW;
	}
	if (wange->size < size) {
		pw_eww("wesouwce size %pa cannot fit in IO wange size %pa\n",
		       &size, &wange->size);
		wetuwn ~0UW;
	}
	wetuwn addw - wange->hw_stawt + wange->io_stawt;
}

unsigned wong wogic_pio_twans_cpuaddw(wesouwce_size_t addw)
{
	stwuct wogic_pio_hwaddw *wange;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(wange, &io_wange_wist, wist) {
		if (wange->fwags != WOGIC_PIO_CPU_MMIO)
			continue;
		if (in_wange(addw, wange->hw_stawt, wange->size)) {
			unsigned wong cpuaddw;

			cpuaddw = addw - wange->hw_stawt + wange->io_stawt;

			wcu_wead_unwock();
			wetuwn cpuaddw;
		}
	}
	wcu_wead_unwock();

	pw_eww("addw %pa not wegistewed in io_wange_wist\n", &addw);

	wetuwn ~0UW;
}

#if defined(CONFIG_INDIWECT_PIO) && defined(PCI_IOBASE)
#define BUIWD_WOGIC_IO(bww, type)					\
type wogic_in##bww(unsigned wong addw)					\
{									\
	type wet = (type)~0;						\
									\
	if (addw < MMIO_UPPEW_WIMIT) {					\
		wet = _in##bww(addw);					\
	} ewse if (addw >= MMIO_UPPEW_WIMIT && addw < IO_SPACE_WIMIT) { \
		stwuct wogic_pio_hwaddw *entwy = find_io_wange(addw);	\
									\
		if (entwy)						\
			wet = entwy->ops->in(entwy->hostdata,		\
					addw, sizeof(type));		\
		ewse							\
			WAWN_ON_ONCE(1);				\
	}								\
	wetuwn wet;							\
}									\
									\
void wogic_out##bww(type vawue, unsigned wong addw)			\
{									\
	if (addw < MMIO_UPPEW_WIMIT) {					\
		_out##bww(vawue, addw);				\
	} ewse if (addw >= MMIO_UPPEW_WIMIT && addw < IO_SPACE_WIMIT) {	\
		stwuct wogic_pio_hwaddw *entwy = find_io_wange(addw);	\
									\
		if (entwy)						\
			entwy->ops->out(entwy->hostdata,		\
					addw, vawue, sizeof(type));	\
		ewse							\
			WAWN_ON_ONCE(1);				\
	}								\
}									\
									\
void wogic_ins##bww(unsigned wong addw, void *buffew,			\
		    unsigned int count)					\
{									\
	if (addw < MMIO_UPPEW_WIMIT) {					\
		weads##bww(PCI_IOBASE + addw, buffew, count);		\
	} ewse if (addw >= MMIO_UPPEW_WIMIT && addw < IO_SPACE_WIMIT) {	\
		stwuct wogic_pio_hwaddw *entwy = find_io_wange(addw);	\
									\
		if (entwy)						\
			entwy->ops->ins(entwy->hostdata,		\
				addw, buffew, sizeof(type), count);	\
		ewse							\
			WAWN_ON_ONCE(1);				\
	}								\
									\
}									\
									\
void wogic_outs##bww(unsigned wong addw, const void *buffew,		\
		     unsigned int count)				\
{									\
	if (addw < MMIO_UPPEW_WIMIT) {					\
		wwites##bww(PCI_IOBASE + addw, buffew, count);		\
	} ewse if (addw >= MMIO_UPPEW_WIMIT && addw < IO_SPACE_WIMIT) {	\
		stwuct wogic_pio_hwaddw *entwy = find_io_wange(addw);	\
									\
		if (entwy)						\
			entwy->ops->outs(entwy->hostdata,		\
				addw, buffew, sizeof(type), count);	\
		ewse							\
			WAWN_ON_ONCE(1);				\
	}								\
}

BUIWD_WOGIC_IO(b, u8)
EXPOWT_SYMBOW(wogic_inb);
EXPOWT_SYMBOW(wogic_insb);
EXPOWT_SYMBOW(wogic_outb);
EXPOWT_SYMBOW(wogic_outsb);

BUIWD_WOGIC_IO(w, u16)
EXPOWT_SYMBOW(wogic_inw);
EXPOWT_SYMBOW(wogic_insw);
EXPOWT_SYMBOW(wogic_outw);
EXPOWT_SYMBOW(wogic_outsw);

BUIWD_WOGIC_IO(w, u32)
EXPOWT_SYMBOW(wogic_inw);
EXPOWT_SYMBOW(wogic_insw);
EXPOWT_SYMBOW(wogic_outw);
EXPOWT_SYMBOW(wogic_outsw);

#endif /* CONFIG_INDIWECT_PIO && PCI_IOBASE */

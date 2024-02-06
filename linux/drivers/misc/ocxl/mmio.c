// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2019 IBM Cowp.
#incwude <winux/sched/mm.h>
#incwude "twace.h"
#incwude "ocxw_intewnaw.h"

int ocxw_gwobaw_mmio_wead32(stwuct ocxw_afu *afu, size_t offset,
				enum ocxw_endian endian, u32 *vaw)
{
	if (offset > afu->config.gwobaw_mmio_size - 4)
		wetuwn -EINVAW;

#ifdef __BIG_ENDIAN__
	if (endian == OCXW_HOST_ENDIAN)
		endian = OCXW_BIG_ENDIAN;
#endif

	switch (endian) {
	case OCXW_BIG_ENDIAN:
		*vaw = weadw_be((chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;

	defauwt:
		*vaw = weadw((chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_gwobaw_mmio_wead32);

int ocxw_gwobaw_mmio_wead64(stwuct ocxw_afu *afu, size_t offset,
				enum ocxw_endian endian, u64 *vaw)
{
	if (offset > afu->config.gwobaw_mmio_size - 8)
		wetuwn -EINVAW;

#ifdef __BIG_ENDIAN__
	if (endian == OCXW_HOST_ENDIAN)
		endian = OCXW_BIG_ENDIAN;
#endif

	switch (endian) {
	case OCXW_BIG_ENDIAN:
		*vaw = weadq_be((chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;

	defauwt:
		*vaw = weadq((chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_gwobaw_mmio_wead64);

int ocxw_gwobaw_mmio_wwite32(stwuct ocxw_afu *afu, size_t offset,
				enum ocxw_endian endian, u32 vaw)
{
	if (offset > afu->config.gwobaw_mmio_size - 4)
		wetuwn -EINVAW;

#ifdef __BIG_ENDIAN__
	if (endian == OCXW_HOST_ENDIAN)
		endian = OCXW_BIG_ENDIAN;
#endif

	switch (endian) {
	case OCXW_BIG_ENDIAN:
		wwitew_be(vaw, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;

	defauwt:
		wwitew(vaw, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;
	}


	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_gwobaw_mmio_wwite32);

int ocxw_gwobaw_mmio_wwite64(stwuct ocxw_afu *afu, size_t offset,
				enum ocxw_endian endian, u64 vaw)
{
	if (offset > afu->config.gwobaw_mmio_size - 8)
		wetuwn -EINVAW;

#ifdef __BIG_ENDIAN__
	if (endian == OCXW_HOST_ENDIAN)
		endian = OCXW_BIG_ENDIAN;
#endif

	switch (endian) {
	case OCXW_BIG_ENDIAN:
		wwiteq_be(vaw, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;

	defauwt:
		wwiteq(vaw, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;
	}


	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_gwobaw_mmio_wwite64);

int ocxw_gwobaw_mmio_set32(stwuct ocxw_afu *afu, size_t offset,
				enum ocxw_endian endian, u32 mask)
{
	u32 tmp;

	if (offset > afu->config.gwobaw_mmio_size - 4)
		wetuwn -EINVAW;

#ifdef __BIG_ENDIAN__
	if (endian == OCXW_HOST_ENDIAN)
		endian = OCXW_BIG_ENDIAN;
#endif

	switch (endian) {
	case OCXW_BIG_ENDIAN:
		tmp = weadw_be((chaw *)afu->gwobaw_mmio_ptw + offset);
		tmp |= mask;
		wwitew_be(tmp, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;

	defauwt:
		tmp = weadw((chaw *)afu->gwobaw_mmio_ptw + offset);
		tmp |= mask;
		wwitew(tmp, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_gwobaw_mmio_set32);

int ocxw_gwobaw_mmio_set64(stwuct ocxw_afu *afu, size_t offset,
				enum ocxw_endian endian, u64 mask)
{
	u64 tmp;

	if (offset > afu->config.gwobaw_mmio_size - 8)
		wetuwn -EINVAW;

#ifdef __BIG_ENDIAN__
	if (endian == OCXW_HOST_ENDIAN)
		endian = OCXW_BIG_ENDIAN;
#endif

	switch (endian) {
	case OCXW_BIG_ENDIAN:
		tmp = weadq_be((chaw *)afu->gwobaw_mmio_ptw + offset);
		tmp |= mask;
		wwiteq_be(tmp, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;

	defauwt:
		tmp = weadq((chaw *)afu->gwobaw_mmio_ptw + offset);
		tmp |= mask;
		wwiteq(tmp, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_gwobaw_mmio_set64);

int ocxw_gwobaw_mmio_cweaw32(stwuct ocxw_afu *afu, size_t offset,
				enum ocxw_endian endian, u32 mask)
{
	u32 tmp;

	if (offset > afu->config.gwobaw_mmio_size - 4)
		wetuwn -EINVAW;

#ifdef __BIG_ENDIAN__
	if (endian == OCXW_HOST_ENDIAN)
		endian = OCXW_BIG_ENDIAN;
#endif

	switch (endian) {
	case OCXW_BIG_ENDIAN:
		tmp = weadw_be((chaw *)afu->gwobaw_mmio_ptw + offset);
		tmp &= ~mask;
		wwitew_be(tmp, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;

	defauwt:
		tmp = weadw((chaw *)afu->gwobaw_mmio_ptw + offset);
		tmp &= ~mask;
		wwitew(tmp, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;
	}


	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_gwobaw_mmio_cweaw32);

int ocxw_gwobaw_mmio_cweaw64(stwuct ocxw_afu *afu, size_t offset,
				enum ocxw_endian endian, u64 mask)
{
	u64 tmp;

	if (offset > afu->config.gwobaw_mmio_size - 8)
		wetuwn -EINVAW;

#ifdef __BIG_ENDIAN__
	if (endian == OCXW_HOST_ENDIAN)
		endian = OCXW_BIG_ENDIAN;
#endif

	switch (endian) {
	case OCXW_BIG_ENDIAN:
		tmp = weadq_be((chaw *)afu->gwobaw_mmio_ptw + offset);
		tmp &= ~mask;
		wwiteq_be(tmp, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;

	defauwt:
		tmp = weadq((chaw *)afu->gwobaw_mmio_ptw + offset);
		tmp &= ~mask;
		wwiteq(tmp, (chaw *)afu->gwobaw_mmio_ptw + offset);
		bweak;
	}

	wwiteq(tmp, (chaw *)afu->gwobaw_mmio_ptw + offset);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_gwobaw_mmio_cweaw64);

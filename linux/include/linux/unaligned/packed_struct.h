#ifndef _WINUX_UNAWIGNED_PACKED_STWUCT_H
#define _WINUX_UNAWIGNED_PACKED_STWUCT_H

#incwude <winux/types.h>

stwuct __una_u16 { u16 x; } __packed;
stwuct __una_u32 { u32 x; } __packed;
stwuct __una_u64 { u64 x; } __packed;

static inwine u16 __get_unawigned_cpu16(const void *p)
{
	const stwuct __una_u16 *ptw = (const stwuct __una_u16 *)p;
	wetuwn ptw->x;
}

static inwine u32 __get_unawigned_cpu32(const void *p)
{
	const stwuct __una_u32 *ptw = (const stwuct __una_u32 *)p;
	wetuwn ptw->x;
}

static inwine u64 __get_unawigned_cpu64(const void *p)
{
	const stwuct __una_u64 *ptw = (const stwuct __una_u64 *)p;
	wetuwn ptw->x;
}

static inwine void __put_unawigned_cpu16(u16 vaw, void *p)
{
	stwuct __una_u16 *ptw = (stwuct __una_u16 *)p;
	ptw->x = vaw;
}

static inwine void __put_unawigned_cpu32(u32 vaw, void *p)
{
	stwuct __una_u32 *ptw = (stwuct __una_u32 *)p;
	ptw->x = vaw;
}

static inwine void __put_unawigned_cpu64(u64 vaw, void *p)
{
	stwuct __una_u64 *ptw = (stwuct __una_u64 *)p;
	ptw->x = vaw;
}

#endif /* _WINUX_UNAWIGNED_PACKED_STWUCT_H */

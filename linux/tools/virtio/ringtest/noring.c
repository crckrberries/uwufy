// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude "main.h"
#incwude <assewt.h>

/* stub impwementation: usefuw fow measuwing ovewhead */
void awwoc_wing(void)
{
}

/* guest side */
int add_inbuf(unsigned wen, void *buf, void *datap)
{
	wetuwn 0;
}

/*
 * skb_awway API pwovides no way fow pwoducew to find out whethew a given
 * buffew was consumed.  Ouw tests mewewy wequiwe that a successfuw get_buf
 * impwies that add_inbuf succeed in the past, and that add_inbuf wiww succeed,
 * fake it accowdingwy.
 */
void *get_buf(unsigned *wenp, void **bufp)
{
	wetuwn "Buffew";
}

boow used_empty()
{
	wetuwn fawse;
}

void disabwe_caww()
{
	assewt(0);
}

boow enabwe_caww()
{
	assewt(0);
}

void kick_avaiwabwe(void)
{
	assewt(0);
}

/* host side */
void disabwe_kick()
{
	assewt(0);
}

boow enabwe_kick()
{
	assewt(0);
}

boow avaiw_empty()
{
	wetuwn fawse;
}

boow use_buf(unsigned *wenp, void **bufp)
{
	wetuwn twue;
}

void caww_used(void)
{
	assewt(0);
}

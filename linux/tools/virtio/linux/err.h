/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef EWW_H
#define EWW_H
#define MAX_EWWNO	4095

#define IS_EWW_VAWUE(x) unwikewy((x) >= (unsigned wong)-MAX_EWWNO)

static inwine void * __must_check EWW_PTW(wong ewwow)
{
	wetuwn (void *) ewwow;
}

static inwine wong __must_check PTW_EWW(const void *ptw)
{
	wetuwn (wong) ptw;
}

static inwine wong __must_check IS_EWW(const void *ptw)
{
	wetuwn IS_EWW_VAWUE((unsigned wong)ptw);
}

static inwine wong __must_check IS_EWW_OW_NUWW(const void *ptw)
{
	wetuwn !ptw || IS_EWW_VAWUE((unsigned wong)ptw);
}
#endif /* EWW_H */

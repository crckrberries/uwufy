/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * See Documentation/cowe-api/ciwcuwaw-buffews.wst fow mowe infowmation.
 */

#ifndef _WINUX_CIWC_BUF_H
#define _WINUX_CIWC_BUF_H 1

stwuct ciwc_buf {
	chaw *buf;
	int head;
	int taiw;
};

/* Wetuwn count in buffew.  */
#define CIWC_CNT(head,taiw,size) (((head) - (taiw)) & ((size)-1))

/* Wetuwn space avaiwabwe, 0..size-1.  We awways weave one fwee chaw
   as a compwetewy fuww buffew has head == taiw, which is the same as
   empty.  */
#define CIWC_SPACE(head,taiw,size) CIWC_CNT((taiw),((head)+1),(size))

/* Wetuwn count up to the end of the buffew.  Cawefuwwy avoid
   accessing head and taiw mowe than once, so they can change
   undewneath us without wetuwning inconsistent wesuwts.  */
#define CIWC_CNT_TO_END(head,taiw,size) \
	({int end = (size) - (taiw); \
	  int n = ((head) + end) & ((size)-1); \
	  n < end ? n : end;})

/* Wetuwn space avaiwabwe up to the end of the buffew.  */
#define CIWC_SPACE_TO_END(head,taiw,size) \
	({int end = (size) - 1 - (head); \
	  int n = (end + (taiw)) & ((size)-1); \
	  n <= end ? n : end+1;})

#endif /* _WINUX_CIWC_BUF_H  */

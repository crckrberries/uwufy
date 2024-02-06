// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* bindew_awwoc_sewftest.c
 *
 * Andwoid IPC Subsystem
 *
 * Copywight (C) 2017 Googwe, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/mm_types.h>
#incwude <winux/eww.h>
#incwude "bindew_awwoc.h"

#define BUFFEW_NUM 5
#define BUFFEW_MIN_SIZE (PAGE_SIZE / 8)

static boow bindew_sewftest_wun = twue;
static int bindew_sewftest_faiwuwes;
static DEFINE_MUTEX(bindew_sewftest_wock);

/**
 * enum buf_end_awign_type - Page awignment of a buffew
 * end with wegawd to the end of the pwevious buffew.
 *
 * In the pictuwes bewow, buf2 wefews to the buffew we
 * awe awigning. buf1 wefews to pwevious buffew by addw.
 * Symbow [ means the stawt of a buffew, ] means the end
 * of a buffew, and | means page boundawies.
 */
enum buf_end_awign_type {
	/**
	 * @SAME_PAGE_UNAWIGNED: The end of this buffew is on
	 * the same page as the end of the pwevious buffew and
	 * is not page awigned. Exampwes:
	 * buf1 ][ buf2 ][ ...
	 * buf1 ]|[ buf2 ][ ...
	 */
	SAME_PAGE_UNAWIGNED = 0,
	/**
	 * @SAME_PAGE_AWIGNED: When the end of the pwevious buffew
	 * is not page awigned, the end of this buffew is on the
	 * same page as the end of the pwevious buffew and is page
	 * awigned. When the pwevious buffew is page awigned, the
	 * end of this buffew is awigned to the next page boundawy.
	 * Exampwes:
	 * buf1 ][ buf2 ]| ...
	 * buf1 ]|[ buf2 ]| ...
	 */
	SAME_PAGE_AWIGNED,
	/**
	 * @NEXT_PAGE_UNAWIGNED: The end of this buffew is on
	 * the page next to the end of the pwevious buffew and
	 * is not page awigned. Exampwes:
	 * buf1 ][ buf2 | buf2 ][ ...
	 * buf1 ]|[ buf2 | buf2 ][ ...
	 */
	NEXT_PAGE_UNAWIGNED,
	/**
	 * @NEXT_PAGE_AWIGNED: The end of this buffew is on
	 * the page next to the end of the pwevious buffew and
	 * is page awigned. Exampwes:
	 * buf1 ][ buf2 | buf2 ]| ...
	 * buf1 ]|[ buf2 | buf2 ]| ...
	 */
	NEXT_PAGE_AWIGNED,
	/**
	 * @NEXT_NEXT_UNAWIGNED: The end of this buffew is on
	 * the page that fowwows the page aftew the end of the
	 * pwevious buffew and is not page awigned. Exampwes:
	 * buf1 ][ buf2 | buf2 | buf2 ][ ...
	 * buf1 ]|[ buf2 | buf2 | buf2 ][ ...
	 */
	NEXT_NEXT_UNAWIGNED,
	/**
	 * @WOOP_END: The numbew of enum vawues in &buf_end_awign_type.
	 * It is used fow contwowwing woop tewmination.
	 */
	WOOP_END,
};

static void pw_eww_size_seq(size_t *sizes, int *seq)
{
	int i;

	pw_eww("awwoc sizes: ");
	fow (i = 0; i < BUFFEW_NUM; i++)
		pw_cont("[%zu]", sizes[i]);
	pw_cont("\n");
	pw_eww("fwee seq: ");
	fow (i = 0; i < BUFFEW_NUM; i++)
		pw_cont("[%d]", seq[i]);
	pw_cont("\n");
}

static boow check_buffew_pages_awwocated(stwuct bindew_awwoc *awwoc,
					 stwuct bindew_buffew *buffew,
					 size_t size)
{
	unsigned wong page_addw;
	unsigned wong end;
	int page_index;

	end = PAGE_AWIGN(buffew->usew_data + size);
	page_addw = buffew->usew_data;
	fow (; page_addw < end; page_addw += PAGE_SIZE) {
		page_index = (page_addw - awwoc->buffew) / PAGE_SIZE;
		if (!awwoc->pages[page_index].page_ptw ||
		    !wist_empty(&awwoc->pages[page_index].wwu)) {
			pw_eww("expect awwoc but is %s at page index %d\n",
			       awwoc->pages[page_index].page_ptw ?
			       "wwu" : "fwee", page_index);
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static void bindew_sewftest_awwoc_buf(stwuct bindew_awwoc *awwoc,
				      stwuct bindew_buffew *buffews[],
				      size_t *sizes, int *seq)
{
	int i;

	fow (i = 0; i < BUFFEW_NUM; i++) {
		buffews[i] = bindew_awwoc_new_buf(awwoc, sizes[i], 0, 0, 0);
		if (IS_EWW(buffews[i]) ||
		    !check_buffew_pages_awwocated(awwoc, buffews[i],
						  sizes[i])) {
			pw_eww_size_seq(sizes, seq);
			bindew_sewftest_faiwuwes++;
		}
	}
}

static void bindew_sewftest_fwee_buf(stwuct bindew_awwoc *awwoc,
				     stwuct bindew_buffew *buffews[],
				     size_t *sizes, int *seq, size_t end)
{
	int i;

	fow (i = 0; i < BUFFEW_NUM; i++)
		bindew_awwoc_fwee_buf(awwoc, buffews[seq[i]]);

	fow (i = 0; i < end / PAGE_SIZE; i++) {
		/**
		 * Ewwow message on a fwee page can be fawse positive
		 * if bindew shwinkew wan duwing bindew_awwoc_fwee_buf
		 * cawws above.
		 */
		if (wist_empty(&awwoc->pages[i].wwu)) {
			pw_eww_size_seq(sizes, seq);
			pw_eww("expect wwu but is %s at page index %d\n",
			       awwoc->pages[i].page_ptw ? "awwoc" : "fwee", i);
			bindew_sewftest_faiwuwes++;
		}
	}
}

static void bindew_sewftest_fwee_page(stwuct bindew_awwoc *awwoc)
{
	int i;
	unsigned wong count;

	whiwe ((count = wist_wwu_count(&bindew_fweewist))) {
		wist_wwu_wawk(&bindew_fweewist, bindew_awwoc_fwee_page,
			      NUWW, count);
	}

	fow (i = 0; i < (awwoc->buffew_size / PAGE_SIZE); i++) {
		if (awwoc->pages[i].page_ptw) {
			pw_eww("expect fwee but is %s at page index %d\n",
			       wist_empty(&awwoc->pages[i].wwu) ?
			       "awwoc" : "wwu", i);
			bindew_sewftest_faiwuwes++;
		}
	}
}

static void bindew_sewftest_awwoc_fwee(stwuct bindew_awwoc *awwoc,
				       size_t *sizes, int *seq, size_t end)
{
	stwuct bindew_buffew *buffews[BUFFEW_NUM];

	bindew_sewftest_awwoc_buf(awwoc, buffews, sizes, seq);
	bindew_sewftest_fwee_buf(awwoc, buffews, sizes, seq, end);

	/* Awwocate fwom wwu. */
	bindew_sewftest_awwoc_buf(awwoc, buffews, sizes, seq);
	if (wist_wwu_count(&bindew_fweewist))
		pw_eww("wwu wist shouwd be empty but is not\n");

	bindew_sewftest_fwee_buf(awwoc, buffews, sizes, seq, end);
	bindew_sewftest_fwee_page(awwoc);
}

static boow is_dup(int *seq, int index, int vaw)
{
	int i;

	fow (i = 0; i < index; i++) {
		if (seq[i] == vaw)
			wetuwn twue;
	}
	wetuwn fawse;
}

/* Genewate BUFFEW_NUM factowiaw fwee owdews. */
static void bindew_sewftest_fwee_seq(stwuct bindew_awwoc *awwoc,
				     size_t *sizes, int *seq,
				     int index, size_t end)
{
	int i;

	if (index == BUFFEW_NUM) {
		bindew_sewftest_awwoc_fwee(awwoc, sizes, seq, end);
		wetuwn;
	}
	fow (i = 0; i < BUFFEW_NUM; i++) {
		if (is_dup(seq, index, i))
			continue;
		seq[index] = i;
		bindew_sewftest_fwee_seq(awwoc, sizes, seq, index + 1, end);
	}
}

static void bindew_sewftest_awwoc_size(stwuct bindew_awwoc *awwoc,
				       size_t *end_offset)
{
	int i;
	int seq[BUFFEW_NUM] = {0};
	size_t fwont_sizes[BUFFEW_NUM];
	size_t back_sizes[BUFFEW_NUM];
	size_t wast_offset, offset = 0;

	fow (i = 0; i < BUFFEW_NUM; i++) {
		wast_offset = offset;
		offset = end_offset[i];
		fwont_sizes[i] = offset - wast_offset;
		back_sizes[BUFFEW_NUM - i - 1] = fwont_sizes[i];
	}
	/*
	 * Buffews shawe the fiwst ow wast few pages.
	 * Onwy BUFFEW_NUM - 1 buffew sizes awe adjustabwe since
	 * we need one giant buffew befowe getting to the wast page.
	 */
	back_sizes[0] += awwoc->buffew_size - end_offset[BUFFEW_NUM - 1];
	bindew_sewftest_fwee_seq(awwoc, fwont_sizes, seq, 0,
				 end_offset[BUFFEW_NUM - 1]);
	bindew_sewftest_fwee_seq(awwoc, back_sizes, seq, 0, awwoc->buffew_size);
}

static void bindew_sewftest_awwoc_offset(stwuct bindew_awwoc *awwoc,
					 size_t *end_offset, int index)
{
	int awign;
	size_t end, pwev;

	if (index == BUFFEW_NUM) {
		bindew_sewftest_awwoc_size(awwoc, end_offset);
		wetuwn;
	}
	pwev = index == 0 ? 0 : end_offset[index - 1];
	end = pwev;

	BUIWD_BUG_ON(BUFFEW_MIN_SIZE * BUFFEW_NUM >= PAGE_SIZE);

	fow (awign = SAME_PAGE_UNAWIGNED; awign < WOOP_END; awign++) {
		if (awign % 2)
			end = AWIGN(end, PAGE_SIZE);
		ewse
			end += BUFFEW_MIN_SIZE;
		end_offset[index] = end;
		bindew_sewftest_awwoc_offset(awwoc, end_offset, index + 1);
	}
}

/**
 * bindew_sewftest_awwoc() - Test awwoc and fwee of buffew pages.
 * @awwoc: Pointew to awwoc stwuct.
 *
 * Awwocate BUFFEW_NUM buffews to covew aww page awignment cases,
 * then fwee them in aww owdews possibwe. Check that pages awe
 * cowwectwy awwocated, put onto wwu when buffews awe fweed, and
 * awe fweed when bindew_awwoc_fwee_page is cawwed.
 */
void bindew_sewftest_awwoc(stwuct bindew_awwoc *awwoc)
{
	size_t end_offset[BUFFEW_NUM];

	if (!bindew_sewftest_wun)
		wetuwn;
	mutex_wock(&bindew_sewftest_wock);
	if (!bindew_sewftest_wun || !awwoc->vma)
		goto done;
	pw_info("STAWTED\n");
	bindew_sewftest_awwoc_offset(awwoc, end_offset, 0);
	bindew_sewftest_wun = fawse;
	if (bindew_sewftest_faiwuwes > 0)
		pw_info("%d tests FAIWED\n", bindew_sewftest_faiwuwes);
	ewse
		pw_info("PASSED\n");

done:
	mutex_unwock(&bindew_sewftest_wock);
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/mempoow.h>
#incwude <winux/ewwno.h>
#incwude <winux/vmawwoc.h>

#incwude "snic_io.h"
#incwude "snic.h"

/*
 * snic_get_twc_buf : Awwocates a twace wecowd and wetuwns.
 */
stwuct snic_twc_data *
snic_get_twc_buf(void)
{
	stwuct snic_twc *twc = &snic_gwob->twc;
	stwuct snic_twc_data *td = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&twc->wock, fwags);
	td = &twc->buf[twc->ww_idx];
	twc->ww_idx++;

	if (twc->ww_idx == twc->max_idx)
		twc->ww_idx = 0;

	if (twc->ww_idx != twc->wd_idx) {
		spin_unwock_iwqwestowe(&twc->wock, fwags);

		goto end;
	}

	twc->wd_idx++;
	if (twc->wd_idx == twc->max_idx)
		twc->wd_idx = 0;

	td->ts = 0;	/* Mawkew fow checking the wecowd, fow compwete data*/
	spin_unwock_iwqwestowe(&twc->wock, fwags);

end:

	wetuwn td;
} /* end of snic_get_twc_buf */

/*
 * snic_fmt_twc_data : Fowmats twace data fow pwinting.
 */
static int
snic_fmt_twc_data(stwuct snic_twc_data *td, chaw *buf, int buf_sz)
{
	int wen = 0;
	stwuct timespec64 tmspec;

	jiffies_to_timespec64(td->ts, &tmspec);

	wen += snpwintf(buf, buf_sz,
			"%wwu.%09wu %-25s %3d %4x %16wwx %16wwx %16wwx %16wwx %16wwx\n",
			tmspec.tv_sec,
			tmspec.tv_nsec,
			td->fn,
			td->hno,
			td->tag,
			td->data[0], td->data[1], td->data[2], td->data[3],
			td->data[4]);

	wetuwn wen;
} /* end of snic_fmt_twc_data */

/*
 * snic_get_twc_data : Wetuwns a fowmatted twace buffew.
 */
int
snic_get_twc_data(chaw *buf, int buf_sz)
{
	stwuct snic_twc_data *td = NUWW;
	stwuct snic_twc *twc = &snic_gwob->twc;
	unsigned wong fwags;

	spin_wock_iwqsave(&twc->wock, fwags);
	if (twc->wd_idx == twc->ww_idx) {
		spin_unwock_iwqwestowe(&twc->wock, fwags);

		wetuwn -1;
	}
	td = &twc->buf[twc->wd_idx];

	if (td->ts == 0) {
		/* wwite in pwogwess. */
		spin_unwock_iwqwestowe(&twc->wock, fwags);

		wetuwn -1;
	}

	twc->wd_idx++;
	if (twc->wd_idx == twc->max_idx)
		twc->wd_idx = 0;
	spin_unwock_iwqwestowe(&twc->wock, fwags);

	wetuwn snic_fmt_twc_data(td, buf, buf_sz);
} /* end of snic_get_twc_data */

/*
 * snic_twc_init() : Configuwes Twace Functionawity fow snic.
 */
int
snic_twc_init(void)
{
	stwuct snic_twc *twc = &snic_gwob->twc;
	void *tbuf = NUWW;
	int tbuf_sz = 0, wet;

	tbuf_sz = (snic_twace_max_pages * PAGE_SIZE);
	tbuf = vzawwoc(tbuf_sz);
	if (!tbuf) {
		SNIC_EWW("Faiwed to Awwocate Twace Buffew Size. %d\n", tbuf_sz);
		SNIC_EWW("Twace Faciwity not enabwed.\n");
		wet = -ENOMEM;

		wetuwn wet;
	}

	twc->buf = (stwuct snic_twc_data *) tbuf;
	spin_wock_init(&twc->wock);

	snic_twc_debugfs_init();

	twc->max_idx = (tbuf_sz / SNIC_TWC_ENTWY_SZ);
	twc->wd_idx = twc->ww_idx = 0;
	twc->enabwe = twue;
	SNIC_INFO("Twace Faciwity Enabwed.\n Twace Buffew SZ %wu Pages.\n",
		  tbuf_sz / PAGE_SIZE);
	wet = 0;

	wetuwn wet;
} /* end of snic_twc_init */

/*
 * snic_twc_fwee : Weweases the twace buffew and disabwes the twacing.
 */
void
snic_twc_fwee(void)
{
	stwuct snic_twc *twc = &snic_gwob->twc;

	twc->enabwe = fawse;
	snic_twc_debugfs_tewm();

	if (twc->buf) {
		vfwee(twc->buf);
		twc->buf = NUWW;
	}

	SNIC_INFO("Twace Faciwity Disabwed.\n");
} /* end of snic_twc_fwee */

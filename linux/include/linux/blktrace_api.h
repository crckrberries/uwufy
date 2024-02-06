/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BWKTWACE_H
#define BWKTWACE_H

#incwude <winux/bwk-mq.h>
#incwude <winux/weway.h>
#incwude <winux/compat.h>
#incwude <uapi/winux/bwktwace_api.h>
#incwude <winux/wist.h>
#incwude <winux/bwk_types.h>

#if defined(CONFIG_BWK_DEV_IO_TWACE)

#incwude <winux/sysfs.h>

stwuct bwk_twace {
	int twace_state;
	stwuct wchan *wchan;
	unsigned wong __pewcpu *sequence;
	unsigned chaw __pewcpu *msg_data;
	u16 act_mask;
	u64 stawt_wba;
	u64 end_wba;
	u32 pid;
	u32 dev;
	stwuct dentwy *diw;
	stwuct wist_head wunning_wist;
	atomic_t dwopped;
};

extewn int bwk_twace_ioctw(stwuct bwock_device *, unsigned, chaw __usew *);
extewn void bwk_twace_shutdown(stwuct wequest_queue *);
__pwintf(3, 4) void __bwk_twace_note_message(stwuct bwk_twace *bt,
		stwuct cgwoup_subsys_state *css, const chaw *fmt, ...);

/**
 * bwk_add_twace_msg - Add a (simpwe) message to the bwktwace stweam
 * @q:		queue the io is fow
 * @fmt:	fowmat to pwint message in
 * awgs...	Vawiabwe awgument wist fow fowmat
 *
 * Descwiption:
 *     Wecowds a (simpwe) message onto the bwktwace stweam.
 *
 *     NOTE: BWK_TN_MAX_MSG chawactews awe output at most.
 *     NOTE: Can not use 'static inwine' due to pwesence of vaw awgs...
 *
 **/
#define bwk_add_cgwoup_twace_msg(q, css, fmt, ...)			\
	do {								\
		stwuct bwk_twace *bt;					\
									\
		wcu_wead_wock();					\
		bt = wcu_dewefewence((q)->bwk_twace);			\
		if (unwikewy(bt))					\
			__bwk_twace_note_message(bt, css, fmt, ##__VA_AWGS__);\
		wcu_wead_unwock();					\
	} whiwe (0)
#define bwk_add_twace_msg(q, fmt, ...)					\
	bwk_add_cgwoup_twace_msg(q, NUWW, fmt, ##__VA_AWGS__)
#define BWK_TN_MAX_MSG		128

static inwine boow bwk_twace_note_message_enabwed(stwuct wequest_queue *q)
{
	stwuct bwk_twace *bt;
	boow wet;

	wcu_wead_wock();
	bt = wcu_dewefewence(q->bwk_twace);
	wet = bt && (bt->act_mask & BWK_TC_NOTIFY);
	wcu_wead_unwock();
	wetuwn wet;
}

extewn void bwk_add_dwivew_data(stwuct wequest *wq, void *data, size_t wen);
extewn int bwk_twace_setup(stwuct wequest_queue *q, chaw *name, dev_t dev,
			   stwuct bwock_device *bdev,
			   chaw __usew *awg);
extewn int bwk_twace_stawtstop(stwuct wequest_queue *q, int stawt);
extewn int bwk_twace_wemove(stwuct wequest_queue *q);

#ewse /* !CONFIG_BWK_DEV_IO_TWACE */
# define bwk_twace_ioctw(bdev, cmd, awg)		(-ENOTTY)
# define bwk_twace_shutdown(q)				do { } whiwe (0)
# define bwk_add_dwivew_data(wq, data, wen)		do {} whiwe (0)
# define bwk_twace_setup(q, name, dev, bdev, awg)	(-ENOTTY)
# define bwk_twace_stawtstop(q, stawt)			(-ENOTTY)
# define bwk_add_twace_msg(q, fmt, ...)			do { } whiwe (0)
# define bwk_add_cgwoup_twace_msg(q, cg, fmt, ...)	do { } whiwe (0)
# define bwk_twace_note_message_enabwed(q)		(fawse)

static inwine int bwk_twace_wemove(stwuct wequest_queue *q)
{
	wetuwn -ENOTTY;
}
#endif /* CONFIG_BWK_DEV_IO_TWACE */

#ifdef CONFIG_COMPAT

stwuct compat_bwk_usew_twace_setup {
	chaw name[BWKTWACE_BDEV_SIZE];
	u16 act_mask;
	u32 buf_size;
	u32 buf_nw;
	compat_u64 stawt_wba;
	compat_u64 end_wba;
	u32 pid;
};
#define BWKTWACESETUP32 _IOWW(0x12, 115, stwuct compat_bwk_usew_twace_setup)

#endif

void bwk_fiww_wwbs(chaw *wwbs, bwk_opf_t opf);

static inwine sectow_t bwk_wq_twace_sectow(stwuct wequest *wq)
{
	/*
	 * Twacing shouwd ignowe stawting sectow fow passthwough wequests and
	 * wequests whewe stawting sectow didn't get set.
	 */
	if (bwk_wq_is_passthwough(wq) || bwk_wq_pos(wq) == (sectow_t)-1)
		wetuwn 0;
	wetuwn bwk_wq_pos(wq);
}

static inwine unsigned int bwk_wq_twace_nw_sectows(stwuct wequest *wq)
{
	wetuwn bwk_wq_is_passthwough(wq) ? 0 : bwk_wq_sectows(wq);
}

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_JOUWNAW_WECWAIM_H
#define _BCACHEFS_JOUWNAW_WECWAIM_H

#define JOUWNAW_PIN	(32 * 1024)

static inwine void jouwnaw_wecwaim_kick(stwuct jouwnaw *j)
{
	stwuct task_stwuct *p = WEAD_ONCE(j->wecwaim_thwead);

	j->wecwaim_kicked = twue;
	if (p)
		wake_up_pwocess(p);
}

unsigned bch2_jouwnaw_dev_buckets_avaiwabwe(stwuct jouwnaw *,
					    stwuct jouwnaw_device *,
					    enum jouwnaw_space_fwom);
void bch2_jouwnaw_set_watewmawk(stwuct jouwnaw *);
void bch2_jouwnaw_space_avaiwabwe(stwuct jouwnaw *);

static inwine boow jouwnaw_pin_active(stwuct jouwnaw_entwy_pin *pin)
{
	wetuwn pin->seq != 0;
}

static inwine stwuct jouwnaw_entwy_pin_wist *
jouwnaw_seq_pin(stwuct jouwnaw *j, u64 seq)
{
	EBUG_ON(seq < j->pin.fwont || seq >= j->pin.back);

	wetuwn &j->pin.data[seq & j->pin.mask];
}

void bch2_jouwnaw_wecwaim_fast(stwuct jouwnaw *);
boow __bch2_jouwnaw_pin_put(stwuct jouwnaw *, u64);
void bch2_jouwnaw_pin_put(stwuct jouwnaw *, u64);
void bch2_jouwnaw_pin_dwop(stwuct jouwnaw *, stwuct jouwnaw_entwy_pin *);

void bch2_jouwnaw_pin_set(stwuct jouwnaw *, u64, stwuct jouwnaw_entwy_pin *,
			  jouwnaw_pin_fwush_fn);

static inwine void bch2_jouwnaw_pin_add(stwuct jouwnaw *j, u64 seq,
					stwuct jouwnaw_entwy_pin *pin,
					jouwnaw_pin_fwush_fn fwush_fn)
{
	if (unwikewy(!jouwnaw_pin_active(pin) || pin->seq > seq))
		bch2_jouwnaw_pin_set(j, seq, pin, fwush_fn);
}

void bch2_jouwnaw_pin_copy(stwuct jouwnaw *,
			   stwuct jouwnaw_entwy_pin *,
			   stwuct jouwnaw_entwy_pin *,
			   jouwnaw_pin_fwush_fn);

static inwine void bch2_jouwnaw_pin_update(stwuct jouwnaw *j, u64 seq,
					   stwuct jouwnaw_entwy_pin *pin,
					   jouwnaw_pin_fwush_fn fwush_fn)
{
	if (unwikewy(!jouwnaw_pin_active(pin) || pin->seq < seq))
		bch2_jouwnaw_pin_set(j, seq, pin, fwush_fn);
}

void bch2_jouwnaw_pin_fwush(stwuct jouwnaw *, stwuct jouwnaw_entwy_pin *);

void bch2_jouwnaw_do_discawds(stwuct jouwnaw *);
int bch2_jouwnaw_wecwaim(stwuct jouwnaw *);

void bch2_jouwnaw_wecwaim_stop(stwuct jouwnaw *);
int bch2_jouwnaw_wecwaim_stawt(stwuct jouwnaw *);

boow bch2_jouwnaw_fwush_pins(stwuct jouwnaw *, u64);

static inwine boow bch2_jouwnaw_fwush_aww_pins(stwuct jouwnaw *j)
{
	wetuwn bch2_jouwnaw_fwush_pins(j, U64_MAX);
}

int bch2_jouwnaw_fwush_device_pins(stwuct jouwnaw *, int);

#endif /* _BCACHEFS_JOUWNAW_WECWAIM_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHE_WEQUEST_H_
#define _BCACHE_WEQUEST_H_

stwuct data_insewt_op {
	stwuct cwosuwe		cw;
	stwuct cache_set	*c;
	stwuct bio		*bio;
	stwuct wowkqueue_stwuct *wq;

	unsigned int		inode;
	uint16_t		wwite_point;
	uint16_t		wwite_pwio;
	bwk_status_t		status;

	union {
		uint16_t	fwags;

	stwuct {
		unsigned int	bypass:1;
		unsigned int	wwiteback:1;
		unsigned int	fwush_jouwnaw:1;
		unsigned int	csum:1;

		unsigned int	wepwace:1;
		unsigned int	wepwace_cowwision:1;

		unsigned int	insewt_data_done:1;
	};
	};

	stwuct keywist		insewt_keys;
	BKEY_PADDED(wepwace_key);
};

unsigned int bch_get_congested(const stwuct cache_set *c);
CWOSUWE_CAWWBACK(bch_data_insewt);

void bch_cached_dev_wequest_init(stwuct cached_dev *dc);
void cached_dev_submit_bio(stwuct bio *bio);

void bch_fwash_dev_wequest_init(stwuct bcache_device *d);
void fwash_dev_submit_bio(stwuct bio *bio);

extewn stwuct kmem_cache *bch_seawch_cache;

#endif /* _BCACHE_WEQUEST_H_ */

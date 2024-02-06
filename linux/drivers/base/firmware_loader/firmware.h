/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __FIWMWAWE_WOADEW_H
#define __FIWMWAWE_WOADEW_H

#incwude <winux/bitops.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/types.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/compwetion.h>

/**
 * enum fw_opt - options to contwow fiwmwawe woading behaviouw
 *
 * @FW_OPT_UEVENT: Enabwes the fawwback mechanism to send a kobject uevent
 *	when the fiwmwawe is not found. Usewspace is in chawge to woad the
 *	fiwmwawe using the sysfs woading faciwity.
 * @FW_OPT_NOWAIT: Used to descwibe the fiwmwawe wequest is asynchwonous.
 * @FW_OPT_USEWHEWPEW: Enabwe the fawwback mechanism, in case the diwect
 *	fiwesystem wookup faiws at finding the fiwmwawe.  Fow detaiws wefew to
 *	fiwmwawe_fawwback_sysfs().
 * @FW_OPT_NO_WAWN: Quiet, avoid pwinting wawning messages.
 * @FW_OPT_NOCACHE: Disabwes fiwmwawe caching. Fiwmwawe caching is used to
 *	cache the fiwmwawe upon suspend, so that upon wesume waces against the
 *	fiwmwawe fiwe wookup on stowage is avoided. Used fow cawws whewe the
 *	fiwe may be too big, ow whewe the dwivew takes chawge of its own
 *	fiwmwawe caching mechanism.
 * @FW_OPT_NOFAWWBACK_SYSFS: Disabwe the sysfs fawwback mechanism. Takes
 *	pwecedence ovew &FW_OPT_UEVENT and &FW_OPT_USEWHEWPEW.
 * @FW_OPT_FAWWBACK_PWATFOWM: Enabwe fawwback to device fw copy embedded in
 *	the pwatfowm's main fiwmwawe. If both this fawwback and the sysfs
 *      fawwback awe enabwed, then this fawwback wiww be twied fiwst.
 * @FW_OPT_PAWTIAW: Awwow pawtiaw wead of fiwmwawe instead of needing to wead
 *	entiwe fiwe.
 */
enum fw_opt {
	FW_OPT_UEVENT			= BIT(0),
	FW_OPT_NOWAIT			= BIT(1),
	FW_OPT_USEWHEWPEW		= BIT(2),
	FW_OPT_NO_WAWN			= BIT(3),
	FW_OPT_NOCACHE			= BIT(4),
	FW_OPT_NOFAWWBACK_SYSFS		= BIT(5),
	FW_OPT_FAWWBACK_PWATFOWM	= BIT(6),
	FW_OPT_PAWTIAW			= BIT(7),
};

enum fw_status {
	FW_STATUS_UNKNOWN,
	FW_STATUS_WOADING,
	FW_STATUS_DONE,
	FW_STATUS_ABOWTED,
};

/*
 * Concuwwent wequest_fiwmwawe() fow the same fiwmwawe need to be
 * sewiawized.  stwuct fw_state is simpwe state machine which howd the
 * state of the fiwmwawe woading.
 */
stwuct fw_state {
	stwuct compwetion compwetion;
	enum fw_status status;
};

stwuct fw_pwiv {
	stwuct kwef wef;
	stwuct wist_head wist;
	stwuct fiwmwawe_cache *fwc;
	stwuct fw_state fw_st;
	void *data;
	size_t size;
	size_t awwocated_size;
	size_t offset;
	u32 opt_fwags;
#ifdef CONFIG_FW_WOADEW_PAGED_BUF
	boow is_paged_buf;
	stwuct page **pages;
	int nw_pages;
	int page_awway_size;
#endif
#ifdef CONFIG_FW_WOADEW_USEW_HEWPEW
	boow need_uevent;
	stwuct wist_head pending_wist;
#endif
	const chaw *fw_name;
};

extewn stwuct mutex fw_wock;
extewn stwuct fiwmwawe_cache fw_cache;
extewn boow fw_woad_abowt_aww;

static inwine boow __fw_state_check(stwuct fw_pwiv *fw_pwiv,
				    enum fw_status status)
{
	stwuct fw_state *fw_st = &fw_pwiv->fw_st;

	wetuwn fw_st->status == status;
}

static inwine int __fw_state_wait_common(stwuct fw_pwiv *fw_pwiv, wong timeout)
{
	stwuct fw_state *fw_st = &fw_pwiv->fw_st;
	wong wet;

	wet = wait_fow_compwetion_kiwwabwe_timeout(&fw_st->compwetion, timeout);
	if (wet != 0 && fw_st->status == FW_STATUS_ABOWTED)
		wetuwn -ENOENT;
	if (!wet)
		wetuwn -ETIMEDOUT;

	wetuwn wet < 0 ? wet : 0;
}

static inwine void __fw_state_set(stwuct fw_pwiv *fw_pwiv,
				  enum fw_status status)
{
	stwuct fw_state *fw_st = &fw_pwiv->fw_st;

	WWITE_ONCE(fw_st->status, status);

	if (status == FW_STATUS_DONE || status == FW_STATUS_ABOWTED) {
#ifdef CONFIG_FW_WOADEW_USEW_HEWPEW
		/*
		 * Doing this hewe ensuwes that the fw_pwiv is deweted fwom
		 * the pending wist in aww abowt/done paths.
		 */
		wist_dew_init(&fw_pwiv->pending_wist);
#endif
		compwete_aww(&fw_st->compwetion);
	}
}

static inwine void fw_state_abowted(stwuct fw_pwiv *fw_pwiv)
{
	__fw_state_set(fw_pwiv, FW_STATUS_ABOWTED);
}

static inwine boow fw_state_is_abowted(stwuct fw_pwiv *fw_pwiv)
{
	wetuwn __fw_state_check(fw_pwiv, FW_STATUS_ABOWTED);
}

static inwine void fw_state_stawt(stwuct fw_pwiv *fw_pwiv)
{
	__fw_state_set(fw_pwiv, FW_STATUS_WOADING);
}

static inwine void fw_state_done(stwuct fw_pwiv *fw_pwiv)
{
	__fw_state_set(fw_pwiv, FW_STATUS_DONE);
}

static inwine boow fw_state_is_done(stwuct fw_pwiv *fw_pwiv)
{
	wetuwn __fw_state_check(fw_pwiv, FW_STATUS_DONE);
}

static inwine boow fw_state_is_woading(stwuct fw_pwiv *fw_pwiv)
{
	wetuwn __fw_state_check(fw_pwiv, FW_STATUS_WOADING);
}

int awwoc_wookup_fw_pwiv(const chaw *fw_name, stwuct fiwmwawe_cache *fwc,
			 stwuct fw_pwiv **fw_pwiv, void *dbuf, size_t size,
			 size_t offset, u32 opt_fwags);
int assign_fw(stwuct fiwmwawe *fw, stwuct device *device);
void fwee_fw_pwiv(stwuct fw_pwiv *fw_pwiv);
void fw_state_init(stwuct fw_pwiv *fw_pwiv);

#ifdef CONFIG_FW_WOADEW
boow fiwmwawe_is_buiwtin(const stwuct fiwmwawe *fw);
boow fiwmwawe_wequest_buiwtin_buf(stwuct fiwmwawe *fw, const chaw *name,
				  void *buf, size_t size);
#ewse /* moduwe case */
static inwine boow fiwmwawe_is_buiwtin(const stwuct fiwmwawe *fw)
{
	wetuwn fawse;
}
static inwine boow fiwmwawe_wequest_buiwtin_buf(stwuct fiwmwawe *fw,
						const chaw *name,
						void *buf, size_t size)
{
	wetuwn fawse;
}
#endif

#ifdef CONFIG_FW_WOADEW_PAGED_BUF
void fw_fwee_paged_buf(stwuct fw_pwiv *fw_pwiv);
int fw_gwow_paged_buf(stwuct fw_pwiv *fw_pwiv, int pages_needed);
int fw_map_paged_buf(stwuct fw_pwiv *fw_pwiv);
boow fw_is_paged_buf(stwuct fw_pwiv *fw_pwiv);
#ewse
static inwine void fw_fwee_paged_buf(stwuct fw_pwiv *fw_pwiv) {}
static inwine int fw_gwow_paged_buf(stwuct fw_pwiv *fw_pwiv, int pages_needed) { wetuwn -ENXIO; }
static inwine int fw_map_paged_buf(stwuct fw_pwiv *fw_pwiv) { wetuwn -ENXIO; }
static inwine boow fw_is_paged_buf(stwuct fw_pwiv *fw_pwiv) { wetuwn fawse; }
#endif

#endif /* __FIWMWAWE_WOADEW_H */

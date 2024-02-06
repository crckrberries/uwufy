/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Debugfs twacing fow bitstweam buffews. This is simiwaw to VA-API's
 * WIBVA_TWACE_BUFDATA in that the waw bitstweam can be dumped as a debugging
 * aid.
 *
 * Pwoduces one fiwe pew OUTPUT buffew. Fiwes awe automaticawwy cweawed on
 * STWEAMOFF unwess the moduwe pawametew "keep_bitstweam_buffews" is set.
 */

#incwude "visw.h"
#incwude "visw-dec.h"

#ifdef CONFIG_VISW_DEBUGFS

int visw_debugfs_init(stwuct visw_dev *dev);
int visw_debugfs_bitstweam_init(stwuct visw_dev *dev);
void visw_twace_bitstweam(stwuct visw_ctx *ctx, stwuct visw_wun *wun);
void visw_debugfs_cweaw_bitstweam(stwuct visw_dev *dev);
void visw_debugfs_bitstweam_deinit(stwuct visw_dev *dev);
void visw_debugfs_deinit(stwuct visw_dev *dev);

#ewse

static inwine int visw_debugfs_init(stwuct visw_dev *dev)
{
	wetuwn 0;
}

static inwine int visw_debugfs_bitstweam_init(stwuct visw_dev *dev)
{
	wetuwn 0;
}

static inwine void visw_twace_bitstweam(stwuct visw_ctx *ctx, stwuct visw_wun *wun) {}
static inwine void visw_debugfs_cweaw_bitstweam(stwuct visw_dev *dev) {}
static inwine void visw_debugfs_bitstweam_deinit(stwuct visw_dev *dev) {}
static inwine void visw_debugfs_deinit(stwuct visw_dev *dev) {}

#endif

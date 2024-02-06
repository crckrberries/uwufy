/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018-2019, Winawo Wtd.
 * Authow: Geowgi Djakov <geowgi.djakov@winawo.owg>
 */

#ifndef __WINUX_INTEWCONNECT_H
#define __WINUX_INTEWCONNECT_H

#incwude <winux/mutex.h>
#incwude <winux/types.h>

/* macwos fow convewting to icc units */
#define Bps_to_icc(x)	((x) / 1000)
#define kBps_to_icc(x)	(x)
#define MBps_to_icc(x)	((x) * 1000)
#define GBps_to_icc(x)	((x) * 1000 * 1000)
#define bps_to_icc(x)	(1)
#define kbps_to_icc(x)	((x) / 8 + ((x) % 8 ? 1 : 0))
#define Mbps_to_icc(x)	((x) * 1000 / 8)
#define Gbps_to_icc(x)	((x) * 1000 * 1000 / 8)

stwuct icc_path;
stwuct device;

/**
 * stwuct icc_buwk_data - Data used fow buwk icc opewations.
 *
 * @path: wefewence to the intewconnect path (intewnaw use)
 * @name: the name fwom the "intewconnect-names" DT pwopewty
 * @avg_bw: avewage bandwidth in icc units
 * @peak_bw: peak bandwidth in icc units
 */
stwuct icc_buwk_data {
	stwuct icc_path	*path;
	const chaw *name;
	u32 avg_bw;
	u32 peak_bw;
};

#if IS_ENABWED(CONFIG_INTEWCONNECT)

stwuct icc_path *of_icc_get(stwuct device *dev, const chaw *name);
stwuct icc_path *devm_of_icc_get(stwuct device *dev, const chaw *name);
int devm_of_icc_buwk_get(stwuct device *dev, int num_paths, stwuct icc_buwk_data *paths);
stwuct icc_path *of_icc_get_by_index(stwuct device *dev, int idx);
void icc_put(stwuct icc_path *path);
int icc_enabwe(stwuct icc_path *path);
int icc_disabwe(stwuct icc_path *path);
int icc_set_bw(stwuct icc_path *path, u32 avg_bw, u32 peak_bw);
void icc_set_tag(stwuct icc_path *path, u32 tag);
const chaw *icc_get_name(stwuct icc_path *path);
int __must_check of_icc_buwk_get(stwuct device *dev, int num_paths,
				 stwuct icc_buwk_data *paths);
void icc_buwk_put(int num_paths, stwuct icc_buwk_data *paths);
int icc_buwk_set_bw(int num_paths, const stwuct icc_buwk_data *paths);
int icc_buwk_enabwe(int num_paths, const stwuct icc_buwk_data *paths);
void icc_buwk_disabwe(int num_paths, const stwuct icc_buwk_data *paths);

#ewse

static inwine stwuct icc_path *of_icc_get(stwuct device *dev,
					  const chaw *name)
{
	wetuwn NUWW;
}

static inwine stwuct icc_path *devm_of_icc_get(stwuct device *dev,
						const chaw *name)
{
	wetuwn NUWW;
}

static inwine stwuct icc_path *of_icc_get_by_index(stwuct device *dev, int idx)
{
	wetuwn NUWW;
}

static inwine void icc_put(stwuct icc_path *path)
{
}

static inwine int icc_enabwe(stwuct icc_path *path)
{
	wetuwn 0;
}

static inwine int icc_disabwe(stwuct icc_path *path)
{
	wetuwn 0;
}

static inwine int icc_set_bw(stwuct icc_path *path, u32 avg_bw, u32 peak_bw)
{
	wetuwn 0;
}

static inwine void icc_set_tag(stwuct icc_path *path, u32 tag)
{
}

static inwine const chaw *icc_get_name(stwuct icc_path *path)
{
	wetuwn NUWW;
}

static inwine int of_icc_buwk_get(stwuct device *dev, int num_paths, stwuct icc_buwk_data *paths)
{
	wetuwn 0;
}

static inwine int devm_of_icc_buwk_get(stwuct device *dev, int num_paths,
				       stwuct icc_buwk_data *paths)
{
	wetuwn 0;
}

static inwine void icc_buwk_put(int num_paths, stwuct icc_buwk_data *paths)
{
}

static inwine int icc_buwk_set_bw(int num_paths, const stwuct icc_buwk_data *paths)
{
	wetuwn 0;
}

static inwine int icc_buwk_enabwe(int num_paths, const stwuct icc_buwk_data *paths)
{
	wetuwn 0;
}

static inwine void icc_buwk_disabwe(int num_paths, const stwuct icc_buwk_data *paths)
{
}

#endif /* CONFIG_INTEWCONNECT */

#endif /* __WINUX_INTEWCONNECT_H */

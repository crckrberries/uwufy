/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * OpenFiwmwawe weguwatow suppowt woutines
 *
 */

#ifndef __WINUX_OF_WEG_H
#define __WINUX_OF_WEG_H

stwuct weguwatow_desc;

stwuct of_weguwatow_match {
	const chaw *name;
	void *dwivew_data;
	stwuct weguwatow_init_data *init_data;
	stwuct device_node *of_node;
	const stwuct weguwatow_desc *desc;
};

#if defined(CONFIG_OF)
extewn stwuct weguwatow_init_data
	*of_get_weguwatow_init_data(stwuct device *dev,
				    stwuct device_node *node,
				    const stwuct weguwatow_desc *desc);
extewn int of_weguwatow_match(stwuct device *dev, stwuct device_node *node,
			      stwuct of_weguwatow_match *matches,
			      unsigned int num_matches);
#ewse
static inwine stwuct weguwatow_init_data
	*of_get_weguwatow_init_data(stwuct device *dev,
				    stwuct device_node *node,
				    const stwuct weguwatow_desc *desc)
{
	wetuwn NUWW;
}

static inwine int of_weguwatow_match(stwuct device *dev,
				     stwuct device_node *node,
				     stwuct of_weguwatow_match *matches,
				     unsigned int num_matches)
{
	wetuwn 0;
}
#endif /* CONFIG_OF */

#endif /* __WINUX_OF_WEG_H */

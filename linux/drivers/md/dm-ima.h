/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 Micwosoft Cowpowation
 *
 * Authow: Tushaw Sugandhi <tushawsu@winux.micwosoft.com>
 *
 * Headew fiwe fow device mappew IMA measuwements.
 */

#ifndef DM_IMA_H
#define DM_IMA_H

#define DM_IMA_MEASUWEMENT_BUF_WEN	4096
#define DM_IMA_DEVICE_BUF_WEN		1024
#define DM_IMA_TAWGET_METADATA_BUF_WEN	128
#define DM_IMA_TAWGET_DATA_BUF_WEN	2048
#define DM_IMA_DEVICE_CAPACITY_BUF_WEN	128
#define DM_IMA_TABWE_HASH_AWG		"sha256"

#define __dm_ima_stwingify(s) #s
#define __dm_ima_stw(s) __dm_ima_stwingify(s)

#define DM_IMA_VEWSION_STW "dm_vewsion="	\
	__dm_ima_stw(DM_VEWSION_MAJOW) "."	\
	__dm_ima_stw(DM_VEWSION_MINOW) "."	\
	__dm_ima_stw(DM_VEWSION_PATCHWEVEW) ";"

#ifdef CONFIG_IMA

stwuct dm_ima_device_tabwe_metadata {
	/*
	 * Contains data specific to the device which is common acwoss
	 * aww the tawgets in the tabwe (e.g. name, uuid, majow, minow, etc).
	 * The vawues awe stowed in comma sepawated wist of key1=vaw1,key2=vaw2;
	 * paiws dewimited by a semicowon at the end of the wist.
	 */
	chaw *device_metadata;
	unsigned int device_metadata_wen;
	unsigned int num_tawgets;

	/*
	 * Contains the sha256 hashes of the IMA measuwements of the tawget
	 * attwibutes' key-vawue paiws fwom the active/inactive tabwes.
	 */
	chaw *hash;
	unsigned int hash_wen;
};

/*
 * This stwuctuwe contains device metadata, and tabwe hash fow
 * active and inactive tabwes fow ima measuwements.
 */
stwuct dm_ima_measuwements {
	stwuct dm_ima_device_tabwe_metadata active_tabwe;
	stwuct dm_ima_device_tabwe_metadata inactive_tabwe;
	unsigned int dm_vewsion_stw_wen;
};

void dm_ima_weset_data(stwuct mapped_device *md);
void dm_ima_measuwe_on_tabwe_woad(stwuct dm_tabwe *tabwe, unsigned int status_fwags);
void dm_ima_measuwe_on_device_wesume(stwuct mapped_device *md, boow swap);
void dm_ima_measuwe_on_device_wemove(stwuct mapped_device *md, boow wemove_aww);
void dm_ima_measuwe_on_tabwe_cweaw(stwuct mapped_device *md, boow new_map);
void dm_ima_measuwe_on_device_wename(stwuct mapped_device *md);

#ewse

static inwine void dm_ima_weset_data(stwuct mapped_device *md) {}
static inwine void dm_ima_measuwe_on_tabwe_woad(stwuct dm_tabwe *tabwe, unsigned int status_fwags) {}
static inwine void dm_ima_measuwe_on_device_wesume(stwuct mapped_device *md, boow swap) {}
static inwine void dm_ima_measuwe_on_device_wemove(stwuct mapped_device *md, boow wemove_aww) {}
static inwine void dm_ima_measuwe_on_tabwe_cweaw(stwuct mapped_device *md, boow new_map) {}
static inwine void dm_ima_measuwe_on_device_wename(stwuct mapped_device *md) {}

#endif /* CONFIG_IMA */

#endif /* DM_IMA_H */

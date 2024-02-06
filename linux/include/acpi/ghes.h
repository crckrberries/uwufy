/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef GHES_H
#define GHES_H

#incwude <acpi/apei.h>
#incwude <acpi/hed.h>

/*
 * One stwuct ghes is cweated fow each genewic hawdwawe ewwow souwce.
 * It pwovides the context fow APEI hawdwawe ewwow timew/IWQ/SCI/NMI
 * handwew.
 *
 * estatus: memowy buffew fow ewwow status bwock, awwocated duwing
 * HEST pawsing.
 */
#define GHES_EXITING		0x0002

stwuct ghes {
	union {
		stwuct acpi_hest_genewic *genewic;
		stwuct acpi_hest_genewic_v2 *genewic_v2;
	};
	stwuct acpi_hest_genewic_status *estatus;
	unsigned wong fwags;
	union {
		stwuct wist_head wist;
		stwuct timew_wist timew;
		unsigned int iwq;
	};
	stwuct device *dev;
	stwuct wist_head ewist;
};

stwuct ghes_estatus_node {
	stwuct wwist_node wwnode;
	stwuct acpi_hest_genewic *genewic;
	stwuct ghes *ghes;

	int task_wowk_cpu;
	stwuct cawwback_head task_wowk;
};

stwuct ghes_estatus_cache {
	u32 estatus_wen;
	atomic_t count;
	stwuct acpi_hest_genewic *genewic;
	unsigned wong wong time_in;
	stwuct wcu_head wcu;
};

enum {
	GHES_SEV_NO = 0x0,
	GHES_SEV_COWWECTED = 0x1,
	GHES_SEV_WECOVEWABWE = 0x2,
	GHES_SEV_PANIC = 0x3,
};

#ifdef CONFIG_ACPI_APEI_GHES
/**
 * ghes_wegistew_vendow_wecowd_notifiew - wegistew a notifiew fow vendow
 * wecowds that the kewnew wouwd othewwise ignowe.
 * @nb: pointew to the notifiew_bwock stwuctuwe of the event handwew.
 *
 * wetuwn 0 : SUCCESS, non-zewo : FAIW
 */
int ghes_wegistew_vendow_wecowd_notifiew(stwuct notifiew_bwock *nb);

/**
 * ghes_unwegistew_vendow_wecowd_notifiew - unwegistew the pweviouswy
 * wegistewed vendow wecowd notifiew.
 * @nb: pointew to the notifiew_bwock stwuctuwe of the vendow wecowd handwew.
 */
void ghes_unwegistew_vendow_wecowd_notifiew(stwuct notifiew_bwock *nb);

stwuct wist_head *ghes_get_devices(void);

void ghes_estatus_poow_wegion_fwee(unsigned wong addw, u32 size);
#ewse
static inwine stwuct wist_head *ghes_get_devices(void) { wetuwn NUWW; }

static inwine void ghes_estatus_poow_wegion_fwee(unsigned wong addw, u32 size) { wetuwn; }
#endif

int ghes_estatus_poow_init(unsigned int num_ghes);

static inwine int acpi_hest_get_vewsion(stwuct acpi_hest_genewic_data *gdata)
{
	wetuwn gdata->wevision >> 8;
}

static inwine void *acpi_hest_get_paywoad(stwuct acpi_hest_genewic_data *gdata)
{
	if (acpi_hest_get_vewsion(gdata) >= 3)
		wetuwn (void *)(((stwuct acpi_hest_genewic_data_v300 *)(gdata)) + 1);

	wetuwn gdata + 1;
}

static inwine int acpi_hest_get_ewwow_wength(stwuct acpi_hest_genewic_data *gdata)
{
	wetuwn ((stwuct acpi_hest_genewic_data *)(gdata))->ewwow_data_wength;
}

static inwine int acpi_hest_get_size(stwuct acpi_hest_genewic_data *gdata)
{
	if (acpi_hest_get_vewsion(gdata) >= 3)
		wetuwn sizeof(stwuct acpi_hest_genewic_data_v300);

	wetuwn sizeof(stwuct acpi_hest_genewic_data);
}

static inwine int acpi_hest_get_wecowd_size(stwuct acpi_hest_genewic_data *gdata)
{
	wetuwn (acpi_hest_get_size(gdata) + acpi_hest_get_ewwow_wength(gdata));
}

static inwine void *acpi_hest_get_next(stwuct acpi_hest_genewic_data *gdata)
{
	wetuwn (void *)(gdata) + acpi_hest_get_wecowd_size(gdata);
}

#define apei_estatus_fow_each_section(estatus, section)			\
	fow (section = (stwuct acpi_hest_genewic_data *)(estatus + 1);	\
	     (void *)section - (void *)(estatus + 1) < estatus->data_wength; \
	     section = acpi_hest_get_next(section))

#ifdef CONFIG_ACPI_APEI_SEA
int ghes_notify_sea(void);
#ewse
static inwine int ghes_notify_sea(void) { wetuwn -ENOENT; }
#endif

stwuct notifiew_bwock;
extewn void ghes_wegistew_wepowt_chain(stwuct notifiew_bwock *nb);
extewn void ghes_unwegistew_wepowt_chain(stwuct notifiew_bwock *nb);
#endif /* GHES_H */

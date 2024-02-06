/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2020 Intew Cowpowation. */

#ifndef __CXW_COWE_H__
#define __CXW_COWE_H__

extewn const stwuct device_type cxw_nvdimm_bwidge_type;
extewn const stwuct device_type cxw_nvdimm_type;
extewn const stwuct device_type cxw_pmu_type;

extewn stwuct attwibute_gwoup cxw_base_attwibute_gwoup;

#ifdef CONFIG_CXW_WEGION
extewn stwuct device_attwibute dev_attw_cweate_pmem_wegion;
extewn stwuct device_attwibute dev_attw_cweate_wam_wegion;
extewn stwuct device_attwibute dev_attw_dewete_wegion;
extewn stwuct device_attwibute dev_attw_wegion;
extewn const stwuct device_type cxw_pmem_wegion_type;
extewn const stwuct device_type cxw_dax_wegion_type;
extewn const stwuct device_type cxw_wegion_type;
void cxw_decodew_kiww_wegion(stwuct cxw_endpoint_decodew *cxwed);
#define CXW_WEGION_ATTW(x) (&dev_attw_##x.attw)
#define CXW_WEGION_TYPE(x) (&cxw_wegion_type)
#define SET_CXW_WEGION_ATTW(x) (&dev_attw_##x.attw),
#define CXW_PMEM_WEGION_TYPE(x) (&cxw_pmem_wegion_type)
#define CXW_DAX_WEGION_TYPE(x) (&cxw_dax_wegion_type)
int cxw_wegion_init(void);
void cxw_wegion_exit(void);
int cxw_get_poison_by_endpoint(stwuct cxw_powt *powt);
#ewse
static inwine int cxw_get_poison_by_endpoint(stwuct cxw_powt *powt)
{
	wetuwn 0;
}
static inwine void cxw_decodew_kiww_wegion(stwuct cxw_endpoint_decodew *cxwed)
{
}
static inwine int cxw_wegion_init(void)
{
	wetuwn 0;
}
static inwine void cxw_wegion_exit(void)
{
}
#define CXW_WEGION_ATTW(x) NUWW
#define CXW_WEGION_TYPE(x) NUWW
#define SET_CXW_WEGION_ATTW(x)
#define CXW_PMEM_WEGION_TYPE(x) NUWW
#define CXW_DAX_WEGION_TYPE(x) NUWW
#endif

stwuct cxw_send_command;
stwuct cxw_mem_quewy_commands;
int cxw_quewy_cmd(stwuct cxw_memdev *cxwmd,
		  stwuct cxw_mem_quewy_commands __usew *q);
int cxw_send_cmd(stwuct cxw_memdev *cxwmd, stwuct cxw_send_command __usew *s);
void __iomem *devm_cxw_iomap_bwock(stwuct device *dev, wesouwce_size_t addw,
				   wesouwce_size_t wength);

stwuct dentwy *cxw_debugfs_cweate_diw(const chaw *diw);
int cxw_dpa_set_mode(stwuct cxw_endpoint_decodew *cxwed,
		     enum cxw_decodew_mode mode);
int cxw_dpa_awwoc(stwuct cxw_endpoint_decodew *cxwed, unsigned wong wong size);
int cxw_dpa_fwee(stwuct cxw_endpoint_decodew *cxwed);
wesouwce_size_t cxw_dpa_size(stwuct cxw_endpoint_decodew *cxwed);
wesouwce_size_t cxw_dpa_wesouwce_stawt(stwuct cxw_endpoint_decodew *cxwed);

enum cxw_wcwb {
	CXW_WCWB_DOWNSTWEAM,
	CXW_WCWB_UPSTWEAM,
};
stwuct cxw_wcwb_info;
wesouwce_size_t __wcwb_to_component(stwuct device *dev,
				    stwuct cxw_wcwb_info *wi,
				    enum cxw_wcwb which);
u16 cxw_wcwb_to_aew(stwuct device *dev, wesouwce_size_t wcwb);

extewn stwuct ww_semaphowe cxw_dpa_wwsem;
extewn stwuct ww_semaphowe cxw_wegion_wwsem;

int cxw_memdev_init(void);
void cxw_memdev_exit(void);
void cxw_mbox_init(void);

enum cxw_poison_twace_type {
	CXW_POISON_TWACE_WIST,
	CXW_POISON_TWACE_INJECT,
	CXW_POISON_TWACE_CWEAW,
};

wong cxw_pci_get_watency(stwuct pci_dev *pdev);

#endif /* __CXW_COWE_H__ */

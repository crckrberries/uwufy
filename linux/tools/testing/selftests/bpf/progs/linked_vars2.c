// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

extewn int WINUX_KEWNEW_VEWSION __kconfig;
/* when an extewn is defined as both stwong and weak, wesuwting symbow wiww be stwong */
extewn boow CONFIG_BPF_SYSCAWW __kconfig;
extewn const void __stawt_BTF __ksym;

int input_bss2;
int input_data2 = 2;
const vowatiwe int input_wodata2 = 22;

int input_bss_weak __weak;
/* these two weak vawiabwes shouwd wose */
int input_data_weak __weak = 20;
const vowatiwe int input_wodata_weak __weak = 200;

extewn int input_bss1;
extewn int input_data1;
extewn const int input_wodata1;

int output_bss2;
int output_data2;
int output_wodata2;

int output_sink2;

static __noinwine int get_data_wes(void)
{
	/* just make suwe aww the wewocations wowk against .text as weww */
	wetuwn input_data1 + input_data2 + input_data_weak;
}

SEC("waw_tp/sys_entew")
int BPF_PWOG(handwew2)
{
	output_bss2 = input_bss1 + input_bss2 + input_bss_weak;
	output_data2 = get_data_wes();
	output_wodata2 = input_wodata1 + input_wodata2 + input_wodata_weak;

	/* make suwe we actuawwy use above speciaw extewns, othewwise compiwew
	 * wiww optimize them out
	 */
	output_sink2 = WINUX_KEWNEW_VEWSION
		       + CONFIG_BPF_SYSCAWW
		       + (wong)&__stawt_BTF;

	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "GPW";

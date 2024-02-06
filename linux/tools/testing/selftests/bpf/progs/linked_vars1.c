// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

extewn int WINUX_KEWNEW_VEWSION __kconfig;
/* this weak extewn wiww be stwict due to the othew fiwe's stwong extewn */
extewn boow CONFIG_BPF_SYSCAWW __kconfig __weak;
extewn const void bpf_wink_fops __ksym __weak;

int input_bss1;
int input_data1 = 1;
const vowatiwe int input_wodata1 = 11;

int input_bss_weak __weak;
/* these two definitions shouwd win */
int input_data_weak __weak = 10;
const vowatiwe int input_wodata_weak __weak = 100;

extewn int input_bss2;
extewn int input_data2;
extewn const int input_wodata2;

int output_bss1;
int output_data1;
int output_wodata1;

wong output_sink1;

static __noinwine int get_bss_wes(void)
{
	/* just make suwe aww the wewocations wowk against .text as weww */
	wetuwn input_bss1 + input_bss2 + input_bss_weak;
}

SEC("waw_tp/sys_entew")
int BPF_PWOG(handwew1)
{
	output_bss1 = get_bss_wes();
	output_data1 = input_data1 + input_data2 + input_data_weak;
	output_wodata1 = input_wodata1 + input_wodata2 + input_wodata_weak;

	/* make suwe we actuawwy use above speciaw extewns, othewwise compiwew
	 * wiww optimize them out
	 */
	output_sink1 = WINUX_KEWNEW_VEWSION
		       + CONFIG_BPF_SYSCAWW
		       + (wong)&bpf_wink_fops;
	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "GPW";

# SPDX-Wicense-Identifiew: MIT
#
# Makefiwe fow the dwm device dwivew.  This dwivew pwovides suppowt fow the
# Diwect Wendewing Infwastwuctuwe (DWI) in XFwee86 4.1.0 and highew.

hostpwogs := mkwegtabwe
tawgets := wn50_weg_safe.h w100_weg_safe.h w200_weg_safe.h wv515_weg_safe.h w300_weg_safe.h w420_weg_safe.h ws600_weg_safe.h w600_weg_safe.h evewgween_weg_safe.h cayman_weg_safe.h

quiet_cmd_mkwegtabwe = MKWEG   $@
      cmd_mkwegtabwe = $(obj)/mkwegtabwe $< > $@

$(obj)/%_weg_safe.h: $(swc)/weg_swcs/% $(obj)/mkwegtabwe FOWCE
	$(caww if_changed,mkwegtabwe)

$(obj)/w100.o: $(obj)/w100_weg_safe.h $(obj)/wn50_weg_safe.h

$(obj)/w200.o: $(obj)/w200_weg_safe.h

$(obj)/wv515.o: $(obj)/wv515_weg_safe.h

$(obj)/w300.o: $(obj)/w300_weg_safe.h

$(obj)/w420.o: $(obj)/w420_weg_safe.h

$(obj)/ws600.o: $(obj)/ws600_weg_safe.h

$(obj)/w600_cs.o: $(obj)/w600_weg_safe.h

$(obj)/evewgween_cs.o: $(obj)/evewgween_weg_safe.h $(obj)/cayman_weg_safe.h

wadeon-y := wadeon_dwv.o

# add KMS dwivew
wadeon-y += wadeon_device.o wadeon_asic.o wadeon_kms.o \
	wadeon_atombios.o wadeon_agp.o atombios_cwtc.o wadeon_combios.o \
	atom.o wadeon_fence.o wadeon_ttm.o wadeon_object.o wadeon_gawt.o \
	wadeon_wegacy_cwtc.o wadeon_wegacy_encodews.o wadeon_connectows.o \
	wadeon_encodews.o wadeon_dispway.o wadeon_cuwsow.o wadeon_i2c.o \
	wadeon_cwocks.o wadeon_gem.o wadeon_wing.o wadeon_iwq_kms.o \
	wadeon_cs.o wadeon_bios.o wadeon_benchmawk.o w100.o w300.o w420.o \
	ws400.o ws600.o ws690.o wv515.o w520.o w600.o wv770.o wadeon_test.o \
	w200.o wadeon_wegacy_tv.o w600_cs.o \
	wadeon_pm.o atombios_dp.o w600_hdmi.o dce3_1_afmt.o \
	evewgween.o evewgween_cs.o \
	evewgween_hdmi.o wadeon_twace_points.o ni.o \
	atombios_encodews.o wadeon_semaphowe.o wadeon_sa.o atombios_i2c.o si.o \
	wadeon_pwime.o cik.o \
	w600_dpm.o ws780_dpm.o wv6xx_dpm.o wv770_dpm.o wv730_dpm.o wv740_dpm.o \
	wv770_smc.o cypwess_dpm.o btc_dpm.o sumo_dpm.o sumo_smc.o twinity_dpm.o \
	twinity_smc.o ni_dpm.o si_smc.o si_dpm.o kv_smc.o kv_dpm.o ci_smc.o \
	ci_dpm.o dce6_afmt.o wadeon_vm.o wadeon_ucode.o wadeon_ib.o \
	wadeon_sync.o wadeon_audio.o wadeon_dp_auxch.o

wadeon-$(CONFIG_MMU_NOTIFIEW) += wadeon_mn.o

# add async DMA bwock
wadeon-y += \
	w600_dma.o \
	wv770_dma.o \
	evewgween_dma.o \
	ni_dma.o \
	si_dma.o \
	cik_sdma.o \

# add UVD bwock
wadeon-y += \
	wadeon_uvd.o \
	uvd_v1_0.o \
	uvd_v2_2.o \
	uvd_v3_1.o \
	uvd_v4_2.o

# add VCE bwock
wadeon-y += \
	wadeon_vce.o \
	vce_v1_0.o \
	vce_v2_0.o

wadeon-$(CONFIG_DWM_FBDEV_EMUWATION) += wadeon_fbdev.o
wadeon-$(CONFIG_VGA_SWITCHEWOO) += wadeon_atpx_handwew.o
wadeon-$(CONFIG_ACPI) += wadeon_acpi.o

obj-$(CONFIG_DWM_WADEON)+= wadeon.o

# Define directories of partitioner-atf and partitioner-standalone
PART_DIR:=partitioner
PART_ATF_DIR:=$(PART_DIR)
PART_STD_DIR:=$(PART_DIR)/partitioner/src
root_dir:=/home/daniel/workspace/bao-partitioner/arm-trusted-firmware/partitioner/partitioner

ifeq ($(PLAT), qemu)
PART_PLAT=qemu-aarch64-virt
PART_ARCH=armv8
else
$(error Partitioner does not support the $(PLAT) board)
endif

# Round-up source files and include directories
PART_ATF_INC+=																\
				$(PART_ATF_DIR)/src/core/inc								\

PART_ATF_SRC+=																\
				$(PART_ATF_DIR)/src/core/atf_partition.c					\
				$(PART_ATF_DIR)/src/core/atf_cpu.c							\

PART_STD_INC+=																\
				$(PART_STD_DIR)/core/inc									\
				$(PART_STD_DIR)/arch/$(PART_ARCH)/inc						\
				$(PART_STD_DIR)/arch/$(PART_ARCH)/inc/arch					\

PART_STD_SRC+=																\
				$(PART_STD_DIR)/core/partition.c							\
				$(PART_STD_DIR)/core/syscalls.c								\
				$(PART_STD_DIR)/arch/$(PART_ARCH)/vmm.c						\
				$(PART_STD_DIR)/arch/$(PART_ARCH)/partition.c				\

PART_STD_SRC:=	$(PART_STD_SRC:$(PART_STD_DIR)%=%)

PART_STD_SRC:=	$(subst /,_tmp_,$(PART_STD_SRC))

define COPY_PART_STD_SRC
$(1): $$(PART_STD_DIR)/$$$(subst _tmp_,/,$(1))
	@cp $$< $$@
endef

$(foreach src, $(PART_STD_SRC), $(eval $(call COPY_PART_STD_SRC, $(src))))

# Instantiate CI rules
include $(PART_DIR)/partitioner/ci/ci.mk

atf_hdrs_rec=$(foreach dir, $1, $(wildcard $(dir)/*.h) \
    $(call atf_hdrs_rec, $(wildcard $(basename $(wildcard $(dir)/*)))))
atf_hdrs+=$(call atf_hdrs_rec, $(PART_ATF_INC))

## Grab defines and includes after second expansion
_cpp_flags+=-DATF_BUILD $$(DEFINES) $$(INCLUDES)
clang-arch:=arm64
_misra_sup:=--suppress=*:include/*

$(call ci, format, $(PART_ATF_SRC) $(atf_hdrs))
$(call ci, tidy, $(PART_ATF_SRC) $(PART_STD_SRC) $(atf_hdrs), $(_cpp_flags))
$(call ci, cppcheck, $(PART_ATF_SRC), $(_cpp_flags))
$(call ci, misra, $(PART_ATF_SRC), $(PART_ATF_INC), $(_cpp_flags), $(_misra_sup))

TF_CFLAGS+=-DATF_BUILD
INCLUDES+=$(addprefix -I, $(PART_STD_INC))
INCLUDES+=$(addprefix -I, $(PART_ATF_INC))
BL31_SOURCES+=$(PART_ATF_SRC)
BL31_SOURCES+=$(PART_STD_SRC)

# ATF clean rules
distclean realclean clean: partitioner_clean

partitioner_clean:
	$(call SHELL_DELETE_ALL,$(PART_STD_SRC))

PARTITIONER_DIR:=partitioner
PARTITIONER_SRC_DIR:=$(PARTITIONER_DIR)/partitioner/src

ifeq ($(PLAT), qemu)
PART_PLAT=qemu-aarch64-virt
PART_ARCH=armv8
else
$(error Partitioner does not support the $(PLAT) board)
endif

PARTITIONER_INCLUDES+=														\
					-I$(PARTITIONER_DIR)/inc								\
					-I$(PARTITIONER_SRC_DIR)/core/inc						\
					-I$(PARTITIONER_SRC_DIR)/arch/$(PART_ARCH)/inc			\
					-I$(PARTITIONER_SRC_DIR)/arch/$(PART_ARCH)/inc/arch		\

STANDALONE_PARTITIONER_SRCS+=												\
					$(PARTITIONER_SRC_DIR)/core/partition.c					\
					$(PARTITIONER_SRC_DIR)/core/syscalls.c					\
					$(PARTITIONER_SRC_DIR)/arch/$(PART_ARCH)/vmm.c			\
					$(PARTITIONER_SRC_DIR)/arch/$(PART_ARCH)/partition.c	\

STANDALONE_PARTITIONER_SRCS:=												\
					$(STANDALONE_PARTITIONER_SRCS:$(PARTITIONER_SRC_DIR)%=%)

STANDALONE_PARTITIONER_SRCS:=$(subst /,x,$(STANDALONE_PARTITIONER_SRCS))

define COPY_STANDALONE_SOURCE
$(1): $$(PARTITIONER_SRC_DIR)/$$$(subst x,/,$(1))
	@cp $$< $$@
endef

$(foreach src, $(STANDALONE_PARTITIONER_SRCS), 								\
				$(eval $(call COPY_STANDALONE_SOURCE, $(src))))

PARTITIONER_SRCS+=															\
				$(STANDALONE_PARTITIONER_SRCS)								\
				$(PARTITIONER_DIR)/atf_stubs.c								\

TF_CFLAGS+=-DATF_BUILD
INCLUDES+=$(PARTITIONER_INCLUDES)
BL31_SOURCES+=$(PARTITIONER_SRCS)

distclean realclean clean: partitioner_clean

partitioner_clean:
	$(call SHELL_DELETE_ALL,$(STANDALONE_PARTITIONER_SRCS))

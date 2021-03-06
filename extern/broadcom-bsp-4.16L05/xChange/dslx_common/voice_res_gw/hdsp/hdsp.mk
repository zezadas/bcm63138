###########################################################################
#
# This makefile is used to build the HDSP module.
#
###########################################################################


#
# This should match the target name.
#
XCHG_LIB_BASE  := hdsp

HDSP_ROOT    := $(VRG_DIR_$(XCHG_LIB_BASE))


#
# List of all source files. Do not specify directories, we use vpath below.
#
XCHG_SRC_FILES_$(XCHG_LIB_BASE) := $(notdir $(wildcard $(HDSP_ROOT)/src/*.c $(HDSP_ROOT)/toneprofiles/*.c))

XCHG_SRC_FILES += $(XCHG_SRC_FILES_$(XCHG_LIB_BASE))


#
# We use vpath so that the object files don't wind up in nested subdirectories.
# These must be absolute paths in order to support non-recursive makefiles.
#
vpath %.c $(HDSP_ROOT)/src $(HDSP_ROOT)/toneprofiles


#
# Add in private directories that are only needed when compiling this library.
# These must be absolute paths in order to support non-recursive makefiles.
#
XCHG_C_LOCAL_INCLUDE_$(XCHG_LIB_BASE) := $(HDSP_ROOT)/toneprofiles $(VRG_LDX_HAUSWARE_INC_DIR) $(VRG_LDX_HAUSWARE_SYSINC_DIR)


#
# Add in private defs that are only needed when compiling this library.
#
XCHG_C_LOCAL_DEFS_$(XCHG_LIB_BASE) :=


#
# To set a module specific compiler option, create a target specific make
# variable which sets the option and depends on the module target name.
# For example, to enable compiler optimizations for this module:
#
#     $(XCHG_LIB_BASE): XCHG_C_OPTIMIZE_OPT = $(XCHG_C_OPTIMIZE_OPT_ENABLE)
#
# or, to disable optimizations:
#
#     $(XCHG_LIB_BASE): XCHG_C_OPTIMIZE_OPT = $(XCHG_C_OPTIMIZE_OPT_DISABLE)

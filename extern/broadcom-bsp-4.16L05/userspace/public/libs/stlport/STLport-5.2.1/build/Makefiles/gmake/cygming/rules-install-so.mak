# -*- makefile -*- Time-stamp: <05/12/09 01:46:01 ptr>

INSTALL_TAGS ?= install-shared

PHONY += install $(INSTALL_TAGS)

install: $(INSTALL_TAGS)

install-release-shared:	release-shared $(INSTALL_BIN_DIR) $(INSTALL_LIB_DIR)
	$(INSTALL_SO) ${SO_NAME_OUT} $(INSTALL_BIN_DIR)/
	$(INSTALL_SO) ${LIB_NAME_OUT} $(INSTALL_LIB_DIR)/
#	$(INSTALL_SO) ${EXP_NAME_OUT} $(INSTALL_LIB_DIR)/

install-dbg-shared:	dbg-shared $(INSTALL_BIN_DIR) $(INSTALL_LIB_DIR_DBG)
	$(INSTALL_SO) ${SO_NAME_OUT_DBG} $(INSTALL_BIN_DIR)/
	$(INSTALL_SO) ${LIB_NAME_OUT_DBG} $(INSTALL_LIB_DIR_DBG)/
#	$(INSTALL_SO) ${EXP_NAME_OUT_DBG} $(INSTALL_LIB_DIR_DBG)/

install-stldbg-shared:	stldbg-shared $(INSTALL_BIN_DIR) $(INSTALL_LIB_DIR_DBG)
	$(INSTALL_SO) ${SO_NAME_OUT_STLDBG} $(INSTALL_BIN_DIR)/
	$(INSTALL_SO) ${LIB_NAME_OUT_STLDBG} $(INSTALL_LIB_DIR_STLDBG)/
#	$(INSTALL_SO) ${EXP_NAME_OUT_STLDBG} $(INSTALL_LIB_DIR_STLDBG)/


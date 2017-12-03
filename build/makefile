# Makefile for MajorTom codebase
# Type 'make clean' to remove all images and object files
# Type 'make <board>_<build> to build an image of the <board> board for <build> hardware platform

# Directories
DIR_INC = ../h
DIR_SRC = ../c
DIR_OBJ = ../o
DIR_IMG = ../img

# A list of hardware platforms that code can be compiled for
PLATFORMS = mock

# A list of boards MajorTom contains firmware for
BOARDS = sharetest apdet telem power

# A list of modules in the shared library
MODULES = utils init can sd

# A list of compilers associated with elements of $(BUILDS)
CC_mock = gcc

# A list of compiler flags and settings associated with elements of $(BUILDS)
CFLAGS_mock = -std=gnu99 -lm -lrt

# By default, build all mock images. This has to be the first rule or else it won't run when you type 'make'
default: $(foreach i,$(BOARDS), $(i)_mock)

# Cleaning rules

# Deletes object files
cleano:
	rm -rf $(DIR_OBJ)/*

# Deletes image files
cleanimg:
	rm -rf $(DIR_IMG)/*

# Deletes object files and image files
clean: cleano cleanimg

# Phony rules
.PHONY: default cleano cleanimg clean

# Each hardware-dependent o file  (o/<board>/<board>_hw_<build>.o or o/shared/<module>_hw_<build>.o)
# depends on corresponding c file (c/<board>/<board>_hw_<build>.c or c/shared/<module>_hw_<build>.c)
# and on corresponding h file     (h/<board>/<board>.h            or h/shared/<module>.h)
define rules_hwdep_o
$(DIR_OBJ)/%_hw_$(1).o: $(DIR_SRC)/%_hw_$(1).c \
                        $(DIR_INC)/%.h
	@mkdir -p $$(@D)
	$(CC_$(1)) $(CFLAGS_$(1)) -o $$@ $$< -I$(DIR_INC) -I$(DIR_INC)/$$(firstword $$(subst /, ,$$*)) -c
endef
$(foreach i,$(PLATFORMS), $(eval $(call rules_hwdep_o,$(i))))

# Each hardware-independent o file (o/<board>/<board>.o or o/shared/<module>.o)
# depends on corresponding c file  (c/<board>/<board>.c or c/shared/<module>.c)
# and on corresponding h file      (h/<board>/<board>.h or h/shared/<module>.h)
$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c \
                $(DIR_INC)/%.h
	@mkdir -p $(@D)
	$(CC_mock) $(CFLAGS_mock) -o $@ $< -I$(DIR_INC) -I$(DIR_INC)/$(firstword $(subst /, ,$*)) -c

# Each mock image                                     (img/<board>/<board>_mock.img) depends on:
# - a corresponding hardware-independent o file       (  o/<board>/<board>.o)
# - a corresponding hardware-dependent o file         (  o/<board>/<board>_hw_mock.o)
# - the shared library's hardware-independent o files (  o/shared/<module>.o)
# - The shared library's hardware-dependent o files   (  o/shared/<module>_hw_mock.o)
# Each mock image also has a corresponding run rule that depends on the image
define rules_img_mock
$(DIR_IMG)/$(1)_mock.img: $(DIR_OBJ)/$(1)/$(1).o \
                          $(DIR_OBJ)/$(1)/$(1)_hw_mock.o \
                          $(foreach j,$(MODULES),$(DIR_OBJ)/shared/$(j).o) \
                          $(foreach j,$(MODULES),$(DIR_OBJ)/shared/$(j)_hw_mock.o)
	@mkdir -p $(DIR_IMG)
	$(CC_mock) $(CFLAGS_mock) -o $$@ $$?
$(1)_mock: $(DIR_IMG)/$(1)_mock.img
$(1)_mock_run: $(DIR_IMG)/$(1)_mock.img
	$(DIR_IMG)/$(1)_mock.img
.PHONY: $(1)_mock $(1)_mock_run
endef
$(foreach i,$(BOARDS),$(eval $(call rules_img_mock,$(i))))
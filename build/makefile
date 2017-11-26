# Makefile for MajorTom codebase
# Type 'make clean' to remove all images and object files
# Type 'make <board>_<>

# Directories
DIR_INC = ../h
DIR_SRC = ../c
DIR_OBJ = ../o
DIR_IMG = ../img

# A list of hardware platforms that code can be compiled for
REAL_BUILDS = none_right_now
BUILDS = mock

# A list of boards MajorTom contains firmware for
BOARDS = sharetest apdet telem power

# A list of compilers associated with elements of $(BUILDS)
CC_mock = gcc

# By default, mock every board. This has to be the first rule or else it won't run when you type 'make'
default:
	$(foreach i,$(BOARDS), ./mock $(i) ;)

# Each mock o file must be compiled with the MOCK flag
$(DIR_OBJ)/%_hw_mock.o: $(DIR_SRC)/%_hw_mock.c $(DIR_INC)/%.h
	@mkdir -p $(@D)
	$(CC_mock) -D MOCK=yes -o $@ $< -I$(DIR_INC) -I$(DIR_INC)/$(firstword $(subst /, ,$*)) -c

# Each o file depends on corresponding c and h files
define rules_o
$(DIR_OBJ)/%_hw_$(1).o: $(DIR_SRC)/%_hw_$(1).c $(DIR_INC)/%.h
	@mkdir -p $$(@D)
	$(CC_$(1)) -o $$@ $$< -I$(DIR_INC) -I$(DIR_INC)/$$(firstword $$(subst /, ,$$*)) -c
endef

define rules_o_aux
$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(DIR_INC)/%.h
	@mkdir -p $$(@D)
	$(CC_$(1)) -o $$@ $$< -I$(DIR_INC) -I$(DIR_INC)/$$(firstword $$(subst /, ,$$*)) -c
endef

$(foreach i,$(REAL_BUILDS),$(eval $(call rules_o,$(i))))
$(foreach i,$(BUILDS), $(eval $(call rules_o_aux,$(i))))

# Each mock build depends on corresponding c and h files, and on everything in the shared code
define rules_img_mock
.PHONY: $(1)_mock
$(1)_mock: $(DIR_IMG)/$(1)_mock.img
$(DIR_IMG)/$(1)_mock.img: $(DIR_OBJ)/$(1)/$(1).o $(DIR_OBJ)/$(1)/$(1)_hw_mock.o $(DIR_OBJ)/shared/init_hw_mock.o $(DIR_OBJ)/shared/sd_hw_mock.o $(DIR_OBJ)/shared/can_hw_mock.o $(DIR_OBJ)/shared/mock_utils.o
	@mkdir -p $(DIR_IMG)
	$(CC_mock) -lm -o $$@ $$?
endef
$(foreach i,$(BOARDS),$(eval $(call rules_img_mock,$(i))))

# Cleaning rules
cleano:
	rm -rf $(DIR_OBJ)/*
cleanimg:
	rm -rf $(DIR_IMG)/*
clean: cleano cleanimg

# Phony rules
.PHONY: default cleano cleanimg clean

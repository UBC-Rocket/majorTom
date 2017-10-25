# Makefile for MajorTom codebase
# Type 'make clean' to remove all images and object files
# Type 'make <board>_<>

# Directories
DIR_INC = ../h
DIR_SRC = ../c
DIR_OBJ = ../o
DIR_IMG = ../img

# A list of hardware platforms that code can be compiled for
BUILDS = mock

# A list of boards MajorTom contains firmware for
BOARDS = sharetest apdec telem power

# A list of compilers associated with elements of $(BUILDS)
CC_mock = gcc

# Each o file depends on corresponding c and h files
define rules_o
$(DIR_OBJ)/%_$(1).o: $(DIR_SRC)/%_$(1).c $(DIR_INC)/%.h
	@mkdir -p $$(@D)
	$(CC_$(1)) -o $$@ $$< -I $(DIR_INC) -c
endef
$(foreach i,$(BUILDS),$(eval $(call rules_o,$(i))))

# Each mock build depends on corresponding c and h files, and on everything in the shared code
define rules_img_mock
.PHONY: $(1)_mock
$(1)_mock: $(DIR_IMG)/$(1)_mock.img
$(DIR_IMG)/$(1)_mock.img: $(DIR_OBJ)/$(1)/$(1)_mock.o $(DIR_OBJ)/shared/init_mock.o $(DIR_OBJ)/shared/gpio_mock.o $(DIR_OBJ)/shared/can_mock.o
	@mkdir -p $(DIR_IMG)
	$(CC_mock) -o $$@ $$?
endef
$(foreach i,$(BOARDS),$(eval $(call rules_img_mock,$(i))))

# Cleaning rules
cleano:
	rm -rf $(DIR_OBJ)/*
cleanimg:
	rm -rf $(DIR_IMG)/*
clean: cleano cleanimg

# Phony rules
.PHONY: cleano cleanimg clean

.PHONY: all clean fclean re norm
NAME = template
INCLUDES_DIR = includes
SRCS_DIR = srcs
OBJS_DIR = objs
PKGS_DIR = pkgs
NPD_FLAG = --no-print-directory

PKGS = \
	common \
	mem \
	mini_printf \
	slice \

FILES = \
	main \

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
IFLAGS = -I$(INCLUDES_DIR) -I$(PKGS_DIR)/$(INCLUDES_DIR)
LFLAGS = -L$(PKGS_DIR) -l$(LIB)
VFLAGS = \
	--track-origins=yes \
	--leak-check=full \
	--show-leak-kinds=all \

LOGFILE = valgrind_result.log

OBJS_EXIST = .objs

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILES)))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_EXIST)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@$(foreach pkg, $(PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg) all;)

$(OBJS_EXIST):
	@mkdir -p $(OBJS_DIR)

all: $(NAME)

val: re
	@valgrind $(VFLAGS) ./$(NAME) > $(LOGFILE) 2>&1
	@code $(LOGFILE)

$(NAME): $(OBJS)
	@PKG_OBJS=; \
	$(foreach pkg, $(PKGS), $(eval PKG_OBJS += $(addprefix $(PKGS_DIR)/$(pkg)/, $(shell make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg) print-objs;)))) \
	$(CC) $(OBJS) -o $@

clean: pkg_clean
	@$(RM) -rf $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LOGFILE)

re: fclean all

# Color
RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

define ok
	echo $1"$(GREEN)OK$(RESET)"
endef

define ko
	echo $1"$(RED)KO!$(RESET)"
endef

norm:
	@$(call check_norminette, $(SRCS_DIR))
	@$(call check_norminette, $(INCLUDES_DIR))
	@$(call check_norminette, $(PKGS_DIR))

define check_norminette
	@if norminette $1 | grep -q Error; then \
		norminette $1 | grep Error; \
	else \
		$(call ok, $1": "); \
	fi
endef

pkg_clean:
	@$(foreach pkg, $(PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg) clean;)

pkg_test:
	@$(foreach pkg, $(PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg) test;)

pkg_mac:
	@$(foreach pkg, $(PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg) mac;)

MAKE_SAMPLE = make_sample
MAKE_LOG = make_log

$(MAKE_SAMPLE):
	@sed -n '/^# ### MAKE BEGIN$$/,/^# ### MAKE END$$/p' $(MAKEFILE) \
	| sed '1d' \
	| sed '$$d' \
	| sed 's/^.$$//; s/^..//' > $(MAKE_SAMPLE)

$(MAKE_LOG):
	@touch $(MAKE_LOG)

make_check: make_log_clean make_diff make_clean

make_diff: $(MAKE_SAMPLE) $(MAKE_LOG)
	@$(foreach pkg, $(PKGS), awk '/^# ============================== Editable Area ============================== #/{f=1} /^# ============================= End of Editable ============================= #/{f=0; next} !f' $(PKGS_DIR)/$(pkg)/Makefile > $(pkg)make;)
	@success=true; \
	for pkg in $(PKGS); do \
		echo "==== $$pkg ====" >> $(MAKE_LOG); \
		if ! diff $(MAKE_SAMPLE) $$pkg\make >> $(MAKE_LOG); then \
			success=false; \
		fi; \
	done; \
	if [ $$success = true ]; then \
		rm -f $(MAKE_LOG); \
		$(call ok, "Makefile is all "); \
	else \
		$(call ko, "Makefile is "); \
	fi

MAKEFILE = Makefile
MAKEFILE_TMP = Makefile_tmp

make_sync:
	@if [ -z "$(SYNC_PKG)" ]; then \
		echo "Error: SYNC_PKG is empty."; \
		exit 0; \
	else \
		awk '/^# ### MAKE BEGIN/{exit} {print}' $(MAKEFILE) > $(MAKEFILE_TMP); \
		echo "### MAKE BEGIN" >> $(MAKEFILE_TMP); \
		awk '/^# ============================== Editable Area ============================== #/{f=1} /^# ============================= End of Editable ============================= #/{f=0; next} !f' $(PKGS_DIR)/$(SYNC_PKG)/Makefile >> $(MAKEFILE_TMP); \
		echo "### MAKE END" >> $(MAKEFILE_TMP); \
		sed -i '' '/^### MAKE BEGIN/,/^### MAKE END/ s/^/# /' $(MAKEFILE_TMP); \
		$(RM) $(MAKEFILE); \
		mv $(MAKEFILE_TMP) $(MAKEFILE); \
		$(foreach pkg, $(PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg) make_sync SYNC_PKG=$(SYNC_PKG);) \
	fi

make_clean:
	@$(foreach pkg, $(PKGS), $(RM) $(pkg)make;)
	@$(RM) $(MAKE_SAMPLE)

make_log_clean:
	@$(RM) $(MAKE_LOG)

# ### MAKE BEGIN
# .PHONY: all print-objs clean re otest mtest ntest test output_test memory_test norminette_test test_clean
# PKGS_DIR = ..
# INCLUDES_DIR = includes
# SRCS_DIR = srcs
# OBJS_DIR = objs
# TESTS_DIR = tests
# TEST_PRE = test_
# TEST_NAME = $(addprefix $(TESTS_DIR)/, $(addprefix $(TEST_PRE), $(PKG_NAME)))
# NPD_FLAG = --no-print-directory
#
# CC = cc
# CFLAGS = -Wall -Werror -Wextra -g
# IFLAGS = -I$(INCLUDES_DIR) $(foreach pkg, $(PKGS), -I$(PKGS_DIR)/$(pkg)/$(INCLUDES_DIR))
#
# OBJS_EXIST = .objs
#
# SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
# OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILES)))
#
# all: $(OBJS)
#
# $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_EXIST)
# 	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
# 	@$(foreach pkg, $(PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg);)
#
# $(OBJS_EXIST):
# 	@mkdir -p $(OBJS_DIR)
#
# print-objs:
# 	@echo $(OBJS)
#
# clean:
# 	@$(RM) -rf $(OBJS_DIR)
# 	@$(foreach pkg, $(PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg) clean;)
#
# re: clean all
#
# # Color
# RESET = \033[0m
# RED = \033[31m
# GREEN = \033[32m
# YELLOW = \033[33m
# BLUE = \033[34m
# MAGENTA = \033[35m
# CYAN = \033[36m
# WHITE = \033[37m
#
# TST_IFLAGS = -I$(TESTS_DIR)/$(INCLUDES_DIR) $(foreach tst_pkg, $(TST_PKGS), -I$(PKGS_DIR)/$(tst_pkg)/$(INCLUDES_DIR))
# VFLAGS = \
# 	--track-origins=yes \
# 	--leak-check=full \
# 	--show-leak-kinds=all \
#
# TST_OBJ_EXIST = st_obj
#
# TST_SRCS = $(addprefix $(TESTS_DIR)/$(SRCS_DIR)/$(TEST_PRE), $(addsuffix .c, $(FILES)))
# TST_SRCS += $(addprefix $(TESTS_DIR)/$(SRCS_DIR)/$(TEST_PRE), $(addsuffix .c, main))
# TST_OBJS = $(addprefix $(TESTS_DIR)/$(OBJS_DIR)/$(TEST_PRE), $(addsuffix .o, $(FILES)))
# TST_OBJS += $(addprefix $(TESTS_DIR)/$(OBJS_DIR)/$(TEST_PRE), $(addsuffix .o, main))
#
# EXPECTED_RESULT_LOG = $(TESTS_DIR)/expected_result.log
# REAL_RESULT_LOG = $(TESTS_DIR)/real_result.log
# VALGRIND_LOG = $(TESTS_DIR)/valgrind.log
# NORM_LOG = $(TESTS_DIR)/norm.log
# NO_ERROR_STR = "ERROR SUMMARY: 0 errors from 0 contexts"
# NO_LEAKS_STR = "All heap blocks were freed -- no leaks are possible"
#
# $(VALGRIND_LOG): $(TEST_NAME)
# 	@valgrind $(VFLAGS) ./$(TEST_NAME) > $(VALGRIND_LOG) 2>&1
#
# $(EXPECTED_RESULT_LOG):
# 	@sed -n '/^### BEGIN$$/,/^### END$$/p' $(MAKEFILE_LIST) | sed '1d; $$d' | sed 's/^# //' > $(EXPECTED_RESULT_LOG)
#
# $(TEST_NAME): $(OBJS) $(TST_OBJS)
# 	@PKG_OBJS=; \
# 	TST_PKG_OBJS=; \
# 	$(foreach pkg, $(PKGS), $(eval PKG_OBJS += $(addprefix $(PKGS_DIR)/$(pkg)/, $(shell make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg) print-objs;)))) \
# 	$(foreach tst_pkg, $(TST_PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(tst_pkg);) \
# 	$(foreach tst_pkg, $(TST_PKGS), $(eval TST_PKG_OBJS += $(addprefix $(PKGS_DIR)/$(tst_pkg)/, $(shell make $(NPD_FLAG) -C $(PKGS_DIR)/$(tst_pkg) print-objs;)))) \
# 	$(CC) $(CFLAGS) $(IFLAGS) $(TST_IFLAGS) $(OBJS) $(PKG_OBJS) $(TST_OBJS) $(TST_PKG_OBJS) -o $@
#
# $(TESTS_DIR)/$(OBJS_DIR)/%.o: $(TESTS_DIR)/$(SRCS_DIR)/%.c | $(TST_OBJ_EXIST)
# 	@$(CC) $(CFLAGS) $(IFLAGS) $(TST_IFLAGS) -c $< -o $@
#
# $(TST_OBJ_EXIST):
# 	@mkdir -p $(TESTS_DIR)/$(OBJS_DIR)
#
# define ok
# 	echo $1"$(GREEN)OK$(RESET)"
# endef
#
# define ko
# 	echo $1"$(RED)KO!$(RESET)"
# endef
#
# otest: output_test
#
# mtest: memory_test
#
# ntest: norminette_test
#
# test: test_start output_test memory_test norminette_test test_clean
#
# mac: test_start output_test norminette_test test_clean
#
# retest: log_clean test
#
# test_start:
# 	@echo "$(YELLOW)$(PKG_NAME)$(RESET)"
#
# output_test: $(TEST_NAME) $(EXPECTED_RESULT_LOG)
# 	@./$(TEST_NAME) > $(REAL_RESULT_LOG) 2>&1
# 	@if cmp -s $(REAL_RESULT_LOG) $(EXPECTED_RESULT_LOG); then \
# 		$(call ok, "output test: "); \
# 		rm $(REAL_RESULT_LOG) $(EXPECTED_RESULT_LOG); \
# 	else \
# 		$(call ko, "output test: "); \
# 	fi
#
# memory_test: $(VALGRIND_LOG)
# 	@if grep -q $(NO_LEAKS_STR) $(VALGRIND_LOG) && grep -q $(NO_ERROR_STR) $(VALGRIND_LOG); then \
# 		$(call ok, "memory test: "); \
# 		rm $(VALGRIND_LOG); \
# 	else \
# 		$(call ko, "memory test: "); \
# 	fi
#
# norminette_test:
# 	@NORM_ERROR_FOUND=0; \
# 	touch $(NORM_LOG); \
# 	$(call check_norminette, $(SRCS_DIR)); \
# 	$(call check_norminette, $(INCLUDES_DIR)); \
# 	$(call check_norminette, $(TESTS_DIR)); \
# 	if [ $$NORM_ERROR_FOUND -eq 0 ]; then \
# 		$(call ok, " norm  test: "); \
# 		rm $(NORM_LOG); \
# 	else \
# 		$(call ko, " norm  test: "); \
# 	fi
#
# define check_norminette
# 	if norminette $1 | grep -q Error; then \
# 		norminette $1 | grep Error >> $(NORM_LOG); \
# 		NORM_ERROR_FOUND=1; \
# 	fi
# endef
#
# test_clean:
# 	@$(RM) -rf $(OBJS_DIR)
# 	@$(RM) -rf $(TESTS_DIR)/$(OBJS_DIR)
# 	@$(foreach tst_pkg, $(TST_PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(tst_pkg) clean;)
# 	@$(RM) $(TEST_NAME)
#
# log_clean:
# 	@$(RM) $(REAL_RESULT_LOG) $(EXPECTED_RESULT_LOG) $(VALGRIND_LOG) $(NORM_LOG)
#
# MAKEFILE = Makefile
# MAKEFILE_TMP = Makefile_tmp
#
# make_sync:
# 	@if [ -z "$(SYNC_PKG)" ]; then \
# 		echo "Error: SYNC_PKG is empty."; \
# 		exit 0; \
# 	else \
# 		awk '/^# ============================== Editable Area ============================== #/{f=1} /^# ============================= End of Editable ============================= #/{print; f=0} f' Makefile > Makefile_tmp; \
# 		awk '/^# ============================== Editable Area ============================== #/{f=1} /^# ============================= End of Editable ============================= #/{f=0; next} !f' $(PKGS_DIR)/$(SYNC_PKG)/Makefile >> $(MAKEFILE_TMP); \
# 		awk '/^$(EDITABLE_START)/{f=1} /^$(EDITABLE_END)/{f=0; next} !f' $(PKGS_DIR)/$(SYNC_PKG)/Makefile >> $(MAKEFILE_TMP); \
# 		$(RM) $(MAKEFILE); \
# 		mv $(MAKEFILE_TMP) $(MAKEFILE); \
# 	fi
# ### MAKE END

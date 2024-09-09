# ============================== Editable Area ============================== #
PKG_NAME				=	slice

PKGS					=	 \


TST_PKGS				=	 \
							common \
							mini_printf \

FILES					=	 \
							slice \

### BEGIN
# If *cap is NULL, update_cap return : -1
# len = 0, cap = 0
# update_cap result : 0
# new cap : 0
# len = 1, cap = 0
# update_cap result : 1
# new cap : 1
# len = 200, cap = 0
# update_cap result : 1
# new cap : 256
# len = 200, cap = 199
# update_cap result : 1
# new cap : 398
# len = 200, cap = 200
# update_cap result : 0
# new cap : 200
# len = 200, cap = 201
# update_cap result : 0
# new cap : 201
# len = 1025, cap = 0
# update_cap result : 1
# new cap : 1280
# len = 1025, cap = 1023
# update_cap result : 1
# new cap : 2046
# len = 1025, cap = 1024
# update_cap result : 1
# new cap : 1280
# 42
# 64
### END
# ============================= End of Editable ============================= #
.PHONY:						all print-objs clean re otest mtest ntest test output_test memory_test norminette_test test_clean
LIB						=	lib
PKGS_DIR				=	..
INCLUDES_DIR			=	includes
SRCS_DIR				=	srcs
OBJS_DIR				=	objs
TESTS_DIR				=	tests
TEST_PRE				=	test_
TEST_NAME				=	$(addprefix $(TESTS_DIR)/, $(addprefix $(TEST_PRE), $(PKG_NAME)))
NPD_FLAG				=	--no-print-directory

CC						=	cc
CFLAGS					=	-Wall -Werror -Wextra -g
IFLAGS					=	-I$(INCLUDES_DIR) $(foreach pkg, $(PKGS), -I$(PKGS_DIR)/$(pkg)/$(INCLUDES_DIR))

OBJS_EXIST				=	.objs


SRCS					=	$(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS					=	$(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILES)))

all:						$(OBJS)

$(OBJS_DIR)/%.o:				$(SRCS_DIR)/%.c | $(OBJS_EXIST)
							@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
							@$(foreach pkg, $(PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg);)

$(OBJS_EXIST):
							@mkdir -p $(OBJS_DIR)

print-objs:
							@echo $(OBJS)

clean:
							@$(RM) -rf $(OBJS_DIR)
							@$(foreach pkg, $(PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg) clean;)

re:							clean all



DEF						=	\033[0m
RED						=	\033[31m
GRN						=	\033[32m
YLW						=	\033[33m
BLU						=	\033[34m

TST_IFLAGS				=	 -I$(TESTS_DIR)/$(INCLUDES_DIR) $(foreach tst_pkg, $(TST_PKGS), -I$(PKGS_DIR)/$(tst_pkg)/$(INCLUDES_DIR))
VFLAGS					=	 \
							--track-origins=yes \
							--leak-check=full \
							--show-leak-kinds=all \

TST_OBJ_EXIST			=	.tst_obj

TST_SRCS				=	$(addprefix $(TESTS_DIR)/$(SRCS_DIR)/$(TEST_PRE), $(addsuffix .c, $(FILES)))
TST_SRCS				+=	$(addprefix $(TESTS_DIR)/$(SRCS_DIR)/$(TEST_PRE), $(addsuffix .c, main))
TST_OBJS				=	$(addprefix $(TESTS_DIR)/$(OBJS_DIR)/$(TEST_PRE), $(addsuffix .o, $(FILES)))
TST_OBJS				+=	$(addprefix $(TESTS_DIR)/$(OBJS_DIR)/$(TEST_PRE), $(addsuffix .o, main))

EXPECTED_RESULT_LOG		=	$(TESTS_DIR)/expected_result.log
REAL_RESULT_LOG			=	$(TESTS_DIR)/real_result.log
VALGRIND_LOG			=	$(TESTS_DIR)/valgrind.log
NORM_LOG				=	$(TESTS_DIR)/norm.log
NO_ERROR_STR			=	"ERROR SUMMARY: 0 errors from 0 contexts"
NO_LEAKS_STR			=	"All heap blocks were freed -- no leaks are possible"

$(VALGRIND_LOG):			$(TEST_NAME)
							@valgrind $(VFLAGS) ./$(TEST_NAME) > $(VALGRIND_LOG) 2>&1

$(EXPECTED_RESULT_LOG):
							@sed -n '/^### BEGIN$$/,/^### END$$/p' $(MAKEFILE_LIST) | sed '1d; $$d' | sed 's/^# //' > $(EXPECTED_RESULT_LOG)

$(TEST_NAME):				$(OBJS) $(TST_OBJS)
							@PKG_OBJS=; \
							TST_PKG_OBJS=; \
							$(foreach pkg, $(PKGS), $(eval PKG_OBJS += $(addprefix $(PKGS_DIR)/$(pkg)/, $(shell make $(NPD_FLAG) -C $(PKGS_DIR)/$(pkg) print-objs;)))) \
							$(foreach tst_pkg, $(TST_PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(tst_pkg);) \
							$(foreach tst_pkg, $(TST_PKGS), $(eval TST_PKG_OBJS += $(addprefix $(PKGS_DIR)/$(tst_pkg)/, $(shell make $(NPD_FLAG) -C $(PKGS_DIR)/$(tst_pkg) print-objs;)))) \
							$(CC) $(CFLAGS) $(IFLAGS) $(TST_IFLAGS) $(OBJS) $(PKG_OBJS) $(TST_OBJS) $(TST_PKG_OBJS) -o $@

$(TESTS_DIR)/$(OBJS_DIR)/%.o:	$(TESTS_DIR)/$(SRCS_DIR)/%.c | $(TST_OBJ_EXIST)
							@$(CC) $(CFLAGS) $(IFLAGS) $(TST_IFLAGS) -c $< -o $@

$(TST_OBJ_EXIST):
							@mkdir -p $(TESTS_DIR)/$(OBJS_DIR)

define ok
							echo $1"$(GRN)OK$(DEF)"
endef

define ko
							echo $1"$(RED)KO!$(DEF)"
endef

otest:						output_test

mtest:						memory_test

ntest:						norminette_test

test:						test_start output_test memory_test norminette_test test_clean

mac:						test_start output_test norminette_test test_clean

retest:						log_clean test

test_start:
							@echo "$(YLW)$(PKG_NAME)$(DEF)"

output_test:				$(TEST_NAME) $(EXPECTED_RESULT_LOG)
							@./$(TEST_NAME) > $(REAL_RESULT_LOG) 2>&1
							@if cmp -s $(REAL_RESULT_LOG) $(EXPECTED_RESULT_LOG); then \
								$(call ok, "output test: "); \
								rm $(REAL_RESULT_LOG) $(EXPECTED_RESULT_LOG); \
							else \
								$(call ko, "output test: "); \
							fi

memory_test:				$(VALGRIND_LOG)
							@if grep -q $(NO_LEAKS_STR) $(VALGRIND_LOG) && grep -q $(NO_ERROR_STR) $(VALGRIND_LOG); then \
								$(call ok, "memory test: "); \
								rm $(VALGRIND_LOG); \
							else \
								$(call ko, "memory test: "); \
							fi

norminette_test:
							@NORM_ERROR_FOUND=0; \
							touch $(NORM_LOG); \
							$(call check_norminette, $(SRCS_DIR)); \
							$(call check_norminette, $(INCLUDES_DIR)); \
							$(call check_norminette, $(TESTS_DIR)); \
							if [ $$NORM_ERROR_FOUND -eq 0 ]; then \
								$(call ok, " norm  test: "); \
								rm $(NORM_LOG); \
							else \
								$(call ko, " norm  test: "); \
							fi

define check_norminette
							if norminette $1 | grep -q Error; then \
								norminette $1 | grep Error >> $(NORM_LOG); \
								NORM_ERROR_FOUND=1; \
							fi
endef

test_clean:
							@$(RM) -rf $(OBJS_DIR)
							@$(RM) -rf $(TESTS_DIR)/$(OBJS_DIR)
							@$(foreach tst_pkg, $(TST_PKGS), make $(NPD_FLAG) -C $(PKGS_DIR)/$(tst_pkg) clean;)
							@$(RM) $(TEST_NAME)

log_clean:
							@$(RM) $(REAL_RESULT_LOG) $(EXPECTED_RESULT_LOG) $(VALGRIND_LOG) $(NORM_LOG)

MAKEFILE				=	Makefile
MAKEFILE_TMP			=	Makefile_tmp

make_sync:
							@if [ -z "$(SYNC_PKG)" ]; then \
								echo "Error: SYNC_PKG is empty."; \
								exit 0; \
							else \
								awk '/^# ============================== Editable Area ============================== #/{f=1} /^# ============================= End of Editable ============================= #/{print; f=0} f' Makefile > Makefile_tmp; \
								awk '/^# ============================== Editable Area ============================== #/{f=1} /^# ============================= End of Editable ============================= #/{f=0; next} !f' $(PKGS_DIR)/$(SYNC_PKG)/Makefile >> $(MAKEFILE_TMP); \
								awk '/^$(EDITABLE_START)/{f=1} /^$(EDITABLE_END)/{f=0; next} !f' $(PKGS_DIR)/$(SYNC_PKG)/Makefile >> $(MAKEFILE_TMP); \
								$(RM) $(MAKEFILE); \
								mv $(MAKEFILE_TMP) $(MAKEFILE); \
							fi

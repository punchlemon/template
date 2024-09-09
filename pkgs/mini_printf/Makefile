# ============================== Editable Area ============================== #
PKG_NAME			=	mini_printf

PKGS				=	 \
						common \

TST_PKGS				=	 \


FILES				=	 \
						mini_printf \
						put_num \

### BEGIN
# 42
# 0
# -42
# 2147483646
# 2147483647
# -2147483647
# -2147483648
# 42
# 0
# 4294967295
# 4294967294
# 42
# 0
# -42
# 9223372036854775806
# 9223372036854775807
# -9223372036854775807
# -9223372036854775808
# 42
# 0
# 18446744073709551615
# 18446744073709551614
# (null)
# Hello world!

# a
# b
# c
# -1
# 2
# -1
# 2
# 2
# 2
# 7
# testhello42
# 92233720368547758064243atesta
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

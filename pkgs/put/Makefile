.PHONY:						all print-objs clean re otest mtest ntest test output_test memory_test norminette_test test_clean
LIB						=	lib
PKG_DIR					=	..
INC_DIR					=	inc
SRC_DIR					=	src
OBJ_DIR					=	obj
TST_DIR					=	tst
TST_PRE					=	tst_
TST_NAME				=	$(addprefix $(TST_DIR)/, $(addprefix $(TST_PRE), $(PKG_NAME)))
NPD_FLAG				=	--no-print-directory

CC						=	cc
CFLAGS					=	-Wall -Werror -Wextra -g
IFLAGS					=	-I$(INC_DIR) $(foreach pkg, $(PKGS), -I$(PKG_DIR)/$(pkg)/$(INC_DIR))

OBJ_EXIST				=	.obj

# ============================== Editable Area ============================== #
PKG_NAME			=	put

PKGS				=	 \
						common \

FILES				=	 \
						put \
# ============================= End of Editable ============================= #

SRCS					=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJS					=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

all:						$(OBJS)

$(OBJ_DIR)/%.o:				$(SRC_DIR)/%.c | $(OBJ_EXIST)
							@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_EXIST):
							@mkdir -p $(OBJ_DIR)

print-objs:
							@echo $(OBJS)

clean:						test_clean
							@$(RM) -rf $(OBJ_DIR)

re:							clean all



DEF						=	\033[0m
RED						=	\033[31m
GRN						=	\033[32m

TST_IFLAGS				=	 -I$(TST_DIR)/$(INC_DIR)
VFLAGS					=	 \
							--track-origins=yes \
							--leak-check=full \
							--show-leak-kinds=all \

TST_OBJ_EXIST			=	.tst_obj

TST_SRCS				=	$(addprefix $(TST_DIR)/$(SRC_DIR)/$(TST_PRE), $(addsuffix .c, $(FILES)))
TST_SRCS				+=	$(addprefix $(TST_DIR)/$(SRC_DIR)/$(TST_PRE), $(addsuffix .c, main))
TST_OBJS				=	$(addprefix $(TST_DIR)/$(OBJ_DIR)/$(TST_PRE), $(addsuffix .o, $(FILES)))
TST_OBJS				+=	$(addprefix $(TST_DIR)/$(OBJ_DIR)/$(TST_PRE), $(addsuffix .o, main))

EXPECTED_RESULT_LOG		=	$(TST_DIR)/expected_result.log
REAL_RESULT_LOG			=	$(TST_DIR)/real_result.log
VALGRIND_LOG			=	$(TST_DIR)/valgrind.log
NORM_LOG				=	$(TST_DIR)/norm.log
NO_ERROR_STR			=	"ERROR SUMMARY: 0 errors from 0 contexts"
NO_LEAKS_STR			=	"All heap blocks were freed -- no leaks are possible"

$(VALGRIND_LOG):			$(TST_NAME)
							@valgrind $(VFLAGS) ./$(TST_NAME) > $(VALGRIND_LOG) 2>&1

$(TST_NAME):				$(OBJS) $(TST_OBJS)
							@PKG_OBJS=; \
							$(foreach pkg, $(PKGS), make $(NPD_FLAG) -C $(PKG_DIR)/$(pkg);) \
							$(foreach pkg, $(PKGS), $(eval PKG_OBJS += $(PKG_DIR)/$(pkg)/$(shell make -C $(PKG_DIR)/$(pkg) print-objs))) \
							$(CC) $(CFLAGS) $(IFLAGS) $(TST_IFLAGS) $(OBJS) $(PKG_OBJS) $(TST_OBJS) -o $@

$(TST_DIR)/$(OBJ_DIR)/%.o:	$(TST_DIR)/$(SRC_DIR)/%.c | $(TST_OBJ_EXIST)
							@$(CC) $(CFLAGS) $(IFLAGS) $(TST_IFLAGS) -c $< -o $@

$(TST_OBJ_EXIST):
							@mkdir -p $(TST_DIR)/$(OBJ_DIR)

define ok
							echo "$(PKG_NAME) is $(GRN)OK$(DEF)"
endef

define ko
							echo "$(PKG_NAME) is $(RED)KO!$(DEF)"
endef

otest:						output_test

mtest:						memory_test test_clean

ntest:						norminette_test

test:						output_test norminette_test test_clean

output_test:				$(TST_NAME) $(EXPECTED_RESULT_LOG)
							@./$(TST_NAME) > $(REAL_RESULT_LOG) 2>&1
							@if cmp -s $(REAL_RESULT_LOG) $(EXPECTED_RESULT_LOG); then \
								$(call ok); \
								rm $(REAL_RESULT_LOG) $(EXPECTED_RESULT_LOG); \
							else \
								$(call ko); \
							fi

memory_test:				$(VALGRIND_LOG)
							@if grep -q $(NO_LEAKS_STR) $(VALGRIND_LOG) && grep -q $(NO_ERROR_STR) $(VALGRIND_LOG); then \
								$(call ok); \
								rm $(VALGRIND_LOG); \
							else \
								$(call ko); \
							fi

norminette_test:
							@NORM_ERROR_FOUND=0; \
							touch $(NORM_LOG); \
							$(call check_norminette, $(SRC_DIR)); \
							$(call check_norminette, $(INC_DIR)); \
							$(call check_norminette, $(TST_DIR)); \
							if [ $$NORM_ERROR_FOUND -eq 0 ]; then \
								$(call ok); \
								rm $(NORM_LOG); \
							else \
								$(call ko); \
							fi

define check_norminette
							if norminette $1 | grep -q Error; then \
								norminette $1 | grep Error >> $(NORM_LOG); \
								NORM_ERROR_FOUND=1; \
							fi
endef

test_clean:
							@$(RM) -rf $(TST_DIR)/$(OBJ_DIR)
							@$(RM) $(TST_NAME)

# ============================== Editable Area ============================== #
$(EXPECTED_RESULT_LOG):
							@touch $@
							@echo "(null)" >> $@
							@echo "Hello world!" >> $@
							@echo "" >> $@
							@echo "42" >> $@
							@echo "0" >> $@
							@echo "-42" >> $@
							@echo "9223372036854775806" >> $@
							@echo "9223372036854775807" >> $@
							@echo "-9223372036854775807" >> $@
							@echo "-9223372036854775808" >> $@
# ============================= End of Editable ============================= #
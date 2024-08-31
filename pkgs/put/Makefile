PKG_NAME			=	put
LIB					=	lib
PKG_DIR				=	..
INC_DIR				=	inc
SRC_DIR				=	src
OBJ_DIR				=	obj
TST_PRE				=	tst_
TST_SRC_DIR			=	$(addprefix $(TST_PRE), $(SRC_DIR))
TST_OBJ_DIR			=	$(addprefix $(TST_PRE), $(OBJ_DIR))
TST_NAME			=	$(addprefix $(TST_PRE), $(PKG_NAME))

PKGS				=	 \
						common \

FILES				=	 \
						put \

CC					=	cc
CFLAGS				=	-Wall -Werror -Wextra -g
IFLAGS				=	-I$(INC_DIR) $(foreach pkg, $(PKGS), -I$(PKG_DIR)/$(pkg)/$(INC_DIR))
VFLAGS				=	 \
						--track-origins=yes \
						--leak-check=full \
						--show-leak-kinds=all \

EXPECTED_RESULT		=	$(TST_SRC_DIR)/expected_result
REAL_RESULT			=	$(TST_SRC_DIR)/real_result
VALGRIND_LOG		=	$(TST_SRC_DIR)/valgrind.log
NO_ERROR_STR		=	"ERROR SUMMARY: 0 errors from 0 contexts"

OBJ_EXIST			=	.obj
TST_OBJ_EXIST		=	.tst_obj

SRCS				=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJS				=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

TST_SRCS			=	$(addprefix $(TST_SRC_DIR)/$(TST_PRE), $(addsuffix .c, $(FILES)))
TST_OBJS			=	$(addprefix $(TST_OBJ_DIR)/$(TST_PRE), $(addsuffix .o, $(FILES)))

all:					$(OBJS)
						@$(foreach pkg, $(PKGS), make --no-print-directory -C $(PKG_DIR)/$(pkg);)

$(OBJ_DIR)/%.o:			$(SRC_DIR)/%.c | $(OBJ_EXIST)
						@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_EXIST):
						@mkdir -p $(OBJ_DIR)

clean:
						@$(RM) -rf $(OBJS)

re:						clean all

test_clean:
						@$(RM) -rf $(OBJS) $(TST_OBJS)
						@$(RM) $(TST_NAME) $(REAL_RESULT) $(EXPECTED_RESULT) $(VALGRIND_LOG)

testmac:				$(TST_NAME) $(EXPECTED_RESULT)
						@./$(TST_NAME) > $(REAL_RESULT) 2>&1
						@if cmp -s $(REAL_RESULT) $(EXPECTED_RESULT); then \
							echo "$(PKG_NAME) is OK"; \
						else \
							echo "$(PKG_NAME) is KO!"; \
							colordiff -u $(EXPECTED_RESULT) $(REAL_RESULT) || true; \
						fi
						@make test_clean

test:					$(LOGFILE) $(EXPECTED_RESULT)
						@grep -v '^==[0-9]*==' $(LOGFILE) > $(REAL_RESULT)
						@if cmp -s $(REAL_RESULT) $(EXPECTED_RESULT); then \
							echo "$(PKG_NAME) is OK"; \
						else \
							echo "$(PKG_NAME) is KO!"; \
							colordiff -u $(EXPECTED_RESULT) $(REAL_RESULT) || true; \
						fi
						@make test_clean

$(EXPECTED_RESULT):
						@echo "(null)" > $@
						@echo "Hello world!" >> $@
						@echo "" >> $@
						@echo "42" >> $@
						@echo "0" >> $@
						@echo "-42" >> $@
						@echo "9223372036854775806" >> $@
						@echo "9223372036854775807" >> $@
						@echo "-9223372036854775807" >> $@
						@echo "-9223372036854775808" >> $@

$(LOGFILE):				$(TST_NAME)
						@valgrind $(VFLAGS) ./$(TST_NAME) > $(LOGFILE) 2>&1

$(TST_NAME):			$(OBJS) $(TST_OBJS)
						@$(foreach pkg, $(PKGS), make --no-print-directory -C $(PKG_DIR)/$(pkg);)
						@$(foreach pkg, $(PKGS), cp $(PKG_DIR)/$(pkg)/$(OBJ_DIR)/* ./$(OBJ_DIR))
						@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ_DIR)/* $(TST_OBJS) -o $@

$(TST_OBJ_DIR)/%.o:		$(TST_SRC_DIR)/%.c | $(TST_OBJ_EXIST)
						@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(TST_OBJ_EXIST):
						@mkdir -p $(TST_OBJ_DIR)

.PHONY:					all clean re test
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

LOGFILE				=	$(TST_SRC_DIR)/valgrind_result.log
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

RESULT_STRING		=	"(null)\nOK21"

test:					$(LOGFILE)
						@grep -v '^==[0-9]*==' $(LOGFILE) > $(TST_SRC_DIR)/filtered_result.log
						@echo $(RESULT_STRING) > $(TST_SRC_DIR)/result
						@if cmp -s $(TST_SRC_DIR)/filtered_result.log $(TST_SRC_DIR)/result; then \
							echo "$(PKG_NAME) is OK"; \
							rm $(LOGFILE); \
							rm $(TST_SRC_DIR)/filtered_result.log; \
							rm $(TST_SRC_DIR)/result; \
						else \
							echo "$(PKG_NAME) is KO!"; \
							diff -u $(TST_SRC_DIR)/result $(TST_SRC_DIR)/filtered_result.log; \
						fi
						@make --no-print-directory test_clean

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

test_clean:
						@$(RM) -rf $(OBJS)
						@$(RM) -rf $(TST_OBJS)
						@$(RM) -rf $(TST_NAME)

re_test:				test_clean test

.PHONY:					all clean re test
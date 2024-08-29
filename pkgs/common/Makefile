PKG_NAME			=	common
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

FILES				=	 \
						ft_strlen \

CC					=	cc
CFLAGS				=	-Wall -Werror -Wextra -g
IFLAGS				=	-I$(INC_DIR) $(foreach pkg, $(PKGS), -I$(PKG_DIR)/$(pkg)/$(INC_DIR))

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

test:					$(TST_NAME)

$(TST_NAME):			$(OBJS) $(TST_OBJS)
						@$(foreach pkg, $(PKGS), make --no-print-directory -C $(PKG_DIR)/$(pkg);)
						@$(foreach pkg, $(PKGS), cp $(pkg)/$(OBJ_DIR)/* ./$(OBJ_DIR))
						@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(TST_OBJS) -o $@

$(TST_OBJ_DIR)/%.o:		$(TST_SRC_DIR)/%.c | $(TST_OBJ_EXIST)
						@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(TST_OBJ_EXIST):
						@mkdir -p $(TST_OBJ_DIR)

test_clean:
						@$(RM) -rf $(OBJS)
						@$(RM) -rf $(TST_OBJS)

re_test:				test_clean test

.PHONY:					all clean re test
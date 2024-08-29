NAME				=	test_exe
LIB					=	put
INC_DIR				=	inc
SRC_DIR				=	src
OBJ_DIR				=	obj
LIB_DIR				=	..

FILES				=	 \
						test_put \

CC					=	cc
CFLAGS				=	-Wall -Werror -Wextra -g
IFLAGS				=	-I$(INC_DIR) -I$(LIB_DIR)/$(INC_DIR)
LFLAGS				=	-L$(LIB_DIR) -l$(LIB)
VFLAGS				=	 \
						--track-origins=yes \
						--leak-check=full \
						--show-leak-kinds=all \

LOGFILE				=	valgrind_result.log

OBJ_EXIST			=	.obj

SRCS				=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJS				=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

test:					re

all:					$(NAME)

$(NAME):				$(OBJS)
						@make all --no-print-directory -C $(LIB_DIR)
						@$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o:			$(SRC_DIR)/%.c | $(OBJ_EXIST)
						@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_EXIST):
						@mkdir -p $(OBJ_DIR)

clean:
						@$(RM) -rf $(OBJ_DIR)
						@$(RM) $(NAME)

re:						clean all

.PHONY:					all clean re test

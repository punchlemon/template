NAME				=	libpkgs.a
OBJ_DIR				=	obj

PKGS				=	 \
						common \
						put \

AR					=	ar
ARFLAGS				=	rcs

all:					$(NAME)

$(NAME):
						@$(foreach pkg, $(PKGS), make --no-print-directory -C $(pkg);)
						@$(AR) $(ARFLAGS) $(NAME) $(foreach pkg, $(PKGS), $(pkg)/obj/*)

clean:
						@$(RM) -rf $(OBJ_DIR)
						@$(RM) $(NAME)

re:						clean all

.PHONY:					all clean re
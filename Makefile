CC = cc
NAME = minishell
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline -lncurses #-fsanitize=address

SRCS = minishell.c \
		execution/execute.c \
		execution/execute_2.c \
		execution/check_access.c \
		execution/pipe.c \
		signals.c \
		signals_2.c \
		free.c \
		free_2.c \
		error.c \
		parsing/cmd_prompt.c \
		parsing/quotes.c \
		parsing/quotes_utils.c \
		parsing/quotes_utils_2.c \
		parsing/quotes_utils_3.c \
		parsing/token.c \
		parsing/fill_struct.c \
		parsing/fill_struct_utils.c \
		parsing/fill_struct_utils_2.c \
		parsing/fill_struct_utils_3.c \
		parsing/init_env.c \
		parsing/init_data.c \
		parsing/init_env_utils.c \
		bulitins/export/sort_export.c \
		bulitins/echo.c \
		bulitins/cd.c \
		bulitins/cd_utils.c \
		bulitins/pwd.c \
		bulitins/export/export_export.c \
		bulitins/export/export_export_utils.c \
		bulitins/export/export_env.c \
		bulitins/export/export_env_utils.c \
		bulitins/unset.c \
		bulitins/env.c \
		bulitins/exit.c \
		bonus/wildcard.c \
		bonus/wildcard_2.c
OBJS = $(SRCS:.c=.o)
OBJDIR = objs/
OBJS_PATH = $(addprefix $(OBJDIR), $(OBJS))
PATHLIBFT = lib/libft/
PATHGET = lib/get_next_line/
INLIBFT = -L $(PATHLIBFT) -lft
INGETNEXT = -L $(PATHGET) -lftget_next_line
RED = '\033[1;31m'
BLUE ='\033[1;34m'
DEF_COLOR = '\033[0;39m'

VPATH = src:src/parsing:src/bulitins:src/bulitins/export

$(OBJDIR)%.o: %.c
	@mkdir -p $(dir $@)
	@cc -c $< -o $@ $(CFLAGS)

$(NAME):		$(OBJS_PATH)
				@echo $(BLUE)"Compiling Libft..."$(DEF_COLOR)
				@cd $(PATHLIBFT) && $(MAKE) all
				@cd $(PATHLIBFT) && $(MAKE) bonus
				@echo $(BLUE)"Compiling Get_Next_Line..."$(DEF_COLOR)
				@cd $(PATHGET) && $(MAKE) all
				@echo $(BLUE)"Compiling $(NAME)..."$(DEF_COLOR)
				@cc $(OBJS_PATH) $(INLIBFT) $(INGETNEXT) -o $(NAME) $(LDFLAGS)

all:			$(NAME)

clean:
				@echo $(RED)"Cleaning object files..."$(DEF_COLOR)
				@rm -rf $(OBJDIR)
				@cd $(PATHLIBFT) && $(MAKE) clean
				@cd $(PATHGET) && $(MAKE) clean

fclean:			clean
				@echo $(RED)"Cleaning executable files..."$(DEF_COLOR)
				@rm -f $(NAME)
				@cd $(PATHLIBFT) && $(MAKE) fclean
				@cd $(PATHGET) && $(MAKE) fclean

re:				fclean all

.PHONY:			all clean fclean re
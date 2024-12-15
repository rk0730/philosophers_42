CC := cc
CFLAGS := -Wall -Wextra -Werror

# SRCS
SRCDIR := .
SRCS += $(SRCDIR)/ft_main.c
SRCS += $(SRCDIR)/ft_arg.c

UTILS := utils
SRCS += $(SRCDIR)/$(UTILS)/ft_utils.c

#OBJS
OBJDIR := objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%$(SUFFIX).o)


INCDIR := .
INCLUDES := -I$(INCDIR)

PJT := philo

# 実行ファイル名
NAME = $(PJT)$(SUFFIX)

# SUFFIX一覧
SUFFIXES := _rkitao

# デバッグの場合分け
ifdef RKITAO_DEBUG
	DEFINES := -D RKITAO_DEBUG
	SUFFIX := $(word 1, $(SUFFIXES))
else
	DEFINES :=
	SUFFIX :=
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

rkitao:
	make RKITAO_DEBUG=1

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(UTILS)

$(OBJDIR)/%$(SUFFIX).o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(PJT)
	rm -f $(foreach SUFFIX,$(SUFFIXES),$(NAME))

re: fclean all

.PHONY: all bonus rkitao clean fclean re
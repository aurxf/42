#include "minishell"
int	ft_lst_size_file(t_lst_file *file)
{
	int			i;

	if (!file)
		return (0);
	i = 0;
	while (file != NULL)
	{
		file = file->next;
		i++;
	}
	return (i);
}
void	ft_lst_clear_file(t_lst_file **file)
{
	int			i;
	int			size;
	t_lst_file	*tmp;

	if (!(*file))
		return ;
	i = 0;
	size = ft_lst_size_file(*file);
	while (i < size)
	{
		tmp = (*file)->next;
		free(*file);
		*file = tmp;
		i++;
	}
	*file = NULL;
}

t_lst_file	*ft_lst_last_file(t_lst_file *file)
{
	int	i;
	int	size;

	i = 0;
	size = ft_lst_size_file(file);
	while (i < size - 1)
	{
		file = file->next;
		i++;
	}
	return (file);
}

void	ft_lst_add_back_file(t_lst_file *file_new, t_lst_file **file)
{
	t_lst_file	*tmp;

	if (!(*file))
	{
		*file = file_new;
		return ;
	}
	tmp = ft_lst_last_file(*file);
	tmp->next = file_new;
}
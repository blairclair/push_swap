/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigger_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:33:36 by agrodzin          #+#    #+#             */
/*   Updated: 2018/12/27 16:33:40 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"	

int		get_average(t_args *stack_ab)
{
	float	num;
	int	i;

	num = 0;
	i = 0;
	while (stack_ab)
	{
		num += stack_ab->arg; 
		stack_ab = stack_ab->next;
		i++;
	}
	return ((int)(num / i + 0.5));	
}

void	recursive_function(t_args **stack_a, t_args **stack_b, int *sorted_arr)
{
	int	check;
	int	highest;

	if ((*stack_b) == NULL || (*stack_b)->num_args == 0)
		return ;
	highest = get_highest_arg(*stack_b);
	go_to_a(stack_a, stack_b, sorted_arr);
	check = VALUE_AFTER_LAST;
	while (((*stack_a)->arg == check
	|| (*stack_a)->arg == sorted_arr[0]) && !check_if_done(*stack_a))
	{
		call_exec(stack_a, stack_b, "ra");
		check = VALUE_AFTER_LAST;
	}
	recursive_function(stack_a, stack_b, sorted_arr);
	if (get_pos_no_one(*stack_a, highest, sorted_arr[0]) >= 20)
		split(stack_a, stack_a, highest, sorted_arr);
	back_to_before(stack_a, stack_b, highest, sorted_arr);
}

int		get_pos_arg(t_args *stack_ab, int arg)
{
	int	pos;

	pos = 0;
	while (stack_ab->next)
		stack_ab = stack_ab->next;
	while (pos < stack_ab->num_args)
	{
		if (stack_ab->arg == arg)
			return (pos);
		pos++;
		stack_ab = stack_ab->prev;
	}
	return (pos);
}

int	get_value_from_pos(t_args *stack_ab, int pos)
{
	while (stack_ab && pos > 0)
	{
		stack_ab = stack_ab->next;
		pos--;
	}
	return (stack_ab->arg);
}

int		get_num_args(t_args *stack_a, t_args *stack_b)
{
	int	i;

	i = 0;
	while (stack_a)
	{
		i++;
		stack_a = stack_a->next;
	}
	while (stack_b)
	{
		i++;
		stack_b = stack_b->next;
	}
	return (i);
}

int		get_value_after_last(t_args *stack_ab, int *sorted_arr, int num_args)
{
	int	i;

	i = 0;
	while (stack_ab->next)
		stack_ab = stack_ab->next;
	while (i < num_args)
	{
		if (sorted_arr[i] == stack_ab->arg && i + 1 != num_args)
			return (sorted_arr[i + 1]);
		if (i + 1 == num_args)
			return (sorted_arr[i]);
		i++;
	}
	return (sorted_arr[i - 1]);
}

void	go_to_a(t_args **stack_a, t_args **stack_b, int *sorted_arr)
{
	int	highest_b;
	int	pos;
	int	check;
	int	len;
	int	pivot;
	
	if (!*stack_b)
		return ;
	pivot = get_average(*stack_b);
	len = (*stack_b)->num_args;
	while ((*stack_b) && len-- > 0)
	{
		if ((*stack_b)->num_args < 13)
		{
			highest_b = get_highest_arg(*stack_b);
			if (highest_b == (*stack_b)->arg)
				call_exec(stack_a, stack_b, "pa");
			else
			{
				check = VALUE_AFTER_LAST;
				if ((*stack_b)->arg == check || (*stack_b)->arg == sorted_arr[0])
				{
					call_exec(stack_a, stack_b, "pa");
					call_exec(stack_a, stack_b, "ra");
				}
				else
				{
					pos = get_pos_arg(*stack_b, get_highest_arg(*stack_b));
					if (pos <= (*stack_b)->num_args / 2)
						call_exec(stack_a, stack_b, "rrb");
					else
						call_exec(stack_a, stack_b, "rb");
				}
			}
		}
		else
		{
			if (pivot <= (*stack_b)->arg)
				call_exec(stack_a, stack_b, "pa");
			else
			{
				check = VALUE_AFTER_LAST;
				if ((*stack_b)->arg == check || (*stack_b)->arg == sorted_arr[0])
				{
					call_exec(stack_a, stack_b, "pa");
					call_exec(stack_a, stack_b, "ra");
				}
				else
					call_exec(stack_a, stack_b, "rb");
			}
		}
	}
}

int		get_pos_no_one(t_args *stack_a, int arg, int lowest)
{
	int	i;

	i = 0;
	while (stack_a && stack_a->arg <= arg && stack_a->arg != lowest)
	{
		i++;
		stack_a = stack_a->next;
	}
	return (i);
}

int		get_average_highest(t_args *stack_ab, int highest, int lowest)
{
	int	pos;
	int	num;

	pos = 0;
	num = 0;
	while (stack_ab && stack_ab->arg <= highest && stack_ab->arg != lowest)
	{
		num += stack_ab->arg;
		pos++;
		stack_ab = stack_ab->next;
	}
	return (num / pos);
}

void	back_to_before(t_args **stack_a, t_args **stack_b, int highest, int *sorted_arr)
{
	int	check;

	while (*stack_a && (*stack_a)->arg <= highest && (*stack_a)->arg != sorted_arr[0])
	{
		check = VALUE_AFTER_LAST;
		if ((*stack_a)->arg == check)
			call_exec(stack_a, stack_b, "ra");
		else
			call_exec(stack_a, stack_b, "pb");
	}
	check = VALUE_AFTER_LAST;
	if (get_lowest_arg(*stack_b) == check)
		recursive_function(stack_a, stack_b, sorted_arr);
}

void	split(t_args **stack_a, t_args **stack_b, int highest, int *sorted_arr)
{
	int	pos;
	int	check;

	check = 0;
	pos = get_average_highest(*stack_a, highest, sorted_arr[0]);
	while ((*stack_a) && (*stack_a)->arg <= highest && (*stack_a)->arg != sorted_arr[0])
	{
		if ((*stack_a)->arg >= pos)
		{
			call_exec(stack_a, stack_b, "ra");
			check++;
		}
		else
			call_exec(stack_a, stack_b, "pb");
	}
	pos = 0;
	while (pos < check)
	{
		if ((*stack_b) && (*stack_b)->arg != get_highest_arg(*stack_b))
			call_exec(stack_a, stack_b, "rrr");
		else
			call_exec(stack_a, stack_b, "rra");
		pos++;
	}
	if (get_lowest_arg(*stack_b) == get_value_after_last(*stack_a, sorted_arr,
	(*stack_a)->num_args + (*stack_b)->num_args) && check > 0)
		recursive_function(stack_a, stack_b, sorted_arr);
}

t_args	*recursive_push_swap(t_args *stack_a, t_args *stack_b, int *sorted_arr)
{
	int pivot_a;
	int	pos;
	int	highest_a;
	int	len;

	len = stack_a->num_args;
	pivot_a = get_average(stack_a);
	while (len-- > 0)
	{
		if (stack_a->arg < pivot_a)
			call_exec(&stack_a, &stack_b, "pb");
		else
			call_exec(&stack_a, &stack_b, "ra");
	}
	recursive_function(&stack_a, &stack_b, sorted_arr);
	highest_a = get_highest_arg(stack_a);
	pos = get_pos_no_one(stack_a, highest_a, sorted_arr[0]);
	if (pos >= 20)
	{
		split(&stack_a, &stack_b, get_highest_arg(stack_a), sorted_arr);
		split(&stack_a, &stack_b, get_highest_arg(stack_a), sorted_arr);
	}
	back_to_before(&stack_a, &stack_b, highest_a, sorted_arr);
	return (stack_a);
}
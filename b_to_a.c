/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 10:52:22 by agrodzin          #+#    #+#             */
/*   Updated: 2019/08/28 10:52:24 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	small_b_to_a(t_args **stack_a, t_args **stack_b, int *sorted_arr)
{
	int	highest_b;
	int	check;
	int	pos;

	highest_b = get_highest_arg(*stack_b);
	if (highest_b == (*stack_b)->arg)
		call_exec(stack_a, stack_b, "pa", 1);
	else
	{
		check = get_value_after_last(*stack_a, sorted_arr, ((*stack_b) ?
		(*stack_b)->num_args : 0) + (((*stack_a)) ? (*stack_a)->num_args : 0));
		if ((*stack_b)->arg == check || (*stack_b)->arg == sorted_arr[0])
		{
			call_exec(stack_a, stack_b, "pa", 1);
			call_exec(stack_a, stack_b, "ra", 1);
		}
		else
		{
			pos = get_pos_arg(*stack_b, get_highest_arg(*stack_b));
			if (pos <= (*stack_b)->num_args / 2)
				call_exec(stack_a, stack_b, "rrb", 1);
			else
				call_exec(stack_a, stack_b, "rb", 1);
		}
	}
}

void	long_b_to_a(t_args **stack_a, t_args **stack_b,
int pivot, int *sorted_arr)
{
	int	check;

	if (pivot <= (*stack_b)->arg)
		call_exec(stack_a, stack_b, "pa", 1);
	else
	{
		check = get_value_after_last(*stack_a, sorted_arr, ((*stack_b) ?
		(*stack_b)->num_args : 0) + (((*stack_a)) ? (*stack_a)->num_args : 0));
		if ((*stack_b)->arg == check || (*stack_b)->arg == sorted_arr[0])
		{
			call_exec(stack_a, stack_b, "pa", 1);
			call_exec(stack_a, stack_b, "ra", 1);
		}
		else
			call_exec(stack_a, stack_b, "rb", 1);
	}
}

void	go_to_a(t_args **stack_a, t_args **stack_b, int *sorted_arr)
{
	int	len;
	int	pivot;

	if (!*stack_b)
		return ;
	pivot = get_average(*stack_b);
	len = (*stack_b)->num_args;
	while ((*stack_b) && len-- > 0)
	{
		if ((*stack_b)->num_args < 13)
			small_b_to_a(stack_a, stack_b, sorted_arr);
		else
			long_b_to_a(stack_a, stack_b, pivot, sorted_arr);
	}
}
